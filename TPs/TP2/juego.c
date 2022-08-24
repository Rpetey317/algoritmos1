// ||LIBRERIAS||
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include "companero.h"
#include "papeleo.h"
#include "utiles.h"

// ||MAIN||
int main(){

    srand ((unsigned)time(NULL)); //seed

    char transporte = ' ';
    char marcha = ' ';
    float hora = -1.0f;
    int nota = -1;

    msj_intro_companero();
    preguntar_transporte(&transporte);
    preguntar_marcha(&marcha);
    preguntar_hora(&hora);
    preguntar_nota(&nota);
    system("clear");

    char personaje_tp1 = obtener_personaje(transporte, marcha, hora, nota);
    imprimir_personaje(personaje_tp1);

    juego_t juego;
    inicializar_juego(&juego, personaje_tp1);

    imprimir_terreno(juego);

    return 0;
}