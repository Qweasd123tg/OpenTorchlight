#include "EmptyStrings.h"
#include "GameEnums.h"
#include "GameVariables.h"
#include "GameNamespaces.h"
#include "POV.h"
#include "RunicCore.h"
#include "Settings.h"
#include "BaseUnit.h"
#include "CollisionModel.h"
#include "OgreUtilities.h"
#include "ResourceManager.h"
#include "SceneNodeObject.h"
#include "SoundBank.h"
#include "UtilitiesMath.h"

void CPOV::ExtractOrientationVectors()
{
    m_fUnknown108 = *reinterpret_cast<const float *>(&m_fUnknown18[0]);
    m_fUnknown110 = *reinterpret_cast<const float *>(&m_fUnknown38[0]);
    m_fUnknown10C = *reinterpret_cast<const float *>(&m_fUnknown28[0]);
    m_fUnknownF0 = *reinterpret_cast<const float *>(&m_fUnknown18[4]);
    m_fUnknownF4 = *reinterpret_cast<const float *>(&m_fUnknown28[4]);
    m_fUnknownF8 = *reinterpret_cast<const float *>(&m_fUnknown38[4]);
    m_fUnknownFC = *reinterpret_cast<const float *>(&m_fUnknown20[0]);
    m_fUnknown100 = *reinterpret_cast<const float *>(&m_fUnknown30[0]);
    m_fUnknown104 = *reinterpret_cast<const float *>(&m_fUnknown40[0]);
    m_iUnknown134 = *reinterpret_cast<const int *>(&m_iUnknown78);
    m_iUnknown12C = *reinterpret_cast<const int *>(&m_iUnknown58);
    m_iUnknown130 = *reinterpret_cast<const int *>(&m_iUnknown68);
    m_iUnknown114 = *reinterpret_cast<const int *>(
        reinterpret_cast<const unsigned char *>(&m_iUnknown58) + 4);
    m_iUnknown118 = *reinterpret_cast<const int *>(
        reinterpret_cast<const unsigned char *>(&m_iUnknown68) + 4);
    m_iUnknown11C = *reinterpret_cast<const int *>(
        reinterpret_cast<const unsigned char *>(&m_iUnknown78) + 4);
    m_iUnknown120 = *reinterpret_cast<const int *>(&m_iUnknown60);
    m_fUnknown124 = *reinterpret_cast<const float *>(&m_iUnknown70);
    m_iUnknown128 = *reinterpret_cast<const int *>(&m_iUnknown80);
}

void CPOV::DampContactVelocity(float param_1)
{
    float fVar1 = m_fUnknown138 * m_fUnknownF0 +
                  m_fUnknown13C * m_fUnknownF4 +
                  m_fUnknown140 * m_fUnknownF8;
    float fVar2 = m_fUnknownF8 * fVar1;
    float fVar3 = m_fUnknownF4 * fVar1;

    fVar1 = m_fUnknownF0 * fVar1;
    m_fUnknown140 = (m_fUnknown140 - fVar2) * param_1 + fVar2;
    m_fUnknown13C = (m_fUnknown13C - fVar3) * param_1 + fVar3;
    m_fUnknown138 = (m_fUnknown138 - fVar1) * param_1 + fVar1;
}

void CPOV::AccelerateUpDown(float fAmount)
{
    m_fUnknown140 = m_fUnknownF8 * fAmount + m_fUnknown140;
    m_fUnknown13C = m_fUnknownF4 * fAmount + m_fUnknown13C;
    m_fUnknown138 = fAmount * m_fUnknownF0 + m_fUnknown138;
}

void CPOV::Accelerate(float fUnknownValue)
{
    m_fUnknown140 = m_fUnknown104 * fUnknownValue + m_fUnknown140;
    m_fUnknown13C = m_fUnknown100 * fUnknownValue + m_fUnknown13C;
    m_fUnknown138 = m_fUnknownFC * fUnknownValue + m_fUnknown138;
}

