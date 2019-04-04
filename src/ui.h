#ifndef _UI_H_
#define _UI_H_
/*
Author: Eric Claerhout, Henry Lin
Student ID: 1532360, 1580649
CMPUT 275 Winter 2019

Final Project: Starbucks Simulator
##################################
*/

// -------- //
// Includes //
// ---------//
#include <ncurses.h>
#include <string>
#include <vector>

#include "uiHelper.h"


// --------- //
// Functions //
// --------- //

/* Title Screen function
Draws the title screen and waits for user input (Enter) before returning.
*/
void titleScreen();


/* Select Screen function
Draws the select screen and processes user input to allow user selection.
Returns an integer corresponding to the user's choice.

Args:
- prompt: The prompt string displayed at the top of the screen
- choiceStrs: A string vector of the available choices to the user. The strings
              are displayed in order and the returned integer corresponds to an
              index in this vector. Best if 1-6 strings are provided.
*/
int selectScreen(std::string prompt, std::vector<std::string> choiceStrs);


/* Create Prompt function
Creates and draws a centered prompt window at the top of the terminal, complete
with border. Looks best if the prompt string is the same parity as the
terminal's width (odd or even). Returns the created window for later deletion.

Args:
- prompt: String to be displayed.
*/
WINDOW* createPrompt(std::string prompt);


/* Ready Screen function
Draws the timer until the round start and the current score. Returns when the
timer has depleted.

Args:
- round: The current round number
- score: The score to display
*/
void readyScreen(int round, int score);


/* Gameplay Screen function
Draws the timer, score, message and input windows, processes the user input, and
updates the timer accordingly. Returns the string typed by the user when enter
is pressed, or the partial string within the buffer if the timer runs out.

Args:
- t: The timer object to be updated
- score: The score to display
- message: The message to display
*/
std::string gameplayScreen(Timer& t, int score, const std::string& message);


/* Results Screen function
Placeholder for results screen with leaderboards, initial input, and play again.
*/
void resultsScreen(int& score);

#endif
