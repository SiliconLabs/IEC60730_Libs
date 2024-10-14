/***************************************************************************//**
 * @file
 * @brief common unit test api
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

#ifndef _TEST_COMMON_H
#define _TEST_COMMON_H

#include <stdint.h>
#include <string.h>
#include "unity.h"

/*=======Result test case=====*/
#define MAX_NUMBER_OF_TEST_CASE    20

extern uint8_t test_case_result[MAX_NUMBER_OF_TEST_CASE];
extern uint8_t current_test_numth;

/*=======Test Runner Used To Run Each Test=====*/
extern void run_test(UnityTestFunction func, const char* name, UNITY_LINE_TYPE line_num);

#endif  // _TEST_COMMON_H
