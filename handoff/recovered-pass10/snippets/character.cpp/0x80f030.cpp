std::wstring CCharacter::getWardrobeGlovesTexture()
{
    if (m_wardrobe) return m_wardrobe->m_textures[1];
    return EMPTY_WSTRING;
}
