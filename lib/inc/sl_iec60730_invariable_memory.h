/***************************************************************************/ /**
 * @file
 * @brief Invariable memory check
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

#ifndef IEC60730_INVARIABLE_MEMORY_H_
#define IEC60730_INVARIABLE_MEMORY_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "sl_iec60730.h"
#include IEC_BOARD_HEADER

/**************************************************************************/ /**
 * @addtogroup efr32_iec60730
 * @{
 * @addtogroup IEC60730_INVARIABLE_MEMORY_Test
 * @{
 * @details
 * @section imc_hardware_architecture Hardware Architecture
 *
 * In the current version, the calculation of CRC for Flash is calculated
 * starting from the starting address of the Flash (that value can be changed)
 * to the end address whose value is specified by the address of the
 * #__checksum variable. Currently, the #__checksum variable is set to the end
 * address of user code that uses IEC Library.
 *
 * To test the Flash memory, a Cyclic Redundancy Check (CRC) is computed and
 * compared with a value stored in Flash. Any change in the Flash will cause
 * the CRC not to match the stored value.
 *
 * We support multiple calculation modes. These modes are selected by the user.
 * User adds definitions to use these modes. Please reference to definitions
 * #SL_IEC60730_CRC_DEBUG_ENABLE, #SL_IEC60730_CRC_USE_SW, and #SL_IEC60730_USE_CRC_32 for more detail.
 *
 * @section imc_failure_risks Failure Risks
 * As electrically eraseable memories, the primary risk with Flash is losing
 * charge. Normal memory concerns such as stuck-at, coupling, and address
 * faults may also occur. All these faults will be detected by a CRC across
 * the region. Another risk is the hardware CRC module operating
 * incorrectly. In this case, the CRC comparison will fail and
 * #sl_iec60730_safe_state() will begin.
 *
 * @section imc_software_architecture Software Architecture
 * The Invariable Memory Check (IMC) validates that the Flash memory storing the
 * firmware and any persistent configuration information has not been
 * corrupted. The IMC calculates a CRC across designated areas to verify
 * their contents.
 *
 * We support calculation CRC by using hardware and software. The default CRC is
 * hardware calculation. User CAN use the #SL_IEC60730_CRC_USE_SW definition in case using
 * CRC software.
 *
 * With case CRC software is chosen, the default is calculate CRC-table in
 * initialization process. User CAN use the #SL_IEC60730_SW_CRC_TABLE definition in case
 * using pre-defined table.
 *
 * We support both CRC-16 and CRC-32 mode. With CRC-16, the CRC engine is
 * configured to use the CRC-16/XMODEM polynominal 0x1021. With CRC-32, the CRC
 * engine is configured to use the CRC-32 polynominal 0x04C11DB7. The default is
 * CRC-16 mode. In case using CRC-32, user SHOULD define the #SL_IEC60730_USE_CRC_32
 * definition.
 *
 * We also provide scripts named gcc_crc16.sh (for CRC-16 mode) and gcc_crc32.sh
 * (for CRC-32 mode) which is used in Post Build process to calculate CRC value
 * of the Flash and place this CRC value at the end of user code determined by
 * address of #__checksum variable. We WILL call these scripts with the common
 * name \ref gcc_crcXY. Don't worry about the gcc prefix, these scripts
 * work for both GCC and IAR compiler. To use these scripts, user SHOULD install
 * srecord that can be downloaded (.exe) file for Window OS or run command as
 * below for Linux OS.
 *
 * ```
 * $sudo apt install srecord
 * ```
 * \anchor gcc_crcXY
 * Script @ref gcc_crcXY requires the following parameters
 * \param #$1: Name of your project.
 * \param #$2: Directory of building. This directory MUST contain *.hex file and
 * *.map file. The *.map file MUST contains #__checksum variable.
 * \param #$3: Path of srecord. With Linux OS, it SHOULD be blank. With Win OS,
 * it SHOULD be the path to install folder of srecord. For example:
 * 'C:\srecord-1.64-win32' in Win OS.
 * \param #$4: Compiler: GCC or IAR.
 * \param #$5: Start address of Flash.
 * \param #$6: True for non-secure. False otherwise.
 *
 * The struct #sl_iec60730_imc_params_t is used to manage hardware configuration of CRC.
 * In case using CRC software (define #SL_IEC60730_CRC_USE_SW), you can pass NULL pointer
 * to function use this struct.
 *
 * We use a pair of variables to check intergrity. Using the following macros
 * in case you want to work with pair of variables need to be checked intergrity.
 * These macros are defined in sl_iec60730.h file.
 *
 *   * #DEC_CLASSB_VARS is used to declare a pair of variables.
 *   * #EXTERN_DEC_CLASSB_VARS is used to mark pair of variable to be extern.
 *   * #STATIC_DEC_CLASSB_VARS is used to declare a static pair of variables.
 *   * #INV_CLASSB_VAR is used to inverse value of a variable.
 *   * #INV_CLASSB_PVAR is used to inverse value of a pointer.
 *
 * Some detail about implementing of IMC and using variables for testing purpose.
 * These ariables are also used in the test cases (TC) of the IMC module.
 *
 * \anchor iec60730_ref_crc
 *    * Variable \ref iec60730_ref_crc is variable that is stored on (*.classb_ram*) section.
 * In case user use definition #SL_IEC60730_CRC_DEBUG_ENABLE for debug purpose, \ref iec60730_ref_crc
 * variable is useful for debug purpose. Value of \ref iec60730_ref_crc is calculated in
 * #sl_iec60730_imc_post function. This value SHOULD be equal value that stored in
 * address of #__checksum.
 *
 * \anchor iec60730_cur_crc
 *   * Variable \ref iec60730_cur_crc is variable that stores on (*.classb_ram*) section.
 * This variable is CRC calculated value after each function call
 * #sl_iec60730_imc_bist. That means this value will be accumulated for each step
 * of BIST. After checking all Flash, the final value of \ref iec60730_cur_crc under
 * normal conditions, no exception SHOULD be equal to the value stored in Flash.
 *
 * \anchor iec60730_run_crc
 *   * Variable \ref iec60730_run_crc is variable that stores on (*.classb_ram*) section.
 * This is pointer that point to start address of testing process. In case
 * \ref iec60730_run_crc is less than #SL_IEC60730_ROM_END, every time function #sl_iec60730_imc_bist is
 * invoked, the value of \ref iec60730_run_crc increases by #SL_IEC60730_FLASH_BLOCK_WORDS. Otherwise,
 * calculating \ref iec60730_cur_crc and compare it with value of \ref iec60730_ref_crc or value
 * stored in #SL_IEC60730_REF_CRC.
 *
 * To provide complete definitions of IMC modules, in #IEC_BOARD_HEADER file,
 * user SHOULD pay attention to the #SL_IEC60730_ROM_START definition. The #STEPS_NUMBER,
 * #SL_IEC60730_ROM_SIZE_INWORDS, and #SL_IEC60730_FLASH_BLOCK_WORDS definitions SHOULD use our default
 * definitions. The #SL_IEC60730_FLASH_BLOCK, #SL_IEC60730_ROM_END, and #SL_IEC60730_REF_CRC definitions can be
 * redefined by the user but SHOULD not be recommended unless the user has
 * knowledge of linker and Flash configuration.
 *
 * Figure 1 describes a Flash with multiple applications on that. These
 * applications are named Application 1, Application 2, ..., Application N, and
 * Application (N+1). Where Application N is a main application that uses the
 * IEC library.
 *
 * \anchor invariable_memory_check_example_flowchart
 * \image html invariable_memory_check_example_flowchart.png "Figure 1 Example of calculating CRC"
 *
 * The #SL_IEC60730_ROM_START definition can be placed anywhere that guarantees the
 * description of #SL_IEC60730_ROM_START. As you can see in Figure 1, it is possible that
 * #SL_IEC60730_ROM_START is either #SL_IEC60730_ROM_START (1) or #SL_IEC60730_ROM_START (N).
 *
 * The #SL_IEC60730_ROM_END definition as described at the address of the variable
 * #__checksum. As the linker files is used in our example will be at
 * address the end of Application (N). The CRC calculation will go from address
 * #SL_IEC60730_ROM_START to #SL_IEC60730_ROM_END.
 *
 * With #SL_IEC60730_ROM_START (1) we calculate CRC (1) and with #SL_IEC60730_ROM_START (N) we calculate
 * CRC (N). The CRC value is calculated and placed at the location of the
 * variable #__checksum. Calculating and placing are implemented by script
 * \ref gcc_crcXY.
 *
 * In this example you see that Application (N + 1) is an application that does
 * not use the IEC library. Our reference solutions DO NOT support customizing
 * #__checksum anywhere in Flash. Therefore, the CRC calculation WILL not
 * cover the Flash area of Application (N + 1).
 *
 * In case the user edits their linker to let the #__checksum variable go
 * to any location (of course larger than #SL_IEC60730_ROM_START), the IMC modules WILL
 * still work normally. For example, the user adjust the address of
 * #__checksum to the end address of Flash of Application (N + 1), then the
 * CRC calculation WILL completely cover Application (N + 1).
 *
 * Function #sl_iec60730_imc_post() checks for all the invariable memory areas have
 * been configured.
 *
 * On BIST, partial memory sections are tested to keep overall BIST test
 * time reasonable. Global variables store the current location being tested
 * and other information. Each call to #sl_iec60730_imc_bist() it checks
 * #SL_IEC60730_INVAR_BLOCKS_PER_BIST. If after the calculation, the CRC does not match the
 * expected value #IEC60730_TEST_FAILED is returned. If it does match, the
 * global variables are configured for the next CRC entry. If all areas are
 * complete, #IEC60730_TEST_PASSED is returned. If all areas are not complete,
 * #IEC60730_TEST_IN_PROGRESS is returned.
 *
 * \anchor invariable_memory_check_post_flowchart
 * \image html invariable_memory_check_post_flowchart.png "Figure 2 Flow chart of Invariable Memory Check BIST&POST"
 *
 *****************************************************************************/

