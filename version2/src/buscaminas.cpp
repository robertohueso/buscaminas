//Por Manuel Orantes Taboada
//Por Roberto Hueso Gomez

#include <iostream>
#include "campominas.h"

using namespace std;

int main(){
  int filas, columnas, cantidad_bombas;
  char accion;

  cout << "Introduzca la dimensión (Filas y columnas): ";
  //Lee filas y columnas separadas por un espacio.
  cin >> filas >> columnas;
  cout << "Introduzca las minas: ";
  cin >> cantidad_bombas;

  CampoMinas tablero(filas, columnas, cantidad_bombas);
  tablero.ImprimeTablero();
  cout << "\n\n";
  tablero.ImprimeTableroSinOcultar();
  while(!tablero.ComprobarPartidaGanada() && !tablero.ComprobarExplosion()){
    cout << "Introduzca acción (a/m) y posición (fila columna): ";
    cin >> accion >> filas >> columnas;

    if(accion == 'm')
      tablero.MarcaCasilla(filas,columnas);
    else if(accion == 'a')
      tablero.AbreCasilla(filas, columnas);
    else
      cout << "\n¡Comando no válido!\n";
    tablero.ImprimeTablero();
  }

  if(tablero.ComprobarPartidaGanada()){
    cout << "\n¡Felicidades! ¡Has ganado!";
  }else{
    cout << "\n¡Perdiste!";
  }
  cout << "\n";
  tablero.ImprimeTableroSinOcultar();
}
