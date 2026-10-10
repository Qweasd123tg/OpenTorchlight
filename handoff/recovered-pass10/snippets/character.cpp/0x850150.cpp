void CCharacter::setWardrobeChestTexture(std::wstring value)
{
    if (m_wardrobe) {
        m_wardrobe->setBaseTexture(static_cast<EWardrobeSlot>(0), value);
        m_wardrobe->update(m_inventory);
        getBones();
    }
}
