# make all
# make clean
# make program
# make build
# make release
# make debug
# make info


CC = g++
INCLUDE = -I./include
CPPFLAGS = -Wall -fexceptions
RELEASE_FLAGS = -O2
DEBUG_FLAGS = -pedantic-errors -Wextra -Weffc++ -g
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
BUILD = ./build
OBJ_DIR = ${BUILD}/objs
BIN_DIR = ${BUILD}/bin
TARGET = program

SRC = $(wildcard src/*.cpp)
OBJECTS  = $(SRC:src/%.cpp=$(OBJ_DIR)/%.o)
DEPENDENCIES := $(OBJECTS:.o=.d) 						\


all: build $(BIN_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: src/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(INCLUDE) -c $< -MMD -o $@

$(BIN_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) -o $(BIN_DIR)/$(TARGET) $^ $(LDFLAGS)

-include $(DEPENDENCIES)

# tells make that these commands are special targets (not associated with actual files)
.PHONY: all build clean debug release info

build:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CPPFLAGS += ${DEBUG_FLAGS}
debug: all

release: CPPFLAGS += ${RELEASE_FLAGS}
release: all

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(BIN_DIR)/*

info:
	@echo "[*] Application dir: ${BIN_DIR}     "
	@echo "[*] Object dir:      ${OBJ_DIR}     "
	@echo "[*] Sources:         ${SRC}         "
	@echo "[*] Objects:         ${OBJECTS}     "
	@echo "[*] Dependencies:    ${DEPENDENCIES}"
