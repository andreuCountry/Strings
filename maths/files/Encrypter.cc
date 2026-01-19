#include <stdio.h>

FILE *f;

char Cadena[500], Caracter;

char EncryptedCharacter(char Character) {
    return Character + 3;
}

char DecryptedCharacter(char Character) {
    return Character - 3;
}

int main() {

    if ((f=fopen("original.txt", "r")) == NULL) {
        printf("Error. Este fichero no existe");
    } else {
        int contador = 0;

        do {
            Caracter = EncryptedCharacter(fgetc(f));

            Cadena[contador] = Caracter;
            contador++;
        } while (!feof(f));
        fclose(f);

        // Añadir a codigo.txt el tochaco
        f = fopen("codigo.txt", "w");
        fputs(Cadena, f);
        fclose(f);

        int secondContador = 0;

        f = fopen("codigo.txt", "r");

        do {
            Caracter = DecryptedCharacter(fgetc(f));

            Cadena[secondContador] = Caracter;
            secondContador++;
        } while (!feof(f));
        fclose(f);

        f = fopen("texto.txt", "w");
        fputs(Cadena, f);
        fclose(f);
    }

    return 0;
}