BatchModelRef* CMasterResourceManager::getBatchModel(CGenericModel* model)
{
    for (unsigned int i = 0; i < m_batchModels.size(); ++i)
        if (m_batchModels[i]->m_pBatchModel == model) return m_batchModels[i];
    return NULL;
}
