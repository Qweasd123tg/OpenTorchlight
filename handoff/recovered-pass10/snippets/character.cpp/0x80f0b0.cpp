std::wstring CCharacter::getWardrobeShoulderMesh()
{
    if (m_wardrobe) return m_wardrobe->m_meshes[4];
    return EMPTY_WSTRING;
}
