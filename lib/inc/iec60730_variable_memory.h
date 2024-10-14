/***************************************************************************/ /**
 * @file
 * @brief Variable memory check
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

#ifndef IEC60730_VARIABLE_MEMORY_H_
#define IEC60730_VARIABLE_MEMORY_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include IEC_BOARD_HEADER

/**************************************************************************/ /**
 * @addtogroup efr32_iec60730
 * @{
 * @addtogroup IEC60730_VARIABLE_MEMORY_Test
 * @{
 * @details
 * @section vmc_hardware_architecture Hardware Architecture
 * Depending on using the definitation, the testing process takes place through
 * different steps and different region RAM memory.
 *
 * @section vmc_failure_risks Failure Risks
 *
 * There are several potential sources of failure in the variable memory hardware
 *   * Stuck bits that do not change (either 0 or 1)
 *   * Coupled bits that change based on a neighbor
 *   * Address lines that couple or disconnect, activating an incorrect location
 *   * Single Event Upset (SEU) that toggle a bit or bits without permanent
 *   damage to the memory hardware
 *
 * The variable memory check can detect the first three types of errors using
 * the March-X algorithm. The VMC is based on a word-oriented March-X algorithm
 * from <http://www.ece.uc.edu/~wjone/Memory.pdf>.
 *
 * SEU failures are not detected in a class B control, and would
 * require class C level of validation to detect - data duplication, error-
 * detecting-and-correcting memory, etc. A failure of this type will be detected
 * once it causes a secondary failure such as missing a watchdog restart or
 * incorrect clock frequency.
 *
 * @section vmc_software_architecture Software Architecture
 *
 * As show in @ref vmc_software_architecture, there are 3 test processes happen.
 * In the case POST testing, the algorithm used is March-C. In the BIST testing,
 * the algorithm used is March-X by default. If user DOES NOT use the #USE_MARCHX
 * definition, the algorithm used is March-C. March-X algorithm is faster than
 * March-C because March-X algorithm is only March-C algorithm that omits some
 * steps (Step 3, 4). The March-C algorithm (van de Goor,1991) is described as
 * below steps
 *
 *   * STEP 1: Write all zeros to array
 *   * STEP 2: Starting at lowest address, read zeros, write ones, increment up array
 *   * STEP 3: Starting at lowest address, read ones, write zeros, increment up array.
 *   * STEP 4: Starting at highest address, read zeros, write ones, decrement down array.
 *   * STEP 5: Starting at highest address, read ones, write zeros, decrement down array.
 *   * STEP 6: Read all zeros from array.
 *
 * Some detail about implementing of Variable Memory Check (VMC) and used
 * variables. These ariables are also used in the test cases (TC) of the
 * VMC module.
 *
 * To make sure the VMC module as well as the IMC module work properly, it is
 * necessary to ensure the location of the ram area for these modules. The
 * sections SHOULD be placed in the correct order: (*.rt_buf*) -> (*.overlap*).
 * DO NOT change this order. Please refer to our example linker for more details.
 *
 * User need declare a variable of struct #vmcParams_t. In the initialization
 * step, We need to assign the start address and end address to this variable for
 * executing the VMC. We will call the starting address #RAMTEST_START and the
 * ending address #RAMTEST_END to make it easier to describe later.
 *
 * \anchor bkBuf
 *   * Variable \ref bkBuf is a buffer used to backup data during testing process
 * and is placed at (*.rt_buf*) section. The size of this variable is defined in
 * #IEC_BOARD_HEADER (i.e #RT_BLOCKSIZE definition). The #RT_BLOCKSIZE definition
 * will be mentioned later.
 *
 * \anchor ramTestOverLap
 *   * Variable \ref ramTestOverLap is a buffer used to ensure that the
 * algorithm runs at #iec60730_VmcBist function is correct. This variable is
 * placed at (*.overlap*) section.
 *
 * \anchor rtCheck
 *   * Variable \ref rtCheck is pointer that point to start address of testing
 * process and is placed at (*.classb_ram*) section. In case \ref rtCheck is
 * less than #RAMTEST_END, every time function #iec60730_VmcBist is invoked and
 * test is done, then the value of \ref rtCheck increases by #BLOCKSIZE. The
 * #BLOCKSIZE definition is defined in #IEC_BOARD_HEADER and will be mentioned
 * later. Otherwise, we test the backup buffer (i.e the bkBuf variable is
 * mentioned above).
 *
 * Before performing the RAM test, we provide a callback function named
 * #Vmc_PreRunMarchXC_Step. After performing the RAM test, we also provide a
 * callback function named #Vmc_PostRunMarchXC_Step, and the user decides what
 * to do after the RAM test is over.
 *
 * As mentioned about #IEC_BOARD_HEADER in @ref IEC60730_INVARIABLE_MEMORY_Test
 * module, the definition #IEC_BOARD_HEADER also has the necessary information
 * for VMC module to run. The #RAMTEST_START and #RAMTEST_END definitions are used to
 * assigned to start, and end member of a variable of type #vmcParams_t. Two
 * definitions are optional because the user can directly assign values to the
 * start and end member of a variable as long as these values satisfy the
 * conditions describled of the #RAMTEST_START, and #RAMTEST_END definitions. The
 * #BACKGROUND, #BLOCKSIZE, #RT_BLOCK_OVERLAP, and #RT_BLOCKSIZE SHOULD use our
 * default definitions.
 *
 * Currently we also support stack test to check for stack overflow using pattern
 * (here is an array with 4 elements) placed at the bottom of the stack. You can
 * refer to the (*.stack_bottom*) section in our linker example. The initialization
 * values of this array are initialized when calling the function
 * #iec60730_VmcInit. Every time when executing #iec60730_VmcBist will check the
 * value of this array and based on the check results will return
 * #IEC60730_TEST_FAILED nor not.
 *
 * \anchor stackTestOverFlow
 *   * Variable \ref stackTestOverFlow is buffer that store values defined by
 * #STACK_OVERFLOW_CONST_GUARD_VALUE_0, #STACK_OVERFLOW_CONST_GUARD_VALUE_1,
 * #STACK_OVERFLOW_CONST_GUARD_VALUE_2, and #STACK_OVERFLOW_CONST_GUARD_VALUE_3.
 *
 * iec60730_VmcPost()
 *
 * \anchor variable_memory_check_post_flowchart
 * \image html variable_memory_check_post_flowchart.png "Figure 1 Flow chart of Variable Memory Check POST"
 *
 * iec60730_VmcBist()
 *
 * \anchor variable_memory_check_bist_flowchart
 * \image html variable_memory_check_bist_flowchart.png "Figure 2 Flow chart of Variable Memory Check BIST"
 *
 * Figure 3 shows two examples of RAM configurations. The figure on the left can
 * be found in our examples. The figure on the right is a possible scenario.
 * We will analyze these cases as below.
 *
 * \anchor variable_memory_check_example_flowchart
 * \image html variable_memory_check_example_flowchart.png "Figure 3 Example of RAM memory configuration"
 *
 *
 * With the figure on the left, as mentioned above (*.rt_buf*) and (*.overlap*)
 * are placed in fixed order, namely <b>Ram Backup</b> and <b>Overlap</b> as
 * shown in the Figure. The #RAMTEST_START can start the next Overlap. This
 * figure also describes the algorithm of testing. The RAM area under test is
 * defined starting from #RAMTEST_START to #RAMTEST_END, and split into multiple
 * BLOCKs. Each block has a size determined by #BLOCKSIZE. In the first test
 * step, the BLOCK (1) and <b>Overlap</b> are tested. The <b>Ram Backup</b> is
 * used to back up the data in the BLOCK being tested, and will restore it after
 * the test in BLOCKs competletey. In the second test step, BLOCK (2) is tested
 * and a part of BLOCK (1) is also tested. There is an area in BLOCK (1), also
 * called overlap, which will be tested twice. This makes the test even more
 * secure. Continue like this until the test reaches BLOCK (N), the last block,
 * then return to test the <b>Ram Backup</b>.
 *
 * The image on the right is slightly different when, the tested area (from
 * #RAMTEST_START to #RAMTEST_END) contains <b>RamBackup</b> and <b>Overlap</b>.
 * In order to ensure the algorithm works properly, in the case like the figure
 * on the right at the starting position (#RAMTEST_START) it is necessary to
 * create an overlap area. As mentioned above this overlap is also tested so user
 * DOES NOT need to worry. Next, the test process is the same as said, will test
 * the BLOCKs (from BLOCK (1) to BLOCK (N)). Here is a point to note when
 * testing to <b>Ram Backup</b>, it will be ignored because this <b>Ram Backup</b>
 * WILL be tested after the test of the last block (BLOCK (N)).
 *
 * In case the tested area has the address of #RAMTEST_START smaller than the
 * address of <b>RamBackup</b>, the test process is similar to the figure on the
 * right.
 *
 *****************************************************************************/

