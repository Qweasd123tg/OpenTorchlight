#include "EmptyStrings.h"
#include "InventoryMenu.h"

bool CInventoryMenu::handle_RotateLeft(const CEGUI::EventArgs&)
{
    m_bRotateLeft = true;
    return true;
}

bool CInventoryMenu::handle_EndRotateLeft(const CEGUI::EventArgs&)
{
    m_bRotateLeft = false;
    return true;
}

bool CInventoryMenu::handle_RotateRight(const CEGUI::EventArgs&)
{
    m_bRotateRight = true;
    return true;
}

bool CInventoryMenu::handle_EndRotateRight(const CEGUI::EventArgs&)
{
    m_bRotateRight = false;
    return true;
}

#include "Equipment.h"

void CInventoryMenu::equipmentDropped(CEquipment*)
{
    updateLayout();
}

void CInventoryMenu::equipmentEquipped(CEquipment*)
{
    updateLayout();
}

void CInventoryMenu::equipmentUsed(CEquipment*)
{
    updateLayout();
}

#include "InventoryMenu.h"
#include "Equipment.h"
#include "StringUtilities.h"
#include <CEGUI.h>
void CInventoryMenu::setSlotIcon(CEquipment* pItem, int iSlotIndex, int iDataIndex)
{


    unsigned int uiIconX = (unsigned int)(m_pSocketedSizeWindows[iSlotIndex]->getPosition().d_x.asAbsolute(0.0f));
    unsigned int uiIconY = (unsigned int)(m_pSocketedSizeWindows[iSlotIndex]->getPosition().d_y.asAbsolute(0.0f));

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

        pIcon->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f, 0.0f), CEGUI::UDim(0.0f, 1.0f)));
        pIcon->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f, 0.0f), CEGUI::UDim(0.0f, 0.0f)));

        pIcon->setSize(m_pSocketedSizeWindows[iSlotIndex]->getSize());
        pIcon->moveToFront();

        pIcon->setUserData(&m_aiSlotData[iDataIndex]);
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

    if (pItem->m_bUnknown348)
    {
        m_pMainUnidentifiedWindows[iSlotIndex]->setProperty("Image", "");
    }
    else
    {
        m_pMainUnidentifiedWindows[iSlotIndex]->setProperty("Image", CEGUI::PropertyHelper::imageToString(
            &m_pImageset->getImage("unidentified")));
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

#include "InventoryMenu.h"
#include "Inventory.h"
#include "Equipment.h"
#include "Skill.h"
#include "StringTranslate.h"
#include "StringUtilities.h"
#include <CEGUI.h>

void CInventoryMenu::updateLayout()
{
    if (!m_bOpen || !m_pCharacter || !m_pCharacter->m_pInventory)
        return;
    CInventory* inventory = m_pCharacter->m_pInventory;
    while (m_pSocketedIconParent->getChildCount())
        m_pSocketedIconParent->removeChildWindow(m_pSocketedIconParent->getChildAtIdx(0));
    // The original removes one child per equipment slot, not all children.
    for (unsigned i = 0; i < 12; ++i)
        if (m_pSocketedSizeWindows[i] && m_pSocketedSizeWindows[i]->getChildCount())
            m_pSocketedSizeWindows[i]->removeChildWindow(m_pSocketedSizeWindows[i]->getChildAtIdx(0));

    for (unsigned i = 0; i < 12; ++i)
    {
        if (!m_pSocketedSizeWindows[i]) continue;
        CEquipmentRef* ref = reinterpret_cast<CEquipmentRef*>(inventory->getEquipmentRefInSlot(i));
        if (!ref)
        {
            // The inventory query is a call boundary; the slot pointer is re-read.
            if (!m_pSocketedSizeWindows[i]) continue;
            m_pMainUnidentifiedWindows[i]->setProperty("Image", "");
            m_pMainSocketGlowWindows[i]->setProperty("Image", "");
            m_pMainSocketGlowWindows[i]->setSize(m_pSocketedSizeWindows[i]->getSize());
            m_pMainGlowWindows[i]->setProperty("Image", "");
            m_pMainGlowWindows[i]->setSize(m_pSocketedSizeWindows[i]->getSize());
            m_pSocketedSizeWindows[i]->setProperty("Image", m_DefaultSlotImages[i]);
            m_pSocketedSizeWindows[i]->setTooltipText(CEGUI::String(m_DefaultSlotTooltips[i].c_str()));
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
        const float socketX = m_pSocketedSizeWindows[i]->getPosition().d_x.asAbsolute(0.0f);
        float socketY = m_pSocketedSizeWindows[i]->getPosition().d_y.asAbsolute(0.0f);
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
        if (item->m_bUnknown348)
            m_pMainUnidentifiedWindows[i]->setProperty("Image", "");
        else
            m_pMainUnidentifiedWindows[i]->setProperty("Image", CEGUI::PropertyHelper::imageToString(&m_pImageset->getImage("unidentified")));
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
                    gemIcon->setPosition(CEGUI::UVector2(CEGUI::UDim(0,socketX), CEGUI::UDim(0,socketY)));
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
            CEGUI::UVector2 size = m_pSocketedSizeWindows[i]->getSize();
            const float width = size.d_x.asAbsolute(0.0f);
            const float oldHeight = size.d_y.asAbsolute(0.0f);
            const float height = width * 1.5f;
            size.d_x = CEGUI::UDim(0,width);
            size.d_y = CEGUI::UDim(0,height);
            icon->setPosition(CEGUI::UVector2(CEGUI::UDim(0,0),CEGUI::UDim(0,-((height-oldHeight)*0.5f))));
            icon->setSize(size);
            icon->moveToFront();
            icon->update(0.001f);
        }
        m_pSocketedSizeWindows[i]->setTooltipText(CEGUI::String(reinterpret_cast<const unsigned char*>("")));
    }
    for (unsigned i = 19; i < 82; ++i)
    {
        m_pMainGlowWindows[i]->setProperty("Image", "");
        m_pMainSocketGlowWindows[i]->setProperty("Image", "");
        m_pMainUnidentifiedWindows[i]->setProperty("Image", "");
        if (m_pMainStackWindows[i])
            m_pMainStackWindows[i]->setText(CEGUI::String(reinterpret_cast<const unsigned char*>("")));
        if (m_pSocketedSizeWindows[i]->getChildCount())
            m_pSocketedSizeWindows[i]->removeChildWindow(m_pSocketedSizeWindows[i]->getChildAtIdx(0));
    }
    // Typed view of the established +0x30 list; keep the shared partial
    // Inventory declaration unchanged until its own constructor is recovered.
    const TArrayList<CEquipmentRef*>& equipmentRefs =
        *reinterpret_cast<const TArrayList<CEquipmentRef*>*>(inventory->m_Unknown30);
    for (unsigned i = 0; i < equipmentRefs.size(); ++i)
    {
        CEquipmentRef* ref = equipmentRefs[i];
        CEquipment* item = static_cast<CEquipment*>(ref->m_pUnknown10);
        if (ref->m_iSlot > 18)
            setSlotIcon(item, equipmentRefs[i]->m_iSlot, equipmentRefs[i]->m_iSlot);
    }
    for (unsigned i = 0; i < 4; ++i)
    {
        if (!m_pSpellWindows[i]) continue;
        static std::wstring g_RemoveASpell;
        if (g_RemoveASpell.empty())
            g_RemoveASpell = CStringTranslate::getSinglton()->getTranslateString(L"Hold [CTRL] and left-click to");
        static std::wstring g_RemoveASpell2;
        if (g_RemoveASpell2.empty())
            g_RemoveASpell2 = CStringTranslate::getSinglton()->getTranslateString(L"un-learn this spell");
        static std::wstring g_DragASpell;
        if (g_DragASpell.empty())
            g_DragASpell = CStringTranslate::getSinglton()->getTranslateString(L"Drag a spell here to learn it");
        CSkill* spell = m_pCharacter->getKnownSpell(i);
        if (spell && !spell->getSkillIcon().empty())
        {
            m_pSpellWindows[i]->setProperty("Image", CEGUI::PropertyHelper::imageToString(m_pGameUI->getImageFromImageSet(
                reinterpret_cast<const unsigned char*>(STRINGS::StringConvertToNarrow(spell->getSkillIcon().c_str()).c_str()))));
            m_SpellGuids[i] = spell->m_Guid;
            m_pSpellWindows[i]->setUserData(&m_SpellGuids[i]);
            m_pSpellWindows[i]->setTooltipText(CEGUI::String(reinterpret_cast<const unsigned char*>(STRINGS::StringConvertToUTF8(
                std::wstring((g_RemoveASpell + L"\n" + g_RemoveASpell2).c_str())).c_str())));
        }
        else
        {
            m_pSpellWindows[i]->setTooltipText(CEGUI::String(reinterpret_cast<const unsigned char*>(STRINGS::StringConvertToUTF8(std::wstring(g_DragASpell.c_str())).c_str())));
            m_pSpellWindows[i]->setProperty("Image", "");
            m_pSpellWindows[i]->setUserData(&m_NoSpell);
        }
    }
    m_pBackground->moveToBack();
    m_pForeground48->moveToFront();
    m_pPanel->moveToFront();
    m_pSocketedIconParent->moveToFront();
    m_pForeground38->moveToFront();
}

#include "EmptyStrings.h"
#include "InventoryMenu.h"
#include <CEGUI.h>
#include <OgreCamera.h>
#include <OgreSceneManager.h>
#include <OgreMesh.h>
#include <OgreEntity.h>
#include "DynamicPropertyFile.h"
#include "GameVariables.h"
#include "Settings.h"
#include "StringUtilities.h"
#include "ResourceManager.h"
#include "GenericModel.h"
#include "FileSystem.h"
#include "EquipmentDefines.h"
#include "SkillTooltip.h"
namespace inventory_create_detail { struct UIRoot { char pad[0x488];CEGUI::Window* root; }; }
inline __attribute__((always_inline))
CSkillTooltip::CSkillTooltip(CGameUI* ui,CEGUI::Window* root):m_pGameUI(ui),m_sText(EMPTY_WSTRING),m_iIndex(-1),m_pRoot(root) {}
__attribute__((flatten)) void CInventoryMenu::createMenus()
{
    float fResWidth  = (float)m_pDynamicPropertyFile->GetInt(KSETTINGS_RES_WIDTH);
    float fResHeight = (float)m_pDynamicPropertyFile->GetInt(KSETTINGS_RES_HEIGHT);
    m_pInventoryModel = m_pResourceManager->createGenericModel(
        m_pInventorySceneManager,
        L"media/ui/models/inventory/inventory.mesh",
        L"",
        false, false, false);
    m_pInventoryModel->generateExtremes(5,true);
    m_pInventoryModel->getEntity()->getMesh()->_setBounds(
        Ogre::AxisAlignedBox(
            Ogre::Vector3(-100000.0f, -100000.0f, -100000.0f),
            Ogre::Vector3( 100000.0f,  100000.0f,  100000.0f)),
        true);
    float fScale = fResWidth - (fResHeight / 0.75f);
    fScale /= m_pDynamicPropertyFile->GetFloat(KSETTINGS_YRATIO);
    m_pInventoryModel->setPosition(0.5f * fScale, 0.0f, 0.0f);
    m_pInventoryModel->setVisible(false);
    m_pImageset = CEGUI::ImagesetManager::getSingleton().getImageset("UIIcons");
    m_pBackground = CEGUI::WindowManager::getSingleton().createWindow(
        "DefaultWindow", "InventorySheet", "");
    m_pBackground->setSize(CEGUI::UVector2(CEGUI::UDim(1.0f, 0.0f),
                                          CEGUI::UDim(1.0f, 0.0f)));
    m_pBackground->setProperty("RiseOnClick", "False");
    m_pBackground->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f, 0.0f),
                                              CEGUI::UDim(0.0f, 0.0f)));
    m_pBackground->setMousePassThroughEnabled(true);
    m_pBackground->setZOrderingEnabled(false);
    {
        CEGUI::Event::Connection conn = m_pBackground->subscribeEvent(
            CEGUI::Window::EventMouseMove,             
            CEGUI::SubscriberSlot(&CInventoryMenu::handle_MouseThrough, this));
        (void)conn;
    }
    {
        std::wstring layoutProbePath(L"media/ui/inventorymenu.layout");
        CFileInfo fileInfo;
        CFileSystem::getSingleton()->getFileInfo(
            layoutProbePath,
            fileInfo,
            false,   
            true,    
            false);  
        CEGUI::String layoutName(fileInfo.m_sResourceName.c_str());
        CEGUI::Window* layoutRoot =
            CEGUI::WindowManager::getSingleton().loadWindowLayout(layoutName, true);
        m_pGameUI->convertToScreenScale(layoutRoot, false);
        m_pGameUI->mapToFunctions(layoutRoot);
        mapEventHandlers(layoutRoot);
        {
            CEGUI::String blockerName("Blocker");   
            CEGUI::Window* blocker =
                layoutRoot->recursiveChildSearch(blockerName);
            blocker->getParent()->removeChildWindow(blocker);
            m_pBackground->addChildWindow(blocker);
            blocker->setProperty("RiseOnClick", "False");
            blocker->moveToBack();
            blocker->setZOrderingEnabled(false);
        }
        {
            CEGUI::String bottomName("BottomFrame");  
            m_pForeground48 = layoutRoot->recursiveChildSearch(bottomName);
            m_pForeground48->getParent()->removeChildWindow(m_pForeground48);
            m_pBackground->addChildWindow(m_pForeground48);
            m_pForeground48->setProperty("RiseOnClick", "False");
            m_pForeground48->moveToFront();
            m_pForeground48->setZOrderingEnabled(false);
        }
        {
            CEGUI::String topName("TopFrame");      
            m_pPanel = layoutRoot->recursiveChildSearch(topName);
            m_pPanel->getParent()->removeChildWindow(m_pPanel);
            m_pBackground->addChildWindow(m_pPanel);
            m_pPanel->setProperty("RiseOnClick", "False");
            m_pPanel->moveToFront();
            m_pPanel->setZOrderingEnabled(false);
        }
    }
    m_pSocketedIconParent = CEGUI::WindowManager::getSingleton().createWindow(
        "DefaultWindow", "ISockets", "");
    m_pPanel->addChildWindow(m_pSocketedIconParent);
    m_pSocketedIconParent->setSize(m_pPanel->getSize());
    m_pSocketedIconParent->setProperty("RiseOnClick", "False");
    m_pSocketedIconParent->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f, 0.0f),
                                                      CEGUI::UDim(0.0f, 0.0f)));
    m_pSocketedIconParent->setMousePassThroughEnabled(true);
    m_pSocketedIconParent->moveToFront();
    m_pForeground38 = CEGUI::WindowManager::getSingleton().createWindow(
        "DefaultWindow", "ISocketsO", "");
    m_pPanel->addChildWindow(m_pForeground38);
    m_pForeground38->setSize(m_pPanel->getSize());
    m_pForeground38->setProperty("RiseOnClick", "False");
    m_pForeground38->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f, 0.0f),
                                             CEGUI::UDim(0.0f, 0.0f)));
    m_pForeground38->setMousePassThroughEnabled(true);
    m_pForeground38->moveToFront();
    m_pIconParent = CEGUI::WindowManager::getSingleton().createWindow(
        "DefaultWindow", "IIcons", "");
    m_pPanel->addChildWindow(m_pIconParent);
    m_pIconParent->setSize(m_pPanel->getSize());
    m_pIconParent->setProperty("RiseOnClick", "False");
    m_pIconParent->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f, 0.0f),
                                             CEGUI::UDim(0.0f, 0.0f)));
    m_pIconParent->setMousePassThroughEnabled(true);
    m_pIconParent->moveToFront();
    {
        CEGUI::String glowName("SlotGlow");    
        m_pSlotGlow = m_pPanel->recursiveChildSearch(glowName);
        m_pSlotGlow->setMutedState(true);
        m_pSlotGlow->setMousePassThroughEnabled(true);
        m_pSlotGlow->setRiseOnClickEnabled(false);
        m_pSlotGlow->getParent()->removeChildWindow(m_pSlotGlow);
    }
    {
        CEGUI::String closeName("Close");      
        CEGUI::Window* closeButton =
            m_pPanel->recursiveChildSearch(closeName);
        closeButton->setRiseOnClickEnabled(false);
        closeButton->moveToFront();
        CEGUI::Event::Connection conn = closeButton->subscribeEvent(
            CEGUI::Window::EventMouseButtonDown,   
            CEGUI::SubscriberSlot(&CInventoryMenu::handle_CloseButton, this));
        (void)conn;
    }
    {
        CEGUI::Window* paperdoll=m_pPanel->recursiveChildSearch("PaperdollEquip");
        paperdoll->moveToFront();
        paperdoll->setRiseOnClickEnabled(false);
        paperdoll->setWantsMultiClickEvents(false);
        paperdoll->setUserData(&m_aiSlotData[999]);
        paperdoll->subscribeEvent(CEGUI::Window::EventMouseButtonDown,CEGUI::SubscriberSlot(&CInventoryMenu::handle_ItemClick,this));
    }
    {
        CEGUI::Window* rotate=m_pPanel->recursiveChildSearch("RotateLeft");
        rotate->setRiseOnClickEnabled(false);
        rotate->moveToFront();
        rotate->subscribeEvent(CEGUI::Window::EventMouseButtonDown,CEGUI::SubscriberSlot(&CInventoryMenu::handle_RotateLeft,this));
        rotate->subscribeEvent(CEGUI::Window::EventMouseButtonUp,CEGUI::SubscriberSlot(&CInventoryMenu::handle_EndRotateLeft,this));
        rotate->subscribeEvent(CEGUI::Window::EventMouseLeaves,CEGUI::SubscriberSlot(&CInventoryMenu::handle_EndRotateLeft,this));
    }
    {
        CEGUI::Window* rotate=m_pPanel->recursiveChildSearch("RotateRight");
        rotate->setRiseOnClickEnabled(false);
        rotate->moveToFront();
        rotate->subscribeEvent(CEGUI::Window::EventMouseButtonDown,CEGUI::SubscriberSlot(&CInventoryMenu::handle_RotateRight,this));
        rotate->subscribeEvent(CEGUI::Window::EventMouseButtonUp,CEGUI::SubscriberSlot(&CInventoryMenu::handle_EndRotateRight,this));
        rotate->subscribeEvent(CEGUI::Window::EventMouseLeaves,CEGUI::SubscriberSlot(&CInventoryMenu::handle_EndRotateRight,this));
    }
    for(unsigned i=0;i<12;++i) {
        m_pSocketedSizeWindows[i]=NULL;
        m_pMainGlowWindows[i]=NULL;
        m_pMainStackWindows[i]=NULL;
        m_pMainSocketGlowWindows[i]=NULL;
        if(KEquipmentIconName[i].empty())continue;
        CEGUI::Window* slot=m_pPanel->recursiveChildSearch(KEquipmentIconName[i].c_str());
        slot->setRiseOnClickEnabled(false);
        slot->setWantsMultiClickEvents(false);
        slot->setUserData(&m_aiSlotData[i]);
        slot->subscribeEvent(CEGUI::Window::EventMouseButtonDown,CEGUI::SubscriberSlot(&CInventoryMenu::handle_ItemClick,this));
        slot->subscribeEvent(CEGUI::Window::EventMouseEnters,CEGUI::SubscriberSlot(&CInventoryMenu::handle_MouseOver,this));
        slot->subscribeEvent(CEGUI::Window::EventMouseMove,CEGUI::SubscriberSlot(&CInventoryMenu::handle_MouseOver,this));
        slot->subscribeEvent(CEGUI::Window::EventMouseLeaves,CEGUI::SubscriberSlot(&CInventoryMenu::handle_MouseOut,this));
        slot->moveToFront();
        m_pSocketedSizeWindows[i]=slot;
        m_DefaultSlotImages[i]=slot->getProperty("Image");
        m_DefaultSlotTooltips[i]=slot->getTooltipText();
        m_pMainStackWindows[i]=NULL;
        {
            CEGUI::Window* overlay=CEGUI::WindowManager::getSingleton().createWindow("GuiLook/StaticImage",STRINGS::uniqueName(std::string("gui_")).c_str(),"");
            m_pPanel->addChildWindow(overlay);
            overlay->setRiseOnClickEnabled(false);
            overlay->setWantsMultiClickEvents(false);
            overlay->setMousePassThroughEnabled(true);
            overlay->setMutedState(true);
            overlay->setPosition(slot->getPosition());
            overlay->setSize(slot->getSize());
            m_pMainGlowWindows[i]=overlay;
        }
        {
            CEGUI::Window* overlay=CEGUI::WindowManager::getSingleton().createWindow("GuiLook/StaticImage",STRINGS::uniqueName(std::string("gui_")).c_str(),"");
            m_pForeground38->addChildWindow(overlay);
            overlay->setRiseOnClickEnabled(false);
            overlay->setWantsMultiClickEvents(false);
            overlay->setMousePassThroughEnabled(true);
            overlay->setMutedState(true);
            overlay->setPosition(slot->getPosition());
            overlay->setSize(slot->getSize());
            m_pMainSocketGlowWindows[i]=overlay;
        }
        {
            CEGUI::Window* overlay=CEGUI::WindowManager::getSingleton().createWindow("GuiLook/StaticImage",STRINGS::uniqueName(std::string("gui_")).c_str(),"");
            m_pIconParent->addChildWindow(overlay);
            overlay->setRiseOnClickEnabled(false);
            overlay->setWantsMultiClickEvents(false);
            overlay->setMousePassThroughEnabled(true);
            overlay->setMutedState(true);
            overlay->setPosition(slot->getPosition());
            overlay->setSize(slot->getSize());
            m_pMainUnidentifiedWindows[i]=overlay;
        }
    }
    for(int i=0;i<1000;++i)m_aiSlotData[i]=i;
    for(int i=0;i<99;++i)m_SpellGuids[i]=i;
    m_NoSpell=99;
    m_pBackpackTab=m_pForeground48->recursiveChildSearch("TabBackpack");
    m_TabUnselectedImages[0]=m_pBackpackTab->getProperty("UnselectedImage");
    m_TabSelectedImages[0]=m_pBackpackTab->getProperty("SelectedImage");
    m_pSpellsTab=m_pForeground48->recursiveChildSearch("TabSpell");
    m_TabUnselectedImages[1]=m_pSpellsTab->getProperty("UnselectedImage");
    m_TabSelectedImages[1]=m_pSpellsTab->getProperty("SelectedImage");
    m_pFishTab=m_pForeground48->recursiveChildSearch("TabFish");
    m_TabUnselectedImages[2]=m_pFishTab->getProperty("UnselectedImage");
    m_TabSelectedImages[2]=m_pFishTab->getProperty("SelectedImage");
    m_pBackpackTab->setZOrderingEnabled(false);
    m_pSpellsTab->setZOrderingEnabled(false);
    m_pFishTab->setZOrderingEnabled(false);
    m_pBackpackSlots=m_pForeground48->recursiveChildSearch("SlotsEquipment");
    m_pSpellsSlots=m_pForeground48->recursiveChildSearch("SlotsSpells");
    m_pSpellsSlots->setVisible(false);
    m_pFishSlots=m_pForeground48->recursiveChildSearch("SlotsFish");
    m_pFishSlots->setVisible(false);
    for (int i = 1; i != 64; ++i)
    {
        const int idx = 19 + (i - 1);   
        std::string petSlotName =
            std::string("Slot") + STRINGS::GetValueAsString(i);
        CEGUI::String petSlotNameCegui(petSlotName.c_str());
        CEGUI::Window* slot =
            m_pForeground48->recursiveChildSearch(petSlotNameCegui);
        slot->moveToFront();
        slot->setRiseOnClickEnabled(false);
        slot->setWantsMultiClickEvents(false);
        slot->setUserData(&m_aiSlotData[i + 18]);
        {
            slot->subscribeEvent(
                CEGUI::Window::EventMouseButtonDown,  
                CEGUI::SubscriberSlot(&CInventoryMenu::handle_ItemClick, this));
            slot->subscribeEvent(
                CEGUI::Window::EventMouseEnters,     
                CEGUI::SubscriberSlot(&CInventoryMenu::handle_MouseOver, this));
            slot->subscribeEvent(
                CEGUI::Window::EventMouseMove,       
                CEGUI::SubscriberSlot(&CInventoryMenu::handle_MouseOver, this));
            slot->subscribeEvent(
                CEGUI::Window::EventMouseLeaves,     
                CEGUI::SubscriberSlot(&CInventoryMenu::handle_MouseOut, this));
        }
        m_pSocketedSizeWindows[idx] = slot;                 
        CEGUI::Window* label = NULL;
        {
            std::string autoBase("gui_");
            CEGUI::String  autoName(STRINGS::uniqueName(autoBase).c_str());
            label = CEGUI::WindowManager::getSingleton().createWindow(
                "GuiLook/StaticText", autoName, "");
        }
        m_pMainStackWindows[idx] = label;                
        CEGUI::String fontName("Serif");
        label->setFont(fontName);
        label->setSize(slot->getSize());
        CEGUI::UVector2 labelPos = slot->getPosition();
        label->setProperty("HorzTextFormatting", "RightAligned");
        label->setProperty("VertFormatting", "BottomAligned");
        label->setMousePassThroughEnabled(true);
        label->setPosition(labelPos);
        slot->getParent()->addChildWindow(label);
        label->setText(CEGUI::String(""));
        CEGUI::String textColourName("TextColour");
        CEGUI::String textColourValue(
            CEGUI::PropertyHelper::colourToString(
                CEGUI::colour(1.0f, 1.0f, 1.0f, 1.0f)));
        label->setProperty(textColourName, textColourValue);
        label->setAlwaysOnTop(true);
        CEGUI::Window* overlayA = NULL;
        {
            std::string autoBase("gui_");
            CEGUI::String  autoName(STRINGS::uniqueName(autoBase).c_str());
            overlayA = CEGUI::WindowManager::getSingleton().createWindow(
                "GuiLook/StaticImage", autoName, "");
        }
        slot->getParent()->addChildWindow(overlayA);
        overlayA->setRiseOnClickEnabled(false);
        overlayA->setWantsMultiClickEvents(false);
        overlayA->setMousePassThroughEnabled(true);
        overlayA->setMutedState(true);
        overlayA->setPosition(slot->getPosition());
        overlayA->setSize(slot->getSize());
        m_pMainGlowWindows[idx] = overlayA;           
        CEGUI::Window* overlayB = NULL;
        {
            std::string autoBase("gui_");
            CEGUI::String  autoName(STRINGS::uniqueName(autoBase).c_str());
            overlayB = CEGUI::WindowManager::getSingleton().createWindow(
                "GuiLook/StaticImage", autoName, "");
        }
        m_pForeground38->addChildWindow(overlayB);
        overlayB->setRiseOnClickEnabled(false);
        overlayB->setWantsMultiClickEvents(false);
        overlayB->setMousePassThroughEnabled(true);
        overlayB->setMutedState(true);
        overlayB->setPosition(slot->getPosition());
        overlayB->setSize(slot->getSize());
        m_pMainSocketGlowWindows[idx] = overlayB;         
        CEGUI::Window* overlayC = NULL;
        {
            std::string autoBase("gui_");
            CEGUI::String  autoName(STRINGS::uniqueName(autoBase).c_str());
            overlayC = CEGUI::WindowManager::getSingleton().createWindow(
                "GuiLook/StaticImage", autoName, "");
        }
        slot->getParent()->addChildWindow(overlayC);
        overlayC->setRiseOnClickEnabled(false);
        overlayC->setWantsMultiClickEvents(false);
        overlayC->setMousePassThroughEnabled(true);
        overlayC->setMutedState(true);
        overlayC->setPosition(slot->getPosition());
        overlayC->setSize(slot->getSize());
        overlayC->setAlwaysOnTop(true);
        m_pMainUnidentifiedWindows[idx] = overlayC;       
    }
    for(unsigned i=0;i<4;++i) {
        CEGUI::Window* spell=m_pPanel->recursiveChildSearch((std::string("Spell")+STRINGS::GetValueAsString(i+1)).c_str());
        spell->setRiseOnClickEnabled(false);
        spell->setWantsMultiClickEvents(false);
        spell->subscribeEvent(CEGUI::Window::EventMouseEnters,CEGUI::SubscriberSlot(&CInventoryMenu::handle_SpellMouseOver,this));
        spell->subscribeEvent(CEGUI::Window::EventMouseMove,CEGUI::SubscriberSlot(&CInventoryMenu::handle_SpellMouseOver,this));
        spell->subscribeEvent(CEGUI::Window::EventMouseLeaves,CEGUI::SubscriberSlot(&CInventoryMenu::handle_SpellMouseOut,this));
        spell->subscribeEvent(CEGUI::Window::EventMouseButtonDown,CEGUI::SubscriberSlot(&CInventoryMenu::handle_SetSpell,this));
        spell->setID(i);
        m_pSpellWindows[i]=spell;
        spell->setID(i);
    }
    m_pMoneyWindow=m_pForeground48->recursiveChildSearch("Money");
    m_pWeaponSwitchWindow=m_pPanel->recursiveChildSearch("WeaponSwitch");
    m_pWardrobeCamera=m_pWardrobeSceneManager->createCamera("WardrobeCam");
    m_pWardrobeCamera->setPosition(Ogre::Vector3(0.0f,1.0f,3.5f));
    m_pWardrobeCamera->lookAt(Ogre::Vector3(0.0f,1.0f,0.0f));
    m_pWardrobeCamera->setNearClipDistance(0.1f);
    m_pWardrobeCamera->setFarClipDistance(20.0f);
    CEGUI::Window* root=reinterpret_cast<inventory_create_detail::UIRoot*>(m_pGameUI)->root;
    m_pSkillTooltip=new CSkillTooltip(m_pGameUI,root);
    m_pSkillTooltip->load(m_pGameUI,L"media/UI/skilltooltip.layout");
}

