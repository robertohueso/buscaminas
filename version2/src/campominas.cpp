#include "campominas.h"
#include <cstdlib>
#include <iostream>
#include <ctime>

using namespace std;

//Símbolo UNICODE para una bomba.
static const char *SIMBOLO_BOMBA = "💣";

struct CeldaPosicion{
  int fila;
  int columna;
  CeldaPosicion *siguiente_celda;
};

CampoMinas::CampoMinas(const int &filas, const int &columnas, int numero_minas)
  :tablero(filas, columnas)
{
  Casilla casilla_default;
  casilla_default.abierta = false;
  casilla_default.bomba = false;
  casilla_default.marcada = false;
  //Rellena las casillas con el valor por defecto
  for(int i = 0; i < filas; i++){
    for(int j = 0; j < columnas; j++){
      tablero.ModificaCasilla(i, j, casilla_default);
    }
  }

  //Criterio de maximos y minimos de minas
  if(numero_minas < 5){
    numero_minas = 5;
  }else if(numero_minas > (filas*columnas)/2){
    numero_minas = (filas*columnas)/2;
  }

  //Posiciona las minas aleatoriamente (Usa la librería ctime y cstdlib)
  int aleatorio_fila, aleatorio_columna, i;
  srand(time(NULL));
  casilla_default.bomba = true;
  i = 0;
  while(i < numero_minas){
    aleatorio_fila = rand()%tablero.Filas();
    aleatorio_columna = rand()%tablero.Columnas();
    if(tablero.ValoresCasilla(aleatorio_fila,aleatorio_columna).bomba == false){
      tablero.ModificaCasilla(aleatorio_fila, aleatorio_columna, casilla_default);
      i++;
    }
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

  for(int i = 0; i < tablero.Filas(); i++){
    for(int j = 0; j < tablero.Columnas(); j++){
      casilla_actual = tablero.ValoresCasilla(i, j);
      if(casilla_actual.bomba == true && casilla_actual.abierta == true)
        return true;
    }
  }
  return false;
}

bool CampoMinas::ComprobarPartidaGanada(){
  Casilla casilla_actual;

  for(int i = 0; i < tablero.Filas(); i++){
    for(int j = 0; j < tablero.Columnas(); j++){
      casilla_actual = tablero.ValoresCasilla(i, j);
      if(casilla_actual.abierta == false && casilla_actual.bomba == false)
        return false;
    }
  }
  return true;
}

bool CampoMinas::MarcaCasilla(const int &fila, const int &columna){
  Casilla casilla_actual = tablero.ValoresCasilla(fila, columna);
  if(casilla_actual.abierta == false){
    if(casilla_actual.marcada == false){
      casilla_actual.marcada = true;
    }else{
      casilla_actual.marcada = false;
    }

    //Comprueba que está en el rango de la tabla (Modifica casilla)
    if(tablero.ModificaCasilla(fila, columna, casilla_actual))
      return true;
    else
      return false;
  }else
    return false;
}

bool CampoMinas::AbreCasilla(const int &fila, const int &columna){
  Casilla casilla_abierta;
  CeldaPosicion *pend = new CeldaPosicion;
  pend->fila = fila;
  pend->columna = columna;
  pend->siguiente_celda = NULL;

  while(pend != NULL){
    int f = pend->fila;
    int c = pend->columna;
    if(this->NumeroBombasEntorno(f,c) != 0){
      casilla_abierta = tablero.ValoresCasilla(f,c);
      casilla_abierta.abierta = true;
      tablero.ModificaCasilla(f, c, casilla_abierta);
      CeldaPosicion *aux = pend;
      pend = pend->siguiente_celda;
      delete aux;
    }else{
      casilla_abierta = tablero.ValoresCasilla(f,c);
      casilla_abierta.abierta = true;
      tablero.ModificaCasilla(f, c, casilla_abierta);
      CeldaPosicion *aux = pend;
      pend = pend->siguiente_celda;
      delete aux;
      for(int i = f-1; i <= f+1; i++){
        for(int j = c-1; j <= c+1; j++){
          if((i >= 0) && (j >= 0) && (i < tablero.Filas()) && (j < tablero.Columnas()) && (tablero.ValoresCasilla(i,j).abierta == false)){
            CeldaPosicion *aux = new CeldaPosicion;
            aux->fila = i;
            aux->columna = j;
            aux->siguiente_celda = pend;
            pend = aux;
          }
        }
      }
    }
  }
  return true;
}

int CampoMinas::NumeroBombasEntorno(const int &fila, const int &columna){
  int numero_bombas = 0;

  for(int i = fila-1; i <= fila+1; i++){
    for(int j = columna-1; j <= columna+1; j++){
      if(tablero.ValoresCasilla(i, j).bomba == true){
        numero_bombas++;
      }
    }
  }
  //--------------------------------------------------------------------
  //FIXME: Cuenta una bomba de más en caso de explosión
  //pero en principio no parece relevante para el programa.
  //--------------------------------------------------------------------
  return numero_bombas;
}

void CampoMinas::ImprimeTablero(){
  int filas = tablero.Filas();
  int columnas = tablero.Columnas();
  int bombas_entorno;
  Casilla casilla_actual;

  cout << "    ";
  for(int i = 0; i < columnas; i++){
    cout << " " << i << "  ";
  }
  cout << "\n";
  for(int i = 0; i < filas; i++){
    cout << i << "->|";
    for(int j = 0; j < columnas; j++){
      casilla_actual = tablero.ValoresCasilla(i, j);
      if(!casilla_actual.abierta){
        if(!casilla_actual.marcada)
          cout << " * |";
        else
          cout << " ? |";
      }
      else{
        if(casilla_actual.bomba)
          cout <<" "<< SIMBOLO_BOMBA <<" |";
        else{
          bombas_entorno = this->NumeroBombasEntorno(i, j);
          if(bombas_entorno == 0)
            cout << "   |";
          else
            cout << " " << bombas_entorno << " |";
        }
      }

    }
    cout << "\n";
  }
}

void CampoMinas::ImprimeTableroSinOcultar(){
  int filas = tablero.Filas();
  int columnas = tablero.Columnas();
  int bombas_entorno;
  Casilla casilla_actual;

  cout << "    ";
  for(int i = 0; i < columnas; i++){
    cout << " " << i << "  ";
  }
  cout << "\n";
  for(int i = 0; i < filas; i++){
    cout << i << "->|";
    for(int j = 0; j < columnas; j++){
      casilla_actual = tablero.ValoresCasilla(i, j);
        if(casilla_actual.bomba)
          cout << " " << SIMBOLO_BOMBA << " |";
        else{
          bombas_entorno = this->NumeroBombasEntorno(i, j);
          if(bombas_entorno == 0)
            cout << "   |";
          else
            cout << " " << bombas_entorno << " |";
        }
      }
    cout << "\n";
  }
}
