#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

char MorseCadena[255];

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

/*
    'A', ".-",
	'B', "-...",
	'C', "-.-.",
	'D', "-..",
	'E', ".",
	'F', "..-.",
	'G', "--.",
	'H', "....",
	'I', "..",
	'J', ".---",
	'K', "-.-",
	'L', ".-..",
	'M', "--",
	'N', "-.",
	'Ñ', "--.--",
	'O', "---",
	'P', "-..-",
	'Q', "--.-",
	'R', ".-.",
	'S', "...",
	'T', "-",
	'U', "..-",
	'V', "...-",
	'W', ".--",
	'X', "-..-",
	'Y', "-.--",
	'Z', "--..",
	'0', "-----",
	'1', ".----",
	'2', "..---",
	'3', "...--",
	'4', "....-",
	'5', ".....",
	'6', "-....",
	'7', "--...",
	'8', "---..",
	'9', "----.",
*/

void MorseIntoHuman() {

}

void HumanIntoMorse() {

}

void Translate() {

}

void ReadMagic() {
    fgets(MorseCadena, 255, stdin);
    DeleteSpecialCharacters(MorseCadena);
}

void ValidateOption(char Option) {
    switch (Option) {
        case '1':
            printf("Escribeme una cosita en lenguaje humano, y te traduzco a humano: ");
            ReadMagic();
            MorseIntoHuman();
        break;
        case '2':
            printf("Escribeme una cosita en morse, y te traduzco a morse: ");
            ReadMagic();
            HumanIntoMorse();
        break;
        case '3':
            printf("Lo siguiente que escribas, se mete directo en morse: ");
            Translate();
        break;
    }

    //system("cls");

}

void ShowMenu() {
    printf("1 -- Escribe en morse y traducimos a lenguaje humano \n");
    printf("2 -- Esribe en lenguaje humano y traducimos a morse \n");
    printf("3 -- Escribe directamente en morse \n");
    printf("4 -- Salir! \n");
}

int main() {

    char Option;

    do {
        
        ShowMenu();

        // Lógica para que no se ejecute si no es un n valido
        Option = getch();

        ValidateOption(Option);

    } while(Option != '4');

    return 0;
}