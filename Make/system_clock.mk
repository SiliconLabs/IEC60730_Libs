# Component specific definitions
DEFS += '-DTEST_TIMER_EN' '-DTEST_BIST_EN' '-DIEC_BOARD_HEADER="iec60730_board.h"'

-include comp_comm.mk

# Object files
OBJS += Test_sys_clock.o iec60730_oem_timer.o iec60730_bist.o iec60730_post.o

# Build all specific source files
Test_sys_clock.o: $(TEST_DIR)/src/Test_sys_clock.c
	$(CC) $(CFLAGS) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/Test_sys_clock.d -o $(CUR_BUILDDIR)/$@ $^
	@echo ' '

iec60730_oem_timer.o: $(TEST_DIR)/src/iec60730_oem_timer.c
	$(CC) $(CFLAGS) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/iec60730_oem_timer.d -o $(CUR_BUILDDIR)/$@ $^
	@echo ' '

iec60730_bist.o: $(COMP_DIR)/src/iec60730_bist.c
	$(CC) $(CFLAGS) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/iec60730_bist.d -o $(CUR_BUILDDIR)/$@ $^
	@echo ' '

iec60730_post.o: $(COMP_DIR)/src/iec60730_post.c
	$(CC) $(CFLAGS) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/iec60730_post.d -o $(CUR_BUILDDIR)/$@ $^
	@echo ' '