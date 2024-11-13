/***************************************************************************/ /**
 * @file
 * @brief Internal definitions
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

#ifndef __IEC60730_INTERNAL_H__
#define __IEC60730_INTERNAL_H__

// Standard libraries
#include <stdbool.h>
#include <stdint.h>

// Header files needed for publics
#include "iec60730.h"

// Header files needed for privates
#include "iec60730_watchdog.h"
#include "iec60730_invariable_memory.h"
#include "iec60730_variable_memory.h"
#include "iec60730_cpu_registers.h"
#include "iec60730_system_clock.h"
#include "iec60730_programme_counter.h"
#include "iec60730_irq.h"
#include "iec60730_oem.h"

// These macros should be defined in iec60730_oem.h by OEM, otherwise default definition will be used.
#if (!defined(IEC60370_ENTER_ATOMIC) || !defined(IEC60370_EXIT_ATOMIC))
#define IEC60370_ENTER_ATOMIC() __disable_irq()
#define IEC60370_EXIT_ATOMIC()  __enable_irq()
#define IEC60370_DECLARE_IRQ_STATE
#endif

// Disable warnings on unused labels.  Labels are used to set breakpoints for
// automated testing.
#if defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wunused-label"
#endif

#endif /* __IEC60730_INTERNAL_H__ */
