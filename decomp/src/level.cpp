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

long long CLevel::addListenerToUnit(CBaseUnit* unit, iUnitObserver* observer)
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

#include "Dungeon.h"
#include "Inventory.h"
#include "iLevelUpdate.h"
#include "iLevelUpdatedCharacter.h"
#include "TimerStatics.h"
#include "PropertyNode.h"
#include "CollisionList.h"
#include <OgreStaticGeometry.h>
#include <cmath>

void CLevel::setNonLightStaticGeometryVisible(bool visible)
{
    if (m_nonLightStaticGeometry) {
        m_nonLightStaticGeometry->setVisible(visible);
        m_nonLightStaticGeometry2->setVisible(visible);
        m_nonLightStaticGeometry3->setVisible(visible);
    }
}

void CLevel::setLightStaticGeometryVisible(bool visible)
{
    if (m_lightStaticGeometry) m_lightStaticGeometry->setVisible(visible);
}

CBaseUnit* CLevel::getBaseUnitByDataGroup(CDataGroup* group)
{
    if (!group) return NULL;
    for (TLinkedListNode<CCharacter*>* p=m_pCharacters->getHead();p;p=p->m_pNext)
        if (p->m_Data && p->m_Data->m_pDataGroup==group) return p->m_Data;
    for (TLinkedListNode<CItem*>* p=m_items->getHead();p;p=p->m_pNext)
        if (p->m_Data && p->m_Data->m_pDataGroup==group) return p->m_Data;
    return NULL;
}

CCharacter* CLevel::getCharacterByGuid(long long guid)
{
    if (m_pGameClient && m_pGameClient->m_pPlayer && m_pGameClient->m_pPlayer->getGuid()==guid)
        return m_pGameClient->m_pPlayer;
    for (TLinkedListNode<CCharacter*>* p=m_pCharacters->getHead();p;p=p->m_pNext)
        if (p->m_Data && p->m_Data->getGuid()==guid) return p->m_Data;
    return NULL;
}

bool CLevel::removeUpdateObject(iLevelUpdate* object)
{
    int index=m_updateObjects.find(object);
    if (index!=-1) { m_updateObjects.removeAt(index);return true; }
    return false;
}

unsigned int CLevel::getCurrentLevelSeed()
{
    unsigned int seed=m_levelSeed;
    CDungeon* dungeon=m_pGameClient->m_currentDungeon;
    unsigned int dungeonSeed=dungeon ? dungeon->m_iDungeonIndex : 0;
    return seed+m_iLevelDepth+dungeonSeed;
}

float CLevel::topLeftX() { return m_collisionList ? m_topLeftX : 0.0f; }
float CLevel::topLeftY() { return m_collisionList ? m_topLeftY : 0.0f; }

CItem* CLevel::getItemByGuid(long long originalGuid,long long parentGuid)
{
    if (m_items) for (TLinkedListNode<CItem*>* p=m_items->getHead();p;p=p->m_pNext) {
        CItem* item=p->m_Data;
        if (item->getOriginalGuid()==originalGuid && item->getSceneOwner() &&
            item->getSceneOwner()->getOriginalGuid()==parentGuid) return item;
    }
    return NULL;
}

void CLevel::updateLevelUpdateObjects(Ogre::Camera* camera,const Ogre::Vector3& position,float elapsed)
{
    for (unsigned int i=0;i<m_updateObjects.size();++i) {
        iLevelUpdate* object=m_updateObjects[i];
        if (object && object->updateLevelObject(elapsed,camera,position)) continue;
        if (i<m_updateObjects.size() && m_updateObjects[i]==object) {
            m_updateObjects.removeAt(i);
            --i;
        }
    }
}

void CLevel::makeQuestUnitsUncool(long long questGuid,bool)
{
    for (TLinkedListNode<CItem*>* p=m_items->getHead();p;p=p->m_pNext) {
        CItem* item=p->m_Data;
        if (item->m_iQuestGuid==questGuid && item->ISA(static_cast<UNITTYPES::EUNITTYPES>(0x67)))
            item->m_bBaseUnitFlag190=true;
    }
}

void CLevel::populateNewMerchantsInventory()
{
    for (TLinkedListNode<CCharacter*>* p=m_pCharacters->getHead();p;p=p->m_pNext) {
        CCharacter* character=p->m_Data;
        if (character->ISA(static_cast<UNITTYPES::EUNITTYPES>(0x29)) ||
            character->ISA(static_cast<UNITTYPES::EUNITTYPES>(0x7f))) {
            CInventory* inventory=character->m_pInventory;
            if (inventory && !inventory->itemsInPane(static_cast<EINVENTORY_PANES>(4)) &&
                !inventory->itemsInPane(static_cast<EINVENTORY_PANES>(3)) &&
                !inventory->itemsInPane(static_cast<EINVENTORY_PANES>(1)))
                character->generateMerchantInventory();
        }
    }
}

std::wstring CLevel::getLevelChampionSpawnClass()
{
    if (m_pLevelTemplateData) return m_pLevelTemplateData->m_selectedUnitSpawners[1];
    return L"MONSTERSETCHAMPION";
}

std::wstring CLevel::getLevelMonsterSpawnClass()
{
    if (m_pLevelTemplateData) return m_pLevelTemplateData->m_selectedUnitSpawners[0];
    return L"MONSTERSET";
}

void CLevel::addUpdateObject(iLevelUpdate* object)
{
    if (m_updateObjects.find(object)==-1) m_updateObjects.add(object);
}

void CLevel::removeCharacterUpdateListener(iLevelUpdatedCharacter* listener)
{
    if (!m_characterUpdateListeners) return;
    for (TLinkedListNode<iLevelUpdatedCharacter*>* p=m_characterUpdateListeners->getHead();p;p=p->m_pNext)
        if (p->m_Data==listener) {
            if (m_pendingCharacterUpdateRemovals.find(p)==-1) m_pendingCharacterUpdateRemovals.add(p);
            return;
        }
}

void CLevel::flushCharacterUpdateListeners()
{
    for (unsigned int i=0;i<m_pendingCharacterUpdateRemovals.size();++i) {
        TLinkedListNode<iLevelUpdatedCharacter*>* node=m_pendingCharacterUpdateRemovals[i];
        if (node) {
            if (m_characterUpdateListeners->m_pHead==node) {
                if (node->m_pNext) node->m_pNext->m_pPrevious=NULL;
                if (node->m_pNext) {
                    m_characterUpdateListeners->m_pHead=node->m_pNext;
                    node->m_pNext->m_pPrevious=NULL;
                } else m_characterUpdateListeners->m_pHead=NULL;
            } else {
                if (node->m_pPrevious) node->m_pPrevious->m_pNext=node->m_pNext;
                if (node->m_pNext) node->m_pNext->m_pPrevious=node->m_pPrevious;
            }
            node->m_pNext=NULL;node->m_pPrevious=NULL;delete node;
        }
    }
    m_pendingCharacterUpdateRemovals.clear();
}

void CLevel::updateDroppingItems(float elapsed)
{
    for (TLinkedListNode<CItem*>* p=m_activeItems->getHead();p;) {
        CItem* item=p->m_Data;p=p->m_pNext;
        if (item->m_bInActiveRange) {
            CEquipment* equipment=dynamic_cast<CEquipment*>(item);
            if (equipment) equipment->updateDrop(elapsed);
        }
    }
}

