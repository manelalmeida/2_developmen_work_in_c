#include <stdio.h>
    
    int dobrar (int x){return x * 2;}

    int triplicar (int x){return x * 3;}

    int quadrado (int x){return x * x;}

int main(){

    int (*calculos[2])(int) = {dobrar, triplicar, quadrado};

    
}
