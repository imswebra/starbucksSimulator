#ifndef _LEVENSHTEIN_DISTANCE_
#define _LEVENSHTEIN_DISTANCE_
/*
Author: Eric Claerhout, Henry Lin
Student ID: 1532360, 1580649
CMPUT 275 Winter 2019

Final Project: Starbucks Simulator
#########################################
*/

// -------- //
// Includes //
// -------- //
#include <string>

// --------- //
// Functions //
// --------- //

/* Damerau Levenshtein Distance function
Strings need to be all uppercase
Can only contain characters from the 26 letter alphabet
Based off pseudocode found here:
https://en.wikipedia.org/wiki/Damerau%E2%80%93Levenshtein_distance

Given two strings, it will create a 2-dimensional array of size m+2 by n+2,
where m is the length of string 1 and n is the length of string 2. Then
calculates edit distances for each position in the array by finding the minimum
value for addition, deletion, substitution, and transposition for the current
index. By solving the individual values for each index of the array the total
edit distance can be calculated through the values of the found sub-indexes.

Args:
- A: The first string to compare edit distances
- B: The second string used to compare with A

Returns:
c: The integer edit distance, the value of the very last index in the distances
   array.
*/
int dynamicDL(std::string& A, std::string& B);

#endif
