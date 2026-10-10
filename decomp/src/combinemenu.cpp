#include "CombineMenu.h"
#include "Equipment.h"
#include "StringUtilities.h"
#include <CEGUI.h>
void CCombineMenu::setSlotIcon(CEquipment* pItem, int iSlotIndex)
{


    // Preserve the original parent-then-slot call order. A single overloaded
    // vector addition expression lets GCC evaluate the slot argument first.
    const CEGUI::UVector2& parentY = m_pSocketedSizeWindows[iSlotIndex]->getParent()->getPosition();
    const CEGUI::UVector2& slotY = m_pSocketedSizeWindows[iSlotIndex]->getPosition();
    unsigned int uiIconY = (unsigned int)((parentY + slotY).d_y.asAbsolute(0.0f));
    const CEGUI::UVector2& parentX = m_pSocketedSizeWindows[iSlotIndex]->getParent()->getPosition();
    const CEGUI::UVector2& slotX = m_pSocketedSizeWindows[iSlotIndex]->getPosition();
    unsigned int uiIconX = (unsigned int)((parentX + slotX).d_x.asAbsolute(0.0f));

    CEGUI::Window* pIcon = pItem->m_pIconWindow;

    if (pIcon == 0)
    {
        pItem->createIcon(*m_pGameUI, false);

        pIcon = pItem->m_pIconWindow;

        if (pIcon != 0)
        {
            pIcon->setMutedState(true);
            pIcon->setMousePassThroughEnabled(true);
        }
    }

    if (pIcon != 0)
    {
        CEGUI::Window* pOldParent = pIcon->getParent();
        if (pOldParent != 0)
        {
            pOldParent->removeChildWindow(pIcon);
        }

        m_pSocketedSizeWindows[iSlotIndex]->addChildWindow(pIcon);


    }



    if (!pItem->m_bUnknown348 || pItem->m_iSocketCount == 0)
    {
        m_pMainSocketGlowWindows[iSlotIndex]->setProperty("Image", "");
    }
    else
    {
        if (pItem->m_iSocketCount == 1)
        {
            m_pMainSocketGlowWindows[iSlotIndex]->setProperty("Image", CEGUI::PropertyHelper::imageToString(
                &m_pImageset->getImage("onesocketglow")));
        }
        else
        {
            m_pMainSocketGlowWindows[iSlotIndex]->setProperty("Image", CEGUI::PropertyHelper::imageToString(
                &m_pImageset->getImage("twosocketglow")));
        }

        m_pMainSocketGlowWindows[iSlotIndex]->moveToFront();
    }

    if (pItem->m_iSocketCount > 1)
    {
        uiIconY = (unsigned int)((float)uiIconY +
            m_pSocketedSizeWindows[iSlotIndex]->getSize().d_y.asAbsolute(0.0f) * -0.19f);
    }

    if (pItem->m_SocketedEquipment.size() != 0)
    {


        for (unsigned int iSocket = 0; iSocket < pItem->m_SocketedEquipment.size(); iSocket++)
        {
            CEquipment* pSocketedItem = pItem->m_SocketedEquipment[iSocket];

            CEGUI::Window* pSocketedIcon = pSocketedItem->m_pIconWindow;

            if (pSocketedIcon == 0)
            {
                pSocketedItem->createIcon(*m_pGameUI, false);

                pSocketedIcon = pSocketedItem->m_pIconWindow;

                if (pSocketedIcon != 0)
                {
                    pSocketedIcon->setMutedState(true);
                    pSocketedIcon->setMousePassThroughEnabled(true);
                }
            }

            if (pSocketedIcon != 0)
            {
                CEGUI::Window* pOldParent = pSocketedIcon->getParent();
                if (pOldParent != 0)
                {
                    pOldParent->removeChildWindow(pSocketedIcon);
                }

                m_pSocketedIconParent->addChildWindow(pSocketedIcon);

                pSocketedIcon->setPosition(
                    CEGUI::UVector2(CEGUI::UDim(0.0f, (float)uiIconX),
                                    CEGUI::UDim(0.0f, (float)uiIconY)));

                pSocketedIcon->setSize(m_pSocketedSizeWindows[iSlotIndex]->getSize());
                pSocketedIcon->moveToFront();

                pSocketedIcon->setMousePassThroughEnabled(true);
            }

            uiIconY = (unsigned int)((float)uiIconY +
                m_pSocketedSizeWindows[iSlotIndex]->getSize().d_y.asAbsolute(0.0f) * 0.4f);
        }
    }



    const UNITTYPES::EUNITTYPES kIsaSlotGold = static_cast<UNITTYPES::EUNITTYPES>(0x36);
    const UNITTYPES::EUNITTYPES kIsaSlotBlue = static_cast<UNITTYPES::EUNITTYPES>(0x37);

    if (!pItem->canEquip(m_pCharacter, false))
    {
        if (pItem->isMagical())
        {
            m_pMainGlowWindows[iSlotIndex]->setProperty("Image", CEGUI::PropertyHelper::imageToString(
                &m_pImageset->getImage("blueredslotglow")));
        }
        else
        {
            m_pMainGlowWindows[iSlotIndex]->setProperty("Image", CEGUI::PropertyHelper::imageToString(
                &m_pImageset->getImage("redslotglow")));
        }
    }
    else if (pItem->ISA(kIsaSlotGold))
    {
        m_pMainGlowWindows[iSlotIndex]->setProperty("Image", CEGUI::PropertyHelper::imageToString(
            &m_pImageset->getImage("goldslotglow")));
    }
    else if (pItem->isMagical())
    {
        if (pItem->ISA(kIsaSlotBlue))
        {
            m_pMainGlowWindows[iSlotIndex]->setProperty("Image", CEGUI::PropertyHelper::imageToString(
                &m_pImageset->getImage("blueslotglow")));
        }
        else
        {
            m_pMainGlowWindows[iSlotIndex]->setProperty("Image", CEGUI::PropertyHelper::imageToString(
                &m_pImageset->getImage("greenslotglow")));
        }
    }
    else
    {
        m_pMainGlowWindows[iSlotIndex]->setProperty("Image", "");
    }



    if (pIcon != 0)
    {
        pIcon->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f, 0.0f), CEGUI::UDim(0.0f, 1.0f)));
        pIcon->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f, 0.0f), CEGUI::UDim(0.0f, 0.0f)));

        pIcon->setSize(m_pSocketedSizeWindows[iSlotIndex]->getSize());
        pIcon->moveToFront();

        pIcon->setUserData(&m_aiSlotData[iSlotIndex]);
    }

    if (m_pMainStackWindows[iSlotIndex] != 0)
    {
        if (pItem->m_iUnknown238 <= 1)
        {
            m_pMainStackWindows[iSlotIndex]->setVisible(false);
        }
        else
        {
            m_pMainStackWindows[iSlotIndex]->setVisible(true);

            std::string sCount = "x" + STRINGS::GetValueAsString(pItem->m_iUnknown238);

            CEGUI::String sText((const unsigned char*)sCount.c_str());

            m_pMainStackWindows[iSlotIndex]->setText(sText);
        }
    }
}

