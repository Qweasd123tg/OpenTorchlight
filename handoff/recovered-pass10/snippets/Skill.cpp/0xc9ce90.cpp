const std::wstring& CSkill::getDisplayName()
{
    return m_property ? m_property->m_sDisplayName : EMPTY_WSTRING;
}
