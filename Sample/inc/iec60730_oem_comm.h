/**************************************************************************//**
 * Copyright (c) 2021 by Silicon Laboratories Inc. All rights reserved.
 *
 * http://developer.silabs.com/legal/version/v11/Silicon_Labs_Software_License_Agreement.txt
 *****************************************************************************/

#ifndef IEC60730_OEM_COMM_H_
#define IEC60730_OEM_COMM_H_

#include "iec60730.h"

/**************************************************************************//**
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

/**************************************************************************//**
 * public Initialize UART
 *
 * @return void
 *
 * This function initialize UART
 *****************************************************************************/
void iec60730_commInit(void);

/**************************************************************************//**
 * public Deinitialize UART
 *
 * @return void
 *
 * This function deinitialize UART
 *****************************************************************************/
void iec60730_commDeInit(void);

/**************************************************************************//**
 * public Ready peripheral to read a status message
 *
 * @return void
 *
 * This function calls into the UART peripheral library to receive
 * the status packet.
 *****************************************************************************/
void iec60730_commInitReceiveStatusMessage(void);

/**************************************************************************//**
 * public Transmit status message
 *
 * @return void
 *
 * This function passes a status message buffer into the UART peripheral library
 * for transmit using @ref iec60730_commSendMessage.
 *****************************************************************************/
void iec60730_commTransmitStatusMessage(void);

/**************************************************************************//**
 * public Check received message
 *
 * @return void
 *
 * This function examines the received buffer to check that the CRC is valid.
 * @returns Returns #iec60730_TestFailed if message does not provide 
 * correct CRC and address, #iec60730_TestPassed otherwise.
 *****************************************************************************/
iec60730_TestResult_t iec60730_commCheckReceivedMessage(void);

/**************************************************************************//**
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

/**************************************************************************//**
 * public Transmit Log
 *
 * @param str Log string
 *
 * @return void
 *
 * This function sends a string of Log.
 *****************************************************************************/
void iec60730_commLog(const uint8_t* str);

/// Sets the address used by the transmitter and checked by receiver in the comm protocol.
#define IEC60730_COMM_DEVICE_ADDRESS 0x01

/// Buffer used in comm that includes IEC60730-compliant address and CRC.
typedef struct messageBuffer {
  uint8_t   device_address;     ///< 8-bit address of transmitting device
  uint8_t   message;            ///< Payload of buffer
  crc_t     crc;                ///< CRC covering all other bytes in packet
} messageBuffer_t;

/** @} (end addtogroup IEC60730_OEM_COMM_Test) */
/** @} (end addtogroup efr32_iec60730) */

#endif /* IEC60730_OEM_COMM_H_ */
