#ifndef GAMEUI_H
#define GAMEUI_H
#include "RunicCore.h"

enum ELayoutFunction { LAYOUT_FUNCTION_EXIT_GAME = 0 };
enum EContextTip { CONTEXT_TIP_NONE = -1 };

// Partial: size 0x1a08 is the allocation at 0x5790e2. Complete vtable shape;
// onClick's return type is not verified and that method is not used here.
class CTextEvent;

class CGameUI : public CRunicCore
{
public:
    virtual ~CGameUI();
    virtual long long onClick(ELayoutFunction);
    static CGameUI* getSingleton();
    void queueTip(EContextTip tip);
    void closeLeft();
    void closeRight();
    void closeMenus();
    void closeAll();
    void setInteractiveMenuVisible(bool visible);
    int getUIIsInCinematic();
    void returnTextEventObject(CTextEvent* event);
private:
    unsigned char m_GameUIData[0x1a08 - 0x10];
};
#endif
