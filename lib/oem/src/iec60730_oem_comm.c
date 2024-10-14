/***************************************************************************/ /**
 * @file iec60730_oem_comm.c
 * @brief Oem function test uart through com
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

#include <string.h>
#include "uartdrv.h"
#include "hal-config-types.h"
#include "iec60730.h"
#include "iec60730_oem_comm.h"
#include HAL_CONFIG_HEADER

#if defined(_USART_ROUTELOC0_MASK)
#define USART0_INIT                                                            \
  {                                                                            \
      USART0,               /* USART port                   */                 \
      HAL_USART0_BAUD_RATE, /* Baud rate                    */                 \
      BSP_USART0_TX_LOC,    /* USART Tx pin location number */                 \
      BSP_USART0_RX_LOC,    /* USART Rx pin location number */                 \
      (USART_Stopbits_TypeDef)                                                 \
          USART_FRAME_STOPBITS_ONE, /* Stop bits                    */         \
      (USART_Parity_TypeDef)                                                   \
          USART_FRAME_PARITY_NONE, /* Parity                       */          \
      (USART_OVS_TypeDef)                                                      \
          USART_CTRL_OVS_X16, /* Oversampling mode            */               \
      false,                  /* Majority vote disable        */               \
      (UARTDRV_FlowControlType_t)                                              \
          HAL_USART0_FLOW_CONTROL, /* Flow control                 */          \
      BSP_USART0_CTS_PORT,         /* CTS port number              */          \
      BSP_USART0_CTS_PIN,          /* CTS pin number               */          \
      BSP_USART0_RTS_PORT,         /* RTS port number              */          \
      BSP_USART0_RTS_PIN,          /* RTS pin number               */          \
      NULL,                        /* RX operation queue           */          \
      NULL,                        /* TX operation queue           */          \
      BSP_USART0_CTS_LOC,          /* CTS pin location             */          \
      BSP_USART0_RTS_LOC           /* RTS pin location             */          \
  }
#elif defined(_GPIO_USART_ROUTEEN_MASK) // #define USART0_INIT
#define USART0_INIT                                                            \
  {                                                                            \
      USART0,               /* USART port                   */                 \
      HAL_USART0_BAUD_RATE, /* Baud rate                    */                 \
      BSP_USART0_TX_PORT,   /* TX port number               */                 \
      BSP_USART0_RX_PORT,   /* RX port number               */                 \
      BSP_USART0_TX_PIN,    /* TX pin number                */                 \
      BSP_USART0_RX_PIN,    /* RX pin number                */                 \
      0,                    /* UART instance number         */                 \
      (USART_Stopbits_TypeDef)                                                 \
          USART_FRAME_STOPBITS_ONE, /* Stop bits                    */         \
      (USART_Parity_TypeDef)                                                   \
          USART_FRAME_PARITY_NONE, /* Parity                       */          \
      (USART_OVS_TypeDef)                                                      \
          USART_CTRL_OVS_X16, /* Oversampling mode            */               \
      false,                  /* Majority vote disable        */               \
      (UARTDRV_FlowControlType_t)                                              \
          HAL_USART0_FLOW_CONTROL, /* Flow control                 */          \
      BSP_USART0_CTS_PORT,         /* CTS port number              */          \
      BSP_USART0_CTS_PIN,          /* CTS pin number               */          \
      BSP_USART0_RTS_PORT,         /* RTS port number              */          \
      BSP_USART0_RTS_PIN,          /* RTS pin number               */          \
      NULL,                        /* RX operation queue           */          \
      NULL,                        /* TX operation queue           */          \
  }
#else
#define USART0_INIT                                                            \
  {                                                                            \
      USART0,               /* USART port                   */                 \
      HAL_USART0_BAUD_RATE, /* Baud rate                    */                 \
      BSP_USART0_ROUTE_LOC, /* USART pins location number   */                 \
      (USART_Stopbits_TypeDef)                                                 \
          USART_FRAME_STOPBITS_ONE, /* Stop bits                    */         \
      (USART_Parity_TypeDef)                                                   \
          USART_FRAME_PARITY_NONE, /* Parity                       */          \
      (USART_OVS_TypeDef)                                                      \
          USART_CTRL_OVS_X16, /* Oversampling mode            */               \
      (UARTDRV_FlowControlType_t)                                              \
          HAL_USART0_FLOW_CONTROL, /* Flow control                 */          \
      BSP_USART0_CTS_PORT,         /* CTS port number              */          \
      BSP_USART0_CTS_PIN,          /* CTS pin number               */          \
      BSP_USART0_RTS_PORT,         /* RTS port number              */          \
      BSP_USART0_RTS_PIN,          /* RTS pin number               */          \
      NULL,                        /* RX operation queue           */          \
      NULL                         /* TX operation queue           */          \
  }
