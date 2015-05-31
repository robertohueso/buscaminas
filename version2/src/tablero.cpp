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
  //Reserva memoria y crea la matriz de Casillas
  casillas = new Casilla*[filas];
  for(int i = 0; i < columnas; i++)
    casillas[i] = new Casilla;
}

//Destructor
Tablero::~Tablero(){
  for(int i = 0; i < columnas; i++)
    delete[] casillas[i];
  delete[] casillas;
}

//Constructor de copia
Tablero::Tablero(const Tablero &tablero_input){
  filas = tablero_input.Filas();
  columnas = tablero_input.Columnas();

  casillas = new Casilla*[filas];
  for(int i = 0; i < columnas; i++)
    casillas[i] = new Casilla;

  for(int i = 0; i < filas; i++)
    for(int j = 0; j < columnas; j++)
      casillas[i][j] = tablero_input.ValoresCasilla(i,j);
}

//Sobrecarga del operador de asignacion
Tablero& Tablero::operator=(const Tablero &tablero_input){
  //Vaciamos la memoria
  for(int i = 0; i < this->columnas; i++)
    delete[] this->casillas[i];
  delete[] this->casillas;

  //Rellenamos con tablero_input
  this->filas = tablero_input.Filas();
  this->columnas = tablero_input.Columnas();
  this->casillas = new Casilla*[filas];
  for(int i = 0; i < columnas; i++)
    this->casillas[i] = new Casilla;

  for(int i = 0; i < filas; i++)
    for(int j = 0; j < columnas; j++)
      this->casillas[i][j] = tablero_input.ValoresCasilla(i,j);

  return *this;
}

int Tablero::Filas() const{
  return filas;
}

int Tablero::Columnas() const{
  return columnas;
}

Casilla Tablero::ValoresCasilla(const int &fila, const int &columna) const{
  return casillas[fila][columna];
}

bool Tablero::ModificaCasilla(const int &fila, const int &columna, const Casilla &casilla_nueva){
  //Devuelve true si la operación se completa correctamente,
  //false en caso contrario.
  if(DentroDelTablero(fila, columna)){
    casillas[fila][columna] = casilla_nueva;
    return true;
  }
  else
    return false;
}

bool Tablero::DentroDelTablero(const int &fila, const int &columna) const{
  if(fila >= 0 && columna >= 0 && fila < filas && columna < columnas)
    return true;
  else
    return false;
}

Casilla& Tablero::operator()(const int &fila, const int &columna) const{
  return casillas[fila][columna];
}
/*
std::ostream& operator<<(std::ostream &os, const Casilla &casilla_actual) const{
  if(casilla_actual.abierta)
    os << 1;
  else
    os << 0;

  if(casilla_actual.bomba)
    os << 1;
  else
    os << 0;

  if(casilla_actual.marcada)
    os << 1;
  else
    os << 0;
  return os;
}

std::ostream& operator<<(std::ostream &os, const Tablero &tablero_actual) const{
  os << tablero_actual.Filas() << '\n';
  os << tablero_actual.Columnas() << '\n';
  for(int i = 0; i < tablero_actual.Filas(); i++)
    for(int j = 0; j < tablero_actual.Columnas(); j++)
      os << tablero(i,j) << ',';
  return os;
}
*/
