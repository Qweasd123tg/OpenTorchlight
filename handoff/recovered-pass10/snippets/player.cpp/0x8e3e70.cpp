void CPlayer::clearSkillMap()
{
    for (int i = 0; i < 10; ++i) { m_skillMap[i] = -1; m_leftSkillMap[i] = -1; }
}
