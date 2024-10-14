/***************************************************************************/ /**
 * @file    sl_iec60730_cpu_registers.c
 * @brief CPU Registers check
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
#include "sl_iec60730_cpu_registers.h"

/**************************************************************************/ /**
* @addtogroup efr32_iec60730
 * @{
 * @addtogroup IEC60730_CPUREG_Test
 * @{
 *****************************************************************************/

/**************************************************************************/ /**
 * public IEC60730 CPU Registers Built In Self Test
 *
 * @returns #iec60730_TestResult_t
 * @returns #iec60730_TestFailed means test failed,
 *          #iec60730_TestPassed means test passed.
 *
 * This function will do a test of all the CPU core registers.
 *****************************************************************************/
iec60730_TestResult_t iec60730_CpuRegistersBist(void)
{
  /* Test core register: APSR, R0-R12, LR */
  if (iec60730_TestFailed == iec60730_CpuRegistersCore())
    return iec60730_TestFailed;

#if (IEC60370_CPU == IEC60370_CM33)
#if defined(__TZ_PRESENT) && (__TZ_PRESENT == 1)

#if defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  /* Test Main Stack Pointer Non Secure */
  if (iec60730_TestFailed == iec60730_CpuRegistersMSP_NS())
    return iec60730_TestFailed;

  /* Test Main Stack Pointer Secure */
  if (iec60730_TestFailed == iec60730_CpuRegistersMSP_S())
    return iec60730_TestFailed;

  /* Test Process Stack Pointer Non Secure */
  if (iec60730_TestFailed == iec60730_CpuRegistersPSP_NS())
    return iec60730_TestFailed;

  /* Test Process Stack Pointer Secure */
  if (iec60730_TestFailed == iec60730_CpuRegistersPSP_S())
    return iec60730_TestFailed;

  /* Test Main Stack Pointer Limit Non Secure */
  if (iec60730_TestFailed == iec60730_CpuRegistersMSPLim_NS())
    return iec60730_TestFailed;

  /* Test Main Stack Pointer Limit Secure */
  if (iec60730_TestFailed == iec60730_CpuRegistersMSPLim_S())
    return iec60730_TestFailed;

  /* Test Process Stack Pointer Limit None Secure */
  if (iec60730_TestFailed == iec60730_CpuRegistersPSPLim_NS())
    return iec60730_TestFailed;

  /* Test Process Stack Pointer Limit Secure */
  if (iec60730_TestFailed == iec60730_CpuRegistersPSPLim_S())
    return iec60730_TestFailed;

  /* Test Control None Secure register */
  if (iec60730_TestFailed == iec60730_CpuRegistersControl_NS())
    return iec60730_TestFailed;

  /* Test Control Secure register */
  if (iec60730_TestFailed == iec60730_CpuRegistersControl_S())
    return iec60730_TestFailed;

  /* Test Primask Non Secure register */
  if (iec60730_TestFailed == iec60730_CpuRegistersPriMask_NS())
    return iec60730_TestFailed;

  /* Test Primask Secure register */
  if (iec60730_TestFailed == iec60730_CpuRegistersPriMask_S())
    return iec60730_TestFailed;

  /* Test BasePri Non Secure register */
  if (iec60730_TestFailed == iec60730_CpuRegistersBasePri_NS())
    return iec60730_TestFailed;

  /* Test BasePri Secure register */
  if (iec60730_TestFailed == iec60730_CpuRegistersBasePri_S())
    return iec60730_TestFailed;

  /* Test FaultMask Non Secure register */
  if (iec60730_TestFailed == iec60730_CpuRegistersFaultMask_NS())
    return iec60730_TestFailed;

  /* Test FaultMask Secure register */
  if (iec60730_TestFailed == iec60730_CpuRegistersFaultMask_S())
    return iec60730_TestFailed;
#endif
#else
#error the CM33 without TZ is not supported
#endif // defined(__TZ_PRESENT) && (__TZ_PRESENT == 1)
#endif // (IEC60370_CPU == IEC60370_CM33)

#if (IEC60370_CPU == IEC60370_CM4)
  /* Test Main Stack Pointer */
  if (iec60730_TestFailed == iec60730_CpuRegistersMSP())
    return iec60730_TestFailed;

  /* Test Process Stack Pointer */
  if (iec60730_TestFailed == iec60730_CpuRegistersPSP())
    return iec60730_TestFailed;

  /* Test Control register */
  if (iec60730_TestFailed == iec60730_CpuRegistersControl())
    return iec60730_TestFailed;

  /* Test Primask register */
  if (iec60730_TestFailed == iec60730_CpuRegistersPriMask())
    return iec60730_TestFailed;

  /* Test BasePri register */
  if (iec60730_TestFailed == iec60730_CpuRegistersBasePri())
    return iec60730_TestFailed;

  /* Test FaultMask register */
  if (iec60730_TestFailed == iec60730_CpuRegistersFaultMask())
    return iec60730_TestFailed;
#endif

  /* Test FPU FPSCR register */
  if (iec60730_TestFailed == iec60730_CpuRegistersFPU_FPSCR())
    return iec60730_TestFailed;

  /* Test FPU So-S31 register */
  if (iec60730_TestFailed == iec60730_CpuRegistersFPU_FPSx())
    return iec60730_TestFailed;

  iec60730_programmeCounterCheck |= (IEC60730_CPU_REGS_COMPLETE);

  return iec60730_TestPassed;
}

/**************************************************************************/ /**
 * public IEC60730 CPU Registers Power On Self Test
 *
 * @returns #iec60730_TestResult_t
 *
 * This function simply calls the iec60730_CpuRegistersBist() function.
 *****************************************************************************/
iec60730_TestResult_t iec60730_CpuRegistersPost(void)
{
  return iec60730_CpuRegistersBist();
}

/**************************************************************************/ /**
 * private IEC60730 CPU Registers Endless loop function
 *
 * @returns None
 *
 * This function simply disables interrupt then calls the iec60730_SafeState()
 * function.
 *****************************************************************************/
void iec60730_FailEndlessLoop(void)
{
  // Disable interrupts since we need to enter SafeState as quickly as possible
  __asm volatile("CPSID i" :::);

  iec60730_SafeState(iec60730_CpuRegistersFail);
}

/**************************************************************************/ /**
 * private IEC60730 CPU Registers Core Check
 *
 * @returns #iec60730_TestResult_t
 * @returns #iec60730_TestFailed means test failed,
 *          #iec60730_TestPassed means test passed.
 *
 * This function tests the following CPU registers in a sequence: APSR, R0-R12,
 * LR
 * Test patterns: R0�R12, LR: 0xAAAAAAAA, 0x55555555
 *****************************************************************************/
iec60730_TestResult_t iec60730_CpuRegistersCore(void)
{
  iec60730_TestResult_t result;

  __asm volatile(
      /* Safe critical registers */
      "   STMDB SP!, {R4, R5, R6, R7, R8, R9, R10, R11}   \n"

      /* Register APSR */
      "   MOVS R0, #0x00000000   \n" /* Set Z(ero) Flag */
#ifndef IAR_TESTING                  /* GCC */
      "IEC60730_CPU_REGS_CORE_Z_FLAG_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_CORE_Z_FLAG_ASM_BKPT:: \n"
#endif
      "   BNE.W iec60730_FailEndlessLoopCore   \n" /* Fails if Z clear */
      "   SUBS R0,#1   \n"                         /* Set N(egative) Flag */
#ifndef IAR_TESTING                                /* GCC */
      "IEC60730_CPU_REGS_CORE_N_FLAG_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_CORE_N_FLAG_ASM_BKPT:: \n"
#endif
      "   BPL.W iec60730_FailEndlessLoopCore   \n" /* Fails if N clear */
      "   ADDS R0,#2   \n" /* Set C(array) Flag and do not set Z*/
#ifndef IAR_TESTING        /* GCC */
      "IEC60730_CPU_REGS_CORE_C_FLAG_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_CORE_C_FLAG_ASM_BKPT:: \n"
#endif
      "   BCC.W iec60730_FailEndlessLoopCore   \n" /* Fails if C clear */
      "   MOVS R0, #0x80000000   \n"               /* Prepares Overflow test */
      "   ADDS R0, R0, R0   \n"                    /* Set V(overflow) Flag */
#ifndef IAR_TESTING                                /* GCC */
      "IEC60730_CPU_REGS_CORE_V_FLAG_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_CORE_V_FLAG_ASM_BKPT:: \n"
#endif
      "   BVC.W iec60730_FailEndlessLoopCore   \n" /* Fails if V clear */
      "   MOVS R0, #0xFFFFFFFF   \n" /* Prepares Saturation test */
      "   USAT R1,#10,R0   \n"       /* Set Q(saturation) Flag */
      "   MRS R0, APSR   \n"         /* Get Status register */
      "   CMP R0, #0xB8000000   \n"  /* Verifies that N=C=V=Q=1 */
      "   BNE.W iec60730_FailEndlessLoopCore   \n" /* Fails if Q+N+C=V clear */

      /* Register R0 (holds value returned by the function) */
      "   MOVS R0, #0xAAAAAAAA   \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_CORE_R0_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_CORE_R0_ASM_BKPT:: \n"
#endif
      "   CMP R0, #0xAAAAAAAA   \n"
      "   BNE.W iec60730_FailEndlessLoopCore   \n"
      "   MOVS R0, #0x55555555   \n"
      "   CMP R0, #0x55555555   \n"
      "   BNE.W iec60730_FailEndlessLoopCore   \n"

      /* Register R1 */
      "   MOVS R1, #0xAAAAAAAA \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_CORE_R1_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_CORE_R1_ASM_BKPT:: \n"
#endif
      "   CMP R1, #0xAAAAAAAA \n"
      "   BNE.W iec60730_FailEndlessLoopCore \n"
      "   MOVS R1, #0x55555555 \n"
      "   CMP R1, #0x55555555 \n"
      "   BNE.W iec60730_FailEndlessLoopCore \n"

      /* Register R2 */
      "   MOVS R2, #0xAAAAAAAA \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_CORE_R2_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_CORE_R2_ASM_BKPT:: \n"
#endif
      "   CMP R2, #0xAAAAAAAA \n"
      "   BNE.W IEC60730_CPU_REGS_CORE_FAIL \n"
      "   MOVS R2, #0x55555555 \n"
      "   CMP R2, #0x55555555 \n"
      "   BNE.W IEC60730_CPU_REGS_CORE_FAIL \n"

      /* Register R3 */
      "   MOVS R3, #0xAAAAAAAA \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_CORE_R3_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_CORE_R3_ASM_BKPT:: \n"
#endif
      "   CMP R3, #0xAAAAAAAA \n"
      "   BNE.W IEC60730_CPU_REGS_CORE_FAIL \n"
      "   MOVS R3, #0x55555555 \n"
      "   CMP R3, #0x55555555 \n"
      "   BNE.W IEC60730_CPU_REGS_CORE_FAIL \n"

      /* Register R4 */
      "   MOVS R4, #0xAAAAAAAA \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_CORE_R4_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_CORE_R4_ASM_BKPT:: \n"
#endif
      "   CMP R4, #0xAAAAAAAA \n"
      "   BNE.W IEC60730_CPU_REGS_CORE_FAIL \n"
      "   MOVS R4, #0x55555555 \n"
      "   CMP R4, #0x55555555 \n"
      "   BNE.W IEC60730_CPU_REGS_CORE_FAIL \n"

      /* Register R5 */
      "   MOVS R5, #0xAAAAAAAA \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_CORE_R5_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_CORE_R5_ASM_BKPT:: \n"
#endif
      "   CMP R5, #0xAAAAAAAA \n"
      "   BNE.W IEC60730_CPU_REGS_CORE_FAIL \n"
      "   MOVS R5, #0x55555555 \n"
      "   CMP R5, #0x55555555 \n"
      "   BNE.W IEC60730_CPU_REGS_CORE_FAIL \n"

      /* Register R6 */
      "   MOVS R6, #0xAAAAAAAA \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_CORE_R6_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_CORE_R6_ASM_BKPT:: \n"
#endif
      "   CMP R6, #0xAAAAAAAA \n"
      "   BNE.W IEC60730_CPU_REGS_CORE_FAIL \n"
      "   MOVS R6, #0x55555555 \n"
      "   CMP R6, #0x55555555 \n"
      "   BNE.W IEC60730_CPU_REGS_CORE_FAIL \n"

      /* Register R7 */
      "   MOVS R7, #0xAAAAAAAA \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_CORE_R7_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_CORE_R7_ASM_BKPT:: \n"
#endif
      "   CMP R7, #0xAAAAAAAA \n"
      "   BNE.W IEC60730_CPU_REGS_CORE_FAIL \n"
      "   MOVS R7, #0x55555555 \n"
      "   CMP R7, #0x55555555 \n"
      "   BNE.W IEC60730_CPU_REGS_CORE_FAIL \n"

      /* Register R8 */
      "   MOVS R8, #0xAAAAAAAA \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_CORE_R8_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_CORE_R8_ASM_BKPT:: \n"
#endif
      "   CMP R8, #0xAAAAAAAA \n"
      "   BNE.W IEC60730_CPU_REGS_CORE_FAIL \n"
      "   MOVS R8, #0x55555555 \n"
      "   CMP R8, #0x55555555 \n"
      "   BNE.W IEC60730_CPU_REGS_CORE_FAIL \n"

      /* Register R9 */
      "   MOVS R9, #0xAAAAAAAA \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_CORE_R9_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_CORE_R9_ASM_BKPT:: \n"
#endif
      "   CMP R9, #0xAAAAAAAA \n"
      "   BNE.W IEC60730_CPU_REGS_CORE_FAIL \n"
      "   MOVS R9, #0x55555555 \n"
      "   CMP R9, #0x55555555 \n"
      "   BNE.W IEC60730_CPU_REGS_CORE_FAIL \n"

      /* Register R10 */
      "   MOVS R10, #0xAAAAAAAA \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_CORE_R10_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_CORE_R10_ASM_BKPT:: \n"
#endif
      "   CMP R10, #0xAAAAAAAA \n"
      "   BNE IEC60730_CPU_REGS_CORE_FAIL \n"
      "   MOVS R10, #0x55555555 \n"
      "   CMP R10, #0x55555555 \n"
      "   BNE IEC60730_CPU_REGS_CORE_FAIL \n"

      /* Register R11 */
      "   MOVS R11, #0xAAAAAAAA \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_CORE_R11_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_CORE_R11_ASM_BKPT:: \n"
#endif
      "   CMP R11, #0xAAAAAAAA \n"
      "   BNE IEC60730_CPU_REGS_CORE_FAIL \n"
      "   MOVS R11, #0x55555555 \n"
      "   CMP R11, #0x55555555 \n"
      "   BNE IEC60730_CPU_REGS_CORE_FAIL \n"

      /* Register R12 */
      "   MOVS R12, #0xAAAAAAAA \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_CORE_R12_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_CORE_R12_ASM_BKPT:: \n"
#endif
      "   CMP R12, #0xAAAAAAAA \n"
      "   BNE IEC60730_CPU_REGS_CORE_FAIL \n"
      "   MOVS R12, #0x55555555 \n"
      "   CMP R12, #0x55555555 \n"
      "   BNE IEC60730_CPU_REGS_CORE_FAIL \n"

      /* Register LR (R14) */
      "   MOV R0, LR   \n"
      "   MOVS R1, #0xAAAAAAAA   \n"
      "   MOV LR, R1   \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_CORE_LR_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_CORE_LR_ASM_BKPT:: \n"
#endif
      "   MOV R2, LR   \n"
      "   CMP R2, R1   \n" /* Verify value */
      "   BNE iec60730_FailEndlessLoopCore   \n"
      "   MOVS R1, #0x55555555   \n"
      "   MOV LR, R1   \n"
      "   MOV R2, LR   \n"
      "   CMP R2, R1   \n" /* Verify value */
      "   BNE iec60730_FailEndlessLoopCore   \n"
      "   MOV LR, R0   \n" /* Restore value */

      "   B IEC60730_CPU_REGS_CORE_PASS_ASM_BKPT   \n"
#ifndef IAR_TESTING /* GCC */
      "iec60730_FailEndlessLoopCore: \n"
#else
      "iec60730_FailEndlessLoopCore:: \n"
#endif
      "   LDR R3,=iec60730_FailEndlessLoop \n"
      "   BX R3   \n"

/*Test passed, return 1 instead of 0 in global variable*/
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_CORE_PASS_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_CORE_PASS_ASM_BKPT:: \n"
#endif
      "   MOVS %0, #0x1      \n" /* Return. */
      "   B IEC60730_CPU_REGS_CORE_DONE    \n"

#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_CORE_FAIL:                \n"
#else
      "IEC60730_CPU_REGS_CORE_FAIL::                \n"
#endif
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_CORE_FAIL_ASM_BKPT:       \n"
#else
      "IEC60730_CPU_REGS_CORE_FAIL_ASM_BKPT::       \n"
#endif
      "   MOVS %0, #0x0      \n"

/* Restore critical registers */
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_CORE_DONE:\n"
#else
      "IEC60730_CPU_REGS_CORE_DONE::\n"
#endif
      "   LDMIA SP!, {R4, R5, R6, R7, R8, R9, R10, R11}   \n"
      "                    \n"
      : "=r"(result)::"memory");

  return result;
}

