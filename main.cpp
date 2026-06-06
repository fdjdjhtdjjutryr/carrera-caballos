#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include "caballo.h"

int main() {
    srand(time(NULL));
    char opcionContinuar = 's';

    while (opcionContinuar == 's' || opcionContinuar == 'S') {
        int num_caballos;
        int largoPista;
        int numVueltas;
        Caballo competidores[7];

        preparar_carrera(competidores, num_caballos, largoPista, numVueltas);

        initscr(); 
        cbreak(); 
        noecho(); 
        curs_set(0);

        int filasTerminal, columnasTerminal;
        getmaxyx(stdscr, filasTerminal, columnasTerminal);
        if (columnasTerminal < (largoPista + 25) || filasTerminal < (num_caballos * 3 + 20)) {
            endwin();
            printf("Error: La terminal es excesivamente pequeña para esta configuración.\n");
            printf("Maximice la ventana o elija parámetros de pista inferiores.\n");
            return 1;
        }

        hipodromo(competidores, num_caballos, largoPista);
        mvprintw(6 + (num_caballos * 2), 0, "Presione cualquier tecla para iniciar la carrera...");
        refresh();
        getch();

        pthread_t hilos[num_caballos];
        HiloCaballo datosHilos[num_caballos];

        for(int i = 0; i < num_caballos; i++){
            datosHilos[i] = { &competidores[i], largoPista, numVueltas };
            pthread_create(&hilos[i], NULL, correrCaballo, &datosHilos[i]);
        }

        bool banderaTodosTerminaron = false;
        int metaFinal = largoPista * numVueltas;

        while(!banderaTodosTerminaron){
            hipodromo(competidores, num_caballos, largoPista);
            
            banderaTodosTerminaron = true;
            for(int i = 0; i < num_caballos; i++){
                if(competidores[i].distanciaTotal < metaFinal){
                    banderaTodosTerminaron = false;
                    break;
                }
            }
            napms(50); 
        }

        for(int i = 0; i < num_caballos; i++){
            pthread_join(hilos[i], NULL);
        }

        hipodromo(competidores, num_caballos, largoPista);

        // Importar las variables de control de orden global desde caballo.cpp
        extern int ordenLlegada[7];
        extern int cuentaTerminados;

        // Mostrar resultados con la tabla completa de posiciones
        presentar_resultado(competidores, num_caballos, ordenLlegada, cuentaTerminados, largoPista, numVueltas);
        
        echo();
        curs_set(1);
        opcionContinuar = getch();
        noecho();
        curs_set(0);

        endwin(); 
    }

    return 0;
}