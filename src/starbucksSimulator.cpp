/*
Author: Eric Claerhout, Henry Lin
Student ID: 1532360, 1580649
CMPUT 275 Winter 2019

Final Project: Starbucks Simulator
##################################
*/

// ------------------------ //
// Includes and Definitions //
// ------------------------ //
#include <iostream>
#include <ncurses.h>
#include <ctime>
#include <unistd.h> // For sleep

#include "ui.h"
#include "uiHelper.h" // For Timer class
#include "gameController.h"

using namespace std;


// --------- //
// Functions //
// --------- //

void round(string prompt, Cpu& game, int& score) {
    // Initialize variables
    Timer t(30, time(NULL));
    int roundScore = 0;
    string resultsMessage = "";

    // Create and draw the prompt
    WINDOW* pWin = createPrompt(prompt);

    while (t.verify()) {
        // Draw the rest of the gameplay screen and get the user input
        string input = gameplayScreen(t, roundScore + score, resultsMessage);
        if (input.empty() || input == game.displayName()) {
            resultsMessage = "";
            continue;
        }

        // Verify equal phonetic index
        game.processInput(input);

        // Calculate awarded points, notify user
        int inputScore = game.getScore();
        if (inputScore == 0) resultsMessage = "Doesn't sound the same!";
        else if (inputScore > roundScore) {
            roundScore = inputScore;
            resultsMessage = "Score of " + to_string(inputScore)
                              + ", round score is now " + to_string(roundScore);
        }
        else if (inputScore <= roundScore) {
            resultsMessage = "Score of " + to_string(inputScore)
                            + ", round score is still " + to_string(roundScore);
        }
    }

    // Update game score with the final round score
    score += roundScore;

    // Cleanup
    delwin(pWin);
    clear();
    refresh();
}


// Main function
int main() {
    cout << "Starbucks Simulator Starting..." << endl;
    if(system("resize -s 12 55")); // Terminal dependent, see README
    sleep(1);

    // Ncurses initialization
    initscr();
    cbreak();
    noecho();
    curs_set(0);

    while (true) {
        titleScreen();

        int character = selectScreen("Choose your fighter",
                                 {"1800s names", "1950s names", "2000s names"});
        int opponent = selectScreen("Choose your rival",
                                 {"Soundex", "NYSIIS", "Metaphone"});

        Cpu game(character, opponent);
        int score = 0;

        readyScreen(1, score);
        round("Round 1: " + game.displayName(), game, score);

        game.nextName();
        readyScreen(2, score);
        round("Round 2: " + game.displayName(), game, score);

        game.nextName();
        readyScreen(3, score);
        round("Round 3: " + game.displayName(), game, score);

        // If player chooses to quit
        if (!resultsScreen(score)) { break; }
    }

    // Cleanup
    endwin();
    return 0;
}
