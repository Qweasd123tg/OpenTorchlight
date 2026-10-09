#ifndef OTL_SKILL_FOLDOUT_H
#define OTL_SKILL_FOLDOUT_H
#include "RunicCore.h"
#include <string>
class CGameUI;
namespace CEGUI { class Window; }
// Partial: allocation 0xcb8, base and initializer offsets verified in GameUI::create.
class CSkillFoldout : public CRunicCore {
public:
    virtual ~CSkillFoldout();
    CSkillFoldout(CGameUI*,CEGUI::Window*);
    void load(CGameUI*,std::wstring);
    int m_iSelection;
    char m_Padding14[4];
    long long m_SkillIndices[100];
    CGameUI* m_pGameUI;
    CEGUI::Window* m_pParent;
    char m_Unrecovered348[0xcb1-0x348];
    bool m_bFlagCB1;
    char m_TailCB2[6];
};
typedef char check_foldout_size[sizeof(CSkillFoldout)==0xcb8?1:-1];
#endif