void CLevel::reactToAreaDamage(CCharacter* attacker,CCharacter* target)
{
    for (TLinkedListNode<CCharacter*>* p=m_activeCharacters->getHead();p;p=p->m_pNext) {
        CCharacter* character=p->m_Data;
        if (character!=target && character->alive() && character->isFriend(target) && character->inDamageReactRange(target))
            character->reactToDamage(attacker,false);
    }
}

namespace {
int levelGridLimit(int value,int maximum)
{
    if (value<0) value=0;
    if (value>maximum) value=maximum;
    return value;
}
void levelAdjustGrid(short** grid,int width,int height,const Ogre::Vector3& minimum,
                     const Ogre::Vector3& maximum,float radius,float originX,float originZ,int adjustment)
{
    float middleX=(minimum.x+maximum.x)*0.5f;
    float middleZ=(minimum.z+maximum.z)*0.5f;
    int firstX=levelGridLimit(static_cast<int>(::floorf((minimum.x-originX)/0.4f)),width);
    int firstZ=levelGridLimit(static_cast<int>(::floorf((minimum.z-originZ)/0.4f)),height);
    int lastX=levelGridLimit(static_cast<int>(::floorf((maximum.x-originX)/0.4f)),width);
    int lastZ=levelGridLimit(static_cast<int>(::floorf((maximum.z-originZ)/0.4f)),height);
    for (int x=firstX;x<lastX;++x) for (int z=firstZ;z<lastZ;++z) {
        if (radius!=0.0f) {
            float dx=middleX-(static_cast<float>(x)*0.4f+originX);
            float dz=middleZ-(static_cast<float>(z)*0.4f+originZ);
            if (!(::sqrtf(dx*dx+0.0f+dz*dz)<=radius)) continue;
        }
        grid[x][z]+=adjustment;
    }
}
}
// Generated repeated public overloads below.

void CLevel::incrementMapPassability(const Ogre::Vector3& position)
{
    int x=static_cast<int>(::floorf((position.x-topLeftX())/0.4f));
    int z=static_cast<int>(::floorf((position.z-topLeftY())/0.4f));
    if (z<0 || x<0 || x>=static_cast<int>(m_passWidth) || z>=static_cast<int>(m_passHeight)) return;
    ++m_mapPassability[x][z];
}

void CLevel::decrementMapPassability(const Ogre::Vector3& position)
{
    int x=static_cast<int>(::floorf((position.x-topLeftX())/0.4f));
    int z=static_cast<int>(::floorf((position.z-topLeftY())/0.4f));
    if (z<0 || x<0 || x>=static_cast<int>(m_passWidth) || z>=static_cast<int>(m_passHeight)) return;
    --m_mapPassability[x][z];
}

void CLevel::incrementObjectPassability(const Ogre::Vector3& position)
{
    int x=static_cast<int>(::floorf((position.x-topLeftX())/0.4f));
    int z=static_cast<int>(::floorf((position.z-topLeftY())/0.4f));
    if (z<0 || x<0 || x>=static_cast<int>(m_passWidth) || z>=static_cast<int>(m_passHeight)) return;
    ++m_objectPassability[x][z];
}

void CLevel::decrementObjectPassability(const Ogre::Vector3& position)
{
    int x=static_cast<int>(::floorf((position.x-topLeftX())/0.4f));
    int z=static_cast<int>(::floorf((position.z-topLeftY())/0.4f));
    if (z<0 || x<0 || x>=static_cast<int>(m_passWidth) || z>=static_cast<int>(m_passHeight)) return;
    --m_objectPassability[x][z];
}

bool CLevel::mapPassable(const Ogre::Vector3& position)
{
    int x=static_cast<int>(::floorf((position.x-topLeftX())/0.4f));
    int z=static_cast<int>(::floorf((position.z-topLeftY())/0.4f));
    return mapPassable(x,z);
}

bool CLevel::positionPassable(const Ogre::Vector3& position)
{
    int x=static_cast<int>(::floorf((position.x-topLeftX())/0.4f));
    int z=static_cast<int>(::floorf((position.z-topLeftY())/0.4f));
    return positionPassable(x,z);
}

void CLevel::incrementMapPassability(const Ogre::Vector3& minimum,const Ogre::Vector3& maximum,float radius)
{
    levelAdjustGrid(m_mapPassability,m_passWidth,m_passHeight,minimum,maximum,radius,topLeftX(),topLeftY(),1);
}

void CLevel::incrementMapPassability(const Ogre::AxisAlignedBox& bounds,float radius)
{
    levelAdjustGrid(m_mapPassability,m_passWidth,m_passHeight,bounds.getMinimum(),bounds.getMaximum(),radius,topLeftX(),topLeftY(),1);
}

void CLevel::decrementMapPassability(const Ogre::Vector3& minimum,const Ogre::Vector3& maximum,float radius)
{
    levelAdjustGrid(m_mapPassability,m_passWidth,m_passHeight,minimum,maximum,radius,topLeftX(),topLeftY(),-1);
}

void CLevel::decrementMapPassability(const Ogre::AxisAlignedBox& bounds,float radius)
{
    levelAdjustGrid(m_mapPassability,m_passWidth,m_passHeight,bounds.getMinimum(),bounds.getMaximum(),radius,topLeftX(),topLeftY(),-1);
}

void CLevel::incrementObjectPassability(const Ogre::Vector3& minimum,const Ogre::Vector3& maximum,float radius)
{
    levelAdjustGrid(m_objectPassability,m_passWidth,m_passHeight,minimum,maximum,radius,topLeftX(),topLeftY(),1);
}

void CLevel::incrementObjectPassability(const Ogre::AxisAlignedBox& bounds,float radius)
{
    levelAdjustGrid(m_objectPassability,m_passWidth,m_passHeight,bounds.getMinimum(),bounds.getMaximum(),0.0f,topLeftX(),topLeftY(),1);
}

void CLevel::decrementObjectPassability(const Ogre::Vector3& minimum,const Ogre::Vector3& maximum,float radius)
{
    levelAdjustGrid(m_objectPassability,m_passWidth,m_passHeight,minimum,maximum,radius,topLeftX(),topLeftY(),-1);
}

void CLevel::decrementObjectPassability(const Ogre::AxisAlignedBox& bounds,float radius)
{
    levelAdjustGrid(m_objectPassability,m_passWidth,m_passHeight,bounds.getMinimum(),bounds.getMaximum(),radius,topLeftX(),topLeftY(),-1);
}

CCharacter* CLevel::getCharacterByOriginalGuid(long long originalGuid,long long parentGuid,int room)
{
    for (TLinkedListNode<CCharacter*>* p=m_pCharacters->getHead();p;p=p->m_pNext) {
        CCharacter* character=p->m_Data;
        if (room!=-1 && character->m_iRoomIndex==-1)
            character->m_iRoomIndex=getRoomIndexThatPositionIsIn(character->getPosition(true));
        CEditorScene* parent=character->getSceneOwner();
        long long parentOriginal=parent ? parent->getOriginalGuid() : -1;
        if (character->getOriginalGuid()==originalGuid && (parentOriginal==parentGuid || parentGuid==-1) &&
            (room==-1 || character->m_iRoomIndex==room)) return character;
    }
    return NULL;
}

