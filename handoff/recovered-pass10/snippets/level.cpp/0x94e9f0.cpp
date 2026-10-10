bool CLevel::sightUnobstructed(const Ogre::Vector3& start, const Ogre::Vector3& end, bool flag)
{
    Ogre::Vector3 hit, normal, extra;
    unsigned int type;
    return !rayCollision(start, end, hit, normal, type, extra, flag);
}
