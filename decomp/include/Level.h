#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <map>
#include <vector>
#include <stdio.h>
#include <OgreTimer.h>
#include "GameEnums.h"
#include "RenderableStates.h"
class CAutomap;
class CPlayer;
namespace Ogre { class Billboard; class Camera; class Frustum; class SceneManager; class StaticGeometry; }
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

class iLevelUpdate;
class CItem;
class CGameClient;
class CCharacter;
class CBaseUnit;
class CDataGroup;
class CSkill;
class CEditorScene;
class CLevelTemplateData;
class CPropertyNode;
class CRoomPiece;
class iLevelUpdatedCharacter;

class CSettings;
class CResourceManager;
class CSoundManager;
class CGenericModel;
class CRandomizer;
class CLayout;
class CChunk;
class CLevelLayout;
class CFormationNode;
class CTimerStatics;
class CCollisionList;
template<class T> class CQuadtree;


// Partial: members used by recovered TUs; unnamed regions are padding until
// level.cpp is recovered. Size 0x2f0 follows CGameClient::loadMenuLevel allocation.
class CLevel : public CRunicCore
{
    friend class CTriggerUnit;
    friend class CSpawnClassData;
    friend class CConsole;
    friend class CGameClient;
public:
    void setNonLightStaticGeometryVisible(bool); // 0x935e60
    void setLightStaticGeometryVisible(bool); // 0x935ee0
    bool removeUpdateObject(iLevelUpdate*); // 0x9360e0
    float topLeftX(); // 0x9361e0
    float topLeftY(); // 0x936200
    CItem* getItemByGuid(long long, long long); // 0x9362b0
    void updateLevelUpdateObjects(Ogre::Camera*, Ogre::Vector3 const&, float); // 0x9363b0
    void makeQuestUnitsUncool(long long, bool); // 0x9365c0
    void populateNewMerchantsInventory(); // 0x936630
    std::wstring getLevelChampionSpawnClass(); // 0x9366f0
    std::wstring getLevelMonsterSpawnClass(); // 0x936740
    void flushCharacterUpdateListeners(); // 0x936a80
    void updateDroppingItems(float); // 0x936c80
    void reactToAreaDamage(CCharacter*, CCharacter*); // 0x936cf0
    void notifyOfDeletion(CCharacter*); // 0x936f20
    void decrementMapPassability(Ogre::Vector3 const&); // 0x937860
    void incrementMapPassability(Ogre::Vector3 const&); // 0x937950
    void incrementObjectPassability(Ogre::AxisAlignedBox const&, float); // 0x937a40
    void decrementObjectPassability(Ogre::Vector3 const&); // 0x9381b0
    void incrementObjectPassability(Ogre::Vector3 const&); // 0x9382a0
    bool mapPassable(Ogre::Vector3 const&); // 0x938390
    bool positionPassable(Ogre::Vector3 const&); // 0x938480
    CCharacter* getCharacterByOriginalGuid(long long, long long, int); // 0x944ed0
    CItem* getItemByOriginalGuid(long long, long long, int, long long); // 0x944fe0
    void updateNearUnitList(Ogre::Vector3 const&); // 0x9451d0
    void decrementObjectPassability(Ogre::AxisAlignedBox const&, float); // 0x945ff0
    bool objectRayCollision(Ogre::Vector3 const&, Ogre::Vector3 const&, Ogre::Vector3&, Ogre::Vector3&, unsigned int&, CBaseUnit**, bool); // 0x946300
    bool objectSphereCollision(Ogre::Vector3 const&, Ogre::Vector3 const&, float, Ogre::Vector3&, Ogre::Vector3&, Ogre::Vector3&, unsigned int&, CBaseUnit**, bool); // 0x9465b0
    void updateVisibleParticles(Ogre::Camera*, Ogre::Vector3 const&, bool); // 0x9474f0
    void getActiveUnitsAtPosition(Ogre::Vector3 const&, float, TArrayList<CCharacter*>&, TArrayList<CItem*>&); // 0x948430
    bool preSortedSphereCollision(Ogre::Vector3 const&, Ogre::Vector3 const&, float, Ogre::Vector3&, Ogre::Vector3&, Ogre::Vector3&, unsigned int&, Ogre::Vector3&, bool); // 0x948720
    bool preSortedSphereCollision(Ogre::Vector3 const&, Ogre::Vector3 const&, float, Ogre::Vector3&, Ogre::Vector3&, Ogre::Vector3&, unsigned int&, Ogre::Vector3&, CBaseUnit**, bool); // 0x948b40
    bool preSortedRayCollision(Ogre::Vector3 const&, Ogre::Vector3 const&, Ogre::Vector3&, Ogre::Vector3&, unsigned int&, Ogre::Vector3&, bool); // 0x948f60
    void deleteCharacter(CCharacter*); // 0x949a10
    void updateCharacters(Ogre::Camera*, Ogre::Vector3 const&, float, float); // 0x949c90
    void updateItems(Ogre::Camera*, Ogre::Vector3 const&, float); // 0x94a1a0
    void pushTime(); // 0x94a570
    CLevel(std::wstring, CSettings*, CGameClient*, CResourceManager*, Ogre::SceneManager*, CSoundManager*, int, int); // 0x94ab00
    CCharacter* findCharacterAtScreenCoordinates(Ogre::Matrix4 const&, Ogre::Matrix4 const&, float, float, CCharacter*); // 0x94b440
    CItem* findItemAtScreenCoordinates(Ogre::Matrix4 const&, Ogre::Matrix4 const&, float, float); // 0x94c730
    void sortForCollisionByPoints(Ogre::Vector3 const&, Ogre::Vector3 const&, float); // 0x94da90
    void sortForCollision(Ogre::Vector3 const&, Ogre::Vector3 const&); // 0x94dec0
    CItem* findItemWithinView(Ogre::Matrix4 const&, float, float); // 0x94ea30
    void findItemsOnscreen(Ogre::Camera*); // 0x94f730
    void findParticles(); // 0x950660
    void updateMaterialAmbient(); // 0x950a40
    void deleteTemporaryDungeonPortals(std::wstring); // 0x952af0
    int placePlayerAtWarpToDungeonFloor(std::wstring, int, bool, std::wstring); // 0x953000
    void calculatePassability(std::wstring const&, Ogre::Vector3 const&, Ogre::Vector3 const&); // 0x954580
    void bakeCollision(bool); // 0x955210
    void bake(bool); // 0x957f00
    void clearOutRoomPieces(); // 0x95a0f0
    void activate(); // 0x95a5d0
    std::wstring getName(); // 0x95a790
    Ogre::Vector3 findTemporaryDungeonPortal(std::wstring); // 0x95abb0
    void clearProjectorPass(CGenericModel*, CGenericModel*); // 0x95b100
    void setProjectorPass(Ogre::Frustum*, Ogre::Frustum*, CGenericModel*, CGenericModel*, std::string const&, std::string const&); // 0x95b420
    void update(Ogre::Camera*, Ogre::Vector3 const&, float, float, CPlayer*); // 0x95c7f0
    void rollMoney(CCharacter*, CCharacter*, Ogre::Vector3 const&, bool); // 0x95ce70
    void rollTreasure(CCharacter*, CCharacter*, Ogre::Vector3 const&); // 0x95d0b0
    int populateSectionOfLevel(Ogre::Vector3 const&, Ogre::Vector3 const&, std::wstring const&, bool, bool); // 0x95d220
    unsigned int populateFormations(CRandomizer&, TArrayList<Ogre::AxisAlignedBox>&); // 0x95dc40
    void setInited(bool); // 0x95e8b0
    void mergeLayoutsForRoomPiece(std::wstring const&, CLayout*); // 0x95e980
    void popTime(wchar_t const*); // 0x95ee30
    void loadRoomLayout(CLevelTemplateData*, bool, ELevelEntryType, std::vector<std::wstring>*, std::wstring); // 0x95f150
    void loadRoomLayout(std::wstring, bool, ELevelEntryType, std::vector<std::wstring>*, std::wstring); // 0x9622f0
    void populate(bool); // 0x962630
    void saveRoomLayoutForQuickLoad(std::wstring const&); // 0x965f00

