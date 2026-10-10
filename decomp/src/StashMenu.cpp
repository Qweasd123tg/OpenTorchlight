// -----------------------------------------------------------------------------
// CStashMenu::createMenus()  --  reconstructed candidate body, revision 2
//
// Target : _ZN10CStashMenu11createMenusEv  @ 0xbfbe20, 33050 bytes.
// Source language: original-style C++98, GCC 4.4.7, Linux x86-64.
//
// REVISION 2 corrects the proven errors listed in
// input/supervisor-verification/compile-first.log and
// input/supervisor-verification/REPAIR.md:
//
//   E1  KSETTINGS_RES_WIDTH / KSETTINGS_RES_HEIGHT / KSETTINGS_YRATIO were not
//       declared.  They are in input/project-headers/GameVariables.h:11-12
//       (`extern int`) and input/project-headers/Settings.h:11
//       (`extern unsigned int`).  Both headers are now included.
//   E2  CGenericModel was incomplete.  ResourceManager.h only forward-declares
//       it (line 12); input/project-headers/GenericModel.h defines it.  That is
//       now included.
//   E3  CGameUI had no convertToScreenScale / mapToFunctions.  Added to
//       output/GameUI.h (a superset of the input header; both are original
//       symbols at 0xa83ed0 / 0xa980e0).
//   E4  The event name at static-address 0x14247e0 is
//       CEGUI::Window::EventMouseButtonDown, not EventMouseClick.  Per
//       input/evidence-supplement/references.json (exact symbol).  Three call
//       sites affected.
//   E5  SDK Window +0x3e2 is d_mousePassThroughEnabled and +0x213 is
//       d_riseOnClick, per
//       input/supervisor-verification/sdk-layout-facts.json (d_mousePassThroughEnabled
//       at 994, d_riseOnClick at 531).  The previous revision had these two
//       swapped; every `movb` site is corrected.
//   E6  The wide literals are now known from references.json:
//       0xfeffe0 -> L"media/ui/models/merchant/merchant.mesh"
//       0xff15d0 -> L"media/ui/stashmenu.layout"
//       0x1001608 -> L""  (empty)
//   E7  0x14d2f60 / 0x14d2f68 are EMPTY_STRING / EMPTY_WSTRING, i.e. the
//       inlined CFileInfo() constructor, not extra assignments.  They are gone.
//   E8  getEntity() was an invented accessor.  CSceneNodeObject::m_pEntity is
//       an existing declaration; output/SceneNodeObject.h relaxes only its
//       access specifier (declaration order preserved).
//
// NOT CLAIMED: compilation, or equivalence.  The supervisor compiles.
// -----------------------------------------------------------------------------

#include "StashMenu.h"

#include "GenericModel.h"
#include "GameVariables.h"

#include <CEGUIEventArgs.h>
#include <CEGUIEventSet.h>
#include <CEGUIImageset.h>
#include <CEGUIImagesetManager.h>
#include <CEGUIPropertyHelper.h>
#include <CEGUIString.h>
#include <CEGUISubscriberSlot.h>
#include <CEGUIWindow.h>
#include <CEGUIWindowManager.h>

#include <OgreAxisAlignedBox.h>
#include <OgreEntity.h>
#include <OgreMesh.h>
#include <OgreVector3.h>

// -----------------------------------------------------------------------------
// [B] Loop bounds, recovered from the two loop tails:
//     item-socket loop : 0x24(%rsp) set to 1, `add $1` / `cmp $0x2b`
//                        -> the body runs for i = 1 .. 42
//     pet-socket loop  : `add $1` / `cmp $0x40`  -> the body runs for i = 1 .. 63
//   These are two different numbers.  Neither is a socket count and neither is
//   an inserted-item list size; createMenus writes no count field at all.
// -----------------------------------------------------------------------------
static const int STASH_ITEM_SOCKET_COUNT = 43;   // loop runs i = 1 .. 42
static const int STASH_PET_SOCKET_COUNT  = 64;   // loop runs i = 1 .. 63

// [A] Both loops form `this + 0xb0 + (i + 0x12) * 4` (bfe135, c00504) and store
//     that address in the window's d_userData.  The +18 bias means the first 19
//     ints of m_aiSlotData belong to something else and are not claimed here;
//     the item loop owns 19..60 and the pet loop owns 19..81.
static const int STASH_SLOTDATA_BIAS = 18;

