int CInventory::itemsInPane(EINVENTORY_PANES pane)
{
    unsigned int index = getPaneIndex(pane);
    int count = 0;
    for (unsigned int i = 0; i < m_equipmentRefs.size(); ++i) {
        unsigned int slot = m_equipmentRefs[i]->m_slot;
        if (slot >= m_paneStarts[index] && (index == m_paneStarts.size() - 1 || slot < m_paneStarts[index + 1])) ++count;
    }
    return count;
}
