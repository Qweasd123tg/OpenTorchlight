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

#include "Warper.h"
#include "StringUtilities.h"

int CLevel::placePlayerAtWarpToDungeonFloor(std::wstring dungeon, int floor,
                                          bool, std::wstring entryName)
{
    CPlayer* player = m_pGameClient->m_pPlayer;
    if (!player) return 0;
    int delta;
    if (dungeon == m_sDungeonName) {
        delta = floor - m_iLevelDepth;
    } else {
        floor = 0;
        delta = 0;
    }
    TArrayList<CEditorBaseObject*> objects(10);
    for (unsigned int i = 0; i < m_RoomScenes.size(); ++i) {
        CEditorScene* scene = m_RoomScenes[i];
        if (!scene) continue;
        objects.clear();
        scene->GetObjectsCreatedByADescriptor(L"Warper", &objects);
        for (unsigned int j = 0; j < objects.size(); ++j) {
            CEditorBaseObject* object = objects[j];
            if (!object) continue;
            CWarper* warp = dynamic_cast<CWarper*>(object);
            if (!warp) continue;
            if (warp->getName() != EMPTY_WSTRING && dungeon != EMPTY_WSTRING &&
                STRINGS::StringUpper(warp->getName()) == STRINGS::StringUpper(entryName)) {
                player->setPosition(warp->getPosition(true));
                player->setDirection(warp->getForwardAbsolute());
                return 1;
            }
            if ((STRINGS::StringUpper(warp->m_sDungeon) == dungeon ||
                 (dungeon == L"MAIN" && warp->m_sDungeon == EMPTY_WSTRING)) &&
                ((warp->m_iLevelDelta == 0 && warp->m_iLevelDepth == floor) ||
                 (warp->m_iLevelDepth == 0 && warp->m_iLevelDelta == delta))) {
                player->setPosition(warp->getPosition(true));
                player->setDirection(warp->getForwardAbsolute());
                return 1;
            }
        }
    }
    return 0;
}

#include "LogicNodeState.h"
#include "UTFConversion.h"

void CLogicNodeState::save(FILE* file)
{
    unsigned short length = static_cast<unsigned short>(m_wstrName.size());
    fwrite(&length, 2, 1, file);
    WriteUTF32ToUTF16(file, m_wstrName, length);
    unsigned char flag = m_bActive;
    fwrite(&flag, 1, 1, file);
    flag = m_bEnabled;
    fwrite(&flag, 1, 1, file);
    flag = m_bFailed;
    fwrite(&flag, 1, 1, file);
    flag = m_bActive;
    fwrite(&flag, 1, 1, file);
    fwrite(&m_nNodeId, 4, 1, file);
    fwrite(&m_nParentNodeId, 4, 1, file);
    fwrite(&m_nStateFlags, 4, 1, file);
    fwrite(&m_nCurrentState, 4, 1, file);
    fwrite(&m_guid, 8, 1, file);
    fwrite(&m_parentGuid, 8, 1, file);
    fwrite(&m_parentHierarchyHash, 8, 1, file);
    fwrite(&m_position, 12, 1, file);
    flag = m_bPersistent;
    fwrite(&flag, 1, 1, file);
    fwrite(&m_nStateVersion, 4, 1, file);
}

void CLevel::decrementMapPassabilityCollision(const Ogre::AxisAlignedBox& bounds, CBaseUnit* unit)
{
    int firstX = levelGridLimit(static_cast<int>(::floorf((bounds.getMinimum().x - topLeftX()) / 0.4f)), m_passWidth);
    int firstZ = levelGridLimit(static_cast<int>(::floorf((bounds.getMinimum().z - topLeftY()) / 0.4f)), m_passHeight);
    int lastX = levelGridLimit(static_cast<int>(::floorf((bounds.getMaximum().x - topLeftX()) / 0.4f)), m_passWidth);
    int lastZ = levelGridLimit(static_cast<int>(::floorf((bounds.getMaximum().z - topLeftY()) / 0.4f)), m_passHeight);
    for (int x = firstX; x < lastX; ++x) {
        for (int z = firstZ; z < lastZ; ++z) {
            float worldX = topLeftX() + static_cast<float>(x) * 0.4f;
            float worldZ = topLeftY() + static_cast<float>(z) * 0.4f;
            Ogre::Vector3 hit, normal;
            if (unit->rayCollision(Ogre::Vector3(worldX, 1000.0f, worldZ),
                                   Ogre::Vector3(worldX, -1000.0f, worldZ), hit, normal, true))
                --m_mapPassability[x][z];
        }
    }
}

void CLevel::incrementMapPassabilityCollision(const Ogre::AxisAlignedBox& bounds, CBaseUnit* unit)
{
    int firstX = levelGridLimit(static_cast<int>(::floorf((bounds.getMinimum().x - topLeftX()) / 0.4f)), m_passWidth);
    int firstZ = levelGridLimit(static_cast<int>(::floorf((bounds.getMinimum().z - topLeftY()) / 0.4f)), m_passHeight);
    int lastX = levelGridLimit(static_cast<int>(::floorf((bounds.getMaximum().x - topLeftX()) / 0.4f)), m_passWidth);
    int lastZ = levelGridLimit(static_cast<int>(::floorf((bounds.getMaximum().z - topLeftY()) / 0.4f)), m_passHeight);
    for (int x = firstX; x < lastX; ++x) {
        for (int z = firstZ; z < lastZ; ++z) {
            float worldX = topLeftX() + static_cast<float>(x) * 0.4f;
            float worldZ = topLeftY() + static_cast<float>(z) * 0.4f;
            Ogre::Vector3 hit, normal;
            if (unit->rayCollision(Ogre::Vector3(worldX, 1000.0f, worldZ),
                                   Ogre::Vector3(worldX, -1000.0f, worldZ), hit, normal, true))
                ++m_mapPassability[x][z];
        }
    }
}

CItem* CLevel::findItemWithinView(const Ogre::Matrix4& transform, float angle, float distance)
{
    Ogre::Matrix4 inverse = transform.inverse();
    for (TLinkedListNode<CItem*>* node = m_items->m_pHead; node; node = node->m_pNext) {
        CItem* item = node->m_Data;
        if (!item->m_bItemFlag1F0 || !item->m_bInActiveRange || !item->getEnabled() ||
            !item->ISA(static_cast<UNITTYPES::EUNITTYPES>(29))) continue;
        Ogre::Vector3 local = inverse * item->getPosition(true);
        local.y = 0.0f;
        float length = local.length();
        float direction = ::fabsf(::atan2f(local.x, local.z) * (180.0f / 3.14159f));
        if (!(direction <= angle && length <= distance)) continue;
        Ogre::Vector3 from(transform[0][3], transform[1][3], transform[2][3]);
        Ogre::Vector3 to = item->getPosition(true);
        to.y += 5.0f;
        from.y += 5.0f;
        if (sightUnobstructed(from, to, false)) return item;
    }
    return NULL;
}

#include "TriggerUnit.h"
void CLevel::updateAutomapIcons()
{
    if (m_automap)
    {
        m_automap->clearNPCIcons();
        if (m_pCharacters)
            for (TLinkedListNode<CCharacter*>* node = m_pCharacters->m_pHead; node; node = node->m_pNext)
            {
                node->m_Data->m_automapBillboard = NULL;
                if (!node->m_Data->getEnabled() || node->m_Data->m_bBaseUnitFlag190)
                    continue;
                if (node->m_Data->ISA(static_cast<UNITTYPES::EUNITTYPES>(127)))
                    { Ogre::Billboard* billboard = m_automap->addTile(31, node->m_Data->getPosition(true), Ogre::Vector3(1, 0, -1), true, true); node->m_Data->m_automapBillboard = billboard; }
                else if (node->m_Data->ISA(static_cast<UNITTYPES::EUNITTYPES>(130)))
                    { Ogre::Billboard* billboard = m_automap->addTile(29, node->m_Data->getPosition(true), Ogre::Vector3(1, 0, -1), true, true); node->m_Data->m_automapBillboard = billboard; }
                else if (node->m_Data->ISA(static_cast<UNITTYPES::EUNITTYPES>(134)))
                    { Ogre::Billboard* billboard = m_automap->addTile(32, node->m_Data->getPosition(true), Ogre::Vector3(1, 0, -1), true, true); node->m_Data->m_automapBillboard = billboard; }
                else if (node->m_Data->ISA(static_cast<UNITTYPES::EUNITTYPES>(133)))
                    { Ogre::Billboard* billboard = m_automap->addTile(33, node->m_Data->getPosition(true), Ogre::Vector3(1, 0, -1), true, true); node->m_Data->m_automapBillboard = billboard; }
                else if (node->m_Data->ISA(static_cast<UNITTYPES::EUNITTYPES>(132)))
                    { Ogre::Billboard* billboard = m_automap->addTile(30, node->m_Data->getPosition(true), Ogre::Vector3(1, 0, -1), true, true); node->m_Data->m_automapBillboard = billboard; }
                else if (node->m_Data->ISA(static_cast<UNITTYPES::EUNITTYPES>(41)))
                    { Ogre::Billboard* billboard = m_automap->addTile(25, node->m_Data->getPosition(true), Ogre::Vector3(1, 0, -1), true, true); node->m_Data->m_automapBillboard = billboard; }
                else if (node->m_Data->ISA(static_cast<UNITTYPES::EUNITTYPES>(131)) && m_pGameClient && m_pGameClient->m_pPlayer)
                {
                    int icon = m_pGameClient->m_pPlayer->getQuestManager()->getNPCIcon(node->m_Data);
                    if (icon != -1)
                        { Ogre::Billboard* billboard = m_automap->addTile(icon, node->m_Data->getPosition(true), Ogre::Vector3(1, 0, -1), true, true); node->m_Data->m_automapBillboard = billboard; }
                }
            }
    }
    if (m_items)
        for (TLinkedListNode<CItem*>* node = m_items->m_pHead; node; node = node->m_pNext)
        {
            CTriggerUnit* trigger = dynamic_cast<CTriggerUnit*>(node->m_Data);
            if (trigger && trigger->getEnabled() && !trigger->m_bBaseUnitFlag190)
            {
                if (trigger->ISA(static_cast<UNITTYPES::EUNITTYPES>(43)))
                    m_automap->addTile(34, trigger->getPosition(true), Ogre::Vector3(1, 0, -1), true, true);
                else if (trigger->ISA(static_cast<UNITTYPES::EUNITTYPES>(171)))
                    m_automap->addTile(34, trigger->getPosition(true), Ogre::Vector3(1, 0, -1), true, true);
            }
        }
}

