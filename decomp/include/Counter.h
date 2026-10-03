#ifndef COUNTER_H
#define COUNTER_H

#include <string>

#include "EditorBaseObject.h"

// Enumerator names are ours; values follow gCOUNTER_TYPE_NAMES.
enum ECOUNTER_TYPES
{
    COUNTER_ACTIVATE_ONCE,
    COUNTER_ACTIVATE_AND_RESET,
    COUNTER_ACTIVATE_ON_EACH_ADD,
    COUNTER_ACTIVATE_ON_EACH_ADD_AND_RESET,
    COUNTER_ACTIVATE_ON_EACH_SUBTRACT,
    COUNTER_ACTIVATE_ON_EACH_SUBTRACT_AND_RESET,
    COUNTER_TYPE_COUNT
};

static const std::wstring gCOUNTER_TYPE_NAMES[] =
{
    L"Activate only once",
    L"Activate and reset",
    L"Activate on each add",
    L"Activate on each add and reset",
    L"Activate on each subtract",
    L"Activate on each subtract and reset",
};

// Logic object holding a value that inputs add to or subtract from; fires
// OUTPUT_EVENT_ACTIVATED on reaching the target or on each change, by type.
class CCounter : public CEditorBaseObject
{
public:
    CCounter();
    virtual ~CCounter();

    void reset();
    void updateCounter();
    void subtract(int amount);
    void add(int amount);

private:
    int m_iTarget;
    int m_iStartValue;
    int m_iValue;
    ECOUNTER_TYPES m_eType;
    bool m_bEnabled;
};

#endif
