CC=g++
CFLAGS=-Wall -c
BIN=bin
SRC=src
INC=include
OBJ=obj
CXXFLAGS=-I$(INC)

all: $(BIN)/buscaminas

$(BIN)/buscaminas: $(OBJ)/campominas.o $(OBJ)/tablero.o
	$(CC) $(CXXFLAGS) $(OBJ)/campominas.o $(OBJ)/tablero.o -o $(BIN)/buscaminas $(SRC)/buscaminas.cpp

$(OBJ)/campominas.o: $(SRC)/campominas.cpp $(INC)/campominas.h $(OBJ)/tablero.o
	$(CC) $(CFLAGS) $(CXXFLAGS) -o $(OBJ)/campominas.o $(SRC)/campominas.cpp

$(OBJ)/tablero.o: $(SRC)/tablero.cpp $(INC)/tablero.h
	$(CC) $(CFLAGS) $(CXXFLAGS) -o $(OBJ)/tablero.o $(SRC)/tablero.cpp

clean:
	rm $(OBJ)/*
mrproper:
	rm $(OBJ)/*
	rm $(BIN)/*
