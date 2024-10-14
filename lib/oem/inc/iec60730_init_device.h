/***************************************************************************/ /**
 * @file iec60730_init_device.h
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

#ifndef INITDEVICE_H_
#define INITDEVICE_H_

#define TEST_WDOG_INST WDOG0

#define WDOG_INIT_TEST                                                         \
  {                                                                            \
      true,            /* Start watchdog when initialization is done. */       \
      false,           /* WDOG is not counting during debug halt. */           \
      false,           /* WDOG is not counting when in EM2. */                 \
      false,           /* WDOG is not counting when in EM3. */                 \
      false,           /* EM4 can be entered. */                               \
      false,           /* Do not lock WDOG configuration. */                   \
      wdogPeriod_256k, /* Set longest possible timeout period. */              \
      wdogWarnDisable, /* Disable warning interrupt. */                        \
      wdogIllegalWindowDisable, /* Disable illegal window interrupt. */        \
      false                     /* Do not disable reset. */                    \
  }

void System_Config(void);

#endif /* INITDEVICE_H_ */
