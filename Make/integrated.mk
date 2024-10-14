# Component specific definitions
DEFS += '-DTEST_TIMER_EN' '-DTEST_WDOG_EN' '-DTEST_INTEGRATED_EN' '-DIEC_BOARD_HEADER="iec60730_board.h"' '-DIEC60730_RSTCAUSES_CLEAR_ENABLE' '-DIEC60730_SAVE_STAGE_ENABLE'
ifeq ($(strip $(COMPILER)),IAR)
DEFS += '-DIAR_TESTING'
endif
NON_STD_COMPONENT := true
WDOG_NUMB := 2
ifeq ($(strip $(DEVICE)),efr32bg22)
WDOG_NUMB := 1
else
ifeq ($(strip $(DEVICE)),efr32fg22)
WDOG_NUMB := 1
else
ifeq ($(strip $(DEVICE)),efm32pg22)
WDOG_NUMB := 1
endif
endif
endif

ifeq ($(strip $(WDOG_NUMB)),1)
DEFS += '-DIEC60730_WDOGINST_NUMB=1' '-DIEC60730_ENABLE_WDOG0'
endif

ifeq ($(strip $(NON_SECURE_ACT)),true)
DEFS += '-DIEC60730_NON_SECURE_EN'
endif

-include comp_comm.mk

# Match X is default algorithm
ifeq ($(strip $(N_MARCHX)),1)
ASMDEFS +=
else
ASMDEFS += '-DUSE_MARCHX'
endif

# Default turn on CRC Debug
ifeq ($(strip $(N_CRC_DEBUG)),1)
DEFS += ''
else
DEFS += '-DCRC_DEBUG'
endif

ifeq ($(strip $(CRC_SW)),1)
DEFS += '-DCRC_USE_SW'
	ifeq ($(strip $(CRC_TABLE)),1)
DEFS += '-DSW_CRC_TABLE'
	endif
endif

# Default CRC16
ifeq ($(strip $(CRC_SW)),1)
DEFS += '-DUSE_CRC_32'
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
NS_OBJS += Test_integrated_ns.o \
em_wdog.o \
em_gpcrc.o \
iec60730_oem_timer.o \
iec60730_bist.o \
iec60730_post.o \
iec60730_cpu_registers.o \
iec60730_invariable_memory.o \
iec60730_irq.o \
iec60730_programme_counter.o \
iec60730_system_clock.o \
iec60730_variable_memory.o \
iec60730_watchdog.o
else
OBJS += Test_integrated.o \
em_wdog.o \
em_gpcrc.o \
iec60730_oem_timer.o \
iec60730_bist.o \
iec60730_post.o \
iec60730_cpu_registers.o \
iec60730_invariable_memory.o \
iec60730_irq.o \
iec60730_programme_counter.o \
iec60730_system_clock.o \
iec60730_variable_memory.o \
iec60730_watchdog.o
endif

ifeq ($(strip $(COMPILER)),GCC)
# GCC
ifeq ($(strip $(NON_SECURE_ACT)),true)
NS_OBJS += iec60730_vmc_marchC.o \
iec60730_vmc_marchXC.o
else
OBJS += iec60730_vmc_marchC.o \
iec60730_vmc_marchXC.o
endif
else
ifeq ($(strip $(COMPILER)),IAR)
# IAR
ifeq ($(strip $(NON_SECURE_ACT)),true)
NS_OBJS += iec60730_vmc_marchCIAR.o \
iec60730_vmc_marchXCIAR.o
else
OBJS += iec60730_vmc_marchCIAR.o \
iec60730_vmc_marchXCIAR.o
endif
endif
endif

SIZE_OBJS = "$(CUR_BUILDDIR)/iec60730_*.o"

# Build all specific source files
Test_integrated.o: $(TEST_DIR)/src/Test_integrated.c
	@echo 'Building file: $<'
	@echo 'Invoking: $(COMPILER) ARM C Compiler'
	$(CC) $(CFLAGS) $(CMSE_FLAG) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/Test_integrated.d -o $(CUR_BUILDDIR)/$@ $^
	@echo 'Finished building: $<'
	@echo ' '

Test_integrated_ns.o: $(TEST_DIR)/src/Test_integrated_ns.c
	@echo 'Building file: $<'
	@echo 'Invoking: $(COMPILER) ARM C Compiler'
	$(CC) $(CFLAGS) $(CMSE_FLAG) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/Test_integrated_ns.d -o $(CUR_BUILDDIR)/$@ $^
	@echo 'Finished building: $<'
	@echo ' '
  