#ifdef DOXYGEN

/// The library support both hardware and software CRC. Use this definition in
/// case the user use software CRC. The default hardware is used.
#define SL_IEC60730_CRC_USE_SW

/// If using #SL_IEC60730_CRC_USE_SW definition then the #SL_IEC60730_SW_CRC_TABLE definition is used for
/// using pre-defined table for calculating.
#define SL_IEC60730_SW_CRC_TABLE

/// Use this definition in case the user use CRC-32 for calculating the CRC value.
/// The default CRC-16 is used.
#define SL_IEC60730_USE_CRC_32

/// This macro is the initial value used for CRC calculations.
///   * If the #SL_IEC60730_USE_CRC_32 definition is used then #SL_IEC60730_IMC_INIT_VALUE definition
/// SHOULD be 0xFFFFFFFFuL.
///   * Otherwise, the definition SHOULD be 0x0000
#define SL_IEC60730_IMC_INIT_VALUE

/// This macro is the value that will XOR with calculated CRC value to get CRC
/// output value.
///   * If the #SL_IEC60730_USE_CRC_32 definition is used then #SL_IEC60730_IMC_INIT_VALUE definition
/// SHOULD be 0xFFFFFFFFuL.
///   * Otherwise, the definition SHOULD be 0x0000
#define SL_IEC60730_IMC_XOROUTPUT