#endif //defined( _USART_ROUTELOC0_MASK )

//#define TOOL_LOOPBACK

static messageBuffer_t iec60730_TXbuffer; /*!< Transmit Buffer */
static messageBuffer_t iec60730_RXbuffer; /*!< Receive Buffer */
static uint8_t message_byte = 0;          /*!< Byte to send */
static UARTDRV_HandleData_t uartHandle;
static UARTDRV_Handle_t commHandle = &uartHandle;
// Use 2 variables to sync TX-RX
static bool readyToSendTxMessage  = true;
static bool readyToCheckRxMessage = false;
typedef uint8_t usartErrorCode_t;
enum {
  E_UART_NOERROR            = 0,
  E_UART_ERROR_ADDRESS      = 1,
  E_UART_ERROR_FUNC_CRC     = 2,
  E_UART_ERROR_RECEIVED_CRC = 3,
  E_UART_ERROR_PAYLOAD      = 4,
  E_UART_ERROR_HARDWARE     = 5,
};

usartErrorCode_t errorCode = E_UART_NOERROR;
crc_t calculatedCrc        = (crc_t) IMC_CRCBUFFER_INIT_VALUE;

DEFINE_BUF_QUEUE(1, comBufferQueueRxUsart0);
DEFINE_BUF_QUEUE(1, comBufferQueueTxUsart0);

static sl_iec60730_test_failure_t iec60730_commCheckStatusMessage(void);

static void rxCallback(UARTDRV_Handle_t handle,
                       Ecode_t transferStatus,
                       uint8_t *data,
                       UARTDRV_Count_t transferCount)
{
  (void) data;
  (void) handle;
  (void) transferCount;

  if (transferStatus == ECODE_EMDRV_UARTDRV_ABORTED) {
    sl_iec60730_safety_check_error_occur(IEC60730_USART0_FAIL);
    errorCode            = E_UART_ERROR_HARDWARE;
    return;
  }

  if (transferStatus == ECODE_EMDRV_UARTDRV_OK) {
    LABEL_DEF(IEC60730_COMM_CHECK_STATUS_BKPT);
    readyToCheckRxMessage = true;
    sl_iec60730_program_counter_check |= IEC60730_COMMS_COMPLETE;
    LABEL_DEF(IEC60730_COMM_BIST_FLAG_BKPT);
    sl_iec60730_program_counter_check = sl_iec60730_program_counter_check;
  }
}

static void txCallback(UARTDRV_Handle_t handle,
                       Ecode_t transferStatus,
                       uint8_t *data,
                       UARTDRV_Count_t transferCount)
{
  (void) data;
  (void) handle;
  (void) transferCount;

  if (transferStatus == ECODE_EMDRV_UARTDRV_ABORTED) {
    sl_iec60730_safety_check_error_occur(IEC60730_USART0_FAIL);
    errorCode            = E_UART_ERROR_HARDWARE;
  }
}

void iec60730_commInit(void)
{
  UARTDRV_InitUart_t initCom = USART0_INIT;

  initCom.rxQueue = (UARTDRV_Buffer_FifoQueue_t *) &comBufferQueueRxUsart0;
  initCom.txQueue = (UARTDRV_Buffer_FifoQueue_t *) &comBufferQueueTxUsart0;

  UARTDRV_InitUart(commHandle, &initCom);
  GPIO_PinModeSet(commHandle->rxPort, commHandle->rxPin, gpioModeInputPull, 1);
#ifdef HAL_VCOM_ENABLE
  GPIO_PinModeSet(BSP_VCOM_ENABLE_PORT,
                  BSP_VCOM_ENABLE_PIN,
                  gpioModePushPull,
                  1);
#endif /* HAL_VCOM_ENABLE */
  UARTDRV_Receive(commHandle,
                  (uint8_t *) (&iec60730_RXbuffer),
                  sizeof(messageBuffer_t),
                  rxCallback);
}

