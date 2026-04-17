#ifndef CABALLO_H
#define CABALLO_H

#include <ncurses.h>

#define META 100
#define MAX_NOMBRE 20

struct Caballo {
    char nombre[MAX_NOMBRE];
    int posicion;
};

void hipodromo(Caballo c[], int n);
void mover(Caballo &c);
int correr(Caballo c[], int n);
void ganador(Caballo &c);

#endif
