/**************************************************************************//**
 * Copyright (c) 2021 by Silicon Laboratories Inc. All rights reserved.
 *
 * http://developer.silabs.com/legal/version/v11/Silicon_Labs_Software_License_Agreement.txt
 *****************************************************************************/

#ifndef INITDEVICE_H_
#define INITDEVICE_H_

#define TEST_WDOG_INST  WDOG0

#define WDOG_INIT_TEST                                                          \
  {                                                                             \
    true,                     /* Start watchdog when initialization is done. */ \
    false,                    /* WDOG is not counting during debug halt. */     \
    false,                    /* WDOG is not counting when in EM2. */           \
    false,                    /* WDOG is not counting when in EM3. */           \
    false,                    /* EM4 can be entered. */                         \
    false,                    /* Do not lock WDOG configuration. */             \
    wdogPeriod_256k,          /* Set longest possible timeout period. */        \
    wdogWarnDisable,          /* Disable warning interrupt. */                  \
    wdogIllegalWindowDisable, /* Disable illegal window interrupt. */           \
    false                     /* Do not disable reset. */                       \
  }

void System_Config(void);

#endif /* INITDEVICE_H_ */