#include "CombineMenu.h"
#include "Inventory.h"
#include "Equipment.h"
#include "StringUtilities.h"
#include <CEGUI.h>

void CCombineMenu::updateLayout()
{
    if (!m_bOpen || !m_pCharacter || !m_pCharacter->m_pInventory)
        return;
    CInventory* inventory = m_pCharacter->m_pInventory;
    while (m_pSocketedIconParent->getChildCount())
        m_pSocketedIconParent->removeChildWindow(m_pSocketedIconParent->getChildAtIdx(0));
    for (unsigned i = 0; i < 4; ++i)
    {
        if (!m_pSocketedSizeWindows[i]) continue;
        if (m_pSocketedSizeWindows[i]->getChildCount())
            m_pSocketedSizeWindows[i]->removeChildWindow(m_pSocketedSizeWindows[i]->getChildAtIdx(0));
        CEquipmentRef* ref = reinterpret_cast<CEquipmentRef*>(inventory->getEquipmentRefInSlot(m_aiSlotData[i]));
        if (!ref)
        {
            // The inventory query is a call boundary; the slot pointer is re-read.
            if (!m_pSocketedSizeWindows[i]) continue;
            m_pMainStackWindows[i]->setVisible(false);
            m_pMainSocketGlowWindows[i]->setProperty("Image", "");
            m_pMainSocketGlowWindows[i]->setSize(m_pSocketedSizeWindows[i]->getSize());
            m_pMainGlowWindows[i]->setProperty("Image", "");
            m_pMainGlowWindows[i]->setSize(m_pSocketedSizeWindows[i]->getSize());
            m_pSocketedSizeWindows[i]->setProperty("Image", "");
            continue;
        }
        CEquipment* item = static_cast<CEquipment*>(ref->m_pUnknown10);
        CEGUI::Window* icon = item->m_pIconWindow;
        if (!icon)
        {
            item->createIcon(*m_pGameUI, false);
            icon = item->m_pIconWindow;
            if (icon)
            {
                icon->setMutedState(true);
                icon->setMousePassThroughEnabled(true);
            }
        }
        if (icon)
        {
            if (icon->getParent()) icon->getParent()->removeChildWindow(icon);
            m_pSocketedSizeWindows[i]->addChildWindow(icon);
        }
        const CEGUI::UVector2& parentY = m_pSocketedSizeWindows[i]->getParent()->getPosition();
        const CEGUI::UVector2& slotY = m_pSocketedSizeWindows[i]->getPosition();
        unsigned int socketY = (unsigned int)((parentY + slotY).d_y.asAbsolute(0.0f));
        const CEGUI::UVector2& parentX = m_pSocketedSizeWindows[i]->getParent()->getPosition();
        const CEGUI::UVector2& slotX = m_pSocketedSizeWindows[i]->getPosition();
        unsigned int socketX = (unsigned int)((parentX + slotX).d_x.asAbsolute(0.0f));
        if (!item->m_bUnknown348 || !item->m_iSocketCount ||
            !m_pSocketedSizeWindows[i]->getParent()->isVisible(false))
            m_pMainSocketGlowWindows[i]->setProperty("Image", "");
        else
        {
            if (item->m_iSocketCount == 1)
                m_pMainSocketGlowWindows[i]->setProperty("Image", CEGUI::PropertyHelper::imageToString(&m_pImageset->getImage("onesocketglow")));
            else
                m_pMainSocketGlowWindows[i]->setProperty("Image", CEGUI::PropertyHelper::imageToString(&m_pImageset->getImage("twosocketglow")));
            m_pMainSocketGlowWindows[i]->moveToFront();
        }
        if (m_pMainStackWindows[i])
        {
            if (item->m_iUnknown238 <= 1) m_pMainStackWindows[i]->setVisible(false);
            else
            {
                m_pMainStackWindows[i]->setVisible(true);
                std::string count = "x" + STRINGS::GetValueAsString(item->m_iUnknown238);
                m_pMainStackWindows[i]->setText(CEGUI::String(reinterpret_cast<const unsigned char*>(count.c_str())));
            }
        }
        if (item->m_iSocketCount > 1)
            socketY += m_pSocketedSizeWindows[i]->getSize().d_y.asAbsolute(0.0f) * -0.19f;
        if (m_pSocketedSizeWindows[i]->getParent()->isVisible(false))
            for (unsigned socket = 0; socket < item->m_SocketedEquipment.size(); ++socket)
            {
                CEquipment* gem = item->m_SocketedEquipment[socket];
                CEGUI::Window* gemIcon = gem->m_pIconWindow;
                if (!gemIcon)
                {
                    gem->createIcon(*m_pGameUI, false);
                    gemIcon = gem->m_pIconWindow;
                    if (gemIcon)
                    {
                        gemIcon->setMutedState(true);
                        gemIcon->setMousePassThroughEnabled(true);
                    }
                }
                if (gemIcon)
                {
                    if (gemIcon->getParent()) gemIcon->getParent()->removeChildWindow(gemIcon);
                    m_pSocketedIconParent->addChildWindow(gemIcon);
                    gemIcon->setPosition(CEGUI::UVector2(CEGUI::UDim(0,(float)socketX), CEGUI::UDim(0,(float)socketY)));
                    gemIcon->setSize(m_pSocketedSizeWindows[i]->getSize());
                    gemIcon->moveToFront();
                    gemIcon->setMousePassThroughEnabled(true);
                }
                socketY += m_pSocketedSizeWindows[i]->getSize().d_y.asAbsolute(0.0f) * 0.4f;
            }
        if (item->ISA(static_cast<UNITTYPES::EUNITTYPES>(0x36)))
            m_pMainGlowWindows[i]->setProperty("Image", CEGUI::PropertyHelper::imageToString(&m_pImageset->getImage("goldslotglow")));
        else if (item->isMagical())
        {
            if (item->ISA(static_cast<UNITTYPES::EUNITTYPES>(0x37)))
                m_pMainGlowWindows[i]->setProperty("Image", CEGUI::PropertyHelper::imageToString(&m_pImageset->getImage("blueslotglow")));
            else
                m_pMainGlowWindows[i]->setProperty("Image", CEGUI::PropertyHelper::imageToString(&m_pImageset->getImage("greenslotglow")));
        }
        else m_pMainGlowWindows[i]->setProperty("Image", "");
        m_pSocketedSizeWindows[i]->setProperty("Image", "");
        if (icon)
        {
            icon->setPosition(CEGUI::UVector2(CEGUI::UDim(0,0),CEGUI::UDim(0,1)));
            icon->setPosition(CEGUI::UVector2(CEGUI::UDim(0,0),CEGUI::UDim(0,0)));
            icon->setSize(m_pSocketedSizeWindows[i]->getSize());
            icon->moveToFront();
            icon->update(0.001f);
        }
    }
    m_pBackground->moveToBack();
    m_pPanel->moveToFront();
    m_pForeground->moveToFront();
    m_pSocketedIconParent->moveToFront();
}

