#include "tablero.h"

//Métodos de la clase Tablero

//Constructor
Tablero::Tablero(const int &filas_utiles, const int &columnas_utiles){
  filas = filas_utiles;
  columnas = columnas_utiles;
}

int Tablero::Filas(){
  return filas;
}

int Tablero::Columnas(){
  return columnas;
}

Casilla Tablero::ValoresCasilla(const int &fila, const int &columna){
  if(fila < filas && columna < columnas){
    if(fila >= 0 && columna >= 0){
      return casillas[fila][columna];
    }
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