#ifndef _PREPROCESS_H_
#define _PREPROCESS_H_

#include <string>
#include <algorithm>

using namespace std;

void makeUppercase(string& str);

// https://stackoverflow.com/a/5891643
// doesn't remove first letter
void removeChars(string& str, const string& chars);

// https://stackoverflow.com/a/27663803
// removes sequential duplicates, leaving only one
void removeDuplicates(string& str);

void resizeWithZeros(string& str, int desiredLength);

#endif
