/***************************************************************************//**
 * @file    iec60730_programme_counter.c
 * @brief Program Counter check
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

#include "iec60730_internal.h"

/**************************************************************************//**
 * @addtogroup efr32_iec60730
 * @{ 
 * @addtogroup IEC60730_PROGRAMME_COUNTER
 * @{
 *****************************************************************************/

SI_SEGMENT_VARIABLE(iec60730_programmeCounterCheck, uint16_t, SI_SEG_DATA) = 0;

void iec60730_programmeCounterTest(void)
{
  LABEL_DEF(IEC60730_PC_BKPT);
  // All bits for enabled tests should be set, if not enter safe state
  if (iec60730_programmeCounterCheck != IEC60730_ALL_COMPLETE_BITS)
  {
    // Disable interrupts since we need to enter SafeState as quickly as possible
    __disable_irq();

    iec60730_SafetyCheck = iec60730_ProgrammeCounterFail;
  }
  // Reset flags to make sure that bist is continuously executing
  iec60730_programmeCounterCheck = 0;
}

/** @} (end addtogroup IEC60730_PROGRAMME_COUNTER) */
/** @} (end addtogroup efr32_iec60730) */

