# IEC60730_Libs
Platform codes for EFR32 series chips which complies to IEC60730 safety standard

## Introduction
The IEC60730 library for EFR32 provides a basic implementation required to support the necessary requirements found in Table H.1 in the IEC60730 specification. It includes all the Power On Self Test (POST) functions executed when a device is first powered on, as well as Built In Self Test (BIST) functions that are called periodically to ensure correct operation. Certain portions of the requirements require a detailed understanding of the system under development. Callback functions must be completed by the developer to guarantee meeting the full specification. These include a Safe State function used when validation detects an anomaly, properly implemented communications channels (redundancy, error detection, periodic communications), and Plausibility functions to validate system state (internal variables and inputs/outputs).

## License
Please refer document in Doc/html.

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

**Tools specification**

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

**Source code control:**
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

#### Install slcc

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

Export SDK_PATH=<path_to_sdk>, ARM_GCC_DIR=<path_to_toolchain>, TOOL_CHAINS and START_ADDR_FLASH (flash start address support calculate crc for module invariable memory) before run config CMake.

```sh
$ export SDK_PATH=~/SimplicityStudio/SDKs/gecko_sdk
$ export ARM_GCC_DIR=~/Downloads/SimplicityStudio_v5/developer/toolchains/gnu_arm/12.2.rel1_2023.7
$ export TOOL_CHAINS=GCC
$ export START_ADDR_FLASH=0x8000000
```

with START_ADDR_FLASH=0x8000000 is flash start address of board name brd4187c (chip EFR32MG24)

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

With the commands above, the default value supports calculation CRC-16. If you want to change to calculate for CRC-32 bits, use the config command below

```sh
$ cmake --toolchain ../cmake/toolchain.cmake .. -DENABLE_UNIT_TESTING=ON -DBOARD_NAME=brd4187c -DENABLE_CAL_CRC_32=ON
```

Here is some options to support running tests of invariable memory modules:
- ENABLE_CAL_CRC_32
- ENABLE_CRC_USE_SW (if this option ON, you can enable option: ENABLE_SW_CRC_TABLE)

CMake Build

```sh
$ cmake --build . --target unit_tests -j4
```

or

```sh
$ make unit_tests -j4
```

