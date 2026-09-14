/* Targeted Ghidra class export.
   namespace=CMerchantMenu
   Treat pseudocode as navigation evidence. */


/* address=00b60f80
   symbol=CMerchantMenu::equipmentPickedUp */

/* non-virtual thunk to CMerchantMenu::equipmentPickedUp(CEquipment*) */

void __thiscall CMerchantMenu::equipmentPickedUp(CMerchantMenu *this,CEquipment *param_1)

{
  equipmentPickedUp((CEquipment *)(this + -0x10));
  return;
}

/* address=00b60f90
   symbol=CMerchantMenu::equipmentPickedUp */

/* CMerchantMenu::equipmentPickedUp(CEquipment*) */

void CMerchantMenu::equipmentPickedUp(CEquipment *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x00b60f97. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)param_1 + 0x48))();
  return;
}

/* address=00b60fa0
   symbol=CMerchantMenu::equipmentDropped */

/* non-virtual thunk to CMerchantMenu::equipmentDropped(CEquipment*) */

void __thiscall CMerchantMenu::equipmentDropped(CMerchantMenu *this,CEquipment *param_1)

{
  equipmentDropped((CEquipment *)(this + -0x10));
  return;
}

/* address=00b60fb0
   symbol=CMerchantMenu::equipmentDropped */

/* CMerchantMenu::equipmentDropped(CEquipment*) */

void CMerchantMenu::equipmentDropped(CEquipment *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x00b60fb7. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)param_1 + 0x48))();
  return;
}

/* address=00b60fc0
   symbol=CMerchantMenu::equipmentEquipped */

/* non-virtual thunk to CMerchantMenu::equipmentEquipped(CEquipment*) */

void __thiscall CMerchantMenu::equipmentEquipped(CMerchantMenu *this,CEquipment *param_1)

{
  equipmentEquipped((CEquipment *)(this + -0x10));
  return;
}

/* address=00b60fd0
   symbol=CMerchantMenu::equipmentEquipped */

/* CMerchantMenu::equipmentEquipped(CEquipment*) */

void CMerchantMenu::equipmentEquipped(CEquipment *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x00b60fd7. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)param_1 + 0x48))();
  return;
}

/* address=00b60fe0
   symbol=CMerchantMenu::equipmentUnequipped */

/* non-virtual thunk to CMerchantMenu::equipmentUnequipped(CEquipment*) */

void __thiscall CMerchantMenu::equipmentUnequipped(CMerchantMenu *this,CEquipment *param_1)

{
  equipmentUnequipped((CEquipment *)(this + -0x10));
  return;
}

/* address=00b60ff0
   symbol=CMerchantMenu::equipmentUnequipped */

/* CMerchantMenu::equipmentUnequipped(CEquipment*) */

void CMerchantMenu::equipmentUnequipped(CEquipment *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x00b60ff7. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)param_1 + 0x48))();
  return;
}

/* address=00b61000
   symbol=CMerchantMenu::equipmentUsed */

/* non-virtual thunk to CMerchantMenu::equipmentUsed(CEquipment*) */

void __thiscall CMerchantMenu::equipmentUsed(CMerchantMenu *this,CEquipment *param_1)

{
  equipmentUsed((CEquipment *)(this + -0x10));
  return;
}

/* address=00b61010
   symbol=CMerchantMenu::equipmentUsed */

/* CMerchantMenu::equipmentUsed(CEquipment*) */

void CMerchantMenu::equipmentUsed(CEquipment *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x00b61017. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)param_1 + 0x48))();
  return;
}

/* address=00b61020
   symbol=CMerchantMenu::inventoryDestroyed */

/* non-virtual thunk to CMerchantMenu::inventoryDestroyed() */

void __thiscall CMerchantMenu::inventoryDestroyed(CMerchantMenu *this)

{
  inventoryDestroyed();
  return;
}

/* address=00b61030
   symbol=CMerchantMenu::inventoryDestroyed */

/* CMerchantMenu::inventoryDestroyed() */

void CMerchantMenu::inventoryDestroyed(void)

{
  return;
}

/* address=00b61040
   symbol=CMerchantMenu::handle_ItemClick */

/* CMerchantMenu::handle_ItemClick(CEGUI::EventArgs const&) */

undefined8 __thiscall CMerchantMenu::handle_ItemClick(CMerchantMenu *this,EventArgs *param_1)

{
  undefined4 uVar1;

  if ((*(long *)(param_1 + 0x10) != 0) && (this[0x60] != (CMerchantMenu)0x0)) {
    uVar1 = **(undefined4 **)(*(long *)(param_1 + 0x10) + 0x1d8);
    if (*(int *)(param_1 + 0x28) == 0) {
      *(undefined4 *)(this + 0x3430) = uVar1;
      return 1;
    }
    if (*(int *)(param_1 + 0x28) == 1) {
      *(undefined4 *)(this + 0x3434) = uVar1;
      return 1;
    }
  }
  return 1;
}

/* address=00b61090
   symbol=CMerchantMenu::handle_MouseThrough */

/* CMerchantMenu::handle_MouseThrough(CEGUI::EventArgs const&) */

undefined8 CMerchantMenu::handle_MouseThrough(EventArgs *param_1)

{
  param_1[0x3450] = (EventArgs)0x0;
  return 1;
}

/* address=00b610a0
   symbol=CMerchantMenu::handle_onClick */

/* CMerchantMenu::handle_onClick(CEGUI::EventArgs const&) */

undefined8 __thiscall CMerchantMenu::handle_onClick(CMerchantMenu *this,EventArgs *param_1)

{
  undefined8 uVar1;

  if ((*(int *)(param_1 + 0x28) == 0) && (*(long *)(param_1 + 0x10) != 0)) {
                    /* WARNING: Could not recover jumptable at 0x00b610c3. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(*(long *)this + 0x98))
                      (this,**(undefined4 **)(*(long *)(param_1 + 0x10) + 0x1d8));
    return uVar1;
  }
  return 1;
}

/* address=00b610d0
   symbol=CMerchantMenu::setTab */

/* CMerchantMenu::setTab(int) */

void __thiscall CMerchantMenu::setTab(CMerchantMenu *this,int param_1)

{
                    /* WARNING: Could not recover jumptable at 0x00b610dd. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)this + 0x98))(this,param_1 + 0x40);
  return;
}

/* address=00b610e0
   symbol=CMerchantMenu::setPetTab */

/* CMerchantMenu::setPetTab(int) */

void __thiscall CMerchantMenu::setPetTab(CMerchantMenu *this,int param_1)

{
                    /* WARNING: Could not recover jumptable at 0x00b610ed. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)this + 0x98))(this,param_1 + 0xe);
  return;
}

/* address=00b610f0
   symbol=CMerchantMenu::handle_PetItemClick */

/* CMerchantMenu::handle_PetItemClick(CEGUI::EventArgs const&) */

undefined8 __thiscall CMerchantMenu::handle_PetItemClick(CMerchantMenu *this,EventArgs *param_1)

{
  undefined4 uVar1;

  if (*(long *)(param_1 + 0x10) != 0) {
    uVar1 = **(undefined4 **)(*(long *)(param_1 + 0x10) + 0x1d8);
    if (*(int *)(param_1 + 0x28) == 0) {
      *(undefined4 *)(this + 0x3428) = uVar1;
      return 1;
    }
    if (*(int *)(param_1 + 0x28) == 1) {
      *(undefined4 *)(this + 0x342c) = uVar1;
      return 1;
    }
  }
  return 1;
}

/* address=00b61140
   symbol=CMerchantMenu::handle_PetMouseOut */

/* CMerchantMenu::handle_PetMouseOut(CEGUI::EventArgs const&) */

undefined8 __thiscall CMerchantMenu::handle_PetMouseOut(CMerchantMenu *this,EventArgs *param_1)

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
     lVar3 == *(long *)(this + 0x3438))) {
    *(undefined8 *)(this + 0x3438) = 0;
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

/* address=00b611f0
   symbol=CMerchantMenu::handle_MouseOut */

/* CMerchantMenu::handle_MouseOut(CEGUI::EventArgs const&) */

undefined8 __thiscall CMerchantMenu::handle_MouseOut(CMerchantMenu *this,EventArgs *param_1)

{
  char cVar1;
  long lVar2;

  if (((*(long *)(param_1 + 0x10) != 0) && (*(long *)(this + 0x50) != 0)) &&
     (lVar2 = CInventory::getEquipmentInSlot
                        (*(CInventory **)(*(long *)(this + 0x50) + 0x490),
                         **(uint **)(*(long *)(param_1 + 0x10) + 0x1d8)),
     lVar2 == *(long *)(this + 0x3438))) {
    *(undefined8 *)(this + 0x3438) = 0;
    if ((*(CBaseUnit **)(*(long *)(this + 0x70) + 0xb8) != (CBaseUnit *)0x0) &&
       (cVar1 = CBaseUnit::ISA(*(CBaseUnit **)(*(long *)(this + 0x70) + 0xb8),0x78), cVar1 != '\0'))
    {
      return 1;
    }
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x30),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x38),0));
  }
  return 1;
}

/* address=00b61280
   symbol=CMerchantMenu::onClick */

/* CMerchantMenu::onClick(ELayoutFunction) */

undefined8 __thiscall CMerchantMenu::onClick(CMerchantMenu *this,undefined4 param_2)

{
  undefined1 uVar1;

  if (this[0x60] == (CMerchantMenu)0x0) {
switchD_00b612a2_caseD_11:
    return 1;
  }
  switch(param_2) {
  case 0xe:
    *(undefined4 *)(this + 0x3458) = 0;
    CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x33e0),0));
    CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x33e8),0));
    CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x33f0),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x33c8),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x33d0),0));
    uVar1 = (undefined1)*(undefined8 *)(this + 0x33d8);
    goto LAB_00b61385;
  case 0xf:
    *(undefined4 *)(this + 0x3458) = 1;
    CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x33e0),0));
    CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x33e8),0));
    CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x33f0),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x33c8),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x33d0),0));
    uVar1 = (undefined1)*(undefined8 *)(this + 0x33d8);
    goto LAB_00b61385;
  case 0x10:
    *(undefined4 *)(this + 0x3458) = 2;
    CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x33e0),0));
    CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x33e8),0));
    CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x33f0),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x33c8),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x33d0),0));
    uVar1 = (undefined1)*(undefined8 *)(this + 0x33d8);
    goto LAB_00b6130a;
  default:
    goto switchD_00b612a2_caseD_11;
  case 0x40:
    *(undefined4 *)(this + 0x3454) = 0;
    CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x3420),0));
    CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x3410),0));
    CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x3418),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x3408),0));
    uVar1 = (undefined1)*(undefined8 *)(this + 0x33f8);
    break;
  case 0x41:
    *(undefined4 *)(this + 0x3454) = 1;
    CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x3420),0));
    CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x3410),0));
    CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x3418),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x3408),0));
    uVar1 = (undefined1)*(undefined8 *)(this + 0x33f8);
    break;
  case 0x42:
    *(undefined4 *)(this + 0x3454) = 2;
    CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x3420),0));
    CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x3410),0));
    CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x3418),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x3408),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x33f8),0));
    uVar1 = (undefined1)*(undefined8 *)(this + 0x3400);
LAB_00b6130a:
    CEGUI::Window::setVisible((bool)uVar1);
    (**(code **)(*(long *)this + 0x48))(this);
    return 1;
  }
  CEGUI::Window::setVisible((bool)uVar1);
  uVar1 = (undefined1)*(undefined8 *)(this + 0x3400);
LAB_00b61385:
  CEGUI::Window::setVisible((bool)uVar1);
  (**(code **)(*(long *)this + 0x48))(this);
  return 1;
}

/* address=00b61530
   symbol=CMerchantMenu::processInput */

/* CMerchantMenu::processInput(void*, float, bool) */

bool CMerchantMenu::processInput(void *param_1,float param_2,bool param_3)

{
  CBaseUnit *pCVar1;
  char cVar2;
  char in_DL;
  bool bVar3;

  if (in_DL == '\0') {
    *(undefined8 *)((long)param_1 + 0x3438) = 0;
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
    if (*(long *)((long)param_1 + 0x3438) != 0) {
      if (*(char *)(*(long *)((long)param_1 + 0x3438) + 0x198) == '\0') goto LAB_00b615bb;
      *(undefined8 *)((long)param_1 + 0x3438) = 0;
    }
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)((long)param_1 + 0x30),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)((long)param_1 + 0x38),0));
    cVar2 = *(char *)((long)param_1 + 0x3450);
  }
  else {
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)((long)param_1 + 0x38),0));
    CEGUI::Window::moveToFront();
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)((long)param_1 + 0x30),0));
    CEGUI::Window::moveToFront();
LAB_00b615bb:
    cVar2 = *(char *)((long)param_1 + 0x3450);
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
  *(undefined4 *)((long)param_1 + 0x3430) = 0xffffffff;
  *(undefined4 *)((long)param_1 + 0x3434) = 0xffffffff;
  *(undefined4 *)((long)param_1 + 0x3428) = 0xffffffff;
  *(undefined4 *)((long)param_1 + 0x342c) = 0xffffffff;
  return !bVar3;
}

/* address=00b61740
   symbol=CMerchantMenu::setPlayer */

/* CMerchantMenu::setPlayer(CCharacter*) */

void __thiscall CMerchantMenu::setPlayer(CMerchantMenu *this,CCharacter *param_1)

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

/* address=00b617e0
   symbol=CMerchantMenu::setOwner */

/* CMerchantMenu::setOwner(CCharacter*) */

void __thiscall CMerchantMenu::setOwner(CMerchantMenu *this,CCharacter *param_1)

{
  long *plVar1;
  CCharacter *pCVar2;
  long lVar3;

  pCVar2 = param_1;
  if (*(CCharacter **)(this + 0x50) != param_1) {
    (**(code **)(*(long *)this + 0x90))();
    pCVar2 = *(CCharacter **)(this + 0x50);
  }
  if (pCVar2 != (CCharacter *)0x0) {
    CInventory::removeListener(*(CInventory **)(pCVar2 + 0x490),(iInventoryListener *)(this + 0x10))
    ;
  }
  *(CCharacter **)(this + 0x50) = param_1;
  if (param_1 != (CCharacter *)0x0) {
    CInventory::addListener(*(CInventory **)(param_1 + 0x490),(iInventoryListener *)(this + 0x10));
  }
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

/* address=00b68400
   symbol=CMerchantMenu::_GLOBAL__I_CMerchantMenu */

/* CMerchantMenu::CMerchantMenu(CGameUI&, CSettings&, Ogre::RenderWindow*, Ogre::SceneManager*,
   CEGUI::Window*, CResourceManager*) */

void CMerchantMenu::_GLOBAL__I_CMerchantMenu(void)

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
  std::wstring::wstring((wstring_conflict *)&DAT_014c79a8,L"ITEM",&aStack_1c6);
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
  std::wstring::wstring((wstring_conflict *)&DAT_014c85d8,L"ABOVE",&aStack_55);
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

/* address=00b68410
   symbol=CMerchantMenu::~CMerchantMenu */

/* CMerchantMenu::~CMerchantMenu() */

void __thiscall CMerchantMenu::~CMerchantMenu(CMerchantMenu *this)

{
  *(undefined ***)this = &PTR__CMerchantMenu_00ff0110;
  *(undefined ***)(this + 0x10) = &PTR__CMerchantMenu_00ff01c0;
                    /* try { // try from 00b6842a to 00b68467 has its CatchHandler @ 00b684ac */
  setOwner(this,(CCharacter *)0x0);
  setPlayer(this,(CCharacter *)0x0);
  if (*(long **)(this + 0x90) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x90) + 8))();
    *(undefined8 *)(this + 0x90) = 0;
  }
  if (*(long **)(this + 0xa8) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0xa8) + 8))();
    *(undefined8 *)(this + 0xa8) = 0;
  }
  if (*(void **)(this + 0x3460) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x3460));
    *(undefined8 *)(this + 0x3460) = 0;
  }
  *(undefined ***)(this + 0x10) = &PTR__iInventoryListener_00fce450;
  *(undefined ***)this = &PTR__CSubMenu_00fe64b0;
  CRunicCore::~CRunicCore((CRunicCore *)this);
  return;
}

/* address=00b684f0
   symbol=CMerchantMenu::~CMerchantMenu */

/* non-virtual thunk to CMerchantMenu::~CMerchantMenu() */

void __thiscall CMerchantMenu::~CMerchantMenu(CMerchantMenu *this)

{
  ~CMerchantMenu(this + -0x10);
  return;
}

/* address=00b68500
   symbol=CMerchantMenu::~CMerchantMenu */

/* non-virtual thunk to CMerchantMenu::~CMerchantMenu() */

void __thiscall CMerchantMenu::~CMerchantMenu(CMerchantMenu *this)

{
  ~CMerchantMenu(this + -0x10);
  return;
}

/* address=00b68510
   symbol=CMerchantMenu::~CMerchantMenu */

/* CMerchantMenu::~CMerchantMenu() */

void __thiscall CMerchantMenu::~CMerchantMenu(CMerchantMenu *this)

{
  ~CMerchantMenu(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}

/* address=00b68530
   symbol=CMerchantMenu::handle_PetMouseOver */

/* CMerchantMenu::handle_PetMouseOver(CEGUI::EventArgs const&) */

undefined8 __thiscall CMerchantMenu::handle_PetMouseOver(CMerchantMenu *this,EventArgs *param_1)

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
        *(CBaseUnit **)(this + 0x3438) = pCVar5;
        if (((pCVar5[0x348] == (CBaseUnit)0x0) || (*(int *)(pCVar5 + 0x3e0) == 0)) &&
           (cVar4 = CBaseUnit::ISA(pCVar5,0x78), cVar4 == '\0')) {
          CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x30),0));
          CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x38),0));
        }
        else {
          CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x30),0));
          CEGUI::Window::moveToFront();
          CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x38),0));
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
                    /* try { // try from 00b687e0 to 00b687e4 has its CatchHandler @ 00b688d3 */
      CEGUI::Window::setPosition(*(UVector2 **)(this + 0x3448));
                    /* try { // try from 00b68841 to 00b68845 has its CatchHandler @ 00b688cb */
      CEGUI::Window::setSize(*(UVector2 **)(this + 0x3448));
      CEGUI::Window::moveToBack();
      this[0x3450] = (CMerchantMenu)0x1;
      return 1;
    }
    return 1;
  }
  return 1;
}

/* address=00b688e0
   symbol=CMerchantMenu::handle_MouseOver */

/* CMerchantMenu::handle_MouseOver(CEGUI::EventArgs const&) */

undefined8 __thiscall CMerchantMenu::handle_MouseOver(CMerchantMenu *this,EventArgs *param_1)

{
  Window *pWVar1;
  char cVar2;
  CBaseUnit *pCVar3;

  if (*(long *)(param_1 + 0x10) == 0) {
    return 1;
  }
  if (*(long *)(this + 0x50) != 0) {
    if (this[0x60] != (CMerchantMenu)0x0) {
      pCVar3 = (CBaseUnit *)
               CInventory::getEquipmentInSlot
                         (*(CInventory **)(*(long *)(this + 0x50) + 0x490),
                          **(uint **)(*(long *)(param_1 + 0x10) + 0x1d8));
      if (pCVar3 != (CBaseUnit *)0x0) {
        *(CBaseUnit **)(this + 0x3438) = pCVar3;
        if (((pCVar3[0x348] == (CBaseUnit)0x0) || (*(int *)(pCVar3 + 0x3e0) == 0)) &&
           (cVar2 = CBaseUnit::ISA(pCVar3,0x78), cVar2 == '\0')) {
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
      pWVar1 = *(Window **)(this + 0x28);
      CEGUI::Window::getPosition();
      CEGUI::Window::getPosition();
      CEGUI::Window::getWidth();
      CEGUI::Window::getHeight();
      cVar2 = CEGUI::Window::isChild(pWVar1);
      if (cVar2 == '\0') {
        CEGUI::Window::addChildWindow(pWVar1);
      }
                    /* try { // try from 00b68ba7 to 00b68bab has its CatchHandler @ 00b68c90 */
      CEGUI::Window::setPosition(*(UVector2 **)(this + 0x3448));
                    /* try { // try from 00b68c08 to 00b68c0c has its CatchHandler @ 00b68c88 */
      CEGUI::Window::setSize(*(UVector2 **)(this + 0x3448));
      CEGUI::Window::moveToBack();
      this[0x3450] = (CMerchantMenu)0x1;
      return 1;
    }
    return 1;
  }
  return 1;
}

/* address=00b68ca0
   symbol=CMerchantMenu::handle_CloseButton */

/* CMerchantMenu::handle_CloseButton(CEGUI::EventArgs const&) */

undefined8 __thiscall CMerchantMenu::handle_CloseButton(CMerchantMenu *this,EventArgs *param_1)

{
  long lVar1;

  if (*(int *)(param_1 + 0x28) != 0) {
    return 1;
  }
  this[0x62] = (CMerchantMenu)0x1;
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

/* address=00b69c00
   symbol=CMerchantMenu::update */

/* WARNING: Removing unreachable block (ram,0x00b6a205) */
/* WARNING: Removing unreachable block (ram,0x00b6a1f7) */
/* WARNING: Removing unreachable block (ram,0x00b6a1e9) */
/* WARNING: Removing unreachable block (ram,0x00b6a1aa) */
/* CMerchantMenu::update(float) */

void __thiscall CMerchantMenu::update(CMerchantMenu *this,float param_1)

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
  if (this[0x60] == (CMerchantMenu)0x0) {
    *(undefined8 *)(this + 0x3438) = 0;
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x30),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x38),0));
    if ((this[0x60] == (CMerchantMenu)0x0) && (this[0x61] != (CMerchantMenu)0x0)) {
      return;
    }
  }
  CGenericModel::updateAnimation(*(CGenericModel **)(this + 0x90),param_1,false);
  Ogre::Entity::_updateAnimation();
  plVar6 = *(long **)(*(long *)(this + 0x90) + 0x130);
  pcVar3 = *(code **)(*plVar6 + 0x1b0);
                    /* try { // try from 00b69c9d to 00b69ca1 has its CatchHandler @ 00b6a1c9 */
  std::string::string((string *)local_58,"tag_topmerchant",local_39);
                    /* try { // try from 00b69ca8 to 00b69caa has its CatchHandler @ 00b6a1d6 */
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
                    /* try { // try from 00b69dcc to 00b69dd0 has its CatchHandler @ 00b6a1c7 */
  CEGUI::Window::setPosition(*(UVector2 **)(this + 0x28));
  plVar6 = *(long **)(*(long *)(this + 0x90) + 0x130);
  pcVar3 = *(code **)(*plVar6 + 0x1b0);
                    /* try { // try from 00b69e02 to 00b69e06 has its CatchHandler @ 00b6a1c2 */
  std::string::string((string *)local_68,"tag_bottommerchant",&local_3a);
                    /* try { // try from 00b69e0d to 00b69e0f has its CatchHandler @ 00b6a1b5 */
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
                    /* try { // try from 00b69eaa to 00b69eae has its CatchHandler @ 00b6a1d4 */
  CEGUI::Window::setPosition(*(UVector2 **)(this + 0x40));
  plVar6 = *(long **)(*(long *)(this + 0x90) + 0x130);
  pcVar3 = *(code **)(*plVar6 + 0x1b0);
                    /* try { // try from 00b69ee0 to 00b69ee4 has its CatchHandler @ 00b6a1e2 */
  std::string::string((string *)local_78,"tag_bottommerchantright",&local_3b);
                    /* try { // try from 00b69eeb to 00b69eed has its CatchHandler @ 00b6a1d2 */
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
  if ((this[0x60] == (CMerchantMenu)0x0) && (this[0x61] == (CMerchantMenu)0x0)) {
                    /* try { // try from 00b6a00e to 00b6a027 has its CatchHandler @ 00b6a180 */
    std::string::string((string *)local_88,"CLOSE",&local_3c);
    cVar4 = CGenericModel::animationPlaying(*(CGenericModel **)(this + 0x90),(string *)local_88);
    bVar8 = false;
    if (cVar4 == '\0') {
                    /* try { // try from 00b6a08d to 00b6a0ab has its CatchHandler @ 00b6a180 */
      std::string::string(local_98,"CLOSE",&local_3d);
      cVar4 = CGenericModel::animationQueued(*(CGenericModel **)(this + 0x90),local_98);
      bVar8 = cVar4 == '\0';
                    /* try { // try from 00b6a0ba to 00b6a0be has its CatchHandler @ 00b6a1e4 */
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
      this[0x61] = (CMerchantMenu)0x1;
    }
  }
  return;
}

/* address=00b6a220
   symbol=CMerchantMenu::setOpen */

/* WARNING: Removing unreachable block (ram,0x00b6a775) */
/* WARNING: Removing unreachable block (ram,0x00b6a768) */
/* WARNING: Removing unreachable block (ram,0x00b6a714) */
/* CMerchantMenu::setOpen(bool) */

void __thiscall CMerchantMenu::setOpen(CMerchantMenu *this,bool param_1)

{
  int *piVar1;
  char cVar2;
  int iVar3;
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

  if (this[0x60] == (CMerchantMenu)0x0) {
    if (!param_1) {
      this[0x60] = (CMerchantMenu)0x0;
      return;
    }
    CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0x68),KSETTINGS_RES_WIDTH);
    CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0x68),KSETTINGS_RES_HEIGHT);
    CSoundBank::playSample(*(CSoundBank **)(this + 0xa8),0x16,(SceneNode *)0x0,0.0,0.0,false);
    (**(code **)(**(long **)(this + 0x90) + 0x50))(*(long **)(this + 0x90),1);
                    /* try { // try from 00b6a2dd to 00b6a2e1 has its CatchHandler @ 00b6a722 */
    std::string::string((string *)&local_28,"CLOSE",&local_19);
                    /* try { // try from 00b6a2ec to 00b6a2f0 has its CatchHandler @ 00b6a71f */
    cVar2 = CGenericModel::animationPlaying(*(CGenericModel **)(this + 0x90),(string *)&local_28);
    if ((allocator *)(local_28 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_28 + -8);
      iVar3 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar3 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_28 + -0x18));
      }
    }
    if (cVar2 == '\0') {
                    /* try { // try from 00b6a58a to 00b6a58e has its CatchHandler @ 00b6a726 */
      std::string::string(local_48,"OPEN",&local_1b);
                    /* try { // try from 00b6a5ab to 00b6a5af has its CatchHandler @ 00b6a724 */
      CGenericModel::playAnimation
                (*(CGenericModel **)(this + 0x90),local_48,false,DAT_00fa4824,DAT_00fa8760);
                    /* try { // try from 00b6a5b3 to 00b6a5b7 has its CatchHandler @ 00b6a726 */
      std::string::~string(local_48);
    }
    else {
                    /* try { // try from 00b6a321 to 00b6a325 has its CatchHandler @ 00b6a712 */
      std::string::string(local_38,"OPEN",&local_1a);
                    /* try { // try from 00b6a34a to 00b6a34e has its CatchHandler @ 00b6a705 */
      CGenericModel::blendAnimation
                (*(CGenericModel **)(this + 0x90),local_38,false,DAT_00fa480c,DAT_00fa4824,
                 DAT_00fa8760);
                    /* try { // try from 00b6a352 to 00b6a356 has its CatchHandler @ 00b6a712 */
      std::string::~string(local_38);
    }
                    /* try { // try from 00b6a369 to 00b6a36d has its CatchHandler @ 00b6a703 */
    std::string::string((string *)local_58,"IDLE",&local_1c);
                    /* try { // try from 00b6a38d to 00b6a391 has its CatchHandler @ 00b6a773 */
    CGenericModel::queueBlendAnimation
              (*(CGenericModel **)(this + 0x90),(string *)local_58,true,DAT_00fa480c,DAT_00fa47fc);
    if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_58[0] + -8);
      iVar3 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar3 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
      }
    }
    CEGUI::Window::addChildWindow(*(Window **)(this + 0x18));
    CEGUI::Window::moveToBack();
    *(undefined4 *)(this + 0x3454) = 0;
    *(undefined4 *)(this + 0x3458) = 0;
    CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x33e0),0));
    CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x33e8),0));
    CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x33f0),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x33c8),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x33d0),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x33d8),0));
    iVar3 = CCharacter::getDefaultMerchantTab(*(CCharacter **)(this + 0x50));
    if (iVar3 == 1) {
      CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x3420),0));
      CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x3410),0));
      CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x3418),0));
      CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x3408),0));
      CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x33f8),0));
      CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x3400),0));
      *(undefined4 *)(this + 0x3454) = 1;
    }
    else if (iVar3 == 2) {
      *(undefined4 *)(this + 0x3454) = 2;
      CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x3420),0));
      CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x3410),0));
      CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x3418),0));
      CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x3408),0));
      CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x33f8),0));
      CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x3400),0));
    }
    else {
      *(undefined4 *)(this + 0x3454) = 0;
      CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x3420),0));
      CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x3410),0));
      CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x3418),0));
      CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x3408),0));
      CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x33f8),0));
      CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x3400),0));
    }
    cVar2 = CBaseUnit::ISA(*(CBaseUnit **)(this + 0x50),0x7f);
    if (cVar2 == '\0') {
      CGameUI::queueTip(*(CGameUI **)(this + 0x70),5);
    }
    else {
      CGameUI::queueTip(*(CGameUI **)(this + 0x70),0xc);
    }
  }
  else if (!param_1) {
    CSoundBank::playSample(*(CSoundBank **)(this + 0xa8),0x42,(SceneNode *)0x0,0.0,0.0,false);
                    /* try { // try from 00b6a505 to 00b6a509 has its CatchHandler @ 00b6a6f8 */
    std::string::string((string *)local_68,"CLOSE",&local_1d);
                    /* try { // try from 00b6a52e to 00b6a532 has its CatchHandler @ 00b6a75b */
    CGenericModel::blendAnimation
              (*(CGenericModel **)(this + 0x90),(string *)local_68,false,DAT_00fa480c,DAT_00fa4824,
               DAT_00fa8760);
    if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_68[0] + -8);
      iVar3 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar3 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
      }
    }
    this[0x61] = (CMerchantMenu)0x0;
    this[0x60] = (CMerchantMenu)0x0;
    return;
  }
  this[0x60] = (CMerchantMenu)param_1;
  (**(code **)(*(long *)this + 0x48))(this);
  return;
}

