/***************************************************************************/ /**
 * @file    sl_iec60730_program_counter.h
 * @brief Program Counter check
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef SL_IEC60730_PROGRAMME_COUNTER_H
#define SL_IEC60730_PROGRAMME_COUNTER_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "sl_iec60730_internal.h"

/**************************************************************************/ /**
 * @addtogroup efr32_iec60730
 * @{
 * @addtogroup IEC60730_PROGRAM_COUNTER
 * @{
 * @details
 * The frequency of test execution must be checked to ensure that tests
 * are being run in time.
 *
 * @section programme_counter_hardware_architecture Hardware Architecture
 * The programme counter check requires that each BIST test set a bit in a
 * bit array whenever an iteration of testing completes.
 * The programme counter check uses the test clock timer configured
 * in the system clock plausibility test to determine when to execute.  See
 * @ref IEC60730_SYSTEM_CLOCK_Test for system clock plausibility details.
 * The programme counter test executes at 1/10 the frequency of the system clock
 * plausibility test.  Best practice recommendations and example OEM code
 * configure the system clock plausibility test to run at 100 ms intervals,
 * resulting in BIST frequency check intervals of 1s.
 *
 * Bits within #sl_iec60730_program_counter_check are set as tests pass. OEMs can determine
 * how fast their tests are running by checking this variable. If a bit is still
 * clear, that test has not completed.
 *
 * @section programme_counter_suggested_OEM_configuration Suggested OEM Configuration
 * OEM configuration of this test is dependent on system clock plausibility
 * configuration.  Please see @ref IEC60730_SYSTEM_CLOCK_Test for details.
 *
 * @section programme_counter_failure_risks Failure Risks
 * The library's BIST execution frequency test will force entry into
 * safe state if a period of time defined by 1/10 test clock test frequency
 * passes without all BIST tests completing their test execution.  It is
 * the OEM's responsibility to call the BIST in the main() loop with enough
 * frequency to execute all tests within the required time period.
 *
 * If the system clock test's test timer is not configured as expected, so that
 * 1/10 test clock frequency is unexpectedly fast, the system may fall into safe state
 * because tests have not had enough time to execute to completion.
 *
 * @section programme_counter_software_architecture Software Architecture
 *
 * For the IEC60730 implementation, \link programme_counter_check Figure 1\endlink
 *
 * \image html programme_counter_check.png "Figure 1 Programme Counter Check Flowchart" \anchor programme_counter_check
 *
 *****************************************************************************/

/// private IEC60730 Programme Counter Test
///
/// Checks flags in #sl_iec60730_program_counter_check set by each BIST test to determine if BIST is
/// executing within a specified period.
/// @return #sl_iec60730_test_result_t. If test fails, returns #SL_IEC60730_TEST_FAILED;
/// otherwise #SL_IEC60730_TEST_PASSED.
void sl_iec60730_program_counter_test(void);

/** @} (end addtogroup IEC60730_PROGRAMME_COUNTER) */
/** @} (end addtogroup efr32_iec60730) */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* SL_IEC60730_PROGRAMME_COUNTER_H */
