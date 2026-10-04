#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "PathController.h"
#include "BaseUnit.h"
#include "GameClient.h"
#include "Player.h"
#include "PositionableObject.h"
#include "UnitResourceList.h"
#include "CollisionList.h"
#include "CollisionModel.h"
#include "OgreUtilities.h"
#include "ResourceManager.h"
#include "SceneNodeObject.h"
#include "SoundBank.h"
#include "UtilitiesMath.h"
#include "TArrayList.h"
#include "SafePointer.h"

void CPathController::setVisible(bool visible)
{
    m_bVisible = visible;

    TArrayList<CPositionableObject*>& objects =
        *reinterpret_cast<TArrayList<CPositionableObject*>*>(m_Unknown138);

    for (unsigned int i = 0; i < objects.size(); ++i)
        objects[i]->setVisible(visible);
}

float CPathController::getClosestPctOfPath(const Ogre::Vector3& point)
{
    TArrayList<float>& vectors = reinterpret_cast<TArrayList<float>&>(m_Unknown150);
    TArrayList<float>& pathLengths = reinterpret_cast<TArrayList<float>&>(m_Unknown168);

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
        sqrtf(distance);
    }

    return pathLengths[0] / m_fUnknown180;
}

float CPathController::caculatePointInFrontOfPlayer(CBaseUnit* unit)
{
    Ogre::Vector3 position = getPosition(true);
    float resultX = position.x;
    volatile float resultY = position.y;

    if (getResourceManager()->getGameClientCount() != 0)
    {
        CGameClient* gameClient = getResourceManager()->getGameClient(0);
        if (gameClient != NULL)
        {
            CPlayer* player = *reinterpret_cast<CPlayer**>(
                reinterpret_cast<unsigned char*>(gameClient) + 0x58);

            if (player != NULL)
            {
                Ogre::Vector3 playerPosition = player->getPosition(true);
                float dx = position.x - playerPosition.x;
                float dy = position.y - playerPosition.y;
                volatile float squaredX = dx * dx;
                volatile float distance = squaredX + 1.0f;
                distance = distance + dy * dy;
                float actualDistance = distance;

                if (actualDistance > 1e-8)
                {
                    float inverseDistance = 1.0f / actualDistance;
                    dx *= inverseDistance;
                    dy *= inverseDistance;
                }

                if (getResourceManager()->getGameClientCount() != 0)
                {
                    CGameClient* currentGameClient = getResourceManager()->getGameClient(0);
                    CPlayer* currentPlayer = *reinterpret_cast<CPlayer**>(
                        reinterpret_cast<unsigned char*>(currentGameClient) + 0x58);

                    float playerRadius = *reinterpret_cast<const float*>(
                        reinterpret_cast<const unsigned char*>(currentPlayer) + 0x194);
                    float unitRadius = *reinterpret_cast<const float*>(
                        reinterpret_cast<const unsigned char*>(unit) + 0x194);
                    float offset = (playerRadius + unitRadius) * 2.0f;

                    resultX = playerPosition.x + dx * offset;
                    resultY = playerPosition.y + dy * offset;
                }
            }
        }
    }

    return resultX;
}

long long CPathController::getNextPointAtPercent(float percent, CBaseUnit* unit, bool flag)
{
    Ogre::Vector3 point;

    if (m_bWalkToPlayer)
    {
        point = caculatePointInFrontOfPlayer(unit);
    }
    else
    {
        TArrayList<float>& vectors =
            *reinterpret_cast<TArrayList<float>*>(&m_Unknown150[0]);
        TArrayList<float>& percentages =
            *reinterpret_cast<TArrayList<float>*>(&m_Unknown168[0]);
        unsigned int index;
        float value;

        percent = percent > 0.0f ? std::min(percent, 1.0f) : 0.0f;
        point = getPosition(true);

        if (flag)
        {
            index = 0;
            while (index < percentages.size())
            {
                value = percentages[index];
                if (m_fUnknown180 != 0.0f)
                    value /= m_fUnknown180;

                if (percent <= value)
                    break;

                ++index;
            }

            if (index == percentages.size())
            {
                if (vectors.size() > 2)
                {
                    point.x += vectors[0];
                    point.y += vectors[1];
                    point.z += vectors[2];
                }
                else
                {
                    point.z += vectors[0];
                    if (vectors.size() == 2)
                        point.z += vectors[1];
                    point.x += vectors[0];
                    point.y += vectors[0];
                }
            }
            else
            {
                point.x += vectors[index * 3];
                point.y += vectors[index * 3 + 1];
                point.z += vectors[index * 3 + 2];
            }
        }
        else
        {
            index = percentages.size() - 1;

            for (;;)
            {
                value = percentages[index];
                if (m_fUnknown180 != 0.0f)
                    value /= m_fUnknown180;

                if (percent >= value)
                    break;

                --index;
            }

            point.x += vectors[index * 3];
            point.y += vectors[index * 3 + 1];
            point.z += vectors[index * 3 + 2];
        }
    }

    long long result;
    std::memcpy(&result, &point, sizeof(result));
    return result;
}

void CPathController::childNodeMoved()
{
    TArrayList<CPositionableObject*>& nodes =
        *reinterpret_cast<TArrayList<CPositionableObject*>*>(&m_Unknown138);

    if (nodes.size() != 0 && nodes[0] != 0)
        setPosition(nodes[0]->getPosition(true));
}

void CPathController::positionUpdated(const Ogre::Vector3& position)
{
    if (*reinterpret_cast<int*>(m_Unknown138 + 8) != 0)
    {
        CPositionableObject* object =
            *reinterpret_cast<CPositionableObject**>(&m_Unknown138);

        if (object->getPosition(false) != position)
        {
            CPathController** controller = reinterpret_cast<CPathController**>(
                reinterpret_cast<unsigned char*>(object) + 0x100);

            *controller = 0;
            object->setPosition(position);
            *controller = this;
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

    typedef TArrayList<CPathController *> TSafePointerList;
    TSafePointerList &safePointers =
        reinterpret_cast<TSafePointerList &>(m_Unknown108);

    struct SafePointerLayout
    {
        CPathController *pObject;
        unsigned int index;
    };

    for (unsigned int i = 0; i < safePointers.size(); ++i)
    {
        TSafePointer<void *> *pointer =
            reinterpret_cast<TSafePointer<void *> *>(safePointers[i]);

        if (pointer != NULL)
        {
            SafePointerLayout *layout =
                reinterpret_cast<SafePointerLayout *>(pointer);

            if (layout->pObject != NULL)
                layout->pObject->removeSafePointer(pointer, layout->index);

            layout->pObject = NULL;
            layout->index = 0xFFFFFFFF;
            Ogre::NedAllocImpl::deallocBytes(pointer);
        }
    }

    safePointers.clear();
}

void CPathController::caculateSpline()
{
    m_fUnknown180 = 0.0f;

    if (m_bWalkToPlayer || getSceneOwner() == NULL ||
        m_pResourceManager->getEditorIsRunning())
        return;

    TArrayList<float>& vectors =
        *reinterpret_cast<TArrayList<float>*>(&m_Unknown150);
    TArrayList<float>& spline =
        *reinterpret_cast<TArrayList<float>*>(&m_Unknown168);

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
                (z - previousZ) * (z - previousZ) +
                (y - previousY) * (y - previousY));
        }

        spline.add(m_fUnknown180);

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
