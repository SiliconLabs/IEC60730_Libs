/***************************************************************************//**
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

#ifndef APP_H
#define APP_H

#include "unit_test_common.h"

#ifdef UNIT_TEST_IEC60730_POST_ENABLE
#include "unit_test_iec60730_post.h"
#endif

#ifdef UNIT_TEST_IEC60730_BIST_ENABLE
#include "unit_test_iec60730_bist.h"
#endif

#ifdef UNIT_TEST_IEC60730_PROGRAM_COUNTER_ENABLE
#include "unit_test_iec60730_program_counter.h"
#endif

#ifdef UNIT_TEST_IEC60730_SAFETY_CHECK_ENABLE
#include "unit_test_iec60730_safety_check.h"
#endif

#ifdef UNIT_TEST_IEC60730_IRQ_ENABLE
#include "unit_test_iec60730_irq.h"
#endif

#ifdef UNIT_TEST_IEC60730_SYSTEM_CLOCK_ENABLE
#include "unit_test_iec60730_system_clock.h"
#endif

#ifdef UNIT_TEST_IEC60730_WATCHDOG_ENABLE
#include "unit_test_iec60730_watchdog.h"
#endif

/***************************************************************************//**
 * Initialize application.
 ******************************************************************************/
void app_init(void);

/***************************************************************************//**
 * App ticking function.
 ******************************************************************************/
void app_process_action(void);

#endif  // APP_H
