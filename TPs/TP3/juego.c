// gcc *.c utiles.o -std=c99 -Wall -Wconversion -Werror -lm -o juegotest

// ||LIBRERIAS||
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>

#include "companero.h"
#include "papeleo.h"
#include "utiles.h"
#include "controlador.h"
#include "mensajes.h"
#include "config.h"

const char EMPEZAR = 'N';

// ||MAIN||
int main(){

    srand ((unsigned)time(NULL)); //seed

    char personaje_tp1 = ' ';
    char empezar = ' ';

    jugar_tp1(&personaje_tp1);
    inicializar_controlador();

    printf("\nPresione \"%c\" para continuar\n", EMPEZAR);
    do{
        scanf(" %c", &empezar);
        empezar = (char) toupper(empezar);
    } while (empezar != EMPEZAR);
    
    reglas_y_controles();


    printf("Buena suerte! (presiona \"%c\" para empezar)\n", EMPEZAR);
    empezar = ' ';
    do{
        scanf(" %c", &empezar);
        empezar = (char) toupper(empezar);
    } while (empezar != EMPEZAR);
    

    juego_t juego;
    inicializar_juego(&juego, personaje_tp1);

    imprimir_terreno(juego);

    while(estado_juego(juego) == JUGANDO){
        imprimir_terreno(juego);
        realizar_jugada(&juego);

        if (estado_nivel(juego.niveles[juego.nivel_actual - 1].papeleos, juego.niveles[juego.nivel_actual - 1].tope_papeleos) == GANADO){
            system("clear");
            imprimir_nivel_superado();
        }
    }

    system("clear");
    if(estado_juego(juego) == PERDIDO){
        imprimir_perdiste();
    } else{
        imprimir_ganaste();
    }

    terminar_controlador();

    return 0;
}