#include "UnitSpawnerDescriptorNames.h"
#include "Layout.h"
#include "Level.h"
#include "Character.h"
#include "iUnitSpawner.h"
#include "GameEnums.h"
#include "EditorScene.h"
#include "EmptyStrings.h"
#include "GameVariables.h"
#include "Particle.h"
#include "UnitSpawner.h"
#include "iMissile.h"

#include "GenericModel.h"
#include "UnitResourceList.h"
#include <algorithm>

template<class T> static void destroySpawnerReference(TSafePointer<T>* reference)
{
    if (!reference) return;
    reference->~TSafePointer<T>();
    Ogre::NedAllocImpl::deallocBytes(reference);
}

void CUnitSpawner::createParticleSystemAt(const std::wstring& name, const Ogre::Vector3& position, const Ogre::Quaternion& orientation, unsigned int index)
{
    Ogre::Vector3 snapped = position;
    if (!m_pResourceManager->getLevel()->snapToValidGround(snapped, 0.01f)) return;
    CLayout* layout;
    if (index < m_spawnLayouts.size()) {
        layout = static_cast<CLayout*>(m_spawnLayouts[index]);
        layout->setVisible(true);
    } else {
        layout = new CLayout(m_pResourceManager, static_cast<ELAYOUT_TYPES>(1));
        layout->loadLayoutFile(name, false, NULL, false, false, 0);
        m_spawnLayouts.add(layout);
    }
    layout->setPosition(snapped);
    layout->setOrientation(orientation);
    layout->setVisible(true);
    layout->getSceneNode()->_update(true, true);
    layout->start();
    for (unsigned int i = 0; i < m_spawnListeners.size(); ++i)
        m_spawnListeners[i]->unitSpawnedFromUnitSpawner(this, layout);
}

void CUnitSpawner::setResourceSpawn(std::wstring name)
{
    m_resourceSpawn = name;
    if (m_category == gSPAWN_TYPE_NAMES[2] || m_category == gSPAWN_TYPE_NAMES[4] ||
        m_category == gSPAWN_TYPE_NAMES[3] || m_category == gSPAWN_TYPE_NAMES[5]) return;
    CDataGroup* data = m_pResourceManager->getMasterResourceList()->getDataGroupByObjectName(m_category, m_resourceSpawn);
    std::wstring animation = EMPTY_WSTRING;
    if (data) {
        animation = data->GetDataValue(L"SPAWNER", EMPTY_WSTRING);
        m_hasSpawnAnimation = animation != EMPTY_WSTRING;
    }
    if (m_pResourceManager->getEditorIsRunning()) {
        if (m_editorPreview) { delete m_editorPreview; m_editorPreview = NULL; }
        if (data && animation != EMPTY_WSTRING) {
            m_editorPreview = new CGenericModel(m_pResourceManager, NULL, EMPTY_WSTRING, EMPTY_WSTRING, false);
            m_editorPreview->loadModel(animation, EMPTY_WSTRING, false, false, false);
            m_editorPreview->sceneNodeSetParent(m_pSceneNode, false);
        }
    }
}

void CUnitSpawner::spawn()
{
    setVisible(true);
    reset();
    m_editorSpawning = m_pResourceManager->getEditorIsRunning();
    m_spawning = true;
    m_unitsToCreateInMemory = m_numberOfUnitsToCreate;
    if (m_pulseNumber >= 1 && m_pulseNumber <= ~1u)
        m_unitsToCreateInMemory *= m_pulseNumber;
    if (!(m_spawnDuration > 0.0f)) {
        for (unsigned int i = 0; i < m_unitsToCreateInMemory; ++i)
            if (spawnUnitByIndex(i)) ++m_reset18c;
        if (static_cast<unsigned int>(m_reset18c) != m_unitsToCreateInMemory)
            m_spawning = true;
    }
}

