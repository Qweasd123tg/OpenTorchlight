#include <CEGUIEventArgs.h>
#include <CEGUIInputEvent.h>
#include <CEGUIWindow.h>
#include "GameUI.h"
#include "Player.h"
#include "Quest.h"
#include "QuestDialog.h"
#include "QuestDialogMenu.h"
#include "QuestManager.h"
#include "QuestRewards.h"

bool CQuestDialogMenu::handle_MouseThrough(const CEGUI::EventArgs&)
{
    m_mouseThrough = false;
    return true;
}

const Ogre::Vector3& CQuestDialogMenu::getCameraOffset()
{
    return m_dialog ? m_dialog->m_cameraOffset : Ogre::Vector3::ZERO;
}

bool CQuestDialogMenu::acceptQuest(CBaseUnit* unit)
{
    if (!m_dialog || m_dialog->m_pQuest->m_questAccepted)
        return false;
    static_cast<CPlayer*>(m_pGameUI->getCharacter())->getQuestManager()->giveQuest(
        m_dialog->m_pQuest, unit ? unit : m_unit, true);
    broadcastEvent(static_cast<EMENU_TYPE>(0), static_cast<EMENU_EVENT>(3));
    broadcastAcceptedOrDeclined(true, unit);
    return true;
}

bool CQuestDialogMenu::handle_ExitButton(const CEGUI::EventArgs& event)
{
    if (m_unit)
        m_unit->BroadcastEvent(95);
    m_bUnknown32 = true;
    m_pGameUI->getCharacter()->setAIState(static_cast<EAIState>(2));
    if (m_acceptOnExit)
        acceptQuest(NULL);
    m_acceptOnExit = false;
    broadcastEvent(static_cast<EMENU_TYPE>(0), static_cast<EMENU_EVENT>(1));
    broadcastAcceptedOrDeclined(false, NULL);
    return true;
}

bool CQuestDialogMenu::handle_CloseButton(const CEGUI::EventArgs& event)
{
    if (static_cast<const CEGUI::MouseEventArgs&>(event).button != CEGUI::LeftButton)
        return true;
    if (m_unit)
        m_unit->BroadcastEvent(95);
    m_bUnknown32 = true;
    m_pGameUI->getCharacter()->setAIState(static_cast<EAIState>(2));
    if (m_acceptOnExit)
        acceptQuest(NULL);
    m_acceptOnExit = false;
    broadcastEvent(static_cast<EMENU_TYPE>(0), static_cast<EMENU_EVENT>(1));
    broadcastAcceptedOrDeclined(false, NULL);
    return CDropdownMenu::handle_CloseButton(event);
}

CQuestDialogMenu::~CQuestDialogMenu()
{
    m_unit = NULL;
}

bool CQuestDialogMenu::handle_MouseOver(const CEGUI::EventArgs& event)
{
    if (m_dialog)
    {
        int index = *static_cast<int*>(static_cast<const CEGUI::WindowEventArgs&>(event).window->getUserData());
        CQuest* quest = m_dialog->m_pQuest;
        if (quest)
        {
            TArrayList<CBaseUnit*>* items = quest->m_pQuestRewards->getRewardItems();
            if (index < static_cast<int>(items->size()))
                m_hoveredReward = (*items)[index];
        }
        m_mouseThrough = true;
    }
    return true;
}

bool CQuestDialogMenu::handle_MouseOut(const CEGUI::EventArgs& event)
{
    if (m_dialog)
    {
        int index = *static_cast<int*>(static_cast<const CEGUI::WindowEventArgs&>(event).window->getUserData());
        CQuest* quest = m_dialog->m_pQuest;
        if (quest)
        {
            TArrayList<CBaseUnit*>* items = quest->m_pQuestRewards->getRewardItems();
            if (index < static_cast<int>(items->size()))
            {
                if (m_hoveredReward == (*items)[index])
                    m_hoveredReward = NULL;
            }
        }
    }
    return true;
}

