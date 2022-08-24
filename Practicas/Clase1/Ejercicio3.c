#include<stdio.h>

int main(){

    for (int i = 1; i <= 10; i++){
        if(i%2 == 0){
            printf("Hey Heihei, el número %i es par\n", i);
        } else {
            printf("Hey Heihei, el número %i es impar\n", i);
            } 
    }

    //Variante con while
    int i = 1;
    while (i <= 10){
        if(i%2 == 0){
            printf("Hey Heihei, el número %i es par\n", i);
        } else {
            printf("Hey Heihei, el número %i es impar\n", i);
            } 
        i++;
    }

    return 0;
}
