void CDynamicLine::setPoint(unsigned short index, const Ogre::Vector3& point)
{
    m_points[index] = point;
    m_dirty = true;
}
