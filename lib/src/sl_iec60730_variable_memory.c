/***************************************************************************/ /**
 * @file
 * @brief Variable memory check
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

#include <stddef.h>
#include <string.h>

#include "sl_iec60730_internal.h"

/* RAM location for temporary storage for run-time test */
static uint32_t iec60730_bk_buf[RT_BLOCKSIZE + 2] __RT_BUF;
/* RAM pointer for run-time test */
STATIC_DEC_CLASSB_VARS(uint32_t *, iec60730_rt_check);
static uint32_t iec60730_stack_test_over_flow[4] __STACK_BOTTOM;
static __no_init sl_iec60730_vmc_params_t iec60730_vmc_test_config __CLASSB_RAM;
static bool iec60730_vmc_init_flag = false;

extern bool sl_iec60730_vmc_marchc_step(uint32_t *start,
                                        uint32_t *end,
                                        uint32_t background,
                                        uint32_t *backup);
extern bool sl_iec60730_vmc_marchxc_step(uint32_t *start,
                                         uint32_t *end,
                                         uint32_t background,
                                         uint32_t *backup);

__WEAK void sl_iec60730_vmc_pre_run_marchxc_step(uint32_t *addr, uint32_t size)
{
  UNUSED_VAR(addr);
  UNUSED_VAR(size);
}

__WEAK void sl_iec60730_vmc_post_run_marchxc_step(uint32_t *addr, uint32_t size)
{
  UNUSED_VAR(addr);
  UNUSED_VAR(size);
}

void sl_iec60730_vmc_init(sl_iec60730_vmc_params_t *params)
{
  if ((NULL == params) || (params->start == NULL) || (params->end == NULL))
    return;

  iec60730_vmc_test_config.start = params->start;
  iec60730_vmc_test_config.end   = params->end;
  iec60730_rt_check =
      (uint32_t *) ((uint32_t) (params->start - (RT_BLOCK_OVERLAP << 1))
                    & 0xFFFFFFFCUL);
  INV_CLASSB_PVAR(uint32_t, iec60730_rt_check);

  iec60730_stack_test_over_flow[0] = SL_STACK_OVERFLOW_CONST_GUARD_VALUE_0;
  iec60730_stack_test_over_flow[1] = SL_STACK_OVERFLOW_CONST_GUARD_VALUE_1;
  iec60730_stack_test_over_flow[2] = SL_STACK_OVERFLOW_CONST_GUARD_VALUE_2;
  iec60730_stack_test_over_flow[3] = SL_STACK_OVERFLOW_CONST_GUARD_VALUE_3;
  iec60730_vmc_init_flag           = true;
}

sl_iec60730_test_result_t sl_iec60730_vmc_post(void)
{
  sl_iec60730_test_result_t result = IEC60730_TEST_FAILED;

  SL_IEC60730_VMC_POST_ENTER_ATOMIC();

  if (!iec60730_vmc_init_flag) {
    goto VMC_POST_DONE;
  }

  iec60730_rt_check = (uint32_t *) ((uint32_t) (iec60730_vmc_test_config.start
                                                - (RT_BLOCK_OVERLAP << 1))
                                    & 0xFFFFFFFCUL);
  INV_CLASSB_PVAR(uint32_t, iec60730_rt_check);

  LABEL_DEF(IEC60730_VMC_POST_START_BKPT);

  // Check RAM region from begin to end
  while (iec60730_rt_check < iec60730_vmc_test_config.end) {
    if (!CHECK_INTEGRITY(uint32_t, iec60730_rt_check)) {
      goto VMC_POST_DONE;
    }

    // Only test iec60730_bk_buf in the last step
    if (iec60730_rt_check == iec60730_bk_buf) {
      iec60730_rt_check += BLOCKSIZE;
    }
    if (!sl_iec60730_vmc_marchc_step(
            iec60730_rt_check,
            (uint32_t *) ((uint8_t *) (iec60730_rt_check + 4) - 1),
            BACKGROUND,
            iec60730_bk_buf)) {
      goto VMC_POST_DONE;
    }
    iec60730_rt_check += BLOCKSIZE;
    LABEL_DEF(IEC60730_VMC_POST_MARCHC_STEP_BKPT);
    INV_CLASSB_PVAR(uint32_t, iec60730_rt_check);
  }

  LABEL_DEF(IEC60730_VMC_POST_CHECKiec60730_bk_buf_BKPT);

  // Check buffer iec60730_bk_buf
  if (CHECK_INTEGRITY(uint32_t, iec60730_rt_check)) {
    if (sl_iec60730_vmc_marchc_step(
            iec60730_bk_buf,
            (uint32_t *) ((uint8_t *) (iec60730_bk_buf + BLOCKSIZE) - 1),
            BACKGROUND,
            iec60730_bk_buf)) {
      result = IEC60730_TEST_PASSED;
    }
  }

VMC_POST_DONE:
  SL_IEC60730_VMC_POST_EXIT_ATOMIC();

  return result;
}

