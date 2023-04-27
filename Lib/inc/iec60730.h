/***************************************************************************//**
 * @file
 * @brief Library definitions
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

#ifndef __IEC60730_H__
#define __IEC60730_H__

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include "si_toolchain.h"
#include "iec60730_oem.h"
#include IEC_BOARD_HEADER

#ifdef DOXYGEN
/// User SHOULD define #IEC_BOARD_HEADER definition for using IMC and VMC modules.
/// This definition SHOULD be a header file. In this header file SHOULD be
/// definitions listed in IMC and VMC modules. In our example we defined
/// the #IEC_BOARD_HEADER definition is iec60730_board.h. Our definitions
/// in #IEC_BOARD_HEADER is an example that you can reference. Of course, user CAN
/// redefine the #IEC_BOARD_HEADER definition to any header file.
#define IEC_BOARD_HEADER

#else

#define SFRPAGING 0

#ifdef EFR32MG21_DEVICE
#include "em_device.h"
#define DEVICE_FOUND 1
#ifndef INVAR_BLOCKS_PER_BIST
#define INVAR_BLOCKS_PER_BIST 512
#endif
#ifndef VAR_BLOCKS_PER_BIST
#define VAR_BLOCKS_PER_BIST   256
#endif

#ifndef IEC60730_NON_SECURE_EN
#ifndef ROM_START
#define ROM_START             ((uint32_t*) 0x00000000uL)
#endif // ROM_START
#else
#ifndef ROM_START
#define ROM_START             ((uint32_t*) 0x00028000uL)
#endif
#endif // IEC60730_NON_SECURE_EN

#endif // EFR32MG21_DEVICE

#ifdef EFR32MG12P_DEVICE
#include "em_device.h"
#define DEVICE_FOUND 1
#ifndef INVAR_BLOCKS_PER_BIST
#define INVAR_BLOCKS_PER_BIST 512
#endif
#ifndef VAR_BLOCKS_PER_BIST
#define VAR_BLOCKS_PER_BIST   256
#endif

#ifndef ROM_START
#define ROM_START             ((uint32_t*) 0x00000000uL)
#endif // ROM_START

#endif // EFR32MG12P_DEVICE

#ifdef EFR32FG23_DEVICE
#include "em_device.h"
#define DEVICE_FOUND 1
#ifndef INVAR_BLOCKS_PER_BIST
#define INVAR_BLOCKS_PER_BIST 1024
#endif
#ifndef VAR_BLOCKS_PER_BIST
#define VAR_BLOCKS_PER_BIST   256
#endif

#ifndef IEC60730_NON_SECURE_EN
#ifndef ROM_START
#define ROM_START             ((uint32_t*) 0x08000000uL)
#endif // ROM_START
#else
#ifndef ROM_START
#define ROM_START             ((uint32_t*) 0x08028000uL)
#endif
#endif // IEC60730_NON_SECURE_EN

#endif // EFR32FG23_DEVICE

#ifdef EFR32ZG23_DEVICE
#include "em_device.h"
#define DEVICE_FOUND 1
#ifndef INVAR_BLOCKS_PER_BIST
#define INVAR_BLOCKS_PER_BIST 1024
#endif
#ifndef VAR_BLOCKS_PER_BIST
#define VAR_BLOCKS_PER_BIST   256
#endif

#ifndef IEC60730_NON_SECURE_EN
#ifndef ROM_START
#define ROM_START             ((uint32_t*) 0x08000000uL)
#endif // ROM_START
#else
#ifndef ROM_START
#define ROM_START             ((uint32_t*) 0x08028000uL)
#endif
#endif // IEC60730_NON_SECURE_EN

#endif // EFR32ZG23_DEVICE

#ifndef DEVICE_FOUND
#error "Unknown EFR32 device! Set EFR32xxx_DEVICE in build configuration!"
#endif

#define IEC60370_CM4          0
#define IEC60370_CM33         1

#if defined(__CM4_REV)
#define IEC60370_CPU          IEC60370_CM4
#elif defined(__CM33_REV)
#define IEC60370_CPU          IEC60370_CM33
#else
#error "Unknown Core type!"
#endif

#endif /* DOXYGEN */

/**************************************************************************//**
 * @addtogroup efr32_iec60730
 * @{
 * @addtogroup IEC60730_POST
 * @{
 *****************************************************************************/

#ifdef DOXYGEN
/// This structure holds library version in the format
/// MAJOR.MINOR.REVISION.
typedef struct
{
  uint8_t major;        ///< Major version
  uint8_t minor;        ///< Minor version
  uint8_t revision;     ///< Revision
} iec60730_LibraryVersion_t;
#else
typedef struct
{
  uint8_t major;
  uint8_t minor;
  uint8_t revision;
} iec60730_LibraryVersion_t;
#endif

/// IEC60370 library version. Modified by build jobs to correct version.
#define IE60730_LIBRARY_VERSION { 1, 0, 0 }

/// Global variable which holds the IEC60370 library version.
extern const iec60730_LibraryVersion_t iec60730_LibraryVersion;

/// The result of a test.
typedef enum
{
  iec60730_TestFailed     = 0,              ///< test result failed
  iec60730_TestPassed     = 1,              ///< test result passed
  iec60730_TestInProgress = 2,              ///< test is still in progress
} iec60730_TestResult_t;

