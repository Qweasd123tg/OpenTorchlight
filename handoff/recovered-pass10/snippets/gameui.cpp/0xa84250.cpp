void CGameUI::setRightButtonPressed()
{
    m_mouse.mouseEvent(0x204, 0);
    m_mouse.capture();
}
