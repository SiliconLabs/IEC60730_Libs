/***************************************************************************/ /**
 * @file
 * @brief Watchdog check
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

#ifndef __IEC60730_WATCHDOG_H__
#define __IEC60730_WATCHDOG_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**************************************************************************/ /**
 * @addtogroup efr32_iec60730
 * @{
 * @addtogroup IEC60730_WDOG_Test
 * @{
 * @details
 * For IEC 60730, a watchdog timer must be enabled to validate proper
 * operation of the Program Counter. A watchdog timer resets the device if it
 * has not been restarted.
 * @section watchdog_hardware_architecture Hardware Architecture
 * The second implementation has a dedicated watchdog peripheral WDOG0, WDOG1
 * watchdog timers in the EFR32 family.
 *
 *
 * @warning  - The watchdog timer must be disabled during flash page erase.
 *
 * @section watchdog_failure_risks Failure Risks
 * The watchdog timer will force entry into Safe State if the firmware program
 * execution does not return to the BIST quick enough.  This will detect a
 * failure that causes the CPU to halt or enter an infinite loop.
 * The watchdog timer POST verifies that a watchdog timer reset is possible.
 *
 * OEMs must ensure that their system works reliably in all modes of operation
 * using the watchdog timeout. Insufficient testing may allow for firmware
 * states that inadvertently trigger a watchdog reset.
 *
 * @section watchdog_software_architecture Software Architecture
 *
 * For the EFR32 IEC60730 implementation, \link watchdog_flowchart Figure 1\endlink
 * shows the logic flow chart of the Watchdog Timer during POST. The POST test
 * determines if the reset source was a power-on, and if so, validates that a
 * watchdog reset can occur.  If the reset source was a watchdog reset, it
 * determines if the watchdog reset was expected as part of POST testing, or
 * unexpected. An unexpected reset causes immediate iec60730_SafeState() entry.
 * Otherwise normal operation continues.
 *
 * \image html Watchdog_flowchart.png "Figure 1 Flow chart of Watchdog Timer POST validation" \anchor watchdog_flowchart
 *
 * The main loop must execute iec60730_Bist() faster than the nominal
 * timeout, or call iec60730_RestartWatchdogs(). After iec60730_Bist() has
 * confirmed all modules are operating correctly it restarts the Watchdog Timer
 * with iec60730_RestartWatchdogs(). If a module is not operating correctly,
 * iec60730_Bist() calls iec60730_SafeState(). iec60730_SafeState() will call
 * iec60730_RestartWatchdogs() continuously. The system must be powered down and
 * restarted to resume normal operation.
 *
 * The function iec60730_WatchdogPost will set the timeout period (PERSEL) to minimum
 * when check watchdog units to avoid wasting time.
 *
 * @section watchdog_configuration Software Configuration
 *
 * The number of Watchdog units which are tested by lib should be defined by user code
 * by defining the macros "IEC60730_WDOGINST_NUMB" and IEC60730_ENABLE_WDOGx (x = 0, 1).
 * The number of Watchdog unit depends on target EFR32 series.
 * Example for series 1:
 * #define IEC60730_WDOGINST_NUMB  1
 * #define IEC60730_ENABLE_WDOG0
 *
 * User can define macro IEC60730_WDOG_INST(n) to select appropriate Watchdog peripheral.
 * User can define macro IEC60730_RST to select appropriate Reset peripheral.
 *
 * If these macros are not defined then the default configuration will be used.
 *
 * To clear reset cause flags in the RSTCASUES register after watchdog testing
 * completed -> Add the definition of macro "#define IEC60730_RSTCAUSES_CLEAR_ENABLE"
 * to user code. By default this feature is disabled.
 *
 * If the Watchdog module is build in non-secure mode then the macro "IEC60730_NON_SECURE_EN"
 * must be defined to enable the lib using non-secure address of the Watchdog peripheral.
 *
 * @warning - The static variable iec60730_WatchdogCount must be located at memory
 * location that is not cleared when system startup (section ".ram_no_clear").
 * - The global variable iec60730_WatchdogState must be located at memory
 * location that is not cleared when system startup. And it should be located at
 * retention RAM block that is available on EFR32 Series 1 devices (section ".ram_ret_no_clear").
 * This will avoid the missing contain of the variable when device returns from
 * the power saving mode EM4.
 *
 * There's no retention RAM on EFR32 Series 2 devices but they have backup RAM (BURAM)
 * that could be used to save value of the variable.
 * To enable saving iec60730_WatchdogState to backup RAM on Series 2, add the macro
 * "#define IEC60730_SAVE_STAGE_ENABLE" to user code. By default it will be disabled.
 * Define macro "IEC60730_BURAM_IDX" to select which register of the BURAM will be used.
 * The default value is 0x0.
*****************************************************************************/
/// Watchdog component configuration structure
typedef struct {
  WDOG_TypeDef *const wdog; ///< Pointer to Watchdog instance
  const uint32_t rst;       ///< Watchdog reset cause value
} iec60730_WatchDog_t;

