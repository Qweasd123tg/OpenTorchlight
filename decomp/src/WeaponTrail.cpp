#include "WeaponTrail.h"
#include <OgreVertexIndexData.h>



// Imported source candidates; historical status is not fresh acceptance.
void CWeaponTrail::clear()
{
}

void CWeaponTrail::setVisible(bool visible)
{
    m_object->setVisible(visible);
    if (visible) m_object->setRenderQueueGroup(91);
}

void CWeaponTrail::setWeaponEntity(Ogre::Entity* entity)
{
    m_weaponEntity = entity;
    if (entity) m_weaponNode = entity->getParentNode();
    else { m_weaponNode = NULL; m_weaponEntity = NULL; }
}

void CWeaponTrail::setWeaponNode(Ogre::Node* node)
{
    m_weaponNode = node;
    m_weaponEntity = NULL;
}

void CWeaponTrail::setSegmentStartInitialColourValue(const Ogre::ColourValue& colour)
{
    m_startColour = colour;
}

const Ogre::ColourValue& CWeaponTrail::getSegmentStartInitialColourValue() const
{
    return m_startColour;
}

void CWeaponTrail::setSegmentEndInitialColourValue(const Ogre::ColourValue& colour)
{
    m_endColour = colour;
}

const Ogre::ColourValue& CWeaponTrail::getSegmentEndInitialColourValue() const
{
    return m_endColour;
}

bool CWeaponTrail::isActive() const
{
    return m_active;
}

bool CWeaponTrail::isVisible() const
{
    return m_segments.next != &m_segments;
}

void CWeaponTrail::setMaterialName(const std::string& name)
{
    m_material = name;
    if (m_object) m_object->setMaterialName(0, m_material);
}