#include "StringTranslate.h"
CQuestDialogMenu::CQuestDialogMenu(CGameUI& ui, CSettings& settings, Ogre::SceneManager* scene, CEGUI::Window* parent, CResourceManager* resources)
    : CDropdownMenu(ui, settings, scene, parent, resources, 1), m_unit(NULL), m_dialogWindow(NULL), m_promptWindow(NULL), m_acceptWindow(NULL), m_declineWindow(NULL), m_rewardWindow(NULL), m_rewardTextWindow(NULL), m_detailWindow(NULL), m_iconWindow(NULL), m_iconParent(NULL), m_dialog(NULL), m_textIndex(0), m_textLength(0), m_dialogName(), m_displayedCharacters(0), m_hoveredReward(NULL), m_mouseThrough(false), m_dialogActive(true), m_acceptOnExit(false), m_resultBroadcast(false), m_safeOwner(), m_textSpeed(1.0f)
{
    static std::wstring g_Dialog;
    if (g_Dialog.empty())
        g_Dialog = CStringTranslate::getSinglton()->getTranslateString(L"Dialog");
    setTitle(g_Dialog);
    createMenus();
}
#include "BaseUnit.h"

void CQuestDialogMenu::broadcastAcceptedOrDeclined(bool accepted, CBaseUnit* unit)
{
    if (!unit) unit = m_unit;
    if (!unit) return;
    if (m_dialog && !m_resultBroadcast) {
        m_resultBroadcast = true;
        unit->BroadcastEvent(accepted ? 93 : 94);
    }
    unit->BroadcastEvent(92);
}

#include "GameClient.h"
#include "Item.h"
void CQuestDialogMenu::setOpen(bool open)
{
    if (m_bUnknown30 != open) m_pGameUI->setInteractiveMenuVisible(open);
    if (m_bUnknown30) {
        if (!open) {
            if (m_dialog) m_dialog->stopDialogSound();
            CGameClient* client = m_pGameUI->getGameClient();
            client->m_selectedItem.setObject(NULL); client->m_targetItem.setObject(NULL);
            client->m_selectedCharacter.setObject(NULL); client->m_targetCharacter.setObject(NULL);
            static_cast<CEGUI::Window*>(m_pUnknown10)->removeChildWindow(static_cast<CEGUI::Window*>(m_pUnknown18));
            m_bUnknown31 = true; m_hoveredReward = NULL;
            if (m_unit) m_unit->setEnabled(m_dialogActive);
            m_unit = NULL;
        }
    } else if (open) {
        m_pDynamicPropertyFile->GetInt(KSETTINGS_RES_WIDTH);
        m_pDynamicPropertyFile->GetInt(KSETTINGS_RES_HEIGHT);
        static_cast<CEGUI::Window*>(m_pUnknown20)->setPosition(CEGUI::UVector2(CEGUI::UDim(0,0),CEGUI::UDim(0,0)));
        static_cast<CEGUI::Window*>(m_pUnknown10)->addChildWindow(static_cast<CEGUI::Window*>(m_pUnknown18));
        static_cast<CEGUI::Window*>(m_pUnknown18)->moveToBack();
    }
    m_bUnknown30 = open; m_resultBroadcast = false;
}

#include <CEGUI.h>
#include "Equipment.h"
#include "StringUtilities.h"
#include "Settings.h"
#include "GameVariables.h"
#include "MasterResourceManager.h"
#include "SoundBankDataInformation.h"
#include "SoundData.h"
#include <OgreEntity.h>
#include <OgreSkeletonInstance.h>
#include <OgreBone.h>

