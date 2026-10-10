bool CLevel::addListenerToUnit(CBaseUnit* unit, iUnitObserver* observer)
{
    if (unit) return addListenerToUnit(unit->getGuid(), observer);
    return false;
}
