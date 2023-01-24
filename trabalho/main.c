#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// caminho : C:\Users\rocha\GitHub\trabalho_ed2

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
void limpa_terminal();

void cria_lista(no **lista);
void cria_lista_musicas(musicas *m);
void cria_lista_top3(no **lista, musicas *musica,  no **nomes);

void imprime(no **lista);
void imprime_musicas(musicas *m, int tamanho);
void imprime_pesquisados_top3(no **lista);

pessoa *le_pessoa(musicas *m1, musicas *m2, musicas *m3, musicas *m4);

void insere(no **lista, pessoa nova);
void insere_do_arquivo(no **lista, pessoa nova);

void le_pesquisa (FILE *arquivo_pesquisa, no **lista);
void grava(no **l1, no **l2, no **l3, no **l4);
void grava_musicas(FILE *arquivo_musicas, musicas *m, int tamanho);


int decrementa(int numero);
void shellsort(musicas *m, int t);
int calcula_h(int numero, int tamanho);
void ordena(musicas *m1, musicas *m2, musicas *m3, musicas *m4, int tamanho);

int vazia(no **lista);
void libera_lista(no **lista);
void adiciona_voto (musicas *m, int musica_escolhida);
int masculino(pessoa p);
int feminino(pessoa p);
int menor_igual_20(pessoa p);
int maior_20(pessoa p);

void encerra(no **l1, no **l2, no **l3, no **l4, musicas *m1, musicas *m2, musicas *m3, musicas *m4);

/*----------------------------------------------------------------------------
                                    MAIN:
----------------------------------------------------------------------------*/