void CQuestDialogMenu::setSlotIcon(int index, CEquipment* item)
{
    if (!m_rewardSlots[index]) { m_overlayWindow->moveToFront(); m_rewardContainer->moveToFront(); return; }
    if (!item) {
        m_rewardCounts[index]->setVisible(false);
        m_rewardIcons[index]->setProperty("Image", "");
        m_rewardIcons[index]->setSize(m_rewardSlots[index]->getSize());
        m_rewardRarity[index]->setProperty("Image", "");
        m_rewardRarity[index]->setSize(m_rewardSlots[index]->getSize());
        m_rewardSlots[index]->setProperty("Image", "");
        m_overlayWindow->moveToFront(); m_rewardContainer->moveToFront(); return;
    }
    CEGUI::Window* icon = item->m_pIconWindow;
    if (!icon) {
        item->createIcon(*m_pGameUI, false);
        icon = item->m_pIconWindow;
        if (icon) { icon->setMutedState(true); icon->setMousePassThroughEnabled(true); }
    }
    if (icon) {
        if (icon->getParent()) icon->getParent()->removeChildWindow(icon);
        m_rewardSlots[index]->addChildWindow(icon);
    }
    if (!item->m_bUnknown348 || !item->m_iSocketCount || !m_rewardSlots[index]->getParent()->isVisible(false))
        m_rewardIcons[index]->setProperty("Image", "");
    else {
        if (static_cast<unsigned>(item->m_iSocketCount) > 1)
            m_rewardIcons[index]->setProperty("Image", CEGUI::PropertyHelper::imageToString(&m_uiImages->getImage("twosocketglow")));
        else if (item->m_iSocketCount == 1)
            m_rewardIcons[index]->setProperty("Image", CEGUI::PropertyHelper::imageToString(&m_uiImages->getImage("onesocketglow")));
        m_rewardIcons[index]->moveToFront();
    }
    if (m_rewardCounts[index]) {
        if (item->m_iUnknown238 <= 1) m_rewardCounts[index]->setVisible(false);
        else {
            m_rewardCounts[index]->setVisible(true);
            std::string text = "x" + STRINGS::GetValueAsString(item->m_iUnknown238);
            m_rewardCounts[index]->setText(CEGUI::String(reinterpret_cast<const unsigned char*>(text.c_str())));
        }
    }
    float y = 0.0f;
    if (static_cast<unsigned>(item->m_iSocketCount) > 1)
        y += m_rewardSlots[index]->getSize().d_y.asAbsolute(0.0f) * -0.19f;
    if (m_rewardSlots[index]->getParent()->isVisible(false) && item->m_SocketedEquipment.size()) {
        for (unsigned int i = 0; i < item->m_SocketedEquipment.size(); ++i) {
            CEquipment* socketed = item->m_SocketedEquipment[i];
            CEGUI::Window* socketIcon = socketed->m_pIconWindow;
            if (!socketIcon) {
                socketed->createIcon(*m_pGameUI, false);
                socketIcon = socketed->m_pIconWindow;
                if (socketIcon) { socketIcon->setMutedState(true); socketIcon->setMousePassThroughEnabled(true); }
            }
            if (socketIcon) {
                if (socketIcon->getParent()) socketIcon->getParent()->removeChildWindow(socketIcon);
                m_rewardContainer->addChildWindow(socketIcon);
                socketIcon->setPosition(CEGUI::UVector2(CEGUI::UDim(0,0),CEGUI::UDim(0,y)));
                socketIcon->setSize(m_rewardSlots[index]->getSize());
                socketIcon->moveToFront();
                socketIcon->setMousePassThroughEnabled(true);
            }
            y += m_rewardSlots[index]->getSize().d_y.asAbsolute(0.0f) * 0.4f;
        }
    }
    if (item->ISA(static_cast<UNITTYPES::EUNITTYPES>(0x36)))
        m_rewardRarity[index]->setProperty("Image", CEGUI::PropertyHelper::imageToString(&m_uiImages->getImage("goldslotglow")));
    else if (item->isMagical()) {
        if (item->ISA(static_cast<UNITTYPES::EUNITTYPES>(0x37)))
            m_rewardRarity[index]->setProperty("Image", CEGUI::PropertyHelper::imageToString(&m_uiImages->getImage("blueslotglow")));
        else m_rewardRarity[index]->setProperty("Image", CEGUI::PropertyHelper::imageToString(&m_uiImages->getImage("greenslotglow")));
    } else m_rewardRarity[index]->setProperty("Image", "");
    m_rewardSlots[index]->setProperty("Image", "");
    if (icon) {
        icon->setPosition(CEGUI::UVector2(CEGUI::UDim(0,0),CEGUI::UDim(0,1)));
        icon->setPosition(CEGUI::UVector2(CEGUI::UDim(0,0),CEGUI::UDim(0,0)));
        icon->setSize(m_rewardSlots[index]->getSize());
        icon->moveToFront();
        icon->update(0.001f);
    }
    m_overlayWindow->moveToFront(); m_rewardContainer->moveToFront();
}

void CQuestDialogMenu::updateTextDisplay(float elapsed)
{
    if (m_safeOwner.getObject()) return;
    if (m_declineWindow->getText() != m_dialogName)
        m_declineWindow->setText(CEGUI::String(reinterpret_cast<const unsigned char*>(m_dialogName.c_str())));
    if (m_textLength > 0.0f && m_textLength > m_textIndex) {
        m_textIndex += elapsed;
        float height = m_declineWindow->getParent()->getHeight().asAbsolute(0.0f) + 50.0f;
        float y = height - (m_textIndex / m_textLength) * height;
        m_declineWindow->setPosition(CEGUI::UVector2(CEGUI::UDim(0,0),CEGUI::UDim(0,y)));
    } else {
        m_declineWindow->getParent()->getHeight();
        m_declineWindow->setPosition(CEGUI::UVector2(CEGUI::UDim(0,0),CEGUI::UDim(0,0)));
    }
}

