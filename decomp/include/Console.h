#ifndef CONSOLE_H
#define CONSOLE_H

#include <CEGUIWindow.h>
#include <string>
#include "RunicCore.h"

// The RTTI base and two destructor vtable slots are present in the original.
// Unrecovered regions remain opaque; container/window types below are named
// by calls in CConsole's original functions.
class CGameUI; class CResourceManager; class CGameClient;
class CConsole : public CRunicCore
{
public:
    void spawnUnit(std::wstring, std::wstring);
    void update(float);
    void spawnMonster(std::wstring, std::wstring, bool, int);
    bool handleKeyDown(const CEGUI::EventArgs&);
    void createObjectByName(std::wstring, std::wstring);
    void spawnItem(std::wstring, long long, std::wstring);
    void executeCommandLine(std::wstring);
    void addText(std::wstring);
    bool handleSubmit(const CEGUI::EventArgs&);
    void equipSkillToPlayer(std::wstring name);
    void addSpeedToPlayer();
    void cameraShake(std::wstring name);
    void spawnClassCreate(std::wstring name, std::wstring count, std::wstring level);
    void addTextNoHistory(std::wstring text);
    void keyEvent(unsigned int event, unsigned int key, long text);

    CConsole(CGameUI*, CResourceManager*, CEGUI::Window*);

    virtual ~CConsole();
    bool getVisible();
    void setVisible(bool);
    bool handleClose(const CEGUI::EventArgs&);
    std::wstring getHistoryText();

    CEGUI::Window* m_parentWindow; // +0x10
    CEGUI::Window* m_window;
    CEGUI::Window* m_inputWindow;
    CEGUI::Window* m_historyWindow;
    int m_historyIndex; // +0x30
    unsigned char m_Padding34[4];
    TArrayList<std::wstring> m_history;
    CResourceManager* m_resources; // +0x50
    CGameClient* m_gameClient; // +0x58
    CGameUI* m_gameUI; // +0x60
    bool m_logConsole; // +0x68
    unsigned char m_Padding69[7];
};

#endif