CItem* CLevel::getItemByOriginalGuid(long long originalGuid,long long,int room,long long hierarchy)
{
    CItem* result=NULL;
    for (TLinkedListNode<CItem*>* p=m_items->getHead();p;p=p->m_pNext) {
        CItem* item=p->m_Data;
        if (item->m_iRoomIndex==-1) item->m_iRoomIndex=getRoomIndexThatPositionIsIn(item->getPosition(true));
        if (item->getOriginalGuid()!=originalGuid || (room!=-1 && item->m_iRoomIndex!=room)) continue;
        if (!hierarchy || item->getParentHierarchyHashCode()==hierarchy) return item;
        result=item;
    }
    return result;
}

CEditorScene* CLevel::getRoomThatPositionIsIn(const Ogre::Vector3& position)
{
    for (unsigned int i=0;i<m_roomBounds.size();++i)
        if (m_roomBounds[i].contains(position)) return m_RoomScenes[i];
    return NULL;
}

bool CLevel::isInNoSpawnRegion(const Ogre::Vector3& position,float radius)
{
    if (radius<=0.0f) {
        for (unsigned int i=0;i<m_noSpawnRegions.size();++i)
            if (m_noSpawnRegions[i]->m_bounds.contains(position)) return true;
    } else {
        Ogre::Vector3 offset(radius,radius,radius);
        Ogre::AxisAlignedBox bounds(position-offset,position+offset);
        for (unsigned int i=0;i<m_noSpawnRegions.size();++i)
            if (m_noSpawnRegions[i]->m_bounds.intersects(bounds)) return true;
    }
    return false;
}

void CLevel::addCharacterUpdateListener(iLevelUpdatedCharacter* listener)
{
    if (!m_characterUpdateListeners) return;
    for (unsigned int i=0;i<m_pendingCharacterUpdateRemovals.size();++i)
        if (m_pendingCharacterUpdateRemovals[i]->m_Data==listener) {
            m_pendingCharacterUpdateRemovals.removeAt(i);break;
        }
    for (TLinkedListNode<iLevelUpdatedCharacter*>* p=m_characterUpdateListeners->getHead();p;p=p->m_pNext)
        if (p->m_Data==listener) return;
    TLinkedListNode<iLevelUpdatedCharacter*>* node=new TLinkedListNode<iLevelUpdatedCharacter*>;
    node->m_Data=listener;node->m_pNext=NULL;node->m_pPrevious=NULL;
    if (m_characterUpdateListeners->m_pHead) {
        node->m_pNext=m_characterUpdateListeners->m_pHead;
        m_characterUpdateListeners->m_pHead->m_pPrevious=node;
        m_characterUpdateListeners->m_pHead=node;
    } else {
        m_characterUpdateListeners->m_pHead=node;
        node->m_pNext=NULL;m_characterUpdateListeners->m_pHead->m_pPrevious=NULL;
    }
}

void CLevel::getUnitsByUnitType(UNITTYPES::EUNITTYPES type,TArrayList<CBaseUnit*>& units)
{
    for (TLinkedListNode<CCharacter*>* p=m_pCharacters->getHead();p;p=p->m_pNext)
        if (p->m_Data->ISA(type)) units.add(p->m_Data);
    for (TLinkedListNode<CItem*>* p=m_items->getHead();p;p=p->m_pNext)
        if (p->m_Data->ISA(type)) units.add(p->m_Data);
}

void CLevel::getBaseUnitsByDataGroup(CDataGroup* group,TArrayList<CBaseUnit*>& units)
{
    if (!group) return;
    for (TLinkedListNode<CCharacter*>* p=m_pCharacters->getHead();p;p=p->m_pNext)
        if (p->m_Data && p->m_Data->m_pDataGroup==group) units.add(p->m_Data);
    for (TLinkedListNode<CItem*>* p=m_items->getHead();p;p=p->m_pNext)
        if (p->m_Data && p->m_Data->m_pDataGroup==group) units.add(p->m_Data);
}

void CLevel::getActiveUnitsAtPosition(const Ogre::Vector3& position,float radius,
                                     TArrayList<CCharacter*>& characters,TArrayList<CItem*>& items)
{
    for (TLinkedListNode<CCharacter*>* p=m_activeCharacters->getHead();p;p=p->m_pNext)
        if ((p->m_Data->getPosition(true)-position).length()<=radius) characters.add(p->m_Data);
    for (TLinkedListNode<CItem*>* p=m_activeItems->getHead();p;p=p->m_pNext)
        if ((p->m_Data->getPosition(true)-position).length()<=radius) items.add(p->m_Data);
}

void CLevel::getActiveCharactersAtPosition(const Ogre::Vector3& position,UNITTYPES::EUNITTYPES type,
                                           EAlignment alignment,float radius,bool aliveState,bool deadState,
                                           TArrayList<CCharacter*>& characters)
{
    for (TLinkedListNode<CCharacter*>* p=m_activeCharacters->getHead();p;p=p->m_pNext) {
        if (!p->m_Data->ISA(type)) continue;
        if (alignment!=static_cast<EAlignment>(3) && p->m_Data->alignment()!=alignment) continue;
        if (p->m_Data->alive()!=aliveState && (!p->m_Data->alive())!=deadState) continue;
        if ((p->m_Data->getPosition(true)-position).length()<=radius) characters.add(p->m_Data);
    }
}

void CLevel::unitBroadcastMessage(CBaseUnit* unit,EUNIT_STATES state)
{
    std::map<long long,TArrayList<iUnitObserver*>*>::iterator it=m_unitObservers.find(unit->getGuid());
    if (it==m_unitObservers.end()) return;
    for (unsigned int i=0;i<it->second->size();++i) (*it->second)[i]->unitStateChange(unit,state);
    if (static_cast<int>(state)==0) {
        delete it->second;it->second=NULL;m_unitObservers.erase(it);
    }
}

namespace {
template<class T> TLinkedListNode<T>* levelFindListNode(TLinkedListNode<T>* head,T object)
{
    for (TLinkedListNode<T>* p=head;p;p=p->m_pNext) if (p->m_Data==object) return p;
    return NULL;
}
template<class T> void levelEraseListNode(TLinkedListNode<T>*& head,TLinkedListNode<T>* node)
{
    if (!node) return;
    if (head==node) {
        if (node->m_pNext) node->m_pNext->m_pPrevious=NULL;
        if (node->m_pNext) { head=node->m_pNext;node->m_pNext->m_pPrevious=NULL; }
        else head=NULL;
    } else {
        if (node->m_pPrevious) node->m_pPrevious->m_pNext=node->m_pNext;
        if (node->m_pNext) node->m_pNext->m_pPrevious=node->m_pPrevious;
    }
    node->m_pNext=NULL;node->m_pPrevious=NULL;delete node;
}
}

void CLevel::removeCharacter(CCharacter* character,bool clearReferences)
{
    if (!character) return;
    if (character->m_automapBillboard) {m_npcIconsDirty=true;character->m_automapBillboard=NULL;}
    levelEraseListNode(m_pCharacters->m_pHead,levelFindListNode(m_pCharacters->getHead(),character));
    levelEraseListNode(m_activeCharacters->m_pHead,levelFindListNode(m_activeCharacters->getHead(),character));
    if (clearReferences) {
        character->clearAllUnitReferences();character->setTarget(NULL);character->setTargetItem(NULL);
        if (character->m_eAIState!=static_cast<EAIState>(0x2a)) character->setAIState(static_cast<EAIState>(2));
    }
    if (m_pendingCharacters)
        levelEraseListNode(m_pendingCharacters->m_pHead,levelFindListNode(m_pendingCharacters->getHead(),character));
}

