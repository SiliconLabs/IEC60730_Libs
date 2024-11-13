/***************************************************************************/ /**
 * @file Test_programme_counter.c
 * @brief Program counter test cases
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
#include "integration_test_common.h"

// Dump functions
__WEAK sl_iec60730_test_result_t sl_iec60730_vmc_bist(void)
{
  return IEC60730_TEST_PASSED;
}

__WEAK sl_iec60730_test_result_t sl_iec60730_imc_bist(void)
{
  return IEC60730_TEST_PASSED;
}

__WEAK sl_iec60730_test_result_t sl_iec60730_cpu_registers_bist(void)
{
  return IEC60730_TEST_PASSED;
}

__WEAK sl_iec60730_test_result_t sl_iec60730_vmc_post()
{
  return IEC60730_TEST_PASSED;
}

__WEAK sl_iec60730_test_result_t sl_iec60730_imc_post()
{
  return IEC60730_TEST_PASSED;
}

__WEAK sl_iec60730_test_result_t sl_iec60730_watchdog_post(void)
{
  return IEC60730_TEST_PASSED;
}

__WEAK sl_iec60730_test_result_t sl_ec60730_cpu_registers_post(void)
{
  return IEC60730_TEST_PASSED;
}

void integration_test_run(void)
{
  integration_test_init();
}
