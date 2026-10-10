unsigned int CGenericModel::getKeyCount(unsigned int animation)
{
    unsigned int result = 0;
    if (m_animationSet) {
        result = m_animationSet->m_lAnimationGroups.size();
        if (animation < m_animationSet->m_lAnimationGroups.size()) result = m_animationSet->m_lAnimationGroups[animation].size();
    }
    return result;
}