// -----------------------------------------------------------------------------
void CStashMenu::createMenus()
{
    // --- screen metrics ------------------------------------------------------
    // [A] GetInt returns int; `cvtsi2ss` at bfbe43/bfbe5c is the int->float
    //     narrowing and is kept.  %rbx is the permanent `this`, and the listing
    //     reloads 0x68(%rbx) before each call, so no pointer is cached.
    const float fScreenWidth  =
        (float)m_pDynamicPropertyFile->GetInt(KSETTINGS_RES_WIDTH);
    const float fScreenHeight =
        (float)m_pDynamicPropertyFile->GetInt(KSETTINGS_RES_HEIGHT);

    // --- the merchant backdrop model ----------------------------------------
    // [A] createGenericModel(this+0x98, this+0x78, <w1>, <w2>, 0, 0, 0);
    //     result stored at this+0x90.
    // [A] w1 = 0xfeffe0, w2 = 0x1001608; both decoded from
    //     input/evidence-supplement/references.json (E6).
    m_pUnknown90 = m_pResourceManager->createGenericModel(
        m_pUnknown78, L"media/ui/models/merchant/merchant.mesh", L"",
        false, false, false);

    // [A] The AxisAlignedBox is built inline on the stack at 0x3560(%rsp):
    //     three 0xc7c35000 (-100000.0f) then three 0x47c35000 (+100000.0f).
    // [A] The receiver is `0x60(%rax)`, the CSceneNodeObject::m_pEntity member
    //     reached by a direct load, not through a getter (E8).
    // [A] The Mesh* is then taken from `*(void**)(rax + 8)` after the call the
    //     listing labels `Ogre::Entity::getMesh() const`; see UNRESOLVED 1.
    m_pUnknown90->getEntity()->getMesh()->_setBounds(
        Ogre::AxisAlignedBox(Ogre::Vector3(-100000.0f, -100000.0f, -100000.0f),
                             Ogre::Vector3( 100000.0f,  100000.0f,  100000.0f)),
        true);

    // [A] three floats in, three floats out.  The constants are 0x3f400000
    //     (0.75) at 0xfc6774 and 0xbf000000 (-0.5) at 0xfa86f4.
    //     Vtable slot 11 of CGenericModel, which is
    //     CPositionableObject::setPosition(float,float,float): slot 10 is
    //     CSceneNodeObject::setVisible(bool) and slot 11 is the next new virtual,
    //     because CEditorBaseObject contributes slots 2..7 and
    //     CSceneNodeObject overrides 2 and 5 rather than adding slots.
    m_pUnknown90->setPosition(
        -0.5f * ((fScreenWidth - fScreenHeight / 0.75f)
                 / m_pDynamicPropertyFile->GetFloat(KSETTINGS_YRATIO)),
        0.0f, 0.0f);
    m_pUnknown90->setVisible(false);

    // --- force both imagesets to load ---------------------------------------
    // [A] The "GuiLook" lookup result is dead: nothing between bfc141 and bfc149
    //     reads %rax.  The call is kept because it loads the imageset.
    // [A] The "UIIcons" lookup result is stored at this+0x3410.
    CEGUI::ImagesetManager::getSingleton().getImageset("GuiLook");
    m_pUnknown3410 = CEGUI::ImagesetManager::getSingleton().getImageset("UIIcons");

    // --- the top-level sheet -------------------------------------------------
    // [A] createWindow(type="DefaultWindow", name="StashSheet", prefix="")
    //     stored at this+0x20.  The third String is the empty *prefix*
    //     (CEGUIWindowManager.h:138), built with grow(0) and a NUL write.
    m_pUnknown20 = CEGUI::WindowManager::getSingleton().createWindow(
        "DefaultWindow", "StashSheet", "");

    // [A] UVector2{ UDim(1.0f,0.0f), UDim(1.0f,0.0f) } on the stack at 0x3750.
    m_pUnknown20->setSize(CEGUI::UVector2(CEGUI::UDim(1.0f, 0.0f),
                                          CEGUI::UDim(1.0f, 0.0f)));

    // [A] setProperty("RiseOnClick","False") -- the property path, not the
    //     setter.  The original uses the property everywhere, never the setter,
    //     for this one flag.
    m_pUnknown20->setProperty("RiseOnClick", "False");

    // [A] UVector2{ UDim(0,0), UDim(0,0) } at 0x3740 (four zero floats).
    m_pUnknown20->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f, 0.0f),
                                              CEGUI::UDim(0.0f, 0.0f)));

    // [A] `movb $0x1,0x3e2(%rax)` is the inlined body of
    //     Window::setMousePassThroughEnabled(true) (CEGUIWindow.h:2562);
    //     d_mousePassThroughEnabled is at 994 == 0x3e2 in the pinned header.
    m_pUnknown20->setMousePassThroughEnabled(true);
    m_pUnknown20->setZOrderingEnabled(false);

    // [A] one subscription on the sheet, for handle_MouseThrough, with the
    //     static CEGUI::Window::EventMouseMove at 0x1424020.
    //     The Event::Connection (== RefCounted<BoundSlot>) that subscribeEvent
    //     returns is released immediately, which is why the original ends each
    //     block with a ~SharedPtr and a ~SubscriberSlot.  Releasing is not
    //     disconnecting: the Event holds its own reference, so the subscription
    //     survives.  The by-value SubscriberSlot is passed indirectly (RDX
    //     holds &name, RCX the address of the stack temporary), which
    //     input/supervisor-verification/ABI_RESULTS.md confirms is normal
    //     GCC 4.4.7 behaviour for a nontrivial by-value class.
    m_pUnknown20->subscribeEvent(
        CEGUI::Window::EventMouseMove,
        CEGUI::SubscriberSlot(&CStashMenu::handle_MouseThrough, this));

    // --- locate the layout through the file system --------------------------
    // [A] CFileInfo at 0x3530(%rsp)..0x3560(%rsp); its layout matches
    //     input/project-headers/FileSystem.h exactly:
    //       +0x00 m_sModName, +0x08 m_sResourceName, +0x10 m_sPath,
    //       +0x18 m_eFormat, +0x1c m_eLocation, +0x20 m_sResourceGroup,
    //       +0x28 m_bExists.
    // [A] The two copy-ctor calls at bfc9d6 / bfc9ec take EMPTY_STRING
    //     (0x14d2f60) and EMPTY_WSTRING (0x14d2f68), and the stores of 4 and 3
    //     at bfc a06/bfca11 are FILE_FORMAT_UNKNOWN and FILE_LOCATION_NONE.
    //     All four are the inlined CFileInfo() constructor -- there are no extra
    //     assignments (E7).
    CFileInfo layoutFile;

    // [A] getFileInfo(L"media/ui/stashmenu.layout", layoutFile, false, true, false)
    CFileSystem::getSingleton()->getFileInfo(
        std::wstring(L"media/ui/stashmenu.layout"), layoutFile,
        false, true, false);

    // [A] The layout file name is the *narrow* m_sResourceName: the copy loop is
    //     `movzbl (%rdx,%r12,1),%edx ; mov %edx,(%rax,%r12,4)` -- one byte per
    //     code point, i.e. String(const char*), NOT the utf8 decoder.
    CEGUI::String layoutName(layoutFile.m_sResourceName.c_str());

    // [A] loadWindowLayout(layoutName, /*generateRandomPrefix=*/true); the
    //     result is a LOCAL -- it is never written to a member of this.
    CEGUI::Window* layout =
        CEGUI::WindowManager::getSingleton().loadWindowLayout(layoutName, true);

    // [A] the three registration passes on the freshly loaded layout, in order.
    m_pGameUI->convertToScreenScale(layout, false);
    m_pGameUI->mapToFunctions(layout);
    mapEventHandlers(layout);

    // --- re-parent the Blocker out of the layout and onto the sheet ---------
    // [A] recursiveChildSearch("Blocker") on the layout; the result stays in a
    //     local.  Contrast the four frames below, which ARE members.
    {
        CEGUI::Window* blocker = layout->recursiveChildSearch("Blocker");
        blocker->getParent()->removeChildWindow(blocker);
        m_pUnknown20->addChildWindow(blocker);
        blocker->setProperty("RiseOnClick", "False");
        blocker->moveToBack();
        blocker->setZOrderingEnabled(false);
    }

    // --- BottomFrame: member +0x40 ------------------------------------------
    // [A] searched in the layout, detached from its old parent, re-attached to
    //     m_pUnknown20.  Order: remove, add, property, front, z-ordering.
    m_pUnknown40 = layout->recursiveChildSearch("BottomFrame");
    m_pUnknown40->getParent()->removeChildWindow(m_pUnknown40);
    m_pUnknown20->addChildWindow(m_pUnknown40);
    m_pUnknown40->setProperty("RiseOnClick", "False");
    m_pUnknown40->moveToFront();
    m_pUnknown40->setZOrderingEnabled(false);

    // --- TopFrame: member +0x28 ---------------------------------------------
    // [A] identical shape to BottomFrame.
    m_pUnknown28 = layout->recursiveChildSearch("TopFrame");
    m_pUnknown28->getParent()->removeChildWindow(m_pUnknown28);
    m_pUnknown20->addChildWindow(m_pUnknown28);
    m_pUnknown28->setProperty("RiseOnClick", "False");
    m_pUnknown28->moveToFront();
    m_pUnknown28->setZOrderingEnabled(false);

    // --- the two socket containers -------------------------------------------
    // [A] createWindow("DefaultWindow","SSockets","")   -> member +0x30
    m_pUnknown30 = CEGUI::WindowManager::getSingleton().createWindow(
        "DefaultWindow", "SSockets", "");
    m_pUnknown28->addChildWindow(m_pUnknown30);
    m_pUnknown30->setSize(m_pUnknown28->getSize());
    m_pUnknown30->setProperty("RiseOnClick", "False");
    m_pUnknown30->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f, 0.0f),
                                              CEGUI::UDim(0.0f, 0.0f)));
    m_pUnknown30->setMousePassThroughEnabled(true);
    m_pUnknown30->moveToFront();

    // [A] createWindow("DefaultWindow","SSocketsO","")  -> member +0x38
    m_pUnknown38 = CEGUI::WindowManager::getSingleton().createWindow(
        "DefaultWindow", "SSocketsO", "");
    m_pUnknown28->addChildWindow(m_pUnknown38);
    m_pUnknown38->setSize(m_pUnknown28->getSize());
    m_pUnknown38->setProperty("RiseOnClick", "False");
    m_pUnknown38->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f, 0.0f),
                                              CEGUI::UDim(0.0f, 0.0f)));
    m_pUnknown38->setMousePassThroughEnabled(true);
    m_pUnknown38->moveToFront();

    // --- SlotGlow: member +0x3418 -------------------------------------------
    // [A] searched inside m_pUnknown28 (TopFrame), muted, made clickable, made
    //     mouse-transparent, then detached.  It is NOT re-attached anywhere;
    //     keep that asymmetry.
    m_pUnknown3418 = m_pUnknown28->recursiveChildSearch("SlotGlow");
    m_pUnknown3418->EventSet::setMutedState(true);
    m_pUnknown3418->setMousePassThroughEnabled(true);
    m_pUnknown3418->setRiseOnClickEnabled(false);
    m_pUnknown3418->getParent()->removeChildWindow(m_pUnknown3418);

    // --- the Close button ---------------------------------------------------
    // [A] searched inside TopFrame, made non-rising, brought to front, then
    //     subscribed to EventMouseButtonDown (static String at 0x14247e0, E4).
    {
        CEGUI::Window* closeButton = m_pUnknown28->recursiveChildSearch("Close");
        closeButton->setRiseOnClickEnabled(false);
        closeButton->moveToFront();
        closeButton->subscribeEvent(
            CEGUI::Window::EventMouseButtonDown,
            CEGUI::SubscriberSlot(&CStashMenu::handle_CloseButton, this));
    }

    // --- initialize the per-socket indices ------------------------------------
    // Original bfdf60..bfdf72 writes the increasing index, not zero, over
    //     this+0xb0 .. this+0xb0+0x640.  Not a memset call and not 8-byte
    //     stores; keep it as a 400-element int array.
    for (int i = 0; i < 400; ++i)
        m_aiSlotData[i] = i;

    // =========================================================================
    // Item sockets.  They live in TopFrame (m_pUnknown28), not in the layout.
    // =========================================================================
    for (int i = 1; i < STASH_ITEM_SOCKET_COUNT; ++i)
    {
        // [A] name = "Slot" + STRINGS::GetValueAsString(i), formed as a
        //     std::string (operator+(char const*, std::string const&), literal
        //     0xff0cc3) and then *byte*-copied into a CEGUI::String.
        //     The cast is not cosmetic: StringUtilities.h declares both
        //     GetValueAsString(int) and GetValueAsString(unsigned int), and the
        //     exact symbol at 0xc91f60 is the unsigned overload.  Casting makes
        //     the selection match the symbol instead of relying on which
        //     overloads the real header happens to expose.
        CEGUI::String slotName(
            ("Slot" + STRINGS::GetValueAsString((unsigned int)i)).c_str());

        CEGUI::Window* slot = m_pUnknown28->recursiveChildSearch(slotName);

        slot->moveToFront();
        // [A] movb $0x0,0x213  == setRiseOnClickEnabled(false)
        slot->setRiseOnClickEnabled(false);
        slot->setWantsMultiClickEvents(false);

        // [A] the *address* of the socket-data int goes into Window::d_userData,
        //     which the pinned header puts at 472 == 0x1d8.  The index carries
        //     the +18 bias, so item sockets 1..42 own ints 19..60.
        slot->setUserData(&m_aiSlotData[i + STASH_SLOTDATA_BIAS]);

        // [A] four subscriptions; event names are the static CEGUI::String
        //     objects at 0x14247e0 / 0x1423b80 / 0x1424020 / 0x1423700, i.e.
        //     EventMouseButtonDown / EventMouseEnters / EventMouseMove /
        //     EventMouseLeaves (E4).  Note handle_MouseOver is bound twice.
        slot->subscribeEvent(
            CEGUI::Window::EventMouseButtonDown,
            CEGUI::SubscriberSlot(&CStashMenu::handle_ItemClick, this));
        slot->subscribeEvent(
            CEGUI::Window::EventMouseEnters,
            CEGUI::SubscriberSlot(&CStashMenu::handle_MouseOver, this));
        slot->subscribeEvent(
            CEGUI::Window::EventMouseMove,
            CEGUI::SubscriberSlot(&CStashMenu::handle_MouseOver, this));
        slot->subscribeEvent(
            CEGUI::Window::EventMouseLeaves,
            CEGUI::SubscriberSlot(&CStashMenu::handle_MouseOut, this));

        // [A] the array store happens *after* the fourth subscription (bfe464),
        //     not next to the recursiveChildSearch as one might expect.
        m_pSocketedSizeWindows[i + 18] = slot;

        // -- (1) the item-count label: GuiLook/StaticText over the slot ------
        {
            CEGUI::String name(STRINGS::uniqueName(std::string("gui_")).c_str());
            CEGUI::Window* text =
                CEGUI::WindowManager::getSingleton().createWindow(
                    "GuiLook/StaticText", name, "");
            m_pMainStackWindows[(i - 1) + 19] = text;

            text->setFont("Serif");
            text->setSize(slot->getSize());
            const CEGUI::UVector2 labelPosition = slot->getPosition();
            text->setProperty("HorzTextFormatting", "RightAligned");
            text->setProperty("VertFormatting", "TopAligned");
            text->setMousePassThroughEnabled(true);
            text->setPosition(labelPosition);
            slot->getParent()->addChildWindow(text);
            text->setText("");
            // [A] colour(1.0f,1.0f,1.0f,1.0f): the single 1.0f at 0xfa47fc is
            //     loaded once and splatted into all four arguments.
            text->setProperty("TextColour",
                              CEGUI::PropertyHelper::colourToString(
                                  CEGUI::colour(1.0f, 1.0f, 1.0f, 1.0f)));
            text->setAlwaysOnTop(true);
        }

        // -- (2) the socket glow image, parented to the slot's parent -------
        {
            CEGUI::String name(STRINGS::uniqueName(std::string("gui_")).c_str());
            CEGUI::Window* glow =
                CEGUI::WindowManager::getSingleton().createWindow(
                    "GuiLook/StaticImage", name, "");
            slot->getParent()->addChildWindow(glow);
            glow->setRiseOnClickEnabled(false);
            glow->setWantsMultiClickEvents(false);
            glow->setMousePassThroughEnabled(true);
            glow->EventSet::setMutedState(true);
            glow->setPosition(slot->getPosition());
            glow->setSize(slot->getSize());
            m_pMainGlowWindows[(i - 1) + 19] = glow;
        }

        // -- (3) the socket overlay image, parented to SSocketsO ------------
        {
            CEGUI::String name(STRINGS::uniqueName(std::string("gui_")).c_str());
            CEGUI::Window* overlay =
                CEGUI::WindowManager::getSingleton().createWindow(
                    "GuiLook/StaticImage", name, "");
            m_pUnknown38->addChildWindow(overlay);
            overlay->setRiseOnClickEnabled(false);
            overlay->setWantsMultiClickEvents(false);
            overlay->setMousePassThroughEnabled(true);
            overlay->EventSet::setMutedState(true);
            overlay->setPosition(slot->getPosition());
            overlay->setSize(slot->getSize());
            m_pMainSocketGlowWindows[(i - 1) + 19] = overlay;
        }

        // -- (4) the always-on-top stack image -------------------------------
        {
            CEGUI::String name(STRINGS::uniqueName(std::string("gui_")).c_str());
            CEGUI::Window* top =
                CEGUI::WindowManager::getSingleton().createWindow(
                    "GuiLook/StaticImage", name, "");
            slot->getParent()->addChildWindow(top);
            top->setRiseOnClickEnabled(false);
            top->setWantsMultiClickEvents(false);
            top->setMousePassThroughEnabled(true);
            top->EventSet::setMutedState(true);
            top->setPosition(slot->getPosition());
            top->setSize(slot->getSize());
            m_pMainUnidentifiedWindows[(i - 1) + 19] = top;
            top->setAlwaysOnTop(true);
        }
    }

    // =========================================================================
    // The pet tab frames, all looked up in BottomFrame (m_pUnknown40).
    // [A] six DISTINCT members, three separate setZOrderingEnabled(false) calls
    //     and two setVisible(false) calls.  They are not an array.
    // =========================================================================
    m_pUnknown33e0 = m_pUnknown40->recursiveChildSearch("TabBackpack");
    m_pUnknown33e8 = m_pUnknown40->recursiveChildSearch("TabSpell");
    m_pUnknown33f0 = m_pUnknown40->recursiveChildSearch("TabFish");

    m_pUnknown33e0->setZOrderingEnabled(false);
    m_pUnknown33e8->setZOrderingEnabled(false);
    m_pUnknown33f0->setZOrderingEnabled(false);

    m_pUnknown33c8 = m_pUnknown40->recursiveChildSearch("PetSlotsEquipment");
    m_pUnknown33d0 = m_pUnknown40->recursiveChildSearch("PetSlotsSpells");
    m_pUnknown33d0->setVisible(false);
    m_pUnknown33d8 = m_pUnknown40->recursiveChildSearch("PetSlotsFish");

    // Only the spells and fish groups are hidden; equipment is left alone.
    m_pUnknown33d8->setVisible(false);

    // =========================================================================
    // Pet sockets.  These live in BottomFrame (m_pUnknown40), not TopFrame, and
    // their VertFormatting is BottomAligned rather than TopAligned.
    // =========================================================================
    for (int i = 1; i < STASH_PET_SOCKET_COUNT; ++i)
    {
        // [A] Same shape, "PetSlot" prefix (literal 0xfeffd7) and BottomFrame.
        CEGUI::String slotName(
            ("PetSlot" + STRINGS::GetValueAsString((unsigned int)i)).c_str());

        CEGUI::Window* slot = m_pUnknown40->recursiveChildSearch(slotName);

        slot->moveToFront();
        slot->setRiseOnClickEnabled(false);
        slot->setWantsMultiClickEvents(false);
        slot->setUserData(&m_aiSlotData[i + STASH_SLOTDATA_BIAS]);

        slot->subscribeEvent(
            CEGUI::Window::EventMouseButtonDown,
            CEGUI::SubscriberSlot(&CStashMenu::handle_PetItemClick, this));
        slot->subscribeEvent(
            CEGUI::Window::EventMouseEnters,
            CEGUI::SubscriberSlot(&CStashMenu::handle_PetMouseOver, this));
        slot->subscribeEvent(
            CEGUI::Window::EventMouseMove,
            CEGUI::SubscriberSlot(&CStashMenu::handle_PetMouseOver, this));
        slot->subscribeEvent(
            CEGUI::Window::EventMouseLeaves,
            CEGUI::SubscriberSlot(&CStashMenu::handle_PetMouseOut, this));

        // [A] stored at c0081f, again after the last subscription.
        m_pSlotWindows[i + 18] = slot;

        // -- (1) the pet-item-count label -------------------------------------
        {
            CEGUI::String name(STRINGS::uniqueName(std::string("gui_")).c_str());
            CEGUI::Window* text =
                CEGUI::WindowManager::getSingleton().createWindow(
                    "GuiLook/StaticText", name, "");
            m_pStackWindows[i + 18] = text;

            text->setFont("Serif");
            text->setSize(slot->getSize());
            const CEGUI::UVector2 labelPosition = slot->getPosition();
            text->setProperty("HorzTextFormatting", "RightAligned");
            text->setProperty("VertFormatting", "BottomAligned");
            text->setMousePassThroughEnabled(true);
            text->setPosition(labelPosition);
            slot->getParent()->addChildWindow(text);
            text->setText("");
            text->setProperty("TextColour",
                              CEGUI::PropertyHelper::colourToString(
                                  CEGUI::colour(1.0f, 1.0f, 1.0f, 1.0f)));
            text->setAlwaysOnTop(true);
        }

        // -- (2) the socket glow image ----------------------------------------
        {
            CEGUI::String name(STRINGS::uniqueName(std::string("gui_")).c_str());
            CEGUI::Window* glow =
                CEGUI::WindowManager::getSingleton().createWindow(
                    "GuiLook/StaticImage", name, "");
            slot->getParent()->addChildWindow(glow);
            glow->setRiseOnClickEnabled(false);
            glow->setWantsMultiClickEvents(false);
            glow->setMousePassThroughEnabled(true);
            glow->EventSet::setMutedState(true);
            glow->setPosition(slot->getPosition());
            glow->setSize(slot->getSize());
            m_pSlotGlowWindows[i + 18] = glow;
        }

        // -- (3) the socket overlay image, parented to SSocketsO --------------
        {
            CEGUI::String name(STRINGS::uniqueName(std::string("gui_")).c_str());
            CEGUI::Window* overlay =
                CEGUI::WindowManager::getSingleton().createWindow(
                    "GuiLook/StaticImage", name, "");
            m_pUnknown38->addChildWindow(overlay);
            overlay->setRiseOnClickEnabled(false);
            overlay->setWantsMultiClickEvents(false);
            overlay->setMousePassThroughEnabled(true);
            overlay->EventSet::setMutedState(true);
            overlay->setPosition(slot->getPosition());
            overlay->setSize(slot->getSize());
            m_pSocketGlowWindows[i + 18] = overlay;
        }

        // -- (4) the always-on-top stack image -------------------------------
        {
            CEGUI::String name(STRINGS::uniqueName(std::string("gui_")).c_str());
            CEGUI::Window* top =
                CEGUI::WindowManager::getSingleton().createWindow(
                    "GuiLook/StaticImage", name, "");
            slot->getParent()->addChildWindow(top);
            top->setRiseOnClickEnabled(false);
            top->setWantsMultiClickEvents(false);
            top->setMousePassThroughEnabled(true);
            top->EventSet::setMutedState(true);
            top->setPosition(slot->getPosition());
            top->setSize(slot->getSize());
            m_pUnidentifiedWindows[i + 18] = top;
            top->setAlwaysOnTop(true);
        }
    }

    // --- teardown ------------------------------------------------------------
    // [A] four std::string / std::wstring members of layoutFile are destroyed
    //     here (0x3530, 0x3538, 0x3540, 0x3550) plus the long-lived
    //     CEGUI::String local at 0x40(%rsp).  These are the automatic objects;
    //     no explicit code is needed and none is written.
    // [A] One more slot, 0x3580(%rsp), is tested and, only if non-null, passed to
    //     Ogre::NedAllocImpl::deallocBytes.  It is zeroed in the prologue (bfbe94)
    //     and never written in this function -- there is no `lea 0x3580(%rsp)`
    //     anywhere in the 6271-line listing -- so the free never runs.  It is not
    //     modelled.  See output/UNRESOLVED.md section 7.
}