#include "UnitResourceList.h"
#include "Level.h"
#include "Item.h"
void CQuestDialogMenu::updateDialogTags()
{
    TArrayList<std::pair<std::string, std::string> > tags(10);
    getTags(m_dialogName, tags);
    CCharacter* owner = dynamic_cast<CCharacter*>(m_unit);
    for (unsigned int i = 0; i < tags.size(); ++i) {
        if (!owner || tags[i].first.compare("LOOKAT")) continue;
        if (!tags[i].second.compare("PLAYER")) {
            owner->setTarget(m_pResourceManager->getGameClient()->getPlayer());
            continue;
        }
        if (!owner->getResourceManager() || !owner->getResourceManager()->getLevel()) continue;
        std::wstring name = STRINGS::StringConvertToWide(tags[i].second.c_str(), 5000);
        CDataGroup* group = m_pResourceManager->getMasterResourceList()->getDataGroupByObjectName(name);
        if (!group) continue;
        CBaseUnit* unit = owner->getLevel()->getBaseUnitByDataGroup(group);
        if (!unit) continue;
        CCharacter* character = dynamic_cast<CCharacter*>(unit);
        if (character) owner->setTarget(character);
        else {
            CItem* item = dynamic_cast<CItem*>(unit);
            if (item) owner->setTargetItem(item);
        }
    }
}

#include "TextEvent.h"
#include "SoundManager.h"
#include "EmptyStrings.h"
void CQuestDialogMenu::update(float elapsed)
{
    bool volumeChanged = false;
    if (m_bUnknown30 && m_dialog && !m_dialog->m_sSoundName.empty()) {
        if (m_textSpeed > 0.25f) {
            float value = m_textSpeed - elapsed;
            m_textSpeed = value < 0.25f ? 0.25f : value;
            volumeChanged = true;
        }
    } else if (m_textSpeed < 1.0f) {
        float value = m_textSpeed + elapsed;
        m_textSpeed = value > 1.0f ? 1.0f : value;
        volumeChanged = true;
    }
    if (volumeChanged) {
        float sound = CMasterResourceManager::getSingleton()->m_pSettings->GetFloat(KSETTINGS_F_SOUNDVOLUME);
        float music = CMasterResourceManager::getSingleton()->m_pSettings->GetFloat(KSETTINGS_F_MUSICVOLUME);
        bool soundMute = CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_SOUNDMUTE) != 0;
        bool musicMute = CMasterResourceManager::getSingleton()->m_pSettings->GetInt(KSETTINGS_MUSICMUTE) != 0;
        CMasterResourceManager::getSingleton()->m_pSoundManager->updateAudioLevels(sound, music * m_textSpeed, soundMute, musicMute);
    }
    if (m_safeOwner.getObject() && static_cast<CTextEvent*>(m_safeOwner.getObject())->m_Value68 <= 250.0f) {
        onClick(static_cast<ELayoutFunction>(10), EMPTY_WSTRING);
        m_unit = NULL;
        m_safeOwner.setObject(NULL);
    }
    if (m_bUnknown30 || !m_bUnknown31) {
        if (m_pGameUI->m_mouse.buttonHeld(static_cast<EMouseButton>(0)) || m_pGameUI->m_mouse.buttonHeld(static_cast<EMouseButton>(1)))
            updateTextDisplay(elapsed * 10.0f);
        else if (m_pGameUI->m_mouse.buttonPressed(static_cast<EMouseButton>(0)) || m_pGameUI->m_mouse.buttonPressed(static_cast<EMouseButton>(1)))
            updateTextDisplay(m_textLength);
        else updateTextDisplay(elapsed);
        bool wasClosed = m_bUnknown31;
        CDropdownMenu::update(elapsed);
        if (!wasClosed && m_bUnknown31) {
            if (m_dialog) m_dialog->stopDialogSound();
            m_dialog = NULL;
            if (m_unit) m_unit->setEnabled(m_dialogActive);
            m_unit = NULL;
        }
    }
}

