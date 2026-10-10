void CCharacter::setWardrobeBootsMesh(std::wstring value)
{
    if (m_wardrobe) {
        { std::wstring copied(value); m_wardrobe->m_meshes[2].assign(copied); }
        m_wardrobe->update(m_inventory);
        getBones();
    }
}
