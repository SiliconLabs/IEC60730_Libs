/***************************************************************************/ /**
 * @file
 * @brief Interrupt check
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

#include "sl_iec60730_internal.h"

/**************************************************************************/ /**
 * @addtogroup efr32_iec60730
 * @{
 * @addtogroup IEC60730_IRQ_Test
 * @{
 *****************************************************************************/

void iec60730_IRQCheck(void)
{
  uint8_t index;
  LABEL_DEF(IEC60730_IRQ_BKPT);
  for (index = 0; index < iec60730_IRQFreqBoundsSize; index++) {
    if ((iec60730_IRQExecCount[index] > iec60730_IRQFreqBounds[index].max)
        || (iec60730_IRQExecCount[index] < iec60730_IRQFreqBounds[index].min)) {
      iec60730_SafetyCheck = iec60730_InterruptFail;
    }
    iec60730_IRQExecCount[index] = 0;
  }
  iec60730_programmeCounterCheck |= IEC60730_INTERRUPT_COMPLETE;
}

/** @} (end addtogroup IEC60730_IRQ_Test) */
/** @} (end addtogroup efr32_iec60730) */
