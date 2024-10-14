
EFR32FG23_LIST := \
efr32fg23a010f128gm40 \
efr32fg23a010f256gm40 \
efr32fg23a010f256gm48 \
efr32fg23a010f512gm40 \
efr32fg23a010f512gm48 \
efr32fg23a011f512gm40 \
efr32fg23a020f128gm40 \
efr32fg23a020f256gm40 \
efr32fg23a020f256gm48 \
efr32fg23a020f512gm40 \
efr32fg23a020f512gm48 \
efr32fg23a021f512gm40 \
efr32fg23b010f128gm40 \
efr32fg23b010f512gm48 \
efr32fg23b010f512im40 \
efr32fg23b010f512im48 \
efr32fg23b020f128gm40 \
efr32fg23b020f512im40 \
efr32fg23b020f512im48

ifneq ($(strip $(DERIVATIVE)),)
ifeq ($(findstring $(DERIVATIVE),$(EFR32FG23_LIST)), $(DERIVATIVE))
DEVICE := efr32fg23
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
