#ifndef UTFCONVERSION_H
#define UTFCONVERSION_H

#include <string>

// Partial: wchar_t (UTF-32) <-> UTF-16 helpers over ConvertUTF. In the original
// they are linked in the ParticleUniverseSphere.cpp group.
typedef std::basic_string<unsigned short> utf16string;

utf16string UTF32ToUTF16(const std::wstring& text);
int ReadUTF16ToUTF32(const unsigned short* source, wchar_t* destination, unsigned long length);

#endif
