#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

// caminho : C:\Users\rocha\GitHub\trabalho_ed2

/* 
4 listas encadeadas que possuem as pessoas que mencionaram em primeiro lugar (posicao 0 do vetor) uma das tres musicas mais populares entre as 30:
    - Masculino que possuem idade <= 20
    - Masculino que possuem idade > 20 
    - Feminino que possuem idade <= 20
    - Feminino que possuem idade > 20 
*/ 

// 4 vetores com 30 posições que possui a musica e a quantidade de vezes que ela foi mencionada na categoria

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
pessoa *le_pessoa(musicas *m1, musicas *m2, musicas *m3, musicas *m4);
void cria_lista_musicas(musicas *m);
void insere(no **lista, pessoa nova);
void le_arquivo(FILE *arq, no **lista1, no **lista2, no **lista3, no **lista4, musicas *m1, musicas *m2, musicas *m3, musicas *m4);
void grava(no **l1, no **l2, no **l3, no **l4, musicas *m1, musicas *m2, musicas *m3, musicas *m4);
void encerra(no **l1, no **l2, no **l3, no **l4, musicas *m1, musicas *m2, musicas *m3, musicas *m4);
void insere_do_arquivo(no **lista, pessoa nova);
void imprime_musicas(musicas *m1, musicas *m2, musicas *m3, musicas *m4, int tamanho);
void imprime_top3(musicas *m1, musicas *m2, musicas *m3, musicas *m4, int tamanho);
int decrementa(int numero);
void shellsort(musicas *m, int t);
int calcula_h(int numero, int tamanho);

/*----------------------------------------------------------------------------
                                    MAIN:
----------------------------------------------------------------------------*/

