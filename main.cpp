#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include "caballo.cpp"

int main() {
    srand(time(NULL));
    initscr(); cbreak(); noecho(); curs_set(0);

    Caballo c[4];
    strcpy(c[0].nombre, "Caballo 1"); c[0];
    strcpy(c[1].nombre, "Caballo 2");   c[1];
    strcpy(c[2].nombre, "Caballo 3");    c[2];
    strcpy(c[3].nombre, "Caballo 4");    c[3];   

    int caballo_ganador = correr(c, 4);
    ganador(c[caballo_ganador]);

    endwin();
    return 0;
}
