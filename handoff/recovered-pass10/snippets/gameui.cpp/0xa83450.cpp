void CGameUI::closeRight()
{
    for (unsigned int i = 0; i < m_submenus.size(); ++i)
        if (m_submenus[i]->isRight()) m_submenus[i]->setOpen(false);
}