#include <string>

#include "CEGUI.h"

#include "BaseUnit.h"
#include "Equipment.h"
#include "GameUI.h"
#include "StringUtilities.h"

#include "StashMenu.h"

// 6229 machine bytes at 0xb6ab50. The two integer parameters are not interchangeable: the
// second one indexes the window arrays of CMerchantMenu, the third one (scaled by 4)
// becomes the address stored in the item icon's userData.
void CStashMenu::setPetSlotIcon(CEquipment* pItem, int iSlotIndex, int iDataIndex)
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
                &m_pUnknown3410->getImage("onesocketglow")));
        }
        else
        {
            m_pSocketGlowWindows[iSlotIndex]->setProperty("Image", CEGUI::PropertyHelper::imageToString(
                &m_pUnknown3410->getImage("twosocketglow")));
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
            &m_pUnknown3410->getImage("unidentified")));
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

                m_pUnknown30->addChildWindow(pSocketedIcon);

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

    if (!pItem->canEquip(m_pCharacter, false))
    {
        if (pItem->isMagical())
        {
            m_pSlotGlowWindows[iSlotIndex]->setProperty("Image", CEGUI::PropertyHelper::imageToString(
                &m_pUnknown3410->getImage("blueredslotglow")));
        }
        else
        {
            // 11 byte image name at 0xfe60e3; the bytes are not in the confirmed rodata.
            m_pSlotGlowWindows[iSlotIndex]->setProperty("Image", CEGUI::PropertyHelper::imageToString(
                &m_pUnknown3410->getImage("redslotglow")));
        }
    }
    else if (pItem->ISA(kIsaSlotGold))
    {
        m_pSlotGlowWindows[iSlotIndex]->setProperty("Image", CEGUI::PropertyHelper::imageToString(
            &m_pUnknown3410->getImage("goldslotglow")));
    }
    else if (pItem->isMagical())
    {
        if (pItem->ISA(kIsaSlotBlue))
        {
            m_pSlotGlowWindows[iSlotIndex]->setProperty("Image", CEGUI::PropertyHelper::imageToString(
                &m_pUnknown3410->getImage("blueslotglow")));
        }
        else
        {
            m_pSlotGlowWindows[iSlotIndex]->setProperty("Image", CEGUI::PropertyHelper::imageToString(
                &m_pUnknown3410->getImage("greenslotglow")));
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

void CStashMenu::setSlotIcon(CEquipment* pItem, int iSlotIndex, int iDataIndex)
{


    // Two independent getPosition() calls on the slot window (b6ab7c, b6abd4). The second
    // UDim of the vector is the one that is used, and asAbsolute(0.0f) really multiplies by
    // a runtime zero: 0.0f * inf is a NaN, which fails the "0.0f < x" test inside
    // PixelAligned and would take the other branch, so the multiply must stay.
    // UDim::asAbsolute returns float in this CEGUI (CEGUIUDim.h).
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
        // rdi = this, rsi = the argument: the icon is taken out of its current parent and
        // then added to the slot window.
        CEGUI::Window* pOldParent = pIcon->getParent();
        if (pOldParent != 0)
        {
            pOldParent->removeChildWindow(pIcon);
        }

        m_pSocketedSizeWindows[iSlotIndex]->addChildWindow(pIcon);

        // Both calls are in the original; only the second one leaves the icon at (0,0).
        pIcon->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f, 0.0f), CEGUI::UDim(0.0f, 1.0f)));
        pIcon->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f, 0.0f), CEGUI::UDim(0.0f, 0.0f)));

        pIcon->setSize(m_pSocketedSizeWindows[iSlotIndex]->getSize());
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
        m_pMainSocketGlowWindows[iSlotIndex]->setProperty("Image", "");
    }
    else
    {
        if (pItem->m_iSocketCount == 1)
        {
            m_pMainSocketGlowWindows[iSlotIndex]->setProperty("Image", CEGUI::PropertyHelper::imageToString(
                &m_pUnknown3410->getImage("onesocketglow")));
        }
        else
        {
            m_pMainSocketGlowWindows[iSlotIndex]->setProperty("Image", CEGUI::PropertyHelper::imageToString(
                &m_pUnknown3410->getImage("twosocketglow")));
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
            &m_pUnknown3410->getImage("unidentified")));
    }

    // Multi socket items are nudged up by a fraction of the slot height.
    if (pItem->m_iSocketCount > 1)
    {
        uiIconY = (unsigned int)((float)uiIconY +
            m_pSocketedSizeWindows[iSlotIndex]->getSize().d_y.asAbsolute(0.0f) * -0.19f);
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

                m_pUnknown30->addChildWindow(pSocketedIcon);

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
                m_pSocketedSizeWindows[iSlotIndex]->getSize().d_y.asAbsolute(0.0f) * 0.4f);
        }
    }

    // Main slot glow. canEquip() and isMagical() are virtual calls, ISA() is a direct call;
    // the short circuit order is part of the behaviour.


    // Only the numeric values are proven; the enumerator names live in UnitTypes.h, which
    // is not part of the evidence (see output/UNRESOLVED.md).
    const UNITTYPES::EUNITTYPES kIsaSlotGold = static_cast<UNITTYPES::EUNITTYPES>(0x36);
    const UNITTYPES::EUNITTYPES kIsaSlotBlue = static_cast<UNITTYPES::EUNITTYPES>(0x37);

    if (!pItem->canEquip(m_pCharacter, false))
    {
        if (pItem->isMagical())
        {
            m_pMainGlowWindows[iSlotIndex]->setProperty("Image", CEGUI::PropertyHelper::imageToString(
                &m_pUnknown3410->getImage("blueredslotglow")));
        }
        else
        {
            // 11 byte image name at 0xfe60e3; the bytes are not in the confirmed rodata.
            m_pMainGlowWindows[iSlotIndex]->setProperty("Image", CEGUI::PropertyHelper::imageToString(
                &m_pUnknown3410->getImage("redslotglow")));
        }
    }
    else if (pItem->ISA(kIsaSlotGold))
    {
        m_pMainGlowWindows[iSlotIndex]->setProperty("Image", CEGUI::PropertyHelper::imageToString(
            &m_pUnknown3410->getImage("goldslotglow")));
    }
    else if (pItem->isMagical())
    {
        if (pItem->ISA(kIsaSlotBlue))
        {
            m_pMainGlowWindows[iSlotIndex]->setProperty("Image", CEGUI::PropertyHelper::imageToString(
                &m_pUnknown3410->getImage("blueslotglow")));
        }
        else
        {
            m_pMainGlowWindows[iSlotIndex]->setProperty("Image", CEGUI::PropertyHelper::imageToString(
                &m_pUnknown3410->getImage("greenslotglow")));
        }
    }
    else
    {
        m_pMainGlowWindows[iSlotIndex]->setProperty("Image", "");
    }

    // Stack count window; nothing at all is called when it does not exist.


    if (m_pMainStackWindows[iSlotIndex] != 0)
    {
        if (pItem->m_iUnknown238 <= 1)
        {
            m_pMainStackWindows[iSlotIndex]->setVisible(false);
        }
        else
        {
            m_pMainStackWindows[iSlotIndex]->setVisible(true);

            // The GetValueAsString() temporary dies right after the concatenation and the
            // concatenated string dies after setText.
            std::string sCount = "x" + STRINGS::GetValueAsString(pItem->m_iUnknown238);

            // The constructor the listing calls is String(unsigned char const*), i.e.
            // String(const utf8*) - plain c_str() would select String(const char*).
            CEGUI::String sText((const unsigned char*)sCount.c_str());

            m_pMainStackWindows[iSlotIndex]->setText(sText);
        }
    }
}

