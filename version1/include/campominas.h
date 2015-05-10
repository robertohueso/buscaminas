#include "tablero.h"

class CampoMinas{
private:
  Tablero tablero(filas, columnas);

  //Devuelve la cantidad de bombas que hay en el entorno
  //de una casilla
  int NumeroBombasEntorno(const int &fila, const int &columna);

public:
  //Constructor del campo
  CampoMinas CampoMinas(const int &filas, const int &columnas, const int &numero_minas);

  //Devuelve el numero de filas del campo
  int Filas();

  //Devuelve el numero de columnas del campo
  int Columnas();

  //Comprueba si ha explotado alguna mina
  bool ComprobarExplosion();

  //Comprueba si la partida se ha ganado
  bool ComprobarPartidaGanada();

  //Marca la casilla (La desmarca en caso de que ya esté marcada)
  bool MarcaCasilla(const int &fila, const int &columna);

  //Abre una casilla
  bool AbreCasilla(const int &fila, const int &columna);

  //Imprime el tablero formateado a través de cout
  void ImprimeTablero();

  //Imprime el tablero formateado a través de cout sin ocultar nada
  void ImprimeTableroSinOcultar();
};