bool CLevel::removeItem(CItem* item,bool deactivate)
{
    bool removed=false;
    if (!item) return removed;
    if (m_items) {
        TLinkedListNode<CItem*>* node=levelFindListNode(m_items->getHead(),item);
        if (node) {
            if (deactivate) item->deactivateUnitInLevel();
            levelEraseListNode(m_items->m_pHead,node);removed=true;
        }
    }
    if (m_activeItems) levelEraseListNode(m_activeItems->m_pHead,levelFindListNode(m_activeItems->getHead(),item));
    if (m_pendingItems) levelEraseListNode(m_pendingItems->m_pHead,levelFindListNode(m_pendingItems->getHead(),item));
    return removed;
}

void CLevel::deleteCharacter(CCharacter* character)
{
    if (!character) return;
    levelEraseListNode(m_pendingCharacters->m_pHead,levelFindListNode(m_pendingCharacters->getHead(),character));
    levelEraseListNode(m_activeCharacters->m_pHead,levelFindListNode(m_activeCharacters->getHead(),character));
    levelEraseListNode(m_pCharacters->m_pHead,levelFindListNode(m_pCharacters->getHead(),character));
    notifyOfDeletion(character);
    if (character->m_bSaveFlag191 && character->getSceneOwner()) character->getSceneOwner()->DeleteObjectInScene(character);
    else delete character;
}

void CLevel::deleteItem(CItem* item)
{
    if (!item) return;
    item->deactivateUnitInLevel();
    levelEraseListNode(m_pendingItems->m_pHead,levelFindListNode(m_pendingItems->getHead(),item));
    levelEraseListNode(m_activeItems->m_pHead,levelFindListNode(m_activeItems->getHead(),item));
    levelEraseListNode(m_items->m_pHead,levelFindListNode(m_items->getHead(),item));
    notifyOfDeletion(item);
    if (item->m_bSaveFlag191 && item->getSceneOwner()) item->getSceneOwner()->DeleteObjectInScene(item);
    else delete item;
}

void CLevel::updateItems(Ogre::Camera* camera,const Ogre::Vector3& position,float elapsed)
{
    flushCharacterUpdateListeners();
    for (TLinkedListNode<CItem*>* p=m_activeItems->getHead();p;) {
        CItem* item=p->m_Data;p=p->m_pNext;
        if (item->m_bBaseUnitFlag190) {deleteItem(item);flushCharacterUpdateListeners();}
        else {
            item->update(camera,position,elapsed);flushCharacterUpdateListeners();
            if (item->m_bInActiveRange && item->ISA(static_cast<UNITTYPES::EUNITTYPES>(0x1d)))
                for (TLinkedListNode<iLevelUpdatedCharacter*>* listener=m_characterUpdateListeners->getHead();listener;) {
                    iLevelUpdatedCharacter* current=listener->m_Data;listener=listener->m_pNext;
                    current->itemUpdatedInLevel(elapsed,item);
                }
        }
    }
    flushCharacterUpdateListeners();
}

CBaseUnit* CLevel::addUnit(CBaseUnit* unit,const Ogre::Vector3& position)
{
    if (unit) {
        CCharacter* character=dynamic_cast<CCharacter*>(unit);
        if (character) return addCharacter(character,position,false);
        CItem* item=dynamic_cast<CItem*>(unit);
        if (item) return addItem(item,position,true);
    }
    return unit;
}

#include "TimerStatics.h"
#include "DataGroup.h"
#include "UtilitiesMath.h"

void CLevel::pushTime()
{
    if (m_timerStatics) m_timerStatics->m_times.add(static_cast<unsigned int>(m_timerStatics->m_timer.getMicroseconds()));
}

void CLevel::popTime(const wchar_t* name)
{
    if (m_timerStatics) m_timerStatics->popTime(name);
}

void CLevel::setInited(bool initialized)
{
    if (m_timerStatics) {
        m_timerStatics->getStatics(true);
        if (m_timerStatics) {delete m_timerStatics;m_timerStatics=NULL;}
    }
    m_automapRoomPieces=initialized;
    for (TLinkedListNode<CCharacter*>* p=m_pCharacters->getHead();p;p=p->m_pNext)
        if (p->m_Data) p->m_Data->levelLoaded(this);
}

float CLevel::floorHeight(Ogre::Vector3 point)
{
    Ogre::Vector3 start(point.x,400.0f,point.z),end(point.x,-100.0f,point.z);
    Ogre::Vector3 hit,normal,faceNormal;unsigned int material;
    if (rayCollision(start,end,hit,normal,material,faceNormal,false)) return hit.y;
    return 0.0f;
}

void CLevel::activate()
{
    unsigned int count=m_RoomScenes.size();std::wstring newline(L"\n");
    for (unsigned int i=0;i<count;++i) {CEditorScene* scene=m_RoomScenes[i];scene->setEnabled(true);scene->setActivated(true);}
    clearOutRoomPieces();findParticles();
}

const std::wstring& getStringFromDataGroup(CDataGroup* group,std::wstring& childName,const std::wstring& fallback)
{
    CDataGroup* child=group->GetDataGroupByName(childName,false);
    if (child) return child->GetDataValue(L"VALUE",fallback);
    return fallback;
}

Ogre::Vector3 CLevel::randomOpenItemPositionRange(const Ogre::Vector3& position,float minimum,float maximum,bool avoidNoSpawn)
{
    for (unsigned int attempt=0;attempt<100;++attempt) {
        Ogre::Vector3 offset(0.0f,0.0f,UTILITIES::randomBetweenVolatile(minimum,maximum));
        float angle=UTILITIES::randomBetweenVolatile(0.0f,360.0f)*0.01745329238474369f;
        MATH::rotateY(&offset,angle);Ogre::Vector3 candidate=position+offset;
        if (mapPassable(candidate) && (!avoidNoSpawn || !isInNoSpawnRegion(candidate,1.0f))) return candidate;
        if (attempt+1>5) maximum+=0.1f;
    }
    return position;
}

Ogre::Vector3 CLevel::randomOpenPositionRange(const Ogre::Vector3& position,float minimum,float maximum,bool avoidNoSpawn)
{
    for (unsigned int attempt=0;attempt<100;++attempt) {
        Ogre::Vector3 offset(0.0f,0.0f,UTILITIES::randomBetweenVolatile(minimum,maximum));
        float angle=UTILITIES::randomBetweenVolatile(0.0f,360.0f)*0.01745329238474369f;
        MATH::rotateY(&offset,angle);Ogre::Vector3 candidate=position+offset;
        bool valid=true;
        // The original repeats the query at candidate; the loop coordinates
        // determine the number of checks without changing its position.
        for (float x=candidate.x-0.8f;x<=candidate.x+0.8f;x+=0.4f)
            for (float z=candidate.z-0.8f;z<=candidate.z+0.8f;z+=0.4f)
                if (!mapPassable(candidate) || !positionPassable(candidate) ||
                    (avoidNoSpawn && isInNoSpawnRegion(candidate,0.0f))) valid=false;
        if (valid) return candidate;
        if (attempt+1>5) maximum=std::max(5.0f,maximum+0.1f);
    }
    return position;
}

