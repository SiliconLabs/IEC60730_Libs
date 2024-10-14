
EFM32PG22_LIST := \
efm32pg22c200f32im32 \
efm32pg22c200f128im40 \
efm32pg22c200f256im32 \
efm32pg22c200f256im40 \
efm32pg22c200f32im32 \
efm32pg22c200f32im40 \
efm32pg22c200f512im32 \
efm32pg22c200f512im40 \
efm32pg22c200f64im32 \
efm32pg22c200f64im40

ifneq ($(strip $(DERIVATIVE)),)
ifeq ($(findstring $(DERIVATIVE),$(EFM32PG22_LIST)), $(DERIVATIVE))
DEVICE := efm32pg22
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
