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
void libera_lista(no **lista);

void cria_lista(no **lista);
void cria_lista_musicas(musicas *m);

void imprime(no **lista);
void imprime_musicas(musicas *m, int tamanho);
void imprime_categoria(no **lista);

pessoa *le_pessoa(musicas *m1, musicas *m2, musicas *m3, musicas *m4, musicas *m5);

void insere(no **lista, pessoa nova);
void insere_do_arquivo(no **lista, pessoa nova);

void le_pesquisa (no **lista);
void le_musicas( FILE *arquivo_musicas, musicas *m);
void grava_pesquisa(no **lista);
void grava_pesquisa_categoria ( FILE *arquivo_pesquisa, no **lista );
void grava_musicas(musicas *m, int tamanho);
void grava_musicas_categoria(FILE *arquivo_musicas, musicas *m, int tamanho);

int decrementa(int numero);
void shellsort(musicas *m, int t);
int calcula_h(int numero, int tamanho);
void ordena(musicas *m1, musicas *m2, musicas *m3, musicas *m4, musicas *m5, int tamanho);

int vazia(no **lista);
void adiciona_voto (musicas *m, int musica_escolhida);
int masculino(pessoa p);
int feminino(pessoa p);
int menor_igual_20(pessoa p);
int maior_20(pessoa p);

void encerra(no **l1, no **l2, no **l3, no **l4, no **lista_completa, musicas *m1, musicas *m2, musicas *m3, musicas *m4, musicas *musicas_completa);
void atualiza_categorias(no **lista_principal, no **l1, no **l2, no **l3, no **l4, musicas *m1, musicas *m2, musicas *m3, musicas *m4);

/*----------------------------------------------------------------------------
                                    MAIN:
----------------------------------------------------------------------------*/

