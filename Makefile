####################### CONFIGURATION ########################################

# Preliminaries
SHELL = /bin/sh

# C++ compiler and compling flags
CC := g++
CFLAGS := -Wall -Wextra -g -std=c++14 -MMD -MP

# Directories
BUILD_DIR := ./build# this ./ is critical
SRC_DIR := polygonal-niceness
DATA_DIR := data
TARGET := bin/main
MISC := *.txt

SRC_EXT := cpp
SRCS := $(shell find $(SRC_DIR) -type f -name *.$(SRC_EXT))
OBJS := $(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(SRCS:.$(SRC_EXT)=.o))
DATA := $(shell find $(DATADIR) -type f -name *.csv)
INC := -I include

# linking flags, "-L/path/to/your/libs"
LDFLAGS :=
# libraries, either "/path/to/static/libs.a" or just -llibs
LIBS := -lCGAL -lgmp -lmpfr -lboost_thread

# dependencies, your headers that are depended by objs
# note that in general, you need to group objs for different
# deps
DEPS := $(OBJS:.o=.d)

# suffix rule
.SUFFIXES: .cpp .cc .c++ .h .hpp .hh .h++

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

############## RULES ##################

# Commands #
#
default: $(TARGET)
	$(TARGET)

$(TARGET): $(OBJS)
	$(CC) $^ -o $@ $(LIBS) 

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.$.cpp
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<


clean:
	$(RM) -r $(BUILDDIR) $(TARGET) $(MISC);

.PHONY: clean

-include $(DEPS)


# Formatting

# Colors #
COM_C := \033[0;34m
OBJ_C := \033[0;36m
OK_C := \033[0;32m
ERROR_C := \033[0;31m
WARN_C := \033[0;33m
NO_C := \033[m

# Formatting #
BF := \033[1m
UL := \033[4m
NM := \033[0m
DM := \033[2m


# Strings #
OK_S := "[OK]"
ERROR_S := "[ERROR]"
WARN_S := "[WARNING]"
COM_S := "Compiling"
LNK_S := "Linking:"
CLN_S := "Cleaning:"


# $(TARGET_EXEC): $(OBJS)
# 	@echo "$(COM_C)$(BF)$(LNK_S)$(NM)$(NO_C) $(OBJECTS)"
# 	@echo "    $(BF)$(CC) $^ $(LIBS) -o $(TARGET) $(NM)"
# 	@$(CC) $^ $(LIBS) -o $@
# 
# $(BUILD_DIR)/%.cpp.o: %.cpp
# 	@echo "$(COM_C)$(BF)$(COM_S)$(NM)$(NO_C)"
# 	@echo "    $(UL)$(CC) $(CFLAGS) $(INC) -c -o $@ $<$(NM)"
# 	@mkdir -p $(BUILD_DIR)
# 	@$(CC) $(CFLAGS) $(INC) -c $< -o $@ 
# 
# .PHONY: clean
# 
# clean:
# 	@echo "$(COM_C)$(BF)$(CLN_S)$(NM)$(NO_C)"
# 	@echo "    $(RM) -r $(BUILDDIR) $(TARGET) $(MISC)";
# 	@$(RM) -r $(BUILDDIR) $(TARGET) $(MISC);
# 
# 
# -include $(DEPS)



