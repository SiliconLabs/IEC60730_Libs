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

#include "iec60730_internal.h"

/* RAM location for temporary storage for run-time test */
static uint32_t bkBuf[RT_BLOCKSIZE + 2] __RT_BUF;
/* RAM pointer for run-time test */
STATIC_DEC_CLASSB_VARS(uint32_t *, rtCheck);
static uint32_t ramTestOverLap[RT_BLOCK_OVERLAP << 1] __USED __OVERLAP;
static uint32_t stackTestOverFlow[4] __STACK_BOTTOM;

extern bool Vmc_MarchC_Step(uint32_t *start,
                            uint32_t *end,
                            uint32_t background,
                            uint32_t *backup);
extern bool
    Vmc_MarchXC_Step(uint32_t *start, uint32_t *backup, uint32_t background);

__WEAK bool Vmc_PreRunMarchXC_Step(uint32_t *addr, uint32_t size)
{
  UNUSED_VAR(addr);
  UNUSED_VAR(size);
  return true;
}

__WEAK void Vmc_PostRunMarchXC_Step(uint32_t *addr, uint32_t size)
{
  UNUSED_VAR(addr);
  UNUSED_VAR(size);
}

void iec60730_VmcInit(vmcParams_t *params)
{
  if (NULL == params)
    return;

  rtCheck = (uint32_t *) ((uint32_t) params->start & 0xFFFFFFFCUL);
  INV_CLASSB_PVAR(uint32_t, rtCheck);

  stackTestOverFlow[0] = STACK_OVERFLOW_CONST_GUARD_VALUE_0;
  stackTestOverFlow[1] = STACK_OVERFLOW_CONST_GUARD_VALUE_1;
  stackTestOverFlow[2] = STACK_OVERFLOW_CONST_GUARD_VALUE_2;
  stackTestOverFlow[3] = STACK_OVERFLOW_CONST_GUARD_VALUE_3;
}

iec60730_TestResult_t iec60730_VmcPost(vmcParams_t *params)
{
  if (NULL == params)
    return iec60730_TestFailed;

  iec60730_TestResult_t result = iec60730_TestFailed;

  IEC60730_VMC_POST_ENTER_ATOMIC();

  iec60730_VmcInit(params);

  LABEL_DEF(IEC60730_VMC_POST_START_BKPT);

  // Check RAM region from begin to end
  while (rtCheck < params->end) {
    if (!CHECK_INTEGRITY(uint32_t, rtCheck))
      goto CHECK_DONE;
    if (!Vmc_MarchC_Step(rtCheck,
                         (uint32_t *) ((uint8_t *) (rtCheck + BLOCKSIZE) - 1),
                         BACKGROUND,
                         bkBuf))
      goto CHECK_DONE;
    rtCheck += BLOCKSIZE;
    // Only test bkBuf in the last step
    if (rtCheck == bkBuf) {
      rtCheck += BLOCKSIZE;
    }
    LABEL_DEF(IEC60730_VMC_POST_MARCHC_STEP_BKPT);
    INV_CLASSB_PVAR(uint32_t, rtCheck);
  }

  LABEL_DEF(IEC60730_VMC_POST_CHECKBKBUF_BKPT);

  // Check buffer bkBuf
  if (CHECK_INTEGRITY(uint32_t, rtCheck)) {
    if (Vmc_MarchC_Step(bkBuf,
                        (uint32_t *) ((uint8_t *) (bkBuf + BLOCKSIZE) - 1),
                        BACKGROUND,
                        bkBuf)) {
      result = iec60730_TestPassed;
    }
  }

CHECK_DONE:
  IEC60730_VMC_POST_EXIT_ATOMIC();

  return result;
}

iec60730_TestResult_t iec60730_VmcBist(vmcParams_t *params)
{
  if (NULL == params)
    return iec60730_TestFailed;

  LABEL_DEF(IEC60730_VMC_BIST_START_BKPT);

  iec60730_TestResult_t result = iec60730_TestInProgress;

  IEC60730_VMC_BIST_ENTER_ATOMIC();

  for (uint16_t i = 0; i < VAR_BLOCKS_PER_BIST; i++) {
    if (!CHECK_INTEGRITY(uint32_t, rtCheck)) {
      result = iec60730_TestFailed;
      goto VMC_BIST_DONE;
    }

    if (rtCheck > params->end) {
      LABEL_DEF(IEC60730_IMC_BIST_CHECKBKBUF_BKPT);

      // Check backup buffer bkBuf
      if (Vmc_MarchXC_Step(bkBuf, bkBuf, BACKGROUND)) {
        result = iec60730_TestPassed;
      } else {
        result = iec60730_TestFailed;
      }

      iec60730_VmcInit(params);
      goto VMC_BIST_DONE;
    } else {
      // Checking the allowance run testing
      if (!Vmc_PreRunMarchXC_Step(rtCheck, BLOCKSIZE)) {
        Vmc_PostRunMarchXC_Step(rtCheck, BLOCKSIZE);
        rtCheck += BLOCKSIZE;
        // If rtCheck equal bkBuf then jump to next block
        if (rtCheck == bkBuf) {
          rtCheck += BLOCKSIZE;
        }
        INV_CLASSB_PVAR(uint32_t, rtCheck);
        continue;
      }

      // Call MarchXC
      if (Vmc_MarchXC_Step(rtCheck, &bkBuf[1], BACKGROUND)) {
        // Implement after invoking MarchXC
        Vmc_PostRunMarchXC_Step(rtCheck, BLOCKSIZE);
        // Point to next block
        rtCheck += BLOCKSIZE;
        // If rtCheck equal bkBuf then jump to next block
        if (rtCheck == bkBuf) {
          rtCheck += BLOCKSIZE;
        }
        LABEL_DEF(IEC60730_VMC_BIST_MARCHC_STEP_BKPT);
        INV_CLASSB_PVAR(uint32_t, rtCheck);
      } else {
        // Implement after invoking MarchXC
        Vmc_PostRunMarchXC_Step(rtCheck, BLOCKSIZE);
        // Set result failed
        result = iec60730_TestFailed;
        goto VMC_BIST_DONE;
      }
    }
  }

VMC_BIST_DONE:
  IEC60730_VMC_BIST_EXIT_ATOMIC();

  if ((result == iec60730_TestInProgress) || (result == iec60730_TestPassed)) {
    LABEL_DEF(IEC60730_VMC_BIST_STACK_TEST_BKPT);
    if ((stackTestOverFlow[0] != STACK_OVERFLOW_CONST_GUARD_VALUE_0)
        || (stackTestOverFlow[1] != STACK_OVERFLOW_CONST_GUARD_VALUE_1)
        || (stackTestOverFlow[2] != STACK_OVERFLOW_CONST_GUARD_VALUE_2)
        || (stackTestOverFlow[3] != STACK_OVERFLOW_CONST_GUARD_VALUE_3)) {
      result = iec60730_TestFailed;
    } else {
      LABEL_DEF(IEC60730_VMC_BIST_STACK_TEST_OK_BKPT);
    }

    if (result == iec60730_TestPassed) {
      iec60730_programmeCounterCheck |= (IEC60730_VMC_COMPLETE);
    }
  }

  return result;
}
