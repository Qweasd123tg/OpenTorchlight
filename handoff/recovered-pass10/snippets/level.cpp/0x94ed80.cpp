bool CLevel::rayCollision(const Ogre::Vector3& start, const Ogre::Vector3& end, Ogre::Vector3& hit, Ogre::Vector3& normal, bool flag)
{
    unsigned int type;
    Ogre::Vector3 extra;
    return rayCollision(start, end, hit, normal, type, extra, flag);
}
