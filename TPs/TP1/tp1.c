// |||LIBRERIAS|||
#include <stdio.h>
#include <stdbool.h>


// |||CONSTANTES|||

// Personajes
// Uso define en estas porque las necesito para un switch
#define OLAF 'O'
#define STITCH 'S'
#define JASMIN 'J'
#define MCQUEEN 'R'

// Respuestas pregunta 1
#define TRINEO 'T'
#define NAVE 'N'
#define CAMION 'C'
#define ALFOMBRA 'A'

// Respuestas pregunta 2
#define BOLAS_DE_NIEVE 'B'
#define PIUM_PIUM 'P'
#define KUCHAU 'K'
#define GENIO 'G'

// Respuestas pregunta 3 (Límites de los rangos de valores posibles)
const int HORA_MIN = 0;
const int HORA_MAX = 23;
const float MINUTOS_MAX = 0.60f; // La máxima en verdad es 0.59, pero hago la comparación < 0.6 por temas de precisión del float

// Respuestas pregunta 4 (Límites de los rangos de valores posibles)
const int NOTA_MIN = 1;
const int NOTA_MAX = 10;

// Constantes para el calculo del puntaje
//Pregunta 1
const int VALOR_T_N = 10;
const int VALOR_C_A = 20;

//Pregunta 2
const int VALOR_B = 3;
const int VALOR_P = 6;
const int VALOR_K = 9;
const int VALOR_G = 12;

//Pregunta 4
const int TOPE_MULT_1 = 3;
const int TOPE_MULT_2 = 6;
const int TOPE_MULT_3 = 8;
//no hace falta TOPE_MULT_4 porque es igual a NOTA_MAX
const int MULT_1 = 1;
const int MULT_2 = 2;
const int MULT_3 = 3;
const int MULT_4 = 4;

//Pregunta 3
const float HORA_PARCIAL = 15.31f; //no pongo 15.30 por el mismo tema con la precisión que con MINUTOS_MAX

// Para el cálculo del personaje
const int SCORE_MIN = 13;
const int TOPE_SCORE_BAJO = 41;
const int SCORE_MAX = 68;

// Para el mensaje después de la pregunta 3
const float TEMPRANO = 6.00f;
const float TARDE = 19.00f;

//Única constante string que uso porque aún no hemos visto eso pero vi que lo usaron por ahí y este separador lo uso muchas veces
const char* SEPARADOR = "-------------------------------------------------------------\n";


// |||FUNCIONES & PROCEDIMIENTOS|||

//Mensajes

//Mensaje que manda cuando arranca el programa
//El único propósito de este procedimiento es sacarme todo este texto del main
void msj_intro(){
    printf("Tienes que rendir un final mañana. Pero no es cualquier final, es el final de los finales, "
        "el final para dominarlos a todos,\nun final para sobrepasar al Metal Gear, un final que... Sabes qué, "
        "creo que ya entiendes el punto.\nLo peor de todo es que, después de preparar la MOAF (Mother Of All Finales) "
        "con sangre, sudor, lágrimas, alfajores de fruta y descansos para unas rondas del CSGO,\n"
        "anunciaron por la tele que el día del final habrá paro de todos los medios de transporte en Buenos Aires.\n"
        "Cómo se supone que llegues a la facultad sin tus sencillos 4 colectivos, 2 trenes, 3 líneas de subte "
        "y 5 metro-carretas-de-caballos?!?\nPara hacer frente a la mayor amenaza que hayas visto desde la última vez "
        "que tu madre te haya llamado por tu primer y segundo nombre, decides recurrir\na tu grupo de estudios "
        "(y squad de LoL miércoles y viernes por la noche) para que te ayuden a terminar de preparar el final y te ayuden "
        "a llegar a la facu.\nSi tomas buenas decisiones, aprobar el final es una verdadera posibilidad. Hora de la acción!\n");
    printf("%s", SEPARADOR);
}

