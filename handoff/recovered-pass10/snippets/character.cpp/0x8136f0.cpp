float CCharacter::getEffectValueWithoutInventory(EEFFECT_TYPE type, EDAMAGE_TYPES damage)
{
    return m_pEffectManager ? m_pEffectManager->getEffectValue(type, damage) : 0.0f;
}
