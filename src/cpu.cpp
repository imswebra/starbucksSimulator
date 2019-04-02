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



Cpu::Cpu(int c, int o) {
    // Set the selected "player" as the selected list of names
    this->nameList = c;
    // Set the selected "opponent" as the chosen phonetic algorithm
    this->opponent = o;

    this->score = 0;

    auto gen = std::default_random_engine {};
    shuffle(this->names.begin(), this->names.end(), gen);  // array, array+SIZE
    this->index = 0;
    this->currentName = this->names[0];
}

void Cpu::nextName() {
    if(index < this->names.size()){
        this->index++;
        this->currentName = this->names[this->index];
    }
    else {
        this->currentName = "End of names";
    }
}

string Cpu::displayName() {
    return this->currentName;
}

int Cpu::getScore() {
    return this->score;
}

void Cpu::processInput(string input) {
    string desired = soundex(this->currentName);
    string given = soundex(input);
    if (desired == given) {
        calculateScore(input);
    }
}

void Cpu::calculateScore(string A) {
    this->score = dynamicDL(this->currentName, A);
}
