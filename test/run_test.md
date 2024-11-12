# Guideline for running auto test using bash script

## Support run unit test

Command run

```sh
bash execute_test.sh $1 $2 $3 $4 $5 $6
```

With the input arguments, there is the following information

- $1: BOARD_NAME: brd4187c
- $2: task: all, gen-only, run-only
- $3: components: all, unit_test_iec60730_bist, unit_test_iec60730_post, ...
- $4: ADAPTER_SN
- $5: compiler: GCC, IAR
- $6: OPTION_SUPPORT_UNIT_TEST: "-DENABLE_CAL_CRC_32=ON -DENABLE_CRC_USE_SW"

In which: Components list that supports unit testing includes:
- unit_test_iec60730_post
- unit_test_iec60730_bist
- unit_test_iec60730_program_counter
- unit_test_iec60730_safety_check
- unit_test_iec60730_irq
- unit_test_iec60730_system_clock
- unit_test_iec60730_watchdog
- unit_test_iec60730_cpu_registers
- unit_test_iec60730_variable_memory
- unit_test_iec60730_invariable_memory

Before running the bash file, you need to install Jlink, Srecord and slc tool, refer [README.md](../README.md) to set up some environment variables as follows:
If the compiler is GCC
- If the compiler is GCC:

```sh
$ export SDK_PATH=~/SimplicityStudio/SDKs/gecko_sdk
$ export ARM_GCC_DIR=~/Downloads/SimplicityStudio_v5/developer/toolchains/gnu_arm/12.2.rel1_2023.7
$ export TOOL_CHAINS=GCC
$ export START_ADDR_FLASH=0x8000000
$ export JLINK_PATH=/opt/SEGGER/JLink/libjlinkarm.so
```

### Example

```sh
bash execute_unit_test.sh brd4187c all all 440111030 GCC
```

### Note:
In case you want to build CRC32 run this command. For example

```sh
bash execute_unit_test.sh brd4187c all all 440111030 GCC "-DENABLE_CAL_CRC_32=ON"
```