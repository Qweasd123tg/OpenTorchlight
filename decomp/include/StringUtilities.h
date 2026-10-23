#ifndef STRINGUTILITIES_H
#define STRINGUTILITIES_H

#include <string>
#include <queue>

// Partial: declarations from StringUtilities.cpp used by recovered TUs.
namespace STRINGS
{
    unsigned int GetArrayValueFloat(const std::string& text, float* output, unsigned int count, std::string separators);
    unsigned int GetArrayValueFloat(const std::wstring& text, float* output, unsigned int count, std::wstring separators);
    unsigned int StringSizeOfWCharArray(const wchar_t* text, unsigned int maximum);
    unsigned int StringSizeOfCharArray(const char* text, unsigned int maximum);
    int StringConvertToWide(const std::string& text, wchar_t* output, int capacity);
    std::string StringLower(const std::string& text);
    std::wstring StringLower(const std::wstring& text);
    unsigned int StringCopyWCharArray(wchar_t* output, unsigned int capacity, const char* text);
    double GetFloat64(const std::string& text);
    double GetFloat64(const std::wstring& text);
    long long GetInt64(const std::wstring& text);
    void TokenizeString(std::queue<std::wstring, std::deque<std::wstring, std::allocator<std::wstring> > >* tokens, const std::wstring& text, const wchar_t* separators);
    void TokenizeString(std::queue<std::string, std::deque<std::string, std::allocator<std::string> > >* tokens, const std::string& text, const char* separators);
    std::wstring GetApplicationPath();
    std::string GetValueAsString(double value);
    std::string GetValueAsString(long long value);
    std::wstring GetValueAsWString(long long value);
    std::wstring GetValueAsWString(double value);
    std::wstring GetValueAsWString(float value);
    unsigned int StringCopyWCharArray(wchar_t* destination, unsigned int capacity, const wchar_t* source);
    int GetInt(const std::wstring& text);
    std::string uniqueName(const std::string& prefix);
    std::wstring GetValueAsWString(int value);
    std::wstring GetValueAsWString(unsigned int value);
    std::wstring replaceWString(std::wstring text, const std::wstring& find, const std::wstring& replacement);
    std::wstring StringConvertUTF8ToWide(const std::string& text);
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
