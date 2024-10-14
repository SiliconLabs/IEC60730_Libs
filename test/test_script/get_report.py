from util import PyTestSuites
import os
if __name__ == "__main__":
  logFilePath = os.path.dirname(os.path.realpath(__file__)) + '/../../log/log.txt'
  fileHdl = open(logFilePath, 'r')
  log = fileHdl.read()
  testClass = "IEC"
  pyTest = PyTestSuites()
  for line in log.splitlines():
    # print ("line: ",line)
    if "Start run test:" in line:
      testName=line.split()[-1]
      # print ("testName: ",testName)
      pyTest.insert_test_case(testName, testClass)
    if ("Finish run test:" in line) and (testName in line):
      result=line.split()[-1]
      # print ("result: ",result)
      pyTest.assume(result == "PASS")
      pyTest.complete_test_case()
  pyTest.close_test_suite()