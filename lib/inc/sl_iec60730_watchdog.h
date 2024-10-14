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
 * unexpected. An unexpected reset causes immediate sl_iec60730_safe_state() entry.
 * Otherwise normal operation continues.
 *
 * \image html Watchdog_flowchart.png "Figure 1 Flow chart of Watchdog Timer POST validation" \anchor watchdog_flowchart
 *
 * The main loop must execute sl_iec60730_bist() faster than the nominal
 * timeout, or call sl_iec60730_restart_watchdogs(). After sl_iec60730_bist() has
 * confirmed all modules are operating correctly it restarts the Watchdog Timer
 * with sl_iec60730_restart_watchdogs(). If a module is not operating correctly,
 * sl_iec60730_bist() calls sl_iec60730_safe_state(). sl_iec60730_safe_state() will call
 * sl_iec60730_restart_watchdogs() continuously. The system must be powered down and
 * restarted to resume normal operation.
 *
 * The function iec60730_watchdog_post will set the timeout period (PERSEL) to minimum
 * when check watchdog units to avoid wasting time.
 *
 * @section watchdog_configuration Software Configuration
 *
 * The number of Watchdog units which are tested by lib should be defined by user code
 * by defining the macros "SL_IEC60730_WDOGINST_NUMB" and IEC60730_ENABLE_WDOGx (x = 0, 1).
 * The number of Watchdog unit depends on target EFR32 series.
 * Example for series 1:
 * #define SL_IEC60730_WDOGINST_NUMB  1
 * #define SL_IEC60730_WDOG0_ENABLE   1
 *
 * User can define macro  SL_IEC60730_WDOG_INST(n) to select appropriate Watchdog peripheral.
 * User can define macro SL_IEC60730_RST to select appropriate Reset peripheral.
 *
 * If these macros are not defined then the default configuration will be used.
 *
 * To clear reset cause flags in the RSTCASUES register after watchdog testing
 * completed -> Enable the definition of macro "#define SL_IEC60730_RSTCAUSES_CLEAR_ENABLE"
 * on file sl_iec60730_config.h. By default this feature is disabled.
 *
 * If the Watchdog module is build in non-secure mode then the macro "SL_IEC60730_NON_SECURE_EN"
 * must be defined to enable the lib using non-secure address of the Watchdog peripheral.
 *
 * @warning - The static variable iec60730_watchdog_count must be located at memory
 * location that is not cleared when system startup (section ".ram_no_clear").
 * - The global variable iec60730_watchdog_state must be located at memory
 * location that is not cleared when system startup. And it should be located at
 * section ram_no_clear in RAM block that is available on EFR32 Series 1 devices (section ".ram_ret_no_clear").
 * This will avoid the missing contain of the variable when device returns from
 * the power saving mode EM4.
 *
 * On EFR32 Series 2 devices, they have backup RAM (BURAM)
 * that could be used to save value of the variable.
 * To enable saving iec60730_watchdog_state to backup RAM on Series 2, enable the macro
 * "#define SL_IEC60730_SAVE_STAGE_ENABLE" on file sl_iec60730_config.h. By default it will be disabled.
 * Define macro "SL_IEC60730_BURAM_IDX" to select which register of the BURAM will be used.
 * The default value is 0x0.
*****************************************************************************/
/// Watchdog component configuration structure
typedef struct {
  WDOG_TypeDef *const wdog; ///< Pointer to Watchdog instance
  const uint32_t rst;       ///< Watchdog reset cause value
} sl_iec60730_watchdog_t;

/// State of watchdog testing
typedef enum {
  IEC60730_WATCHDOG_INVALID = 0, ///< Watchdog POST test not done
  IEC60730_WATCHDOG_TESTING = 1, ///< Watchdog POST testing in progress
  IEC60730_WATCHDOG_VALID = 2, ///< Watchdog POST test complete, watchdog valid
} sl_iec60730_test_watchdog_t;

// Default configuration number of enabled watchdog SL_IEC60730_WDOGINST_NUMB
#if ((SL_IEC60730_WDOG0_ENABLE == 1) && (SL_IEC60730_WDOG1_ENABLE == 1))
#define SL_IEC60730_WDOGINST_NUMB 2
#elif ((SL_IEC60730_WDOG0_ENABLE == 0) && (SL_IEC60730_WDOG1_ENABLE == 0))
#error "No watchdogs have been selected for testing!"
#else
#define SL_IEC60730_WDOGINST_NUMB 1
#endif

#ifndef SL_IEC60730_WDOG_WAIT_TIMEOUT
#define SL_IEC60730_WDOG_WAIT_TIMEOUT (uint32_t) 0x0000FFFFUL
#endif

