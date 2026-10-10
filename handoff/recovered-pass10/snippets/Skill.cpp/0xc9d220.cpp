float CSkill::getCoolDown()
{
    return m_property ? m_property->getCoolDown() : 1.0f;
}
