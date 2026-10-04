#include "EmptyStrings.h"
#include "FileReader.h"
#include "FileSystem.h"
#include "FileUtilities.h"
#include "StringUtilities.h"
#include "UTFConversion.h"
#include <OgreLogManager.h>
#include <OgreMemoryAllocatorConfig.h>
#include <cstring>

int _wfopen_s(FILE** file, const wchar_t* filename, const wchar_t* mode);

CFileReader::CFileReader()
    : m_sFilename(L"NOT LOADED"), m_pBuffer(NULL), m_iLength(0), m_iPosition(0), m_iCharacterSize(4)
{
}

CFileReader::~CFileReader()
{
    if (m_pBuffer != NULL)
    {
        OGRE_FREE(m_pBuffer, Ogre::MEMCATEGORY_GENERAL);
        m_pBuffer = NULL;
    }
}

wchar_t* CFileReader::GetBuffer()
{
    return m_pBuffer;
}

wchar_t& CFileReader::ReadWChar()
{
    if (m_iPosition >= m_iLength)
        return m_pBuffer[m_iLength - 1];
    return m_pBuffer[m_iPosition++];
}

void CFileReader::ResetFile()
{
    m_iPosition = 0;
}

bool CFileReader::EndOfFile()
{
    return m_iPosition == m_iLength;
}

std::wstring CFileReader::ReadLine(wchar_t ignore)
{
    std::wstring line;
    wchar_t character = ReadWChar();
    while (character != L'\n' && character != 0 && !EndOfFile())
    {
        if (character > L'\r' && character != ignore)
            line += character;
        character = ReadWChar();
    }
    return line;
}

void CFileReader::ReadLineTokenize(std::queue<std::wstring>* tokens, const wchar_t* separators, wchar_t comment)
{
    std::wstring line = ReadLine(0);
    if (line != L"")
    {
        std::wstring::size_type end = line.find(comment);
        if (end != std::wstring::npos)
            line = line.erase(end);
        std::wstring::size_type start = line.find_first_not_of(separators, 0);
        while (start != std::wstring::npos)
        {
            end = line.find_first_of(separators, start);
            tokens->push(line.substr(start, end - start));
            start = line.find_first_not_of(separators, end);
        }
    }
}

bool CFileReader::ReadFile(FILE* file)
{
    m_iCharacterSize = 4;
    if (file == NULL)
        return false;
    fseek(file, 0, SEEK_END);
    m_iLength = static_cast<unsigned int>(ftell(file));
    fseek(file, 0, SEEK_SET);
    if (m_pBuffer != NULL)
    {
        OGRE_FREE(m_pBuffer, Ogre::MEMCATEGORY_GENERAL);
        m_pBuffer = NULL;
    }
    m_pBuffer = OGRE_ALLOC_T(wchar_t, m_iLength, Ogre::MEMCATEGORY_GENERAL);
    std::memset(m_pBuffer, 0, m_iLength * sizeof(wchar_t));
    ReadUTF16ToUTF32(file, m_pBuffer, m_iLength);
    if (ReadWChar() != 0xfeff)
        m_iPosition = 0;
    return true;
}

bool CFileReader::ConvertFileToUnicode(FILE* file, const std::wstring& filename)
{
    unsigned char prefix[80];
    fseek(file, 0, SEEK_SET);
    fread(prefix, sizeof(prefix), 1, file);
    const char* error = "Unable to determin file type( Best Guess ASCII ). You need to save the file as unicode - recommend doing it in word pad.";
    if (prefix[0] == 0xff && prefix[1] == 0xfe)
    {
        if (prefix[2] != 0 || prefix[3] != 0)
        {
            fseek(file, 0, SEEK_SET);
            return true;
        }
        error = "Need to resave file as a unicode 16bit or ascii file. File read as Unicode 32bit.";
    }
    else if (prefix[0] == 0 && prefix[1] == 0 && prefix[2] == 0xfe && prefix[3] == 0xff)
        error = "Need to resave file as a unicode 16bit or ascii file. File read as Unicode 32bit.";
    else if (prefix[0] == 0xef && prefix[1] == 0xbb && prefix[2] == 0xbf)
        error = "Need to resave file as a unicode 16bit or ascii file. File read as UTF-8.";
    else if (prefix[0] == 0xfe && prefix[1] == 0xff)
        error = "Need to resave file as a unicode 16bit little endian or ascii file. File read was read in as Unicode 16bit big endian.";
    Ogre::LogManager::getSingleton().logMessage(error + STRINGS::StringConvertToNarrow(filename.c_str()),
                                                Ogre::LML_CRITICAL, false);
    return false;
}

bool CFileReader::ReadFile(const std::wstring& filename)
{
    Ogre::DataStreamPtr stream;
    if (CFileSystem::getSingleton() != NULL)
    {
        CFileInfo info;
        CFileSystem::getSingleton()->getFileInfo(filename, info, false, true, false);
        stream = CFileSystem::getSingleton()->getDataStream(info);
    }
    if (stream.isNull())
    {
        m_sFilename = FILESYSTEM::CleanPath(filename);
        FILE* file = NULL;
        _wfopen_s(&file, m_sFilename.c_str(), L"rb");
        if (file == NULL)
            return false;
        if (feof(file))
            fclose(file);
        if (ConvertFileToUnicode(file, filename))
        {
            m_iPosition = 0;
            ReadFile(file);
        }
        fclose(file);
    }
    else
    {
        // The original uses the previous length's parity here.
        unsigned int bytes = static_cast<unsigned int>(stream->size()) + (m_iLength & 1);
        m_iLength = (bytes >> 1) + 1;
        if (m_pBuffer != NULL)
        {
            OGRE_FREE(m_pBuffer, Ogre::MEMCATEGORY_GENERAL);
            m_pBuffer = NULL;
        }
        if (m_iLength < 2)
            return false;
        m_pBuffer = OGRE_ALLOC_T(wchar_t, m_iLength, Ogre::MEMCATEGORY_GENERAL);
        m_pBuffer[m_iLength - 1] = 0;
        m_pBuffer[m_iLength - 2] = 0;
        unsigned short* input = new unsigned short[m_iLength];
        std::memset(input, 0, m_iLength * sizeof(unsigned short));
        stream->read(input, bytes);
        ReadUTF16ToUTF32(input, m_pBuffer, m_iLength);
        // No delete[] of this temporary occurs in the original function.
        if (ReadWChar() != 0xfeff)
            m_iPosition = 0;
    }
    return m_iLength != 0;
}
