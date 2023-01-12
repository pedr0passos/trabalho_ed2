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
    char nome[256];
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
    int votos;
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
void le_arquivo(FILE *arq1, FILE *arq2, no **lista1, no **lista2, no **lista3, no **lista4, musicas *m1, musicas *m2, musicas *m3, musicas *m4);
void grava(no **l1, no **l2, no **l3, no **l4, musicas *m1, musicas *m2, musicas *m3, musicas *m4);
void encerra(no **l1, no **l2, no **l3, no **l4, musicas *m1, musicas *m2, musicas *m3, musicas *m4);
void insere_do_arquivo(no **lista, pessoa nova);
void imprime_musicas(musicas *m1, musicas *m2, musicas *m3, musicas *m4, int tamanho);
void imprime_top3(musicas *m1, musicas *m2, musicas *m3, musicas *m4, int tamanho);
int decrementa(int numero);
void shellsort(musicas *m, int t);
int calcula_h(int numero, int tamanho);
void ordena (musicas *m1, musicas *m2, musicas *m3, musicas *m4, int tamanho);
void lista_top3(no **l1, no **l2, no **l3, no **l4, musicas *m1, musicas *m2, musicas *m3, musicas *m4,  no **n1, no **n2, no **n3, no **n4);
void libera_lista (no **lista);
int masculino(pessoa p);
int feminino(pessoa p);
int menor_igual_20(pessoa p);
int maior_20(pessoa p);

/*----------------------------------------------------------------------------
                                    MAIN:
----------------------------------------------------------------------------*/

