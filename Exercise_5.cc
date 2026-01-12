#include <stdio.h>

char Cadenita[255] = {'\0'}, Word[255] = {'\0'}, NewCadenita[255] = {'\0'};

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

void AddNewCadena(int Index, char Cadena[]) {

    int LengthWord = strlen(Cadena);

    int contador = 0;
    for (int i = Index; i < Index + LengthWord; i++) {
        NewCadenita[i] = Cadena[contador];
        contador++;
    }
}

int main() {

    printf("Introducir cadena para evaluar palabras: ");
    fgets(Cadenita, 255, stdin);
    int CadenaLenght = strlen(Cadenita);
    DeleteSpecialCharacters(Cadenita);

    int LastIndex = 0;

    for (int i = 0; i < CadenaLenght - 1; i++) {
        
        Word[i] = Cadenita[i];

        if (Cadenita[i] == ' ' ||  Cadenita[i] == '\0') {
            ReverseWord(Word);
            AddNewCadena(LastIndex, Word);
            LastIndex = i + 1;
        }
    }

    fputs(NewCadenita, stdout);

    return 0;
}