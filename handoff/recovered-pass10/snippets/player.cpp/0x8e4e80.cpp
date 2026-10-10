int CPlayer::getSkillPointsAwardedForLevel(unsigned int level)
{
    if (!m_skillPointsGraph.empty()) {
        CGraph* graph = CGraphManager::getSingleton()->getGraph(m_skillPointsGraph);
        if (graph) return static_cast<int>(ceilf(graph->getValue(static_cast<float>(level), 0)));
    }
    return 0;
}