#include "SkillManager.h"
#include "SoundBank.h"
#include "UtilitiesMath.h"
#include <OgreSkeletonInstance.h>
#include <OgreBone.h>
#include <OgreViewport.h>
#include <OgreRenderWindow.h>
namespace inventory_update {
struct PointerFields { char prefix[0x12d0]; long x,y; };
}
__attribute__((flatten)) void CInventoryMenu::update(float elapsed)
{
    typedef char parent_offset[__builtin_offsetof(CInventoryMenu,m_pParent)==0x18?1:-1];
    typedef char closed_offset[__builtin_offsetof(CInventoryMenu,m_bFullyClosed)==0x61?1:-1];
    typedef char hover_offset[__builtin_offsetof(CInventoryMenu,m_pHoverObject)==0x1020?1:-1];
    typedef char viewport_offset[__builtin_offsetof(CInventoryMenu,m_pViewport)==0x9158?1:-1];
    typedef char hovered_offset[__builtin_offsetof(CInventoryMenu,m_bSpellHovered)==0x9161?1:-1];
    typedef char guid_offset[__builtin_offsetof(CInventoryMenu,m_HoveredSkillGuid)==0x9168?1:-1];
    typedef char edge_offset[__builtin_offsetof(CInventoryMenu,m_fScreenEdge)==0x9180?1:-1];
    typedef char panel_offset[__builtin_offsetof(CInventoryMenu,m_fPanelX)==0x9184?1:-1];
    typedef char sound_offset[__builtin_offsetof(CInventoryMenu,m_pSoundBank)==0x9188?1:-1];
    typedef char notification_offset[__builtin_offsetof(CInventoryMenu,m_TabNotifications)==0x91a8?1:-1];
    typedef char phase_offset[__builtin_offsetof(CInventoryMenu,m_fTabPhase)==0x91ac?1:-1];
    typedef char secondary_offset[__builtin_offsetof(CCharacter,m_bSecondaryWeaponSet)==0x70e?1:-1];
    typedef char size_check[sizeof(CInventoryMenu)==0x95d0?1:-1];
    float phase=m_fTabPhase+elapsed;
    m_fTabPhase=phase;
    if(phase>=1.0f) {
        do {phase-=1.0f;} while(phase>=1.0f);
        m_fTabPhase=phase;
    }
    for(unsigned i=0;i<3;++i) {
        if(!m_TabNotifications[i])continue;
        CEGUI::Window*& container=i==0?m_pBackpackSlots:i==1?m_pSpellsSlots:m_pFishSlots;
        CEGUI::Window*& tab=i==0?m_pBackpackTab:i==1?m_pSpellsTab:m_pFishTab;
        if(container->isVisible(false)) {
            m_TabNotifications[i]=true;
            tab->setProperty("UnselectedImage",m_TabUnselectedImages[i]);
        } else {
            CEGUI::String& value=m_fTabPhase>0.5f?m_TabSelectedImages[i]:m_TabUnselectedImages[i];
            if(tab->getProperty("UnselectedImage")!=value)tab->setProperty("UnselectedImage",value);
        }
    }
    int width=m_pDynamicPropertyFile->GetInt(KSETTINGS_RES_WIDTH);
    int height=m_pDynamicPropertyFile->GetInt(KSETTINGS_RES_HEIGHT);
    if(m_pCharacter) {
        static std::wstring g_GP;
        if(g_GP.empty())g_GP=CStringTranslate::getSinglton()->getTranslateString(L"GP");
        std::wstring money=g_GP+L":"+STRINGS::GetValueAsWString(m_pCharacter->m_iGold);
        CEGUI::String text(reinterpret_cast<const unsigned char*>(STRINGS::StringConvertToUTF8(std::wstring(money.c_str())).c_str()));
        if(m_pMoneyWindow->getText()!=text)m_pMoneyWindow->setText(text);
        if(static_cast<CEGUI::Checkbox*>(m_pWeaponSwitchWindow)->isSelected()!=m_pCharacter->m_bSecondaryWeaponSet &&
           m_pCharacter->alive() && !m_pCharacter->performingAttackLoose() && !m_pCharacter->performingSkillLoose()) {
            m_pSoundBank->playSample(18,0,0.0f,0.0f,false);
            m_pCharacter->toggleSecondaryWeaponSet();
            updateLayout();
        }
    }
    if(m_bRotateLeft) {
        Ogre::Matrix4 orientation=m_pCharacter->m_pPaperdollModel->getOrientation();
        Ogre::Matrix4 rotation;MATH::matrixRotationY(rotation,elapsed*-1.7453292608261108f);
        orientation=orientation*rotation;
        m_pCharacter->m_pPaperdollModel->setOrientation(orientation,false);
    } else if(m_bRotateRight) {
        Ogre::Matrix4 orientation=m_pCharacter->m_pPaperdollModel->getOrientation();
        Ogre::Matrix4 rotation;MATH::matrixRotationY(rotation,elapsed*1.7453292608261108f);
        orientation=orientation*rotation;
        m_pCharacter->m_pPaperdollModel->setOrientation(orientation,false);
    }
    if(!m_bOpen) {
        m_pHoverObject=0;
        m_pSocketedIconParent->setVisible(false);
        m_pForeground38->setVisible(false);
        if(!m_bOpen && m_bFullyClosed) {
            if(m_pSkillTooltip && m_pSkillTooltip->m_pWindow->getParent())
                m_pSkillTooltip->m_pWindow->getParent()->removeChildWindow(m_pSkillTooltip->m_pWindow);
            return;
        }
    }
    m_pInventoryModel->updateAnimation(elapsed,false);
    m_pInventoryModel->getEntity()->_updateAnimation();
    Ogre::Bone* top=m_pInventoryModel->m_pSkeleton->getBone("tag_topinventory");
    Ogre::Vector3 position=m_pInventoryModel->getPosition(false);
    const Ogre::Vector3& tag=top->_getDerivedPosition();
    float sumY=tag.y+position.y;
    float scaledX=m_pGameUI->scaledY(tag.x+position.x);
    float halfWidth=float(width)*0.5f;
    float panelY=-(float(height)*-0.5f+m_pGameUI->scaledY(sumY));
    m_fPanelX=scaledX+halfWidth;
    m_pPanel->setPosition(CEGUI::UVector2(CEGUI::UDim(0,m_fPanelX),CEGUI::UDim(0,panelY)));
    Ogre::Bone* bottom=m_pInventoryModel->m_pSkeleton->getBone("tag_bottominventory");
    position=m_pInventoryModel->getPosition(false);
    float bottomX=bottom->_getDerivedPosition().x+position.x;
    float scaledBottom=m_pGameUI->scaledY(bottomX);
    float bottomScreen=halfWidth+scaledBottom;
    m_pForeground48->setPosition(CEGUI::UVector2(CEGUI::UDim(0,bottomScreen),CEGUI::UDim(0,panelY)));
    float edge=m_pGameUI->scaledY(50.0f)+bottomScreen;
    m_fScreenEdge=edge<float(width)?edge:float(width);
    if(m_pViewport) {
        float panelX=m_fPanelX;
        float left=(panelX+m_pGameUI->scaledY(124.0f))/float(width);
        float y=m_pGameUI->scaledY(132.0f)/float(height);
        float span=m_pGameUI->scaledY(166.0f)/float(width);
        float h=m_pGameUI->scaledY(192.0f)/float(height);
        if(left+span>1.0f)span=1.0f-left;
        if(y+h>1.0f)h=1.0f-y;
        if(left<0.0f)left=0.0f;
        y=0.0f>y?0.0f:y;
        float minimum=1.0f/float(width);
        if(minimum>span){left=1.0f-minimum;span=minimum;}
        m_pViewport->setDimensions(left,y,span,h);
        m_pWardrobeCamera->setAspectRatio(float(m_pViewport->getActualWidth())/float(m_pViewport->getActualHeight()));
    }
    if(!m_bOpen && !m_bFullyClosed) {
        if(!m_pInventoryModel->animationPlaying("CLOSE") && !m_pInventoryModel->animationQueued("CLOSE")) {
            m_pInventoryModel->setVisible(false);
            m_bFullyClosed=true;
            m_pRenderWindow->removeViewport(3);
            m_pParent->removeChildWindow(m_pBackground);
            m_pViewport=0;
        }
    }
    if(m_bSpellHovered && m_pCharacter) {
        CSkillManager* manager=m_pCharacter->getSkillManager();
        long long guid=m_HoveredSkillGuid;
        if(!manager)return;
        CSkill* skill=manager->getSkillByGuid(guid);
        if(!skill)return;
        inventory_update::PointerFields& mouse=*reinterpret_cast<inventory_update::PointerFields*>(m_pGameUI);
        m_pSkillTooltip->showTooltip(m_pCharacter,skill,float(mouse.x),float(mouse.y));
    } else {
        CEGUI::Window* window=m_pSkillTooltip->m_pWindow;
        if(window->getParent())window->getParent()->removeChildWindow(window);
    }
}

