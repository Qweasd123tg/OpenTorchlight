#ifndef DROPDOWNMENU_H
#define DROPDOWNMENU_H

// Partial: generated from symbols, RTTI and recovered layouts (tools/decomp/promote.py).
// Bases, virtual order and field offsets are the original ones; names, field types
// and return types are placeholders until the class's own TU is recovered.

#include <CEGUIEventArgs.h>
#include <CEGUIWindow.h>
#include <OgreSceneManager.h>
#include <string>
#include "DynamicPropertyFile.h"
#include "GameEnums.h"
#include "GenericModel.h"
#include "ResourceManager.h"
#include "RunicCore.h"
#include "Settings.h"
#include "SoundBank.h"
class CGameUI;
class iMenuListener;

class CDropdownMenu : public CRunicCore
{
public:
    virtual ~CDropdownMenu();
    virtual long long processInput(void*, float, bool);
    virtual void update(float);
    virtual void updateLayout();
    virtual void addMenuListener(iMenuListener*);
    virtual void removeMenuListener(iMenuListener*);
    virtual void setOpen(bool);
    virtual void onClick(ELayoutFunction, std::wstring);
    virtual void onDoubleClick(ELayoutFunction, std::wstring);
    void broadcastEvent(EMENU_TYPE, EMENU_EVENT);
    long long handle_CloseButton(const CEGUI::EventArgs&);
    void mapEventHandlers(CEGUI::Window*);
    void setTitle(const std::wstring&);
    unsigned long handle_onDoubleClick(const CEGUI::EventArgs&);
    unsigned long handle_onClick(const CEGUI::EventArgs&);
    void createMenus();
    CDropdownMenu(CGameUI&, CSettings&, Ogre::SceneManager*, CEGUI::Window*, CResourceManager*, unsigned int);

    // fields
    void* m_pUnknown10;
    void* m_pUnknown18;
    void* m_pUnknown20;
    unsigned char m_gap28[0x8] __attribute__((aligned(8)));
    bool m_bUnknown30;
    bool m_bUnknown31;
    bool m_bUnknown32;
    unsigned char m_gap33[0x5];
    CDynamicPropertyFile* m_pDynamicPropertyFile;
    CGameUI* m_pGameUI;
    void* m_pUnknown48;
    long long m_iUnknown50;
    unsigned char m_gap58[0x18] __attribute__((aligned(8)));
    CGenericModel* m_pGenericModel;
    CResourceManager* m_pResourceManager;
    CSoundBank* m_pSoundBank;
    int m_iUnknown88;
    unsigned char m_gap8C[0x4] __attribute__((aligned(4)));
    unsigned char m_Unknown90[0x18] __attribute__((aligned(8)));
    unsigned char m_UnknownA8[0x18] __attribute__((aligned(8)));
};

#endif