int main () {

    int laco1 = TRUE;
    int laco2 = TRUE;

    no *total_pesquisados;
    no *masculino_menor_20;
    no *masculino_maior_20;
    no *feminino_menor_20;
    no *feminino_maior_20;

    musicas musicas_total[MaxMusicas];
    musicas musicas_populares[MaxMusicas];    
    musicas musicas_masculino_menor_20[MaxMusicas];
    musicas musicas_masculino_maior_20[MaxMusicas];
    musicas musicas_feminino_menor_20[MaxMusicas];
    musicas musicas_feminino_maior_20[MaxMusicas];

    // no *nome_pesquisados1; 
    // no *nome_pesquisados2; 
    // no *nome_pesquisados3; 
    // no *nome_pesquisados4;

    cria_lista(&total_pesquisados);
    cria_lista(&masculino_menor_20);
    cria_lista(&masculino_maior_20);
    cria_lista(&feminino_maior_20);
    cria_lista(&feminino_menor_20);

    cria_lista_musicas(musicas_total);
    cria_lista_musicas(musicas_populares);
    cria_lista_musicas(musicas_masculino_menor_20);
    cria_lista_musicas(musicas_masculino_maior_20);
    cria_lista_musicas(musicas_feminino_menor_20);
    cria_lista_musicas(musicas_feminino_maior_20);

    // cria_lista(&nome_pesquisados1);
    // cria_lista(&nome_pesquisados2);
    // cria_lista(&nome_pesquisados3);
    // cria_lista(&nome_pesquisados4);
    
    FILE *arq1 = fopen("arquivos/pesquisa_masculino_menor.txt", "r");
    FILE *arq2 = fopen("arquivos/pesquisa_masculino_maior.txt", "r");
    FILE *arq3 = fopen("arquivos/pesquisa_feminino_menor.txt", "r");
    FILE *arq4 = fopen("arquivos/pesquisa_feminino_maior.txt", "r");

    le_pesquisa(arq1, &masculino_menor_20);
    le_pesquisa(arq2, &masculino_maior_20);
    le_pesquisa(arq3, &feminino_menor_20);
    le_pesquisa(arq4, &feminino_maior_20);

    int opcao;
    while(laco1) {
        linha();
        printf("1 - Adicionar a Pesquisa\n");
        printf("2 - Gerar Musicas Mais Populares\n");
        printf("3 - Musicas\n");
        printf("4 - Nomes das Pessoas Que Mencionaram o Top3 como Primeira Musica\n");
        printf("5 - Sair\n");   
        linha();     
        printf("OPCAO: ");
        scanf("%d", &opcao);
        switch (opcao) {
        case 1:;
            limpa_terminal();
            pessoa *p = le_pessoa(musicas_masculino_menor_20,musicas_masculino_maior_20,musicas_feminino_menor_20,musicas_feminino_maior_20);
            insere(&total_pesquisados, *p);
            limpa_terminal();
        break;
        case 2:;
            limpa_terminal();
            laco2 = TRUE;
            while (laco2) {
                linha();
                printf("Escolha qual categoria:\n");
                printf("1 - MASCULINO COM IDADE MENOR OU IGUAL A 20\n");
                printf("2 - MASCULINO COM IDADE MAIOR 20\n");
                printf("3 - FEMININO COM IDADE MENOR OU IGUAL A 20\n");
                printf("4 - FEMININO COM IDADE MAIOR 20\n");
                printf("5 - TODAS\n");
                printf("6 - SAIR\n");
                linha();
                printf("Escolha: ");
                scanf("%d", &opcao);
                switch (opcao) {
                    case 1:;   
                        limpa_terminal();
                        linha();
                        imprime(&masculino_menor_20);
                    break;
                    case 2:;
                        limpa_terminal();
                        linha();
                        imprime(&masculino_maior_20);
                    break;                    
                    case 3:;
                        limpa_terminal();
                        linha();
                        imprime(&feminino_menor_20);
                    break;
                    case 4:;
                        limpa_terminal();
                        linha();
                        imprime(&feminino_maior_20);
                    break;
                    case 5:;
                        limpa_terminal();
                        linha();
                        printf("PESQUISA COMPLETA:\n");
                        linha();
                        imprime(&total_pesquisados);
                    break;
                    case 6:;
                        laco2 = FALSE;
                        limpa_terminal();
                    break;
                    default:;
                        printf("Opcao Invalida!\n");                
                }
            }            
        break;
        case 3:;
            limpa_terminal();
            linha();
            printf("MUSICAS MAIS POPULARES DE CADA CATEGORIA:\n");
            linha();
            printf("MASCULINO COM IDADE MENOR OU IGUAL A 20:\n\n");
            imprime_musicas(musicas_masculino_menor_20, MaxMusicas);
            linha();
            printf("MASCULINO COM IDADE MAIOR QUE 20:\n\n");
            imprime_musicas(musicas_masculino_maior_20, MaxMusicas);
            linha();
            printf("FEMININO COM IDADE MENOR OU IGUAL A 20:\n\n");
            imprime_musicas(musicas_feminino_menor_20, MaxMusicas);
            linha();
            printf("FEMININO COM IDADE MAIOR QUE 20:\n\n");
            imprime_musicas(musicas_feminino_maior_20, MaxMusicas);
        break;
        case 4:;
        break;
        case 5:;
            limpa_terminal();
            encerra(&masculino_menor_20, &masculino_maior_20, &feminino_menor_20, &feminino_maior_20, musicas_masculino_menor_20, musicas_masculino_maior_20, musicas_feminino_menor_20, musicas_feminino_maior_20);
            laco1 = FALSE;
        break;
        default:;
            limpa_terminal();
            printf("Opcao Invalida!\n");
        }
    } 
    return 0;
} 

/*----------------------------------------------------------------------------
                            FUNÇÕES AUXILIARES:
----------------------------------------------------------------------------*/

// Funções de Limpeza
void limpa_buffer() {
    setbuf(stdin, NULL);
}

void limpa_terminal(){
    system("cls");
}

// Função de Criação de Linha Separadora
void linha() {
    printf("-----------------------------------------------------------------------\n");
}

