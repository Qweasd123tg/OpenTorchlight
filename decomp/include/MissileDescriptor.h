#ifndef MISSILEDESCRIPTOR_H
#define MISSILEDESCRIPTOR_H

#include "PositionableObjectDescriptor.h"
#include "EditorBaseObject.h"
#include "EditorScene.h"
#include "DescriptorProp.h"

class CMissileDescriptor : public CPositionableObjectDescriptor
{
public:
    virtual ~CMissileDescriptor();
    virtual void update(float);
    virtual CEditorBaseObject* CreateObject(CEditorScene* scene);
    CMissileDescriptor();

    unsigned char m_gap170[0x8] __attribute__((aligned(8)));
    int m_iUnknown178;
    unsigned char m_gap17C[0x4] __attribute__((aligned(4)));
    int m_iUnknown180;
    unsigned char m_gap184[0x2];
    bool m_bUnknown186;
    bool m_bUnknown187;
    bool m_bUnknown188;
    unsigned char m_gap189[0x13];
    int m_iUnknown19C;
    unsigned char m_gap1A0[0x18] __attribute__((aligned(8)));
    int m_iUnknown1B8;
    unsigned char m_gap1BC[0x94] __attribute__((aligned(4)));
    float m_fUnknown250;
    int m_iUnknown254;
    unsigned char m_gap258[0x8] __attribute__((aligned(8)));
    int m_iUnknown260;
    int m_iUnknown264;
    int m_iUnknown268;
    int m_iUnknown26C;
    int m_iUnknown270;
    unsigned char m_gap274[0x8] __attribute__((aligned(4)));
    int m_iUnknown27C;
    int m_iUnknown280;
    int m_iUnknown284;
    int m_iUnknown288;
    int m_iUnknown28C;
    unsigned char m_gap290[0x38] __attribute__((aligned(8)));
    long long m_Unknown2C8;
    int m_iUnknown2D0;

    static void Set_setParticleFileKMISSILE_PARTICLE_RELEASE(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getParticleFileKMISSILE_PARTICLE_RELEASE(CEditorBaseObject* object, unsigned int& count);
    static void Set_setParticleFileKMISSILE_PARTICLE_ALIVE(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getParticleFileKMISSILE_PARTICLE_ALIVE(CEditorBaseObject* object, unsigned int& count);
    static void Set_setParticleFileKMISSILE_PARTICLE_HIT(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getParticleFileKMISSILE_PARTICLE_HIT(CEditorBaseObject* object, unsigned int& count);
    static void Set_setParticleFileKMISSILE_PARTICLE_DIE(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getParticleFileKMISSILE_PARTICLE_DIE(CEditorBaseObject* object, unsigned int& count);
    static void Set_setNumberOfRicochets(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getNumberOfRicochets(CEditorBaseObject* object, unsigned int& count);
    static void Set_setDistanceAllowedToTraveled(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getDistanceAllowedToTraveled(CEditorBaseObject* object, unsigned int& count);
    static void Set_setRadiusOfMissile(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getRadiusOfMissile(CEditorBaseObject* object, unsigned int& count);
    static void Set_setAOERadius(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getAOERadius(CEditorBaseObject* object, unsigned int& count);
    static void Set_setMaxVelocity(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getMaxVelocity(CEditorBaseObject* object, unsigned int& count);
    static void Set_setFriction(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getFriction(CEditorBaseObject* object, unsigned int& count);
    static void Set_setForceAppliedPerSecond(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getForceAppliedPerSecond(CEditorBaseObject* object, unsigned int& count);
    static void Set_setStartAtFullVelocity(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getStartAtFullVelocity(CEditorBaseObject* object, unsigned int& count);
    static void Set_setMissileName(CEditorBaseObject* object, UNIONDATA16BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getMissileName(CEditorBaseObject* object, unsigned int& count);
    static void Set_setTargetHomingValue(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getTargetHomingValue(CEditorBaseObject* object, unsigned int& count);
    static void Set_setTargetingAngle(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getTargetingAngle(CEditorBaseObject* object, unsigned int& count);
    static void Set_setRateOFire(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getRateOFire(CEditorBaseObject* object, unsigned int& count);
    static void Set_setCollisionSphereVisible(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getCollisionSphereVisible(CEditorBaseObject* object, unsigned int& count);
    static void Set_setAOESphereVisible(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getAOESphereVisible(CEditorBaseObject* object, unsigned int& count);
    static void Set_setTrackGround(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getTrackGround(CEditorBaseObject* object, unsigned int& count);
    static void Set_setTargetsPosition(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getTargetsPosition(CEditorBaseObject* object, unsigned int& count);
    static void Set_setCollidesWithObjects(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getCollidesWithObjects(CEditorBaseObject* object, unsigned int& count);
    static void Set_setMissileArchHeight(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getMissileArchHeight(CEditorBaseObject* object, unsigned int& count);
    static void Set_setHomeAfterXSeconds(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getHomeAfterXSeconds(CEditorBaseObject* object, unsigned int& count);
    static void Set_setPiercing(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getPiercing(CEditorBaseObject* object, unsigned int& count);
    static void Set_setMaxTurnRate(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getMaxTurnRate(CEditorBaseObject* object, unsigned int& count);
    static void Set_setTurnAcceleration(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getTurnAcceleration(CEditorBaseObject* object, unsigned int& count);
    static void Set_setRandomizedTurnAcceleration(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getRandomizedTurnAcceleration(CEditorBaseObject* object, unsigned int& count);
    static void Set_setRandomizedTurnUpdate(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getRandomizedTurnUpdate(CEditorBaseObject* object, unsigned int& count);
    static void Set_setAOEDamageScale(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getAOEDamageScale(CEditorBaseObject* object, unsigned int& count);
    static void Set_setSoakScale(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getSoakScale(CEditorBaseObject* object, unsigned int& count);
    static void Set_setCanVerticalAim(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getCanVerticalAim(CEditorBaseObject* object, unsigned int& count);
    static void Set_setInherentMinDMGPercent(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getInherentMinDMGPercent(CEditorBaseObject* object, unsigned int& count);
    static void Set_setInherentMaxDMGPercent(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getInherentMaxDMGPercent(CEditorBaseObject* object, unsigned int& count);
    static void Set_setInherentKnockback(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getInherentKnockback(CEditorBaseObject* object, unsigned int& count);
    static void Set_setDamageType(CEditorBaseObject* object, const UNIONDATA8BIT* data, unsigned int count);
    static UNIONDATA8BIT* Get_getDamageType(CEditorBaseObject* object, unsigned int& count);
    static unsigned int GetDamageTypeIDByString(CEditorScene* scene, CEditorBaseObject* object, const std::wstring& value, void* userData);
    static std::wstring GetDamageTypeStringByID(CEditorScene* scene, CEditorBaseObject* object, unsigned int index, void* userData);
};

#endif
