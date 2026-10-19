#include <CEGUIEventArgs.h>
#include <CEGUIInputEvent.h>
#include <CEGUIWindow.h>
#include "Character.h"
#include "QuestMenu.h"

void CQuestMenu::setOwner(CCharacter* owner)
{
    m_owner = owner;
}

bool CQuestMenu::handle_CloseButton(const CEGUI::EventArgs& event)
{
    if (static_cast<const CEGUI::MouseEventArgs&>(event).button == CEGUI::LeftButton)
        m_requestClose = true;
    return true;
}

bool CQuestMenu::handle_MouseThrough(const CEGUI::EventArgs&)
{
    m_mouseThrough = false;
    return true;
}

bool CQuestMenu::handle_QuestClick(const CEGUI::EventArgs& event)
{
    CEGUI::Window* window = static_cast<const CEGUI::WindowEventArgs&>(event).window;
    if (window && window->getID() != m_selectedQuestID) {
        m_selectedQuestID = window->getID();
        m_selectedQuestChanged = true;
    }
    return true;
}

bool CQuestMenu::onClick(ELayoutFunction function)
{
    if (m_allowAbandon && function == static_cast<ELayoutFunction>(8)) abandonQuest();
    return true;
}

bool CQuestMenu::processInput(void*,float,bool capture)
{
    if (capture) {
        if (m_requestClose) {
            setOpen(false);
            m_requestClose = false;
            return false;
        }
    } else m_hoveredReward = NULL;
    return true;
}

#include "Player.h"
#include "Quest.h"
#include "QuestManager.h"
#include "QuestRewards.h"

bool CQuestMenu::handle_onClick(const CEGUI::EventArgs& event)
{
    const CEGUI::MouseEventArgs& mouse = static_cast<const CEGUI::MouseEventArgs&>(event);
    CEGUI::Window* window = mouse.window;
    if (mouse.button == CEGUI::LeftButton && window)
        return onClick(*static_cast<ELayoutFunction*>(window->getUserData()));
    return true;
}

bool CQuestMenu::handle_MouseOver(const CEGUI::EventArgs& event)
{
    CEGUI::Window* window = static_cast<const CEGUI::WindowEventArgs&>(event).window;
    if (window && m_owner) {
        int reward = *static_cast<int*>(window->getUserData());
        CQuestManager* manager = static_cast<CPlayer*>(m_owner)->getQuestManager();
        if (manager && m_selectedQuestIndex < static_cast<int>(reinterpret_cast<TArrayList<CQuest*>&>(manager->m_Unknown18).size())) {
            CQuest* quest = reinterpret_cast<TArrayList<CQuest*>&>(manager->m_Unknown18)[m_selectedQuestIndex];
            TArrayList<CBaseUnit*>* items = quest->m_pQuestRewards->getRewardItems();
            if (reward < static_cast<int>(items->size())) m_hoveredReward = (*items)[reward];
        }
        m_mouseThrough = true;
    }
    return true;
}

bool CQuestMenu::handle_MouseOut(const CEGUI::EventArgs& event)
{
    CEGUI::Window* window = static_cast<const CEGUI::WindowEventArgs&>(event).window;
    if (window && m_owner) {
        int reward = *static_cast<int*>(window->getUserData());
        CQuestManager* manager = static_cast<CPlayer*>(m_owner)->getQuestManager();
        if (manager && m_selectedQuestIndex < static_cast<int>(reinterpret_cast<TArrayList<CQuest*>&>(manager->m_Unknown18).size())) {
            CQuest* quest = reinterpret_cast<TArrayList<CQuest*>&>(manager->m_Unknown18)[m_selectedQuestIndex];
            TArrayList<CBaseUnit*>* items = quest->m_pQuestRewards->getRewardItems();
            if (reward < static_cast<int>(items->size()) && m_hoveredReward == (*items)[reward])
                m_hoveredReward = NULL;
        }
    }
    return true;
}

#include "GenericModel.h"
#include "SoundBank.h"
CQuestMenu::~CQuestMenu()
{
    if (m_model) { delete m_model; m_model = NULL; }
    if (m_soundBank) { delete m_soundBank; m_soundBank = NULL; }
}