//Mensaje respuesta a la pregunta 1 según lo que haya ingresado el usuario
//Manda un mensaje de error si la respuesta se encuentra fuera del rango esperado
//Rango esperado: caracteres TRINEO, NAVE, CAMION o ALFOMBRA
//Debería recibir sólamente valores dentro del rango esperado
void msj_preg_1(char respuesta){
    printf("Escogiste la opción: ");

    switch (respuesta){
    case TRINEO:
        printf("TRINEO\n");
        printf("No sé como pretendes usar un trineo en el conurbano bonaerense pero ok, como quieras...\n");
        break;

    case NAVE:
        printf("NAVE ESPACIAL\n");
        printf("Menos mal que aún no han inventado los piquetes aéreos!\n");
        break;
    
    case CAMION:
        printf("MAC EL CAMIÓN\n");
        printf("No imprta que no haya transporte público si tienes transporte privado!\n");
        break;
    
    case ALFOMBRA:
        printf("ALFOMBRA VOLADORA\n");
        printf("Quién necesita la autopista 25 de mayo cuando tienes transporte mágico?\n");
        break;

    default:
        printf("Si ves esto ha ocurrido un error: respuesta a la pregunta 1 inválida :(\n");
        break;
    }

    printf("%s", SEPARADOR);
}

//Mensaje respuesta a la pregunta 2 según lo que haya ingresado el usuario
//Manda un mensaje de error si la respuesta se encuentra fuera del rango esperado
//Rango esperado: caracteres BOLAS_DE_NIEVE, PIUM_PIUM, KUCHAU o GENIO
//Debería recibir sólamente valores dentro del rango esperado
void msj_preg_2(char respuesta){
    printf("Escogiste la opción: ");

    switch (respuesta){
    case BOLAS_DE_NIEVE:
        printf("BOLAS DE NIEVE\n");
        printf("Una guerra de bolas de nieve los mantendrá distraídos por un tiempo! Pasaste la manifestación!\n");
        break;

    case PIUM_PIUM:
        printf("PISTOLITA PIUM PIUM\n");
        printf("Tranquilo, es una pistola alien no letal para captura de experimentos. "
            "Y también sirve contra manifestantes al parecer\n");
        break;
    
    case KUCHAU:
        printf("KUCHAU!\n");
        printf("Dejaste completamente anonadados a los manifestantes con las maravillas del KUCHAU! "
            "Y pasas la manifestación (velozmente)\n");
        break;
    
    case GENIO:
        printf("GENIO DE LA LÁMPARA\n");
        printf("Tuvimos que contratar a un nuevo genio luego de que el anterior tuviera problemas con una zebra, "
            "pero igual te concedió el deseo de pasar la manifesación!\n");
        break;

    default:
        printf("Si ves esto ha ocurrido un error: respuesta a la pregunta 2 inválida :(\n");
        break;
    }

    printf("%s", SEPARADOR);
}

//Mensaje respuesta a la pregunta 3 según lo que haya ingresado el usuario
//Manda un mensaje de error si la respuesta se encuentra fuera del rango esperado
//Rango esperado: entre HORA_MIN y HORA_MAX para la parte entera y menor a MINUTOS_MAX para la parte decimal
//Debería recibir sólamente valores dentro del rango esperado
void msj_preg_3(float respuesta){ 
    printf("Llegaste a las: %.2f\n", respuesta);

    if((respuesta >= (float) HORA_MIN) && respuesta <= TEMPRANO){
        printf("Llegaste tan temprano que ni siquiera ha abierto la facultad aún. VELOZ!!!\n");
    }else if(respuesta > TEMPRANO && respuesta <= HORA_PARCIAL){
        printf("Justo a tiempo! te da tiempo de tomarte un café y relajarte un poco incluso\n");
    }else if(respuesta > HORA_PARCIAL && respuesta <= TARDE){
        printf("Mas vale tarde que nunca...\n");
    }else if(respuesta > TARDE && respuesta <= HORA_MAX){
        printf("LA FACU NO CIERRA HASTA QUE RESPONDA LA ÚLTIMA PREGUNTA!!!\n");
    }else{
        printf("Si ves esto ha ocurrido un error: respuesta a la pregunta 3 inválida :(\n");
    }

    printf("%s", SEPARADOR);
}

