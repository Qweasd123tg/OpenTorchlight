float CShape::getRadiusAtPercent(float percent)
{
    float minimum = getMinRadiusAtPercent(percent);
    float maximum = getMaxRadiusAtPercent(percent);
    if (m_radiusMode == 2) return Ogre::Math::RangeRandom(minimum, maximum);
    return minimum + (maximum - minimum) * percent;
}
