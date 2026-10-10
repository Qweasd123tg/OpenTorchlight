CollisionModelRef* CMasterResourceManager::getCollisionModel(std::wstring name)
{
    for (unsigned int i = 0; i < m_collisionModels.size(); ++i)
        if (m_collisionModels[i]->m_sUnknown20 == name) return m_collisionModels[i];
    return NULL;
}
