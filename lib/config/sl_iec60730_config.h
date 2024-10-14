/***************************************************************************/ /**
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

#ifndef __IEC60730_CONFIG_H__
#define __IEC60730_CONFIG_H__

// <<< Use Configuration Wizard in Context Menu >>>

/**************************************************************************/ /**
 * @addtogroup efr32_iec60730
 * @{
 * @addtogroup IEC60730_IRQ_Test
 * @{
 *****************************************************************************/

// <h> IEC60730_IRQ

// <o SL_IEC60730_IRQ_TYPE_VARIABLE> Data type for iec60730_IRQExecCount variables
// <uint8_t=> uint8_t
// <uint16_t=> uint16_t
// <uint32_t=> uint32_t
// <i> Default: uint8_t
#define SL_IEC60730_IRQ_TYPE_VARIABLE  uint8_t

// <q SL_IEC60730_IRQ_STATUS_ENABLE> Enable function to get the value of failed irqs
// <i> Default: 0
#define SL_IEC60730_IRQ_STATUS_ENABLE  0

// </h>

/** @} (end addtogroup IEC60730_IRQ_Test) */

/**************************************************************************/ /**
 * @addtogroup IEC60730_WDOG_Test
 * @{
 *****************************************************************************/

// <h> IEC60730_WATCHDOG

// <q SL_IEC60730_WDOG0_ENABLE> Enable Watchdog 0
// <i> Default: 1
#define SL_IEC60730_WDOG0_ENABLE                1

// <q SL_IEC60730_WDOG1_ENABLE> Enable Watchdog 1
// <i> Default: 0
#define SL_IEC60730_WDOG1_ENABLE                0

// <q SL_IEC60730_SAVE_STAGE_ENABLE> Enable saving iec60730_WatchdogState to backup RAM on Series 2
// <i> Default: 0
#define SL_IEC60730_SAVE_STAGE_ENABLE           0

// <q SL_IEC60730_RSTCAUSES_CLEAR_ENABLE> Reset cause flags in the RSTCASUES register
// <i> Default: 0
#define SL_IEC60730_RSTCAUSES_CLEAR_ENABLE      0

// </h>

/** @} (end addtogroup IEC60730_WDOG_Test) */

/**************************************************************************/ /**
 * @addtogroup IEC60730_SYSTEM_CLOCK_Test
 * @{
 *****************************************************************************/

// <h> IEC60730_SYS_CLOCK

// <o SL_IEC60730_TEST_CLOCK_MULTIPLIER> Determines how many entrances into sl_iec60730_test_clock_tick()
// occur before bist frequency test executes
// <i> Default: 10
#define SL_IEC60730_TEST_CLOCK_MULTIPLIER       10

// <o SL_IEC60730_SYS_CLOCK_TEST_CLK_FREQ> This value is used to compare with the system clock counter
// This define holds the ratio value between system clock timer interrupt period and
// test clock timer interrupt period
// <i> Default: 10
#define SL_IEC60730_SYS_CLOCK_TEST_CLK_FREQ     10

// <o SL_IEC60730_SYS_CLOCK_TEST_TOLERANCE> The tolerance of test
// (OEM set value of the define, example: iec60730_sys_clock_test_tolerance)
// is typical (+/-) 10%-49% of the SL_IEC60730_SYS_CLOCK_TEST_CLK_FREQ.
// <i> Default: 1
#define SL_IEC60730_SYS_CLOCK_TEST_TOLERANCE    1

// </h>

/** @} (end addtogroup IEC60730_SYSTEM_CLOCK_Test) */

/**************************************************************************/ /**
 * @addtogroup IEC60730_VARIABLE_MEMORY_Test
 * @{
 *****************************************************************************/

// <h> IEC60730_VMC

// <q SL_IEC60730_USE_MARCHX_ENABLE> Enable used the algorithm used in BIST is March-X.
// <i> Default: 1
#define SL_IEC60730_USE_MARCHX_ENABLE           1

// <o SL_IEC60730_VAR_BLOCKS_PER_BIST> SL_IEC60730_VAR_BLOCKS_PER_BIST
// <i> Default: 256
#define SL_IEC60730_VAR_BLOCKS_PER_BIST         256

// <s.14 SL_STACK_OVERFLOW_CONST_GUARD_VALUE_0> Pattern 0 is used for stack overflow
// <i> Default: (0xEEEEEEEEuL)
#define SL_STACK_OVERFLOW_CONST_GUARD_VALUE_0   (0xEEEEEEEEuL)

// <s.14 SL_STACK_OVERFLOW_CONST_GUARD_VALUE_1> Pattern 1 is used for stack overflow
// <i> Default: (0xCCCCCCCCuL)
#define SL_STACK_OVERFLOW_CONST_GUARD_VALUE_1   (0xCCCCCCCCuL)

// <s.14 SL_STACK_OVERFLOW_CONST_GUARD_VALUE_2> Pattern 2 is used for stack overflow
// <i> Default: (0xBBBBBBBBuL)
#define SL_STACK_OVERFLOW_CONST_GUARD_VALUE_2   (0xBBBBBBBBuL)

// <s.14 SL_STACK_OVERFLOW_CONST_GUARD_VALUE_3> Pattern 3 is used for stack overflow
// <i> Default: (0xDDDDDDDDuL)
#define SL_STACK_OVERFLOW_CONST_GUARD_VALUE_3   (0xDDDDDDDDuL)


// </h>

/** @} (end addtogroup IEC60730_VARIABLE_MEMORY_Test) */

/**************************************************************************/ /**
 * @addtogroup IEC60730_INVARIABLE_MEMORY_Test
 * @{
 *****************************************************************************/

// <h> IEC60730_IMC

// <q SL_IEC60730_CRC_DEBUG_ENABLE> Enable debug IMC module
/// Use this definition for debugging purposes.
// <i> Default: 1
#define SL_IEC60730_CRC_DEBUG_ENABLE            1

// <o SL_IEC60730_INVAR_BLOCKS_PER_BIST> SL_IEC60730_INVAR_BLOCKS_PER_BIST
// <i> Default: 512
#define SL_IEC60730_INVAR_BLOCKS_PER_BIST       512

// <o SL_IEC60730_FLASH_BLOCK> Definition is size of block of Flash
/// The value of this
/// definition SHOULD be a power of two. The minimal value SHOULD be 4 and
/// maximum value SHOULD be the alignment value that is defined in linker (GCC
/// compiler) or in configuration of IAR. Our example use alignment 64 for
/// #__checksum variable. So that in our example the #SL_IEC60730_FLASH_BLOCK definition
/// is 64. User can refer to our example linker on how to provide #__checksum
/// variable with alignment 64.
// <i> Default: 64
#define SL_IEC60730_FLASH_BLOCK                 64


// </h>

/** @} (end addtogroup IEC60730_INVARIABLE_MEMORY_Test) */
/** @} (end addtogroup efr32_iec60730) */

// <<< end of configuration section >>>

#endif /* __IEC60730_CONFIG_H__ */
