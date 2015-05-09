#include "tablero.h"

//Métodos de la clase Tablero

int Tablero::Filas(){
  return filas;
}

int Tablero::Columnas(){
  return columnas;
}

Casilla Tablero::ValoresCasilla(const int &fila, const int &columna){
  if(fila < filas && columna < columnas){
    return casillas[fila][columna];
  }
}

bool Tablero::ModificaCasilla(const int &fila, const int &columna, const Casilla &casilla_nueva){
  if(fila < filas && columna < columnas){
    casillas[fila][columna] = casilla_nueva;
    return true;
  }
  else{
    return false;
  }
}