/**************************************************************************/ /**
 * private IEC60730 CPU Register MSP Non-Secure Check
 *
 * @returns #iec60730_TestResult_t
 *          #iec60730_TestPassed means test passed.
 *
 * This function tests the MSP_NS (Main Stack Pointer, Non-Secure) register.
 * If MSP_NS is corrupted, the function stucks in an endless loop with
 * interrupts disabled. This state must be observed by another safety mechanism
 * (for example, watchdog).
 * Test patterns: 0xAAAAAAA8, 0x55555554
 * @warning This function cannot be interrupted. The core must be in the
 * secure state.
 *****************************************************************************/
#if ((IEC60370_CPU == IEC60370_CM33) && defined(__TZ_PRESENT)                  \
     && (__TZ_PRESENT == 1))                                                   \
    && defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
iec60730_TestResult_t iec60730_CpuRegistersMSP_NS(void)
{
  iec60730_TestResult_t result;

  __asm volatile(
      "   CPSID i  \n"             /*Disable IRQ Interrupts*/
      "   MRS R3, CONTROL_NS   \n" /*Save Control value */
      "   MRS R0, MSP_NS   \n"     /*Save stack value */
      "   MOVW R1, #0xAAA8   \n"   /*Test is different (MSP is word aligned)*/
      "   MOVT R1, #0xAAAA   \n"
      "   MSR MSP_NS, R1   \n" /*load stack value */
#ifndef IAR_TESTING            /* GCC */
      "IEC60730_CPU_REGS_MSP_NS_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_MSP_NS_ASM_BKPT:: \n"
#endif
      "   MRS R2, MSP_NS   \n" /*Get back stack value */
      "   CMP R2, R1   \n"     /*Verify value */
      "   BNE iec60730_FailEndlessLoopMSP_NS   \n"
      "   MOVW R1, #0x5554   \n" /*Test is different (MSP is word aligned)*/
      "   MOVT R1, #0x5555   \n"
      "   MSR MSP_NS, R1   \n" /* load stack value */
      "   MRS R2, MSP_NS   \n" /* Get back stack value */
      "   CMP R2, R1   \n"     /* Verify value */
      "   BNE iec60730_FailEndlessLoopMSP_NS   \n"
      "   MSR MSP_NS, R0   \n"     /* Restore stack value */
      "   MSR CONTROL_NS, R3   \n" /* Restore Control value */
      "   ISB             \n"

      "   B IEC60730_CPU_REGS_MSP_NS_PASS_ASM_BKPT   \n"
#ifndef IAR_TESTING /* GCC */
      "iec60730_FailEndlessLoopMSP_NS: \n"
#else
      "iec60730_FailEndlessLoopMSP_NS:: \n"
#endif
      "   LDR R3,=iec60730_FailEndlessLoop \n"
      "   BX R3   \n"

#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_MSP_NS_PASS_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_MSP_NS_PASS_ASM_BKPT:: \n"
#endif
      "   MOVS %0, #0x1      \n" /* Returned value. */
      "   CPSIE i  \n"           /*Enable IRQ Interrupts*/
      : "=r"(result)::"memory");

  return result;
}
#endif

/**************************************************************************/ /**
 * private IEC60730 CPU Register MSP Secure Check
 *
 * @returns #iec60730_TestResult_t
 *          #iec60730_TestPassed means test passed.
 *
 * This function tests the MSPS (Main Stack Pointer, Secure) register.
 * If MSP_S is corrupted, the function stucks in an endless loop with
 * interrupts disabled. This state must be observed by another safety mechanism
 * (for example, watchdog).
 * Test patterns: 0xAAAAAAA8, 0x55555554
 * @warning This function cannot be interrupted. The core must be in the
 * secure state.
 *****************************************************************************/
#if ((IEC60370_CPU == IEC60370_CM33) && defined(__TZ_PRESENT)                  \
     && (__TZ_PRESENT == 1))                                                   \
    && defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
iec60730_TestResult_t iec60730_CpuRegistersMSP_S(void)
{
  iec60730_TestResult_t result;

  __asm volatile("   CPSID i  \n"          /*Disable IRQ Interrupts*/
                 "   MRS R3, CONTROL   \n" /* Save Control value */
                 "   MRS R0, MSP   \n"     /* Save stack value */
                 "   MOVW R1, #0xAAA8   \n"
                 "   MOVT R1, #0xAAAA   \n"
                 "   MSR MSP, R1   \n" /* load stack value */
#ifndef IAR_TESTING                    /* GCC */
                 "IEC60730_CPU_REGS_MSP_S_ASM_BKPT: \n"
#else
                 "IEC60730_CPU_REGS_MSP_S_ASM_BKPT:: \n"
#endif
                 "   MRS R2, MSP   \n" /* Get back stack value */
                 "   CMP R2, R1   \n"  /* Verify value */
                 "   BNE iec60730_FailEndlessLoopMSP_S   \n"
                 "   MOVW R1, #0x5554   \n"
                 "   MOVT R1, #0x5555   \n"
                 "   MSR MSP, R1   \n" /* load stack value */
                 "   MRS R2, MSP   \n" /* Get back stack value */
                 "   CMP R2, R1   \n"  /* Verify value */
                 "   BNE iec60730_FailEndlessLoopMSP_S   \n"
                 "   MSR MSP, R0   \n"     /* Restore stack value */
                 "   MSR CONTROL, R3   \n" /* Restore Control value */
                 "   ISB             \n"

                 "   B IEC60730_CPU_REGS_MSP_S_PASS_ASM_BKPT   \n"
#ifndef IAR_TESTING /* GCC */
                 "iec60730_FailEndlessLoopMSP_S: \n"
#else
                 "iec60730_FailEndlessLoopMSP_S:: \n"
#endif
                 "   LDR R3,=iec60730_FailEndlessLoop \n"
                 "   BX R3   \n"

#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_MSP_S_PASS_ASM_BKPT: \n"
#else
                 "IEC60730_CPU_REGS_MSP_S_PASS_ASM_BKPT:: \n"
#endif
                 "   MOVS %0, #0x1      \n" /* Return. */
                 "   CPSIE i  \n"           /*Enable IRQ Interrupts*/
                 : "=r"(result)::"memory");

  return result;
}
#endif

/**************************************************************************/ /**
 * private IEC60730 CPU Register MSP Check
 *
 * @returns #iec60730_TestResult_t
 *          #iec60730_TestPassed means test passed.
 *
 * This function tests the MSP (Main Stack Pointer) register.
 * If MSP is corrupted, the function stucks in an endless loop with
 * interrupts disabled. This state must be observed by another safety mechanism
 * (for example, watchdog).
 * Test patterns: 0xAAAAAAA8, 0x55555554
 * @warning This function cannot be interrupted.
 *****************************************************************************/
#if (IEC60370_CPU == IEC60370_CM4)
iec60730_TestResult_t iec60730_CpuRegistersMSP(void)
{
  iec60730_TestResult_t result;

  __asm volatile("   CPSID i  \n"          /*Disable IRQ Interrupts*/
                 "   MRS R3, CONTROL   \n" /* Save Control value */
                 "   MRS R0, MSP   \n"     /* Save stack value */
                 "   MOVW R1, #0xAAA8   \n"
                 "   MOVT R1, #0xAAAA   \n"
                 "   MSR MSP, R1   \n" /* load stack value */
#ifndef IAR_TESTING                    /* GCC */
                 "IEC60730_CPU_REGS_MSP_S_ASM_BKPT: \n"
#else
                 "IEC60730_CPU_REGS_MSP_S_ASM_BKPT:: \n"
#endif
                 "   MRS R2, MSP   \n" /* Get back stack value */
                 "   CMP R2, R1   \n"  /* Verify value */
                 "   BNE iec60730_FailEndlessLoopMSP   \n"
                 "   MOVW R1, #0x5554   \n"
                 "   MOVT R1, #0x5555   \n"
                 "   MSR MSP, R1   \n" /* load stack value */
                 "   MRS R2, MSP   \n" /* Get back stack value */
                 "   CMP R2, R1   \n"  /* Verify value */
                 "   BNE iec60730_FailEndlessLoopMSP   \n"
                 "   MSR MSP, R0   \n"     /* Restore stack value */
                 "   MSR CONTROL, R3   \n" /* Restore Control value */

                 "   B IEC60730_CPU_REGS_MSP_S_PASS_ASM_BKPT   \n"
#ifndef IAR_TESTING /* GCC */
                 "iec60730_FailEndlessLoopMSP: \n"
#else
                 "iec60730_FailEndlessLoopMSP:: \n"
#endif
                 "   LDR R3,=iec60730_FailEndlessLoop \n"
                 "   BX R3   \n"

#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_MSP_S_PASS_ASM_BKPT: \n"
#else
                 "IEC60730_CPU_REGS_MSP_S_PASS_ASM_BKPT:: \n"
#endif
                 "   MOVS %0, #0x1      \n" /* Return. */
                 "   CPSIE i  \n"           /*Enable IRQ Interrupts*/
                 : "=r"(result)::"memory");

  return result;
}
#endif

/**************************************************************************/ /**
 * private IEC60730 CPU Register PSP Non-Secure Check
 *
 * @returns #iec60730_TestResult_t
 *          #iec60730_TestPassed means test passed.
 *
 * This function tests the PSP_NS (Process Stack Pointer, Non-Secure) register.
 * If PSP_NS is corrupted, the function stucks in an endless loop with
 * interrupts disabled. This state must be observed by another safety mechanism
 * (for example, watchdog).
 * Test patterns: 0xAAAAAAA8, 0x55555554
 * @warning This function cannot be interrupted. The core must be in the
 * secure state.
 *****************************************************************************/
#if ((IEC60370_CPU == IEC60370_CM33) && defined(__TZ_PRESENT)                  \
     && (__TZ_PRESENT == 1))                                                   \
    && defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
