#include "ParticleEmitterWrapperDescriptor.h"

void CParticleEmitterWrapperDescriptor::deleteNotification()
{
    for (unsigned int i = 0; i < m_Objects.size(); ++i)
        DescriptorObjectBeingDeleted(m_Objects[i]);
}

CParticleEmitterWrapperDescriptor::~CParticleEmitterWrapperDescriptor()
{
}

#include "ParticleEmitterWrapper.h"
#include <map>
#include <string>

bool CParticleEmitterWrapperDescriptor::DescriptorObjectBeingDeleted(CEditorBaseObject* object)
{
    static_cast<CParticleEmitterWrapper*>(object)->destroyEmitter();
    return true;
}

void CParticleEmitterWrapperDescriptor::InputLogicEvent(CEditorBaseObject* object, unsigned int event, CEditorBaseObject* initiator)
{
    if (object)
    {
        CParticleEmitterWrapper* target = dynamic_cast<CParticleEmitterWrapper*>(object);
        if (target)
        {
            switch (event)
            {
            case 2: target->setVisible(true); target->setEnabled(true); break;
            case 3: target->setEnabled(false); break;
            }
            CPositionableObjectDescriptor::InputLogicEvent(object, event, initiator);
        }
    }
}
