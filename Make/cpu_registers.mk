-include comp_comm.mk

DEFS += '-DIEC_BOARD_HEADER="iec60730_board.h"'

ifeq ($(strip $(COMPILER)),IAR)
DEFS += '-DIAR_TESTING'
endif

# Object files
ifeq ($(strip $(NON_SECURE_ACT)),true)
NS_ADDED_OBJS += Test_cpu_ns.o \
em_wdog.o \
iec60730_oem_timer.o \
iec60730_bist.o
NS_OBJS += iec60730_$(COMPONENT).o \
Test_cpu_ns.o \
em_wdog.o \
iec60730_oem_timer.o \
iec60730_bist.o
else
OBJS += Test_cpu.o \
em_wdog.o \
iec60730_oem_timer.o \
iec60730_bist.o
endif

# Build all specific source files
Test_cpu.o: $(TEST_DIR)/src/Test_cpu.c
	$(CC) $(CFLAGS) $(CMSE_FLAG) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/Test_cpu.d -o $(CUR_BUILDDIR)/$@ $^
	@echo ' '

Test_cpu_ns.o: $(TEST_DIR)/src/Test_cpu_ns.c
	$(CC) $(CFLAGS) $(CMSE_FLAG) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/Test_cpu_ns.d -o $(CUR_BUILDDIR)/$@ $^
	@echo ' '

em_wdog.o: $(TEST_DIR)/comm/emlib/src/em_wdog.c
	$(CC) $(CFLAGS) $(CMSE_FLAG) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/em_wdog.d -o $(CUR_BUILDDIR)/$@ $^
	@echo ' '

iec60730_bist.o: $(COMP_DIR)/src/iec60730_bist.c
	$(CC) $(CFLAGS) $(CMSE_FLAG) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/iec60730_bist.d -o $(CUR_BUILDDIR)/$@ $^
	@echo ' '

iec60730_oem_timer.o: $(TEST_DIR)/src/iec60730_oem_timer.c
	$(CC) $(CFLAGS) $(CMSE_FLAG) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/iec60730_oem_timer.d -o $(CUR_BUILDDIR)/$@ $^
	@echo ' '