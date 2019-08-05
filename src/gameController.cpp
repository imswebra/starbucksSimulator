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
#include "gameController.h"

#include <string>
#include <algorithm>  // for random_shuffle
#include <vector>
#include <random>
#include <fstream>
#include <ctime>

#include "algs/levenshtein-distance.h"
#include "algs/soundex.h"
#include "algs/nysiis.h"
#include "algs/metaphone.h"

#include <iostream>  // for debugging

using namespace std;

// ------------- //
// Class Methods //
// ------------- //

// Private methods

/* Calculate Score function
Only called when the phonetics of the current name and the input string are the
same.
Calculates the score as a Damerau Levenshtein distance and sets it to
this->score.

Args:
- A: The valid user inputted string.
*/
void Cpu::calculateScore(string A) {
    this->score = dynamicDL(this->currentName, A);
}


/* Make Names function
Opens the given filename and adds 5 random lines of names to the names vector

Args:
- filename: The file path to open
*/
void Cpu::makeNames(string filename) {
    // Initial declarations
    srand (time(NULL));  // the generator seed
    ifstream inputFile(filename);
    string readLine;
    int lineNum = 0;
    int random;

    // Get 5 strings
    for (int i = 0; i < 5; i++) {
        random = rand() % 100 + 1;  // between 1 - 100
        while (lineNum < 100) {
            getline(inputFile, readLine);
            if (random == lineNum) {
                this->names.push_back(readLine);
                break;
            }
            lineNum++;
        }
        inputFile.clear();
        inputFile.seekg(0, ios_base::beg);  // set the stream back to start of file
        lineNum = 0;
    }
    // Remember to close the ifstream
    inputFile.close();
}


/* Clean Input function
Removes the spaces, hyphens and apostrophes from the passed string.

Args:
- input: The unformatted user input as a string
*/
void Cpu::cleanInput(string& input) {
    input.erase(remove(input.begin(), input.end(), ' '), input.end());
    input.erase(remove(input.begin(), input.end(), '-'), input.end());
    input.erase(remove(input.begin(), input.end(), '\''), input.end());
}


// Public methods

/* Constructor
Args:
- c: The integer value (0 - 2) for which name list to read.
- o: The integer value (0 - 2) for which phonetic algorithm to use.
*/
Cpu::Cpu(int c, int o) : nameList(c), opponent(o) {
    // Construct the name list
    switch (this->nameList) {
        case 0:
            makeNames("data/1880s.csv");
            break;
        case 1:
            makeNames("data/1950s.csv");
            break;
        case 2:
            makeNames("data/2000s.csv");
            break;
    }
    // Get the first name on the shuffled list
    this->index = 0;
    this->currentName = this->names[0];
}


/* Next Name function
Checks if reached end of list, if not then it sets currentName to the next name
on the list
*/
void Cpu::nextName() {
    if(index < this->names.size()){
        this->index++;
        this->currentName = this->names[this->index];
    }
    else {
        this->currentName = "End of names";
    }
}


/* Display Name function
Returns the current name as a std::string
*/
string Cpu::displayName() {
    return this->currentName;
}


/* Get Score function
Retrieves the calculated score, if no score has been calculated score = 0
*/
int Cpu::getScore() {
    return this->score;
}


/* Process Input function
Given an input as a string, checks using the chosen phonetic algorithm whether
it matches with the phonetics of the given/current name.
If the given string matches with the phonetics, then a score is calculated.

Args:
- input: The string that the user has inputted
*/
void Cpu::processInput(string input) {
    string desired, given;
    cleanInput(input);

    switch(this->opponent) {
        case 0:
            desired = soundex(this->currentName);
            given = soundex(input);
            break;
        case 1:
            desired = nysiis(this->currentName);
            given = nysiis(input);
            break;
        case 2:
            desired = metaphone(this->currentName);
            given = metaphone(input);
            break;
    }
    // debug flag
    if(dFlag) {
        char trash;
        cout << desired << " " << given << endl;
        // VERY LOW LEVEL WAIT COMMAND
        cin >> trash;
    }
    if (desired == given) {
        calculateScore(input);
    }
    else {
        this->score = 0;
    }
}
