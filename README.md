# IEC60730_Libs
Platform codes for EFR32 series chips which complies to IEC60730 safety standard

## Introduction
The IEC60730 library for EFR32 provides a basic implementation required to support the necessary requirements found in Table H.1 in the IEC60730 specification. It includes all the Power On Self Test (POST) functions executed when a device is first powered on, as well as Built In Self Test (BIST) functions that are called periodically to ensure correct operation. Certain portions of the requirements require a detailed understanding of the system under development. Callback functions must be completed by the developer to guarantee meeting the full specification. These include a Safe State function used when validation detects an anomaly, properly implemented communications channels (redundancy, error detection, periodic communcations), and Plausibility functions to validate system state (internal variables and inputs/outputs).

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
Use the New Project window and select an Example project. Under the IEC60730 folder is the IEC60730 Demo project.
See OEM Customization for details on customizing the project and adding custom code.

## Compiler specifications
**The C compilers:**
- GNU GCC V10.3
- IAR EW for ARM V9.2

**Tools specification**
Test frame work tools:
- Python V3.11

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