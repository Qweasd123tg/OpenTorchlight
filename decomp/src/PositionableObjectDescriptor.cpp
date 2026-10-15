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
