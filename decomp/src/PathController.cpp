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

#include "StringUtilities.h"
#include <OgreUTFString.h>
void CPathController::setPathName(const std::wstring& name)
{
    m_pathName=name;
    for (unsigned int i=0;i<m_pathNodes.size();++i) {
        if (m_pathName.empty())
            m_pathNodes[i]->setText(L"Node _ "+STRINGS::GetValueAsWString(i));
        else
            m_pathNodes[i]->setText(Ogre::UTFString(m_pathName)+Ogre::UTFString(" _ ")+Ogre::UTFString(STRINGS::GetValueAsWString(i)));
    }
}


CPathController::CPathController(CResourceManager* resources)
    : CPositionableObject(resources,NULL), m_pUnitInteractDataGroup(NULL), m_units(5),
      m_pCategory(gRESOURCE_GROUP_NAMES[1]), m_bVisible(false), m_bUnknown131(false),
      m_bUnknown132(false), m_bEnabled(true), m_bUnitRunsOnPath(true),
      m_bWalkToPlayer(false), m_bUnknown136(false), m_bUnknown137(false),
      m_pathNodes(10), m_pathCoordinates(21), m_pathDistances(10), m_fUnknown180(0),
      m_pathName(EMPTY_WSTRING), m_iNumberOfPathPoints(0), m_bEnableUnitOnStart(false)
{
}

CPathController::~CPathController()
{
    m_pathNodes.clear();
    for (unsigned int i=0;i<m_units.size();++i) {
        OGRE_DELETE_T(m_units[i],TSafePointer<CCharacter>,Ogre::MEMCATEGORY_GENERAL);
        m_units[i]=NULL;
    }
    m_units.clear();
    m_pUnitInteractDataGroup=NULL;
}


#include "Editor.h"
#include "EditorObjectManager.h"
void CPathController::setNumberOfPathPoints(unsigned int count)
{
    if (count>100) count=100;
    if (static_cast<unsigned int>(m_iNumberOfPathPoints)==count) return;
    m_iNumberOfPathPoints=count;
    if (!m_pResourceManager->getEditorIsRunning()) return;
    while (count<m_pathNodes.size()) {
        gEditor->getObjectManager()->EditorObjectDeleted(m_pathNodes[0]);
        delete m_pathNodes[0];
        m_pathNodes[0]=NULL;
        m_pathNodes.removeAt(0);
    }
    while (count>m_pathNodes.size()) {
        CPathNode* node=dynamic_cast<CPathNode*>(getSceneOwner()->CreateObjectByDescriptor(L"Path Node",true));
        if (node) {
            m_pathNodes.add(node);
            gEditor->getObjectManager()->EditorObjectCreated(node);
            gEditor->getObjectManager()->EditorObjectSelected(node);
            node->setPosition(getPosition(false));
            node->m_pPathController=this;
        }
    }
    setPathName(m_pathName);
}


#include "Level.h"
void CPathController::setEnabled(bool enabled)
{
    if (enabled==m_bEnabled) return;
    m_bEnabled=enabled;
    BroadcastEvent(enabled?6:7);
    if (!m_units.size()) {
        if (m_bUnknown137) {
            CPlayer*player=m_pResourceManager->getGameClient()->getPlayer();
            if (!player) return;
            player->setAIState(AISTATE_IDLE);
            TSafePointer<CCharacter>*safe=OGRE_NEW_T(TSafePointer<CCharacter>,Ogre::MEMCATEGORY_GENERAL)();
            safe->setObject(player);
            m_units.add(safe);
        } else {
            TArrayList<CBaseUnit*>units(100);
            m_pResourceManager->getLevel()->getBaseUnitsByDataGroup(m_pUnitInteractDataGroup,units);
            for (unsigned int i=0;i<units.size();++i) {
                CCharacter*unit=dynamic_cast<CCharacter*>(units[i]);
                if (unit) {
                    TSafePointer<CCharacter>*safe=OGRE_NEW_T(TSafePointer<CCharacter>,Ogre::MEMCATEGORY_GENERAL)();
                    safe->setObject(unit);
                    m_units.add(safe);
                }
            }
        }
    }
    for (unsigned int i=0;i<m_units.size();++i) {
        TSafePointer<CCharacter>*safe=m_units[i];
        if (enabled) {
            caculateSpline();
            m_bUnknown136=false;
            if (m_bWalkToPlayer) {
                setPosition(safe->getObject()->getPosition(true));
                safe->getObject()->setTarget(m_pResourceManager->getGameClient()->getPlayer());
            } else safe->getObject()->setTarget(NULL);
            safe->getObject()->stopPathing();
            safe->getObject()->setTargetItem(NULL);
            safe->getObject()->setPathToFollow(this);
            safe->getObject()->setAIState(AISTATE_IDLE);
        } else if (safe->getObject() && safe->getObject()->m_pathToFollow.getObject()==this)
            safe->getObject()->setPathToFollow(NULL);
        if (m_bEnableUnitOnStart) safe->getObject()->setEnabled(true);
    }
}
