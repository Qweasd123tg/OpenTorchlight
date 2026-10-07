#include <string>

#include "CEGUI.h"

#include "BaseUnit.h"
#include "Equipment.h"
#include "GameUI.h"
#include "StringUtilities.h"

#include "MerchantMenu.h"

// 6229 machine bytes at 0xb6ab50. The two integer parameters are not interchangeable: the
// second one indexes the window arrays of CMerchantMenu, the third one (scaled by 4)
// becomes the address stored in the item icon's userData.
void CMerchantMenu::setPetSlotIcon(CEquipment* pItem, int iSlotIndex, int iDataIndex)
{


    // Two independent getPosition() calls on the slot window (b6ab7c, b6abd4). The second
    // UDim of the vector is the one that is used, and asAbsolute(0.0f) really multiplies by
    // a runtime zero: 0.0f * inf is a NaN, which fails the "0.0f < x" test inside
    // PixelAligned and would take the other branch, so the multiply must stay.
    // UDim::asAbsolute returns float in this CEGUI (CEGUIUDim.h).
    unsigned int uiIconX = (unsigned int)(m_pSlotWindows[iSlotIndex]->getPosition().d_x.asAbsolute(0.0f));
    unsigned int uiIconY = (unsigned int)(m_pSlotWindows[iSlotIndex]->getPosition().d_y.asAbsolute(0.0f));

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
        // rdi = this, rsi = the argument: the icon is taken out of its current parent and
        // then added to the slot window.
        CEGUI::Window* pOldParent = pIcon->getParent();
        if (pOldParent != 0)
        {
            pOldParent->removeChildWindow(pIcon);
        }

        m_pSlotWindows[iSlotIndex]->addChildWindow(pIcon);

        // Both calls are in the original; only the second one leaves the icon at (0,0).
        pIcon->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f, 0.0f), CEGUI::UDim(0.0f, 1.0f)));
        pIcon->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f, 0.0f), CEGUI::UDim(0.0f, 0.0f)));

        pIcon->setSize(m_pSlotWindows[iSlotIndex]->getSize());
        pIcon->moveToFront();

        pIcon->setUserData(&m_aiSlotData[iDataIndex]);
    }

    // Socket count glow layer, then the unidentified layer. The two layers are separate:
    // m_bUnknown348 and the socket count are both tested, and moveToFront() only happens
    // on the glow layer when the count is not zero. Every setProperty below is a single
    // expression with three CEGUI::String temporaries (image name, imageToString result,
    // "Image"), destroyed in that reverse order after the call.


    if (!pItem->m_bUnknown348 || pItem->m_iSocketCount == 0)
    {
        m_pSocketGlowWindows[iSlotIndex]->setProperty("Image", "");
    }
    else
    {
        if (pItem->m_iSocketCount == 1)
        {
            m_pSocketGlowWindows[iSlotIndex]->setProperty("Image", CEGUI::PropertyHelper::imageToString(
                &m_pImageset->getImage("onesocketglow")));
        }
        else
        {
            m_pSocketGlowWindows[iSlotIndex]->setProperty("Image", CEGUI::PropertyHelper::imageToString(
                &m_pImageset->getImage("twosocketglow")));
        }

        m_pSocketGlowWindows[iSlotIndex]->moveToFront();
    }

    if (pItem->m_bUnknown348)
    {
        m_pUnidentifiedWindows[iSlotIndex]->setProperty("Image", "");
    }
    else
    {
        m_pUnidentifiedWindows[iSlotIndex]->setProperty("Image", CEGUI::PropertyHelper::imageToString(
            &m_pImageset->getImage("unidentified")));
    }

    // Multi socket items are nudged up by a fraction of the slot height.
    if (pItem->m_iSocketCount > 1)
    {
        uiIconY = (unsigned int)((float)uiIconY +
            m_pSlotWindows[iSlotIndex]->getSize().d_y.asAbsolute(0.0f) * -0.19f);
    }

    if (pItem->m_SocketedEquipment.size() != 0)
    {


        for (unsigned int iSocket = 0; iSocket < pItem->m_SocketedEquipment.size(); iSocket++)
        {
            // TArrayList::operator[] falls back to m_pData[0] when the index is outside the
            // capacity, and that fallback is observable here.
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

                // Written a second time on purpose: the original listing stores this byte
                // once here and once right after setMutedState(true), and the calls in
                // between keep both stores alive.
                pSocketedIcon->setMousePassThroughEnabled(true);
            }

            // Also reached when createIcon() produced no window: the size is still read and
            // the following placement is still advanced.
            uiIconY = (unsigned int)((float)uiIconY +
                m_pSlotWindows[iSlotIndex]->getSize().d_y.asAbsolute(0.0f) * 0.4f);
        }
    }

    // Main slot glow. canEquip() and isMagical() are virtual calls, ISA() is a direct call;
    // the short circuit order is part of the behaviour.


    // Only the numeric values are proven; the enumerator names live in UnitTypes.h, which
    // is not part of the evidence (see output/UNRESOLVED.md).
    const UNITTYPES::EUNITTYPES kIsaSlotGold = static_cast<UNITTYPES::EUNITTYPES>(0x36);
    const UNITTYPES::EUNITTYPES kIsaSlotBlue = static_cast<UNITTYPES::EUNITTYPES>(0x37);

    if (!pItem->canEquip(m_pCanEquipCharacter, false))
    {
        if (pItem->isMagical())
        {
            m_pSlotGlowWindows[iSlotIndex]->setProperty("Image", CEGUI::PropertyHelper::imageToString(
                &m_pImageset->getImage("blueredslotglow")));
        }
        else
        {
            // 11 byte image name at 0xfe60e3; the bytes are not in the confirmed rodata.
            m_pSlotGlowWindows[iSlotIndex]->setProperty("Image", CEGUI::PropertyHelper::imageToString(
                &m_pImageset->getImage("redslotglow")));
        }
    }
    else if (pItem->ISA(kIsaSlotGold))
    {
        m_pSlotGlowWindows[iSlotIndex]->setProperty("Image", CEGUI::PropertyHelper::imageToString(
            &m_pImageset->getImage("goldslotglow")));
    }
    else if (pItem->isMagical())
    {
        if (pItem->ISA(kIsaSlotBlue))
        {
            m_pSlotGlowWindows[iSlotIndex]->setProperty("Image", CEGUI::PropertyHelper::imageToString(
                &m_pImageset->getImage("blueslotglow")));
        }
        else
        {
            m_pSlotGlowWindows[iSlotIndex]->setProperty("Image", CEGUI::PropertyHelper::imageToString(
                &m_pImageset->getImage("greenslotglow")));
        }
    }
    else
    {
        m_pSlotGlowWindows[iSlotIndex]->setProperty("Image", "");
    }

    // Stack count window; nothing at all is called when it does not exist.


    if (m_pStackWindows[iSlotIndex] != 0)
    {
        if (pItem->m_iUnknown238 <= 1)
        {
            m_pStackWindows[iSlotIndex]->setVisible(false);
        }
        else
        {
            m_pStackWindows[iSlotIndex]->setVisible(true);

            // The GetValueAsString() temporary dies right after the concatenation and the
            // concatenated string dies after setText.
            std::string sCount = "x" + STRINGS::GetValueAsString(pItem->m_iUnknown238);

            // The constructor the listing calls is String(unsigned char const*), i.e.
            // String(const utf8*) - plain c_str() would select String(const char*).
            CEGUI::String sText((const unsigned char*)sCount.c_str());

            m_pStackWindows[iSlotIndex]->setText(sText);
        }
    }
}
