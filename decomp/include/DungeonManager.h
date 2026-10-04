#ifndef DUNGEONMANAGER_H
#define DUNGEONMANAGER_H

#include <string>

#include "RunicCore.h"
#include "TArrayList.h"

class CDungeon;

class CDungeonManager : public CRunicCore
{
public:
    virtual ~CDungeonManager();

    static CDungeonManager* getSingleton();

    void clear();
    void reload();

    CDungeon* getDungeonByName(std::wstring name);

    CDungeonManager(std::wstring path);

    std::wstring m_szDungeonPath;
    TArrayList<CDungeon*> m_lDungeons;
};

#endif
