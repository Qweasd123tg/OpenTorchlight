#ifndef TRIGGERBOX_H
#define TRIGGERBOX_H

#include "LogicTrigger.h"

class CTriggerBox : public CLogicTrigger
{
public:
    CTriggerBox(CResourceManager* resourceManager);
    virtual ~CTriggerBox();
    void setDimensions(const Ogre::Vector3& dimensions);
    virtual void scaleUpdated(const Ogre::Vector3& scale);
    virtual void updateTrigger(float elapsed, CEditorScene* scene);

private:
    Ogre::Vector3 m_vDimensions;
    Ogre::Vector3 m_vHalfDimensions;
};

#endif
