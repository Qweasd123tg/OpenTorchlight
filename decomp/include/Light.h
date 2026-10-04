#ifndef LIGHT_H
#define LIGHT_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include <OgreMatrix4.h>
#include <OgreVector3.h>
#include <string>
#include "GenericModel.h"
#include "PositionableObject.h"
#include "ResourceManager.h"

class CLight : public CPositionableObject
{
public:
    virtual ~CLight();
    virtual void orientationUpdated(const Ogre::Matrix4&);
    virtual void scaleUpdated(const Ogre::Vector3&);
    float getRotation();
    void setRotation(float);
    void destroyLights();
    CLight(CResourceManager*);
    void updateLightDensity(bool);
    void setBitmapFile(std::wstring);

    // fields
    int m_iLightDensity;
    unsigned char m_gap104[0x4] __attribute__((aligned(4)));
    unsigned char m_Unknown108[0x18] __attribute__((aligned(8)));
    void* m_pBitmapFile;
    int m_iUnknown128;
    unsigned char m_gap12C[0x4] __attribute__((aligned(4)));
    CGenericModel* m_pGenericModel;

public:
    // Inline accessors behind the descriptors' property functions.
    int getLightDensity() const { return m_iLightDensity; }
};

#endif
