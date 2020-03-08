CC = gcc
SRC_DIR = ./src

all: $(SRC_DIR)/common.c $(SRC_DIR)/memManager.c $(SRC_DIR)/tlb.c $(SRC_DIR)/pageTable.c
	@mkdir -p ./bin
	$(CC) $(SRC_DIR)/common.c $(SRC_DIR)/memManager.c $(SRC_DIR)/tlb.c $(SRC_DIR)/pageTable.c -o ./bin/a.out