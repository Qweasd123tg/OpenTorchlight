#ifndef DUNGEONOBJECT_H
#define DUNGEONOBJECT_H

#include "PositionableObject.h"
#include <string>

class CDungeonObject : public CPositionableObject
{
public:
    CDungeonObject(CResourceManager* resourceManager);
    virtual ~CDungeonObject();
    void createEntity();
    void clearHistory();

private:
    std::wstring m_sDungeon;
    CResourceManager* m_pResourceManager;

public:
    // Inline accessors behind the descriptors' property functions.
    const std::wstring& getDungeon() const { return m_sDungeon; }
    void setDungeon(const std::wstring& value) { m_sDungeon = value; }
};

#endif
