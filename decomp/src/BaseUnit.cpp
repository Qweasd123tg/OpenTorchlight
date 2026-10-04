#include "EmptyStrings.h"
#include "BaseUnit.h"
#include "CullingBounds.h"
#include "GenericModel.h"
#include "Level.h"
#include "OutputEvents.h"
#include "EffectManager.h"
#include "UnitThemes.h"
#include "SkillManager.h"
#include "DataGroup.h"
#include "Randomizer.h"
#include "UtilitiesMath.h"
#include "Skill.h"

void CBaseUnit::setSpawnerGuid(long long guid)
{
    m_iSpawnerGuid = guid;
}

bool CBaseUnit::getCastsShadows()
{
    return m_bCastsShadows;
}

const Ogre::Vector3& CBaseUnit::getMinBounds()
{
    return m_pCullingBounds != NULL ? m_pCullingBounds->getWorldMinimum() : Ogre::Vector3::ZERO;
}

const Ogre::Vector3& CBaseUnit::getMaxBounds()
{
    return m_pCullingBounds != NULL ? m_pCullingBounds->getWorldMaximum() : Ogre::Vector3::ZERO;
}

const Ogre::Vector3& CBaseUnit::getLocalMinBounds()
{
    return m_pCullingBounds != NULL ? m_pCullingBounds->getLocalMinimum() : Ogre::Vector3::ZERO;
}

const Ogre::Vector3& CBaseUnit::getLocalMaxBounds()
{
    return m_pCullingBounds != NULL ? m_pCullingBounds->getLocalMaximum() : Ogre::Vector3::ZERO;
}

void CBaseUnit::deactivateUnitInLevel()
{
    m_bRangeEnabled = false;
    setActiveInLevel(false);
}

void CBaseUnit::setHighlighted(bool highlighted)
{
    m_bHighlighted = highlighted;
    if (getUnitModel() != NULL)
        static_cast<CGenericModel*>(getUnitModel())->setHighlighted(m_bHighlighted);
}

bool CBaseUnit::ISA(UNITTYPES::EUNITTYPES type)
{
    return m_pResourceManager != NULL ? m_pResourceManager->ISA(m_eUnitType, type) : false;
}

bool CBaseUnit::getIsQuestUnit()
{
    return ISA(UNITTYPES::QUESTITEM) || m_iQuestGuid != -1;
}

void CBaseUnit::broadcastAlerted()
{
    if (m_bBaseUnitFlag0 && !ISA(UNITTYPES::PLAYER))
        BroadcastEvent(OUTPUT_EVENT_MONSTER_ALERTED);
}

void CBaseUnit::broadcastKilled()
{
    if (!ISA(UNITTYPES::PLAYER))
        BroadcastEvent(OUTPUT_EVENT_MONSTER_KILLED);
}

void CBaseUnit::setCastsShadows(bool shadows)
{
    m_bCastsShadows = shadows;
    if (getUnitModel() != NULL)
        static_cast<CGenericModel*>(getUnitModel())->setCastsShadows(m_bCastsShadows);
}

void CBaseUnit::activateUnitInLevel()
{
    m_bInActiveRange = true;
    m_bInFadeRange = true;
    m_bRangeEnabled = true;
    setActiveInLevel(true);
    setCastsShadows(m_bCastsShadows);
}

void CBaseUnit::broadcastUnitState(EUNIT_STATES state)
{
    if (getLevel() != NULL)
        getLevel()->unitBroadcastMessage(this, state);
}

void CBaseUnit::questEventFire(EQUEST_EVENTS event, CCharacter* character, CBaseUnit* target)
{
    if (getLevel() != NULL)
        getLevel()->questEventFire(event, character, target);
}

bool CBaseUnit::hasUnitTheme(CUnitTheme* theme)
{
    return m_AffixThemes.find(theme) != -1 || m_UnitThemes.find(theme) != -1;
}

bool CBaseUnit::hasUnitTheme(long long guid)
{
    CUnitThemes* themes = CUnitThemes::getSingleton();
    return themes != NULL ? hasUnitTheme(themes->getTheme(guid)) : false;
}

bool CBaseUnit::hasUnitTheme(const std::wstring& name)
{
    CUnitThemes* themes = CUnitThemes::getSingleton();
    return themes != NULL ? hasUnitTheme(themes->getTheme(name)) : false;
}

bool CBaseUnit::removeEffect(const std::wstring& name)
{
    return m_pEffectManager != NULL ? m_pEffectManager->removeEffect(name, true) : false;
}

bool CBaseUnit::removeAffix(const std::wstring& name)
{
    return m_pEffectManager != NULL ? m_pEffectManager->deleteAffix(name) : false;
}

