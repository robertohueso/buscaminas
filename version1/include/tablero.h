//Datos de tipo Casilla
struct Casilla{
  bool abierta;
  bool bomba;
  bool marcada;
};

//Datos de clase Tablero
class Tablero{
private:
  Casilla casillas[20][20];
  int filas;
  int columnas;

public:
  //Metodo constructor
  Tablero(const int &filas, const int &columnas);

  //Devuelve el número de filas del tablero
  int Filas() const;

  //Devuelve el numero de columnas del tablero
  int Columnas() const;

  //Devuelve el objeto casilla en la posición correspondiente
  Casilla ValoresCasilla(const int &fila, const int &columna) const;

  //Modifica el valor de una casilla en la posición correspondiente
  bool ModificaCasilla(const int &fila, const int &columna, const Casilla &casilla_nueva);
};
