void EditorResetCamera(float x, float y, float z)
{
    if (!gEditor->isActive()) return;
    gEditor->ResetCamera(Ogre::Vector3(x, y, z));
}
