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
#include "nysiis.h"

#include <string>
#include <vector>
#include <algorithm>

#include "../preprocess.h"

using namespace std;


// --------- //
// Functions //
// --------- //

/* NYSIIS Replace H function
Handles the 'H' character replacement of the NYSIIS function, replacing it with
the preceding letter if either the preceding or letter is not a vowel.
*/
void nyssiisReplaceH(string& str) {
    // Variable initialization
    string vowels = "AEIOU";
    unsigned int pos = 1;

    // For every found H, if either the follow letter and the preceding letter
    // are not vowels, replace them with the preceding letter
    while ((pos = str.find('H', pos)) != string::npos) {
        if (pos != str.size() - 1 && vowels.find(str[pos + 1]) != string::npos) {
            if (vowels.find(str[pos - 1]) != string::npos) { continue; }
        }
        str.replace(pos, 1, str.substr(pos - 1, 1));
        pos++;
    }
}


/* NYSIIS function
Returns the New York State Identification and Intelligence System encoding of
the given string. Based off the Wikipedia pseudocode. Has a best case complexity
of O(n) and a worse case complexity of O(n^2).
*/
string nysiis(string name) {
    string code = name;
    makeUppercase(code);

    // Beginning replacements
    replaceStrs(code, 0, 3, "MAC", "MCC");
    replaceStrs(code, 0, 2, "KN", "NN");
    replaceStrs(code, 0, 1, "K", "C");
    replaceStrs(code, 0, 2, "PH", "FF");
    replaceStrs(code, 0, 2, "PF", "FF");
    replaceStrs(code, 0, 3, "SCH", "SSS");

    // End replacements
    if (name.size() >= 2) {
        replaceStrs(code, code.size() - 2, code.size(), "EE", "Y_");
        replaceStrs(code, code.size() - 2, code.size(), "IE", "Y_");
        for (auto s: vector<string> {"DT", "RT", "RD", "NT", "ND"}) {
            replaceStrs(code, code.size() - 2, code.size(), s, "D_");
        }
        removeChars(code, "_");
    }

    // Replacements throughout (except for the first letter)
    replaceStrs(code, 1, code.size(), "EV", "AF");
    for (auto c: "EIOU") replace(code.begin() + 1, code.end(), c, 'A');
    replace(code.begin() + 1, code.end(), 'Q', 'G');
    replace(code.begin() + 1, code.end(), 'Z', 'S');
    replace(code.begin() + 1, code.end(), 'M', 'N');
    replaceStrs(code, 1, code.size(), "KN", "NN");
    replace(code.begin() + 1, code.end(), 'K', 'C');
    replaceStrs(code, 1, code.size(), "SCH", "SSS");
    replaceStrs(code, 1, code.size(), "PH", "FF");
    nyssiisReplaceH(code);
    for (auto c: string("AEIOU")) {
        replaceStrs(code, 1, code.size(), string(1, c) + "W", string(2, c));
    }

    // End replacements
    removeDuplicates(code);
    replace(code.end() - 1, code.end(), 'S', '_');
    replaceStrs(code, code.size() - 2, code.size(), "AY", "Y_");
    replace(code.end() - 1, code.end(), 'A', '_');
    removeChars(code, "_");

    return code;
}
