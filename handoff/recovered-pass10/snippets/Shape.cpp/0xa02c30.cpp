float CShape::getAngleOfReleaseAtPercent(float percent)
{
    if (m_releaseAngle) return m_releaseAngle->getValue(NULL, percent);
    return 360.0f;
}
