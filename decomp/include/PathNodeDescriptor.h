#ifndef PATHNODEDESCRIPTOR_H
#define PATHNODEDESCRIPTOR_H

#include "PositionableObjectDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"

class CPathNodeDescriptor : public CPositionableObjectDescriptor
{
public:
    virtual ~CPathNodeDescriptor();
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    CPathNodeDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description);

};

#endif
