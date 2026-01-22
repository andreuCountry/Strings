#include <stdio.h>

struct Info {
    char Origen[50], Destino[50], KMLongitud[10];
};

Info InfoToSet;

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

void CopyOrigin() {
    int i;
    for (i = 0; i < strlen(Cadena); i++) {
        InfoToSet.Origen[i] = Cadena[i];
    }

    InfoToSet.Origen[i++] = ';';
    InfoToSet.Origen[i++] = '\0';

    //fputs(InfoToSet.Origen, stdout);
}

void CopyDestiny() {
    int i;
    for (i = 0; i < strlen(Cadena); i++) {
        InfoToSet.Destino[i] = Cadena[i];
    }

    InfoToSet.Destino[i++] = ';';
    InfoToSet.Destino[i++] = '\0';

    //fputs(InfoToSet.Destino, stdout);
}

void CopyKm() {
    int i;
    for (i = 0; i < strlen(Cadena); i++) {
        InfoToSet.KMLongitud[i] = Cadena[i];
    }

    InfoToSet.KMLongitud[i++] = ';';
    InfoToSet.KMLongitud[i++] = '\0';

    //fputs(InfoToSet.KMLongitud, stdout);
}

void CopyCadena(int Index) {
    switch (Index) {
        case 0:
            CopyOrigin();
        break;
        case 1:
            CopyDestiny();
        break;
        case 2:
            CopyKm();
        break;
    }
}
void CleanInfo() {
    for (int i = 0; i < 50; i++) {
        InfoToSet.Origen[i] = '\0';
    }

    for (int i = 0; i < 50; i++) {
        InfoToSet.Destino[i] = '\0';
    }

    for (int i = 0; i < 10; i++) {
        InfoToSet.KMLongitud[i] = '\0';
    }

}

int main() {

    f = fopen("TablaKM.txt", "r");
    distancia = fopen("distancies.dat", "wb");

    int contador = 0, StartSpecialIndex = 0;

    do {
        // Check de los primeros params, despues vamos a los segundos

        char Character = fgetc(f);

        if (Character == '\n') {

            if (contador > 0) {
                Cadena[contador] = '\0';
                CopyCadena(StartSpecialIndex);
            }

            // Debuggear
            /*printf("Origen:   '%s'\n", InfoToSet.Origen);
            printf("Destino:  '%s'\n", InfoToSet.Destino);
            printf("Km:       '%s'\n", InfoToSet.KMLongitud);*/
            fwrite(&InfoToSet, sizeof(struct Info), 1, distancia);

            contador = 0;
            StartSpecialIndex = 0;
            CleanCadena(Cadena);
            CleanInfo();

            continue;
        }

        if (Character == ';') {

            Cadena[contador] = '\0';
            CopyCadena(StartSpecialIndex);
            StartSpecialIndex++;

            contador = 0;
            CleanCadena(Cadena);
            continue;
        }

        if (contador < 254) {
            Cadena[contador++] = Character;
        }

    } while (!feof(f));



    fclose(f);
    fclose(distancia);

    return 0;
}