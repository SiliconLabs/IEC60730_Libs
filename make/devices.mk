ifeq ($(strip $(COMPILER)),GCC)
# GCC
# Core types compiler option
CORE_M33 := -mcpu=cortex-m33
CORE_M4 := -mcpu=cortex-m4
ASM_CORE_M33 := -mcpu=cortex-m33
ASM_CORE_M4 := -mcpu=cortex-m4

# FPU types compiler option
M33_FPU_HARD := -mfpu=fpv5-sp-d16 -mfloat-abi=hard
M4_FPU_HARD := -mfpu=fpv4-sp-d16 -mfloat-abi=hard
ASM_M33_FPU_HARD := -mfpu=fpv5-sp-d16 -mfloat-abi=hard
ASM_M4_FPU_HARD := -mfpu=fpv4-sp-d16 -mfloat-abi=hard
else
ifeq ($(strip $(COMPILER)),IAR)
# IAR
# Core types compiler option
CORE_M33 := --cpu=Cortex-M33.fp
ASM_CORE_M33 := --cpu Cortex-M33.fp
CORE_M4 := --cpu=Cortex-M4
ASM_CORE_M4 := --cpu Cortex-M4

# FPU types compiler option
M33_FPU_HARD := --fpu=VFPv5-SP
ASM_M33_FPU_HARD := --fpu VFPv5-SP
M4_FPU_HARD := --fpu=VFPv4-SP
ASM_M4_FPU_HARD := --fpu VFPv4-SP

endif
endif

# For non-secure build
NS_SUBFIX := _NS
NON_SECURE_ACT := false
ifndef NON_SECURE_EN
NON_SECURE_EN := false
endif
ifndef APP_SECURE
APP_SECURE := true
endif

# Device family
#DEVICE := efr32mg12p
# efr32mg12p
# efr32mg21

# Chip ID
#DERIVATIVE := efr32mg12p132f1024gl125
# efr32mg12p132f1024gl125
# efr32mg21b020f512im32

# Lib components
#COMPONENT := invariable_memory

COMPONENTS_LIST := \
programme_counter \
invariable_memory \
system_clock \
variable_memory \
irq \
watchdog \
cpu_registers \
post \
bist \
integrated

FOUND :=

NON_STD_COMPONENT := false

# Definitions
COMP_DEFS := 

# Default config
# ifeq ($(strip $(DEVICE)),)
# DEVICE := efr32mg21
# endif

ifeq ($(strip $(DERIVATIVE)),)
DERIVATIVE := efr32mg21b020f512im32
endif

ifeq ($(strip $(COMPONENT)),)
COMPONENT := cpu_registers
endif

# Check valid components
ifneq ($(strip $(COMPONENT)), all)
ifneq ($(findstring $(COMPONENT),$(COMPONENTS_LIST)), $(COMPONENT))
$(error Invalid Component!)
endif
endif

# Find device ID of the derivative
ifeq ($(strip $(FOUND)),)
-include efr32mg21.mk
endif

ifeq ($(strip $(FOUND)),)
-include efr32mg12p.mk
endif

ifeq ($(strip $(FOUND)),)
-include efr32fg23.mk
endif

ifeq ($(strip $(FOUND)),)
-include efr32zg23.mk
endif

ifeq ($(strip $(FOUND)),)
-include efr32bg22.mk
endif

ifeq ($(strip $(FOUND)),)
-include efr32fg22.mk
endif

ifeq ($(strip $(FOUND)),)
-include efm32pg22.mk
endif

ifeq ($(strip $(FOUND)),)
-include efr32mg24.mk
endif

# Finally, if not found then there's no valid chip ID
ifeq ($(strip $(FOUND)),)
$(error Invalid Derivative!)
endif

# Definitions
ifeq ($(strip $(NON_SECURE_ACT)),true)
DEFS += '-DTEST_NONSECURE_ENABLE' '-DIEC60730_NON_SECURE_EN'
endif
DEFS += '-DSL_LEGACY_LINKER'
DEFS += '-D$(shell echo $(DERIVATIVE) | tr a-z A-Z)=1' '-D$(shell echo $(DEVICE)_DEVICE | tr a-z A-Z)'

# Linker file
LD_DIRS := ../Lib/Device/$(DEVICE)/Source/$(COMPILER)
ifeq ($(strip $(COMPILER)),GCC)
# GCC
LD_FILE := $(LD_DIRS)/$(DEVICE).ld
LD_FILE_NS := $(LD_DIRS)/$(DEVICE)$(NS_SUBFIX).ld
else
ifeq ($(strip $(COMPILER)),IAR)
# IAR
LD_FILE := $(LD_DIRS)/$(DEVICE).icf
LD_FILE_NS := $(LD_DIRS)/$(DEVICE)$(NS_SUBFIX).icf

endif
endif

# Startup code
STRUP_DIRS := ../Lib/Device/$(DEVICE)/Source/$(COMPILER)
STRUP_FILE := $(STRUP_DIRS)/startup_$(DEVICE).c
