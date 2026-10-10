int CPlayer::getStatsPointsAwardedForLevel(unsigned int level)
{
    if (!m_statPointsGraph.empty()) {
        CGraph* graph = CGraphManager::getSingleton()->getGraph(m_statPointsGraph);
        if (graph) return static_cast<int>(ceilf(graph->getValue(static_cast<float>(level), 0)));
    }
    return 0;
}
