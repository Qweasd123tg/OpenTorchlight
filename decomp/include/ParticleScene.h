#ifndef PARTICLESCENE_H
#define PARTICLESCENE_H

#include "EditorDefines.h"
#include "EditorScene.h"

class CParticleScene : public CEditorScene
{
public:
    virtual ~CParticleScene();
    virtual void fireEvent(EEDITOR_EVENTS event, long long objectId);
    virtual void createDescriptors();

    CParticleScene();
};

#endif
