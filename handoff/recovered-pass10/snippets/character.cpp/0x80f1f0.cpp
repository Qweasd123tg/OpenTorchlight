std::wstring CCharacter::getModelPath()
{
    if (m_pUnitModel) return m_pUnitModel->m_sModelPath;
    return EMPTY_WSTRING;
}