/// Cause of failure passed to Safe State function.
typedef enum
{
  iec60730_NoFailure = 0,            ///< No failure detected
  iec60730_TestVerify = 1,           ///< Special case used for automated verification testing
  iec60730_WatchdogPostFail = 2,     ///< Watchdog POST test failed
  iec60730_VMCFail = 3,              ///< Variable Memory Check detected a failure
  iec60730_IMCFail = 4,              ///< Invariable Memory Check detected a failure
  iec60730_CpuRegistersFail = 5,     ///< CPU Registers Check detected a failure
  iec60730_ClockFail = 6,            ///< System Clock Check detected a failure
  iec60730_InterruptFail = 7,        ///< Interrupt Plausibility Check detected a failure
  iec60730_ProgrammeCounterFail = 8, ///< Program Counter Check detected a failure
  iec60730_GpioFail = 9,             ///< GPIO Plausibility Check detected a failure
  iec60730_AnalogFail = 10,          ///< Analog Plausibility Check detected a failure
  iec60730_Cs0Fail = 11,             ///< CSEN0 detected a failureLESENSE
  iec60730_LeSense0Fail = 12,        ///< LESENSE0 detected a failure
  iec60730_RadioFail = 13,           ///< Radio comms detected a failure
  iec60730_I2C0Fail = 14,            ///< I2C0 comms channel detected a failure
  iec60730_I2C1Fail = 15,            ///< I2C1 comms channel detected a failure
  iec60730_Usart0Fail = 16,          ///< USART0 comms channel detected a failure
  iec60730_Usart1Fail = 17,          ///< USART1 comms channel detected a failure
  iec60730_Usart2Fail = 18,          ///< USART2 comms channel detected a failure
  iec60730_Usart3Fail = 19,          ///< USART3 comms channel detected a failure
  iec60730_LeUart0Fail = 20,         ///< LEUART comms channel detected a failure
  iec60730_Euart0Fail = 21,          ///< EUART comms channel detected a failure
  iec60730_Pdm0Fail = 22,            ///< PDM comms channel detected a failure
  iec60730_OEMFail_1 = 23,           ///< OEM defined failure
  iec60730_OEMFail_2 = 24,           ///< OEM defined failure
  iec60730_OEMFail_3 = 25,           ///< OEM defined failure
  iec60730_OEMFail_4 = 26,           ///< OEM defined failure
} iec60730_TestFailure_t;

/// Useful macro for avoiding compiler warnings related to unused function
/// arguments or unused variables.
#ifndef UNUSED_VAR
#define UNUSED_VAR(x) (void)(x)
#endif /* UNUSED_VAR */

#ifndef __CONCAT
#define __CONCAT(x,y) x##y
#endif

#define CONCAT(x,y)   __CONCAT(x,y)

#define STR(x)  #x
#define XSTR(x) STR(x)

#ifdef __GNUC__ /* GCC */
#define LB_ASM        __asm__
#define LB_XSTR(x)    XSTR(x:)
#elif defined (__ICCARM__)
#define LB_ASM        __asm
#define LB_XSTR(x)    XSTR(x::)
#endif

/// The #LABEL_DEF macro is used to generate label for break points. Using this
/// macro avoids label removal by the compiler's optimize levels.
#ifndef LABEL_DEF
#define LABEL_DEF(NAME)      LB_ASM volatile(LB_XSTR(NAME))
#endif /* LABEL_DEF */

/// The #__CLASSB_RAM macro is used to define
/// (.classb_ram) section.
#ifndef __CLASSB_RAM
#define __CLASSB_RAM      __attribute__((section(".classb_ram")))
#endif /* __CLASSB_RAM */

/// The #__RT_BUF macro is used to define
/// (.rt_buf) section.
#ifndef __RT_BUF
#define __RT_BUF          __attribute__((section(".rt_buf")))
#endif /* __RT_BUF */

/// The #__OVERLAP macro is used to define
/// (.overlap) section.
#ifndef __OVERLAP
#define __OVERLAP         __attribute__((section(".overlap")))
#endif /* __OVERLAP */

#ifdef DOXYGEN
/// The #__no_init macro is used for compatibility between
/// GCC and IAR compiler.
#define __no_init
#else // !DOXYGEN
#ifdef __GNUC__
  #ifndef __no_init
  #define __no_init
  #endif /* __no_init */
#endif
#endif // DOXYGEN

/// The #DEC_CLASSB_VARS definition is used for declaring pair of classsb_ram
/// variables.
#define DEC_CLASSB_VARS(vartype, name)  \
  __no_init vartype name __CLASSB_RAM;  \
  __no_init vartype CONCAT(name, Inv) __CLASSB_RAM

/// The #EXTERN_DEC_CLASSB_VARS definition is extern of pair of
/// #DEC_CLASSB_VARS
#define EXTERN_DEC_CLASSB_VARS(vartype, name)   \
  extern __no_init vartype name __CLASSB_RAM;   \
  extern __no_init vartype CONCAT(name, Inv) __CLASSB_RAM

