CollisionModelRef* CMasterResourceManager::getCollisionModel(CCollisionModel* model)
{
    for (unsigned int i = 0; i < m_collisionModels.size(); ++i)
        if (m_collisionModels[i]->m_pCollisionModel == model) return m_collisionModels[i];
    return NULL;
}