bool CLevel::passableBetween(Ogre::Vector3 start,const Ogre::Vector3& end,bool mapOnly)
{
    Ogre::Vector3 step(end.x-start.x,0.0f,end.z-start.z);float length=step.length();step.normalise();step*=0.1f;
    for (float distance=0.0f;distance<=length;distance+=0.1f) {
        if (mapOnly ? !mapPassable(start) : !positionPassable(start)) return false;
        start+=step;
    }
    return true;
}

#include "EmptyStrings.h"
#include "StringTranslate.h"
#include "StringUtilities.h"
#include "MasterResourceManager.h"
#include "Settings.h"

std::wstring CLevel::getName()
{
    if (!m_pLevelTemplateData) return EMPTY_WSTRING;
    if (!m_pLevelTemplateData->m_showFloorNumber) return m_pLevelTemplateData->m_levelName;
    static std::wstring floor;
    if (floor.empty()) floor=CStringTranslate::getSinglton()->getTranslateString(L"Floor");
    std::wstring number=STRINGS::GetValueAsWString(m_iLevelDepth+1);
    return m_pLevelTemplateData->m_levelName+L" - "+floor+L" "+number;
}

void parseDataGroupForRoomPiece(CDataGroup* group,FILE* file)
{
    if (!group) return;
    for (unsigned int i=0;i<group->GetNumberOfDataGroups();++i) {
        CDataGroup* properties=group->GetDataGroup(i)->GetDataGroupByName(L"PROPERTIES",false);
        if (properties) {
            properties->GetDataValue(L"DESCRIPTOR",EMPTY_WSTRING).compare(L"Room Piece");
            parseDataGroupForRoomPiece(group->GetDataGroup(i)->GetDataGroupByName(L"CHILDREN",false),file);
        }
    }
}

void CLevel::toggleAutomap()
{
    if (!m_automap) return;
    if (!m_automap->m_bVisible) {
        CMasterResourceManager::getSingleton()->m_pSettings->SetInt(KSETTINGS_AUTOMAP,1);
        m_automap->setFullscreen(false);m_automap->setVisible(true);
    } else if (!m_automap->m_bFullscreen) {
        CMasterResourceManager::getSingleton()->m_pSettings->SetInt(KSETTINGS_AUTOMAP,2);
        m_automap->setFullscreen(true);
    } else {
        CMasterResourceManager::getSingleton()->m_pSettings->SetInt(KSETTINGS_AUTOMAP,0);
        m_automap->setVisible(false);
    }
}

bool CLevel::objectRayCollision(const Ogre::Vector3& start,const Ogre::Vector3& end,Ogre::Vector3& hit,Ogre::Vector3& normal,unsigned int& material,CBaseUnit** collided,bool flag)
{
    float nearest=99999.0f;
    for (TLinkedListNode<CCharacter*>* p=m_activeCharacters->getHead();p;p=p->m_pNext) {
        CCharacter* unit=p->m_Data;
        if (!unit->m_bBlocksPath || !unit->m_bPathingFlag19C || (flag && !unit->m_bBaseUnitFlag18E)) continue;
        Ogre::Vector3 localHit,localNormal;
        if (unit->rayCollision(start,end,localHit,localNormal,false)) {
            float distance=(localHit-start).length();
            if (distance<nearest) {
                if (collided) *collided=p->m_Data;
                material=2000;hit=localHit;normal=localNormal;nearest=distance;
            }
        }
    }
    for (TLinkedListNode<CItem*>* p=m_activeItems->getHead();p;p=p->m_pNext) {
        CItem* unit=p->m_Data;
        if (!unit->m_bBlocksPath || !unit->m_bPathingFlag19C || (flag && !unit->m_bBaseUnitFlag18E)) continue;
        Ogre::Vector3 localHit,localNormal;
        if (unit->rayCollision(start,end,localHit,localNormal,false)) {
            float distance=(localHit-start).length();
            if (distance<nearest) {
                if (collided) *collided=p->m_Data;
                material=100;hit=localHit;normal=localNormal;nearest=distance;
            }
        }
    }
    return nearest!=99999.0f;
}

bool CLevel::objectSphereCollision(const Ogre::Vector3& start,const Ogre::Vector3& end,float radius,Ogre::Vector3& position,Ogre::Vector3& hit,Ogre::Vector3& normal,unsigned int& material,CBaseUnit** collided,bool flag)
{
    float nearest=99999.0f;
    for (TLinkedListNode<CCharacter*>* p=m_activeCharacters->getHead();p;p=p->m_pNext) {
        CCharacter* unit=p->m_Data;
        if (!unit->m_bBlocksPath || !unit->m_bPathingFlag19C || (flag && !unit->m_bBaseUnitFlag18E)) continue;
        Ogre::Vector3 localHit,localNormal,localPosition;
        if (unit->sphereCollision(start,end,radius,localPosition,localHit,localNormal)) {
            float distance=(localHit-start).length();
            if (distance<nearest) {
                if (collided) *collided=p->m_Data;
                material=2000;position=localPosition;hit=localHit;normal=localNormal;nearest=distance;
            }
        }
    }
    for (TLinkedListNode<CItem*>* p=m_activeItems->getHead();p;p=p->m_pNext) {
        CItem* unit=p->m_Data;
        if (!unit->m_bBlocksPath || !unit->m_bPathingFlag19C || (flag && !unit->m_bBaseUnitFlag18E)) continue;
        Ogre::Vector3 localHit,localNormal,localPosition;
        if (unit->sphereCollision(start,end,radius,localPosition,localHit,localNormal)) {
            float distance=(localHit-start).length();
            if (distance<nearest) {
                if (collided) *collided=p->m_Data;
                material=100;position=localPosition;hit=localHit;normal=localNormal;nearest=distance;
            }
        }
    }
    return nearest!=99999.0f;
}


#include "CollisionList.h"
bool CLevel::preSortedSphereCollision(const Ogre::Vector3& start,const Ogre::Vector3& end,float radius,
    Ogre::Vector3& position,Ogre::Vector3& hit,Ogre::Vector3& normal,unsigned int& material,Ogre::Vector3& faceNormal,bool flag)
{
    float distance=99999.0f,nearest=99999.0f;Ogre::Vector3 localPosition,localHit,localNormal;
    if (!flag && objectSphereCollision(start,end,radius,localPosition,localHit,localNormal,material,NULL,true)) {
        nearest=(localHit-start).length();position=localPosition;hit=localHit;normal=localNormal;faceNormal=Ogre::Vector3(1.0f,1.0f,1.0f);
    }
    Ogre::Vector3 minimum=start,maximum=start;MATH::expandBounds(minimum,maximum,end);
    minimum-=Ogre::Vector3(radius,radius,radius);maximum+=Ogre::Vector3(radius,radius,radius);
    m_collisionList->sphereCollision(m_collisionIndices,start,end,minimum,maximum,radius,localPosition,localHit,localNormal,material,faceNormal,distance);
    if (distance!=99999.0f) {
        float hitDistance=(localHit-start).length();
        if (hitDistance<nearest) {position=localPosition;hit=localHit;normal=localNormal;nearest=hitDistance;}
    }
    return nearest!=99999.0f;
}

