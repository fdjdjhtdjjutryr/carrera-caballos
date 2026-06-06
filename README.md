Carrera de Caballos - Tarea 2 (UCSC)
Asignatura: Sistemas Operativos (IN1077C)

 Integrantes
- Oscar González
- Jeremy Mendoza
- Dan Ocampo

 Descripción del Proyecto
Este programa es una simulación interactiva y modular en C++ de una carrera de caballos utilizando Hebras POSIX pthread.h para el control concurrente de cada competidor y la biblioteca ncurses  para el renderizado gráfico de la interfaz en modalidad texto. 

A diferencia de la versión anterior, esta entrega incorpora:
1. Lógica de Avance Probabilística: Los hilos calculan de manera independiente su probabilidad de avance (75% de éxito por ciclo).
2. Sincronización por Mutex: Implementación de exclusión mutua para evitar condiciones de carrera en la línea de meta, asegurando un registro del orden de llegada.
3. Métricas Globales: Despliegue en tiempo real de la sumatoria total de metros recorridos y vueltas completadas por todos los hilos en carrera.
4. Tabla de Posiciones Dinámica: Al finalizar la competencia, se despliega el podio completo con el orden de llegada exacto de todos los competidores (desde el 1° hasta el último lugar).
5. Ciclo de Reconfiguración: Permite al usuario reiniciar y configurar parámetros de una nueva carrera de forma interactiva sin salir de la aplicación.

Requisitos del Sistema
- Sistema Operativo: Entorno Linux Nativo o WSL (Windows Subsystem for Linux).
- Compilador: g++ (GCC) con soporte para estándar moderno de C++.
- Librerías de Desarrollo: - libncurses6 y libncurses-dev (Manejo de pantallas en consola).
- Componente nativo de hilos POSIX (pthread).

 Instrucciones de Instalación (WSL / Linux)

1. Instalar dependencias del sistema:
   Si ejecutas el proyecto por primera vez en tu distribución, asegúrate de tener el compilador y las librerías instaladas corriendo en la terminal:
   bash
   sudo apt update && sudo apt install -y build-essential libncurses6 libncurses-dev
2. cd /ruta/a/tu/carpeta/carrera-caballos
3. g++ main.cpp caballo.cpp -o carrera -lncurses -lpthread