#ifndef POV_H
#define POV_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include <OgreMatrix4.h>
#include <OgreVector3.h>
#include "RunicCore.h"
#include "Settings.h"

class CPOV : public CRunicCore
{
public:
    virtual ~CPOV();
    void ExtractOrientationVectors();
    void DampContactVelocity(float);
    void DampLateralVelocity(float);
    void AccelerateUpDown(float);
    void Accelerate(float);
    void AccelerateX(float);
    void FlyTo(Ogre::Vector3, Ogre::Vector3);
    long long UpdateFlyingTo(float);
    void CapContactVelocity(float);
    void DeactivateMouse();
    void UpdateMouseInput(void*, float);
    CPOV(CSettings&);
    void UpdateInputs(float);
    void Update(float, float);
    void ResetPOV(bool, float, float);
    void SetOrientation(const Ogre::Matrix4&);
    void SetViewOrientation(const Ogre::Matrix4&);

    // fields
    long long m_Unknown10;
    unsigned char m_fUnknown18[0x8] __attribute__((aligned(8)));
    unsigned char m_fUnknown20[0x8] __attribute__((aligned(8)));
    unsigned char m_fUnknown28[0x8] __attribute__((aligned(8)));
    unsigned char m_fUnknown30[0x8] __attribute__((aligned(8)));
    unsigned char m_fUnknown38[0x8] __attribute__((aligned(8)));
    unsigned char m_fUnknown40[0x8] __attribute__((aligned(8)));
    long long m_iUnknown48;
    long long m_iUnknown50;
    long long m_iUnknown58;
    long long m_iUnknown60;
    long long m_iUnknown68;
    long long m_iUnknown70;
    long long m_iUnknown78;
    long long m_iUnknown80;
    long long m_iUnknown88;
    long long m_iUnknown90;
    unsigned char m_gap98[0x40] __attribute__((aligned(8)));
    float m_fUnknownD8;
    float m_fUnknownDC;
    float m_fUnknownE0;
    unsigned char m_gapE4[0xc] __attribute__((aligned(4)));
    float m_fUnknownF0;
    float m_fUnknownF4;
    float m_fUnknownF8;
    float m_fUnknownFC;
    float m_fUnknown100;
    float m_fUnknown104;
    float m_fUnknown108;
    float m_fUnknown10C;
    float m_fUnknown110;
    int m_iUnknown114;
    int m_iUnknown118;
    int m_iUnknown11C;
    int m_iUnknown120;
    float m_fUnknown124;
    int m_iUnknown128;
    int m_iUnknown12C;
    int m_iUnknown130;
    int m_iUnknown134;
    float m_fUnknown138;
    float m_fUnknown13C;
    float m_fUnknown140;
    float m_fUnknown144;
    bool m_bUnknown148;
    bool m_bUnknown149;
    bool m_bUnknown14A;
    bool m_bUnknown14B;
    bool m_bUnknown14C;
    bool m_bUnknown14D;
    bool m_bUnknown14E;
    unsigned char m_gap14F[0x1];
    float m_fUnknown150;
    float m_fUnknown154;
    float m_fUnknown158;
    float m_fUnknown15C;
    float m_fUnknown160;
    float m_fUnknown164;
    long long m_iUnknown168;
    long long m_iUnknown170;
    bool m_bUnknown178;
    bool m_bUnknown179;
    unsigned char m_gap17A[0x2];
    float m_fUnknown17C;
    float m_fUnknown180;
    float m_fUnknown184;
    float m_fUnknown188;
    float m_fUnknown18C;
    float m_fUnknown190;
    unsigned char m_gap194[0x4] __attribute__((aligned(4)));
};

#endif
