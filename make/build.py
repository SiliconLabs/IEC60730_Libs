from os import system as cmd

dev = "make DEVICE:=efr32mg21"
try:
    print("Start building...\n")
    cmd('make clean_all')
    cmd(dev)
    print("Build completed.\n")
except:
    print("Error occurred.")
