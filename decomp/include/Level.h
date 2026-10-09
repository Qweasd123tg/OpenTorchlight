#ifndef LEVEL_H
#define LEVEL_H

#include <string>
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
    char m_LevelData28[0x98 - 0x28];
    TLinkedList<CCharacter*>* m_pCharacters;
    char m_LevelDataA0[0x1a4 - 0xa0];
    int m_iLevelDepth;
    char m_LevelData1A8[0x1d8 - 0x1a8];
    CLevelTemplateData* m_pLevelTemplateData;
    char m_LevelData1E0[0x220 - 0x1e0];
    CGameClient* m_pGameClient;
    char m_LevelData228[0x280 - 0x228];
    std::wstring m_sDungeonName;
    char m_LevelData288[0x2f0 - 0x288];
};

#endif
