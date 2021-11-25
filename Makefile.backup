CC=gcc

SRC_DIR=src
OBJ_DIR=obj
LIB_DIR=lib
BIN_DIR=bin
INC_DIR=include

PGM=dummy_ai/everrust_ai.c
BIN=$(BIN_DIR)/everrust_ai

SRC=$(wildcard $(SRC_DIR)/*.c)
OBJ=$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
LIB=$(LIB_DIR)/libconnsix.a

ARFLAGS=-rv
LDLIBS=-L$(LIB_DIR) -lconnsix

.PHONY: all clean connsix dummy_ai run

all: connsix dummy_ai

connsix: $(LIB)

dummy_ai: $(BIN)

$(BIN): $(PGM) | $(LIB) $(BIN_DIR)
	$(CC) $^ -o $@ -I$(INC_DIR) $(LDLIBS)

$(LIB): $(OBJ) | $(LIB_DIR)
	ar $(ARFLAGS) $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) -c $< -o $@ -I$(INC_DIR)

$(OBJ_DIR) $(LIB_DIR) $(BIN_DIR):
	mkdir -p $@

run: | $(BIN)
	$(BIN)

clean:
	@$(RM) -rv $(OBJ_DIR) $(LIB_DIR) $(BIN_DIR)
