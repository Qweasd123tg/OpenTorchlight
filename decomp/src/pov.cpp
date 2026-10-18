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
    m_fUnknown108 = m_orientation[0][0];
    m_fUnknown110 = m_orientation[2][0];
    m_fUnknown10C = m_orientation[1][0];
    m_fUnknownF0 = m_orientation[0][1];
    m_fUnknownF4 = m_orientation[1][1];
    m_fUnknownF8 = m_orientation[2][1];
    m_fUnknownFC = m_orientation[0][2];
    m_fUnknown100 = m_orientation[1][2];
    m_fUnknown104 = m_orientation[2][2];
    m_iUnknown134 = *reinterpret_cast<const int*>(&m_viewOrientation[2][0]);
    m_iUnknown12C = *reinterpret_cast<const int*>(&m_viewOrientation[0][0]);
    m_iUnknown130 = *reinterpret_cast<const int*>(&m_viewOrientation[1][0]);
    m_iUnknown114 = *reinterpret_cast<const int*>(&m_viewOrientation[0][1]);
    m_iUnknown118 = *reinterpret_cast<const int*>(&m_viewOrientation[1][1]);
    m_iUnknown11C = *reinterpret_cast<const int*>(&m_viewOrientation[2][1]);
    m_iUnknown120 = *reinterpret_cast<const int*>(&m_viewOrientation[0][2]);
    m_fUnknown124 = m_viewOrientation[1][2];
    m_iUnknown128 = *reinterpret_cast<const int*>(&m_viewOrientation[2][2]);
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

    float x = m_fUnknown17C - m_fUnknownD8;
    float y = m_fUnknown180 - m_fUnknownDC;
    float z = m_fUnknown184 - m_fUnknownE0;
    const float distance = sqrtf(x * x + y * y + z * z);
    if (distance < 0.01f) {
        x = m_fUnknown17C;
        y = m_fUnknown180;
        z = m_fUnknown184;
    } else {
        z = z * 0.8f + m_fUnknown184;
        y = y * 0.8f + m_fUnknown180;
        x = x * 0.8f + m_fUnknown17C;
    }
    m_fUnknownD8 = x;
    m_fUnknownDC = y;
    m_fUnknownE0 = z;
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

    m_orientation = Ogre::Matrix4::IDENTITY;
    m_viewOrientation = Ogre::Matrix4::IDENTITY;

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


#include "Utilities.h"

void CPOV::DampLateralVelocity(float amount)
{
    float projection = m_fUnknown138 * m_fUnknown108 +
                       m_fUnknown13C * m_fUnknown10C +
                       m_fUnknown140 * m_fUnknown110;
    float x = m_fUnknown108 * projection;
    float y = m_fUnknown10C * projection;
    float z = m_fUnknown110 * projection;
    m_fUnknown138 = (m_fUnknown138 - x) + x * amount;
    m_fUnknown13C = (m_fUnknown13C - y) + y * amount;
    m_fUnknown140 = (m_fUnknown140 - z) + z * amount;
}

void CPOV::CapContactVelocity(float maximum)
{
    Ogre::Vector3 velocity(m_fUnknown138, m_fUnknown13C, m_fUnknown140);
    Ogre::Vector3 up(m_fUnknownF0, m_fUnknownF4, m_fUnknownF8);
    Ogre::Vector3 contact = up * velocity.dotProduct(up);
    velocity -= contact;
    if (velocity.length() > maximum) {
        velocity.normalise();
        velocity *= maximum;
    }
    velocity += contact;
    m_fUnknown138 = velocity.x;
    m_fUnknown13C = velocity.y;
    m_fUnknown140 = velocity.z;
}

void CPOV::SetOrientation(const Ogre::Matrix4& orientation)
{
    Ogre::Vector3 forward(orientation[0][2], orientation[1][2], orientation[2][2]);
    forward.normalise();
    Ogre::Vector3 up(0.0f, 1.0f, 0.0f);
    Ogre::Vector3 right = forward.crossProduct(up);
    m_orientation[0][0] = right.x;
    m_orientation[1][0] = right.y;
    m_orientation[2][0] = right.z;
    m_orientation[0][1] = up.x;
    m_orientation[1][1] = up.y;
    m_orientation[2][1] = up.z;
    m_orientation[0][2] = forward.x;
    m_orientation[1][2] = forward.y;
    m_orientation[2][2] = forward.z;
}

void CPOV::SetViewOrientation(const Ogre::Matrix4& orientation)
{
    m_viewOrientation = orientation;
    Ogre::Vector3 forward(orientation[0][2], orientation[1][2], orientation[2][2]);
    Ogre::Vector3 horizontal(forward.x, 0.0f, forward.z);
    horizontal.normalise();
    m_fUnknown150 = UTILITIES::VerifyFloat(MATH::angleBetween(horizontal, forward) * 57.295826f, 180.0f);
    if (forward.y > 0.0f)
        m_fUnknown150 = -m_fUnknown150;
}

