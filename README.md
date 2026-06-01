# carrera-caballos
TAREA 1: CARRERA DE CABALLOS UCSC
SISTEMAS OPERATIVOS 

INTEGRANTES:
- Oscar González
- Jeremy Mendoza
- Dan Ocampo

Este programa simula una carrera de 4 caballos utilizando una 
metodología de programación modular en C++. La interfaz gráfica 
se despliega en la terminal mediante la biblioteca ncurses.h.

- Compilador g++ (GCC).
- Biblioteca ncurses (libncurses5-dev).
- Entorno Linux o WSL (Windows Subsystem for Linux).

El código está organizado de forma modular para permitir la 
reutilización de funciones:
- caballo.h: Interfaz de la biblioteca 
- caballo.cpp: Implementación de la lógica 
- main.cpp: Programa principal 

Para compilar el proyecto, ejecute en la terminal:
- cd /ruta/a/tu/carpeta/carrera-caballos
- g++ main.cpp caballo.cpp -o carrera -lncurses

INSTRUCCIONES DE USO
1. Ejecute el programa con: ./carrera
2. Si la terminal es muy pequeña, el programa mostrará un error. 
   Deberá maximizar la ventana y volver a ejecutar.
3. Presione cualquier tecla para iniciar la competencia.
4. Observe el avance aleatorio de los competidores.
5. Al finalizar, se anunciará al ganador. Presione una tecla para salir.

