# Object files
OBJS := startup_$(DEVICE).o \
system_$(DEVICE).o \
em_core.o \
em_rmu.o \
Test_System.o \
main.o
ifneq ($(strip $(NON_SECURE_ACT)),true)
OBJS += em_cmu.o \
em_emu.o \
em_timer.o \
em_letimer.o
endif

ifeq ($(strip $(NON_STD_COMPONENT)),false)
OBJS += iec60730_$(COMPONENT).o
endif

ifeq ($(strip $(NON_SECURE_ACT)),true)
NS_ADDED_OBJS += main_ns.o \
em_cmu.o \
em_emu.o \
em_timer.o \
em_letimer.o \
startup_$(DEVICE).o \
system_$(DEVICE)$(NS_SUBFIX).o

NS_OBJS += $(NS_ADDED_OBJS) \
em_core.o \
Test_System.o
endif

# Build all common source files
ifeq ($(strip $(NON_STD_COMPONENT)),false)
iec60730_$(COMPONENT).o: $(COMP_DIR)/src/iec60730_$(COMPONENT).c
	$(CC) $(CFLAGS) $(CMSE_FLAG) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/iec60730_$(COMPONENT).d -o $(CUR_BUILDDIR)/$@ $^
	@echo ' '
endif

startup_$(DEVICE).o: $(STRUP_DIRS)/startup_$(DEVICE).c
	$(CC) $(CFLAGS) $(CMSE_FLAG) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/startup_$(DEVICE).d -o $(CUR_BUILDDIR)/$@ $^
	@echo ' '

system_$(DEVICE).o: $(DEVICE_DIRS)/$(DEVICE)/Source/system_$(DEVICE).c
	$(CC) $(CFLAGS) $(CMSE_FLAG) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/system_$(DEVICE).d -o $(CUR_BUILDDIR)/$@ $^
	@echo ' '

em_core.o: $(TEST_DIR)/comm/emlib/src/em_core.c
	$(CC) $(CFLAGS) $(CMSE_FLAG) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/em_core.d -o $(CUR_BUILDDIR)/$@ $^
	@echo ' '

em_rmu.o: $(TEST_DIR)/comm/emlib/src/em_rmu.c
	$(CC) $(CFLAGS) $(CMSE_FLAG) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/em_rmu.d -o $(CUR_BUILDDIR)/$@ $^
	@echo ' '

Test_System.o: $(TEST_DIR)/src/Test_System.c
	$(CC) $(CFLAGS) $(CMSE_FLAG) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/Test_System.d -o $(CUR_BUILDDIR)/$@ $^
	@echo ' '

main.o: $(TEST_DIR)/src/main.c
	$(CC) $(CFLAGS) $(CMSE_FLAG) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/main.d -o $(CUR_BUILDDIR)/$@ $^
	@echo ' '

main_ns.o: $(TEST_DIR)/src/main_ns.c
	$(CC) $(CFLAGS) $(CMSE_FLAG) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/main_ns.d -o $(CUR_BUILDDIR)/$@ $^
	@echo ' '

system_$(DEVICE)$(NS_SUBFIX).o: $(DEVICE_DIRS)/$(DEVICE)/Source/system_$(DEVICE)$(NS_SUBFIX).c
	$(CC) $(CFLAGS) $(CMSE_FLAG) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/system_$(DEVICE)$(NS_SUBFIX).d -o $(CUR_BUILDDIR)/$@ $^
	@echo ' '

em_timer.o: $(TEST_DIR)/comm/emlib/src/em_timer.c
	$(CC) $(CFLAGS) $(CMSE_FLAG) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/em_timer.d -o $(CUR_BUILDDIR)/$@ $^
	@echo ' '

em_letimer.o: $(TEST_DIR)/comm/emlib/src/em_letimer.c
	$(CC) $(CFLAGS) $(CMSE_FLAG) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/em_letimer.d -o $(CUR_BUILDDIR)/$@ $^
	@echo ' '

em_cmu.o: $(TEST_DIR)/comm/emlib/src/em_cmu.c
	$(CC) $(CFLAGS) $(CMSE_FLAG) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/em_cmu.d -o $(CUR_BUILDDIR)/$@ $^
	@echo ' '

em_emu.o: $(TEST_DIR)/comm/emlib/src/em_emu.c
	$(CC) $(CFLAGS) $(CMSE_FLAG) $(DEPENDENCIES_FLAG) $(CUR_BUILDDIR)/em_emu.d -o $(CUR_BUILDDIR)/$@ $^
	@echo ' '
