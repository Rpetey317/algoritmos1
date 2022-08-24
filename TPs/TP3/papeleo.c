#include "papeleo.h"

// ||LIBRERIAS||
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "utiles.h"
#include "companero.h"
#include "config.h"

//Constantes para trabajar con matrices
#define FIL_MAX_MAT 31
#define COL_MAX_MAT 31

#define ORIGEN_FIL 0
#define ORIGEN_COL 0

#define NO_EXISTE -1

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

//Efectos de las casillas
#define MEDIA_PENALTY 10
#define BOTELLA_BONO 7

//Misc
#define DELAY_GRAVEDAD 0.2f
#define NIVEL_ACTUAL (*juego).niveles[(*juego).nivel_actual - 1]
#define MAX_STR_RANDALL 20
const int ASCII_OFFSET_NUM = 48;

// ||PROCEDIMIENTOS Y FUNCIONES||

/*
* imprime una matriz hasta tope_fil y tope_col por pantalla
* NO imprime un \n al final
*/
void imprimir_matriz(char mat[FIL_MAX_MAT][COL_MAX_MAT], int tope_fil, int tope_col){
    for (int i = 0; i < tope_fil; i++){
        for (int j = 0; j < tope_col; j++){
            printf("%c ", mat[i][j]);
        }
        printf("\n");
    }
}

/*
* Llena todoas las entradas de una matriz del caracter especificado hasta tope_fil y tope_col
*/
void llenar_matriz_char(char mat[FIL_MAX_MAT][COL_MAX_MAT], int tope_fil, int tope_col, char relleno){
    for (int i = 0; i < tope_fil; i++){
        for (int j = 0; j < tope_col; j++){
            mat[i][j] = relleno;
        }
    }
}

/*
* Procedimiento que recibe el juego e imprime toda su información por pantalla.
* En el proceso limpia lo que ya estaba impreso en la pantalla
*/
void imprimir_terreno(juego_t juego){
    //inicialización del mapa
    char mapa[FIL_MAX_MAT][COL_MAX_MAT];
    nivel_t nivel_actual = juego.niveles[juego.nivel_actual - 1];
    int mapa_fil = CONFIGURACIONES[juego.nivel_actual - 1].filas;
    int mapa_col = CONFIGURACIONES[juego.nivel_actual - 1].columnas;
    llenar_matriz_char(mapa, mapa_fil, mapa_col, LIBRE);

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
            mapa[x][y] = (char) (nivel_actual.papeleos[i].id_papeleo + ASCII_OFFSET_NUM);
            //mapa[x][y] = PAPELEO;
        }
    }

    //Jugador
    int jugador_x = juego.jugador.posicion.fil;
    int jugador_y = juego.jugador.posicion.col;
    mapa[jugador_x][jugador_y] = JUGADOR;

    system("clear");
    imprimir_matriz(mapa, mapa_fil, mapa_col);
    printf("\n");

    //Info adicional
    int nivel = juego.nivel_actual;
    int movimientos = juego.jugador.movimientos;
    int martillos = juego.jugador.martillos;
    int extintores = juego.jugador.extintores;
    char ahuyenta_randall[MAX_STR_RANDALL];
    if(juego.jugador.ahuyenta_randall){
        strcpy(ahuyenta_randall, "Activado!");
    } else{
        strcpy(ahuyenta_randall, "Desactivado");
    }
    printf("Nivel: %i || Movimientos: %i || Martillos: %i || Extintores: %i || Ahuyenta Randall: %s""\n", nivel, movimientos, martillos, extintores, ahuyenta_randall);

}

/*
* Devuelve una coordenada aleatoria, con la fila y la columna acotados entre sus mínimos y máximos (min/max_fil/col respectivamente.)
*/
coordenada_t coordenada_aleatoria(int min_fil, int max_fil, int min_col, int max_col){
    coordenada_t coord = {0, 0};
    int amplitud_fil = max_fil - min_fil;
    int amplitud_col = max_col - min_col;
    
    coord.fil = rand() % amplitud_fil + min_fil;
    coord.col = rand() % amplitud_col + min_col;

    return coord;
}

