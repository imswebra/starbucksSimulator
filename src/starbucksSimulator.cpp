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

using namespace std;


// --------- //
// Functions //
// --------- //

// TEMPORARY: Only as a demonstration of the gameplay ui
void round(string prompt) {
    // Create and draw the prompt
    WINDOW* pWin = createPrompt(prompt);

    // Draw the rest of the gameplay screen and get the user input
    timer t(10, time(NULL));
    while (t.verify()) {
        string result = gameplayScreen(t); // Get user input
        // Check that result.size() > 0;
        // Clean result -> Remove spaces and hyphens
        // Check that result.size() > 0;
        // Verify equal phonetic index
        // Calculate awarded points
    }

    // Cleanup
    delwin(pWin);
    clear();
    refresh();
}


// Main function
int main() {
    cout << "Starbucks Simulator Starting..." << endl;
    system("resize -s 12 56"); // Ghetto, not a good way to do this
    sleep(1);

    // Ncurses initialization
    initscr();
    cbreak();
    noecho();

    curs_set(0);
    titleScreen();
    int character = selectScreen("Choose your character:",
                                 {"Character 0", "Character 1", "Character 2"});
    int opponent = selectScreen("Choose your opponent:",
                                {"Opponent 0", "Opponent 1", "Opponent 2"});
    curs_set(1);

    round("Round 1: Henry");
    round("Round 2: Eric");
    round("Round 3: Ryan");

    // Cleanup
    endwin();
    return 0;
}
