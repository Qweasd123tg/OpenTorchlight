// Candidate only: compare complete original entry before publication.
#include "EmptyStrings.h"
#include "PetMenu.h"
#include <OgreMesh.h>
#include <OgreCamera.h>
#include <OgreSceneManager.h>
#include <CEGUI.h>
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
namespace pet_create_detail { struct UIRoot { char pad[0x488];CEGUI::Window* root; }; }
inline __attribute__((always_inline))
CSkillTooltip::CSkillTooltip(CGameUI* ui,CEGUI::Window* root):m_pGameUI(ui),m_sText(EMPTY_WSTRING),m_iIndex(-1),m_pRoot(root) {}
__attribute__((flatten)) void CPetMenu::createMenus()
{
    typedef char check_m_pBackground[__builtin_offsetof(CPetMenu,m_pBackground)==32?1:-1];
    typedef char check_m_pPanel[__builtin_offsetof(CPetMenu,m_pPanel)==40?1:-1];
    typedef char check_m_pSocketedIconParent[__builtin_offsetof(CPetMenu,m_pSocketedIconParent)==48?1:-1];
    typedef char check_m_pIconLayer[__builtin_offsetof(CPetMenu,m_pIconLayer)==56?1:-1];
    typedef char check_m_pSocketOverlay[__builtin_offsetof(CPetMenu,m_pSocketOverlay)==64?1:-1];
    typedef char check_m_pForeground48[__builtin_offsetof(CPetMenu,m_pForeground48)==72?1:-1];
    typedef char check_m_pCharacter[__builtin_offsetof(CPetMenu,m_pCharacter)==88?1:-1];
    typedef char check_m_pDynamicPropertyFile[__builtin_offsetof(CPetMenu,m_pDynamicPropertyFile)==136?1:-1];
    typedef char check_m_pGameUI[__builtin_offsetof(CPetMenu,m_pGameUI)==144?1:-1];
    typedef char check_m_aiSlotData[__builtin_offsetof(CPetMenu,m_aiSlotData)==160?1:-1];
    typedef char check_m_pSpellWindows[__builtin_offsetof(CPetMenu,m_pSpellWindows)==4160?1:-1];
    typedef char check_m_SpellGuids[__builtin_offsetof(CPetMenu,m_SpellGuids)==4176?1:-1];
    typedef char check_m_NoSpell[__builtin_offsetof(CPetMenu,m_NoSpell)==4968?1:-1];
    typedef char check_m_pSocketedSizeWindows[__builtin_offsetof(CPetMenu,m_pSocketedSizeWindows)==4984?1:-1];
    typedef char check_m_pMainUnidentifiedWindows[__builtin_offsetof(CPetMenu,m_pMainUnidentifiedWindows)==5640?1:-1];
    typedef char check_m_pMainGlowWindows[__builtin_offsetof(CPetMenu,m_pMainGlowWindows)==6296?1:-1];
    typedef char check_m_pMainSocketGlowWindows[__builtin_offsetof(CPetMenu,m_pMainSocketGlowWindows)==6952?1:-1];
    typedef char check_m_pMainStackWindows[__builtin_offsetof(CPetMenu,m_pMainStackWindows)==7608?1:-1];
    typedef char check_m_DefaultSlotImages[__builtin_offsetof(CPetMenu,m_DefaultSlotImages)==8264?1:-1];
    typedef char check_m_DefaultSlotTooltips[__builtin_offsetof(CPetMenu,m_DefaultSlotTooltips)==22696?1:-1];
    typedef char check_m_pImageset[__builtin_offsetof(CPetMenu,m_pImageset)==37128?1:-1];
    typedef char check_m_pSlotGlow[__builtin_offsetof(CPetMenu,m_pSlotGlow)==37136?1:-1];
    typedef char check_m_pCharacterName[__builtin_offsetof(CPetMenu,m_pCharacterName)==37144?1:-1];
    typedef char check_m_pLevel[__builtin_offsetof(CPetMenu,m_pLevel)==37152?1:-1];
    typedef char check_m_pXP[__builtin_offsetof(CPetMenu,m_pXP)==37208?1:-1];
    typedef char check_m_pHP[__builtin_offsetof(CPetMenu,m_pHP)==37200?1:-1];
    typedef char check_m_pMana[__builtin_offsetof(CPetMenu,m_pMana)==37192?1:-1];
    typedef char check_m_pMeleeDamage[__builtin_offsetof(CPetMenu,m_pMeleeDamage)==37160?1:-1];
    typedef char check_m_pRangedDamage[__builtin_offsetof(CPetMenu,m_pRangedDamage)==37168?1:-1];
    typedef char check_m_pMagicDamage[__builtin_offsetof(CPetMenu,m_pMagicDamage)==37176?1:-1];
    typedef char check_m_pDefense[__builtin_offsetof(CPetMenu,m_pDefense)==37184?1:-1];
    typedef char check_m_pPetSceneManager[__builtin_offsetof(CPetMenu,m_pPetSceneManager)==37216?1:-1];
    typedef char check_m_pWardrobeSceneManager[__builtin_offsetof(CPetMenu,m_pWardrobeSceneManager)==37224?1:-1];
    typedef char check_m_pWardrobeCamera[__builtin_offsetof(CPetMenu,m_pWardrobeCamera)==37232?1:-1];
    typedef char check_m_pPetModel[__builtin_offsetof(CPetMenu,m_pPetModel)==37280?1:-1];
    typedef char check_m_pResourceManager[__builtin_offsetof(CPetMenu,m_pResourceManager)==37288?1:-1];
    typedef char check_m_pBackpackSlots[__builtin_offsetof(CPetMenu,m_pBackpackSlots)==37312?1:-1];
    typedef char check_m_pSpellsSlots[__builtin_offsetof(CPetMenu,m_pSpellsSlots)==37320?1:-1];
    typedef char check_m_pFishSlots[__builtin_offsetof(CPetMenu,m_pFishSlots)==37328?1:-1];
    typedef char check_m_pBackpackTab[__builtin_offsetof(CPetMenu,m_pBackpackTab)==37336?1:-1];
    typedef char check_m_pSpellsTab[__builtin_offsetof(CPetMenu,m_pSpellsTab)==37344?1:-1];
    typedef char check_m_pFishTab[__builtin_offsetof(CPetMenu,m_pFishTab)==37352?1:-1];
    typedef char check_m_pSkillTooltip[__builtin_offsetof(CPetMenu,m_pSkillTooltip)==37360?1:-1];
    typedef char check_m_TabUnselectedImages[__builtin_offsetof(CPetMenu,m_TabUnselectedImages)==37376?1:-1];
    typedef char check_m_TabSelectedImages[__builtin_offsetof(CPetMenu,m_TabSelectedImages)==37904?1:-1];
    typedef char check_size[sizeof(CPetMenu)==0x9620?1:-1];
    float fResWidth  = (float)m_pDynamicPropertyFile->GetInt(KSETTINGS_RES_WIDTH);
    float fResHeight = (float)m_pDynamicPropertyFile->GetInt(KSETTINGS_RES_HEIGHT);
    m_pPetModel = m_pResourceManager->createGenericModel(
        m_pPetSceneManager,
        L"media/ui/models/pet/pet.mesh",
        L"",
        false, false, false);
    m_pPetModel->generateExtremes(5,true);
    m_pPetModel->getEntity()->getMesh()->_setBounds(
        Ogre::AxisAlignedBox(
            Ogre::Vector3(-100000.0f, -100000.0f, -100000.0f),
            Ogre::Vector3( 100000.0f,  100000.0f,  100000.0f)),
        true);
    float fScale = fResWidth - (fResHeight / 0.75f);
    fScale /= m_pDynamicPropertyFile->GetFloat(KSETTINGS_YRATIO);
    m_pPetModel->setPosition(-0.5f * fScale, 0.0f, 0.0f);
    m_pPetModel->setVisible(false);
    m_pImageset = CEGUI::ImagesetManager::getSingleton().getImageset("UIIcons");
    m_pBackground = CEGUI::WindowManager::getSingleton().createWindow(
        "DefaultWindow", "PetSheet", "");
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
            CEGUI::SubscriberSlot(&CPetMenu::handle_MouseThrough, this));
        (void)conn;
    }
    {
        std::wstring layoutProbePath(L"media/ui/petmenu.layout");
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
        m_pCharacterName=layoutRoot->recursiveChildSearch("CharacterName");
        m_pLevel=layoutRoot->recursiveChildSearch("Level");
        m_pXP=layoutRoot->recursiveChildSearch("XP");
        m_pHP=layoutRoot->recursiveChildSearch("HP");
        m_pMana=layoutRoot->recursiveChildSearch("Mana");
        m_pMeleeDamage=layoutRoot->recursiveChildSearch("MeleeDamage");
        m_pRangedDamage=layoutRoot->recursiveChildSearch("RangedDamage");
        m_pMagicDamage=layoutRoot->recursiveChildSearch("MagicDamage");
        m_pDefense=layoutRoot->recursiveChildSearch("Defense");
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
        "DefaultWindow", "PSockets", "");
    m_pPanel->addChildWindow(m_pSocketedIconParent);
    m_pSocketedIconParent->setSize(m_pPanel->getSize());
    m_pSocketedIconParent->setProperty("RiseOnClick", "False");
    m_pSocketedIconParent->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f, 0.0f),
                                                      CEGUI::UDim(0.0f, 0.0f)));
    m_pSocketedIconParent->setMousePassThroughEnabled(true);
    m_pSocketedIconParent->moveToFront();
    m_pSocketOverlay = CEGUI::WindowManager::getSingleton().createWindow(
        "DefaultWindow", "PSocketsO", "");
    m_pPanel->addChildWindow(m_pSocketOverlay);
    m_pSocketOverlay->setSize(m_pPanel->getSize());
    m_pSocketOverlay->setProperty("RiseOnClick", "False");
    m_pSocketOverlay->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f, 0.0f),
                                             CEGUI::UDim(0.0f, 0.0f)));
    m_pSocketOverlay->setMousePassThroughEnabled(true);
    m_pSocketOverlay->moveToFront();
    m_pIconLayer = CEGUI::WindowManager::getSingleton().createWindow(
        "DefaultWindow", "PIcons", "");
    m_pPanel->addChildWindow(m_pIconLayer);
    m_pIconLayer->setSize(m_pPanel->getSize());
    m_pIconLayer->setProperty("RiseOnClick", "False");
    m_pIconLayer->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f, 0.0f),
                                             CEGUI::UDim(0.0f, 0.0f)));
    m_pIconLayer->setMousePassThroughEnabled(true);
    m_pIconLayer->moveToFront();
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
            CEGUI::SubscriberSlot(&CPetMenu::handle_CloseButton, this));
        (void)conn;
    }
    {
        CEGUI::Window* paperdoll=m_pPanel->recursiveChildSearch("PaperdollEquip");
        paperdoll->moveToFront();
        paperdoll->setRiseOnClickEnabled(false);
        paperdoll->setWantsMultiClickEvents(false);
        paperdoll->setUserData(&m_aiSlotData[999]);
        paperdoll->subscribeEvent(CEGUI::Window::EventMouseButtonDown,CEGUI::SubscriberSlot(&CPetMenu::handle_ItemClick,this));
    }
    {
        CEGUI::Window* rotate=m_pPanel->recursiveChildSearch("RotateLeft");
        rotate->setRiseOnClickEnabled(false);
        rotate->moveToFront();
        rotate->subscribeEvent(CEGUI::Window::EventMouseButtonDown,CEGUI::SubscriberSlot(&CPetMenu::handle_RotateLeft,this));
        rotate->subscribeEvent(CEGUI::Window::EventMouseButtonUp,CEGUI::SubscriberSlot(&CPetMenu::handle_EndRotateLeft,this));
        rotate->subscribeEvent(CEGUI::Window::EventMouseLeaves,CEGUI::SubscriberSlot(&CPetMenu::handle_EndRotateLeft,this));
    }
    {
        CEGUI::Window* rotate=m_pPanel->recursiveChildSearch("RotateRight");
        rotate->setRiseOnClickEnabled(false);
        rotate->moveToFront();
        rotate->subscribeEvent(CEGUI::Window::EventMouseButtonDown,CEGUI::SubscriberSlot(&CPetMenu::handle_RotateRight,this));
        rotate->subscribeEvent(CEGUI::Window::EventMouseButtonUp,CEGUI::SubscriberSlot(&CPetMenu::handle_EndRotateRight,this));
        rotate->subscribeEvent(CEGUI::Window::EventMouseLeaves,CEGUI::SubscriberSlot(&CPetMenu::handle_EndRotateRight,this));
    }
    for(unsigned i=0;i<12;++i) {
        m_pSocketedSizeWindows[i]=NULL;
        m_pMainGlowWindows[i]=NULL;
        m_pMainStackWindows[i]=NULL;
        m_pMainSocketGlowWindows[i]=NULL;
        if(KEquipmentIconName[i].empty())continue;
        CEGUI::Window* slot=m_pPanel->recursiveChildSearch(KEquipmentIconName[i].c_str());
        if(!slot)continue;
        slot->moveToFront();
        slot->setRiseOnClickEnabled(false);
        slot->setWantsMultiClickEvents(false);
        slot->setUserData(&m_aiSlotData[i]);
        slot->subscribeEvent(CEGUI::Window::EventMouseButtonDown,CEGUI::SubscriberSlot(&CPetMenu::handle_ItemClick,this));
        slot->subscribeEvent(CEGUI::Window::EventMouseEnters,CEGUI::SubscriberSlot(&CPetMenu::handle_MouseOver,this));
        slot->subscribeEvent(CEGUI::Window::EventMouseMove,CEGUI::SubscriberSlot(&CPetMenu::handle_MouseOver,this));
        slot->subscribeEvent(CEGUI::Window::EventMouseLeaves,CEGUI::SubscriberSlot(&CPetMenu::handle_MouseOut,this));
        slot->moveToFront(); // The original repeats this after binding handlers.
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
            m_pSocketOverlay->addChildWindow(overlay);
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
            slot->getParent()->addChildWindow(overlay);
            overlay->setRiseOnClickEnabled(false);
            overlay->setWantsMultiClickEvents(false);
            overlay->setMousePassThroughEnabled(true);
            overlay->setMutedState(true);
            overlay->setPosition(slot->getPosition());
            overlay->setSize(slot->getSize());
            overlay->setAlwaysOnTop(true);
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
                CEGUI::SubscriberSlot(&CPetMenu::handle_ItemClick, this));
            slot->subscribeEvent(
                CEGUI::Window::EventMouseEnters,     
                CEGUI::SubscriberSlot(&CPetMenu::handle_MouseOver, this));
            slot->subscribeEvent(
                CEGUI::Window::EventMouseMove,       
                CEGUI::SubscriberSlot(&CPetMenu::handle_MouseOver, this));
            slot->subscribeEvent(
                CEGUI::Window::EventMouseLeaves,     
                CEGUI::SubscriberSlot(&CPetMenu::handle_MouseOut, this));
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
        m_pSocketOverlay->addChildWindow(overlayB);
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
        m_pIconLayer->addChildWindow(overlayC);
        overlayC->setRiseOnClickEnabled(false);
        overlayC->setWantsMultiClickEvents(false);
        overlayC->setMousePassThroughEnabled(true);
        overlayC->setMutedState(true);
        overlayC->setPosition(slot->getPosition());
        overlayC->setSize(slot->getSize());
        m_pMainUnidentifiedWindows[idx] = overlayC;       
    }
    for(unsigned i=0;i<2;++i) {
        CEGUI::Window* spell=m_pPanel->recursiveChildSearch((std::string("Spell")+STRINGS::GetValueAsString(i+1)).c_str());
        spell->setRiseOnClickEnabled(false);
        spell->setWantsMultiClickEvents(false);
        spell->subscribeEvent(CEGUI::Window::EventMouseEnters,CEGUI::SubscriberSlot(&CPetMenu::handle_SpellMouseOver,this));
        spell->subscribeEvent(CEGUI::Window::EventMouseMove,CEGUI::SubscriberSlot(&CPetMenu::handle_SpellMouseOver,this));
        spell->subscribeEvent(CEGUI::Window::EventMouseLeaves,CEGUI::SubscriberSlot(&CPetMenu::handle_SpellMouseOut,this));
        spell->subscribeEvent(CEGUI::Window::EventMouseButtonDown,CEGUI::SubscriberSlot(&CPetMenu::handle_SetSpell,this));
        spell->setID(i);
        m_pSpellWindows[i]=spell;
        spell->setID(i);
    }
    m_pWardrobeCamera=m_pWardrobeSceneManager->createCamera("PetWardrobeCam");
    m_pWardrobeCamera->setPosition(Ogre::Vector3(0.0f,1.0f,3.5f));
    m_pWardrobeCamera->lookAt(Ogre::Vector3(0.0f,1.0f,0.0f));
    m_pWardrobeCamera->setNearClipDistance(0.1f);
    m_pWardrobeCamera->setFarClipDistance(20.0f);
    CEGUI::Window* root=reinterpret_cast<pet_create_detail::UIRoot*>(m_pGameUI)->root;
    m_pSkillTooltip=new CSkillTooltip(m_pGameUI,root);
    m_pSkillTooltip->load(m_pGameUI,L"media/UI/skilltooltip.layout");
}

