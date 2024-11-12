
S79_SRCS := 
OBJ_SRCS := 
S_SRCS := 
ASM_SRCS := 
C_SRCS := 
S79_UPPER_SRCS := 
S_UPPER_SRCS := 
O_SRCS := 
EXECUTABLES := 
OBJS := 
NS_OBJS := 
NS_ADDED_OBJS := 
SIZE_OBJS :=
C_DEPS := 
DEFS := 

# Build dir
BUILD_DIR := ../Build
OUT_DIR := Out
COMP_DIR := ../Lib
TEST_DIR := ../Test
DEVICE_DIRS := ../Lib/Device
LIB_DIRS := $(DEVICE_DIRS)
CMSIS_DIRS := ../Lib/CMSIS
CUR_BUILDDIR := 
TARGET := 

# Every subdirectory with source files must be described here
SUBDIRS := 

ifeq ($(strip $(COMPILER)),)
COMPILER := GCC
endif

ifneq ($(strip $(COMPILER)),GCC)
ifneq ($(strip $(COMPILER)),IAR)
$(error Invalid Compiler!)
endif
endif