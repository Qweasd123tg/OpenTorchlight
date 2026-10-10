void CMasterResourceManager::removeCollisionModel(CCollisionModel* model)
{
    CollisionModelRef* found = getCollisionModel(model);
    if (found) --found->m_referenceCount;
}
