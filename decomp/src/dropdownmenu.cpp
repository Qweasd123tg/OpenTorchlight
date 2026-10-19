#include "Item.h"
#include "Character.h"
#include "DropdownMenu.h"
#include "iMenuListener.h"


CDropdownMenu::~CDropdownMenu()
{
    if (m_pGenericModel)
    {
        delete m_pGenericModel;
        m_pGenericModel = NULL;
    }
    if (m_pSoundBank)
    {
        delete m_pSoundBank;
        m_pSoundBank = NULL;
    }
    m_menuListeners.clear();
    m_pendingMenuListeners.clear();
}

template TArrayList<iMenuListener*>::~TArrayList();

bool CDropdownMenu::processInput(void*, float, bool capture)
{
    if (capture && m_bUnknown32) {
        setOpen(false);
        m_bUnknown32 = false;
        return false;
    }
    return true;
}

#include <CEGUIInputEvent.h>
#include "GameClient.h"

void CDropdownMenu::addMenuListener(iMenuListener* listener)
{
    if (m_menuListeners.find(listener) != -1) return;
    m_pendingMenuListeners.remove(listener);
    m_menuListeners.add(listener);
}

void CDropdownMenu::removeMenuListener(iMenuListener* listener)
{
    m_pendingMenuListeners.add(listener);
}

void CDropdownMenu::broadcastEvent(EMENU_TYPE menu, EMENU_EVENT event)
{
    for (unsigned int i = 0; i < m_pendingMenuListeners.size(); ++i)
        m_menuListeners.remove(m_pendingMenuListeners[i]);
    m_pendingMenuListeners.clear();
    for (unsigned int i = 0; i < m_menuListeners.size(); ++i)
        m_menuListeners[i]->menuEventOccured(this, menu, event);
}

bool CDropdownMenu::handle_CloseButton(const CEGUI::EventArgs& event)
{
    if (static_cast<const CEGUI::MouseEventArgs&>(event).button == CEGUI::LeftButton) {
        m_bUnknown32 = true;
        CGameClient* client = m_pGameUI->m_gameClient;
        client->m_selectedItem.setObject(NULL);
        client->m_targetItem.setObject(NULL);
        client->m_selectedCharacter.setObject(NULL);
        client->m_targetCharacter.setObject(NULL);
    }
    return true;
}

#include "StringUtilities.h"
bool CDropdownMenu::handle_onDoubleClick(const CEGUI::EventArgs& event)
{
    CEGUI::Window* window = static_cast<const CEGUI::WindowEventArgs&>(event).window;
    if (!window) return true;
    ELayoutFunction function = *static_cast<ELayoutFunction*>(window->getUserData());
    // These event controls store the payload string and prefix length in the
    // extended layout at +0x520/+0x680, beyond Window's ordinary text/ID.
    const CEGUI::String& payload = *reinterpret_cast<const CEGUI::String*>(reinterpret_cast<const char*>(window) + 0x520);
    std::wstring text = STRINGS::StringConvertToWide(reinterpret_cast<const char*>(payload.c_str()), 5000);
    std::wstring::size_type prefix = *reinterpret_cast<const int*>(reinterpret_cast<const char*>(window) + 0x680);
    text = text.substr(prefix, text.length() - prefix);
    return onDoubleClick(function, text);
}
bool CDropdownMenu::handle_onClick(const CEGUI::EventArgs& event)
{
    const CEGUI::MouseEventArgs& mouse = static_cast<const CEGUI::MouseEventArgs&>(event);
    CEGUI::Window* window = mouse.window;
    if (mouse.button != CEGUI::LeftButton || !window) return true;
    // These event controls store the payload string and prefix length in the
    // extended layout at +0x520/+0x680, beyond Window's ordinary text/ID.
    const CEGUI::String& payload = *reinterpret_cast<const CEGUI::String*>(reinterpret_cast<const char*>(window) + 0x520);
    std::wstring text = STRINGS::StringConvertToWide(reinterpret_cast<const char*>(payload.c_str()), 5000);
    std::wstring::size_type prefix = *reinterpret_cast<const int*>(reinterpret_cast<const char*>(window) + 0x680);
    text = text.substr(prefix, text.length() - prefix);
    return onClick(*static_cast<ELayoutFunction*>(window->getUserData()), text);
}

#include "GameVariables.h"
#include "StringUtilities.h"
#include <OgreBone.h>
#include <OgreSkeletonInstance.h>
#include <OgreEntity.h>

