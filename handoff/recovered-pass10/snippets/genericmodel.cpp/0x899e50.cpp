int CGenericModel::findKey(int animation, CKeyframe* key)
{
    for (unsigned int i = 0; i < m_animationSet->m_lAnimationGroups[animation].size(); ++i)
        if (m_animationSet->m_lAnimationGroups[animation][i] == key) return i;
    return -1;
}
