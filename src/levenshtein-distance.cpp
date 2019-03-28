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

// Size 26 means that no accented characters are supported
#define alphabetSize 26  // Supported alphabet size

void makeUppercase(string& str) {
    for (auto & c: str) c = toupper(c);
}

// Optimal String Alignment Distance calculation
// Based off pseudocode found here:
// https://en.wikipedia.org/wiki/Damerau%E2%80%93Levenshtein_distance
int oStringAlignment(string A, string B) {
    bool cost = 0;  // cost will only be 0 or 1
    int distance[A.length() + 2][B.length() + 2];

    for (unsigned int i = 0; i <= A.length(); i++) {
        distance[i][0] = i;
    }
    for (unsigned int j = 0; j <= B.length(); j++) {
        distance[0][j] = j;
    }

    for (unsigned int i = 1; i <= A.length(); i++) {
        for (unsigned int j = 1; j <= B.length(); j++) {
            if (A[i-1] == B[j-1]) {
                cost = 0;
            }
            else {
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
    return distance[A.length()][B.length()];
}

// Damerau-Levenshtein distance using dynamic programming
// Strings need to be all uppercase
// Can only contain characters from the 26 letter alphabet
// Based off pseudocode found here:
// https://en.wikipedia.org/wiki/Damerau%E2%80%93Levenshtein_distance
int dynamicDL(string A, string B) {
    // Strings need to be uppercase for dynamic programming comparison
    makeUppercase(A);
    makeUppercase(B);

    bool cost = 0;  // cost will only ever be 0 or 1
    int k, l, db;

    // Create the language size table
    unsigned int da[alphabetSize];
    for (unsigned int i = 0; i < alphabetSize; i++) {
        da[i] = 0;
    }

    // Initialize the distances table
    int maxdistance = A.length() + B.length();
    unsigned int distances[A.length() + 2][B.length() + 2];
    distances[0][0] = maxdistance;
    for (unsigned int i = 1; i <= A.length() + 1; i++) {
        distances[i][0] = maxdistance;
        distances[i][1] = i - 1;
    }
    for (unsigned int j = 1; j <= B.length() + 1; j++) {
        distances[0][j] = maxdistance;
        distances[1][j] = j - 1;
    }

    // Create all distances given the operations on the distances table
    for (unsigned int i = 2; i <= A.length() + 2; i++) {
        db = 1;
        for (unsigned int j = 2; j < B.length() + 2; j++) {
            k = da[B[j-2] - 64] + 1;
            l = db;
            if (A[i-2] == B[j-2]) {
                cost = 0;
                db = j;
            }
            else {
                cost = 1;
            }
            distances[i][j] = min(distances[i-1][j-1] + cost,  // substitution
                                    min(distances[i][j-1] + 1,  // insertion
                                        min(distances[i-1][j] + 1,  // deletion
                                            distances[k-1][l-1] + (i-1-k) + 1
                                                + (j-1-l))));  // transposition
        }
        da[A[i-2] - 64] = i;
    }

    // The final distance is the last index in the 2-d array
    return distances[A.length() + 1][B.length() + 1];
}
