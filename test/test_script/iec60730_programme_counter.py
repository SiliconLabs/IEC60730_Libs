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
# @defgroup IEC60730_PROGRAMME_COUNTER_VERIFICATION Programme Counter Verification Tests
# @{
# Python script for the IEC60730 Programme Counter Verification tests.
#
# For details on the tests, see iec60730_programme_counter.iec60730_programme_counter.
#
#@section programme_counter_test_results Test Results
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


##  IEC60730 CPU programme counter Tests
#
# @details This class runs IEC60730 programme counter tests.
#
# Hardware setup:
#   Connect DUT to PC. No additional hardware setup required.

class iec60730_programme_counter(unittest.TestCase, iec60730TestBase):
  ## Text name of the test suite, used in XML output.
  TEST_SUITE_NAME = "PROGRAMME_COUNTER"

  def setUp(self):
    self.env_setup(adapter_serial_no, chip_name, lst_file_path, lib_path, app_type, compiler)


  @iec60730_test_case('TC: Verify programme counter execution')
  ## Verify the DUT repeatedly programme counter test, indicating programme counter correctly running.
  # @details Order of execution:
  #   - Verify code reaches breakpoint at IEC60730_PC_BKPT
  #   - Verify code reaches breakpoint at IEC60730_PC_BKPT
  #     - Test passes, return True
  #
  # @return True
  #
  def test_01_programme_counter_execution(self):
    # Set breakpoints in system clock test-related ISRs.
    self.adapter.halt()
    self.adapter.clear_all_breakpoints()

    self.adapter.set_breakpoint(address = asm_labels['IEC60730_PC_BKPT'],
                                 typeflags=enums.JLinkBreakpoint.ANY)

    self.adapter.set_breakpoint(address = asm_labels['iec60730_SafeState'],
                                 typeflags=enums.JLinkBreakpoint.ANY)

    self.adapter.reset()
    pc = self.adapter.run_to_breakpoint(2)
    logging.info("Halted at label: " + self.get_label(pc))
    self.assertEqual(pc, asm_labels['IEC60730_PC_BKPT'],\
                    "DUT failed to stop at IEC60730_PC_BKPT" \
                    " , pc = " + hex(pc))

    pc = self.adapter.run_to_breakpoint(2)
    self.assertEqual(pc, asm_labels['IEC60730_PC_BKPT'], \
                      "DUT failed to stop at IEC60730_PC_BKPT a second time" + \
                      ", pc = " + hex(pc))

    logging.info("DUT correctly running programme counter test")

    return True


  @iec60730_test_case('TC: Enter SafeState when programme counter tests are not executing within period')
  ## Verify the DUT repeatedly executes programme counter test, indicating programme counter enters safe state.
  # @details Order of execution:
  #   - Verify code reaches breakpoint at IEC60730_PC_BKPT
  #   - Inject fault condition into programme counter flags
  #   - Verify code reaches breakpoint at iec60730_SafeState
  #     - Test passes, return True
  #
  # @return True
  #
  def test_02_programme_counter_too_slow(self):
    programmeCounterCheck_loc = variables['iec60730_programmeCounterCheck']

    self.assertNotEqual(0, programmeCounterCheck_loc,\
                    "Can not read iec60730_programmeCounterCheck address")

    # Set breakpoints in system clock test-related ISRs.
    self.adapter.halt()
    self.adapter.clear_all_breakpoints()

    self.adapter.set_breakpoint(address = asm_labels['IEC60730_PC_BKPT'],
                                 typeflags=enums.JLinkBreakpoint.ANY)



    self.adapter.reset()
    pc = self.adapter.run_to_breakpoint(2)
    logging.info("Halted at label: " + self.get_label(pc))
    self.assertEqual(pc, asm_labels['IEC60730_PC_BKPT'],\
                    "DUT failed to stop at IEC60730_PC_BKPT" \
                    " , pc = " + hex(pc))

    self.adapter.clear_all_breakpoints()

    self.adapter.set_breakpoint(address = asm_labels['iec60730_SafeState'],
                                 typeflags=enums.JLinkBreakpoint.ANY)

    # Clear bist execution completion flag bits
    self.adapter.memory_write16(addr = programmeCounterCheck_loc, data = {0x0000})

    read_value = self.adapter.memory_read16(addr = programmeCounterCheck_loc,num_halfwords=1)

    # Verify written data
    self.assertEqual(0, read_value[0], \
                      "Cannot clear BIST execution flag" + \
                      ", read value = " + str(read_value[0]))

    pc = self.adapter.run_to_breakpoint(2)
    self.assertEqual(pc, asm_labels['iec60730_SafeState'], \
                      "DUT did not enter safe state after bist frequency fail" + \
                      ", pc = " + hex(pc))

    logging.info("DUT correctly entered safe state after programme counter check failure")

    return True

if __name__ == "__main__":

  chip_name = os.getenv('CHIP')

  app_type = os.getenv('APP_TYPE')

  lst_file_path = os.getenv('LST_PATH')

  adapter_serial_no = os.getenv('ADAPTER_SN')

  lib_path = os.getenv('JLINK_PATH')

  while len(sys.argv) > 1:
    line = sys.argv.pop()
    if len(sys.argv) == 1:
      compiler = line

  print("Compiler: "+compiler)

  unittest.main()

## @}
# @}
