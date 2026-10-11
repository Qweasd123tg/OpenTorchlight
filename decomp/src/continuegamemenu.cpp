#include <CEGUIEventArgs.h>
#include <CEGUIInputEvent.h>
#include <CEGUIWindow.h>
#include <algorithm>
#include "Character.h"
#include "CharacterSaveState.h"
#include "ContinueGameMenu.h"

bool CContinueGameMenu::handle_ExitButton(const CEGUI::EventArgs& event)
{
    CGameUI* ui = m_pGameUI;
    ui->m_bExitButtonPressed = true;
    ui->closeAll();
    return true;
}

bool CContinueGameMenu::handle_CloseButton(const CEGUI::EventArgs& event)
{
    return CDropdownMenu::handle_CloseButton(event);
}

void CContinueGameMenu::scrollUp()
{
    int index = m_iUnknownC4 - 1;
    if (index < 0) index = 0;
    m_iUnknownC4 = index;
    updateCharacterList();
}

bool CContinueGameMenu::canContinue()
{
    return m_savedCharacters.size() != 0 && m_iUnknownC8 < int(m_savedCharacters.size()) && m_savedCharacters[m_iUnknownC8]->m_hp > 0.0f;
}

void CContinueGameMenu::setOpen(bool open)
{
    if (open) {
        reloadFiles(false);
        CDropdownMenu::setOpen(true);
        updateCharacterList();
        selectCharacter(0, true);
    } else CDropdownMenu::setOpen(false);
}

void CContinueGameMenu::scrollDown()
{
    ++m_iUnknownC4;
    if (m_iUnknownC4 >= static_cast<int>(m_savedCharacters.size()) - 4)
        m_iUnknownC4 = std::max(static_cast<int>(m_savedCharacters.size()) - 5, 0);
    updateCharacterList();
}

bool CContinueGameMenu::onDoubleClick(ELayoutFunction function, std::wstring)
{
    if (!m_bUnknown30 && m_bUnknown31) return false;
    if (!m_savedCharacters.empty() && !(m_savedCharacters[m_iUnknownC8]->m_hp <= 0.0f) &&
        function >= 14 && function <= 17) {
        m_pGameUI->requestSetGameState(static_cast<EGameState>(2), static_cast<EMenu>(0));
        setOpen(false);
    }
    return true;
}

bool CContinueGameMenu::onClick(ELayoutFunction function, std::wstring)
{
    if (!m_bUnknown30 && m_bUnknown31) return true;
    switch (static_cast<int>(function)) {
    case 3:
        if (m_savedCharacters[m_iUnknownC8]->m_hp > 0.0f) {
            m_pGameUI->requestSetGameState(static_cast<EGameState>(2), static_cast<EMenu>(0));
            setOpen(false);
        }
        break;
    case 7: m_pGameUI->requestSetGameState(static_cast<EGameState>(0), static_cast<EMenu>(0)); setOpen(false); break;
    case 8: reinterpret_cast<CEGUI::Window*>(m_iUnknown198)->setVisible(false); break;
    case 9:
        if (reinterpret_cast<CEGUI::Window*>(m_iUnknown198)->isVisible(false)) {
            reinterpret_cast<CEGUI::Window*>(m_iUnknown198)->setVisible(false);
            deleteCharacter();
        }
        break;
    case 12: scrollUp(); break;
    case 13: scrollDown(); break;
    case 14: case 15: case 16: case 17: case 18: selectCharacter(static_cast<int>(function) - 14, false); break;
    case 90: reinterpret_cast<CEGUI::Window*>(m_iUnknown198)->setVisible(true); break;
    }
    return true;
}

#include "StringTranslate.h"
CContinueGameMenu::CContinueGameMenu(CGameUI& ui, CSettings& settings, Ogre::SceneManager* scene, CEGUI::Window* parent, CResourceManager* resources)
    : CDropdownMenu(ui, settings, scene, parent, resources, 1), m_bUnknownC0(false), m_bUnknownC1(false), m_iUnknownC4(0), m_iUnknownC8(0)
{
    createMenus();
}

#include "CharacterSaveState.h"
CContinueGameMenu::~CContinueGameMenu()
{
    for (unsigned int i = 0; i < m_savedCharacters.size(); ++i)
        if (m_savedCharacters[i]) { delete m_savedCharacters[i]; m_savedCharacters[i] = NULL; }
    for (unsigned int i = 0; i < m_auxiliaryStates.size(); ++i)
        if (m_auxiliaryStates[i]) { delete m_auxiliaryStates[i]; m_auxiliaryStates[i] = NULL; }
    m_savedCharacters.clear();
    m_auxiliaryStates.clear();
    m_savePaths.clear();
    m_characterNames.clear();
    m_characterFlags.clear();
    m_characterIndices.clear();
}

#include "FileUtilities.h"
int DeleteFile(const wchar_t*);
void CContinueGameMenu::deleteCharacter()
{
    if (m_iUnknownC8 < static_cast<int>(m_savedCharacters.size())) {
        const std::wstring& selected = m_savePaths[m_iUnknownC8];
        std::wstring path = FILESYSTEM::AssembleAbsolutePath(FILESYSTEM::GetSaveDataPath(), selected);
        DeleteFile(path.c_str());
        m_iUnknownC8 = static_cast<int>(static_cast<unsigned int>(m_iUnknownC8) - 1u);
        if (m_iUnknownC8 < 0) m_iUnknownC8 = 0;
        reloadFiles(false); selectCharacter(m_iUnknownC8, true);
    }
    updateCharacterList();
}