bool CLevel::preSortedSphereCollision(const Ogre::Vector3& start,const Ogre::Vector3& end,float radius,
    Ogre::Vector3& position,Ogre::Vector3& hit,Ogre::Vector3& normal,unsigned int& material,Ogre::Vector3& faceNormal,CBaseUnit** collided,bool flag)
{
    float distance=99999.0f,nearest=99999.0f;Ogre::Vector3 localPosition,localHit,localNormal;
    if (flag && objectSphereCollision(start,end,radius,localPosition,localHit,localNormal,material,collided,false)) {
        nearest=(localHit-start).length();position=localPosition;hit=localHit;normal=localNormal;faceNormal=Ogre::Vector3(1.0f,1.0f,1.0f);
    }
    Ogre::Vector3 minimum=start,maximum=start;MATH::expandBounds(minimum,maximum,end);
    minimum-=Ogre::Vector3(radius,radius,radius);maximum+=Ogre::Vector3(radius,radius,radius);
    m_collisionList->sphereCollision(m_collisionIndices,start,end,minimum,maximum,radius,localPosition,localHit,localNormal,material,faceNormal,distance);
    if (distance!=99999.0f) {
        float hitDistance=(localHit-start).length();
        if (hitDistance<nearest) {position=localPosition;hit=localHit;normal=localNormal;nearest=hitDistance;}
    }
    return nearest!=99999.0f;
}

bool CLevel::preSortedRayCollision(const Ogre::Vector3& start,const Ogre::Vector3& end,Ogre::Vector3& hit,
    Ogre::Vector3& normal,unsigned int& material,Ogre::Vector3& faceNormal,bool flag)
{
    float distance=99999.0f,nearest=99999.0f;Ogre::Vector3 localHit,localNormal;
    Ogre::Vector3 minimum=start,maximum=start;MATH::expandBounds(minimum,maximum,end);
    if (!flag && objectRayCollision(start,end,localHit,localNormal,material,NULL,true)) {
        nearest=(localHit-start).length();distance=nearest;hit=localHit;normal=localNormal;faceNormal=Ogre::Vector3(1.0f,1.0f,1.0f);
    }
    m_collisionList->rayCollision(m_collisionIndices,start,end,minimum,maximum,localHit,localNormal,material,faceNormal,distance);
    if (distance<nearest) {hit=localHit;normal=localNormal;faceNormal=Ogre::Vector3(1.0f,1.0f,1.0f);nearest=distance;}
    return nearest!=99999.0f;
}

#include "RoomPiece.h"
#include "Light.h"
#include "GameUI.h"
#include "Console.h"
#include "Layout.h"
#include "QuestManager.h"

void CLevel::updateMaterialAmbient()
{
    Ogre::ColourValue ambient(m_pLevelTemplateData->m_materialAmbientColorR,m_pLevelTemplateData->m_materialAmbientColorG,
                              m_pLevelTemplateData->m_materialAmbientColorB,m_pLevelTemplateData->m_materialAmbientColorA);
    unsigned int count=m_RoomScenes.size();
    for (unsigned int i=0;i<count;++i) {
        CEditorScene* scene=m_RoomScenes[i];TArrayList<CEditorBaseObject*> objects(10);
        scene->GetObjectsCreatedByADescriptor(L"Scene Object",&objects);
        if (!objects.size()) {
            TArrayList<CEditorBaseObject*> pieces(10);scene->GetObjectsCreatedByADescriptor(L"Room Piece",&pieces);
            for (unsigned int j=0;j<pieces.size();++j) {
                CRoomPiece* piece=dynamic_cast<CRoomPiece*>(pieces[j]);
                if (piece && piece->m_pGenericModel) piece->m_pGenericModel->setAmbient(ambient);
            }
        }
    }
}

void CLevel::loadRoomLayout(std::wstring name,bool layoutFile,ELevelEntryType entry,std::vector<std::wstring>* extra,std::wstring waypoint)
{
    if (m_pLevelTemplateData && m_pLevelTemplateData->m_state761) {delete m_pLevelTemplateData;m_pLevelTemplateData=NULL;}
    if (layoutFile) {
        m_resourceManager->m_bFlag2=true;
        m_pLevelTemplateData=new CLevelTemplateData(L"media/layouts/cave/rules.dat");m_pLevelTemplateData->m_state761=true;
        CLayout* layout=new CLayout(m_resourceManager,static_cast<ELAYOUT_TYPES>(0));layout->setEnabled(false);layout->clearObjectIndex();
        layout->loadLayoutFile(name,true,NULL,false,false,0);mergeLayoutsForRoomPiece(name,layout);m_RoomScenes.add(layout);
        loadRoomLayout(static_cast<CLevelTemplateData*>(NULL),true,entry,extra,waypoint);m_resourceManager->m_bFlag2=false;
    } else {
        m_pLevelTemplateData=new CLevelTemplateData(name.c_str());m_pLevelTemplateData->m_state761=true;
        loadRoomLayout(m_pLevelTemplateData,false,entry,extra,waypoint);
    }
}

void CLevel::updateNPCIcons()
{
    if (!m_pGameClient || !m_pGameClient->getPlayer()) return;
    for (TLinkedListNode<CCharacter*>* p=m_pCharacters->getHead();p;p=p->m_pNext) {
        CCharacter* character=p->m_Data;
        if (!character || character->m_bBaseUnitFlag190) continue;
        if (!character->getEnabled() && character->m_forcedHidden) continue;
        if (static_cast<unsigned char>(m_pGameClient->getPlayer()->getQuestManager()->calculateNPCIcon(character))) continue;
        const wchar_t* theme=NULL;
        if (character->ISA(static_cast<UNITTYPES::EUNITTYPES>(0x7f))) theme=L"GAMBLER";
        else if (character->ISA(static_cast<UNITTYPES::EUNITTYPES>(0x82))) theme=L"ENCHANTER";
        else if (character->ISA(static_cast<UNITTYPES::EUNITTYPES>(0x86))) theme=L"TRANSMUTE";
        else if (character->ISA(static_cast<UNITTYPES::EUNITTYPES>(0x85))) theme=L"GEMRETRIEVE";
        else if (character->ISA(static_cast<UNITTYPES::EUNITTYPES>(0x84))) theme=L"GEMRECOVER";
        else if (character->ISA(static_cast<UNITTYPES::EUNITTYPES>(0x29))) theme=L"MERCHANT";
        if (theme) character->addUnitTheme(std::wstring(theme));
    }
}

#include "SkillManager.h"
#include "Skill.h"
#include "MissilePreloader.h"
#include "ItemGold.h"
#include "iLevelUpdatedCharacter.h"

void CLevel::notifyOfDeletion(CItem* item)
{
    m_resourceManager->getMissilePreloader()->notifyOfDeletion(NULL, item);
    m_pGameClient->notifyOfDeletion(item);
    for (TLinkedListNode<CCharacter*>* node = m_pCharacters->m_pHead; node; node = node->m_pNext)
        node->m_Data->notifyOfDeletion(item);
    CSkillManager* skills = item->m_pSkillManager;
    if (skills) {
        for (std::map<std::wstring,TArrayList<CSkill*>*>::iterator it = skills->m_SkillsByName.begin();
             it != skills->m_SkillsByName.end(); ++it) {
            TArrayList<CSkill*>* list = it->second;
            if (list) for (unsigned int i = 0; i < list->size(); ++i)
                // Native code passes the unadjusted skill address as an opaque
                // missile observer identity; the callee only compares it.
                m_resourceManager->getMissilePreloader()->notifyOfDeletion(reinterpret_cast<iMissile*>((*list)[i]), NULL);
        }
    }
}

