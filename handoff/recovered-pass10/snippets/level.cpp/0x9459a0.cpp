Ogre::Vector3 CLevel::randomOpenPosition(const Ogre::Vector3& position, float radius, bool flag)
{
    return randomOpenPositionRange(position, 0.0f, radius, flag);
}
