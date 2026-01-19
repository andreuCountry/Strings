#include <stdio.h>

FILE *f;
char caracter;

int main() {
    if ((f=fopen("texto0.txt", "r")) == NULL) {
        printf("Error. El fichero no existe.");
    } else {
        do {
            caracter = fgetc(f);
            printf("%c", caracter);
        } while (!feof(f));
        fclose(f);
    }

    return 0;
}