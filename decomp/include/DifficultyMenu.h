#ifndef DIFFICULTYMENU_H
#define DIFFICULTYMENU_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include <CEGUIEventArgs.h>
#include <CEGUIWindow.h>
#include <elements/CEGUICheckbox.h>
#include <OgreSceneManager.h>
#include <string>
#include "DropdownMenu.h"
#include "GameEnums.h"
#include "ResourceManager.h"
#include "Settings.h"
class CGameUI;

class CDifficultyMenu : public CDropdownMenu
{
public:

    virtual ~CDifficultyMenu();
    virtual void update(float);
    virtual void setOpen(bool);
    virtual bool onClick(ELayoutFunction, std::wstring);
    bool handle_ExitButton(const CEGUI::EventArgs&);
    bool handle_CloseButton(const CEGUI::EventArgs&);
    void createMenus();
    CDifficultyMenu(CGameUI&, CSettings&, Ogre::SceneManager*, CEGUI::Window*, CResourceManager*);

    // fields
    bool m_bUnknownC0;
    bool m_bUnknownC1;
    unsigned char m_gapC2[0x6];
    CEGUI::Checkbox* m_hardcoreCheckbox;
    bool m_bUnknownD0;
};

#endif
