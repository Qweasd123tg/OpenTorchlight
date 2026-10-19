#include "EmptyStrings.h"
#include "GameVariables.h"
#include "Missile.h"
#include "Particle.h"
#include "iMissile.h"


// Imported source candidates; historical status is not fresh acceptance.
bool CMissile::getCollisionSphereVisible()
{
    return false;
}

bool CMissile::getAOESphereVisible()
{
    return false;
}

void CMissile::setCollisionSphereVisible(bool visible)
{
}

void CMissile::setAOESphereVisible(bool visible)
{
}

void CMissile::setRadiusOfMissile(float radius)
{
    m_fRadiusOfMissile=radius;
}

void CMissile::setAOERadius(float radius)
{
    m_fAOERadius=radius;
}

std::wstring CMissile::getParticleFile(EMISSILE_PARTICLES particle)
{
    if(m_particles[particle])return m_particleFiles[particle];
    return EMPTY_WSTRING;
}

#include "MissileData.h"
#include "Path.h"
#include "Level.h"
#include <OgreMatrix3.h>
#include <OgreMatrix4.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <algorithm>

float CMissile::getRateOFire()
{
    return g_fMissileEditorRefreshRate;
}

void CMissile::setRateOFire(float rate)
{
    g_fMissileEditorRefreshRate = rate;
}

void CMissile::resetMissile()
{
    m_bUnknown185 = false;
    m_fUnknown1BC = 0.0f;
    m_iUnknown1C4 = 0;
    m_fUnknown1C0 = 0.0f;
    m_resetVector148 = Ogre::Vector3::ZERO;
    m_resetVector1A0 = Ogre::Vector3::ZERO;
    m_iUnknown17C = 0;
}

CCharacter* CMissile::getClosestTarget(const Ogre::Quaternion& orientation, const Ogre::Vector3& position)
{
    CCharacter* owner = dynamic_cast<CCharacter*>(m_owner.getObject());
    if (!m_pResourceManager->getLevel() || !owner)
        return NULL;
    Ogre::Matrix3 rotation;
    orientation.ToRotationMatrix(rotation);
    Ogre::Matrix4 transform = Ogre::Matrix4::IDENTITY;
    transform = rotation;
    transform.setTrans(position);
    return m_pResourceManager->getLevel()->findCharacterWithinView(
        transform, owner->getTargetAlignment(), 0.0f, m_fTargetingAngle,
        m_fDistanceAllowedToTraveled + 1.0f, true, NULL, NULL);
}

void CMissile::removeArchFromMissile(float elapsed)
{
    if (!m_pPath || 0.0f >= m_fMissileArchHeight || 0.0f >= m_fUnknown198)
        return;
    Ogre::Vector3 position = getPosition(true);
    float height;
    if (!(m_fUnknown218 >= 1.0f))
        height = m_pPath->GetSplinePositionAtDistance(m_fUnknown218 * m_pPath->m_fPathLength).y;
    else
        height = -m_fMaxVelocity * elapsed;
    position.y -= height;
    setPosition(position);
}

void CMissile::addArchFromMissile(float elapsed)
{
    if (!m_pPath || 0.0f >= m_fMissileArchHeight || 0.0f >= m_fUnknown198)
        return;
    float progress = m_fUnknown1BC / (m_bTargetsPosition ? m_fUnknown198 : m_fDistanceAllowedToTraveled);
    m_fUnknown218 = std::max(std::min(progress, 1.0f), 0.0f);
    float height;
    if (progress >= 1.0f)
        height = m_pPath->GetSplinePositionAtDistance(m_pPath->m_fPathLength).y + (-m_fMaxVelocity) * elapsed;
    else
        height = m_pPath->GetSplinePositionAtDistance(m_fUnknown218 * m_pPath->m_fPathLength).y;
    Ogre::Vector3 position = getPosition(true);
    position.y += height;
    setPosition(position);
}

bool CMissile::handleDeathOfMissile(float elapsed)
{
    m_fUnknown1B4 -= elapsed;
    if (m_fUnknown1B4 > 0.0f)
        return true;
    for (unsigned int i = 0; i < 4; ++i)
    {
        if (!m_particles[i])
            continue;
        m_particles[i]->Stop(false);
        if (m_particles[i]->getNumberOfParticlesUpdating(true))
            return true;
        m_particles[i]->setVisible(false);
    }
    m_Listeners.clear();
    for (unsigned int i = 0; i < m_sceneNodes.size(); ++i)
        if (m_sceneNodes[i]->getParentSceneNode())
            m_pResourceManager->getSceneManager()->getRootSceneNode()->removeChild(m_sceneNodes[i]);
    return false;
}

void CMissile::setTarget(CPositionableObject* target)
{
    m_target.setObject(target);
    m_targetCharacter.setObject(dynamic_cast<CCharacter*>(target));
}

void CMissile::killMissile()
{
    m_bUnknown184 = true;
    m_fUnknown1B4 = 1.0f;
    if (m_particles[3])
    {
        Ogre::Vector3 position = getPosition(true);
        position.y -= m_fUnknown16C;
        m_particles[3]->setPosition(position);
        m_particles[3]->Start();
    }
    for (unsigned int i = 0; i < m_Listeners.size(); ++i)
        m_Listeners[i]->missileDieing(this);
}

