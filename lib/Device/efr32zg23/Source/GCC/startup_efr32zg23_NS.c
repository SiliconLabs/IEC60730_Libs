/***************************************************************************//**
 * @file
 * @brief CMSIS Compatible EFR32ZG23 startup file in C.
 *        Should be used with GCC 'GNU Tools ARM Embedded'.
 *******************************************************************************
 * # License
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is Third Party Software licensed by Silicon Labs from a third party
 * and is governed by the sections of the MSLA applicable to Third Party
 * Software and the additional terms set forth below.
 *
 ******************************************************************************/
/*
 * Copyright (c) 2009-2018 Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdbool.h>
#include "em_device.h"

#ifdef BOOTLOADER_ENABLE
#include "api/btl_interface.h"

#endif

/*----------------------------------------------------------------------------
 * Linker generated Symbols
 *----------------------------------------------------------------------------*/
extern uint32_t __etext;
extern uint32_t __data_start__;
extern uint32_t __data_end__;
extern uint32_t __copy_table_start__;
extern uint32_t __copy_table_end__;
extern uint32_t __zero_table_start__;
extern uint32_t __zero_table_end__;
extern uint32_t __bss_start__;
extern uint32_t __bss_end__;
extern uint32_t __StackTop;

#ifdef BOOTLOADER_ENABLE
extern MainBootloaderTable_t mainStageTable;

extern void SystemInit2(void);

/*----------------------------------------------------------------------------
 * Exception / Interrupt Handler Function Prototype
 *----------------------------------------------------------------------------*/
typedef void (*pFunc)(void);
#endif

/*----------------------------------------------------------------------------
 * External References
 *----------------------------------------------------------------------------*/
#ifndef __START
extern void  _start(void) __attribute__((noreturn));    /* Pre Main (C library entry point) */
#else
extern int  __START(void) __attribute__((noreturn));    /* main entry point */
#endif

#ifndef __NO_SYSTEM_INIT
extern void SystemInit(void);             /* CMSIS System Initialization      */
#endif

/*----------------------------------------------------------------------------
 * Internal References
 *----------------------------------------------------------------------------*/
void Default_Handler_NS(void);                          /* Default empty handler */
void Reset_Handler(void);                            /* Reset Handler */

/*----------------------------------------------------------------------------
 * User Initial Stack & Heap
 *----------------------------------------------------------------------------*/
#ifndef __STACK_SIZE
#define __STACK_SIZE    0x00000400
#endif
static uint8_t stack[__STACK_SIZE] __attribute__ ((aligned(8), used, section(".stack")));

#ifndef __HEAP_SIZE
#define __HEAP_SIZE    0x00000C00
#endif
#if __HEAP_SIZE > 0
static uint8_t heap[__HEAP_SIZE]   __attribute__ ((aligned(8), used, section(".heap")));
#endif

/*----------------------------------------------------------------------------
 * Exception / Interrupt Handler
 *----------------------------------------------------------------------------*/
/* Cortex-M Processor Exceptions */
void NMI_Handler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void HardFault_Handler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void MemManage_Handler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void BusFault_Handler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void UsageFault_Handler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void DebugMon_Handler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void SVC_Handler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void PendSV_Handler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void SysTick_Handler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
/* Provide a dummy value for the sl_app_properties symbol. */
void sl_app_properties(void);     /* Prototype to please MISRA checkers. */
void sl_app_properties(void)         __attribute__ ((weak, alias("Default_Handler_NS")));