iec60730_TestResult_t iec60730_CpuRegistersPSP_NS(void)
{
  iec60730_TestResult_t result;

  __asm volatile("   CPSID i  \n"             /*Disable IRQ Interrupts*/
                 "   MRS R3, CONTROL_NS   \n" /* Save Control value */
                 "   MRS R0, PSP_NS   \n"     /* Save process stack value */
                 "   MOVW R1, #0xAAA8   \n"
                 "   MOVT R1, #0xAAAA   \n"
                 "   MSR PSP_NS, R1   \n" /* load process stack value */
#ifndef IAR_TESTING                       /* GCC */
                 "IEC60730_CPU_REGS_PSP_NS_ASM_BKPT: \n"
#else
                 "IEC60730_CPU_REGS_PSP_NS_ASM_BKPT:: \n"
#endif
                 "   MRS R2, PSP_NS   \n" /* Get back process stack value */
                 "   CMP R2, R1   \n"     /* Verify value */
                 "   BNE iec60730_FailEndlessLoopPSP_NS   \n"
                 "   MOVW R1, #0x5554   \n"
                 "   MOVT R1, #0x5555   \n"
                 "   MSR PSP_NS, R1   \n" /* load process stack value */
                 "   MRS R2, PSP_NS   \n" /* Get back process stack value */
                 "   CMP R2, R1   \n"     /* Verify value */
                 "   BNE iec60730_FailEndlessLoopPSP_NS   \n"
                 "   MSR PSP_NS, R0   \n"     /* Restore process stack value */
                 "   MSR CONTROL_NS, R3   \n" /* Restore Control value */
                 "   ISB             \n"

                 "   B IEC60730_CPU_REGS_PSP_NS_PASS_ASM_BKPT   \n"
#ifndef IAR_TESTING /* GCC */
                 "iec60730_FailEndlessLoopPSP_NS: \n"
#else
                 "iec60730_FailEndlessLoopPSP_NS:: \n"
#endif
                 "   LDR R3,=iec60730_FailEndlessLoop \n"
                 "   BX R3   \n"

#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_PSP_NS_PASS_ASM_BKPT: \n"
#else
                 "IEC60730_CPU_REGS_PSP_NS_PASS_ASM_BKPT:: \n"
#endif
                 "   MOVS %0, #0x1      \n" /* Return. */
                 "   CPSIE i  \n"           /*Enable IRQ Interrupts*/
                 : "=r"(result)::"memory");

  return result;
}
#endif

/**************************************************************************/ /**
 * private IEC60730 CPU Register PSP Secure Check
 *
 * @returns #iec60730_TestResult_t
 *          #iec60730_TestPassed means test passed.
 *
 * This function tests the PSP_S (Process Stack Pointer, Secure) register.
 * If PSP_S is corrupted, the function stucks in an endless loop with
 * interrupts disabled. This state must be observed by another safety mechanism
 * (for example, watchdog).
 * Test patterns: 0xAAAAAAA8, 0x55555554
 * @warning This function cannot be interrupted. The core must be in the
 * secure state.
 *****************************************************************************/
#if ((IEC60370_CPU == IEC60370_CM33) && defined(__TZ_PRESENT)                  \
     && (__TZ_PRESENT == 1))                                                   \
    && defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
iec60730_TestResult_t iec60730_CpuRegistersPSP_S(void)
{
  iec60730_TestResult_t result;

  __asm volatile("   CPSID i  \n"          /*Disable IRQ Interrupts*/
                 "   MRS R3, CONTROL   \n" /* Save Control value */
                 "   MRS R0, PSP   \n"     /* Save process stack value */
                 "   MOVW R1, #0xAAA8   \n"
                 "   MOVT R1, #0xAAAA   \n"
                 "   MSR PSP, R1   \n" /* load process stack value */
#ifndef IAR_TESTING                    /* GCC */
                 "IEC60730_CPU_REGS_PSP_S_ASM_BKPT: \n"
#else
                 "IEC60730_CPU_REGS_PSP_S_ASM_BKPT:: \n"
#endif
                 "   MRS R2, PSP   \n" /* Get back process stack value */
                 "   CMP R2, R1   \n"  /* Verify value */
                 "   BNE iec60730_FailEndlessLoopPSP_S   \n"
                 "   MOVW R1, #0x5554   \n"
                 "   MOVT R1, #0x5555   \n"
                 "   MSR PSP, R1   \n" /* load process stack value */
                 "   MRS R2, PSP   \n" /* Get back process stack value */
                 "   CMP R2, R1   \n"  /* Verify value */
                 "   BNE iec60730_FailEndlessLoopPSP_S   \n"
                 "   MSR PSP, R0   \n"     /* Restore process stack value */
                 "   MSR CONTROL, R3   \n" /* Restore Control value */
                 "   ISB             \n"

                 "   B IEC60730_CPU_REGS_PSP_S_PASS_ASM_BKPT   \n"
#ifndef IAR_TESTING /* GCC */
                 "iec60730_FailEndlessLoopPSP_S: \n"
#else
                 "iec60730_FailEndlessLoopPSP_S:: \n"
#endif
                 "   LDR R3,=iec60730_FailEndlessLoop \n"
                 "   BX R3   \n"

#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_PSP_S_PASS_ASM_BKPT: \n"
#else
                 "IEC60730_CPU_REGS_PSP_S_PASS_ASM_BKPT:: \n"
#endif

                 "   MOVS %0, #0x1      \n" /* Return. */
                 "   CPSIE i  \n"           /*Enable IRQ Interrupts*/
                 : "=r"(result)::"memory");

  return result;
}
#endif

/**************************************************************************/ /**
 * private IEC60730 CPU Register PSP Check
 *
 * @returns #iec60730_TestResult_t
 *          #iec60730_TestPassed means test passed.
 *
 * This function tests the PSP (Process Stack Pointer) register.
 * If PSP is corrupted, the function stucks in an endless loop with
 * interrupts disabled. This state must be observed by another safety mechanism
 * (for example, watchdog).
 * Test patterns: 0xAAAAAAA8, 0x55555554
 * @warning This function cannot be interrupted.
 *****************************************************************************/
#if (IEC60370_CPU == IEC60370_CM4)
iec60730_TestResult_t iec60730_CpuRegistersPSP(void)
{
  iec60730_TestResult_t result;

  __asm volatile("   CPSID i  \n"          /*Disable IRQ Interrupts*/
                 "   MRS R3, CONTROL   \n" /* Save Control value */
                 "   MRS R0, PSP   \n"     /* Save process stack value */
                 "   MOVW R1, #0xAAA8   \n"
                 "   MOVT R1, #0xAAAA   \n"
                 "   MSR PSP, R1   \n" /* load process stack value */
#ifndef IAR_TESTING                    /* GCC */
                 "IEC60730_CPU_REGS_PSP_S_ASM_BKPT: \n"
#else
                 "IEC60730_CPU_REGS_PSP_S_ASM_BKPT:: \n"
#endif
                 "   MRS R2, PSP   \n" /* Get back process stack value */
                 "   CMP R2, R1   \n"  /* Verify value */
                 "   BNE iec60730_FailEndlessLoopPSP   \n"
                 "   MOVW R1, #0x5554   \n"
                 "   MOVT R1, #0x5555   \n"
                 "   MSR PSP, R1   \n" /* load process stack value */
                 "   MRS R2, PSP   \n" /* Get back process stack value */
                 "   CMP R2, R1   \n"  /* Verify value */
                 "   BNE iec60730_FailEndlessLoopPSP   \n"
                 "   MSR PSP, R0   \n"     /* Restore process stack value */
                 "   MSR CONTROL, R3   \n" /* Restore Control value */

                 "   B IEC60730_CPU_REGS_PSP_S_PASS_ASM_BKPT   \n"
#ifndef IAR_TESTING /* GCC */
                 "iec60730_FailEndlessLoopPSP: \n"
#else
                 "iec60730_FailEndlessLoopPSP:: \n"
#endif
                 "   LDR R3,=iec60730_FailEndlessLoop \n"
                 "   BX R3   \n"

#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_PSP_S_PASS_ASM_BKPT: \n"
#else
                 "IEC60730_CPU_REGS_PSP_S_PASS_ASM_BKPT:: \n"
#endif
                 "   MOVS %0, #0x1      \n" /* Return. */
                 "   CPSIE i  \n"           /*Enable IRQ Interrupts*/
                 : "=r"(result)::"memory");

  return result;
}
#endif

/**************************************************************************/ /**
 * private IEC60730 CPU Register MSPLIM Non-Secure Check
 *
 * @returns #iec60730_TestResult_t
 *          #iec60730_TestPassed means test passed.
 *
 * This function tests the MSPLIM_NS (Main Stack Pointer Limit, Non-Secure)
 * register. If MSPLIM_NS is corrupted, the function stucks in an endless loop
 * with interrupts disabled. This state must be observed by another safety
 * mechanism (for example, watchdog).
 * Test patterns: 0xAAAAAAA8, 0x55555550
 * @warning This function cannot be interrupted. The core must be in the
 * secure state.
 *****************************************************************************/
#if ((IEC60370_CPU == IEC60370_CM33) && defined(__TZ_PRESENT)                  \
     && (__TZ_PRESENT == 1))                                                   \
    && defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
iec60730_TestResult_t iec60730_CpuRegistersMSPLim_NS(void)
{
  iec60730_TestResult_t result;

  __asm volatile("   CPSID i  \n"             /*Disable IRQ Interrupts*/
                 "   MRS R3, CONTROL_NS   \n" /* Save Control value */
                 "   MRS R0, MSPLIM_NS   \n"  /* Save stack value */
                 "   MOVW R1, #0xAAA8   \n"
                 "   MOVT R1, #0xAAAA   \n"
                 "   MSR MSPLIM_NS, R1   \n" /* load stack value */
#ifndef IAR_TESTING                          /* GCC */
                 "IEC60730_CPU_REGS_MSPLIM_NS_ASM_BKPT: \n"
#else
                 "IEC60730_CPU_REGS_MSPLIM_NS_ASM_BKPT:: \n"
#endif
                 "   MRS R2, MSPLIM_NS   \n" /* Get back stack value */
                 "   CMP R2, R1   \n"        /* Verify value */
                 "   BNE iec60730_FailEndlessLoopMSPLim_NS   \n"
                 "   MOVW R1, #0x5550   \n"
                 "   MOVT R1, #0x5555   \n"
                 "   MSR MSPLIM_NS, R1   \n" /* load stack value */
                 "   MRS R2, MSPLIM_NS   \n" /* Get back stack value */
                 "   CMP R2, R1   \n"        /* Verify value */
                 "   BNE iec60730_FailEndlessLoopMSPLim_NS   \n"
                 "   MSR MSPLIM_NS, R0   \n"  /* Restore stack value */
                 "   MSR CONTROL_NS, R3   \n" /* Restore Control value */
                 "   ISB             \n"

                 "   B IEC60730_CPU_REGS_MSPLIM_NS_PASS_ASM_BKPT   \n"
#ifndef IAR_TESTING /* GCC */
                 "iec60730_FailEndlessLoopMSPLim_NS: \n"
#else
                 "iec60730_FailEndlessLoopMSPLim_NS:: \n"
#endif
                 "   LDR R3,=iec60730_FailEndlessLoop \n"
                 "   BX R3   \n"

#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_MSPLIM_NS_PASS_ASM_BKPT: \n"
#else
                 "IEC60730_CPU_REGS_MSPLIM_NS_PASS_ASM_BKPT:: \n"
#endif
                 "   MOVS %0, #0x1      \n" /* Return. */
                 "   CPSIE i  \n"           /*Enable IRQ Interrupts*/
                 : "=r"(result)::"memory");

  return result;
}
#endif

/**************************************************************************/ /**
 * private IEC60730 CPU Register MSPLIM Secure Check
 *
 * @returns #iec60730_TestResult_t
 *          #iec60730_TestPassed means test passed.
 *
 * This function tests the MSPLIM_S (Main Stack Pointer Limit, Secure)
 * register. If MSPLIM_S is corrupted, the function stucks in an endless loop
 * with interrupts disabled. This state must be observed by another safety
 * mechanism (for example, watchdog).
 * Test patterns: 0xAAAAAAA8, 0x55555550
 * @warning This function cannot be interrupted. The core must be in the
 * secure state.
 *****************************************************************************/
#if ((IEC60370_CPU == IEC60370_CM33) && defined(__TZ_PRESENT)                  \
     && (__TZ_PRESENT == 1))                                                   \
    && defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
iec60730_TestResult_t iec60730_CpuRegistersMSPLim_S(void)
{
  iec60730_TestResult_t result;

  __asm volatile("   CPSID i  \n"             /*Disable IRQ Interrupts*/
                 "   MRS R3, CONTROL      \n" /* Save Control value */
                 "   MRS R0, MSPLIM   \n"     /* Save stack value */
                 "   MOVW R1, #0xAAA8   \n"
                 "   MOVT R1, #0xAAAA   \n"
                 "   MSR MSPLIM, R1   \n" /* load stack value */
#ifndef IAR_TESTING                       /* GCC */
                 "IEC60730_CPU_REGS_MSPLIM_S_ASM_BKPT: \n"
#else
                 "IEC60730_CPU_REGS_MSPLIM_S_ASM_BKPT:: \n"
#endif
                 "   MRS R2, MSPLIM   \n" /* Get back stack value */
                 "   CMP R2, R1   \n"     /* Verify value */
                 "   BNE iec60730_FailEndlessLoopMSPLim_S   \n"
                 "   MOVW R1, #0x5550   \n"
                 "   MOVT R1, #0x5555   \n"
                 "   MSR MSPLIM, R1   \n" /* load stack value */
                 "   MRS R2, MSPLIM   \n" /* Get back stack value */
                 "   CMP R2, R1   \n"     /* Verify value */
                 "   BNE iec60730_FailEndlessLoopMSPLim_S   \n"
                 "   MSR MSPLIM, R0   \n"  /* Restore stack value */
                 "   MSR CONTROL, R3   \n" /* Restore Control value */
                 "   ISB             \n"

                 "   B IEC60730_CPU_REGS_MSPLIM_S_PASS_ASM_BKPT   \n"
#ifndef IAR_TESTING /* GCC */
                 "iec60730_FailEndlessLoopMSPLim_S: \n"
#else
                 "iec60730_FailEndlessLoopMSPLim_S:: \n"
#endif
                 "   LDR R3,=iec60730_FailEndlessLoop \n"
                 "   BX R3   \n"

#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_MSPLIM_S_PASS_ASM_BKPT: \n"
#else
                 "IEC60730_CPU_REGS_MSPLIM_S_PASS_ASM_BKPT:: \n"
#endif
                 "   MOVS %0, #0x1      \n" /* Return. */
                 "   CPSIE i  \n"           /*Enable IRQ Interrupts*/
                 : "=r"(result)::"memory");

  return result;
}
#endif

