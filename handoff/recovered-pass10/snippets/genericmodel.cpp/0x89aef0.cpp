void CGenericModel::setAmbient(Ogre::ColourValue& colour)
{
    for (unsigned int i = 0; i < static_cast<unsigned int>(m_renderableStates.size()); ++i) {
        Ogre::Material* material = m_renderableStates[i].material;
        material->setAmbient(colour); material->setDiffuse(colour);
    }
}
