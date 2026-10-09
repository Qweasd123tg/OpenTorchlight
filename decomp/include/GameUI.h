#ifndef GAMEUI_H
#define GAMEUI_H
#include <string>

#include "GameEnums.h"
#include "RunicCore.h"

enum ELayoutFunction { LAYOUT_FUNCTION_EXIT_GAME = 0 };
enum EContextTip { CONTEXT_TIP_NONE = -1 };

// Partial: size 0x1a08 is the allocation at 0x5790e2. Complete vtable shape;
// onClick's return type is not verified and that method is not used here.
namespace CEGUI { class Image; class Window; }
class CGameClient;
class CSubMenu;
class CItem;
namespace Ogre { class RenderWindow; }
class CTextEvent;
class CCharacter;
class CEquipment;
class CEquipmentTooltip;
class iMenuListener;

class CGameUI : public CRunicCore
{
public:
    void showEquipmentTooltip(CCharacter*,CEquipment*,CEquipmentTooltip*,CEquipmentTooltip*,CEquipmentTooltip*);
    float getWindowWidth();
    float getWindowHeight();
    void updateIngameUI(float, CGameClient*, Ogre::RenderWindow*);
    void convertToScreenScale(CEGUI::Window*, bool);
    void mapToFunctions(CEGUI::Window*);
    virtual ~CGameUI();
    void updateSlots();
    bool menuItemClick(CCharacter*, CSubMenu*, int, bool);
    void returnDraggedItem();
    void setCursorState(ECursorState);
    void setMouseOverItem(CItem*, bool);
    void updateHardwareCursor();
    virtual long long onClick(ELayoutFunction);
    static CGameUI* getSingleton();
    CCharacter* getCharacter() { return m_pCharacter; }
    void queueTip(EContextTip tip);
    float scaledY(float value);
    const CEGUI::Image* getImageFromImageSet(const unsigned char* name);
    void clearMenuMouseOvers();
    void openModalDialog(std::wstring,std::wstring,bool);
    void closeLeft();
    void closeRight();
    void closeMenus();
    void closeAll();
    void setInteractiveMenuVisible(bool visible);
    int getUIIsInCinematic();
    void returnTextEventObject(CTextEvent* event);
    void addMenuListener(EMENU_TYPE menu, iMenuListener* listener);
    void setCinematicOpen(std::wstring cinematic);
private:
    unsigned char m_GameUIData10[0x38 - 0x10];
    CCharacter* m_pCharacter;
    unsigned char m_GameUIData40[0x1a08 - 0x40];
};
#endif