/// State of watchdog testing
typedef enum {
  iec60730_WatchdogInvalid = 0, ///< Watchdog POST test not done
  iec60730_WatchdogTesting = 1, ///< Watchdog POST testing in progress
  iec60730_WatchdogValid   = 2, ///< Watchdog POST test complete, watchdog valid
} iec60730_TestWatchdog_t;

// Default configuration if IEC60730_WDOGINST_NUMB is not defined
#ifndef IEC60730_WDOGINST_NUMB
#if (_SILICON_LABS_32B_SERIES < 2) // Series 1
#define IEC60730_WDOGINST_NUMB 1
#define IEC60730_ENABLE_WDOG0
#else // Series 2
#define IEC60730_WDOGINST_NUMB 2
#define IEC60730_ENABLE_WDOG0
#define IEC60730_ENABLE_WDOG1
#endif
#endif

#if (IEC60730_WDOGINST_NUMB == 0)
#error "Number of Watchdog cannot be zero!"
#endif

#ifndef IEC60730_WDOG_WAIT_TIMEOUT
#define IEC60730_WDOG_WAIT_TIMEOUT (uint32_t) 0x0000FFFFUL
#endif

#define WDG_INST_DEF()                                                         \
  const iec60730_WatchDog_t iec60730_WdogInst_arr[IEC60730_WDOGINST_NUMB] = {  \
      IEC60730_WDOG_CFGSET}
#define IEC60730_WDOG(numb) iec60730_WdogInst_arr[numb].wdog

#ifndef IEC60730_WDOG_INST
#ifdef IEC60730_NON_SECURE_EN
#define IEC60730_WDOG_INST(n) WDOG##n##_NS
#else
#define IEC60730_WDOG_INST(n) WDOG##n
#endif
#endif

#if (_SILICON_LABS_32B_SERIES < 2)
#ifndef IEC60730_RST
#define IEC60730_RST RMU
#endif
#define IEC60730_RSTCAUSE_POR   RMU_RSTCAUSE_PORST
#define IEC60730_RSTCAUSE_EM4   RMU_RSTCAUSE_EM4RST
#define IEC60730_RSTCAUSE_WDOG0 RMU_RSTCAUSE_WDOGRST
#define IEC60730_RSTCAUSE_WDOG1 RMU_RSTCAUSE_WDOGRST
#define IEC60730_RSTCAUSES_CLEAR()                                             \
  do {                                                                         \
    IEC60730_RST->CMD |= RMU_CMD_RCCLR;                                        \
  } while (0)
#else // Series 2 devices
#ifndef IEC60730_RST
#ifdef IEC60730_NON_SECURE_EN
#define IEC60730_RST EMU_NS
#else
#define IEC60730_RST EMU
#endif
#endif

#define IEC60730_RSTCAUSE_POR   EMU_RSTCAUSE_POR
#define IEC60730_RSTCAUSE_EM4   EMU_RSTCAUSE_EM4
#define IEC60730_RSTCAUSE_WDOG0 EMU_RSTCAUSE_WDOG0
#define IEC60730_RSTCAUSE_WDOG1 EMU_RSTCAUSE_WDOG1
#ifdef WDOG_HAS_SET_CLEAR
#define IEC60730_RSTCAUSES_CLEAR()                                             \
  do {                                                                         \
    IEC60730_RST->CMD_SET = EMU_CMD_RSTCAUSECLR;                               \
  } while (0)
#else
#define IEC60730_RSTCAUSES_CLEAR()                                             \
  do {                                                                         \
    IEC60730_RST->CMD |= EMU_CMD_RSTCAUSECLR;                                  \
  } while (0)
#endif
#endif // (_SILICON_LABS_32B_SERIES < 2)

#define IEC60730_RSTCAUSE (IEC60730_RST->RSTCAUSE)
#define IEC60730_RST_POR  (IEC60730_RSTCAUSE & IEC60730_RSTCAUSE_POR)
#define IEC60730_RST_EM4  (IEC60730_RSTCAUSE & IEC60730_RSTCAUSE_EM4)
#ifdef IEC60730_ENABLE_WDOG0
#define IEC60730_RST_WDOG0 (IEC60730_RSTCAUSE & IEC60730_RSTCAUSE_WDOG0)
#else
#define IEC60730_RST_WDOG0 0
#endif
#ifdef IEC60730_ENABLE_WDOG1
#define IEC60730_RST_WDOG1 (IEC60730_RSTCAUSE & IEC60730_RSTCAUSE_WDOG1)
#else
#define IEC60730_RST_WDOG1 0
#endif
#define IEC60730_RST_WDOGS (IEC60730_RST_WDOG0 || IEC60730_RST_WDOG1)

#define IEC60730_RST_WDOG(numb)                                                \
  (IEC60730_RSTCAUSE & iec60730_WdogInst_arr[numb].rst)
#define IEC60730_RST_WDOG_CHECK(numb)                                          \
  (IEC60730_RSTCAUSE & iec60730_WdogInst_arr[numb].rst)                        \
      == iec60730_WdogInst_arr[numb].rst

