#include "Hierarchy.h"
#include "EmptyStrings.h"
#include "StringUtilities.h"

bool CHierarchy::ISA(unsigned int type, unsigned int parent)
{
    if (type == parent)
        return true;
    std::map<unsigned int, std::vector<unsigned int> >::iterator found = m_parentTypes.find(type);
    if (found != m_parentTypes.end())
        for (unsigned int i = 0; i < found->second.size(); ++i)
            if (found->second[i] == parent)
                return true;
    return false;
}

std::wstring CHierarchy::getTypeName(unsigned int type)
{
    for (std::map<std::wstring, unsigned int>::iterator i = m_typeIDs.begin();
         i != m_typeIDs.end(); ++i)
        if (i->second == type)
            return i->first;
    return EMPTY_WSTRING;
}

void CHierarchy::getTypeNames(TArrayList<std::wstring>* names)
{
    for (std::map<std::wstring, unsigned int>::iterator i = m_typeIDs.begin();
         i != m_typeIDs.end(); ++i)
        names->add(i->first);
}

UNITTYPES::EUNITTYPES CHierarchy::getTypeIDByName(const std::wstring& name)
{
    if (m_typeIDs.empty())
        return static_cast<UNITTYPES::EUNITTYPES>(-1);
    std::wstring upperName = STRINGS::StringUpper(name);
    std::map<std::wstring, unsigned int>::iterator i = m_typeIDs.find(upperName);
    if (i != m_typeIDs.end())
        return static_cast<UNITTYPES::EUNITTYPES>(i->second);
    return static_cast<UNITTYPES::EUNITTYPES>(-1);
}
