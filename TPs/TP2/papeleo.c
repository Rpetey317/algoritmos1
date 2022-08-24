#include "papeleo.h"

// ||LIBRERIAS||
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "utiles.h"
#include "companero.h"
#include <stdlib.h>

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
} config_t;

//COnstantes para trabajar con matrices
#define FIL_MAX_MAT 31
#define COL_MAX_MAT 31

//Bonos de los pjs del tp 1
#define BONO_OLAF_1_LVL 1
#define BONO_OLAF_1_CANT 2
#define BONO_OLAF_2_LVL 2
#define BONO_OLAF_2_CANT 1

#define BONO_STITCH_LVL 3
#define BONO_STITCH_CANT 1

#define BONO_MCQUEEN_LVL 1
#define BONO_MCQUEEN_CANT 10

#define BONO_JASMIN_CANT 1

//Símbolos para imprimir el juego
#define JUGADOR 'W'
#define LIBRE '.'
#define PARED '#'
#define PAPELEO 'P'
#define FUEGO 'F'
#define MEDIA 'M'
#define INTERRUPTOR 'I'
#define BOTELLA 'G'

#define ORIGEN_FIL 0
#define ORIGEN_COL 0

//Configuración del nivel 1
//Las constantes están declaradas en el mismo orden que en el que se usan en config_t
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
static const config_t CONFIG_1 = {ID_N1, FILAS_N1, COLUMNAS_N1, PAPELEOS_N1, MOVIMIENTOS_N1, MEDIAS_N1,
                                FUEGOS_N1, MARTILLOS_N1, EXTINTORES_N1, BOTELLAS_N1, INTERRUPTORES_N1};


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
static const config_t CONFIG_2 = {ID_N2, FILAS_N2, COLUMNAS_N2, PAPELEOS_N2, MOVIMIENTOS_N2, MEDIAS_N2,
                                FUEGOS_N2, MARTILLOS_N2, EXTINTORES_N2, BOTELLAS_N2, INTERRUPTORES_N2};


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
static const config_t CONFIG_3 = {ID_N3, FILAS_N3, COLUMNAS_N3, PAPELEOS_N3, MOVIMIENTOS_N3, MEDIAS_N3,
                                FUEGOS_N3, MARTILLOS_N3, EXTINTORES_N3, BOTELLAS_N3, INTERRUPTORES_N3};

static const config_t CONFIGURACIONES[MAX_NIVELES] = {CONFIG_1, CONFIG_2, CONFIG_3};


// ||PROCEDIMIENTOS Y FUNCIONES||

//imprime una matriz hasta tope_fil y tope_col por pantalla
//NO imprime un \n al final
void imprimir_matriz(char mat[FIL_MAX_MAT][COL_MAX_MAT], int tope_fil, int tope_col){
    for (int i = 0; i < tope_fil; i++){
        for (int j = 0; j < tope_col; j++){
            printf("%c ", mat[i][j]);
        }
        printf("\n");
    }
}

//Llena todoas las entradas de una matriz del caracter especificado hasta tope_fil y tope_col
void llenar_matriz_char(char mat[FIL_MAX_MAT][COL_MAX_MAT], int tope_fil, int tope_col, char relleno){
    for (int i = 0; i < tope_fil; i++){
        for (int j = 0; j < tope_col; j++){
            mat[i][j] = relleno;
        }
    }
}

