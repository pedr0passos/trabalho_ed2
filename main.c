#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

// lista encadeada com toda a pesquisa

/* 4 listas encadeadas que possuem as pessoas que mencionaram em primeiro lugar (posicao 0 do vetor) uma das tres musicas mais populares da ca:
    - Masculino que possuem idade <= 20
    - Masculino que possuem idade > 20 
    - Feminino que possuem idade <= 20
    - Feminino que possuem idade > 20 
*/ 

// vetor com 30 posições que possui a musica e a quantidade de vezes que ela foi mencionada

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

typedef struct lista_musicas {
    int musica;
    int quantidade;
}no_musica;

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
    no *pesquisa;
    int laco = TRUE;

    no *lista1, *lista2, lista3, lista4;

    //lista1 = Masculino que possuem idade <= 20
    //lista2 = Masculino que possuem idade > 20
    //lista3 = Feminino que possuem idade <= 20
    //lista4 = Feminino que possuem idade > 20

    cria_lista(&lista1);
    cria_lista(&lista2);
    cria_lista(&lista3);
    cria_lista(&lista4);

    int opcao;
    while(laco) {
        printf("1 - Adicionar Pesquisa\n");
        printf("2 - Imprimir Pesquisa Completa\n");
        printf("OPCAO: ");
        scanf("%d", &opcao);
        switch (opcao) {
        case 1:;
            limpa_terminal();
            p = le_pessoa();
            
            if ( (p->idade <= 20) && (strcmp(p->sexo, "M") == 0) ) 
                insere(&lista1, *p);

            if ( (p->idade > 20) && (strcmp(p->sexo, "M") == 0) ) 
                insere(&lista2, *p);

            if ( (p->idade <= 20) && (strcmp(p->sexo, "F") == 0) )
                insere(&lista3, *p);

            if ( (p->idade > 20) && (strcmp(p->sexo, "F") == 0) )
                insere(&lista4, *p);

            limpa_terminal();
        break;
        case 2:;
            limpa_terminal();
            imprime(&pesquisa);
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
                            FUNÇÕES AUXILIARES:
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

