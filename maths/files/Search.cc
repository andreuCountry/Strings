#include <stdio.h>

FILE *f;

char Character, Word[20], WordText[20];

struct LowerLetter {
    char LetterLow, Letter;
};

LowerLetter Alphabet[27] = {
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
	{'z', 'Z'},
    {' ', ' '}
};


// Necesito palabrita para buscarla en todo un texto

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

char charToLower(char Letter) {
    for (int i = 0; i < 27; i++) {
        if (Letter == Alphabet[i].Letter) {
            Letter = Alphabet[i].LetterLow;
        }
    }

    return Letter;
}

int main() {

    printf("Palabrita a buscar: ");
    fgets(Word, 20, stdin);
    DeleteSpecialCharacters(Word);

    f = fopen("quijote.txt", "r");
    
    int contador = 0, LastIndex = 0;
    do {

        bool Searched = true;

        Character = charToLower(fgetc(f));

        if (Character != ' ') {
            WordText[LastIndex] = Character;
            LastIndex++;
        } else {
            LastIndex = 0;
            for (int i = 0; i < strlen(Word); i++) {
                if (Word[i] != WordText[i]) {
                    Searched = false;
                }
            }

            if (Searched) {
                contador++;
            }
        }

    } while (!feof(f));
    
    fclose(f);

    printf("Sale un total de %d.", contador);

    return 0;
}