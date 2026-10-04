#ifndef GAMESTATECONTROLLER_H
#define GAMESTATECONTROLLER_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include "EditorBaseObject.h"
#include "ResourceManager.h"

class CGameStateController : public CEditorBaseObject
{
public:
    virtual ~CGameStateController();
    void broadcastPlayerHPThreshholdEvents(float, float, float);
    void showHelp();
    void healPlayer();
    void doActualGameState(bool);
    void performStateControl();
    void setInitialized();
    void update(float);
    CGameStateController(CResourceManager*);

    // fields
    CResourceManager* m_pResourceManager;
    bool m_bEnabled;
    bool m_bUnknown61;
    unsigned char m_gap62[0x2];
    int m_iGameState;
    bool m_bPlayerInvulnerable;
    unsigned char m_gap69[0x3];
    float m_fUnknown6C;
    int m_iHelpTip;
};

#endif
