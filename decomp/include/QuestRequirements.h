#ifndef QUESTREQUIREMENTS_H
#define QUESTREQUIREMENTS_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include "DataGroup.h"
#include "RunicCore.h"
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
    void* m_pUnknown30;
    unsigned char m_Unknown38[0x18] __attribute__((aligned(8)));
};

#endif