/*
* Función que recibe una coordenada y verifica si es un espacio del tipo dado en un mapa
* coord debería estar dentro de los límites (topes) del mapa, aunque no se reciban en esta función
* mapa debería estar inicializado
*/
bool es_espacio_tipo(char tipo, coordenada_t coord, char mapa[FIL_MAX_MAT][COL_MAX_MAT]){
    int x = coord.fil;
    int y = coord.col;
    return(mapa[x][y] == tipo);
}

/*
* Función que recibe una coordenada y verifica si es adyacente a un tipo de espacio en el mapa
* coord debería estar dentro de los límites del mapa y mapa debería estar inicializado
* tipo debe ser un char que represente algo en el mapa (PARED, MEDIA, FUEGO, EXTINTOR, INTERRUPTOR, BOTELLA, JUGADOR o LIBRE)
*/
bool es_adyacente_a(char tipo, coordenada_t coord, char mapa[FIL_MAX_MAT][COL_MAX_MAT]){
    if(mapa[coord.fil + 1][coord.col] == tipo){
        return true;
    } else if(mapa[coord.fil - 1][coord.col] == tipo){
        return true;
    } else if(mapa[coord.fil][coord.col + 1] == tipo){
        return true;
    } else if(mapa[coord.fil][coord.col - 1] == tipo){
        return true;
    }
    return false;
}

/*
* Carga el vector de obstáculos de un nivel con posiciones aleatorios, se encarga de que sean válidas
* Recibe el mapa del nivel, la configuración, el vector de obstáculos con su tope, y el personaje de los obsequios
* devuelve los obstáculos correspondientes al nivel cargados en el vector de obstáculos (con su respectivo tope) y en el mapa
* Asume que el vector de obstáculos está vacío, por lo que sobreescribe lo que ya haya ahí
* Para ser llamada por inicializar_nivel
*/
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
        } while (!es_espacio_tipo(LIBRE, coord, mapa));
       
        obstaculos[*tope_obstaculos].posicion = coord;
        obstaculos[*tope_obstaculos].tipo = MEDIA;
        *tope_obstaculos += 1;
    }

    for(int i = 0; i < cant_fuegos; i++){
        coordenada_t coord = {0, 0};
        do {
            coord = coordenada_aleatoria(ORIGEN_FIL, fil_mapa, ORIGEN_COL, col_mapa); 
        } while ( !(es_espacio_tipo(LIBRE, coord, mapa) && es_adyacente_a(PARED, coord, mapa)) );
        
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

/*
* Carga el vector de herramientas de un nivel con posiciones aleatorias, se encarga de que sean válidas
* Recibe el mapa del nivel, la configuración, y el vector de herramientas con su tope
* devuelve las herramientas correspondientes al nivel cargadas en el vector de herramientas (con su respectivo tope) y en el mapa
* Asume que el vector de herramientas está vacío, por lo que sobreescribe lo que ya haya ahí
* Para ser llamada por inicializar_nivel
*/
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
        } while (!es_espacio_tipo(LIBRE, coord, mapa));
       
        herramientas[*tope_herramientas].posicion = coord;
        herramientas[*tope_herramientas].tipo = BOTELLA;
        *tope_herramientas += 1;
    }

    for(int i = 0; i < cant_interruptores; i++){
        coordenada_t coord = {0, 0};
        do {
            coord = coordenada_aleatoria(ORIGEN_FIL, fil_mapa, ORIGEN_COL, col_mapa); 
        } while (!es_espacio_tipo(LIBRE, coord, mapa));
       
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

/*
* Carga el vector de papeleos de un nivel con posiciones aleatorias, se encarga de que sean válidas
* devuelve los papeleos correspondientes al nivel cargados en el vector de papeleos (con su respectivo tope) y en el mapa
* Inicializa las *.id_papeleo de los papeleos secuencialmente empezando desde 1 y los *.recolectado como false
* Asume que el vector de papeleos está vacío, por lo que sobreescribe lo que ya haya ahí
* Devuelve el vector papeleos ordenado por id
* Para ser llamada por inicializar_nivel
*/
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
        } while (!es_espacio_tipo(LIBRE, coord, mapa));
       
        papeleos[*tope_papeleos].posicion = coord;
        papeleos[*tope_papeleos].id_papeleo = i+1;
        papeleos[*tope_papeleos].recolectado = false;
        *tope_papeleos += 1;
    }

    for (int i = 0; i < *tope_papeleos; i++){
        int x = papeleos[i].posicion.fil;
        int y = papeleos[i].posicion.col;
        mapa[x][y] = PAPELEO;
    }

}

