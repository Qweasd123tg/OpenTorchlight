#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "PathController.h"
#include "PathNode.h"
#include "Character.h"
#include "BaseUnit.h"
#include "GameClient.h"
#include "Player.h"
#include "PositionableObject.h"
#include "UnitResourceList.h"
#include "CollisionList.h"
#include "CollisionModel.h"
#include "OgreUtilities.h"
#include "ResourceManager.h"
#include "EditorScene.h"
#include "SceneNodeObject.h"
#include "SoundBank.h"
#include "UtilitiesMath.h"
#include "TArrayList.h"
#include "SafePointer.h"

void CPathController::setVisible(bool visible)
{
    m_bVisible = visible;

    TArrayList<CPathNode*>& objects = m_pathNodes;

    for (unsigned int i = 0; i < objects.size(); ++i)
        objects[i]->setVisible(visible);
}

float CPathController::getClosestPctOfPath(const Ogre::Vector3& point)
{
    TArrayList<float>& vectors = m_pathCoordinates;
    TArrayList<float>& pathLengths = m_pathDistances;

    if (m_bWalkToPlayer || vectors.size() == 1 || m_fUnknown180 == 0.0f)
    {
        return 1.0f;
    }

    for (unsigned int i = 0; i < vectors.size(); i += 3)
    {
        float distance =
            (vectors[i] - point.x) * (vectors[i] - point.x) +
            (vectors[i + 1] - point.y) * (vectors[i + 1] - point.y) +
            (vectors[i + 2] - point.z) * (vectors[i + 2] - point.z);
        if (0.0f > distance) sqrtf(distance);
    }

    return pathLengths[0] / m_fUnknown180;
}

void CPathController::childNodeMoved()
{
    TArrayList<CPathNode*>& nodes = m_pathNodes;

    if (nodes.size() != 0 && nodes[0] != 0)
        CPositionableObject::setPosition(nodes[0]->getPosition(true));
}

void CPathController::positionUpdated(const Ogre::Vector3& position)
{
    if (m_pathNodes.size() != 0)
    {
        if (m_pathNodes[0]->getPosition(false) != position)
        {
            m_pathNodes[0]->m_pPathController = 0;
            m_pathNodes[0]->CPositionableObject::setPosition(position);
            m_pathNodes[0]->m_pPathController = this;
        }
    }
}

void CPathController::setUnitInteractWith(std::wstring unitInteractWith)
{
    if (m_pResourceManager == NULL)
        return;

    m_sUnitInteractWith = unitInteractWith;

    if (m_sUnitInteractWith.compare(L"PLAYER") == 0)
    {
        m_pUnitInteractDataGroup = NULL;
        m_bUnknown137 = true;
    }
    else
    {
        m_pUnitInteractDataGroup = CUnitResourceList::getSingleton()->getDataGroupByObjectName(unitInteractWith);
        m_bUnknown137 = false;
    }

    for (unsigned int i = 0; i < m_units.size(); ++i) {
        OGRE_DELETE_T(m_units[i], TSafePointer<CCharacter>, Ogre::MEMCATEGORY_GENERAL);
        m_units[i] = NULL;
    }
    m_units.clear();
}

void CPathController::caculateSpline()
{
    m_fUnknown180 = 0.0f;

    if (m_bWalkToPlayer || getSceneOwner() == NULL ||
        m_pResourceManager->getEditorIsRunning())
        return;

    TArrayList<float>& vectors =
        m_pathCoordinates;
    TArrayList<float>& spline =
        m_pathDistances;

    spline.clear();

    float previousX;
    float previousY;
    float previousZ;

    for (unsigned int i = 0; i < vectors.size(); i += 3)
    {
        float x = vectors[i];
        float y = vectors[i + 1];
        float z = vectors[i + 2];

        if (i != 0)
        {
            m_fUnknown180 += sqrtf(
                (x - previousX) * (x - previousX) +
                (y - previousY) * (y - previousY) +
                (z - previousZ) * (z - previousZ));
            spline.add(m_fUnknown180);
        }
        else
            spline.add(0.0f);

        previousX = x;
        previousY = y;
        previousZ = z;
    }
}

void CPathController::initPathController()
{
    if (m_pResourceManager->getEditorIsRunning())
        return;

    caculateSpline();
    if (m_bEnabled)
    {
        m_bEnabled = false;
        setEnabled(true);
    }
}

void CPathController::initObjectInEditor()
{
    if (!m_pResourceManager->getEditorIsRunning())
        return;

    setVisible(true);

    float points[3] = { 0.0f };
    points[0] = getPosition(false).x;
    points[1] = getPosition(false).y;
    points[2] = getPosition(false).z;

    setArrayOfVectors(points, 3);
    m_bUnknown132 = true;
}

Ogre::Vector3 CPathController::caculatePointInFrontOfPlayer(CBaseUnit* unit)
{
    Ogre::Vector3 position = getPosition(true);
    CGameClient* client = m_pResourceManager->getGameClient();
    if (client && client->getPlayer()) {
        Ogre::Vector3 playerPosition = client->getPlayer()->getPosition(true);
        Ogre::Vector3 direction(position.x - playerPosition.x, 0.0f, position.z - playerPosition.z);
        direction.normalise();
        float distance = (m_pResourceManager->getGameClient()->getPlayer()->m_fBaseUnitValue194 + unit->m_fBaseUnitValue194) * 2.0f;
        position.x = playerPosition.x + direction.x * distance;
        position.z = playerPosition.z + direction.z * distance;
    }
    return Ogre::Vector3(position.x, 0.0f, position.z);
}

Ogre::Vector3 CPathController::getNextPointAtPercent(float percent, CBaseUnit* unit, bool forward)
{
    if (m_bWalkToPlayer)
        return caculatePointInFrontOfPlayer(unit);
    if (percent > 0.0f) {
        if (!(percent < 1.0f)) percent = 1.0f;
    } else percent = 0.0f;
    Ogre::Vector3 parentPosition = getSceneOwner()->getPosition(true);
    unsigned int point = 0;
    if (forward) {
        for (unsigned int i = 0; i < m_pathDistances.size(); ++i) {
            float distance = m_pathDistances[i];
            if (m_fUnknown180 != 0.0f) distance /= m_fUnknown180;
            if (distance >= percent) { point = i; break; }
        }
    } else {
        unsigned int i = m_pathDistances.size() - 1;
        for (;;) {
            float distance = m_pathDistances[i];
            if (m_fUnknown180 != 0.0f) distance /= m_fUnknown180;
            if (percent >= distance) { point = i; break; }
            --i;
        }
    }
    return Ogre::Vector3(m_pathCoordinates[point*3] + parentPosition.x,
                         m_pathCoordinates[point*3+1] + parentPosition.y,
                         m_pathCoordinates[point*3+2] + parentPosition.z);
}

float* CPathController::getArrayOfVectors(unsigned int& count)
{
    if (m_pResourceManager->getEditorIsRunning()) {
        m_pathCoordinates.clear();
        for (unsigned int i = 0; i < m_pathNodes.size(); ++i) {
            m_pathCoordinates.add(m_pathNodes[i]->getPosition(false).x);
            m_pathCoordinates.add(m_pathNodes[i]->getPosition(false).y);
            m_pathCoordinates.add(m_pathNodes[i]->getPosition(false).z);
        }
    }
    count = m_pathCoordinates.size();
    return &m_pathCoordinates[0];
}

void CPathController::setArrayOfVectors(const float* values, unsigned int count)
{
    m_pathCoordinates.clear();
    if (values)
        for (unsigned int i = 0; i < count; ++i)
            m_pathCoordinates.add(values[i]);
    setNumberOfPathPoints(count / 3);
    if (m_pResourceManager->getEditorIsRunning() && getSceneOwner()) {
        for (unsigned int i = 0; i < count; i += 3) {
            if (i + 2 < count) {
                unsigned int point = i / 3;
                m_pathNodes[point]->m_pPathController = 0;
                m_pathNodes[point]->setPosition(m_pathCoordinates[i], m_pathCoordinates[i+1], m_pathCoordinates[i+2]);
                m_pathNodes[point]->m_pPathController = this;
            }
        }
        setVisible(m_bVisible);
    }
}
