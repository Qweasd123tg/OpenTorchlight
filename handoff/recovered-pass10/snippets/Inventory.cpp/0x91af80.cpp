void CInventory::removeListener(iInventoryListener* listener)
{
    if (listener) m_listeners.remove(listener);
}
