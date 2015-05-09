#include "campominas.h"
#include <cstdlib>

CampoMinas::CampoMinas(const int &filas, const int &columnas, const int &numero_minas){
  Casilla casilla_default;
  casilla_default.abierta = false;
  casilla_default.bomba = false;
  casilla_default.marcada = false;

  //Rellena las casillas con el valor por defecto
  for(int i = 0; i < filas; i++){
    for(int j = 0; j < columnas; j++){
      ModificaCasilla(i, j, casilla_default);
    }
  }

  //Posiciona las minas aleatoriamente
  casilla_default.bomba = true;
  for(int i = 0; i < numero_minas; i++){
    ModificaCasilla(rand()%tablero.Filas(), rand()%tablero.Columnas(), casilla_default);
  }
}

int CampoMinas::Filas(){
  return tablero.Filas();
}

int CampoMinas::Columnas(){
  return tablero.Columnas();
}

bool CampoMinas::ComprobarExplosion(){
  Casilla casilla_actual;

  for(int i = 0; i < this.Filas(); i++){
    for(int j = 0; j < this.Columnas(); j++){
      casilla_actual = tablero.ValoresCasilla(i, j);
      if(casilla_actual.bomba == true && casilla_actual.abierta == true)
        return true;
    }
  }
  return false;
}

bool CampoMinas::ComprobarPartidaGanada(){
  Casilla casilla_actual;

  for(int i = 0; i < this.Filas(); i++){
    for(int j = 0; j < this.Columnas(); j++){
      casilla_actual = tablero.ValoresCasilla(i, j);
      if(casilla_actual.abierta == false && casilla_actual.bomba == false)
        return false;
    }
  }
  return true;
}
