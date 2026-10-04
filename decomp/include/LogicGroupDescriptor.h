#ifndef LOGICGROUPDESCRIPTOR_H
#define LOGICGROUPDESCRIPTOR_H

#include "DataGroup.h"
#include "Descriptor.h"
#include "DescriptorLoadConfiguration.h"
#include "DescriptorSaveConfiguration.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "OgreReader.h"
#include "DescriptorProp.h"

class CLogicGroupDescriptor : public CDescriptor
{
public:
    virtual ~CLogicGroupDescriptor();
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    virtual bool saveAdditionalInfo(CEditorBaseObject*, std::basic_ofstream<char, std::char_traits<char> >*, CDataGroup*, CDescriptorSaveConfiguration*);
    virtual bool loadAdditionalInfo(CEditorBaseObject*, COgreReader*, CDataGroup*, CDescriptorLoadConfiguration*);
    virtual void InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*);
    void levelActivated(CEditorScene*);
    CLogicGroupDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description);

};

#endif
