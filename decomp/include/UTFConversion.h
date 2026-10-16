#ifndef UTFCONVERSION_H
#define UTFCONVERSION_H

#include <string>
#include <cstdio>

// Partial: wchar_t (UTF-32) <-> UTF-16 helpers over ConvertUTF. In the original
// they are linked in the ParticleUniverseSphere.cpp group.
typedef std::basic_string<unsigned short> utf16string;

void WriteUTF32ToUTF16(_IO_FILE*, const std::wstring&, unsigned long);
std::wstring UTF8ToUTF32(const std::string& text);
utf16string UTF32ToUTF16(const std::wstring& text);
std::wstring UTF16ToUTF32(const std::basic_string<unsigned short, std::char_traits<unsigned short>, std::allocator<unsigned short> >& text);
int ReadUTF16ToUTF32(const unsigned short* source, wchar_t* destination, unsigned long length);
int ReadUTF16ToUTF32(FILE* source, wchar_t* destination, unsigned long length);

#endif
