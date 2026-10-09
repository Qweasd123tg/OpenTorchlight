#ifndef OTL_QUESTDIALOGMENU_H
#define OTL_QUESTDIALOGMENU_H
#include "DropdownMenu.h"
class CGameUI; class CSettings; class CResourceManager;
namespace Ogre { class RenderWindow; class SceneManager; }
namespace CEGUI { class Window; }
// Partial: RTTI base and allocation size from the original GameUI create call.
// Opaque bytes are initialized by the original out-of-line constructor.
class CQuestDialogMenu : public CDropdownMenu {
public:
    virtual ~CQuestDialogMenu();
    CQuestDialogMenu(CGameUI&, CSettings&, Ogre::SceneManager*, CEGUI::Window*, CResourceManager*);
    char m_Unrecoveredc0[0x148];
};
typedef char check_CQuestDialogMenu_size[sizeof(CQuestDialogMenu)==0x208?1:-1];
#endif
