/***************************************************************************//**
 * @file  unit_test_iec60730_irq.c
 * @brief Unit tests for functions in irq module
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

#include <string.h>
#include "em_core.h"
#include "em_gpcrc.h"
#include "em_cmu.h"
#include "unit_test_common.h"
#include "unit_test_iec60730_invariable_memory.h"
#include "sl_iec60730_internal.h"

/*=======Mock Code=====*/
uint16_t sl_iec60730_program_counter_check;
__no_init sl_iec60730_imc_params_t unit_test_imc;

#if (SL_IEC60730_CRC_USE_SW_ENABLE == 0)
bool unit_test_gpcrc_enable;
#else
bool unit_test_sw_cal_crc_enable;
#endif // (SL_IEC60730_CRC_USE_SW_ENABLE == 0)
bool check_integrity_result;
uint32_t* unit_test_init_run_crc;

uint32_t* unit_test_iec60730_imc_mock_init_run_crc(void) {
  return unit_test_init_run_crc;
}

bool unit_test_mock_check_integrity(void) {
  return check_integrity_result;
}

void set_up_test_vmc_post_and_bist(void) {
  CMU_ClockEnable(cmuClock_GPCRC, true);
  unit_test_imc.gpcrc = SL_IEC60730_DEFAULT_GPRC;
  check_integrity_result = true;
  unit_test_init_run_crc = SL_IEC60730_ROM_START;
  #if (SL_IEC60730_CRC_USE_SW_ENABLE == 0)
  unit_test_gpcrc_enable = true;
  #else
  unit_test_sw_cal_crc_enable = true;
  #endif // (SL_IEC60730_CRC_USE_SW_ENABLE == 0)
  sl_iec60730_imc_init(&unit_test_imc);
}

#if (SL_IEC60730_CRC_USE_SW_ENABLE == 0)
bool unit_test_iec60730_imc_mock_enable_gpcrc(void) {
  return unit_test_gpcrc_enable;
}
#else
bool unit_test_iec60730_imc_mock_sw_enable_cal_crc(void) {
  return unit_test_sw_cal_crc_enable;
}
#endif // (SL_IEC60730_CRC_USE_SW_ENABLE == 0)

/*=======Test Case=====*/
void test_sl_iec60730_imc_init_param_null(void) {
  #if (SL_IEC60730_CRC_USE_SW_ENABLE == 0)
  /*Setup*/
  sl_iec60730_test_result_t result = IEC60730_TEST_FAILED;
  unit_test_imc.gpcrc = NULL;
  /*Execute test*/
  sl_iec60730_imc_init(NULL);
  result = sl_iec60730_imc_post();
  TEST_ASSERT_EQUAL(IEC60730_TEST_FAILED, result);
  #else
  TEST_ASSERT(true);
  #endif // (SL_IEC60730_CRC_USE_SW_ENABLE == 0)
}

void test_sl_iec60730_imc_post_pass_check(void) {
  /*Setup*/
  sl_iec60730_test_result_t result = IEC60730_TEST_FAILED;
  set_up_test_vmc_post_and_bist();
  /*Execute test*/
  result = sl_iec60730_imc_post();
  TEST_ASSERT_EQUAL(IEC60730_TEST_PASSED, result);
}

void test_sl_iec60730_imc_post_fail_check(void) {
  /*Setup*/
  sl_iec60730_test_result_t result = IEC60730_TEST_FAILED;
  set_up_test_vmc_post_and_bist();
  #if (SL_IEC60730_CRC_USE_SW_ENABLE == 0)
  unit_test_gpcrc_enable = false;
  #else
  unit_test_sw_cal_crc_enable = false;
  #endif // (SL_IEC60730_CRC_USE_SW_ENABLE == 0)
  /*Execute test*/
  sl_iec60730_imc_init(&unit_test_imc);
  result = sl_iec60730_imc_post();
  TEST_ASSERT_EQUAL(IEC60730_TEST_FAILED, result);
}

