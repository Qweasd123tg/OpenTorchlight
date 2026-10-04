#ifndef BASEOBJECTDESCRIPTOR_H
#define BASEOBJECTDESCRIPTOR_H

#include "Descriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"

class CBaseObjectDescriptor : public CDescriptor
{
public:
    virtual ~CBaseObjectDescriptor();
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    void SetIcon(const wchar_t*);
    CBaseObjectDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description);

};

#endif
