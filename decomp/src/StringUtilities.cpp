#include <cstdlib>
#include <cwchar>
#include <cstring>
#include "StringUtilities.h"
#include "EmptyStrings.h"
#include "GameVariables.h"
#include "GameNamespaces.h"
#include "StringUtilities.h"

long long STRINGS::firstXCharactersMatch(const wchar_t *text, unsigned int length,
                                        const wchar_t *other, unsigned int otherLength)
{
    if (length < otherLength)
        return 0;

    for (unsigned int i = 0; i < otherLength; ++i)
        if (text[i] != other[i])
            return 0;

    return 1;
}

unsigned int STRINGS::StringCopyWCharArray(wchar_t* destination,
                                            unsigned int maxLength,
                                            const wchar_t* source)
{
    if (source != 0 && destination != 0)
    {
        unsigned int length = 0;
        unsigned int remaining = 10000;

        while (source[length] != L'\0' && remaining != 0)
        {
            ++length;
            --remaining;
        }

        ++length;
        if (length <= maxLength)
        {
            for (unsigned int i = 0; i < length; ++i)
                destination[i] = source[i];

            return length;
        }
    }

    return 0;
}

long long STRINGS::StringIsLower(const std::wstring& text)
{
    for (unsigned int i = 0; i < text.size(); ++i)
        if (tolower(text[i]) != text[i])
            return 0;
    return 1;
}

long long STRINGS::StringIsLower(const std::string& text)
{
    for (unsigned int i = 0; i < text.length(); ++i)
    {
        char c = text[i];
        if (tolower(c) != c)
            return 0;
    }
    return 1;
}

namespace STRINGS
{
    long long StringIsUpper(const std::wstring& text)
    {
        for (unsigned int i = 0; i < text.length(); ++i)
        {
            if (text[i] != toupper(text[i]))
                return 0;
        }
        return 1;
    }
}

long long STRINGS::StringIsUpper(const std::string& text)
{
    for (unsigned int i = 0; i < text.length(); ++i)
    {
        if (toupper(text[i]) != text[i])
            return 0;
    }

    return 1;
}

namespace STRINGS
{
    std::string GetValueAsString(bool value)
    {
        if (value)
            return std::string("true");
        else
            return std::string("false");
    }
}

void* STRINGS::StringConvertUTF8ToWide(const std::string& text)
{
    extern void UTF8ToUTF32(const std::string&);
    UTF8ToUTF32(text);
    return const_cast<std::string*>(&text);
}

extern std::string UTF32ToUTF8(const std::wstring&);

std::string STRINGS::StringConvertToUTF8(const std::wstring& text)
{
    return UTF32ToUTF8(text);
}

int STRINGS::GetBool(const std::wstring& text)
{
    if (text.compare(L"") == 0)
        return 0;

    const unsigned int value = static_cast<unsigned int>(text[0]);

    if (value == static_cast<unsigned int>(L'F'))
        return 0;

    if (value == static_cast<unsigned int>(L'f'))
        return 0;

    int result;
    __asm__("cmp $0x30, %1\n\t"
            "setne %b0"
            : "=a"(result)
            : "r"(value)
            : "cc");

    return result;
}

bool STRINGS::GetBool(const std::string& text)
{
    return text != "" && text[0] != 'F' && text[0] != 'f' && text[0] != '0';
}

long STRINGS::GetInt64(const std::string& text)
{
    return strtod(text.c_str(), 0);
}

void STRINGS::GetFloat64(const std::string& text)
{
    strtod(text.c_str(), 0);
}

long long STRINGS::GetInt64(const std::wstring& text)
{
    long long result;
    swscanf(text.c_str(), L"%lld", &result);
    return result;
}

namespace STRINGS
{
    int GetInt(const std::wstring& text)
    {
        wchar_t* end = 0;
        return wcstol(text.c_str(), &end, 0);
    }
}

namespace STRINGS
{
    int GetInt(const std::string& text)
    {
        return static_cast<int>(strtol(text.c_str(), 0, 10));
    }
}

void STRINGS::GetFloat64(const std::wstring& text)
{
    wchar_t* end = 0;
    wcstod(text.c_str(), &end);
}

namespace STRINGS
{
    void TokenizeString(std::queue<std::string>* tokens, std::string text, const char* separators, char comment)
    {
        std::string::size_type end = text.find(comment);
        if (end != std::string::npos)
            text = text.erase(end);

        std::string::size_type start = text.find_first_not_of(separators, 0);
        while (start != std::string::npos)
        {
            end = text.find_first_of(separators, start);
            std::string token = text.substr(start, end - start);
            tokens->push(token);
            start = text.find_first_not_of(separators, end);
        }
    }
}

std::wstring STRINGS::StringConvertToWide(const char* text, unsigned int maxLength)
{
    std::string textString(text);
    return StringConvertToWide(textString);
}

void STRINGS::StringConvertToNarrow(const std::wstring& text, std::string& result)
{
    result = std::string(text.begin(), text.end());
}

long long STRINGS::StringCopyWCharArray(wchar_t* output, unsigned int outputSize,
                                        std::string text)
{
    return output != 0 ? StringCopyWCharArray(output, outputSize, text.c_str()) : 0;
}

unsigned int STRINGS::getStringIndex(const std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >& text, const std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >* table, unsigned int count, unsigned int defaultIndex, bool caseSensitive)
{
    if (caseSensitive)
    {
        std::wstring upperText = StringUpper(text);

        for (unsigned int i = 0; i < count; ++i)
        {
            if (upperText == StringUpper(table[i]))
                return i;
        }
    }
    else
    {
        for (unsigned int i = 0; i < count; ++i)
        {
            if (text == table[i])
                return i;
        }
    }

    return defaultIndex;
}


// Imported source candidates; historical status is not fresh acceptance.
unsigned int STRINGS::StringCopyCharArray(char* out, unsigned int capacity, const char* text)
{
    if(!text || !out)return 0;
    memset(out,0,capacity);
    unsigned int length=0,remaining=10000;
    while(text[length] && remaining){++length;--remaining;}
    ++length;
    if(length>capacity)return 0;
    for(unsigned int i=0;i<length;++i)out[i]=text[i];
    return length;
}

std::wstring STRINGS::GetValueAsWString(bool value)
{
    if(value)return std::wstring(L"true");
    return std::wstring(L"false");
}

float STRINGS::GetFloat(const std::string& text)
{
    return static_cast<float>(strtod(text.c_str(),NULL));
}

float STRINGS::GetFloat(const std::wstring& text)
{
    wchar_t* end=NULL;
    return static_cast<float>(wcstod(text.c_str(),&end));
}

std::string STRINGS::replaceString(std::string text, const std::string& find, const std::string& replacement)
{
    std::string::size_type length=find.size();
    std::string::size_type pos;
    while((pos=text.find(find))!=std::string::npos)text.replace(pos,length,replacement);
    return text;
}

std::wstring STRINGS::replaceWString(std::wstring text, const std::wstring& find, const std::wstring& replacement)
{
    std::wstring::size_type length=find.size();
    std::wstring::size_type pos;
    while((pos=text.find(find))!=std::wstring::npos)text.replace(pos,length,replacement);
    return text;
}
