#include <stdio.h>

FILE *f;
char character;

int main() {

    if ((f=fopen("texto0.txt", "r")) == NULL) {
        printf("Error. El fichero no existe");
    } else {
        printf("Introduzca una cadena para añadir al texto: \n");
        char Cadena[200];

        fgets(Cadena, 255, stdin);

        f = fopen("texto0.txt", "a");
        fputs(Cadena, f);
        fclose(f);
    }

    return 0;
}