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

#include "DataGroup.h"
#include "DataValue.h"

CHierarchy::~CHierarchy()
{
}

void CHierarchy::parseHierachy(CDataGroup* group)
{
    if (!group) return;
    CDataGroup* types = group->GetDataGroupByName(L"UNITTYPES", false);
    if (!types) return;
    const std::wstring key(L"ID");
    m_types.setGrowBy(types->GetNumberOfDataGroups() + 1);
    for (unsigned int i = 0; i < types->GetNumberOfDataGroups(); ++i) {
        CDataGroup* type = types->GetDataGroup(i);
        unsigned int id = type->GetDataValue(key, static_cast<unsigned int>(-1));
        if (id == static_cast<unsigned int>(-1)) continue;
        m_typeIDs[STRINGS::StringUpper(type->GetGroupName())] = id;
        m_types.add(id);
        if (type->GetNumberOfDataValues() <= 1)
            m_parentTypes[id].push_back(id);
        else {
            for (unsigned int j = 0; j < type->GetNumberOfDataValues(); ++j) {
                CDataValue* value = type->GetDataValue(j);
                if (value->GetDataValueName() != key)
                    m_parentTypes[id].push_back(value->GetValueUInt32());
            }
        }
    }
}

CHierarchy::CHierarchy(const wchar_t* filename)
    : m_types(10)
{
    CDataGroup group(L"", NULL, 20, 10, NULL);
    group.LoadFile(filename, static_cast<CTimerStatics*>(NULL));
    parseHierachy(&group);
}