#include "Character.h"
#include "Inventory.h"
namespace inventory_controls {
struct UIFocus {char prefix[0xb8];CBaseUnit* unit;};
struct HoverState {char prefix[0x198];bool flag198;};
struct ActorFields {char prefix[0x70e];bool secondary;};
inline __attribute__((always_inline)) CBaseUnit* focused(CGameUI* ui){return reinterpret_cast<UIFocus*>(ui)->unit;}
inline __attribute__((always_inline)) bool secondary(CCharacter* p){return reinterpret_cast<ActorFields*>(p)->secondary;}
}
void CInventoryMenu::inventoryDestroyed() {}

bool CInventoryMenu::handle_ItemClick(const CEGUI::EventArgs& event) {
 const CEGUI::MouseEventArgs& mouse=static_cast<const CEGUI::MouseEventArgs&>(event);
 if(mouse.window) {
  int slot=*static_cast<int*>(mouse.window->getUserData());
  if(mouse.button==CEGUI::LeftButton)m_ClickedSlot=slot;
  else if(mouse.button==CEGUI::RightButton)m_RightClickedSlot=slot;
 }
 return true;
}

bool CInventoryMenu::handle_MouseThrough(const CEGUI::EventArgs&) {m_InventoryData9160=0;m_bSpellHovered=false;return true;}

