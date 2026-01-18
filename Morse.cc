#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

char Cadena[1000];
int LastIndex = 0;

struct Morse {
    char Character, MorseWay[6];
    int Length;
};

struct UpperLetter {
    char Letter, LetterUp;
};

Morse Table[36] = {
    {'A', ".-", 2},
	{'B', "-...", 4},
	{'C', "-.-.", 4},
	{'D', "-..", 3},
	{'E', ".", 1},
	{'F', "..-.", 4},
	{'G', "--.", 3},
	{'H', "....", 4},
	{'I', "..", 2},
	{'J', ".---", 4},
	{'K', "-.-", 3},
	{'L', ".-..", 4},
	{'M', "--", 2},
	{'N', "-.", 2},
	{'O', "---", 3},
	{'P', "-..-", 4},
	{'Q', "--.-", 4},
	{'R', ".-.", 3},
	{'S', "...", 3},
	{'T', "-", 1},
	{'U', "..-", 3},
	{'V', "...-", 4},
	{'W', ".--", 3},
	{'X', "-..-", 4},
	{'Y', "-.--", 4},
	{'Z', "--..", 4},
	{'0', "-----", 5},
	{'1', ".----", 5},
	{'2', "..---", 5},
	{'3', "...--", 5},
	{'4', "....-", 5},
	{'5', ".....", 5},
	{'6', "-....", 5},
	{'7', "--...", 5},
	{'8', "---..", 5},
	{'9', "----.", 5},
};

UpperLetter Alphabet[26] = {
    {'a', 'A',},
	{'b', 'B'},
	{'c', 'C'},
	{'d', 'D'},
	{'e', 'E'},
	{'f', 'F'},
	{'g', 'G'},
	{'h', 'H'},
	{'i', 'I'},
	{'j', 'J'},
	{'k', 'K'},
	{'l', 'L'},
	{'m', 'M'},
	{'n', 'N'},
	{'o', 'O'},
	{'p', 'P'},
	{'q', 'Q'},
	{'r', 'R'},
	{'s', 'S'},
	{'t', 'T'},
	{'u', 'U'},
	{'v', 'V'},
	{'w', 'W'},
	{'x', 'X'},
	{'y', 'Y'},
	{'z', 'Z'}
};

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

char charToUpper(char Letter) {
    for (int i = 0; i < 26; i++) {
        if (Letter == Alphabet[i].Letter) {
            Letter = Alphabet[i].LetterUp;
        }
    }

    return Letter;
}

void Maps(char Letter, bool IsMorse, int Start, int Index) {

    if (!IsMorse) {
        Letter = charToUpper(Letter);
    }

    if (!IsMorse) {
        for (int i = 0; i < 36; i++) {
            if (Letter == Table[i].Character) {
                for (int j = 0; j < strlen(Table[i].MorseWay); j++) {
                    printf("%c", Table[i].MorseWay[j]);
                }
                printf(" ");
            }
        }
    } else {
        int lenghtMorseLetter = Index - Start;

        for (int i = 0; i < 36; i++) {
            if (Table[i].Length == lenghtMorseLetter) {
                bool IsValid = true;

                for (int j = 0; j < lenghtMorseLetter; j++) {
                    if (Table[i].MorseWay[j] != Cadena[LastIndex + j]) {
                        IsValid = false;
                    }
                }

                if (IsValid) {
                    printf("%c", Table[i].Character);
                }
            }
        }
    }
    
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
    for (int i = 0; i < strlen(Cadena); i++) {

        if (Cadena[i + 1] == ' ' || Cadena[i + 1] == '\0') {
            Maps(Cadena[i], true, LastIndex, i + 1);
            LastIndex = i + 2;
        }

        if (Cadena[i + 1] == ' ' && Cadena[i + 2] == ' ') {
            printf(" ");
        }
    }

    printf("\n");
}

void HumanIntoMorse() {
    for (int i = 0; i < strlen(Cadena); i++) {

        if (Cadena[i] != ' ') {
            Maps(Cadena[i], false, LastIndex, i);
        } else {
            printf(" ");
        }
    }

    printf("\n");
}

void Translate(char Letter) {
    for (int i = 0; i < 36; i++) {
        if (Table[i].Character == Letter) {
            int length = strlen(Table[i].MorseWay);

            for (int j = 0; j < length; j++) {
                printf("%c", Table[i].MorseWay[j]);
            }
            printf(" ");
        }
    }    
}

void ReadMagic() {
    fgets(Cadena, 255, stdin);
    DeleteSpecialCharacters(Cadena);
}

void ValidateOption(char Option) {
    switch (Option) {
        case '1':
            printf("Escribeme una cosita en morse, y te traduzco a lenguage humano: ");
            ReadMagic();
            MorseIntoHuman();
        break;
        case '2':
            printf("Escribeme una cosita en lenguaje humano, y te traduzco a morse: ");
            ReadMagic();
            HumanIntoMorse();
        break;
        case '3':
            printf("Lo siguiente que escribas, se mete directo en morse: ");
            char LetterIntroduceIt = getch();

            while (LetterIntroduceIt != '\r') {
                
                if (LetterIntroduceIt == ' ') {
                    printf("  ");
                }

                if (LetterIntroduceIt < 48 || LetterIntroduceIt > 57) {
                    Translate(charToUpper(LetterIntroduceIt));
                } else if (LetterIntroduceIt >= 48 && LetterIntroduceIt <= 57){
                    Translate(LetterIntroduceIt);
                }

                LetterIntroduceIt = getch();
            }

            printf("\n");
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