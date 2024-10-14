/******************************************************************************
 * @file     main_s.c
 * @brief    Code template for secure main function
 * @version  V1.1.1
 * @date     10. January 2018
 ******************************************************************************/
/*
 * Copyright (c) 2013-2018 Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* Use CMSE intrinsics */
#if defined(TEST_NONSECURE_ENABLE)
#include <arm_cmse.h>
#include "partition_ARMCM33.h"
#endif
#include "Test_System.h"

/* TZ_START_NS: Start address of non-secure application */
#ifndef TZ_START_NS
#define TZ_START_NS (FLASH_MEM_BASE + 0x00028000U)
#endif

/* typedef for non-secure callback functions */
#if defined(TEST_NONSECURE_ENABLE)
typedef void (*funcptr_void)(void) __attribute__((cmse_nonsecure_call));
#endif

void SystemInit_ns(void)
{
#if defined(TEST_NONSECURE_ENABLE)
#if defined(__VTOR_PRESENT) && (__VTOR_PRESENT == 1U)
  SCB_NS->VTOR = (uint32_t) TZ_START_NS;
#endif

#if defined(UNALIGNED_SUPPORT_DISABLE)
  SCB_NS->CCR |= SCB_CCR_UNALIGN_TRP_Msk;
#endif

#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
  SCB_NS->CPACR |= ((3U << 10U * 2U)     /* set CP10 Full Access */
                    | (3U << 11U * 2U)); /* set CP11 Full Access */
#endif
#endif
}

void Nvic_Init(void)
{
  // One Group Priority
  NVIC_SetPriorityGrouping(7);
#if defined(TEST_TIMER_EN) || defined(TEST_IRQ_EN)                             \
    || defined(TEST_INTEGRATED_EN)
  /* Timer 0 */
  T_NVIC_SetPriority(TIMER0_IRQn, 1);
  T_NVIC_EnableIRQ(TIMER0_IRQn);
  /* Timer 1 */
  /* T_NVIC_SetPriority(TIMER1_IRQn, 1);
  T_NVIC_EnableIRQ(TIMER1_IRQn); */

  /* LETIMER 0 */
  T_NVIC_SetPriority(LETIMER0_IRQn, 1);
  T_NVIC_EnableIRQ(LETIMER0_IRQn);
#endif
}

/* SMU configuration */
void Smu_Config(void)
{
#if defined(SMU_PRESENT) && defined(_SILICON_LABS_32B_SERIES_2)
  /* WDOG0, WDOG1 non-secure */
  SMU_S->PPUSATD0_CLR =
      (SMU_PPUSATD0_CMU | SMU_PPUSATD0_HFRCO0 | SMU_PPUSATD0_FSRCO
       | SMU_PPUSATD0_DPLL0 | SMU_PPUSATD0_LFXO | SMU_PPUSATD0_LFRCO
       | SMU_PPUSATD0_GPIO | SMU_PPUSATD0_TIMER0 | SMU_PPUSATD0_BURAM
       | SMU_PPUSATD0_GPCRC | SMU_PPUSATD0_EMU)
      & _SMU_PPUSATD0_MASK;
  /* WDOG0, WDOG1 non-secure */
  SMU_S->PPUSATD1_CLR =
      (SMU_PPUSATD1_LETIMER0 | SMU_PPUSATD1_WDOG0) & _SMU_PPUSATD1_MASK;
#if (WDOG_COUNT > 1)
  SMU_S->PPUSATD1_CLR |= SMU_PPUSATD1_WDOG1;
#endif
  /* Flash Secure region */
  SMU_S->ESAUMRB01 = 0x00020000 & _SMU_ESAUMRB01_MASK;
  /* Flash Secure - Non secure callable region */
  SMU_S->ESAUMRB12 = 0x00028000 & _SMU_ESAUMRB12_MASK;
  /* RAM Secure region */
  SMU_S->ESAUMRB45 = 0x2000A000 & _SMU_ESAUMRB45_MASK;
  /* RAM Secure - Non secure callable region */
  SMU_S->ESAUMRB56 = 0x2000C000 & _SMU_ESAUMRB56_MASK;
#endif
}

/* Secure main() */
int main(void)
{
#if defined(TEST_NONSECURE_ENABLE)
  funcptr_void NonSecure_ResetHandler;
  cmse_address_info_t addr_ok;

  /* Add user setup code for secure part here*/
  Smu_Config();
  SystemInit_ns();
  Nvic_Init();

  /* Set non-secure main stack (MSP_NS) */
  __TZ_set_MSP_NS(*((uint32_t *) (TZ_START_NS)));

  /* Get non-secure reset handler */
  NonSecure_ResetHandler =
      (funcptr_void) (*((uint32_t *) ((TZ_START_NS) + 4U)));

  if (cmse_is_nsfptr(NonSecure_ResetHandler)) {
    while (1)
      ;
  } else {
    addr_ok = cmse_TTA_fptr(NonSecure_ResetHandler);
    if (!addr_ok.flags.secure) {
      /* Start non-secure state software application */
      NonSecure_ResetHandler();
    } else {
      while (1)
        ;
    }
  }

#else
  Nvic_Init();

  test_main();
#endif
  /* Non-secure software does not return, this code is not executed */
  while (1) {
    __NOP();
  }
}