bool CInventoryMenu::handle_onClick(const CEGUI::EventArgs& event) {
 const CEGUI::MouseEventArgs& mouse=static_cast<const CEGUI::MouseEventArgs&>(event);
 CEGUI::Window* w=mouse.window;
 if(mouse.button==CEGUI::LeftButton&&w)return onClick(*static_cast<ELayoutFunction*>(w->getUserData()));
 return true;
}

void CInventoryMenu::setTab(int tab) {onClick(static_cast<ELayoutFunction>(static_cast<unsigned>(tab)+14u));}

bool CInventoryMenu::handle_SpellMouseOver(const CEGUI::EventArgs& event) {
 CEGUI::Window* w=static_cast<const CEGUI::WindowEventArgs&>(event).window;
 if(w){long long guid=*static_cast<long long*>(w->getUserData());m_bSpellHovered=true;m_HoveredSkillGuid=guid;}
 return true;
}

bool CInventoryMenu::handle_SpellMouseOut(const CEGUI::EventArgs&) {return true;}

void CInventoryMenu::setOwner(CCharacter* owner) {
 bool changed=owner!=m_pCharacter;
 if(changed)inventoryDestroyed();
 if(m_pCharacter&&m_pCharacter->m_pInventory)m_pCharacter->m_pInventory->removeListener(this);
 m_pCharacter=owner;
 if(owner&&owner->m_pInventory)owner->m_pInventory->addListener(this);
 if(m_pCharacter)static_cast<CEGUI::Checkbox*>(m_pWeaponSwitchWindow)->setSelected(inventory_controls::secondary(m_pCharacter));
 if(changed)updateLayout();
 m_TabNotifications[0]=false;m_TabNotifications[1]=false;m_TabNotifications[2]=false;
}

