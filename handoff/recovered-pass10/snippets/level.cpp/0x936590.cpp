void CLevel::setNPCAutomapBillboardVisible(Ogre::Billboard* billboard, bool visible)
{
    if (billboard && m_automap) m_automap->setNPCBillboardVisible(billboard, visible);
}