/* Part Specific Interrupts */
void SMU_SECURE_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void SMU_PRIVILEGED_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void SMU_NS_PRIVILEGED_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void EMU_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void TIMER0_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void TIMER1_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void TIMER2_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void TIMER3_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void TIMER4_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void USART0_RX_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void USART0_TX_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void EUSART0_RX_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void EUSART0_TX_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void EUSART1_RX_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void EUSART1_TX_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void EUSART2_RX_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void EUSART2_TX_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void ICACHE0_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void BURTC_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void LETIMER0_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void SYSCFG_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void MPAHBRAM_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void LDMA_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void LFXO_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void LFRCO_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void ULFRCO_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void GPIO_ODD_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void GPIO_EVEN_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void I2C0_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void I2C1_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void EMUDG_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void AGC_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void BUFC_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void FRC_PRI_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void FRC_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void MODEM_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void PROTIMER_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void RAC_RSM_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void RAC_SEQ_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void HOSTMAILBOX_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void SYNTH_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void ACMP0_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void ACMP1_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void WDOG0_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void WDOG1_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void HFXO0_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void HFRCO0_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void HFRCOEM23_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void CMU_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void AES_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void IADC_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void MSC_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void DPLL0_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void EMUEFP_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void DCDC_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void VDAC_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void PCNT0_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void SW0_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void SW1_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void SW2_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void SW3_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void KERNEL0_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void KERNEL1_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void M33CTI0_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void M33CTI1_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void FPUEXH_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void SETAMPERHOST_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void SEMBRX_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void SEMBTX_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void LESENSE_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void SYSRTC_APP_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void SYSRTC_SEQ_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void LCD_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void KEYSCAN_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void RFECA0_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));
void RFECA1_IRQHandler(void) __attribute__ ((weak, alias("Default_Handler_NS")));

/*----------------------------------------------------------------------------
 * Exception / Interrupt Vector table
 *----------------------------------------------------------------------------*/
