#include <stdio.h>
#include <stdbool.h>

int main(){
    char var1 = 'a';
    char var2 = 'b';
    bool var3 = var1 > var2;
    bool var4 = !var3;

    printf("%i%i\n", (int)var3, (int)var4);

    return 0;
}