int CSkill::getMaximumDamage()
{
    if (!m_property) return 0;
    float minimum = 0.0f;
    float maximum = 0.0f;
    m_property->addMinAndMaxValuesOfAnEffect(m_resources, 0x34, minimum, maximum);
    return static_cast<int>(ceilf(maximum));
}
