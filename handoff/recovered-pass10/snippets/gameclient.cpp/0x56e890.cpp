void CGameClient::questEventFire(EQUEST_EVENTS event, CCharacter* character, CBaseUnit* target)
{
    if (m_questManager) m_questManager->questEventUpdate(event, character, target);
}