//Mensaje respuesta a la pregunta 4 según lo que haya ingresado el usuario
//Manda un mensaje de error si la respuesta se encuentra fuera del rango esperado
//Rango esperado: número entre el NOTA_MIN y NOTA_MAX
//Debería recibir sólamente valores dentro del rango esperado
void msj_preg_4(int respuesta){
    printf("Tu nota final fue: %i\n", respuesta);

    //Puedo reusar las constantes para el cálculo del score ya que las tengo
    if((respuesta >= NOTA_MIN) && respuesta < TOPE_MULT_1){
        printf("Se confió, se intentó, y no se logró...\n");
    }else if(respuesta >= TOPE_MULT_1 && respuesta < TOPE_MULT_2){
        printf("Pudo haber sido mucho peor\n");
    }else if(respuesta >= TOPE_MULT_2 && respuesta < TOPE_MULT_3){
        printf("Buena nota, juguemos unas partiditas del Rocket League para celebrar!\n");
    }else if(respuesta >= TOPE_MULT_3 && respuesta <= NOTA_MAX){
        printf("Victoria absoluta! Tu final fue tan bueno que lo enmarcaron y lo colgaron en la entrada!\n");
    }else{
        printf("Si ves esto ha ocurrido un error: respuesta a la pregunta 4 inválida :(\n");
    }

    printf("%s", SEPARADOR);
}


//<Verificación de la validez de las respuestas>

//Verifica la validez de la respuesta a la pregunta 1
//Devuelve true si la respuesta es TRINEO, NAVE, CAMION o ALFOMBRA, false si es otra cosa
bool es_respuesta_valida_1(char respuesta){
   return(respuesta == TRINEO || respuesta == NAVE || respuesta == CAMION || respuesta == ALFOMBRA);
}

//Verifica la validez de la respuesta a la pregunta 2
//Devuelve true si la respuesta es BOLAS_DE_NIEVE, PIUM_PIUM, KUCHAU o GENIO, false si es otra cosa
bool es_respuesta_valida_2(char respuesta){
   return(respuesta == BOLAS_DE_NIEVE || respuesta == PIUM_PIUM || respuesta == KUCHAU || respuesta == GENIO);
}

//Verifica la validez de la respuesta a la pregunta 3
//Devuelve true si la respuesta es un float con parte entera entre HORA_MIN y HORA_MAX y parte decimal menor a MINUTOS_MAX (no incl.), false si no
bool es_respuesta_valida_3(float respuesta){
    int hora = (int) respuesta;
    bool valid_hora = ((hora >= HORA_MIN) && (hora <= HORA_MAX));
    float minutos = respuesta - (float) hora;
    bool valid_minutos = ((minutos >= HORA_MIN) && (minutos < MINUTOS_MAX));
    return valid_hora && valid_minutos; 
}

//Verifica la validez de la respuesta a la pregunta 4
//Devuelve true si la respuesta es un int entre NOTA_MIN y NOTA_MAX (incl.), false si no
bool es_respuesta_valida_4(int respuesta){
    return((respuesta >= NOTA_MIN) && (respuesta <= NOTA_MAX));
}


//<Procedimientos de hacer las preguntas>

//Procedimientos de hacer la pregunta 1 y chequear la validez de las respuesta 
//Es recursiva, me pareció una buena solución para seguir preguntando hasta que la respuesta sea válida
//Como también se ocupa de validar la respuesta, debería funcionar siempre y cuando reciba el tipo de dato correcto
//Devuelve la respuesta en el parámetro pasado al procedimiento
//La respuesta va a ser TRINEO, NAVE, CAMION o ALFOMBRA
//Falla cuando el usuario ingresa algo que no sea un número
void preguntar_1(char* respuesta){ 
    printf("Ingrese su respuesta\nEstas son las respuestas posibles: ");
    printf("Trineo (%c), Nave espacial (%c), Mac el camión (%c), Alfombra voladora (%c) (En mayúscula)\n", TRINEO, NAVE, CAMION, ALFOMBRA);
    scanf(" %c", respuesta);
    printf("%s", SEPARADOR);
    if(!es_respuesta_valida_1(*respuesta)){
        printf("Respuesta Inválida! Así no llegás más a la uni!\n");
        preguntar_1(respuesta);
    }
}