/// This macro is the default value of struct #CRC_INIT_TypeDef. In our library,
/// The #CRC_INIT_TypeDef struct WILL be #GPCRC_Init_TypeDef struct, a struct
/// is defined for CRC by Silicon Labs.
#define SL_IEC60730_IMC_INIT_DEFAULT

#else

#ifdef SL_IEC60730_USE_CRC_32
#define SL_IEC60730_IMC_INIT_VALUE (0xFFFFFFFFuL)
#define SL_IEC60730_IMC_XOROUTPUT  (0xFFFFFFFFuL)
#define SL_IEC60730_IMC_INIT_DEFAULT                                                       \
  {                                                                            \
      0x04C11DB7UL,   /* CRC32 Polynomial value. */                            \
      SL_IEC60730_IMC_INIT_VALUE, /* Initialization value. */                              \
      false,          /* Byte order is normal. */                              \
      false,          /* Bit order is not reversed on output. */               \
      false,          /* Disable byte mode. */                                 \
      false,          /* Disable automatic initialization on data read. */     \
      true,           /* Enable GPCRC. */                                      \
  }
#else /* !SL_IEC60730_USE_CRC_32 */
#define SL_IEC60730_IMC_INIT_VALUE (0x0000)
#define SL_IEC60730_IMC_XOROUTPUT  (0x0000)
#define SL_IEC60730_IMC_INIT_DEFAULT                                                       \
  {                                                                            \
      0x1021UL,                                                                \
      SL_IEC60730_IMC_INIT_VALUE,                                                          \
      false,                                                                   \
      true,                                                                    \
      false,                                                                   \
      false,                                                                   \
      true,                                                                    \
  }
#endif /* SL_IEC60730_USE_CRC_32 */
#endif // DOXYGEN

/**************************************************************************/ /**
 * public IEC60730 Invariable Memory Check POST
 *
 * @returns #sl_iec60730_test_result_t.
 *          * If test fails, returns #IEC60730_TEST_FAILED;
 *          * Otherwise, return #IEC60730_TEST_PASSED.
 *
 * Performs a CRC check across all defined memory areas.
 *****************************************************************************/
sl_iec60730_test_result_t sl_iec60730_imc_post(void);

/**************************************************************************/ /**
 * public IEC60730 Invariable Memory Check BIST
 *
 * @returns #sl_iec60730_test_result_t.
 *          * If test fails, return #IEC60730_TEST_FAILED;
 *          * Else if not complete, return #IEC60730_TEST_IN_PROGRESS
 *          * Otherwise, return #IEC60730_TEST_PASSED.
 *
 * Performs a CRC check across all defined memory areas. For details
 * how #sl_iec60730_imc_bist work, please refer to @ref imc_software_architecture
 *
 * Requires #sl_iec60730_imc_init to be called first to setup global variables.
 *****************************************************************************/
sl_iec60730_test_result_t sl_iec60730_imc_bist(void);

/** @} (end addtogroup IEC60730_INVARIABLE_MEMORY_Test) */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* IEC60730_INVARIABLE_MEMORY_H_ */
