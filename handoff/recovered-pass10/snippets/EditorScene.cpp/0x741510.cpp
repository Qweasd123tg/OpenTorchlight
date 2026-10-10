CDescriptor* CEditorScene::GetDescriptorInSceneByName(const wchar_t* name, bool create)
{
    if (m_pDescriptorManager) return m_pDescriptorManager->GetDescriptor(name, create);
    return NULL;
}
