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


class Cpu {
public:
    Cpu(int c, int o);

    void nextName();

    void processInput(std::string input);

    int getScore();

    std::string displayName();

private:

    std::string currentName;
    unsigned int index;
    int opponent;
    int nameList;
    int score;


    void calculateScore(std::string input);

    std::vector<std::string> names = {  // Placeholder before being able to obtain names from CSV
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
