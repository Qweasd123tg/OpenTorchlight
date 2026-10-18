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

#include "FileUtilities.h"

CDataGroup* CUnitResourceList::getDataGroupByFileName(const std::wstring& fileName, const std::wstring& objectName)
{
    typedef std::map<std::wstring, std::map<std::wstring, CDataGroup*> > Groups;
    Groups::iterator group = m_dataGroupsByFileItemAndName.find(STRINGS::StringUpper(fileName));
    if (group == m_dataGroupsByFileItemAndName.end())
        return NULL;
    std::map<std::wstring, CDataGroup*>::iterator data =
        group->second.find(STRINGS::StringUpper(FILESYSTEM::CleanPath(objectName)));
    if (data != group->second.end())
        return data->second;
    return NULL;
}

CDataGroup* CUnitResourceList::getDataGroupByObjectName(const std::wstring& resourceGroup, const std::wstring& objectName)
{
    typedef std::map<std::wstring, std::map<std::wstring, CDataGroup*> > Groups;
    Groups::iterator group = m_dataGroupsByResourceGroupAndName.find(STRINGS::StringUpper(resourceGroup));
    if (group == m_dataGroupsByResourceGroupAndName.end())
        return NULL;
    std::map<std::wstring, CDataGroup*>::iterator data = group->second.find(STRINGS::StringUpper(objectName));
    if (data != group->second.end())
        return data->second;
    return NULL;
}

#include "MasterResourceManager.h"
#include "EmptyStrings.h"

CUnitResourceList* CUnitResourceList::getSingleton()
{
    return m_pGlobalUnitResourceList;
}

unsigned int CUnitResourceList::getDataGroupsByUnitType(unsigned int type, TArrayList<CDataGroup*>& groups)
{
    CHierarchy* hierarchy = CMasterResourceManager::getSingleton()->m_pHierarchy;
    if (!hierarchy)
        return 0;
    typedef std::map<std::wstring, std::map<std::wstring,CDataGroup*> > Groups;
    for (Groups::iterator group = m_dataGroupsByResourceGroupAndName.begin(); group != m_dataGroupsByResourceGroupAndName.end(); ++group) {
        for (std::map<std::wstring,CDataGroup*>::iterator item = group->second.begin(); item != group->second.end(); ++item) {
            CDataGroup* data = item->second;
            std::wstring unitType = data->GetDataValue(L"UNITTYPE", EMPTY_WSTRING);
            if (unitType != EMPTY_WSTRING && hierarchy->ISA(hierarchy->getTypeIDByName(unitType), type))
                groups.add(data);
        }
    }
    return groups.size();
}

#include "FileSystem.h"
#include "Utilities.h"
#include <OgreLogManager.h>

CUnitResourceList::CUnitResourceList()
    : m_pResourceSettings(NULL), m_playerClassNames(5), m_pHierarchy(NULL),
      m_loadedDataGroups(1000), m_pMasterDataGroup(NULL)
{
    if (!m_pGlobalUnitResourceList)
        m_pGlobalUnitResourceList = this;
}

CUnitResourceList::~CUnitResourceList()
{
    if (m_pMasterDataGroup) {
        delete m_pMasterDataGroup;
        m_pMasterDataGroup = NULL;
    }
    clearDataOut();
    m_pGlobalUnitResourceList = NULL;
}

CDataGroup* CUnitResourceList::getDataGroupByFileName(const wchar_t* fileName,
                                                    const wchar_t* objectName)
{
    typedef std::map<std::wstring, std::map<std::wstring, CDataGroup*> > Groups;
    Groups::iterator group = m_dataGroupsByFileItemAndName.find(STRINGS::StringUpper(fileName));
    if (group == m_dataGroupsByFileItemAndName.end())
        return NULL;
    std::map<std::wstring, CDataGroup*>::iterator data =
        group->second.find(STRINGS::StringUpper(FILESYSTEM::CleanPath(objectName)));
    return data == group->second.end() ? NULL : data->second;
}

CDataGroup* CUnitResourceList::parseChildFile(const std::wstring& fileName, bool createNew)
{
    CDataGroup* data = new CDataGroup(L"", NULL, 20, 10, NULL);
    data->LoadFile(fileName, NULL);
    bool dontCreate = data->GetDataValue(L"DONTCREATE", false);
    std::wstring baseFile = data->GetDataValue(L"BASEFILE", EMPTY_WSTRING);
    std::wstring guid = data->GetDataValue(L"UNIT_GUID", EMPTY_WSTRING);
    std::wstring displayName = data->GetDataValue(L"DISPLAYNAME", EMPTY_WSTRING);
    if ((guid.empty() || displayName.empty()) && createNew &&
        (guid.empty() || !dontCreate)) {
        if (guid.empty()) {
            guid = STRINGS::GetValueAsWString(UTILITIES::createUniqueGuid());
            data->SetDataValue(L"UNIT_GUID", guid, false);
        }
        if (displayName.empty()) {
            std::wstring name = data->GetDataValue(L"NAME", EMPTY_WSTRING);
            if (name != EMPTY_WSTRING)
                data->SetDataValue(L"DISPLAYNAME", name, true);
        }
        data->SaveToFile(fileName);
    }
    CDataGroup* result = data;
    if (baseFile != EMPTY_WSTRING) {
        result = parseChildFile(baseFile, false);
        if (!result) {
            std::string error = "Unable to find base file : \n" +
                STRINGS::StringConvertToNarrow(baseFile.c_str()) + "\n for child file:\n" +
                STRINGS::StringConvertToNarrow(fileName.c_str());
            Ogre::LogManager::getSingleton().logMessage(error.c_str(), Ogre::LML_CRITICAL, false);
            delete data;
            return NULL;
        }
        result->CopyDataGroup(data, false);
        delete data;
        result->SetDataValue(L"UNIT_GUID", guid, false);
    }
    if (result)
        result->SetDataValue(L"DONTCREATE", dontCreate);
    return result;
}

void CUnitResourceList::parseMasterDirectory(ERESOURCE_GROUPS resourceGroup,
                                            std::wstring directory,
                                            std::wstring resourceGroupName,
                                            CDataGroup* parentGroup, bool overwrite)
{
    if (directory == L"" || resourceGroupName == L"")
        return;
    TArrayList<std::wstring> files(5000);
    CFileSystem::getSingleton()->getFileList(directory, files, L"*.dat", true, true, false, false);
    for (unsigned int i = 0; i < files.size(); ++i)
        loadFile(resourceGroup, resourceGroupName, files[i], false, parentGroup);
}
