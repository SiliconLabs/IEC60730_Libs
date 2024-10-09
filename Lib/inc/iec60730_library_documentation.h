/***************************************************************************//**
 * @file
 * @brief Library Documentation
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

// This file is a centralized location for documentation on OEM functions.
// It contains no source.

/**************************************************************************//**
 * @defgroup efr32_iec60730 EFR32 IEC60730 Library
 * @brief EFR32 IEC60730 Library
 * @{
 * @section introduction Introduction
 * The IEC60730 library for EFR32 provides a basic implementation required to 
 * support the necessary requirements found in Table H.1 in the <a href="https://webstore.iec.ch/publication/23952">IEC60730 
 * specification</a>. It includes all the Power On Self Test (POST) functions 
 * executed when a device is first powered on, as well as Built In Self Test 
 * (BIST) functions that are called periodically to ensure correct operation.
 * Certain portions of the requirements require a detailed understanding of 
 * the system under development.  Callback functions must be completed by 
 * the developer to guarantee meeting the full specification. These include a 
 * Safe State function used when validation detects an anomaly, properly 
 * implemented communications channels (redundancy, error detection, periodic 
 * communcations), and Plausibility functions to validate system state (internal 
 * variables and inputs/outputs).
 *  
 * @section license License
 * @ref iec60730_license_agreement
 * 
 * @section release_notes Release Notes
 * @ref iec60730_release_notes
 * 
 * @section certificate IEC60730 Certificate
 * <a href="http://www.silabs.com/appliances"> The Silicon Labs Appliances</a>
 * homepage will contain the final certificate and detailed report when 
 * it is completed.
 *
 * @section oem_testing OEM Testing
 * 
 * Once OEMs have completed integrating their system with the IEC60730 Library,
 * they will need to certify their device with a qualified certification house.
 *
 * \subsection families_sec Supported Families
 *
 * This library supports all EFR32 devices listed in the 
 * <a href="https://www.silabs.com/wireless">Selector Guide</a>.
 *
 * @section software_requirements Software Requirements
 * The IEC 60730 library dependencies:
 * -# CMSIS package.
 * -# Silicon Labs Devices header files.
 *
 * User could get dependency source files from the GSDK suite (platform) or from <repository>/Lib/Device/<...>/Include.
 * The dependency source files on IEC60730 project repository supports only version GSDK V3.x.
 * To get the latest version of GSDK, please refer
 * <a href="https://github.com/SiliconLabs/gecko_sdk"> Gecko SDK.</a>
 *
 * @warning The IEC 60730 library requires 
 * <a href="https://www.silabs.com/developers/simplicity-studio"> Simplicity Studio 5.</a>
 *
 * Details on the validation test setup used internally by Silicon Labs can 
 * be found at \link IEC60730_VERIFICATION IEC60730 Test Specification\endlink. 
 * Test results can be found inside each module.
 *
 * Currently tested on Windows and Linux platforms.
 *
 * @subsection installation_steps Building the IEC60730 Demo
 *
 * Use the New Project window and select an Example project. Under the
 * IEC60730 folder is the IEC60730 Demo project.
 *
 * See \link OEM_customization OEM Customization \endlink for details on
 * customizing the project and adding custom code.
 * 
 * @warning While source code is provided for the IEC60730 library, 
 * Silicon Labs recommends using the certified library file. 
 * When applying for certification, the certified library file will
 * reduce the certification time.
 * 
 * @note The Simplicity Studio debugger will allow breakpoints and code tracing
 * into the IEC60730 library, except for iec60730_CpuRegistersBist(), since 
 * that test requires special compiler commands. To set breakpoints or 
 * trace inside iec60730_CpuRegistersBist(), set a breakpoint inside 
 * iec60730_Bist() at the line with iec60730_CpuRegistersBist(), and 
 * single-step into the function.
 * 
 * @section compilers Compiler specifications
 * The C compilers:
 * -# GNU GCC V10.3
 * -# IAR EW for ARM V9.2
 *
 * @section tool_chains Tools specification
 * Test frame work tools:
 * -# Python V3.11
 * 
 * Source code control:
 * -# GIT V2.39
 * -# JIRA V8.22.2
 * 
 * @section system_architecture_spec System Architecture
 * 
 * This library has two primary components.  The 
 * \link IEC60730_POST POST component\endlink is run immediately after 
 * power on, validating system state before entering the main 
 * execution loop. 
 * 
 * The \link IEC60730_BIST BIST component\endlink is run periodically in the  
 * main execution loop.
 * 
 * Validation for IEC 60730 also requires external communications validation. 
 * Every OEM application has unique external communications requirements. 
 * This library provides an example UART communications library that meets
 * IEC 60730 requirements. OEMs must adapt their communications 
 * to IEC60730 requirements.
 * 
 * iec60730_oem_functions.c includes functions and variables that OEMs must
 * modify for their system.
 * 
 * This EFR32 IEC60730 library fulfills the requirements for a Class B device.
 * \link iec60730_table1 Table 1\endlink lists the firmware requirements 
 * that must be met by controls. This is taken from Table 1 in IEC 60730, 
 * including new entries from Annex H.
 * 
 * \link iec60730_tableh1 Table 2\endlink lists the firmware-specific 
 * requirements for software based controls taken from Table H.1 in IEC 60730.
 * 
 * <center><b>Table 1 Requirements that must be met by controls </b></center>\anchor iec60730_table1
 * Information | Clause | Method [1] | Notes specific to this library [2]
 * ------------|--------|------------|-----------------------------------
 * 36 Limits of activating quantity | 11.3.2 H.11.4.15 H.17.14 H.18.1.5 H.27.1.1 H.28 | X | Not Applicable
 * 52 Minimum parameters of any heat dissipator | 14 | X | Not Applicable
 * 53 Type of output waveform if other than sinusoidal | H.25 | X | Not Applicable
 * 54 Details of the leakage current waveform produced after failure of the basic insulation | H.27 | X | Not Applicable
 * 55 Relevant parameters of electronic devices unlikely to fail | H.27 | X | Not Applicable
 * 56 Type of output waveform produced after failure of an electronic device | H.27 | X | Not Applicable
 * 57 The effect on controlled outputs after electronic circuit component failure | H.27 | X | To be provided by OEM
 * 58b The effect on controlled outputs after a failure to operate as a result of tests | H.26.2 H.26.15 | X | Not Applicable
 * 66 Software sequence documentation | H.11.12.2.9 | D | Covered by this documentation
 * 67 Program documentation | H.11.12.2.9 H.11.12.2.12 | D | Covered by this documentation
 * 68 Software fault analysis | H.11.12 H.27.1.1.4 | D | Covered by this documentation
 * 69 Software class(es) and structure | H.11.12.2 H.11.12.3 H.27.1.2.2.1 H.27.1.2.3.1 | D | Covered by this documentation
 * 70 Analytical measure and fault/error control techniques employed | H.11.12.1.2 | D | Covered by this documentation
 * 71 Software fault/error detection times for controls | H.2.17.10 | X | Provided by OEM timer ticks. Example uses 1 second.
 * 72 Control responses in case of detected fault/error | H.11.12.2.7 | X | Must be provided by OEM
 * 73 Controls subjected to a second fault analysis and declared condition as a result of the second fault | H.27.1.2.3 | X | Must be provided by OEM
 * 74. External load and emission control measures to be used for test purposes | H.23.1.1 | X | Not Applicable
 * 91 Fault reaction time |H.2.23.2 H.27.1.2.2.2 H.27.1.2.2.3 H.27.1.2.3.2 H.27.1.2.3.3 H.27.1.2.4.2 H.27.1.2.4.3 | X | Provided by OEM timer ticks. Example uses 1 second.
 * 92 Class or classes of control functions | H.6.18 H.27.1.2.2 H.27.1.2.3 | D | This library is for Class B control functions
 * 93 Maximum number of reset actions within a time period | H.11.12.4.3.6 H.11.12.4.3.4 | X | Not Applicable
 * 94 Number of remote reset actions | H.17.1.4.3 | X | Not Applicable
 * 
 * 1. Methods (See IEC60730 documentation for additional details):
 *   - C - Marking
 *   - D - Hard copy
 *   - E - Documentation on electronic media, internal or external
 *   - X - Declaration on materials provided to certification body
 * 2. OEMs are still responsible for providing any documentation for software outside the IEC60730 library.
 * 
 * <center><b>Table 2 Measures to address software fault/errors</b></center> \anchor iec60730_tableh1
 * 
 * Component | Measure Used | Notes
 * ----------|-------------|-----
 * \link IEC60730_CPUREG_Test 1.1 Registers\endlink | Periodic self-test using a Static memory test | Provided by library
 * 1.2 Instruction decoding and execution | None | Not required for Class B
 * \link IEC60730_PROGRAMME_COUNTER 1.3 Program counter\endlink / \link IEC60730_WDOG_Test Watchdog\endlink | Logical monitoring of the program sequence. Code execution sets flag that is periodically checked.  Watchdog timer prevents runaway program execution. | Provided by library, see example for integration sample
 * 1.4 Addressing | None | Not required for Class B
 * 1.5 Data paths Instruction decoding | None | Not required for Class B
 * \link IEC60730_IRQ_Test 2 Interrupt handling and execution\endlink | Time-slot monitoring(upper and lower limit) | Provided by library, see example for integration sample
 * \link IEC60730_SYSTEM_CLOCK_Test 3 Clock\endlink | Reciprocal Comparison. Use separate oscillator to monitor SYSCLK - Calculate ratio and determine range based on accuracy | Provided by library, see example for integration sample
 * \link IEC60730_INVARIABLE_MEMORY_Test 4.1 Invariable memory\endlink | Periodic 16 bit CRC | Provided by library, see example for integration sample
 * \link IEC60730_VARIABLE_MEMORY_Test 4.2 Variable memory\endlink | Periodic static memory test using March-C & stack guard. | Provided by library, see example for integration sample
 * 4.3 Addressing (variable and invariable memory) | | 4.1 and 4.2 provide coverage for this component
 * 5.1 Internal data path | | 4.1 and 4.2 provide coverage for this component
 * 5.2 Internal addressing | | 4.1 and 4.2 provide coverage for this component
 * \link IEC60730_OEM_COMM_Test 6 External Communication \endlink | | Provided by OEM, UART example in library
 * \link IEC60730_OEM_COMM_Test 6.1 External Communications - Data \endlink | 16 bit CRC | CRC check provided by library
 * \link IEC60730_OEM_COMM_Test 6.2 External Communications - Addressing \endlink | 16 bit CRC including the adress | OEM must include in protocol proper address verification - see UART example in library
 * \link IEC60730_OEM_COMM_Test 6.3 External Communications - Timing (UART example)\endlink | Scheduled transmission |  OEM must include in protocol proper timing measures - see UART example in library
 * \link IEC60730_GPIO_PLAUSIBILTY_Test 7 Input/output periphery / 7.1 Digital I/O\endlink | Plausibility check | Provided by OEM
 * \link IEC60730_ADC_PLAUSIBILTY_Test 7.2 Analog I/O / 7.2.1 A/D and D/A convertor\endlink | Plausibility check | Provided by OEM
 * \link IEC60730_ADC_PLAUSIBILTY_Test 7.2.2 Analog multiplexer\endlink| Plausibility check | Provided by OEM
 * 8 Monitoring device and comparators | None | Not needed for class B
 * 9 Custom chips | None | Not Applicable
 * 
 * \section test_specifications Test Specifications
 * \link IEC60730_VERIFICATION Test Specifications\endlink provide detailed
 * specifications for verification testing.
 * 
 * @section coding_standard Coding Standard
 * The IEC60730 library follows @ref iec60730_coding_standard
 * 
 * @section support Support
 * Customers with support questions can begin with the 
 * <a href="https://www.silabs.com/support">Silicon Labs support page. </a>
 * Customers can also post their questions to the Silicon Labs 
 * <a href="https://community.silabs.com/s/?language=en_US">Community Forums</a> 
 * for help from other Silicon Labs customers.
 * 
 * If a customer needs help with a complex issue, create a Support Request on
 * the support page and the Silicon Labs MCU Applications Engineering 
 * team will assist with duplicating the issue, and understanding 
 * the root cause.
 * 
 * @section update Change Control and Update process
 * The IEC60730 library is a complex software project, and will need support 
 * and updates in the future. This section provides details on how Silicon 
 * Labs will help customers with their implementation, and release updates 
 * to the IEC60730 library.
 * 
 * Once an issue is confirmed to be a problem with the IEC60730 Library, 
 * a JIRA ticket must be filed within the Developer Services Team project 
 * (DS) with a title starting with "IEC60730: ". Each issue is 
 * assessed by the IEC60730 team lead and given a severity, with the 
 * options being: 
 *   - Blocker (Customer cannot move forward/is lines-down) 
 *   - Critical (Customer can proceed, but with major inconvenience/no workaround)
 *   - High (Customer can proceed with minor inconvenience/workaround)
 *   - Low (Customer can proceed with no inconvenience, no workaround necessary). 
 * Information about the impact of the change on the library is also added
 * to the ticket, along with an estimated schedule to implement the change.
 * 
 * The issue is assigned to the Developer Services Team manager. At their 
 * discretion, they will call a meeting with the IEC60730 Change Control 
 * Board (DS team lead) to discuss open JIRA tickets against the IEC60730 Library. 
 * At the conclusion of the meeting, each JIRA ticket will be voted on to 
 * fix or no-fix. Each ticket will be updated to reflect its
 * status. Work will be assigned to appropriate Firmware team members. 
 * Work will be placed in a separate branch from Main within the Git 
 * Version Control System.
 * 
 * Once the updated firmware is complete, the developer will check in
 * that firmware into the Silicon Labs Git version control system and
 * create a Code Review JIRA ticket. The review developer will 
 * review the code and ensure it follows the <a href=coding-standard.pdf>Coding Standard</a>.
 * If possible, a Git Pull Request will be created between the two revisions
 * of the source code. Any comments from the review developer will be 
 * added to a Git branch of the IEC60730 project. The Git commit ID will be
 * attached to the Code Review JIRA ticket. The developer will address
 * the comments from the code review, noting any declined changes with 
 * reasons behind the decline.
 * 
 * The IEC60730 library version will be incremented. Any issues fixed will 
 * have an automated test created to duplicate the issue with the previous
 * library, and prove the issue is no longer present in the new library. 
 * The developer must also verify the Python code is operating correctly
 * when the original tests are run.
 * 
 * If an issue cannot be validated using the automated testing 
 * infrastructure, a special waiver must be granted by the Change Control 
 * Board and instructions for manual testing included in documentation for the 
 * affected module. A full automated and manual validation cycle must pass 
 * before the updated library is ready for release. This is done by kicking
 * off a Daily Firmware build job in the Jenkins build & test environment
 * using the Git branch as the source.
 *
 * Once the Daily Firmware build job and any necessary manual tests 
 * verify correct firmware operation, the branch will be merged back into
 * the master branch. A Release Build is kicked off in Jenkins using the 
 * new release version and the master branch.
 * 
 * The MCU FW Team Manager must sign off on the validation results via JIRA.
 * 
 * Once the library completes validation, the updated library with a 
 * change list is submitted to the certification house for re-certification. 
 * After the library completes re-certification, an Errata document listing 
 * all the issues will be created/updated with the new fix/no-fix issues, 
 * and any workarounds.
 *
 * The new library, along with the Errata document and updated Readme file with 
 * the new version number, will be uploaded to the Silicon Labs downloads site
 * and available through Simplicity Studio.
 * 
 * @section OEM_customization OEM Customization and Integration
 * An OEM must be aware of these items when integrating the IEC60730 library 
 * into their final product.
 * 
 * @warning Any certification image must use the Release source files of the IEC60730
 * library.
 * 
 * @subsection Safe_state_integration Safe state
 * OEMs must customize the iec60730_SafeState() function according to their 
 * system configuration . Safe State must configure any external signals and
 * communications channels such that the system will not cause damage or 
 * unexpected operation. The function may attempt external notification, 
 * however it must be done cautiously to prevent further deterioration 
 * of the system.
 * 
 * @subsection POST_integration POST
 * iec60730_Post() is normally called after system initialization is complete,
 * but before beginning primary operating mode. It includes a Watchdog test 
 * that resets the system to verify Watchdog operation. OEMs must expect 
 * initialization code before iec60730_Post() to execute twice. Initialization
 * code execution time must be short enough that the watchdog can be refreshed
 * in iec60730_Post() before expiration.
 * 
 * @subsection BIST_integration BIST
 * iec60730_Bist() is executed as part of the main system loop., typically at
 * the end. Systems with long execution times will require manual watchdog 
 * refresh, and adjustment of iec60730_TestClockTick() frequency to ensure 
 * iec60730_programmeCounterTest() passes, or calling iec60730_Bist() at 
 * multiple locations in the main system loop.
 * 
 * When in safety-critical code where POST and BIST are executing, interrupts 
 * should remain globally enabled.  If interrupts must be disabled for a 
 * critical section of firmware, the critical section should follow best 
 * practices and be as short as possible. The time in the critical section 
 * must be shorter than the fastest clock timer interrupt (usually 10ms), or 
 * #iec60730_timerTestControl must be used to disable the timer tests.
 * 
 * @subsection Programme_counter_integration Program counter
 * #IEC60730_GPIO_COMPLETE and #IEC60730_ANALOG_COMPLETE must be set by OEM 
 * validation code. Usage examples are provided.
 * 
 * OEMs can use #IEC60730_OEM0_COMPLETE - #IEC60730_OEM7_COMPLETE OR'ed into 
 * #iec60730_programmeCounterCheck to verify their own test algorithms are 
 * executing at least once per every call to iec60730_programmeCounterTest(). 
 * Unused flags must be set to 1.
 * 
 * @warning iec60730_Bist() can take several ms to execute, see 
 * \link resources_used Execution Time \endlink for details. If the 
 * execution time is longer than the system can tolerate, customize the 
 * iec60730_Bist() routine or split it up into individual calls in 
 * the main system loop.
 * 
 * @subsection Watchdog_integration Watchdog
 * User should setup the internal watchdog as user's design expectation.
 * 
 * When in a long latency loop, use iec60730_RestartWatchdogs() to prevent a 
 * watchdog reset. Minimize the time in the loop as much as possible. 
 * 
 * @warning Call iec60730_RestartWatchdogs() to re-enable 
 * the watchdog once the flash erase has completed. During the flash erase 
 * time, any control signals must remain in a safe configuration. 
 * \link IEC60730_WDOG_Test Watchdog Test \endlink provides details.
 * 
 * @subsection IRQ_integration IRQ
 * OEMs must update #iec60730_IRQFreqBounds for their system use. Interrupt 
 * service routines must include code for incrementing 
 * #iec60730_IRQExecCount; for an example, see iec60730_oem_timer.c. OEMs 
 * must choose and enumerate the index values for #iec60730_IRQExecCount.
 * 
 * @warning Interrupts are disabled during portions of the 
 * \link IEC60730_INVARIABLE_MEMORY_Test
 * Invariable Memory Test \endlink and \link IEC60730_VARIABLE_MEMORY_Test 
 * Variable Memory Test \endlink. Interrupts must be tolerant of the latency
 * times these tests introduce to servicing an interrupt.
 * 
 * @subsection Clock_integration Clock
 * OEMs can modify the default System Clock and Timer Clock configurations
 * in iec60730_oem_timer.c according to their system requirements.
 * 
 * @subsection Invariable_memory_integration Invariable memory
 * OEMs must modify the #iec60730_Invariable structure to align with their
 * memory usage. #iec60730_Invar_Crc or similar must be modified to store 
 * the CRC values.
 * 
 * During the CRC generation for a block of memory, the CPU is halted and 
 * unable to respond to interrupt requests.
 * 
 * For a typical system, the amount of invariable memory checked will 
 * determine the fault reaction time.
 * 
 * @subsection Variable_memory_integration Variable memory
 * More safety critical variables should be placed in IDATA, since IDATA is 
 * fully validated every call to iec60730_VmcBist(). 
 * 
 * If not all of XDATA is used, #iec60730_XdataNumPartitions can be decreased
 * to cover only the used portions of memory. This will decrease the time to
 * check the used XDATA space.
 * 
 * @subsection external_communications_integration External communications
 * OEMs must write their safety-related communications protocol according to
 * the IEC60730 requirements. The demo provides an example protocol test for
 * UART 0.
 * 
 * @subsection GPIO_integration GPIO
 * iec60730_GpioInit() must be replaced by OEMs with GPIO configuration for
 * their system usage.
 * 
 * iec60730_GpioCheck() must be customized by OEMs to reflect their system
 * usage, and expected/plausible values for their configuration.
 * 
 * OEMs must manually add this check to their main system loop where 
 * appropriate. It is not run as part of iec60730_Bist().
 * 
 * @subsection ADC_integration ADC
 * iec60730_AnalogCheck() must be customized by OEMs to reflect their system
 * usage, and expected/plausible values for their configuration.
 * 
 * OEMs must manually add this check to their main system loop where 
 * appropriate. It is not run as part of iec60730_Bist().
 * 
 * @subsection ADC_mux_integration ADC mux
 * OEMs must manually add this check to their main system loop where 
 * appropriate. It is not run as part of iec60730_Bist(). For more details 
 * see iec60730_AnalogCheck().
 * 
 * @subsection additional_oem_tests Additional OEM safety checks
 * OEMs can implement additional safety checks and call iec60730_SafeState()
 * with custom #iec60730_OEMFail_1 settings.
 * 
 * \subsection resources_used Resources Used
 * The sizes given below are for the sample programs provided with the SDK.
 * 
 * OEM devices that do not use a communications channel(~400 bytes), or 
 * have simple plausilbity functions (~200 bytes), will use less space.
 * 
 * OEMs can use these numbers for planning purposes, but must verify against 
 * their implementation.
 * 
 * <center><b>Table 3 Resources Used</b></center> \anchor resources_used_table
 * EFR32 Device | Code | RAM 
 * -------------|------|-----
 * EFR32xG21    | 5315 | 79
 * EFR32xG23    | 5351 | 79
 * 
 * @subsection bist_frequency BIST call frequency
 * All tests must complete execution before iec60730_programmeCounterTest()
 * is called. The example code calls iec60730_programmeCounterTest() once per
 * second. 
 * 
 * The test requiring the most iterations to complete is the Invariable 
 * Memory Test. With large memories, it may require frequent calls to 
 * iec60730_Bist() to guarantee all the invariable memory areas are checked 
 * before iec60730_programmeCounterTest() is called. This table assumes the 
 * largest invariable memory size for each device, and a check across 
 * the whole memory area.
 * 
 * The number of blocks per BIST call #INVAR_BLOCKS_PER_BIST is chosen to 
 * get the time between BIST calls close to the watchdog timeout.
 * 
 * Number of iec60730_Bist() calls/second = Size of memory / (Size of CRC block * number of blocks per BIST call)
 * 
 * Maximum time between BIST calls= 1 / (Number of iec60730_Bist calls)
 * 
 * <center><b>Table 4 BIST Call Frequency</b></center> \anchor bist_frequency_table
 * EFR32 Device | Size of memory | Size of CRC block | Blocks per call | Calls/second | Time between BIST calls
 * -------------|----------------|-------------------|-----------------|--------------|------------------------
 * EFR32xG21    | 1024 KB        | 64 bytes          | 512             | 32           | 31.25 ms
 * EFR32xG23    | 512  KB        | 64 bytes          | 512             | 16           | 62.50 ms
 *
 * Checking against smaller areas increase the time between BIST calls.
 * 
 * @subsection fault_reaction_time Fault Reaction Time
 * The default Fault Reaction Time for the IEC60730 library is 1 second. 
 * Because of the BIST call frequency configuration above, a full invariable 
 * memory test can take 1 second to run on the largest memory EFR32 devices. 
 * The \ref Programme_counter_integration check runs once per second by 
 * default, and all completion bits must be set. OEMs can modify the 
 * \ref Clock_integration according to their needs to increase the
 * Fault Reaction Time.
 * 
 * @subsection oem_time OEM time
 * BIST execution time will vary depending upon the state of the invariable 
 * memory tests. These numbers are measured assuming the invariable memory
 * test is working on an area with the maximum remainder. 
 * 
 * The lower of watchdog timeout or BIST call frequency determine how much 
 * available processing time is left for OEM functions.
 * 
 * OEM processing time = lowest( watchdog time, time between BIST calls) - measured BIST execution time
 * 
 * OEM time % = OEM processing time / (lowest( watchdog time, time between BIST calls)
 * 
 * These numbers assume a full invariable memory check against a maximum size EFR32
 * device.
 * 
 * <center><b>Table 5 BIST Time</b></center> \anchor oem_time_table
 * EFR32 Device | Measured BIST execution time 
 * ------------ |------------------------------
 * EFR32xG21    | 3.326 ms                     
 * EFR32xG23    | 3.157 ms                     
 *
 * OEM time is the maximum time for non-IEC60730 functions in the main
 * while(1) loop.
 * @}
 *****************************************************************************/

