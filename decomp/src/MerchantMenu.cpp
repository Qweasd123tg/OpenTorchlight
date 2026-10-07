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


// ============================================================================
//  MerchantMenu.cpp  --  REPAIRED reconstruction candidate
//
//  CMerchantMenu::createMenus()
//      _ZN13CMerchantMenu11createMenusEv
//      0xb6ed20 .. 0xb7729f   (34170 original machine bytes)
//
//  Target: GCC 4.4.7, Linux x86-64, C++98, CEGUI 0.6.2.
//  Companion files: output/MerchantMenu.h, output/other-class-additions.h,
//                   output/UNRESOLVED.md, output/STATUS.md.
//
//  No inline assembly, no p-code, no re-entry into the original address, no
//  stubs, no local workarounds.  Every statement is an SDK call whose target is
//  named in input/original.asm, or a call proven by the original ELF but
//  declared in output/other-class-additions.h.
//
//  =========================================================================
//  REPAIRS IN THIS REVISION - all five forced by
//  input/supervisor-verification/, none by guesswork:
//  =========================================================================
//
//  R1  0xfc6774 is float 0.75f (0x3f400000), not 1.0f.  Referenced-data.json
//      "float32_candidate": 0.75.
//
//  R2  The division by 0.75f applies to fResHeight ALONE, before the
//      subtraction, not to (fResWidth - fResHeight).  b6ee19 divss comes
//      before b6ee34 subss.  The previous candidate had both the constant and
//      the operand order wrong.
//
//  R3  0x14247e0 is CEGUI::Window::EventMouseButtonDown, not
//      EventMouseClick.  The other three event statics were right:
//      0x1423b80 EventMouseEnters, 0x1424020 EventMouseMove,
//      0x1423700 EventMouseLeaves.  Symbols from referenced-data.json.
//
//  R4  0x14c7380 / 0x14c7388 are EMPTY_STRING / EMPTY_WSTRING, i.e. the
//      CFileInfo default constructor's member initialisers - not merchant
//      layout path globals.  The CEGUI::String handed to loadWindowLayout is
//      built from fileInfo.m_sResourceName, which the getFileInfo() call fills
//      in.  That is the call's real purpose, and it is load bearing.
//      0xff0080 is L"media/ui/merchantmenu.layout" (the probe path) and
//      0xfeffe0 is L"media/ui/models/merchant/merchant.mesh"; 0x1001608 is an
//      empty wide string.  No invented text remains.
//
//  R5  Vtable slot 11 takes THREE floats (xmm0, xmm1 and xmm2 are all
//      loaded -0.5f, 0.0f, 0.0f), so the call is the inline
//      CPositionableObject::setPosition(float,float,float) declared at
//      PositionableObject.h:21, not a setSize(float,float).  Slot 10 with one
//      bool stays CSceneNodeObject::setVisible(bool).  Neither guess survives.
//
//  R6  All three raw-offset accessors are deleted.  sdk-layout-facts.json
//      pins the real CEGUI::Window, and the "unexplained" byte stores are
//      CEGUIWindow.h's own inline setters:
//          +0x213 == d_riseOnClick            -> setRiseOnClickEnabled(bool)
//          +0x3e2 == d_mousePassThroughEnabled-> setMousePassThroughEnabled(bool)
//          +0xb0  == d_parent                 -> getParent()
//      All three are one-line inline accessors in the supplied SDK header, so
//      GCC 4.4.7 emits exactly the observed load/store.  The previous
//      "shipped CEGUI differs from input/cegui-0.6.2" theory was wrong.
//
//  R7  SubscriberSlot is 8 bytes and is passed BY VALUE indirectly; the ABI
//      probe (abi_probe.s pass_subscriber) shows GCC 4.4.7 copying it to a
//      stack temporary and passing that address in a register.  The supplied
//      subscribeEvent(const String&, Event::Subscriber) spelling is therefore
//      already correct and is unchanged.
//
//  R8  MemberFunctionSlot<CMerchantMenu> really is 32 bytes: member pointers
//      are 16 bytes (ptr + 0 adj for a non-virtual member), so the store of 0
//      at slot+0x10 is the member pointer's second word, not a flag.
//
//  R9  m_pPositionableObject (+0x90) is retyped to CGenericModel*, because
//      CResourceManager::createGenericModel returns exactly that and the
//      listing stores its return value there.
// ============================================================================

#include <string>

#include <CEGUIString.h>
#include <CEGUIEvent.h>
#include <CEGUIEventSet.h>
#include <CEGUISubscriberSlot.h>
#include <CEGUIWindow.h>
#include <CEGUIWindowManager.h>
#include <CEGUIImagesetManager.h>
#include <CEGUIPropertyHelper.h>
#include <CEGUIcolour.h>

#include "MerchantMenu.h"
#include "other-class-additions.h"

#include "FileSystem.h"            // CFileSystem::getSingleton, CFileInfo
#include "EmptyStrings.h"
#include "GameVariables.h"         // KSETTINGS_RES_WIDTH, KSETTINGS_RES_HEIGHT
#include "Settings.h"              // KSETTINGS_YRATIO
#include "StringUtilities.h"       // STRINGS::uniqueName, GetValueAsString
#include "DynamicPropertyFile.h"
#include "ResourceManager.h"
#include "GenericModel.h"          // CGenericModel, createGenericModel return
#include "PositionableObject.h"    // setPosition(float,float,float)
#include "SceneNodeObject.h"       // setVisible(bool), getEntity()
#include "GameUI.h"

