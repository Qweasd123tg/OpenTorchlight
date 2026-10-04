#include "EmptyStrings.h"
#include "OgreReader.h"
#include "FileSystem.h"

COgreReader::COgreReader()
    : m_sFileName(EMPTY_WSTRING), m_pData(NULL), m_iSize(0), m_iPosition(0)
{
}

void COgreReader::seek(unsigned int position)
{
    m_iPosition = position;
    if (position > m_iSize)
        m_iPosition = m_iSize;
}

void COgreReader::read(void* buffer, unsigned int size)
{
    if (m_iPosition == m_iSize)
        return;
    memcpy(buffer, m_pData + m_iPosition, size);
    m_iPosition += size;
}

bool COgreReader::ReadFile(Ogre::DataStreamPtr stream)
{
    m_iSize = 0;
    if (m_pData)
        delete[] m_pData;
    m_pData = NULL;
    if (stream.isNull())
        return false;
    m_iSize = stream->size();
    if (m_iSize == 0)
        return false;
    m_pData = new char[m_iSize];
    stream->read(m_pData, m_iSize);
    return true;
}

bool COgreReader::ReadFile(CFileInfo& info)
{
    Ogre::DataStreamPtr stream = CFileSystem::getSingleton()->getDataStream(info);
    if (stream.isNull())
    {
        m_iSize = 0;
        if (m_pData)
        {
            OGRE_FREE(m_pData, Ogre::MEMCATEGORY_GENERAL);
            m_pData = NULL;
        }
        return m_iSize != 0;
    }
    return ReadFile(stream);
}

COgreReader::~COgreReader()
{
    if (m_pData)
    {
        m_iSize = 0;
        if (m_pData)
            delete[] m_pData;
        m_pData = NULL;
    }
}

bool COgreReader::ReadFile(const std::wstring& path)
{
    m_sFileName = path;
    CFileInfo info;
    CFileSystem::getSingleton()->getFileInfo(path, info, true, false, false);
    return ReadFile(info);
}
