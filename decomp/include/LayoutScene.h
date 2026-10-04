#ifndef LAYOUTSCENE_H
#define LAYOUTSCENE_H

#include "EditorDefines.h"
#include "EditorScene.h"

class CLayoutScene : public CEditorScene
{
public:
    CLayoutScene();
    virtual ~CLayoutScene();
    virtual void fireEvent(EEDITOR_EVENTS event, long long guid);
    virtual void createDescriptors();
};

#endif