//Procedimientos de hacer la pregunta 2 y chequear la validez de las respuesta 
//Es recursiva, me pareció una buena solución para seguir preguntando hasta que la respuesta sea válida
//Como también se ocupa de validar la respuesta, debería funcionar siempre y cuando reciba el tipo de dato correcto
//Devuelve la respuesta en el parámetro pasado al procedimiento
//La respuesta va a ser BOLAS_DE_NIEVE, PIUM_PIUM, KUCHAU o GENIO
//Falla cuando el usuario ingresa algo que no sea un número
void preguntar_2(char* respuesta){
    printf("Ingrese su respuesta\nEstas son las respuestas posibles: ");
    printf("Bolas de nieve (%c), Pistolita pium pium (%c), KUCHAU! (%c), Genio de la lámpara (%c) (En mayúscula)\n", BOLAS_DE_NIEVE, PIUM_PIUM, KUCHAU, GENIO);
    scanf(" %c", respuesta);
    printf("%s", SEPARADOR);
    if(!es_respuesta_valida_2(*respuesta)){
        printf("Respuesta Inválida! Eso no detendrá a los manifestantes!\n");
        printf("%s", SEPARADOR);
        preguntar_2(respuesta);
    }
}

//Procedimientos de hacer la pregunta 3 y chequear la validez de las respuesta 
//Es recursiva, me pareció una buena solución para seguir preguntando hasta que la respuesta sea válida
//Como también se ocupa de validar la respuesta, debería funcionar siempre y cuando reciba el tipo de dato correcto
//Devuelve la respuesta en el parámetro pasado al procedimiento
//La respuesta que devuelve va a ser un float:
//Su parte entera va estar entre HORA_MIN y HORA_MAX incl. y la  parte decimal menor a MINUTOS_MAX no incl.
//Falla cuando el usuario ingresa algo que no sea un número
void preguntar_3(float* respuesta){
    printf("Ingrese su respuesta\nLa respuesta debe ser: ");
    float verdadera_hora_max = (float) HORA_MAX + MINUTOS_MAX - 0.01f;
    printf("Hora con formato hh.mm entre las 00.00 y las %.2f inclusive. Ej: 15.25. ", verdadera_hora_max);
    printf("Poner ÚNICAMENTE un número, no otro tipo de caracter\n");  
    scanf(" %f", respuesta);
    printf("%s", SEPARADOR);
    if(!es_respuesta_valida_3(*respuesta)){
        printf("Respuesta Inválida! Qué clase de reloj usas?\n");
        printf("%s", SEPARADOR);
        preguntar_3(respuesta);
    }
}

//Procedimientos de hacer la pregunta 4 y chequear la validez de las respuesta 
//Es recursiva, me pareció una buena solución para seguir preguntando hasta que la respuesta sea válida
//Como también se ocupa de validar la respuesta, debería funcionar siempre y cuando reciba el tipo de dato correcto
//Devuelve la respuesta en el parámetro pasado al procedimiento
//La respuesta que devuelve va a ser un int entre NOTA_MIN y NOTA_MAX (incl.)
//Falla cuando el usuario ingresa algo que no sea un número
void preguntar_4(int* respuesta){
    printf("Ingrese su respuesta\nLa respuesta debe ser: ");
    printf("Un número entero entre el %i y el %i. ", NOTA_MIN, NOTA_MAX);
    printf("Poner ÚNICAMENTE un número, no otro tipo de caracter\n");
    scanf(" %i", respuesta);
    printf("%s", SEPARADOR);
    if(!es_respuesta_valida_4(*respuesta)){
        printf("Respuesta Inválida! Que escalas tan raras usan para corregir hoy en día...\n");
        printf("%s", SEPARADOR);
        preguntar_4(respuesta);
    }
}


//<Funciones para el cálculo del score>