#include <OgreAxisAlignedBox.h>
#include <OgreEntity.h>
#include <OgreMesh.h>


// ============================================================================
//  void CMerchantMenu::createMenus()                          [A] void, [A] addr
// ============================================================================
void CMerchantMenu::createMenus()
{
    // ------------------------------------------------------------------
    // [A] Resolution probe.  GetInt returns unsigned; both results are
    //     narrowed to float by cvtsi2ss (b6ed43 / b6ed5c) before anything
    //     else happens, so the conversions are load bearing, not cosmetic.
    // ------------------------------------------------------------------
    float fResWidth  = (float)m_pDynamicPropertyFile->GetInt(KSETTINGS_RES_WIDTH);
    float fResHeight = (float)m_pDynamicPropertyFile->GetInt(KSETTINGS_RES_HEIGHT);

    // ------------------------------------------------------------------
    // [A] Generic model.  Receiver m_pResourceManager (+0x98); the scene
    //     manager argument is +0x78; the two wide arguments are
    //     L"media/ui/models/merchant/merchant.mesh" (0xfeffe0) and L""
    //     (0x1001608, a terminated empty string); all three trailing bools
    //     are false (r8d = 0, r9d = 0, and 0 on the stack).
    //     Result stored at +0x90.
    // ------------------------------------------------------------------
    m_pPositionableObject = m_pResourceManager->createGenericModel(
        m_pUnknown78,
        L"media/ui/models/merchant/merchant.mesh",
        L"",
        false, false, false);

    // ------------------------------------------------------------------
    // [A] Reach the model's Ogre::Entity (CSceneNodeObject::m_pEntity at
    //     +0x60 - see output/other-class-additions.h for the offset chain),
    //     take its Mesh, and blow the mesh bounds out to +/-100000 per axis.
    //     The axis aligned box is built in stack slots 0x3980..0x3997 as
    //     {min, max} and passed by const reference; the bool argument is the
    //     literal 1.  0xc7c35000 == -100000.0f, 0x47c35000 == +100000.0f.
    // ------------------------------------------------------------------
    m_pPositionableObject->getEntity()->getMesh()->_setBounds(
        Ogre::AxisAlignedBox(
            Ogre::Vector3(-100000.0f, -100000.0f, -100000.0f),
            Ogre::Vector3( 100000.0f,  100000.0f,  100000.0f)),
        true);

    // ------------------------------------------------------------------
    // [A] Screen scale, with the operand order the instructions actually
    //     have:  b6ee0c  xmm0 = fResHeight
    //             b6ee19  divss 0.75f            <-- on fResHeight ALONE
    //             b6ee21  xmm1 = fResWidth
    //             b6ee34  subss                 <-- fResWidth - (fResHeight/0.75f)
    //             b6ee42  call GetFloat         <-- GetFloat happens AFTER the sub
    //             b6ee54  divss
    //     0xfc6774 == 0x3f400000 == 0.75f.  Note GetFloat is called after the
    //     subtraction, which is why the subtraction is written out rather than
    //     folded into a single expression.
    // ------------------------------------------------------------------
    float fScale = fResWidth - (fResHeight / 0.75f);
    fScale /= m_pDynamicPropertyFile->GetFloat(KSETTINGS_YRATIO);

    // [A] Vtable slot 11.  Decisive detail: %rdi still holds `this` and NO
    //     memory argument is set up before the call, so the parameter cannot be
    //     a reference or a struct-by-pointer - CPositionableObject's
    //     setPosition(const Ogre::Vector3&) overload would need %rdi and is
    //     therefore excluded.  What is left is three float registers:
    //         b6ee58  movss 0xfa86f4,%xmm0     -0.5f   (0xbf000000)
    //         b6ee60  xorps  %xmm2,%xmm2       0.0f
    //         b6ee63  mulss  %xmm1,%xmm0       -0.5f * fScale
    //         b6ee67  movaps %xmm2,%xmm1       0.0f
    //         b6ee6a  call   *%rbp
    //     Among CPositionableObject's three-float virtuals
    //     (setPosition, setScale, setForward, setRight, setUp) only
    //     setPosition is semantically meaningful here, it is declared at
    //     PositionableObject.h:21, and counting the CSceneNodeObject overrides
    //     puts it at slot 11.  Arity [A], target [B].
    m_pPositionableObject->setPosition(-0.5f * fScale, 0.0f, 0.0f);

    // [A] Vtable slot 10: %rdi = this, %esi = 0, no memory argument, so
    //     setVisible(bool) - CSceneNodeObject.h:28.
    m_pPositionableObject->setVisible(false);

    // ------------------------------------------------------------------
    // [A] Imagesets.  "GuiLook" is fetched and the result is deliberately
    //     thrown away: the very next instruction destroys the CEGUI::String
    //     argument and %rax is never stored anywhere.  Reproduced because the
    //     call has an observable side effect - it forces the imageset to load.
    // ------------------------------------------------------------------
    CEGUI::ImagesetManager::getSingleton().getImageset("GuiLook");

    // [A] "UIIcons" -> m_pImageset (+0x3440).
    m_pImageset = CEGUI::ImagesetManager::getSingleton().getImageset("UIIcons");

    // ------------------------------------------------------------------
    // [A] The merchant sheet frame.
    //     type  = "DefaultWindow"  (fresh temporary at 0x3740)
    //     name  = "MerchantSheet"  (rodata 0xfeffb6)
    //     class = ""              (grow(0) temporary at 0x35e0)
    //     -> m_pUnknown20 (+0x20).
    // ------------------------------------------------------------------
    m_pUnknown20 = CEGUI::WindowManager::getSingleton().createWindow(
        "DefaultWindow", "MerchantSheet", "");

    // [A] UDim is {float d_scale, d_offset} (CEGUIUDim.h:70), so the dword
    //     pairs at 0x3b70 and 0x3b78 are (1.0f, 0.0f) each - not (0, 1.0f).
    m_pUnknown20->setSize(CEGUI::UVector2(CEGUI::UDim(1.0f, 0.0f),
                                          CEGUI::UDim(1.0f, 0.0f)));

    // [A] PropertySet::setProperty(name, value): the VALUE String (0x3480)
    //     goes in %rdx and the NAME String (0x3530) in %rsi.
    m_pUnknown20->setProperty("RiseOnClick", "False");

    // [A] Four zero dwords -> UDim(0,0) twice -> UVector2(0,0).
    m_pUnknown20->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f, 0.0f),
                                              CEGUI::UDim(0.0f, 0.0f)));

    // [A] `movb $0x1,0x3e2(%rax)` == CEGUI::Window::d_mousePassThroughEnabled,
    //     written through the inline setter at CEGUIWindow.h:2562.
    m_pUnknown20->setMousePassThroughEnabled(true);

    // [A] Out-of-line call this time: setZOrderingEnabled(false).
    m_pUnknown20->setZOrderingEnabled(false);

    // ------------------------------------------------------------------
    // [A] Subscribe the sheet to one event.  The subscriber is built by
    //     CEGUI::SubscriberSlot(bool (T::*)(const EventArgs&), T*)
    //     (CEGUISubscriberSlot.h:106), which heap-allocates a 32-byte
    //     CEGUI::MemberFunctionSlot<CMerchantMenu>.  Per abi_probe.s a member
    //     pointer is 16 bytes, so the four stores are:
    //         +0x00 vptr 0xff0270
    //         +0x08 member-function pointer, word 0 = 0xb61090
    //         +0x10 member-function pointer, word 1 = 0   (non-virtual => no adj)
    //         +0x18 owner = this
    //     The 8-byte SubscriberSlot temporary is passed BY VALUE, and per the
    //     probe GCC 4.4.7 lowers that to "address of a stack temporary in a
    //     register" - exactly the `lea 0x3e40(%rsp),%r12; mov %r12,%rcx` pair.
    //     The callback is 0xb61090 == CMerchantMenu::handle_MouseThrough.
    //     EventSet::subscribeEvent returns a 16-byte
    //     RefCounted<BoundSlot> (d_object + d_count) through the sret slot at
    //     0x3b50 and it is released again immediately, which is why the
    //     refcount decrement and both `operator delete` calls are in scope.
    // ------------------------------------------------------------------
    {
        CEGUI::Event::Connection conn = m_pUnknown20->subscribeEvent(
            CEGUI::Window::EventMouseMove,             // 0x1424020 [A] symbol
            CEGUI::SubscriberSlot(&CMerchantMenu::handle_MouseThrough, this));
        (void)conn;
    }

    // ------------------------------------------------------------------
    // [A] Resolve the merchant layout path and load it.
    //
    //     The std::wstring at 0x3e30 is built by the out-of-line
    //     basic_string(wchar_t const*, allocator const&) from the wide literal
    //     at 0xff0080 = L"media/ui/merchantmenu.layout".
    //
    //     The object at 0x3950 is a default-constructed CFileInfo.  Its layout
    //     is directly readable in the listing, which is what proves the
    //     8-byte std::string: m_sModName at +0 (one rep-pointer store),
    //     m_sResourceName at +8 (copy of EMPTY_STRING at 0x14c7380),
    //     m_sPath at +0x10 (copy of EMPTY_WSTRING at 0x14c7388),
    //     m_eFormat = 4 (FILE_FORMAT_UNKNOWN), m_eLocation = 3
    //     (FILE_LOCATION_NONE), m_sResourceGroup at +0x20, m_bExists = false.
    //     That is CFileInfo's own initialiser list from FileSystem.h; nothing
    //     is written by hand.
    //
    //     getFileInfo() therefore RESOLVES the path into
    //     m_sResourceName, and that resolved name is what is handed to
    //     loadWindowLayout().  b6f974 reloads m_sResourceName's data pointer
    //     and reads the length at `_M_p - 0x18`, so the CEGUI::String is built
    //     from the RESOLVED name, not from the literal.  The call's effect is
    //     load bearing and must not be deleted as dead code.
    //
    //     b6f95b..b6f96e is the EH type check on the CFileInfo, and control
    //     then falls straight into the CEGUI::String construction: neither
    //     getFileInfo's void return nor m_bExists is ever tested.
    // ------------------------------------------------------------------
    {
        std::wstring layoutProbePath(L"media/ui/merchantmenu.layout");

        CFileInfo fileInfo;
        CFileSystem::getSingleton()->getFileInfo(
            layoutProbePath,
            fileInfo,
            false,   // rcx = 0   bCompiled
            true,    // r8  = 1   bBinary
            false);  // r9  = 0   bModsOnly

        CEGUI::String layoutName(fileInfo.m_sResourceName.c_str());

        // [A] %r15 keeps the root for the rest of the function.
        CEGUI::Window* layoutRoot =
            CEGUI::WindowManager::getSingleton().loadWindowLayout(layoutName, true);

        // [A] Three post-load passes on the same root, each argument reloaded
        //     from memory rather than cached.
        m_pGameUI->convertToScreenScale(layoutRoot, false);
        m_pGameUI->mapToFunctions(layoutRoot);
        mapEventHandlers(layoutRoot);

        // ------------------------------------------------------------------
        // [A] "Blocker" is re-parented onto the sheet.  The receiver of
        //     removeChildWindow is the found window's CURRENT parent
        //     (CEGUI::Window::getParent(), the inline at CEGUIWindow.h:858,
        //     reading d_parent at +0xb0), read fresh for the remove and never
        //     reused.  This is the ONLY frame that gets moveToBack().
        // ------------------------------------------------------------------
        {
            CEGUI::String blockerName("Blocker");   // rodata 0xfe4a28, 7 chars
            CEGUI::Window* blocker =
                layoutRoot->recursiveChildSearch(blockerName);

            blocker->getParent()->removeChildWindow(blocker);
            m_pUnknown20->addChildWindow(blocker);

            blocker->setProperty("RiseOnClick", "False");
            blocker->moveToBack();
            blocker->setZOrderingEnabled(false);
        }

        // ------------------------------------------------------------------
        // [A] "BottomFrame" -> m_pUnknown40 (+0x40), same re-parenting, then
        //     RiseOnClick=False, moveToFront(), setZOrderingEnabled(false).
        // ------------------------------------------------------------------
        {
            CEGUI::String bottomName("BottomFrame");  // rodata 0xfef81a, 11 chars
            m_pUnknown40 = layoutRoot->recursiveChildSearch(bottomName);

            m_pUnknown40->getParent()->removeChildWindow(m_pUnknown40);
            m_pUnknown20->addChildWindow(m_pUnknown40);

            m_pUnknown40->setProperty("RiseOnClick", "False");
            m_pUnknown40->moveToFront();
            m_pUnknown40->setZOrderingEnabled(false);
        }

        // ------------------------------------------------------------------
        // [A] "TopFrame" -> m_pUnknown28 (+0x28), same treatment.  This is
        //     the search root for every later panel lookup and the parent of
        //     MSocketsO.
        // ------------------------------------------------------------------
        {
            CEGUI::String topName("TopFrame");      // rodata 0xfef811, 8 chars
            m_pUnknown28 = layoutRoot->recursiveChildSearch(topName);

            m_pUnknown28->getParent()->removeChildWindow(m_pUnknown28);
            m_pUnknown20->addChildWindow(m_pUnknown28);

            m_pUnknown28->setProperty("RiseOnClick", "False");
            m_pUnknown28->moveToFront();
            m_pUnknown28->setZOrderingEnabled(false);
        }
    }

    // ------------------------------------------------------------------
    // [A] MSocketsO.  Type "DefaultWindow" (fresh CEGUI::String at 0x2980),
    //     name "MSocketsO" (rodata 0xfeffcd), class "" (0x2820)
    //     -> m_pUnknown38 (+0x38).
    //     +0x38 is ALSO the CEGUI::EventSet base offset inside a Window, which
    //     is why later code does `lea 0x38(win),%rdi` before setMutedState()
    //     and before the virtual subscribeEvent dispatch.
    // ------------------------------------------------------------------
    // Original b703bc..b7060b: separate MSockets at +0x30, before MSocketsO.
    m_pSocketedIconParent = CEGUI::WindowManager::getSingleton().createWindow(
        "DefaultWindow", "MSockets", "");
    m_pUnknown28->addChildWindow(m_pSocketedIconParent);
    m_pSocketedIconParent->setSize(m_pUnknown28->getSize());
    m_pSocketedIconParent->setProperty("RiseOnClick", "False");
    m_pSocketedIconParent->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f, 0.0f),
                                                      CEGUI::UDim(0.0f, 0.0f)));
    m_pSocketedIconParent->setMousePassThroughEnabled(true);
    m_pSocketedIconParent->moveToFront();

    m_pUnknown38 = CEGUI::WindowManager::getSingleton().createWindow(
        "DefaultWindow", "MSocketsO", "");

    m_pUnknown28->addChildWindow(m_pUnknown38);

    // [A] Size copied from the TopFrame, not from a constant.
    m_pUnknown38->setSize(m_pUnknown28->getSize());

    m_pUnknown38->setProperty("RiseOnClick", "False");
    m_pUnknown38->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f, 0.0f),
                                             CEGUI::UDim(0.0f, 0.0f)));
    m_pUnknown38->setMousePassThroughEnabled(true);
    m_pUnknown38->moveToFront();

    // ------------------------------------------------------------------
    // [A] The per-slot "SlotGlow" window under the TopFrame is cached in
    //     m_pUnknown3448 (+0x3448), muted, flagged, z-order cleared and
    //     detached from its parent.  setMutedState is an out-of-line
    //     CEGUI::EventSet call with `this` = win + 0x38.
    // ------------------------------------------------------------------
    {
        CEGUI::String glowName("SlotGlow");    // rodata 0xfef808, 8 chars
        m_pUnknown3448 = m_pUnknown28->recursiveChildSearch(glowName);

        m_pUnknown3448->setMutedState(true);
        m_pUnknown3448->setMousePassThroughEnabled(true);
        m_pUnknown3448->setRiseOnClickEnabled(false);
        m_pUnknown3448->getParent()->removeChildWindow(m_pUnknown3448);
    }

    // ------------------------------------------------------------------
    // [A] The Close button: a plain local, not a member.  Found under the
    //     TopFrame, z-order cleared BEFORE moveToFront, then subscribed to
    //     the same event constant the item and pet-item slots use.
    // ------------------------------------------------------------------
    {
        CEGUI::String closeName("Close");      // rodata 0xfef802, 5 chars
        CEGUI::Window* closeButton =
            m_pUnknown28->recursiveChildSearch(closeName);

        closeButton->setRiseOnClickEnabled(false);
        closeButton->moveToFront();

        CEGUI::Event::Connection conn = closeButton->subscribeEvent(
            CEGUI::Window::EventMouseButtonDown,   // 0x14247e0 [A] symbol
            CEGUI::SubscriberSlot(&CMerchantMenu::handle_CloseButton, this));
        (void)conn;
    }

    // ------------------------------------------------------------------
    // [A] Slot-data table priming.  A real counted loop, not a memset:
    //       b70e55  xor %eax,%eax
    //       b70e60  mov %eax,0xb0(%rdx)     base this+0xb0, stride 4
    //       b70e6d  cmp $0x190,%eax         == 400
    //       b70e72  jne b70e60
    //     `this` is spilled to 0x38(%rsp) first and reloaded by the loop, so
    //     the base pointer is not cached across the stores.  400 is the only
    //     proven bound on the extent.
    // ------------------------------------------------------------------
    {
        CMerchantMenu* pThis = this;
        for (int i = 0; i < 400; ++i)
            pThis->m_aiSlotData[i] = i;
    }

    // ------------------------------------------------------------------
    // [A] Six named panels of the TopFrame (+0x28).  Search order and
    //     destinations straight out of the listing:
    //       "TabMisc"   -> +0x3420 [11]   "SlotsMisc"    -> +0x3408 [8]
    //       "TabWeapon" -> +0x3410 [9]    "SlotsWeapons" -> +0x33f8 [6]
    //       "TabArmor"  -> +0x3418 [10]   "SlotsArmor"   -> +0x3400 [7]
    //     then three setZOrderingEnabled(false) in the order +0x3420, +0x3410,
    //     +0x3418 (b7112d..b71152), then setVisible(false) on +0x33f8
    //     (b7132c) and on +0x3400 (b71424).  Each member is stored immediately
    //     after its own search, and SlotsWeapons/SlotsArmor are hidden right
    //     after being found - the interleaving is reproduced.
    // ------------------------------------------------------------------
    {
        CEGUI::String nameTabMisc("TabMisc");            // rodata 0xfeffae, 7
        CEGUI::Window* tabMisc = m_pUnknown28->recursiveChildSearch(nameTabMisc);
        m_pUnknown33C8[11] = tabMisc;

        CEGUI::String nameTabWeapon("TabWeapon");        // rodata 0xfeffa4, 9
        CEGUI::Window* tabWeapon = m_pUnknown28->recursiveChildSearch(nameTabWeapon);
        m_pUnknown33C8[9] = tabWeapon;

        CEGUI::String nameTabArmor("TabArmor");          // rodata 0xfeff9b, 8
        CEGUI::Window* tabArmor = m_pUnknown28->recursiveChildSearch(nameTabArmor);
        m_pUnknown33C8[10] = tabArmor;

        tabMisc->setZOrderingEnabled(false);
        tabWeapon->setZOrderingEnabled(false);
        tabArmor->setZOrderingEnabled(false);

        CEGUI::String nameSlotsMisc("SlotsMisc");        // rodata 0xfeff91, 9
        CEGUI::Window* slotsMisc = m_pUnknown28->recursiveChildSearch(nameSlotsMisc);
        m_pUnknown33C8[8] = slotsMisc;

        CEGUI::String nameSlotsWeapons("SlotsWeapons");  // rodata 0xfeff84, 12
        CEGUI::Window* slotsWeapons =
            m_pUnknown28->recursiveChildSearch(nameSlotsWeapons);
        m_pUnknown33C8[6] = slotsWeapons;
        slotsWeapons->setVisible(false);

        CEGUI::String nameSlotsArmor("SlotsArmor");      // rodata 0xfeff79, 10
        CEGUI::Window* slotsArmor =
            m_pUnknown28->recursiveChildSearch(nameSlotsArmor);
        m_pUnknown33C8[7] = slotsArmor;
        slotsArmor->setVisible(false);
    }

    // ------------------------------------------------------------------
    // [A] The item-slot loop.  126 iterations.
    //       b71446  movl $0x1,0x24(%rsp)        i = 1
    //       b715e5  lea 0xb0(%rbx,%r13,4),%rax  r13 = i + 0x12
    //       b73271  addl $0x1,0x24(%rsp)        ++i
    //       b73276  add $0x8,%rbp               ++array cursor
    //       b7327a  cmpl $0x7f,0x24(%rsp)       while (i != 127)
    //       b7327f  jne  b71464
    //     The five arrays written per iteration all start at their own base
    //     + 8*(i-1):
    //       +0x1e80  the slot window itself             (m_pUnknown1E80)
    //       +0x2308  item-name StaticText              (m_pUnknown2308)
    //       +0x1570  overlay A, child of slot's parent (m_pUnknown1570)
    //       +0x19f8  overlay B, child of MSocketsO     (m_pUnknown19F8)
    //       +0x10e8  overlay C, child of slot's parent, always-on-top
    //                                                    (m_pUnknown10E8)
    //     i+18 is the slot-data index handed to setUserData, so the user-data
    //     pointers run 19..144 - inside the 0..399 table primed above.
    //     The name is "Slot" + STRINGS::GetValueAsString(i): the literal is on
    //     the LEFT (b71493 is std::operator+<char>(const char*, const
    //     string&)), and the CEGUI::String is then widened byte by byte.
    // ------------------------------------------------------------------
    for (int i = 1; i != 127; ++i)
    {
        const int idx = i - 1;   // the running 8-byte array cursor / 8

        std::string slotName =
            std::string("Slot") + STRINGS::GetValueAsString(i);
        CEGUI::String slotNameCegui(slotName.c_str());

        CEGUI::Window* slot = m_pUnknown28->recursiveChildSearch(slotNameCegui);

        slot->moveToFront();
        slot->setRiseOnClickEnabled(false);
        slot->setWantsMultiClickEvents(false);

        // [A] setUserData() is inline at CEGUIWindow.h:1809 and compiles to the
        //     single `mov %rax,0x1d8(%r14)` store at b715ed - which is what
        //     pins CEGUI::Window::d_userData at +0x1d8.
        slot->setUserData(&m_aiSlotData[i + 18]);

        // [A] Four subscriptions, in this exact order, each building a fresh
        //     32-byte CEGUI::MemberFunctionSlot and immediately releasing the
        //     returned Connection:
        //       0x14247e0 -> handle_ItemClick
        //       0x1423b80 -> handle_MouseOver
        //       0x1424020 -> handle_MouseOver
        //       0x1423700 -> handle_MouseOut
        //     handle_MouseOver is registered TWICE, for two DIFFERENT events.
        //     They must not be merged into one subscription.
        {
            slot->subscribeEvent(
                CEGUI::Window::EventMouseButtonDown,  // 0x14247e0
                CEGUI::SubscriberSlot(&CMerchantMenu::handle_ItemClick, this));
            slot->subscribeEvent(
                CEGUI::Window::EventMouseEnters,     // 0x1423b80
                CEGUI::SubscriberSlot(&CMerchantMenu::handle_MouseOver, this));
            slot->subscribeEvent(
                CEGUI::Window::EventMouseMove,       // 0x1424020
                CEGUI::SubscriberSlot(&CMerchantMenu::handle_MouseOver, this));
            slot->subscribeEvent(
                CEGUI::Window::EventMouseLeaves,     // 0x1423700
                CEGUI::SubscriberSlot(&CMerchantMenu::handle_MouseOut, this));

        }

        m_pSocketedSizeWindows[idx + 19] = slot;

        // --------------------------------------------------------------
        // [A] Item-name label: "GuiLook/StaticText" (rodata 0xfe4872) with a
        //     generated name from STRINGS::uniqueName(std::string("gui_"))
        //     (rodata 0xfe468a) and an empty class string.
        //     setFont("Serif")                     rodata 0xfe4944, 5 chars
        //     setSize(slot->getSize())             getSize() returns
        //                                            UVector2 by value
        //     getPosition() returns const UVector2&, and its two dwords are
        //        COPIED to 0x3a20/0x3a28 and reused by the second
        //        setPosition() below - fetched exactly once
        //     setProperty("RightAligned", "HorzTextFormatting") 0xfe6021/0xfe48bd
        //     setProperty("TopAligned",   "VertFormatting")     0xfe4895/0xfe48a0
        //     setMousePassThroughEnabled(true)
        //     setPosition(cachedPosition)
        //     slot->getParent()->addChildWindow(label)
        //     setText("")                        grow(0) temporary at 0x1a60
        //     setProperty("TextColour", PropertyHelper::colourToString(
        //         colour(1.0f, 1.0f, 1.0f, 1.0f)))
        //         0xfa47fc holds 0x3f800000 and movaps replicates it into
        //         xmm0..xmm3 - four 1.0f arguments, opaque white.
        //     setAlwaysOnTop(true)
        // --------------------------------------------------------------
        CEGUI::Window* label = NULL;
        {
            std::string autoBase("gui_");
            CEGUI::String  autoName(STRINGS::uniqueName(autoBase).c_str());
            label = CEGUI::WindowManager::getSingleton().createWindow(
                "GuiLook/StaticText", autoName, "");
        }

        // [A] Member filled in IMMEDIATELY after the createWindow() return
        //     (b71cd7), before any configuration.
        m_pUnknown2308[idx] = label;

        CEGUI::String fontName("Serif");
        label->setFont(fontName);

        label->setSize(slot->getSize());

        CEGUI::UVector2 labelPos = slot->getPosition();
        label->setProperty("HorzTextFormatting", "RightAligned");
        label->setProperty("VertFormatting", "TopAligned");
        label->setMousePassThroughEnabled(true);
        label->setPosition(labelPos);

        slot->getParent()->addChildWindow(label);
        label->setText(CEGUI::String(""));

        CEGUI::String textColourName("TextColour");     // rodata 0xfe4654, 10
        CEGUI::String textColourValue(
            CEGUI::PropertyHelper::colourToString(
                CEGUI::colour(1.0f, 1.0f, 1.0f, 1.0f)));
        label->setProperty(textColourName, textColourValue);
        label->setAlwaysOnTop(true);

        // --------------------------------------------------------------
        // [A] Overlay A: "GuiLook/StaticImage" (rodata 0xfd0bff),
        //     uniqueName("gui_"), empty class.  Added to the slot's PARENT,
        //     not to the slot; rise-on-click cleared, multi-click off,
        //     mouse-pass-through on, EventSet muted, then position and size
        //     copied from the slot (getPosition()/getSize() re-fetched here,
        //     NOT reused from the label's copy).
        // --------------------------------------------------------------
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
        m_pUnknown1570[idx] = overlayA;

        // --------------------------------------------------------------
        // [A] Overlay B: identical except that it is added to m_pUnknown38
        //     (the MSocketsO window) instead of the slot's parent.  This is
        //     the layer that lines the socket overlays up with the socket
        //     window rather than with the inventory.
        // --------------------------------------------------------------
        CEGUI::Window* overlayB = NULL;
        {
            std::string autoBase("gui_");
            CEGUI::String  autoName(STRINGS::uniqueName(autoBase).c_str());
            overlayB = CEGUI::WindowManager::getSingleton().createWindow(
                "GuiLook/StaticImage", autoName, "");
        }

        m_pUnknown38->addChildWindow(overlayB);
        overlayB->setRiseOnClickEnabled(false);
        overlayB->setWantsMultiClickEvents(false);
        overlayB->setMousePassThroughEnabled(true);
        overlayB->setMutedState(true);
        overlayB->setPosition(slot->getPosition());
        overlayB->setSize(slot->getSize());
        m_pUnknown19F8[idx] = overlayB;

        // --------------------------------------------------------------
        // [A] Overlay C: same as A, plus setAlwaysOnTop(true) last.  This is
        //     the drag / selection highlight layer.
        // --------------------------------------------------------------
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
        m_pUnknown10E8[idx] = overlayC;
    }

    // ------------------------------------------------------------------
    // [A] Six more panels, all under the BottomFrame (+0x40):
    //       "TabBackpack"       -> +0x33e0 [3]
    //       "TabSpell"          -> +0x33e8 [4]
    //       "TabFish"           -> +0x33f0 [5]
    //       "PetSlotsEquipment" -> +0x33c8 [0]
    //       "PetSlotsSpells"    -> +0x33d0 [1] then setVisible(false)
    //       "PetSlotsFish"      -> +0x33d8 [2] then setVisible(false)
    //     with three setZOrderingEnabled(false) in between, in the order
    //     +0x33e0, +0x33e8, +0x33f0 (b73531, b7353f, b7354d).
    //     With the previous block this fills m_pUnknown33C8[0..11] exactly.
    // ------------------------------------------------------------------
    {
        CEGUI::String nameTabBackpack("TabBackpack");        // 0xfef7d0, 11
        CEGUI::Window* tabBackpack =
            m_pUnknown40->recursiveChildSearch(nameTabBackpack);
        m_pUnknown33C8[3] = tabBackpack;

        CEGUI::String nameTabSpell("TabSpell");              // 0xfef7c7, 8
        CEGUI::Window* tabSpell =
            m_pUnknown40->recursiveChildSearch(nameTabSpell);
        m_pUnknown33C8[4] = tabSpell;

        CEGUI::String nameTabFish("TabFish");                // 0xfef7bf, 7
        CEGUI::Window* tabFish =
            m_pUnknown40->recursiveChildSearch(nameTabFish);
        m_pUnknown33C8[5] = tabFish;

        tabBackpack->setZOrderingEnabled(false);
        tabSpell->setZOrderingEnabled(false);
        tabFish->setZOrderingEnabled(false);

        CEGUI::String namePetEquipment("PetSlotsEquipment"); // 0xfeff67, 17
        CEGUI::Window* petEquipment =
            m_pUnknown40->recursiveChildSearch(namePetEquipment);
        m_pUnknown33C8[0] = petEquipment;

        CEGUI::String namePetSpells("PetSlotsSpells");       // 0xfeff58, 14
        CEGUI::Window* petSpells =
            m_pUnknown40->recursiveChildSearch(namePetSpells);
        m_pUnknown33C8[1] = petSpells;
        petSpells->setVisible(false);

        CEGUI::String namePetFish("PetSlotsFish");           // 0xfeff4b, 12
        CEGUI::Window* petFish =
            m_pUnknown40->recursiveChildSearch(namePetFish);
        m_pUnknown33C8[2] = petFish;
        petFish->setVisible(false);
    }

    // ------------------------------------------------------------------
    // [A] The pet-slot loop.  63 iterations.
    //       b73829  movl $0x1,0x24(%rsp)   i = 1
    //       b75b6f  addl $0x1,0x24(%rsp)   ++i
    //       b75b74  add $0x8,%rdx         ++array cursor
    //       b75b78  cmpl $0x40,0x24(%rsp)  while (i != 64)
    //       b75b7d  mov %rdx,0x38(%rsp)    cursor spilled to memory
    //       b75b82  jne  b7384c
    //     The cursor is a stack slot rather than a register, which is why
    //     every array access below reloads it.  It starts at `this` (b70e55
    //     stores %rbx to 0x38(%rsp)) and the first access is +0x2790.
    //     0x2790 - 19*8 == 0x26f8, so the first touched element is element 19
    //     of the 82-entry array at +0x26f8, and 19 + 63 == 82.  Same
    //     arithmetic for the other four bases:
    //       +0x2790 -> m_pSlotWindows[19..81]
    //       +0x31d0 -> m_pStackWindows[19..81]
    //       +0x2cb0 -> m_pSlotGlowWindows[19..81]
    //       +0x2f40 -> m_pSocketGlowWindows[19..81]
    //       +0x2a20 -> m_pUnidentifiedWindows[19..81]
    //     Elements 0..18 of all five are NOT written by createMenus(); they
    //     belong to setPetSlotIcon.  See UNRESOLVED.md #7 for the
    //     socket-count versus inserted-item-list-size distinction.
    //
    //     Differences from the item loop, all read off the listing:
    //       * prefix "PetSlot" (rodata 0xfeffd7), not "Slot";
    //       * search root is the BottomFrame (+0x40), not the TopFrame;
    //       * the label uses VertFormatting "BottomAligned" (0xfe6013, 13)
    //         where the item loop used "TopAligned" (0xfe4895, 10);
    //       * callbacks handle_PetItemClick / handle_PetMouseOver /
    //         handle_PetMouseOut;
    //       * overlay B is parented to m_pUnknown38, overlay C to the slot's
    //         parent, and only overlay C gets always-on-top.
    // ------------------------------------------------------------------
    for (int i = 1; i != 64; ++i)
    {
        const int idx = 19 + (i - 1);   // cursor/8, biased by 19 elements

        std::string petSlotName =
            std::string("PetSlot") + STRINGS::GetValueAsString(i);
        CEGUI::String petSlotNameCegui(petSlotName.c_str());

        CEGUI::Window* slot =
            m_pUnknown40->recursiveChildSearch(petSlotNameCegui);

        slot->moveToFront();
        slot->setRiseOnClickEnabled(false);
        slot->setWantsMultiClickEvents(false);
        slot->setUserData(&m_aiSlotData[i + 18]);

        {
            slot->subscribeEvent(
                CEGUI::Window::EventMouseButtonDown,  // 0x14247e0
                CEGUI::SubscriberSlot(&CMerchantMenu::handle_PetItemClick, this));
            slot->subscribeEvent(
                CEGUI::Window::EventMouseEnters,     // 0x1423b80
                CEGUI::SubscriberSlot(&CMerchantMenu::handle_PetMouseOver, this));
            slot->subscribeEvent(
                CEGUI::Window::EventMouseMove,       // 0x1424020
                CEGUI::SubscriberSlot(&CMerchantMenu::handle_PetMouseOver, this));
            slot->subscribeEvent(
                CEGUI::Window::EventMouseLeaves,     // 0x1423700
                CEGUI::SubscriberSlot(&CMerchantMenu::handle_PetMouseOut, this));

        }

        m_pSlotWindows[idx] = slot;                 // cursor + 0x2790

        // --------------------------------------------------------------
        // [A] Pet item-name label - same construction as the item loop.
        // --------------------------------------------------------------
        CEGUI::Window* label = NULL;
        {
            std::string autoBase("gui_");
            CEGUI::String  autoName(STRINGS::uniqueName(autoBase).c_str());
            label = CEGUI::WindowManager::getSingleton().createWindow(
                "GuiLook/StaticText", autoName, "");
        }

        // [A] Filled in immediately after the createWindow() return (b747f9).
        m_pStackWindows[idx] = label;                // cursor + 0x31d0

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

        // --------------------------------------------------------------
        // [A] Overlay A: parented to the pet slot's parent.
        // --------------------------------------------------------------
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
        m_pSlotGlowWindows[idx] = overlayA;           // cursor + 0x2cb0

        // --------------------------------------------------------------
        // [A] Overlay B: parented to m_pUnknown38 (MSocketsO).
        // --------------------------------------------------------------
        CEGUI::Window* overlayB = NULL;
        {
            std::string autoBase("gui_");
            CEGUI::String  autoName(STRINGS::uniqueName(autoBase).c_str());
            overlayB = CEGUI::WindowManager::getSingleton().createWindow(
                "GuiLook/StaticImage", autoName, "");
        }

        m_pUnknown38->addChildWindow(overlayB);
        overlayB->setRiseOnClickEnabled(false);
        overlayB->setWantsMultiClickEvents(false);
        overlayB->setMousePassThroughEnabled(true);
        overlayB->setMutedState(true);
        overlayB->setPosition(slot->getPosition());
        overlayB->setSize(slot->getSize());
        m_pSocketGlowWindows[idx] = overlayB;         // cursor + 0x2f40

        // --------------------------------------------------------------
        // [A] Overlay C: parented to the pet slot's parent, always-on-top.
        // --------------------------------------------------------------
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
        m_pUnidentifiedWindows[idx] = overlayC;       // cursor + 0x2a20
    }

    // ------------------------------------------------------------------
    // [A] Epilogue (b75b88..b75c10).  Four cleanup blocks compare
    //     `_M_p - 0x18` of the four std::strings against the typeinfo addresses
    //     0x1423a20 / 0x1424540 (exception unwinding), then
    //       mov 0x39a0(%rsp),%rdi ; test %rdi,%rdi ; je ;
    //       call Ogre::NedAllocImpl::deallocBytes
    //     0x39a0(%rsp) is initialised to 0 at b6ee94 and never written again on
    //     the normal path, so the branch is dead; it is the compiler-generated
    //     release of a raw allocation made by an inlined callee and has no
    //     source spelling.  See UNRESOLVED.md #8.
    //     No %rax setup precedes the pops: the return type is void.
    // ------------------------------------------------------------------
}


// ============================================================================
//  Required declarations that are NOT satisfied by input/project-headers/
//  are in output/other-class-additions.h, not here:
//    * CGameUI::convertToScreenScale(CEGUI::Window*, bool)   proven by 0xa83ed0
//    * CGameUI::mapToFunctions(CEGUI::Window*)               proven by 0xa980e0
//    * CSceneNodeObject::getEntity()                         offset +0x60 proven
//  MerchantMenu.h supplies everything that belongs to CMerchantMenu itself,
//  including the eight callback declarations the partial header omitted.
// ============================================================================