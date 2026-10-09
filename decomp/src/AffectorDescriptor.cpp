#include "AffectorDescriptor.h"

void CAffectorDescriptor::deleteNotification()
{
    for (unsigned int i = 0; i < m_Objects.size(); ++i)
        DescriptorObjectBeingDeleted(m_Objects[i]);
}

CAffectorDescriptor::~CAffectorDescriptor()
{
}
