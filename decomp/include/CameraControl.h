#ifndef CAMERACONTROL_H
#define CAMERACONTROL_H
#include "RunicCore.h"

// Partial: allocation size 0xa0 at 0x56173f; only cinematic control used.
class CCameraControl : public CRunicCore
{
public:
    virtual ~CCameraControl();
    static CCameraControl* getSingleton();
    void setCinematicMode(bool enabled);
private:
    unsigned char m_CameraControlData[0xa0 - 0x10];
};
#endif
