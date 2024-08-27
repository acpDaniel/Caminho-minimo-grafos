CC = g++
CFLAGS = -Wall -I include
SRC_DIR = src/
BIN_DIR = bin/
EXECUTABLE = $(BIN_DIR)tp2.out
SOURCE_FILES = $(SRC_DIR)tpLista.cpp $(SRC_DIR)minHeap.cpp $(SRC_DIR)listaAdjGrafo.cpp

all: 
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(SOURCE_FILES)

lista:
	g++ -I include -o tpLista src/tpLista.cpp src/minHeap.cpp src/listaAdjGrafo.cpp

matriz:
	g++ -I include -o tpMatriz src/tpMatriz.cpp src/minHeap.cpp src/matrizAdjGrafo.cpp

clean:
	rm -rf $(BIN_DIR)*.out