/* address=00b6a790
   symbol=CMerchantMenu::mapEventHandlers */

/* CMerchantMenu::mapEventHandlers(CEGUI::Window*) */

void __thiscall CMerchantMenu::mapEventHandlers(CMerchantMenu *this,Window *param_1)

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
                    /* try { // try from 00b6a856 to 00b6a8d3 has its CatchHandler @ 00b6ab34 */
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
                    /* try { // try from 00b6aa28 to 00b6aaa6 has its CatchHandler @ 00b6ab34 */
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
                    /* try { // try from 00b6aab3 to 00b6aab7 has its CatchHandler @ 00b6aaee */
    CEGUI::String::~String((String *)local_268);
                    /* try { // try from 00b6aac0 to 00b6aac4 has its CatchHandler @ 00b6ab27 */
    CEGUI::String::~String((String *)&local_1b8);
  }
                    /* try { // try from 00b6a8e2 to 00b6a911 has its CatchHandler @ 00b6ab15 */
  CEGUI::String::~String((String *)&local_108);
  if (bVar11) {
    pcVar3 = *(code **)(*(long *)(param_1 + 0x38) + 0x10);
    local_48[0] = operator_new(0x20);
    local_48[0][3] = this;
    *local_48[0] = &PTR__MemberFunctionSlot_00ff0270;
    local_48[0][2] = 0;
    local_48[0][1] = 0x59;
                    /* try { // try from 00b6a951 to 00b6a986 has its CatchHandler @ 00b6ab1a */
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
                    /* try { // try from 00b6a9b7 to 00b6a9bb has its CatchHandler @ 00b6ab15 */
    CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_48);
  }
  return;
}

/* address=00b6ab50
   symbol=CMerchantMenu::setPetSlotIcon */

/* WARNING: Removing unreachable block (ram,0x00b6c261) */
/* WARNING: Removing unreachable block (ram,0x00b6c2cc) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CMerchantMenu::setPetSlotIcon(CEquipment*, int, int) */

void __thiscall
CMerchantMenu::setPetSlotIcon(CMerchantMenu *this,CEquipment *param_1,int param_2,int param_3)

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
      goto LAB_00b6ac38;
    }
  }
  else {
LAB_00b6ac38:
    if (*(Window **)(pUVar17 + 0xb0) != (Window *)0x0) {
      CEGUI::Window::removeChildWindow(*(Window **)(pUVar17 + 0xb0));
    }
    CEGUI::Window::addChildWindow(*(Window **)(this + lVar16 * 8 + 0x26f8));
    local_64 = 0;
    local_68 = 0;
    local_5c = 0x3f800000;
    local_60 = 0;
                    /* try { // try from 00b6ac98 to 00b6ac9c has its CatchHandler @ 00b6c365 */
    CEGUI::Window::setPosition(pUVar17);
    local_74 = 0;
    local_78 = 0;
    local_6c = 0;
    local_70 = 0;
                    /* try { // try from 00b6acd4 to 00b6acd8 has its CatchHandler @ 00b6c315 */
    CEGUI::Window::setPosition(pUVar17);
    CEGUI::Window::getSize();
                    /* try { // try from 00b6acfc to 00b6ad00 has its CatchHandler @ 00b6c30c */
    CEGUI::Window::setSize(pUVar17);
    CEGUI::Window::moveToFront();
    *(CMerchantMenu **)(pUVar17 + 0x1d8) = this + (long)param_3 * 4 + 0xb0;
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
                    /* try { // try from 00b6b1ad to 00b6b1b1 has its CatchHandler @ 00b6c322 */
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
                    /* try { // try from 00b6b21e to 00b6b222 has its CatchHandler @ 00b6c339 */
    CEGUI::PropertySet::setProperty(*(String **)(this + lVar16 * 8 + 0x2ea8),(String *)&local_598);
                    /* try { // try from 00b6b226 to 00b6b22a has its CatchHandler @ 00b6c322 */
    CEGUI::String::~String((String *)&local_598);
    CEGUI::String::~String((String *)&local_648);
    if (param_1[0x348] != (CEquipment)0x0) goto LAB_00b6af42;
LAB_00b6b241:
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
                    /* try { // try from 00b6b31d to 00b6b334 has its CatchHandler @ 00b6c2a5 */
    CEGUI::Imageset::getImage(*(String **)(this + 0x3440));
    CEGUI::PropertyHelper::imageToString(local_7a8);
    local_850 = 0x20;
    local_848 = 0;
    local_838 = 0;
    local_840 = 0;
    local_7b0 = (uint *)0x0;
    local_858 = 0;
    local_830[0] = 0;
                    /* try { // try from 00b6b398 to 00b6b39c has its CatchHandler @ 00b6c2ca */
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
                    /* try { // try from 00b6b415 to 00b6b419 has its CatchHandler @ 00b6c317 */
    CEGUI::PropertySet::setProperty(*(String **)(this + lVar16 * 8 + 0x2988),(String *)&local_858);
                    /* try { // try from 00b6b41d to 00b6b421 has its CatchHandler @ 00b6c2ca */
    CEGUI::String::~String((String *)&local_858);
                    /* try { // try from 00b6b425 to 00b6b429 has its CatchHandler @ 00b6c2a5 */
    CEGUI::String::~String((String *)local_7a8);
  }
  else {
    if (*(uint *)(param_1 + 0x3e0) < 2) {
      CEGUI::String::String(local_388,"onesocketglow");
                    /* try { // try from 00b6c164 to 00b6c17b has its CatchHandler @ 00b6c1f2 */
      CEGUI::Imageset::getImage(*(String **)(this + 0x3440));
      CEGUI::PropertyHelper::imageToString(local_438);
                    /* try { // try from 00b6c18c to 00b6c190 has its CatchHandler @ 00b6c1eb */
      CEGUI::String::String(local_4e8,"Image");
                    /* try { // try from 00b6c1a4 to 00b6c1a8 has its CatchHandler @ 00b6c1e9 */
      CEGUI::PropertySet::setProperty(*(String **)(this + lVar16 * 8 + 0x2ea8),local_4e8);
                    /* try { // try from 00b6c1ac to 00b6c1b0 has its CatchHandler @ 00b6c1eb */
      CEGUI::String::~String(local_4e8);
                    /* try { // try from 00b6c1b4 to 00b6c1b8 has its CatchHandler @ 00b6c1f2 */
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
                    /* try { // try from 00b6ae15 to 00b6ae2c has its CatchHandler @ 00b6c2d7 */
      CEGUI::Imageset::getImage(*(String **)(this + 0x3440));
      CEGUI::PropertyHelper::imageToString(local_228);
      local_2d0 = 0x20;
      local_2c8 = 0;
      local_2b8 = 0;
      local_2c0 = 0;
      local_230 = (uint *)0x0;
      local_2d8 = 0;
      local_2b0[0] = 0;
                    /* try { // try from 00b6ae90 to 00b6ae94 has its CatchHandler @ 00b6c2dc */
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
                    /* try { // try from 00b6af05 to 00b6af09 has its CatchHandler @ 00b6c2de */
      CEGUI::PropertySet::setProperty(*(String **)(this + lVar16 * 8 + 0x2ea8),(String *)&local_2d8)
      ;
                    /* try { // try from 00b6af0d to 00b6af11 has its CatchHandler @ 00b6c2dc */
      CEGUI::String::~String((String *)&local_2d8);
                    /* try { // try from 00b6af15 to 00b6af19 has its CatchHandler @ 00b6c2d7 */
      CEGUI::String::~String((String *)local_228);
      CEGUI::String::~String((String *)&local_178);
    }
    CEGUI::Window::moveToFront();
    if (param_1[0x348] == (CEquipment)0x0) goto LAB_00b6b241;
LAB_00b6af42:
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
                    /* try { // try from 00b6b034 to 00b6b038 has its CatchHandler @ 00b6c2eb */
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
                    /* try { // try from 00b6b0ad to 00b6b0b1 has its CatchHandler @ 00b6c347 */
    CEGUI::PropertySet::setProperty(*(String **)(this + lVar16 * 8 + 0x2988),(String *)&local_908);
                    /* try { // try from 00b6b0b5 to 00b6b0b9 has its CatchHandler @ 00b6c2eb */
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
        if (pUVar17 != (UVector2 *)0x0) goto LAB_00b6b532;
LAB_00b6b68d:
        CEquipment::createIcon(this_00,*(CGameUI **)(this + 0x70),false);
        pUVar17 = *(UVector2 **)(this_00 + 0x2c8);
        if (pUVar17 != (UVector2 *)0x0) {
          CEGUI::EventSet::setMutedState((bool)((char)pUVar17 + '8'));
          pUVar17[0x3e2] = (UVector2)0x1;
          goto LAB_00b6b532;
        }
      }
      else {
        this_00 = (CEquipment *)**(long **)(param_1 + 1000);
        pUVar17 = *(UVector2 **)(this_00 + 0x2c8);
        if (pUVar17 == (UVector2 *)0x0) goto LAB_00b6b68d;
LAB_00b6b532:
        if (*(Window **)(pUVar17 + 0xb0) != (Window *)0x0) {
          CEGUI::Window::removeChildWindow(*(Window **)(pUVar17 + 0xb0));
        }
        CEGUI::Window::addChildWindow(*(Window **)(this + 0x30));
        local_a4 = (float)((long)((float)(int)((float)(~uVar21 & uVar8 | uVar7 & uVar21) +
                                              fVar3 * 0.0) + fVar4) & 0xffffffff);
        local_9c = (float)(uVar20 & 0xffffffff);
        local_a8 = 0;
        local_a0 = 0;
                    /* try { // try from 00b6b59c to 00b6b5a0 has its CatchHandler @ 00b6c319 */
        CEGUI::Window::setPosition(pUVar17);
        CEGUI::Window::getSize();
                    /* try { // try from 00b6b5c3 to 00b6b5c7 has its CatchHandler @ 00b6c335 */
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
                    /* try { // try from 00b6bc65 to 00b6bc7c has its CatchHandler @ 00b6c2aa */
      CEGUI::Imageset::getImage(*(String **)(this + 0x3440));
      CEGUI::PropertyHelper::imageToString(local_14b8);
      local_1560 = 0x20;
      local_1558 = 0;
      local_1548 = 0;
      local_1550 = 0;
      local_14c0 = (uint *)0x0;
      local_1568 = 0;
      local_1540[0] = 0;
                    /* try { // try from 00b6bce0 to 00b6bce4 has its CatchHandler @ 00b6c2b5 */
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
                    /* try { // try from 00b6bd4d to 00b6bd51 has its CatchHandler @ 00b6c337 */
      CEGUI::PropertySet::setProperty
                (*(String **)(this + lVar16 * 8 + 0x2c18),(String *)&local_1568);
                    /* try { // try from 00b6bd55 to 00b6bd59 has its CatchHandler @ 00b6c2b5 */
      CEGUI::String::~String((String *)&local_1568);
                    /* try { // try from 00b6bd5d to 00b6bd61 has its CatchHandler @ 00b6c2aa */
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
                    /* try { // try from 00b6ba95 to 00b6baac has its CatchHandler @ 00b6c355 */
      CEGUI::Imageset::getImage(*(String **)(this + 0x3440));
      CEGUI::PropertyHelper::imageToString(local_12a8);
      local_1350 = 0x20;
      local_1348 = 0;
      local_1338 = 0;
      local_1340 = 0;
      local_12b0 = (uint *)0x0;
      local_1358 = 0;
      local_1330[0] = 0;
                    /* try { // try from 00b6bb10 to 00b6bb14 has its CatchHandler @ 00b6c34c */
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
                    /* try { // try from 00b6bb7d to 00b6bb81 has its CatchHandler @ 00b6c372 */
      CEGUI::PropertySet::setProperty
                (*(String **)(this + lVar16 * 8 + 0x2c18),(String *)&local_1358);
                    /* try { // try from 00b6bb85 to 00b6bb89 has its CatchHandler @ 00b6c34c */
      CEGUI::String::~String((String *)&local_1358);
                    /* try { // try from 00b6bb8d to 00b6bb91 has its CatchHandler @ 00b6c355 */
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
                    /* try { // try from 00b6c0eb to 00b6c102 has its CatchHandler @ 00b6c395 */
          CEGUI::Imageset::getImage(*(String **)(this + 0x3440));
          CEGUI::PropertyHelper::imageToString(local_f38);
                    /* try { // try from 00b6c113 to 00b6c117 has its CatchHandler @ 00b6c385 */
          CEGUI::String::String(local_fe8,"Image");
                    /* try { // try from 00b6c12b to 00b6c12f has its CatchHandler @ 00b6c377 */
          CEGUI::PropertySet::setProperty(*(String **)(this + lVar16 * 8 + 0x2c18),local_fe8);
                    /* try { // try from 00b6c133 to 00b6c137 has its CatchHandler @ 00b6c385 */
          CEGUI::String::~String(local_fe8);
                    /* try { // try from 00b6c13b to 00b6c13f has its CatchHandler @ 00b6c395 */
          CEGUI::String::~String((String *)local_f38);
        }
        else {
          pSVar19 = local_c78;
          CEGUI::String::String(pSVar19,"blueslotglow");
                    /* try { // try from 00b6bdb0 to 00b6bdc7 has its CatchHandler @ 00b6c1f9 */
          CEGUI::Imageset::getImage(*(String **)(this + 0x3440));
          CEGUI::PropertyHelper::imageToString(local_d28);
                    /* try { // try from 00b6bdd8 to 00b6bddc has its CatchHandler @ 00b6c1f7 */
          CEGUI::String::String(local_dd8,"Image");
                    /* try { // try from 00b6bdf0 to 00b6bdf4 has its CatchHandler @ 00b6c1c6 */
          CEGUI::PropertySet::setProperty(*(String **)(this + lVar16 * 8 + 0x2c18),local_dd8);
                    /* try { // try from 00b6bdf8 to 00b6bdfc has its CatchHandler @ 00b6c1f7 */
          CEGUI::String::~String(local_dd8);
                    /* try { // try from 00b6be00 to 00b6be04 has its CatchHandler @ 00b6c1f9 */
          CEGUI::String::~String((String *)local_d28);
        }
        CEGUI::String::~String(pSVar19);
        goto LAB_00b6b8d2;
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
                    /* try { // try from 00b6bf44 to 00b6bf48 has its CatchHandler @ 00b6c21d */
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
                    /* try { // try from 00b6bfbd to 00b6bfc1 has its CatchHandler @ 00b6c202 */
      CEGUI::PropertySet::setProperty
                (*(String **)(this + lVar16 * 8 + 0x2c18),(String *)&local_1098);
                    /* try { // try from 00b6bfc5 to 00b6bfc9 has its CatchHandler @ 00b6c21d */
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
                    /* try { // try from 00b6b7cd to 00b6b7e4 has its CatchHandler @ 00b6c305 */
      CEGUI::Imageset::getImage(*(String **)(this + 0x3440));
      CEGUI::PropertyHelper::imageToString(local_b18);
      local_bc0 = 0x20;
      local_bb8 = 0;
      local_ba8 = 0;
      local_bb0 = 0;
      local_b20 = (uint *)0x0;
      local_bc8 = 0;
      local_ba0[0] = 0;
                    /* try { // try from 00b6b848 to 00b6b84c has its CatchHandler @ 00b6c30a */
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
                    /* try { // try from 00b6b8b5 to 00b6b8b9 has its CatchHandler @ 00b6c2f0 */
      CEGUI::PropertySet::setProperty(*(String **)(this + lVar16 * 8 + 0x2c18),(String *)&local_bc8)
      ;
                    /* try { // try from 00b6b8bd to 00b6b8c1 has its CatchHandler @ 00b6c30a */
      CEGUI::String::~String((String *)&local_bc8);
                    /* try { // try from 00b6b8c5 to 00b6b8c9 has its CatchHandler @ 00b6c305 */
      CEGUI::String::~String((String *)local_b18);
    }
  }
  CEGUI::String::~String(pSVar19);