void CInventoryMenu::checkForUpdate(CEquipment* item) {
 if(item&&m_pCharacter->m_pInventory) {
  int pane=m_pCharacter->m_pInventory->getRequiredPane(item);
  int slot=m_pCharacter->m_pInventory->findEquipmentSlot(item);
  if(slot>18)switch(pane) {
   case 0:if(!m_pBackpackSlots->isVisible(false))m_TabNotifications[0]=true;break;
   case 1:if(!m_pSpellsSlots->isVisible(false))m_TabNotifications[1]=true;break;
   case 2:if(!m_pFishSlots->isVisible(false))m_TabNotifications[2]=true;break;
  }
 }
}

void CInventoryMenu::equipmentUnequipped(CEquipment* item) {checkForUpdate(item);updateLayout();}

void CInventoryMenu::equipmentPickedUp(CEquipment* item) {checkForUpdate(item);updateLayout();}

bool CInventoryMenu::handle_MouseOut(const CEGUI::EventArgs& event) {
 CEGUI::Window* w=static_cast<const CEGUI::WindowEventArgs&>(event).window;
 CCharacter* owner=m_pCharacter;
 if(w&&owner) {
  CEquipment* item=owner->m_pInventory->getEquipmentInSlot(*static_cast<unsigned*>(w->getUserData()));
  if(item==m_pHoverObject) {
   m_pHoverObject=0;
   CBaseUnit* focused=inventory_controls::focused(m_pGameUI);
   if(!focused || !focused->ISA(static_cast<UNITTYPES::EUNITTYPES>(120))) {
    m_pSocketedIconParent->setVisible(false);m_pForeground38->setVisible(false);
   }
  }
 }
 return true;
}

