#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_TUERCAS 1000

typedef struct tuerca{
    int tamanho;
    bool esta_oxidada;
} tuerca_t;

//Para ser llamada únicamente por promedioTuerca
//posActual e iteración deben ser mayores o iguales a 0
int promedioTuercaRec(tuerca_t tuercas[MAX_TUERCAS], int topeTuercas, int tamanhoBuscado, int posActual, int iteracion, int suma){
    
    if(posActual >= topeTuercas){
        return suma/iteracion;
    }
    if(tuercas[posActual].tamanho == tamanhoBuscado && !tuercas[posActual].esta_oxidada){
        return (suma + tamanhoBuscado)/(iteracion + 1);
    }

    if(tuercas[posActual].tamanho % 2 == 0){
        return promedioTuercaRec(tuercas, topeTuercas, tamanhoBuscado, posActual + 50, iteracion + 1, suma + tuercas[posActual].tamanho);
    } else{
        return promedioTuercaRec(tuercas, topeTuercas, tamanhoBuscado, posActual + 25, iteracion + 1, suma + tuercas[posActual].tamanho);
    }
}

//recorre un vector de tuercas de maneras trambólicas hasta encontrar una tuerca de tamanhoBuscado
//devuelve el promedio de todas las tuercas que recorrió hasta encontrar dicha tuerca
//tuercas debe ser un vector no vacío, con tuercas debidamente inicializadas (tamaño estrictamente positivo)
int promedioTuerca(tuerca_t tuercas[MAX_TUERCAS], int topeTuercas, int tamanhoBuscado){
    return promedioTuercaRec(tuercas, topeTuercas, tamanhoBuscado, 0, 0, 0);
}
