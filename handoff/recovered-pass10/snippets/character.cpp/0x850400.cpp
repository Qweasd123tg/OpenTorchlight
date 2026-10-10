void CCharacter::setWardrobeGlovesMesh(std::wstring value)
{
    if (m_wardrobe) {
        { std::wstring copied(value); m_wardrobe->m_meshes[1].assign(copied); }
        m_wardrobe->update(m_inventory);
        getBones();
    }
}
