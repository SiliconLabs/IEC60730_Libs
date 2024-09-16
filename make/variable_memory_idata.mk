-include comp_comm.mk

# Object files
OBJS += main.o

# Build all specific source files
main.o: $(TEST_DIR)/src/main.c
	$(CC) $(CFLAGS) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/main.d -o $(CUR_BUILDDIR)/$@ $^
	@echo ' '
