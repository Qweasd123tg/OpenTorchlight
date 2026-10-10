void CShape::setMaxRadius(const float* values, unsigned int count)
{
    if (m_maxRadius) { delete m_maxRadius; m_maxRadius = NULL; }
    m_maxRadius = getDynPropFromArray(values, count);
}
