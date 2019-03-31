#include <string>
#include <algorithm>

using namespace std;

void makeUppercase(string& str) {
    for (auto & c: str) c = toupper(c);
}

// https://stackoverflow.com/a/5891643
// doesn't remove first letter
void removeChars(string& str, const string& chars) {
    for (unsigned int i = 0; i < chars.length(); ++i) {
       str.erase(remove(str.begin() + 1, str.end(), chars.at(i)), str.end());
    }
}

// https://stackoverflow.com/a/27663803
// removes sequential duplicates, leaving only one
void removeDuplicates(string& str) {
    str.erase(unique(str.begin(), str.end()), str.end());
}


void resizeWithZeros(string& str, int desiredLength) {
    str.resize(desiredLength, '0');
}
