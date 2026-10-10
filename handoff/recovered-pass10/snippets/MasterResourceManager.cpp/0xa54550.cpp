void CMasterResourceManager::removeBatchModel(CGenericModel* model)
{
    BatchModelRef* found = getBatchModel(model);
    if (found) --found->m_referenceCount;
}
