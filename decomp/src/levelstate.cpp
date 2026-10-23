#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "GameNamespaces.h"
#include "LevelState.h"
#include "LogicNodeState.h"
#include "Automap.h"
#include "RunicCore.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "GameNamespaces.h"
#include "Level.h"

CLevelState::CLevelState(int iLevelId)
    : CRunicCore(),
      m_iLevelId(iLevelId),
      m_sLevelName(EMPTY_WSTRING),
      m_lCharacters(),
      m_lItems(),
      m_lLogicStates(),
      m_lLevelStrings(),
      m_lFormations(10),
      m_iStateVersion(0),
      m_iAutomapWidth(0),
      m_iAutomapHeight(0),
      m_pAutomapData(NULL),
      m_bUnknownB0(false),
      m_bUnknownB1(false)
{
}

void CLevelState::restoreAutomap(CAutomap *pAutomap)
{
    if (m_iAutomapWidth == pAutomap->m_iMapGridWidth &&
        m_iAutomapHeight == pAutomap->m_iMapGridHeight) {
        memcpy(pAutomap->m_pRevealedTiles, m_pAutomapData,
               (long)(m_iAutomapWidth * m_iAutomapHeight) << 2);
        pAutomap->m_bTilesChanged = true;
    }
}

void CLevelState::addLogicState(CLogicNodeState *pLogicState, CLevel &Level)
{
    m_lLogicStates.push_back(pLogicState);
}

#include "UTFConversion.h"
#include "FormationNode.h"
#include "FormationNodeSaveAndLoad.h"
#include "ItemSaveState.h"
#include "CharacterSaveState.h"

void CLevelState::addAutomap(CAutomap* map)
{
    delete[] static_cast<float*>(m_pAutomapData);
    m_iAutomapWidth = map->m_iMapGridWidth;
    m_iAutomapHeight = map->m_iMapGridHeight;
    m_pAutomapData = new float[m_iAutomapWidth * m_iAutomapHeight];
    memcpy(m_pAutomapData, map->m_pRevealedTiles,
           static_cast<long>(m_iAutomapWidth * m_iAutomapHeight) * 4);
}

void CLevelState::addFormations(TArrayList<CFormationNode*>* formations, CLevel& level)
{
    for (unsigned int i = 0; i < formations->size(); ++i)
        if (!(*formations)[i]->m_bActivationStarted)
            m_lFormations.add(new CFormationNodeSaveAndLoad((*formations)[i]));
}

void CLevelState::addItem(CItem& item)
{
    CItemSaveState* state = new CItemSaveState;
    item.fillSaveState(*state, -1, false);
    m_lItems.push_back(state);
}

void CLevelState::addCharacter(CCharacter& character, CLevel& level)
{
    CCharacterSaveState* state = new CCharacterSaveState;
    character.fillSaveState(*state);
    m_lCharacters.push_back(state);
}

void CLevelState::save(FILE* file)
{
    fwrite(&m_iLevelId, 4, 1, file);
    fwrite(&m_iStateVersion, 4, 1, file);
    unsigned short length = m_sLevelName.length();
    fwrite(&length, 2, 1, file);
    WriteUTF32ToUTF16(file, m_sLevelName, length);
    unsigned char flag = m_bUnknownB0;
    fwrite(&flag, 1, 1, file);
    flag = m_bUnknownB1;
    fwrite(&flag, 1, 1, file);
    fwrite(&m_iAutomapWidth, 4, 1, file);
    fwrite(&m_iAutomapHeight, 4, 1, file);
    if (m_iAutomapWidth > 0)
        fwrite(m_pAutomapData, static_cast<size_t>(m_iAutomapWidth) * m_iAutomapHeight * 4, 1, file);
    unsigned int count = m_lCharacters.size();
    fwrite(&count, 4, 1, file);
    for (unsigned int i = 0; i < count; ++i) m_lCharacters[i]->save(file);
    count = m_lItems.size();
    fwrite(&count, 4, 1, file);
    for (unsigned int i = 0; i < count; ++i) m_lItems[i]->save(file);
    count = m_lLogicStates.size();
    fwrite(&count, 4, 1, file);
    for (unsigned int i = 0; i < count; ++i) m_lLogicStates[i]->save(file);
    count = m_lLevelStrings.size();
    fwrite(&count, 4, 1, file);
    for (unsigned int i = 0; i < count; ++i)
    {
        std::wstring text = m_lLevelStrings[i];
        unsigned short length = text.length();
        fwrite(&length, 2, 1, file);
        WriteUTF32ToUTF16(file, text, length);
    }
    count = 0;
    for (unsigned int i = 0; i < m_lFormations.size(); ++i)
        if (m_lFormations[i]->m_bSavePosition) ++count;
    fwrite(&count, 4, 1, file);
    for (unsigned int i = 0; i < m_lFormations.size(); ++i)
        if (m_lFormations[i]->m_bSavePosition) m_lFormations[i]->saveFormationNode(file);
}

