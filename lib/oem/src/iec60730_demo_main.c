/***************************************************************************/ /**
 * @file iec60730_demo_main.c
 * @brief demo main function
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

#include "em_wdog.h"
#include "iec60730.h"
#include "iec60730_init_device.h"
#include "iec60730_oem_comm.h"
#include IEC_BOARD_HEADER
#ifdef SEGGER_RTT_PRESENT
#include "SEGGER_SYSVIEW.h"
#endif /* SEGGER */

#if defined(__ICCARM__)
#pragma diag_suppress = Pe111
#endif // IAR

__no_init imcParams_t imcTest __CLASSB_RAM;
__no_init vmcParams_t vmcTest __CLASSB_RAM;
SI_SEGMENT_POINTER(iec60730_wdogInstance, WDOG_TypeDef, SI_SEG_DATA);

uint32_t tickUartCounter;

// Bist execution status
volatile bool BistCheck_Flag;
// USART run flag
volatile bool usart_Flag;

volatile uint32_t err_test = 0;

// Global variables used for IRQ check
SI_SEGMENT_CONST(iec60730_IRQFreqBoundsSize, uint8_t, SI_SEG_CODE) = 1;
SI_SEGMENT_VARIABLE(iec60730_IRQExecCount[IEC60730_IRQ_SIZE],
                    uint8_t,
                    SI_SEG_IDATA)                                  = {0};
SI_SEGMENT_CONST(iec60730_IRQFreqBounds[IEC60730_IRQ_SIZE],
                 sl_iec60730_irq_execution_bounds_t,
                 SI_SEG_CODE) = {{.min = 9, .max = 11},
                                 {.min = 9, .max = 11},
                                 {.min = 9, .max = 11},
                                 {.min = 9, .max = 11},
                                 {.min = 9, .max = 11},
                                 {.min = 9, .max = 11},
                                 {.min = 9, .max = 11},
                                 {.min = 9, .max = 11}};

static void iec60730_Config(void);
static void iec60730_Init(void);

int main(void)
{
  System_Config();

  // Configure parameters before running #iec60730_Post
  iec60730_Config();

#ifdef SEGGER_RTT_PRESENT
  SEGGER_SYSVIEW_Conf();
  DECLARE_BENMARK_BIST();
  SEGGER_SYSVIEW_Start();
#endif /* SEGGER */

  // Power on self test
  iec60730_Post();

  // Initialize parameters before running #iec60730_Bist
  iec60730_Init();

  while (1) {
    // Application tasks
    // Process UART transmit/receive
    iec60730_commInitReceiveStatusMessage();
    if (usart_Flag) {
      usart_Flag = false;
      tickUartCounter++;
      if (tickUartCounter >= SYSTICK__100MS) {
        tickUartCounter = 0x0;
        // iec60730_commInitReceiveStatusMessage();
        iec60730_commTransmitStatusMessage();
      }
    }
    // System check tasks
    // Force the OEM test results to completed
    if (!err_test) {
      sl_iec60730_program_counter_check |=
          IEC60730_GPIO_COMPLETE | IEC60730_ANALOG_COMPLETE
          | IEC60730_OEM0_COMPLETE | IEC60730_OEM1_COMPLETE
          | IEC60730_OEM2_COMPLETE | IEC60730_OEM3_COMPLETE
          | IEC60730_OEM4_COMPLETE | IEC60730_OEM5_COMPLETE
          | IEC60730_OEM6_COMPLETE | IEC60730_OEM7_COMPLETE;
    }
    // Build In self Test
    STARTEXEC_BENMARK_BIST();
    iec60730_Bist();
    TERMINATE_BENMARK_BIST();
  }

  return 0;
}

/**************************************************************************/ /**
 * @brief Configuration
 *
 * return void
 *
 * Config parameters before running #iec60730_Post
 *****************************************************************************/
void iec60730_Config(void)
{
  /// Config parameter before running #iec60730_Post
  imcTest.gpcrc = DEFAULT_GPRC;

  vmcTest.start = RAMTEST_START;
  vmcTest.end   = RAMTEST_END;

  iec60730_wdogInstance = TEST_WDOG_INST;

  iec60730_clockTestTolerance              = 1;
  iec60730_sys_clock_test_clock_frequency = 10;
}

/**************************************************************************/ /**
 * @brief Initialize
 *
 * return void
 *
 * Initialize parameters before running #iec60730_Bist
 *****************************************************************************/
void iec60730_Init(void)
{
  iec60730_ImcInit(&imcTest);

  BistCheck_Flag  = false;
  usart_Flag      = false;
  tickUartCounter = 0x0U;

  iec60730_VmcInit(&vmcTest);

  // Reset clock tick counter
  iec60730_clockTicksReset();
}
