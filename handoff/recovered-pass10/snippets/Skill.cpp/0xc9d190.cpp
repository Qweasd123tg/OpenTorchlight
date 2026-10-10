bool CSkill::canAffixesAndEffectsBeAppliedToUnit(CBaseUnit* unit, CCharacter* character)
{
    if (!m_property) return false;
    CSkillProperty* property = m_property;
    if (!character) character = getOwnerCharacter();
    return property->canAffixesAndEffectsBeAppliedToUnit(unit, character);
}
