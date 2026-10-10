#ifndef MAINMENU_H
#define MAINMENU_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include <CEGUIEventArgs.h>
#include <CEGUIWindow.h>
#include <OgreSceneManager.h>
#include <string>
#include "DropdownMenu.h"
#include "GameEnums.h"
#include "ResourceManager.h"
#include "Settings.h"
class CGameUI;

class CMainMenu : public CDropdownMenu
{
public:

    virtual ~CMainMenu();
    virtual void update(float);
    virtual bool onClick(ELayoutFunction, std::wstring);
    bool handle_ExitButton(const CEGUI::EventArgs&);
    bool handle_CloseButton(const CEGUI::EventArgs&);
    void createMenus();
    CMainMenu(CGameUI&, CSettings&, Ogre::SceneManager*, CEGUI::Window*, CResourceManager*);

    // fields
    bool m_bUnknownC0;
    bool m_bUnknownC1;
    unsigned char m_gapC2[0x6];
    long long m_iUnknownC8;
    long long m_iUnknownD0;
    long long m_iUnknownD8;
    long long m_iUnknownE0;
    long long m_iUnknownE8;
    long long m_iUnknownF0;
};

#endif
