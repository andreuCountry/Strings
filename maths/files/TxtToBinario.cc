#include <stdio.h>

struct Info {
    char Origen[50], Destino[];
    int KMLongitud;
};

FILE *f, *distancia;
int valor;
char Cadena[255];

int strlen(char Cadena[]) {
    int contador = 0;

    while (Cadena[contador] != '\0') {
        contador++;
    }

    return contador;
}

void CleanCadena(char Cadena[]) {
    for (int i = 0; i < strlen(Cadena); i++) {
        Cadena[i] = '\0';
    }
}

int main() {

    f = fopen("TablaKM.txt", "r");
    distancia = fopen("distancies.dat", "wb");

    int StartIndex = 0, LastIndex = 0;
    int contador = 0;

    do {
        // Check de los primeros params, despues vamos a los segundos

        char Character = fgetc(f);

        if (Character != ';') {
            Cadena[contador] = Character;
        }

    } while (!feof(f));

    fclose(f);
    fclose(distancia);

    return 0;
}