em_wdog.o: $(TEST_DIR)/comm/emlib/src/em_wdog.c
	@echo 'Building file: $<'
	@echo 'Invoking: $(COMPILER) ARM C Compiler'
	$(CC) $(CFLAGS) $(CMSE_FLAG) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/em_wdog.d -o $(CUR_BUILDDIR)/$@ $^
	@echo 'Finished building: $<'
	@echo ' '

em_gpcrc.o: $(TEST_DIR)/comm/emlib/src/em_gpcrc.c
	@echo 'Building file: $<'
	@echo 'Invoking: $(COMPILER) ARM C Compiler'
	$(CC) $(CFLAGS) $(CMSE_FLAG) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/em_gpcrc.d -o $(CUR_BUILDDIR)/$@ $^
	@echo 'Finished building: $<'
	@echo ' '

iec60730_oem_timer.o: $(TEST_DIR)/src/iec60730_oem_timer.c
	@echo 'Building file: $<'
	@echo 'Invoking: $(COMPILER) ARM C Compiler'
	$(CC) $(CFLAGS) $(CMSE_FLAG) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/iec60730_oem_timer.d -o $(CUR_BUILDDIR)/$@ $^
	@echo 'Finished building: $<'
	@echo ' '

iec60730_bist.o: $(COMP_DIR)/src/iec60730_bist.c
	@echo 'Building file: $<'
	@echo 'Invoking: $(COMPILER) ARM C Compiler'
	$(CC) $(CFLAGS) $(CMSE_FLAG) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/iec60730_bist.d -o $(CUR_BUILDDIR)/$@ $^
	@echo 'Finished building: $<'
	@echo ' '

iec60730_post.o: $(COMP_DIR)/src/iec60730_post.c
	@echo 'Building file: $<'
	@echo 'Invoking: $(COMPILER) ARM C Compiler'
	$(CC) $(CFLAGS) $(CMSE_FLAG) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/iec60730_post.d -o $(CUR_BUILDDIR)/$@ $^
	@echo 'Finished building: $<'
	@echo ' '

iec60730_cpu_registers.o: $(COMP_DIR)/src/iec60730_cpu_registers.c
	@echo 'Building file: $<'
	@echo 'Invoking: $(COMPILER) ARM C Compiler'
	$(CC) $(CFLAGS) $(CMSE_FLAG) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/iec60730_cpu_registers.d -o $(CUR_BUILDDIR)/$@ $^
	@echo 'Finished building: $<'
	@echo ' '

iec60730_invariable_memory.o: $(COMP_DIR)/src/iec60730_invariable_memory.c
	@echo 'Building file: $<'
	@echo 'Invoking: $(COMPILER) ARM C Compiler'
	$(CC) $(CFLAGS) $(CMSE_FLAG) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/iec60730_invariable_memory.d -o $(CUR_BUILDDIR)/$@ $^
	@echo 'Finished building: $<'
	@echo ' '

iec60730_irq.o: $(COMP_DIR)/src/iec60730_irq.c
	@echo 'Building file: $<'
	@echo 'Invoking: $(COMPILER) ARM C Compiler'
	$(CC) $(CFLAGS) $(CMSE_FLAG) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/iec60730_irq.d -o $(CUR_BUILDDIR)/$@ $^
	@echo 'Finished building: $<'
	@echo ' '

iec60730_programme_counter.o: $(COMP_DIR)/src/iec60730_programme_counter.c
	@echo 'Building file: $<'
	@echo 'Invoking: $(COMPILER) ARM C Compiler'
	$(CC) $(CFLAGS) $(CMSE_FLAG) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/iec60730_programme_counter.d -o $(CUR_BUILDDIR)/$@ $^
	@echo 'Finished building: $<'
	@echo ' '

iec60730_system_clock.o: $(COMP_DIR)/src/iec60730_system_clock.c
	@echo 'Building file: $<'
	@echo 'Invoking: $(COMPILER) ARM C Compiler'
	$(CC) $(CFLAGS) $(CMSE_FLAG) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/iec60730_system_clock.d -o $(CUR_BUILDDIR)/$@ $^
	@echo 'Finished building: $<'
	@echo ' '

iec60730_variable_memory.o: $(COMP_DIR)/src/iec60730_variable_memory.c
	@echo 'Building file: $<'
	@echo 'Invoking: $(COMPILER) ARM C Compiler'
	$(CC) $(CFLAGS) $(CMSE_FLAG) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/iec60730_variable_memory.d -o $(CUR_BUILDDIR)/$@ $^
	@echo 'Finished building: $<'
	@echo ' '

iec60730_watchdog.o: $(COMP_DIR)/src/iec60730_watchdog.c
	@echo 'Building file: $<'
	@echo 'Invoking: $(COMPILER) ARM C Compiler'
	$(CC) $(CFLAGS) $(CMSE_FLAG) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/iec60730_watchdog.d -o $(CUR_BUILDDIR)/$@ $^
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