void CDropdownMenu::mapEventHandlers(CEGUI::Window* window)
{
    int count = window->getChildCount();
    for (int i = 0; i < count; ++i)
        mapEventHandlers(window->getChildAtIdx(i));
    try {
        if (window->isPropertyPresent("onClick") && window->getProperty("onClick").length() != 0) {
            window->setWantsMultiClickEvents(true);
            window->subscribeEvent(CEGUI::Window::EventMouseDoubleClick,
                CEGUI::Event::Subscriber(&CDropdownMenu::handle_onDoubleClick, this));
            window->subscribeEvent(CEGUI::Window::EventMouseButtonDown,
                CEGUI::Event::Subscriber(&CDropdownMenu::handle_onClick, this));
        }
    } catch (...) {
    }
}

void CDropdownMenu::setTitle(const std::wstring& title)
{
    if (m_iUnknown50)
        m_iUnknown50->setText(CEGUI::String(reinterpret_cast<const CEGUI::utf8*>(STRINGS::StringConvertToUTF8(title).c_str())));
}

void CDropdownMenu::setOpen(bool open)
{
    if (m_bUnknown30 && !open) {
        CGameClient* client = m_pGameUI->m_gameClient;
        client->m_selectedItem.setObject(NULL);
        client->m_targetItem.setObject(NULL);
        client->m_selectedCharacter.setObject(NULL);
        client->m_targetCharacter.setObject(NULL);
        if (m_pGenericModel) {
            m_pSoundBank->playSample(66, NULL, 0.0f, 0.0f, false);
            m_pGenericModel->blendAnimation("CLOSE", false, 0.1f, 2.0f, -1.0f);
            m_bUnknown31 = false;
        } else {
            static_cast<CEGUI::Window*>(m_pUnknown10)->removeChildWindow(static_cast<CEGUI::Window*>(m_pUnknown18));
            m_bUnknown31 = true;
        }
    } else if (!m_bUnknown30 && open) {
        m_pDynamicPropertyFile->GetInt(KSETTINGS_RES_WIDTH);
        m_pDynamicPropertyFile->GetInt(KSETTINGS_RES_HEIGHT);
        if (m_pGenericModel) {
            m_pSoundBank->playSample(22, NULL, 0.0f, 0.0f, false);
            m_pGenericModel->setVisible(true);
            if (m_pGenericModel->animationPlaying("CLOSE"))
                m_pGenericModel->blendAnimation("OPEN", false, 0.1f, 2.0f, -1.0f);
            else
                m_pGenericModel->playAnimation("OPEN", false, 2.0f, -1.0f);
            m_pGenericModel->queueBlendAnimation("IDLE", true, 0.1f, 1.0f);
        } else {
            static_cast<CEGUI::Window*>(m_pUnknown20)->setPosition(CEGUI::UVector2(CEGUI::UDim(0,0), CEGUI::UDim(0,0)));
        }
        static_cast<CEGUI::Window*>(m_pUnknown10)->addChildWindow(static_cast<CEGUI::Window*>(m_pUnknown18));
        static_cast<CEGUI::Window*>(m_pUnknown18)->moveToBack();
    }
    m_bUnknown30 = open;
}

void CDropdownMenu::update(float elapsed)
{
    int width = m_pDynamicPropertyFile->GetInt(KSETTINGS_RES_WIDTH);
    int height = m_pDynamicPropertyFile->GetInt(KSETTINGS_RES_HEIGHT);
    if (m_bUnknown30 || !m_bUnknown31) {
        if (m_pGenericModel) {
            m_pGenericModel->updateAnimation(elapsed, false);
            m_pGenericModel->getEntity()->_updateAnimation();
            Ogre::Bone* bone = m_pGenericModel->m_pSkeleton->getBone("tag_dropdowntop");
            Ogre::Vector3 position = m_pGenericModel->getPosition(false);
            position += bone->_getDerivedPosition();
            float x = m_pGameUI->scaledY(position.x);
            float y = m_pGameUI->scaledY(position.y);
            static_cast<CEGUI::Window*>(m_pUnknown20)->setPosition(
                CEGUI::UVector2(CEGUI::UDim(0, width * 0.5f + x), CEGUI::UDim(0, -(height * -0.5f + y))));
        }
        if (!m_bUnknown30 && !m_bUnknown31 && m_pGenericModel &&
                !m_pGenericModel->animationPlaying("CLOSE") && !m_pGenericModel->animationQueued("CLOSE")) {
            m_pGenericModel->setVisible(false);
            static_cast<CEGUI::Window*>(m_pUnknown10)->removeChildWindow(static_cast<CEGUI::Window*>(m_pUnknown18));
            m_bUnknown31 = true;
        }
    }
}