#include "OgreUtilities.h"
#include <OgreEntity.h>
void CMissile::placeSphere()
{
    if (static_cast<unsigned int>(m_iUnknown208) >= m_sceneNodes.size())
    {
        for (unsigned int i = 0; i < 10; ++i)
        {
            Ogre::SceneNode* node = m_pResourceManager->getSceneManager()->createSceneNode();
            Ogre::Entity* entity = OGRE_UTILITIES::createEntity(m_pResourceManager->getSceneManager(),
                OGRE_UTILITIES::PRIMITIVE_SPHERE, OGRE_UTILITIES::QUERY_MASK_DEFAULT, "gm");
            node->attachObject(entity);
            node->setScale(0.1f, 0.1f, 0.1f);
            m_sceneNodes.add(node);
        }
    }
    m_sceneNodes[m_iUnknown208]->setPosition(getPosition(false));
    m_pResourceManager->getSceneManager()->getRootSceneNode()->addChild(m_sceneNodes[m_iUnknown208]);
    ++m_iUnknown208;
}

#include "ParticlePreloader.h"
#include "MasterResourceManager.h"
#include "StringUtilities.h"
void CMissile::setParticleFile(EMISSILE_PARTICLES particle, std::wstring file)
{
    if (file.empty())
    {
        if (m_particles[particle])
        {
            delete m_particles[particle];
            m_particles[particle] = NULL;
        }
        m_particleFiles[particle] = EMPTY_WSTRING;
        return;
    }
    file = STRINGS::StringUpper(file);
    if (file == m_particleFiles[particle])
        return;
    if (m_particles[particle])
    {
        delete m_particles[particle];
        m_particles[particle] = NULL;
    }
    m_particleFiles[particle] = file;
    CMasterResourceManager::getSingleton()->m_pParticlePreloader->LoadParticle(file);
    m_particles[particle] = CMasterResourceManager::getSingleton()->m_pParticlePreloader->GetParticle(m_pResourceManager, file.c_str());
    if (m_particles[particle])
        m_particles[particle]->Stop(false);
}

#include "Item.h"
void CMissile::initialize()
{
    m_bUnknown294 = false;
    m_fUnknown290 = 1.0f;
    m_targetCharacter.setObject(NULL);
    m_fUnknown274 = 0.0f;
    m_fUnknown170 = 0.0f;
    m_fUnknown218 = 0.0f;
    m_fUnknown198 = 0.0f;
    m_fUnknown258 = 0.0f;
    m_fMissileArchHeight = 0.0f;
    m_fHomeAfterXSeconds = 0.0f;
    m_bTargetsPosition = false;
    m_bCollidesWithObjects = true;
    m_bTrackGround = false;
    m_fTargetingAngle = 120.0f;
    m_fUnknown174 = 0.0f;
    m_fUnknown25C = 0.0f;
    m_fMaxTurnRate = 0.0f;
    m_fTurnAcceleration = 0.0f;
    m_fAOEDamageScale = 1.0f;
    m_fSoakScale = 1.0f;
    m_fRandomizedTurnAcceleration = 0.0f;
    m_fRandomizedTurnUpdate = 0.25f;
    m_targetPosition = Ogre::Vector3::ZERO;
    m_fTargetHomingValue = 0.0f;
    m_target.setObject(NULL);
    m_iUnknown164 = 0;
    m_fUnknown16C = 0.0f;
    m_iUnknown168 = 0x42480000;
    m_fDistanceAllowedToTraveled = 25.0f;
    m_fUnknown1BC = 0.0f;
    m_iUnknown1C4 = 0.0f;
    m_fUnknown1C0 = 0.0f;
    m_bUnknown185 = false;
    m_fUnknown1B4 = 999.0f;
    m_iUnknown208 = 0;
    m_fLifetimeRemaining = 0.0f;
    m_resetVector148 = Ogre::Vector3::ZERO;
    m_resetVector1A0 = Ogre::Vector3::ZERO;
    m_fForceAppliedPerSecond = 0.0f;
    m_fMaxVelocity = 1.0f;
    m_bStartAtFullVelocity = true;
    m_iNumberOfRicochets = 0;
    m_iUnknown17C = 0;
    m_fRadiusOfMissile = 0.2f;
    m_fFriction = 1.0f;
    m_bUnknown141 = false;
    m_bUnknown184 = false;
    m_fInherentMinDMGPercent = 0.0f;
    m_fInherentMaxDMGPercent = 0.0f;
    m_fInherentKnockback = 0.0f;
    m_owner.setObject(NULL);
    m_fLifetime = 3.0f;
    for (unsigned int i = 0; i < 4; ++i)
        m_particles[i] = NULL;
    setVisible(true);
    m_fAOERadius = 0.0f;
}

