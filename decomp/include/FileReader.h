#ifndef FILE_READER_H
#define FILE_READER_H

#include <cstdio>
#include <queue>
#include <string>

class CFileReader
{
public:
    CFileReader();
    ~CFileReader();
    wchar_t* GetBuffer();
    wchar_t& ReadWChar();
    void ResetFile();
    bool EndOfFile();
    std::wstring ReadLine(wchar_t ignore = 0);
    void ReadLineTokenize(std::queue<std::wstring>* tokens, const wchar_t* separators, wchar_t comment);
    bool ReadFile(FILE* file);
    bool ReadFile(const std::wstring& filename);
    bool ConvertFileToUnicode(FILE* file, const std::wstring& filename);
private:
    std::wstring m_sFilename;
    wchar_t* m_pBuffer;
    unsigned int m_iLength;
    unsigned int m_iPosition;
    unsigned int m_iCharacterSize;
};
#endif
