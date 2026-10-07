#ifndef OTHER_CLASS_ADDITIONS_H
#define OTHER_CLASS_ADDITIONS_H

// ============================================================================
//  output/other-class-additions.h
//
//  Declarations that output/MerchantMenu.cpp requires, that are proven by the
//  original ELF, but that live in OTHER classes whose headers are read-only
//  inputs.  This file is the exact text to merge into those headers; it is
//  deliberately NOT hidden inside MerchantMenu.h, because putting
//  `CGameUI::convertToScreenScale` on CMerchantMenu would be a fiction.
//
//  Each entry gives the call target, the register arguments, and how the name
//  and arity were fixed.  Nothing here is a guess dressed up as an API: every
//  one is either (a) a named function whose mangled name and demangled
//  signature the supervisor's own symbol table already proves, or (b) marked
//  [B] with the offset arithmetic that pins the member.
//
//  If the supervisor's own GameUI.h / SceneNodeObject.h already declare these,
//  this file is a no-op; nothing in MerchantMenu.cpp changes.
// ============================================================================

// ----------------------------------------------------------------------------
//  1. CGameUI  (input/project-headers/GameUI.h is a "Partial" export)
// ----------------------------------------------------------------------------
//  Both are plain non-virtual members called on `this` = m_pGameUI (+0x70) with
//  the freshly loaded layout root in %rsi.
//
//    0xb6fa6e  mov 0x70(%rbx),%rdi        ; this
//    0xb6fa72  xor %edx,%edx              ; bool false
//    0xb6fa74  mov %r15,%rsi              ; layoutRoot
//    0xb6fa77  call 0xa83ed0 <CGameUI::convertToScreenScale(CEGUI::Window*, bool)>
//
//    0xb6fa7c  mov 0x70(%rbx),%rdi
//    0xb6fa80  mov %r15,%rsi
//    0xb6fa83  call 0xa980e0 <CGameUI::mapToFunctions(CEGUI::Window*)>
//
//  Demangled names, parameter types and constness come from the call-site
//  comments in input/original.asm; they are the ELF's own symbol text, not a
//  reconstruction.  [A] for the names and arities.
//
//      void convertToScreenScale(CEGUI::Window* window, bool second);
//      void mapToFunctions(CEGUI::Window* window);
//
//  CEGUI::Window must be visible; GameUI.h currently forward-declares only
//  CEGUI::Image inside `namespace CEGUI`, so add `class Window;` there.

// ----------------------------------------------------------------------------
//  2. CSceneNodeObject  (input/project-headers/SceneNodeObject.h, also partial)
// ----------------------------------------------------------------------------
//  createMenus() reaches the generic model's Ogre::Entity and then calls
//  Ogre::Entity::getMesh() on it:
//
//    b6ee12  mov 0x90(%rbx),%rax          ; m_pPositionableObject
//    b6eded  mov 0x60(%rax),%rdi          ; <- the Ogre::Entity*
//    b6edf1  call 555158 <Ogre::Entity::getMesh() const@plt>
//    b6edf6  mov 0x8(%rax),%rdi           ; &Mesh::mMeshBoundingBox
//    b6edfa  lea 0x3980(%rsp),%rsi
//    b6ee02  mov $0x1,%edx                 ; autogenerate = true
//    b6ee07  call 5557c8 <Ogre::Mesh::_setBounds(AxisAlignedBox const&, bool)@plt>
//
//  +0x60 on a CGenericModel is CSceneNodeObject::m_pEntity, and that is not a
//  guess - it is forced by the exported CPositionableObject layout in
//  input/supervisor-verification/sdk-layout-facts.json (m_vPosition at 132 =
//  0x84) walked backwards through the declared member order:
//
//      CRunicCore              0x00 vptr, 0x08 m_pSafePointers        -> 0x10
//      CEditorBaseObject       0x10 m_iGuid                          0x18 m_iParentGuid
//                              0x20 m_iOriginalGuid                  0x28 m_iParentHierarchyHashCode
//                              0x30 m_bHashFromOriginalGuid + pad    0x38 m_pDescriptor
//                              0x40 m_sName (std::wstring, 8 bytes)  0x48 m_pSceneOwner
//                              0x50 m_pParentPositionableObject      -> 0x58
//      CSceneNodeObject        0x58 m_pSceneNode
//                              0x60 m_pEntity                       <- the listing's +0x60
//                              0x68 m_pResourceManager               0x70 m_pParentSceneNode
//                              0x78 m_pSceneManager                  0x80 m_bKeepParent
//                              0x81 m_bVisible                       0x82 m_bEnabled
//                                                                    -> 0x88
//      CPositionableObject     0x84 m_vPosition   <-- EXPORTED at 132.  Chain closes exactly.
//
//  That 8-byte std::string/std::wstring is independently confirmed twice: the
//  CFileInfo object the listing default-constructs at 0x3950 has m_sModName at
//  +0, m_sResourceName at +8, m_sPath at +0x10, m_eFormat at +0x18 (the
//  listing stores 4 == FILE_FORMAT_UNKNOWN), m_eLocation at +0x1c (3 ==
//  FILE_LOCATION_NONE), m_sResourceGroup at +0x20 and m_bExists at +0x28;
//  and sdk-layout-facts types CGenericModel::m_sModelPath as std::wstring of
//  size 8.
//
//  Only the NAME is not recovered: the partial header exposes getSceneNode()
//  and getResourceManager() but no entity accessor.  Add the accessor that
//  matches the existing style.  [B] name, [A] offset and return type.
//
//      Ogre::Entity* getEntity() const   { return m_pEntity; }
//
// ----------------------------------------------------------------------------
//  3. Not an addition, but worth stating: Ogre::Mesh::_setBounds
// ----------------------------------------------------------------------------
//  Stock Ogre 1.x declares `protected: void _setBounds(const AxisAlignedBox&,
//  bool autogenerate = false);`.  The original calls it from game code, so the
//  shipped Ogre either exposes it or befriend the game.  No Ogre declaration is
//  proposed here: Ogre headers are not in the supplied inputs and inventing
//  one would change a third-party ABI.  If the supervisor's Ogre has it
//  protected, MerchantMenu.cpp line for `getMesh()->_setBounds(...)` needs the
//  real visibility decision, not a local workaround.
// ----------------------------------------------------------------------------

#endif