void CEditor::SetRenderWindowHasFocus(bool focused)
{
    if (m_pCameraController) m_pCameraController->m_bUnknown178 = focused;
    m_bRenderWindowHasFocus = focused;
}
