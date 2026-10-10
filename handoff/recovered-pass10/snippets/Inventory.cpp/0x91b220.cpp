bool CInventory::isEquipmentInInventory(CEquipment* equipment)
{
    for (unsigned int i = 0; i < m_equipmentRefs.size(); ++i) {
        CEquipmentRef* ref = m_equipmentRefs[i];
        if (ref && ref->m_pEquipment == equipment) return true;
    }
    return false;
}