/**************************************************************************/ /**
 * public IEC60730 Variable Memory Check (VMC) POST
 *
 * @param params input parameter of struct #vmcParams_t form
 *
 * @returns #sl_iec60730_test_result_t.
 *          * If test fails, returns #IEC60730_TEST_FAILED
 *          * Otherwise, returns #IEC60730_TEST_PASSED.
 *
 * Performs a variable memory check in defined area. For details how
 * #iec60730_VmcBist work, please refer to @ref vmc_software_architecture
 *
 *****************************************************************************/
sl_iec60730_test_result_t iec60730_VmcPost(vmcParams_t *params);

/**************************************************************************/ /**
 * public IEC60730 Variable Memory Check (VMC) BIST
 *
 * @param params input parameter of struct #vmcParams_t form
 *
 * @returns #sl_iec60730_test_result_t.
 *          * If test fails, return #IEC60730_TEST_FAILED;
 *          * If not complete, returns #IEC60730_TEST_IN_PROGRESS
 *          * Otherwise, returns #IEC60730_TEST_PASSED.
 *
 * Performs a variable memory check in defined area.
 * For details how #iec60730_VmcBist work, please refer to
 * @ref vmc_software_architecture
 *
 * Requires #iec60730_VmcInit to be called first to setup global variables.
 *
 *****************************************************************************/
