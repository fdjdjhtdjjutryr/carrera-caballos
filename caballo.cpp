#include <ncurses.h>
#include <cstdlib>
#include <cstring>

#define META 150
#define MAX_NOMBRE 20

struct Caballo {
    char nombre[MAX_NOMBRE];
    int  posicion =0;
};


void mover(Caballo &c) {
        c.posicion += (rand() % 2) + 1;
        if (c.posicion > META)
            c.posicion = META;
}

bool gano(Caballo &c) {
        return c.posicion >= META;
}

void hipodromo(Caballo c[], int n) {
    clear();
    mvprintw(0, 0, "=== CARRERA DE CABALLOS ===");
    for (int i = 0; i < n; i++) {
        mvprintw(2 + i * 2, 0, "%s", c[i].nombre);
        for (int j = 0; j <= META; j++)
        mvprintw(2 + i * 2, 12 + j, "-");
        mvprintw(2 + i * 2, 12 + META, "|");
        mvprintw(2 + i * 2, 12 + c[i].posicion, "H");
    }
    refresh();
}

int correr(Caballo c[], int n) {
    while (true) {
        for (int i = 0; i < n; i++) {
            mover(c[i]);
            if (gano(c[i])) {
                hipodromo(c, n);
                return i;
            }
        }
        hipodromo(c, n);
        napms(100);
    }
}

void ganador(Caballo &c) {
    mvprintw(10, 0, "*** GANADOR: %s ***  (presiona una tecla)", c.nombre);
    refresh();
    getch();
}