// Complete candidate entry; not published until differential verification.
#include "Settings.h"
#include "GameVariables.h"
#include "ResourceManager.h"
#include "GenericModel.h"
#include "FileSystem.h"
#include <OgreEntity.h>
#include <OgreMesh.h>
__attribute__((flatten)) void CCombineMenu::createMenus()
{
    typedef char check_m_pParent[__builtin_offsetof(CCombineMenu,m_pParent)==72?1:-1];
    typedef char check_m_pBackground[__builtin_offsetof(CCombineMenu,m_pBackground)==80?1:-1];
    typedef char check_m_pPanel[__builtin_offsetof(CCombineMenu,m_pPanel)==88?1:-1];
    typedef char check_m_pSocketedIconParent[__builtin_offsetof(CCombineMenu,m_pSocketedIconParent)==96?1:-1];
    typedef char check_m_pForeground[__builtin_offsetof(CCombineMenu,m_pForeground)==104?1:-1];
    typedef char check_m_pTitle[__builtin_offsetof(CCombineMenu,m_pTitle)==112?1:-1];
    typedef char check_m_pDialog[__builtin_offsetof(CCombineMenu,m_pDialog)==120?1:-1];
    typedef char check_m_pAccept[__builtin_offsetof(CCombineMenu,m_pAccept)==128?1:-1];
    typedef char check_m_pCharacter[__builtin_offsetof(CCombineMenu,m_pCharacter)==144?1:-1];
    typedef char check_m_bOpen[__builtin_offsetof(CCombineMenu,m_bOpen)==152?1:-1];
    typedef char check_m_pSettings[__builtin_offsetof(CCombineMenu,m_pSettings)==160?1:-1];
    typedef char check_m_pGameUI[__builtin_offsetof(CCombineMenu,m_pGameUI)==168?1:-1];
    typedef char check_m_pSceneManager[__builtin_offsetof(CCombineMenu,m_pSceneManager)==176?1:-1];
    typedef char check_m_pRenderWindow[__builtin_offsetof(CCombineMenu,m_pRenderWindow)==184?1:-1];
    typedef char check_m_pMenuModel[__builtin_offsetof(CCombineMenu,m_pMenuModel)==200?1:-1];
    typedef char check_m_pResourceManager[__builtin_offsetof(CCombineMenu,m_pResourceManager)==208?1:-1];
    typedef char check_m_aiSlotData[__builtin_offsetof(CCombineMenu,m_aiSlotData)==232?1:-1];
    typedef char check_m_aiLocalSlotData[__builtin_offsetof(CCombineMenu,m_aiLocalSlotData)==248?1:-1];
    typedef char check_m_pMainGlowWindows[__builtin_offsetof(CCombineMenu,m_pMainGlowWindows)==264?1:-1];
    typedef char check_m_pMainSocketGlowWindows[__builtin_offsetof(CCombineMenu,m_pMainSocketGlowWindows)==296?1:-1];
    typedef char check_m_pSocketedSizeWindows[__builtin_offsetof(CCombineMenu,m_pSocketedSizeWindows)==328?1:-1];
    typedef char check_m_pMainStackWindows[__builtin_offsetof(CCombineMenu,m_pMainStackWindows)==360?1:-1];
    typedef char check_m_pImageset[__builtin_offsetof(CCombineMenu,m_pImageset)==408?1:-1];
    typedef char check_m_pSlotGlow[__builtin_offsetof(CCombineMenu,m_pSlotGlow)==416?1:-1];
    typedef char check_size[sizeof(CCombineMenu)==0x1b0?1:-1];
    float width = (float)m_pSettings->GetInt(KSETTINGS_RES_WIDTH);
    float height = (float)m_pSettings->GetInt(KSETTINGS_RES_HEIGHT);
    m_pMenuModel = m_pResourceManager->createGenericModel(m_pSceneManager,
        L"media/ui/models/dropdown/dropdown.mesh", L"", false, false, false);
    m_pMenuModel->getEntity()->getMesh()->_setBounds(
        Ogre::AxisAlignedBox(Ogre::Vector3(-100000.0f,-100000.0f,-100000.0f),
                             Ogre::Vector3(100000.0f,100000.0f,100000.0f)),true);
    float x = width - height / 0.75f;
    x /= m_pSettings->GetFloat(KSETTINGS_YRATIO);
    m_pMenuModel->setPosition(-0.5f*x-270.0f,0.0f,0.0f);
    m_pMenuModel->setVisible(false);
    CEGUI::ImagesetManager::getSingleton().getImageset("GuiLook");
    m_pImageset=CEGUI::ImagesetManager::getSingleton().getImageset("UIIcons");
    m_pBackground=CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow","CombineSheet","");
    m_pBackground->setSize(CEGUI::UVector2(CEGUI::UDim(1,0),CEGUI::UDim(1,0)));
    m_pBackground->setProperty("RiseOnClick","False");
    m_pBackground->setPosition(CEGUI::UVector2(CEGUI::UDim(0,0),CEGUI::UDim(0,0)));
    m_pBackground->setMousePassThroughEnabled(true);
    m_pBackground->setZOrderingEnabled(false);
    m_pBackground->subscribeEvent(CEGUI::Window::EventMouseMove,CEGUI::SubscriberSlot(&CCombineMenu::handle_MouseThrough,this));
    CEGUI::Window* barrier=CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow","CombineClickBarrier","");
    m_pBackground->addChildWindow(barrier);
    float barrierHeight=m_pGameUI->scaledY(768.0f);
    float barrierWidth=m_pGameUI->scaledY(390.0f);
    barrier->setSize(CEGUI::UVector2(CEGUI::UDim(0,barrierWidth),CEGUI::UDim(0,barrierHeight)));
    barrier->setProperty("RiseOnClick","False");
    barrier->setPosition(CEGUI::UVector2(CEGUI::UDim(0,0),CEGUI::UDim(0,0)));
    barrier->moveToBack();
    barrier->setZOrderingEnabled(false);
    CFileInfo fileInfo;
    CFileSystem::getSingleton()->getFileInfo(L"media/ui/combinemenu.layout",fileInfo,false,true,false);
    m_pPanel=CEGUI::WindowManager::getSingleton().loadWindowLayout(fileInfo.m_sResourceName.c_str(),true);
    m_pGameUI->convertToScreenScale(m_pPanel,false);
    m_pGameUI->mapToFunctions(m_pPanel);
    mapEventHandlers(m_pPanel);
    m_pBackground->addChildWindow(m_pPanel);
    m_pPanel->setMousePassThroughEnabled(true);
    m_pPanel->moveToFront();
    m_pPanel->setZOrderingEnabled(false);
    m_pTitle=m_pPanel->recursiveChildSearch("Title");
    m_pSlotGlow=CEGUI::WindowManager::getSingleton().createWindow("GuiLook/StaticImage",STRINGS::uniqueName(std::string("gui_")).c_str(),"");
    m_pSlotGlow->setMutedState(true);
    m_pSlotGlow->setMousePassThroughEnabled(true);
    m_pSlotGlow->setRiseOnClickEnabled(false);
    m_pSlotGlow->setProperty("Image",CEGUI::PropertyHelper::imageToString(&m_pImageset->getImage("slotglow")));
    for(unsigned i=0;i<4;++i)m_aiSlotData[i]=15+i;
    for(unsigned i=0;i<4;++i)m_aiLocalSlotData[i]=i;
    m_pDialog=m_pPanel->recursiveChildSearch("Dialog");
    m_pAccept=m_pPanel->recursiveChildSearch("Accept");
    m_pSocketedIconParent=CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow","CombineerSockets","");
    m_pPanel->addChildWindow(m_pSocketedIconParent);
    m_pSocketedIconParent->setSize(m_pPanel->getSize());
    m_pSocketedIconParent->setProperty("RiseOnClick","False");
    m_pSocketedIconParent->setPosition(CEGUI::UVector2(CEGUI::UDim(0,0),CEGUI::UDim(0,0)));
    m_pSocketedIconParent->setMousePassThroughEnabled(true);
    m_pSocketedIconParent->moveToFront();
    m_pForeground=CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow","CombineerSocketsO","");
    m_pPanel->addChildWindow(m_pForeground);
    m_pForeground->setSize(m_pPanel->getSize());
    m_pForeground->setProperty("RiseOnClick","False");
    m_pForeground->setPosition(CEGUI::UVector2(CEGUI::UDim(0,0),CEGUI::UDim(0,0)));
    m_pForeground->setMousePassThroughEnabled(true);
    m_pForeground->moveToFront();
    for(unsigned i=0;i<4;++i) {
        CEGUI::Window* slot=m_pPanel->recursiveChildSearch((std::string("ItemSlot")+STRINGS::GetValueAsString(i+1)).c_str());
        slot->moveToFront();
        slot->setRiseOnClickEnabled(false);
        slot->setWantsMultiClickEvents(false);
        slot->setUserData(&m_aiLocalSlotData[i]);
        slot->setAlwaysOnTop(true);
        slot->subscribeEvent(CEGUI::Window::EventMouseButtonDown,CEGUI::SubscriberSlot(&CCombineMenu::handle_ItemClick,this));
        slot->subscribeEvent(CEGUI::Window::EventMouseEnters,CEGUI::SubscriberSlot(&CCombineMenu::handle_MouseOver,this));
        slot->subscribeEvent(CEGUI::Window::EventMouseMove,CEGUI::SubscriberSlot(&CCombineMenu::handle_MouseOver,this));
        slot->subscribeEvent(CEGUI::Window::EventMouseLeaves,CEGUI::SubscriberSlot(&CCombineMenu::handle_MouseOut,this));
        slot->moveToFront();
        m_pSocketedSizeWindows[i]=slot;
        m_pMainStackWindows[i]=0;
        m_pMainStackWindows[i]=CEGUI::WindowManager::getSingleton().createWindow("GuiLook/StaticText",STRINGS::uniqueName(std::string("gui_")).c_str(),"");
        m_pMainStackWindows[i]->setFont("Serif");
        m_pMainStackWindows[i]->setSize(slot->getSize());
        CEGUI::UVector2 labelPosition=slot->getPosition();
        m_pMainStackWindows[i]->setProperty("HorzTextFormatting","RightAligned");
        m_pMainStackWindows[i]->setProperty("VertFormatting","BottomAligned");
        m_pMainStackWindows[i]->setMousePassThroughEnabled(true);
        m_pMainStackWindows[i]->setPosition(labelPosition);
        m_pSocketedSizeWindows[i]->getParent()->addChildWindow(m_pMainStackWindows[i]);
        m_pMainStackWindows[i]->setText("");
        m_pMainStackWindows[i]->setProperty("TextColour",CEGUI::PropertyHelper::colourToString(CEGUI::colour(1,1,1,1)));
        m_pMainStackWindows[i]->setAlwaysOnTop(true);
        CEGUI::Window* glow=CEGUI::WindowManager::getSingleton().createWindow("GuiLook/StaticImage",STRINGS::uniqueName(std::string("gui_")).c_str(),"");
        m_pSocketedSizeWindows[i]->getParent()->addChildWindow(glow);
        glow->setRiseOnClickEnabled(false);
        glow->setWantsMultiClickEvents(false);
        glow->setMousePassThroughEnabled(true);
        glow->setMutedState(true);
        glow->setPosition(slot->getPosition());
        glow->setSize(slot->getSize());
        m_pMainGlowWindows[i]=glow;
        CEGUI::Window* socketGlow=CEGUI::WindowManager::getSingleton().createWindow("GuiLook/StaticImage",STRINGS::uniqueName(std::string("gui_")).c_str(),"");
        m_pForeground->addChildWindow(socketGlow);
        socketGlow->setRiseOnClickEnabled(false);
        socketGlow->setWantsMultiClickEvents(false);
        socketGlow->setMousePassThroughEnabled(true);
        socketGlow->setMutedState(true);
        const CEGUI::UVector2& parentPosition=m_pSocketedSizeWindows[i]->getParent()->getPosition();
        const CEGUI::UVector2& slotPosition=m_pSocketedSizeWindows[i]->getPosition();
        socketGlow->setPosition(slotPosition+parentPosition);
        socketGlow->setSize(slot->getSize());
        m_pMainSocketGlowWindows[i]=socketGlow;
    }
}

