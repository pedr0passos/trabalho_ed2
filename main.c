#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

// caminho : C:\Users\rocha\GitHub\trabalho_ed2

// lista encadeada com toda a pesquisa

/* 4 listas encadeadas que possuem as pessoas que mencionaram em primeiro lugar (posicao 0 do vetor) uma das tres musicas mais populares entre as 30:
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
void cria_lista_musicas(musicas *m);
void insere(no **lista, pessoa nova);
void le_arquivo( FILE *arq, no **lista1, no **lista2, no **lista3, no **lista4, musicas *m );
void grava( no **l1, no **l2, no **l3, no **l4, musicas *m );
void encerra(no **l1, no **l2, no **l3, no **l4, musicas *m );
void insere_do_arquivo(no **lista, pessoa nova);
void imprime_musicas(musicas *m, int tamanho);

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

    le_arquivo(arquivo, &lista1, &lista2, &lista3, &lista4, m);

    int opcao;
    while(laco) {
        printf("1 - Adicionar a Pesquisa\n");
        printf("2 - Imprimir Pesquisa\n");
        printf("3 - Musicas mais Populares\n");
        printf("4 - Sair\n");
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
            printf("Escolha qual categoria:\n1 - MASCULINO COM IDADE MENOR OU IGUAL A 20 | 2 - MASCULINO COM IDADE MAIOR 20\n3 - FEMININO COM IDADE MENOR OU IGUAL A 20  | 4 - FEMININO COM IDADE MAIOR 20\n5 - TODAS\n");
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
                    printf("MASCULINO COM IDADE MENOR OU IGUAL A 20:\n");
                    imprime(&lista1);
                    linha();
                    printf("MASCULINO COM IDADE MAIOR QUE 20:\n");
                    imprime(&lista2);
                    linha();
                    printf("FEMININO COM IDADE MENOR OU IGUAL A 20:\n");                    
                    imprime(&lista3);
                    linha();
                    printf("FEMININO COM IDADE MAIOR QUE 20:\n");
                    imprime(&lista4);
                    linha();
                break;
                default:;
                    printf("Opcao Invalida!\n");                
            }
        break; 
        case 3:;
            linha();
            imprime_musicas(m, MaxMusicas);
            linha();
        break;
        default:
            encerra(&lista1, &lista2, &lista3, &lista4, m);
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

int vazia(no **lista) {
    return (*lista == NULL);
}

/*----------------------------------------------------------------------------
                            FUNÇÕES DO PROGRAMA:
----------------------------------------------------------------------------*/

