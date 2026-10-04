#include "EmptyStrings.h"
#include <OgrePrerequisites.h>
#include "StringRepository.h"

CStringRepository::CStringRepository()
    : m_iNextID(0), m_sEmpty(L"")
{
}

const std::wstring& CStringRepository::GetString(unsigned int id)
{
    std::map<unsigned int, StringToID::iterator>::iterator it = m_Strings.find(id);
    if (it == m_Strings.end())
        return m_sEmpty;
    return it->second->first;
}

CStringRepository::~CStringRepository()
{
}

int CStringRepository::GetStringID(const std::wstring& text)
{
    StringToID::iterator it = m_IDs.find(text);
    if (it == m_IDs.end())
        return -1;
    return it->second;
}

unsigned int CStringRepository::AddString(const std::wstring& text)
{
    unsigned int id = GetStringID(text);
    if (id != (unsigned int)-1)
        return id;
    id = m_iNextID++;
    m_IDs[text] = id;
    m_Strings[id] = m_IDs.find(text);
    return id;
}
