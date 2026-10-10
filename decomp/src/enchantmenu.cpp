#include "EmptyStrings.h"
#include "EmptyStrings.h"
#include "EnchantMenu.h"
#include "Equipment.h"
#include "StringUtilities.h"
#include <CEGUI.h>
void CEnchantMenu::setSlotIcon(CEquipment* pItem, int iSlotIndex)
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
        m_pSocketedSizeWindows[iSlotIndex]->addChildWindow(pIcon);
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

#include "EmptyStrings.h"
#include "GameGlobals.h"
#include "StringTranslate.h"
#include "EnchantMenu.h"
#include "Inventory.h"
#include "Equipment.h"
#include "StringUtilities.h"
#include <CEGUI.h>

// Original float overload used by this TU; keep unrelated partial-header users unchanged.
namespace STRINGS { std::wstring GetValueAsWString(float); }

namespace enchant_detail {
inline __attribute__((always_inline)) void setCachedText(CEGUI::Window* window, const std::wstring& text)
{
    window->setText(CEGUI::String(reinterpret_cast<const unsigned char*>(STRINGS::StringConvertToUTF8(std::wstring(text.c_str())).c_str())));
}
inline __attribute__((always_inline)) void setBuiltText(CEGUI::Window* window, const std::wstring& text)
{
    window->setText(CEGUI::String(reinterpret_cast<const unsigned char*>(STRINGS::StringConvertToUTF8(text).c_str())));
}
}
#define ENCHANT_TRANSLATION(NAME, TEXT) static std::wstring NAME; if (NAME.empty()) NAME = CStringTranslate::getSinglton()->getTranslateString(TEXT)

