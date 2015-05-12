#include "tablero.h"

//Métodos de la clase Tablero

//Constructor
Tablero::Tablero(const int &filas_utiles, const int &columnas_utiles){
  filas = filas_utiles;
  columnas = columnas_utiles;
  if(filas_utiles < 5)
    filas = 5;
  if(columnas_utiles < 5)
    columnas = 5;
}

int Tablero::Filas(){
  return filas;
}

int Tablero::Columnas(){
  return columnas;
}

Casilla Tablero::ValoresCasilla(const int &fila, const int &columna){
  Casilla casilla_default;
  casilla_default.bomba = false;
  casilla_default.abierta = false;
  casilla_default.marcada = false;
  if((fila < filas && columna < columnas) && (fila >= 0 && columna >= 0)){
    return casillas[fila][columna];
  }else{
    return casilla_default;
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
