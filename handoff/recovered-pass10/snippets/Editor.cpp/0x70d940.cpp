void CEditor::FlyToPositionLookingAtPos(Ogre::Vector3 position, Ogre::Vector3 target)
{
    if (m_pCameraController) m_pCameraController->FlyTo(position, target);
}
