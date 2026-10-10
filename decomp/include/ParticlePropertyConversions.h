#ifndef PARTICLE_PROPERTY_CONVERSIONS_H
#define PARTICLE_PROPERTY_CONVERSIONS_H
#include "ParticleDynamicAttribute.h"
ParticleUniverse::DynamicAttribute* getDynPropFromArray(const float* values, unsigned int count);
float* getArrayFromDynProp(ParticleUniverse::DynamicAttribute* value, unsigned int& count);
#endif