__attribute__((flatten)) void CEnchantMenu::updateLayout()
{
    if (!m_bOpen || !m_pCharacter || !m_pCharacter->m_pInventory)
        return;
    CInventory* inventory = m_pCharacter->m_pInventory;
    while (m_pSocketedIconParent->getChildCount())
        m_pSocketedIconParent->removeChildWindow(m_pSocketedIconParent->getChildAtIdx(0));
    std::wstring builtText(EMPTY_WSTRING);
    for (unsigned i = 0; i < 1; ++i)
    {
        if (!m_pSocketedSizeWindows[i]) continue;
        if (m_pSocketedSizeWindows[i]->getChildCount())
            m_pSocketedSizeWindows[i]->removeChildWindow(m_pSocketedSizeWindows[i]->getChildAtIdx(0));
        CEquipmentRef* ref = reinterpret_cast<CEquipmentRef*>(inventory->getEquipmentRefInSlot(m_aiSlotData[i]));
        if (!ref)
        {
            // The inventory query is a call boundary; the slot pointer is re-read.
            if (!m_pSocketedSizeWindows[i]) continue;
            ENCHANT_TRANSLATION(g_PlaceHereToEnchant, L"Place item here to enchant");
            ENCHANT_TRANSLATION(g_PlaceItemHereToDestroySocketable, L"Place item here to recover gems");
            ENCHANT_TRANSLATION(g_PlaceItemHereToDestroyGems, L"Place item here to destroy gems");
            ENCHANT_TRANSLATION(g_PlaceItemHereToPassDown, L"Place item here to pass down");
            switch (m_iMode)
            {
                case 0x15: case 0x16: enchant_detail::setCachedText(m_pDescription,g_PlaceHereToEnchant); break;
                case 0x19: enchant_detail::setCachedText(m_pDescription,g_PlaceItemHereToDestroyGems); break;
                case 0x1a: enchant_detail::setCachedText(m_pDescription,g_PlaceItemHereToDestroySocketable); break;
                case 0x1b: enchant_detail::setCachedText(m_pDescription,g_PlaceItemHereToPassDown); break;
            }
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
        const int mode = m_iMode;
        // These modes own distinct same-named local statics in the original.
        if (mode == 0x15)
        {
            if (!(item->ISA(static_cast<UNITTYPES::EUNITTYPES>(8)) ||
                  item->ISA(static_cast<UNITTYPES::EUNITTYPES>(13)) ||
                  item->ISA(static_cast<UNITTYPES::EUNITTYPES>(17)) ||
                  item->ISA(static_cast<UNITTYPES::EUNITTYPES>(24))))
            {
                ENCHANT_TRANSLATION(g_CannotEnchant,L"Cannot enchant item");
                enchant_detail::setCachedText(m_pDescription,g_CannotEnchant);
            }
            else
            {
                const int count = item->m_iUnknown344;
                const int limit = CGameGlobals::getSingleton()->m_iEnchanterMaxEnchantments;
                if (count >= limit)
                {
                    ENCHANT_TRANSLATION(g_MaxEnchant,L"Maximum enchantments reached");
                    enchant_detail::setCachedText(m_pDescription,g_MaxEnchant);
                }
                else
                {
                    ENCHANT_TRANSLATION(g_EnchantPrice,L"Enchant price");
                    ENCHANT_TRANSLATION(g_Disenchant,L"Disenchant chance");
                    const unsigned int currentCount = (unsigned int)item->m_iUnknown344;
                    const float accumulated = (float)currentCount * CGameGlobals::getSingleton()->m_fEnchanterDisenchantPerEnchant;
                    float chance = accumulated + CGameGlobals::getSingleton()->m_fEnchanterDisenchantBase;
                    const float maximum = CGameGlobals::getSingleton()->m_fEnchanterDisenchantMax;
                    // MINSS keeps the computed chance for unordered/equal operands.
                    chance = maximum < chance ? maximum : chance;
                    builtText = g_EnchantPrice + L":" + STRINGS::GetValueAsWString(item->enchantPrice()) + L"\n" + g_Disenchant + L":" + STRINGS::GetValueAsWString(chance) + L"%";
                    enchant_detail::setBuiltText(m_pDescription,builtText);
                }
            }
        }
        else if (mode == 0x16)
        {
            if (!(item->ISA(static_cast<UNITTYPES::EUNITTYPES>(8)) ||
                  item->ISA(static_cast<UNITTYPES::EUNITTYPES>(13)) ||
                  item->ISA(static_cast<UNITTYPES::EUNITTYPES>(17)) ||
                  item->ISA(static_cast<UNITTYPES::EUNITTYPES>(24))))
            {
                ENCHANT_TRANSLATION(g_CannotEnchant,L"Cannot enchant item");
                enchant_detail::setCachedText(m_pDescription,g_CannotEnchant);
            }
            else
            {
                const int count = item->m_iUnknown344;
                const int limit = CGameGlobals::getSingleton()->m_iShrineMaxEnchantments;
                if (count >= limit)
                {
                    ENCHANT_TRANSLATION(g_MaxEnchant,L"Maximum enchantments reached");
                    enchant_detail::setCachedText(m_pDescription,g_MaxEnchant);
                }
                else
                {
                    ENCHANT_TRANSLATION(g_PressEnchant,L"Press 'Enchant' to receive a random effect");
                    ENCHANT_TRANSLATION(g_Disenchant,L"Disenchant chance");
                    const unsigned int currentCount = (unsigned int)item->m_iUnknown344;
                    const float accumulated = (float)currentCount * CGameGlobals::getSingleton()->m_fShrineDisenchantPerEnchant;
                    float chance = accumulated + CGameGlobals::getSingleton()->m_fShrineDisenchantBase;
                    const float maximum = CGameGlobals::getSingleton()->m_fShrineDisenchantMax;
                    // MINSS keeps the computed chance for unordered/equal operands.
                    chance = maximum < chance ? maximum : chance;
                    builtText = g_PressEnchant + L"\n" + g_Disenchant + L":" + STRINGS::GetValueAsWString(chance) + L"%";
                    enchant_detail::setBuiltText(m_pDescription,builtText);
                }
            }
        }
        else if (mode == 0x19)
        {
            if (item->m_iSocketCount == 0 || item->m_SocketedEquipment.size() == 0)
            {
                ENCHANT_TRANSLATION(g_NoGem,L"No gems to destroy");
                enchant_detail::setCachedText(m_pDescription,g_NoGem);
            }
            else
            {
                ENCHANT_TRANSLATION(g_PressDestroyGem,L"Press 'Destroy' to destroy gems");
                enchant_detail::setCachedText(m_pDescription,g_PressDestroyGem);
            }
        }
        else if (mode == 0x1a)
        {
            if (item->m_iSocketCount == 0 || item->m_SocketedEquipment.size() == 0)
            {
                ENCHANT_TRANSLATION(g_NoGemsToRecover,L"No gems to recover");
                enchant_detail::setCachedText(m_pDescription,g_NoGemsToRecover);
            }
            else
            {
                ENCHANT_TRANSLATION(g_PressRecover,L"Press 'Recover' to recover gems");
                enchant_detail::setCachedText(m_pDescription,g_PressRecover);
            }
        }
        else if (mode == 0x1b)
        {
            if (!(item->ISA(static_cast<UNITTYPES::EUNITTYPES>(8)) ||
                  item->ISA(static_cast<UNITTYPES::EUNITTYPES>(13)) ||
                  item->ISA(static_cast<UNITTYPES::EUNITTYPES>(39))))
            {
                ENCHANT_TRANSLATION(g_NoHeirloom,L"No item to pass down");
                enchant_detail::setCachedText(m_pDescription,g_NoHeirloom);
            }
            else
            {
                ENCHANT_TRANSLATION(g_PressRetire,L"Press 'Retire' to pass down Heirloom");
                enchant_detail::setCachedText(m_pDescription,g_PressRetire);
            }
        }
    }
    m_pBackground->moveToBack();
    m_pPanel->moveToFront();
    m_pForeground->moveToFront();
    m_pSocketedIconParent->moveToFront();
}

#undef ENCHANT_TRANSLATION

#include "EmptyStrings.h"
#include "EnchantMenu.h"
#include "Equipment.h"
#include "Inventory.h"
#include "GameClient.h"
#include "GameGlobals.h"
#include "SoundBank.h"
#include "EffectManager.h"
#include "Level.h"
#include "StringTranslate.h"
#include "StringUtilities.h"
#include "Utilities.h"
#include "SteamStats.h"
#include "Achievements.h"
#include "Achievement.h"
#include "SafePointer.h"

namespace enchant_interaction {
// Views of established fields beyond the currently recovered class prefixes.
// They are never constructed; in particular, no extra string lifetime is added.
struct ActorFields {
 char pad0[0x298]; CSoundBank* speech;
 char pad2a0[0x4c0-0x2a0]; std::wstring name;
 char pad4c8[0xa10-0x4c8]; int retirements; bool retired;
};
struct UIFields { char pad0[0x1920]; CGameClient* client; };
struct ClientFields {
 char pad0[0x1c8]; TSafePointer<CRunicCore> click1,click2,click3,click4;
 char pad208[0x3900-0x208]; CEquipment* heirloom; int retirements;
};
typedef char offset_ActorFields_speech[__builtin_offsetof(ActorFields,speech)==664?1:-1];
typedef char offset_ActorFields_name[__builtin_offsetof(ActorFields,name)==1216?1:-1];
typedef char offset_ActorFields_retirements[__builtin_offsetof(ActorFields,retirements)==2576?1:-1];
typedef char offset_ActorFields_retired[__builtin_offsetof(ActorFields,retired)==2580?1:-1];
typedef char offset_UIFields_client[__builtin_offsetof(UIFields,client)==6432?1:-1];
typedef char offset_ClientFields_click1[__builtin_offsetof(ClientFields,click1)==456?1:-1];
typedef char offset_ClientFields_click2[__builtin_offsetof(ClientFields,click2)==472?1:-1];
typedef char offset_ClientFields_click3[__builtin_offsetof(ClientFields,click3)==488?1:-1];
typedef char offset_ClientFields_click4[__builtin_offsetof(ClientFields,click4)==504?1:-1];
typedef char offset_ClientFields_heirloom[__builtin_offsetof(ClientFields,heirloom)==14592?1:-1];
typedef char offset_ClientFields_retirements[__builtin_offsetof(ClientFields,retirements)==14600?1:-1];
typedef char offset_CEnchantMenu_m_pOwnerItem[__builtin_offsetof(CEnchantMenu,m_pOwnerItem)==104?1:-1];
typedef char offset_CEnchantMenu_m_bInteractionComplete[__builtin_offsetof(CEnchantMenu,m_bInteractionComplete)==114?1:-1];
typedef char offset_CEnchantMenu_m_bRetirementComplete[__builtin_offsetof(CEnchantMenu,m_bRetirementComplete)==115?1:-1];
typedef char offset_CEnchantMenu_m_pSoundBank[__builtin_offsetof(CEnchantMenu,m_pSoundBank)==184?1:-1];
inline __attribute__((always_inline)) ActorFields& actor(CCharacter* p) { return *reinterpret_cast<ActorFields*>(p); }
inline __attribute__((always_inline)) CGameClient* client(CGameUI* p) { return reinterpret_cast<UIFields*>(p)->client; }
inline __attribute__((always_inline)) void play(CEnchantMenu* m,int sound) { m->m_pSoundBank->playSample(sound,m->m_pCharacter->getSceneNode(),0.0f,0.0f,false); }
inline __attribute__((always_inline)) void speak(CEnchantMenu* m,int sound) { if(actor(m->m_pCharacter).speech) actor(m->m_pCharacter).speech->queueGlobalSample(sound,1.0f,1.0f); }
inline __attribute__((always_inline)) void returnItem(CEnchantMenu* m,CInventory* inventory,CEquipment* item) {
 if(!inventory->pickupEquipment(item,true)) {
  Ogre::Vector3 position=m->m_pCharacter->getPosition(true);
  m->m_pCharacter->getLevel()->addItem(item,position,true);
  item->drop();
 }
}
inline __attribute__((always_inline)) std::wstring normalize(std::wstring text) { return STRINGS::replaceWString(text,L"\\n",L"\n"); }
inline __attribute__((always_inline)) void complete(CEnchantMenu* m,const std::wstring& title,const std::wstring& message) {
 m->m_bInteractionComplete=true;
 m->m_pGameUI->getCharacter()->setTarget(NULL);
 client(m->m_pGameUI)->clearMouseClickUnits();
 m->m_pGameUI->openModalDialog(title,message,false);
 m->m_pGameUI->clearMenuMouseOvers();
}
}
#define INTERACTION_TRANSLATION(NAME,TEXT) static std::wstring NAME; if(NAME.empty()) NAME=CStringTranslate::getSinglton()->getTranslateString(TEXT)

__attribute__((flatten))
void CEnchantMenu::performInteraction()
{
 using namespace enchant_interaction;
 INTERACTION_TRANSLATION(g_AncientRites,L"The enchanter performs the ancient rites on the");
 INTERACTION_TRANSLATION(g_NothingHappens,L"but nothing happens");
 INTERACTION_TRANSLATION(g_AddedSockets,L"and creates new sockets");
 INTERACTION_TRANSLATION(g_AddedEnchantments,L"and adds new enchantments");
 INTERACTION_TRANSLATION(g_RemovedEnchantments,L"and accidentally removes all enchantments");
 INTERACTION_TRANSLATION(g_YouPlunge,L"You plunge the");
 INTERACTION_TRANSLATION(g_IntoTheLight,L"into the light");
 INTERACTION_TRANSLATION(g_TheGemsWithin,L"The gems within the");
 INTERACTION_TRANSLATION(g_AreDestroyed,L"are destroyed");
 INTERACTION_TRANSLATION(g_GemsRecovered,L"The item is destroyed, recovering the gems within");
 INTERACTION_TRANSLATION(g_Sockets,L"Sockets");
 INTERACTION_TRANSLATION(g_Enchant,L"Enchant");
 int randomCount=UTILITIES::randomIntegerBetweenVolatile(0,1);
 std::wstring message(EMPTY_WSTRING);
 CEquipment* equipment=NULL;
 bool disenchanted=false;
 switch(m_iMode) {
 case 0x15: case 0x16: {
  equipment=reinterpret_cast<CEquipment*>(m_pCharacter->m_pInventory->getEquipmentInSlot(14));
  if(!equipment || !(equipment->ISA(static_cast<UNITTYPES::EUNITTYPES>(8)) || equipment->ISA(static_cast<UNITTYPES::EUNITTYPES>(13)) || equipment->ISA(static_cast<UNITTYPES::EUNITTYPES>(17)) || equipment->ISA(static_cast<UNITTYPES::EUNITTYPES>(24)))) { play(this,0x18); return; }
  bool shrine=m_iMode==0x16;
  const std::wstring& name=equipment->getItemName();
  message=shrine ? normalize(g_YouPlunge+L" "+name+L" "+g_IntoTheLight+L" ... "+g_NothingHappens+L"!") : normalize(g_AncientRites+L" "+name+L" ... "+g_NothingHappens+L"!");
  if(!shrine) {
   if(equipment->enchantPrice()>m_pCharacter->getGold()) { play(this,0x18); return; }
   m_pCharacter->giveGold(-equipment->enchantPrice());
   play(this,0x17);
  }
  float chance=static_cast<float>(static_cast<unsigned>(equipment->m_iUnknown344));
  chance*=shrine ? CGameGlobals::getSingleton()->m_fShrineDisenchantPerEnchant : CGameGlobals::getSingleton()->m_fEnchanterDisenchantPerEnchant;
  chance+=shrine ? CGameGlobals::getSingleton()->m_fShrineDisenchantBase : CGameGlobals::getSingleton()->m_fEnchanterDisenchantBase;
  float maximum=shrine ? CGameGlobals::getSingleton()->m_fShrineDisenchantMax : CGameGlobals::getSingleton()->m_fEnchanterDisenchantMax;
  chance=maximum<chance ? maximum : chance;
  float roll=UTILITIES::randomBetweenVolatile(0.0f,1000.0f);
  if(chance*10.0f>=roll && equipment->m_pEffectManager) {
   const std::wstring& currentName=equipment->getItemName();
   message=normalize((shrine?g_YouPlunge:g_AncientRites)+L" "+currentName+L" ... "+g_RemovedEnchantments+L"!");
   equipment->m_pEffectManager->clearOutAffixEffects();
   equipment->m_pEffectManager->clearEffects(true);
   equipment->clearDamageBonuses();
   if(shrine) { play(this,0x23); speak(this,0x40); equipment->m_iUnknown344=0; }
   else { equipment->m_iUnknown344=0; speak(this,0x40); play(this,0x23); }
   disenchanted=true;
  } else {
   int sockets=static_cast<int>(equipment->m_iSocketCount);
   bool addSocket=false;
   if(sockets<equipment->getMaxSockets()) {
    roll=UTILITIES::randomBetweenVolatile(0.0f,1000.0f);
    float socketChance=shrine ? CGameGlobals::getSingleton()->m_fShrineSocketChance : CGameGlobals::getSingleton()->m_fEnchanterSocketChance;
    addSocket=socketChance*10.0f>roll;
   }
   bool enchant=false;
   if(!addSocket) {
    roll=UTILITIES::randomBetweenVolatile(0.0f,1000.0f);
    float enchantChance=shrine ? CGameGlobals::getSingleton()->m_fShrineEnchantChance : CGameGlobals::getSingleton()->m_fEnchanterEnchantChance;
    enchant=enchantChance*10.0f>=roll;
   }
   if(addSocket || enchant) {
    const std::wstring& currentName=equipment->getItemName();
    const std::wstring& outcome=addSocket ? g_AddedSockets:g_AddedEnchantments;
    message=shrine ? normalize(g_YouPlunge+L" "+currentName+L" "+g_IntoTheLight+L" ... "+outcome+L"!") : normalize(g_AncientRites+L" "+currentName+L" ... "+outcome+L"!");
    play(this,0x24);
    if(!shrine) speak(this,0x3f);
    if(addSocket) equipment->addSockets();
    else {
     unsigned level=shrine ? m_pCharacter->m_iUnitLevel : static_cast<unsigned>(equipment->m_iUnknown274);
     equipment->addEnchant(static_cast<int>(level>3 ? level:4),randomCount+1,randomCount+2);
    }
    if(shrine) speak(this,0x3f);
    ++equipment->m_iUnknown344;
   } else {
    if(shrine) { play(this,0x23); speak(this,0x40); }
    else { speak(this,0x40); play(this,0x23); }
   }
  }
  equipment->m_bUnknown348=true;
  equipment->destroyItemText();
  m_pCharacter->m_pInventory->removeEquipment(equipment);
  returnItem(this,m_pCharacter->m_pInventory,equipment);
  complete(this,g_Enchant,message);
  if(shrine && m_pOwnerItem) m_pOwnerItem->interact(m_pCharacter);
  updateLayout();
  m_pCharacter->incrementJournalStatistic(static_cast<EJournalStatistic>(17),1);
  break;
 }
 case 0x19:
  equipment=reinterpret_cast<CEquipment*>(m_pCharacter->m_pInventory->getEquipmentInSlot(14));
  if(!equipment || !equipment->m_iSocketCount || !equipment->m_SocketedEquipment.size()) { play(this,0x18); return; }
  message=normalize(g_TheGemsWithin+L" "+equipment->getItemName()+L" "+g_AreDestroyed+L"!");
  play(this,0x24);
  equipment->m_SocketedEquipment.deleteAll();
  m_pCharacter->m_pInventory->removeEquipment(equipment);
  returnItem(this,m_pCharacter->m_pInventory,equipment);
  complete(this,g_Sockets,message);
  updateLayout();
  break;
 case 0x1a:
  equipment=reinterpret_cast<CEquipment*>(m_pCharacter->m_pInventory->getEquipmentInSlot(14));
  if(!equipment || !equipment->m_iSocketCount || !equipment->m_SocketedEquipment.size()) { play(this,0x18); return; }
  message=normalize(g_GemsRecovered+L"!");
  play(this,0x24);
  while(static_cast<int>(equipment->m_SocketedEquipment.size())>0) {
   CEquipment* gem=equipment->m_SocketedEquipment[0];
   equipment->m_SocketedEquipment.removeAt(0);
   if(!gem->ISA(static_cast<UNITTYPES::EUNITTYPES>(0xa0))) {
    gem->reapplyEffects(true); gem->reapplyAffixes(true);
    if(gem->m_iUnknown28C>0) gem->improveHeirloom();
   }
   returnItem(this,m_pCharacter->m_pInventory,gem);
  }
  m_pCharacter->m_pInventory->removeEquipment(equipment);
  delete equipment;
  complete(this,g_Sockets,message);
  updateLayout();
  return;
 case 0x1b: {
  equipment=reinterpret_cast<CEquipment*>(m_pCharacter->m_pInventory->getEquipmentInSlot(14));
  if(!equipment) { play(this,0x18); return; }
  m_bRetirementComplete=true; m_bInteractionComplete=true;
  m_pGameUI->getCharacter()->setTarget(NULL);
  ClientFields& state=*reinterpret_cast<ClientFields*>(client(m_pGameUI));
  state.click4.setObject(NULL); state.click3.setObject(NULL); state.click1.setObject(NULL); state.click2.setObject(NULL);
  m_pGameUI->closeRight();
  m_pCharacter->m_pInventory->removeEquipment(equipment);
  if(equipment->m_iUnknown28C==0) equipment->m_sItemName=actor(m_pCharacter).name+L"'s "+equipment->getItemName();
  ++equipment->m_iUnknown28C;
  equipment->improveHeirloom();
  reinterpret_cast<ClientFields*>(client(m_pGameUI))->heirloom=equipment;
  reinterpret_cast<ClientFields*>(client(m_pGameUI))->retirements=actor(m_pGameUI->getCharacter()).retirements+1;
  actor(m_pCharacter).retired=true;
  CSteamStats::getSingleton()->incrementStat(static_cast<ESTATS>(11),1);
  CSteamStats::getSingleton()->incrementStat(static_cast<ESTATS>(12),m_pCharacter->m_iUnitLevel);
  m_pGameUI->clearMenuMouseOvers();
  updateLayout();
  break;
 }
 default:return;
 }
 if(equipment && static_cast<unsigned>(m_iMode-0x15)<2) {
  if(disenchanted) {
   if(equipment->m_iUnknown344==0) reinterpret_cast<CAchievement*>(CAchievements::getSingleton()->getAchievement(static_cast<EACHIEVEMENTS>(29)))->forceComplete();
   CSteamStats::getSingleton()->incrementStat(static_cast<ESTATS>(7),1);
  } else if(equipment->m_iUnknown344==5 || equipment->m_iUnknown344==10) {
   reinterpret_cast<CAchievement*>(CAchievements::getSingleton()->getAchievement(static_cast<EACHIEVEMENTS>(equipment->m_iUnknown344==5?32:33)))->forceComplete();
  }
 }
}
#undef INTERACTION_TRANSLATION

// Complete candidate entry; not published until differential verification.
#include "Settings.h"
#include "GameVariables.h"
#include "ResourceManager.h"
#include "GenericModel.h"
#include "FileSystem.h"
#include <OgreEntity.h>
#include <OgreMesh.h>
__attribute__((flatten)) void CEnchantMenu::createMenus()
{
    typedef char check_m_pParent[__builtin_offsetof(CEnchantMenu,m_pParent)==24?1:-1];
    typedef char check_m_pBackground[__builtin_offsetof(CEnchantMenu,m_pBackground)==32?1:-1];
    typedef char check_m_pPanel[__builtin_offsetof(CEnchantMenu,m_pPanel)==40?1:-1];
    typedef char check_m_pSocketedIconParent[__builtin_offsetof(CEnchantMenu,m_pSocketedIconParent)==48?1:-1];
    typedef char check_m_pForeground[__builtin_offsetof(CEnchantMenu,m_pForeground)==56?1:-1];
    typedef char check_m_pTitle[__builtin_offsetof(CEnchantMenu,m_pTitle)==64?1:-1];
    typedef char check_m_pDescription[__builtin_offsetof(CEnchantMenu,m_pDescription)==72?1:-1];
    typedef char check_m_pAccept[__builtin_offsetof(CEnchantMenu,m_pAccept)==80?1:-1];
    typedef char check_m_pCharacter[__builtin_offsetof(CEnchantMenu,m_pCharacter)==96?1:-1];
    typedef char check_m_pOwnerItem[__builtin_offsetof(CEnchantMenu,m_pOwnerItem)==104?1:-1];
    typedef char check_m_bOpen[__builtin_offsetof(CEnchantMenu,m_bOpen)==112?1:-1];
    typedef char check_m_bInteractionComplete[__builtin_offsetof(CEnchantMenu,m_bInteractionComplete)==114?1:-1];
    typedef char check_m_bRetirementComplete[__builtin_offsetof(CEnchantMenu,m_bRetirementComplete)==115?1:-1];
    typedef char check_m_pSettings[__builtin_offsetof(CEnchantMenu,m_pSettings)==120?1:-1];
    typedef char check_m_pGameUI[__builtin_offsetof(CEnchantMenu,m_pGameUI)==128?1:-1];
    typedef char check_m_pSceneManager[__builtin_offsetof(CEnchantMenu,m_pSceneManager)==136?1:-1];
    typedef char check_m_pRenderWindow[__builtin_offsetof(CEnchantMenu,m_pRenderWindow)==144?1:-1];
    typedef char check_m_pMenuModel[__builtin_offsetof(CEnchantMenu,m_pMenuModel)==160?1:-1];
    typedef char check_m_pResourceManager[__builtin_offsetof(CEnchantMenu,m_pResourceManager)==168?1:-1];
    typedef char check_m_pSoundBank[__builtin_offsetof(CEnchantMenu,m_pSoundBank)==184?1:-1];
    typedef char check_m_aiSlotData[__builtin_offsetof(CEnchantMenu,m_aiSlotData)==192?1:-1];
    typedef char check_m_aiLocalSlotData[__builtin_offsetof(CEnchantMenu,m_aiLocalSlotData)==196?1:-1];
    typedef char check_m_pMainGlowWindows[__builtin_offsetof(CEnchantMenu,m_pMainGlowWindows)==200?1:-1];
    typedef char check_m_pMainSocketGlowWindows[__builtin_offsetof(CEnchantMenu,m_pMainSocketGlowWindows)==208?1:-1];
    typedef char check_m_pSocketedSizeWindows[__builtin_offsetof(CEnchantMenu,m_pSocketedSizeWindows)==216?1:-1];
    typedef char check_m_pMainStackWindows[__builtin_offsetof(CEnchantMenu,m_pMainStackWindows)==224?1:-1];
    typedef char check_m_pImageset[__builtin_offsetof(CEnchantMenu,m_pImageset)==248?1:-1];
    typedef char check_m_pSlotGlow[__builtin_offsetof(CEnchantMenu,m_pSlotGlow)==256?1:-1];
    typedef char check_m_iMode[__builtin_offsetof(CEnchantMenu,m_iMode)==268?1:-1];
    typedef char check_size[sizeof(CEnchantMenu)==0x110?1:-1];
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
    m_pBackground=CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow","EnchantSheet","");
    m_pBackground->setSize(CEGUI::UVector2(CEGUI::UDim(1,0),CEGUI::UDim(1,0)));
    m_pBackground->setProperty("RiseOnClick","False");
    m_pBackground->setPosition(CEGUI::UVector2(CEGUI::UDim(0,0),CEGUI::UDim(0,0)));
    m_pBackground->setMousePassThroughEnabled(true);
    m_pBackground->setZOrderingEnabled(false);
    m_pBackground->subscribeEvent(CEGUI::Window::EventMouseMove,CEGUI::SubscriberSlot(&CEnchantMenu::handle_MouseThrough,this));
    CEGUI::Window* barrier=CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow","EnchantClickBarrier","");
    m_pBackground->addChildWindow(barrier);
    float barrierHeight=m_pGameUI->scaledY(768.0f);
    float barrierWidth=m_pGameUI->scaledY(390.0f);
    barrier->setSize(CEGUI::UVector2(CEGUI::UDim(0,barrierWidth),CEGUI::UDim(0,barrierHeight)));
    barrier->setProperty("RiseOnClick","False");
    barrier->setPosition(CEGUI::UVector2(CEGUI::UDim(0,0),CEGUI::UDim(0,0)));
    barrier->moveToBack();
    barrier->setZOrderingEnabled(false);
    CFileInfo fileInfo;
    CFileSystem::getSingleton()->getFileInfo(L"media/ui/enchantmenu.layout",fileInfo,false,true,false);
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
    m_aiSlotData[0]=14;
    m_aiLocalSlotData[0]=0;
    m_pDescription=m_pPanel->recursiveChildSearch("Dialog");
    m_pAccept=m_pPanel->recursiveChildSearch("Accept");
    {
        const unsigned i=0;
        CEGUI::Window* slot=m_pPanel->recursiveChildSearch("ItemSlot");
        slot->moveToFront();
        slot->setRiseOnClickEnabled(false);
        slot->setWantsMultiClickEvents(false);
        slot->setUserData(&m_aiLocalSlotData[i]);
        slot->setAlwaysOnTop(true);
        slot->subscribeEvent(CEGUI::Window::EventMouseButtonDown,CEGUI::SubscriberSlot(&CEnchantMenu::handle_ItemClick,this));
        slot->subscribeEvent(CEGUI::Window::EventMouseEnters,CEGUI::SubscriberSlot(&CEnchantMenu::handle_MouseOver,this));
        slot->subscribeEvent(CEGUI::Window::EventMouseMove,CEGUI::SubscriberSlot(&CEnchantMenu::handle_MouseOver,this));
        slot->subscribeEvent(CEGUI::Window::EventMouseLeaves,CEGUI::SubscriberSlot(&CEnchantMenu::handle_MouseOut,this));
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
    m_pSocketedIconParent=CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow","EnchanterSockets","");
    m_pPanel->addChildWindow(m_pSocketedIconParent);
    m_pSocketedIconParent->setSize(m_pPanel->getSize());
    m_pSocketedIconParent->setProperty("RiseOnClick","False");
    m_pSocketedIconParent->setPosition(CEGUI::UVector2(CEGUI::UDim(0,0),CEGUI::UDim(0,0)));
    m_pSocketedIconParent->setMousePassThroughEnabled(true);
    m_pSocketedIconParent->moveToFront();
    m_pForeground=CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow","EnchanterSocketsO","");
    m_pPanel->addChildWindow(m_pForeground);
    m_pForeground->setSize(m_pPanel->getSize());
    m_pForeground->setProperty("RiseOnClick","False");
    m_pForeground->setPosition(CEGUI::UVector2(CEGUI::UDim(0,0),CEGUI::UDim(0,0)));
    m_pForeground->setMousePassThroughEnabled(true);
    m_pForeground->moveToFront();
        CEGUI::Window* glow=CEGUI::WindowManager::getSingleton().createWindow("GuiLook/StaticImage",STRINGS::uniqueName(std::string("gui_")).c_str(),"");
        m_pSocketedSizeWindows[i]->getParent()->addChildWindow(glow);
        glow->setRiseOnClickEnabled(false);
        glow->setWantsMultiClickEvents(false);
        glow->setMousePassThroughEnabled(true);
        glow->setMutedState(true);
        glow->setZOrderingEnabled(false);
        glow->setPosition(slot->getPosition());
        glow->setSize(slot->getSize());
        m_pMainGlowWindows[i]=glow;
        CEGUI::Window* socketGlow=CEGUI::WindowManager::getSingleton().createWindow("GuiLook/StaticImage",STRINGS::uniqueName(std::string("gui_")).c_str(),"");
        m_pForeground->addChildWindow(socketGlow);
        socketGlow->setRiseOnClickEnabled(false);
        socketGlow->setWantsMultiClickEvents(false);
        socketGlow->setMousePassThroughEnabled(true);
        socketGlow->setMutedState(true);
        // Unlike Combine, this entry queries the slot before its parent.
        const CEGUI::UVector2& slotPosition=slot->getPosition();
        const CEGUI::UVector2& parentPosition=slot->getParent()->getPosition();
        socketGlow->setPosition(parentPosition+slotPosition);
        socketGlow->setSize(slot->getSize());
        m_pMainSocketGlowWindows[i]=socketGlow;
        m_pSocketedSizeWindows[i]->moveToFront();
    }
}

#include "EnchantMenu.h"
#include "Equipment.h"
#include "Inventory.h"
#include "Level.h"
#include "GenericModel.h"
#include "Settings.h"
#include "SoundBank.h"
#include "StringTranslate.h"
#include "StringUtilities.h"
#include <CEGUI.h>

void CEnchantMenu::setOpen(bool open, EAIState state)
{
    m_iMode = state;
    if (m_bOpen) {
        if (open) {
            m_bOpen = open;
            updateLayout();
            return;
        }
        if (m_pCharacter) {
            CEquipment* item = m_pCharacter->m_pInventory->getEquipmentInSlot(14);
            if (item) {
                m_pCharacter->m_pInventory->removeEquipment(item);
                if (!m_pCharacter->m_pInventory->pickupEquipment(item, true)) {
                    Ogre::Vector3 position = m_pCharacter->getPosition(true);
                    m_pCharacter->getLevel()->addItem(item, position, true);
                    item->drop();
                }
            }
        }
        m_pSoundBank->playSample(66, 0, 0.0f, 0.0f, false);
        m_pMenuModel->blendAnimation("CLOSE", false, 0.1f, 2.0f, -1.0f);
        m_bFullyClosed = 0;
        m_bOpen = false;
        return;
    }
    if (!open) {
        m_bOpen = false;
        return;
    }
    m_pSettings->GetInt(KSETTINGS_RES_WIDTH);
    m_pSettings->GetInt(KSETTINGS_RES_HEIGHT);
#define OPEN_TRANSLATION(NAME, TEXT) static std::wstring NAME; if (NAME.empty()) NAME = CStringTranslate::getSinglton()->getTranslateString(TEXT)
    OPEN_TRANSLATION(g_Enchant, L"Enchant");
    OPEN_TRANSLATION(g_Destroy, L"Destroy");
    OPEN_TRANSLATION(g_Sockets, L"Sockets");
    OPEN_TRANSLATION(g_Recover, L"Recover");
    OPEN_TRANSLATION(g_Retire, L"Retire");
    OPEN_TRANSLATION(g_Heirloom, L"Heirloom");
#undef OPEN_TRANSLATION
    switch (m_iMode) {
    case 21:
    case 22:
        m_pTitle->setText(CEGUI::String((const unsigned char*)STRINGS::StringConvertToUTF8(std::wstring(g_Enchant.c_str())).c_str()));
        m_pAccept->setText(CEGUI::String((const unsigned char*)STRINGS::StringConvertToUTF8(std::wstring(g_Enchant.c_str())).c_str()));
        break;
    case 25:
        m_pTitle->setText(CEGUI::String((const unsigned char*)STRINGS::StringConvertToUTF8(std::wstring(g_Sockets.c_str())).c_str()));
        m_pAccept->setText(CEGUI::String((const unsigned char*)STRINGS::StringConvertToUTF8(std::wstring(g_Destroy.c_str())).c_str()));
        break;
    case 26:
        m_pTitle->setText(CEGUI::String((const unsigned char*)STRINGS::StringConvertToUTF8(std::wstring(g_Sockets.c_str())).c_str()));
        m_pAccept->setText(CEGUI::String((const unsigned char*)STRINGS::StringConvertToUTF8(std::wstring(g_Recover.c_str())).c_str()));
        break;
    case 27:
        m_pTitle->setText(CEGUI::String((const unsigned char*)STRINGS::StringConvertToUTF8(std::wstring(g_Heirloom.c_str())).c_str()));
        m_pAccept->setText(CEGUI::String((const unsigned char*)STRINGS::StringConvertToUTF8(std::wstring(g_Retire.c_str())).c_str()));
        break;
    }
    m_pSoundBank->playSample(22, 0, 0.0f, 0.0f, false);
    m_pMenuModel->setVisible(true);
    if (m_pMenuModel->animationPlaying("CLOSE"))
        m_pMenuModel->blendAnimation("OPEN", false, 0.1f, 2.0f, -1.0f);
    else
        m_pMenuModel->playAnimation("OPEN", false, 2.0f, -1.0f);
    m_pMenuModel->queueBlendAnimation("IDLE", true, 0.1f, 1.0f);
    m_pParent->addChildWindow(m_pBackground);
    m_pBackground->moveToBack();
    m_pGameUI->queueTip(static_cast<EContextTip>(13));
    m_bOpen = open;
    updateLayout();
}

namespace enchant_controls {
struct UIFields {char prefix[0xb8];CEquipment* dragged;};
struct HoverState {char prefix[0x198];bool flag198;};
struct ClientFields {char prefix[0x1c8];TSafePointer<CRunicCore> first,second,third,fourth;};
struct ClientUI {char prefix[0x1920];ClientFields* client;};
inline __attribute__((always_inline,flatten)) void clearMouseClicks(CGameUI* ui) {
 ClientFields* c=reinterpret_cast<ClientUI*>(ui)->client;
 c->fourth.setObject(0);c->third.setObject(0);c->first.setObject(0);c->second.setObject(0);
}
}
void CEnchantMenu::setOwner(CCharacter* owner){m_pOwner=owner;m_pOwnerItem=0;}
void CEnchantMenu::setOwnerItem(CItem* item){m_pOwner=0;m_pOwnerItem=item;}
void CEnchantMenu::equipmentEquipped(CEquipment*){updateLayout();}
void CEnchantMenu::equipmentUnequipped(CEquipment*){updateLayout();}
void CEnchantMenu::inventoryDestroyed(){}
bool CEnchantMenu::handle_ItemClick(const CEGUI::EventArgs& event) {
 const CEGUI::MouseEventArgs& mouse=static_cast<const CEGUI::MouseEventArgs&>(event);
 if(mouse.window){int slot=*static_cast<int*>(mouse.window->getUserData());
  if(mouse.button==CEGUI::LeftButton)m_ClickedSlot=m_aiSlotData[slot];
  else if(mouse.button==CEGUI::RightButton)m_RightClickedSlot=m_aiSlotData[slot];
 }
 return true;
}
bool CEnchantMenu::handle_MouseThrough(const CEGUI::EventArgs&){m_bHover=false;return true;}
bool CEnchantMenu::handle_onClick(const CEGUI::EventArgs& event) {
 const CEGUI::MouseEventArgs& mouse=static_cast<const CEGUI::MouseEventArgs&>(event);
 if(mouse.button==CEGUI::LeftButton&&mouse.window)return onClick(*static_cast<ELayoutFunction*>(mouse.window->getUserData()));
 return true;
}
void CEnchantMenu::equipmentDropped(CEquipment*){updateLayout();}
void CEnchantMenu::equipmentPickedUp(CEquipment*){updateLayout();}
void CEnchantMenu::equipmentUsed(CEquipment*){updateLayout();}
void CEnchantMenu::setPlayer(CCharacter* player) {
 if(player!=m_pCharacter)inventoryDestroyed();
 if(m_pCharacter)m_pCharacter->m_pInventory->removeListener(this);
 m_pCharacter=player;
 if(player)player->m_pInventory->addListener(this);
}
bool CEnchantMenu::handle_MouseOut(const CEGUI::EventArgs& event) {
 CEGUI::Window* window=static_cast<const CEGUI::WindowEventArgs&>(event).window;
 CCharacter* owner=m_pCharacter;
 if(window&&owner) {
  int slot=*static_cast<int*>(window->getUserData());
  CEquipment* item=owner->m_pInventory->getEquipmentInSlot(m_aiSlotData[slot]);
  if(item==m_pHoverObject) {
   m_pHoverObject=0;
   CEquipment* dragged=reinterpret_cast<enchant_controls::UIFields*>(m_pGameUI)->dragged;
   if(!dragged||!dragged->ISA(static_cast<UNITTYPES::EUNITTYPES>(120))) {
    m_pSocketedIconParent->setVisible(false);m_pForeground->setVisible(false);
   }
  }
 }
 return true;
}
bool CEnchantMenu::handle_CloseButton(const CEGUI::EventArgs& event) {
 if(static_cast<const CEGUI::MouseEventArgs&>(event).button==CEGUI::LeftButton) {
  m_bInteractionComplete=true;m_pGameUI->getCharacter()->setTarget(0);
  enchant_controls::clearMouseClicks(m_pGameUI);m_pGameUI->closeRight();
 }
 return true;
}
bool CEnchantMenu::onClick(ELayoutFunction action) {
 if(m_bOpen) {
  if(static_cast<int>(action)==8) {
   m_bInteractionComplete=true;m_pGameUI->getCharacter()->setTarget(0);
   enchant_controls::clearMouseClicks(m_pGameUI);m_pGameUI->closeRight();
  }else if(static_cast<int>(action)==9)performInteraction();
 }
 return true;
}
void CEnchantMenu::mapEventHandlers(CEGUI::Window* window) {
 int count=static_cast<int>(window->getChildCount());
 for(int i=0;i<count;++i)mapEventHandlers(window->getChildAtIdx(i));
 try {
  if(window->isPropertyPresent("onClick")&&!window->getProperty("onClick").empty())
   window->subscribeEvent(CEGUI::Window::EventMouseButtonDown,CEGUI::Event::Subscriber(&CEnchantMenu::handle_onClick,this));
 }catch(...) {}
}


bool CEnchantMenu::processInput(void*,float,bool active) {
 if(!active) {
  m_pHoverObject=0;m_pSocketedIconParent->setVisible(false);m_pForeground->setVisible(false);
  if(m_pSlotGlow->getParent()&&m_pSlotGlow->getParent()->isChild(m_pSlotGlow))m_pSlotGlow->getParent()->removeChildWindow(m_pSlotGlow);
  return true;
 }
 bool result=true;
 if(m_bInteractionComplete){setOpen(false);m_bInteractionComplete=false;result=false;}
 CEquipment* dragged=m_pCharacter?reinterpret_cast<enchant_controls::UIFields*>(m_pGameUI)->dragged:0;
 if(dragged&&dragged->ISA(static_cast<UNITTYPES::EUNITTYPES>(120))) {
  m_pForeground->setVisible(true);m_pForeground->moveToFront();
  m_pSocketedIconParent->setVisible(true);m_pSocketedIconParent->moveToFront();
 }else {
  if(!m_pHoverObject){m_pSocketedIconParent->setVisible(false);m_pForeground->setVisible(false);}
  else if(reinterpret_cast<enchant_controls::HoverState*>(m_pHoverObject)->flag198){m_pHoverObject=0;m_pForeground->setVisible(false);m_pSocketedIconParent->setVisible(false);}
 }
 if(!m_bHover) {
  if(m_pSlotGlow->getParent()&&m_pSlotGlow->getParent()->isChild(m_pSlotGlow))m_pSlotGlow->getParent()->removeChildWindow(m_pSlotGlow);
  m_pHoverObject=0;
 }
 m_ClickedSlot=-1;m_RightClickedSlot=-1;return result;
}

bool CEnchantMenu::handle_MouseOver(const CEGUI::EventArgs& event) {
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
