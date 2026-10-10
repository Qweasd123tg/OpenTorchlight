#ifndef NEWGAMEMENU_H
#define NEWGAMEMENU_H

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

class CNewGameMenu : public CDropdownMenu
{
public:

    virtual ~CNewGameMenu();
    virtual void update(float);
    virtual void setOpen(bool);
    virtual bool onClick(ELayoutFunction, std::wstring);
    bool handle_Submit(const CEGUI::EventArgs&);
    bool handle_ExitButton(const CEGUI::EventArgs&);
    bool handle_CloseButton(const CEGUI::EventArgs&);
    CNewGameMenu* getEmptySave(std::wstring);
    bool handle_SubmitPet(const CEGUI::EventArgs&);
    void createMenus();
    CNewGameMenu(CGameUI&, CSettings&, Ogre::SceneManager*, CEGUI::Window*, CResourceManager*);

    // fields
    bool m_bUnknownC0;
    bool m_bUnknownC1;
    unsigned char m_gapC2[0x6];
    long long m_iUnknownC8;
    CEGUI::Window* m_pUnknownD0;
    CEGUI::Window* m_pUnknownD8;
    long long m_iUnknownE0;
    long long m_iUnknownE8;
    long long m_iUnknownF0;
    bool m_bUnknownF8;
};

#endif
