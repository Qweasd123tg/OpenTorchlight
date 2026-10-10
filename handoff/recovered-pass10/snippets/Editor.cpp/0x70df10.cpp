void CEditor::keyEvent(unsigned int event, unsigned int code)
{
    if (m_pObjectManager) m_pObjectManager->keyEvent(event, code);
}
