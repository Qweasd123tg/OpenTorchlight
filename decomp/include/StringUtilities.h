#ifndef STRINGUTILITIES_H
#define STRINGUTILITIES_H

#include <string>

// Partial: declarations from StringUtilities.cpp used by recovered TUs.
namespace STRINGS
{
    int GetInt(const std::wstring& text);
    std::string uniqueName(const std::string& prefix);
    std::wstring GetValueAsWString(int value);
    std::wstring GetValueAsWString(unsigned int value);
    std::wstring replaceWString(std::wstring text, const std::wstring& find, const std::wstring& replacement);
    std::string StringConvertToUTF8(const std::wstring& text);
    std::wstring StringConvertToWide(const std::string& text);
    std::wstring StringConvertToWide(const char* text, unsigned int maxLength);
    std::string StringConvertToNarrow(const wchar_t* text);
    std::string StringUpper(const std::string& text);
    std::wstring StringUpper(const std::wstring& text);
    std::string GetValueAsString(int value);
    std::string GetValueAsString(unsigned int value);
    std::string GetValueAsString(float value);
    void StringConvertToNarrow(const std::wstring& text, std::string& result);
    // Index of text in table[0..count), or defaultIndex.
    unsigned int getStringIndex(const std::wstring& text, const std::wstring* table, unsigned int count,
                                unsigned int defaultIndex, bool caseSensitive);
}

// Despite its name, this original inline helper trims only line feeds.
inline std::wstring removeWhiteSpace(const std::wstring& text)
{
    std::wstring result=text;
    while (!result.empty() && result[result.size()-1]==L'\n') result=result.substr(0,result.size()-1);
    while (!result.empty() && result[0]==L'\n') result=result.substr(1,result.size()-1);
    return result;
}


// Signatures retained from the supplied pass10 source, verified against the original at import.
namespace STRINGS {
unsigned int StringCopyCharArray(char* out, unsigned int capacity, const char* text);
std::wstring GetValueAsWString(bool value);
float GetFloat(const std::string& text);
float GetFloat(const std::wstring& text);
std::string replaceString(std::string text, const std::string& find, const std::string& replacement);
std::wstring replaceWString(std::wstring text, const std::wstring& find, const std::wstring& replacement);
}

#endif