void CLevel::notifyOfDeletion(CCharacter* character)
{
    m_resourceManager->getMissilePreloader()->notifyOfDeletion(NULL, character);
    m_pGameClient->notifyOfDeletion(character);
    for (TLinkedListNode<CCharacter*>* node = m_pCharacters->m_pHead; node; node = node->m_pNext)
        node->m_Data->notifyOfDeletion(character);
    CSkillManager* skills = character->m_pSkillManager;
    if (skills) {
        for (std::map<std::wstring,TArrayList<CSkill*>*>::iterator it = skills->m_SkillsByName.begin();
             it != skills->m_SkillsByName.end(); ++it) {
            TArrayList<CSkill*>* list = it->second;
            if (list) for (unsigned int i = 0; i < list->size(); ++i)
                m_resourceManager->getMissilePreloader()->notifyOfDeletion(reinterpret_cast<iMissile*>((*list)[i]), NULL);
        }
    }
}

void CLevel::updateNearUnitList(const Ogre::Vector3& position)
{
    while (m_activeCharacters->m_pHead) {
        TLinkedListNode<CCharacter*>* node = m_activeCharacters->m_pHead;
        m_activeCharacters->m_pHead = node->m_pNext;
        node->m_pNext = NULL; node->m_pPrevious = NULL; delete node;
    }
    while (m_activeItems->m_pHead) {
        TLinkedListNode<CItem*>* node = m_activeItems->m_pHead;
        m_activeItems->m_pHead = node->m_pNext;
        node->m_pNext = NULL; node->m_pPrevious = NULL; delete node;
    }
    for (TLinkedListNode<CCharacter*>* node = m_pCharacters->m_pHead; node; node = node->m_pNext) {
        CCharacter* character = node->m_Data;
        character->calculateActiveRange(position);
        if (character->m_bInFadeRange) {
            TLinkedListNode<CCharacter*>* active = new TLinkedListNode<CCharacter*>;
            active->m_Data = character; active->m_pNext = m_activeCharacters->m_pHead; active->m_pPrevious = NULL;
            if (active->m_pNext) active->m_pNext->m_pPrevious = active;
            m_activeCharacters->m_pHead = active;
        } else character->setVisible(false, true);
    }
    if (m_items) for (TLinkedListNode<CItem*>* node = m_items->m_pHead; node; node = node->m_pNext) {
        CItem* item = node->m_Data;
        item->calculateActiveRange(position);
        if (item->m_bInFadeRange) {
            TLinkedListNode<CItem*>* active = new TLinkedListNode<CItem*>;
            active->m_Data = item; active->m_pNext = m_activeItems->m_pHead; active->m_pPrevious = NULL;
            if (active->m_pNext) active->m_pNext->m_pPrevious = active;
            m_activeItems->m_pHead = active;
        } else { item->setVisible(false, true); item->hideItemText(); }
    }
}

long long CLevel::addListenerToUnit(long long guid, iUnitObserver* observer)
{
    if (guid != -1) {
        std::map<long long,TArrayList<iUnitObserver*>*>::iterator it = m_unitObservers.find(guid);
        if (it == m_unitObservers.end()) {
            TArrayList<iUnitObserver*>* list = new TArrayList<iUnitObserver*>(25);
            m_unitObservers[guid] = list;
            list->add(observer);
        } else if (it->second->find(observer) == -1) it->second->add(observer);
    }
    return guid;
}

void CLevel::updateCharacters(Ogre::Camera* camera, const Ogre::Vector3& position, float elapsed, float speed)
{
    flushCharacterUpdateListeners();
    m_updatedCharacterCount = 0;
    float adjustedElapsed = elapsed * speed;
    TLinkedListNode<CCharacter*>* node = m_activeCharacters->m_pHead;
    while (node) {
        CCharacter* character = node->m_Data;
        node = node->m_pNext;
        if (character->m_bBaseUnitFlag190) {
            deleteCharacter(character);
            flushCharacterUpdateListeners();
            continue;
        }
        character->update(camera, position, character->ISA(UNITTYPES::PLAYER) ? elapsed : adjustedElapsed);
        if (character->m_bInActiveRange) {
            if (m_automap) {
                if (character->ISA(UNITTYPES::PLAYER)) m_automap->setPlayerPosition(character->getPosition(true));
                else if (character->m_pMaster && character->m_pMaster->ISA(UNITTYPES::PLAYER) &&
                         (character->m_pMaster->m_Followers.empty() ? NULL : character->m_pMaster->m_Followers[0]) == character) {
                    if (character->m_eAIState == static_cast<EAIState>(42)) m_automap->setPetVisible(false);
                    else { m_automap->setPetVisible(true); m_automap->setPetPosition(character->getPosition(true)); }
                }
            }
            flushCharacterUpdateListeners();
            TLinkedListNode<iLevelUpdatedCharacter*>* observer = m_characterUpdateListeners->m_pHead;
            while (observer) {
                iLevelUpdatedCharacter* listener = observer->m_Data;
                observer = observer->m_pNext;
                listener->characterUpdatedInLevel(elapsed, character);
            }
            ++m_updatedCharacterCount;
        }
    }
    flushCharacterUpdateListeners();
}

void CLevel::rollMoney(CCharacter* first, CCharacter* second, const Ogre::Vector3& position, bool always)
{
    if (second && second->m_spawnFlag703) return;
    for (unsigned int i = 0; i < 3; ++i) {
        if (!always && !(UTILITIES::randomBetweenVolatile(0.0f, 1.0f) < 0.1f)) continue;
        CCharacter* character = second ? second : first;
        int amount;
        if (character) {
            float scale = static_cast<float>(character->getLevel()->m_dungeonDepth) * 0.25f + 1.0f;
            amount = UTILITIES::randomIntegerBetweenVolatile(static_cast<int>(scale * 2.0f), static_cast<int>(scale * 12.0f));
        } else amount = UTILITIES::randomIntegerBetweenVolatile(2, 12);
        if (first) amount += static_cast<int>(static_cast<float>(amount) * first->getEffectValue(static_cast<EEFFECT_TYPE>(51), static_cast<EDAMAGE_TYPES>(7)) / 100.0f);
        CItemGold* gold = new CItemGold(m_resourceManager, amount);
        Ogre::Vector3 point = randomOpenItemPosition(position, 1.0f, false);
        addItem(gold, point, true);
        gold->playDropSound(gold->getSceneNode());
    }
}

void CLevel::rollTreasure(CCharacter* first, CCharacter* second, const Ogre::Vector3& position)
{
    TArrayList<CBaseUnit*> units(1);
    m_resourceManager->createUnitsBySpawnClass(L"BARREL_TREASURE", units, 1, NULL, first, m_dungeonDepth, 0);
    for (unsigned int i = 0; i < units.size(); ++i) addUnit(units[i], position);
    rollMoney(first, second, position, false);
}

#include "SkillProperty.h"
#include "SkillEvent.h"
#include "SkillEffectAndAffixes.h"
#include "EffectManager.h"

