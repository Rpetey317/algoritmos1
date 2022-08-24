#include <stdio.h>
#include <stdbool.h>

int main(){
    bool var1 = true;
    bool var2 = false;
    bool var3 = true;
    int var4 = ((int) var1) + ((int) var3);
    printf("%i, %i, %i\n", var1, var2, var4);

    return 0;
}
