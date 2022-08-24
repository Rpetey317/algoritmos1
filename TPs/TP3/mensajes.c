#include "mensajes.h"

#include <stdio.h>
#include "utiles.h"
#include "companero.h"
#include "papeleo.h"
#include "config.h"

#define PRINT_DELAY 0.1f
#define PRINT_DELAY_LONG 0.8f
#define SHOW_DELAY 1.0f

/*
* Imprime "Nivel Superado!" en ASCII art con un pequeño delay entre línea y línea y un pequeño delay al final
*/
void imprimir_nivel_superado(){
    printf("d8b   db d888888b db    db d88888b db      \n");
    detener_el_tiempo(PRINT_DELAY);
    printf("888o  88   `88'   88    88 88'     88      \n");
    detener_el_tiempo(PRINT_DELAY);
    printf("88V8o 88    88    Y8    8P 88ooooo 88      \n");
    detener_el_tiempo(PRINT_DELAY);
    printf("88 V8o88    88    `8b  d8' 88~~~~~ 88      \n");
    detener_el_tiempo(PRINT_DELAY);
    printf("88  V888   .88.    `8bd8'  88.     88booo. \n");
    detener_el_tiempo(PRINT_DELAY);
    printf("VP   V8P Y888888P    YP    Y88888P Y88888P \n");
    detener_el_tiempo(PRINT_DELAY);

    printf("\n");

    printf(".d8888. db    db d8888b. d88888b d8888b.  .d8b.  d8888b.  .d88b.  db \n");
    detener_el_tiempo(PRINT_DELAY);
    printf("88'  YP 88    88 88  `8D 88'     88  `8D d8' `8b 88  `8D .8P  Y8. 88 \n");
    detener_el_tiempo(PRINT_DELAY);
    printf("`8bo.   88    88 88oodD' 88ooooo 88oobY' 88ooo88 88   88 88    88 YP \n");
    detener_el_tiempo(PRINT_DELAY);
    printf("  `Y8b. 88    88 88~~~   88~~~~~ 88`8b   88~~~88 88   88 88    88    \n");
    detener_el_tiempo(PRINT_DELAY);
    printf("db   8D 88b  d88 88      88.     88 `88. 88   88 88  .8D `8b  d8' db \n");
    detener_el_tiempo(PRINT_DELAY);
    printf("`8888Y' ~Y8888P' 88      Y88888P 88   YD YP   YP Y8888D'  `Y88P'  YP \n");
    detener_el_tiempo(PRINT_DELAY);
                                                                     
    printf("\n");  

    detener_el_tiempo(SHOW_DELAY);                                                                                                      
                                           
}

/*
* Imprime "Perdiste! Que mal =(" en ASCII art con un pequeño delay entre línea y línea
*/
void imprimir_perdiste(){
    printf("d8888b. d88888b d8888b. d8888b. d888888b .d8888. d888888b d88888b db \n");
    detener_el_tiempo(PRINT_DELAY);
    printf("88  `8D 88'     88  `8D 88  `8D   `88'   88'  YP `~~88~~' 88'     88 \n");
    detener_el_tiempo(PRINT_DELAY);
    printf("88oodD' 88ooooo 88oobY' 88   88    88    `8bo.      88    88ooooo YP \n");
    detener_el_tiempo(PRINT_DELAY);
    printf("88~~~   88~~~~~ 88`8b   88   88    88      `Y8b.    88    88~~~~~    \n");
    detener_el_tiempo(PRINT_DELAY);
    printf("88      88.     88 `88. 88  .8D   .88.   db   8D    88    88.     db \n");
    detener_el_tiempo(PRINT_DELAY);
    printf("88      Y88888P 88   YD Y8888D' Y888888P `8888Y'    YP    Y88888P YP \n");
    detener_el_tiempo(PRINT_DELAY);
                                                                     
    printf("\n");

    printf(" .d88b.  db    db d88888b      .88b  d88.  .d8b.  db                      dD \n");
    detener_el_tiempo(PRINT_DELAY);
    printf(".8P  Y8. 88    88 88'          88'YbdP`88 d8' `8b 88           C8888D   d8'  \n");
    detener_el_tiempo(PRINT_DELAY);
    printf("88    88 88    88 88ooooo      88  88  88 88ooo88 88                   d8    \n");
    detener_el_tiempo(PRINT_DELAY);
    printf("88    88 88    88 88~~~~~      88  88  88 88~~~88 88           C8888D C88    \n");
    detener_el_tiempo(PRINT_DELAY);
    printf("`8P  d8' 88b  d88 88.          88  88  88 88   88 88booo.              V8    \n");
    detener_el_tiempo(PRINT_DELAY);
    printf(" `Y88'Y8 ~Y8888P' Y88888P      YP  YP  YP YP   YP Y88888P               V8.  \n");
    detener_el_tiempo(PRINT_DELAY);
    printf("                                                                          VD \n");
    detener_el_tiempo(PRINT_DELAY);

    printf("\n");                                                                                                                                             
}

