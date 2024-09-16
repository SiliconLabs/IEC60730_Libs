-include comp_comm.mk

# Component specific definitions
DEFS += '-DIEC_BOARD_HEADER="sl_iec60730_board.h"'

# Match X is default algorithm
ifneq ($(strip $(N_MARCHX)),1)
ASMDEFS += '-DUSE_MARCHX'
endif

# ASM Flags
ifeq ($(strip $(COMPILER)),GCC)
ASMFLAGS := -g3 -gdwarf-2 $(CORE_TYPE) -mthumb $(FPU_TYPE) -c -x assembler-with-cpp $(ASMDEFS) -Wall
else
ifeq ($(strip $(COMPILER)),IAR)
ASMFLAGS := $(ASM_CORE_TYPE) $(ASM_FPU_TYPE) -s+ -r $(ASMDEFS)
endif
endif

# Object files
ifeq ($(strip $(NON_SECURE_ACT)),true)
TEMP_NS_OBJS += Test_vmc_ns.o \
iec60730_bist.o \
iec60730_post.o \
iec60730_oem_timer.o \
em_wdog.o
	ifeq ($(strip $(COMPILER)),GCC)
TEMP_NS_OBJS += iec60730_vmc_marchC.o \
iec60730_vmc_marchXC.o
	else # GCC
		ifeq ($(strip $(COMPILER)),IAR)
TEMP_NS_OBJS += iec60730_vmc_marchCIAR.o \
iec60730_vmc_marchXCIAR.o
		endif # IAR
	endif # GCC

NS_ADDED_OBJS += $(TEMP_NS_OBJS)
NS_OBJS += iec60730_$(COMPONENT).o \
$(TEMP_NS_OBJS)

else # NON_SECURE_ACT

OBJS += Test_vmc.o \
iec60730_bist.o \
iec60730_post.o \
iec60730_oem_timer.o \
em_wdog.o
	ifeq ($(strip $(COMPILER)),GCC)
OBJS += iec60730_vmc_marchC.o \
	iec60730_vmc_marchXC.o
	else # GCC
		ifeq ($(strip $(COMPILER)),IAR)
OBJS += iec60730_vmc_marchCIAR.o \
iec60730_vmc_marchXCIAR.o
		endif # IAR
	endif # GCC
endif # NON_SECURE_ACT

# Build all specific source files
Test_vmc.o: $(TEST_DIR)/src/Test_vmc.c
	@echo 'Building file: $<'
	@echo 'Invoking: $(COMPILER) ARM C Compiler'
	$(CC) $(CFLAGS) $(CMSE_FLAG) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/Test_vmc.d -o $(CUR_BUILDDIR)/$@ $^
	@echo 'Finished building: $<'
	@echo ' '

Test_vmc_ns.o: $(TEST_DIR)/src/Test_vmc_ns.c
	@echo 'Building file: $<'
	@echo 'Invoking: $(COMPILER) ARM C Compiler'
	$(CC) $(CFLAGS) $(CMSE_FLAG) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/Test_vmc_ns.d -o $(CUR_BUILDDIR)/$@ $^
	@echo 'Finished building: $<'
	@echo ' '

em_wdog.o: $(TEST_DIR)/comm/emlib/src/em_wdog.c
	@echo 'Building file: $<'
	@echo 'Invoking: $(COMPILER) ARM C Compiler'
	$(CC) $(CFLAGS) $(CMSE_FLAG) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/em_wdog.d -o $(CUR_BUILDDIR)/$@ $^
	@echo 'Finished building: $<'
	@echo ' '

iec60730_bist.o: $(COMP_DIR)/src/sl_iec60730_bist.c
	@echo 'Building file: $<'
	@echo 'Invoking: $(COMPILER) ARM C Compiler'
	$(CC) $(CFLAGS) $(CMSE_FLAG) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/iec60730_bist.d -o $(CUR_BUILDDIR)/$@ $^
	@echo 'Finished building: $<'
	@echo ' '

iec60730_post.o: $(COMP_DIR)/src/sl_iec60730_post.c
	@echo 'Building file: $<'
	@echo 'Invoking: $(COMPILER) ARM C Compiler'
	$(CC) $(CFLAGS) $(CMSE_FLAG) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/iec60730_post.d -o $(CUR_BUILDDIR)/$@ $^
	@echo 'Finished building: $<'
	@echo ' '

iec60730_oem_timer.o: $(TEST_DIR)/src/oem_iec60730_timer.c
	@echo 'Building file: $<'
	@echo 'Invoking: $(COMPILER) ARM C Compiler'
	$(CC) $(CFLAGS) $(CMSE_FLAG) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/iec60730_oem_timer.d -o $(CUR_BUILDDIR)/$@ $^
	@echo 'Finished building: $<'
	@echo ' '

iec60730_vmc_marchC.o: $(COMP_DIR)/asm/$(DEVICE)/iec60730_vmc_marchC.s
	@echo 'Building file: $<'
	@echo 'Invoking: $(COMPILER) ARM Assembler'
	$(CC) $(ASMFLAGS) $(CMSE_FLAG) -o $(CUR_BUILDDIR)/$@ $^
	@echo 'Finished building: $<'
	@echo ' '

iec60730_vmc_marchXC.o: $(COMP_DIR)/asm/$(DEVICE)/iec60730_vmc_marchXC.s
	@echo 'Building file: $<'
	@echo 'Invoking: $(COMPILER) ARM Assembler'
	$(CC) $(ASMFLAGS) $(CMSE_FLAG) -o $(CUR_BUILDDIR)/$@ $^
	@echo 'Finished building: $<'
	@echo ' '

iec60730_vmc_marchCIAR.o: $(COMP_DIR)/asm/$(DEVICE)/iec60730_vmc_marchCIAR.s
	@echo 'Building file: $<'
	@echo 'Invoking: $(COMPILER) ARM Assembler'
	$(CASM) $(ASMFLAGS) $(CMSE_FLAG) -o $(CUR_BUILDDIR)/$@ $^
	@echo 'Finished building: $<'
	@echo ' '

iec60730_vmc_marchXCIAR.o: $(COMP_DIR)/asm/$(DEVICE)/iec60730_vmc_marchXCIAR.s
	@echo 'Building file: $<'
	@echo 'Invoking: $(COMPILER) ARM Assembler'
	$(CASM) $(ASMFLAGS) $(CMSE_FLAG) -o $(CUR_BUILDDIR)/$@ $^
	@echo 'Finished building: $<'
	@echo ' '
