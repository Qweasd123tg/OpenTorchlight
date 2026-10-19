#include "SettingsMenu.h"

bool CSettingsMenu::onClick(ELayoutFunction function,std::wstring)
{
    if (m_bUnknown30) {
        if (function == static_cast<ELayoutFunction>(8)) m_bUnknown32 = true;
        else if (function == static_cast<ELayoutFunction>(9)) { m_applyChanges = true; m_bUnknown32 = true; }
        setOpen(false);
    }
    return true;
}

#include "StringTranslate.h"
CSettingsMenu::CSettingsMenu(CGameUI& ui, CSettings& settings, Ogre::SceneManager* scene, CEGUI::Window* parent, CResourceManager* resources)
    : CDropdownMenu(ui, settings, scene, parent, resources, 0), m_applyChanges(false)
{
    createMenus();
    static std::wstring g_Settings;
    if (g_Settings.empty())
        g_Settings = CStringTranslate::getSinglton()->getTranslateString(L"Settings");
    setTitle(g_Settings);
}

#include "FileSystem.h"
#include "MasterResourceManager.h"
#include "StringUtilities.h"
#include "SettingsMenuData.h"
#include <CEGUIWindowManager.h>
#include <elements/CEGUICheckbox.h>
#include <elements/CEGUICombobox.h>
#include <elements/CEGUIComboDropList.h>
#include <elements/CEGUIListboxTextItem.h>
#include <elements/CEGUISlider.h>

void CSettingsMenu::createMenus()
{
    CFileInfo info;
    CFileSystem::getSingleton()->getFileInfo(L"media/ui/settingsmenu.layout", info, false, true, false);
    CEGUI::Window* layout = CEGUI::WindowManager::getSingleton().loadWindowLayout(CEGUI::String(info.m_sResourceName), true);
    m_pGameUI->convertToScreenScale(layout, false);
    m_pGameUI->mapToFunctions(layout);
    mapEventHandlers(layout);
    static_cast<CEGUI::Window*>(m_pUnknown20)->addChildWindow(layout);
    m_iUnknown50 = layout->recursiveChildSearch("Title");
    m_window130 = layout->recursiveChildSearch("ShowTips");
    static_cast<CEGUI::Checkbox*>(m_window130)->setSelected(CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_SHOW_TIPS) != 0);
    m_window138 = layout->recursiveChildSearch("ShowFloatyNumbers");
    static_cast<CEGUI::Checkbox*>(m_window138)->setSelected(CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_FLOATY_NUMBERS) != 0);
    m_window140 = layout->recursiveChildSearch("ShowBlood");
    static_cast<CEGUI::Checkbox*>(m_window140)->setSelected(CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_SHOW_BLOOD) != 0);
    m_window148 = layout->recursiveChildSearch("NetbookMode");
    static_cast<CEGUI::Checkbox*>(m_window148)->setSelected(CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_NETBOOK_MODE) != 0);
    m_windowC8 = layout->recursiveChildSearch("Fullscreen");
    m_windowD0 = layout->recursiveChildSearch("Antialiasing");
    m_windowD8 = layout->recursiveChildSearch("RenderBehind");
    m_windowE0 = layout->recursiveChildSearch("Rimlights");
    m_windowE8 = layout->recursiveChildSearch("HardwareSkinning");
    m_windowF0 = layout->recursiveChildSearch("VSync");
    m_window120 = layout->recursiveChildSearch("MusicMute");
    m_window128 = layout->recursiveChildSearch("SoundMute");
    m_windowF8 = layout->recursiveChildSearch("ResolutionDropdown");
    m_window100 = layout->recursiveChildSearch("ShadowDropdown");
    m_window108 = layout->recursiveChildSearch("ParticleDropdown");
    CEGUI::Combobox* resolution = static_cast<CEGUI::Combobox*>(m_windowF8);
    resolution->getDropList()->setAlwaysOnTop(true);
    resolution->getDropList()->setAutoArmEnabled(true);
    resolution->setSingleClickEnabled(true);
    resolution->getDropList()->setClippedByParent(false);
    resolution->setClippedByParent(false);
    m_windowE8->setVisible(false);
    CEGUI::Combobox* shadows = static_cast<CEGUI::Combobox*>(m_window100);
    shadows->getDropList()->setAlwaysOnTop(true);
    shadows->getDropList()->setAutoArmEnabled(true);
    shadows->setSingleClickEnabled(true);
    shadows->getDropList()->setClippedByParent(false);
    shadows->setClippedByParent(false);
    CEGUI::Combobox* particles = static_cast<CEGUI::Combobox*>(m_window108);
    particles->getDropList()->setAlwaysOnTop(true);
    particles->getDropList()->setAutoArmEnabled(true);
    particles->setSingleClickEnabled(true);
    particles->getDropList()->setClippedByParent(false);
    particles->setClippedByParent(false);
    m_window118 = layout->recursiveChildSearch("SoundVolume");
    m_window110 = layout->recursiveChildSearch("MusicVolume");
}