LAB_00b6b8d2:
  if (*(long *)(this + lVar16 * 8 + 0x3138) != 0) {
    bVar18 = SUB81(*(long *)(this + lVar16 * 8 + 0x3138),0);
    if (*(int *)(param_1 + 0x238) < 2) {
      CEGUI::Window::setVisible(bVar18);
    }
    else {
      CEGUI::Window::setVisible(bVar18);
      STRINGS::GetValueAsString((STRINGS *)local_58,*(int *)(param_1 + 0x238));
                    /* try { // try from 00b6b92a to 00b6b92e has its CatchHandler @ 00b6c2f2 */
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
                    /* try { // try from 00b6b958 to 00b6b95c has its CatchHandler @ 00b6c24e */
      CEGUI::String::String(local_1618,local_48[0]);
                    /* try { // try from 00b6b96d to 00b6b971 has its CatchHandler @ 00b6c26c */
      CEGUI::Window::setText(*(String **)(this + lVar16 * 8 + 0x3138));
                    /* try { // try from 00b6b975 to 00b6b979 has its CatchHandler @ 00b6c24e */
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

/* address=00b6c3b0
   symbol=CMerchantMenu::setSlotIcon */

/* WARNING: Removing unreachable block (ram,0x00b6dc55) */
/* WARNING: Removing unreachable block (ram,0x00b6dacb) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CMerchantMenu::setSlotIcon(CEquipment*, int, int) */

void __thiscall
CMerchantMenu::setSlotIcon(CMerchantMenu *this,CEquipment *param_1,int param_2,int param_3)

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
  byte *pbVar12;
  char *pcVar13;
  CEquipment *this_00;
  undefined4 *puVar14;
  uint *puVar15;
  long lVar16;
  UVector2 *pUVar17;
  bool bVar18;
  String *pSVar19;
  ulong uVar20;
  uint uVar21;
  float fVar22;
  uint uVar23;
  uint uVar24;
  String local_1778 [176];
  undefined8 local_16c8;
  ulong local_16c0;
  undefined8 local_16b8;
  undefined8 local_16b0;
  undefined8 local_16a8;
  uint local_16a0 [5];
  uint local_168c [27];
  uint *local_1620;
  Image local_1618 [176];
  undefined8 local_1568;
  ulong local_1560;
  undefined8 local_1558;
  undefined8 local_1550;
  undefined8 local_1548;
  uint local_1540 [11];
  uint local_1514 [21];
  uint *local_14c0;
  undefined8 local_14b8;
  ulong local_14b0;
  undefined8 local_14a8;
  undefined8 local_14a0;
  undefined8 local_1498;
  uint local_1490 [5];
  uint local_147c [27];
  uint *local_1410;
  Image local_1408 [176];
  undefined8 local_1358;
  ulong local_1350;
  undefined8 local_1348;
  undefined8 local_1340;
  undefined8 local_1338;
  uint local_1330 [15];
  uint local_12f4 [17];
  uint *local_12b0;
  String local_12a8 [176];
  String local_11f8 [176];
  String local_1148 [176];
  Image local_1098 [176];
  String local_fe8 [176];
  String local_f38 [176];
  Image local_e88 [176];
  String local_dd8 [176];
  undefined8 local_d28;
  ulong local_d20;
  undefined8 local_d18;
  undefined8 local_d10;
  undefined8 local_d08;
  uint local_d00 [5];
  uint local_cec [27];
  uint *local_c80;
  Image local_c78 [176];
  undefined8 local_bc8;
  ulong local_bc0;
  undefined8 local_bb8;
  undefined8 local_bb0;
  undefined8 local_ba8;
  uint local_ba0 [12];
  uint local_b70 [20];
  uint *local_b20;
  undefined8 local_b18;
  ulong local_b10;
  undefined8 local_b08;
  undefined8 local_b00;
  undefined8 local_af8;
  undefined4 local_af0 [32];
  undefined4 *local_a70;
  undefined8 local_a68;
  ulong local_a60;
  undefined8 local_a58;
  undefined8 local_a50;
  undefined8 local_a48;
  uint local_a40 [5];
  uint local_a2c [27];
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
      goto LAB_00b6c49c;
    }
  }
  else {
LAB_00b6c49c:
    if (*(Window **)(pUVar17 + 0xb0) != (Window *)0x0) {
      CEGUI::Window::removeChildWindow(*(Window **)(pUVar17 + 0xb0));
    }
    CEGUI::Window::addChildWindow(*(Window **)(this + lVar16 * 8 + 0x1de8));
    local_64 = 0;
    local_68 = 0;
    local_5c = 0x3f800000;
    local_60 = 0;
                    /* try { // try from 00b6c4fc to 00b6c500 has its CatchHandler @ 00b6db95 */
    CEGUI::Window::setPosition(pUVar17);
    local_74 = 0;
    local_78 = 0;
    local_6c = 0;
    local_70 = 0;
                    /* try { // try from 00b6c538 to 00b6c53c has its CatchHandler @ 00b6db85 */
    CEGUI::Window::setPosition(pUVar17);
    CEGUI::Window::getSize();
                    /* try { // try from 00b6c560 to 00b6c564 has its CatchHandler @ 00b6db75 */
    CEGUI::Window::setSize(pUVar17);
    CEGUI::Window::moveToFront();
    *(CMerchantMenu **)(pUVar17 + 0x1d8) = this + (long)param_3 * 4 + 0xb0;
  }
  if (((param_1[0x348] == (CEquipment)0x0) || (*(int *)(param_1 + 0x3e0) == 0)) ||
     (cVar9 = CBaseUnit::ISA(*(CBaseUnit **)(this + 0x50),0x7f), cVar9 != '\0')) {
    local_640 = 0x20;
    local_638 = 0;
    local_628 = 0;
    local_630 = 0;
    local_5a0 = (undefined4 *)0x0;
    local_648 = 0;
    local_620[0] = 0;
    CEGUI::String::grow((ulong)&local_648);
    local_648 = 0;
    puVar14 = local_620;
    if (0x20 < local_640) {
      puVar14 = local_5a0;
    }
    *puVar14 = 0;
    local_590 = 0x20;
    local_588 = 0;
    local_578 = 0;
    local_580 = 0;
    local_4f0 = (uint *)0x0;
    local_598 = 0;
    local_570[0] = 0;
                    /* try { // try from 00b6c686 to 00b6c68a has its CatchHandler @ 00b6daf5 */
    CEGUI::String::grow((ulong)&local_598);
    puVar15 = local_570;
    if (0x20 < local_590) {
      puVar15 = local_4f0;
    }
    pbVar12 = (byte *)0xfd0c0d;
    do {
      bVar6 = *pbVar12;
      pbVar12 = pbVar12 + 1;
      *puVar15 = (uint)bVar6;
      puVar15 = puVar15 + 1;
    } while (pbVar12 != (byte *)0xfd0c12);
    local_598 = 5;
    puVar15 = local_55c;
    if (0x20 < local_590) {
      puVar15 = local_4f0 + 5;
    }
    *puVar15 = 0;
                    /* try { // try from 00b6c6f6 to 00b6c6fa has its CatchHandler @ 00b6db0d */
    CEGUI::PropertySet::setProperty(*(String **)(this + lVar16 * 8 + 0x1960),(String *)&local_598);
                    /* try { // try from 00b6c6fe to 00b6c702 has its CatchHandler @ 00b6daf5 */
    CEGUI::String::~String((String *)&local_598);
    CEGUI::String::~String((String *)&local_648);
  }
  else {
    if (*(uint *)(param_1 + 0x3e0) < 2) {
      if (*(uint *)(param_1 + 0x3e0) == 1) {
        CEGUI::String::String(local_388,"onesocketglow");
                    /* try { // try from 00b6d89f to 00b6d8b6 has its CatchHandler @ 00b6dc35 */
        CEGUI::Imageset::getImage(*(String **)(this + 0x3440));
        CEGUI::PropertyHelper::imageToString(local_438);
                    /* try { // try from 00b6d8c7 to 00b6d8cb has its CatchHandler @ 00b6dc25 */
        CEGUI::String::String(local_4e8,"Image");
                    /* try { // try from 00b6d8df to 00b6d8e3 has its CatchHandler @ 00b6dc45 */
        CEGUI::PropertySet::setProperty(*(String **)(this + lVar16 * 8 + 0x1960),local_4e8);
                    /* try { // try from 00b6d8e7 to 00b6d8eb has its CatchHandler @ 00b6dc25 */
        CEGUI::String::~String(local_4e8);
                    /* try { // try from 00b6d8ef to 00b6d8f3 has its CatchHandler @ 00b6dc35 */
        CEGUI::String::~String((String *)local_438);
        CEGUI::String::~String(local_388);
      }
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
      puVar15 = local_150;
      if (0x20 < local_170) {
        puVar15 = local_d0;
      }
      pcVar13 = "twosocketglow";
      do {
        bVar6 = *pcVar13;
        pcVar13 = pcVar13 + 1;
        *puVar15 = (uint)bVar6;
        puVar15 = puVar15 + 1;
      } while ((byte *)pcVar13 != (byte *)0xfe60d0);
      local_178 = 0xd;
      puVar15 = local_11c;
      if (0x20 < local_170) {
        puVar15 = local_d0 + 0xd;
      }
      *puVar15 = 0;
                    /* try { // try from 00b6d4a5 to 00b6d4bc has its CatchHandler @ 00b6da6a */
      CEGUI::Imageset::getImage(*(String **)(this + 0x3440));
      CEGUI::PropertyHelper::imageToString(local_228);
      local_2d0 = 0x20;
      local_2c8 = 0;
      local_2b8 = 0;
      local_2c0 = 0;
      local_230 = (uint *)0x0;
      local_2d8 = 0;
      local_2b0[0] = 0;
                    /* try { // try from 00b6d520 to 00b6d524 has its CatchHandler @ 00b6da68 */
      CEGUI::String::grow((ulong)&local_2d8);
      puVar15 = local_2b0;
      if (0x20 < local_2d0) {
        puVar15 = local_230;
      }
      pbVar12 = (byte *)0xfd0c0d;
      do {
        bVar6 = *pbVar12;
        pbVar12 = pbVar12 + 1;
        *puVar15 = (uint)bVar6;
        puVar15 = puVar15 + 1;
      } while (pbVar12 != (byte *)0xfd0c12);
      local_2d8 = 5;
      puVar15 = local_29c;
      if (0x20 < local_2d0) {
        puVar15 = local_230 + 5;
      }
      *puVar15 = 0;
                    /* try { // try from 00b6d59d to 00b6d5a1 has its CatchHandler @ 00b6da0e */
      CEGUI::PropertySet::setProperty(*(String **)(this + lVar16 * 8 + 0x1960),(String *)&local_2d8)
      ;
                    /* try { // try from 00b6d5a5 to 00b6d5a9 has its CatchHandler @ 00b6da68 */
      CEGUI::String::~String((String *)&local_2d8);
                    /* try { // try from 00b6d5ad to 00b6d5b1 has its CatchHandler @ 00b6da6a */
      CEGUI::String::~String((String *)local_228);
      CEGUI::String::~String((String *)&local_178);
    }
    CEGUI::Window::moveToFront();
  }
  if (param_1[0x348] == (CEquipment)0x0) {
    pSVar19 = (String *)&local_6f8;
    local_6f0 = 0x20;
    local_6e8 = 0;
    local_6d8 = 0;
    local_6e0 = 0;
    local_650 = (uint *)0x0;
    local_6f8 = 0;
    local_6d0[0] = 0;
    CEGUI::String::grow((ulong)pSVar19);
    puVar15 = local_6d0;
    if (0x20 < local_6f0) {
      puVar15 = local_650;
    }
    pcVar13 = "unidentified";
    do {
      bVar6 = *pcVar13;
      pcVar13 = pcVar13 + 1;
      *puVar15 = (uint)bVar6;
      puVar15 = puVar15 + 1;
    } while ((byte *)pcVar13 != (byte *)0xfef79d);
    local_6f8 = 0xc;
    puVar15 = local_6a0;
    if (0x20 < local_6f0) {
      puVar15 = local_650 + 0xc;
    }
    *puVar15 = 0;
                    /* try { // try from 00b6c7ed to 00b6c804 has its CatchHandler @ 00b6dae2 */
    CEGUI::Imageset::getImage(*(String **)(this + 0x3440));
    CEGUI::PropertyHelper::imageToString(local_7a8);
    local_850 = 0x20;
    local_848 = 0;
    local_838 = 0;
    local_840 = 0;
    local_7b0 = (uint *)0x0;
    local_858 = 0;
    local_830[0] = 0;
                    /* try { // try from 00b6c868 to 00b6c86c has its CatchHandler @ 00b6dae7 */
    CEGUI::String::grow((ulong)&local_858);
    puVar15 = local_830;
    if (0x20 < local_850) {
      puVar15 = local_7b0;
    }
    pbVar12 = (byte *)0xfd0c0d;
    do {
      bVar6 = *pbVar12;
      pbVar12 = pbVar12 + 1;
      *puVar15 = (uint)bVar6;
      puVar15 = puVar15 + 1;
    } while (pbVar12 != (byte *)0xfd0c12);
    local_858 = 5;
    puVar15 = local_81c;
    if (0x20 < local_850) {
      puVar15 = local_7b0 + 5;
    }
    *puVar15 = 0;
                    /* try { // try from 00b6c8e5 to 00b6c8e9 has its CatchHandler @ 00b6dac6 */
    CEGUI::PropertySet::setProperty(*(String **)(this + lVar16 * 8 + 0x1050),(String *)&local_858);
                    /* try { // try from 00b6c8ed to 00b6c8f1 has its CatchHandler @ 00b6dae7 */
    CEGUI::String::~String((String *)&local_858);
                    /* try { // try from 00b6c8f5 to 00b6c8f9 has its CatchHandler @ 00b6dae2 */
    CEGUI::String::~String((String *)local_7a8);
  }
  else {
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
    puVar14 = local_990;
    if (0x20 < local_9b0) {
      puVar14 = local_910;
    }
    *puVar14 = 0;
    local_900 = 0x20;
    local_8f8 = 0;
    local_8e8 = 0;
    local_8f0 = 0;
    local_860 = (uint *)0x0;
    local_908 = 0;
    local_8e0[0] = 0;
                    /* try { // try from 00b6cef2 to 00b6cef6 has its CatchHandler @ 00b6dae0 */
    CEGUI::String::grow((ulong)&local_908);
    puVar15 = local_8e0;
    if (0x20 < local_900) {
      puVar15 = local_860;
    }
    pbVar12 = (byte *)0xfd0c0d;
    do {
      bVar6 = *pbVar12;
      pbVar12 = pbVar12 + 1;
      *puVar15 = (uint)bVar6;
      puVar15 = puVar15 + 1;
    } while (pbVar12 != (byte *)0xfd0c12);
    local_908 = 5;
    puVar15 = local_8cc;
    if (0x20 < local_900) {
      puVar15 = local_860 + 5;
    }
    *puVar15 = 0;
                    /* try { // try from 00b6cf6d to 00b6cf71 has its CatchHandler @ 00b6db3d */
    CEGUI::PropertySet::setProperty(*(String **)(this + lVar16 * 8 + 0x1050),(String *)&local_908);
                    /* try { // try from 00b6cf75 to 00b6cf79 has its CatchHandler @ 00b6dae0 */
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
        if (pUVar17 != (UVector2 *)0x0) goto LAB_00b6c9f2;
LAB_00b6cb48:
        CEquipment::createIcon(this_00,*(CGameUI **)(this + 0x70),false);
        pUVar17 = *(UVector2 **)(this_00 + 0x2c8);
        if (pUVar17 != (UVector2 *)0x0) {
          CEGUI::EventSet::setMutedState((bool)((char)pUVar17 + '8'));
          pUVar17[0x3e2] = (UVector2)0x1;
          goto LAB_00b6c9f2;
        }
      }
      else {
        this_00 = (CEquipment *)**(long **)(param_1 + 1000);
        pUVar17 = *(UVector2 **)(this_00 + 0x2c8);
        if (pUVar17 == (UVector2 *)0x0) goto LAB_00b6cb48;
LAB_00b6c9f2:
        if (*(Window **)(pUVar17 + 0xb0) != (Window *)0x0) {
          CEGUI::Window::removeChildWindow(*(Window **)(pUVar17 + 0xb0));
        }
        CEGUI::Window::addChildWindow(*(Window **)(this + 0x30));
        local_a4 = (float)((long)((float)(int)((float)(~uVar21 & uVar8 | uVar7 & uVar21) +
                                              fVar3 * 0.0) + fVar4) & 0xffffffff);
        local_9c = (float)(uVar20 & 0xffffffff);
        local_a8 = 0;
        local_a0 = 0;
                    /* try { // try from 00b6ca5c to 00b6ca60 has its CatchHandler @ 00b6dad6 */
        CEGUI::Window::setPosition(pUVar17);
        CEGUI::Window::getSize();
                    /* try { // try from 00b6ca7e to 00b6ca82 has its CatchHandler @ 00b6dade */
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
  cVar9 = CBaseUnit::ISA(*(CBaseUnit **)(this + 0x50),0x7f);
  if (cVar9 == '\0') {
    cVar9 = (**(code **)(*(long *)param_1 + 0x2f8))(param_1,*(undefined8 *)(this + 0x58),0);
    if (cVar9 == '\0') {
      cVar9 = (**(code **)(*(long *)param_1 + 0x2b0))(param_1);
      if (cVar9 == '\0') {
        pSVar19 = (String *)&local_1568;
        local_1560 = 0x20;
        local_1558 = 0;
        local_1548 = 0;
        local_1550 = 0;
        local_14c0 = (uint *)0x0;
        local_1568 = 0;
        local_1540[0] = 0;
        CEGUI::String::grow((ulong)pSVar19);
        puVar15 = local_1540;
        if (0x20 < local_1560) {
          puVar15 = local_14c0;
        }
        pbVar12 = (byte *)0xfe60e3;
        do {
          bVar6 = *pbVar12;
          pbVar12 = pbVar12 + 1;
          *puVar15 = (uint)bVar6;
          puVar15 = puVar15 + 1;
        } while (pbVar12 != (byte *)0xfe60ee);
        local_1568 = 0xb;
        puVar15 = local_1514;
        if (0x20 < local_1560) {
          puVar15 = local_14c0 + 0xb;
        }
        *puVar15 = 0;
                    /* try { // try from 00b6d6ad to 00b6d6c4 has its CatchHandler @ 00b6db65 */
        CEGUI::Imageset::getImage(*(String **)(this + 0x3440));
        CEGUI::PropertyHelper::imageToString(local_1618);
        local_16c0 = 0x20;
        local_16b8 = 0;
        local_16a8 = 0;
        local_16b0 = 0;
        local_1620 = (uint *)0x0;
        local_16c8 = 0;
        local_16a0[0] = 0;
                    /* try { // try from 00b6d728 to 00b6d72c has its CatchHandler @ 00b6db55 */
        CEGUI::String::grow((ulong)&local_16c8);
        puVar15 = local_16a0;
        if (0x20 < local_16c0) {
          puVar15 = local_1620;
        }
        pbVar12 = (byte *)0xfd0c0d;
        do {
          bVar6 = *pbVar12;
          pbVar12 = pbVar12 + 1;
          *puVar15 = (uint)bVar6;
          puVar15 = puVar15 + 1;
        } while (pbVar12 != (byte *)0xfd0c12);
        local_16c8 = 5;
        puVar15 = local_168c;
        if (0x20 < local_16c0) {
          puVar15 = local_1620 + 5;
        }
        *puVar15 = 0;
                    /* try { // try from 00b6d7a5 to 00b6d7a9 has its CatchHandler @ 00b6db47 */
        CEGUI::PropertySet::setProperty
                  (*(String **)(this + lVar16 * 8 + 0x14d8),(String *)&local_16c8);
                    /* try { // try from 00b6d7ad to 00b6d7b1 has its CatchHandler @ 00b6db55 */
        CEGUI::String::~String((String *)&local_16c8);
                    /* try { // try from 00b6d7b5 to 00b6d7b9 has its CatchHandler @ 00b6db65 */
        CEGUI::String::~String((String *)local_1618);
      }
      else {
        pSVar19 = (String *)&local_1358;
        local_1350 = 0x20;
        local_1348 = 0;
        local_1338 = 0;
        local_1340 = 0;
        local_12b0 = (uint *)0x0;
        local_1358 = 0;
        local_1330[0] = 0;
        CEGUI::String::grow((ulong)pSVar19);
        puVar15 = local_1330;
        if (0x20 < local_1350) {
          puVar15 = local_12b0;
        }
        pcVar13 = "blueredslotglow";
        do {
          bVar6 = *pcVar13;
          pcVar13 = pcVar13 + 1;
          *puVar15 = (uint)bVar6;
          puVar15 = puVar15 + 1;
        } while ((byte *)pcVar13 != (byte *)0xfe60ee);
        local_1358 = 0xf;
        puVar15 = local_12f4;
        if (0x20 < local_1350) {
          puVar15 = local_12b0 + 0xf;
        }
        *puVar15 = 0;
                    /* try { // try from 00b6d27d to 00b6d294 has its CatchHandler @ 00b6da63 */
        CEGUI::Imageset::getImage(*(String **)(this + 0x3440));
        CEGUI::PropertyHelper::imageToString(local_1408);
        local_14b0 = 0x20;
        local_14a8 = 0;
        local_1498 = 0;
        local_14a0 = 0;
        local_1410 = (uint *)0x0;
        local_14b8 = 0;
        local_1490[0] = 0;
                    /* try { // try from 00b6d2f8 to 00b6d2fc has its CatchHandler @ 00b6da5e */
        CEGUI::String::grow((ulong)&local_14b8);
        puVar15 = local_1490;
        if (0x20 < local_14b0) {
          puVar15 = local_1410;
        }
        pbVar12 = (byte *)0xfd0c0d;
        do {
          bVar6 = *pbVar12;
          pbVar12 = pbVar12 + 1;
          *puVar15 = (uint)bVar6;
          puVar15 = puVar15 + 1;
        } while (pbVar12 != (byte *)0xfd0c12);
        local_14b8 = 5;
        puVar15 = local_147c;
        if (0x20 < local_14b0) {
          puVar15 = local_1410 + 5;
        }
        *puVar15 = 0;
                    /* try { // try from 00b6d375 to 00b6d379 has its CatchHandler @ 00b6dbed */
        CEGUI::PropertySet::setProperty
                  (*(String **)(this + lVar16 * 8 + 0x14d8),(String *)&local_14b8);
                    /* try { // try from 00b6d37d to 00b6d381 has its CatchHandler @ 00b6da5e */
        CEGUI::String::~String((String *)&local_14b8);
                    /* try { // try from 00b6d385 to 00b6d389 has its CatchHandler @ 00b6da63 */
        CEGUI::String::~String((String *)local_1408);
      }
    }
    else {
      cVar9 = CBaseUnit::ISA((CBaseUnit *)param_1,0x36);
      if (cVar9 == '\0') {
        cVar9 = (**(code **)(*(long *)param_1 + 0x2b0))(param_1);
        if (cVar9 != '\0') {
          cVar9 = CBaseUnit::ISA((CBaseUnit *)param_1,0x37);
          if (cVar9 == '\0') {
            pSVar19 = local_fe8;
            CEGUI::String::String(pSVar19,"greenslotglow");
                    /* try { // try from 00b6d807 to 00b6d81e has its CatchHandler @ 00b6dc15 */
            CEGUI::Imageset::getImage(*(String **)(this + 0x3440));
            CEGUI::PropertyHelper::imageToString(local_1098);
                    /* try { // try from 00b6d82f to 00b6d833 has its CatchHandler @ 00b6dc05 */
            CEGUI::String::String(local_1148,"Image");
                    /* try { // try from 00b6d847 to 00b6d84b has its CatchHandler @ 00b6dbf5 */
            CEGUI::PropertySet::setProperty(*(String **)(this + lVar16 * 8 + 0x14d8),local_1148);
                    /* try { // try from 00b6d84f to 00b6d853 has its CatchHandler @ 00b6dc05 */
            CEGUI::String::~String(local_1148);
                    /* try { // try from 00b6d857 to 00b6d85b has its CatchHandler @ 00b6dc15 */
            CEGUI::String::~String((String *)local_1098);
          }
          else {
            pSVar19 = local_dd8;
            CEGUI::String::String(pSVar19,"blueslotglow");
                    /* try { // try from 00b6d9b4 to 00b6d9cb has its CatchHandler @ 00b6da59 */
            CEGUI::Imageset::getImage(*(String **)(this + 0x3440));
            CEGUI::PropertyHelper::imageToString(local_e88);
                    /* try { // try from 00b6d9dc to 00b6d9e0 has its CatchHandler @ 00b6da54 */
            CEGUI::String::String(local_f38,"Image");
                    /* try { // try from 00b6d9f4 to 00b6d9f8 has its CatchHandler @ 00b6da31 */
            CEGUI::PropertySet::setProperty(*(String **)(this + lVar16 * 8 + 0x14d8),local_f38);
                    /* try { // try from 00b6d9fc to 00b6da00 has its CatchHandler @ 00b6da54 */
            CEGUI::String::~String(local_f38);
                    /* try { // try from 00b6da04 to 00b6da08 has its CatchHandler @ 00b6da59 */
            CEGUI::String::~String((String *)local_e88);
          }
          CEGUI::String::~String(pSVar19);
          goto LAB_00b6cd2a;
        }
        pSVar19 = local_12a8;
        CEGUI::String::String(pSVar19,"");
                    /* try { // try from 00b6d96b to 00b6d96f has its CatchHandler @ 00b6db42 */
        CEGUI::String::String(local_11f8,"Image");
                    /* try { // try from 00b6d983 to 00b6d987 has its CatchHandler @ 00b6db3f */
        CEGUI::PropertySet::setProperty(*(String **)(this + lVar16 * 8 + 0x14d8),local_11f8);
                    /* try { // try from 00b6d98b to 00b6d98f has its CatchHandler @ 00b6db42 */
        CEGUI::String::~String(local_11f8);
      }
      else {
        pSVar19 = (String *)&local_bc8;
        local_bc0 = 0x20;
        local_bb8 = 0;
        local_ba8 = 0;
        local_bb0 = 0;
        local_b20 = (uint *)0x0;
        local_bc8 = 0;
        local_ba0[0] = 0;
        CEGUI::String::grow((ulong)pSVar19);
        puVar15 = local_ba0;
        if (0x20 < local_bc0) {
          puVar15 = local_b20;
        }
        pcVar13 = "goldslotglow";
        do {
          bVar6 = *pcVar13;
          pcVar13 = pcVar13 + 1;
          *puVar15 = (uint)bVar6;
          puVar15 = puVar15 + 1;
        } while ((byte *)pcVar13 != (byte *)0xfe60a7);
        local_bc8 = 0xc;
        puVar15 = local_b70;
        if (0x20 < local_bc0) {
          puVar15 = local_b20 + 0xc;
        }
        *puVar15 = 0;
                    /* try { // try from 00b6d085 to 00b6d09c has its CatchHandler @ 00b6dbe8 */
        CEGUI::Imageset::getImage(*(String **)(this + 0x3440));
        CEGUI::PropertyHelper::imageToString(local_c78);
        local_d20 = 0x20;
        local_d18 = 0;
        local_d08 = 0;
        local_d10 = 0;
        local_c80 = (uint *)0x0;
        local_d28 = 0;
        local_d00[0] = 0;
                    /* try { // try from 00b6d100 to 00b6d104 has its CatchHandler @ 00b6da74 */
        CEGUI::String::grow((ulong)&local_d28);
        puVar15 = local_d00;
        if (0x20 < local_d20) {
          puVar15 = local_c80;
        }
        pbVar12 = (byte *)0xfd0c0d;
        do {
          bVar6 = *pbVar12;
          pbVar12 = pbVar12 + 1;
          *puVar15 = (uint)bVar6;
          puVar15 = puVar15 + 1;
        } while (pbVar12 != (byte *)0xfd0c12);
        local_d28 = 5;
        puVar15 = local_cec;
        if (0x20 < local_d20) {
          puVar15 = local_c80 + 5;
        }
        *puVar15 = 0;
                    /* try { // try from 00b6d17d to 00b6d181 has its CatchHandler @ 00b6da72 */
        CEGUI::PropertySet::setProperty
                  (*(String **)(this + lVar16 * 8 + 0x14d8),(String *)&local_d28);
                    /* try { // try from 00b6d185 to 00b6d189 has its CatchHandler @ 00b6da74 */
        CEGUI::String::~String((String *)&local_d28);
                    /* try { // try from 00b6d18d to 00b6d191 has its CatchHandler @ 00b6dbe8 */
        CEGUI::String::~String((String *)local_c78);
      }
    }
  }
  else {
    pSVar19 = (String *)&local_b18;
    local_b10 = 0x20;
    local_b08 = 0;
    local_af8 = 0;
    local_b00 = 0;
    local_a70 = (undefined4 *)0x0;
    local_b18 = 0;
    local_af0[0] = 0;
    CEGUI::String::grow((ulong)pSVar19);
    local_b18 = 0;
    puVar14 = local_af0;
    if (0x20 < local_b10) {
      puVar14 = local_a70;
    }
    *puVar14 = 0;
    local_a60 = 0x20;
    local_a58 = 0;
    local_a48 = 0;
    local_a50 = 0;
    local_9c0 = (uint *)0x0;
    local_a68 = 0;
    local_a40[0] = 0;
                    /* try { // try from 00b6cc98 to 00b6cc9c has its CatchHandler @ 00b6dba5 */
    CEGUI::String::grow((ulong)&local_a68);
    puVar15 = local_a40;
    if (0x20 < local_a60) {
      puVar15 = local_9c0;
    }
    pbVar12 = (byte *)0xfd0c0d;
    do {
      bVar6 = *pbVar12;
      pbVar12 = pbVar12 + 1;
      *puVar15 = (uint)bVar6;
      puVar15 = puVar15 + 1;
    } while (pbVar12 != (byte *)0xfd0c12);
    local_a68 = 5;
    puVar15 = local_a2c;
    if (0x20 < local_a60) {
      puVar15 = local_9c0 + 5;
    }
    *puVar15 = 0;
                    /* try { // try from 00b6cd15 to 00b6cd19 has its CatchHandler @ 00b6db1a */
    CEGUI::PropertySet::setProperty(*(String **)(this + lVar16 * 8 + 0x14d8),(String *)&local_a68);
                    /* try { // try from 00b6cd1d to 00b6cd21 has its CatchHandler @ 00b6dba5 */
    CEGUI::String::~String((String *)&local_a68);
  }
  CEGUI::String::~String(pSVar19);
LAB_00b6cd2a:
  if (*(long *)(this + lVar16 * 8 + 0x2270) != 0) {
    bVar18 = SUB81(*(long *)(this + lVar16 * 8 + 0x2270),0);
    if (*(int *)(param_1 + 0x238) < 2) {
      CEGUI::Window::setVisible(bVar18);
    }
    else {
      CEGUI::Window::setVisible(bVar18);
      STRINGS::GetValueAsString((STRINGS *)local_58,*(int *)(param_1 + 0x238));
                    /* try { // try from 00b6cd82 to 00b6cd86 has its CatchHandler @ 00b6db2a */
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
                    /* try { // try from 00b6cdb0 to 00b6cdb4 has its CatchHandler @ 00b6da76 */
      CEGUI::String::String(local_1778,local_48[0]);
                    /* try { // try from 00b6cdc5 to 00b6cdc9 has its CatchHandler @ 00b6da8d */
      CEGUI::Window::setText(*(String **)(this + lVar16 * 8 + 0x2270));
                    /* try { // try from 00b6cdcd to 00b6cdd1 has its CatchHandler @ 00b6da76 */
      CEGUI::String::~String(local_1778);
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

/* address=00b6dc70
   symbol=CMerchantMenu::updateLayout */

/* WARNING: Removing unreachable block (ram,0x00b6ece2) */
/* WARNING: Removing unreachable block (ram,0x00b6ec88) */
/* CMerchantMenu::updateLayout() */

void __thiscall CMerchantMenu::updateLayout(CMerchantMenu *this)

{
  int *piVar1;
  byte bVar2;
  CInventory *pCVar3;
  Window *pWVar4;
  int iVar5;
  byte *pbVar6;
  uint *puVar7;
  undefined4 *puVar8;
  length_error *this_00;
  long *plVar9;
  uint uVar10;
  long lVar11;
  ulong uVar12;
  CEquipment *pCVar13;
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

  if (((this[0x60] != (CMerchantMenu)0x0) && (*(long *)(this + 0x50) != 0)) &&
     (pCVar3 = *(CInventory **)(*(long *)(this + 0x50) + 0x490), pCVar3 != (CInventory *)0x0)) {
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
                    /* try { // try from 00b6de4d to 00b6de51 has its CatchHandler @ 00b6ec5e */
      CEGUI::String::grow((ulong)&local_108);
      puVar7 = local_e0;
      if (0x20 < local_100) {
        puVar7 = local_60;
      }
      pbVar6 = (byte *)0xfd0c0d;
      do {
        bVar2 = *pbVar6;
        pbVar6 = pbVar6 + 1;
        *puVar7 = (uint)bVar2;
        puVar7 = puVar7 + 1;
      } while (pbVar6 != (byte *)0xfd0c12);
      local_108 = 5;
      puVar7 = local_cc;
      if (0x20 < local_100) {
        puVar7 = local_60 + 5;
      }
      *puVar7 = 0;
                    /* try { // try from 00b6dec5 to 00b6dec9 has its CatchHandler @ 00b6ec93 */
      CEGUI::PropertySet::setProperty(*(String **)(this + lVar11 + 0x1570),(String *)&local_108);
                    /* try { // try from 00b6decd to 00b6ded1 has its CatchHandler @ 00b6ec5e */
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
                    /* try { // try from 00b6dfca to 00b6dfce has its CatchHandler @ 00b6eca0 */
      CEGUI::String::grow((ulong)&local_268);
      pbVar6 = (byte *)0xfd0c0d;
      puVar7 = local_240;
      if (0x20 < local_260) {
        puVar7 = local_1c0;
      }
      do {
        bVar2 = *pbVar6;
        pbVar6 = pbVar6 + 1;
        *puVar7 = (uint)bVar2;
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
                    /* try { // try from 00b6e04a to 00b6e04e has its CatchHandler @ 00b6ecb8 */
      CEGUI::PropertySet::setProperty(*(String **)(this + lVar11 + 0x19f8),(String *)&local_268);
                    /* try { // try from 00b6e057 to 00b6e05b has its CatchHandler @ 00b6eca0 */
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
                    /* try { // try from 00b6e14f to 00b6e153 has its CatchHandler @ 00b6ecca */
      CEGUI::String::grow((ulong)&local_3c8);
      pbVar6 = (byte *)0xfd0c0d;
      puVar7 = local_3a0;
      if (0x20 < local_3c0) {
        puVar7 = local_320;
      }
      do {
        bVar2 = *pbVar6;
        pbVar6 = pbVar6 + 1;
        *puVar7 = (uint)bVar2;
        puVar7 = puVar7 + 1;
      } while (pbVar6 != (byte *)0xfd0c12);
      local_3c8 = 5;
      puVar7 = local_38c;
      if (0x20 < local_3c0) {
        puVar7 = local_320 + 5;
      }
      *puVar7 = 0;
                    /* try { // try from 00b6e1c5 to 00b6e1c9 has its CatchHandler @ 00b6eb90 */
      CEGUI::PropertySet::setProperty(*(String **)(this + lVar11 + 0x10e8),(String *)&local_3c8);
                    /* try { // try from 00b6e1cd to 00b6e1d1 has its CatchHandler @ 00b6ecca */
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
                    /* try { // try from 00b6e375 to 00b6e379 has its CatchHandler @ 00b6ec18 */
          std::string::string((string *)&local_48,
                              "Length for utf8 encoded string can not be \'npos\'",local_39);
          this_00 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00b6e38d to 00b6e391 has its CatchHandler @ 00b6ec1d */
          std::length_error::length_error(this_00,(string *)&local_48);
          if ((allocator *)(local_48 + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_48 + -8);
            iVar5 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar5 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_48 + -0x18));
            }
          }
          goto LAB_00b6e3ab;
        }
        CEGUI::String::grow((ulong)&local_528);
        local_528 = 0;
        puVar8 = local_500;
        if (0x20 < local_520) {
          puVar8 = local_480;
        }
        *puVar8 = 0;
                    /* try { // try from 00b6e28b to 00b6e28f has its CatchHandler @ 00b6ebb0 */
        CEGUI::Window::setText(*(String **)(this + lVar11 + 0x2308));
        CEGUI::String::~String((String *)&local_528);
      }
      lVar11 = lVar11 + 8;
    } while (lVar11 != 0x3f0);
    if (*(int *)(pCVar3 + 0x38) != 0) {
      uVar12 = 0;
      do {
        uVar10 = (uint)uVar12;
        if (uVar10 < *(uint *)(pCVar3 + 0x3c)) {
          plVar9 = *(long **)(pCVar3 + 0x30);
          lVar11 = plVar9[uVar12];
          pCVar13 = *(CEquipment **)(lVar11 + 0x10);
        }
        else {
          plVar9 = *(long **)(pCVar3 + 0x30);
          lVar11 = *plVar9;
          pCVar13 = *(CEquipment **)(lVar11 + 0x10);
        }
        if (0x12 < *(int *)(lVar11 + 0x18)) {
          if (uVar10 < *(uint *)(pCVar3 + 0x3c)) {
            plVar9 = (long *)(uVar12 * 8 + *(long *)(pCVar3 + 0x30));
          }
          iVar5 = CInventory::getItemPane(pCVar3,*(uint *)(*plVar9 + 0x18));
          if (iVar5 == *(int *)(this + 0x3454)) {
            if (uVar10 < *(uint *)(pCVar3 + 0x3c)) {
              plVar9 = (long *)(uVar12 * 8 + *(long *)(pCVar3 + 0x30));
            }
            else {
              plVar9 = *(long **)(pCVar3 + 0x30);
            }
            setSlotIcon(this,pCVar13,*(int *)(*plVar9 + 0x18),*(int *)(*plVar9 + 0x18));
          }
        }
        uVar12 = (ulong)(uVar10 + 1);
      } while (uVar10 + 1 < *(uint *)(pCVar3 + 0x38));
    }
    plVar9 = *(long **)(*(long *)(this + 0x58) + 0x648);
    if (((*(long *)(*(long *)(this + 0x58) + 0x650) - (long)plVar9 >> 3 != 0) &&
        (lVar11 = *plVar9, lVar11 != 0)) &&
       (pCVar3 = *(CInventory **)(lVar11 + 0x490), pCVar3 != (CInventory *)0x0)) {
      lVar11 = 0;
      do {
        pWVar4 = *(Window **)(this + lVar11 + 0x2790);
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
                    /* try { // try from 00b6e565 to 00b6e569 has its CatchHandler @ 00b6eb8b */
        CEGUI::String::grow((ulong)&local_5d8);
        puVar7 = local_5b0;
        if (0x20 < local_5d0) {
          puVar7 = local_530;
        }
        pbVar6 = (byte *)0xfd0c0d;
        do {
          bVar2 = *pbVar6;
          pbVar6 = pbVar6 + 1;
          *puVar7 = (uint)bVar2;
          puVar7 = puVar7 + 1;
        } while (pbVar6 != (byte *)0xfd0c12);
        local_5d8 = 5;
        puVar7 = local_59c;
        if (0x20 < local_5d0) {
          puVar7 = local_530 + 5;
        }
        *puVar7 = 0;
                    /* try { // try from 00b6e5e7 to 00b6e5eb has its CatchHandler @ 00b6eb6b */
        CEGUI::PropertySet::setProperty(*(String **)(this + lVar11 + 0x2cb0),(String *)&local_5d8);
                    /* try { // try from 00b6e5ef to 00b6e5f3 has its CatchHandler @ 00b6eb8b */
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
                    /* try { // try from 00b6e6ec to 00b6e6f0 has its CatchHandler @ 00b6ebc3 */
        CEGUI::String::grow((ulong)&local_738);
        pbVar6 = (byte *)0xfd0c0d;
        puVar7 = local_710;
        if (0x20 < local_730) {
          puVar7 = local_690;
        }
        do {
          bVar2 = *pbVar6;
          pbVar6 = pbVar6 + 1;
          *puVar7 = (uint)bVar2;
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
                    /* try { // try from 00b6e76c to 00b6e770 has its CatchHandler @ 00b6ec06 */
        CEGUI::PropertySet::setProperty(*(String **)(this + lVar11 + 0x2f40),(String *)&local_738);
                    /* try { // try from 00b6e779 to 00b6e77d has its CatchHandler @ 00b6ebc3 */
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
                    /* try { // try from 00b6e871 to 00b6e875 has its CatchHandler @ 00b6ebee */
        CEGUI::String::grow((ulong)&local_898);
        pbVar6 = (byte *)0xfd0c0d;
        puVar7 = local_870;
        if (0x20 < local_890) {
          puVar7 = local_7f0;
        }
        do {
          bVar2 = *pbVar6;
          pbVar6 = pbVar6 + 1;
          *puVar7 = (uint)bVar2;
          puVar7 = puVar7 + 1;
        } while (pbVar6 != (byte *)0xfd0c12);
        local_898 = 5;
        puVar7 = local_85c;
        if (0x20 < local_890) {
          puVar7 = local_7f0 + 5;
        }
        *puVar7 = 0;
                    /* try { // try from 00b6e8ef to 00b6e8f3 has its CatchHandler @ 00b6ecd2 */
        CEGUI::PropertySet::setProperty(*(String **)(this + lVar11 + 0x2a20),(String *)&local_898);
                    /* try { // try from 00b6e8f7 to 00b6e8fb has its CatchHandler @ 00b6ebee */
        CEGUI::String::~String((String *)&local_898);
        CEGUI::String::~String((String *)&local_948);
        if (*(long *)(this + lVar11 + 0x31d0) != 0) {
          local_9f0 = 0x20;
          local_9e8 = 0;
          local_9d8 = 0;
          local_9e0 = 0;
          local_950 = (undefined4 *)0x0;
          local_9f8 = 0;
          local_9d0[0] = 0;
          if (CEGUI::String::npos == 0) {
                    /* try { // try from 00b6ead4 to 00b6ead8 has its CatchHandler @ 00b6ed08 */
            std::string::string((string *)local_58,
                                "Length for utf8 encoded string can not be \'npos\'",local_3b);
            this_00 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00b6eaec to 00b6eaf0 has its CatchHandler @ 00b6ecf0 */
            std::length_error::length_error(this_00,(string *)local_58);
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
LAB_00b6e3ab:
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
                    /* try { // try from 00b6e99d to 00b6e9a1 has its CatchHandler @ 00b6ebdb */
          CEGUI::Window::setText(*(String **)(this + lVar11 + 0x31d0));
          CEGUI::String::~String((String *)&local_9f8);
        }
        lVar11 = lVar11 + 8;
      } while (lVar11 != 0x1f8);
      if (*(int *)(pCVar3 + 0x38) != 0) {
        uVar12 = 0;
        do {
          uVar10 = (uint)uVar12;
          if (uVar10 < *(uint *)(pCVar3 + 0x3c)) {
            plVar9 = *(long **)(pCVar3 + 0x30);
            lVar11 = plVar9[uVar12];
            pCVar13 = *(CEquipment **)(lVar11 + 0x10);
          }
          else {
            plVar9 = *(long **)(pCVar3 + 0x30);
            lVar11 = *plVar9;
            pCVar13 = *(CEquipment **)(lVar11 + 0x10);
          }
          if (0x12 < *(int *)(lVar11 + 0x18)) {
            if (uVar10 < *(uint *)(pCVar3 + 0x3c)) {
              plVar9 = (long *)(uVar12 * 8 + *(long *)(pCVar3 + 0x30));
            }
            iVar5 = CInventory::getItemPane(pCVar3,*(uint *)(*plVar9 + 0x18));
            if (iVar5 == *(int *)(this + 0x3458)) {
              if (uVar10 < *(uint *)(pCVar3 + 0x3c)) {
                plVar9 = (long *)(uVar12 * 8 + *(long *)(pCVar3 + 0x30));
              }
              else {
                plVar9 = *(long **)(pCVar3 + 0x30);
              }
              setPetSlotIcon(this,pCVar13,*(int *)(*plVar9 + 0x18),*(int *)(*plVar9 + 0x18));
            }
          }
          uVar12 = (ulong)(uVar10 + 1);
        } while (uVar10 + 1 < *(uint *)(pCVar3 + 0x38));
      }
    }
    CEGUI::Window::moveToBack();
    CEGUI::Window::moveToFront();
    CEGUI::Window::moveToFront();
    CEGUI::Window::moveToFront();
    CEGUI::Window::moveToFront();
  }
  return;
}

