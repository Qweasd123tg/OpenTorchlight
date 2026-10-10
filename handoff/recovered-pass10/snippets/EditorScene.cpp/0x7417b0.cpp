CEditorBaseObject* CEditorScene::CreateObjectByDescriptor(unsigned int index, CEditorBaseObject* parent, CEditorBaseObject* owner, bool load)
{
    if (m_pDescriptorManager) return CreateObjectByDescriptor(m_pDescriptorManager->GetDescriptor(index), parent, owner, load);
    return NULL;
}
