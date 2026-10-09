#ifndef OTL_SKILL_FOLDOUT_H
#define OTL_SKILL_FOLDOUT_H
#include "RunicCore.h"
#include <string>
class CGameUI;
class CBaseUnit;
namespace CEGUI { class Window; }
// Partial: allocation 0xcb8, base and initializer offsets verified in GameUI::create.
class CSkillFoldout : public CRunicCore {
public:
    void showFoldout(CBaseUnit*,float,float,bool,bool);
    virtual ~CSkillFoldout();
    CSkillFoldout(CGameUI*,CEGUI::Window*);
    void load(CGameUI*,std::wstring);
    int m_iSelection;
    char m_Padding14[4];
    long long m_SkillIndices[100];
    CGameUI* m_pGameUI;
    CEGUI::Window* m_pParent;
    CEGUI::Window* m_pWindow;
    CEGUI::Window* m_Icons[10][10];
    CEGUI::Window* m_Hotkeys[10][10];
    long long m_ItemGuids[10][10];
    bool m_bIncludeItems;
    bool m_bFlagCB1;
    char m_TailCB2[6];
};
typedef char check_foldout_size[sizeof(CSkillFoldout)==0xcb8?1:-1];
#endif
