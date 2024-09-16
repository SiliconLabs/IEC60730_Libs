import re
import logging

list_test_case = []
file_test_case = "../unit_test/src/test_iec60730_module_demo.c"
unity_begin_row = 0
unity_end_row = 0
log_report = '../../log/unit_test_report.log'

def get_unity_begin_file(files,logger):
  with open(files, 'r') as fp:
  # read all lines using readline()
    lines = fp.readlines()
    for row in lines:
      # check if string present on a current line
      word = 'UnityBegin'
      if row.find(word) != -1:
        res = re.findall(r'\(.*?\)', row)
        file_test = str(res[0])
        file_test =file_test.replace('(','').replace(')','').replace('"','')  
        # printing result
        logger.info("File test case: " + file_test)  
        return file_test, lines.index(row)

def get_unity_end_file(files):
  with open(files, 'r') as fp:
  # read all lines using readline()
    lines = fp.readlines()
    for row in lines:
      # check if string present on a current line
      word = 'UnityEnd'
      if row.find(word) != -1:
        return lines.index(row)

def get_test_case(files,logger,start,end):
  with open(files, 'r') as fp:
  # read all lines using readline()
    lines = fp.readlines()
   
    for row in lines:
      # check if string present on a current line
      word = 'run_test'
      if (row.find(word) != -1) and (start < lines.index(row)) \
      and (end > lines.index(row)):
        res = re.findall(r'\(.*?\)', row)
        test_case = str(res[0])
        test_case = test_case.replace('(','').replace(')','').replace('"','')  
        # printing result
        list_test_case.append(test_case)
    return list_test_case
        
def get_report_unit_test(result,file_test_case,log_report):
  test_fail = 0
  
  # Remove all handlers associated with the root logger object.
  for handler in logging.root.handlers[:]:
    logging.root.removeHandler(handler)
  logging.basicConfig(filename=log_report,
                    format='%(asctime)s %(message)s',
                    filemode='w')
  logger = logging.getLogger(log_report)
  logger.setLevel(logging.DEBUG)

  file_test, unity_begin_row = get_unity_begin_file(file_test_case,logger)
  unity_end_row = get_unity_end_file(file_test_case)
  list_test_case = get_test_case(file_test_case,logger,unity_begin_row,unity_end_row)

  if len(list_test_case) != len(result):
    raise ValueError("The list of test cases " + str(len(list_test_case)) + " in the file" 
                    + file_test + "is not equal " + str(len(result)) + " test cases"
                    "results received from device")
  
  for test_case in list_test_case:
    index = list_test_case.index(test_case)
    test_case = test_case.split(',',3)
    if result[index] == 0:
      logger.info(file_test + ":" + test_case[2] + ":" + test_case[0] + ":PASS")
    else:
      test_fail +=1
      logger.info(file_test + ":" + test_case[2] + ":" + test_case[0] + ":FAIL") 
  logger.info("\n----------------------------------------------------------------------\n") 
  logger.info(str(len(list_test_case)) + " Tests " + str(test_fail) + " Failures ") 
  if test_fail != 0:
    logger.info("FAIL") 
  else: 
    logger.info("PASS") 

