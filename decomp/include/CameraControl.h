#ifndef CAMERACONTROL_H
#define CAMERACONTROL_H

// Partial: generated layout; field names are placeholders until named from the code that uses them.

#include <OgreCamera.h>
#include <OgreVector3.h>
#include "GameEnums.h"
#include "ResourceManager.h"
#include "RunicCore.h"
#include "Settings.h"
#include "SafePointer.h"
#include "TArrayList.h"
class CKeyManager;
class CMouseManager;
class CCameraShake;

class CCameraControl : public CRunicCore
{
public:
    void addCameraShake(CCameraShake*, bool);
    virtual ~CCameraControl();
    float getMaxDistanceToDolly();
    float getDefaultDistanceToDolly();
    static CCameraControl* getSingleton();
    void setAspectRatio(ECAMERAS, float, float);
    void setCinematicMode(bool);
    void updateGameCamera(float, CResourceManager*, Ogre::Vector3, ECAMERA_STATES);
    long long processInput(void*, CSettings*, CKeyManager*, CMouseManager*, float, bool);
    void clearCameraShakes();
    CCameraControl(Ogre::Camera*, Ogre::Camera*, Ogre::Camera*, Ogre::Camera*, Ogre::Camera*);

    // fields
    union
    {
        Ogre::Camera* m_cameras[5];
        struct
        {
            Ogre::Camera* m_pUnknown10;
            Ogre::Camera* m_pUnknown18;
            Ogre::Camera* m_pUnknown20;
            Ogre::Camera* m_pUnknown28;
            Ogre::Camera* m_pUnknown30;
        };
    };
    float m_fUnknown38;
    float m_fUnknown3C;
    float m_fUnknown40;
    float m_fUnknown44;
    float m_fUnknown48;
    float m_fUnknown4C;
    float m_fUnknown50;
    float m_fUnknown54;
    TArrayList<TSafePointer<CCameraShake>*> m_cameraShakes;
    TArrayList<TSafePointer<CCameraShake>*> m_cameraShakesSecondary;
    bool m_bUnknown88;
    unsigned char m_gap89[0x3];
    float m_fUnknown8C;
    bool m_bUnknown90;
    unsigned char m_gap91[0x3];
    float m_fUnknown94;
    bool m_bUnknown98;
};

#endif