/// The #STATIC_DEC_CLASSB_VARS definition used for declaring static pair
/// #DEC_CLASSB_VARS
#define STATIC_DEC_CLASSB_VARS(vartype, name)   \
  static __no_init vartype name __CLASSB_RAM;   \
  static __no_init vartype CONCAT(name, Inv) __CLASSB_RAM

/// The #INV_CLASSB_VAR macro is used to inverse a Inv value of pair
/// #DEC_CLASSB_VARS
#define INV_CLASSB_VAR(vartype, name)  \
  CONCAT(name, Inv) = (vartype)(~(vartype) name)

/// The #INV_CLASSB_PVAR macro is used to inverse a Inv value of pointer pair
/// #DEC_CLASSB_VARS
#define INV_CLASSB_PVAR(vartype, name) \
  CONCAT(name, Inv) = (vartype *)(~(vartype) name)

/// The #CHECK_INTEGRITY definition used for checking integrity of pair of
/// variables stored in *.classb_ram* section.
#define CHECK_INTEGRITY(vartype, x) \
  ((vartype)-1 == ((vartype) x ^ (vartype) CONCAT(x, Inv)))

/** @} (end addtogroup IEC60730_POST) */

/**************************************************************************//**
 * @addtogroup IEC60730_INVARIABLE_MEMORY_Test
 * @{
 *****************************************************************************/

#ifdef DOXYGEN
/// Support for cleaner code.
///   * If user use the #USE_CRC_32 definition, #crc_t is uint32_t.
///   * Otherwis, #crc_t is uint16_t.
#define crc_t

/// The #INVAR_BLOCKS_PER_BIST desribles maximum number of loops that perform
/// the CRC calculation each time the #iec60730_ImcBist is invoked. We provide
/// default value for this definition in iec60730.h file.
#define INVAR_BLOCKS_PER_BIST

/// The #ROM_START definition describes the start address of Flash for CRC
/// calculation. This definition MUST be alignment of #FLASH_BLOCK and can be
/// changed by user so that the value DOES NOT exceed the end address of Flash
/// (the #ROM_END definition). Otherwise, #iec60730_ImcPost and #iec60730_ImcBist
/// return #iec60730_TestFailed. The default value of the #ROM_START can be found in
/// iec60730.h file.
///
/// In case you change value of this definition then you SHOULD change the 5th
/// parameter of the script \ref gcc_crcXY when running the Post Build.
///
/// In our example, we use the variable __FlashStart provided by the linker file
/// to simply define the start address of Flash. User can redefine #ROM_START
/// as follows.
/// ```
/// #define ROM_START  ((uint32_t *)(&__FlashStart))
/// ```
#define ROM_START

#else // !DOXYGEN

#ifdef USE_CRC_32
typedef uint32_t crc_t;
#else /* !USE_CRC_32 */
typedef uint16_t crc_t;
#endif /* USE_CRC_32 */

#endif // DOXYGEN

/// The end address of Flash is specified by the address of the #__checksum
/// variable. This variable is provided by linker in GCC or generated by
/// configurations in IAR.
extern crc_t __checksum;

/// The #FLASH_BLOCK definition is size of block of Flash. The value of this
/// definition SHOULD be a power of two. The minimal value SHOULD be 4 and
/// maximum value SHOULD be the alignment value that is defined in linker (GCC
/// compiler) or in configuration of IAR. Our example use alignment 64 for
/// #__checksum variable. So that in our example the #FLASH_BLOCK definition
/// is 64. User can refer to our example linker on how to provide #__checksum
/// variable with alignment 64.
#ifndef FLASH_BLOCK
#define FLASH_BLOCK         (64)
#endif

/// The #ROM_END definition describes the end address of Flash. It is the
/// address of #__checksum variables. In this version, users SHOULD not
/// change this definition. Refer to the example in
/// \ref invariable_memory_check_example_flowchart, to better understand the
/// #ROM_START, and #ROM_END definitions.
#ifndef ROM_END
#define ROM_END             ((uint32_t *)(&__checksum))
#endif

/// The #ROM_SIZE definition describes the size of Flash caculated CRC value.
/// This caculation based on #ROM_END, and #ROM_START definitions.
#define ROM_SIZE            ((uint32_t) ROM_END - (uint32_t) ROM_START)

/// The #STEPS_NUMBER definitionn WILL be defined base on #ROM_SIZE and
/// #FLASH_BLOCK definition. User SHOULD not change it.
#define STEPS_NUMBER        ((uint32_t) ROM_SIZE / FLASH_BLOCK)

/// The #ROM_SIZE_INWORDS definitionn WILL be defined base on #ROM_SIZE definition.
/// User SHOULD not change it.
#define ROM_SIZE_INWORDS    ((uint32_t) ROM_SIZE / 4U)

/// The #FLASH_BLOCK_WORDS definitionn WILL be defined base on #ROM_SIZE_INWORDS
/// and #STEPS_NUMBER  definitions. User SHOULD not change it.
#define FLASH_BLOCK_WORDS   ((uint32_t) (ROM_SIZE_INWORDS / STEPS_NUMBER))

