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

void ReverseWord(char Cadena[80]) {
    
    int Length = strlen(Cadena);
    char Aux;

    for (int i = 0; i < Length / 2; i++) {
        // Necesito una auxiliar para guardar el caracter
        Aux = Cadena[i];
        // Necesito cambiar el ultimo caracter para asignarlo al ultimo
        Cadena[i] = Cadena[Length - i - 1];
        Cadena[Length - i - 1] = Aux;
    }
}

int main() {

    printf("Introducir cadena para evaluar palabras: ");
    fgets(Cadenita, 255, stdin);
    int CadenaLenght = strlen(Cadenita);
    DeleteSpecialCharacters(Cadenita);

    printf("Introducir la subcadena para ocultar: ");
    fgets(CadenaOcultar, 10, stdin);
    DeleteSpecialCharacters(CadenaOcultar);

    for (int i = 0; i < CadenaLenght - 1; i++) {
        if (Cadenita[i] == CadenaOcultar[0] && Cadenita[i + 1] == CadenaOcultar[1]) {
            Cadenita[i] = 'X';
            Cadenita[i + 1] = 'X';
        }
    }

    fputs(Cadenita, stdout);

    return 0;
}