#include "AffectorDescriptor.h"

void CAffectorDescriptor::deleteNotification()
{
    for (unsigned int i = 0; i < m_Objects.size(); ++i)
        DescriptorObjectBeingDeleted(m_Objects[i]);
}

CAffectorDescriptor::~CAffectorDescriptor()
{
}

#include "AffectorWrapper.h"
#include <map>
#include <string>

bool CAffectorDescriptor::DescriptorObjectBeingDeleted(CEditorBaseObject* object)
{
    static_cast<CAffectorWrapper*>(object)->destroyAffector();
    return true;
}

void CAffectorDescriptor::InputLogicEvent(CEditorBaseObject* object, unsigned int event, CEditorBaseObject* initiator)
{
    if (object)
    {
        CAffectorWrapper* target = dynamic_cast<CAffectorWrapper*>(object);
        if (target)
        {
            switch (event)
            {
            case 2: target->setEnabled(true); break;
            case 3: target->setEnabled(false); break;
            }
            CPositionableObjectDescriptor::InputLogicEvent(object, event, initiator);
        }
    }
}

CAffectorDescriptor::CAffectorDescriptor(const wchar_t* name, const wchar_t* group, const wchar_t* description)
    : CPositionableObjectDescriptor(name, group, description, true, false, false, false, false)
{
    AddInputLogic(INPUT_EVENT_ENABLE);
    AddInputLogic(INPUT_EVENT_DISABLE);
    m_iFlags &= ~(DESCRIPTOR_FLAG_100 | DESCRIPTOR_FLAG_4000);
    m_ParentFilters.add(std::wstring(L"PARTICLE"));
    m_ParentFilters.add(std::wstring(L"EMITTER"));
    AddProperty(L"PROPERTIES", L"ENABLE", L"Disable or Enable this affector", (void*)Set_setEnabled, (void*)Get_getEnabled, VARIABLE_TYPE_BOOL, 0);
}