bool CBaseUnit::hasEffect(EEFFECT_TYPE type)
{
    return m_pEffectManager != NULL ? m_pEffectManager->hasEffect(type) : false;
}

bool CBaseUnit::hasEffect(EEFFECT_TYPE type, const std::wstring& name)
{
    return m_pEffectManager != NULL ? m_pEffectManager->hasEffect(type, name) : false;
}

bool CBaseUnit::hasEffect(const std::wstring& name)
{
    return m_pEffectManager != NULL ? m_pEffectManager->hasEffect(name) : false;
}

float CBaseUnit::getEffectValue(EEFFECT_TYPE type, float fallback, EDAMAGE_TYPES damage)
{
    return m_pEffectManager != NULL ? m_pEffectManager->getEffectValue(type, damage) : fallback;
}

float CBaseUnit::getEffectValue(EEFFECT_TYPE type, float fallback, const std::wstring& name)
{
    return m_pEffectManager != NULL ? m_pEffectManager->getEffectValue(type, name) : fallback;
}

float CBaseUnit::getEffectValue(EEFFECT_ACTIVATION activation, EEFFECT_TYPE type, float fallback, EDAMAGE_TYPES damage)
{
    return m_pEffectManager != NULL ? m_pEffectManager->getEffectValue(activation, type, damage) : fallback;
}

void CBaseUnit::addUnitTheme(CUnitTheme* theme)
{
    if (m_UnitThemes.find(theme) != -1)
        return;
    m_ThemesToRemove.remove(theme);
    m_ThemesToAdd.add(theme);
    m_UnitThemes.add(theme);
}

void CBaseUnit::removeUnitTheme(CUnitTheme* theme)
{
    if (m_UnitThemes.find(theme) == -1)
        return;
    m_ThemesToRemove.add(theme);
    m_ThemesToAdd.remove(theme);
    m_UnitThemes.remove(theme);
}

void CBaseUnit::addUnitTheme(const std::wstring& name)
{
    CUnitThemes* themes = CUnitThemes::getSingleton();
    if (themes != NULL)
        addUnitTheme(themes->getTheme(name));
}

void CBaseUnit::removeUnitTheme(const std::wstring& name)
{
    CUnitThemes* themes = CUnitThemes::getSingleton();
    if (themes != NULL)
        removeUnitTheme(themes->getTheme(name));
}

void CBaseUnit::removeUnitTheme(long long guid)
{
    CUnitThemes* themes = CUnitThemes::getSingleton();
    if (themes != NULL)
        removeUnitTheme(themes->getTheme(guid));
}

void CBaseUnit::setEditorThemeID(unsigned int id)
{
    if (m_pResourceManager->getEditorIsRunning())
    {
        m_iEditorThemeID = id;
        CUnitThemes* themes = CUnitThemes::getSingleton();
        for (unsigned int i = 1; i <= themes->getThemes().size(); ++i)
        {
            if (i == id)
                addUnitTheme(themes->getThemes()[i-1]);
            else
                removeUnitTheme(themes->getThemes()[i-1]);
        }
    }
}


void CBaseUnit::update(Ogre::Camera* camera,const Ogre::Vector3& cameraPosition,float elapsed)
{
    if (m_pSkillManager != NULL)
        m_pSkillManager->update(elapsed);
    for (unsigned int i = 0; i < m_ThemesToRemove.size(); ++i)
        unitThemeUpdated(m_ThemesToRemove[i], true);
    m_ThemesToRemove.clear();
    for (unsigned int i = 0; i < m_ThemesToAdd.size(); ++i)
        unitThemeUpdated(m_ThemesToAdd[i], false);
    m_ThemesToAdd.clear();
    if (m_pEffectManager != NULL)
    {
        m_pEffectManager->updateAffixes(elapsed);
        TArrayList<CUnitTheme*>* themes = m_pEffectManager->getUnitThemes();
        if (themes != NULL)
        {
            for (unsigned int i = 0; i < themes->size(); ++i)
            {
                if (m_AffixThemes.find((*themes)[i]) == -1)
                {
                    unitThemeUpdated((*themes)[i], false);
                    m_AffixThemes.add((*themes)[i]);
                }
            }
            for (unsigned int i = 0; i < m_AffixThemes.size(); ++i)
            {
                if (themes->find(m_AffixThemes[i]) == -1)
                {
                    unitThemeUpdated(m_AffixThemes[i], true);
                    m_AffixThemes.removeAt(i);
                    --i;
                }
            }
        }
    }
}