//Puntaje asociado a la respuesta 1
//Devuelve 0 si la respuesta se encuentra fuera del rango esperado
//Rango esperado: caracteres TRINEO, NAVE, CAMION o ALFOMBRA
//Debería recibir sólamente valores dentro del rango esperado
int valor_res_1(char respuesta){
    int valor = 0;

    if(respuesta == TRINEO || respuesta == NAVE){
        valor = VALOR_T_N;
    } else if(respuesta == CAMION || respuesta == ALFOMBRA){
        valor = VALOR_C_A;
    }

    return valor;
}

//Puntaje asociado a la respuesta 2
//Devuelve 0 si la respuesta se encuentra fuera del rango esperado
//Rango esperado: caracteres BOLAS_DE_NIEVE, PIUM_PIUM, KUCHAU o GENIO
//Debería recibir sólamente valores dentro del rango esperado
int valor_res_2(char respuesta){
    int valor = 0;

    switch(respuesta){
        case BOLAS_DE_NIEVE:
            valor = VALOR_B; 
            break;

        case PIUM_PIUM:
            valor = VALOR_P;
            break;

        case KUCHAU:
            valor = VALOR_K;
            break;

        case GENIO:
            valor = VALOR_G;
            break;

        default:
            break;
    }
    return valor;
}

//"Puntaje" asociado a la respuesta 3
//En verdad,como solo nos interesa si la hora es menor o mayor a cierta hora, se puede usar un bool
//Funciona para cualquier variable del tipo correcto, pero debería recibir únicamente datos dentro del rango esperado
//Rango esperado: entre HORA_MIN y HORA_MAX para la parte entera y menor a MINUTOS_MAX para la parte decimal
//Decidí nombrarla así y no llego_temprano o algo parecido por la consistencia con el resto de nombres
bool valor_res_3(float respuesta_3){ 
    return(respuesta_3 < HORA_PARCIAL);
}

//Puntaje asociado a la respuesta 4
//Devuelve 0 si la respuesta se encuentra fuera del rango esperado
//Rango esperado: número entre NOTA_MIN y NOTA_MAX 
//Debería recibir sólamente valores dentro del rango esperado, ya que la respuesta debería haber sido validada antes
int valor_res_4(int respuesta){
    int valor = 0;

    if(respuesta >= NOTA_MIN && respuesta <= TOPE_MULT_1){
        valor = MULT_1;
    } else if(respuesta > TOPE_MULT_1 && respuesta <= TOPE_MULT_2){
        valor = MULT_2;
    } else if(respuesta > TOPE_MULT_2 && respuesta <= TOPE_MULT_3){
        valor = MULT_3;
    } else if(respuesta > TOPE_MULT_3 && respuesta <= NOTA_MAX){
        valor = MULT_4;
    }
    return valor;
}

//Cálculo del score total
//Aunque siempre devuelve algo, debería recibir únicamente datos válidos para res_1, res_2 y res_4
//Rangos esperados:
//res_1: caracteres TRINEO, NAVE, CAMION o ALFOMBRA
//res_2: caracteres BOLAS_DE_NIEVE, PIUM_PIUM, KUCHAU o GENIO
//res_4: número entre NOTA_MIN y NOTA_MAX
//Devuelve un int entre 13 y 68 inclusive
int obtener_score(char res_1, char res_2, int res_4){
    return valor_res_1(res_1) + (valor_res_2(res_2)*valor_res_4(res_4));
}

