void CWeaponTrail::setWeaponEntity(Ogre::Entity* entity)
{
    m_weaponEntity = entity;
    if (entity) m_weaponNode = entity->getParentNode();
    else { m_weaponNode = NULL; m_weaponEntity = NULL; }
}