/// The #REF_CRC definition describes variable that address of this variable
/// store CRC value that is calculated by \ref gcc_crcXY in Post Build. We use
/// #__checksum so in our example #REF_CRC definition is #__checksum.
#ifndef REF_CRC
#define REF_CRC             (__checksum)
#endif

/** @} (end addtogroup IEC60730_INVARIABLE_MEMORY_Test) */

/**************************************************************************//**
 * @addtogroup IEC60730_VARIABLE_MEMORY_Test
 * @{
 *****************************************************************************/

/// The #BLOCKSIZE definition MUST be 4 as our example for the algorithm to
/// work properly.
#define BLOCKSIZE         (4)

/// The #RT_BLOCK_OVERLAP definition is used to present the size of
/// #ramTestOverLap buffer. The variable #ramTestOverLap has a size of
/// (2 * #RT_BLOCK_OVERLAP). For the algorithm (March-X/March-C) to work
/// properly this definition MUST take the value 1 as in our example.
#define RT_BLOCK_OVERLAP  (1)

/// The definition of #RT_BLOCKSIZE is taken from the definition of #BLOCKSIZE
/// and #RT_BLOCK_OVERLAP.
#define RT_BLOCKSIZE      (BLOCKSIZE + (RT_BLOCK_OVERLAP << 1))

/// The #BACKGROUND definition is background used to testing. In our sample,
/// value 0x00000000uL is used value for background. Of course, we can define
/// another value. We recommend using definition like ours (0x00000000uL) because
/// it accurately describes the steps of the March-X/March-C algorithm
/// described above.
#ifndef BACKGROUND
#define BACKGROUND        ((uint32_t) 0x00000000uL)
#endif

/// Pattern 0 is used for stack overflow
#ifndef STACK_OVERFLOW_CONST_GUARD_VALUE_0
#define STACK_OVERFLOW_CONST_GUARD_VALUE_0    (0xEEEEEEEEuL)
#endif /* STACK_OVERFLOW_CONST_GUARD_VALUE_0 */

/// Pattern 1 is used for stack overflow
#ifndef STACK_OVERFLOW_CONST_GUARD_VALUE_1
#define STACK_OVERFLOW_CONST_GUARD_VALUE_1    (0xCCCCCCCCuL)
#endif /* STACK_OVERFLOW_CONST_GUARD_VALUE_1 */

/// Pattern 2 is used for stack overflow
#ifndef STACK_OVERFLOW_CONST_GUARD_VALUE_2
#define STACK_OVERFLOW_CONST_GUARD_VALUE_2    (0xBBBBBBBBuL)
#endif /* STACK_OVERFLOW_CONST_GUARD_VALUE_2 */

/// Pattern 3 is used for stack overflow
#ifndef STACK_OVERFLOW_CONST_GUARD_VALUE_3
#define STACK_OVERFLOW_CONST_GUARD_VALUE_3    (0xDDDDDDDDuL)
#endif /* STACK_OVERFLOW_CONST_GUARD_VALUE_3 */

/// The #__STACK_BOTTOM macro is used to define
/// (.stack_bottom) section.
#ifndef __STACK_BOTTOM
#define __STACK_BOTTOM    __attribute__((section(".stack_bottom")))
#endif /* __STACK_BOTTOM */

/** @} (end addtogroup IEC60730_VARIABLE_MEMORY_Test) */

/**************************************************************************//**
 * @addtogroup IEC60730_SAFE_STATE
 * @{
 * The Safe State function must be written by the OEM to configure the
 * system to prevent any potential negative effects from occuring. GPIOs and
 * communications channels must be configured appropriately.
 *
 * Once any configuration is complete, the function loops to restart the watchdog.
 * This prevents any resets until the end-user power-cycles the device.
 *
 *****************************************************************************/

/**************************************************************************//**
 * public IEC60730 Safe State
 *
 * @param failure Enum with the failing test, can be preserved for debug.
 * See \link #iec60730_TestFailure_t iec60730_TestFailure_t \endlink
 *
 * @return Never.
 *
 * When a validation failure is detected, the Safe State function is
 * executed to prevent further system failures.
 * @note This is an example; an OEM must fully implement this according
 * to their system needs.
*****************************************************************************/
void iec60730_SafeState(iec60730_TestFailure_t failure);
/** @} (end addtogroup IEC60730_SAFE_STATE) */

/**************************************************************************//**
 * @addtogroup IEC60730_BIST
 * @{
 * iec60730_Bist() confirms correct operation of the device during
 * main loop execution. If a module validation fails, iec60730_SafeState()
 * is called.
 *
 * Longer functions such as variable and non-variable memory checks
 * have critical sections that disable interrupts. To minimize disruption
 * to interrupt service routines, these functions break up validation
 * into smaller pieces. This allows pending interrupts to be
 * serviced while validating.
 *
 * OEM code must set #iec60730_SafetyCheck to one of the failure
 * conditions in #iec60730_TestFailure_t if the code determines a failure
 * has occurred. This can be used for communications channels or to
 * trigger SafeState entry due to a failure within an interrupt.
 *
 * The validation time for the full memory varies between
 * devices depending on the size of memory available, and how frequent
 * iec60730_Bist() is called by the main loop. For details see
 * @ref bist_frequency.
 *
 * Periodic BIST execution is shown in \link bist_flowchart Figure 1\endlink
 *
 * @anchor bist_flowchart
 * @image html BIST_flowchart.png "Figure 1 Flow chart of Periodic BIST execution"
 *****************************************************************************/

