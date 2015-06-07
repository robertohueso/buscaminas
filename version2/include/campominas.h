#include "tablero.h"
#include <iostream>
#include <fstream>

class CampoMinas{
private:
  Tablero tablero;

  bool explosion;
  //Devuelve la cantidad de bombas que hay en el entorno
  //de una casilla
  inline int NumeroBombasEntorno(const int &fila, const int &columna);

public:
  //Constructor del campo
  CampoMinas(const int &filas, const int &columnas, int numero_minas);

  //Devuelve el numero de filas del campo
  inline int Filas() const;

  //Devuelve el numero de columnas del campo
  inline int Columnas() const;

  //Comprueba si ha explotado alguna mina
  bool ComprobarExplosion() const;

  //Comprueba si la partida se ha ganado
  bool ComprobarPartidaGanada();

  //Marca la casilla (La desmarca en caso de que ya esté marcada)
  bool MarcaCasilla(const int &fila, const int &columna);

  //Abre una casilla
  bool AbreCasilla(const int &fila, const int &columna);

  //Imprime el tablero formateado a través de cout
  void ImprimeTablero(std::ostream& os = std::cout);

  //Imprime el tablero formateado a través de cout sin ocultar nada
  void ImprimeTableroSinOcultar();

  //Guarda el estado a un fichero
  bool Escribir(const char *nombre_fichero);

  //Lee y carga el estado de un tablero
  bool Leer(const char *nombre_fichero);
};
