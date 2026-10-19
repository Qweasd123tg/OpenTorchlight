#ifndef QUESTREQUIREMENTS_H
#define QUESTREQUIREMENTS_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include "DataGroup.h"
#include "RunicCore.h"
#include <string>
#include "TArrayList.h"
class CQuest;

class CQuestRequirements : public CRunicCore
{
public:
    virtual ~CQuestRequirements();
    CQuestRequirements(CQuest*);
    long long parseRequirementTag(CDataGroup*);
    char questRequirmentsHaveBeenMet();

    // fields
    CDataGroup* m_pDataGroup;
    CQuest* m_pQuest;
    int m_iUnknown20;
    int m_iUnknown24;
    int m_iUnknown28;
    int m_iUnknown2C;
    std::wstring m_pUnknown30; // +0x30, ruleset
    TArrayList<TArrayList<std::wstring>*> m_Unknown38; // +0x38, three owning requirement lists
};

#endif
