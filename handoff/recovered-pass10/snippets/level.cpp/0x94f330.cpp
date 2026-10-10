bool CLevel::sphereCollision(const Ogre::Vector3& start, const Ogre::Vector3& end, float radius, Ogre::Vector3& position, Ogre::Vector3& hit, Ogre::Vector3& normal)
{
    unsigned int type;
    Ogre::Vector3 extra;
    return sphereCollision(start, end, radius, position, hit, normal, type, extra);
}
