#include "tablero.h"

//Implementación de métodos de la clase Tablero

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
  //Defino una casilla por defecto que será devuelta
  //en caso de que los valores fila o columna
  //no sean válidos.
  Casilla casilla_default;
  casilla_default.bomba = false;
  casilla_default.abierta = false;
  casilla_default.marcada = false;

  //Devuelve la casilla
  if((fila < filas && columna < columnas) && (fila >= 0 && columna >= 0))
    return casillas[fila][columna];
  else
    return casilla_default;
}

bool Tablero::ModificaCasilla(const int &fila, const int &columna, const Casilla &casilla_nueva){
  //Devuelve true si la operación se completa correctamente,
  //false en caso contrario.
  if((fila < filas && columna < columnas) && (fila >= 0 && columna >= 0)){
    casillas[fila][columna] = casilla_nueva;
    return true;
  }
  else
    return false;
}
