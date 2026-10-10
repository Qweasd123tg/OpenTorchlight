bool CGameUI::handle_SkillMouseOut(const CEGUI::EventArgs& event)
{
    const CEGUI::WindowEventArgs& e = static_cast<const CEGUI::WindowEventArgs&>(event);
    if (e.window)
    {
        if (e.window->getID() == 1000) m_itemHovered = false;
        else m_skillHovered = false;
    }
    return true;
}