#include "Recipes.h"
#include "Level.h"
#include "SpawnClass.h"
#include "UnitResourceList.h"
#include "EmptyStrings.h"
#include "SoundBank.h"
namespace combine_interaction_detail {
struct Ingredient { UNITTYPES::EUNITTYPES type; char pad4[4]; std::wstring name; int count; };
struct Output { std::wstring spawnClass; std::wstring itemName; };
struct RecipeFields { char prefix[8]; TArrayList<Ingredient*> inputs; TArrayList<Output*> outputs; };
struct OwnerFields { char prefix[0x100]; int level; char pad104[0x298-0x104]; CSoundBank* sound; char pad2a0[0x490-0x2a0]; CInventory* inventory; };
typedef char check_ingredient_name[__builtin_offsetof(Ingredient,name)==8?1:-1];
typedef char check_ingredient_count[__builtin_offsetof(Ingredient,count)==0x10?1:-1];
typedef char check_recipe_outputs[__builtin_offsetof(RecipeFields,outputs)==0x20?1:-1];
typedef char check_owner_sound[__builtin_offsetof(OwnerFields,sound)==0x298?1:-1];
typedef char check_owner_inventory[__builtin_offsetof(OwnerFields,inventory)==0x490?1:-1];
__attribute__((always_inline)) inline RecipeFields& recipe(CRecipe* p){return *reinterpret_cast<RecipeFields*>(p);}
__attribute__((always_inline)) inline OwnerFields& owner(CCharacter* p){return *reinterpret_cast<OwnerFields*>(p);}
__attribute__((always_inline)) inline int subtract(int a,int b){return static_cast<int>(static_cast<unsigned int>(a)-static_cast<unsigned int>(b));}
__attribute__((always_inline)) inline bool typeMatch(CRecipe* r,unsigned i,CEquipment* item){
    bool magical=false;
    if(recipe(r).inputs[i]->type==static_cast<UNITTYPES::EUNITTYPES>(135)) {
        if(item && item->isMagical() && !item->ISA(static_cast<UNITTYPES::EUNITTYPES>(54)) && !item->ISA(static_cast<UNITTYPES::EUNITTYPES>(55)))magical=true;
    }
    if(!item)return false;
    return item->ISA(recipe(r).inputs[i]->type)||magical;
}
__attribute__((always_inline)) inline CDataGroup* namedGroup(CCombineMenu* menu,CRecipe* r,unsigned i){
    const std::wstring& name=recipe(r).inputs[i]->name;
    std::wstring category(L"ITEMS");
    return menu->m_pResourceManager->getMasterResourceList()->getDataGroupByObjectName(category,name);
}
__attribute__((always_inline)) inline long long guid(CCombineMenu* menu,CDataGroup* data){
    std::wstring key(L"UNIT_GUID");return menu->m_pResourceManager->getUnitGuidByDataGroup(data,key);
}
__attribute__((always_inline)) inline void consume(CCombineMenu* menu,CEquipment* item,int& remaining){
    if(item->m_iUnknown238>1){
        int count=item->m_iUnknown238<remaining?item->m_iUnknown238:remaining;
        item->incrementStackBy(-count);remaining=subtract(remaining,count);
        if(item->m_iUnknown238>0)return;
    }else remaining=subtract(remaining,1);
    owner(menu->m_pCharacter).inventory->removeEquipment(item);
    menu->itemUpdatedInMenu(item,false);
    delete item;
}
}
__attribute__((flatten))
void CCombineMenu::performInteraction(){
    using namespace combine_interaction_detail;
    std::wstring resultName;
    int count=static_cast<int>(CRecipes::getSingleton()->m_recipes.size());
    CRecipes* recipes=CRecipes::getSingleton();
    TArrayList<CRecipe*> matches(10);
    for(int i=0;i<count;++i){
        CRecipe* current=recipes->m_recipes[i];
        unsigned ingredients=recipe(current).inputs.size();bool matched=true;
        for(unsigned j=0;j<ingredients;++j){
            int remaining=recipe(current).inputs[j]->count;
            if(recipe(current).inputs[j]->type==static_cast<UNITTYPES::EUNITTYPES>(22)){
                CDataGroup* group=namedGroup(this,current,j);
                if(group){
                    long long requiredGuid=guid(this,group);
                    for(unsigned slot=0;slot<4;++slot){
                        CEquipment* item=owner(m_pCharacter).inventory->getEquipmentInSlot(m_aiSlotData[slot]);
                        if(item && guid(this,item->getDataGroup())==requiredGuid)remaining=subtract(remaining,item->m_iUnknown238);
                    }
                }
            }else{
                for(unsigned slot=0;slot<4;++slot){
                    CEquipment* item=owner(m_pCharacter).inventory->getEquipmentInSlot(m_aiSlotData[slot]);
                    if(typeMatch(current,j,item))remaining=subtract(remaining,item->m_iUnknown238);
                }
            }
            if(remaining>0){matched=false;break;}
        }
        if(matched)matches.add(current);
    }
    if(matches.size()==0){m_pSoundBank->playSample(24,m_pCharacter->getSceneNode(),0.0f,0.0f,false);return;}
    CRecipe* selected=matches[0];unsigned threshold=0;
    for(unsigned i=0;i<matches.size();++i){
        unsigned required=0;
        for(unsigned j=0;j<recipe(matches[i]).inputs.size();++j)required+=static_cast<unsigned>(recipe(matches[i]).inputs[j]->count);
        if(required>threshold){selected=matches[i];threshold=recipe(selected).inputs.size();}
    }
    // The original compares total quantity but retains ingredient count as its threshold.
    for(unsigned j=0;j<recipe(selected).inputs.size();++j){
        int remaining=recipe(selected).inputs[j]->count;
        if(recipe(selected).inputs[j]->type==static_cast<UNITTYPES::EUNITTYPES>(22)){
            CDataGroup* group=namedGroup(this,selected,j);
            if(group){
                long long requiredGuid=guid(this,group);
                for(unsigned slot=0;slot<4;++slot){
                    if(remaining<=0)continue;
                    CEquipment* item=owner(m_pCharacter).inventory->getEquipmentInSlot(m_aiSlotData[slot]);
                    if(item && guid(this,item->getDataGroup())==requiredGuid)consume(this,item,remaining);
                }
            }
        }else{
            for(unsigned slot=0;slot<4;++slot){
                if(remaining<=0)continue;
                CEquipment* item=owner(m_pCharacter).inventory->getEquipmentInSlot(m_aiSlotData[slot]);
                if(typeMatch(selected,j,item))consume(this,item,remaining);
            }
        }
    }
    m_pSoundBank->playSample(36,m_pCharacter->getSceneNode(),0.0f,0.0f,false);
    if(owner(m_pCharacter).sound)owner(m_pCharacter).sound->queueGlobalSample(63,0.0f,0.1f);
    if(recipe(selected).outputs.size()==0)return;
    for(unsigned slot=0;slot<4;++slot){
        CEquipment* item=owner(m_pCharacter).inventory->getEquipmentInSlot(m_aiSlotData[slot]);
        if(item){
            owner(m_pCharacter).inventory->removeEquipment(item);
            if(!owner(m_pCharacter).inventory->pickupEquipment(item,true)){
                Ogre::Vector3 position=m_pCharacter->getPosition(true);
                m_pCharacter->getLevel()->addItem(item,position,true);
                item->drop();
            }
        }
    }
    Output* output=recipe(selected).outputs[0];
    if(output->spawnClass==EMPTY_WSTRING){
        CEquipment* item=m_pResourceManager->createEquipment(output->itemName.c_str(),false,true);
        if(item)owner(m_pCharacter).inventory->pickupEquipment(item,m_aiSlotData[0],true);
    }else{
        CSpawnClass* spawn=m_pResourceManager->getSpawnClassByName(output->spawnClass);
        if(!spawn)return;
        TArrayList<CDataGroup*> groups;
        TArrayList<bool> enchanted;
        CCharacter* character=m_pCharacter;
        spawn->rollSpawnClass(groups,&enchanted,character,character,owner(character).level,static_cast<unsigned>(-1),0,-1,0,0);
        for(unsigned i=0;i<(groups.size()<4?groups.size():4);++i){
            CEquipment* item;
            {std::wstring key(L"NAME");item=m_pResourceManager->createEquipment(groups[i]->GetDataValue(key,EMPTY_WSTRING).c_str(),false,true);}
            if(enchanted[i])item->enchant(true);
            owner(m_pCharacter).inventory->pickupEquipment(item,m_aiSlotData[i],true);
        }
    }
    m_pCharacter->incrementJournalStatistic(static_cast<EJournalStatistic>(16),1);
}

