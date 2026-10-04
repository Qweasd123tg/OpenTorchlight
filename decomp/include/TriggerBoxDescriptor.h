#ifndef TRIGGERBOXDESCRIPTOR_H
#define TRIGGERBOXDESCRIPTOR_H

#include "TriggerDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"

class CTriggerBoxDescriptor : public CTriggerDescriptor
{
public:
    virtual ~CTriggerBoxDescriptor();
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    CTriggerBoxDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description);


    static void Set_setDimensions(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getDimensions(CEditorBaseObject* object, unsigned int& count);
};

#endif
