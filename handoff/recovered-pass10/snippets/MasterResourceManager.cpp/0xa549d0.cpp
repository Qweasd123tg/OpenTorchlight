int CMasterResourceManager::experienceGate(int level)
{
    if (!level) return 0;
    if (level > m_experienceGraph->getControlPoints()) level = m_experienceGraph->getControlPoints();
    return static_cast<int>(m_experienceGraph->getValue(static_cast<float>(level), 0));
}
