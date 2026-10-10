void CPlayer::setMappedFunctionSkill(unsigned int index, long long guid)
{
    for (int i = 0; i < 12; ++i) if (m_functionSkills[i] == guid) m_functionSkills[i] = -1;
    m_functionSkills[index] = guid;
    if (guid != -1) m_leftFunctionSkills[index] = -1;
}
