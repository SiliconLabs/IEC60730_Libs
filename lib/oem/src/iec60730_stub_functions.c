/***************************************************************************/ /**
 * @file iec60730_stub_functions.c
 * @brief
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
#include "iec60730.h"

// TODO
// This file will be removed when components are completed

#ifdef EFR32MG12P_DEVICE
__WEAK sl_iec60730_test_result_t iec60730_CpuRegistersPost(void)
{
  return IEC60730_TEST_PASSED;
}

__WEAK sl_iec60730_test_result_t iec60730_CpuRegistersBist(void)
{
  return IEC60730_TEST_PASSED;
}
#endif /* EFR32MG12P_DEVICE */