/* address=00b6ed20
   symbol=CMerchantMenu::createMenus */

/* WARNING: Removing unreachable block (ram,0x00b76fac) */
/* WARNING: Removing unreachable block (ram,0x00b770ee) */
/* WARNING: Removing unreachable block (ram,0x00b76539) */
/* WARNING: Removing unreachable block (ram,0x00b76217) */
/* WARNING: Removing unreachable block (ram,0x00b763ac) */
/* WARNING: Removing unreachable block (ram,0x00b75f06) */
/* WARNING: Removing unreachable block (ram,0x00b761e4) */
/* WARNING: Removing unreachable block (ram,0x00b76e4a) */
/* WARNING: Removing unreachable block (ram,0x00b76ee7) */
/* WARNING: Removing unreachable block (ram,0x00b76e3f) */
/* WARNING: Removing unreachable block (ram,0x00b76ca8) */
/* WARNING: Removing unreachable block (ram,0x00b76861) */
/* WARNING: Removing unreachable block (ram,0x00b76a1f) */
/* WARNING: Removing unreachable block (ram,0x00b76856) */
/* WARNING: Removing unreachable block (ram,0x00b76cb3) */
/* WARNING: Removing unreachable block (ram,0x00b76bb8) */
/* WARNING: Removing unreachable block (ram,0x00b761ef) */
/* WARNING: Removing unreachable block (ram,0x00b763ba) */
/* WARNING: Removing unreachable block (ram,0x00b76685) */
/* WARNING: Removing unreachable block (ram,0x00b7674c) */
/* WARNING: Removing unreachable block (ram,0x00b76085) */
/* WARNING: Removing unreachable block (ram,0x00b77221) */
/* WARNING: Removing unreachable block (ram,0x00b77087) */
/* WARNING: Removing unreachable block (ram,0x00b7728f) */
/* WARNING: Removing unreachable block (ram,0x00b7714f) */
/* WARNING: Removing unreachable block (ram,0x00b77095) */
/* WARNING: Removing unreachable block (ram,0x00b7720c) */
/* WARNING: Removing unreachable block (ram,0x00b76432) */
/* WARNING: Removing unreachable block (ram,0x00b76bc3) */
/* WARNING: Removing unreachable block (ram,0x00b7643d) */
/* WARNING: Removing unreachable block (ram,0x00b762f7) */
/* WARNING: Removing unreachable block (ram,0x00b76031) */
/* WARNING: Removing unreachable block (ram,0x00b765b1) */
/* WARNING: Removing unreachable block (ram,0x00b76ef2) */
/* WARNING: Removing unreachable block (ram,0x00b765bc) */
/* WARNING: Removing unreachable block (ram,0x00b76f4b) */
/* WARNING: Removing unreachable block (ram,0x00b764cb) */
/* WARNING: Removing unreachable block (ram,0x00b7652e) */
/* WARNING: Removing unreachable block (ram,0x00b764c0) */
/* CMerchantMenu::createMenus() */

void __thiscall CMerchantMenu::createMenus(CMerchantMenu *this)

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
  CMerchantMenu *pCVar26;
  char *pcVar27;
  char *pcVar28;
  long lVar29;
  bool bVar30;
  float fVar31;
  float fVar32;
  int local_3ea4;
  CMerchantMenu *local_3e90;
  undefined8 local_3e88;
  ulong local_3e80;
  undefined8 local_3e78;
  undefined8 local_3e70;
  undefined8 local_3e68;
  undefined4 local_3e60 [32];
  undefined4 *local_3de0;
  long local_3dd8;
  ulong local_3dd0;
  undefined8 local_3dc8;
  undefined8 local_3dc0;
  undefined8 local_3db8;
  undefined4 local_3db0 [32];
  undefined4 *local_3d30;
  long local_3d28;
  ulong local_3d20;
  undefined8 local_3d18;
  undefined8 local_3d10;
  undefined8 local_3d08;
  uint local_3d00 [32];
  uint *local_3c80;
  undefined8 local_3c78;
  ulong local_3c70;
  undefined8 local_3c68;
  undefined8 local_3c60;
  undefined8 local_3c58;
  undefined4 local_3c50 [32];
  undefined4 *local_3bd0;
  long local_3bc8;
  ulong local_3bc0;
  undefined8 local_3bb8;
  undefined8 local_3bb0;
  undefined8 local_3ba8;
  undefined4 local_3ba0 [32];
  undefined4 *local_3b20;
  long local_3b18;
  ulong local_3b10;
  undefined8 local_3b08;
  undefined8 local_3b00;
  undefined8 local_3af8;
  uint local_3af0 [32];
  uint *local_3a70;
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
  uint local_3830 [10];
  uint local_3808 [22];
  uint *local_37b0;
  String local_37a8 [176];
  undefined8 local_36f8;
  ulong local_36f0;
  undefined8 local_36e8;
  undefined8 local_36e0;
  undefined8 local_36d8;
  undefined4 local_36d0 [32];
  undefined4 *local_3650;
  undefined8 local_3648;
  ulong local_3640;
  undefined8 local_3638;
  undefined8 local_3630;
  undefined8 local_3628;
  uint local_3620 [13];
  uint local_35ec [19];
  uint *local_35a0;
  undefined8 local_3598;
  ulong local_3590;
  undefined8 local_3588;
  undefined8 local_3580;
  undefined8 local_3578;
  uint local_3570 [14];
  uint local_3538 [18];
  uint *local_34f0;
  undefined8 local_34e8;
  ulong local_34e0;
  undefined8 local_34d8;
  undefined8 local_34d0;
  undefined8 local_34c8;
  uint local_34c0 [12];
  uint local_3490 [20];
  uint *local_3440;
  undefined8 local_3438;
  ulong local_3430;
  undefined8 local_3428;
  undefined8 local_3420;
  undefined8 local_3418;
  uint local_3410 [18];
  uint local_33c8 [14];
  uint *local_3390;
  undefined8 local_3388;
  ulong local_3380;
  undefined8 local_3378;
  undefined8 local_3370;
  undefined8 local_3368;
  uint local_3360 [5];
  uint local_334c [27];
  uint *local_32e0;
  undefined8 local_32d8;
  ulong local_32d0;
  undefined8 local_32c8;
  undefined8 local_32c0;
  undefined8 local_32b8;
  undefined4 local_32b0 [32];
  undefined4 *local_3230;
  long local_3228;
  ulong local_3220;
  undefined8 local_3218;
  undefined8 local_3210;
  undefined8 local_3208;
  undefined4 local_3200 [32];
  undefined4 *local_3180;
  long local_3178;
  ulong local_3170;
  undefined8 local_3168;
  undefined8 local_3160;
  undefined8 local_3158;
  uint local_3150 [32];
  uint *local_30d0;
  long local_30c8;
  ulong local_30c0;
  undefined8 local_30b8;
  undefined8 local_30b0;
  undefined8 local_30a8;
  undefined4 local_30a0 [32];
  undefined4 *local_3020;
  undefined8 local_3018;
  ulong local_3010;
  undefined8 local_3008;
  undefined8 local_3000;
  undefined8 local_2ff8;
  uint local_2ff0 [12];
  uint local_2fc0 [20];
  uint *local_2f70;
  undefined8 local_2f68;
  ulong local_2f60;
  undefined8 local_2f58;
  undefined8 local_2f50;
  undefined8 local_2f48;
  uint local_2f40 [14];
  uint local_2f08 [18];
  uint *local_2ec0;
  undefined8 local_2eb8;
  ulong local_2eb0;
  undefined8 local_2ea8;
  undefined8 local_2ea0;
  undefined8 local_2e98;
  uint local_2e90 [17];
  uint local_2e4c [15];
  uint *local_2e10;
  undefined8 local_2e08;
  ulong local_2e00;
  undefined8 local_2df8;
  undefined8 local_2df0;
  undefined8 local_2de8;
  uint local_2de0 [7];
  uint local_2dc4 [25];
  uint *local_2d60;
  undefined8 local_2d58;
  ulong local_2d50;
  undefined8 local_2d48;
  undefined8 local_2d40;
  undefined8 local_2d38;
  uint local_2d30 [8];
  uint local_2d10 [24];
  uint *local_2cb0;
  undefined8 local_2ca8;
  ulong local_2ca0;
  undefined8 local_2c98;
  undefined8 local_2c90;
  undefined8 local_2c88;
  uint local_2c80 [11];
  uint local_2c54 [21];
  uint *local_2c00;
  undefined8 local_2bf8;
  ulong local_2bf0;
  undefined8 local_2be8;
  undefined8 local_2be0;
  undefined8 local_2bd8;
  undefined4 local_2bd0 [32];
  undefined4 *local_2b50;
  long local_2b48;
  ulong local_2b40;
  undefined8 local_2b38;
  undefined8 local_2b30;
  undefined8 local_2b28;
  undefined4 local_2b20 [32];
  undefined4 *local_2aa0;
  long local_2a98;
  ulong local_2a90;
  undefined8 local_2a88;
  undefined8 local_2a80;
  undefined8 local_2a78;
  uint local_2a70 [32];
  uint *local_29f0;
  undefined8 local_29e8;
  ulong local_29e0;
  undefined8 local_29d8;
  undefined8 local_29d0;
  undefined8 local_29c8;
  undefined4 local_29c0 [32];
  undefined4 *local_2940;
  long local_2938;
  ulong local_2930;
  undefined8 local_2928;
  undefined8 local_2920;
  undefined8 local_2918;
  undefined4 local_2910 [32];
  undefined4 *local_2890;
  long local_2888;
  ulong local_2880;
  undefined8 local_2878;
  undefined8 local_2870;
  undefined8 local_2868;
  uint local_2860 [32];
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
  uint local_25a0 [10];
  uint local_2578 [22];
  uint *local_2520;
  String local_2518 [176];
  undefined8 local_2468;
  ulong local_2460;
  undefined8 local_2458;
  undefined8 local_2450;
  undefined8 local_2448;
  undefined4 local_2440 [32];
  undefined4 *local_23c0;
  undefined8 local_23b8;
  ulong local_23b0;
  undefined8 local_23a8;
  undefined8 local_23a0;
  undefined8 local_2398;
  uint local_2390 [10];
  uint local_2368 [22];
  uint *local_2310;
  undefined8 local_2308;
  ulong local_2300;
  undefined8 local_22f8;
  undefined8 local_22f0;
  undefined8 local_22e8;
  uint local_22e0 [14];
  uint local_22a8 [18];
  uint *local_2260;
  undefined8 local_2258;
  ulong local_2250;
  undefined8 local_2248;
  undefined8 local_2240;
  undefined8 local_2238;
  uint local_2230 [12];
  uint local_2200 [20];
  uint *local_21b0;
  undefined8 local_21a8;
  ulong local_21a0;
  undefined8 local_2198;
  undefined8 local_2190;
  undefined8 local_2188;
  uint local_2180 [18];
  uint local_2138 [14];
  uint *local_2100;
  undefined8 local_20f8;
  ulong local_20f0;
  undefined8 local_20e8;
  undefined8 local_20e0;
  undefined8 local_20d8;
  uint local_20d0 [5];
  uint local_20bc [27];
  uint *local_2050;
  undefined8 local_2048;
  ulong local_2040;
  undefined8 local_2038;
  undefined8 local_2030;
  undefined8 local_2028;
  undefined4 local_2020 [32];
  undefined4 *local_1fa0;
  long local_1f98;
  ulong local_1f90;
  undefined8 local_1f88;
  undefined8 local_1f80;
  undefined8 local_1f78;
  undefined4 local_1f70 [32];
  undefined4 *local_1ef0;
  long local_1ee8;
  ulong local_1ee0;
  undefined8 local_1ed8;
  undefined8 local_1ed0;
  undefined8 local_1ec8;
  uint local_1ec0 [32];
  uint *local_1e40;
  long local_1e38;
  ulong local_1e30;
  undefined8 local_1e28;
  undefined8 local_1e20;
  undefined8 local_1e18;
  undefined4 local_1e10 [32];
  undefined4 *local_1d90;
  undefined8 local_1d88;
  ulong local_1d80;
  undefined8 local_1d78;
  undefined8 local_1d70;
  undefined8 local_1d68;
  uint local_1d60 [10];
  uint local_1d38 [22];
  uint *local_1ce0;
  undefined8 local_1cd8;
  ulong local_1cd0;
  undefined8 local_1cc8;
  undefined8 local_1cc0;
  undefined8 local_1cb8;
  uint local_1cb0 [12];
  uint local_1c80 [20];
  uint *local_1c30;
  undefined8 local_1c28;
  ulong local_1c20;
  undefined8 local_1c18;
  undefined8 local_1c10;
  undefined8 local_1c08;
  uint local_1c00 [9];
  uint local_1bdc [23];
  uint *local_1b80;
  undefined8 local_1b78;
  ulong local_1b70;
  undefined8 local_1b68;
  undefined8 local_1b60;
  undefined8 local_1b58;
  uint local_1b50 [8];
  uint local_1b30 [24];
  uint *local_1ad0;
  undefined8 local_1ac8;
  ulong local_1ac0;
  undefined8 local_1ab8;
  undefined8 local_1ab0;
  undefined8 local_1aa8;
  uint local_1aa0 [9];
  uint local_1a7c [23];
  uint *local_1a20;
  undefined8 local_1a18;
  ulong local_1a10;
  undefined8 local_1a08;
  undefined8 local_1a00;
  undefined8 local_19f8;
  uint local_19f0 [7];
  uint local_19d4 [25];
  uint *local_1970;
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
                    /* try { // try from 00b6edf1 to 00b6ef7a has its CatchHandler @ 00b76d45 */
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
                    /* try { // try from 00b743e4 to 00b743e8 has its CatchHandler @ 00b771c0 */
    std::string::string((string *)local_278,"Length for utf8 encoded string can not be \'npos\'",
                        &local_42);
    plVar21 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00b743fc to 00b74400 has its CatchHandler @ 00b771f4 */
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
                    /* try { // try from 00b74427 to 00b7442b has its CatchHandler @ 00b76d45 */
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
    if (pcVar27 == (char *)0x0) goto LAB_00b6f12d;
LAB_00b6ef9a:
    bVar30 = local_620 != 0;
