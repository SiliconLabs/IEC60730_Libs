# Component specific definitions
DEFS += '-DTEST_IRQ_EN' '-DTEST_BIST_EN' '-DIEC_BOARD_HEADER="sl_iec60730_board.h"'

-include comp_comm.mk

# Object files
OBJS += Test_irq.o iec60730_oem_timer.o iec60730_bist.o

# Build all specific source files
Test_irq.o: $(TEST_DIR)/src/Test_irq.c
	$(CC) $(CFLAGS) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/Test_irq.d -o $(CUR_BUILDDIR)/$@ $^
	@echo ' '

iec60730_oem_timer.o: $(TEST_DIR)/src/oem_iec60730_timer.c
	$(CC) $(CFLAGS) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/iec60730_oem_timer.d -o $(CUR_BUILDDIR)/$@ $^
	@echo ' '

iec60730_bist.o: $(COMP_DIR)/src/sl_iec60730_bist.c
	$(CC) $(CFLAGS) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/iec60730_bist.d -o $(CUR_BUILDDIR)/$@ $^
	@echo ' '