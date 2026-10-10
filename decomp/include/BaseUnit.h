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
class CAffix;
class CSkill;
class CCullingBounds;
class CDataGroup;
class CEffect;
class CEffectManager;
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
    friend class CSkill;

    friend class CLevel;
    friend struct SmallmatchPass7Probe;
    friend class CEquipment;
    friend class CEnchantMenu;
    friend class CSkillProperty;
    friend struct SmallmatchLayoutProbe;
friend class CInventory;
public:
    long long getQuestGuid() const { return m_iQuestGuid; }
    long long getUnitGuid() const { return m_iUnitValue1A0; }

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
    virtual bool getHighlighted() { return m_bHighlighted; }
    virtual const Ogre::Vector3& getMinBounds();
    virtual const Ogre::Vector3& getMaxBounds();
    virtual const Ogre::Vector3& getLocalMinBounds();
    virtual const Ogre::Vector3& getLocalMaxBounds();
    virtual bool isEffectValidForUnit(CCharacter* source, CBaseUnit* target, CEffect* effect);
    virtual bool applyEffectOnUnit(CCharacter* source, CBaseUnit* target, CEffect* effect);
    virtual float getEffectValue(EEFFECT_ACTIVATION activation, EEFFECT_TYPE type, float value, EDAMAGE_TYPES damageType);
    virtual float getEffectValue(EEFFECT_TYPE type, float value, EDAMAGE_TYPES damageType);
    virtual float getEffectValue(EEFFECT_TYPE type, float value, const std::wstring& name);
    virtual void deactivateEffect(CEffect* effect);
    virtual void removeFromAvoidanceMap(CLevel& level);
    virtual void addToAvoidanceMap(CLevel& level);
    virtual void setLevel(unsigned int level);

    void addUnitTheme(CUnitTheme* theme);
    void addUnitTheme(const std::wstring& name);
    void removeUnitTheme(CUnitTheme* theme);
    void removeUnitTheme(const std::wstring& name);
    void removeUnitTheme(long long guid);
    void setEditorThemeID(unsigned int id);
    bool hasUnitTheme(CUnitTheme* theme);
    bool hasUnitTheme(long long guid);
    bool hasUnitTheme(const std::wstring& name);
    CAffix* addAffix(CAffix* affix,unsigned int level,CBaseUnit* source,float scale);
    CAffix* addAffix(const std::wstring& name,unsigned int level,CBaseUnit* source,float scale);
    CEffect* addNewEffect(CEffect* effect);
    CEffect* copyEffect(CBaseUnit* source,CEffect* effect);
    void copyEffects(CBaseUnit* source,const TArrayList<CEffect*>* effects);
    CSkill* addSkillByName(const std::wstring& name,bool flag);
    CSkill* cloneSkill(CSkill* skill);
    bool dontUseOnFull();
    void activateEffect(CEffect* effect);
    void reapplyEffects(bool flag);
    void reapplyAffixes(bool flag);
    void unitInitThemes();
    bool removeEffect(const std::wstring& name);
    bool removeAffix(const std::wstring& name);
    bool hasEffect(EEFFECT_TYPE type);
    bool hasEffect(EEFFECT_TYPE type, const std::wstring& name);
    bool hasEffect(const std::wstring& name);
    bool ISA(UNITTYPES::EUNITTYPES type);
    void updateCullingBounds();
    bool rayCollision(const Ogre::Vector3& start,const Ogre::Vector3& end,Ogre::Vector3& hit,Ogre::Vector3& normal,bool force);
    bool sphereCollision(const Ogre::Vector3& start,const Ogre::Vector3& end,float radius,Ogre::Vector3& position,Ogre::Vector3& hit,Ogre::Vector3& normal);
    bool getIsQuestUnit();
    bool getCastsShadows();
    void setCastsShadows(bool shadows);
    void setSpawnerGuid(long long guid);
    void activateUnitInLevel();
    void deactivateUnitInLevel();
    void broadcastAlerted();
    void broadcastKilled();
    void broadcastHPThreshholdEvents(float maximum,float current,float threshold,float change);
    std::wstring getUnitDataName();
    int selectRandomSkill();
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
    friend class CGameUI;
    friend class CCharacter;
    unsigned int m_iUnitLevel;
    TArrayList<CUnitTheme*> m_ThemesToAdd;
    TArrayList<CUnitTheme*> m_ThemesToRemove;
    TArrayList<CUnitTheme*> m_UnitThemes;
    TArrayList<CUnitTheme*> m_AffixThemes;
    unsigned int m_iEditorThemeID;
    unsigned char m_BaseUnitData16C[4];
    long long m_iQuestGuid;
    int m_iQuestState;
    int m_iRoomIndex;
    long long m_iSpawnerGuid;
    EBASEUNIT_TYPE m_eBaseUnitType;
    bool m_bBaseUnitFlag18C;
    bool m_bBlocksPath;
    bool m_bBaseUnitFlag18E;
    bool m_bBaseUnitFlag18F;
    bool m_bBaseUnitFlag190;
    bool m_bSaveFlag191;
    char m_BaseUnitData192[2];
    float m_fBaseUnitValue194;
    bool m_bRangeEnabled;
    bool m_bInActiveRange;
    bool m_bInFadeRange;
    bool m_bBaseUnitFlag19B;
    bool m_bPathingFlag19C;
    char m_BaseUnitData19D[0x1a0 - 0x19d];
    long long m_iUnitValue1A0;
    bool m_bHighlighted;
    bool m_bCastsShadows;
    char m_BaseUnitData1AA[2];
    UNITTYPES::EUNITTYPES m_eUnitType;
    CDataGroup* m_pDataGroup;
    CEffectManager* m_pEffectManager;
    CCullingBounds* m_pCullingBounds;
    CSkillManager* m_pSkillManager;
    bool m_bBaseUnitFlag0;
    bool m_bBaseUnitFlag1;
};

#endif