/**************************************************************************/ /**
 * private IEC60730 CPU Register PSPLIM Non-Secure Check
 *
 * @returns #iec60730_TestResult_t
 *          #iec60730_TestPassed means test passed.
 *
 * This function tests the PSPLIM_NS (Process Stack Pointer Limit, Non-Secure)
 * register. If PSPLIM_NS is corrupted, the function stucks in an endless loop
 * with interrupts disabled. This state must be observed by another safety
 * mechanism (for example, watchdog).
 * Test patterns: 0xAAAAAAA8, 0x55555550
 * @warning This function cannot be interrupted. The core must be in the
 * secure state.
 *****************************************************************************/
#if ((IEC60370_CPU == IEC60370_CM33) && defined(__TZ_PRESENT)                  \
     && (__TZ_PRESENT == 1))                                                   \
    && defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
iec60730_TestResult_t iec60730_CpuRegistersPSPLim_NS(void)
{
  iec60730_TestResult_t result;

  __asm volatile("   CPSID i  \n"             /*Disable IRQ Interrupts*/
                 "   MRS R3, CONTROL_NS   \n" /* Save Control value */
                 "   MRS R0, PSPLIM_NS   \n"  /* Save stack value */
                 "   MOVW R1, #0xAAA8   \n"
                 "   MOVT R1, #0xAAAA   \n"
                 "   MSR PSPLIM_NS, R1   \n" /* load stack value */
#ifndef IAR_TESTING                          /* GCC */
                 "IEC60730_CPU_REGS_PSPLIM_NS_ASM_BKPT: \n"
#else
                 "IEC60730_CPU_REGS_PSPLIM_NS_ASM_BKPT:: \n"
#endif
                 "   MRS R2, PSPLIM_NS   \n" /* Get back process stack value */
                 "   CMP R2, R1   \n"        /* Verify value */
                 "   BNE iec60730_FailEndlessLoopPSPLim_NS   \n"
                 "   MOVW R1, #0x5550   \n"
                 "   MOVT R1, #0x5555   \n"
                 "   MSR PSPLIM_NS, R1   \n" /* load stack value */
                 "   MRS R2, PSPLIM_NS   \n" /* Get back stack value */
                 "   CMP R2, R1   \n"        /* Verify value */
                 "   BNE iec60730_FailEndlessLoopPSPLim_NS   \n"
                 "   MSR PSPLIM_NS, R0   \n"  /* Restore stack value */
                 "   MSR CONTROL_NS, R3   \n" /* Restore Control value */
                 "   ISB             \n"

                 "   B IEC60730_CPU_REGS_PSPLIM_NS_PASS_ASM_BKPT   \n"
#ifndef IAR_TESTING /* GCC */
                 "iec60730_FailEndlessLoopPSPLim_NS: \n"
#else
                 "iec60730_FailEndlessLoopPSPLim_NS:: \n"
#endif
                 "   LDR R3,=iec60730_FailEndlessLoop \n"
                 "   BX R3   \n"

#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_PSPLIM_NS_PASS_ASM_BKPT: \n"
#else
                 "IEC60730_CPU_REGS_PSPLIM_NS_PASS_ASM_BKPT:: \n"
#endif
                 "   MOVS %0, #0x1      \n" /* Return. */
                 "   CPSIE i  \n"           /*Enable IRQ Interrupts*/
                 : "=r"(result)::"memory");

  return result;
}
#endif

/**************************************************************************/ /**
 * private IEC60730 CPU Register PSPLIM Secure Check
 *
 * @returns #iec60730_TestResult_t
 *          #iec60730_TestPassed means test passed.
 *
 * This function tests the PSPLIM_S (Process Stack Pointer Limit, Secure)
 * register. If PSPLIM_S is corrupted, the function stucks in an endless loop
 * with interrupts disabled. This state must be observed by another safety
 * mechanism (for example, watchdog).
 * Test patterns: 0xAAAAAAA8, 0x55555550
 * @warning This function cannot be interrupted. The core must be in the
 * secure state.
 *****************************************************************************/
#if ((IEC60370_CPU == IEC60370_CM33) && defined(__TZ_PRESENT)                  \
     && (__TZ_PRESENT == 1))                                                   \
    && defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
iec60730_TestResult_t iec60730_CpuRegistersPSPLim_S(void)
{
  iec60730_TestResult_t result;

  __asm volatile("   CPSID i  \n"            /*Disable IRQ Interrupts*/
                 "   MRS R3, CONTROL     \n" /* Save Control value */
                 "   MRS R0, PSPLIM   \n"    /* Save process stack value */
                 "   MOVW R1, #0xAAA8   \n"
                 "   MOVT R1, #0xAAAA   \n"
                 "   MSR PSPLIM, R1   \n" /* load process stack value */
#ifndef IAR_TESTING                       /* GCC */
                 "IEC60730_CPU_REGS_PSPLIM_S_ASM_BKPT: \n"
#else
                 "IEC60730_CPU_REGS_PSPLIM_S_ASM_BKPT:: \n"
#endif
                 "   MRS R2, PSPLIM   \n" /* Get back process stack value */
                 "   CMP R2, R1   \n"     /* Verify value */
                 "   BNE iec60730_FailEndlessLoopPSPLim_S   \n"
                 "   MOVW R1, #0x5550   \n"
                 "   MOVT R1, #0x5555   \n"
                 "   MSR PSPLIM, R1   \n" /* load process stack value */
                 "   MRS R2, PSPLIM   \n" /* Get back process stack value */
                 "   CMP R2, R1   \n"     /* Verify value */
                 "   BNE iec60730_FailEndlessLoopPSPLim_S   \n"
                 "   MSR PSPLIM, R0   \n"  /* Restore process stack value */
                 "   MSR CONTROL, R3   \n" /* Restore Control value */
                 "   ISB             \n"

                 "   B IEC60730_CPU_REGS_PSPLIM_S_PASS_ASM_BKPT   \n"
#ifndef IAR_TESTING /* GCC */
                 "iec60730_FailEndlessLoopPSPLim_S: \n"
#else
                 "iec60730_FailEndlessLoopPSPLim_S:: \n"
#endif
                 "   LDR R3,=iec60730_FailEndlessLoop \n"
                 "   BX R3   \n"

#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_PSPLIM_S_PASS_ASM_BKPT: \n"
#else
                 "IEC60730_CPU_REGS_PSPLIM_S_PASS_ASM_BKPT:: \n"
#endif
                 "   MOVS %0, #0x1      \n" /* Return. */
                 "   CPSIE i  \n"           /*Enable IRQ Interrupts*/
                 : "=r"(result)::"memory");

  return result;
}
#endif

/**************************************************************************/ /**
 * private IEC60730 CPU Register Control Non-Secure Check
 *
 * @returns #iec60730_TestResult_t
 *          #iec60730_TestFailed means test failed,
 *          #iec60730_TestPassed means test passed.
 *
 * This function tests the Control_NS (Control, Non-Secure) register.
 * Test patterns: 0x00000002, 0x00000004
 * @warning This function cannot be interrupted. The core must be in the
 * secure state.
 *****************************************************************************/
#if ((IEC60370_CPU == IEC60370_CM33) && defined(__TZ_PRESENT)                  \
     && (__TZ_PRESENT == 1))                                                   \
    && defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
iec60730_TestResult_t iec60730_CpuRegistersControl_NS(void)
{
  iec60730_TestResult_t result;

  __asm volatile("   CPSID i  \n" /*Disable IRQ Interrupts*/
                 "   MRS R0, CONTROL_NS    \n"
                 "   MOVS R1, #0x2      \n"
                 "   MSR CONTROL_NS, R1    \n"
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_CONTROL_NS_SPSEL_ASM_BKPT: \n"
#else
                 "IEC60730_CPU_REGS_CONTROL_NS_SPSEL_ASM_BKPT:: \n"
#endif
                 "   MRS R2, CONTROL_NS   \n"
                 "   CMP R2, R1   \n"
                 "   BNE IEC60730_CPU_REGS_CONTROL_NS_FAIL   \n"
                 "   MOVW R1, #0x4   \n"
                 "   MSR CONTROL_NS, R1   \n"
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_CONTROL_NS_FPCA_ASM_BKPT: \n"
#else
                 "IEC60730_CPU_REGS_CONTROL_NS_FPCA_ASM_BKPT:: \n"
#endif
                 "   MRS R2, CONTROL_NS   \n"
                 "   CMP R2, R1   \n"
                 "   BNE IEC60730_CPU_REGS_CONTROL_NS_FAIL   \n"
                 "   MSR CONTROL_NS, R0   \n"
                 "   ISB             \n"
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_CONTROL_NS_PASS_ASM_BKPT: \n"
#else
                 "IEC60730_CPU_REGS_CONTROL_NS_PASS_ASM_BKPT:: \n"
#endif
                 "   MOVS %0, #0x1      \n"
                 "   B IEC60730_CPU_REGS_CONTROL_NS_DONE      \n"

#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_CONTROL_NS_FAIL:          \n"
#else
                 "IEC60730_CPU_REGS_CONTROL_NS_FAIL::          \n"
#endif
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_CONTROL_NS_FAIL_ASM_BKPT: \n"
#else
                 "IEC60730_CPU_REGS_CONTROL_NS_FAIL_ASM_BKPT:: \n"
#endif
                 "   MSR CONTROL_NS, R0   \n"
                 "   ISB             \n"
                 "   MOVS %0, #0x0       \n"
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_CONTROL_NS_DONE:\n"
#else
                 "IEC60730_CPU_REGS_CONTROL_NS_DONE::\n"
#endif
                 "   CPSIE i  \n" /*Enable IRQ Interrupts*/
                 : "=r"(result)::"memory");

  return result;
}
#endif

/**************************************************************************/ /**
 * private IEC60730 CPU Register Control Secure Check
 *
 * @returns #iec60730_TestResult_t
 *          #iec60730_TestFailed means test failed,
 *          #iec60730_TestPassed means test passed.
 *
 * This function tests the Control_S (Control, Secure) register.
 * Test patterns: 0x0000000A, 0x00000004
 * @warning This function cannot be interrupted. The core must be in the
 * secure state.
 *****************************************************************************/
#if ((IEC60370_CPU == IEC60370_CM33) && defined(__TZ_PRESENT)                  \
     && (__TZ_PRESENT == 1))                                                   \
    && defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
iec60730_TestResult_t iec60730_CpuRegistersControl_S(void)
{
  iec60730_TestResult_t result;

  __asm volatile("   CPSID i  \n" /*Disable IRQ Interrupts*/
                 "   MRS R0, CONTROL    \n"
                 "   MOVW R1, #0x000A      \n"
                 "   MSR CONTROL, R1    \n"
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_CONTROL_S_SPSEL_ASM_BKPT: \n"
#else
                 "IEC60730_CPU_REGS_CONTROL_S_SPSEL_ASM_BKPT:: \n"
#endif
                 "   MRS R2, CONTROL   \n"
                 "   CMP R2, R1   \n"
                 "   BNE IEC60730_CPU_REGS_CONTROL_S_FAIL   \n"
                 "   MOVW R1, #0x4   \n"
                 "   MSR CONTROL, R1   \n"
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_CONTROL_S_FPCA_ASM_BKPT: \n"
#else
                 "IEC60730_CPU_REGS_CONTROL_S_FPCA_ASM_BKPT:: \n"
#endif
                 "   MRS R2, CONTROL   \n"
                 "   CMP R2, R1   \n"
                 "   BNE IEC60730_CPU_REGS_CONTROL_S_FAIL   \n"
                 "   MSR CONTROL, R0   \n"
                 "   ISB             \n"
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_CONTROL_S_PASS_ASM_BKPT: \n"
#else
                 "IEC60730_CPU_REGS_CONTROL_S_PASS_ASM_BKPT:: \n"
#endif
                 "   MOVS %0, #0x1      \n"
                 "   B IEC60730_CPU_REGS_CONTROL_S_DONE      \n"

#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_CONTROL_S_FAIL:          \n"
#else
                 "IEC60730_CPU_REGS_CONTROL_S_FAIL::          \n"
#endif
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_CONTROL_S_FAIL_ASM_BKPT: \n"
#else
                 "IEC60730_CPU_REGS_CONTROL_S_FAIL_ASM_BKPT:: \n"
#endif
                 "   MSR CONTROL, R0   \n"
                 "   ISB             \n"
                 "   MOVS %0, #0x0       \n"
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_CONTROL_S_DONE:\n"
#else
                 "IEC60730_CPU_REGS_CONTROL_S_DONE::\n"
#endif
                 "   CPSIE i  \n" /*Enable IRQ Interrupts*/
                 : "=r"(result)::"memory");

  return result;
}
#endif

/**************************************************************************/ /**
 * private IEC60730 CPU Register Control Check
 *
 * @returns #iec60730_TestResult_t
 *          #iec60730_TestFailed means test failed,
 *          #iec60730_TestPassed means test passed.
 *
 * This function tests the Control register.
 * Test patterns: 0x00000002, 0x00000004
 * @warning This function cannot be interrupted.
 *****************************************************************************/
