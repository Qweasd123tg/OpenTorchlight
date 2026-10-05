#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "ParticleUniverseConstants.h"
#include "RunicCore.h"
#include "UnitTypes.h"
#include "TArrayList.h"

class CBaseUnit;
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
class CResourceManager : public CRunicCore
{
public:
    CMissilePreloader* getMissilePreloader();
    CParticle* createParticle(const wchar_t* name);
    CResourceManager(Ogre::SceneManager* sceneManager);
    virtual ~CResourceManager();

    CBaseUnit* createUnit(long long guid,int level,bool flag1,bool flag2);
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
