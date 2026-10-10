void CWeaponTrail::setVisible(bool visible)
{
    m_object->setVisible(visible);
    if (visible) m_object->setRenderQueueGroup(91);
}
