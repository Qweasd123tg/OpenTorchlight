#ifndef MONEYTAKERDESCRIPTOR_H
#define MONEYTAKERDESCRIPTOR_H

#include "BaseObjectDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"

class CMoneyTakerDescriptor : public CBaseObjectDescriptor
{
public:
    virtual ~CMoneyTakerDescriptor();
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    virtual void InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*);
    CMoneyTakerDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description);


    static void Set_setAmount(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getAmount(CEditorBaseObject* object, unsigned int& count);
};

#endif
