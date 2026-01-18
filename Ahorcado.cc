#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

const int MaxTries = 6;

struct Words {
    int Length;
    char Letters[20];
};

struct LetterToGuess {
    char Letter;
    bool IsDiscovered = false;
};

struct UpperLetter {
    char Letter, LetterUp;
};

LetterToGuess WordSelected[20];
int Tries = 0;

Words WordsToGet[50] = {
    {5,  "ZELDA"},
    {5,  "MARIO"},
    {7,  "POKEMON"},
    {5,  "SONIC"},
    {4,  "HALO"},
    {7,  "MEGAMAN"},
    {6,  "METAL"},
    {9,  "FINALFANT"},
    {8,  "RESIDENT"},
    {8,  "ASSASSIN"},
    {6,  "CASTLE"},
    {7,  "FALLOUT"},
    {6,  "SKYRIM"},
    {4,  "DOOM"},
    {9,  "STARCRAFT"},
    {8,  "WARCRAFT"},
    {6,  "DIABLO"},
    {8,  "DARKSOUL"},
    {9,  "ELDENRING"},
    {6,  "TETRIS"},
    {6,  "PACMAN"},
    {9,  "MINECRAFT"},
    {6,  "PORTAL"},
    {8,  "HALFLIFE"},
    {7,  "DESTINY"},
    {9,  "OVERWATCH"},
    {8,  "BIOSHOCK"},
    {6,  "BORDER"},
    {6,  "FARCRY"},
    {6,  "HITMAN"},
    {6,  "BATMAN"},
    {6,  "ARKHAM"},
    {6,  "NINTEN"},
    {6,  "YAKUZA"},
    {7,  "PERSONA"},
    {7,  "MONSTER"},
    {7,  "STREETF"},
    {7,  "MORTALK"},
    {6,  "TEKKEN"},
    {7,  "DRAGONQ"},
    {7,  "KINGDOM"},
    {6,  "ANIMAL"},
    {7,  "SPLATON"},
    {7,  "METROID"},
    {8,  "DEADCELL"},
    {7,  "HORIZON"},
    {7,  "CONTROL"},
    {7,  "OUTLAST"},
    {5,  "GEARS"}
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

int strstruct(LetterToGuess Word[]) {
    int contador = 0;

    while (Word[contador].Letter != '\0') {
        contador++;
    }

    return contador;
}

void DeleteSpecialCharacters(char Cadena[]) {

    Cadena[strlen(Cadena) - 1] = '\0';
}

void PreselectWord() {
    int numRnd = rand() % 50;
    
    for (int i = 0; i <= strlen(WordsToGet[numRnd].Letters); i++) {
        if (i == strlen(WordsToGet[numRnd].Letters)) {
            WordSelected[i].Letter = '\0';
        } else {
            WordSelected[i].Letter = WordsToGet[numRnd].Letters[i];
        }
    }
}

void GenerateRand() {

    srand(time(NULL));
}

char charToUpper(char Letter) {
    for (int i = 0; i < 26; i++) {
        if (Letter == Alphabet[i].Letter) {
            Letter = Alphabet[i].LetterUp;
        }
    }

    return Letter;
}

void ShowWordLetters(int Length) {

    for (int i = 0; i < Length; i++) {
        if (!WordSelected[i].IsDiscovered) {
            printf("?  ");
        } else {
            printf("%c  ", WordSelected[i].Letter);
        }
    }

    printf("\n");

    printf("Te quedan %d intentos.", MaxTries - Tries);

    printf("\n");
}

bool ValidateLetter(char Letter) {

    bool LetterGuessIt = false;
    for (int i = 0; i < strstruct(WordSelected); i++) {
        if (Letter == WordSelected[i].Letter) {
            WordSelected[i].IsDiscovered = true;
            LetterGuessIt = true;
        }
    }

    return LetterGuessIt;
}

bool ValidateWord() {
    
    bool AllGood = true; 
    for (int i = 0; i < strstruct(WordSelected); i++) {
        if (!WordSelected[i].IsDiscovered) {
            AllGood = false;
        }
    }

    return AllGood;
}

void VamosAJugar() {

    int length = (strstruct(WordSelected));
    ShowWordLetters(length);
    
    printf("Introducir letra: ");

    char Letter = getch();

    bool TryOut = ValidateLetter(charToUpper(Letter));

    if (!TryOut) {
        Tries++;
    }

    bool Correct = ValidateWord();

    if (!Correct && Tries < MaxTries) {
        VamosAJugar();
    }
}

int main() {

    GenerateRand();

    PreselectWord();

    printf("La palabra contiene %d letras. Intenta adivinarla !! \n", strstruct(WordSelected));

    VamosAJugar();

    // checkeo de los tries y de la palabrita

    if (Tries == MaxTries) {

        printf("Fallaste. La palabra era: ");
        for (int i = 0; i < strstruct(WordSelected); i++) {
            printf("%c", WordSelected[i].Letter);
        }
    } else {
        printf("Felicidadeees !! Acertaste.");
    }

    return 0;
}
