/***************************************************************************/ /**
 * @file iec60730_oem_comm_DMA_mem.c
 * @brief Oem function test uart through com using DMA
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

#include <stdio.h>
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

//#define EXTERAL_COMM_TEST
#define CONFLICT_DMA_TEST

#define RX_BUFF_SIZE   (128)
#define RX_STOP        (4)
#define BUFF_LIMIT     (RX_BUFF_SIZE / RX_STOP)
#define MSG_SIZE       sizeof(messageBuffer_t)
#define COUNT_FAIL_MAX (3)

static messageBuffer_t iec60730_TXbuffer; /*!< Transmit Buffer */
static uint8_t rxBuffer[RX_BUFF_SIZE];    /*!< Receive Buffer */
static uint16_t buffRxIndex = 0;
static uint16_t headRxIndex = 0;
static uint16_t tailRxIndex = 0;
static uint16_t usedRx      = 0;
static uint8_t messageByte  = 0; /*!< Byte to send */
static uint8_t oldmesgByte  = 0xFF;
static UARTDRV_HandleData_t uartHandle;
static UARTDRV_Handle_t commHandle = &uartHandle;
typedef uint8_t usartErrorCode_t;
enum {
  E_UART_NOERROR            = 0,
  E_UART_ERROR_ADDRESS      = 1,
  E_UART_ERROR_FUNC_CRC     = 2,
  E_UART_ERROR_RECEIVED_CRC = 3,
  E_UART_ERROR_PAYLOAD      = 4,
  E_UART_ERROR_HARDWARE     = 5,
};

usartErrorCode_t errorCode   = E_UART_NOERROR;
crc_t receivedCrc            = 0;
crc_t calculatedCrc          = (crc_t) IMC_CRCBUFFER_INIT_VALUE;
uint32_t dupMessage          = 0;
uint32_t countCheckStatus    = 0;
uint32_t countFailed         = 0;
uint32_t countFailedContinue = 0;

DEFINE_BUF_QUEUE(EMDRV_UARTDRV_MAX_CONCURRENT_RX_BUFS, comBufferQueueRxUsart0);
DEFINE_BUF_QUEUE(EMDRV_UARTDRV_MAX_CONCURRENT_TX_BUFS, comBufferQueueTxUsart0);

static sl_iec60730_test_failure_t iec60730_commCheckStatusMessage(void);
static void rxNextBuffer(UARTDRV_Handle_t handle);

