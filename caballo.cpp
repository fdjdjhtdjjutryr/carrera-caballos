#include "caballo.h"
#include <cstdlib>
#include <cstdio>
#include <cstring>

// Mutex y variables globales para registrar el orden de llegada
pthread_mutex_t mutexMetas = PTHREAD_MUTEX_INITIALIZER;
int ordenLlegada[7];  // Guarda los IDs de los caballos en orden de llegada
int cuentaTerminados = 0;

void preparar_carrera(Caballo c[], int &numCaballos, int &largoPista, int &numVueltas) {
    do {
        printf("Cantidad de caballos (2-7): ");
        if (scanf("%d", &numCaballos) != 1) while (getchar() != '\n');
    } while(numCaballos < 2 || numCaballos > 7);

    do {
        printf("Largo de pista (30,40,50,60): ");
        if (scanf("%d", &largoPista) != 1) while (getchar() != '\n');
    } while(largoPista != 30 && largoPista != 40 && largoPista != 50 && largoPista != 60);

    do {
        printf("Numero de vueltas (1-4): ");
        if (scanf("%d", &numVueltas) != 1) while (getchar() != '\n');
    } while(numVueltas < 1 || numVueltas > 4);

    for(int i = 0; i < numCaballos; i++) {
        c[i].id = i;
        sprintf(c[i].nombre, "Caballo %c", 'A' + i);
        c[i].posicion = 0;
        c[i].vueltas = 0;
        c[i].distanciaTotal = 0;
        c[i].termino = false;
    }
    
    // Resetear contadores globales para la nueva carrera
    cuentaTerminados = 0;
    for(int i = 0; i < 7; i++) ordenLlegada[i] = -1;
}

void mover(Caballo &c, int largoPista) {
    // Función de probabilidad (75% de probabilidad de avance)
    if ((rand() % 100) < 75) {
        c.distanciaTotal += 1;
        c.vueltas = c.distanciaTotal / largoPista;
        c.posicion = c.distanciaTotal % largoPista;
    }
}

void* correrCaballo(void* arg) { 
    HiloCaballo* datos = (HiloCaballo*) arg;
    int metaFinal = datos->largoPista * datos->numVueltas;

    while(datos->caballo->distanciaTotal < metaFinal) {
        mover(*datos->caballo, datos->largoPista);

        if(datos->caballo->distanciaTotal >= metaFinal && !datos->caballo->termino) {
            datos->caballo->termino = true;
            
            // SECCIÓN CRÍTICA: Registra de manera ordenada la llegada usando el Mutex
            pthread_mutex_lock(&mutexMetas);
            ordenLlegada[cuentaTerminados] = datos->caballo->id;
            cuentaTerminados++;
            pthread_mutex_unlock(&mutexMetas);
        }
        napms(45); 
    }
    pthread_exit(NULL);
}

void hipodromo(Caballo c[], int n, int largoPista) {
    clear();
    mvprintw(0, 0, "================================= CARRERA =================================");
    
    int totalesVueltas = 0;
    int totalesMetros = 0;

    for (int i = 0; i < n; i++) {
        mvprintw(2 + i, 0, "%s: %d vuelta(s) - %d metros", c[i].nombre, c[i].vueltas, c[i].distanciaTotal);
        totalesVueltas += c[i].vueltas;
        totalesMetros += c[i].distanciaTotal;
    }

    mvprintw(3 + n, 0, "Totales: %d vueltas - %d metros", totalesVueltas, totalesMetros);
    
    int filaInicioCarriles = 5 + n;
    for (int i = 0; i < n; i++) {
        char letraCompetidor = 'A' + i;
        mvprintw(filaInicioCarriles + i, 0, "Carril %d | %c |", i + 1, letraCompetidor);
        
        for (int j = 0; j < largoPista; j++) {
            mvprintw(filaInicioCarriles + i, 13 + j, "-");
        }
        mvprintw(filaInicioCarriles + i, 13 + largoPista, "| N");
        
        mvprintw(filaInicioCarriles + i, 13 + c[i].posicion, "H");
    }
    
    mvprintw(filaInicioCarriles + n + 1, 13, "0");
    mvprintw(filaInicioCarriles + n + 1, 13 + (largoPista / 2) - 4, "DISTANCIA");
    mvprintw(filaInicioCarriles + n + 1, 13 + largoPista, "%d", largoPista);
    
    refresh();
}

void presentar_resultado(Caballo c[], int n, int ordenLlegada[], int totalTerminados, int largoPista, int numVueltas) {
    int filaBase = 8 + (n * 2);
    mvprintw(filaBase, 0, "---------------------------------------------------------------------------");
    mvprintw(filaBase + 1, 0, "Largo de la pista: %d metros", largoPista);
    mvprintw(filaBase + 2, 0, "Número de vueltas: %d", numVueltas);
    
    // REQUISITO ADICIONAL: Mostrar tabla con el orden de todos los caballos
    mvprintw(filaBase + 4, 0, "============= TABLA DE POSICIONES =============");
    for (int i = 0; i < totalTerminados; i++) {
        int idCaballo = ordenLlegada[i];
        mvprintw(filaBase + 5 + i, 0, " %d° Lugar: %s", i + 1, c[idCaballo].nombre);
    }
    
    int filaSiguiente = filaBase + 6 + totalTerminados;
    mvprintw(filaSiguiente, 0, "-----------------------------------------------");
    mvprintw(filaSiguiente + 1, 0, "Gracias por participar.");
    mvprintw(filaSiguiente + 3, 0, "¿Desea configurar una nueva carrera? (s/n): ");
    refresh();
}