#if (IEC60370_CPU == IEC60370_CM4)
iec60730_TestResult_t iec60730_CpuRegistersControl(void)
{
  iec60730_TestResult_t result;

  __asm volatile("   CPSID i  \n" /*Disable IRQ Interrupts*/
                 "   MRS R0, CONTROL    \n"
                 "   MOVW R1, #0x2      \n"
                 "   MSR CONTROL, R1    \n"
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_CONTROL_S_SPSEL_ASM_BKPT: \n"
#else
                 "IEC60730_CPU_REGS_CONTROL_S_SPSEL_ASM_BKPT:: \n"
#endif
                 "   MRS R2, CONTROL   \n"
                 "   CMP R2, R1   \n"
                 "   BNE IEC60730_CPU_REGS_CONTROL_S_FAIL   \n"
                 "   MOVW R1, #0x4   \n"
                 "   MSR CONTROL, R1   \n"
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_CONTROL_S_FPCA_ASM_BKPT: \n"
#else
                 "IEC60730_CPU_REGS_CONTROL_S_FPCA_ASM_BKPT:: \n"
#endif
                 "   MRS R2, CONTROL   \n"
                 "   CMP R2, R1   \n"
                 "   BNE IEC60730_CPU_REGS_CONTROL_S_FAIL   \n"
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_CONTROL_S_PASS_ASM_BKPT: \n"
#else
                 "IEC60730_CPU_REGS_CONTROL_S_PASS_ASM_BKPT:: \n"
#endif
                 "   MSR CONTROL, R0   \n"
                 "   MOVS %0, #0x1      \n"
                 "   B IEC60730_CPU_REGS_CONTROL_S_DONE      \n"
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_CONTROL_S_FAIL:          \n"
#else
                 "IEC60730_CPU_REGS_CONTROL_S_FAIL::          \n"
#endif
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_CONTROL_S_FAIL_ASM_BKPT: \n"
#else
                 "IEC60730_CPU_REGS_CONTROL_S_FAIL_ASM_BKPT:: \n"
#endif
                 "   MSR CONTROL, R0   \n"
                 "   MOVS %0, #0x0       \n"
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_CONTROL_S_DONE:\n"
#else
                 "IEC60730_CPU_REGS_CONTROL_S_DONE::\n"
#endif
                 "   CPSIE i  \n" /*Enable IRQ Interrupts*/
                 : "=r"(result)::"memory");

  return result;
}
#endif

/**************************************************************************/ /**
 * private IEC60730 CPU Register PriMask Non-Secure Check
 *
 * @returns #iec60730_TestResult_t
 *          #iec60730_TestFailed means test failed,
 *          #iec60730_TestPassed means test passed.
 *
 * This function tests the PriMask_NS (PriMask, Non-Secure) register.
 * Test patterns: 0x00000001, 0x00000000
 * @warning This function cannot be interrupted. The core must be in the
 * secure state.
 *****************************************************************************/
#if ((IEC60370_CPU == IEC60370_CM33) && defined(__TZ_PRESENT)                  \
     && (__TZ_PRESENT == 1))                                                   \
    && defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
iec60730_TestResult_t iec60730_CpuRegistersPriMask_NS(void)
{
  iec60730_TestResult_t result;

  __asm volatile("   CPSID i  \n" /*Disable IRQ Interrupts*/
                 "   MRS R0, PRIMASK_NS    \n"
                 "   MOVW R1, #0x0001      \n"
                 "   MSR PRIMASK_NS, R1    \n"
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_PRIMASK_NS_ASM_BKPT: \n"
#else
                 "IEC60730_CPU_REGS_PRIMASK_NS_ASM_BKPT:: \n"
#endif
                 "   MRS R2, PRIMASK_NS   \n"
                 "   CMP R2, R1   \n"
                 "   BNE IEC60730_CPU_REGS_PRIMASK_NS_FAIL   \n"
                 "   MOVW R1, #0x0000   \n"
                 "   MSR PRIMASK_NS, R1   \n"
                 "   MRS R2, PRIMASK_NS   \n"
                 "   CMP R2, R1   \n"
                 "   BNE IEC60730_CPU_REGS_PRIMASK_NS_FAIL   \n"
                 "   MSR PRIMASK_NS, R0   \n"
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_PRIMASK_NS_PASS_ASM_BKPT: \n"
#else
                 "IEC60730_CPU_REGS_PRIMASK_NS_PASS_ASM_BKPT:: \n"
#endif
                 "   MOVS %0, #0x1      \n"
                 "   B IEC60730_CPU_REGS_PRIMASK_NS_DONE      \n"

#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_PRIMASK_NS_FAIL:          \n"
#else
                 "IEC60730_CPU_REGS_PRIMASK_NS_FAIL::          \n"
#endif
                 "   MSR PRIMASK_NS, R0   \n"
                 "   MOVS %0, #0x0       \n"
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_PRIMASK_NS_DONE:\n"
#else
                 "IEC60730_CPU_REGS_PRIMASK_NS_DONE:\n"
#endif
                 "   CPSIE i  \n" /*Enable IRQ Interrupts*/
                 : "=r"(result)::"memory");

  return result;
}
#endif

/**************************************************************************/ /**
 * private IEC60730 CPU Register PriMask Secure Check
 *
 * @returns #iec60730_TestResult_t
 *          #iec60730_TestFailed means test failed,
 *          #iec60730_TestPassed means test passed.
 *
 * This function tests the PriMask_S (PriMask, Secure) register.
 * Test patterns: 0x00000001, 0x00000000
 * @warning This function cannot be interrupted. The core must be in the
 * secure state.
 *****************************************************************************/
#if ((IEC60370_CPU == IEC60370_CM33) && defined(__TZ_PRESENT)                  \
     && (__TZ_PRESENT == 1))                                                   \
    && defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
iec60730_TestResult_t iec60730_CpuRegistersPriMask_S(void)
{
  iec60730_TestResult_t result;

  __asm volatile("   CPSID i  \n" /*Disable IRQ Interrupts*/
                 "   MRS R0, PRIMASK    \n"
                 "   MOVW R1, #0x0001      \n"
                 "   MSR PRIMASK, R1    \n"
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_PRIMASK_S_ASM_BKPT: \n"
#else
                 "IEC60730_CPU_REGS_PRIMASK_S_ASM_BKPT:: \n"
#endif
                 "   MRS R2, PRIMASK   \n"
                 "   CMP R2, R1   \n"
                 "   BNE IEC60730_CPU_REGS_PRIMASK_S_FAIL   \n"
                 "   MOVW R1, #0x0000   \n"
                 "   MSR PRIMASK, R1   \n"
                 "   MRS R2, PRIMASK   \n"
                 "   CMP R2, R1   \n"
                 "   BNE IEC60730_CPU_REGS_PRIMASK_S_FAIL   \n"
                 "   MSR PRIMASK, R0   \n"
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_PRIMASK_S_PASS_ASM_BKPT: \n"
#else
                 "IEC60730_CPU_REGS_PRIMASK_S_PASS_ASM_BKPT:: \n"
#endif
                 "   MOVS %0, #0x1      \n"
                 "   B IEC60730_CPU_REGS_PRIMASK_S_DONE      \n"
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_PRIMASK_S_FAIL:          \n"
#else
                 "IEC60730_CPU_REGS_PRIMASK_S_FAIL::          \n"
#endif
                 "   MSR PRIMASK, R0   \n"
                 "   MOVS %0, #0x0       \n"
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_PRIMASK_S_DONE:\n"
#else
                 "IEC60730_CPU_REGS_PRIMASK_S_DONE::\n"
#endif
                 "   CPSIE i  \n" /*Enable IRQ Interrupts*/
                 : "=r"(result)::"memory");

  return result;
}
#endif

/**************************************************************************/ /**
 * private IEC60730 CPU Register PriMask Check
 *
 * @returns #iec60730_TestResult_t
 *          #iec60730_TestFailed means test failed,
 *          #iec60730_TestPassed means test passed.
 *
 * This function tests the PriMask register.
 * Test patterns: 0x00000001, 0x00000000
 * @warning This function cannot be interrupted.
 *****************************************************************************/
#if (IEC60370_CPU == IEC60370_CM4)
iec60730_TestResult_t iec60730_CpuRegistersPriMask(void)
{
  iec60730_TestResult_t result;

  __asm volatile("   CPSID i  \n" /*Disable IRQ Interrupts*/
                 "   MRS R0, PRIMASK    \n"
                 "   MOVW R1, #0x0001      \n"
                 "   MSR PRIMASK, R1    \n"
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_PRIMASK_S_ASM_BKPT: \n"
#else
                 "IEC60730_CPU_REGS_PRIMASK_S_ASM_BKPT:: \n"
#endif
                 "   MRS R2, PRIMASK   \n"
                 "   CMP R2, R1   \n"
                 "   BNE IEC60730_CPU_REGS_PRIMASK_S_FAIL   \n"
                 "   MOVW R1, #0x0000   \n"
                 "   MSR PRIMASK, R1   \n"
                 "   MRS R2, PRIMASK   \n"
                 "   CMP R2, R1   \n"
                 "   BNE IEC60730_CPU_REGS_PRIMASK_S_FAIL   \n"
                 "   MSR PRIMASK, R0   \n"
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_PRIMASK_S_PASS_ASM_BKPT: \n"
#else
                 "IEC60730_CPU_REGS_PRIMASK_S_PASS_ASM_BKPT:: \n"
#endif
                 "   MOVS %0, #0x1      \n"
                 "   B IEC60730_CPU_REGS_PRIMASK_S_DONE      \n"
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_PRIMASK_S_FAIL:          \n"
#else
                 "IEC60730_CPU_REGS_PRIMASK_S_FAIL::          \n"
#endif
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_PRIMASK_S_FAIL_ASM_BKPT: \n"
#else
                 "IEC60730_CPU_REGS_PRIMASK_S_FAIL_ASM_BKPT:: \n"
#endif
                 "   MSR PRIMASK, R0   \n"
                 "   MOVS %0, #0x0       \n"
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_PRIMASK_S_DONE:\n"
#else
                 "IEC60730_CPU_REGS_PRIMASK_S_DONE::\n"
#endif
                 "   CPSIE i  \n" /*Enable IRQ Interrupts*/
                 : "=r"(result)::"memory");

  return result;
}
#endif

/**************************************************************************/ /**
 * private IEC60730 CPU Register BasePri Non-Secure Check
 *
 * @returns #iec60730_TestResult_t
 *          #iec60730_TestFailed means test failed,
 *          #iec60730_TestPassed means test passed.
 *
 * This function tests the BASEPRI_NS (BasePri, Non-Secure) register.
 * Test patterns: 0x000000A0, 0x00000040
 * @warning This function cannot be interrupted. The core must be in the
 * secure state.
 *****************************************************************************/
#if ((IEC60370_CPU == IEC60370_CM33) && defined(__TZ_PRESENT)                  \
     && (__TZ_PRESENT == 1))                                                   \
    && defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
iec60730_TestResult_t iec60730_CpuRegistersBasePri_NS(void)
{
  iec60730_TestResult_t result;

  __asm volatile("   CPSID i  \n" /*Disable IRQ Interrupts*/
                 "   MRS R0, BASEPRI_NS    \n"
                 "   MOV R1, #0xA0      \n"
                 "   MSR BASEPRI_NS, R1    \n"
                 "   DSB             \n"
                 "   ISB             \n"
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_BASEPRI_NS_ASM_BKPT: \n"
#else
                 "IEC60730_CPU_REGS_BASEPRI_NS_ASM_BKPT:: \n"
#endif
                 "   MRS R2, BASEPRI_NS   \n"
                 "   CMP R2, R1   \n"
                 "   BNE IEC60730_CPU_REGS_BASEPRI_NS_FAIL   \n"
                 "   MOV R1, #0x40   \n"
                 "   MSR BASEPRI_NS, R1   \n"
                 "   DSB             \n"
                 "   ISB             \n"
                 "   MRS R2, BASEPRI_NS   \n"
                 "   CMP R2, R1   \n"
                 "   BNE IEC60730_CPU_REGS_BASEPRI_NS_FAIL   \n"
                 "   MSR BASEPRI_NS, R0   \n"
                 "   DSB             \n"
                 "   ISB             \n"
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_BASEPRI_NS_PASS_ASM_BKPT: \n"
#else
                 "IEC60730_CPU_REGS_BASEPRI_NS_PASS_ASM_BKPT:: \n"
#endif
                 "   MOVS %0, #0x1      \n"
                 "   B IEC60730_CPU_REGS_BASEPRI_NS_DONE      \n"
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_BASEPRI_NS_FAIL:          \n"
#else
                 "IEC60730_CPU_REGS_BASEPRI_NS_FAIL::          \n"
#endif
                 "   MSR BASEPRI_NS, R0   \n"
                 "   DSB             \n"
                 "   ISB             \n"
                 "   MOVS %0, #0x0       \n"
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_BASEPRI_NS_DONE:\n"
#else
                 "IEC60730_CPU_REGS_BASEPRI_NS_DONE::\n"
#endif
                 "   CPSIE i  \n" /*Enable IRQ Interrupts*/
                 : "=r"(result)::"memory");

  return result;
}
#endif

/**************************************************************************/ /**
 * private IEC60730 CPU Register BasePri Secure Check
 *
 * @returns #iec60730_TestResult_t
 *          #iec60730_TestFailed means test failed,
 *          #iec60730_TestPassed means test passed.
 *
 * This function tests the BASEPRI (BasePri, Secure) register.
 * Test patterns: 0x000000A0, 0x00000040
 * @warning This function cannot be interrupted. The core must be in the
 * secure state.
 *****************************************************************************/
#if ((IEC60370_CPU == IEC60370_CM33) && defined(__TZ_PRESENT)                  \
     && (__TZ_PRESENT == 1))                                                   \
    && defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
iec60730_TestResult_t iec60730_CpuRegistersBasePri_S(void)
{
  iec60730_TestResult_t result;

  __asm volatile("   CPSID i  \n" /*Disable IRQ Interrupts*/
                 "   MRS R0, BASEPRI    \n"
                 "   MOV R1, #0xA0      \n"
                 "   MSR BASEPRI, R1    \n"
                 "   DSB             \n"
                 "   ISB             \n"
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_BASEPRI_S_ASM_BKPT: \n"
#else
                 "IEC60730_CPU_REGS_BASEPRI_S_ASM_BKPT:: \n"
#endif
                 "   MRS R2, BASEPRI   \n"
                 "   CMP R2, R1   \n"
                 "   BNE IEC60730_CPU_REGS_BASEPRI_S_FAIL   \n"
                 "   MOV R1, #0x40   \n"
                 "   MSR BASEPRI, R1   \n"
                 "   DSB             \n"
                 "   ISB             \n"
                 "   MRS R2, BASEPRI   \n"
                 "   CMP R2, R1   \n"
                 "   BNE IEC60730_CPU_REGS_BASEPRI_S_FAIL   \n"
                 "   MSR BASEPRI, R0   \n"
                 "   DSB             \n"
                 "   ISB             \n"
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_BASEPRI_S_PASS_ASM_BKPT: \n"
#else
                 "IEC60730_CPU_REGS_BASEPRI_S_PASS_ASM_BKPT:: \n"
#endif
                 "   MOVS %0, #0x1      \n"
                 "   B IEC60730_CPU_REGS_BASEPRI_S_DONE      \n"
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_BASEPRI_S_FAIL:          \n"
#else
                 "IEC60730_CPU_REGS_BASEPRI_S_FAIL::          \n"
#endif
                 "   MSR BASEPRI, R0   \n"
                 "   DSB             \n"
                 "   ISB             \n"
                 "   MOVS %0, #0x0       \n"
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_BASEPRI_S_DONE:\n"
#else
                 "IEC60730_CPU_REGS_BASEPRI_S_DONE::\n"
#endif
                 "   CPSIE i  \n" /*Enable IRQ Interrupts*/
                 : "=r"(result)::"memory");

  return result;
}
#endif