namespace combine_controls {
struct UIFields {char prefix[0xb8];CEquipment* dragged;};
struct HoverState {char prefix[0x198];bool flag198;};
struct ClientFields {char prefix[0x1c8];TSafePointer<CRunicCore> first,second,third,fourth;};
struct ClientUI {char prefix[0x1920];ClientFields* client;};
inline __attribute__((always_inline,flatten)) void clearMouseClicks(CGameUI* ui) {
 ClientFields* c=reinterpret_cast<ClientUI*>(ui)->client;
 c->fourth.setObject(0);c->third.setObject(0);c->first.setObject(0);c->second.setObject(0);
}
}
void CCombineMenu::setOwner(CCharacter* owner){m_pOwner=owner;}
void CCombineMenu::equipmentEquipped(CEquipment*){updateLayout();}
void CCombineMenu::equipmentUnequipped(CEquipment*){updateLayout();}
void CCombineMenu::inventoryDestroyed(){}
bool CCombineMenu::handle_ItemClick(const CEGUI::EventArgs& event) {
 const CEGUI::MouseEventArgs& mouse=static_cast<const CEGUI::MouseEventArgs&>(event);
 if(mouse.window){int slot=*static_cast<int*>(mouse.window->getUserData());
  if(mouse.button==CEGUI::LeftButton)m_ClickedSlot=m_aiSlotData[slot];
  else if(mouse.button==CEGUI::RightButton)m_RightClickedSlot=m_aiSlotData[slot];
 }
 return true;
}
bool CCombineMenu::handle_MouseThrough(const CEGUI::EventArgs&){m_bHover=false;return true;}
bool CCombineMenu::handle_onClick(const CEGUI::EventArgs& event) {
 const CEGUI::MouseEventArgs& mouse=static_cast<const CEGUI::MouseEventArgs&>(event);
 if(mouse.button==CEGUI::LeftButton&&mouse.window)return onClick(*static_cast<ELayoutFunction*>(mouse.window->getUserData()));
 return true;
}
void CCombineMenu::equipmentDropped(CEquipment* item){itemUpdatedInMenu(item,false);updateLayout();}
void CCombineMenu::equipmentPickedUp(CEquipment* item){itemUpdatedInMenu(item,true);updateLayout();}
void CCombineMenu::setPlayer(CCharacter* player) {
 if(player!=m_pCharacter)inventoryDestroyed();
 if(m_pCharacter)m_pCharacter->m_pInventory->removeListener(this);
 m_pCharacter=player;
 if(player)player->m_pInventory->addListener(this);
}
bool CCombineMenu::handle_MouseOut(const CEGUI::EventArgs& event) {
 CEGUI::Window* window=static_cast<const CEGUI::WindowEventArgs&>(event).window;
 CCharacter* owner=m_pCharacter;
 if(window&&owner) {
  int slot=*static_cast<int*>(window->getUserData());
  CEquipment* item=owner->m_pInventory->getEquipmentInSlot(m_aiSlotData[slot]);
  if(item==m_pHoverObject) {
   m_pHoverObject=0;
   CEquipment* dragged=reinterpret_cast<combine_controls::UIFields*>(m_pGameUI)->dragged;
   if(!dragged||!dragged->ISA(static_cast<UNITTYPES::EUNITTYPES>(120))) {
    m_pSocketedIconParent->setVisible(false);m_pForeground->setVisible(false);
   }
  }
 }
 return true;
}
bool CCombineMenu::handle_CloseButton(const CEGUI::EventArgs& event) {
 if(static_cast<const CEGUI::MouseEventArgs&>(event).button==CEGUI::LeftButton) {
  m_bCloseRequested=true;m_pGameUI->getCharacter()->setTarget(0);
  combine_controls::clearMouseClicks(m_pGameUI);m_pGameUI->closeRight();
 }
 return true;
}
bool CCombineMenu::onClick(ELayoutFunction action) {
 if(m_bOpen) {
  if(static_cast<int>(action)==8) {
   m_bCloseRequested=true;m_pGameUI->getCharacter()->setTarget(0);
   combine_controls::clearMouseClicks(m_pGameUI);m_pGameUI->closeRight();
  }else if(static_cast<int>(action)==9)performInteraction();
 }
 return true;
}
void CCombineMenu::mapEventHandlers(CEGUI::Window* window) {
 int count=static_cast<int>(window->getChildCount());
 for(int i=0;i<count;++i)mapEventHandlers(window->getChildAtIdx(i));
 try {
  if(window->isPropertyPresent("onClick")&&!window->getProperty("onClick").empty())
   window->subscribeEvent(CEGUI::Window::EventMouseButtonDown,CEGUI::Event::Subscriber(&CCombineMenu::handle_onClick,this));
 }catch(...) {}
}

