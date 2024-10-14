/***************************************************************************/ /**
 * @file iec60730_demo_micrium.c
 * @brief demo main function example micrium
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
#ifdef IEC60730_OS_PRESENT
#include "os.h"
#endif
#include "iec60730.h"
#include "iec60730_init_device.h"
#include "iec60730_oem_comm.h"
#include IEC_BOARD_HEADER

#ifndef IEC60730_TASK_STACK_SIZE
#define IEC60730_TASK_STACK_SIZE 256
#endif

#ifndef IEC60730_TASK_PRIO
#define IEC60730_TASK_PRIO 20
#endif

#ifndef COMM_TASK_STACK_SIZE
#define COMM_TASK_STACK_SIZE 256
#endif

#ifndef COMM_TASK_PRIO
#define COMM_TASK_PRIO 20
#endif

static OS_TCB iec60730_tcb;
static OS_TCB comm_tcb;
static CPU_STK iec60730_stack[IEC60730_TASK_STACK_SIZE];
static CPU_STK comm_stack[COMM_TASK_STACK_SIZE];

__no_init imcParams_t imcTest __CLASSB_RAM;
__no_init vmcParams_t vmcTest __CLASSB_RAM;

volatile uint32_t err_test = 0;

// Global variables used for IRQ check
SI_SEGMENT_CONST(iec60730_IRQFreqBoundsSize, uint8_t, SI_SEG_CODE) = 1;
SI_SEGMENT_VARIABLE(iec60730_IRQExecCount[IEC60730_IRQ_SIZE],
                    uint8_t,
                    SI_SEG_DATA)                                   = {0};
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

/**************************************************************************/ /**
 * @brief BIST task
 *
 * return void
 *
 *****************************************************************************/
void iec60730_task(void *arg)
{
  RTOS_ERR err;
  (void) &arg;

  while (1) {
    // Task executed every 10ms
    OSTimeDlyHMSM(0, 0, 0, 10, OS_OPT_TIME_TIMEOUT, &err);
    EFM_ASSERT((RTOS_ERR_CODE_GET(err) == RTOS_ERR_NONE));
    // System check taskss
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
    iec60730_Bist();
  }
}

/**************************************************************************/ /**
 * @brief Communication task
 *
 * return void
 *
 *****************************************************************************/
void app_comm_task(void *arg)
{
  RTOS_ERR err;
  (void) &arg;

  while (1) {
    // Task executed every 500ms
    OSTimeDlyHMSM(0, 0, 0, 500, OS_OPT_TIME_TIMEOUT, &err);
    EFM_ASSERT((RTOS_ERR_CODE_GET(err) == RTOS_ERR_NONE));
    iec60730_commTransmitStatusMessage();
  }
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
  RTOS_ERR err;

  iec60730_ImcInit(&imcTest);

  iec60730_VmcInit(&vmcTest);

  // Reset clock tick counter
  iec60730_clockTicksReset();

  // Create IEC60730 Task
  OSTaskCreate(&iec60730_tcb,
               "IEC60730 task",
               iec60730_task,
               DEF_NULL,
               IEC60730_TASK_PRIO,
               &iec60730_stack[0],
               (IEC60730_TASK_STACK_SIZE / 10u),
               IEC60730_TASK_STACK_SIZE,
               0u,
               0u,
               DEF_NULL,
               (OS_OPT_TASK_STK_CLR),
               &err);
  EFM_ASSERT((RTOS_ERR_CODE_GET(err) == RTOS_ERR_NONE));
}

/**************************************************************************/ /**
 * @brief Initialize communication task
 *
 * return void
 *
 *****************************************************************************/
void app_comm_Init(void)
{
  RTOS_ERR err;

  OSTaskCreate(&comm_tcb,
               "App comm task",
               app_comm_task,
               DEF_NULL,
               COMM_TASK_PRIO,
               &comm_stack[0],
               (COMM_TASK_STACK_SIZE / 10u),
               COMM_TASK_STACK_SIZE,
               0u,
               0u,
               DEF_NULL,
               (OS_OPT_TASK_STK_CLR),
               &err);
  EFM_ASSERT((RTOS_ERR_CODE_GET(err) == RTOS_ERR_NONE));
}
