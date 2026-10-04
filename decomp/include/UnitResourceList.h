#ifndef UNITRESOURCELIST_H
#define UNITRESOURCELIST_H

#include <map>
#include <string>

#include "DataGroup.h"
#include "GenTypes.h"
#include "Hierarchy.h"
#include "ResourceSettings.h"
#include "RunicCore.h"
#include "TArrayList.h"

class CUnitResourceList : public CRunicCore
{
public:
    virtual ~CUnitResourceList();

    static CUnitResourceList *getSingleton();

    CDataGroup *getDataGroupByGuid(long long guid);
    TArrayList<std::wstring> *getPlayerClassNames();
    std::map<long long, CDataGroup *> *getGroupByName(
        const std::wstring &name);
    void getUnitNames(TArrayList<std::wstring> &unitNames);
    void getDataGroupsByUnitType(unsigned int unitType,
                                 TArrayList<CDataGroup *> &dataGroups);

    void clearDataOut();

    CDataGroup *getDataGroupByObjectName(const std::wstring &objectName);
    CDataGroup *getDataGroupByFileName(const wchar_t *fileName,
                                       const wchar_t *objectName);
    CDataGroup *getDataGroupByFileName(const std::wstring &fileName,
                                       const std::wstring &objectName);
    CDataGroup *getDataGroupByObjectName(const std::wstring &resourceGroup,
                                         const std::wstring &objectName);

    CDataGroup *parseChildFile(const std::wstring &fileName, bool createNew);
    void addNewItem(const std::wstring &resourceGroup,
                    CDataGroup *dataGroup, bool overwrite);

    void loadFile(ERESOURCE_GROUPS resourceGroup,
                  std::wstring resourceGroupName,
                  std::wstring fileName, bool overwrite,
                  CDataGroup *parentGroup);

    void parseMasterDirectory(ERESOURCE_GROUPS resourceGroup,
                              std::wstring directory,
                              std::wstring resourceGroupName,
                              CDataGroup *parentGroup, bool overwrite);

    void InitUnitResourceList(CResourceSettings *resourceSettings,
                              CHierarchy *hierarchy);

    CResourceSettings *m_pResourceSettings;

    std::map<std::wstring, std::map<std::wstring, CDataGroup *> >
        m_dataGroupsByResourceGroupAndName;

    std::map<std::wstring, std::map<std::wstring, CDataGroup *> >
        m_dataGroupsByFileItemAndName;

    std::map<std::wstring, std::map<long long, CDataGroup *> >
        m_dataGroupsByResourceGroupAndGuid;

    std::map<long long, CDataGroup *> m_dataGroupsByGuid;

    TArrayList<std::wstring> m_playerClassNames;

    unsigned char m_alignmentPaddingF0[0x8];

    CHierarchy *m_pHierarchy;

    TArrayList<CDataGroup *> m_loadedDataGroups;
    CDataGroup *m_pMasterDataGroup;
};

#endif