void test_sl_iec60730_imc_bist_pass_all_check(void) {
  /*Setup*/
  sl_iec60730_test_result_t result = IEC60730_TEST_FAILED;
  set_up_test_vmc_post_and_bist();
  sl_iec60730_imc_post();
  /*Execute test*/
  result = sl_iec60730_imc_bist();
  TEST_ASSERT_EQUAL(IEC60730_TEST_PASSED, result);
}

void test_sl_iec60730_imc_bist_fail_check_integrity(void) {
  /*Setup*/
  sl_iec60730_test_result_t result = IEC60730_TEST_FAILED;
  set_up_test_vmc_post_and_bist();
  check_integrity_result = false;
  /*Execute test*/
  result = sl_iec60730_imc_bist();
  TEST_ASSERT_EQUAL(IEC60730_TEST_FAILED, result);
}

void test_sl_iec60730_imc_bist_iec60730_run_crc_greater_than_rom_end_address(void) {
  /*Setup*/
  sl_iec60730_test_result_t result = IEC60730_TEST_FAILED;
  set_up_test_vmc_post_and_bist();
  unit_test_init_run_crc = SL_IEC60730_ROM_END;
  sl_iec60730_imc_init(&unit_test_imc);
  /*Execute test*/
  result = sl_iec60730_imc_bist();
  TEST_ASSERT_EQUAL(IEC60730_TEST_FAILED, result);
}

void test_sl_iec60730_imc_bist_fail_compare_crc(void) {
  /*Setup*/
  sl_iec60730_test_result_t result = IEC60730_TEST_FAILED;
  set_up_test_vmc_post_and_bist();
  sl_iec60730_imc_post();
  set_up_test_vmc_post_and_bist();
  #if (SL_IEC60730_CRC_USE_SW_ENABLE == 0)
  unit_test_gpcrc_enable = false;
  sl_iec60730_imc_init(&unit_test_imc);
  #else
  sl_iec60730_imc_init(&unit_test_imc);
  unit_test_sw_cal_crc_enable = false;
  #endif // (SL_IEC60730_CRC_USE_SW_ENABLE == 0)
  /*Execute test*/
  result = sl_iec60730_imc_bist();
  TEST_ASSERT_EQUAL(IEC60730_TEST_FAILED, result);
}

void test_sl_iec60730_update_crc_with_data_buffer_params_null(void) {
  /*Setup*/
  sl_iec60730_test_result_t result = IEC60730_TEST_FAILED;
  set_up_test_vmc_post_and_bist();
  sl_iec60730_crc_t crc_value = (sl_iec60730_crc_t) SL_IEC60730_IMC_CRC_BUFFER_INIT_VALUE;
  /*Execute test*/
  result = sl_iec60730_update_crc_with_data_buffer(NULL,
                                          &crc_value,
                                          (uint8_t *)SL_IEC60730_IMC_CRC_BUFFER_SAMPLE_TEST,
                                          strlen(SL_IEC60730_IMC_CRC_BUFFER_SAMPLE_TEST));
  TEST_ASSERT_EQUAL(IEC60730_TEST_FAILED, result);
}