void CSettingsMenu::setOpen(bool open)
{
    if (m_bUnknown30 != open) m_pGameUI->setInteractiveMenuVisible(open);
    if (m_bUnknown30) {
        if (!open) {
            static_cast<CEGUI::Window*>(m_pUnknown10)->removeChildWindow(static_cast<CEGUI::Window*>(m_pUnknown18));
            m_bUnknown31 = false;
        }
    } else if (open) {
        m_bUnknown31 = false;
        m_pDynamicPropertyFile->GetInt(KSETTINGS_RES_WIDTH);
        m_pDynamicPropertyFile->GetInt(KSETTINGS_RES_HEIGHT);
        static_cast<CEGUI::Window*>(m_pUnknown20)->setPosition(CEGUI::UVector2(CEGUI::UDim(0,0),CEGUI::UDim(0,0)));
        static_cast<CEGUI::Window*>(m_pUnknown10)->addChildWindow(static_cast<CEGUI::Window*>(m_pUnknown18));
        static_cast<CEGUI::Window*>(m_pUnknown18)->moveToBack();
        m_applyChanges = false;
        static_cast<CEGUI::Checkbox*>(m_windowC8)->setSelected(CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_FULLSCREEN) != 0);
        static_cast<CEGUI::Checkbox*>(m_windowD0)->setSelected(CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_FSAA) != 0);
        static_cast<CEGUI::Checkbox*>(m_windowD8)->setSelected(CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_RENDERBEHIND) != 0);
        static_cast<CEGUI::Checkbox*>(m_windowE0)->setSelected(CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_RIMLIGHTS_ENABLED) != 0);
        static_cast<CEGUI::Checkbox*>(m_windowE8)->setSelected(CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_ALLOW_HWSKINNING) != 0);
        static_cast<CEGUI::Checkbox*>(m_windowF0)->setSelected(CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_VSYNCH) != 0);
        static_cast<CEGUI::Checkbox*>(m_window128)->setSelected(CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_SOUNDMUTE) != 0);
        static_cast<CEGUI::Checkbox*>(m_window120)->setSelected(CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_MUSICMUTE) != 0);
        float sound = CMasterResourceManager::getSingleton()->m_pSettings->GetFloat(KSETTINGS_F_SOUNDVOLUME);
        float music = CMasterResourceManager::getSingleton()->m_pSettings->GetFloat(KSETTINGS_F_MUSICVOLUME);
        static_cast<CEGUI::Slider*>(m_window118)->setMaxValue(1.0f);
        static_cast<CEGUI::Slider*>(m_window118)->setCurrentValue(sound);
        static_cast<CEGUI::Slider*>(m_window110)->setMaxValue(1.0f);
        static_cast<CEGUI::Slider*>(m_window110)->setCurrentValue(music);
        CEGUI::Combobox* resolutions = static_cast<CEGUI::Combobox*>(m_windowF8);
        if (resolutions->getItemCount() == 0) {
            CSettings* settings = CMasterResourceManager::getSingleton()->m_pSettings;
            for (unsigned int i = 0; i < settings->m_resolutions.size(); ++i) {
                std::string label = STRINGS::GetValueAsString(settings->m_resolutions[i].width) + " x " + STRINGS::GetValueAsString(settings->m_resolutions[i].height);
                CEGUI::ListboxTextItem* item = new CEGUI::ListboxTextItem(CEGUI::String(reinterpret_cast<const CEGUI::utf8*>(label.c_str())),0,NULL,false,true);
                item->setSelectionColours(CEGUI::colour(1.0f,0.5f,0.5f,1.0f));
                item->setID(i);
                item->setAutoDeleted(true);
                resolutions->addItem(item);
            }
        }
        CSettings* settings = CMasterResourceManager::getSingleton()->m_pSettings;
        if (resolutions->getItemCount() != 0) resolutions->setItemSelectState(static_cast<size_t>(0),true);
        for (unsigned int i = 0; i < settings->m_resolutions.size(); ++i) {
            if (settings->m_resolutions[i].width == CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_RES_WIDTH) &&
                settings->m_resolutions[i].height == CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_RES_HEIGHT)) {
                resolutions->setItemSelectState(static_cast<size_t>(i),true);
                break;
            }
        }
        m_pGameUI->sizeComboList(resolutions);
        resolutions->moveToFront();
        resolutions->getDropList()->moveToFront();
        CEGUI::Combobox* shadows = static_cast<CEGUI::Combobox*>(m_window100);
        if (shadows->getItemCount() == 0) {
            for (unsigned int i = 0; i < 6; ++i) {
                std::wstring text = CStringTranslate::getSinglton()->getTranslateString(KShadowSettingNames[i].c_str());
                std::string label = STRINGS::StringConvertToUTF8(std::wstring(text.c_str()));
                CEGUI::ListboxTextItem* item = new CEGUI::ListboxTextItem(CEGUI::String(reinterpret_cast<const CEGUI::utf8*>(label.c_str())),0,NULL,false,true);
                item->setSelectionColours(CEGUI::colour(1.0f,0.5f,0.5f,1.0f));
                item->setAutoDeleted(true);
                item->setID(i);
                shadows->addItem(item);
            }
        }
        shadows->setItemSelectState(static_cast<size_t>(0),true);
        for (unsigned int i = 0; i < 6; ++i) {
            if (static_cast<int>(i) == CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_SHADOW_DETAIL)) {
                shadows->setItemSelectState(static_cast<size_t>(i),true);
                break;
            }
        }
        m_pGameUI->sizeComboList(shadows);
        shadows->moveToFront();
        shadows->getDropList()->moveToFront();
        CEGUI::Combobox* particles = static_cast<CEGUI::Combobox*>(m_window108);
        if (particles->getItemCount() == 0) {
            for (unsigned int i = 0; i < 3; ++i) {
                std::wstring text = CStringTranslate::getSinglton()->getTranslateString(KParticleSettingNames[i].c_str());
                std::string label = STRINGS::StringConvertToUTF8(std::wstring(text.c_str()));
                CEGUI::ListboxTextItem* item = new CEGUI::ListboxTextItem(CEGUI::String(reinterpret_cast<const CEGUI::utf8*>(label.c_str())),0,NULL,false,true);
                item->setSelectionColours(CEGUI::colour(1.0f,0.5f,0.5f,1.0f));
                item->setAutoDeleted(true);
                item->setID(i);
                particles->addItem(item);
            }
        }
        particles->setItemSelectState(static_cast<size_t>(0),true);
        for (unsigned int i = 0; i < 3; ++i) {
            if (KParticleFPSDetail[i] >= CMasterResourceManager::getSingleton()->m_pSettings->GetFloat(KSETTINGS_F_PARTICLEFPS)) {
                particles->setItemSelectState(static_cast<size_t>(i),true);
                break;
            }
        }
        static_cast<CEGUI::Checkbox*>(m_window130)->setSelected(CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_SHOW_TIPS) != 0);
        static_cast<CEGUI::Checkbox*>(m_window138)->setSelected(CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_FLOATY_NUMBERS) != 0);
        static_cast<CEGUI::Checkbox*>(m_window140)->setSelected(CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_SHOW_BLOOD) != 0);
        static_cast<CEGUI::Checkbox*>(m_window148)->setSelected(CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_NETBOOK_MODE) != 0);
        m_pGameUI->sizeComboList(particles);
        particles->moveToFront();
        particles->getDropList()->moveToFront();
    }
    m_bUnknown30 = open;
}

