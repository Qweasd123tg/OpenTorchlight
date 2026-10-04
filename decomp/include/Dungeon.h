#ifndef DUNGEON_H
#define DUNGEON_H

#include <string>

#include "Randomizer.h"
#include "RunicCore.h"
#include "TArrayList.h"

class CDataGroup;
class CGameClient;
class CLevelTemplateData;

class CDungeon : public CRunicCore
{
public:
    virtual ~CDungeon();

    CDungeon();

    CLevelTemplateData* getStrataTemplate(unsigned int depth);
    CLevelTemplateData* getRandomLevelTemplateData();
    CLevelTemplateData* getLevelTemplateDataForDepth(CGameClient* gameClient,
                                                     unsigned int depth);
    bool loadDungeon(const wchar_t* filename);

    TArrayList<CLevelTemplateData*> m_levelTemplateData;
    TArrayList<TArrayList<std::wstring>*> m_mustBeCompleted;
    TArrayList<TArrayList<std::wstring>*> m_mustBeCompletedOrActive;
    int m_iDungeonIndex;
    std::wstring m_sName;
    std::wstring m_sDisplayName;
    float m_fMonsterLevelMultiplier;
    int m_iPlayerLevelMatchMin;
    int m_iPlayerLevelMatchMax;
    int m_iPlayerLevelMatchOffset;
    std::wstring m_sParentDungeon;
    bool m_bVolatile;
    bool m_bBottomless;
    CRandomizer m_randomizer;
    CDataGroup* m_pDungeonData;
    TArrayList<CDataGroup*> m_strataData;
};

#endif
