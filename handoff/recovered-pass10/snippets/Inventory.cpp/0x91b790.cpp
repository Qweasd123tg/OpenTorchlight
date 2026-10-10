int CInventory::getMaxStackSizeOfEquipment(CEquipment* equipment)
{
    return equipment ? equipment->m_iUnknown23C : 0;
}
