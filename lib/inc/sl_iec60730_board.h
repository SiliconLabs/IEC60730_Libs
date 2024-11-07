/***************************************************************************/ /**
 * @file  iec60730_board
 * @brief Internal definitions
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

#ifndef IEC60730_BOARD_H_
#define IEC60730_BOARD_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// Standard libraries
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

/**************************************************************************/ /**
 * @addtogroup efr32_iec60730
 * @{
 * @addtogroup IEC60730_INVARIABLE_MEMORY_Test
 * @{
 *****************************************************************************/

/* Invariable Memory */
extern uint32_t __FlashStart;

/// The #SL_IEC60730_ROM_START definition describes the start address of Flash for CRC
/// calculation. This definition MUST be alignment of #SL_IEC60730_FLASH_BLOCK and can be
/// changed by user so that the value DOES NOT exceed the end address of Flash
/// (the #SL_IEC60730_ROM_END definition). Otherwise, #sl_iec60730_imc_post and #sl_iec60730_imc_bist
/// return #IEC60730_TEST_FAILED. The default value of the #SL_IEC60730_ROM_START can be found in
/// sl_iec60730.h file.
///
/// In case you change value of this definition then you SHOULD change the 5th
/// parameter of the script \ref gcc_crcXY when running the Post Build.
///
/// In our example, we use the variable __FlashStart provided by the linker file
/// to simply define the start address of Flash. User can redefine #SL_IEC60730_ROM_START
/// as follows.
/// ```
/// #define SL_IEC60730_ROM_START  ((uint32_t *)(&__FlashStart))
/// ```
#ifndef SL_IEC60730_ROM_END
#define SL_IEC60730_ROM_START ((uint32_t *) (&__FlashStart))
#endif

/// The #SL_IEC60730_ROM_END definition describes the end address of Flash. It is the
/// address of #__checksum variables. In this version, users SHOULD not
/// change this definition. Refer to the example in
/// \ref invariable_memory_check_example_flowchart, to better understand the
/// #SL_IEC60730_ROM_START, and #SL_IEC60730_ROM_END definitions.
#ifndef SL_IEC60730_ROM_END
#define SL_IEC60730_ROM_END ((uint32_t *) (&__checksum))
#endif

/** @} (end addtogroup IEC60730_INVARIABLE_MEMORY_Test) */

/**************************************************************************/ /**
 * @addtogroup IEC60730_VARIABLE_MEMORY_Test
 * @{
 *****************************************************************************/

/* Variable Memory */
extern uint32_t __classb_start;
extern uint32_t __classb_end;
extern uint32_t __StackTop;
extern uint32_t __RamStart;
extern uint32_t __ClassBLimit;

#define RAM_START  ((uint32_t *) (&__RamStart))
#define RAM_END    ((uint32_t *) ((uint32_t) RAM_BACKUP - 1))
#define RAM_BACKUP ((uint32_t *) (&__StackTop))

#define CLASSB_START ((uint32_t *) (&__classb_start))
#define CLASSB_END   ((uint32_t *) ((uint32_t) (&__ClassBLimit) - 1))

#define RAMTEST_START CLASSB_START
#define RAMTEST_END   CLASSB_END

/** @} (end addtogroup IEC60730_VARIABLE_MEMORY_Test) */
/** @} (end addtogroup efr32_iec60730) */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* IEC60730_BOARD_H_ */
