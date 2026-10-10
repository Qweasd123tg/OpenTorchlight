void CSkill::fillOutStatBonuses(float (&bonuses)[6], bool includeBase, unsigned int level)
{
    CSkillProperty* property = m_property;
    if (level > 0 && level != static_cast<unsigned int>(-1) && level <= m_levelProperties.size())
        property = m_levelProperties[level - 1];
    if (property) property->fillOutStatBonuses(bonuses, includeBase);
}
