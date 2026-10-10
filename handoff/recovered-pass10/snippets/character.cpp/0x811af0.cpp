void CCharacter::updateSkill(float elapsed)
{
    if (m_inventory) m_inventory->updateSkillManagers(elapsed);
}
