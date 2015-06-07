//Por Manuel Orantes Taboada
//Por Roberto Hueso Gomez
//Universidad de Granada - 2015 - Doble grado Informática y Matemáticas
//----------------------------------------------------------------------

#include <iostream>
#include <cstdlib>
#include <cstring>
#include "campominas.h"

using namespace std;

static const int TAM_MAX_LINEA = 100;

//Analiza la acción a tomar en cada caso
bool AnalizaComando(char *texto, CampoMinas &tablero){
  char *palabras[TAM_MAX_LINEA];
  int i = 0;
  palabras[0] = texto;
  int cuenta = 1;
  while(texto[i] != '\0'){
    texto[i] = tolower(texto[i]);
    if(isspace(texto[i])){
      palabras[cuenta]= texto+i+1;
      texto[i] = '\0';
      cuenta++;
    }
    i++;
  }

  //Elecciones
  if(strcmp(palabras[0],"a") == 0 || strcmp(palabras[0],"abrir") == 0)
    tablero.AbreCasilla(atoi(palabras[1]),atoi(palabras[2]));
  else if(strcmp(palabras[0],"m") == 0 || strcmp(palabras[0],"marcar") == 0)
    tablero.MarcaCasilla(atoi(palabras[1]),atoi(palabras[2]));
  else if(strcmp(palabras[0],"s") == 0 || strcmp(palabras[0],"salvar") == 0)
    tablero.Escribir(palabras[1]);
  else{
    cout << "Error, introduzca la orden de nuevo!\n";
    return false;
  }
  return true;
}

//Programa principal
int main(int argc, char *argv[]){
  int filas, columnas, cantidad_bombas;
  char accion;
  char comandos[TAM_MAX_LINEA];
  CampoMinas tablero(5, 5, 5);
  if(argc == 4){
    filas = atoi(argv[1]);
    columnas = atoi(argv[2]);
    cantidad_bombas = atoi(argv[3]);
    if(filas >= 4 && columnas >= 4 && cantidad_bombas > 0 && cantidad_bombas < (filas*columnas)){
      CampoMinas tablero2(filas, columnas, cantidad_bombas);
      tablero = tablero2;
    }else
      return 0;
  }else if(argc == 2){
    tablero.Leer(argv[1]);
  }else{
    cout << "Error! Introduzca 3 parámetros (filas, columnas, numero de minas) " <<
            "o el nombre de un archivo con una partida guardada para iniciar " <<
            "el juego \n";
            return 0;
  }

  tablero.ImprimeTablero();
  cout << "\n\n";
  tablero.ImprimeTableroSinOcultar();
  while(!tablero.ComprobarPartidaGanada() && !tablero.ComprobarExplosion()){
    cout << "Introduzca comando: ";
    cin.getline(comandos, TAM_MAX_LINEA);
    AnalizaComando(comandos, tablero);
    tablero.ImprimeTablero();
  }

  if(tablero.ComprobarPartidaGanada()){
    cout << "\n¡Felicidades! ¡Has ganado!";
  }else{
    cout << "\n¡Perdiste!";
  }
  cout << "\n";
  tablero.ImprimeTableroSinOcultar();
  return 0;
}
