#ifndef _SOUNDEX_H_
#define _SOUNDEX_H_
/*
Author: Eric Claerhout, Henry Lin
Student ID: 1532360, 1580649
CMPUT 275 Winter 2019

Final Project: Starbucks Simulator
#########################################
*/

// ------------------------ //
// Includes and Definitions //
// ------------------------ //
#include <string>


// --------- //
// Functions //
// --------- //

/* Soundex function
Returns the Soundex encoding of the given string. Based off the Wikipedia
pseudocode. Operates in O(n) complexity.
*/
std::string soundex(std::string name);

#endif