#include "Character.h"
#include "SkillManager.h"
#include "MasterResourceManager.h"
#include "StringTranslate.h"
#include "UtilitiesMath.h"
#include <OgreUTFString.h>
#include <OgreSkeletonInstance.h>
#include <OgreBone.h>
#include <OgreViewport.h>
#include <OgreRenderWindow.h>

namespace pet_update {
struct ActorFields {
    char prefix[0x100]; unsigned level;
    char gap104[0x1c8-0x104]; CSkillManager* skills;
    char gap1d0[0x208-0x1d0]; CPositionableObject* model;
    char gap210[0x330-0x210]; int category;
    char gap334[0x418-0x334]; int baseHealth;
    char gap41c[0x43c-0x41c]; int baseMana;
    char gap440[8]; int experience;
    char gap44c[0x4c0-0x44c]; std::wstring name;
};
struct PointerFields { char prefix[0x12d0]; long x,y; };
inline __attribute__((always_inline)) ActorFields& actor(CCharacter* p) {
    return *reinterpret_cast<ActorFields*>(p);
}
inline __attribute__((always_inline)) CEGUI::String utf8(const std::string& value) {
    return CEGUI::String(reinterpret_cast<const unsigned char*>(value.c_str()));
}
inline __attribute__((always_inline)) bool changed(CEGUI::Window*& window,const std::string& value) {
    if(window->getText()!=value) { window->setText(utf8(value)); return true; }
    return false;
}
inline __attribute__((always_inline)) bool changed(CEGUI::Window*& window,const CEGUI::String& value) {
    if(window->getText()!=value) {
        window->setText(CEGUI::String(reinterpret_cast<const unsigned char*>(value.c_str())));
        return true;
    }
    return false;
}
inline __attribute__((always_inline)) void textColour(CEGUI::Window*& window,int value,int base) {
    window->setProperty("TextColour",value<base?"FFFF0000":value>base?"FFc0c0ff":"FFFFFFFF");
}
inline __attribute__((always_inline)) float maxSecond(float a,float b) { return a>b?a:b; }
}

