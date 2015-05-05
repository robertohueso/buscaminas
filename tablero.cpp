struct Casilla{
  bool abierta;
  bool bomba;
  bool marcada;
};

class Tablero{
private:
  Casilla casillas[20][20];
  int filas;
  int columnas;
public:
  //Devuelve el número de filas del tablero
  int Filas(){
    return filas;
  }

  //Devuelve el numero de columnas del tablero
  int Columnas(){
    return columnas;
  }

  //Devuelve el objeto casilla en la posición correspondiente
  Casilla ValoresCasilla(const int &fila, int columna){
    return casillas[fila][columna];
  }

  //Modifica el valor de una casilla en la posición correspondiente
  bool ModificaCasilla(const int &fila, const int &columna, const Casilla &casilla_nueva){
    if(fila < filas && columna < columnas){
      casillas[fila][columna] = casilla_nueva;
      return true;
    }
    else{
      return false;
    }
  }
};
