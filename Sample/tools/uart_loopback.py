#!/usr/bin/python

import serial
import sys, getopt
import time

def printUsage(prg) :
  print("\nUsage: " + prg + " [Options]\n")
  print("Options: -p <port>  (uart port)")
  print("         -b <baud>  (uart baud rate)")
  print("         -?         (show this help)")
  print("\nExample:")
  print("uart_loopback -p /dev/ttyACM0\n")
  sys.exit(1)

def main(argv) :
  baud = 115200
  tty = "/dev/ttyACM0"

  try:
    opts, args = getopt.getopt(argv, "p:b:?")
  except getopt.GetoptError as err:
    print(repr(err))
    sys.exit(1)

  for opt, arg in opts:
    if opt == '-?':
      printUsage(sys.argv[0])
    elif opt == "-b":
      baud = arg
    elif opt == "-p":
      tty = arg

  print("Uart port used: " + tty + " baud: " + "{}".format(baud))

  ser = serial.Serial(
                    port=tty, \
                    baudrate=baud, \
                    parity=serial.PARITY_NONE, \
                    stopbits=serial.STOPBITS_ONE, \
                    bytesize=serial.EIGHTBITS, \
                    timeout=0, \
                    write_timeout=0)

  while True :
    if ser.inWaiting() > 0 :
      byteReads = ser.read(ser.inWaiting())
      ser.write(byteReads)
      for b in byteReads :
        print("{" + "{:02X}".format(b) + "}", end ='', flush=True)

if __name__ == "__main__":
  main(sys.argv[1:])