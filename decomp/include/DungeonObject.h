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
};

#endif
