#include <CEGUIEventArgs.h>
#include <CEGUIWindow.h>
#include "Character.h"
#include "DialogMenu.h"

bool CDialogMenu::handle_ExitButton(const CEGUI::EventArgs& event)
{
    m_bUnknown32 = true;
    m_pGameUI->getCharacter()->setAIState(AISTATE_IDLE);
    return true;
}

bool CDialogMenu::handle_CloseButton(const CEGUI::EventArgs& event)
{
    if (static_cast<const CEGUI::MouseEventArgs&>(event).button == CEGUI::LeftButton) {
    m_bUnknown32 = true;
    m_pGameUI->getCharacter()->setAIState(AISTATE_IDLE);
        return CDropdownMenu::handle_CloseButton(event);
    }
    return true;
}

void CDialogMenu::update(float elapsed)
{
    bool closing = m_bUnknown31;
    CDropdownMenu::update(elapsed);
    if (!closing && m_bUnknown31) m_dialogOwner = NULL;
}

void CDialogMenu::setOpen(bool open)
{
    if (m_bUnknown30 != open) m_pGameUI->setInteractiveMenuVisible(open);
    CDropdownMenu::setOpen(open);
}

#include "Player.h"
#include "QuestManager.h"
#include "QuestDialog.h"

bool CDialogMenu::onClick(ELayoutFunction function, std::wstring)
{
    if (m_bUnknown30) {
        switch (static_cast<int>(function)) {
        case 9:
            m_pGameUI->getCharacter()->setAIState(AISTATE_IDLE);
            m_bUnknown32 = true;
            if (!m_dialogOwner) return false;
            static_cast<CPlayer*>(m_pGameUI->getCharacter())->getQuestManager()->giveQuest(
                m_dialogOwner->m_pQuest, m_speaker, true);
            break;
        case 10:
            m_pGameUI->getCharacter()->setAIState(AISTATE_IDLE);
            m_bUnknown32 = true;
            if (m_dialogOwner && m_dialogOwner->m_iDialogType == 3)
                static_cast<CPlayer*>(m_pGameUI->getCharacter())->getQuestManager()->completeQuest(m_dialogOwner->m_pQuest);
            break;
        case 8:
            m_pGameUI->getCharacter()->setAIState(AISTATE_IDLE);
            m_bUnknown32 = true;
            break;
        }
    }
    return true;
}

#include "StringTranslate.h"
CDialogMenu::CDialogMenu(CGameUI& ui, CSettings& settings, Ogre::SceneManager* scene, CEGUI::Window* parent, CResourceManager* resources)
    : CDropdownMenu(ui, settings, scene, parent, resources, 0), m_speaker(NULL), m_promptWindow(NULL), m_acceptWindow(NULL), m_declineWindow(NULL), m_extraWindow(NULL), m_dialogOwner(NULL)
{
    createMenus();
    static std::wstring g_Dialog;
    if (g_Dialog.empty())
        g_Dialog = CStringTranslate::getSinglton()->getTranslateString(L"Dialog");
    setTitle(g_Dialog);
}