#include "Character.h"
#include <CEGUI.h>
namespace stash_controls {
struct ClientFields {char prefix[0x1c8];TSafePointer<CRunicCore> first,second,third,fourth;};
struct ClientUI {char prefix[0x1920];ClientFields* client;};
inline __attribute__((always_inline,flatten)) void clearMouseClicks(CGameUI* ui) {
 ClientFields* c=reinterpret_cast<ClientUI*>(ui)->client;
 c->fourth.setObject(0);c->third.setObject(0);c->first.setObject(0);c->second.setObject(0);
}
}
void CStashMenu::equipmentPickedUp(CEquipment*){updateLayout();}
void CStashMenu::equipmentDropped(CEquipment*){updateLayout();}
void CStashMenu::equipmentEquipped(CEquipment*){updateLayout();}
void CStashMenu::equipmentUnequipped(CEquipment*){updateLayout();}
void CStashMenu::equipmentUsed(CEquipment*){updateLayout();}
void CStashMenu::inventoryDestroyed(){}
bool CStashMenu::handle_ItemClick(const CEGUI::EventArgs& event) {
 const CEGUI::MouseEventArgs& mouse=static_cast<const CEGUI::MouseEventArgs&>(event);
 if(mouse.window){int slot=*static_cast<int*>(mouse.window->getUserData());
  if(mouse.button==CEGUI::LeftButton)m_iUnknown3400=slot;
  else if(mouse.button==CEGUI::RightButton)m_iUnknown3404=slot;
 }return true;
}
bool CStashMenu::handle_PetItemClick(const CEGUI::EventArgs& event) {
 const CEGUI::MouseEventArgs& mouse=static_cast<const CEGUI::MouseEventArgs&>(event);
 if(mouse.window){int slot=*static_cast<int*>(mouse.window->getUserData());
  if(mouse.button==CEGUI::LeftButton)m_iUnknown33F8=slot;
  else if(mouse.button==CEGUI::RightButton)m_iUnknown33FC=slot;
 }return true;
}
bool CStashMenu::handle_MouseThrough(const CEGUI::EventArgs&){m_bUnknown3420=false;return true;}
void CStashMenu::setPetTab(int tab){onClick(static_cast<ELayoutFunction>(tab+14));}
bool CStashMenu::handle_onClick(const CEGUI::EventArgs& event) {
 const CEGUI::MouseEventArgs& mouse=static_cast<const CEGUI::MouseEventArgs&>(event);
 if(mouse.button==CEGUI::LeftButton&&mouse.window)return onClick(*static_cast<ELayoutFunction*>(mouse.window->getUserData()));
 return true;
}
bool CStashMenu::handle_CloseButton(const CEGUI::EventArgs& event) {
 if(static_cast<const CEGUI::MouseEventArgs&>(event).button==CEGUI::LeftButton) {
  m_bUnknown62=true;m_pGameUI->getCharacter()->setTarget(0);
  stash_controls::clearMouseClicks(m_pGameUI);m_pGameUI->closeRight();
 }return true;
}
bool CStashMenu::onClick(ELayoutFunction action) {
 if(m_bOpenPartial&&(static_cast<int>(action)==14||static_cast<int>(action)==15||static_cast<int>(action)==16)) {
  static_cast<CEGUI::RadioButton*>(m_pUnknown33e0)->setSelected(static_cast<int>(action)==14);
  static_cast<CEGUI::RadioButton*>(m_pUnknown33e8)->setSelected(static_cast<int>(action)==15);
  static_cast<CEGUI::RadioButton*>(m_pUnknown33f0)->setSelected(static_cast<int>(action)==16);
  m_pUnknown33c8->setVisible(static_cast<int>(action)==14);
  m_pUnknown33d0->setVisible(static_cast<int>(action)==15);
  m_pUnknown33d8->setVisible(static_cast<int>(action)==16);
  updateLayout();
 }return true;
}
void CStashMenu::mapEventHandlers(CEGUI::Window* window) {
 int count=static_cast<int>(window->getChildCount());
 for(int i=0;i<count;++i)mapEventHandlers(window->getChildAtIdx(i));
 try {
  if(window->isPropertyPresent("onClick")&&!window->getProperty("onClick").empty())
   window->subscribeEvent(CEGUI::Window::EventMouseButtonDown,CEGUI::Event::Subscriber(&CStashMenu::handle_onClick,this));
 }catch(...) {}
}

