# Guideline for running unit test

## Manually run unit tests

CMake config

```sh
$ make prepare
$ cd build
$ cmake --toolchain ../cmake/toolchain.cmake .. -DENABLE_UNIT_TESTING=ON -DBOARD_NAME=brd4187c
```

CMake Build

```sh
$ cmake --build . --target unit_test_info -j4
```

or

```sh
$ make unit_test_info -j4
```

## Automatically run unit tests

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

If you want to calculate from start address to end address of flash:

```sh
$ export SDK_PATH=~/SimplicityStudio/SDKs/gecko_sdk
$ export TOOL_DIRS=~/Downloads/SimplicityStudio_v5/developer/toolchains/gnu_arm/12.2.rel1_2023.7/bin
$ export TOOL_CHAINS=GCC
$ export FLASH_REGIONS_TEST=0x8000000
```

or if you want to calculate multiple regions:

```sh
$ export FLASH_REGIONS_TEST="0x8000000 0x8000050 0x80000a0 0x80000f0 0x8000140 0x8000190"
```

> [!NOTE]
> In the current unit test file, only enable computation one region: from the FLASH_REGIONS_TEST address of ​​the flash to the end of the flash. Therefore, just export the flash's starting address. For example, chip EFR32MG24:
>> $ export FLASH_REGIONS_TEST=0x8000000

### Example

```sh
bash execute_unit_test.sh brd4187c all all 440111030 GCC
```

## CRC calculation options

When running build cmake to run unit tests and integration tests for invariable memory modules, the crc calculation image file will have the suffix _crc16 or _crc32, you must flash the image file with this suffix.

With the commands above, the default value supports calculation CRC-16. If you want to change to calculate for CRC-32 bits, use the CMake config command below:

- With unit test:

```sh
$ cmake --toolchain ../cmake/toolchain.cmake .. -DENABLE_UNIT_TESTING=ON -DBOARD_NAME=brd4187c -DENABLE_CAL_CRC_32=ON
```

- or with integration test:

```sh
$ cmake --toolchain ../cmake/toolchain.cmake .. -DENABLE_INTEGRATION_TESTING=ON -DBOARD_NAME=brd4187c -DENABLE_CAL_CRC_32=ON
```

Here is some options to support running tests of invariable memory modules:
- ENABLE_CAL_CRC_32
- ENABLE_CRC_USE_SW (if this option ON, you can enable option: ENABLE_SW_CRC_TABLE)

> [!NOTE]
> Only use ENABLE_SW_CRC_TABLE option when the ENABLE_CRC_USE_SW option is ON, otherwise an error will be reported during the build process.