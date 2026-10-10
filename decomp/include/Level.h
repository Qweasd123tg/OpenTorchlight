#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <map>
class CAutomap;
class CPlayer;
namespace Ogre { class Billboard; }
#include <OgreVector3.h>
#include <OgreAxisAlignedBox.h>
#include <OgreMatrix4.h>
#include <string>

#include "RunicCore.h"
#include "Constants.h"
#include "TArrayList.h"
#include "TLinkedList.h"
#include "UnitTypes.h"
#include "QuestDefines.h"
#include "iUnitObserver.h"

class CItem;
class CGameClient;
class CCharacter;
class CBaseUnit;
class CSkill;
class CEditorScene;
class CLevelTemplateData;

// Partial: members used by recovered TUs; unnamed regions are padding until
// level.cpp is recovered. Size 0x2f0 follows CGameClient::loadMenuLevel allocation.
class CLevel : public CRunicCore
{
public:
    void removeListenerFromUnit(long long guid, iUnitObserver* observer);
    void removeListenerFromUnit(CBaseUnit* unit, iUnitObserver* observer);
    bool addListenerToUnit(CBaseUnit* unit, iUnitObserver* observer);
    void removeListenerFromUnits(iUnitObserver* observer);
    bool getAutomapVisible();
    void setNPCAutomapBillboardVisible(Ogre::Billboard* billboard, bool visible);
    void clearPassabilityData();
    bool mapPassable(int x, int y);
    bool positionPassable(int x, int y);
    void restartLevel();
    void updateLayouts(float elapsed);
    void updateCharacterAnimation(float elapsed, float scale, CPlayer* player);
    bool isDormant();
    CCharacter* getRandomMonster();
    void destroyIcons();
    void deleteOpenPortals();
    bool rayCollision(const Ogre::Vector3& start, const Ogre::Vector3& end, Ogre::Vector3& hit, Ogre::Vector3& normal, bool flag);
    bool sphereCollision(const Ogre::Vector3& start, const Ogre::Vector3& end, float radius, Ogre::Vector3& position, Ogre::Vector3& hit, Ogre::Vector3& normal);
    bool sightUnobstructed(const Ogre::Vector3& start, const Ogre::Vector3& end, bool flag);
    bool snapToValidGround(Ogre::Vector3& position, float height);
    void killAll();
    bool addListenerToUnit(long long,iUnitObserver*);
    Ogre::Vector3 randomOpenItemPositionRange(const Ogre::Vector3&,float,float,bool);
    Ogre::Vector3 randomOpenPositionRange(const Ogre::Vector3&,float,float,bool);
    bool sphereCollision(const Ogre::Vector3&,const Ogre::Vector3&,float,Ogre::Vector3&,Ogre::Vector3&,Ogre::Vector3&,unsigned int&,Ogre::Vector3&);
    void updateAutomapIcons();

    void addItem(CItem*,const Ogre::Vector3&,bool);
    // Original removal symbols; used by typed descriptor notifications.
    bool removeItem(CItem* item, bool deactivate);
    void removeCharacter(CCharacter* character, bool clearReferences);
    CCharacter* getPlayer();
    Ogre::Vector3 randomOpenItemPosition(const Ogre::Vector3&,float,bool);
    float floorHeight(Ogre::Vector3);
    void updateNPCIcons();
    virtual ~CLevel();
    void removeUnit(CBaseUnit* unit,bool flag);
    void incrementMapPassability(const Ogre::Vector3& minimum,const Ogre::Vector3& maximum,float radius);
    void decrementMapPassability(const Ogre::Vector3& minimum,const Ogre::Vector3& maximum,float radius);
    void incrementObjectPassability(const Ogre::Vector3& minimum,const Ogre::Vector3& maximum,float radius);
    void decrementObjectPassability(const Ogre::Vector3& minimum,const Ogre::Vector3& maximum,float radius);
    void incrementMapPassabilityCollision(const Ogre::AxisAlignedBox& bounds,CBaseUnit* unit);
    void decrementMapPassabilityCollision(const Ogre::AxisAlignedBox& bounds,CBaseUnit* unit);
    void unitBroadcastMessage(CBaseUnit* unit, EUNIT_STATES state);
    void questEventFire(EQUEST_EVENTS event, CCharacter* character, CBaseUnit* target);
    int getRoomIndexThatPositionIsIn(const Ogre::Vector3& position);
    CEditorScene* getRoomThatPositionIsIn(const Ogre::Vector3& position);
    void toggleAutomap();
    void zoomAutomap(float);
    Ogre::Vector3 randomOpenPosition(const Ogre::Vector3& position, float radius, bool flag);
    bool rayCollision(const Ogre::Vector3& start, const Ogre::Vector3& end, Ogre::Vector3& hit,
                      Ogre::Vector3& normal, unsigned int& type, Ogre::Vector3& extra, bool flag);
    CCharacter* getCharacterByGuid(long long guid);
    CCharacter* findCharacterWithinView(const Ogre::Matrix4& view, EAlignment alignment, float minimumAngle,
                                        float angle, float range, bool flag, CCharacter* exclude, CSkill* skill);
    void getActiveCharactersAtPosition(const Ogre::Vector3& position, UNITTYPES::EUNITTYPES unitType,
                                       EAlignment alignment, float radius, bool includeLiving, bool includeDead,
                                       TArrayList<CCharacter*>& characters);

    const std::wstring& getDungeonName() { return m_sDungeonName; }
    int getLevelDepth() { return m_iLevelDepth; }
    CLevelTemplateData* getLevelTemplateData() { return m_pLevelTemplateData; }
    TArrayList<CEditorScene*>& getRoomScenes() { return m_RoomScenes; }
    TLinkedList<CCharacter*>* getCharacters() { return m_pCharacters; }

private:
    friend struct SmallmatchPass7Probe;
    TArrayList<CEditorScene*> m_RoomScenes;
    TArrayList<Ogre::AxisAlignedBox> m_roomBounds;
    short** m_mapPassability;
    short** m_objectPassability;
    unsigned int m_passWidth;
    unsigned int m_passHeight;
    char m_LevelData58[0x88-0x58];
    TLinkedList<CCharacter*>* m_activeCharacters;
    TLinkedList<CItem*>* m_activeItems;
    TLinkedList<CCharacter*>* m_pCharacters;
    TLinkedList<CItem*>* m_items;
    char m_LevelDataA8[0x1a4-0xa8];
    int m_iLevelDepth;
    char m_LevelData1A8[0x1d8 - 0x1a8];
    CLevelTemplateData* m_pLevelTemplateData;
    CAutomap* m_automap;
    char m_LevelData1E8[0x220-0x1e8];
    CGameClient* m_pGameClient;
    char m_LevelData228[0x280 - 0x228];
    std::wstring m_sDungeonName;
    char m_LevelData288[0x2a8-0x288];
    std::map<long long,TArrayList<iUnitObserver*>*> m_unitObservers;
    char m_LevelData2D8[0x2f0-0x2d8];
};

#endif