#include "FileSystem.h"
void CQuestDialogMenu::createMenus()
{
    m_uiImages = CEGUI::ImagesetManager::getSingleton().getImageset("UIIcons");
    CFileInfo info;
    CFileSystem::getSingleton()->getFileInfo(L"media/ui/questdialogmenu.layout", info, false, true, false);
    CEGUI::WindowManager& wm = CEGUI::WindowManager::getSingleton();
    CEGUI::Window* layout = wm.loadWindowLayout(CEGUI::String(info.m_sResourceName), true);
    m_acceptWindow = layout->recursiveChildSearch("Decline");
    m_promptWindow = layout->recursiveChildSearch("Accept");
    m_dialogWindow = layout->recursiveChildSearch("Ok");
    m_declineWindow = layout->recursiveChildSearch("DialogText");
    m_detailWindow = layout->recursiveChildSearch("Portrait");
    m_rewardWindow = layout->recursiveChildSearch("RewardGold");
    m_rewardTextWindow = layout->recursiveChildSearch("RewardXP");
    m_windowF8 = layout->recursiveChildSearch("RewardFame");
    m_iconWindow = layout->recursiveChildSearch("RewardGoldBox");
    m_iconParent = layout->recursiveChildSearch("RewardXPBox");
    m_window118 = layout->recursiveChildSearch("RewardFameBox");
    m_pGameUI->convertToScreenScale(layout, false);
    m_pGameUI->mapToFunctions(layout);
    CDropdownMenu::mapEventHandlers(layout);
    static_cast<CEGUI::Window*>(m_pUnknown20)->addChildWindow(layout);
    for (int i = 0; i < 4; ++i) m_rewardIDs[i] = i;
    m_rewardContainer = wm.createWindow("DefaultWindow", "QuestRewardSockets", "");
    layout->addChildWindow(m_rewardContainer);
    m_rewardContainer->setSize(layout->getSize());
    m_rewardContainer->setProperty("RiseOnClick", "False");
    m_rewardContainer->setPosition(CEGUI::UVector2(CEGUI::UDim(0,0), CEGUI::UDim(0,0)));
    m_rewardContainer->setMousePassThroughEnabled(true);
    m_rewardContainer->moveToFront();
    m_overlayWindow = wm.createWindow("DefaultWindow", "QuestRewardSocketsO", "");
    layout->addChildWindow(m_overlayWindow);
    m_overlayWindow->setSize(layout->getSize());
    m_overlayWindow->setProperty("RiseOnClick", "False");
    m_overlayWindow->setPosition(CEGUI::UVector2(CEGUI::UDim(0,0), CEGUI::UDim(0,0)));
    m_overlayWindow->setMousePassThroughEnabled(true);
    m_overlayWindow->moveToFront();
    for (int i = 0; i < 3; ++i) {
        m_rewardBackgrounds[i] = layout->recursiveChildSearch(("ItemBkg" + STRINGS::GetValueAsString(i + 1)).c_str());
        CEGUI::Window* slot = layout->recursiveChildSearch(("ItemSlot" + STRINGS::GetValueAsString(i + 1)).c_str());
        slot->setRiseOnClickEnabled(false);
        slot->moveToFront();
        slot->setWantsMultiClickEvents(false);
        slot->setUserData(&m_rewardIDs[i]);
        slot->subscribeEvent(CEGUI::Window::EventMouseEnters, CEGUI::Event::Subscriber(&CQuestDialogMenu::handle_MouseOver, this));
        slot->subscribeEvent(CEGUI::Window::EventMouseMove, CEGUI::Event::Subscriber(&CQuestDialogMenu::handle_MouseOver, this));
        slot->subscribeEvent(CEGUI::Window::EventMouseLeaves, CEGUI::Event::Subscriber(&CQuestDialogMenu::handle_MouseOut, this));
        slot->moveToFront();
        m_rewardSlots[i] = slot;
        m_rewardCounts[i] = NULL;
        CEGUI::Window* count = wm.createWindow("GuiLook/StaticText", STRINGS::uniqueName("gui_"), "");
        m_rewardCounts[i] = count;
        count->setFont("Serif");
        count->setSize(slot->getSize());
        CEGUI::UVector2 position = slot->getPosition();
        count->setProperty("HorzTextFormatting", "RightAligned");
        count->setProperty("VertFormatting", "BottomAligned");
        count->setMousePassThroughEnabled(true);
        count->setPosition(position);
        slot->getParent()->addChildWindow(count);
        count->setText("");
        count->setProperty("TextColour", CEGUI::PropertyHelper::colourToString(CEGUI::colour(1,1,1,1)));
        count->setAlwaysOnTop(true);
        CEGUI::Window* rarity = wm.createWindow("GuiLook/StaticImage", STRINGS::uniqueName("gui_"), "");
        m_rewardBackgrounds[i]->addChildWindow(rarity);
        rarity->setRiseOnClickEnabled(false);
        rarity->setWantsMultiClickEvents(false);
        rarity->setMousePassThroughEnabled(true);
        rarity->setMutedState(true);
        rarity->setPosition(slot->getPosition());
        rarity->setSize(slot->getSize());
        m_rewardRarity[i] = rarity;
        CEGUI::Window* socket = wm.createWindow("GuiLook/StaticImage", STRINGS::uniqueName("gui_"), "");
        m_overlayWindow->addChildWindow(socket);
        socket->setRiseOnClickEnabled(false);
        socket->setWantsMultiClickEvents(false);
        socket->setMousePassThroughEnabled(true);
        socket->setMutedState(true);
        const CEGUI::UVector2& backgroundPosition = m_rewardBackgrounds[i]->getPosition();
        const CEGUI::UVector2& slotPosition = slot->getPosition();
        socket->setPosition(backgroundPosition + slotPosition);
        socket->setSize(slot->getSize());
        m_rewardIcons[i] = socket;
    }
}

