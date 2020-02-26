CC = gcc
SRC_DIR = ./src

all: $(SRC_DIR)/common.c $(SRC_DIR)/memManager.c $(SRC_DIR)/tlb.c
	@mkdir -p ./bin
	$(CC) $(SRC_DIR)/common.c $(SRC_DIR)/memManager.c $(SRC_DIR)/tlb.c -o ./bin/a.out