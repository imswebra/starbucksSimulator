#ifndef _NYSIIS_H_
#define _NYSIIS_H_
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

/* NYSIIS function
Returns the New York State Identification and Intelligence System encoding of
the given string. Based off the Wikipedia pseudocode. Has a best case complexity
of O(n) and a worse case complexity of O(n^2).
*/
std::string nysiis(std::string name);

#endif