#include "Inventory.h"
#include "SharedStash.h"
namespace stash_owners {
inline __attribute__((always_inline)) CCharacter* firstFollower(CCharacter* player){return player->getFollower(0);}
}
void CStashMenu::setPlayer(CCharacter* player) {
 if(m_pCharacter&&stash_owners::firstFollower(m_pCharacter))stash_owners::firstFollower(m_pCharacter)->m_pInventory->removeListener(this);
 m_pCharacter=player;
 if(player&&stash_owners::firstFollower(player))stash_owners::firstFollower(player)->m_pInventory->addListener(this);
}
void CStashMenu::setOwner(CCharacter* owner) {
 if(owner!=m_pOwner)inventoryDestroyed();
 if(m_pOwner) {
  CInventory* inventory;
  if(m_pOwner->ISA(static_cast<UNITTYPES::EUNITTYPES>(170))&&CSharedStash::getSingleton())inventory=CSharedStash::getSingleton()->m_pInventory;
  else inventory=static_cast<CCharacter*>(m_pOwner)->m_pInventory;
  if(inventory)inventory->removeListener(this);
 }
 m_pOwner=owner;
 if(owner) {
  CInventory* inventory;
  if(owner->ISA(static_cast<UNITTYPES::EUNITTYPES>(170))&&CSharedStash::getSingleton()){inventory=CSharedStash::getSingleton()->m_pInventory;m_bUnknown3421=true;}
  else {inventory=static_cast<CCharacter*>(m_pOwner)->m_pInventory;m_bUnknown3421=false;}
  if(inventory)inventory->addListener(this);
 }
 if(m_pCharacter&&stash_owners::firstFollower(m_pCharacter)) {
  stash_owners::firstFollower(m_pCharacter)->m_pInventory->removeListener(this);
  stash_owners::firstFollower(m_pCharacter)->m_pInventory->addListener(this);
 }
}

