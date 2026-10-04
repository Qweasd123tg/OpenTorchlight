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
    if (!m_pRunicCore)
        return false;

    m_fElapsedTime = std::min(m_fElapsedTime + fDeltaTime, m_fDuration);

    float fElapsedTimeRatio = m_fElapsedTime / m_fDuration;
    float fMagnitude = reinterpret_cast<CGraph*>(m_pRunicCore)->getValue(
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
      m_fDirectionZ(0.0f), m_pRunicCore(NULL),
      m_nRunicCoreSafePointerIndex(-1), m_strCameraShakeName(EMPTY_WSTRING),
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
        m_bCameraShakeActive = pCameraShake->m_bCameraShakeActive;
        m_bCameraFallsOffWithDistance = pCameraShake->m_bCameraFallsOffWithDistance;
        m_fDuration = pCameraShake->m_fDuration;
        setCameraShakeName(m_strCameraShakeName);
    }
}
