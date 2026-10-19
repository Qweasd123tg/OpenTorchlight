#ifndef RENDERABLESTATES_H
#define RENDERABLESTATES_H

#include <string>
namespace Ogre { class Material; }

struct CRenderableStates
{
    unsigned char m_state0;
    bool castsShadows;
    unsigned char m_state2;
    bool highlighted;
    bool renderBehind;
    unsigned char m_gap5[3];
    Ogre::Material* originalMaterial; // +0x8, preserved before cloning by reInitialize
    Ogre::Material* material;
    Ogre::Material* material18;
    Ogre::Material* material20;
    short projectorTechnique;
    short projectorPass;
    unsigned short m_value2c;
    unsigned char m_gap2e;
    bool spectral; // +0x2f, material name contains SPECTRAL
    bool m_flag30;
    bool m_flag31;
    unsigned char m_gap32[2];
    float m_opacity; // +0x34
    std::string name; // +0x38, used by StringUpper in the texture setters
};

#endif
