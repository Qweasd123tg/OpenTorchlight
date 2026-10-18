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
