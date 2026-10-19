#ifndef OTL_CINEMATICMENU_H
#define OTL_CINEMATICMENU_H
#include "DropdownMenu.h"
class CGameUI; class CSettings; class CResourceManager;
namespace Ogre { class RenderWindow; class SceneManager; }
namespace CEGUI { class Window; class Imageset; }
// Partial: RTTI base and allocation size from the original GameUI create call.
// Opaque bytes are initialized by the original out-of-line constructor.
class CCinematicMenu : public CDropdownMenu {
public:
    void setText(std::wstring);
    void createMenus();
    void updateTextDisplay(float elapsed);
    virtual void update(float elapsed);
    virtual void setOpen(bool open);
    virtual bool onClick(ELayoutFunction function, std::wstring text);

    virtual ~CCinematicMenu();
    CCinematicMenu(CGameUI&, CSettings&, Ogre::SceneManager*, CEGUI::Window*, CResourceManager*);
    CEGUI::Window* m_cinematicWindow;
    CEGUI::Window* m_textWindow;
    CEGUI::Window* m_skipWindow;
    float m_textIndex;
    float m_textDuration;
    std::string m_cinematicName; // +0xe0
    int m_displayedCharacters;
    unsigned char m_PaddingEC[4];
    CEGUI::Imageset* m_cinematicData;
    float m_textSpeed;
    unsigned char m_PaddingFC[4];
};
typedef char check_CCinematicMenu_size[sizeof(CCinematicMenu)==0x100?1:-1];
#endif
