#ifndef IUNITOBSERVER_H
#define IUNITOBSERVER_H

class CBaseUnit;

// Partial: unit state values are not recovered yet.
enum EUNIT_STATES
{
};

// Receives unit state changes (implemented by CSkill).
class iUnitObserver
{
public:
    virtual ~iUnitObserver() {}

    virtual void unitStateChange(CBaseUnit* unit, EUNIT_STATES state) = 0;
};

#endif