/*
* Inicializará un nivel, cargando toda la información inicial, las paredes,
* los objetos, los papeleos y la posición inicial del jugador en dicho nivel.
*/
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

/*
* Inicializa el jugador según el nivel actual y el personaje de los obsequios
* Los movimientos se añaden, no se sobreescriben. Se asume que si el nivel NO es 1, movimientos ya está inicializado
* pos_inicial debe ser obtenida del nivel correspondiente
* Nivel es un número entre 1 y MAX_NIVELES (preferiblemente juego.nivel_actual)
*/
void inicializar_jugador(jugador_t *jugador, coordenada_t pos_inicial, int nivel, char pj_tp1){
    if(nivel == 1){
        (*jugador).movimientos = 0;
    }

    (*jugador).posicion = pos_inicial;
    (*jugador).ahuyenta_randall = false;
    (*jugador).extintores = CONFIGURACIONES[nivel - 1].extintores;
    (*jugador).movimientos_realizados = 0;
    
    (*jugador).martillos = CONFIGURACIONES[nivel - 1].martillos; 
    if(pj_tp1 == JASMIN){
        (*jugador).martillos = (*jugador).martillos + BONO_JASMIN_CANT;
    }

    (*jugador).movimientos += CONFIGURACIONES[nivel - 1].movimientos;
    if((pj_tp1 == MCQUEEN) && (nivel == BONO_MCQUEEN_LVL)){
        (*jugador).movimientos = (*jugador).movimientos + BONO_MCQUEEN_CANT;
    }
}

/*
* Inicializará el juego, cargando toda la información inicial, los datos del jugador, 
* el personaje resultado del tp anterior, y los 3 niveles. El campo "nivel_actual"
* comienza en 1.
*/
void inicializar_juego(juego_t* juego, char personaje_tp1){
    (*juego).nivel_actual = 1;
    (*juego).personaje_tp1 = personaje_tp1;
    for(int i = 0; i < MAX_NIVELES; i++){
        inicializar_nivel(&(*juego).niveles[i], i + 1, personaje_tp1);
    }
    
    inicializar_jugador(&(*juego).jugador, NIVEL_ACTUAL.pos_inicial_jugador, (*juego).nivel_actual, ((*juego).personaje_tp1));
}

/*
* El nivel se dará por terminado , si se reolectan todos los papeleos en el mismo.
* Devolverá:
* -> 0 si el estado es jugando.
* -> 1 si el estado es ganado.
*/
int estado_nivel(papeleo_t papeleos[MAX_PAPELEOS], int tope_papeleos){

    for (int i = 0; i < tope_papeleos; i++){
        if (!papeleos[i].recolectado){
            return JUGANDO;
        }
    }
    return GANADO;
}

/*
* Recibe un juego con todas sus estructuras válidas.
* El juego se dará por ganado , si terminó todos los niveles. O perdido , si el personaje queda
* sin movimientos.
* Devolverá:
* -> 0 si el estado es jugando.
* -> -1 si el estado es perdido.
* -> 1 si el estado es ganado.
*/
int estado_juego(juego_t juego){
    if(juego.jugador.movimientos <= 0){
        return PERDIDO;
    }
    
    for(int i = 0; i <= MAX_NIVELES; i++){
        if(estado_nivel(juego.niveles[i].papeleos, juego.niveles[i].tope_papeleos) != GANADO){
            return JUGANDO;
        }
    }

    return GANADO;
}

