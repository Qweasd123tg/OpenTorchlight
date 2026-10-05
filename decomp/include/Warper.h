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

public:
    // Inline accessors behind the descriptors' property functions.
    void setLevelDelta(int value) { m_iLevelDelta = value; }
    void setLevelDepth(int value) { m_iLevelDepth = value; }
    void setWaypoint(bool value) { m_bWaypoint = value; }
    bool getWaypoint() const { return m_bWaypoint; }
    int getLevelDepth() const { return m_iLevelDepth; }
    int getLevelDelta() const { return m_iLevelDelta; }
    const std::wstring& getWarpName() const { return m_sWarpName; }
    const std::wstring& getDungeon() const { return m_sDungeon; }
    void setWarpName(const std::wstring& value) { m_sWarpName = value; }
    void setDungeon(const std::wstring& value) { m_sDungeon = value; }
};

#endif
