
# Log file
LOG_FILE :=
#&> ../Build/log.txt

CMSE_FLAG :=

# Toolchain dir
ifeq ($(strip $(COMPILER)),GCC)
# GCC
ifeq ($(strip $(TOOL_DIRS)),)
TOOL_DIRS := C:/SiliconLabs/SimplicityStudio/v5/developer/toolchains/gnu_arm/10.3_2021.10/bin
endif
GCC := $(TOOL_DIRS)/arm-none-eabi-gcc
GCC_CP := $(TOOL_DIRS)/arm-none-eabi-objcopy
GCC_OBJDUMP := $(TOOL_DIRS)/arm-none-eabi-objdump
GCC_SIZE := $(TOOL_DIRS)/arm-none-eabi-size
else
ifeq ($(strip $(COMPILER)),IAR)
# IAR
ifeq ($(strip $(TOOL_DIRS)),)
TOOL_DIRS := C:/EmbeddedWorkbench8.4/arm/bin
endif
ICC := $(TOOL_DIRS)/iccarm
IASM := $(TOOL_DIRS)/iasmarm
ICL := $(TOOL_DIRS)/ilinkarm
ICC_CP := $(TOOL_DIRS)/ielftool
ICC_OBJDUMP := $(TOOL_DIRS)/ielfdumparm
ICC_SIZE :=
endif
endif

# Compiler
ifeq ($(strip $(COMPILER)),GCC)
CC := $(GCC)
CL := $(GCC)
CC_CP := $(GCC_CP)
CC_OBJDUMP := $(GCC_OBJDUMP)
CC_SIZE := $(GCC_SIZE)
CASM := $(GCC)
else
ifeq ($(strip $(COMPILER)),IAR)
CC := $(ICC)
CL := $(ICL)
CC_CP := $(ICC_CP)
CC_OBJDUMP := $(ICC_OBJDUMP)
CC_SIZE := $(ICC_SIZE)
CASM := $(IASM)
endif
endif

# Include dirs
INC_DIRS := \
$(COMP_DIR)/config \
$(COMP_DIR)/inc \
$(TEST_DIR)/inc \
$(TEST_DIR)/comm/emlib/inc \
$(DEVICE_DIRS) \
$(DEVICE_DIRS)/$(DEVICE)/Include \
$(CMSIS_DIRS)/Core/Include \
$(DEVICE_DIRS)/Comm/inc


# Include dir options
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# Use for keep __checksum in IAR
CHECKSUM_FLAGS :=

# Compile options for C source
ifeq ($(strip $(COMPILER)),GCC)
# GCC
CFLAGS := -g3 -gdwarf-2 $(CORE_TYPE) $(DEFS) $(INC_FLAGS) -mthumb $(FPU_TYPE) -std=c99 -Wall -Wextra -fno-builtin -ffunction-sections -fdata-sections -c -fmessage-length=0 -MMD -MP $(LOG_FILE)

ifeq ($(strip $(APP_SECURE)),true)
CMSE_FLAG := -mcmse
endif

DEPENDENCIES_FLAG := -MF
MAP_FLAG := -Xlinker -Map -Xlinker
LDFILE_FLAG := -Xlinker -T
IHEX_FLAG := -O ihex
BINARY_FLAG := -O binary
SREC_FLAG := -O srec
OBJDUMP_FLAG := -t -h -d -S
SIZE_FLAG := -A
SIZE_FLAG_1 := -B --common -t

else
ifeq ($(strip $(COMPILER)),IAR)
# IAR
CFLAGS := $(CORE_TYPE) $(DEFS) $(INC_FLAGS) --debug --cpu_mode=thumb $(FPU_TYPE) -On -e --char_is_unsigned --header_context --error_limit=3 $(LOG_FILE)

ifeq ($(strip $(APP_SECURE)),true)
CMSE_FLAG := --cmse
endif

DEPENDENCIES_FLAG := --dependencies=i
MAP_FLAG := --map
LDFILE_FLAG := --config
# LDFILE_FLAG :=
IHEX_FLAG := --ihex
BINARY_FLAG := --bin
SREC_FLAG := --srec
OBJDUMP_FLAG := --all --source
SIZE_FLAG :=
SIZE_FLAG_1 :=

endif
endif

# Linker options
ifeq ($(strip $(COMPILER)),GCC)
# GCC
LDFLAGS := -g3 -gdwarf-2 $(CORE_TYPE) -mthumb $(FPU_TYPE) -Xlinker --gc-sections $(LIBS) $(LOG_FILE)
else
ifeq ($(strip $(COMPILER)),IAR)
# IAR
LDFLAGS := $(CORE_TYPE) $(FPU_TYPE) --error_limit=3 --use_optimized_variants=auto $(LIBS) $(LOG_FILE)
endif
endif
#-Xlinker -nostartfiles

# CRC
SRECORD_PATH:=
CRC_GCC:=gcc_crc
CRC_TYPE:=16
CRC_EXTENSION:=sh
CMD_SCRIPT:=sh

ifeq ($(OS),Windows_NT)
	CMD_SCRIPT=cmd //c
	CRC_EXTENSION=bat
	SRECORD_PATH=C:\srecord-1.64-win32
endif

ifneq (,$(findstring DUSE_CRC_32, $(DEFS)))
	CRC_TYPE=32
	ifeq ($(strip $(COMPILER)),IAR)
		CHECKSUM_FLAGS := --keep __checksum --place_holder __checksum,4,.checksum,64
	endif
else
	ifeq ($(strip $(COMPILER)),IAR)
		CHECKSUM_FLAGS := --keep __checksum --place_holder __checksum,2,.checksum,64
	endif
endif

CMD_CRC := ${CMD_SCRIPT} ${CRC_GCC}${CRC_TYPE}.${CRC_EXTENSION}
