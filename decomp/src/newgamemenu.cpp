#include <CEGUIEventArgs.h>
#include <CEGUIInputEvent.h>
#include <CEGUIWindow.h>
#include "Character.h"
#include "NewGameMenu.h"

bool CNewGameMenu::handle_ExitButton(const CEGUI::EventArgs& event)
{
    CGameUI* ui = m_pGameUI;
    ui->m_bExitButtonPressed = true;
    ui->closeAll();
    return true;
}

bool CNewGameMenu::handle_CloseButton(const CEGUI::EventArgs& event)
{
    return CDropdownMenu::handle_CloseButton(event);
}

bool CNewGameMenu::handle_Submit(const CEGUI::EventArgs&)
{
    if (m_pUnknownD0->getText().length() != 0) m_pUnknownD8->activate();
    return true;
}

CNewGameMenu::CNewGameMenu(CGameUI& ui, CSettings& settings, Ogre::SceneManager* scene, CEGUI::Window* parent, CResourceManager* resources)
    : CDropdownMenu(ui, settings, scene, parent, resources, 1), m_bUnknownC0(false), m_bUnknownC1(false), m_bUnknownF8(false)
{
    createMenus();
}

#include "FileUtilities.h"
#include "NewGameMenuData.h"
#include "StringUtilities.h"
#include "GameClient.h"
#include "DataGroup.h"
#include <vector>

std::wstring CNewGameMenu::getEmptySave(std::wstring)
{
    TArrayList<std::wstring> files(10);
    std::vector<int> used;
    FILESYSTEM::GetFileListRecursive(FILESYSTEM::GetSaveDataPath(), files, L"*" + m_gFileVersionExtension);
    for (unsigned int i = 0; i < files.size(); ++i) {
        if (files[i].size() > 4) {
            std::wstring file = FILESYSTEM::GetFileName(files[i]);
            std::wstring stem = file.substr(0, file.size()-4);
            used.push_back(STRINGS::GetInt(std::wstring(stem.c_str())));
        }
    }
    int index = 0;
    if (!used.empty()) {
        bool empty;
        do {
            empty = true;
            for (unsigned int i = 0; i < used.size(); ++i)
                if (used[i] == index) { ++index; empty = false; }
        } while (!empty);
    }
    while (FILESYSTEM::FileExists(STRINGS::GetValueAsWString(index) + m_gFileVersionExtension))
        ++index;
    return STRINGS::GetValueAsWString(index) + m_gFileVersionExtension;
}

bool CNewGameMenu::onClick(ELayoutFunction function, std::wstring value)
{
    if (!m_bUnknown30 && m_bUnknown31) return true;
    switch (static_cast<int>(function)) {
    case 7:
        m_pGameUI->requestSetGameState(static_cast<EGameState>(0), static_cast<EMenu>(0));
        setOpen(false);
        break;
    case 14:
        m_pGameUI->getGameClient()->setCreationClass(value);
        m_pUnknownD0->activate();
        break;
    case 87: case 88: case 89:
        m_pGameUI->getGameClient()->setCreationPet(value);
        m_pUnknownD0->activate();
        break;
    case 2:
        m_pGameUI->m_text16C0 = getEmptySave(STRINGS::StringConvertToWide(m_pUnknownD0->getText().c_str(), 5000));
        m_pGameUI->m_name16B0 = STRINGS::StringConvertToWide(m_pUnknownD0->getText().c_str(), 5000);
        m_pGameUI->m_name16B8 = STRINGS::StringConvertToWide(m_pUnknownD8->getText().c_str(), 5000);
        m_pGameUI->requestSetGameState(static_cast<EGameState>(0), static_cast<EMenu>(m_bUnknownF8 ? 5 : 4));
        setOpen(false);
        break;
    }
    return true;
}

