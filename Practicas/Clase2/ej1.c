#include <stdio.h>

#define ID_DORMILON 1
#define ID_GRUNHON 2
#define ID_TONTIN 3 //el switch no funciona con const, solo con define
const char DORMILON = 'D';
const char GRUNHON = 'G';
const char TONTIN = 'T';
const char ERROR = 'E';

char enanoName(int id_enano){
    
    switch (id_enano){
    case ID_DORMILON:
        return(DORMILON);
        break;
    case ID_GRUNHON:
        return(GRUNHON);
        break;
    case ID_TONTIN:
        return(TONTIN);
        break;
    
    default:
        return(ERROR);
        break;
    }
}

int main(){

    int id_enano = 2;
    char inic_enano = enanoName(id_enano);
    printf("Este enano es %c\n", inic_enano);

    return 0;
}
