void CGameClient::notifyOfDeletion(CItem* object)
{
    if (m_targetItem.getObject() == object) m_targetItem.setObject(NULL);
    if (m_selectedItem.getObject() == object) m_selectedItem.setObject(NULL);
    if (m_pGameUI) m_pGameUI->notifyOfDeletion(object);
}
