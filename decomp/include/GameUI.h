#ifndef GAMEUI_H
#define GAMEUI_H
#include <string>

#include "GameEnums.h"
#include "RunicCore.h"

enum ELayoutFunction { LAYOUT_FUNCTION_EXIT_GAME = 0 };
enum EContextTip { CONTEXT_TIP_NONE = -1 };

// Partial: size 0x1a08 is the allocation at 0x5790e2. Complete vtable shape;
// onClick's return type is not verified and that method is not used here.
class CTextEvent;
class CCharacter;
class iMenuListener;

class CGameUI : public CRunicCore
{
public:
    virtual ~CGameUI();
    virtual long long onClick(ELayoutFunction);
    static CGameUI* getSingleton();
    CCharacter* getCharacter() { return m_pCharacter; }
    void queueTip(EContextTip tip);
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