void CMissile::doAOEDamage(CBaseUnit* excluded)
{
    static TArrayList<CCharacter*> mCharacterList(25);
    static TArrayList<CItem*> mItemList(25);
    mCharacterList.clear();
    mItemList.clear();
    if (!(m_fAOERadius > 0.0f))
        return;
    Ogre::Vector3 position = getPosition(true);
    m_pResourceManager->getLevel()->getActiveUnitsAtPosition(position, m_fAOERadius, mCharacterList, mItemList);
    for (unsigned int i = 0; i < mCharacterList.size(); ++i)
    {
        if (mCharacterList[i] == m_owner.getObject() || mCharacterList[i] == excluded)
            continue;
        Ogre::Vector3 origin = getPosition(false);
        Ogre::Vector3 direction = mCharacterList[i]->getPosition(true) - origin;
        direction.normalise();
        doDamageToCharacter(mCharacterList[i], direction, m_fAOEDamageScale, m_fSoakScale);
    }
    for (unsigned int i = 0; i < mItemList.size(); ++i)
        if (mItemList[i] != m_owner.getObject() && mItemList[i] != excluded)
            mItemList[i]->interact(NULL);
}

Ogre::Vector3 CMissile::ricochetMissile(const Ogre::Vector3&, const Ogre::Vector3&,
                                      const Ogre::Vector3& position, const Ogre::Vector3& surfaceNormal)
{
    if (m_particles[2])
    {
        Ogre::Vector3 particlePosition = getPosition(true);
        particlePosition.y -= m_fUnknown16C;
        m_particles[2]->setPosition(particlePosition);
        if (&position)
        {
            Ogre::Vector3 forward = position;
            forward.normalise();
            Ogre::Vector3 up = Ogre::Vector3::UNIT_Y;
            m_particles[2]->setOrientation(forward, up);
        }
        m_particles[2]->Start();
    }
    ++m_iUnknown17C;
    Ogre::Vector3 normal = surfaceNormal;
    normal.normalise();
    float product = m_resetVector148.dotProduct(normal);
    m_resetVector148 -= (normal * product) * 2.0f;
    if (surfaceNormal.y == 0.0f)
    {
        float speed = m_resetVector148.length();
        m_resetVector148.y = 0.0f;
        m_resetVector148.normalise();
        m_resetVector148 *= speed;
    }
    return position + normal * (m_fRadiusOfMissile + 0.01f);
}

CMissile::CMissile(CResourceManager* resources)
    : CPositionableObject(resources, NULL), m_bPiercing(false), m_bCanVerticalAim(true), m_bUnknown144(false),
      m_fUnknown16C(0.0f), m_fUnknown170(0.0f), m_Listeners(10), m_sceneNodes(10), m_pPath(NULL),
      m_fMaxTurnRate(0.0f), m_fTurnAcceleration(0.0f), m_fRandomizedTurnAcceleration(0.0f),
      m_fRandomizedTurnUpdate(0.25f), m_fUnknown274(0.0f), m_fUnknown278(0.0f),
      m_fInherentMinDMGPercent(0.0f), m_fInherentMaxDMGPercent(0.0f), m_fInherentKnockback(0.0f),
      m_collisionUnits(10), m_collisionStates(10), m_sMissileName(L""), m_iDamageType(0)
{
    initialize();
}

CMissile::CMissile(CResourceManager* resources, const CMissile* source)
    : CPositionableObject(resources, NULL), m_Listeners(10), m_sceneNodes(10), m_pPath(NULL),
      m_collisionUnits(10), m_collisionStates(10), m_sMissileName(L"")
{
    initialize();
    setPosition(source->m_vPosition);
    m_iDamageType = source->m_iDamageType;
    m_fMissileArchHeight = source->m_fMissileArchHeight;
    m_bTargetsPosition = source->m_bTargetsPosition;
    m_bCollidesWithObjects = source->m_bCollidesWithObjects;
    m_bTrackGround = source->m_bTrackGround;
    m_fTargetingAngle = source->m_fTargetingAngle;
    m_fUnknown170 = source->m_vPosition.y;
    m_fUnknown16C = source->m_fUnknown16C;
    m_fForceAppliedPerSecond = source->m_fForceAppliedPerSecond;
    m_fMaxVelocity = source->m_fMaxVelocity;
    m_fAOEDamageScale = source->m_fAOEDamageScale;
    m_fSoakScale = source->m_fSoakScale;
    m_bStartAtFullVelocity = source->m_bStartAtFullVelocity;
    m_iNumberOfRicochets = source->m_iNumberOfRicochets;
    m_fRadiusOfMissile = source->m_fRadiusOfMissile;
    m_fFriction = source->m_fFriction;
    m_owner.setObject(source->m_owner.getObject());
    m_fLifetime = source->m_fLifetime;
    m_fDistanceAllowedToTraveled = source->m_fDistanceAllowedToTraveled;
    m_fAOERadius = source->m_fAOERadius;
    m_bPiercing = source->m_bPiercing;
    m_bCanVerticalAim = source->m_bCanVerticalAim;
    m_fMaxTurnRate = source->m_fMaxTurnRate;
    m_fTurnAcceleration = source->m_fTurnAcceleration;
    m_fRandomizedTurnAcceleration = source->m_fRandomizedTurnAcceleration;
    m_fRandomizedTurnUpdate = source->m_fRandomizedTurnUpdate;
    m_fInherentMinDMGPercent = source->m_fInherentMinDMGPercent;
    m_fInherentMaxDMGPercent = source->m_fInherentMaxDMGPercent;
    m_fInherentKnockback = source->m_fInherentKnockback;
    m_fTargetHomingValue = source->m_fTargetHomingValue;
    m_sMissileName = source->m_sMissileName;
    m_fHomeAfterXSeconds = source->m_fHomeAfterXSeconds;
    m_fUnknown274 = 0.0f;
    for (unsigned int i = 0; i < 4; ++i)
        if (source->m_particles[i])
            setParticleFile(static_cast<EMISSILE_PARTICLES>(i), source->m_particleFiles[i]);
}

