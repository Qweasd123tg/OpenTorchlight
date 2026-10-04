#ifndef LOGICGROUP_H
#define LOGICGROUP_H

#include <fstream>

#include "DataGroup.h"
#include "DescriptorLoadConfiguration.h"
#include "DescriptorSaveConfiguration.h"
#include "EditorBaseObject.h"
#include "LogicObject.h"
#include "OgreReader.h"
#include "ResourceManager.h"
#include "TArrayList.h"

class CLogicGroup : public CEditorBaseObject
{
public:
    virtual ~CLogicGroup();

    CLogicObject* GetLogicObjectByIndex(unsigned int index);
    unsigned int GetLogicObjectIndex(CLogicObject* pLogicObject);

    void AddLogicObject(CLogicObject* pLogicObject);
    int AddLogicObject(long long objectID);

    bool RemoveLogicObjectsLink(unsigned int logicObjectIndex,
                                unsigned int linkIndex);
    bool RemoveLogicObjectByIndex(unsigned int index);
    bool RemoveLogicObjectsRefingObjectID(long long objectID);

    CLogicGroup(CResourceManager* pResourceManager);

    void saveLogicGroupToDataGroup(
        CDataGroup* pDataGroup,
        std::basic_ofstream<char, std::char_traits<char> >* pStream,
        CDescriptorSaveConfiguration* pSaveConfiguration);
    void loadLogicGroupToDataGroup(
        CDataGroup* pDataGroup,
        COgreReader* pReader,
        CDescriptorLoadConfiguration* pLoadConfiguration);

    CResourceManager* m_pResourceManager;
    TArrayList<CLogicObject*> m_logicObjects;
    float m_fEnabled;
};

#endif