bool CCombineMenu::processInput(void*,float,bool active) {
 if(!active) {
  m_pHoverObject=0;m_pSocketedIconParent->setVisible(false);m_pForeground->setVisible(false);
  if(m_pSlotGlow->getParent()&&m_pSlotGlow->getParent()->isChild(m_pSlotGlow))m_pSlotGlow->getParent()->removeChildWindow(m_pSlotGlow);
  return true;
 }
 bool result=true;
 if(m_bCloseRequested){setOpen(false);m_bCloseRequested=false;result=false;}
 CEquipment* dragged=m_pCharacter?reinterpret_cast<combine_controls::UIFields*>(m_pGameUI)->dragged:0;
 if(dragged&&dragged->ISA(static_cast<UNITTYPES::EUNITTYPES>(120))) {
  m_pForeground->setVisible(true);m_pForeground->moveToFront();
  m_pSocketedIconParent->setVisible(true);m_pSocketedIconParent->moveToFront();
 }else {
  if(m_pHoverObject&&reinterpret_cast<combine_controls::HoverState*>(m_pHoverObject)->flag198)m_pHoverObject=0;
  if(!m_pHoverObject){m_pSocketedIconParent->setVisible(false);m_pForeground->setVisible(false);}
 }
 if(!m_bHover) {
  if(m_pSlotGlow->getParent()&&m_pSlotGlow->getParent()->isChild(m_pSlotGlow))m_pSlotGlow->getParent()->removeChildWindow(m_pSlotGlow);
  m_pHoverObject=0;
 }
 m_ClickedSlot=-1;m_RightClickedSlot=-1;return result;
}

