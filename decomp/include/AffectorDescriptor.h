#ifndef AFFECTORDESCRIPTOR_H
#define AFFECTORDESCRIPTOR_H

#include "PositionableObjectDescriptor.h"
#include "EditorBaseObject.h"
#include "DescriptorProp.h"

class CAffectorDescriptor : public CPositionableObjectDescriptor
{
public:
    virtual ~CAffectorDescriptor();
    virtual void deleteNotification();
    virtual bool DescriptorObjectBeingDeleted(CEditorBaseObject*);
    virtual void InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*);
    CAffectorDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description);


    static void Set_setEnabled(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getEnabled(CEditorBaseObject* object, unsigned int& count);
};

#endif