/// Global variable used by OEM and interrupt check functions to relay
/// status to IEC60730 safety code.  When a failure is detected, set
/// #iec60730_SafetyCheck to #iec60730_TestFailed.
extern SI_SEGMENT_VARIABLE(iec60730_SafetyCheck, iec60730_TestFailure_t, SI_SEG_DATA);

/**************************************************************************//**
 * public IEC60730 Built In Self Test
 *
 *
 * @returns None. If validation fails function never returns. If validation
 * passes, function returns.
 *
 * Each module is tested, and if a failure is detected iec60730_SafeState()
 * is called. If a test failure occurs outside this function (such as comms),
 * set #iec60730_SafetyCheck to #iec60730_TestFailed.
 *****************************************************************************/
void iec60730_Bist(void);
/** @} (end addtogroup IEC60730_BIST) */

/**************************************************************************//**
 * @addtogroup IEC60730_PROGRAMME_COUNTER
 * @{
 *****************************************************************************/

/// Global variable used by BIST to determine if modules are running
/// frequently enough to meet maximum fault time.
///
/// iec60730_programmeCounterTest() resets all bits to 0. Each module
/// then sets its assigned bit once it has completed testing. Before the
/// maximum fault time, iec60730_programmeCounterTest() verfies that the
/// value is @ref IEC60730_ALL_COMPLETE_BITS.
extern SI_SEGMENT_VARIABLE(iec60730_programmeCounterCheck, uint16_t, SI_SEG_DATA);

/// Mask bit used for Variable Memory Checks completed
#define IEC60730_VMC_COMPLETE           (1 << 0)
/// Mask bit used for Invariable Memory Checks completed
#define IEC60730_IMC_COMPLETE           (1 << 1)
/// Mask bit used for CPU Clocks Checks completed
#define IEC60730_CPU_CLOCKS_COMPLETE    (1 << 2)
/// Mask bit used for CPU Register Checks completed
#define IEC60730_CPU_REGS_COMPLETE      (1 << 3)
/// Mask bit used for Interrupt Checks completed
#define IEC60730_INTERRUPT_COMPLETE     (1 << 4)
/// Mask bit used for GPIO Plausibility Checks completed
#define IEC60730_GPIO_COMPLETE          (1 << 5)
/// Mask bit used for Analog Plausibility Checks completed
#define IEC60730_ANALOG_COMPLETE        (1 << 6)
/// Mask bit used for Communications Plausibility Checks completed
#define IEC60730_COMMS_COMPLETE         (1 << 7)
/// Mask bit used for OEM Check 0 completed
#define IEC60730_OEM0_COMPLETE          (1 << 8)
/// Mask bit used for OEM Check 1 completed
#define IEC60730_OEM1_COMPLETE          (1 << 9)
/// Mask bit used for OEM Check 2 completed
#define IEC60730_OEM2_COMPLETE          (1 << 10)
/// Mask bit used for OEM Check 3 completed
#define IEC60730_OEM3_COMPLETE          (1 << 11)
/// Mask bit used for OEM Check 4 completed
#define IEC60730_OEM4_COMPLETE          (1 << 12)
/// Mask bit used for OEM Check 5 completed
#define IEC60730_OEM5_COMPLETE          (1 << 13)
/// Mask bit used for OEM Check 6 completed
#define IEC60730_OEM6_COMPLETE          (1 << 14)
/// Mask bit used for OEM Check 7 completed
#define IEC60730_OEM7_COMPLETE          (1 << 15)
/// Mask used for checking that all bits are set
#define IEC60730_ALL_COMPLETE_BITS (IEC60730_VMC_COMPLETE           \
                                    | IEC60730_IMC_COMPLETE         \
                                    | IEC60730_CPU_CLOCKS_COMPLETE  \
                                    | IEC60730_CPU_REGS_COMPLETE    \
                                    | IEC60730_INTERRUPT_COMPLETE   \
                                    | IEC60730_GPIO_COMPLETE        \
                                    | IEC60730_ANALOG_COMPLETE      \
                                    | IEC60730_COMMS_COMPLETE       \
                                    | IEC60730_OEM0_COMPLETE        \
                                    | IEC60730_OEM1_COMPLETE        \
                                    | IEC60730_OEM2_COMPLETE        \
                                    | IEC60730_OEM3_COMPLETE        \
                                    | IEC60730_OEM4_COMPLETE        \
                                    | IEC60730_OEM5_COMPLETE        \
                                    | IEC60730_OEM6_COMPLETE        \
                                    | IEC60730_OEM7_COMPLETE)
/** @} (end addtogroup IEC60730_PROGRAMME_COUNTER) */

/**************************************************************************//**
 * @addtogroup IEC60730_POST
 * @{
 * iec60730_Post() validates system health before starting execution
 * of the main loop.
 * It must be called first in the main() function. If the result of a test
 * routine is a failure, iec60730_SafeState() is called.
 *****************************************************************************/

