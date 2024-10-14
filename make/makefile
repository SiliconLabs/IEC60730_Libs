
RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include devices.mk
-include objects.mk
-include $(COMPONENT).mk
-include toolchains.mk

# Current build dir
ifeq ($(strip $(NON_SECURE_ACT)),true)
CUR_BUILDDIR := $(BUILD_DIR)/$(COMPONENT)/$(DEVICE)/$(DERIVATIVE)/$(COMPILER)/NS
else
CUR_BUILDDIR := $(BUILD_DIR)/$(COMPONENT)/$(DEVICE)/$(DERIVATIVE)/$(COMPILER)/S
endif

-include pre_build.mk
-include post_build.mk

# All Targets
all: build

# Build target
build: $(COMPONENT)
	@echo "Target compiled."

# Lib component
ifeq ($(strip $(NON_SECURE_ACT)),false)
COMPONENT_CMD_LIST := pre_build iec60730_$(COMPONENT).axf
# only run post_build with integrated and invariable_memory components
ifeq ($(strip $(COMPONENT)), integrated)
COMPONENT_CMD_LIST += post_build
else
ifeq ($(strip $(COMPONENT)), invariable_memory)
COMPONENT_CMD_LIST += post_build
endif
endif
else
ifeq ($(strip $(APP_SECURE)),true)
COMPONENT_CMD_LIST := pre_build iec60730_$(COMPONENT).axf
else
COMPONENT_CMD_LIST += iec60730_$(COMPONENT)$(NS_SUBFIX).axf
# only run post_build with integrated and invariable_memory components
ifeq ($(strip $(COMPONENT)), integrated)
COMPONENT_CMD_LIST += post_build
else
ifeq ($(strip $(COMPONENT)), invariable_memory)
COMPONENT_CMD_LIST += post_build
endif
endif
endif
endif

$(COMPONENT): $(COMPONENT_CMD_LIST)

# Build target
ifeq ($(strip $(NON_SECURE_ACT)),true)
iec60730_$(COMPONENT).axf: $(OBJS)
	@echo 'Tool chain: $(COMPILER)'
	@echo 'Building target: $@'
	$(CL) $(LDFLAGS) $(LDFILE_FLAG) $(LD_FILE) -o $(CUR_BUILDDIR)/$(OUT_DIR)/$@ $(OBJS:%.o=$(CUR_BUILDDIR)/%.o) $(CHECKSUM_FLAGS)
	@echo 'Finished building target: $@'
	@echo ' '
else
iec60730_$(COMPONENT).axf: $(OBJS)
	@echo 'Tool chain: $(COMPILER)'
	@echo 'Building target: $@'
	$(CL) $(LDFLAGS) $(LDFILE_FLAG) $(LD_FILE) $(MAP_FLAG) "$(CUR_BUILDDIR)/iec60730_$(COMPONENT).map" -o $(CUR_BUILDDIR)/$(OUT_DIR)/$@ $(OBJS:%.o=$(CUR_BUILDDIR)/%.o) $(CHECKSUM_FLAGS)
	@echo 'Finished building target: $@'
	@echo ' '
endif

	@echo 'Building hex file: iec60730_$(COMPONENT).hex'
	$(CC_CP) $(IHEX_FLAG) "$(CUR_BUILDDIR)/$(OUT_DIR)/iec60730_$(COMPONENT).axf" "$(CUR_BUILDDIR)/$(OUT_DIR)/iec60730_$(COMPONENT).hex"
	@echo ' '

	@echo 'Building bin file: iec60730_$(COMPONENT).bin'
	$(CC_CP) $(BINARY_FLAG) "$(CUR_BUILDDIR)/$(OUT_DIR)/iec60730_$(COMPONENT).axf" "$(CUR_BUILDDIR)/$(OUT_DIR)/iec60730_$(COMPONENT).bin"
	@echo ' '

	@echo 'Building s37 file: iec60730_$(COMPONENT).s37'
	$(CC_CP) $(SREC_FLAG) "$(CUR_BUILDDIR)/$(OUT_DIR)/iec60730_$(COMPONENT).axf" "$(CUR_BUILDDIR)/$(OUT_DIR)/iec60730_$(COMPONENT).s37"
	@echo ' '