#ifndef SL_IEC60730_WDOG_INST
#ifdef SL_IEC60730_NON_SECURE_EN
#define SL_IEC60730_WDOG_INST(n) WDOG##n##_NS
#else
#define SL_IEC60730_WDOG_INST(n) WDOG##n
#endif
#endif

#if (_SILICON_LABS_32B_SERIES < 2)
#ifndef SL_IEC60730_RST
#define SL_IEC60730_RST RMU
#endif

#define SL_IEC60730_RSTCAUSE_POR   RMU_RSTCAUSE_PORST
#define SL_IEC60730_RSTCAUSE_EM4   RMU_RSTCAUSE_EM4RST
#define SL_IEC60730_RSTCAUSE_WDOG0 RMU_RSTCAUSE_WDOGRST
#define SL_IEC60730_RSTCAUSE_WDOG1 RMU_RSTCAUSE_WDOGRST

#define SL_IEC60730_RSTCAUSES_CLEAR()                                          \
  do {                                                                         \
    SL_IEC60730_RST->CMD |= RMU_CMD_RCCLR;                                     \
  } while (0)
#else // Series 2 devices
#ifndef SL_IEC60730_RST
#ifdef SL_IEC60730_NON_SECURE_EN
#define SL_IEC60730_RST EMU_NS
#else
#define SL_IEC60730_RST EMU
#endif
#endif

#define SL_IEC60730_RSTCAUSE_POR   EMU_RSTCAUSE_POR
#define SL_IEC60730_RSTCAUSE_EM4   EMU_RSTCAUSE_EM4
#define SL_IEC60730_RSTCAUSE_WDOG0 EMU_RSTCAUSE_WDOG0
#define SL_IEC60730_RSTCAUSE_WDOG1 EMU_RSTCAUSE_WDOG1

#ifdef WDOG_HAS_SET_CLEAR
#define SL_IEC60730_RSTCAUSES_CLEAR()                                          \
  do {                                                                         \
    SL_IEC60730_RST->CMD_SET = EMU_CMD_RSTCAUSECLR;                            \
  } while (0)
#else
#define SL_IEC60730_RSTCAUSES_CLEAR()                                          \
  do {                                                                         \
    SL_IEC60730_RST->CMD |= EMU_CMD_RSTCAUSECLR;                               \
  } while (0)
#endif
#endif // (_SILICON_LABS_32B_SERIES < 2)

#define SL_IEC60730_RSTCAUSE (SL_IEC60730_RST->RSTCAUSE)
#define SL_IEC60730_RST_POR  (SL_IEC60730_RSTCAUSE & SL_IEC60730_RSTCAUSE_POR)
#define SL_IEC60730_RST_EM4  (SL_IEC60730_RSTCAUSE & SL_IEC60730_RSTCAUSE_EM4)

#if (SL_IEC60730_WDOG0_ENABLE == 1)
#define SL_IEC60730_RST_WDOG0                                                  \
  (SL_IEC60730_RSTCAUSE & SL_IEC60730_RSTCAUSE_WDOG0)
#else
#define SL_IEC60730_RST_WDOG0 0
#endif
#if (SL_IEC60730_WDOG1_ENABLE == 1)
#define SL_IEC60730_RST_WDOG1                                                  \
  (SL_IEC60730_RSTCAUSE & SL_IEC60730_RSTCAUSE_WDOG1)
#else
#define SL_IEC60730_RST_WDOG1 0
#endif
#define SL_IEC60730_RST_WDOGS (SL_IEC60730_RST_WDOG0 || SL_IEC60730_RST_WDOG1)

#ifndef SL_IEC60730_BURAM
#ifdef SL_IEC60730_NON_SECURE_EN
#define SL_IEC60730_BURAM BURAM_NS
#else
#define SL_IEC60730_BURAM BURAM
#endif
#endif
#ifndef SL_IEC60730_BURAM_IDX
#define SL_IEC60730_BURAM_IDX 0UL
#endif

/// Global variable used to track watchdog testing state.
///
/// @warning Must be placed in a memory area not cleared to 0x0 on start!
extern volatile sl_iec60730_test_watchdog_t iec60730_watchdog_state
    IEC60730_DATA_NO_CLEAR;

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
 * #sl_iec60730_safe_state().
 *
 * @warning Remove all accesses to Watchdog Timer hardware from InitDevice.
 * Reset state of pins must be safe for the device. During POST test, device pins
 * will be kept in reset state while validating watchdog reset.
 *****************************************************************************/
sl_iec60730_test_result_t sl_iec60730_watchdog_post(void);

/** @} (end addtogroup IEC60730_WDOG_Test) */
/** @} (end addtogroup efr32_iec60730) */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __IEC60730_WATCHDOG_H__ */
