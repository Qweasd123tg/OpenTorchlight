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
