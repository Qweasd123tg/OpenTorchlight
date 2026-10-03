#ifndef EMPTYSTRINGS_H
#define EMPTYSTRINGS_H

#include <string>

// Internal-linkage copies exist in most original TUs (_ZL12EMPTY_STRING,
// _ZL13EMPTY_WSTRING); they are constructed before std::ios_base::Init, so this
// header precedes the OGRE headers that include <iostream>.
const std::string EMPTY_STRING;
const std::wstring EMPTY_WSTRING;

#endif
