#!/usr/bin/env python
# License
# <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
# *******************************************************************************
#
# The licensor of this software is Silicon Laboratories Inc. Your use of this
# software is governed by the terms of Silicon Labs Master Software License
# Agreement (MSLA) available at
# www.silabs.com/about-us/legal/master-software-license-agreement. This
# software is distributed to you in Source Code format and is governed by the
# sections of the MSLA applicable to Source Code.
# *******************************************************************************

## @addtogroup IEC60730_VERIFICATION
# @{
# @defgroup IEC60730_IRQ_VERIFICATION IRQ Automated Verification Tests
# @{
# Python script for the IEC60730 IRQ plausibility verification tests.
#
# For details on the tests, see iec60730_irq.iec60730_irq.
#
#@section irq_test_results Test Results
#
#EFR32 Device| Test Results
#------------|-------------

from binascii import hexlify
import random
import os
import sys
from time import sleep

from iec60730_test_base import *
import jlink, jlink_constants
import unittest
import enums

def int_to_bytes(number: int) -> bytes:
    return number.to_bytes(length=(8 + (number + (number < 0)).bit_length()) // 8, byteorder='big', signed=True)

##  IEC60730 IRQ Plausibility Verification Tests
#   
# @details This class runs IEC60730 verification tests for the irq plausibility test.
#  
# Hardware setup:
#   Connect DUT to PC. No additional hardware setup required.
class iec60730_irq(unittest.TestCase, iec60730TestBase):
  ## Text name of the test suite, used in XML output.
  TEST_SUITE_NAME = "IRQ"
  
  ## Initialization function
  def setUp(self):
    self.env_setup(adapter_serial_no, chip_name, lst_file_path, lib_path, app_type, compiler)

  @iec60730_test_case('TC: IRQ execution test')
  ## Verify the DUT repeatedly executes the IRQ plausibility test, indicating no erroneous entry into safe state.
  # @details Order of execution:
  #   - Verify code reaches breakpoint at IEC60730_IRQ_BKPT
  #   - Verify code reaches breakpoint at IEC60730_IRQ_BKPT
  #     - Test passes, return True
  #
  # @return True
  #
  def test_irq_execution(self):
    # Set breakpoints in system clock test-related ISRs.
    self.adapter.halt()
    self.adapter.clear_all_breakpoints()
    self.adapter.set_breakpoint(address = asm_labels['IEC60730_IRQ_BKPT'], 
                                 typeflags=enums.JLinkBreakpoint.ANY)
    self.adapter.set_breakpoint(address = asm_labels['IEC60730_SAFE_STATE_BKPT'], 
                                 typeflags=enums.JLinkBreakpoint.ANY)
    # Reset device
    self.adapter.reset()
    pc = self.adapter.run_to_breakpoint(1)
    logging.info("Halted at label: " + self.get_label(pc))
    self.assertEqual(pc, asm_labels['IEC60730_IRQ_BKPT'],\
                    "DUT failed enter IRQ test" \
                    " , pc = " + hex(pc))

    pc = self.adapter.run_to_breakpoint(1)
    logging.info("Halted at label: " + self.get_label(pc))
    self.assertEqual(pc, asm_labels['IEC60730_IRQ_BKPT'],\
                    "DUT did not enter IRQ a second time" \
                    " , pc = " + hex(pc))    
    
    logging.info("DUT correctly running IRQ plausibility test")
    return True
  
  @iec60730_test_case('TC: Enter SafeState when IRQ is found to be executing outside of OEM-specified bounds')
  ## Verifies that the IRQ plausibility test forces entry into safe state when IRQs execute out-of-spec.
  # @details Order of execution:
  #   - Verify code reaches breakpoint at IEC60730_IRQ_BKPT
  #   - Force value of interrupt count to be less than minimum
  #   - Verify safe state entrance
  #   - Reset
  #   - Verify code reaches breakpoint at IEC60730_IRQ_BKPT
  #   - Force value of interrupt count to be higher than maximum
  #   - Verify code reaches breakpoint at IEC60730_SAFE_STATE_BKPT
  #     - Code correctly tested entered iec60730_SafeState() due to out of bounds clock
  #     - Test passes, return True
  #
  # @return True
  #
  # \image html irq_plausibility_test_validation_flowchart.jpg "Figure 1 Execution Flow of of IRQ plausibility test" \anchor irq_plausibility_test_validation_flowchart
  def test_IRQ_out_of_bounds(self):
    var_name = "iec60730_IRQExecCount"

    variables[var_name] = \
      self.get_variable_address("/../", var_name)

    self.assertNotEqual(0, variables[var_name],\
                    "Can not read "+ var_name +" address")
    
    # Set breakpoint to force IRQs to to appear as though they've not executed to frequently/infrequently, and breakpoint for safe state entry
    self.adapter.halt()
    self.adapter.clear_all_breakpoints()
    self.adapter.set_breakpoint(address = asm_labels['IEC60730_IRQ_BKPT'], 
                                 typeflags=enums.JLinkBreakpoint.ANY)
    self.adapter.set_breakpoint(address = asm_labels['IEC60730_SAFE_STATE_BKPT'], 
                                 typeflags=enums.JLinkBreakpoint.ANY)
                                 
    # Reset device
    self.adapter.reset()
    pc = self.adapter.run_to_breakpoint(1)
    logging.info("Halted at label: " + self.get_label(pc))
    self.assertEqual(pc, asm_labels['IEC60730_IRQ_BKPT'],\
                    "DUT failed to reach IRQ plausibility test" \
                    " , pc = " + hex(pc))
      
    # Set count of IRQ to be 0, when minimum in code is 1 (interrupt index 0, timer clock)
    self.adapter.memory_write8(addr = (variables[var_name]), data =  {0x00}, zone=None)
    
    pc = self.adapter.run_to_breakpoint(2)
    logging.info("Halted at label: " + self.get_label(pc))
    self.assertEqual(pc, asm_labels['IEC60730_SAFE_STATE_BKPT'],\
                    "DUT did not enter safe state after IRQ plausibility fail" \
                    " , pc = " + hex(pc))
    
    self.adapter.reset()
    pc = self.adapter.run_to_breakpoint(1)
    logging.info("Halted at label: " + self.get_label(pc))
    self.assertEqual(pc, asm_labels['IEC60730_IRQ_BKPT'],\
                    "DUT failed to reach IRQ plausibility test" \
                    " , pc = " + hex(pc))
                    
    # Set count of IRQ to be 13, when maximum in code is 11 (interrupt index 1, system clock)
    self.adapter.memory_write8(addr = (variables[var_name]+1), data =  {13}, zone=None)
      
    pc = self.adapter.run_to_breakpoint(2)
    logging.info("Halted at label: " + self.get_label(pc))
    self.assertEqual(pc, asm_labels['IEC60730_SAFE_STATE_BKPT'],\
                    "DUT did not enter safe state after IRQ plausibility fail" \
                    " , pc = " + hex(pc))
    logging.info("DUT correctly entered safe state after IRQ plausibility check failure")
    return True

if __name__ == "__main__":

  chip_name = os.getenv('CHIP')
  # print("Chip ID: "+chip_name)
  app_type = os.getenv('APP_TYPE')
  lst_file_path = os.getenv('LST_PATH')
  # print("List file path: "+lst_file_path)
  adapter_serial_no = os.getenv('ADAPTER_SN')
  # print("Adapter ID: "+adapter_serial_no)
  lib_path = os.getenv('JLINK_PATH')
  # print("Debugger Lib path: "+lib_path)
  
  while len(sys.argv) > 1:
    line = sys.argv.pop()
    if len(sys.argv) == 1:
        compiler = line

  print("Compiler: "+compiler)
  unittest.main()
  
## @}
# @}