#include "FileSystem.h"
#include "FileUtilities.h"
void CLevel::mergeLayoutsForRoomPiece(const std::wstring& path, CLayout* target)
{
    if (m_resourceManager->getEditorIsRunning() || !target)
        return;
    std::wstring directory = FILESYSTEM::GetDirectory(path) + L"MERGE/";
    TArrayList<std::wstring> files(5);
    CFileSystem::getSingleton()->getFileList(directory, files, L"*.layout", true, true, false, false);
    for (unsigned int i = 0; i < files.size(); ++i)
    {
        CLayout* layout = static_cast<CLayout*>(target->CreateObjectByDescriptor(std::wstring(L"Layout Link"), true));
        layout->loadLayoutFile(files[i], true, NULL, false, false, 0);
        layout->setPosition(0.0f, 0.0f, 0.0f);
        layout->setVisible(true);
    }
}

#include <OgreTechnique.h>
#include <OgrePass.h>
void CLevel::clearProjectorPass(CGenericModel* model, CGenericModel* other)
{
    if (other)
        other->clearProjectorPass();
    if (model && STRINGS::StringUpper(std::wstring(model->m_sModelPath)).find(L"LIGHT") != 0)
        model->clearProjectorPass();
    if (m_items)
    {
        for (TLinkedListNode<CItem*>* node = m_items->m_pHead; node; node = node->m_pNext)
            if (node->m_Data->m_bLevelLighting)
                static_cast<CGenericModel*>(node->m_Data->getUnitModel())->clearProjectorPass();
    }
    for (unsigned int i = 0; i < m_renderableStates.size(); ++i)
    {
        if (!m_renderableStates[i].m_flag31)
            continue;
        Ogre::Material* material = m_renderableStates[i].material;
        Ogre::Pass* pass = material->getTechnique(0)->getPass(0);
        unsigned short count = pass->getNumTextureUnitStates();
        int index = m_renderableStates[i].projectorPass;
        if (count <= index)
            continue;
        if (m_renderableStates[i].m_flag30 &&
            CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_SHADOWS_ENABLED))
        {
            unsigned short remove = index > 1 ? index - 1 : count - 2;
            pass->removeTextureUnitState(remove);
            pass->removeTextureUnitState(remove);
        }
        else
            pass->removeTextureUnitState(index > 1 ? index - 1 : count - 1);
        m_renderableStates[i].projectorTechnique = -1;
        material->compile(true);
    }
}

void CLevel::addRoomPieceToAutomap(CRoomPiece* piece)
{
    if (!piece || !piece->getSceneOwner())
        return;
    Ogre::Vector3 position = piece->getPosition(true);
    Ogre::Quaternion orientation = piece->m_pParentSceneNode->getOrientation() * piece->getOrientationQuaternion();
    Ogre::Matrix3 rotation;
    orientation.ToRotationMatrix(rotation);
    Ogre::Vector3 direction(rotation[0][2], rotation[1][2], rotation[2][2]);
    if (piece->m_iUnknown158 == 27)
    {
        if (m_pLevelTemplateData->m_automap != EMPTY_WSTRING)
            m_automap->setFullMap(m_pLevelTemplateData->m_automap,
                                 m_pLevelTemplateData->m_automapWidth,
                                 m_pLevelTemplateData->m_automapHeight,
                                 position, direction,
                                 m_pLevelTemplateData->m_automapAngle);
    }
    else
        m_automap->addTile(piece->m_iUnknown158, position, direction, true, false);
}

CLevel::CLevel(std::wstring dungeon, CSettings*, CGameClient* client,
               CResourceManager* resources, Ogre::SceneManager* scene,
               CSoundManager*, int seed, int depth)
    : m_RoomScenes(10), m_roomBounds(10), m_mapPassability(NULL), m_objectPassability(NULL), m_passWidth(0),
      m_passHeight(0), m_collisionTree(NULL), m_collisionList(NULL),
      m_activeCharacters(NULL), m_activeItems(NULL), m_updateObjects(10),
      m_characterUpdateListeners(NULL), m_noSpawnRegions(10),
      m_propertyNodesF0(10), m_propertyNodes108(10),
      m_resourceManager(resources), m_playerStart(0, 0, 0),
      m_startDirection(0, 0, 1), m_secondaryStart(0, 0, 0),
      m_secondaryStartDirection(0, 0, 1), m_automapRoomPieces(false),
      m_flag1A1(false), m_npcIconsDirty(false), m_iLevelDepth(depth),
      m_dungeonDepth(depth), m_sceneManager(scene),
      m_nonLightStaticGeometry(NULL), m_nonLightStaticGeometry2(NULL),
      m_nonLightStaticGeometry3(NULL), m_lightStaticGeometry(NULL),
      m_pLevelTemplateData(NULL), m_automap(NULL), m_formations(5),
      m_pGameClient(client), m_levelSeed(seed), m_updatedCharacterCount(0),
      m_flag258(false), m_auxiliaryLayouts(10), m_updateRange(40.0f), m_sDungeonName(dungeon),
      m_timerStatics(NULL), m_pendingCharacterUpdateRemovals(10)
{
    std::memset(m_LevelData58, 0, 4);
    std::memset(m_LevelData218, 0, 8);
    m_timer.reset();
    m_resourceManager->m_pLevel = this;
    m_pCharacters = new TLinkedList<CCharacter*>();
    m_items = new TLinkedList<CItem*>();
    m_activeCharacters = new TLinkedList<CCharacter*>();
    m_activeItems = new TLinkedList<CItem*>();
    m_pendingItems = new TLinkedList<CItem*>();
    m_pendingCharacters = new TLinkedList<CCharacter*>();
    m_characterUpdateListeners = new TLinkedList<iLevelUpdatedCharacter*>();
}

#include "Skill.h"
CCharacter* CLevel::findCharacterWithinView(const Ogre::Matrix4& transform,
    EAlignment alignment, float radius, float angle, float distance,
    bool nearest, CCharacter* ignored, CSkill* skill)
{
    if (skill && !skill->getMasterOwnerCharacter()) skill = NULL;
    Ogre::Matrix4 inverse = transform.inverse();
    bool targetsDead = skill && skill->m_targetsDead;
    CCharacter* found = NULL;
    float bestDistance = 9999.0f;
    for (TLinkedListNode<CCharacter*>* node = m_activeCharacters->m_pHead;
         node; node = node->m_pNext)
    {
        bool valid = true;
        if (skill) {
            Ogre::Vector3 position = skill->getMasterOwnerCharacter()->getPosition(true);
            valid = skill->getTargetIsValid(node->m_Data, skill->getMasterOwnerCharacter(), &position, false);
        }
        CCharacter* character = node->m_Data;
        if (!(character->alive() || (targetsDead && !character->alive()))) continue;
        if (!character->getEnabled() || !character->m_bVisible || character == ignored ||
            !character->m_bInActiveRange || !character->m_damageShapeEnabled) continue;
        if ((alignment == static_cast<EAlignment>(6) || alignment == static_cast<EAlignment>(1)) &&
            character->alignment() != static_cast<EAlignment>(1)) continue;
        if ((alignment == static_cast<EAlignment>(5) || alignment == static_cast<EAlignment>(2)) &&
            character->alignment() != static_cast<EAlignment>(2)) continue;
        if (!targetsDead && (character->isPetNearDeath() || !character->alive() ||
            character->m_eAIState == static_cast<EAIState>(42) ||
            character->m_eAIState == static_cast<EAIState>(41))) continue;
        if (character->ISA(static_cast<UNITTYPES::EUNITTYPES>(167)) &&
            character->hasUnitTheme(L"MIMICIDLE")) valid = false;
        if (!valid) continue;
        Ogre::Vector3 local = inverse * character->getPosition(true);
        local.y = 0.0f;
        float length = local.length();
        if (!(length <= radius)) {
            float direction = ::fabsf(::atan2f(local.x, local.z) * (180.0f / 3.14159f));
            if (!(direction <= angle) && !(angle > 0.0f && length < 2.0f && direction < 30.0f))
                continue;
            if (!(length <= distance)) continue;
        }
        Ogre::Vector3 from(transform[0][3], transform[1][3], transform[2][3]);
        Ogre::Vector3 to = character->getPosition(true);
        to.y += 5.0f; from.y += 5.0f;
        if (!sightUnobstructed(from, to, false)) continue;
        if (!nearest) return character;
        if (length < bestDistance) { bestDistance = length; found = character; }
    }
    return found;
}

