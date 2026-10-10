CEquipment* CCharacter::getWeaponInRightHand()
{
    if (!m_inventory) return NULL;
    return m_inventory->getEquipmentEquippedAt(static_cast<EEQUIP_LOCATIONS>(0));
}
