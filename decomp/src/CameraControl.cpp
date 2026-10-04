#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "GameNamespaces.h"
#include "CameraControl.h"
#include "KeyManager.h"
#include "MouseManager.h"
#include "RunicCore.h"
#include "Settings.h"
#include "BaseUnit.h"
#include "CollisionModel.h"
#include "OgreUtilities.h"
#include "ResourceManager.h"
#include "SceneNodeObject.h"
#include "SoundBank.h"
#include "UtilitiesMath.h"

float CCameraControl::getMaxDistanceToDolly()
{
    return m_fUnknown8C * 28.5f;
}

float CCameraControl::getDefaultDistanceToDolly()
{
    return m_fUnknown8C * 28.5f;
}

CCameraControl* CCameraControl::getSingleton()
{
    return static_cast<CCameraControl*>(g_pCameraControl);
}

void CCameraControl::setCinematicMode(bool cinematicMode)
{
    if (m_bUnknown98 == cinematicMode) {
        return;
    }

    if (cinematicMode) {
        m_fUnknown94 = m_fUnknown38;
        m_fUnknown38 = 28.5f;
        if (m_fUnknown38 > m_fUnknown8C * 28.5f) {
            m_fUnknown38 = m_fUnknown8C * 28.5f;
        }
    } else {
        m_fUnknown38 = m_fUnknown94;
        if (m_fUnknown38 < 14.0f) {
            m_fUnknown38 = 14.0f;
        } else if (m_fUnknown38 > m_fUnknown8C * 28.5f) {
            m_fUnknown38 = m_fUnknown8C * 28.5f;
        }
    }

    m_bUnknown98 = cinematicMode;
}

long long CCameraControl::processInput(void* pUnused, CSettings* pSettings,
    CKeyManager* pKeyManager, CMouseManager* pMouseManager, float fUnused, bool bUnused)
{
    if (pMouseManager != 0 && m_bUnknown90 && !m_bUnknown98)
    {
        float fZoom = -0.01f * float(
            *reinterpret_cast<int*>(reinterpret_cast<char*>(pMouseManager) + 0x48));
        if (pKeyManager->keyPressed(pSettings->GetInt(KSETTINGS_KEYMAP_ZOOMIN)))
            fZoom -= 1.0f;
        else if (pKeyManager->keyPressed(pSettings->GetInt(KSETTINGS_KEYMAP_ZOOMOUT)))
            fZoom += 1.0f;

        fZoom += m_fUnknown38;
        m_fUnknown38 = fZoom;

        if (fZoom < 14.0f)
        {
            m_fUnknown38 = 14.0f;
        }
        else
        {
            float fMaxZoom = 28.5f * m_fUnknown8C;
            if (fMaxZoom < fZoom)
                m_fUnknown38 = fMaxZoom;
        }

        if (pMouseManager->buttonPressed(static_cast<EMouseButton>(2)))
            m_fUnknown38 = 28.5f * m_fUnknown8C;
    }

    return 1;
}

CCameraControl::CCameraControl(Ogre::Camera* camera1, Ogre::Camera* camera2,
                               Ogre::Camera* camera3, Ogre::Camera* camera4,
                               Ogre::Camera* camera5)
    : CRunicCore()
{
    *reinterpret_cast<long long*>(reinterpret_cast<char*>(this) + 0x58) = 0;
    m_fUnknown3C = 0.0f;
    m_fUnknown40 = 0.0f;
    m_fUnknown44 = 0.0f;
    m_fUnknown48 = 0.0f;
    m_fUnknown4C = 0.0f;
    m_fUnknown50 = 0.0f;
    m_fUnknown54 = 0.0f;

    *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x60) = 0;
    *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x64) = 0;
    *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x68) = 5;

    *reinterpret_cast<long long*>(reinterpret_cast<char*>(this) + 0x70) = 0;
    *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x78) = 0;
    *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x7c) = 0;
    *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x80) = 5;

    m_bUnknown88 = true;
    m_fUnknown8C = 1.0f;
    m_bUnknown90 = true;
    m_bUnknown98 = false;
    m_fUnknown38 = 28.5f;

    g_pCameraControl = this;

    m_pUnknown10 = camera1;
    m_pUnknown18 = camera2;
    m_pUnknown20 = camera3;
    m_pUnknown28 = camera4;
    m_pUnknown30 = camera5;
}
