void CPlayer::setLeftMappedFunctionSkill(unsigned int index, long long guid)
{
    for (int i = 0; i < 12; ++i) if (m_leftFunctionSkills[i] == guid) m_leftFunctionSkills[i] = -1;
    m_leftFunctionSkills[index] = guid;
    if (guid != -1) m_functionSkills[index] = -1;
}
