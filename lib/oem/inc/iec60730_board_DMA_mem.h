/***************************************************************************/ /**
 * @file  iec60730_board_DMA_mem
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

/* Invariable Memory */
extern uint32_t __FlashStart;
#define ROM_START ((uint32_t *) (&__FlashStart))

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

// Tick 10 ms
#define SYSTICK_10MS   ((uint32_t) 1UL)
#define SYSTICK_100MS  ((uint32_t) 10UL)
#define SYSTICK_1000MS ((uint32_t) 100UL)
// Tick 100 ms
#define SYSTICK__100MS  ((uint32_t) 1UL)
#define SYSTICK__1000MS ((uint32_t) 10UL)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* IEC60730_BOARD_H_ */
