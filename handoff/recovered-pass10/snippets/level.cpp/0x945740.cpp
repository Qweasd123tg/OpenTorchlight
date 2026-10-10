Ogre::Vector3 CLevel::randomOpenItemPosition(const Ogre::Vector3& position, float radius, bool flag)
{
    return randomOpenItemPositionRange(position, 0.0f, radius, flag);
}
