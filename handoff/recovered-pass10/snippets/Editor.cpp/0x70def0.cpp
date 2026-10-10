void CEditor::mouseEvent(unsigned int event, unsigned int code)
{
    if (m_pObjectManager) m_pObjectManager->mouseEvent(event, code);
}
