void CPlayer::clearSkillFunctionMap()
{
    for (int i = 0; i < 12; ++i) { m_functionSkills[i] = -1; m_leftFunctionSkills[i] = -1; }
}
