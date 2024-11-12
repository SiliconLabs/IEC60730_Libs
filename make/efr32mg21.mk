
EFR32MG21_LIST := \
efr32mg21a010f1024im32 \
efr32mg21a010f512im32 \
efr32mg21a010f768im32 \
efr32mg21a020f1024im32 \
efr32mg21a020f512im32 \
efr32mg21a020f768im32 \
efr32mg21b010f1024im32 \
efr32mg21b010f512im32 \
efr32mg21b010f768im32 \
efr32mg21b020f1024im32 \
efr32mg21b020f512im32 \
efr32mg21b020f768im32 \
rm21z000f1024im32

ifneq ($(strip $(DERIVATIVE)),)
ifeq ($(findstring $(DERIVATIVE),$(EFR32MG21_LIST)), $(DERIVATIVE))
DEVICE := efr32mg21
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



