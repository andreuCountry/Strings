#include <stdio.h>

FILE *f;

int main() {

    f = fopen("texto0.txt", "w");

    fputs("Esto es una prueba de texto", f);
    fclose(f);
}