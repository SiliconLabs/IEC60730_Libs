/***************************************************************************/ /**
 * @file ie60730_oem_comm.h
 * @brief
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

#ifndef IEC60730_OEM_COMM_H_
#define IEC60730_OEM_COMM_H_

#include "iec60730.h"

/**************************************************************************/ /**
 * @addtogroup efr32_iec60730
 * @{
 * @addtogroup IEC60730_OEM_COMM_Test
 * @{
 * @details These files provide an example communications protocol that meet
 * IEC60730 requirements, which include address redundancy, a CRC check on data payloads,
 * and a periodic transfer of data.  This example uses UART as its protocol.
 *
 * This protocol simulates both the transmitter and receiver in an IEC60730 compliant
 * application.  The UART RX and TX pins must be shorted together in order for the
 * example to successfully receive transmitted data.
 *****************************************************************************/

/**************************************************************************/ /**
 * public Initialize UART
 *
 * @return void
 *
 * This function initialize UART
 *****************************************************************************/
void iec60730_commInit(void);

/**************************************************************************/ /**
 * public Deinitialize UART
 *
 * @return void
 *
 * This function deinitialize UART
 *****************************************************************************/
void iec60730_commDeInit(void);

/**************************************************************************/ /**
 * public Ready peripheral to read a status message
 *
 * @return void
 *
 * This function calls into the UART peripheral library to receive
 * the status packet.
 *****************************************************************************/
void iec60730_commInitReceiveStatusMessage(void);

/**************************************************************************/ /**
 * public Transmit status message
 *
 * @return void
 *
 * This function passes a status message buffer into the UART peripheral library
 * for transmit using @ref iec60730_commSendMessage.
 *****************************************************************************/
void iec60730_commTransmitStatusMessage(void);

/**************************************************************************/ /**
 * public Check received message
 *
 * @return void
 *
 * This function examines the received buffer to check that the CRC is valid.
 * @returns Returns #IEC60730_TEST_FAILED if message does not provide
 * correct CRC and address, #IEC60730_TEST_PASSED otherwise.
 *****************************************************************************/
sl_iec60730_test_result_t iec60730_commCheckReceivedMessage(void);

/**************************************************************************/ /**
 * public Transmit message
 *
 * @param message_byte 1-byte data payload to be transmitted
 *
 * @return void
 *
 * This function sends a 1-byte payload with IEC-compliant header
 * and footer overhead.
 *****************************************************************************/
void iec60730_commSendMessage(uint8_t message_byte);

/**************************************************************************/ /**
 * public Transmit Log
 *
 * @param str Log string
 *
 * @return void
 *
 * This function sends a string of Log.
 *****************************************************************************/
void iec60730_commLog(const uint8_t *str);

/// Sets the address used by the transmitter and checked by receiver in the comm protocol.
#define IEC60730_COMM_DEVICE_ADDRESS 0x01

/// Buffer used in comm that includes IEC60730-compliant address and CRC.
typedef struct messageBuffer {
  uint8_t device_address; ///< 8-bit address of transmitting device
  uint8_t message;        ///< Payload of buffer
  crc_t crc;              ///< CRC covering all other bytes in packet
} messageBuffer_t;

/** @} (end addtogroup IEC60730_OEM_COMM_Test) */
/** @} (end addtogroup efr32_iec60730) */

#endif /* IEC60730_OEM_COMM_H_ */
