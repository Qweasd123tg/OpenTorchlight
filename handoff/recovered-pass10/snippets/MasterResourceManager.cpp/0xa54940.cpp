int CMasterResourceManager::fameGate(int level)
{
    if (!level) return 0;
    if (level > m_fameGraph->getControlPoints()) level = m_fameGraph->getControlPoints();
    return static_cast<int>(m_fameGraph->getValue(static_cast<float>(level), 0));
}
