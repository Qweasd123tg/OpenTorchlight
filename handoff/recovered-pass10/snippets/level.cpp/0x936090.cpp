void CLevel::removeListenerFromUnit(CBaseUnit* unit, iUnitObserver* observer)
{
    if (observer && unit) removeListenerFromUnit(unit->getGuid(), observer);
}
