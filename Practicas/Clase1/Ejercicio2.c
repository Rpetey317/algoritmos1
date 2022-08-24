#include<stdio.h>

int main(){

    printf("Caso 1:\n\n");
    for (int i = 1; i <= 20; i++){
    printf("Hey Heihei, el número es %i\n", i);
    }

    printf("\nCaso 2:\n\n");
    int i = 20;
    do{
        printf("Hey Heihei, el número es %i\n", i);
        i--;
    } while (i >= 1);

    return 0;
}