CMissile::~CMissile()
{
    for (unsigned int i = 0; i < m_sceneNodes.size(); ++i)
    {
        if (m_sceneNodes[i]->getParentSceneNode())
            m_pResourceManager->getSceneManager()->getRootSceneNode()->removeChild(m_sceneNodes[i]);
        m_pResourceManager->getSceneManager()->destroyEntity(static_cast<Ogre::Entity*>(m_sceneNodes[i]->getAttachedObject(0)));
        m_pResourceManager->getSceneManager()->destroySceneNode(m_sceneNodes[i]);
    }
    m_sceneNodes.clear();
    m_Listeners.clear();
    for (unsigned int i = 0; i < 4; ++i)
        if (m_particles[i])
        {
            delete m_particles[i];
            m_particles[i] = NULL;
        }
    if (m_pPath)
    {
        delete m_pPath;
        m_pPath = NULL;
    }
}
#include "Graph.h"
#include "Utilities.h"
#include <algorithm>

void CMissile::calculateLaunchOrientation(const Ogre::Vector3& start, const Ogre::Vector3& target)
{
    Ogre::Vector3 originalStart = start;
    Ogre::Vector3 originalTarget = target;
    m_targetPosition = originalTarget;
    Ogre::Vector3 direction = originalTarget - originalStart;
    float limit = Ogre::Vector3(originalTarget.x, originalStart.y, originalTarget.z).length() * 0.25f;
    direction.y = std::max(-limit, std::min(limit, direction.y));
    direction.y += originalStart.y;
    direction.y -= originalStart.y;
    direction.normalise();
    Ogre::Vector3 up = Ogre::Vector3::UNIT_Y;
    setOrientation(direction, up);
    m_fUnknown198 = (start - target).length();
    if (!(m_fMissileArchHeight > 0.0f))
        return;
    Ogre::Vector3 endpoint = m_targetPosition;
    if (m_pResourceManager->getGameClient())
    {
        Ogre::Vector3 top = endpoint, bottom = endpoint, normal, extra;
        unsigned int type;
        top.y += 100.0f;
        bottom.y -= 100.0f;
        m_pResourceManager->getLevel()->rayCollision(top, bottom, endpoint, normal, type, extra, false);
    }
    if (!m_pPath)
        m_pPath = new CPath("", false, Ogre::Vector3::ZERO);
    m_pPath->Clear();
    m_pPath->AddPoint(start, -60.0f, 60.0f);
    Ogre::Vector3 middle = (start + endpoint) * 0.5f + Ogre::Vector3(0.0f, m_fMissileArchHeight, 0.0f);
    m_pPath->AddPoint(middle, -60.0f, 60.0f);
    m_pPath->AddPoint(endpoint, -60.0f, 60.0f);
    m_fUnknown218 = 0.0f;
}

bool CMissile::doDamageToCharacter(CCharacter* target, const Ogre::Vector3& direction, float damageScale, float effectScale)
{
    if (target)
        for (unsigned int i = 0; i < m_Listeners.size(); ++i)
            if (!m_Listeners[i]->getCharacterCanBeHarmedByMissile(this, target))
                return false;
    bool unhandled = true;
    for (unsigned int i = 0; i < m_Listeners.size(); ++i)
        if (m_Listeners[i]->missileApplyingEffects(this, target, &direction, damageScale * m_fUnknown290, effectScale))
            unhandled = false;
    if (unhandled)
    {
        float graphValue = m_pResourceManager->getGraphDamage()->getValue(static_cast<float>(target->m_iUnitLevel), 0);
        float damage = graphValue * UTILITIES::randomBetweenVolatile(m_fInherentMinDMGPercent, m_fInherentMaxDMGPercent) * m_fUnknown290;
        Ogre::Vector3 position = getPosition(true);
        target->applyDamage(*m_pResourceManager->getLevel(), position, damage, direction, m_fInherentKnockback, NULL, false, true, true, false, 0x200);
    }
    return true;
}
bool CMissile::handleMissileHitUnit(CBaseUnit* unit, Ogre::Vector3 direction)
{
    if (!unit)
        return false;
    direction.y = 0.0f;
    direction.normalise();
    if (unit->ISA(UNITTYPES::INTERACTABLE))
        return true;
    // The original hierarchy's root ITEM has identifier 2.
    if (unit->ISA(static_cast<UNITTYPES::EUNITTYPES>(2)))
    {
        if (!static_cast<CItem*>(unit)->interact(NULL))
            return false;
    }
    else
    {
        bool permitted = true;
        for (unsigned int i = 0; i < m_Listeners.size(); ++i)
            if (!m_Listeners[i]->getCharacterCanBeHarmedByMissile(this, static_cast<CCharacter*>(unit)))
            {
                permitted = false;
                break;
            }
        if (permitted)
        {
            float reflection = static_cast<CCharacter*>(unit)->getDmgToReflectFromMissile();
            if (reflection > 0.0f)
            {
                m_fUnknown290 = reflection;
                m_bUnknown294 = true;
                setForward(-getForward());
                setRight(-getRight());
                setTarget(NULL);
                m_iUnknown1C4 = 0.0f;
                m_fUnknown1BC = 0.0f;
                m_fUnknown1C0 = 0.0f;
                m_resetVector148 = -m_resetVector148;
                return false;
            }
        }
        Ogre::Vector3 forward = m_resetVector148;
        forward.y = 0.0f;
        forward.normalise();
        Ogre::Vector3 combined = forward * 2.0f + direction;
        combined.normalise();
        if (!doDamageToCharacter(static_cast<CCharacter*>(unit), combined, 1.0f, m_fSoakScale))
            return false;
    }
    doAOEDamage(unit);
    return true;
}

bool CMissile::update(float elapsed)
{
    if (!m_bVisible)
        return false;
    if (!m_bUnknown185)
        return true;
    if (m_bUnknown184)
        m_fUnknown174 -= elapsed;
    if (m_particles[1])
    {
        if (m_fUnknown174 >= 0.0f)
        {
            Ogre::Vector3 position = getPosition(true);
            position.y -= m_fUnknown16C;
            m_particles[1]->setPosition(position);
        }
        else
            m_particles[1]->Stop(false);
    }
    Ogre::Vector3 position = getPosition(true);
    Ogre::Vector3 distance = m_resetVector1A0 - position;
    distance.y = 0.0f;
    float travelled = distance.length();
    m_fUnknown1BC += travelled;
    m_fUnknown1C0 += travelled;
    if (!m_bUnknown184 && (m_fUnknown1C0 >= m_fDistanceAllowedToTraveled ||
        (m_bTargetsPosition && m_fUnknown1BC >= m_fUnknown198)))
    {
        killMissile();
        doAOEDamage(NULL);
    }
    if (m_bUnknown184)
        return handleDeathOfMissile(elapsed);
    m_resetVector1A0 = getPosition(true);
    position = updatePositionByVelocity(elapsed);
    if (m_pResourceManager->getEditorIsRunning())
    {
        setPosition(position);
        return true;
    }
    bool collided = false;
    Ogre::Vector3 normal, extra;
    CBaseUnit* unit;
    do
    {
        unit = NULL;
        if (checkCollision(m_resetVector1A0, position, position, extra, normal, &unit))
            collided = true;
    }
    while (m_bPiercing && unit);
    setPosition(position);
    if (collided && m_particles[2])
    {
        Ogre::Vector3 particlePosition = getPosition(true);
        particlePosition.y -= m_fUnknown16C;
        m_particles[2]->setPosition(particlePosition);
        normal.normalise();
        Ogre::Vector3 up = Ogre::Vector3::UNIT_Y;
        m_particles[2]->setOrientation(normal, up);
        m_particles[2]->Start();
    }
    return true;
}
#include "UtilitiesMath.h"
#include "MasterResourceManager.h"
#include "Settings.h"
#include "SettingsVariables.h"
#include <cmath>