static void rxCallback(UARTDRV_Handle_t handle,
                       Ecode_t transferStatus,
                       uint8_t *data,
                       UARTDRV_Count_t transferCount)
{
  if (transferStatus == ECODE_EMDRV_UARTDRV_ABORTED) {
    sl_iec60730_safety_check_error_occur(IEC60730_USART0_FAIL);
    errorCode            = E_UART_ERROR_HARDWARE;
    return;
  }

  if (transferStatus == ECODE_EMDRV_UARTDRV_OK) {
    LABEL_DEF(IEC60730_COMM_CHECK_STATUS_BKPT);
    headRxIndex = (headRxIndex + transferCount) % RX_BUFF_SIZE;
    usedRx += transferCount;
    while (UARTDRV_GetReceiveDepth(commHandle) < 3) {
      if (usedRx > RX_BUFF_SIZE - 2 * RX_STOP) {
        break;
      }
      rxNextBuffer(commHandle);
    }
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
  rxNextBuffer(commHandle);
  rxNextBuffer(commHandle);
}

void iec60730_commDeInit(void)
{
  UARTDRV_DeInit(commHandle);
}

void iec60730_commTransmitStatusMessage(void)
{
  iec60730_commSendMessage(messageByte);
  if (oldmesgByte == messageByte) {
    dupMessage++;
  } else {
    oldmesgByte = messageByte;
  }
  sl_iec60730_program_counter_check |= IEC60730_COMMS_COMPLETE;
}

void iec60730_commSendMessage(uint8_t byte)
{
#ifdef EXTERAL_COMM_TEST
  LABEL_DEF(IEC60730_TRANSMIT_DISABLE_BKPT);
  // Packet begins with transmitting device address
  iec60730_TXbuffer.device_address = IEC60730_COMM_DEVICE_ADDRESS;

  // Payload in this example is one byte
  iec60730_TXbuffer.message = byte;

  crc_t crcValue           = (crc_t) IMC_CRCBUFFER_INIT_VALUE;
  updateCrcParams_t update = IMC_CRCBUFFER_UPDATE_DEFAULT;

  // Calculate CRC using CRC generating function included in library
  if (IEC60730_TEST_FAILED
      == iec60730_updateCRCWithDataBuffer(&update,
                                          &crcValue,
                                          (uint8_t *) (&iec60730_TXbuffer),
                                          MSG_SIZE - sizeof(crc_t))) {
    iec60730_SafeState(IEC60730_OEM_FAIL_1);
  }

  iec60730_TXbuffer.crc = crcValue;

  if (ECODE_OK
      != UARTDRV_Transmit(commHandle,
                          (uint8_t *) (&iec60730_TXbuffer),
                          MSG_SIZE,
                          txCallback)) {
    while (UARTDRV_Transmit(commHandle,
                            (uint8_t *) (&iec60730_TXbuffer),
                            MSG_SIZE,
                            txCallback)
           != ECODE_OK) {}
  }
#else
  UNUSED_VAR(iec60730_TXbuffer);
#endif /* EXTERAL_COMM_TEST */
}

void iec60730_commInitReceiveStatusMessage(void)
{
#ifdef EXTERAL_COMM_TEST
  if (usedRx >= MSG_SIZE) {
    uint16_t rxLength   = usedRx;
    uint16_t addrOffset = 1;

    countCheckStatus++;
    if (IEC60730_USART0_FAIL == iec60730_commCheckStatusMessage()) {
      countFailed++;
      countFailedContinue++;

      if (COUNT_FAIL_MAX == countFailedContinue) {
        sl_iec60730_safety_check_error_occur(IEC60730_USART0_FAIL);
        return;
      }

      for (; addrOffset < rxLength; addrOffset++) {
        if (rxBuffer[tailRxIndex + addrOffset] == IEC60730_COMM_DEVICE_ADDRESS)
          break;
      }
    } else {
      addrOffset          = MSG_SIZE;
      countFailedContinue = 0;
    }

    IEC60370_DECLARE_IRQ_STATE;
    IEC60370_ENTER_ATOMIC();
    tailRxIndex = (tailRxIndex + addrOffset) % RX_BUFF_SIZE;
    usedRx -= addrOffset;
    while (UARTDRV_GetReceiveDepth(commHandle) < 2) {
      if (usedRx > RX_BUFF_SIZE - 2 * RX_STOP) {
        break;
      }
      rxNextBuffer(commHandle);
    }
    IEC60370_EXIT_ATOMIC();
  }
#else /* !EXTERAL_COMM_TEST */
#ifdef CONFLICT_DMA_TEST
  if (usedRx >= MSG_SIZE) {
    // call this function to remove warning unused function
    (void) iec60730_commCheckStatusMessage();
    IEC60370_DECLARE_IRQ_STATE;
    IEC60370_ENTER_ATOMIC();
    tailRxIndex = (tailRxIndex + MSG_SIZE) % RX_BUFF_SIZE;
    usedRx -= MSG_SIZE;
    while (UARTDRV_GetReceiveDepth(commHandle) < 2) {
      if (usedRx > RX_BUFF_SIZE - 2 * RX_STOP) {
        break;
      }
      rxNextBuffer(commHandle);
    }
    IEC60370_EXIT_ATOMIC();
  }
#endif /* CONFLICT_DMA_TEST */
#endif /* EXTERAL_COMM_TEST */
}

sl_iec60730_test_failure_t iec60730_commCheckStatusMessage(void)
{
#ifdef EXTERAL_COMM_TEST
  // If received and expected address do not match, enter safe state
  messageBuffer_t iec60730_Rxbuffer;

  iec60730_Rxbuffer.device_address = rxBuffer[tailRxIndex];
  iec60730_Rxbuffer.message        = rxBuffer[(tailRxIndex + 1) % RX_BUFF_SIZE];
  iec60730_Rxbuffer.crc = rxBuffer[(tailRxIndex + 3) % RX_BUFF_SIZE] << 8
                          | rxBuffer[(tailRxIndex + 2) % RX_BUFF_SIZE];

  if (iec60730_Rxbuffer.device_address != IEC60730_COMM_DEVICE_ADDRESS) {
    errorCode = E_UART_ERROR_ADDRESS;
    return IEC60730_USART0_FAIL;
  }

  calculatedCrc            = (crc_t) IMC_CRCBUFFER_INIT_VALUE;
  updateCrcParams_t update = IMC_CRCBUFFER_UPDATE_DEFAULT;

  // Calculate CRC using CRC generating function included in library
  if (IEC60730_TEST_FAILED
      == iec60730_updateCRCWithDataBuffer(&update,
                                          &calculatedCrc,
                                          (uint8_t *) (&iec60730_Rxbuffer),
                                          MSG_SIZE - sizeof(crc_t))) {
    errorCode = E_UART_ERROR_FUNC_CRC;
    return IEC60730_USART0_FAIL;
  }

  receivedCrc = iec60730_Rxbuffer.crc;

  // If CRCs don't match, enter safe state
  if (calculatedCrc != receivedCrc) {
    errorCode = E_UART_ERROR_RECEIVED_CRC;
    return IEC60730_USART0_FAIL;
  }

  // Also check payload to make sure that 'status' message is what is expected
  // if (iec60730_RXbuffer->message != message_byte) {
  //  errorCode = E_UART_ERROR_PAYLOAD;
  //  return IEC60730_USART0_FAIL;
  // }

  // For the purposes of this example, the status message is an incrementing value
  messageByte = messageByte + 1;
#endif

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

bool Vmc_PreRunMarchXC_Step(uint32_t *startAddr, uint32_t blockSize)
{
  if (!(startAddr + blockSize < (uint32_t *) rxBuffer
        || startAddr > (uint32_t *) &rxBuffer[RX_BUFF_SIZE])) {
    DMADRV_PauseTransfer(commHandle->rxDmaCh);
  }
  return true;
}

void Vmc_PostRunMarchXC_Step(uint32_t *startAddr, uint32_t blockSize)
{
  if (!(startAddr + blockSize < (uint32_t *) rxBuffer
        || startAddr > (uint32_t *) &rxBuffer[RX_BUFF_SIZE])) {
    DMADRV_ResumeTransfer(commHandle->rxDmaCh);
  }
}

void rxNextBuffer(UARTDRV_Handle_t handle)
{
  if (ECODE_OK
      == UARTDRV_Receive(handle,
                         &rxBuffer[buffRxIndex * RX_STOP],
                         RX_STOP,
                         rxCallback)) {
    buffRxIndex = (buffRxIndex + 1) % BUFF_LIMIT;
  }
}
