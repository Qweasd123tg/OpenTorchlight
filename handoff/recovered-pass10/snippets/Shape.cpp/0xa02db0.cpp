void CShape::setMinRadius(const float* values, unsigned int count)
{
    if (m_minRadius) { delete m_minRadius; m_minRadius = NULL; }
    m_minRadius = getDynPropFromArray(values, count);
}