#include "SteamStats.h"
bool CQuestDialogMenu::onClick(ELayoutFunction function, std::wstring)
{
    CBaseUnit* unit = m_unit;
    if (unit) unit->setEnabled(m_dialogActive);
    m_unit = NULL;
    if (!m_dialog) return true;
    if (!m_safeOwner.getObject()) m_dialog->stopDialogSound();
    bool sendEnd = true;
    bool decline = function == static_cast<ELayoutFunction>(8);
    if (function == static_cast<ELayoutFunction>(9)) {
        if (m_dialog && m_dialog->m_iDialogType != 3) {
            CQuest* quest = m_dialog->m_pQuest;
            if (quest->getQuestDetails() != EMPTY_WSTRING && !quest->m_bUnknown28) {
                CQuestManager* manager = static_cast<CPlayer*>(m_pGameUI->getCharacter())->getQuestManager();
                int count = 0;
                for (int i = 0; i < static_cast<int>(manager->m_Unknown18.size()); ++i)
                    if (manager->m_Unknown18[i]->getQuestDetails() != EMPTY_WSTRING) ++count;
                if (count > 5) {
                    static std::wstring g_Quest;
                    if (g_Quest.empty()) g_Quest = CStringTranslate::getSinglton()->getTranslateString(L"Quest");
                    static std::wstring g_QuestLogFull;
                    if (g_QuestLogFull.empty()) g_QuestLogFull = CStringTranslate::getSinglton()->getTranslateString(L"Your quest log is full!");
                    m_pGameUI->openModalDialog(g_Quest, g_QuestLogFull, false);
                    decline = true;
                }
            }
        }
        if (!decline) {
            broadcastEvent(static_cast<EMENU_TYPE>(0), static_cast<EMENU_EVENT>(3));
            m_pGameUI->getCharacter()->setAIState(static_cast<EAIState>(2));
            m_bUnknown32 = true;
            acceptQuest(unit);
            sendEnd = false;
            if (m_dialog) m_dialog->giveOrRemoveItems(unit);
        }
    } else if (function == static_cast<ELayoutFunction>(10)) {
        broadcastEvent(static_cast<EMENU_TYPE>(0), static_cast<EMENU_EVENT>(2));
        m_pGameUI->getCharacter()->setAIState(static_cast<EAIState>(2));
        m_bUnknown32 = true;
        if (m_dialog) {
            if (m_dialog->m_iDialogType == 3) {
                if (unit) {
                    unit->BroadcastEvent(95); unit->BroadcastEvent(93); unit->BroadcastEvent(92);
                    if (unit->getName().compare(L"Male1") == 0)
                        CSteamStats::getSingleton()->incrementStat(static_cast<ESTATS>(25), 1);
                    else if (unit->getName().compare(L"Gar") == 0)
                        CSteamStats::getSingleton()->incrementStat(static_cast<ESTATS>(26), 1);
                }
                static_cast<CPlayer*>(m_pGameUI->getCharacter())->getQuestManager()->completeQuest(m_dialog->m_pQuest);
            }
            if (m_dialog) m_dialog->giveOrRemoveItems(unit);
        }
    } else if (!decline) {
        if (m_dialog) m_dialog->giveOrRemoveItems(unit);
    }
    if (decline) {
        broadcastEvent(static_cast<EMENU_TYPE>(0), static_cast<EMENU_EVENT>(4));
        m_pGameUI->getCharacter()->setTarget(NULL);
        m_pGameUI->getCharacter()->setAIState(static_cast<EAIState>(2));
        m_dialog->m_bDialogInitialized = false;
        m_bUnknown32 = true;
        broadcastAcceptedOrDeclined(false, unit);
        sendEnd = false;
    }
    if (unit) { unit->BroadcastEvent(95); if (sendEnd) unit->BroadcastEvent(92); }
    CCharacter* player = m_pGameUI->getCharacter();
    if (player && player->getResourceManager() && player->getResourceManager()->getLevel()) {
        player->getResourceManager()->getLevel()->updateNPCIcons();
        m_pGameUI->getCharacter()->getLevel()->updateAutomapIcons();
    }
    setOpen(false);
    m_dialog = NULL;
    return true;
}

