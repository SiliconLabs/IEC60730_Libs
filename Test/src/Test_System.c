/***************************************************************************//**
 * @file Test_System.c
 * @brief System init for test
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
#include "iec60730.h"
#include "iec60730_oem_timer.h"
#include "iec60730_watchdog.h"

/* Global Variables */
#if !defined(TEST_BIST_EN)
// SI_SEGMENT_VARIABLE(iec60730_SafetyCheck, iec60730_TestFailure_t, SI_SEG_DATA_NO_CLEAR);
#endif

// Watchdog settings
#ifdef TEST_WDOG_EN
const WDOG_Init_TypeDef wdog_init = WDOG_INIT_DEFAULT;
#endif

/* Function Prototype */
// void Nvic_Init(void);
void Clock_Config(void);

/* Function Definition */
void Test_Init(void)
{
  Clock_Config();
  // Nvic_Init();
#ifdef TEST_WDOG_EN
	WDOGn_Init(TEST_WDOG_INST0, &wdog_init);
  #ifdef IEC60730_ENABLE_WDOG1
  WDOGn_Init(TEST_WDOG_INST1, &wdog_init);
  #endif
#endif
  
#if defined(TEST_TIMER_EN) || defined(TEST_IRQ_EN) || defined(TEST_INTEGRATED_EN)
  TestTimer_Init();
#endif

  CORE_ATOMIC_IRQ_ENABLE();
}

void Test_DeInit(void)
{
  /* Disable watchdog timer */
#ifdef TEST_WDOG_EN
	WDOGn_Enable(TEST_WDOG_INST0, TEST_DISABLE);
  #ifdef IEC60730_ENABLE_WDOG1
  WDOGn_Enable(TEST_WDOG_INST1, TEST_DISABLE);
  #endif
#endif
  
#if defined(TEST_TIMER_EN) || defined(TEST_IRQ_EN) || defined(TEST_INTEGRATED_EN)
  TestTimer_DeInit();
#endif
}

void SW0_IRQHandler(void)
{
  while(1);
}

iec60730_TestFailure_t currFailure = iec60730_NoFailure;

/* IEC60730 safe state */
void iec60730_SafeState(iec60730_TestFailure_t failure)
{
  // (void)failure;
  currFailure = failure;
  LABEL_DEF(IEC60730_SAFE_STATE_BKPT);
  // IEC60730_RSTCAUSES_CLEAR();
  while(true){
    #ifdef TEST_WDOG_EN
    WDOGn_Feed(TEST_WDOG_INST0);
    #ifdef IEC60730_ENABLE_WDOG1
    WDOGn_Feed(TEST_WDOG_INST1);
    #endif
    #endif
  }
}

/* Clock configuration */
void Clock_Config(void)
{
  #if (_SILICON_LABS_32B_SERIES_2_CONFIG >= 1)
  /* System clock is default FSRCO - 20Mhz */
  /* Watchdog and LETIMER clock is default LFRCO - 32Khz */
  /* FSRCO clocks for timers at fixed 20Mhz */
  CMU_ClockSelectSet(cmuClock_TIMER0, cmuSelect_FSRCO);
 
  CMU_ClockSelectSet(cmuClock_LETIMER0, cmuSelect_LFRCO);
  
  #if (_SILICON_LABS_32B_SERIES_2_CONFIG > 1)
  CMU_ClockEnable(cmuClock_TIMER0, true);
  CMU_ClockEnable(cmuClock_LETIMER0, true);
  CMU_ClockEnable(cmuClock_WDOG0, true);
  CMU_ClockEnable(cmuClock_WDOG1, true);
  CMU_ClockEnable(cmuClock_GPCRC, true);
  CMU_ClockEnable(cmuClock_BURAM, true);
  CMU_ClockEnable(cmuClock_FSRCO, true);
  CMU_ClockEnable(cmuClock_LFRCO, true);
  #endif
  #else
  /* System clock is default HFRCO - 19Mhz */
  /* Watchdog clock is default LFRCO - 32Khz */
  /* FSRCO clocks for timers at 19Mhz */
  CMU_ClockEnable(cmuClock_HFPER, true);
  CMU_ClockEnable(cmuClock_TIMER0, true);
  /* Enable Low energy Peripherals clock */
  #if defined(CMU_HFCORECLKEN0_LE)
  CMU_ClockEnable(cmuClock_HFLE, true);
  #else
  CMU->HFBUSCLKEN0 |= (CMU_HFBUSCLKEN0_LE & _CMU_HFBUSCLKEN0_MASK);
  #endif
  
  /* LFACLK clock is selected as LFRCO */
  CMU_ClockSelectSet(cmuClock_LFA, cmuSelect_LFRCO);
  /* Enable clock for LETIMER0 as LFRCO - 32.768 kHz*/
  CMU_ClockEnable(cmuClock_LETIMER0, true);
  /* Enable clock of CRC */
  CMU_ClockEnable(cmuClock_GPCRC, true);
  #endif
}

__WEAK void iec60730_IRQCheck(void)
{
	
}

__WEAK iec60730_TestResult_t iec60730_WatchdogPost(void)
{
	return iec60730_TestPassed;
}
