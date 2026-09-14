/* Targeted Ghidra class export.
   namespace=CStashMenu
   Treat pseudocode as navigation evidence. */


/* address=00bee360
   symbol=CStashMenu::equipmentPickedUp */

/* non-virtual thunk to CStashMenu::equipmentPickedUp(CEquipment*) */

void __thiscall CStashMenu::equipmentPickedUp(CStashMenu *this,CEquipment *param_1)

{
  equipmentPickedUp((CEquipment *)(this + -0x10));
  return;
}

/* address=00bee370
   symbol=CStashMenu::equipmentPickedUp */

/* CStashMenu::equipmentPickedUp(CEquipment*) */

void CStashMenu::equipmentPickedUp(CEquipment *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x00bee377. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)param_1 + 0x48))();
  return;
}

/* address=00bee380
   symbol=CStashMenu::equipmentDropped */

/* non-virtual thunk to CStashMenu::equipmentDropped(CEquipment*) */

void __thiscall CStashMenu::equipmentDropped(CStashMenu *this,CEquipment *param_1)

{
  equipmentDropped((CEquipment *)(this + -0x10));
  return;
}

/* address=00bee390
   symbol=CStashMenu::equipmentDropped */

/* CStashMenu::equipmentDropped(CEquipment*) */

void CStashMenu::equipmentDropped(CEquipment *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x00bee397. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)param_1 + 0x48))();
  return;
}

/* address=00bee3a0
   symbol=CStashMenu::equipmentEquipped */

/* non-virtual thunk to CStashMenu::equipmentEquipped(CEquipment*) */

void __thiscall CStashMenu::equipmentEquipped(CStashMenu *this,CEquipment *param_1)

{
  equipmentEquipped((CEquipment *)(this + -0x10));
  return;
}

/* address=00bee3b0
   symbol=CStashMenu::equipmentEquipped */

/* CStashMenu::equipmentEquipped(CEquipment*) */

void CStashMenu::equipmentEquipped(CEquipment *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x00bee3b7. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)param_1 + 0x48))();
  return;
}

/* address=00bee3c0
   symbol=CStashMenu::equipmentUnequipped */

/* non-virtual thunk to CStashMenu::equipmentUnequipped(CEquipment*) */

void __thiscall CStashMenu::equipmentUnequipped(CStashMenu *this,CEquipment *param_1)

{
  equipmentUnequipped((CEquipment *)(this + -0x10));
  return;
}

/* address=00bee3d0
   symbol=CStashMenu::equipmentUnequipped */

/* CStashMenu::equipmentUnequipped(CEquipment*) */

void CStashMenu::equipmentUnequipped(CEquipment *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x00bee3d7. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)param_1 + 0x48))();
  return;
}

/* address=00bee3e0
   symbol=CStashMenu::equipmentUsed */

/* non-virtual thunk to CStashMenu::equipmentUsed(CEquipment*) */

void __thiscall CStashMenu::equipmentUsed(CStashMenu *this,CEquipment *param_1)

{
  equipmentUsed((CEquipment *)(this + -0x10));
  return;
}

/* address=00bee3f0
   symbol=CStashMenu::equipmentUsed */

/* CStashMenu::equipmentUsed(CEquipment*) */

void CStashMenu::equipmentUsed(CEquipment *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x00bee3f7. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)param_1 + 0x48))();
  return;
}

/* address=00bee400
   symbol=CStashMenu::inventoryDestroyed */

/* non-virtual thunk to CStashMenu::inventoryDestroyed() */

void __thiscall CStashMenu::inventoryDestroyed(CStashMenu *this)

{
  inventoryDestroyed();
  return;
}

/* address=00bee410
   symbol=CStashMenu::inventoryDestroyed */

/* CStashMenu::inventoryDestroyed() */

void CStashMenu::inventoryDestroyed(void)

{
  return;
}

/* address=00bee420
   symbol=CStashMenu::handle_ItemClick */

/* CStashMenu::handle_ItemClick(CEGUI::EventArgs const&) */

undefined8 __thiscall CStashMenu::handle_ItemClick(CStashMenu *this,EventArgs *param_1)

{
  undefined4 uVar1;

  if (*(long *)(param_1 + 0x10) != 0) {
    uVar1 = **(undefined4 **)(*(long *)(param_1 + 0x10) + 0x1d8);
    if (*(int *)(param_1 + 0x28) == 0) {
      *(undefined4 *)(this + 0x3400) = uVar1;
      return 1;
    }
    if (*(int *)(param_1 + 0x28) == 1) {
      *(undefined4 *)(this + 0x3404) = uVar1;
      return 1;
    }
  }
  return 1;
}

/* address=00bee470
   symbol=CStashMenu::handle_MouseThrough */

/* CStashMenu::handle_MouseThrough(CEGUI::EventArgs const&) */

undefined8 CStashMenu::handle_MouseThrough(EventArgs *param_1)

{
  param_1[0x3420] = (EventArgs)0x0;
  return 1;
}

/* address=00bee480
   symbol=CStashMenu::handle_onClick */

/* CStashMenu::handle_onClick(CEGUI::EventArgs const&) */

undefined8 __thiscall CStashMenu::handle_onClick(CStashMenu *this,EventArgs *param_1)

{
  undefined8 uVar1;

  if ((*(int *)(param_1 + 0x28) == 0) && (*(long *)(param_1 + 0x10) != 0)) {
                    /* WARNING: Could not recover jumptable at 0x00bee4a3. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(*(long *)this + 0x98))
                      (this,**(undefined4 **)(*(long *)(param_1 + 0x10) + 0x1d8));
    return uVar1;
  }
  return 1;
}

/* address=00bee4b0
   symbol=CStashMenu::setPetTab */

/* CStashMenu::setPetTab(int) */

void __thiscall CStashMenu::setPetTab(CStashMenu *this,int param_1)

{
                    /* WARNING: Could not recover jumptable at 0x00bee4bd. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)this + 0x98))(this,param_1 + 0xe);
  return;
}

/* address=00bee4c0
   symbol=CStashMenu::handle_PetItemClick */

/* CStashMenu::handle_PetItemClick(CEGUI::EventArgs const&) */

undefined8 __thiscall CStashMenu::handle_PetItemClick(CStashMenu *this,EventArgs *param_1)

{
  undefined4 uVar1;

  if (*(long *)(param_1 + 0x10) != 0) {
    uVar1 = **(undefined4 **)(*(long *)(param_1 + 0x10) + 0x1d8);
    if (*(int *)(param_1 + 0x28) == 0) {
      *(undefined4 *)(this + 0x33f8) = uVar1;
      return 1;
    }
    if (*(int *)(param_1 + 0x28) == 1) {
      *(undefined4 *)(this + 0x33fc) = uVar1;
      return 1;
    }
  }
  return 1;
}

/* address=00bee510
   symbol=CStashMenu::handle_PetMouseOut */

/* CStashMenu::handle_PetMouseOut(CEGUI::EventArgs const&) */

undefined8 __thiscall CStashMenu::handle_PetMouseOut(CStashMenu *this,EventArgs *param_1)

{
  long *plVar1;
  char cVar2;
  long lVar3;

  plVar1 = *(long **)(*(long *)(this + 0x58) + 0x648);
  if ((((*(long *)(*(long *)(this + 0x58) + 0x650) - (long)plVar1 >> 3 != 0) &&
       (lVar3 = *plVar1, lVar3 != 0)) && (*(long *)(param_1 + 0x10) != 0)) &&
     (lVar3 = CInventory::getEquipmentInSlot
                        (*(CInventory **)(lVar3 + 0x490),
                         **(uint **)(*(long *)(param_1 + 0x10) + 0x1d8)),
     lVar3 == *(long *)(this + 0x3408))) {
    *(undefined8 *)(this + 0x3408) = 0;
    if ((*(CBaseUnit **)(*(long *)(this + 0x70) + 0xb8) != (CBaseUnit *)0x0) &&
       (cVar2 = CBaseUnit::ISA(*(CBaseUnit **)(*(long *)(this + 0x70) + 0xb8),0x78), cVar2 != '\0'))
    {
      return 1;
    }
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x30),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x38),0));
  }
  return 1;
}

/* address=00bee5c0
   symbol=CStashMenu::onClick */

/* CStashMenu::onClick(ELayoutFunction) */

undefined8 __thiscall CStashMenu::onClick(CStashMenu *this,int param_2)

{
  undefined1 uVar1;

  if (this[0x60] == (CStashMenu)0x0) {
    return 1;
  }
  if (param_2 == 0xf) {
    CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x33e0),0));
    CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x33e8),0));
    CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x33f0),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x33c8),0));
    uVar1 = (undefined1)*(undefined8 *)(this + 0x33d0);
  }
  else {
    if (param_2 == 0x10) {
      CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x33e0),0));
      CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x33e8),0));
      CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x33f0),0));
      CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x33c8),0));
      CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x33d0),0));
      CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x33d8),0));
      (**(code **)(*(long *)this + 0x48))(this);
      return 1;
    }
    if (param_2 != 0xe) {
      return 1;
    }
    CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x33e0),0));
    CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x33e8),0));
    CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x33f0),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x33c8),0));
    uVar1 = (undefined1)*(undefined8 *)(this + 0x33d0);
  }
  CEGUI::Window::setVisible((bool)uVar1);
  CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x33d8),0));
  (**(code **)(*(long *)this + 0x48))(this);
  return 1;
}

/* address=00bee710
   symbol=CStashMenu::handle_MouseOut */

/* CStashMenu::handle_MouseOut(CEGUI::EventArgs const&) */

undefined8 __thiscall CStashMenu::handle_MouseOut(CStashMenu *this,EventArgs *param_1)

{
  uint uVar1;
  char cVar2;
  long lVar3;
  CInventory *this_00;

  if ((*(long *)(param_1 + 0x10) != 0) && (*(CBaseUnit **)(this + 0x50) != (CBaseUnit *)0x0)) {
    uVar1 = **(uint **)(*(long *)(param_1 + 0x10) + 0x1d8);
    cVar2 = CBaseUnit::ISA(*(CBaseUnit **)(this + 0x50),0xaa);
    if (cVar2 == '\0') {
      this_00 = *(CInventory **)(*(long *)(this + 0x50) + 0x490);
    }
    else {
      lVar3 = CSharedStash::getSingleton();
      this_00 = *(CInventory **)(lVar3 + 0x10);
    }
    lVar3 = CInventory::getEquipmentInSlot(this_00,uVar1);
    if (lVar3 == *(long *)(this + 0x3408)) {
      *(undefined8 *)(this + 0x3408) = 0;
      if ((*(CBaseUnit **)(*(long *)(this + 0x70) + 0xb8) != (CBaseUnit *)0x0) &&
         (cVar2 = CBaseUnit::ISA(*(CBaseUnit **)(*(long *)(this + 0x70) + 0xb8),0x78), cVar2 != '\0'
         )) {
        return 1;
      }
      CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x30),0));
      CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x38),0));
    }
  }
  return 1;
}

/* address=00bee7e0
   symbol=CStashMenu::processInput */

/* CStashMenu::processInput(void*, float, bool) */

bool CStashMenu::processInput(void *param_1,float param_2,bool param_3)

{
  CBaseUnit *pCVar1;
  char cVar2;
  char in_DL;
  bool bVar3;

  if (in_DL == '\0') {
    *(undefined8 *)((long)param_1 + 0x3408) = 0;
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)((long)param_1 + 0x30),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)((long)param_1 + 0x38),0));
    cVar2 = CEGUI::Window::isChild(*(Window **)((long)param_1 + 0x28));
    if (cVar2 != '\0') {
      CEGUI::Window::removeChildWindow(*(Window **)((long)param_1 + 0x28));
      return true;
    }
    cVar2 = CEGUI::Window::isChild(*(Window **)((long)param_1 + 0x40));
    if (cVar2 == '\0') {
      return true;
    }
    CEGUI::Window::removeChildWindow(*(Window **)((long)param_1 + 0x40));
    return true;
  }
  bVar3 = *(char *)((long)param_1 + 0x62) != '\0';
  if (bVar3) {
    param_2 = (float)(**(code **)(*(long *)param_1 + 0x40))(param_1,0);
    *(undefined1 *)((long)param_1 + 0x62) = 0;
  }
  if ((((*(long *)((long)param_1 + 0x50) == 0) ||
       (cVar2 = CBaseUnit::ISA((CBaseUnit *)param_2,*(long *)((long)param_1 + 0x50),0x7f),
       cVar2 != '\0')) ||
      (pCVar1 = *(CBaseUnit **)(*(long *)((long)param_1 + 0x70) + 0xb8), pCVar1 == (CBaseUnit *)0x0)
      ) || (cVar2 = CBaseUnit::ISA(pCVar1,0x78), cVar2 == '\0')) {
    if (*(long *)((long)param_1 + 0x3408) != 0) {
      if (*(char *)(*(long *)((long)param_1 + 0x3408) + 0x198) == '\0') goto LAB_00bee86b;
      *(undefined8 *)((long)param_1 + 0x3408) = 0;
    }
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)((long)param_1 + 0x30),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)((long)param_1 + 0x38),0));
    cVar2 = *(char *)((long)param_1 + 0x3420);
  }
  else {
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)((long)param_1 + 0x38),0));
    CEGUI::Window::moveToFront();
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)((long)param_1 + 0x30),0));
    CEGUI::Window::moveToFront();
LAB_00bee86b:
    cVar2 = *(char *)((long)param_1 + 0x3420);
  }
  if (cVar2 == '\0') {
    cVar2 = CEGUI::Window::isChild(*(Window **)((long)param_1 + 0x28));
    if (cVar2 == '\0') {
      cVar2 = CEGUI::Window::isChild(*(Window **)((long)param_1 + 0x40));
      if (cVar2 != '\0') {
        CEGUI::Window::removeChildWindow(*(Window **)((long)param_1 + 0x40));
      }
    }
    else {
      CEGUI::Window::removeChildWindow(*(Window **)((long)param_1 + 0x28));
    }
  }
  *(undefined4 *)((long)param_1 + 0x3400) = 0xffffffff;
  *(undefined4 *)((long)param_1 + 0x3404) = 0xffffffff;
  *(undefined4 *)((long)param_1 + 0x33f8) = 0xffffffff;
  *(undefined4 *)((long)param_1 + 0x33fc) = 0xffffffff;
  return !bVar3;
}

/* address=00bee9f0
   symbol=CStashMenu::setPlayer */

/* CStashMenu::setPlayer(CCharacter*) */

void __thiscall CStashMenu::setPlayer(CStashMenu *this,CCharacter *param_1)

{
  long lVar1;

  lVar1 = *(long *)(this + 0x58);
  if (((lVar1 != 0) && (*(long *)(lVar1 + 0x650) - (long)*(long **)(lVar1 + 0x648) >> 3 != 0)) &&
     (lVar1 = **(long **)(lVar1 + 0x648), lVar1 != 0)) {
    CInventory::removeListener(*(CInventory **)(lVar1 + 0x490),(iInventoryListener *)(this + 0x10));
  }
  *(CCharacter **)(this + 0x58) = param_1;
  if (((param_1 != (CCharacter *)0x0) &&
      (*(long *)(param_1 + 0x650) - (long)*(long **)(param_1 + 0x648) >> 3 != 0)) &&
     (lVar1 = **(long **)(param_1 + 0x648), lVar1 != 0)) {
    CInventory::addListener(*(CInventory **)(lVar1 + 0x490),(iInventoryListener *)(this + 0x10));
    return;
  }
  return;
}

/* address=00beea90
   symbol=CStashMenu::setOwner */

/* CStashMenu::setOwner(CCharacter*) */

void __thiscall CStashMenu::setOwner(CStashMenu *this,CCharacter *param_1)

{
  long *plVar1;
  char cVar2;
  long lVar3;
  CBaseUnit *pCVar4;
  CInventory *pCVar5;

  pCVar4 = (CBaseUnit *)param_1;
  if (*(CCharacter **)(this + 0x50) != param_1) {
    (**(code **)(*(long *)this + 0x90))(this);
    pCVar4 = *(CBaseUnit **)(this + 0x50);
  }
  if (pCVar4 != (CBaseUnit *)0x0) {
    cVar2 = CBaseUnit::ISA(pCVar4,0xaa);
    if (cVar2 == '\0') {
LAB_00beeacc:
      pCVar5 = *(CInventory **)(*(long *)(this + 0x50) + 0x490);
    }
    else {
      lVar3 = CSharedStash::getSingleton();
      if (lVar3 == 0) goto LAB_00beeacc;
      lVar3 = CSharedStash::getSingleton();
      pCVar5 = *(CInventory **)(lVar3 + 0x10);
    }
    if (pCVar5 != (CInventory *)0x0) {
      CInventory::removeListener(pCVar5,(iInventoryListener *)(this + 0x10));
    }
  }
  *(CCharacter **)(this + 0x50) = param_1;
  if (param_1 == (CCharacter *)0x0) goto LAB_00beeb23;
  cVar2 = CBaseUnit::ISA((CBaseUnit *)param_1,0xaa);
  if (cVar2 == '\0') {
LAB_00beeb03:
    pCVar5 = *(CInventory **)(*(long *)(this + 0x50) + 0x490);
    this[0x3421] = (CStashMenu)0x0;
  }
  else {
    lVar3 = CSharedStash::getSingleton();
    if (lVar3 == 0) goto LAB_00beeb03;
    lVar3 = CSharedStash::getSingleton();
    pCVar5 = *(CInventory **)(lVar3 + 0x10);
    this[0x3421] = (CStashMenu)0x1;
  }
  if (pCVar5 != (CInventory *)0x0) {
    CInventory::addListener(pCVar5,(iInventoryListener *)(this + 0x10));
  }
LAB_00beeb23:
  lVar3 = *(long *)(this + 0x58);
  if (((lVar3 != 0) && (*(long *)(lVar3 + 0x650) - (long)*(long **)(lVar3 + 0x648) >> 3 != 0)) &&
     (lVar3 = **(long **)(lVar3 + 0x648), lVar3 != 0)) {
    CInventory::removeListener(*(CInventory **)(lVar3 + 0x490),(iInventoryListener *)(this + 0x10));
    lVar3 = 0;
    plVar1 = *(long **)(*(long *)(this + 0x58) + 0x648);
    if (*(long *)(*(long *)(this + 0x58) + 0x650) - (long)plVar1 >> 3 != 0) {
      lVar3 = *plVar1;
    }
    CInventory::addListener(*(CInventory **)(lVar3 + 0x490),(iInventoryListener *)(this + 0x10));
    return;
  }
  return;
}

/* address=00bf5740
   symbol=CStashMenu::_GLOBAL__I_CStashMenu */

/* CStashMenu::CStashMenu(CGameUI&, CSettings&, Ogre::RenderWindow*, Ogre::SceneManager*,
   CEGUI::Window*, CResourceManager*) */

void CStashMenu::_GLOBAL__I_CStashMenu(void)

{
  allocator aStack_27f;
  allocator aStack_27e;
  allocator aStack_27d;
  allocator aStack_27c;
  allocator aStack_27b;
  allocator aStack_27a;
  allocator aStack_279;
  allocator aStack_278;
  allocator aStack_277;
  allocator aStack_276;
  allocator aStack_275;
  allocator aStack_274;
  allocator aStack_273;
  allocator aStack_272;
  allocator aStack_271;
  allocator aStack_270;
  allocator aStack_26f;
  allocator aStack_26e;
  allocator aStack_26d;
  allocator aStack_26c;
  allocator aStack_26b;
  allocator aStack_26a;
  allocator aStack_269;
  allocator aStack_268;
  allocator aStack_267;
  allocator aStack_266;
  allocator aStack_265;
  allocator aStack_264;
  allocator aStack_263;
  allocator aStack_262;
  allocator aStack_261;
  allocator aStack_260;
  allocator aStack_25f;
  allocator aStack_25e;
  allocator aStack_25d;
  allocator aStack_25c;
  allocator aStack_25b;
  allocator aStack_25a;
  allocator aStack_259;
  allocator aStack_258;
  allocator aStack_257;
  allocator aStack_256;
  allocator aStack_255;
  allocator aStack_254;
  allocator aStack_253;
  allocator aStack_252;
  allocator aStack_251;
  allocator aStack_250;
  allocator aStack_24f;
  allocator aStack_24e;
  allocator aStack_24d;
  allocator aStack_24c;
  allocator aStack_24b;
  allocator aStack_24a;
  allocator aStack_249;
  allocator aStack_248;
  allocator aStack_247;
  allocator aStack_246;
  allocator aStack_245;
  allocator aStack_244;
  allocator aStack_243;
  allocator aStack_242;
  allocator aStack_241;
  allocator aStack_240;
  allocator aStack_23f;
  allocator aStack_23e;
  allocator aStack_23d;
  allocator aStack_23c;
  allocator aStack_23b;
  allocator aStack_23a;
  allocator aStack_239;
  allocator aStack_238;
  allocator aStack_237;
  allocator aStack_236;
  allocator aStack_235;
  allocator aStack_234;
  allocator aStack_233;
  allocator aStack_232;
  allocator aStack_231;
  allocator aStack_230;
  allocator aStack_22f;
  allocator aStack_22e;
  allocator aStack_22d;
  allocator aStack_22c;
  allocator aStack_22b;
  allocator aStack_22a;
  allocator aStack_229;
  allocator aStack_228;
  allocator aStack_227;
  allocator aStack_226;
  allocator aStack_225;
  allocator aStack_224;
  allocator aStack_223;
  allocator aStack_222;
  allocator aStack_221;
  allocator aStack_220;
  allocator aStack_21f;
  allocator aStack_21e;
  allocator aStack_21d;
  allocator aStack_21c;
  allocator aStack_21b;
  allocator aStack_21a;
  allocator aStack_219;
  allocator aStack_218;
  allocator aStack_217;
  allocator aStack_216;
  allocator aStack_215;
  allocator aStack_214;
  allocator aStack_213;
  allocator aStack_212;
  allocator aStack_211;
  allocator aStack_210;
  allocator aStack_20f;
  allocator aStack_20e;
  allocator aStack_20d;
  allocator aStack_20c;
  allocator aStack_20b;
  allocator aStack_20a;
  allocator aStack_209;
  allocator aStack_208;
  allocator aStack_207;
  allocator aStack_206;
  allocator aStack_205;
  allocator aStack_204;
  allocator aStack_203;
  allocator aStack_202;
  allocator aStack_201;
  allocator aStack_200;
  allocator aStack_1ff;
  allocator aStack_1fe;
  allocator aStack_1fd;
  allocator aStack_1fc;
  allocator aStack_1fb;
  allocator aStack_1fa;
  allocator aStack_1f9;
  allocator aStack_1f8;
  allocator aStack_1f7;
  allocator aStack_1f6;
  allocator aStack_1f5;
  allocator aStack_1f4;
  allocator aStack_1f3;
  allocator aStack_1f2;
  allocator aStack_1f1;
  allocator aStack_1f0;
  allocator aStack_1ef;
  allocator aStack_1ee;
  allocator aStack_1ed;
  allocator aStack_1ec;
  allocator aStack_1eb;
  allocator aStack_1ea;
  allocator aStack_1e9;
  allocator aStack_1e8;
  allocator aStack_1e7;
  allocator aStack_1e6;
  allocator aStack_1e5;
  allocator aStack_1e4;
  allocator aStack_1e3;
  allocator aStack_1e2;
  allocator aStack_1e1;
  allocator aStack_1e0;
  allocator aStack_1df;
  allocator aStack_1de;
  allocator aStack_1dd;
  allocator aStack_1dc;
  allocator aStack_1db;
  allocator aStack_1da;
  allocator aStack_1d9;
  allocator aStack_1d8;
  allocator aStack_1d7;
  allocator aStack_1d6;
  allocator aStack_1d5;
  allocator aStack_1d4;
  allocator aStack_1d3;
  allocator aStack_1d2;
  allocator aStack_1d1;
  allocator aStack_1d0;
  allocator aStack_1cf;
  allocator aStack_1ce;
  allocator aStack_1cd;
  allocator aStack_1cc;
  allocator aStack_1cb;
  allocator aStack_1ca;
  allocator aStack_1c9;
  allocator aStack_1c8;
  allocator aStack_1c7;
  allocator aStack_1c6;
  allocator aStack_1c5;
  allocator aStack_1c4;
  allocator aStack_1c3;
  allocator aStack_1c2;
  allocator aStack_1c1;
  allocator aStack_1c0;
  allocator aStack_1bf;
  allocator aStack_1be;
  allocator aStack_1bd;
  allocator aStack_1bc;
  allocator aStack_1bb;
  allocator aStack_1ba;
  allocator aStack_1b9;
  allocator aStack_1b8;
  allocator aStack_1b7;
  allocator aStack_1b6;
  allocator aStack_1b5;
  allocator aStack_1b4;
  allocator aStack_1b3;
  allocator aStack_1b2;
  allocator aStack_1b1;
  allocator aStack_1b0;
  allocator aStack_1af;
  allocator aStack_1ae;
  allocator aStack_1ad;
  allocator aStack_1ac;
  allocator aStack_1ab;
  allocator aStack_1aa;
  allocator aStack_1a9;
  allocator aStack_1a8;
  allocator aStack_1a7;
  allocator aStack_1a6;
  allocator aStack_1a5;
  allocator aStack_1a4;
  allocator aStack_1a3;
  allocator aStack_1a2;
  allocator aStack_1a1;
  allocator aStack_1a0;
  allocator aStack_19f;
  allocator aStack_19e;
  allocator aStack_19d;
  allocator aStack_19c;
  allocator aStack_19b;
  allocator aStack_19a;
  allocator aStack_199;
  allocator aStack_198;
  allocator aStack_197;
  allocator aStack_196;
  allocator aStack_195;
  allocator aStack_194;
  allocator aStack_193;
  allocator aStack_192;
  allocator aStack_191;
  allocator aStack_190;
  allocator aStack_18f;
  allocator aStack_18e;
  allocator aStack_18d;
  allocator aStack_18c;
  allocator aStack_18b;
  allocator aStack_18a;
  allocator aStack_189;
  allocator aStack_188;
  allocator aStack_187;
  allocator aStack_186;
  allocator aStack_185;
  allocator aStack_184;
  allocator aStack_183;
  allocator aStack_182;
  allocator aStack_181;
  allocator aStack_180;
  allocator aStack_17f;
  allocator aStack_17e;
  allocator aStack_17d;
  allocator aStack_17c;
  allocator aStack_17b;
  allocator aStack_17a;
  allocator aStack_179;
  allocator aStack_178;
  allocator aStack_177;
  allocator aStack_176;
  allocator aStack_175;
  allocator aStack_174;
  allocator aStack_173;
  allocator aStack_172;
  allocator aStack_171;
  allocator aStack_170;
  allocator aStack_16f;
  allocator aStack_16e;
  allocator aStack_16d;
  allocator aStack_16c;
  allocator aStack_16b;
  allocator aStack_16a;
  allocator aStack_169;
  allocator aStack_168;
  allocator aStack_167;
  allocator aStack_166;
  allocator aStack_165;
  allocator aStack_164;
  allocator aStack_163;
  allocator aStack_162;
  allocator aStack_161;
  allocator aStack_160;
  allocator aStack_15f;
  allocator aStack_15e;
  allocator aStack_15d;
  allocator aStack_15c;
  allocator aStack_15b;
  allocator aStack_15a;
  allocator aStack_159;
  allocator aStack_158;
  allocator aStack_157;
  allocator aStack_156;
  allocator aStack_155;
  allocator aStack_154;
  allocator aStack_153;
  allocator aStack_152;
  allocator aStack_151;
  allocator aStack_150;
  allocator aStack_14f;
  allocator aStack_14e;
  allocator aStack_14d;
  allocator aStack_14c;
  allocator aStack_14b;
  allocator aStack_14a;
  allocator aStack_149;
  allocator aStack_148;
  allocator aStack_147;
  allocator aStack_146;
  allocator aStack_145;
  allocator aStack_144;
  allocator aStack_143;
  allocator aStack_142;
  allocator aStack_141;
  allocator aStack_140;
  allocator aStack_13f;
  allocator aStack_13e;
  allocator aStack_13d;
  allocator aStack_13c;
  allocator aStack_13b;
  allocator aStack_13a;
  allocator aStack_139;
  allocator aStack_138;
  allocator aStack_137;
  allocator aStack_136;
  allocator aStack_135;
  allocator aStack_134;
  allocator aStack_133;
  allocator aStack_132;
  allocator aStack_131;
  allocator aStack_130;
  allocator aStack_12f;
  allocator aStack_12e;
  allocator aStack_12d;
  allocator aStack_12c;
  allocator aStack_12b;
  allocator aStack_12a;
  allocator aStack_129;
  allocator aStack_128;
  allocator aStack_127;
  allocator aStack_126;
  allocator aStack_125;
  allocator aStack_124;
  allocator aStack_123;
  allocator aStack_122;
  allocator aStack_121;
  allocator aStack_120;
  allocator aStack_11f;
  allocator aStack_11e;
  allocator aStack_11d;
  allocator aStack_11c;
  allocator aStack_11b;
  allocator aStack_11a;
  allocator aStack_119;
  allocator aStack_118;
  allocator aStack_117;
  allocator aStack_116;
  allocator aStack_115;
  allocator aStack_114;
  allocator aStack_113;
  allocator aStack_112;
  allocator aStack_111;
  allocator aStack_110;
  allocator aStack_10f;
  allocator aStack_10e;
  allocator aStack_10d;
  allocator aStack_10c;
  allocator aStack_10b;
  allocator aStack_10a;
  allocator aStack_109;
  allocator aStack_108;
  allocator aStack_107;
  allocator aStack_106;
  allocator aStack_105;
  allocator aStack_104;
  allocator aStack_103;
  allocator aStack_102;
  allocator aStack_101;
  allocator aStack_100;
  allocator aStack_ff;
  allocator aStack_fe;
  allocator aStack_fd;
  allocator aStack_fc;
  allocator aStack_fb;
  allocator aStack_fa;
  allocator aStack_f9;
  allocator aStack_f8;
  allocator aStack_f7;
  allocator aStack_f6;
  allocator aStack_f5;
  allocator aStack_f4;
  allocator aStack_f3;
  allocator aStack_f2;
  allocator aStack_f1;
  allocator aStack_f0;
  allocator aStack_ef;
  allocator aStack_ee;
  allocator aStack_ed;
  allocator aStack_ec;
  allocator aStack_eb;
  allocator aStack_ea;
  allocator aStack_e9;
  allocator aStack_e8;
  allocator aStack_e7;
  allocator aStack_e6;
  allocator aStack_e5;
  allocator aStack_e4;
  allocator aStack_e3;
  allocator aStack_e2;
  allocator aStack_e1;
  allocator aStack_e0;
  allocator aStack_df;
  allocator aStack_de;
  allocator aStack_dd;
  allocator aStack_dc;
  allocator aStack_db;
  allocator aStack_da;
  allocator aStack_d9;
  allocator aStack_d8;
  allocator aStack_d7;
  allocator aStack_d6;
  allocator aStack_d5;
  allocator aStack_d4;
  allocator aStack_d3;
  allocator aStack_d2;
  allocator aStack_d1;
  allocator aStack_d0;
  allocator aStack_cf;
  allocator aStack_ce;
  allocator aStack_cd;
  allocator aStack_cc;
  allocator aStack_cb;
  allocator aStack_ca;
  allocator aStack_c9;
  allocator aStack_c8;
  allocator aStack_c7;
  allocator aStack_c6;
  allocator aStack_c5;
  allocator aStack_c4;
  allocator aStack_c3;
  allocator aStack_c2;
  allocator aStack_c1;
  allocator aStack_c0;
  allocator aStack_bf;
  allocator aStack_be;
  allocator aStack_bd;
  allocator aStack_bc;
  allocator aStack_bb;
  allocator aStack_ba;
  allocator aStack_b9;
  allocator aStack_b8;
  allocator aStack_b7;
  allocator aStack_b6;
  allocator aStack_b5;
  allocator aStack_b4;
  allocator aStack_b3;
  allocator aStack_b2;
  allocator aStack_b1;
  allocator aStack_b0;
  allocator aStack_af;
  allocator aStack_ae;
  allocator aStack_ad;
  allocator aStack_ac;
  allocator aStack_ab;
  allocator aStack_aa;
  allocator aStack_a9;
  allocator aStack_a8;
  allocator aStack_a7;
  allocator aStack_a6;
  allocator aStack_a5;
  allocator aStack_a4;
  allocator aStack_a3;
  allocator aStack_a2;
  allocator aStack_a1;
  allocator aStack_a0;
  allocator aStack_9f;
  allocator aStack_9e;
  allocator aStack_9d;
  allocator aStack_9c;
  allocator aStack_9b;
  allocator aStack_9a;
  allocator aStack_99;
  allocator aStack_98;
  allocator aStack_97;
  allocator aStack_96;
  allocator aStack_95;
  allocator aStack_94;
  allocator aStack_93;
  allocator aStack_92;
  allocator aStack_91;
  allocator aStack_90;
  allocator aStack_8f;
  allocator aStack_8e;
  allocator aStack_8d;
  allocator aStack_8c;
  allocator aStack_8b;
  allocator aStack_8a;
  allocator aStack_89;
  allocator aStack_88;
  allocator aStack_87;
  allocator aStack_86;
  allocator aStack_85;
  allocator aStack_84;
  allocator aStack_83;
  allocator aStack_82;
  allocator aStack_81;
  allocator aStack_80;
  allocator aStack_7f;
  allocator aStack_7e;
  allocator aStack_7d;
  allocator aStack_7c;
  allocator aStack_7b;
  allocator aStack_7a;
  allocator aStack_79;
  allocator aStack_78;
  allocator aStack_77;
  allocator aStack_76;
  allocator aStack_75;
  allocator aStack_74;
  allocator aStack_73;
  allocator aStack_72;
  allocator aStack_71;
  allocator aStack_70;
  allocator aStack_6f;
  allocator aStack_6e;
  allocator aStack_6d;
  allocator aStack_6c;
  allocator aStack_6b;
  allocator aStack_6a;
  allocator aStack_69;
  allocator aStack_68;
  allocator aStack_67;
  allocator aStack_66;
  allocator aStack_65;
  allocator aStack_64;
  allocator aStack_63;
  allocator aStack_62;
  allocator aStack_61;
  allocator aStack_60;
  allocator aStack_5f;
  allocator aStack_5e;
  allocator aStack_5d;
  allocator aStack_5c;
  allocator aStack_5b;
  allocator aStack_5a;
  allocator aStack_59;
  allocator aStack_58;
  allocator aStack_57;
  allocator aStack_56;
  allocator aStack_55;
  allocator aStack_54;
  allocator aStack_53;
  allocator aStack_52;
  allocator aStack_51;
  allocator aStack_50;
  allocator aStack_4f;
  allocator aStack_4e;
  allocator aStack_4d;
  allocator aStack_4c;
  allocator aStack_4b;
  allocator aStack_4a;
  allocator aStack_49;
  allocator aStack_48;
  allocator aStack_47;
  allocator aStack_46;
  allocator aStack_45;
  allocator aStack_44;
  allocator aStack_43;
  allocator aStack_42;
  allocator aStack_41;
  allocator aStack_40;
  allocator aStack_3f;
  allocator aStack_3e;
  allocator aStack_3d;
  allocator aStack_3c;
  allocator aStack_3b;
  allocator aStack_3a;
  allocator aStack_39;
  allocator aStack_38;
  allocator aStack_37;
  allocator aStack_36;
  allocator aStack_35;
  allocator aStack_34;
  allocator aStack_33;
  allocator aStack_32;
  allocator aStack_31;
  allocator aStack_30;
  allocator aStack_2f;
  allocator aStack_2e;
  allocator aStack_2d;
  allocator aStack_2c;
  allocator aStack_2b;
  allocator aStack_2a;
  allocator aStack_29;
  allocator aStack_28;
  allocator aStack_27;
  allocator aStack_26;
  allocator aStack_25;
  allocator aStack_24;
  allocator aStack_23;
  allocator aStack_22;
  allocator aStack_21;
  allocator aStack_20;
  allocator aStack_1f;
  allocator aStack_1e;
  allocator aStack_1d;
  allocator aStack_1c;
  allocator aStack_1b;
  allocator aStack_1a;
  allocator aStack_19;
  allocator aStack_18;
  allocator aStack_17;
  allocator aStack_16;
  allocator aStack_15;
  allocator aStack_14;
  allocator aStack_13;
  allocator aStack_12;
  allocator aStack_11;
  allocator aStack_10;
  allocator aStack_f;
  allocator aStack_e;
  allocator aStack_d;
  allocator aStack_c;
  allocator aStack_b;
  allocator aStack_a;
  allocator aStack_9;

  ::EMPTY_STRING = &DAT_01423a38;
  __cxa_atexit(std::string::~string,&::EMPTY_STRING,&__dso_handle);
  ::EMPTY_WSTRING = &DAT_01424558;
  __cxa_atexit(std::wstring::~wstring,&::EMPTY_WSTRING,&__dso_handle);
  std::ios_base::Init::Init((Init *)&std::__ioinit);
  __cxa_atexit(std::ios_base::Init::~Init,&std::__ioinit,&__dso_handle);
  std::string::string((string *)::KLayoutFunctionNames,"GUIEXITGAME",&aStack_27f);
  std::string::string((string *)(::KLayoutFunctionNames + 8),"GUIEXITAPPLICATION",&aStack_27e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x10),"GUINEWGAME",&aStack_27d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x18),"GUICONTINUEGAME",&aStack_27c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x20),"GUINEWGAMEMENU",&aStack_27b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x28),"GUICONTINUEGAMEMENU",&aStack_27a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x30),"GUICLOSEMENU",&aStack_279);
  std::string::string((string *)(::KLayoutFunctionNames + 0x38),"GUIBACK",&aStack_278);
  std::string::string((string *)(::KLayoutFunctionNames + 0x40),"GUIDECLINE",&aStack_277);
  std::string::string((string *)(::KLayoutFunctionNames + 0x48),"GUIACCEPT",&aStack_276);
  std::string::string((string *)(::KLayoutFunctionNames + 0x50),"GUIOK",&aStack_275);
  std::string::string((string *)(::KLayoutFunctionNames + 0x58),"GUIPAUSE",&aStack_274);
  std::string::string((string *)(::KLayoutFunctionNames + 0x60),"GUISCROLLUP",&aStack_273);
  std::string::string((string *)(::KLayoutFunctionNames + 0x68),"GUISCROLLDOWN",&aStack_272);
  std::string::string((string *)(::KLayoutFunctionNames + 0x70),"GUISELECT1",&aStack_271);
  std::string::string((string *)(::KLayoutFunctionNames + 0x78),"GUISELECT2",&aStack_270);
  std::string::string((string *)(::KLayoutFunctionNames + 0x80),"GUISELECT3",&aStack_26f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x88),"GUISELECT4",&aStack_26e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x90),"GUISELECT5",&aStack_26d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x98),"GUISELECT6",&aStack_26c);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa0),"GUISELECT7",&aStack_26b);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa8),"GUISELECT8",&aStack_26a);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb0),"GUISELECT9",&aStack_269);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb8),"GUISELECT10",&aStack_268);
  std::string::string((string *)(::KLayoutFunctionNames + 0xc0),"GUISELECT11",&aStack_267);
  std::string::string((string *)(::KLayoutFunctionNames + 200),"GUISELECT12",&aStack_266);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd0),"GUISELECT13",&aStack_265);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd8),"GUISELECT14",&aStack_264);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe0),"GUISELECT15",&aStack_263);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe8),"GUISELECT16",&aStack_262);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf0),"GUISELECT17",&aStack_261);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf8),"GUISELECT18",&aStack_260);
  std::string::string((string *)(::KLayoutFunctionNames + 0x100),"GUISELECT19",&aStack_25f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x108),"GUISELECT20",&aStack_25e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x110),"GUISELECT21",&aStack_25d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x118),"GUISELECT22",&aStack_25c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x120),"GUISELECT23",&aStack_25b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x128),"GUISELECT24",&aStack_25a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x130),"GUISELECT25",&aStack_259);
  std::string::string((string *)(::KLayoutFunctionNames + 0x138),"GUISELECT26",&aStack_258);
  std::string::string((string *)(::KLayoutFunctionNames + 0x140),"GUISELECT27",&aStack_257);
  std::string::string((string *)(::KLayoutFunctionNames + 0x148),"GUISELECT28",&aStack_256);
  std::string::string((string *)(::KLayoutFunctionNames + 0x150),"GUISELECT29",&aStack_255);
  std::string::string((string *)(::KLayoutFunctionNames + 0x158),"GUISELECT30",&aStack_254);
  std::string::string((string *)(::KLayoutFunctionNames + 0x160),"GUISELECT31",&aStack_253);
  std::string::string((string *)(::KLayoutFunctionNames + 0x168),"GUISELECT32",&aStack_252);
  std::string::string((string *)(::KLayoutFunctionNames + 0x170),"GUISELECT33",&aStack_251);
  std::string::string((string *)(::KLayoutFunctionNames + 0x178),"GUISELECT34",&aStack_250);
  std::string::string((string *)(::KLayoutFunctionNames + 0x180),"GUISELECT35",&aStack_24f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x188),"GUISELECT36",&aStack_24e);
  std::string::string((string *)(::KLayoutFunctionNames + 400),"GUISELECT37",&aStack_24d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x198),"GUISELECT38",&aStack_24c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a0),"GUISELECT39",&aStack_24b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a8),"GUISELECT40",&aStack_24a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b0),"GUISELECT41",&aStack_249);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b8),"GUISELECT42",&aStack_248);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c0),"GUISELECT43",&aStack_247);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c8),"GUISELECT44",&aStack_246);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d0),"GUISELECT45",&aStack_245);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d8),"GUISELECT46",&aStack_244);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e0),"GUISELECT47",&aStack_243);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e8),"GUISELECT48",&aStack_242);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f0),"GUISELECT49",&aStack_241);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f8),"GUISELECT50",&aStack_240);
  std::string::string((string *)(::KLayoutFunctionNames + 0x200),"GUISELECTA",&aStack_23f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x208),"GUISELECTB",&aStack_23e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x210),"GUISELECTC",&aStack_23d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x218),"GUISELECTD",&aStack_23c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x220),"GUIFEEDPET",&aStack_23b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x228),"GUIPETPASSIVE",&aStack_23a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x230),"GUIPETAGGRESSIVE",&aStack_239);
  std::string::string((string *)(::KLayoutFunctionNames + 0x238),"GUIPETDEFENSIVE",&aStack_238);
  std::string::string((string *)(::KLayoutFunctionNames + 0x240),"GUITOGGLEINVENTORY",&aStack_237);
  std::string::string((string *)(::KLayoutFunctionNames + 0x248),"GUITOGGLEQUESTS",&aStack_236);
  std::string::string((string *)(::KLayoutFunctionNames + 0x250),"GUITOGGLESTATS",&aStack_235);
  std::string::string((string *)(::KLayoutFunctionNames + 600),"GUITOGGLESKILLS",&aStack_234);
  std::string::string((string *)(::KLayoutFunctionNames + 0x260),"GUITOGGLEPERKS",&aStack_233);
  std::string::string((string *)(::KLayoutFunctionNames + 0x268),"GUITOGGLEJOURNAL",&aStack_232);
  std::string::string((string *)(::KLayoutFunctionNames + 0x270),"GUITOGGLEPET",&aStack_231);
  std::string::string((string *)(::KLayoutFunctionNames + 0x278),"GUITOGGLEAUTOMAP",&aStack_230);
  std::string::string((string *)(::KLayoutFunctionNames + 0x280),"GUITOGGLEOPTIONS",&aStack_22f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x288),"GUITOGGLEITEMNAMES",&aStack_22e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x290),"GUIAUTOMAPZOOMIN",&aStack_22d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x298),"GUIAUTOMAPZOOMOUT",&aStack_22c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a0),"GUILEVELUP",&aStack_22b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a8),"GUISTATSUP",&aStack_22a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b0),"GUISKILLUP",&aStack_229);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b8),"GUIPET1",&aStack_228);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c0),"GUIPET2",&aStack_227);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c8),"GUIPET3",&aStack_226);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d0),"GUIDELETE1",&aStack_225);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d8),"GUIDELETE2",&aStack_224);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e0),"GUIDELETE3",&aStack_223);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e8),"GUIDELETE4",&aStack_222);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f0),"GUISETTINGSMENU",&aStack_221);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f8),"GUIPETSELL",&aStack_220);
  std::string::string((string *)(::KLayoutFunctionNames + 0x300),"NONE",&aStack_21f);
  __cxa_atexit(::__tcf_0,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSOUNDBANK_STRINGS,L"STEP_SOUND",&aStack_21e);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 8),L"STRIKE_SOUND",&aStack_21d);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x10),L"PHYSICALHIT_SOUND",&aStack_21c);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x18),L"ICEHIT_SOUND",&aStack_21b);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x20),L"FIREHIT_SOUND",&aStack_21a);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x28),L"ELECTRICHIT_SOUND",&aStack_219);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x30),L"POISONHIT_SOUND",&aStack_218);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x38),L"SHIELDBLOCK",&aStack_217);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x40),L"BLOCK",&aStack_216);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x48),L"CRITICAL_SOUND",&aStack_215);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x50),L"ATTACK_SOUND",&aStack_214);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x58),L"IDLE_SOUND",&aStack_213)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x60),L"DEATH_SOUND",&aStack_212);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x68),L"ROAR_SOUND",&aStack_211)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x70),L"FLEE_SOUND",&aStack_210)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x78),L"MISS_SOUND",&aStack_20f)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x80),L"FALL_SOUND",&aStack_20e)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x88),L"LAND_SOUND",&aStack_20d)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x90),L"TAKE_SOUND",&aStack_20c)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x98),L"SPAWN_SOUND",&aStack_20b);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa0),L"USE_SOUND",&aStack_20a);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa8),L"EQUIP_SOUND",&aStack_209);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb0),L"OPENMENU_SOUND",&aStack_208);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb8),L"BUY_SOUND",&aStack_207);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xc0),L"ERROR_SOUND",&aStack_206);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 200),L"LEVELUP_SOUND",&aStack_205);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd0),L"EFFORT_SOUND",&aStack_204);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd8),L"SPENDPOINT_SOUND",&aStack_203);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe0),L"PORTALENTER_SOUND",&aStack_202);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe8),L"POERTALEXIT_SOUND",&aStack_201);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf0),L"SKILLASSIGN_SOUND",&aStack_200);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf8),L"QUESTRECEIVED_SOUND",&aStack_1ff);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x100),L"QUESTCOMPLETED_SOUND",&aStack_1fe)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x108),L"LOWMANA_SOUND",&aStack_1fd);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x110),L"MISSILEREFLECT_SOUND",&aStack_1fc)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x118),L"BADEFFECT_SOUND",&aStack_1fb);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x120),L"GOODEFFECT_SOUND",&aStack_1fa);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x128),L"NPCDIALOG_SOUND",&aStack_1f9);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x130),L"NPCGREET",&aStack_1f8);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x138),L"NPCBYE",&aStack_1f7);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x140),L"NPCPURCHASE",&aStack_1f6);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x148),L"NPCSELL",&aStack_1f5);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x150),L"VOICEPETINVENTORYFULL_SOUND",
             &aStack_1f4);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x158),L"VOICEPETDEPARTED_SOUND",
             &aStack_1f3);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x160),L"VOICEPETRETURNED_SOUND",
             &aStack_1f2);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x168),L"VOICEPETFLED_SOUND",&aStack_1f1);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x170),L"VOICEPETLEVELUP_SOUND",&aStack_1f0
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x178),L"VOICEINVENTORYFULL_SOUND",
             &aStack_1ef);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x180),L"VOICEINSUFFICIENTGOLD_SOUND",
             &aStack_1ee);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x188),L"VOICEIMPOSSIBLE_SOUND",&aStack_1ed
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 400),L"VOICECANTCAST_SOUND",&aStack_1ec);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x198),L"VOICECANTCASTHERE_SOUND",
             &aStack_1eb);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a0),L"VOICEHEALTHLOW_SOUND",&aStack_1ea)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a8),L"VOICEMANALOW_SOUND",&aStack_1e9);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b0),L"VOICETRAPSPRUNG_SOUND",&aStack_1e8
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b8),L"VOICEREFRESHED_SOUND",&aStack_1e7)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c0),L"VOICEPOWERFUL_SOUND",&aStack_1e6);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c8),L"VOICEHEALTHY_SOUND",&aStack_1e5);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d0),L"VOICEILL_SOUND",&aStack_1e4);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d8),L"VOICEPOISONED_SOUND",&aStack_1e3);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e0),L"VOICELEVELUP_SOUND",&aStack_1e2);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e8),L"VOICEFAMEUP_SOUND",&aStack_1e1);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f0),L"VOICESKILLUP_SOUND",&aStack_1e0);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f8),L"VOICEFORTUNEGOOD_SOUND",
             &aStack_1df);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x200),L"VOICEFORTUNEBAD_SOUND",&aStack_1de
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x208),L"VOICESPELLLEARNED_SOUND",
             &aStack_1dd);
  ::KSOUNDBANK_STRINGS._528_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_1,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KALIGNMENT_STRINGS,L"NEUTRAL",&aStack_1dc);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 8),L"GOOD",&aStack_1db);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x10),L"EVIL",&aStack_1da);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x18),L"ALL",&aStack_1d9);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x20),L"BERSERK",&aStack_1d8);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x28),L"EVILBERSERK",&aStack_1d7);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x30),L"GOODBERSERK",&aStack_1d6);
  __cxa_atexit(::__tcf_2,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KAITYPE_STRINGS,L"NORMAL",&aStack_1d5);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 8),L"RANGEDDEFENDER",&aStack_1d4);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x10),L"DEFENDER",&aStack_1d3);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x18),L"RANGEDCASTER",&aStack_1d2);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x20),L"CIRCLER",&aStack_1d1);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x28),L"RESURRECTER",&aStack_1d0);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x30),L"DUMMY",&aStack_1cf);
  __cxa_atexit(::__tcf_3,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gDAMAGE_TYPES,L"Physical",&aStack_1ce);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 8),L"Magical",&aStack_1cd);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x10),L"Fire",&aStack_1cc);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x18),L"Ice",&aStack_1cb);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x20),L"Electric",&aStack_1ca);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x28),L"Poison",&aStack_1c9);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x30),L"All",&aStack_1c8);
  __cxa_atexit(::__tcf_4,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::gTARGET_TYPES,L"USER",&aStack_1c7);
  std::wstring::wstring((wstring_conflict *)&DAT_014d3588,L"ITEM",&aStack_1c6);
  __cxa_atexit(::__tcf_5,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSFXTypeName,L"STATIONARYTARGET",&aStack_1c5);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 8),L"STATIONARYOWNER",&aStack_1c4);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x10),L"STATIONARY",&aStack_1c3);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x18),L"STATIONARYPORTAL",&aStack_1c2)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x20),L"BEAM",&aStack_1c1);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x28),L"FOLLOWOWNER",&aStack_1c0);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x30),L"FOLLOWTARGET",&aStack_1bf);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x38),L"PROJECTILELOCATION",&aStack_1be);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x40),L"PROJECTILECHARACTER",&aStack_1bd);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x48),L"PROJECTILELOCATIONERRATIC",&aStack_1bc);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x50),L"PROJECTILECHARACTERERRATIC",&aStack_1bb);
  __cxa_atexit(::__tcf_6,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KCharacterNames,L"NA",&aStack_1ba);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 8),L"NA",&aStack_1b9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x10),L"NA",&aStack_1b8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x18),L"NA",&aStack_1b7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x20),L"NA",&aStack_1b6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x28),L"NA",&aStack_1b5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x30),L"NA",&aStack_1b4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x38),L"NA",&aStack_1b3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x40),L"Bksp",&aStack_1b2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x48),L"Tab",&aStack_1b1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x50),L"NA",&aStack_1b0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x58),L"NA",&aStack_1af);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x60),L"Ctr",&aStack_1ae);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x68),L"Ret",&aStack_1ad);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x70),L"NA",&aStack_1ac);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x78),L"NA",&aStack_1ab);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x80),L"Shift",&aStack_1aa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x88),L"Ctrl",&aStack_1a9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x90),L"Alt",&aStack_1a8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x98),L"Tab",&aStack_1a7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa0),L"NA",&aStack_1a6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa8),L"NA",&aStack_1a5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb0),L"NA",&aStack_1a4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb8),L"NA",&aStack_1a3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xc0),L"NA",&aStack_1a2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 200),L"NA",&aStack_1a1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd0),L"NA",&aStack_1a0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd8),L"NA",&aStack_19f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe0),L"NA",&aStack_19e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe8),L"NA",&aStack_19d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf0),L"NA",&aStack_19c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf8),L"NA",&aStack_19b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x100),L"space",&aStack_19a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x108),L"pgup",&aStack_199);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x110),L"pgdn",&aStack_198);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x118),L"end",&aStack_197);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x120),L"home",&aStack_196);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x128),L"left arrow",&aStack_195);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x130),L"up arrow",&aStack_194);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x138),L"right arrow",&aStack_193);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x140),L"down arrow",&aStack_192);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x148),L")",&aStack_191);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x150),L"*",&aStack_190);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x158),L"+",&aStack_18f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x160),L",",&aStack_18e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x168),L"ins",&aStack_18d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x170),L"del",&aStack_18c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x178),L"/",&aStack_18b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x180),L"0",&aStack_18a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x188),L"1",&aStack_189);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 400),L"2",&aStack_188);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x198),L"3",&aStack_187);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a0),L"4",&aStack_186);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a8),L"5",&aStack_185);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b0),L"6",&aStack_184);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b8),L"7",&aStack_183);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c0),L"8",&aStack_182);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c8),L"9",&aStack_181);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d0),L":",&aStack_180);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d8),L";",&aStack_17f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e0),L"<",&aStack_17e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e8),L"=",&aStack_17d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f0),L">",&aStack_17c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f8),L"?",&aStack_17b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x200),L"@",&aStack_17a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x208),L"a",&aStack_179);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x210),L"b",&aStack_178);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x218),L"c",&aStack_177);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x220),L"d",&aStack_176);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x228),L"e",&aStack_175);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x230),L"NA",&aStack_174);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x238),L"g",&aStack_173);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x240),L"h",&aStack_172);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x248),L"i",&aStack_171);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x250),L"j",&aStack_170);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 600),L"k",&aStack_16f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x260),L"l",&aStack_16e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x268),L"m",&aStack_16d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x270),L"n",&aStack_16c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x278),L"o",&aStack_16b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x280),L"p",&aStack_16a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x288),L"NA",&aStack_169);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x290),L"r",&aStack_168);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x298),L"s",&aStack_167);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a0),L"t",&aStack_166);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a8),L"u",&aStack_165);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b0),L"v",&aStack_164);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b8),L"w",&aStack_163);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c0),L"x",&aStack_162);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c8),L"y",&aStack_161);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d0),L"z",&aStack_160);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d8),L"[",&aStack_15f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e0),L"\\",&aStack_15e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e8),L"]",&aStack_15d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f0),L"^",&aStack_15c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f8),L"_",&aStack_15b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x300),L"NUM 0",&aStack_15a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x308),L"NUM 1",&aStack_159);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x310),L"NUM 2",&aStack_158);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x318),L"NUM 3",&aStack_157);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 800),L"NUM 4",&aStack_156);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x328),L"NUM 5",&aStack_155);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x330),L"NUM 6",&aStack_154);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x338),L"NUM 7",&aStack_153);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x340),L"NUM 8",&aStack_152);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x348),L"NUM 9",&aStack_151);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x350),L"*",&aStack_150);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x358),L"+",&aStack_14f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x360),L"NA",&aStack_14e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x368),L"-",&aStack_14d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x370),L"NA",&aStack_14c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x378),L"F1",&aStack_14b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x380),L"F2",&aStack_14a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x388),L"F3",&aStack_149);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x390),L"F4",&aStack_148);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x398),L"F5",&aStack_147);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a0),L"F6",&aStack_146);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a8),L"F7",&aStack_145);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b0),L"F8",&aStack_144);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b8),L"F9",&aStack_143);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c0),L"F10",&aStack_142);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c8),L"F11",&aStack_141);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d0),L"F12",&aStack_140);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d8),L"{",&aStack_13f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3e0),L"|",&aStack_13e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 1000),L"}",&aStack_13d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f0),L"~",&aStack_13c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f8),L";",&aStack_13b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x400),L"=",&aStack_13a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x408),L".",&aStack_139);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x410),L"-",&aStack_138);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x418),L",",&aStack_137);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x420),L"/",&aStack_136);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x428),L"`",&aStack_135);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x430),L"[",&aStack_134);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x438),L"\\",&aStack_133);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x440),L"]",&aStack_132);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x448),L"\'",&aStack_131);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x450),L"NA",&aStack_130);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x458),L"NA",&aStack_12f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x460),L"NA",&aStack_12e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x468),L"NA",&aStack_12d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x470),L"NA",&aStack_12c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x478),L"NA",&aStack_12b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x480),L"NA",&aStack_12a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x488),L"NA",&aStack_129);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x490),L"NA",&aStack_128);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x498),L"NA",&aStack_127);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a0),L"NA",&aStack_126);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a8),L"NA",&aStack_125);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b0),L"NA",&aStack_124);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b8),L"NA",&aStack_123);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c0),L"NA",&aStack_122);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c8),L"NA",&aStack_121);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d0),L"NA",&aStack_120);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d8),L"NA",&aStack_11f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e0),L"NA",&aStack_11e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e8),L"NA",&aStack_11d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f0),L"NA",&aStack_11c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f8),L"NA",&aStack_11b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x500),L"NA",&aStack_11a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x508),L"NA",&aStack_119);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x510),L"NA",&aStack_118);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x518),L"NA",&aStack_117);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x520),L"NA",&aStack_116);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x528),L"NA",&aStack_115);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x530),L"NA",&aStack_114);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x538),L"NA",&aStack_113);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x540),L"NA",&aStack_112);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x548),L"NA",&aStack_111);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x550),L"NA",&aStack_110);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x558),L"NA",&aStack_10f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x560),L"NA",&aStack_10e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x568),L"NA",&aStack_10d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x570),L"NA",&aStack_10c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x578),L"NA",&aStack_10b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x580),L"NA",&aStack_10a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x588),L"NA",&aStack_109);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x590),L"NA",&aStack_108);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x598),L"NA",&aStack_107);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a0),L"NA",&aStack_106);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a8),L"NA",&aStack_105);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b0),L"NA",&aStack_104);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b8),L"NA",&aStack_103);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c0),L"NA",&aStack_102);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c8),L"NA",&aStack_101);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d0),L";",&aStack_100);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d8),L"=",&aStack_ff);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e0),L",",&aStack_fe);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e8),L"-",&aStack_fd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f0),L".",&aStack_fc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f8),L"/",&aStack_fb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x600),L"`",&aStack_fa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x608),L"NA",&aStack_f9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x610),L"NA",&aStack_f8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x618),L"NA",&aStack_f7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x620),L"NA",&aStack_f6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x628),L"NA",&aStack_f5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x630),L"NA",&aStack_f4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x638),L"NA",&aStack_f3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x640),L"NA",&aStack_f2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x648),L"NA",&aStack_f1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x650),L"NA",&aStack_f0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x658),L"NA",&aStack_ef);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x660),L"NA",&aStack_ee);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x668),L"NA",&aStack_ed);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x670),L"NA",&aStack_ec);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x678),L"NA",&aStack_eb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x680),L"NA",&aStack_ea);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x688),L"NA",&aStack_e9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x690),L"NA",&aStack_e8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x698),L"NA",&aStack_e7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a0),L"NA",&aStack_e6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a8),L"NA",&aStack_e5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b0),L"NA",&aStack_e4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b8),L"NA",&aStack_e3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c0),L"NA",&aStack_e2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c8),L"NA",&aStack_e1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d0),L"NA",&aStack_e0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d8),L"[",&aStack_df);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e0),L"\\",&aStack_de);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e8),L"]",&aStack_dd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f0),L"\'",&aStack_dc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f8),L"NA",&aStack_db);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x700),L"NA",&aStack_da);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x708),L"NA",&aStack_d9);
  __cxa_atexit(::__tcf_7,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KContextTipNames,L"TIP_INVENTORY",&aStack_d8);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 8),L"TIP_UNIDENTIFIED",&aStack_d7)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x10),L"TIP_INVENTORYFULL",&aStack_d6);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x18),L"TIP_HEALTHLOW",&aStack_d5)
  ;
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x20),L"TIP_MANALOW",&aStack_d4);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x28),L"TIP_MERCHANT",&aStack_d3);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x30),L"TIP_LEVELUP",&aStack_d2);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x38),L"TIP_STATS",&aStack_d1);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x40),L"TIP_SPELL",&aStack_d0);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x48),L"TIP_WELCOME",&aStack_cf);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x50),L"TIP_SOCKETABLE",&aStack_ce);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x58),L"TIP_PETFLEE",&aStack_cd);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x60),L"TIP_GAMBLE",&aStack_cc);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x68),L"TIP_ENCHANT",&aStack_cb);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x70),L"TIP_TRANSMUTE",&aStack_ca)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x78),L"TIP_PETINVENTORY",&aStack_c9);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x80),L"TIP_PETINVENTORYFULL",&aStack_c8);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x88),L"TIP_STASH",&aStack_c7);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x90),L"TIP_FISHING",&aStack_c6);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x98),L"TIP_SPELLFIND",&aStack_c5)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xa0),L"TIP_QUESTCOMPLETE",&aStack_c4);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xa8),L"TIP_SHAREDSTASH",&aStack_c3);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xb0),L"TIP_HOWTOATTACK",&aStack_c2);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xb8),L"TIP_TEMP5",&aStack_c1);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xc0),L"TIP_TEMP6",&aStack_c0);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 200),L"TIP_TEMP7",&aStack_bf);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xd0),L"TIP_TEMP8",&aStack_be);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xd8),L"TIP_TEMP9",&aStack_bd);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xe0),L"TIP_TEMP10",&aStack_bc);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xe8),L"TIP_TEMP11",&aStack_bb);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xf0),L"TIP_TEMP12",&aStack_ba);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xf8),L"TIP_TEMP13",&aStack_b9);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x100),L"TIP_TEMP14",&aStack_b8);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x108),L"TIP_TEMP15",&aStack_b7);
  __cxa_atexit(::__tcf_8,0,&__dso_handle);
  ParticleUniverse::HALFSCALE._4_4_ = DAT_0142463c * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._0_4_ = Ogre::Vector3::UNIT_SCALE * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._8_4_ = DAT_00fa4810 * DAT_01424640;
  std::string::string((string *)&ParticleUniverse::ALIAS,"1",&aStack_b6);
  __cxa_atexit(std::string::~string,&ParticleUniverse::ALIAS,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::SYSTEM,"2",&aStack_b5);
  __cxa_atexit(std::string::~string,&ParticleUniverse::SYSTEM,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::TECHNIQUE,"3",&aStack_b4);
  __cxa_atexit(std::string::~string,&ParticleUniverse::TECHNIQUE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::RENDERER,"4",&aStack_b3);
  __cxa_atexit(std::string::~string,&ParticleUniverse::RENDERER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EMITTER,"5",&aStack_b2);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EMITTER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::AFFECTOR,"6",&aStack_b1);
  __cxa_atexit(std::string::~string,&ParticleUniverse::AFFECTOR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::OBSERVER,"7",&aStack_b0);
  __cxa_atexit(std::string::~string,&ParticleUniverse::OBSERVER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::HANDLER,"8",&aStack_af);
  __cxa_atexit(std::string::~string,&ParticleUniverse::HANDLER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::BEHAVIOUR,"9",&aStack_ae);
  __cxa_atexit(std::string::~string,&ParticleUniverse::BEHAVIOUR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EXTERN,"10",&aStack_ad);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EXTERN,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DYNAMIC_ATTRIBUTE,"11",&aStack_ac);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DYNAMIC_ATTRIBUTE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DEPENDENCY,"12",&aStack_ab);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DEPENDENCY,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_TYPE_NAMES,L"",&aStack_aa);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 8),L"FIND",&aStack_a9);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x10),L"KILL NUM",&aStack_a8);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x18),L"KILL BOSS",&aStack_a7);
  __cxa_atexit(::__tcf_9,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_DIALOG_TYPE_NAMES,L"ERROR",&aStack_a6);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 8),L"INTRO",&aStack_a5);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x10),L"RETURN",&aStack_a4);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x18),L"COMPLETE",&aStack_a3);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x20),L"PASSIVE",&aStack_a2);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x28),L"DETAILS",&aStack_a1);
  __cxa_atexit(::__tcf_10,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEffect_Activation_Names,L"PASSIVE",&aStack_a0);
  std::wstring::wstring((wstring_conflict *)(::gEffect_Activation_Names + 8),L"DYNAMIC",&aStack_9f);
  std::wstring::wstring
            ((wstring_conflict *)(::gEffect_Activation_Names + 0x10),L"TRANSFER",&aStack_9e);
  __cxa_atexit(::__tcf_11,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEFFECT_STAT_MODIFIER_NAMES,L"MELEE",&aStack_9d);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 8),L"RANGED",&aStack_9c);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x10),L"DEFENSE",&aStack_9b);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x18),L"MAGIC",&aStack_9a);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x20),L"LEVEL",&aStack_99);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x28),L"OWNERLEVEL",&aStack_98);
  __cxa_atexit(::__tcf_12,0,&__dso_handle);
  std::string::string((string *)::gEFFECT_STAT_MODIFIER_ICON_NAMES,"iconmelee",&aStack_97);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 8),"iconranged",&aStack_96);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x10),"icondefense",&aStack_95
                     );
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x18),"iconmagic",&aStack_94);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x20),"iconmagic",&aStack_93);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x28),"iconmagic",&aStack_92);
  __cxa_atexit(::__tcf_13,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES,"tag_righthand",&aStack_91);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 8),"tag_lefthand",&aStack_90);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x10),"",&aStack_8f);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x18),"Bip01 Head",&aStack_8e);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x20),"",&aStack_8d);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x28),"Bip01 L Clavicle",&aStack_8c);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x30),"",&aStack_8b);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x38),"",&aStack_8a);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x40),"",&aStack_89);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x48),"",&aStack_88);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x50),"",&aStack_87);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x58),"tag_leftarm",&aStack_86);
  __cxa_atexit(::__tcf_14,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES_SECONDARY,"",&aStack_85);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 8),"",&aStack_84);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x10),"",&aStack_83);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x18),"",&aStack_82);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x20),"",&aStack_81);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x28),"Bip01 R Clavicle",
                      &aStack_80);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x30),"",&aStack_7f);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x38),"",&aStack_7e);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x40),"",&aStack_7d);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x48),"",&aStack_7c);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x50),"",&aStack_7b);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x58),"",&aStack_7a);
  __cxa_atexit(::__tcf_15,0,&__dso_handle);
  std::string::string((string *)::KEquipmentIconName,"EquipLeftHand",&aStack_79);
  std::string::string((string *)(::KEquipmentIconName + 8),"EquipRightHand",&aStack_78);
  std::string::string((string *)(::KEquipmentIconName + 0x10),"EquipGloves",&aStack_77);
  std::string::string((string *)(::KEquipmentIconName + 0x18),"EquipHelm",&aStack_76);
  std::string::string((string *)(::KEquipmentIconName + 0x20),"EquipChest",&aStack_75);
  std::string::string((string *)(::KEquipmentIconName + 0x28),"EquipShoulder",&aStack_74);
  std::string::string((string *)(::KEquipmentIconName + 0x30),"EquipBoots",&aStack_73);
  std::string::string((string *)(::KEquipmentIconName + 0x38),"EquipBelt",&aStack_72);
  std::string::string((string *)(::KEquipmentIconName + 0x40),"EquipRing1",&aStack_71);
  std::string::string((string *)(::KEquipmentIconName + 0x48),"EquipRing2",&aStack_70);
  std::string::string((string *)(::KEquipmentIconName + 0x50),"EquipAmulet",&aStack_6f);
  std::string::string((string *)(::KEquipmentIconName + 0x58),"",&aStack_6e);
  __cxa_atexit(::__tcf_16,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames,L"CHEST",&aStack_6d);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 8),L"GLOVES",&aStack_6c);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x10),L"BOOTS",&aStack_6b);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x18),L"HELMET",&aStack_6a);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x20),L"SHOULDERS",&aStack_69);
  __cxa_atexit(::__tcf_17,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames2,L"",&aStack_68);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 8),L"",&aStack_67);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x10),L"",&aStack_66);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x18),L"FACE",&aStack_65);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x20),L"",&aStack_64);
  __cxa_atexit(::__tcf_18,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_AIFLAG_TYPE_NAMES,L"AWARE",&aStack_63);
  std::wstring::wstring((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 8),L"BERSERK",&aStack_62);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x10),L"CANNOT INTERRUPT",&aStack_61);
  std::wstring::wstring((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x18),L"FRIGHTEN",&aStack_60);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x20),L"NO LINE OF SIGHT",&aStack_5f);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x28),L"NEVER CHANGE TARGET",&aStack_5e);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x30),L"CANNOT TARGET",&aStack_5d);
  __cxa_atexit(::__tcf_19,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_AISTAT_TYPE_NAMES,L"NONE",&aStack_5c);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 8),L"HP",&aStack_5b);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x10),L"MANA",&aStack_5a);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x18),L"HP PCT",&aStack_59);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x20),L"MANA PCT",&aStack_58);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x28),L"ACTIVE UNITS",&aStack_57);
  __cxa_atexit(::__tcf_20,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::g_AISTAT_LOGIC_NAMES,L"BELOW",&aStack_56);
  std::wstring::wstring((wstring_conflict *)&DAT_014d41b8,L"ABOVE",&aStack_55);
  __cxa_atexit(::__tcf_21,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_AISTAT_TARGET_NAMES,L"SELF",&aStack_54);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 8),L"FORMATION",&aStack_53);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 0x10),L"AREA",&aStack_52);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 0x18),L"AREAUNITTYPES",&aStack_51);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 0x20),L"AREAFORMATION",&aStack_50);
  __cxa_atexit(::__tcf_22,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)OGRE_UTILITIES::gPRIMITIVE_NAMES,L"SPHERE",&aStack_4f);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 8),L"BOX",&aStack_4e);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x10),L"PLANE",&aStack_4d);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x18),L"CYLINDER",&aStack_4c);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x20),L"CONE",&aStack_4b);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x28),L"ARROW",&aStack_4a);
  __cxa_atexit(::__tcf_23,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gKEYFRAME_TYPES,L"HIT",&aStack_49);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 8),L"BLENDIN",&aStack_48);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x10),L"BLENDOUT",&aStack_47);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x18),L"PLAYSOUND",&aStack_46);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x20),L"SPAWNPARTICLE",&aStack_45);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x28),L"SPAWNPARTICLE_STOP_ON_DEATH",
             &aStack_44);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x30),L"FOOTSTEP",&aStack_43);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x38),L"SHOWWEAPONTRAIL",&aStack_42);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x40),L"HIDEWEAPONTRAIL",&aStack_41);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x48),L"ATTACKSOUND",&aStack_40);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x50),L"ENABLECOLLISION",&aStack_3f);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x58),L"DISABLECOLLISION",&aStack_3e);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x60),L"REMOVEPARTICLES",&aStack_3d);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x68),L"REMOVEANIMATIONPARTICLES",&aStack_3c);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x70),L"CAMERASHAKE",&aStack_3b);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x78),L"ATTACKEND",&aStack_3a);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x80),L"UNTARGETABLE",&aStack_39);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x88),L"TARGETABLE",&aStack_38);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x90),L"DAMPVELOCITY",&aStack_37);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x98),L"UNDAMPVELOCITY",&aStack_36)
  ;
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xa0),L"SHOWWEAPONS",&aStack_35);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xa8),L"HIDEWEAPONS",&aStack_34);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xb0),L"HIDEMESH",&aStack_33);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xb8),L"SHOWMESH",&aStack_32);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xc0),L"FADEOUTMESH",&aStack_31);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 200),L"FADEINMESH",&aStack_30);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0xd0),L"CAMERASHAKE_NO_FALLOFF",&aStack_2f);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0xd8),L"PLAYSOUND_NO_FALLOFF",&aStack_2e);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xe0),L"HITTWO",&aStack_2d);
  __cxa_atexit(::__tcf_24,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEDITOR_EVENT_NAMES,L"STOP",&aStack_2c);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 8),L"PLAY",&aStack_2b);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x10),L"RELOAD TILES",&aStack_2a);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x18),L"TOGGLE LIGHTING",&aStack_29);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x20),L"SELECT COLLIDABLE",&aStack_28);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x28),L"PAUSE PARTICLES",&aStack_27);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x30),L"UNPAUSE PARTICLES",&aStack_26);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x38),L"COLLISION ALL",&aStack_25);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x40),L"COLLISION MODELS",&aStack_24);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x48),L"COLLISION PREFABS",&aStack_23);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x50),L"COLLISION ROOMPIECES",&aStack_22);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x58),L"COLLISION ROOMPROPS",&aStack_21);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x60),L"RELOAD GRAPHS",&aStack_20);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x68),L"TOGGLE PLAYER LIGHT",&aStack_1f);
  __cxa_atexit(::__tcf_25,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEDITOR_FLAG_NAMES,L"LOGIC ENABLED",&aStack_1e);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 8),L"INGAME MODE",&aStack_1d);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x10),L"SHOW STATS",&aStack_1c);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x18),L"EDIT POSITION",&aStack_1b);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x20),L"EDIT SCALE",&aStack_1a);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x28),L"EDIT ORIENTATION",&aStack_19);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x30),L"EDIT NONE",&aStack_18);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x38),L"SHOW HELPERS",&aStack_17);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x40),L"SHOW GRID",&aStack_16);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x48),L"SHOW WORKING PLANE",&aStack_15);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x50),L"SNAP TO GRID",&aStack_14);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x58),L"SUSPEND EDITOR",&aStack_13);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x60),L"LIGHTING VISIBLE",&aStack_12);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x68),L"RECALCULATE LIGHTING",&aStack_11);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x70),L"SHOW EDGES",&aStack_10);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x78),L"UPDATE PARTICLES CIRCLE",&aStack_f)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x80),L"SHOW LOGIC OUTPUT",&aStack_e);
  __cxa_atexit(::__tcf_26,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::gEDITOR_UPDATE_MASKS,L"OBJECT SELECTION CHANGED",&aStack_d);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 8),L"OBJECT DATA CHANGED",&aStack_c);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 0x10),L"OBJECTS CREATED",&aStack_b);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 0x18),L"REFRESH TREE VIEW",&aStack_a);
  __cxa_atexit(::__tcf_27,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::m_gFileVersionExtension,L".svt",&aStack_9);
  __cxa_atexit(std::wstring::~wstring,&::m_gFileVersionExtension,&__dso_handle);
  return;
}

/* address=00bf5750
   symbol=CStashMenu::~CStashMenu */

/* CStashMenu::~CStashMenu() */

void __thiscall CStashMenu::~CStashMenu(CStashMenu *this)

{
  *(undefined ***)this = &PTR__CStashMenu_00ff1650;
  *(undefined ***)(this + 0x10) = &PTR__CStashMenu_00ff1700;
                    /* try { // try from 00bf5769 to 00bf57a6 has its CatchHandler @ 00bf57ce */
  setPlayer(this,(CCharacter *)0x0);
  setOwner(this,(CCharacter *)0x0);
  if (*(long **)(this + 0x90) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x90) + 8))();
    *(undefined8 *)(this + 0x90) = 0;
  }
  if (*(long **)(this + 0xa8) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0xa8) + 8))();
    *(undefined8 *)(this + 0xa8) = 0;
  }
  *(undefined ***)(this + 0x10) = &PTR__iInventoryListener_00fce450;
  *(undefined ***)this = &PTR__CSubMenu_00fe64b0;
  CRunicCore::~CRunicCore((CRunicCore *)this);
  return;
}

/* address=00bf57f0
   symbol=CStashMenu::~CStashMenu */

/* non-virtual thunk to CStashMenu::~CStashMenu() */

void __thiscall CStashMenu::~CStashMenu(CStashMenu *this)

{
  ~CStashMenu(this + -0x10);
  return;
}

/* address=00bf5800
   symbol=CStashMenu::~CStashMenu */

/* non-virtual thunk to CStashMenu::~CStashMenu() */

void __thiscall CStashMenu::~CStashMenu(CStashMenu *this)

{
  ~CStashMenu(this + -0x10);
  return;
}

/* address=00bf5810
   symbol=CStashMenu::~CStashMenu */

/* CStashMenu::~CStashMenu() */

void __thiscall CStashMenu::~CStashMenu(CStashMenu *this)

{
  ~CStashMenu(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}

/* address=00bf5830
   symbol=CStashMenu::handle_MouseOver */

/* CStashMenu::handle_MouseOver(CEGUI::EventArgs const&) */

undefined8 __thiscall CStashMenu::handle_MouseOver(CStashMenu *this,EventArgs *param_1)

{
  uint uVar1;
  Window *pWVar2;
  char cVar3;
  CBaseUnit *pCVar4;
  long lVar5;
  CInventory *this_00;

  if (*(long *)(param_1 + 0x10) == 0) {
    return 1;
  }
  if (*(CBaseUnit **)(this + 0x50) != (CBaseUnit *)0x0) {
    uVar1 = **(uint **)(*(long *)(param_1 + 0x10) + 0x1d8);
    cVar3 = CBaseUnit::ISA(*(CBaseUnit **)(this + 0x50),0xaa);
    if (cVar3 == '\0') {
      this_00 = *(CInventory **)(*(long *)(this + 0x50) + 0x490);
    }
    else {
      lVar5 = CSharedStash::getSingleton();
      this_00 = *(CInventory **)(lVar5 + 0x10);
    }
    pCVar4 = (CBaseUnit *)CInventory::getEquipmentInSlot(this_00,uVar1);
    if (pCVar4 != (CBaseUnit *)0x0) {
      *(CBaseUnit **)(this + 0x3408) = pCVar4;
      if (((pCVar4[0x348] == (CBaseUnit)0x0) || (*(int *)(pCVar4 + 0x3e0) == 0)) &&
         (cVar3 = CBaseUnit::ISA(pCVar4,0x78), cVar3 == '\0')) {
        CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x30),0));
        CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x38),0));
      }
      else {
        CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x38),0));
        CEGUI::Window::moveToFront();
        CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x30),0));
        CEGUI::Window::moveToFront();
      }
    }
    pWVar2 = *(Window **)(this + 0x28);
    CEGUI::Window::getPosition();
    CEGUI::Window::getPosition();
    CEGUI::Window::getWidth();
    CEGUI::Window::getHeight();
    cVar3 = CEGUI::Window::isChild(pWVar2);
    if (cVar3 == '\0') {
      CEGUI::Window::addChildWindow(pWVar2);
    }
                    /* try { // try from 00bf5ae2 to 00bf5ae6 has its CatchHandler @ 00bf5bd3 */
    CEGUI::Window::setPosition(*(UVector2 **)(this + 0x3418));
                    /* try { // try from 00bf5b43 to 00bf5b47 has its CatchHandler @ 00bf5bcb */
    CEGUI::Window::setSize(*(UVector2 **)(this + 0x3418));
    CEGUI::Window::moveToBack();
    this[0x3420] = (CStashMenu)0x1;
    return 1;
  }
  return 1;
}

/* address=00bf5be0
   symbol=CStashMenu::handle_PetMouseOver */

/* CStashMenu::handle_PetMouseOver(CEGUI::EventArgs const&) */

undefined8 __thiscall CStashMenu::handle_PetMouseOver(CStashMenu *this,EventArgs *param_1)

{
  long *plVar1;
  long lVar2;
  Window *pWVar3;
  char cVar4;
  CBaseUnit *pCVar5;

  plVar1 = *(long **)(*(long *)(this + 0x58) + 0x648);
  if (*(long *)(*(long *)(this + 0x58) + 0x650) - (long)plVar1 >> 3 == 0) {
    return 1;
  }
  lVar2 = *plVar1;
  if (lVar2 != 0) {
    if (*(long *)(param_1 + 0x10) != 0) {
      pCVar5 = (CBaseUnit *)
               CInventory::getEquipmentInSlot
                         (*(CInventory **)(lVar2 + 0x490),
                          **(uint **)(*(long *)(param_1 + 0x10) + 0x1d8));
      if (pCVar5 != (CBaseUnit *)0x0) {
        *(CBaseUnit **)(this + 0x3408) = pCVar5;
        if (((pCVar5[0x348] == (CBaseUnit)0x0) || (*(int *)(pCVar5 + 0x3e0) == 0)) &&
           (cVar4 = CBaseUnit::ISA(pCVar5,0x78), cVar4 == '\0')) {
          CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x38),0));
          CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x30),0));
        }
        else {
          CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x38),0));
          CEGUI::Window::moveToFront();
          CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x30),0));
          CEGUI::Window::moveToFront();
        }
      }
      pWVar3 = *(Window **)(this + 0x28);
      CEGUI::Window::getPosition();
      CEGUI::Window::getPosition();
      CEGUI::Window::getWidth();
      CEGUI::Window::getHeight();
      cVar4 = CEGUI::Window::isChild(pWVar3);
      if (cVar4 == '\0') {
        CEGUI::Window::addChildWindow(pWVar3);
      }
                    /* try { // try from 00bf5e90 to 00bf5e94 has its CatchHandler @ 00bf5f83 */
      CEGUI::Window::setPosition(*(UVector2 **)(this + 0x3418));
                    /* try { // try from 00bf5ef1 to 00bf5ef5 has its CatchHandler @ 00bf5f7b */
      CEGUI::Window::setSize(*(UVector2 **)(this + 0x3418));
      CEGUI::Window::moveToBack();
      this[0x3420] = (CStashMenu)0x1;
      return 1;
    }
    return 1;
  }
  return 1;
}

/* address=00bf5f90
   symbol=CStashMenu::handle_CloseButton */

/* CStashMenu::handle_CloseButton(CEGUI::EventArgs const&) */

undefined8 __thiscall CStashMenu::handle_CloseButton(CStashMenu *this,EventArgs *param_1)

{
  long lVar1;

  if (*(int *)(param_1 + 0x28) != 0) {
    return 1;
  }
  this[0x62] = (CStashMenu)0x1;
  CCharacter::setTarget(*(CCharacter **)(*(long *)(this + 0x70) + 0x38),(CCharacter *)0x0);
  lVar1 = *(long *)(*(long *)(this + 0x70) + 0x1920);
  if (*(CRunicCore **)(lVar1 + 0x1f8) != (CRunicCore *)0x0) {
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(lVar1 + 0x1f8),(TSafePointer *)(lVar1 + 0x1f8),
               *(uint *)(lVar1 + 0x200));
    *(undefined8 *)(lVar1 + 0x1f8) = 0;
  }
  if (*(CRunicCore **)(lVar1 + 0x1e8) != (CRunicCore *)0x0) {
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(lVar1 + 0x1e8),(TSafePointer *)(lVar1 + 0x1e8),
               *(uint *)(lVar1 + 0x1f0));
    *(undefined8 *)(lVar1 + 0x1e8) = 0;
  }
  if (*(CRunicCore **)(lVar1 + 0x1c8) != (CRunicCore *)0x0) {
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(lVar1 + 0x1c8),(TSafePointer *)(lVar1 + 0x1c8),
               *(uint *)(lVar1 + 0x1d0));
    *(undefined8 *)(lVar1 + 0x1c8) = 0;
  }
  if (*(CRunicCore **)(lVar1 + 0x1d8) != (CRunicCore *)0x0) {
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(lVar1 + 0x1d8),(TSafePointer *)(lVar1 + 0x1d8),
               *(uint *)(lVar1 + 0x1e0));
    *(undefined8 *)(lVar1 + 0x1d8) = 0;
  }
  CGameUI::closeRight(*(CGameUI **)(this + 0x70));
  return 1;
}

/* address=00bf6ef0
   symbol=CStashMenu::update */

/* WARNING: Removing unreachable block (ram,0x00bf74f5) */
/* WARNING: Removing unreachable block (ram,0x00bf74e7) */
/* WARNING: Removing unreachable block (ram,0x00bf74d9) */
/* WARNING: Removing unreachable block (ram,0x00bf749a) */
/* CStashMenu::update(float) */

void __thiscall CStashMenu::update(CStashMenu *this,float param_1)

{
  int *piVar1;
  int iVar2;
  code *pcVar3;
  char cVar4;
  int iVar5;
  long *plVar6;
  float *pfVar7;
  bool bVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  undefined8 uVar12;
  string local_98 [16];
  long local_88 [2];
  long local_78 [2];
  long local_68 [2];
  long local_58 [3];
  allocator local_3d;
  allocator local_3c;
  allocator local_3b;
  allocator local_3a;
  allocator local_39 [9];

  iVar5 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0x68),KSETTINGS_RES_WIDTH);
  CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0x68),KSETTINGS_RES_HEIGHT);
  if (this[0x60] == (CStashMenu)0x0) {
    *(undefined8 *)(this + 0x3408) = 0;
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x30),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x38),0));
    if ((this[0x60] == (CStashMenu)0x0) && (this[0x61] != (CStashMenu)0x0)) {
      return;
    }
  }
  CGenericModel::updateAnimation(*(CGenericModel **)(this + 0x90),param_1,false);
  Ogre::Entity::_updateAnimation();
  plVar6 = *(long **)(*(long *)(this + 0x90) + 0x130);
  pcVar3 = *(code **)(*plVar6 + 0x1b0);
                    /* try { // try from 00bf6f8d to 00bf6f91 has its CatchHandler @ 00bf74b9 */
  std::string::string((string *)local_58,"tag_topmerchant",local_39);
                    /* try { // try from 00bf6f98 to 00bf6f9a has its CatchHandler @ 00bf74c6 */
  plVar6 = (long *)(*pcVar3)(plVar6);
  if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_58[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
    }
  }
  uVar12 = CPositionableObject::getPosition(*(CPositionableObject **)(this + 0x90),false);
  pfVar7 = (float *)(**(code **)(*plVar6 + 0x200))(plVar6);
  fVar10 = pfVar7[1];
  CGameUI::scaledY(*(CGameUI **)(this + 0x70),*pfVar7 + (float)uVar12);
  fVar9 = (float)iVar5 * DAT_00fa4810;
  CGameUI::scaledY(*(CGameUI **)(this + 0x70),fVar10 + (float)((ulong)uVar12 >> 0x20));
                    /* try { // try from 00bf70bc to 00bf70c0 has its CatchHandler @ 00bf74b7 */
  CEGUI::Window::setPosition(*(UVector2 **)(this + 0x28));
  plVar6 = *(long **)(*(long *)(this + 0x90) + 0x130);
  pcVar3 = *(code **)(*plVar6 + 0x1b0);
                    /* try { // try from 00bf70f2 to 00bf70f6 has its CatchHandler @ 00bf74b2 */
  std::string::string((string *)local_68,"tag_bottommerchant",&local_3a);
                    /* try { // try from 00bf70fd to 00bf70ff has its CatchHandler @ 00bf74a5 */
  plVar6 = (long *)(*pcVar3)(plVar6);
  if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_68[0] + -8);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
    }
  }
  fVar10 = (float)CPositionableObject::getPosition(*(CPositionableObject **)(this + 0x90),false);
  pfVar7 = (float *)(**(code **)(*plVar6 + 0x200))(plVar6);
  CGameUI::scaledY(*(CGameUI **)(this + 0x70),*pfVar7 + fVar10);
                    /* try { // try from 00bf719a to 00bf719e has its CatchHandler @ 00bf74c4 */
  CEGUI::Window::setPosition(*(UVector2 **)(this + 0x40));
  plVar6 = *(long **)(*(long *)(this + 0x90) + 0x130);
  pcVar3 = *(code **)(*plVar6 + 0x1b0);
                    /* try { // try from 00bf71d0 to 00bf71d4 has its CatchHandler @ 00bf74d2 */
  std::string::string((string *)local_78,"tag_bottommerchantright",&local_3b);
                    /* try { // try from 00bf71db to 00bf71dd has its CatchHandler @ 00bf74c2 */
  plVar6 = (long *)(*pcVar3)(plVar6);
  if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_78[0] + -8);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
    }
  }
  fVar10 = (float)CPositionableObject::getPosition(*(CPositionableObject **)(this + 0x90),false);
  pfVar7 = (float *)(**(code **)(*plVar6 + 0x200))(plVar6);
  fVar10 = (float)CGameUI::scaledY(*(CGameUI **)(this + 0x70),*pfVar7 + fVar10);
  fVar11 = (float)CGameUI::scaledY(*(CGameUI **)(this + 0x70),DAT_00fa8738);
  fVar11 = (fVar9 + fVar10) - fVar11;
  if (fVar11 <= 0.0) {
    fVar11 = 0.0;
  }
  *(float *)(this + 0xa0) = fVar11;
  if ((this[0x60] == (CStashMenu)0x0) && (this[0x61] == (CStashMenu)0x0)) {
                    /* try { // try from 00bf72fe to 00bf7317 has its CatchHandler @ 00bf7470 */
    std::string::string((string *)local_88,"CLOSE",&local_3c);
    cVar4 = CGenericModel::animationPlaying(*(CGenericModel **)(this + 0x90),(string *)local_88);
    bVar8 = false;
    if (cVar4 == '\0') {
                    /* try { // try from 00bf737d to 00bf739b has its CatchHandler @ 00bf7470 */
      std::string::string(local_98,"CLOSE",&local_3d);
      cVar4 = CGenericModel::animationQueued(*(CGenericModel **)(this + 0x90),local_98);
      bVar8 = cVar4 == '\0';
                    /* try { // try from 00bf73aa to 00bf73ae has its CatchHandler @ 00bf74d4 */
      std::string::~string(local_98);
    }
    if ((allocator *)(local_88[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_88[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
      }
    }
    if (bVar8) {
      (**(code **)(**(long **)(this + 0x90) + 0x50))(*(long **)(this + 0x90),0);
      CEGUI::Window::removeChildWindow(*(Window **)(this + 0x18));
      this[0x61] = (CStashMenu)0x1;
    }
  }
  return;
}

/* address=00bf7510
   symbol=CStashMenu::setOpen */

/* WARNING: Removing unreachable block (ram,0x00bf78e7) */
/* WARNING: Removing unreachable block (ram,0x00bf78da) */
/* WARNING: Removing unreachable block (ram,0x00bf7888) */
/* CStashMenu::setOpen(bool) */

void __thiscall CStashMenu::setOpen(CStashMenu *this,bool param_1)

{
  int *piVar1;
  int iVar2;
  char cVar3;
  long local_68 [2];
  long local_58 [2];
  string local_48 [16];
  string local_38 [16];
  long local_28;
  allocator local_1d;
  allocator local_1c;
  allocator local_1b;
  allocator local_1a;
  allocator local_19;

  if (this[0x60] == (CStashMenu)0x0) {
    if (!param_1) {
      this[0x60] = (CStashMenu)0x0;
      return;
    }
    CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0x68),KSETTINGS_RES_WIDTH);
    CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0x68),KSETTINGS_RES_HEIGHT);
    CSoundBank::playSample(*(CSoundBank **)(this + 0xa8),0x16,(SceneNode *)0x0,0.0,0.0,false);
    (**(code **)(**(long **)(this + 0x90) + 0x50))(*(long **)(this + 0x90),1);
                    /* try { // try from 00bf75cd to 00bf75d1 has its CatchHandler @ 00bf7886 */
    std::string::string((string *)&local_28,"CLOSE",&local_19);
                    /* try { // try from 00bf75dc to 00bf75e0 has its CatchHandler @ 00bf786c */
    cVar3 = CGenericModel::animationPlaying(*(CGenericModel **)(this + 0x90),(string *)&local_28);
    if ((allocator *)(local_28 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_28 + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_28 + -0x18));
      }
    }
    if (cVar3 == '\0') {
                    /* try { // try from 00bf77da to 00bf77de has its CatchHandler @ 00bf7881 */
      std::string::string(local_48,"OPEN",&local_1b);
                    /* try { // try from 00bf77fb to 00bf77ff has its CatchHandler @ 00bf787f */
      CGenericModel::playAnimation
                (*(CGenericModel **)(this + 0x90),local_48,false,DAT_00fa4824,DAT_00fa8760);
                    /* try { // try from 00bf7803 to 00bf7807 has its CatchHandler @ 00bf7881 */
      std::string::~string(local_48);
    }
    else {
                    /* try { // try from 00bf7611 to 00bf7615 has its CatchHandler @ 00bf78a2 */
      std::string::string(local_38,"OPEN",&local_1a);
                    /* try { // try from 00bf763a to 00bf763e has its CatchHandler @ 00bf7897 */
      CGenericModel::blendAnimation
                (*(CGenericModel **)(this + 0x90),local_38,false,DAT_00fa480c,DAT_00fa4824,
                 DAT_00fa8760);
                    /* try { // try from 00bf7642 to 00bf7646 has its CatchHandler @ 00bf78a2 */
      std::string::~string(local_38);
    }
                    /* try { // try from 00bf7659 to 00bf765d has its CatchHandler @ 00bf7895 */
    std::string::string((string *)local_58,"IDLE",&local_1c);
                    /* try { // try from 00bf767d to 00bf7681 has its CatchHandler @ 00bf7893 */
    CGenericModel::queueBlendAnimation
              (*(CGenericModel **)(this + 0x90),(string *)local_58,true,DAT_00fa480c,DAT_00fa47fc);
    if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_58[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
      }
    }
    CEGUI::Window::addChildWindow(*(Window **)(this + 0x18));
    CEGUI::Window::moveToBack();
    CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x33e0),0));
    CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x33e8),0));
    CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x33f0),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x33c8),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x33d0),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x33d8),0));
    if (this[0x3421] == (CStashMenu)0x0) {
      CGameUI::queueTip(*(CGameUI **)(this + 0x70),0x11);
    }
    else {
      CGameUI::queueTip(*(CGameUI **)(this + 0x70),0x15);
    }
  }
  else if (!param_1) {
    CSoundBank::playSample(*(CSoundBank **)(this + 0xa8),0x42,(SceneNode *)0x0,0.0,0.0,false);
                    /* try { // try from 00bf775d to 00bf7761 has its CatchHandler @ 00bf78e5 */
    std::string::string((string *)local_68,"CLOSE",&local_1d);
                    /* try { // try from 00bf7786 to 00bf778a has its CatchHandler @ 00bf78cd */
    CGenericModel::blendAnimation
              (*(CGenericModel **)(this + 0x90),(string *)local_68,false,DAT_00fa480c,DAT_00fa4824,
               DAT_00fa8760);
    if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_68[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
      }
    }
    this[0x61] = (CStashMenu)0x0;
    this[0x60] = (CStashMenu)0x0;
    return;
  }
  this[0x60] = (CStashMenu)param_1;
  (**(code **)(*(long *)this + 0x48))(this);
  return;
}

/* address=00bf7900
   symbol=CStashMenu::mapEventHandlers */

/* CStashMenu::mapEventHandlers(CEGUI::Window*) */

void __thiscall CStashMenu::mapEventHandlers(CStashMenu *this,Window *param_1)

{
  undefined8 *puVar1;
  byte bVar2;
  code *pcVar3;
  char cVar4;
  long lVar5;
  char *pcVar6;
  uint *puVar7;
  int iVar8;
  long lVar9;
  int iVar10;
  bool bVar11;
  long local_268 [22];
  undefined8 local_1b8;
  ulong local_1b0;
  undefined8 local_1a8;
  undefined8 local_1a0;
  undefined8 local_198;
  uint local_190 [7];
  uint local_174 [25];
  uint *local_110;
  undefined8 local_108;
  ulong local_100;
  undefined8 local_f8;
  undefined8 local_f0;
  undefined8 local_e8;
  uint local_e0 [7];
  uint local_c4 [25];
  uint *local_60;
  BoundSlot *local_58;
  int *local_50;
  undefined8 *local_48 [3];

  lVar5 = *(long *)(param_1 + 0x78);
  iVar10 = (int)((ulong)(*(long *)(param_1 + 0x80) - lVar5) >> 3);
  if (0 < iVar10) {
    lVar9 = 0;
    iVar8 = 0;
    while( true ) {
      puVar1 = (undefined8 *)(lVar5 + lVar9);
      iVar8 = iVar8 + 1;
      lVar9 = lVar9 + 8;
      mapEventHandlers(this,(Window *)*puVar1);
      if (iVar10 <= iVar8) break;
      lVar5 = *(long *)(param_1 + 0x78);
    }
  }
  local_100 = 0x20;
  local_f8 = 0;
  local_e8 = 0;
  local_f0 = 0;
  local_60 = (uint *)0x0;
  local_108 = 0;
  local_e0[0] = 0;
                    /* try { // try from 00bf79c6 to 00bf7a43 has its CatchHandler @ 00bf7ca4 */
  CEGUI::String::grow((ulong)&local_108);
  puVar7 = local_e0;
  if (0x20 < local_100) {
    puVar7 = local_60;
  }
  pcVar6 = "onClick";
  do {
    bVar2 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    *puVar7 = (uint)bVar2;
    puVar7 = puVar7 + 1;
  } while ((byte *)pcVar6 != (byte *)0xfe4847);
  local_108 = 7;
  puVar7 = local_c4;
  if (0x20 < local_100) {
    puVar7 = local_60 + 7;
  }
  *puVar7 = 0;
  cVar4 = CEGUI::PropertySet::isPropertyPresent((String *)param_1);
  bVar11 = false;
  if (cVar4 != '\0') {
    local_1b0 = 0x20;
    local_1a8 = 0;
    local_198 = 0;
    local_1a0 = 0;
    local_110 = (uint *)0x0;
    local_1b8 = 0;
    local_190[0] = 0;
                    /* try { // try from 00bf7b98 to 00bf7c16 has its CatchHandler @ 00bf7ca4 */
    CEGUI::String::grow((ulong)&local_1b8);
    puVar7 = local_110;
    if (local_1b0 < 0x21) {
      puVar7 = local_190;
    }
    pcVar6 = "onClick";
    do {
      bVar2 = *pcVar6;
      pcVar6 = pcVar6 + 1;
      *puVar7 = (uint)bVar2;
      puVar7 = puVar7 + 1;
    } while ((byte *)pcVar6 != (byte *)0xfe4847);
    local_1b8 = 7;
    if (local_1b0 < 0x21) {
      puVar7 = local_174;
    }
    else {
      puVar7 = local_110 + 7;
    }
    *puVar7 = 0;
    CEGUI::PropertySet::getProperty((String *)local_268);
    bVar11 = local_268[0] != 0;
                    /* try { // try from 00bf7c23 to 00bf7c27 has its CatchHandler @ 00bf7c5e */
    CEGUI::String::~String((String *)local_268);
                    /* try { // try from 00bf7c30 to 00bf7c34 has its CatchHandler @ 00bf7c97 */
    CEGUI::String::~String((String *)&local_1b8);
  }
                    /* try { // try from 00bf7a52 to 00bf7a81 has its CatchHandler @ 00bf7c85 */
  CEGUI::String::~String((String *)&local_108);
  if (bVar11) {
    pcVar3 = *(code **)(*(long *)(param_1 + 0x38) + 0x10);
    local_48[0] = operator_new(0x20);
    local_48[0][3] = this;
    *local_48[0] = &PTR__MemberFunctionSlot_00ff17b0;
    local_48[0][2] = 0;
    local_48[0][1] = 0x59;
                    /* try { // try from 00bf7ac1 to 00bf7af6 has its CatchHandler @ 00bf7c8a */
    (*pcVar3)(&local_58,param_1 + 0x38,CEGUI::Window::EventMouseButtonDown,
              (SubscriberSlot *)local_48);
    if ((local_58 != (BoundSlot *)0x0) &&
       (iVar10 = *local_50, *local_50 = iVar10 + -1, iVar10 + -1 == 0)) {
      if (local_58 != (BoundSlot *)0x0) {
        CEGUI::BoundSlot::~BoundSlot(local_58);
        operator_delete(local_58);
      }
      operator_delete(local_50);
      local_58 = (BoundSlot *)0x0;
      local_50 = (int *)0x0;
    }
                    /* try { // try from 00bf7b27 to 00bf7b2b has its CatchHandler @ 00bf7c85 */
    CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_48);
  }
  return;
}

/* address=00bf7cc0
   symbol=CStashMenu::setPetSlotIcon */

/* WARNING: Removing unreachable block (ram,0x00bf93d1) */
/* WARNING: Removing unreachable block (ram,0x00bf943c) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CStashMenu::setPetSlotIcon(CEquipment*, int, int) */

void __thiscall
CStashMenu::setPetSlotIcon(CStashMenu *this,CEquipment *param_1,int param_2,int param_3)

{
  int *piVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  byte bVar6;
  uint uVar7;
  uint uVar8;
  char cVar9;
  long lVar10;
  float *pfVar11;
  char *pcVar12;
  byte *pbVar13;
  CEquipment *this_00;
  uint *puVar14;
  undefined4 *puVar15;
  long lVar16;
  UVector2 *pUVar17;
  bool bVar18;
  String *pSVar19;
  ulong uVar20;
  uint uVar21;
  float fVar22;
  uint uVar23;
  uint uVar24;
  String local_1618 [176];
  undefined8 local_1568;
  ulong local_1560;
  undefined8 local_1558;
  undefined8 local_1550;
  undefined8 local_1548;
  uint local_1540 [5];
  uint local_152c [27];
  uint *local_14c0;
  Image local_14b8 [176];
  undefined8 local_1408;
  ulong local_1400;
  undefined8 local_13f8;
  undefined8 local_13f0;
  undefined8 local_13e8;
  uint local_13e0 [11];
  uint local_13b4 [21];
  uint *local_1360;
  undefined8 local_1358;
  ulong local_1350;
  undefined8 local_1348;
  undefined8 local_1340;
  undefined8 local_1338;
  uint local_1330 [5];
  uint local_131c [27];
  uint *local_12b0;
  Image local_12a8 [176];
  undefined8 local_11f8;
  ulong local_11f0;
  undefined8 local_11e8;
  undefined8 local_11e0;
  undefined8 local_11d8;
  uint local_11d0 [15];
  uint local_1194 [17];
  uint *local_1150;
  undefined8 local_1148;
  ulong local_1140;
  undefined8 local_1138;
  undefined8 local_1130;
  undefined8 local_1128;
  undefined4 local_1120 [32];
  undefined4 *local_10a0;
  undefined8 local_1098;
  ulong local_1090;
  undefined8 local_1088;
  undefined8 local_1080;
  undefined8 local_1078;
  uint local_1070 [5];
  uint local_105c [27];
  uint *local_ff0;
  String local_fe8 [176];
  Image local_f38 [176];
  String local_e88 [176];
  String local_dd8 [176];
  Image local_d28 [176];
  String local_c78 [176];
  undefined8 local_bc8;
  ulong local_bc0;
  undefined8 local_bb8;
  undefined8 local_bb0;
  undefined8 local_ba8;
  uint local_ba0 [5];
  uint local_b8c [27];
  uint *local_b20;
  Image local_b18 [176];
  undefined8 local_a68;
  ulong local_a60;
  undefined8 local_a58;
  undefined8 local_a50;
  undefined8 local_a48;
  uint local_a40 [12];
  uint local_a10 [20];
  uint *local_9c0;
  undefined8 local_9b8;
  ulong local_9b0;
  undefined8 local_9a8;
  undefined8 local_9a0;
  undefined8 local_998;
  undefined4 local_990 [32];
  undefined4 *local_910;
  undefined8 local_908;
  ulong local_900;
  undefined8 local_8f8;
  undefined8 local_8f0;
  undefined8 local_8e8;
  uint local_8e0 [5];
  uint local_8cc [27];
  uint *local_860;
  undefined8 local_858;
  ulong local_850;
  undefined8 local_848;
  undefined8 local_840;
  undefined8 local_838;
  uint local_830 [5];
  uint local_81c [27];
  uint *local_7b0;
  Image local_7a8 [176];
  undefined8 local_6f8;
  ulong local_6f0;
  undefined8 local_6e8;
  undefined8 local_6e0;
  undefined8 local_6d8;
  uint local_6d0 [12];
  uint local_6a0 [20];
  uint *local_650;
  undefined8 local_648;
  ulong local_640;
  undefined8 local_638;
  undefined8 local_630;
  undefined8 local_628;
  undefined4 local_620 [32];
  undefined4 *local_5a0;
  undefined8 local_598;
  ulong local_590;
  undefined8 local_588;
  undefined8 local_580;
  undefined8 local_578;
  uint local_570 [5];
  uint local_55c [27];
  uint *local_4f0;
  String local_4e8 [176];
  Image local_438 [176];
  String local_388 [176];
  undefined8 local_2d8;
  ulong local_2d0;
  undefined8 local_2c8;
  undefined8 local_2c0;
  undefined8 local_2b8;
  uint local_2b0 [5];
  uint local_29c [27];
  uint *local_230;
  Image local_228 [176];
  undefined8 local_178;
  ulong local_170;
  undefined8 local_168;
  undefined8 local_160;
  undefined8 local_158;
  uint local_150 [13];
  uint local_11c [19];
  uint *local_d0;
  float local_c0;
  float local_bc;
  undefined4 local_a8;
  float local_a4;
  undefined4 local_a0;
  float local_9c;
  float local_90;
  float local_8c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  long local_58 [2];
  uchar *local_48 [3];

  lVar16 = (long)param_2;
  lVar10 = CEGUI::Window::getPosition();
  uVar8 = DAT_00fa86f4;
  uVar7 = DAT_00fa4810;
  fVar22 = *(float *)(lVar10 + 8) * 0.0;
  uVar21 = -(uint)(0.0 < fVar22);
  uVar24 = DAT_00fa4810 & uVar21;
  uVar23 = ~uVar21 & DAT_00fa86f4;
  fVar2 = *(float *)(lVar10 + 0xc);
  pfVar11 = (float *)CEGUI::Window::getPosition();
  fVar3 = *pfVar11;
  pUVar17 = *(UVector2 **)(param_1 + 0x2c8);
  uVar21 = -(uint)(0.0 < fVar3 * 0.0);
  fVar4 = pfVar11[1];
  if (pUVar17 == (UVector2 *)0x0) {
    CEquipment::createIcon(param_1,*(CGameUI **)(this + 0x70),false);
    pUVar17 = *(UVector2 **)(param_1 + 0x2c8);
    if (pUVar17 != (UVector2 *)0x0) {
      CEGUI::EventSet::setMutedState((bool)((char)pUVar17 + '8'));
      pUVar17[0x3e2] = (UVector2)0x1;
      goto LAB_00bf7da8;
    }
  }
  else {
LAB_00bf7da8:
    if (*(Window **)(pUVar17 + 0xb0) != (Window *)0x0) {
      CEGUI::Window::removeChildWindow(*(Window **)(pUVar17 + 0xb0));
    }
    CEGUI::Window::addChildWindow(*(Window **)(this + lVar16 * 8 + 0x26f8));
    local_64 = 0;
    local_68 = 0;
    local_5c = 0x3f800000;
    local_60 = 0;
                    /* try { // try from 00bf7e08 to 00bf7e0c has its CatchHandler @ 00bf94d5 */
    CEGUI::Window::setPosition(pUVar17);
    local_74 = 0;
    local_78 = 0;
    local_6c = 0;
    local_70 = 0;
                    /* try { // try from 00bf7e44 to 00bf7e48 has its CatchHandler @ 00bf9485 */
    CEGUI::Window::setPosition(pUVar17);
    CEGUI::Window::getSize();
                    /* try { // try from 00bf7e6c to 00bf7e70 has its CatchHandler @ 00bf947c */
    CEGUI::Window::setSize(pUVar17);
    CEGUI::Window::moveToFront();
    *(CStashMenu **)(pUVar17 + 0x1d8) = this + (long)param_3 * 4 + 0xb0;
  }
  if ((param_1[0x348] == (CEquipment)0x0) || (*(uint *)(param_1 + 0x3e0) == 0)) {
    local_640 = 0x20;
    local_638 = 0;
    local_628 = 0;
    local_630 = 0;
    local_5a0 = (undefined4 *)0x0;
    local_648 = 0;
    local_620[0] = 0;
    CEGUI::String::grow((ulong)&local_648);
    local_648 = 0;
    puVar15 = local_620;
    if (0x20 < local_640) {
      puVar15 = local_5a0;
    }
    *puVar15 = 0;
    local_590 = 0x20;
    local_588 = 0;
    local_578 = 0;
    local_580 = 0;
    local_4f0 = (uint *)0x0;
    local_598 = 0;
    local_570[0] = 0;
                    /* try { // try from 00bf831d to 00bf8321 has its CatchHandler @ 00bf9492 */
    CEGUI::String::grow((ulong)&local_598);
    puVar14 = local_570;
    if (0x20 < local_590) {
      puVar14 = local_4f0;
    }
    pbVar13 = (byte *)0xfd0c0d;
    do {
      bVar6 = *pbVar13;
      pbVar13 = pbVar13 + 1;
      *puVar14 = (uint)bVar6;
      puVar14 = puVar14 + 1;
    } while (pbVar13 != (byte *)0xfd0c12);
    local_598 = 5;
    puVar14 = local_55c;
    if (0x20 < local_590) {
      puVar14 = local_4f0 + 5;
    }
    *puVar14 = 0;
                    /* try { // try from 00bf838e to 00bf8392 has its CatchHandler @ 00bf94a9 */
    CEGUI::PropertySet::setProperty(*(String **)(this + lVar16 * 8 + 0x2ea8),(String *)&local_598);
                    /* try { // try from 00bf8396 to 00bf839a has its CatchHandler @ 00bf9492 */
    CEGUI::String::~String((String *)&local_598);
    CEGUI::String::~String((String *)&local_648);
    if (param_1[0x348] != (CEquipment)0x0) goto LAB_00bf80b2;
LAB_00bf83b1:
    pSVar19 = (String *)&local_6f8;
    local_6f0 = 0x20;
    local_6e8 = 0;
    local_6d8 = 0;
    local_6e0 = 0;
    local_650 = (uint *)0x0;
    local_6f8 = 0;
    local_6d0[0] = 0;
    CEGUI::String::grow((ulong)pSVar19);
    puVar14 = local_6d0;
    if (0x20 < local_6f0) {
      puVar14 = local_650;
    }
    pcVar12 = "unidentified";
    do {
      bVar6 = *pcVar12;
      pcVar12 = pcVar12 + 1;
      *puVar14 = (uint)bVar6;
      puVar14 = puVar14 + 1;
    } while ((byte *)pcVar12 != (byte *)0xfef79d);
    local_6f8 = 0xc;
    puVar14 = local_6a0;
    if (0x20 < local_6f0) {
      puVar14 = local_650 + 0xc;
    }
    *puVar14 = 0;
                    /* try { // try from 00bf848d to 00bf84a4 has its CatchHandler @ 00bf9415 */
    CEGUI::Imageset::getImage(*(String **)(this + 0x3410));
    CEGUI::PropertyHelper::imageToString(local_7a8);
    local_850 = 0x20;
    local_848 = 0;
    local_838 = 0;
    local_840 = 0;
    local_7b0 = (uint *)0x0;
    local_858 = 0;
    local_830[0] = 0;
                    /* try { // try from 00bf8508 to 00bf850c has its CatchHandler @ 00bf943a */
    CEGUI::String::grow((ulong)&local_858);
    puVar14 = local_830;
    if (0x20 < local_850) {
      puVar14 = local_7b0;
    }
    pbVar13 = (byte *)0xfd0c0d;
    do {
      bVar6 = *pbVar13;
      pbVar13 = pbVar13 + 1;
      *puVar14 = (uint)bVar6;
      puVar14 = puVar14 + 1;
    } while (pbVar13 != (byte *)0xfd0c12);
    local_858 = 5;
    puVar14 = local_81c;
    if (0x20 < local_850) {
      puVar14 = local_7b0 + 5;
    }
    *puVar14 = 0;
                    /* try { // try from 00bf8585 to 00bf8589 has its CatchHandler @ 00bf9487 */
    CEGUI::PropertySet::setProperty(*(String **)(this + lVar16 * 8 + 0x2988),(String *)&local_858);
                    /* try { // try from 00bf858d to 00bf8591 has its CatchHandler @ 00bf943a */
    CEGUI::String::~String((String *)&local_858);
                    /* try { // try from 00bf8595 to 00bf8599 has its CatchHandler @ 00bf9415 */
    CEGUI::String::~String((String *)local_7a8);
  }
  else {
    if (*(uint *)(param_1 + 0x3e0) < 2) {
      CEGUI::String::String(local_388,"onesocketglow");
                    /* try { // try from 00bf92d4 to 00bf92eb has its CatchHandler @ 00bf9362 */
      CEGUI::Imageset::getImage(*(String **)(this + 0x3410));
      CEGUI::PropertyHelper::imageToString(local_438);
                    /* try { // try from 00bf92fc to 00bf9300 has its CatchHandler @ 00bf935b */
      CEGUI::String::String(local_4e8,"Image");
                    /* try { // try from 00bf9314 to 00bf9318 has its CatchHandler @ 00bf9359 */
      CEGUI::PropertySet::setProperty(*(String **)(this + lVar16 * 8 + 0x2ea8),local_4e8);
                    /* try { // try from 00bf931c to 00bf9320 has its CatchHandler @ 00bf935b */
      CEGUI::String::~String(local_4e8);
                    /* try { // try from 00bf9324 to 00bf9328 has its CatchHandler @ 00bf9362 */
      CEGUI::String::~String((String *)local_438);
      CEGUI::String::~String(local_388);
    }
    else {
      local_170 = 0x20;
      local_168 = 0;
      local_158 = 0;
      local_160 = 0;
      local_d0 = (uint *)0x0;
      local_178 = 0;
      local_150[0] = 0;
      CEGUI::String::grow((ulong)&local_178);
      puVar14 = local_150;
      if (0x20 < local_170) {
        puVar14 = local_d0;
      }
      pcVar12 = "twosocketglow";
      do {
        bVar6 = *pcVar12;
        pcVar12 = pcVar12 + 1;
        *puVar14 = (uint)bVar6;
        puVar14 = puVar14 + 1;
      } while ((byte *)pcVar12 != (byte *)0xfe60d0);
      local_178 = 0xd;
      puVar14 = local_11c;
      if (0x20 < local_170) {
        puVar14 = local_d0 + 0xd;
      }
      *puVar14 = 0;
                    /* try { // try from 00bf7f85 to 00bf7f9c has its CatchHandler @ 00bf9447 */
      CEGUI::Imageset::getImage(*(String **)(this + 0x3410));
      CEGUI::PropertyHelper::imageToString(local_228);
      local_2d0 = 0x20;
      local_2c8 = 0;
      local_2b8 = 0;
      local_2c0 = 0;
      local_230 = (uint *)0x0;
      local_2d8 = 0;
      local_2b0[0] = 0;
                    /* try { // try from 00bf8000 to 00bf8004 has its CatchHandler @ 00bf944c */
      CEGUI::String::grow((ulong)&local_2d8);
      puVar14 = local_2b0;
      if (0x20 < local_2d0) {
        puVar14 = local_230;
      }
      pbVar13 = (byte *)0xfd0c0d;
      do {
        bVar6 = *pbVar13;
        pbVar13 = pbVar13 + 1;
        *puVar14 = (uint)bVar6;
        puVar14 = puVar14 + 1;
      } while (pbVar13 != (byte *)0xfd0c12);
      local_2d8 = 5;
      puVar14 = local_29c;
      if (0x20 < local_2d0) {
        puVar14 = local_230 + 5;
      }
      *puVar14 = 0;
                    /* try { // try from 00bf8075 to 00bf8079 has its CatchHandler @ 00bf944e */
      CEGUI::PropertySet::setProperty(*(String **)(this + lVar16 * 8 + 0x2ea8),(String *)&local_2d8)
      ;
                    /* try { // try from 00bf807d to 00bf8081 has its CatchHandler @ 00bf944c */
      CEGUI::String::~String((String *)&local_2d8);
                    /* try { // try from 00bf8085 to 00bf8089 has its CatchHandler @ 00bf9447 */
      CEGUI::String::~String((String *)local_228);
      CEGUI::String::~String((String *)&local_178);
    }
    CEGUI::Window::moveToFront();
    if (param_1[0x348] == (CEquipment)0x0) goto LAB_00bf83b1;
LAB_00bf80b2:
    pSVar19 = (String *)&local_9b8;
    local_9b0 = 0x20;
    local_9a8 = 0;
    local_998 = 0;
    local_9a0 = 0;
    local_910 = (undefined4 *)0x0;
    local_9b8 = 0;
    local_990[0] = 0;
    CEGUI::String::grow((ulong)pSVar19);
    local_9b8 = 0;
    puVar15 = local_990;
    if (0x20 < local_9b0) {
      puVar15 = local_910;
    }
    *puVar15 = 0;
    local_900 = 0x20;
    local_8f8 = 0;
    local_8e8 = 0;
    local_8f0 = 0;
    local_860 = (uint *)0x0;
    local_908 = 0;
    local_8e0[0] = 0;
                    /* try { // try from 00bf81a4 to 00bf81a8 has its CatchHandler @ 00bf945b */
    CEGUI::String::grow((ulong)&local_908);
    puVar14 = local_8e0;
    if (0x20 < local_900) {
      puVar14 = local_860;
    }
    pbVar13 = (byte *)0xfd0c0d;
    do {
      bVar6 = *pbVar13;
      pbVar13 = pbVar13 + 1;
      *puVar14 = (uint)bVar6;
      puVar14 = puVar14 + 1;
    } while (pbVar13 != (byte *)0xfd0c12);
    local_908 = 5;
    puVar14 = local_8cc;
    if (0x20 < local_900) {
      puVar14 = local_860 + 5;
    }
    *puVar14 = 0;
                    /* try { // try from 00bf821d to 00bf8221 has its CatchHandler @ 00bf94b7 */
    CEGUI::PropertySet::setProperty(*(String **)(this + lVar16 * 8 + 0x2988),(String *)&local_908);
                    /* try { // try from 00bf8225 to 00bf8229 has its CatchHandler @ 00bf945b */
    CEGUI::String::~String((String *)&local_908);
  }
  CEGUI::String::~String(pSVar19);
  uVar20 = (ulong)((float)(int)(fVar22 + (float)(uVar23 | uVar24)) + fVar2);
  if (1 < *(uint *)(param_1 + 0x3e0)) {
    CEGUI::Window::getSize();
    uVar23 = -(uint)(0.0 < local_90 * 0.0);
    uVar20 = (ulong)((float)(uVar20 & 0xffffffff) +
                    ((float)(int)((float)(~uVar23 & DAT_00fa86f4 | DAT_00fa4810 & uVar23) +
                                 local_90 * 0.0) + local_8c) * _DAT_00fe6520);
  }
  if (*(int *)(param_1 + 0x3f0) != 0) {
    uVar23 = 0;
    do {
      if (uVar23 < *(uint *)(param_1 + 0x3f4)) {
        this_00 = *(CEquipment **)((ulong)uVar23 * 8 + *(long *)(param_1 + 1000));
        pUVar17 = *(UVector2 **)(this_00 + 0x2c8);
        if (pUVar17 != (UVector2 *)0x0) goto LAB_00bf86a2;
LAB_00bf87fd:
        CEquipment::createIcon(this_00,*(CGameUI **)(this + 0x70),false);
        pUVar17 = *(UVector2 **)(this_00 + 0x2c8);
        if (pUVar17 != (UVector2 *)0x0) {
          CEGUI::EventSet::setMutedState((bool)((char)pUVar17 + '8'));
          pUVar17[0x3e2] = (UVector2)0x1;
          goto LAB_00bf86a2;
        }
      }
      else {
        this_00 = (CEquipment *)**(long **)(param_1 + 1000);
        pUVar17 = *(UVector2 **)(this_00 + 0x2c8);
        if (pUVar17 == (UVector2 *)0x0) goto LAB_00bf87fd;
LAB_00bf86a2:
        if (*(Window **)(pUVar17 + 0xb0) != (Window *)0x0) {
          CEGUI::Window::removeChildWindow(*(Window **)(pUVar17 + 0xb0));
        }
        CEGUI::Window::addChildWindow(*(Window **)(this + 0x30));
        local_a4 = (float)((long)((float)(int)((float)(~uVar21 & uVar8 | uVar7 & uVar21) +
                                              fVar3 * 0.0) + fVar4) & 0xffffffff);
        local_9c = (float)(uVar20 & 0xffffffff);
        local_a8 = 0;
        local_a0 = 0;
                    /* try { // try from 00bf870c to 00bf8710 has its CatchHandler @ 00bf9489 */
        CEGUI::Window::setPosition(pUVar17);
        CEGUI::Window::getSize();
                    /* try { // try from 00bf8733 to 00bf8737 has its CatchHandler @ 00bf94a5 */
        CEGUI::Window::setSize(pUVar17);
        CEGUI::Window::moveToFront();
        pUVar17[0x3e2] = (UVector2)0x1;
      }
      uVar23 = uVar23 + 1;
      CEGUI::Window::getSize();
      uVar24 = -(uint)(0.0 < local_c0 * 0.0);
      if (*(uint *)(param_1 + 0x3f0) <= uVar23) break;
      uVar20 = (ulong)((float)(uVar20 & 0xffffffff) +
                      ((float)(int)((float)(~uVar24 & DAT_00fa86f4 | DAT_00fa4810 & uVar24) +
                                   local_c0 * 0.0) + local_bc) * DAT_00fa4830);
    } while( true );
  }
  cVar9 = (**(code **)(*(long *)param_1 + 0x2f8))(param_1,*(undefined8 *)(this + 0x58),0);
  if (cVar9 == '\0') {
    cVar9 = (**(code **)(*(long *)param_1 + 0x2b0))(param_1);
    if (cVar9 == '\0') {
      pSVar19 = (String *)&local_1408;
      local_1400 = 0x20;
      local_13f8 = 0;
      local_13e8 = 0;
      local_13f0 = 0;
      local_1360 = (uint *)0x0;
      local_1408 = 0;
      local_13e0[0] = 0;
      CEGUI::String::grow((ulong)pSVar19);
      puVar14 = local_13e0;
      if (0x20 < local_1400) {
        puVar14 = local_1360;
      }
      pbVar13 = (byte *)0xfe60e3;
      do {
        bVar6 = *pbVar13;
        pbVar13 = pbVar13 + 1;
        *puVar14 = (uint)bVar6;
        puVar14 = puVar14 + 1;
      } while (pbVar13 != (byte *)0xfe60ee);
      local_1408 = 0xb;
      puVar14 = local_13b4;
      if (0x20 < local_1400) {
        puVar14 = local_1360 + 0xb;
      }
      *puVar14 = 0;
                    /* try { // try from 00bf8dd5 to 00bf8dec has its CatchHandler @ 00bf941a */
      CEGUI::Imageset::getImage(*(String **)(this + 0x3410));
      CEGUI::PropertyHelper::imageToString(local_14b8);
      local_1560 = 0x20;
      local_1558 = 0;
      local_1548 = 0;
      local_1550 = 0;
      local_14c0 = (uint *)0x0;
      local_1568 = 0;
      local_1540[0] = 0;
                    /* try { // try from 00bf8e50 to 00bf8e54 has its CatchHandler @ 00bf9425 */
      CEGUI::String::grow((ulong)&local_1568);
      puVar14 = local_1540;
      if (0x20 < local_1560) {
        puVar14 = local_14c0;
      }
      pbVar13 = (byte *)0xfd0c0d;
      do {
        bVar6 = *pbVar13;
        pbVar13 = pbVar13 + 1;
        *puVar14 = (uint)bVar6;
        puVar14 = puVar14 + 1;
      } while (pbVar13 != (byte *)0xfd0c12);
      local_1568 = 5;
      puVar14 = local_152c;
      if (0x20 < local_1560) {
        puVar14 = local_14c0 + 5;
      }
      *puVar14 = 0;
                    /* try { // try from 00bf8ebd to 00bf8ec1 has its CatchHandler @ 00bf94a7 */
      CEGUI::PropertySet::setProperty
                (*(String **)(this + lVar16 * 8 + 0x2c18),(String *)&local_1568);
                    /* try { // try from 00bf8ec5 to 00bf8ec9 has its CatchHandler @ 00bf9425 */
      CEGUI::String::~String((String *)&local_1568);
                    /* try { // try from 00bf8ecd to 00bf8ed1 has its CatchHandler @ 00bf941a */
      CEGUI::String::~String((String *)local_14b8);
    }
    else {
      pSVar19 = (String *)&local_11f8;
      local_11f0 = 0x20;
      local_11e8 = 0;
      local_11d8 = 0;
      local_11e0 = 0;
      local_1150 = (uint *)0x0;
      local_11f8 = 0;
      local_11d0[0] = 0;
      CEGUI::String::grow((ulong)pSVar19);
      puVar14 = local_11d0;
      if (0x20 < local_11f0) {
        puVar14 = local_1150;
      }
      pcVar12 = "blueredslotglow";
      do {
        bVar6 = *pcVar12;
        pcVar12 = pcVar12 + 1;
        *puVar14 = (uint)bVar6;
        puVar14 = puVar14 + 1;
      } while ((byte *)pcVar12 != (byte *)0xfe60ee);
      local_11f8 = 0xf;
      puVar14 = local_1194;
      if (0x20 < local_11f0) {
        puVar14 = local_1150 + 0xf;
      }
      *puVar14 = 0;
                    /* try { // try from 00bf8c05 to 00bf8c1c has its CatchHandler @ 00bf94c5 */
      CEGUI::Imageset::getImage(*(String **)(this + 0x3410));
      CEGUI::PropertyHelper::imageToString(local_12a8);
      local_1350 = 0x20;
      local_1348 = 0;
      local_1338 = 0;
      local_1340 = 0;
      local_12b0 = (uint *)0x0;
      local_1358 = 0;
      local_1330[0] = 0;
                    /* try { // try from 00bf8c80 to 00bf8c84 has its CatchHandler @ 00bf94bc */
      CEGUI::String::grow((ulong)&local_1358);
      puVar14 = local_1330;
      if (0x20 < local_1350) {
        puVar14 = local_12b0;
      }
      pbVar13 = (byte *)0xfd0c0d;
      do {
        bVar6 = *pbVar13;
        pbVar13 = pbVar13 + 1;
        *puVar14 = (uint)bVar6;
        puVar14 = puVar14 + 1;
      } while (pbVar13 != (byte *)0xfd0c12);
      local_1358 = 5;
      puVar14 = local_131c;
      if (0x20 < local_1350) {
        puVar14 = local_12b0 + 5;
      }
      *puVar14 = 0;
                    /* try { // try from 00bf8ced to 00bf8cf1 has its CatchHandler @ 00bf94e2 */
      CEGUI::PropertySet::setProperty
                (*(String **)(this + lVar16 * 8 + 0x2c18),(String *)&local_1358);
                    /* try { // try from 00bf8cf5 to 00bf8cf9 has its CatchHandler @ 00bf94bc */
      CEGUI::String::~String((String *)&local_1358);
                    /* try { // try from 00bf8cfd to 00bf8d01 has its CatchHandler @ 00bf94c5 */
      CEGUI::String::~String((String *)local_12a8);
    }
  }
  else {
    cVar9 = CBaseUnit::ISA((CBaseUnit *)param_1,0x36);
    if (cVar9 == '\0') {
      cVar9 = (**(code **)(*(long *)param_1 + 0x2b0))(param_1);
      if (cVar9 != '\0') {
        cVar9 = CBaseUnit::ISA((CBaseUnit *)param_1,0x37);
        if (cVar9 == '\0') {
          pSVar19 = local_e88;
          CEGUI::String::String(pSVar19,"greenslotglow");
                    /* try { // try from 00bf925b to 00bf9272 has its CatchHandler @ 00bf9505 */
          CEGUI::Imageset::getImage(*(String **)(this + 0x3410));
          CEGUI::PropertyHelper::imageToString(local_f38);
                    /* try { // try from 00bf9283 to 00bf9287 has its CatchHandler @ 00bf94f5 */
          CEGUI::String::String(local_fe8,"Image");
                    /* try { // try from 00bf929b to 00bf929f has its CatchHandler @ 00bf94e7 */
          CEGUI::PropertySet::setProperty(*(String **)(this + lVar16 * 8 + 0x2c18),local_fe8);
                    /* try { // try from 00bf92a3 to 00bf92a7 has its CatchHandler @ 00bf94f5 */
          CEGUI::String::~String(local_fe8);
                    /* try { // try from 00bf92ab to 00bf92af has its CatchHandler @ 00bf9505 */
          CEGUI::String::~String((String *)local_f38);
        }
        else {
          pSVar19 = local_c78;
          CEGUI::String::String(pSVar19,"blueslotglow");
                    /* try { // try from 00bf8f20 to 00bf8f37 has its CatchHandler @ 00bf9369 */
          CEGUI::Imageset::getImage(*(String **)(this + 0x3410));
          CEGUI::PropertyHelper::imageToString(local_d28);
                    /* try { // try from 00bf8f48 to 00bf8f4c has its CatchHandler @ 00bf9367 */
          CEGUI::String::String(local_dd8,"Image");
                    /* try { // try from 00bf8f60 to 00bf8f64 has its CatchHandler @ 00bf9336 */
          CEGUI::PropertySet::setProperty(*(String **)(this + lVar16 * 8 + 0x2c18),local_dd8);
                    /* try { // try from 00bf8f68 to 00bf8f6c has its CatchHandler @ 00bf9367 */
          CEGUI::String::~String(local_dd8);
                    /* try { // try from 00bf8f70 to 00bf8f74 has its CatchHandler @ 00bf9369 */
          CEGUI::String::~String((String *)local_d28);
        }
        CEGUI::String::~String(pSVar19);
        goto LAB_00bf8a42;
      }
      pSVar19 = (String *)&local_1148;
      local_1140 = 0x20;
      local_1138 = 0;
      local_1128 = 0;
      local_1130 = 0;
      local_10a0 = (undefined4 *)0x0;
      local_1148 = 0;
      local_1120[0] = 0;
      CEGUI::String::grow((ulong)pSVar19);
      local_1148 = 0;
      puVar15 = local_1120;
      if (0x20 < local_1140) {
        puVar15 = local_10a0;
      }
      *puVar15 = 0;
      local_1090 = 0x20;
      local_1088 = 0;
      local_1078 = 0;
      local_1080 = 0;
      local_ff0 = (uint *)0x0;
      local_1098 = 0;
      local_1070[0] = 0;
                    /* try { // try from 00bf90b4 to 00bf90b8 has its CatchHandler @ 00bf938d */
      CEGUI::String::grow((ulong)&local_1098);
      puVar14 = local_1070;
      if (0x20 < local_1090) {
        puVar14 = local_ff0;
      }
      pbVar13 = (byte *)0xfd0c0d;
      do {
        bVar6 = *pbVar13;
        pbVar13 = pbVar13 + 1;
        *puVar14 = (uint)bVar6;
        puVar14 = puVar14 + 1;
      } while (pbVar13 != (byte *)0xfd0c12);
      local_1098 = 5;
      puVar14 = local_105c;
      if (0x20 < local_1090) {
        puVar14 = local_ff0 + 5;
      }
      *puVar14 = 0;
                    /* try { // try from 00bf912d to 00bf9131 has its CatchHandler @ 00bf9372 */
      CEGUI::PropertySet::setProperty
                (*(String **)(this + lVar16 * 8 + 0x2c18),(String *)&local_1098);
                    /* try { // try from 00bf9135 to 00bf9139 has its CatchHandler @ 00bf938d */
      CEGUI::String::~String((String *)&local_1098);
    }
    else {
      pSVar19 = (String *)&local_a68;
      local_a60 = 0x20;
      local_a58 = 0;
      local_a48 = 0;
      local_a50 = 0;
      local_9c0 = (uint *)0x0;
      local_a68 = 0;
      local_a40[0] = 0;
      CEGUI::String::grow((ulong)pSVar19);
      puVar14 = local_a40;
      if (0x20 < local_a60) {
        puVar14 = local_9c0;
      }
      pcVar12 = "goldslotglow";
      do {
        bVar6 = *pcVar12;
        pcVar12 = pcVar12 + 1;
        *puVar14 = (uint)bVar6;
        puVar14 = puVar14 + 1;
      } while ((byte *)pcVar12 != (byte *)0xfe60a7);
      local_a68 = 0xc;
      puVar14 = local_a10;
      if (0x20 < local_a60) {
        puVar14 = local_9c0 + 0xc;
      }
      *puVar14 = 0;
                    /* try { // try from 00bf893d to 00bf8954 has its CatchHandler @ 00bf9475 */
      CEGUI::Imageset::getImage(*(String **)(this + 0x3410));
      CEGUI::PropertyHelper::imageToString(local_b18);
      local_bc0 = 0x20;
      local_bb8 = 0;
      local_ba8 = 0;
      local_bb0 = 0;
      local_b20 = (uint *)0x0;
      local_bc8 = 0;
      local_ba0[0] = 0;
                    /* try { // try from 00bf89b8 to 00bf89bc has its CatchHandler @ 00bf947a */
      CEGUI::String::grow((ulong)&local_bc8);
      puVar14 = local_ba0;
      if (0x20 < local_bc0) {
        puVar14 = local_b20;
      }
      pbVar13 = (byte *)0xfd0c0d;
      do {
        bVar6 = *pbVar13;
        pbVar13 = pbVar13 + 1;
        *puVar14 = (uint)bVar6;
        puVar14 = puVar14 + 1;
      } while (pbVar13 != (byte *)0xfd0c12);
      local_bc8 = 5;
      puVar14 = local_b8c;
      if (0x20 < local_bc0) {
        puVar14 = local_b20 + 5;
      }
      *puVar14 = 0;
                    /* try { // try from 00bf8a25 to 00bf8a29 has its CatchHandler @ 00bf9460 */
      CEGUI::PropertySet::setProperty(*(String **)(this + lVar16 * 8 + 0x2c18),(String *)&local_bc8)
      ;
                    /* try { // try from 00bf8a2d to 00bf8a31 has its CatchHandler @ 00bf947a */
      CEGUI::String::~String((String *)&local_bc8);
                    /* try { // try from 00bf8a35 to 00bf8a39 has its CatchHandler @ 00bf9475 */
      CEGUI::String::~String((String *)local_b18);
    }
  }
  CEGUI::String::~String(pSVar19);
LAB_00bf8a42:
  if (*(long *)(this + lVar16 * 8 + 0x3138) != 0) {
    bVar18 = SUB81(*(long *)(this + lVar16 * 8 + 0x3138),0);
    if (*(int *)(param_1 + 0x238) < 2) {
      CEGUI::Window::setVisible(bVar18);
    }
    else {
      CEGUI::Window::setVisible(bVar18);
      STRINGS::GetValueAsString((STRINGS *)local_58,*(int *)(param_1 + 0x238));
                    /* try { // try from 00bf8a9a to 00bf8a9e has its CatchHandler @ 00bf9462 */
      std::operator+((char *)local_48,(string *)&DAT_0103f7f3);
      if ((allocator *)(local_58[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_58[0] + -8);
        iVar5 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar5 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
        }
      }
                    /* try { // try from 00bf8ac8 to 00bf8acc has its CatchHandler @ 00bf93be */
      CEGUI::String::String(local_1618,local_48[0]);
                    /* try { // try from 00bf8add to 00bf8ae1 has its CatchHandler @ 00bf93dc */
      CEGUI::Window::setText(*(String **)(this + lVar16 * 8 + 0x3138));
                    /* try { // try from 00bf8ae5 to 00bf8ae9 has its CatchHandler @ 00bf93be */
      CEGUI::String::~String(local_1618);
      if ((allocator *)(local_48[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_48[0] + -8);
        iVar5 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar5 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
        }
      }
    }
  }
  return;
}

/* address=00bf9520
   symbol=CStashMenu::setSlotIcon */

/* WARNING: Removing unreachable block (ram,0x00bfac11) */
/* WARNING: Removing unreachable block (ram,0x00bfac7c) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CStashMenu::setSlotIcon(CEquipment*, int, int) */

void __thiscall
CStashMenu::setSlotIcon(CStashMenu *this,CEquipment *param_1,int param_2,int param_3)

{
  int *piVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  byte bVar6;
  uint uVar7;
  uint uVar8;
  char cVar9;
  long lVar10;
  float *pfVar11;
  char *pcVar12;
  byte *pbVar13;
  CEquipment *this_00;
  uint *puVar14;
  undefined4 *puVar15;
  long lVar16;
  UVector2 *pUVar17;
  bool bVar18;
  String *pSVar19;
  ulong uVar20;
  uint uVar21;
  float fVar22;
  uint uVar23;
  uint uVar24;
  String local_1618 [176];
  undefined8 local_1568;
  ulong local_1560;
  undefined8 local_1558;
  undefined8 local_1550;
  undefined8 local_1548;
  uint local_1540 [5];
  uint local_152c [27];
  uint *local_14c0;
  Image local_14b8 [176];
  undefined8 local_1408;
  ulong local_1400;
  undefined8 local_13f8;
  undefined8 local_13f0;
  undefined8 local_13e8;
  uint local_13e0 [11];
  uint local_13b4 [21];
  uint *local_1360;
  undefined8 local_1358;
  ulong local_1350;
  undefined8 local_1348;
  undefined8 local_1340;
  undefined8 local_1338;
  uint local_1330 [5];
  uint local_131c [27];
  uint *local_12b0;
  Image local_12a8 [176];
  undefined8 local_11f8;
  ulong local_11f0;
  undefined8 local_11e8;
  undefined8 local_11e0;
  undefined8 local_11d8;
  uint local_11d0 [15];
  uint local_1194 [17];
  uint *local_1150;
  undefined8 local_1148;
  ulong local_1140;
  undefined8 local_1138;
  undefined8 local_1130;
  undefined8 local_1128;
  undefined4 local_1120 [32];
  undefined4 *local_10a0;
  undefined8 local_1098;
  ulong local_1090;
  undefined8 local_1088;
  undefined8 local_1080;
  undefined8 local_1078;
  uint local_1070 [5];
  uint local_105c [27];
  uint *local_ff0;
  String local_fe8 [176];
  Image local_f38 [176];
  String local_e88 [176];
  String local_dd8 [176];
  Image local_d28 [176];
  String local_c78 [176];
  undefined8 local_bc8;
  ulong local_bc0;
  undefined8 local_bb8;
  undefined8 local_bb0;
  undefined8 local_ba8;
  uint local_ba0 [5];
  uint local_b8c [27];
  uint *local_b20;
  Image local_b18 [176];
  undefined8 local_a68;
  ulong local_a60;
  undefined8 local_a58;
  undefined8 local_a50;
  undefined8 local_a48;
  uint local_a40 [12];
  uint local_a10 [20];
  uint *local_9c0;
  undefined8 local_9b8;
  ulong local_9b0;
  undefined8 local_9a8;
  undefined8 local_9a0;
  undefined8 local_998;
  undefined4 local_990 [32];
  undefined4 *local_910;
  undefined8 local_908;
  ulong local_900;
  undefined8 local_8f8;
  undefined8 local_8f0;
  undefined8 local_8e8;
  uint local_8e0 [5];
  uint local_8cc [27];
  uint *local_860;
  undefined8 local_858;
  ulong local_850;
  undefined8 local_848;
  undefined8 local_840;
  undefined8 local_838;
  uint local_830 [5];
  uint local_81c [27];
  uint *local_7b0;
  Image local_7a8 [176];
  undefined8 local_6f8;
  ulong local_6f0;
  undefined8 local_6e8;
  undefined8 local_6e0;
  undefined8 local_6d8;
  uint local_6d0 [12];
  uint local_6a0 [20];
  uint *local_650;
  undefined8 local_648;
  ulong local_640;
  undefined8 local_638;
  undefined8 local_630;
  undefined8 local_628;
  undefined4 local_620 [32];
  undefined4 *local_5a0;
  undefined8 local_598;
  ulong local_590;
  undefined8 local_588;
  undefined8 local_580;
  undefined8 local_578;
  uint local_570 [5];
  uint local_55c [27];
  uint *local_4f0;
  String local_4e8 [176];
  Image local_438 [176];
  String local_388 [176];
  undefined8 local_2d8;
  ulong local_2d0;
  undefined8 local_2c8;
  undefined8 local_2c0;
  undefined8 local_2b8;
  uint local_2b0 [5];
  uint local_29c [27];
  uint *local_230;
  Image local_228 [176];
  undefined8 local_178;
  ulong local_170;
  undefined8 local_168;
  undefined8 local_160;
  undefined8 local_158;
  uint local_150 [13];
  uint local_11c [19];
  uint *local_d0;
  float local_c0;
  float local_bc;
  undefined4 local_a8;
  float local_a4;
  undefined4 local_a0;
  float local_9c;
  float local_90;
  float local_8c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  long local_58 [2];
  uchar *local_48 [3];

  lVar16 = (long)param_2;
  lVar10 = CEGUI::Window::getPosition();
  uVar8 = DAT_00fa86f4;
  uVar7 = DAT_00fa4810;
  fVar22 = *(float *)(lVar10 + 8) * 0.0;
  uVar21 = -(uint)(0.0 < fVar22);
  uVar24 = DAT_00fa4810 & uVar21;
  uVar23 = ~uVar21 & DAT_00fa86f4;
  fVar2 = *(float *)(lVar10 + 0xc);
  pfVar11 = (float *)CEGUI::Window::getPosition();
  fVar3 = *pfVar11;
  pUVar17 = *(UVector2 **)(param_1 + 0x2c8);
  uVar21 = -(uint)(0.0 < fVar3 * 0.0);
  fVar4 = pfVar11[1];
  if (pUVar17 == (UVector2 *)0x0) {
    CEquipment::createIcon(param_1,*(CGameUI **)(this + 0x70),false);
    pUVar17 = *(UVector2 **)(param_1 + 0x2c8);
    if (pUVar17 != (UVector2 *)0x0) {
      CEGUI::EventSet::setMutedState((bool)((char)pUVar17 + '8'));
      pUVar17[0x3e2] = (UVector2)0x1;
      goto LAB_00bf960c;
    }
  }
  else {
LAB_00bf960c:
    if (*(Window **)(pUVar17 + 0xb0) != (Window *)0x0) {
      CEGUI::Window::removeChildWindow(*(Window **)(pUVar17 + 0xb0));
    }
    CEGUI::Window::addChildWindow(*(Window **)(this + lVar16 * 8 + 0x1de8));
    local_64 = 0;
    local_68 = 0;
    local_5c = 0x3f800000;
    local_60 = 0;
                    /* try { // try from 00bf966c to 00bf9670 has its CatchHandler @ 00bfad15 */
    CEGUI::Window::setPosition(pUVar17);
    local_74 = 0;
    local_78 = 0;
    local_6c = 0;
    local_70 = 0;
                    /* try { // try from 00bf96a8 to 00bf96ac has its CatchHandler @ 00bfacc5 */
    CEGUI::Window::setPosition(pUVar17);
    CEGUI::Window::getSize();
                    /* try { // try from 00bf96d0 to 00bf96d4 has its CatchHandler @ 00bfacbc */
    CEGUI::Window::setSize(pUVar17);
    CEGUI::Window::moveToFront();
    *(CStashMenu **)(pUVar17 + 0x1d8) = this + (long)param_3 * 4 + 0xb0;
  }
  if ((param_1[0x348] == (CEquipment)0x0) || (*(uint *)(param_1 + 0x3e0) == 0)) {
    local_640 = 0x20;
    local_638 = 0;
    local_628 = 0;
    local_630 = 0;
    local_5a0 = (undefined4 *)0x0;
    local_648 = 0;
    local_620[0] = 0;
    CEGUI::String::grow((ulong)&local_648);
    local_648 = 0;
    puVar15 = local_620;
    if (0x20 < local_640) {
      puVar15 = local_5a0;
    }
    *puVar15 = 0;
    local_590 = 0x20;
    local_588 = 0;
    local_578 = 0;
    local_580 = 0;
    local_4f0 = (uint *)0x0;
    local_598 = 0;
    local_570[0] = 0;
                    /* try { // try from 00bf9b8d to 00bf9b91 has its CatchHandler @ 00bfacd2 */
    CEGUI::String::grow((ulong)&local_598);
    puVar14 = local_570;
    if (0x20 < local_590) {
      puVar14 = local_4f0;
    }
    pbVar13 = (byte *)0xfd0c0d;
    do {
      bVar6 = *pbVar13;
      pbVar13 = pbVar13 + 1;
      *puVar14 = (uint)bVar6;
      puVar14 = puVar14 + 1;
    } while (pbVar13 != (byte *)0xfd0c12);
    local_598 = 5;
    puVar14 = local_55c;
    if (0x20 < local_590) {
      puVar14 = local_4f0 + 5;
    }
    *puVar14 = 0;
                    /* try { // try from 00bf9bfe to 00bf9c02 has its CatchHandler @ 00bface9 */
    CEGUI::PropertySet::setProperty(*(String **)(this + lVar16 * 8 + 0x1960),(String *)&local_598);
                    /* try { // try from 00bf9c06 to 00bf9c0a has its CatchHandler @ 00bfacd2 */
    CEGUI::String::~String((String *)&local_598);
    CEGUI::String::~String((String *)&local_648);
    if (param_1[0x348] != (CEquipment)0x0) goto LAB_00bf991a;
LAB_00bf9c21:
    pSVar19 = (String *)&local_6f8;
    local_6f0 = 0x20;
    local_6e8 = 0;
    local_6d8 = 0;
    local_6e0 = 0;
    local_650 = (uint *)0x0;
    local_6f8 = 0;
    local_6d0[0] = 0;
    CEGUI::String::grow((ulong)pSVar19);
    puVar14 = local_6d0;
    if (0x20 < local_6f0) {
      puVar14 = local_650;
    }
    pcVar12 = "unidentified";
    do {
      bVar6 = *pcVar12;
      pcVar12 = pcVar12 + 1;
      *puVar14 = (uint)bVar6;
      puVar14 = puVar14 + 1;
    } while ((byte *)pcVar12 != (byte *)0xfef79d);
    local_6f8 = 0xc;
    puVar14 = local_6a0;
    if (0x20 < local_6f0) {
      puVar14 = local_650 + 0xc;
    }
    *puVar14 = 0;
                    /* try { // try from 00bf9cfd to 00bf9d14 has its CatchHandler @ 00bfac55 */
    CEGUI::Imageset::getImage(*(String **)(this + 0x3410));
    CEGUI::PropertyHelper::imageToString(local_7a8);
    local_850 = 0x20;
    local_848 = 0;
    local_838 = 0;
    local_840 = 0;
    local_7b0 = (uint *)0x0;
    local_858 = 0;
    local_830[0] = 0;
                    /* try { // try from 00bf9d78 to 00bf9d7c has its CatchHandler @ 00bfac7a */
    CEGUI::String::grow((ulong)&local_858);
    puVar14 = local_830;
    if (0x20 < local_850) {
      puVar14 = local_7b0;
    }
    pbVar13 = (byte *)0xfd0c0d;
    do {
      bVar6 = *pbVar13;
      pbVar13 = pbVar13 + 1;
      *puVar14 = (uint)bVar6;
      puVar14 = puVar14 + 1;
    } while (pbVar13 != (byte *)0xfd0c12);
    local_858 = 5;
    puVar14 = local_81c;
    if (0x20 < local_850) {
      puVar14 = local_7b0 + 5;
    }
    *puVar14 = 0;
                    /* try { // try from 00bf9df5 to 00bf9df9 has its CatchHandler @ 00bfacc7 */
    CEGUI::PropertySet::setProperty(*(String **)(this + lVar16 * 8 + 0x14d8),(String *)&local_858);
                    /* try { // try from 00bf9dfd to 00bf9e01 has its CatchHandler @ 00bfac7a */
    CEGUI::String::~String((String *)&local_858);
                    /* try { // try from 00bf9e05 to 00bf9e09 has its CatchHandler @ 00bfac55 */
    CEGUI::String::~String((String *)local_7a8);
  }
  else {
    if (*(uint *)(param_1 + 0x3e0) < 2) {
      CEGUI::String::String(local_388,"onesocketglow");
                    /* try { // try from 00bfab14 to 00bfab2b has its CatchHandler @ 00bfaba2 */
      CEGUI::Imageset::getImage(*(String **)(this + 0x3410));
      CEGUI::PropertyHelper::imageToString(local_438);
                    /* try { // try from 00bfab3c to 00bfab40 has its CatchHandler @ 00bfab9b */
      CEGUI::String::String(local_4e8,"Image");
                    /* try { // try from 00bfab54 to 00bfab58 has its CatchHandler @ 00bfab99 */
      CEGUI::PropertySet::setProperty(*(String **)(this + lVar16 * 8 + 0x1960),local_4e8);
                    /* try { // try from 00bfab5c to 00bfab60 has its CatchHandler @ 00bfab9b */
      CEGUI::String::~String(local_4e8);
                    /* try { // try from 00bfab64 to 00bfab68 has its CatchHandler @ 00bfaba2 */
      CEGUI::String::~String((String *)local_438);
      CEGUI::String::~String(local_388);
    }
    else {
      local_170 = 0x20;
      local_168 = 0;
      local_158 = 0;
      local_160 = 0;
      local_d0 = (uint *)0x0;
      local_178 = 0;
      local_150[0] = 0;
      CEGUI::String::grow((ulong)&local_178);
      puVar14 = local_150;
      if (0x20 < local_170) {
        puVar14 = local_d0;
      }
      pcVar12 = "twosocketglow";
      do {
        bVar6 = *pcVar12;
        pcVar12 = pcVar12 + 1;
        *puVar14 = (uint)bVar6;
        puVar14 = puVar14 + 1;
      } while ((byte *)pcVar12 != (byte *)0xfe60d0);
      local_178 = 0xd;
      puVar14 = local_11c;
      if (0x20 < local_170) {
        puVar14 = local_d0 + 0xd;
      }
      *puVar14 = 0;
                    /* try { // try from 00bf97ed to 00bf9804 has its CatchHandler @ 00bfac87 */
      CEGUI::Imageset::getImage(*(String **)(this + 0x3410));
      CEGUI::PropertyHelper::imageToString(local_228);
      local_2d0 = 0x20;
      local_2c8 = 0;
      local_2b8 = 0;
      local_2c0 = 0;
      local_230 = (uint *)0x0;
      local_2d8 = 0;
      local_2b0[0] = 0;
                    /* try { // try from 00bf9868 to 00bf986c has its CatchHandler @ 00bfac8c */
      CEGUI::String::grow((ulong)&local_2d8);
      puVar14 = local_2b0;
      if (0x20 < local_2d0) {
        puVar14 = local_230;
      }
      pbVar13 = (byte *)0xfd0c0d;
      do {
        bVar6 = *pbVar13;
        pbVar13 = pbVar13 + 1;
        *puVar14 = (uint)bVar6;
        puVar14 = puVar14 + 1;
      } while (pbVar13 != (byte *)0xfd0c12);
      local_2d8 = 5;
      puVar14 = local_29c;
      if (0x20 < local_2d0) {
        puVar14 = local_230 + 5;
      }
      *puVar14 = 0;
                    /* try { // try from 00bf98dd to 00bf98e1 has its CatchHandler @ 00bfac8e */
      CEGUI::PropertySet::setProperty(*(String **)(this + lVar16 * 8 + 0x1960),(String *)&local_2d8)
      ;
                    /* try { // try from 00bf98e5 to 00bf98e9 has its CatchHandler @ 00bfac8c */
      CEGUI::String::~String((String *)&local_2d8);
                    /* try { // try from 00bf98ed to 00bf98f1 has its CatchHandler @ 00bfac87 */
      CEGUI::String::~String((String *)local_228);
      CEGUI::String::~String((String *)&local_178);
    }
    CEGUI::Window::moveToFront();
    if (param_1[0x348] == (CEquipment)0x0) goto LAB_00bf9c21;
LAB_00bf991a:
    pSVar19 = (String *)&local_9b8;
    local_9b0 = 0x20;
    local_9a8 = 0;
    local_998 = 0;
    local_9a0 = 0;
    local_910 = (undefined4 *)0x0;
    local_9b8 = 0;
    local_990[0] = 0;
    CEGUI::String::grow((ulong)pSVar19);
    local_9b8 = 0;
    puVar15 = local_990;
    if (0x20 < local_9b0) {
      puVar15 = local_910;
    }
    *puVar15 = 0;
    local_900 = 0x20;
    local_8f8 = 0;
    local_8e8 = 0;
    local_8f0 = 0;
    local_860 = (uint *)0x0;
    local_908 = 0;
    local_8e0[0] = 0;
                    /* try { // try from 00bf9a0c to 00bf9a10 has its CatchHandler @ 00bfac9b */
    CEGUI::String::grow((ulong)&local_908);
    puVar14 = local_8e0;
    if (0x20 < local_900) {
      puVar14 = local_860;
    }
    pbVar13 = (byte *)0xfd0c0d;
    do {
      bVar6 = *pbVar13;
      pbVar13 = pbVar13 + 1;
      *puVar14 = (uint)bVar6;
      puVar14 = puVar14 + 1;
    } while (pbVar13 != (byte *)0xfd0c12);
    local_908 = 5;
    puVar14 = local_8cc;
    if (0x20 < local_900) {
      puVar14 = local_860 + 5;
    }
    *puVar14 = 0;
                    /* try { // try from 00bf9a85 to 00bf9a89 has its CatchHandler @ 00bfacf7 */
    CEGUI::PropertySet::setProperty(*(String **)(this + lVar16 * 8 + 0x14d8),(String *)&local_908);
                    /* try { // try from 00bf9a8d to 00bf9a91 has its CatchHandler @ 00bfac9b */
    CEGUI::String::~String((String *)&local_908);
  }
  CEGUI::String::~String(pSVar19);
  uVar20 = (ulong)((float)(int)(fVar22 + (float)(uVar23 | uVar24)) + fVar2);
  if (1 < *(uint *)(param_1 + 0x3e0)) {
    CEGUI::Window::getSize();
    uVar23 = -(uint)(0.0 < local_90 * 0.0);
    uVar20 = (ulong)((float)(uVar20 & 0xffffffff) +
                    ((float)(int)((float)(~uVar23 & DAT_00fa86f4 | DAT_00fa4810 & uVar23) +
                                 local_90 * 0.0) + local_8c) * _DAT_00fe6520);
  }
  if (*(int *)(param_1 + 0x3f0) != 0) {
    uVar23 = 0;
    do {
      if (uVar23 < *(uint *)(param_1 + 0x3f4)) {
        this_00 = *(CEquipment **)((ulong)uVar23 * 8 + *(long *)(param_1 + 1000));
        pUVar17 = *(UVector2 **)(this_00 + 0x2c8);
        if (pUVar17 != (UVector2 *)0x0) goto LAB_00bf9f02;
LAB_00bfa058:
        CEquipment::createIcon(this_00,*(CGameUI **)(this + 0x70),false);
        pUVar17 = *(UVector2 **)(this_00 + 0x2c8);
        if (pUVar17 != (UVector2 *)0x0) {
          CEGUI::EventSet::setMutedState((bool)((char)pUVar17 + '8'));
          pUVar17[0x3e2] = (UVector2)0x1;
          goto LAB_00bf9f02;
        }
      }
      else {
        this_00 = (CEquipment *)**(long **)(param_1 + 1000);
        pUVar17 = *(UVector2 **)(this_00 + 0x2c8);
        if (pUVar17 == (UVector2 *)0x0) goto LAB_00bfa058;
LAB_00bf9f02:
        if (*(Window **)(pUVar17 + 0xb0) != (Window *)0x0) {
          CEGUI::Window::removeChildWindow(*(Window **)(pUVar17 + 0xb0));
        }
        CEGUI::Window::addChildWindow(*(Window **)(this + 0x30));
        local_a4 = (float)((long)((float)(int)((float)(~uVar21 & uVar8 | uVar7 & uVar21) +
                                              fVar3 * 0.0) + fVar4) & 0xffffffff);
        local_9c = (float)(uVar20 & 0xffffffff);
        local_a8 = 0;
        local_a0 = 0;
                    /* try { // try from 00bf9f6c to 00bf9f70 has its CatchHandler @ 00bfacc9 */
        CEGUI::Window::setPosition(pUVar17);
        CEGUI::Window::getSize();
                    /* try { // try from 00bf9f8e to 00bf9f92 has its CatchHandler @ 00bface5 */
        CEGUI::Window::setSize(pUVar17);
        CEGUI::Window::moveToFront();
        pUVar17[0x3e2] = (UVector2)0x1;
      }
      uVar23 = uVar23 + 1;
      CEGUI::Window::getSize();
      uVar24 = -(uint)(0.0 < local_c0 * 0.0);
      if (*(uint *)(param_1 + 0x3f0) <= uVar23) break;
      uVar20 = (ulong)((float)(uVar20 & 0xffffffff) +
                      ((float)(int)((float)(~uVar24 & DAT_00fa86f4 | DAT_00fa4810 & uVar24) +
                                   local_c0 * 0.0) + local_bc) * DAT_00fa4830);
    } while( true );
  }
  cVar9 = (**(code **)(*(long *)param_1 + 0x2f8))(param_1,*(undefined8 *)(this + 0x58),0);
  if (cVar9 == '\0') {
    cVar9 = (**(code **)(*(long *)param_1 + 0x2b0))(param_1);
    if (cVar9 == '\0') {
      pSVar19 = (String *)&local_1408;
      local_1400 = 0x20;
      local_13f8 = 0;
      local_13e8 = 0;
      local_13f0 = 0;
      local_1360 = (uint *)0x0;
      local_1408 = 0;
      local_13e0[0] = 0;
      CEGUI::String::grow((ulong)pSVar19);
      puVar14 = local_13e0;
      if (0x20 < local_1400) {
        puVar14 = local_1360;
      }
      pbVar13 = (byte *)0xfe60e3;
      do {
        bVar6 = *pbVar13;
        pbVar13 = pbVar13 + 1;
        *puVar14 = (uint)bVar6;
        puVar14 = puVar14 + 1;
      } while (pbVar13 != (byte *)0xfe60ee);
      local_1408 = 0xb;
      puVar14 = local_13b4;
      if (0x20 < local_1400) {
        puVar14 = local_1360 + 0xb;
      }
      *puVar14 = 0;
                    /* try { // try from 00bfa615 to 00bfa62c has its CatchHandler @ 00bfac5a */
      CEGUI::Imageset::getImage(*(String **)(this + 0x3410));
      CEGUI::PropertyHelper::imageToString(local_14b8);
      local_1560 = 0x20;
      local_1558 = 0;
      local_1548 = 0;
      local_1550 = 0;
      local_14c0 = (uint *)0x0;
      local_1568 = 0;
      local_1540[0] = 0;
                    /* try { // try from 00bfa690 to 00bfa694 has its CatchHandler @ 00bfac65 */
      CEGUI::String::grow((ulong)&local_1568);
      puVar14 = local_1540;
      if (0x20 < local_1560) {
        puVar14 = local_14c0;
      }
      pbVar13 = (byte *)0xfd0c0d;
      do {
        bVar6 = *pbVar13;
        pbVar13 = pbVar13 + 1;
        *puVar14 = (uint)bVar6;
        puVar14 = puVar14 + 1;
      } while (pbVar13 != (byte *)0xfd0c12);
      local_1568 = 5;
      puVar14 = local_152c;
      if (0x20 < local_1560) {
        puVar14 = local_14c0 + 5;
      }
      *puVar14 = 0;
                    /* try { // try from 00bfa6fd to 00bfa701 has its CatchHandler @ 00bface7 */
      CEGUI::PropertySet::setProperty
                (*(String **)(this + lVar16 * 8 + 0x1050),(String *)&local_1568);
                    /* try { // try from 00bfa705 to 00bfa709 has its CatchHandler @ 00bfac65 */
      CEGUI::String::~String((String *)&local_1568);
                    /* try { // try from 00bfa70d to 00bfa711 has its CatchHandler @ 00bfac5a */
      CEGUI::String::~String((String *)local_14b8);
    }
    else {
      pSVar19 = (String *)&local_11f8;
      local_11f0 = 0x20;
      local_11e8 = 0;
      local_11d8 = 0;
      local_11e0 = 0;
      local_1150 = (uint *)0x0;
      local_11f8 = 0;
      local_11d0[0] = 0;
      CEGUI::String::grow((ulong)pSVar19);
      puVar14 = local_11d0;
      if (0x20 < local_11f0) {
        puVar14 = local_1150;
      }
      pcVar12 = "blueredslotglow";
      do {
        bVar6 = *pcVar12;
        pcVar12 = pcVar12 + 1;
        *puVar14 = (uint)bVar6;
        puVar14 = puVar14 + 1;
      } while ((byte *)pcVar12 != (byte *)0xfe60ee);
      local_11f8 = 0xf;
      puVar14 = local_1194;
      if (0x20 < local_11f0) {
        puVar14 = local_1150 + 0xf;
      }
      *puVar14 = 0;
                    /* try { // try from 00bfa44d to 00bfa464 has its CatchHandler @ 00bfad05 */
      CEGUI::Imageset::getImage(*(String **)(this + 0x3410));
      CEGUI::PropertyHelper::imageToString(local_12a8);
      local_1350 = 0x20;
      local_1348 = 0;
      local_1338 = 0;
      local_1340 = 0;
      local_12b0 = (uint *)0x0;
      local_1358 = 0;
      local_1330[0] = 0;
                    /* try { // try from 00bfa4c8 to 00bfa4cc has its CatchHandler @ 00bfacfc */
      CEGUI::String::grow((ulong)&local_1358);
      puVar14 = local_1330;
      if (0x20 < local_1350) {
        puVar14 = local_12b0;
      }
      pbVar13 = (byte *)0xfd0c0d;
      do {
        bVar6 = *pbVar13;
        pbVar13 = pbVar13 + 1;
        *puVar14 = (uint)bVar6;
        puVar14 = puVar14 + 1;
      } while (pbVar13 != (byte *)0xfd0c12);
      local_1358 = 5;
      puVar14 = local_131c;
      if (0x20 < local_1350) {
        puVar14 = local_12b0 + 5;
      }
      *puVar14 = 0;
                    /* try { // try from 00bfa535 to 00bfa539 has its CatchHandler @ 00bfad22 */
      CEGUI::PropertySet::setProperty
                (*(String **)(this + lVar16 * 8 + 0x1050),(String *)&local_1358);
                    /* try { // try from 00bfa53d to 00bfa541 has its CatchHandler @ 00bfacfc */
      CEGUI::String::~String((String *)&local_1358);
                    /* try { // try from 00bfa545 to 00bfa549 has its CatchHandler @ 00bfad05 */
      CEGUI::String::~String((String *)local_12a8);
    }
  }
  else {
    cVar9 = CBaseUnit::ISA((CBaseUnit *)param_1,0x36);
    if (cVar9 == '\0') {
      cVar9 = (**(code **)(*(long *)param_1 + 0x2b0))(param_1);
      if (cVar9 != '\0') {
        cVar9 = CBaseUnit::ISA((CBaseUnit *)param_1,0x37);
        if (cVar9 == '\0') {
          pSVar19 = local_e88;
          CEGUI::String::String(pSVar19,"greenslotglow");
                    /* try { // try from 00bfaa9b to 00bfaab2 has its CatchHandler @ 00bfad45 */
          CEGUI::Imageset::getImage(*(String **)(this + 0x3410));
          CEGUI::PropertyHelper::imageToString(local_f38);
                    /* try { // try from 00bfaac3 to 00bfaac7 has its CatchHandler @ 00bfad35 */
          CEGUI::String::String(local_fe8,"Image");
                    /* try { // try from 00bfaadb to 00bfaadf has its CatchHandler @ 00bfad27 */
          CEGUI::PropertySet::setProperty(*(String **)(this + lVar16 * 8 + 0x1050),local_fe8);
                    /* try { // try from 00bfaae3 to 00bfaae7 has its CatchHandler @ 00bfad35 */
          CEGUI::String::~String(local_fe8);
                    /* try { // try from 00bfaaeb to 00bfaaef has its CatchHandler @ 00bfad45 */
          CEGUI::String::~String((String *)local_f38);
        }
        else {
          pSVar19 = local_c78;
          CEGUI::String::String(pSVar19,"blueslotglow");
                    /* try { // try from 00bfa75f to 00bfa776 has its CatchHandler @ 00bfaba9 */
          CEGUI::Imageset::getImage(*(String **)(this + 0x3410));
          CEGUI::PropertyHelper::imageToString(local_d28);
                    /* try { // try from 00bfa787 to 00bfa78b has its CatchHandler @ 00bfaba7 */
          CEGUI::String::String(local_dd8,"Image");
                    /* try { // try from 00bfa79f to 00bfa7a3 has its CatchHandler @ 00bfab76 */
          CEGUI::PropertySet::setProperty(*(String **)(this + lVar16 * 8 + 0x1050),local_dd8);
                    /* try { // try from 00bfa7a7 to 00bfa7ab has its CatchHandler @ 00bfaba7 */
          CEGUI::String::~String(local_dd8);
                    /* try { // try from 00bfa7af to 00bfa7b3 has its CatchHandler @ 00bfaba9 */
          CEGUI::String::~String((String *)local_d28);
        }
        CEGUI::String::~String(pSVar19);
        goto LAB_00bfa29a;
      }
      pSVar19 = (String *)&local_1148;
      local_1140 = 0x20;
      local_1138 = 0;
      local_1128 = 0;
      local_1130 = 0;
      local_10a0 = (undefined4 *)0x0;
      local_1148 = 0;
      local_1120[0] = 0;
      CEGUI::String::grow((ulong)pSVar19);
      local_1148 = 0;
      puVar15 = local_1120;
      if (0x20 < local_1140) {
        puVar15 = local_10a0;
      }
      *puVar15 = 0;
      local_1090 = 0x20;
      local_1088 = 0;
      local_1078 = 0;
      local_1080 = 0;
      local_ff0 = (uint *)0x0;
      local_1098 = 0;
      local_1070[0] = 0;
                    /* try { // try from 00bfa8f3 to 00bfa8f7 has its CatchHandler @ 00bfabcd */
      CEGUI::String::grow((ulong)&local_1098);
      puVar14 = local_1070;
      if (0x20 < local_1090) {
        puVar14 = local_ff0;
      }
      pbVar13 = (byte *)0xfd0c0d;
      do {
        bVar6 = *pbVar13;
        pbVar13 = pbVar13 + 1;
        *puVar14 = (uint)bVar6;
        puVar14 = puVar14 + 1;
      } while (pbVar13 != (byte *)0xfd0c12);
      local_1098 = 5;
      puVar14 = local_105c;
      if (0x20 < local_1090) {
        puVar14 = local_ff0 + 5;
      }
      *puVar14 = 0;
                    /* try { // try from 00bfa96d to 00bfa971 has its CatchHandler @ 00bfabb2 */
      CEGUI::PropertySet::setProperty
                (*(String **)(this + lVar16 * 8 + 0x1050),(String *)&local_1098);
                    /* try { // try from 00bfa975 to 00bfa979 has its CatchHandler @ 00bfabcd */
      CEGUI::String::~String((String *)&local_1098);
    }
    else {
      pSVar19 = (String *)&local_a68;
      local_a60 = 0x20;
      local_a58 = 0;
      local_a48 = 0;
      local_a50 = 0;
      local_9c0 = (uint *)0x0;
      local_a68 = 0;
      local_a40[0] = 0;
      CEGUI::String::grow((ulong)pSVar19);
      puVar14 = local_a40;
      if (0x20 < local_a60) {
        puVar14 = local_9c0;
      }
      pcVar12 = "goldslotglow";
      do {
        bVar6 = *pcVar12;
        pcVar12 = pcVar12 + 1;
        *puVar14 = (uint)bVar6;
        puVar14 = puVar14 + 1;
      } while ((byte *)pcVar12 != (byte *)0xfe60a7);
      local_a68 = 0xc;
      puVar14 = local_a10;
      if (0x20 < local_a60) {
        puVar14 = local_9c0 + 0xc;
      }
      *puVar14 = 0;
                    /* try { // try from 00bfa195 to 00bfa1ac has its CatchHandler @ 00bfacb5 */
      CEGUI::Imageset::getImage(*(String **)(this + 0x3410));
      CEGUI::PropertyHelper::imageToString(local_b18);
      local_bc0 = 0x20;
      local_bb8 = 0;
      local_ba8 = 0;
      local_bb0 = 0;
      local_b20 = (uint *)0x0;
      local_bc8 = 0;
      local_ba0[0] = 0;
                    /* try { // try from 00bfa210 to 00bfa214 has its CatchHandler @ 00bfacba */
      CEGUI::String::grow((ulong)&local_bc8);
      puVar14 = local_ba0;
      if (0x20 < local_bc0) {
        puVar14 = local_b20;
      }
      pbVar13 = (byte *)0xfd0c0d;
      do {
        bVar6 = *pbVar13;
        pbVar13 = pbVar13 + 1;
        *puVar14 = (uint)bVar6;
        puVar14 = puVar14 + 1;
      } while (pbVar13 != (byte *)0xfd0c12);
      local_bc8 = 5;
      puVar14 = local_b8c;
      if (0x20 < local_bc0) {
        puVar14 = local_b20 + 5;
      }
      *puVar14 = 0;
                    /* try { // try from 00bfa27d to 00bfa281 has its CatchHandler @ 00bfaca0 */
      CEGUI::PropertySet::setProperty(*(String **)(this + lVar16 * 8 + 0x1050),(String *)&local_bc8)
      ;
                    /* try { // try from 00bfa285 to 00bfa289 has its CatchHandler @ 00bfacba */
      CEGUI::String::~String((String *)&local_bc8);
                    /* try { // try from 00bfa28d to 00bfa291 has its CatchHandler @ 00bfacb5 */
      CEGUI::String::~String((String *)local_b18);
    }
  }
  CEGUI::String::~String(pSVar19);
LAB_00bfa29a:
  if (*(long *)(this + lVar16 * 8 + 0x2270) != 0) {
    bVar18 = SUB81(*(long *)(this + lVar16 * 8 + 0x2270),0);
    if (*(int *)(param_1 + 0x238) < 2) {
      CEGUI::Window::setVisible(bVar18);
    }
    else {
      CEGUI::Window::setVisible(bVar18);
      STRINGS::GetValueAsString((STRINGS *)local_58,*(int *)(param_1 + 0x238));
                    /* try { // try from 00bfa2f2 to 00bfa2f6 has its CatchHandler @ 00bfaca2 */
      std::operator+((char *)local_48,(string *)&DAT_0103f7f3);
      if ((allocator *)(local_58[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_58[0] + -8);
        iVar5 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar5 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
        }
      }
                    /* try { // try from 00bfa320 to 00bfa324 has its CatchHandler @ 00bfabfe */
      CEGUI::String::String(local_1618,local_48[0]);
                    /* try { // try from 00bfa335 to 00bfa339 has its CatchHandler @ 00bfac1c */
      CEGUI::Window::setText(*(String **)(this + lVar16 * 8 + 0x2270));
                    /* try { // try from 00bfa33d to 00bfa341 has its CatchHandler @ 00bfabfe */
      CEGUI::String::~String(local_1618);
      if ((allocator *)(local_48[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_48[0] + -8);
        iVar5 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar5 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
        }
      }
    }
  }
  return;
}

/* address=00bfad60
   symbol=CStashMenu::updateLayout */

/* WARNING: Removing unreachable block (ram,0x00bfbd8b) */
/* WARNING: Removing unreachable block (ram,0x00bfbe07) */
/* CStashMenu::updateLayout() */

void __thiscall CStashMenu::updateLayout(CStashMenu *this)

{
  int *piVar1;
  int iVar2;
  byte bVar3;
  Window *pWVar4;
  char cVar5;
  byte *pbVar6;
  uint *puVar7;
  undefined4 *puVar8;
  length_error *this_00;
  long *plVar9;
  uint uVar10;
  long lVar11;
  ulong uVar12;
  long lVar13;
  CEquipment *pCVar14;
  long local_a00;
  undefined8 local_9f8;
  ulong local_9f0;
  undefined8 local_9e8;
  undefined8 local_9e0;
  undefined8 local_9d8;
  undefined4 local_9d0 [32];
  undefined4 *local_950;
  undefined8 local_948;
  ulong local_940;
  undefined8 local_938;
  undefined8 local_930;
  undefined8 local_928;
  undefined4 local_920 [32];
  undefined4 *local_8a0;
  undefined8 local_898;
  ulong local_890;
  undefined8 local_888;
  undefined8 local_880;
  undefined8 local_878;
  uint local_870 [5];
  uint local_85c [27];
  uint *local_7f0;
  undefined8 local_7e8;
  ulong local_7e0;
  undefined8 local_7d8;
  undefined8 local_7d0;
  undefined8 local_7c8;
  undefined4 local_7c0 [32];
  undefined4 *local_740;
  undefined8 local_738;
  ulong local_730;
  undefined8 local_728;
  undefined8 local_720;
  undefined8 local_718;
  uint local_710 [5];
  uint local_6fc [27];
  uint *local_690;
  undefined8 local_688;
  ulong local_680;
  undefined8 local_678;
  undefined8 local_670;
  undefined8 local_668;
  undefined4 local_660 [32];
  undefined4 *local_5e0;
  undefined8 local_5d8;
  ulong local_5d0;
  undefined8 local_5c8;
  undefined8 local_5c0;
  undefined8 local_5b8;
  uint local_5b0 [5];
  uint local_59c [27];
  uint *local_530;
  undefined8 local_528;
  ulong local_520;
  undefined8 local_518;
  undefined8 local_510;
  undefined8 local_508;
  undefined4 local_500 [32];
  undefined4 *local_480;
  undefined8 local_478;
  ulong local_470;
  undefined8 local_468;
  undefined8 local_460;
  undefined8 local_458;
  undefined4 local_450 [32];
  undefined4 *local_3d0;
  undefined8 local_3c8;
  ulong local_3c0;
  undefined8 local_3b8;
  undefined8 local_3b0;
  undefined8 local_3a8;
  uint local_3a0 [5];
  uint local_38c [27];
  uint *local_320;
  undefined8 local_318;
  ulong local_310;
  undefined8 local_308;
  undefined8 local_300;
  undefined8 local_2f8;
  undefined4 local_2f0 [32];
  undefined4 *local_270;
  undefined8 local_268;
  ulong local_260;
  undefined8 local_258;
  undefined8 local_250;
  undefined8 local_248;
  uint local_240 [5];
  uint local_22c [27];
  uint *local_1c0;
  undefined8 local_1b8;
  ulong local_1b0;
  undefined8 local_1a8;
  undefined8 local_1a0;
  undefined8 local_198;
  undefined4 local_190 [32];
  undefined4 *local_110;
  undefined8 local_108;
  ulong local_100;
  undefined8 local_f8;
  undefined8 local_f0;
  undefined8 local_e8;
  uint local_e0 [5];
  uint local_cc [27];
  uint *local_60;
  long local_58 [2];
  long local_48;
  allocator local_3b [2];
  allocator local_39 [9];

  if ((this[0x60] != (CStashMenu)0x0) && (*(CBaseUnit **)(this + 0x50) != (CBaseUnit *)0x0)) {
    cVar5 = CBaseUnit::ISA(*(CBaseUnit **)(this + 0x50),0xaa);
    if (cVar5 == '\0') {
      local_a00 = *(long *)(*(long *)(this + 0x50) + 0x490);
    }
    else {
      lVar11 = CSharedStash::getSingleton();
      local_a00 = *(long *)(lVar11 + 0x10);
    }
    if (local_a00 != 0) {
      while (pWVar4 = *(Window **)(this + 0x30),
            *(long *)(pWVar4 + 0x80) - *(long *)(pWVar4 + 0x78) >> 3 != 0) {
        CEGUI::Window::removeChildWindow(pWVar4);
      }
      lVar11 = 0;
      do {
        pWVar4 = *(Window **)(this + lVar11 + 0x1e80);
        if (*(long *)(pWVar4 + 0x80) - *(long *)(pWVar4 + 0x78) >> 3 != 0) {
          CEGUI::Window::removeChildWindow(pWVar4);
        }
        local_1b0 = 0x20;
        local_1a8 = 0;
        local_198 = 0;
        local_1a0 = 0;
        local_110 = (undefined4 *)0x0;
        local_1b8 = 0;
        local_190[0] = 0;
        CEGUI::String::grow((ulong)&local_1b8);
        local_1b8 = 0;
        puVar8 = local_110;
        if (local_1b0 < 0x21) {
          puVar8 = local_190;
        }
        *puVar8 = 0;
        local_100 = 0x20;
        local_f8 = 0;
        local_e8 = 0;
        local_f0 = 0;
        local_60 = (uint *)0x0;
        local_108 = 0;
        local_e0[0] = 0;
                    /* try { // try from 00bfaf4d to 00bfaf51 has its CatchHandler @ 00bfbd4e */
        CEGUI::String::grow((ulong)&local_108);
        puVar7 = local_e0;
        if (0x20 < local_100) {
          puVar7 = local_60;
        }
        pbVar6 = (byte *)0xfd0c0d;
        do {
          bVar3 = *pbVar6;
          pbVar6 = pbVar6 + 1;
          *puVar7 = (uint)bVar3;
          puVar7 = puVar7 + 1;
        } while (pbVar6 != (byte *)0xfd0c12);
        local_108 = 5;
        puVar7 = local_cc;
        if (0x20 < local_100) {
          puVar7 = local_60 + 5;
        }
        *puVar7 = 0;
                    /* try { // try from 00bfafcd to 00bfafd1 has its CatchHandler @ 00bfbd66 */
        CEGUI::PropertySet::setProperty(*(String **)(this + lVar11 + 0x1570),(String *)&local_108);
                    /* try { // try from 00bfafd5 to 00bfafd9 has its CatchHandler @ 00bfbd4e */
        CEGUI::String::~String((String *)&local_108);
        CEGUI::String::~String((String *)&local_1b8);
        local_310 = 0x20;
        local_308 = 0;
        local_2f8 = 0;
        local_300 = 0;
        local_270 = (undefined4 *)0x0;
        local_318 = 0;
        local_2f0[0] = 0;
        CEGUI::String::grow((ulong)&local_318);
        puVar8 = local_2f0;
        if (0x20 < local_310) {
          puVar8 = local_270;
        }
        local_318 = 0;
        *puVar8 = 0;
        local_260 = 0x20;
        local_258 = 0;
        local_248 = 0;
        local_250 = 0;
        local_1c0 = (uint *)0x0;
        local_268 = 0;
        local_240[0] = 0;
                    /* try { // try from 00bfb0d2 to 00bfb0d6 has its CatchHandler @ 00bfbc68 */
        CEGUI::String::grow((ulong)&local_268);
        pbVar6 = (byte *)0xfd0c0d;
        puVar7 = local_240;
        if (0x20 < local_260) {
          puVar7 = local_1c0;
        }
        do {
          bVar3 = *pbVar6;
          pbVar6 = pbVar6 + 1;
          *puVar7 = (uint)bVar3;
          puVar7 = puVar7 + 1;
        } while (pbVar6 != (byte *)0xfd0c12);
        local_268 = 5;
        if (local_260 < 0x21) {
          puVar7 = local_22c;
        }
        else {
          puVar7 = local_1c0 + 5;
        }
        *puVar7 = 0;
                    /* try { // try from 00bfb14f to 00bfb153 has its CatchHandler @ 00bfbc80 */
        CEGUI::PropertySet::setProperty(*(String **)(this + lVar11 + 0x10e8),(String *)&local_268);
                    /* try { // try from 00bfb15c to 00bfb160 has its CatchHandler @ 00bfbc68 */
        CEGUI::String::~String((String *)&local_268);
        CEGUI::String::~String((String *)&local_318);
        local_470 = 0x20;
        local_468 = 0;
        local_458 = 0;
        local_460 = 0;
        local_3d0 = (undefined4 *)0x0;
        local_478 = 0;
        local_450[0] = 0;
        CEGUI::String::grow((ulong)&local_478);
        puVar8 = local_450;
        if (0x20 < local_470) {
          puVar8 = local_3d0;
        }
        local_478 = 0;
        *puVar8 = 0;
        local_3c0 = 0x20;
        local_3b8 = 0;
        local_3a8 = 0;
        local_3b0 = 0;
        local_320 = (uint *)0x0;
        local_3c8 = 0;
        local_3a0[0] = 0;
                    /* try { // try from 00bfb259 to 00bfb25d has its CatchHandler @ 00bfbc92 */
        CEGUI::String::grow((ulong)&local_3c8);
        pbVar6 = (byte *)0xfd0c0d;
        puVar7 = local_3a0;
        if (0x20 < local_3c0) {
          puVar7 = local_320;
        }
        do {
          bVar3 = *pbVar6;
          pbVar6 = pbVar6 + 1;
          *puVar7 = (uint)bVar3;
          puVar7 = puVar7 + 1;
        } while (pbVar6 != (byte *)0xfd0c12);
        local_3c8 = 5;
        if (local_3c0 < 0x21) {
          puVar7 = local_38c;
        }
        else {
          puVar7 = local_320 + 5;
        }
        *puVar7 = 0;
                    /* try { // try from 00bfb2d7 to 00bfb2db has its CatchHandler @ 00bfbcaa */
        CEGUI::PropertySet::setProperty(*(String **)(this + lVar11 + 0x19f8),(String *)&local_3c8);
                    /* try { // try from 00bfb2e4 to 00bfb2e8 has its CatchHandler @ 00bfbc92 */
        CEGUI::String::~String((String *)&local_3c8);
        CEGUI::String::~String((String *)&local_478);
        if (*(long *)(this + lVar11 + 0x2308) != 0) {
          local_520 = 0x20;
          local_518 = 0;
          local_508 = 0;
          local_510 = 0;
          local_480 = (undefined4 *)0x0;
          local_528 = 0;
          local_500[0] = 0;
          if (CEGUI::String::npos == 0) {
                    /* try { // try from 00bfb4e5 to 00bfb4e9 has its CatchHandler @ 00bfbdea */
            std::string::string((string *)&local_48,
                                "Length for utf8 encoded string can not be \'npos\'",local_39);
            this_00 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00bfb4fd to 00bfb501 has its CatchHandler @ 00bfbdef */
            std::length_error::length_error(this_00,(string *)&local_48);
            if ((allocator *)(local_48 + -0x18) !=
                (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar1 = (int *)(local_48 + -8);
              iVar2 = *piVar1;
              *piVar1 = *piVar1 + -1;
              UNLOCK();
              if (iVar2 < 1) {
                std::string::_Rep::_M_destroy((allocator *)(local_48 + -0x18));
              }
            }
            goto LAB_00bfb51b;
          }
          CEGUI::String::grow((ulong)&local_528);
          local_528 = 0;
          puVar8 = local_500;
          if (0x20 < local_520) {
            puVar8 = local_480;
          }
          *puVar8 = 0;
                    /* try { // try from 00bfb3a2 to 00bfb3a6 has its CatchHandler @ 00bfbdab */
          CEGUI::Window::setText(*(String **)(this + lVar11 + 0x2308));
          CEGUI::String::~String((String *)&local_528);
        }
        lVar11 = lVar11 + 8;
      } while (lVar11 != 0x150);
      if (*(int *)(local_a00 + 0x38) != 0) {
        uVar12 = 0;
        do {
          uVar10 = (uint)uVar12;
          if (uVar10 < *(uint *)(local_a00 + 0x3c)) {
            plVar9 = *(long **)(local_a00 + 0x30);
            lVar11 = plVar9[uVar12];
            pCVar14 = *(CEquipment **)(lVar11 + 0x10);
          }
          else {
            plVar9 = *(long **)(local_a00 + 0x30);
            lVar11 = *plVar9;
            pCVar14 = *(CEquipment **)(lVar11 + 0x10);
          }
          if (0x12 < *(int *)(lVar11 + 0x18)) {
            if (uVar10 < *(uint *)(local_a00 + 0x3c)) {
              plVar9 = (long *)(uVar12 * 8 + *(long *)(local_a00 + 0x30));
            }
            setSlotIcon(this,pCVar14,*(int *)(*plVar9 + 0x18),*(int *)(*plVar9 + 0x18));
          }
          uVar12 = (ulong)(uVar10 + 1);
        } while (uVar10 + 1 < *(uint *)(local_a00 + 0x38));
      }
      lVar11 = 0;
      plVar9 = *(long **)(*(long *)(this + 0x58) + 0x648);
      if (*(long *)(*(long *)(this + 0x58) + 0x650) - (long)plVar9 >> 3 != 0) {
        lVar11 = *plVar9;
      }
      lVar11 = *(long *)(lVar11 + 0x490);
      if (lVar11 != 0) {
        lVar13 = 0;
        do {
          pWVar4 = *(Window **)(this + lVar13 + 0x2790);
          if (*(long *)(pWVar4 + 0x80) - *(long *)(pWVar4 + 0x78) >> 3 != 0) {
            CEGUI::Window::removeChildWindow(pWVar4);
          }
          local_680 = 0x20;
          local_678 = 0;
          local_668 = 0;
          local_670 = 0;
          local_5e0 = (undefined4 *)0x0;
          local_688 = 0;
          local_660[0] = 0;
          CEGUI::String::grow((ulong)&local_688);
          local_688 = 0;
          puVar8 = local_5e0;
          if (local_680 < 0x21) {
            puVar8 = local_660;
          }
          *puVar8 = 0;
          local_5d0 = 0x20;
          local_5c8 = 0;
          local_5b8 = 0;
          local_5c0 = 0;
          local_530 = (uint *)0x0;
          local_5d8 = 0;
          local_5b0[0] = 0;
                    /* try { // try from 00bfb6dd to 00bfb6e1 has its CatchHandler @ 00bfbcc7 */
          CEGUI::String::grow((ulong)&local_5d8);
          puVar7 = local_5b0;
          if (0x20 < local_5d0) {
            puVar7 = local_530;
          }
          pbVar6 = (byte *)0xfd0c0d;
          do {
            bVar3 = *pbVar6;
            pbVar6 = pbVar6 + 1;
            *puVar7 = (uint)bVar3;
            puVar7 = puVar7 + 1;
          } while (pbVar6 != (byte *)0xfd0c12);
          local_5d8 = 5;
          puVar7 = local_59c;
          if (0x20 < local_5d0) {
            puVar7 = local_530 + 5;
          }
          *puVar7 = 0;
                    /* try { // try from 00bfb752 to 00bfb756 has its CatchHandler @ 00bfbcf7 */
          CEGUI::PropertySet::setProperty(*(String **)(this + lVar13 + 0x2cb0),(String *)&local_5d8)
          ;
                    /* try { // try from 00bfb75a to 00bfb75e has its CatchHandler @ 00bfbcc7 */
          CEGUI::String::~String((String *)&local_5d8);
          CEGUI::String::~String((String *)&local_688);
          local_7e0 = 0x20;
          local_7d8 = 0;
          local_7c8 = 0;
          local_7d0 = 0;
          local_740 = (undefined4 *)0x0;
          local_7e8 = 0;
          local_7c0[0] = 0;
          CEGUI::String::grow((ulong)&local_7e8);
          puVar8 = local_7c0;
          if (0x20 < local_7e0) {
            puVar8 = local_740;
          }
          local_7e8 = 0;
          *puVar8 = 0;
          local_730 = 0x20;
          local_728 = 0;
          local_718 = 0;
          local_720 = 0;
          local_690 = (uint *)0x0;
          local_738 = 0;
          local_710[0] = 0;
                    /* try { // try from 00bfb857 to 00bfb85b has its CatchHandler @ 00bfbcdf */
          CEGUI::String::grow((ulong)&local_738);
          pbVar6 = (byte *)0xfd0c0d;
          puVar7 = local_710;
          if (0x20 < local_730) {
            puVar7 = local_690;
          }
          do {
            bVar3 = *pbVar6;
            pbVar6 = pbVar6 + 1;
            *puVar7 = (uint)bVar3;
            puVar7 = puVar7 + 1;
          } while (pbVar6 != (byte *)0xfd0c12);
          local_738 = 5;
          if (local_730 < 0x21) {
            puVar7 = local_6fc;
          }
          else {
            puVar7 = local_690 + 5;
          }
          *puVar7 = 0;
                    /* try { // try from 00bfb8d7 to 00bfb8db has its CatchHandler @ 00bfbd3c */
          CEGUI::PropertySet::setProperty(*(String **)(this + lVar13 + 0x2f40),(String *)&local_738)
          ;
                    /* try { // try from 00bfb8e4 to 00bfb8e8 has its CatchHandler @ 00bfbcdf */
          CEGUI::String::~String((String *)&local_738);
          CEGUI::String::~String((String *)&local_7e8);
          local_940 = 0x20;
          local_938 = 0;
          local_928 = 0;
          local_930 = 0;
          local_8a0 = (undefined4 *)0x0;
          local_948 = 0;
          local_920[0] = 0;
          CEGUI::String::grow((ulong)&local_948);
          puVar8 = local_920;
          if (0x20 < local_940) {
            puVar8 = local_8a0;
          }
          local_948 = 0;
          *puVar8 = 0;
          local_890 = 0x20;
          local_888 = 0;
          local_878 = 0;
          local_880 = 0;
          local_7f0 = (uint *)0x0;
          local_898 = 0;
          local_870[0] = 0;
                    /* try { // try from 00bfb9e1 to 00bfb9e5 has its CatchHandler @ 00bfbd37 */
          CEGUI::String::grow((ulong)&local_898);
          pbVar6 = (byte *)0xfd0c0d;
          puVar7 = local_870;
          if (0x20 < local_890) {
            puVar7 = local_7f0;
          }
          do {
            bVar3 = *pbVar6;
            pbVar6 = pbVar6 + 1;
            *puVar7 = (uint)bVar3;
            puVar7 = puVar7 + 1;
          } while (pbVar6 != (byte *)0xfd0c12);
          local_898 = 5;
          if (local_890 < 0x21) {
            puVar7 = local_85c;
          }
          else {
            puVar7 = local_7f0 + 5;
          }
          *puVar7 = 0;
                    /* try { // try from 00bfba5f to 00bfba63 has its CatchHandler @ 00bfbd12 */
          CEGUI::PropertySet::setProperty(*(String **)(this + lVar13 + 0x2a20),(String *)&local_898)
          ;
                    /* try { // try from 00bfba6c to 00bfba70 has its CatchHandler @ 00bfbd37 */
          CEGUI::String::~String((String *)&local_898);
          CEGUI::String::~String((String *)&local_948);
          if (*(long *)(this + lVar13 + 0x31d0) != 0) {
            local_9f0 = 0x20;
            local_9e8 = 0;
            local_9d8 = 0;
            local_9e0 = 0;
            local_950 = (undefined4 *)0x0;
            local_9f8 = 0;
            local_9d0[0] = 0;
            if (CEGUI::String::npos == 0) {
                    /* try { // try from 00bfbbf7 to 00bfbbfb has its CatchHandler @ 00bfbcbc */
              std::string::string((string *)local_58,
                                  "Length for utf8 encoded string can not be \'npos\'",local_3b);
              this_00 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00bfbc0f to 00bfbc13 has its CatchHandler @ 00bfbd73 */
              std::length_error::length_error(this_00,(string *)local_58);
              if ((allocator *)(local_58[0] + -0x18) !=
                  (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar1 = (int *)(local_58[0] + -8);
                iVar2 = *piVar1;
                *piVar1 = *piVar1 + -1;
                UNLOCK();
                if (iVar2 < 1) {
                  std::string::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
                }
              }
LAB_00bfb51b:
                    /* WARNING: Subroutine does not return */
              __cxa_throw(this_00,&std::length_error::typeinfo,std::length_error::~length_error);
            }
            CEGUI::String::grow((ulong)&local_9f8);
            local_9f8 = 0;
            puVar8 = local_9d0;
            if (0x20 < local_9f0) {
              puVar8 = local_950;
            }
            *puVar8 = 0;
                    /* try { // try from 00bfbb12 to 00bfbb16 has its CatchHandler @ 00bfbd04 */
            CEGUI::Window::setText(*(String **)(this + lVar13 + 0x31d0));
            CEGUI::String::~String((String *)&local_9f8);
          }
          lVar13 = lVar13 + 8;
        } while (lVar13 != 0x1f8);
        if (*(int *)(lVar11 + 0x38) != 0) {
          uVar12 = 0;
          do {
            uVar10 = (uint)uVar12;
            if (uVar10 < *(uint *)(lVar11 + 0x3c)) {
              plVar9 = *(long **)(lVar11 + 0x30);
              lVar13 = plVar9[uVar12];
              pCVar14 = *(CEquipment **)(lVar13 + 0x10);
            }
            else {
              plVar9 = *(long **)(lVar11 + 0x30);
              lVar13 = *plVar9;
              pCVar14 = *(CEquipment **)(lVar13 + 0x10);
            }
            if (0x12 < *(int *)(lVar13 + 0x18)) {
              if (uVar10 < *(uint *)(lVar11 + 0x3c)) {
                plVar9 = (long *)(uVar12 * 8 + *(long *)(lVar11 + 0x30));
              }
              setPetSlotIcon(this,pCVar14,*(int *)(*plVar9 + 0x18),*(int *)(*plVar9 + 0x18));
            }
            uVar12 = (ulong)(uVar10 + 1);
          } while (uVar10 + 1 < *(uint *)(lVar11 + 0x38));
        }
      }
      CEGUI::Window::moveToBack();
      CEGUI::Window::moveToFront();
      CEGUI::Window::moveToFront();
      CEGUI::Window::moveToFront();
      CEGUI::Window::moveToFront();
    }
  }
  return;
}

/* address=00bfbe20
   symbol=CStashMenu::createMenus */

/* WARNING: Removing unreachable block (ram,0x00c03c4f) */
/* WARNING: Removing unreachable block (ram,0x00c03d95) */
/* WARNING: Removing unreachable block (ram,0x00c03385) */
/* WARNING: Removing unreachable block (ram,0x00c02f7c) */
/* WARNING: Removing unreachable block (ram,0x00c02edd) */
/* WARNING: Removing unreachable block (ram,0x00c0331b) */
/* WARNING: Removing unreachable block (ram,0x00c03161) */
/* WARNING: Removing unreachable block (ram,0x00c0362a) */
/* WARNING: Removing unreachable block (ram,0x00c03927) */
/* WARNING: Removing unreachable block (ram,0x00c0361f) */
/* WARNING: Removing unreachable block (ram,0x00c03ace) */
/* WARNING: Removing unreachable block (ram,0x00c03a1b) */
/* WARNING: Removing unreachable block (ram,0x00c03816) */
/* WARNING: Removing unreachable block (ram,0x00c03a10) */
/* WARNING: Removing unreachable block (ram,0x00c03535) */
/* WARNING: Removing unreachable block (ram,0x00c0388a) */
/* WARNING: Removing unreachable block (ram,0x00c0316c) */
/* WARNING: Removing unreachable block (ram,0x00c02ed2) */
/* WARNING: Removing unreachable block (ram,0x00c02ff5) */
/* WARNING: Removing unreachable block (ram,0x00c02d17) */
/* WARNING: Removing unreachable block (ram,0x00c03435) */
/* WARNING: Removing unreachable block (ram,0x00c03ec1) */
/* WARNING: Removing unreachable block (ram,0x00c03d2d) */
/* WARNING: Removing unreachable block (ram,0x00c03f2f) */
/* WARNING: Removing unreachable block (ram,0x00c03df8) */
/* WARNING: Removing unreachable block (ram,0x00c03d3b) */
/* WARNING: Removing unreachable block (ram,0x00c03eac) */
/* WARNING: Removing unreachable block (ram,0x00c03310) */
/* WARNING: Removing unreachable block (ram,0x00c038c1) */
/* WARNING: Removing unreachable block (ram,0x00c0322d) */
/* WARNING: Removing unreachable block (ram,0x00c03289) */
/* WARNING: Removing unreachable block (ram,0x00c03932) */
/* WARNING: Removing unreachable block (ram,0x00c03222) */
/* WARNING: Removing unreachable block (ram,0x00c03bee) */
/* WARNING: Removing unreachable block (ram,0x00c02f87) */
/* WARNING: Removing unreachable block (ram,0x00c02e4a) */
/* WARNING: Removing unreachable block (ram,0x00c02f19) */
/* WARNING: Removing unreachable block (ram,0x00c02e55) */
/* WARNING: Removing unreachable block (ram,0x00c0308d) */
/* CStashMenu::createMenus() */

void __thiscall CStashMenu::createMenus(CStashMenu *this)

{
  int *piVar1;
  char cVar2;
  byte bVar3;
  code *pcVar4;
  BoundSlot *pBVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  undefined8 uVar10;
  long lVar11;
  char *pcVar12;
  char *pcVar13;
  CFileSystem *this_00;
  String *pSVar14;
  byte *pbVar15;
  String *pSVar16;
  undefined8 *puVar17;
  UVector2 *pUVar18;
  undefined4 *puVar19;
  uint *puVar20;
  length_error *plVar21;
  ulong uVar22;
  uint uVar23;
  byte *pbVar24;
  ulong uVar25;
  CStashMenu *pCVar26;
  char *pcVar27;
  char *pcVar28;
  long lVar29;
  bool bVar30;
  float fVar31;
  float fVar32;
  int local_3a84;
  CStashMenu *local_3a70;
  undefined8 local_3a68;
  ulong local_3a60;
  undefined8 local_3a58;
  undefined8 local_3a50;
  undefined8 local_3a48;
  undefined4 local_3a40 [32];
  undefined4 *local_39c0;
  long local_39b8;
  ulong local_39b0;
  undefined8 local_39a8;
  undefined8 local_39a0;
  undefined8 local_3998;
  undefined4 local_3990 [32];
  undefined4 *local_3910;
  long local_3908;
  ulong local_3900;
  undefined8 local_38f8;
  undefined8 local_38f0;
  undefined8 local_38e8;
  uint local_38e0 [32];
  uint *local_3860;
  undefined8 local_3858;
  ulong local_3850;
  undefined8 local_3848;
  undefined8 local_3840;
  undefined8 local_3838;
  undefined4 local_3830 [32];
  undefined4 *local_37b0;
  long local_37a8;
  ulong local_37a0;
  undefined8 local_3798;
  undefined8 local_3790;
  undefined8 local_3788;
  undefined4 local_3780 [32];
  undefined4 *local_3700;
  long local_36f8;
  ulong local_36f0;
  undefined8 local_36e8;
  undefined8 local_36e0;
  undefined8 local_36d8;
  uint local_36d0 [32];
  uint *local_3650;
  undefined8 local_3648;
  ulong local_3640;
  undefined8 local_3638;
  undefined8 local_3630;
  undefined8 local_3628;
  undefined4 local_3620 [32];
  undefined4 *local_35a0;
  long local_3598;
  ulong local_3590;
  undefined8 local_3588;
  undefined8 local_3580;
  undefined8 local_3578;
  undefined4 local_3570 [32];
  undefined4 *local_34f0;
  long local_34e8;
  ulong local_34e0;
  undefined8 local_34d8;
  undefined8 local_34d0;
  undefined8 local_34c8;
  uint local_34c0 [32];
  uint *local_3440;
  undefined8 local_3438;
  ulong local_3430;
  undefined8 local_3428;
  undefined8 local_3420;
  undefined8 local_3418;
  uint local_3410 [10];
  uint local_33e8 [22];
  uint *local_3390;
  String local_3388 [176];
  undefined8 local_32d8;
  ulong local_32d0;
  undefined8 local_32c8;
  undefined8 local_32c0;
  undefined8 local_32b8;
  undefined4 local_32b0 [32];
  undefined4 *local_3230;
  undefined8 local_3228;
  ulong local_3220;
  undefined8 local_3218;
  undefined8 local_3210;
  undefined8 local_3208;
  uint local_3200 [13];
  uint local_31cc [19];
  uint *local_3180;
  undefined8 local_3178;
  ulong local_3170;
  undefined8 local_3168;
  undefined8 local_3160;
  undefined8 local_3158;
  uint local_3150 [14];
  uint local_3118 [18];
  uint *local_30d0;
  undefined8 local_30c8;
  ulong local_30c0;
  undefined8 local_30b8;
  undefined8 local_30b0;
  undefined8 local_30a8;
  uint local_30a0 [12];
  uint local_3070 [20];
  uint *local_3020;
  undefined8 local_3018;
  ulong local_3010;
  undefined8 local_3008;
  undefined8 local_3000;
  undefined8 local_2ff8;
  uint local_2ff0 [18];
  uint local_2fa8 [14];
  uint *local_2f70;
  undefined8 local_2f68;
  ulong local_2f60;
  undefined8 local_2f58;
  undefined8 local_2f50;
  undefined8 local_2f48;
  uint local_2f40 [5];
  uint local_2f2c [27];
  uint *local_2ec0;
  undefined8 local_2eb8;
  ulong local_2eb0;
  undefined8 local_2ea8;
  undefined8 local_2ea0;
  undefined8 local_2e98;
  undefined4 local_2e90 [32];
  undefined4 *local_2e10;
  long local_2e08;
  ulong local_2e00;
  undefined8 local_2df8;
  undefined8 local_2df0;
  undefined8 local_2de8;
  undefined4 local_2de0 [32];
  undefined4 *local_2d60;
  long local_2d58;
  ulong local_2d50;
  undefined8 local_2d48;
  undefined8 local_2d40;
  undefined8 local_2d38;
  uint local_2d30 [32];
  uint *local_2cb0;
  long local_2ca8;
  ulong local_2ca0;
  undefined8 local_2c98;
  undefined8 local_2c90;
  undefined8 local_2c88;
  undefined4 local_2c80 [32];
  undefined4 *local_2c00;
  undefined8 local_2bf8;
  ulong local_2bf0;
  undefined8 local_2be8;
  undefined8 local_2be0;
  undefined8 local_2bd8;
  uint local_2bd0 [12];
  uint local_2ba0 [20];
  uint *local_2b50;
  undefined8 local_2b48;
  ulong local_2b40;
  undefined8 local_2b38;
  undefined8 local_2b30;
  undefined8 local_2b28;
  uint local_2b20 [14];
  uint local_2ae8 [18];
  uint *local_2aa0;
  undefined8 local_2a98;
  ulong local_2a90;
  undefined8 local_2a88;
  undefined8 local_2a80;
  undefined8 local_2a78;
  uint local_2a70 [17];
  uint local_2a2c [15];
  uint *local_29f0;
  undefined8 local_29e8;
  ulong local_29e0;
  undefined8 local_29d8;
  undefined8 local_29d0;
  undefined8 local_29c8;
  uint local_29c0 [7];
  uint local_29a4 [25];
  uint *local_2940;
  undefined8 local_2938;
  ulong local_2930;
  undefined8 local_2928;
  undefined8 local_2920;
  undefined8 local_2918;
  uint local_2910 [8];
  uint local_28f0 [24];
  uint *local_2890;
  undefined8 local_2888;
  ulong local_2880;
  undefined8 local_2878;
  undefined8 local_2870;
  undefined8 local_2868;
  uint local_2860 [11];
  uint local_2834 [21];
  uint *local_27e0;
  undefined8 local_27d8;
  ulong local_27d0;
  undefined8 local_27c8;
  undefined8 local_27c0;
  undefined8 local_27b8;
  undefined4 local_27b0 [32];
  undefined4 *local_2730;
  long local_2728;
  ulong local_2720;
  undefined8 local_2718;
  undefined8 local_2710;
  undefined8 local_2708;
  undefined4 local_2700 [32];
  undefined4 *local_2680;
  long local_2678;
  ulong local_2670;
  undefined8 local_2668;
  undefined8 local_2660;
  undefined8 local_2658;
  uint local_2650 [32];
  uint *local_25d0;
  undefined8 local_25c8;
  ulong local_25c0;
  undefined8 local_25b8;
  undefined8 local_25b0;
  undefined8 local_25a8;
  undefined4 local_25a0 [32];
  undefined4 *local_2520;
  long local_2518;
  ulong local_2510;
  undefined8 local_2508;
  undefined8 local_2500;
  undefined8 local_24f8;
  undefined4 local_24f0 [32];
  undefined4 *local_2470;
  long local_2468;
  ulong local_2460;
  undefined8 local_2458;
  undefined8 local_2450;
  undefined8 local_2448;
  uint local_2440 [32];
  uint *local_23c0;
  undefined8 local_23b8;
  ulong local_23b0;
  undefined8 local_23a8;
  undefined8 local_23a0;
  undefined8 local_2398;
  undefined4 local_2390 [32];
  undefined4 *local_2310;
  long local_2308;
  ulong local_2300;
  undefined8 local_22f8;
  undefined8 local_22f0;
  undefined8 local_22e8;
  undefined4 local_22e0 [32];
  undefined4 *local_2260;
  long local_2258;
  ulong local_2250;
  undefined8 local_2248;
  undefined8 local_2240;
  undefined8 local_2238;
  uint local_2230 [32];
  uint *local_21b0;
  undefined8 local_21a8;
  ulong local_21a0;
  undefined8 local_2198;
  undefined8 local_2190;
  undefined8 local_2188;
  uint local_2180 [10];
  uint local_2158 [22];
  uint *local_2100;
  String local_20f8 [176];
  undefined8 local_2048;
  ulong local_2040;
  undefined8 local_2038;
  undefined8 local_2030;
  undefined8 local_2028;
  undefined4 local_2020 [32];
  undefined4 *local_1fa0;
  undefined8 local_1f98;
  ulong local_1f90;
  undefined8 local_1f88;
  undefined8 local_1f80;
  undefined8 local_1f78;
  uint local_1f70 [10];
  uint local_1f48 [22];
  uint *local_1ef0;
  undefined8 local_1ee8;
  ulong local_1ee0;
  undefined8 local_1ed8;
  undefined8 local_1ed0;
  undefined8 local_1ec8;
  uint local_1ec0 [14];
  uint local_1e88 [18];
  uint *local_1e40;
  undefined8 local_1e38;
  ulong local_1e30;
  undefined8 local_1e28;
  undefined8 local_1e20;
  undefined8 local_1e18;
  uint local_1e10 [12];
  uint local_1de0 [20];
  uint *local_1d90;
  undefined8 local_1d88;
  ulong local_1d80;
  undefined8 local_1d78;
  undefined8 local_1d70;
  undefined8 local_1d68;
  uint local_1d60 [18];
  uint local_1d18 [14];
  uint *local_1ce0;
  undefined8 local_1cd8;
  ulong local_1cd0;
  undefined8 local_1cc8;
  undefined8 local_1cc0;
  undefined8 local_1cb8;
  uint local_1cb0 [5];
  uint local_1c9c [27];
  uint *local_1c30;
  undefined8 local_1c28;
  ulong local_1c20;
  undefined8 local_1c18;
  undefined8 local_1c10;
  undefined8 local_1c08;
  undefined4 local_1c00 [32];
  undefined4 *local_1b80;
  long local_1b78;
  ulong local_1b70;
  undefined8 local_1b68;
  undefined8 local_1b60;
  undefined8 local_1b58;
  undefined4 local_1b50 [32];
  undefined4 *local_1ad0;
  long local_1ac8;
  ulong local_1ac0;
  undefined8 local_1ab8;
  undefined8 local_1ab0;
  undefined8 local_1aa8;
  uint local_1aa0 [32];
  uint *local_1a20;
  long local_1a18;
  ulong local_1a10;
  undefined8 local_1a08;
  undefined8 local_1a00;
  undefined8 local_19f8;
  undefined4 local_19f0 [32];
  undefined4 *local_1970;
  undefined8 local_1968;
  ulong local_1960;
  undefined8 local_1958;
  undefined8 local_1950;
  undefined8 local_1948;
  uint local_1940 [5];
  uint local_192c [27];
  uint *local_18c0;
  undefined8 local_18b8;
  ulong local_18b0;
  undefined8 local_18a8;
  undefined8 local_18a0;
  undefined8 local_1898;
  uint local_1890 [8];
  uint local_1870 [24];
  uint *local_1810;
  undefined8 local_1808;
  ulong local_1800;
  undefined8 local_17f8;
  undefined8 local_17f0;
  undefined8 local_17e8;
  uint local_17e0 [5];
  uint local_17cc [27];
  uint *local_1760;
  undefined8 local_1758;
  ulong local_1750;
  undefined8 local_1748;
  undefined8 local_1740;
  undefined8 local_1738;
  uint local_1730 [11];
  uint local_1704 [21];
  uint *local_16b0;
  undefined8 local_16a8;
  ulong local_16a0;
  undefined8 local_1698;
  undefined8 local_1690;
  undefined8 local_1688;
  undefined4 local_1680 [32];
  undefined4 *local_1600;
  String local_15f8 [176];
  long local_1548;
  ulong local_1540;
  undefined8 local_1538;
  undefined8 local_1530;
  undefined8 local_1528;
  uint local_1520 [32];
  uint *local_14a0;
  undefined8 local_1498;
  ulong local_1490;
  undefined8 local_1488;
  undefined8 local_1480;
  undefined8 local_1478;
  uint local_1470 [5];
  uint local_145c [27];
  uint *local_13f0;
  undefined8 local_13e8;
  ulong local_13e0;
  undefined8 local_13d8;
  undefined8 local_13d0;
  undefined8 local_13c8;
  uint local_13c0 [11];
  uint local_1394 [21];
  uint *local_1340;
  undefined8 local_1338;
  ulong local_1330;
  undefined8 local_1328;
  undefined8 local_1320;
  undefined8 local_1318;
  undefined4 local_1310 [32];
  undefined4 *local_1290;
  String local_1288 [176];
  String local_11d8 [176];
  undefined8 local_1128;
  ulong local_1120;
  undefined8 local_1118;
  undefined8 local_1110;
  undefined8 local_1108;
  uint local_1100 [5];
  uint local_10ec [27];
  uint *local_1080;
  undefined8 local_1078;
  ulong local_1070;
  undefined8 local_1068;
  undefined8 local_1060;
  undefined8 local_1058;
  uint local_1050 [11];
  uint local_1024 [21];
  uint *local_fd0;
  undefined8 local_fc8;
  ulong local_fc0;
  undefined8 local_fb8;
  undefined8 local_fb0;
  undefined8 local_fa8;
  uint local_fa0 [8];
  uint local_f80 [24];
  uint *local_f20;
  undefined8 local_f18;
  ulong local_f10;
  undefined8 local_f08;
  undefined8 local_f00;
  undefined8 local_ef8;
  uint local_ef0 [5];
  uint local_edc [27];
  uint *local_e70;
  undefined8 local_e68;
  ulong local_e60;
  undefined8 local_e58;
  undefined8 local_e50;
  undefined8 local_e48;
  uint local_e40 [11];
  uint local_e14 [21];
  uint *local_dc0;
  undefined8 local_db8;
  ulong local_db0;
  undefined8 local_da8;
  undefined8 local_da0;
  undefined8 local_d98;
  uint local_d90 [11];
  uint local_d64 [21];
  uint *local_d10;
  undefined8 local_d08;
  ulong local_d00;
  undefined8 local_cf8;
  undefined8 local_cf0;
  undefined8 local_ce8;
  uint local_ce0 [5];
  uint local_ccc [27];
  uint *local_c60;
  undefined8 local_c58;
  ulong local_c50;
  undefined8 local_c48;
  undefined8 local_c40;
  undefined8 local_c38;
  uint local_c30 [11];
  uint local_c04 [21];
  uint *local_bb0;
  undefined8 local_ba8;
  ulong local_ba0;
  undefined8 local_b98;
  undefined8 local_b90;
  undefined8 local_b88;
  uint local_b80 [7];
  uint local_b64 [25];
  uint *local_b00;
  long local_af8;
  ulong local_af0;
  undefined8 local_ae8;
  undefined8 local_ae0;
  undefined8 local_ad8;
  undefined4 local_ad0 [32];
  undefined4 *local_a50;
  undefined8 local_a48;
  ulong local_a40;
  undefined8 local_a38;
  undefined8 local_a30;
  undefined8 local_a28;
  uint local_a20 [5];
  uint local_a0c [27];
  uint *local_9a0;
  undefined8 local_998;
  ulong local_990;
  undefined8 local_988;
  undefined8 local_980;
  undefined8 local_978;
  uint local_970 [11];
  uint local_944 [21];
  uint *local_8f0;
  undefined8 local_8e8;
  ulong local_8e0;
  undefined8 local_8d8;
  undefined8 local_8d0;
  undefined8 local_8c8;
  undefined4 local_8c0 [32];
  undefined4 *local_840;
  long local_838;
  ulong local_830;
  undefined8 local_828;
  undefined8 local_820;
  undefined8 local_818;
  uint local_810 [32];
  uint *local_790;
  String local_788 [176];
  long local_6d8;
  ulong local_6d0;
  undefined8 local_6c8;
  undefined8 local_6c0;
  undefined8 local_6b8;
  uint local_6b0 [32];
  uint *local_630;
  long local_628;
  ulong local_620;
  undefined8 local_618;
  undefined8 local_610;
  undefined8 local_608;
  uint local_600 [32];
  uint *local_580;
  undefined1 *local_578;
  long local_570;
  long local_568;
  undefined4 local_560;
  undefined4 local_55c;
  undefined1 *local_558;
  undefined1 local_550;
  undefined4 local_548;
  undefined4 local_544;
  undefined4 local_540;
  undefined4 local_53c;
  undefined4 local_538;
  undefined4 local_534;
  undefined4 local_530;
  void *local_528;
  undefined1 local_518 [32];
  undefined1 local_4f8 [80];
  undefined8 local_4a8;
  undefined8 local_4a0;
  BoundSlot *local_488;
  int *local_480;
  BoundSlot *local_478;
  int *local_470;
  BoundSlot *local_468;
  int *local_460;
  BoundSlot *local_458;
  int *local_450;
  BoundSlot *local_408;
  int *local_400;
  BoundSlot *local_3f8;
  int *local_3f0;
  BoundSlot *local_3e8;
  int *local_3e0;
  BoundSlot *local_3d8;
  int *local_3d0;
  BoundSlot *local_3c8;
  int *local_3c0;
  undefined4 local_3b8;
  undefined4 local_3b4;
  undefined4 local_3b0;
  undefined4 local_3ac;
  undefined4 local_398;
  undefined4 local_394;
  undefined4 local_390;
  undefined4 local_38c;
  BoundSlot *local_378;
  int *local_370;
  undefined4 local_368;
  undefined4 local_364;
  undefined4 local_360;
  undefined4 local_35c;
  undefined4 local_358;
  undefined4 local_354;
  undefined4 local_350;
  undefined4 local_34c;
  long local_348 [2];
  long local_338 [2];
  long local_328 [2];
  long local_318 [2];
  long local_308 [2];
  long local_2f8 [2];
  long local_2e8 [2];
  long local_2d8 [2];
  long local_2c8 [2];
  long local_2b8 [2];
  long local_2a8 [2];
  long local_298 [2];
  long local_288 [2];
  long local_278 [2];
  long local_268 [2];
  long local_258 [2];
  long local_248 [2];
  long local_238 [2];
  long local_228 [2];
  long local_218 [2];
  long local_208 [2];
  long local_1f8 [2];
  undefined8 *local_1e8 [2];
  undefined8 *local_1d8 [2];
  undefined8 *local_1c8 [2];
  undefined8 *local_1b8 [2];
  long local_1a8 [2];
  long local_198 [2];
  long local_188 [2];
  long local_178 [2];
  long local_168 [2];
  long local_158 [2];
  long local_148 [2];
  long local_138 [2];
  long local_128 [2];
  long local_118 [2];
  undefined8 *local_108 [2];
  undefined8 *local_f8 [2];
  undefined8 *local_e8 [2];
  undefined8 *local_d8 [2];
  long local_c8 [2];
  long local_b8 [2];
  undefined8 *local_a8 [2];
  long local_98 [2];
  undefined8 *local_88 [3];
  allocator local_6f [4];
  allocator local_6b [4];
  allocator local_67 [2];
  allocator local_65 [4];
  allocator local_61 [6];
  allocator local_5b [4];
  allocator local_57 [4];
  allocator local_53 [2];
  allocator local_51 [4];
  allocator local_4d [4];
  allocator local_49 [3];
  allocator local_46 [2];
  allocator local_44 [2];
  allocator local_42;
  allocator local_41;
  allocator local_40;
  allocator local_3f;
  allocator local_3e;
  allocator local_3d;
  allocator local_3c;
  allocator local_3b;
  allocator local_3a;
  allocator local_39 [9];

  iVar6 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0x68),KSETTINGS_RES_WIDTH);
  iVar7 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0x68),KSETTINGS_RES_HEIGHT)
  ;
  uVar10 = CResourceManager::createGenericModel
                     (*(CResourceManager **)(this + 0x98),*(SceneManager **)(this + 0x78),
                      L"media/ui/models/merchant/merchant.mesh",L"",false,false,false);
  *(undefined8 *)(this + 0x90) = uVar10;
  local_528 = (void *)0x0;
  local_530 = 1;
  local_548 = 0xc7c35000;
  local_544 = 0xc7c35000;
  local_540 = 0xc7c35000;
  local_53c = 0x47c35000;
  local_538 = 0x47c35000;
  local_534 = 0x47c35000;
                    /* try { // try from 00bfbef1 to 00bfc07a has its CatchHandler @ 00c03549 */
  lVar11 = Ogre::Entity::getMesh();
  Ogre::Mesh::_setBounds(*(AxisAlignedBox **)(lVar11 + 8),SUB81(&local_548,0));
  fVar31 = (float)iVar7 / DAT_00fc6774;
  pcVar4 = *(code **)(**(long **)(this + 0x90) + 0x58);
  fVar32 = (float)CDynamicPropertyFile::GetFloat
                            (*(CDynamicPropertyFile **)(this + 0x68),KSETTINGS_YRATIO);
  (*pcVar4)(DAT_00fa86f4 * (((float)iVar6 - fVar31) / fVar32),0,*(undefined8 *)(this + 0x90));
  (**(code **)(**(long **)(this + 0x90) + 0x50))(*(long **)(this + 0x90),0);
  pcVar27 = (char *)0x0;
  pcVar13 = "GuiLook";
  local_620 = 0x20;
  local_618 = 0;
  pcVar28 = "GuiLook";
  local_608 = 0;
  local_610 = 0;
  local_580 = (uint *)0x0;
  local_628 = 0;
  local_600[0] = 0;
  cVar2 = s_GuiLook_00fe493c[0];
  while (pcVar28 = pcVar28 + 1, cVar2 != '\0') {
    pcVar27 = pcVar28 + -0xfe493c;
    cVar2 = *pcVar28;
  }
  if (pcVar27 == CEGUI::String::npos) {
                    /* try { // try from 00c00f37 to 00c00f3b has its CatchHandler @ 00c03e62 */
    std::string::string((string *)local_278,"Length for utf8 encoded string can not be \'npos\'",
                        &local_42);
    plVar21 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00c00f4f to 00c00f53 has its CatchHandler @ 00c03e94 */
    std::length_error::length_error(plVar21,(string *)local_278);
    if ((allocator *)(local_278[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_278[0] + -8);
      iVar6 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar6 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_278[0] + -0x18));
      }
    }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00c00f7a to 00c00f7e has its CatchHandler @ 00c03549 */
    __cxa_throw(plVar21,&std::length_error::typeinfo,std::length_error::~length_error);
  }
  lVar11 = 0;
  pcVar28 = pcVar27;
  pbVar15 = (byte *)"GuiLook";
  while (pcVar28 != (char *)0x0) {
    bVar3 = *pbVar15;
    pcVar12 = pcVar28 + -1;
    pbVar24 = pbVar15 + 1;
    if ((char)bVar3 < '\0') {
      if (bVar3 < 0xe0) {
        pcVar12 = pcVar28 + -2;
        pbVar24 = pbVar15 + 2;
      }
      else if (bVar3 < 0xf0) {
        pcVar12 = pcVar28 + -3;
        pbVar24 = pbVar15 + 3;
      }
      else {
        pcVar12 = pcVar28 + -3;
        pbVar24 = pbVar15 + 4;
      }
    }
    lVar11 = lVar11 + 1;
    pcVar28 = pcVar12;
    pbVar15 = pbVar24;
  }
  CEGUI::String::grow((ulong)&local_628);
  if (local_620 < 0x21) {
    puVar20 = local_600;
    if (pcVar27 != (char *)0x0) goto LAB_00bfc09a;
LAB_00bfc22d:
    if (s_GuiLook_00fe493c[0] != '\0') {
      do {
        pcVar13 = pcVar13 + 1;
        pcVar27 = pcVar13 + -0xfe493c;
      } while (*pcVar13 != '\0');
      bVar30 = pcVar27 != (char *)0x0 && local_620 != 0;
      goto LAB_00bfc0a0;
    }
  }
  else {
    puVar20 = local_580;
    if (pcVar27 == (char *)0x0) goto LAB_00bfc22d;
LAB_00bfc09a:
    bVar30 = local_620 != 0;
LAB_00bfc0a0:
    if (bVar30) {
      pcVar13 = (char *)0x0;
      uVar9 = 0;
      uVar22 = local_620;
      do {
        bVar3 = pcVar13[0xfe493c];
        uVar23 = (uint)bVar3;
        uVar8 = uVar9 + 1;
        if ((char)bVar3 < '\0') {
          uVar23 = (uint)bVar3;
          if (0xdf < bVar3) {
            if (bVar3 < 0xf0) {
              uVar25 = (ulong)uVar8;
              uVar8 = uVar9 + 3;
              uVar23 = (byte)"GuiLook"[uVar9 + 2] & 0x3f | (uVar23 & 0xf) << 0xc |
                       ((byte)"GuiLook"[uVar25] & 0x3f) << 6;
            }
            else {
              uVar25 = (ulong)uVar8;
              uVar8 = uVar9 + 4;
              uVar23 = ((byte)"GuiLook"[uVar25] & 0x3f) << 0xc | (byte)"GuiLook"[uVar9 + 3] & 0x3f |
                       (uVar23 & 7) << 0x12 | ((byte)"GuiLook"[uVar9 + 2] & 0x3f) << 6;
            }
            goto LAB_00bfc0b3;
          }
          uVar9 = uVar9 + 2;
          *puVar20 = (byte)"GuiLook"[uVar8] & 0x3f | (uVar23 & 0x1f) << 6;
        }
        else {
LAB_00bfc0b3:
          *puVar20 = uVar23;
          uVar9 = uVar8;
        }
        pcVar13 = (char *)(ulong)uVar9;
        if ((pcVar27 <= pcVar13) || (uVar22 = uVar22 - 1, uVar22 == 0)) break;
        puVar20 = puVar20 + 1;
      } while( true );
    }
  }
  puVar20 = local_600;
  if (0x20 < local_620) {
    puVar20 = local_580;
  }
  puVar20[lVar11] = 0;
  local_628 = lVar11;
                    /* try { // try from 00bfc141 to 00bfc145 has its CatchHandler @ 00c0358e */
  CEGUI::ImagesetManager::getImageset(CEGUI::Singleton<CEGUI::ImagesetManager>::ms_Singleton);
                    /* try { // try from 00bfc149 to 00bfc2f2 has its CatchHandler @ 00c03549 */
  CEGUI::String::~String((String *)&local_628);
  pcVar28 = (char *)0x0;
  pcVar27 = "UIIcons";
  local_6d0 = 0x20;
  local_6c8 = 0;
  pcVar13 = "UIIcons";
  local_6b8 = 0;
  local_6c0 = 0;
  local_630 = (uint *)0x0;
  local_6d8 = 0;
  local_6b0[0] = 0;
  cVar2 = s_UIIcons_00fe49dd[0];
  while (pcVar13 = pcVar13 + 1, cVar2 != '\0') {
    pcVar28 = pcVar13 + -0xfe49dd;
    cVar2 = *pcVar13;
  }
  if (pcVar28 == CEGUI::String::npos) {
                    /* try { // try from 00c00ff7 to 00c00ffb has its CatchHandler @ 00c03e15 */
    std::string::string((string *)local_288,"Length for utf8 encoded string can not be \'npos\'",
                        local_44);
    plVar21 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00c0100f to 00c01013 has its CatchHandler @ 00c03de0 */
    std::length_error::length_error(plVar21,(string *)local_288);
    if ((allocator *)(local_288[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_288[0] + -8);
      iVar6 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar6 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_288[0] + -0x18));
      }
    }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00c0103a to 00c0103e has its CatchHandler @ 00c03549 */
    __cxa_throw(plVar21,&std::length_error::typeinfo,std::length_error::~length_error);
  }
  lVar11 = 0;
  pcVar13 = pcVar28;
  pbVar15 = (byte *)"UIIcons";
  while (pcVar13 != (char *)0x0) {
    bVar3 = *pbVar15;
    pcVar12 = pcVar13 + -1;
    pbVar24 = pbVar15 + 1;
    if ((char)bVar3 < '\0') {
      if (bVar3 < 0xe0) {
        pcVar12 = pcVar13 + -2;
        pbVar24 = pbVar15 + 2;
      }
      else if (bVar3 < 0xf0) {
        pcVar12 = pcVar13 + -3;
        pbVar24 = pbVar15 + 3;
      }
      else {
        pcVar12 = pcVar13 + -3;
        pbVar24 = pbVar15 + 4;
      }
    }
    lVar11 = lVar11 + 1;
    pcVar13 = pcVar12;
    pbVar15 = pbVar24;
  }
  CEGUI::String::grow((ulong)&local_6d8);
  puVar20 = local_6b0;
  if (0x20 < local_6d0) {
    puVar20 = local_630;
  }
  if (pcVar28 == (char *)0x0) {
    if (s_UIIcons_00fe49dd[0] != '\0') {
      do {
        pcVar27 = pcVar27 + 1;
        pcVar28 = pcVar27 + -0xfe49dd;
      } while (*pcVar27 != '\0');
      bVar30 = pcVar28 != (char *)0x0 && local_6d0 != 0;
      goto LAB_00bfc31c;
    }
  }
  else {
    bVar30 = local_6d0 != 0;
LAB_00bfc31c:
    if (bVar30) {
      pcVar13 = (char *)0x0;
      uVar9 = 0;
      uVar22 = local_6d0;
      do {
        bVar3 = pcVar13[0xfe49dd];
        uVar23 = (uint)bVar3;
        uVar8 = uVar9 + 1;
        if ((char)bVar3 < '\0') {
          uVar23 = (uint)bVar3;
          if (0xdf < bVar3) {
            if (bVar3 < 0xf0) {
              uVar25 = (ulong)uVar8;
              uVar8 = uVar9 + 3;
              uVar23 = (byte)"UIIcons"[uVar9 + 2] & 0x3f | (uVar23 & 0xf) << 0xc |
                       ((byte)"UIIcons"[uVar25] & 0x3f) << 6;
            }
            else {
              uVar25 = (ulong)uVar8;
              uVar8 = uVar9 + 4;
              uVar23 = ((byte)"UIIcons"[uVar25] & 0x3f) << 0xc | (byte)"UIIcons"[uVar9 + 3] & 0x3f |
                       (uVar23 & 7) << 0x12 | ((byte)"UIIcons"[uVar9 + 2] & 0x3f) << 6;
            }
            goto LAB_00bfc333;
          }
          uVar9 = uVar9 + 2;
          *puVar20 = (byte)"UIIcons"[uVar8] & 0x3f | (uVar23 & 0x1f) << 6;
        }
        else {
LAB_00bfc333:
          *puVar20 = uVar23;
          uVar9 = uVar8;
        }
        pcVar13 = (char *)(ulong)uVar9;
        if ((pcVar28 <= pcVar13) || (uVar22 = uVar22 - 1, uVar22 == 0)) break;
        puVar20 = puVar20 + 1;
      } while( true );
    }
  }
  puVar20 = local_6b0;
  if (0x20 < local_6d0) {
    puVar20 = local_630;
  }
  puVar20[lVar11] = 0;
  local_6d8 = lVar11;
                    /* try { // try from 00bfc3c1 to 00bfc3c5 has its CatchHandler @ 00c03895 */
  uVar10 = CEGUI::ImagesetManager::getImageset
                     (CEGUI::Singleton<CEGUI::ImagesetManager>::ms_Singleton);
  *(undefined8 *)(this + 0x3410) = uVar10;
                    /* try { // try from 00bfc3d0 to 00bfc439 has its CatchHandler @ 00c03549 */
  CEGUI::String::~String((String *)&local_6d8);
  local_8e0 = 0x20;
  local_8d8 = 0;
  local_8c8 = 0;
  local_8d0 = 0;
  local_840 = (undefined4 *)0x0;
  local_8e8 = 0;
  local_8c0[0] = 0;
  CEGUI::String::grow((ulong)&local_8e8);
  local_8e8 = 0;
  puVar19 = local_8c0;
  if (0x20 < local_8e0) {
    puVar19 = local_840;
  }
  *puVar19 = 0;
  pcVar28 = (char *)0x0;
  local_830 = 0x20;
  local_828 = 0;
  local_818 = 0;
  local_820 = 0;
  local_790 = (uint *)0x0;
  local_838 = 0;
  local_810[0] = 0;
  pcVar13 = "tashSheet";
  cVar2 = s_XBStashSheet_00ff15ae[2];
  while (cVar2 != '\0') {
    pcVar28 = pcVar13 + -0xff15b0;
    cVar2 = *pcVar13;
    pcVar13 = pcVar13 + 1;
  }
  if (pcVar28 == CEGUI::String::npos) {
                    /* try { // try from 00c010b7 to 00c010bb has its CatchHandler @ 00c03d46 */
    std::string::string((string *)local_298,"Length for utf8 encoded string can not be \'npos\'",
                        local_46);
    plVar21 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00c010cf to 00c010d3 has its CatchHandler @ 00c03cf1 */
    std::length_error::length_error(plVar21,(string *)local_298);
    if ((allocator *)(local_298[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_298[0] + -8);
      iVar6 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar6 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_298[0] + -0x18));
      }
    }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00c010fa to 00c010fe has its CatchHandler @ 00c03942 */
    __cxa_throw(plVar21,&std::length_error::typeinfo,std::length_error::~length_error);
  }
  lVar11 = 0;
  pcVar13 = pcVar28;
  pbVar15 = (byte *)0xff15b0;
  while (pcVar13 != (char *)0x0) {
    bVar3 = *pbVar15;
    pcVar27 = pcVar13 + -1;
    pbVar24 = pbVar15 + 1;
    if ((char)bVar3 < '\0') {
      if (bVar3 < 0xe0) {
        pcVar27 = pcVar13 + -2;
        pbVar24 = pbVar15 + 2;
      }
      else if (bVar3 < 0xf0) {
        pcVar27 = pcVar13 + -3;
        pbVar24 = pbVar15 + 3;
      }
      else {
        pcVar27 = pcVar13 + -3;
        pbVar24 = pbVar15 + 4;
      }
    }
    lVar11 = lVar11 + 1;
    pcVar13 = pcVar27;
    pbVar15 = pbVar24;
  }
                    /* try { // try from 00bfc59e to 00bfc5a2 has its CatchHandler @ 00c03942 */
  CEGUI::String::grow((ulong)&local_838);
  puVar20 = local_810;
  if (0x20 < local_830) {
    puVar20 = local_790;
  }
  if (pcVar28 == (char *)0x0) {
    pcVar13 = "tashSheet";
    if (s_XBStashSheet_00ff15ae[2] != '\0') {
      do {
        cVar2 = *pcVar13;
        pcVar28 = pcVar13 + -0xff15b0;
        pcVar13 = pcVar13 + 1;
      } while (cVar2 != '\0');
      bVar30 = pcVar28 != (char *)0x0 && local_830 != 0;
      goto LAB_00bfc5cc;
    }
  }
  else {
    bVar30 = local_830 != 0;
LAB_00bfc5cc:
    if (bVar30) {
      pcVar13 = (char *)0x0;
      uVar9 = 0;
      uVar22 = local_830;
      do {
        bVar3 = pcVar13[0xff15b0];
        uVar23 = (uint)bVar3;
        uVar8 = uVar9 + 1;
        if ((char)bVar3 < '\0') {
          uVar23 = (uint)bVar3;
          if (0xdf < bVar3) {
            if (bVar3 < 0xf0) {
              uVar25 = (ulong)uVar8;
              uVar8 = uVar9 + 3;
              uVar23 = (byte)"XBStashSheet"[(ulong)(uVar9 + 2) + 2] & 0x3f | (uVar23 & 0xf) << 0xc |
                       ((byte)"XBStashSheet"[uVar25 + 2] & 0x3f) << 6;
            }
            else {
              uVar25 = (ulong)uVar8;
              uVar8 = uVar9 + 4;
              uVar23 = ((byte)"XBStashSheet"[uVar25 + 2] & 0x3f) << 0xc |
                       (byte)"XBStashSheet"[(ulong)(uVar9 + 3) + 2] & 0x3f | (uVar23 & 7) << 0x12 |
                       ((byte)"XBStashSheet"[(ulong)(uVar9 + 2) + 2] & 0x3f) << 6;
            }
            goto LAB_00bfc5e3;
          }
          uVar9 = uVar9 + 2;
          *puVar20 = (byte)"XBStashSheet"[(ulong)uVar8 + 2] & 0x3f | (uVar23 & 0x1f) << 6;
        }
        else {
LAB_00bfc5e3:
          *puVar20 = uVar23;
          uVar9 = uVar8;
        }
        pcVar13 = (char *)(ulong)uVar9;
        if ((pcVar28 <= pcVar13) || (uVar22 = uVar22 - 1, uVar22 == 0)) break;
        puVar20 = puVar20 + 1;
      } while( true );
    }
  }
  puVar20 = local_810;
  if (0x20 < local_830) {
    puVar20 = local_790;
  }
  puVar20[lVar11] = 0;
  local_838 = lVar11;
                    /* try { // try from 00bfc677 to 00bfc67b has its CatchHandler @ 00c0394a */
  CEGUI::String::String(local_788,(uchar *)"DefaultWindow");
                    /* try { // try from 00bfc68c to 00bfc690 has its CatchHandler @ 00c0370a */
  uVar10 = CEGUI::WindowManager::createWindow
                     (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,local_788,
                      (String *)&local_838);
  *(undefined8 *)(this + 0x20) = uVar10;
                    /* try { // try from 00bfc698 to 00bfc69c has its CatchHandler @ 00c0394a */
  CEGUI::String::~String(local_788);
                    /* try { // try from 00bfc6a0 to 00bfc6a4 has its CatchHandler @ 00c03942 */
  CEGUI::String::~String((String *)&local_838);
                    /* try { // try from 00bfc6a8 to 00bfc6ac has its CatchHandler @ 00c03549 */
  CEGUI::String::~String((String *)&local_8e8);
  local_354 = 0;
  local_358 = 0x3f800000;
  local_34c = 0;
  local_350 = 0x3f800000;
                    /* try { // try from 00bfc6e5 to 00bfc6e9 has its CatchHandler @ 00c0372a */
  CEGUI::Window::setSize(*(UVector2 **)(this + 0x20));
  local_a40 = 0x20;
  local_a38 = 0;
  local_a28 = 0;
  local_a30 = 0;
  local_9a0 = (uint *)0x0;
  local_a48 = 0;
  local_a20[0] = 0;
                    /* try { // try from 00bfc74d to 00bfc751 has its CatchHandler @ 00c03549 */
  CEGUI::String::grow((ulong)&local_a48);
  puVar20 = local_a20;
  if (0x20 < local_a40) {
    puVar20 = local_9a0;
  }
  pcVar13 = "False";
  do {
    bVar3 = *pcVar13;
    pcVar13 = pcVar13 + 1;
    *puVar20 = (uint)bVar3;
    puVar20 = puVar20 + 1;
  } while ((byte *)pcVar13 != (byte *)0xfe603f);
  local_a48 = 5;
  puVar20 = local_a0c;
  if (0x20 < local_a40) {
    puVar20 = local_9a0 + 5;
  }
  *puVar20 = 0;
  local_990 = 0x20;
  local_988 = 0;
  local_978 = 0;
  local_980 = 0;
  local_8f0 = (uint *)0x0;
  local_998 = 0;
  local_970[0] = 0;
                    /* try { // try from 00bfc815 to 00bfc819 has its CatchHandler @ 00c0372f */
  CEGUI::String::grow((ulong)&local_998);
  puVar20 = local_970;
  if (0x20 < local_990) {
    puVar20 = local_8f0;
  }
  pcVar13 = "RiseOnClick";
  do {
    bVar3 = *pcVar13;
    pcVar13 = pcVar13 + 1;
    *puVar20 = (uint)bVar3;
    puVar20 = puVar20 + 1;
  } while ((byte *)pcVar13 != (byte *)0xfe6039);
  local_998 = 0xb;
  puVar20 = local_944;
  if (0x20 < local_990) {
    puVar20 = local_8f0 + 0xb;
  }
  *puVar20 = 0;
                    /* try { // try from 00bfc88d to 00bfc891 has its CatchHandler @ 00c0373f */
  CEGUI::PropertySet::setProperty(*(String **)(this + 0x20),(String *)&local_998);
                    /* try { // try from 00bfc895 to 00bfc899 has its CatchHandler @ 00c0372f */
  CEGUI::String::~String((String *)&local_998);
                    /* try { // try from 00bfc89d to 00bfc8a1 has its CatchHandler @ 00c03549 */
  CEGUI::String::~String((String *)&local_a48);
  local_364 = 0;
  local_368 = 0;
  local_35c = 0;
  local_360 = 0;
                    /* try { // try from 00bfc8da to 00bfc8de has its CatchHandler @ 00c0374c */
  CEGUI::Window::setPosition(*(UVector2 **)(this + 0x20));
  *(undefined1 *)(*(long *)(this + 0x20) + 0x3e2) = 1;
                    /* try { // try from 00bfc8f0 to 00bfc90a has its CatchHandler @ 00c03549 */
  CEGUI::Window::setZOrderingEnabled(SUB81(*(undefined8 *)(this + 0x20),0));
  pcVar4 = *(code **)(*(long *)(*(long *)(this + 0x20) + 0x38) + 0x10);
  local_88[0] = operator_new(0x20);
  *local_88[0] = &PTR__MemberFunctionSlot_00ff17b0;
  local_88[0][2] = 0;
  local_88[0][1] = handle_MouseThrough;
  local_88[0][3] = this;
                    /* try { // try from 00bfc94e to 00bfc983 has its CatchHandler @ 00c03751 */
  (*pcVar4)(&local_378,*(long *)(this + 0x20) + 0x38,CEGUI::Window::EventMouseMove);
  if ((local_378 != (BoundSlot *)0x0) &&
     (iVar6 = *local_370, *local_370 = iVar6 + -1, iVar6 + -1 == 0)) {
    if (local_378 != (BoundSlot *)0x0) {
      CEGUI::BoundSlot::~BoundSlot(local_378);
      operator_delete(local_378);
    }
    operator_delete(local_370);
    local_378 = (BoundSlot *)0x0;
    local_370 = (int *)0x0;
  }
                    /* try { // try from 00bfc9b4 to 00bfc9b8 has its CatchHandler @ 00c03549 */
  CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_88);
  local_578 = &DAT_01423a38;
                    /* try { // try from 00bfc9d6 to 00bfc9da has its CatchHandler @ 00c03761 */
  std::string::string((string *)&local_570,(string *)&::EMPTY_STRING);
                    /* try { // try from 00bfc9ec to 00bfc9f0 has its CatchHandler @ 00c03776 */
  std::wstring::wstring((wstring_conflict *)&local_568,(wstring_conflict *)&::EMPTY_WSTRING);
  local_560 = 4;
  local_55c = 3;
  local_558 = &DAT_01423a38;
  local_550 = 0;
                    /* try { // try from 00bfca33 to 00bfca37 has its CatchHandler @ 00c0389a */
  std::wstring::wstring((wstring_conflict *)local_98,L"media/ui/stashmenu.layout",local_39);
                    /* try { // try from 00bfca38 to 00bfca5a has its CatchHandler @ 00c037d0 */
  this_00 = (CFileSystem *)CFileSystem::getSingleton();
  CFileSystem::getFileInfo
            (this_00,(wstring_conflict *)local_98,(CFileInfo *)&local_578,false,true,false);
  if ((allocator *)(local_98[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_98[0] + -8);
    iVar6 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar6 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
    }
  }
  local_af0 = 0x20;
  local_ae8 = 0;
  local_ad8 = 0;
  local_ae0 = 0;
  local_a50 = (undefined4 *)0x0;
  local_af8 = 0;
  local_ad0[0] = 0;
  lVar11 = *(long *)(local_570 + -0x18);
                    /* try { // try from 00bfcae1 to 00bfcae5 has its CatchHandler @ 00c0380c */
  CEGUI::String::grow((ulong)&local_af8);
  puVar19 = local_ad0;
  if (0x20 < local_af0) {
    puVar19 = local_a50;
  }
  puVar19[lVar11] = 0;
  if (lVar11 != 0) {
    lVar29 = lVar11;
    do {
      lVar29 = lVar29 + -1;
      puVar19 = local_ad0;
      if (0x20 < local_af0) {
        puVar19 = local_a50;
      }
      puVar19[lVar29] = (uint)*(byte *)(local_570 + lVar29);
    } while (lVar29 != 0);
  }
  local_af8 = lVar11;
                    /* try { // try from 00bfcb5e to 00bfcb62 has its CatchHandler @ 00c03811 */
  pSVar14 = (String *)
            CEGUI::WindowManager::loadWindowLayout
                      (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,
                       SUB81((String *)&local_af8,0));
                    /* try { // try from 00bfcb69 to 00bfcbfa has its CatchHandler @ 00c0380c */
  CEGUI::String::~String((String *)&local_af8);
  CGameUI::convertToScreenScale(*(CGameUI **)(this + 0x70),(Window *)pSVar14,false);
  CGameUI::mapToFunctions(*(CGameUI **)(this + 0x70),(Window *)pSVar14);
  mapEventHandlers(this,(Window *)pSVar14);
  local_ba0 = 0x20;
  local_b98 = 0;
  local_b88 = 0;
  local_b90 = 0;
  local_b00 = (uint *)0x0;
  local_ba8 = 0;
  local_b80[0] = 0;
  CEGUI::String::grow((ulong)&local_ba8);
  puVar20 = local_b80;
  if (0x20 < local_ba0) {
    puVar20 = local_b00;
  }
  pbVar15 = (byte *)0xfe4a28;
  do {
    bVar3 = *pbVar15;
    pbVar15 = pbVar15 + 1;
    *puVar20 = (uint)bVar3;
    puVar20 = puVar20 + 1;
  } while (pbVar15 != (byte *)0xfe4a2f);
  local_ba8 = 7;
  puVar20 = local_b64;
  if (0x20 < local_ba0) {
    puVar20 = local_b00 + 7;
  }
  *puVar20 = 0;
                    /* try { // try from 00bfcc68 to 00bfcc6c has its CatchHandler @ 00c03822 */
  pSVar16 = (String *)CEGUI::Window::recursiveChildSearch(pSVar14);
                    /* try { // try from 00bfcc73 to 00bfccfb has its CatchHandler @ 00c0380c */
  CEGUI::String::~String((String *)&local_ba8);
  CEGUI::Window::removeChildWindow(*(Window **)(pSVar16 + 0xb0));
  CEGUI::Window::addChildWindow(*(Window **)(this + 0x20));
  local_d00 = 0x20;
  local_cf8 = 0;
  local_ce8 = 0;
  local_cf0 = 0;
  local_c60 = (uint *)0x0;
  local_d08 = 0;
  local_ce0[0] = 0;
  CEGUI::String::grow((ulong)&local_d08);
  puVar20 = local_ce0;
  if (0x20 < local_d00) {
    puVar20 = local_c60;
  }
  pcVar13 = "False";
  do {
    bVar3 = *pcVar13;
    pcVar13 = pcVar13 + 1;
    *puVar20 = (uint)bVar3;
    puVar20 = puVar20 + 1;
  } while ((byte *)pcVar13 != (byte *)0xfe603f);
  local_d08 = 5;
  puVar20 = local_ccc;
  if (0x20 < local_d00) {
    puVar20 = local_c60 + 5;
  }
  *puVar20 = 0;
  local_c50 = 0x20;
  local_c48 = 0;
  local_c38 = 0;
  local_c40 = 0;
  local_bb0 = (uint *)0x0;
  local_c58 = 0;
  local_c30[0] = 0;
                    /* try { // try from 00bfcdc5 to 00bfcdc9 has its CatchHandler @ 00c03827 */
  CEGUI::String::grow((ulong)&local_c58);
  puVar20 = local_c30;
  if (0x20 < local_c50) {
    puVar20 = local_bb0;
  }
  pcVar13 = "RiseOnClick";
  do {
    bVar3 = *pcVar13;
    pcVar13 = pcVar13 + 1;
    *puVar20 = (uint)bVar3;
    puVar20 = puVar20 + 1;
  } while ((byte *)pcVar13 != (byte *)0xfe6039);
  local_c58 = 0xb;
  puVar20 = local_c04;
  if (0x20 < local_c50) {
    puVar20 = local_bb0 + 0xb;
  }
  *puVar20 = 0;
                    /* try { // try from 00bfce38 to 00bfce3c has its CatchHandler @ 00c03837 */
  CEGUI::PropertySet::setProperty(pSVar16,(String *)&local_c58);
                    /* try { // try from 00bfce40 to 00bfce44 has its CatchHandler @ 00c03827 */
  CEGUI::String::~String((String *)&local_c58);
                    /* try { // try from 00bfce48 to 00bfcec6 has its CatchHandler @ 00c0380c */
  CEGUI::String::~String((String *)&local_d08);
  CEGUI::Window::moveToBack();
  CEGUI::Window::setZOrderingEnabled(SUB81(pSVar16,0));
  local_db0 = 0x20;
  local_da8 = 0;
  local_d98 = 0;
  local_da0 = 0;
  local_d10 = (uint *)0x0;
  local_db8 = 0;
  local_d90[0] = 0;
  CEGUI::String::grow((ulong)&local_db8);
  puVar20 = local_d90;
  if (0x20 < local_db0) {
    puVar20 = local_d10;
  }
  pcVar13 = "BottomFrame";
  do {
    bVar3 = *pcVar13;
    pcVar13 = pcVar13 + 1;
    *puVar20 = (uint)bVar3;
    puVar20 = puVar20 + 1;
  } while ((byte *)pcVar13 != (byte *)0xfef825);
  local_db8 = 0xb;
  puVar20 = local_d64;
  if (0x20 < local_db0) {
    puVar20 = local_d10 + 0xb;
  }
  *puVar20 = 0;
                    /* try { // try from 00bfcf31 to 00bfcf35 has its CatchHandler @ 00c03844 */
  uVar10 = CEGUI::Window::recursiveChildSearch(pSVar14);
  *(undefined8 *)(this + 0x40) = uVar10;
                    /* try { // try from 00bfcf3d to 00bfcfc6 has its CatchHandler @ 00c0380c */
  CEGUI::String::~String((String *)&local_db8);
  CEGUI::Window::removeChildWindow(*(Window **)(*(long *)(this + 0x40) + 0xb0));
  CEGUI::Window::addChildWindow(*(Window **)(this + 0x20));
  local_f10 = 0x20;
  local_f08 = 0;
  local_ef8 = 0;
  local_f00 = 0;
  local_e70 = (uint *)0x0;
  local_f18 = 0;
  local_ef0[0] = 0;
  CEGUI::String::grow((ulong)&local_f18);
  puVar20 = local_ef0;
  if (0x20 < local_f10) {
    puVar20 = local_e70;
  }
  pcVar13 = "False";
  do {
    bVar3 = *pcVar13;
    pcVar13 = pcVar13 + 1;
    *puVar20 = (uint)bVar3;
    puVar20 = puVar20 + 1;
  } while ((byte *)pcVar13 != (byte *)0xfe603f);
  local_f18 = 5;
  puVar20 = local_edc;
  if (0x20 < local_f10) {
    puVar20 = local_e70 + 5;
  }
  *puVar20 = 0;
  local_e60 = 0x20;
  local_e58 = 0;
  local_e48 = 0;
  local_e50 = 0;
  local_dc0 = (uint *)0x0;
  local_e68 = 0;
  local_e40[0] = 0;
                    /* try { // try from 00bfd08d to 00bfd091 has its CatchHandler @ 00c036a3 */
  CEGUI::String::grow((ulong)&local_e68);
  puVar20 = local_e40;
  if (0x20 < local_e60) {
    puVar20 = local_dc0;
  }
  pcVar13 = "RiseOnClick";
  do {
    bVar3 = *pcVar13;
    pcVar13 = pcVar13 + 1;
    *puVar20 = (uint)bVar3;
    puVar20 = puVar20 + 1;
  } while ((byte *)pcVar13 != (byte *)0xfe6039);
  local_e68 = 0xb;
  puVar20 = local_e14;
  if (0x20 < local_e60) {
    puVar20 = local_dc0 + 0xb;
  }
  *puVar20 = 0;
                    /* try { // try from 00bfd0fa to 00bfd0fe has its CatchHandler @ 00c036a8 */
  CEGUI::PropertySet::setProperty(*(String **)(this + 0x40),(String *)&local_e68);
                    /* try { // try from 00bfd102 to 00bfd106 has its CatchHandler @ 00c036a3 */
  CEGUI::String::~String((String *)&local_e68);
                    /* try { // try from 00bfd10a to 00bfd18a has its CatchHandler @ 00c0380c */
  CEGUI::String::~String((String *)&local_f18);
  CEGUI::Window::moveToFront();
  CEGUI::Window::setZOrderingEnabled(SUB81(*(undefined8 *)(this + 0x40),0));
  local_fc0 = 0x20;
  local_fb8 = 0;
  local_fa8 = 0;
  local_fb0 = 0;
  local_f20 = (uint *)0x0;
  local_fc8 = 0;
  local_fa0[0] = 0;
  CEGUI::String::grow((ulong)&local_fc8);
  puVar20 = local_fa0;
  if (0x20 < local_fc0) {
    puVar20 = local_f20;
  }
  pcVar13 = "TopFrame";
  do {
    bVar3 = *pcVar13;
    pcVar13 = pcVar13 + 1;
    *puVar20 = (uint)bVar3;
    puVar20 = puVar20 + 1;
  } while ((byte *)pcVar13 != (byte *)0xfef819);
  local_fc8 = 8;
  puVar20 = local_f80;
  if (0x20 < local_fc0) {
    puVar20 = local_f20 + 8;
  }
  *puVar20 = 0;
                    /* try { // try from 00bfd1f9 to 00bfd1fd has its CatchHandler @ 00c036b5 */
  uVar10 = CEGUI::Window::recursiveChildSearch(pSVar14);
  *(undefined8 *)(this + 0x28) = uVar10;
                    /* try { // try from 00bfd205 to 00bfd28e has its CatchHandler @ 00c0380c */
  CEGUI::String::~String((String *)&local_fc8);
  CEGUI::Window::removeChildWindow(*(Window **)(*(long *)(this + 0x28) + 0xb0));
  CEGUI::Window::addChildWindow(*(Window **)(this + 0x20));
  local_1120 = 0x20;
  local_1118 = 0;
  local_1108 = 0;
  local_1110 = 0;
  local_1080 = (uint *)0x0;
  local_1128 = 0;
  local_1100[0] = 0;
  CEGUI::String::grow((ulong)&local_1128);
  puVar20 = local_1100;
  if (0x20 < local_1120) {
    puVar20 = local_1080;
  }
  pcVar13 = "False";
  do {
    bVar3 = *pcVar13;
    pcVar13 = pcVar13 + 1;
    *puVar20 = (uint)bVar3;
    puVar20 = puVar20 + 1;
  } while ((byte *)pcVar13 != (byte *)0xfe603f);
  local_1128 = 5;
  puVar20 = local_10ec;
  if (0x20 < local_1120) {
    puVar20 = local_1080 + 5;
  }
  *puVar20 = 0;
  local_1070 = 0x20;
  local_1068 = 0;
  local_1058 = 0;
  local_1060 = 0;
  local_fd0 = (uint *)0x0;
  local_1078 = 0;
  local_1050[0] = 0;
                    /* try { // try from 00bfd355 to 00bfd359 has its CatchHandler @ 00c036c5 */
  CEGUI::String::grow((ulong)&local_1078);
  puVar20 = local_1050;
  if (0x20 < local_1070) {
    puVar20 = local_fd0;
  }
  pcVar13 = "RiseOnClick";
  do {
    bVar3 = *pcVar13;
    pcVar13 = pcVar13 + 1;
    *puVar20 = (uint)bVar3;
    puVar20 = puVar20 + 1;
  } while ((byte *)pcVar13 != (byte *)0xfe6039);
  local_1078 = 0xb;
  puVar20 = local_1024;
  if (0x20 < local_1070) {
    puVar20 = local_fd0 + 0xb;
  }
  *puVar20 = 0;
                    /* try { // try from 00bfd3ca to 00bfd3ce has its CatchHandler @ 00c036d5 */
  CEGUI::PropertySet::setProperty(*(String **)(this + 0x28),(String *)&local_1078);
                    /* try { // try from 00bfd3d2 to 00bfd3d6 has its CatchHandler @ 00c036c5 */
  CEGUI::String::~String((String *)&local_1078);
                    /* try { // try from 00bfd3da to 00bfd457 has its CatchHandler @ 00c0380c */
  CEGUI::String::~String((String *)&local_1128);
  CEGUI::Window::moveToFront();
  CEGUI::Window::setZOrderingEnabled(SUB81(*(undefined8 *)(this + 0x28),0));
  local_1330 = 0x20;
  local_1328 = 0;
  local_1318 = 0;
  local_1320 = 0;
  local_1290 = (undefined4 *)0x0;
  local_1338 = 0;
  local_1310[0] = 0;
  CEGUI::String::grow((ulong)&local_1338);
  local_1338 = 0;
  puVar19 = local_1310;
  if (0x20 < local_1330) {
    puVar19 = local_1290;
  }
  *puVar19 = 0;
                    /* try { // try from 00bfd492 to 00bfd496 has its CatchHandler @ 00c036e5 */
  CEGUI::String::String(local_1288,(uchar *)"SSockets");
                    /* try { // try from 00bfd4a7 to 00bfd4ab has its CatchHandler @ 00c036f5 */
  CEGUI::String::String(local_11d8,(uchar *)"DefaultWindow");
                    /* try { // try from 00bfd4bc to 00bfd4c0 has its CatchHandler @ 00c03b5a */
  uVar10 = CEGUI::WindowManager::createWindow
                     (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,local_11d8,local_1288);
  *(undefined8 *)(this + 0x30) = uVar10;
                    /* try { // try from 00bfd4c8 to 00bfd4cc has its CatchHandler @ 00c036f5 */
  CEGUI::String::~String(local_11d8);
                    /* try { // try from 00bfd4d0 to 00bfd4d4 has its CatchHandler @ 00c036e5 */
  CEGUI::String::~String(local_1288);
                    /* try { // try from 00bfd4d8 to 00bfd4fd has its CatchHandler @ 00c0380c */
  CEGUI::String::~String((String *)&local_1338);
  CEGUI::Window::addChildWindow(*(Window **)(this + 0x28));
  CEGUI::Window::getSize();
                    /* try { // try from 00bfd505 to 00bfd509 has its CatchHandler @ 00c03b6a */
  CEGUI::Window::setSize(*(UVector2 **)(this + 0x30));
  local_1490 = 0x20;
  local_1488 = 0;
  local_1478 = 0;
  local_1480 = 0;
  local_13f0 = (uint *)0x0;
  local_1498 = 0;
  local_1470[0] = 0;
                    /* try { // try from 00bfd56d to 00bfd571 has its CatchHandler @ 00c0380c */
  CEGUI::String::grow((ulong)&local_1498);
  puVar20 = local_1470;
  if (0x20 < local_1490) {
    puVar20 = local_13f0;
  }
  pcVar13 = "False";
  do {
    bVar3 = *pcVar13;
    pcVar13 = pcVar13 + 1;
    *puVar20 = (uint)bVar3;
    puVar20 = puVar20 + 1;
  } while ((byte *)pcVar13 != (byte *)0xfe603f);
  local_1498 = 5;
  puVar20 = local_145c;
  if (0x20 < local_1490) {
    puVar20 = local_13f0 + 5;
  }
  *puVar20 = 0;
  local_13e0 = 0x20;
  local_13d8 = 0;
  local_13c8 = 0;
  local_13d0 = 0;
  local_1340 = (uint *)0x0;
  local_13e8 = 0;
  local_13c0[0] = 0;
                    /* try { // try from 00bfd635 to 00bfd639 has its CatchHandler @ 00c03b6f */
  CEGUI::String::grow((ulong)&local_13e8);
  puVar20 = local_13c0;
  if (0x20 < local_13e0) {
    puVar20 = local_1340;
  }
  pcVar13 = "RiseOnClick";
  do {
    bVar3 = *pcVar13;
    pcVar13 = pcVar13 + 1;
    *puVar20 = (uint)bVar3;
    puVar20 = puVar20 + 1;
  } while ((byte *)pcVar13 != (byte *)0xfe6039);
  local_13e8 = 0xb;
  puVar20 = local_1394;
  if (0x20 < local_13e0) {
    puVar20 = local_1340 + 0xb;
  }
  *puVar20 = 0;
                    /* try { // try from 00bfd6aa to 00bfd6ae has its CatchHandler @ 00c03b75 */
  CEGUI::PropertySet::setProperty(*(String **)(this + 0x30),(String *)&local_13e8);
                    /* try { // try from 00bfd6b2 to 00bfd6b6 has its CatchHandler @ 00c03b6f */
  CEGUI::String::~String((String *)&local_13e8);
                    /* try { // try from 00bfd6ba to 00bfd6be has its CatchHandler @ 00c0380c */
  CEGUI::String::~String((String *)&local_1498);
  local_394 = 0;
  local_398 = 0;
  local_38c = 0;
  local_390 = 0;
                    /* try { // try from 00bfd6f7 to 00bfd6fb has its CatchHandler @ 00c03b85 */
  CEGUI::Window::setPosition(*(UVector2 **)(this + 0x30));
  *(undefined1 *)(*(long *)(this + 0x30) + 0x3e2) = 1;
                    /* try { // try from 00bfd70b to 00bfd771 has its CatchHandler @ 00c0380c */
  CEGUI::Window::moveToFront();
  local_16a0 = 0x20;
  local_1698 = 0;
  local_1688 = 0;
  local_1690 = 0;
  local_1600 = (undefined4 *)0x0;
  local_16a8 = 0;
  local_1680[0] = 0;
  CEGUI::String::grow((ulong)&local_16a8);
  local_16a8 = 0;
  puVar19 = local_1600;
  if (local_16a0 < 0x21) {
    puVar19 = local_1680;
  }
  *puVar19 = 0;
                    /* try { // try from 00bfd7ac to 00bfd7b0 has its CatchHandler @ 00c03b95 */
  CEGUI::String::String(local_15f8,(uchar *)"SSocketsO");
  pcVar28 = (char *)0x0;
  pcVar27 = "DefaultWindow";
  local_1540 = 0x20;
  local_1538 = 0;
  pcVar13 = "DefaultWindow";
  local_1528 = 0;
  local_1530 = 0;
  local_14a0 = (uint *)0x0;
  local_1548 = 0;
  local_1520[0] = 0;
  cVar2 = s_DefaultWindow_00fe499d[0];
  while (pcVar13 = pcVar13 + 1, cVar2 != '\0') {
    pcVar28 = pcVar13 + -0xfe499d;
    cVar2 = *pcVar13;
  }
  if (pcVar28 == CEGUI::String::npos) {
                    /* try { // try from 00c01177 to 00c0117b has its CatchHandler @ 00c03c6c */
    std::string::string((string *)local_2a8,"Length for utf8 encoded string can not be \'npos\'",
                        local_49);
    plVar21 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00c0118f to 00c01193 has its CatchHandler @ 00c03c37 */
    std::length_error::length_error(plVar21,(string *)local_2a8);
    if ((allocator *)(local_2a8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_2a8[0] + -8);
      iVar6 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar6 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_2a8[0] + -0x18));
      }
    }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00c011ba to 00c011be has its CatchHandler @ 00c0395d */
    __cxa_throw(plVar21,&std::length_error::typeinfo,std::length_error::~length_error);
  }
  lVar11 = 0;
  pcVar13 = pcVar28;
  pbVar15 = (byte *)"DefaultWindow";
  while (pcVar13 != (char *)0x0) {
    bVar3 = *pbVar15;
    pcVar12 = pcVar13 + -1;
    pbVar24 = pbVar15 + 1;
    if ((char)bVar3 < '\0') {
      if (bVar3 < 0xe0) {
        pcVar12 = pcVar13 + -2;
        pbVar24 = pbVar15 + 2;
      }
      else if (bVar3 < 0xf0) {
        pcVar12 = pcVar13 + -3;
        pbVar24 = pbVar15 + 3;
      }
      else {
        pcVar12 = pcVar13 + -3;
        pbVar24 = pbVar15 + 4;
      }
    }
    lVar11 = lVar11 + 1;
    pcVar13 = pcVar12;
    pbVar15 = pbVar24;
  }
                    /* try { // try from 00bfd93e to 00bfd942 has its CatchHandler @ 00c0395d */
  CEGUI::String::grow((ulong)&local_1548);
  puVar20 = local_1520;
  if (0x20 < local_1540) {
    puVar20 = local_14a0;
  }
  if (pcVar28 == (char *)0x0) {
    if (s_DefaultWindow_00fe499d[0] == '\0') goto LAB_00bfd9e0;
    do {
      pcVar27 = pcVar27 + 1;
      pcVar28 = pcVar27 + -0xfe499d;
    } while (*pcVar27 != '\0');
    bVar30 = pcVar28 != (char *)0x0 && local_1540 != 0;
  }
  else {
    bVar30 = local_1540 != 0;
  }
  if (bVar30) {
    pcVar13 = (char *)0x0;
    uVar9 = 0;
    uVar22 = local_1540;
    do {
      bVar3 = pcVar13[0xfe499d];
      uVar23 = (uint)bVar3;
      uVar8 = uVar9 + 1;
      if ((char)bVar3 < '\0') {
        uVar23 = (uint)bVar3;
        if (0xdf < bVar3) {
          if (bVar3 < 0xf0) {
            uVar25 = (ulong)uVar8;
            uVar8 = uVar9 + 3;
            uVar23 = (byte)"DefaultWindow"[uVar9 + 2] & 0x3f | (uVar23 & 0xf) << 0xc |
                     ((byte)"DefaultWindow"[uVar25] & 0x3f) << 6;
          }
          else {
            uVar25 = (ulong)uVar8;
            uVar8 = uVar9 + 4;
            uVar23 = ((byte)"DefaultWindow"[uVar25] & 0x3f) << 0xc |
                     (byte)"DefaultWindow"[uVar9 + 3] & 0x3f | (uVar23 & 7) << 0x12 |
                     ((byte)"DefaultWindow"[uVar9 + 2] & 0x3f) << 6;
          }
          goto LAB_00bfd983;
        }
        uVar9 = uVar9 + 2;
        *puVar20 = (byte)"DefaultWindow"[uVar8] & 0x3f | (uVar23 & 0x1f) << 6;
      }
      else {
LAB_00bfd983:
        *puVar20 = uVar23;
        uVar9 = uVar8;
      }
      pcVar13 = (char *)(ulong)uVar9;
      if ((pcVar28 <= pcVar13) || (uVar22 = uVar22 - 1, uVar22 == 0)) break;
      puVar20 = puVar20 + 1;
    } while( true );
  }
LAB_00bfd9e0:
  puVar20 = local_1520;
  if (0x20 < local_1540) {
    puVar20 = local_14a0;
  }
  puVar20[lVar11] = 0;
  local_1548 = lVar11;
                    /* try { // try from 00bfda21 to 00bfda25 has its CatchHandler @ 00c03ae1 */
  uVar10 = CEGUI::WindowManager::createWindow
                     (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,(String *)&local_1548,
                      local_15f8);
  *(undefined8 *)(this + 0x38) = uVar10;
                    /* try { // try from 00bfda2d to 00bfda31 has its CatchHandler @ 00c0395d */
  CEGUI::String::~String((String *)&local_1548);
                    /* try { // try from 00bfda3a to 00bfda3e has its CatchHandler @ 00c03b95 */
  CEGUI::String::~String(local_15f8);
                    /* try { // try from 00bfda47 to 00bfda6c has its CatchHandler @ 00c0380c */
  CEGUI::String::~String((String *)&local_16a8);
  CEGUI::Window::addChildWindow(*(Window **)(this + 0x28));
  CEGUI::Window::getSize();
                    /* try { // try from 00bfda74 to 00bfda78 has its CatchHandler @ 00c03af1 */
  CEGUI::Window::setSize(*(UVector2 **)(this + 0x38));
  local_1800 = 0x20;
  local_17f8 = 0;
  local_17e8 = 0;
  local_17f0 = 0;
  local_1760 = (uint *)0x0;
  local_1808 = 0;
  local_17e0[0] = 0;
                    /* try { // try from 00bfdadc to 00bfdae0 has its CatchHandler @ 00c0380c */
  CEGUI::String::grow((ulong)&local_1808);
  puVar20 = local_17e0;
  if (0x20 < local_1800) {
    puVar20 = local_1760;
  }
  pcVar13 = "False";
  do {
    bVar3 = *pcVar13;
    pcVar13 = pcVar13 + 1;
    *puVar20 = (uint)bVar3;
    puVar20 = puVar20 + 1;
  } while ((byte *)pcVar13 != (byte *)0xfe603f);
  local_1808 = 5;
  puVar20 = local_17cc;
  if (0x20 < local_1800) {
    puVar20 = local_1760 + 5;
  }
  *puVar20 = 0;
  local_1750 = 0x20;
  local_1748 = 0;
  local_1738 = 0;
  local_1740 = 0;
  local_16b0 = (uint *)0x0;
  local_1758 = 0;
  local_1730[0] = 0;
                    /* try { // try from 00bfdba5 to 00bfdba9 has its CatchHandler @ 00c03af6 */
  CEGUI::String::grow((ulong)&local_1758);
  puVar20 = local_1730;
  if (0x20 < local_1750) {
    puVar20 = local_16b0;
  }
  pcVar13 = "RiseOnClick";
  do {
    bVar3 = *pcVar13;
    pcVar13 = pcVar13 + 1;
    *puVar20 = (uint)bVar3;
    puVar20 = puVar20 + 1;
  } while ((byte *)pcVar13 != (byte *)0xfe6039);
  local_1758 = 0xb;
  puVar20 = local_1704;
  if (0x20 < local_1750) {
    puVar20 = local_16b0 + 0xb;
  }
  *puVar20 = 0;
                    /* try { // try from 00bfdc1a to 00bfdc1e has its CatchHandler @ 00c03b05 */
  CEGUI::PropertySet::setProperty(*(String **)(this + 0x38),(String *)&local_1758);
                    /* try { // try from 00bfdc22 to 00bfdc26 has its CatchHandler @ 00c03af6 */
  CEGUI::String::~String((String *)&local_1758);
                    /* try { // try from 00bfdc2a to 00bfdc2e has its CatchHandler @ 00c0380c */
  CEGUI::String::~String((String *)&local_1808);
  local_3b4 = 0;
  local_3b8 = 0;
  local_3ac = 0;
  local_3b0 = 0;
                    /* try { // try from 00bfdc67 to 00bfdc6b has its CatchHandler @ 00c03b15 */
  CEGUI::Window::setPosition(*(UVector2 **)(this + 0x38));
  *(undefined1 *)(*(long *)(this + 0x38) + 0x3e2) = 1;
                    /* try { // try from 00bfdc7b to 00bfdce7 has its CatchHandler @ 00c0380c */
  CEGUI::Window::moveToFront();
  local_18b0 = 0x20;
  local_18a8 = 0;
  local_1898 = 0;
  local_18a0 = 0;
  local_1810 = (uint *)0x0;
  local_18b8 = 0;
  local_1890[0] = 0;
  CEGUI::String::grow((ulong)&local_18b8);
  puVar20 = local_1890;
  if (0x20 < local_18b0) {
    puVar20 = local_1810;
  }
  pcVar13 = "SlotGlow";
  do {
    bVar3 = *pcVar13;
    pcVar13 = pcVar13 + 1;
    *puVar20 = (uint)bVar3;
    puVar20 = puVar20 + 1;
  } while ((byte *)pcVar13 != (byte *)0xfef810);
  local_18b8 = 8;
  puVar20 = local_1870;
  if (0x20 < local_18b0) {
    puVar20 = local_1810 + 8;
  }
  *puVar20 = 0;
                    /* try { // try from 00bfdd51 to 00bfdd55 has its CatchHandler @ 00c03b25 */
  uVar10 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x28));
  *(undefined8 *)(this + 0x3418) = uVar10;
                    /* try { // try from 00bfdd60 to 00bfde10 has its CatchHandler @ 00c0380c */
  CEGUI::String::~String((String *)&local_18b8);
  CEGUI::EventSet::setMutedState((bool)((char)*(undefined8 *)(this + 0x3418) + '8'));
  *(undefined1 *)(*(long *)(this + 0x3418) + 0x3e2) = 1;
  *(undefined1 *)(*(long *)(this + 0x3418) + 0x213) = 0;
  CEGUI::Window::removeChildWindow(*(Window **)(*(long *)(this + 0x3418) + 0xb0));
  local_1960 = 0x20;
  local_1958 = 0;
  local_1948 = 0;
  local_1950 = 0;
  local_18c0 = (uint *)0x0;
  local_1968 = 0;
  local_1940[0] = 0;
  CEGUI::String::grow((ulong)&local_1968);
  puVar20 = local_1940;
  if (0x20 < local_1960) {
    puVar20 = local_18c0;
  }
  pcVar13 = "Close";
  do {
    bVar3 = *pcVar13;
    pcVar13 = pcVar13 + 1;
    *puVar20 = (uint)bVar3;
    puVar20 = puVar20 + 1;
  } while ((byte *)pcVar13 != (byte *)0xfef807);
  local_1968 = 5;
  puVar20 = local_192c;
  if (0x20 < local_1960) {
    puVar20 = local_18c0 + 5;
  }
  *puVar20 = 0;
                    /* try { // try from 00bfde7a to 00bfde7e has its CatchHandler @ 00c03b35 */
  lVar11 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x28));
                    /* try { // try from 00bfde85 to 00bfdeaa has its CatchHandler @ 00c0380c */
  CEGUI::String::~String((String *)&local_1968);
  *(undefined1 *)(lVar11 + 0x213) = 0;
  CEGUI::Window::moveToFront();
  pcVar4 = *(code **)(*(long *)(lVar11 + 0x38) + 0x10);
  local_a8[0] = operator_new(0x20);
  *local_a8[0] = &PTR__MemberFunctionSlot_00ff17b0;
  local_a8[0][2] = 0;
  local_a8[0][1] = handle_CloseButton;
  local_a8[0][3] = this;
                    /* try { // try from 00bfdeea to 00bfdf1f has its CatchHandler @ 00c03b45 */
  (*pcVar4)(&local_3c8,lVar11 + 0x38,CEGUI::Window::EventMouseButtonDown,(SubscriberSlot *)local_a8)
  ;
  if ((local_3c8 != (BoundSlot *)0x0) &&
     (iVar6 = *local_3c0, *local_3c0 = iVar6 + -1, iVar6 + -1 == 0)) {
    if (local_3c8 != (BoundSlot *)0x0) {
      CEGUI::BoundSlot::~BoundSlot(local_3c8);
      operator_delete(local_3c8);
    }
    operator_delete(local_3c0);
    local_3c8 = (BoundSlot *)0x0;
    local_3c0 = (int *)0x0;
  }
                    /* try { // try from 00bfdf50 to 00bfdfc6 has its CatchHandler @ 00c0380c */
  CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_a8);
  iVar6 = 0;
  pCVar26 = this;
  do {
    *(int *)(pCVar26 + 0xb0) = iVar6;
    iVar6 = iVar6 + 1;
    pCVar26 = pCVar26 + 4;
  } while (iVar6 != 400);
  local_3a84 = 1;
  pCVar26 = this;
  do {
    STRINGS::GetValueAsString((uint)local_b8);
                    /* try { // try from 00bfdfdc to 00bfdfe0 has its CatchHandler @ 00c0397f */
    std::operator+((char *)local_c8,(string *)0xff0cc3);
    local_1a10 = 0x20;
    local_1a08 = 0;
    local_19f8 = 0;
    local_1a00 = 0;
    local_1970 = (undefined4 *)0x0;
    local_1a18 = 0;
    local_19f0[0] = 0;
    lVar11 = *(long *)(local_c8[0] + -0x18);
                    /* try { // try from 00bfe04b to 00bfe04f has its CatchHandler @ 00c03994 */
    CEGUI::String::grow((ulong)&local_1a18);
    puVar19 = local_19f0;
    if (0x20 < local_1a10) {
      puVar19 = local_1970;
    }
    puVar19[lVar11] = 0;
    lVar29 = lVar11;
    while (lVar29 != 0) {
      lVar29 = lVar29 + -1;
      puVar19 = local_19f0;
      if (0x20 < local_1a10) {
        puVar19 = local_1970;
      }
      puVar19[lVar29] = (uint)*(byte *)(local_c8[0] + lVar29);
    }
    local_1a18 = lVar11;
                    /* try { // try from 00bfe0cb to 00bfe0cf has its CatchHandler @ 00c039a6 */
    lVar11 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x28));
                    /* try { // try from 00bfe0db to 00bfe0df has its CatchHandler @ 00c03994 */
    CEGUI::String::~String((String *)&local_1a18);
    if ((allocator *)(local_c8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_c8[0] + -8);
      iVar6 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar6 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
      }
    }
    if ((allocator *)(local_b8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_b8[0] + -8);
      iVar6 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar6 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
      }
    }
                    /* try { // try from 00bfe116 to 00bfe155 has its CatchHandler @ 00c0380c */
    CEGUI::Window::moveToFront();
    *(undefined1 *)(lVar11 + 0x213) = 0;
    CEGUI::Window::setWantsMultiClickEvents(SUB81(lVar11,0));
    *(CStashMenu **)(lVar11 + 0x1d8) = this + (ulong)(local_3a84 + 0x12) * 4 + 0xb0;
    pcVar4 = *(code **)(*(long *)(lVar11 + 0x38) + 0x10);
    local_d8[0] = operator_new(0x20);
    lVar29 = lVar11 + 0x38;
    *local_d8[0] = &PTR__MemberFunctionSlot_00ff17b0;
    local_d8[0][2] = 0;
    local_d8[0][1] = handle_ItemClick;
    local_d8[0][3] = this;
                    /* try { // try from 00bfe198 to 00bfe1d3 has its CatchHandler @ 00c03a26 */
    (*pcVar4)(&local_3d8,lVar29,CEGUI::Window::EventMouseButtonDown,(SubscriberSlot *)local_d8);
    pBVar5 = local_3d8;
    if ((local_3d8 != (BoundSlot *)0x0) &&
       (iVar6 = *local_3d0, *local_3d0 = iVar6 + -1, iVar6 + -1 == 0)) {
      if (local_3d8 != (BoundSlot *)0x0) {
        CEGUI::BoundSlot::~BoundSlot(local_3d8);
        operator_delete(pBVar5);
      }
      operator_delete(local_3d0);
      local_3d8 = (BoundSlot *)0x0;
      local_3d0 = (int *)0x0;
    }
                    /* try { // try from 00bfe206 to 00bfe221 has its CatchHandler @ 00c0380c */
    CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_d8);
    pcVar4 = *(code **)(*(long *)(lVar11 + 0x38) + 0x10);
    local_e8[0] = operator_new(0x20);
    *local_e8[0] = &PTR__MemberFunctionSlot_00ff17b0;
    local_e8[0][2] = 0;
    local_e8[0][1] = handle_MouseOver;
    local_e8[0][3] = this;
                    /* try { // try from 00bfe260 to 00bfe29b has its CatchHandler @ 00c03a2b */
    (*pcVar4)(&local_3e8,lVar29,CEGUI::Window::EventMouseEnters,(SubscriberSlot *)local_e8);
    pBVar5 = local_3e8;
    if ((local_3e8 != (BoundSlot *)0x0) &&
       (iVar6 = *local_3e0, *local_3e0 = iVar6 + -1, iVar6 + -1 == 0)) {
      if (local_3e8 != (BoundSlot *)0x0) {
        CEGUI::BoundSlot::~BoundSlot(local_3e8);
        operator_delete(pBVar5);
      }
      operator_delete(local_3e0);
      local_3e8 = (BoundSlot *)0x0;
      local_3e0 = (int *)0x0;
    }
                    /* try { // try from 00bfe2ce to 00bfe2e9 has its CatchHandler @ 00c0380c */
    CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_e8);
    pcVar4 = *(code **)(*(long *)(lVar11 + 0x38) + 0x10);
    local_f8[0] = operator_new(0x20);
    *local_f8[0] = &PTR__MemberFunctionSlot_00ff17b0;
    local_f8[0][2] = 0;
    local_f8[0][1] = handle_MouseOver;
    local_f8[0][3] = this;
                    /* try { // try from 00bfe328 to 00bfe363 has its CatchHandler @ 00c03a30 */
    (*pcVar4)(&local_3f8,lVar29,CEGUI::Window::EventMouseMove,(SubscriberSlot *)local_f8);
    pBVar5 = local_3f8;
    if ((local_3f8 != (BoundSlot *)0x0) &&
       (iVar6 = *local_3f0, *local_3f0 = iVar6 + -1, iVar6 + -1 == 0)) {
      if (local_3f8 != (BoundSlot *)0x0) {
        CEGUI::BoundSlot::~BoundSlot(local_3f8);
        operator_delete(pBVar5);
      }
      operator_delete(local_3f0);
      local_3f8 = (BoundSlot *)0x0;
      local_3f0 = (int *)0x0;
    }
                    /* try { // try from 00bfe396 to 00bfe3b1 has its CatchHandler @ 00c0380c */
    CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_f8);
    pcVar4 = *(code **)(*(long *)(lVar11 + 0x38) + 0x10);
    local_108[0] = operator_new(0x20);
    *local_108[0] = &PTR__MemberFunctionSlot_00ff17b0;
    local_108[0][2] = 0;
    local_108[0][1] = handle_MouseOut;
    local_108[0][3] = this;
                    /* try { // try from 00bfe3f0 to 00bfe426 has its CatchHandler @ 00c03a35 */
    (*pcVar4)(&local_408,lVar29,CEGUI::Window::EventMouseLeaves,(SubscriberSlot *)local_108);
    pBVar5 = local_408;
    if ((local_408 != (BoundSlot *)0x0) &&
       (iVar6 = *local_400, *local_400 = iVar6 + -1, iVar6 + -1 == 0)) {
      if (local_408 != (BoundSlot *)0x0) {
        CEGUI::BoundSlot::~BoundSlot(local_408);
        operator_delete(pBVar5);
      }
      operator_delete(local_400);
      local_408 = (BoundSlot *)0x0;
      local_400 = (int *)0x0;
    }
                    /* try { // try from 00bfe457 to 00bfe4c4 has its CatchHandler @ 00c0380c */
    CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_108);
    *(long *)(pCVar26 + 0x1e80) = lVar11;
    local_1c20 = 0x20;
    local_1c18 = 0;
    local_1c08 = 0;
    local_1c10 = 0;
    local_1b80 = (undefined4 *)0x0;
    local_1c28 = 0;
    local_1c00[0] = 0;
    CEGUI::String::grow((ulong)&local_1c28);
    local_1c28 = 0;
    puVar19 = local_1b80;
    if (local_1c20 < 0x21) {
      puVar19 = local_1c00;
    }
    *puVar19 = 0;
                    /* try { // try from 00bfe507 to 00bfe50b has its CatchHandler @ 00c03a45 */
    std::string::string((string *)local_118,"gui_",&local_3a);
                    /* try { // try from 00bfe51c to 00bfe520 has its CatchHandler @ 00c03a5a */
    STRINGS::uniqueName((STRINGS *)local_128,(string *)local_118);
    local_1b70 = 0x20;
    local_1b68 = 0;
    local_1b58 = 0;
    local_1b60 = 0;
    local_1ad0 = (undefined4 *)0x0;
    local_1b78 = 0;
    local_1b50[0] = 0;
    lVar11 = *(long *)(local_128[0] + -0x18);
                    /* try { // try from 00bfe58b to 00bfe58f has its CatchHandler @ 00c03a6c */
    CEGUI::String::grow((ulong)&local_1b78);
    puVar19 = local_1b50;
    if (0x20 < local_1b70) {
      puVar19 = local_1ad0;
    }
    puVar19[lVar11] = 0;
    lVar29 = lVar11;
    while (lVar29 != 0) {
      lVar29 = lVar29 + -1;
      puVar19 = local_1b50;
      if (0x20 < local_1b70) {
        puVar19 = local_1ad0;
      }
      puVar19[lVar29] = (uint)*(byte *)(local_128[0] + lVar29);
    }
    pcVar28 = (char *)0x0;
    local_1ac0 = 0x20;
    local_1ab8 = 0;
    local_1aa8 = 0;
    pcVar13 = "GuiLook/StaticText";
    local_1ab0 = 0;
    local_1a20 = (uint *)0x0;
    local_1ac8 = 0;
    local_1aa0[0] = 0;
    cVar2 = s_GuiLook_StaticText_00fe4872[0];
    while (pcVar13 = pcVar13 + 1, cVar2 != '\0') {
      pcVar28 = pcVar13 + -0xfe4872;
      cVar2 = *pcVar13;
    }
    local_1b78 = lVar11;
    if (pcVar28 == CEGUI::String::npos) {
                    /* try { // try from 00c00ed7 to 00c00edb has its CatchHandler @ 00c03ee7 */
      std::string::string((string *)local_2b8,"Length for utf8 encoded string can not be \'npos\'",
                          local_4d);
      plVar21 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00c00eef to 00c00ef3 has its CatchHandler @ 00c03ecf */
      std::length_error::length_error(plVar21,(string *)local_2b8);
      if ((allocator *)(local_2b8[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_2b8[0] + -8);
        iVar6 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar6 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_2b8[0] + -0x18));
        }
      }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00c00f1a to 00c00f1e has its CatchHandler @ 00c03ac9 */
      __cxa_throw(plVar21,&std::length_error::typeinfo,std::length_error::~length_error);
    }
    lVar11 = 0;
    pcVar13 = pcVar28;
    pbVar15 = (byte *)"GuiLook/StaticText";
    while (pcVar13 != (char *)0x0) {
      bVar3 = *pbVar15;
      pcVar27 = pcVar13 + -1;
      pbVar24 = pbVar15 + 1;
      if ((char)bVar3 < '\0') {
        if (bVar3 < 0xe0) {
          pcVar27 = pcVar13 + -2;
          pbVar24 = pbVar15 + 2;
        }
        else if (bVar3 < 0xf0) {
          pcVar27 = pcVar13 + -3;
          pbVar24 = pbVar15 + 3;
        }
        else {
          pcVar27 = pcVar13 + -3;
          pbVar24 = pbVar15 + 4;
        }
      }
      lVar11 = lVar11 + 1;
      pcVar13 = pcVar27;
      pbVar15 = pbVar24;
    }
                    /* try { // try from 00bfe72b to 00bfe72f has its CatchHandler @ 00c03ac9 */
    CEGUI::String::grow((ulong)&local_1ac8);
    puVar20 = local_1a20;
    if (local_1ac0 < 0x21) {
      puVar20 = local_1aa0;
    }
    if (pcVar28 == (char *)0x0) {
      pcVar13 = "GuiLook/StaticText";
      if (s_GuiLook_StaticText_00fe4872[0] != '\0') {
        do {
          pcVar13 = pcVar13 + 1;
          pcVar28 = pcVar13 + -0xfe4872;
        } while (*pcVar13 != '\0');
        bVar30 = pcVar28 != (char *)0x0 && local_1ac0 != 0;
        goto LAB_00bfe75d;
      }
    }
    else {
      bVar30 = local_1ac0 != 0;
LAB_00bfe75d:
      if (bVar30) {
        pcVar13 = (char *)0x0;
        uVar9 = 0;
        uVar22 = local_1ac0;
        do {
          bVar3 = pcVar13[0xfe4872];
          uVar23 = (uint)bVar3;
          uVar8 = uVar9 + 1;
          if ((char)bVar3 < '\0') {
            uVar23 = (uint)bVar3;
            if (0xdf < bVar3) {
              if (bVar3 < 0xf0) {
                uVar25 = (ulong)uVar8;
                uVar8 = uVar9 + 3;
                uVar23 = (byte)"GuiLook/StaticText"[uVar9 + 2] & 0x3f | (uVar23 & 0xf) << 0xc |
                         ((byte)"GuiLook/StaticText"[uVar25] & 0x3f) << 6;
              }
              else {
                uVar25 = (ulong)uVar8;
                uVar8 = uVar9 + 4;
                uVar23 = ((byte)"GuiLook/StaticText"[uVar25] & 0x3f) << 0xc |
                         (byte)"GuiLook/StaticText"[uVar9 + 3] & 0x3f | (uVar23 & 7) << 0x12 |
                         ((byte)"GuiLook/StaticText"[uVar9 + 2] & 0x3f) << 6;
              }
              goto LAB_00bfe773;
            }
            uVar9 = uVar9 + 2;
            *puVar20 = (byte)"GuiLook/StaticText"[uVar8] & 0x3f | (uVar23 & 0x1f) << 6;
          }
          else {
LAB_00bfe773:
            *puVar20 = uVar23;
            uVar9 = uVar8;
          }
          pcVar13 = (char *)(ulong)uVar9;
          if ((pcVar28 <= pcVar13) || (uVar22 = uVar22 - 1, uVar22 == 0)) break;
          puVar20 = puVar20 + 1;
        } while( true );
      }
    }
    puVar20 = local_1a20;
    if (local_1ac0 < 0x21) {
      puVar20 = local_1aa0;
    }
    puVar20[lVar11] = 0;
    local_1ac8 = lVar11;
                    /* try { // try from 00bfe81a to 00bfe81e has its CatchHandler @ 00c03a7e */
    uVar10 = CEGUI::WindowManager::createWindow
                       (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,(String *)&local_1ac8,
                        (String *)&local_1b78);
    *(undefined8 *)(pCVar26 + 0x2308) = uVar10;
                    /* try { // try from 00bfe82e to 00bfe832 has its CatchHandler @ 00c03ac9 */
    CEGUI::String::~String((String *)&local_1ac8);
                    /* try { // try from 00bfe83b to 00bfe83f has its CatchHandler @ 00c03a6c */
    CEGUI::String::~String((String *)&local_1b78);
    if ((allocator *)(local_128[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_128[0] + -8);
      iVar6 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar6 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_128[0] + -0x18));
      }
    }
    if ((allocator *)(local_118[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_118[0] + -8);
      iVar6 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar6 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_118[0] + -0x18));
      }
    }
                    /* try { // try from 00bfe87c to 00bfe8e8 has its CatchHandler @ 00c0380c */
    CEGUI::String::~String((String *)&local_1c28);
    local_1cd0 = 0x20;
    local_1cc8 = 0;
    local_1cb8 = 0;
    local_1cc0 = 0;
    local_1c30 = (uint *)0x0;
    local_1cd8 = 0;
    local_1cb0[0] = 0;
    CEGUI::String::grow((ulong)&local_1cd8);
    puVar20 = local_1cb0;
    if (0x20 < local_1cd0) {
      puVar20 = local_1c30;
    }
    pcVar13 = "Serif";
    do {
      bVar3 = *pcVar13;
      pcVar13 = pcVar13 + 1;
      *puVar20 = (uint)bVar3;
      puVar20 = puVar20 + 1;
    } while ((byte *)pcVar13 != (byte *)0xfe4949);
    local_1cd8 = 5;
    puVar20 = local_1c9c;
    if (0x20 < local_1cd0) {
      puVar20 = local_1c30 + 5;
    }
    *puVar20 = 0;
                    /* try { // try from 00bfe95d to 00bfe961 has its CatchHandler @ 00c034d8 */
    CEGUI::Window::setFont(*(String **)(pCVar26 + 0x2308));
                    /* try { // try from 00bfe965 to 00bfe97c has its CatchHandler @ 00c0380c */
    CEGUI::String::~String((String *)&local_1cd8);
    CEGUI::Window::getSize();
                    /* try { // try from 00bfe987 to 00bfe98b has its CatchHandler @ 00c03525 */
    CEGUI::Window::setSize(*(UVector2 **)(pCVar26 + 0x2308));
                    /* try { // try from 00bfe98f to 00bfe993 has its CatchHandler @ 00c0380c */
    puVar17 = (undefined8 *)CEGUI::Window::getPosition();
    local_4a8 = *puVar17;
    local_4a0 = puVar17[1];
    local_1e30 = 0x20;
    local_1e28 = 0;
    local_1e18 = 0;
    local_1e20 = 0;
    local_1d90 = (uint *)0x0;
    local_1e38 = 0;
    local_1e10[0] = 0;
                    /* try { // try from 00bfea0e to 00bfea12 has its CatchHandler @ 00c03507 */
    CEGUI::String::grow((ulong)&local_1e38);
    puVar20 = local_1e10;
    if (0x20 < local_1e30) {
      puVar20 = local_1d90;
    }
    pcVar13 = "RightAligned";
    do {
      bVar3 = *pcVar13;
      pcVar13 = pcVar13 + 1;
      *puVar20 = (uint)bVar3;
      puVar20 = puVar20 + 1;
    } while ((byte *)pcVar13 != (byte *)0xfe602d);
    local_1e38 = 0xc;
    puVar20 = local_1de0;
    if (0x20 < local_1e30) {
      puVar20 = local_1d90 + 0xc;
    }
    *puVar20 = 0;
    local_1d80 = 0x20;
    local_1d78 = 0;
    local_1d68 = 0;
    local_1d70 = 0;
    local_1ce0 = (uint *)0x0;
    local_1d88 = 0;
    local_1d60[0] = 0;
                    /* try { // try from 00bfead5 to 00bfead9 has its CatchHandler @ 00c03515 */
    CEGUI::String::grow((ulong)&local_1d88);
    puVar20 = local_1d60;
    if (0x20 < local_1d80) {
      puVar20 = local_1ce0;
    }
    pcVar13 = "HorzTextFormatting";
    do {
      bVar3 = *pcVar13;
      pcVar13 = pcVar13 + 1;
      *puVar20 = (uint)bVar3;
      puVar20 = puVar20 + 1;
    } while ((byte *)pcVar13 != (byte *)0xfe48cf);
    local_1d88 = 0x12;
    puVar20 = local_1d18;
    if (0x20 < local_1d80) {
      puVar20 = local_1ce0 + 0x12;
    }
    *puVar20 = 0;
                    /* try { // try from 00bfeb50 to 00bfeb54 has its CatchHandler @ 00c034e8 */
    CEGUI::PropertySet::setProperty(*(String **)(pCVar26 + 0x2308),(String *)&local_1d88);
                    /* try { // try from 00bfeb58 to 00bfeb5c has its CatchHandler @ 00c03515 */
    CEGUI::String::~String((String *)&local_1d88);
                    /* try { // try from 00bfeb60 to 00bfebcc has its CatchHandler @ 00c03507 */
    CEGUI::String::~String((String *)&local_1e38);
    local_1f90 = 0x20;
    local_1f88 = 0;
    local_1f78 = 0;
    local_1f80 = 0;
    local_1ef0 = (uint *)0x0;
    local_1f98 = 0;
    local_1f70[0] = 0;
    CEGUI::String::grow((ulong)&local_1f98);
    puVar20 = local_1f70;
    if (0x20 < local_1f90) {
      puVar20 = local_1ef0;
    }
    pcVar13 = "TopAligned";
    do {
      bVar3 = *pcVar13;
      pcVar13 = pcVar13 + 1;
      *puVar20 = (uint)bVar3;
      puVar20 = puVar20 + 1;
    } while ((byte *)pcVar13 != (byte *)0xfe489f);
    local_1f98 = 10;
    puVar20 = local_1f48;
    if (0x20 < local_1f90) {
      puVar20 = local_1ef0 + 10;
    }
    *puVar20 = 0;
    local_1ee0 = 0x20;
    local_1ed8 = 0;
    local_1ec8 = 0;
    local_1ed0 = 0;
    local_1e40 = (uint *)0x0;
    local_1ee8 = 0;
    local_1ec0[0] = 0;
                    /* try { // try from 00bfec95 to 00bfec99 has its CatchHandler @ 00c034f8 */
    CEGUI::String::grow((ulong)&local_1ee8);
    puVar20 = local_1ec0;
    if (0x20 < local_1ee0) {
      puVar20 = local_1e40;
    }
    pcVar13 = "VertFormatting";
    do {
      bVar3 = *pcVar13;
      pcVar13 = pcVar13 + 1;
      *puVar20 = (uint)bVar3;
      puVar20 = puVar20 + 1;
    } while ((byte *)pcVar13 != (byte *)0xfe48ae);
    local_1ee8 = 0xe;
    puVar20 = local_1e88;
    if (0x20 < local_1ee0) {
      puVar20 = local_1e40 + 0xe;
    }
    *puVar20 = 0;
                    /* try { // try from 00bfed10 to 00bfed14 has its CatchHandler @ 00c034fd */
    CEGUI::PropertySet::setProperty(*(String **)(pCVar26 + 0x2308),(String *)&local_1ee8);
                    /* try { // try from 00bfed18 to 00bfed1c has its CatchHandler @ 00c034f8 */
    CEGUI::String::~String((String *)&local_1ee8);
                    /* try { // try from 00bfed20 to 00bfedd3 has its CatchHandler @ 00c03507 */
    CEGUI::String::~String((String *)&local_1f98);
    *(undefined1 *)(*(long *)(pCVar26 + 0x2308) + 0x3e2) = 1;
    CEGUI::Window::setPosition(*(UVector2 **)(pCVar26 + 0x2308));
    CEGUI::Window::addChildWindow(*(Window **)(*(long *)(pCVar26 + 0x1e80) + 0xb0));
    local_2040 = 0x20;
    local_2038 = 0;
    local_2028 = 0;
    local_2030 = 0;
    local_1fa0 = (undefined4 *)0x0;
    local_2048 = 0;
    local_2020[0] = 0;
    if (CEGUI::String::npos == (char *)0x0) {
                    /* try { // try from 00c00f97 to 00c00f9b has its CatchHandler @ 00c03ebc */
      std::string::string((string *)local_2c8,"Length for utf8 encoded string can not be \'npos\'",
                          local_51);
      plVar21 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00c00faf to 00c00fb3 has its CatchHandler @ 00c03e4a */
      std::length_error::length_error(plVar21,(string *)local_2c8);
      if ((allocator *)(local_2c8[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_2c8[0] + -8);
        iVar6 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar6 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_2c8[0] + -0x18));
        }
      }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00c00fda to 00c00fde has its CatchHandler @ 00c03507 */
      __cxa_throw(plVar21,&std::length_error::typeinfo,std::length_error::~length_error);
    }
    CEGUI::String::grow((ulong)&local_2048);
    local_2048 = 0;
    puVar19 = local_2020;
    if (0x20 < local_2040) {
      puVar19 = local_1fa0;
    }
    *puVar19 = 0;
                    /* try { // try from 00bfee08 to 00bfee0c has its CatchHandler @ 00c03547 */
    CEGUI::Window::setText(*(String **)(pCVar26 + 0x2308));
                    /* try { // try from 00bfee10 to 00bfee48 has its CatchHandler @ 00c03507 */
    CEGUI::String::~String((String *)&local_2048);
    CEGUI::colour::colour(local_4f8,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc);
    CEGUI::PropertyHelper::colourToString(local_20f8);
    local_21a0 = 0x20;
    local_2198 = 0;
    local_2188 = 0;
    local_2190 = 0;
    local_2100 = (uint *)0x0;
    local_21a8 = 0;
    local_2180[0] = 0;
                    /* try { // try from 00bfeeac to 00bfeeb0 has its CatchHandler @ 00c03502 */
    CEGUI::String::grow((ulong)&local_21a8);
    puVar20 = local_2180;
    if (0x20 < local_21a0) {
      puVar20 = local_2100;
    }
    pbVar15 = (byte *)0xfe4654;
    do {
      bVar3 = *pbVar15;
      pbVar15 = pbVar15 + 1;
      *puVar20 = (uint)bVar3;
      puVar20 = puVar20 + 1;
    } while (pbVar15 != (byte *)0xfe465e);
    local_21a8 = 10;
    puVar20 = local_2158;
    if (0x20 < local_21a0) {
      puVar20 = local_2100 + 10;
    }
    *puVar20 = 0;
                    /* try { // try from 00bfef20 to 00bfef24 has its CatchHandler @ 00c03545 */
    CEGUI::PropertySet::setProperty(*(String **)(pCVar26 + 0x2308),(String *)&local_21a8);
                    /* try { // try from 00bfef28 to 00bfef2c has its CatchHandler @ 00c03502 */
    CEGUI::String::~String((String *)&local_21a8);
                    /* try { // try from 00bfef30 to 00bfefa7 has its CatchHandler @ 00c03507 */
    CEGUI::String::~String(local_20f8);
    CEGUI::Window::setAlwaysOnTop(SUB81(*(undefined8 *)(pCVar26 + 0x2308),0));
    local_23b0 = 0x20;
    local_23a8 = 0;
    local_2398 = 0;
    local_23a0 = 0;
    local_2310 = (undefined4 *)0x0;
    local_23b8 = 0;
    local_2390[0] = 0;
    CEGUI::String::grow((ulong)&local_23b8);
    local_23b8 = 0;
    puVar19 = local_2310;
    if (local_23b0 < 0x21) {
      puVar19 = local_2390;
    }
    *puVar19 = 0;
                    /* try { // try from 00bfefea to 00bfefee has its CatchHandler @ 00c03555 */
    std::string::string((string *)local_138,"gui_",&local_3b);
                    /* try { // try from 00bfefff to 00bff003 has its CatchHandler @ 00c0356a */
    STRINGS::uniqueName((STRINGS *)local_148,(string *)local_138);
    local_2300 = 0x20;
    local_22f8 = 0;
    local_22e8 = 0;
    local_22f0 = 0;
    local_2260 = (undefined4 *)0x0;
    local_2308 = 0;
    local_22e0[0] = 0;
    lVar11 = *(long *)(local_148[0] + -0x18);
                    /* try { // try from 00bff06e to 00bff072 has its CatchHandler @ 00c0357c */
    CEGUI::String::grow((ulong)&local_2308);
    puVar19 = local_22e0;
    if (0x20 < local_2300) {
      puVar19 = local_2260;
    }
    puVar19[lVar11] = 0;
    lVar29 = lVar11;
    while (lVar29 != 0) {
      lVar29 = lVar29 + -1;
      puVar19 = local_22e0;
      if (0x20 < local_2300) {
        puVar19 = local_2260;
      }
      puVar19[lVar29] = (uint)*(byte *)(local_148[0] + lVar29);
    }
    pcVar28 = (char *)0x0;
    local_2250 = 0x20;
    local_2248 = 0;
    local_2238 = 0;
    pcVar13 = "GuiLook/StaticImage";
    local_2240 = 0;
    local_21b0 = (uint *)0x0;
    local_2258 = 0;
    local_2230[0] = 0;
    cVar2 = s_GuiLook_StaticImage_00fd0bff[0];
    while (pcVar13 = pcVar13 + 1, cVar2 != '\0') {
      pcVar28 = pcVar13 + -0xfd0bff;
      cVar2 = *pcVar13;
    }
    local_2308 = lVar11;
    if (pcVar28 == CEGUI::String::npos) {
                    /* try { // try from 00c01057 to 00c0105b has its CatchHandler @ 00c03d8f */
      std::string::string((string *)local_2d8,"Length for utf8 encoded string can not be \'npos\'",
                          local_53);
      plVar21 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00c0106f to 00c01073 has its CatchHandler @ 00c03d77 */
      std::length_error::length_error(plVar21,(string *)local_2d8);
      if ((allocator *)(local_2d8[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_2d8[0] + -8);
        iVar6 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar6 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_2d8[0] + -0x18));
        }
      }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00c0109a to 00c0109e has its CatchHandler @ 00c0359e */
      __cxa_throw(plVar21,&std::length_error::typeinfo,std::length_error::~length_error);
    }
    lVar11 = 0;
    pcVar13 = pcVar28;
    pbVar15 = (byte *)"GuiLook/StaticImage";
    while (pcVar13 != (char *)0x0) {
      bVar3 = *pbVar15;
      pcVar27 = pcVar13 + -1;
      pbVar24 = pbVar15 + 1;
      if ((char)bVar3 < '\0') {
        if (bVar3 < 0xe0) {
          pcVar27 = pcVar13 + -2;
          pbVar24 = pbVar15 + 2;
        }
        else if (bVar3 < 0xf0) {
          pcVar27 = pcVar13 + -3;
          pbVar24 = pbVar15 + 3;
        }
        else {
          pcVar27 = pcVar13 + -3;
          pbVar24 = pbVar15 + 4;
        }
      }
      lVar11 = lVar11 + 1;
      pcVar13 = pcVar27;
      pbVar15 = pbVar24;
    }
                    /* try { // try from 00bff21b to 00bff21f has its CatchHandler @ 00c0359e */
    CEGUI::String::grow((ulong)&local_2258);
    if (local_2250 < 0x21) {
      puVar20 = local_2230;
      if (pcVar28 != (char *)0x0) goto LAB_00bff247;
LAB_00c00d12:
      pcVar13 = "GuiLook/StaticImage";
      if (s_GuiLook_StaticImage_00fd0bff[0] != '\0') {
        do {
          pcVar13 = pcVar13 + 1;
          pcVar28 = pcVar13 + -0xfd0bff;
        } while (*pcVar13 != '\0');
        bVar30 = pcVar28 != (char *)0x0 && local_2250 != 0;
        goto LAB_00bff24d;
      }
    }
    else {
      puVar20 = local_21b0;
      if (pcVar28 == (char *)0x0) goto LAB_00c00d12;
LAB_00bff247:
      bVar30 = local_2250 != 0;
LAB_00bff24d:
      if (bVar30) {
        pcVar13 = (char *)0x0;
        uVar9 = 0;
        uVar22 = local_2250;
        do {
          bVar3 = pcVar13[0xfd0bff];
          uVar23 = (uint)bVar3;
          uVar8 = uVar9 + 1;
          if ((char)bVar3 < '\0') {
            uVar23 = (uint)bVar3;
            if (0xdf < bVar3) {
              if (bVar3 < 0xf0) {
                uVar25 = (ulong)uVar8;
                uVar8 = uVar9 + 3;
                uVar23 = (byte)"GuiLook/StaticImage"[uVar9 + 2] & 0x3f | (uVar23 & 0xf) << 0xc |
                         ((byte)"GuiLook/StaticImage"[uVar25] & 0x3f) << 6;
              }
              else {
                uVar25 = (ulong)uVar8;
                uVar8 = uVar9 + 4;
                uVar23 = ((byte)"GuiLook/StaticImage"[uVar25] & 0x3f) << 0xc |
                         (byte)"GuiLook/StaticImage"[uVar9 + 3] & 0x3f | (uVar23 & 7) << 0x12 |
                         ((byte)"GuiLook/StaticImage"[uVar9 + 2] & 0x3f) << 6;
              }
              goto LAB_00bff263;
            }
            uVar9 = uVar9 + 2;
            *puVar20 = (byte)"GuiLook/StaticImage"[uVar8] & 0x3f | (uVar23 & 0x1f) << 6;
          }
          else {
LAB_00bff263:
            *puVar20 = uVar23;
            uVar9 = uVar8;
          }
          pcVar13 = (char *)(ulong)uVar9;
          if ((pcVar28 <= pcVar13) || (uVar22 = uVar22 - 1, uVar22 == 0)) break;
          puVar20 = puVar20 + 1;
        } while( true );
      }
    }
    puVar20 = local_21b0;
    if (local_2250 < 0x21) {
      puVar20 = local_2230;
    }
    puVar20[lVar11] = 0;
    local_2258 = lVar11;
                    /* try { // try from 00bff30a to 00bff30e has its CatchHandler @ 00c035b0 */
    pUVar18 = (UVector2 *)
              CEGUI::WindowManager::createWindow
                        (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,(String *)&local_2258,
                         (String *)&local_2308);
                    /* try { // try from 00bff31a to 00bff31e has its CatchHandler @ 00c0359e */
    CEGUI::String::~String((String *)&local_2258);
                    /* try { // try from 00bff327 to 00bff32b has its CatchHandler @ 00c0357c */
    CEGUI::String::~String((String *)&local_2308);
    if ((allocator *)(local_148[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_148[0] + -8);
      iVar6 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar6 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_148[0] + -0x18));
      }
    }
    if ((allocator *)(local_138[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_138[0] + -8);
      iVar6 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar6 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_138[0] + -0x18));
      }
    }
                    /* try { // try from 00bff368 to 00bff3d3 has its CatchHandler @ 00c03507 */
    CEGUI::String::~String((String *)&local_23b8);
    CEGUI::Window::addChildWindow(*(Window **)(*(long *)(pCVar26 + 0x1e80) + 0xb0));
    pUVar18[0x213] = (UVector2)0x0;
    CEGUI::Window::setWantsMultiClickEvents(SUB81(pUVar18,0));
    pUVar18[0x3e2] = (UVector2)0x1;
    CEGUI::EventSet::setMutedState((bool)(SUB81(pUVar18,0) + '8'));
    CEGUI::Window::getPosition();
    CEGUI::Window::setPosition(pUVar18);
    CEGUI::Window::getSize();
                    /* try { // try from 00bff3da to 00bff3de has its CatchHandler @ 00c0361a */
    CEGUI::Window::setSize(pUVar18);
    *(UVector2 **)(pCVar26 + 0x10e8) = pUVar18;
    local_25c0 = 0x20;
    local_25b8 = 0;
    local_25a8 = 0;
    local_25b0 = 0;
    local_2520 = (undefined4 *)0x0;
    local_25c8 = 0;
    local_25a0[0] = 0;
                    /* try { // try from 00bff443 to 00bff447 has its CatchHandler @ 00c03507 */
    CEGUI::String::grow((ulong)&local_25c8);
    local_25c8 = 0;
    puVar19 = local_2520;
    if (local_25c0 < 0x21) {
      puVar19 = local_25a0;
    }
    *puVar19 = 0;
                    /* try { // try from 00bff48a to 00bff48e has its CatchHandler @ 00c03635 */
    std::string::string((string *)local_158,"gui_",&local_3c);
                    /* try { // try from 00bff49f to 00bff4a3 has its CatchHandler @ 00c0364a */
    STRINGS::uniqueName((STRINGS *)local_168,(string *)local_158);
    local_2510 = 0x20;
    local_2508 = 0;
    local_24f8 = 0;
    local_2500 = 0;
    local_2470 = (undefined4 *)0x0;
    local_2518 = 0;
    local_24f0[0] = 0;
    lVar11 = *(long *)(local_168[0] + -0x18);
                    /* try { // try from 00bff50e to 00bff512 has its CatchHandler @ 00c0365c */
    CEGUI::String::grow((ulong)&local_2518);
    puVar19 = local_2470;
    if (local_2510 < 0x21) {
      puVar19 = local_24f0;
    }
    puVar19[lVar11] = 0;
    if (lVar11 != 0) {
      lVar29 = lVar11;
      do {
        lVar29 = lVar29 + -1;
        puVar19 = local_24f0;
        if (0x20 < local_2510) {
          puVar19 = local_2470;
        }
        puVar19[lVar29] = (uint)*(byte *)(local_168[0] + lVar29);
      } while (lVar29 != 0);
    }
    pcVar28 = (char *)0x0;
    local_2460 = 0x20;
    local_2458 = 0;
    local_2448 = 0;
    pcVar13 = "GuiLook/StaticImage";
    local_2450 = 0;
    local_23c0 = (uint *)0x0;
    local_2468 = 0;
    local_2440[0] = 0;
    cVar2 = s_GuiLook_StaticImage_00fd0bff[0];
    while (pcVar13 = pcVar13 + 1, cVar2 != '\0') {
      pcVar28 = pcVar13 + -0xfd0bff;
      cVar2 = *pcVar13;
    }
    local_2518 = lVar11;
    if (pcVar28 == CEGUI::String::npos) {
                    /* try { // try from 00c01117 to 00c0111b has its CatchHandler @ 00c03cec */
      std::string::string((string *)local_2e8,"Length for utf8 encoded string can not be \'npos\'",
                          local_57);
      plVar21 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00c0112f to 00c01133 has its CatchHandler @ 00c03ca8 */
      std::length_error::length_error(plVar21,(string *)local_2e8);
      if ((allocator *)(local_2e8[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_2e8[0] + -8);
        iVar6 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar6 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_2e8[0] + -0x18));
        }
      }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00c0115a to 00c0115e has its CatchHandler @ 00c03875 */
      __cxa_throw(plVar21,&std::length_error::typeinfo,std::length_error::~length_error);
    }
    lVar11 = 0;
    pcVar13 = pcVar28;
    pbVar15 = (byte *)"GuiLook/StaticImage";
    while (pcVar13 != (char *)0x0) {
      bVar3 = *pbVar15;
      pcVar27 = pcVar13 + -1;
      pbVar24 = pbVar15 + 1;
      if ((char)bVar3 < '\0') {
        if (bVar3 < 0xe0) {
          pcVar27 = pcVar13 + -2;
          pbVar24 = pbVar15 + 2;
        }
        else if (bVar3 < 0xf0) {
          pcVar27 = pcVar13 + -3;
          pbVar24 = pbVar15 + 3;
        }
        else {
          pcVar27 = pcVar13 + -3;
          pbVar24 = pbVar15 + 4;
        }
      }
      lVar11 = lVar11 + 1;
      pcVar13 = pcVar27;
      pbVar15 = pbVar24;
    }
                    /* try { // try from 00bff71b to 00bff71f has its CatchHandler @ 00c03875 */
    CEGUI::String::grow((ulong)&local_2468);
    if (local_2460 < 0x21) {
      puVar20 = local_2440;
      if (pcVar28 != (char *)0x0) goto LAB_00bff747;
LAB_00c00da8:
      pcVar13 = "GuiLook/StaticImage";
      if (s_GuiLook_StaticImage_00fd0bff[0] != '\0') {
        do {
          pcVar13 = pcVar13 + 1;
          pcVar28 = pcVar13 + -0xfd0bff;
        } while (*pcVar13 != '\0');
        bVar30 = pcVar28 != (char *)0x0 && local_2460 != 0;
        goto LAB_00bff74d;
      }
    }
    else {
      puVar20 = local_23c0;
      if (pcVar28 == (char *)0x0) goto LAB_00c00da8;
LAB_00bff747:
      bVar30 = local_2460 != 0;
LAB_00bff74d:
      if (bVar30) {
        pcVar13 = (char *)0x0;
        uVar9 = 0;
        uVar22 = local_2460;
        do {
          bVar3 = pcVar13[0xfd0bff];
          uVar23 = (uint)bVar3;
          uVar8 = uVar9 + 1;
          if ((char)bVar3 < '\0') {
            uVar23 = (uint)bVar3;
            if (0xdf < bVar3) {
              if (bVar3 < 0xf0) {
                uVar25 = (ulong)uVar8;
                uVar8 = uVar9 + 3;
                uVar23 = (byte)"GuiLook/StaticImage"[uVar9 + 2] & 0x3f | (uVar23 & 0xf) << 0xc |
                         ((byte)"GuiLook/StaticImage"[uVar25] & 0x3f) << 6;
              }
              else {
                uVar25 = (ulong)uVar8;
                uVar8 = uVar9 + 4;
                uVar23 = ((byte)"GuiLook/StaticImage"[uVar25] & 0x3f) << 0xc |
                         (byte)"GuiLook/StaticImage"[uVar9 + 3] & 0x3f | (uVar23 & 7) << 0x12 |
                         ((byte)"GuiLook/StaticImage"[uVar9 + 2] & 0x3f) << 6;
              }
              goto LAB_00bff763;
            }
            uVar9 = uVar9 + 2;
            *puVar20 = (byte)"GuiLook/StaticImage"[uVar8] & 0x3f | (uVar23 & 0x1f) << 6;
          }
          else {
LAB_00bff763:
            *puVar20 = uVar23;
            uVar9 = uVar8;
          }
          pcVar13 = (char *)(ulong)uVar9;
          if ((pcVar28 <= pcVar13) || (uVar22 = uVar22 - 1, uVar22 == 0)) break;
          puVar20 = puVar20 + 1;
        } while( true );
      }
    }
    puVar20 = local_23c0;
    if (local_2460 < 0x21) {
      puVar20 = local_2440;
    }
    puVar20[lVar11] = 0;
    local_2468 = lVar11;
                    /* try { // try from 00bff80a to 00bff80e has its CatchHandler @ 00c038a7 */
    pUVar18 = (UVector2 *)
              CEGUI::WindowManager::createWindow
                        (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,(String *)&local_2468,
                         (String *)&local_2518);
                    /* try { // try from 00bff81a to 00bff81e has its CatchHandler @ 00c03875 */
    CEGUI::String::~String((String *)&local_2468);
                    /* try { // try from 00bff827 to 00bff82b has its CatchHandler @ 00c0365c */
    CEGUI::String::~String((String *)&local_2518);
    if ((allocator *)(local_168[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_168[0] + -8);
      iVar6 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar6 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_168[0] + -0x18));
      }
    }
    if ((allocator *)(local_158[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_158[0] + -8);
      iVar6 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar6 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_158[0] + -0x18));
      }
    }
                    /* try { // try from 00bff868 to 00bff8c9 has its CatchHandler @ 00c03507 */
    CEGUI::String::~String((String *)&local_25c8);
    CEGUI::Window::addChildWindow(*(Window **)(this + 0x38));
    pUVar18[0x213] = (UVector2)0x0;
    CEGUI::Window::setWantsMultiClickEvents(SUB81(pUVar18,0));
    pUVar18[0x3e2] = (UVector2)0x1;
    CEGUI::EventSet::setMutedState((bool)(SUB81(pUVar18,0) + '8'));
    CEGUI::Window::getPosition();
    CEGUI::Window::setPosition(pUVar18);
    CEGUI::Window::getSize();
                    /* try { // try from 00bff8d0 to 00bff8d4 has its CatchHandler @ 00c0369e */
    CEGUI::Window::setSize(pUVar18);
    *(UVector2 **)(pCVar26 + 0x19f8) = pUVar18;
    local_27d0 = 0x20;
    local_27c8 = 0;
    local_27b8 = 0;
    local_27c0 = 0;
    local_2730 = (undefined4 *)0x0;
    local_27d8 = 0;
    local_27b0[0] = 0;
                    /* try { // try from 00bff939 to 00bff93d has its CatchHandler @ 00c03507 */
    CEGUI::String::grow((ulong)&local_27d8);
    local_27d8 = 0;
    puVar19 = local_2730;
    if (local_27d0 < 0x21) {
      puVar19 = local_27b0;
    }
    *puVar19 = 0;
                    /* try { // try from 00bff980 to 00bff984 has its CatchHandler @ 00c038b9 */
    std::string::string((string *)local_178,"gui_",&local_3d);
                    /* try { // try from 00bff995 to 00bff999 has its CatchHandler @ 00c0389f */
    STRINGS::uniqueName((STRINGS *)local_188,(string *)local_178);
    local_2720 = 0x20;
    local_2718 = 0;
    local_2708 = 0;
    local_2710 = 0;
    local_2680 = (undefined4 *)0x0;
    local_2728 = 0;
    local_2700[0] = 0;
    lVar11 = *(long *)(local_188[0] + -0x18);
                    /* try { // try from 00bffa07 to 00bffa0b has its CatchHandler @ 00c03955 */
    CEGUI::String::grow((ulong)&local_2728);
    puVar19 = local_2700;
    if (0x20 < local_2720) {
      puVar19 = local_2680;
    }
    puVar19[lVar11] = 0;
    if (lVar11 != 0) {
      lVar29 = lVar11;
      do {
        lVar29 = lVar29 + -1;
        puVar19 = local_2700;
        if (0x20 < local_2720) {
          puVar19 = local_2680;
        }
        puVar19[lVar29] = (uint)*(byte *)(local_188[0] + lVar29);
      } while (lVar29 != 0);
    }
    pcVar28 = (char *)0x0;
    local_2670 = 0x20;
    local_2668 = 0;
    local_2658 = 0;
    pcVar13 = "GuiLook/StaticImage";
    local_2660 = 0;
    local_25d0 = (uint *)0x0;
    local_2678 = 0;
    local_2650[0] = 0;
    cVar2 = s_GuiLook_StaticImage_00fd0bff[0];
    while (pcVar13 = pcVar13 + 1, cVar2 != '\0') {
      pcVar28 = pcVar13 + -0xfd0bff;
      cVar2 = *pcVar13;
    }
    local_2728 = lVar11;
    if (pcVar28 == CEGUI::String::npos) {
                    /* try { // try from 00c011d7 to 00c011db has its CatchHandler @ 00c03be9 */
      std::string::string((string *)local_2f8,"Length for utf8 encoded string can not be \'npos\'",
                          local_5b);
      plVar21 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00c011ef to 00c011f3 has its CatchHandler @ 00c03bd1 */
      std::length_error::length_error(plVar21,(string *)local_2f8);
      if ((allocator *)(local_2f8[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_2f8[0] + -8);
        iVar6 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar6 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_2f8[0] + -0x18));
        }
      }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00c0121a to 00c0121e has its CatchHandler @ 00c03ad9 */
      __cxa_throw(plVar21,&std::length_error::typeinfo,std::length_error::~length_error);
    }
    lVar11 = 0;
    pcVar13 = pcVar28;
    pbVar15 = (byte *)"GuiLook/StaticImage";
    while (pcVar13 != (char *)0x0) {
      bVar3 = *pbVar15;
      pcVar27 = pcVar13 + -1;
      pbVar24 = pbVar15 + 1;
      if ((char)bVar3 < '\0') {
        if (bVar3 < 0xe0) {
          pcVar27 = pcVar13 + -2;
          pbVar24 = pbVar15 + 2;
        }
        else if (bVar3 < 0xf0) {
          pcVar27 = pcVar13 + -3;
          pbVar24 = pbVar15 + 3;
        }
        else {
          pcVar27 = pcVar13 + -3;
          pbVar24 = pbVar15 + 4;
        }
      }
      lVar11 = lVar11 + 1;
      pcVar13 = pcVar27;
      pbVar15 = pbVar24;
    }
                    /* try { // try from 00bffbf6 to 00bffbfa has its CatchHandler @ 00c03ad9 */
    CEGUI::String::grow((ulong)&local_2678);
    if (local_2670 < 0x21) {
      puVar20 = local_2650;
      if (pcVar28 != (char *)0x0) goto LAB_00bffc22;
LAB_00c00e59:
      pcVar13 = "GuiLook/StaticImage";
      if (s_GuiLook_StaticImage_00fd0bff[0] != '\0') {
        do {
          pcVar13 = pcVar13 + 1;
          pcVar28 = pcVar13 + -0xfd0bff;
        } while (*pcVar13 != '\0');
        bVar30 = pcVar28 != (char *)0x0 && local_2670 != 0;
        goto LAB_00bffc28;
      }
    }
    else {
      puVar20 = local_25d0;
      if (pcVar28 == (char *)0x0) goto LAB_00c00e59;
LAB_00bffc22:
      bVar30 = local_2670 != 0;
LAB_00bffc28:
      if (bVar30) {
        pcVar13 = (char *)0x0;
        uVar9 = 0;
        uVar22 = local_2670;
        do {
          bVar3 = pcVar13[0xfd0bff];
          uVar23 = (uint)bVar3;
          uVar8 = uVar9 + 1;
          if ((char)bVar3 < '\0') {
            uVar23 = (uint)bVar3;
            if (0xdf < bVar3) {
              if (bVar3 < 0xf0) {
                uVar25 = (ulong)uVar8;
                uVar8 = uVar9 + 3;
                uVar23 = (byte)"GuiLook/StaticImage"[uVar9 + 2] & 0x3f | (uVar23 & 0xf) << 0xc |
                         ((byte)"GuiLook/StaticImage"[uVar25] & 0x3f) << 6;
              }
              else {
                uVar25 = (ulong)uVar8;
                uVar8 = uVar9 + 4;
                uVar23 = ((byte)"GuiLook/StaticImage"[uVar25] & 0x3f) << 0xc |
                         (byte)"GuiLook/StaticImage"[uVar9 + 3] & 0x3f | (uVar23 & 7) << 0x12 |
                         ((byte)"GuiLook/StaticImage"[uVar9 + 2] & 0x3f) << 6;
              }
              goto LAB_00bffc3b;
            }
            uVar9 = uVar9 + 2;
            *puVar20 = (byte)"GuiLook/StaticImage"[uVar8] & 0x3f | (uVar23 & 0x1f) << 6;
          }
          else {
LAB_00bffc3b:
            *puVar20 = uVar23;
            uVar9 = uVar8;
          }
          pcVar13 = (char *)(ulong)uVar9;
          if ((pcVar28 <= pcVar13) || (uVar22 = uVar22 - 1, uVar22 == 0)) break;
          puVar20 = puVar20 + 1;
        } while( true );
      }
    }
    puVar20 = local_25d0;
    if (local_2670 < 0x21) {
      puVar20 = local_2650;
    }
    puVar20[lVar11] = 0;
    local_2678 = lVar11;
                    /* try { // try from 00bffcd5 to 00bffcd9 has its CatchHandler @ 00c0378c */
    pUVar18 = (UVector2 *)
              CEGUI::WindowManager::createWindow
                        (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,(String *)&local_2678,
                         (String *)&local_2728);
                    /* try { // try from 00bffce5 to 00bffce9 has its CatchHandler @ 00c03ad9 */
    CEGUI::String::~String((String *)&local_2678);
                    /* try { // try from 00bffced to 00bffcf1 has its CatchHandler @ 00c03955 */
    CEGUI::String::~String((String *)&local_2728);
    if ((allocator *)(local_188[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_188[0] + -8);
      iVar6 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar6 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_188[0] + -0x18));
      }
    }
    if ((allocator *)(local_178[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_178[0] + -8);
      iVar6 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar6 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_178[0] + -0x18));
      }
    }
                    /* try { // try from 00bffd2e to 00bffda1 has its CatchHandler @ 00c03507 */
    CEGUI::String::~String((String *)&local_27d8);
    CEGUI::Window::addChildWindow(*(Window **)(*(long *)(pCVar26 + 0x1e80) + 0xb0));
    pUVar18[0x213] = (UVector2)0x0;
    bVar30 = SUB81(pUVar18,0);
    CEGUI::Window::setWantsMultiClickEvents(bVar30);
    pUVar18[0x3e2] = (UVector2)0x1;
    CEGUI::EventSet::setMutedState((bool)(bVar30 + '8'));
    CEGUI::Window::getPosition();
    CEGUI::Window::setPosition(pUVar18);
    CEGUI::Window::getSize();
                    /* try { // try from 00bffda8 to 00bffdac has its CatchHandler @ 00c0393d */
    CEGUI::Window::setSize(pUVar18);
                    /* try { // try from 00bffdb5 to 00bffdb9 has its CatchHandler @ 00c03507 */
    CEGUI::Window::setAlwaysOnTop(bVar30);
    *(UVector2 **)(pCVar26 + 0x1570) = pUVar18;
    local_3a84 = local_3a84 + 1;
    pCVar26 = pCVar26 + 8;
  } while (local_3a84 != 0x2b);
  local_2880 = 0x20;
  local_2878 = 0;
  local_2868 = 0;
  local_2870 = 0;
  local_27e0 = (uint *)0x0;
  local_2888 = 0;
  local_2860[0] = 0;
                    /* try { // try from 00bffe38 to 00bffe3c has its CatchHandler @ 00c0380c */
  CEGUI::String::grow((ulong)&local_2888);
  puVar20 = local_2860;
  if (0x20 < local_2880) {
    puVar20 = local_27e0;
  }
  pcVar13 = "TabBackpack";
  do {
    bVar3 = *pcVar13;
    pcVar13 = pcVar13 + 1;
    *puVar20 = (uint)bVar3;
    puVar20 = puVar20 + 1;
  } while ((byte *)pcVar13 != (byte *)0xfef7db);
  local_2888 = 0xb;
  puVar20 = local_2834;
  if (0x20 < local_2880) {
    puVar20 = local_27e0 + 0xb;
  }
  *puVar20 = 0;
                    /* try { // try from 00bffea2 to 00bffea6 has its CatchHandler @ 00c03495 */
  uVar10 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x40));
  *(undefined8 *)(this + 0x33e0) = uVar10;
                    /* try { // try from 00bffeb1 to 00bfff1d has its CatchHandler @ 00c0380c */
  CEGUI::String::~String((String *)&local_2888);
  local_2930 = 0x20;
  local_2928 = 0;
  local_2918 = 0;
  local_2920 = 0;
  local_2890 = (uint *)0x0;
  local_2938 = 0;
  local_2910[0] = 0;
  CEGUI::String::grow((ulong)&local_2938);
  puVar20 = local_2910;
  if (0x20 < local_2930) {
    puVar20 = local_2890;
  }
  pcVar13 = "TabSpell";
  do {
    bVar3 = *pcVar13;
    pcVar13 = pcVar13 + 1;
    *puVar20 = (uint)bVar3;
    puVar20 = puVar20 + 1;
  } while ((byte *)pcVar13 != (byte *)0xfef7cf);
  local_2938 = 8;
  puVar20 = local_28f0;
  if (0x20 < local_2930) {
    puVar20 = local_2890 + 8;
  }
  *puVar20 = 0;
                    /* try { // try from 00bfff83 to 00bfff87 has its CatchHandler @ 00c03485 */
  uVar10 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x40));
  *(undefined8 *)(this + 0x33e8) = uVar10;
                    /* try { // try from 00bfff92 to 00bffffe has its CatchHandler @ 00c0380c */
  CEGUI::String::~String((String *)&local_2938);
  local_29e0 = 0x20;
  local_29d8 = 0;
  local_29c8 = 0;
  local_29d0 = 0;
  local_2940 = (uint *)0x0;
  local_29e8 = 0;
  local_29c0[0] = 0;
  CEGUI::String::grow((ulong)&local_29e8);
  puVar20 = local_29c0;
  if (0x20 < local_29e0) {
    puVar20 = local_2940;
  }
  pcVar13 = "TabFish";
  do {
    bVar3 = *pcVar13;
    pcVar13 = pcVar13 + 1;
    *puVar20 = (uint)bVar3;
    puVar20 = puVar20 + 1;
  } while ((byte *)pcVar13 != (byte *)0xfef7c6);
  local_29e8 = 7;
  puVar20 = local_29a4;
  if (0x20 < local_29e0) {
    puVar20 = local_2940 + 7;
  }
  *puVar20 = 0;
                    /* try { // try from 00c00064 to 00c00068 has its CatchHandler @ 00c03475 */
  uVar10 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x40));
  *(undefined8 *)(this + 0x33f0) = uVar10;
                    /* try { // try from 00c00073 to 00c00109 has its CatchHandler @ 00c0380c */
  CEGUI::String::~String((String *)&local_29e8);
  CEGUI::Window::setZOrderingEnabled(SUB81(*(undefined8 *)(this + 0x33e0),0));
  CEGUI::Window::setZOrderingEnabled(SUB81(*(undefined8 *)(this + 0x33e8),0));
  CEGUI::Window::setZOrderingEnabled(SUB81(*(undefined8 *)(this + 0x33f0),0));
  local_2a90 = 0x20;
  local_2a88 = 0;
  local_2a78 = 0;
  local_2a80 = 0;
  local_29f0 = (uint *)0x0;
  local_2a98 = 0;
  local_2a70[0] = 0;
  CEGUI::String::grow((ulong)&local_2a98);
  puVar20 = local_2a70;
  if (0x20 < local_2a90) {
    puVar20 = local_29f0;
  }
  pcVar13 = "PetSlotsEquipment";
  do {
    bVar3 = *pcVar13;
    pcVar13 = pcVar13 + 1;
    *puVar20 = (uint)bVar3;
    puVar20 = puVar20 + 1;
  } while ((byte *)pcVar13 != (byte *)0xfeff78);
  local_2a98 = 0x11;
  puVar20 = local_2a2c;
  if (0x20 < local_2a90) {
    puVar20 = local_29f0 + 0x11;
  }
  *puVar20 = 0;
                    /* try { // try from 00c0016f to 00c00173 has its CatchHandler @ 00c0346a */
  uVar10 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x40));
  *(undefined8 *)(this + 0x33c8) = uVar10;
                    /* try { // try from 00c0017e to 00c001ea has its CatchHandler @ 00c0380c */
  CEGUI::String::~String((String *)&local_2a98);
  local_2b40 = 0x20;
  local_2b38 = 0;
  local_2b28 = 0;
  local_2b30 = 0;
  local_2aa0 = (uint *)0x0;
  local_2b48 = 0;
  local_2b20[0] = 0;
  CEGUI::String::grow((ulong)&local_2b48);
  puVar20 = local_2b20;
  if (0x20 < local_2b40) {
    puVar20 = local_2aa0;
  }
  pcVar13 = "PetSlotsSpells";
  do {
    bVar3 = *pcVar13;
    pcVar13 = pcVar13 + 1;
    *puVar20 = (uint)bVar3;
    puVar20 = puVar20 + 1;
  } while ((byte *)pcVar13 != (byte *)0xfeff66);
  local_2b48 = 0xe;
  puVar20 = local_2ae8;
  if (0x20 < local_2b40) {
    puVar20 = local_2aa0 + 0xe;
  }
  *puVar20 = 0;
                    /* try { // try from 00c00250 to 00c00254 has its CatchHandler @ 00c03465 */
  uVar10 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x40));
  *(undefined8 *)(this + 0x33d0) = uVar10;
                    /* try { // try from 00c0025f to 00c002d9 has its CatchHandler @ 00c0380c */
  CEGUI::String::~String((String *)&local_2b48);
  CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x33d0),0));
  local_2bf0 = 0x20;
  local_2be8 = 0;
  local_2bd8 = 0;
  local_2be0 = 0;
  local_2b50 = (uint *)0x0;
  local_2bf8 = 0;
  local_2bd0[0] = 0;
  CEGUI::String::grow((ulong)&local_2bf8);
  puVar20 = local_2bd0;
  if (0x20 < local_2bf0) {
    puVar20 = local_2b50;
  }
  pcVar13 = "PetSlotsFish";
  do {
    bVar3 = *pcVar13;
    pcVar13 = pcVar13 + 1;
    *puVar20 = (uint)bVar3;
    puVar20 = puVar20 + 1;
  } while ((byte *)pcVar13 != (byte *)0xfeff57);
  local_2bf8 = 0xc;
  puVar20 = local_2ba0;
  if (0x20 < local_2bf0) {
    puVar20 = local_2b50 + 0xc;
  }
  *puVar20 = 0;
                    /* try { // try from 00c0033f to 00c00343 has its CatchHandler @ 00c0345c */
  uVar10 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x40));
  *(undefined8 *)(this + 0x33d8) = uVar10;
                    /* try { // try from 00c0034e to 00c003ab has its CatchHandler @ 00c0380c */
  CEGUI::String::~String((String *)&local_2bf8);
  CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x33d8),0));
  local_3a84 = 1;
  local_3a70 = this;
  do {
    STRINGS::GetValueAsString((uint)local_198);
                    /* try { // try from 00c003c1 to 00c003c5 has its CatchHandler @ 00c03454 */
    std::operator+((char *)local_1a8,(string *)"PetSlot");
    local_2ca0 = 0x20;
    local_2c98 = 0;
    local_2c88 = 0;
    local_2c90 = 0;
    local_2c00 = (undefined4 *)0x0;
    local_2ca8 = 0;
    local_2c80[0] = 0;
    lVar11 = *(long *)(local_1a8[0] + -0x18);
                    /* try { // try from 00c00430 to 00c00434 has its CatchHandler @ 00c031a6 */
    CEGUI::String::grow((ulong)&local_2ca8);
    puVar19 = local_2c80;
    if (0x20 < local_2ca0) {
      puVar19 = local_2c00;
    }
    puVar19[lVar11] = 0;
    lVar29 = lVar11;
    while (lVar29 != 0) {
      lVar29 = lVar29 + -1;
      puVar19 = local_2c80;
      if (0x20 < local_2ca0) {
        puVar19 = local_2c00;
      }
      puVar19[lVar29] = (uint)*(byte *)(local_1a8[0] + lVar29);
    }
    local_2ca8 = lVar11;
                    /* try { // try from 00c00498 to 00c0049c has its CatchHandler @ 00c03177 */
    lVar11 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x40));
                    /* try { // try from 00c004a8 to 00c004ac has its CatchHandler @ 00c031a6 */
    CEGUI::String::~String((String *)&local_2ca8);
    if ((allocator *)(local_1a8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_1a8[0] + -8);
      iVar6 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar6 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_1a8[0] + -0x18));
      }
    }
    if ((allocator *)(local_198[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_198[0] + -8);
      iVar6 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar6 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_198[0] + -0x18));
      }
    }
                    /* try { // try from 00c004e4 to 00c00521 has its CatchHandler @ 00c0380c */
    CEGUI::Window::moveToFront();
    *(undefined1 *)(lVar11 + 0x213) = 0;
    CEGUI::Window::setWantsMultiClickEvents(SUB81(lVar11,0));
    *(CStashMenu **)(lVar11 + 0x1d8) = this + (ulong)(local_3a84 + 0x12) * 4 + 0xb0;
    pcVar4 = *(code **)(*(long *)(lVar11 + 0x38) + 0x10);
    local_1b8[0] = operator_new(0x20);
    lVar29 = lVar11 + 0x38;
    *local_1b8[0] = &PTR__MemberFunctionSlot_00ff17b0;
    local_1b8[0][2] = 0;
    local_1b8[0][1] = handle_PetItemClick;
    local_1b8[0][3] = this;
                    /* try { // try from 00c00562 to 00c00597 has its CatchHandler @ 00c030f4 */
    (*pcVar4)(&local_458,lVar29,CEGUI::Window::EventMouseButtonDown,local_1b8);
    pBVar5 = local_458;
    if ((local_458 != (BoundSlot *)0x0) &&
       (iVar6 = *local_450, *local_450 = iVar6 + -1, iVar6 + -1 == 0)) {
      if (local_458 != (BoundSlot *)0x0) {
        CEGUI::BoundSlot::~BoundSlot(local_458);
        operator_delete(pBVar5);
      }
      operator_delete(local_450);
      local_458 = (BoundSlot *)0x0;
      local_450 = (int *)0x0;
    }
                    /* try { // try from 00c005cd to 00c005e4 has its CatchHandler @ 00c0380c */
    CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_1b8);
    pcVar4 = *(code **)(*(long *)(lVar11 + 0x38) + 0x10);
    local_1c8[0] = operator_new(0x20);
    *local_1c8[0] = &PTR__MemberFunctionSlot_00ff17b0;
    local_1c8[0][2] = 0;
    local_1c8[0][1] = handle_PetMouseOver;
    local_1c8[0][3] = this;
                    /* try { // try from 00c00620 to 00c00655 has its CatchHandler @ 00c030df */
    (*pcVar4)(&local_468,lVar29,CEGUI::Window::EventMouseEnters,local_1c8);
    pBVar5 = local_468;
    if ((local_468 != (BoundSlot *)0x0) &&
       (iVar6 = *local_460, *local_460 = iVar6 + -1, iVar6 + -1 == 0)) {
      if (local_468 != (BoundSlot *)0x0) {
        CEGUI::BoundSlot::~BoundSlot(local_468);
        operator_delete(pBVar5);
      }
      operator_delete(local_460);
      local_468 = (BoundSlot *)0x0;
      local_460 = (int *)0x0;
    }
                    /* try { // try from 00c0068b to 00c006a2 has its CatchHandler @ 00c0380c */
    CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_1c8);
    pcVar4 = *(code **)(*(long *)(lVar11 + 0x38) + 0x10);
    local_1d8[0] = operator_new(0x20);
    *local_1d8[0] = &PTR__MemberFunctionSlot_00ff17b0;
    local_1d8[0][2] = 0;
    local_1d8[0][1] = handle_PetMouseOver;
    local_1d8[0][3] = this;
                    /* try { // try from 00c006de to 00c00713 has its CatchHandler @ 00c030ca */
    (*pcVar4)(&local_478,lVar29,CEGUI::Window::EventMouseMove,local_1d8);
    pBVar5 = local_478;
    if ((local_478 != (BoundSlot *)0x0) &&
       (iVar6 = *local_470, *local_470 = iVar6 + -1, iVar6 + -1 == 0)) {
      if (local_478 != (BoundSlot *)0x0) {
        CEGUI::BoundSlot::~BoundSlot(local_478);
        operator_delete(pBVar5);
      }
      operator_delete(local_470);
      local_478 = (BoundSlot *)0x0;
      local_470 = (int *)0x0;
    }
                    /* try { // try from 00c00749 to 00c00765 has its CatchHandler @ 00c0380c */
    CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_1d8);
    pcVar4 = *(code **)(*(long *)(lVar11 + 0x38) + 0x10);
    local_1e8[0] = operator_new(0x20);
    *local_1e8[0] = &PTR__MemberFunctionSlot_00ff17b0;
    local_1e8[0][2] = 0;
    local_1e8[0][1] = handle_PetMouseOut;
    local_1e8[0][3] = this;
                    /* try { // try from 00c007a4 to 00c007da has its CatchHandler @ 00c030ba */
    (*pcVar4)(&local_488,lVar29,CEGUI::Window::EventMouseLeaves,(SubscriberSlot *)local_1e8);
    pBVar5 = local_488;
    if ((local_488 != (BoundSlot *)0x0) &&
       (iVar6 = *local_480, *local_480 = iVar6 + -1, iVar6 + -1 == 0)) {
      if (local_488 != (BoundSlot *)0x0) {
        CEGUI::BoundSlot::~BoundSlot(local_488);
        operator_delete(pBVar5);
      }
      operator_delete(local_480);
      local_488 = (BoundSlot *)0x0;
      local_480 = (int *)0x0;
    }
                    /* try { // try from 00c0080b to 00c0087d has its CatchHandler @ 00c0380c */
    CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_1e8);
    *(long *)(local_3a70 + 0x2790) = lVar11;
    local_2eb0 = 0x20;
    local_2ea8 = 0;
    local_2e98 = 0;
    local_2ea0 = 0;
    local_2e10 = (undefined4 *)0x0;
    local_2eb8 = 0;
    local_2e90[0] = 0;
    CEGUI::String::grow((ulong)&local_2eb8);
    local_2eb8 = 0;
    puVar19 = local_2e10;
    if (local_2eb0 < 0x21) {
      puVar19 = local_2e90;
    }
    *puVar19 = 0;
                    /* try { // try from 00c008c0 to 00c008c4 has its CatchHandler @ 00c03238 */
    std::string::string((string *)local_1f8,"gui_",&local_3e);
                    /* try { // try from 00c008d5 to 00c008d9 has its CatchHandler @ 00c0309d */
    STRINGS::uniqueName((STRINGS *)local_208,(string *)local_1f8);
    local_2e00 = 0x20;
    local_2df8 = 0;
    local_2de8 = 0;
    local_2df0 = 0;
    local_2d60 = (undefined4 *)0x0;
    local_2e08 = 0;
    local_2de0[0] = 0;
    lVar11 = *(long *)(local_208[0] + -0x18);
                    /* try { // try from 00c00944 to 00c00948 has its CatchHandler @ 00c03098 */
    CEGUI::String::grow((ulong)&local_2e08);
    puVar19 = local_2de0;
    if (0x20 < local_2e00) {
      puVar19 = local_2d60;
    }
    puVar19[lVar11] = 0;
    lVar29 = lVar11;
    while (lVar29 != 0) {
      lVar29 = lVar29 + -1;
      puVar19 = local_2de0;
      if (0x20 < local_2e00) {
        puVar19 = local_2d60;
      }
      puVar19[lVar29] = (uint)*(byte *)(local_208[0] + lVar29);
    }
    local_2d50 = 0x20;
    local_2d48 = 0;
    local_2d38 = 0;
    local_2d40 = 0;
    local_2cb0 = (uint *)0x0;
    local_2d58 = 0;
    local_2d30[0] = 0;
    pcVar13 = (char *)0x0;
    cVar2 = s_GuiLook_StaticText_00fe4872[0];
    while (cVar2 != '\0') {
      cVar2 = pcVar13[0xfe4873];
      pcVar13 = pcVar13 + 1;
    }
    local_2e08 = lVar11;
    if (pcVar13 == CEGUI::String::npos) {
                    /* try { // try from 00c02be0 to 00c02be4 has its CatchHandler @ 00c0342c */
      std::string::string((string *)local_308,"Length for utf8 encoded string can not be \'npos\'",
                          local_61);
      plVar21 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00c02bf8 to 00c02bfc has its CatchHandler @ 00c03414 */
      std::length_error::length_error(plVar21,(string *)local_308);
      if ((allocator *)(local_308[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_308[0] + -8);
        iVar6 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar6 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_308[0] + -0x18));
        }
      }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00c02c23 to 00c02c27 has its CatchHandler @ 00c03051 */
      __cxa_throw(plVar21,&std::length_error::typeinfo,std::length_error::~length_error);
    }
    lVar11 = 0;
    pbVar15 = (byte *)"GuiLook/StaticText";
    pcVar28 = pcVar13;
    while (pcVar28 != (char *)0x0) {
      bVar3 = *pbVar15;
      pcVar27 = pcVar28 + -1;
      pbVar24 = pbVar15 + 1;
      if ((char)bVar3 < '\0') {
        if (bVar3 < 0xe0) {
          pcVar27 = pcVar28 + -2;
          pbVar24 = pbVar15 + 2;
        }
        else if (bVar3 < 0xf0) {
          pcVar27 = pcVar28 + -3;
          pbVar24 = pbVar15 + 3;
        }
        else {
          pcVar27 = pcVar28 + -3;
          pbVar24 = pbVar15 + 4;
        }
      }
      lVar11 = lVar11 + 1;
      pbVar15 = pbVar24;
      pcVar28 = pcVar27;
    }
                    /* try { // try from 00c01240 to 00c01244 has its CatchHandler @ 00c03051 */
    CEGUI::String::grow((ulong)&local_2d58);
    puVar20 = local_2cb0;
    if (local_2d50 < 0x21) {
      puVar20 = local_2d30;
    }
    if (pcVar13 == (char *)0x0) {
      pcVar28 = (char *)0x0;
      if (s_GuiLook_StaticText_00fe4872[0] != '\0') {
        do {
          pcVar13 = pcVar28 + 1;
          pcVar27 = pcVar28 + 0xfe4873;
          pcVar28 = pcVar13;
        } while (*pcVar27 != '\0');
        bVar30 = pcVar13 != (char *)0x0 && local_2d50 != 0;
        goto LAB_00c01294;
      }
    }
    else {
      bVar30 = local_2d50 != 0;
LAB_00c01294:
      if (bVar30) {
        pcVar28 = (char *)0x0;
        uVar22 = local_2d50;
        while( true ) {
          bVar3 = pcVar28[0xfe4872];
          uVar9 = (uint)bVar3;
          iVar6 = (int)pcVar28;
          pcVar28 = (char *)(ulong)(iVar6 + 1);
          if ((char)bVar3 < '\0') {
            uVar9 = (uint)bVar3;
            if (bVar3 < 0xe0) {
              uVar9 = (byte)pcVar28[0xfe4872] & 0x3f | (uVar9 & 0x1f) << 6;
              pcVar28 = (char *)(ulong)(iVar6 + 2);
            }
            else if (bVar3 < 0xf0) {
              uVar9 = (byte)"GuiLook/StaticText"[iVar6 + 2] & 0x3f | (uVar9 & 0xf) << 0xc |
                      ((byte)pcVar28[0xfe4872] & 0x3f) << 6;
              pcVar28 = (char *)(ulong)(iVar6 + 3);
            }
            else {
              pbVar15 = (byte *)(pcVar28 + 0xfe4872);
              pcVar28 = (char *)(ulong)(iVar6 + 4);
              uVar9 = (*pbVar15 & 0x3f) << 0xc | (byte)"GuiLook/StaticText"[iVar6 + 3] & 0x3f |
                      (uVar9 & 7) << 0x12 | ((byte)"GuiLook/StaticText"[iVar6 + 2] & 0x3f) << 6;
            }
          }
          *puVar20 = uVar9;
          uVar22 = uVar22 - 1;
          if ((pcVar13 <= pcVar28) || (uVar22 == 0)) break;
          puVar20 = puVar20 + 1;
        }
      }
    }
    puVar20 = local_2cb0;
    if (local_2d50 < 0x21) {
      puVar20 = local_2d30;
    }
    puVar20[lVar11] = 0;
    local_2d58 = lVar11;
                    /* try { // try from 00c0136c to 00c01370 has its CatchHandler @ 00c03326 */
    uVar10 = CEGUI::WindowManager::createWindow
                       (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,(String *)&local_2d58,
                        (String *)&local_2e08);
    *(undefined8 *)(local_3a70 + 0x31d0) = uVar10;
                    /* try { // try from 00c01385 to 00c01389 has its CatchHandler @ 00c03051 */
    CEGUI::String::~String((String *)&local_2d58);
                    /* try { // try from 00c01392 to 00c01396 has its CatchHandler @ 00c03098 */
    CEGUI::String::~String((String *)&local_2e08);
    if ((allocator *)(local_208[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_208[0] + -8);
      iVar6 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar6 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_208[0] + -0x18));
      }
    }
    if ((allocator *)(local_1f8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_1f8[0] + -8);
      iVar6 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar6 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_1f8[0] + -0x18));
      }
    }
                    /* try { // try from 00c013d3 to 00c0143f has its CatchHandler @ 00c0380c */
    CEGUI::String::~String((String *)&local_2eb8);
    local_2f60 = 0x20;
    local_2f58 = 0;
    local_2f48 = 0;
    local_2f50 = 0;
    local_2ec0 = (uint *)0x0;
    local_2f68 = 0;
    local_2f40[0] = 0;
    CEGUI::String::grow((ulong)&local_2f68);
    puVar20 = local_2f40;
    if (0x20 < local_2f60) {
      puVar20 = local_2ec0;
    }
    pcVar13 = "Serif";
    do {
      bVar3 = *pcVar13;
      pcVar13 = pcVar13 + 1;
      *puVar20 = (uint)bVar3;
      puVar20 = puVar20 + 1;
    } while ((byte *)pcVar13 != (byte *)0xfe4949);
    local_2f68 = 5;
    puVar20 = local_2f2c;
    if (0x20 < local_2f60) {
      puVar20 = local_2ec0 + 5;
    }
    *puVar20 = 0;
                    /* try { // try from 00c014af to 00c014b3 has its CatchHandler @ 00c032ab */
    CEGUI::Window::setFont(*(String **)(local_3a70 + 0x31d0));
                    /* try { // try from 00c014b7 to 00c014ce has its CatchHandler @ 00c0380c */
    CEGUI::String::~String((String *)&local_2f68);
    CEGUI::Window::getSize();
                    /* try { // try from 00c014de to 00c014e2 has its CatchHandler @ 00c032a6 */
    CEGUI::Window::setSize(*(UVector2 **)(local_3a70 + 0x31d0));
                    /* try { // try from 00c014e6 to 00c014ea has its CatchHandler @ 00c0380c */
    puVar17 = (undefined8 *)CEGUI::Window::getPosition();
    local_4a8 = *puVar17;
    local_4a0 = puVar17[1];
    local_30c0 = 0x20;
    local_30b8 = 0;
    local_30a8 = 0;
    local_30b0 = 0;
    local_3020 = (uint *)0x0;
    local_30c8 = 0;
    local_30a0[0] = 0;
                    /* try { // try from 00c01565 to 00c01569 has its CatchHandler @ 00c033c5 */
    CEGUI::String::grow((ulong)&local_30c8);
    puVar20 = local_30a0;
    if (0x20 < local_30c0) {
      puVar20 = local_3020;
    }
    pcVar13 = "RightAligned";
    do {
      bVar3 = *pcVar13;
      pcVar13 = pcVar13 + 1;
      *puVar20 = (uint)bVar3;
      puVar20 = puVar20 + 1;
    } while ((byte *)pcVar13 != (byte *)0xfe602d);
    local_30c8 = 0xc;
    puVar20 = local_3070;
    if (0x20 < local_30c0) {
      puVar20 = local_3020 + 0xc;
    }
    *puVar20 = 0;
    local_3010 = 0x20;
    local_3008 = 0;
    local_2ff8 = 0;
    local_3000 = 0;
    local_2f70 = (uint *)0x0;
    local_3018 = 0;
    local_2ff0[0] = 0;
                    /* try { // try from 00c0162d to 00c01631 has its CatchHandler @ 00c033b5 */
    CEGUI::String::grow((ulong)&local_3018);
    puVar20 = local_2ff0;
    if (0x20 < local_3010) {
      puVar20 = local_2f70;
    }
    pcVar13 = "HorzTextFormatting";
    do {
      bVar3 = *pcVar13;
      pcVar13 = pcVar13 + 1;
      *puVar20 = (uint)bVar3;
      puVar20 = puVar20 + 1;
    } while ((byte *)pcVar13 != (byte *)0xfe48cf);
    local_3018 = 0x12;
    puVar20 = local_2fa8;
    if (0x20 < local_3010) {
      puVar20 = local_2f70 + 0x12;
    }
    *puVar20 = 0;
                    /* try { // try from 00c016a4 to 00c016a8 has its CatchHandler @ 00c033a9 */
    CEGUI::PropertySet::setProperty(*(String **)(local_3a70 + 0x31d0),(String *)&local_3018);
                    /* try { // try from 00c016ac to 00c016b0 has its CatchHandler @ 00c033b5 */
    CEGUI::String::~String((String *)&local_3018);
                    /* try { // try from 00c016b4 to 00c01720 has its CatchHandler @ 00c033c5 */
    CEGUI::String::~String((String *)&local_30c8);
    local_3220 = 0x20;
    local_3218 = 0;
    local_3208 = 0;
    local_3210 = 0;
    local_3180 = (uint *)0x0;
    local_3228 = 0;
    local_3200[0] = 0;
    CEGUI::String::grow((ulong)&local_3228);
    puVar20 = local_3200;
    if (0x20 < local_3220) {
      puVar20 = local_3180;
    }
    pcVar13 = "BottomAligned";
    do {
      bVar3 = *pcVar13;
      pcVar13 = pcVar13 + 1;
      *puVar20 = (uint)bVar3;
      puVar20 = puVar20 + 1;
    } while ((byte *)pcVar13 != (byte *)0xfe6020);
    local_3228 = 0xd;
    puVar20 = local_31cc;
    if (0x20 < local_3220) {
      puVar20 = local_3180 + 0xd;
    }
    *puVar20 = 0;
    local_3170 = 0x20;
    local_3168 = 0;
    local_3158 = 0;
    local_3160 = 0;
    local_30d0 = (uint *)0x0;
    local_3178 = 0;
    local_3150[0] = 0;
                    /* try { // try from 00c017e2 to 00c017e6 has its CatchHandler @ 00c033a4 */
    CEGUI::String::grow((ulong)&local_3178);
    puVar20 = local_3150;
    if (0x20 < local_3170) {
      puVar20 = local_30d0;
    }
    pcVar13 = "VertFormatting";
    do {
      bVar3 = *pcVar13;
      pcVar13 = pcVar13 + 1;
      *puVar20 = (uint)bVar3;
      puVar20 = puVar20 + 1;
    } while ((byte *)pcVar13 != (byte *)0xfe48ae);
    local_3178 = 0xe;
    puVar20 = local_3118;
    if (0x20 < local_3170) {
      puVar20 = local_30d0 + 0xe;
    }
    *puVar20 = 0;
                    /* try { // try from 00c01859 to 00c0185d has its CatchHandler @ 00c033d5 */
    CEGUI::PropertySet::setProperty(*(String **)(local_3a70 + 0x31d0),(String *)&local_3178);
                    /* try { // try from 00c01861 to 00c01865 has its CatchHandler @ 00c033a4 */
    CEGUI::String::~String((String *)&local_3178);
                    /* try { // try from 00c01869 to 00c01926 has its CatchHandler @ 00c033c5 */
    CEGUI::String::~String((String *)&local_3228);
    *(undefined1 *)(*(long *)(local_3a70 + 0x31d0) + 0x3e2) = 1;
    CEGUI::Window::setPosition(*(UVector2 **)(local_3a70 + 0x31d0));
    CEGUI::Window::addChildWindow(*(Window **)(*(long *)(local_3a70 + 0x2790) + 0xb0));
    local_32d0 = 0x20;
    local_32c8 = 0;
    local_32b8 = 0;
    local_32c0 = 0;
    local_3230 = (undefined4 *)0x0;
    local_32d8 = 0;
    local_32b0[0] = 0;
    if (CEGUI::String::npos == (char *)0x0) {
                    /* try { // try from 00c02c40 to 00c02c44 has its CatchHandler @ 00c02d12 */
      std::string::string((string *)local_318,"Length for utf8 encoded string can not be \'npos\'",
                          local_65);
      plVar21 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00c02c58 to 00c02c5c has its CatchHandler @ 00c02cfd */
      std::length_error::length_error(plVar21,(string *)local_318);
      if ((allocator *)(local_318[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_318[0] + -8);
        iVar6 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar6 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_318[0] + -0x18));
        }
      }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00c02c7f to 00c02c83 has its CatchHandler @ 00c033c5 */
      __cxa_throw(plVar21,&std::length_error::typeinfo,std::length_error::~length_error);
    }
    CEGUI::String::grow((ulong)&local_32d8);
    local_32d8 = 0;
    puVar19 = local_32b0;
    if (0x20 < local_32d0) {
      puVar19 = local_3230;
    }
    *puVar19 = 0;
                    /* try { // try from 00c0195f to 00c01963 has its CatchHandler @ 00c030aa */
    CEGUI::Window::setText(*(String **)(local_3a70 + 0x31d0));
                    /* try { // try from 00c01967 to 00c0199f has its CatchHandler @ 00c033c5 */
    CEGUI::String::~String((String *)&local_32d8);
    CEGUI::colour::colour(local_518,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc);
    CEGUI::PropertyHelper::colourToString(local_3388);
    local_3430 = 0x20;
    local_3428 = 0;
    local_3418 = 0;
    local_3420 = 0;
    local_3390 = (uint *)0x0;
    local_3438 = 0;
    local_3410[0] = 0;
                    /* try { // try from 00c01a03 to 00c01a07 has its CatchHandler @ 00c030a2 */
    CEGUI::String::grow((ulong)&local_3438);
    puVar20 = local_3410;
    if (0x20 < local_3430) {
      puVar20 = local_3390;
    }
    pbVar15 = (byte *)0xfe4654;
    do {
      bVar3 = *pbVar15;
      pbVar15 = pbVar15 + 1;
      *puVar20 = (uint)bVar3;
      puVar20 = puVar20 + 1;
    } while (pbVar15 != (byte *)0xfe465e);
    local_3438 = 10;
    puVar20 = local_33e8;
    if (0x20 < local_3430) {
      puVar20 = local_3390 + 10;
    }
    *puVar20 = 0;
                    /* try { // try from 00c01a78 to 00c01a7c has its CatchHandler @ 00c02d45 */
    CEGUI::PropertySet::setProperty(*(String **)(local_3a70 + 0x31d0),(String *)&local_3438);
                    /* try { // try from 00c01a80 to 00c01a84 has its CatchHandler @ 00c030a2 */
    CEGUI::String::~String((String *)&local_3438);
                    /* try { // try from 00c01a88 to 00c01b04 has its CatchHandler @ 00c033c5 */
    CEGUI::String::~String(local_3388);
    CEGUI::Window::setAlwaysOnTop(SUB81(*(undefined8 *)(local_3a70 + 0x31d0),0));
    local_3640 = 0x20;
    local_3638 = 0;
    local_3628 = 0;
    local_3630 = 0;
    local_35a0 = (undefined4 *)0x0;
    local_3648 = 0;
    local_3620[0] = 0;
    CEGUI::String::grow((ulong)&local_3648);
    local_3648 = 0;
    puVar19 = local_35a0;
    if (local_3640 < 0x21) {
      puVar19 = local_3620;
    }
    *puVar19 = 0;
                    /* try { // try from 00c01b47 to 00c01b4b has its CatchHandler @ 00c02d65 */
    std::string::string((string *)local_218,"gui_",&local_3f);
                    /* try { // try from 00c01b5c to 00c01b60 has its CatchHandler @ 00c02d5d */
    STRINGS::uniqueName((STRINGS *)local_228,(string *)local_218);
    local_3590 = 0x20;
    local_3588 = 0;
    local_3578 = 0;
    local_3580 = 0;
    local_34f0 = (undefined4 *)0x0;
    local_3598 = 0;
    local_3570[0] = 0;
    lVar11 = *(long *)(local_228[0] + -0x18);
                    /* try { // try from 00c01bcb to 00c01bcf has its CatchHandler @ 00c02c84 */
    CEGUI::String::grow((ulong)&local_3598);
    puVar19 = local_3570;
    if (0x20 < local_3590) {
      puVar19 = local_34f0;
    }
    puVar19[lVar11] = 0;
    lVar29 = lVar11;
    while (lVar29 != 0) {
      lVar29 = lVar29 + -1;
      puVar19 = local_3570;
      if (0x20 < local_3590) {
        puVar19 = local_34f0;
      }
      puVar19[lVar29] = (uint)*(byte *)(local_228[0] + lVar29);
    }
    local_34e0 = 0x20;
    local_34d8 = 0;
    local_34c8 = 0;
    local_34d0 = 0;
    local_3440 = (uint *)0x0;
    local_34e8 = 0;
    local_34c0[0] = 0;
    pcVar13 = (char *)0x0;
    cVar2 = s_GuiLook_StaticImage_00fd0bff[0];
    while (cVar2 != '\0') {
      cVar2 = pcVar13[0xfd0c00];
      pcVar13 = pcVar13 + 1;
    }
    local_3598 = lVar11;
    if (pcVar13 == CEGUI::String::npos) {
                    /* try { // try from 00c02ac0 to 00c02ac4 has its CatchHandler @ 00c02feb */
      std::string::string((string *)local_328,"Length for utf8 encoded string can not be \'npos\'",
                          local_67);
      plVar21 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00c02ad8 to 00c02adc has its CatchHandler @ 00c02fd3 */
      std::length_error::length_error(plVar21,(string *)local_328);
      if ((allocator *)(local_328[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_328[0] + -8);
        iVar6 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar6 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_328[0] + -0x18));
        }
      }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00c02b03 to 00c02b07 has its CatchHandler @ 00c02d30 */
      __cxa_throw(plVar21,&std::length_error::typeinfo,std::length_error::~length_error);
    }
    lVar11 = 0;
    pbVar15 = (byte *)"GuiLook/StaticImage";
    pcVar28 = pcVar13;
    while (pcVar28 != (char *)0x0) {
      bVar3 = *pbVar15;
      pcVar27 = pcVar28 + -1;
      pbVar24 = pbVar15 + 1;
      if ((char)bVar3 < '\0') {
        if (bVar3 < 0xe0) {
          pcVar27 = pcVar28 + -2;
          pbVar24 = pbVar15 + 2;
        }
        else if (bVar3 < 0xf0) {
          pcVar27 = pcVar28 + -3;
          pbVar24 = pbVar15 + 3;
        }
        else {
          pcVar27 = pcVar28 + -3;
          pbVar24 = pbVar15 + 4;
        }
      }
      lVar11 = lVar11 + 1;
      pbVar15 = pbVar24;
      pcVar28 = pcVar27;
    }
                    /* try { // try from 00c01d0d to 00c01d11 has its CatchHandler @ 00c02d30 */
    CEGUI::String::grow((ulong)&local_34e8);
    puVar20 = local_3440;
    if (local_34e0 < 0x21) {
      puVar20 = local_34c0;
    }
    if (pcVar13 == (char *)0x0) {
      pcVar28 = (char *)0x0;
      if (s_GuiLook_StaticImage_00fd0bff[0] != '\0') {
        do {
          pcVar13 = pcVar28 + 1;
          pcVar27 = pcVar28 + 0xfd0c00;
          pcVar28 = pcVar13;
        } while (*pcVar27 != '\0');
        bVar30 = pcVar13 != (char *)0x0 && local_34e0 != 0;
        goto LAB_00c01d3f;
      }
    }
    else {
      bVar30 = local_34e0 != 0;
LAB_00c01d3f:
      if (bVar30) {
        pcVar28 = (char *)0x0;
        uVar22 = local_34e0;
        while( true ) {
          bVar3 = pcVar28[0xfd0bff];
          uVar9 = (uint)bVar3;
          iVar6 = (int)pcVar28;
          pcVar28 = (char *)(ulong)(iVar6 + 1);
          if ((char)bVar3 < '\0') {
            uVar9 = (uint)bVar3;
            if (bVar3 < 0xe0) {
              uVar9 = (byte)pcVar28[0xfd0bff] & 0x3f | (uVar9 & 0x1f) << 6;
              pcVar28 = (char *)(ulong)(iVar6 + 2);
            }
            else if (bVar3 < 0xf0) {
              uVar9 = (byte)"GuiLook/StaticImage"[iVar6 + 2] & 0x3f | (uVar9 & 0xf) << 0xc |
                      ((byte)pcVar28[0xfd0bff] & 0x3f) << 6;
              pcVar28 = (char *)(ulong)(iVar6 + 3);
            }
            else {
              pbVar15 = (byte *)(pcVar28 + 0xfd0bff);
              pcVar28 = (char *)(ulong)(iVar6 + 4);
              uVar9 = (*pbVar15 & 0x3f) << 0xc | (byte)"GuiLook/StaticImage"[iVar6 + 3] & 0x3f |
                      (uVar9 & 7) << 0x12 | ((byte)"GuiLook/StaticImage"[iVar6 + 2] & 0x3f) << 6;
            }
          }
          *puVar20 = uVar9;
          uVar22 = uVar22 - 1;
          if ((pcVar13 <= pcVar28) || (uVar22 == 0)) break;
          puVar20 = puVar20 + 1;
        }
      }
    }
    puVar20 = local_3440;
    if (local_34e0 < 0x21) {
      puVar20 = local_34c0;
    }
    puVar20[lVar11] = 0;
    local_34e8 = lVar11;
                    /* try { // try from 00c01e17 to 00c01e1b has its CatchHandler @ 00c02ebd */
    pUVar18 = (UVector2 *)
              CEGUI::WindowManager::createWindow
                        (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,(String *)&local_34e8,
                         (String *)&local_3598);
                    /* try { // try from 00c01e27 to 00c01e2b has its CatchHandler @ 00c02d30 */
    CEGUI::String::~String((String *)&local_34e8);
                    /* try { // try from 00c01e34 to 00c01e38 has its CatchHandler @ 00c02c84 */
    CEGUI::String::~String((String *)&local_3598);
    if ((allocator *)(local_228[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_228[0] + -8);
      iVar6 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar6 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_228[0] + -0x18));
      }
    }
    if ((allocator *)(local_218[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_218[0] + -8);
      iVar6 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar6 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_218[0] + -0x18));
      }
    }
                    /* try { // try from 00c01e75 to 00c01ee0 has its CatchHandler @ 00c033c5 */
    CEGUI::String::~String((String *)&local_3648);
    CEGUI::Window::addChildWindow(*(Window **)(*(long *)(local_3a70 + 0x2790) + 0xb0));
    pUVar18[0x213] = (UVector2)0x0;
    CEGUI::Window::setWantsMultiClickEvents(SUB81(pUVar18,0));
    pUVar18[0x3e2] = (UVector2)0x1;
    CEGUI::EventSet::setMutedState((bool)(SUB81(pUVar18,0) + '8'));
    CEGUI::Window::getPosition();
    CEGUI::Window::setPosition(pUVar18);
    CEGUI::Window::getSize();
                    /* try { // try from 00c01ee7 to 00c01eeb has its CatchHandler @ 00c02e60 */
    CEGUI::Window::setSize(pUVar18);
    *(UVector2 **)(local_3a70 + 0x2cb0) = pUVar18;
    local_3850 = 0x20;
    local_3848 = 0;
    local_3838 = 0;
    local_3840 = 0;
    local_37b0 = (undefined4 *)0x0;
    local_3858 = 0;
    local_3830[0] = 0;
                    /* try { // try from 00c01f55 to 00c01f59 has its CatchHandler @ 00c033c5 */
    CEGUI::String::grow((ulong)&local_3858);
    local_3858 = 0;
    puVar19 = local_37b0;
    if (local_3850 < 0x21) {
      puVar19 = local_3830;
    }
    *puVar19 = 0;
                    /* try { // try from 00c01f9c to 00c01fa0 has its CatchHandler @ 00c02dae */
    std::string::string((string *)local_238,"gui_",&local_40);
                    /* try { // try from 00c01fb1 to 00c01fb5 has its CatchHandler @ 00c02de2 */
    STRINGS::uniqueName((STRINGS *)local_248,(string *)local_238);
    local_37a0 = 0x20;
    local_3798 = 0;
    local_3788 = 0;
    local_3790 = 0;
    local_3700 = (undefined4 *)0x0;
    local_37a8 = 0;
    local_3780[0] = 0;
    lVar11 = *(long *)(local_248[0] + -0x18);
                    /* try { // try from 00c02020 to 00c02024 has its CatchHandler @ 00c02dc3 */
    CEGUI::String::grow((ulong)&local_37a8);
    puVar19 = local_3700;
    if (local_37a0 < 0x21) {
      puVar19 = local_3780;
    }
    puVar19[lVar11] = 0;
    if (lVar11 != 0) {
      lVar29 = lVar11;
      do {
        lVar29 = lVar29 + -1;
        puVar19 = local_3780;
        if (0x20 < local_37a0) {
          puVar19 = local_3700;
        }
        puVar19[lVar29] = (uint)*(byte *)(local_248[0] + lVar29);
      } while (lVar29 != 0);
    }
    local_36f0 = 0x20;
    local_36e8 = 0;
    local_36d8 = 0;
    local_36e0 = 0;
    local_3650 = (uint *)0x0;
    local_36f8 = 0;
    local_36d0[0] = 0;
    pcVar13 = (char *)0x0;
    cVar2 = s_GuiLook_StaticImage_00fd0bff[0];
    while (cVar2 != '\0') {
      cVar2 = pcVar13[0xfd0c00];
      pcVar13 = pcVar13 + 1;
    }
    local_37a8 = lVar11;
    if (pcVar13 == CEGUI::String::npos) {
                    /* try { // try from 00c02b20 to 00c02b24 has its CatchHandler @ 00c0337f */
      std::string::string((string *)local_338,"Length for utf8 encoded string can not be \'npos\'",
                          local_6b);
      plVar21 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00c02b38 to 00c02b3c has its CatchHandler @ 00c03367 */
      std::length_error::length_error(plVar21,(string *)local_338);
      if ((allocator *)(local_338[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_338[0] + -8);
        iVar6 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar6 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_338[0] + -0x18));
        }
      }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00c02b63 to 00c02b67 has its CatchHandler @ 00c02f92 */
      __cxa_throw(plVar21,&std::length_error::typeinfo,std::length_error::~length_error);
    }
    lVar11 = 0;
    pcVar28 = pcVar13;
    pbVar15 = (byte *)"GuiLook/StaticImage";
    while (pcVar28 != (char *)0x0) {
      bVar3 = *pbVar15;
      pcVar27 = pcVar28 + -1;
      pbVar24 = pbVar15 + 1;
      if ((char)bVar3 < '\0') {
        if (bVar3 < 0xe0) {
          pcVar27 = pcVar28 + -2;
          pbVar24 = pbVar15 + 2;
        }
        else if (bVar3 < 0xf0) {
          pcVar27 = pcVar28 + -3;
          pbVar24 = pbVar15 + 3;
        }
        else {
          pcVar27 = pcVar28 + -3;
          pbVar24 = pbVar15 + 4;
        }
      }
      lVar11 = lVar11 + 1;
      pcVar28 = pcVar27;
      pbVar15 = pbVar24;
    }
                    /* try { // try from 00c02165 to 00c02169 has its CatchHandler @ 00c02f92 */
    CEGUI::String::grow((ulong)&local_36f8);
    puVar20 = local_3650;
    if (local_36f0 < 0x21) {
      puVar20 = local_36d0;
    }
    if (pcVar13 == (char *)0x0) {
      pcVar28 = (char *)0x0;
      if (s_GuiLook_StaticImage_00fd0bff[0] != '\0') {
        do {
          pcVar13 = pcVar28 + 1;
          pcVar27 = pcVar28 + 0xfd0c00;
          pcVar28 = pcVar13;
        } while (*pcVar27 != '\0');
        bVar30 = pcVar13 != (char *)0x0 && local_36f0 != 0;
        goto LAB_00c021b5;
      }
    }
    else {
      bVar30 = local_36f0 != 0;
LAB_00c021b5:
      if (bVar30) {
        pcVar28 = (char *)0x0;
        uVar22 = local_36f0;
        while( true ) {
          bVar3 = pcVar28[0xfd0bff];
          uVar9 = (uint)bVar3;
          iVar6 = (int)pcVar28;
          pcVar28 = (char *)(ulong)(iVar6 + 1);
          if ((char)bVar3 < '\0') {
            uVar9 = (uint)bVar3;
            if (bVar3 < 0xe0) {
              uVar9 = (byte)pcVar28[0xfd0bff] & 0x3f | (uVar9 & 0x1f) << 6;
              pcVar28 = (char *)(ulong)(iVar6 + 2);
            }
            else if (bVar3 < 0xf0) {
              uVar9 = (byte)"GuiLook/StaticImage"[iVar6 + 2] & 0x3f | (uVar9 & 0xf) << 0xc |
                      ((byte)pcVar28[0xfd0bff] & 0x3f) << 6;
              pcVar28 = (char *)(ulong)(iVar6 + 3);
            }
            else {
              pbVar15 = (byte *)(pcVar28 + 0xfd0bff);
              pcVar28 = (char *)(ulong)(iVar6 + 4);
              uVar9 = (*pbVar15 & 0x3f) << 0xc | (byte)"GuiLook/StaticImage"[iVar6 + 3] & 0x3f |
                      (uVar9 & 7) << 0x12 | ((byte)"GuiLook/StaticImage"[iVar6 + 2] & 0x3f) << 6;
            }
          }
          *puVar20 = uVar9;
          uVar22 = uVar22 - 1;
          if ((pcVar13 <= pcVar28) || (uVar22 == 0)) break;
          puVar20 = puVar20 + 1;
        }
      }
    }
    puVar20 = local_3650;
    if (local_36f0 < 0x21) {
      puVar20 = local_36d0;
    }
    puVar20[lVar11] = 0;
    local_36f8 = lVar11;
                    /* try { // try from 00c0228d to 00c02291 has its CatchHandler @ 00c0320d */
    pUVar18 = (UVector2 *)
              CEGUI::WindowManager::createWindow
                        (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,(String *)&local_36f8,
                         (String *)&local_37a8);
                    /* try { // try from 00c0229d to 00c022a1 has its CatchHandler @ 00c02f92 */
    CEGUI::String::~String((String *)&local_36f8);
                    /* try { // try from 00c022aa to 00c022ae has its CatchHandler @ 00c02dc3 */
    CEGUI::String::~String((String *)&local_37a8);
    if ((allocator *)(local_248[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_248[0] + -8);
      iVar6 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar6 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_248[0] + -0x18));
      }
    }
    if ((allocator *)(local_238[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_238[0] + -8);
      iVar6 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar6 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_238[0] + -0x18));
      }
    }
                    /* try { // try from 00c022eb to 00c02347 has its CatchHandler @ 00c033c5 */
    CEGUI::String::~String((String *)&local_3858);
    CEGUI::Window::addChildWindow(*(Window **)(this + 0x38));
    pUVar18[0x213] = (UVector2)0x0;
    CEGUI::Window::setWantsMultiClickEvents(SUB81(pUVar18,0));
    pUVar18[0x3e2] = (UVector2)0x1;
    CEGUI::EventSet::setMutedState((bool)(SUB81(pUVar18,0) + '8'));
    CEGUI::Window::getPosition();
    CEGUI::Window::setPosition(pUVar18);
    CEGUI::Window::getSize();
                    /* try { // try from 00c0234e to 00c02352 has its CatchHandler @ 00c031ab */
    CEGUI::Window::setSize(pUVar18);
    *(UVector2 **)(local_3a70 + 0x2f40) = pUVar18;
    local_3a60 = 0x20;
    local_3a58 = 0;
    local_3a48 = 0;
    local_3a50 = 0;
    local_39c0 = (undefined4 *)0x0;
    local_3a68 = 0;
    local_3a40[0] = 0;
                    /* try { // try from 00c023a7 to 00c023ab has its CatchHandler @ 00c033c5 */
    CEGUI::String::grow((ulong)&local_3a68);
    local_3a68 = 0;
    puVar19 = local_39c0;
    if (local_3a60 < 0x21) {
      puVar19 = local_3a40;
    }
    *puVar19 = 0;
                    /* try { // try from 00c023e5 to 00c023e9 has its CatchHandler @ 00c02de7 */
    std::string::string((string *)local_258,"gui_",&local_41);
                    /* try { // try from 00c023fa to 00c023fe has its CatchHandler @ 00c0301c */
    STRINGS::uniqueName((STRINGS *)local_268,(string *)local_258);
    local_39b0 = 0x20;
    local_39a8 = 0;
    local_3998 = 0;
    local_39a0 = 0;
    local_3910 = (undefined4 *)0x0;
    local_39b8 = 0;
    local_3990[0] = 0;
    lVar11 = *(long *)(local_268[0] + -0x18);
                    /* try { // try from 00c02469 to 00c0246d has its CatchHandler @ 00c03014 */
    CEGUI::String::grow((ulong)&local_39b8);
    puVar19 = local_3910;
    if (local_39b0 < 0x21) {
      puVar19 = local_3990;
    }
    puVar19[lVar11] = 0;
    if (lVar11 != 0) {
      lVar29 = lVar11;
      do {
        lVar29 = lVar29 + -1;
        puVar19 = local_3990;
        if (0x20 < local_39b0) {
          puVar19 = local_3910;
        }
        puVar19[lVar29] = (uint)*(byte *)(local_268[0] + lVar29);
      } while (lVar29 != 0);
    }
    local_3900 = 0x20;
    local_38f8 = 0;
    local_38e8 = 0;
    local_38f0 = 0;
    local_3860 = (uint *)0x0;
    local_3908 = 0;
    local_38e0[0] = 0;
    pcVar13 = (char *)0x0;
    cVar2 = s_GuiLook_StaticImage_00fd0bff[0];
    while (cVar2 != '\0') {
      cVar2 = pcVar13[0xfd0c00];
      pcVar13 = pcVar13 + 1;
    }
    local_39b8 = lVar11;
    if (pcVar13 == CEGUI::String::npos) {
                    /* try { // try from 00c02b80 to 00c02b84 has its CatchHandler @ 00c03284 */
      std::string::string((string *)local_348,"Length for utf8 encoded string can not be \'npos\'",
                          local_6f);
      plVar21 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00c02b98 to 00c02b9c has its CatchHandler @ 00c0326c */
      std::length_error::length_error(plVar21,(string *)local_348);
      if ((allocator *)(local_348[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_348[0] + -8);
        iVar6 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar6 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_348[0] + -0x18));
        }
      }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00c02bc3 to 00c02bc7 has its CatchHandler @ 00c02dec */
      __cxa_throw(plVar21,&std::length_error::typeinfo,std::length_error::~length_error);
    }
    lVar11 = 0;
    pcVar28 = pcVar13;
    pbVar15 = (byte *)"GuiLook/StaticImage";
    while (pcVar28 != (char *)0x0) {
      bVar3 = *pbVar15;
      pcVar27 = pcVar28 + -1;
      pbVar24 = pbVar15 + 1;
      if ((char)bVar3 < '\0') {
        if (bVar3 < 0xe0) {
          pcVar27 = pcVar28 + -2;
          pbVar24 = pbVar15 + 2;
        }
        else if (bVar3 < 0xf0) {
          pcVar27 = pcVar28 + -3;
          pbVar24 = pbVar15 + 3;
        }
        else {
          pcVar27 = pcVar28 + -3;
          pbVar24 = pbVar15 + 4;
        }
      }
      lVar11 = lVar11 + 1;
      pcVar28 = pcVar27;
      pbVar15 = pbVar24;
    }
                    /* try { // try from 00c0260c to 00c02610 has its CatchHandler @ 00c02dec */
    CEGUI::String::grow((ulong)&local_3908);
    puVar20 = local_38e0;
    if (0x20 < local_3900) {
      puVar20 = local_3860;
    }
    if (pcVar13 == (char *)0x0) {
      pcVar28 = (char *)0x0;
      if (s_GuiLook_StaticImage_00fd0bff[0] != '\0') {
        do {
          pcVar13 = pcVar28 + 1;
          pcVar27 = pcVar28 + 0xfd0c00;
          pcVar28 = pcVar13;
        } while (*pcVar27 != '\0');
        bVar30 = pcVar13 != (char *)0x0 && local_3900 != 0;
        goto LAB_00c0263a;
      }
    }
    else {
      bVar30 = local_3900 != 0;
LAB_00c0263a:
      if (bVar30) {
        pcVar28 = (char *)0x0;
        uVar22 = local_3900;
        while( true ) {
          bVar3 = pcVar28[0xfd0bff];
          uVar9 = (uint)bVar3;
          iVar6 = (int)pcVar28;
          pcVar28 = (char *)(ulong)(iVar6 + 1);
          if ((char)bVar3 < '\0') {
            uVar9 = (uint)bVar3;
            if (bVar3 < 0xe0) {
              uVar9 = (byte)pcVar28[0xfd0bff] & 0x3f | (uVar9 & 0x1f) << 6;
              pcVar28 = (char *)(ulong)(iVar6 + 2);
            }
            else if (bVar3 < 0xf0) {
              uVar9 = (byte)"GuiLook/StaticImage"[iVar6 + 2] & 0x3f | (uVar9 & 0xf) << 0xc |
                      ((byte)pcVar28[0xfd0bff] & 0x3f) << 6;
              pcVar28 = (char *)(ulong)(iVar6 + 3);
            }
            else {
              pbVar15 = (byte *)(pcVar28 + 0xfd0bff);
              pcVar28 = (char *)(ulong)(iVar6 + 4);
              uVar9 = (*pbVar15 & 0x3f) << 0xc | (byte)"GuiLook/StaticImage"[iVar6 + 3] & 0x3f |
                      (uVar9 & 7) << 0x12 | ((byte)"GuiLook/StaticImage"[iVar6 + 2] & 0x3f) << 6;
            }
          }
          *puVar20 = uVar9;
          uVar22 = uVar22 - 1;
          if ((pcVar13 <= pcVar28) || (uVar22 == 0)) break;
          puVar20 = puVar20 + 1;
        }
      }
    }
    puVar20 = local_38e0;
    if (0x20 < local_3900) {
      puVar20 = local_3860;
    }
    puVar20[lVar11] = 0;
    local_3908 = lVar11;
                    /* try { // try from 00c02706 to 00c0270a has its CatchHandler @ 00c02d6d */
    pUVar18 = (UVector2 *)
              CEGUI::WindowManager::createWindow
                        (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,(String *)&local_3908,
                         (String *)&local_39b8);
                    /* try { // try from 00c02711 to 00c02715 has its CatchHandler @ 00c02dec */
    CEGUI::String::~String((String *)&local_3908);
                    /* try { // try from 00c0271e to 00c02722 has its CatchHandler @ 00c03014 */
    CEGUI::String::~String((String *)&local_39b8);
    if ((allocator *)(local_268[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_268[0] + -8);
      iVar6 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar6 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_268[0] + -0x18));
      }
    }
    if ((allocator *)(local_258[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_258[0] + -8);
      iVar6 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar6 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_258[0] + -0x18));
      }
    }
                    /* try { // try from 00c0275c to 00c027d9 has its CatchHandler @ 00c033c5 */
    CEGUI::String::~String((String *)&local_3a68);
    CEGUI::Window::addChildWindow(*(Window **)(*(long *)(local_3a70 + 0x2790) + 0xb0));
    pUVar18[0x213] = (UVector2)0x0;
    bVar30 = SUB81(pUVar18,0);
    CEGUI::Window::setWantsMultiClickEvents(bVar30);
    pUVar18[0x3e2] = (UVector2)0x1;
    CEGUI::EventSet::setMutedState((bool)(bVar30 + '8'));
    CEGUI::Window::getPosition();
    CEGUI::Window::setPosition(pUVar18);
    CEGUI::Window::getSize();
                    /* try { // try from 00c027e0 to 00c027e4 has its CatchHandler @ 00c02f14 */
    CEGUI::Window::setSize(pUVar18);
                    /* try { // try from 00c027ed to 00c027f1 has its CatchHandler @ 00c033c5 */
    CEGUI::Window::setAlwaysOnTop(bVar30);
    *(UVector2 **)(local_3a70 + 0x2a20) = pUVar18;
    local_3a84 = local_3a84 + 1;
    local_3a70 = local_3a70 + 8;
    if (local_3a84 == 0x40) {
      if ((allocator *)(local_558 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
      {
        LOCK();
        piVar1 = (int *)(local_558 + -8);
        iVar6 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar6 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_558 + -0x18));
        }
      }
      if ((allocator *)(local_568 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
         ) {
        LOCK();
        piVar1 = (int *)(local_568 + -8);
        iVar6 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar6 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_568 + -0x18));
        }
      }
      if ((allocator *)(local_570 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
      {
        LOCK();
        piVar1 = (int *)(local_570 + -8);
        iVar6 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar6 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_570 + -0x18));
        }
      }
      if ((allocator *)(local_578 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
      {
        LOCK();
        piVar1 = (int *)(local_578 + -8);
        iVar6 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar6 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_578 + -0x18));
        }
      }
      if (local_528 != (void *)0x0) {
        Ogre::NedAllocImpl::deallocBytes(local_528);
      }
      return;
    }
  } while( true );
}

/* address=00c03f40
   symbol=CStashMenu::CStashMenu */

/* WARNING: Removing unreachable block (ram,0x00c041e6) */
/* WARNING: Removing unreachable block (ram,0x00c041c0) */
/* CStashMenu::CStashMenu(CGameUI&, CSettings&, Ogre::RenderWindow*, Ogre::SceneManager*,
   CEGUI::Window*, CResourceManager*) */

void __thiscall
CStashMenu::CStashMenu
          (CStashMenu *this,CGameUI *param_1,CSettings *param_2,RenderWindow *param_3,
          SceneManager *param_4,Window *param_5,CResourceManager *param_6)

{
  int *piVar1;
  int iVar2;
  CSoundBankDataInformation *this_00;
  CSoundManager *pCVar3;
  long lVar4;
  CSoundBank *this_01;
  long local_58 [2];
  long local_48;
  allocator local_3a;
  allocator local_39 [9];

  CRunicCore::CRunicCore((CRunicCore *)this);
  *(undefined ***)this = &PTR__CStashMenu_00ff1650;
  *(undefined ***)(this + 0x10) = &PTR__CStashMenu_00ff1700;
  *(Window **)(this + 0x18) = param_5;
  *(undefined8 *)(this + 0x50) = 0;
  *(undefined8 *)(this + 0x58) = 0;
  this[0x60] = (CStashMenu)0x0;
  this[0x61] = (CStashMenu)0x1;
  this[0x62] = (CStashMenu)0x0;
  *(CSettings **)(this + 0x68) = param_2;
  *(CGameUI **)(this + 0x70) = param_1;
  *(SceneManager **)(this + 0x78) = param_4;
  *(RenderWindow **)(this + 0x80) = param_3;
  *(undefined8 *)(this + 0x90) = 0;
  *(CResourceManager **)(this + 0x98) = param_6;
  *(undefined4 *)(this + 0xa0) = 0;
  *(undefined8 *)(this + 0xa8) = 0;
  *(undefined4 *)(this + 0x33f8) = 0xffffffff;
  *(undefined4 *)(this + 0x33fc) = 0xffffffff;
  *(undefined4 *)(this + 0x3400) = 0xffffffff;
  *(undefined4 *)(this + 0x3404) = 0xffffffff;
  *(undefined8 *)(this + 0x3408) = 0;
  this[0x3420] = (CStashMenu)0x0;
  this[0x3421] = (CStashMenu)0x0;
                    /* try { // try from 00c04028 to 00c0404f has its CatchHandler @ 00c041e2 */
  lVar4 = CMasterResourceManager::getSingleton();
  this_00 = *(CSoundBankDataInformation **)(lVar4 + 0x100);
  lVar4 = CMasterResourceManager::getSingleton();
  pCVar3 = *(CSoundManager **)(lVar4 + 0x98);
  this_01 = (CSoundBank *)Ogre::NedAllocImpl::allocBytes(0xd0,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00c0405b to 00c0405f has its CatchHandler @ 00c0419d */
  CSoundBank::CSoundBank(this_01,pCVar3,false);
  *(CSoundBank **)(this + 0xa8) = this_01;
                    /* try { // try from 00c04079 to 00c0407d has its CatchHandler @ 00c041d8 */
  std::wstring::wstring((wstring_conflict *)&local_48,L"STATSOPEN",local_39);
                    /* try { // try from 00c04084 to 00c04088 has its CatchHandler @ 00c041cb */
  lVar4 = CSoundBankDataInformation::getSoundDataObject(this_00,(wstring_conflict *)&local_48);
  if ((allocator *)(local_48 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_48 + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_48 + -0x18));
    }
  }
  if (lVar4 != 0) {
                    /* try { // try from 00c040b4 to 00c040b8 has its CatchHandler @ 00c041e2 */
    CSoundBank::addSample(*(CSoundBank **)(this + 0xa8),0x16,*(longlong *)(lVar4 + 0x20));
  }
                    /* try { // try from 00c040cb to 00c040cf has its CatchHandler @ 00c041dd */
  std::wstring::wstring((wstring_conflict *)local_58,L"STATSCLOSE",&local_3a);
                    /* try { // try from 00c040d6 to 00c040da has its CatchHandler @ 00c041e4 */
  lVar4 = CSoundBankDataInformation::getSoundDataObject(this_00,(wstring_conflict *)local_58);
  if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_58[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
    }
  }
  if (lVar4 != 0) {
                    /* try { // try from 00c04103 to 00c0410f has its CatchHandler @ 00c041e2 */
    CSoundBank::addSample(*(CSoundBank **)(this + 0xa8),0x42,*(longlong *)(lVar4 + 0x20));
  }
  createMenus(this);
  return;
}

/* address=00c04200
   symbol=CStashMenu::isRight */

/* CStashMenu::isRight() */

undefined8 CStashMenu::isRight(void)

{
  return 0;
}

/* address=00c04210
   symbol=CStashMenu::open */

/* CStashMenu::open() */

byte __thiscall CStashMenu::open(CStashMenu *this)

{
  byte bVar1;

  bVar1 = 1;
  if (this[0x60] == (CStashMenu)0x0) {
    bVar1 = (byte)this[0x61] ^ 1;
  }
  return bVar1;
}

/* address=00c04230
   symbol=CStashMenu::openPartial */

/* CStashMenu::openPartial() */

CStashMenu __thiscall CStashMenu::openPartial(CStashMenu *this)

{
  return this[0x60];
}

/* address=00c04240
   symbol=CStashMenu::screenEdge */

/* CStashMenu::screenEdge() */

undefined4 __thiscall CStashMenu::screenEdge(CStashMenu *this)

{
  return *(undefined4 *)(this + 0xa0);
}

/* address=00c04250
   symbol=CStashMenu::getOwner */

/* CStashMenu::getOwner() */

undefined8 __thiscall CStashMenu::getOwner(CStashMenu *this)

{
  return *(undefined8 *)(this + 0x50);
}

/* export-summary functions=44 failures=0 */
