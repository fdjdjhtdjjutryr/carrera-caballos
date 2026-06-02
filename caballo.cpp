#include "caballo.h"
#include <cstdlib>
#include <cstring>
#include <cstdio>

void hipodromo(Caballo c[], int n, int largoPista) {
    clear();
    mvprintw(0, 0, "=== CARRERA DE CABALLOS - UCSC ===");
    for (int i = 0; i < n; i++) {
        mvprintw(2 + i * 2, 0, "%-12s", c[i].nombre);
        for (int j = 0; j <= largoPista; j++) mvprintw(2 + i * 2, 13 + j, "-");
        mvprintw(2 + i * 2, 13 + largoPista, "|");
        mvprintw(2 + i * 2, 13 + c[i].posicion, "H");
        mvprintw(3 + i * 2, 0,
         "Vueltas:%d Dist:%d",
         c[i].vueltas,
         c[i].distanciaTotal);
    }
    refresh();
}

void mover(Caballo &c, int largoPista) {
    c.distanciaTotal += (rand() % 2) + 1;

    c.vueltas = c.distanciaTotal / largoPista;

    c.posicion = c.distanciaTotal % largoPista;
}

int correr(Caballo c[], int n, int largoPista, int numVueltas) {
     int metaFinal = largoPista * numVueltas;
    while (true) {
        for (int i = 0; i < n; i++) {
            mover(c[i], largoPista);

            if(c[i].distanciaTotal >= metaFinal) {
                hipodromo(c, n, largoPista);
                return i;
            }
        }
        hipodromo(c, n, largoPista);
        napms(100);
    }
}

void ganador(Caballo &c, int n) {
    mvprintw((n * 2) + 2, 0, "*** GANADOR: %s ***", c.nombre);
    mvprintw((n * 2) + 4, 0, "Presiona una tecla para finalizar...");
    refresh();
    getch();
}