/**************************************************************************//**
 * public IEC60730 Power On Self Test
 *
 * @returns None. If validation fails function never returns. If validation
 * passes, function returns.
 *
 * Each module is tested, and if a failure is detected iec60730_SafeState()
 * is called.
 *****************************************************************************/
void iec60730_Post();
/** @} (end addtogroup IEC60730_POST) */

/**************************************************************************//**
 * @addtogroup IEC60730_WDOG_Test
 * @{
 *****************************************************************************/

/**************************************************************************//**
 * public IEC60730 Watchdog Restart
 *
 * @returns None.
 *
 * This function abstracts the differences between the EFR32 family watchdog
 * timers. OEMs can call it during long duration executions to restart
 * the watchdog timer.
 *****************************************************************************/
void iec60730_RestartWatchdogs(void);

/** @} (end addtogroup IEC60730_WDOG_Test) */

/**************************************************************************//**
 * @addtogroup IEC60730_SYSTEM_CLOCK_Test
 * @{
 *****************************************************************************/

/// Enable/disable switch for system timer test
typedef enum
{
  iec60730_TimerTestDisable  = 0,             ///< timer tests will not execute
  iec60730_TimerTestEnable   = 1,             ///< timer tests will execute
} iec60730_TimerTestControl_t;

/// Variable set by OEM to determine clock tolerance allowed.
extern SI_SEGMENT_VARIABLE(iec60730_clockTestTolerance, uint8_t, SI_SEG_DATA);
/// Allows OEM code to disable ISR-based timer test execution when
/// in safe states.
///
/// This switch allows customers to stop ISR-based tests
/// when code enters a safe state where BIST is not being called because the
/// code is not safety critical. Tests whose execution is gated by this
/// value are the system clock test, the interrupt plausibility
/// test, and the BIST execution frequency test.
extern SI_SEGMENT_VARIABLE(iec60730_timerTestControl, uint8_t, SI_SEG_DATA);
/// Allows OEM code to run tests using timer tick.
///
/// This global variable allows OEM code to test when events occur.
extern SI_SEGMENT_VARIABLE(iec60730_timerTick, uint16_t, SI_SEG_DATA);
/// Provides the expected ratio of system clock to test clock ticks
///
/// Must be defined as system clock (faster clock) / test clock (slower clock).
/// The ratio value cannot exceed 0xFFFF.
extern SI_SEGMENT_VARIABLE(iec60730_systemClockToTestClockFrequency, uint16_t, SI_SEG_DATA);

/**************************************************************************//**
 * public IEC60730 System Clock Tick
 *
 * @returns None.
 *
 * This function increments a system clock counter, which is compared to a
 * test clock counter as part of the system clock frequency check.  It should
 * be called in the timer interrupt service routine designated as the system
 * clock timer in iec60730_oem_timer.c.
 *****************************************************************************/
void iec60730_SystemClockTick(void);

/**************************************************************************//**
 * public IEC60730 Test Clock Tick
 *
 * @returns None.
 *
 * This function increments a test clock counter.  The function executes
 * all interrupt service routine-based IEC60730 tests, including the system
 * clock frequency check.  It should be called in the timer interrupt
 * service routine designated as the test clock timer in iec60730_oem_timer.c.
 *****************************************************************************/
void iec60730_TestClockTick(void);

/**************************************************************************//**
 * public IEC60730 Initialize iec60730 timers and timer interrupts
 *
 * @returns None.
 *
 * This routine configures the test timer and both test timer and system
 * timer interrupts. #iec60730_SystemClockTick should execute at a period
 * of 10 ms and #iec60730_TestClockTick should execute at a period of 100 ms.
 *****************************************************************************/
void iec60730_TimersInit(void);

/**************************************************************************//**
 * public IEC60730 Initialize iec60730 timer tick variables
 *
 * @returns None.
 *
 * This function should be called within the #iec60730_TestClockTick
 * callback.  During the initialization of the test clock timers, this
 * function resets the internal test clock and system clock tick variables
 * to known reset states.
 *****************************************************************************/
void iec60730_clockTicksReset(void);

/** @} (end addtogroup IEC60730_SYSTEM_CLOCK_Test) */

/**************************************************************************//**
 * @addtogroup IEC60730_IRQ_Test
 * @{
 *****************************************************************************/

/// OEMs use this structure to define the expected min and max number
/// of executions for each interrupt included in a project.
typedef struct
{
  uint8_t min;  ///< Minimum expected executions of ISR.  Can be 0-255, must be less than or equal to max.
  uint8_t max;  ///< Maximum executed executions of ISR.  Can be 0-255, must be greater than or equal to min
} iec60730_IRQExecutionBounds_t;

