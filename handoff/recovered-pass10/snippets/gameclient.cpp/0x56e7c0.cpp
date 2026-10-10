void CGameClient::notifyOfDeletion(CCharacter* object)
{
    if (m_targetCharacter.getObject() == object) m_targetCharacter.setObject(NULL);
    if (m_selectedCharacter.getObject() == object) m_selectedCharacter.setObject(NULL);
    if (m_pGameUI) m_pGameUI->notifyOfDeletion(object);
}
