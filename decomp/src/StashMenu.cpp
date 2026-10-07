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
        m_apItemSlotWindows[i - 1] = slot;

        // -- (1) the item-count label: GuiLook/StaticText over the slot ------
        {
            CEGUI::String name(STRINGS::uniqueName(std::string("gui_")).c_str());
            CEGUI::Window* text =
                CEGUI::WindowManager::getSingleton().createWindow(
                    "GuiLook/StaticText", name, "");
            m_apItemCountWindows[i - 1] = text;

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
            m_apItemSocketGlowWindows[i - 1] = glow;
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
            m_apItemSocketOverlayWindows[i - 1] = overlay;
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
            m_apItemStackWindows[i - 1] = top;
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
        m_apPetSlotWindows[i - 1] = slot;

        // -- (1) the pet-item-count label -------------------------------------
        {
            CEGUI::String name(STRINGS::uniqueName(std::string("gui_")).c_str());
            CEGUI::Window* text =
                CEGUI::WindowManager::getSingleton().createWindow(
                    "GuiLook/StaticText", name, "");
            m_apPetCountWindows[i - 1] = text;

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
            m_apPetSocketGlowWindows[i - 1] = glow;
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
            m_apPetSocketOverlayWindows[i - 1] = overlay;
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
            m_apPetStackWindows[i - 1] = top;
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