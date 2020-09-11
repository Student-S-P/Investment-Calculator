#This makefile builds .cpp projects using .cpp libraries.
# It expects a src folder to exist, and creates object and binary
# directories. Bin is where the executable ends up.

CPPFLAGS = -g -Wall -Werror -Wextra -O2

SRC_DIR = ./src
BUILD_DIR = ./obj
BIN_DIR = ./bin
LIB_DIR = ./json

DIRS := $(SRC_DIR) $(LIB_DIR)
find_files = $(wildcard $(dir)/*.cpp)

debug ?= no

#BRIEF: This function takes a directory and the expansion of its .cpp elements
# and then fills out a list of .cpp source items and creates a matching .o
# list. Eval is needed to grab the values rather than the references to
# them.
# (1) is a directory input
# (2) is an expanded list of the .cpp items in each directory in (1)
define func
$(eval
SRC_LIST += $(2)
OBJ_LIST += $(2:$(1)/%.cpp=$(BUILD_DIR)/%.o)
)
endef

PROG = $(BIN_DIR)/InvestmentPredictor.exe

$(foreach dir,$(DIRS),$(call func,$(dir),$(wildcard $(dir)/*.cpp)))

ifeq ($(debug),yes)
$(warning SRC_DIR=$(SRC_DIR))
$(warning BIN_DIR=$(BIN_DIR))
$(warning BUILD_DIR=$(BUILD_DIR))

$(warning SRC_LIST=$(SRC_LIST))
$(warning OBJ_LIST=$(OBJ_LIST))
endif

all : $(PROG)

$(PROG) : $(OBJ_LIST)
	@echo Building $@ because: $^
	@ [ -d $(@D) ] || mkdir -p $(@D)
	$(LINK.cc) $^ -o $@

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.cpp
	@echo Building $@ because: $^
	@ [ -d $(@D) ] || mkdir -p $(@D)
	$(COMPILE.cc) $^ -o $@

$(BUILD_DIR)/%.o : $(LIB_DIR)/%.cpp
	@echo Building $@ because: $^
	@ [ -d $(@D) ] || mkdir -p $(@D)
	$(COMPILE.cc) $^ -o $@

clean :
	$(RM) $(BIN_DIR)/$(PROG) $(OBJ_LIST)

.PHONY : all clean

