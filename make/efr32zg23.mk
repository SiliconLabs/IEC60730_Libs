
EFR32ZG23_LIST := \
efr32zg23a010f512gm40 \
efr32zg23a010f512gm48 \
efr32zg23a020f512gm40 \
efr32zg23a020f512gm48 \
efr32zg23b010f512im40 \
efr32zg23b010f512im48 \
efr32zg23b011f512im40 \
efr32zg23b020f512im40 \
efr32zg23b020f512im48 \
efr32zg23b021f512im40

ifneq ($(strip $(DERIVATIVE)),)
ifeq ($(findstring $(DERIVATIVE),$(EFR32ZG23_LIST)), $(DERIVATIVE))
DEVICE := efr32zg23
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
