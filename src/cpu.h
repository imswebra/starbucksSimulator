#ifndef _CPU_H_
#define _CPU_H_
/*
Author: Eric Claerhout, Henry Lin
Student ID: 1532360, 1580649
CMPUT 275 Winter 2019

Final Project: Starbucks Simulator
#########################################
*/
#include <string>
#include <vector>

using namespace std;

class cpu {
public:
    cpu (int c, int o);

    string currentName;

    void nextName();

    void processInput(string input);

    int getScore();

    string displayName();

private:

    unsigned int index;
    int opponent;
    int nameList;
    int score;

    void calculateScore(string input);

    vector<string> names = {  // Placeholder before being able to obtain names from CSV
        "Henry",
        "Joseph",
        "Erica",
        "Mark",
        "Stephen",
        "Geoff",
        "Jocelyn",
        "Kaitlyn",
    };
};

#endif