#include "GameUI.h"
#include "Layout.h"
#include "Particle.h"
#include "MasterResourceManager.h"
#include "Settings.h"
#include <OgreCamera.h>
void CLevel::updateVisibleParticles(Ogre::Camera* camera, const Ogre::Vector3& position, bool force)
{
    if (!m_auxiliaryLayouts.size()) return;
    CGameUI* ui = m_pGameClient->m_pGameUI;
    if (!ui) return;
    static Ogre::Vector3 mLastPos(-9999.0f, -9999.0f, -999.0f);
    if (m_pGameClient->m_pPlayer) {
        if (!force && (position - mLastPos).length() < 0.25f) return;
        mLastPos = position;
    }
    Ogre::Matrix3 rotation;
    camera->getOrientation().ToRotationMatrix(rotation);
    Ogre::Matrix4 view = Ogre::Matrix4::IDENTITY;
    view = rotation;
    view.setTrans(camera->getPosition());
    view = view.inverse();
    Ogre::Matrix4 projection = camera->getProjectionMatrix() * view;
    Ogre::Vector3 up = camera->getOrientation().yAxis();
    float width = ui->getWindowWidth();
    ui->getWindowHeight();
    float aspect = ui->getAspectRatio();
    float farDepth = CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_NETBOOK_MODE) == 1 ? 45.0f : 90.0f;
    for (unsigned int i = 0; i < m_auxiliaryLayouts.size(); ++i) {
        if (m_auxiliaryLayouts[i]->m_pParticle &&
            (m_auxiliaryLayouts[i]->m_pParticle->m_bUnknown127 || !m_auxiliaryLayouts[i]->getEnabled()))
            continue;
        Ogre::Vector3 particlePosition = m_auxiliaryLayouts[i]->getPosition(true);
        Ogre::Vector3 screen = ui->getScreenPosition(&particlePosition, &up, projection);
        Ogre::Vector3 relative = m_auxiliaryLayouts[i]->getPosition(true) - position;
        relative.y = 0.0f;
        float distance = relative.length();
        if (!(screen.x >= -0.5f * width && screen.x <= 1.5f * width && screen.z >= 0.0f && screen.z <= farDepth) &&
            !(15.0f * aspect > distance) && !force) {
            if (m_auxiliaryLayouts[i]->m_bVisible) m_auxiliaryLayouts[i]->setVisible(false);
        } else if (!m_auxiliaryLayouts[i]->m_bVisible) {
            m_auxiliaryLayouts[i]->setVisible(true);
            if (force && m_auxiliaryLayouts[i]->m_pParticle)
                m_auxiliaryLayouts[i]->m_pParticle->forceParticleUpdate(1.0f);
        }
    }
}

#include "Light.h"
#include "RoomPiece.h"
#include "GameUI.h"
#include "Console.h"
#include "StringUtilities.h"
void CLevel::clearOutRoomPieces()
{
    int rooms = 0, lights = 0;
    for (unsigned int i = 0; i < m_RoomScenes.size(); ++i) {
        CEditorScene* scene = m_RoomScenes[i];
        TArrayList<CEditorBaseObject*> objects(5000);
        scene->GetObjectsCreatedByADescriptor(L"Room Piece", &objects);
        for (unsigned int j = 0; j < objects.size(); ++j) {
            CRoomPiece* piece = dynamic_cast<CRoomPiece*>(objects[j]);
            if (piece && !piece->getRoomPieceIsAnimated() && piece->m_bIsBakeable) {
                piece->getSceneOwner()->DeleteObjectInScene(piece);
                ++rooms;
            }
        }
        objects.clear();
        scene->GetObjectsCreatedByADescriptor(L"Light", &objects);
        for (unsigned int j = 0; j < objects.size(); ++j) {
            CLight* light = dynamic_cast<CLight*>(objects[j]);
            if (light) {
                light->getSceneOwner()->DeleteObjectInScene(light);
                ++lights;
            }
        }
    }
    m_pGameClient->m_pGameUI->m_console->addTextNoHistory(L"RoomPieces Deleted :" + STRINGS::GetValueAsWString(rooms));
    m_pGameClient->m_pGameUI->m_console->addTextNoHistory(L"Lights Deleted :" + STRINGS::GetValueAsWString(lights));
}

#include "Quadtree.h"
#include "MissilePreloader.h"

void CLevel::sortForCollisionByPoints(const Ogre::Vector3& start, const Ogre::Vector3& end, float radius)
{
    Ogre::Vector3 minimum = start;
    Ogre::Vector3 maximum = start;
    MATH::expandBounds(minimum, maximum, end);
    minimum.x -= radius;
    minimum.y -= radius;
    minimum.z -= radius;
    maximum.x += radius;
    maximum.y += radius;
    maximum.z += radius;
    m_collisionIndices.resize(0);
    if (m_collisionTree->m_root)
        m_collisionTree->m_root->sort(minimum, maximum, true, m_collisionIndices);
}

void CLevel::sortForCollision(const Ogre::Vector3& minimum, const Ogre::Vector3& maximum)
{
    m_collisionIndices.resize(0);
    if (m_collisionTree->m_root)
        m_collisionTree->m_root->sort(minimum, maximum, true, m_collisionIndices);
}

bool CLevel::rayCollision(const Ogre::Vector3& start, const Ogre::Vector3& end,
                         Ogre::Vector3& hit, Ogre::Vector3& normal,
                         unsigned int& material, Ogre::Vector3& faceNormal, bool staticOnly)
{
    if (!m_collisionList) return false;
    float distance = 99999.0f;
    Ogre::Vector3 minimum = start;
    Ogre::Vector3 maximum = start;
    MATH::expandBounds(minimum, maximum, end);
    Ogre::Vector3 localHit;
    Ogre::Vector3 localNormal;
    float objectDistance = 99999.0f;
    if (!staticOnly && objectRayCollision(start, end, localHit, localNormal, material, NULL, true))
    {
        objectDistance = (localHit - start).length();
        distance = objectDistance;
        hit = localHit;
        normal = localNormal;
        faceNormal = Ogre::Vector3(1.0f, 1.0f, 1.0f);
    }
    std::vector<unsigned int> faces;
    faces.reserve(500);
    if (m_collisionTree->m_root)
        m_collisionTree->m_root->sort(minimum, maximum, true, faces);
    m_collisionList->rayCollision(faces, start, end, minimum, maximum, localHit,
                                 localNormal, material, faceNormal, distance);
    if (distance != 99999.0f)
    {
        if (distance < objectDistance)
        {
            hit = localHit;
            normal = localNormal;
        }
        return true;
    }
    return false;
}

bool CLevel::sphereCollision(const Ogre::Vector3& start, const Ogre::Vector3& end,
                            float radius, Ogre::Vector3& position, Ogre::Vector3& hit,
                            Ogre::Vector3& normal, unsigned int& material,
                            Ogre::Vector3& faceNormal)
{
    if (!m_collisionList) return false;
    float distance = 99999.0f;
    Ogre::Vector3 minimum = start;
    Ogre::Vector3 maximum = start;
    MATH::expandBounds(minimum, maximum, end);
    minimum.x -= radius;
    minimum.y -= radius;
    minimum.z -= radius;
    maximum.x += radius;
    maximum.y += radius;
    maximum.z += radius;
    std::vector<unsigned int> faces;
    faces.reserve(500);
    if (m_collisionTree->m_root)
        m_collisionTree->m_root->sort(minimum, maximum, true, faces);
    m_collisionList->sphereCollision(faces, start, end, minimum, maximum, radius,
                                    position, hit, normal, material, faceNormal, distance);
    return distance != 99999.0f;
}

void CLevel::update(Ogre::Camera* camera, const Ogre::Vector3& position,
                    float elapsed, float scale, CPlayer*)
{
    static float UpdateTimer = 100.0f;
    if (elapsed == 0.0f) return;
    if (m_npcIconsDirty && m_automap)
    {
        updateNPCIcons();
        m_npcIconsDirty = false;
    }
    float adjusted = elapsed * scale;
    UpdateTimer += adjusted;
    if (UpdateTimer > 1.0f)
    {
        updateNearUnitList(position);
        UpdateTimer = 0.0f;
    }
    m_resourceManager->getMissilePreloader()->updateMissiles(adjusted);
    updateCharacters(camera, position, elapsed, scale);
    updateItems(camera, position, adjusted);
    updateLevelUpdateObjects(camera, position, adjusted);
    if (m_automap) m_automap->update(position, elapsed);
}

#include <algorithm>
#include <cmath>

namespace {
void levelProjectedBounds(const Ogre::Matrix4& transform,
                          const Ogre::Vector3& minimum, const Ogre::Vector3& maximum,
                          Ogre::Vector3& projectedMinimum, Ogre::Vector3& projectedMaximum)
{
    projectedMinimum = projectedMaximum = transform * minimum;
    for (unsigned int i = 1; i < 8; ++i)
    {
        Ogre::Vector3 corner(i & 1 ? maximum.x : minimum.x,
                             i & 2 ? maximum.y : minimum.y,
                             i & 4 ? maximum.z : minimum.z);
        MATH::expandBounds(projectedMinimum, projectedMaximum, transform * corner);
    }
}
bool levelScreenCenter(const Ogre::Vector3& point)
{
    return point.x > -1.1f && point.x <= 1.1f && point.y >= -1.1f && point.y <= 1.1f;
}
bool levelItemOnscreen(const Ogre::Matrix4& transform, const Ogre::Vector3& position)
{
    Ogre::Vector3 projected = transform * position;
    projected /= projected.z;
    return projected.x > -1.0f && projected.x <= 1.0f &&
           projected.y >= -1.0f && projected.y <= 1.0f && projected.z >= 0.0f;
}
}

