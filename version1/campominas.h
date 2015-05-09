#include "tablero.h"

class CampoMinas{
private:
  Tablero tablero(filas, columnas);

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
};
