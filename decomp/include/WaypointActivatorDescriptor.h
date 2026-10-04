#ifndef WAYPOINTACTIVATORDESCRIPTOR_H
#define WAYPOINTACTIVATORDESCRIPTOR_H

#include "PositionableObjectDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"

class CWaypointActivatorDescriptor : public CPositionableObjectDescriptor
{
public:
    virtual ~CWaypointActivatorDescriptor();
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    virtual void InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*);
    CWaypointActivatorDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description);

};

#endif