namespace stash_input {
struct UIFields {char prefix[0xb8];CEquipment* dragged;};
struct HoverFields {char prefix[0x198];bool flag198;};
inline __attribute__((always_inline)) void removeGlow(CStashMenu* menu) {
 if(menu->m_pUnknown28->isChild(menu->m_pUnknown3418))menu->m_pUnknown28->removeChildWindow(menu->m_pUnknown3418);
 else if(menu->m_pUnknown40->isChild(menu->m_pUnknown3418))menu->m_pUnknown40->removeChildWindow(menu->m_pUnknown3418);
}
}
bool CStashMenu::processInput(void*,float,bool active) {
 if(!active){m_pHoverObject=0;m_pUnknown30->setVisible(false);m_pUnknown38->setVisible(false);stash_input::removeGlow(this);return true;}
 bool result=true;if(m_bUnknown62){setOpen(false);m_bUnknown62=false;result=false;}
 CEquipment* dragged=0;
 if(m_pOwner&&!m_pOwner->ISA(static_cast<UNITTYPES::EUNITTYPES>(127)))dragged=reinterpret_cast<stash_input::UIFields*>(m_pGameUI)->dragged;
 if(dragged&&dragged->ISA(static_cast<UNITTYPES::EUNITTYPES>(120))) {
  m_pUnknown38->setVisible(true);m_pUnknown38->moveToFront();m_pUnknown30->setVisible(true);m_pUnknown30->moveToFront();
 }else if(!m_pHoverObject||reinterpret_cast<stash_input::HoverFields*>(m_pHoverObject)->flag198) {
  m_pHoverObject=0;m_pUnknown30->setVisible(false);m_pUnknown38->setVisible(false);
 }
 if(!m_bUnknown3420)stash_input::removeGlow(this);
 m_iUnknown3400=-1;m_iUnknown3404=-1;m_iUnknown33F8=-1;m_iUnknown33FC=-1;return result;
}
bool CStashMenu::handle_MouseOut(const CEGUI::EventArgs& event) {
 CEGUI::Window* window=static_cast<const CEGUI::WindowEventArgs&>(event).window;CBaseUnit* owner=m_pOwner;
 if(window&&owner){int slot=*static_cast<int*>(window->getUserData());CInventory* inventory;
  if(owner->ISA(static_cast<UNITTYPES::EUNITTYPES>(170)))inventory=CSharedStash::getSingleton()->m_pInventory;
  else inventory=static_cast<CCharacter*>(m_pOwner)->m_pInventory;
  CEquipment* item=inventory->getEquipmentInSlot(slot);
  if(item==m_pHoverObject){m_pHoverObject=0;CEquipment* dragged=reinterpret_cast<stash_input::UIFields*>(m_pGameUI)->dragged;
   if(!dragged||!dragged->ISA(static_cast<UNITTYPES::EUNITTYPES>(120))){m_pUnknown30->setVisible(false);m_pUnknown38->setVisible(false);}
  }
 }return true;
}
bool CStashMenu::handle_PetMouseOut(const CEGUI::EventArgs& event) {
 CEGUI::Window* window=static_cast<const CEGUI::WindowEventArgs&>(event).window;CCharacter* pet=m_pCharacter->getFollower(0);
 if(pet&&window){int slot=*static_cast<int*>(window->getUserData());CEquipment* item=pet->m_pInventory->getEquipmentInSlot(slot);
  if(item==m_pHoverObject){m_pHoverObject=0;CEquipment* dragged=reinterpret_cast<stash_input::UIFields*>(m_pGameUI)->dragged;
   if(!dragged||!dragged->ISA(static_cast<UNITTYPES::EUNITTYPES>(120))){m_pUnknown30->setVisible(false);m_pUnknown38->setVisible(false);}
  }
 }return true;
}