/*
* Recibe una coordenada de una matriz junto con la cantidad de filas de la misma
* y devuelve la coordenada correspondiente a una rotación horaria de dicha matriz
* Si se le ingresa una coordenada perteneciente a una matriz de n x m,
* el resultado estará en los límites de una matriz de m x n
*/
coordenada_t rot_horaria(coordenada_t coord, int fil){
    coordenada_t rotacion;
    rotacion.fil = coord.col;
    rotacion.col = abs(coord.fil - fil + 1);
    return rotacion;
}

/*
* Recibe una coordenada de una matriz junto con la cantidad de columnas de la misma
* y devuelve la coordenada correspondiente a una rotación antihoraria de dicha matriz
* Si se le ingresa una coordenada perteneciente a una matriz de n x m,
* el resultado estará en los límites de una matriz de m x n
*/
coordenada_t rot_antihoraria(coordenada_t coord, int col){
    coordenada_t rotacion;
    rotacion.fil = abs(coord.col - col + 1);
    rotacion.col = coord.fil;
    return rotacion;
}

/*
* Rota las coordenadas de todos los elementos del mapa y del jugador horariamente
*/
void rotar_horario(nivel_t* nivel, jugador_t* jugador, int fil){
    
    for(int i = 0; i < (*nivel).tope_paredes; i++){
        (*nivel).paredes[i] = rot_horaria((*nivel).paredes[i], fil);
    }

    for(int i = 0; i < (*nivel).tope_obstaculos; i++){
        (*nivel).obstaculos[i].posicion = rot_horaria((*nivel).obstaculos[i].posicion, fil);
    }

    for(int i = 0; i < (*nivel).tope_herramientas; i++){
        (*nivel).herramientas[i].posicion = rot_horaria((*nivel).herramientas[i].posicion, fil);
    }
    
    for(int i = 0; i < (*nivel).tope_papeleos; i++){
        (*nivel).papeleos[i].posicion = rot_horaria((*nivel).papeleos[i].posicion, fil);
    }
    
    (*jugador).posicion = rot_horaria((*jugador).posicion, fil);

}

/*
* Rota las coordenadas de todos los elementos del mapa y del jugador antihorariamente
*/
void rotar_antihorario(nivel_t* nivel, jugador_t* jugador, int col){
    
    for(int i = 0; i < (*nivel).tope_paredes; i++){
        (*nivel).paredes[i] = rot_antihoraria((*nivel).paredes[i], col);
    }

    for(int i = 0; i < (*nivel).tope_obstaculos; i++){
        (*nivel).obstaculos[i].posicion = rot_antihoraria((*nivel).obstaculos[i].posicion, col);
    }

    for(int i = 0; i < (*nivel).tope_herramientas; i++){
        (*nivel).herramientas[i].posicion = rot_antihoraria((*nivel).herramientas[i].posicion, col);
    }
    
    for(int i = 0; i < (*nivel).tope_papeleos; i++){
        (*nivel).papeleos[i].posicion = rot_antihoraria((*nivel).papeleos[i].posicion, col);
    }
    
    (*jugador).posicion = rot_antihoraria((*jugador).posicion, col);

}

/*
* Devuelve true si la coordenada se encuentra en el borde del mapa
*/
bool es_del_borde(coordenada_t coord, int max_fil, int max_col){
    return (coord.fil == ORIGEN_FIL || coord.col == ORIGEN_COL || coord.fil == max_fil-1 || coord.col == max_col-1);
}

/*
* Si coord se encuentra en el vector de paredes, devuelve su posición
* Si no existe en el vector, devuelve -1
*/
int pos_pared(coordenada_t coord, coordenada_t paredes[MAX_PAREDES], int tope){
    for (int i = 0; i < tope; i++){
        if (coord.fil == paredes[i].fil && coord.col == paredes[i].col){
            return i;
        }
    }
    return NO_EXISTE;
}

/*
* Si existe un fuego en la posición de coord, devuelve su posición en el vector de obstáculos
* Si no existe en el vector, devuelve -1
*/
int pos_fuego(coordenada_t coord, objeto_t obstaculos[MAX_OBSTACULOS], int tope){
    for (int i = 0; i < tope; i++){
        if ((coord.fil == obstaculos[i].posicion.fil) && (coord.col == obstaculos[i].posicion.col) && (obstaculos[i].tipo == FUEGO)){
            return i;
        }
    }
    return NO_EXISTE;
}

