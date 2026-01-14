#include <stdio.h>

char Cadena[255] = {'\0'}, SubCadena[255] = {'\0'}, NewCadena[255] = {'\0'};

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

void ResetCadena(int Length) {
    for (int i = 0; i < Length; i++) {
        SubCadena[i] = '\0'; 
    }
}

int InsertCadena(int TimesToInsert, int LengthSubCadena, int IndexCadena) {
    for (int i = 0; i < TimesToInsert; i++) {
        for (int j = 0; j < LengthSubCadena; j++) {
            NewCadena[IndexCadena + j] = SubCadena[j];
        }

        IndexCadena += LengthSubCadena;
    }

    return IndexCadena;
}

int main() {
    printf("Cadena con numeros para multiplicar dicha cadena: ");
    fgets(Cadena, 255, stdin);
    DeleteSpecialCharacters(Cadena);

    int number = Cadena[0] - 48;
    int LastCIndex = 0;
    int subIndex = 0;

    for (int i = 1; i < strlen(Cadena); i++) {

        if (Cadena[i] < 48 || Cadena[i] > 57) {
            SubCadena[subIndex++] = Cadena[i];
        } else {
            // No entra aqui
            LastCIndex = InsertCadena(number, strlen(SubCadena), LastCIndex);
            ResetCadena(255);
            number = Cadena[i] - 48;
        }
    }

    if (subIndex > 0) {
        InsertCadena(number, subIndex, LastCIndex);
        // ahora sí terminamos la cadena
        NewCadena[LastCIndex + number * subIndex] = '\0';
    }

    fputs(NewCadena, stdout);
}