int main () {

    musicas m1[MaxMusicas], m2[MaxMusicas], m3[MaxMusicas], m4[MaxMusicas];
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

    // 4 listas de musicas, gravam o resultado das musicas favoritas de cada categoria

    cria_lista_musicas(m1);
    cria_lista_musicas(m2);
    cria_lista_musicas(m3);
    cria_lista_musicas(m4);

    FILE *arquivo = fopen("pesquisa.txt", "r");
    
    if ( arquivo != NULL )
        printf("Arquivo Aberto\n");

    le_arquivo(arquivo, &lista1, &lista2, &lista3, &lista4, m1, m2, m3, m4);

    int opcao;
    while(laco) {
        printf("1 - Adicionar a Pesquisa\n");
        printf("2 - Imprimir Pesquisa\n");
        printf("3 - Musicas\n");
        printf("4 - Imprimir Top 3 Musicas mais Populares\n");
        printf("5 - Sair\n");        
        printf("OPCAO: ");
        scanf("%d", &opcao);
        switch (opcao) {
        case 1:;    //adiciona na pesquisa
            limpa_terminal();
            p = le_pessoa(m1,m2,m3,m4);
            
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
        case 2:;    // imprime as listas
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
        case 3:;    // imprime as musicas de cada categoria
            linha();
            imprime_musicas(m1,m2,m3,m4, MaxMusicas);
            linha();
        break;
        case 4:;    // imprime top3 das musicas de cada categoria
            linha();
            imprime_top3(m1,m2,m3,m4, MaxMusicas);
            linha();
        break;
        case 5:;    // encerra o programa
            encerra(&lista1, &lista2, &lista3, &lista4, m1, m2, m3, m4);
            laco = FALSE;
        break;
        default:;
            printf("Opcao Invalida!\n");
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

int decrementa(int numero) {
    numero = (numero-1)/3;
    return numero;
}

int calcula_h(int numero, int tamanho ) {
    while (numero < tamanho)
        numero = numero*3+1;
    return numero;
}

/*----------------------------------------------------------------------------
                            FUNÇÕES DO PROGRAMA:
----------------------------------------------------------------------------*/

void cria_lista(no **lista){
    *lista = NULL;
}

pessoa *le_pessoa(musicas *m1, musicas *m2, musicas *m3, musicas *m4) {        

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
        
                if ( novo->idade <= 20 && strcmp(novo->sexo, "M") == 0 )
                    adiciona_pesquisa(m1, novo->musicas[i]);

                if ( novo->idade > 20 && strcmp(novo->sexo, "M") == 0 )
                    adiciona_pesquisa(m2, novo->musicas[i]);

                if ( novo->idade <= 20 && strcmp(novo->sexo, "F") == 0 )
                    adiciona_pesquisa(m3, novo->musicas[i]);

                if ( novo->idade > 20 && strcmp(novo->sexo, "F") == 0 )
                    adiciona_pesquisa(m4, novo->musicas[i]);

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

void le_arquivo( FILE *arq, no **l1, no **l2, no **l3, no **l4, musicas *m1, musicas *m2, musicas *m3, musicas *m4 ) {
    
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

        // lendo a lista de musica 1
        int auxiliar1, auxiliar2, i;
        i = 0;
        while ( fscanf(arq, "%d %d\t", &auxiliar1, &auxiliar2) == 2 ) {
            m1[i].musica = auxiliar1;
            m1[i].quantidade = auxiliar2;
            i++;        
        }
        // lendo a lista de musicas 2
        i = 0;
        while ( fscanf(arq, "%d %d\t", &auxiliar1, &auxiliar2) == 2 ) {
            m2[i].musica = auxiliar1;
            m2[i].quantidade = auxiliar2;
            i++;        
        }
        // lendo a lista de musicas 3
        i = 0;
        while ( fscanf(arq, "%d %d\t", &auxiliar1, &auxiliar2) == 2 ) {
            m3[i].musica = auxiliar1;
            m3[i].quantidade = auxiliar2;
            i++;        
        }
        // lendo a lista de musicas 4
        i = 0;
        while ( fscanf(arq, "%d %d\t", &auxiliar1, &auxiliar2) == 2 ) {
            m4[i].musica = auxiliar1;
            m4[i].quantidade = auxiliar2;
            i++;        
        }
    }


}

void grava( no **l1, no **l2, no **l3, no **l4, musicas *m1, musicas *m2, musicas *m3, musicas *m4 ) {

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

    // gravando a lista de musicas 1
    for ( int i = 0; i < MaxMusicas; i++ ) {
        fprintf(arq, "%d %d\t", m1[i].musica, m1[i].quantidade);
    }
    fprintf(arq, "\n");
    // gravando a lista de musicas 2
    for ( int i = 0; i < MaxMusicas; i++ ) {
        fprintf(arq, "%d %d\t", m2[i].musica, m2[i].quantidade);
    }
    fprintf(arq, "\n");
    // gravando a lista de musicas 3
    for ( int i = 0; i < MaxMusicas; i++ ) {
        fprintf(arq, "%d %d\t", m3[i].musica, m3[i].quantidade);
    }
    fprintf(arq, "\n");
    // gravando a lista de musicas 4
    for ( int i = 0; i < MaxMusicas; i++ ) {
        fprintf(arq, "%d %d\t", m4[i].musica, m4[i].quantidade);
    }
    fprintf(arq, "\n");
}

void encerra(no **l1, no **l2, no **l3, no **l4, musicas *m1, musicas *m2, musicas *m3, musicas *m4 ) {
    linha();
    printf("Programa Encerrado!\n");
    linha();
    ordena(m1,m2,m3,m4, MaxMusicas);
    grava(l1, l2, l3, l4, m1,m2,m3,m4);
}

void imprime_musicas(musicas *m1, musicas *m2, musicas *m3, musicas *m4, int tamanho) {
    ordena(m1,m2,m3,m4,MaxMusicas);
    printf("MUSICAS MAIS POPULARES DE CADA CATEGORIA:\n\n");
    linha();
    printf("MASCULINO MENOR OU IGUAL A 20 ANOS:\n");
    for ( int i = 0; i < tamanho; i++ ) 
        if (m1[i].quantidade > 0 )
            printf("Musica: %d | Quantidade: %d\n", m1[i].musica, m1[i].quantidade);
    linha();
    printf("MASCULINO MAIOR QUE 20 ANOS:\n");
    for ( int i = 0; i < tamanho; i++ ) 
        if (m2[i].quantidade > 0 )
            printf("Musica: %d | Quantidade: %d\n", m2[i].musica, m2[i].quantidade);
    linha();
    printf("FEMININO MENOR OU IGUAL A 20 ANOS:\n");
    for ( int i = 0; i < tamanho; i++ ) 
        if (m3[i].quantidade > 0 )
            printf("Musica: %d | Quantidade: %d\n", m3[i].musica, m3[i].quantidade);
    linha();
    printf("FEMININO MAIOR QUE 20 ANOS:\n");
    for ( int i = 0; i < tamanho; i++ ) 
        if (m4[i].quantidade > 0 )
            printf("Musica: %d | Quantidade: %d\n", m4[i].musica, m4[i].quantidade);
    linha();

}

void imprime_top3(musicas *m1, musicas *m2, musicas *m3, musicas *m4, int tamanho) {
    ordena(m1,m2,m3,m4,MaxMusicas);
    printf("TOP 3 MUSICAS MAIS POPULARES DE CADA CATEGORIA:\n\n");
    linha();
    printf("MASCULINO MENOR OU IGUAL A 20 ANOS:\n");
    for ( int i = 0; i < 3; i++ ) 
        if (m1[i].quantidade > 0 )
            printf("TOP %d | Musica: %d | Quantidade: %d\n",(i+1), m1[i].musica, m1[i].quantidade);
    linha();
    printf("MASCULINO MAIOR QUE 20 ANOS:\n");
    for ( int i = 0; i < 3; i++ ) 
        if (m2[i].quantidade > 0 )
            printf("TOP %d | Musica: %d | Quantidade: %d\n",(i+1), m2[i].musica, m2[i].quantidade);
    linha();
    printf("FEMININO MENOR OU IGUAL A 20 ANOS:\n");
    for ( int i = 0; i < 3; i++ ) 
        if (m3[i].quantidade > 0 )
            printf("TOP %d | Musica: %d | Quantidade: %d\n",(i+1), m3[i].musica, m3[i].quantidade);
    linha();
    printf("FEMININO MAIOR QUE 20 ANOS:\n");
    for ( int i = 0; i < 3; i++ ) 
        if (m4[i].quantidade > 0 )
            printf("TOP %d | Musica: %d | Quantidade: %d\n",(i+1), m4[i].musica, m4[i].quantidade);
    linha();
}

void shellsort(musicas *m, int tamanho ) {
    int i, j, h;
    musicas auxiliar;

    h = 1;

    h = calcula_h(h, tamanho);

    while ( h > 1 ) {
        h = decrementa(h);
        for ( i = h; i < tamanho; i++ ) {
            auxiliar = m[i];
            j = i-h;
            while  ( j >= 0 && auxiliar.quantidade > m[j].quantidade ) {
                m[j+h] = m[j];
                j = j - h;
            }
            if ( j != (i-h)) 
                m[j+h] = auxiliar;
        }

    }
}

void ordena (musicas *m1, musicas *m2, musicas *m3, musicas *m4, int tamanho) {
    shellsort(m1, tamanho);
    shellsort(m2, tamanho);
    shellsort(m3, tamanho);
    shellsort(m4, tamanho);
}