/**************************************************************************/ /**
 * private IEC60730 CPU Register BasePri Check
 *
 * @returns #iec60730_TestResult_t
 *          #iec60730_TestFailed means test failed,
 *          #iec60730_TestPassed means test passed.
 *
 * This function tests the BASEPRI register.
 * Test patterns: 0x000000A0, 0x00000040
 * @warning This function cannot be interrupted.
 *****************************************************************************/
#if (IEC60370_CPU == IEC60370_CM4)
iec60730_TestResult_t iec60730_CpuRegistersBasePri(void)
{
  iec60730_TestResult_t result;

  __asm volatile("   CPSID i  \n" /*Disable IRQ Interrupts*/
                 "   MRS R0, BASEPRI    \n"
                 "   MOV R1, #0xA0      \n"
                 "   MSR BASEPRI, R1    \n"
                 "   DSB             \n"
                 "   ISB             \n"
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_BASEPRI_S_ASM_BKPT: \n"
#else
                 "IEC60730_CPU_REGS_BASEPRI_S_ASM_BKPT:: \n"
#endif
                 "   MRS R2, BASEPRI   \n"
                 "   CMP R2, R1   \n"
                 "   BNE IEC60730_CPU_REGS_BASEPRI_S_FAIL   \n"
                 "   MOV R1, #0x40   \n"
                 "   MSR BASEPRI, R1   \n"
                 "   DSB             \n"
                 "   ISB             \n"
                 "   MRS R2, BASEPRI   \n"
                 "   CMP R2, R1   \n"
                 "   BNE IEC60730_CPU_REGS_BASEPRI_S_FAIL   \n"
                 "   MSR BASEPRI, R0   \n"
                 "   DSB             \n"
                 "   ISB             \n"
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_BASEPRI_S_PASS_ASM_BKPT: \n"
#else
                 "IEC60730_CPU_REGS_BASEPRI_S_PASS_ASM_BKPT:: \n"
#endif
                 "   MOVS %0, #0x1      \n"
                 "   B IEC60730_CPU_REGS_BASEPRI_S_DONE      \n"
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_BASEPRI_S_FAIL:          \n"
#else
                 "IEC60730_CPU_REGS_BASEPRI_S_FAIL::          \n"
#endif
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_BASEPRI_S_FAIL_ASM_BKPT: \n"
#else
                 "IEC60730_CPU_REGS_BASEPRI_S_FAIL_ASM_BKPT:: \n"
#endif
                 "   MSR BASEPRI, R0   \n"
                 "   DSB             \n"
                 "   ISB             \n"
                 "   MOVS %0, #0x0       \n"
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_BASEPRI_S_DONE:\n"
#else
                 "IEC60730_CPU_REGS_BASEPRI_S_DONE::\n"
#endif
                 "   CPSIE i  \n" /*Enable IRQ Interrupts*/
                 : "=r"(result)::"memory");

  return result;
}
#endif

/**************************************************************************/ /**
 * private IEC60730 CPU Register FaultMask Non-Secure Check
 *
 * @returns #iec60730_TestResult_t
 *          #iec60730_TestFailed means test failed,
 *          #iec60730_TestPassed means test passed.
 *
 * This function tests the FAULTMASK_NS (FaultMask, Non-Secure) register.
 * Test patterns: 0x00000001, 0x00000000
 * @warning This function cannot be interrupted. The core must be in the
 * secure state.
 *****************************************************************************/
#if ((IEC60370_CPU == IEC60370_CM33) && defined(__TZ_PRESENT)                  \
     && (__TZ_PRESENT == 1))                                                   \
    && defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
iec60730_TestResult_t iec60730_CpuRegistersFaultMask_NS(void)
{
  iec60730_TestResult_t result;

  __asm volatile("   CPSID i  \n" /*Disable IRQ Interrupts*/
                 "   MRS R0, FAULTMASK_NS    \n"
                 "   MOV R1, #1      \n"
                 "   MSR FAULTMASK_NS, R1    \n"
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_FAULTMASK_NS_ASM_BKPT: \n"
#else
                 "IEC60730_CPU_REGS_FAULTMASK_NS_ASM_BKPT:: \n"
#endif
                 "   MRS R2, FAULTMASK_NS   \n"
                 "   CMP R2, R1   \n"
                 "   BNE IEC60730_CPU_REGS_FAULTMASK_NS_FAIL   \n"
                 "   MOV R1, #0   \n"
                 "   MSR FAULTMASK_NS, R1   \n"
                 "   MRS R2, FAULTMASK_NS   \n"
                 "   CMP R2, R1   \n"
                 "   BNE IEC60730_CPU_REGS_FAULTMASK_NS_FAIL   \n"
                 "   MSR FAULTMASK_NS, R0   \n"
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_FAULTMASK_NS_PASS_ASM_BKPT: \n"
#else
                 "IEC60730_CPU_REGS_FAULTMASK_NS_PASS_ASM_BKPT:: \n"
#endif
                 "   MOVS %0, #0x1      \n"
                 "   B IEC60730_CPU_REGS_FAULTMASK_NS_DONE      \n"
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_FAULTMASK_NS_FAIL:          \n"
#else
                 "IEC60730_CPU_REGS_FAULTMASK_NS_FAIL::          \n"
#endif
                 "   MSR FAULTMASK_NS, R0   \n"
                 "   MOVS %0, #0x0       \n"
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_FAULTMASK_NS_DONE:\n"
#else
                 "IEC60730_CPU_REGS_FAULTMASK_NS_DONE::\n"
#endif
                 "   CPSIE i  \n" /*Enable IRQ Interrupts*/
                 : "=r"(result)::"memory");

  return result;
}
#endif

/**************************************************************************/ /**
 * private IEC60730 CPU Register FaultMask Secure Check
 *
 * @returns #iec60730_TestResult_t
 *          #iec60730_TestFailed means test failed,
 *          #iec60730_TestPassed means test passed.
 *
 * This function tests the FAULTMASK (FaultMask, Secure) register.
 * Test patterns: 0x00000001, 0x00000000
 * @warning This function cannot be interrupted. The core must be in the
 * secure state.
 *****************************************************************************/
#if ((IEC60370_CPU == IEC60370_CM33) && defined(__TZ_PRESENT)                  \
     && (__TZ_PRESENT == 1))                                                   \
    && defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
iec60730_TestResult_t iec60730_CpuRegistersFaultMask_S(void)
{
  iec60730_TestResult_t result;

  __asm volatile("   CPSID i  \n" /*Disable IRQ Interrupts*/
                 "   MRS R0, FAULTMASK    \n"
                 "   MOV R1, #1      \n"
                 "   MSR FAULTMASK, R1    \n"
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_FAULTMASK_S_ASM_BKPT: \n"
#else
                 "IEC60730_CPU_REGS_FAULTMASK_S_ASM_BKPT:: \n"
#endif
                 "   MRS R2, FAULTMASK   \n"
                 "   CMP R2, R1   \n"
                 "   BNE IEC60730_CPU_REGS_FAULTMASK_S_FAIL   \n"
                 "   MOV R1, #0   \n"
                 "   MSR FAULTMASK, R1   \n"
                 "   MRS R2, FAULTMASK   \n"
                 "   CMP R2, R1   \n"
                 "   BNE IEC60730_CPU_REGS_FAULTMASK_S_FAIL   \n"
                 "   MSR FAULTMASK, R0   \n"
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_FAULTMASK_S_PASS_ASM_BKPT: \n"
#else
                 "IEC60730_CPU_REGS_FAULTMASK_S_PASS_ASM_BKPT:: \n"
#endif
                 "   MOVS %0, #0x1      \n"
                 "   B IEC60730_CPU_REGS_FAULTMASK_S_DONE      \n"
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_FAULTMASK_S_FAIL:          \n"
#else
                 "IEC60730_CPU_REGS_FAULTMASK_S_FAIL::          \n"
#endif
                 "   MSR FAULTMASK, R0   \n"
                 "   MOVS %0, #0x0       \n"
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_FAULTMASK_S_DONE:\n"
#else
                 "IEC60730_CPU_REGS_FAULTMASK_S_DONE::\n"
#endif
                 "   CPSIE i  \n" /*Enable IRQ Interrupts*/
                 : "=r"(result)::"memory");

  return result;
}
#endif

/**************************************************************************/ /**
 * private IEC60730 CPU Register FaultMask Check
 *
 * @returns #iec60730_TestResult_t
 *          #iec60730_TestFailed means test failed,
 *          #iec60730_TestPassed means test passed.
 *
 * This function tests the FAULTMASK register.
 * Test patterns: 0x00000001, 0x00000000
 * @warning This function cannot be interrupted.
 *****************************************************************************/
#if (IEC60370_CPU == IEC60370_CM4)
iec60730_TestResult_t iec60730_CpuRegistersFaultMask(void)
{
  iec60730_TestResult_t result;

  __asm volatile("   CPSID i  \n" /*Disable IRQ Interrupts*/
                 "   MRS R0, FAULTMASK    \n"
                 "   MOV R1, #1      \n"
                 "   MSR FAULTMASK, R1    \n"
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_FAULTMASK_S_ASM_BKPT: \n"
#else
                 "IEC60730_CPU_REGS_FAULTMASK_S_ASM_BKPT:: \n"
#endif
                 "   MRS R2, FAULTMASK   \n"
                 "   CMP R2, R1   \n"
                 "   BNE IEC60730_CPU_REGS_FAULTMASK_S_FAIL   \n"
                 "   MOV R1, #0   \n"
                 "   MSR FAULTMASK, R1   \n"
                 "   MRS R2, FAULTMASK   \n"
                 "   CMP R2, R1   \n"
                 "   BNE IEC60730_CPU_REGS_FAULTMASK_S_FAIL   \n"
                 "   MSR FAULTMASK, R0   \n"
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_FAULTMASK_S_PASS_ASM_BKPT: \n"
#else
                 "IEC60730_CPU_REGS_FAULTMASK_S_PASS_ASM_BKPT:: \n"
#endif
                 "   MOVS %0, #0x1      \n"
                 "   B IEC60730_CPU_REGS_FAULTMASK_S_DONE      \n"
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_FAULTMASK_S_FAIL:          \n"
#else
                 "IEC60730_CPU_REGS_FAULTMASK_S_FAIL::          \n"
#endif
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_FAULTMASK_S_FAIL_ASM_BKPT: \n"
#else
                 "IEC60730_CPU_REGS_FAULTMASK_S_FAIL_ASM_BKPT:: \n"
#endif
                 "   MSR FAULTMASK, R0   \n"
                 "   MOVS %0, #0x0       \n"
#ifndef IAR_TESTING /* GCC */
                 "IEC60730_CPU_REGS_FAULTMASK_S_DONE:\n"
#else
                 "IEC60730_CPU_REGS_FAULTMASK_S_DONE::\n"
#endif
                 "   CPSIE i  \n" /*Enable IRQ Interrupts*/
                 : "=r"(result)::"memory");

  return result;
}
#endif

#if ((defined(__FPU_PRESENT) && (__FPU_PRESENT == 1U))                         \
     && (defined(__FPU_USED) && (__FPU_USED == 1U)))
/**************************************************************************/ /**
 * private IEC60730 FPU Register FPSCR Check
 *
 * @returns #iec60730_TestResult_t
 *          #iec60730_TestFailed means test failed,
 *          #iec60730_TestPassed means test passed.
 *
 * This function tests the FPSCR (Floating-point Status and Control) register.
 * Test patterns: 0x55400015, 0xA280008A
 * @warning The core must be in the secure state.Only for devices with the
 * Floating Point Unit (FPU).
 *****************************************************************************/
