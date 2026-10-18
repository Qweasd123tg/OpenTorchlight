class CGameUI;
#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "ParticleUniverseConstants.h"
#include <map>
#include "RunicCore.h"
#include "UnitTypes.h"
#include "GameEnums.h"
#include "TArrayList.h"

class CGraph;
class CAffix;
class CMissile;
class CEquipment;
class CSpawnClass;
namespace Ogre { class TextureManager; }
class CBaseUnit;
class CCharacter;
class CMonster;
class CPlayer;
class CItem;
class CGameClient;
class CParticle;
class CGenericModel;
class CDataGroup;
class CHierarchy;
class CLevel;

namespace Ogre
{
    class SceneManager;
}

// Partial: members are declared as ResourceManager.cpp is recovered. The
// layout follows the constructor.
class CMissilePreloader;
class CDungeonManager;
class CDungeon;
class CUnitResourceList;
class CGameUI;
class CCameraControl;
class CResourceManager : public CRunicCore
{
public:
    CBaseUnit* createUnit(const wchar_t* category, const wchar_t* name, int level, bool flag);
    int ISA(const std::wstring& unit, const std::wstring& parent);

    TArrayList<CGameClient*>* getGameClients() { return &m_GameClients; }

    CGraph* getGraph(const std::wstring&);
    CGraph* getGraphDamage();
    unsigned int getCurrentLevelSeed();
    CAffix* getNewAffixByName(const std::wstring& name, unsigned int level);
    ERESOURCE_GROUPS getResourceGroupFromDataGroup(CDataGroup* data);
    CGameUI* getGameUI();
    void createUnitsBySpawnClass(CSpawnClass* spawn, TArrayList<CBaseUnit*>& units, unsigned int count, CCharacter* first, CCharacter* second, int level, int flags);
    CEquipment* createEquipment(const wchar_t*,bool,bool);
    CSpawnClass* getSpawnClassByName(const std::wstring&);
    void createUnitsBySpawnClassAtPositionInLevel(CSpawnClass* spawn, unsigned int count,
        const Ogre::Vector3& position, CLevel* level, CCharacter* owner, CCharacter* source, int unitLevel);
    CMissilePreloader* getMissilePreloader();
    CMissile* createMissile(const std::wstring& name);
    std::map<long long, CDataGroup*>* getGroupByName(const std::wstring& name);
    Ogre::TextureManager* getTextureManager();
    CDungeonManager* getDungeonManager();
    CDungeon* getDungeonByName(const std::wstring&);
    CUnitResourceList* getMasterResourceList();
    CCameraControl* getCameraControl();
    CParticle* createParticle(const wchar_t* name);
    CResourceManager(Ogre::SceneManager* sceneManager);
    virtual ~CResourceManager();

    CDataGroup* getUnitDataByGuid(long long);
    CMonster* createMonster(long long guid, int level, bool flag);
    CMonster* createMonster(const wchar_t* name, int level, bool flag);
    CPlayer* createPlayer(const wchar_t* name, bool flag);
    CItem* createNewItem(CDataGroup* data);
    CItem* createItem(long long guid, bool flag1, bool flag2, bool flag3);
    CItem* createItem(const wchar_t* name, bool flag1, bool flag2);
    void createUnitsBySpawnClass(const std::wstring& name, TArrayList<CBaseUnit*>& units,
        unsigned int count, CCharacter* first, CCharacter* second, int level, int flags);
    CBaseUnit* createUnit(long long guid,int level,bool flag1,bool flag2);
    CBaseUnit* createUnit(CDataGroup*,int,bool,bool);
    void createAffixesForUnit(CBaseUnit* unit,unsigned int level,unsigned int count);
    bool getEditorIsRunning();
    CGenericModel* createGenericModel(Ogre::SceneManager*,const wchar_t*,const wchar_t*,bool,bool,bool);
    long long getUnitGuidByDataGroup(CDataGroup* data,const std::wstring& name);
    UNITTYPES::EUNITTYPES getUnitTypeByName(const std::wstring& name);
    bool ISA(UNITTYPES::EUNITTYPES type, UNITTYPES::EUNITTYPES parent);
    Ogre::SceneManager* getSceneManager() { return m_pSceneManager; }
    CLevel* getLevel() { return m_pLevel; }
    // Read by CDescriptor::BroadcastEventFromObject (Descriptor.cpp).
    bool getLogicMessagesEnabled() { return m_bFlag1; }
    unsigned int getGameClientCount() { return m_GameClients.size(); }
    CGameClient* getGameClient(unsigned int index) { return m_GameClients[index]; }
    CGameClient* getGameClient() { return m_GameClients.size() != 0 ? m_GameClients[0] : NULL; }

private:
    friend class CRandomGroup;
    Ogre::SceneManager* m_pSceneManager;
    CLevel* m_pLevel;
    CHierarchy* m_pHierarchy;
    TArrayList<CGameClient*> m_GameClients;
    bool m_bFlag0;
    bool m_bFlag1;
    bool m_bFlag2;
    bool m_bFlag3;
};

#endif
