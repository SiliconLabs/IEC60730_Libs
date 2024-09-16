# Component specific definitions
DEFS += '-DIEC_BOARD_HEADER="sl_iec60730_board.h"'

-include comp_comm.mk

# Object files
OBJS += Test_programme_counter.o iec60730_bist.o

# Build all specific source files
Test_programme_counter.o: $(TEST_DIR)/src/Test_programme_counter.c
	$(CC) $(CFLAGS) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/Test_programme_counter.d -o $(CUR_BUILDDIR)/$@ $^
	@echo ' '

iec60730_bist.o: $(COMP_DIR)/src/sl_iec60730_bist.c
	$(CC) $(CFLAGS) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/iec60730_bist.d -o $(CUR_BUILDDIR)/$@ $^
	@echo ' '