/*
* Imprime "Ganaste! Woohoo =D" en ASCII art con un pequeño delay entre línea y línea
*/
void imprimir_ganaste(){

    printf(" d888b   .d8b.  d8b   db  .d8b.  .d8888. d888888b d88888b db \n");
    detener_el_tiempo(PRINT_DELAY);
    printf("88' Y8b d8' `8b 888o  88 d8' `8b 88'  YP `~~88~~' 88'     88 \n");
    detener_el_tiempo(PRINT_DELAY);
    printf("88      88ooo88 88V8o 88 88ooo88 `8bo.      88    88ooooo YP \n");
    detener_el_tiempo(PRINT_DELAY);
    printf("88  ooo 88~~~88 88 V8o88 88~~~88   `Y8b.    88    88~~~~~    \n");
    detener_el_tiempo(PRINT_DELAY);
    printf("88. ~8~ 88   88 88  V888 88   88 db   8D    88    88.     db \n");
    detener_el_tiempo(PRINT_DELAY);
    printf(" Y888P  YP   YP VP   V8P YP   YP `8888Y'    YP    Y88888P YP \n");
    detener_el_tiempo(PRINT_DELAY);
                                                             
    printf("\n");

    printf("db   d8b   db  .d88b.   .d88b.  db   db  .d88b.   .d88b.              d8888b. \n");
    detener_el_tiempo(PRINT_DELAY);
    printf("88   I8I   88 .8P  Y8. .8P  Y8. 88   88 .8P  Y8. .8P  Y8.      C8888D 88  `8D \n");
    detener_el_tiempo(PRINT_DELAY);
    printf("88   I8I   88 88    88 88    88 88ooo88 88    88 88    88             88   88 \n");
    detener_el_tiempo(PRINT_DELAY);
    printf("Y8   I8I   88 88    88 88    88 88~~~88 88    88 88    88      C8888D 88   88 \n");
    detener_el_tiempo(PRINT_DELAY);
    printf("`8b d8'8b d8' `8b  d8' `8b  d8' 88   88 `8b  d8' `8b  d8'             88  .8D \n");
    detener_el_tiempo(PRINT_DELAY);
    printf(" `8b8' `8d8'   `Y88P'   `Y88P'  YP   YP  `Y88P'   `Y88P'              Y8888D' \n");
    detener_el_tiempo(PRINT_DELAY);
                                                                              
    printf("\n");
}