/*
* Si existe una media en la posición de coord, devuelve su posición en el vector de obstáculos
* Si no existe en el vector, devuelve -1
*/
int pos_media(coordenada_t coord, objeto_t obstaculos[MAX_OBSTACULOS], int tope){
    for (int i = 0; i < tope; i++){
        if ((coord.fil == obstaculos[i].posicion.fil) && (coord.col == obstaculos[i].posicion.col) && (obstaculos[i].tipo == MEDIA)){
            return i;
        }
    }
    return NO_EXISTE;
}

/*
* Si existe una botella de gritos en la posición de coord, devuelve su posición en el vector de herramientas
* Si no existe en el vector, devuelve -1
*/
int pos_botella(coordenada_t coord, objeto_t herramientas[MAX_HERRAMIENTAS], int tope){
    for (int i = 0; i < tope; i++){
        if ((coord.fil == herramientas[i].posicion.fil) && (coord.col == herramientas[i].posicion.col) && (herramientas[i].tipo == BOTELLA)){
            return i;
        }
    }
    return NO_EXISTE;
}

/*
* Si existe un interruptor en la posición de coord, devuelve su posición en el vector de herramientas
* Si no existe en el vector, devuelve -1
*/
int pos_interruptor(coordenada_t coord, objeto_t herramientas[MAX_HERRAMIENTAS], int tope){
    for (int i = 0; i < tope; i++){
        if ((coord.fil == herramientas[i].posicion.fil) && (coord.col == herramientas[i].posicion.col) && (herramientas[i].tipo == INTERRUPTOR)){
            return i;
        }
    }
    return NO_EXISTE;
}

/*
* Si existe un papeleo sin recolectar en la posición de coord, devuelve su posición en el vector de papeleos
* Si no existe en el vector, devuelve -1
*/
int pos_papeleo(coordenada_t coord, papeleo_t papeleo[MAX_PAPELEOS], int tope){
    for (int i = 0; i < tope; i++){
        if ((coord.fil == papeleo[i].posicion.fil) && (coord.col == papeleo[i].posicion.col) && !(papeleo[i].recolectado)){
            return i;
        }
    }
    return NO_EXISTE;
}

/*
* Elimina una pared del vector de paredes
*/
void eliminar_pared(int pos, coordenada_t paredes[MAX_PAREDES], int* tope){
    for (int i = pos; i < *tope - 1; i++){
        paredes[i] = paredes[i+1];
    }
    *tope -= 1;
}

/*
* Elimina un obstáculo del vector de obstáculos
*/
void eliminar_obstaculo(int pos, objeto_t obstaculos[MAX_OBSTACULOS], int* tope){
    for (int i = pos; i < *tope - 1; i++){
        obstaculos[i] = obstaculos[i+1];
    }
    *tope -= 1;
}

/*
* Elimina la pared adyacente al jugador en la direccion indicada, descuenta un martillo,
* Y actualiza realizado acordemente en caso de que dicha pared exista
*/
void romper_pared(char direccion, jugador_t* jugador, nivel_t* nivel, int nivel_actual){
    coordenada_t coord = (*jugador).posicion;

    switch (direccion){
    case ARRIBA:
        coord.fil -= 1;        
        break;

    case ABAJO:
        coord.fil += 1;        
        break;

    case IZQUIERDA:
        coord.col -= 1;        
        break;

    case DERECHA:
        coord.col += 1;        
        break;
    }

    int pared_a_romper = pos_pared(coord, (*nivel).paredes, (*nivel).tope_paredes);
    int fil = CONFIGURACIONES[nivel_actual-1].filas;
    int col = CONFIGURACIONES[nivel_actual-1].columnas;
    if((pared_a_romper != NO_EXISTE) && (!es_del_borde(coord, fil, col)) && ((*jugador).martillos > 0)){
        eliminar_pared(pared_a_romper, (*nivel).paredes, &(*nivel).tope_paredes);
        (*jugador).martillos -= 1;
    }
}

