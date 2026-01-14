#include <stdio.h>

char Cadena[255] = {'\0'}, SubCadena[255] = {'\0'}, NewCadena[255] = {'\0'};
int subIndex = 1;



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

int InsertCadena(int TimesToInsert, int SubLength, int IndexCadena) {
    printf("%d \n", TimesToInsert);
    printf("%d \n", SubLength);
    printf("%d \n", IndexCadena);
    for (int i = 0; i < TimesToInsert; i++) {
        for (int j = 1; j < SubLength + 1; j++) {

            NewCadena[IndexCadena] = SubCadena[j]; 
            IndexCadena++;
        }
    }

    // NewCadena[IndexCadena] = SubCadena[IndexSubCadena];

    return strlen(NewCadena);
}

int main() {

    printf("Cadena con numeros para multiplicar dicha cadena: ");
    fgets(Cadena, 255, stdin);
    DeleteSpecialCharacters(Cadena);

    int LastCIndex = 0;

    for (int i = 0; i < strlen(Cadena); i++) {

        if (Cadena[i] < 48 || Cadena[i] > 57) {
            SubCadena[subIndex] = Cadena[i];
            subIndex++;
        } else {
            SubCadena[0] = Cadena[i] - 48;
            LastCIndex = InsertCadena(SubCadena[0], strlen(SubCadena), LastCIndex);
            subIndex = 1;
        }
    }

    fputs(NewCadena, stdout);
}