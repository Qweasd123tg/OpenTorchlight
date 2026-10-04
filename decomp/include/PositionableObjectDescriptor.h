#ifndef POSITIONABLEOBJECTDESCRIPTOR_H
#define POSITIONABLEOBJECTDESCRIPTOR_H

#include "BaseObjectDescriptor.h"
#include "DataGroup.h"
#include "DescriptorLoadConfiguration.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "OgreReader.h"
#include "DescriptorProp.h"

class CPositionableObjectDescriptor : public CBaseObjectDescriptor
{
public:
    virtual ~CPositionableObjectDescriptor();
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    virtual bool loadAdditionalInfo(CEditorBaseObject*, COgreReader*, CDataGroup*, CDescriptorLoadConfiguration*);
    virtual void InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*);
    CPositionableObjectDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description, bool option1, bool option2, bool option3, bool option4, bool option5);

};

#endif
