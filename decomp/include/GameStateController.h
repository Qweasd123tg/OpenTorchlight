#ifndef GAMESTATECONTROLLER_H
#define GAMESTATECONTROLLER_H

// Partial: original class layout; game-state and HP event methods.

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
    bool m_bInitialized;
    unsigned char m_gap62[0x2];
    int m_iGameState;
    bool m_bPlayerInvulnerable;
    unsigned char m_gap69[0x3];
    float m_fPreviousHP;
    int m_iHelpTip;
};

#endif