void CUnitSpawner::update(float elapsed)
{
    for (unsigned int i = 0; i < m_spawnLayouts.size(); ++i)
        m_spawnLayouts[i]->update(elapsed);
    if (m_spawning) {
        m_time184 -= elapsed;
        m_time1a0 -= elapsed;
        m_time188 += elapsed;
        if (m_time188 >= m_spawnDuration) {
            for (unsigned int i = m_reset18c; i < m_unitsToCreateInMemory; ++i)
                if (spawnUnitByIndex(i)) ++m_reset18c;
            if (static_cast<unsigned int>(m_reset18c) == m_unitsToCreateInMemory) m_spawning = false;
        } else if (m_time184 <= 0.0f && m_time1a0 <= 0.0f) {
            if (m_pulseNumber >= 1 && m_pulseNumber <= ~1u) {
                while (m_time1a0 < 0.0f) {
                    for (unsigned int i = 0; i < m_numberOfUnitsToCreate; ++i)
                        if (spawnUnitByIndex(m_reset18c + 1)) ++m_reset18c;
                    ++m_counter198;
                    m_time1a0 += m_spawnDuration / float(m_pulseNumber);
                }
            } else {
                while (m_time184 < 0.0f) {
                    if (!spawnUnitByIndex(m_reset18c)) { m_time184 = 0.0f; break; }
                    ++m_reset18c;
                    m_time184 += m_spawnDuration / std::max(1.0f, float(m_unitsToCreateInMemory));
                }
                if (static_cast<unsigned int>(m_reset18c) == m_unitsToCreateInMemory) m_spawning = false;
            }
        }
    }
    if (m_pResourceManager->getEditorIsRunning()) return;
    if (m_spawning && !m_maxMonstersAtATime) return;
    if (!m_spawnedCharacters.size()) return;
    m_time1cc -= elapsed;
    if (m_time1cc > 0.0f) return;
    for (unsigned int i = 0; i < m_spawnedCharacters.size(); ++i) {
        TSafePointer<CCharacter>* ref = m_spawnedCharacters[i];
        if (!ref->getObject() || !ref->getObject()->alive()) {
            if (ref->getObject()) BroadcastEvent(24);
            ref = m_spawnedCharacters[i];
            if (ref) { destroySpawnerReference(ref); m_spawnedCharacters[i] = NULL; }
            m_spawnedCharacters.removeAt(i--);
        }
    }
    if (!m_spawnedCharacters.size() && m_time1cc < 0.0f) BroadcastEvent(25);
}

CUnitSpawner::~CUnitSpawner()
{
    if (m_editorPreview) { delete m_editorPreview; m_editorPreview = NULL; }
    if (m_pResourceManager->getLevel())
        m_pResourceManager->getLevel()->removeListenerFromUnits(this);
    for (unsigned i=0;i<m_spawnedUnits.size();++i) destroySpawnerReference(m_spawnedUnits[i]);
    m_spawnedUnits.clear();
    for (unsigned i=0;i<m_spawnedCharacters.size();++i) destroySpawnerReference(m_spawnedCharacters[i]);
    m_spawnedCharacters.clear();
    clear();
    m_spawnListeners.clear();
    m_spawnLayouts.deleteAll();
}



// Imported source candidates; historical status is not fresh acceptance.
void CUnitSpawner::stop()
{
    m_editorSpawning=false;
    m_spawning=false;
}

bool CUnitSpawner::getParticlesStillVisible()
{
    for(unsigned int i=0;i<m_spawnLayouts.size();++i)if(m_spawnLayouts[i]->getNumberOfParticlesUpdating())return true;
    return false;
}

#include "Layout.h"

void CUnitSpawner::stopAllParticles()
{
    for(unsigned int i=0;i<m_spawnLayouts.size();++i) static_cast<CLayout*>(m_spawnLayouts[i])->stop(false);
}
void CUnitSpawner::reset()
{
    m_reset188=0; m_reset1a0=0; m_reset184=0; m_reset18c=0;
    for(unsigned int i=0;i<m_spawnLayouts.size();++i) {
        static_cast<CLayout*>(m_spawnLayouts[i])->stop(false);
        m_spawnLayouts[i]->setVisible(false);
    }
}
void CUnitSpawner::clear()
{
    for(unsigned int i=0;i<m_spawnLayouts.size();++i) {
        static_cast<CLayout*>(m_spawnLayouts[i])->stop(false);
        m_spawnLayouts[i]->setVisible(false);
    }
}

