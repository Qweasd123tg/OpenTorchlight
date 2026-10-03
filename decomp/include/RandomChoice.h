#ifndef RANDOMCHOICE_H
#define RANDOMCHOICE_H

#include <string>

#include "EditorBaseObject.h"
#include "OutputEvents.h"

// Enumerator names are ours; values follow gRANDOMCHOICE_TYPE_NAMES.
enum ERANDOMCHOICE_TYPES
{
    RANDOMCHOICE_WEIGHT,
    RANDOMCHOICE_RANDOM,
    RANDOMCHOICE_COUNT
};

static const std::wstring gRANDOMCHOICE_TYPE_NAMES[] =
{
    L"WEIGHT",
    L"RANDOM",
};

// Logic object that fires one of five outputs: by weight (a number of rolls)
// or independently by percentage.
class CRandomChoice : public CEditorBaseObject
{
public:
    enum { OUTPUT_COUNT = 5 };

    CRandomChoice();
    virtual ~CRandomChoice();

    void roll();

private:
    ERANDOMCHOICE_TYPES m_eRandomType;
    unsigned int m_iOutputs[OUTPUT_COUNT];
    int m_iRandomValues[OUTPUT_COUNT];
    bool m_bEnabled;
    unsigned int m_iCount;
};

#endif
