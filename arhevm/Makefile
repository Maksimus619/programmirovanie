CC = gcc
CFLAGS = -Wall -Wextra -std=c99

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

LIB_NAME = mySimpleComputer
LIB = $(BIN_DIR)/lib$(LIB_NAME).a

PR01_SRC = $(SRC_DIR)/pr01.c
PR01_OBJ = $(OBJ_DIR)/pr01.o
PR01_BIN = $(BIN_DIR)/pr01

.PHONY: all clean

all: $(LIB) $(PR01_BIN)

$(LIB): $(OBJ)
    ar rcs $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
    $(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
    mkdir -p $(OBJ_DIR)

$(PR01_BIN): $(PR01_OBJ) $(LIB) | $(BIN_DIR)
    $(CC) $(CFLAGS) $< -L$(BIN_DIR) -l$(LIB_NAME) -o $@

$(BIN_DIR):
    mkdir -p $(BIN_DIR)

clean:
    rm -rf $(OBJ_DIR) $(BIN_DIR)