void iec60730_commDeInit(void)
{
  UARTDRV_DeInit(commHandle);
}

void iec60730_commTransmitStatusMessage(void)
{
  if (readyToSendTxMessage) {
#ifdef TOOL_LOOPBACK
    readyToSendTxMessage = false;
#endif
    iec60730_commSendMessage(message_byte);
    sl_iec60730_program_counter_check |= IEC60730_COMMS_COMPLETE;
  }
}

void iec60730_commSendMessage(uint8_t message_byte)
{
  LABEL_DEF(IEC60730_TRANSMIT_DISABLE_BKPT);
  // Packet begins with transmitting device address
  iec60730_TXbuffer.device_address = IEC60730_COMM_DEVICE_ADDRESS;

  // Payload in this example is one byte
  iec60730_TXbuffer.message = message_byte;

  crc_t crcValue           = (crc_t) IMC_CRCBUFFER_INIT_VALUE;
  updateCrcParams_t update = IMC_CRCBUFFER_UPDATE_DEFAULT;

  // Calculate CRC using CRC generating function included in library
  if (IEC60730_TEST_FAILED
      == iec60730_updateCRCWithDataBuffer(&update,
                                          &crcValue,
                                          (uint8_t *) (&iec60730_TXbuffer),
                                          sizeof(messageBuffer_t)
                                              - sizeof(crc_t))) {
    iec60730_SafeState(IEC60730_OEM_FAIL_1);
  }

  iec60730_TXbuffer.crc = crcValue;

  UARTDRV_Transmit(commHandle,
                   (uint8_t *) (&iec60730_TXbuffer),
                   sizeof(messageBuffer_t),
                   txCallback);
}

void iec60730_commInitReceiveStatusMessage(void)
{
  if (readyToCheckRxMessage) {
    readyToCheckRxMessage = false;
    //DMADRV_StopTransfer(commHandle->rxDmaCh);
    if (iec60730_commCheckStatusMessage() == IEC60730_USART0_FAIL) {
      sl_iec60730_safety_check_error_occur(IEC60730_USART0_FAIL);
    }
    UARTDRV_Receive(commHandle,
                    (uint8_t *) (&iec60730_RXbuffer),
                    sizeof(messageBuffer_t),
                    rxCallback);
    readyToSendTxMessage = true;
  }
}

sl_iec60730_test_failure_t iec60730_commCheckStatusMessage(void)
{
  // If received and expected address do not match, enter safe state
  if (iec60730_RXbuffer.device_address != IEC60730_COMM_DEVICE_ADDRESS) {
    errorCode = E_UART_ERROR_ADDRESS;
    return IEC60730_USART0_FAIL;
  }

  calculatedCrc            = (crc_t) IMC_CRCBUFFER_INIT_VALUE;
  updateCrcParams_t update = IMC_CRCBUFFER_UPDATE_DEFAULT;

  // Calculate CRC using CRC generating function included in library
  if (IEC60730_TEST_FAILED
      == iec60730_updateCRCWithDataBuffer(&update,
                                          &calculatedCrc,
                                          (uint8_t *) (&iec60730_RXbuffer),
                                          sizeof(messageBuffer_t)
                                              - sizeof(crc_t))) {
    errorCode = E_UART_ERROR_FUNC_CRC;
    return IEC60730_USART0_FAIL;
  }

#ifdef UART_CRC_CHECK
  crc_t receivedCrc = iec60730_RXbuffer.crc;

  // If CRCs don't match, enter safe state
  if (calculatedCrc != receivedCrc) {
    errorCode = E_UART_ERROR_RECEIVED_CRC;
    return IEC60730_USART0_FAIL;
  }
#endif // UART_CRC_CHECK

#ifdef UART_PAYLOAD_CHECK
  // Also check payload to make sure that 'status' message is what is expected
  if (iec60730_RXbuffer.message != message_byte) {
    errorCode = E_UART_ERROR_PAYLOAD;
    return IEC60730_USART0_FAIL;
  }
#endif // UART_PAYLOAD_CHECK

  // For the purposes of this example, the status message is an incrementing value
  message_byte = message_byte + 1;

  return IEC60730_NO_FAILURE;
}

void iec60730_commLog(const uint8_t *str)
{
  if (str != NULL) {
    UARTDRV_Transmit(commHandle,
                     (uint8_t *) str,
                     strlen((char *) str),
                     txCallback);
  }
}
