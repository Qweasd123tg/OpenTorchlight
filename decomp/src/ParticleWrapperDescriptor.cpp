#include "EmptyStrings.h"
#include "ParticleWrapperDescriptor.h"

CParticleWrapperDescriptor::CParticleWrapperDescriptor()
    : CPositionableObjectDescriptor(L"Particle", L"A PARTICLE", L"particle", true, true, true, true, true)
{
    m_iFlags |= DESCRIPTOR_FLAG_CHILDREN;
    AddProperty(L"PROPERTIES", L"LIFE TIME", L"Leave 0 to loop.", (void*)Set_setFixedLifeTime, (void*)Get_getFixedLifeTime, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"PROPERTIES", L"VISIBLE", L"sets the particle system visible or not.", (void*)Set_setVisible, (void*)Get_getVisible, VARIABLE_TYPE_BOOL, 0);
    AddProperty(L"WORLD SCALES", L"VISUAL SCALE", L"Scales everything that is a visual by scale", (void*)Set_setWorldVisualScale, (void*)Get_getWorldVisualScale, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"WORLD SCALES", L"TIME SCALE", L"Make particle systems go faster", (void*)Set_setWorldScaleTime, (void*)Get_getWorldScaleTime, VARIABLE_TYPE_FLOAT, 0);
    AddProperty(L"WORLD SCALES", L"VELOCITY SCALE", L"Make particle and emitter velocities faster or slower", (void*)Set_setWorldScaleVelocity, (void*)Get_getWorldScaleVelocity, VARIABLE_TYPE_FLOAT, 0);
}

CParticleWrapperDescriptor::~CParticleWrapperDescriptor()
{
}
