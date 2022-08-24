#ifndef __PERSONAJE_H__
#define __PERSONAJE_H__

#include <stdio.h>
#include <stdbool.h>

// Personajes
#define OLAF 'O'
#define STITCH 'S'
#define JASMIN 'J'
#define MCQUEEN 'R'

//Mensaje introductorio a las preguntas
void msj_intro_companero();

//Mensaje respuesta a la pregunta del transporte según lo que haya ingresado el usuario
//Manda un mensaje de error si la respuesta se encuentra fuera del rango esperado
//Rango esperado: caracteres TRINEO, NAVE, CAMION o ALFOMBRA
//Debería recibir sólamente valores dentro del rango esperado
void msj_preg_transporte(char respuesta);

//Mensaje respuesta a la pregunta 2 según lo que haya ingresado el usuario
//Manda un mensaje de error si la respuesta se encuentra fuera del rango esperado
//Rango esperado: caracteres BOLAS_DE_NIEVE, PIUM_PIUM, KUCHAU o GENIO
//Debería recibir sólamente valores dentro del rango esperado
void msj_preg_marcha(char respuesta);

//Mensaje respuesta a la pregunta 3 según lo que haya ingresado el usuario
//Manda un mensaje de error si la respuesta se encuentra fuera del rango esperado
//Rango esperado: entre HORA_MIN y HORA_MAX para la parte entera y menor a MINUTOS_MAX para la parte decimal
//Debería recibir sólamente valores dentro del rango esperado
void msj_preg_hora(float respuesta);

//Mensaje respuesta a la pregunta 4 según lo que haya ingresado el usuario
//Manda un mensaje de error si la respuesta se encuentra fuera del rango esperado
//Rango esperado: número entre el NOTA_MIN y NOTA_MAX
//Debería recibir sólamente valores dentro del rango esperado
void msj_preg_nota(int respuesta);

//Procedimientos de hacer la pregunta del transporte y chequear la validez de las respuesta 
//Como también se ocupa de validar la respuesta, debería funcionar siempre y cuando reciba el tipo de dato correcto
//Devuelve la respuesta en la variable respuesta
//La respuesta va a ser TRINEO, NAVE, CAMION o ALFOMBRA
void preguntar_transporte(char* respuesta);

//Procedimientos de hacer la pregunta de la marcha y chequear la validez de las respuesta 
//Como también se ocupa de validar la respuesta, debería funcionar siempre y cuando reciba el tipo de dato correcto
//Devuelve la respuesta en la variable respuesta
//La respuesta va a ser BOLAS_DE_NIEVE, PIUM_PIUM, KUCHAU o GENIO
void preguntar_marcha(char* respuesta);

//Procedimientos de hacer la pregunta de la hora y chequear la validez de la respuesta 
//Como también se ocupa de validar la respuesta, debería funcionar siempre y cuando reciba el tipo de dato correcto
//Devuelve la respuesta en la variable respuesta
//La respuesta que devuelve va a ser un float:
//Su parte entera va estar entre HORA_MIN y HORA_MAX incl. y la parte decimal va a ser menor a MINUTOS_MAX no incl.
//Falla cuando el usuario ingresa algo que no sea un número
void preguntar_hora(float* respuesta);

//Procedimientos de hacer la pregunta 4 y chequear la validez de la respuesta 
//Como también se ocupa de validar la respuesta, debería funcionar siempre y cuando reciba el tipo de dato correcto
//Devuelve la respuesta en la variable respuesta
//La respuesta que devuelve va a ser un int entre NOTA_MIN y NOTA_MAX (incl.)
//Falla cuando el usuario ingresa algo que no sea un número
void preguntar_nota(int* respuesta);

//Devuelve el personaje según las respuestas dadas
//Las 4 respuestas deben ser obtenidas por preguntar_transporte, marcha, etc.
//Devuelve ' ' si llega a haber un problema al calcular el score
char obtener_personaje(char transporte, char marcha, float hora, int nota);

//Imprime el personaje obtenido y un mensaje final según el resultado
//Valores esperados: caracteres OLAF, STITCH, JASMIN o MCQUEEN
//Debería recibir un dato calculado por obtener_personaje
void imprimir_personaje(char personaje);

#endif // __PERSONAJE_H__ 