/**************************************************************************//**
 * @addtogroup efr32_iec60730
 * @{ 
 *****************************************************************************/

/**************************************************************************//**
 * @defgroup IEC60730_EXTRA EFR32 IEC60730 Library Extra Files
 * @{ 
 * @brief Extra files for the EFR32 IEC Library.
 * @}
 *****************************************************************************/

/**************************************************************************//**
 * @addtogroup IEC60730_EXTRA 
 * @{
 * @defgroup iec60730_coding_standard Silicon Labs Coding Standard
 * @{ 
 * @brief Silicon Labs Coding Standard
 * @}
 * @defgroup iec60730_release_notes Release Notes
 * @{ 
 * @brief Release Notes for the IEC60730 Library
 * @}
 * @defgroup iec60730_license_agreement Silicon Labs Software License Agreement
 * @{ 
 * @brief License Agreement for the IEC60730 Library
 * @} 
 * @} 
 *****************************************************************************/

/**************************************************************************//**
 * @defgroup IEC60730_POST POST
 * @{ 
 * @brief Power On Self Test - Executed once during power up.
 * @}
 *****************************************************************************/

/**************************************************************************//**
 * @defgroup IEC60730_BIST BIST 
 * @{ 
 * @brief Built In Self Test - Executed periodically.
 * @}
 *****************************************************************************/

