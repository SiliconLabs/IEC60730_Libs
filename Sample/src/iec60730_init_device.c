/**************************************************************************//**
 * Copyright (c) 2021 by Silicon Laboratories Inc. All rights reserved.
 *
 * http://developer.silabs.com/legal/version/v11/Silicon_Labs_Software_License_Agreement.txt
 *****************************************************************************/

#include "em_cmu.h"
#include "em_wdog.h"
#include "iec60730_internal.h"
#include "iec60730_init_device.h"
#include "iec60730_oem_timer.h"
#include "iec60730_oem_comm.h"

// Wdg config
const WDOG_Init_TypeDef wdog_init = WDOG_INIT_DEFAULT;
const WDOG_Init_TypeDef wdog1_init = WDOG_INIT_DEFAULT;
// HFXO config
const CMU_HFXOInit_TypeDef hfxo_init = CMU_HFXOINIT_DEFAULT;
#if (_SILICON_LABS_32B_SERIES_2_CONFIG >= 1)
// DPLL configured default 80Mhz
const CMU_DPLLInit_TypeDef dpll_init = CMU_DPLLINIT_DEFAULT;
#endif

static void Clock_Config(void);
static void Nvic_Init(void);

void System_Config(void) {
  Clock_Config();
  Nvic_Init();
  iec60730_Timers_Init();
  iec60730_commInit();
  WDOGn_Init(TEST_WDOG_INST, &wdog_init);
#ifdef IEC60730_ENABLE_WDOG1
  WDOGn_Init(IEC60730_WDOG_INST(1), &wdog1_init);
#endif

  CORE_ATOMIC_IRQ_ENABLE();
}

void Clock_Config(void) {
#if (_SILICON_LABS_32B_SERIES_2_CONFIG >= 1)
  #ifndef IEC60730_OS_PRESENT
  #if (_SILICON_LABS_32B_SERIES_2_CONFIG > 1)
  CMU_ClockEnable(cmuClock_HFXO, true);
  CMU_ClockEnable(cmuClock_DPLL0, true);
  #endif
  
  /* Enable HFXO */
  CMU_HFXOInit(&hfxo_init);
  CMU_OscillatorEnable(cmuOsc_HFXO, true, true);
  /* Configure DPLL */
  // CMU_HFRCODPLLBandSet(cmuHFRCODPLLFreq_80M0Hz);
  if(!CMU_DPLLLock(&dpll_init)) {
      while(1);
  }

  #if (_SILICON_LABS_32B_SERIES_2_CONFIG > 1)
  /* System clock is DPLL - 80Mhz */
  // CMU_ClockSelectSet(cmuClock_SYSCLK, cmuSelect_HFRCODPLLRT);
  // CMU_ClockSelectSet(cmuClock_TIMER0, cmuSelect_HFRCODPLLRT);
  CMU_ClockSelectSet(cmuClock_SYSCLK, cmuSelect_HFRCODPLL);
  CMU_ClockSelectSet(cmuClock_TIMER0, cmuSelect_HFRCODPLL);
  /* Watchdog and LETIMER clock is default LFRCO - 32Khz */
  
  CMU_ClockEnable(cmuClock_TIMER0, true);
  CMU_ClockEnable(cmuClock_LETIMER0, true);
  CMU_ClockEnable(cmuClock_WDOG0, true);
  CMU_ClockEnable(cmuClock_WDOG1, true);
  CMU_ClockEnable(cmuClock_GPCRC, true);
  CMU_ClockEnable(cmuClock_BURAM, true);
  #else
  /* System clock is DPLL - 80Mhz */
  CMU_ClockSelectSet(cmuClock_SYSCLK, cmuSelect_HFRCODPLL);
  CMU_ClockSelectSet(cmuClock_TIMER0, cmuSelect_HFRCODPLL);
  /* Watchdog and LETIMER clock is default LFRCO - 32Khz */
  #endif
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

void Nvic_Init(void) {
  /* One Group Priority */
#ifndef IEC60730_OS_PRESENT
  NVIC_SetPriorityGrouping(7);
#endif
  /* Timer 0 */
  NVIC_SetPriority(TIMER0_IRQn, 1);
  NVIC_EnableIRQ(TIMER0_IRQn);

  /* LETIMER 0 */
  NVIC_SetPriority(LETIMER0_IRQn, 1);
  NVIC_EnableIRQ(LETIMER0_IRQn);
}
