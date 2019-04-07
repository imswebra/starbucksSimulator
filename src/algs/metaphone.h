#ifndef _METAPHONE_H_
#define _METAPHONE_H_

// -------- //
// Includes //
// -------- //
#include <string>

// --------- //
// Functions //
// --------- //

/* Metaphone Caller function
Given string s, calls the phonetic function to generate the phonetic string,
then quickly cleans up the outputted phonetic string to avoid errors from
deprecated C conversion.

Args:
- s: The string to be converted to phonetic version

Returns:
metaphone: The cleaned phonetic version of the given string s.
*/
std::string metaphone(std::string s);

#endif