CCharacter* CLevel::findCharacterAtScreenCoordinates(const Ogre::Matrix4& view,
                            const Ogre::Matrix4& projection, float x, float y, CCharacter* exclude)
{
    Ogre::Matrix4 transform = projection * view;
    CCharacter* follower = exclude && !exclude->m_Followers.empty() ? exclude->m_Followers[0] : NULL;
    CCharacter* result = NULL;
    float closest = 99999.0f;
    for (TLinkedListNode<CCharacter*>* node = m_activeCharacters->m_pHead; node; node = node->m_pNext)
    {
        CCharacter* actor = node->m_Data;
        if (!actor->alive() || actor->m_pMaster == exclude || !actor->m_bInActiveRange ||
            (follower && actor->m_pMaster == follower) || actor == exclude ||
            !actor->m_damageShapeEnabled || !actor->getEnabled())
            continue;
        Ogre::Vector3 position(actor->m_lastWorldPosition[0], actor->m_lastWorldPosition[1], actor->m_lastWorldPosition[2]);
        if (!levelScreenCenter(transform * position)) continue;
        Ogre::Vector3 minimum = actor->getLocalMinBounds();
        Ogre::Vector3 maximum;
        maximum.y = actor->getLocalMaxBounds().y * 0.9f;
        float extentX = minimum.x * 0.7f;
        float extentZ = minimum.z * 0.7f;
        minimum.x = std::min(extentX, -0.55f);
        minimum.z = std::min(extentZ, -0.55f);
        maximum.x = std::max(extentX, 0.55f);
        maximum.z = std::max(extentZ, 0.55f);
        Ogre::Vector3 projectedMinimum, projectedMaximum;
        levelProjectedBounds(transform, minimum + position, maximum + position,
                             projectedMinimum, projectedMaximum);
        if (!(projectedMaximum.z > 0.0f)) continue;
        float distance = ::fabsf(projectedMinimum.z);
        if (actor->alignment() == static_cast<EAlignment>(0)) distance += 800.0f;
        if (actor->alignment() == static_cast<EAlignment>(1)) distance += 1200.0f;
        if (closest > distance && x >= projectedMinimum.x && y >= projectedMinimum.y &&
            x <= projectedMaximum.x && y <= projectedMaximum.y)
        {
            result = actor;
            closest = distance;
        }
    }
    return result;
}

CItem* CLevel::findItemAtScreenCoordinates(const Ogre::Matrix4& view,
                           const Ogre::Matrix4& projection, float x, float y)
{
    Ogre::Matrix4 transform = projection * view;
    CItem* result = NULL;
    float closest = 99999.0f;
    for (TLinkedListNode<CItem*>* node = m_pendingItems->m_pHead; node; node = node->m_pNext)
    {
        CItem* item = node->m_Data;
        if (!item->m_bItemFlag1F0 || item->m_bNonSelectable || !item->m_bInActiveRange)
            continue;
        if (!levelScreenCenter(transform * item->getPosition(true))) continue;
        Ogre::Vector3 minimum = item->getLocalMinBounds();
        Ogre::Vector3 maximum = item->getLocalMaxBounds();
        minimum.x *= 0.7f; minimum.y *= 0.9f; minimum.z *= 0.7f;
        maximum.x *= 0.7f; maximum.y *= 0.9f; maximum.z *= 0.7f;
        minimum += item->getPosition(true);
        maximum += item->getPosition(true);
        Ogre::Vector3 projectedMinimum, projectedMaximum;
        levelProjectedBounds(transform, minimum, maximum, projectedMinimum, projectedMaximum);
        if (!(projectedMaximum.z > 0.0f)) continue;
        float distance = ::fabsf(projectedMinimum.z);
        if (closest > distance && x >= projectedMinimum.x && y >= projectedMinimum.y &&
            x <= projectedMaximum.x && y <= projectedMaximum.y)
        {
            result = item;
            closest = distance;
        }
    }
    return result;
}

void CLevel::findItemsOnscreen(Ogre::Camera* camera)
{
    if (!m_pendingItems) return;
    while (m_pendingItems->m_pHead)
    {
        TLinkedListNode<CItem*>* node = m_pendingItems->m_pHead;
        m_pendingItems->m_pHead = node->m_pNext;
        node->m_pPrevious = node->m_pNext = NULL;
        delete node;
    }
    Ogre::Matrix3 rotation;
    camera->getOrientation().ToRotationMatrix(rotation);
    Ogre::Matrix4 view = Ogre::Matrix4::IDENTITY;
    view = rotation;
    view.setTrans(camera->getPosition());
    view = view.inverse();
    Ogre::Matrix4 transform = camera->getProjectionMatrix() * view;
    for (TLinkedListNode<CItem*>* node = m_activeItems->m_pHead; node; node = node->m_pNext)
    {
        CItem* item = node->m_Data;
        if ((item->ISA(static_cast<UNITTYPES::EUNITTYPES>(31)) || item->m_bItemFlag1F0) &&
            !item->m_bNonSelectable && item->m_bVisible && item->getEnabled() &&
            levelItemOnscreen(transform, item->getPosition(true)))
            {
            TLinkedListNode<CItem*>* added = new TLinkedListNode<CItem*>;
            added->m_Data = item;
            added->m_pNext = m_pendingItems->m_pHead;
            added->m_pPrevious = NULL;
            if (added->m_pNext) added->m_pNext->m_pPrevious = added;
            m_pendingItems->m_pHead = added;
        }
        else
            item->hideItemText();
    }
    if (!m_pendingCharacters) return;
    while (m_pendingCharacters->m_pHead)
    {
        TLinkedListNode<CCharacter*>* node = m_pendingCharacters->m_pHead;
        m_pendingCharacters->m_pHead = node->m_pNext;
        node->m_pPrevious = node->m_pNext = NULL;
        delete node;
    }
    for (TLinkedListNode<CCharacter*>* node = m_activeCharacters->m_pHead; node; node = node->m_pNext)
    {
        CCharacter* actor = node->m_Data;
        if (actor->alive() && actor->ISA(static_cast<UNITTYPES::EUNITTYPES>(167)) &&
            actor->hasUnitTheme(L"MIMICIDLE") && actor->m_bVisible && actor->getEnabled() &&
            levelItemOnscreen(transform, actor->getPosition(true)))
            {
            TLinkedListNode<CCharacter*>* added = new TLinkedListNode<CCharacter*>;
            added->m_Data = actor;
            added->m_pNext = m_pendingCharacters->m_pHead;
            added->m_pPrevious = NULL;
            if (added->m_pNext) added->m_pNext->m_pPrevious = added;
            m_pendingCharacters->m_pHead = added;
        }
        else
            actor->hideCharacterText();
    }
}