#include <CEGUIImagesetManager.h>
#include <CEGUIWindowManager.h>
#include <OgreMesh.h>
void CDropdownMenu::createMenus()
{
    m_pDynamicPropertyFile->GetInt(KSETTINGS_RES_WIDTH);
    m_pDynamicPropertyFile->GetInt(KSETTINGS_RES_HEIGHT);
    if (!(m_iUnknown88 & 1)) {
        m_pGenericModel = m_pResourceManager->createGenericModel(
            static_cast<Ogre::SceneManager*>(m_pUnknown48),
            L"media/ui/models/dropdown/dropdown.mesh", L"", false, false, false);
        Ogre::AxisAlignedBox bounds(Ogre::Vector3(-100000,-100000,-100000), Ogre::Vector3(100000,100000,100000));
        m_pGenericModel->getEntity()->getMesh()->_setBounds(bounds, true);
    }
    if (m_pGenericModel) {
        m_pGenericModel->setPosition(0.0f,0.0f,0.0f);
        m_pGenericModel->setVisible(false);
    }
    CEGUI::ImagesetManager::getSingleton().getImageset("GuiLook");
    CEGUI::WindowManager& manager = CEGUI::WindowManager::getSingleton();
    CEGUI::Window* root = manager.createWindow("DefaultWindow", STRINGS::uniqueName("gui_").c_str(), "");
    m_pUnknown18 = root;
    root->setSize(CEGUI::UVector2(CEGUI::UDim(1,0),CEGUI::UDim(1,0)));
    root->setProperty("RiseOnClick", "False");
    root->setPosition(CEGUI::UVector2(CEGUI::UDim(0,0),CEGUI::UDim(0,0)));
    root->setMousePassThroughEnabled(false);
    root->setZOrderingEnabled(false);
    CEGUI::Window* background = manager.createWindow("DefaultWindow", STRINGS::uniqueName("gui_").c_str(), "");
    root->addChildWindow(background);
    background->setSize(CEGUI::UVector2(CEGUI::UDim(1,0),CEGUI::UDim(1,0)));
    background->setProperty("RiseOnClick", "False");
    background->setPosition(CEGUI::UVector2(CEGUI::UDim(0,0),CEGUI::UDim(0,0)));
    background->moveToBack();
    background->setZOrderingEnabled(false);
    CEGUI::Window* contents = manager.createWindow("DefaultWindow", STRINGS::uniqueName("gui_").c_str(), "");
    m_pUnknown20 = contents;
    root->addChildWindow(contents);
    contents->setSize(CEGUI::UVector2(CEGUI::UDim(1,0),CEGUI::UDim(1,0)));
    contents->setProperty("RiseOnClick", "False");
    contents->setPosition(CEGUI::UVector2(CEGUI::UDim(0,0),CEGUI::UDim(0,0)));
    contents->setMousePassThroughEnabled(true);
    contents->moveToFront();
    contents->setZOrderingEnabled(false);
}

#include "MasterResourceManager.h"
#include "SoundBankDataInformation.h"
#include "SoundData.h"
CDropdownMenu::CDropdownMenu(CGameUI& ui, CSettings& settings, Ogre::SceneManager* scene, CEGUI::Window* parent, CResourceManager* resources, unsigned int mode)
    : CRunicCore(), m_pUnknown10(parent), m_bUnknown30(false), m_bUnknown31(true), m_bUnknown32(false),
      m_pDynamicPropertyFile(&settings), m_pGameUI(&ui), m_pUnknown48(scene), m_iUnknown50(NULL),
      m_pGenericModel(NULL), m_pResourceManager(resources), m_pSoundBank(NULL), m_iUnknown88(static_cast<int>(mode)),
      m_menuListeners(2), m_pendingMenuListeners(2)
{
    CSoundBankDataInformation* data = CMasterResourceManager::getSingleton()->m_pSoundBankDataInformation;
    CSoundManager* sound = CMasterResourceManager::getSingleton()->m_pSoundManager;
    m_pSoundBank = new CSoundBank(*sound,false);
    CSoundData* sample = data->getSoundDataObject(L"CENTEROPEN");
    if (sample) m_pSoundBank->addSample(22,sample->m_iGuid);
    sample = data->getSoundDataObject(L"CENTERCLOSE");
    if (sample) m_pSoundBank->addSample(66,sample->m_iGuid);
    createMenus();
}
