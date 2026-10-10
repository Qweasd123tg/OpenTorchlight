void CDynamicLine::addPoint(float x, float y, float z)
{
    m_points.push_back(Ogre::Vector3(x, y, z));
    m_dirty = true;
}
