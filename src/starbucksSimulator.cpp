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
#include <unistd.h> // For sleep

#include "ui.h"

using namespace std;


// --------- //
// Functions //
// --------- //

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

    string result = gameplayScreen("Round 1: Henry");

    // Cleanup
    endwin();

    cout << endl;
    cout << "character: " << character << endl;
    cout << "opponent: " << opponent << endl;
    cout << "user input: " << result << endl;

    return 0;
}