CBaseUnit::CBaseUnit(CResourceManager* resourceManager,EBASEUNIT_TYPE type)
    : CPositionableObject(resourceManager,NULL),m_iUnitLevel(1),
      m_ThemesToAdd(1),m_ThemesToRemove(1),m_UnitThemes(1),m_AffixThemes(1),
      m_iQuestGuid(-1),m_iQuestState(-1),m_iRoomIndex(-1),m_iSpawnerGuid(-1),
      m_eBaseUnitType(type),m_bBaseUnitFlag18C(true),m_bBlocksPath(true),
      m_bBaseUnitFlag18E(false),m_bBaseUnitFlag18F(true),m_bBaseUnitFlag190(false),
      m_bSaveFlag191(false),m_fBaseUnitValue194(0.3f),m_bRangeEnabled(false),
      m_bInActiveRange(false),m_bInFadeRange(false),m_bBaseUnitFlag19B(false),
      m_bPathingFlag19C(false),m_iUnitValue1A0(-1),m_bHighlighted(false),
      m_bCastsShadows(true),m_eUnitType(static_cast<UNITTYPES::EUNITTYPES>(0)),
      m_pDataGroup(NULL),m_pEffectManager(NULL),m_pCullingBounds(NULL),
      m_pSkillManager(NULL),m_bBaseUnitFlag0(false),m_bBaseUnitFlag1(false)
{
    m_bEnabled = true;
    CSceneNodeObject::setVisible(false);
    m_pCullingBounds = new CCullingBounds;
}

CBaseUnit::~CBaseUnit()
{
    if (m_bSaveFlag191 && m_pResourceManager != NULL && m_pResourceManager->getLevel() != NULL)
        m_pResourceManager->getLevel()->removeUnit(this,false);
    broadcastUnitState(static_cast<EUNIT_STATES>(0));
    m_iUnitValue1A0 = -1;
    m_pDataGroup = NULL;
    if (m_pCullingBounds != NULL)
    {
        delete m_pCullingBounds;
        m_pCullingBounds = NULL;
    }
    if (m_pEffectManager != NULL)
    {
        delete m_pEffectManager;
        m_pEffectManager = NULL;
    }
    if (m_pSkillManager != NULL)
    {
        delete m_pSkillManager;
        m_pSkillManager = NULL;
    }
}

void CBaseUnit::levelResetting()
{
    if (m_pSkillManager != NULL)
        m_pSkillManager->stopAllSkills(true,false,false);
}


std::wstring CBaseUnit::getUnitDataName()
{
    return m_pDataGroup != NULL ? m_pDataGroup->GetDataValue(L"NAME",EMPTY_WSTRING) : EMPTY_WSTRING;
}

int CBaseUnit::selectRandomSkill()
{
    if (m_pSkillManager != NULL)
    {
        int count = m_pSkillManager->knownSkills(static_cast<ESKILL_ACTIVATION_TYPE>(0));
        if (count > 0)
        {
            CRandomizer random(RANDOMIZER_NORMAL);
            for (int i = 0; i < count; ++i)
                random.addChoice(i,1);
            return random.getRandom();
        }
    }
    return -1;
}

void CBaseUnit::broadcastHPThreshholdEvents(float maximum,float current,float threshold,float change)
{
    static const float eventsByPct[] = {0.9f,0.8f,0.7f,0.6f,0.5f,0.4f,0.3f,0.2f,0.1f};
    static const unsigned int eventsBroadCast[] = {
        OUTPUT_EVENT_HP_90_PCT,OUTPUT_EVENT_HP_80_PCT,OUTPUT_EVENT_HP_70_PCT,
        OUTPUT_EVENT_HP_60_PCT,OUTPUT_EVENT_HP_50_PCT,OUTPUT_EVENT_HP_40_PCT,
        OUTPUT_EVENT_HP_30_PCT,OUTPUT_EVENT_HP_20_PCT,OUTPUT_EVENT_HP_10_PCT};
    if (!m_bBaseUnitFlag0 || ISA(static_cast<UNITTYPES::EUNITTYPES>(28)) || change >= 0 || current + change >= threshold)
        return;
    float oldRatio = current / maximum;
    float newRatio = (current + change) / maximum;
    if (m_bBaseUnitFlag1)
    {
        for (int i = 0; i < 9; ++i)
            if (oldRatio > eventsByPct[i] && newRatio <= eventsByPct[i])
                BroadcastEvent(eventsBroadCast[i]);
    }
    else
    {
        for (int i = 8; i >= 0; --i)
            if (oldRatio > eventsByPct[i] && newRatio <= eventsByPct[i])
            {
                BroadcastEvent(eventsBroadCast[i]);
                return;
            }
    }
}

