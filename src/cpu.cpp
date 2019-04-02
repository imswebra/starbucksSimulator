/*
Author: Eric Claerhout, Henry Lin
Student ID: 1532360, 1580649
CMPUT 275 Winter 2019

Final Project: Starbucks Simulator
#########################################
*/
#include "cpu.h"

#include <string>
#include <algorithm>  // for random_shuffle
#include <vector>
#include <random>

#include "levenshtein-distance.h"
#include "soundex.h"

#include <iostream>  // for debugging
using namespace std;


// Constructor
Cpu::Cpu(int c, int o) : nameList(c), opponent(o) {
    // Shuffle the current name list
    auto gen = std::default_random_engine {};
    shuffle(this->names.begin(), this->names.end(), gen);  // array, array+SIZE
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
*/
void Cpu::processInput(string input) {
    string desired = soundex(this->currentName);
    string given = soundex(input);
    if (desired == given) {
        calculateScore(input);
    }
}

/* Calculate Score function
Only called when the phonetics of the current name and the input string are the
same.
Calculates the score as a Damerau Levenshtein distance and sets it to
this->score.
*/
void Cpu::calculateScore(string A) {
    this->score = dynamicDL(this->currentName, A);
}
