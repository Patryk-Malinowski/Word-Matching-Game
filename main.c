//Patryk Malinowski
// R00210173
// Word Matching Game

#include <stdio.h>
#include "utils.h"
#include <ctype.h>
#include <string.h>
#include <time.h>

#define DICT_SIZE 5757
#define WORD_SIZE 5


void load_word_list(char dictionary[DICT_SIZE][WORD_SIZE+1]){

    char *file_name = "./word_list.txt";

    FILE* f = fopen(file_name, "r");
    int idx = 0;

    if (f == NULL){
        printf("%s does not exist. Please ensure you have downloaded it from Canvas.", file_name);
    }
    else{
        while(fscanf(f, "%s", dictionary[idx++]) != EOF);
    }
}


int main() {

    char my2dArray[5757][6];
    char correctArray[6];
    int random;
    char guessArray[20];
    char inputContinue = 'y';
    char correctChar = 0;
    char gameArray[6];
    int winstreak = 0;
    int gamesPlayed = 0;
    int guesses = 6; // the player has 6 guesses
    char alphabetArray[27]; // holds every letter in the alphabet

    for (int i = 0; i < 26; i++) { // fills alphabetArray with the alphabet
        alphabetArray[i] = 'a' + i;
    }

    load_word_list(my2dArray); // loads the 5-letter word list into my2dArray

    srand(time(NULL)); // initialize once, creates random seed for random generator, disable this when testing
    random = rand() % 5757;

    for (int i = 0; i < 5; ++i) { // chooses a 5-letter word at random from the list
        correctArray[i] = my2dArray[random][i];
//        printf("%c", correctArray[i]); // prints the chosen word for testing purposes
    }


    for (int i = 0; i < 5; i++) { // initialise game array to *
        gameArray[i] = '*';
    }

    printf("\n***** Word Matching Game *****\n");
    printf("***** Enjoy! *****\n\n");

    printf("You must guess the 5 letter word!");
    while (inputContinue == 'y') {


        printf("\n");


        for (int i = 0; i < 20; i++) { // initialise guess array to 0
            guessArray[i] = 0;
        }

        printf("\nYou have %d guesses left.", guesses);
        printf("\nEnter your guess:");


        char input = 0;
        int count = 0; // keeps track of how many chars a guess has
        int valid = 1; // keeps track whether a guess is valid or not

        while (1) { // while loop that carries out checks to see if a guess is valid
            for (int i = 0; input != '\n'; i++) {
                input = getchar();
                if (input == '\n') {
                    break;
                } else {
                    guessArray[i] = input;
                    guessArray[i] = tolower(guessArray[i]);
                    count++;
                }
            }


            if (count != 5) { // if too many chars
                valid = 0;
                printf("\nPlease enter a 5 letter word only:");
                printf("\nEnter your guess:");
                input = 0;
                count = 0;

                for (int i = 0; i < 20; i++) {
                    guessArray[i] = 0;
                }

            } else {
                int check = 0;

                for (int i = 0; i < 5; i++) {
                    if (isalpha(guessArray[i])) {
                        check++;
                    }
                }

                if (check == 5) {
                    valid = 1;
                } else {
                    valid = 0;
                    printf("\nPlease enter a 5 letter word only:");
                    printf("\nEnter your guess:");
                    input = 0;
                    count = 0;

                    for (int i = 0; i < 20; i++) {
                        guessArray[i] = 0;
                    }
                }
            }
            int listWord = 0;
            for (int i = 0; i < 5757; i++) { // checks if a word is in the list
                if (strcmp(guessArray, my2dArray[i]) == 0) {
                    listWord = 1;
                    valid = 1;
                    break;
                }
            }

            if (listWord == 0 && count == 5) {
                printf("\nThis 5 letter word is not in the list, try again.");
                printf("\nEnter your guess:");

                valid = 0;
                input = 0;
                count = 0;
            }


            if (valid == 1) {
                guesses--;
                break;
            }
        } // end first inside while

        int count2 = 0;
        int k = 0;
        while (1) { // while loop for checking correctly guessed characters
            int validChar = 0; // keeps track whether a char in a guess is correct or not


            for (k; k < 5 && validChar == 0; k++) { // checks each char one by one in guess if it exists in any index of correct word
                for (int j = 0; j < 5; j++) {
                    if (guessArray[k] == correctArray[j]) {
                        correctChar = guessArray[k];
                        validChar = 1;
                        break;
                    }
                }
                count2++;
            }


            for (int i = 0; i < 5; i++) { // if a char has not been guessed yet, it will be added to game array if it is guessed correctly
                if (correctArray[i] == correctChar) {
                    if (gameArray[i] == '*') {
                        gameArray[i] = correctChar;
                    }
                }
            }

            if (count2 == 5) {
                k = 0;
                count2 = 0;
                break;
            }

        } // end second inside while loop


        printf("Guess: %s\n", guessArray); // prints the users guess

//        printf("Correct: %s\n", correctArray); // prints correct word for testing

        printf("Game: %s\n", gameArray); // prints game array


        int count3 = 0;
        char hint[6] = {'-'};
        char correctLetters[6];
        int correctLettersLength =0;
        for (int i = 0; i < 5; i++) { // checks if the game array contains all 5 correct characters
            if (correctArray[i] == gameArray[i]) {
                hint[i] = correctArray[i];
                count3++;
            }else{
                for (int j=0;j<5;j++){
                    if (gameArray[i] == correctArray[j]){
                        correctLetters[correctLettersLength++] = gameArray[i];
                    }
                }

            }
        }


        if (count3 == 5) { // If user guessed the word
            printf("\nCongratulations! You guessed the word!");
            winstreak++;
        }
        if (guesses == 0) { // If user runs out of guesses and did not guess the word
            if (count3 != 5) {
                printf("\nYou ran out of guesses! Better luck next time!");
                printf("\nThe correct word was %s!", correctArray);
            }

        }

        if (count3 == 5 || guesses == 0) { // if the user won AND/OR ran out of guesses, asks user if he wants to play again.
            printf("\nPress 'y' to play again or press 'n' to exit");
            inputContinue = getchar();
            while (getchar() != '\n');

            if (inputContinue == 'y') { // the user wants to play again
                guesses = 6; // the player has 6 guesses
                gamesPlayed++;
                random = rand() % 5757;
                for (int i = 0; i < 5; ++i) { // chooses a 5-letter word at random from the list
                    correctArray[i] = my2dArray[random][i];
                    //        printf("%c", correctArray[i]); // prints the chosen word for testing purposes
                }

                for (int i = 0; i < 5; i++) { // initialise game array to *
                    gameArray[i] = '*';
                }
            } else { // the user chooses not to play again
                gamesPlayed++;
                float winPercentage = (float) winstreak / (float) gamesPlayed * 100;
                float charPercentage = 0;
                printf("\nYou have won %d game(s) out of %d", winstreak, gamesPlayed);
                printf("\nYour win percentage is %.2f%%", winPercentage);
            }
        }
    } // end main while loop
}

