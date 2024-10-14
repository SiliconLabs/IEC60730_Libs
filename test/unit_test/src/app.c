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

#include "app.h"

void app_init(void)
{

#ifdef UNIT_TEST_IEC60730_POST_ENABLE
  unit_test_iec60730_post();
#endif

#ifdef UNIT_TEST_IEC60730_BIST_ENABLE
  unit_test_iec60730_bist();
#endif

#ifdef UNIT_TEST_IEC60730_PROGRAM_COUNTER_ENABLE
  unit_test_iec60730_program_counter();
#endif

#ifdef UNIT_TEST_IEC60730_SAFETY_CHECK_ENABLE
  unit_test_iec60730_safety_check();
#endif

#ifdef UNIT_TEST_IEC60730_IRQ_ENABLE
  unit_test_iec60730_irq();
#endif

#ifdef UNIT_TEST_IEC60730_SYSTEM_CLOCK_ENABLE
  unit_test_iec60730_system_clock();
#endif

#ifdef UNIT_TEST_IEC60730_WATCHDOG_ENABLE
  unit_test_iec60730_watchdog();
#endif

#ifdef UNIT_TEST_IEC60730_CPU_REGISTERS_ENABLE
  unit_test_iec60730_cpu_registers();
#endif

#ifdef UNIT_TEST_IEC60730_VARIABLE_MEMORY_ENABLE
  unit_test_iec60730_variable_memory();
#endif

}

void app_process_action(void)
{

}
