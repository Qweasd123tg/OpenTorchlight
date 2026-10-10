void CLevel::removeListenerFromUnit(long long guid, iUnitObserver* observer)
{
    if (!observer) return;
    std::map<long long, TArrayList<iUnitObserver*>*>::iterator it = m_unitObservers.find(guid);
    if (it != m_unitObservers.end()) it->second->remove(observer);
}