#include <cstdlib>
extern short GetAsyncKeyState(unsigned int);
extern bool SetCursorPos(int,int);
void CPOV::Update(float elapsed, float scale)
{
    if (UpdateFlyingTo(elapsed) || !m_bUnknown178) return;
    UpdateInputs(elapsed);
    m_fUnknownD8 += m_fUnknown138 * elapsed * scale;
    m_fUnknownDC += m_fUnknown13C * elapsed * scale;
    m_fUnknownE0 += m_fUnknown140 * elapsed * scale;
    ExtractOrientationVectors();
    float damping = static_cast<float>(pow(static_cast<double>(0.0001f), static_cast<double>(elapsed)));
    m_fUnknown138 *= damping; m_fUnknown13C *= damping; m_fUnknown140 *= damping;
    CapContactVelocity(scale * 750.0f);
    m_previousX=m_fUnknownD8; m_previousY=m_fUnknownDC; m_previousZ=m_fUnknownE0;
}
void CPOV::UpdateMouseInput(void*, float)
{
    POINT point; GetCursorPos(&point);
    long long x=point.x, y=point.y;
    bool outside=x<=0 || x>=m_settings->GetInt(KSETTINGS_WIN_WIDTH) || y<=0 || y>=m_settings->GetInt(KSETTINGS_WIN_HEIGHT);
    if (GetAsyncKeyState(2)<0 && !outside && GetAsyncKeyState(16)>=0) {
        m_fUnknown160=(float(point.x)-float(m_iUnknown168))*0.5f;
        m_fUnknown158=(float(point.y)-float(m_iUnknown170))*0.5f;
        if(m_fUnknown160 < -10.0f)m_fUnknown160=-10.0f; else if(m_fUnknown160>10.0f)m_fUnknown160=10.0f;
        if(m_fUnknown158 < -10.0f)m_fUnknown158=-10.0f; else if(m_fUnknown158>10.0f)m_fUnknown158=10.0f;
        int height=m_settings->GetInt(KSETTINGS_RES_HEIGHT), width=m_settings->GetInt(KSETTINGS_RES_WIDTH);
        SetCursorPos(width/2+int(x-point.x),height/2+int(y-point.y));
        if(!m_bUnknown14E){m_fUnknown160=0; m_fUnknown158=0;}
        m_bUnknown14E=true;
    } else {
        m_bUnknown14E=false;
        m_fUnknown160*=0.8f; if(float(std::abs(int(m_fUnknown160)))<0.01f)m_fUnknown160=0;
        m_fUnknown158*=0.8f; if(float(std::abs(int(m_fUnknown158)))<0.01f)m_fUnknown158=0;
    }
    m_iUnknown168=point.x; m_iUnknown170=point.y;
}
void CPOV::ResetPOV(bool resetPosition,float roll,float pitch)
{
    m_fUnknown158=m_fUnknown15C=m_fUnknown160=m_fUnknown164=0;
    m_bUnknown148=m_bUnknown149=m_bUnknown14A=m_bUnknown14B=m_bUnknown14C=m_bUnknown14D=false;
    m_fUnknown138=Ogre::Vector3::ZERO.x;m_fUnknown13C=Ogre::Vector3::ZERO.y;m_fUnknown140=Ogre::Vector3::ZERO.z;
    if(resetPosition){m_fUnknownD8=m_fUnknownDC=m_fUnknownE0=0;m_orientation=Ogre::Matrix4::IDENTITY;m_viewOrientation=Ogre::Matrix4::IDENTITY;}
    Ogre::Matrix3 matrix;m_orientation.extract3x3Matrix(matrix);Ogre::Quaternion q(matrix);
    Ogre::Vector3 axis=Ogre::Quaternion::IDENTITY.xAxis();m_fUnknown108=axis.x;m_fUnknown10C=axis.y;m_fUnknown110=axis.z;
    axis=Ogre::Quaternion::IDENTITY.yAxis();m_fUnknownF0=axis.x;m_fUnknownF4=axis.y;m_fUnknownF8=axis.z;
    axis=Ogre::Quaternion::IDENTITY.zAxis();m_fUnknownFC=axis.x;m_fUnknown100=axis.y;m_fUnknown104=axis.z;
    axis=q.xAxis();m_viewAxis12C=axis.x;m_viewAxis130=axis.y;m_viewAxis134=axis.z;
    axis=q.yAxis();m_viewAxis114=axis.x;m_viewAxis118=axis.y;m_viewAxis11C=axis.z;
    axis=q.zAxis();m_viewAxis120=axis.x;m_fUnknown124=axis.y;m_viewAxis128=axis.z;
    m_fUnknown150=pitch;if(pitch==0)m_fUnknown150=q.getPitch(true).valueAngleUnits();if(m_fUnknown124>0)m_fUnknown150=-m_fUnknown150;
    m_fUnknown154=roll;if(roll==0)m_fUnknown154=q.getRoll(true).valueAngleUnits();
    Update(1.0f,1.0f);
}
