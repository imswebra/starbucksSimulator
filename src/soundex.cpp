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

#include "soundex.h"

#include <string>
#include <algorithm> // remove, replace, unique
#include <iostream>

using namespace std;


// --------- //
// Functions //
// --------- //

void makeUppercase(string& str) {
    for (auto & c: str) c = toupper(c);
}

// https://stackoverflow.com/a/5891643
// doesn't remove first letter
void removeChars(string& str, const string& chars) {
    for (unsigned int i = 0; i < chars.length(); ++i) {
       str.erase(remove(str.begin() + 1, str.end(), chars.at(i)), str.end());
    }
}

// https://stackoverflow.com/a/27663803
// removes sequential duplicates, leaving only one
void removeDuplicates(string& str) {
    str.erase(unique(str.begin(), str.end()), str.end());
}


void resizeWithZeros(string& str, int desiredLength) {
    str.resize(desiredLength, '0');
}


string soundex(string name) {
    string code = name;

    makeUppercase(code);
    removeChars(code, "HW");
    // Replace vowels with "_" temporarily
    for (auto c: "AEIOUY") replace(code.begin() + 1, code.end(), c, '_');

    // Work on the whole, including the first letter
    for (auto c: "BFPV") replace(code.begin(), code.end(), c, '1');
    for (auto c: "CGJKQSXZ") replace(code.begin(), code.end(), c, '2');
    for (auto c: "DT") replace(code.begin(), code.end(), c, '3');
    for (auto c: "MN") replace(code.begin(), code.end(), c, '5');
    replace(code.begin(), code.end(), 'L', '4');
    replace(code.begin(), code.end(), 'R', '6');

    removeDuplicates(code);
    removeChars(code, "_");

    code[0] = name[0];

    resizeWithZeros(code, 4);

    return code;
}


int main() {
    while (true) {
        string input;
        cin >> input;
        cout << soundex(input) << endl;
    }
    return 0;
}
