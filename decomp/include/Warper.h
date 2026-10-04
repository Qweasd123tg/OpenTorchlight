#ifndef WARPER_H
#define WARPER_H

// Level transition logic; size 0x128 from original allocation at 0x68efad.

#include <string>
#include "PositionableObject.h"
#include "ResourceManager.h"

class CWarper : public CPositionableObject
{
public:
    virtual ~CWarper();
    virtual void setEnabled(bool enabled) { m_bEnabled = enabled; }
    virtual bool getEnabled() { return m_bEnabled; }
    void createEntity();
    CWarper(CResourceManager*);
    void activate();

    // fields
    int m_iLevelDelta;
    int m_iLevelDepth;
    bool m_bEnabled;
    bool m_bWaypoint;
    unsigned char m_gap10A[0x6];
    std::wstring m_sDungeon;
    std::wstring m_sWarpName;
    CResourceManager* m_pResourceManager;
};

#endif
