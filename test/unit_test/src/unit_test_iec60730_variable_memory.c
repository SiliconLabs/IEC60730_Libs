/***************************************************************************//**
 * @file  unit_test_iec60730_variable_memory.c
 * @brief Unit tests for functions in variable memory module
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

#include "unit_test_common.h"
#include "unit_test_iec60730_variable_memory.h"
#include "sl_iec60730_internal.h"

/*=======Mock Code=====*/
uint16_t sl_iec60730_program_counter_check;
__no_init sl_iec60730_vmc_params_t unit_test_vmc;
bool vmc_marchc_step_check_ram_section;
bool vmc_marchc_step_check_backup_section;
bool check_integrity_result;
bool iec60730_vmc_pre_run_marchxc_step_flag;
bool run_test_sl_iec60730_vmc_bist_allow;

bool unit_test_mock_check_integrity(void) {
  return check_integrity_result;
}

__WEAK bool sl_iec60730_vmc_marchc_step(uint32_t *start,
                            uint32_t *end,
                            uint32_t background,
                            uint32_t *backup) {
  (void)background;
  (void)end;
  if(start == backup) {
    cmock_set_value(vmc_marchc_step_check_backup_section);
    if(!check_integrity_result) {
      cmock_set_value(unit_test_mock_check_integrity());
    }
  } else {
    cmock_set_value(vmc_marchc_step_check_ram_section);
    if(!check_integrity_result) {
      cmock_set_value(unit_test_mock_check_integrity());
    }
  }
  return cmock_return_value();
}

__WEAK bool sl_iec60730_vmc_marchxc_step(uint32_t *start,
                            uint32_t *end,
                            uint32_t background,
                            uint32_t *backup) {
  (void)background;
  (void)end;
  if(start == backup) {
    cmock_set_value(vmc_marchc_step_check_backup_section);
    if(!check_integrity_result) {
      cmock_set_value(unit_test_mock_check_integrity());
    }
  } else {
    run_test_sl_iec60730_vmc_bist_allow = true;
    cmock_set_value(vmc_marchc_step_check_ram_section);
    if(!check_integrity_result) {
      cmock_set_value(unit_test_mock_check_integrity());
    }
  }
  return cmock_return_value();
}

bool sl_iec60730_vmc_pre_run_marchxc_step(uint32_t *addr, uint32_t size)
{
  UNUSED_VAR(addr);
  UNUSED_VAR(size);
  return iec60730_vmc_pre_run_marchxc_step_flag;
}

void set_up_test_vmc_post_and_bist(void) {
  unit_test_vmc.start = RAMTEST_START;
  unit_test_vmc.end   = RAMTEST_END;
  vmc_marchc_step_check_ram_section = true;
  vmc_marchc_step_check_backup_section = true;
  check_integrity_result = true;
  iec60730_vmc_pre_run_marchxc_step_flag = true;
  run_test_sl_iec60730_vmc_bist_allow = false;
  sl_iec60730_vmc_init(&unit_test_vmc);
}

/*=======Test Case=====*/
void test_sl_iec60730_vmc_init_param_null(void) {
  /*Setup*/
  sl_iec60730_test_result_t result = IEC60730_TEST_FAILED;
  unit_test_vmc.start = NULL;
  /*Execute test*/
  sl_iec60730_vmc_init(&unit_test_vmc);
  result = sl_iec60730_vmc_post();
  TEST_ASSERT_EQUAL(IEC60730_TEST_FAILED, result);
}

void test_sl_iec60730_vmc_init_start_address_greater_than_end_address(void) {
  /*Setup*/
  sl_iec60730_test_result_t result = IEC60730_TEST_FAILED;
  unit_test_vmc.start = RAMTEST_END;
  unit_test_vmc.end   = RAMTEST_START;
  /*Execute test*/
  sl_iec60730_vmc_init(&unit_test_vmc);
  result = sl_iec60730_vmc_post();
  TEST_ASSERT_EQUAL(IEC60730_TEST_FAILED, result);
}

