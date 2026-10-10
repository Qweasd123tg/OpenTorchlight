float CShape::getMinRadiusAtPercent(float percent)
{
    if (m_minRadius) {
        if (m_radiusOnEdge) return getMaxRadiusAtPercent(percent);
        return m_minRadius->getValue(NULL, percent);
    }
    return 1.0f;
}
