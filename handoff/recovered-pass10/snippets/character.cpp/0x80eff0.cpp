std::wstring CCharacter::getWardrobeBootsTexture()
{
    if (m_wardrobe) return m_wardrobe->m_textures[2];
    return EMPTY_WSTRING;
}
