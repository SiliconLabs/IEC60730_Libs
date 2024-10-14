Show list of components:
make info

Build target example:
- Select toolchain:
	"export COMPILER=IAR"
or
	"export COMPILER=GCC"

- Set the toolchain directory:
export TOOL_DIRS=C:/SiliconLabs/SimplicityStudio/v5/developer/toolchains/gnu_arm/10.3_2021.10/bin

For devices does not have Trust zone implemented:
	make build COMPONENT=invariable_memory DERIVATIVE=efr32mg12p132f1024gl125 NON_SECURE_EN=false APP_SECURE=false
  or (for the 'COMPILER' is not set before):
	make build COMPONENT=invariable_memory DERIVATIVE=efr32mg12p132f1024gl125 NON_SECURE_EN=false APP_SECURE=false COMPILER=IAR

  Output is <device>/<compiler>/S/Out

For devices that have Trust zone implemented:
  Build secure test app only:
  make build COMPONENT=cpu_registers DERIVATIVE=efr32mg21a020f1024im32 NON_SECURE_EN=false APP_SECURE=true

  Build non-secure test app only:
  make build COMPONENT=cpu_registers DERIVATIVE=efr32mg21a020f1024im32 NON_SECURE_EN=false APP_SECURE=false

  Output is <device>/<compiler>/S/Out

For devices that have Trust zone implemented and non-secure peripherals need to test:
Must to run two commands below.

  Build secure test app with non-secure peripherals need to test:
  make build COMPONENT=cpu_registers DERIVATIVE=efr32mg21a020f1024im32 NON_SECURE_EN=true APP_SECURE=true

  Build non-secure test app with non-secure peripherals need to test:
  make build COMPONENT=cpu_registers DERIVATIVE=efr32mg21a020f1024im32 NON_SECURE_EN=true APP_SECURE=false

  Output of S and NS apps is <device>/<compiler>/NS/Out

Clean all:
make clean_all

Clean specific device example:
make clean COMPONENT=invariable_memory DERIVATIVE=efr32mg12p132f1024gl125

Run this command in case your shell script not run
sed -i -e 's/\r$//' scriptname.sh

Install screc

Linux
```
sudo apt install srecord
```
