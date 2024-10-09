/***************************************************************************//**
 * @file iec60730_oem.h
 * @brief Watchdog test cases
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

#ifndef __IEC60730_OEM_H__
#define __IEC60730_OEM_H__

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

// OEM specific header file
#include "em_core.h"

#include "em_gpcrc.h"
#ifndef CRC_USE_SW
#include "em_cmu.h"
#endif /* CRC_USE_SW */

#ifdef SEGGER_RTT_PRESENT
#include "iec60730_segger_trace.h"
#endif

/**************************************************************************//**
 * @addtogroup efr32_iec60730
 * @{
 * @addtogroup IEC60730_OEM
 * @{
 * @section communications_hardware_architecture Hardware Architecture
 *
 * \link
 *
 * \image
 *****************************************************************************/
/** @} (end addtogroup IEC60730_OEM) */
/** @} (end addtogroup efr32_iec60730) */

// Enter ATOMIC section.
#define IEC60370_ENTER_ATOMIC()	CORE_ENTER_ATOMIC()
// Exit ATOMIC section.
#define IEC60370_EXIT_ATOMIC()	CORE_EXIT_ATOMIC()
// Allocate storage for PRIMASK or BASEPRI value
#define IEC60370_DECLARE_IRQ_STATE CORE_DECLARE_IRQ_STATE;

// OEM ICM
// Enter ATOMIC section of IMC Bist
#define IEC60730_IMC_BIST_ENTER_ATOMIC() \
  CORE_DECLARE_IRQ_STATE; \
  CORE_ENTER_ATOMIC()

// Exit ATOMIC section of IMC Post
#define IEC60730_IMC_BIST_EXIT_ATOMIC() \
  CORE_EXIT_ATOMIC()

#define INVAR_BLOCKS_PER_BIST (512)

// CRC
typedef GPCRC_TypeDef CRC_TypeDef;
typedef GPCRC_Init_TypeDef CRC_INIT_TypeDef;

#define CRC_INIT(crc, init)     GPCRC_Init(crc, init)
#define CRC_RESET(crc)          GPCRC_Reset(crc)
#define CRC_START(crc)          GPCRC_Start(crc)
#define CRC_INPUTU32(crc, d)    GPCRC_InputU32(crc, d)
#define CRC_INPUTU16(crc, d)    GPCRC_InputU16(crc, d)
#define CRC_INPUTU8(crc, d)     GPCRC_InputU8(crc, d)
#define CRC_DATAREAD(crc)       GPCRC_DataRead(crc)
#define CRC_DATAREADBITREVERSED(crc)      GPCRC_DataReadBitReversed(crc)
#define CRC_DATAREADBYTEREVERSED(crc)     GPCRC_DataReadByteReversed(crc)

// OEM VCM
// Enter ATOMIC section of VMC Post
#define IEC60730_VMC_POST_ENTER_ATOMIC()

// Exit ATOMIC section of VMC Post
#define IEC60730_VMC_POST_EXIT_ATOMIC()

// Enter ATOMIC section of VMC Bist
#define IEC60730_VMC_BIST_ENTER_ATOMIC() \
  CORE_DECLARE_IRQ_STATE; \
  CORE_ENTER_ATOMIC()

// Exit ATOMIC section of VMC Bist
#define IEC60730_VMC_BIST_EXIT_ATOMIC() \
  CORE_EXIT_ATOMIC()

#define VAR_BLOCKS_PER_BIST   (256)

// Declare Bist
#ifndef DECLARE_BENMARK_BIST
#define DECLARE_BENMARK_BIST()
#endif

// Start Benmark Bist
#ifndef STARTEXEC_BENMARK_BIST
#define STARTEXEC_BENMARK_BIST()
#endif

// Terminate Benmark Bist
#ifndef TERMINATE_BENMARK_BIST
#define TERMINATE_BENMARK_BIST()
#endif

// IRQ Bounds Size
#define IEC60730_IRQ_SIZE 8

// Bist execution status
extern volatile bool BistCheck_Flag;
// USART run flag
extern volatile bool usart_Flag;

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif

