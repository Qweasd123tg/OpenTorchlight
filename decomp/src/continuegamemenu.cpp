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
