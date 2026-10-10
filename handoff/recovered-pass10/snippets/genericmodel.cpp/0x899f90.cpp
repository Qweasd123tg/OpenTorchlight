CKeyframe* CGenericModel::getKeyFrame(unsigned int animation, unsigned int key)
{
    if (!m_animationSet) return NULL;
    if (animation >= m_animationSet->m_lAnimationGroups.size()) return NULL;
    if (key >= m_animationSet->m_lAnimationGroups[animation].size()) return NULL;
    return m_animationSet->m_lAnimationGroups[animation][key];
}