__attribute__((flatten)) void CPetMenu::update(float elapsed) {
    typedef char check_m_pParent[__builtin_offsetof(CPetMenu,m_pParent)==24?1:-1];
    typedef char check_m_bOpenPartial[__builtin_offsetof(CPetMenu,m_bOpenPartial)==104?1:-1];
    typedef char check_m_bFullyClosed[__builtin_offsetof(CPetMenu,m_bFullyClosed)==105?1:-1];
    typedef char check_m_pHoverObject[__builtin_offsetof(CPetMenu,m_pHoverObject)==4976?1:-1];
    typedef char check_m_pRenderWindow[__builtin_offsetof(CPetMenu,m_pRenderWindow)==37240?1:-1];
    typedef char check_m_pViewport[__builtin_offsetof(CPetMenu,m_pViewport)==37248?1:-1];
    typedef char check_m_bSpellHovered[__builtin_offsetof(CPetMenu,m_bSpellHovered)==37257?1:-1];
    typedef char check_m_HoveredSkillGuid[__builtin_offsetof(CPetMenu,m_HoveredSkillGuid)==37264?1:-1];
    typedef char check_m_bRotateLeft[__builtin_offsetof(CPetMenu,m_bRotateLeft)==37272?1:-1];
    typedef char check_m_bRotateRight[__builtin_offsetof(CPetMenu,m_bRotateRight)==37273?1:-1];
    typedef char check_m_fScreenEdge[__builtin_offsetof(CPetMenu,m_fScreenEdge)==37296?1:-1];
    typedef char check_m_fPanelX[__builtin_offsetof(CPetMenu,m_fPanelX)==37300?1:-1];
    typedef char check_m_pSoundBank[__builtin_offsetof(CPetMenu,m_pSoundBank)==37304?1:-1];
    typedef char check_m_TabNotifications[__builtin_offsetof(CPetMenu,m_TabNotifications)==37368?1:-1];
    typedef char check_m_fTabPhase[__builtin_offsetof(CPetMenu,m_fTabPhase)==37372?1:-1];
    typedef char check_size[sizeof(CPetMenu)==0x9620?1:-1];
    typedef char check_skill_window[__builtin_offsetof(CSkillTooltip,m_pWindow)==0x30?1:-1];
    typedef char check_skill_size[sizeof(CSkillTooltip)==0x178?1:-1];
    using namespace pet_update;
    float phase=m_fTabPhase+elapsed;
    m_fTabPhase=phase;
    if(phase>=1.0f) {
        do { phase-=1.0f; } while(phase>=1.0f);
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
    if(m_bOpenPartial && m_pCharacter && (actor(m_pCharacter).category==41 || actor(m_pCharacter).category==42))setOpen(false);
    int width=m_pDynamicPropertyFile->GetInt(KSETTINGS_RES_WIDTH);
    int height=m_pDynamicPropertyFile->GetInt(KSETTINGS_RES_HEIGHT);
    if(m_bRotateLeft) {
        Ogre::Matrix4 orientation=actor(m_pCharacter).model->getOrientation();
        Ogre::Matrix4 rotation;MATH::matrixRotationY(rotation,elapsed*-1.7453292608261108f);
        orientation=orientation*rotation;
        actor(m_pCharacter).model->setOrientation(orientation,false);
    } else if(m_bRotateRight) {
        Ogre::Matrix4 orientation=actor(m_pCharacter).model->getOrientation();
        Ogre::Matrix4 rotation;MATH::matrixRotationY(rotation,elapsed*1.7453292608261108f);
        orientation=orientation*rotation;
        actor(m_pCharacter).model->setOrientation(orientation,false);
    }
    if(!m_bOpenPartial) {
        m_pHoverObject=0;
        m_pSocketedIconParent->setVisible(false);
        m_pSocketOverlay->setVisible(false);
        if(!m_bOpenPartial && m_bFullyClosed) {
            if(m_pSkillTooltip && m_pSkillTooltip->m_pWindow->getParent())
                m_pSkillTooltip->m_pWindow->getParent()->removeChildWindow(m_pSkillTooltip->m_pWindow);
            return;
        }
    }
    if(m_pCharacter) {
        static std::wstring g_XP;
        if(g_XP.empty())g_XP=CStringTranslate::getSinglton()->getTranslateString(L"XP");
        changed(m_pLevel,STRINGS::GetValueAsString(actor(m_pCharacter).level));
        changed(m_pCharacterName,STRINGS::StringConvertToUTF8(std::wstring(actor(m_pCharacter).name.c_str())));
        int level=int(actor(m_pCharacter).level);
        Ogre::UTFString gate(STRINGS::GetValueAsString(CMasterResourceManager::getSingleton()->experienceGate(level)));
        Ogre::UTFString slash("/");
        Ogre::UTFString experience(STRINGS::GetValueAsString(actor(m_pCharacter).experience));
        Ogre::UTFString colon(":");
        Ogre::UTFString label(g_XP);
        std::string xp=(label+colon+experience+slash+gate).asUTF8();
        changed(m_pXP,xp);
        int base=m_pCharacter->maximumDamageForDisplay(true,false,true);
        int high=m_pCharacter->maximumDamageForDisplay(true,false,false);
        std::string maximum=STRINGS::GetValueAsString(high);
        std::string minimum=STRINGS::GetValueAsString(m_pCharacter->minimumDamageForDisplay(true,false,false));
        if(changed(m_pMeleeDamage,minimum+"-"+maximum))textColour(m_pMeleeDamage,high,base);
        base=m_pCharacter->maximumDamageForDisplay(false,false,true);
        high=m_pCharacter->maximumDamageForDisplay(false,false,false);
        maximum=STRINGS::GetValueAsString(high);
        minimum=STRINGS::GetValueAsString(m_pCharacter->minimumDamageForDisplay(false,false,false));
        if(changed(m_pRangedDamage,minimum+"-"+maximum))textColour(m_pRangedDamage,high,base);
        int low=m_pCharacter->minimumDamageForDisplay(false,true,false);
        int otherLow=m_pCharacter->minimumDamageForDisplay(true,true,false);
        if(!low)low=otherLow;else if(otherLow && otherLow<low)low=otherLow;
        base=m_pCharacter->maximumDamageForDisplay(false,true,true);
        high=m_pCharacter->maximumDamageForDisplay(false,true,false);
        int otherHigh=m_pCharacter->maximumDamageForDisplay(true,true,false);
        if(otherHigh>=high)high=otherHigh;
        maximum=STRINGS::GetValueAsString(high);minimum=STRINGS::GetValueAsString(low);
        if(changed(m_pMagicDamage,minimum+"-"+maximum))textColour(m_pMagicDamage,high,base);
        base=m_pCharacter->baseAC();int armor=m_pCharacter->AC();
        maximum=STRINGS::GetValueAsString(armor);minimum=STRINGS::GetValueAsString(m_pCharacter->minimumAC());
        if(changed(m_pDefense,minimum+"-"+maximum))textColour(m_pDefense,armor,base);
        static CEGUI::String g_MP;
        if(g_MP.empty())g_MP=STRINGS::StringConvertToUTF8(CStringTranslate::getSinglton()->getTranslateString(L"MP"));
        std::string manaMaximum=STRINGS::GetValueAsString(m_pCharacter->maxMana());
        CEGUI::String mana=g_MP+": "+manaMaximum;
        if(changed(m_pMana,mana)) {
            int value=m_pCharacter->maxMana();int original=actor(m_pCharacter).baseMana;
            if(value<original)m_pMana->setProperty("TextColour","FFFF0000");
            else { value=m_pCharacter->maxMana();original=actor(m_pCharacter).baseMana;
                m_pMana->setProperty("TextColour",value>original?"FFc0c0ff":"FFFFFFFF"); }
        }
        static CEGUI::String g_HP;
        if(g_HP.empty())g_HP=STRINGS::StringConvertToUTF8(CStringTranslate::getSinglton()->getTranslateString(L"HP"));
        std::string healthMaximum=STRINGS::GetValueAsString(m_pCharacter->maxHP());
        CEGUI::String health=g_HP+": "+healthMaximum;
        if(changed(m_pHP,health)) {
            int value=m_pCharacter->maxHP();int original=actor(m_pCharacter).baseHealth;
            if(value<original)m_pHP->setProperty("TextColour","FFFF0000");
            else { value=m_pCharacter->maxHP();original=actor(m_pCharacter).baseHealth;
                m_pHP->setProperty("TextColour",value>original?"FFc0c0ff":"FFFFFFFF"); }
        }
    }
    m_pPetModel->updateAnimation(elapsed,false);
    m_pPetModel->getEntity()->_updateAnimation();
    Ogre::Bone* top=m_pPetModel->m_pSkeleton->getBone("tag_toppet");
    Ogre::Vector3 position=m_pPetModel->getPosition(false);
    const Ogre::Vector3& tag=top->_getDerivedPosition();
    float sumY=tag.y+position.y;
    float scaledX=m_pGameUI->scaledY(tag.x+position.x);
    float halfWidth=float(width)*0.5f;
    float panelY=-(float(height)*-0.5f+m_pGameUI->scaledY(sumY));
    m_fPanelX=scaledX+halfWidth;
    m_pPanel->setPosition(CEGUI::UVector2(CEGUI::UDim(0,m_fPanelX),CEGUI::UDim(0,panelY)));
    Ogre::Bone* bottom=m_pPetModel->m_pSkeleton->getBone("tag_bottompet");
    position=m_pPetModel->getPosition(false);
    float bottomX=bottom->_getDerivedPosition().x+position.x;
    float scaledBottom=m_pGameUI->scaledY(bottomX);
    m_pForeground48->setPosition(CEGUI::UVector2(CEGUI::UDim(0,scaledBottom+halfWidth),CEGUI::UDim(0,panelY)));
    Ogre::Bone* right=m_pPetModel->m_pSkeleton->getBone("tag_bottompetright");
    position=m_pPetModel->getPosition(false);
    float rightX=right->_getDerivedPosition().x+position.x;
    float scaledRight=m_pGameUI->scaledY(rightX);
    float edge=(scaledRight+halfWidth)-m_pGameUI->scaledY(50.0f);
    m_fScreenEdge=edge>0.0f?edge:0.0f;
    float panelX=m_fPanelX;
    float left=(panelX+m_pGameUI->scaledY(97.0f))/float(width);
    float span=m_pGameUI->scaledY(166.0f)/float(width);
    if(left<0.0f) { span=maxSecond(span+left,1.0f/float(width)+0.0f);left=0.0f; }
    if(m_pViewport) {
        float h=m_pGameUI->scaledY(135.0f);
        float y=m_pGameUI->scaledY(169.0f);
        m_pViewport->setDimensions(left,y/float(height),span,h/float(height));
        m_pWardrobeCamera->setAspectRatio(float(m_pViewport->getActualWidth())/float(m_pViewport->getActualHeight()));
    }
    if(!m_bOpenPartial && !m_bFullyClosed) {
        if(!m_pPetModel->animationPlaying("CLOSE") && !m_pPetModel->animationQueued("CLOSE")) {
            m_pPetModel->setVisible(false);
            m_bFullyClosed=true;
            m_pRenderWindow->removeViewport(4);
            m_pParent->removeChildWindow(m_pBackground);
            m_pViewport=0;
        }
    }
    if(m_bSpellHovered && m_pCharacter) {
        CSkillManager* manager=actor(m_pCharacter).skills;
        long long guid=m_HoveredSkillGuid;
        if(!manager)return;
        CSkill* skill=manager->getSkillByGuid(guid);
        if(!skill)return;
        PointerFields& mouse=*reinterpret_cast<PointerFields*>(m_pGameUI);
        m_pSkillTooltip->showTooltip(m_pCharacter,skill,float(mouse.x),float(mouse.y));
    } else {
        CEGUI::Window* window=m_pSkillTooltip->m_pWindow;
        if(window->getParent())window->getParent()->removeChildWindow(window);
    }
}

#include "Inventory.h"
#include "Equipment.h"
#include "Skill.h"
#include "StringTranslate.h"
#include "StringUtilities.h"
void CPetMenu::updateLayout()
{
    typedef char current_tab_offset[__builtin_offsetof(CPetMenu,m_iCurrentTab)==0x6c?1:-1];
    if (!m_pCharacter || !m_bOpenPartial || !m_pCharacter->m_pInventory)
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
            m_pSocketedSizeWindows[i]->setTooltipText(CEGUI::String(m_DefaultSlotTooltips[i].c_str()));
            m_pSocketedSizeWindows[i]->setProperty("Image", m_DefaultSlotImages[i]);
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
                    if (!m_pSocketedIconParent->isChild(gemIcon))
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
            icon->setPosition(CEGUI::UVector2(CEGUI::UDim(0,0),CEGUI::UDim(0,0)));
            CEGUI::UVector2 size = m_pSocketedSizeWindows[i]->getSize();
            const float width = size.d_x.asAbsolute(0.0f);
            const float height = width * 1.5f;
            size.d_x = CEGUI::UDim(0,width);
            size.d_y = CEGUI::UDim(0,height);
            icon->setSize(size);
            icon->moveToFront();
            icon->update(0.001f);
        }
        m_pSocketedSizeWindows[i]->setTooltipText(CEGUI::String(reinterpret_cast<const unsigned char*>("")));
    }
    for(unsigned i=0;i<2;++i) {
        if(!m_pSpellWindows[i])continue;
        static std::string g_RemoveASpell;
        if(g_RemoveASpell.empty())g_RemoveASpell=STRINGS::StringConvertToNarrow(CStringTranslate::getSinglton()->getTranslateString(L"Hold [CTRL] and left-click to").c_str());
        static std::string g_RemoveASpell2;
        if(g_RemoveASpell2.empty())g_RemoveASpell2=STRINGS::StringConvertToNarrow(CStringTranslate::getSinglton()->getTranslateString(L"un-learn this spell").c_str());
        static std::string g_DragASpell;
        if(g_DragASpell.empty())g_DragASpell=STRINGS::StringConvertToNarrow(CStringTranslate::getSinglton()->getTranslateString(L"Drag a spell here to learn it").c_str());
        CSkill* spell=m_pCharacter->getKnownSpell(i);
        if(spell&&!spell->getSkillIcon().empty()) {
            m_pSpellWindows[i]->setProperty("Image",CEGUI::PropertyHelper::imageToString(m_pGameUI->getImageFromImageSet(reinterpret_cast<const unsigned char*>(STRINGS::StringConvertToNarrow(spell->getSkillIcon().c_str()).c_str()))));
            m_SpellGuids[i]=spell->m_Guid;
            m_pSpellWindows[i]->setUserData(&m_SpellGuids[i]);
            m_pSpellWindows[i]->setTooltipText(CEGUI::String(reinterpret_cast<const unsigned char*>((g_RemoveASpell+" "+g_RemoveASpell2).c_str())));
        } else {
            m_pSpellWindows[i]->setProperty("Image","");
            m_pSpellWindows[i]->setUserData(&m_NoSpell);
            m_pSpellWindows[i]->setTooltipText(CEGUI::String(reinterpret_cast<const unsigned char*>(g_DragASpell.c_str())));
        }
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
        if (ref->m_iSlot > 18) {
            int pane=inventory->getItemPane(equipmentRefs[i]->m_iSlot);
            if(pane==m_iCurrentTab)
                setSlotIcon(item,equipmentRefs[i]->m_iSlot,equipmentRefs[i]->m_iSlot);
        }
    }
    m_pBackground->moveToBack();
    m_pForeground48->moveToFront();
    m_pPanel->moveToFront();
    m_pSocketedIconParent->moveToFront();
    m_pSocketOverlay->moveToFront();
}

