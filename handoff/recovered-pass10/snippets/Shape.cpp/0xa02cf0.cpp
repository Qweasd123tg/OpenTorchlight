void CShape::setAngleOffset(const float* values, unsigned int count)
{
    if (m_angleOffset) { delete m_angleOffset; m_angleOffset = NULL; }
    m_angleOffset = getDynPropFromArray(values, count);
}
