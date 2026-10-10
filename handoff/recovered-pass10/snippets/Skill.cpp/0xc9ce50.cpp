const std::wstring& CSkill::getName()
{
    return m_property ? m_property->m_sName : EMPTY_WSTRING;
}
