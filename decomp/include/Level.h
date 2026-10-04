#ifndef LEVEL_H
#define LEVEL_H

#include <OgreVector3.h>

#include "RunicCore.h"
#include "Constants.h"
#include "TArrayList.h"
#include "TLinkedList.h"
#include "UnitTypes.h"
#include "QuestDefines.h"
#include "iUnitObserver.h"

class CCharacter;
class CBaseUnit;
class CEditorScene;
class CLevelTemplateData;

// Partial: members used by recovered TUs; unnamed regions are padding until
// level.cpp is recovered. Size 0x2f0 follows CGameClient::loadMenuLevel allocation.
class CLevel : public CRunicCore
{
public:
    virtual ~CLevel();
    void unitBroadcastMessage(CBaseUnit* unit, EUNIT_STATES state);
    void questEventFire(EQUEST_EVENTS event, CCharacter* character, CBaseUnit* target);
    int getRoomIndexThatPositionIsIn(const Ogre::Vector3& position);
    Ogre::Vector3 randomOpenPosition(const Ogre::Vector3& position, float radius, bool flag);
    bool rayCollision(const Ogre::Vector3& start, const Ogre::Vector3& end, Ogre::Vector3& hit,
                      Ogre::Vector3& normal, unsigned int& type, Ogre::Vector3& extra, bool flag);
    CCharacter* getCharacterByGuid(long long guid);
    void getActiveCharactersAtPosition(const Ogre::Vector3& position, UNITTYPES::EUNITTYPES unitType,
                                       EAlignment alignment, float radius, bool includeLiving, bool includeDead,
                                       TArrayList<CCharacter*>& characters);

    CLevelTemplateData* getLevelTemplateData() { return m_pLevelTemplateData; }
    TArrayList<CEditorScene*>& getRoomScenes() { return m_RoomScenes; }
    TLinkedList<CCharacter*>* getCharacters() { return m_pCharacters; }

private:
    TArrayList<CEditorScene*> m_RoomScenes;
    char m_LevelData28[0x98 - 0x28];
    TLinkedList<CCharacter*>* m_pCharacters;
    char m_LevelDataA0[0x1d8 - 0xa0];
    CLevelTemplateData* m_pLevelTemplateData;
    char m_LevelData1E0[0x2f0 - 0x1e0];
};

#endif
