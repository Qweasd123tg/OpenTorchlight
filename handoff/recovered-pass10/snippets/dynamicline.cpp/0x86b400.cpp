void CDynamicLine::addPoint(const Ogre::Vector3& point)
{
    m_points.push_back(point);
    m_dirty = true;
}
