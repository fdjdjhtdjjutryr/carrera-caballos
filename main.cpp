#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include "caballo.h"

int main() {
    // Configuración inicial
    srand(time(NULL));
    initscr(); 
    cbreak(); 
    noecho(); 
    curs_set(0);

    // Validación de tamaño)
    int rows, cols;
    getmaxyx(stdscr, rows, cols);
    if (cols < META + 20) {
        endwin();
        printf("Error: La terminal es muy pequeña.\n");
        printf("Se necesitan al menos %d columnas (actualmente tienes %d).\n", META + 20, cols);
        printf("Por favor, maximiza la ventana e intenta de nuevo.\n");
        return 1;
    }

    // Inicialización 
    const int num_caballos = 4;
    Caballo competidores[num_caballos];
    
    for(int i = 0; i < num_caballos; i++) {
        sprintf(competidores[i].nombre, "Caballo %d", i + 1);
        competidores[i].posicion = 0;
    }

    hipodromo(competidores, num_caballos);
    mvprintw(10, 0, "Presione cualquier tecla para iniciar la carrera...");
    refresh();
    getch();

    // Inicia la carerra
    int indice_ganador = correr(competidores, num_caballos);
    
    // Ganador de la carrera
    ganador(competidores[indice_ganador]);

    endwin();
    return 0;
}