bool CWeaponTrail::isVisible() const
{
    return m_segments.next != &m_segments;
}
