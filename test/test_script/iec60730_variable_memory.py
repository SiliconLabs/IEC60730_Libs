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
# @defgroup IEC60730_VARIABLE_MEMORY_VERIFICATION Variable Memory Automated Verification Tests
# @{
# Python script for the IEC60730 Variable Memory plausibility verification tests.
#
# For details on the tests, see iec60730_variable_memory.iec60730_variable_memory.
#
#@section irq_test_results Test Results
#
#EFR32 Device| Test Results
#------------|-------------

from binascii import hexlify
from logging import debug, log
import random
import os
import sys
from time import sleep

from iec60730_test_base import *
import jlink, jlink_constants
import unittest
import enums

is_enableMatchX = True
is_nonSecure = False

# this value reference to file #IEC_BOARD_HEADER (sl_iec60730_board.h)
RAMTEST_END = 0x20000080

##  IEC60730 Variable Memory Plausibility Verification Tests
#
# @details This class runs IEC60730 verification tests for the variable memory plausibility test.
#
# Hardware setup:
#   Connect DUT to PC. No additional hardware setup required.

class iec60730_vmc(unittest.TestCase, iec60730TestBase):
  TEST_SUITE_NAME = "VMC"

  def setUp(self):
    self.env_setup(adapter_serial_no, chip_name, lst_file_path, lib_path, app_type, compiler)

  def set_breakpoint(self, label) :
    self.adapter.set_breakpoint(address = asm_labels[label],
                                typeflags=enums.JLinkBreakpoint.ANY)

  def reach_to_breakpoint(self, label, setbkp, time) :
    if setbkp :
      self.set_breakpoint(label)

    logging.info("Run to bkp: " + label)
    pc = self.adapter.run_to_breakpoint(time)

    self.assertEqual(pc, asm_labels[label], \
                    "DUT failed to stop at " + label + \
                    ", pc = " + hex(pc) + \
                    ", setbkp = " + str(setbkp))

  def corruption(self,
                address = 0,
                value = 0,
                time = 1,
                label = '',
                label_pass = 'iec60730_SafeState') :
    self.reach_to_breakpoint(label, True, time)
    # write data to address
    self.adapter.memory_write32(address, data = {value})
    logging.info("Write to location: " + hex(address) + ", bkp: " + label)
    temp = self.adapter.memory_read32(address, 1)
    logging.info("Read from location: " + hex(address) + ", val = " + hex(temp[0]))
    self.reach_to_breakpoint(label_pass, True, time)
    self.adapter.clear_all_breakpoints()
    self.adapter.reset()
    # self.reach_to_breakpoint(label, True, time)

  @iec60730_test_case('TC: Run step by step when testing Full Ram class B')
  ## Verify the DUT run step by step when testing full ram at POST. This test
  # case (TC) checks under normal conditions with no exceptions, VMC module
  # DOES NOT raise issue.
  #
  # @details Order of execution
  # - Reset device
  # - Verify code reaches breakpoint at IEC60730_MARCHC_STEP_SAVE
  # - Verify code reaches breakpoint at IEC60730_MARCHC_STEP_STEP1
  # - Verify code reaches breakpoint at IEC60730_MARCHC_STEP_STEP2
  # - Verify code reaches breakpoint at IEC60730_MARCHC_STEP_STEP3
  # - Verify code reaches breakpoint at IEC60730_MARCHC_STEP_STEP4
  # - Verify code reaches breakpoint at IEC60730_MARCHC_STEP_STEP5
  # - Verify code reaches breakpoint at IEC60730_MARCHC_STEP_STEP6
  # - Verify code reaches breakpoint at IEC60730_MARCHC_STEP_RESTORE
  # - Verify code reaches breakpoint at IEC60730_MARCHC_STEP_MARCH_RET
  # - Verify code reaches breakpoint at IEC60730_VMC_POST_MARCHC_STEP_BKPT
  #
  # This process in loop with coditon \ref rtCheck < #RAMTEST_END. In case this
  # condition is not satisfied, clear all break point and verify
  #
  # - Verify code reaches breakpoint at IEC60730_VMC_POST_CHECKBKBUF_BKPT
  # - Verify code reaches breakpoint at IEC60730_MARCHC_STEP_BUFF1
  # - Verify code reaches breakpoint at IEC60730_MARCHC_STEP_BUFF2
  # - Verify code reaches breakpoint at IEC60730_MARCHC_STEP_BUFF3
  # - Verify code reaches breakpoint at IEC60730_MARCHC_STEP_BUFF4
  # - Verify code reaches breakpoint at IEC60730_MARCHC_STEP_BUFF5
  # - Verify code reaches breakpoint at IEC60730_MARCHC_STEP_BUFF6
  # - Verify code reaches breakpoint at IEC60730_MARCHC_STEP_MARCH_RET
  # - Verify code reaches breakpoint at IEC60730_MARCHC_STEP_RET
  #
  # @return True
  #
  def test_CorrectBackGround_FullRamClassB(self):
    self.adapter.halt()
    self.adapter.clear_all_breakpoints()
    self.adapter.reset()

    firstTime = True

    self.reach_to_breakpoint('IEC60730_VMC_POST_START_BKPT', True, 1)
    self.adapter.clear_all_breakpoints()

    rtCheck_location = variables['rtCheck']
    rtCheck = self.adapter.memory_read32(rtCheck_location, 1)

    phaseSteps = ['IEC60730_MARCHC_STEP_SAVE',
                  'IEC60730_MARCHC_STEP_STEP1',
                  'IEC60730_MARCHC_STEP_STEP2',
                  'IEC60730_MARCHC_STEP_STEP3',
                  'IEC60730_MARCHC_STEP_STEP4',
                  'IEC60730_MARCHC_STEP_STEP5',
                  'IEC60730_MARCHC_STEP_STEP6',
                  'IEC60730_MARCHC_STEP_RESTORE',
                  'IEC60730_MARCHC_STEP_MARCH_RET',
                  'IEC60730_VMC_POST_MARCHC_STEP_BKPT']

    while rtCheck[0] < RAMTEST_END :
      logging.info(" rtCheck: " + hex(rtCheck[0]))
      for phase in phaseSteps :
        self.reach_to_breakpoint(phase, firstTime, 1)
      rtCheck = self.adapter.memory_read32(rtCheck_location, 1)
      firstTime = False

    self.adapter.clear_all_breakpoints()

    phaseBuffs = ['IEC60730_VMC_POST_CHECKBKBUF_BKPT',
                  'IEC60730_MARCHC_STEP_BUFF1',
                  'IEC60730_MARCHC_STEP_BUFF2',
                  'IEC60730_MARCHC_STEP_BUFF3',
                  'IEC60730_MARCHC_STEP_BUFF4',
                  'IEC60730_MARCHC_STEP_BUFF5',
                  'IEC60730_MARCHC_STEP_BUFF6',
                  'IEC60730_MARCHC_STEP_MARCH_RET',
                  'IEC60730_MARCHC_STEP_RET']
    for phase in phaseBuffs :
      self.reach_to_breakpoint(phase, True, 1)

    return True

  @iec60730_test_case('TC: Detect corruption when testing Full Ram class B')
  ## Verify the DUT jump to #iec60730_SafeState when testing ram failed at
  # post. This TC simulates an abnormal situation that causes the \ref rtCheck,
  # and \ref bkBuf variables to be changed. This leads to jump to break point at
  # #iec60730_SafeState.
  #
  # In the VMC documentation there is a detailed description of the \ref rtCheck,
  # and \ref bkBuf variables.
  #
  # @details Order of execution
  # - Reset device
  # - Verify code reaches breakpoint at IEC60730_MARCHC_STEP_STEP2. We don't reach
  # IEC60730_MARCHC_STEP_STEP1 because this step only write (W1)
  #   - Edit value at address of \ref rtCheck
  #   - Verify code reaches breakpoint at #iec60730_SafeState
  # - Verify code reaches breakpoint at IEC60730_MARCHC_STEP_STEP3
  #   - Edit value at address of \ref rtCheck
  #   + Verify code reaches breakpoint at #iec60730_SafeState
  # - Verify code reaches breakpoint at IEC60730_MARCHC_STEP_STEP4
  #   - Edit value at address of \ref rtCheck
  #   - Verify code reaches breakpoint at #iec60730_SafeState
  # - Verify code reaches breakpoint at IEC60730_MARCHC_STEP_STEP5
  #   - Edit value at address of \ref rtCheck
  #   - Verify code reaches breakpoint at #iec60730_SafeState
  # - Verify code reaches breakpoint at IEC60730_MARCHC_STEP_STEP6
  #   - Edit value at address of \ref rtCheck
  #   - Verify code reaches breakpoint at #iec60730_SafeState
  #
  # - Verify code reaches breakpoint at IEC60730_VMC_POST_CHECKBKBUF_BKPT
  #
  # - Verify code reaches breakpoint at IEC60730_MARCHC_STEP_BUFF2. We don't reach
  # IEC60730_MARCHC_STEP_BUFF1 because this step only write (W1)
  #   - Edit value at address of \ref bkBuf
  #   - Verify code reaches breakpoint at #iec60730_SafeState
  # - Verify code reaches breakpoint at IEC60730_MARCHC_STEP_BUFF3
  #   - Edit value at address of \ref bkBuf
  #   - Verify code reaches breakpoint at #iec60730_SafeState
  # - Verify code reaches breakpoint at IEC60730_MARCHC_STEP_BUFF4
  #   - Edit value at address of \ref bkBuf
  #   - Verify code reaches breakpoint at #iec60730_SafeState
  # - Verify code reaches breakpoint at IEC60730_MARCHC_STEP_BUFF5
  #   - Edit value at address of \ref bkBuf
  #   - Verify code reaches breakpoint at #iec60730_SafeState
  # - Verify code reaches breakpoint at IEC60730_MARCHC_STEP_BUFF6
  #   - Edit value at address of \ref bkBuf
  #   - Verify code reaches breakpoint at #iec60730_SafeState
  #
  # @return True
  #
  def test_DetectCorruption_FullRamClassB(self):
    self.adapter.halt()
    self.adapter.clear_all_breakpoints()
    self.adapter.reset()

    self.reach_to_breakpoint('IEC60730_VMC_POST_START_BKPT', True, 1)
    self.adapter.clear_all_breakpoints()

    rtCheck_location = variables['rtCheck']

    phaseSteps = ['IEC60730_MARCHC_STEP_STEP2',
                  'IEC60730_MARCHC_STEP_STEP3',
                  'IEC60730_MARCHC_STEP_STEP4',
                  'IEC60730_MARCHC_STEP_STEP5',
                  'IEC60730_MARCHC_STEP_STEP6']

    for phase in phaseSteps :
      self.corruption(address = rtCheck_location,
                      value = 0xA5A5A5A5,
                      time = 1,
                      label = phase,
                      label_pass = 'iec60730_SafeState')

    self.adapter.clear_all_breakpoints()
    self.adapter.reset()

    # TODO: Check test case again
    self.reach_to_breakpoint('IEC60730_VMC_POST_CHECKBKBUF_BKPT', True, 1)
    self.adapter.clear_all_breakpoints()

    bkBuf_location = 0
    bkBuf_location = variables['bkBuf']

    phaseBuffs = ['IEC60730_MARCHC_STEP_BUFF2',
                  'IEC60730_MARCHC_STEP_BUFF3',
                  'IEC60730_MARCHC_STEP_BUFF4',
                  'IEC60730_MARCHC_STEP_BUFF5',
                  'IEC60730_MARCHC_STEP_BUFF6']

    for phase in phaseBuffs :
      self.corruption(address = bkBuf_location,
                      value = 0xA5A5A5A5,
                      time = 1,
                      label = phase,
                      label_pass = 'iec60730_SafeState')

    return True

  @iec60730_test_case('TC: Run step by step when testing Step Ram class B')
  ## Verify the DUT run step by step when testing full ram at BIST. This TC
  # checks under normal conditions with no exceptions, vmc module DOES NOT raise
  # issue.
  #
  # @details Order of execution
  # - Reset device
  #
  # - Verify code reaches breakpoint at IEC60730_VMC_BIST_START_BKPT
  #
  # The loop with coditon \ref rtCheck < #RAMTEST_END
  # - Verify code reaches breakpoint at IEC60730_MARCHCX_STEP_SAVE
  # - Verify code reaches breakpoint at IEC60730_MARCHCX_STEP_STEP1
  # - Verify code reaches breakpoint at IEC60730_MARCHCX_STEP_STEP2
  # - if not enable MatchX
  #   - Verify code reaches breakpoint at IEC60730_MARCHCX_STEP_STEP3
  #   - Verify code reaches breakpoint at IEC60730_MARCHCX_STEP_STEP4
  # - Verify code reaches breakpoint at IEC60730_MARCHCX_STEP_STEP5
  # - Verify code reaches breakpoint at IEC60730_MARCHCX_STEP_STEP6
  # - Verify code reaches breakpoint at IEC60730_MARCHCX_STEP_RESTORE
  # - Verify code reaches breakpoint at IEC60730_MARCHCX_STEP_MARCH_RET
  # - Verify code reaches breakpoint at IEC60730_MARCHCX_STEP_RET
  # - Verify code reaches breakpoint at IEC60730_VMC_BIST_MARCHC_STEP_BKPT
  #
  # In case condition is not satisfied, clear all break point and verify
  #
  # - Verify code reaches breakpoint at IEC60730_IMC_BIST_CHECKBKBUF_BKPT
  # - Verify code reaches breakpoint at IEC60730_MARCHCX_STEP_BUFF1
  # - Verify code reaches breakpoint at IEC60730_MARCHCX_STEP_BUFF2
  # - if not enable MatchX
  #   - Verify code reaches breakpoint at IEC60730_MARCHCX_STEP_BUFF3
  #   - Verify code reaches breakpoint at IEC60730_MARCHCX_STEP_BUFF4
  # - Verify code reaches breakpoint at IEC60730_MARCHCX_STEP_BUFF5
  # - Verify code reaches breakpoint at IEC60730_MARCHCX_STEP_BUFF6
  # - Verify code reaches breakpoint at IEC60730_MARCHCX_STEP_MARCH_RET
  # - Verify code reaches breakpoint at IEC60730_MARCHCX_STEP_RET
  #
  # @return True
  #
  def test_CorrectBackGround_StepRamClassB(self):
    self.adapter.halt()
    self.adapter.clear_all_breakpoints()
    self.adapter.reset()

    firstTime = True

    self.reach_to_breakpoint('IEC60730_VMC_BIST_START_BKPT', True, 1)
    self.adapter.clear_all_breakpoints()

    rtCheck_location = variables['rtCheck']
    rtCheck = self.adapter.memory_read32(rtCheck_location, 1)

    phaseSteps = []
    if is_enableMatchX :
      phaseSteps = ['IEC60730_MARCHCX_STEP_SAVE',
                    'IEC60730_MARCHCX_STEP_STEP1',
                    'IEC60730_MARCHCX_STEP_STEP2',
                    'IEC60730_MARCHCX_STEP_STEP5',
                    'IEC60730_MARCHCX_STEP_STEP6',
                    'IEC60730_VMC_BIST_MARCHC_STEP_BKPT']
    else :
      phaseSteps = ['IEC60730_MARCHCX_STEP_SAVE',
                    'IEC60730_MARCHCX_STEP_STEP1',
                    'IEC60730_MARCHCX_STEP_STEP2',
                    'IEC60730_MARCHCX_STEP_STEP3',
                    'IEC60730_MARCHCX_STEP_STEP4',
                    'IEC60730_MARCHCX_STEP_STEP5',
                    'IEC60730_MARCHCX_STEP_STEP6',
                    'IEC60730_VMC_BIST_MARCHC_STEP_BKPT']

    while rtCheck[0] < RAMTEST_END :
      logging.info("TC: rtCheck: " + hex(rtCheck[0]))
      for phase in phaseSteps :
        self.reach_to_breakpoint(phase, firstTime, 1)
      rtCheck = self.adapter.memory_read32(rtCheck_location, 1)
      firstTime = False

    self.adapter.clear_all_breakpoints()

    logging.info("Testing VMC the backup Buffer")
    phaseBuffs = []
    if is_enableMatchX :
      phaseBuffs = ['IEC60730_IMC_BIST_CHECKBKBUF_BKPT',
                    'IEC60730_MARCHCX_STEP_BUFF1',
                    'IEC60730_MARCHCX_STEP_BUFF2',
                    'IEC60730_MARCHCX_STEP_BUFF5',
                    'IEC60730_MARCHCX_STEP_BUFF6',
                    'IEC60730_MARCHCX_STEP_MARCH_RET',
                    'IEC60730_MARCHCX_STEP_RET']
    else :
      phaseBuffs = ['IEC60730_IMC_BIST_CHECKBKBUF_BKPT',
                    'IEC60730_MARCHCX_STEP_BUFF1',
                    'IEC60730_MARCHCX_STEP_BUFF2',
                    'IEC60730_MARCHCX_STEP_BUFF3',
                    'IEC60730_MARCHCX_STEP_BUFF4',
                    'IEC60730_MARCHCX_STEP_BUFF5',
                    'IEC60730_MARCHCX_STEP_BUFF6',
                    'IEC60730_MARCHCX_STEP_MARCH_RET',
                    'IEC60730_MARCHCX_STEP_RET']
    for phase in phaseBuffs :
      self.reach_to_breakpoint(phase, True, 1)

    return True

  @iec60730_test_case('TC: Detect corruption when testing Step Ram class B')
  ## Verify the DUT jump to #iec60730_SafeState when testing ram failed at
  # BIST. This TC simulates an abnormal situation that causes the variable rtCheck,
  # bkBuf to be changed. This leads to jump to break point at #iec60730_SafeState.
  #
  # In the VMC documentation there is a detailed description of the \ref rtCheck,
  # and \ref bkBuf variables.
  #
  # @details Order of execution
  # - Reset device
  #
  # - Verify code reaches breakpoint at IEC60730_VMC_BIST_START_BKPT
  #
  # - Verify code reaches breakpoint at IEC60730_MARCHCX_STEP_STEP2. We don't reach
  # IEC60730_MARCHCX_STEP_STEP1 because this step only write (W1)
  #   - Edit value at address of \ref rtCheck
  #   - Verify code reaches breakpoint at #iec60730_SafeState
  # - if not enable MatchX
  #   - Verify code reaches breakpoint at IEC60730_MARCHCX_STEP_STEP3
  #     - Edit value at address of \ref rtCheck
  #     - Verify code reaches breakpoint at #iec60730_SafeState
  #   - Verify code reaches breakpoint at IEC60730_MARCHCX_STEP_STEP4
  #     - Edit value at address of \ref rtCheck
  #     - Verify code reaches breakpoint at #iec60730_SafeState
  # - Verify code reaches breakpoint at IEC60730_MARCHCX_STEP_STEP5
  #   - Edit value at address of \ref rtCheck
  #   - Verify code reaches breakpoint at #iec60730_SafeState
  # - Verify code reaches breakpoint at IEC60730_MARCHCX_STEP_STEP6
  #   - Edit value at address of \ref rtCheck
  #   - Verify code reaches breakpoint at #iec60730_SafeState
  #
  # - Verify code reaches breakpoint at IEC60730_IMC_BIST_CHECKBKBUF_BKPT
  #
  # - Verify code reaches breakpoint at IEC60730_MARCHCX_STEP_BUFF2. We don't reach
  # IEC60730_MARCHCX_STEP_BUFF1 because this step only write (W1)
  #   - Edit value at address of \ref bkBuf
  #   - Verify code reaches breakpoint at #iec60730_SafeState
  # - if not enable MatchX
  #   - Verify code reaches breakpoint at IEC60730_MARCHCX_STEP_BUFF3
  #     - Edit value at address of \ref bkBuf
  #     - Verify code reaches breakpoint at #iec60730_SafeState
  #   - Verify code reaches breakpoint at IEC60730_MARCHCX_STEP_BUFF4
  #     - Edit value at address of \ref bkBuf
  #     - Verify code reaches breakpoint at #iec60730_SafeState
  # - Verify code reaches breakpoint at IEC60730_MARCHCX_STEP_BUFF6
  #   - Edit value at address of \ref bkBuf
  #   - Verify code reaches breakpoint at #iec60730_SafeState
  # - Verify code reaches breakpoint at IEC60730_MARCHCX_STEP_BUFF6
  #   - Edit value at address of \ref bkBuf
  #   - Verify code reaches breakpoint at #iec60730_SafeState
  #
  # @return True
  #
  def test_DetectCorruption_StepRamClassB(self):
    self.adapter.halt()
    self.adapter.clear_all_breakpoints()
    self.adapter.reset()

    self.reach_to_breakpoint('IEC60730_VMC_BIST_START_BKPT', True, 1)
    self.adapter.clear_all_breakpoints()

    rtCheck_location = variables['rtCheck']

    phaseSteps = []
    if is_enableMatchX :
      phaseSteps = ['IEC60730_MARCHCX_STEP_STEP2',
                    'IEC60730_MARCHCX_STEP_STEP5',
                    'IEC60730_MARCHCX_STEP_STEP6']
    else :
      phaseSteps = ['IEC60730_MARCHCX_STEP_STEP2',
                    'IEC60730_MARCHCX_STEP_STEP3',
                    'IEC60730_MARCHCX_STEP_STEP4',
                    'IEC60730_MARCHCX_STEP_STEP5',
                    'IEC60730_MARCHCX_STEP_STEP6']

    for phase in phaseSteps :
      self.corruption(address = rtCheck_location,
                      value = 0xA5A5A5A5,
                      time = 1,
                      label = phase,
                      label_pass = 'iec60730_SafeState')

    self.adapter.clear_all_breakpoints()
    self.adapter.reset()

    self.reach_to_breakpoint('IEC60730_IMC_BIST_CHECKBKBUF_BKPT', True, 1)
    self.adapter.clear_all_breakpoints()

    bkBuf_location = 0
    bkBuf_location = variables['bkBuf']

    phaseBuffs = []
    if is_enableMatchX :
      phaseBuffs = ['IEC60730_MARCHCX_STEP_BUFF2',
                    'IEC60730_MARCHCX_STEP_BUFF5',
                    'IEC60730_MARCHCX_STEP_BUFF6']
    else :
      phaseBuffs = ['IEC60730_MARCHCX_STEP_BUFF2',
                    'IEC60730_MARCHCX_STEP_BUFF3',
                    'IEC60730_MARCHCX_STEP_BUFF4',
                    'IEC60730_MARCHCX_STEP_BUFF5',
                    'IEC60730_MARCHCX_STEP_BUFF6']

    for phase in phaseBuffs :
      self.corruption(address = bkBuf_location,
                      value = 0xA5A5A5A5,
                      time = 1,
                      label = phase,
                      label_pass = 'iec60730_SafeState')

    return True

  @iec60730_test_case('TC: Stack Test work normally')
  ## Verify the DUT run to check RAM and not failed at BIST. This TC checks
  # under normal conditions with no exceptions, vmc module DOES NOT raise issue.
  #
  # @details Order of execution
  # - Reset device
  #
  # - Verify code reaches breakpoint at IEC60730_VMC_BIST_START_BKPT
  # - Verify code reaches breakpoint at IEC60730_VMC_BIST_STACK_TEST_OK_BKPT
  #
  # @return True
  #
  def test_WorkNormally_StackTest(self):
    self.adapter.halt()
    self.adapter.clear_all_breakpoints()
    self.adapter.reset()

    self.reach_to_breakpoint('IEC60730_VMC_BIST_START_BKPT', True, 1)
    self.adapter.clear_all_breakpoints()

    phaseBuffs = ['IEC60730_VMC_BIST_STACK_TEST_BKPT',
                  'IEC60730_VMC_BIST_STACK_TEST_OK_BKPT' ]

    for phase in phaseBuffs :
      self.reach_to_breakpoint(phase, True, 1)

    return True

  @iec60730_test_case('TC: Stack Test failed')
  ## Verify the DUT jump to #iec60730_SafeState when stack test failed at
  # BIST. This TC simulates an abnormal situation that causes the variable
  # \ref stackTestOverFlow to be changed. This leads to jump to break point at
  # #iec60730_SafeState.
  #
  # In the VMC documentation there is a detailed description of the variable
  # \ref stackTestOverFlow.
  #
  # @details Order of execution
  # - Reset device
  #
  # - Verify code reaches breakpoint at IEC60730_VMC_BIST_START_BKPT
  #   - Edit value at address of \ref stackTestOverFlow
  #   - Verify code reaches breakpoint at #iec60730_SafeState
  #
  # @return True
  #
  def test_DetectFailed_StackTest(self):
    self.adapter.halt()
    self.adapter.clear_all_breakpoints()
    self.adapter.reset()

    self.reach_to_breakpoint('IEC60730_VMC_BIST_START_BKPT', True, 1)
    self.adapter.clear_all_breakpoints()

    # Edit variable stackTestOverFlow
    stackTestOverFlow_location = 0
    stackTestOverFlow_location = variables['stackTestOverFlow']

    for i in range(4):
      stackTestOverFlow = self.adapter.memory_read32(stackTestOverFlow_location + 4 * i, 1)
      logging.info("DUT stackTestOverFlow[" + str(i) + "]=" + hex(stackTestOverFlow[0]))
      self.corruption(address = stackTestOverFlow_location + 4 * i,
                      value = 0x00000000,
                      time = 1,
                      label = 'IEC60730_VMC_BIST_STACK_TEST_BKPT',
                      label_pass = 'iec60730_SafeState')

    return True

if __name__ == "__main__":
  chip_name = os.getenv('CHIP')
  app_type = os.getenv('APP_TYPE')
  lst_file_path = os.getenv('LST_PATH')
  adapter_serial_no = os.getenv('ADAPTER_SN')
  lib_path = os.getenv('JLINK_PATH')

  while len(sys.argv) > 1:
    line = sys.argv.pop()
    if "N_MARCHX=1" in line:
      is_enableMatchX = False
    if "NON_SECURE_EN=true" in line:
      is_nonSecure = True
    if len(sys.argv) == 1:
      compiler = line

  if is_nonSecure:
    RAMTEST_END = 0x2000C080

  unittest.main()

## @}
# @}
