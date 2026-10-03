#ifndef OGREREADER_H
#define OGREREADER_H

#include <string>

// Partial: OgreReader.cpp. Sequential reader over a file loaded into memory.
class COgreReader
{
public:
    COgreReader();
    ~COgreReader();

    void read(void* buffer, unsigned int size);
    void seek(unsigned int position);

private:
    std::wstring m_sFileName;
    char* m_pData;
    unsigned int m_iSize;
    unsigned int m_iPosition;
};

#endif