#include "CameraControl.h"
#include "RoomPiece.h"
#include <OgreTextureUnitState.h>
void CLevel::setProjectorPass(Ogre::Frustum* shadow, Ogre::Frustum* projector,
                             CGenericModel* model, CGenericModel* other,
                             const std::string& shadowTexture, const std::string& projectorTexture)
{
    clearProjectorPass(model, other);
    Ogre::ColourValue ambient(1,1,1,1);
    CSettings* settings = CMasterResourceManager::getSingleton()->m_pSettings;
    if (settings->GetInt(KSETTINGS_OVERRIDE_LIGHTING) > 0 || !m_pLevelTemplateData) {
        ambient.b = static_cast<float>(settings->GetInt(KSETTINGS_MATERIAL_AMBIENT_LIGHT_BLUE)) / 255.0f;
        ambient.g = static_cast<float>(settings->GetInt(KSETTINGS_MATERIAL_AMBIENT_LIGHT_GREEN)) / 255.0f;
        ambient.r = static_cast<float>(settings->GetInt(KSETTINGS_MATERIAL_AMBIENT_LIGHT_RED)) / 255.0f;
    } else {
        ambient.r = m_pLevelTemplateData->m_materialAmbientColorR;
        ambient.g = m_pLevelTemplateData->m_materialAmbientColorG;
        ambient.b = m_pLevelTemplateData->m_materialAmbientColorB;
        ambient.a = m_pLevelTemplateData->m_materialAmbientColorA;
    }
    int lighting = settings->GetInt(KSETTINGS_LIGHTING_ENABLED);
    int rooms = static_cast<int>(m_RoomScenes.size());
    for (int i=0; i<rooms; ++i) {
        TArrayList<CEditorBaseObject*> pieces(10);
        m_RoomScenes[i]->GetObjectsCreatedByADescriptor(L"Room Piece", &pieces);
        for (unsigned int j=0; j<pieces.size(); ++j) {
            CRoomPiece* piece = dynamic_cast<CRoomPiece*>(pieces[j]);
            if (piece && piece->m_pGenericModel) piece->m_pGenericModel->setAmbient(ambient);
        }
    }
    if (other) {
        if (lighting == 1) other->setProjectorPass(m_pGameClient->m_cameraControl->m_pUnknown30,
            m_pGameClient->m_cameraControl->m_pUnknown28, m_pGameClient->m_projectorTexture,
            m_pGameClient->m_projectorFalloffTexture);
        other->setAmbient(ambient);
    }
    if (model && static_cast<int>(STRINGS::StringUpper(std::wstring(model->m_sModelPath)).find(L"LIGHT")) >= 0) {
        if (lighting == 1) model->setProjectorPass(m_pGameClient->m_cameraControl->m_pUnknown30,
            m_pGameClient->m_cameraControl->m_pUnknown28, m_pGameClient->m_projectorTexture,
            m_pGameClient->m_projectorFalloffTexture);
        model->setAmbient(ambient);
    }
    if (m_items) {
        for (TLinkedListNode<CItem*>* node=m_items->m_pHead; node; node=node->m_pNext) {
            if (!node->m_Data->m_bLevelLighting) continue;
            if (lighting == 1) static_cast<CGenericModel*>(node->m_Data->getUnitModel())->setProjectorPass(
                m_pGameClient->m_cameraControl->m_pUnknown30, m_pGameClient->m_cameraControl->m_pUnknown28,
                m_pGameClient->m_projectorTexture, m_pGameClient->m_projectorFalloffTexture);
            static_cast<CGenericModel*>(node->m_Data->getUnitModel())->setAmbient(ambient);
        }
    }
    if (lighting != 1) return;
    for (unsigned int i=0;i<static_cast<unsigned int>(m_renderableStates.size());++i) {
        CRenderableStates& state=m_renderableStates[i];
        state.material->setAmbient(ambient);
        state.material->setDiffuse(ambient);
        if (state.projectorTechnique!=-1 || !state.m_flag31) continue;
        Ogre::Pass* pass=state.material->getTechnique(0)->getPass(0);
        int index=state.projectorPass;
        bool shadows=state.m_flag30 && CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_SHADOWS_ENABLED);
        if (index+(shadows?2:1)<=pass->getNumTextureUnitStates()) continue;
        Ogre::TextureUnitState* first=NULL;
        Ogre::TextureUnitState* second=NULL;
        if (index>1) {
            if (shadows) pass->createTextureUnitState();
            Ogre::TextureUnitState* copy=pass->createTextureUnitState();
            *copy=*pass->getTextureUnitState(index-1);
            copy->setName("");
            if (shadows) {
                first=pass->getTextureUnitState(index-1);
                second=pass->getTextureUnitState(index);
                first->setBlank();
                second->setBlank();
            } else {
                second=pass->getTextureUnitState(index-1);
                second->setBlank();
            }
        } else {
            if (shadows) first=pass->createTextureUnitState(shadowTexture,0);
            second=pass->createTextureUnitState(projectorTexture,0);
        }
        if (shadows) {
            first->setProjectiveTexturing(true,shadow);
            first->setTextureAddressingMode(Ogre::TextureUnitState::TAM_CLAMP);
            first->setTextureFiltering(Ogre::FO_POINT,Ogre::FO_LINEAR,Ogre::FO_NONE);
            first->setColourOperationEx(Ogre::LBX_MODULATE_X2,Ogre::LBS_CURRENT,Ogre::LBS_TEXTURE,Ogre::ColourValue::White,Ogre::ColourValue::White,0.0f);
            if (index>1) first->setTextureName(shadowTexture,Ogre::TEX_TYPE_2D);
            first->setName("LIGHTPASS");
        }
        second->setProjectiveTexturing(true,projector);
        second->setTextureAddressingMode(Ogre::TextureUnitState::TAM_CLAMP);
        second->setTextureFiltering(Ogre::FO_POINT,Ogre::FO_LINEAR,Ogre::FO_NONE);
        second->setColourOperationEx(Ogre::LBX_MODULATE_X4,shadows?Ogre::LBS_CURRENT:Ogre::LBS_TEXTURE,shadows?Ogre::LBS_TEXTURE:Ogre::LBS_CURRENT,Ogre::ColourValue::White,Ogre::ColourValue::White,0.0f);
        if (index>1) second->setTextureName(projectorTexture,Ogre::TEX_TYPE_2D);
        second->setName("LIGHTPASS");
        if (shadows) state.projectorTechnique=state.projectorPass;
        if (m_resourceManager && m_resourceManager->getGameClient()) m_resourceManager->getGameClient()->m_pendingPassClear=true;
    }
}

#include "DataGroup.h"
#include "LinuxUtils.h"
#include <OgreUTFString.h>
void CLevel::saveRoomLayoutForQuickLoad(const std::wstring& filename)
{
    CDataGroup group(EMPTY_WSTRING, NULL, 20, 10, NULL);
    group.LoadFile(filename, NULL);
    if (group.GetDataGroupByName(L"OBJECTS", false))
    {
        std::wstring roomFilename = (Ogre::UTFString(filename) + Ogre::UTFString(".room")).asWStr();
        FILE* file;
        _wfopen_s(&file, roomFilename.c_str(), L"wb");
        parseDataGroupForRoomPiece(&group, file);
        fclose(file);
    }
}

#include "SpawnClass.h"
#include "RandomNames.h"
#include "PropertyNode.h"
#include "UtilitiesMath.h"
int CLevel::populateSectionOfLevel(const Ogre::Vector3& minimum, const Ogre::Vector3& maximum,
                                  const std::wstring& spawnName, bool champion, bool useNodes)
{
    CSpawnClass* spawn = m_resourceManager->getSpawnClassByName(spawnName);
    if (!spawn) return 0;
    TArrayList<CDataGroup*> groups(10);
    spawn->rollSpawnClass(groups, NULL, NULL, NULL, m_dungeonDepth, ~0u, 0, -1, 0, 0);
    int characters = 0;
    int items = 0;
    for (unsigned int i=0; i<groups.size(); ++i)
    {
        Ogre::Vector3 position(0,0,0);
        Ogre::Quaternion orientation(1,0,0,0);
        bool nodePosition = false;
        unsigned int attempts = 0;
        if (useNodes && m_propertyNodesF0.size())
        {
            for (; attempts<10; ++attempts)
            {
                unsigned int index = UTILITIES::randomIntegerBetweenVolatile(1, m_propertyNodesF0.size()) - 1;
                CPropertyNode* node = m_propertyNodesF0[index];
                if (node->m_iUnknown114) continue;
                position = node->getPosition(true);
                ++m_propertyNodesF0[index]->m_iUnknown114;
                orientation = m_propertyNodesF0[index]->getOrientationQuaternion();
                nodePosition = true;
                break;
            }
        }
        if (!nodePosition)
        {
            for (; attempts<50; ++attempts)
            {
                float z = UTILITIES::randomBetweenVolatile(minimum.z, maximum.z);
                float x = UTILITIES::randomBetweenVolatile(minimum.x, maximum.x);
                Ogre::Vector3 candidate(x, 27.5f, z);
                position = randomOpenPosition(candidate, 3.0f, true);
                if (position != candidate && !isInNoSpawnRegion(position, 1.0f)) break;
            }
            if (attempts == 50) continue;
        }
        CBaseUnit* unit = m_resourceManager->createUnit(groups[i], m_dungeonDepth, false, false);
        if (nodePosition) unit->setOrientation(orientation);
        else
        {
            Ogre::Vector3 direction(0,0,1);
            float angle = static_cast<float>(static_cast<double>(UTILITIES::randomBetweenVolatile(0,360)) * 0.01745329252);
            MATH::rotateY(&direction, angle);
            unit->setDirection(direction);
        }
        if (!unit) continue;
        CCharacter* actor = dynamic_cast<CCharacter*>(unit);
        if (actor)
        {
            if (champion) actor->makeChampion(CRandomNames::getSingleton()->generateName(true), m_dungeonDepth+1, L"CHAMPION");
            ++characters;
            addCharacter(actor, position, false);
            continue;
        }
        CItem* item = dynamic_cast<CItem*>(unit);
        if (!item) continue;
        if (item->m_bBlocksPath && item->m_bPathingFlag19C && item->ISA(static_cast<UNITTYPES::EUNITTYPES>(32)))
        {
            if (!passableBetween(position + Ogre::Vector3(-2,0,0), position + Ogre::Vector3(2,0,0), false) ||
                !passableBetween(position + Ogre::Vector3(0,0,-2), position + Ogre::Vector3(0,0,2), false) ||
                !passableBetween(position + Ogre::Vector3(2,0,-2), position + Ogre::Vector3(-2,0,2), false) ||
                !passableBetween(position + Ogre::Vector3(-2,0,-2), position + Ogre::Vector3(2,0,2), false))
            {
                delete item;
                continue;
            }
        }
        ++items;
        addItem(item, position, true);
    }
    return characters + items;
}

