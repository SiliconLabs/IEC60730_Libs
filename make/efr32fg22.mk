
EFR32FG22_LIST := \
efr32fg22c121f256gm32 \
efr32fg22c121f256gm40 \
efr32fg22c121f512gm32 \
efr32fg22c121f512gm40

ifneq ($(strip $(DERIVATIVE)),)
ifeq ($(findstring $(DERIVATIVE),$(EFR32FG22_LIST)), $(DERIVATIVE))
DEVICE := efr32fg22
CORE_TYPE := $(CORE_M33)
ASM_CORE_TYPE := $(ASM_CORE_M33)
FPU_TYPE := $(M33_FPU_HARD)
ASM_FPU_TYPE := $(ASM_M33_FPU_HARD)
ifeq ($(strip $(NON_SECURE_EN)),true)
NON_SECURE_ACT := true
endif
FOUND := true
endif
endif
