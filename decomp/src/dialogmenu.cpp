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

#include "FileSystem.h"
#include "EmptyStrings.h"
#include "StringUtilities.h"
#include "Quest.h"
#include <CEGUIWindowManager.h>
#include <OgreLogManager.h>
void CDialogMenu::createMenus()
{
    CFileInfo info;
    CFileSystem::getSingleton()->getFileInfo(L"media/ui/dialogmenu.layout",info,false,true,false);
    CEGUI::Window* layout = CEGUI::WindowManager::getSingleton().loadWindowLayout(CEGUI::String(info.m_sResourceName),true);
    m_declineWindow = layout->getChild("Decline");
    m_acceptWindow = layout->getChild("Accept");
    m_promptWindow = layout->getChild("Ok");
    m_extraWindow = layout->getChild("DialogText");
    m_iUnknown50 = layout->recursiveChildSearch("Title");
    m_pGameUI->convertToScreenScale(layout,false);
    m_pGameUI->mapToFunctions(layout);
    mapEventHandlers(layout);
    static_cast<CEGUI::Window*>(m_pUnknown20)->addChildWindow(layout);
}
void CDialogMenu::setNPC(CCharacter* npc)
{
    m_dialogOwner = NULL;
    m_speaker = npc;
    if (!m_acceptWindow || !m_declineWindow || !m_promptWindow) return;
    m_acceptWindow->setVisible(false);
    m_declineWindow->setVisible(false);
    m_promptWindow->setVisible(false);
    CPlayer* player = static_cast<CPlayer*>(m_pGameUI->getCharacter());
    if (player || !player->getQuestManager() || !m_speaker) {
        TArrayList<CQuestDialog*> dialogs(10);
        player->getQuestManager()->getDialogsForNPC(dialogs,m_speaker,true);
        if (dialogs.size()) {
            m_dialogOwner = dialogs[0];
            if (m_dialogOwner) {
                std::wstring details = EMPTY_WSTRING;
                switch (m_dialogOwner->m_iDialogType) {
                case 2:
                    details = L"\n\n" + m_dialogOwner->m_pQuest->getQuestDetails();
                case 3:
                    m_promptWindow->setVisible(true);
                    break;
                case 1:
                    m_declineWindow->setVisible(true);
                    m_acceptWindow->setVisible(true);
                    break;
                }
                std::string label = STRINGS::StringConvertToUTF8(m_dialogOwner->getDialog(false)) +
                                    STRINGS::StringConvertToUTF8(details);
                m_extraWindow->setText(CEGUI::String(reinterpret_cast<const CEGUI::utf8*>(label.c_str())));
            }
        } else {
            std::wstring message = L"Error occured getting NPC dialog for character : " + m_speaker->getName();
            Ogre::LogManager::getSingleton().logMessage(STRINGS::StringConvertToNarrow(message.c_str()),Ogre::LML_CRITICAL,false);
        }
    }
}