#include "Console.h"
#include "GameUI.h"
#include <cmath>
namespace {
bool levelPassabilityNeighbour(short** map, int width, int height, int x, int z)
{
    return x>=0 && z>=0 && x<width && z<height && map[x][z]<=0;
}
}
void CLevel::calculatePassability(const std::wstring& filename, const Ogre::Vector3& minimum,
                                const Ogre::Vector3& maximum)
{
    std::wstring name(filename);
    float originX = m_collisionList ? m_topLeftX : 0.0f;
    float originZ = m_collisionList ? m_topLeftY : 0.0f;
    int firstX = static_cast<int>(::floorf((m_collisionList ? minimum.x-originX : minimum.x)/0.4f))-1;
    int firstZ = static_cast<int>(::floorf((m_collisionList ? minimum.z-originZ : minimum.z)/0.4f))-1;
    int lastX = static_cast<int>(::ceilf((m_collisionList ? maximum.x-originX : maximum.x)/0.4f))+1;
    int lastZ = static_cast<int>(::ceilf((maximum.z-originZ)/0.4f))+1;
    int width = lastX-firstX;
    short* values = new short[width*(lastZ-firstZ)];
    int rayCasts = 0;
    if (m_collisionList)
    {
        for (int x=firstX; x<lastX; ++x)
            for (int z=firstZ; z<lastZ; ++z)
            {
                short& value = values[x-firstX + (z-firstZ)*width];
                if (x<0 || z<0 || x>=static_cast<int>(m_passWidth) || z>=static_cast<int>(m_passHeight))
                {
                    value=1;
                    continue;
                }
                short previous = m_mapPassability[x][z];
                value = previous==-1 ? 0 : previous;
                if (previous==-1 || previous==0)
                {
                    float cx = (static_cast<float>(x)*0.4f+0.2f)+originX;
                    float cz = (static_cast<float>(z)*0.4f+0.2f)+originZ;
                    sortForCollision(Ogre::Vector3(cx-0.2f-1.0f,-200,cz-0.2f-1.0f),
                                     Ogre::Vector3(cx+0.2f+1.0f,200,cz+0.2f+1.0f));
                    Ogre::Vector3 position, hit, normal, faceNormal;
                    unsigned int material;
                    ++rayCasts;
                    if (!preSortedSphereCollision(Ogre::Vector3(cx,200,cz), Ogre::Vector3(cx,-200,cz),
                                                   0.1f,position,hit,normal,material,faceNormal,true) ||
                        hit.y>80.0f || hit.y<-80.0f || material==100)
                        value=1;
                    else
                    {
                        Ogre::Vector3 center(hit.x,hit.y+1.5f,hit.z);
                        if ((preSortedRayCollision(center,center+Ogre::Vector3(0.3f,0,0),hit,normal,material,faceNormal,true) && material==100) ||
                            (preSortedRayCollision(center,center+Ogre::Vector3(-0.3f,0,0),hit,normal,material,faceNormal,true) && material==100) ||
                            (preSortedRayCollision(center,center+Ogre::Vector3(0,0,0.3f),hit,normal,material,faceNormal,true) && material==100) ||
                            (preSortedRayCollision(center,center+Ogre::Vector3(0,0,-0.3f),hit,normal,material,faceNormal,true) && material==100))
                            value=1;
                    }
                }
                m_mapPassability[x][z]=value;
                if (value==0) ++m_openCellCount;
            }
    }
    for (int x=firstX; x<lastX; ++x)
        for (int z=firstZ; z<lastZ; ++z)
        {
            int gridWidth=static_cast<int>(m_passWidth), gridHeight=static_cast<int>(m_passHeight);
            if (x<0 || z<0 || x>=gridWidth || z>=gridHeight || m_mapPassability[x][z]!=0) continue;
            if ((!levelPassabilityNeighbour(m_mapPassability,gridWidth,gridHeight,x-1,z) && !levelPassabilityNeighbour(m_mapPassability,gridWidth,gridHeight,x+1,z)) ||
                (!levelPassabilityNeighbour(m_mapPassability,gridWidth,gridHeight,x,z-1) && !levelPassabilityNeighbour(m_mapPassability,gridWidth,gridHeight,x,z+1)) ||
                (!levelPassabilityNeighbour(m_mapPassability,gridWidth,gridHeight,x-1,z-1) && !levelPassabilityNeighbour(m_mapPassability,gridWidth,gridHeight,x+1,z+1)) ||
                (!levelPassabilityNeighbour(m_mapPassability,gridWidth,gridHeight,x+1,z-1) && !levelPassabilityNeighbour(m_mapPassability,gridWidth,gridHeight,x-1,z+1)))
                m_mapPassability[x][z]=1;
        }
    delete[] values;
    m_pGameClient->m_pGameUI->m_console->addTextNoHistory(L"Level Pathnode Ray Casts :" + STRINGS::GetValueAsWString(rayCasts));
}

void CLevel::setAutomapVisible(bool visible)
{
    if (!m_automap) return;
    if (visible)
    {
        if (!m_automap->m_bVisible && gbWasVisible)
            m_automap->setVisible(true);
    }
    else
    {
        gbWasVisible = m_automap->m_bVisible;
        if (m_automap->m_bVisible)
            m_automap->setVisible(false);
    }
}


#include "FormationNode.h"
#include "Quadtree.h"
#include "TimerStatics.h"
#include "MissilePreloader.h"
#include "ParticlePreloader.h"
#include <OgreStaticGeometry.h>
namespace {
template<class T> void levelReleaseListNodes(TLinkedListNode<T>*& head)
{
    TLinkedListNode<T>* node=head;
    while (node)
    {
        TLinkedListNode<T>* next=node->m_pNext;
        node->m_pPrevious=NULL;
        node->m_pNext=NULL;
        delete node;
        node=next;
    }
    head=NULL;
}
template<class T> void levelDeleteListObjects(TLinkedListNode<T>* node)
{
    while (node)
    {
        T value=node->m_Data;
        node=node->m_pNext;
        if (value) delete value;
    }
}
}
CLevel::~CLevel()
{
    flushCharacterUpdateListeners();
    m_formations.deleteAll();
    if (m_timerStatics) { delete m_timerStatics; m_timerStatics=NULL; }
    if (m_automap) { delete m_automap; m_automap=NULL; }
    if (m_nonLightStaticGeometry) m_sceneManager->destroyStaticGeometry(m_nonLightStaticGeometry);
    if (m_nonLightStaticGeometry2) m_sceneManager->destroyStaticGeometry(m_nonLightStaticGeometry2);
    if (m_nonLightStaticGeometry3) m_sceneManager->destroyStaticGeometry(m_nonLightStaticGeometry3);
    if (m_lightStaticGeometry) m_sceneManager->destroyStaticGeometry(m_lightStaticGeometry);
    if (m_pLevelTemplateData && m_pLevelTemplateData->m_state761)
    {
        delete m_pLevelTemplateData;
        m_pLevelTemplateData=NULL;
    }
    if (m_collisionList) { delete m_collisionList; m_collisionList=NULL; }
    if (m_collisionTree) { delete m_collisionTree; m_collisionTree=NULL; }
    levelReleaseListNodes(m_pendingItems->m_pHead);
    delete m_pendingItems;
    m_pendingItems=NULL;
    levelReleaseListNodes(m_pendingCharacters->m_pHead);
    delete m_pendingCharacters;
    m_pendingCharacters=NULL;
    m_RoomScenes.deleteAll();
    m_updateObjects.clear();
    levelReleaseListNodes(m_characterUpdateListeners->m_pHead);
    delete m_characterUpdateListeners;
    m_characterUpdateListeners=NULL;
    levelDeleteListObjects(m_pCharacters->getHead());
    levelReleaseListNodes(m_pCharacters->m_pHead);
    delete m_pCharacters;
    m_pCharacters=NULL;
    levelReleaseListNodes(m_activeCharacters->m_pHead);
    delete m_activeCharacters;
    m_activeCharacters=NULL;
    levelDeleteListObjects(m_items->getHead());
    levelReleaseListNodes(m_items->m_pHead);
    delete m_items;
    m_items=NULL;
    levelReleaseListNodes(m_activeItems->m_pHead);
    delete m_activeItems;
    m_activeItems=NULL;
    m_resourceManager->getMissilePreloader()->clearCachedMissiles();
    m_auxiliaryLayouts.clear();
    CMasterResourceManager::getSingleton()->m_pParticlePreloader->unloadParticlesOnLevelUnload();
    for (unsigned int x=0; x<m_passWidth; ++x)
    {
        if (m_mapPassability[x]) delete[] m_mapPassability[x];
        if (m_objectPassability[x]) delete[] m_objectPassability[x];
    }
    if (m_mapPassability)
    {
        delete[] m_mapPassability;
        if (m_objectPassability) delete[] m_objectPassability;
    }
    for (std::map<long long,TArrayList<iUnitObserver*>*>::iterator it=m_unitObservers.begin(); it!=m_unitObservers.end(); ++it)
    {
        if (it->second) { delete it->second; it->second=NULL; }
    }
    m_unitObservers.clear();
}

#include "FormationNode.h"
#include "Utilities.h"
unsigned int CLevel::populateFormations(CRandomizer& regions, TArrayList<Ogre::AxisAlignedBox>& bounds)
{
    if (!m_pLevelTemplateData || m_pLevelTemplateData->m_selectedUnitSpawners[7].empty())
        return 0;
    CDataGroup data(EMPTY_WSTRING,NULL,20,10,NULL);
    data.LoadFile(m_pLevelTemplateData->m_selectedUnitSpawners[7],NULL);
    CRandomizer layouts(RANDOMIZER_NORMAL);
    TArrayList<std::wstring> names(10);
    for (unsigned int i=0; i<data.GetNumberOfDataGroups(); ++i)
    {
        std::wstring name=data.GetDataGroup(i)->GetDataValue(L"FILE",EMPTY_WSTRING);
        if (name.empty()) return 0;
        int weight=data.GetDataGroup(i)->GetDataValue(L"WEIGHT",1);
        layouts.addChoice(names.size(),weight>0?weight:1);
        names.add(name);
    }
    unsigned int count=m_pLevelTemplateData->getNumberOfUnitsToCreate(static_cast<ELEVELLAYOUT_CREATION>(7),m_openCellCount);
    for (unsigned int i=0; i<count; ++i)
    {
        Ogre::AxisAlignedBox box(bounds[regions.getRandom()]);
        const std::wstring& name=names[layouts.getRandom()];
        float z=UTILITIES::randomBetweenVolatile(box.getMinimum().z,box.getMaximum().z);
        float x=UTILITIES::randomBetweenVolatile(box.getMinimum().x,box.getMaximum().x);
        Ogre::Vector3 position(x,30.5f,z);
        for (unsigned int attempt=1; attempt!=51; ++attempt)
        {
            z=UTILITIES::randomBetweenVolatile(box.getMinimum().z,box.getMaximum().z);
            x=UTILITIES::randomBetweenVolatile(box.getMinimum().x,box.getMaximum().x);
            Ogre::Vector3 requested(x,30.5f,z);
            position=randomOpenPosition(requested,3.0f,true);
            if (position==requested || isInNoSpawnRegion(position,12.0f)) continue;
            unsigned int j=0;
            for (;j<m_formations.size();++j)
                if ((m_formations[j]->getPosition(false)-position).length()<20.0f) break;
            if (j!=m_formations.size()) continue;
            CFormationNode* node=new CFormationNode(m_resourceManager,NULL);
            node->setLayoutFile(name,m_resourceManager);
            node->setPosition(position);
            m_formations.add(node);
            break;
        }
    }
    return count;
}

