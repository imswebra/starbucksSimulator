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
#include "cpu.h"

using namespace std;


// --------- //
// Functions //
// --------- //

// TEMPORARY: Only as a demonstration of the gameplay ui
void round(string prompt, Game& foo) {
    // Create and draw the prompt
    WINDOW* pWin = createPrompt(prompt);

    int score = 0;
    // Draw the rest of the gameplay screen and get the user input
    timer t(020, time(NULL));
    while (t.verify()) {
        string result = gameplayScreen(t, score); // Get user input
        // Check that result.size() > 0;
        // Clean result -> Remove spaces and hyphens
        // Check that result.size() > 0;
        // Verify equal phonetic index
        // Calculate awarded points
        if (result.empty()) break;  // no input to be processed
        foo.processInput(result);
        score = foo.getScore();
    }

    // Cleanup
    delwin(pWin);
    clear();
    refresh();
}


// Main function
int main() {
    cout << "Starbucks Simulator Starting..." << endl;
    system("resize -s 12 55"); // Ghetto, not a good way to do this
    sleep(1);

    // Ncurses initialization
    initscr();
    cbreak();
    noecho();

    curs_set(0);
    titleScreen();

    int character = selectScreen("Choose your fighter",
                                 {"Names 0", "Names 1", "Names 2"});
    int opponent = selectScreen("Choose your rival",
                                {"Character 0", "Character 1", "Character 2"});
    curs_set(1);

    Game foo(character, opponent);
    round("Round 1: " + foo.displayName(), foo);
    foo.nextName();
    round("Round 2: " + foo.displayName(), foo);
    foo.nextName();
    round("Round 3: " + foo.displayName(), foo);

    // Cleanup
    endwin();
    return 0;
}
