-include comp_comm.mk

# Component specific definitions
# DEFS += '-DTEST_TIMER_EN'
DEFS += '-DIEC_BOARD_HEADER="sl_iec60730_board.h"'

# Default turn on CRC Debug
ifneq ($(strip $(N_CRC_DEBUG)),1)
DEFS += '-DCRC_DEBUG'
endif

ifeq ($(strip $(CRC_SW)),1)
DEFS += '-DCRC_USE_SW'
	ifeq ($(strip $(CRC_TABLE)),1)
DEFS += '-DSW_CRC_TABLE'
	endif
endif

# Default CRC16
ifeq ($(strip $(CRC_32)),1)
DEFS += '-DUSE_CRC_32'
endif

# Object files
ifeq ($(strip $(NON_SECURE_ACT)),true)
TEMP_NS_OBJS += Test_imc_ns.o \
iec60730_bist.o \
iec60730_post.o \
iec60730_oem_timer.o \
em_wdog.o \
em_gpcrc.o

NS_ADDED_OBJS += $(TEMP_NS_OBJS)
NS_OBJS += iec60730_$(COMPONENT).o \
$(TEMP_NS_OBJS)
else # NON_SECURE_ACT
OBJS += Test_imc.o \
iec60730_bist.o \
iec60730_post.o \
iec60730_oem_timer.o \
em_wdog.o \
em_gpcrc.o
endif

# Build all specific source files
Test_imc.o: $(TEST_DIR)/src/Test_imc.c
	@echo 'Building file: $<'
	@echo 'Invoking: $(COMPILER) ARM C Compiler'
	$(CC) $(CFLAGS) $(CMSE_FLAG) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/Test_imc.d -o $(CUR_BUILDDIR)/$@ $^
	@echo 'Finished building: $<'
	@echo ' '

Test_imc_ns.o: $(TEST_DIR)/src/Test_imc_ns.c
	@echo 'Building file: $<'
	@echo 'Invoking: $(COMPILER) ARM C Compiler'
	$(CC) $(CFLAGS) $(CMSE_FLAG) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/Test_imc_ns.d -o $(CUR_BUILDDIR)/$@ $^
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

iec60730_post.o: $(COMP_DIR)/src/sl_iec60730_post.c
	@echo 'Building file: $<'
	@echo 'Invoking: $(COMPILER) ARM C Compiler'
	$(CC) $(CFLAGS) $(CMSE_FLAG) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/iec60730_post.d -o $(CUR_BUILDDIR)/$@ $^
	@echo 'Finished building: $<'
	@echo ' '

iec60730_bist.o: $(COMP_DIR)/src/sl_iec60730_bist.c
	@echo 'Building file: $<'
	@echo 'Invoking: $(COMPILER) ARM C Compiler'
	$(CC) $(CFLAGS) $(CMSE_FLAG) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/iec60730_bist.d -o $(CUR_BUILDDIR)/$@ $^
	@echo 'Finished building: $<'
	@echo ' '

iec60730_oem_timer.o: $(TEST_DIR)/src/oem_iec60730_timer.c
	@echo 'Building file: $<'
	@echo 'Invoking: $(COMPILER) ARM C Compiler'
	$(CC) $(CFLAGS) $(CMSE_FLAG) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/iec60730_oem_timer.d -o $(CUR_BUILDDIR)/$@ $^
	@echo 'Finished building: $<'
	@echo ' '
