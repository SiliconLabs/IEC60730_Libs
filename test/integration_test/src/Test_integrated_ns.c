/***************************************************************************/ /**
 * @file Test_integrated.c
 * @brief Integrated test cases
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
#include "Test_System.h"
#include "sl_iec60730.h"
#include IEC_BOARD_HEADER
#include "oem_iec60730_timer.h"

#define IEC60730_IRQ_SIZE 8

SI_SEGMENT_CONST(iec60730_IRQFreqBoundsSize, uint8_t, SI_SEG_IDATA) = 8;
SI_SEGMENT_VARIABLE(iec60730_IRQExecCount[IEC60730_IRQ_SIZE],
                    uint8_t,
                    SI_SEG_IDATA);
SI_SEGMENT_CONST(iec60730_IRQFreqBounds[IEC60730_IRQ_SIZE],
                 iec60730_IRQExecutionBounds_t,
                 SI_SEG_CODE) = {{.min = 9, .max = 11},
                                 {.min = 9, .max = 11},
                                 {.min = 9, .max = 11},
                                 {.min = 9, .max = 11},
                                 {.min = 9, .max = 11},
                                 {.min = 9, .max = 11},
                                 {.min = 9, .max = 11},
                                 {.min = 9, .max = 11}};

__no_init imcParams_t imcTest __CLASSB_RAM;
__no_init vmcParams_t vmcTest __CLASSB_RAM;

uint8_t wdog_restart_en = 1;

void Test_irq(void)
{
  for (uint8_t i = 0; i < iec60730_IRQFreqBoundsSize; i++) {
    iec60730_IRQExecCount[i]++;
  }
}

void integration_test_run_ns(void)
{
  integration_test_init();
  iec60730_clockTicksReset();

  // Init Clock varirable
  iec60730_clockTestTolerance              = 1;
  iec60730_systemClockToTestClockFrequency = 10;

  // Config imcTest varirable
  imcTest.gpcrc = DEFAULT_GPRC;

  // Config imcTest varirable
  vmcTest.start = RAMTEST_START;
  vmcTest.end   = RAMTEST_END;

  iec60730_Post();

  // Init imcTest
  iec60730_ImcInit(&imcTest);

  // Init vmcTest
  iec60730_VmcInit(&vmcTest);

  LABEL_DEF(IEC60730_TEST_RESTART_WDOG_BKPT);
  while (1) {
    iec60730_programmeCounterCheck |=
        IEC60730_GPIO_COMPLETE | IEC60730_ANALOG_COMPLETE
        | IEC60730_COMMS_COMPLETE | IEC60730_OEM0_COMPLETE
        | IEC60730_OEM1_COMPLETE | IEC60730_OEM2_COMPLETE
        | IEC60730_OEM3_COMPLETE | IEC60730_OEM4_COMPLETE
        | IEC60730_OEM5_COMPLETE | IEC60730_OEM6_COMPLETE
        | IEC60730_OEM7_COMPLETE;

    if (wdog_restart_en) {
      iec60730_Bist();
    }
  }
  integration_test_deinit();
}
