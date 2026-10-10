void CGameClient::mouseEvent(unsigned int event, unsigned int button)
{
    if (m_pGameUI) m_pGameUI->mouseEvent(event, button);
    m_mouse.mouseEvent(event, button);
}
