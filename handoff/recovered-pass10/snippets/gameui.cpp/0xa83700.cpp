bool CGameUI::handle_SkillSelectMouseOut(const CEGUI::EventArgs& event)
{
    const CEGUI::WindowEventArgs& e = static_cast<const CEGUI::WindowEventArgs&>(event);
    if (e.window)
    {
        m_foldoutSkillHovered = false;
        m_foldoutItemHovered = false;
        m_foldoutItemGuid = -1;
        m_foldoutSkillGuid = -1;
    }
    m_skillHovered = false;
    m_itemHovered = false;
    return true;
}
