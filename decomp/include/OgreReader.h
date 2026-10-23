#ifndef OGREREADER_H
#define OGREREADER_H

#include <string>

#include <OgreDataStream.h>

class CFileInfo;
class CEditorScene;
class CDescriptorLoadConfiguration;
class CEditorBaseObject;

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
    friend class COgreResourceFile;
    friend bool loadObjectByCompressedFile(CEditorScene*, CDescriptorLoadConfiguration&,
                                         COgreReader&, CEditorBaseObject*, bool);
    std::wstring m_sFileName;
    char* m_pData;
    unsigned int m_iSize;
    unsigned int m_iPosition;
};

#endif