iec60730_TestResult_t iec60730_CpuRegistersFPU_FPSCR(void)
{
  iec60730_TestResult_t result = iec60730_TestPassed;

#if ((IEC60370_CPU == IEC60370_CM33) && defined(__TZ_PRESENT)                  \
     && (__TZ_PRESENT == 1))                                                   \
    && defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  __asm volatile(
      "   CPSID i  \n" /*Disable IRQ Interrupts*/
      "   STMDB SP!, {R4, R5, R6} \n"
      "   LDR R0, =0xE000ED88\n"
      "   LDR R5, [R0, #0] \n" /* Save CPACR to R5 */
      "   LDR R0, =0xE000EF34\n"
      "   LDR R6, [R0, #0] \n"        /* Save FPCCR to R6 */
      "   VMRS R4, FPSCR     \n"      /* Save FPSCR register to R4 */
      "   MOV R1, R6 \n"              /* Copy FPCCR to R1 */
      "   ORR R1, R1, #0xC0000000 \n" /* Set ASPEN_MASK and LSPEN_MASK */
      "   STR R1, [R0, #0] \n"        /* Write back to FPCCR */
      "   MOV R1, R5 \n"              /* Load CPACR value from R5 */
      "   ORR R1, R1, #0xF00000 \n"   /* Enable FPU on CPACR */
      "   LDR R0, =0xE000ED88\n"
      "   STR R1, [R0, #0] \n" /* Write back to CPACR */

      "   MOVW R1, #0x0015   \n"
      "   MOVT R1, #0x5540   \n"
      "   VMSR FPSCR, R1   \n" /* load process stack value */
#ifndef IAR_TESTING            /* GCC */
      "IEC60730_CPU_REGS_FPU_FPSCR_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_FPU_FPSCR_ASM_BKPT:: \n"
#endif
      "   VMRS R2, FPSCR   \n" /* Get back process stack value */
      "   CMP R2, R1   \n"     /* Verify value */
      "   BNE IEC60730_CPU_REGS_FPU_FPSCR_FAIL   \n"
      "   MOVW R1, #0x008A   \n"
      "   MOVT R1, #0xA280   \n"
      "   VMSR FPSCR, R1   \n"
      "   VMRS R2, FPSCR   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_FPSCR_FAIL   \n"

#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_FPSCR_PASS_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_FPU_FPSCR_PASS_ASM_BKPT:: \n"
#endif
      "   MOVS %0, #0x1      \n"
      "   B IEC60730_CPU_REGS_FPU_FPSCR_DONE      \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_FPSCR_FAIL:          \n"
#else
      "IEC60730_CPU_REGS_FPU_FPSCR_FAIL::          \n"
#endif
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_FPSCR_FAIL_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_FPU_FPSCR_FAIL_ASM_BKPT:: \n"
#endif
      "   MOVS %0, #0x0       \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_FPSCR_DONE:\n"
#else
      "IEC60730_CPU_REGS_FPU_FPSCR_DONE::\n"
#endif
      "   LDR R1, =0xE000ED88\n"
      "   STR R5, [R1, #0] \n" /* Restore CPACR */
      "   LDR R1, =0xE000EF34\n"
      "   STR R6, [R1, #0] \n" /* Restore FPCCR */
      "   VMSR FPSCR, R4   \n" /* Restore FPSCR */
      "   LDMIA SP!, {R4, R5, R6}   \n"
      "   CPSIE i  \n" /*Enable IRQ Interrupts*/
      : "=r"(result)::"memory");
#endif

#if (IEC60370_CPU == IEC60370_CM4)
  __asm volatile(
      "   CPSID i  \n" /*Disable IRQ Interrupts*/
      "   STMDB SP!, {R4, R5, R6} \n"
      "   MOVW R1, #0x0004      \n"
      "   MSR CONTROL, R1    \n"
      "   LDR.W R0, =0xE000ED88\n"
      "   LDR R5, [R0, #0] \n" /* Save CPACR to R5 */
      "   LDR R0, =0xE000EF34\n"
      "   LDR R6, [R0, #0] \n"        /* Save FPCCR to R6 */
      "   VMRS R4, FPSCR     \n"      /* Save FPSCR register to R4 */
      "   MOV R1, R6 \n"              /* Copy FPCCR to R1 */
      "   ORR R1, R1, #0xC0000000 \n" /* Set ASPEN_MASK and LSPEN_MASK */
      "   STR R1, [R0, #0] \n"        /* Write back to FPCCR */
      "   MOV R1, R5 \n"              /* Load CPACR value from R5 */
      "   ORR R1, R1, #0xF00000 \n"   /* Enable FPU on CPACR */
      "   LDR R0, =0xE000ED88\n"
      "   STR R1, [R0, #0] \n" /* Write back to CPACR */

      "   MOVW R1, #0x0015   \n"
      "   MOVT R1, #0x5540   \n"
      "   VMSR FPSCR, R1   \n" /* load process stack value */
#ifndef IAR_TESTING            /* GCC */
      "IEC60730_CPU_REGS_FPU_FPSCR_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_FPU_FPSCR_ASM_BKPT:: \n"
#endif
      "   VMRS R2, FPSCR   \n" /* Get back process stack value */
      "   CMP R2, R1   \n"     /* Verify value */
      "   BNE IEC60730_CPU_REGS_FPU_FPSCR_FAIL   \n"
      "   MOVW R1, #0x008A   \n"
      "   MOVT R1, #0xA280   \n"
      "   VMSR FPSCR, R1   \n"
      "   VMRS R2, FPSCR   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_FPSCR_FAIL   \n"

#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_FPSCR_PASS_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_FPU_FPSCR_PASS_ASM_BKPT:: \n"
#endif
      "   MOVS %0, #0x1      \n"
      "   B IEC60730_CPU_REGS_FPU_FPSCR_DONE      \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_FPSCR_FAIL:          \n"
#else
      "IEC60730_CPU_REGS_FPU_FPSCR_FAIL::          \n"
#endif
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_FPSCR_FAIL_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_FPU_FPSCR_FAIL_ASM_BKPT:: \n"
#endif
      "   MOVS %0, #0x0       \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_FPSCR_DONE:\n"
#else
      "IEC60730_CPU_REGS_FPU_FPSCR_DONE::\n"
#endif
      "   LDR R1, =0xE000ED88\n"
      "   STR R5, [R1, #0] \n" /* Restore CPACR */
      "   LDR R1, =0xE000EF34\n"
      "   STR R6, [R1, #0] \n" /* Restore FPCCR */
      "   VMSR FPSCR, R4   \n" /* Restore FPSCR */
      "   LDMIA SP!, {R4, R5, R6}   \n"
      "   CPSIE i  \n" /*Enable IRQ Interrupts*/
      : "=r"(result)::"memory");
#endif

  return result;
}

/**************************************************************************/ /**
 * private IEC60730 FPU Registers FPS0-FPS31 Check
 *
 * @returns #iec60730_TestResult_t
 *          #iec60730_TestFailed means test failed,
 *          #iec60730_TestPassed means test passed.
 *
 * This function tests the FPS0-FPS31 register.
 * Test patterns: 0x55555555, 0xAAAAAAAA
 * @warning The core must be in the secure state.Only for devices with the
 * Floating Point Unit (FPU).
 *****************************************************************************/
