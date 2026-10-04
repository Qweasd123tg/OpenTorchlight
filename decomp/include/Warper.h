#ifndef WARPER_H
#define WARPER_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include "PositionableObject.h"
#include "ResourceManager.h"

class CWarper : public CPositionableObject
{
public:
    virtual ~CWarper();
    virtual void setEnabled(bool);
    virtual bool getEnabled();
    void createEntity();
    CWarper(CResourceManager*);
    void activate();

    // fields
    int m_iLevelDelta;
    int m_iLevelDepth;
    bool m_bEnabled;
    bool m_bWaypoint;
    unsigned char m_gap10A[0x6];
    void* m_pDungeon;
    void* m_pWarpName;
    CResourceManager* m_pResourceManager;
};

#endif
