#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include <string>
#include "PositionableObject.h"
#include "ResourceManager.h"
#include "RunicCore.h"

class CCameraController : public CPositionableObject
{
public:
    virtual ~CCameraController();
    void stopCamera();
    void update(float);
    void setUnitInteractWith(std::wstring);
    void configureUnit();
    void startCamera();
    void configureUnitsInLevel();
    CCameraController(CResourceManager*);

    // fields
    CResourceManager* m_pResourceManager;
    void* m_pCategory;
    std::wstring m_sUnitInteractWith;
    long long m_iUnknown118;
    CRunicCore* m_pRunicCore;
    int m_iUnknown128;
    unsigned char m_gap12C[0x4] __attribute__((aligned(4)));
    float m_fUnknown130;
    float m_fUnknown134;
    float m_fUnknown138;
    float m_fUnknown13C;
    float m_fUnknown140;
    float m_fUnknown144;
    float m_fCameraPanTime;
    float m_fUnknown14C;
    float m_fCameraEaseInPCT;
    float m_fCameraEaseInDistancePCT;
    float m_fCameraPauseTimer;
    float m_fUnknown15C;
    bool m_bUnknown160;
    bool m_bRestoreCameraStateAfterMoving;
    bool m_bFollowUnit;
    bool m_bUnknown163;
    unsigned char m_gap164[0x4] __attribute__((aligned(4)));
    long long m_Unknown168;
    unsigned char m_gap170[0x50] __attribute__((aligned(8)));
    int m_iCameraType;
};

#endif
