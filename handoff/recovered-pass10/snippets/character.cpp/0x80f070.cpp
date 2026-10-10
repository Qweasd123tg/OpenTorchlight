std::wstring CCharacter::getWardrobeChestTexture()
{
    if (m_wardrobe) return m_wardrobe->m_textures[0];
    return EMPTY_WSTRING;
}
