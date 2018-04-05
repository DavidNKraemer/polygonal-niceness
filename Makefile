####################### CONFIGURATION ########################################

# C++ compiler and compling flags
CC := g++
CFLAGS := -Wall -Wextra -g -std=c++14

# Directories
BUILDDIR := build
SRCDIR := polygonal-niceness 
DATADIR := data
TARGET := bin/main
MISC := *.txt

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
DATA := $(shell find $(DATADIR) -type f -name *.txt)
INC := -I include

# linking flags, "-L/path/to/your/libs"
LDFLAGS :=
# libraries, either "/path/to/static/libs.a" or just -llibs
LIBS := -lCGAL

# dependencies, your headers that are depended by objs
# note that in general, you need to group objs for different
# deps
DEPS := $(SRCDIR)/polygon2d.h

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


# suffix rule
.SUFFIXES: .cpp .cc .c++ .h .hpp .hh .h++ .o

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

############## RULES ##################

# Commands #
default: $(TARGET) $(OBJECTS)
	@echo "$(COM_C)$(BF)Running:$(NM)$(NO_C) $(TARGET)"
	@$(TARGET)

plots: $(DATA)
	@echo "plotting data"
	$(python3 scripts/plot_results.py)

$(TARGET): $(OBJECTS)
	@echo "$(COM_C)$(BF)$(LNK_S)$(NM)$(NO_C) $(OBJECTS)"
	@echo "    $(BF)$(CC) $^ $(LIBS) -o $(TARGET) $(NM)"
	@$(CC) $^ $(LIBS) -o $(TARGET) 

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@echo "$(COM_C)$(BF)$(COM_S)$(NM)$(NO_C)"
	@mkdir -p $(BUILDDIR)
	@echo "    $(UL)$(CC) $(CFLAGS) $(INC) -c -o $@ $<$(NM)"
	@$(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo "$(COM_C)$(BF)$(CLN_S)$(NM)$(NO_C)"
	@echo "    $(RM) -r $(BUILDDIR) $(TARGET) $(MISC)";
	@$(RM) -r $(BUILDDIR)/ $(TARGET) $(MISC);

.PHONY: clean plots
