CEquipment* CCharacter::getWeaponInLeftHand()
{
    if (!m_inventory) return NULL;
    return m_inventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(1));
}