#include "PetMenu.h"
#include "Equipment.h"
#include "Character.h"
#include "StringUtilities.h"
#include <CEGUI.h>

void CPetMenu::setSlotIcon(CEquipment* pItem, int iSlotIndex, int iDataIndex)
{


    unsigned int uiIconY = (unsigned int)(m_pSocketedSizeWindows[iSlotIndex]->getPosition().d_y.asAbsolute(0.0f));
    unsigned int uiIconX = (unsigned int)(m_pSocketedSizeWindows[iSlotIndex]->getPosition().d_x.asAbsolute(0.0f));

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

    if (!pItem->canEquip(m_pCharacter->m_pMaster, false))
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

#include "Character.h"
#include "Inventory.h"
namespace pet_controls {
struct UIFocus {char prefix[0xb8];CBaseUnit* unit;};
struct HoverState {char prefix[0x198];bool flag198;};
inline __attribute__((always_inline)) CBaseUnit* focused(CGameUI* ui){return reinterpret_cast<UIFocus*>(ui)->unit;}
}
void CPetMenu::equipmentDropped(CEquipment*) {updateLayout();}
void CPetMenu::equipmentEquipped(CEquipment*) {updateLayout();}
void CPetMenu::equipmentUsed(CEquipment*) {updateLayout();}
// The original callback has no side effects.
void CPetMenu::inventoryDestroyed() {}
bool CPetMenu::handle_ItemClick(const CEGUI::EventArgs& event) {
 const CEGUI::MouseEventArgs& mouse=static_cast<const CEGUI::MouseEventArgs&>(event);
 if(mouse.window) {
  int slot=*static_cast<int*>(mouse.window->getUserData());
  if(mouse.button==CEGUI::LeftButton)m_ClickedSlot=slot;
  else if(mouse.button==CEGUI::RightButton)m_RightClickedSlot=slot;
 }
 return true;
}
bool CPetMenu::handle_CloseButton(const CEGUI::EventArgs& event) {
 if(static_cast<const CEGUI::MouseEventArgs&>(event).button==CEGUI::LeftButton)m_Data6a[0]=1;
 return true;
}
bool CPetMenu::handle_RotateLeft(const CEGUI::EventArgs&) {m_bRotateLeft=true;return true;}
bool CPetMenu::handle_EndRotateLeft(const CEGUI::EventArgs&) {m_bRotateLeft=false;return true;}
bool CPetMenu::handle_RotateRight(const CEGUI::EventArgs&) {m_bRotateRight=true;return true;}
bool CPetMenu::handle_EndRotateRight(const CEGUI::EventArgs&) {m_bRotateRight=false;return true;}
bool CPetMenu::handle_MouseThrough(const CEGUI::EventArgs&) {m_Data9188=0;m_bSpellHovered=false;return true;}
bool CPetMenu::handle_onClick(const CEGUI::EventArgs& event) {
 const CEGUI::MouseEventArgs& mouse=static_cast<const CEGUI::MouseEventArgs&>(event);
 CEGUI::Window* w=mouse.window;
 if(mouse.button==CEGUI::LeftButton&&w)return onClick(*static_cast<ELayoutFunction*>(w->getUserData()));
 return true;
}
void CPetMenu::setTab(int tab) {onClick(static_cast<ELayoutFunction>(static_cast<unsigned>(tab)+14u));}
bool CPetMenu::handle_SpellMouseOver(const CEGUI::EventArgs& event) {
 CEGUI::Window* w=static_cast<const CEGUI::WindowEventArgs&>(event).window;
 if(w){long long guid=*static_cast<long long*>(w->getUserData());m_bSpellHovered=true;m_HoveredSkillGuid=guid;}
 return true;
}
bool CPetMenu::handle_SpellMouseOut(const CEGUI::EventArgs&) {return true;}
void CPetMenu::setOwner(CCharacter* owner) {
 bool changed=owner!=m_pCharacter;
 if(changed)inventoryDestroyed();
 if(m_pCharacter&&m_pCharacter->m_pInventory)m_pCharacter->m_pInventory->removeListener(this);
 m_pCharacter=owner;
 if(owner&&owner->m_pInventory)owner->m_pInventory->addListener(this);
 if(changed)updateLayout();
 m_TabNotifications[0]=false;m_TabNotifications[1]=false;m_TabNotifications[2]=false;
}
void CPetMenu::checkForUpdate(CEquipment* item) {
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
void CPetMenu::equipmentUnequipped(CEquipment* item) {checkForUpdate(item);updateLayout();}
void CPetMenu::equipmentPickedUp(CEquipment* item) {checkForUpdate(item);updateLayout();}
bool CPetMenu::handle_MouseOut(const CEGUI::EventArgs& event) {
 CEGUI::Window* w=static_cast<const CEGUI::WindowEventArgs&>(event).window;
 CCharacter* owner=m_pCharacter;
 if(w&&owner) {
  CEquipment* item=owner->m_pInventory->getEquipmentInSlot(*static_cast<unsigned*>(w->getUserData()));
  if(item==m_pHoverObject) {
   m_pHoverObject=0;
   CBaseUnit* focused=pet_controls::focused(m_pGameUI);
   if(!focused || !focused->ISA(static_cast<UNITTYPES::EUNITTYPES>(120))) {
    m_pSocketedIconParent->setVisible(false);m_pSocketOverlay->setVisible(false);
   }
  }
 }
 return true;
}
bool CPetMenu::processInput(void*,float,bool active) {
 bool result=true;
 if(active) {
  if(m_Data6a[0]){setOpen(false);m_Data6a[0]=0;result=false;}
  CBaseUnit* focused=pet_controls::focused(m_pGameUI);
  if(focused && focused->ISA(static_cast<UNITTYPES::EUNITTYPES>(120))) {
   m_pSocketOverlay->setVisible(true);m_pSocketOverlay->moveToFront();
   m_pSocketedIconParent->setVisible(true);m_pSocketedIconParent->moveToFront();
  }else {
   if(m_pHoverObject&&reinterpret_cast<pet_controls::HoverState*>(m_pHoverObject)->flag198)m_pHoverObject=0;
   if(!m_pHoverObject){m_pSocketedIconParent->setVisible(false);m_pSocketOverlay->setVisible(false);}
  }
  if(!m_Data9188) {
   if(m_pPanel->isChild(m_pSlotGlow))m_pPanel->removeChildWindow(m_pSlotGlow);
   else if(m_pForeground48->isChild(m_pSlotGlow))m_pForeground48->removeChildWindow(m_pSlotGlow);
  }
  m_ClickedSlot=-1;m_RightClickedSlot=-1;
 }else {
  m_pHoverObject=0;m_pSocketedIconParent->setVisible(false);m_pSocketOverlay->setVisible(false);
  if(m_pPanel->isChild(m_pSlotGlow))m_pPanel->removeChildWindow(m_pSlotGlow);
  else if(m_pForeground48->isChild(m_pSlotGlow))m_pForeground48->removeChildWindow(m_pSlotGlow);
 }
 return result;
}
bool CPetMenu::onClick(ELayoutFunction action) {
 if(m_bOpenPartial) {
  switch(action) {
  case static_cast<ELayoutFunction>(14):
   static_cast<CEGUI::RadioButton*>(m_pBackpackTab)->setSelected(true);
   static_cast<CEGUI::RadioButton*>(m_pSpellsTab)->setSelected(false);
   static_cast<CEGUI::RadioButton*>(m_pFishTab)->setSelected(false);
   m_pBackpackSlots->setVisible(true);
   m_pSpellsSlots->setVisible(false);
   m_pFishSlots->setVisible(false);
   m_iCurrentTab=0;m_TabNotifications[0]=false;
   m_pBackpackTab->setProperty("UnselectedImage",m_TabUnselectedImages[0]);updateLayout();break;
  case static_cast<ELayoutFunction>(15):
   static_cast<CEGUI::RadioButton*>(m_pBackpackTab)->setSelected(false);
   static_cast<CEGUI::RadioButton*>(m_pSpellsTab)->setSelected(true);
   static_cast<CEGUI::RadioButton*>(m_pFishTab)->setSelected(false);
   m_pBackpackSlots->setVisible(false);
   m_pSpellsSlots->setVisible(true);
   m_pFishSlots->setVisible(false);
   m_iCurrentTab=1;m_TabNotifications[1]=false;
   m_pSpellsTab->setProperty("UnselectedImage",m_TabUnselectedImages[1]);updateLayout();break;
  case static_cast<ELayoutFunction>(16):
   static_cast<CEGUI::RadioButton*>(m_pBackpackTab)->setSelected(false);
   static_cast<CEGUI::RadioButton*>(m_pSpellsTab)->setSelected(false);
   static_cast<CEGUI::RadioButton*>(m_pFishTab)->setSelected(true);
   m_pBackpackSlots->setVisible(false);
   m_pSpellsSlots->setVisible(false);
   m_pFishSlots->setVisible(true);
   m_iCurrentTab=2;m_TabNotifications[2]=false;
   m_pFishTab->setProperty("UnselectedImage",m_TabUnselectedImages[2]);updateLayout();break;
  default:break;
  }
 }
 return true;
}
