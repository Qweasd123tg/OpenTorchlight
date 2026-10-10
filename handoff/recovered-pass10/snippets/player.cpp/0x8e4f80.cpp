void CPlayer::calculateMaxHP()
{
    if (!m_hpGraph.empty()) {
        CGraph* graph = CGraphManager::getSingleton()->getGraph(m_hpGraph);
        if (graph) {
            m_maxHPBase = static_cast<int>(ceilf(graph->getValue(static_cast<float>(static_cast<int>(m_iUnitLevel)), 0)));
            if (m_fHPFloat > maxHP()) m_fHPFloat = maxHP();
        }
    }
}
