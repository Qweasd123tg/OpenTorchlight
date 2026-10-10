void CShape::setAngleOfRelease(const float* values, unsigned int count)
{
    if (m_releaseAngle) { delete m_releaseAngle; m_releaseAngle = NULL; }
    m_releaseAngle = getDynPropFromArray(values, count);
}