ifneq ($(strip $(NON_SECURE_ACT)),true)
	@echo 'Generating dump information: iec60730_$(COMPONENT).lst'
	$(CC_OBJDUMP) $(OBJDUMP_FLAG) "$(CUR_BUILDDIR)/$(OUT_DIR)/iec60730_$(COMPONENT).axf" >"$(CUR_BUILDDIR)/$(OUT_DIR)/iec60730_$(COMPONENT).lst"
	@echo ' '
endif

ifneq ($(strip $(CC_SIZE)),)
	@echo 'Running size tool'
	$(CC_SIZE) "$(CUR_BUILDDIR)/$(OUT_DIR)/iec60730_$(COMPONENT).axf" $(SIZE_FLAG)
	@echo ' '
ifneq ($(strip $(SIZE_OBJS)),)
	$(CC_SIZE) "$(SIZE_OBJS)" $(SIZE_FLAG_1) >$(CUR_BUILDDIR)/size_report.txt
endif
endif

iec60730_$(COMPONENT)$(NS_SUBFIX).axf: $(NS_OBJS)
	@echo 'Building nonsecure target: $@'
	$(CL) $(LDFLAGS) $(LDFILE_FLAG) $(LD_FILE_NS) $(MAP_FLAG) "$(CUR_BUILDDIR)/iec60730_$(COMPONENT)$(NS_SUBFIX).map" -o $(CUR_BUILDDIR)/$(OUT_DIR)/$@ $(NS_OBJS:%.o=$(CUR_BUILDDIR)/%.o) $(CHECKSUM_FLAGS)
	@echo 'Finished building nonsecure target: $@'
	@echo ' '

	@echo 'Building hex file: iec60730_$(COMPONENT)$(NS_SUBFIX).hex'
	$(CC_CP) $(IHEX_FLAG) "$(CUR_BUILDDIR)/$(OUT_DIR)/iec60730_$(COMPONENT)$(NS_SUBFIX).axf" "$(CUR_BUILDDIR)/$(OUT_DIR)/iec60730_$(COMPONENT)$(NS_SUBFIX).hex"
	@echo ' '

	@echo 'Building bin file: iec60730_$(COMPONENT)$(NS_SUBFIX).bin'
	$(CC_CP) $(BINARY_FLAG) "$(CUR_BUILDDIR)/$(OUT_DIR)/iec60730_$(COMPONENT)$(NS_SUBFIX).axf" "$(CUR_BUILDDIR)/$(OUT_DIR)/iec60730_$(COMPONENT)$(NS_SUBFIX).bin"
	@echo ' '

	@echo 'Building s37 file: iec60730_$(COMPONENT)$(NS_SUBFIX).s37'
	$(CC_CP) $(SREC_FLAG) "$(CUR_BUILDDIR)/$(OUT_DIR)/iec60730_$(COMPONENT)$(NS_SUBFIX).axf" "$(CUR_BUILDDIR)/$(OUT_DIR)/iec60730_$(COMPONENT)$(NS_SUBFIX).s37"
	@echo ' '

	@echo 'Generating dump information: iec60730_$(COMPONENT)$(NS_SUBFIX).lst'
	$(CC_OBJDUMP) $(OBJDUMP_FLAG) "$(CUR_BUILDDIR)/$(OUT_DIR)/iec60730_$(COMPONENT)$(NS_SUBFIX).axf" >"$(CUR_BUILDDIR)/$(OUT_DIR)/iec60730_$(COMPONENT)$(NS_SUBFIX).lst"
	@echo ' '

ifneq ($(strip $(CC_SIZE)),)
	@echo 'Running size tool'
	$(CC_SIZE) "$(CUR_BUILDDIR)/$(OUT_DIR)/iec60730_$(COMPONENT)$(NS_SUBFIX).axf" $(SIZE_FLAG)
	@echo ' '
endif

# Other Targets
clean_all:
	-$(RM) $(BUILD_DIR)/*
	-@echo ' '

clean:
ifeq ($(strip $(CUR_BUILDDIR)),)
	-@echo "Empty folder"
	-@echo ' '
else
	 -$(RM) $(CUR_BUILDDIR)
	 -@echo ' '
endif

info:
	-@echo "Components list: $(COMPONENTS_LIST)"
	-@echo ' '

.PHONY: all clean clean_all build info
