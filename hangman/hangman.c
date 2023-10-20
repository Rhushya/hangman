#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Node {
    char data;
    struct Node* next;
} Node;

Node* createNode(char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

Node* appendNode(Node* head, char data) {
    if (head == NULL) {
        return createNode(data);
    }
    Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = createNode(data);
    return head;
}

void displayWord(Node* word, char* guessedLetters) {
    Node* current = word;
    while (current != NULL) {
        if (strchr(guessedLetters, current->data)) {
            printf("%c", current->data);
        } else {
            printf("_");
        }
        current = current->next;
    }
    printf("\n");
}

int main() {
    srand(time(0));

    char* movieNames[] = {
        "avatar", "inception", "titanic", "jaws", "matrix", "starwars",
        "fightclub", "pulpfiction", "forrestgump", "shawshank", "gladiator",
        "braveheart", "jurassicpark", "interstellar", "gravity", "memento",
        "inception", "thegodfather", "shutterisland", "blackswan", "thehobbit",
        "incredibles", "batmanbegins", "terminator", "theshining", "goodfellas",
        "eternalsunshine", "bladerunner", "deadpool", "forrestgump", "reservoirdogs",
        "thelionking", "casino", "americanpsycho", "panslabyrinth", "gladiator",
        "inception", "thegodfather", "darkknight", "frozen", "godzilla",
        "interstellar", "incredibles", "predator", "psycho"
    };
    int numMovies = sizeof(movieNames) / sizeof(movieNames[0]);

    int mode;
    printf("Hangman Game\n");
    printf("Select a mode:\n");
    printf("1. Single Player (Computer selects movie name)\n");
    printf("2. Two Player (One player enters movie name, the other guesses)\n");
    printf("Enter 1 or 2: ");
    scanf("%d", &mode);

    int correctGuesses = 0;
    int incorrectGuesses = 0;
    int attempts = 0;

    if (mode == 1) {
        char* movieName = movieNames[rand() % numMovies];
        int tries = 6;
        char guessedLetters[26] = {0};

        Node* word = NULL;
        for (int i = 0; i < strlen(movieName); i++) {
            word = appendNode(word, movieName[i]);
        }

        while (tries > 0) {
            printf("Tries left: %d\n", tries);
            printf("Enter a letter: ");
            char guess;
            scanf(" %c", &guess);

            if (strchr(guessedLetters, guess)) {
                printf("You already guessed that letter. Try again.\n");
                continue;
            }

            guessedLetters[strlen(guessedLetters)] = guess;
            attempts++;

            if (!strchr(movieName, guess)) {
                tries--;
                incorrectGuesses++;
                if (tries == 0) {
                    printf("You ran out of tries. The movie was: %s\n", movieName);
                    break;
                }
            } else {
                correctGuesses++;
            }

            int allGuessed = 1;
            Node* current = word;
            while (current != NULL) {
                if (!strchr(guessedLetters, current->data)) {
                    allGuessed = 0;
                    break;
                }
                current = current->next;
            }

            if (allGuessed) {
                printf("Congratulations! You guessed the movie: %s\n", movieName);
                break;
            }

            printf("Guessed so far: ");
            displayWord(word, guessedLetters);
        }
    } else if (mode == 2) {
        char movieName[50];
        printf("Player 1, enter the movie name (in lowercase, no spaces): ");
        scanf("%s", movieName);
        int len = strlen(movieName);

        char guessedLetters[26] = {0};
        int tries = 6;

        Node* word = NULL;
        for (int i = 0; i < len; i++) {
            word = appendNode(word, movieName[i]);
        }

        while (tries > 0) {
            printf("Tries left: %d\n", tries);
            printf("Enter a letter: ");
            char guess;
            scanf(" %c", &guess);

            if (strchr(guessedLetters, guess)) {
                printf("You already guessed that letter. Try again.\n");
                continue;
            }

            guessedLetters[strlen(guessedLetters)] = guess;
            attempts++;

            if (!strchr(movieName, guess)) {
                tries--;
                incorrectGuesses++;
                if (tries == 0) {
                    printf("You ran out of tries. The movie was: %s\n", movieName);
                    break;
                }
            } else {
                correctGuesses++;
            }

            int allGuessed = 1;
            Node* current = word;
            while (current != NULL) {
                if (!strchr(guessedLetters, current->data)) {
                    allGuessed = 0;
                    break;
                }
                current = current->next;
            }

            if (allGuessed) {
                printf("Congratulations! You guessed the movie: %s\n", movieName);
                break;
            }

            printf("Guessed so far: ");
            displayWord(word, guessedLetters);
        }
    } else {
        printf("Invalid mode selection.\n");
    }

    printf("Number of correct guesses: %d\n", correctGuesses);
    printf("Number of incorrect guesses: %d\n", incorrectGuesses);
    printf("Total attempts: %d\n", attempts);

    return 0;
}
