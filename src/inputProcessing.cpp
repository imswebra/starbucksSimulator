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
#include "inputProcessing.h"

#include <ncurses.h>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

// -------------------------- //
// Menu Functions and Classes //
// -------------------------- //

// Choices Class - Private functions

/* Calculate Position function
Based on the strings lengths and the total number of strings, this function
calculates the x drawing position such that each string is centered over an
equal division of the terminal's width. Results are stored in the pos
member, with their index matching that of the string. */
void choices::calcPos() {
    for (int i = 0; i < size; i++) {
        pos.push_back(((COLS * (i + 1)) / (size + 1))
                      - (str[i].size() / 2));
    }
}

/* Positive Modulo function
Source: https://stackoverflow.com/a/14997413
Returns abs(a % b). */
int choices::posMod(int a, int b) { return (a % b + b) % b; }


// Choices Class - Public functions

// Constructor
choices::choices(vector<string> strings) : size(strings.size()), str(strings)  {
    calcPos();
}

int choices::getSelect() { return selection; }

// Sets the selection equal to 'i', with wrap-around.
void choices::select(int i) {
    oldSelection = selection;
    selection = posMod(i, size);
}

// Increments the selection by 'i', with wrap-around.
void choices::selectUp(int i) {
    oldSelection = selection;
    selection = posMod(selection + i, size);
}

// Decrements the selection by 'i', with wrap-around.
void choices::selectDown(int i) {
    oldSelection = selection;
    selection = posMod(selection - i, size);
}

/* Draws All Choices function
Draws the choices in the passed window based on the calculated pos values.
Assumes the window is the width of the terminal.
*/
void choices::drawAll(WINDOW* win) {
    for (int i = 0; i < size; i++) {
        mvwprintw(win, 0, pos[i], str[i].c_str());
    }
    wrefresh(win);
}

/* Draws Selected Choice function
Draws the selected choice with highlighting to the passed window. First
redraws the previously selected choice to remove the highlighting and then
redraws the current choice with highlighting.
*/
void choices::drawSelect(WINDOW* win) {
    mvwprintw(win, 0, pos[oldSelection], str[oldSelection].c_str());
    wattron(win, A_STANDOUT);
    mvwprintw(win, 0, pos[selection], str[selection].c_str());
    wattroff(win, A_STANDOUT);
}


/* Process Menu function
Given the appropriate window and a choices object, handles all the user input
for selecting an option. Supports left and right arrow keys or 'a' and 'd' for
lateral movement, or numbers 1-9 for quick selection, with 'Enter' for
confirmation. Returns a index value corresponding to the chosen option.
*/
int processMenu(WINDOW* cWin, choices c) {
    // Set default selection
    c.select(1);
    c.drawSelect(cWin);

    // Process input
    int key = 0;
    while (key != 10) { // Exit if enter is pressed
        key = wgetch(cWin);
        switch (key) {
            case KEY_RIGHT:
            case 'd':
                c.selectUp();
                break;
            case KEY_LEFT:
            case 'a':
                c.selectDown();
                break;
            case '1' ... '9':
                c.select(key - '0' - 1);
                break;
            default:
                continue;
        }
        c.drawSelect(cWin);
    }
    return c.getSelect();
}


// ------------------------------------ //
// Keyboard Input Functions and Classes //
// ------------------------------------ //

// Buffer Class - Private functions

// Redraws the buffer to the passed window
void buffer::redrawBuffer(WINDOW* win) {
    werase(win);
    mvwprintw(win, 0, (maxSize - str.size() + 1) / 2, str.c_str());
    redrawCursor(win);
};


// Buffer Class - Public functions

// Constructor
buffer::buffer(unsigned int maxSize) : maxSize(maxSize) {}

string buffer::getBuffer() { return str; }

void buffer::redrawCursor(WINDOW* win) {
    wmove(win, 0, index + (maxSize - str.size() + 1) / 2);
}

// Inserts the character at the cursor
void buffer::insert(WINDOW* win, char c) {
    if (str.size() == maxSize) return;
    str.insert(index, string(1, c));
    index++;
    redrawBuffer(win);
}

// Removes the character behind the cursor
void buffer::backspace(WINDOW* win) {
    if (index == 0) return;
    index--;
    str.erase(index, 1);
    redrawBuffer(win);
}

// Removes the character at the cursor
void buffer::del(WINDOW* win) {
    if (index == str.size()) return;
    str.erase(index, 1);
    redrawBuffer(win);
}

// Moves the cursor up by one
void buffer::indexInc(WINDOW* win) {
    if (index == str.size()) return;
    index++;
    redrawCursor(win);
}

// Moves the cursor down by one
void buffer::indexDec(WINDOW* win) {
    if (index == 0) return;
    index--;
    redrawCursor(win);
}

// Sets the cursor to the beginning of the line
void buffer::indexBegin(WINDOW* win) {
    index = 0;
    redrawCursor(win);
}

// Sets the cursor to the end of the line
void buffer::indexEnd(WINDOW* win) {
    index = str.size();
    redrawCursor(win);
}


/* Process Keyboard function
Waits for user input and takes appropriate action, updating the passed window
and buffer. Returns true if enter was pressed, returns false otherwise.

Args:
- iWin: The input window to update
- b: The buffer to update
*/
bool processKeyboard(WINDOW* iWin, buffer& b) {
    int key = wgetch(iWin);
    switch (key) {
        case 10:
            return true;
        case 'A' ... 'Z':
        case 'a' ... 'z':
        case ' ':
        case '-':
            b.insert(iWin, (char) key);
            break;
        case KEY_BACKSPACE:
            b.backspace(iWin);
            break;
        case KEY_DC: // Delete key
            b.del(iWin);
            break;
        case KEY_RIGHT:
            b.indexInc(iWin);
            break;
        case KEY_LEFT:
            b.indexDec(iWin);
            break;
        case 545: // Ctrl + left arrow
        case KEY_HOME:
            b.indexBegin(iWin);
            break;
        case 560: // Ctrl + right arrow
        case KEY_END:
            b.indexEnd(iWin);
            break;
    }
    return false;
}
