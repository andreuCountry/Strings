#include <stdio.h>

char Cadena[255] = {'\0'}, SubCadena[255] = {'\0'}, NewCadena[255] = {'\0'};
int firstIndex = 0, secondIndex;

bool Fin = false;

// Pensar, la subcadena debe contener el digito de cuantas veces se repite, figura

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

int ImprimirCadena(int Cuantity, int FirstIndex, int SecondIndex) {


    for (int i = 0; i < Cuantity; i++) {
        for (int j = FirstIndex + 1; j < SecondIndex; j++) {
            if (!Fin) {
                printf("%c", Cadena[j]);
            }
        }
    }

    return strlen(NewCadena);
}

int main() {

    printf("Cadena con numeros para multiplicar dicha cadena: ");
    fgets(Cadena, 255, stdin);
    DeleteSpecialCharacters(Cadena);

    for (int i = 0; i < strlen(Cadena); i++) {

        if (Cadena[i] >= 48 && Cadena[i] <= 57) {
            firstIndex = i;
            Fin = false;
            for (int j = firstIndex + 1; j < strlen(Cadena) + 1; j++) {
                if ((Cadena[j] >= 48 && Cadena[j] <= 57) || Cadena[j] == '\0') {
                    secondIndex = j;
                    ImprimirCadena(Cadena[firstIndex] - 48, firstIndex, secondIndex);
                    Fin = true;
                }
            }
        }
    }
}