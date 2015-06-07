#include "campominas.h"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

//Símbolo UNICODE para una bomba.
static const char *SIMBOLO_BOMBA = "💣";
static const char *MAGIC_STRING = "#MP−BUSCAMINAS−V1.0";

struct CeldaPosicion{
  int fila;
  int columna;
  CeldaPosicion *siguiente_celda;
};

CampoMinas::CampoMinas(const int &filas, const int &columnas, int numero_minas)
  :tablero(filas, columnas)
{
  explosion = false;
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
  srand(time(NULL));  //Inicializa el generador aleatorio
  casilla_default.bomba = true;
  i = 0;
  while(i < numero_minas){
    aleatorio_fila = rand()%tablero.Filas();
    aleatorio_columna = rand()%tablero.Columnas();
    if(tablero(aleatorio_fila, aleatorio_columna).bomba == false){
      tablero.ModificaCasilla(aleatorio_fila, aleatorio_columna, casilla_default);
      i++;
    }
  }
}

int CampoMinas::Filas() const{
  return tablero.Filas();
}

int CampoMinas::Columnas() const{
  return tablero.Columnas();
}

bool CampoMinas::ComprobarExplosion() const{
  return explosion;
}

bool CampoMinas::ComprobarPartidaGanada(){
  Casilla casilla_actual;

  for(int i = 0; i < tablero.Filas(); i++){
    for(int j = 0; j < tablero.Columnas(); j++){
      casilla_actual = tablero(i, j);
      if(casilla_actual.abierta == false && casilla_actual.bomba == false)
        return false;
    }
  }
  return true;
}

bool CampoMinas::MarcaCasilla(const int &fila, const int &columna){
  Casilla casilla_actual = tablero(fila, columna);
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
    casilla_abierta = tablero(f,c);
    if(casilla_abierta.marcada == false){
      casilla_abierta.abierta = true;
      tablero.ModificaCasilla(f, c, casilla_abierta);
      if(casilla_abierta.bomba == true)
        explosion = true;
    }
    CeldaPosicion *aux = pend;
    pend = pend->siguiente_celda;
    delete aux;

    if(NumeroBombasEntorno(f,c) == 0){
      for(int i = f-1; i <= f+1; i++){
        for(int j = c-1; j <= c+1; j++){
          if(tablero.DentroDelTablero(i,j) && (tablero(i,j).abierta == false) && tablero(i,j).marcada == false){
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
      if(tablero.DentroDelTablero(i,j) && tablero(i, j).bomba == true){
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

void CampoMinas::ImprimeTablero(std::ostream& os){
  int filas = tablero.Filas();
  int columnas = tablero.Columnas();
  int bombas_entorno;
  Casilla casilla_actual;

  os << "    ";
  for(int i = 0; i < columnas; i++){
    os << " " << i << "  ";
  }
  os << "\n";
  for(int i = 0; i < filas; i++){
    os << i << "->|";
    for(int j = 0; j < columnas; j++){
      casilla_actual = tablero(i, j);
      if(!casilla_actual.abierta){
        if(!casilla_actual.marcada)
          os << " * |";
        else
          os << " ? |";
      }
      else{
        if(casilla_actual.bomba)
          os <<" "<< SIMBOLO_BOMBA <<" |";
        else{
          bombas_entorno = NumeroBombasEntorno(i, j);
          if(bombas_entorno == 0)
            os << "   |";
          else
            os << " " << bombas_entorno << " |";
        }
      }

    }
    os << "\n";
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
      casilla_actual = tablero(i,j);
        if(casilla_actual.bomba)
          cout << " " << SIMBOLO_BOMBA << " |";
        else{
          bombas_entorno = NumeroBombasEntorno(i, j);
          if(bombas_entorno == 0)
            cout << "   |";
          else
            cout << " " << bombas_entorno << " |";
        }
      }
    cout << "\n";
  }
}

bool CampoMinas::Escribir(const char *nombre_fichero){
  std::ofstream fichero(nombre_fichero, ios::trunc | ios::out);
  if(fichero){
    fichero << MAGIC_STRING << "\n";
    fichero << tablero;
    fichero.close();
    return true;
  }
  else{
    return false;
  }
}

bool CampoMinas::Leer(const char *nombre_fichero){
  std::ifstream fichero(nombre_fichero, ios::in);
  int fils, cols;
  char flujo[1000];
  fichero >> flujo;
  if(strcmp(flujo, MAGIC_STRING) != 0)
    return false;
  fichero >> fils;
  fichero >> cols;
  Tablero tablero_nuevo(fils,cols);
  for(int i = 0; i < fils; i++){
    for(int j = 0; j < cols; j++){
      Casilla casilla_nueva;
      char elemento_casilla;
      bool cast_char_bool[3];
      for(int z = 0; z < 3; z++){
        fichero.width(1);
        fichero >> elemento_casilla;
        if(elemento_casilla == '0')
          cast_char_bool[z] = false;
        else
          cast_char_bool[z] = true;
      }
      casilla_nueva.abierta = cast_char_bool[0];
      casilla_nueva.bomba =  cast_char_bool[1];
      casilla_nueva.marcada = cast_char_bool[2];
      tablero_nuevo.ModificaCasilla(i,j,casilla_nueva);
    }
  }
  tablero = tablero_nuevo;
  return true;
}