bool CCombineMenu::handle_MouseOver(const CEGUI::EventArgs& event) {
 CEGUI::Window* window=static_cast<const CEGUI::WindowEventArgs&>(event).window;
 CCharacter* owner=m_pCharacter;
 if(window&&owner) {
  int slot=*static_cast<int*>(window->getUserData());
  CEquipment* item=owner->m_pInventory->getEquipmentInSlot(m_aiSlotData[slot]);
  if(item) {
   m_pHoverObject=item;
   if((item->m_bUnknown348&&item->m_iSocketCount)||item->ISA(static_cast<UNITTYPES::EUNITTYPES>(120))) {
    m_pForeground->setVisible(true);m_pForeground->moveToFront();
    m_pSocketedIconParent->setVisible(true);m_pSocketedIconParent->moveToFront();
   }else {m_pSocketedIconParent->setVisible(false);m_pForeground->setVisible(false);}
  }
  float width=m_pSocketedSizeWindows[slot]->getWidth().asAbsolute(0.0f);
  float height=m_pSocketedSizeWindows[slot]->getHeight().asAbsolute(0.0f);
  if(!m_pSocketedSizeWindows[slot]->isChild(m_pSlotGlow))m_pSocketedSizeWindows[slot]->addChildWindow(m_pSlotGlow);
  m_pSlotGlow->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f,0.0f),CEGUI::UDim(0.0f,0.0f)));
  m_pSlotGlow->setSize(CEGUI::UVector2(CEGUI::UDim(0.0f,width),CEGUI::UDim(0.0f,height)));
  m_pSlotGlow->moveToBack();m_bHover=true;
 }
 return true;
}

#include "MasterResourceManager.h"
#include "SoundBankDataInformation.h"
#include "SoundData.h"
CCombineMenu::CCombineMenu(CGameUI& ui,CSettings& settings,Ogre::RenderWindow* render,
 Ogre::SceneManager* scene,CEGUI::Window* parent,CResourceManager* resources)
 :m_pParent(parent),m_pOwner(0),m_pCharacter(0),m_bOpen(false),m_bFullyClosed(true),m_bCloseRequested(false),
 m_pSettings(&settings),m_pGameUI(&ui),m_pSceneManager(scene),m_pRenderWindow(render),m_pMenuModel(0),
 m_pResourceManager(resources),m_fPanelX(0.0f),m_pSoundBank(0),m_ClickedSlot(-1),m_RightClickedSlot(-1),m_pHoverObject(0),m_bHover(false)
{
 CSoundBankDataInformation* sounds=CMasterResourceManager::getSingleton()->m_pSoundBankDataInformation;
 m_pSoundBank=new CSoundBank(*CMasterResourceManager::getSingleton()->m_pSoundManager,false);
 CSoundData* open=sounds->getSoundDataObject(L"STATSOPEN");if(open)m_pSoundBank->addSample(22,open->m_iGuid);
 CSoundData* close=sounds->getSoundDataObject(L"STATSCLOSE");if(close)m_pSoundBank->addSample(66,close->m_iGuid);
 CSoundData* error=sounds->getSoundDataObject(L"ERROR");if(error)m_pSoundBank->addSample(24,error->m_iGuid);
 CSoundData* mana=sounds->getSoundDataObject(L"LOWMANA");if(mana)m_pSoundBank->addSample(35,mana->m_iGuid);
 CSoundData* reveal=sounds->getSoundDataObject(L"REVEAL");if(reveal)m_pSoundBank->addSample(36,reveal->m_iGuid);
 CSoundData* buy=sounds->getSoundDataObject(L"GOLDBUY");if(buy)m_pSoundBank->addSample(23,buy->m_iGuid);
 createMenus();
}
CCombineMenu::~CCombineMenu() {
 m_OriginalItemLocations.clear();setPlayer(0);
 if(m_pMenuModel){delete m_pMenuModel;m_pMenuModel=0;}
 if(m_pSoundBank){delete m_pSoundBank;m_pSoundBank=0;}
}

