#ifndef _PREPROCESS_H_
#define _PREPROCESS_H_
/*
Author: Eric Claerhout, Henry Lin
Student ID: 1532360, 1580649
CMPUT 275 Winter 2019

Final Project: Starbucks Simulator
#########################################
*/

#include <string>

void makeUppercase(std::string& str);

// https://stackoverflow.com/a/5891643
// doesn't remove first letter
void removeChars(std::string& str, const std::string& chars);

// https://stackoverflow.com/a/27663803
// removes sequential duplicates, leaving only one
void removeDuplicates(std::string& str);

void resizeWithZeros(std::string& str, int desiredLength);

#endif
