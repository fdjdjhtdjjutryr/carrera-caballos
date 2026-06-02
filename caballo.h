#ifndef CABALLO_H
#define CABALLO_H

#include <ncurses.h>

#define META 100
#define MAX_NOMBRE 20

struct Caballo {
    char nombre[MAX_NOMBRE];
    int posicion;
    int vueltas;
    int distanciaTotal;
};

void hipodromo(Caballo c[], int n, int largoPista);
void mover(Caballo &c, int largoPista);
int correr(Caballo c[], int n, int largoPista, int numVueltas);
void ganador(Caballo &c, int n);

#endif