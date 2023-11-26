BINARY 			:= main

LIBRARIES 		:= 

CXX_FLAGS 		:= -std=c++2b -g -ggdb -Wall -Wextra -Wshadow -Werror -Wpedantic -pedantic-errors -MMD -pthread -O0 #-fsanitize=address 
#CXX_FLAGS += `pkg-config --cflags $(LIBRARIES)`

##############################

CXX 			:= clang++ 

BINARY_EXT 		:= exe
SRC_EXT 		:= cpp
OBJ_EXT			:= o
DEP_EXT 		:= d

VPATH 			:= $(shell find . -type d) 

#BIN_DIR			:= ./bin
#SRC_DIR 		:= ./src
#LOC_INC_DIR 	:= ./include
#LOC_LIB_DIR 	:= ./lib
#OBJ_DIR 		:= ./build
BIN_DIR			:= bin
SRC_DIR 		:= src
LOC_INC_DIR 	:= include
LOC_LIB_DIR 	:= lib
OBJ_DIR 		:= build
SYS_INC_DIR 	:= /usr/local/include /usr/include 
SYS_LIB_DIR 	:= /usr/local/lib /usr/lib 

SRC_DIRS 		:= $(shell find $(SRC_DIR) -type d) 
LOC_INC_DIRS 	:= $(shell find $(LOC_INC_DIR) -type d) 
LOC_LIB_DIRS 	:= $(shell find $(LOC_LIB_DIR) -type d) 

LD_FLAGS 		:= #-fsanitize=address
#LD_LIBS 		:= $(addprefix -l,$(LIBRARIES)) $(shell pkg-config --libs $(LIBRARIES))

SYS_LIB_FLAGS 	:= $(addprefix -L,$(SYS_LIB_DIR))
LOC_LIB_FLAGS 	:= $(addprefix -L,$(LOC_LIB_DIRS))
LIB_FLAGS 		:= $(SYS_LIB_FLAGS) $(LOC_LIB_FLAGS)

SYS_INC_FLAGS 	:= $(addprefix -I,$(SYS_INC_DIR))
LOC_INC_FLAGS 	:= $(addprefix -I,$(LOC_INC_DIRS))
INC_FLAGS		:= $(SYS_INC_FLAGS) $(LOC_INC_FLAGS)

SRCS 			:= $(shell find $(SRC_DIR) -type f)
SRC_NAMES		:= $(shell find $(SRC_DIRS) -type f -printf "%f\n")
SRC_NAMES 		:= $(patsubst %.$(SRC_EXT),%,$(SRC_NAMES))

OBJS 			:= $(patsubst %,$(OBJ_DIR)/%.$(OBJ_EXT),$(SRC_NAMES))
DEPS 			:= $(patsubst $(OBJ_DIR)/%.$(OBJ_EXT),$(OBJ_DIR)/%.$(DEP_EXT),$(OBJS))

.PHONY: all debug release build rebuild run clean

all: debug 

bear: 
	bear -- make rebuild

debug: build

release: CXX_FLAGS += -O2
release: clean build clean

build: $(BIN_DIR)/$(BINARY).$(BINARY_EXT) 

# === LINKER COMMANDS ===

$(BIN_DIR)/$(BINARY).$(BINARY_EXT): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) -o $@ $^ $(LD_FLAGS) $(LIB_FLAGS) $(LD_LIBS) 
	@echo

# === COMPILER COMMANDS ===

$(OBJ_DIR)/%.$(OBJ_EXT): %.$(SRC_EXT)
	@mkdir -p $(OBJ_DIR)
	$(CXX) -o $@ -c $< $(CXX_FLAGS) $(INC_FLAGS)
	@echo

clean:
	rm -rf $(OBJ_DIR) $(shell find . -type f -wholename "*.$(DEP_EXT)") $(shell find . -type f -wholename "*.$(OBJ_EXT)") $(shell find . -type f -wholename "*.$(BINARY_EXT)") 

rebuild: clean build

run: build
	$(BIN_DIR)/$(BINARY).$(BINARY_EXT)

-include $(DEPS)
