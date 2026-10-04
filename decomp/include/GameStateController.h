#ifndef GAMESTATECONTROLLER_H
#define GAMESTATECONTROLLER_H

#include "EditorBaseObject.h"

class CResourceManager;

class CGameStateController : public CEditorBaseObject
{
public:
    virtual ~CGameStateController();

    void broadcastPlayerHPThreshholdEvents(float fCurrentHP,
                                            float fPreviousHP,
                                            float fDeltaHP);
    void showHelp();
    void healPlayer();
    void doActualGameState(bool bEnabled);
    void performStateControl();
    void setInitialized();
    void update(float fDeltaTime);

    CGameStateController(CResourceManager* pResourceManager);

    CResourceManager* m_pResourceManager;
    bool m_bEnabled;
    bool m_bInitialized;
    int m_iGameState;
    bool m_bPlayerInvulnerable;
    float m_fPreviousPlayerHP;
    int m_iHelpTip;
};

#endif
