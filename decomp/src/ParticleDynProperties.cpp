#include "ParticlePropertyConversions.h"

TArrayList<float> m_DynamicArrayForProperties(10);

float* getArrayFromDynProp(ParticleUniverse::DynamicAttribute* property, unsigned int& count)
{
    using namespace ParticleUniverse;
    m_DynamicArrayForProperties.clear();
    switch (property->getType()) {
    case 0:
        m_DynamicArrayForProperties.add(0.0f);
        m_DynamicArrayForProperties.add(property->getValue(NULL, 0.0f));
        break;
    case 1:
        m_DynamicArrayForProperties.add(1.0f);
        m_DynamicArrayForProperties.add(static_cast<DynamicAttributeRandom*>(property)->getMin());
        m_DynamicArrayForProperties.add(static_cast<DynamicAttributeRandom*>(property)->getMax());
        break;
    case 2:
        if (DynamicAttributeCurved* curve = dynamic_cast<DynamicAttributeCurved*>(property)) {
            m_DynamicArrayForProperties.add(curve->getInterpolationType() == 0 ? 2.0f : 3.0f);
            unsigned int points = curve->getNumControlPoints();
            for (unsigned int i = 0; i < points; ++i) {
                float time, value;
                curve->getControlPointValues(i, time, value);
                m_DynamicArrayForProperties.add(time);
                m_DynamicArrayForProperties.add(value);
            }
        }
        break;
    case 4:
        if (DynamicAttributeRandomCurved* curve = dynamic_cast<DynamicAttributeRandomCurved*>(property)) {
            m_DynamicArrayForProperties.add(curve->getInterpolationType() == 0 ? 4.0f : 5.0f);
            unsigned int points = curve->getNumControlPoints();
            for (unsigned int i = 0; i < points; ++i) {
                float time, minimum, maximum;
                curve->getControlPointValues(i, time, minimum, maximum);
                m_DynamicArrayForProperties.add(time);
                m_DynamicArrayForProperties.add(minimum);
                m_DynamicArrayForProperties.add(maximum);
            }
        }
        break;
    }
    count = m_DynamicArrayForProperties.size();
    return &m_DynamicArrayForProperties[0];
}
