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
