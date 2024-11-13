# IEC60730_Libs
Platform codes for EFR32 series chips which complies to IEC60730 safety standard

## Introduction
The IEC60730 library for EFR32 provides a basic implementation required to support the necessary requirements found in Table H.1 in the IEC60730 specification. It includes all the Power On Self Test (POST) functions executed when a device is first powered on, as well as Built In Self Test (BIST) functions that are called periodically to ensure correct operation. Certain portions of the requirements require a detailed understanding of the system under development. Callback functions must be completed by the developer to guarantee meeting the full specification. These include a Safe State function used when validation detects an anomaly, properly implemented communications channels (redundancy, error detection, periodic communications), and Plausibility functions to validate system state (internal variables and inputs/outputs).

## License
Please refer LICENSE.md.

## Release Notes
Please refer document in Doc/html.

## IEC60730 Certificate
The Silicon Labs Appliances homepage will contain the final certificate and detailed report when it is completed.

## OEM Testing
Once OEMs have completed integrating their system with the IEC60730 Library, they will need to certify their device with a qualified certification house.

## Supported Families
This library supports all EFR32 devices listed in Doc/html.

## Software Requirements
The IEC 60730 library dependencies:
- CMSIS package.
- Silicon Labs Devices header files. They are available in the Gecko SDK suite (platform).

Currently tested on Windows and Linux platforms.

## Building the IEC60730 Demo
To use Simplicity Studio to generate and build a demo IEC60730 and OEM Customization, refer to the IEC60730 Safety Library Integration Manual in the Doc folder for more details.

## Generate document
Using Doxygen to generate HTML documentation, the documents will be generated in `Doc/html/EFR32_ICE60730_Libraries`

```sh
$ sudo apt-get install doxygen
$ doxygen qat.doxygen
```

## Coding convention tool

### Features

- Automatically fixes end-of-file issues.
- Removes trailing whitespace from lines.
- Identifies and suggests fixes for common spelling errors using codespell.
- Formats code according to specified clang-format rules base on Silabs's coding standard.
- Checks code for potential errors and style issues using cppcheck.

### Installation

```sh
$ pip install pre-commit
$ sudo apt install clang-format clang-tidy cppcheck
```

### Run

```sh
$ pre-commit install
$ pre-commit run --all-files
```

## Compiler specifications
**The C compilers:**
- GNU GCC V12.2
- IAR EW for ARM V9.2

## Tools specification

Test frame work tools:
- Python V3.11

Simplicity Studio Commander
- Simplicity Commander version 1v16p8b1613

Support check coding convention by pre-commit
- pre-commit 3.5.0
- clang-format version 19.0.0
- Cppcheck 1.90

Support CMake
- CMake version >=3.25

SEGGER JLink
- JLink version 17.0.11

SLC-CLI
- slc version 5.9.1.1

Source code control:
- GIT V2.39
- JIRA V8.22.2

## System Architecture
This library has two primary components. The POST component is run immediately after power on, validating system state before entering the main execution loop.

The BIST component is run periodically in the
main execution loop.

Validation for IEC 60730 also requires external communications validation. Every OEM application has unique external communications requirements. This library provides an example UART communications library that meets IEC 60730 requirements. OEMs must adapt their communications to IEC60730 requirements.

This EFR32 IEC60730 library fulfills the requirements for a **Class B** device.

**For more details, please refer document in Doc/html.**

## Step run CMake

### Install Dependencies

#### Install slc-cli

- Follow this link to Install slc: [Install slc](https://docs.silabs.com/simplicity-studio-5-users-guide/latest/ss-5-users-guide-tools-slc-cli/02-installation)
- Follow this link to [Install Amazon Corretto 17 on Debian-Based Linux](https://docs.aws.amazon.com/corretto/latest/corretto-17-ug/downloads-list.html)

##### How to use slc

Add the path to the expanded slc-cli to your PATH sh export PATH=$PATH:~/SimplicityStudio/slc_cli_linux/slc_cli/

Configure SDK. For example sh slc configuration --sdk ~/SimplicityStudio/SDKs/gecko_sdk/

Run slc signature trust --sdk <path_to_the_gecko_sdk> if you have not yet trusted your SDK.

For example your SDK locate at ~/SimplicityStudio/SDKs/gecko_sdk/ sh slc signature trust --sdk ~/SimplicityStudio/SDKs/gecko_sdk/

Set toolchain For example sh slc configuration -gcc=~/SimplicityStudio-5/SimplicityStudio_v5/developer/toolchains/gnu_arm/10.3_2021.10/

Generate the project sh slc generate \path\to\example.slcp -np -d <project_destination> -name=<new_name> --with <board_or_device_that_supports_project>

Choose one of the options below to generate the project

| Operation | Arguments | Description |
|---|---|---|
|generate | -cp, --copy-sources | Copies all files referenced by this project, selected components, and any other running tools (Pin Tool, etc.). By default, no files are copied. |
|^ | -cpproj, --copy-proj-sources | Copies all files referenced by the project and links any SDK sources. This can be combined with -cpsdk. |
|^ | -cpsdk, --copy-sdk-sources | Copies all files referenced by the selected components and links any project sources. This can be combined with -cpproj. |

##### For example

```sh
$ GSDK=~/SimplicityStudio/SDKs/gecko_sdk
$ slc configuration --sdk=$GSDK --gcc-toolchain=/Applications/ARM
$ slc generate $GSDK/app/common/example/blink_baremetal -np -d blinky -name=blinky -o makefile
   --with brd4166a
```

### Export Variable

Export SDK_PATH=<path_to_sdk>, ARM_GCC_DIR=<path_to_toolchain>, TOOL_CHAINS and FLASH_REGIONS_TEST (flash start address support calculate crc for module invariable memory) before run config CMake.

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

with FLASH_REGIONS_TEST=0x8000000 is flash start address of board name brd4187c (chip EFR32MG24)

  1. Create Source and CMakeLists.txt
  2. mkdir build
  3. cd build
  4. cmake ..   -  Generting the Build Files / Configure the Project
  5. cmake --build .

### Run unit test

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

### Run integration test

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

### CRC calculation options

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