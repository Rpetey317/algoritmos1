#ifndef __CONFIG__
#define __CONFIG__


#include "papeleo.h"

//Estados del juego y el nivel
#define JUGANDO 0
#define GANADO 1
#define PERDIDO -1

//Struct de configuración de un nivel
typedef struct config{
    int id;
    int filas;
    int columnas;
    int papeleos;
    int movimientos;
    int medias;
    int fuegos;
    int martillos;
    int extintores;
    int botellas;
    int interruptores;
    int paredes_random;
    int cte_randall;
} config_t;

//Las constantes están declaradas en el mismo orden que en el que se usan en config_t

//Configuración del nivel 1
#define ID_N1 1
#define FILAS_N1 22
#define COLUMNAS_N1 22
#define PAPELEOS_N1 2
#define MOVIMIENTOS_N1 40
#define MEDIAS_N1 5
#define FUEGOS_N1 10
#define MARTILLOS_N1 4
#define EXTINTORES_N1 4
#define BOTELLAS_N1 4
#define INTERRUPTORES_N1 1
#define PAREDES_RANDOM_N1 40
#define CTE_RANDALL_N1 7 
static const config_t CONFIG_1 = {ID_N1, FILAS_N1, COLUMNAS_N1, PAPELEOS_N1, MOVIMIENTOS_N1, MEDIAS_N1,FUEGOS_N1, MARTILLOS_N1, EXTINTORES_N1, BOTELLAS_N1, INTERRUPTORES_N1, PAREDES_RANDOM_N1, CTE_RANDALL_N1};

//Configuración del nivel 2
#define ID_N2 2
#define FILAS_N2 17
#define COLUMNAS_N2 17
#define PAPELEOS_N2 3
#define MOVIMIENTOS_N2 30
#define MEDIAS_N2 4
#define FUEGOS_N2 5
#define MARTILLOS_N2 5
#define EXTINTORES_N2 2
#define BOTELLAS_N2 3
#define INTERRUPTORES_N2 1
#define PAREDES_RANDOM_N2 30
#define CTE_RANDALL_N2 5
static const config_t CONFIG_2 = {ID_N2, FILAS_N2, COLUMNAS_N2, PAPELEOS_N2, MOVIMIENTOS_N2, MEDIAS_N2,FUEGOS_N2, MARTILLOS_N2, EXTINTORES_N2, BOTELLAS_N2, INTERRUPTORES_N2, PAREDES_RANDOM_N2, CTE_RANDALL_N2};

//Configuración del nivel 3
#define ID_N3 3
#define FILAS_N3 12
#define COLUMNAS_N3 12
#define PAPELEOS_N3 4
#define MOVIMIENTOS_N3 20
#define MEDIAS_N3 3
#define FUEGOS_N3 3
#define MARTILLOS_N3 6
#define EXTINTORES_N3 2
#define BOTELLAS_N3 2
#define INTERRUPTORES_N3 0
#define PAREDES_RANDOM_N3 20
#define CTE_RANDALL_N3 3
static const config_t CONFIG_3 = {ID_N3, FILAS_N3, COLUMNAS_N3, PAPELEOS_N3, MOVIMIENTOS_N3, MEDIAS_N3,FUEGOS_N3, MARTILLOS_N3, EXTINTORES_N3, BOTELLAS_N3, INTERRUPTORES_N3, PAREDES_RANDOM_N3, CTE_RANDALL_N3};

static const config_t CONFIGURACIONES[MAX_NIVELES] = {CONFIG_1, CONFIG_2, CONFIG_3};

//Símbolos para imprimir el juego
#define JUGADOR 'W'
#define LIBRE '.'
#define PARED '#'
#define PAPELEO 'P'
#define FUEGO 'F'
#define MEDIA 'M'
#define INTERRUPTOR 'I'
#define BOTELLA 'G'

//Movimientos
#define ROTAR_H 'E'
#define ROTAR_AH 'Q'

#define ARRIBA 'W'
#define ABAJO 'S'
#define IZQUIERDA 'A' 
#define DERECHA 'D'

#define MARTILLO 'Z'
#define EXTINTOR 'C'

#define MAX_ACCIONES 6
static const char ACCIONES[MAX_ACCIONES] = {ROTAR_H, ROTAR_AH, IZQUIERDA, DERECHA, MARTILLO, EXTINTOR};
#define MAX_DIRECCIONES 4
static const char DIRECCIONES[MAX_DIRECCIONES] = {ARRIBA, ABAJO, IZQUIERDA, DERECHA};

#endif /* __CONFIG__ */