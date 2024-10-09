/***************************************************************************//**
 * @file
 * @brief Interrupt check
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

#ifndef __IEC60730_IRQ_H__
#define __IEC60730_IRQ_H__

#include <si_toolchain.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/**************************************************************************//**
 * @addtogroup efr32_iec60730
 * @{
 * @addtogroup IEC60730_IRQ_Test
 * @{
 * @details The interrupt plausibility test checks that enabled interrupts 
 * are executing at a frequency that is within expected minimum and maximum 
 * bounds every test timer period.
 * 
 * OEM firmware is responsible for setting expected minimum and maximum 
 * bounds for each enabled interrupt in the #iec60730_IRQFreqBounds 
 * structure. The OEM is also responsible for incrementing the element 
 * in the #iec60730_IRQExecCount array inside each enabled interrupt. 
 * In #iec60730_IRQCheck(), which executes as part of the test timer-driven 
 * tests of the BIST, this counter array is compared with the defined 
 * bounds to determine whether each interrupt is operating within safe parameters.
 * 
 * @section irq_hardware_architecture Hardware Architecture
 * Most hardware-implemented peripherals in Silicon Labs EFR32 devices 
 * offer the ability to vector to an interrupt service routine in order 
 * to quickly respond peripheral-related events and state updates.
 * 
 * In order to vector to an interrupt from executing foreground code,
 * hardware pushes the program counter to the stack and vectors to a 
 * hardware-defined entry in a vector table stored in non-volatile memory 
 * in a region of Flash.  The code of the interrupt service routine is 
 * either stored directly within this table entry, or stored elsewhere in 
 * memory and accessed through a jump instruction placed in the vector 
 * table, depending on the size of the interrupt service routine.
 * 
 * Once the function body of the interrupt service routine has completed 
 * executing, the program counter is pop from the stack and 
 * returns to foreground code to continue execution.
 * 
 * Each interrupt has a flag in a register that must be cleared inside the 
 * interrupt service routine function to signal that the interrupt has been 
 * processed in firmware.  Failure to clear this flag inside the function 
 * body will result in the hardware immediately vectoring back to 
 * the interrupt.
 * 
 * @section irq_failure_risks Failure Risks
 * It is the OEM's responsibility to accurately estimate the frequency of 
 * each enabled interrupt in a firmware project.  For interrupts that are 
 * asynchronous and may not execute at all within a test timer period, 
 * the lower bounds for the interrupt should be set to 0.
 * 
 * It is also the OEM's responsibility to increment values in 
 * #iec60730_IRQExecCount once and only once per interrupt execution. 
 * Failure to include this incrementing command will result in an 
 * interrupt that appears to be executing below minimum defined 
 * bounds, which will force safe state entry.
 * 
 * The OEM should also be mindful of all hardware-related constraints of 
 * each interrupt.  Failure to clear an interrupt flag inside an interrupt 
 * service routine will cause the routine to execute repeatedly,
 * which will increment an #iec60730_IRQExecCount entry beyond upper bounds
 * and cause a safe state entry.
 * 
 * The OEM must also perform a bounds check on the element in 
 * #iec60730_IRQExecCount being incremented to ensure that the counter 
 * does not exceed the upper bounds defined by its data type and overflow 
 * back to 0. Failure to perform this bounds check could have the effect 
 * of creating a passing IRQ plausibility test when the interrupt is 
 * actually running outside of defined limits.
 * 
 * @section irq_software_architecture Software Architecture
 * The interrupt plausibility test function relies on an array of counters 
 * called #iec60730_IRQExecCount, stored in volatile memory and an array 
 * of struct #iec60730_IRQExecutionBounds_t found in non-volatile memory 
 * and called #iec60730_IRQFreqBounds. OEM firmware increments bytes in 
 * #iec60730_IRQExecCount during execution of each enabled interrupt 
 * service routine.  When the test timer interrupt occurs, 
 * #iec60730_IRQCheck() executes. Inside this function, firmware compares 
 * the count values to the bound values, and sets #iec60730_SafetyCheck to 
 * #iec60730_InterruptFail if a count exceeds either the minimum or 
 * maximum bounds.  The next execution of the BIST routine will detect the 
 * #iec60730_TestFailed state and enter safe state.  A flowchart of this 
 * functionality is shown in \link irq_plausibility_test_flowchart Figure 1\endlink.
 * 
 * For more information on configuration of the test timer, please see 
 * @ref IEC60730_SYSTEM_CLOCK_Test.
 * 
 * \anchor irq_plausibility_test_flowchart\
 * \image html irq_plausibility_test_flowchart.png "Figure 1 Flow chart of interrupt plausibility check"
 * 
 *****************************************************************************/

/**************************************************************************//**
 * public IEC60730 Interrupt plausibility check
 *
 * @returns None. 
 * 
 * This function compares each entry in #iec60730_IRQExecCount
 * with its corresponding bounds defined in #iec60730_IRQFreqBounds.  If the
 * entry is found to exceed the defined bounds, #iec60730_SafetyCheck is 
 * set to #iec60730_InterruptFail.
 * Otherwise no action is taken.  The function ends by setting 
 * #IEC60730_INTERRUPT_COMPLETE in #iec60730_programmeCounterCheck.
 *****************************************************************************/
void iec60730_IRQCheck(void);

/** @} (end addtogroup IEC60730_IRQ_Test) */
/** @} (end addtogroup efr32_iec60730) */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
