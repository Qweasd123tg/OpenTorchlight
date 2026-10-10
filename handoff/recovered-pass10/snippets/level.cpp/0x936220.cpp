bool CLevel::positionPassable(int x, int y)
{
    if (y < 0 || x < 0 || x >= static_cast<int>(m_passWidth) || y >= static_cast<int>(m_passHeight)) return false;
    return m_mapPassability[x][y] <= 0 && m_objectPassability[x][y] <= 0;
}
