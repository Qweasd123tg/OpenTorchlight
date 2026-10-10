const std::wstring& CSkill::getSkillUsageDescription()
{
    return m_property ? m_property->m_sUsageDescription : EMPTY_WSTRING;
}
