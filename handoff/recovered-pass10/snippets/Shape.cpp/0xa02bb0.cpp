float CShape::getMaxRadiusAtPercent(float percent)
{
    if (m_maxRadius) return m_maxRadius->getValue(NULL, percent) * (1.0f + m_radiusExtraScale);
    return 1.0f;
}
