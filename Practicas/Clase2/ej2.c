#include <stdio.h>
#include <stdbool.h>

const int NUM_EXP_STITCH = 720;

void pedir_lilo(char* letra_lilo){
    printf("Lilo decime tu letra pls\n");
    scanf(" %c", letra_lilo);
}
void pedir_stitch(char* letra_stitch){
    printf("Ahora decime la tuya Stitch\n");
    scanf(" %c", letra_stitch);
}
bool es_numero_valido(int num){
    return (num > 0 && num <= NUM_EXP_STITCH);
}
void pedir_numero(int* num_lilo){
    printf("A ver Lilo, ahora decime un numero\n");
    scanf(" %i", num_lilo);
    while (es_numero_valido(*num_lilo) == false){
        printf("Ese numero no Lilo! El numero debe estar entre 1 y %i\n", NUM_EXP_STITCH);
        scanf(" %i", num_lilo);
    }
}
void imprimir_divisores(int num){
    for(int i = 1; i <= num; i++){
        if (num%i == 0){
            printf("%i es un divisor de %i\n", i, NUM_EXP_STITCH);
        }   
    }
}

int main(){

    char letra_lilo;
    pedir_lilo(&letra_lilo);
    char letra_stitch;
    pedir_stitch(&letra_stitch);

    printf("La letra de Lilo es %c, y la de Stictch es %c\n", letra_lilo, letra_stitch);

    while (letra_stitch != letra_lilo + 1){
        printf("Estas mal Stitch! La letra que sigue a %c no es %c! Vuelve a intentarlo:\n", letra_lilo, letra_stitch);
        pedir_stitch(&letra_stitch);
    }

    printf("Muy bien Stitch!\n");

    int numero_lilo;
    pedir_numero(&numero_lilo);
    printf("A ver... los divisores de %i menores que %i son:\n", NUM_EXP_STITCH, numero_lilo);
    imprimir_divisores(numero_lilo);
    
    return 0;
}
