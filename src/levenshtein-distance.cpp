/*
Author: Eric Claerhout, Henry Lin
Student ID: 1532360, 1580649
CMPUT 275 Winter 2019

Final Project: Starbucks Simulator
#########################################
*/
#include "levenshtein-distance.h"

#include <string>
#include <algorithm>  // for min()
#include <cstring>  // for memset()

#include "preprocess.h"

using namespace std;

// Size 26 means that no accented characters are supported
#define alphabetSize 26  // Supported alphabet size


// Damerau-Levenshtein distance using dynamic programming
// Strings need to be all uppercase
// Can only contain characters from the 26 letter alphabet
// Based off pseudocode found here:
// https://en.wikipedia.org/wiki/Damerau%E2%80%93Levenshtein_distance
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
    memset(da, 0, sizeof(da));

    // Allocate memory for distance table:
    // https://stackoverflow.com/questions/9219712/c-array-expression-must-have-a-constant-value
    int maxdistance = aSize + bSize;
    int** distances = new int*[aSize + 2];
    for (int i = 0; i <= aSize + 2; i++) {
        distances[i] = new int[bSize + 2];
    }

    // Initialize the distances table
    distances[0][0] = maxdistance;
    for (int i = 1; i <= aSize + 1; i++) {
        distances[i][0] = maxdistance;
        distances[i][1] = i - 1;
    }
    for (int j = 1; j <= bSize + 1; j++) {
        distances[0][j] = maxdistance;
        distances[1][j] = j - 1;
    }

    // Create all distances given the operations on the distances table
    for (int i = 2; i <= aSize + 2; i++) {
        db = 1;
        for (int j = 2; j < bSize + 2; j++) {
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
    int c = distances[aSize + 1][bSize + 1];

    // Free the memory to prevent leaks

    for (int i = 0; i <= aSize + 2; i++) {
        //delete[] distances[i];
        distances[i] = NULL;
    }
    distances = NULL;
    free(distances);
    // FIXME freeing memory from heap results in double free vulnerability


    return c;
}
