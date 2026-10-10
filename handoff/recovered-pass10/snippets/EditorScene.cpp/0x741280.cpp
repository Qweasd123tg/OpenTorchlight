unsigned int CEditorScene::GetNumberOfObjectsInScene(bool includeOwner)
{
    if (includeOwner && getSceneOwner()) return getSceneOwner()->GetNumberOfObjectsInScene(true) + m_Objects.size();
    return m_Objects.size();
}
