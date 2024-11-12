
USER_OBJS :=

ifeq ($(strip $(COMPILER)),GCC)
# GCC
LIBS := -lgcc -lc -lm -lnosys

else
ifeq ($(strip $(COMPILER)),IAR)
# IAR
LIBS :=

endif
endif