void CCombineMenu::setOpen(bool open) {
 if(!m_bOpen&&open) {
  m_OriginalItemLocations.clear();
  m_pSettings->GetInt(KSETTINGS_RES_WIDTH);m_pSettings->GetInt(KSETTINGS_RES_HEIGHT);
  m_pSoundBank->playSample(22,0,0.0f,0.0f,false);m_pMenuModel->setVisible(true);
  if(m_pMenuModel->animationPlaying("CLOSE"))m_pMenuModel->blendAnimation("OPEN",false,0.1f,2.0f,-1.0f);
  else m_pMenuModel->playAnimation("OPEN",false,2.0f,-1.0f);
  m_pMenuModel->queueBlendAnimation("IDLE",true,0.1f,1.0f);
  m_pParent->addChildWindow(m_pBackground);m_pBackground->moveToBack();m_pGameUI->queueTip(static_cast<EContextTip>(14));
 }else if(m_bOpen&&!open) {
  if(m_pCharacter)for(unsigned i=0;i<4;++i) {
   CEquipment* item=m_pCharacter->m_pInventory->getEquipmentInSlot(m_aiSlotData[i]);
   if(item){g_bDontTrackItemEquipAndUnEquip=true;m_pCharacter->m_pInventory->removeEquipment(item);returnItemsToCorrectLocation(item);g_bDontTrackItemEquipAndUnEquip=false;}
  }
  m_OriginalItemLocations.clear();m_pSoundBank->playSample(66,0,0.0f,0.0f,false);
  m_pMenuModel->blendAnimation("CLOSE",false,0.1f,2.0f,-1.0f);m_bFullyClosed=false;
 }
 m_bOpen=open;if(open)updateLayout();
}
#include <OgreSkeletonInstance.h>
#include <OgreBone.h>
namespace combine_animation {
struct ModelFields {char prefix[0x60];Ogre::Entity* entity;char gap68[0x130-0x68];Ogre::SkeletonInstance* skeleton;};
inline __attribute__((always_inline)) ModelFields& model(CGenericModel* p){return *reinterpret_cast<ModelFields*>(p);}
}
void CCombineMenu::update(float elapsed) {
 int width=m_pSettings->GetInt(KSETTINGS_RES_WIDTH);int height=m_pSettings->GetInt(KSETTINGS_RES_HEIGHT);
 if(!m_bOpen){m_pHoverObject=0;m_pSocketedIconParent->setVisible(false);m_pForeground->setVisible(false);}
 if(m_bOpen||!m_bFullyClosed) {
  if(m_pMenuModel) {
   m_pMenuModel->updateAnimation(elapsed,false);combine_animation::model(m_pMenuModel).entity->_updateAnimation();
   Ogre::Bone* bone=combine_animation::model(m_pMenuModel).skeleton->getBone("tag_dropdowntop");
   Ogre::Vector3 position=m_pMenuModel->getPosition(false);
   const Ogre::Vector3& offset=bone->_getDerivedPosition();
   float x=position.x+offset.x;float y=position.y+offset.y;
   x=m_pGameUI->scaledY(x);y=m_pGameUI->scaledY(y);
   m_pPanel->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f,float(width)*0.5f+x),CEGUI::UDim(0.0f,-(y+float(height)*-0.5f))));
  }
  if(!m_bOpen&&!m_bFullyClosed&&!m_pMenuModel->animationPlaying("CLOSE")&&!m_pMenuModel->animationQueued("CLOSE")) {
   m_pMenuModel->setVisible(false);m_pParent->removeChildWindow(m_pBackground);m_bFullyClosed=true;
  }
 }
}

#include "Level.h"
void CCombineMenu::itemUpdatedInMenu(CEquipment* item,bool added) {
 if(g_bDontTrackItemEquipAndUnEquip)return;
 std::map<CEquipment*,std::pair<CInventory*,EEQUIP_LOCATIONS> >::iterator found=m_OriginalItemLocations.find(item);
 if(added) {
  if(found==m_OriginalItemLocations.end()&&item->m_pInventory)
   m_OriginalItemLocations[item]=std::make_pair(item->m_pInventory,static_cast<EEQUIP_LOCATIONS>(item->m_iUnknown298));
 }else if(found!=m_OriginalItemLocations.end())m_OriginalItemLocations.erase(found);
}
namespace combine_items {
inline __attribute__((always_inline)) void drop(CCombineMenu* menu,CEquipment* item) {
 Ogre::Vector3 position=menu->m_pCharacter->getPosition(true);
 menu->m_pCharacter->getLevel()->addItem(item,position,true);item->drop();
}
}
void CCombineMenu::returnItemsToCorrectLocation(CEquipment* item) {
 if(!item)return;
 CCharacter* player=m_pCharacter;CInventory* inventory=player?player->m_pInventory:0;
 std::map<CEquipment*,std::pair<CInventory*,EEQUIP_LOCATIONS> >::iterator found=m_OriginalItemLocations.find(item);
 if(found!=m_OriginalItemLocations.end()) {
  inventory=found->second.first;EEQUIP_LOCATIONS location=found->second.second;
  if(!inventory) {combine_items::drop(this,item);m_OriginalItemLocations.erase(found);return;}
  if(static_cast<int>(location)>=0&&static_cast<int>(location)<=18&&!inventory->getEquipmentEquippedAt(location)&&inventory->equipEquipmentIntoSpecificLocation(item,location)==true) {
   player=m_pCharacter;
  }else {
   if(!inventory->pickupEquipment(item,true))combine_items::drop(this,item);
   m_OriginalItemLocations.erase(found);return;
  }
 }
 if(player&&inventory&&!inventory->isEquipmentInInventory(item)) {
  if(!inventory->pickupEquipment(item,true))combine_items::drop(this,item);
 }
 if(found!=m_OriginalItemLocations.end())m_OriginalItemLocations.erase(found);
}
void CCombineMenu::equipmentUsed(CEquipment* item) {
 if(!g_bDontTrackItemEquipAndUnEquip)returnItemsToCorrectLocation(item);
 updateLayout();
}