void CLevel::deleteTemporaryDungeonPortals(std::wstring dungeon)
{
    if (!m_items) return;
    for (TLinkedListNode<CItem*>* node = m_items->m_pHead; node; node = node->m_pNext) {
        CItem* item = node->m_Data;
        if (item->ISA(static_cast<UNITTYPES::EUNITTYPES>(173))) {
            if (item->m_pEffectManager && item->m_pEffectManager->hasEffect(static_cast<EEFFECT_TYPE>(113), dungeon)) {
                item->m_bBaseUnitFlag190 = true;
                if (m_pGameClient && m_pGameClient->getPlayer())
                    m_pGameClient->getPlayer()->clearDungeonHistory(dungeon);
            }
        }
        if (item->ISA(static_cast<UNITTYPES::EUNITTYPES>(165))) {
            CSkillManager* manager = item->m_pSkillManager;
            if (!manager || static_cast<int>(manager->m_OtherSkills.size()) <= 0 || !manager->m_OtherSkills[0]) continue;
            CSkill* skill = manager->m_OtherSkills[0];
            CSkillProperty* property = skill->m_property;
            if (!property && skill->m_iSkillLevelCount && skill->m_levelPropertyData[0]) property = skill->m_levelPropertyData[0];
            if (!property) continue;
            TArrayList<CSkillEvent*>* events = property->m_eventLists[0];
            if (!events) continue;
            for (unsigned int i = 0; i < events->size(); ++i) {
                CSkillEffectAndAffixes* effects = (*events)[i]->m_pSkillEffectAndAffixes;
                if (effects && effects->getPortalSkillName() == dungeon) item->m_bBaseUnitFlag190 = true;
            }
        }
    }
}

Ogre::Vector3 CLevel::findTemporaryDungeonPortal(std::wstring dungeon)
{
    if (m_items) for (TLinkedListNode<CItem*>* node = m_items->m_pHead; node; node = node->m_pNext) {
        CItem* item = node->m_Data;
        if (item->ISA(static_cast<UNITTYPES::EUNITTYPES>(173))) {
            if (item->m_pEffectManager && item->m_pEffectManager->hasEffect(static_cast<EEFFECT_TYPE>(113), dungeon))
                return item->getPosition(true);
        } else if (item->ISA(static_cast<UNITTYPES::EUNITTYPES>(165))) {
            CSkillManager* manager = item->m_pSkillManager;
            if (!manager || static_cast<int>(manager->m_OtherSkills.size()) <= 0 || !manager->m_OtherSkills[0]) continue;
            CSkill* skill = manager->m_OtherSkills[0];
            CSkillProperty* property = skill->m_property;
            if (!property && skill->m_iSkillLevelCount && skill->m_levelPropertyData[0]) property = skill->m_levelPropertyData[0];
            if (!property) continue;
            TArrayList<CSkillEvent*>* events = property->m_eventLists[0];
            if (!events) continue;
            for (unsigned int i = 0; i < events->size(); ++i) {
                CSkillEffectAndAffixes* effects = (*events)[i]->m_pSkillEffectAndAffixes;
                if (effects && effects->getPortalSkillName() == dungeon) return item->getPosition(true);
            }
        }
    }
    return Ogre::Vector3(-999.0f, -999.0f, -999.0f);
}

CCharacter* CLevel::addCharacter(CCharacter* character, const Ogre::Vector3& position, bool alreadyActive)
{
    if (!character) return NULL;
    TLinkedList<CCharacter*>* lists[2] = {m_pCharacters, m_activeCharacters};
    for (unsigned int i = 0; i < 2; ++i) {
        TLinkedListNode<CCharacter*>* node = new TLinkedListNode<CCharacter*>;
        node->m_Data = character;
        node->m_pNext = lists[i]->m_pHead;
        node->m_pPrevious = NULL;
        if (node->m_pNext) node->m_pNext->m_pPrevious = node;
        lists[i]->m_pHead = node;
    }
    if (!alreadyActive && !m_resourceManager->m_bFlag3) {
        character->activateUnitInLevel();
        character->setPosition(position);
        character->m_iRoomIndex = getRoomIndexThatPositionIsIn(position);
        character->createPathfinder(*this);
        character->dropToGround(*this, 4.0f, false);
        character->addToAvoidanceMap(*this);
        character->m_currentOpacity = 1.0f;
        character->updateOpacity(0.0f, true);
        character->setRimlight(m_pLevelTemplateData ? m_pLevelTemplateData->m_sRimlightTexture : L"media/sharedtextures/rimlight.dds");
    }
    return character;
}

#include "CameraControl.h"
#include "Settings.h"
#include <OgreColourValue.h>

CItem* CLevel::addItem(CItem* item, const Ogre::Vector3& position, bool drop)
{
    TLinkedListNode<CItem*>* itemNode = new TLinkedListNode<CItem*>;
    itemNode->m_Data = item;
    itemNode->m_pNext = m_items->m_pHead;
    itemNode->m_pPrevious = NULL;
    if (itemNode->m_pNext) itemNode->m_pNext->m_pPrevious = itemNode;
    m_items->m_pHead = itemNode;
    TLinkedListNode<CItem*>* activeNode = new TLinkedListNode<CItem*>;
    activeNode->m_Data = item;
    activeNode->m_pNext = m_activeItems->m_pHead;
    activeNode->m_pPrevious = NULL;
    if (activeNode->m_pNext) activeNode->m_pNext->m_pPrevious = activeNode;
    m_activeItems->m_pHead = activeNode;
    if (m_resourceManager->m_bFlag3) return item;
    item->setPosition(position);
    item->activateUnitInLevel();
    item->m_fOpacity = 1.0f;
    item->updateOpacity(0.0f, true);
    item->m_iRoomIndex = getRoomIndexThatPositionIsIn(position);
    CEquipment* equipment = dynamic_cast<CEquipment*>(item);
    if (equipment) {
        if (drop) equipment->drop();
        else equipment->activateDropParticles();
    }
    if (drop && item->ISA(static_cast<UNITTYPES::EUNITTYPES>(34)))
        static_cast<CItemGold*>(item)->playDropSound(item->getSceneNode());
    if (!item->m_bLevelLighting) {
        item->setRimlight(m_pLevelTemplateData ? m_pLevelTemplateData->m_sRimlightTexture : L"media/sharedtextures/rimlight.dds");
        if (!item->m_bLevelLighting) return item;
    }
    if (CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_LIGHTING_ENABLED) == 1) {
        CCameraControl* camera = m_pGameClient->m_cameraControl;
        static_cast<CGenericModel*>(item->getUnitModel())->setProjectorPass(
            camera->m_pUnknown30, camera->m_pUnknown28,
            m_pGameClient->m_projectorTexture, m_pGameClient->m_projectorFalloffTexture);
    }
    Ogre::ColourValue ambient;
    if (CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_OVERRIDE_LIGHTING) > 0) {
        int blue = CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_MATERIAL_AMBIENT_LIGHT_BLUE);
        int green = CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_MATERIAL_AMBIENT_LIGHT_GREEN);
        int red = CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_MATERIAL_AMBIENT_LIGHT_RED);
        ambient = Ogre::ColourValue(static_cast<float>(red) / 255.0f,
                                   static_cast<float>(green) / 255.0f,
                                   static_cast<float>(blue) / 255.0f, 1.0f);
    } else {
        if (!m_pLevelTemplateData) return item;
        ambient = Ogre::ColourValue(m_pLevelTemplateData->m_materialAmbientColorR,
                                   m_pLevelTemplateData->m_materialAmbientColorG,
                                   m_pLevelTemplateData->m_materialAmbientColorB,
                                   m_pLevelTemplateData->m_materialAmbientColorA);
    }
    static_cast<CGenericModel*>(item->getUnitModel())->setAmbient(ambient);
    return item;
}