int main () {

    int laco = TRUE;

    no *total_pesquisados;

    no *masculino_menor_20;
    no *masculino_maior_20;
    no *feminino_menor_20;
    no *feminino_maior_20;

    musicas musicas_total[MaxMusicas];   

    musicas musicas_masculino_menor_20[MaxMusicas];
    musicas musicas_masculino_maior_20[MaxMusicas];
    musicas musicas_feminino_menor_20[MaxMusicas];
    musicas musicas_feminino_maior_20[MaxMusicas];

    cria_lista(&total_pesquisados);
    cria_lista(&masculino_menor_20);
    cria_lista(&masculino_maior_20);
    cria_lista(&feminino_maior_20);
    cria_lista(&feminino_menor_20);

    cria_lista_musicas(musicas_total);
    cria_lista_musicas(musicas_masculino_menor_20);
    cria_lista_musicas(musicas_masculino_maior_20);
    cria_lista_musicas(musicas_feminino_menor_20);
    cria_lista_musicas(musicas_feminino_maior_20);
    
    FILE *m_menor = fopen("arquivos/musicas/musicas_masculino_menor.txt", "r");
    FILE *m_maior = fopen("arquivos/musicas/musicas_masculino_maior.txt", "r");
    FILE *f_menor = fopen("arquivos/musicas/musicas_feminino_menor.txt", "r");
    FILE *f_maior = fopen("arquivos/musicas/musicas_feminino_maior.txt", "r");
    FILE *total_musicas = fopen("arquivos/musicas/musicas.txt", "r");

    le_pesquisa(&total_pesquisados);
    le_musicas(m_menor, musicas_masculino_menor_20);
    le_musicas(m_maior, musicas_masculino_maior_20);
    le_musicas(f_menor, musicas_feminino_menor_20);
    le_musicas(f_maior, musicas_feminino_maior_20);
    le_musicas(total_musicas, musicas_total);

    fclose(m_maior);
    fclose(m_menor);
    fclose(f_menor);
    fclose(f_maior);
    fclose(total_musicas);

    int opcao;
    while(laco) {
        linha();
        printf(" 1 - Adicionar a Pesquisa\n");
        printf(" 2 - Mostrar Resultado da Pesquisa Completa\n");
        printf(" 3 - Mostrar Musicas Mais Populares\n");
        printf(" 4 - Mostrar Pesquisados que Selecionaram como Primeira Opcao as TOP 3 Musicas da Categoria\n");
        printf(" 5 - Mostrar Musicas Mais Populares de Cada Categoria\n");
        printf(" 6 - Sair\n");   
        linha();     
        printf(" OPCAO: ");
        scanf("%d", &opcao);
        switch (opcao) {
        case 1:;
            limpa_terminal();
            pessoa *p = le_pessoa(musicas_masculino_menor_20,musicas_masculino_maior_20,musicas_feminino_menor_20,musicas_feminino_maior_20, musicas_total);
            insere(&total_pesquisados, *p);
            limpa_terminal();
        break;
        case 2:;
            limpa_terminal();
            linha();
            printf(" PESQUISA COMPLETA:\n");
            linha();
            imprime(&total_pesquisados);
        break;
        case 3:;
            limpa_terminal();
            shellsort(musicas_total, MaxMusicas);
            linha();
            printf(" MUSICAS COM O TOTAL DE VOTOS OBTIDOS NA PESQUISA:\n");
            linha();
            imprime_musicas(musicas_total, MaxMusicas);
        break;
        case 4:;
            // // separa as pessoas em suas devidas categorias
            atualiza_categorias(&total_pesquisados, &masculino_menor_20, &masculino_maior_20, &feminino_menor_20, &feminino_maior_20, musicas_masculino_menor_20, musicas_masculino_maior_20, musicas_feminino_menor_20, musicas_feminino_maior_20);
            limpa_terminal();
            linha();
            printf(" CATEGORIAS DOS PESQUISADOS\n");
            linha();
            printf(" MASCULINO COM IDADE MENOR OU IGUAL A 20 ANOS:\n");
            imprime_categoria(&masculino_menor_20);
            linha();
            printf(" MASCULINO COM IDADE MAIOR QUE 20 ANOS:\n");
            imprime_categoria(&masculino_maior_20);
            linha();
            printf(" FEMININO COM IDADE MENOR OU IGUAL A 20 ANOS:\n");
            imprime_categoria(&feminino_menor_20);
            linha();
            printf(" FEMININO COM IDADE MAIOR QUE 20 ANOS:\n");
            imprime_categoria(&feminino_maior_20);
        break;
        case 5:;
            limpa_terminal();
            linha();
            printf(" MUSICAS MAIS POPULARES DE CADA CATEGORIA:\n");
            linha();
            printf(" MASCULINO COM IDADE MENOR OU IGUAL A 20:\n\n");
            imprime_musicas(musicas_masculino_menor_20, MaxMusicas);
            linha();
            printf(" MASCULINO COM IDADE MAIOR QUE 20:\n\n");
            imprime_musicas(musicas_masculino_maior_20, MaxMusicas);
            linha();
            printf(" FEMININO COM IDADE MENOR OU IGUAL A 20:\n\n");
            imprime_musicas(musicas_feminino_menor_20, MaxMusicas);
            linha();
            printf(" FEMININO COM IDADE MAIOR QUE 20:\n\n");
            imprime_musicas(musicas_feminino_maior_20, MaxMusicas);
        break;
        case 6:;
            limpa_terminal();
            // separando as pessoas em suas categorias para poder salvar
            atualiza_categorias(&total_pesquisados, &masculino_menor_20, &masculino_maior_20, &feminino_menor_20, &feminino_maior_20, musicas_masculino_menor_20, musicas_masculino_maior_20, musicas_feminino_menor_20, musicas_feminino_maior_20);
            encerra(&masculino_menor_20, &masculino_maior_20, &feminino_menor_20, &feminino_maior_20, &total_pesquisados, musicas_masculino_menor_20, musicas_masculino_maior_20, musicas_feminino_menor_20, musicas_feminino_maior_20, musicas_total);
            laco = FALSE;
        break;
        default:;
            limpa_terminal();
            printf(" Opcao Invalida!\n");
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

void ordena(musicas *m1, musicas *m2, musicas *m3, musicas *m4, musicas *m5, int tamanho) {
    shellsort(m1, tamanho);
    shellsort(m2, tamanho);
    shellsort(m3, tamanho);
    shellsort(m4, tamanho);
    shellsort(m5, tamanho);
}

// Incrementa os Votos 
void adiciona_voto(musicas *m, int musica_escolhida) {
    int i;
    for (i = 0; i < MaxMusicas; i++) 
        if ( m[i].musica == musica_escolhida ) 
            m[i].votos++;
}

void atualiza_categorias(no **lista_principal, no **l1, no **l2, no **l3, no **l4, musicas *m1, musicas *m2, musicas *m3, musicas *m4) {
    
    libera_lista(l1);
    libera_lista(l2);
    libera_lista(l3);
    libera_lista(l4);

    for ( no *temp = (*lista_principal); temp != NULL; temp = temp->proximo ) {
        if (masculino(temp->p) && menor_igual_20(temp->p) && esta_no_top3(temp->p, m1))
            insere(l1, temp->p);
        
        if (masculino(temp->p) && maior_20(temp->p) && esta_no_top3(temp->p, m2))
            insere(l2, temp->p);

        if (feminino(temp->p) && menor_igual_20(temp->p) && esta_no_top3(temp->p, m3))
            insere(l3, temp->p);

        if (feminino(temp->p) && maior_20(temp->p) && esta_no_top3(temp->p, m4))
            insere(l4, temp->p);
    }
    
}

void libera_lista(no **lista) {
    no *p, *temp;
    for ( p = *lista; p != NULL; p = temp ) {
        temp = p->proximo;
        free(p);
    } 
    *lista = NULL;
    free(temp);
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
            printf(" Nome: %s | Idade: %d | Sexo: %c | Musicas: %d %d %d %d %d\n", p->p.nome, p->p.idade, p->p.sexo, p->p.musicas[0], p->p.musicas[1], p->p.musicas[2], p->p.musicas[3], p->p.musicas[4]);
    else 
        printf(" Lista Vazia!\n");
}

void imprime_categoria(no **lista) {
    if (!vazia(lista))
        for (no *p = (*lista); p!= NULL; p = p->proximo )
            printf(" Nome e Sobrenome: %s\n", p->p.nome);
    else
        printf(" Lista Vazia!\n");    
}

void imprime_musicas(musicas *m, int tamanho) {
    int imprimiu;
    int i;
    imprimiu = FALSE;
    for ( i = 0; i < tamanho; i++ )
        if (m[i].votos > 0 ) {
            printf(" Musica: %d | Votos: %d\n", m[i].musica, m[i].votos);
            imprimiu = TRUE;
        }

    if (!imprimiu && i == tamanho)
        printf(" Lista Vazia, Nenhum Voto!\n");

}

// Função de Leitura
pessoa *le_pessoa(musicas *m1, musicas *m2, musicas *m3, musicas *m4, musicas *m5) {        

    pessoa *novo = malloc(sizeof(pessoa));

    printf(" Nome e Sobrenome: ");
    limpa_buffer();
    scanf("%[^\n]", novo->nome);
    
    printf(" Idade: ");
    scanf("%d", &novo->idade);
    
    printf(" Sexo (M ou F): ");
    limpa_buffer();
    scanf("%c", &novo->sexo);

    if (novo->sexo == 'm')
        novo->sexo = 'M';

    if (novo->sexo == 'f')
        novo->sexo = 'F';

    printf(" Musicas (1-30):\n");
    int i = 0;
    while (i < 5) {
        printf(" %d: ",i+1);
        scanf("%d", &novo->musicas[i]);
        if ( novo->musicas[i] < 1 || novo->musicas[i] > 30 )
            printf(" Valor Invalido! Tente Novamente\n");
        else {
            int repetido = FALSE;
            if (i > 0) {
                for (int j = 0; j < i; j++)
                    if ( novo->musicas[i] == novo->musicas[j] ) {
                        printf(" Valor Repetido! Tente Novamente\n");
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

                adiciona_voto(m5, novo->musicas[i]);
                i++;
            }
        }
    }
    return novo;
}

// Funções do Arquivo ( Leitura e Gravacao )
void le_pesquisa (no **lista) {
    pessoa *nova = malloc(sizeof(pessoa));
    FILE *arquivo_pesquisa = fopen("arquivos/pesquisas/pesquisa.txt", "r");
    while ( fscanf(arquivo_pesquisa, "%[^\t]\t%c\t%d\t%d %d %d %d %d\n", nova->nome, &nova->sexo, &nova->idade, &nova->musicas[0], &nova->musicas[1], &nova->musicas[2], &nova->musicas[3], &nova->musicas[4]) != EOF )
        insere_do_arquivo(lista, *nova);
    fclose(arquivo_pesquisa);
}

void le_musicas( FILE *arquivo_musicas, musicas *m) {
    fscanf(arquivo_musicas, "Musica\tVotos\n");
    int i = 0;
    while(fscanf(arquivo_musicas, "%d\t\t%d\n", &m[i].musica, &m[i].votos) != EOF )
        i++;
}

void grava_pesquisa(no **lista) {

    FILE *arquivo_pesquisa = fopen("arquivos/pesquisas/pesquisa.txt", "w");
    for ( no *temporario = (*lista); temporario != NULL; temporario = temporario->proximo )
        fprintf(arquivo_pesquisa,"%s\t%c\t%d\t%d %d %d %d %d\n", temporario->p.nome, temporario->p.sexo, temporario->p.idade, temporario->p.musicas[0], temporario->p.musicas[1], temporario->p.musicas[2], temporario->p.musicas[3], temporario->p.musicas[4]);
    
    fclose(arquivo_pesquisa);
}

void grava_pesquisa_categoria ( FILE *arquivo_pesquisa, no **lista ) {
    fprintf(arquivo_pesquisa, "NOME E SOBRENOME DAS PESSOAS QUE MENCIONARAM EM PRIMEIRO LUGAR UMA DAS TRES MUSICAS MAIS POPULARES DA CATEGORIA\n");
    fprintf(arquivo_pesquisa, "----------------------------------------------------------------------------------------------------------------\n");
    for (no *temporario = (*lista); temporario != NULL; temporario = temporario->proximo )
        fprintf(arquivo_pesquisa, "Nome e Sobrenome: %s\n", temporario->p.nome);
}

void grava_musicas( musicas *m, int tamanho) {
    shellsort(m, tamanho);
    FILE *arquivo_musicas = fopen("arquivos/musicas/musicas.txt", "w");
    fprintf(arquivo_musicas, "Musica\tVotos\n");
    for ( int i = 0; i < tamanho; i++ ) 
        fprintf(arquivo_musicas, "%d\t\t%d\n",m[i].musica, m[i].votos);
}

void grava_musicas_categoria(FILE *arquivo_musicas, musicas *m, int tamanho) {
    shellsort(m, tamanho);
    fprintf(arquivo_musicas, "Musica\tVotos\n");
    for ( int i = 0; i < tamanho; i++ ) 
        if (m[i].votos > 0 )
            fprintf(arquivo_musicas, "%d\t\t%d\n",m[i].musica, m[i].votos);
}

// Função de Encerramento
void encerra(no **l1, no **l2, no **l3, no **l4, no **lista_completa, musicas *m1, musicas *m2, musicas *m3,musicas *m4, musicas *musicas_completa) {

    FILE *arq_m_menor = fopen("arquivos/musicas/musicas_masculino_menor.txt", "w");
    FILE *arq_m_maior = fopen("arquivos/musicas/musicas_masculino_maior.txt", "w");
    FILE *arq_f_menor = fopen("arquivos/musicas/musicas_feminino_menor.txt", "w");
    FILE *arq_f_maior = fopen("arquivos/musicas/musicas_feminino_maior.txt", "w");

    grava_musicas_categoria(arq_m_menor, m1, MaxMusicas);
    grava_musicas_categoria(arq_m_maior, m2, MaxMusicas);
    grava_musicas_categoria(arq_f_menor, m3, MaxMusicas);
    grava_musicas_categoria(arq_f_maior, m4, MaxMusicas);
    grava_musicas(musicas_completa, MaxMusicas);

    arq_m_menor = fopen("arquivos/pesquisas/pesquisa_masculino_menor.txt", "w");
    arq_m_maior = fopen("arquivos/pesquisas/pesquisa_masculino_maior.txt", "w");
    arq_f_menor = fopen("arquivos/pesquisas/pesquisa_feminino_menor.txt", "w");
    arq_f_maior = fopen("arquivos/pesquisas/pesquisa_feminino_maior.txt", "w");
    
    grava_pesquisa_categoria(arq_m_menor, l1);
    grava_pesquisa_categoria(arq_m_maior, l2);
    grava_pesquisa_categoria(arq_f_menor, l3);
    grava_pesquisa_categoria(arq_f_maior, l4);
    grava_pesquisa(lista_completa);

    fclose(arq_f_maior);
    fclose(arq_f_menor);
    fclose(arq_m_maior);
    fclose(arq_m_menor);

    linha();
    printf("Programa Encerrado!\n");
    linha();

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
