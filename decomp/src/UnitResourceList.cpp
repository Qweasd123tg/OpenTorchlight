#include "UnitResourceList.h"
#include "StringUtilities.h"

TArrayList<std::wstring> * CUnitResourceList::getPlayerClassNames()
{
    return &m_playerClassNames;
}

CDataGroup* CUnitResourceList::getDataGroupByGuid(long long guid)
{
    if (guid == 0xffffffffLL)
        return NULL;
    std::map<long long, CDataGroup*>::iterator found = m_dataGroupsByGuid.find(guid);
    return found == m_dataGroupsByGuid.end() ? NULL : found->second;
}

std::map<long long, CDataGroup*>* CUnitResourceList::getGroupByName(const std::wstring& name)
{
    std::map<std::wstring, std::map<long long, CDataGroup*> >::iterator found =
        m_dataGroupsByResourceGroupAndGuid.find(name);
    return found == m_dataGroupsByResourceGroupAndGuid.end() ? NULL : &found->second;
}

void CUnitResourceList::getUnitNames(TArrayList<std::wstring>& unitNames)
{
    for (std::map<std::wstring, std::map<std::wstring, CDataGroup*> >::iterator group =
             m_dataGroupsByResourceGroupAndName.begin();
         group != m_dataGroupsByResourceGroupAndName.end(); ++group)
        for (std::map<std::wstring, CDataGroup*>::iterator unit = group->second.begin();
             unit != group->second.end(); ++unit)
            unitNames.add(unit->first);
}

void CUnitResourceList::clearDataOut()
{
    m_loadedDataGroups.deleteAll();
    m_dataGroupsByGuid.clear();
    m_dataGroupsByFileItemAndName.clear();
    m_dataGroupsByResourceGroupAndGuid.clear();
    m_playerClassNames.clear();
}

CDataGroup* CUnitResourceList::getDataGroupByObjectName(const std::wstring& objectName)
{
    std::wstring name = STRINGS::StringUpper(objectName);
    for (std::map<std::wstring, std::map<std::wstring, CDataGroup*> >::iterator group =
             m_dataGroupsByResourceGroupAndName.begin();
         group != m_dataGroupsByResourceGroupAndName.end(); ++group) {
        std::map<std::wstring, CDataGroup*>::iterator found = group->second.find(name);
        if (found != group->second.end())
            return found->second;
    }
    return NULL;
}
