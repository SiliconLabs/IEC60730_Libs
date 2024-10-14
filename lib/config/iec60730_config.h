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

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "si_toolchain.h"
#include "iec60730_oem.h"
#include "em_device.h"
#include IEC_BOARD_HEADER

// <<< Use Configuration Wizard in Context Menu >>>

// <h> IEC60730_IRQ

// <o IEC60730_IRQ_TYPE_VARIABLE> Data type for iec60730_IRQExecCount variables
// <uint8_t=> uint8_t
// <uint16_t=> uint16_t
// <uint32_t=> uint32_t
// <i> Default: uint8_t
#define IEC60730_IRQ_TYPE_VARIABLE  uint8_t
// <o SL_IEC60730_IRQ_STATUS_EN> Enable function to get the value of failed irqs
// <i> Default: 0
// <0..1:1>
#define SL_IEC60730_IRQ_STATUS_EN   0

// </h>

// <h> IEC60730_SYS_CLOCK

// <o SL_TEST_CLOCK_MULTIPLIER> Determines how many entrances into sl_iec60730_test_clock_tick()
// occur before bist frequency test executes
// <i> Default: 10
#define SL_TEST_CLOCK_MULTIPLIER                10

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

// <h> IEC60730_IMC

// <o VAR_BLOCKS_PER_BIST> VAR_BLOCKS_PER_BIST
// <i> Default: 256
#define VAR_BLOCKS_PER_BIST 256
// <o INVAR_BLOCKS_PER_BIST> INVAR_BLOCKS_PER_BIST
// <i> Default: 512
#define INVAR_BLOCKS_PER_BIST 512
// <o BLOCKSIZE> BLOCKSIZE definition MUST be 4 for the algorithm (March-X/March-C)
// <i> Default: 4
#define BLOCKSIZE (4)

// <o RT_BLOCK_OVERLAP> RT_BLOCK_OVERLAP definition is used to present the size of #ramTestOverLap buffer.
// The variable #ramTestOverLap has a size of
// (2 * #RT_BLOCK_OVERLAP). For the algorithm (March-X/March-C) to work
// properly this definition MUST take the value 1 as in our example.
// <i> Default: 1
#define RT_BLOCK_OVERLAP (1)

// <o BACKGROUND> The BACKGROUND definition is background used to testing. <f.h>
// In our sample, value 0x00000000uL is used value for background. Of course, we can define
// another value. We recommend using definition like ours (0x00000000uL) because
// it accurately describes the steps of the March-X/March-C algorithm
// described above.
// <i> Default: 0x00000000
#define BACKGROUND ((uint32_t) 0x00000000UL)

// </h>

// <<< end of configuration section >>>

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
#define IEC60370_CM4  0
#define IEC60370_CM33 1
#if defined(__CM4_REV)
#define IEC60370_CPU IEC60370_CM4
#elif defined(__CM33_REV)
#define IEC60370_CPU IEC60370_CM33
#else
#error "Unknown Core type!"
#endif

#endif /* DOXYGEN */

/**************************************************************************/ /**
 * @addtogroup IEC60730_VARIABLE_MEMORY_Test
 * @{
 *****************************************************************************/

/// The definition of #RT_BLOCKSIZE is taken from the definition of #BLOCKSIZE
/// and #RT_BLOCK_OVERLAP.
#define RT_BLOCKSIZE (BLOCKSIZE + (RT_BLOCK_OVERLAP << 1))

//  Pattern 0 is used for stack overflow <f.h>
#define STACK_OVERFLOW_CONST_GUARD_VALUE_0 (0xEEEEEEEEUL)

// <o STACK_OVERFLOW_CONST_GUARD_VALUE_1> Pattern 1 is used for stack overflow <f.h>
#define STACK_OVERFLOW_CONST_GUARD_VALUE_1 (0xCCCCCCCCUL)

// Pattern 2 is used for stack overflow <f.h>
#define STACK_OVERFLOW_CONST_GUARD_VALUE_2 (0xBBBBBBBBUL)

// Pattern 3 is used for stack overflow <f.h>
#define STACK_OVERFLOW_CONST_GUARD_VALUE_3 (0xDDDDDDDDUL)

/** @} (end addtogroup IEC60730_VARIABLE_MEMORY_Test) */

/// This macro is the sample test buffer used for testing CRC algorithm. This
/// value is used in development phase. User DOES NOT take care this definition.
#define IMC_CRCBUFFER_SAMPLETEST "123456789"

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __IEC60730_CONFIG_H__ */
