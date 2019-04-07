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
#include <algorithm> // remove, replace, unique, search

using namespace std;


// --------- //
// Functions //
// --------- //

/* Some notes on complexity:
<algorithm>'s remove, replace, unique, search:
Linear with respect to the distance within the searchbounds

<string>'s replace - Up to linear with respect to the new string's length
<string>'s find - Up to linear with respect to the distance within the search
                  bounds
<string>'s erase - Linear with respect to the distance within the search bounds

replaceStrs - Worst case quadratic with respect to str's length
removeChars - O(mn) with respect to the string's length and the number of chars
removeDuplicates - Linear with respect to the string's length
makeUppercase - Linear with respect the string's length
*/


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
void replaceStrs(string& str, unsigned int start, unsigned int end,
                    const string& oldVal, const string& newVal) {
    // Return if sizes aren't valid
    if (oldVal.size() != newVal.size()) return;
    if (oldVal.size() > str.size()) return;

    size_t pos = str.find(oldVal, start);
    while (pos != string::npos && pos <= end - oldVal.size()) {
        str.replace(pos, oldVal.size(), newVal);
        pos += oldVal.size();
        pos = str.find(oldVal, pos);
    }
}


/* Remove Characters function
Removes all occurrences of the characters in the chars string from the passed
str string, though always preserves the first letter.
Based on https://stackoverflow.com/a/5891643

Args:
- str: String to remove characters from
- chars: A string containing all the characters to remove
*/
void removeChars(string& str, const string& chars) {
    for (unsigned int i = 0; i < chars.length(); ++i) {
       str.erase(remove(str.begin() + 1, str.end(), chars.at(i)), str.end());
    }
}


/* Remove Duplicates function
Removes all sequential duplicates found in the passed string, leaving a single
character of the matching sequence.
Based on https://stackoverflow.com/a/27663803
*/
void removeDuplicates(string& str) {
    str.erase(unique(str.begin(), str.end()), str.end());
}


/* Make Uppercase function
Modifies the passed string to make all of its letters uppercase.
*/
void makeUppercase(string& str) {
    for (auto & c: str) c = toupper(c);
}
