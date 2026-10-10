bool CGameUI::getConsoleIsOpen()
{
    return m_console ? m_console->getVisible() : false;
}
