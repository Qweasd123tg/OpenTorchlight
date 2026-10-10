bool CLevel::snapToValidGround(Ogre::Vector3& position, float height)
{
    Ogre::Vector3 start = position;
    Ogre::Vector3 end = position;
    start.y += 10.0f;
    end.y -= 100.0f;
    Ogre::Vector3 hit, normal, extra;
    unsigned int type;
    if (rayCollision(start, end, hit, normal, type, extra, false) && type != 100) {
        position = hit; position.y += height; return true;
    }
    return false;
}
