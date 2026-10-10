int CLevel::getRoomIndexThatPositionIsIn(const Ogre::Vector3& position)
{
    for (unsigned int i = 0; i < m_roomBounds.size(); ++i) if (m_roomBounds[i].contains(position)) return i;
    return -1;
}
