#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NOMBRE_COLOR 20
#define MAX_CARAMELOS 100
#define ANANA 'A'
#define MUCHAS_CALORIAS 400

typedef struct caramelo{
    int calorias;
    char color[MAX_NOMBRE_COLOR];
    int radio;
    char sabor;
} caramelo_t;

int caramelos_insalubres(caramelo_t caramelos[MAX_CARAMELOS], int topeCaramelos){
    int cantidad = 0;
    for(int i = 0; i < topeCaramelos; i++){
        if(caramelos[i].sabor == ANANA && caramelos[i].sabor >= MUCHAS_CALORIAS){
            cantidad++;
        }
    }
    return cantidad;
}

//devuelve true si c1 es menor por color primero y mayor por calorias segundo
bool hayQueIntercambiar(caramelo_t c1, 
                        caramelo_t c2){
    int comp = strcmp(c1.color, c2.color);
    if(comp == 0){
        return c1.calorias > c2.calorias;
    } else{
        return comp < 0;
    }
}

//ordena un vector de caramelos descendiente por color y ascendente por calorías
//el vector no debe estar vacío y debe tener caramelos correctamente inicializados
//a saber: calorías estrictamente positivas y color una string válida (empezando en mayúsculas)
void ordenarCaramelos(caramelo_t caramelos[MAX_CARAMELOS], int tope){
    for(int i = 0; i < tope; i++){
        for(int j = 0; j < tope - i - 1; j++){
            if(hayQueIntercambiar(caramelos[j], caramelos[j+1])){
                caramelo_t aux = caramelos[j];
                caramelos[j] = caramelos[j+1];
                caramelos[j+1] = aux;
            }
        }
    }
}
