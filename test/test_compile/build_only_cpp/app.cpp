/***************************************************************************/ /**
 * @file
 * @brief Top level application functions
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/
#include "iec60730_internal.h"

const uint8_t iec60730_IRQFreqBoundsSize                      = 2;
const iec60730_IRQExecutionBounds_t iec60730_IRQFreqBounds[2] = {1, 2};
uint8_t iec60730_IRQExecCount[2];
imcParams_t imcTest;
vmcParams_t vmcTest;

void iec60730_SafeState(iec60730_TestFailure_t failure)
{
  (void) failure;
}

void iec60730_TimersInit(void) {}

/***************************************************************************/ /**
 * Initialize application.
 ******************************************************************************/
void app_init(void) {}

/***************************************************************************/ /**
 * App ticking function.
 ******************************************************************************/
void app_process_action(void)
{
  iec60730_Bist();
  iec60730_Post();
  iec60730_RestartWatchdogs();
  iec60730_SystemClockTick();
  iec60730_TestClockTick();
  iec60730_clockTicksReset();
  iec60730_ImcInit(NULL);
  iec60730_VmcInit(NULL);
  iec60730_ImcPost(NULL);
  iec60730_ImcBist(NULL);
  iec60730_VmcPost(NULL);
  iec60730_VmcBist(NULL);
  iec60730_WatchdogPost();
  iec60730_IRQCheck();
  iec60730_programmeCounterTest();
}
