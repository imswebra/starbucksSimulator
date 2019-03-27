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

    initscr();
    cbreak(); // For the menu
    noecho(); // For the menu

    curs_set(0);
    titleScreen();
    int character = selectScreen("Choose your character:",
                                 {"Character 0", "Character 1", "Character 2"});
    int opponent = selectScreen("Choose your opponent:",
                                {"Opponent 0", "Opponent 1", "Opponent 2"});
    curs_set(1);

    // Cleanup
    endwin();

    cout << character << " " << opponent << endl;

    return 0;
}
