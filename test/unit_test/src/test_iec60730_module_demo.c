/***************************************************************************//**
 * @file
 * @brief Demo unit test module
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

#include "test_common.h"
#include "test_iec60730_module_demo.h"

/*======= CODE =====*/
void non_return_control_fun(void)
{
}

int add(int a, int b)
{
    return (a+b);
}

void setUp(void)
{
}

void tearDown(void)
{
}

/*=======Test Case=====*/
void test_addition(void)
{
    TEST_ASSERT_EQUAL(5, add(2,3));
}

void test_addition_failure(void)
{
    TEST_ASSERT_EQUAL(7, add(2,3));
}

/*=======Run Test Case=====*/

void test_iec60730_module_demo(void)
{
  // Initialize
  memset((void *)test_case_result, 0xff, sizeof(test_case_result));
  current_test_numth = 0;

  // Start run test
  printf("--- BEGIN UNIT TEST ---\n");
  UnityBegin("/unit_test/src/test_iec60730_module_demo.c");
  run_test(test_addition, "test_addition",23);
  run_test(test_addition_failure, "test_addition_failure", 28);
  UnityEnd();
  __asm volatile("IEC60730_UNIT_TEST_END:");

  while(1){
    // Do nothing
  }
}