/// Defines number of interrupt entries in #iec60730_IRQFreqBounds
///
/// This count is used by the test to step through each entry in
/// #iec60730_IRQFreqBounds to determine if the count for each interrupt
/// exceeds expected min/max bounds. OEM code is responsible for
/// incrementing the element of this array corresponding to the IRQ described
/// by the corresponding element in #iec60730_IRQFreqBounds.  The
/// incrementing instruction should only be placed inside the IRQ referred
/// to by the element.  The element will be reset to 0 by the interrupt
/// plausibility check executing in #iec60730_TestClockTick.
extern SI_SEGMENT_VARIABLE(iec60730_IRQExecCount[], uint8_t, SI_SEG_DATA);
/// Defines expected interrupt min/max boundaries for plausibility testing
///
/// This OEM-defined structure defines the expected minimum and maximum
/// number of executions for every test clock period.  The interrupt
/// plausibility test, which executes at the end of a test clock period,
/// compares the number of ISR executions for each ISR as defined in the
/// #iec60730_IRQExecCount array.  A count outside the defined bounds results
/// in a safe state entry.
extern SI_SEGMENT_CONST(iec60730_IRQFreqBounds[], iec60730_IRQExecutionBounds_t, SI_SEG_CODE);
/// Defines number of interrupt entries in #iec60730_IRQFreqBounds
///
/// This count is used by the test to step through each entry in
/// #iec60730_IRQFreqBounds to determine if the count for each interrupt
/// exceeds expected min/max bounds.
extern SI_SEGMENT_CONST(iec60730_IRQFreqBoundsSize, uint8_t, SI_SEG_CODE);

/** @} (end addtogroup IEC60730_IRQ_Test) */

/**************************************************************************//**
 * @addtogroup IEC60730_INVARIABLE_MEMORY_Test
 * @{
 *****************************************************************************/

/// The way to read CRC value when using function #iec60730_updateCRCWithDataBuffer
typedef uint8_t readType_t;
enum {
  IMC_DATA_READ = 0,                ///< use function GPCRC_DataRead to read CRC
  IMC_DATA_READ_BIT_REVERSED = 1,   ///< use function GPCRC_DataReadBitReversed to read CRC
  IMC_DATA_READ_BYTE_REVERSED = 2,  ///< use function GPCRC_DataReadByteReversed to read CRC
};

/// This structure is used as configuration for IMC testing, that holds GPCRC Register
typedef struct {
  CRC_TypeDef *gpcrc;       ///< GPCRC Register
} imcParams_t;

/// This structure is used as configuration for CRC Buffer calculation.
/// It used when using function #iec60730_updateCRCWithDataBuffer
/// @note: struct #CRC_INIT_TypeDef defined in header file iec60730_oem.h
typedef struct {
#ifndef CRC_USE_SW
  imcParams_t hal;          ///< struct #imcParams_t that contain GPCRC Register
  CRC_INIT_TypeDef init;    ///< CRC initialization structure.
  readType_t readType;      ///< The way to read calculated CRC value
#endif /* CRC_USE_SW */
  crc_t xorOut;             ///< XOR with calculated CRC value
} updateCrcParams_t;

#ifdef DOXYGEN
/// This macro is the default of GPCRC Register.
///   * Default #DEFAULT_GPRC is GPCRC (also GPCRC_S).
///   * If the #IEC60730_NON_SECURE_EN is enable, #DEFAULT_GPRC is GPCRC_NS.
#define DEFAULT_GPRC
#else
#ifndef DEFAULT_GPRC
#ifndef IEC60730_NON_SECURE_EN
#define DEFAULT_GPRC GPCRC
#else
#define DEFAULT_GPRC GPCRC_NS
#endif
#endif // DEFAULT_GPRC
#endif // DOXYGEN

/// This macro is the sample test buffer used for testing CRC algorithm. This
/// value is used in development phase. User DOES NOT take care this definition.
#define IMC_CRCBUFFER_SAMPLETEST "123456789"

#ifdef DOXYGEN
/// This macro is the initial value used for CRC calculations.
/// User DOES NOT change this value
///   * <b>CRC-16</b>: 0x0000 (SW) <b>CRC-32</b>: 0xFFFFFFFFuL (SW)
///   * <b>CRC-16</b>: 0xFFFF (HW) <b>CRC-32</b>: 0xFFFFFFFFuL (HW)
#define IMC_CRCBUFFER_INIT_VALUE

/// This macro is the value that will XOR with calculated CRC value to get CRC
/// ouput value. User DOES NOT change this value
///   * <b>CRC-16</b>: 0x0000 (SW) <b>CRC-32</b>: 0xFFFFFFFFuL (SW)
///   * <b>CRC-16</b>: 0x0000 (HW) <b>CRC-32</b>: 0xFFFFFFFFuL (HW)
#define IMC_CRCBUFFER_XOROUTPUT

/// This macro is the expected CRC value with input buffer that equal to
/// "123456789". These value are only used in development phase. User DOES NOT
/// take care this definition.
///   * <b>CRC-16</b>: 0x29B1 <b>CRC-32</b>: 0xCBF43926
#define IMC_CRCBUFFER_SAMPLERESULT

/// This macro is the default value of struct #updateCrcParams_t. User DOES NOT
/// change this value
#define IMC_CRCBUFFER_UPDATE_DEFAULT

#else

#ifdef CRC_USE_SW
  #ifdef USE_CRC_32
#define IMC_CRCBUFFER_INIT_VALUE    (0xFFFFFFFFuL)
#define IMC_CRCBUFFER_XOROUTPUT     (0xFFFFFFFFuL)
#define IMC_CRCBUFFER_SAMPLERESULT  (0xCBF43926)
#define IMC_CRCBUFFER_UPDATE_DEFAULT { \
    IMC_CRCBUFFER_XOROUTPUT \
  }
  #else /* !USE_CRC_32 */
