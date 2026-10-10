void CCharacter::toggleSecondaryWeaponSet()
{
    m_inventory->swapWeaponSet();
    m_secondaryWeaponSet = !m_secondaryWeaponSet;
}
