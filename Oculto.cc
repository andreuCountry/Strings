#include <stdio.h>

char Cadenita[255] = {'\0'}, CadenaOcultar[10] = {'\0'};

int strlen(char Cadena[]) {
    int contador = 0;

    while (Cadena[contador] != '\0') {
        contador++;
    }

    return contador;
}

void DeleteSpecialCharacters(char Cadena[80]) {

    Cadena[strlen(Cadena) - 1] = '\0';
}

bool CompareStrings(int Index, char Cadena1[], char Cadena2[]) {
    bool Equal = true;
    for (int i = 0; i < strlen(Cadena2); i++) {
        if (Cadena1[Index + i] != Cadena2[i]) {
            Equal = false;
        }
    }

    return Equal;
}

int main() {

    printf("Introducir cadena para evaluar palabras: ");
    fgets(Cadenita, 255, stdin);
    int CadenaLenght = strlen(Cadenita);
    DeleteSpecialCharacters(Cadenita);

    printf("Introducir la subcadena para ocultar: ");
    fgets(CadenaOcultar, 10, stdin);
    DeleteSpecialCharacters(CadenaOcultar);

    for (int i = 0; i < CadenaLenght; i++) {
        // Lógica para añadir en mas de dos characteres, que me mire todos los strings

        if (Cadenita[i] == CadenaOcultar[0]) {
            bool Comparation = CompareStrings(i, Cadenita, CadenaOcultar);
            
            if (Comparation) {
                for (int j = 0; j < strlen(CadenaOcultar); j++) {
                    Cadenita[i + j] = 'X';
                }
            }
        }
    }

    fputs(Cadenita, stdout);

    return 0;
}