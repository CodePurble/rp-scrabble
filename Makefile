# Configure file directories
BIN_DIR=./bin
SRC_DIR=./src
INCLUDE_DIR=./include
INSTALL_DIR=$(HOME)/.local/bin
LOG_DIR=$(HOME)/.local/share/rp-scrabble/logs
EXEC=rp-scrabble

CFLAGS += -Wall -g -I$(INCLUDE_DIR)/ -DLOG_PATH=\"$(HOME)/.local/share/rp-scrabble/logs/\"

COMPILE=$(CXX) $(CFLAGS) -c $^ -o $@
LINK_EXE=$(CXX) $(CFLAGS) -o $@ $^

# Create lists of src and object files for src dir
SRC_FILES=$(wildcard $(SRC_DIR)/*.cc)									# Get .c files in source
SRC_OBJS=$(patsubst $(SRC_DIR)/%.cc,$(BIN_DIR)/%.o, $(SRC_FILES))		# Get name of .o files in source

# Create bin directory if it doesn't exist
$(shell if [ ! -d "${BIN_DIR}" ]; then mkdir -p ${BIN_DIR}; fi;)

# A phony target is one that is not really the name of a file;
# rather it is just a name for a recipe to be executed when you make an explicit request
# All targets that generate files should have target name = name of file
# so that make can correctly track if we need to rebuild the target

all: $(BIN_DIR)/$(EXEC)

$(BIN_DIR)/$(EXEC): $(SRC_OBJS)
	$(LINK_EXE)

# Create src object files
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cc
	$(COMPILE)

install:
	mkdir -p $(INSTALL_DIR)
	mkdir -p $(LOG_DIR)
	cp -f $(BIN_DIR)/$(EXEC) $(INSTALL_DIR)
	chmod 755 $(INSTALL_DIR)/$(EXEC)

uninstall:
	rm -f $(INSTALL_DIR)/$(EXEC)
	rm -rdf $(LOG_DIR)

clean:
	rm -rf $(BIN_DIR)/*

.phony: all clean install uninstall