// Funções de Comparações
int vazia(no **lista) {
    return (*lista == NULL);
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

int esta_no_top3( pessoa p, musicas *m ) {
    if (p.musicas[0] == m[0].musica || p.musicas[0] == m[1].musica || p.musicas[0] == m[2].musica )
        return TRUE;
    return FALSE;
}

// Funções que Ajudam o Algoritmo de Ordenação
int decrementa(int numero) {
    numero = (numero-1)/3;
    return numero;
}

int calcula_h(int numero, int tamanho ) {
    while (numero < tamanho)
        numero = numero*3+1;
    return numero;
}

void ordena(musicas *m1, musicas *m2, musicas *m3, musicas *m4, int tamanho) {
    shellsort(m1, tamanho);
    shellsort(m2, tamanho);
    shellsort(m3, tamanho);
    shellsort(m4, tamanho);
}

// Incrementa os Votos 
void adiciona_voto(musicas *m, int musica_escolhida) {
    int i;
    for (i = 0; i < MaxMusicas; i++) 
        if ( m[i].musica == musica_escolhida ) 
            m[i].votos++;
}

// Esvazia Lista Encadeada
void libera_lista(no **lista) {
    no *p, *temp;
    for ( p = *lista; p != NULL; p = p->proximo ) {
        temp = p->proximo;
        free(p);
    } 
    *lista = NULL;
}

/*----------------------------------------------------------------------------
                            FUNÇÕES DO PROGRAMA:
----------------------------------------------------------------------------*/

// Funções de Criação das Listas
void cria_lista(no **lista){
    *lista = NULL;
}

void cria_lista_musicas(musicas *m) {
    for (int i = 0; i < MaxMusicas; i++) {
        m[i].musica = i+1; 
        m[i].votos = 0;
    }
}

// Funções de Inserção em Listas
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

// Funções de Imprimir
void imprime (no **lista) {

    if (!vazia(lista))
        for (no *p = (*lista); p!= NULL; p = p->proximo )
            printf("Nome: %s | Idade: %d | Sexo: %c | Musicas: %d %d %d %d %d\n", p->p.nome, p->p.idade, p->p.sexo, p->p.musicas[0], p->p.musicas[1], p->p.musicas[2], p->p.musicas[3], p->p.musicas[4]);
    else 
        printf("Lista Vazia!\n");
}

void imprime_pesquisados_top3(no **lista) {
    if (!vazia(lista))
        for (no *p = (*lista); p!= NULL; p = p->proximo )
            printf("Nome Completo: %s\n", p->p.nome);
    else
        printf("Lista Vazia!\n");    
}

void imprime_musicas(musicas *m, int tamanho) {
    int imprimiu;
    int i;
    imprimiu = FALSE;
    for ( i = 0; i < tamanho; i++ )
        if (m[i].votos > 0 ) {
            printf("Musica: %d | Votos: %d\n", m[i].musica, m[i].votos);
            imprimiu = TRUE;
        }

    if (!imprimiu && i == tamanho)
        printf("Lista Vazia, Nenhum Voto!\n");

}

// Função de Leitura
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
        if ( novo->musicas[i] < 1 || novo->musicas[i] > 30 )
            printf("Valor Invalido! Tente Novamente\n");
        else {
            int repetido = FALSE;
            if (i > 0) {
                for (int j = 0; j < i; j++)
                    if ( novo->musicas[i] == novo->musicas[j] ) {
                        printf("Valor Repetido! Tente Novamente\n");
                        repetido = TRUE;
                    }            
            } 
            if (!repetido) {

                if ( menor_igual_20(*novo) && masculino(*novo) )
                    adiciona_voto(m1, novo->musicas[i]);          

                if ( maior_20(*novo) && masculino(*novo) )
                    adiciona_voto(m2, novo->musicas[i]);

                if ( menor_igual_20(*novo) && feminino(*novo) )
                    adiciona_voto(m3, novo->musicas[i]);

                if ( maior_20(*novo) && feminino(*novo) )
                    adiciona_voto(m4, novo->musicas[i]);

                i++;
            }
        }
    }
    return novo;
}

