/*
-----------------------------------------------------------------------------------------------
Copyright (C) 2013 Henry van Merode. All rights reserved.

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
-----------------------------------------------------------------------------------------------
*/

#ifndef PARTICLE_DYNAMIC_ATTRIBUTE_H
#define PARTICLE_DYNAMIC_ATTRIBUTE_H

#include <vector>
#include <OgreVector2.h>
#include <OgreSimpleSpline.h>

// ABI declarations for the version statically linked into Torchlight.
// Upstream fa746774 is a reference, not a drop-in replacement: the original
// getValue takes Particle*, and DynamicAttribute has no value-changed flag.
namespace ParticleUniverse
{
class Particle;
enum InterpolationType { IT_LINEAR = 0, IT_SPLINE = 1 };
class IElement
{
public:
    virtual ~IElement();
};
class DynamicAttribute : public IElement
{
public:
    enum DynamicAttributeType { DAT_FIXED, DAT_RANDOM, DAT_CURVED };
    DynamicAttribute();
    virtual ~DynamicAttribute();
    virtual float getValue(Particle*, float) = 0;
    virtual void copyAttributesTo(DynamicAttribute*) = 0;
protected:
    DynamicAttributeType mType;
};
class DynamicAttributeCurved : public DynamicAttribute
{
public:
    DynamicAttributeCurved(InterpolationType interpolationType);
    virtual ~DynamicAttributeCurved();
    virtual float getValue(Particle*, float);
    virtual void copyAttributesTo(DynamicAttribute*);
    virtual void addControlPoint(float x, float y);
    void processControlPoints();
    size_t getNumControlPoints() const;
    void getControlPointValues(unsigned int, float&, float&);
    void removeAllControlPoints();
private:
    float mRange;
    Ogre::SimpleSpline mSpline;
    InterpolationType mInterpolationType;
    std::vector<Ogre::Vector2> mControlPoints;
};
}
#endif
