#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define True 1
#define False 0

typedef struct b {
    int true = True;
    int false = False;
} bool;

int main(){

printf("%d", True || False);
    return 0;
}
