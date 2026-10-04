#ifndef LEVELSTATE_H
#define LEVELSTATE_H

#include <stdio.h>
#include <string>

#include "Character.h"
#include "Item.h"
#include "Level.h"
#include "RunicCore.h"
#include "TArrayList.h"

class CAutomap;
class CCharacterSaveState;
class CFormationNode;
class CFormationNodeSaveAndLoad;
class CItemSaveState;
class CLogicNodeState;

class CLevelState : public CRunicCore
{
public:
    virtual ~CLevelState();

    CLevelState(int iLevelId);

    void restoreAutomap(CAutomap *pAutomap);
    void addAutomap(CAutomap *pAutomap);
    void addFormations(TArrayList<CFormationNode *> *pFormations,
                       CLevel &Level);
    void save(_IO_FILE *pFile);
    void addLogicState(CLogicNodeState *pLogicState, CLevel &Level);
    void addItem(CItem &Item);
    void addCharacter(CCharacter &Character, CLevel &Level);
    void load(_IO_FILE *pFile, unsigned int uiVersion);

    int m_iLevelId;
    unsigned char m_gap14[0x4] __attribute__((aligned(4)));

    std::wstring m_sLevelName;
    TArrayList<CCharacterSaveState *> m_lCharacters;
    TArrayList<CItemSaveState *> m_lItems;
    TArrayList<CLogicNodeState *> m_lLogicStates;
    TArrayList<std::wstring> m_lLevelStrings;
    TArrayList<CFormationNodeSaveAndLoad *> m_lFormations;

    int m_iStateVersion;
    int m_iAutomapWidth;
    int m_iAutomapHeight;
    unsigned char m_gapA4[0x4] __attribute__((aligned(4)));
    void *m_pAutomapData;
    bool m_bUnknownB0;
    bool m_bUnknownB1;
};

#endif
