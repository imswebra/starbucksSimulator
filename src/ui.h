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
#include <ncurses.h>
#include <string>
#include <vector>
#include <ctime>


// ------- //
// Classes //
// ------- //

/* Timer class
Stores all the needed information for updating and verifying the user input
timer. Initialized with the starting value of the timer and the start time.
*/
class timer {
private:
    int timerVal; // The current value
    int max; // The maximum possible value
    time_t startTime; // The time at initialization

public:
    // Constructor
    timer(int startVal, time_t startTime) : timerVal(startVal), max(startVal),
                                            startTime(startTime) {}

    // Draws the timer
    void draw(WINDOW* win);

    // Verifies the timer and redraws it if it was updated
    void update(WINDOW* win);

    // Returns false if the timer is less than zero
    bool verify();
};


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


/* Gameplay Screen function
Draws the timer and input windows, processes the user input, and updates the
timer accordingly. Returns the string typed by the user when enter is pressed,
or the partial string within the buffer if the timer runs out.

Args:
- t: The timer object to be updated
*/
std::string gameplayScreen(timer& t);

#endif