extern const tVectorEntry __Vectors[];
const tVectorEntry        __Vectors[] __attribute__ ((section(".vectors"))) = {
  /* Cortex-M Exception Handlers */
  { .topOfStack = &__StackTop },            /*      Initial Stack Pointer     */
  { Reset_Handler },                        /*      Reset Handler             */
  { NMI_Handler },                          /*      NMI Handler               */
  { HardFault_Handler },                    /*      Hard Fault Handler        */
  { MemManage_Handler },                    /*      MPU Fault Handler         */
  { BusFault_Handler },                     /*      Bus Fault Handler         */
  { UsageFault_Handler },                   /*      Usage Fault Handler       */
  { Default_Handler_NS },                      /*      Reserved                  */
  { Default_Handler_NS },                      /*      Reserved                  */
  { Default_Handler_NS },                      /*      Reserved                  */
#ifdef BOOTLOADER_ENABLE
  { (pFunc) & mainStageTable },
#else
  { Default_Handler_NS },                      /*      Reserved                  */
#endif
  { SVC_Handler },                          /*      SVCall Handler            */
  { DebugMon_Handler },                     /*      Debug Monitor Handler     */
  { sl_app_properties },                    /*      Application properties    */
  { PendSV_Handler },                       /*      PendSV Handler            */
  { SysTick_Handler },                      /*      SysTick Handler           */

  /* External interrupts */
  { SMU_SECURE_IRQHandler },                       /* -16 = SMU_SECURE */
  { SMU_PRIVILEGED_IRQHandler },                   /* -15 = SMU_PRIVILEGED */
  { SMU_NS_PRIVILEGED_IRQHandler },                /* -14 = SMU_NS_PRIVILEGED */
  { EMU_IRQHandler },                              /* -13 = EMU */
  { TIMER0_IRQHandler },                           /* -12 = TIMER0 */
  { TIMER1_IRQHandler },                           /* -11 = TIMER1 */
  { TIMER2_IRQHandler },                           /* -10 = TIMER2 */
  { TIMER3_IRQHandler },                           /* -9 = TIMER3 */
  { TIMER4_IRQHandler },                           /* -8 = TIMER4 */
  { USART0_RX_IRQHandler },                        /* -7 = USART0_RX */
  { USART0_TX_IRQHandler },                        /* -6 = USART0_TX */
  { EUSART0_RX_IRQHandler },                       /* -5 = EUSART0_RX */
  { EUSART0_TX_IRQHandler },                       /* -4 = EUSART0_TX */
  { EUSART1_RX_IRQHandler },                       /* -3 = EUSART1_RX */
  { EUSART1_TX_IRQHandler },                       /* -2 = EUSART1_TX */
  { EUSART2_RX_IRQHandler },                       /* -1 = EUSART2_RX */
  { EUSART2_TX_IRQHandler },                       /* 00 = EUSART2_TX */
  { ICACHE0_IRQHandler },                          /* 01 = ICACHE0 */
  { BURTC_IRQHandler },                            /* 02 = BURTC */
  { LETIMER0_IRQHandler },                         /* 03 = LETIMER0 */
  { SYSCFG_IRQHandler },                           /* 04 = SYSCFG */
  { MPAHBRAM_IRQHandler },                         /* 05 = MPAHBRAM */
  { LDMA_IRQHandler },                             /* 06 = LDMA */
  { LFXO_IRQHandler },                             /* 07 = LFXO */
  { LFRCO_IRQHandler },                            /* 08 = LFRCO */
  { ULFRCO_IRQHandler },                           /* 09 = ULFRCO */
  { GPIO_ODD_IRQHandler },                         /* 10 = GPIO_ODD */
  { GPIO_EVEN_IRQHandler },                        /* 11 = GPIO_EVEN */
  { I2C0_IRQHandler },                             /* 12 = I2C0 */
  { I2C1_IRQHandler },                             /* 13 = I2C1 */
  { EMUDG_IRQHandler },                            /* 14 = EMUDG */
  { AGC_IRQHandler },                              /* 15 = AGC */
  { BUFC_IRQHandler },                             /* 16 = BUFC */
  { FRC_PRI_IRQHandler },                          /* 17 = FRC_PRI */
  { FRC_IRQHandler },                              /* 18 = FRC */
  { MODEM_IRQHandler },                            /* 19 = MODEM */
  { PROTIMER_IRQHandler },                         /* 20 = PROTIMER */
  { RAC_RSM_IRQHandler },                          /* 21 = RAC_RSM */
  { RAC_SEQ_IRQHandler },                          /* 22 = RAC_SEQ */
  { HOSTMAILBOX_IRQHandler },                      /* 23 = HOSTMAILBOX */
  { SYNTH_IRQHandler },                            /* 24 = SYNTH */
  { ACMP0_IRQHandler },                            /* 25 = ACMP0 */
  { ACMP1_IRQHandler },                            /* 26 = ACMP1 */
  { WDOG0_IRQHandler },                            /* 27 = WDOG0 */
  { WDOG1_IRQHandler },                            /* 28 = WDOG1 */
  { HFXO0_IRQHandler },                            /* 29 = HFXO0 */
  { HFRCO0_IRQHandler },                           /* 30 = HFRCO0 */
  { HFRCOEM23_IRQHandler },                        /* 31 = HFRCOEM23 */
  { CMU_IRQHandler },                              /* 32 = CMU */
  { AES_IRQHandler },                              /* 33 = AES */
  { IADC_IRQHandler },                             /* 34 = IADC */
  { MSC_IRQHandler },                              /* 35 = MSC */
  { DPLL0_IRQHandler },                            /* 36 = DPLL0 */
  { EMUEFP_IRQHandler },                           /* 37 = EMUEFP */
  { DCDC_IRQHandler },                             /* 38 = DCDC */
  { VDAC_IRQHandler },                             /* 39 = VDAC */
  { PCNT0_IRQHandler },                            /* 40 = PCNT0 */
  { SW0_IRQHandler },                              /* 41 = SW0 */
  { SW1_IRQHandler },                              /* 42 = SW1 */
  { SW2_IRQHandler },                              /* 43 = SW2 */
  { SW3_IRQHandler },                              /* 44 = SW3 */
  { KERNEL0_IRQHandler },                          /* 45 = KERNEL0 */
  { KERNEL1_IRQHandler },                          /* 46 = KERNEL1 */
  { M33CTI0_IRQHandler },                          /* 47 = M33CTI0 */
  { M33CTI1_IRQHandler },                          /* 48 = M33CTI1 */
  { FPUEXH_IRQHandler },                           /* 49 = FPUEXH */
  { SETAMPERHOST_IRQHandler },                     /* 50 = SETAMPERHOST */
  { SEMBRX_IRQHandler },                           /* 51 = SEMBRX */
  { SEMBTX_IRQHandler },                           /* 52 = SEMBTX */
  { LESENSE_IRQHandler },                          /* 53 = LESENSE */
  { SYSRTC_APP_IRQHandler },                       /* 54 = SYSRTC_APP */
  { SYSRTC_SEQ_IRQHandler },                       /* 55 = SYSRTC_SEQ */
  { LCD_IRQHandler },                              /* 56 = LCD */
  { KEYSCAN_IRQHandler },                          /* 57 = KEYSCAN */
  { RFECA0_IRQHandler },                           /* 58 = RFECA0 */
  { RFECA1_IRQHandler },                           /* 59 = RFECA1 */
};

