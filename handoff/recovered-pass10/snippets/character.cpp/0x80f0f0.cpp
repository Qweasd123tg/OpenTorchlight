std::wstring CCharacter::getWardrobeHelmMesh()
{
    if (m_wardrobe) return m_wardrobe->m_meshes[3];
    return EMPTY_WSTRING;
}
