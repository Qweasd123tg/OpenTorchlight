void CMasterResourceManager::removeAnimationSet(CAnimationSet* model)
{
    CAnimationSet* found = getAnimationSet(model);
    if (found) --found->m_nAnimationCount;
}