Ogre::Vector3 CMissile::updatePositionByVelocity(float elapsed)
{
    m_resetVector148 += (getForward() * m_fForceAppliedPerSecond) * elapsed;
    m_resetVector148 += (getForwardAbsolute() * m_fForceAppliedPerSecond) * elapsed;
    float speed = m_resetVector148.normalise();
    m_fUnknown258 -= elapsed;
    if (m_targetCharacter.getObject())
    {
        bool retarget = !m_targetCharacter.getObject()->alive();
        if (!retarget)
            for (unsigned int i = 0; i < m_collisionUnits.size(); ++i)
                if (m_collisionUnits[i] == m_targetCharacter.getObject())
                {
                    retarget = true;
                    break;
                }
        if (retarget)
        {
            Ogre::Vector3 position = getPosition(true);
            Ogre::Quaternion orientation = getOrientationQuaternion();
            setTarget(getClosestTarget(orientation, position));
        }
    }
    if (m_fUnknown258 <= 0.0f && m_target.getObject() && m_fTargetHomingValue > 0.0f)
    {
        m_fUnknown25C += elapsed;
        while (m_fUnknown25C >= 1.0f / 30.0f)
        {
            m_fUnknown25C -= 1.0f / 30.0f;
            Ogre::Vector3 targetPosition = m_target.getObject()->getPosition(true);
            targetPosition.y += m_fRadiusOfMissile * 2.0f;
            Ogre::Vector3 direction = targetPosition - getPosition(true);
            direction.normalise();
            m_resetVector148 = direction * m_fTargetHomingValue + m_resetVector148 * (1.0f - m_fTargetHomingValue);
            m_resetVector148.normalise();
        }
    }
    m_fUnknown274 += elapsed * m_fTurnAcceleration;
    m_fUnknown278 += elapsed;
    if (m_fUnknown278 > m_fRandomizedTurnUpdate)
    {
        m_fUnknown274 += UTILITIES::randomBetweenVolatile(-m_fRandomizedTurnAcceleration, m_fRandomizedTurnAcceleration);
        m_fUnknown278 = 0.0f;
    }
    if (std::fabs(m_fUnknown274) > std::fabs(m_fMaxTurnRate))
        m_fUnknown274 = m_fUnknown274 < 0.0f ? -m_fMaxTurnRate : m_fMaxTurnRate;
    MATH::rotateY(&m_resetVector148, static_cast<float>(static_cast<double>(m_fUnknown274 * elapsed) * 0.01745329252));
    float magnitude = speed * m_fFriction;
    Ogre::Vector3 forward = m_resetVector148;
    forward.normalise();
    Ogre::Vector3 up = Ogre::Vector3::UNIT_Y;
    setOrientation(forward, up);
    m_resetVector148 *= magnitude;
    Ogre::Vector3 position = getPosition(true);
    if (m_pPath && m_fMissileArchHeight > 0.0f)
    {
        m_iUnknown1C4 += m_resetVector148.length() * elapsed;
        m_iUnknown1C4 = std::min(m_iUnknown1C4, m_pPath->m_fPathLength);
        position = m_pPath->GetSplinePositionAtDistance(m_iUnknown1C4);
        if (m_iUnknown1C4 >= m_pPath->m_fPathLength)
        {
            m_fUnknown1C0 = m_fDistanceAllowedToTraveled;
            m_fUnknown1BC = m_fUnknown198;
        }
        float next = std::min(m_iUnknown1C4 + 0.01f, m_pPath->m_fPathLength);
        Ogre::Vector3 from = m_pPath->GetSplinePositionAtDistance(std::max(next - 0.02f, 0.0f));
        Ogre::Vector3 to = m_pPath->GetSplinePositionAtDistance(next);
        Ogre::Vector3 tangent = to - from;
        tangent.normalise();
        if (m_particles[1])
        {
            Ogre::Vector3 particleUp = Ogre::Vector3::UNIT_Y;
            m_particles[1]->setOrientation(tangent, particleUp);
        }
    }
    else
    {
        position += m_resetVector148 * elapsed;
        if (m_particles[1])
        {
            Ogre::Vector3 direction = m_resetVector148;
            direction.normalise();
            Ogre::Vector3 particleUp = Ogre::Vector3::UNIT_Y;
            m_particles[1]->setOrientation(direction, particleUp);
        }
    }
    if (CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_SHOW_MISSILE_TRAILS) == 1 &&
        (position - m_previousVelocityPosition).length() > 1.0f)
    {
        m_previousVelocityPosition = position;
        placeSphere();
    }
    return position;
}
int CMissile::checkCollision(Ogre::Vector3 start, Ogre::Vector3 end, Ogre::Vector3& position,
                            Ogre::Vector3& impact, Ogre::Vector3& normal, CBaseUnit** collidedUnit)
{
    if (m_bPiercing)
        for (unsigned int i = 0; i < m_collisionUnits.size(); ++i)
        {
            m_collisionStates[i] = m_collisionUnits[i]->m_bBlocksPath;
            m_collisionUnits[i]->m_bBlocksPath = false;
        }
    TSafePointer<CBaseUnit> originalOwner;
    bool ownerBlocks = false;
    if (m_owner.getObject())
    {
        ownerBlocks = m_owner.getObject()->m_bBlocksPath;
        originalOwner.setObject(m_owner.getObject());
        m_owner.getObject()->m_bBlocksPath = m_bUnknown144;
    }
    start.y += m_fUnknown170;
    end.y += m_fUnknown170;
    position = end;
    m_pResourceManager->getLevel()->sortForCollisionByPoints(start, end, m_fRadiusOfMissile);
    Ogre::Vector3 collisionPoint, extra;
    unsigned int collisionType;
    CBaseUnit* unit = NULL;
    bool result = m_pResourceManager->getLevel()->preSortedSphereCollision(start, end, m_fRadiusOfMissile,
        collisionPoint, impact, normal, collisionType, extra, &unit, m_bCollidesWithObjects);
    if (collisionType == 100)
    {
        normal.y = 0.0f;
        normal.normalise();
    }
    if (m_bPiercing && unit && !unit->ISA(static_cast<UNITTYPES::EUNITTYPES>(25)) && !unit->ISA(UNITTYPES::BREAKABLE))
        unit = NULL;
    bool process = false;
    if (!result || (unit && !m_bUnknown144 && unit == m_owner.getObject()))
    {
        position.y -= m_fUnknown170;
        unit = NULL;
        result = false;
    }
    else if (unit)
    {
        result = handleMissileHitUnit(unit, unit->getPosition(true) - start);
        if (!result)
        {
            position.y -= m_fUnknown170;
            impact.y -= m_fUnknown170;
            unit = NULL;
        }
        else
        {
            if (m_bPiercing)
            {
                bool found = false;
                for (unsigned int i = 0; i < m_collisionUnits.size(); ++i)
                    if (m_collisionUnits[i] == unit)
                    {
                        found = true;
                        break;
                    }
                if (!found)
                {
                    m_collisionUnits.add(unit);
                    m_collisionStates.add(true);
                }
            }
            process = true;
        }
    }
    else if (m_bTrackGround && normal.y > 0.2f)
    {
        position = collisionPoint;
        position.y += m_fRadiusOfMissile;
        position.y -= m_fUnknown170;
        impact.y -= m_fUnknown170;
        unit = NULL;
        result = false;
    }
    else
        process = true;
    if (process)
    {
        if (!m_bPiercing || !unit)
        {
            position = collisionPoint;
            bool bounced = false;
            if (m_iNumberOfRicochets && static_cast<unsigned int>(m_iNumberOfRicochets) >= static_cast<unsigned int>(m_iUnknown17C))
            {
                position = ricochetMissile(position, end, impact, normal);
                if (m_bPiercing)
                    for (unsigned int i = 0; i < m_collisionUnits.size(); ++i)
                        m_collisionUnits[i]->m_bBlocksPath = m_collisionStates[i];
                m_collisionUnits.clear();
                m_collisionStates.clear();
                m_fUnknown1C0 = 0.0f;
                bounced = m_iNumberOfRicochets && static_cast<unsigned int>(m_iNumberOfRicochets) >= static_cast<unsigned int>(m_iUnknown17C);
            }
            if (!bounced && !(m_bPiercing && unit) && !m_bUnknown184)
            {
                killMissile();
                if (!unit)
                    doAOEDamage(NULL);
            }
        }
        position.y -= m_fUnknown170;
        impact.y -= m_fUnknown170;
    }
    if (m_bPiercing)
        for (unsigned int i = 0; i < m_collisionUnits.size(); ++i)
            m_collisionUnits[i]->m_bBlocksPath = m_collisionStates[i];
    if (collidedUnit && result)
        *collidedUnit = unit;
    if (originalOwner.getObject())
        originalOwner.getObject()->m_bBlocksPath = ownerBlocks;
    return result;
}
#include "GameClient.h"