sl_iec60730_test_result_t iec60730_VmcBist(vmcParams_t *params);

/** @} (end addtogroup IEC60730_VARIABLE_MEMORY_Test) */

/**************************************************************************/ /**
 * @addtogroup IEC60730_VARIABLE_MEMORY_Test
 * @{
 *****************************************************************************/
#ifdef DOXYGEN

/// The #USE_MARCHX definition is used the algorithm used in BIST is March-X.
#define USE_MARCHX

/// The #RAMTEST_START definition describles the start address of the RAM area
/// under test. The RAMTEST_START definition SHOULD be multiple of 4.
#define RAMTEST_START

/// The #RAMTEST_END definition describle the end address of the RAM area under
/// test. The #RAMTEST_END definition can get value as long as (#RAMTEST_END
/// \- #RAMTEST_START + 1) is a multiple of 4. Value 4 to ensure the algorithm
/// runs correctly, it is also the value defined in #BLOCKSIZE definition.
#define RAMTEST_END

/**************************************************************************/ /**
 * @brief This function is called before performing the RAM check. Depending on
 * the RAM region will be checked to give reasonable actions.
 *
 * @param addr The starting address of the ram under test
 * @param size The size of the ram area to be tested. This parameter
 * is #BLOCKSIZE
 *
 * @return bool
 *          * true - allow running RAM test
 *          * false - not allow
 *
 *****************************************************************************/
bool Vmc_PreRunMarchXC_Step(uint32_t *addr, uint32_t size);

/**************************************************************************/ /**
 * @brief After testing the RAM, you can restore the previous work.
 *
 * @param addr The starting address of the ram under test
 * @param size The size of the ram area to be tested. This parameter
 *
 * @return void
 *
 *****************************************************************************/
void Vmc_PostRunMarchXC_Step(uint32_t *addr, uint32_t size);

#endif // DOXYGEN
/** @} (end addtogroup efr32_iec60730) */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* IEC60730_VARIABLE_MEMORY_H_ */