void CBaseUnit::updateCullingBounds()
{
    if (m_pCullingBounds == NULL)
        return;
    Ogre::Vector3 position = getPosition(true);
    if (getUnitModel() != NULL)
        position += getUnitModel() != NULL ? static_cast<CPositionableObject*>(getUnitModel())->getPosition(false) : Ogre::Vector3::ZERO;
    Ogre::Matrix4 transform = m_mOrientation;
    transform.setTrans(position);
    CCullingBounds& bounds = *m_pCullingBounds;
    const Ogre::Vector3& low = bounds.m_vMinimum;
    const Ogre::Vector3& high = bounds.m_vMaximum;
    bounds.m_vWorldMinimum = transform * low;
    bounds.m_vWorldMaximum = bounds.m_vWorldMinimum;
    MATH::expandBounds(bounds.m_vWorldMinimum,bounds.m_vWorldMaximum,transform * low);
    MATH::expandBounds(bounds.m_vWorldMinimum,bounds.m_vWorldMaximum,transform * high);
    MATH::expandBounds(bounds.m_vWorldMinimum,bounds.m_vWorldMaximum,transform * Ogre::Vector3(low.x,low.y,high.z));
    MATH::expandBounds(bounds.m_vWorldMinimum,bounds.m_vWorldMaximum,transform * Ogre::Vector3(low.x,high.y,high.z));
    MATH::expandBounds(bounds.m_vWorldMinimum,bounds.m_vWorldMaximum,transform * Ogre::Vector3(low.x,high.y,low.z));
    MATH::expandBounds(bounds.m_vWorldMinimum,bounds.m_vWorldMaximum,transform * Ogre::Vector3(high.x,low.y,low.z));
    MATH::expandBounds(bounds.m_vWorldMinimum,bounds.m_vWorldMaximum,transform * Ogre::Vector3(high.x,high.y,low.z));
    MATH::expandBounds(bounds.m_vWorldMinimum,bounds.m_vWorldMaximum,transform * Ogre::Vector3(high.x,low.y,high.z));
    for(unsigned int i=0;i<8;++i)
        bounds.m_WorldCorners[i] = Ogre::Vector3(i&1?bounds.m_vWorldMaximum.x:bounds.m_vWorldMinimum.x,
                                               i&2?bounds.m_vWorldMaximum.y:bounds.m_vWorldMinimum.y,
                                               i&4?bounds.m_vWorldMaximum.z:bounds.m_vWorldMinimum.z);
}


CAffix* CBaseUnit::addAffix(CAffix* affix,unsigned int level,CBaseUnit* source,float scale)
{
    if (m_pEffectManager == NULL)
        m_pEffectManager = new CEffectManager(this);
    return m_pEffectManager->addAffix(affix,level,source,scale);
}

CAffix* CBaseUnit::addAffix(const std::wstring& name,unsigned int level,CBaseUnit* source,float scale)
{
    if (m_pEffectManager == NULL)
        m_pEffectManager = new CEffectManager(this);
    return m_pEffectManager->addAffix(name,level,source,m_pResourceManager,scale);
}

CEffect* CBaseUnit::addNewEffect(CEffect* effect)
{
    if (effect == NULL)
        return NULL;
    if (m_pEffectManager == NULL)
        m_pEffectManager = new CEffectManager(this);
    return m_pEffectManager->addNewEffect(effect);
}

CEffect* CBaseUnit::copyEffect(CBaseUnit* source,CEffect* effect)
{
    if (effect == NULL)
        return NULL;
    if (m_pEffectManager == NULL)
        m_pEffectManager = new CEffectManager(this);
    return m_pEffectManager->cloneEffect(source,effect);
}

void CBaseUnit::copyEffects(CBaseUnit* source,const TArrayList<CEffect*>* effects)
{
    if (effects != NULL)
        for (unsigned int i = 0; i < effects->size(); ++i)
            copyEffect(source,(*effects)[i]);
}

CSkill* CBaseUnit::addSkillByName(const std::wstring& name,bool flag)
{
    if (m_pSkillManager == NULL)
        m_pSkillManager = new CSkillManager(m_pResourceManager,this);
    // Original ignores the public flag and always enables this argument.
    CSkill* skill = m_pSkillManager->addSkill(name,true);
    if (skill != NULL)
        skill->assignSkillAnimations(this);
    return skill;
}

CSkill* CBaseUnit::cloneSkill(CSkill* source)
{
    CSkill* skill = NULL;
    if (source != NULL)
    {
        if (m_pSkillManager == NULL)
            m_pSkillManager = new CSkillManager(m_pResourceManager,this);
        skill = m_pSkillManager->addSkill(source,true,false);
        skill->assignSkillAnimations(this);
    }
    return skill;
}

bool CBaseUnit::dontUseOnFull()
{
    return m_pDataGroup != NULL ? m_pDataGroup->GetDataValue(L"DONT_USE_ON_FULL",false) : false;
}
