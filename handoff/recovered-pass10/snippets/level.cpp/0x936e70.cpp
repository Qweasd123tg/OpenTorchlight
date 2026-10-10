void CLevel::removeListenerFromUnits(iUnitObserver* observer)
{
    if (!observer) return;
    for (std::map<long long, TArrayList<iUnitObserver*>*>::iterator it = m_unitObservers.begin(); it != m_unitObservers.end(); ++it) it->second->remove(observer);
}