//Procedimiento que recibe el juego e imprime toda su información por pantalla.
void imprimir_terreno(juego_t juego){
    //inicialización del mapa
    char mapa[FIL_MAX_MAT][COL_MAX_MAT];
    nivel_t nivel_actual = juego.niveles[juego.nivel_actual - 1];
    int mapa_fil = CONFIGURACIONES[juego.nivel_actual - 1].filas;
    int mapa_col = CONFIGURACIONES[juego.nivel_actual - 1].columnas;
    llenar_matriz_char(mapa, mapa_fil, mapa_col, LIBRE);

    //Jugador
    int jugador_x = juego.jugador.posicion.fil;
    int jugador_y = juego.jugador.posicion.col;
    mapa[jugador_x][jugador_y] = JUGADOR;

    //Paredes
    for(int i = 0; i < nivel_actual.tope_paredes; i++){
        int x = nivel_actual.paredes[i].fil;
        int y = nivel_actual.paredes[i].col;
        mapa[x][y] = PARED;
    }

    //Obstáculos
    for(int i = 0; i < nivel_actual.tope_obstaculos; i++){
        int x = nivel_actual.obstaculos[i].posicion.fil;
        int y = nivel_actual.obstaculos[i].posicion.col;
        mapa[x][y] = nivel_actual.obstaculos[i].tipo;
    }

    //Herramientas
    for(int i = 0; i < nivel_actual.tope_herramientas; i++){
        int x = nivel_actual.herramientas[i].posicion.fil;
        int y = nivel_actual.herramientas[i].posicion.col;
        mapa[x][y] = nivel_actual.herramientas[i].tipo;
    }

    //Papeleos
    for(int i = 0; i < nivel_actual.tope_papeleos; i++){
        int x = nivel_actual.papeleos[i].posicion.fil;
        int y = nivel_actual.papeleos[i].posicion.col;
        if(!nivel_actual.papeleos[i].recolectado){
            mapa[x][y] = PAPELEO;
        }
    }

    imprimir_matriz(mapa, mapa_fil, mapa_col);
    printf("\n");

    //Info adicional
    int nivel = juego.nivel_actual;
    int movimientos = juego.jugador.movimientos;
    int martillos = juego.jugador.martillos;
    int extintores = juego.jugador.extintores;
    char* ahuyenta_randall = "Desactivado";
    if(juego.jugador.ahuyenta_randall){
        strcpy(ahuyenta_randall, "Activado!");
    }
    printf("Nivel: %i || Movimientos: %i || Martillos: %i || Extintores: %i || Ahuyenta Randall: %s"
            "\n", nivel, movimientos, martillos, extintores, ahuyenta_randall);

}

//Devuelve una coordenada aleatoria, con la fila y la columna acotados entre sus mínimos y máximos (min/max_fil/col respectivamente.)
coordenada_t coordenada_aleatoria(int min_fil, int max_fil, int min_col, int max_col){
    coordenada_t coord = {0, 0};
    int amplitud_fil = max_fil - min_fil;
    int amplitud_col = max_col - min_col;
    
    coord.fil = rand() % amplitud_fil + min_fil;
    coord.col = rand() % amplitud_col + min_col;

    return coord;
}

//Función que recibe una coordenada y verifica si es un espacio libre en un mapa
//coord debería estar dentro de los límites (topes) del mapa, aunque no se reciban en esta función
//mapa debería estar inicializado
bool es_espacio_libre(coordenada_t coord, char mapa[FIL_MAX_MAT][COL_MAX_MAT]){
    int x = coord.fil;
    int y = coord.col;
    return(mapa[x][y] == LIBRE);
}

//Función que recibe una coordenada y verifica si es adyacente a un tipo de espacio en el mapa
//coord debería estar dentro de los límites del mapa y mapa debería estar inicializado
//tipo debe ser un char que represente algo en el mapa (PARED, MEDIA, FUEGO, EXTINTOR, INTERRUPTOR, BOTELLA, JUGADOR o LIBRE)
bool es_adyacente_a(char tipo, coordenada_t coord, char mapa[FIL_MAX_MAT][COL_MAX_MAT]){
    if(mapa[coord.fil + 1][coord.col] == tipo){
        return true;
    } else if(mapa[coord.fil - 1][coord.col] == tipo){
        return true;
    } else if(mapa[coord.fil][coord.col + 1] == tipo){
        return true;
    } else if(mapa[coord.fil][coord.col - 1] == tipo){
        return true;
    } else{
        return false;
    }
}

