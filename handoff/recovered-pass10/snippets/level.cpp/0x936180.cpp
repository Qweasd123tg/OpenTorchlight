void CLevel::clearPassabilityData()
{
    for (unsigned int x = 0; x < m_passWidth; ++x) {
        for (unsigned int y = 0; y < m_passHeight; ++y) {
            m_mapPassability[x][y] = -1;
            m_objectPassability[x][y] = 0;
        }
    }
}