void test_sl_iec60730_update_crc_with_data_buffer_calculation_crc(void) {
  /*Setup*/
  sl_iec60730_test_result_t result = IEC60730_TEST_FAILED;
  set_up_test_vmc_post_and_bist();
  sl_iec60730_crc_t crc_value = (sl_iec60730_crc_t) SL_IEC60730_IMC_CRC_BUFFER_INIT_VALUE;
  sl_iec60730_update_crc_params_t update = SL_IEC60730_IMC_CRC_BUFFER_UPDATE_DEFAULT;
  /*Execute test*/
  result = sl_iec60730_update_crc_with_data_buffer(&update,
                                          &crc_value,
                                          (uint8_t *)SL_IEC60730_IMC_CRC_BUFFER_SAMPLE_TEST,
                                          (uint32_t)strlen(SL_IEC60730_IMC_CRC_BUFFER_SAMPLE_TEST));
  TEST_ASSERT_EQUAL(IEC60730_TEST_PASSED, result);

  #if (SL_IEC60730_CRC_USE_SW_ENABLE == 1)
  #if (SL_IEC60730_USE_CRC_32_ENABLE == 1)
  TEST_ASSERT_EQUAL(SL_IEC60730_IMC_CRC_BUFFER_SAMPLE_RESULT, crc_value);
  #else // (SL_IEC60730_USE_CRC_32_ENABLE != 1)
  TEST_ASSERT_EQUAL(SL_IEC60730_IMC_CRC_BUFFER_SAMPLE_RESULT, crc_value);
  #endif // (SL_IEC60730_USE_CRC_32_ENABLE == 1)
  #else  // (SL_IEC60730_CRC_USE_SW_ENABLE != 1)
  #if (SL_IEC60730_USE_CRC_32_ENABLE == 1)
  if (SL_IEC60730_IMC_DATA_READ == update.readType) {
    TEST_ASSERT_EQUAL(SL_IEC60730_IMC_CRC_BUFFER_SAMPLE_RESULT, crc_value);
  } else if (SL_IEC60730_IMC_DATA_READ_BIT_REVERSED == update.readType) {
    TEST_ASSERT_EQUAL(0x649C2FD3, crc_value);
  } else if (SL_IEC60730_IMC_DATA_READ_BYTE_REVERSED == update.readType) {
    TEST_ASSERT_EQUAL(0x2639F4CB, crc_value);
  } else {
    TEST_ASSERT_EQUAL(SL_IEC60730_IMC_CRC_BUFFER_INIT_VALUE, crc_value);
  }
  #else // (SL_IEC60730_USE_CRC_32_ENABLE != 1)
  if (SL_IEC60730_IMC_DATA_READ == update.readType) {
    TEST_ASSERT_EQUAL(0x8D94, crc_value);
  } else if (SL_IEC60730_IMC_DATA_READ_BIT_REVERSED == update.readType) {
    TEST_ASSERT_EQUAL(SL_IEC60730_IMC_CRC_BUFFER_SAMPLE_RESULT, crc_value);
  } else if (SL_IEC60730_IMC_DATA_READ_BYTE_REVERSED == update.readType) {
    TEST_ASSERT_EQUAL(0x948D, crc_value);
  } else {
    TEST_ASSERT_EQUAL(SL_IEC60730_IMC_CRC_BUFFER_INIT_VALUE, crc_value);
  }
  #endif // (SL_IEC60730_USE_CRC_32_ENABLE == 1)
  #endif // (SL_IEC60730_CRC_USE_SW_ENABLE == 1)
}

/*=======Run Test Case=====*/

void unit_test_run_all_test_cases(void)
{
  // Initialize
  memset((void *)test_case_result, 0xff, sizeof(test_case_result));
  current_test_numth = 0;

  // Start run test
  printf("--- BEGIN UNIT TEST ---\n");
  UnityBegin("/unit_test/src/unit_test_iec60730_invariable_memory.c");
  run_test(test_sl_iec60730_imc_init_param_null,"test_sl_iec60730_imc_init_param_null",70);
  run_test(test_sl_iec60730_imc_post_pass_check,"test_sl_iec60730_imc_post_pass_check",84);
  run_test(test_sl_iec60730_imc_post_fail_check,"test_sl_iec60730_imc_post_fail_check",93);
  run_test(test_sl_iec60730_imc_bist_pass_all_check,"test_sl_iec60730_imc_bist_pass_all_check",108);
  run_test(test_sl_iec60730_imc_bist_fail_check_integrity,"test_sl_iec60730_imc_bist_fail_check_integrity",118);
  run_test(test_sl_iec60730_imc_bist_iec60730_run_crc_greater_than_rom_end_address,"test_sl_iec60730_imc_bist_iec60730_run_crc_greater_than_rom_end_address",128);
  run_test(test_sl_iec60730_imc_bist_fail_compare_crc,"test_sl_iec60730_imc_bist_fail_compare_crc",139);
  run_test(test_sl_iec60730_update_crc_with_data_buffer_params_null,"test_sl_iec60730_update_crc_with_data_buffer_params_null",157);
  run_test(test_sl_iec60730_update_crc_with_data_buffer_calculation_crc,"test_sl_iec60730_update_crc_with_data_buffer_calculation_crc",170);
  UnityEnd();
  __asm volatile("IEC60730_UNIT_TEST_END:");

  while(1){
    // Do nothing
  }
}