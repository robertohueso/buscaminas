#include <fstream>

//Datos de tipo Casilla
struct Casilla{
  bool abierta;
  bool bomba;
  bool marcada;
};

//Datos de clase Tablero
class Tablero{
private:
  Casilla **casillas;
  int filas;
  int columnas;

public:
  //Metodo constructor
  Tablero(const int &filas, const int &columnas);

  //Destructor
  ~Tablero();

  //Constructor de copia
  Tablero(const Tablero &tablero_input);

  //Operador de asignacion sobrecargado
  Tablero& operator=(const Tablero &tablero_input);

  //Devuelve el número de filas del tablero
  int Filas() const;

  //Devuelve el numero de columnas del tablero
  int Columnas() const;

  //Devuelve el objeto casilla en la posición correspondiente
  //DEPRECATED!
  Casilla ValoresCasilla(const int &fila, const int &columna) const;

  //Modifica el valor de una casilla en la posición correspondiente
  bool ModificaCasilla(const int &fila, const int &columna, const Casilla &casilla_nueva);

  //Comprueba si un elemento está dentro del tablero
  bool DentroDelTablero(const int &fila, const int &columna) const;

  //Sobrecarga parentesis para ValorCasilla
  Casilla& operator()(const int &fila, const int &columna) const;
};

//Implementacion E/S

//Flujo de salida con el estado de cada casilla
std::ostream& operator<<(std::ostream &os, const Casilla &casilla_actual);
