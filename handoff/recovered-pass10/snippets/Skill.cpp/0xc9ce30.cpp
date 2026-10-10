const std::wstring& CSkill::getSkillIconInactive()
{
    return m_property ? m_property->m_sSkillIconInactive : EMPTY_WSTRING;
}
