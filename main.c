#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define TRUE 1
#define FALSE 0 

/*----------------------------------------------------------------------------
                            ESTRUTURAS DO PROGRAMA:
----------------------------------------------------------------------------*/

typedef struct p {
    char nome[100];
    char sexo;
    int idade;
    int musicas[5];
}pessoa;

typedef struct lista {
    pessoa p;
    struct lista *proximo;
}no;

/*----------------------------------------------------------------------------
                            CABEÇALHO DAS FUNÇÕES:
----------------------------------------------------------------------------*/

void limpa_buffer();
void limpa_terminal();
void cria_lista(no **lista);
int vazia(no **lista);
pessoa *le_pessoa();
void insere(no **lista, pessoa nova);
void imprime(no **lista);
void linha();

/*----------------------------------------------------------------------------
                                    MAIN:
----------------------------------------------------------------------------*/

int main () {

    pessoa *p;
    no *l;
    int laco = TRUE;
    // criando a lista
    cria_lista(&l);
    
    int opcao;
    while(laco) {
        printf("1 - Adicionar Pesquisa\n");
        printf("2 - Imprimir Pesquisa\n");
        printf("OPCAO: ");
        scanf("%d", &opcao);
        switch (opcao) {
        case 1:;
            limpa_terminal();
            p = le_pessoa();
            insere(&l, *p);
            limpa_terminal();
        break;
        case 2:;
            limpa_terminal();
            imprime(&l);
        break; 
        default:
            printf("Programa Encerrado!");
            laco = FALSE;
        break;
        }
    }
    return 0;
}
/*----------------------------------------------------------------------------
                            FUNÇÕES DO AUXILIARES:
----------------------------------------------------------------------------*/

void limpa_buffer() {
    setbuf(stdin, NULL);
}

void limpa_terminal(){
    system("cls");
}

void linha() {
    printf("\n\n-----------------------------------------------------------------------\n");
}

/*----------------------------------------------------------------------------
                            FUNÇÕES DO PROGRAMA:
----------------------------------------------------------------------------*/

void cria_lista(no **lista){
    *lista = NULL;
}

int vazia(no **lista) {
    return (*lista == NULL);

}

pessoa *le_pessoa() {        

    pessoa *novo = (pessoa*)malloc(sizeof(pessoa));

    printf("Nome: ");
    limpa_buffer();
    scanf("%[^\n]", novo->nome);
    
    printf("Idade: ");
    scanf("%d", &novo->idade);
    
    printf("Sexo (M ou F): ");
    limpa_buffer();
    scanf("%c", &novo->sexo);

    printf("Musicas:\n");
    int i = 0;
    while (i < 5) {
        printf("%d: ",i+1);
        scanf("%d", &novo->musicas[i]);
        if ( novo->musicas[i] > 30 || novo->musicas[i] < 0 )
            printf("Valor Invalido! Tente Novamente\n");
        else 
            i++;
    }

    return novo;

}

void insere( no **lista, pessoa nova ) {
    no *novo_no = malloc(sizeof(no));
    novo_no->p = nova;
    novo_no->proximo = (*lista);
    (*lista) = novo_no;
}

void imprime (no **lista) {
    linha();
    if (!vazia(lista)) {
        for (no *p = (*lista); p!= NULL; p = p->proximo )
            printf("Nome: %s | Idade: %d | Sexo: %c\n", p->p.nome, p->p.idade, p->p.sexo);
    } else {
        printf("Lista Vazia");
    }
    linha();
}