#define IMC_CRCBUFFER_INIT_VALUE    (0x0000)
#define IMC_CRCBUFFER_XOROUTPUT     (0x0000)
#define IMC_CRCBUFFER_SAMPLERESULT  (0x29B1)
#define IMC_CRCBUFFER_UPDATE_DEFAULT { \
    IMC_CRCBUFFER_XOROUTPUT \
  }
  #endif /* USE_CRC_32 */
#else /* !CRC_USE_SW */
  #ifdef USE_CRC_32
#define IMC_CRCBUFFER_INIT_VALUE    (0xFFFFFFFFuL)
#define IMC_CRCBUFFER_XOROUTPUT     (0xFFFFFFFFuL)
#define IMC_CRCBUFFER_SAMPLERESULT  (0xCBF43926)
#define IMC_CRCBUFFER_INIT_DEFAULT { \
    0x04C11DB7UL, \
    IMC_CRCBUFFER_INIT_VALUE, \
    false, \
    false, \
    false, \
    false, \
    true, \
  }

#define IMC_CRCBUFFER_UPDATE_DEFAULT { \
    { DEFAULT_GPRC }, \
    IMC_CRCBUFFER_INIT_DEFAULT, \
    IMC_DATA_READ, \
    IMC_CRCBUFFER_XOROUTPUT \
  }
  #else /* !USE_CRC_32 */
#define IMC_CRCBUFFER_INIT_VALUE    (0xFFFF)
#define IMC_CRCBUFFER_XOROUTPUT     (0x0000)
#define IMC_CRCBUFFER_SAMPLERESULT  (0x29B1)
#define IMC_CRCBUFFER_INIT_DEFAULT { \
    0x1021UL, \
    IMC_CRCBUFFER_INIT_VALUE, \
    false, \
    true, \
    false, \
    false, \
    true, \
  }
#define IMC_CRCBUFFER_UPDATE_DEFAULT { \
    { DEFAULT_GPRC }, \
    IMC_CRCBUFFER_INIT_DEFAULT, \
    IMC_DATA_READ_BIT_REVERSED, \
    IMC_CRCBUFFER_XOROUTPUT \
  }
  #endif /* USE_CRC_32 */
#endif /* CRC_USE_SW */

#endif // DOXYGEN

/**************************************************************************//**
 * public IEC60730 Invariable Memory Check (IMC) Init
 *
 * @param params input parameter of struct #imcParams_t form
 *
 * @return void
 *
 * Performs a initialization of global variables and hardware configuration in
 * case hardware support.
 *****************************************************************************/
void iec60730_ImcInit(imcParams_t *params);

/**************************************************************************//**
 * public IEC60730 Update CRC git pull with Data Buffer
 *
 * @param params input parameter of struct #updateCrcParams_t form
 * @param crc The CRC to be updated. The initial value of crc is also initial
 * value of CRC calculation.
 * @param buffer A contiguous array of 1-byte values to be used to update the CRC.
 * @param size The number of bytes stored in the buffer.
 *
 * @returns #iec60730_TestResult_t.
 *          * If test fails, returns #iec60730_TestFailed;
 *          * Otherwise, return #iec60730_TestPassed.
 *
 * This routine takes a CRC and updates it using a buffer of one or more
 * bytes of data. For details on the CRC polynomial used, see
 * @ref imc_hardware_architecture
 *****************************************************************************/
iec60730_TestResult_t iec60730_updateCRCWithDataBuffer(updateCrcParams_t *params,
                                                       crc_t *crc,
                                                       uint8_t *buffer,
                                                       uint32_t size);

/** @} (end addtogroup IEC60730_INVARIABLE_MEMORY_Test) */

/**************************************************************************//**
 * @addtogroup IEC60730_VARIABLE_MEMORY_Test
 * @{
 *****************************************************************************/

/// This structure is used as configuration for VMC testing
typedef struct {
  uint32_t  *start;         ///< Start address of RAM to check
  uint32_t  *end;           ///< End address of RAM to check
} vmcParams_t;

/**************************************************************************//**
 * public IEC60730 Variable Memory Check (VMC) Initialize
 *
 * @param params input parameter of struct #vmcParams_t form
 *
 * @return void
 *
 * Performs a initialization of global variables. This function SHOULD call
 * before calling #iec60730_VmcBist
 *****************************************************************************/
void iec60730_VmcInit(vmcParams_t *params);

/** @} (end addtogroup IEC60730_VARIABLE_MEMORY_Test) */


#if (_SILICON_LABS_32B_SERIES == 2)
// Write to backup ram module
// buram_inst: Pointer to BURAM instance
// idx: BURAM Reg index
// val: write value
#define IEC60730_BURAM_WRITE(buram_inst, idx, val)  \
  do { \
    buram_inst->RET[idx].REG = val; \
  } while(0)

// Read from backup ram module
// buram_inst: Pointer to BURAM instance
// idx: BURAM Reg index
#define IEC60730_BURAM_READ(buram_inst, idx)        (buram_inst->RET[idx].REG)
#endif

/** @} (end addtogroup efr32_iec60730) */

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif

