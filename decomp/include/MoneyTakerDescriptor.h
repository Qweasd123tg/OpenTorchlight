#ifndef MONEYTAKERDESCRIPTOR_H
#define MONEYTAKERDESCRIPTOR_H

#include "BaseObjectDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"
#include "MoneyTaker.h"

class CMoneyTakerDescriptor : public CBaseObjectDescriptor
{
public:
    virtual ~CMoneyTakerDescriptor();
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    virtual void InputLogicEvent(CEditorBaseObject*, unsigned int, CEditorBaseObject*);
    CMoneyTakerDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description);


    static void Set_setAmount(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count)
    {
        if (object)
            static_cast<CMoneyTaker*>(object)->setAmount(((const UNIONDATA32BIT*)data)->m_iValue);
    }
    static UNIONDATA8BIT* Get_getAmount(CEditorBaseObject* object, unsigned int& count)
    {
        if (!object)
            return NULL;
        count = sizeof(int);
        gUnionOf32BitData[0].m_iValue = static_cast<CMoneyTaker*>(object)->getAmount();
        return (UNIONDATA8BIT*)gUnionOf32BitData;
    }
};

#endif
