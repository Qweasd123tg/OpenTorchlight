#ifndef MODELVIEWERSCENE_H
#define MODELVIEWERSCENE_H

#include "EditorScene.h"

class CModelViewerScene : public CEditorScene
{
public:
    CModelViewerScene();
    virtual ~CModelViewerScene();
    virtual void createDescriptors();
};

#endif
