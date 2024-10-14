# Calculate CRC
START_ADDR:=0

ifeq ($(strip $(NON_SECURE_ACT)),true)
START_ADDR:=0x00028000
endif

ifneq (,$(findstring DEFR32ZG23_DEVICE, $(DEFS)))
START_ADDR:=0x8000000
	ifeq ($(strip $(NON_SECURE_ACT)),true)
START_ADDR:=0x08028000
	endif
else ifneq (,$(findstring DEFR32FG23_DEVICE, $(DEFS)))
START_ADDR:=0x8000000
    ifeq ($(strip $(NON_SECURE_ACT)),true)
START_ADDR:=0x08028000
	endif
else ifneq (,$(findstring DEFR32MG24_DEVICE, $(DEFS)))
START_ADDR:=0x8000000
    ifeq ($(strip $(NON_SECURE_ACT)),true)
START_ADDR:=0x08028000
	endif
endif

TOOL_CHAINS:=GCC
ifeq ($(strip $(COMPILER)),IAR)
TOOL_CHAINS:=IAR
endif

post_build:
	$(CMD_CRC) 'iec60730_$(COMPONENT)' '$(CUR_BUILDDIR)/$(OUT_DIR)' '$(SRECORD_PATH)' '$(TOOL_CHAINS)' $(START_ADDR) $(NON_SECURE_ACT)
	-@echo ' '

.PHONY: post_build
