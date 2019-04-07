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
#include "levenshtein-distance.h"

#include <string>
#include <algorithm>  // for min()
#include <cstring>  // for memset()

#include "../preprocess.h"

// Size 26 means that no accented characters are supported
#define alphabetSize 26  // Supported alphabet size

using namespace std;

// --------- //
// Functions //
// --------- //

/* Damerau Levenshtein Distance function
Strings need to be all uppercase
Can only contain characters from the 26 letter alphabet
Based off pseudocode found here:
https://en.wikipedia.org/wiki/Damerau%E2%80%93Levenshtein_distance

Given two strings, it will create a 2-dimensional array of size m+2 by n+2,
where m is the length of string 1 and n is the length of string 2. Then
calculates edit distances for each position in the array by finding the minimum
value for addition, deletion, substitution, and transposition for the current
index. By solving the individual values for each index of the array the total
edit distance can be calculated through the values of the found sub-indexes.

Args:
- A: The first string to compare edit distances
- B: The second string used to compare with A

Returns:
c: The integer edit distance, the value of the very last index in the distances
   array.
*/
int dynamicDL(string& A, string& B) {
    // Strings need to be uppercase for dynamic programming comparison
    makeUppercase(A);
    makeUppercase(B);
    int aSize = A.length();
    int bSize = B.length();

    bool cost = 0;  // cost will only ever be 0 or 1
    int k, db;
    int l;

    // Create the language size table
    unsigned int da[alphabetSize];
    for(int i = 0; i < alphabetSize; i++) {
        da[i] = 0;
    }

    // Allocate memory for distance table:
    // https://stackoverflow.com/questions/9219712/c-array-expression-must-have-a-constant-value
    int maxdistance = aSize + bSize;
    int** distances = new int*[aSize + 2];
    for (int i = 0; i < aSize + 2; i++) {
        distances[i] = new int[bSize + 2];
    }

    // Initialize the distances table
    distances[0][0] = maxdistance;
    for (int i = 1; i < aSize + 2; i++) {
        distances[i][0] = maxdistance;
        distances[i][1] = i - 1;
    }
    for (int j = 1; j < bSize + 2; j++) {
        distances[0][j] = maxdistance;
        distances[1][j] = j - 1;
    }

    // Create all distances given the operations on the distances table
    for (int i = 2; i < aSize + 2; i++) {
        db = 1;
        for (int j = 2; j < bSize + 2; j++) {
            k = da[B[j-2] - 65] + 1;
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
        da[A[i-2] - 65] = i;
    }

    // The final distance is the last index in the 2-d array
    int c = distances[aSize + 1][bSize + 1];

    // Free the memory to prevent leaks

    for (int i = 0; i < aSize + 2; i++) {
        delete[] distances[i];
        distances[i] = NULL;
    }
    delete[] distances;
    distances = NULL;


    return c;
}
