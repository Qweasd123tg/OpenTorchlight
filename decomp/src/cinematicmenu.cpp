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

#include "Cinematic.h"
#include "Cinematics.h"
#include "FileSystem.h"
#include "SoundData.h"
#include "SoundBankDataInformation.h"
#include "StringUtilities.h"
#include <CEGUIImagesetManager.h>
#include <CEGUIImageset.h>
#include <CEGUIWindowManager.h>
#include <CEGUIPropertyHelper.h>
#include <OgreResourceGroupManager.h>

void CCinematicMenu::updateTextDisplay(float elapsed)
{
    if (m_textWindow->getText() != m_cinematicName)
        m_textWindow->setText(CEGUI::String(reinterpret_cast<const CEGUI::utf8*>(m_cinematicName.c_str())));
    if (m_textDuration > 0.0f && m_textIndex < m_textDuration) {
        m_textIndex += elapsed;
        float height = m_textWindow->getParent()->getHeight().asAbsolute(1.0f) + 50.0f;
        m_textWindow->setPosition(CEGUI::UVector2(CEGUI::UDim(0,0), CEGUI::UDim(0,height-height*(m_textIndex/m_textDuration))));
    } else {
        m_textWindow->getParent()->getHeight();
        m_textWindow->setPosition(CEGUI::UVector2(CEGUI::UDim(0,0),CEGUI::UDim(0,0)));
    }
}

void CCinematicMenu::createMenus()
{
    CFileInfo info;
    CFileSystem::getSingleton()->getFileInfo(L"media/ui/cinematicmenu.layout", info, false, true, false);
    CEGUI::Window* layout = CEGUI::WindowManager::getSingleton().loadWindowLayout(CEGUI::String(info.m_sResourceName), true);
    m_cinematicWindow = layout->recursiveChildSearch("Skip");
    m_textWindow = layout->recursiveChildSearch("DialogText");
    m_skipWindow = layout->recursiveChildSearch("Background");
    m_pGameUI->convertToScreenScale(layout, false);
    m_pGameUI->mapToFunctions(layout);
    mapEventHandlers(layout);
    static_cast<CEGUI::Window*>(m_pUnknown20)->addChildWindow(layout);
}

void CCinematicMenu::setText(std::wstring name)
{
    CCinematic* cinematic = CCinematics::getSingleton()->getCinematic(name.c_str());
    if (!cinematic) return;
    if (m_pSoundBank) {
        delete m_pSoundBank;
        m_pSoundBank = NULL;
    }
    CMasterResourceManager* master = CMasterResourceManager::getSingleton();
    m_pSoundBank = new CSoundBank(*master->m_pSoundManager, false);
    if (cinematic->m_sSound != EMPTY_WSTRING) {
        CSoundData* sound = master->m_pSoundBankDataInformation->getSoundDataObject(STRINGS::StringUpper(cinematic->m_sSound));
        if (sound) m_pSoundBank->addSample(38, sound->m_iGuid);
        m_pSoundBank->playSample(38, NULL, 0.0f, 0.0f, false);
    }
    if (m_cinematicData)
        CEGUI::ImagesetManager::getSingleton().destroyImageset(m_cinematicData);
    std::string image = STRINGS::StringConvertToUTF8(std::wstring(cinematic->m_sImage.c_str()));
    m_cinematicData = CEGUI::ImagesetManager::getSingleton().createImageset(
        CEGUI::String(image), CEGUI::String(Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME));
    m_cinematicData->setNativeResolution(CEGUI::Size(float(int(m_pGameUI->getAspectRatio()*768.0f)),768.0f));
    m_skipWindow->setProperty("Image", CEGUI::PropertyHelper::imageToString(&m_cinematicData->getImage("image")));
    m_displayedCharacters = 0;
    std::wstring text = STRINGS::replaceWString(cinematic->m_sText, L"\\n", L"\n");
    m_cinematicName = STRINGS::StringConvertToUTF8(std::wstring(text.c_str()));
    m_textIndex = 0.0f;
    float duration = float(m_cinematicName.size())*0.015f;
    m_textDuration = duration > 10.0f ? duration : 10.0f;
    updateTextDisplay(0.0f);
    m_textWindow->setText("");
}
