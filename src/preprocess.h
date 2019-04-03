#ifndef _PREPROCESS_H_
#define _PREPROCESS_H_
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

/* Replace Strings function
Replaces all occurrences of oldVal in str between start and end with newVal.
Complimentary to algorithm's 'replace' but supporting strings instead of single
characters. The former should be used whenever possible as this function has a
worst case O(n^2) complexity and 'replace' has a O(n) complexity.

Args:
- str: The string to modify
- start: The starting index to search for the oldVal string. No part of str
         before this index will be modified.
- end: The ending index to search for the oldVal string. No part of str at or
       after this index will be modified.
- oldVal: The substring to be replaced by newVal in str. Must be the same length
          as newVal.
- newVal: The substring to replaced oldVal by in str. Must be the same length as
          oldVal.
*/
void replaceStrs(std::string& str, unsigned int start, unsigned int end,
                          const std::string& oldVal, const std::string& newVal);


/* Remove Characters function
Removes all occurrences of the characters in the chars string from the passed
str string, though always preserves the first letter.
Based on https://stackoverflow.com/a/5891643

Args:
- str: String to remove characters from
- chars: A string containing all the characters to remove
*/
void removeChars(std::string& str, const std::string& chars);


/* Remove Duplicates function
Removes all sequential duplicates found in the passed string, leaving a single
character of the matching sequence.
Based on https://stackoverflow.com/a/27663803
*/
void removeDuplicates(std::string& str);


/* Make Uppercase function
Modifies the passed string to make all of its letters uppercase.
*/
void makeUppercase(std::string& str);

#endif
