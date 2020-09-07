#MAKEFILE IS REAL

CPPFLAGS = -g -Wall -Werror -Wextra -O2
#OBJS = main.o market.o pi_factory.o pi_product.o pi_setup.o

SRC_DIR = ./src
BUILD_DIR = ./obj
BIN_DIR = ./bin

#debug = yes

PROG = $(BIN_DIR)/InvestmentPredictor.exe

SRC_LIST := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_LIST = $(SRC_LIST:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

#OBJ_LIST = $(BUILD_DIR)/$(notdir $(SRC_LIST:%.cpp=%.o))
#OBJ_LIST = $(addprefix $(BUILD_DIR)/,$(notdir $(SRC_LIST:%.cpp=%.o)))

ifeq ($(debug),yes)
$(info SRC_DIR=$(SRC_DIR))
$(info BIN_DIR=$(BIN_DIR))
$(info BUILD_DIR=$(BUILD_DIR))

$(info SRC_LIST=$(SRC_LIST))
$(info OBJ_LIST=$(OBJ_LIST))
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

clean :
	$(RM) $(BIN_DIR)/$(PROG) $(OBJ_LIST)

.PHONY : all clean

