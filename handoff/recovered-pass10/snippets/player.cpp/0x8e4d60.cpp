void CPlayer::calculateMaxMana()
{
    if (!m_manaGraph.empty()) {
        CGraph* graph = CGraphManager::getSingleton()->getGraph(m_manaGraph);
        if (graph) {
            m_maxManaBase = static_cast<int>(ceilf(graph->getValue(static_cast<float>(static_cast<int>(m_iUnitLevel)), 0)));
            if (m_fManaFloat > maxMana()) m_fManaFloat = maxMana();
        }
    }
}