#include <OgreLogManager.h>
void CQuestDialogMenu::setNPC(CBaseUnit* unit, bool showFloaty, CQuest* requestedQuest)
{
    if (unit && unit->getName().compare(L"Horse") == 0)
        CSteamStats::getSingleton()->incrementStat(static_cast<ESTATS>(27), 1);
    m_pGameUI->returnDraggedItem();
    if (m_unit) m_unit->setEnabled(m_dialogActive);
    m_unit = NULL;
    if (m_dialog) m_dialog->stopDialogSound();
    m_dialog = NULL;
    m_unit = unit;
    m_dialogActive = unit ? unit->getEnabled() : true;
    if (!m_promptWindow || !m_acceptWindow || !m_dialogWindow) {
        if (m_unit) m_unit->setEnabled(m_dialogActive);
        m_unit = NULL;
        return;
    }
    m_promptWindow->setVisible(false); m_acceptWindow->setVisible(false); m_dialogWindow->setVisible(false);
    m_promptWindow->setEnabled(false); m_acceptWindow->setEnabled(false); m_dialogWindow->setEnabled(false);
    if (!m_pGameUI->getCharacter() && static_cast<CPlayer*>(m_pGameUI->getCharacter())->getQuestManager()
        && m_unit && m_unit->getDataGroup()) {
        m_unit->setEnabled(m_dialogActive); m_unit = NULL; return;
    }
    std::wstring portrait = m_unit->getDataGroup()->GetDataValue(L"PORTRAIT", EMPTY_WSTRING);
    bool haveImage = false;
    if (portrait != EMPTY_WSTRING) {
        std::string text = STRINGS::StringConvertToUTF8(std::wstring(portrait.c_str()));
        const CEGUI::Image* image = m_pGameUI->getImageFromImageSet(reinterpret_cast<const unsigned char*>(text.c_str()));
        if (image) { m_detailWindow->setProperty("Image", CEGUI::PropertyHelper::imageToString(image)); haveImage = true; }
    }
    m_detailWindow->setVisible(haveImage);
    if (requestedQuest) m_dialog = reinterpret_cast<CQuestDialog*>(requestedQuest->getQuestDialog(m_unit));
    if (!m_dialog) {
        TArrayList<CQuestDialog*> dialogs(10);
        static_cast<CPlayer*>(m_pGameUI->getCharacter())->getQuestManager()->getDialogsForNPC(dialogs, m_unit, true);
        if (!dialogs.size()) {
            std::wstring message = L"Error occured getting NPC dialog for character : " + m_unit->getName();
            Ogre::LogManager::getSingleton().logMessage(STRINGS::StringConvertToUTF8(message), Ogre::LML_CRITICAL, false);
            m_bUnknown32 = true;
            m_unit->BroadcastEvent(95); m_unit->BroadcastEvent(93); m_unit->BroadcastEvent(92);
            broadcastEvent(static_cast<EMENU_TYPE>(0), static_cast<EMENU_EVENT>(1));
            if (m_unit) m_unit->setEnabled(m_dialogActive);
            m_unit = NULL;
            return;
        }
        m_dialog = dialogs[0];
    }
    if (!m_dialog) return;
    CQuest* quest = m_dialog->m_pQuest;
    if (!quest) return;
    for (int i = 0; i < 3; ++i) {
        m_rewardBackgrounds[i]->setVisible(false);
        if (m_rewardSlots[i]->getChildCount()) m_rewardSlots[i]->removeChildWindow(m_rewardSlots[i]->getChildAtIdx(0));
        m_rewardIcons[i]->setProperty("Image", "");
    }
    while (m_rewardContainer->getChildCount()) m_rewardContainer->removeChildWindow(m_rewardContainer->getChildAtIdx(0));
    m_acceptOnExit = quest->m_bUnknown28;
    m_dialog->playDialogSound();
    bool floaty = m_dialog->m_bFloatyText || showFloaty;
    if (!floaty) {
        int type = m_dialog->m_iDialogType;
        if (type == 1) {
            m_acceptWindow->setVisible(true); m_promptWindow->setVisible(true);
            m_acceptWindow->setEnabled(true); m_promptWindow->setEnabled(true);
        } else if (type == 2 || type == 3 || type == 4) {
            m_dialogWindow->setVisible(true); m_dialogWindow->setEnabled(true);
        }
    }
    m_displayedCharacters = 0;
    m_dialogName = STRINGS::StringConvertToUTF8(m_dialog->getDialog(false));
    m_textIndex = 0.0f;
    float duration = float(m_dialogName.size()) * 0.015f;
    m_textLength = duration > 5.0f ? duration : 5.0f;
    updateTextDisplay(0.0f);
    m_declineWindow->setText("");
    static std::wstring g_GP;
    if (g_GP.empty()) g_GP = CStringTranslate::getSinglton()->getTranslateString(L"GP");
    static std::wstring g_XP;
    if (g_XP.empty()) g_XP = CStringTranslate::getSinglton()->getTranslateString(L"XP");
    static std::wstring g_Fame;
    if (g_Fame.empty()) g_Fame = CStringTranslate::getSinglton()->getTranslateString(L"Fame");
    if (quest->getQuestRewardGold() > 0) {
        m_iconWindow->setVisible(true);
        std::wstring number = STRINGS::GetValueAsWString(quest->getQuestRewardGold());
        std::string text = STRINGS::StringConvertToUTF8(g_GP + L":" + number);
        m_rewardWindow->setText(CEGUI::String(reinterpret_cast<const unsigned char*>(text.c_str())));
    } else m_iconWindow->setVisible(false);
    if (quest->getQuestRewardXP() > 0) {
        m_iconParent->setVisible(true);
        std::wstring number = STRINGS::GetValueAsWString(quest->getQuestRewardXP());
        std::string text = STRINGS::StringConvertToUTF8(g_XP + L":" + number);
        m_rewardTextWindow->setText(CEGUI::String(reinterpret_cast<const unsigned char*>(text.c_str())));
    } else m_iconParent->setVisible(false);
    if (quest->getQuestRewardFame() > 0) {
        m_window118->setVisible(true);
        std::wstring number = STRINGS::GetValueAsWString(quest->getQuestRewardFame());
        std::string text = STRINGS::StringConvertToUTF8(g_Fame + L":" + number);
        m_windowF8->setText(CEGUI::String(reinterpret_cast<const unsigned char*>(text.c_str())));
    } else m_window118->setVisible(false);
    if (quest->m_pQuestRewards) {
        TArrayList<CBaseUnit*>* rewards = quest->m_pQuestRewards->getRewardItems();
        for (unsigned int i = 0; i < rewards->size() && i < 3; ++i) {
            m_rewardBackgrounds[i]->setVisible(true);
            setSlotIcon(i, static_cast<CEquipment*>((*rewards)[i]));
        }
    }
    if (m_acceptOnExit && m_acceptWindow->isVisible(false)) {
        m_acceptWindow->setVisible(false); m_acceptWindow->setEnabled(false);
    }
    m_safeOwner.setObject(NULL);
    if (!floaty) {
        m_unit->setEnabled(false);
        setOpen(true);
    } else {
        CEGUI::colour first(1,1,1,1), second(1,1,1,1);
        Ogre::Vector3 position = m_unit->getPosition(true);
        position = Ogre::Vector3(position.x + 0.0f, position.y + 1.5f, position.z + 0.0f);
        CTextEvent* event = m_pGameUI->getTextEventObject(position, m_dialogName, 1.25f, 255.0f, first, second, true);
        m_safeOwner.setObject(event);
        event->m_Value60 = 0.5f;
        if (m_dialog) m_dialog->giveOrRemoveItems(m_unit);
    }
    m_dialog->m_bDialogInitialized = true;
    if (m_dialog->m_bLookAtPlayer && m_unit) {
        CCharacter* character = dynamic_cast<CCharacter*>(m_unit);
        if (character) character->setTarget(m_pGameUI->getCharacter());
    }
    updateDialogTags();
    m_bUnknown32 = false;
}