#include "ParticleTechWrapper.h"
#include <ParticleUniverseTechnique.h>
void CLevel::findParticles()
{
    m_auxiliaryLayouts.clear();
    TArrayList<CEditorBaseObject*> layouts(1000);
    for (unsigned int i=0; i<m_RoomScenes.size(); ++i)
        m_RoomScenes[i]->GetObjectsCreatedByADescriptor(L"Layout Link Particle",&layouts);
    for (unsigned int i=0; i<layouts.size(); ++i)
    {
        CLayout* layout=static_cast<CLayout*>(layouts[i]);
        if (!layout->m_bStartOnLoad) continue;
        TArrayList<CEditorBaseObject*> particles(10);
        layout->GetObjectsCreatedByADescriptor(L"Particle",&particles);
        unsigned int j=0;
        for (;j<particles.size();++j)
        {
            CParticleTechWrapper* wrapper=dynamic_cast<CParticleTechWrapper*>(particles[j]);
            if (wrapper && wrapper->m_technique->mRunicFlag5b1) break;
        }
        if (j==particles.size()) m_auxiliaryLayouts.add(layout);
    }
}

#include "Quadtree.h"
#include "RandomGroup.h"
#include "CollisionModel.h"
#include "Console.h"
#include "GameUI.h"
#include <OgreMatrix3.h>
#include <OgreSceneNode.h>
#include <cmath>
void CLevel::bakeCollision(bool buildPassability)
{
    if (m_collisionList) { delete m_collisionList; m_collisionList=NULL; }
    if (m_collisionTree) { delete m_collisionTree; m_collisionTree=NULL; }
    m_collisionList=new CCollisionList;
    unsigned long collisionStart=m_timer.getMilliseconds();
    std::vector<Ogre::AxisAlignedBox> roomBounds;
    int pieceCount=0;
    int roomCount=static_cast<int>(m_RoomScenes.size());
    for (int i=0;i<roomCount;++i)
    {
        CEditorScene* scene=m_RoomScenes[i];
        std::vector<CRandomGroup*> hiddenGroups;
        TArrayList<CEditorBaseObject*> groups(5);
        scene->GetObjectsCreatedByADescriptor(L"Group",&groups);
        for (unsigned int j=0;j<groups.size();++j)
        {
            CRandomGroup* group=dynamic_cast<CRandomGroup*>(groups[j]);
            if (!group->m_bVisible)
            {
                hiddenGroups.push_back(group);
                group->setVisible(true);
            }
        }
        Ogre::AxisAlignedBox roomBox;
        roomBox.setInfinite();
        TArrayList<CEditorBaseObject*> objects(5000);
        scene->GetObjectsCreatedByADescriptor(L"Room Piece",&objects);
        for (unsigned int j=0;j<objects.size();++j)
        {
            CRoomPiece* piece=dynamic_cast<CRoomPiece*>(objects[j]);
            if (!piece || !piece->getCollisionMesh() || !piece->m_bCollisionEnabled) continue;
            bool visible=piece->m_bVisible;
            piece->setVisible(true);
            Ogre::Vector3 position=piece->getPosition(true);
            Ogre::Quaternion orientation=piece->m_pSceneNode->_getDerivedOrientation();
            Ogre::Matrix4 transform=Ogre::Matrix4::IDENTITY;
            Ogre::Matrix4 scale=Ogre::Matrix4::IDENTITY;
            scale.setScale(piece->getScale());
            transform=transform*scale;
            Ogre::Matrix3 rotation3;
            orientation.ToRotationMatrix(rotation3);
            Ogre::Matrix4 rotation=Ogre::Matrix4::IDENTITY;
            rotation=rotation3;
            transform=transform*rotation;
            transform.setTrans(position);
            m_collisionList->addCollisionList(piece->getCollisionMesh()->getCollisionList(),transform,-1);
            piece->setVisible(visible);
            if (buildPassability)
            {
                // The historical CollisionList field names have opposite min/max meanings.
                Ogre::Vector3 minimum=piece->getCollisionMesh()->getCollisionList()->m_vBoundsMax;
                Ogre::Vector3 maximum=piece->getCollisionMesh()->getCollisionList()->m_vBoundsMin;
                Ogre::AxisAlignedBox box(minimum,maximum);
                box.transform(transform);
                m_collisionBounds.push_back(box);
                if (roomBox.isInfinite()) roomBox=box;
                else roomBox.merge(box);
            }
        }
        pieceCount+=objects.size();
        roomBounds.push_back(roomBox);
        for (unsigned int j=0;j<hiddenGroups.size();++j) hiddenGroups[j]->setVisible(false);
    }
    m_pGameClient->m_pGameUI->m_console->addTextNoHistory(L"Collision Pieces :"+STRINGS::GetValueAsWString(pieceCount));
    m_collisionList->calculateFaceBounds();
    m_collisionList->calculateNormals();
    unsigned int smallest=1;
    float extent=(m_collisionList->m_vBoundsMax-m_collisionList->m_vBoundsMin).length()/1000.0f;
    if (extent>1.0f) smallest=static_cast<unsigned long>(extent);
    CQuadtree<unsigned int>* tree=new CQuadtree<unsigned int>;
    tree->m_minimumCellSize=static_cast<float>(smallest);
    tree->m_minimum=m_collisionList->m_vBoundsMin;
    tree->m_maximum=m_collisionList->m_vBoundsMax;
    tree->m_root=NULL;
    Ogre::Vector3 maximum=m_collisionList->m_vBoundsMin;
    Ogre::Vector3 minimum=m_collisionList->m_vBoundsMax;
    float width=::fabsf(maximum.x-minimum.x),height=::fabsf(maximum.z-minimum.z);
    if (height>width) { float d=(height-width)*0.5f;minimum.x-=d;maximum.x+=d; }
    else if (height<width) { float d=(width-height)*0.5f;minimum.z-=d;maximum.z+=d; }
    CQuadtreeNode<unsigned int>* root=new CQuadtreeNode<unsigned int>;
    root->m_maximum=maximum;
    root->m_minimum=minimum;
    root->m_subdivided=false;
    for (unsigned int i=0;i<4;++i) root->m_children[i]=NULL;
    tree->m_root=root;
    m_collisionTree=tree;
    m_pGameClient->m_pGameUI->m_console->addTextNoHistory(L"Smallest Face :"+STRINGS::GetValueAsWString(smallest));
    m_pGameClient->m_pGameUI->m_console->addTextNoHistory(L"Collision Bake Time: "+STRINGS::GetValueAsWString(static_cast<float>(m_timer.getMilliseconds()-collisionStart)/1000.0f));
    unsigned int faces=m_collisionList->getFaceCount();
    for (unsigned int i=0;i<faces;++i)
    {
        Ogre::Vector3& maximum=m_collisionList->getMaxFaceBounds(i);
        Ogre::Vector3& minimum=m_collisionList->getMinFaceBounds(i);
        m_collisionTree->m_root->addData(i,minimum,maximum,m_collisionTree->m_minimumCellSize);
    }
    m_pGameClient->m_pGameUI->m_console->addTextNoHistory(L"Collision Faces :"+STRINGS::GetValueAsWString(faces));
    unsigned long passabilityStart=m_timer.getMilliseconds();
    if (buildPassability && m_collisionList)
    {
        m_topLeftX=static_cast<int>(::floorf(m_collisionList->m_vBoundsMax.x/0.4f))*0.4f;
        m_topLeftY=static_cast<int>(::floorf(m_collisionList->m_vBoundsMax.z/0.4f))*0.4f;
        m_bottomRightX=static_cast<int>(::ceilf(m_collisionList->m_vBoundsMin.x/0.4f))*0.4f;
        m_bottomRightZ=static_cast<int>(::ceilf(m_collisionList->m_vBoundsMin.z/0.4f))*0.4f;
        m_passWidth=static_cast<unsigned long>((m_bottomRightX-m_topLeftX)/0.4f);
        m_passHeight=static_cast<unsigned long>((m_bottomRightZ-m_topLeftY)/0.4f);
        m_mapPassability=new short*[m_passWidth];
        m_objectPassability=new short*[m_passWidth];
        for (unsigned int i=0;i<m_passWidth;++i)
        {
            m_mapPassability[i]=new short[m_passHeight];
            m_objectPassability[i]=new short[m_passHeight];
        }
        clearPassabilityData();
        m_collisionBounds.clear();
        if (m_chunks.empty()) calculatePassability(EMPTY_WSTRING,m_collisionList->m_vBoundsMax,m_collisionList->m_vBoundsMin);
        else
            for (int i=0;i<roomCount;++i)
            {
                CChunkInstance* chunk=m_selectedLayout->m_chunkInstances[i];
                CChunkType* type=m_pLevelTemplateData->m_chunkTypes[chunk->m_chunkTypeIndex];
                float width=m_pLevelTemplateData->m_chunkWidthBasis*m_pLevelTemplateData->m_tileBasis;
                Ogre::AxisAlignedBox chunkBounds(
                    Ogre::Vector3(width*-0.5f+chunk->m_x,chunk->m_y-1000.0f,chunk->m_z+0.0f),
                    Ogre::Vector3(width*0.5f+(static_cast<float>(type->m_width)-1.0f)*width+chunk->m_x,
                                  chunk->m_y+1000.0f,
                                  m_pLevelTemplateData->m_chunkHeightBasis*static_cast<float>(type->m_width)*m_pLevelTemplateData->m_tileBasis+chunk->m_z));
                if (!roomBounds[i].isInfinite()) calculatePassability(m_chunks[i]->m_filename,roomBounds[i].getMinimum(),roomBounds[i].getMaximum());
            }
    }
    for (unsigned int x=0;x<m_passWidth;++x)
        for (unsigned int z=0;z<m_passHeight;++z)
            if (m_mapPassability[x][z]==-1) m_mapPassability[x][z]=1;
    m_pGameClient->m_pGameUI->m_console->addTextNoHistory(L"Passability Calculation Time: "+STRINGS::GetValueAsWString(static_cast<float>(m_timer.getMilliseconds()-passabilityStart)/1000.0f));
}