void cria_lista(no **lista){
    *lista = NULL;
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


    printf("Musicas (1-30):\n");
    int i = 0;
    while (i < 5) {
        printf("%d: ",i+1);
        scanf("%d", &novo->musicas[i]);
        if ( novo->musicas[i] > 30 || novo->musicas[i] < 0 )
            printf("Valor Invalido! Tente Novamente\n");
        else {
            int repetido = FALSE;
            if (i > 0) {
                for (int j = 0; j < i; j++) {
                    if ( novo->musicas[i] == novo->musicas[j] ) {
                        printf("Valor Repetido! Tente Novamente\n");
                        repetido = TRUE;
                    }
                }                
            } 
            if (repetido == FALSE) {
                adiciona_pesquisa(m, novo->musicas[i]);
                i++;
            }
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

void insere_do_arquivo(no **lista, pessoa nova) {

    no *novo_no = malloc(sizeof(no));
    novo_no->p = nova;

    if (!vazia(lista)) {
        no *auxiliar;
        for ( auxiliar = (*lista); auxiliar->proximo != NULL; auxiliar = auxiliar->proximo );
        novo_no->proximo = NULL;
        auxiliar->proximo = novo_no;
    } else {
        novo_no->proximo = NULL;
        (*lista) = novo_no;
    }


}

void imprime (no **lista) {

    if (!vazia(lista)) {
        for (no *p = (*lista); p!= NULL; p = p->proximo )
            printf("Nome: %s | Idade: %d | Sexo: %c | Musicas: %d %d %d %d %d\n", p->p.nome, p->p.idade, p->p.sexo, p->p.musicas[0], p->p.musicas[1], p->p.musicas[2], p->p.musicas[3], p->p.musicas[4]);
    } else {
        printf("Lista Vazia!\n");
    }

}

void cria_lista_musicas(musicas *m) {
    for (int i = 0; i < MaxMusicas; i++) {
        m[i].musica = i+1; 
        m[i].quantidade = 0;
    }
}

void adiciona_pesquisa(musicas *m, int musica_escolhida) {
    int i;
    for (i = 0; i < MaxMusicas; i++) {
        if ( m[i].musica == musica_escolhida ) {
            m[i].quantidade++;
        }
    }
}

void le_arquivo( FILE *arq, no **l1, no **l2, no **l3, no **l4, musicas *m ) {
    
    pessoa *p = malloc(sizeof(pessoa));

    while ( fscanf(arq, "%[^\t]\t%c\t%d\t%d %d %d %d %d\n", p->nome, &p->sexo, &p->idade, &p->musicas[0], &p->musicas[1], &p->musicas[2], &p->musicas[3], &p->musicas[4]) != EOF ) {

        no *l = malloc(sizeof(no));

        if ( (p->idade <= 20) && (strcmp(&p->sexo, "M") == 0) )
            insere_do_arquivo(l1, *p);

        if ( (p->idade > 20) && (strcmp(&p->sexo, "M") == 0) ) 
            insere_do_arquivo(l2, *p);

        if ( (p->idade <= 20) && (strcmp(&p->sexo, "F") == 0) )
            insere_do_arquivo(l3, *p);

        if ( (p->idade > 20) && (strcmp(&p->sexo, "F") == 0) )
            insere_do_arquivo(l4, *p);

        int auxiliar1, auxiliar2;
        int i = 0;
        while ( fscanf(arq, "%d %d\t", &auxiliar1, &auxiliar2) == 2 ) {
            printf("%d %d\n", auxiliar1, auxiliar2);
            m[i].musica = auxiliar1;
            m[i].quantidade = auxiliar2;
            i++;        
        }
    }


}

void grava( no **l1, no **l2, no **l3, no **l4, musicas *m ) {

    FILE *arq = fopen("pesquisa.txt", "w");

    // gravando a lista1
    for ( no *temporario = (*l1); temporario != NULL; temporario = temporario->proximo ) {
        fprintf(arq,"%s\t%c\t%d\t%d %d %d %d %d\n", temporario->p.nome, temporario->p.sexo, temporario->p.idade, temporario->p.musicas[0], temporario->p.musicas[1], temporario->p.musicas[2], temporario->p.musicas[3], temporario->p.musicas[4]);
    }
    // gravando a lista2
    for ( no *temporario = (*l2); temporario != NULL; temporario = temporario->proximo ) {
        fprintf(arq,"%s\t%c\t%d\t%d %d %d %d %d\n", temporario->p.nome, temporario->p.sexo, temporario->p.idade, temporario->p.musicas[0], temporario->p.musicas[1], temporario->p.musicas[2], temporario->p.musicas[3], temporario->p.musicas[4]);
    }
    // gravando a lista3
    for ( no *temporario = (*l3); temporario != NULL; temporario = temporario->proximo ) {
        fprintf(arq,"%s\t%c\t%d\t%d %d %d %d %d\n", temporario->p.nome, temporario->p.sexo, temporario->p.idade, temporario->p.musicas[0], temporario->p.musicas[1], temporario->p.musicas[2], temporario->p.musicas[3], temporario->p.musicas[4]);
    }
    // gravando a lista4
    for ( no *temporario = (*l4); temporario != NULL; temporario = temporario->proximo ) {
        fprintf(arq,"%s\t%c\t%d\t%d %d %d %d %d\n", temporario->p.nome, temporario->p.sexo, temporario->p.idade, temporario->p.musicas[0], temporario->p.musicas[1], temporario->p.musicas[2], temporario->p.musicas[3], temporario->p.musicas[4]);
    }
    // gravando a lista de musicas 
    for ( int i = 0; i < MaxMusicas; i++ ) {
        fprintf(arq, "%d %d\t", m[i].musica, m[i].quantidade);
    }

}

void encerra(no **l1, no **l2, no **l3, no **l4, musicas *m ) {
    linha();
    printf("Programa Encerrado!\n");
    linha();
    grava(l1, l2, l3, l4, m);
}

void imprime_musicas(musicas *m, int tamanho) {
    printf("MUSICAS MAIS POPULARES:\n");
    for ( int i = 0; i < tamanho; i++ ) 
        printf("Musica: %d | Quantidade: %d\n", m[i].musica, m[i].quantidade);
}