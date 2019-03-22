/*
Author: Eric Claerhout, Henry Lin
Student ID: 1532360, 1580649
CMPUT 275 Winter 2019

Final Project: Starbucks Simulator
#########################################
*/
#include "levenshtein-distance.h"
#include <iostream>
#include <string>
#include <algorithm>  // for min()

using namespace std;

// Optimal String Alignment Distance calculation
// Based off pseudocode found here:
// https://en.wikipedia.org/wiki/Damerau%E2%80%93Levenshtein_distance
unsigned int levenshtein(string A, string B) {
    bool cost = 0;  // cost will only be 0 or 1
    unsigned int distance[A.length() + 2][B.length() + 2];

    for(unsigned int i = 0; i <= A.length() + 1; i++) {
        distance[i][0] = i;
    }
    for(unsigned int j = 0; j <= B.length() + 1; j++) {
        distance[0][j] = j;
    }

    for(unsigned int i = 1; i <= A.length() + 1; i++) {
        for(unsigned int j = 1; j <= B.length() + 1; j++) {
            if(A[i] == B[j]) {
                cost = 0;
            }
            else{
                cost = 1;
            }
            distance[i][j] = min(distance[i - 1][j] + 1,  // deletion
                                min(distance[i][j - 1] + 1,  // insertion
                                        distance[i-1][j-1] + cost));  // substitution
            if(i > 1 && j > 1 && A[i] == B[j-1] && A[i-1] == B[j]) {
                distance[i][j] = min(distance[i][j],
                                    distance[i-2][j-2] + cost); // transposition
            }
        }
    }
    return distance[A.length() + 1][B.length() + 1];
}

int main() {
    string s1 = "Damerau";
    string s2 = "Levenshtein";
    cout << levenshtein(s1, s2) << endl;
    return 0;
}