//Carga el vector de obstáculos de un nivel con posiciones aleatorios, se encarga de que sean válidas
//Recibe el mapa del nivel, la configuración, el vector de obstáculos con su tope, y el personaje de los obsequios
//devuelve los obstáculos correspondientes al nivel cargados en el vector de obstáculos (con su respectivo tope) y en el mapa
//Asume que el vector de obstáculos está vacío, por lo que sobreescribe lo que ya haya ahí
//Para ser llamada por inicializar_nivel
void obtener_obstaculos(char mapa[FIL_MAX_MAT][COL_MAX_MAT], config_t config, objeto_t obstaculos[MAX_OBSTACULOS], int *tope_obstaculos, char pj_tp1){
    int cant_medias = config.medias;
    int cant_fuegos = config.fuegos;
    if(pj_tp1 == OLAF){
        if(config.id == BONO_OLAF_1_LVL){
            cant_fuegos = cant_fuegos - BONO_OLAF_1_CANT;
        }
        if(config.id == BONO_OLAF_2_LVL){
            cant_fuegos = cant_fuegos - BONO_OLAF_2_CANT;
        }
    }

    int fil_mapa = config.filas;
    int col_mapa = config.columnas;
    *tope_obstaculos = 0;

    for(int i = 0; i < cant_medias; i++){
        coordenada_t coord = {0, 0};
        do {
            coord = coordenada_aleatoria(ORIGEN_FIL, fil_mapa, ORIGEN_COL, col_mapa); 
        } while (!es_espacio_libre(coord, mapa));
       
        obstaculos[*tope_obstaculos].posicion = coord;
        obstaculos[*tope_obstaculos].tipo = MEDIA;
        *tope_obstaculos += 1;
    }

    for(int i = 0; i < cant_fuegos; i++){
        coordenada_t coord = {0, 0};
        do {
            coord = coordenada_aleatoria(ORIGEN_FIL, fil_mapa, ORIGEN_COL, col_mapa); 
        } while ( !(es_espacio_libre(coord, mapa) && es_adyacente_a(PARED, coord, mapa)) );
        
        obstaculos[*tope_obstaculos].posicion = coord;
        obstaculos[*tope_obstaculos].tipo = FUEGO;
        *tope_obstaculos += 1;
    }

    for (int i = 0; i < *tope_obstaculos; i++){
        int x = obstaculos[i].posicion.fil;
        int y = obstaculos[i].posicion.col;
        mapa[x][y] = obstaculos[i].tipo;
    }

}

//Carga el vector de herramientas de un nivel con posiciones aleatorias, se encarga de que sean válidas
//Recibe el mapa del nivel, la configuración, y el vector de herramientas con su tope
//devuelve las herramientas correspondientes al nivel cargadas en el vector de herramientas (con su respectivo tope) y en el mapa
//Asume que el vector de herramientas está vacío, por lo que sobreescribe lo que ya haya ahí
//Para ser llamada por inicializar_nivel
void obtener_herramientas(char mapa[FIL_MAX_MAT][COL_MAX_MAT], config_t config, objeto_t herramientas[MAX_HERRAMIENTAS], int *tope_herramientas){
    int cant_botellas = config.botellas;
    int cant_interruptores = config.interruptores;
    int fil_mapa = config.filas;
    int col_mapa = config.columnas;
    *tope_herramientas = 0;

    for(int i = 0; i < cant_botellas; i++){
        coordenada_t coord = {0, 0};
        do {
            coord = coordenada_aleatoria(ORIGEN_FIL, fil_mapa, ORIGEN_COL, col_mapa); 
        } while (!es_espacio_libre(coord, mapa));
       
        herramientas[*tope_herramientas].posicion = coord;
        herramientas[*tope_herramientas].tipo = BOTELLA;
        *tope_herramientas += 1;
    }

    for(int i = 0; i < cant_interruptores; i++){
        coordenada_t coord = {0, 0};
        do {
            coord = coordenada_aleatoria(ORIGEN_FIL, fil_mapa, ORIGEN_COL, col_mapa); 
        } while (!es_espacio_libre(coord, mapa));
       
        herramientas[*tope_herramientas].posicion = coord;
        herramientas[*tope_herramientas].tipo = INTERRUPTOR;
        *tope_herramientas += 1;
    }

    for (int i = 0; i < *tope_herramientas; i++){
        int x = herramientas[i].posicion.fil;
        int y = herramientas[i].posicion.col;
        mapa[x][y] = herramientas[i].tipo;
    }
}

