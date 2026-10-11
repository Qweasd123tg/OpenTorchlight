#include <CEGUIEventArgs.h>
#include <CEGUIWindow.h>
#include "Character.h"
#include "CinematicMenu.h"

bool CCinematicMenu::onClick(ELayoutFunction function, std::wstring)
{
    if (m_bUnknown30) {
        if (function == static_cast<ELayoutFunction>(10)) {
            m_pGameUI->requestSetGameState(static_cast<EGameState>(1), static_cast<EMenu>(0));
            m_bUnknown32 = true;
        }
        m_bUnknown32 = true;
    }
    return true;
}

CCinematicMenu::~CCinematicMenu()
{
}

#include "StringTranslate.h"
CCinematicMenu::CCinematicMenu(CGameUI& ui, CSettings& settings, Ogre::SceneManager* scene, CEGUI::Window* parent, CResourceManager* resources)
    : CDropdownMenu(ui, settings, scene, parent, resources, 1), m_cinematicWindow(NULL), m_textWindow(NULL), m_skipWindow(NULL), m_textIndex(0), m_textDuration(0), m_cinematicName(), m_displayedCharacters(0), m_cinematicData(NULL), m_textSpeed(1.0f)
{
    static std::wstring g_Dialog;
    if (g_Dialog.empty())
        g_Dialog = CStringTranslate::getSinglton()->getTranslateString(L"Dialog");
    setTitle(g_Dialog);
    createMenus();
}

#include "GameClient.h"
#include "Item.h"
#include "MouseManager.h"
#include "MasterResourceManager.h"
#include "SoundManager.h"
void CCinematicMenu::setOpen(bool open)
{
    if (m_bUnknown30) {
        if (!open) {
            if (m_pSoundBank) m_pSoundBank->stop();
            m_pGameUI->setIngameUIVisible(true);
            CGameClient* client = m_pGameUI->getGameClient();
            client->m_selectedItem.setObject(NULL); client->m_targetItem.setObject(NULL);
            client->m_selectedCharacter.setObject(NULL); client->m_targetCharacter.setObject(NULL);
            static_cast<CEGUI::Window*>(m_pUnknown10)->removeChildWindow(static_cast<CEGUI::Window*>(m_pUnknown18));
            m_bUnknown31 = true;
            broadcastEvent(static_cast<EMENU_TYPE>(1), static_cast<EMENU_EVENT>(2));
        }
    } else if (open) {
        m_pGameUI->setIngameUIVisible(false);
        m_pDynamicPropertyFile->GetInt(KSETTINGS_RES_WIDTH);
        m_pDynamicPropertyFile->GetInt(KSETTINGS_RES_HEIGHT);
        static_cast<CEGUI::Window*>(m_pUnknown20)->setPosition(CEGUI::UVector2(CEGUI::UDim(0,0),CEGUI::UDim(0,0)));
        static_cast<CEGUI::Window*>(m_pUnknown10)->addChildWindow(static_cast<CEGUI::Window*>(m_pUnknown18));
        static_cast<CEGUI::Window*>(m_pUnknown18)->moveToBack();
    }
    m_bUnknown30 = open;
}
void CCinematicMenu::update(float elapsed)
{
    if (m_bUnknown32) setOpen(false);
    bool adjust = false;
    if (m_bUnknown30) {
        if (m_textSpeed > 0.25f) {
            float value = m_textSpeed - elapsed; m_textSpeed = value < 0.25f ? 0.25f : value; adjust = true;
        }
    } else if (m_textSpeed < 1.0f) {
        float value = m_textSpeed + elapsed; m_textSpeed = value > 1.0f ? 1.0f : value; adjust = true;
    }
    if (adjust) {
        unsigned int property = KSETTINGS_F_SOUNDVOLUME;
        float sound = CMasterResourceManager::getSingleton()->m_pSettings->GetFloat(property);
        property = KSETTINGS_F_MUSICVOLUME;
        float music = CMasterResourceManager::getSingleton()->m_pSettings->GetFloat(property);
        property = KSETTINGS_SOUNDMUTE;
        int muteSound = CMasterResourceManager::getSingleton()->m_pSettings->GetInt(property);
        property = KSETTINGS_MUSICMUTE;
        int muteMusic = CMasterResourceManager::getSingleton()->m_pSettings->GetInt(property);
        music = music * m_textSpeed;
        CMasterResourceManager::getSingleton()->m_pSoundManager->updateAudioLevels(sound, music, muteSound != 0, muteMusic != 0);
    }
    if (!m_bUnknown30 && m_bUnknown31) return;
    if (reinterpret_cast<CMouseManager*>(reinterpret_cast<char*>(m_pGameUI) + 0x12a8)->buttonHeld(MOUSE_LEFT) || reinterpret_cast<CMouseManager*>(reinterpret_cast<char*>(m_pGameUI) + 0x12a8)->buttonHeld(MOUSE_RIGHT)) updateTextDisplay(elapsed * 10.0f);
    else if (reinterpret_cast<CMouseManager*>(reinterpret_cast<char*>(m_pGameUI) + 0x12a8)->buttonPressed(MOUSE_LEFT) || reinterpret_cast<CMouseManager*>(reinterpret_cast<char*>(m_pGameUI) + 0x12a8)->buttonPressed(MOUSE_RIGHT)) updateTextDisplay(m_textDuration);
    else updateTextDisplay(elapsed);
    CDropdownMenu::update(elapsed);
}
