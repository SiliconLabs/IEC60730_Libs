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
# @defgroup IEC60730_INVARIABLE_MEMORY_VERIFICATION Invariable Memory Automated Verification Tests
# @{
# Python script for the IEC60730 Invariable Memory plausibility verification tests.
#
# For details on the tests, see iec60730_invariable_memory.iec60730_invariable_memory.
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

is_crc32 = False

##  IEC60730 Invariable Memory Plausibility Verification Tests
#
# @details This class runs IEC60730 verification tests for the invariable memory plausibility test.
#
# Hardware setup:
#   Connect DUT to PC. No additional hardware setup required.
class iec60730_imc(unittest.TestCase, iec60730TestBase):
  TEST_SUITE_NAME = "IMC"

  def setUp(self):
    self.env_setup(adapter_serial_no, chip_name, lst_file_path, lib_path, compiler)

  def set_breakpoint(self, label) :
    self.adapter.set_breakpoint(address = asm_labels[label],
                                typeflags=enums.JLinkBreakpoint.ANY)

  def reach_to_breakpoint(self, label, setbkp, time) :
    if setbkp :
      self.set_breakpoint(label)

    pc = self.adapter.run_to_breakpoint(time)
    self.assertEqual(pc, asm_labels[label], \
                    "DUT failed to stop at " + label + \
                    ", pc = " + hex(pc) + \
                    ", setbkp = " + str(setbkp))

  @iec60730_test_case('TC: Calculate CRC for the entire flash memory')
  ## Verify the DUT calculation of CRC value at POST. This  test case (TC) checks
  # under normal conditions with no exceptions, firmware will calculate the CRC
  # of the entire flash, the calculated value SHOULD be equal to the calculated
  # value stored in the flash.
  #
  # @details Order of execution
  # - Reset device
  # - Verify code reachs breakpoint at IEC60730_IMC_POST_START_BKPT
  # - Verify code reachs breakpoint at IEC60730_IMC_POST_REFCRC_BKPT
  # - Verify code reachs breakpoint at IEC60730_IMC_POST_END_BKPT
  #
  # @return True
  #
  def test_CalCRC_Full_Memory(self):
    self.adapter.halt()
    self.adapter.clear_all_breakpoints()

    # Reset device & run to break point
    self.adapter.reset()

    # reach to break point IEC60730_IMC_POST_START_BKPT
    self.reach_to_breakpoint('IEC60730_IMC_POST_START_BKPT', True, 1)

    # Verify initial value of refCrc
    refCrc_location = variables['refCrc']
    if is_crc32 :
      refCrc = self.adapter.memory_read32(refCrc_location, 1)
    else :
      refCrc = self.adapter.memory_read16(refCrc_location, 1)

    # Debug
    logging.info("DUT refCrc=" + hex(refCrc[0]) + " at " + hex(refCrc_location))

    if 0 != refCrc[0] :
      logging.info("DUT value of refCrc not equal 0")
      return False

    # reach to break point IEC60730_IMC_POST_REFCRC_BKPT
    self.reach_to_breakpoint('IEC60730_IMC_POST_REFCRC_BKPT', True, 1)

    # print value of refCrc
    if is_crc32 :
      refCrc = self.adapter.memory_read32(refCrc_location, 1)
    else :
      refCrc = self.adapter.memory_read16(refCrc_location, 1)

    # Debug
    logging.info("DUT refCrc=" + hex(refCrc[0]))

    # clear all break point
    self.adapter.clear_all_breakpoints()

    # reach to break point IEC60730_IMC_POST_END_BKPT
    self.reach_to_breakpoint('IEC60730_IMC_POST_END_BKPT', True, 1)

    return True

  @iec60730_test_case('TC: Corrupt CRC for the entire flash memory')
  ## Verify the DUT jump to #iec60730_SafeState when flash faied at POST.
  # This TC simulates an abnormal situation that causes the variable \ref refCrc
  # to be changed, resulting in the calculated CRC value for the entire flash
  # being different from the value stored in the flash. This leads to jump to
  # break point at #iec60730_SafeState.
  #
  # In the IMC documentation there is a detailed description of the variable
  # \ref refCrc.
  #
  # @details Order of execution
  # - Reset device
  # - Verify code reachs breakpoint at IEC60730_IMC_POST_START_BKPT
  # - Verify code reachs breakpoint at IEC60730_IMC_POST_REFCRC_BKPT
  #   - Edit value of \ref refCrc variable
  #   - Verify execution breaks at #iec60730_SafeState()
  #
  # @return True
  #
  def test_CorruptCRC_Full_Memory(self):
    self.adapter.halt()
    self.adapter.clear_all_breakpoints()

    # Reset device & jump to break point
    self.adapter.reset()

    # reach to break point IEC60730_IMC_POST_START_BKPT
    self.reach_to_breakpoint('IEC60730_IMC_POST_START_BKPT', True, 1)

    # reach to break point IEC60730_IMC_POST_START_BKPT
    self.reach_to_breakpoint('IEC60730_IMC_POST_REFCRC_BKPT', True, 1)

    # Set refCrc to {0x0000}
    refCrc_location = variables['refCrc']
    if is_crc32 :
      self.adapter.memory_write32(refCrc_location, data = {0x00000000})
    else :
      self.adapter.memory_write16(refCrc_location, data = {0x0000})

    # Debug
    logging.info("DUT refCrc at " + hex(refCrc_location))

    # Set break point at iec60730_SafeState
    self.adapter.clear_all_breakpoints()

    # reach to break point iec60730_SafeState
    self.reach_to_breakpoint('iec60730_SafeState', True, 1)

    return True

  @iec60730_test_case('TC: Calculate CRC for the Block flash memory')
  ## Verify the DUT calculation of CRC value at BIST. This TC checks under normal
  # conditions with no exceptions, firmware will calculate the CRC values for each
  # step of BIST and accumulate these values. Finally, the calculated CRC value
  # SHOULD be equal to the value stored in the flash.
  #
  # @details Order of execution
  # - Reset device
  # - Verify code reachs breakpoint at IEC60730_IMC_BIST_CRCBLOCK_BKPT
  # - Loop with IEC60730_IMC_BIST_CALCRC_BKPT
  # - Verify code reachs breakpoint at IEC60730_IMC_BIST_END_BKPT (success)
  #
  # @return True
  #
  def test_CalCRC_Block_Memory(self):
    self.adapter.halt()
    self.adapter.clear_all_breakpoints()
    self.adapter.reset()

    firstTime = True

    # Reset device & jump to break point
    self.reach_to_breakpoint('IEC60730_IMC_BIST_START_BKPT', True, 1)
    self.adapter.clear_all_breakpoints()

    runCrc_location = variables['runCrc']
    runCrc = self.adapter.memory_read32(runCrc_location, 1)

    ROM_END_location = variables['__checksum']

    # Debug
    logging.info("DUT runCrc at " + hex(runCrc_location) + " __checksum at " + hex(ROM_END_location))

    while runCrc[0] < ROM_END_location :
      # logging.info("TC: runCrc: " + hex(runCrc[0]) + " < ROM_END: " + hex(ROM_END_location))
      self.reach_to_breakpoint('IEC60730_IMC_BIST_CRCBLOCK_BKPT', firstTime, 1)
      runCrc = self.adapter.memory_read32(runCrc_location, 1)
      firstTime = False

    self.adapter.clear_all_breakpoints()

    self.reach_to_breakpoint('IEC60730_IMC_BIST_CALCRC_BKPT', True, 1)

    # Verify initial value of crcCrc
    curCrc_location = variables['curCrc']
    if is_crc32 :
      curCrc = self.adapter.memory_read32(curCrc_location, 1)
    else :
      curCrc = self.adapter.memory_read16(curCrc_location, 1)

    # Debug
    logging.info("DUT curCrc=" + hex(curCrc[0]) + " at " + hex(curCrc_location))

    if 0 == curCrc[0] :
      logging.info("DUT value of curCrc equal 0")
      return False

    self.adapter.clear_all_breakpoints()
    self.reach_to_breakpoint('IEC60730_IMC_BIST_END_BKPT', True, 1)

    return True

  @iec60730_test_case('TC: Corrupt CRC at step calculate CRC for the Block flash memory')
  ## Verify the DUT jump to #iec60730_SafeState when flash faied at BIST.
  # This TC simulates an abnormal situation that causes the variable \ref curCrc
  # to be changed, resulting in the calculated CRC value for the entire flash
  # being different from the value stored in the flash. This leads to jump to
  # break point at #iec60730_SafeState.
  #
  # In the IMC documentation there is a detailed description of the variable
  # \ref curCrc.
  #
  # @details Order of execution
  # - Reset device
  # - Verify code reachs breakpoint at IEC60730_IMC_BIST_CALCRC_BKPT
  #   - Edit value of \ref curCrc
  #   - Verify execution breaks at #iec60730_SafeState()
  #
  # @return True
  #
  def test_CorruptCRC_CalCRC_Block_Memory(self):
    self.adapter.halt()
    self.adapter.clear_all_breakpoints()

    # Reset device & jump to break point
    self.adapter.reset()

    # reach to break point IEC60730_IMC_BIST_CALCRC_BKPT
    self.reach_to_breakpoint('IEC60730_IMC_BIST_CALCRC_BKPT', True, 1)

    # Verify initial value of crcCrc
    curCrc_location = variables['curCrc']
    if is_crc32 :
      curCrc = self.adapter.memory_read32(curCrc_location, 1)
    else :
      curCrc = self.adapter.memory_read16(curCrc_location, 1)
    logging.info("DUT curCrc=" + hex(curCrc[0]) + " at " + hex(curCrc_location))

    # Set refCrc to {0x0000}
    refCrc_location = variables['refCrc']
    logging.info("DUT refCrc at " + hex(refCrc_location))

    if is_crc32 :
      self.adapter.memory_write16(refCrc_location, data = {0x00000000})
    else :
      self.adapter.memory_write16(refCrc_location, data = {0x0000})

    # Set break point at iec60730_SafeState
    self.adapter.clear_all_breakpoints()

    # reach to break point iec60730_SafeState
    self.reach_to_breakpoint('iec60730_SafeState', True, 1)

    return True

  @iec60730_test_case('TC: Corrupt integrity of runCrc variable for the Block flash memory')
  ## Verify integrity of \ref runCrc variable. This TC simulates an abnormal
  # situation that causes the variable runCrc to be changed, resulting in the
  # calculated CRC value for the entire flash being different from the value stored
  # in the flash. This leads to jump to break point at #iec60730_SafeState.
  #
  # In the IMC documentation there is a detailed description of the variable
  # \ref runCrc.
  #
  # @details Order of execution
  # - Reset device
  # - Verify code reachs breakpoint at IEC60730_IMC_BIST_CRCBLOCK_BKPT
  #   - Edit value of \ref runCrc variable
  #   - Verify execution breaks at #iec60730_SafeState()
  #
  # @return True
  #
  def test_CorruptIntegrity_RunCRC_Block_Memory(self):
    self.adapter.halt()
    self.adapter.clear_all_breakpoints()

    # Reset device & jump to break point
    self.adapter.reset()

    # reach to break point IEC60730_IMC_BIST_CRCBLOCK_BKPT
    self.reach_to_breakpoint('IEC60730_IMC_BIST_CRCBLOCK_BKPT', True, 1)

    runCrc_location = variables['runCrc']
    logging.info("DUT runCrc at " + hex(runCrc_location))

    if is_crc32 :
      self.adapter.memory_write16(runCrc_location, data = {0x00000000})
    else :
      self.adapter.memory_write16(runCrc_location, data = {0x0000})

    # reach to break point iec60730_SafeState
    self.reach_to_breakpoint('iec60730_SafeState', True, 1)

    return True


if __name__ == "__main__":
  chip_name = os.getenv('CHIP')
  lst_file_path = os.getenv('LST_PATH')
  adapter_serial_no = os.getenv('ADAPTER_SN')
  lib_path = os.getenv('JLINK_PATH')

  while len(sys.argv) > 1:
    line = sys.argv.pop()
    if "CRC_32=1" in line:
      is_crc32 = True
    if len(sys.argv) == 1:
      compiler = line

  unittest.main()

## @}
# @}