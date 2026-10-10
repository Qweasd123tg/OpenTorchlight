int CPlayer::getSkillPointsAwardedForFameLevel(unsigned int level)
{
    if (!m_famePointsGraph.empty()) {
        CGraph* graph = CGraphManager::getSingleton()->getGraph(m_famePointsGraph);
        if (graph) return static_cast<int>(ceilf(graph->getValue(static_cast<float>(level), 0)));
    }
    return 0;
}
