# Guideline for running integration test

## Manually run integration tests

CMake config

```sh
$ make prepare
$ cd build
$ cmake --toolchain ../cmake/toolchain.cmake .. -DENABLE_INTEGRATION_TESTING=ON -DBOARD_NAME=brd4187c
```

CMake Build

```sh
$ cmake --build . --target integration_test_info -j4
```

or

```sh
$ make integration_test_info -j4
```

To support running integration tests for the watchdog module, there are 2 options when running when running CMake config:
- TEST_SECURE_PERIPHERALS_ENABLE: enable test secure peripherals

- INTEGRATION_TEST_WDOG1_ENABLE: enable watchdog 1 to test if device supports

To support running integration tests for the variable memory module, there are 1 options when running when running CMake config:
- INTEGRATION_TEST_USE_MARCHX_DISABLE: disable using MarchXC algorithm

By default when testing variable memory module, enable using MarchXC algorithm. For example:

```sh
$ cmake --toolchain ../cmake/toolchain.cmake .. -DENABLE_INTEGRATION_TESTING=ON -DINTEGRATION_TEST_USE_MARCHX_DISABLE=ON -DBOARD_NAME=brd4187c
```

For devices that have Trust zone implemented, secure and non-secure peripherals need to test.
Default enable checks non-secure peripherals. To check secure peripherals enable this option when run CMake config: TEST_SECURE_PERIPHERALS_ENABLE. For example:

```sh
$ cmake --toolchain ../cmake/toolchain.cmake .. -DENABLE_INTEGRATION_TESTING=ON -DTEST_SECURE_PERIPHERALS_ENABLE=ON -DBOARD_NAME=brd4187c
```

For devices that support 2 watchdogs, if you want to test both watchdogs, enable option INTEGRATION_TEST_WDOG1_ENABLE to ON when run Cmake config:

```sh
$ cmake --toolchain ../cmake/toolchain.cmake .. -DENABLE_INTEGRATION_TESTING=ON -DINTEGRATION_TEST_WDOG1_ENABLE=ON -DBOARD_NAME=brd4187c
```

To run integration tests for the watchdog module you need to connect the device to ethernet. Export CHIP, ADAPTER_SN, LST_PATH, JLINK_PATH and the device's IP address and run test script, for example:

```sh
$ export CHIP=EFR32MG24BXXXF1536 ADAPTER_SN=440111030
$ export LST_PATH=~/devs_safety_lib/build/test/integration_test/build/brd4187c/integration_test_iec60730_watchdog/S
```

if test secure peripherals or for non-secure peripherals:

```sh
$ export LST_PATH=~/devs_safety_lib/build/test/integration_test/build/brd4187c/integration_test_iec60730_watchdog/NS
```

```sh
$ export JLINK_PATH=/opt/SEGGER/JLink/libjlinkarm.so
$ export HOST_IP=192.168.1.69
```

```sh
$ python3 integration_test_iec60730_irq.py GCC
```

By default device enable watchdog 0 and test watchdog 0. If you want to test wachdog 1 using this command:

```sh
$ INTEGRATION_TEST_WDOG1_ENABLE=enable python3 integration_test_iec60730_watchdog.py GCC
```

If you want to test variable memory module with disable using MarchXC algorithm:

```sh
$ INTEGRATION_TEST_USE_MARCHX_DISABLE=disable python3 integration_test_iec60730_variable_memory.py GCC
```

If you want to test invariable memory module with calculate crc32:

```sh
$ INTEGRATION_TEST_ENABLE_CAL_CRC_32=enable python3 integration_test_iec60730_variable_memory.py GCC
```

## Automatically run integration tests

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
- $6: OPTION_SUPPORT_INTEGRATION_TEST: "-DENABLE_CAL_CRC_32=ON -DENABLE_CRC_USE_SW=ON -DTEST_SECURE_PERIPHERALS_ENABLE=ON -DINTEGRATION_TEST_WDOG1_ENABLE=ON - INTEGRATION_TEST_USE_MARCHX_DISABLE=ON"

In which: Components list that support testing includes:
- integration_test_iec60730_program_counter
- integration_test_iec60730_irq
- integration_test_iec60730_system_clock
- integration_test_iec60730_watchdog
- integration_test_iec60730_cpu_registers
- integration_test_iec60730_variable_memory
- integration_test_iec60730_invariable_memory

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
> In the current integration test file, only enable computation one region: from the FLASH_REGIONS_TEST address of ​​the flash to the end of the flash. Therefore, just export the flash's starting address. For example, chip EFR32MG24:
>> $ export FLASH_REGIONS_TEST=0x8000000

### Example

```sh
bash execute_integration_test.sh brd4187c all all 440111030 GCC
```

### Note:
In case you want to build CRC32 run this command. For example:

```sh
bash execute_integration_test.sh brd4187c all all 440111030 GCC "-DENABLE_CAL_CRC_32=ON"
```

Or case you want to enable test secure peripherals run this command. For example:

```sh
bash execute_integration_test.sh brd4187c all all 440111030 GCC "-DTEST_SECURE_PERIPHERALS_ENABLE=ON -DINTEGRATION_TEST_WDOG1_ENABLE=ON -DINTEGRATION_TEST_USE_MARCHX_DISABLE=ON -DENABLE_CAL_CRC_32=ON"
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