#include "MasterResourceManager.h"
#include "Settings.h"
#include "SettingsVariables.h"
#include "Light.h"
#include "RoomPiece.h"
#include "Console.h"
#include "GameUI.h"
#include <OgreStaticGeometry.h>
#include <OgreSceneManager.h>
void CLevel::bake(bool rebuildAutomap)
{
    if (rebuildAutomap)
    {
        delete m_automap;
        m_automap=new CAutomap(m_resourceManager,CMasterResourceManager::getSingleton()->m_automapScene);
        int setting=CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_AUTOMAP);
        if (setting==1) m_automap->setVisible(true);
        else if (setting==2) { m_automap->setVisible(true);m_automap->setFullscreen(true); }
        else if (setting==0) m_automap->setVisible(false);
    }
    m_renderableStates.clear();
    if (m_nonLightStaticGeometry) m_sceneManager->destroyStaticGeometry(m_nonLightStaticGeometry);
    if (m_nonLightStaticGeometry2) m_sceneManager->destroyStaticGeometry(m_nonLightStaticGeometry2);
    if (m_nonLightStaticGeometry3) m_sceneManager->destroyStaticGeometry(m_nonLightStaticGeometry3);
    if (m_lightStaticGeometry) m_sceneManager->destroyStaticGeometry(m_lightStaticGeometry);
    bool netbook=CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_NETBOOK_MODE)==1;
    float lightDistance=netbook?75.f:150.f;
    float distance=netbook?30.f:48.f;
    Ogre::Vector3 region(50,50,50);
    if (m_pLevelTemplateData) region=Ogre::Vector3(m_pLevelTemplateData->m_regionBoundsX,m_pLevelTemplateData->m_regionBoundsY,m_pLevelTemplateData->m_regionBoundsZ);
    m_nonLightStaticGeometry=m_sceneManager->createStaticGeometry(STRINGS::uniqueName("stgeompre_"));
    m_nonLightStaticGeometry->setRegionDimensions(region);
    m_nonLightStaticGeometry->setRenderingDistance(distance);
    m_nonLightStaticGeometry->setRenderQueueGroup(48);
    m_nonLightStaticGeometry2=m_sceneManager->createStaticGeometry(STRINGS::uniqueName("stgeom_"));
    m_nonLightStaticGeometry2->setRegionDimensions(region);
    m_nonLightStaticGeometry2->setRenderingDistance(distance);
    m_nonLightStaticGeometry2->setRenderQueueGroup(49);
    m_nonLightStaticGeometry3=m_sceneManager->createStaticGeometry(STRINGS::uniqueName("stgeompost_"));
    m_nonLightStaticGeometry3->setRegionDimensions(region);
    m_nonLightStaticGeometry3->setRenderingDistance(distance);
    m_nonLightStaticGeometry3->setRenderQueueGroup(89);
    m_lightStaticGeometry=m_sceneManager->createStaticGeometry(STRINGS::uniqueName("stgeomLight_"));
    m_lightStaticGeometry->setRegionDimensions(Ogre::Vector3(50,50,50));
    m_lightStaticGeometry->setRenderingDistance(lightDistance);
    m_lightStaticGeometry->setRenderQueueGroup(95);
    unsigned long start=m_timer.getMilliseconds();
    int rooms=static_cast<int>(m_RoomScenes.size());
    int genericCount=0,pieceCount=0,bakedPieces=0,lightCount=0,bakedLights=0;
    for (int i=0;i<rooms;++i)
    {
        CEditorScene* room=m_RoomScenes[i];
        room->setVisible(true);
        TArrayList<CEditorBaseObject*> objects(10);
        room->GetObjectsCreatedByADescriptor(L"Generic Model",&objects);
        int generics=objects.size();
        objects.clear();
        room->GetObjectsCreatedByADescriptor(L"Room Piece",&objects);
        if (objects.size())
        {
            pieceCount+=objects.size();
            for (unsigned int j=0;j<objects.size();++j)
            {
                CRoomPiece* piece=dynamic_cast<CRoomPiece*>(objects[j]);
                if (!piece || !piece->m_pGenericModel) continue;
                CGenericModel* model=piece->m_pGenericModel;
                for (unsigned int k=0;k<model->m_renderableStates.size();++k)
                {
                    CRenderableStates& state=model->m_renderableStates[k];
                    if (!state.m_flag31) continue;
                    bool found=false;
                    for (unsigned int n=0;n<m_renderableStates.size();++n)
                        if (m_renderableStates[n].material==state.material) { found=true;break; }
                    if (found) continue;
                    CRenderableStates initial=CRenderableStates();
                    initial.m_state0=1;initial.projectorTechnique=-1;initial.projectorPass=1;initial.m_flag31=true;initial.m_opacity=1;
                    m_renderableStates.resize(m_renderableStates.size()+1,initial);
                    CRenderableStates& added=m_renderableStates.back();
                    // The native aggregate assignment preserves the freshly initialized +0x2c word.
                    added.m_state0=state.m_state0;added.castsShadows=state.castsShadows;
                    added.highlighted=state.highlighted;added.renderBehind=state.renderBehind;
                    added.originalMaterial=state.originalMaterial;added.material=state.material;
                    added.material18=state.material18;added.material20=state.material20;
                    added.projectorTechnique=state.projectorTechnique;added.projectorPass=state.projectorPass;
                    added.m_gap2e=state.m_gap2e;added.spectral=state.spectral;added.m_flag30=state.m_flag30;
                    added.m_flag31=state.m_flag31;added.m_opacity=state.m_opacity;added.name=state.name;
                }
                Ogre::Vector3 position=piece->getPosition(true);
                Ogre::Quaternion orientation=piece->m_pSceneNode->_getDerivedOrientation();
                if (rebuildAutomap && piece->m_iUnknown158>0 && piece->m_bVisibleOnMap && piece->m_bVisible) addRoomPieceToAutomap(piece);
                if (!piece->getRoomPieceIsAnimated() && piece->m_bIsBakeable && piece->m_bVisible && piece->m_pGenericModel && piece->m_pGenericModel->m_pEntity)
                {
                    ++bakedPieces;
                    piece->setVisible(false);
                    Ogre::StaticGeometry* geometry=piece->m_bUnknown152?m_nonLightStaticGeometry:piece->m_bUnknown151?m_nonLightStaticGeometry3:m_nonLightStaticGeometry2;
                    geometry->addEntity(piece->m_pGenericModel->m_pEntity,position,orientation,piece->getScale());
                }
            }
            objects.clear();
            room->GetObjectsCreatedByADescriptor(L"Light",&objects);
            if (objects.size())
            {
                int count=objects.size();
                for (unsigned int j=0;j<objects.size();++j)
                {
                    CLight* light=dynamic_cast<CLight*>(objects[j]);
                    if (!light || !light->m_pGenericModel || !light->m_pGenericModel->m_pEntity || !light->m_bVisible) continue;
                    Ogre::Vector3 position=light->getPosition(true);
                    Ogre::Quaternion local=light->getOrientationQuaternion();
                    Ogre::Quaternion orientation=light->m_pParentSceneNode->_getDerivedOrientation()*local;
                    int density=light->m_iLightDensity;
                    for (int n=0;n<density;++n) m_lightStaticGeometry->addEntity(light->m_pGenericModel->m_pEntity,position,orientation,light->getScale());
                    ++bakedLights;
                }
                lightCount+=count;
            }
        }
        genericCount+=generics;
    }
    m_nonLightStaticGeometry->build();
    m_nonLightStaticGeometry2->build();
    m_nonLightStaticGeometry3->build();
    m_lightStaticGeometry->build();
    float seconds=static_cast<float>(m_timer.getMilliseconds()-start)/1000.f;
    CConsole* console=m_pGameClient->m_pGameUI->m_console;
    console->addTextNoHistory(L"------------------");
    console->addTextNoHistory(L"Bake Time: "+STRINGS::GetValueAsWString(seconds));
    console->addTextNoHistory(L"Layouts :"+STRINGS::GetValueAsWString(rooms));
    console->addTextNoHistory(L"Room Pieces :"+STRINGS::GetValueAsWString(pieceCount));
    console->addTextNoHistory(L"Batched Room Pieces :"+STRINGS::GetValueAsWString(bakedPieces));
    console->addTextNoHistory(L"Light Pieces :"+STRINGS::GetValueAsWString(lightCount));
    console->addTextNoHistory(L"Batched Light Pieces :"+STRINGS::GetValueAsWString(bakedLights));
    console->addTextNoHistory(L"Generic Models :"+STRINGS::GetValueAsWString(genericCount));
}