/*
* Elimina el fuego adyacente al jugador en la direccion indicada, descuenta un extintor,
* Y actualiza realizado acordemente en caso de que dicho fuego exista
*/
void extinguir_fuego(char direccion, jugador_t* jugador, nivel_t* nivel){
    coordenada_t coord = (*jugador).posicion;

    switch (direccion){
    case ARRIBA:
        coord.fil -= 1;        
        break;

    case IZQUIERDA:
        coord.col -= 1;        
        break;

    case DERECHA:
        coord.col += 1;        
        break;
    }

    int fuego_a_eliminar = pos_fuego(coord, (*nivel).obstaculos, (*nivel).tope_obstaculos);
    if(fuego_a_eliminar != NO_EXISTE && (*jugador).extintores > 0){
        eliminar_obstaculo(fuego_a_eliminar, (*nivel).obstaculos, &(*nivel).tope_obstaculos);
        (*jugador).extintores -= 1;
    }
}

/*
* Devuelve true si el caracter corresponde a una accion válida
*/
bool es_accion_valida(char accion){
    for(int i = 0; i < MAX_ACCIONES; i++){
        if(accion == ACCIONES[i]){
            return true;
        }
    }
    return false;
}

/*
* Devuelve true si el caracter corresponde a una direccion válida
*/
bool es_direccion_valida(char accion){
    for(int i = 0; i < MAX_DIRECCIONES; i++){
        if(accion == DIRECCIONES[i]){
            return true;
        }
    }
    return false;
}

/*
* Realiza el movimiento del jugador: rotacion, paso, o uso de objeto
* marca realizado como true solo si el jugador dio un paso o roto el mapa
* marca se_movio como true solo si el jugador dio un paso
*/
void realizar_movimiento(juego_t* juego, bool* realizado, bool* se_movio){
    
    char accion = ' ';
    *realizado = false;
    do{
        scanf(" %c", &accion);
        accion = (char) toupper(accion);
    } while(!es_accion_valida(accion));

    switch (accion){
    case ROTAR_AH:
        rotar_antihorario(&NIVEL_ACTUAL, &(*juego).jugador, CONFIGURACIONES[(*juego).nivel_actual - 1].columnas);
        *realizado = true;
        
        break;
    
    case ROTAR_H:
        rotar_horario(&NIVEL_ACTUAL, &(*juego).jugador, CONFIGURACIONES[(*juego).nivel_actual - 1].filas);
        *realizado = true;

        break;

    case IZQUIERDA:
        {
        coordenada_t coord = (*juego).jugador.posicion; 
        coord.col += -1;
        if (pos_pared(coord, NIVEL_ACTUAL.paredes, NIVEL_ACTUAL.tope_paredes) == NO_EXISTE){
            (*juego).jugador.posicion = coord;
            *realizado = true;
            *se_movio = true;
        }
        
        break;
        }

    case DERECHA:
        {
        coordenada_t coord = (*juego).jugador.posicion; 
        coord.col += 1;
        if (pos_pared(coord, NIVEL_ACTUAL.paredes, NIVEL_ACTUAL.tope_paredes) == NO_EXISTE){
            (*juego).jugador.posicion = coord;
            *realizado = true;
            *se_movio = true;
        }
        
        break;
        }

    case MARTILLO:
        {
        printf("Seleccione direccion para martillar: \n");
        printf("(Presione %c de nuevo para cancelar)\n", MARTILLO);
        char direccion = ' ';

        do{
            scanf(" %c", &direccion);
            direccion = (char) toupper(direccion);
        } while(!es_direccion_valida(direccion) && direccion != MARTILLO);

        if(direccion != MARTILLO){
            romper_pared(direccion, &(*juego).jugador, &NIVEL_ACTUAL, (*juego).nivel_actual);
        }

        break;
        }

    case EXTINTOR:
        {
        printf("Seleccione direccion para usar el extintor: \n");
        printf("(Presione %c de nuevo para cancelar)\n", EXTINTOR);
        char direccion = ' ';

        do{
            scanf(" %c", &direccion);
            direccion = (char) toupper(direccion);
        } while(!es_direccion_valida(direccion) && direccion != EXTINTOR);

        if(direccion != EXTINTOR){
            extinguir_fuego(direccion, &(*juego).jugador, &NIVEL_ACTUAL);
        }

        break;
        }

    default:
        break;
    }

    if((accion == ROTAR_AH || accion == ROTAR_H || accion == IZQUIERDA || accion == DERECHA) && *realizado){
        (*juego).jugador.movimientos -= 1;
        (*juego).jugador.movimientos_realizados += 1;
    }

}

