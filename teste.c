#include <stdio.h>
#include <string.h>

int main () {

    char *masculino = "M";
    char *feminino = "M";

    printf("%s \t %s\n", masculino, feminino);

    printf("%d ", strcmp(masculino, "F"));

    return 0;
}