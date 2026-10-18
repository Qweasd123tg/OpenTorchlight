#include "EditorScene.h"
#include "EmptyStrings.h"
#include "GameVariables.h"
#include "Particle.h"
#include "UnitSpawner.h"
#include "iMissile.h"


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
