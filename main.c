#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct p {
    char nome[100];
    int idade;
    char sexo;
}pessoa;



int main () {



    pessoa p;
    printf("Nome: ");
    printf("Idade: ");
    printf("Sexo: ");
    printf("Músicas: ");

    return 0;
}

void localiza(){
    setlocale(LC_ALL, "portuguese");
}