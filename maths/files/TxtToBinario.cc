#include <stdio.h>

FILE *f, *distancia;
int valor;
char Cadena[255];

int main() {

    f = fopen("TablaKM.txt", "r");
    distancia = fopen("distancies.txt", "w");

    int StartIndex = 0, LastIndex = 0;

    do {
        char Caracter = fgetc(f);
        char LastCharacter;

        fputc(Caracter, distancia);
        Cadena[StartIndex] = Caracter;
        StartIndex++;

        if (Caracter == ';' && LastCharacter == ';') {
            fputc('\n', distancia);
        }

        if (Caracter == ';') {
            LastCharacter = Caracter;
        } else {
            LastCharacter = ' ';
        }


    } while (!feof(f));

    fclose(f);
    fclose(distancia);

    return 0;
}