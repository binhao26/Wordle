#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

/**
 * A simple implementation of the popular wordle game.
 * From cs50 lecture 2 Array - problem set worddle.
 * */

//*************************************************************Colour Constant*************************************************************************************
// each of our text files contains 1000 words
#define LISTSIZE 1000

// values for colors and score (EXACT == right letter, right place; CLOSE == right letter, wrong place; WRONG == wrong letter)
#define EXACT 2
#define CLOSE 1
#define WRONG 0

#define MAX_WORD_LENGTH 8

// ANSI color codes for boxed in letters
#define GREEN   "\e[38;2;255;255;255;1m\e[48;2;106;170;100;1m"
#define YELLOW  "\e[38;2;255;255;255;1m\e[48;2;201;180;88;1m"
#define RED     "\e[38;2;255;255;255;1m\e[48;2;220;20;60;1m"
#define RESET   "\e[0;39m"
//************************************************************/Colour Constant**********************************************************************************

char global_guess[MAX_WORD_LENGTH];
void get_guess(char global_guess[], int wordsize);
int check_word(char guess[], int wordsize, int status[], char choice[]);
void print_word(char guess[], int wordsize, int status[]);

int main()
{


    printf("Enter word size to begin the game: ");
    int wordsize = 0;
    int correct_wordsize = false;
    
    do{
        scanf("%d", &wordsize);
        if (wordsize == 5 || wordsize == 6 || wordsize == 7 || wordsize == 8){
            correct_wordsize = true;
        }
        else {
            printf("Incorrect wordsize");
        }

    }while(correct_wordsize == false);

    char choice[5] = {'h', 'e', 'l', 'l', 'o'}; // the correct word to finish the game

    // allow one more guess than the length of the word
    int guesses = wordsize + 1;
    bool won = false;

    // print greeting, using ANSI color codes to demonstrate
    printf(GREEN"This is WORDLE50"RESET"\n");
    printf("You have %i tries to guess the %i-letter word I'm thinking of\n", guesses, wordsize);

    // main game loop, one iteration for each guess
    char guess[wordsize];
    
    for (int i = 0; i < guesses; i++)
    {
        // obtain user's guess
        get_guess(global_guess, wordsize);
        strcpy(guess, global_guess);
       
        // array to hold guess status, initially set to zero
        int status[wordsize];

        // set all elements of status array initially to 0, aka WRONG
        for(int j = 0; j < wordsize; j++)
        {
            status[j] = 0;
            printf("Status[%d] is %d\n", j, status[j]);
        }

        // Calculate score for the guess
        int score = check_word(guess, wordsize, status, choice);
        // check status
        for(int j = 0; j < wordsize; j++)
        {
            printf("Status[%d] is %d\n", j, status[j]);
        }


        printf("Guess %i: ", i + 1);

        // Print the guess
        print_word(guess, wordsize, status);

        // if they guessed it exactly right, set terminate loop
        if (score == EXACT * wordsize)
        {
            won = true;
            break;
        }
    }

    // Print the game's result
    if (won == true)
    {
        printf("You won!\n");
    }
    else
    {
        printf("You lost :(\n");
        printf("The secret word is: %s\n", choice);
    }

    return 0;
}

/**
 * Gets 1 guess  from user 
 * terminates as soon as a correct  length
 * word entered
 * */
void get_guess(char global_guess[], int wordsize)  {
    bool correct_word_length = true;
    int input;
    int guess_wordsize = 0;

    while (correct_word_length) { 

        printf("Enter your guess: ");
        while ((input = getchar()) != '\n') {
            global_guess[guess_wordsize] = input;
            guess_wordsize++;
        }
        // terminates once word length matched the selected word length at start
        if (guess_wordsize == wordsize) {
            correct_word_length = false;
            break;
        }
        else {
            printf("guess_wordsizei s %d\n", guess_wordsize);
            printf("Incorrect word length for guess! Try again");
        }
        guess_wordsize = 0;

    }

}

/**
 * Returns score based on the correctness
 * of the guess entered by user
 * 
 * @status[] is for holding scores of guess word
 * */

int check_word(char guess[], int wordsize, int status[], char choice[]) {

   int score = 0;
   // nested loop checks individual letters in guess
    for (int i = 0; i < wordsize; i++) {

        for (int j = 0; j < wordsize; j++) {
            // if letter and its position in guess matched in correct word
            // Gives letter's index in status a score of exact
            if (guess[i] == choice[j] && i == j) {
                status[i] = EXACT;
                break;
                
            }
            //if the letter occured in correct word but position is not exact
            // gives it a score of CLOSE in status
            else if (guess[i] == choice[j]) {
                status[i] = CLOSE;
                
                
            }
            
        }
    }

    // sum up the total score
    for (int i = 0; i < wordsize; i++) {

        score+=status[i];
    }

    return score;
}

/**
 * Prints out the result of guess word
 * by using values in status[] that represents correctness
 * coloured each letter based on EXACT, CLOSE, WRONG
 * EXACT = GREEN
 * CLOSE = YELLOW
 * WRONG = RED
 * */
void print_word(char guess[], int wordsize, int status[]) {

    for (int i = 0; i < wordsize; i++) {

        switch(status[i]) {
            case EXACT:
                printf(GREEN"%c"RESET, guess[i]);
                break;
            case CLOSE:
                printf(YELLOW"%c"RESET, guess[i]);
                break;
            case WRONG:
                printf(RED"%c"RESET, guess[i]);
                break;
            default:
                printf("somethhing went wrong");
                break;
        }
    }
}



