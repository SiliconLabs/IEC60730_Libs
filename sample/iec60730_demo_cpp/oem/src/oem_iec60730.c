/***************************************************************************/ /**
 * @file iec60730_demo_main.c
 * @brief demo main function
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

#include "oem_iec60730.h"

#ifdef SEGGER_RTT_PRESENT
#include "SEGGER_SYSVIEW.h"
#endif /* SEGGER */

#if defined(__ICCARM__)
#pragma diag_suppress = Pe111
#endif // IAR

#define IEC60730_IRQ_SIZE    8
#define OEM_NUM_IRQ_CHECK    1

__no_init sl_iec60730_imc_params_t oem_imc_test __CLASSB_RAM;
__no_init sl_iec60730_vmc_params_t oem_vmc_test;

uint32_t oem_tick_uart_counter;

// Bist execution status
volatile bool oem_bist_check_flag;
// USART run flag
volatile bool oem_usart_flag;

volatile uint32_t oem_err_test = 0;

// Global variables used for IRQ check
volatile SL_IEC60730_IRQ_TYPE_VARIABLE oem_irq_exec_count[IEC60730_IRQ_SIZE] = {0};
const sl_iec60730_irq_execution_bounds_t oem_irq_freq_bounds[IEC60730_IRQ_SIZE] = {{.min = 9, .max = 11},
                                                                            {.min = 9, .max = 11},
                                                                            {.min = 9, .max = 11},
                                                                            {.min = 9, .max = 11},
                                                                            {.min = 9, .max = 11},
                                                                            {.min = 9, .max = 11},
                                                                            {.min = 9, .max = 11},
                                                                            {.min = 9, .max = 11}};

sl_iec60730_irq_cfg_t oem_irq_config = {&oem_irq_exec_count[0],
                                        &oem_irq_freq_bounds[0],
                                        OEM_NUM_IRQ_CHECK};

/**************************************************************************/ /**
 * @brief iec60730 App Initialize
 *
 * return void
 *
 * App Init iec60730
 *****************************************************************************/
void app_oem_init(void)
{
  oem_system_config();

  // Configure parameters before running #sl_iec60730_post
  oem_iec60730_config();

  oem_adj_top_val_timer();

  // enable timers for BIST testing
  oem_timers_enable();

  // Initialize parameters before running #sl_iec60730_post
  oem_iec60730_init();

  // Power on self test
  sl_iec60730_post();
}

/**************************************************************************/ /**
 * @brief iec60730 App Process Action
 *
 * return void
 *
 * App process action iec60730
 *****************************************************************************/
void app_oem_process_action(void)
{
  // Application tasks
  // Process UART transmit/receive
  oem_comm_init_receive_status_message();
  if (oem_usart_flag) {
    oem_usart_flag = false;
    oem_tick_uart_counter++;
    if (oem_tick_uart_counter >= SYSTICK_10MS) {
      oem_tick_uart_counter = 0x0;
      // oem_comm_init_receive_status_message();
      oem_comm_transmit_status_message();
    }
  }
  // System check tasks
  // Force the OEM test results to completed
  if (!oem_err_test) {
    sl_iec60730_program_counter_check |=
        IEC60730_GPIO_COMPLETE | IEC60730_ANALOG_COMPLETE
        | IEC60730_OEM0_COMPLETE | IEC60730_OEM1_COMPLETE
        | IEC60730_OEM2_COMPLETE | IEC60730_OEM3_COMPLETE
        | IEC60730_OEM4_COMPLETE | IEC60730_OEM5_COMPLETE
        | IEC60730_OEM6_COMPLETE | IEC60730_OEM7_COMPLETE;
  }
  // Build In self Test
  STARTEXEC_BENMARK_BIST();
  sl_iec60730_bist();
  oem_comm_log((uint8_t *) "Pass-Test\n");
  TERMINATE_BENMARK_BIST();
}

/**************************************************************************/ /**
 * @brief Configuration
 *
 * return void
 *
 * Config parameters before running #sl_iec60730_post
 *****************************************************************************/
void oem_iec60730_config(void)
{
  /// Config parameter before running #sl_iec60730_post
  oem_imc_test.gpcrc = SL_IEC60730_DEFAULT_GPRC;

  oem_vmc_test.start = RAMTEST_START;
  oem_vmc_test.end   = RAMTEST_END;
}

/**************************************************************************/ /**
 * @brief Initialize
 *
 * return void
 *
 * Initialize parameters before running #sl_iec60730_post
 *****************************************************************************/
void oem_iec60730_init(void)
{
  oem_bist_check_flag  = false;
  oem_usart_flag      = false;
  oem_tick_uart_counter = 0x0U;

  sl_iec60730_vmc_init(&oem_vmc_test);
  sl_iec60730_irq_init(&oem_irq_config);
  sl_iec60730_imc_init(&oem_imc_test);
  // Reset clock tick counter
  sl_iec60730_sys_clock_count_reset();
}

/**************************************************************************/ /**
 * @brief Increase IRQ counter
 *
 * return void
 *
 * Increase #oem_irq_exec_count
 *****************************************************************************/
void oem_irq_exec_count_tick(void)
{
  oem_irq_exec_count[0]++;
}