/*
* Marca un papeleo como recolectado solo si los papeleos con id menor tambien estan recolectados
*/
void recolectar_papeleo(int index_papeleo, papeleo_t papeleos[MAX_PAPELEOS]){
    papeleos[index_papeleo].recolectado = true;
    for(int i = 0; i < index_papeleo; i++){
        if(!papeleos[i].recolectado){
            papeleos[index_papeleo].recolectado = false;
            return;
        }
    }
}

/*
* Chequea si el jugador está sobre algún objeto en el mapa y realiza la acción correspondiente:
* fuego: le quita todos los movimientos
* media: resta movimientos
* botella: añade movimientos
* interruptor: activa el ahuyenta randall
* papeleo: lo marca como recolectado
*/
void colision(juego_t* juego){
    char objeto = ' ';
    int index = NO_EXISTE;
    coordenada_t coord = (*juego).jugador.posicion;

    //Odio este pedazo de codigo con mi alma
    index = pos_fuego(coord, NIVEL_ACTUAL.obstaculos, NIVEL_ACTUAL.tope_obstaculos);
    if(index != NO_EXISTE){
        objeto = FUEGO;
    } else{
        index = pos_media(coord, NIVEL_ACTUAL.obstaculos, NIVEL_ACTUAL.tope_obstaculos);
        if(index != NO_EXISTE){
            objeto = MEDIA;
        } else{
            index = pos_botella(coord, NIVEL_ACTUAL.herramientas, NIVEL_ACTUAL.tope_herramientas);
            if(index != NO_EXISTE){
            objeto = BOTELLA;
            } else{
                index = pos_interruptor(coord, NIVEL_ACTUAL.herramientas, NIVEL_ACTUAL.tope_herramientas);
                if(index != NO_EXISTE){
                objeto = INTERRUPTOR;
                } else{
                   index = pos_papeleo(coord, NIVEL_ACTUAL.papeleos, NIVEL_ACTUAL.tope_papeleos);
                    if(index != NO_EXISTE){
                    objeto = PAPELEO;
                    }
                }
            }
        }
    }

    switch(objeto){
    case FUEGO:
        (*juego).jugador.movimientos = 0;
        break;

    case MEDIA:
        (*juego).jugador.movimientos -= MEDIA_PENALTY;
        break;

    case BOTELLA:
        (*juego).jugador.movimientos += BOTELLA_BONO;
        break;

    case INTERRUPTOR:
        (*juego).jugador.ahuyenta_randall = !(*juego).jugador.ahuyenta_randall;
        break;

    case PAPELEO:
        recolectar_papeleo(index, NIVEL_ACTUAL.papeleos);
        break;

    default:
        break;
    }
}

/*
* Devuelve true si no hay nada en un nivel que ocupe la coordenada coord
*/
bool es_coord_libre(coordenada_t coord, nivel_t nivel, coordenada_t pos_jugador){
    for(int i = 0; i < nivel.tope_paredes; i++){
        if(nivel.paredes[i].fil == coord.fil && nivel.paredes[i].col == coord.col){
            return false;
        }
    }
    for(int i = 0; i < nivel.tope_obstaculos; i++){
        if(nivel.obstaculos[i].posicion.fil == coord.fil && nivel.obstaculos[i].posicion.col == coord.col){
            return false;
        }
    }
    for(int i = 0; i < nivel.tope_herramientas; i++){
        if(nivel.herramientas[i].posicion.fil == coord.fil && nivel.herramientas[i].posicion.col == coord.col){
            return false;
        }
    }
    for(int i = 0; i < nivel.tope_papeleos; i++){
        if(nivel.papeleos[i].posicion.fil == coord.fil && nivel.papeleos[i].posicion.col == coord.col && !nivel.papeleos[i].recolectado){
            return false;
        }
    }
    if(coord.fil == pos_jugador.fil && coord.col == pos_jugador.col){
        return false;
    }

    return true;
}

