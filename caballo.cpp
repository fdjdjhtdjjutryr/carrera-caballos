#include "caballo.h"
#include <cstdlib>
#include <cstring>
#include <cstdio>

void hipodromo(Caballo c[], int n) {
    clear();
    mvprintw(0, 0, "=== CARRERA DE CABALLOS - UCSC ===");
    for (int i = 0; i < n; i++) {
        mvprintw(2 + i * 2, 0, "%-12s", c[i].nombre);
        for (int j = 0; j <= META; j++) mvprintw(2 + i * 2, 13 + j, "-");
        mvprintw(2 + i * 2, 13 + META, "|");
        mvprintw(2 + i * 2, 13 + c[i].posicion, "H");
    }
    refresh();
}

void mover(Caballo &c) {
    c.posicion += (rand() % 2) + 1;
    if (c.posicion > META) c.posicion = META;
}

int correr(Caballo c[], int n) {
    while (true) {
        for (int i = 0; i < n; i++) {
            mover(c[i]);
            if (c[i].posicion >= META) {
                hipodromo(c, n);
                return i;
            }
        }
        hipodromo(c, n);
        napms(100);
    }
}

void ganador(Caballo &c) {
    mvprintw(12, 0, "*** GANADOR: %s ***", c.nombre);
    mvprintw(13, 0, "Presiona una tecla para finalizar...");
    refresh();
    getch();
}