sl_iec60730_test_result_t sl_iec60730_vmc_bist(void)
{
  LABEL_DEF(IEC60730_VMC_BIST_START_BKPT);

  sl_iec60730_test_result_t result = IEC60730_TEST_IN_PROGRESS;

  SL_IEC60730_VMC_BIST_ENTER_ATOMIC();

  for (uint16_t i = 0; i < SL_IEC60730_VAR_BLOCKS_PER_BIST; i++) {
    if (!CHECK_INTEGRITY(uint32_t, iec60730_rt_check)) {
      result = IEC60730_TEST_FAILED;
      goto VMC_BIST_DONE;
    }

    if (iec60730_rt_check > iec60730_vmc_test_config.end) {
      LABEL_DEF(IEC60730_IMC_BIST_CHECKiec60730_bk_buf_BKPT);

      // Check backup buffer iec60730_bk_buf
      if (sl_iec60730_vmc_marchxc_step(
              iec60730_bk_buf,
              (uint32_t *) ((uint8_t *) (iec60730_bk_buf + BLOCKSIZE) - 1),
              BACKGROUND,
              iec60730_bk_buf)) {
        result = IEC60730_TEST_PASSED;
      } else {
        result = IEC60730_TEST_FAILED;
      }

      iec60730_rt_check =
          (uint32_t *) ((uint32_t) (iec60730_vmc_test_config.start
                                    - (RT_BLOCK_OVERLAP << 1))
                        & 0xFFFFFFFCUL);
      INV_CLASSB_PVAR(uint32_t, iec60730_rt_check);
      goto VMC_BIST_DONE;
    } else {
      // if there is a requirement to run a pre-test before running testing
      sl_iec60730_vmc_pre_run_marchxc_step(iec60730_rt_check, BLOCKSIZE);

      // If iec60730_rt_check equal iec60730_bk_buf then jump to next block
      if (iec60730_rt_check == iec60730_bk_buf) {
        iec60730_rt_check += BLOCKSIZE;
      }
      // Call MarchXC
      if (sl_iec60730_vmc_marchxc_step(
              iec60730_bk_buf,
              (uint32_t *) ((uint8_t *) (iec60730_bk_buf + BLOCKSIZE) - 1),
              BACKGROUND,
              iec60730_bk_buf)) {
        // Implement after invoking MarchXC
        sl_iec60730_vmc_post_run_marchxc_step(iec60730_rt_check, BLOCKSIZE);
        // Point to next block
        iec60730_rt_check += BLOCKSIZE;
        LABEL_DEF(IEC60730_VMC_BIST_MARCHC_STEP_BKPT);
        INV_CLASSB_PVAR(uint32_t, iec60730_rt_check);
      } else {
        // Implement after invoking MarchXC
        sl_iec60730_vmc_post_run_marchxc_step(iec60730_rt_check, BLOCKSIZE);
        // Set result failed
        result = IEC60730_TEST_FAILED;
        goto VMC_BIST_DONE;
      }
    }
  }

VMC_BIST_DONE:
  SL_IEC60730_VMC_BIST_EXIT_ATOMIC();

  if ((result == IEC60730_TEST_IN_PROGRESS)
      || (result == IEC60730_TEST_PASSED)) {
    LABEL_DEF(IEC60730_VMC_BIST_STACK_TEST_BKPT);
    if ((iec60730_stack_test_over_flow[0]
         != SL_STACK_OVERFLOW_CONST_GUARD_VALUE_0)
        || (iec60730_stack_test_over_flow[1]
            != SL_STACK_OVERFLOW_CONST_GUARD_VALUE_1)
        || (iec60730_stack_test_over_flow[2]
            != SL_STACK_OVERFLOW_CONST_GUARD_VALUE_2)
        || (iec60730_stack_test_over_flow[3]
            != SL_STACK_OVERFLOW_CONST_GUARD_VALUE_3)) {
      result = IEC60730_TEST_FAILED;
    } else {
      LABEL_DEF(IEC60730_VMC_BIST_STACK_TEST_OK_BKPT);
    }

    if (result == IEC60730_TEST_PASSED) {
      sl_iec60730_program_counter_check |= (IEC60730_VMC_COMPLETE);
    }
  }

  return result;
}
