#include <stdio.h>
#include <string.h>

struct Info {
    char Origen[50], Destino[50], KMLongitud[10];
};

FILE *f;
char Origen[50], Destino[50], KMLongitud[10];

Info InformationGiven;

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

void SaveInfo() {
    printf("Introduzca el origen: ");
    fgets(Origen, 50, stdin);
    DeleteSpecialCharacters(Origen);

    printf("\n");

    printf("Introduzca el destino: ");
    fgets(Destino, 50, stdin);
    DeleteSpecialCharacters(Destino);

}

int main() {

    SaveInfo();

    f = fopen("distancies.dat", "rb");

    int StartIndex = 0, contador = 0;

    while (fread(&InformationGiven, sizeof(struct Info), 1, f)) {

        DeleteSpecialCharacters(InformationGiven.Origen);
        DeleteSpecialCharacters(InformationGiven.Destino);
        DeleteSpecialCharacters(InformationGiven.KMLongitud);    

        if (strcmp(Origen, InformationGiven.Origen) == 0 && strcmp(Destino, InformationGiven.Destino) == 0) {
            printf("La distancia es: ");
            for (int i = 0; i < strlen(InformationGiven.KMLongitud); i++) {
                printf("%c", InformationGiven.KMLongitud[i]);
            }
            printf(" Km");
        }
        
    }
    
    fclose(f);

    return 0;
}