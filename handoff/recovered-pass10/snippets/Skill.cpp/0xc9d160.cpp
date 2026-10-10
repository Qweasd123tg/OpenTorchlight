CCharacter* CSkill::getOwnerCharacter()
{
    if (m_pOwner && m_pOwner->m_eBaseUnitType == 0)
        return dynamic_cast<CCharacter*>(m_pOwner);
    return NULL;
}
