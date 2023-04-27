# Component specific definitions
DEFS += '-DTEST_WDOG_EN' '-DIEC_BOARD_HEADER="iec60730_board.h"' '-DIEC60730_RSTCAUSES_CLEAR_ENABLE' '-DIEC60730_SAVE_STAGE_ENABLE'
ifeq ($(strip $(NON_SECURE_ACT)),true)
DEFS += '-DIEC60730_NON_SECURE_EN'
endif

-include comp_comm.mk

# Object files
ifeq ($(strip $(NON_SECURE_ACT)),true)
NS_ADDED_OBJS += Test_watchdog_ns.o \
iec60730_$(COMPONENT).o \
em_wdog.o
NS_OBJS += iec60730_$(COMPONENT).o \
Test_watchdog_ns.o \
em_wdog.o
else
OBJS += Test_watchdog.o \
em_wdog.o
endif

# Build all specific source files
Test_watchdog.o: $(TEST_DIR)/src/Test_watchdog.c
	$(CC) $(CFLAGS) $(CMSE_FLAG) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/Test_watchdog.d -o $(CUR_BUILDDIR)/$@ $^
	@echo ' '

Test_watchdog_ns.o: $(TEST_DIR)/src/Test_watchdog_ns.c
	$(CC) $(CFLAGS) $(CMSE_FLAG) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/Test_watchdog_ns.d -o $(CUR_BUILDDIR)/$@ $^
	@echo ' '
  
em_wdog.o: $(TEST_DIR)/comm/emlib/src/em_wdog.c
	$(CC) $(CFLAGS) $(CMSE_FLAG) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/em_wdog.d -o $(CUR_BUILDDIR)/$@ $^
	@echo ' '