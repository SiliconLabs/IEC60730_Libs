
EFR32BG22_LIST := \
efr32bg22c112f352gm32 \
efr32bg22c112f352gm40 \
efr32bg22c222f352gm32 \
efr32bg22c222f352gm40 \
efr32bg22c222f352gn32 \
efr32bg22c224f512gm32 \
efr32bg22c224f512gm40 \
efr32bg22c224f512gn32 \
efr32bg22c224f512im32 \
efr32bg22c224f512im40

ifneq ($(strip $(DERIVATIVE)),)
ifeq ($(findstring $(DERIVATIVE),$(EFR32BG22_LIST)), $(DERIVATIVE))
DEVICE := efr32bg22
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
