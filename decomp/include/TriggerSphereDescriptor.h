#ifndef TRIGGERSPHEREDESCRIPTOR_H
#define TRIGGERSPHEREDESCRIPTOR_H

#include "TriggerDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"
#include "TriggerSphere.h"

class CTriggerSphereDescriptor : public CTriggerDescriptor
{
public:
    virtual ~CTriggerSphereDescriptor();
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    CTriggerSphereDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description);


    static void Set_setRadius(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getRadius(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(float);
        gUnionOf32BitData[0].m_fValue = static_cast<CTriggerSphere*>(object)->getRadius();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
};

#endif
