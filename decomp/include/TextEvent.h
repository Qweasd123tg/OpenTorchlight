#ifndef OTL_TEXT_EVENT_H
#define OTL_TEXT_EVENT_H
#include "RunicCore.h"
#include <CEGUIcolour.h>
#include <string>
class CGameUI;
namespace CEGUI { class Window; }
// Partial: original allocation and inlined initialization establish the named offsets.
class CTextEvent : public CRunicCore {
public:
    virtual ~CTextEvent();
    CTextEvent(const std::string&,const CEGUI::colour&,const CEGUI::colour&);
    void createText(CGameUI*,CEGUI::Window*);
    float m_Value10,m_Value14,m_Value18;
    char m_Padding1C[4];
    std::string m_Text;
    CEGUI::colour m_Colour28,m_Colour40;
    char m_Unrecovered58[8];
    float m_Value60,m_Value64,m_Value68,m_Unrecovered6C,m_Value70;
    char m_Padding74[4];
    CEGUI::Window* m_pWindow;
    bool m_Flag80,m_Flag81,m_Flag82;
    char m_Tail83[5];
};
typedef char check_event_size[sizeof(CTextEvent)==0x88?1:-1];
#endif