void CQuestMenu::abandonQuest()
{
    CQuestManager* manager = static_cast<CPlayer*>(m_owner)->getQuestManager();
    if (!manager) return;
    unsigned int visible = 0;
    for (int i = 0; i < static_cast<int>(reinterpret_cast<TArrayList<CQuest*>&>(manager->m_Unknown18).size()); ++i) {
        if (!reinterpret_cast<TArrayList<CQuest*>&>(manager->m_Unknown18)[i]->getQuestDetails().empty()) {
            if (visible == m_selectedQuestID && reinterpret_cast<TArrayList<CQuest*>&>(manager->m_Unknown18)[i]->m_bUnknown208) {
                m_soundBank->playSample(35, NULL, 0.0f, 0.0f, false);
                manager->removeQuest(reinterpret_cast<TArrayList<CQuest*>&>(manager->m_Unknown18)[i], true);
                updateLayout(); return;
            }
            ++visible;
        }
    }
}

void CQuestMenu::mapEventHandlers(CEGUI::Window* window)
{
    int count = static_cast<int>(window->getChildCount());
    for (int i = 0; i < count; ++i)
        mapEventHandlers(window->getChildAtIdx(i));
    bool clickable = false;
    if (window->isPropertyPresent("onClick"))
        clickable = !window->getProperty("onClick").empty();
    if (clickable) {
        window->setWantsMultiClickEvents(true);
        window->subscribeEvent(CEGUI::Window::EventMouseButtonDown, CEGUI::Event::Subscriber(&CQuestMenu::handle_onClick, this));
        window->subscribeEvent(CEGUI::Window::EventMouseDoubleClick, CEGUI::Event::Subscriber(&CQuestMenu::handle_onClick, this));
    }
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

void CQuestMenu::setSlotIcon(int index, CEquipment* item)
{
    if (!m_rewardSlots[index]) {  return; }
    if (!item) {
        m_rewardCounts[index]->setVisible(false);
        m_rewardIcons[index]->setProperty("Image", "");
        m_rewardIcons[index]->setSize(m_rewardSlots[index]->getSize());
        m_rewardRarity[index]->setProperty("Image", "");
        m_rewardRarity[index]->setSize(m_rewardSlots[index]->getSize());
        m_rewardSlots[index]->setProperty("Image", "");
         return;
    }
    CEGUI::Window* icon = item->m_pIconWindow;
    if (!icon) {
        item->createIcon(*m_gameUI, false);
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
                socketed->createIcon(*m_gameUI, false);
                socketIcon = socketed->m_pIconWindow;
                if (socketIcon) { socketIcon->setMutedState(true); socketIcon->setMousePassThroughEnabled(true); }
            }
            if (socketIcon) {
                if (socketIcon->getParent()) socketIcon->getParent()->removeChildWindow(socketIcon);
                m_listContent->addChildWindow(socketIcon);
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

}

void CQuestMenu::setOpen(bool opened)
{
    if (!m_allowAbandon && opened) {
        m_soundBank->playSample(22, NULL, 0.0f, 0.0f, false);
        m_settings->GetInt(KSETTINGS_RES_WIDTH);
        m_settings->GetInt(KSETTINGS_RES_HEIGHT);
        m_model->setVisible(true);
        if (m_model->animationPlaying("CLOSE")) m_model->blendAnimation("OPEN", false, 0.1f, 2.0f, -1.0f);
        else m_model->playAnimation("OPEN", false, 2.0f, -1.0f);
        m_model->queueBlendAnimation("IDLE", true, 0.1f, 1.0f);
        m_parentWindow->addChildWindow(m_rootWindow);
        m_rootWindow->moveToBack();
        updateLayout();
        m_rootWindow->moveToBack();
        m_topWindow->moveToFront();
        m_bottomWindow->moveToFront();
    } else if (m_allowAbandon && !opened) {
        m_soundBank->playSample(66, NULL, 0.0f, 0.0f, false);
        m_model->blendAnimation("CLOSE", false, 0.1f, 2.0f, -1.0f);
        m_closed = false;
    }
    m_allowAbandon = opened;
}
void CQuestMenu::update(float elapsed)
{
    int width = m_settings->GetInt(KSETTINGS_RES_WIDTH);
    int height = m_settings->GetInt(KSETTINGS_RES_HEIGHT);
    if (!m_allowAbandon && m_closed) return;
    if (m_selectedQuestChanged) { m_selectedQuestChanged = false; updateLayout(); }
    m_model->updateAnimation(elapsed, false);
    m_model->getEntity()->_updateAnimation();
    Ogre::Bone* top = m_model->m_pSkeleton->getBone("tag_topskill");
    Ogre::Vector3 position = m_model->getPosition(false);
    const Ogre::Vector3& tag = top->_getDerivedPosition();
    float sumY = tag.y + position.y;
    float x = m_gameUI->scaledY(tag.x + position.x) + float(width) * 0.5f;
    float y = -(m_gameUI->scaledY(sumY) + float(height) * -0.5f);
    m_modelAnchor = x;
    m_topWindow->setPosition(CEGUI::UVector2(CEGUI::UDim(0,x),CEGUI::UDim(0,y)));
    Ogre::Bone* bottom = m_model->m_pSkeleton->getBone("tag_bottomskill");
    position = m_model->getPosition(false);
    float bottomX = bottom->_getDerivedPosition().x + position.x;
    float screenX = m_gameUI->scaledY(bottomX) + float(width) * 0.5f;
    m_bottomWindow->setPosition(CEGUI::UVector2(CEGUI::UDim(0,screenX),CEGUI::UDim(0,y)));
    float edge = m_gameUI->scaledY(50.0f) + screenX;
    m_screenEdge = edge < float(width) ? edge : float(width);
    if (!m_allowAbandon && !m_closed && !m_model->animationPlaying("CLOSE") && !m_model->animationQueued("CLOSE")) {
        m_model->setVisible(false); m_closed = true; m_parentWindow->removeChildWindow(m_rootWindow);
    }
}

CQuestMenu::CQuestMenu(CGameUI& ui, CSettings& settings, Ogre::RenderWindow*, Ogre::SceneManager* scene, Ogre::SceneManager*, CEGUI::Window* parent, CResourceManager* resources)
    : m_parentWindow(parent), m_hoveredReward(NULL), m_mouseThrough(false), m_owner(NULL), m_allowAbandon(false), m_closed(true), m_requestClose(false), m_selectedQuestChanged(false), m_selectedQuestID(0), m_selectedQuestIndex(0), m_settings(&settings), m_gameUI(&ui), m_scene(scene), m_model(NULL), m_resources(resources), m_modelAnchor(5000.0f), m_soundBank(NULL), m_questWindows(10)
{
    for (int i = 0; i < 100; ++i) m_questIDs[i] = i;
    CSoundBankDataInformation* sounds = CMasterResourceManager::getSingleton()->m_pSoundBankDataInformation;
    m_soundBank = new CSoundBank(*CMasterResourceManager::getSingleton()->m_pSoundManager, false);
    CSoundData* sample = sounds->getSoundDataObject(L"INVENTORYOPEN");
    if (sample) m_soundBank->addSample(22, sample->m_iGuid);
    sample = sounds->getSoundDataObject(L"INVENTORYCLOSE");
    if (sample) m_soundBank->addSample(66, sample->m_iGuid);
    sample = sounds->getSoundDataObject(L"LOWMANA");
    if (sample) m_soundBank->addSample(35, sample->m_iGuid);
    float width = float(m_settings->GetInt(KSETTINGS_RES_WIDTH));
    m_settings->GetInt(KSETTINGS_RES_HEIGHT);
    m_screenEdge = width;
    createMenus();
}

#include "FileSystem.h"
#include "ResourceManager.h"
#include <OgreMesh.h>
void CQuestMenu::createMenus()
{
    float width = float(m_settings->GetInt(KSETTINGS_RES_WIDTH));
    float height = float(m_settings->GetInt(KSETTINGS_RES_HEIGHT));
    m_model = m_resources->createGenericModel(m_scene, L"media/ui/models/quest/quest.mesh", L"", false, false, false);
    m_model->generateExtremes(5, true);
    Ogre::AxisAlignedBox bounds(Ogre::Vector3(-100000,-100000,-100000), Ogre::Vector3(100000,100000,100000));
    m_model->getEntity()->getMesh()->_setBounds(bounds, true);
    m_model->setPosition(((width - height / 0.75f) / m_settings->GetFloat(KSETTINGS_YRATIO)) * 0.5f, 0.0f, 0.0f);
    m_model->setVisible(false);
    m_itemImages = CEGUI::ImagesetManager::getSingleton().getImageset("GuiLook");
    m_uiImages = CEGUI::ImagesetManager::getSingleton().getImageset("UIIcons");
    CEGUI::WindowManager& wm = CEGUI::WindowManager::getSingleton();
    m_rootWindow = wm.createWindow("DefaultWindow", "QuestSheet", "");
    m_rootWindow->setSize(CEGUI::UVector2(CEGUI::UDim(1,0), CEGUI::UDim(1,0)));
    m_rootWindow->setProperty("RiseOnClick", "False");
    m_rootWindow->setPosition(CEGUI::UVector2(CEGUI::UDim(0,0), CEGUI::UDim(0,0)));
    m_rootWindow->setMousePassThroughEnabled(true);
    m_rootWindow->setZOrderingEnabled(false);
    m_rootWindow->subscribeEvent(CEGUI::Window::EventMouseMove, CEGUI::Event::Subscriber(&CQuestMenu::handle_MouseThrough, this));
    CFileInfo info;
    CFileSystem::getSingleton()->getFileInfo(L"media/ui/questmenu.layout", info, false, true, false);
    CEGUI::Window* layout = wm.loadWindowLayout(CEGUI::String(info.m_sResourceName), true);
    m_gameUI->convertToScreenScale(layout, false);
    m_gameUI->mapToFunctions(layout);
    mapEventHandlers(layout);
    CEGUI::Window* blocker = layout->recursiveChildSearch("Blocker");
    blocker->getParent()->removeChildWindow(blocker);
    m_rootWindow->addChildWindow(blocker);
    blocker->setProperty("RiseOnClick", "False");
    blocker->moveToBack();
    blocker->setZOrderingEnabled(false);
    CEGUI::Window* close = layout->recursiveChildSearch("Close");
    close->setRiseOnClickEnabled(false);
    close->moveToFront();
    close->subscribeEvent(CEGUI::Window::EventMouseButtonDown, CEGUI::Event::Subscriber(&CQuestMenu::handle_CloseButton, this));
    m_detailsWindow = layout->recursiveChildSearch("DescriptionFrame");
    m_listWindow = layout->recursiveChildSearch("RewardFrame");
    m_xpWindow = layout->recursiveChildSearch("Abandon");
    m_xpIcon = layout->recursiveChildSearch("Gold");
    m_goldIcon = layout->recursiveChildSearch("XP");
    m_fameIcon = layout->recursiveChildSearch("Fame");
    m_goldWindow = layout->recursiveChildSearch("GoldReward");
    m_fameWindow = layout->recursiveChildSearch("XPReward");
    m_rewardLabel = layout->recursiveChildSearch("FameReward");
    for (int i = 0; i < 6; ++i) {
        std::string suffix = STRINGS::GetValueAsString(i + 1);
        m_questButtons[i] = layout->recursiveChildSearch(("Quest" + suffix).c_str());
        m_questButtons[i]->setRiseOnClickEnabled(false);
        m_questButtons[i]->subscribeEvent(CEGUI::Window::EventMouseButtonDown, CEGUI::Event::Subscriber(&CQuestMenu::handle_QuestClick, this));
        m_questMarkers[i] = layout->recursiveChildSearch(("QuestText" + STRINGS::GetValueAsString(i + 1)).c_str());
        m_questMarkers[i]->setAlwaysOnTop(true);
        m_questMarkers[i]->setMousePassThroughEnabled(true);
    }
    for (int i = 0; i < 4; ++i) m_rewardIDs[i] = i;
    m_listContent = wm.createWindow("DefaultWindow", "RewardSockets", "");
    m_listWindow->addChildWindow(m_listContent);
    m_listContent->setSize(m_listWindow->getSize());
    m_listContent->setProperty("RiseOnClick", "False");
    m_listContent->setPosition(CEGUI::UVector2(CEGUI::UDim(0,0), CEGUI::UDim(0,0)));
    m_listContent->setMousePassThroughEnabled(true);
    m_listContent->moveToFront();
    m_detailContent = wm.createWindow("DefaultWindow", "RewardSocketsO", "");
    m_listWindow->addChildWindow(m_detailContent);
    m_detailContent->setSize(m_listWindow->getSize());
    m_detailContent->setProperty("RiseOnClick", "False");
    m_detailContent->setPosition(CEGUI::UVector2(CEGUI::UDim(0,0), CEGUI::UDim(0,0)));
    m_detailContent->setMousePassThroughEnabled(true);
    m_detailContent->moveToFront();
    for (int i = 0; i < 3; ++i) {
        m_rewardBackgrounds[i] = layout->recursiveChildSearch(("ItemRewardBkg" + STRINGS::GetValueAsString(i + 1)).c_str());
        CEGUI::Window* slot = layout->recursiveChildSearch(("ItemRewardSlot" + STRINGS::GetValueAsString(i + 1)).c_str());
        slot->setRiseOnClickEnabled(false);
        slot->moveToFront();
        slot->setWantsMultiClickEvents(false);
        slot->setUserData(&m_rewardIDs[i]);
        slot->subscribeEvent(CEGUI::Window::EventMouseEnters, CEGUI::Event::Subscriber(&CQuestMenu::handle_MouseOver, this));
        slot->subscribeEvent(CEGUI::Window::EventMouseMove, CEGUI::Event::Subscriber(&CQuestMenu::handle_MouseOver, this));
        slot->subscribeEvent(CEGUI::Window::EventMouseLeaves, CEGUI::Event::Subscriber(&CQuestMenu::handle_MouseOut, this));
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
        m_detailContent->addChildWindow(socket);
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
    m_bottomWindow = layout->recursiveChildSearch("BottomFrame");
    m_bottomWindow->getParent()->removeChildWindow(m_bottomWindow);
    m_rootWindow->addChildWindow(m_bottomWindow);
    m_bottomWindow->setProperty("RiseOnClick", "False");
    m_bottomWindow->moveToFront();
    m_bottomWindow->setZOrderingEnabled(false);
    m_topWindow = layout->recursiveChildSearch("TopFrame");
    m_topWindow->getParent()->removeChildWindow(m_topWindow);
    m_rootWindow->addChildWindow(m_topWindow);
    m_topWindow->setProperty("RiseOnClick", "False");
    m_topWindow->moveToFront();
    m_topWindow->setZOrderingEnabled(false);
}

#include "StringTranslate.h"
#include "EmptyStrings.h"
void CQuestMenu::updateLayout()
{
    if (!m_allowAbandon) m_hoveredReward = NULL;
    if (!m_owner) return;
    for (unsigned int i = 0; i < m_questWindows.size(); ++i) {
        CEGUI::Window* window = m_questWindows[i];
        if (m_topWindow->isChild(window)) m_topWindow->removeChildWindow(window);
        else if (m_bottomWindow->isChild(window)) m_bottomWindow->removeChildWindow(window);
        CEGUI::WindowManager::getSingleton().destroyWindow(window);
    }
    m_questWindows.clear();
    CQuestManager* manager = static_cast<CPlayer*>(m_owner)->getQuestManager();
    m_detailsWindow->setText("");
    m_xpWindow->setVisible(false);
    m_xpIcon->setVisible(false); m_goldWindow->setVisible(false);
    m_goldIcon->setVisible(false); m_fameWindow->setVisible(false);
    m_fameIcon->setVisible(false); m_rewardLabel->setVisible(false);
    for (int i = 0; i < 3; ++i) {
        m_rewardBackgrounds[i]->setVisible(false);
        if (m_rewardSlots[i]->getChildCount()) m_rewardSlots[i]->removeChildWindow(m_rewardSlots[i]->getChildAtIdx(0));
        setSlotIcon(i, NULL);
    }
    while (m_listContent->getChildCount()) m_listContent->removeChildWindow(m_listContent->getChildAtIdx(0));
    if (manager) {
        if (static_cast<int>(manager->m_Unknown18.size()) <= static_cast<int>(m_selectedQuestID)) {
            m_selectedQuestID = 0; m_selectedQuestIndex = 0;
        }
        int row = 0;
        for (int i = 0; i < static_cast<int>(manager->m_Unknown18.size()); ++i) {
            if (manager->m_Unknown18[i]->getQuestDetails() == EMPTY_WSTRING || row >= 6) continue;
            m_questButtons[row]->setVisible(true);
            m_questMarkers[row]->setVisible(true);
            if (m_selectedQuestID == static_cast<unsigned>(row)) {
                m_selectedQuestIndex = i;
                m_questButtons[m_selectedQuestID]->setProperty("NormalImage", "set:UIIcons image:QuestButtonPressed");
            } else m_questButtons[row]->setProperty("NormalImage", "set:UIIcons image:QuestButton");
            m_questButtons[row]->setID(row);
            std::wstring name = manager->m_Unknown18[i]->replaceStringTags(manager->m_Unknown18[i]->m_sUnknown58);
            static std::wstring g_Complete;
            if (g_Complete.empty()) g_Complete = CStringTranslate::getSinglton()->getTranslateString(L"Complete");
            static std::wstring g_Incomplete;
            if (g_Incomplete.empty()) g_Incomplete = CStringTranslate::getSinglton()->getTranslateString(L"Incomplete");
            if (manager->m_Unknown18[i]->isComplete(true)) {
                m_questMarkers[row]->setProperty("TextColour", "FFffcb3f");
                name = name + L" - " + g_Complete;
            } else {
                m_questMarkers[row]->setProperty("TextColour", "FFFFFFFF");
                name = name + L" - " + g_Incomplete;
            }
            std::string text = STRINGS::StringConvertToUTF8(std::wstring(name.c_str()));
            m_questMarkers[row]->setText(CEGUI::String(reinterpret_cast<const unsigned char*>(text.c_str())));
            if (m_selectedQuestID == static_cast<unsigned>(row)) {
                m_xpIcon->setVisible(true); m_goldWindow->setVisible(true);
                m_goldIcon->setVisible(true); m_fameWindow->setVisible(true);
                m_fameIcon->setVisible(true); m_rewardLabel->setVisible(true);
                text = STRINGS::GetValueAsString(manager->m_Unknown18[i]->getQuestRewardGold());
                m_goldWindow->setText(CEGUI::String(reinterpret_cast<const unsigned char*>(text.c_str())));
                text = STRINGS::GetValueAsString(manager->m_Unknown18[i]->getQuestRewardXP());
                m_fameWindow->setText(CEGUI::String(reinterpret_cast<const unsigned char*>(text.c_str())));
                text = STRINGS::GetValueAsString(manager->m_Unknown18[i]->getQuestRewardFame());
                m_rewardLabel->setText(CEGUI::String(reinterpret_cast<const unsigned char*>(text.c_str())));
                TArrayList<CBaseUnit*>* rewards = manager->m_Unknown18[i]->m_pQuestRewards->getRewardItems();
                for (unsigned int j = 0; j < rewards->size() && j < 3; ++j) {
                    m_rewardBackgrounds[j]->setVisible(true);
                    setSlotIcon(j, static_cast<CEquipment*>((*rewards)[j]));
                }
                std::wstring details = manager->m_Unknown18[i]->getQuestDetails();
                text = STRINGS::StringConvertToUTF8(std::wstring(details.c_str()));
                m_detailsWindow->setText(CEGUI::String(reinterpret_cast<const unsigned char*>(text.c_str())));
                if (manager->m_Unknown18[i]->m_bUnknown208) m_xpWindow->setVisible(true);
            }
            ++row;
            if (row > 5) break;
        }
        while (row < 6) {
            m_questButtons[row]->setVisible(false); m_questMarkers[row]->setVisible(false); ++row;
        }
    }
    m_rootWindow->moveToBack();
    m_detailContent->moveToFront();
    m_listContent->moveToFront();
}