LAB_00b6efa0:
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
            goto LAB_00b6efb3;
          }
          uVar9 = uVar9 + 2;
          *puVar20 = (byte)"GuiLook"[uVar8] & 0x3f | (uVar23 & 0x1f) << 6;
        }
        else {
LAB_00b6efb3:
          *puVar20 = uVar23;
          uVar9 = uVar8;
        }
        pcVar13 = (char *)(ulong)uVar9;
        if ((pcVar27 <= pcVar13) || (uVar22 = uVar22 - 1, uVar22 == 0)) break;
        puVar20 = puVar20 + 1;
      } while( true );
    }
  }
  else {
    puVar20 = local_580;
    if (pcVar27 != (char *)0x0) goto LAB_00b6ef9a;
LAB_00b6f12d:
    if (s_GuiLook_00fe493c[0] != '\0') {
      do {
        pcVar13 = pcVar13 + 1;
        pcVar27 = pcVar13 + -0xfe493c;
      } while (*pcVar13 != '\0');
      bVar30 = pcVar27 != (char *)0x0 && local_620 != 0;
      goto LAB_00b6efa0;
    }
  }
  puVar20 = local_600;
  if (0x20 < local_620) {
    puVar20 = local_580;
  }
  puVar20[lVar11] = 0;
  local_628 = lVar11;
                    /* try { // try from 00b6f041 to 00b6f045 has its CatchHandler @ 00b76dd2 */
  CEGUI::ImagesetManager::getImageset(CEGUI::Singleton<CEGUI::ImagesetManager>::ms_Singleton);
                    /* try { // try from 00b6f049 to 00b6f1f2 has its CatchHandler @ 00b76d45 */
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
                    /* try { // try from 00b744a4 to 00b744a8 has its CatchHandler @ 00b7716c */
    std::string::string((string *)local_288,"Length for utf8 encoded string can not be \'npos\'",
                        local_44);
    plVar21 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00b744bc to 00b744c0 has its CatchHandler @ 00b77137 */
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
                    /* try { // try from 00b744e7 to 00b744eb has its CatchHandler @ 00b76d45 */
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
      goto LAB_00b6f21c;
    }
  }
  else {
    bVar30 = local_6d0 != 0;
LAB_00b6f21c:
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
            goto LAB_00b6f233;
          }
          uVar9 = uVar9 + 2;
          *puVar20 = (byte)"UIIcons"[uVar8] & 0x3f | (uVar23 & 0x1f) << 6;
        }
        else {
LAB_00b6f233:
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
                    /* try { // try from 00b6f2c1 to 00b6f2c5 has its CatchHandler @ 00b76e75 */
  uVar10 = CEGUI::ImagesetManager::getImageset
                     (CEGUI::Singleton<CEGUI::ImagesetManager>::ms_Singleton);
  *(undefined8 *)(this + 0x3440) = uVar10;
                    /* try { // try from 00b6f2d0 to 00b6f339 has its CatchHandler @ 00b76d45 */
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
  pcVar27 = (char *)0x0;
  pcVar13 = "MerchantSheet";
  local_830 = 0x20;
  local_828 = 0;
  local_818 = 0;
  local_820 = 0;
  pcVar28 = "MerchantSheet";
  local_790 = (uint *)0x0;
  local_838 = 0;
  local_810[0] = 0;
  cVar2 = s_MerchantSheet_00feffb6[0];
  while (pcVar28 = pcVar28 + 1, cVar2 != '\0') {
    pcVar27 = pcVar28 + -0xfeffb6;
    cVar2 = *pcVar28;
  }
  if (pcVar27 == CEGUI::String::npos) {
                    /* try { // try from 00b74564 to 00b74568 has its CatchHandler @ 00b770a0 */
    std::string::string((string *)local_298,"Length for utf8 encoded string can not be \'npos\'",
                        local_46);
    plVar21 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00b7457c to 00b74580 has its CatchHandler @ 00b77047 */
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
                    /* try { // try from 00b745a7 to 00b745ab has its CatchHandler @ 00b76995 */
    __cxa_throw(plVar21,&std::length_error::typeinfo,std::length_error::~length_error);
  }
  lVar11 = 0;
  pcVar28 = pcVar27;
  pbVar15 = (byte *)"MerchantSheet";
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
                    /* try { // try from 00b6f49e to 00b6f4a2 has its CatchHandler @ 00b76995 */
  CEGUI::String::grow((ulong)&local_838);
  puVar20 = local_810;
  if (0x20 < local_830) {
    puVar20 = local_790;
  }
  if (pcVar27 == (char *)0x0) {
    if (s_MerchantSheet_00feffb6[0] != '\0') {
      do {
        pcVar13 = pcVar13 + 1;
        pcVar27 = pcVar13 + -0xfeffb6;
      } while (*pcVar13 != '\0');
      bVar30 = pcVar27 != (char *)0x0 && local_830 != 0;
      goto LAB_00b6f4cc;
    }
  }
  else {
    bVar30 = local_830 != 0;
LAB_00b6f4cc:
    if (bVar30) {
      pcVar13 = (char *)0x0;
      uVar9 = 0;
      uVar22 = local_830;
      do {
        bVar3 = pcVar13[0xfeffb6];
        uVar23 = (uint)bVar3;
        uVar8 = uVar9 + 1;
        if ((char)bVar3 < '\0') {
          uVar23 = (uint)bVar3;
          if (0xdf < bVar3) {
            if (bVar3 < 0xf0) {
              uVar25 = (ulong)uVar8;
              uVar8 = uVar9 + 3;
              uVar23 = (byte)"MerchantSheet"[uVar9 + 2] & 0x3f | (uVar23 & 0xf) << 0xc |
                       ((byte)"MerchantSheet"[uVar25] & 0x3f) << 6;
            }
            else {
              uVar25 = (ulong)uVar8;
              uVar8 = uVar9 + 4;
              uVar23 = ((byte)"MerchantSheet"[uVar25] & 0x3f) << 0xc |
                       (byte)"MerchantSheet"[uVar9 + 3] & 0x3f | (uVar23 & 7) << 0x12 |
                       ((byte)"MerchantSheet"[uVar9 + 2] & 0x3f) << 6;
            }
            goto LAB_00b6f4e3;
          }
          uVar9 = uVar9 + 2;
          *puVar20 = (byte)"MerchantSheet"[uVar8] & 0x3f | (uVar23 & 0x1f) << 6;
        }
        else {
LAB_00b6f4e3:
          *puVar20 = uVar23;
          uVar9 = uVar8;
        }
        pcVar13 = (char *)(ulong)uVar9;
        if ((pcVar27 <= pcVar13) || (uVar22 = uVar22 - 1, uVar22 == 0)) break;
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
                    /* try { // try from 00b6f577 to 00b6f57b has its CatchHandler @ 00b769a5 */
  CEGUI::String::String(local_788,(uchar *)"DefaultWindow");
                    /* try { // try from 00b6f58c to 00b6f590 has its CatchHandler @ 00b76aa5 */
  uVar10 = CEGUI::WindowManager::createWindow
                     (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,local_788,
                      (String *)&local_838);
  *(undefined8 *)(this + 0x20) = uVar10;
                    /* try { // try from 00b6f598 to 00b6f59c has its CatchHandler @ 00b769a5 */
  CEGUI::String::~String(local_788);
                    /* try { // try from 00b6f5a0 to 00b6f5a4 has its CatchHandler @ 00b76995 */
  CEGUI::String::~String((String *)&local_838);
                    /* try { // try from 00b6f5a8 to 00b6f5ac has its CatchHandler @ 00b76d45 */
  CEGUI::String::~String((String *)&local_8e8);
  local_354 = 0;
  local_358 = 0x3f800000;
  local_34c = 0;
  local_350 = 0x3f800000;
                    /* try { // try from 00b6f5e5 to 00b6f5e9 has its CatchHandler @ 00b76ab5 */
  CEGUI::Window::setSize(*(UVector2 **)(this + 0x20));
  local_a40 = 0x20;
  local_a38 = 0;
  local_a28 = 0;
  local_a30 = 0;
  local_9a0 = (uint *)0x0;
  local_a48 = 0;
  local_a20[0] = 0;
                    /* try { // try from 00b6f64d to 00b6f651 has its CatchHandler @ 00b76d45 */
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
                    /* try { // try from 00b6f715 to 00b6f719 has its CatchHandler @ 00b76abd */
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
                    /* try { // try from 00b6f78d to 00b6f791 has its CatchHandler @ 00b76acd */
  CEGUI::PropertySet::setProperty(*(String **)(this + 0x20),(String *)&local_998);
                    /* try { // try from 00b6f795 to 00b6f799 has its CatchHandler @ 00b76abd */
  CEGUI::String::~String((String *)&local_998);
                    /* try { // try from 00b6f79d to 00b6f7a1 has its CatchHandler @ 00b76d45 */
  CEGUI::String::~String((String *)&local_a48);
  local_364 = 0;
  local_368 = 0;
  local_35c = 0;
  local_360 = 0;
                    /* try { // try from 00b6f7da to 00b6f7de has its CatchHandler @ 00b76ada */
  CEGUI::Window::setPosition(*(UVector2 **)(this + 0x20));
  *(undefined1 *)(*(long *)(this + 0x20) + 0x3e2) = 1;
                    /* try { // try from 00b6f7f0 to 00b6f80a has its CatchHandler @ 00b76d45 */
  CEGUI::Window::setZOrderingEnabled(SUB81(*(undefined8 *)(this + 0x20),0));
  pcVar4 = *(code **)(*(long *)(*(long *)(this + 0x20) + 0x38) + 0x10);
  local_88[0] = operator_new(0x20);
  *local_88[0] = &PTR__MemberFunctionSlot_00ff0270;
  local_88[0][2] = 0;
  local_88[0][1] = handle_MouseThrough;
  local_88[0][3] = this;
                    /* try { // try from 00b6f84e to 00b6f883 has its CatchHandler @ 00b76adc */
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
                    /* try { // try from 00b6f8b4 to 00b6f8b8 has its CatchHandler @ 00b76d45 */
  CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_88);
  local_578 = &DAT_01423a38;
                    /* try { // try from 00b6f8d6 to 00b6f8da has its CatchHandler @ 00b76aec */
  std::string::string((string *)&local_570,(string *)&::EMPTY_STRING);
                    /* try { // try from 00b6f8ec to 00b6f8f0 has its CatchHandler @ 00b76b01 */
  std::wstring::wstring((wstring_conflict *)&local_568,(wstring_conflict *)&::EMPTY_WSTRING);
  local_560 = 4;
  local_55c = 3;
  local_558 = &DAT_01423a38;
  local_550 = 0;
                    /* try { // try from 00b6f933 to 00b6f937 has its CatchHandler @ 00b769b2 */
  std::wstring::wstring((wstring_conflict *)local_98,L"media/ui/merchantmenu.layout",local_39);
                    /* try { // try from 00b6f938 to 00b6f95a has its CatchHandler @ 00b769b7 */
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
                    /* try { // try from 00b6f9e1 to 00b6f9e5 has its CatchHandler @ 00b769f6 */
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
                    /* try { // try from 00b6fa5e to 00b6fa62 has its CatchHandler @ 00b76a1a */
  pSVar14 = (String *)
            CEGUI::WindowManager::loadWindowLayout
                      (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,
                       SUB81((String *)&local_af8,0));
                    /* try { // try from 00b6fa69 to 00b6fafa has its CatchHandler @ 00b769f6 */
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
                    /* try { // try from 00b6fb68 to 00b6fb6c has its CatchHandler @ 00b769fb */
  pSVar16 = (String *)CEGUI::Window::recursiveChildSearch(pSVar14);
                    /* try { // try from 00b6fb73 to 00b6fbfb has its CatchHandler @ 00b769f6 */
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
                    /* try { // try from 00b6fcc5 to 00b6fcc9 has its CatchHandler @ 00b76a05 */
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
                    /* try { // try from 00b6fd38 to 00b6fd3c has its CatchHandler @ 00b76a2a */
  CEGUI::PropertySet::setProperty(pSVar16,(String *)&local_c58);
                    /* try { // try from 00b6fd40 to 00b6fd44 has its CatchHandler @ 00b76a05 */
  CEGUI::String::~String((String *)&local_c58);
                    /* try { // try from 00b6fd48 to 00b6fdc6 has its CatchHandler @ 00b769f6 */
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
                    /* try { // try from 00b6fe31 to 00b6fe35 has its CatchHandler @ 00b76a37 */
  uVar10 = CEGUI::Window::recursiveChildSearch(pSVar14);
  *(undefined8 *)(this + 0x40) = uVar10;
                    /* try { // try from 00b6fe3d to 00b6fec6 has its CatchHandler @ 00b769f6 */
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
                    /* try { // try from 00b6ff8d to 00b6ff91 has its CatchHandler @ 00b76a3c */
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
                    /* try { // try from 00b6fffa to 00b6fffe has its CatchHandler @ 00b76a45 */
  CEGUI::PropertySet::setProperty(*(String **)(this + 0x40),(String *)&local_e68);
                    /* try { // try from 00b70002 to 00b70006 has its CatchHandler @ 00b76a3c */
  CEGUI::String::~String((String *)&local_e68);
                    /* try { // try from 00b7000a to 00b7008a has its CatchHandler @ 00b769f6 */
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
                    /* try { // try from 00b700f9 to 00b700fd has its CatchHandler @ 00b76a55 */
  uVar10 = CEGUI::Window::recursiveChildSearch(pSVar14);
  *(undefined8 *)(this + 0x28) = uVar10;
                    /* try { // try from 00b70105 to 00b7018e has its CatchHandler @ 00b769f6 */
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
                    /* try { // try from 00b70255 to 00b70259 has its CatchHandler @ 00b76a65 */
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
                    /* try { // try from 00b702ca to 00b702ce has its CatchHandler @ 00b76a75 */
  CEGUI::PropertySet::setProperty(*(String **)(this + 0x28),(String *)&local_1078);
                    /* try { // try from 00b702d2 to 00b702d6 has its CatchHandler @ 00b76a65 */
  CEGUI::String::~String((String *)&local_1078);
                    /* try { // try from 00b702da to 00b70357 has its CatchHandler @ 00b769f6 */
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
                    /* try { // try from 00b70392 to 00b70396 has its CatchHandler @ 00b76a85 */
  CEGUI::String::String(local_1288,(uchar *)"MSockets");
                    /* try { // try from 00b703a7 to 00b703ab has its CatchHandler @ 00b76a95 */
  CEGUI::String::String(local_11d8,(uchar *)"DefaultWindow");
                    /* try { // try from 00b703bc to 00b703c0 has its CatchHandler @ 00b7693a */
  uVar10 = CEGUI::WindowManager::createWindow
                     (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,local_11d8,local_1288);
  *(undefined8 *)(this + 0x30) = uVar10;
                    /* try { // try from 00b703c8 to 00b703cc has its CatchHandler @ 00b76a95 */
  CEGUI::String::~String(local_11d8);
                    /* try { // try from 00b703d0 to 00b703d4 has its CatchHandler @ 00b76a85 */
  CEGUI::String::~String(local_1288);
                    /* try { // try from 00b703d8 to 00b703fd has its CatchHandler @ 00b769f6 */
  CEGUI::String::~String((String *)&local_1338);
  CEGUI::Window::addChildWindow(*(Window **)(this + 0x28));
  CEGUI::Window::getSize();
                    /* try { // try from 00b70405 to 00b70409 has its CatchHandler @ 00b76952 */
  CEGUI::Window::setSize(*(UVector2 **)(this + 0x30));
  local_1490 = 0x20;
  local_1488 = 0;
  local_1478 = 0;
  local_1480 = 0;
  local_13f0 = (uint *)0x0;
  local_1498 = 0;
  local_1470[0] = 0;
                    /* try { // try from 00b7046d to 00b70471 has its CatchHandler @ 00b769f6 */
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
                    /* try { // try from 00b70535 to 00b70539 has its CatchHandler @ 00b76957 */
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
                    /* try { // try from 00b705aa to 00b705ae has its CatchHandler @ 00b76965 */
  CEGUI::PropertySet::setProperty(*(String **)(this + 0x30),(String *)&local_13e8);
                    /* try { // try from 00b705b2 to 00b705b6 has its CatchHandler @ 00b76957 */
  CEGUI::String::~String((String *)&local_13e8);
                    /* try { // try from 00b705ba to 00b705be has its CatchHandler @ 00b769f6 */
  CEGUI::String::~String((String *)&local_1498);
  local_394 = 0;
  local_398 = 0;
  local_38c = 0;
  local_390 = 0;
                    /* try { // try from 00b705f7 to 00b705fb has its CatchHandler @ 00b76975 */
  CEGUI::Window::setPosition(*(UVector2 **)(this + 0x30));
  *(undefined1 *)(*(long *)(this + 0x30) + 0x3e2) = 1;
                    /* try { // try from 00b7060b to 00b70671 has its CatchHandler @ 00b769f6 */
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
                    /* try { // try from 00b706ac to 00b706b0 has its CatchHandler @ 00b76985 */
  CEGUI::String::String(local_15f8,(uchar *)"MSocketsO");
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
                    /* try { // try from 00b74624 to 00b74628 has its CatchHandler @ 00b76fc9 */
    std::string::string((string *)local_2a8,"Length for utf8 encoded string can not be \'npos\'",
                        local_49);
    plVar21 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00b7463c to 00b74640 has its CatchHandler @ 00b76f94 */
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
                    /* try { // try from 00b74667 to 00b7466b has its CatchHandler @ 00b76c0c */
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
                    /* try { // try from 00b7083e to 00b70842 has its CatchHandler @ 00b76c0c */
  CEGUI::String::grow((ulong)&local_1548);
  puVar20 = local_1520;
  if (0x20 < local_1540) {
    puVar20 = local_14a0;
  }
  if (pcVar28 == (char *)0x0) {
    if (s_DefaultWindow_00fe499d[0] == '\0') goto LAB_00b708e0;
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
          goto LAB_00b70883;
        }
        uVar9 = uVar9 + 2;
        *puVar20 = (byte)"DefaultWindow"[uVar8] & 0x3f | (uVar23 & 0x1f) << 6;
      }
      else {
LAB_00b70883:
        *puVar20 = uVar23;
        uVar9 = uVar8;
      }
      pcVar13 = (char *)(ulong)uVar9;
      if ((pcVar28 <= pcVar13) || (uVar22 = uVar22 - 1, uVar22 == 0)) break;
      puVar20 = puVar20 + 1;
    } while( true );
  }
