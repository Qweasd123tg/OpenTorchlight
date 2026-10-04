#ifndef LAYOUTSCENE_H
#define LAYOUTSCENE_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include "EditorDefines.h"
#include "EditorScene.h"

class CLayoutScene : public CEditorScene
{
public:
    virtual ~CLayoutScene();
    virtual void fireEvent(EEDITOR_EVENTS, long long);
    virtual void createDescriptors();
    CLayoutScene();

    // fields
};

#endif
