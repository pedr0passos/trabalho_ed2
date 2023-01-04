#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

// caminho : C:\Users\rocha\GitHub\trabalho_ed2

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
#define MaxMusicas 30

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

typedef struct m {
    int musica;
    int quantidade;
}musicas;

/*----------------------------------------------------------------------------
                            CABEÇALHO DAS FUNÇÕES:
----------------------------------------------------------------------------*/

void linha();
void limpa_buffer();
int vazia(no **lista);
void limpa_terminal();
void imprime(no **lista);
void cria_lista(no **lista);
void adiciona_pesquisa (musicas *m, int musica_escolhida);
pessoa *le_pessoa(musicas *m);
int calcula_meio(int ini, int fim);
void cria_lista_musicas(musicas *m);
void insere(no **lista, pessoa nova);
void pega_do_arquivo( FILE *arq, no **lista1, no **lista2, no **lista3, no **lista4 );

/*----------------------------------------------------------------------------
                                    MAIN:
----------------------------------------------------------------------------*/

int main () {

    musicas m[MaxMusicas];
    pessoa *p;
    int laco = TRUE;

    no *lista1, *lista2, *lista3, *lista4;

    //lista1 = Masculino que possuem idade <= 20
    //lista2 = Masculino que possuem idade > 20
    //lista3 = Feminino que possuem idade <= 20
    //lista4 = Feminino que possuem idade > 20

    cria_lista(&lista1);
    cria_lista(&lista2);
    cria_lista(&lista3);
    cria_lista(&lista4);
    cria_lista_musicas(m);

    FILE *arquivo = fopen("pesquisa.txt", "r");
    
    if ( arquivo != NULL )
        printf("Arquivo Aberto\n");

    pega_do_arquivo(arquivo, &lista1, &lista2, &lista3, &lista4);

    int opcao;
    while(laco) {
        printf("1 - Adicionar a Pesquisa\n");
        printf("2 - Imprimir Pesquisa\n");
        printf("3 - Sair\n");
        printf("OPCAO: ");
        scanf("%d", &opcao);
        switch (opcao) {
        case 1:;
            limpa_terminal();
            p = le_pessoa(m);
            
            if ( (p->idade <= 20) && (strcmp(&p->sexo, "M") == 0) ) 
                insere(&lista1, *p);

            if ( (p->idade > 20) && (strcmp(&p->sexo, "M") == 0) ) 
                insere(&lista2, *p);

            if ( (p->idade <= 20) && (strcmp(&p->sexo, "F") == 0) )
                insere(&lista3, *p);

            if ( (p->idade > 20) && (strcmp(&p->sexo, "F") == 0) )
                insere(&lista4, *p);

            limpa_terminal();
        break;
        case 2:;
            limpa_terminal();
            printf("Escolha qual categoria:\n1 - MASCULINO COM IDADE MAIOR QUE 20 | 2 - MASCULINO COM IDADE MENOR OU IGUAL A 20\n3 - FEMININO COM IDADE MAIOR QUE 20  | 4 - FEMININO COM IDADE MENOR OU IGUAL A 20\n5 - TODAS\n");
            printf("Escolha: ");
            scanf("%d", &opcao);
            switch (opcao) {
                case 1:;   
                    linha();
                    imprime(&lista1);
                    linha();
                break;
                case 2:;
                    linha();
                    imprime(&lista2);
                    linha();
                break;
                case 3:;
                    linha();
                    imprime(&lista3);
                    linha();
                break;
                case 4:;
                    linha();
                    imprime(&lista4);
                    linha();
                break;
                case 5:;
                    linha();
                    printf("MASCULINO COM IDADE MAIOR QUE 20:\n");
                    imprime(&lista1);
                    printf("MASCULINO COM IDADE MENOR OU IGUAL A 20:\n");
                    imprime(&lista2);
                    printf("FEMININO COM IDADE MAIOR QUE 20:\n");                    
                    imprime(&lista3);
                    printf("FEMININO COM IDADE MENOR OU IGUAL A 20:\n");
                    imprime(&lista4);
                    linha();
                break;
            default:
                printf("Opcao Invalida\n");
                break;
            }
        break; 
        default:
            printf("Programa Encerrado!\n");
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
    printf("-----------------------------------------------------------------------\n");
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

pessoa *le_pessoa(musicas *m) {        

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
        else {
            adiciona_pesquisa(m, novo->musicas[i]);
            i++;
        }

    }

    return novo;

}

void insere(no **lista, pessoa nova) {
    no *novo_no = malloc(sizeof(no));
    novo_no->p = nova;
    novo_no->proximo = (*lista);
    (*lista) = novo_no;
}

void imprime (no **lista) {

    if (!vazia(lista)) {
        for (no *p = (*lista); p!= NULL; p = p->proximo )
            printf("Nome: %s | Idade: %d | Sexo: %c\n", p->p.nome, p->p.idade, p->p.sexo);
    } else {
        printf("Lista Vazia\n");
    }

}

void cria_lista_musicas(musicas *m) {
    for (int i = 0; i < MaxMusicas; i++) {
        m[i].musica = i+1; 
        m[i].quantidade = 0;
    }
}

void adiciona_pesquisa(musicas *m, int musica_escolhida) {

    int inicio, meio, fim;

    inicio = 0;
    fim = MaxMusicas-1;
    meio = ((inicio+fim)/2);

    while ( inicio <= fim ) {
        if ( m[meio].musica == musica_escolhida ){
            m[meio].quantidade++;
            break;
        } else if (musica_escolhida > m[meio].musica ) {
            inicio = meio+1;
        } else {
            fim = meio-1;
        }
         meio = ((inicio+fim)/2);  
         printf("while\n");
    }

}

void pega_do_arquivo( FILE *arq, no **l1, no **l2, no **l3, no **l4 ) {
    
    pessoa *p = malloc(sizeof(pessoa));

    while ( fscanf(arq, "%[^\t]\t%c\t%d\t", p->nome, &p->sexo, &p->idade) != EOF ) {

        no *l = malloc(sizeof(no));
        int aux, i=0;

        while ( fscanf(arq, "%d ", &aux) == 1 ) {
            p->musicas[i] = aux;
            i++;
        }

        if ( (p->idade <= 20) && (strcmp(&p->sexo, "M") == 0) ) {
            printf("Inseriu\n");
            insere(l1, *p);
        }
        if ( (p->idade > 20) && (strcmp(&p->sexo, "M") == 0) ) 
            insere(l2, *p);

        if ( (p->idade <= 20) && (strcmp(&p->sexo, "F") == 0) )
            insere(l3, *p);

        if ( (p->idade > 20) && (strcmp(&p->sexo, "F") == 0) )
            insere(l4, *p);

    }

}