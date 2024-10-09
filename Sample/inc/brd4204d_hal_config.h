/**************************************************************************//**
 * Copyright (c) 2021 by Silicon Laboratories Inc. All rights reserved.
 *
 * http://developer.silabs.com/legal/version/v11/Silicon_Labs_Software_License_Agreement.txt
 *****************************************************************************/

#ifndef BRD4204D_HAL_CONFIG_H_
#define BRD4204D_HAL_CONFIG_H_

#define BSP_USART0_TX_PIN           (8U)
#define BSP_USART0_TX_PORT          (gpioPortA)

#define BSP_USART0_RX_PIN           (9U)
#define BSP_USART0_RX_PORT          (gpioPortA)

#define BSP_USART0_CTS_PIN          (10U)
#define BSP_USART0_CTS_PORT         (gpioPortA)

#define BSP_USART0_RTS_PIN          (0U)
#define BSP_USART0_RTS_PORT         (gpioPortA)

#define HAL_USART0_BAUD_RATE        (115200UL)
#define HAL_USART0_FLOW_CONTROL     (HAL_USART_FLOW_CONTROL_NONE)
// #define HAL_USART0_FLOW_CONTROL     (HAL_USART_FLOW_CONTROL_HWUART)

#define HAL_VCOM_ENABLE             (1)
#define BSP_VCOM_ENABLE_PIN         (0U)
#define BSP_VCOM_ENABLE_PORT        (gpioPortB)

#endif /* BRD4204D_HAL_CONFIG_H_ */
