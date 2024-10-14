/***************************************************************************/ /**
 * @file
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

#ifndef IEC60730_CPU_REGISTERS_H_
#define IEC60730_CPU_REGISTERS_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "iec60730_internal.h"

/**************************************************************************/ /**
 * @addtogroup efr32_iec60730
 * @{
 * @addtogroup IEC60730_CPUREG_Test
 * @{
 * @section cpureg_hardware_architecture Hardware Architecture
 * The CM33 CPU registers include the following registers:
 * General-purpose registers:
 *      • R0-R12
 * Stack pointer registers:
 *      • MSP + MSPLIM (secure/non-secure)
 *      • PSP + PSPLIM (secure/non-secure)
 * Special registers:
 *      • APSR • CONTROL (secure/non-secure)
 *      • PRIMASK (secure/non-secure)
 *      • FAULTMASK (secure/non-secure)
 *      • BASEPRI (secure/non-secure)
 * Link register:
 *      • LR
 * FPU registers:
 *      • FPSCR
 *      • S0 – S31
 * There is a set of tests performed once after the MCU reset and also during
 * runtime.
 *
 * @section cpureg_failure_risks Failure Risks
 * The primary risks with the CPU registers are stuck bits and shorted bits.
 * The CPU register tests will verify that bits can be set high and low, and
 * adjacent bits are not shorted.
 *
 * @section cpureg_software_architecture Software Architecture
 * Because internal CPU registers are being tested, the code must be written
 * using assembly language.
 *
 * The identification of safety errors is ensured by the specific FAIL return
 * if some registers have the stuck-at fault. Assess the return value of every
 * function. If the value equals the FAIL return, then a jump into the safety
 * error handling function should occur. The safety error handling function may
 * be specific to the application and it is not a part of the library. The main
 * purpose of this function is to put the application into a safe state.
 *
 * In some special cases, the error is not reported by the FAIL return, because
 * it would require the action of a corrupt register. In that case, the function
 * waits for reset in an endless loop. The principle of the stuck-at error test
 * of the CPU registers is to write and compare two test patterns in every
 * register. The content of the register is compared with the constant or with
 * the value written into another register that was tested before. Most of the
 *  time, R0, R1, and R2 are used as auxiliary registers. Patterns are defined
 * to check the logical one and logical zero values in all register bits.
 *
 * Due to the Arm TrustZone support, some core registers are banked between the
 * security states. The Secure (S) or Non-Secure (NS) sets of the corresponding
 * registers are accessible during execution (depending on the current security
 * state). Both register versions are accessible during the S state, but not
 * during the NS state. This is the reason why the NXP Safety Library must be
 * executed in a secure mode. All of the banked registers are listed above.
 *
 * For the EFR32 IEC60730 implementation, \link cpu_registers_check_flowchart Figure 1\endlink
 * shows the logic flow chart of the CPU registers check during BIST and POST.
 *
 * \image html cpu_registers_check_flowchart.png "Figure 1 CPU registers check flowchart" \anchor cpu_registers_check_flowchart
 *
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
iec60730_TestResult_t iec60730_CpuRegistersBist(void);

/**************************************************************************/ /**
 * public IEC60730 CPU Registers Power On Self Test
 *
 * @returns #iec60730_TestResult_t
 *
 * This function simply calls the iec60730_CpuRegistersBist() function.
 *****************************************************************************/
iec60730_TestResult_t iec60730_CpuRegistersPost(void);

/**************************************************************************/ /**
 * private IEC60730 CPU Registers Core Check
 *
 * @returns #iec60730_TestResult_t
 * @returns #iec60730_TestFailed means test failed,
 *          #iec60730_TestPassed means test passed.
 *
 * This function tests the following CPU registers in a sequence: APSR, R0-R12,
 * LR
 * Test patterns: R0–R12, LR: 0xAAAAAAAA, 0x55555555
 *****************************************************************************/
iec60730_TestResult_t iec60730_CpuRegistersCore(void);

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
iec60730_TestResult_t iec60730_CpuRegistersMSP_NS(void);
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
iec60730_TestResult_t iec60730_CpuRegistersMSP_S(void);
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
iec60730_TestResult_t iec60730_CpuRegistersMSP(void);
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
iec60730_TestResult_t iec60730_CpuRegistersPSP_NS(void);
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
iec60730_TestResult_t iec60730_CpuRegistersPSP_S(void);
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
iec60730_TestResult_t iec60730_CpuRegistersPSP(void);
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
iec60730_TestResult_t iec60730_CpuRegistersMSPLim_NS(void);
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
iec60730_TestResult_t iec60730_CpuRegistersMSPLim_S(void);
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
iec60730_TestResult_t iec60730_CpuRegistersPSPLim_NS(void);
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
iec60730_TestResult_t iec60730_CpuRegistersPSPLim_S(void);
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
iec60730_TestResult_t iec60730_CpuRegistersControl_NS(void);
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
iec60730_TestResult_t iec60730_CpuRegistersControl_S(void);
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
iec60730_TestResult_t iec60730_CpuRegistersControl(void);
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
iec60730_TestResult_t iec60730_CpuRegistersPriMask_NS(void);
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
iec60730_TestResult_t iec60730_CpuRegistersPriMask_S(void);
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
iec60730_TestResult_t iec60730_CpuRegistersPriMask(void);
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
iec60730_TestResult_t iec60730_CpuRegistersBasePri_NS(void);
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
iec60730_TestResult_t iec60730_CpuRegistersBasePri_S(void);
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
iec60730_TestResult_t iec60730_CpuRegistersBasePri(void);
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
iec60730_TestResult_t iec60730_CpuRegistersFaultMask_NS(void);
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
iec60730_TestResult_t iec60730_CpuRegistersFaultMask_S(void);
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
iec60730_TestResult_t iec60730_CpuRegistersFaultMask(void);
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
iec60730_TestResult_t iec60730_CpuRegistersFPU_FPSCR(void);

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
iec60730_TestResult_t iec60730_CpuRegistersFPU_FPSx(void);
#endif // ((defined (__FPU_PRESENT) && (__FPU_USED == 1U))

/** @} (end addtogroup IEC60730_CPUREG_Test) */
/** @} (end addtogroup efr32_iec60730) */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* IEC60730_CPU_REGISTERS_H_ */
