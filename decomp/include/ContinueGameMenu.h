#ifndef CONTINUEGAMEMENU_H
#define CONTINUEGAMEMENU_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include <CEGUIEventArgs.h>
#include <CEGUIWindow.h>
#include <OgreSceneManager.h>
#include <string>
#include "DropdownMenu.h"
#include "GameEnums.h"
#include "GameUI.h"
#include "ResourceManager.h"
#include "Settings.h"
class CGameUI;
class CCharacterSaveState;

class CContinueGameMenu : public CDropdownMenu
{
public:

    virtual ~CContinueGameMenu();
    virtual void update(float);
    virtual void setOpen(bool);
    virtual bool onClick(ELayoutFunction, std::wstring);
    virtual bool onDoubleClick(ELayoutFunction, std::wstring);
    bool canContinue();
    bool handle_ExitButton(const CEGUI::EventArgs&);
    bool handle_CloseButton(const CEGUI::EventArgs&);
    void updateCharacterList();
    void scrollUp();
    void scrollDown();
    void reloadFiles(bool);
    bool selectCharacter(int, bool);
    void deleteCharacter();
    void createMenus();
    CContinueGameMenu(CGameUI&, CSettings&, Ogre::SceneManager*, CEGUI::Window*, CResourceManager*);

    // fields
    bool m_bUnknownC0;
    bool m_bUnknownC1;
    unsigned char m_gapC2[0x2];
    int m_iUnknownC4;
    int m_iUnknownC8;
    unsigned char m_gapCC[0x4] __attribute__((aligned(4)));
    void* m_pUnknownD0;
    void* m_pUnknownD8;
    void* m_pUnknownE0;
    void* m_pUnknownE8;
    void* m_pUnknownF0;
    void* m_pUnknownF8;
    void* m_pUnknown100;
    void* m_pUnknown108;
    void* m_pUnknown110;
    void* m_pUnknown118;
    long long m_iUnknown120;
    long long m_iUnknown128;
    long long m_iUnknown130;
    long long m_iUnknown138;
    long long m_iUnknown140;
    long long m_iUnknown148;
    long long m_iUnknown150;
    long long m_iUnknown158;
    long long m_iUnknown160;
    long long m_iUnknown168;
    long long m_iUnknown170;
    long long m_iUnknown178;
    long long m_iUnknown180;
    long long m_iUnknown188;
    long long m_iUnknown190;
    long long m_iUnknown198;
    long long m_iUnknown1A0;
    std::vector<bool> m_characterFlags; // +0x1a8
    std::vector<int> m_characterIndices; // +0x1d0
    std::vector<CCharacterSaveState*> m_savedCharacters;
    std::vector<CCharacterSaveState*> m_auxiliaryStates; // +0x200
    std::vector<std::wstring> m_savePaths; // +0x218
    std::vector<std::wstring> m_characterNames; // +0x230
};

#endif