#include "EditorScene.h"
#include "EmptyStrings.h"
#include "GameVariables.h"
#include "Particle.h"
#include "UnitSpawner.h"
#include "iMissile.h"
#include "Layout.h"
#include "BaseUnit.h"
#include "Character.h"
#include "Item.h"
#include "Equipment.h"
#include "Level.h"
#include "Missile.h"
#include "ResourceManager.h"
#include "UnitSpawnerDescriptorNames.h"
#include "iUnitSpawner.h"
#include <OgreLogManager.h>
#include <OgreMemoryAllocatorConfig.h>
#include <new>
#include <cstring>

CUnitSpawner::CUnitSpawner(CResourceManager* resources)
    : CShape(resources), m_unitsGiveXP(true), m_unitsGiveLoot(true),
      m_spawnInCenter(false), m_spawnOnCreate(true), m_useSpawnAnimation(true),
      m_requiresLOS(false), m_mustSpawn(true), m_spawnDuration(1.0f),
      m_reset184(0), m_reset188(0), m_reset18c(0), m_numberOfUnitsToCreate(10),
      m_pulseNumber(0), m_counter198(0), m_maxMonstersAtATime(0), m_reset1a0(0),
      m_spawnLevelOverrideDelta(0), m_randomWeight(1), m_category(gSPAWN_TYPE_NAMES[0]),
      m_resourceSpawn(EMPTY_WSTRING), m_editorSpawning(false), m_spawning(false),
      m_targetPlayer(false), m_hasSpawnAnimation(false), m_destroyMeshOnDeath(false),
      m_unitsToCreateInMemory(0), m_time1cc(1.0f), m_spawnLayouts(10),
      m_spawnedUnits(10), m_spawnedCharacters(10), m_spawnListeners(10),
      m_snapToGround(true), m_editorPreview(NULL)
{
    std::memset(m_unrecovered234, 0, sizeof(m_unrecovered234));
}

void CUnitSpawner::createUnitsInMemory()
{
    if (m_pResourceManager->getEditorIsRunning())
        return;
    if (m_spawnedCharacters.size() || m_spawnedUnits.size() || m_resourceSpawn.empty())
        return;
    m_unitsToCreateInMemory = m_numberOfUnitsToCreate;
    if (m_pulseNumber - 1u <= 0xfffffffdu)
        m_unitsToCreateInMemory *= m_pulseNumber;
}

void CUnitSpawner::addSpawnedUnit(CBaseUnit* unit)
{
    unit->setSpawnerGuid(getOriginalGuid());
    CCharacter* character = dynamic_cast<CCharacter*>(unit);
    if (character) {
        void* storage = Ogre::GeneralAllocPolicy::allocateBytes(sizeof(TSafePointer<CCharacter>));
        TSafePointer<CCharacter>* ref = new(storage) TSafePointer<CCharacter>;
        try { ref->setObject(character); }
        catch (...) { Ogre::GeneralAllocPolicy::deallocateBytes(storage); throw; }
        m_spawnedCharacters.add(ref);
        return;
    }
    void* storage = Ogre::GeneralAllocPolicy::allocateBytes(sizeof(TSafePointer<CBaseUnit>));
    TSafePointer<CBaseUnit>* ref = new(storage) TSafePointer<CBaseUnit>;
    try { ref->setObject(unit); }
    catch (...) { Ogre::GeneralAllocPolicy::deallocateBytes(storage); throw; }
    m_spawnedUnits.add(ref);
    unit->getLevel()->addListenerToUnit(unit, this);
}