#include "MasterResourceManager.h"
#include "SoundBankDataInformation.h"
#include "SoundBank.h"
#include "SoundData.h"
CStashMenu::CStashMenu(CGameUI& ui,CSettings& settings,Ogre::RenderWindow* render,
 Ogre::SceneManager* scene,CEGUI::Window* parent,CResourceManager* resources)
 :m_pUnknown18(parent),m_pOwner(0),m_pCharacter(0),m_bOpenPartial(false),m_bUnknown61(true),m_bUnknown62(false),
 m_pDynamicPropertyFile(&settings),m_pGameUI(&ui),m_pUnknown78(scene),m_pUnknown80(render),m_pUnknown90(0),
 m_pResourceManager(resources),m_fScreenEdge(0.0f),m_pSoundBank(0),m_iUnknown33F8(-1),m_iUnknown33FC(-1),
 m_iUnknown3400(-1),m_iUnknown3404(-1),m_pHoverObject(0),m_bUnknown3420(false),m_bUnknown3421(false)
{
 CSoundBankDataInformation* sounds=CMasterResourceManager::getSingleton()->m_pSoundBankDataInformation;
 m_pSoundBank=new CSoundBank(*CMasterResourceManager::getSingleton()->m_pSoundManager,false);
 CSoundData* open=sounds->getSoundDataObject(L"STATSOPEN");if(open)m_pSoundBank->addSample(22,open->m_iGuid);
 CSoundData* close=sounds->getSoundDataObject(L"STATSCLOSE");if(close)m_pSoundBank->addSample(66,close->m_iGuid);
 createMenus();
}
CStashMenu::~CStashMenu() {
 setPlayer(0);setOwner(0);
 if(m_pUnknown90){delete m_pUnknown90;m_pUnknown90=0;}
 if(m_pSoundBank){delete m_pSoundBank;m_pSoundBank=0;}
}

bool CStashMenu::handle_MouseOver(const CEGUI::EventArgs& event) {
 CEGUI::Window* window=static_cast<const CEGUI::WindowEventArgs&>(event).window;CBaseUnit* owner=m_pOwner;
 if(window&&owner){int slot=*static_cast<int*>(window->getUserData());CInventory* inventory;
  if(owner->ISA(static_cast<UNITTYPES::EUNITTYPES>(170)))inventory=CSharedStash::getSingleton()->m_pInventory;
  else inventory=static_cast<CCharacter*>(m_pOwner)->m_pInventory;

  CEquipment* item=inventory->getEquipmentInSlot(slot);
  if(item){m_pHoverObject=item;
   if((item->m_bUnknown348&&item->m_iSocketCount)||item->ISA(static_cast<UNITTYPES::EUNITTYPES>(120))){m_pUnknown38->setVisible(true);m_pUnknown38->moveToFront();m_pUnknown30->setVisible(true);m_pUnknown30->moveToFront();}
   else {m_pUnknown30->setVisible(false);m_pUnknown38->setVisible(false);}
  }
  // Both original hover paths attach the shared glow to TopFrame.
  CEGUI::Window* parent=m_pUnknown28;
  float x=m_pSocketedSizeWindows[slot]->getPosition().d_x.asAbsolute(0.0f);
  float y=m_pSocketedSizeWindows[slot]->getPosition().d_y.asAbsolute(0.0f);
  float width=m_pSocketedSizeWindows[slot]->getWidth().asAbsolute(0.0f);
  float height=m_pSocketedSizeWindows[slot]->getHeight().asAbsolute(0.0f);
  if(!parent->isChild(m_pUnknown3418))parent->addChildWindow(m_pUnknown3418);
  m_pUnknown3418->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f,x),CEGUI::UDim(0.0f,y)));
  m_pUnknown3418->setSize(CEGUI::UVector2(CEGUI::UDim(0.0f,width),CEGUI::UDim(0.0f,height)));
  m_pUnknown3418->moveToBack();m_bUnknown3420=true;

 }return true;
}
bool CStashMenu::handle_PetMouseOver(const CEGUI::EventArgs& event) {
 CEGUI::Window* window=static_cast<const CEGUI::WindowEventArgs&>(event).window;CCharacter* pet=m_pCharacter->getFollower(0);
 if(pet&&window){int slot=*static_cast<int*>(window->getUserData());CInventory* inventory=pet->m_pInventory;

  CEquipment* item=inventory->getEquipmentInSlot(slot);
  if(item){m_pHoverObject=item;
   if((item->m_bUnknown348&&item->m_iSocketCount)||item->ISA(static_cast<UNITTYPES::EUNITTYPES>(120))){m_pUnknown38->setVisible(true);m_pUnknown38->moveToFront();m_pUnknown30->setVisible(true);m_pUnknown30->moveToFront();}
   else {m_pUnknown38->setVisible(false);m_pUnknown30->setVisible(false);}
  }
  // Both original hover paths attach the shared glow to TopFrame.
  CEGUI::Window* parent=m_pUnknown28;
  float x=m_pSlotWindows[slot]->getPosition().d_x.asAbsolute(0.0f);
  float y=m_pSlotWindows[slot]->getPosition().d_y.asAbsolute(0.0f);
  float width=m_pSlotWindows[slot]->getWidth().asAbsolute(0.0f);
  float height=m_pSlotWindows[slot]->getHeight().asAbsolute(0.0f);
  if(!parent->isChild(m_pUnknown3418))parent->addChildWindow(m_pUnknown3418);
  m_pUnknown3418->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f,x),CEGUI::UDim(0.0f,y)));
  m_pUnknown3418->setSize(CEGUI::UVector2(CEGUI::UDim(0.0f,width),CEGUI::UDim(0.0f,height)));
  m_pUnknown3418->moveToBack();m_bUnknown3420=true;

 }return true;
}

