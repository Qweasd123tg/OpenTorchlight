#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "GameNamespaces.h"
#include "CameraShake.h"
#include "EditorBaseObject.h"
#include "Graph.h"
#include "BaseUnit.h"
#include "CollisionModel.h"
#include "OgreUtilities.h"
#include "ResourceManager.h"
#include "SceneNodeObject.h"
#include "SoundBank.h"
#include "UtilitiesMath.h"

bool CCameraShake::update(float fDeltaTime, Ogre::Vector3& cameraPosition,
                          Ogre::Vector3& shakeOffset, bool applyShake)
{
    if (!m_graph.getObject())
        return false;

    m_fElapsedTime = std::min(m_fElapsedTime + fDeltaTime, m_fDuration);

    float fElapsedTimeRatio = m_fElapsedTime / m_fDuration;
    float fMagnitude = m_graph.getObject()->getValue(
        fElapsedTimeRatio, 0);
    fMagnitude *= m_fMagnitudeMultiplier;

    float fDistanceMultiplier = 1.0f;
    if (m_bCameraShakeActive && m_bCameraFallsOffWithDistance)
    {
        m_fCameraPositionY = cameraPosition.y;
        Ogre::Vector3 cameraDistance(
            cameraPosition.x - m_fCameraPositionX,
            cameraPosition.y - m_fCameraPositionY,
            cameraPosition.z - m_fCameraPositionZ);
        float fCameraDistance = cameraDistance.length();

        if (fCameraDistance >= 2.0f)
        {
            float fDistanceScale = (fCameraDistance - 2.0f) / 10.0f;
            if (fDistanceScale < 1.0f)
            {
                fDistanceMultiplier = 1.0f - fDistanceScale;
                if (fDistanceMultiplier < 1.0f)
                    fDistanceMultiplier = 1.0f;
            }
            else
            {
                fDistanceMultiplier = 0.0f;
            }
        }
    }

    if (applyShake)
    {
        shakeOffset += Ogre::Vector3(m_fDirectionX, m_fDirectionY,
                                      m_fDirectionZ)
                      * fMagnitude * fDistanceMultiplier;
    }

    if (shakeOffset.length() > 3.5f)
    {
        shakeOffset.normalise();
        shakeOffset *= 3.5f;
    }

    if (fElapsedTimeRatio >= 1.0f)
    {
        m_fElapsedTime = 0.0f;
        return false;
    }

    return true;
}

CCameraShake::CCameraShake()
    : CEditorBaseObject(), m_fDuration(0.5f), m_fElapsedTime(0.0f),
      m_fMagnitudeMultiplier(1.0f), m_fDirectionX(0.0f), m_fDirectionY(1.0f),
      m_fDirectionZ(0.0f), m_graph(), m_strCameraShakeName(EMPTY_WSTRING),
      m_nDirectionOrientation(0), m_fCameraPositionX(0.0f),
      m_fCameraPositionY(0.0f), m_fCameraPositionZ(0.0f),
      m_bCameraShakeActive(false), m_bCameraFallsOffWithDistance(true)
{
}

void CCameraShake::clone(CCameraShake* pCameraShake)
{
    if (pCameraShake != NULL)
    {
        m_nDirectionOrientation = pCameraShake->m_nDirectionOrientation;
        m_fMagnitudeMultiplier = pCameraShake->m_fMagnitudeMultiplier;
        m_fDirectionX = pCameraShake->m_fDirectionX;
        m_fDirectionY = pCameraShake->m_fDirectionY;
        m_fDirectionZ = pCameraShake->m_fDirectionZ;
        m_strCameraShakeName = pCameraShake->m_strCameraShakeName;
        m_bCameraFallsOffWithDistance = pCameraShake->m_bCameraFallsOffWithDistance;
        m_bCameraShakeActive = pCameraShake->m_bCameraShakeActive;
        m_fDuration = pCameraShake->m_fDuration;
        setCameraShakeName(m_strCameraShakeName);
    }
}

#include "GraphManager.h"
#include "StringUtilities.h"
#include "CameraControl.h"

void CCameraShake::setCameraShakeName(const std::wstring& name)
{
    m_strCameraShakeName = STRINGS::StringUpper(name);
    m_graph.setObject(CGraphManager::getSingleton()->getGraph(m_strCameraShakeName));
}

CCameraShake::CCameraShake(const std::wstring& name,Ogre::Vector3 direction,float duration)
    : CEditorBaseObject(),m_fDuration(duration),m_fElapsedTime(0),m_fMagnitudeMultiplier(1),
      m_fDirectionX(direction.x),m_fDirectionY(direction.y),m_fDirectionZ(direction.z),m_graph(),
      m_strCameraShakeName(name),m_nDirectionOrientation(0),m_fCameraPositionX(0),m_fCameraPositionY(0),m_fCameraPositionZ(0),
      m_bCameraShakeActive(false),m_bCameraFallsOffWithDistance(true)
{
    setCameraShakeName(name);
}
CCameraShake::~CCameraShake()
{
    m_graph.setObject(NULL);
    m_strCameraShakeName=EMPTY_WSTRING;
}
void CCameraShake::startCameraShake(const Ogre::Vector3& position,bool updateCamera)
{
    m_fCameraPositionX=position.x;m_fCameraPositionY=position.y;m_fCameraPositionZ=position.z;
    m_bCameraShakeActive=true;
    CCameraControl* camera=CCameraControl::getSingleton();
    if (updateCamera) {
        TSafePointer<CCameraShake>* reference=OGRE_NEW_T(TSafePointer<CCameraShake>,Ogre::MEMCATEGORY_GENERAL)();
        reference->setObject(this);
        camera->m_cameraShakes.add(reference);
    } else {
        TSafePointer<CCameraShake>* reference=OGRE_NEW_T(TSafePointer<CCameraShake>,Ogre::MEMCATEGORY_GENERAL)();
        reference->setObject(this);
        camera->m_cameraShakesSecondary.add(reference);
    }
}