/**************************************************************************//**
 * @defgroup IEC60730_PROGRAMME_COUNTER Programme Counter Check
 * @{ 
 * @brief Verifies all tests have completed on time.
 * @}
 *****************************************************************************/

/**************************************************************************//**
 * @defgroup IEC60730_WDOG_Test Watchdog Test
 * @{ 
 * @brief Monitors CPU execution.
 * @}
 *****************************************************************************/

/**************************************************************************//**
 * @defgroup IEC60730_IRQ_Test IRQ Test
 * @{ 
 * @brief Verifies interrupt frequency is within bounds.
 * @}
 *****************************************************************************/

/**************************************************************************//**
 * @defgroup IEC60730_GPIO_PLAUSIBILTY_Test GPIO Plausibility Test
 * @{ 
 * @brief Verifies GPIOs work properly.
 * @}
 *****************************************************************************/

/**************************************************************************//**
 * @defgroup IEC60730_ADC_PLAUSIBILTY_Test ADC Plausibility Test
 * @{ 
 * @brief Verifies analog components work properly.
 * @}
 *****************************************************************************/

/**************************************************************************//**
 * @defgroup IEC60730_INVARIABLE_MEMORY_Test Invariable Memory Check
 * @{ 
 * @brief Verifies contents of flash memory.
 * @}
 *****************************************************************************/

