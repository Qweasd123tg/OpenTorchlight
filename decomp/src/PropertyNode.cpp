#include "PropertyNode.h"

void CPropertyNode::setPropertyNodeType(unsigned int type)
{
    m_iPropertyNodeType = type;
}

void CPropertyNode::createEntity()
{
    
}

void CPropertyNode::setEnabled(bool enabled)
{
    m_bEnabled = enabled;
    if (enabled)
        BroadcastEvent(6);
    else
        BroadcastEvent(7);
    switch (m_iPropertyNodeType) {
    case 6: jumpDownLogic(); break;
    case 8:
    case 9: updatePathNodes(); break;
    default: break;
    }
}

void CPropertyNode::orientationUpdated(const Ogre::Matrix4&)
{
    updateBoundingBox();
}

void CPropertyNode::positionUpdated(const Ogre::Vector3&)
{
    updateBoundingBox();
}
