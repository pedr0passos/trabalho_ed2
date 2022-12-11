#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

typedef struct {
    char nome[100];
    char sexo;
    int idade;
    int musicas[5];
} pesquisa;

typedef struct no {
    pesquisa pessoa;
    struct no *proximo;
}no_lista;

void l();
void adiciona (no_lista **lista);
void cria (no_lista **lista);
void limpa_buffer();

int main(){
setlocale(LC_ALL, "portuguese");
// variaveis para o funcionamento do menu
bool iniciador = true;
int escolha;
no_lista *lista_pessoas;
cria(lista_pessoas); 

    while (iniciador) {
        printf("Menu:\n");
        printf("1 - Adicionar Pessoa à Pesquisa.\n");
        printf("Escolha: ");
        scanf("%d", &escolha);
        switch (escolha) {
            case 1:        
                system("cls");   
                adiciona(lista_pessoas);             
            break;
            default:
                iniciador = false;
            break;
        }
    }

return 0;
}

void l(){
    printf("\n---------------------------------------------\n");
}

void cria (no_lista **lista) {
    *lista = NULL;
}

void limpa_buffer() {
    setbuf(stdin, NULL);
}

void adiciona (no_lista **lista) {
    no_lista *novo = malloc(sizeof(no_lista));
    if ( novo != NULL ) {
        printf("Nome: ");
        limpa_buffer();
        scanf("%[^\n]", novo->pessoa.nome);
        printf("Sexo ([M]-Masculino [F]-Feminino) :");
        limpa_buffer();
        scanf("%c", novo->pessoa.sexo);
        printf("Idade: ");
        scanf("%d", novo->pessoa.idade);
        printf("Digite as 5 Músicas:\n");
        int i = 0;
        while ( i < 5 ) {
            scanf("%d", novo->pessoa.musicas[i]);
            if ( novo->pessoa.musicas[i] <= 30 && novo->pessoa.musicas[i] >= 1 ) {
                i++;
            } else {
                novo->pessoa.musicas[i] = 0;
                printf("Músicas Inválida.");
            }
        }
        novo->proximo = (*lista);
        (*lista) = novo;
    } else {
        printf("Falha ao Alocar Memória.\n");
    }
}