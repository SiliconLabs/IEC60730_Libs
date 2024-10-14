/**************************************************************************/ /**
 * Copyright (c) 2021 by Silicon Laboratories Inc. All rights reserved.
 *
 * http://developer.silabs.com/legal/version/v11/Silicon_Labs_Software_License_Agreement.txt
 *****************************************************************************/

#ifndef HAL_CONFIG_BOARD_H
#define HAL_CONFIG_BOARD_H

#define BSP_USART0_TX_PIN  (0U)
#define BSP_USART0_TX_PORT (gpioPortA)
#define BSP_USART0_TX_LOC  (0U)

#define BSP_USART0_RX_PIN  (1U)
#define BSP_USART0_RX_PORT (gpioPortA)
#define BSP_USART0_RX_LOC  (0U)

#define BSP_USART0_CTS_PIN  (2U)
#define BSP_USART0_CTS_PORT (gpioPortA)
#define BSP_USART0_CTS_LOC  (30U)

#define BSP_USART0_RTS_PIN  (3U)
#define BSP_USART0_RTS_PORT (gpioPortA)
#define BSP_USART0_RTS_LOC  (30U)

#define HAL_USART0_BAUD_RATE    (115200UL)
#define HAL_USART0_FLOW_CONTROL (HAL_USART_FLOW_CONTROL_NONE)
// #define HAL_USART0_FLOW_CONTROL     (HAL_USART_FLOW_CONTROL_HWUART)

#define HAL_VCOM_ENABLE      (1)
#define BSP_VCOM_ENABLE_PIN  (5U)
#define BSP_VCOM_ENABLE_PORT (gpioPortA)

#endif // HAL_CONFIG_BOARD_H