/*----------------------------------------------------------------------------
 * Reset Handler called on controller reset
 *----------------------------------------------------------------------------*/
void Reset_Handler(void)
{
  uint32_t *pSrc, *pDest;
  uint32_t *pTable __attribute__((unused));

#ifndef __NO_SYSTEM_INIT
  SystemInit();
#endif

#ifdef BOOTLOADER_ENABLE
  SystemInit2();
#endif

/*  Firstly it copies data from read only memory to RAM. There are two schemes
 *  to copy. One can copy more than one sections. Another can only copy
 *  one section.  The former scheme needs more instructions and read-only
 *  data to implement than the latter.
 *  Macro __STARTUP_COPY_MULTIPLE is used to choose between two schemes.  */

#ifdef __STARTUP_COPY_MULTIPLE
/*  Multiple sections scheme.
 *
 *  Between symbol address __copy_table_start__ and __copy_table_end__,
 *  there are array of triplets, each of which specify:
 *    offset 0: LMA of start of a section to copy from
 *    offset 4: VMA of start of a section to copy to
 *    offset 8: size of the section to copy. Must be multiply of 4
 *
 *  All addresses must be aligned to 4 bytes boundary.
 */
  pTable = &__copy_table_start__;

  for (; pTable < &__copy_table_end__; pTable = pTable + 3) {
    pSrc  = (uint32_t *) *(pTable + 0);
    pDest = (uint32_t *) *(pTable + 1);
    for (; pDest < (uint32_t *) (*(pTable + 1) + *(pTable + 2)); ) {
      *pDest++ = *pSrc++;
    }
  }
#else
/*  Single section scheme.
 *
 *  The ranges of copy from/to are specified by following symbols
 *    __etext: LMA of start of the section to copy from. Usually end of text
 *    __data_start__: VMA of start of the section to copy to
 *    __data_end__: VMA of end of the section to copy to
 *
 *  All addresses must be aligned to 4 bytes boundary.
 */
  pSrc  = &__etext;
  pDest = &__data_start__;

  for (; pDest < &__data_end__; ) {
    *pDest++ = *pSrc++;
  }
#endif /*__STARTUP_COPY_MULTIPLE */

/*  This part of work usually is done in C library startup code. Otherwise,
 *  define this macro to enable it in this startup.
 *
 *  There are two schemes too. One can clear multiple BSS sections. Another
 *  can only clear one section. The former is more size expensive than the
 *  latter.
 *
 *  Define macro __STARTUP_CLEAR_BSS_MULTIPLE to choose the former.
 *  Otherwise efine macro __STARTUP_CLEAR_BSS to choose the later.
 */
#ifdef __STARTUP_CLEAR_BSS_MULTIPLE
/*  Multiple sections scheme.
 *
 *  Between symbol address __copy_table_start__ and __copy_table_end__,
 *  there are array of tuples specifying:
 *    offset 0: Start of a BSS section
 *    offset 4: Size of this BSS section. Must be multiply of 4
 */
  pTable = &__zero_table_start__;

  for (; pTable < &__zero_table_end__; pTable = pTable + 2) {
    pDest = (uint32_t *) *(pTable + 0);
    for (; pDest < (uint32_t *) (*(pTable + 0) + *(pTable + 1)); ) {
      *pDest++ = 0UL;
    }
  }
#elif defined (__STARTUP_CLEAR_BSS)
/*  Single BSS section scheme.
 *
 *  The BSS section is specified by following symbols
 *    __bss_start__: start of the BSS section.
 *    __bss_end__: end of the BSS section.
 *
 *  Both addresses must be aligned to 4 bytes boundary.
 */
  pDest = &__bss_start__;

  for (; pDest < &__bss_end__; ) {
    *pDest++ = 0UL;
  }
#endif /* __STARTUP_CLEAR_BSS_MULTIPLE || __STARTUP_CLEAR_BSS */

#ifndef __START
#define __START    _start
#endif
  __START();
}

/*----------------------------------------------------------------------------
 * Default Handler for Exceptions / Interrupts
 *----------------------------------------------------------------------------*/
void Default_Handler_NS(void)
{
  while (true) {
  }
}