/**************************************************************************//**
 * @defgroup IEC60730_VARIABLE_MEMORY_Test Variable Memory Check
 * @{ 
 * @brief Verifies RAM is working correctly.
 * @}
 *****************************************************************************/

/**************************************************************************//**
 * @defgroup IEC60730_CPUREG_Test CPU Register Check
 * @{ 
 * @brief Verifies CPU registers are working correctly.
 * @}
 *****************************************************************************/

/**************************************************************************//**
 * @defgroup IEC60730_SYSTEM_CLOCK_Test System clock plausibility test
 * @{ 
 * @brief Verifies that system clocks are within expected frequencies.
 * @}
 *****************************************************************************/

/**************************************************************************//**
 * @defgroup IEC60730_OEM_COMM_Test OEM External Communications Example using UART
 * @{ 
 * @brief Verifies communication channel is operating as expected.
 * @}
 *****************************************************************************/

/**************************************************************************//**
 * @defgroup IEC60730_SAFE_STATE Safe State
 * @{ 
 * @brief When incorrect behavior is detected, this state prevents further execution.
 * @}
 *****************************************************************************/

 /**************************************************************************//**
  * @defgroup IEC60730_VERIFICATION IEC60730 Test Specification
  * @{ 
  * @brief Automated tests for validating correct firmware operation.
  * @}
  *****************************************************************************/

 /** @} (end addtogroup efr32_iec60730) */