iec60730_TestResult_t iec60730_CpuRegistersFPU_FPSx(void)
{
  iec60730_TestResult_t result = iec60730_TestPassed;
#if (IEC60370_CPU == IEC60370_CM4)                                             \
    || ((IEC60370_CPU == IEC60370_CM33) && defined(__TZ_PRESENT)               \
        && (__TZ_PRESENT == 1))                                                \
           && defined(__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  __asm volatile(
      "   CPSID i  \n" /*Disable IRQ Interrupts*/
      "   STMDB SP!, {R4, R5, R6} \n"
      "   LDR.W R0, =0xE000ED88\n"
      "   LDR R5, [R0, #0] \n" /* Save CPACR to R5 */
      "   LDR.W R0, =0xE000EF34\n"
      "   LDR R6, [R0, #0] \n"        /* Save FPCCR to R6 */
      "   VMRS R4, FPSCR     \n"      /* Save FPSCR register to R4 */
      "   MOV R1, R6 \n"              /* Copy FPCCR to R1 */
      "   ORR R1, R1, #0xC0000000 \n" /* Set ASPEN_MASK and LSPEN_MASK */
      "   STR R1, [R0, #0] \n"        /* Write back to FPCCR */
      "   MOV R1, R5 \n"              /* Load CPACR value from R5 */
      "   ORR R1, R1, #0xF00000 \n"   /* Enable FPU on CPACR */
      "   LDR.W R0, =0xE000ED88\n"
      "   STR R1, [R0, #0] \n" /* Write back to CPACR */

      "   VMOV R0, S0    \n" /*S0 */
      "   MOVS R1, #0x55555555 \n"
      "   VMOV S0, R1    \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_S0_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_FPU_S0_ASM_BKPT:: \n"
#endif
      "   VMOV R2, S0   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S0_S3_FAIL   \n"
      "   MOVS R1, #0xAAAAAAAA \n"
      "   VMOV S0, R1   \n"
      "   VMOV R2, S0   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S0_S3_FAIL   \n"
      "   VMOV S0, R0   \n"

      "   VMOV R0, S1    \n" /* S1 */
      "   MOVS R1, #0x55555555 \n"
      "   VMOV S1, R1    \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_S1_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_FPU_S1_ASM_BKPT:: \n"
#endif
      "   VMOV R2, S1   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S0_S3_FAIL   \n"
      "   MOVS R1, #0xAAAAAAAA \n"
      "   VMOV S1, R1   \n"
      "   VMOV R2, S1   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S0_S3_FAIL   \n"
      "   VMOV S1, R0   \n"

      "   VMOV R0, S2    \n" /* S2 */
      "   MOVS R1, #0x55555555 \n"
      "   VMOV S2, R1    \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_S2_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_FPU_S2_ASM_BKPT:: \n"
#endif
      "   VMOV R2, S2   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S0_S3_FAIL   \n"
      "   MOVS R1, #0xAAAAAAAA \n"
      "   VMOV S2, R1   \n"
      "   VMOV R2, S2   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S0_S3_FAIL   \n"
      "   VMOV S2, R0   \n"

      "   VMOV R0, S3    \n" /* S3 */
      "   MOVS R1, #0x55555555 \n"
      "   VMOV S3, R1    \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_S3_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_FPU_S3_ASM_BKPT:: \n"
#endif
      "   VMOV R2, S3   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S0_S3_FAIL   \n"
      "   MOVS R1, #0xAAAAAAAA \n"
      "   VMOV S3, R1   \n"
      "   VMOV R2, S3   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S0_S3_FAIL   \n"
      "   VMOV S3, R0   \n"

      "   B IEC60730_CPU_REGS_FPU_S0_S3_PASS   \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_S0_S3_FAIL: \n"
#else
      "IEC60730_CPU_REGS_FPU_S0_S3_FAIL:: \n"
#endif
      "   B IEC60730_CPU_REGS_FPU_S4_S7_FAIL   \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_S0_S3_PASS: \n"
#else
      "IEC60730_CPU_REGS_FPU_S0_S3_PASS:: \n"
#endif

      "   VMOV R0, S4    \n" /* S4 */
      "   MOVS R1, #0x55555555 \n"
      "   VMOV S4, R1    \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_S4_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_FPU_S4_ASM_BKPT:: \n"
#endif
      "   VMOV R2, S4   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S4_S7_FAIL   \n"
      "   MOVS R1, #0xAAAAAAAA \n"
      "   VMOV S4, R1   \n"
      "   VMOV R2, S4   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S4_S7_FAIL   \n"
      "   VMOV S4, R0   \n"

      "   VMOV R0, S5    \n" /* S5 */
      "   MOVS R1, #0x55555555 \n"
      "   VMOV S5, R1    \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_S5_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_FPU_S5_ASM_BKPT:: \n"
#endif
      "   VMOV R2, S5   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S4_S7_FAIL   \n"
      "   MOVS R1, #0xAAAAAAAA \n"
      "   VMOV S5, R1   \n"
      "   VMOV R2, S5   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S4_S7_FAIL   \n"
      "   VMOV S5, R0   \n"

      "   VMOV R0, S6    \n" /* S6 */
      "   MOVS R1, #0x55555555 \n"
      "   VMOV S6, R1    \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_S6_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_FPU_S6_ASM_BKPT:: \n"
#endif
      "   VMOV R2, S6   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S4_S7_FAIL   \n"
      "   MOVS R1, #0xAAAAAAAA \n"
      "   VMOV S6, R1   \n"
      "   VMOV R2, S6   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S4_S7_FAIL   \n"
      "   VMOV S6, R0   \n"

      "   VMOV R0, S7    \n" /* S7 */
      "   MOVS R1, #0x55555555 \n"
      "   VMOV S7, R1    \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_S7_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_FPU_S7_ASM_BKPT:: \n"
#endif
      "   VMOV R2, S7   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S4_S7_FAIL   \n"
      "   MOVS R1, #0xAAAAAAAA \n"
      "   VMOV S7, R1   \n"
      "   VMOV R2, S7   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S4_S7_FAIL   \n"
      "   VMOV S7, R0   \n"

      "   B IEC60730_CPU_REGS_FPU_S4_S7_PASS   \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_S4_S7_FAIL: \n"
#else
      "IEC60730_CPU_REGS_FPU_S4_S7_FAIL:: \n"
#endif
      "   B IEC60730_CPU_REGS_FPU_S8_S11_FAIL   \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_S4_S7_PASS: \n"
#else
      "IEC60730_CPU_REGS_FPU_S4_S7_PASS:: \n"
#endif

      "   VMOV R0, S8    \n" /* S8 */
      "   MOVS R1, #0x55555555 \n"
      "   VMOV S8, R1    \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_S8_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_FPU_S8_ASM_BKPT:: \n"
#endif
      "   VMOV R2, S8   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S8_S11_FAIL   \n"
      "   MOVS R1, #0xAAAAAAAA \n"
      "   VMOV S8, R1   \n"
      "   VMOV R2, S8   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S8_S11_FAIL   \n"
      "   VMOV S8, R0   \n"

      "   VMOV R0, S9    \n" /* S9 */
      "   MOVS R1, #0x55555555 \n"
      "   VMOV S9, R1    \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_S9_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_FPU_S9_ASM_BKPT:: \n"
#endif
      "   VMOV R2, S9   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S8_S11_FAIL   \n"
      "   MOVS R1, #0xAAAAAAAA \n"
      "   VMOV S9, R1   \n"
      "   VMOV R2, S9   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S8_S11_FAIL   \n"
      "   VMOV S9, R0   \n"

      "   VMOV R0, S10    \n" /* S10 */
      "   MOVS R1, #0x55555555 \n"
      "   VMOV S10, R1    \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_S10_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_FPU_S10_ASM_BKPT:: \n"
#endif
      "   VMOV R2, S10   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S8_S11_FAIL   \n"
      "   MOVS R1, #0xAAAAAAAA \n"
      "   VMOV S10, R1   \n"
      "   VMOV R2, S10   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S8_S11_FAIL   \n"
      "   VMOV S10, R0   \n"

      "   VMOV R0, S11    \n" /* S11 */
      "   MOVS R1, #0x55555555 \n"
      "   VMOV S11, R1    \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_S11_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_FPU_S11_ASM_BKPT:: \n"
#endif
      "   VMOV R2, S11   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S8_S11_FAIL   \n"
      "   MOVS R1, #0xAAAAAAAA \n"
      "   VMOV S11, R1   \n"
      "   VMOV R2, S11   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S8_S11_FAIL   \n"
      "   VMOV S11, R0   \n"

      "   B IEC60730_CPU_REGS_FPU_S8_S11_PASS   \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_S8_S11_FAIL: \n"
#else
      "IEC60730_CPU_REGS_FPU_S8_S11_FAIL:: \n"
#endif
      "   B IEC60730_CPU_REGS_FPU_S12_S15_FAIL   \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_S8_S11_PASS: \n"
#else
      "IEC60730_CPU_REGS_FPU_S8_S11_PASS:: \n"
#endif

      "   VMOV R0, S12    \n" /* S12 */
      "   MOVS R1, #0x55555555 \n"
      "   VMOV S12, R1    \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_S12_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_FPU_S12_ASM_BKPT:: \n"
#endif
      "   VMOV R2, S12   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S12_S15_FAIL   \n"
      "   MOVS R1, #0xAAAAAAAA \n"
      "   VMOV S12, R1   \n"
      "   VMOV R2, S12   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S12_S15_FAIL   \n"
      "   VMOV S12, R0   \n"

      "   VMOV R0, S13    \n" /* S13 */
      "   MOVS R1, #0x55555555 \n"
      "   VMOV S13, R1    \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_S13_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_FPU_S13_ASM_BKPT:: \n"
#endif
      "   VMOV R2, S13   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S12_S15_FAIL   \n"
      "   MOVS R1, #0xAAAAAAAA \n"
      "   VMOV S13, R1   \n"
      "   VMOV R2, S13   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S12_S15_FAIL   \n"
      "   VMOV S13, R0   \n"

      "   VMOV R0, S14    \n" /* S14 */
      "   MOVS R1, #0x55555555 \n"
      "   VMOV S14, R1    \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_S14_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_FPU_S14_ASM_BKPT:: \n"
#endif
      "   VMOV R2, S14   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S12_S15_FAIL   \n"
      "   MOVS R1, #0xAAAAAAAA \n"
      "   VMOV S14, R1   \n"
      "   VMOV R2, S14   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S12_S15_FAIL   \n"
      "   VMOV S14, R0   \n"

      "   VMOV R0, S15    \n" /* S15 */
      "   MOVS R1, #0x55555555 \n"
      "   VMOV S15, R1    \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_S15_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_FPU_S15_ASM_BKPT:: \n"
#endif
      "   VMOV R2, S15   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S12_S15_FAIL   \n"
      "   MOVS R1, #0xAAAAAAAA \n"
      "   VMOV S15, R1   \n"
      "   VMOV R2, S15   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S12_S15_FAIL   \n"
      "   VMOV S15, R0   \n"

      "   B IEC60730_CPU_REGS_FPU_S12_S15_PASS   \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_S12_S15_FAIL: \n"
#else
      "IEC60730_CPU_REGS_FPU_S12_S15_FAIL:: \n"
#endif
      "   B IEC60730_CPU_REGS_FPU_S16_S19_FAIL   \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_S12_S15_PASS: \n"
#else
      "IEC60730_CPU_REGS_FPU_S12_S15_PASS:: \n"
#endif

      "   VMOV R0, S16    \n" /* S16 */
      "   MOVS R1, #0x55555555 \n"
      "   VMOV S16, R1    \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_S16_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_FPU_S16_ASM_BKPT:: \n"
#endif
      "   VMOV R2, S16   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S16_S19_FAIL   \n"
      "   MOVS R1, #0xAAAAAAAA \n"
      "   VMOV S16, R1   \n"
      "   VMOV R2, S16   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S16_S19_FAIL   \n"
      "   VMOV S16, R0   \n"

      "   VMOV R0, S17    \n" /* S17 */
      "   MOVS R1, #0x55555555 \n"
      "   VMOV S17, R1    \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_S17_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_FPU_S17_ASM_BKPT:: \n"
#endif
      "   VMOV R2, S17   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S16_S19_FAIL   \n"
      "   MOVS R1, #0xAAAAAAAA \n"
      "   VMOV S17, R1   \n"
      "   VMOV R2, S17   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S16_S19_FAIL   \n"
      "   VMOV S17, R0   \n"

      "   VMOV R0, S18    \n" /* S18 */
      "   MOVS R1, #0x55555555 \n"
      "   VMOV S18, R1    \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_S18_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_FPU_S18_ASM_BKPT:: \n"
#endif
      "   VMOV R2, S18   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S16_S19_FAIL   \n"
      "   MOVS R1, #0xAAAAAAAA \n"
      "   VMOV S18, R1   \n"
      "   VMOV R2, S18   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S16_S19_FAIL   \n"
      "   VMOV S18, R0   \n"

      "   VMOV R0, S19    \n" /* S19 */
      "   MOVS R1, #0x55555555 \n"
      "   VMOV S19, R1    \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_S19_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_FPU_S19_ASM_BKPT:: \n"
#endif
      "   VMOV R2, S19   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S16_S19_FAIL   \n"
      "   MOVS R1, #0xAAAAAAAA \n"
      "   VMOV S19, R1   \n"
      "   VMOV R2, S19   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S16_S19_FAIL   \n"
      "   VMOV S19, R0   \n"

      "   B IEC60730_CPU_REGS_FPU_S16_S19_PASS   \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_S16_S19_FAIL: \n"
#else
      "IEC60730_CPU_REGS_FPU_S16_S19_FAIL:: \n"
#endif
      "   B IEC60730_CPU_REGS_FPU_S20_S23_FAIL   \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_S16_S19_PASS: \n"
#else
      "IEC60730_CPU_REGS_FPU_S16_S19_PASS:: \n"
#endif

      "   VMOV R0, S20    \n" /* S20 */
      "   MOVS R1, #0x55555555 \n"
      "   VMOV S20, R1    \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_S20_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_FPU_S20_ASM_BKPT:: \n"
#endif
      "   VMOV R2, S20   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S20_S23_FAIL   \n"
      "   MOVS R1, #0xAAAAAAAA \n"
      "   VMOV S20, R1   \n"
      "   VMOV R2, S20   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S20_S23_FAIL   \n"
      "   VMOV S20, R0   \n"

      "   VMOV R0, S21    \n" /* S21 */
      "   MOVS R1, #0x55555555 \n"
      "   VMOV S21, R1    \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_S21_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_FPU_S21_ASM_BKPT:: \n"
#endif
      "   VMOV R2, S21   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S20_S23_FAIL   \n"
      "   MOVS R1, #0xAAAAAAAA \n"
      "   VMOV S21, R1   \n"
      "   VMOV R2, S21   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S20_S23_FAIL   \n"
      "   VMOV S21, R0   \n"

      "   VMOV R0, S22    \n" /* S22 */
      "   MOVS R1, #0x55555555 \n"
      "   VMOV S22, R1    \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_S22_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_FPU_S22_ASM_BKPT:: \n"
#endif
      "   VMOV R2, S22   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S20_S23_FAIL   \n"
      "   MOVS R1, #0xAAAAAAAA \n"
      "   VMOV S22, R1   \n"
      "   VMOV R2, S22   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S20_S23_FAIL   \n"
      "   VMOV S22, R0   \n"

      "   VMOV R0, S23    \n" /* S23 */
      "   MOVS R1, #0x55555555 \n"
      "   VMOV S23, R1    \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_S23_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_FPU_S23_ASM_BKPT:: \n"
#endif
      "   VMOV R2, S23   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S20_S23_FAIL   \n"
      "   MOVS R1, #0xAAAAAAAA \n"
      "   VMOV S23, R1   \n"
      "   VMOV R2, S23   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S20_S23_FAIL   \n"
      "   VMOV S23, R0   \n"

      "   B IEC60730_CPU_REGS_FPU_S20_S23_PASS   \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_S20_S23_FAIL: \n"
#else
      "IEC60730_CPU_REGS_FPU_S20_S23_FAIL:: \n"
#endif
      "   B IEC60730_CPU_REGS_FPU_S24_S27_FAIL   \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_S20_S23_PASS: \n"
#else
      "IEC60730_CPU_REGS_FPU_S20_S23_PASS:: \n"
#endif

      "   VMOV R0, S24    \n" /* S24 */
      "   MOVS R1, #0x55555555 \n"
      "   VMOV S24, R1    \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_S24_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_FPU_S24_ASM_BKPT:: \n"
#endif
      "   VMOV R2, S24   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S24_S27_FAIL   \n"
      "   MOVS R1, #0xAAAAAAAA \n"
      "   VMOV S24, R1   \n"
      "   VMOV R2, S24   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S24_S27_FAIL   \n"
      "   VMOV S24, R0   \n"

      "   VMOV R0, S25    \n" /* S25 */
      "   MOVS R1, #0x55555555 \n"
      "   VMOV S25, R1    \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_S25_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_FPU_S25_ASM_BKPT:: \n"
#endif
      "   VMOV R2, S25   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S24_S27_FAIL   \n"
      "   MOVS R1, #0xAAAAAAAA \n"
      "   VMOV S25, R1   \n"
      "   VMOV R2, S25   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S24_S27_FAIL   \n"
      "   VMOV S25, R0   \n"

      "   VMOV R0, S26    \n" /* S26 */
      "   MOVS R1, #0x55555555 \n"
      "   VMOV S26, R1    \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_S26_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_FPU_S26_ASM_BKPT:: \n"
#endif
      "   VMOV R2, S26   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S24_S27_FAIL   \n"
      "   MOVS R1, #0xAAAAAAAA \n"
      "   VMOV S26, R1   \n"
      "   VMOV R2, S26   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S24_S27_FAIL   \n"
      "   VMOV S26, R0   \n"

      "   VMOV R0, S27    \n" /* S27 */
      "   MOVS R1, #0x55555555 \n"
      "   VMOV S27, R1    \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_S27_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_FPU_S27_ASM_BKPT:: \n"
#endif
      "   VMOV R2, S27   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S24_S27_FAIL   \n"
      "   MOVS R1, #0xAAAAAAAA \n"
      "   VMOV S27, R1   \n"
      "   VMOV R2, S27   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_S24_S27_FAIL   \n"
      "   VMOV S27, R0   \n"

      "   B IEC60730_CPU_REGS_FPU_S24_S27_PASS   \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_S24_S27_FAIL: \n"
#else
      "IEC60730_CPU_REGS_FPU_S24_S27_FAIL:: \n"
#endif
      "   B IEC60730_CPU_REGS_FPU_Sx_FAIL   \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_S24_S27_PASS: \n"
#else
      "IEC60730_CPU_REGS_FPU_S24_S27_PASS:: \n"
#endif

      "   VMOV R0, S28    \n" /* S28 */
      "   MOVS R1, #0x55555555 \n"
      "   VMOV S28, R1    \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_S28_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_FPU_S28_ASM_BKPT:: \n"
#endif
      "   VMOV R2, S28   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_Sx_FAIL   \n"
      "   MOVS R1, #0xAAAAAAAA \n"
      "   VMOV S28, R1   \n"
      "   VMOV R2, S28   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_Sx_FAIL   \n"
      "   VMOV S28, R0   \n"

      "   VMOV R0, S29    \n" /* S29 */
      "   MOVS R1, #0x55555555 \n"
      "   VMOV S29, R1    \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_S29_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_FPU_S29_ASM_BKPT:: \n"
#endif
      "   VMOV R2, S29   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_Sx_FAIL   \n"
      "   MOVS R1, #0xAAAAAAAA \n"
      "   VMOV S29, R1   \n"
      "   VMOV R2, S29   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_Sx_FAIL   \n"
      "   VMOV S29, R0   \n"

      "   VMOV R0, S30    \n" /* S30 */
      "   MOVS R1, #0x55555555 \n"
      "   VMOV S30, R1    \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_S30_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_FPU_S30_ASM_BKPT:: \n"
#endif
      "   VMOV R2, S30   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_Sx_FAIL   \n"
      "   MOVS R1, #0xAAAAAAAA \n"
      "   VMOV S30, R1   \n"
      "   VMOV R2, S30   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_Sx_FAIL   \n"
      "   VMOV S30, R0   \n"

      "   VMOV R0, S31    \n" /* S31 */
      "   MOVS R1, #0x55555555 \n"
      "   VMOV S31, R1    \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_S31_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_FPU_S31_ASM_BKPT:: \n"
#endif
      "   VMOV R2, S31   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_Sx_FAIL   \n"
      "   MOVS R1, #0xAAAAAAAA \n"
      "   VMOV S31, R1   \n"
      "   VMOV R2, S31   \n"
      "   CMP R2, R1   \n"
      "   BNE IEC60730_CPU_REGS_FPU_Sx_FAIL   \n"
      "   VMOV S31, R0   \n"

#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_Sx_PASS_ASM_BKPT: \n"
#else
      "IEC60730_CPU_REGS_FPU_Sx_PASS_ASM_BKPT:: \n"
#endif
      "   MOVS %0, #0x1      \n"
      "   B IEC60730_CPU_REGS_FPU_Sx_DONE      \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_Sx_FAIL:          \n"
#else
      "IEC60730_CPU_REGS_FPU_Sx_FAIL::          \n"
#endif
      "   MOVS %0, #0x0       \n"
#ifndef IAR_TESTING /* GCC */
      "IEC60730_CPU_REGS_FPU_Sx_DONE:\n"
#else
      "IEC60730_CPU_REGS_FPU_Sx_DONE::\n"
#endif
      "   LDR R1, =0xE000ED88\n"
      "   STR R5, [R1, #0] \n" /* Restore CPACR */
      "   LDR R1, =0xE000EF34\n"
      "   STR R6, [R1, #0] \n" /* Restore FPCCR */
      "   VMSR FPSCR, R4   \n" /* Restore FPSCR */
      "   LDMIA SP!, {R4, R5, R6}   \n"
      "   CPSIE i  \n" /*Enable IRQ Interrupts*/
      : "=r"(result)::"memory");
#endif
  return result;
}
#endif // ((defined (__FPU_PRESENT) && (__FPU_USED == 1U))

/** @} (end addtogroup IEC60730_CPUREG_Test) */
/** @} (end addtogroup efr32_iec60730) */