void CPOV::AccelerateX(float acceleration)
{
    m_fUnknown140 = m_fUnknown110 * acceleration + m_fUnknown140;
    m_fUnknown13C = m_fUnknown10C * acceleration + m_fUnknown13C;
    m_fUnknown138 = m_fUnknown108 * acceleration + m_fUnknown138;
}

void CPOV::FlyTo(Ogre::Vector3 position, Ogre::Vector3 target)
{
    if (position == target)
        return;

    m_bUnknown179 = true;
    m_fUnknown17C = position.x;
    m_fUnknown180 = position.y;
    m_fUnknown184 = position.z;
    m_fUnknown188 = target.x;
    m_fUnknown18C = target.y;
    m_fUnknown190 = target.z;
}

long long CPOV::UpdateFlyingTo(float)
{
    if (!m_bUnknown179)
        return 0;

    float fDX = m_fUnknown180 - m_fUnknownDC;
    float fDY = m_fUnknown17C - m_fUnknownD8;
    float fDZ = m_fUnknown184 - m_fUnknownE0;
    float fDistance = sqrtf(fDX * fDX + fDY * fDY + fDZ * fDZ);

    if (fDistance >= 0.01f)
    {
        m_fUnknownDC = fDX * 0.8f + m_fUnknown180;
        m_fUnknownD8 = fDY * 0.8f + m_fUnknown17C;
        m_fUnknownE0 = fDZ * 0.8f + m_fUnknown184;
    }
    else
    {
        m_fUnknownDC = m_fUnknown180;
        m_fUnknownD8 = m_fUnknown17C;
        m_fUnknownE0 = m_fUnknown184;
    }

    return 1;
}

struct POINT
{
    long long x;
    long long y;
};

extern bool GetCursorPos(POINT *);

void CPOV::DeactivateMouse()
{
    POINT point;

    m_bUnknown14E = false;
    GetCursorPos(&point);
    m_iUnknown168 = point.x;
    m_iUnknown170 = point.y;
}

CPOV::~CPOV()
{
}

CPOV::CPOV(CSettings& settings)
    : CRunicCore()
{
    m_Unknown10 = reinterpret_cast<long long>(&settings);

    *reinterpret_cast<Ogre::Matrix4*>(&m_fUnknown18[0]) = Ogre::Matrix4::IDENTITY;
    *reinterpret_cast<Ogre::Matrix4*>(&m_iUnknown58) = Ogre::Matrix4::IDENTITY;

    m_fUnknownD8 = 0.0f;
    m_fUnknownDC = 0.0f;
    m_fUnknownE0 = 0.0f;
    m_fUnknownF0 = 0.0f;
    m_fUnknownF4 = 1.0f;
    m_fUnknownF8 = 0.0f;
    m_fUnknownFC = 0.0f;
    m_fUnknown100 = 0.0f;
    m_fUnknown104 = -1.0f;
    m_fUnknown108 = 1.0f;
    m_fUnknown10C = 0.0f;
    m_fUnknown110 = 0.0f;
    m_fUnknown138 = 0.0f;
    m_fUnknown13C = 0.0f;
    m_fUnknown140 = 0.0f;
    m_fUnknown144 = 1.0f;
    m_bUnknown148 = false;
    m_bUnknown149 = false;
    m_bUnknown14A = false;
    m_bUnknown14B = false;
    m_bUnknown14C = false;
    m_bUnknown14D = false;
    m_bUnknown14E = false;
    m_fUnknown150 = 0.0f;
    m_fUnknown154 = 0.0f;
    m_fUnknown158 = 0.0f;
    m_fUnknown15C = 0.0f;
    m_fUnknown160 = 0.0f;
    m_fUnknown164 = 0.0f;
    m_iUnknown168 = 0;
    m_iUnknown170 = 0;
    m_bUnknown178 = false;
    m_bUnknown179 = false;
}
