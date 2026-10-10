void CInventory::refreshEquipped()
{
    for (unsigned int i = 0; i < m_listeners.size(); ++i)
        m_listeners[i]->equipmentEquipped(NULL);
}
