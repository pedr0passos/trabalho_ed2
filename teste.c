#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    char palavra1[50] = {"bola"}; // \0
    char palavra2[50] = {"abacate"};

    printf("\nAntes de copiar:\npalavra 1: %s\npalavra2: %s\n", palavra1, palavra2);

    strcpy(palavra2, palavra1);

    printf("\nDepois de copiar:\npalavra 1: %s\npalavra2: %s\n", palavra1, palavra2);

    return 0;
}
