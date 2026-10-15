#include "PositionableObjectDescriptor.h"

CEditorBaseObject* CPositionableObjectDescriptor::CreateObject(CEditorScene* scene)
{
    return NULL;
}

CPositionableObjectDescriptor::~CPositionableObjectDescriptor()
{
}

#include "PositionableObject.h"

void CPositionableObjectDescriptor::InputLogicEvent(CEditorBaseObject* object, unsigned int event, CEditorBaseObject* initiator)
{
    if (object)
    {
        CPositionableObject* target = dynamic_cast<CPositionableObject*>(object);
        if (target)
        {
            switch (event)
            {
            case 0: target->setVisible(true); break;
            case 1: target->setVisible(false); break;
            }
        }
    }
}

bool CPositionableObjectDescriptor::loadAdditionalInfo(CEditorBaseObject* object, COgreReader* reader, CDataGroup* data, CDescriptorLoadConfiguration* configuration)
{
    CPositionableObject* positionable = dynamic_cast<CPositionableObject*>(object);
    if (positionable) {
        positionable->setPosition(positionable->getPosition(false));
        positionable->setOrientation(positionable->getOrientation(), false);
    }
    return true;
}

CPositionableObjectDescriptor::CPositionableObjectDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description, bool option1, bool option2, bool option3, bool option4, bool option5)
    : CBaseObjectDescriptor(name, group, description)
{
    if (option5)
    {
        AddProperty(L"PROPERTIES", L"VISIBLE", L"sets the object visible or not", (void*)Set_setVisible, (void*)Get_getVisible, VARIABLE_TYPE_BOOL, 0);
        AddOutputLogic(OUTPUT_EVENT_ON_VISIBLE);
        AddOutputLogic(OUTPUT_EVENT_ON_INVISIBLE);
        AddInputLogic(INPUT_EVENT_SHOW);
        AddInputLogic(INPUT_EVENT_HIDE);
    }
    if (option1)
    {
        AddProperty(L"POSITION", L"POSITION", L"Position by X,Y,Z", (void*)Set_setPositionLocal, (void*)Get_getPositionLocal, VARIABLE_TYPE_VECTOR3, 0);
        m_iFlags |= DESCRIPTOR_FLAG_POSITIONABLE;
    }
    if (option2)
    {
        AddProperty(L"ORIENTATION", L"FORWARD", L"Forward by X,Y,Z", (void*)Set_setForward, (void*)Get_getForward, VARIABLE_TYPE_VECTOR3, 0);
        m_iFlags |= DESCRIPTOR_FLAG_ROTATEABLE;
    }
    if (option3)
    {
        AddProperty(L"ORIENTATION", L"RIGHT", L"Right by X,Y,Z", (void*)Set_setRight, (void*)Get_getRight, VARIABLE_TYPE_VECTOR3, 0);
    }
    if (option4)
    {
        AddProperty(L"ORIENTATION", L"UP", L"Up by X,Y,Z", (void*)Set_setUp, (void*)Get_getUp, VARIABLE_TYPE_VECTOR3, 0);
    }
}