void CMissile::fireMissile(CBaseUnit* owner, Ogre::Vector3 position, const Ogre::Quaternion& orientation,
                          CPositionableObject* target, Ogre::Vector3 aim)
{
    m_collisionUnits.clear();
    m_collisionStates.clear();
    for (unsigned int i = 0; i < 4; ++i)
        if (m_particles[i])
        {
            m_particles[i]->Stop(false);
            m_particles[i]->setVisible(false);
            m_particles[i]->setOrientation(orientation);
            m_particles[i]->setPosition(position);
        }
    m_bUnknown144 = false;
    if (!m_bUnknown185)
        for (unsigned int i = 0; i < m_Listeners.size(); ++i)
            target = m_Listeners[i]->missileValidateTargetBeforeLaunch(this, target, aim);
    if (!owner)
        owner = m_owner.getObject();
    float ground = owner ? owner->getPosition(true).y - owner->m_fBaseUnitValue194 : 0.0f;
    float height = position.y - m_fRadiusOfMissile - ground;
    if (height < 0.01f)
    {
        m_fUnknown16C = -height;
        position.y += -height;
    }
    m_resetVector1A0 = position;
    m_previousVelocityPosition = position;
    setTarget(target);
    m_fUnknown25C = 0.0f;
    m_iUnknown1C4 = 0.0f;
    m_fUnknown1BC = 0.0f;
    m_fUnknown1C0 = 0.0f;
    m_fLifetimeRemaining = m_fLifetime;
    m_fUnknown174 = 0.1f;
    m_bUnknown141 = false;
    m_bUnknown184 = false;
    m_iUnknown17C = 0;
    m_fUnknown258 = m_fHomeAfterXSeconds;
    m_owner.setObject(owner);
    setPosition(position);
    setOrientation(orientation);
    m_pSceneNode->_update(true, true);
    if (!target)
    {
        target = m_target.getObject();
        if (!target && m_owner.getObject())
        {
            CCharacter* character = dynamic_cast<CCharacter*>(m_owner.getObject());
            if (character)
            {
                CPositionableObject* preferred = character->m_targetCharacter.getObject();
                if (!preferred)
                    preferred = character->m_targetItem.getObject();
                if (preferred)
                {
                    setTarget(preferred);
                    target = m_target.getObject();
                }
                else if (m_fTargetHomingValue > 0.0f)
                {
                    CCharacter* closest = getClosestTarget(orientation, position);
                    m_target.setObject(closest);
                    setTarget(closest);
                }
            }
        }
    }
    float muzzleDistance = 0.0f;
    if (owner)
    {
        Ogre::Vector3 ownerPosition = owner->getPosition(true);
        muzzleDistance = Ogre::Vector3(position.x - ownerPosition.x, 0.0f, position.z - ownerPosition.z).length();
    }
    if (target)
    {
        if (owner)
        {
            Ogre::Vector3 ownerPosition = owner->getPosition(true);
            Ogre::Vector3 targetPosition = target->getPosition(true);
            float targetGround = targetPosition.y - static_cast<CBaseUnit*>(target)->m_fBaseUnitValue194;
            float distance = Ogre::Vector3(targetPosition.x - ownerPosition.x, 0.0f, targetPosition.z - ownerPosition.z).length();
            Ogre::Vector3 forward = orientation.zAxis();
            aim.x = forward.x * distance + ownerPosition.x + (position.x - ownerPosition.x);
            aim.y = (forward.y * distance + ground) + (targetGround - ground) + (position.y - ground);
            aim.z = forward.z * distance + ownerPosition.z + (position.z - ownerPosition.z);
            ownerPosition = owner->getPosition(true);
            if (Ogre::Vector3(aim.x - ownerPosition.x, 0.0f, aim.z - ownerPosition.z).length() > muzzleDistance + 0.1f)
                calculateLaunchOrientation(position, aim);
        }
        else
        {
            Ogre::Vector3 targetPosition = target->getPosition(true);
            float distance = Ogre::Vector3(targetPosition.x - position.x, 0.0f, targetPosition.z - position.z).length();
            Ogre::Vector3 forward = orientation.zAxis();
            Ogre::Vector3 endpoint(position.x + forward.x * distance, height + targetPosition.y, position.z + forward.z * distance);
            if (0.0f > muzzleDistance + 0.1f)
                calculateLaunchOrientation(position, endpoint);
        }
    }
    else if (m_pResourceManager->getGameClient())
    {
        if (aim == Ogre::Vector3::ZERO && owner && owner->ISA(UNITTYPES::PLAYER) && m_bCanVerticalAim)
        {
            m_pResourceManager->getGameClient()->findWorldLocation(aim, true);
            Ogre::Vector3 top = aim, bottom = aim, hit = position, normal, extra;
            unsigned int type;
            top.y += 100.0f;
            bottom.y -= 100.0f;
            aim = Ogre::Vector3::ZERO;
            if (m_pResourceManager->getLevel()->rayCollision(top, bottom, hit, normal, type, extra, false) && type != 100)
            {
                Ogre::Vector3 ownerPosition = owner->getPosition(true);
                float distance = Ogre::Vector3(hit.x - ownerPosition.x, 0.0f, hit.z - ownerPosition.z).length();
                Ogre::Vector3 forward = orientation.zAxis();
                aim.x = forward.x * distance + ownerPosition.x + (position.x - ownerPosition.x);
                aim.y = (((hit.y - ground) + (forward.y * distance + ground)) - height) + (position.y - ground);
                aim.z = forward.z * distance + ownerPosition.z + (position.z - ownerPosition.z);
            }
            else
            {
                aim = position + getForward();
                aim.y -= height;
            }
        }
        if (aim != Ogre::Vector3::ZERO)
        {
            float distance = 0.0f;
            if (owner)
            {
                Ogre::Vector3 ownerPosition = owner->getPosition(true);
                distance = Ogre::Vector3(aim.x - ownerPosition.x, 0.0f, aim.z - ownerPosition.z).length();
            }
            aim.y += height;
            if (distance > muzzleDistance + 0.1f)
                calculateLaunchOrientation(position, aim);
        }
    }
    if (m_bStartAtFullVelocity)
        m_resetVector148 = getForward() * m_fMaxVelocity;
    setVisible(true);
    if (!m_bUnknown185)
        for (unsigned int i = 0; i < m_Listeners.size(); ++i)
            m_Listeners[i]->missileBeingFired(this);
    CBaseUnit* collided = NULL;
    if (owner && position != owner->getPosition(true))
    {
        Ogre::Vector3 ownerPosition = owner->getPosition(true);
        ownerPosition.y = position.y;
        if ((ownerPosition - position).length() < 4.0f)
        {
            Ogre::Vector3 collisionPosition, impact, normal;
            if (checkCollision(ownerPosition, position, collisionPosition, impact, normal, &collided) && collided)
            {
                if (m_particles[0])
                {
                    Ogre::Vector3 particlePosition = getPosition(true);
                    particlePosition.y -= m_fUnknown16C;
                    m_particles[0]->setPosition(particlePosition);
                    m_particles[0]->Start();
                }
                setPosition(collisionPosition);
                if (!collided)
                    doAOEDamage(NULL);
                if (m_bPiercing || collided->ISA(static_cast<UNITTYPES::EUNITTYPES>(25)) || collided->ISA(UNITTYPES::BREAKABLE))
                {
                    if (m_particles[1])
                    {
                        Ogre::Vector3 particlePosition = getPosition(true);
                        particlePosition.y -= m_fUnknown16C;
                        m_particles[1]->setPosition(particlePosition);
                        m_particles[1]->Start();
                    }
                    bool found = false;
                    for (unsigned int i = 0; i < m_collisionUnits.size(); ++i)
                        if (m_collisionUnits[i] == collided)
                        {
                            found = true;
                            break;
                        }
                    if (!found)
                    {
                        m_collisionUnits.add(collided);
                        m_collisionStates.add(true);
                    }
                }
                else
                    killMissile();
                m_bUnknown185 = true;
                return;
            }
        }
    }
    for (unsigned int i = 0; i < 2; ++i)
        if (m_particles[i])
        {
            Ogre::Vector3 particlePosition = getPosition(true);
            particlePosition.y -= m_fUnknown16C;
            m_particles[i]->setPosition(particlePosition);
            m_particles[i]->Start();
        }
    m_bUnknown185 = true;
}