void test_sl_iec60730_vmc_post_pass_all_check_sections(void) {
  /*Setup*/
  sl_iec60730_test_result_t result = IEC60730_TEST_FAILED;
  set_up_test_vmc_post_and_bist();
  /*Execute test*/
  result = sl_iec60730_vmc_post();
  TEST_ASSERT_EQUAL(IEC60730_TEST_PASSED, result);
}

void test_sl_iec60730_vmc_post_fail_marchc_check_ram_section(void) {
  /*Setup*/
  sl_iec60730_test_result_t result = IEC60730_TEST_FAILED;
  set_up_test_vmc_post_and_bist();
  vmc_marchc_step_check_ram_section = false;
  /*Execute test*/
  result = sl_iec60730_vmc_post();
  TEST_ASSERT_EQUAL(IEC60730_TEST_FAILED, result);
}

void test_sl_iec60730_vmc_post_fail_marchc_check_backup_section(void) {
  /*Setup*/
  sl_iec60730_test_result_t result = IEC60730_TEST_FAILED;
  set_up_test_vmc_post_and_bist();
  vmc_marchc_step_check_backup_section = false;
  /*Execute test*/
  result = sl_iec60730_vmc_post();
  TEST_ASSERT_EQUAL(IEC60730_TEST_FAILED, result);
}

void test_sl_iec60730_vmc_post_fail_check_integrity_ram_section(void) {
  /*Setup*/
  sl_iec60730_test_result_t result = IEC60730_TEST_FAILED;
  set_up_test_vmc_post_and_bist();
  check_integrity_result = false;
  /*Execute test*/
  result = sl_iec60730_vmc_post();
  TEST_ASSERT_EQUAL(IEC60730_TEST_FAILED, result);
}

void test_sl_iec60730_vmc_post_fail_check_integrity_backup_section(void) {
  /*Setup*/
  sl_iec60730_test_result_t result = IEC60730_TEST_FAILED;
  set_up_test_vmc_post_and_bist();
  check_integrity_result = false;
  /*Execute test*/
  result = sl_iec60730_vmc_post();
  TEST_ASSERT_EQUAL(IEC60730_TEST_FAILED, result);
}

void test_sl_iec60730_vmc_bist_pass_all_check_sections(void) {
  /*Setup*/
  sl_iec60730_test_result_t result = IEC60730_TEST_FAILED;
  set_up_test_vmc_post_and_bist();
  /*Execute test*/
  result = sl_iec60730_vmc_bist();
  TEST_ASSERT_EQUAL(IEC60730_TEST_PASSED, result);
}

void test_sl_iec60730_vmc_bist_fail_marchxc_check_ram_section(void) {
  /*Setup*/
  sl_iec60730_test_result_t result = IEC60730_TEST_FAILED;
  set_up_test_vmc_post_and_bist();
  vmc_marchc_step_check_ram_section = false;
  /*Execute test*/
  result = sl_iec60730_vmc_bist();
  TEST_ASSERT_EQUAL(IEC60730_TEST_FAILED, result);
}

void test_sl_iec60730_vmc_bist_fail_marchxc_check_backup_section(void) {
  /*Setup*/
  sl_iec60730_test_result_t result = IEC60730_TEST_FAILED;
  set_up_test_vmc_post_and_bist();
  vmc_marchc_step_check_backup_section = false;
  /*Execute test*/
  result = sl_iec60730_vmc_bist();
  TEST_ASSERT_EQUAL(IEC60730_TEST_FAILED, result);
}

void test_sl_iec60730_vmc_bist_fail_check_integrity_ram_section(void) {
  /*Setup*/
  sl_iec60730_test_result_t result = IEC60730_TEST_FAILED;
  set_up_test_vmc_post_and_bist();
  check_integrity_result = false;
  /*Execute test*/
  result = sl_iec60730_vmc_bist();
  TEST_ASSERT_EQUAL(IEC60730_TEST_FAILED, result);
}

