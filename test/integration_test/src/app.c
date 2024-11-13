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
#include "integration_test_common.h"
#include "sl_iec60730_internal.h"

void app_init(void)
{
#if defined(TEST_NONSECURE_ENABLE)
  funcptr_void NonSecure_ResetHandler;
  cmse_address_info_t addr_ok;

  /* Add user setup code for secure part here*/
  smu_config();
  system_init_ns();
  nvic_init();

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
#ifdef TEST_NON_SECURE_PERIPHERALS_ENABLE
printf("Test non-secure peripherals\n");
#else
printf("Test secure peripherals\n");
#endif

  integration_test_run_init();
  sl_iec60730_post();
#endif
}

void app_process_action(void)
{
  integration_test_run_process_action();
  printf("Pass-Test\n");
}
