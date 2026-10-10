BatchModelRef* CMasterResourceManager::getBatchModel(std::wstring name)
{
    for (unsigned int i = 0; i < m_batchModels.size(); ++i)
        if (m_batchModels[i]->m_sBatchModelName == name) return m_batchModels[i];
    return NULL;
}
