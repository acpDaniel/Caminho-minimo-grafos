CC = g++
CFLAGS = -Wall -I include
SRC_DIR = src/
BIN_DIR = bin/
EXECUTABLE = $(BIN_DIR)tp2.out
SOURCE_FILES = $(SRC_DIR)tpLista.cpp $(SRC_DIR)minHeap.cpp $(SRC_DIR)listaAdjGrafo.cpp

all: 
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(SOURCE_FILES)

clean:
	rm -rf $(BIN_DIR)*.out