void CUnitSpawner::createAndFireMissile(const std::wstring& name,
    const Ogre::Vector3& position, const Ogre::Quaternion& orientation)
{
    CMissile* missile = m_pResourceManager->createMissile(name);
    if (!missile)
        return;
    for (unsigned int i = 0; i < m_spawnListeners.size(); ++i)
        m_spawnListeners[i]->unitSpawnedFromUnitSpawner(this, missile);
    missile->fireMissile(static_cast<CBaseUnit*>(missile->m_pRunicCore), position,
        orientation, NULL, Ogre::Vector3::ZERO);
}

void CUnitSpawner::hideAndDisableUnits(bool hide)
{
    for (unsigned int i = 0; i < m_spawnedCharacters.size(); ++i) {
        CCharacter* character = m_spawnedCharacters[i]->getObject();
        if (character) {
            character->setEnabled(!hide);
            character->setVisible(!hide, true);
        }
    }
    for (unsigned int i = 0; i < m_spawnLayouts.size(); ++i) {
        CLayout* layout = static_cast<CLayout*>(m_spawnLayouts[i]);
        if (hide) {
            layout->stop(false);
            layout->setVisible(false);
        } else {
            layout->start();
            layout->setVisible(true);
        }
    }
}

void CUnitSpawner::unitStateChange(CBaseUnit* unit, EUNIT_STATES state)
{
    if (unit->getResourceManager() && unit->getResourceManager()->getLevel())
        unit->getResourceManager()->getLevel()->removeListenerFromUnit(unit, this);
    for (unsigned int i = 0; i < m_spawnedUnits.size(); ++i) {
        if (m_spawnedUnits[i]->getObject() == unit) {
            m_spawnedUnits.removeAt(i);
            break;
        }
    }
    if (state == 1) {
        Ogre::LogManager::getSingleton().logMessage("Error in unit creater.  Trying to update character.", Ogre::LML_CRITICAL, false);
    } else if (state == 3) {
        BroadcastEvent(27);
        for (unsigned int i = 0; i < m_spawnedUnits.size(); ++i) {
            if (dynamic_cast<CEquipment*>(m_spawnedUnits[i]->getObject()))
                return;
        }
        BroadcastEvent(28);
    } else if (state == 2) {
        BroadcastEvent(29);
        for (unsigned int i = 0; i < m_spawnedUnits.size(); ++i) {
            if (dynamic_cast<CItem*>(m_spawnedUnits[i]->getObject()) &&
                !dynamic_cast<CEquipment*>(m_spawnedUnits[i]->getObject()))
                return;
        }
        BroadcastEvent(30);
    }
}
void CUnitSpawner::destroyUnits()
{
    m_editorSpawning = false;
    m_spawning = false;
    for (unsigned int i = 0; i < m_spawnedCharacters.size(); ++i) {
        CCharacter* character = m_spawnedCharacters[i]->getObject();
        if (character)
            character->die(NULL, NULL, 0.0f, false);
    }
    for (unsigned int i = 0; i < m_spawnLayouts.size(); ++i) {
        static_cast<CLayout*>(m_spawnLayouts[i])->stop(false);
        m_spawnLayouts[i]->setVisible(false);
    }
    for (unsigned int i = 0; i < m_spawnedCharacters.size(); ++i) {
        TSafePointer<CCharacter>* ref = m_spawnedCharacters[i];
        if (ref) {
            ref->~TSafePointer<CCharacter>();
            Ogre::GeneralAllocPolicy::deallocateBytes(ref);
            m_spawnedCharacters[i] = NULL;
        }
        m_spawnedCharacters[i] = NULL;
    }
    m_spawnedCharacters.clear();
    for (unsigned int i = 0; i < m_spawnedUnits.size(); ++i) {
        TSafePointer<CBaseUnit>* ref = m_spawnedUnits[i];
        if (ref) {
            ref->~TSafePointer<CBaseUnit>();
            Ogre::GeneralAllocPolicy::deallocateBytes(ref);
            m_spawnedUnits[i] = NULL;
        }
        m_spawnedUnits[i] = NULL;
    }
    m_spawnedUnits.clear();
}