void test_sl_iec60730_vmc_bist_fail_check_integrity_backup_section(void) {
  /*Setup*/
  sl_iec60730_test_result_t result = IEC60730_TEST_FAILED;
  set_up_test_vmc_post_and_bist();
  check_integrity_result = false;
  /*Execute test*/
  result = sl_iec60730_vmc_bist();
  TEST_ASSERT_EQUAL(IEC60730_TEST_FAILED, result);
}

void test_sl_iec60730_vmc_bist_checking_allow_run_test(void) {
  /*Setup*/
  set_up_test_vmc_post_and_bist();
  iec60730_vmc_pre_run_marchxc_step_flag = false;
  /*Execute test*/
  sl_iec60730_vmc_bist();
  TEST_ASSERT_EQUAL(false, run_test_sl_iec60730_vmc_bist_allow);
}

void test_sl_iec60730_vmc_bist_fail_stack_test_over_flow(void) {
  /*Setup*/
  sl_iec60730_test_result_t result = IEC60730_TEST_FAILED;
  set_up_test_vmc_post_and_bist();
  uint32_t *stack_start = STACK_CHECK;
  /*Execute test*/
  *stack_start = SL_STACK_OVERFLOW_CONST_GUARD_VALUE_3;
  result = sl_iec60730_vmc_bist();
  TEST_ASSERT_EQUAL(IEC60730_TEST_FAILED, result);
}

/*=======Run Test Case=====*/

void unit_test_run_all_test_cases(void)
{
  // Initialize
  memset((void *)test_case_result, 0xff, sizeof(test_case_result));
  current_test_numth = 0;

  // Start run test
  printf("--- BEGIN UNIT TEST ---\n");
  UnityBegin("/unit_test/src/unit_test_iec60730_variable_memory.c");
  run_test(test_sl_iec60730_vmc_init_param_null,"test_sl_iec60730_vmc_init_param_null",95);
  run_test(test_sl_iec60730_vmc_init_start_address_greater_than_end_address,"test_sl_iec60730_vmc_init_start_address_greater_than_end_address",105);
  run_test(test_sl_iec60730_vmc_post_pass_all_check_sections,"test_sl_iec60730_vmc_post_pass_all_check_sections",116);
  run_test(test_sl_iec60730_vmc_post_fail_marchc_check_ram_section,"test_sl_iec60730_vmc_post_fail_marchc_check_ram_section",125);
  run_test(test_sl_iec60730_vmc_post_fail_marchc_check_backup_section,"test_sl_iec60730_vmc_post_fail_marchc_check_backup_section",135);
  run_test(test_sl_iec60730_vmc_post_fail_check_integrity_ram_section,"test_sl_iec60730_vmc_post_fail_check_integrity_ram_section",145);
  run_test(test_sl_iec60730_vmc_post_fail_check_integrity_backup_section,"test_sl_iec60730_vmc_post_fail_check_integrity_backup_section",155);
  run_test(test_sl_iec60730_vmc_bist_pass_all_check_sections,"test_sl_iec60730_vmc_bist_pass_all_check_sections",165);
  run_test(test_sl_iec60730_vmc_bist_fail_marchxc_check_ram_section,"test_sl_iec60730_vmc_bist_fail_marchxc_check_ram_section",174);
  run_test(test_sl_iec60730_vmc_bist_fail_marchxc_check_backup_section,"test_sl_iec60730_vmc_bist_fail_marchxc_check_backup_section",184);
  run_test(test_sl_iec60730_vmc_bist_fail_check_integrity_ram_section,"test_sl_iec60730_vmc_bist_fail_check_integrity_ram_section",194);
  run_test(test_sl_iec60730_vmc_bist_fail_check_integrity_backup_section,"test_sl_iec60730_vmc_bist_fail_check_integrity_backup_section",204);
  run_test(test_sl_iec60730_vmc_bist_checking_allow_run_test,"test_sl_iec60730_vmc_bist_checking_allow_run_test",214);
  run_test(test_sl_iec60730_vmc_bist_fail_stack_test_over_flow,"test_sl_iec60730_vmc_bist_fail_stack_test_over_flow",223);
  UnityEnd();
  __asm volatile("IEC60730_UNIT_TEST_END:");

  while(1){
    // Do nothing
  }
}