void CStashMenu::setOpen(bool open) {
 if(m_bOpenPartial){
  if(!open){m_pSoundBank->playSample(66,0,0.0f,0.0f,false);m_pUnknown90->blendAnimation("CLOSE",false,0.1f,2.0f,-1.0f);m_bUnknown61=false;m_bOpenPartial=false;return;}
 }else {
  if(!open){m_bOpenPartial=false;return;}
  m_pDynamicPropertyFile->GetInt(KSETTINGS_RES_WIDTH);m_pDynamicPropertyFile->GetInt(KSETTINGS_RES_HEIGHT);
  m_pSoundBank->playSample(22,0,0.0f,0.0f,false);m_pUnknown90->setVisible(true);
  if(m_pUnknown90->animationPlaying("CLOSE"))m_pUnknown90->blendAnimation("OPEN",false,0.1f,2.0f,-1.0f);
  else m_pUnknown90->playAnimation("OPEN",false,2.0f,-1.0f);
  m_pUnknown90->queueBlendAnimation("IDLE",true,0.1f,1.0f);
  m_pUnknown18->addChildWindow(m_pUnknown20);m_pUnknown20->moveToBack();
  static_cast<CEGUI::RadioButton*>(m_pUnknown33e0)->setSelected(true);
  static_cast<CEGUI::RadioButton*>(m_pUnknown33e8)->setSelected(false);
  static_cast<CEGUI::RadioButton*>(m_pUnknown33f0)->setSelected(false);
  m_pUnknown33c8->setVisible(true);m_pUnknown33d0->setVisible(false);m_pUnknown33d8->setVisible(false);
  m_pGameUI->queueTip(static_cast<EContextTip>(m_bUnknown3421?21:17));
 }
 m_bOpenPartial=open;updateLayout();
}

#include <OgreSkeletonInstance.h>
#include <OgreBone.h>
namespace stash_animation {
struct ModelFields {char prefix[0x60];Ogre::Entity* entity;char gap68[0x130-0x68];Ogre::SkeletonInstance* skeleton;};
inline __attribute__((always_inline)) ModelFields& model(CGenericModel* p){return *reinterpret_cast<ModelFields*>(p);}
}
void CStashMenu::update(float elapsed) {
 int width=m_pDynamicPropertyFile->GetInt(KSETTINGS_RES_WIDTH);int height=m_pDynamicPropertyFile->GetInt(KSETTINGS_RES_HEIGHT);
 if(!m_bOpenPartial){m_pHoverObject=0;m_pUnknown30->setVisible(false);m_pUnknown38->setVisible(false);}
 if(m_bOpenPartial||!m_bUnknown61){
  m_pUnknown90->updateAnimation(elapsed,false);stash_animation::model(m_pUnknown90).entity->_updateAnimation();
  Ogre::Bone* top=stash_animation::model(m_pUnknown90).skeleton->getBone("tag_topmerchant");
  Ogre::Vector3 position=m_pUnknown90->getPosition(false);const Ogre::Vector3& offset=top->_getDerivedPosition();
  float x=position.x+offset.x;float y=position.y+offset.y;
  x=m_pGameUI->scaledY(x);float halfWidth=float(width)*0.5f;y=m_pGameUI->scaledY(y);y=-(y+float(height)*-0.5f);
  m_pUnknown28->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f,halfWidth+x),CEGUI::UDim(0.0f,y)));
  Ogre::Bone* bottom=stash_animation::model(m_pUnknown90).skeleton->getBone("tag_bottommerchant");
  position=m_pUnknown90->getPosition(false);const Ogre::Vector3& bottomOffset=bottom->_getDerivedPosition();
  x=m_pGameUI->scaledY(position.x+bottomOffset.x);
  m_pUnknown40->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f,halfWidth+x),CEGUI::UDim(0.0f,y)));
  Ogre::Bone* right=stash_animation::model(m_pUnknown90).skeleton->getBone("tag_bottommerchantright");
  position=m_pUnknown90->getPosition(false);const Ogre::Vector3& rightOffset=right->_getDerivedPosition();
  x=m_pGameUI->scaledY(position.x+rightOffset.x);float margin=m_pGameUI->scaledY(50.0f);float edge=(halfWidth+x)-margin;m_fScreenEdge=edge>0.0f?edge:0.0f;
  if(!m_bOpenPartial&&!m_bUnknown61&&!m_pUnknown90->animationPlaying("CLOSE")&&!m_pUnknown90->animationQueued("CLOSE")){
   m_pUnknown90->setVisible(false);m_pUnknown18->removeChildWindow(m_pUnknown20);m_bUnknown61=true;
  }
 }
}

#include "EquipmentRef.h"
namespace stash_layout {
inline __attribute__((always_inline)) TArrayList<CEquipmentRef*>& equipment(CInventory* p){return p->m_equipmentRefs;}
}
void CStashMenu::updateLayout(){
 if(!m_bOpenPartial||!m_pOwner)return;
 CInventory* inventory;
 if(m_pOwner->ISA(static_cast<UNITTYPES::EUNITTYPES>(170)))inventory=CSharedStash::getSingleton()->m_pInventory;
 else inventory=static_cast<CCharacter*>(m_pOwner)->m_pInventory;
 if(!inventory)return;
 while(m_pUnknown30->getChildCount())m_pUnknown30->removeChildWindow(m_pUnknown30->getChildAtIdx(0));
 for(int slot=19;slot<61;++slot){
  if(m_pSocketedSizeWindows[slot]->getChildCount())m_pSocketedSizeWindows[slot]->removeChildWindow(m_pSocketedSizeWindows[slot]->getChildAtIdx(0));
  m_pMainUnidentifiedWindows[slot]->setProperty("Image","");m_pMainGlowWindows[slot]->setProperty("Image","");m_pMainSocketGlowWindows[slot]->setProperty("Image","");
  if(m_pMainStackWindows[slot])m_pMainStackWindows[slot]->setText("");
 }
 TArrayList<CEquipmentRef*>& items=stash_layout::equipment(inventory);
 for(unsigned i=0;i<items.size();++i){CEquipmentRef* ref=items[i];CEquipment* item=static_cast<CEquipment*>(ref->m_pUnknown10);if(ref->m_iSlot>18){int slot=items[i]->m_iSlot;setSlotIcon(item,slot,slot);}}
 inventory=m_pCharacter->getFollower(0)->m_pInventory;
 if(inventory){
  for(int slot=19;slot<82;++slot){
   if(m_pSlotWindows[slot]->getChildCount())m_pSlotWindows[slot]->removeChildWindow(m_pSlotWindows[slot]->getChildAtIdx(0));
   m_pSlotGlowWindows[slot]->setProperty("Image","");m_pSocketGlowWindows[slot]->setProperty("Image","");m_pUnidentifiedWindows[slot]->setProperty("Image","");
   if(m_pStackWindows[slot])m_pStackWindows[slot]->setText("");
  }
  TArrayList<CEquipmentRef*>& petItems=stash_layout::equipment(inventory);
  for(unsigned i=0;i<petItems.size();++i){CEquipmentRef* ref=petItems[i];CEquipment* item=static_cast<CEquipment*>(ref->m_pUnknown10);if(ref->m_iSlot>18){int slot=petItems[i]->m_iSlot;setPetSlotIcon(item,slot,slot);}}
 }
 m_pUnknown20->moveToBack();m_pUnknown40->moveToFront();m_pUnknown28->moveToFront();m_pUnknown38->moveToFront();m_pUnknown30->moveToFront();
}
