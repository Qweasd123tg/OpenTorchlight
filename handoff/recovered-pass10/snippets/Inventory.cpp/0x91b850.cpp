bool CInventory::canUseEquipment(CEquipment* equipment, CCharacter* target)
{
    if (!equipment) return false;
    if (!target) target = m_pPositionableObject;
    return equipment->canUseOnTarget(m_pPositionableObject, target);
}