LAB_00b708e0:
  puVar20 = local_1520;
  if (0x20 < local_1540) {
    puVar20 = local_14a0;
  }
  puVar20[lVar11] = 0;
  local_1548 = lVar11;
                    /* try { // try from 00b70921 to 00b70925 has its CatchHandler @ 00b768aa */
  uVar10 = CEGUI::WindowManager::createWindow
                     (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,(String *)&local_1548,
                      local_15f8);
  *(undefined8 *)(this + 0x38) = uVar10;
                    /* try { // try from 00b7092d to 00b70931 has its CatchHandler @ 00b76c0c */
  CEGUI::String::~String((String *)&local_1548);
                    /* try { // try from 00b7093a to 00b7093e has its CatchHandler @ 00b76985 */
  CEGUI::String::~String(local_15f8);
                    /* try { // try from 00b70947 to 00b7096c has its CatchHandler @ 00b769f6 */
  CEGUI::String::~String((String *)&local_16a8);
  CEGUI::Window::addChildWindow(*(Window **)(this + 0x28));
  CEGUI::Window::getSize();
                    /* try { // try from 00b70974 to 00b70978 has its CatchHandler @ 00b768d4 */
  CEGUI::Window::setSize(*(UVector2 **)(this + 0x38));
  local_1800 = 0x20;
  local_17f8 = 0;
  local_17e8 = 0;
  local_17f0 = 0;
  local_1760 = (uint *)0x0;
  local_1808 = 0;
  local_17e0[0] = 0;
                    /* try { // try from 00b709dc to 00b709e0 has its CatchHandler @ 00b769f6 */
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
                    /* try { // try from 00b70aa5 to 00b70aa9 has its CatchHandler @ 00b768d9 */
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
                    /* try { // try from 00b70b1a to 00b70b1e has its CatchHandler @ 00b768e5 */
  CEGUI::PropertySet::setProperty(*(String **)(this + 0x38),(String *)&local_1758);
                    /* try { // try from 00b70b22 to 00b70b26 has its CatchHandler @ 00b768d9 */
  CEGUI::String::~String((String *)&local_1758);
                    /* try { // try from 00b70b2a to 00b70b2e has its CatchHandler @ 00b769f6 */
  CEGUI::String::~String((String *)&local_1808);
  local_3b4 = 0;
  local_3b8 = 0;
  local_3ac = 0;
  local_3b0 = 0;
                    /* try { // try from 00b70b67 to 00b70b6b has its CatchHandler @ 00b768f5 */
  CEGUI::Window::setPosition(*(UVector2 **)(this + 0x38));
  *(undefined1 *)(*(long *)(this + 0x38) + 0x3e2) = 1;
                    /* try { // try from 00b70b7b to 00b70be7 has its CatchHandler @ 00b769f6 */
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
                    /* try { // try from 00b70c51 to 00b70c55 has its CatchHandler @ 00b76905 */
  uVar10 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x28));
  *(undefined8 *)(this + 0x3448) = uVar10;
                    /* try { // try from 00b70c60 to 00b70d10 has its CatchHandler @ 00b769f6 */
  CEGUI::String::~String((String *)&local_18b8);
  CEGUI::EventSet::setMutedState((bool)((char)*(undefined8 *)(this + 0x3448) + '8'));
  *(undefined1 *)(*(long *)(this + 0x3448) + 0x3e2) = 1;
  *(undefined1 *)(*(long *)(this + 0x3448) + 0x213) = 0;
  CEGUI::Window::removeChildWindow(*(Window **)(*(long *)(this + 0x3448) + 0xb0));
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
                    /* try { // try from 00b70d7a to 00b70d7e has its CatchHandler @ 00b76915 */
  lVar11 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x28));
                    /* try { // try from 00b70d85 to 00b70daa has its CatchHandler @ 00b769f6 */
  CEGUI::String::~String((String *)&local_1968);
  *(undefined1 *)(lVar11 + 0x213) = 0;
  CEGUI::Window::moveToFront();
  pcVar4 = *(code **)(*(long *)(lVar11 + 0x38) + 0x10);
  local_a8[0] = operator_new(0x20);
  *local_a8[0] = &PTR__MemberFunctionSlot_00ff0270;
  local_a8[0][2] = 0;
  local_a8[0][1] = handle_CloseButton;
  local_a8[0][3] = this;
                    /* try { // try from 00b70dea to 00b70e1f has its CatchHandler @ 00b76925 */
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
                    /* try { // try from 00b70e50 to 00b70edb has its CatchHandler @ 00b769f6 */
  CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_a8);
  iVar6 = 0;
  pCVar26 = this;
  do {
    *(int *)(pCVar26 + 0xb0) = iVar6;
    iVar6 = iVar6 + 1;
    pCVar26 = pCVar26 + 4;
  } while (iVar6 != 400);
  local_1a10 = 0x20;
  local_1a08 = 0;
  local_19f8 = 0;
  local_1a00 = 0;
  local_1970 = (uint *)0x0;
  local_1a18 = 0;
  local_19f0[0] = 0;
  CEGUI::String::grow((ulong)&local_1a18);
  puVar20 = local_19f0;
  if (0x20 < local_1a10) {
    puVar20 = local_1970;
  }
  pbVar15 = &DAT_00feffae;
  do {
    bVar3 = *pbVar15;
    pbVar15 = pbVar15 + 1;
    *puVar20 = (uint)bVar3;
    puVar20 = puVar20 + 1;
  } while (pbVar15 != &DAT_00feffb5);
  local_1a18 = 7;
  puVar20 = local_19d4;
  if (0x20 < local_1a10) {
    puVar20 = local_1970 + 7;
  }
  *puVar20 = 0;
                    /* try { // try from 00b70f49 to 00b70f4d has its CatchHandler @ 00b7676e */
  uVar10 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x28));
  *(undefined8 *)(this + 0x3420) = uVar10;
                    /* try { // try from 00b70f58 to 00b70fc4 has its CatchHandler @ 00b769f6 */
  CEGUI::String::~String((String *)&local_1a18);
  local_1ac0 = 0x20;
  local_1ab8 = 0;
  local_1aa8 = 0;
  local_1ab0 = 0;
  local_1a20 = (uint *)0x0;
  local_1ac8 = 0;
  local_1aa0[0] = 0;
  CEGUI::String::grow((ulong)&local_1ac8);
  puVar20 = local_1aa0;
  if (0x20 < local_1ac0) {
    puVar20 = local_1a20;
  }
  pcVar13 = "TabWeapon";
  do {
    bVar3 = *pcVar13;
    pcVar13 = pcVar13 + 1;
    *puVar20 = (uint)bVar3;
    puVar20 = puVar20 + 1;
  } while ((byte *)pcVar13 != (byte *)0xfeffad);
  local_1ac8 = 9;
  puVar20 = local_1a7c;
  if (0x20 < local_1ac0) {
    puVar20 = local_1a20 + 9;
  }
  *puVar20 = 0;
                    /* try { // try from 00b71031 to 00b71035 has its CatchHandler @ 00b76775 */
  uVar10 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x28));
  *(undefined8 *)(this + 0x3410) = uVar10;
                    /* try { // try from 00b71040 to 00b710ac has its CatchHandler @ 00b769f6 */
  CEGUI::String::~String((String *)&local_1ac8);
  local_1b70 = 0x20;
  local_1b68 = 0;
  local_1b58 = 0;
  local_1b60 = 0;
  local_1ad0 = (uint *)0x0;
  local_1b78 = 0;
  local_1b50[0] = 0;
  CEGUI::String::grow((ulong)&local_1b78);
  puVar20 = local_1b50;
  if (0x20 < local_1b70) {
    puVar20 = local_1ad0;
  }
  pcVar13 = "TabArmor";
  do {
    bVar3 = *pcVar13;
    pcVar13 = pcVar13 + 1;
    *puVar20 = (uint)bVar3;
    puVar20 = puVar20 + 1;
  } while ((byte *)pcVar13 != (byte *)0xfeffa3);
  local_1b78 = 8;
  puVar20 = local_1b30;
  if (0x20 < local_1b70) {
    puVar20 = local_1ad0 + 8;
  }
  *puVar20 = 0;
                    /* try { // try from 00b71119 to 00b7111d has its CatchHandler @ 00b76785 */
  uVar10 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x28));
  *(undefined8 *)(this + 0x3418) = uVar10;
                    /* try { // try from 00b71128 to 00b711be has its CatchHandler @ 00b769f6 */
  CEGUI::String::~String((String *)&local_1b78);
  CEGUI::Window::setZOrderingEnabled(SUB81(*(undefined8 *)(this + 0x3420),0));
  CEGUI::Window::setZOrderingEnabled(SUB81(*(undefined8 *)(this + 0x3410),0));
  CEGUI::Window::setZOrderingEnabled(SUB81(*(undefined8 *)(this + 0x3418),0));
  local_1c20 = 0x20;
  local_1c18 = 0;
  local_1c08 = 0;
  local_1c10 = 0;
  local_1b80 = (uint *)0x0;
  local_1c28 = 0;
  local_1c00[0] = 0;
  CEGUI::String::grow((ulong)&local_1c28);
  puVar20 = local_1c00;
  if (0x20 < local_1c20) {
    puVar20 = local_1b80;
  }
  pcVar13 = "SlotsMisc";
  do {
    bVar3 = *pcVar13;
    pcVar13 = pcVar13 + 1;
    *puVar20 = (uint)bVar3;
    puVar20 = puVar20 + 1;
  } while ((byte *)pcVar13 != (byte *)0xfeff9a);
  local_1c28 = 9;
  puVar20 = local_1bdc;
  if (0x20 < local_1c20) {
    puVar20 = local_1b80 + 9;
  }
  *puVar20 = 0;
                    /* try { // try from 00b71229 to 00b7122d has its CatchHandler @ 00b76795 */
  uVar10 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x28));
  *(undefined8 *)(this + 0x3408) = uVar10;
                    /* try { // try from 00b71238 to 00b712a4 has its CatchHandler @ 00b769f6 */
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
  pcVar13 = "SlotsWeapons";
  do {
    bVar3 = *pcVar13;
    pcVar13 = pcVar13 + 1;
    *puVar20 = (uint)bVar3;
    puVar20 = puVar20 + 1;
  } while ((byte *)pcVar13 != (byte *)0xfeff90);
  local_1cd8 = 0xc;
  puVar20 = local_1c80;
  if (0x20 < local_1cd0) {
    puVar20 = local_1c30 + 0xc;
  }
  *puVar20 = 0;
                    /* try { // try from 00b71311 to 00b71315 has its CatchHandler @ 00b767a5 */
  uVar10 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x28));
  *(undefined8 *)(this + 0x33f8) = uVar10;
                    /* try { // try from 00b71320 to 00b7139a has its CatchHandler @ 00b769f6 */
  CEGUI::String::~String((String *)&local_1cd8);
  CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x33f8),0));
  local_1d80 = 0x20;
  local_1d78 = 0;
  local_1d68 = 0;
  local_1d70 = 0;
  local_1ce0 = (uint *)0x0;
  local_1d88 = 0;
  local_1d60[0] = 0;
  CEGUI::String::grow((ulong)&local_1d88);
  puVar20 = local_1d60;
  if (0x20 < local_1d80) {
    puVar20 = local_1ce0;
  }
  pcVar13 = "SlotsArmor";
  do {
    bVar3 = *pcVar13;
    pcVar13 = pcVar13 + 1;
    *puVar20 = (uint)bVar3;
    puVar20 = puVar20 + 1;
  } while ((byte *)pcVar13 != (byte *)0xfeff83);
  local_1d88 = 10;
  puVar20 = local_1d38;
  if (0x20 < local_1d80) {
    puVar20 = local_1ce0 + 10;
  }
  *puVar20 = 0;
                    /* try { // try from 00b71409 to 00b7140d has its CatchHandler @ 00b767b5 */
  uVar10 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x28));
  *(undefined8 *)(this + 0x3400) = uVar10;
                    /* try { // try from 00b71418 to 00b7147d has its CatchHandler @ 00b769f6 */
  CEGUI::String::~String((String *)&local_1d88);
  CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x3400),0));
  local_3ea4 = 1;
  pCVar26 = this;
  do {
    STRINGS::GetValueAsString((uint)local_b8);
                    /* try { // try from 00b71493 to 00b71497 has its CatchHandler @ 00b767c5 */
    std::operator+((char *)local_c8,(string *)0xff0cc3);
    local_1e30 = 0x20;
    local_1e28 = 0;
    local_1e18 = 0;
    local_1e20 = 0;
    local_1d90 = (undefined4 *)0x0;
    local_1e38 = 0;
    local_1e10[0] = 0;
    lVar11 = *(long *)(local_c8[0] + -0x18);
                    /* try { // try from 00b71502 to 00b71506 has its CatchHandler @ 00b767da */
    CEGUI::String::grow((ulong)&local_1e38);
    puVar19 = local_1e10;
    if (0x20 < local_1e30) {
      puVar19 = local_1d90;
    }
    puVar19[lVar11] = 0;
    lVar29 = lVar11;
    while (lVar29 != 0) {
      lVar29 = lVar29 + -1;
      puVar19 = local_1e10;
      if (0x20 < local_1e30) {
        puVar19 = local_1d90;
      }
      puVar19[lVar29] = (uint)*(byte *)(local_c8[0] + lVar29);
    }
    local_1e38 = lVar11;
                    /* try { // try from 00b7157b to 00b7157f has its CatchHandler @ 00b767ec */
    lVar11 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x28));
                    /* try { // try from 00b7158b to 00b7158f has its CatchHandler @ 00b767da */
    CEGUI::String::~String((String *)&local_1e38);
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
                    /* try { // try from 00b715c6 to 00b71605 has its CatchHandler @ 00b769f6 */
    CEGUI::Window::moveToFront();
    *(undefined1 *)(lVar11 + 0x213) = 0;
    CEGUI::Window::setWantsMultiClickEvents(SUB81(lVar11,0));
    *(CMerchantMenu **)(lVar11 + 0x1d8) = this + (ulong)(local_3ea4 + 0x12) * 4 + 0xb0;
    pcVar4 = *(code **)(*(long *)(lVar11 + 0x38) + 0x10);
    local_d8[0] = operator_new(0x20);
    lVar29 = lVar11 + 0x38;
    *local_d8[0] = &PTR__MemberFunctionSlot_00ff0270;
    local_d8[0][2] = 0;
    local_d8[0][1] = handle_ItemClick;
    local_d8[0][3] = this;
                    /* try { // try from 00b71648 to 00b71683 has its CatchHandler @ 00b7686c */
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
                    /* try { // try from 00b716b6 to 00b716d1 has its CatchHandler @ 00b769f6 */
    CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_d8);
    pcVar4 = *(code **)(*(long *)(lVar11 + 0x38) + 0x10);
    local_e8[0] = operator_new(0x20);
    *local_e8[0] = &PTR__MemberFunctionSlot_00ff0270;
    local_e8[0][2] = 0;
    local_e8[0][1] = handle_MouseOver;
    local_e8[0][3] = this;
                    /* try { // try from 00b71710 to 00b7174b has its CatchHandler @ 00b76871 */
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
                    /* try { // try from 00b7177e to 00b71799 has its CatchHandler @ 00b769f6 */
    CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_e8);
    pcVar4 = *(code **)(*(long *)(lVar11 + 0x38) + 0x10);
    local_f8[0] = operator_new(0x20);
    *local_f8[0] = &PTR__MemberFunctionSlot_00ff0270;
    local_f8[0][2] = 0;
    local_f8[0][1] = handle_MouseOver;
    local_f8[0][3] = this;
                    /* try { // try from 00b717d8 to 00b71813 has its CatchHandler @ 00b76876 */
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
                    /* try { // try from 00b71846 to 00b71861 has its CatchHandler @ 00b769f6 */
    CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_f8);
    pcVar4 = *(code **)(*(long *)(lVar11 + 0x38) + 0x10);
    local_108[0] = operator_new(0x20);
    *local_108[0] = &PTR__MemberFunctionSlot_00ff0270;
    local_108[0][2] = 0;
    local_108[0][1] = handle_MouseOut;
    local_108[0][3] = this;
                    /* try { // try from 00b718a0 to 00b718d6 has its CatchHandler @ 00b76885 */
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
                    /* try { // try from 00b71907 to 00b71974 has its CatchHandler @ 00b769f6 */
    CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_108);
    *(long *)(pCVar26 + 0x1e80) = lVar11;
    local_2040 = 0x20;
    local_2038 = 0;
    local_2028 = 0;
    local_2030 = 0;
    local_1fa0 = (undefined4 *)0x0;
    local_2048 = 0;
    local_2020[0] = 0;
    CEGUI::String::grow((ulong)&local_2048);
    local_2048 = 0;
    puVar19 = local_1fa0;
    if (local_2040 < 0x21) {
      puVar19 = local_2020;
    }
    *puVar19 = 0;
                    /* try { // try from 00b719b7 to 00b719bb has its CatchHandler @ 00b76895 */
    std::string::string((string *)local_118,"gui_",&local_3a);
                    /* try { // try from 00b719cc to 00b719d0 has its CatchHandler @ 00b76cc3 */
    STRINGS::uniqueName((STRINGS *)local_128,(string *)local_118);
    local_1f90 = 0x20;
    local_1f88 = 0;
    local_1f78 = 0;
    local_1f80 = 0;
    local_1ef0 = (undefined4 *)0x0;
    local_1f98 = 0;
    local_1f70[0] = 0;
    lVar11 = *(long *)(local_128[0] + -0x18);
                    /* try { // try from 00b71a3b to 00b71a3f has its CatchHandler @ 00b76ccb */
    CEGUI::String::grow((ulong)&local_1f98);
    puVar19 = local_1f70;
    if (0x20 < local_1f90) {
      puVar19 = local_1ef0;
    }
    puVar19[lVar11] = 0;
    lVar29 = lVar11;
    while (lVar29 != 0) {
      lVar29 = lVar29 + -1;
      puVar19 = local_1f70;
      if (0x20 < local_1f90) {
        puVar19 = local_1ef0;
      }
      puVar19[lVar29] = (uint)*(byte *)(local_128[0] + lVar29);
    }
    pcVar28 = (char *)0x0;
    local_1ee0 = 0x20;
    local_1ed8 = 0;
    local_1ec8 = 0;
    pcVar13 = "GuiLook/StaticText";
    local_1ed0 = 0;
    local_1e40 = (uint *)0x0;
    local_1ee8 = 0;
    local_1ec0[0] = 0;
    cVar2 = s_GuiLook_StaticText_00fe4872[0];
    while (pcVar13 = pcVar13 + 1, cVar2 != '\0') {
      pcVar28 = pcVar13 + -0xfe4872;
      cVar2 = *pcVar13;
    }
    local_1f98 = lVar11;
    if (pcVar28 == CEGUI::String::npos) {
                    /* try { // try from 00b74384 to 00b74388 has its CatchHandler @ 00b77247 */
      std::string::string((string *)local_2b8,"Length for utf8 encoded string can not be \'npos\'",
                          local_4d);
      plVar21 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00b7439c to 00b743a0 has its CatchHandler @ 00b7722f */
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
                    /* try { // try from 00b743c7 to 00b743cb has its CatchHandler @ 00b76cd5 */
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
                    /* try { // try from 00b71bdb to 00b71bdf has its CatchHandler @ 00b76cd5 */
    CEGUI::String::grow((ulong)&local_1ee8);
    puVar20 = local_1e40;
    if (local_1ee0 < 0x21) {
      puVar20 = local_1ec0;
    }
    if (pcVar28 == (char *)0x0) {
      pcVar13 = "GuiLook/StaticText";
      if (s_GuiLook_StaticText_00fe4872[0] != '\0') {
        do {
          pcVar13 = pcVar13 + 1;
          pcVar28 = pcVar13 + -0xfe4872;
        } while (*pcVar13 != '\0');
        bVar30 = pcVar28 != (char *)0x0 && local_1ee0 != 0;
        goto LAB_00b71c0d;
      }
    }
    else {
      bVar30 = local_1ee0 != 0;
LAB_00b71c0d:
      if (bVar30) {
        pcVar13 = (char *)0x0;
        uVar9 = 0;
        uVar22 = local_1ee0;
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
              goto LAB_00b71c23;
            }
            uVar9 = uVar9 + 2;
            *puVar20 = (byte)"GuiLook/StaticText"[uVar8] & 0x3f | (uVar23 & 0x1f) << 6;
          }
          else {
LAB_00b71c23:
            *puVar20 = uVar23;
            uVar9 = uVar8;
          }
          pcVar13 = (char *)(ulong)uVar9;
          if ((pcVar28 <= pcVar13) || (uVar22 = uVar22 - 1, uVar22 == 0)) break;
          puVar20 = puVar20 + 1;
        } while( true );
      }
    }
    puVar20 = local_1e40;
    if (local_1ee0 < 0x21) {
      puVar20 = local_1ec0;
    }
    puVar20[lVar11] = 0;
    local_1ee8 = lVar11;
                    /* try { // try from 00b71cca to 00b71cce has its CatchHandler @ 00b76c14 */
    uVar10 = CEGUI::WindowManager::createWindow
                       (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,(String *)&local_1ee8,
                        (String *)&local_1f98);
    *(undefined8 *)(pCVar26 + 0x2308) = uVar10;
                    /* try { // try from 00b71cde to 00b71ce2 has its CatchHandler @ 00b76cd5 */
    CEGUI::String::~String((String *)&local_1ee8);
                    /* try { // try from 00b71ceb to 00b71cef has its CatchHandler @ 00b76ccb */
    CEGUI::String::~String((String *)&local_1f98);
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
                    /* try { // try from 00b71d2c to 00b71d98 has its CatchHandler @ 00b769f6 */
    CEGUI::String::~String((String *)&local_2048);
    local_20f0 = 0x20;
    local_20e8 = 0;
    local_20d8 = 0;
    local_20e0 = 0;
    local_2050 = (uint *)0x0;
    local_20f8 = 0;
    local_20d0[0] = 0;
    CEGUI::String::grow((ulong)&local_20f8);
    puVar20 = local_20d0;
    if (0x20 < local_20f0) {
      puVar20 = local_2050;
    }
    pcVar13 = "Serif";
    do {
      bVar3 = *pcVar13;
      pcVar13 = pcVar13 + 1;
      *puVar20 = (uint)bVar3;
      puVar20 = puVar20 + 1;
    } while ((byte *)pcVar13 != (byte *)0xfe4949);
    local_20f8 = 5;
    puVar20 = local_20bc;
    if (0x20 < local_20f0) {
      puVar20 = local_2050 + 5;
    }
    *puVar20 = 0;
                    /* try { // try from 00b71e0d to 00b71e11 has its CatchHandler @ 00b76cbe */
    CEGUI::Window::setFont(*(String **)(pCVar26 + 0x2308));
                    /* try { // try from 00b71e15 to 00b71e2c has its CatchHandler @ 00b769f6 */
    CEGUI::String::~String((String *)&local_20f8);
    CEGUI::Window::getSize();
                    /* try { // try from 00b71e37 to 00b71e3b has its CatchHandler @ 00b76ced */
    CEGUI::Window::setSize(*(UVector2 **)(pCVar26 + 0x2308));
                    /* try { // try from 00b71e3f to 00b71e43 has its CatchHandler @ 00b769f6 */
    puVar17 = (undefined8 *)CEGUI::Window::getPosition();
    local_4a8 = *puVar17;
    local_4a0 = puVar17[1];
    local_2250 = 0x20;
    local_2248 = 0;
    local_2238 = 0;
    local_2240 = 0;
    local_21b0 = (uint *)0x0;
    local_2258 = 0;
    local_2230[0] = 0;
                    /* try { // try from 00b71ebe to 00b71ec2 has its CatchHandler @ 00b76cf2 */
    CEGUI::String::grow((ulong)&local_2258);
    puVar20 = local_2230;
    if (0x20 < local_2250) {
      puVar20 = local_21b0;
    }
    pcVar13 = "RightAligned";
    do {
      bVar3 = *pcVar13;
      pcVar13 = pcVar13 + 1;
      *puVar20 = (uint)bVar3;
      puVar20 = puVar20 + 1;
    } while ((byte *)pcVar13 != (byte *)0xfe602d);
    local_2258 = 0xc;
    puVar20 = local_2200;
    if (0x20 < local_2250) {
      puVar20 = local_21b0 + 0xc;
    }
    *puVar20 = 0;
    local_21a0 = 0x20;
    local_2198 = 0;
    local_2188 = 0;
    local_2190 = 0;
    local_2100 = (uint *)0x0;
    local_21a8 = 0;
    local_2180[0] = 0;
                    /* try { // try from 00b71f85 to 00b71f89 has its CatchHandler @ 00b76cf7 */
    CEGUI::String::grow((ulong)&local_21a8);
    puVar20 = local_2180;
    if (0x20 < local_21a0) {
      puVar20 = local_2100;
    }
    pcVar13 = "HorzTextFormatting";
    do {
      bVar3 = *pcVar13;
      pcVar13 = pcVar13 + 1;
      *puVar20 = (uint)bVar3;
      puVar20 = puVar20 + 1;
    } while ((byte *)pcVar13 != (byte *)0xfe48cf);
    local_21a8 = 0x12;
    puVar20 = local_2138;
    if (0x20 < local_21a0) {
      puVar20 = local_2100 + 0x12;
    }
    *puVar20 = 0;
                    /* try { // try from 00b72000 to 00b72004 has its CatchHandler @ 00b76d05 */
    CEGUI::PropertySet::setProperty(*(String **)(pCVar26 + 0x2308),(String *)&local_21a8);
                    /* try { // try from 00b72008 to 00b7200c has its CatchHandler @ 00b76cf7 */
    CEGUI::String::~String((String *)&local_21a8);
                    /* try { // try from 00b72010 to 00b7207c has its CatchHandler @ 00b76cf2 */
    CEGUI::String::~String((String *)&local_2258);
    local_23b0 = 0x20;
    local_23a8 = 0;
    local_2398 = 0;
    local_23a0 = 0;
    local_2310 = (uint *)0x0;
    local_23b8 = 0;
    local_2390[0] = 0;
    CEGUI::String::grow((ulong)&local_23b8);
    puVar20 = local_2390;
    if (0x20 < local_23b0) {
      puVar20 = local_2310;
    }
    pcVar13 = "TopAligned";
    do {
      bVar3 = *pcVar13;
      pcVar13 = pcVar13 + 1;
      *puVar20 = (uint)bVar3;
      puVar20 = puVar20 + 1;
    } while ((byte *)pcVar13 != (byte *)0xfe489f);
    local_23b8 = 10;
    puVar20 = local_2368;
    if (0x20 < local_23b0) {
      puVar20 = local_2310 + 10;
    }
    *puVar20 = 0;
    local_2300 = 0x20;
    local_22f8 = 0;
    local_22e8 = 0;
    local_22f0 = 0;
    local_2260 = (uint *)0x0;
    local_2308 = 0;
    local_22e0[0] = 0;
                    /* try { // try from 00b72145 to 00b72149 has its CatchHandler @ 00b76d15 */
    CEGUI::String::grow((ulong)&local_2308);
    puVar20 = local_22e0;
    if (0x20 < local_2300) {
      puVar20 = local_2260;
    }
    pcVar13 = "VertFormatting";
    do {
      bVar3 = *pcVar13;
      pcVar13 = pcVar13 + 1;
      *puVar20 = (uint)bVar3;
      puVar20 = puVar20 + 1;
    } while ((byte *)pcVar13 != (byte *)0xfe48ae);
    local_2308 = 0xe;
    puVar20 = local_22a8;
    if (0x20 < local_2300) {
      puVar20 = local_2260 + 0xe;
    }
    *puVar20 = 0;
                    /* try { // try from 00b721c0 to 00b721c4 has its CatchHandler @ 00b76d25 */
    CEGUI::PropertySet::setProperty(*(String **)(pCVar26 + 0x2308),(String *)&local_2308);
                    /* try { // try from 00b721c8 to 00b721cc has its CatchHandler @ 00b76d15 */
    CEGUI::String::~String((String *)&local_2308);
                    /* try { // try from 00b721d0 to 00b72283 has its CatchHandler @ 00b76cf2 */
    CEGUI::String::~String((String *)&local_23b8);
    *(undefined1 *)(*(long *)(pCVar26 + 0x2308) + 0x3e2) = 1;
    CEGUI::Window::setPosition(*(UVector2 **)(pCVar26 + 0x2308));
    CEGUI::Window::addChildWindow(*(Window **)(*(long *)(pCVar26 + 0x1e80) + 0xb0));
    local_2460 = 0x20;
    local_2458 = 0;
    local_2448 = 0;
    local_2450 = 0;
    local_23c0 = (undefined4 *)0x0;
    local_2468 = 0;
    local_2440[0] = 0;
    if (CEGUI::String::npos == (char *)0x0) {
                    /* try { // try from 00b74444 to 00b74448 has its CatchHandler @ 00b7721c */
      std::string::string((string *)local_2c8,"Length for utf8 encoded string can not be \'npos\'",
                          local_51);
      plVar21 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00b7445c to 00b74460 has its CatchHandler @ 00b771a8 */
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
                    /* try { // try from 00b74487 to 00b7448b has its CatchHandler @ 00b76cf2 */
      __cxa_throw(plVar21,&std::length_error::typeinfo,std::length_error::~length_error);
    }
    CEGUI::String::grow((ulong)&local_2468);
    local_2468 = 0;
    puVar19 = local_2440;
    if (0x20 < local_2460) {
      puVar19 = local_23c0;
    }
    *puVar19 = 0;
                    /* try { // try from 00b722b8 to 00b722bc has its CatchHandler @ 00b76d35 */
    CEGUI::Window::setText(*(String **)(pCVar26 + 0x2308));
                    /* try { // try from 00b722c0 to 00b722f8 has its CatchHandler @ 00b76cf2 */
    CEGUI::String::~String((String *)&local_2468);
    CEGUI::colour::colour(local_4f8,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc);
    CEGUI::PropertyHelper::colourToString(local_2518);
    local_25c0 = 0x20;
    local_25b8 = 0;
    local_25a8 = 0;
    local_25b0 = 0;
    local_2520 = (uint *)0x0;
    local_25c8 = 0;
    local_25a0[0] = 0;
                    /* try { // try from 00b7235c to 00b72360 has its CatchHandler @ 00b76d55 */
    CEGUI::String::grow((ulong)&local_25c8);
    puVar20 = local_25a0;
    if (0x20 < local_25c0) {
      puVar20 = local_2520;
    }
    pbVar15 = (byte *)0xfe4654;
    do {
      bVar3 = *pbVar15;
      pbVar15 = pbVar15 + 1;
      *puVar20 = (uint)bVar3;
      puVar20 = puVar20 + 1;
    } while (pbVar15 != (byte *)0xfe465e);
    local_25c8 = 10;
    puVar20 = local_2578;
    if (0x20 < local_25c0) {
      puVar20 = local_2520 + 10;
    }
    *puVar20 = 0;
                    /* try { // try from 00b723d0 to 00b723d4 has its CatchHandler @ 00b76d65 */
    CEGUI::PropertySet::setProperty(*(String **)(pCVar26 + 0x2308),(String *)&local_25c8);
                    /* try { // try from 00b723d8 to 00b723dc has its CatchHandler @ 00b76d55 */
    CEGUI::String::~String((String *)&local_25c8);
                    /* try { // try from 00b723e0 to 00b72457 has its CatchHandler @ 00b76cf2 */
    CEGUI::String::~String(local_2518);
    CEGUI::Window::setAlwaysOnTop(SUB81(*(undefined8 *)(pCVar26 + 0x2308),0));
    local_27d0 = 0x20;
    local_27c8 = 0;
    local_27b8 = 0;
    local_27c0 = 0;
    local_2730 = (undefined4 *)0x0;
    local_27d8 = 0;
    local_27b0[0] = 0;
    CEGUI::String::grow((ulong)&local_27d8);
    local_27d8 = 0;
    puVar19 = local_2730;
    if (local_27d0 < 0x21) {
      puVar19 = local_27b0;
    }
    *puVar19 = 0;
                    /* try { // try from 00b7249a to 00b7249e has its CatchHandler @ 00b76d75 */
    std::string::string((string *)local_138,"gui_",&local_3b);
                    /* try { // try from 00b724af to 00b724b3 has its CatchHandler @ 00b76d8a */
    STRINGS::uniqueName((STRINGS *)local_148,(string *)local_138);
    local_2720 = 0x20;
    local_2718 = 0;
    local_2708 = 0;
    local_2710 = 0;
    local_2680 = (undefined4 *)0x0;
    local_2728 = 0;
    local_2700[0] = 0;
    lVar11 = *(long *)(local_148[0] + -0x18);
                    /* try { // try from 00b7251e to 00b72522 has its CatchHandler @ 00b76dcd */
    CEGUI::String::grow((ulong)&local_2728);
    puVar19 = local_2700;
    if (0x20 < local_2720) {
      puVar19 = local_2680;
    }
    puVar19[lVar11] = 0;
    lVar29 = lVar11;
    while (lVar29 != 0) {
      lVar29 = lVar29 + -1;
      puVar19 = local_2700;
      if (0x20 < local_2720) {
        puVar19 = local_2680;
      }
      puVar19[lVar29] = (uint)*(byte *)(local_148[0] + lVar29);
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
                    /* try { // try from 00b74504 to 00b74508 has its CatchHandler @ 00b770e9 */
      std::string::string((string *)local_2d8,"Length for utf8 encoded string can not be \'npos\'",
                          local_53);
      plVar21 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00b7451c to 00b74520 has its CatchHandler @ 00b770d1 */
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
                    /* try { // try from 00b74547 to 00b7454b has its CatchHandler @ 00b76d9c */
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
                    /* try { // try from 00b726cb to 00b726cf has its CatchHandler @ 00b76d9c */
    CEGUI::String::grow((ulong)&local_2678);
    puVar20 = local_25d0;
    if (local_2670 < 0x21) {
      puVar20 = local_2650;
    }
    if (pcVar28 == (char *)0x0) {
      pcVar13 = "GuiLook/StaticImage";
      if (s_GuiLook_StaticImage_00fd0bff[0] != '\0') {
        do {
          pcVar13 = pcVar13 + 1;
          pcVar28 = pcVar13 + -0xfd0bff;
        } while (*pcVar13 != '\0');
        bVar30 = pcVar28 != (char *)0x0 && local_2670 != 0;
        goto LAB_00b726fd;
      }
    }
    else {
      bVar30 = local_2670 != 0;
LAB_00b726fd:
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
              goto LAB_00b72713;
            }
            uVar9 = uVar9 + 2;
            *puVar20 = (byte)"GuiLook/StaticImage"[uVar8] & 0x3f | (uVar23 & 0x1f) << 6;
          }
          else {
LAB_00b72713:
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
                    /* try { // try from 00b727ba to 00b727be has its CatchHandler @ 00b76dbb */
    pUVar18 = (UVector2 *)
              CEGUI::WindowManager::createWindow
                        (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,(String *)&local_2678,
                         (String *)&local_2728);
                    /* try { // try from 00b727ca to 00b727ce has its CatchHandler @ 00b76d9c */
    CEGUI::String::~String((String *)&local_2678);
                    /* try { // try from 00b727d7 to 00b727db has its CatchHandler @ 00b76dcd */
    CEGUI::String::~String((String *)&local_2728);
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
                    /* try { // try from 00b72818 to 00b72883 has its CatchHandler @ 00b76cf2 */
    CEGUI::String::~String((String *)&local_27d8);
    CEGUI::Window::addChildWindow(*(Window **)(*(long *)(pCVar26 + 0x1e80) + 0xb0));
    pUVar18[0x213] = (UVector2)0x0;
    CEGUI::Window::setWantsMultiClickEvents(SUB81(pUVar18,0));
    pUVar18[0x3e2] = (UVector2)0x1;
    CEGUI::EventSet::setMutedState((bool)(SUB81(pUVar18,0) + '8'));
    CEGUI::Window::getPosition();
    CEGUI::Window::setPosition(pUVar18);
    CEGUI::Window::getSize();
                    /* try { // try from 00b7288a to 00b7288e has its CatchHandler @ 00b76e3a */
    CEGUI::Window::setSize(pUVar18);
    *(UVector2 **)(pCVar26 + 0x1570) = pUVar18;
    local_29e0 = 0x20;
    local_29d8 = 0;
    local_29c8 = 0;
    local_29d0 = 0;
    local_2940 = (undefined4 *)0x0;
    local_29e8 = 0;
    local_29c0[0] = 0;
                    /* try { // try from 00b728f3 to 00b728f7 has its CatchHandler @ 00b76cf2 */
    CEGUI::String::grow((ulong)&local_29e8);
    local_29e8 = 0;
    puVar19 = local_2940;
    if (local_29e0 < 0x21) {
      puVar19 = local_29c0;
    }
    *puVar19 = 0;
                    /* try { // try from 00b7293a to 00b7293e has its CatchHandler @ 00b76e55 */
    std::string::string((string *)local_158,"gui_",&local_3c);
                    /* try { // try from 00b7294f to 00b72953 has its CatchHandler @ 00b76e5d */
    STRINGS::uniqueName((STRINGS *)local_168,(string *)local_158);
    local_2930 = 0x20;
    local_2928 = 0;
    local_2918 = 0;
    local_2920 = 0;
    local_2890 = (undefined4 *)0x0;
    local_2938 = 0;
    local_2910[0] = 0;
    lVar11 = *(long *)(local_168[0] + -0x18);
                    /* try { // try from 00b729be to 00b729c2 has its CatchHandler @ 00b76e65 */
    CEGUI::String::grow((ulong)&local_2938);
    puVar19 = local_2890;
    if (local_2930 < 0x21) {
      puVar19 = local_2910;
    }
    puVar19[lVar11] = 0;
    if (lVar11 != 0) {
      lVar29 = lVar11;
      do {
        lVar29 = lVar29 + -1;
        puVar19 = local_2910;
        if (0x20 < local_2930) {
          puVar19 = local_2890;
        }
        puVar19[lVar29] = (uint)*(byte *)(local_168[0] + lVar29);
      } while (lVar29 != 0);
    }
    pcVar28 = (char *)0x0;
    local_2880 = 0x20;
    local_2878 = 0;
    local_2868 = 0;
    pcVar13 = "GuiLook/StaticImage";
    local_2870 = 0;
    local_27e0 = (uint *)0x0;
    local_2888 = 0;
    local_2860[0] = 0;
    cVar2 = s_GuiLook_StaticImage_00fd0bff[0];
    while (pcVar13 = pcVar13 + 1, cVar2 != '\0') {
      pcVar28 = pcVar13 + -0xfd0bff;
      cVar2 = *pcVar13;
    }
    local_2938 = lVar11;
    if (pcVar28 == CEGUI::String::npos) {
                    /* try { // try from 00b745c4 to 00b745c8 has its CatchHandler @ 00b77042 */
      std::string::string((string *)local_2e8,"Length for utf8 encoded string can not be \'npos\'",
                          local_57);
      plVar21 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00b745dc to 00b745e0 has its CatchHandler @ 00b76ffe */
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
                    /* try { // try from 00b74607 to 00b7460b has its CatchHandler @ 00b76e6d */
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
                    /* try { // try from 00b72bcb to 00b72bcf has its CatchHandler @ 00b76e6d */
    CEGUI::String::grow((ulong)&local_2888);
    if (local_2880 < 0x21) {
      puVar20 = local_2860;
      if (pcVar28 == (char *)0x0) goto LAB_00b74258;
LAB_00b72bf7:
      bVar30 = local_2880 != 0;
LAB_00b72bfd:
      if (bVar30) {
        pcVar13 = (char *)0x0;
        uVar9 = 0;
        uVar22 = local_2880;
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
              goto LAB_00b72c13;
            }
            uVar9 = uVar9 + 2;
            *puVar20 = (byte)"GuiLook/StaticImage"[uVar8] & 0x3f | (uVar23 & 0x1f) << 6;
          }
          else {
LAB_00b72c13:
            *puVar20 = uVar23;
            uVar9 = uVar8;
          }
          pcVar13 = (char *)(ulong)uVar9;
          if ((pcVar28 <= pcVar13) || (uVar22 = uVar22 - 1, uVar22 == 0)) break;
          puVar20 = puVar20 + 1;
        } while( true );
      }
    }
    else {
      puVar20 = local_27e0;
      if (pcVar28 != (char *)0x0) goto LAB_00b72bf7;
LAB_00b74258:
      pcVar13 = "GuiLook/StaticImage";
      if (s_GuiLook_StaticImage_00fd0bff[0] != '\0') {
        do {
          pcVar13 = pcVar13 + 1;
          pcVar28 = pcVar13 + -0xfd0bff;
        } while (*pcVar13 != '\0');
        bVar30 = pcVar28 != (char *)0x0 && local_2880 != 0;
        goto LAB_00b72bfd;
      }
    }
    puVar20 = local_27e0;
    if (local_2880 < 0x21) {
      puVar20 = local_2860;
    }
    puVar20[lVar11] = 0;
    local_2888 = lVar11;
                    /* try { // try from 00b72cba to 00b72cbe has its CatchHandler @ 00b76b17 */
    pUVar18 = (UVector2 *)
              CEGUI::WindowManager::createWindow
                        (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,(String *)&local_2888,
                         (String *)&local_2938);
                    /* try { // try from 00b72cca to 00b72cce has its CatchHandler @ 00b76e6d */
    CEGUI::String::~String((String *)&local_2888);
                    /* try { // try from 00b72cd7 to 00b72cdb has its CatchHandler @ 00b76e65 */
    CEGUI::String::~String((String *)&local_2938);
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
                    /* try { // try from 00b72d18 to 00b72d79 has its CatchHandler @ 00b76cf2 */
    CEGUI::String::~String((String *)&local_29e8);
    CEGUI::Window::addChildWindow(*(Window **)(this + 0x38));
    pUVar18[0x213] = (UVector2)0x0;
    CEGUI::Window::setWantsMultiClickEvents(SUB81(pUVar18,0));
    pUVar18[0x3e2] = (UVector2)0x1;
    CEGUI::EventSet::setMutedState((bool)(SUB81(pUVar18,0) + '8'));
    CEGUI::Window::getPosition();
    CEGUI::Window::setPosition(pUVar18);
    CEGUI::Window::getSize();
                    /* try { // try from 00b72d80 to 00b72d84 has its CatchHandler @ 00b76bce */
    CEGUI::Window::setSize(pUVar18);
    *(UVector2 **)(pCVar26 + 0x19f8) = pUVar18;
    local_2bf0 = 0x20;
    local_2be8 = 0;
    local_2bd8 = 0;
    local_2be0 = 0;
    local_2b50 = (undefined4 *)0x0;
    local_2bf8 = 0;
    local_2bd0[0] = 0;
                    /* try { // try from 00b72de9 to 00b72ded has its CatchHandler @ 00b76cf2 */
    CEGUI::String::grow((ulong)&local_2bf8);
    local_2bf8 = 0;
    puVar19 = local_2b50;
    if (local_2bf0 < 0x21) {
      puVar19 = local_2bd0;
    }
    *puVar19 = 0;
                    /* try { // try from 00b72e30 to 00b72e34 has its CatchHandler @ 00b76bd3 */
    std::string::string((string *)local_178,"gui_",&local_3d);
                    /* try { // try from 00b72e45 to 00b72e49 has its CatchHandler @ 00b76be8 */
    STRINGS::uniqueName((STRINGS *)local_188,(string *)local_178);
    local_2b40 = 0x20;
    local_2b38 = 0;
    local_2b28 = 0;
    local_2b30 = 0;
    local_2aa0 = (undefined4 *)0x0;
    local_2b48 = 0;
    local_2b20[0] = 0;
    lVar11 = *(long *)(local_188[0] + -0x18);
                    /* try { // try from 00b72eb7 to 00b72ebb has its CatchHandler @ 00b76bfa */
    CEGUI::String::grow((ulong)&local_2b48);
    puVar19 = local_2b20;
    if (0x20 < local_2b40) {
      puVar19 = local_2aa0;
    }
    puVar19[lVar11] = 0;
    if (lVar11 != 0) {
      lVar29 = lVar11;
      do {
        lVar29 = lVar29 + -1;
        puVar19 = local_2b20;
        if (0x20 < local_2b40) {
          puVar19 = local_2aa0;
        }
        puVar19[lVar29] = (uint)*(byte *)(local_188[0] + lVar29);
      } while (lVar29 != 0);
    }
    pcVar28 = (char *)0x0;
    local_2a90 = 0x20;
    local_2a88 = 0;
    local_2a78 = 0;
    pcVar13 = "GuiLook/StaticImage";
    local_2a80 = 0;
    local_29f0 = (uint *)0x0;
    local_2a98 = 0;
    local_2a70[0] = 0;
    cVar2 = s_GuiLook_StaticImage_00fd0bff[0];
    while (pcVar13 = pcVar13 + 1, cVar2 != '\0') {
      pcVar28 = pcVar13 + -0xfd0bff;
      cVar2 = *pcVar13;
    }
    local_2b48 = lVar11;
    if (pcVar28 == CEGUI::String::npos) {
                    /* try { // try from 00b74684 to 00b74688 has its CatchHandler @ 00b76f46 */
      std::string::string((string *)local_2f8,"Length for utf8 encoded string can not be \'npos\'",
                          local_5b);
      plVar21 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00b7469c to 00b746a0 has its CatchHandler @ 00b76f2e */
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
                    /* try { // try from 00b746c7 to 00b746cb has its CatchHandler @ 00b76cdd */
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
                    /* try { // try from 00b730a6 to 00b730aa has its CatchHandler @ 00b76cdd */
    CEGUI::String::grow((ulong)&local_2a98);
    if (local_2a90 < 0x21) {
      puVar20 = local_2a70;
      if (pcVar28 == (char *)0x0) goto LAB_00b742fc;
LAB_00b730d2:
      bVar30 = local_2a90 != 0;
LAB_00b730d8:
      if (bVar30) {
        pcVar13 = (char *)0x0;
        uVar9 = 0;
        uVar22 = local_2a90;
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
              goto LAB_00b730eb;
            }
            uVar9 = uVar9 + 2;
            *puVar20 = (byte)"GuiLook/StaticImage"[uVar8] & 0x3f | (uVar23 & 0x1f) << 6;
          }
          else {
LAB_00b730eb:
            *puVar20 = uVar23;
            uVar9 = uVar8;
          }
          pcVar13 = (char *)(ulong)uVar9;
          if ((pcVar28 <= pcVar13) || (uVar22 = uVar22 - 1, uVar22 == 0)) break;
          puVar20 = puVar20 + 1;
        } while( true );
      }
    }
    else {
      puVar20 = local_29f0;
      if (pcVar28 != (char *)0x0) goto LAB_00b730d2;
LAB_00b742fc:
      pcVar13 = "GuiLook/StaticImage";
      if (s_GuiLook_StaticImage_00fd0bff[0] != '\0') {
        do {
          pcVar13 = pcVar13 + 1;
          pcVar28 = pcVar13 + -0xfd0bff;
        } while (*pcVar13 != '\0');
        bVar30 = pcVar28 != (char *)0x0 && local_2a90 != 0;
        goto LAB_00b730d8;
      }
    }
    puVar20 = local_29f0;
    if (local_2a90 < 0x21) {
      puVar20 = local_2a70;
    }
    puVar20[lVar11] = 0;
    local_2a98 = lVar11;
                    /* try { // try from 00b73185 to 00b73189 has its CatchHandler @ 00b76e7a */
    pUVar18 = (UVector2 *)
              CEGUI::WindowManager::createWindow
                        (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,(String *)&local_2a98,
                         (String *)&local_2b48);
                    /* try { // try from 00b73195 to 00b73199 has its CatchHandler @ 00b76cdd */
    CEGUI::String::~String((String *)&local_2a98);
                    /* try { // try from 00b7319d to 00b731a1 has its CatchHandler @ 00b76bfa */
    CEGUI::String::~String((String *)&local_2b48);
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
                    /* try { // try from 00b731de to 00b73251 has its CatchHandler @ 00b76cf2 */
    CEGUI::String::~String((String *)&local_2bf8);
    CEGUI::Window::addChildWindow(*(Window **)(*(long *)(pCVar26 + 0x1e80) + 0xb0));
    pUVar18[0x213] = (UVector2)0x0;
    bVar30 = SUB81(pUVar18,0);
    CEGUI::Window::setWantsMultiClickEvents(bVar30);
    pUVar18[0x3e2] = (UVector2)0x1;
    CEGUI::EventSet::setMutedState((bool)(bVar30 + '8'));
    CEGUI::Window::getPosition();
    CEGUI::Window::setPosition(pUVar18);
    CEGUI::Window::getSize();
                    /* try { // try from 00b73258 to 00b7325c has its CatchHandler @ 00b76efd */
    CEGUI::Window::setSize(pUVar18);
                    /* try { // try from 00b73265 to 00b73269 has its CatchHandler @ 00b76cf2 */
    CEGUI::Window::setAlwaysOnTop(bVar30);
    *(UVector2 **)(pCVar26 + 0x10e8) = pUVar18;
    local_3ea4 = local_3ea4 + 1;
    pCVar26 = pCVar26 + 8;
  } while (local_3ea4 != 0x7f);
  local_2ca0 = 0x20;
  local_2c98 = 0;
  local_2c88 = 0;
  local_2c90 = 0;
  local_2c00 = (uint *)0x0;
  local_2ca8 = 0;
  local_2c80[0] = 0;
                    /* try { // try from 00b732e8 to 00b732ec has its CatchHandler @ 00b769f6 */
  CEGUI::String::grow((ulong)&local_2ca8);
  puVar20 = local_2c80;
  if (0x20 < local_2ca0) {
    puVar20 = local_2c00;
  }
  pcVar13 = "TabBackpack";
  do {
    bVar3 = *pcVar13;
    pcVar13 = pcVar13 + 1;
    *puVar20 = (uint)bVar3;
    puVar20 = puVar20 + 1;
  } while ((byte *)pcVar13 != (byte *)0xfef7db);
  local_2ca8 = 0xb;
  puVar20 = local_2c54;
  if (0x20 < local_2ca0) {
    puVar20 = local_2c00 + 0xb;
  }
  *puVar20 = 0;
                    /* try { // try from 00b73352 to 00b73356 has its CatchHandler @ 00b76769 */
  uVar10 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x40));
  *(undefined8 *)(this + 0x33e0) = uVar10;
                    /* try { // try from 00b73361 to 00b733cd has its CatchHandler @ 00b769f6 */
  CEGUI::String::~String((String *)&local_2ca8);
  local_2d50 = 0x20;
  local_2d48 = 0;
  local_2d38 = 0;
  local_2d40 = 0;
  local_2cb0 = (uint *)0x0;
  local_2d58 = 0;
  local_2d30[0] = 0;
  CEGUI::String::grow((ulong)&local_2d58);
  puVar20 = local_2d30;
  if (0x20 < local_2d50) {
    puVar20 = local_2cb0;
  }
  pcVar13 = "TabSpell";
  do {
    bVar3 = *pcVar13;
    pcVar13 = pcVar13 + 1;
    *puVar20 = (uint)bVar3;
    puVar20 = puVar20 + 1;
  } while ((byte *)pcVar13 != (byte *)0xfef7cf);
  local_2d58 = 8;
  puVar20 = local_2d10;
  if (0x20 < local_2d50) {
    puVar20 = local_2cb0 + 8;
  }
  *puVar20 = 0;
                    /* try { // try from 00b73433 to 00b73437 has its CatchHandler @ 00b76174 */
  uVar10 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x40));
  *(undefined8 *)(this + 0x33e8) = uVar10;
                    /* try { // try from 00b73442 to 00b734ae has its CatchHandler @ 00b769f6 */
  CEGUI::String::~String((String *)&local_2d58);
  local_2e00 = 0x20;
  local_2df8 = 0;
  local_2de8 = 0;
  local_2df0 = 0;
  local_2d60 = (uint *)0x0;
  local_2e08 = 0;
  local_2de0[0] = 0;
  CEGUI::String::grow((ulong)&local_2e08);
  puVar20 = local_2de0;
  if (0x20 < local_2e00) {
    puVar20 = local_2d60;
  }
  pcVar13 = "TabFish";
  do {
    bVar3 = *pcVar13;
    pcVar13 = pcVar13 + 1;
    *puVar20 = (uint)bVar3;
    puVar20 = puVar20 + 1;
  } while ((byte *)pcVar13 != (byte *)0xfef7c6);
  local_2e08 = 7;
  puVar20 = local_2dc4;
  if (0x20 < local_2e00) {
    puVar20 = local_2d60 + 7;
  }
  *puVar20 = 0;
                    /* try { // try from 00b73514 to 00b73518 has its CatchHandler @ 00b76172 */
  uVar10 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x40));
  *(undefined8 *)(this + 0x33f0) = uVar10;
                    /* try { // try from 00b73523 to 00b735b9 has its CatchHandler @ 00b769f6 */
  CEGUI::String::~String((String *)&local_2e08);
  CEGUI::Window::setZOrderingEnabled(SUB81(*(undefined8 *)(this + 0x33e0),0));
  CEGUI::Window::setZOrderingEnabled(SUB81(*(undefined8 *)(this + 0x33e8),0));
  CEGUI::Window::setZOrderingEnabled(SUB81(*(undefined8 *)(this + 0x33f0),0));
  local_2eb0 = 0x20;
  local_2ea8 = 0;
  local_2e98 = 0;
  local_2ea0 = 0;
  local_2e10 = (uint *)0x0;
  local_2eb8 = 0;
  local_2e90[0] = 0;
  CEGUI::String::grow((ulong)&local_2eb8);
  puVar20 = local_2e90;
  if (0x20 < local_2eb0) {
    puVar20 = local_2e10;
  }
  pcVar13 = "PetSlotsEquipment";
  do {
    bVar3 = *pcVar13;
    pcVar13 = pcVar13 + 1;
    *puVar20 = (uint)bVar3;
    puVar20 = puVar20 + 1;
  } while ((byte *)pcVar13 != (byte *)0xfeff78);
  local_2eb8 = 0x11;
  puVar20 = local_2e4c;
  if (0x20 < local_2eb0) {
    puVar20 = local_2e10 + 0x11;
  }
  *puVar20 = 0;
                    /* try { // try from 00b7361f to 00b73623 has its CatchHandler @ 00b76165 */
  uVar10 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x40));
  *(undefined8 *)(this + 0x33c8) = uVar10;
                    /* try { // try from 00b7362e to 00b7369a has its CatchHandler @ 00b769f6 */
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
  pcVar13 = "PetSlotsSpells";
  do {
    bVar3 = *pcVar13;
    pcVar13 = pcVar13 + 1;
    *puVar20 = (uint)bVar3;
    puVar20 = puVar20 + 1;
  } while ((byte *)pcVar13 != (byte *)0xfeff66);
  local_2f68 = 0xe;
  puVar20 = local_2f08;
  if (0x20 < local_2f60) {
    puVar20 = local_2ec0 + 0xe;
  }
  *puVar20 = 0;
                    /* try { // try from 00b73700 to 00b73704 has its CatchHandler @ 00b76163 */
  uVar10 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x40));
  *(undefined8 *)(this + 0x33d0) = uVar10;
                    /* try { // try from 00b7370f to 00b73789 has its CatchHandler @ 00b769f6 */
  CEGUI::String::~String((String *)&local_2f68);
  CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x33d0),0));
  local_3010 = 0x20;
  local_3008 = 0;
  local_2ff8 = 0;
  local_3000 = 0;
  local_2f70 = (uint *)0x0;
  local_3018 = 0;
  local_2ff0[0] = 0;
  CEGUI::String::grow((ulong)&local_3018);
  puVar20 = local_2ff0;
  if (0x20 < local_3010) {
    puVar20 = local_2f70;
  }
  pcVar13 = "PetSlotsFish";
  do {
    bVar3 = *pcVar13;
    pcVar13 = pcVar13 + 1;
    *puVar20 = (uint)bVar3;
    puVar20 = puVar20 + 1;
  } while ((byte *)pcVar13 != (byte *)0xfeff57);
  local_3018 = 0xc;
  puVar20 = local_2fc0;
  if (0x20 < local_3010) {
    puVar20 = local_2f70 + 0xc;
  }
  *puVar20 = 0;
                    /* try { // try from 00b737ef to 00b737f3 has its CatchHandler @ 00b76153 */
  uVar10 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x40));
  *(undefined8 *)(this + 0x33d8) = uVar10;
                    /* try { // try from 00b737fe to 00b73865 has its CatchHandler @ 00b769f6 */
  CEGUI::String::~String((String *)&local_3018);
  CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x33d8),0));
  local_3ea4 = 1;
  local_3e90 = this;
  do {
    STRINGS::GetValueAsString((uint)local_198);
                    /* try { // try from 00b7387b to 00b7387f has its CatchHandler @ 00b7614e */
    std::operator+((char *)local_1a8,(string *)"PetSlot");
    local_30c0 = 0x20;
    local_30b8 = 0;
    local_30a8 = 0;
    local_30b0 = 0;
    local_3020 = (undefined4 *)0x0;
    local_30c8 = 0;
    local_30a0[0] = 0;
    lVar11 = *(long *)(local_1a8[0] + -0x18);
                    /* try { // try from 00b738ea to 00b738ee has its CatchHandler @ 00b76149 */
    CEGUI::String::grow((ulong)&local_30c8);
    puVar19 = local_30a0;
    if (0x20 < local_30c0) {
      puVar19 = local_3020;
    }
    puVar19[lVar11] = 0;
    lVar29 = lVar11;
    while (lVar29 != 0) {
      lVar29 = lVar29 + -1;
      puVar19 = local_30a0;
      if (0x20 < local_30c0) {
        puVar19 = local_3020;
      }
      puVar19[lVar29] = (uint)*(byte *)(local_1a8[0] + lVar29);
    }
    local_30c8 = lVar11;
                    /* try { // try from 00b7395f to 00b73963 has its CatchHandler @ 00b7611a */
    lVar11 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x40));
                    /* try { // try from 00b7396f to 00b73973 has its CatchHandler @ 00b76149 */
    CEGUI::String::~String((String *)&local_30c8);
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
                    /* try { // try from 00b739ab to 00b739e4 has its CatchHandler @ 00b769f6 */
    CEGUI::Window::moveToFront();
    *(undefined1 *)(lVar11 + 0x213) = 0;
    CEGUI::Window::setWantsMultiClickEvents(SUB81(lVar11,0));
    *(CMerchantMenu **)(lVar11 + 0x1d8) = this + (ulong)(local_3ea4 + 0x12) * 4 + 0xb0;
    pcVar4 = *(code **)(*(long *)(lVar11 + 0x38) + 0x10);
    local_1b8[0] = operator_new(0x20);
    lVar29 = lVar11 + 0x38;
    *local_1b8[0] = &PTR__MemberFunctionSlot_00ff0270;
    local_1b8[0][2] = 0;
    local_1b8[0][1] = handle_PetItemClick;
    local_1b8[0][3] = this;
                    /* try { // try from 00b73a27 to 00b73a5c has its CatchHandler @ 00b7618a */
    (*pcVar4)(&local_458,lVar29,CEGUI::Window::EventMouseButtonDown,(SubscriberSlot *)local_1b8);
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
                    /* try { // try from 00b73a8d to 00b73aa3 has its CatchHandler @ 00b769f6 */
    CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_1b8);
    pcVar4 = *(code **)(*(long *)(lVar11 + 0x38) + 0x10);
    local_1c8[0] = operator_new(0x20);
    *local_1c8[0] = &PTR__MemberFunctionSlot_00ff0270;
    local_1c8[0][2] = 0;
    local_1c8[0][1] = handle_PetMouseOver;
    local_1c8[0][3] = this;
                    /* try { // try from 00b73ae2 to 00b73b17 has its CatchHandler @ 00b76176 */
    (*pcVar4)(&local_468,lVar29,CEGUI::Window::EventMouseEnters,(SubscriberSlot *)local_1c8);
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
                    /* try { // try from 00b73b48 to 00b73b5e has its CatchHandler @ 00b769f6 */
    CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_1c8);
    pcVar4 = *(code **)(*(long *)(lVar11 + 0x38) + 0x10);
    local_1d8[0] = operator_new(0x20);
    *local_1d8[0] = &PTR__MemberFunctionSlot_00ff0270;
    local_1d8[0][2] = 0;
    local_1d8[0][1] = handle_PetMouseOver;
    local_1d8[0][3] = this;
                    /* try { // try from 00b73b9d to 00b73bd2 has its CatchHandler @ 00b7620a */
    (*pcVar4)(&local_478,lVar29,CEGUI::Window::EventMouseMove,(SubscriberSlot *)local_1d8);
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
                    /* try { // try from 00b73c03 to 00b73c19 has its CatchHandler @ 00b769f6 */
    CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_1d8);
    pcVar4 = *(code **)(*(long *)(lVar11 + 0x38) + 0x10);
    local_1e8[0] = operator_new(0x20);
    *local_1e8[0] = &PTR__MemberFunctionSlot_00ff0270;
    local_1e8[0][2] = 0;
    local_1e8[0][1] = handle_PetMouseOut;
    local_1e8[0][3] = this;
                    /* try { // try from 00b73c58 to 00b73c8d has its CatchHandler @ 00b761fa */
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
                    /* try { // try from 00b73cbe to 00b73d33 has its CatchHandler @ 00b769f6 */
    CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_1e8);
    *(long *)(local_3e90 + 0x2790) = lVar11;
    local_32d0 = 0x20;
    local_32c8 = 0;
    local_32b8 = 0;
    local_32c0 = 0;
    local_3230 = (undefined4 *)0x0;
    local_32d8 = 0;
    local_32b0[0] = 0;
    CEGUI::String::grow((ulong)&local_32d8);
    local_32d8 = 0;
    puVar19 = local_32b0;
    if (0x20 < local_32d0) {
      puVar19 = local_3230;
    }
    *puVar19 = 0;
                    /* try { // try from 00b73d72 to 00b73d76 has its CatchHandler @ 00b7620f */
    std::string::string((string *)local_1f8,"gui_",&local_3e);
                    /* try { // try from 00b73d87 to 00b73d8b has its CatchHandler @ 00b76112 */
    STRINGS::uniqueName((STRINGS *)local_208,(string *)local_1f8);
    local_3220 = 0x20;
    local_3218 = 0;
    local_3208 = 0;
    local_3210 = 0;
    local_3180 = (undefined4 *)0x0;
    local_3228 = 0;
    local_3200[0] = 0;
    lVar11 = *(long *)(local_208[0] + -0x18);
                    /* try { // try from 00b73df6 to 00b73dfa has its CatchHandler @ 00b76017 */
    CEGUI::String::grow((ulong)&local_3228);
    puVar19 = local_3200;
    if (0x20 < local_3220) {
      puVar19 = local_3180;
    }
    puVar19[lVar11] = 0;
    lVar29 = lVar11;
    while (lVar29 != 0) {
      lVar29 = lVar29 + -1;
      puVar19 = local_3200;
      if (0x20 < local_3220) {
        puVar19 = local_3180;
      }
      puVar19[lVar29] = (uint)*(byte *)(local_208[0] + lVar29);
    }
    local_3170 = 0x20;
    local_3168 = 0;
    local_3158 = 0;
    local_3160 = 0;
    local_30d0 = (uint *)0x0;
    local_3178 = 0;
    local_3150[0] = 0;
    pcVar13 = (char *)0x0;
    cVar2 = s_GuiLook_StaticText_00fe4872[0];
    while (cVar2 != '\0') {
      cVar2 = pcVar13[0xfe4873];
      pcVar13 = pcVar13 + 1;
    }
    local_3228 = lVar11;
    if (pcVar13 == CEGUI::String::npos) {
                    /* try { // try from 00b75fce to 00b75fd2 has its CatchHandler @ 00b7607c */
      std::string::string((string *)local_308,"Length for utf8 encoded string can not be \'npos\'",
                          local_61);
      plVar21 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00b75fe6 to 00b75fea has its CatchHandler @ 00b76064 */
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
                    /* try { // try from 00b7600d to 00b76011 has its CatchHandler @ 00b75f6d */
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
                    /* try { // try from 00b746f0 to 00b746f4 has its CatchHandler @ 00b75f6d */
    CEGUI::String::grow((ulong)&local_3178);
    puVar20 = local_3150;
    if (0x20 < local_3170) {
      puVar20 = local_30d0;
    }
    if (pcVar13 == (char *)0x0) {
      pcVar28 = (char *)0x0;
      if (s_GuiLook_StaticText_00fe4872[0] != '\0') {
        do {
          pcVar13 = pcVar28 + 1;
          pcVar27 = pcVar28 + 0xfe4873;
          pcVar28 = pcVar13;
        } while (*pcVar27 != '\0');
        bVar30 = pcVar13 != (char *)0x0 && local_3170 != 0;
        goto LAB_00b7471e;
      }
    }
    else {
      bVar30 = local_3170 != 0;
LAB_00b7471e:
      if (bVar30) {
        pcVar28 = (char *)0x0;
        uVar22 = local_3170;
        while( true ) {
          bVar3 = pcVar28[0xfe4872];
          uVar9 = (uint)bVar3;
          iVar6 = (int)pcVar28;
          pcVar27 = (char *)(ulong)(iVar6 + 1);
          pcVar28 = pcVar27;
          if ((char)bVar3 < '\0') {
            if (bVar3 < 0xe0) {
              pcVar28 = (char *)(ulong)(iVar6 + 2);
              uVar9 = (byte)pcVar27[0xfe4872] & 0x3f | (uVar9 & 0x1f) << 6;
            }
            else if (bVar3 < 0xf0) {
              pcVar28 = (char *)(ulong)(iVar6 + 3);
              uVar9 = (byte)"GuiLook/StaticText"[iVar6 + 2] & 0x3f | (uVar9 & 0xf) << 0xc |
                      ((byte)pcVar27[0xfe4872] & 0x3f) << 6;
            }
            else {
              pcVar28 = (char *)(ulong)(iVar6 + 4);
              uVar9 = ((byte)pcVar27[0xfe4872] & 0x3f) << 0xc |
                      (byte)"GuiLook/StaticText"[iVar6 + 3] & 0x3f | (uVar9 & 7) << 0x12 |
                      ((byte)"GuiLook/StaticText"[iVar6 + 2] & 0x3f) << 6;
            }
          }
          *puVar20 = uVar9;
          uVar22 = uVar22 - 1;
          if ((pcVar13 <= pcVar28) || (uVar22 == 0)) break;
          puVar20 = puVar20 + 1;
        }
      }
    }
    puVar20 = local_3150;
    if (0x20 < local_3170) {
      puVar20 = local_30d0;
    }
    puVar20[lVar11] = 0;
    local_3178 = lVar11;
                    /* try { // try from 00b747ec to 00b747f0 has its CatchHandler @ 00b75ed2 */
    uVar10 = CEGUI::WindowManager::createWindow
                       (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,(String *)&local_3178,
                        (String *)&local_3228);
    *(undefined8 *)(local_3e90 + 0x31d0) = uVar10;
                    /* try { // try from 00b74800 to 00b74804 has its CatchHandler @ 00b75f6d */
    CEGUI::String::~String((String *)&local_3178);
                    /* try { // try from 00b7480d to 00b74811 has its CatchHandler @ 00b76017 */
    CEGUI::String::~String((String *)&local_3228);
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
                    /* try { // try from 00b74849 to 00b748b5 has its CatchHandler @ 00b769f6 */
    CEGUI::String::~String((String *)&local_32d8);
    local_3380 = 0x20;
    local_3378 = 0;
    local_3368 = 0;
    local_3370 = 0;
    local_32e0 = (uint *)0x0;
    local_3388 = 0;
    local_3360[0] = 0;
    CEGUI::String::grow((ulong)&local_3388);
    puVar20 = local_3360;
    if (0x20 < local_3380) {
      puVar20 = local_32e0;
    }
    pcVar13 = "Serif";
    do {
      bVar3 = *pcVar13;
      pcVar13 = pcVar13 + 1;
      *puVar20 = (uint)bVar3;
      puVar20 = puVar20 + 1;
    } while ((byte *)pcVar13 != (byte *)0xfe4949);
    local_3388 = 5;
    puVar20 = local_334c;
    if (0x20 < local_3380) {
      puVar20 = local_32e0 + 5;
    }
    *puVar20 = 0;
                    /* try { // try from 00b74927 to 00b7492b has its CatchHandler @ 00b760d2 */
    CEGUI::Window::setFont(*(String **)(local_3e90 + 0x31d0));
                    /* try { // try from 00b7492f to 00b74946 has its CatchHandler @ 00b769f6 */
    CEGUI::String::~String((String *)&local_3388);
    CEGUI::Window::getSize();
                    /* try { // try from 00b74956 to 00b7495a has its CatchHandler @ 00b760cc */
    CEGUI::Window::setSize(*(UVector2 **)(local_3e90 + 0x31d0));
                    /* try { // try from 00b7495e to 00b74962 has its CatchHandler @ 00b769f6 */
    puVar17 = (undefined8 *)CEGUI::Window::getPosition();
    local_4a8 = *puVar17;
    local_4a0 = puVar17[1];
    local_34e0 = 0x20;
    local_34d8 = 0;
    local_34c8 = 0;
    local_34d0 = 0;
    local_3440 = (uint *)0x0;
    local_34e8 = 0;
    local_34c0[0] = 0;
                    /* try { // try from 00b749dd to 00b749e1 has its CatchHandler @ 00b760c4 */
    CEGUI::String::grow((ulong)&local_34e8);
    puVar20 = local_34c0;
    if (0x20 < local_34e0) {
      puVar20 = local_3440;
    }
    pcVar13 = "RightAligned";
    do {
      bVar3 = *pcVar13;
      pcVar13 = pcVar13 + 1;
      *puVar20 = (uint)bVar3;
      puVar20 = puVar20 + 1;
    } while ((byte *)pcVar13 != (byte *)0xfe602d);
    local_34e8 = 0xc;
    puVar20 = local_3490;
    if (0x20 < local_34e0) {
      puVar20 = local_3440 + 0xc;
    }
    *puVar20 = 0;
    local_3430 = 0x20;
    local_3428 = 0;
    local_3418 = 0;
    local_3420 = 0;
    local_3390 = (uint *)0x0;
    local_3438 = 0;
    local_3410[0] = 0;
                    /* try { // try from 00b74aa5 to 00b74aa9 has its CatchHandler @ 00b760c2 */
    CEGUI::String::grow((ulong)&local_3438);
    puVar20 = local_3410;
    if (0x20 < local_3430) {
      puVar20 = local_3390;
    }
    pcVar13 = "HorzTextFormatting";
    do {
      bVar3 = *pcVar13;
      pcVar13 = pcVar13 + 1;
      *puVar20 = (uint)bVar3;
      puVar20 = puVar20 + 1;
    } while ((byte *)pcVar13 != (byte *)0xfe48cf);
    local_3438 = 0x12;
    puVar20 = local_33c8;
    if (0x20 < local_3430) {
      puVar20 = local_3390 + 0x12;
    }
    *puVar20 = 0;
                    /* try { // try from 00b74b1e to 00b74b22 has its CatchHandler @ 00b760be */
    CEGUI::PropertySet::setProperty(*(String **)(local_3e90 + 0x31d0),(String *)&local_3438);
                    /* try { // try from 00b74b26 to 00b74b2a has its CatchHandler @ 00b760c2 */
    CEGUI::String::~String((String *)&local_3438);
                    /* try { // try from 00b74b2e to 00b74b9a has its CatchHandler @ 00b760c4 */
    CEGUI::String::~String((String *)&local_34e8);
    local_3640 = 0x20;
    local_3638 = 0;
    local_3628 = 0;
    local_3630 = 0;
    local_35a0 = (uint *)0x0;
    local_3648 = 0;
    local_3620[0] = 0;
    CEGUI::String::grow((ulong)&local_3648);
    puVar20 = local_3620;
    if (0x20 < local_3640) {
      puVar20 = local_35a0;
    }
    pcVar13 = "BottomAligned";
    do {
      bVar3 = *pcVar13;
      pcVar13 = pcVar13 + 1;
      *puVar20 = (uint)bVar3;
      puVar20 = puVar20 + 1;
    } while ((byte *)pcVar13 != (byte *)0xfe6020);
    local_3648 = 0xd;
    puVar20 = local_35ec;
    if (0x20 < local_3640) {
      puVar20 = local_35a0 + 0xd;
    }
    *puVar20 = 0;
    local_3590 = 0x20;
    local_3588 = 0;
    local_3578 = 0;
    local_3580 = 0;
    local_34f0 = (uint *)0x0;
    local_3598 = 0;
    local_3570[0] = 0;
                    /* try { // try from 00b74c5c to 00b74c60 has its CatchHandler @ 00b760b9 */
    CEGUI::String::grow((ulong)&local_3598);
    puVar20 = local_3570;
    if (0x20 < local_3590) {
      puVar20 = local_34f0;
    }
    pcVar13 = "VertFormatting";
    do {
      bVar3 = *pcVar13;
      pcVar13 = pcVar13 + 1;
      *puVar20 = (uint)bVar3;
      puVar20 = puVar20 + 1;
    } while ((byte *)pcVar13 != (byte *)0xfe48ae);
    local_3598 = 0xe;
    puVar20 = local_3538;
    if (0x20 < local_3590) {
      puVar20 = local_34f0 + 0xe;
    }
    *puVar20 = 0;
                    /* try { // try from 00b74cd5 to 00b74cd9 has its CatchHandler @ 00b760a1 */
    CEGUI::PropertySet::setProperty(*(String **)(local_3e90 + 0x31d0),(String *)&local_3598);
                    /* try { // try from 00b74cdd to 00b74ce1 has its CatchHandler @ 00b760b9 */
    CEGUI::String::~String((String *)&local_3598);
                    /* try { // try from 00b74ce5 to 00b74da2 has its CatchHandler @ 00b760c4 */
    CEGUI::String::~String((String *)&local_3648);
    *(undefined1 *)(*(long *)(local_3e90 + 0x31d0) + 0x3e2) = 1;
    CEGUI::Window::setPosition(*(UVector2 **)(local_3e90 + 0x31d0));
    CEGUI::Window::addChildWindow(*(Window **)(*(long *)(local_3e90 + 0x2790) + 0xb0));
    local_36f0 = 0x20;
    local_36e8 = 0;
    local_36d8 = 0;
    local_36e0 = 0;
    local_3650 = (undefined4 *)0x0;
    local_36f8 = 0;
    local_36d0[0] = 0;
    if (CEGUI::String::npos == (char *)0x0) {
                    /* try { // try from 00b766af to 00b766b3 has its CatchHandler @ 00b76747 */
      std::string::string((string *)local_318,"Length for utf8 encoded string can not be \'npos\'",
                          local_65);
      plVar21 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00b766c7 to 00b766cb has its CatchHandler @ 00b7672f */
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
                    /* try { // try from 00b766ee to 00b766f2 has its CatchHandler @ 00b760c4 */
      __cxa_throw(plVar21,&std::length_error::typeinfo,std::length_error::~length_error);
    }
    CEGUI::String::grow((ulong)&local_36f8);
    local_36f8 = 0;
    puVar19 = local_36d0;
    if (0x20 < local_36f0) {
      puVar19 = local_3650;
    }
    *puVar19 = 0;
                    /* try { // try from 00b74ddc to 00b74de0 has its CatchHandler @ 00b76692 */
    CEGUI::Window::setText(*(String **)(local_3e90 + 0x31d0));
                    /* try { // try from 00b74de4 to 00b74e1c has its CatchHandler @ 00b760c4 */
    CEGUI::String::~String((String *)&local_36f8);
    CEGUI::colour::colour(local_518,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc);
    CEGUI::PropertyHelper::colourToString(local_37a8);
    local_3850 = 0x20;
    local_3848 = 0;
    local_3838 = 0;
    local_3840 = 0;
    local_37b0 = (uint *)0x0;
    local_3858 = 0;
    local_3830[0] = 0;
                    /* try { // try from 00b74e80 to 00b74e84 has its CatchHandler @ 00b766f3 */
    CEGUI::String::grow((ulong)&local_3858);
    puVar20 = local_3830;
    if (0x20 < local_3850) {
      puVar20 = local_37b0;
    }
    pbVar15 = (byte *)0xfe4654;
    do {
      bVar3 = *pbVar15;
      pbVar15 = pbVar15 + 1;
      *puVar20 = (uint)bVar3;
      puVar20 = puVar20 + 1;
    } while (pbVar15 != (byte *)0xfe465e);
    local_3858 = 10;
    puVar20 = local_3808;
    if (0x20 < local_3850) {
      puVar20 = local_37b0 + 10;
    }
    *puVar20 = 0;
                    /* try { // try from 00b74ef7 to 00b74efb has its CatchHandler @ 00b76668 */
    CEGUI::PropertySet::setProperty(*(String **)(local_3e90 + 0x31d0),(String *)&local_3858);
                    /* try { // try from 00b74eff to 00b74f03 has its CatchHandler @ 00b766f3 */
    CEGUI::String::~String((String *)&local_3858);
                    /* try { // try from 00b74f07 to 00b74f86 has its CatchHandler @ 00b760c4 */
    CEGUI::String::~String(local_37a8);
    CEGUI::Window::setAlwaysOnTop(SUB81(*(undefined8 *)(local_3e90 + 0x31d0),0));
    local_3a60 = 0x20;
    local_3a58 = 0;
    local_3a48 = 0;
    local_3a50 = 0;
    local_39c0 = (undefined4 *)0x0;
    local_3a68 = 0;
    local_3a40[0] = 0;
    CEGUI::String::grow((ulong)&local_3a68);
    local_3a68 = 0;
    puVar19 = local_3a40;
    if (0x20 < local_3a60) {
      puVar19 = local_39c0;
    }
    *puVar19 = 0;
                    /* try { // try from 00b74fc5 to 00b74fc9 has its CatchHandler @ 00b76675 */
    std::string::string((string *)local_218,"gui_",&local_3f);
                    /* try { // try from 00b74fda to 00b74fde has its CatchHandler @ 00b7666d */
    STRINGS::uniqueName((STRINGS *)local_228,(string *)local_218);
    local_39b0 = 0x20;
    local_39a8 = 0;
    local_3998 = 0;
    local_39a0 = 0;
    local_3910 = (undefined4 *)0x0;
    local_39b8 = 0;
    local_3990[0] = 0;
    lVar11 = *(long *)(local_228[0] + -0x18);
                    /* try { // try from 00b75049 to 00b7504d has its CatchHandler @ 00b76623 */
    CEGUI::String::grow((ulong)&local_39b8);
    puVar19 = local_3990;
    if (0x20 < local_39b0) {
      puVar19 = local_3910;
    }
    puVar19[lVar11] = 0;
    lVar29 = lVar11;
    while (lVar29 != 0) {
      lVar29 = lVar29 + -1;
      puVar19 = local_3990;
      if (0x20 < local_39b0) {
        puVar19 = local_3910;
      }
      puVar19[lVar29] = (uint)*(byte *)(local_228[0] + lVar29);
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
                    /* try { // try from 00b765df to 00b765e3 has its CatchHandler @ 00b7667a */
      std::string::string((string *)local_328,"Length for utf8 encoded string can not be \'npos\'",
                          local_67);
      plVar21 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00b765f7 to 00b765fb has its CatchHandler @ 00b76650 */
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
                    /* try { // try from 00b7661e to 00b76622 has its CatchHandler @ 00b763c5 */
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
                    /* try { // try from 00b7517c to 00b75180 has its CatchHandler @ 00b763c5 */
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
        goto LAB_00b751aa;
      }
    }
    else {
      bVar30 = local_3900 != 0;
LAB_00b751aa:
      if (bVar30) {
        pcVar28 = (char *)0x0;
        uVar22 = local_3900;
        while( true ) {
          bVar3 = pcVar28[0xfd0bff];
          uVar9 = (uint)bVar3;
          iVar6 = (int)pcVar28;
          pcVar27 = (char *)(ulong)(iVar6 + 1);
          pcVar28 = pcVar27;
          if ((char)bVar3 < '\0') {
            if (bVar3 < 0xe0) {
              pcVar28 = (char *)(ulong)(iVar6 + 2);
              uVar9 = (byte)pcVar27[0xfd0bff] & 0x3f | (uVar9 & 0x1f) << 6;
            }
            else if (bVar3 < 0xf0) {
              pcVar28 = (char *)(ulong)(iVar6 + 3);
              uVar9 = (byte)"GuiLook/StaticImage"[iVar6 + 2] & 0x3f | (uVar9 & 0xf) << 0xc |
                      ((byte)pcVar27[0xfd0bff] & 0x3f) << 6;
            }
            else {
              pcVar28 = (char *)(ulong)(iVar6 + 4);
              uVar9 = ((byte)pcVar27[0xfd0bff] & 0x3f) << 0xc |
                      (byte)"GuiLook/StaticImage"[iVar6 + 3] & 0x3f | (uVar9 & 7) << 0x12 |
                      ((byte)"GuiLook/StaticImage"[iVar6 + 2] & 0x3f) << 6;
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
                    /* try { // try from 00b7527c to 00b75280 has its CatchHandler @ 00b76375 */
    pUVar18 = (UVector2 *)
              CEGUI::WindowManager::createWindow
                        (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,(String *)&local_3908,
                         (String *)&local_39b8);
                    /* try { // try from 00b75287 to 00b7528b has its CatchHandler @ 00b763c5 */
    CEGUI::String::~String((String *)&local_3908);
                    /* try { // try from 00b75294 to 00b75298 has its CatchHandler @ 00b76623 */
    CEGUI::String::~String((String *)&local_39b8);
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
                    /* try { // try from 00b752d0 to 00b75340 has its CatchHandler @ 00b760c4 */
    CEGUI::String::~String((String *)&local_3a68);
    CEGUI::Window::addChildWindow(*(Window **)(*(long *)(local_3e90 + 0x2790) + 0xb0));
    pUVar18[0x213] = (UVector2)0x0;
    CEGUI::Window::setWantsMultiClickEvents(SUB81(pUVar18,0));
    pUVar18[0x3e2] = (UVector2)0x1;
    CEGUI::EventSet::setMutedState((bool)(SUB81(pUVar18,0) + '8'));
    CEGUI::Window::getPosition();
    CEGUI::Window::setPosition(pUVar18);
    CEGUI::Window::getSize();
                    /* try { // try from 00b75347 to 00b7534b has its CatchHandler @ 00b76314 */
    CEGUI::Window::setSize(pUVar18);
    *(UVector2 **)(local_3e90 + 0x2cb0) = pUVar18;
    local_3c70 = 0x20;
    local_3c68 = 0;
    local_3c58 = 0;
    local_3c60 = 0;
    local_3bd0 = (undefined4 *)0x0;
    local_3c78 = 0;
    local_3c50[0] = 0;
                    /* try { // try from 00b753b5 to 00b753b9 has its CatchHandler @ 00b760c4 */
    CEGUI::String::grow((ulong)&local_3c78);
    local_3c78 = 0;
    puVar19 = local_3bd0;
    if (local_3c70 < 0x21) {
      puVar19 = local_3c50;
    }
    *puVar19 = 0;
                    /* try { // try from 00b753fc to 00b75400 has its CatchHandler @ 00b75e40 */
    std::string::string((string *)local_238,"gui_",&local_40);
                    /* try { // try from 00b75411 to 00b75415 has its CatchHandler @ 00b762b0 */
    STRINGS::uniqueName((STRINGS *)local_248,(string *)local_238);
    local_3bc0 = 0x20;
    local_3bb8 = 0;
    local_3ba8 = 0;
    local_3bb0 = 0;
    local_3b20 = (undefined4 *)0x0;
    local_3bc8 = 0;
    local_3ba0[0] = 0;
    lVar11 = *(long *)(local_248[0] + -0x18);
                    /* try { // try from 00b75483 to 00b75487 has its CatchHandler @ 00b762ab */
    CEGUI::String::grow((ulong)&local_3bc8);
    puVar19 = local_3ba0;
    if (0x20 < local_3bc0) {
      puVar19 = local_3b20;
    }
    puVar19[lVar11] = 0;
    if (lVar11 != 0) {
      lVar29 = lVar11;
      do {
        lVar29 = lVar29 + -1;
        puVar19 = local_3ba0;
        if (0x20 < local_3bc0) {
          puVar19 = local_3b20;
        }
        puVar19[lVar29] = (uint)*(byte *)(local_248[0] + lVar29);
      } while (lVar29 != 0);
    }
    local_3b10 = 0x20;
    local_3b08 = 0;
    local_3af8 = 0;
    local_3b00 = 0;
    local_3a70 = (uint *)0x0;
    local_3b18 = 0;
    local_3af0[0] = 0;
    pcVar13 = (char *)0x0;
    cVar2 = s_GuiLook_StaticImage_00fd0bff[0];
    while (cVar2 != '\0') {
      cVar2 = pcVar13[0xfd0c00];
      pcVar13 = pcVar13 + 1;
    }
    local_3bc8 = lVar11;
    if (pcVar13 == CEGUI::String::npos) {
                    /* try { // try from 00b76267 to 00b7626b has its CatchHandler @ 00b762f2 */
      std::string::string((string *)local_338,"Length for utf8 encoded string can not be \'npos\'",
                          local_6b);
      plVar21 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00b7627f to 00b76283 has its CatchHandler @ 00b762da */
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
                    /* try { // try from 00b762a6 to 00b762aa has its CatchHandler @ 00b76225 */
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
                    /* try { // try from 00b755bf to 00b755c3 has its CatchHandler @ 00b76225 */
    CEGUI::String::grow((ulong)&local_3b18);
    puVar20 = local_3af0;
    if (0x20 < local_3b10) {
      puVar20 = local_3a70;
    }
    if (pcVar13 == (char *)0x0) {
      pcVar28 = (char *)0x0;
      if (s_GuiLook_StaticImage_00fd0bff[0] != '\0') {
        do {
          pcVar13 = pcVar28 + 1;
          pcVar27 = pcVar28 + 0xfd0c00;
          pcVar28 = pcVar13;
        } while (*pcVar27 != '\0');
        bVar30 = pcVar13 != (char *)0x0 && local_3b10 != 0;
        goto LAB_00b755ed;
      }
    }
    else {
      bVar30 = local_3b10 != 0;
LAB_00b755ed:
      if (bVar30) {
        pcVar28 = (char *)0x0;
        uVar22 = local_3b10;
        while( true ) {
          bVar3 = pcVar28[0xfd0bff];
          uVar9 = (uint)bVar3;
          iVar6 = (int)pcVar28;
          pcVar27 = (char *)(ulong)(iVar6 + 1);
          pcVar28 = pcVar27;
          if ((char)bVar3 < '\0') {
            if (bVar3 < 0xe0) {
              pcVar28 = (char *)(ulong)(iVar6 + 2);
              uVar9 = (byte)pcVar27[0xfd0bff] & 0x3f | (uVar9 & 0x1f) << 6;
            }
            else if (bVar3 < 0xf0) {
              pcVar28 = (char *)(ulong)(iVar6 + 3);
              uVar9 = (byte)"GuiLook/StaticImage"[iVar6 + 2] & 0x3f | (uVar9 & 0xf) << 0xc |
                      ((byte)pcVar27[0xfd0bff] & 0x3f) << 6;
            }
            else {
              pcVar28 = (char *)(ulong)(iVar6 + 4);
              uVar9 = ((byte)pcVar27[0xfd0bff] & 0x3f) << 0xc |
                      (byte)"GuiLook/StaticImage"[iVar6 + 3] & 0x3f | (uVar9 & 7) << 0x12 |
                      ((byte)"GuiLook/StaticImage"[iVar6 + 2] & 0x3f) << 6;
            }
          }
          *puVar20 = uVar9;
          uVar22 = uVar22 - 1;
          if ((pcVar13 <= pcVar28) || (uVar22 == 0)) break;
          puVar20 = puVar20 + 1;
        }
      }
    }
    puVar20 = local_3af0;
    if (0x20 < local_3b10) {
      puVar20 = local_3a70;
    }
    puVar20[lVar11] = 0;
    local_3b18 = lVar11;
                    /* try { // try from 00b756b7 to 00b756bb has its CatchHandler @ 00b763ca */
    pUVar18 = (UVector2 *)
              CEGUI::WindowManager::createWindow
                        (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,(String *)&local_3b18,
                         (String *)&local_3bc8);
                    /* try { // try from 00b756c2 to 00b756c6 has its CatchHandler @ 00b76225 */
    CEGUI::String::~String((String *)&local_3b18);
                    /* try { // try from 00b756ca to 00b756ce has its CatchHandler @ 00b762ab */
    CEGUI::String::~String((String *)&local_3bc8);
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
                    /* try { // try from 00b7570b to 00b7576c has its CatchHandler @ 00b760c4 */
    CEGUI::String::~String((String *)&local_3c78);
    CEGUI::Window::addChildWindow(*(Window **)(this + 0x38));
    pUVar18[0x213] = (UVector2)0x0;
    CEGUI::Window::setWantsMultiClickEvents(SUB81(pUVar18,0));
    pUVar18[0x3e2] = (UVector2)0x1;
    CEGUI::EventSet::setMutedState((bool)(SUB81(pUVar18,0) + '8'));
    CEGUI::Window::getPosition();
    CEGUI::Window::setPosition(pUVar18);
    CEGUI::Window::getSize();
                    /* try { // try from 00b75773 to 00b75777 has its CatchHandler @ 00b7645d */
    CEGUI::Window::setSize(pUVar18);
    *(UVector2 **)(local_3e90 + 0x2f40) = pUVar18;
    local_3e80 = 0x20;
    local_3e78 = 0;
    local_3e68 = 0;
    local_3e70 = 0;
    local_3de0 = (undefined4 *)0x0;
    local_3e88 = 0;
    local_3e60[0] = 0;
                    /* try { // try from 00b757cf to 00b757d3 has its CatchHandler @ 00b760c4 */
    CEGUI::String::grow((ulong)&local_3e88);
    local_3e88 = 0;
    puVar19 = local_3e60;
    if (0x20 < local_3e80) {
      puVar19 = local_3de0;
    }
    *puVar19 = 0;
                    /* try { // try from 00b7580c to 00b75810 has its CatchHandler @ 00b76458 */
    std::string::string((string *)local_258,"gui_",&local_41);
                    /* try { // try from 00b75821 to 00b75825 has its CatchHandler @ 00b76450 */
    STRINGS::uniqueName((STRINGS *)local_268,(string *)local_258);
    local_3dd0 = 0x20;
    local_3dc8 = 0;
    local_3db8 = 0;
    local_3dc0 = 0;
    local_3d30 = (undefined4 *)0x0;
    local_3dd8 = 0;
    local_3db0[0] = 0;
    lVar11 = *(long *)(local_268[0] + -0x18);
                    /* try { // try from 00b75893 to 00b75897 has its CatchHandler @ 00b76448 */
    CEGUI::String::grow((ulong)&local_3dd8);
    puVar19 = local_3db0;
    if (0x20 < local_3dd0) {
      puVar19 = local_3d30;
    }
    puVar19[lVar11] = 0;
    if (lVar11 != 0) {
      lVar29 = lVar11;
      do {
        lVar29 = lVar29 + -1;
        puVar19 = local_3db0;
        if (0x20 < local_3dd0) {
          puVar19 = local_3d30;
        }
        puVar19[lVar29] = (uint)*(byte *)(local_268[0] + lVar29);
      } while (lVar29 != 0);
    }
    local_3d20 = 0x20;
    local_3d18 = 0;
    local_3d08 = 0;
    local_3d10 = 0;
    local_3c80 = (uint *)0x0;
    local_3d28 = 0;
    local_3d00[0] = 0;
    pcVar13 = (char *)0x0;
    cVar2 = s_GuiLook_StaticImage_00fd0bff[0];
    while (cVar2 != '\0') {
      cVar2 = pcVar13[0xfd0c00];
      pcVar13 = pcVar13 + 1;
    }
    local_3dd8 = lVar11;
    if (pcVar13 == CEGUI::String::npos) {
                    /* try { // try from 00b75f29 to 00b75f2d has its CatchHandler @ 00b76012 */
      std::string::string((string *)local_348,"Length for utf8 encoded string can not be \'npos\'",
                          local_6f);
      plVar21 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00b75f41 to 00b75f45 has its CatchHandler @ 00b75f9e */
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
                    /* try { // try from 00b75f68 to 00b75f6c has its CatchHandler @ 00b75e77 */
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
                    /* try { // try from 00b759b8 to 00b759bc has its CatchHandler @ 00b75e77 */
    CEGUI::String::grow((ulong)&local_3d28);
    puVar20 = local_3d00;
    if (0x20 < local_3d20) {
      puVar20 = local_3c80;
    }
    if (pcVar13 == (char *)0x0) {
      for (; pcVar13[0xfd0bff] != '\0'; pcVar13 = pcVar13 + 1) {
      }
      if (pcVar13 != (char *)0x0) goto LAB_00b759dd;
    }
    else {
LAB_00b759dd:
      if (local_3d20 != 0) {
        pcVar28 = (char *)0x0;
        uVar22 = local_3d20;
        while( true ) {
          bVar3 = pcVar28[0xfd0bff];
          uVar9 = (uint)bVar3;
          iVar6 = (int)pcVar28;
          pcVar27 = (char *)(ulong)(iVar6 + 1);
          pcVar28 = pcVar27;
          if ((char)bVar3 < '\0') {
            if (bVar3 < 0xe0) {
              pcVar28 = (char *)(ulong)(iVar6 + 2);
              uVar9 = (byte)pcVar27[0xfd0bff] & 0x3f | (uVar9 & 0x1f) << 6;
            }
            else if (bVar3 < 0xf0) {
              pcVar28 = (char *)(ulong)(iVar6 + 3);
              uVar9 = (byte)"GuiLook/StaticImage"[iVar6 + 2] & 0x3f | (uVar9 & 0xf) << 0xc |
                      ((byte)pcVar27[0xfd0bff] & 0x3f) << 6;
            }
            else {
              pcVar28 = (char *)(ulong)(iVar6 + 4);
              uVar9 = ((byte)pcVar27[0xfd0bff] & 0x3f) << 0xc |
                      (byte)"GuiLook/StaticImage"[iVar6 + 3] & 0x3f | (uVar9 & 7) << 0x12 |
                      ((byte)"GuiLook/StaticImage"[iVar6 + 2] & 0x3f) << 6;
            }
          }
          *puVar20 = uVar9;
          uVar22 = uVar22 - 1;
          if ((pcVar13 <= pcVar28) || (uVar22 == 0)) break;
          puVar20 = puVar20 + 1;
        }
      }
    }
    puVar20 = local_3d00;
    if (0x20 < local_3d20) {
      puVar20 = local_3c80;
    }
    puVar20[lVar11] = 0;
    local_3d28 = lVar11;
                    /* try { // try from 00b75a7e to 00b75a82 has its CatchHandler @ 00b765a1 */
    pUVar18 = (UVector2 *)
              CEGUI::WindowManager::createWindow
                        (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,(String *)&local_3d28,
                         (String *)&local_3dd8);
                    /* try { // try from 00b75a89 to 00b75a8d has its CatchHandler @ 00b75e77 */
    CEGUI::String::~String((String *)&local_3d28);
                    /* try { // try from 00b75a91 to 00b75a95 has its CatchHandler @ 00b76448 */
    CEGUI::String::~String((String *)&local_3dd8);
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
                    /* try { // try from 00b75acd to 00b75b4a has its CatchHandler @ 00b760c4 */
    CEGUI::String::~String((String *)&local_3e88);
    CEGUI::Window::addChildWindow(*(Window **)(*(long *)(local_3e90 + 0x2790) + 0xb0));
    pUVar18[0x213] = (UVector2)0x0;
    bVar30 = SUB81(pUVar18,0);
    CEGUI::Window::setWantsMultiClickEvents(bVar30);
    pUVar18[0x3e2] = (UVector2)0x1;
    CEGUI::EventSet::setMutedState((bool)(bVar30 + '8'));
    CEGUI::Window::getPosition();
    CEGUI::Window::setPosition(pUVar18);
    CEGUI::Window::getSize();
                    /* try { // try from 00b75b51 to 00b75b55 has its CatchHandler @ 00b76544 */
    CEGUI::Window::setSize(pUVar18);
                    /* try { // try from 00b75b5e to 00b75b62 has its CatchHandler @ 00b760c4 */
    CEGUI::Window::setAlwaysOnTop(bVar30);
    *(UVector2 **)(local_3e90 + 0x2a20) = pUVar18;
    local_3ea4 = local_3ea4 + 1;
    local_3e90 = local_3e90 + 8;
    if (local_3ea4 == 0x40) {
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

/* address=00b772a0
   symbol=CMerchantMenu::CMerchantMenu */

/* WARNING: Removing unreachable block (ram,0x00b77572) */
/* WARNING: Removing unreachable block (ram,0x00b77546) */
/* CMerchantMenu::CMerchantMenu(CGameUI&, CSettings&, Ogre::RenderWindow*, Ogre::SceneManager*,
   CEGUI::Window*, CResourceManager*) */

void __thiscall
CMerchantMenu::CMerchantMenu
          (CMerchantMenu *this,CGameUI *param_1,CSettings *param_2,RenderWindow *param_3,
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
  *(undefined ***)this = &PTR__CMerchantMenu_00ff0110;
  *(undefined ***)(this + 0x10) = &PTR__CMerchantMenu_00ff01c0;
  *(Window **)(this + 0x18) = param_5;
  *(undefined8 *)(this + 0x50) = 0;
  *(undefined8 *)(this + 0x58) = 0;
  this[0x60] = (CMerchantMenu)0x0;
  this[0x61] = (CMerchantMenu)0x1;
  this[0x62] = (CMerchantMenu)0x0;
  *(CSettings **)(this + 0x68) = param_2;
  *(CGameUI **)(this + 0x70) = param_1;
  *(SceneManager **)(this + 0x78) = param_4;
  *(RenderWindow **)(this + 0x80) = param_3;
  *(undefined8 *)(this + 0x90) = 0;
  *(CResourceManager **)(this + 0x98) = param_6;
  *(undefined4 *)(this + 0xa0) = 0;
  *(undefined8 *)(this + 0xa8) = 0;
  *(undefined4 *)(this + 0x3428) = 0xffffffff;
  *(undefined4 *)(this + 0x342c) = 0xffffffff;
  *(undefined4 *)(this + 0x3430) = 0xffffffff;
  *(undefined4 *)(this + 0x3434) = 0xffffffff;
  *(undefined8 *)(this + 0x3438) = 0;
  this[0x3450] = (CMerchantMenu)0x0;
  *(undefined4 *)(this + 0x3454) = 0;
  *(undefined4 *)(this + 0x3458) = 0;
  *(undefined8 *)(this + 0x3460) = 0;
  *(undefined4 *)(this + 0x3468) = 0;
  *(undefined4 *)(this + 0x346c) = 0;
  *(undefined4 *)(this + 0x3470) = 10;
                    /* try { // try from 00b773aa to 00b773d1 has its CatchHandler @ 00b77565 */
  lVar4 = CMasterResourceManager::getSingleton();
  this_00 = *(CSoundBankDataInformation **)(lVar4 + 0x100);
  lVar4 = CMasterResourceManager::getSingleton();
  pCVar3 = *(CSoundManager **)(lVar4 + 0x98);
  this_01 = (CSoundBank *)Ogre::NedAllocImpl::allocBytes(0xd0,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00b773dd to 00b773e1 has its CatchHandler @ 00b77507 */
  CSoundBank::CSoundBank(this_01,pCVar3,false);
  *(CSoundBank **)(this + 0xa8) = this_01;
                    /* try { // try from 00b773fb to 00b773ff has its CatchHandler @ 00b7755e */
  std::wstring::wstring((wstring_conflict *)&local_48,L"STATSOPEN",local_39);
                    /* try { // try from 00b77406 to 00b7740a has its CatchHandler @ 00b77551 */
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
                    /* try { // try from 00b77436 to 00b7743a has its CatchHandler @ 00b77565 */
    CSoundBank::addSample(*(CSoundBank **)(this + 0xa8),0x16,*(longlong *)(lVar4 + 0x20));
  }
                    /* try { // try from 00b7744d to 00b77451 has its CatchHandler @ 00b77563 */
  std::wstring::wstring((wstring_conflict *)local_58,L"STATSCLOSE",&local_3a);
                    /* try { // try from 00b77458 to 00b7745c has its CatchHandler @ 00b77567 */
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
                    /* try { // try from 00b77485 to 00b77491 has its CatchHandler @ 00b77565 */
    CSoundBank::addSample(*(CSoundBank **)(this + 0xa8),0x42,*(longlong *)(lVar4 + 0x20));
  }
  createMenus(this);
  return;
}

/* address=00b77580
   symbol=CMerchantMenu::isRight */

/* CMerchantMenu::isRight() */

undefined8 CMerchantMenu::isRight(void)

{
  return 0;
}

/* address=00b77590
   symbol=CMerchantMenu::open */

/* CMerchantMenu::open() */

byte __thiscall CMerchantMenu::open(CMerchantMenu *this)

{
  byte bVar1;

  bVar1 = 1;
  if (this[0x60] == (CMerchantMenu)0x0) {
    bVar1 = (byte)this[0x61] ^ 1;
  }
  return bVar1;
}

/* address=00b775b0
   symbol=CMerchantMenu::openPartial */

/* CMerchantMenu::openPartial() */

CMerchantMenu __thiscall CMerchantMenu::openPartial(CMerchantMenu *this)

{
  return this[0x60];
}

/* address=00b775c0
   symbol=CMerchantMenu::screenEdge */

/* CMerchantMenu::screenEdge() */

undefined4 __thiscall CMerchantMenu::screenEdge(CMerchantMenu *this)

{
  return *(undefined4 *)(this + 0xa0);
}

/* address=00b775d0
   symbol=CMerchantMenu::getOwner */

/* CMerchantMenu::getOwner() */

undefined8 __thiscall CMerchantMenu::getOwner(CMerchantMenu *this)

{
  return *(undefined8 *)(this + 0x50);
}

/* export-summary functions=45 failures=0 */