#include "SoundManager.h"
#include "GameClient.h"
#include "CameraControl.h"
#include <algorithm>
#include <ParticleUniverseSystemManager.h>
void CSettingsMenu::update(float)
{
    if (!m_bUnknown30 && m_bUnknown31) return;
    bool soundMute = static_cast<CEGUI::Checkbox*>(m_window128)->isSelected();
    bool musicMute = static_cast<CEGUI::Checkbox*>(m_window120)->isSelected();
    float sound = static_cast<CEGUI::Slider*>(m_window118)->getCurrentValue();
    float music = static_cast<CEGUI::Slider*>(m_window110)->getCurrentValue();
    if (music != LastMusicVolume || sound != LastSoundVolume || musicMute != LastMusicMute || soundMute != LastSoundMute)
        CMasterResourceManager::getSingleton()->m_pSoundManager->updateAudioLevels(sound,music,soundMute,musicMute);
    LastSoundVolume = sound;
    LastSoundMute = soundMute;
    LastMusicVolume = music;
    LastMusicMute = musicMute;
    if (m_bUnknown31 || m_bUnknown30) return;
    m_bUnknown31 = true;
    if (!m_applyChanges) {
        int oldSoundMute = CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_SOUNDMUTE);
        int oldMusicMute = CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_MUSICMUTE);
        float oldSound = CMasterResourceManager::getSingleton()->m_pSettings->GetFloat(KSETTINGS_F_SOUNDVOLUME);
        float oldMusic = CMasterResourceManager::getSingleton()->m_pSettings->GetFloat(KSETTINGS_F_MUSICVOLUME);
        CMasterResourceManager::getSingleton()->m_pSoundManager->updateAudioLevels(oldSound,oldMusic,oldSoundMute!=0,oldMusicMute!=0);
        return;
    }
    int oldVsync = CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_VSYNCH);
    int oldRimlights = CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_RIMLIGHTS_ENABLED);
    int oldSkinning = CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_ALLOW_HWSKINNING);
    int oldFsaa = CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_FSAA);
    int oldNetbook = CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_NETBOOK_MODE);
    bool netbook = static_cast<CEGUI::Checkbox*>(m_window148)->isSelected();
    CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_FULLSCREEN);
    CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_RES_WIDTH);
    CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_RES_HEIGHT);
    CMasterResourceManager::getSingleton()->m_pSettings->SetInt(KSETTINGS_NETBOOK_MODE,netbook);
    int resolutionIndex = 0;
    CEGUI::Combobox* resolution = static_cast<CEGUI::Combobox*>(m_windowF8);
    if (resolution->getItemCount()) resolutionIndex = resolution->getSelectedItem()->getID();
    int shadow = 0;
    bool fullscreen = static_cast<CEGUI::Checkbox*>(m_windowC8)->isSelected();
    int rimlights = 0, fsaa = 0, renderBehind = 0;
    if (!netbook) {
        shadow = static_cast<CEGUI::Combobox*>(m_window100)->getSelectedItem()->getID();
        fullscreen = static_cast<CEGUI::Checkbox*>(m_windowC8)->isSelected();
        rimlights = static_cast<CEGUI::Checkbox*>(m_windowE0)->isSelected();
        fsaa = static_cast<CEGUI::Checkbox*>(m_windowD0)->isSelected();
        renderBehind = static_cast<CEGUI::Checkbox*>(m_windowD8)->isSelected();
    }
    bool skinning = static_cast<CEGUI::Checkbox*>(m_windowE8)->isSelected();
    bool vsync = static_cast<CEGUI::Checkbox*>(m_windowF0)->isSelected();
    musicMute = static_cast<CEGUI::Checkbox*>(m_window120)->isSelected();
    soundMute = static_cast<CEGUI::Checkbox*>(m_window128)->isSelected();
    CMasterResourceManager::getSingleton()->m_pSettings->SetInt(KSETTINGS_SOUNDMUTE,soundMute);
    CMasterResourceManager::getSingleton()->m_pSettings->SetInt(KSETTINGS_MUSICMUTE,musicMute);
    CMasterResourceManager::getSingleton()->m_pSettings->SetInt(KSETTINGS_SHOW_TIPS,static_cast<CEGUI::Checkbox*>(m_window130)->isSelected());
    CMasterResourceManager::getSingleton()->m_pSettings->SetInt(KSETTINGS_FLOATY_NUMBERS,static_cast<CEGUI::Checkbox*>(m_window138)->isSelected());
    CMasterResourceManager::getSingleton()->m_pSettings->SetInt(KSETTINGS_SHOW_BLOOD,static_cast<CEGUI::Checkbox*>(m_window140)->isSelected());
    CMasterResourceManager::getSingleton()->m_pSettings->SetInt(KSETTINGS_FULLSCREEN,fullscreen);
    CMasterResourceManager::getSingleton()->m_pSettings->SetInt(KSETTINGS_FSAA,fsaa);
    CMasterResourceManager::getSingleton()->m_pSettings->SetInt(KSETTINGS_RENDERBEHIND,renderBehind);
    CMasterResourceManager::getSingleton()->m_pSettings->SetInt(KSETTINGS_RIMLIGHTS_ENABLED,rimlights);
    CMasterResourceManager::getSingleton()->m_pSettings->SetInt(KSETTINGS_VSYNCH,vsync);
    CMasterResourceManager::getSingleton()->m_pSettings->SetInt(KSETTINGS_ALLOW_HWSKINNING,skinning);
    unsigned particle = static_cast<CEGUI::Combobox*>(m_window108)->getSelectedItem()->getID();
    if (netbook) particle = 0;
    float fps = KParticleFPSDetail[particle];
    float fraction = KParticlePCTDetail[particle];
    CMasterResourceManager::getSingleton()->m_pSettings->SetFloat(KSETTINGS_F_PARTICLEFPS,fps);
    CMasterResourceManager::getSingleton()->m_pParticleSystemManager->setParticleFPS(fps);
    CMasterResourceManager::getSingleton()->m_pSettings->SetFloat(KSETTINGS_F_PARTICLE_PCT,fraction);
    CMasterResourceManager::getSingleton()->m_pParticleSystemManager->setEmitterLoopingReleasePCT(std::max(std::min(fraction,100.0f),0.0f)/100.0f);
    CSettings* settings = CMasterResourceManager::getSingleton()->m_pSettings;
    if (resolutionIndex < static_cast<int>(settings->m_resolutions.size())) {
        CMasterResourceManager::getSingleton()->m_pSettings->SetInt(KSETTINGS_RES_WIDTH,settings->m_resolutions[resolutionIndex].width);
        CMasterResourceManager::getSingleton()->m_pSettings->SetInt(KSETTINGS_RES_HEIGHT,settings->m_resolutions[resolutionIndex].height);
    }
    sound = static_cast<CEGUI::Slider*>(m_window118)->getCurrentValue();
    music = static_cast<CEGUI::Slider*>(m_window110)->getCurrentValue();
    CMasterResourceManager::getSingleton()->m_pSettings->SetFloat(KSETTINGS_F_SOUNDVOLUME,sound);
    CMasterResourceManager::getSingleton()->m_pSettings->SetFloat(KSETTINGS_F_MUSICVOLUME,static_cast<CEGUI::Slider*>(m_window110)->getCurrentValue());
    int oldShadow = CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_SHADOW_DETAIL);
    CMasterResourceManager::getSingleton()->m_pSettings->SetInt(KSETTINGS_SHADOW_DETAIL,shadow);
    int oldShadowsEnabled = CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_SHADOWS_ENABLED);
    switch (shadow) {
    case 0: CMasterResourceManager::getSingleton()->m_pSettings->SetInt(KSETTINGS_LIGHTING_ENABLED,0);
            CMasterResourceManager::getSingleton()->m_pSettings->SetInt(KSETTINGS_SHADOWS_ENABLED,0);
            CMasterResourceManager::getSingleton()->m_pSettings->SetInt(KSETTINGS_SHADOW_RESOLUTION,128); break;
    case 1: CMasterResourceManager::getSingleton()->m_pSettings->SetInt(KSETTINGS_LIGHTING_ENABLED,1);
            CMasterResourceManager::getSingleton()->m_pSettings->SetInt(KSETTINGS_SHADOWS_ENABLED,0);
            CMasterResourceManager::getSingleton()->m_pSettings->SetInt(KSETTINGS_SHADOW_RESOLUTION,128); break;
    case 2: CMasterResourceManager::getSingleton()->m_pSettings->SetInt(KSETTINGS_LIGHTING_ENABLED,1);
            CMasterResourceManager::getSingleton()->m_pSettings->SetInt(KSETTINGS_SHADOWS_ENABLED,1);
            CMasterResourceManager::getSingleton()->m_pSettings->SetInt(KSETTINGS_SHADOW_RESOLUTION,128); break;
    case 3: CMasterResourceManager::getSingleton()->m_pSettings->SetInt(KSETTINGS_LIGHTING_ENABLED,1);
            CMasterResourceManager::getSingleton()->m_pSettings->SetInt(KSETTINGS_SHADOWS_ENABLED,1);
            CMasterResourceManager::getSingleton()->m_pSettings->SetInt(KSETTINGS_SHADOW_RESOLUTION,256); break;
    case 4: CMasterResourceManager::getSingleton()->m_pSettings->SetInt(KSETTINGS_LIGHTING_ENABLED,1);
            CMasterResourceManager::getSingleton()->m_pSettings->SetInt(KSETTINGS_SHADOWS_ENABLED,1);
            CMasterResourceManager::getSingleton()->m_pSettings->SetInt(KSETTINGS_SHADOW_RESOLUTION,512); break;
    case 5: CMasterResourceManager::getSingleton()->m_pSettings->SetInt(KSETTINGS_LIGHTING_ENABLED,1);
            CMasterResourceManager::getSingleton()->m_pSettings->SetInt(KSETTINGS_SHADOWS_ENABLED,1);
            CMasterResourceManager::getSingleton()->m_pSettings->SetInt(KSETTINGS_SHADOW_RESOLUTION,1024); break;
    }
    CMasterResourceManager::getSingleton()->m_pSoundManager->updateAudioLevels(sound,music,soundMute,musicMute);
    if (oldShadow != shadow) m_pResourceManager->getGameClient()->resetShadows(oldShadowsEnabled != 0);
    CGameClient* client = m_pResourceManager->getGameClient();
    if (client->getGameState() == static_cast<EGameState>(0)) client->m_cameraControl->m_cameras[0]->setFarClipDistance(180.0f);
    else if (CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_NETBOOK_MODE) == 1) client->m_cameraControl->m_cameras[0]->setFarClipDistance(45.0f);
    else client->m_cameraControl->m_cameras[0]->setFarClipDistance(90.0f);
    m_applyChanges = false;
    CMasterResourceManager::getSingleton()->m_pSettings->SaveSettings(L"");
    if ((CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_FSAA) == 1) != (oldFsaa == 1) ||
        (CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_VSYNCH) == 1) != (oldVsync == 1) ||
        (CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_RIMLIGHTS_ENABLED) == 1) != (oldRimlights == 1) ||
        (CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_ALLOW_HWSKINNING) == 1) != (oldSkinning == 1) ||
        (CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_NETBOOK_MODE) == 1) != (oldNetbook == 1)) {
        m_pGameUI->m_gap12FA = 1;
        m_pGameUI->closeAll();
    }
}