//Carga el vector de papeleos de un nivel con posiciones aleatorias, se encarga de que sean válidas
//Recibe el mapa del nivel, la configuración, el vector de papeleos con su tope, y el personaje de los obsequios
//devuelve los papeleos correspondientes al nivel cargados en el vector de herramientas (con su respectivo tope) y en el mapa
//Inicializa las *.id_papeleo de los papeleos secuencialmente empezando desde 0 y los *.recolectado como false
//Asume que el vector de papeleos está vacío, por lo que sobreescribe lo que ya haya ahí
//Para ser llamada por inicializar_nivel
void obtener_papeleos(char mapa[FIL_MAX_MAT][COL_MAX_MAT], config_t config, papeleo_t papeleos[MAX_PAPELEOS], int *tope_papeleos, char pj_tp1){
    int cant_papeleos = config.papeleos;
    if( (pj_tp1 == STITCH) && (config.id == BONO_STITCH_LVL) ){
        cant_papeleos = cant_papeleos - BONO_STITCH_CANT;
    }
    int fil_mapa = config.filas;
    int col_mapa = config.columnas;
    *tope_papeleos = 0;

    for(int i = 0; i < cant_papeleos; i++){
        coordenada_t coord = {0, 0};
        do {
            coord = coordenada_aleatoria(ORIGEN_FIL, fil_mapa, ORIGEN_COL, col_mapa); 
        } while (!es_espacio_libre(coord, mapa));
       
        papeleos[*tope_papeleos].posicion = coord;
        papeleos[*tope_papeleos].id_papeleo = i;
        papeleos[*tope_papeleos].recolectado = false;
        *tope_papeleos += 1;
    }

    for (int i = 0; i < *tope_papeleos; i++){
        int x = papeleos[i].posicion.fil;
        int y = papeleos[i].posicion.col;
        mapa[x][y] = PAPELEO;
    }

}

//Inicializará un nivel, cargando toda la información inicial, las paredes,
//los objetos, los papeleos y la posición inicial del jugador en dicho nivel.
void inicializar_nivel(nivel_t* nivel, int numero_nivel, char personaje_tp1){

    config_t config_actual = CONFIGURACIONES[numero_nivel - 1];
    char mapa[FIL_MAX_MAT][COL_MAX_MAT];
    llenar_matriz_char(mapa, config_actual.filas, config_actual.columnas, LIBRE);
    
    obtener_paredes(numero_nivel, (*nivel).paredes, &(*nivel).tope_paredes, &(*nivel).pos_inicial_jugador);
    for(int i = 0; i < (*nivel).tope_paredes; i++){
        int x = (*nivel).paredes[i].fil;
        int y = (*nivel).paredes[i].col;
        mapa[x][y] = PARED;
    }

    int jugador_x = (*nivel).pos_inicial_jugador.fil;
    int jugador_y = (*nivel).pos_inicial_jugador.col;
    mapa[jugador_x][jugador_y] = JUGADOR;

    obtener_obstaculos(mapa, config_actual, (*nivel).obstaculos, &(*nivel).tope_obstaculos, personaje_tp1);
    obtener_herramientas(mapa, config_actual, (*nivel).herramientas, &(*nivel).tope_herramientas);
    obtener_papeleos(mapa, config_actual, (*nivel).papeleos, &(*nivel).tope_papeleos, personaje_tp1);

}

//Inicializa el jugador según el nivel actual y el personaje de los obsequios
//pos_inicial debe ser obtenida de un nivel inicializado por inicializar_nivel para asegurarse de que sea válida
//Nivel es un número entre 1 y MAX_NIVELES
void inicializar_jugador(jugador_t *jugador, coordenada_t pos_inicial, int nivel, char pj_tp1){
    (*jugador).posicion = pos_inicial;
    (*jugador).ahuyenta_randall = false;
    (*jugador).extintores = CONFIGURACIONES[nivel - 1].extintores;
    
    (*jugador).martillos = CONFIGURACIONES[nivel - 1].martillos; 
    if(pj_tp1 == JASMIN){
        (*jugador).martillos = (*jugador).martillos + BONO_JASMIN_CANT;
    }

    (*jugador).movimientos = CONFIGURACIONES[nivel - 1].movimientos;
    if((pj_tp1 == MCQUEEN) && (nivel == BONO_MCQUEEN_LVL)){
        (*jugador).movimientos = (*jugador).movimientos + BONO_MCQUEEN_CANT;
    }
}

//Inicializará el juego, cargando toda la información inicial, los datos del jugador, 
//el personaje resultado del tp anterior, y los 3 niveles. El campo "nivel_actual"
//comienza en 1.
void inicializar_juego(juego_t* juego, char personaje_tp1){
    (*juego).nivel_actual = 1;
    (*juego).personaje_tp1 = personaje_tp1;
    for(int i = 0; i < MAX_NIVELES; i++){
        inicializar_nivel(&(*juego).niveles[i], i + 1, personaje_tp1);
    }

    coordenada_t pos_inic_jugador = (*juego).niveles[(*juego).nivel_actual - 1].pos_inicial_jugador; 
    inicializar_jugador(&(*juego).jugador, pos_inic_jugador, (*juego).nivel_actual, personaje_tp1);

}
