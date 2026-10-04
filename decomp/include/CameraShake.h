#ifndef CAMERASHAKE_H
#define CAMERASHAKE_H

#include <string>

#include "EditorBaseObject.h"

class CRunicCore;

class CCameraShake : public CEditorBaseObject
{
public:
    virtual ~CCameraShake();

    bool update(float fDeltaTime, Ogre::Vector3& cameraPosition,
                Ogre::Vector3& shakeOffset, bool applyShake);
    CCameraShake();
    void setCameraShakeName(const std::wstring& cameraShakeName);
    void clone(CCameraShake* pCameraShake);
    CCameraShake(const std::wstring& cameraShakeName,
                 Ogre::Vector3 direction, float duration);
    void startCameraShake(const Ogre::Vector3& cameraPosition,
                          bool updateCamera);

    float m_fDuration;
    float m_fElapsedTime;
    float m_fMagnitudeMultiplier;
    float m_fDirectionX;
    float m_fDirectionY;
    float m_fDirectionZ;
    CRunicCore* m_pRunicCore;
    int m_nRunicCoreSafePointerIndex;
    unsigned char m_gap7C[4] __attribute__((aligned(4)));
    std::wstring m_strCameraShakeName;
    int m_nDirectionOrientation;
    float m_fCameraPositionX;
    float m_fCameraPositionY;
    float m_fCameraPositionZ;
    bool m_bCameraShakeActive;
    bool m_bCameraFallsOffWithDistance;

public:
    // Inline accessors behind the descriptors' property functions.
    void setDuration(float value) { m_fDuration = value; }
    void setMagnitudeMult(float value) { m_fMagnitudeMultiplier = value; }
    void setCameraFallsOffWithDistance(bool value) { m_bCameraFallsOffWithDistance = value; }
    bool getCameraFallsOffWithDistance() const { return m_bCameraFallsOffWithDistance; }
    float getMagnitudeMult() const { return m_fMagnitudeMultiplier; }
    float getDuration() const { return m_fDuration; }
};

#endif