bool CInventoryMenu::processInput(void*,float,bool active) {
 bool result=true;
 if(active) {
  if(m_bCloseRequested){setOpen(false);m_bCloseRequested=0;result=false;}
  CBaseUnit* focused=inventory_controls::focused(m_pGameUI);
  if(focused && focused->ISA(static_cast<UNITTYPES::EUNITTYPES>(120))) {
   m_pForeground38->setVisible(true);m_pForeground38->moveToFront();
   m_pSocketedIconParent->setVisible(true);m_pSocketedIconParent->moveToFront();
  }else {
   if(m_pHoverObject&&reinterpret_cast<inventory_controls::HoverState*>(m_pHoverObject)->flag198)m_pHoverObject=0;
   if(!m_pHoverObject){m_pSocketedIconParent->setVisible(false);m_pForeground38->setVisible(false);}
  }
  if(!m_InventoryData9160) {
   if(m_pPanel->isChild(m_pSlotGlow))m_pPanel->removeChildWindow(m_pSlotGlow);
   else if(m_pForeground48->isChild(m_pSlotGlow))m_pForeground48->removeChildWindow(m_pSlotGlow);
  }
  m_ClickedSlot=-1;m_RightClickedSlot=-1;
 }else {
  m_pHoverObject=0;m_pForeground38->setVisible(false);m_pSocketedIconParent->setVisible(false);
  if(m_pPanel->isChild(m_pSlotGlow))m_pPanel->removeChildWindow(m_pSlotGlow);
  else if(m_pForeground48->isChild(m_pSlotGlow))m_pForeground48->removeChildWindow(m_pSlotGlow);
 }
 return result;
}

