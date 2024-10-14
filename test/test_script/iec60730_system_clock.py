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
# @defgroup IEC60730_SYSTEM_CLOCK_VERIFICATION System Clock Automated Verification Tests
# @{
# Python script for the IEC60730 system clock Verification tests.
#
# For details on the tests, see iec60730_system_clock.iec60730_system_clock.
#
#@section system_clock_test_results Test Results
#
#EFR32 Device | Test Results
#-------------|-------------


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

# Timer0 TOP register address
t_top_dict = {
"EFR32XG2XXX": {"address": 0x4004801C,"mask": 0xFFFFFFFF, "value": 0},
"EFR32XG1XXX": {"address": 0x4001801C,"mask": 0xFFFFFFFF, "value": 0}
}

##  IEC60730 System Clock Verification Tests
#
# @details This class runs IEC60730 verification tests for the system clock test.
#
# Hardware setup:
#   Connect DUT to PC. No additional hardware setup required.

class iec60730_system_clock(unittest.TestCase, iec60730TestBase):
  ## Text name of the test suite, used in XML output.
  TEST_SUITE_NAME = "SystemClock"

  def setUp(self):
    self.env_setup(adapter_serial_no, chip_name, lst_file_path, lib_path, app_type, compiler)


  @iec60730_test_case('TC: System Clock execution test')
  ## Verify the DUT repeatedly executes the system clock test, indicating no erroneous entry into safe state.
  # @details Order of execution:
  #   - Verify code reaches breakpoint at IEC60730_SYSTEM_CLOCK_TICK_BKPT (to verify Clock counter is working).
  #   - Verify code reaches breakpoint at IEC60730_TEST_CLOCK_TICK_BKPT (To verify Clock counter is checked. Test finishes without stuck in safe state.).
  #     - Test passes, return True
  #
  # @return True
  #
  def test_system_clock_execution(self):
    # Set breakpoints in system clock test-related ISRs.
    self.adapter.halt()
    self.adapter.clear_all_breakpoints()
    bp1 = self.adapter.set_breakpoint(address = asm_labels['IEC60730_SYSTEM_CLOCK_TICK_BKPT'],
                                      typeflags=enums.JLinkBreakpoint.ANY)
    # Reset device
    self.adapter.reset()
    pc = self.adapter.run_to_breakpoint(1)
    logging.info("Halted at label: " + self.get_label(pc))
    self.assertEqual(pc, asm_labels['IEC60730_SYSTEM_CLOCK_TICK_BKPT'],\
                    "DUT failed to enter system clock tick" \
                    " , pc = " + hex(pc))

    self.adapter.clear_all_breakpoints()
    bp2 = self.adapter.set_breakpoint(address = asm_labels['IEC60730_TEST_CLOCK_TICK_BKPT'],
                                      typeflags=enums.JLinkBreakpoint.ANY)

    pc = self.adapter.run_to_breakpoint(1)
    logging.info("Halted at label: " + self.get_label(pc))
    self.assertEqual(pc, asm_labels['IEC60730_TEST_CLOCK_TICK_BKPT'],\
                    "DUT did not run system clock test" \
                    " , pc = " + hex(pc))

    self.adapter.clear_all_breakpoints()
    bp1 = self.adapter.set_breakpoint(address = asm_labels['IEC60730_SYSTEM_CLOCK_TICK_BKPT'],
                                      typeflags=enums.JLinkBreakpoint.ANY)

    pc = self.adapter.run_to_breakpoint(1)
    logging.info("Halted at label: " + self.get_label(pc))
    self.assertEqual(pc, asm_labels['IEC60730_SYSTEM_CLOCK_TICK_BKPT'],\
                    "DUT did not run system clock test a second time, indicating safe state entry" \
                    " , pc = " + hex(pc))

    logging.info("DUT correctly running system clock test")
    return True

  @iec60730_test_case('TC: Enter SafeState when system clock out of low bound')
  ## Verifies that the BIST system clock test enters safe state when out-of-bounds system clock is enabled
  # @details The system clock test is validated by forcing a system clock frequency that runs low
  # bound checked by the test.  Testing validates that the system enters safe state
  # after the system clock is forced low bound, as shown in  \link BIST_system_clock_frequency_validation Figure 2.\endlink
  #
  # Order of execution:
  #   - Verify code reaches breakpoint at IEC60730_SYSTEM_CLOCK_FREQ_ADJUSTMENT_BKPT
  #   - Change timer TOP register to multi by 2, forcing it low bound
  #   - Verify code reaches breakpoint at IEC60730_SAFE_STATE_BKPT
  #     - Code correctly tested entered iec60730_SafeState() due to out of bounds clock
  #     - Test passes, return True
  #
  # @return True
  #
  # \image html BIST_system_clock_frequency_validation.jpg "Figure 2 System clock frequency check flowchart" \anchor BIST_system_clock_frequency_validation

  def test_system_clock_Low_safe_state_entry(self):
    # Set breakpoint to force system clock out of bounds and breakpoint for safe state entry
    self.adapter.halt()
    self.adapter.clear_all_breakpoints()
    self.adapter.set_breakpoint(address = asm_labels['IEC60730_SYSTEM_CLOCK_FREQ_ADJUSTMENT_BKPT'],
                                 typeflags=enums.JLinkBreakpoint.ANY)
    self.adapter.set_breakpoint(address = asm_labels['IEC60730_SAFE_STATE_BKPT'],
                                 typeflags=enums.JLinkBreakpoint.ANY)
    # Reset device
    self.adapter.reset()
    pc = self.adapter.run_to_breakpoint(1)
    logging.info("Halted at label: " + self.get_label(pc))
    self.assertEqual(pc, asm_labels['IEC60730_SYSTEM_CLOCK_FREQ_ADJUSTMENT_BKPT'],\
                    "DUT isn't reaching post test after IEC clock initialization" \
                    " , pc = " + hex(pc))

    # Change value of the CMU register to change system clock
    dev_id = ''
    if -1 != chip_name.find("G1"):
      dev_id = "EFR32XG1XXX"
      logging.info("Modifying device "+dev_id)

      # Stop timer
      reg = self.adapter.memory_write32(addr = (0x4004800C), data = [2], zone=None)

      reg = self.adapter.read_ram_arm_32(address = (t_top_dict[dev_id]["address"]),num_words = 1)
      logging.info("Read mem value: " + hex(reg[0]))
      reg[0] = int(reg[0]*2)
      logging.info("Write mem value: " + hex(reg[0]))
      reg = self.adapter.memory_write32(addr = (t_top_dict[dev_id]["address"]), data =  (reg), zone=None)

      # Start timer
      reg = self.adapter.memory_write32(addr = (0x4004800C), data = [1], zone=None)

    elif -1 != chip_name.find("G2"):
      dev_id = "EFR32XG2XXX"
      logging.info("Modifying device "+dev_id)
      # Stop timer
      reg = self.adapter.memory_write32(addr = (0x40048004), data = [0x00000002], zone=None)

      # Change TOP register value
      reg = self.adapter.read_ram_arm_32(address = (t_top_dict[dev_id]["address"]),num_words = 1)
      logging.info("Read mem value: " + hex(reg[0]))
      reg[0] = int(reg[0]*2)
      logging.info("Write mem value: " + hex(reg[0]))
      reg = self.adapter.memory_write32(addr = (t_top_dict[dev_id]["address"]), data =  (reg), zone=None)

      # Start timer
      reg = self.adapter.memory_write32(addr = (0x40048004), data = [0x00000001], zone=None)
    else:
      self.assertEqual(0, 1, "Invalid DUT")

    pc = self.adapter.run_to_breakpoint(2)
    logging.info("Halted at label: " + self.get_label(pc))
    self.assertEqual(pc, asm_labels['IEC60730_SAFE_STATE_BKPT'],\
                    "DUT did not enter safe state for out-of-bounds low system clock" \
                    " , pc = " + hex(pc))

    logging.info("DUT correctly detected an out-of-bounds low clock and entered safe state")
    return True

  @iec60730_test_case('TC: Enter SafeState when system clock out of high bound')
  ## Verifies that the BIST system clock test enters safe state when out-of-bounds system clock is enabled
  # @details The system clock test is validated by simulate a system clock frequency that runs high
  # bound checked by the test.  Testing validates that the system enters safe state
  # after the system clock is out of bounds, as shown in  \link BIST_system_clock_frequency_validation Figure 2.\endlink
  #
  # Order of execution:
  #   - Verify code reaches breakpoint at IEC60730_SYSTEM_CLOCK_FREQ_ADJUSTMENT_BKPT
  #   - Change timer TOP register to divided by 2, forcing it high bound
  #   - Verify code reaches breakpoint at IEC60730_SAFE_STATE_BKPT
  #     - Code correctly tested entered iec60730_SafeState() due to out of bounds clock
  #     - Test passes, return True
  #
  # @return True
  #
  # \image html BIST_system_clock_frequency_validation.jpg "Figure 2 System clock frequency check flowchart" \anchor BIST_system_clock_frequency_validation

  def test_system_clock_high_safe_state_entry(self):
    # Set breakpoint to force system clock out of bounds and breakpoint for safe state entry
    self.adapter.halt()
    self.adapter.clear_all_breakpoints()
    self.adapter.set_breakpoint(address = asm_labels['IEC60730_SYSTEM_CLOCK_FREQ_ADJUSTMENT_BKPT'],
                                 typeflags=enums.JLinkBreakpoint.ANY)
    self.adapter.set_breakpoint(address = asm_labels['IEC60730_SAFE_STATE_BKPT'],
                                 typeflags=enums.JLinkBreakpoint.ANY)
    # Reset device
    self.adapter.reset()
    pc = self.adapter.run_to_breakpoint(1)
    logging.info("Halted at label: " + self.get_label(pc))
    self.assertEqual(pc, asm_labels['IEC60730_SYSTEM_CLOCK_FREQ_ADJUSTMENT_BKPT'],\
                    "DUT isn't reaching post test after IEC clock initialization" \
                    " , pc = " + hex(pc))

    # Change value of the Timer register to change overflow rate
    dev_id = ''
    if -1 != chip_name.find("G1"):
      dev_id = "EFR32XG1XXX"
      logging.info("Modifying device "+dev_id)

      # Stop timer
      reg = self.adapter.memory_write32(addr = (0x4004800C), data = [2], zone=None)

      reg = self.adapter.read_ram_arm_32(address = (t_top_dict[dev_id]["address"]),num_words = 1)
      logging.info("Read mem value: " + hex(reg[0]))
      reg[0] = int(reg[0]/2)
      logging.info("Write mem value: " + hex(reg[0]))
      reg = self.adapter.memory_write32(addr = (t_top_dict[dev_id]["address"]), data =  (reg), zone=None)

      # Start timer
      reg = self.adapter.memory_write32(addr = (0x4004800C), data = [1], zone=None)
      reg = self.adapter.read_ram_arm_32(address = (0x4004800C),num_words = 1)
      logging.info("Read mem value: " + hex(reg[0]))
    elif -1 != chip_name.find("G2"):
      dev_id = "EFR32XG2XXX"
      logging.info("Modifying device "+dev_id)

      # Stop timer
      reg = self.adapter.memory_write32(addr = (0x40048004), data = [0x00000002], zone=None)

      # Change TOP register value
      reg = self.adapter.read_ram_arm_32(address = (t_top_dict[dev_id]["address"]),num_words = 1)
      logging.info("Read mem value: " + hex(reg[0]))
      reg[0] = int(reg[0]/2)
      logging.info("Write mem value: " + hex(reg[0]))
      reg = self.adapter.memory_write32(addr = (t_top_dict[dev_id]["address"]), data =  (reg), zone=None)

      # Start timer
      reg = self.adapter.memory_write32(addr = (0x40048004), data = [0x00000001], zone=None)
    else:
      self.assertEqual(0, 1, "Invalid DUT")

    pc = self.adapter.run_to_breakpoint(2)
    logging.info("Halted at label: " + self.get_label(pc))
    self.assertEqual(pc, asm_labels['IEC60730_SAFE_STATE_BKPT'],\
                    "DUT did not enter safe state for out-of-bounds high system clock" \
                    " , pc = " + hex(pc))

    logging.info("DUT correctly detected an out-of-bounds high clock and entered safe state")
    return True

if __name__ == "__main__":

  chip_name = os.getenv('CHIP')
  print("Chip ID: "+chip_name)
  app_type = os.getenv('APP_TYPE')
  lst_file_path = os.getenv('LST_PATH')
  print("List file path: "+lst_file_path)
  adapter_serial_no = os.getenv('ADAPTER_SN')
  print("Adapter ID: "+adapter_serial_no)
  lib_path = os.getenv('JLINK_PATH')
  print("Debugger Lib path: "+lib_path)

  while len(sys.argv) > 1:
    line = sys.argv.pop()
    if len(sys.argv) == 1:
        compiler = line

  print("Compiler: "+compiler)

  unittest.main()

## @}
# @}
