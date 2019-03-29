#ifndef _UI_H_
#define _UI_H_
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
#include <string>
#include <vector>

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


/* Gameplay Screen function
Draws the gameplay screen and processes user input to allow typing in a name.
Returns the string typed by the user.

Args:
- name: The prompt name displayed at the top of the screen
*/
std::string gameplayScreen(std::string name);

#endif
