std::wstring CCharacter::getWardrobeBootsMesh()
{
    if (m_wardrobe) return m_wardrobe->m_meshes[2];
    return EMPTY_WSTRING;
}
