#ifndef STRINGUTILITIES_H
#define STRINGUTILITIES_H

#include <string>

// Partial: declarations from StringUtilities.cpp used by recovered TUs.
namespace STRINGS
{
    std::string StringConvertToUTF8(const std::wstring& text);
    std::wstring StringConvertToWide(const std::string& text);
    std::wstring StringConvertToWide(const char* text, unsigned int maxLength);
    std::string StringUpper(const std::string& text);
    std::wstring StringUpper(const std::wstring& text);
    std::string GetValueAsString(int value);
    std::string GetValueAsString(unsigned int value);
}

#endif
