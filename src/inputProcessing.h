#ifndef _INPUTPROCESSING_H_
#define _INPUTPROCESSING_H_
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


// --------------- //
// General Classes //
// --------------- //

/* Timer class
Stores all the needed information for updating and verifying the user input
timer. Initialized with the starting value of the timer and the start time. Note
that the drawing function right aligns and assumes the value can be expressed in
three decimal digits.
*/
class Timer {
private:
    int timerVal; // The current value
    int max; // The maximum possible value
    time_t startTime; // The time at initialization

public:
    // Constructor
    Timer(int startVal, time_t startTime) : timerVal(startVal), max(startVal),
                                            startTime(startTime) {}

    // Draws the timer
    void draw(WINDOW* win);

    // Verifies the timer and redraws it if it was updated
    void update(WINDOW* win);

    // Returns false if the timer is less than zero
    bool verify();
};


// -------------------------- //
// Menu Functions and Classes //
// -------------------------- //

/* Choices class
Based on the string vector passed in the constructor, each string's drawing
position is calculated and stored. The currently selected choice can be updated
using the various 'select' methods, and drawn using drawSelect. All of the
choices can also be drawn at once using drawAll.
*/
class Choices {
private:
    /* Calculate Position function
    Based on the strings lengths and the total number of strings, this function
    calculates the x drawing position such that each string is centered over an
    equal division of the terminal's width. Results are stored in the pos
    member, with their index matching that of the string. */
    void calcPos();

    /* Positive Modulo function
    Source: https://stackoverflow.com/a/14997413
    Returns abs(a % b). */
    int posMod(int a, int b);

    int size; // Number of choices
    std::vector<std::string> str; // Vector of choice strings
    std::vector<int> pos; // Vector of draw positions
    int oldSelection = 0; // Previously selected choice
    int selection = 0; // Currently selected choice

public:
    // Constructor
    Choices(std::vector<std::string> strings);

    int getSelect();

    // Sets the selection equal to 'i', with wrap-around.
    void select(int i);

    // Increments the selection by 'i', with wrap-around.
    void selectUp(int i = 1);

    // Decrements the selection by 'i', with wrap-around.
    void selectDown(int i = 1);

    /* Draws All Choices function
    Draws the choices in the passed window based on the calculated pos values.
    Assumes the window is the width of the terminal.
    */
    void drawAll(WINDOW* win);

    /* Draws Selected Choice function
    Draws the selected choice with highlighting to the passed window. First
    redraws the previously selected choice to remove the highlighting and then
    redraws the current choice with highlighting.
    */
    void drawSelect(WINDOW* win);
};


/* Process Menu function
Given the appropriate window and a choices object, handles all the user input
for selecting an option. Supports left and right arrow keys or 'a' and 'd' for
lateral movement, or numbers 1-9 for quick selection, with 'Enter' for
confirmation. Returns a index value corresponding to the chosen option.
*/
int processMenu(WINDOW* cWin, Choices c) ;


// ------------------------------------ //
// Keyboard Input Functions and Classes //
// ------------------------------------ //

/* Buffer class
Complimentary class to processKeyboard which stores the string being typed, the
maximum size of the string (passed in the constructor) and the location of the
cursor. Contains all the methods needed by processKeyboard to allow the
insertion and deletion of characters and the movement of the cursor.
*/
class Buffer {
private:
    std::string str; // The "buffer" in which characters are stored
    unsigned int maxSize; // Maximum size of the string
    unsigned int index = 0; // The cursor position, an index to the next char

    // Redraws the buffer to the passed window
    void redrawBuffer(WINDOW* win);

public:
    // Constructor
    Buffer(unsigned int maxSize);

    std::string getBuffer();

    void redrawCursor(WINDOW* win);

    // Inserts the character at the cursor
    void insert(WINDOW* win, char c);

    // Removes the character behind the cursor
    void backspace(WINDOW* win);

    // Removes the character at the cursor
    void del(WINDOW* win);

    // Moves the cursor up by one
    void indexInc(WINDOW* win);

    // Moves the cursor down by one
    void indexDec(WINDOW* win);

    // Sets the cursor to the beginning of the line
    void indexBegin(WINDOW* win);

    // Sets the cursor to the end of the line
    void indexEnd(WINDOW* win);
};


/* Process Keyboard function
Waits for user input and takes appropriate action, updating the passed window
and buffer. Returns true if enter was pressed, returns false otherwise.

Args:
- iWin: The input window to update
- b: The buffer to update
*/
bool processKeyboard(WINDOW* iWin, Buffer& b);

#endif
