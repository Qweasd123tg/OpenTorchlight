CAnimationSet* CMasterResourceManager::getAnimationSet(std::wstring name)
{
    for (unsigned int i = 0; i < m_animationSets.size(); ++i)
        if (m_animationSets[i]->m_wsName == name) return m_animationSets[i];
    return NULL;
}
