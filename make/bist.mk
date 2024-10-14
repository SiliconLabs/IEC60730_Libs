# Component specific definitions
DEFS += '-DTEST_TIMER_EN' '-DTEST_WDOG_EN' '-DTEST_BIST_EN' '-DIEC_BOARD_HEADER="sl_iec60730_board.h"'

-include comp_comm.mk

# Object files
OBJS += Test_bist.o iec60730_oem_timer.o em_wdog.o iec60730_system_clock.o iec60730_watchdog.o iec60730_programme_counter.o

# Build all specific source files
Test_bist.o: $(TEST_DIR)/src/Test_bist.c
	$(CC) $(CFLAGS) $(CMSE_FLAG) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/Test_bist.d -o $(CUR_BUILDDIR)/$@ $^
	@echo ' '

iec60730_oem_timer.o: $(TEST_DIR)/src/oem_iec60730_timer.c
	$(CC) $(CFLAGS) $(CMSE_FLAG) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/iec60730_oem_timer.d -o $(CUR_BUILDDIR)/$@ $^
	@echo ' '

em_wdog.o: $(TEST_DIR)/comm/emlib/src/em_wdog.c
	$(CC) $(CFLAGS) $(CMSE_FLAG) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/em_wdog.d -o $(CUR_BUILDDIR)/$@ $^
	@echo ' '

iec60730_system_clock.o: $(COMP_DIR)/src/sl_iec60730_system_clock.c
	$(CC) $(CFLAGS) $(CMSE_FLAG) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/iec60730_system_clock.d -o $(CUR_BUILDDIR)/$@ $^
	@echo ' '

iec60730_watchdog.o: $(COMP_DIR)/src/sl_iec60730_watchdog.c
	$(CC) $(CFLAGS) $(CMSE_FLAG) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/iec60730_watchdog.d -o $(CUR_BUILDDIR)/$@ $^
	@echo ' '

iec60730_programme_counter.o: $(COMP_DIR)/src/iec60730_programme_counter.c
	$(CC) $(CFLAGS) $(CMSE_FLAG) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/iec60730_programme_counter.d -o $(CUR_BUILDDIR)/$@ $^
	@echo ' '