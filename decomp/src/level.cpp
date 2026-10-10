#include "Automap.h"
#include "Character.h"
#include "Descriptor.h"
#include "EditorScene.h"
#include "Equipment.h"
#include "GameClient.h"
#include "GameVariables.h"
#include "Item.h"
#include "Level.h"
#include "LevelTemplateData.h"
#include "Player.h"
#include "Utilities.h"

#include "BaseUnit.h"
#include "Character.h"
#include "GameClient.h"
#include "Item.h"
#include "Level.h"
#include "Player.h"

CCharacter* CLevel::getPlayer()
{
    return m_pGameClient ? m_pGameClient->getPlayer() : NULL;
}

void CLevel::questEventFire(EQUEST_EVENTS event, CCharacter* character, CBaseUnit* target)
{
    if (m_pGameClient)
        m_pGameClient->questEventFire(event, character, target);
}

void CLevel::removeUnit(CBaseUnit* unit, bool flag)
{
    if (unit)
    {
        if (unit->m_eBaseUnitType == static_cast<EBASEUNIT_TYPE>(1))
            removeItem(static_cast<CItem*>(unit), flag);
        else if (unit->m_eBaseUnitType == static_cast<EBASEUNIT_TYPE>(0))
            removeCharacter(static_cast<CCharacter*>(unit), flag);
    }
}


// Imported source candidates; historical status is not fresh acceptance.
void CLevel::removeListenerFromUnit(long long guid, iUnitObserver* observer)
{
    if (!observer) return;
    std::map<long long, TArrayList<iUnitObserver*>*>::iterator it = m_unitObservers.find(guid);
    if (it != m_unitObservers.end()) it->second->remove(observer);
}

void CLevel::removeListenerFromUnit(CBaseUnit* unit, iUnitObserver* observer)
{
    if (observer && unit) removeListenerFromUnit(unit->getGuid(), observer);
}

bool CLevel::addListenerToUnit(CBaseUnit* unit, iUnitObserver* observer)
{
    if (unit) return addListenerToUnit(unit->getGuid(), observer);
    return false;
}

void CLevel::removeListenerFromUnits(iUnitObserver* observer)
{
    if (!observer) return;
    for (std::map<long long, TArrayList<iUnitObserver*>*>::iterator it = m_unitObservers.begin(); it != m_unitObservers.end(); ++it) it->second->remove(observer);
}

bool CLevel::getAutomapVisible()
{
    if (m_automap && !m_automap->m_bFullscreen) return m_automap->m_bVisible;
    return false;
}

void CLevel::zoomAutomap(float delta)
{
    if (m_automap) m_automap->zoom(delta);
}

void CLevel::setNPCAutomapBillboardVisible(Ogre::Billboard* billboard, bool visible)
{
    if (billboard && m_automap) m_automap->setNPCBillboardVisible(billboard, visible);
}

void CLevel::clearPassabilityData()
{
    for (unsigned int x = 0; x < m_passWidth; ++x) {
        for (unsigned int y = 0; y < m_passHeight; ++y) {
            m_mapPassability[x][y] = -1;
            m_objectPassability[x][y] = 0;
        }
    }
}

bool CLevel::mapPassable(int x, int y)
{
    if (y < 0 || x < 0 || x >= static_cast<int>(m_passWidth) || y >= static_cast<int>(m_passHeight)) return false;
    return m_mapPassability[x][y] <= 0;
}

bool CLevel::positionPassable(int x, int y)
{
    if (y < 0 || x < 0 || x >= static_cast<int>(m_passWidth) || y >= static_cast<int>(m_passHeight)) return false;
    return m_mapPassability[x][y] <= 0 && m_objectPassability[x][y] <= 0;
}

void CLevel::restartLevel()
{
    for (TLinkedListNode<CCharacter*>* node = m_pCharacters->getHead(); node; node = node->m_pNext) node->m_Data->levelResetting();
}

void CLevel::updateLayouts(float elapsed)
{
    if (elapsed == 0.0f) return;
    int count = m_RoomScenes.size();
    for (int i = 0; i < count; ++i) m_RoomScenes[i]->update(elapsed);
}

void CLevel::updateCharacterAnimation(float elapsed, float scale, CPlayer* player)
{
    float scaled = scale * elapsed;
    for (TLinkedListNode<CCharacter*>* node = m_activeCharacters->getHead(); node; node = node->m_pNext) {
        if (node->m_Data == player) player->updateAnimation(elapsed);
        else node->m_Data->updateAnimation(scaled);
    }
    for (TLinkedListNode<CItem*>* node = m_activeItems->getHead(); node; node = node->m_pNext) node->m_Data->updateAnimation(scaled);
}