//Cálculo del personaje según el score obtenido y la respuesta a la pregunta 3
//hora_llegada debería estar dentro del rango esperado
//Rango esperado: entre HORA_MIN y HORA_MAX para la parte entera y menor a MINUTOS_MAX para la parte decimal 
//score debe ser cálculado por la función obtener_score con datos válidos para esa función (un int entre 13 y 68 inc.)
//Devuelve ' ' si llega a haber un problema al calcular el score
//Debería devolver un personaje aunque los datos sean inválidos, por lo que los datos deberían ser pre-validados
char obtener_personaje(int score, float hora_llegada){

    bool es_score_bajo = (score <= TOPE_SCORE_BAJO);
    bool llego_temprano = (valor_res_3(hora_llegada));

    //Combino las 2 respuestas en un número entre 0 y 3, equivalente a un número binario de 2 bits
    //Como son 4 casos correspondientes a la combinación del cumplimiento de 2 condiciones, se puede usar esta solución
    //El primer bit (de derecha a izquierda) es si llegó temprano, y el segundo si el score es bajo
    int id_personaje = ((int)es_score_bajo)*2 + ((int) llego_temprano);
    
    char personaje = ' '; 
    switch (id_personaje){
    //como los casos representan un número de 2 bits, es mucho mejor usarlos como literales que definir constantes
    case 0: //score alto + llegó tarde (00)
        personaje = MCQUEEN;
        break;
    
    case 1: //score alto + llego temprano (01)
        personaje = JASMIN;
        break;
    
    case 2: //score bajo + llego tarde (10)
        personaje = OLAF;
        break;
    
    case 3: //score bajo + llega temprano (11)
        personaje = STITCH;
        break;
    
    default:
        break;
    }
    return personaje;
}

//Imprime el personaje obtenido y un mensaje final según el resultado
//Valores esperados: caracteres OLAF, STITCH, JASMIN o MCQUEEN
//Debería recibir un dato calculado por obtener_personaje
void imprimir_resultado(char personaje){
    printf("Has logrado rendir el parcial! Y lo rendiste con ");
    
    switch(personaje){
        case OLAF:
            printf("-Olaf-\n");
            printf("Lamentablemente en Gran Buenos Aires no hay mucha nieve para usar el trineo,\n"
                "pero igual fueron a tomar unos helados, así que fue un buen día al final =D.\n");
            break;

        case STITCH:
            printf("-Stitch-\n");
            printf("Las buena noticia es que la nave espacial es un medio de transporte muy efectivo cuando hay paros!\n"
                "La mala es que \"Ohana significa familia\" no era la respuesta a ninguna pregunta del final.\n");
            break;
        
        case JASMIN:
            printf("-Jasmín-\n");
            printf("Estudiaste con los mejores tutores de la corte, el Genio les puso su playlist de lofi hip hop para que"
                "se concentren y encima cayeron a la facu en una alfombra voladora. La mejor compañera de estudios que hay.\n");
            break;

        case MCQUEEN:
            printf("-Rayo McQueen-\n");
            printf("Son TAN VELOCES estudiando, que ya estudiaron para este final y los siguientes 5 finales,\n"
                "pero Mac también adhirió al paro camionero y no pudieron llegar a la facu,\n"
                "así que pasaron el final para la siguiente fecha y se fueron a echar unas carreritas con Francesco Virgolini.\n");
            break;

        default:
            printf("Si ves esto hubo un error: imprimir_resultado recibió un personaje inválido :(\n");
            break;
    } 
}


//||MAIN||

int main(){
    msj_intro();

    // Primera pregunta
    char respuesta_1 = ' ';
    printf("Estás saliendo de tu casa, y te enteras que hay paro de trenes, ¿Qué otro transporte elegís?\n");
    preguntar_1(&respuesta_1);
    msj_preg_1(respuesta_1);

    // Segunda pregunta
    char respuesta_2 = ' ';
    printf("En medio del camino te encuentras con una manifestación, ¿Que medio utilizas para deshacerte de la manifestación?\n");
    preguntar_2(&respuesta_2);
    msj_preg_2(respuesta_2);

    // Tercera pregunta
    float respuesta_3 = -1.0f;
    printf("Lograste superar la manifestación, ¿A qué hora conseguiste llegar a la universidad?\n");
    preguntar_3(&respuesta_3);
    msj_preg_3(respuesta_3);

    // Cuarta pregunta
    int respuesta_4 = -1;
    printf("Por fin llegó la nota del parcial! ¿Qué nota lograste sacarte?\n");
    preguntar_4(&respuesta_4);
    msj_preg_4(respuesta_4);

    //Cálculo del personaje obtenido
    int score = obtener_score(respuesta_1, respuesta_2, respuesta_4);
    char personaje = obtener_personaje(score, respuesta_3);
    
    //Mensaje final
    imprimir_resultado(personaje);

    return 0;
}
