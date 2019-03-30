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

#include "levenshtein-distance.h"
#include "soundex.h"

#include <iostream>  // for debugging
using namespace std;



cpu::cpu(int c, int o) {
    // Set the selected "player" as the selected list of names
    this->nameList = c;
    // Set the selected "opponent" as the chosen phonetic algorithm
    this->opponent = o;

    random_shuffle(this->names.begin(), this->names.end());  // array, array+SIZE
    this->index = 0;
}

void cpu::nextName() {
    this->index++;
}

string cpu::displayName() {
    if (this->index < this->names.size()) {
        return this->names[this->index];
    }
    else {
        return "EOL";
    }
}

int cpu::getScore() {
    return this->score;
}

void cpu::processInput(string input) {
    string desired = soundex(this->names[this->index]);
    string given = soundex(input);
    if (desired == given) {
        calculateScore(input);
    }
    else {
        this->score = -1;
    }
}

void cpu::calculateScore(string A) {
    this->score = 1.5 * dynamicDL(this->names[this->index], A);
}

int main() {
    cpu foo(0, 0);
    cout << foo.displayName() << endl;
    string s;
    cin >> s;
    foo.processInput(s);
    cout << foo.getScore() << endl;
}
