#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include "caballo.h"
#include <pthread.h>

int main() {
    // Configuración inicial
    srand(time(NULL));
    initscr(); 
    cbreak(); 
    noecho(); 
    curs_set(0);

    

    // Validacion de tamaño
    int rows, cols;
    getmaxyx(stdscr, rows, cols);
    if (cols < META + 20) {
        endwin();
        printf("Error: La terminal es muy pequeña.\n");
        printf("Se necesitan al menos %d columnas (actualmente tienes %d).\n", META + 20, cols);
        printf("Por favor, maximiza la ventana e intenta de nuevo.\n");
        return 1;
    }

    // Inicializacion 
    int num_caballos;
    int largoPista;
    int numVueltas;

    Caballo competidores[7];

    preparar_carrera(
        competidores,
        num_caballos,
        largoPista,
        numVueltas
    );

    pthread_t hilos[num_caballos];
    HiloCaballo datos[num_caballos];
    printf("\n");
    printf("Pista: %d metros\n", largoPista);
    printf("Vueltas: %d\n", numVueltas);
    printf("Meta total: %d metros\n", largoPista * numVueltas);
    hipodromo(competidores, num_caballos, largoPista);
    mvprintw((num_caballos * 2) + 2, 0, "Presione cualquier tecla para iniciar la carrera...");
    refresh();
    getch();

    // crear hilos
    for(int i = 0; i < num_caballos; i++){
        datos[i] = { &competidores[i], largoPista, numVueltas };
        pthread_create(&hilos[i], NULL, correrCaballo, &datos[i]);
    }
    bool todosTerminaron = false;

    while(!todosTerminaron){
        hipodromo(competidores, num_caballos, largoPista);

        todosTerminaron = true;
        int metaFinal = largoPista * numVueltas;

        for(int i = 0; i < num_caballos; i++){
            if(competidores[i].distanciaTotal < metaFinal){
                todosTerminaron = false;
                break;
            }
        }

        napms(100);
    }
    for(int i = 0; i < num_caballos; i++){
    pthread_join(hilos[i], NULL);
    }

    extern int ganadorGlobal;


    // Inicia la carrera
    //int indice_ganador = correr(competidores,num_caballos,largoPista,numVueltas);

    // Ganador de la carrera
    ganador(competidores[ganadorGlobal],num_caballos);

    endwin();
    return 0;
}