bool CNewGameMenu::handle_SubmitPet(const CEGUI::EventArgs&)
{
    if (m_pUnknownD8->getText().length() != 0) {
        if (m_pUnknownD0->getText().length() == 0)
            m_pUnknownD0->activate();
        else {
            m_pGameUI->m_text16C0 = getEmptySave(STRINGS::StringConvertToWide(m_pUnknownD0->getText().c_str(), 5000));
            m_pGameUI->m_name16B0 = STRINGS::StringConvertToWide(m_pUnknownD0->getText().c_str(), 5000);
            m_pGameUI->m_name16B8 = STRINGS::StringConvertToWide(m_pUnknownD8->getText().c_str(), 5000);
            m_pGameUI->requestSetGameState(static_cast<EGameState>(0), static_cast<EMenu>(m_bUnknownF8 ? 5 : 4));
            setOpen(false);
        }
    }
    return true;
}

void CNewGameMenu::setOpen(bool open)
{
    CDropdownMenu::setOpen(open);
    if (!open) return;
    m_pUnknownD0->setText("");
    m_pUnknownD0->activate();
    m_pUnknownD8->setText("Spot");
    m_pGameUI->getGameClient()->setCreationClass(L"Destroyer");
    m_pGameUI->getGameClient()->setCreationPet(L"Dog");
    m_iUnknownF0->setVisible(!m_bUnknownF8);
}

void CNewGameMenu::update(float elapsed)
{
    CDropdownMenu::update(elapsed);
    CCharacter* character = m_pGameUI->m_pCharacter;
    if (character && STRINGS::StringConvertToUTF8(character->getName()) != m_iUnknownE0->getText()) {
        std::string name = STRINGS::StringConvertToUTF8(character->getDataGroup()->GetDataValue(L"DISPLAYNAME", L""));
        m_iUnknownE0->setText(CEGUI::String(reinterpret_cast<const CEGUI::utf8*>(name.c_str())));
        std::string description = STRINGS::StringConvertToUTF8(character->getDescription());
        m_iUnknownE8->setText(CEGUI::String(reinterpret_cast<const CEGUI::utf8*>(description.c_str())));
    }
    m_iUnknownC8->setVisible(!m_pUnknownD0->getText().empty() && !m_pUnknownD8->getText().empty());
    std::wstring name = STRINGS::StringConvertToWide(m_pUnknownD0->getText().c_str(), 5000);
    std::wstring pet = STRINGS::StringConvertToWide(m_pUnknownD8->getText().c_str(), 5000);
    m_pGameUI->m_name16B0 = name;
    m_pGameUI->m_name16B8 = pet;
}

#include "FileSystem.h"
#include "GameVariables.h"
#include <CEGUIWindowManager.h>
#include <elements/CEGUIEditbox.h>
void CNewGameMenu::createMenus()
{
    CFileInfo info;
    CFileSystem::getSingleton()->getFileInfo(L"media/ui/charactercreate.layout", info, false, true, false);
    CEGUI::Window* layout = CEGUI::WindowManager::getSingleton().loadWindowLayout(CEGUI::String(info.m_sResourceName), true);
    m_pGameUI->convertToScreenScale(layout, false);
    m_pGameUI->mapToFunctions(layout);
    mapEventHandlers(layout);
    static_cast<CEGUI::Window*>(m_pUnknown18)->addChildWindow(layout);
    layout->setPosition(CEGUI::UVector2(CEGUI::UDim(0,0),CEGUI::UDim(0,0)));
    m_iUnknownC8 = layout->recursiveChildSearch("CreatePlayer");
    m_pUnknownD0 = layout->recursiveChildSearch("EditBox");
    m_pUnknownD0->subscribeEvent(CEGUI::Editbox::EventTextAccepted,
                               CEGUI::Event::Subscriber(&CNewGameMenu::handle_Submit, this));
    m_pUnknownD8 = layout->recursiveChildSearch("EditBoxPet");
    m_pUnknownD8->subscribeEvent(CEGUI::Editbox::EventTextAccepted,
                               CEGUI::Event::Subscriber(&CNewGameMenu::handle_SubmitPet, this));
    m_iUnknownE0 = layout->recursiveChildSearch("CharacterClass");
    m_iUnknownE8 = layout->recursiveChildSearch("CharacterClassDescription");
    m_iUnknownF0 = layout->recursiveChildSearch("Back");
    m_pDynamicPropertyFile->GetInt(KSETTINGS_RES_WIDTH);
    m_pDynamicPropertyFile->GetInt(KSETTINGS_RES_HEIGHT);
}