/*
* Hace que el jugador "caiga" hasta que se encuentre con una pared o pierda
*/
void gravedad(juego_t* juego){
    coordenada_t coord = (*juego).jugador.posicion;
    coord.fil += 1;
    while ((pos_pared(coord, NIVEL_ACTUAL.paredes, NIVEL_ACTUAL.tope_paredes) == NO_EXISTE)  && (estado_juego(*juego) == JUGANDO)){
        imprimir_terreno((*juego));
        printf("~~~~~AHHHH ME CAIGOOOO!!!~~~~~\n");
        detener_el_tiempo(DELAY_GRAVEDAD);

        (*juego).jugador.posicion.fil += 1;
        colision(juego);
        
        coord = (*juego).jugador.posicion;
        coord.fil += 1;
    }
    
}

/*
* Mueve un papeleo aleatorio no recolectado a una posicion libre aleatoria
* nivel_actual debe estar entre 1 y MAX_NIVELES inclusive
*/
void movimiento_randall(nivel_t* nivel, int nivel_actual, coordenada_t pos_jugador){
    int pos = -1;
    do {
        pos = rand() % (*nivel).tope_papeleos;
    } while((*nivel).papeleos[pos].recolectado);
    
    coordenada_t coord = {-1, -1};
    do {
        coord = coordenada_aleatoria(ORIGEN_FIL, CONFIGURACIONES[nivel_actual - 1].filas, ORIGEN_COL, CONFIGURACIONES[nivel_actual - 1].columnas);
    } while(!es_coord_libre(coord, *nivel, pos_jugador));

    (*nivel).papeleos[pos].posicion.fil = coord.fil;
    (*nivel).papeleos[pos].posicion.col = coord.col;
}

/*
* Añade una pared nueva en una coordenada aleatoria y libre
* nivel_actual debe estar entre 1 y MAX_NIVELES inclusive
*/
void nueva_pared_aleatoria(nivel_t* nivel, int nivel_actual, coordenada_t pos_jugador){
    coordenada_t coord = {-1, -1};
   do {
        coord = coordenada_aleatoria(ORIGEN_FIL, CONFIGURACIONES[nivel_actual - 1].filas, ORIGEN_COL, CONFIGURACIONES[nivel_actual - 1].columnas);
    } while(!es_coord_libre(coord, *nivel, pos_jugador));

    (*nivel).paredes[(*nivel).tope_paredes].fil = coord.fil;
    (*nivel).paredes[(*nivel).tope_paredes].col = coord.col;
    (*nivel).tope_paredes += 1;
}

/*
* Moverá el personaje , y realizará la acción necesaria en caso de chocar con un elemento
*/
void realizar_jugada(juego_t* juego){

    if(estado_nivel(NIVEL_ACTUAL.papeleos, NIVEL_ACTUAL.tope_papeleos) == GANADO){
        (*juego).nivel_actual += 1;
        inicializar_jugador(&(*juego).jugador, NIVEL_ACTUAL.pos_inicial_jugador, (*juego).nivel_actual, ((*juego).personaje_tp1));
        return;
    }

    bool realizado = false;
    bool se_movio = false;
    
    realizar_movimiento(juego, &realizado, &se_movio);

    if(se_movio){
        colision(juego);
    }
    gravedad(juego);

    if(realizado){
        if(((*juego).jugador.movimientos_realizados % CONFIGURACIONES[((*juego).nivel_actual)-1].cte_randall == 0) && !(*juego).jugador.ahuyenta_randall){
            movimiento_randall(&NIVEL_ACTUAL, (*juego).nivel_actual, (*juego).jugador.posicion);
        }

        if((*juego).jugador.movimientos_realizados <= CONFIGURACIONES[((*juego).nivel_actual)-1].paredes_random){
            nueva_pared_aleatoria(&NIVEL_ACTUAL, (*juego).nivel_actual, (*juego).jugador.posicion);
        }
    }
    
}
