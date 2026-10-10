const std::wstring& CSkill::getSkillIcon()
{
    return m_property ? m_property->m_sSkillIcon : EMPTY_WSTRING;
}
