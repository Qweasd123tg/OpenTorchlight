#ifndef LEVELSTATE_H
#define LEVELSTATE_H

#include <stdio.h>
#include <string>
#include <vector>

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
    std::vector<CCharacterSaveState *> m_lCharacters;
    std::vector<CItemSaveState *> m_lItems;
    std::vector<CLogicNodeState *> m_lLogicStates;
    std::vector<std::wstring> m_lLevelStrings;
    TArrayList<CFormationNodeSaveAndLoad *> m_lFormations;

    float m_iStateVersion; // +0x98: history timestamp; cleared to -1.0f by CPlayer.
    int m_iAutomapWidth;
    int m_iAutomapHeight;
    unsigned char m_gapA4[0x4] __attribute__((aligned(4)));
    void *m_pAutomapData;
    bool m_bUnknownB0;
    bool m_bUnknownB1;
};

#endif
