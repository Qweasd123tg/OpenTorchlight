#ifndef CAMERASHAKE_H
#define CAMERASHAKE_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include <OgreVector3.h>
#include <string>
#include "EditorBaseObject.h"
#include "RunicCore.h"

class CCameraShake : public CEditorBaseObject
{
public:
    virtual ~CCameraShake();
    bool update(float, Ogre::Vector3&, Ogre::Vector3&, bool);
    CCameraShake();
    void setCameraShakeName(const std::wstring&);
    void clone(CCameraShake*);
    CCameraShake(const std::wstring&, Ogre::Vector3, float);
    void startCameraShake(const Ogre::Vector3&, bool);

    // fields
    float m_fDuration;
    float m_fUnknown5C;
    float m_fMagnitudeMult;
    int m_iDirection;
    float m_fDirection;
    float m_fDirection_6C;
    CRunicCore* m_pRunicCore;
    int m_iUnknown78;
    unsigned char m_gap7C[0x4] __attribute__((aligned(4)));
    void* m_pCameraShakeName;
    int m_iDirectionOrientation;
    int m_iUnknown8C;
    int m_iUnknown90;
    int m_iUnknown94;
    bool m_bUnknown98;
    bool m_bCameraFallsOffWithDistance;
};

#endif
