#include "DamageShape.h"
#include "Hierarchy.h"
#include "MasterResourceManager.h"

void CDamageShape::setDamageOnlyUnitTypeByUnitTypeLoadIndex(unsigned int index)
{
    CHierarchy* hierarchy = CMasterResourceManager::getSingleton()->m_pHierarchy;
    unsigned int type = ~0u;
    if (index < hierarchy->m_types.size()) type = hierarchy->m_types[index];
    m_iUnknown188 = type;
}
unsigned int CDamageShape::getDamageOnlyUnitTypeLoadIndex()
{
    std::wstring name = CMasterResourceManager::getSingleton()->m_pHierarchy->getTypeName(m_iUnknown188);
    CHierarchy* hierarchy = CMasterResourceManager::getSingleton()->m_pHierarchy;
    unsigned int type = hierarchy->getTypeIDByName(name);
    for (unsigned int i = 0; i < hierarchy->m_types.size(); ++i)
        if (hierarchy->m_types[i] == type) return i;
    return ~0u;
}

#include "Level.h"
void CDamageShape::doInstantDamage()
{
    if (m_pResourceManager && m_pResourceManager->getLevel()) {
        CLevel* level = m_pResourceManager->getLevel();
        for (TLinkedListNode<CCharacter*>* node=level->getCharacters()->getHead(); node; node=node->m_pNext)
            characterUpdatedInLevel(0, node->m_Data);
        level=m_pResourceManager->getLevel();
        for (TLinkedListNode<CItem*>* node=level->m_items->getHead(); node; node=node->m_pNext)
            itemUpdatedInLevel(0, node->m_Data);
    }
}

void CDamageShape::itemUpdatedInLevel(float elapsed,CItem* item)
{
    if(!item || item->m_bItemFlag218) return;
    float radius=item->m_fBaseUnitValue194;
    Ogre::Vector3 position=item->getPosition(false);
    std::pair<bool,float> hit=getPositionIsInShapeAtPercent(m_fUnknown190,position,radius);
    if(hit.first) doDamageToItem(elapsed,item,hit.second);
}
void CDamageShape::characterUpdatedInLevel(float elapsed,CCharacter* character)
{
    if(!getEnabled() || !character || character->m_forcedHidden || !character->m_damageShapeEnabled) return;
    if(m_bTargetOnlyDead) {if(character->alive())return;}
    else if(!character->alive()) return;
    float radius=character->m_fBaseUnitValue194;
    Ogre::Vector3 position=character->getPosition(true);
    std::pair<bool,float> hit=getPositionIsInShapeAtPercent(m_fUnknown190,position,radius);
    if(hit.first) doDamageToCharacter(elapsed,character,hit.second);
}

#include "FormationNodeSaveAndLoad.h"
#include "UTFConversion.h"
#include "Settings.h"
#include <cstring>

CDamageShape::~CDamageShape()
{
    m_damageListeners.clear();
    if (m_pResourceManager->getLevel())
        m_pResourceManager->getLevel()->removeCharacterUpdateListener(this);
}

CDamageShape::CDamageShape(CResourceManager* resources)
    : CShape(resources), iLevelUpdate(), iLevelUpdatedCharacter(),
      m_graph(NULL), m_bUnknown180(false), m_iDamageType(1), m_iUnknown188(0),
      m_iAlignmentTypAllowedToDamage(3), m_fUnknown190(1.0f), m_fUpdateInEditor(0.0f),
      m_fDelayTimer(0.0f), m_fTimer(0.0f), m_iDelayTimer(0), m_bLoopsForEver(true),
      m_bUpdateInEditor(true), m_bUnknown1A6(false), m_bDamageOverTime(true),
      m_bTargetOnlyDead(false), m_iNumLoops(1), m_iUpdateInEditor(0),
      m_fMinDamage(1.0f), m_fMaxDamage(2.0f), m_fUnknown1BC(0.0f),
      m_fUnknown1C0(0.0f), m_fUnknown1C4(0.0f), m_damageListeners(10),
      m_targets(10), m_iTotalNumberOfTargets(0)
{
    if (m_pResourceManager->getEditorIsRunning())
        CDamageShape::setEnabled(true);
    CSceneNodeObject::setVisible(true);
    m_graph = m_pResourceManager->getGraph(L"DAMAGE_MONSTER");
}

void CFormationNodeSaveAndLoad::saveFormationNode(FILE* file)
{
    unsigned int length = m_sFileLoaded.length();
    fwrite(&length, 4, 1, file);
    WriteUTF32ToUTF16(file, m_sFileLoaded, length);
    fwrite(&m_fPositionX, 4, 1, file);
    fwrite(&m_fPositionY, 4, 1, file);
    fwrite(&m_fPositionZ, 4, 1, file);
}

void CFormationNodeSaveAndLoad::loadFormationNode(FILE* file)
{
    unsigned int length = 0;
    fread(&length, 4, 1, file);
    wchar_t* text = new wchar_t[length + 1];
    std::memset(text, 0, (length + 1) * sizeof(wchar_t));
    ReadUTF16ToUTF32(file, text, length);
    m_sFileLoaded = text;
    if (text)
        delete[] text;
    fread(&m_fPositionX, 4, 1, file);
    fread(&m_fPositionY, 4, 1, file);
    fread(&m_fPositionZ, 4, 1, file);
}

void CDamageShape::setEnabled(bool enabled)
{
    m_fDelayTimer = 0.0f;
    m_bEnabled = enabled;
    m_iUpdateInEditor = m_iNumLoops < 0 ? 0 : m_iNumLoops;
    m_fUpdateInEditor = m_fTimer;
    if (m_pResourceManager->getEditorIsRunning() || !m_pResourceManager->getLevel())
        return;
    if (!enabled) {
        m_pResourceManager->getLevel()->removeCharacterUpdateListener(this);
        return;
    }
    m_targets.clear();
    float timer = m_fTimer;
    if (!(timer <= 0.0f) || m_iUpdateInEditor != 0) {
        m_bUnknown1A6 = false;
        m_fTimer = timer;
        m_fUpdateInEditor = timer;
        m_fDelayTimer = 0.0f;
        m_bUnknown180 = false;
        m_pResourceManager->getLevel()->addCharacterUpdateListener(this);
        return;
    }
    doInstantDamage();
    if ((m_bUpdateInEditor && m_pResourceManager->getEditorIsRunning()) ||
        (!m_pResourceManager->getEditorIsRunning() &&
         CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_SHOW_DAMAGE_SHAPES)))
        updateVisual(true, 1.0f);
    setEnabled(false);
}