/*
* Imprime un parrafito explicando las reglas y los controles del juego
*/
void reglas_y_controles(){
    printf("¡Lograste rendir el exámen! Hora de buscar la nota.\n");
    detener_el_tiempo(PRINT_DELAY);
    printf("Como justo ese día estabas ocupado, le pediste a tu buen amigo Mike Wazowski que fuera a buscar la nota por ti.\n");
    detener_el_tiempo(PRINT_DELAY);
    printf("Pero tuvo un problemita: Roz no le va a dar las notas hasta que le entregue todo el papeleo que le tiene pendiente desde hace 4 años y medio\n");
    detener_el_tiempo(PRINT_DELAY);
    printf("Ahora tienes que ayudar a Mike Wazowski (Micky Wazo para los amigos) a recolectar sus papeleos perdidos!\n");
    detener_el_tiempo(PRINT_DELAY_LONG);
    printf("\n");
    detener_el_tiempo(PRINT_DELAY);
    printf("Vas a tener que recorrer las %i aulas en las que Mike dejó sus papeleos olvidados y recogerlos en orden para que Roz no se queje.\n", MAX_NIVELES);
    detener_el_tiempo(PRINT_DELAY);
    printf("Como son las aulas especiales diseñadas al estilo de Monsters University, además de moverte de lado a lado vas a poder rotar toda la habitación.\n");
    detener_el_tiempo(PRINT_DELAY);
    printf("Además, Mike vino preparado con martillos y extintores en su mochila para su clase de carpintería extrema a las 16:30, pero puede usarlos para esta misión.\n");
    detener_el_tiempo(PRINT_DELAY);
    printf("Pero cuidado! Randall está intentando sabotearlo y por eso mueve los papeleos por todas partes.\n");
    detener_el_tiempo(PRINT_DELAY);
    printf("Es tu misión ayudarlo a recoger todos los papeleos!\n");
    detener_el_tiempo(PRINT_DELAY);
    printf("Por suerte, tu amigo del parcial te dejó una ayuda que te puede ser de utilidad.\n");
    detener_el_tiempo(PRINT_DELAY_LONG);
    printf("\n");
    detener_el_tiempo(PRINT_DELAY);
    printf("Estas aulas están llenas de \"objetos especiales\" (termino elegante para \"cosas que nadie se ha tomado la molestia de poner donde van\"):\n");
    detener_el_tiempo(PRINT_DELAY);
    printf("Las paredes (%c) son mágicas y se multiplican con el movimiento, pero luego de un rato se cansan. Se pueden romper a mano con un martillo.\n", PARED);
    detener_el_tiempo(PRINT_DELAY);
    printf("Las botellas de gritos (%c) en verdad son latas de Monster de Mango, si tomas de una vas a tener más energía para seguir buscando.\n", BOTELLA);
    detener_el_tiempo(PRINT_DELAY);
    printf("Las medias (%c) son del equipo de handball y huelen tan mal que cansan. Pueden dejarte fuera de la búsqueda antes de lo que piensas.\n", MEDIA);
    detener_el_tiempo(PRINT_DELAY);
    printf("El interruptor ahuyenta Randall (%c) prende la televisión en Crónica TV. Como Randall no los banca, debería hacer que se vaya\n", INTERRUPTOR);
    detener_el_tiempo(PRINT_DELAY);
    printf("También hay fuego (%c) porque estas eran las aulas anteriores de carpintería extrema. Si tocas uno, vas a tener que ir directo a la enfermería.\n", FUEGO);
    detener_el_tiempo(PRINT_DELAY);
    printf("Por suerte, los papeleos tienen su número en grande y se pueden distinguir a lo lejos. Recuerda agarrarlos en orden!\n");
    detener_el_tiempo(PRINT_DELAY);
    printf("Por último, Mike lleva puesta su gorra de la compañía (%c) para que sepas dónde está.\n", JUGADOR);
    detener_el_tiempo(PRINT_DELAY_LONG);
    printf("\n");
    detener_el_tiempo(PRINT_DELAY);
    printf("Para navegar por las aulas puedes:\n");
    detener_el_tiempo(PRINT_DELAY);
    printf("Moverte a la izquierda (%c) o a la derecha (%c)\n", IZQUIERDA, DERECHA);
    detener_el_tiempo(PRINT_DELAY);
    printf("Rotar toda la habitación en sentido horario (%c) o antihorario (%c)\n", ROTAR_H, ROTAR_AH);
    detener_el_tiempo(PRINT_DELAY);
    printf("Usar un martillo en una pared (%c) o usar un extintor en un fuego (%c)\n", MARTILLO, EXTINTOR);
    detener_el_tiempo(PRINT_DELAY);
    printf("\n");
}