    CBaseUnit* addUnit(CBaseUnit* unit, const Ogre::Vector3& position);
    CCharacter* addCharacter(CCharacter* character, const Ogre::Vector3& position, bool activate);
    void addUpdateObject(iLevelUpdate* object);
    void getBaseUnitsByDataGroup(CDataGroup* dataGroup, TArrayList<CBaseUnit*>& units);
    void addCharacterUpdateListener(iLevelUpdatedCharacter* listener);
    void removeCharacterUpdateListener(iLevelUpdatedCharacter* listener);
    void addRoomPieceToAutomap(CRoomPiece* roomPiece);
    CBaseUnit* getBaseUnitByDataGroup(CDataGroup* dataGroup);
    void getUnitsByUnitType(UNITTYPES::EUNITTYPES type, TArrayList<CBaseUnit*>& units);
    bool isInNoSpawnRegion(const Ogre::Vector3& position, float radius);
    void removeListenerFromUnit(long long guid, iUnitObserver* observer);
    void removeListenerFromUnit(CBaseUnit* unit, iUnitObserver* observer);
    long long addListenerToUnit(CBaseUnit* unit, iUnitObserver* observer);
    void removeListenerFromUnits(iUnitObserver* observer);
    bool getAutomapVisible();
    void setAutomapVisible(bool visible);
    void setNPCAutomapBillboardVisible(Ogre::Billboard* billboard, bool visible);
    void clearPassabilityData();
    unsigned int getCurrentLevelSeed();
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
    long long addListenerToUnit(long long,iUnitObserver*);
    Ogre::Vector3 randomOpenItemPositionRange(const Ogre::Vector3&,float,float,bool);
    Ogre::Vector3 randomOpenPositionRange(const Ogre::Vector3&,float,float,bool);
    bool sphereCollision(const Ogre::Vector3&,const Ogre::Vector3&,float,Ogre::Vector3&,Ogre::Vector3&,Ogre::Vector3&,unsigned int&,Ogre::Vector3&);
    void updateAutomapIcons();

