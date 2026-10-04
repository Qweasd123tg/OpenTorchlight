#ifndef TRIGGERSPHERE_H
#define TRIGGERSPHERE_H

#include "LogicTrigger.h"

class CTriggerSphere : public CLogicTrigger
{
public:
    CTriggerSphere(CResourceManager* resourceManager);
    virtual ~CTriggerSphere();
    virtual void scaleUpdated(const Ogre::Vector3& scale);
    virtual void updateTrigger(float elapsed, CEditorScene* scene);

private:
    float m_fRadius;

public:
    // Inline accessors behind the descriptors' property functions.
    float getRadius() const { return m_fRadius; }
};

#endif
