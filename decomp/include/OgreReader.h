#ifndef OGREREADER_H
#define OGREREADER_H

#include <string>

#include <OgreDataStream.h>

class CFileInfo;

// Sequential reader over a file loaded into memory.
class COgreReader
{
public:
    COgreReader();
    ~COgreReader();

    void read(void* buffer, unsigned int size);
    void seek(unsigned int position);

    bool ReadFile(Ogre::DataStreamPtr stream);
    bool ReadFile(CFileInfo& info);
    bool ReadFile(const std::wstring& path);

private:
    std::wstring m_sFileName;
    char* m_pData;
    unsigned int m_iSize;
    unsigned int m_iPosition;
};

#endif
