CAnimationSet* CMasterResourceManager::getAnimationSet(CAnimationSet* model)
{
    for (unsigned int i = 0; i < m_animationSets.size(); ++i)
        if (m_animationSets[i] == model) return m_animationSets[i];
    return NULL;
}
