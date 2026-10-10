 BatchModelRef::~BatchModelRef()
{
    if (m_pBatchModel) { delete m_pBatchModel; m_pBatchModel = NULL; }
}
