#ifndef CABALLO_H
#define CABALLO_H

#include <ncurses.h>
#include <pthread.h>

#define MAX_NOMBRE 20

struct Caballo {
    int id; 
    char nombre[MAX_NOMBRE];
    int posicion;
    int vueltas;
    int distanciaTotal;
    bool termino;
};

struct HiloCaballo {
    Caballo* caballo;
    int largoPista;
    int numVueltas;
};

// Declaración de funciones del sistema
void hipodromo(Caballo c[], int n, int largoPista);
void mover(Caballo &c, int largoPista);
void* correrCaballo(void* arg);
void presentar_resultado(Caballo c[], int n, int ordenLlegada[], int totalTerminados, int largoPista, int numVueltas);
void preparar_carrera(Caballo c[], int &numCaballos, int &largoPista, int &numVueltas);

#endif