bool CInventoryMenu::onClick(ELayoutFunction action) {
 if(m_bOpen) {
  switch(action) {
  case static_cast<ELayoutFunction>(14):
   static_cast<CEGUI::RadioButton*>(m_pBackpackTab)->setSelected(true);
   static_cast<CEGUI::RadioButton*>(m_pSpellsTab)->setSelected(false);
   static_cast<CEGUI::RadioButton*>(m_pFishTab)->setSelected(false);
   m_pBackpackSlots->setVisible(true);
   m_pSpellsSlots->setVisible(false);
   m_pFishSlots->setVisible(false);
   m_TabNotifications[0]=false;
   m_pBackpackTab->setProperty("UnselectedImage",m_TabUnselectedImages[0]);updateLayout();break;
  case static_cast<ELayoutFunction>(15):
   static_cast<CEGUI::RadioButton*>(m_pBackpackTab)->setSelected(false);
   static_cast<CEGUI::RadioButton*>(m_pSpellsTab)->setSelected(true);
   static_cast<CEGUI::RadioButton*>(m_pFishTab)->setSelected(false);
   m_pBackpackSlots->setVisible(false);
   m_pSpellsSlots->setVisible(true);
   m_pFishSlots->setVisible(false);
   m_TabNotifications[1]=false;
   m_pSpellsTab->setProperty("UnselectedImage",m_TabUnselectedImages[1]);updateLayout();break;
  case static_cast<ELayoutFunction>(16):
   static_cast<CEGUI::RadioButton*>(m_pBackpackTab)->setSelected(false);
   static_cast<CEGUI::RadioButton*>(m_pSpellsTab)->setSelected(false);
   static_cast<CEGUI::RadioButton*>(m_pFishTab)->setSelected(true);
   m_pBackpackSlots->setVisible(false);
   m_pSpellsSlots->setVisible(false);
   m_pFishSlots->setVisible(true);
   m_TabNotifications[2]=false;
   m_pFishTab->setProperty("UnselectedImage",m_TabUnselectedImages[2]);updateLayout();break;
  default:break;
  }
 }
 return true;
}
