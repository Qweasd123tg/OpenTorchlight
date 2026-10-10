void CWeaponTrail::setMaterialName(const std::string& name)
{
    m_material = name;
    if (m_object) m_object->setMaterialName(0, m_material);
}
