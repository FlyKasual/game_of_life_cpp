# Variables

# My own variables

DEBUG ?= 0
ENABLE_WARNINGS ?= 1
WARNINGS_AS_ERRORS ?= 0
OUT_DIR = build
SOURCE_DIR = src
INCLUDE_DIR = include
COMPILE_CPP = $(CXX) $(CPPFLAGS) $(CXXFLAGS)
C_STANDARD = c17
C_OPTIMIZE_FLAGS = -O3

ifeq ($(ENABLE_WARNINGS), 1)
C_WARNING_FLAGS = -Wall -Wextra -Wpedantic
else
C_WARNING_FLAGS =
endif

ifeq ($(WARNINGS_AS_ERRORS), 1)
C_WARNING_FLAGS += -Werror
endif

C_INCLUDE_FLAGS =
C_SOURCE_FILES = $(wildcard *.c)
C_OBJECT_FILES = $(patsubst %.c, $(OUT_DIR)/%.o, $(C_SOURCE_FILES))
CXX_STANDARD = c++17
CXX_OPTIMIZE_FLAGS = -O3
CXX_DEBUG_FLAGS =

ifeq ($(ENABLE_WARNINGS), 1)
CXX_WARNING_FLAGS = -Wall -Wextra -Wpedantic
else
CXX_WARNING_FLAGS =
endif

ifeq ($(WARNINGS_AS_ERRORS), 1)
CXX_WARNING_FLAGS += -Werror
endif

CXX_SOURCE_FILES = $(wildcard $(SOURCE_DIR)/*.cpp)
CXX_OBJECT_FILES = $(patsubst $(SOURCE_DIR)/%.cpp, $(OUT_DIR)/%.o, $(CXX_SOURCE_FILES))
EXECUTABLE_NAME = main

ifeq ($(DEBUG), 1)

C_OPTIMIZE_FLAGS = -O0
C_DEBUG_FLAGS =-g
CXX_OPTIMIZE_FLAGS = -O0
CXX_DEBUG_FLAGS = -g
OUT_DIR = debug

endif

# Alternatively move this is possible further down:
#
# ifeq ($(DEBUG), 1)

# CFLAGS += -g -O0
# CXXFLAGS += -g -O0

# else

# CFLAGS += -O3
# CXXFLAGS += -O3

# endif

# CC:		Program for compiling C programs; default: cc
# CXX:		Program for compiling C++ programs; default g++
# CFLAGS:	Extra flags to give to the C compiler
# CXXFLAGS:	Extra flags to give to the C++ compiler
# CPPFLAGS:	Extra flags to give to the C preprocessor
# LDFLAGS:	Extra flags to give to the linker

CC = gcc
CFLAGS = $(C_WARNING_FLAGS) --std=$(C_STANDARD) $(C_OPTIMIZE_FLAGS) $(C_DEBUG_FLAGS)
CXX = g++
CXXFLAGS = $(CXX_WARNING_FLAGS) --std=$(CXX_STANDARD) $(CXX_OPTIMIZE_FLAGS) $(C_DEBUG_FLAGS)
CPPFLAGS = -I $(INCLUDE_DIR)
LDFLAGS =

# TARGETS

all: build_dir build

build: build_dir $(CXX_OBJECT_FILES)
	$(COMPILE_CPP) $(LDFLAGS) $(CXX_OBJECT_FILES) -o $(OUT_DIR)/$(EXECUTABLE_NAME)

build_dir:
	@mkdir -p $(OUT_DIR)

execute:
	@./$(OUT_DIR)/$(EXECUTABLE_NAME)

clean:
	rm -rf $(OUT_DIR)

# Patterns
# $@: the file name of the target
# $<: the name of the first dependency
# $^: the names of all prerequisites
$(OUT_DIR)/%.o: build_dir $(SOURCE_DIR)/%.cpp
	$(COMPILE_CPP) -c $(word 2, $^) -o $@

$(OUT_DIR)/%.o: build_dir $(SOURCE_DIR)/%.cc
	$(COMPILE_CPP) -c $(word 2, $^) -o $@

$(OUT_DIR)/%.o: build_dir $(SOURCE_DIR)/%.cxx
	$(COMPILE_CPP) -c $(word 2, $^) -o $@

$(OUT_DIR)/%.o: build_dir $(SOURCE_DIR)/%.c
	$(COMPILE_CPP) -c $(word 2, $^) -o $@

# PHONY targets
.PHONY: build build_dir execute clean
