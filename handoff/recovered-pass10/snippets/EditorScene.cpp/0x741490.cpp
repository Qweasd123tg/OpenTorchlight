CEditorBaseObject* CEditorScene::CreateObjectByDescriptor(const std::wstring& name, bool load)
{
    if (m_pDescriptorManager) return CreateObjectByDescriptor(m_pDescriptorManager->GetDescriptor(name.c_str(), true), NULL, NULL, load);
    return NULL;
}
