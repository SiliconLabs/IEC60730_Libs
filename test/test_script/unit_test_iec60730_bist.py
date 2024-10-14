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

from binascii import hexlify
import random
import os
import sys
from time import sleep

from iec60730_get_report_unit_test import *
from iec60730_test_base import *
import jlink, jlink_constants
import unittest
import enums

def int_to_bytes(number: int) -> bytes:
    return number.to_bytes(length=(8 + (number + (number < 0)).bit_length()) // 8, byteorder='big', signed=True)


##  IEC60730 get unit test result
#
# @details This class runs IEC60730 get unit test results
#
# Hardware setup:
#   Connect DUT to PC. No additional hardware setup required.

class iec60730_unit_test_result(unittest.TestCase, iec60730TestBase):

  def get_unit_test_result(self):
    def get_result(self):
      self.adapter.halt()
      self.adapter.clear_all_breakpoints()

      self.adapter.set_breakpoint(address = asm_labels['IEC60730_UNIT_TEST_END'],
                                  typeflags=enums.JLinkBreakpoint.ANY)

      self.adapter.reset()
      pc = self.adapter.run_to_breakpoint(3)
      logging.info("Halted at label: " + self.get_label(pc))
      self.assertEqual(pc, asm_labels['IEC60730_UNIT_TEST_END'],\
                      "DUT failed to stop at IEC60730_UNIT_TEST_END" \
                      " , pc = " + hex(pc))
      #logging.info("Halted at label: " + self.get_label(pc))
      current_test_numth = variables['current_test_numth']
      self.assertNotEqual(0, current_test_numth,\
                        "Can not read current_test_numth address")
      reg = self.adapter.memory_read8(current_test_numth, 1, zone=None)

      current_test_numth = variables['current_test_numth']
      self.assertNotEqual(0, current_test_numth,\
                      "Can not read current_test_numth address")
      current_test_numth = self.adapter.memory_read8(current_test_numth, 1, zone=None)

      test_case_result = variables['test_case_result']
      self.assertNotEqual(0, test_case_result,\
                     "Can not read test_case_result address")
      result = self.adapter.memory_read(test_case_result,current_test_numth[0])
      return result
    def connect_device(self):
      self.pre_exec_test()
      logging.info("----------------- Start get unit test result")
      result = get_result(self)
      logging.info("Get unit test result: Done. See unit_test_report.log")
      logging.info("----------------- End get unit test result")
      self.post_exec_test()
      file_test_case = "../unit_test/src/unit_test_iec60730_bist.c"
      log_report = '../../log/unit_test_iec60730_bist.log'
      get_report_unit_test(result,file_test_case,log_report)
    return connect_device(self)

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
  
  iec60730_unit_test_result = iec60730_unit_test_result()
  iec60730_unit_test_result.env_setup(adapter_serial_no,
                                    chip_name,
                                    lst_file_path,
                                    lib_path,
                                    app_type,
                                    compiler)
  iec60730_unit_test_result.get_unit_test_result()

## @}
# @}
