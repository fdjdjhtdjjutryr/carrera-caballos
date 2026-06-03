#include "caballo.h"
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <pthread.h>
int ganadorGlobal = -1;//registra el primer caballo que alcanza la meta

void hipodromo(Caballo c[], int n, int largoPista) {
    clear();
    mvprintw(0, 0, "=== CARRERA DE CABALLOS - UCSC ===");
    for (int i = 0; i < n; i++) {
        mvprintw(2 + i * 2, 0, "%-12s", c[i].nombre);
        for (int j = 0; j <= largoPista; j++) mvprintw(2 + i * 2, 13 + j, "-");
        mvprintw(2 + i * 2, 13 + largoPista, "|");
        mvprintw(2 + i * 2, 13 + c[i].posicion, "H");
        mvprintw(i + 3 + n *2, 0,
         "%-12s Vueltas:%d Dist:%d",c[i].nombre,
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

/*int correr(Caballo c[], int n, int largoPista, int numVueltas) {
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
}*/

void* correrCaballo(void* arg){ 
    HiloCaballo* datos = (HiloCaballo*) arg;

    int metaFinal = datos->largoPista * datos->numVueltas;

    while(datos->caballo->distanciaTotal < metaFinal){

        mover(*datos->caballo, datos->largoPista);

        if(!datos->caballo->termino &&
           datos->caballo->distanciaTotal >= metaFinal){

            datos->caballo->termino = true;

            if(ganadorGlobal == -1){
                ganadorGlobal = atoi(datos->caballo->nombre + 8) - 1;
            }
        }

        napms(100);
    }

    pthread_exit(NULL);
}

void ganador(Caballo &c, int n) {
    mvprintw((n * 3) + 4, 0, "*** GANADOR: %s ***", c.nombre);
    mvprintw((n * 3) + 6, 0, "Presiona una tecla para finalizar...");
    refresh();
    getch();
}
void preparar_carrera(
    Caballo c[],
    int &numCaballos,
    int &largoPista,
    int &numVueltas
){
    do {
        printf("Cantidad de caballos (2-7): ");
        scanf("%d", &numCaballos);
    }
    while(numCaballos < 2 || numCaballos > 7);

    do {
        printf("Largo de pista (30,40,50,60): ");
        scanf("%d", &largoPista);
    }
    while(largoPista != 30 && largoPista != 40 && argoPista != 50 && largoPista != 60);

    do {
        printf("Numero de vueltas (1-4): ");
        scanf("%d", &numVueltas);
    }
    while(numVueltas < 1 || numVueltas > 4);

    for(int i = 0; i < numCaballos; i++) {

        sprintf(c[i].nombre,"Caballo %d",i + 1);

        c[i].posicion = 0;
        c[i].vueltas = 0;
        c[i].distanciaTotal = 0;
        c[i].termino = false;
    }
}