// Funções do Arquivo ( Leitura e Gravacao )
void le_pesquisa (FILE *arquivo_pesquisa, no **lista) {
    pessoa *nova = malloc(sizeof(pessoa));
    while ( fscanf(arquivo_pesquisa, "%s\t%c\t%d\t%d %d %d %d %d\n", nova->nome, &nova->sexo, &nova->idade, &nova->musicas[0], &nova->musicas[1], &nova->musicas[2], &nova->musicas[3], &nova->musicas[4]) != EOF )
        insere(lista, *nova);
}

void le_musicas() {

}

void grava( no **l1, no **l2, no **l3, no **l4) {

    FILE *arquivo_pesquisa = fopen("arquivos/pesquisa.txt", "w");

    // gravando a lista1
    for ( no *temporario = (*l1); temporario != NULL; temporario = temporario->proximo )
        fprintf(arquivo_pesquisa,"%s\t%c\t%d\t%d %d %d %d %d\n", temporario->p.nome, temporario->p.sexo, temporario->p.idade, temporario->p.musicas[0], temporario->p.musicas[1], temporario->p.musicas[2], temporario->p.musicas[3], temporario->p.musicas[4]);

    // gravando a lista2
    for ( no *temporario = (*l2); temporario != NULL; temporario = temporario->proximo )
        fprintf(arquivo_pesquisa,"%s\t%c\t%d\t%d %d %d %d %d\n", temporario->p.nome, temporario->p.sexo, temporario->p.idade, temporario->p.musicas[0], temporario->p.musicas[1], temporario->p.musicas[2], temporario->p.musicas[3], temporario->p.musicas[4]);
    
    // gravando a lista3
    for ( no *temporario = (*l3); temporario != NULL; temporario = temporario->proximo )
        fprintf(arquivo_pesquisa,"%s\t%c\t%d\t%d %d %d %d %d\n", temporario->p.nome, temporario->p.sexo, temporario->p.idade, temporario->p.musicas[0], temporario->p.musicas[1], temporario->p.musicas[2], temporario->p.musicas[3], temporario->p.musicas[4]);
    
    // gravando a lista4
    for ( no *temporario = (*l4); temporario != NULL; temporario = temporario->proximo ) 
        fprintf(arquivo_pesquisa,"%s\t%c\t%d\t%d %d %d %d %d\n", temporario->p.nome, temporario->p.sexo, temporario->p.idade, temporario->p.musicas[0], temporario->p.musicas[1], temporario->p.musicas[2], temporario->p.musicas[3], temporario->p.musicas[4]);
    
    fclose(arquivo_pesquisa);
}

void grava_musicas(FILE *arquivo_musicas, musicas *m, int tamanho) {
    for ( int i = 0; i < tamanho; i++ ) 
        fprintf(arquivo_musicas, "%d\t%d\n",m[i].musica, m[i].votos);
}

// Função de Encerramento
void encerra(no **l1, no **l2, no **l3, no **l4, musicas *m1, musicas *m2, musicas *m3, musicas *m4 ) {
    linha();
    printf("Programa Encerrado!\n");
    linha();
    ordena(m1,m2,m3,m4, MaxMusicas);

    FILE *arq_m_menor = fopen("arquivos/musicas_masculino_menor.txt", "w");
    FILE *arq_m_maior = fopen("arquivos/musicas_masculino_maior.txt", "w");
    FILE *arq_f_menor = fopen("arquivos/musicas_feminino_menor.txt", "w");
    FILE *arq_f_maior = fopen("arquivos/musicas_feminino_maior.txt", "w");
    // FILE *arq_m_total = fopen("arquivos/musicas.txt", "w");

    grava_musicas(arq_m_menor, m1, MaxMusicas);
    grava_musicas(arq_m_maior, m2, MaxMusicas);
    grava_musicas(arq_f_menor, m3, MaxMusicas);
    grava_musicas(arq_f_maior, m4, MaxMusicas);
    

    grava(l1, l2, l3, l4);
}

// Algoritmo de Ordenação Escolhido
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
