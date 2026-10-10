void CEditorScene::AddDescriptor(CDescriptor* descriptor)
{
    if (descriptor && m_pDescriptorManager) m_pDescriptorManager->AddDescriptor(descriptor);
}
