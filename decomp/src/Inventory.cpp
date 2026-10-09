#include "Inventory.h"


int CInventory::getPaneSize(EINVENTORY_PANES pane)
{
    unsigned int index = getPaneIndex(pane);
    if (index == m_paneStarts.size() - 1)
        return m_iUnknown28 - m_paneStarts[index];
    return m_paneStarts[index + 1] - m_paneStarts[index];
}

bool CInventory::slotIsInPane(unsigned int pane, int slot)
{
    int start = m_paneStarts[pane];
    int end = m_iUnknown28;
    if (pane < m_paneStarts.size() - 1)
        end = m_paneStarts[pane + 1];
    return slot >= start && slot < end;
}

int CInventory::getItemPane(unsigned int slot)
{
    for (unsigned int i = 0; i < m_paneStarts.size(); ++i)
    {
        if (slot >= m_paneStarts[i] &&
            (i == m_paneStarts.size() - 1 || slot < m_paneStarts[i + 1]))
            return i;
    }
    return 0;
}

void CInventory::addSection(EINVENTORY_PANES pane, unsigned int size)
{
    m_panes.push_back(pane);
    m_paneStarts.push_back(m_iUnknown28);
    m_iUnknown28 += size;
}