    int getDungeonDepth() const { return m_dungeonDepth; }
    void notifyOfDeletion(CItem* item);
    CItem* addItem(CItem*,const Ogre::Vector3&,bool);
    void deleteItem(CItem*);
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
    void incrementMapPassability(const Ogre::AxisAlignedBox& bounds, float radius);
    void decrementMapPassability(const Ogre::AxisAlignedBox& bounds, float radius);
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
    bool passableBetween(Ogre::Vector3 start, const Ogre::Vector3& end, bool flag);
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
    friend class CQuestUnitData;
    friend class CCharacter;
    friend class CPlayer;
    friend class CWaypointActivator;
    friend class CMonster;
    friend class CDamageShape;
    friend class CResourceManager;
    friend class CUnitSpawnerDescriptor;
    friend class CRoomPiece;
    friend class CRandomGroup;
    friend class CPropertyNode;
    friend class CLayoutDescriptor;
    friend class CMonsterDescriptor;
    TArrayList<CEditorScene*> m_RoomScenes; // +0x10: native CLayout*, compatible first-base API retained
    TArrayList<Ogre::AxisAlignedBox> m_roomBounds;
    short** m_mapPassability;
    short** m_objectPassability;
    unsigned int m_passWidth;
    unsigned int m_passHeight;
    union {
        char m_LevelData58[0x60-0x58];
        struct { unsigned int m_openCellCount; unsigned char m_cellPadding5C[4]; };
    };
    CQuadtree<unsigned int>* m_collisionTree; // +0x60; class API deferred
    CCollisionList* m_collisionList; // +0x68
    std::vector<unsigned int> m_collisionIndices; // +0x70
    TLinkedList<CCharacter*>* m_activeCharacters;
    TLinkedList<CItem*>* m_activeItems;
    TLinkedList<CCharacter*>* m_pCharacters;
    TLinkedList<CItem*>* m_items;
    TArrayList<iLevelUpdate*> m_updateObjects; // +0xa8
    TLinkedList<CItem*>* m_pendingItems; // +0xc0
    TLinkedList<CCharacter*>* m_pendingCharacters; // +0xc8
    TLinkedList<iLevelUpdatedCharacter*>* m_characterUpdateListeners; // +0xd0
    std::vector<CPropertyNode*> m_noSpawnRegions; // +0xd8
    TArrayList<CPropertyNode*> m_propertyNodesF0; // +0xf0, createUnit mode 0
    TArrayList<CPropertyNode*> m_propertyNodes108; // +0x108, createUnit mode 1
    std::vector<Ogre::AxisAlignedBox> m_collisionBounds; // +0x120
    CResourceManager* m_resourceManager; // +0x138
    Ogre::Vector3 m_playerStart; // +0x140
    Ogre::Vector3 m_returnPortalPosition; // +0x14c
    Ogre::Vector3 m_waypointPosition; // +0x158
    Ogre::Vector3 m_startDirection; // +0x164
    Ogre::Vector3 m_secondaryStart; // +0x170
    Ogre::Vector3 m_secondaryStartDirection; // +0x17c
    Ogre::Vector3 m_auxiliaryPosition188; // +0x188
    Ogre::Vector3 m_auxiliaryPosition194; // +0x194
    bool m_automapRoomPieces;
    bool m_flag1A1;
    bool m_npcIconsDirty; // +0x1a2
    char m_LevelData1A3[1];
    int m_iLevelDepth;
    int m_dungeonDepth; // +0x1a8
    char m_LevelData1AC[4];
    Ogre::SceneManager* m_sceneManager; // +0x1b0
    Ogre::StaticGeometry* m_nonLightStaticGeometry; // +0x1b8
    Ogre::StaticGeometry* m_nonLightStaticGeometry2; // +0x1c0
    Ogre::StaticGeometry* m_nonLightStaticGeometry3; // +0x1c8
    Ogre::StaticGeometry* m_lightStaticGeometry; // +0x1d0
    CLevelTemplateData* m_pLevelTemplateData;
    CAutomap* m_automap;
    std::vector<CChunk*> m_chunks; // +0x1e8
    TArrayList<CFormationNode*> m_formations; // +0x200
    union { char m_LevelData218[8]; CLevelLayout* m_selectedLayout; }; // +0x218, borrowed
    CGameClient* m_pGameClient;
    unsigned int m_levelSeed; // +0x228
    union { char m_LevelData22C[4]; unsigned int m_updatedCharacterCount; };
    float m_topLeftX; // +0x230
    float m_topLeftY; // +0x234
    union { char m_LevelData238[8]; struct { float m_bottomRightX; float m_bottomRightZ; }; }; // +0x238/+0x23c
    Ogre::Timer m_timer; // +0x240, size 0x18 in pinned Linux SDK
    bool m_flag258;
    char m_LevelData259[7];
    TArrayList<CLayout*> m_auxiliaryLayouts; // +0x260
    float m_updateRange; // +0x278
    char m_LevelData27C[4];
    std::wstring m_sDungeonName;
    CTimerStatics* m_timerStatics; // +0x288
    std::vector<CRenderableStates> m_renderableStates; // +0x290, shared renderable-state type
    std::map<long long,TArrayList<iUnitObserver*>*> m_unitObservers;
    TArrayList<TLinkedListNode<iLevelUpdatedCharacter*>*> m_pendingCharacterUpdateRemovals; // +0x2d8
};

// Free functions in the original level.cpp TU.
void parseDataGroupForRoomPiece(CDataGroup*, FILE*);
const std::wstring& getStringFromDataGroup(CDataGroup*, std::wstring&, const std::wstring&);

#endif
