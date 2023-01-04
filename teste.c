#include <stdio.h>
#include <string.h>
#define MaxMusicas 30

typedef struct m {
    int musica;
    int quantidade;
}musicas;

void cria_lista_musicas(musicas *m);

int main () {

    musicas m[MaxMusicas];    
    cria_lista_musicas(m);

    for (int i = 0; i < MaxMusicas; i++)
        printf("%d %d\n", m[i].musica, m[i].quantidade);


    return 0;
}

void cria_lista_musicas(musicas *m) {
    for(int i = 0; i < MaxMusicas; i++) {
        m[i].musica = i+1;
        m[i].quantidade = 0;
    }
}