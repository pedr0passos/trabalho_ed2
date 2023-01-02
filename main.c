#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

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

void limpa_buffer();
void cria_lista(no **lista);
int vazia(no **lista);
pessoa *le_pessoa()

int main () {

    // teste de pesquisa

    pessoa p;
    no *l;
    cria_lista(&l);

    le

    return 0;
}

void limpa_buffer() {
    setbuf(stdin, NULL);
}

void cria_lista(no **lista){
    *lista = NULL;
}

int vazia(no **lista) {
    return (*lista == NULL);

}

no *le_no() {        

    no *novo = (no*)malloc(sizeof(no));

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


}

void imprime (no **lista) {
    if (!vazia(lista)) {
        for (no *p = (*lista); p!= NULL; p = p->proximo )
            printf("Nome: %[^\n] | Idade: %d | Sexo: %c", p->p.nome, p->p.idade, p->p.sexo);
    } else {
        printf("Lista Vazia");
    }
}
