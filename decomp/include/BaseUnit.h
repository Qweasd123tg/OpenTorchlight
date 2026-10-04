#ifndef BASEUNIT_H
#define BASEUNIT_H

#include <string>

#include "PositionableObject.h"
#include "ResourceManager.h"
#include "QuestDefines.h"
#include "Constants.h"
#include "EffectDefines.h"
#include "TArrayList.h"
#include "UnitTypes.h"
#include "iUnitObserver.h"

class CCharacter;
class CCullingBounds;
class CDataGroup;
class CEffect;
class CLevel;
class CSkillManager;
class CUnitTheme;

namespace Ogre
{
    class Camera;
}

enum EBASEUNIT_TYPE
{
};

// Partial: members used by recovered TUs. The layout follows the constructor;
// unnamed regions are padding until BaseUnit.cpp is recovered. Return types of
// virtual methods that recovered code does not call are not verified yet.
class CBaseUnit : public CPositionableObject
{
public:
    CBaseUnit(CResourceManager* resourceManager, EBASEUNIT_TYPE type);
    virtual ~CBaseUnit();

    virtual void setActiveInLevel(bool active) = 0;
    virtual void unitThemeUpdated(CUnitTheme* theme, bool updated);
    virtual void* getUnitModel() = 0;
    virtual void* getUnitCollisionModel() = 0;
    virtual void unitInit(CDataGroup* dataGroup, bool initialize);
    virtual void levelResetting();
    virtual void update(Ogre::Camera* camera, const Ogre::Vector3& cameraPosition, float elapsed);
    virtual void setHighlighted(bool highlighted);
    virtual bool getHighlighted();
    virtual const Ogre::Vector3& getMinBounds();
    virtual const Ogre::Vector3& getMaxBounds();
    virtual const Ogre::Vector3& getLocalMinBounds();
    virtual const Ogre::Vector3& getLocalMaxBounds();
    virtual bool isEffectValidForUnit(CCharacter* source, CBaseUnit* target, CEffect* effect);
    virtual void applyEffectOnUnit(CCharacter* source, CBaseUnit* target, CEffect* effect);
    virtual float getEffectValue(EEFFECT_ACTIVATION activation, EEFFECT_TYPE type, float value, EDAMAGE_TYPES damageType);
    virtual float getEffectValue(EEFFECT_TYPE type, float value, EDAMAGE_TYPES damageType);
    virtual float getEffectValue(EEFFECT_TYPE type, float value, const std::wstring& name);
    virtual void deactivateEffect(CEffect* effect);
    virtual void removeFromAvoidanceMap(CLevel& level);
    virtual void addToAvoidanceMap(CLevel& level);
    virtual void setLevel(unsigned int level);

    bool ISA(UNITTYPES::EUNITTYPES type);
    void updateCullingBounds();
    bool getIsQuestUnit();
    bool getCastsShadows();
    void questEventFire(EQUEST_EVENTS event, CCharacter* character, CBaseUnit* target);
    void broadcastUnitState(EUNIT_STATES state);

    // Level the unit is in, through its resource manager.
    CLevel* getLevel()
    {
        return m_pResourceManager != NULL ? m_pResourceManager->getLevel() : NULL;
    }

    CDataGroup* getDataGroup() { return m_pDataGroup; }
    CSkillManager* getSkillManager() { return m_pSkillManager; }

protected:
    char m_BaseUnitData[0x170 - 0x100];
    long long m_iQuestGuid;
    int m_iQuestState;
    int m_iRoomIndex;
    long long m_iSpawnerGuid;
    char m_BaseUnitData188[0x18d - 0x188];
    bool m_bBlocksPath;
    char m_BaseUnitData18E[0x190 - 0x18e];
    bool m_bBaseUnitFlag190;
    bool m_bSaveFlag191;
    char m_BaseUnitData192[0x198 - 0x192];
    bool m_bRangeEnabled;
    bool m_bInActiveRange;
    bool m_bInFadeRange;
    bool m_bBaseUnitFlag19B;
    bool m_bPathingFlag19C;
    char m_BaseUnitData19D[0x1a0 - 0x19d];
    long long m_iUnitValue1A0;
    char m_BaseUnitData1A8[0x1ac - 0x1a8];
    UNITTYPES::EUNITTYPES m_eUnitType;
    CDataGroup* m_pDataGroup;
    char m_BaseUnitData2[0x8];
    CCullingBounds* m_pCullingBounds;
    CSkillManager* m_pSkillManager;
    bool m_bBaseUnitFlag0;
    bool m_bBaseUnitFlag1;
};

#endif
