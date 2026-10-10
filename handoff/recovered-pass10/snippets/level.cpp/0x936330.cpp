void CLevel::updateLayouts(float elapsed)
{
    if (elapsed == 0.0f) return;
    int count = m_RoomScenes.size();
    for (int i = 0; i < count; ++i) m_RoomScenes[i]->update(elapsed);
}
