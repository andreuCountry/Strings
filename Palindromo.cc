#include <stdio.h>

char Cadena[255] = {'\0'}, FirstWord[255] = {'\0'}, SecondWord[255] = {'\0'};

int strlen(char Cadena[]) {
    int contador = 0;

    while (Cadena[contador] != '\0') {
        contador++;
    }

    return contador;
}

void DeleteSpecialCharacters(char Cadena[]) {

    Cadena[strlen(Cadena) - 1] = '\0';
}

void ReverseWord(char Cadena[]) {
    
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

bool CompareStrings(char Cadena1[], char Cadena2[]) {
    bool Equal = true;

    for (int i = 0; i < strlen(Cadena1); i++) {
        if (Cadena1[i] != Cadena2[i]) {
            Equal = false;
        }
    }

    return Equal;
}

int main() {

    printf("Introducir cadena para valorar si es palindromo: \n");
    fgets(Cadena, 255, stdin);
    int CadenaLenght = strlen(Cadena);
    DeleteSpecialCharacters(Cadena);

    int contador = 0;

    for (int i = 0; i < CadenaLenght; i++) {
        if (i < (CadenaLenght/2) - 1) {
            FirstWord[i] = Cadena[i];
        }
        
        if (i > (CadenaLenght/2) - 1) {
            SecondWord[contador] = Cadena[i];
            contador++;
        }
    }

    ReverseWord(SecondWord);

    printf("\n");

    bool Comparation = CompareStrings(FirstWord, SecondWord);

    if (Comparation) {
        printf("La palabra es un palindromoo!!!");
    } else {
        printf("La palabra no es un palindromo .....");
    }

    return 0;
}