int main () {

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

    musicas *m1 = malloc(sizeof(musicas)*MaxMusicas);
    musicas *m2 = malloc(sizeof(musicas)*MaxMusicas);
    musicas *m3 = malloc(sizeof(musicas)*MaxMusicas);
    musicas *m4 = malloc(sizeof(musicas)*MaxMusicas);

    cria_lista_musicas(m1);
    cria_lista_musicas(m2);
    cria_lista_musicas(m3);
    cria_lista_musicas(m4);

    // Quatro listas separadas com o nome e o sobrenome de todos os pesquisados que tenham mencionado em primeiro lugar uma das três músicas mais populares na categoria.
    no *nome_pesquisados1, *nome_pesquisados2, *nome_pesquisados3, *nome_pesquisados4;
    cria_lista(&nome_pesquisados1);
    cria_lista(&nome_pesquisados2);
    cria_lista(&nome_pesquisados3);
    cria_lista(&nome_pesquisados4);

    FILE *arquivo_pesquisa = fopen("pesquisa.txt", "r");
    FILE *arquivo_musicas = fopen("musicas.txt", "r");
    
    if ( arquivo_pesquisa != NULL && arquivo_musicas != NULL )
        printf("Arquivo Aberto\n");

    le_arquivo(arquivo_pesquisa, arquivo_musicas, &lista1, &lista2, &lista3, &lista4, m1, m2, m3, m4);

    // printf("LISTA1\n");
    // for (int i = 0; i < MaxMusicas; i++ )
    //     printf("MUSICA: %d | QUANTIDADE: %d\n", m1[i].musica, m1[i].quantidade);
    // printf("LISTA2\n");
    // for (int i = 0; i < MaxMusicas; i++ )
    //     printf("MUSICA: %d | QUANTIDADE: %d\n", m2[i].musica, m2[i].quantidade);
    // printf("LISTA3\n");
    // for (int i = 0; i < MaxMusicas; i++ )
    //     printf("MUSICA: %d | QUANTIDADE: %d\n", m3[i].musica, m3[i].quantidade);
    // printf("LISTA4\n");
    // for (int i = 0; i < MaxMusicas; i++ )
    //     printf("MUSICA: %d | QUANTIDADE: %d\n", m4[i].musica, m4[i].quantidade);

    int opcao;
    while(laco) {
        printf("1 - Adicionar a Pesquisa\n");
        printf("2 - Imprimir Pesquisa\n");
        printf("3 - Musicas\n");
        printf("4 - Imprimir Top 3 Musicas mais Populares\n");
        printf("5 - Nomes das Pessoas Que Mencionaram o Top3 como Primeira Musica\n");
        printf("6 - Sair\n");        
        printf("OPCAO: ");
        scanf("%d", &opcao);
        switch (opcao) {
        case 1:;    //adiciona na pesquisa
            limpa_terminal();
            pessoa *p;
            p = le_pessoa(m1,m2,m3,m4);

            if ( menor_igual_20(*p) && masculino(*p) ) 
                insere(&lista1, *p);

            if ( maior_20(*p) && masculino(*p) ) 
                insere(&lista2, *p);

            if ( menor_igual_20(*p) && feminino(*p) )
                insere(&lista3, *p);

            if ( maior_20(*p) && feminino(*p) )
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
        case 5:;
            limpa_terminal();
            lista_top3(&lista1, &lista2, &lista3, &lista4, m1, m2, m3, m4, &nome_pesquisados1, &nome_pesquisados2, &nome_pesquisados3, &nome_pesquisados4);
            imprime(&nome_pesquisados1);
            imprime(&nome_pesquisados2);
            imprime(&nome_pesquisados3);
            imprime(&nome_pesquisados4);
        break;
        case 6:;    // encerra o programa
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

int masculino(pessoa p) {
    if ( p.sexo == 'M')
        return TRUE;
    return FALSE;
}

int feminino(pessoa p) {
    if (p.sexo == 'F')
        return TRUE;
    return FALSE;
}

int menor_igual_20(pessoa p) {
    if (p.idade <= 20)
        return TRUE;
    return FALSE;
}

int maior_20(pessoa p) {
    if (p.idade > 20)
        return TRUE;
    return FALSE;
}

/*----------------------------------------------------------------------------
                            FUNÇÕES DO PROGRAMA:
----------------------------------------------------------------------------*/

void cria_lista(no **lista){
    *lista = NULL;
}

pessoa *le_pessoa(musicas *m1, musicas *m2, musicas *m3, musicas *m4) {        

    pessoa *novo = malloc(sizeof(pessoa));

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
            if (!repetido) {

                if ( menor_igual_20(*novo) && masculino(*novo) )
                    adiciona_pesquisa(m1, novo->musicas[i]);          

                if ( maior_20(*novo) && masculino(*novo) )
                    adiciona_pesquisa(m2, novo->musicas[i]);

                if ( menor_igual_20(*novo) && feminino(*novo) )
                    adiciona_pesquisa(m3, novo->musicas[i]);

                if ( maior_20(*novo) && feminino(*novo) )
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
        m[i].votos = 0;
    }
}

void adiciona_pesquisa(musicas *m, int musica_escolhida) {
    int i;
    for (i = 0; i < MaxMusicas; i++) 
        if ( m[i].musica == musica_escolhida ) 
            m[i].votos++;
}

void le_arquivo( FILE *arq1, FILE *arq2, no **l1, no **l2, no **l3, no **l4, musicas *m1, musicas *m2, musicas *m3, musicas *m4 ) {
    
    pessoa *p = malloc(sizeof(pessoa));

    while ( fscanf(arq1, "%[^\t]\t%c\t%d\t%d %d %d %d %d\n", p->nome, &p->sexo, &p->idade, &p->musicas[0], &p->musicas[1], &p->musicas[2], &p->musicas[3], &p->musicas[4]) != EOF ) {

        no *l = malloc(sizeof(no));

        if ( menor_igual_20(*p) && masculino(*p) ) {
            insere_do_arquivo(l1, *p);
            // for (int i = 0; i < 5; i++ )
            //     adiciona_pesquisa(m1, p->musicas[i]);
        }

        if ( maior_20(*p) && masculino(*p) ) {
            insere_do_arquivo(l2, *p);
            // for (int i = 0; i < 5; i++ )
            //     adiciona_pesquisa(m2, p->musicas[i]);            
        }
        if ( menor_igual_20(*p) && feminino(*p) ) {
            insere_do_arquivo(l3, *p);
            // for (int i = 0; i < 5; i++ )
            //     adiciona_pesquisa(m3, p->musicas[i]);            
        }
        if ( maior_20(*p) && feminino(*p) ) {
            insere_do_arquivo(l4, *p);
            // for (int i = 0; i < 5; i++ )
            //     adiciona_pesquisa(m4, p->musicas[i]);    
        }                      

    }

    int i = 0;
    int j = 0;
    int aux1;
    int aux2;

    while ( fscanf(arq2, "%d %d\t", &aux1, &aux2) != EOF ) {
        if (j == 30)
            j = 0;
        if ( i < 30 ) {
            m1[j].musica = aux1;
            m1[j].votos = aux2;
        }
        if ( i >= 30 && i < 60 ) {
            m2[j].musica = aux1;
            m2[j].votos = aux2;            
        }
        if ( i >= 60 && i < 90 ) {
            m3[j].musica = aux1;
            m3[j].votos = aux2;         
        }
        if ( i >= 90 && i < 120 ) {
            m4[j].musica = aux1;
            m4[j].votos = aux2;
        }
        j++;
        i++;
    }

}

void grava( no **l1, no **l2, no **l3, no **l4, musicas *m1, musicas *m2, musicas *m3, musicas *m4 ) {

    FILE *arq1 = fopen("pesquisa.txt", "w");
    FILE *arq2 = fopen("musicas.txt", "w");

    // gravando a lista1
    for ( no *temporario = (*l1); temporario != NULL; temporario = temporario->proximo ) {
        fprintf(arq1,"%s\t%c\t%d\t%d %d %d %d %d\n", temporario->p.nome, temporario->p.sexo, temporario->p.idade, temporario->p.musicas[0], temporario->p.musicas[1], temporario->p.musicas[2], temporario->p.musicas[3], temporario->p.musicas[4]);
    }
    // gravando a lista2
    for ( no *temporario = (*l2); temporario != NULL; temporario = temporario->proximo ) {
        fprintf(arq1,"%s\t%c\t%d\t%d %d %d %d %d\n", temporario->p.nome, temporario->p.sexo, temporario->p.idade, temporario->p.musicas[0], temporario->p.musicas[1], temporario->p.musicas[2], temporario->p.musicas[3], temporario->p.musicas[4]);
    }
    // gravando a lista3
    for ( no *temporario = (*l3); temporario != NULL; temporario = temporario->proximo ) {
        fprintf(arq1,"%s\t%c\t%d\t%d %d %d %d %d\n", temporario->p.nome, temporario->p.sexo, temporario->p.idade, temporario->p.musicas[0], temporario->p.musicas[1], temporario->p.musicas[2], temporario->p.musicas[3], temporario->p.musicas[4]);
    }
    // gravando a lista4
    for ( no *temporario = (*l4); temporario != NULL; temporario = temporario->proximo ) {
        fprintf(arq1,"%s\t%c\t%d\t%d %d %d %d %d\n", temporario->p.nome, temporario->p.sexo, temporario->p.idade, temporario->p.musicas[0], temporario->p.musicas[1], temporario->p.musicas[2], temporario->p.musicas[3], temporario->p.musicas[4]);
    }

    // gravando a lista de musicas 1
    for ( int i = 0; i < MaxMusicas; i++ ) 
        fprintf(arq2, "%d %d\t", m1[i].musica, m1[i].votos);

    // gravando a lista de musicas 2
    for ( int i = 0; i < MaxMusicas; i++ )
        fprintf(arq2, "%d %d\t", m2[i].musica, m2[i].votos);

    // gravando a lista de musicas 3
    for ( int i = 0; i < MaxMusicas; i++ )
        fprintf(arq2, "%d %d\t", m3[i].musica, m3[i].votos);

    // gravando a lista de musicas 4
    for ( int i = 0; i < MaxMusicas; i++ ) 
        fprintf(arq2, "%d %d\t", m4[i].musica, m4[i].votos);

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
    int imprimiu;
    printf("MUSICAS MAIS POPULARES DE CADA CATEGORIA:\n\n");
    linha();
    printf("MASCULINO MENOR OU IGUAL A 20 ANOS:\n");
    for ( int i = 0; i < tamanho; i++ ) {
        imprimiu = FALSE;
        if (m1[i].votos > 0 ) {
            printf("Musica: %d | Votos: %d\n", m1[i].musica, m1[i].votos);
            imprimiu = TRUE;
        }
        if (!imprimiu)
            printf("Lista Vazia, Nenhum Voto!\n");
    }

    linha();
    printf("MASCULINO MAIOR QUE 20 ANOS:\n");
    for ( int i = 0; i < tamanho; i++ ) {
        imprimiu = FALSE;
        if (m2[i].votos > 0 ) {
            printf("Musica: %d | Votos: %d\n", m2[i].musica, m2[i].votos);
            imprimiu = TRUE;
        }
        if (!imprimiu)
            printf("Lista Vazia, Nenhum Voto!\n");
    }
    linha();
    printf("FEMININO MENOR OU IGUAL A 20 ANOS:\n");
    for ( int i = 0; i < tamanho; i++ ) {
        imprimiu = FALSE;
        if (m3[i].votos > 0 ) {            
            printf("Musica: %d | Votos: %d\n", m3[i].musica, m3[i].votos);
            imprimiu = TRUE;
        }
        if (!imprimiu)
            printf("Lista Vazia, Nenhum Voto!\n");
    }
    linha();
    printf("FEMININO MAIOR QUE 20 ANOS:\n");
    for ( int i = 0; i < tamanho; i++ ) {
        imprimiu = FALSE;
        if (m4[i].votos > 0 ) {
            printf("Musica: %d | Votos: %d\n", m4[i].musica, m4[i].votos);
            imprimiu = TRUE;
        }
        if (!imprimiu)
            printf("Lista Vazia, Nenhum Voto!\n");
    }
    linha();

}

void imprime_top3(musicas *m1, musicas *m2, musicas *m3, musicas *m4, int tamanho) {
    ordena(m1,m2,m3,m4,MaxMusicas);
    printf("TOP 3 MUSICAS MAIS POPULARES DE CADA CATEGORIA:\n\n");
    linha();
    printf("MASCULINO MENOR OU IGUAL A 20 ANOS:\n");
    for ( int i = 0; i < 3; i++ ) 
        if (m1[i].votos > 0 )
            printf("TOP %d | Musica: %d | Votos: %d\n",(i+1), m1[i].musica, m1[i].votos);
    linha();
    printf("MASCULINO MAIOR QUE 20 ANOS:\n");
    for ( int i = 0; i < 3; i++ ) 
        if (m2[i].votos > 0 )
            printf("TOP %d | Musica: %d | Votos: %d\n",(i+1), m2[i].musica, m2[i].votos);
    linha();
    printf("FEMININO MENOR OU IGUAL A 20 ANOS:\n");
    for ( int i = 0; i < 3; i++ ) 
        if (m3[i].votos > 0 )
            printf("TOP %d | Musica: %d | Votos: %d\n",(i+1), m3[i].musica, m3[i].votos);
    linha();
    printf("FEMININO MAIOR QUE 20 ANOS:\n");
    for ( int i = 0; i < 3; i++ ) 
        if (m4[i].votos > 0 )
            printf("TOP %d | Musica: %d | Votos: %d\n",(i+1), m4[i].musica, m4[i].votos);
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
            while  ( j >= 0 && auxiliar.votos > m[j].votos ) {
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

void libera_lista (no **lista) {
    no *p, *temp;
    for ( p = *lista; p != NULL; p = p->proximo ) {
        temp = p->proximo;
        free(p);
        printf("Lista Vazia");
    } 
    *lista = NULL;
}

void lista_top3(no **l1, no **l2, no **l3, no **l4, musicas *m1, musicas *m2, musicas *m3, musicas *m4, no **n1, no **n2, no **n3, no **n4) {
    
    pessoa nova;

    ordena(m1,m2,m3,m4, MaxMusicas);
    libera_lista(n1);
    libera_lista(n2);
    libera_lista(n3);
    libera_lista(n4);
    
    for ( no *aux = (*l1); aux != NULL; aux = aux->proximo ) {
            strcpy(nova.nome, aux->p.nome);
            insere(n1, nova);
    }

    for ( no *aux = (*l2); aux != NULL; aux = aux->proximo ) {
            strcpy(nova.nome, aux->p.nome);
            insere(n2, nova);
    }

    for ( no *aux = (*l3); aux != NULL; aux = aux->proximo ) {
            strcpy(nova.nome, aux->p.nome);
            insere(n3, nova);
    }

    for ( no *aux = (*l4); aux != NULL; aux = aux->proximo ) {
            strcpy(nova.nome, aux->p.nome);
            insere(n4, nova);
    }

}