#define IEC60730_WDOG_CONFIG(n)                                                \
  {.wdog = IEC60730_WDOG_INST(n), .rst = IEC60730_RSTCAUSE_WDOG##n},
#ifdef IEC60730_ENABLE_WDOG0
#define IEC60730_CFG_WDOG0 IEC60730_WDOG_CONFIG(0)
#else
#define IEC60730_CFG_WDOG0
#endif
#ifdef IEC60730_ENABLE_WDOG1
#define IEC60730_CFG_WDOG1 IEC60730_WDOG_CONFIG(1)
#else
#define IEC60730_CFG_WDOG1
#endif

#define IEC60730_WDOG_CFGSET                                                   \
  IEC60730_CFG_WDOG0                                                           \
  IEC60730_CFG_WDOG1

#if defined(_SILICON_LABS_32B_SERIES_2_CONFIG_4)                               \
    || defined(_SILICON_LABS_32B_SERIES_2_CONFIG_3)
#define IEC60730_WDOG_EN_WAIT_DISABLING(numb)                                  \
  while ((iec60730_WdogInst_arr[numb].wdog->EN & WDOG_EN_DISABLING) != 0U) {}
#else
#define IEC60730_WDOG_EN_WAIT_DISABLING(numb)
#endif

// Min value for PERSEL is zero
#if (_SILICON_LABS_32B_SERIES < 2)
#define IEC60730_SETWATCHDOGTIMEOUTMIN(numb)                                   \
  do {                                                                         \
    while ((iec60730_WdogInst_arr[numb].wdog->SYNCBUSY & WDOG_SYNCBUSY_CTRL)   \
           != 0U) {}                                                           \
    iec60730_WdogInst_arr[numb].wdog->CTRL &=                                  \
        ~(uint32_t) _WDOG_CTRL_PERSEL_MASK;                                    \
  } while (0)
#else // Series 2 devices
#ifdef WDOG_HAS_SET_CLEAR
#define IEC60730_SETWATCHDOGTIMEOUTMIN(numb)                                   \
  do {                                                                         \
    iec60730_WdogInst_arr[numb].wdog->EN_CLR = WDOG_EN_EN;                     \
    IEC60730_WDOG_EN_WAIT_DISABLING(numb)                                      \
    iec60730_WdogInst_arr[numb].wdog->CFG_CLR = _WDOG_CFG_PERSEL_MASK;         \
    iec60730_WdogInst_arr[numb].wdog->EN_SET  = WDOG_EN_EN;                    \
  } while (0)
#else
#define IEC60730_SETWATCHDOGTIMEOUTMIN(numb)                                   \
  do {                                                                         \
    iec60730_WdogInst_arr[numb].wdog->EN &= ~_WDOG_EN_MASK;                    \
    IEC60730_WDOG_EN_WAIT_DISABLING(numb)                                      \
    iec60730_WdogInst_arr[numb].wdog->CFG &=                                   \
        ~(uint32_t) _WDOG_CFG_PERSEL_MASK;                                     \
    iec60730_WdogInst_arr[numb].wdog->EN |= WDOG_EN_EN;                        \
  } while (0)
#endif
#endif

#ifndef IEC60730_BURAM
#ifdef IEC60730_NON_SECURE_EN
#define IEC60730_BURAM BURAM_NS
#else
#define IEC60730_BURAM BURAM
#endif
#endif
#ifndef IEC60730_BURAM_IDX
#define IEC60730_BURAM_IDX 0UL
#endif
#define IEC60730_BURAM_STATE_SHIFT 8UL
#define IEC60730_BURAM_MASK        0xFFUL

/// Global variable used to track watchdog testing state.
///
/// @warning Must be placed in a memory area not cleared to 0x0 on start!
extern volatile SI_SEGMENT_VARIABLE(iec60730_WatchdogState,
                                    iec60730_TestWatchdog_t,
                                    SI_SEG_DATA_RETAINED_NO_CLEAR);

/**************************************************************************/ /**
 * public IEC60730 Watchdog Power On Self Test
 *
 * @returns #sl_iec60730_test_result_t If a non-watchdog reset occurred,
 * test watchdog (will not return).
 * Otherwise determine if watchdog reset was planned or unplanned.
 * Unplanned watchdog resets result in failure and entry to Safe State.
 * Planned watchdog resets return #IEC60730_TEST_PASSED.
 *
 * This function will test the watchdog timer by forcing a watchdog reset
 * on the first power-up. Any subsequent watchdog reset forces entry into
 * #iec60730_SafeState().
 *
 * @warning Remove all accesses to Watchdog Timer hardware from InitDevice.
 * Reset state of pins must be safe for the device. During POST test, device pins
 * will be kept in reset state while validating watchdog reset.
 *****************************************************************************/
sl_iec60730_test_result_t iec60730_WatchdogPost(void);

/** @} (end addtogroup IEC60730_WDOG_Test) */
/** @} (end addtogroup efr32_iec60730) */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __IEC60730_WATCHDOG_H__ */