bool CLevel::isDormant()
{
    if (m_pGameClient) return m_pGameClient->m_bStateControl10BC;
    return false;
}

CCharacter* CLevel::getRandomMonster()
{
    int count = 0;
    for (TLinkedListNode<CCharacter*>* node = m_pCharacters->getHead(); node; node = node->m_pNext) ++count;
    int selected = UTILITIES::randomIntegerBetween(0, count);
    for (TLinkedListNode<CCharacter*>* node = m_pCharacters->getHead(); node; node = node->m_pNext) {
        if (--selected < 0) return node->m_Data;
    }
    return NULL;
}

void CLevel::destroyIcons()
{
    if (m_pCharacters) {
        for (TLinkedListNode<CCharacter*>* node = m_pCharacters->getHead(); node; node = node->m_pNext) {
            node->m_Data->destroyIcons(); node->m_Data->destroyCharacterText();
        }
    }
    if (m_items) {
        for (TLinkedListNode<CItem*>* node = m_items->getHead(); node; node = node->m_pNext) {
            CEquipment* equipment = dynamic_cast<CEquipment*>(node->m_Data);
            if (equipment) equipment->destroyIcon();
            node->m_Data->destroyItemText();
        }
    }
}

void CLevel::deleteOpenPortals()
{
    if (m_items) {
        for (TLinkedListNode<CItem*>* node = m_items->getHead(); node; node = node->m_pNext) {
            if (node->m_Data->ISA(static_cast<UNITTYPES::EUNITTYPES>(43)) || node->m_Data->ISA(static_cast<UNITTYPES::EUNITTYPES>(171))) node->m_Data->m_bBaseUnitFlag190 = true;
        }
    }
    updateAutomapIcons();
}

int CLevel::getRoomIndexThatPositionIsIn(const Ogre::Vector3& position)
{
    for (unsigned int i = 0; i < m_roomBounds.size(); ++i) if (m_roomBounds[i].contains(position)) return i;
    return -1;
}

Ogre::Vector3 CLevel::randomOpenItemPosition(const Ogre::Vector3& position, float radius, bool flag)
{
    return randomOpenItemPositionRange(position, 0.0f, radius, flag);
}

Ogre::Vector3 CLevel::randomOpenPosition(const Ogre::Vector3& position, float radius, bool flag)
{
    return randomOpenPositionRange(position, 0.0f, radius, flag);
}

bool CLevel::rayCollision(const Ogre::Vector3& start, const Ogre::Vector3& end, Ogre::Vector3& hit, Ogre::Vector3& normal, bool flag)
{
    unsigned int type;
    Ogre::Vector3 extra;
    return rayCollision(start, end, hit, normal, type, extra, flag);
}

bool CLevel::sphereCollision(const Ogre::Vector3& start, const Ogre::Vector3& end, float radius, Ogre::Vector3& position, Ogre::Vector3& hit, Ogre::Vector3& normal)
{
    unsigned int type;
    Ogre::Vector3 extra;
    return sphereCollision(start, end, radius, position, hit, normal, type, extra);
}

bool CLevel::sightUnobstructed(const Ogre::Vector3& start, const Ogre::Vector3& end, bool flag)
{
    Ogre::Vector3 hit, normal, extra;
    unsigned int type;
    return !rayCollision(start, end, hit, normal, type, extra, flag);
}

bool CLevel::snapToValidGround(Ogre::Vector3& position, float height)
{
    Ogre::Vector3 start = position;
    Ogre::Vector3 end = position;
    start.y += 10.0f;
    end.y -= 100.0f;
    Ogre::Vector3 hit, normal, extra;
    unsigned int type;
    if (rayCollision(start, end, hit, normal, type, extra, false) && type != 100) {
        position = hit; position.y += height; return true;
    }
    return false;
}

void CLevel::killAll()
{
    for (TLinkedListNode<CCharacter*>* node = m_pCharacters->getHead(); node; node = node->m_pNext) {
        CCharacter* character = node->m_Data;
        if (character && !dynamic_cast<CPlayer*>(character)) {
            if (character->alignment() == static_cast<EAlignment>(2) || node->m_Data->alignment() == static_cast<EAlignment>(4)) node->m_Data->die(NULL, NULL, 0.0f, false);
        }
    }
}
