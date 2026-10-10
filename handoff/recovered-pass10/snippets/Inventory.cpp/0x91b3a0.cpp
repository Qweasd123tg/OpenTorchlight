CEquipmentRef* CInventory::getEquipmentRefInSlot(unsigned int slot)
{
    for (unsigned int i = 0; i < m_equipmentRefs.size(); ++i) {
        CEquipmentRef* ref = m_equipmentRefs[i];
        if (ref && ref->m_slot == slot) return ref;
    }
    return NULL;
}
