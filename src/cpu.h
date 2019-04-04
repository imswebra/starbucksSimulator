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
private:
    std::string currentName;
    unsigned int index;
    int nameList;
    int opponent;
    int score = 0;
    std::vector<std::string> names;


    /* Calculate Score function
    Only called when the phonetics of the current name and the input string are the
    same.
    Calculates the score as a Damerau Levenshtein distance and sets it to
    this->score.
    */
    void calculateScore(std::string input);

    void makeNames(std::string filename);

    /* Clean Input function
    Removes the spaces, hyphens and apostrophes from the passed string. */
    void cleanInput(std::string& input);


public:
    // Constructor
    Cpu(int c, int o);

    /* Next Name function
    Checks if reached end of list, if not then it sets currentName to the next name
    on the list
    */
    void nextName();

    /* Process Input function
    Given an input as a string, checks using the chosen phonetic algorithm whether
    it matches with the phonetics of the given/current name.
    If the given string matches with the phonetics, then a score is calculated.
    */
    void processInput(std::string input);

    /* Get Score function
    Retrieves the calculated score, if no score has been calculated score = 0
    */
    int getScore();

    /* Display Name function
    Returns the current name as a std::string
    */
    std::string displayName();
};


#endif