CLevelState::~CLevelState()
{
    delete[] static_cast<float*>(m_pAutomapData);
    m_lFormations.deleteAll();
    for (int i = 0; i < static_cast<int>(m_lLogicStates.size()); ++i)
    {
        delete m_lLogicStates[i];
        m_lLogicStates[i] = NULL;
    }
    m_lLogicStates.clear();
    for (int i = 0; i < static_cast<int>(m_lItems.size()); ++i)
    {
        delete m_lItems[i];
        m_lItems[i] = NULL;
    }
    m_lItems.clear();
    for (int i = 0; i < static_cast<int>(m_lCharacters.size()); ++i)
    {
        delete m_lCharacters[i];
        m_lCharacters[i] = NULL;
    }
    m_lCharacters.clear();
}

#include "FileUtilities.h"

void CLogicNodeState::load(FILE* file, unsigned int version)
{
    unsigned short length;
    fread(&length, 2, 1, file);
    m_wstrName = FILESYSTEM::ReadWString(file, length);
    unsigned char flag;
    fread(&flag, 1, 1, file);
    m_bActive = flag != 0;
    fread(&flag, 1, 1, file);
    m_bEnabled = flag != 0;
    fread(&flag, 1, 1, file);
    m_bFinished = flag != 0;
    fread(&flag, 1, 1, file);
    m_bFailed = flag != 0;
    fread(&m_nNodeId, 4, 1, file);
    fread(&m_nParentNodeId, 4, 1, file);
    fread(&m_nStateFlags, 4, 1, file);
    fread(&m_nCurrentState, 4, 1, file);
    fread(&m_guid, 8, 1, file);
    fread(&m_parentGuid, 8, 1, file);
    if (version > 16)
        fread(&m_parentHierarchyHash, 8, 1, file);
    else if (version == 16) {
        unsigned int unused = 0;
        fread(&unused, 4, 1, file);
    }
    fread(&m_position, 12, 1, file);
    fread(&flag, 1, 1, file);
    m_bPersistent = flag != 0;
    fread(&m_nStateVersion, 4, 1, file);
}

void CLevelState::load(FILE* file, unsigned int version)
{
    fread(&m_iLevelId, 4, 1, file);
    fread(&m_iStateVersion, 4, 1, file);
    for (int i = 0; i < m_iAutomapWidth * m_iAutomapHeight; ++i) {
        unsigned char flag;
        fread(&flag, 1, 1, file);
        static_cast<float*>(m_pAutomapData)[i] = flag ? 1.0f : 0.0f;
    }
    unsigned short length;
    fread(&length, 2, 1, file);
    m_sLevelName = FILESYSTEM::ReadWString(file, length);
    unsigned char flag;
    fread(&flag, 1, 1, file);
    m_bUnknownB0 = flag != 0;
    if (version > 21)
        fread(&m_bUnknownB1, 1, 1, file);
    fread(&m_iAutomapWidth, 4, 1, file);
    fread(&m_iAutomapHeight, 4, 1, file);
    if (m_iAutomapWidth > 0) {
        m_pAutomapData = new float[m_iAutomapWidth * m_iAutomapHeight];
        fread(m_pAutomapData,
              static_cast<long>(m_iAutomapWidth) * m_iAutomapHeight * 4,
              1, file);
    }
    unsigned int count = m_lCharacters.size();
    fread(&count, 4, 1, file);
    for (unsigned int i = 0; i < count; ++i) {
        CCharacterSaveState* state = new CCharacterSaveState;
        state->load(file, version);
        m_lCharacters.push_back(state);
    }
    count = m_lItems.size();
    fread(&count, 4, 1, file);
    for (unsigned int i = 0; i < count; ++i) {
        CItemSaveState* state = new CItemSaveState;
        state->load(file, version);
        m_lItems.push_back(state);
    }
    count = m_lLogicStates.size();
    fread(&count, 4, 1, file);
    for (unsigned int i = 0; i < count; ++i) {
        CLogicNodeState* state = new CLogicNodeState();
        state->load(file, version);
        if (version <= 14 && state->m_wstrName == L"Timeline")
            state->m_bPersistent = true;
        m_lLogicStates.push_back(state);
    }
    count = m_lLevelStrings.size();
    fread(&count, 4, 1, file);
    for (unsigned int i = 0; i < count; ++i) {
        fread(&length, 2, 1, file);
        std::wstring text = FILESYSTEM::ReadWString(file, length);
        m_lLevelStrings.push_back(text);
    }
    count = m_lFormations.size();
    fread(&count, 4, 1, file);
    for (unsigned int i = 0; i < count; ++i) {
        CFormationNodeSaveAndLoad* formation = new CFormationNodeSaveAndLoad(NULL);
        formation->loadFormationNode(file);
        m_lFormations.add(formation);
    }
}
