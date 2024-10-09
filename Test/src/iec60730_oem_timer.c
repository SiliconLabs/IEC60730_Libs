/***************************************************************************//**
 * @file iec60730_oem_timer.c
 * @brief Oem timer used for test
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
#include "iec60730_internal.h"
#include "em_timer.h"
#include "em_letimer.h"
#include "iec60730_oem_timer.h"

const TIMER_Init_TypeDef Timer_10ms_cfg = TIMER_INIT_TEST_10MS;
const LETIMER_Init_TypeDef Timer_100ms_cfg = TIMER_INIT_TEST_100MS;

/* Init test timers */
void TestTimer_Init(void)
{
  /* Initialze 10ms timer */
  TIMER_Init(TEST_Timer_10ms, &Timer_10ms_cfg);
  /* Initialze 10ms timer */
  LETIMER_Init(TEST_Timer_100ms, &Timer_100ms_cfg);
  
  /* Reset counter */
  TIMER_CounterSet(TEST_Timer_10ms, TEST_TIMER_RESET_VAL);
  LETIMER_CounterSet(TEST_Timer_100ms, TEST_TIMER_PRESET_VAL);
  
  /* Set reload value */
  TIMER_TopSet(TEST_Timer_10ms, TEST_TIMER_10MS_VAL);
  LETIMER_TopSet(TEST_Timer_100ms, TEST_TIMER_100MS_VAL);
  
  /* Clear pending interrupt */
  TIMER_IntClear(TEST_Timer_10ms, TIMER_IF_OF);
  LETIMER_IntClear(TEST_Timer_100ms, LETIMER_IF_UF);
  
  /* Enable overflow interrupt */
  TIMER_IntEnable(TEST_Timer_10ms, TIMER_IF_OF);
  LETIMER_IntEnable(TEST_Timer_100ms, LETIMER_IEN_UF);
}

/* De-Init timers */
void TestTimer_DeInit(void)
{
  TIMER_Reset(TEST_Timer_10ms);
  LETIMER_Reset(TEST_Timer_100ms);
}

void TestTimer_Enable(void)
{
  /* Start timer */
  TIMER_Enable(TEST_Timer_10ms, true);
  LETIMER_Enable(TEST_Timer_100ms, true);
}

/* 10ms timer interrupt handler */
void TIMER0_IRQHandler(void)
{
  TIMER_IntClear(TEST_Timer_10ms, TIMER_IF_OF);
  #if defined(TEST_TIMER_EN)
  iec60730_SystemClockTick();
  #endif
  #if defined(TEST_IRQ_EN) || defined(TEST_INTEGRATED_EN)
  Test_irq();
  #endif
}

/* 100ms timer interrupt handler */
void LETIMER0_IRQHandler(void)
{
  LETIMER_IntClear(TEST_Timer_100ms, LETIMER_IF_UF);
  #if defined(TEST_TIMER_EN)
  iec60730_TestClockTick();
  #endif
  #if defined(TEST_IRQ_EN)
  iec60730_IRQCheck();
  #endif
  #if defined(TEST_BIST_EN)
  iec60730_Bist();
  #endif
}

/* Init timers for clock test */
void iec60730_TimersInit(void)
{
#if defined(TEST_TIMER_EN) 
  TestTimer_Enable();
#endif
}