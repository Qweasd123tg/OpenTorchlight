/* Targeted Ghidra class export.
   namespace=CInventoryMenu
   Treat pseudocode as navigation evidence. */


/* address=00b45790
   symbol=CInventoryMenu::equipmentDropped */

/* non-virtual thunk to CInventoryMenu::equipmentDropped(CEquipment*) */

void __thiscall CInventoryMenu::equipmentDropped(CInventoryMenu *this,CEquipment *param_1)

{
  equipmentDropped((CEquipment *)(this + -0x10));
  return;
}

/* address=00b457a0
   symbol=CInventoryMenu::equipmentDropped */

/* CInventoryMenu::equipmentDropped(CEquipment*) */

void CInventoryMenu::equipmentDropped(CEquipment *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x00b457a7. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)param_1 + 0x48))();
  return;
}

/* address=00b457b0
   symbol=CInventoryMenu::equipmentEquipped */

/* non-virtual thunk to CInventoryMenu::equipmentEquipped(CEquipment*) */

void __thiscall CInventoryMenu::equipmentEquipped(CInventoryMenu *this,CEquipment *param_1)

{
  equipmentEquipped((CEquipment *)(this + -0x10));
  return;
}

/* address=00b457c0
   symbol=CInventoryMenu::equipmentEquipped */

/* CInventoryMenu::equipmentEquipped(CEquipment*) */

void CInventoryMenu::equipmentEquipped(CEquipment *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x00b457c7. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)param_1 + 0x48))();
  return;
}

/* address=00b457d0
   symbol=CInventoryMenu::equipmentUsed */

/* non-virtual thunk to CInventoryMenu::equipmentUsed(CEquipment*) */

void __thiscall CInventoryMenu::equipmentUsed(CInventoryMenu *this,CEquipment *param_1)

{
  equipmentUsed((CEquipment *)(this + -0x10));
  return;
}

/* address=00b457e0
   symbol=CInventoryMenu::equipmentUsed */

/* CInventoryMenu::equipmentUsed(CEquipment*) */

void CInventoryMenu::equipmentUsed(CEquipment *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x00b457e7. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)param_1 + 0x48))();
  return;
}

/* address=00b457f0
   symbol=CInventoryMenu::inventoryDestroyed */

/* non-virtual thunk to CInventoryMenu::inventoryDestroyed() */

void __thiscall CInventoryMenu::inventoryDestroyed(CInventoryMenu *this)

{
  inventoryDestroyed();
  return;
}

/* address=00b45800
   symbol=CInventoryMenu::inventoryDestroyed */

/* CInventoryMenu::inventoryDestroyed() */

void CInventoryMenu::inventoryDestroyed(void)

{
  return;
}

/* address=00b45810
   symbol=CInventoryMenu::handle_ItemClick */

/* CInventoryMenu::handle_ItemClick(CEGUI::EventArgs const&) */

undefined8 __thiscall CInventoryMenu::handle_ItemClick(CInventoryMenu *this,EventArgs *param_1)

{
  undefined4 uVar1;

  if (*(long *)(param_1 + 0x10) != 0) {
    uVar1 = **(undefined4 **)(*(long *)(param_1 + 0x10) + 0x1d8);
    if (*(int *)(param_1 + 0x28) == 0) {
      *(undefined4 *)(this + 0x78) = uVar1;
      return 1;
    }
    if (*(int *)(param_1 + 0x28) == 1) {
      *(undefined4 *)(this + 0x7c) = uVar1;
      return 1;
    }
  }
  return 1;
}

/* address=00b45860
   symbol=CInventoryMenu::handle_RotateLeft */

/* CInventoryMenu::handle_RotateLeft(CEGUI::EventArgs const&) */

undefined8 CInventoryMenu::handle_RotateLeft(EventArgs *param_1)

{
  param_1[0x9162] = (EventArgs)0x1;
  return 1;
}

/* address=00b45870
   symbol=CInventoryMenu::handle_EndRotateLeft */

/* CInventoryMenu::handle_EndRotateLeft(CEGUI::EventArgs const&) */

undefined8 CInventoryMenu::handle_EndRotateLeft(EventArgs *param_1)

{
  param_1[0x9162] = (EventArgs)0x0;
  return 1;
}

/* address=00b45880
   symbol=CInventoryMenu::handle_RotateRight */

/* CInventoryMenu::handle_RotateRight(CEGUI::EventArgs const&) */

undefined8 CInventoryMenu::handle_RotateRight(EventArgs *param_1)

{
  param_1[0x9163] = (EventArgs)0x1;
  return 1;
}

/* address=00b45890
   symbol=CInventoryMenu::handle_EndRotateRight */

/* CInventoryMenu::handle_EndRotateRight(CEGUI::EventArgs const&) */

undefined8 CInventoryMenu::handle_EndRotateRight(EventArgs *param_1)

{
  param_1[0x9163] = (EventArgs)0x0;
  return 1;
}

/* address=00b458a0
   symbol=CInventoryMenu::handle_MouseThrough */

/* CInventoryMenu::handle_MouseThrough(CEGUI::EventArgs const&) */

undefined8 CInventoryMenu::handle_MouseThrough(EventArgs *param_1)

{
  param_1[0x9160] = (EventArgs)0x0;
  param_1[0x9161] = (EventArgs)0x0;
  return 1;
}

/* address=00b458c0
   symbol=CInventoryMenu::setTab */

/* CInventoryMenu::setTab(int) */

void __thiscall CInventoryMenu::setTab(CInventoryMenu *this,int param_1)

{
                    /* WARNING: Could not recover jumptable at 0x00b458cd. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)this + 0x98))(this,param_1 + 0xe);
  return;
}

/* address=00b458d0
   symbol=CInventoryMenu::handle_onClick */

/* CInventoryMenu::handle_onClick(CEGUI::EventArgs const&) */

undefined8 __thiscall CInventoryMenu::handle_onClick(CInventoryMenu *this,EventArgs *param_1)

{
  undefined8 uVar1;

  if ((*(int *)(param_1 + 0x28) == 0) && (*(long *)(param_1 + 0x10) != 0)) {
                    /* WARNING: Could not recover jumptable at 0x00b458f3. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(*(long *)this + 0x98))
                      (this,**(undefined4 **)(*(long *)(param_1 + 0x10) + 0x1d8));
    return uVar1;
  }
  return 1;
}

/* address=00b45900
   symbol=CInventoryMenu::handle_SpellMouseOver */

/* CInventoryMenu::handle_SpellMouseOver(CEGUI::EventArgs const&) */

undefined8 __thiscall CInventoryMenu::handle_SpellMouseOver(CInventoryMenu *this,EventArgs *param_1)

{
  undefined8 uVar1;

  if (*(long *)(param_1 + 0x10) != 0) {
    uVar1 = **(undefined8 **)(*(long *)(param_1 + 0x10) + 0x1d8);
    this[0x9161] = (CInventoryMenu)0x1;
    *(undefined8 *)(this + 0x9168) = uVar1;
  }
  return 1;
}

/* address=00b45930
   symbol=CInventoryMenu::handle_SpellMouseOut */

/* CInventoryMenu::handle_SpellMouseOut(CEGUI::EventArgs const&) */

undefined8 CInventoryMenu::handle_SpellMouseOut(EventArgs *param_1)

{
  return 1;
}

/* address=00b45940
   symbol=CInventoryMenu::handle_SetSpell */

/* CInventoryMenu::handle_SetSpell(CEGUI::EventArgs const&) */

undefined8 __thiscall CInventoryMenu::handle_SetSpell(CInventoryMenu *this,EventArgs *param_1)

{
  long lVar1;
  long lVar2;
  CCharacter *pCVar3;
  bool bVar4;
  char cVar5;
  long lVar6;
  CSkill *this_00;
  wstring_conflict *pwVar7;
  CLevel *pCVar8;
  wstring_conflict awStack_28 [16];

  lVar1 = *(long *)(param_1 + 0x10);
  if (lVar1 == 0) {
    return 1;
  }
  lVar6 = *(long *)(this + 0x70);
  if (*(CBaseUnit **)(lVar6 + 200) != (CBaseUnit *)0x0) {
    cVar5 = CBaseUnit::ISA(*(CBaseUnit **)(lVar6 + 200),0x29);
    if (cVar5 != '\0') {
      lVar6 = *(long *)(this + 0x70);
      bVar4 = true;
      lVar2 = *(long *)(lVar6 + 0xb8);
      goto joined_r0x00b45a49;
    }
    lVar6 = *(long *)(this + 0x70);
  }
  lVar2 = *(long *)(lVar6 + 0xb8);
  bVar4 = false;
joined_r0x00b45a49:
  if (lVar2 != 0) {
    cVar5 = CBaseUnit::ISA();
    if ((cVar5 != '\0') && (!bVar4)) {
      pCVar3 = *(CCharacter **)(this + 0x50);
      if ((*(int *)(pCVar3 + 0x330) != 0x2a) && (*(int *)(pCVar3 + 0x330) != 0x29)) {
        pCVar8 = (CLevel *)0x0;
        if (*(long *)(pCVar3 + 0x68) != 0) {
          pCVar8 = *(CLevel **)(*(long *)(pCVar3 + 0x68) + 0x18);
        }
        CGameUI::performItemUse
                  (*(CGameUI **)(this + 0x70),pCVar8,
                   *(CEquipment **)(*(CGameUI **)(this + 0x70) + 0xb8),pCVar3,pCVar3,pCVar3);
        return 1;
      }
      CSoundBank::playSample(*(CSoundBank **)(this + 0x9188),0x18,(SceneNode *)0x0,0.0,0.0,false);
      return 1;
    }
    lVar6 = *(long *)(this + 0x70);
  }
  cVar5 = CKeyManager::keyHeld((CKeyManager *)(lVar6 + 0x590),0x11);
  if (cVar5 == '\0') {
    this_00 = (CSkill *)
              CSkillManager::getSkillByGuid
                        (*(CSkillManager **)(*(long *)(this + 0x50) + 0x1c8),
                         **(longlong **)(lVar1 + 0x1d8));
    if (((this_00 == (CSkill *)0x0) ||
        (CSkill::calculateEffectiveSkillLevel(this_00), *(int *)(this_00 + 0xe0) == 0)) ||
       (((byte)this_00[0x6d] & ((byte)this_00[0x6b] ^ 1)) == 0)) {
      return 1;
    }
    pwVar7 = (wstring_conflict *)CSkill::getName(this_00);
    std::wstring::wstring(awStack_28,pwVar7);
                    /* try { // try from 00b45a22 to 00b45a26 has its CatchHandler @ 00b45b39 */
    CCharacter::setActiveSkillByName(*(CCharacter **)(this + 0x50),awStack_28);
    std::wstring::~wstring(awStack_28);
  }
  else {
    CCharacter::unLearnSpell(*(CCharacter **)(this + 0x50),*(int *)(lVar1 + 0x170));
    (**(code **)(*(long *)this + 0x48))(this);
  }
  CSoundBank::playSample(*(CSoundBank **)(this + 0x9188),0x1e,(SceneNode *)0x0,0.0,0.0,false);
  return 1;
}

/* address=00b45b50
   symbol=CInventoryMenu::processInput */

/* CInventoryMenu::processInput(void*, float, bool) */

bool CInventoryMenu::processInput(void *param_1,float param_2,bool param_3)

{
  long lVar1;
  char cVar2;
  char in_DL;
  bool bVar3;

  if (in_DL == '\0') {
    *(undefined8 *)((long)param_1 + 0x1020) = 0;
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)((long)param_1 + 0x38),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)((long)param_1 + 0x30),0));
    cVar2 = CEGUI::Window::isChild(*(Window **)((long)param_1 + 0x28));
    if (cVar2 != '\0') {
      CEGUI::Window::removeChildWindow(*(Window **)((long)param_1 + 0x28));
      return true;
    }
    cVar2 = CEGUI::Window::isChild(*(Window **)((long)param_1 + 0x48));
    if (cVar2 == '\0') {
      return true;
    }
    CEGUI::Window::removeChildWindow(*(Window **)((long)param_1 + 0x48));
    return true;
  }
  bVar3 = *(char *)((long)param_1 + 0x62) != '\0';
  if (bVar3) {
    param_2 = (float)(**(code **)(*(long *)param_1 + 0x40))(param_1,0);
    *(undefined1 *)((long)param_1 + 0x62) = 0;
  }
  lVar1 = *(long *)(*(long *)((long)param_1 + 0x70) + 0xb8);
  if ((lVar1 == 0) || (cVar2 = CBaseUnit::ISA((CBaseUnit *)param_2,lVar1,0x78), cVar2 == '\0')) {
    if (*(long *)((long)param_1 + 0x1020) != 0) {
      if (*(char *)(*(long *)((long)param_1 + 0x1020) + 0x198) == '\0') goto LAB_00b45bbc;
      *(undefined8 *)((long)param_1 + 0x1020) = 0;
    }
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)((long)param_1 + 0x30),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)((long)param_1 + 0x38),0));
    cVar2 = *(char *)((long)param_1 + 0x9160);
  }
  else {
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)((long)param_1 + 0x38),0));
    CEGUI::Window::moveToFront();
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)((long)param_1 + 0x30),0));
    CEGUI::Window::moveToFront();
LAB_00b45bbc:
    cVar2 = *(char *)((long)param_1 + 0x9160);
  }
  if (cVar2 == '\0') {
    cVar2 = CEGUI::Window::isChild(*(Window **)((long)param_1 + 0x28));
    if (cVar2 == '\0') {
      cVar2 = CEGUI::Window::isChild(*(Window **)((long)param_1 + 0x48));
      if (cVar2 != '\0') {
        CEGUI::Window::removeChildWindow(*(Window **)((long)param_1 + 0x48));
      }
    }
    else {
      CEGUI::Window::removeChildWindow(*(Window **)((long)param_1 + 0x28));
    }
  }
  *(undefined4 *)((long)param_1 + 0x78) = 0xffffffff;
  *(undefined4 *)((long)param_1 + 0x7c) = 0xffffffff;
  return !bVar3;
}

/* address=00b45d30
   symbol=CInventoryMenu::handle_MouseOut */

/* CInventoryMenu::handle_MouseOut(CEGUI::EventArgs const&) */

undefined8 __thiscall CInventoryMenu::handle_MouseOut(CInventoryMenu *this,EventArgs *param_1)

{
  char cVar1;
  long lVar2;

  if (((*(long *)(param_1 + 0x10) != 0) && (*(long *)(this + 0x50) != 0)) &&
     (lVar2 = CInventory::getEquipmentInSlot
                        (*(CInventory **)(*(long *)(this + 0x50) + 0x490),
                         **(uint **)(*(long *)(param_1 + 0x10) + 0x1d8)),
     lVar2 == *(long *)(this + 0x1020))) {
    *(undefined8 *)(this + 0x1020) = 0;
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

/* address=00b45dc0
   symbol=CInventoryMenu::setOwner */

/* CInventoryMenu::setOwner(CCharacter*) */

void __thiscall CInventoryMenu::setOwner(CInventoryMenu *this,CCharacter *param_1)

{
  CCharacter *pCVar1;
  CCharacter *pCVar2;

  pCVar1 = *(CCharacter **)(this + 0x50);
  pCVar2 = param_1;
  if (pCVar1 != param_1) {
    (**(code **)(*(long *)this + 0x90))();
    pCVar2 = *(CCharacter **)(this + 0x50);
  }
  if ((pCVar2 != (CCharacter *)0x0) && (*(CInventory **)(pCVar2 + 0x490) != (CInventory *)0x0)) {
    CInventory::removeListener(*(CInventory **)(pCVar2 + 0x490),(iInventoryListener *)(this + 0x10))
    ;
  }
  *(CCharacter **)(this + 0x50) = param_1;
  if (param_1 != (CCharacter *)0x0) {
    if (*(CInventory **)(param_1 + 0x490) != (CInventory *)0x0) {
      CInventory::addListener(*(CInventory **)(param_1 + 0x490),(iInventoryListener *)(this + 0x10))
      ;
      if (*(long *)(this + 0x50) == 0) goto LAB_00b45e4c;
    }
    CEGUI::Checkbox::setSelected(SUB81(*(undefined8 *)(this + 0x9198),0));
  }
LAB_00b45e4c:
  if (pCVar1 != param_1) {
    (**(code **)(*(long *)this + 0x48))(this);
  }
  this[0x91a8] = (CInventoryMenu)0x0;
  this[0x91a9] = (CInventoryMenu)0x0;
  this[0x91aa] = (CInventoryMenu)0x0;
  return;
}

/* address=00b45e90
   symbol=CInventoryMenu::toggleWeaponSet */

/* CInventoryMenu::toggleWeaponSet() */

void __thiscall CInventoryMenu::toggleWeaponSet(CInventoryMenu *this)

{
  char cVar1;

  if (*(CCharacter **)(this + 0x50) != (CCharacter *)0x0) {
    cVar1 = CCharacter::alive(*(CCharacter **)(this + 0x50));
    if (cVar1 != '\0') {
      cVar1 = CCharacter::performingAttackLoose(*(CCharacter **)(this + 0x50));
      if (cVar1 == '\0') {
        cVar1 = CCharacter::performingSkillLoose(*(CCharacter **)(this + 0x50));
        if (cVar1 == '\0') {
          CEGUI::Checkbox::setSelected(SUB81(*(undefined8 *)(this + 0x9198),0));
          return;
        }
      }
    }
  }
  CSoundBank::playSample(*(CSoundBank **)(this + 0x9188),0x18,(SceneNode *)0x0,0.0,0.0,false);
  return;
}

/* address=00b45f00
   symbol=CInventoryMenu::checkForUpdate */

/* CInventoryMenu::checkForUpdate(CEquipment*) */

void __thiscall CInventoryMenu::checkForUpdate(CInventoryMenu *this,CEquipment *param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;

  if ((param_1 != (CEquipment *)0x0) &&
     (*(CInventory **)(*(long *)(this + 0x50) + 0x490) != (CInventory *)0x0)) {
    iVar2 = CInventory::getRequiredPane(*(CInventory **)(*(long *)(this + 0x50) + 0x490),param_1);
    iVar3 = CInventory::findEquipmentSlot(*(CInventory **)(*(long *)(this + 0x50) + 0x490),param_1);
    if (0x12 < iVar3) {
      if (iVar2 == 1) {
        cVar1 = CEGUI::Window::isVisible(SUB81(*(undefined8 *)(this + 0x9110),0));
        if (cVar1 == '\0') {
          this[0x91a9] = (CInventoryMenu)0x1;
        }
      }
      else if (iVar2 == 2) {
        cVar1 = CEGUI::Window::isVisible(SUB81(*(undefined8 *)(this + 0x9118),0));
        if (cVar1 == '\0') {
          this[0x91aa] = (CInventoryMenu)0x1;
        }
      }
      else if (iVar2 == 0) {
        cVar1 = CEGUI::Window::isVisible(SUB81(*(undefined8 *)(this + 0x9108),0));
        if (cVar1 == '\0') {
          this[0x91a8] = (CInventoryMenu)0x1;
        }
      }
    }
  }
  return;
}

/* address=00b45fe0
   symbol=CInventoryMenu::equipmentUnequipped */

/* non-virtual thunk to CInventoryMenu::equipmentUnequipped(CEquipment*) */

void __thiscall CInventoryMenu::equipmentUnequipped(CInventoryMenu *this,CEquipment *param_1)

{
  equipmentUnequipped(this + -0x10,param_1);
  return;
}

/* address=00b45ff0
   symbol=CInventoryMenu::equipmentUnequipped */

/* CInventoryMenu::equipmentUnequipped(CEquipment*) */

void __thiscall CInventoryMenu::equipmentUnequipped(CInventoryMenu *this,CEquipment *param_1)

{
  checkForUpdate(this,param_1);
                    /* WARNING: Could not recover jumptable at 0x00b46004. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)this + 0x48))(this);
  return;
}

/* address=00b46010
   symbol=CInventoryMenu::equipmentPickedUp */

/* non-virtual thunk to CInventoryMenu::equipmentPickedUp(CEquipment*) */

void __thiscall CInventoryMenu::equipmentPickedUp(CInventoryMenu *this,CEquipment *param_1)

{
  equipmentPickedUp(this + -0x10,param_1);
  return;
}

/* address=00b46020
   symbol=CInventoryMenu::equipmentPickedUp */

/* CInventoryMenu::equipmentPickedUp(CEquipment*) */

void __thiscall CInventoryMenu::equipmentPickedUp(CInventoryMenu *this,CEquipment *param_1)

{
  checkForUpdate(this,param_1);
                    /* WARNING: Could not recover jumptable at 0x00b46034. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)this + 0x48))(this);
  return;
}

/* address=00b4d330
   symbol=CInventoryMenu::_GLOBAL__I_CInventoryMenu */

/* CInventoryMenu::CInventoryMenu(CGameUI&, CSettings&, Ogre::RenderWindow*, Ogre::SceneManager*,
   Ogre::SceneManager*, CEGUI::Window*, CResourceManager*) */

void CInventoryMenu::_GLOBAL__I_CInventoryMenu(void)

{
  allocator aStack_2ab;
  allocator aStack_2aa;
  allocator aStack_2a9;
  allocator aStack_2a8;
  allocator aStack_2a7;
  allocator aStack_2a6;
  allocator aStack_2a5;
  allocator aStack_2a4;
  allocator aStack_2a3;
  allocator aStack_2a2;
  allocator aStack_2a1;
  allocator aStack_2a0;
  allocator aStack_29f;
  allocator aStack_29e;
  allocator aStack_29d;
  allocator aStack_29c;
  allocator aStack_29b;
  allocator aStack_29a;
  allocator aStack_299;
  allocator aStack_298;
  allocator aStack_297;
  allocator aStack_296;
  allocator aStack_295;
  allocator aStack_294;
  allocator aStack_293;
  allocator aStack_292;
  allocator aStack_291;
  allocator aStack_290;
  allocator aStack_28f;
  allocator aStack_28e;
  allocator aStack_28d;
  allocator aStack_28c;
  allocator aStack_28b;
  allocator aStack_28a;
  allocator aStack_289;
  allocator aStack_288;
  allocator aStack_287;
  allocator aStack_286;
  allocator aStack_285;
  allocator aStack_284;
  allocator aStack_283;
  allocator aStack_282;
  allocator aStack_281;
  allocator aStack_280;
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
  std::string::string((string *)::KLayoutFunctionNames,"GUIEXITGAME",&aStack_2ab);
  std::string::string((string *)(::KLayoutFunctionNames + 8),"GUIEXITAPPLICATION",&aStack_2aa);
  std::string::string((string *)(::KLayoutFunctionNames + 0x10),"GUINEWGAME",&aStack_2a9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x18),"GUICONTINUEGAME",&aStack_2a8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x20),"GUINEWGAMEMENU",&aStack_2a7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x28),"GUICONTINUEGAMEMENU",&aStack_2a6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x30),"GUICLOSEMENU",&aStack_2a5);
  std::string::string((string *)(::KLayoutFunctionNames + 0x38),"GUIBACK",&aStack_2a4);
  std::string::string((string *)(::KLayoutFunctionNames + 0x40),"GUIDECLINE",&aStack_2a3);
  std::string::string((string *)(::KLayoutFunctionNames + 0x48),"GUIACCEPT",&aStack_2a2);
  std::string::string((string *)(::KLayoutFunctionNames + 0x50),"GUIOK",&aStack_2a1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x58),"GUIPAUSE",&aStack_2a0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x60),"GUISCROLLUP",&aStack_29f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x68),"GUISCROLLDOWN",&aStack_29e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x70),"GUISELECT1",&aStack_29d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x78),"GUISELECT2",&aStack_29c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x80),"GUISELECT3",&aStack_29b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x88),"GUISELECT4",&aStack_29a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x90),"GUISELECT5",&aStack_299);
  std::string::string((string *)(::KLayoutFunctionNames + 0x98),"GUISELECT6",&aStack_298);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa0),"GUISELECT7",&aStack_297);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa8),"GUISELECT8",&aStack_296);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb0),"GUISELECT9",&aStack_295);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb8),"GUISELECT10",&aStack_294);
  std::string::string((string *)(::KLayoutFunctionNames + 0xc0),"GUISELECT11",&aStack_293);
  std::string::string((string *)(::KLayoutFunctionNames + 200),"GUISELECT12",&aStack_292);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd0),"GUISELECT13",&aStack_291);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd8),"GUISELECT14",&aStack_290);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe0),"GUISELECT15",&aStack_28f);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe8),"GUISELECT16",&aStack_28e);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf0),"GUISELECT17",&aStack_28d);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf8),"GUISELECT18",&aStack_28c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x100),"GUISELECT19",&aStack_28b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x108),"GUISELECT20",&aStack_28a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x110),"GUISELECT21",&aStack_289);
  std::string::string((string *)(::KLayoutFunctionNames + 0x118),"GUISELECT22",&aStack_288);
  std::string::string((string *)(::KLayoutFunctionNames + 0x120),"GUISELECT23",&aStack_287);
  std::string::string((string *)(::KLayoutFunctionNames + 0x128),"GUISELECT24",&aStack_286);
  std::string::string((string *)(::KLayoutFunctionNames + 0x130),"GUISELECT25",&aStack_285);
  std::string::string((string *)(::KLayoutFunctionNames + 0x138),"GUISELECT26",&aStack_284);
  std::string::string((string *)(::KLayoutFunctionNames + 0x140),"GUISELECT27",&aStack_283);
  std::string::string((string *)(::KLayoutFunctionNames + 0x148),"GUISELECT28",&aStack_282);
  std::string::string((string *)(::KLayoutFunctionNames + 0x150),"GUISELECT29",&aStack_281);
  std::string::string((string *)(::KLayoutFunctionNames + 0x158),"GUISELECT30",&aStack_280);
  std::string::string((string *)(::KLayoutFunctionNames + 0x160),"GUISELECT31",&aStack_27f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x168),"GUISELECT32",&aStack_27e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x170),"GUISELECT33",&aStack_27d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x178),"GUISELECT34",&aStack_27c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x180),"GUISELECT35",&aStack_27b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x188),"GUISELECT36",&aStack_27a);
  std::string::string((string *)(::KLayoutFunctionNames + 400),"GUISELECT37",&aStack_279);
  std::string::string((string *)(::KLayoutFunctionNames + 0x198),"GUISELECT38",&aStack_278);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a0),"GUISELECT39",&aStack_277);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a8),"GUISELECT40",&aStack_276);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b0),"GUISELECT41",&aStack_275);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b8),"GUISELECT42",&aStack_274);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c0),"GUISELECT43",&aStack_273);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c8),"GUISELECT44",&aStack_272);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d0),"GUISELECT45",&aStack_271);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d8),"GUISELECT46",&aStack_270);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e0),"GUISELECT47",&aStack_26f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e8),"GUISELECT48",&aStack_26e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f0),"GUISELECT49",&aStack_26d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f8),"GUISELECT50",&aStack_26c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x200),"GUISELECTA",&aStack_26b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x208),"GUISELECTB",&aStack_26a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x210),"GUISELECTC",&aStack_269);
  std::string::string((string *)(::KLayoutFunctionNames + 0x218),"GUISELECTD",&aStack_268);
  std::string::string((string *)(::KLayoutFunctionNames + 0x220),"GUIFEEDPET",&aStack_267);
  std::string::string((string *)(::KLayoutFunctionNames + 0x228),"GUIPETPASSIVE",&aStack_266);
  std::string::string((string *)(::KLayoutFunctionNames + 0x230),"GUIPETAGGRESSIVE",&aStack_265);
  std::string::string((string *)(::KLayoutFunctionNames + 0x238),"GUIPETDEFENSIVE",&aStack_264);
  std::string::string((string *)(::KLayoutFunctionNames + 0x240),"GUITOGGLEINVENTORY",&aStack_263);
  std::string::string((string *)(::KLayoutFunctionNames + 0x248),"GUITOGGLEQUESTS",&aStack_262);
  std::string::string((string *)(::KLayoutFunctionNames + 0x250),"GUITOGGLESTATS",&aStack_261);
  std::string::string((string *)(::KLayoutFunctionNames + 600),"GUITOGGLESKILLS",&aStack_260);
  std::string::string((string *)(::KLayoutFunctionNames + 0x260),"GUITOGGLEPERKS",&aStack_25f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x268),"GUITOGGLEJOURNAL",&aStack_25e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x270),"GUITOGGLEPET",&aStack_25d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x278),"GUITOGGLEAUTOMAP",&aStack_25c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x280),"GUITOGGLEOPTIONS",&aStack_25b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x288),"GUITOGGLEITEMNAMES",&aStack_25a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x290),"GUIAUTOMAPZOOMIN",&aStack_259);
  std::string::string((string *)(::KLayoutFunctionNames + 0x298),"GUIAUTOMAPZOOMOUT",&aStack_258);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a0),"GUILEVELUP",&aStack_257);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a8),"GUISTATSUP",&aStack_256);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b0),"GUISKILLUP",&aStack_255);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b8),"GUIPET1",&aStack_254);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c0),"GUIPET2",&aStack_253);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c8),"GUIPET3",&aStack_252);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d0),"GUIDELETE1",&aStack_251);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d8),"GUIDELETE2",&aStack_250);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e0),"GUIDELETE3",&aStack_24f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e8),"GUIDELETE4",&aStack_24e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f0),"GUISETTINGSMENU",&aStack_24d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f8),"GUIPETSELL",&aStack_24c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x300),"NONE",&aStack_24b);
  __cxa_atexit(::__tcf_0,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSOUNDBANK_STRINGS,L"STEP_SOUND",&aStack_24a);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 8),L"STRIKE_SOUND",&aStack_249);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x10),L"PHYSICALHIT_SOUND",&aStack_248);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x18),L"ICEHIT_SOUND",&aStack_247);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x20),L"FIREHIT_SOUND",&aStack_246);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x28),L"ELECTRICHIT_SOUND",&aStack_245);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x30),L"POISONHIT_SOUND",&aStack_244);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x38),L"SHIELDBLOCK",&aStack_243);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x40),L"BLOCK",&aStack_242);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x48),L"CRITICAL_SOUND",&aStack_241);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x50),L"ATTACK_SOUND",&aStack_240);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x58),L"IDLE_SOUND",&aStack_23f)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x60),L"DEATH_SOUND",&aStack_23e);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x68),L"ROAR_SOUND",&aStack_23d)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x70),L"FLEE_SOUND",&aStack_23c)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x78),L"MISS_SOUND",&aStack_23b)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x80),L"FALL_SOUND",&aStack_23a)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x88),L"LAND_SOUND",&aStack_239)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x90),L"TAKE_SOUND",&aStack_238)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x98),L"SPAWN_SOUND",&aStack_237);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa0),L"USE_SOUND",&aStack_236);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa8),L"EQUIP_SOUND",&aStack_235);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb0),L"OPENMENU_SOUND",&aStack_234);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb8),L"BUY_SOUND",&aStack_233);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xc0),L"ERROR_SOUND",&aStack_232);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 200),L"LEVELUP_SOUND",&aStack_231);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd0),L"EFFORT_SOUND",&aStack_230);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd8),L"SPENDPOINT_SOUND",&aStack_22f);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe0),L"PORTALENTER_SOUND",&aStack_22e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe8),L"POERTALEXIT_SOUND",&aStack_22d);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf0),L"SKILLASSIGN_SOUND",&aStack_22c);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf8),L"QUESTRECEIVED_SOUND",&aStack_22b);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x100),L"QUESTCOMPLETED_SOUND",&aStack_22a)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x108),L"LOWMANA_SOUND",&aStack_229);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x110),L"MISSILEREFLECT_SOUND",&aStack_228)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x118),L"BADEFFECT_SOUND",&aStack_227);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x120),L"GOODEFFECT_SOUND",&aStack_226);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x128),L"NPCDIALOG_SOUND",&aStack_225);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x130),L"NPCGREET",&aStack_224);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x138),L"NPCBYE",&aStack_223);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x140),L"NPCPURCHASE",&aStack_222);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x148),L"NPCSELL",&aStack_221);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x150),L"VOICEPETINVENTORYFULL_SOUND",
             &aStack_220);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x158),L"VOICEPETDEPARTED_SOUND",
             &aStack_21f);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x160),L"VOICEPETRETURNED_SOUND",
             &aStack_21e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x168),L"VOICEPETFLED_SOUND",&aStack_21d);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x170),L"VOICEPETLEVELUP_SOUND",&aStack_21c
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x178),L"VOICEINVENTORYFULL_SOUND",
             &aStack_21b);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x180),L"VOICEINSUFFICIENTGOLD_SOUND",
             &aStack_21a);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x188),L"VOICEIMPOSSIBLE_SOUND",&aStack_219
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 400),L"VOICECANTCAST_SOUND",&aStack_218);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x198),L"VOICECANTCASTHERE_SOUND",
             &aStack_217);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a0),L"VOICEHEALTHLOW_SOUND",&aStack_216)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a8),L"VOICEMANALOW_SOUND",&aStack_215);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b0),L"VOICETRAPSPRUNG_SOUND",&aStack_214
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b8),L"VOICEREFRESHED_SOUND",&aStack_213)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c0),L"VOICEPOWERFUL_SOUND",&aStack_212);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c8),L"VOICEHEALTHY_SOUND",&aStack_211);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d0),L"VOICEILL_SOUND",&aStack_210);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d8),L"VOICEPOISONED_SOUND",&aStack_20f);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e0),L"VOICELEVELUP_SOUND",&aStack_20e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e8),L"VOICEFAMEUP_SOUND",&aStack_20d);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f0),L"VOICESKILLUP_SOUND",&aStack_20c);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f8),L"VOICEFORTUNEGOOD_SOUND",
             &aStack_20b);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x200),L"VOICEFORTUNEBAD_SOUND",&aStack_20a
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x208),L"VOICESPELLLEARNED_SOUND",
             &aStack_209);
  ::KSOUNDBANK_STRINGS._528_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_1,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KALIGNMENT_STRINGS,L"NEUTRAL",&aStack_208);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 8),L"GOOD",&aStack_207);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x10),L"EVIL",&aStack_206);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x18),L"ALL",&aStack_205);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x20),L"BERSERK",&aStack_204);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x28),L"EVILBERSERK",&aStack_203);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x30),L"GOODBERSERK",&aStack_202);
  __cxa_atexit(::__tcf_2,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KAITYPE_STRINGS,L"NORMAL",&aStack_201);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 8),L"RANGEDDEFENDER",&aStack_200);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x10),L"DEFENDER",&aStack_1ff);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x18),L"RANGEDCASTER",&aStack_1fe);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x20),L"CIRCLER",&aStack_1fd);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x28),L"RESURRECTER",&aStack_1fc);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x30),L"DUMMY",&aStack_1fb);
  __cxa_atexit(::__tcf_3,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gDAMAGE_TYPES,L"Physical",&aStack_1fa);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 8),L"Magical",&aStack_1f9);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x10),L"Fire",&aStack_1f8);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x18),L"Ice",&aStack_1f7);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x20),L"Electric",&aStack_1f6);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x28),L"Poison",&aStack_1f5);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x30),L"All",&aStack_1f4);
  __cxa_atexit(::__tcf_4,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::gTARGET_TYPES,L"USER",&aStack_1f3);
  std::wstring::wstring((wstring_conflict *)&DAT_014c6268,L"ITEM",&aStack_1f2);
  __cxa_atexit(::__tcf_5,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSFXTypeName,L"STATIONARYTARGET",&aStack_1f1);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 8),L"STATIONARYOWNER",&aStack_1f0);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x10),L"STATIONARY",&aStack_1ef);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x18),L"STATIONARYPORTAL",&aStack_1ee)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x20),L"BEAM",&aStack_1ed);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x28),L"FOLLOWOWNER",&aStack_1ec);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x30),L"FOLLOWTARGET",&aStack_1eb);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x38),L"PROJECTILELOCATION",&aStack_1ea);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x40),L"PROJECTILECHARACTER",&aStack_1e9);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x48),L"PROJECTILELOCATIONERRATIC",&aStack_1e8);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x50),L"PROJECTILECHARACTERERRATIC",&aStack_1e7);
  __cxa_atexit(::__tcf_6,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KCharacterNames,L"NA",&aStack_1e6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 8),L"NA",&aStack_1e5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x10),L"NA",&aStack_1e4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x18),L"NA",&aStack_1e3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x20),L"NA",&aStack_1e2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x28),L"NA",&aStack_1e1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x30),L"NA",&aStack_1e0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x38),L"NA",&aStack_1df);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x40),L"Bksp",&aStack_1de);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x48),L"Tab",&aStack_1dd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x50),L"NA",&aStack_1dc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x58),L"NA",&aStack_1db);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x60),L"Ctr",&aStack_1da);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x68),L"Ret",&aStack_1d9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x70),L"NA",&aStack_1d8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x78),L"NA",&aStack_1d7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x80),L"Shift",&aStack_1d6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x88),L"Ctrl",&aStack_1d5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x90),L"Alt",&aStack_1d4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x98),L"Tab",&aStack_1d3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa0),L"NA",&aStack_1d2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa8),L"NA",&aStack_1d1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb0),L"NA",&aStack_1d0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb8),L"NA",&aStack_1cf);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xc0),L"NA",&aStack_1ce);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 200),L"NA",&aStack_1cd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd0),L"NA",&aStack_1cc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd8),L"NA",&aStack_1cb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe0),L"NA",&aStack_1ca);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe8),L"NA",&aStack_1c9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf0),L"NA",&aStack_1c8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf8),L"NA",&aStack_1c7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x100),L"space",&aStack_1c6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x108),L"pgup",&aStack_1c5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x110),L"pgdn",&aStack_1c4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x118),L"end",&aStack_1c3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x120),L"home",&aStack_1c2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x128),L"left arrow",&aStack_1c1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x130),L"up arrow",&aStack_1c0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x138),L"right arrow",&aStack_1bf);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x140),L"down arrow",&aStack_1be);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x148),L")",&aStack_1bd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x150),L"*",&aStack_1bc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x158),L"+",&aStack_1bb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x160),L",",&aStack_1ba);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x168),L"ins",&aStack_1b9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x170),L"del",&aStack_1b8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x178),L"/",&aStack_1b7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x180),L"0",&aStack_1b6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x188),L"1",&aStack_1b5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 400),L"2",&aStack_1b4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x198),L"3",&aStack_1b3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a0),L"4",&aStack_1b2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a8),L"5",&aStack_1b1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b0),L"6",&aStack_1b0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b8),L"7",&aStack_1af);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c0),L"8",&aStack_1ae);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c8),L"9",&aStack_1ad);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d0),L":",&aStack_1ac);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d8),L";",&aStack_1ab);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e0),L"<",&aStack_1aa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e8),L"=",&aStack_1a9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f0),L">",&aStack_1a8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f8),L"?",&aStack_1a7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x200),L"@",&aStack_1a6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x208),L"a",&aStack_1a5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x210),L"b",&aStack_1a4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x218),L"c",&aStack_1a3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x220),L"d",&aStack_1a2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x228),L"e",&aStack_1a1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x230),L"NA",&aStack_1a0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x238),L"g",&aStack_19f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x240),L"h",&aStack_19e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x248),L"i",&aStack_19d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x250),L"j",&aStack_19c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 600),L"k",&aStack_19b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x260),L"l",&aStack_19a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x268),L"m",&aStack_199);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x270),L"n",&aStack_198);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x278),L"o",&aStack_197);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x280),L"p",&aStack_196);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x288),L"NA",&aStack_195);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x290),L"r",&aStack_194);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x298),L"s",&aStack_193);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a0),L"t",&aStack_192);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a8),L"u",&aStack_191);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b0),L"v",&aStack_190);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b8),L"w",&aStack_18f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c0),L"x",&aStack_18e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c8),L"y",&aStack_18d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d0),L"z",&aStack_18c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d8),L"[",&aStack_18b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e0),L"\\",&aStack_18a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e8),L"]",&aStack_189);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f0),L"^",&aStack_188);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f8),L"_",&aStack_187);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x300),L"NUM 0",&aStack_186);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x308),L"NUM 1",&aStack_185);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x310),L"NUM 2",&aStack_184);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x318),L"NUM 3",&aStack_183);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 800),L"NUM 4",&aStack_182);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x328),L"NUM 5",&aStack_181);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x330),L"NUM 6",&aStack_180);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x338),L"NUM 7",&aStack_17f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x340),L"NUM 8",&aStack_17e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x348),L"NUM 9",&aStack_17d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x350),L"*",&aStack_17c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x358),L"+",&aStack_17b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x360),L"NA",&aStack_17a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x368),L"-",&aStack_179);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x370),L"NA",&aStack_178);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x378),L"F1",&aStack_177);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x380),L"F2",&aStack_176);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x388),L"F3",&aStack_175);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x390),L"F4",&aStack_174);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x398),L"F5",&aStack_173);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a0),L"F6",&aStack_172);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a8),L"F7",&aStack_171);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b0),L"F8",&aStack_170);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b8),L"F9",&aStack_16f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c0),L"F10",&aStack_16e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c8),L"F11",&aStack_16d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d0),L"F12",&aStack_16c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d8),L"{",&aStack_16b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3e0),L"|",&aStack_16a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 1000),L"}",&aStack_169);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f0),L"~",&aStack_168);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f8),L";",&aStack_167);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x400),L"=",&aStack_166);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x408),L".",&aStack_165);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x410),L"-",&aStack_164);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x418),L",",&aStack_163);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x420),L"/",&aStack_162);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x428),L"`",&aStack_161);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x430),L"[",&aStack_160);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x438),L"\\",&aStack_15f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x440),L"]",&aStack_15e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x448),L"\'",&aStack_15d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x450),L"NA",&aStack_15c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x458),L"NA",&aStack_15b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x460),L"NA",&aStack_15a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x468),L"NA",&aStack_159);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x470),L"NA",&aStack_158);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x478),L"NA",&aStack_157);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x480),L"NA",&aStack_156);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x488),L"NA",&aStack_155);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x490),L"NA",&aStack_154);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x498),L"NA",&aStack_153);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a0),L"NA",&aStack_152);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a8),L"NA",&aStack_151);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b0),L"NA",&aStack_150);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b8),L"NA",&aStack_14f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c0),L"NA",&aStack_14e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c8),L"NA",&aStack_14d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d0),L"NA",&aStack_14c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d8),L"NA",&aStack_14b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e0),L"NA",&aStack_14a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e8),L"NA",&aStack_149);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f0),L"NA",&aStack_148);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f8),L"NA",&aStack_147);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x500),L"NA",&aStack_146);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x508),L"NA",&aStack_145);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x510),L"NA",&aStack_144);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x518),L"NA",&aStack_143);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x520),L"NA",&aStack_142);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x528),L"NA",&aStack_141);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x530),L"NA",&aStack_140);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x538),L"NA",&aStack_13f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x540),L"NA",&aStack_13e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x548),L"NA",&aStack_13d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x550),L"NA",&aStack_13c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x558),L"NA",&aStack_13b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x560),L"NA",&aStack_13a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x568),L"NA",&aStack_139);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x570),L"NA",&aStack_138);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x578),L"NA",&aStack_137);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x580),L"NA",&aStack_136);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x588),L"NA",&aStack_135);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x590),L"NA",&aStack_134);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x598),L"NA",&aStack_133);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a0),L"NA",&aStack_132);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a8),L"NA",&aStack_131);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b0),L"NA",&aStack_130);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b8),L"NA",&aStack_12f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c0),L"NA",&aStack_12e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c8),L"NA",&aStack_12d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d0),L";",&aStack_12c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d8),L"=",&aStack_12b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e0),L",",&aStack_12a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e8),L"-",&aStack_129);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f0),L".",&aStack_128);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f8),L"/",&aStack_127);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x600),L"`",&aStack_126);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x608),L"NA",&aStack_125);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x610),L"NA",&aStack_124);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x618),L"NA",&aStack_123);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x620),L"NA",&aStack_122);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x628),L"NA",&aStack_121);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x630),L"NA",&aStack_120);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x638),L"NA",&aStack_11f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x640),L"NA",&aStack_11e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x648),L"NA",&aStack_11d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x650),L"NA",&aStack_11c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x658),L"NA",&aStack_11b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x660),L"NA",&aStack_11a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x668),L"NA",&aStack_119);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x670),L"NA",&aStack_118);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x678),L"NA",&aStack_117);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x680),L"NA",&aStack_116);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x688),L"NA",&aStack_115);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x690),L"NA",&aStack_114);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x698),L"NA",&aStack_113);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a0),L"NA",&aStack_112);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a8),L"NA",&aStack_111);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b0),L"NA",&aStack_110);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b8),L"NA",&aStack_10f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c0),L"NA",&aStack_10e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c8),L"NA",&aStack_10d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d0),L"NA",&aStack_10c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d8),L"[",&aStack_10b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e0),L"\\",&aStack_10a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e8),L"]",&aStack_109);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f0),L"\'",&aStack_108);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f8),L"NA",&aStack_107);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x700),L"NA",&aStack_106);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x708),L"NA",&aStack_105);
  __cxa_atexit(::__tcf_7,0,&__dso_handle);
  ParticleUniverse::HALFSCALE._4_4_ = DAT_0142463c * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._0_4_ = Ogre::Vector3::UNIT_SCALE * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._8_4_ = DAT_00fa4810 * DAT_01424640;
  std::string::string((string *)&ParticleUniverse::ALIAS,"1",&aStack_104);
  __cxa_atexit(std::string::~string,&ParticleUniverse::ALIAS,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::SYSTEM,"2",&aStack_103);
  __cxa_atexit(std::string::~string,&ParticleUniverse::SYSTEM,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::TECHNIQUE,"3",&aStack_102);
  __cxa_atexit(std::string::~string,&ParticleUniverse::TECHNIQUE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::RENDERER,"4",&aStack_101);
  __cxa_atexit(std::string::~string,&ParticleUniverse::RENDERER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EMITTER,"5",&aStack_100);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EMITTER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::AFFECTOR,"6",&aStack_ff);
  __cxa_atexit(std::string::~string,&ParticleUniverse::AFFECTOR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::OBSERVER,"7",&aStack_fe);
  __cxa_atexit(std::string::~string,&ParticleUniverse::OBSERVER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::HANDLER,"8",&aStack_fd);
  __cxa_atexit(std::string::~string,&ParticleUniverse::HANDLER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::BEHAVIOUR,"9",&aStack_fc);
  __cxa_atexit(std::string::~string,&ParticleUniverse::BEHAVIOUR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EXTERN,"10",&aStack_fb);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EXTERN,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DYNAMIC_ATTRIBUTE,"11",&aStack_fa);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DYNAMIC_ATTRIBUTE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DEPENDENCY,"12",&aStack_f9);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DEPENDENCY,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES,"tag_righthand",&aStack_f8);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 8),"tag_lefthand",&aStack_f7);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x10),"",&aStack_f6);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x18),"Bip01 Head",&aStack_f5);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x20),"",&aStack_f4);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x28),"Bip01 L Clavicle",&aStack_f3);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x30),"",&aStack_f2);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x38),"",&aStack_f1);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x40),"",&aStack_f0);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x48),"",&aStack_ef);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x50),"",&aStack_ee);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x58),"tag_leftarm",&aStack_ed);
  __cxa_atexit(::__tcf_8,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES_SECONDARY,"",&aStack_ec);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 8),"",&aStack_eb);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x10),"",&aStack_ea);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x18),"",&aStack_e9);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x20),"",&aStack_e8);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x28),"Bip01 R Clavicle",
                      &aStack_e7);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x30),"",&aStack_e6);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x38),"",&aStack_e5);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x40),"",&aStack_e4);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x48),"",&aStack_e3);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x50),"",&aStack_e2);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x58),"",&aStack_e1);
  __cxa_atexit(::__tcf_9,0,&__dso_handle);
  std::string::string((string *)&::KEquipmentIconName,"EquipLeftHand",&aStack_e0);
  std::string::string((string *)&DAT_014c6b28,"EquipRightHand",&aStack_df);
  std::string::string((string *)&DAT_014c6b30,"EquipGloves",&aStack_de);
  std::string::string((string *)&DAT_014c6b38,"EquipHelm",&aStack_dd);
  std::string::string((string *)&DAT_014c6b40,"EquipChest",&aStack_dc);
  std::string::string((string *)&DAT_014c6b48,"EquipShoulder",&aStack_db);
  std::string::string((string *)&DAT_014c6b50,"EquipBoots",&aStack_da);
  std::string::string((string *)&DAT_014c6b58,"EquipBelt",&aStack_d9);
  std::string::string((string *)&DAT_014c6b60,"EquipRing1",&aStack_d8);
  std::string::string((string *)&DAT_014c6b68,"EquipRing2",&aStack_d7);
  std::string::string((string *)&DAT_014c6b70,"EquipAmulet",&aStack_d6);
  std::string::string((string *)&DAT_014c6b78,"",&aStack_d5);
  __cxa_atexit(::__tcf_10,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_TYPE_NAMES,L"",&aStack_d4);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 8),L"FIND",&aStack_d3);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x10),L"KILL NUM",&aStack_d2);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x18),L"KILL BOSS",&aStack_d1);
  __cxa_atexit(::__tcf_11,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_DIALOG_TYPE_NAMES,L"ERROR",&aStack_d0);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 8),L"INTRO",&aStack_cf);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x10),L"RETURN",&aStack_ce);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x18),L"COMPLETE",&aStack_cd);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x20),L"PASSIVE",&aStack_cc);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x28),L"DETAILS",&aStack_cb);
  __cxa_atexit(::__tcf_12,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEffect_Activation_Names,L"PASSIVE",&aStack_ca);
  std::wstring::wstring((wstring_conflict *)(::gEffect_Activation_Names + 8),L"DYNAMIC",&aStack_c9);
  std::wstring::wstring
            ((wstring_conflict *)(::gEffect_Activation_Names + 0x10),L"TRANSFER",&aStack_c8);
  __cxa_atexit(::__tcf_13,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEFFECT_STAT_MODIFIER_NAMES,L"MELEE",&aStack_c7);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 8),L"RANGED",&aStack_c6);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x10),L"DEFENSE",&aStack_c5);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x18),L"MAGIC",&aStack_c4);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x20),L"LEVEL",&aStack_c3);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x28),L"OWNERLEVEL",&aStack_c2);
  __cxa_atexit(::__tcf_14,0,&__dso_handle);
  std::string::string((string *)::gEFFECT_STAT_MODIFIER_ICON_NAMES,"iconmelee",&aStack_c1);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 8),"iconranged",&aStack_c0);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x10),"icondefense",&aStack_bf
                     );
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x18),"iconmagic",&aStack_be);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x20),"iconmagic",&aStack_bd);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x28),"iconmagic",&aStack_bc);
  __cxa_atexit(::__tcf_15,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KContextTipNames,L"TIP_INVENTORY",&aStack_bb);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 8),L"TIP_UNIDENTIFIED",&aStack_ba)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x10),L"TIP_INVENTORYFULL",&aStack_b9);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x18),L"TIP_HEALTHLOW",&aStack_b8)
  ;
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x20),L"TIP_MANALOW",&aStack_b7);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x28),L"TIP_MERCHANT",&aStack_b6);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x30),L"TIP_LEVELUP",&aStack_b5);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x38),L"TIP_STATS",&aStack_b4);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x40),L"TIP_SPELL",&aStack_b3);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x48),L"TIP_WELCOME",&aStack_b2);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x50),L"TIP_SOCKETABLE",&aStack_b1);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x58),L"TIP_PETFLEE",&aStack_b0);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x60),L"TIP_GAMBLE",&aStack_af);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x68),L"TIP_ENCHANT",&aStack_ae);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x70),L"TIP_TRANSMUTE",&aStack_ad)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x78),L"TIP_PETINVENTORY",&aStack_ac);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x80),L"TIP_PETINVENTORYFULL",&aStack_ab);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x88),L"TIP_STASH",&aStack_aa);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x90),L"TIP_FISHING",&aStack_a9);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x98),L"TIP_SPELLFIND",&aStack_a8)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xa0),L"TIP_QUESTCOMPLETE",&aStack_a7);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xa8),L"TIP_SHAREDSTASH",&aStack_a6);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xb0),L"TIP_HOWTOATTACK",&aStack_a5);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xb8),L"TIP_TEMP5",&aStack_a4);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xc0),L"TIP_TEMP6",&aStack_a3);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 200),L"TIP_TEMP7",&aStack_a2);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xd0),L"TIP_TEMP8",&aStack_a1);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xd8),L"TIP_TEMP9",&aStack_a0);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xe0),L"TIP_TEMP10",&aStack_9f);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xe8),L"TIP_TEMP11",&aStack_9e);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xf0),L"TIP_TEMP12",&aStack_9d);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xf8),L"TIP_TEMP13",&aStack_9c);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x100),L"TIP_TEMP14",&aStack_9b);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x108),L"TIP_TEMP15",&aStack_9a);
  __cxa_atexit(::__tcf_16,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames,L"CHEST",&aStack_99);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 8),L"GLOVES",&aStack_98);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x10),L"BOOTS",&aStack_97);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x18),L"HELMET",&aStack_96);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x20),L"SHOULDERS",&aStack_95);
  __cxa_atexit(::__tcf_17,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames2,L"",&aStack_94);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 8),L"",&aStack_93);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x10),L"",&aStack_92);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x18),L"FACE",&aStack_91);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x20),L"",&aStack_90);
  __cxa_atexit(::__tcf_18,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_AIFLAG_TYPE_NAMES,L"AWARE",&aStack_8f);
  std::wstring::wstring((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 8),L"BERSERK",&aStack_8e);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x10),L"CANNOT INTERRUPT",&aStack_8d);
  std::wstring::wstring((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x18),L"FRIGHTEN",&aStack_8c);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x20),L"NO LINE OF SIGHT",&aStack_8b);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x28),L"NEVER CHANGE TARGET",&aStack_8a);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x30),L"CANNOT TARGET",&aStack_89);
  __cxa_atexit(::__tcf_19,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_AISTAT_TYPE_NAMES,L"NONE",&aStack_88);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 8),L"HP",&aStack_87);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x10),L"MANA",&aStack_86);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x18),L"HP PCT",&aStack_85);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x20),L"MANA PCT",&aStack_84);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x28),L"ACTIVE UNITS",&aStack_83);
  __cxa_atexit(::__tcf_20,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::g_AISTAT_LOGIC_NAMES,L"BELOW",&aStack_82);
  std::wstring::wstring((wstring_conflict *)&DAT_014c6e98,L"ABOVE",&aStack_81);
  __cxa_atexit(::__tcf_21,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_AISTAT_TARGET_NAMES,L"SELF",&aStack_80);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 8),L"FORMATION",&aStack_7f);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 0x10),L"AREA",&aStack_7e);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 0x18),L"AREAUNITTYPES",&aStack_7d);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 0x20),L"AREAFORMATION",&aStack_7c);
  __cxa_atexit(::__tcf_22,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)OGRE_UTILITIES::gPRIMITIVE_NAMES,L"SPHERE",&aStack_7b);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 8),L"BOX",&aStack_7a);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x10),L"PLANE",&aStack_79);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x18),L"CYLINDER",&aStack_78);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x20),L"CONE",&aStack_77);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x28),L"ARROW",&aStack_76);
  __cxa_atexit(::__tcf_23,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gKEYFRAME_TYPES,L"HIT",&aStack_75);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 8),L"BLENDIN",&aStack_74);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x10),L"BLENDOUT",&aStack_73);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x18),L"PLAYSOUND",&aStack_72);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x20),L"SPAWNPARTICLE",&aStack_71);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x28),L"SPAWNPARTICLE_STOP_ON_DEATH",
             &aStack_70);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x30),L"FOOTSTEP",&aStack_6f);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x38),L"SHOWWEAPONTRAIL",&aStack_6e);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x40),L"HIDEWEAPONTRAIL",&aStack_6d);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x48),L"ATTACKSOUND",&aStack_6c);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x50),L"ENABLECOLLISION",&aStack_6b);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x58),L"DISABLECOLLISION",&aStack_6a);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x60),L"REMOVEPARTICLES",&aStack_69);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x68),L"REMOVEANIMATIONPARTICLES",&aStack_68);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x70),L"CAMERASHAKE",&aStack_67);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x78),L"ATTACKEND",&aStack_66);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x80),L"UNTARGETABLE",&aStack_65);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x88),L"TARGETABLE",&aStack_64);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x90),L"DAMPVELOCITY",&aStack_63);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x98),L"UNDAMPVELOCITY",&aStack_62)
  ;
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xa0),L"SHOWWEAPONS",&aStack_61);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xa8),L"HIDEWEAPONS",&aStack_60);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xb0),L"HIDEMESH",&aStack_5f);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xb8),L"SHOWMESH",&aStack_5e);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xc0),L"FADEOUTMESH",&aStack_5d);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 200),L"FADEINMESH",&aStack_5c);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0xd0),L"CAMERASHAKE_NO_FALLOFF",&aStack_5b);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0xd8),L"PLAYSOUND_NO_FALLOFF",&aStack_5a);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xe0),L"HITTWO",&aStack_59);
  __cxa_atexit(::__tcf_24,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEDITOR_EVENT_NAMES,L"STOP",&aStack_58);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 8),L"PLAY",&aStack_57);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x10),L"RELOAD TILES",&aStack_56);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x18),L"TOGGLE LIGHTING",&aStack_55);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x20),L"SELECT COLLIDABLE",&aStack_54);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x28),L"PAUSE PARTICLES",&aStack_53);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x30),L"UNPAUSE PARTICLES",&aStack_52);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x38),L"COLLISION ALL",&aStack_51);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x40),L"COLLISION MODELS",&aStack_50);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x48),L"COLLISION PREFABS",&aStack_4f);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x50),L"COLLISION ROOMPIECES",&aStack_4e);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x58),L"COLLISION ROOMPROPS",&aStack_4d);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x60),L"RELOAD GRAPHS",&aStack_4c);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x68),L"TOGGLE PLAYER LIGHT",&aStack_4b);
  __cxa_atexit(::__tcf_25,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEDITOR_FLAG_NAMES,L"LOGIC ENABLED",&aStack_4a);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 8),L"INGAME MODE",&aStack_49);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x10),L"SHOW STATS",&aStack_48);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x18),L"EDIT POSITION",&aStack_47);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x20),L"EDIT SCALE",&aStack_46);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x28),L"EDIT ORIENTATION",&aStack_45);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x30),L"EDIT NONE",&aStack_44);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x38),L"SHOW HELPERS",&aStack_43);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x40),L"SHOW GRID",&aStack_42);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x48),L"SHOW WORKING PLANE",&aStack_41);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x50),L"SNAP TO GRID",&aStack_40);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x58),L"SUSPEND EDITOR",&aStack_3f);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x60),L"LIGHTING VISIBLE",&aStack_3e);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x68),L"RECALCULATE LIGHTING",&aStack_3d);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x70),L"SHOW EDGES",&aStack_3c);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x78),L"UPDATE PARTICLES CIRCLE",&aStack_3b
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x80),L"SHOW LOGIC OUTPUT",&aStack_3a);
  __cxa_atexit(::__tcf_26,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::gEDITOR_UPDATE_MASKS,L"OBJECT SELECTION CHANGED",&aStack_39);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 8),L"OBJECT DATA CHANGED",&aStack_38);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 0x10),L"OBJECTS CREATED",&aStack_37);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 0x18),L"REFRESH TREE VIEW",&aStack_36);
  __cxa_atexit(::__tcf_27,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::m_gFileVersionExtension,L".svt",&aStack_35);
  __cxa_atexit(std::wstring::~wstring,&::m_gFileVersionExtension,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_EVENT_TYPE_NAMES,L"EVENT_START",&aStack_34);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 8),L"EVENT_END",&aStack_33)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x10),L"EVENT_TRIGGER",&aStack_32);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x18),L"EVENT_TRIGGER_TWO",&aStack_31)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x20),L"EVENT_UNITHIT",&aStack_30);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x28),L"EVENT_UNITDIE",&aStack_2f);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x30),L"EVENT_MISSILEHIT",&aStack_2e);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x38),L"EVENT_MISSILEDIE",&aStack_2d);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x40),L"EVENT_DIEBYEFFECT",&aStack_2c)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x48),L"EVENT_CASTERDIE",&aStack_2b);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x50),L"EVENT_UNIT_CREATE",&aStack_2a)
  ;
  __cxa_atexit(::__tcf_28,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_TARGET_TYPE_NAMES,L"NONE",&aStack_29);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 8),L"POSITION",&aStack_28)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x10),L"TARGET",&aStack_27);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x18),L"SELF",&aStack_26);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x20),L"EVERYBODY",&aStack_25);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x28),L"POSITIONRANDOM",&aStack_24);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x30),L"POSITIONFLEE",&aStack_23);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x38),L"ITEM",&aStack_22);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x40),L"UNIDENTIFIEDITEM",&aStack_21)
  ;
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x48),L"PETS",&aStack_20);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x50),L"SELFANDPETS",&aStack_1f);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x58),L"TARGET_POS",&aStack_1e);
  __cxa_atexit(::__tcf_29,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_ACTIVATION_TYPE_NAMES,L"ANY",&aStack_1d);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 8),L"PROC",&aStack_1c)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 0x10),L"WEAPON",&aStack_1b);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 0x18),L"NORMAL",&aStack_1a);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 0x20),L"PASSIVE",&aStack_19);
  __cxa_atexit(::__tcf_30,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_TYPE_NAMES,L"SKILL",&aStack_18);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TYPE_NAMES + 8),L"OFFENSIVE",&aStack_17);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TYPE_NAMES + 0x10),L"DEFENSIVE",&aStack_16);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TYPE_NAMES + 0x18),L"CHARM",&aStack_15);
  ::gSKILL_TYPE_NAMES._32_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_31,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_TYPE_DISPLAY_NAMES,L"Class Skill",&aStack_14);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TYPE_DISPLAY_NAMES + 8),L"Offensive Spell",&aStack_13);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TYPE_DISPLAY_NAMES + 0x10),L"Defensive Spell",&aStack_12)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TYPE_DISPLAY_NAMES + 0x18),L"Charm Spell",&aStack_11);
  ::gSKILL_TYPE_DISPLAY_NAMES._32_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_32,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_BONE_ATTACHMENT_NAMES,L"",&aStack_10);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 8),L"CENTER",&aStack_f);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x10),L"HEAD",&aStack_e);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x18),L"RIGHTHAND",&aStack_d);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x20),L"LEFTHAND",&aStack_c);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x28),L"RIGHTSHOULDER",&aStack_b)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x30),L"LEFTSHOULDER",&aStack_a);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x38),L"POSITION",&aStack_9);
  __cxa_atexit(::__tcf_33,0,&__dso_handle);
  return;
}

/* address=00b4d340
   symbol=CInventoryMenu::~CInventoryMenu */

/* CInventoryMenu::~CInventoryMenu() */

void __thiscall CInventoryMenu::~CInventoryMenu(CInventoryMenu *this)

{
  String *this_00;

  *(undefined ***)this = &PTR__CInventoryMenu_00fefb70;
  *(undefined ***)(this + 0x10) = &PTR__CInventoryMenu_00fefc20;
                    /* try { // try from 00b4d35e to 00b4d3d5 has its CatchHandler @ 00b4d49e */
  setOwner(this,(CCharacter *)0x0);
  if (*(long *)(this + 0x9148) != 0) {
    (**(code **)(**(long **)(this + 0x9140) + 0x1c0))();
  }
  *(undefined8 *)(this + 0x9148) = 0;
  if (*(long **)(this + 0x91a0) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x91a0) + 8))();
    *(undefined8 *)(this + 0x91a0) = 0;
  }
  if (*(long **)(this + 0x9170) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x9170) + 8))();
    *(undefined8 *)(this + 0x9170) = 0;
  }
  if (*(long **)(this + 0x9188) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x9188) + 8))();
    *(undefined8 *)(this + 0x9188) = 0;
  }
                    /* try { // try from 00b4d3eb to 00b4d40a has its CatchHandler @ 00b4d507 */
  CEGUI::String::~String((String *)(this + 0x9520));
  CEGUI::String::~String((String *)(this + 38000));
  CEGUI::String::~String((String *)(this + 0x93c0));
                    /* try { // try from 00b4d415 to 00b4d434 has its CatchHandler @ 00b4d4e0 */
  CEGUI::String::~String((String *)(this + 0x9310));
  CEGUI::String::~String((String *)(this + 0x9260));
  CEGUI::String::~String((String *)(this + 0x91b0));
  this_00 = (String *)(this + 0x8dc8);
  do {
    this_00 = this_00 + -0xb0;
                    /* try { // try from 00b4d452 to 00b4d456 has its CatchHandler @ 00b4d52e */
    CEGUI::String::~String(this_00);
  } while (this_00 != (String *)(this + 0x5568));
  do {
    this_00 = this_00 + -0xb0;
                    /* try { // try from 00b4d472 to 00b4d476 has its CatchHandler @ 00b4d4c5 */
    CEGUI::String::~String(this_00);
  } while (this_00 != (String *)(this + 0x1d08));
  *(undefined ***)(this + 0x10) = &PTR__iInventoryListener_00fce450;
  *(undefined ***)this = &PTR__CSubMenu_00fe64b0;
  CRunicCore::~CRunicCore((CRunicCore *)this);
  return;
}

/* address=00b4d550
   symbol=CInventoryMenu::~CInventoryMenu */

/* non-virtual thunk to CInventoryMenu::~CInventoryMenu() */

void __thiscall CInventoryMenu::~CInventoryMenu(CInventoryMenu *this)

{
  ~CInventoryMenu(this + -0x10);
  return;
}

/* address=00b4d560
   symbol=CInventoryMenu::~CInventoryMenu */

/* non-virtual thunk to CInventoryMenu::~CInventoryMenu() */

void __thiscall CInventoryMenu::~CInventoryMenu(CInventoryMenu *this)

{
  ~CInventoryMenu(this + -0x10);
  return;
}

/* address=00b4d570
   symbol=CInventoryMenu::~CInventoryMenu */

/* CInventoryMenu::~CInventoryMenu() */

void __thiscall CInventoryMenu::~CInventoryMenu(CInventoryMenu *this)

{
  ~CInventoryMenu(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}

/* address=00b4d590
   symbol=CInventoryMenu::handle_MouseOver */

/* CInventoryMenu::handle_MouseOver(CEGUI::EventArgs const&) */

undefined8 __thiscall CInventoryMenu::handle_MouseOver(CInventoryMenu *this,EventArgs *param_1)

{
  Window *pWVar1;
  char cVar2;
  CBaseUnit *pCVar3;

  if (*(long *)(param_1 + 0x10) == 0) {
    return 1;
  }
  if (*(long *)(this + 0x50) != 0) {
    pCVar3 = (CBaseUnit *)
             CInventory::getEquipmentInSlot
                       (*(CInventory **)(*(long *)(this + 0x50) + 0x490),
                        **(uint **)(*(long *)(param_1 + 0x10) + 0x1d8));
    if (pCVar3 != (CBaseUnit *)0x0) {
      *(CBaseUnit **)(this + 0x1020) = pCVar3;
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
                    /* try { // try from 00b4d82c to 00b4d830 has its CatchHandler @ 00b4d913 */
    CEGUI::Window::setPosition(*(UVector2 **)(this + 0x1d00));
                    /* try { // try from 00b4d88d to 00b4d891 has its CatchHandler @ 00b4d90b */
    CEGUI::Window::setSize(*(UVector2 **)(this + 0x1d00));
    CEGUI::Window::moveToBack();
    this[0x9160] = (CInventoryMenu)0x1;
    return 1;
  }
  return 1;
}

/* address=00b4d920
   symbol=CInventoryMenu::handle_CloseButton */

/* CInventoryMenu::handle_CloseButton(CEGUI::EventArgs const&) */

undefined8 __thiscall CInventoryMenu::handle_CloseButton(CInventoryMenu *this,EventArgs *param_1)

{
  long lVar1;

  if (*(int *)(param_1 + 0x28) == 0) {
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
    this[0x62] = (CInventoryMenu)0x1;
  }
  return 1;
}

/* address=00b4eb70
   symbol=CInventoryMenu::setOpen */

/* WARNING: Removing unreachable block (ram,0x00b4f194) */
/* WARNING: Removing unreachable block (ram,0x00b4f162) */
/* WARNING: Removing unreachable block (ram,0x00b4f17e) */
/* CInventoryMenu::setOpen(bool) */

void __thiscall CInventoryMenu::setOpen(CInventoryMenu *this,bool param_1)

{
  int *piVar1;
  Window *pWVar2;
  code *pcVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  Camera *pCVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  long local_78 [2];
  long local_68 [2];
  string local_58 [16];
  string local_48 [16];
  long local_38;
  allocator local_2d;
  allocator local_2c;
  allocator local_2b;
  allocator local_2a;
  allocator local_29;

  if (this[0x60] == (CInventoryMenu)0x0) {
    if (!param_1) {
      this[0x60] = (CInventoryMenu)0x0;
      return;
    }
    CSoundBank::playSample(*(CSoundBank **)(this + 0x9188),0x16,(SceneNode *)0x0,0.0,0.0,false);
    iVar5 = CDynamicPropertyFile::GetInt
                      (*(CDynamicPropertyFile **)(this + 0x68),KSETTINGS_RES_WIDTH);
    fVar8 = (float)iVar5;
    iVar5 = CDynamicPropertyFile::GetInt
                      (*(CDynamicPropertyFile **)(this + 0x68),KSETTINGS_RES_HEIGHT);
    (**(code **)(**(long **)(this + 0x9170) + 0x50))(*(long **)(this + 0x9170),1);
                    /* try { // try from 00b4ed07 to 00b4ed0b has its CatchHandler @ 00b4f16d */
    std::string::string((string *)&local_38,"CLOSE",&local_29);
                    /* try { // try from 00b4ed16 to 00b4ed1a has its CatchHandler @ 00b4f17c */
    cVar4 = CGenericModel::animationPlaying(*(CGenericModel **)(this + 0x9170),(string *)&local_38);
    if ((allocator *)(local_38 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_38 + -8);
      iVar6 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar6 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_38 + -0x18));
      }
    }
    if (cVar4 == '\0') {
                    /* try { // try from 00b4ee95 to 00b4ee99 has its CatchHandler @ 00b4f18e */
      std::string::string(local_58,"OPEN",&local_2b);
                    /* try { // try from 00b4eeb6 to 00b4eeba has its CatchHandler @ 00b4f18c */
      CGenericModel::playAnimation
                (*(CGenericModel **)(this + 0x9170),local_58,false,DAT_00fa4824,DAT_00fa8760);
                    /* try { // try from 00b4eebe to 00b4eec2 has its CatchHandler @ 00b4f18e */
      std::string::~string(local_58);
    }
    else {
                    /* try { // try from 00b4ed54 to 00b4ed58 has its CatchHandler @ 00b4f155 */
      std::string::string(local_48,"OPEN",&local_2a);
                    /* try { // try from 00b4ed7d to 00b4ed81 has its CatchHandler @ 00b4f153 */
      CGenericModel::blendAnimation
                (*(CGenericModel **)(this + 0x9170),local_48,false,DAT_00fa480c,DAT_00fa4824,
                 DAT_00fa8760);
                    /* try { // try from 00b4ed85 to 00b4ed89 has its CatchHandler @ 00b4f155 */
      std::string::~string(local_48);
    }
                    /* try { // try from 00b4ed9f to 00b4eda3 has its CatchHandler @ 00b4f15a */
    std::string::string((string *)local_68,"IDLE",&local_2c);
                    /* try { // try from 00b4edc3 to 00b4edc7 has its CatchHandler @ 00b4f140 */
    CGenericModel::queueBlendAnimation
              (*(CGenericModel **)(this + 0x9170),(string *)local_68,true,DAT_00fa480c,DAT_00fa47fc)
    ;
    if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_68[0] + -8);
      iVar6 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar6 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
      }
    }
    CEGUI::Window::addChildWindow(*(Window **)(this + 0x18));
    CEGUI::Window::moveToBack();
    CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x9120),0));
    CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x9128),0));
    CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x9130),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x9108),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x9110),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x9118),0));
    if (*(long *)(this + 0x9158) == 0) {
      pCVar7 = (Camera *)
               (**(code **)(**(long **)(this + 0x9150) + 0x48))
                         (0,0,DAT_00fa47fc,*(long **)(this + 0x9150),*(undefined8 *)(this + 0x9148),
                          3);
      *(Camera **)(this + 0x9158) = pCVar7;
      fVar10 = *(float *)(this + 0x9184);
      fVar9 = (float)CGameUI::scaledY(*(CGameUI **)(this + 0x70),DAT_00fefd50);
      fVar13 = (fVar10 + fVar9) / fVar8;
      fVar9 = (float)CGameUI::scaledY(*(CGameUI **)(this + 0x70),DAT_00fefd54);
      fVar9 = fVar9 / (float)iVar5;
      fVar10 = (float)CGameUI::scaledY(*(CGameUI **)(this + 0x70),DAT_00fefd58);
      fVar10 = fVar10 / fVar8;
      fVar11 = (float)CGameUI::scaledY(*(CGameUI **)(this + 0x70),DAT_00fefd5c);
      fVar11 = fVar11 / (float)iVar5;
      if (DAT_00fa47fc < fVar13 + fVar10) {
        fVar10 = DAT_00fa47fc - fVar13;
      }
      if (DAT_00fa47fc < fVar9 + fVar11) {
        fVar11 = DAT_00fa47fc - fVar9;
      }
      fVar13 = (float)((uint)fVar13 & -(uint)(0.0 <= fVar13));
      fVar12 = 0.0;
      if (0.0 <= fVar9) {
        fVar12 = fVar9;
      }
      fVar8 = DAT_00fa47fc / fVar8;
      if (fVar10 < fVar8) {
        fVar13 = DAT_00fa47fc - fVar8;
        fVar10 = fVar8;
      }
      Ogre::Viewport::setDimensions(fVar13,fVar12,fVar10,fVar11);
      Ogre::Viewport::setBackgroundColour(*(ColourValue **)(this + 0x9158));
      Ogre::Viewport::setClearEveryFrame(SUB81(*(undefined8 *)(this + 0x9158),0),1);
      pcVar3 = *(code **)(**(long **)(this + 0x9148) + 0x278);
      iVar5 = Ogre::Viewport::getActualWidth();
      iVar6 = Ogre::Viewport::getActualHeight();
      (*pcVar3)((float)iVar5 / (float)iVar6,*(undefined8 *)(this + 0x9148));
      Ogre::Viewport::setCamera(pCVar7);
    }
    CGameUI::queueTip(*(CGameUI **)(this + 0x70),0);
  }
  else if (!param_1) {
    if ((*(long *)(this + 0x91a0) != 0) &&
       (pWVar2 = *(Window **)(*(long *)(*(long *)(this + 0x91a0) + 0x30) + 0xb0),
       pWVar2 != (Window *)0x0)) {
      CEGUI::Window::removeChildWindow(pWVar2);
    }
    CSoundBank::playSample(*(CSoundBank **)(this + 0x9188),0x42,(SceneNode *)0x0,0.0,0.0,false);
                    /* try { // try from 00b4ebf9 to 00b4ebfd has its CatchHandler @ 00b4f192 */
    std::string::string((string *)local_78,"CLOSE",&local_2d);
                    /* try { // try from 00b4ec22 to 00b4ec26 has its CatchHandler @ 00b4f16f */
    CGenericModel::blendAnimation
              (*(CGenericModel **)(this + 0x9170),(string *)local_78,false,DAT_00fa480c,DAT_00fa4824
               ,DAT_00fa8760);
    if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_78[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
      }
    }
    this[0x61] = (CInventoryMenu)0x0;
    this[0x60] = (CInventoryMenu)0x0;
    return;
  }
  this[0x60] = (CInventoryMenu)param_1;
  (**(code **)(*(long *)this + 0x48))(this);
  return;
}

/* address=00b4f1b0
   symbol=CInventoryMenu::mapEventHandlers */

/* CInventoryMenu::mapEventHandlers(CEGUI::Window*) */

void __thiscall CInventoryMenu::mapEventHandlers(CInventoryMenu *this,Window *param_1)

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
                    /* try { // try from 00b4f276 to 00b4f2f3 has its CatchHandler @ 00b4f554 */
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
                    /* try { // try from 00b4f448 to 00b4f4c6 has its CatchHandler @ 00b4f554 */
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
                    /* try { // try from 00b4f4d3 to 00b4f4d7 has its CatchHandler @ 00b4f50e */
    CEGUI::String::~String((String *)local_268);
                    /* try { // try from 00b4f4e0 to 00b4f4e4 has its CatchHandler @ 00b4f547 */
    CEGUI::String::~String((String *)&local_1b8);
  }
                    /* try { // try from 00b4f302 to 00b4f331 has its CatchHandler @ 00b4f535 */
  CEGUI::String::~String((String *)&local_108);
  if (bVar11) {
    pcVar3 = *(code **)(*(long *)(param_1 + 0x38) + 0x10);
    local_48[0] = operator_new(0x20);
    local_48[0][3] = this;
    *local_48[0] = &PTR__MemberFunctionSlot_00fefcd0;
    local_48[0][2] = 0;
    local_48[0][1] = 0x59;
                    /* try { // try from 00b4f371 to 00b4f3a6 has its CatchHandler @ 00b4f53a */
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
                    /* try { // try from 00b4f3d7 to 00b4f3db has its CatchHandler @ 00b4f535 */
    CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_48);
  }
  return;
}

/* address=00b4f570
   symbol=CInventoryMenu::onClick */

/* CInventoryMenu::onClick(ELayoutFunction) */

undefined8 __thiscall CInventoryMenu::onClick(CInventoryMenu *this,int param_2)

{
  byte bVar1;
  char *pcVar2;
  uint *puVar3;
  String *this_00;
  undefined8 local_228;
  ulong local_220;
  undefined8 local_218;
  undefined8 local_210;
  undefined8 local_208;
  uint local_200 [15];
  uint local_1c4 [17];
  uint *local_180;
  undefined8 local_178;
  ulong local_170;
  undefined8 local_168;
  undefined8 local_160;
  undefined8 local_158;
  uint local_150 [15];
  uint local_114 [17];
  uint *local_d0;
  undefined8 local_c8;
  ulong local_c0;
  undefined8 local_b8;
  undefined8 local_b0;
  undefined8 local_a8;
  uint local_a0 [15];
  uint local_64 [17];
  uint *local_20;

  if (this[0x60] == (CInventoryMenu)0x0) {
    return 1;
  }
  if (param_2 == 0xf) {
    this_00 = (String *)&local_178;
    CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x9120),0));
    CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x9128),0));
    CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x9130),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x9108),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x9110),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x9118),0));
    this[0x91a9] = (CInventoryMenu)0x0;
    local_170 = 0x20;
    local_168 = 0;
    local_158 = 0;
    local_160 = 0;
    local_d0 = (uint *)0x0;
    local_178 = 0;
    local_150[0] = 0;
    CEGUI::String::grow((ulong)this_00);
    puVar3 = local_150;
    if (0x20 < local_170) {
      puVar3 = local_d0;
    }
    pcVar2 = "UnselectedImage";
    do {
      bVar1 = *pcVar2;
      pcVar2 = pcVar2 + 1;
      *puVar3 = (uint)bVar1;
      puVar3 = puVar3 + 1;
    } while ((byte *)pcVar2 != (byte *)0xfef76b);
    local_178 = 0xf;
    puVar3 = local_114;
    if (0x20 < local_170) {
      puVar3 = local_d0 + 0xf;
    }
    *puVar3 = 0;
                    /* try { // try from 00b4f6eb to 00b4f6ef has its CatchHandler @ 00b4f999 */
    CEGUI::PropertySet::setProperty(*(String **)(this + 0x9128),this_00);
  }
  else {
    if (param_2 == 0x10) {
      CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x9120),0));
      CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x9128),0));
      CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x9130),0));
      CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x9108),0));
      CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x9110),0));
      CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x9118),0));
      this[0x91aa] = (CInventoryMenu)0x0;
      local_220 = 0x20;
      local_218 = 0;
      local_208 = 0;
      local_210 = 0;
      local_180 = (uint *)0x0;
      local_228 = 0;
      local_200[0] = 0;
      CEGUI::String::grow((ulong)&local_228);
      puVar3 = local_200;
      if (0x20 < local_220) {
        puVar3 = local_180;
      }
      pcVar2 = "UnselectedImage";
      do {
        bVar1 = *pcVar2;
        pcVar2 = pcVar2 + 1;
        *puVar3 = (uint)bVar1;
        puVar3 = puVar3 + 1;
      } while ((byte *)pcVar2 != (byte *)0xfef76b);
      local_228 = 0xf;
      puVar3 = local_1c4;
      if (0x20 < local_220) {
        puVar3 = local_180 + 0xf;
      }
      *puVar3 = 0;
                    /* try { // try from 00b4f974 to 00b4f978 has its CatchHandler @ 00b4f9ac */
      CEGUI::PropertySet::setProperty(*(String **)(this + 0x9130),(String *)&local_228);
      CEGUI::String::~String((String *)&local_228);
      (**(code **)(*(long *)this + 0x48))(this);
      return 1;
    }
    if (param_2 != 0xe) {
      return 1;
    }
    this_00 = (String *)&local_c8;
    CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x9120),0));
    CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x9128),0));
    CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x9130),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x9108),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x9110),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x9118),0));
    this[0x91a8] = (CInventoryMenu)0x0;
    local_c0 = 0x20;
    local_b8 = 0;
    local_a8 = 0;
    local_b0 = 0;
    local_20 = (uint *)0x0;
    local_c8 = 0;
    local_a0[0] = 0;
    CEGUI::String::grow((ulong)this_00);
    puVar3 = local_a0;
    if (0x20 < local_c0) {
      puVar3 = local_20;
    }
    pcVar2 = "UnselectedImage";
    do {
      bVar1 = *pcVar2;
      pcVar2 = pcVar2 + 1;
      *puVar3 = (uint)bVar1;
      puVar3 = puVar3 + 1;
    } while ((byte *)pcVar2 != (byte *)0xfef76b);
    local_c8 = 0xf;
    puVar3 = local_64;
    if (0x20 < local_c0) {
      puVar3 = local_20 + 0xf;
    }
    *puVar3 = 0;
                    /* try { // try from 00b4f84b to 00b4f84f has its CatchHandler @ 00b4f9bf */
    CEGUI::PropertySet::setProperty(*(String **)(this + 0x9120),this_00);
  }
  CEGUI::String::~String(this_00);
  (**(code **)(*(long *)this + 0x48))(this);
  return 1;
}

/* address=00b4f9d0
   symbol=CInventoryMenu::update */

/* WARNING: Removing unreachable block (ram,0x00b518ab) */
/* WARNING: Removing unreachable block (ram,0x00b5197e) */
/* WARNING: Removing unreachable block (ram,0x00b51939) */
/* WARNING: Removing unreachable block (ram,0x00b51970) */
/* WARNING: Removing unreachable block (ram,0x00b51a9d) */
/* WARNING: Removing unreachable block (ram,0x00b519c5) */
/* WARNING: Removing unreachable block (ram,0x00b51a01) */
/* WARNING: Removing unreachable block (ram,0x00b5180e) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CInventoryMenu::update(float) */

void CInventoryMenu::update(float param_1)

{
  int *piVar1;
  wchar_t *pwVar2;
  wchar_t wVar3;
  byte bVar4;
  code *pcVar5;
  CSkillManager *this;
  Window *pWVar6;
  char cVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  float *pfVar11;
  CSkill *pCVar12;
  char *pcVar13;
  undefined8 *puVar14;
  uint *puVar15;
  long *plVar16;
  long *in_RDI;
  uint uVar17;
  bool bVar18;
  float fVar19;
  float fVar20;
  float in_XMM1_Da;
  float fVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  String local_11c8 [176];
  String local_1118 [176];
  String local_1068 [176];
  String local_fb8 [176];
  String local_f08 [176];
  String local_e58 [176];
  String local_da8 [176];
  String local_cf8 [176];
  String local_c48 [176];
  String local_b98 [176];
  String local_ae8 [176];
  String local_a38 [176];
  String local_988 [176];
  String local_8d8 [176];
  String local_828 [176];
  String local_778 [176];
  String local_6c8 [176];
  undefined8 local_618;
  ulong local_610;
  undefined8 local_608;
  undefined8 local_600;
  undefined8 local_5f8;
  uint local_5f0 [15];
  uint local_5b4 [17];
  uint *local_570;
  String local_568 [176];
  String local_4b8 [176];
  undefined8 local_408;
  ulong local_400;
  undefined8 local_3f8;
  undefined8 local_3f0;
  undefined8 local_3e8;
  uint local_3e0 [15];
  uint local_3a4 [17];
  uint *local_360;
  undefined8 local_358;
  ulong local_350;
  undefined8 local_348;
  undefined8 local_340;
  undefined8 local_338;
  uint local_330 [15];
  uint local_2f4 [17];
  uint *local_2b0;
  float local_2a8;
  float fStack_2a4;
  float local_2a0;
  float fStack_29c;
  float local_298;
  float fStack_294;
  float local_290;
  float fStack_28c;
  float local_288;
  float fStack_284;
  float local_280;
  float fStack_27c;
  float local_278;
  float fStack_274;
  float local_270;
  float fStack_26c;
  float local_268;
  float fStack_264;
  float local_260;
  float fStack_25c;
  float local_258;
  float fStack_254;
  float local_250;
  float fStack_24c;
  float local_248;
  float fStack_244;
  float local_240;
  float fStack_23c;
  float local_238;
  float fStack_234;
  float local_230;
  float fStack_22c;
  float local_228;
  float local_224;
  float local_220;
  float local_21c;
  float local_218;
  float local_214;
  float local_210;
  float local_20c;
  float local_208;
  float local_204;
  float local_200;
  float local_1fc;
  float local_1f8;
  float local_1f4;
  float local_1f0;
  float local_1ec;
  undefined8 local_1e8;
  undefined8 local_1e0;
  undefined8 local_1d8;
  undefined8 local_1d0;
  undefined8 local_1c8;
  undefined8 local_1c0;
  undefined8 local_1b8;
  undefined8 local_1b0;
  float local_1a8;
  float local_1a4;
  float local_1a0;
  float local_19c;
  float local_198;
  float local_194;
  float local_190;
  float local_18c;
  float local_188;
  float local_184;
  float local_180;
  float local_17c;
  float local_178;
  float local_174;
  float local_170;
  float local_16c;
  undefined8 local_168;
  undefined8 local_160;
  undefined8 local_158;
  undefined8 local_150;
  undefined8 local_148;
  undefined8 local_140;
  undefined8 local_138;
  undefined8 local_130;
  undefined4 local_128;
  float local_124;
  undefined4 local_120;
  uint local_11c;
  undefined4 local_118;
  float local_114;
  undefined4 local_110;
  uint local_10c;
  undefined8 local_108;
  float local_100;
  undefined8 local_f8;
  float local_f0;
  string local_e8 [16];
  string local_d8 [16];
  long local_c8 [2];
  long local_b8 [2];
  uchar *local_a8 [2];
  long local_98 [2];
  long local_88 [2];
  long local_78 [2];
  wchar_t *local_68 [2];
  long local_58 [3];
  allocator local_3d;
  allocator local_3c;
  allocator local_3b;
  allocator local_3a;
  allocator local_39 [9];

  fVar19 = param_1 + *(float *)((long)in_RDI + 0x91ac);
  bVar18 = DAT_00fa47fc <= fVar19;
  *(float *)((long)in_RDI + 0x91ac) = fVar19;
  if (bVar18) {
    do {
      fVar19 = fVar19 - DAT_00fa47fc;
    } while (DAT_00fa47fc <= fVar19);
    *(float *)((long)in_RDI + 0x91ac) = fVar19;
  }
  uVar17 = 1;
  plVar16 = in_RDI;
  do {
    if ((char)plVar16[0x1235] == '\0') {
LAB_00b4fba8:
      if (2 < uVar17) break;
    }
    else {
      if ((int)plVar16 != (int)in_RDI) {
        if ((int)plVar16 - (int)in_RDI == 1) {
          cVar7 = CEGUI::Window::isVisible(SUB81(in_RDI[0x1222],0));
          if (cVar7 != '\0') {
            *(undefined1 *)((long)in_RDI + 0x91a9) = 1;
            CEGUI::String::String(local_828,"UnselectedImage");
                    /* try { // try from 00b51766 to 00b5176a has its CatchHandler @ 00b51bd3 */
            CEGUI::PropertySet::setProperty((String *)in_RDI[0x1225],local_828);
            CEGUI::String::~String(local_828);
            goto LAB_00b4fbae;
          }
          if (*(float *)((long)in_RDI + 0x91ac) <= DAT_00fa4810) {
            CEGUI::String::String(local_ae8,"UnselectedImage");
                    /* try { // try from 00b515bd to 00b515c1 has its CatchHandler @ 00b51a48 */
            CEGUI::PropertySet::getProperty(local_b98);
                    /* try { // try from 00b515d2 to 00b515d6 has its CatchHandler @ 00b51a60 */
            cVar7 = CEGUI::operator!=(local_b98,(String *)(in_RDI + 0x124c));
                    /* try { // try from 00b515e6 to 00b515ea has its CatchHandler @ 00b51a48 */
            CEGUI::String::~String(local_b98);
            CEGUI::String::~String(local_ae8);
            if (cVar7 != '\0') {
              CEGUI::String::String(local_c48,"UnselectedImage");
                    /* try { // try from 00b5162f to 00b51633 has its CatchHandler @ 00b51b7b */
              CEGUI::PropertySet::setProperty((String *)in_RDI[0x1225],local_c48);
              CEGUI::String::~String(local_c48);
            }
          }
          else {
            CEGUI::String::String(local_8d8,"UnselectedImage");
                    /* try { // try from 00b5141c to 00b51420 has its CatchHandler @ 00b51b76 */
            CEGUI::PropertySet::getProperty(local_988);
                    /* try { // try from 00b51431 to 00b51435 has its CatchHandler @ 00b51b51 */
            cVar7 = CEGUI::operator!=(local_988,(String *)(in_RDI + 0x128e));
                    /* try { // try from 00b51445 to 00b51449 has its CatchHandler @ 00b51b76 */
            CEGUI::String::~String(local_988);
            CEGUI::String::~String(local_8d8);
            if (cVar7 != '\0') {
              CEGUI::String::String(local_a38,"UnselectedImage");
                    /* try { // try from 00b5148e to 00b51492 has its CatchHandler @ 00b51a72 */
              CEGUI::PropertySet::setProperty((String *)in_RDI[0x1225],local_a38);
              CEGUI::String::~String(local_a38);
            }
          }
        }
        else {
          cVar7 = CEGUI::Window::isVisible(SUB81(in_RDI[0x1223],0));
          if (cVar7 == '\0') {
            if (*(float *)((long)in_RDI + 0x91ac) <= DAT_00fa4810) {
              CEGUI::String::String(local_fb8,"UnselectedImage");
                    /* try { // try from 00b5166f to 00b51673 has its CatchHandler @ 00b5183e */
              CEGUI::PropertySet::getProperty(local_1068);
                    /* try { // try from 00b51681 to 00b51685 has its CatchHandler @ 00b51819 */
              cVar7 = CEGUI::operator!=(local_1068,(String *)(in_RDI + 0x1262));
                    /* try { // try from 00b51695 to 00b51699 has its CatchHandler @ 00b5183e */
              CEGUI::String::~String(local_1068);
              CEGUI::String::~String(local_fb8);
              if (cVar7 != '\0') {
                CEGUI::String::String(local_1118,"UnselectedImage");
                    /* try { // try from 00b516db to 00b516df has its CatchHandler @ 00b51843 */
                CEGUI::PropertySet::setProperty((String *)in_RDI[0x1226],local_1118);
                CEGUI::String::~String(local_1118);
              }
            }
            else {
              CEGUI::String::String(local_da8,"UnselectedImage");
                    /* try { // try from 00b4fb22 to 00b4fb26 has its CatchHandler @ 00b51b05 */
              CEGUI::PropertySet::getProperty(local_e58);
                    /* try { // try from 00b4fb37 to 00b4fb3b has its CatchHandler @ 00b51ae0 */
              cVar7 = CEGUI::operator!=(local_e58,(String *)(in_RDI + 0x12a4));
                    /* try { // try from 00b4fb4b to 00b4fb4f has its CatchHandler @ 00b51b05 */
              CEGUI::String::~String(local_e58);
              CEGUI::String::~String(local_da8);
              if (cVar7 != '\0') {
                CEGUI::String::String(local_f08,"UnselectedImage");
                    /* try { // try from 00b4fb90 to 00b4fb94 has its CatchHandler @ 00b51ac8 */
                CEGUI::PropertySet::setProperty((String *)in_RDI[0x1226],local_f08);
                CEGUI::String::~String(local_f08);
              }
            }
          }
          else {
            *(undefined1 *)((long)in_RDI + 0x91aa) = 1;
            CEGUI::String::String(local_cf8,"UnselectedImage");
                    /* try { // try from 00b5171f to 00b51723 has its CatchHandler @ 00b5185b */
            CEGUI::PropertySet::setProperty((String *)in_RDI[0x1226],local_cf8);
            CEGUI::String::~String(local_cf8);
          }
        }
        goto LAB_00b4fba8;
      }
      cVar7 = CEGUI::Window::isVisible(SUB81(in_RDI[0x1221],0));
      if (cVar7 == '\0') {
        if (*(float *)((long)in_RDI + 0x91ac) <= DAT_00fa4810) {
          local_610 = 0x20;
          local_608 = 0;
          local_5f8 = 0;
          local_600 = 0;
          local_570 = (uint *)0x0;
          local_618 = 0;
          local_5f0[0] = 0;
          CEGUI::String::grow((ulong)&local_618);
          puVar15 = local_5f0;
          if (0x20 < local_610) {
            puVar15 = local_570;
          }
          pcVar13 = "UnselectedImage";
          do {
            bVar4 = *pcVar13;
            pcVar13 = pcVar13 + 1;
            *puVar15 = (uint)bVar4;
            puVar15 = puVar15 + 1;
          } while ((byte *)pcVar13 != (byte *)0xfef76b);
          local_618 = 0xf;
          puVar15 = local_5b4;
          if (0x20 < local_610) {
            puVar15 = local_570 + 0xf;
          }
          *puVar15 = 0;
                    /* try { // try from 00b51255 to 00b51259 has its CatchHandler @ 00b51b2a */
          CEGUI::PropertySet::getProperty(local_6c8);
                    /* try { // try from 00b51267 to 00b5126b has its CatchHandler @ 00b51b0a */
          cVar7 = CEGUI::operator!=(local_6c8,(String *)(in_RDI + 0x1236));
                    /* try { // try from 00b5127b to 00b5127f has its CatchHandler @ 00b51b2a */
          CEGUI::String::~String(local_6c8);
          CEGUI::String::~String((String *)&local_618);
          if (cVar7 != '\0') {
            CEGUI::String::String(local_778,"UnselectedImage");
                    /* try { // try from 00b512bc to 00b512c0 has its CatchHandler @ 00b51bb6 */
            CEGUI::PropertySet::setProperty((String *)in_RDI[0x1224],local_778);
            CEGUI::String::~String(local_778);
          }
        }
        else {
          local_400 = 0x20;
          local_3f8 = 0;
          local_3e8 = 0;
          local_3f0 = 0;
          local_360 = (uint *)0x0;
          local_408 = 0;
          local_3e0[0] = 0;
          CEGUI::String::grow((ulong)&local_408);
          puVar15 = local_3e0;
          if (0x20 < local_400) {
            puVar15 = local_360;
          }
          pcVar13 = "UnselectedImage";
          do {
            bVar4 = *pcVar13;
            pcVar13 = pcVar13 + 1;
            *puVar15 = (uint)bVar4;
            puVar15 = puVar15 + 1;
          } while ((byte *)pcVar13 != (byte *)0xfef76b);
          local_408 = 0xf;
          puVar15 = local_3a4;
          if (0x20 < local_400) {
            puVar15 = local_360 + 0xf;
          }
          *puVar15 = 0;
                    /* try { // try from 00b50445 to 00b50449 has its CatchHandler @ 00b51b2f */
          CEGUI::PropertySet::getProperty(local_4b8);
                    /* try { // try from 00b50457 to 00b5045b has its CatchHandler @ 00b51aa8 */
          cVar7 = CEGUI::operator!=(local_4b8,(String *)(in_RDI + 0x1278));
                    /* try { // try from 00b5046b to 00b5046f has its CatchHandler @ 00b51b2f */
          CEGUI::String::~String(local_4b8);
          CEGUI::String::~String((String *)&local_408);
          if (cVar7 != '\0') {
            CEGUI::String::String(local_568,"UnselectedImage");
                    /* try { // try from 00b504ac to 00b504b0 has its CatchHandler @ 00b51b34 */
            CEGUI::PropertySet::setProperty((String *)in_RDI[0x1224],local_568);
            CEGUI::String::~String(local_568);
          }
        }
        goto LAB_00b4fba8;
      }
      *(undefined1 *)(in_RDI + 0x1235) = 1;
      local_350 = 0x20;
      local_348 = 0;
      local_338 = 0;
      local_340 = 0;
      local_2b0 = (uint *)0x0;
      local_358 = 0;
      local_330[0] = 0;
      CEGUI::String::grow((ulong)&local_358);
      puVar15 = local_330;
      if (0x20 < local_350) {
        puVar15 = local_2b0;
      }
      pcVar13 = "UnselectedImage";
      do {
        bVar4 = *pcVar13;
        pcVar13 = pcVar13 + 1;
        *puVar15 = (uint)bVar4;
        puVar15 = puVar15 + 1;
      } while ((byte *)pcVar13 != (byte *)0xfef76b);
      local_358 = 0xf;
      puVar15 = local_2f4;
      if (0x20 < local_350) {
        puVar15 = local_2b0 + 0xf;
      }
      *puVar15 = 0;
                    /* try { // try from 00b51582 to 00b51586 has its CatchHandler @ 00b51a8a */
      CEGUI::PropertySet::setProperty((String *)in_RDI[0x1224],(String *)&local_358);
      CEGUI::String::~String((String *)&local_358);
    }
LAB_00b4fbae:
    plVar16 = (long *)((long)plVar16 + 1);
    uVar17 = uVar17 + 1;
  } while( true );
  iVar8 = CDynamicPropertyFile::GetInt((CDynamicPropertyFile *)in_RDI[0xd],KSETTINGS_RES_WIDTH);
  iVar9 = CDynamicPropertyFile::GetInt((CDynamicPropertyFile *)in_RDI[0xd],KSETTINGS_RES_HEIGHT);
  if (in_RDI[10] != 0) {
    if ((update(float)::g_GP == '\0') &&
       (iVar10 = __cxa_guard_acquire(&update(float)::g_GP), iVar10 != 0)) {
      update(float)::g_GP = &DAT_01424558;
      __cxa_guard_release(&update(float)::g_GP);
      __cxa_atexit(std::wstring::~wstring,&update(float)::g_GP,&__dso_handle);
    }
    if (*(long *)(update(float)::g_GP + -6) == 0) {
      CStringTranslate::getSinglton();
      CStringTranslate::getTranslateString((wchar_t *)local_58);
                    /* try { // try from 00b502b5 to 00b502b9 has its CatchHandler @ 00b51926 */
      std::wstring::assign((wstring_conflict *)&update(float)::g_GP);
      if ((allocator *)(local_58[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_58[0] + -8);
        iVar10 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar10 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
        }
      }
    }
    STRINGS::GetValueAsWString((STRINGS *)local_88,*(int *)(in_RDI[10] + 0x444));
                    /* try { // try from 00b4fc3a to 00b4fc3e has its CatchHandler @ 00b518b8 */
    std::wstring::wstring((wstring_conflict *)local_78,(wstring_conflict *)&update(float)::g_GP);
    wcslen(L":");
                    /* try { // try from 00b4fc54 to 00b4fc58 has its CatchHandler @ 00b518d8 */
    std::wstring::append((wchar_t *)local_78,0xfe4ec0);
                    /* try { // try from 00b4fc6a to 00b4fc6e has its CatchHandler @ 00b518cb */
    std::operator+((wstring_conflict *)local_68,(wstring_conflict *)local_78);
    if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_78[0] + -8);
      iVar10 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar10 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
      }
    }
    if ((allocator *)(local_88[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_88[0] + -8);
      iVar10 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar10 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
      }
    }
                    /* try { // try from 00b4fcba to 00b4fcbe has its CatchHandler @ 00b518f5 */
    std::wstring::wstring((wstring_conflict *)local_98,local_68[0],local_39);
                    /* try { // try from 00b4fccd to 00b4fcd1 has its CatchHandler @ 00b518da */
    STRINGS::StringConvertToUTF8((wstring_conflict *)local_a8);
                    /* try { // try from 00b4fce5 to 00b4fce9 has its CatchHandler @ 00b519b5 */
    CEGUI::String::String(local_11c8,local_a8[0]);
    if ((allocator *)(local_a8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_a8[0] + -8);
      iVar10 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar10 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
      }
    }
    if ((allocator *)(local_98[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_98[0] + -8);
      iVar10 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar10 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
      }
    }
                    /* try { // try from 00b4fd29 to 00b4fd54 has its CatchHandler @ 00b51a0c */
    cVar7 = CEGUI::operator!=((String *)(in_RDI[0x1232] + 0xc0),local_11c8);
    if (cVar7 != '\0') {
                    /* try { // try from 00b50b6a to 00b50b6e has its CatchHandler @ 00b51a0c */
      CEGUI::Window::setText((String *)in_RDI[0x1232]);
    }
                    /* try { // try from 00b512dc to 00b51326 has its CatchHandler @ 00b51a0c */
    if ((((*(CCharacter *)(in_RDI[0x1233] + 0x732) != ((CCharacter *)in_RDI[10])[0x70e]) &&
         (cVar7 = CCharacter::alive((CCharacter *)in_RDI[10]), cVar7 != '\0')) &&
        (cVar7 = CCharacter::performingAttackLoose((CCharacter *)in_RDI[10]), cVar7 == '\0')) &&
       (cVar7 = CCharacter::performingSkillLoose((CCharacter *)in_RDI[10]), cVar7 == '\0')) {
      in_XMM1_Da = 0.0;
      CSoundBank::playSample((CSoundBank *)in_RDI[0x1231],0x12,(SceneNode *)0x0,0.0,0.0,false);
      CCharacter::toggleSecondaryWeaponSet((CCharacter *)in_RDI[10]);
      (**(code **)(*in_RDI + 0x48))();
    }
                    /* try { // try from 00b4fd60 to 00b4fd64 has its CatchHandler @ 00b51b4c */
    CEGUI::String::~String(local_11c8);
    if ((allocator *)(local_68[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      pwVar2 = local_68[0] + -2;
      wVar3 = *pwVar2;
      *pwVar2 = *pwVar2 + L'\xffffffff';
      UNLOCK();
      if (wVar3 < L'\x01') {
        std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -6));
      }
    }
  }
  if (*(char *)((long)in_RDI + 0x9162) == '\0') {
    if (*(char *)((long)in_RDI + 0x9163) != '\0') {
      puVar14 = (undefined8 *)(**(code **)(**(long **)(in_RDI[10] + 0x208) + 0xe8))();
      local_1e8 = *puVar14;
      local_1e0 = puVar14[1];
      local_1d8 = puVar14[2];
      local_1d0 = puVar14[3];
      local_1c8 = puVar14[4];
      local_1c0 = puVar14[5];
      local_1b8 = puVar14[6];
      local_1b0 = puVar14[7];
      MATH::matrixRotationY((Matrix4 *)&local_228,param_1 * _DAT_00fefd64);
      local_2a8 = (float)local_1e8 * local_228 + local_1e8._4_4_ * local_218 +
                  (float)local_1e0 * local_208 + local_1e0._4_4_ * local_1f8;
      fStack_2a4 = (float)local_1e8 * local_224 + local_1e8._4_4_ * local_214 +
                   (float)local_1e0 * local_204 + local_1e0._4_4_ * local_1f4;
      local_2a0 = (float)local_1e8 * local_220 + local_1e8._4_4_ * local_210 +
                  local_200 * (float)local_1e0 + local_1f0 * local_1e0._4_4_;
      fStack_29c = (float)local_1e8 * local_21c + local_1e8._4_4_ * local_20c +
                   (float)local_1e0 * local_1fc + local_1e0._4_4_ * local_1ec;
      local_298 = local_228 * (float)local_1d8 + local_218 * local_1d8._4_4_ +
                  local_208 * (float)local_1d0 + local_1f8 * local_1d0._4_4_;
      fStack_294 = local_224 * (float)local_1d8 + local_214 * local_1d8._4_4_ +
                   local_204 * (float)local_1d0 + local_1f4 * local_1d0._4_4_;
      local_290 = local_220 * (float)local_1d8 + local_210 * local_1d8._4_4_ +
                  local_200 * (float)local_1d0 + local_1f0 * local_1d0._4_4_;
      fStack_28c = (float)local_1d8 * local_21c + local_1d8._4_4_ * local_20c +
                   (float)local_1d0 * local_1fc + local_1d0._4_4_ * local_1ec;
      local_1e8 = CONCAT44(fStack_2a4,local_2a8);
      local_1e0 = CONCAT44(fStack_29c,local_2a0);
      local_1d8 = CONCAT44(fStack_294,local_298);
      local_288 = local_228 * (float)local_1c8 + local_218 * local_1c8._4_4_ +
                  local_208 * (float)local_1c0 + local_1f8 * local_1c0._4_4_;
      fStack_284 = local_224 * (float)local_1c8 + local_214 * local_1c8._4_4_ +
                   local_204 * (float)local_1c0 + local_1f4 * local_1c0._4_4_;
      local_280 = local_220 * (float)local_1c8 + local_210 * local_1c8._4_4_ +
                  local_200 * (float)local_1c0 + local_1f0 * local_1c0._4_4_;
      fStack_27c = (float)local_1c8 * local_21c + local_1c8._4_4_ * local_20c +
                   (float)local_1c0 * local_1fc + local_1c0._4_4_ * local_1ec;
      in_XMM1_Da = local_1f0 * local_1b0._4_4_;
      local_278 = local_228 * (float)local_1b8 + local_218 * local_1b8._4_4_ +
                  local_208 * (float)local_1b0 + local_1f8 * local_1b0._4_4_;
      fStack_274 = local_224 * (float)local_1b8 + local_214 * local_1b8._4_4_ +
                   local_204 * (float)local_1b0 + local_1f4 * local_1b0._4_4_;
      local_270 = local_220 * (float)local_1b8 + local_210 * local_1b8._4_4_ +
                  local_200 * (float)local_1b0 + in_XMM1_Da;
      fStack_26c = (float)local_1b8 * local_21c + local_1b8._4_4_ * local_20c +
                   (float)local_1b0 * local_1fc + local_1b0._4_4_ * local_1ec;
      local_1d0 = CONCAT44(fStack_28c,local_290);
      local_1c8 = CONCAT44(fStack_284,local_288);
      local_1c0 = CONCAT44(fStack_27c,local_280);
      local_1b8 = CONCAT44(fStack_274,local_278);
      local_1b0 = CONCAT44(fStack_26c,local_270);
      (**(code **)(**(long **)(in_RDI[10] + 0x208) + 0x118))
                (*(long **)(in_RDI[10] + 0x208),&local_1e8,0);
    }
  }
  else {
    puVar14 = (undefined8 *)(**(code **)(**(long **)(in_RDI[10] + 0x208) + 0xe8))();
    local_168 = *puVar14;
    local_160 = puVar14[1];
    local_158 = puVar14[2];
    local_150 = puVar14[3];
    local_148 = puVar14[4];
    local_140 = puVar14[5];
    local_138 = puVar14[6];
    local_130 = puVar14[7];
    MATH::matrixRotationY((Matrix4 *)&local_1a8,param_1 * _DAT_00fefd60);
    local_268 = (float)local_168 * local_1a8 + local_168._4_4_ * local_198 +
                (float)local_160 * local_188 + local_160._4_4_ * local_178;
    fStack_264 = (float)local_168 * local_1a4 + local_168._4_4_ * local_194 +
                 (float)local_160 * local_184 + local_160._4_4_ * local_174;
    local_260 = (float)local_168 * local_1a0 + local_168._4_4_ * local_190 +
                local_180 * (float)local_160 + local_170 * local_160._4_4_;
    fStack_25c = (float)local_168 * local_19c + local_168._4_4_ * local_18c +
                 (float)local_160 * local_17c + local_160._4_4_ * local_16c;
    local_258 = local_1a8 * (float)local_158 + local_198 * local_158._4_4_ +
                local_188 * (float)local_150 + local_178 * local_150._4_4_;
    fStack_254 = local_1a4 * (float)local_158 + local_194 * local_158._4_4_ +
                 local_184 * (float)local_150 + local_174 * local_150._4_4_;
    local_250 = local_1a0 * (float)local_158 + local_190 * local_158._4_4_ +
                local_180 * (float)local_150 + local_170 * local_150._4_4_;
    fStack_24c = (float)local_158 * local_19c + local_158._4_4_ * local_18c +
                 (float)local_150 * local_17c + local_150._4_4_ * local_16c;
    local_168 = CONCAT44(fStack_264,local_268);
    local_160 = CONCAT44(fStack_25c,local_260);
    local_158 = CONCAT44(fStack_254,local_258);
    local_248 = local_1a8 * (float)local_148 + local_198 * local_148._4_4_ +
                local_188 * (float)local_140 + local_178 * local_140._4_4_;
    fStack_244 = local_1a4 * (float)local_148 + local_194 * local_148._4_4_ +
                 local_184 * (float)local_140 + local_174 * local_140._4_4_;
    local_240 = local_1a0 * (float)local_148 + local_190 * local_148._4_4_ +
                local_180 * (float)local_140 + local_170 * local_140._4_4_;
    fStack_23c = (float)local_148 * local_19c + local_148._4_4_ * local_18c +
                 (float)local_140 * local_17c + local_140._4_4_ * local_16c;
    in_XMM1_Da = local_170 * local_130._4_4_;
    local_238 = local_1a8 * (float)local_138 + local_198 * local_138._4_4_ +
                local_188 * (float)local_130 + local_178 * local_130._4_4_;
    fStack_234 = local_1a4 * (float)local_138 + local_194 * local_138._4_4_ +
                 local_184 * (float)local_130 + local_174 * local_130._4_4_;
    local_230 = local_1a0 * (float)local_138 + local_190 * local_138._4_4_ +
                local_180 * (float)local_130 + in_XMM1_Da;
    fStack_22c = (float)local_138 * local_19c + local_138._4_4_ * local_18c +
                 (float)local_130 * local_17c + local_130._4_4_ * local_16c;
    local_150 = CONCAT44(fStack_24c,local_250);
    local_148 = CONCAT44(fStack_244,local_248);
    local_140 = CONCAT44(fStack_23c,local_240);
    local_138 = CONCAT44(fStack_234,local_238);
    local_130 = CONCAT44(fStack_22c,local_230);
    (**(code **)(**(long **)(in_RDI[10] + 0x208) + 0x118))
              (*(long **)(in_RDI[10] + 0x208),&local_168,0);
  }
  if ((char)in_RDI[0xc] == '\0') {
    in_RDI[0x204] = 0;
    CEGUI::Window::setVisible(SUB81(in_RDI[6],0));
    CEGUI::Window::setVisible(SUB81(in_RDI[7],0));
    if (((char)in_RDI[0xc] == '\0') && (*(char *)((long)in_RDI + 0x61) != '\0')) {
      if (in_RDI[0x1234] == 0) {
        return;
      }
      pWVar6 = *(Window **)(*(long *)(in_RDI[0x1234] + 0x30) + 0xb0);
      goto joined_r0x00b5051b;
    }
  }
  CGenericModel::updateAnimation((CGenericModel *)in_RDI[0x122e],param_1,false);
  Ogre::Entity::_updateAnimation();
  plVar16 = *(long **)(in_RDI[0x122e] + 0x130);
  pcVar5 = *(code **)(*plVar16 + 0x1b0);
                    /* try { // try from 00b4fdf3 to 00b4fdf7 has its CatchHandler @ 00b519fc */
  std::string::string((string *)local_b8,"tag_topinventory",&local_3a);
                    /* try { // try from 00b4fdfe to 00b4fe00 has its CatchHandler @ 00b518a6 */
  plVar16 = (long *)(*pcVar5)(plVar16);
  if ((allocator *)(local_b8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_b8[0] + -8);
    iVar10 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar10 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
    }
  }
  fVar19 = (float)iVar8;
  fVar21 = (float)iVar9;
  local_f8 = CPositionableObject::getPosition((CPositionableObject *)in_RDI[0x122e],false);
  local_f0 = in_XMM1_Da;
  pfVar11 = (float *)(**(code **)(*plVar16 + 0x200))(plVar16);
  fVar22 = pfVar11[1] + local_f8._4_4_;
  fVar20 = (float)CGameUI::scaledY((CGameUI *)in_RDI[0xe],*pfVar11 + (float)local_f8);
  fVar24 = fVar19 * DAT_00fa4810;
  fVar20 = fVar20 + fVar24;
  fVar22 = (float)CGameUI::scaledY((CGameUI *)in_RDI[0xe],fVar22);
  uVar17 = (uint)(fVar21 * DAT_00fa86f4 + fVar22) ^ DAT_00fa8780;
  *(float *)((long)in_RDI + 0x9184) = fVar20;
  local_118 = 0;
  local_110 = 0;
  local_114 = fVar20;
  local_10c = uVar17;
                    /* try { // try from 00b4ff5c to 00b4ff60 has its CatchHandler @ 00b51878 */
  CEGUI::Window::setPosition((UVector2 *)in_RDI[5]);
  plVar16 = *(long **)(in_RDI[0x122e] + 0x130);
  pcVar5 = *(code **)(*plVar16 + 0x1b0);
                    /* try { // try from 00b4ff92 to 00b4ff96 has its CatchHandler @ 00b51873 */
  std::string::string((string *)local_c8,"tag_bottominventory",&local_3b);
                    /* try { // try from 00b4ff9d to 00b4ff9f has its CatchHandler @ 00b517ee */
  plVar16 = (long *)(*pcVar5)(plVar16);
  if ((allocator *)(local_c8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_c8[0] + -8);
    iVar8 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar8 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
    }
  }
  local_108 = CPositionableObject::getPosition((CPositionableObject *)in_RDI[0x122e],false);
  local_100 = fVar20;
  pfVar11 = (float *)(**(code **)(*plVar16 + 0x200))(plVar16);
  fVar20 = (float)CGameUI::scaledY((CGameUI *)in_RDI[0xe],*pfVar11 + (float)local_108);
  local_128 = 0;
  fVar24 = fVar24 + fVar20;
  local_120 = 0;
  local_124 = fVar24;
  local_11c = uVar17;
                    /* try { // try from 00b5006a to 00b5006e has its CatchHandler @ 00b518b6 */
  CEGUI::Window::setPosition((UVector2 *)in_RDI[9]);
  fVar20 = (float)CGameUI::scaledY((CGameUI *)in_RDI[0xe],DAT_00fa8738);
  fVar20 = fVar20 + fVar24;
  if (fVar19 <= fVar20) {
    fVar20 = fVar19;
  }
  *(float *)(in_RDI + 0x1230) = fVar20;
  if (in_RDI[0x122b] != 0) {
    fVar20 = *(float *)((long)in_RDI + 0x9184);
    fVar22 = (float)CGameUI::scaledY((CGameUI *)in_RDI[0xe],DAT_00fefd50);
    fVar23 = (fVar20 + fVar22) / fVar19;
    fVar22 = (float)CGameUI::scaledY((CGameUI *)in_RDI[0xe],DAT_00fefd54);
    fVar22 = fVar22 / fVar21;
    fVar20 = (float)CGameUI::scaledY((CGameUI *)in_RDI[0xe],DAT_00fefd58);
    fVar20 = fVar20 / fVar19;
    fVar24 = (float)CGameUI::scaledY((CGameUI *)in_RDI[0xe],DAT_00fefd5c);
    fVar24 = fVar24 / fVar21;
    if (DAT_00fa47fc < fVar23 + fVar20) {
      fVar20 = DAT_00fa47fc - fVar23;
    }
    if (DAT_00fa47fc < fVar22 + fVar24) {
      fVar24 = DAT_00fa47fc - fVar22;
    }
    fVar23 = (float)((uint)fVar23 & -(uint)(0.0 <= fVar23));
    fVar21 = 0.0;
    if (0.0 <= fVar22) {
      fVar21 = fVar22;
    }
    fVar19 = DAT_00fa47fc / fVar19;
    if (fVar20 < fVar19) {
      fVar23 = DAT_00fa47fc - fVar19;
      fVar20 = fVar19;
    }
    Ogre::Viewport::setDimensions(fVar23,fVar21,fVar20,fVar24);
    pcVar5 = *(code **)(*(long *)in_RDI[0x1229] + 0x278);
    iVar8 = Ogre::Viewport::getActualWidth();
    iVar9 = Ogre::Viewport::getActualHeight();
    (*pcVar5)((float)iVar8 / (float)iVar9,in_RDI[0x1229]);
  }
  if (((char)in_RDI[0xc] == '\0') && (*(char *)((long)in_RDI + 0x61) == '\0')) {
                    /* try { // try from 00b5134a to 00b51363 has its CatchHandler @ 00b51b93 */
    std::string::string(local_d8,"CLOSE",&local_3c);
    cVar7 = CGenericModel::animationPlaying((CGenericModel *)in_RDI[0x122e],local_d8);
    bVar18 = false;
    if (cVar7 == '\0') {
                    /* try { // try from 00b51795 to 00b517ae has its CatchHandler @ 00b51b93 */
      std::string::string(local_e8,"CLOSE",&local_3d);
      cVar7 = CGenericModel::animationQueued((CGenericModel *)in_RDI[0x122e],local_e8);
      bVar18 = cVar7 == '\0';
                    /* try { // try from 00b517b8 to 00b517bc has its CatchHandler @ 00b51801 */
      std::string::~string(local_e8);
    }
                    /* try { // try from 00b51372 to 00b51376 has its CatchHandler @ 00b51bce */
    std::string::~string(local_d8);
    if (bVar18) {
      (**(code **)(*(long *)in_RDI[0x122e] + 0x50))((long *)in_RDI[0x122e],0);
      *(undefined1 *)((long)in_RDI + 0x61) = 1;
      (**(code **)(*(long *)in_RDI[0x122a] + 0x60))((long *)in_RDI[0x122a],3);
      CEGUI::Window::removeChildWindow((Window *)in_RDI[3]);
      in_RDI[0x122b] = 0;
    }
  }
  if ((*(char *)((long)in_RDI + 0x9161) != '\0') && (in_RDI[10] != 0)) {
    this = *(CSkillManager **)(in_RDI[10] + 0x1c8);
    if (this == (CSkillManager *)0x0) {
      return;
    }
    pCVar12 = (CSkill *)CSkillManager::getSkillByGuid(this,in_RDI[0x122d]);
    if (pCVar12 == (CSkill *)0x0) {
      return;
    }
    CSkillTooltip::showTooltip
              ((CSkillTooltip *)in_RDI[0x1234],(CBaseUnit *)in_RDI[10],pCVar12,
               (float)*(long *)(in_RDI[0xe] + 0x12d0),(float)*(long *)(in_RDI[0xe] + 0x12d8));
    return;
  }
  pWVar6 = *(Window **)(*(long *)(in_RDI[0x1234] + 0x30) + 0xb0);
joined_r0x00b5051b:
  if (pWVar6 != (Window *)0x0) {
    CEGUI::Window::removeChildWindow(pWVar6);
  }
  return;
}

/* address=00b51bf0
   symbol=CInventoryMenu::setSlotIcon */

/* WARNING: Removing unreachable block (ram,0x00b532e1) */
/* WARNING: Removing unreachable block (ram,0x00b5334c) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CInventoryMenu::setSlotIcon(CEquipment*, int, int) */

void __thiscall
CInventoryMenu::setSlotIcon(CInventoryMenu *this,CEquipment *param_1,int param_2,int param_3)

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
      goto LAB_00b51cdc;
    }
  }
  else {
LAB_00b51cdc:
    if (*(Window **)(pUVar17 + 0xb0) != (Window *)0x0) {
      CEGUI::Window::removeChildWindow(*(Window **)(pUVar17 + 0xb0));
    }
    CEGUI::Window::addChildWindow(*(Window **)(this + lVar16 * 8 + 0x1028));
    local_64 = 0;
    local_68 = 0;
    local_5c = 0x3f800000;
    local_60 = 0;
                    /* try { // try from 00b51d3c to 00b51d40 has its CatchHandler @ 00b533e5 */
    CEGUI::Window::setPosition(pUVar17);
    local_74 = 0;
    local_78 = 0;
    local_6c = 0;
    local_70 = 0;
                    /* try { // try from 00b51d78 to 00b51d7c has its CatchHandler @ 00b53395 */
    CEGUI::Window::setPosition(pUVar17);
    CEGUI::Window::getSize();
                    /* try { // try from 00b51da0 to 00b51da4 has its CatchHandler @ 00b5338c */
    CEGUI::Window::setSize(pUVar17);
    CEGUI::Window::moveToFront();
    *(CInventoryMenu **)(pUVar17 + 0x1d8) = this + (long)param_3 * 4 + 0x80;
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
                    /* try { // try from 00b5225d to 00b52261 has its CatchHandler @ 00b533a2 */
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
                    /* try { // try from 00b522ce to 00b522d2 has its CatchHandler @ 00b533b9 */
    CEGUI::PropertySet::setProperty(*(String **)(this + lVar16 * 8 + 0x1548),(String *)&local_598);
                    /* try { // try from 00b522d6 to 00b522da has its CatchHandler @ 00b533a2 */
    CEGUI::String::~String((String *)&local_598);
    CEGUI::String::~String((String *)&local_648);
    if (param_1[0x348] != (CEquipment)0x0) goto LAB_00b51fea;
LAB_00b522f1:
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
                    /* try { // try from 00b523cd to 00b523e4 has its CatchHandler @ 00b53325 */
    CEGUI::Imageset::getImage(*(String **)(this + 0x1cf8));
    CEGUI::PropertyHelper::imageToString(local_7a8);
    local_850 = 0x20;
    local_848 = 0;
    local_838 = 0;
    local_840 = 0;
    local_7b0 = (uint *)0x0;
    local_858 = 0;
    local_830[0] = 0;
                    /* try { // try from 00b52448 to 00b5244c has its CatchHandler @ 00b5334a */
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
                    /* try { // try from 00b524c5 to 00b524c9 has its CatchHandler @ 00b53397 */
    CEGUI::PropertySet::setProperty(*(String **)(this + lVar16 * 8 + 0x1a68),(String *)&local_858);
                    /* try { // try from 00b524cd to 00b524d1 has its CatchHandler @ 00b5334a */
    CEGUI::String::~String((String *)&local_858);
                    /* try { // try from 00b524d5 to 00b524d9 has its CatchHandler @ 00b53325 */
    CEGUI::String::~String((String *)local_7a8);
  }
  else {
    if (*(uint *)(param_1 + 0x3e0) < 2) {
      CEGUI::String::String(local_388,"onesocketglow");
                    /* try { // try from 00b531e4 to 00b531fb has its CatchHandler @ 00b53272 */
      CEGUI::Imageset::getImage(*(String **)(this + 0x1cf8));
      CEGUI::PropertyHelper::imageToString(local_438);
                    /* try { // try from 00b5320c to 00b53210 has its CatchHandler @ 00b5326b */
      CEGUI::String::String(local_4e8,"Image");
                    /* try { // try from 00b53224 to 00b53228 has its CatchHandler @ 00b53269 */
      CEGUI::PropertySet::setProperty(*(String **)(this + lVar16 * 8 + 0x1548),local_4e8);
                    /* try { // try from 00b5322c to 00b53230 has its CatchHandler @ 00b5326b */
      CEGUI::String::~String(local_4e8);
                    /* try { // try from 00b53234 to 00b53238 has its CatchHandler @ 00b53272 */
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
                    /* try { // try from 00b51ebd to 00b51ed4 has its CatchHandler @ 00b53357 */
      CEGUI::Imageset::getImage(*(String **)(this + 0x1cf8));
      CEGUI::PropertyHelper::imageToString(local_228);
      local_2d0 = 0x20;
      local_2c8 = 0;
      local_2b8 = 0;
      local_2c0 = 0;
      local_230 = (uint *)0x0;
      local_2d8 = 0;
      local_2b0[0] = 0;
                    /* try { // try from 00b51f38 to 00b51f3c has its CatchHandler @ 00b5335c */
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
                    /* try { // try from 00b51fad to 00b51fb1 has its CatchHandler @ 00b5335e */
      CEGUI::PropertySet::setProperty(*(String **)(this + lVar16 * 8 + 0x1548),(String *)&local_2d8)
      ;
                    /* try { // try from 00b51fb5 to 00b51fb9 has its CatchHandler @ 00b5335c */
      CEGUI::String::~String((String *)&local_2d8);
                    /* try { // try from 00b51fbd to 00b51fc1 has its CatchHandler @ 00b53357 */
      CEGUI::String::~String((String *)local_228);
      CEGUI::String::~String((String *)&local_178);
    }
    CEGUI::Window::moveToFront();
    if (param_1[0x348] == (CEquipment)0x0) goto LAB_00b522f1;
LAB_00b51fea:
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
                    /* try { // try from 00b520dc to 00b520e0 has its CatchHandler @ 00b5336b */
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
                    /* try { // try from 00b52155 to 00b52159 has its CatchHandler @ 00b533c7 */
    CEGUI::PropertySet::setProperty(*(String **)(this + lVar16 * 8 + 0x1a68),(String *)&local_908);
                    /* try { // try from 00b5215d to 00b52161 has its CatchHandler @ 00b5336b */
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
        if (pUVar17 != (UVector2 *)0x0) goto LAB_00b525d2;
LAB_00b52728:
        CEquipment::createIcon(this_00,*(CGameUI **)(this + 0x70),false);
        pUVar17 = *(UVector2 **)(this_00 + 0x2c8);
        if (pUVar17 != (UVector2 *)0x0) {
          CEGUI::EventSet::setMutedState((bool)((char)pUVar17 + '8'));
          pUVar17[0x3e2] = (UVector2)0x1;
          goto LAB_00b525d2;
        }
      }
      else {
        this_00 = (CEquipment *)**(long **)(param_1 + 1000);
        pUVar17 = *(UVector2 **)(this_00 + 0x2c8);
        if (pUVar17 == (UVector2 *)0x0) goto LAB_00b52728;
LAB_00b525d2:
        if (*(Window **)(pUVar17 + 0xb0) != (Window *)0x0) {
          CEGUI::Window::removeChildWindow(*(Window **)(pUVar17 + 0xb0));
        }
        CEGUI::Window::addChildWindow(*(Window **)(this + 0x30));
        local_a4 = (float)((long)((float)(int)((float)(~uVar21 & uVar8 | uVar7 & uVar21) +
                                              fVar3 * 0.0) + fVar4) & 0xffffffff);
        local_9c = (float)(uVar20 & 0xffffffff);
        local_a8 = 0;
        local_a0 = 0;
                    /* try { // try from 00b5263c to 00b52640 has its CatchHandler @ 00b53399 */
        CEGUI::Window::setPosition(pUVar17);
        CEGUI::Window::getSize();
                    /* try { // try from 00b5265e to 00b52662 has its CatchHandler @ 00b533b5 */
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
  cVar9 = (**(code **)(*(long *)param_1 + 0x2f8))(param_1,*(undefined8 *)(this + 0x50),0);
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
                    /* try { // try from 00b52ce5 to 00b52cfc has its CatchHandler @ 00b5332a */
      CEGUI::Imageset::getImage(*(String **)(this + 0x1cf8));
      CEGUI::PropertyHelper::imageToString(local_14b8);
      local_1560 = 0x20;
      local_1558 = 0;
      local_1548 = 0;
      local_1550 = 0;
      local_14c0 = (uint *)0x0;
      local_1568 = 0;
      local_1540[0] = 0;
                    /* try { // try from 00b52d60 to 00b52d64 has its CatchHandler @ 00b53335 */
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
                    /* try { // try from 00b52dcd to 00b52dd1 has its CatchHandler @ 00b533b7 */
      CEGUI::PropertySet::setProperty
                (*(String **)(this + lVar16 * 8 + 0x12b8),(String *)&local_1568);
                    /* try { // try from 00b52dd5 to 00b52dd9 has its CatchHandler @ 00b53335 */
      CEGUI::String::~String((String *)&local_1568);
                    /* try { // try from 00b52ddd to 00b52de1 has its CatchHandler @ 00b5332a */
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
                    /* try { // try from 00b52b1d to 00b52b34 has its CatchHandler @ 00b533d5 */
      CEGUI::Imageset::getImage(*(String **)(this + 0x1cf8));
      CEGUI::PropertyHelper::imageToString(local_12a8);
      local_1350 = 0x20;
      local_1348 = 0;
      local_1338 = 0;
      local_1340 = 0;
      local_12b0 = (uint *)0x0;
      local_1358 = 0;
      local_1330[0] = 0;
                    /* try { // try from 00b52b98 to 00b52b9c has its CatchHandler @ 00b533cc */
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
                    /* try { // try from 00b52c05 to 00b52c09 has its CatchHandler @ 00b533f2 */
      CEGUI::PropertySet::setProperty
                (*(String **)(this + lVar16 * 8 + 0x12b8),(String *)&local_1358);
                    /* try { // try from 00b52c0d to 00b52c11 has its CatchHandler @ 00b533cc */
      CEGUI::String::~String((String *)&local_1358);
                    /* try { // try from 00b52c15 to 00b52c19 has its CatchHandler @ 00b533d5 */
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
                    /* try { // try from 00b5316b to 00b53182 has its CatchHandler @ 00b53415 */
          CEGUI::Imageset::getImage(*(String **)(this + 0x1cf8));
          CEGUI::PropertyHelper::imageToString(local_f38);
                    /* try { // try from 00b53193 to 00b53197 has its CatchHandler @ 00b53405 */
          CEGUI::String::String(local_fe8,"Image");
                    /* try { // try from 00b531ab to 00b531af has its CatchHandler @ 00b533f7 */
          CEGUI::PropertySet::setProperty(*(String **)(this + lVar16 * 8 + 0x12b8),local_fe8);
                    /* try { // try from 00b531b3 to 00b531b7 has its CatchHandler @ 00b53405 */
          CEGUI::String::~String(local_fe8);
                    /* try { // try from 00b531bb to 00b531bf has its CatchHandler @ 00b53415 */
          CEGUI::String::~String((String *)local_f38);
        }
        else {
          pSVar19 = local_c78;
          CEGUI::String::String(pSVar19,"blueslotglow");
                    /* try { // try from 00b52e2f to 00b52e46 has its CatchHandler @ 00b53279 */
          CEGUI::Imageset::getImage(*(String **)(this + 0x1cf8));
          CEGUI::PropertyHelper::imageToString(local_d28);
                    /* try { // try from 00b52e57 to 00b52e5b has its CatchHandler @ 00b53277 */
          CEGUI::String::String(local_dd8,"Image");
                    /* try { // try from 00b52e6f to 00b52e73 has its CatchHandler @ 00b53246 */
          CEGUI::PropertySet::setProperty(*(String **)(this + lVar16 * 8 + 0x12b8),local_dd8);
                    /* try { // try from 00b52e77 to 00b52e7b has its CatchHandler @ 00b53277 */
          CEGUI::String::~String(local_dd8);
                    /* try { // try from 00b52e7f to 00b52e83 has its CatchHandler @ 00b53279 */
          CEGUI::String::~String((String *)local_d28);
        }
        CEGUI::String::~String(pSVar19);
        goto LAB_00b5296a;
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
                    /* try { // try from 00b52fc3 to 00b52fc7 has its CatchHandler @ 00b5329d */
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
                    /* try { // try from 00b5303d to 00b53041 has its CatchHandler @ 00b53282 */
      CEGUI::PropertySet::setProperty
                (*(String **)(this + lVar16 * 8 + 0x12b8),(String *)&local_1098);
                    /* try { // try from 00b53045 to 00b53049 has its CatchHandler @ 00b5329d */
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
                    /* try { // try from 00b52865 to 00b5287c has its CatchHandler @ 00b53385 */
      CEGUI::Imageset::getImage(*(String **)(this + 0x1cf8));
      CEGUI::PropertyHelper::imageToString(local_b18);
      local_bc0 = 0x20;
      local_bb8 = 0;
      local_ba8 = 0;
      local_bb0 = 0;
      local_b20 = (uint *)0x0;
      local_bc8 = 0;
      local_ba0[0] = 0;
                    /* try { // try from 00b528e0 to 00b528e4 has its CatchHandler @ 00b5338a */
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
                    /* try { // try from 00b5294d to 00b52951 has its CatchHandler @ 00b53370 */
      CEGUI::PropertySet::setProperty(*(String **)(this + lVar16 * 8 + 0x12b8),(String *)&local_bc8)
      ;
                    /* try { // try from 00b52955 to 00b52959 has its CatchHandler @ 00b5338a */
      CEGUI::String::~String((String *)&local_bc8);
                    /* try { // try from 00b5295d to 00b52961 has its CatchHandler @ 00b53385 */
      CEGUI::String::~String((String *)local_b18);
    }
  }
  CEGUI::String::~String(pSVar19);
LAB_00b5296a:
  if (*(long *)(this + lVar16 * 8 + 0x17d8) != 0) {
    bVar18 = SUB81(*(long *)(this + lVar16 * 8 + 0x17d8),0);
    if (*(int *)(param_1 + 0x238) < 2) {
      CEGUI::Window::setVisible(bVar18);
    }
    else {
      CEGUI::Window::setVisible(bVar18);
      STRINGS::GetValueAsString((STRINGS *)local_58,*(int *)(param_1 + 0x238));
                    /* try { // try from 00b529c2 to 00b529c6 has its CatchHandler @ 00b53372 */
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
                    /* try { // try from 00b529f0 to 00b529f4 has its CatchHandler @ 00b532ce */
      CEGUI::String::String(local_1618,local_48[0]);
                    /* try { // try from 00b52a05 to 00b52a09 has its CatchHandler @ 00b532ec */
      CEGUI::Window::setText(*(String **)(this + lVar16 * 8 + 0x17d8));
                    /* try { // try from 00b52a0d to 00b52a11 has its CatchHandler @ 00b532ce */
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

/* address=00b53430
   symbol=CInventoryMenu::updateLayout */

/* WARNING: Removing unreachable block (ram,0x00b56570) */
/* WARNING: Removing unreachable block (ram,0x00b56539) */
/* WARNING: Removing unreachable block (ram,0x00b56715) */
/* WARNING: Removing unreachable block (ram,0x00b56589) */
/* WARNING: Removing unreachable block (ram,0x00b563a8) */
/* WARNING: Removing unreachable block (ram,0x00b564b1) */
/* WARNING: Removing unreachable block (ram,0x00b5661e) */
/* WARNING: Removing unreachable block (ram,0x00b5657e) */
/* WARNING: Removing unreachable block (ram,0x00b56905) */
/* WARNING: Removing unreachable block (ram,0x00b567d9) */
/* WARNING: Removing unreachable block (ram,0x00b566a4) */
/* WARNING: Removing unreachable block (ram,0x00b56629) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CInventoryMenu::updateLayout() */

void __thiscall CInventoryMenu::updateLayout(CInventoryMenu *this)

{
  int *piVar1;
  wchar_t *pwVar2;
  float fVar3;
  wchar_t wVar4;
  byte bVar5;
  CInventory *this_00;
  Window *pWVar6;
  float fVar7;
  float fVar8;
  char cVar9;
  int iVar10;
  float *pfVar11;
  byte *pbVar12;
  char *pcVar13;
  CEquipment *this_01;
  uchar *puVar14;
  length_error *this_02;
  CSkill *this_03;
  undefined8 *puVar15;
  undefined4 *puVar16;
  uint *puVar17;
  long *plVar18;
  uint uVar19;
  long lVar20;
  UVector2 *pUVar21;
  String *pSVar22;
  ulong uVar23;
  CInventoryMenu *pCVar24;
  CEquipment *pCVar25;
  uint uVar26;
  uint uVar27;
  uint uVar28;
  float fVar29;
  float fVar30;
  float fVar31;
  uint uVar32;
  int local_2300;
  UVector2 *local_22f0;
  CInventoryMenu *local_22c8;
  undefined8 local_2298;
  ulong local_2290;
  undefined8 local_2288;
  undefined8 local_2280;
  undefined8 local_2278;
  undefined4 local_2270 [32];
  undefined4 *local_21f0;
  undefined8 local_21e8;
  ulong local_21e0;
  undefined8 local_21d8;
  undefined8 local_21d0;
  undefined8 local_21c8;
  uint local_21c0 [5];
  uint local_21ac [27];
  uint *local_2140;
  String local_2138 [176];
  String local_2088 [176];
  undefined8 local_1fd8;
  ulong local_1fd0;
  undefined8 local_1fc8;
  undefined8 local_1fc0;
  undefined8 local_1fb8;
  uint local_1fb0 [5];
  uint local_1f9c [27];
  uint *local_1f30;
  Image local_1f28 [176];
  undefined8 local_1e78;
  ulong local_1e70;
  undefined8 local_1e68;
  undefined8 local_1e60;
  undefined8 local_1e58;
  undefined4 local_1e50 [32];
  undefined4 *local_1dd0;
  undefined8 local_1dc8;
  ulong local_1dc0;
  undefined8 local_1db8;
  undefined8 local_1db0;
  undefined8 local_1da8;
  undefined4 local_1da0 [32];
  undefined4 *local_1d20;
  undefined8 local_1d18;
  ulong local_1d10;
  undefined8 local_1d08;
  undefined8 local_1d00;
  undefined8 local_1cf8;
  uint local_1cf0 [5];
  uint local_1cdc [27];
  uint *local_1c70;
  undefined8 local_1c68;
  ulong local_1c60;
  undefined8 local_1c58;
  undefined8 local_1c50;
  undefined8 local_1c48;
  undefined4 local_1c40 [32];
  undefined4 *local_1bc0;
  undefined8 local_1bb8;
  ulong local_1bb0;
  undefined8 local_1ba8;
  undefined8 local_1ba0;
  undefined8 local_1b98;
  uint local_1b90 [5];
  uint local_1b7c [27];
  uint *local_1b10;
  undefined8 local_1b08;
  ulong local_1b00;
  undefined8 local_1af8;
  undefined8 local_1af0;
  undefined8 local_1ae8;
  undefined4 local_1ae0 [32];
  undefined4 *local_1a60;
  undefined8 local_1a58;
  ulong local_1a50;
  undefined8 local_1a48;
  undefined8 local_1a40;
  undefined8 local_1a38;
  uint local_1a30 [5];
  uint local_1a1c [27];
  uint *local_19b0;
  String local_19a8 [176];
  undefined8 local_18f8;
  ulong local_18f0;
  undefined8 local_18e8;
  undefined8 local_18e0;
  undefined8 local_18d8;
  uint local_18d0 [5];
  uint local_18bc [27];
  uint *local_1850;
  undefined8 local_1848;
  ulong local_1840;
  undefined8 local_1838;
  undefined8 local_1830;
  undefined8 local_1828;
  undefined4 local_1820 [32];
  undefined4 *local_17a0;
  undefined8 local_1798;
  ulong local_1790;
  undefined8 local_1788;
  undefined8 local_1780;
  undefined8 local_1778;
  uint local_1770 [5];
  uint local_175c [27];
  uint *local_16f0;
  undefined8 local_16e8;
  ulong local_16e0;
  undefined8 local_16d8;
  undefined8 local_16d0;
  undefined8 local_16c8;
  undefined4 local_16c0 [32];
  undefined4 *local_1640;
  undefined8 local_1638;
  ulong local_1630;
  undefined8 local_1628;
  undefined8 local_1620;
  undefined8 local_1618;
  uint local_1610 [5];
  uint local_15fc [27];
  uint *local_1590;
  undefined8 local_1588;
  ulong local_1580;
  undefined8 local_1578;
  undefined8 local_1570;
  undefined8 local_1568;
  undefined4 local_1560 [32];
  undefined4 *local_14e0;
  undefined8 local_14d8;
  ulong local_14d0;
  undefined8 local_14c8;
  undefined8 local_14c0;
  undefined8 local_14b8;
  uint local_14b0 [5];
  uint local_149c [27];
  uint *local_1430;
  undefined8 local_1428;
  ulong local_1420;
  undefined8 local_1418;
  undefined8 local_1410;
  undefined8 local_1408;
  undefined4 local_1400 [32];
  undefined4 *local_1380;
  undefined8 local_1378;
  ulong local_1370;
  undefined8 local_1368;
  undefined8 local_1360;
  undefined8 local_1358;
  undefined4 local_1350 [32];
  undefined4 *local_12d0;
  undefined8 local_12c8;
  ulong local_12c0;
  undefined8 local_12b8;
  undefined8 local_12b0;
  undefined8 local_12a8;
  uint local_12a0 [5];
  uint local_128c [27];
  uint *local_1220;
  undefined8 local_1218;
  ulong local_1210;
  undefined8 local_1208;
  undefined8 local_1200;
  undefined8 local_11f8;
  undefined4 local_11f0 [32];
  undefined4 *local_1170;
  undefined8 local_1168;
  ulong local_1160;
  undefined8 local_1158;
  undefined8 local_1150;
  undefined8 local_1148;
  uint local_1140 [5];
  uint local_112c [27];
  uint *local_10c0;
  undefined8 local_10b8;
  ulong local_10b0;
  undefined8 local_10a8;
  undefined8 local_10a0;
  undefined8 local_1098;
  uint local_1090 [5];
  uint local_107c [27];
  uint *local_1010;
  Image local_1008 [176];
  undefined8 local_f58;
  ulong local_f50;
  undefined8 local_f48;
  undefined8 local_f40;
  undefined8 local_f38;
  uint local_f30 [13];
  uint local_efc [19];
  uint *local_eb0;
  undefined8 local_ea8;
  ulong local_ea0;
  undefined8 local_e98;
  undefined8 local_e90;
  undefined8 local_e88;
  uint local_e80 [5];
  uint local_e6c [27];
  uint *local_e00;
  Image local_df8 [176];
  undefined8 local_d48;
  ulong local_d40;
  undefined8 local_d38;
  undefined8 local_d30;
  undefined8 local_d28;
  uint local_d20 [12];
  uint local_cf0 [20];
  uint *local_ca0;
  undefined8 local_c98;
  ulong local_c90;
  undefined8 local_c88;
  undefined8 local_c80;
  undefined8 local_c78;
  uint local_c70 [5];
  uint local_c5c [27];
  uint *local_bf0;
  Image local_be8 [176];
  undefined8 local_b38;
  ulong local_b30;
  undefined8 local_b28;
  undefined8 local_b20;
  undefined8 local_b18;
  uint local_b10 [12];
  uint local_ae0 [20];
  uint *local_a90;
  undefined8 local_a88;
  ulong local_a80;
  undefined8 local_a78;
  undefined8 local_a70;
  undefined8 local_a68;
  undefined4 local_a60 [32];
  undefined4 *local_9e0;
  undefined8 local_9d8;
  ulong local_9d0;
  undefined8 local_9c8;
  undefined8 local_9c0;
  undefined8 local_9b8;
  uint local_9b0 [5];
  uint local_99c [27];
  uint *local_930;
  undefined8 local_928;
  ulong local_920;
  undefined8 local_918;
  undefined8 local_910;
  undefined8 local_908;
  uint local_900 [5];
  uint local_8ec [27];
  uint *local_880;
  Image local_878 [176];
  undefined8 local_7c8;
  ulong local_7c0;
  undefined8 local_7b8;
  undefined8 local_7b0;
  undefined8 local_7a8;
  uint local_7a0 [12];
  uint local_770 [20];
  uint *local_720;
  undefined8 local_718;
  ulong local_710;
  undefined8 local_708;
  undefined8 local_700;
  undefined8 local_6f8;
  undefined4 local_6f0 [32];
  undefined4 *local_670;
  undefined8 local_668;
  ulong local_660;
  undefined8 local_658;
  undefined8 local_650;
  undefined8 local_648;
  uint local_640 [5];
  uint local_62c [27];
  uint *local_5c0;
  undefined8 local_5b8;
  ulong local_5b0;
  undefined8 local_5a8;
  undefined8 local_5a0;
  undefined8 local_598;
  uint local_590 [5];
  uint local_57c [27];
  uint *local_510;
  Image local_508 [176];
  undefined8 local_458;
  ulong local_450;
  undefined8 local_448;
  undefined8 local_440;
  undefined8 local_438;
  uint local_430 [13];
  uint local_3fc [19];
  uint *local_3b0;
  undefined8 local_3a8;
  ulong local_3a0;
  undefined8 local_398;
  undefined8 local_390;
  undefined8 local_388;
  uint local_380 [5];
  uint local_36c [27];
  uint *local_300;
  Image local_2f8 [176];
  undefined8 local_248;
  ulong local_240;
  undefined8 local_238;
  undefined8 local_230;
  undefined8 local_228;
  uint local_220 [13];
  uint local_1ec [19];
  uint *local_1a0;
  undefined4 local_178;
  undefined4 local_174;
  undefined4 local_170;
  uint local_16c;
  float local_168;
  float local_164;
  float local_160;
  float local_15c;
  undefined4 local_158;
  undefined4 local_154;
  undefined4 local_150;
  undefined4 local_14c;
  float local_140;
  float local_13c;
  undefined4 local_128;
  float local_124;
  undefined4 local_120;
  float local_11c;
  float local_110;
  float local_10c;
  long local_108 [2];
  long local_f8 [2];
  uchar *local_e8 [2];
  long local_d8 [2];
  uchar *local_c8 [2];
  long local_b8 [2];
  wchar_t *local_a8 [2];
  long local_98 [2];
  uchar *local_88 [2];
  long local_78 [2];
  long local_68 [2];
  long local_58 [3];
  allocator local_3d [2];
  allocator local_3b;
  allocator local_3a;
  allocator local_39 [9];

  if (((this[0x60] != (CInventoryMenu)0x0) && (*(long *)(this + 0x50) != 0)) &&
     (this_00 = *(CInventory **)(*(long *)(this + 0x50) + 0x490), this_00 != (CInventory *)0x0)) {
    while (pWVar6 = *(Window **)(this + 0x30),
          *(long *)(pWVar6 + 0x80) - *(long *)(pWVar6 + 0x78) >> 3 != 0) {
      CEGUI::Window::removeChildWindow(pWVar6);
    }
    lVar20 = 0;
    do {
      while ((pWVar6 = *(Window **)(this + lVar20 + 0x1028), pWVar6 != (Window *)0x0 &&
             (*(long *)(pWVar6 + 0x80) - *(long *)(pWVar6 + 0x78) >> 3 != 0))) {
        lVar20 = lVar20 + 8;
        CEGUI::Window::removeChildWindow(pWVar6);
        if (lVar20 == 0x60) goto LAB_00b534f0;
      }
      lVar20 = lVar20 + 8;
    } while (lVar20 != 0x60);
LAB_00b534f0:
    uVar19 = 0;
    pCVar24 = this;
    do {
      if (*(long *)(pCVar24 + 0x1028) != 0) {
        lVar20 = CInventory::getEquipmentRefInSlot(this_00,uVar19);
        if (lVar20 == 0) {
          if (*(long *)(pCVar24 + 0x1028) == 0) goto LAB_00b54212;
          local_1580 = 0x20;
          local_1578 = 0;
          local_1568 = 0;
          local_1570 = 0;
          local_14e0 = (undefined4 *)0x0;
          local_1588 = 0;
          local_1560[0] = 0;
          CEGUI::String::grow((ulong)&local_1588);
          local_1588 = 0;
          puVar16 = local_1560;
          if (0x20 < local_1580) {
            puVar16 = local_14e0;
          }
          *puVar16 = 0;
          local_14d0 = 0x20;
          local_14c8 = 0;
          local_14b8 = 0;
          local_14c0 = 0;
          local_1430 = (uint *)0x0;
          local_14d8 = 0;
          local_14b0[0] = 0;
                    /* try { // try from 00b54ee4 to 00b54ee8 has its CatchHandler @ 00b5692a */
          CEGUI::String::grow((ulong)&local_14d8);
          puVar17 = local_14b0;
          if (0x20 < local_14d0) {
            puVar17 = local_1430;
          }
          pbVar12 = (byte *)0xfd0c0d;
          do {
            bVar5 = *pbVar12;
            pbVar12 = pbVar12 + 1;
            *puVar17 = (uint)bVar5;
            puVar17 = puVar17 + 1;
          } while (pbVar12 != (byte *)0xfd0c12);
          local_14d8 = 5;
          puVar17 = local_149c;
          if (0x20 < local_14d0) {
            puVar17 = local_1430 + 5;
          }
          *puVar17 = 0;
                    /* try { // try from 00b54f58 to 00b54f5c has its CatchHandler @ 00b5687c */
          CEGUI::PropertySet::setProperty(*(String **)(pCVar24 + 0x1a68),(String *)&local_14d8);
                    /* try { // try from 00b54f60 to 00b54f64 has its CatchHandler @ 00b5692a */
          CEGUI::String::~String((String *)&local_14d8);
          CEGUI::String::~String((String *)&local_1588);
          local_16e0 = 0x20;
          local_16d8 = 0;
          local_16c8 = 0;
          local_16d0 = 0;
          local_1640 = (undefined4 *)0x0;
          local_16e8 = 0;
          local_16c0[0] = 0;
          CEGUI::String::grow((ulong)&local_16e8);
          puVar16 = local_16c0;
          if (0x20 < local_16e0) {
            puVar16 = local_1640;
          }
          local_16e8 = 0;
          *puVar16 = 0;
          local_1630 = 0x20;
          local_1628 = 0;
          local_1618 = 0;
          local_1620 = 0;
          local_1590 = (uint *)0x0;
          local_1638 = 0;
          local_1610[0] = 0;
                    /* try { // try from 00b5505b to 00b5505f has its CatchHandler @ 00b568e2 */
          CEGUI::String::grow((ulong)&local_1638);
          puVar17 = local_1590;
          if (local_1630 < 0x21) {
            puVar17 = local_1610;
          }
          pbVar12 = (byte *)0xfd0c0d;
          do {
            bVar5 = *pbVar12;
            pbVar12 = pbVar12 + 1;
            *puVar17 = (uint)bVar5;
            puVar17 = puVar17 + 1;
          } while (pbVar12 != (byte *)0xfd0c12);
          local_1638 = 5;
          puVar17 = local_15fc;
          if (0x20 < local_1630) {
            puVar17 = local_1590 + 5;
          }
          *puVar17 = 0;
                    /* try { // try from 00b550da to 00b550de has its CatchHandler @ 00b569a7 */
          CEGUI::PropertySet::setProperty(*(String **)(pCVar24 + 0x1548),(String *)&local_1638);
                    /* try { // try from 00b550e7 to 00b550eb has its CatchHandler @ 00b568e2 */
          CEGUI::String::~String((String *)&local_1638);
          CEGUI::String::~String((String *)&local_16e8);
          CEGUI::Window::getSize();
                    /* try { // try from 00b5511a to 00b5511e has its CatchHandler @ 00b5699f */
          CEGUI::Window::setSize(*(UVector2 **)(pCVar24 + 0x1548));
          local_1840 = 0x20;
          local_1838 = 0;
          local_1828 = 0;
          local_1830 = 0;
          local_17a0 = (undefined4 *)0x0;
          local_1848 = 0;
          local_1820[0] = 0;
          CEGUI::String::grow((ulong)&local_1848);
          puVar16 = local_1820;
          if (0x20 < local_1840) {
            puVar16 = local_17a0;
          }
          local_1848 = 0;
          *puVar16 = 0;
          local_1790 = 0x20;
          local_1788 = 0;
          local_1778 = 0;
          local_1780 = 0;
          local_16f0 = (uint *)0x0;
          local_1798 = 0;
          local_1770[0] = 0;
                    /* try { // try from 00b5520a to 00b5520e has its CatchHandler @ 00b5699a */
          CEGUI::String::grow((ulong)&local_1798);
          puVar17 = local_16f0;
          if (local_1790 < 0x21) {
            puVar17 = local_1770;
          }
          pbVar12 = (byte *)0xfd0c0d;
          do {
            bVar5 = *pbVar12;
            pbVar12 = pbVar12 + 1;
            *puVar17 = (uint)bVar5;
            puVar17 = puVar17 + 1;
          } while (pbVar12 != (byte *)0xfd0c12);
          local_1798 = 5;
          puVar17 = local_175c;
          if (0x20 < local_1790) {
            puVar17 = local_16f0 + 5;
          }
          *puVar17 = 0;
                    /* try { // try from 00b55287 to 00b5528b has its CatchHandler @ 00b56975 */
          CEGUI::PropertySet::setProperty(*(String **)(pCVar24 + 0x12b8),(String *)&local_1798);
                    /* try { // try from 00b55294 to 00b55298 has its CatchHandler @ 00b5699a */
          CEGUI::String::~String((String *)&local_1798);
          CEGUI::String::~String((String *)&local_1848);
          CEGUI::Window::getSize();
                    /* try { // try from 00b552c7 to 00b552cb has its CatchHandler @ 00b56965 */
          CEGUI::Window::setSize(*(UVector2 **)(pCVar24 + 0x12b8));
          local_18f0 = 0x20;
          local_18e8 = 0;
          local_18d8 = 0;
          local_18e0 = 0;
          local_1850 = (uint *)0x0;
          local_18f8 = 0;
          local_18d0[0] = 0;
          CEGUI::String::grow((ulong)&local_18f8);
          puVar17 = local_1850;
          if (local_18f0 < 0x21) {
            puVar17 = local_18d0;
          }
          pbVar12 = (byte *)0xfd0c0d;
          do {
            bVar5 = *pbVar12;
            pbVar12 = pbVar12 + 1;
            *puVar17 = (uint)bVar5;
            puVar17 = puVar17 + 1;
          } while (pbVar12 != (byte *)0xfd0c12);
          local_18f8 = 5;
          puVar17 = local_18bc;
          if (0x20 < local_18f0) {
            puVar17 = local_1850 + 5;
          }
          *puVar17 = 0;
                    /* try { // try from 00b553bf to 00b553c3 has its CatchHandler @ 00b56468 */
          CEGUI::PropertySet::setProperty(*(String **)(pCVar24 + 0x1028),(String *)&local_18f8);
          CEGUI::String::~String((String *)&local_18f8);
          pSVar22 = local_19a8;
          puVar14 = (uchar *)CEGUI::String::build_utf8_buff();
          CEGUI::String::String(pSVar22,puVar14);
                    /* try { // try from 00b55407 to 00b5540b has its CatchHandler @ 00b56455 */
          CEGUI::Window::setTooltipText(*(String **)(pCVar24 + 0x1028));
        }
        else {
          pCVar25 = *(CEquipment **)(lVar20 + 0x10);
          local_22f0 = *(UVector2 **)(pCVar25 + 0x2c8);
          if (local_22f0 == (UVector2 *)0x0) {
            CEquipment::createIcon(pCVar25,*(CGameUI **)(this + 0x70),false);
            local_22f0 = *(UVector2 **)(pCVar25 + 0x2c8);
            if (local_22f0 != (UVector2 *)0x0) {
              CEGUI::EventSet::setMutedState((bool)((char)local_22f0 + '8'));
              local_22f0[0x3e2] = (UVector2)0x1;
              goto LAB_00b5359e;
            }
          }
          else {
LAB_00b5359e:
            if (*(Window **)(local_22f0 + 0xb0) != (Window *)0x0) {
              CEGUI::Window::removeChildWindow(*(Window **)(local_22f0 + 0xb0));
            }
            CEGUI::Window::addChildWindow(*(Window **)(pCVar24 + 0x1028));
          }
          pfVar11 = (float *)CEGUI::Window::getPosition();
          fVar8 = DAT_00fa86f4;
          fVar7 = DAT_00fa4810;
          fVar3 = *pfVar11;
          uVar26 = -(uint)(0.0 < fVar3 * 0.0);
          uVar32 = (uint)DAT_00fa4810 & uVar26;
          uVar28 = ~uVar26 & (uint)DAT_00fa86f4;
          fVar29 = pfVar11[1];
          lVar20 = CEGUI::Window::getPosition();
          fVar31 = *(float *)(lVar20 + 8) * 0.0;
          uVar26 = -(uint)(0.0 < fVar31);
          fVar30 = *(float *)(lVar20 + 0xc);
          if (((pCVar25[0x348] == (CEquipment)0x0) || (*(int *)(pCVar25 + 0x3e0) == 0)) ||
             (cVar9 = CEGUI::Window::isVisible
                                (SUB81(*(undefined8 *)(*(long *)(pCVar24 + 0x1028) + 0xb0),0)),
             cVar9 == '\0')) {
            local_710 = 0x20;
            local_708 = 0;
            local_6f8 = 0;
            local_700 = 0;
            local_670 = (undefined4 *)0x0;
            local_718 = 0;
            local_6f0[0] = 0;
            CEGUI::String::grow((ulong)&local_718);
            local_718 = 0;
            puVar16 = local_6f0;
            if (0x20 < local_710) {
              puVar16 = local_670;
            }
            *puVar16 = 0;
            local_660 = 0x20;
            local_658 = 0;
            local_648 = 0;
            local_650 = 0;
            local_5c0 = (uint *)0x0;
            local_668 = 0;
            local_640[0] = 0;
                    /* try { // try from 00b5376f to 00b53773 has its CatchHandler @ 00b568d7 */
            CEGUI::String::grow((ulong)&local_668);
            puVar17 = local_640;
            if (0x20 < local_660) {
              puVar17 = local_5c0;
            }
            pbVar12 = (byte *)0xfd0c0d;
            do {
              bVar5 = *pbVar12;
              pbVar12 = pbVar12 + 1;
              *puVar17 = (uint)bVar5;
              puVar17 = puVar17 + 1;
            } while (pbVar12 != (byte *)0xfd0c12);
            local_668 = 5;
            puVar17 = local_62c;
            if (0x20 < local_660) {
              puVar17 = local_5c0 + 5;
            }
            *puVar17 = 0;
                    /* try { // try from 00b537e8 to 00b537ec has its CatchHandler @ 00b568b6 */
            CEGUI::PropertySet::setProperty(*(String **)(pCVar24 + 0x1548),(String *)&local_668);
                    /* try { // try from 00b537f0 to 00b537f4 has its CatchHandler @ 00b568d7 */
            CEGUI::String::~String((String *)&local_668);
            CEGUI::String::~String((String *)&local_718);
          }
          else {
            if (*(uint *)(pCVar25 + 0x3e0) < 2) {
              if (*(uint *)(pCVar25 + 0x3e0) == 1) {
                pSVar22 = (String *)&local_458;
                local_450 = 0x20;
                local_448 = 0;
                local_438 = 0;
                local_440 = 0;
                local_3b0 = (uint *)0x0;
                local_458 = 0;
                local_430[0] = 0;
                CEGUI::String::grow((ulong)pSVar22);
                puVar17 = local_430;
                if (0x20 < local_450) {
                  puVar17 = local_3b0;
                }
                pcVar13 = "onesocketglow";
                do {
                  bVar5 = *pcVar13;
                  pcVar13 = pcVar13 + 1;
                  *puVar17 = (uint)bVar5;
                  puVar17 = puVar17 + 1;
                } while ((byte *)pcVar13 != (byte *)0xfe60de);
                local_458 = 0xd;
                puVar17 = local_3fc;
                if (0x20 < local_450) {
                  puVar17 = local_3b0 + 0xd;
                }
                *puVar17 = 0;
                    /* try { // try from 00b55a7d to 00b55a94 has its CatchHandler @ 00b56423 */
                CEGUI::Imageset::getImage(*(String **)(this + 0x1cf8));
                CEGUI::PropertyHelper::imageToString(local_508);
                local_5b0 = 0x20;
                local_5a8 = 0;
                local_598 = 0;
                local_5a0 = 0;
                local_510 = (uint *)0x0;
                local_5b8 = 0;
                local_590[0] = 0;
                    /* try { // try from 00b55af8 to 00b55afc has its CatchHandler @ 00b563c6 */
                CEGUI::String::grow((ulong)&local_5b8);
                puVar17 = local_590;
                if (0x20 < local_5b0) {
                  puVar17 = local_510;
                }
                pbVar12 = (byte *)0xfd0c0d;
                do {
                  bVar5 = *pbVar12;
                  pbVar12 = pbVar12 + 1;
                  *puVar17 = (uint)bVar5;
                  puVar17 = puVar17 + 1;
                } while (pbVar12 != (byte *)0xfd0c12);
                local_5b8 = 5;
                puVar17 = local_57c;
                if (0x20 < local_5b0) {
                  puVar17 = local_510 + 5;
                }
                *puVar17 = 0;
                    /* try { // try from 00b55b6f to 00b55b73 has its CatchHandler @ 00b56955 */
                CEGUI::PropertySet::setProperty(*(String **)(pCVar24 + 0x1548),(String *)&local_5b8)
                ;
                    /* try { // try from 00b55b77 to 00b55b7b has its CatchHandler @ 00b563c6 */
                CEGUI::String::~String((String *)&local_5b8);
                    /* try { // try from 00b55b7f to 00b55b83 has its CatchHandler @ 00b56423 */
                CEGUI::String::~String((String *)local_508);
                goto LAB_00b5561c;
              }
            }
            else {
              pSVar22 = (String *)&local_248;
              local_240 = 0x20;
              local_238 = 0;
              local_228 = 0;
              local_230 = 0;
              local_1a0 = (uint *)0x0;
              local_248 = 0;
              local_220[0] = 0;
              CEGUI::String::grow((ulong)pSVar22);
              puVar17 = local_220;
              if (0x20 < local_240) {
                puVar17 = local_1a0;
              }
              pcVar13 = "twosocketglow";
              do {
                bVar5 = *pcVar13;
                pcVar13 = pcVar13 + 1;
                *puVar17 = (uint)bVar5;
                puVar17 = puVar17 + 1;
              } while ((byte *)pcVar13 != (byte *)0xfe60d0);
              local_248 = 0xd;
              puVar17 = local_1ec;
              if (0x20 < local_240) {
                puVar17 = local_1a0 + 0xd;
              }
              *puVar17 = 0;
                    /* try { // try from 00b55515 to 00b5552c has its CatchHandler @ 00b569c6 */
              CEGUI::Imageset::getImage(*(String **)(this + 0x1cf8));
              CEGUI::PropertyHelper::imageToString(local_2f8);
              local_3a0 = 0x20;
              local_398 = 0;
              local_388 = 0;
              local_390 = 0;
              local_300 = (uint *)0x0;
              local_3a8 = 0;
              local_380[0] = 0;
                    /* try { // try from 00b55590 to 00b55594 has its CatchHandler @ 00b569c1 */
              CEGUI::String::grow((ulong)&local_3a8);
              puVar17 = local_380;
              if (0x20 < local_3a0) {
                puVar17 = local_300;
              }
              pbVar12 = (byte *)0xfd0c0d;
              do {
                bVar5 = *pbVar12;
                pbVar12 = pbVar12 + 1;
                *puVar17 = (uint)bVar5;
                puVar17 = puVar17 + 1;
              } while (pbVar12 != (byte *)0xfd0c12);
              local_3a8 = 5;
              puVar17 = local_36c;
              if (0x20 < local_3a0) {
                puVar17 = local_300 + 5;
              }
              *puVar17 = 0;
                    /* try { // try from 00b55607 to 00b5560b has its CatchHandler @ 00b569bc */
              CEGUI::PropertySet::setProperty(*(String **)(pCVar24 + 0x1548),(String *)&local_3a8);
                    /* try { // try from 00b5560f to 00b55613 has its CatchHandler @ 00b569c1 */
              CEGUI::String::~String((String *)&local_3a8);
                    /* try { // try from 00b55617 to 00b5561b has its CatchHandler @ 00b569c6 */
              CEGUI::String::~String((String *)local_2f8);
LAB_00b5561c:
              CEGUI::String::~String(pSVar22);
            }
            CEGUI::Window::moveToFront();
          }
          if (pCVar25[0x348] == (CEquipment)0x0) {
            pSVar22 = (String *)&local_7c8;
            local_7c0 = 0x20;
            local_7b8 = 0;
            local_7a8 = 0;
            local_7b0 = 0;
            local_720 = (uint *)0x0;
            local_7c8 = 0;
            local_7a0[0] = 0;
            CEGUI::String::grow((ulong)pSVar22);
            puVar17 = local_7a0;
            if (0x20 < local_7c0) {
              puVar17 = local_720;
            }
            pcVar13 = "unidentified";
            do {
              bVar5 = *pcVar13;
              pcVar13 = pcVar13 + 1;
              *puVar17 = (uint)bVar5;
              puVar17 = puVar17 + 1;
            } while ((byte *)pcVar13 != (byte *)0xfef79d);
            local_7c8 = 0xc;
            puVar17 = local_770;
            if (0x20 < local_7c0) {
              puVar17 = local_720 + 0xc;
            }
            *puVar17 = 0;
                    /* try { // try from 00b538dd to 00b538f4 has its CatchHandler @ 00b568d2 */
            CEGUI::Imageset::getImage(*(String **)(this + 0x1cf8));
            CEGUI::PropertyHelper::imageToString(local_878);
            local_920 = 0x20;
            local_918 = 0;
            local_908 = 0;
            local_910 = 0;
            local_880 = (uint *)0x0;
            local_928 = 0;
            local_900[0] = 0;
                    /* try { // try from 00b53958 to 00b5395c has its CatchHandler @ 00b56897 */
            CEGUI::String::grow((ulong)&local_928);
            puVar17 = local_900;
            if (0x20 < local_920) {
              puVar17 = local_880;
            }
            pbVar12 = (byte *)0xfd0c0d;
            do {
              bVar5 = *pbVar12;
              pbVar12 = pbVar12 + 1;
              *puVar17 = (uint)bVar5;
              puVar17 = puVar17 + 1;
            } while (pbVar12 != (byte *)0xfd0c12);
            local_928 = 5;
            puVar17 = local_8ec;
            if (0x20 < local_920) {
              puVar17 = local_880 + 5;
            }
            *puVar17 = 0;
                    /* try { // try from 00b539cf to 00b539d3 has its CatchHandler @ 00b5689c */
            CEGUI::PropertySet::setProperty(*(String **)(pCVar24 + 0x1a68),(String *)&local_928);
                    /* try { // try from 00b539d7 to 00b539db has its CatchHandler @ 00b56897 */
            CEGUI::String::~String((String *)&local_928);
                    /* try { // try from 00b539df to 00b539e3 has its CatchHandler @ 00b568d2 */
            CEGUI::String::~String((String *)local_878);
          }
          else {
            pSVar22 = (String *)&local_a88;
            local_a80 = 0x20;
            local_a78 = 0;
            local_a68 = 0;
            local_a70 = 0;
            local_9e0 = (undefined4 *)0x0;
            local_a88 = 0;
            local_a60[0] = 0;
            CEGUI::String::grow((ulong)pSVar22);
            local_a88 = 0;
            puVar16 = local_a60;
            if (0x20 < local_a80) {
              puVar16 = local_9e0;
            }
            *puVar16 = 0;
            local_9d0 = 0x20;
            local_9c8 = 0;
            local_9b8 = 0;
            local_9c0 = 0;
            local_930 = (uint *)0x0;
            local_9d8 = 0;
            local_9b0[0] = 0;
                    /* try { // try from 00b54b6a to 00b54b6e has its CatchHandler @ 00b568ff */
            CEGUI::String::grow((ulong)&local_9d8);
            puVar17 = local_9b0;
            if (0x20 < local_9d0) {
              puVar17 = local_930;
            }
            pbVar12 = (byte *)0xfd0c0d;
            do {
              bVar5 = *pbVar12;
              pbVar12 = pbVar12 + 1;
              *puVar17 = (uint)bVar5;
              puVar17 = puVar17 + 1;
            } while (pbVar12 != (byte *)0xfd0c12);
            local_9d8 = 5;
            puVar17 = local_99c;
            if (0x20 < local_9d0) {
              puVar17 = local_930 + 5;
            }
            *puVar17 = 0;
                    /* try { // try from 00b54bdf to 00b54be3 has its CatchHandler @ 00b56915 */
            CEGUI::PropertySet::setProperty(*(String **)(pCVar24 + 0x1a68),(String *)&local_9d8);
                    /* try { // try from 00b54be7 to 00b54beb has its CatchHandler @ 00b568ff */
            CEGUI::String::~String((String *)&local_9d8);
          }
          CEGUI::String::~String(pSVar22);
          fVar30 = (float)(int)(fVar31 + (float)(~uVar26 & (uint)fVar8 | (uint)fVar7 & uVar26)) +
                   fVar30;
          if (1 < *(uint *)(pCVar25 + 0x3e0)) {
            CEGUI::Window::getSize();
            uVar26 = -(uint)(0.0 < local_110 * 0.0);
            fVar30 = ((float)(int)((float)(~uVar26 & (uint)DAT_00fa86f4 |
                                          (uint)DAT_00fa4810 & uVar26) + local_110 * 0.0) +
                     local_10c) * _DAT_00fe6520 + fVar30;
          }
          cVar9 = CEGUI::Window::isVisible
                            (SUB81(*(undefined8 *)(*(long *)(pCVar24 + 0x1028) + 0xb0),0));
          if ((cVar9 != '\0') && (*(int *)(pCVar25 + 0x3f0) != 0)) {
            uVar26 = 0;
            do {
              if (uVar26 < *(uint *)(pCVar25 + 0x3f4)) {
                this_01 = *(CEquipment **)((ulong)uVar26 * 8 + *(long *)(pCVar25 + 1000));
                pUVar21 = *(UVector2 **)(this_01 + 0x2c8);
                if (pUVar21 != (UVector2 *)0x0) goto LAB_00b53ada;
LAB_00b53c14:
                CEquipment::createIcon(this_01,*(CGameUI **)(this + 0x70),false);
                pUVar21 = *(UVector2 **)(this_01 + 0x2c8);
                if (pUVar21 != (UVector2 *)0x0) {
                  CEGUI::EventSet::setMutedState((bool)((char)pUVar21 + '8'));
                  pUVar21[0x3e2] = (UVector2)0x1;
                  goto LAB_00b53ada;
                }
              }
              else {
                this_01 = (CEquipment *)**(long **)(pCVar25 + 1000);
                pUVar21 = *(UVector2 **)(this_01 + 0x2c8);
                if (pUVar21 == (UVector2 *)0x0) goto LAB_00b53c14;
LAB_00b53ada:
                if (*(Window **)(pUVar21 + 0xb0) != (Window *)0x0) {
                  CEGUI::Window::removeChildWindow(*(Window **)(pUVar21 + 0xb0));
                }
                CEGUI::Window::addChildWindow(*(Window **)(this + 0x30));
                local_128 = 0;
                local_120 = 0;
                local_124 = (float)(int)((float)(uVar28 | uVar32) + fVar3 * 0.0) + fVar29;
                local_11c = fVar30;
                    /* try { // try from 00b53b39 to 00b53b3d has its CatchHandler @ 00b568ac */
                CEGUI::Window::setPosition(pUVar21);
                CEGUI::Window::getSize();
                    /* try { // try from 00b53b53 to 00b53b57 has its CatchHandler @ 00b568b1 */
                CEGUI::Window::setSize(pUVar21);
                CEGUI::Window::moveToFront();
                pUVar21[0x3e2] = (UVector2)0x1;
              }
              uVar26 = uVar26 + 1;
              CEGUI::Window::getSize();
              uVar27 = -(uint)(0.0 < local_140 * 0.0);
              if (*(uint *)(pCVar25 + 0x3f0) <= uVar26) break;
              fVar30 = ((float)(int)((float)(~uVar27 & (uint)DAT_00fa86f4 |
                                            (uint)DAT_00fa4810 & uVar27) + local_140 * 0.0) +
                       local_13c) * DAT_00fa4830 + fVar30;
            } while( true );
          }
          cVar9 = CBaseUnit::ISA((CBaseUnit *)pCVar25,0x36);
          if (cVar9 == '\0') {
            cVar9 = (**(code **)(*(long *)pCVar25 + 0x2b0))(pCVar25);
            if (cVar9 == '\0') {
              pSVar22 = (String *)&local_1218;
              local_1210 = 0x20;
              local_1208 = 0;
              local_11f8 = 0;
              local_1200 = 0;
              local_1170 = (undefined4 *)0x0;
              local_1218 = 0;
              local_11f0[0] = 0;
              CEGUI::String::grow((ulong)pSVar22);
              local_1218 = 0;
              puVar16 = local_11f0;
              if (0x20 < local_1210) {
                puVar16 = local_1170;
              }
              *puVar16 = 0;
              local_1160 = 0x20;
              local_1158 = 0;
              local_1148 = 0;
              local_1150 = 0;
              local_10c0 = (uint *)0x0;
              local_1168 = 0;
              local_1140[0] = 0;
                    /* try { // try from 00b54d63 to 00b54d67 has its CatchHandler @ 00b568fa */
              CEGUI::String::grow((ulong)&local_1168);
              puVar17 = local_1140;
              if (0x20 < local_1160) {
                puVar17 = local_10c0;
              }
              pbVar12 = (byte *)0xfd0c0d;
              do {
                bVar5 = *pbVar12;
                pbVar12 = pbVar12 + 1;
                *puVar17 = (uint)bVar5;
                puVar17 = puVar17 + 1;
              } while (pbVar12 != (byte *)0xfd0c12);
              local_1168 = 5;
              puVar17 = local_112c;
              if (0x20 < local_1160) {
                puVar17 = local_10c0 + 5;
              }
              *puVar17 = 0;
                    /* try { // try from 00b54dd7 to 00b54ddb has its CatchHandler @ 00b56942 */
              CEGUI::PropertySet::setProperty(*(String **)(pCVar24 + 0x12b8),(String *)&local_1168);
                    /* try { // try from 00b54ddf to 00b54de3 has its CatchHandler @ 00b568fa */
              CEGUI::String::~String((String *)&local_1168);
            }
            else {
              cVar9 = CBaseUnit::ISA((CBaseUnit *)pCVar25,0x37);
              if (cVar9 == '\0') {
                pSVar22 = (String *)&local_f58;
                local_f50 = 0x20;
                local_f48 = 0;
                local_f38 = 0;
                local_f40 = 0;
                local_eb0 = (uint *)0x0;
                local_f58 = 0;
                local_f30[0] = 0;
                CEGUI::String::grow((ulong)pSVar22);
                puVar17 = local_f30;
                if (0x20 < local_f50) {
                  puVar17 = local_eb0;
                }
                pcVar13 = "greenslotglow";
                do {
                  bVar5 = *pcVar13;
                  pcVar13 = pcVar13 + 1;
                  *puVar17 = (uint)bVar5;
                  puVar17 = puVar17 + 1;
                } while ((byte *)pcVar13 != (byte *)0xfe60c2);
                local_f58 = 0xd;
                puVar17 = local_efc;
                if (0x20 < local_f50) {
                  puVar17 = local_eb0 + 0xd;
                }
                *puVar17 = 0;
                    /* try { // try from 00b55765 to 00b5577c has its CatchHandler @ 00b56935 */
                CEGUI::Imageset::getImage(*(String **)(this + 0x1cf8));
                CEGUI::PropertyHelper::imageToString(local_1008);
                local_10b0 = 0x20;
                local_10a8 = 0;
                local_1098 = 0;
                local_10a0 = 0;
                local_1010 = (uint *)0x0;
                local_10b8 = 0;
                local_1090[0] = 0;
                    /* try { // try from 00b557e0 to 00b557e4 has its CatchHandler @ 00b56925 */
                CEGUI::String::grow((ulong)&local_10b8);
                puVar17 = local_1090;
                if (0x20 < local_10b0) {
                  puVar17 = local_1010;
                }
                pbVar12 = (byte *)0xfd0c0d;
                do {
                  bVar5 = *pbVar12;
                  pbVar12 = pbVar12 + 1;
                  *puVar17 = (uint)bVar5;
                  puVar17 = puVar17 + 1;
                } while (pbVar12 != (byte *)0xfd0c12);
                local_10b8 = 5;
                puVar17 = local_107c;
                if (0x20 < local_10b0) {
                  puVar17 = local_1010 + 5;
                }
                *puVar17 = 0;
                    /* try { // try from 00b55847 to 00b5584b has its CatchHandler @ 00b5679b */
                CEGUI::PropertySet::setProperty
                          (*(String **)(pCVar24 + 0x12b8),(String *)&local_10b8);
                    /* try { // try from 00b5584f to 00b55853 has its CatchHandler @ 00b56925 */
                CEGUI::String::~String((String *)&local_10b8);
                    /* try { // try from 00b55857 to 00b5585b has its CatchHandler @ 00b56935 */
                CEGUI::String::~String((String *)local_1008);
              }
              else {
                pSVar22 = (String *)&local_d48;
                local_d40 = 0x20;
                local_d38 = 0;
                local_d28 = 0;
                local_d30 = 0;
                local_ca0 = (uint *)0x0;
                local_d48 = 0;
                local_d20[0] = 0;
                CEGUI::String::grow((ulong)pSVar22);
                puVar17 = local_d20;
                if (0x20 < local_d40) {
                  puVar17 = local_ca0;
                }
                pcVar13 = "blueslotglow";
                do {
                  bVar5 = *pcVar13;
                  pcVar13 = pcVar13 + 1;
                  *puVar17 = (uint)bVar5;
                  puVar17 = puVar17 + 1;
                } while ((byte *)pcVar13 != (byte *)0xfe60b4);
                local_d48 = 0xc;
                puVar17 = local_cf0;
                if (0x20 < local_d40) {
                  puVar17 = local_ca0 + 0xc;
                }
                *puVar17 = 0;
                    /* try { // try from 00b54975 to 00b5498c has its CatchHandler @ 00b56782 */
                CEGUI::Imageset::getImage(*(String **)(this + 0x1cf8));
                CEGUI::PropertyHelper::imageToString(local_df8);
                local_ea0 = 0x20;
                local_e98 = 0;
                local_e88 = 0;
                local_e90 = 0;
                local_e00 = (uint *)0x0;
                local_ea8 = 0;
                local_e80[0] = 0;
                    /* try { // try from 00b549f0 to 00b549f4 has its CatchHandler @ 00b567a0 */
                CEGUI::String::grow((ulong)&local_ea8);
                puVar17 = local_e80;
                if (0x20 < local_ea0) {
                  puVar17 = local_e00;
                }
                pbVar12 = (byte *)0xfd0c0d;
                do {
                  bVar5 = *pbVar12;
                  pbVar12 = pbVar12 + 1;
                  *puVar17 = (uint)bVar5;
                  puVar17 = puVar17 + 1;
                } while (pbVar12 != (byte *)0xfd0c12);
                local_ea8 = 5;
                puVar17 = local_e6c;
                if (0x20 < local_ea0) {
                  puVar17 = local_e00 + 5;
                }
                *puVar17 = 0;
                    /* try { // try from 00b54a57 to 00b54a5b has its CatchHandler @ 00b56947 */
                CEGUI::PropertySet::setProperty(*(String **)(pCVar24 + 0x12b8),(String *)&local_ea8)
                ;
                    /* try { // try from 00b54a5f to 00b54a63 has its CatchHandler @ 00b567a0 */
                CEGUI::String::~String((String *)&local_ea8);
                    /* try { // try from 00b54a67 to 00b54a6b has its CatchHandler @ 00b56782 */
                CEGUI::String::~String((String *)local_df8);
              }
            }
          }
          else {
            pSVar22 = (String *)&local_b38;
            local_b30 = 0x20;
            local_b28 = 0;
            local_b18 = 0;
            local_b20 = 0;
            local_a90 = (uint *)0x0;
            local_b38 = 0;
            local_b10[0] = 0;
            CEGUI::String::grow((ulong)pSVar22);
            puVar17 = local_b10;
            if (0x20 < local_b30) {
              puVar17 = local_a90;
            }
            pcVar13 = "goldslotglow";
            do {
              bVar5 = *pcVar13;
              pcVar13 = pcVar13 + 1;
              *puVar17 = (uint)bVar5;
              puVar17 = puVar17 + 1;
            } while ((byte *)pcVar13 != (byte *)0xfe60a7);
            local_b38 = 0xc;
            puVar17 = local_ae0;
            if (0x20 < local_b30) {
              puVar17 = local_a90 + 0xc;
            }
            *puVar17 = 0;
                    /* try { // try from 00b53d4d to 00b53d64 has its CatchHandler @ 00b56428 */
            CEGUI::Imageset::getImage(*(String **)(this + 0x1cf8));
            CEGUI::PropertyHelper::imageToString(local_be8);
            local_c90 = 0x20;
            local_c88 = 0;
            local_c78 = 0;
            local_c80 = 0;
            local_bf0 = (uint *)0x0;
            local_c98 = 0;
            local_c70[0] = 0;
                    /* try { // try from 00b53dc8 to 00b53dcc has its CatchHandler @ 00b5643b */
            CEGUI::String::grow((ulong)&local_c98);
            puVar17 = local_c70;
            if (0x20 < local_c90) {
              puVar17 = local_bf0;
            }
            pbVar12 = (byte *)0xfd0c0d;
            do {
              bVar5 = *pbVar12;
              pbVar12 = pbVar12 + 1;
              *puVar17 = (uint)bVar5;
              puVar17 = puVar17 + 1;
            } while (pbVar12 != (byte *)0xfd0c12);
            local_c98 = 5;
            puVar17 = local_c5c;
            if (0x20 < local_c90) {
              puVar17 = local_bf0 + 5;
            }
            *puVar17 = 0;
                    /* try { // try from 00b53e3f to 00b53e43 has its CatchHandler @ 00b56448 */
            CEGUI::PropertySet::setProperty(*(String **)(pCVar24 + 0x12b8),(String *)&local_c98);
                    /* try { // try from 00b53e47 to 00b53e4b has its CatchHandler @ 00b5643b */
            CEGUI::String::~String((String *)&local_c98);
                    /* try { // try from 00b53e4f to 00b53e53 has its CatchHandler @ 00b56428 */
            CEGUI::String::~String((String *)local_be8);
          }
          CEGUI::String::~String(pSVar22);
          local_1370 = 0x20;
          local_1368 = 0;
          local_1358 = 0;
          local_1360 = 0;
          local_12d0 = (undefined4 *)0x0;
          local_1378 = 0;
          local_1350[0] = 0;
          CEGUI::String::grow((ulong)&local_1378);
          local_1378 = 0;
          puVar16 = local_1350;
          if (0x20 < local_1370) {
            puVar16 = local_12d0;
          }
          *puVar16 = 0;
          local_12c0 = 0x20;
          local_12b8 = 0;
          local_12a8 = 0;
          local_12b0 = 0;
          local_1220 = (uint *)0x0;
          local_12c8 = 0;
          local_12a0[0] = 0;
                    /* try { // try from 00b53f4e to 00b53f52 has its CatchHandler @ 00b56720 */
          CEGUI::String::grow((ulong)&local_12c8);
          puVar17 = local_12a0;
          if (0x20 < local_12c0) {
            puVar17 = local_1220;
          }
          pbVar12 = (byte *)0xfd0c0d;
          do {
            bVar5 = *pbVar12;
            pbVar12 = pbVar12 + 1;
            *puVar17 = (uint)bVar5;
            puVar17 = puVar17 + 1;
          } while (pbVar12 != (byte *)0xfd0c12);
          local_12c8 = 5;
          puVar17 = local_128c;
          if (0x20 < local_12c0) {
            puVar17 = local_1220 + 5;
          }
          *puVar17 = 0;
                    /* try { // try from 00b53fbf to 00b53fc3 has its CatchHandler @ 00b56725 */
          CEGUI::PropertySet::setProperty(*(String **)(pCVar24 + 0x1028),(String *)&local_12c8);
                    /* try { // try from 00b53fc7 to 00b53fcb has its CatchHandler @ 00b56720 */
          CEGUI::String::~String((String *)&local_12c8);
          CEGUI::String::~String((String *)&local_1378);
          if (local_22f0 != (UVector2 *)0x0) {
            local_154 = 0;
            local_158 = 0;
            local_14c = 0x3f800000;
            local_150 = 0;
                    /* try { // try from 00b54019 to 00b5401d has its CatchHandler @ 00b56735 */
            CEGUI::Window::setPosition(local_22f0);
            CEGUI::Window::getSize();
            fVar29 = local_168 * 0.0;
            fVar30 = local_160 * 0.0;
            fVar3 = DAT_00fa4810;
            if (fVar29 <= 0.0) {
              fVar3 = DAT_00fa86f4;
            }
            local_160 = 0.0;
            local_168 = 0.0;
            uVar26 = -(uint)(0.0 < fVar30);
            local_174 = 0;
            local_178 = 0;
            local_170 = 0;
            local_164 = (float)(int)(fVar29 + fVar3) + local_164;
            local_16c = (uint)((DAT_00fce498 * local_164 -
                               ((float)(int)((float)(~uVar26 & (uint)DAT_00fa86f4 |
                                                    (uint)DAT_00fa4810 & uVar26) + fVar30) +
                               local_15c)) * DAT_00fa4810) ^ DAT_00fa8780;
            local_15c = DAT_00fce498 * local_164;
                    /* try { // try from 00b54135 to 00b54139 has its CatchHandler @ 00b5673a */
            CEGUI::Window::setPosition(local_22f0);
                    /* try { // try from 00b54142 to 00b54162 has its CatchHandler @ 00b56745 */
            CEGUI::Window::setSize(local_22f0);
            CEGUI::Window::moveToFront();
            CEGUI::Window::update(DAT_00fa4828);
          }
          local_1420 = 0x20;
          local_1418 = 0;
          local_1408 = 0;
          local_1410 = 0;
          local_1380 = (undefined4 *)0x0;
          local_1428 = 0;
          local_1400[0] = 0;
          if (CEGUI::String::npos == 0) {
                    /* try { // try from 00b5564d to 00b55651 has its CatchHandler @ 00b56755 */
            std::string::string((string *)local_f8,
                                "Length for utf8 encoded string can not be \'npos\'",&local_3b);
            this_02 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00b55665 to 00b55669 has its CatchHandler @ 00b56765 */
            std::length_error::length_error(this_02,(string *)local_f8);
            if ((allocator *)(local_f8[0] + -0x18) !=
                (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar1 = (int *)(local_f8[0] + -8);
              iVar10 = *piVar1;
              *piVar1 = *piVar1 + -1;
              UNLOCK();
              if (iVar10 < 1) {
                std::string::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
              }
            }
            goto LAB_00b55683;
          }
          pSVar22 = (String *)&local_1428;
          CEGUI::String::grow((ulong)pSVar22);
          local_1428 = 0;
          puVar16 = local_1400;
          if (0x20 < local_1420) {
            puVar16 = local_1380;
          }
          *puVar16 = 0;
                    /* try { // try from 00b54205 to 00b54209 has its CatchHandler @ 00b5693a */
          CEGUI::Window::setTooltipText(*(String **)(pCVar24 + 0x1028));
        }
        CEGUI::String::~String(pSVar22);
      }
LAB_00b54212:
      uVar19 = uVar19 + 1;
      pCVar24 = pCVar24 + 8;
    } while (uVar19 != 0xc);
    local_2300 = 0x13;
    pCVar24 = this;
    do {
      local_1b00 = 0x20;
      local_1af8 = 0;
      local_1ae8 = 0;
      local_1af0 = 0;
      local_1a60 = (undefined4 *)0x0;
      local_1b08 = 0;
      local_1ae0[0] = 0;
      CEGUI::String::grow((ulong)&local_1b08);
      local_1b08 = 0;
      puVar16 = local_1a60;
      if (local_1b00 < 0x21) {
        puVar16 = local_1ae0;
      }
      *puVar16 = 0;
      local_1a50 = 0x20;
      local_1a48 = 0;
      local_1a38 = 0;
      local_1a40 = 0;
      local_19b0 = (uint *)0x0;
      local_1a58 = 0;
      local_1a30[0] = 0;
                    /* try { // try from 00b5437a to 00b5437e has its CatchHandler @ 00b567fc */
      CEGUI::String::grow((ulong)&local_1a58);
      puVar17 = local_1a30;
      if (0x20 < local_1a50) {
        puVar17 = local_19b0;
      }
      pbVar12 = (byte *)0xfd0c0d;
      do {
        bVar5 = *pbVar12;
        pbVar12 = pbVar12 + 1;
        *puVar17 = (uint)bVar5;
        puVar17 = puVar17 + 1;
      } while (pbVar12 != (byte *)0xfd0c12);
      local_1a58 = 5;
      puVar17 = local_1a1c;
      if (0x20 < local_1a50) {
        puVar17 = local_19b0 + 5;
      }
      *puVar17 = 0;
                    /* try { // try from 00b543f4 to 00b543f8 has its CatchHandler @ 00b56819 */
      CEGUI::PropertySet::setProperty(*(String **)(pCVar24 + 0x1350),(String *)&local_1a58);
                    /* try { // try from 00b543fc to 00b54400 has its CatchHandler @ 00b567fc */
      CEGUI::String::~String((String *)&local_1a58);
      CEGUI::String::~String((String *)&local_1b08);
      local_1c60 = 0x20;
      local_1c58 = 0;
      local_1c48 = 0;
      local_1c50 = 0;
      local_1bc0 = (undefined4 *)0x0;
      local_1c68 = 0;
      local_1c40[0] = 0;
      CEGUI::String::grow((ulong)&local_1c68);
      puVar16 = local_1c40;
      if (0x20 < local_1c60) {
        puVar16 = local_1bc0;
      }
      local_1c68 = 0;
      *puVar16 = 0;
      local_1bb0 = 0x20;
      local_1ba8 = 0;
      local_1b98 = 0;
      local_1ba0 = 0;
      local_1b10 = (uint *)0x0;
      local_1bb8 = 0;
      local_1b90[0] = 0;
                    /* try { // try from 00b544f9 to 00b544fd has its CatchHandler @ 00b56826 */
      CEGUI::String::grow((ulong)&local_1bb8);
      pbVar12 = (byte *)0xfd0c0d;
      puVar17 = local_1b90;
      if (0x20 < local_1bb0) {
        puVar17 = local_1b10;
      }
      do {
        bVar5 = *pbVar12;
        pbVar12 = pbVar12 + 1;
        *puVar17 = (uint)bVar5;
        puVar17 = puVar17 + 1;
      } while (pbVar12 != (byte *)0xfd0c12);
      local_1bb8 = 5;
      if (local_1bb0 < 0x21) {
        puVar17 = local_1b7c;
      }
      else {
        puVar17 = local_1b10 + 5;
      }
      *puVar17 = 0;
                    /* try { // try from 00b54576 to 00b5457a has its CatchHandler @ 00b5683b */
      CEGUI::PropertySet::setProperty(*(String **)(pCVar24 + 0x15e0),(String *)&local_1bb8);
                    /* try { // try from 00b54583 to 00b54587 has its CatchHandler @ 00b56826 */
      CEGUI::String::~String((String *)&local_1bb8);
      CEGUI::String::~String((String *)&local_1c68);
      local_1dc0 = 0x20;
      local_1db8 = 0;
      local_1da8 = 0;
      local_1db0 = 0;
      local_1d20 = (undefined4 *)0x0;
      local_1dc8 = 0;
      local_1da0[0] = 0;
      CEGUI::String::grow((ulong)&local_1dc8);
      puVar16 = local_1da0;
      if (0x20 < local_1dc0) {
        puVar16 = local_1d20;
      }
      local_1dc8 = 0;
      *puVar16 = 0;
      local_1d10 = 0x20;
      local_1d08 = 0;
      local_1cf8 = 0;
      local_1d00 = 0;
      local_1c70 = (uint *)0x0;
      local_1d18 = 0;
      local_1cf0[0] = 0;
                    /* try { // try from 00b54680 to 00b54684 has its CatchHandler @ 00b5684d */
      CEGUI::String::grow((ulong)&local_1d18);
      pbVar12 = (byte *)0xfd0c0d;
      puVar17 = local_1cf0;
      if (0x20 < local_1d10) {
        puVar17 = local_1c70;
      }
      do {
        bVar5 = *pbVar12;
        pbVar12 = pbVar12 + 1;
        *puVar17 = (uint)bVar5;
        puVar17 = puVar17 + 1;
      } while (pbVar12 != (byte *)0xfd0c12);
      local_1d18 = 5;
      if (local_1d10 < 0x21) {
        puVar17 = local_1cdc;
      }
      else {
        puVar17 = local_1c70 + 5;
      }
      *puVar17 = 0;
                    /* try { // try from 00b546fe to 00b54702 has its CatchHandler @ 00b56865 */
      CEGUI::PropertySet::setProperty(*(String **)(pCVar24 + 0x1b00),(String *)&local_1d18);
                    /* try { // try from 00b5470b to 00b5470f has its CatchHandler @ 00b5684d */
      CEGUI::String::~String((String *)&local_1d18);
      CEGUI::String::~String((String *)&local_1dc8);
      if (*(long *)(pCVar24 + 0x1870) != 0) {
        local_1e70 = 0x20;
        local_1e68 = 0;
        local_1e58 = 0;
        local_1e60 = 0;
        local_1dd0 = (undefined4 *)0x0;
        local_1e78 = 0;
        local_1e50[0] = 0;
        if (CEGUI::String::npos == 0) {
                    /* try { // try from 00b55879 to 00b5587d has its CatchHandler @ 00b567d4 */
          std::string::string((string *)local_108,
                              "Length for utf8 encoded string can not be \'npos\'",local_3d);
          this_02 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00b55891 to 00b55895 has its CatchHandler @ 00b567e4 */
          std::length_error::length_error(this_02,(string *)local_108);
          if ((allocator *)(local_108[0] + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_108[0] + -8);
            iVar10 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar10 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_108[0] + -0x18));
            }
          }
LAB_00b55683:
                    /* WARNING: Subroutine does not return */
          __cxa_throw(this_02,&std::length_error::typeinfo,std::length_error::~length_error);
        }
        CEGUI::String::grow((ulong)&local_1e78);
        local_1e78 = 0;
        puVar16 = local_1e50;
        if (0x20 < local_1e70) {
          puVar16 = local_1dd0;
        }
        *puVar16 = 0;
                    /* try { // try from 00b547c7 to 00b547cb has its CatchHandler @ 00b56877 */
        CEGUI::Window::setText(*(String **)(pCVar24 + 0x1870));
        CEGUI::String::~String((String *)&local_1e78);
      }
      pWVar6 = *(Window **)(pCVar24 + 0x10c0);
      if (*(long *)(pWVar6 + 0x80) - *(long *)(pWVar6 + 0x78) >> 3 != 0) {
        CEGUI::Window::removeChildWindow(pWVar6);
      }
      local_2300 = local_2300 + 1;
      pCVar24 = pCVar24 + 8;
    } while (local_2300 != 0x52);
    if (*(int *)(this_00 + 0x38) != 0) {
      uVar23 = 0;
      do {
        uVar19 = (uint)uVar23;
        if (uVar19 < *(uint *)(this_00 + 0x3c)) {
          plVar18 = *(long **)(this_00 + 0x30);
          lVar20 = plVar18[uVar23];
          pCVar25 = *(CEquipment **)(lVar20 + 0x10);
        }
        else {
          plVar18 = *(long **)(this_00 + 0x30);
          lVar20 = *plVar18;
          pCVar25 = *(CEquipment **)(lVar20 + 0x10);
        }
        if (0x12 < *(int *)(lVar20 + 0x18)) {
          if (uVar19 < *(uint *)(this_00 + 0x3c)) {
            plVar18 = (long *)(uVar23 * 8 + *(long *)(this_00 + 0x30));
          }
          setSlotIcon(this,pCVar25,*(int *)(*plVar18 + 0x18),*(int *)(*plVar18 + 0x18));
        }
        uVar23 = (ulong)(uVar19 + 1);
      } while (uVar19 + 1 < *(uint *)(this_00 + 0x38));
    }
    uVar19 = 0;
    local_22c8 = this;
    do {
      if (*(long *)(local_22c8 + 0x8dc8) != 0) {
        if ((updateLayout()::g_RemoveASpell == '\0') &&
           (iVar10 = __cxa_guard_acquire(&updateLayout()::g_RemoveASpell), iVar10 != 0)) {
          updateLayout()::g_RemoveASpell = &DAT_01424558;
          __cxa_guard_release(&updateLayout()::g_RemoveASpell);
          __cxa_atexit(std::wstring::~wstring,&updateLayout()::g_RemoveASpell,&__dso_handle);
        }
        if (*(long *)(updateLayout()::g_RemoveASpell + -6) == 0) {
          CStringTranslate::getSinglton();
          CStringTranslate::getTranslateString((wchar_t *)local_58);
                    /* try { // try from 00b5631e to 00b56322 has its CatchHandler @ 00b563b3 */
          std::wstring::assign((wstring_conflict *)&updateLayout()::g_RemoveASpell);
          if ((allocator *)(local_58[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_58[0] + -8);
            iVar10 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar10 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
            }
          }
        }
        if ((updateLayout()::g_RemoveASpell2 == '\0') &&
           (iVar10 = __cxa_guard_acquire(&updateLayout()::g_RemoveASpell2), iVar10 != 0)) {
          updateLayout()::g_RemoveASpell2 = &DAT_01424558;
          __cxa_guard_release(&updateLayout()::g_RemoveASpell2);
          __cxa_atexit(std::wstring::~wstring,&updateLayout()::g_RemoveASpell2,&__dso_handle);
        }
        if (*(long *)(updateLayout()::g_RemoveASpell2 + -6) == 0) {
          CStringTranslate::getSinglton();
          CStringTranslate::getTranslateString((wchar_t *)local_68);
                    /* try { // try from 00b5626b to 00b5626f has its CatchHandler @ 00b56597 */
          std::wstring::assign((wstring_conflict *)&updateLayout()::g_RemoveASpell2);
          if ((allocator *)(local_68[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_68[0] + -8);
            iVar10 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar10 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
            }
          }
        }
        if ((updateLayout()::g_DragASpell == '\0') &&
           (iVar10 = __cxa_guard_acquire(&updateLayout()::g_DragASpell), iVar10 != 0)) {
          updateLayout()::g_DragASpell = &DAT_01424558;
          __cxa_guard_release(&updateLayout()::g_DragASpell);
          __cxa_atexit(std::wstring::~wstring,&updateLayout()::g_DragASpell,&__dso_handle);
        }
        if (*(long *)(updateLayout()::g_DragASpell + -6) == 0) {
          CStringTranslate::getSinglton();
          CStringTranslate::getTranslateString((wchar_t *)local_78);
                    /* try { // try from 00b55cb8 to 00b55cbc has its CatchHandler @ 00b564ac */
          std::wstring::assign((wstring_conflict *)&updateLayout()::g_DragASpell);
          if ((allocator *)(local_78[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_78[0] + -8);
            iVar10 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar10 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
            }
          }
        }
        this_03 = (CSkill *)CCharacter::getKnownSpell(*(CCharacter **)(this + 0x50),uVar19);
        if ((this_03 == (CSkill *)0x0) ||
           (plVar18 = (long *)CSkill::getSkillIcon(this_03), *(long *)(*plVar18 + -0x18) == 0)) {
                    /* try { // try from 00b55fe6 to 00b55fea has its CatchHandler @ 00b564e3 */
          std::wstring::wstring((wstring_conflict *)local_d8,updateLayout()::g_DragASpell,&local_3a)
          ;
                    /* try { // try from 00b55ffb to 00b55fff has its CatchHandler @ 00b564de */
          STRINGS::StringConvertToUTF8((wstring_conflict *)local_e8);
                    /* try { // try from 00b56010 to 00b56014 has its CatchHandler @ 00b564bc */
          CEGUI::String::String(local_2138,local_e8[0]);
                    /* try { // try from 00b56029 to 00b5602d has its CatchHandler @ 00b56527 */
          CEGUI::Window::setTooltipText(*(String **)(local_22c8 + 0x8dc8));
                    /* try { // try from 00b56036 to 00b5603a has its CatchHandler @ 00b564bc */
          CEGUI::String::~String(local_2138);
          if ((allocator *)(local_e8[0] + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_e8[0] + -8);
            iVar10 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar10 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
            }
          }
          if ((allocator *)(local_d8[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_d8[0] + -8);
            iVar10 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar10 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
            }
          }
          local_2290 = 0x20;
          local_2288 = 0;
          local_2278 = 0;
          local_2280 = 0;
          local_21f0 = (undefined4 *)0x0;
          local_2298 = 0;
          local_2270[0] = 0;
          CEGUI::String::grow((ulong)&local_2298);
          puVar16 = local_2270;
          if (0x20 < local_2290) {
            puVar16 = local_21f0;
          }
          local_2298 = 0;
          *puVar16 = 0;
          local_21e0 = 0x20;
          local_21d8 = 0;
          local_21c8 = 0;
          local_21d0 = 0;
          local_2140 = (uint *)0x0;
          local_21e8 = 0;
          local_21c0[0] = 0;
                    /* try { // try from 00b56153 to 00b56157 has its CatchHandler @ 00b56411 */
          CEGUI::String::grow((ulong)&local_21e8);
          puVar17 = local_21c0;
          if (0x20 < local_21e0) {
            puVar17 = local_2140;
          }
          pbVar12 = (byte *)0xfd0c0d;
          do {
            bVar5 = *pbVar12;
            pbVar12 = pbVar12 + 1;
            *puVar17 = (uint)bVar5;
            puVar17 = puVar17 + 1;
          } while (pbVar12 != (byte *)0xfd0c12);
          local_21e8 = 5;
          puVar17 = local_21ac;
          if (0x20 < local_21e0) {
            puVar17 = local_2140 + 5;
          }
          *puVar17 = 0;
                    /* try { // try from 00b561cf to 00b561d3 has its CatchHandler @ 00b564eb */
          CEGUI::PropertySet::setProperty(*(String **)(local_22c8 + 0x8dc8),(String *)&local_21e8);
                    /* try { // try from 00b561d7 to 00b561db has its CatchHandler @ 00b56411 */
          CEGUI::String::~String((String *)&local_21e8);
          CEGUI::String::~String((String *)&local_2298);
          *(CInventoryMenu **)(*(long *)(local_22c8 + 0x8dc8) + 0x1d8) = this + 0x9100;
        }
        else {
          puVar15 = (undefined8 *)CSkill::getSkillIcon(this_03);
          STRINGS::StringConvertToNarrow((STRINGS *)local_88,(wchar_t *)*puVar15);
                    /* try { // try from 00b55d27 to 00b55d3b has its CatchHandler @ 00b565c1 */
          CGameUI::getImageFromImageSet(*(CGameUI **)(this + 0x70),local_88[0]);
          CEGUI::PropertyHelper::imageToString(local_1f28);
          local_1fd0 = 0x20;
          local_1fc8 = 0;
          local_1fb8 = 0;
          local_1fc0 = 0;
          local_1f30 = (uint *)0x0;
          local_1fd8 = 0;
          local_1fb0[0] = 0;
                    /* try { // try from 00b55d97 to 00b55d9b has its CatchHandler @ 00b5659c */
          CEGUI::String::grow((ulong)&local_1fd8);
          puVar17 = local_1fb0;
          if (0x20 < local_1fd0) {
            puVar17 = local_1f30;
          }
          pbVar12 = (byte *)0xfd0c0d;
          do {
            bVar5 = *pbVar12;
            pbVar12 = pbVar12 + 1;
            *puVar17 = (uint)bVar5;
            puVar17 = puVar17 + 1;
          } while (pbVar12 != (byte *)0xfd0c12);
          local_1fd8 = 5;
          puVar17 = local_1f9c;
          if (0x20 < local_1fd0) {
            puVar17 = local_1f30 + 5;
          }
          *puVar17 = 0;
                    /* try { // try from 00b55e17 to 00b55e1b has its CatchHandler @ 00b56704 */
          CEGUI::PropertySet::setProperty(*(String **)(local_22c8 + 0x8dc8),(String *)&local_1fd8);
                    /* try { // try from 00b55e1f to 00b55e23 has its CatchHandler @ 00b5659c */
          CEGUI::String::~String((String *)&local_1fd8);
                    /* try { // try from 00b55e2c to 00b55e30 has its CatchHandler @ 00b565c1 */
          CEGUI::String::~String((String *)local_1f28);
          if ((allocator *)(local_88[0] + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_88[0] + -8);
            iVar10 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar10 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
            }
          }
          *(undefined8 *)(local_22c8 + 0x8de8) = *(undefined8 *)(this_03 + 0x150);
          *(CInventoryMenu **)(*(long *)(local_22c8 + 0x8dc8) + 0x1d8) =
               this + (ulong)uVar19 * 8 + 0x8de8;
                    /* try { // try from 00b55e8b to 00b55e8f has its CatchHandler @ 00b566d3 */
          std::wstring::wstring
                    ((wstring_conflict *)local_98,
                     (wstring_conflict *)&updateLayout()::g_RemoveASpell);
          wcslen(L"\n");
                    /* try { // try from 00b55ea5 to 00b55ea9 has its CatchHandler @ 00b566c3 */
          std::wstring::append((wchar_t *)local_98,0xfd0b48);
                    /* try { // try from 00b55eba to 00b55ebe has its CatchHandler @ 00b566be */
          std::operator+((wstring_conflict *)local_a8,(wstring_conflict *)local_98);
                    /* try { // try from 00b55ed7 to 00b55edb has its CatchHandler @ 00b566b9 */
          std::wstring::wstring((wstring_conflict *)local_b8,local_a8[0],local_39);
                    /* try { // try from 00b55eec to 00b55ef0 has its CatchHandler @ 00b566b4 */
          STRINGS::StringConvertToUTF8((wstring_conflict *)local_c8);
                    /* try { // try from 00b55f01 to 00b55f05 has its CatchHandler @ 00b566af */
          CEGUI::String::String(local_2088,local_c8[0]);
                    /* try { // try from 00b55f1a to 00b55f1e has its CatchHandler @ 00b56660 */
          CEGUI::Window::setTooltipText(*(String **)(local_22c8 + 0x8dc8));
                    /* try { // try from 00b55f27 to 00b55f2b has its CatchHandler @ 00b566af */
          CEGUI::String::~String(local_2088);
          if ((allocator *)(local_c8[0] + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_c8[0] + -8);
            iVar10 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar10 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
            }
          }
          if ((allocator *)(local_b8[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_b8[0] + -8);
            iVar10 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar10 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
            }
          }
          if ((allocator *)(local_a8[0] + -6) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            pwVar2 = local_a8[0] + -2;
            wVar4 = *pwVar2;
            *pwVar2 = *pwVar2 + L'\xffffffff';
            UNLOCK();
            if (wVar4 < L'\x01') {
              std::wstring::_Rep::_M_destroy((allocator *)(local_a8[0] + -6));
            }
          }
          if ((allocator *)(local_98[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_98[0] + -8);
            iVar10 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar10 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
            }
          }
        }
      }
      uVar19 = uVar19 + 1;
      local_22c8 = local_22c8 + 8;
    } while (uVar19 != 4);
    CEGUI::Window::moveToBack();
    CEGUI::Window::moveToFront();
    CEGUI::Window::moveToFront();
    CEGUI::Window::moveToFront();
    CEGUI::Window::moveToFront();
  }
  return;
}

/* address=00b569e0
   symbol=CInventoryMenu::createMenus */

/* WARNING: Removing unreachable block (ram,0x00b606de) */
/* WARNING: Removing unreachable block (ram,0x00b606bc) */
/* WARNING: Removing unreachable block (ram,0x00b6053f) */
/* WARNING: Removing unreachable block (ram,0x00b60608) */
/* WARNING: Removing unreachable block (ram,0x00b6054d) */
/* WARNING: Removing unreachable block (ram,0x00b5f817) */
/* WARNING: Removing unreachable block (ram,0x00b5f885) */
/* WARNING: Removing unreachable block (ram,0x00b5f95f) */
/* WARNING: Removing unreachable block (ram,0x00b5f319) */
/* WARNING: Removing unreachable block (ram,0x00b5f324) */
/* WARNING: Removing unreachable block (ram,0x00b5f771) */
/* WARNING: Removing unreachable block (ram,0x00b5fb15) */
/* WARNING: Removing unreachable block (ram,0x00b6030c) */
/* WARNING: Removing unreachable block (ram,0x00b5fec2) */
/* WARNING: Removing unreachable block (ram,0x00b6031a) */
/* WARNING: Removing unreachable block (ram,0x00b6038d) */
/* WARNING: Removing unreachable block (ram,0x00b601e9) */
/* WARNING: Removing unreachable block (ram,0x00b5fb02) */
/* WARNING: Removing unreachable block (ram,0x00b5f4f7) */
/* WARNING: Removing unreachable block (ram,0x00b5f77c) */
/* WARNING: Removing unreachable block (ram,0x00b5f9da) */
/* WARNING: Removing unreachable block (ram,0x00b5fca5) */
/* WARNING: Removing unreachable block (ram,0x00b5f9cf) */
/* WARNING: Removing unreachable block (ram,0x00b60405) */
/* WARNING: Removing unreachable block (ram,0x00b605a6) */
/* WARNING: Removing unreachable block (ram,0x00b60759) */
/* WARNING: Removing unreachable block (ram,0x00b5fa36) */
/* WARNING: Removing unreachable block (ram,0x00b5f951) */
/* WARNING: Removing unreachable block (ram,0x00b602ab) */
/* WARNING: Removing unreachable block (ram,0x00b60398) */
/* WARNING: Removing unreachable block (ram,0x00b5f6ae) */
/* WARNING: Removing unreachable block (ram,0x00b60468) */
/* WARNING: Removing unreachable block (ram,0x00b5f387) */
/* WARNING: Removing unreachable block (ram,0x00b5f3fb) */
/* WARNING: Removing unreachable block (ram,0x00b5f5b9) */
/* WARNING: Removing unreachable block (ram,0x00b5f463) */
/* WARNING: Removing unreachable block (ram,0x00b5f392) */
/* WARNING: Removing unreachable block (ram,0x00b5fc6e) */
/* WARNING: Removing unreachable block (ram,0x00b5f5ae) */
/* CInventoryMenu::createMenus() */

void __thiscall CInventoryMenu::createMenus(CInventoryMenu *this)

{
  int *piVar1;
  char cVar2;
  byte bVar3;
  code *pcVar4;
  undefined8 uVar5;
  BoundSlot *pBVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  CGenericModel *this_00;
  long lVar12;
  char *pcVar13;
  undefined8 uVar14;
  CFileSystem *this_01;
  Window *pWVar15;
  byte *pbVar16;
  String *pSVar17;
  char *pcVar18;
  long *plVar19;
  CInventoryMenu *pCVar20;
  UVector2 *pUVar21;
  undefined8 *puVar22;
  undefined4 *puVar23;
  length_error *plVar24;
  uint *puVar25;
  CRunicCore *this_02;
  ulong uVar26;
  uint uVar27;
  byte *pbVar28;
  ulong uVar29;
  char *pcVar30;
  undefined1 *puVar31;
  long lVar32;
  char *pcVar33;
  char *pcVar34;
  long lVar35;
  CInventoryMenu *pCVar36;
  bool bVar37;
  float fVar38;
  float fVar39;
  int local_44f8;
  CInventoryMenu *local_44d0;
  undefined8 local_44c8;
  ulong local_44c0;
  undefined8 local_44b8;
  undefined8 local_44b0;
  undefined8 local_44a8;
  uint local_44a0 [12];
  uint local_4470 [20];
  uint *local_4420;
  undefined8 local_4418;
  ulong local_4410;
  undefined8 local_4408;
  undefined8 local_4400;
  undefined8 local_43f8;
  uint local_43f0 [5];
  uint local_43dc [27];
  uint *local_4370;
  long local_4368;
  ulong local_4360;
  undefined8 local_4358;
  undefined8 local_4350;
  undefined8 local_4348;
  undefined4 local_4340 [32];
  undefined4 *local_42c0;
  undefined8 local_42b8;
  ulong local_42b0;
  undefined8 local_42a8;
  undefined8 local_42a0;
  undefined8 local_4298;
  undefined4 local_4290 [32];
  undefined4 *local_4210;
  long local_4208;
  ulong local_4200;
  undefined8 local_41f8;
  undefined8 local_41f0;
  undefined8 local_41e8;
  undefined4 local_41e0 [32];
  undefined4 *local_4160;
  long local_4158;
  ulong local_4150;
  undefined8 local_4148;
  undefined8 local_4140;
  undefined8 local_4138;
  uint local_4130 [32];
  uint *local_40b0;
  undefined8 local_40a8;
  ulong local_40a0;
  undefined8 local_4098;
  undefined8 local_4090;
  undefined8 local_4088;
  undefined4 local_4080 [32];
  undefined4 *local_4000;
  long local_3ff8;
  ulong local_3ff0;
  undefined8 local_3fe8;
  undefined8 local_3fe0;
  undefined8 local_3fd8;
  undefined4 local_3fd0 [32];
  undefined4 *local_3f50;
  long local_3f48;
  ulong local_3f40;
  undefined8 local_3f38;
  undefined8 local_3f30;
  undefined8 local_3f28;
  uint local_3f20 [32];
  uint *local_3ea0;
  undefined8 local_3e98;
  ulong local_3e90;
  undefined8 local_3e88;
  undefined8 local_3e80;
  undefined8 local_3e78;
  undefined4 local_3e70 [32];
  undefined4 *local_3df0;
  long local_3de8;
  ulong local_3de0;
  undefined8 local_3dd8;
  undefined8 local_3dd0;
  undefined8 local_3dc8;
  undefined4 local_3dc0 [32];
  undefined4 *local_3d40;
  long local_3d38;
  ulong local_3d30;
  undefined8 local_3d28;
  undefined8 local_3d20;
  undefined8 local_3d18;
  uint local_3d10 [32];
  uint *local_3c90;
  undefined8 local_3c88;
  ulong local_3c80;
  undefined8 local_3c78;
  undefined8 local_3c70;
  undefined8 local_3c68;
  uint local_3c60 [10];
  uint local_3c38 [22];
  uint *local_3be0;
  String local_3bd8 [176];
  undefined8 local_3b28;
  ulong local_3b20;
  undefined8 local_3b18;
  undefined8 local_3b10;
  undefined8 local_3b08;
  undefined4 local_3b00 [32];
  undefined4 *local_3a80;
  undefined8 local_3a78;
  ulong local_3a70;
  undefined8 local_3a68;
  undefined8 local_3a60;
  undefined8 local_3a58;
  uint local_3a50 [13];
  uint local_3a1c [19];
  uint *local_39d0;
  undefined8 local_39c8;
  ulong local_39c0;
  undefined8 local_39b8;
  undefined8 local_39b0;
  undefined8 local_39a8;
  uint local_39a0 [14];
  uint local_3968 [18];
  uint *local_3920;
  undefined8 local_3918;
  ulong local_3910;
  undefined8 local_3908;
  undefined8 local_3900;
  undefined8 local_38f8;
  uint local_38f0 [12];
  uint local_38c0 [20];
  uint *local_3870;
  undefined8 local_3868;
  ulong local_3860;
  undefined8 local_3858;
  undefined8 local_3850;
  undefined8 local_3848;
  uint local_3840 [18];
  uint local_37f8 [14];
  uint *local_37c0;
  undefined8 local_37b8;
  ulong local_37b0;
  undefined8 local_37a8;
  undefined8 local_37a0;
  undefined8 local_3798;
  uint local_3790 [5];
  uint local_377c [27];
  uint *local_3710;
  undefined8 local_3708;
  ulong local_3700;
  undefined8 local_36f8;
  undefined8 local_36f0;
  undefined8 local_36e8;
  undefined4 local_36e0 [32];
  undefined4 *local_3660;
  long local_3658;
  ulong local_3650;
  undefined8 local_3648;
  undefined8 local_3640;
  undefined8 local_3638;
  undefined4 local_3630 [32];
  undefined4 *local_35b0;
  long local_35a8;
  ulong local_35a0;
  undefined8 local_3598;
  undefined8 local_3590;
  undefined8 local_3588;
  uint local_3580 [32];
  uint *local_3500;
  long local_34f8;
  ulong local_34f0;
  undefined8 local_34e8;
  undefined8 local_34e0;
  undefined8 local_34d8;
  undefined4 local_34d0 [32];
  undefined4 *local_3450;
  undefined8 local_3448;
  ulong local_3440;
  undefined8 local_3438;
  undefined8 local_3430;
  undefined8 local_3428;
  uint local_3420 [9];
  uint local_33fc [23];
  uint *local_33a0;
  undefined8 local_3398;
  ulong local_3390;
  undefined8 local_3388;
  undefined8 local_3380;
  undefined8 local_3378;
  uint local_3370 [11];
  uint local_3344 [21];
  uint *local_32f0;
  undefined8 local_32e8;
  ulong local_32e0;
  undefined8 local_32d8;
  undefined8 local_32d0;
  undefined8 local_32c8;
  uint local_32c0 [14];
  uint local_3288 [18];
  uint *local_3240;
  long local_3238;
  ulong local_3230;
  undefined1 local_3210 [128];
  undefined1 *local_3190;
  undefined8 local_3188;
  ulong local_3180;
  undefined8 local_3178;
  undefined8 local_3170;
  undefined8 local_3168;
  uint local_3160 [13];
  uint local_312c [19];
  uint *local_30e0;
  long local_30d8;
  ulong local_30d0;
  undefined1 local_30b0 [128];
  undefined1 *local_3030;
  undefined8 local_3028;
  ulong local_3020;
  undefined8 local_3018;
  undefined8 local_3010;
  undefined8 local_3008;
  uint local_3000 [15];
  uint local_2fc4 [17];
  uint *local_2f80;
  undefined8 local_2f78;
  ulong local_2f70;
  undefined8 local_2f68;
  undefined8 local_2f60;
  undefined8 local_2f58;
  uint local_2f50 [7];
  uint local_2f34 [25];
  uint *local_2ed0;
  long local_2ec8;
  ulong local_2ec0;
  undefined1 local_2ea0 [128];
  undefined1 *local_2e20;
  undefined8 local_2e18;
  ulong local_2e10;
  undefined8 local_2e08;
  undefined8 local_2e00;
  undefined8 local_2df8;
  uint local_2df0 [13];
  uint local_2dbc [19];
  uint *local_2d70;
  long local_2d68;
  ulong local_2d60;
  undefined1 local_2d40 [128];
  undefined1 *local_2cc0;
  undefined8 local_2cb8;
  ulong local_2cb0;
  undefined8 local_2ca8;
  undefined8 local_2ca0;
  undefined8 local_2c98;
  uint local_2c90 [15];
  uint local_2c54 [17];
  uint *local_2c10;
  undefined8 local_2c08;
  ulong local_2c00;
  undefined8 local_2bf8;
  undefined8 local_2bf0;
  undefined8 local_2be8;
  uint local_2be0 [8];
  uint local_2bc0 [24];
  uint *local_2b60;
  long local_2b58;
  ulong local_2b50;
  undefined1 local_2b30 [128];
  undefined1 *local_2ab0;
  undefined8 local_2aa8;
  ulong local_2aa0;
  undefined8 local_2a98;
  undefined8 local_2a90;
  undefined8 local_2a88;
  uint local_2a80 [13];
  uint local_2a4c [19];
  uint *local_2a00;
  long local_29f8;
  ulong local_29f0;
  undefined1 local_29d0 [128];
  undefined1 *local_2950;
  undefined8 local_2948;
  ulong local_2940;
  undefined8 local_2938;
  undefined8 local_2930;
  undefined8 local_2928;
  uint local_2920 [15];
  uint local_28e4 [17];
  uint *local_28a0;
  undefined8 local_2898;
  ulong local_2890;
  undefined8 local_2888;
  undefined8 local_2880;
  undefined8 local_2878;
  uint local_2870 [11];
  uint local_2844 [21];
  uint *local_27f0;
  undefined8 local_27e8;
  ulong local_27e0;
  undefined8 local_27d8;
  undefined8 local_27d0;
  undefined8 local_27c8;
  undefined4 local_27c0 [32];
  undefined4 *local_2740;
  long local_2738;
  ulong local_2730;
  undefined8 local_2728;
  undefined8 local_2720;
  undefined8 local_2718;
  undefined4 local_2710 [32];
  undefined4 *local_2690;
  long local_2688;
  ulong local_2680;
  undefined8 local_2678;
  undefined8 local_2670;
  undefined8 local_2668;
  uint local_2660 [32];
  uint *local_25e0;
  undefined8 local_25d8;
  ulong local_25d0;
  undefined8 local_25c8;
  undefined8 local_25c0;
  undefined8 local_25b8;
  undefined4 local_25b0 [32];
  undefined4 *local_2530;
  long local_2528;
  ulong local_2520;
  undefined8 local_2518;
  undefined8 local_2510;
  undefined8 local_2508;
  undefined4 local_2500 [32];
  undefined4 *local_2480;
  long local_2478;
  ulong local_2470;
  undefined8 local_2468;
  undefined8 local_2460;
  undefined8 local_2458;
  uint local_2450 [32];
  uint *local_23d0;
  undefined8 local_23c8;
  ulong local_23c0;
  undefined8 local_23b8;
  undefined8 local_23b0;
  undefined8 local_23a8;
  undefined4 local_23a0 [32];
  undefined4 *local_2320;
  long local_2318;
  ulong local_2310;
  undefined8 local_2308;
  undefined8 local_2300;
  undefined8 local_22f8;
  undefined4 local_22f0 [32];
  undefined4 *local_2270;
  long local_2268;
  ulong local_2260;
  undefined8 local_2258;
  undefined8 local_2250;
  undefined8 local_2248;
  uint local_2240 [32];
  uint *local_21c0;
  long local_21b8;
  ulong local_21b0;
  undefined1 auStack_2190 [128];
  undefined1 *local_2110;
  undefined8 local_2108;
  ulong local_2100;
  undefined8 local_20f8;
  undefined8 local_20f0;
  undefined8 local_20e8;
  uint local_20e0 [5];
  uint local_20cc [27];
  uint *local_2060;
  long local_2058;
  ulong local_2050;
  undefined8 local_2048;
  undefined8 local_2040;
  undefined8 local_2038;
  undefined4 local_2030 [32];
  undefined4 *local_1fb0;
  undefined8 local_1fa8;
  ulong local_1fa0;
  undefined8 local_1f98;
  undefined8 local_1f90;
  undefined8 local_1f88;
  uint local_1f80 [11];
  uint local_1f54 [21];
  uint *local_1f00;
  undefined8 local_1ef8;
  ulong local_1ef0;
  undefined8 local_1ee8;
  undefined8 local_1ee0;
  undefined8 local_1ed8;
  uint local_1ed0 [10];
  uint local_1ea8 [22];
  uint *local_1e50;
  undefined8 local_1e48;
  ulong local_1e40;
  undefined8 local_1e38;
  undefined8 local_1e30;
  undefined8 local_1e28;
  uint local_1e20 [14];
  uint local_1de8 [18];
  uint *local_1da0;
  undefined8 local_1d98;
  ulong local_1d90;
  undefined8 local_1d88;
  undefined8 local_1d80;
  undefined8 local_1d78;
  uint local_1d70 [5];
  uint local_1d5c [27];
  uint *local_1cf0;
  undefined8 local_1ce8;
  ulong local_1ce0;
  undefined8 local_1cd8;
  undefined8 local_1cd0;
  undefined8 local_1cc8;
  uint local_1cc0 [8];
  uint local_1ca0 [24];
  uint *local_1c40;
  undefined8 local_1c38;
  ulong local_1c30;
  undefined8 local_1c28;
  undefined8 local_1c20;
  undefined8 local_1c18;
  uint local_1c10 [5];
  uint local_1bfc [27];
  uint *local_1b90;
  undefined8 local_1b88;
  ulong local_1b80;
  undefined8 local_1b78;
  undefined8 local_1b70;
  undefined8 local_1b68;
  uint local_1b60 [11];
  uint local_1b34 [21];
  uint *local_1ae0;
  undefined8 local_1ad8;
  ulong local_1ad0;
  undefined8 local_1ac8;
  undefined8 local_1ac0;
  undefined8 local_1ab8;
  undefined4 local_1ab0 [32];
  undefined4 *local_1a30;
  long local_1a28;
  ulong local_1a20;
  undefined8 local_1a18;
  undefined8 local_1a10;
  undefined8 local_1a08;
  uint local_1a00 [32];
  uint *local_1980;
  long local_1978;
  ulong local_1970;
  undefined8 local_1968;
  undefined8 local_1960;
  undefined8 local_1958;
  uint local_1950 [32];
  uint *local_18d0;
  undefined8 local_18c8;
  ulong local_18c0;
  undefined8 local_18b8;
  undefined8 local_18b0;
  undefined8 local_18a8;
  uint local_18a0 [5];
  uint local_188c [27];
  uint *local_1820;
  undefined8 local_1818;
  ulong local_1810;
  undefined8 local_1808;
  undefined8 local_1800;
  undefined8 local_17f8;
  uint local_17f0 [11];
  uint local_17c4 [21];
  uint *local_1770;
  undefined8 local_1768;
  ulong local_1760;
  undefined8 local_1758;
  undefined8 local_1750;
  undefined8 local_1748;
  undefined4 local_1740 [32];
  undefined4 *local_16c0;
  String local_16b8 [176];
  long local_1608;
  ulong local_1600;
  undefined8 local_15f8;
  undefined8 local_15f0;
  undefined8 local_15e8;
  uint local_15e0 [32];
  uint *local_1560;
  undefined8 local_1558;
  ulong local_1550;
  undefined8 local_1548;
  undefined8 local_1540;
  undefined8 local_1538;
  uint local_1530 [5];
  uint local_151c [27];
  uint *local_14b0;
  undefined8 local_14a8;
  ulong local_14a0;
  undefined8 local_1498;
  undefined8 local_1490;
  undefined8 local_1488;
  uint local_1480 [11];
  uint local_1454 [21];
  uint *local_1400;
  undefined8 local_13f8;
  ulong local_13f0;
  undefined8 local_13e8;
  undefined8 local_13e0;
  undefined8 local_13d8;
  undefined4 local_13d0 [32];
  undefined4 *local_1350;
  String local_1348 [176];
  String local_1298 [176];
  undefined8 local_11e8;
  ulong local_11e0;
  undefined8 local_11d8;
  undefined8 local_11d0;
  undefined8 local_11c8;
  uint local_11c0 [5];
  uint local_11ac [27];
  uint *local_1140;
  undefined8 local_1138;
  ulong local_1130;
  undefined8 local_1128;
  undefined8 local_1120;
  undefined8 local_1118;
  uint local_1110 [11];
  uint local_10e4 [21];
  uint *local_1090;
  undefined8 local_1088;
  ulong local_1080;
  undefined8 local_1078;
  undefined8 local_1070;
  undefined8 local_1068;
  uint local_1060 [8];
  uint local_1040 [24];
  uint *local_fe0;
  undefined8 local_fd8;
  ulong local_fd0;
  undefined8 local_fc8;
  undefined8 local_fc0;
  undefined8 local_fb8;
  uint local_fb0 [5];
  uint local_f9c [27];
  uint *local_f30;
  undefined8 local_f28;
  ulong local_f20;
  undefined8 local_f18;
  undefined8 local_f10;
  undefined8 local_f08;
  uint local_f00 [11];
  uint local_ed4 [21];
  uint *local_e80;
  undefined8 local_e78;
  ulong local_e70;
  undefined8 local_e68;
  undefined8 local_e60;
  undefined8 local_e58;
  uint local_e50 [11];
  uint local_e24 [21];
  uint *local_dd0;
  undefined8 local_dc8;
  ulong local_dc0;
  undefined8 local_db8;
  undefined8 local_db0;
  undefined8 local_da8;
  uint local_da0 [5];
  uint local_d8c [27];
  uint *local_d20;
  undefined8 local_d18;
  ulong local_d10;
  undefined8 local_d08;
  undefined8 local_d00;
  undefined8 local_cf8;
  uint local_cf0 [11];
  uint local_cc4 [21];
  uint *local_c70;
  undefined8 local_c68;
  ulong local_c60;
  undefined8 local_c58;
  undefined8 local_c50;
  undefined8 local_c48;
  uint local_c40 [7];
  uint local_c24 [25];
  uint *local_bc0;
  long local_bb8;
  ulong local_bb0;
  undefined8 local_ba8;
  undefined8 local_ba0;
  undefined8 local_b98;
  undefined4 local_b90 [32];
  undefined4 *local_b10;
  undefined8 local_b08;
  ulong local_b00;
  undefined8 local_af8;
  undefined8 local_af0;
  undefined8 local_ae8;
  uint local_ae0 [5];
  uint local_acc [27];
  uint *local_a60;
  undefined8 local_a58;
  ulong local_a50;
  undefined8 local_a48;
  undefined8 local_a40;
  undefined8 local_a38;
  uint local_a30 [11];
  uint local_a04 [21];
  uint *local_9b0;
  undefined8 local_9a8;
  ulong local_9a0;
  undefined8 local_998;
  undefined8 local_990;
  undefined8 local_988;
  undefined4 local_980 [32];
  undefined4 *local_900;
  long local_8f8;
  ulong local_8f0;
  undefined8 local_8e8;
  undefined8 local_8e0;
  undefined8 local_8d8;
  uint local_8d0 [32];
  uint *local_850;
  long local_848;
  ulong local_840;
  undefined8 local_838;
  undefined8 local_830;
  undefined8 local_828;
  uint local_820 [32];
  uint *local_7a0;
  long local_798;
  ulong local_790;
  undefined8 local_788;
  undefined8 local_780;
  undefined8 local_778;
  uint local_770 [32];
  uint *local_6f0;
  undefined1 *local_6e8;
  long local_6e0;
  long local_6d8;
  undefined4 local_6d0;
  undefined4 local_6cc;
  undefined1 *local_6c8;
  undefined1 local_6c0;
  undefined4 local_6b8;
  undefined4 local_6b4;
  undefined4 local_6b0;
  undefined4 local_6ac;
  undefined4 local_6a8;
  undefined4 local_6a4;
  undefined4 local_6a0;
  void *local_698;
  undefined1 local_688 [32];
  BoundSlot *local_668;
  int *local_660;
  BoundSlot *local_658;
  int *local_650;
  BoundSlot *local_648;
  int *local_640;
  BoundSlot *local_638;
  int *local_630;
  undefined8 local_5f8;
  undefined8 local_5f0;
  BoundSlot *local_5d8;
  int *local_5d0;
  BoundSlot *local_5c8;
  int *local_5c0;
  BoundSlot *local_5b8;
  int *local_5b0;
  BoundSlot *local_5a8;
  int *local_5a0;
  BoundSlot *local_568;
  int *local_560;
  BoundSlot *local_558;
  int *local_550;
  BoundSlot *local_548;
  int *local_540;
  BoundSlot *local_538;
  int *local_530;
  BoundSlot *local_528;
  int *local_520;
  BoundSlot *local_518;
  int *local_510;
  BoundSlot *local_508;
  int *local_500;
  BoundSlot *local_4f8;
  int *local_4f0;
  BoundSlot *local_4e8;
  int *local_4e0;
  BoundSlot *local_4d8;
  int *local_4d0;
  BoundSlot *local_4c8;
  int *local_4c0;
  BoundSlot *local_4b8;
  int *local_4b0;
  undefined4 local_4a8;
  undefined4 local_4a4;
  undefined4 local_4a0;
  undefined4 local_49c;
  undefined4 local_488;
  undefined4 local_484;
  undefined4 local_480;
  undefined4 local_47c;
  undefined4 local_468;
  undefined4 local_464;
  undefined4 local_460;
  undefined4 local_45c;
  BoundSlot *local_448;
  int *local_440;
  undefined4 local_438;
  undefined4 local_434;
  undefined4 local_430;
  undefined4 local_42c;
  undefined4 local_428;
  undefined4 local_424;
  undefined4 local_420;
  undefined4 local_41c;
  undefined4 local_418;
  undefined4 local_414;
  undefined4 local_410;
  undefined4 local_408;
  undefined4 local_404;
  undefined4 local_400;
  long local_3f8 [2];
  long local_3e8 [2];
  long local_3d8 [2];
  long local_3c8 [2];
  long local_3b8 [2];
  long local_3a8 [2];
  long local_398 [2];
  long local_388 [2];
  long local_378 [2];
  long local_368 [2];
  long local_358 [2];
  long local_348 [2];
  long local_338 [2];
  long local_328 [2];
  long local_318 [2];
  long local_308 [2];
  undefined8 *local_2f8 [2];
  undefined8 *local_2e8 [2];
  undefined8 *local_2d8 [2];
  undefined8 *local_2c8 [2];
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
  undefined8 *local_218 [2];
  undefined8 *local_208 [2];
  undefined8 *local_1f8 [2];
  undefined8 *local_1e8 [2];
  long local_1d8 [2];
  long local_1c8 [2];
  long local_1b8 [2];
  long local_1a8 [2];
  long local_198 [2];
  long local_188 [2];
  long local_178 [2];
  long local_168 [2];
  undefined8 *local_158 [2];
  undefined8 *local_148 [2];
  undefined8 *local_138 [2];
  undefined8 *local_128 [2];
  undefined8 *local_118 [2];
  undefined8 *local_108 [2];
  undefined8 *local_f8 [2];
  undefined8 *local_e8 [2];
  undefined8 *local_d8 [2];
  undefined8 *local_c8 [2];
  undefined8 *local_b8 [2];
  undefined8 *local_a8 [2];
  long local_98 [2];
  undefined8 *local_88 [3];
  allocator local_6c [4];
  allocator local_68 [4];
  allocator local_64 [2];
  allocator local_62 [4];
  allocator local_5e [6];
  allocator local_58 [4];
  allocator local_54 [4];
  allocator local_50 [2];
  allocator local_4e [2];
  allocator local_4c [2];
  allocator local_4a [3];
  allocator local_47 [2];
  allocator local_45 [2];
  allocator local_43;
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

  iVar7 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0x68),KSETTINGS_RES_WIDTH);
  iVar8 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0x68),KSETTINGS_RES_HEIGHT)
  ;
  this_00 = (CGenericModel *)
            CResourceManager::createGenericModel
                      (*(CResourceManager **)(this + 0x9178),*(SceneManager **)(this + 0x9138),
                       L"media/ui/models/inventory/inventory.mesh",L"",false,false,false);
  *(CGenericModel **)(this + 0x9170) = this_00;
  CGenericModel::generateExtremes(this_00,5,true);
  local_698 = (void *)0x0;
  local_6a0 = 1;
  local_6b8 = 0xc7c35000;
  local_6b4 = 0xc7c35000;
  local_6b0 = 0xc7c35000;
  local_6ac = 0x47c35000;
  local_6a8 = 0x47c35000;
  local_6a4 = 0x47c35000;
                    /* try { // try from 00b56acd to 00b56c4a has its CatchHandler @ 00b60307 */
  lVar12 = Ogre::Entity::getMesh();
  Ogre::Mesh::_setBounds(*(AxisAlignedBox **)(lVar12 + 8),SUB81(&local_6b8,0));
  fVar38 = (float)iVar8 / DAT_00fc6774;
  pcVar4 = *(code **)(**(long **)(this + 0x9170) + 0x58);
  fVar39 = (float)CDynamicPropertyFile::GetFloat
                            (*(CDynamicPropertyFile **)(this + 0x68),KSETTINGS_YRATIO);
  (*pcVar4)(DAT_00fa4810 * (((float)iVar7 - fVar38) / fVar39),0,*(undefined8 *)(this + 0x9170));
  (**(code **)(**(long **)(this + 0x9170) + 0x50))(*(long **)(this + 0x9170),0);
  pcVar30 = (char *)0x0;
  pcVar33 = "UIIcons";
  local_790 = 0x20;
  local_788 = 0;
  pcVar34 = "UIIcons";
  local_778 = 0;
  local_780 = 0;
  local_6f0 = (uint *)0x0;
  local_798 = 0;
  local_770[0] = 0;
  cVar2 = s_UIIcons_00fe49dd[0];
  while (pcVar34 = pcVar34 + 1, cVar2 != '\0') {
    pcVar30 = pcVar34 + -0xfe49dd;
    cVar2 = *pcVar34;
  }
  if (pcVar30 == CEGUI::String::npos) {
                    /* try { // try from 00b5e7de to 00b5e7e2 has its CatchHandler @ 00b60704 */
    std::string::string((string *)local_328,"Length for utf8 encoded string can not be \'npos\'",
                        &local_43);
    plVar24 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00b5e7f6 to 00b5e7fa has its CatchHandler @ 00b606ec */
    std::length_error::length_error(plVar24,(string *)local_328);
    if ((allocator *)(local_328[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_328[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_328[0] + -0x18));
      }
    }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00b5e821 to 00b5e825 has its CatchHandler @ 00b60307 */
    __cxa_throw(plVar24,&std::length_error::typeinfo,std::length_error::~length_error);
  }
  lVar12 = 0;
  pcVar34 = pcVar30;
  pbVar16 = (byte *)"UIIcons";
  while (pcVar34 != (char *)0x0) {
    bVar3 = *pbVar16;
    pcVar13 = pcVar34 + -1;
    pbVar28 = pbVar16 + 1;
    if ((char)bVar3 < '\0') {
      if (bVar3 < 0xe0) {
        pcVar13 = pcVar34 + -2;
        pbVar28 = pbVar16 + 2;
      }
      else if (bVar3 < 0xf0) {
        pcVar13 = pcVar34 + -3;
        pbVar28 = pbVar16 + 3;
      }
      else {
        pcVar13 = pcVar34 + -3;
        pbVar28 = pbVar16 + 4;
      }
    }
    lVar12 = lVar12 + 1;
    pcVar34 = pcVar13;
    pbVar16 = pbVar28;
  }
  CEGUI::String::grow((ulong)&local_798);
  if (local_790 < 0x21) {
    puVar25 = local_770;
    if (pcVar30 == (char *)0x0) goto LAB_00b56ea1;
LAB_00b56c6a:
    bVar37 = local_790 != 0;
LAB_00b56c70:
    if (bVar37) {
      pcVar34 = (char *)0x0;
      uVar10 = 0;
      uVar26 = local_790;
      do {
        bVar3 = pcVar34[0xfe49dd];
        uVar11 = (uint)bVar3;
        uVar9 = uVar10 + 1;
        if ((char)bVar3 < '\0') {
          uVar11 = (uint)bVar3;
          if (0xdf < bVar3) {
            if (bVar3 < 0xf0) {
              uVar29 = (ulong)uVar9;
              uVar9 = uVar10 + 3;
              uVar11 = (byte)"UIIcons"[uVar10 + 2] & 0x3f | (uVar11 & 0xf) << 0xc |
                       ((byte)"UIIcons"[uVar29] & 0x3f) << 6;
            }
            else {
              uVar29 = (ulong)uVar9;
              uVar9 = uVar10 + 4;
              uVar11 = ((byte)"UIIcons"[uVar29] & 0x3f) << 0xc | (byte)"UIIcons"[uVar10 + 3] & 0x3f
                       | (uVar11 & 7) << 0x12 | ((byte)"UIIcons"[uVar10 + 2] & 0x3f) << 6;
            }
            goto LAB_00b56c83;
          }
          uVar10 = uVar10 + 2;
          *puVar25 = (byte)"UIIcons"[uVar9] & 0x3f | (uVar11 & 0x1f) << 6;
        }
        else {
LAB_00b56c83:
          *puVar25 = uVar11;
          uVar10 = uVar9;
        }
        pcVar34 = (char *)(ulong)uVar10;
        if ((pcVar30 <= pcVar34) || (uVar26 = uVar26 - 1, uVar26 == 0)) break;
        puVar25 = puVar25 + 1;
      } while( true );
    }
  }
  else {
    puVar25 = local_6f0;
    if (pcVar30 != (char *)0x0) goto LAB_00b56c6a;
LAB_00b56ea1:
    if (s_UIIcons_00fe49dd[0] != '\0') {
      do {
        pcVar33 = pcVar33 + 1;
        pcVar30 = pcVar33 + -0xfe49dd;
      } while (*pcVar33 != '\0');
      bVar37 = pcVar30 != (char *)0x0 && local_790 != 0;
      goto LAB_00b56c70;
    }
  }
  puVar25 = local_770;
  if (0x20 < local_790) {
    puVar25 = local_6f0;
  }
  puVar25[lVar12] = 0;
  local_798 = lVar12;
                    /* try { // try from 00b56d11 to 00b56d15 has its CatchHandler @ 00b6026a */
  uVar14 = CEGUI::ImagesetManager::getImageset
                     (CEGUI::Singleton<CEGUI::ImagesetManager>::ms_Singleton);
  *(undefined8 *)(this + 0x1cf8) = uVar14;
                    /* try { // try from 00b56d20 to 00b56d86 has its CatchHandler @ 00b60307 */
  CEGUI::String::~String((String *)&local_798);
  local_9a0 = 0x20;
  local_998 = 0;
  local_988 = 0;
  local_990 = 0;
  local_900 = (undefined4 *)0x0;
  local_9a8 = 0;
  local_980[0] = 0;
  CEGUI::String::grow((ulong)&local_9a8);
  local_9a8 = 0;
  puVar23 = local_900;
  if (local_9a0 < 0x21) {
    puVar23 = local_980;
  }
  *puVar23 = 0;
  pcVar33 = (char *)0x0;
  pcVar34 = "InventorySheet";
  local_8f0 = 0x20;
  local_8e8 = 0;
  local_8d8 = 0;
  local_8e0 = 0;
  pcVar30 = "InventorySheet";
  local_850 = (uint *)0x0;
  local_8f8 = 0;
  local_8d0[0] = 0;
  cVar2 = s_InventorySheet_00fef826[0];
  while (pcVar30 = pcVar30 + 1, cVar2 != '\0') {
    pcVar33 = pcVar30 + -0xfef826;
    cVar2 = *pcVar30;
  }
  if (pcVar33 == CEGUI::String::npos) {
                    /* try { // try from 00b5e8a0 to 00b5e8a4 has its CatchHandler @ 00b60672 */
    std::string::string((string *)local_338,"Length for utf8 encoded string can not be \'npos\'",
                        local_45);
    plVar24 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00b5e8b8 to 00b5e8bc has its CatchHandler @ 00b606a4 */
    std::length_error::length_error(plVar24,(string *)local_338);
    if ((allocator *)(local_338[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_338[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_338[0] + -0x18));
      }
    }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00b5e8e3 to 00b5e8e7 has its CatchHandler @ 00b6021a */
    __cxa_throw(plVar24,&std::length_error::typeinfo,std::length_error::~length_error);
  }
  lVar12 = 0;
  pcVar30 = pcVar33;
  pbVar16 = (byte *)"InventorySheet";
  while (pcVar30 != (char *)0x0) {
    bVar3 = *pbVar16;
    pcVar13 = pcVar30 + -1;
    pbVar28 = pbVar16 + 1;
    if ((char)bVar3 < '\0') {
      if (bVar3 < 0xe0) {
        pcVar13 = pcVar30 + -2;
        pbVar28 = pbVar16 + 2;
      }
      else if (bVar3 < 0xf0) {
        pcVar13 = pcVar30 + -3;
        pbVar28 = pbVar16 + 3;
      }
      else {
        pcVar13 = pcVar30 + -3;
        pbVar28 = pbVar16 + 4;
      }
    }
    lVar12 = lVar12 + 1;
    pcVar30 = pcVar13;
    pbVar16 = pbVar28;
  }
                    /* try { // try from 00b56f4e to 00b56f52 has its CatchHandler @ 00b6021a */
  CEGUI::String::grow((ulong)&local_8f8);
  puVar25 = local_8d0;
  if (0x20 < local_8f0) {
    puVar25 = local_850;
  }
  if (pcVar33 == (char *)0x0) {
    if (s_InventorySheet_00fef826[0] != '\0') {
      do {
        pcVar34 = pcVar34 + 1;
        pcVar33 = pcVar34 + -0xfef826;
      } while (*pcVar34 != '\0');
      bVar37 = pcVar33 != (char *)0x0 && local_8f0 != 0;
      goto LAB_00b56f7c;
    }
  }
  else {
    bVar37 = local_8f0 != 0;
LAB_00b56f7c:
    if (bVar37) {
      pcVar34 = (char *)0x0;
      uVar10 = 0;
      uVar26 = local_8f0;
      do {
        bVar3 = pcVar34[0xfef826];
        uVar11 = (uint)bVar3;
        uVar9 = uVar10 + 1;
        if ((char)bVar3 < '\0') {
          uVar11 = (uint)bVar3;
          if (0xdf < bVar3) {
            if (bVar3 < 0xf0) {
              uVar29 = (ulong)uVar9;
              uVar9 = uVar10 + 3;
              uVar11 = (byte)"InventorySheet"[uVar10 + 2] & 0x3f | (uVar11 & 0xf) << 0xc |
                       ((byte)"InventorySheet"[uVar29] & 0x3f) << 6;
            }
            else {
              uVar29 = (ulong)uVar9;
              uVar9 = uVar10 + 4;
              uVar11 = ((byte)"InventorySheet"[uVar29] & 0x3f) << 0xc |
                       (byte)"InventorySheet"[uVar10 + 3] & 0x3f | (uVar11 & 7) << 0x12 |
                       ((byte)"InventorySheet"[uVar10 + 2] & 0x3f) << 6;
            }
            goto LAB_00b56f93;
          }
          uVar10 = uVar10 + 2;
          *puVar25 = (byte)"InventorySheet"[uVar9] & 0x3f | (uVar11 & 0x1f) << 6;
        }
        else {
LAB_00b56f93:
          *puVar25 = uVar11;
          uVar10 = uVar9;
        }
        pcVar34 = (char *)(ulong)uVar10;
        if ((pcVar33 <= pcVar34) || (uVar26 = uVar26 - 1, uVar26 == 0)) break;
        puVar25 = puVar25 + 1;
      } while( true );
    }
  }
  puVar25 = local_8d0;
  if (0x20 < local_8f0) {
    puVar25 = local_850;
  }
  puVar25[lVar12] = 0;
  pcVar30 = (char *)0x0;
  pcVar33 = "DefaultWindow";
  local_840 = 0x20;
  local_838 = 0;
  local_828 = 0;
  local_830 = 0;
  pcVar34 = "DefaultWindow";
  local_7a0 = (uint *)0x0;
  local_848 = 0;
  local_820[0] = 0;
  cVar2 = s_DefaultWindow_00fe499d[0];
  while (pcVar34 = pcVar34 + 1, cVar2 != '\0') {
    pcVar30 = pcVar34 + -0xfe499d;
    cVar2 = *pcVar34;
  }
  local_8f8 = lVar12;
  if (pcVar30 == CEGUI::String::npos) {
                    /* try { // try from 00b5e9bd to 00b5e9c1 has its CatchHandler @ 00b606d9 */
    std::string::string((string *)local_348,"Length for utf8 encoded string can not be \'npos\'",
                        local_47);
    plVar24 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00b5e9d5 to 00b5e9d9 has its CatchHandler @ 00b6065a */
    std::length_error::length_error(plVar24,(string *)local_348);
    if ((allocator *)(local_348[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_348[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_348[0] + -0x18));
      }
    }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00b5ea00 to 00b5ea04 has its CatchHandler @ 00b5fe96 */
    __cxa_throw(plVar24,&std::length_error::typeinfo,std::length_error::~length_error);
  }
  lVar12 = 0;
  pcVar34 = pcVar30;
  pbVar16 = (byte *)"DefaultWindow";
  while (pcVar34 != (char *)0x0) {
    bVar3 = *pbVar16;
    pcVar13 = pcVar34 + -1;
    pbVar28 = pbVar16 + 1;
    if ((char)bVar3 < '\0') {
      if (bVar3 < 0xe0) {
        pcVar13 = pcVar34 + -2;
        pbVar28 = pbVar16 + 2;
      }
      else if (bVar3 < 0xf0) {
        pcVar13 = pcVar34 + -3;
        pbVar28 = pbVar16 + 3;
      }
      else {
        pcVar13 = pcVar34 + -3;
        pbVar28 = pbVar16 + 4;
      }
    }
    lVar12 = lVar12 + 1;
    pcVar34 = pcVar13;
    pbVar16 = pbVar28;
  }
                    /* try { // try from 00b5714e to 00b57152 has its CatchHandler @ 00b5fe96 */
  CEGUI::String::grow((ulong)&local_848);
  puVar25 = local_820;
  if (0x20 < local_840) {
    puVar25 = local_7a0;
  }
  if (pcVar30 == (char *)0x0) {
    pcVar34 = "DefaultWindow";
    if (s_DefaultWindow_00fe499d[0] != '\0') {
      do {
        pcVar34 = pcVar34 + 1;
        pcVar30 = pcVar34 + -0xfe499d;
      } while (*pcVar34 != '\0');
      bVar37 = pcVar30 != (char *)0x0 && local_840 != 0;
      goto LAB_00b5717c;
    }
  }
  else {
    bVar37 = local_840 != 0;
LAB_00b5717c:
    if (bVar37) {
      pcVar34 = (char *)0x0;
      uVar10 = 0;
      uVar26 = local_840;
      do {
        bVar3 = pcVar34[0xfe499d];
        uVar11 = (uint)bVar3;
        uVar9 = uVar10 + 1;
        if ((char)bVar3 < '\0') {
          uVar11 = (uint)bVar3;
          if (0xdf < bVar3) {
            if (bVar3 < 0xf0) {
              uVar29 = (ulong)uVar9;
              uVar9 = uVar10 + 3;
              uVar11 = (byte)"DefaultWindow"[uVar10 + 2] & 0x3f | (uVar11 & 0xf) << 0xc |
                       ((byte)"DefaultWindow"[uVar29] & 0x3f) << 6;
            }
            else {
              uVar29 = (ulong)uVar9;
              uVar9 = uVar10 + 4;
              uVar11 = ((byte)"DefaultWindow"[uVar29] & 0x3f) << 0xc |
                       (byte)"DefaultWindow"[uVar10 + 3] & 0x3f | (uVar11 & 7) << 0x12 |
                       ((byte)"DefaultWindow"[uVar10 + 2] & 0x3f) << 6;
            }
            goto LAB_00b57193;
          }
          uVar10 = uVar10 + 2;
          *puVar25 = (byte)"DefaultWindow"[uVar9] & 0x3f | (uVar11 & 0x1f) << 6;
        }
        else {
LAB_00b57193:
          *puVar25 = uVar11;
          uVar10 = uVar9;
        }
        pcVar34 = (char *)(ulong)uVar10;
        if ((pcVar30 <= pcVar34) || (uVar26 = uVar26 - 1, uVar26 == 0)) break;
        puVar25 = puVar25 + 1;
      } while( true );
    }
  }
  puVar25 = local_820;
  if (0x20 < local_840) {
    puVar25 = local_7a0;
  }
  puVar25[lVar12] = 0;
  local_848 = lVar12;
                    /* try { // try from 00b5722c to 00b57230 has its CatchHandler @ 00b5feb3 */
  uVar14 = CEGUI::WindowManager::createWindow
                     (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,(String *)&local_848,
                      (String *)&local_8f8);
  *(undefined8 *)(this + 0x20) = uVar14;
                    /* try { // try from 00b57238 to 00b5723c has its CatchHandler @ 00b5fe96 */
  CEGUI::String::~String((String *)&local_848);
                    /* try { // try from 00b57240 to 00b57244 has its CatchHandler @ 00b6021a */
  CEGUI::String::~String((String *)&local_8f8);
                    /* try { // try from 00b5724d to 00b57251 has its CatchHandler @ 00b60307 */
  CEGUI::String::~String((String *)&local_9a8);
  local_424 = 0;
  local_428 = 0x3f800000;
  local_41c = 0;
  local_420 = 0x3f800000;
                    /* try { // try from 00b5728a to 00b5728e has its CatchHandler @ 00b5fecd */
  CEGUI::Window::setSize(*(UVector2 **)(this + 0x20));
  local_b00 = 0x20;
  local_af8 = 0;
  local_ae8 = 0;
  local_af0 = 0;
  local_a60 = (uint *)0x0;
  local_b08 = 0;
  local_ae0[0] = 0;
                    /* try { // try from 00b572f2 to 00b572f6 has its CatchHandler @ 00b60307 */
  CEGUI::String::grow((ulong)&local_b08);
  puVar25 = local_ae0;
  if (0x20 < local_b00) {
    puVar25 = local_a60;
  }
  pcVar34 = "False";
  do {
    bVar3 = *pcVar34;
    pcVar34 = pcVar34 + 1;
    *puVar25 = (uint)bVar3;
    puVar25 = puVar25 + 1;
  } while ((byte *)pcVar34 != (byte *)0xfe603f);
  local_b08 = 5;
  puVar25 = local_acc;
  if (0x20 < local_b00) {
    puVar25 = local_a60 + 5;
  }
  *puVar25 = 0;
  local_a50 = 0x20;
  local_a48 = 0;
  local_a38 = 0;
  local_a40 = 0;
  local_9b0 = (uint *)0x0;
  local_a58 = 0;
  local_a30[0] = 0;
                    /* try { // try from 00b573bd to 00b573c1 has its CatchHandler @ 00b5fed2 */
  CEGUI::String::grow((ulong)&local_a58);
  puVar25 = local_a30;
  if (0x20 < local_a50) {
    puVar25 = local_9b0;
  }
  pcVar34 = "RiseOnClick";
  do {
    bVar3 = *pcVar34;
    pcVar34 = pcVar34 + 1;
    *puVar25 = (uint)bVar3;
    puVar25 = puVar25 + 1;
  } while ((byte *)pcVar34 != (byte *)0xfe6039);
  local_a58 = 0xb;
  puVar25 = local_a04;
  if (0x20 < local_a50) {
    puVar25 = local_9b0 + 0xb;
  }
  *puVar25 = 0;
                    /* try { // try from 00b57435 to 00b57439 has its CatchHandler @ 00b5fdf5 */
  CEGUI::PropertySet::setProperty(*(String **)(this + 0x20),(String *)&local_a58);
                    /* try { // try from 00b5743d to 00b57441 has its CatchHandler @ 00b5fed2 */
  CEGUI::String::~String((String *)&local_a58);
                    /* try { // try from 00b57445 to 00b57449 has its CatchHandler @ 00b60307 */
  CEGUI::String::~String((String *)&local_b08);
  local_434 = 0;
  local_438 = 0;
  local_42c = 0;
  local_430 = 0;
                    /* try { // try from 00b57482 to 00b57486 has its CatchHandler @ 00b5fe12 */
  CEGUI::Window::setPosition(*(UVector2 **)(this + 0x20));
  *(undefined1 *)(*(long *)(this + 0x20) + 0x3e2) = 1;
                    /* try { // try from 00b57498 to 00b574b2 has its CatchHandler @ 00b60307 */
  CEGUI::Window::setZOrderingEnabled(SUB81(*(undefined8 *)(this + 0x20),0));
  pcVar4 = *(code **)(*(long *)(*(long *)(this + 0x20) + 0x38) + 0x10);
  local_88[0] = operator_new(0x20);
  *local_88[0] = &PTR__MemberFunctionSlot_00fefcd0;
  local_88[0][2] = 0;
  local_88[0][1] = handle_MouseThrough;
  local_88[0][3] = this;
                    /* try { // try from 00b574f6 to 00b5752b has its CatchHandler @ 00b5fe1a */
  (*pcVar4)(&local_448,*(long *)(this + 0x20) + 0x38,CEGUI::Window::EventMouseMove);
  if ((local_448 != (BoundSlot *)0x0) &&
     (iVar7 = *local_440, *local_440 = iVar7 + -1, iVar7 + -1 == 0)) {
    if (local_448 != (BoundSlot *)0x0) {
      CEGUI::BoundSlot::~BoundSlot(local_448);
      operator_delete(local_448);
    }
    operator_delete(local_440);
    local_448 = (BoundSlot *)0x0;
    local_440 = (int *)0x0;
  }
                    /* try { // try from 00b5755c to 00b57560 has its CatchHandler @ 00b60307 */
  CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_88);
  local_6e8 = &DAT_01423a38;
                    /* try { // try from 00b5757e to 00b57582 has its CatchHandler @ 00b5fe2a */
  std::string::string((string *)&local_6e0,(string *)&::EMPTY_STRING);
                    /* try { // try from 00b57594 to 00b57598 has its CatchHandler @ 00b5fe3f */
  std::wstring::wstring((wstring_conflict *)&local_6d8,(wstring_conflict *)&::EMPTY_WSTRING);
  local_6d0 = 4;
  local_6cc = 3;
  local_6c8 = &DAT_01423a38;
  local_6c0 = 0;
                    /* try { // try from 00b575db to 00b575df has its CatchHandler @ 00b5fe55 */
  std::wstring::wstring((wstring_conflict *)local_98,L"media/ui/inventorymenu.layout",local_39);
                    /* try { // try from 00b575e0 to 00b57602 has its CatchHandler @ 00b5fe5a */
  this_01 = (CFileSystem *)CFileSystem::getSingleton();
  CFileSystem::getFileInfo
            (this_01,(wstring_conflict *)local_98,(CFileInfo *)&local_6e8,false,true,false);
  if ((allocator *)(local_98[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_98[0] + -8);
    iVar7 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar7 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
    }
  }
  local_bb0 = 0x20;
  local_ba8 = 0;
  local_b98 = 0;
  local_ba0 = 0;
  local_b10 = (undefined4 *)0x0;
  local_bb8 = 0;
  local_b90[0] = 0;
  lVar12 = *(long *)(local_6e0 + -0x18);
                    /* try { // try from 00b57689 to 00b5768d has its CatchHandler @ 00b5fd15 */
  CEGUI::String::grow((ulong)&local_bb8);
  puVar23 = local_b90;
  if (0x20 < local_bb0) {
    puVar23 = local_b10;
  }
  puVar23[lVar12] = 0;
  if (lVar12 != 0) {
    lVar32 = lVar12;
    do {
      lVar32 = lVar32 + -1;
      puVar23 = local_b90;
      if (0x20 < local_bb0) {
        puVar23 = local_b10;
      }
      puVar23[lVar32] = (uint)*(byte *)(local_6e0 + lVar32);
    } while (lVar32 != 0);
  }
  local_bb8 = lVar12;
                    /* try { // try from 00b57706 to 00b5770a has its CatchHandler @ 00b5fd25 */
  pWVar15 = (Window *)
            CEGUI::WindowManager::loadWindowLayout
                      (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,
                       SUB81((String *)&local_bb8,0));
                    /* try { // try from 00b57713 to 00b577aa has its CatchHandler @ 00b5fd15 */
  CEGUI::String::~String((String *)&local_bb8);
  CGameUI::convertToScreenScale(*(CGameUI **)(this + 0x70),pWVar15,false);
  CGameUI::mapToFunctions(*(CGameUI **)(this + 0x70),pWVar15);
  mapEventHandlers(this,pWVar15);
  local_c60 = 0x20;
  local_c58 = 0;
  local_c48 = 0;
  local_c50 = 0;
  local_bc0 = (uint *)0x0;
  local_c68 = 0;
  local_c40[0] = 0;
  CEGUI::String::grow((ulong)&local_c68);
  puVar25 = local_c40;
  if (0x20 < local_c60) {
    puVar25 = local_bc0;
  }
  pbVar16 = (byte *)0xfe4a28;
  do {
    bVar3 = *pbVar16;
    pbVar16 = pbVar16 + 1;
    *puVar25 = (uint)bVar3;
    puVar25 = puVar25 + 1;
  } while (pbVar16 != (byte *)0xfe4a2f);
  local_c68 = 7;
  puVar25 = local_c24;
  if (0x20 < local_c60) {
    puVar25 = local_bc0 + 7;
  }
  *puVar25 = 0;
                    /* try { // try from 00b5781a to 00b5781e has its CatchHandler @ 00b5fd35 */
  pSVar17 = (String *)CEGUI::Window::recursiveChildSearch((String *)pWVar15);
                    /* try { // try from 00b57825 to 00b578ad has its CatchHandler @ 00b5fd15 */
  CEGUI::String::~String((String *)&local_c68);
  CEGUI::Window::removeChildWindow(*(Window **)(pSVar17 + 0xb0));
  CEGUI::Window::addChildWindow(*(Window **)(this + 0x20));
  local_dc0 = 0x20;
  local_db8 = 0;
  local_da8 = 0;
  local_db0 = 0;
  local_d20 = (uint *)0x0;
  local_dc8 = 0;
  local_da0[0] = 0;
  CEGUI::String::grow((ulong)&local_dc8);
  puVar25 = local_da0;
  if (0x20 < local_dc0) {
    puVar25 = local_d20;
  }
  pcVar34 = "False";
  do {
    bVar3 = *pcVar34;
    pcVar34 = pcVar34 + 1;
    *puVar25 = (uint)bVar3;
    puVar25 = puVar25 + 1;
  } while ((byte *)pcVar34 != (byte *)0xfe603f);
  local_dc8 = 5;
  puVar25 = local_d8c;
  if (0x20 < local_dc0) {
    puVar25 = local_d20 + 5;
  }
  *puVar25 = 0;
  local_d10 = 0x20;
  local_d08 = 0;
  local_cf8 = 0;
  local_d00 = 0;
  local_c70 = (uint *)0x0;
  local_d18 = 0;
  local_cf0[0] = 0;
                    /* try { // try from 00b57975 to 00b57979 has its CatchHandler @ 00b5fd45 */
  CEGUI::String::grow((ulong)&local_d18);
  puVar25 = local_cf0;
  if (0x20 < local_d10) {
    puVar25 = local_c70;
  }
  pcVar34 = "RiseOnClick";
  do {
    bVar3 = *pcVar34;
    pcVar34 = pcVar34 + 1;
    *puVar25 = (uint)bVar3;
    puVar25 = puVar25 + 1;
  } while ((byte *)pcVar34 != (byte *)0xfe6039);
  local_d18 = 0xb;
  puVar25 = local_cc4;
  if (0x20 < local_d10) {
    puVar25 = local_c70 + 0xb;
  }
  *puVar25 = 0;
                    /* try { // try from 00b579e8 to 00b579ec has its CatchHandler @ 00b5fd55 */
  CEGUI::PropertySet::setProperty(pSVar17,(String *)&local_d18);
                    /* try { // try from 00b579f0 to 00b579f4 has its CatchHandler @ 00b5fd45 */
  CEGUI::String::~String((String *)&local_d18);
                    /* try { // try from 00b579f8 to 00b57a76 has its CatchHandler @ 00b5fd15 */
  CEGUI::String::~String((String *)&local_dc8);
  CEGUI::Window::moveToBack();
  CEGUI::Window::setZOrderingEnabled(SUB81(pSVar17,0));
  local_e70 = 0x20;
  local_e68 = 0;
  local_e58 = 0;
  local_e60 = 0;
  local_dd0 = (uint *)0x0;
  local_e78 = 0;
  local_e50[0] = 0;
  CEGUI::String::grow((ulong)&local_e78);
  puVar25 = local_e50;
  if (0x20 < local_e70) {
    puVar25 = local_dd0;
  }
  pcVar34 = "BottomFrame";
  do {
    bVar3 = *pcVar34;
    pcVar34 = pcVar34 + 1;
    *puVar25 = (uint)bVar3;
    puVar25 = puVar25 + 1;
  } while ((byte *)pcVar34 != (byte *)0xfef825);
  local_e78 = 0xb;
  puVar25 = local_e24;
  if (0x20 < local_e70) {
    puVar25 = local_dd0 + 0xb;
  }
  *puVar25 = 0;
                    /* try { // try from 00b57ae3 to 00b57ae7 has its CatchHandler @ 00b5fd6a */
  uVar14 = CEGUI::Window::recursiveChildSearch((String *)pWVar15);
  *(undefined8 *)(this + 0x48) = uVar14;
                    /* try { // try from 00b57aef to 00b57b78 has its CatchHandler @ 00b5fd15 */
  CEGUI::String::~String((String *)&local_e78);
  CEGUI::Window::removeChildWindow(*(Window **)(*(long *)(this + 0x48) + 0xb0));
  CEGUI::Window::addChildWindow(*(Window **)(this + 0x20));
  local_fd0 = 0x20;
  local_fc8 = 0;
  local_fb8 = 0;
  local_fc0 = 0;
  local_f30 = (uint *)0x0;
  local_fd8 = 0;
  local_fb0[0] = 0;
  CEGUI::String::grow((ulong)&local_fd8);
  puVar25 = local_fb0;
  if (0x20 < local_fd0) {
    puVar25 = local_f30;
  }
  pcVar34 = "False";
  do {
    bVar3 = *pcVar34;
    pcVar34 = pcVar34 + 1;
    *puVar25 = (uint)bVar3;
    puVar25 = puVar25 + 1;
  } while ((byte *)pcVar34 != (byte *)0xfe603f);
  local_fd8 = 5;
  puVar25 = local_f9c;
  if (0x20 < local_fd0) {
    puVar25 = local_f30 + 5;
  }
  *puVar25 = 0;
  local_f20 = 0x20;
  local_f18 = 0;
  local_f08 = 0;
  local_f10 = 0;
  local_e80 = (uint *)0x0;
  local_f28 = 0;
  local_f00[0] = 0;
                    /* try { // try from 00b57c3d to 00b57c41 has its CatchHandler @ 00b5fd6f */
  CEGUI::String::grow((ulong)&local_f28);
  puVar25 = local_f00;
  if (0x20 < local_f20) {
    puVar25 = local_e80;
  }
  pcVar34 = "RiseOnClick";
  do {
    bVar3 = *pcVar34;
    pcVar34 = pcVar34 + 1;
    *puVar25 = (uint)bVar3;
    puVar25 = puVar25 + 1;
  } while ((byte *)pcVar34 != (byte *)0xfe6039);
  local_f28 = 0xb;
  puVar25 = local_ed4;
  if (0x20 < local_f20) {
    puVar25 = local_e80 + 0xb;
  }
  *puVar25 = 0;
                    /* try { // try from 00b57caa to 00b57cae has its CatchHandler @ 00b5fd75 */
  CEGUI::PropertySet::setProperty(*(String **)(this + 0x48),(String *)&local_f28);
                    /* try { // try from 00b57cb2 to 00b57cb6 has its CatchHandler @ 00b5fd6f */
  CEGUI::String::~String((String *)&local_f28);
                    /* try { // try from 00b57cba to 00b57d3a has its CatchHandler @ 00b5fd15 */
  CEGUI::String::~String((String *)&local_fd8);
  CEGUI::Window::moveToFront();
  CEGUI::Window::setZOrderingEnabled(SUB81(*(undefined8 *)(this + 0x48),0));
  local_1080 = 0x20;
  local_1078 = 0;
  local_1068 = 0;
  local_1070 = 0;
  local_fe0 = (uint *)0x0;
  local_1088 = 0;
  local_1060[0] = 0;
  CEGUI::String::grow((ulong)&local_1088);
  puVar25 = local_1060;
  if (0x20 < local_1080) {
    puVar25 = local_fe0;
  }
  pcVar34 = "TopFrame";
  do {
    bVar3 = *pcVar34;
    pcVar34 = pcVar34 + 1;
    *puVar25 = (uint)bVar3;
    puVar25 = puVar25 + 1;
  } while ((byte *)pcVar34 != (byte *)0xfef819);
  local_1088 = 8;
  puVar25 = local_1040;
  if (0x20 < local_1080) {
    puVar25 = local_fe0 + 8;
  }
  *puVar25 = 0;
                    /* try { // try from 00b57dab to 00b57daf has its CatchHandler @ 00b5fd85 */
  uVar14 = CEGUI::Window::recursiveChildSearch((String *)pWVar15);
  *(undefined8 *)(this + 0x28) = uVar14;
                    /* try { // try from 00b57db7 to 00b57e40 has its CatchHandler @ 00b5fd15 */
  CEGUI::String::~String((String *)&local_1088);
  CEGUI::Window::removeChildWindow(*(Window **)(*(long *)(this + 0x28) + 0xb0));
  CEGUI::Window::addChildWindow(*(Window **)(this + 0x20));
  local_11e0 = 0x20;
  local_11d8 = 0;
  local_11c8 = 0;
  local_11d0 = 0;
  local_1140 = (uint *)0x0;
  local_11e8 = 0;
  local_11c0[0] = 0;
  CEGUI::String::grow((ulong)&local_11e8);
  puVar25 = local_11c0;
  if (0x20 < local_11e0) {
    puVar25 = local_1140;
  }
  pcVar34 = "False";
  do {
    bVar3 = *pcVar34;
    pcVar34 = pcVar34 + 1;
    *puVar25 = (uint)bVar3;
    puVar25 = puVar25 + 1;
  } while ((byte *)pcVar34 != (byte *)0xfe603f);
  local_11e8 = 5;
  puVar25 = local_11ac;
  if (0x20 < local_11e0) {
    puVar25 = local_1140 + 5;
  }
  *puVar25 = 0;
  local_1130 = 0x20;
  local_1128 = 0;
  local_1118 = 0;
  local_1120 = 0;
  local_1090 = (uint *)0x0;
  local_1138 = 0;
  local_1110[0] = 0;
                    /* try { // try from 00b57f05 to 00b57f09 has its CatchHandler @ 00b5fd95 */
  CEGUI::String::grow((ulong)&local_1138);
  puVar25 = local_1110;
  if (0x20 < local_1130) {
    puVar25 = local_1090;
  }
  pcVar34 = "RiseOnClick";
  do {
    bVar3 = *pcVar34;
    pcVar34 = pcVar34 + 1;
    *puVar25 = (uint)bVar3;
    puVar25 = puVar25 + 1;
  } while ((byte *)pcVar34 != (byte *)0xfe6039);
  local_1138 = 0xb;
  puVar25 = local_10e4;
  if (0x20 < local_1130) {
    puVar25 = local_1090 + 0xb;
  }
  *puVar25 = 0;
                    /* try { // try from 00b57f7a to 00b57f7e has its CatchHandler @ 00b5fda5 */
  CEGUI::PropertySet::setProperty(*(String **)(this + 0x28),(String *)&local_1138);
                    /* try { // try from 00b57f82 to 00b57f86 has its CatchHandler @ 00b5fd95 */
  CEGUI::String::~String((String *)&local_1138);
                    /* try { // try from 00b57f8a to 00b58007 has its CatchHandler @ 00b5fd15 */
  CEGUI::String::~String((String *)&local_11e8);
  CEGUI::Window::moveToFront();
  CEGUI::Window::setZOrderingEnabled(SUB81(*(undefined8 *)(this + 0x28),0));
  local_13f0 = 0x20;
  local_13e8 = 0;
  local_13d8 = 0;
  local_13e0 = 0;
  local_1350 = (undefined4 *)0x0;
  local_13f8 = 0;
  local_13d0[0] = 0;
  CEGUI::String::grow((ulong)&local_13f8);
  local_13f8 = 0;
  puVar23 = local_13d0;
  if (0x20 < local_13f0) {
    puVar23 = local_1350;
  }
  *puVar23 = 0;
                    /* try { // try from 00b58042 to 00b58046 has its CatchHandler @ 00b5fdb5 */
  CEGUI::String::String(local_1348,(uchar *)"ISockets");
                    /* try { // try from 00b58057 to 00b5805b has its CatchHandler @ 00b5fdc5 */
  CEGUI::String::String(local_1298,(uchar *)"DefaultWindow");
                    /* try { // try from 00b5806c to 00b58070 has its CatchHandler @ 00b5fdda */
  uVar14 = CEGUI::WindowManager::createWindow
                     (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,local_1298,local_1348);
  *(undefined8 *)(this + 0x30) = uVar14;
                    /* try { // try from 00b58078 to 00b5807c has its CatchHandler @ 00b5fdc5 */
  CEGUI::String::~String(local_1298);
                    /* try { // try from 00b58080 to 00b58084 has its CatchHandler @ 00b5fdb5 */
  CEGUI::String::~String(local_1348);
                    /* try { // try from 00b58088 to 00b580ad has its CatchHandler @ 00b5fd15 */
  CEGUI::String::~String((String *)&local_13f8);
  CEGUI::Window::addChildWindow(*(Window **)(this + 0x28));
  CEGUI::Window::getSize();
                    /* try { // try from 00b580b5 to 00b580b9 has its CatchHandler @ 00b5fde7 */
  CEGUI::Window::setSize(*(UVector2 **)(this + 0x30));
  local_1550 = 0x20;
  local_1548 = 0;
  local_1538 = 0;
  local_1540 = 0;
  local_14b0 = (uint *)0x0;
  local_1558 = 0;
  local_1530[0] = 0;
                    /* try { // try from 00b5811d to 00b58121 has its CatchHandler @ 00b5fd15 */
  CEGUI::String::grow((ulong)&local_1558);
  puVar25 = local_1530;
  if (0x20 < local_1550) {
    puVar25 = local_14b0;
  }
  pcVar34 = "False";
  do {
    bVar3 = *pcVar34;
    pcVar34 = pcVar34 + 1;
    *puVar25 = (uint)bVar3;
    puVar25 = puVar25 + 1;
  } while ((byte *)pcVar34 != (byte *)0xfe603f);
  local_1558 = 5;
  puVar25 = local_151c;
  if (0x20 < local_1550) {
    puVar25 = local_14b0 + 5;
  }
  *puVar25 = 0;
  local_14a0 = 0x20;
  local_1498 = 0;
  local_1488 = 0;
  local_1490 = 0;
  local_1400 = (uint *)0x0;
  local_14a8 = 0;
  local_1480[0] = 0;
                    /* try { // try from 00b581e5 to 00b581e9 has its CatchHandler @ 00b5fdec */
  CEGUI::String::grow((ulong)&local_14a8);
  puVar25 = local_1480;
  if (0x20 < local_14a0) {
    puVar25 = local_1400;
  }
  pcVar34 = "RiseOnClick";
  do {
    bVar3 = *pcVar34;
    pcVar34 = pcVar34 + 1;
    *puVar25 = (uint)bVar3;
    puVar25 = puVar25 + 1;
  } while ((byte *)pcVar34 != (byte *)0xfe6039);
  local_14a8 = 0xb;
  puVar25 = local_1454;
  if (0x20 < local_14a0) {
    puVar25 = local_1400 + 0xb;
  }
  *puVar25 = 0;
                    /* try { // try from 00b5825a to 00b5825e has its CatchHandler @ 00b60065 */
  CEGUI::PropertySet::setProperty(*(String **)(this + 0x30),(String *)&local_14a8);
                    /* try { // try from 00b58262 to 00b58266 has its CatchHandler @ 00b5fdec */
  CEGUI::String::~String((String *)&local_14a8);
                    /* try { // try from 00b5826a to 00b5826e has its CatchHandler @ 00b5fd15 */
  CEGUI::String::~String((String *)&local_1558);
  local_464 = 0;
  local_468 = 0;
  local_45c = 0;
  local_460 = 0;
                    /* try { // try from 00b582a7 to 00b582ab has its CatchHandler @ 00b60075 */
  CEGUI::Window::setPosition(*(UVector2 **)(this + 0x30));
  *(undefined1 *)(*(long *)(this + 0x30) + 0x3e2) = 1;
                    /* try { // try from 00b582bb to 00b58321 has its CatchHandler @ 00b5fd15 */
  CEGUI::Window::moveToFront();
  local_1760 = 0x20;
  local_1758 = 0;
  local_1748 = 0;
  local_1750 = 0;
  local_16c0 = (undefined4 *)0x0;
  local_1768 = 0;
  local_1740[0] = 0;
  CEGUI::String::grow((ulong)&local_1768);
  local_1768 = 0;
  puVar23 = local_16c0;
  if (local_1760 < 0x21) {
    puVar23 = local_1740;
  }
  *puVar23 = 0;
                    /* try { // try from 00b5835c to 00b58360 has its CatchHandler @ 00b60085 */
  CEGUI::String::String(local_16b8,(uchar *)"ISocketsO");
  pcVar30 = (char *)0x0;
  local_1600 = 0x20;
  local_15f8 = 0;
  local_15e8 = 0;
  pcVar34 = "DefaultWindow";
  local_15f0 = 0;
  local_1560 = (uint *)0x0;
  local_1608 = 0;
  local_15e0[0] = 0;
  cVar2 = s_DefaultWindow_00fe499d[0];
  while (pcVar34 = pcVar34 + 1, cVar2 != '\0') {
    pcVar30 = pcVar34 + -0xfe499d;
    cVar2 = *pcVar34;
  }
  if (pcVar30 == CEGUI::String::npos) {
                    /* try { // try from 00b5ead8 to 00b5eadc has its CatchHandler @ 00b605a1 */
    std::string::string((string *)local_358,"Length for utf8 encoded string can not be \'npos\'",
                        local_4a);
    plVar24 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00b5eaf0 to 00b5eaf4 has its CatchHandler @ 00b60589 */
    std::length_error::length_error(plVar24,(string *)local_358);
    if ((allocator *)(local_358[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_358[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_358[0] + -0x18));
      }
    }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00b5eb1b to 00b5eb1f has its CatchHandler @ 00b6002a */
    __cxa_throw(plVar24,&std::length_error::typeinfo,std::length_error::~length_error);
  }
  lVar12 = 0;
  pcVar34 = pcVar30;
  pbVar16 = (byte *)"DefaultWindow";
  while (pcVar34 != (char *)0x0) {
    bVar3 = *pbVar16;
    pcVar13 = pcVar34 + -1;
    pbVar28 = pbVar16 + 1;
    if ((char)bVar3 < '\0') {
      if (bVar3 < 0xe0) {
        pcVar13 = pcVar34 + -2;
        pbVar28 = pbVar16 + 2;
      }
      else if (bVar3 < 0xf0) {
        pcVar13 = pcVar34 + -3;
        pbVar28 = pbVar16 + 3;
      }
      else {
        pcVar13 = pcVar34 + -3;
        pbVar28 = pbVar16 + 4;
      }
    }
    lVar12 = lVar12 + 1;
    pcVar34 = pcVar13;
    pbVar16 = pbVar28;
  }
                    /* try { // try from 00b584ee to 00b584f2 has its CatchHandler @ 00b6002a */
  CEGUI::String::grow((ulong)&local_1608);
  puVar25 = local_15e0;
  if (0x20 < local_1600) {
    puVar25 = local_1560;
  }
  if (pcVar30 == (char *)0x0) {
    pcVar34 = "DefaultWindow";
    if (s_DefaultWindow_00fe499d[0] != '\0') {
      do {
        pcVar34 = pcVar34 + 1;
        pcVar30 = pcVar34 + -0xfe499d;
      } while (*pcVar34 != '\0');
      bVar37 = pcVar30 != (char *)0x0 && local_1600 != 0;
      goto LAB_00b5851c;
    }
  }
  else {
    bVar37 = local_1600 != 0;
LAB_00b5851c:
    if (bVar37) {
      pcVar34 = (char *)0x0;
      uVar10 = 0;
      uVar26 = local_1600;
      do {
        bVar3 = pcVar34[0xfe499d];
        uVar11 = (uint)bVar3;
        uVar9 = uVar10 + 1;
        if ((char)bVar3 < '\0') {
          uVar11 = (uint)bVar3;
          if (0xdf < bVar3) {
            if (bVar3 < 0xf0) {
              uVar29 = (ulong)uVar9;
              uVar9 = uVar10 + 3;
              uVar11 = (byte)"DefaultWindow"[uVar10 + 2] & 0x3f | (uVar11 & 0xf) << 0xc |
                       ((byte)"DefaultWindow"[uVar29] & 0x3f) << 6;
            }
            else {
              uVar29 = (ulong)uVar9;
              uVar9 = uVar10 + 4;
              uVar11 = ((byte)"DefaultWindow"[uVar29] & 0x3f) << 0xc |
                       (byte)"DefaultWindow"[uVar10 + 3] & 0x3f | (uVar11 & 7) << 0x12 |
                       ((byte)"DefaultWindow"[uVar10 + 2] & 0x3f) << 6;
            }
            goto LAB_00b58533;
          }
          uVar10 = uVar10 + 2;
          *puVar25 = (byte)"DefaultWindow"[uVar9] & 0x3f | (uVar11 & 0x1f) << 6;
        }
        else {
LAB_00b58533:
          *puVar25 = uVar11;
          uVar10 = uVar9;
        }
        pcVar34 = (char *)(ulong)uVar10;
        if ((pcVar30 <= pcVar34) || (uVar26 = uVar26 - 1, uVar26 == 0)) break;
        puVar25 = puVar25 + 1;
      } while( true );
    }
  }
  puVar25 = local_15e0;
  if (0x20 < local_1600) {
    puVar25 = local_1560;
  }
  puVar25[lVar12] = 0;
  local_1608 = lVar12;
                    /* try { // try from 00b585d1 to 00b585d5 has its CatchHandler @ 00b6004c */
  uVar14 = CEGUI::WindowManager::createWindow
                     (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,(String *)&local_1608,
                      local_16b8);
  *(undefined8 *)(this + 0x38) = uVar14;
                    /* try { // try from 00b585dd to 00b585e1 has its CatchHandler @ 00b6002a */
  CEGUI::String::~String((String *)&local_1608);
                    /* try { // try from 00b585ea to 00b585ee has its CatchHandler @ 00b60085 */
  CEGUI::String::~String(local_16b8);
                    /* try { // try from 00b585f7 to 00b5861c has its CatchHandler @ 00b5fd15 */
  CEGUI::String::~String((String *)&local_1768);
  CEGUI::Window::addChildWindow(*(Window **)(this + 0x28));
  CEGUI::Window::getSize();
                    /* try { // try from 00b58624 to 00b58628 has its CatchHandler @ 00b60059 */
  CEGUI::Window::setSize(*(UVector2 **)(this + 0x38));
  local_18c0 = 0x20;
  local_18b8 = 0;
  local_18a8 = 0;
  local_18b0 = 0;
  local_1820 = (uint *)0x0;
  local_18c8 = 0;
  local_18a0[0] = 0;
                    /* try { // try from 00b5868c to 00b58690 has its CatchHandler @ 00b5fd15 */
  CEGUI::String::grow((ulong)&local_18c8);
  puVar25 = local_18a0;
  if (0x20 < local_18c0) {
    puVar25 = local_1820;
  }
  pcVar34 = "False";
  do {
    bVar3 = *pcVar34;
    pcVar34 = pcVar34 + 1;
    *puVar25 = (uint)bVar3;
    puVar25 = puVar25 + 1;
  } while ((byte *)pcVar34 != (byte *)0xfe603f);
  local_18c8 = 5;
  puVar25 = local_188c;
  if (0x20 < local_18c0) {
    puVar25 = local_1820 + 5;
  }
  *puVar25 = 0;
  local_1810 = 0x20;
  local_1808 = 0;
  local_17f8 = 0;
  local_1800 = 0;
  local_1770 = (uint *)0x0;
  local_1818 = 0;
  local_17f0[0] = 0;
                    /* try { // try from 00b58755 to 00b58759 has its CatchHandler @ 00b6005e */
  CEGUI::String::grow((ulong)&local_1818);
  puVar25 = local_17f0;
  if (0x20 < local_1810) {
    puVar25 = local_1770;
  }
  pcVar34 = "RiseOnClick";
  do {
    bVar3 = *pcVar34;
    pcVar34 = pcVar34 + 1;
    *puVar25 = (uint)bVar3;
    puVar25 = puVar25 + 1;
  } while ((byte *)pcVar34 != (byte *)0xfe6039);
  local_1818 = 0xb;
  puVar25 = local_17c4;
  if (0x20 < local_1810) {
    puVar25 = local_1770 + 0xb;
  }
  *puVar25 = 0;
                    /* try { // try from 00b587ca to 00b587ce has its CatchHandler @ 00b600c1 */
  CEGUI::PropertySet::setProperty(*(String **)(this + 0x38),(String *)&local_1818);
                    /* try { // try from 00b587d2 to 00b587d6 has its CatchHandler @ 00b6005e */
  CEGUI::String::~String((String *)&local_1818);
                    /* try { // try from 00b587da to 00b587de has its CatchHandler @ 00b5fd15 */
  CEGUI::String::~String((String *)&local_18c8);
  local_484 = 0;
  local_488 = 0;
  local_47c = 0;
  local_480 = 0;
                    /* try { // try from 00b58817 to 00b5881b has its CatchHandler @ 00b600c6 */
  CEGUI::Window::setPosition(*(UVector2 **)(this + 0x38));
  *(undefined1 *)(*(long *)(this + 0x38) + 0x3e2) = 1;
                    /* try { // try from 00b5882b to 00b58891 has its CatchHandler @ 00b5fd15 */
  CEGUI::Window::moveToFront();
  local_1ad0 = 0x20;
  local_1ac8 = 0;
  local_1ab8 = 0;
  local_1ac0 = 0;
  local_1a30 = (undefined4 *)0x0;
  local_1ad8 = 0;
  local_1ab0[0] = 0;
  CEGUI::String::grow((ulong)&local_1ad8);
  local_1ad8 = 0;
  puVar23 = local_1a30;
  if (local_1ad0 < 0x21) {
    puVar23 = local_1ab0;
  }
  *puVar23 = 0;
  pcVar30 = (char *)0x0;
  pcVar13 = "Icons";
  local_1a20 = 0x20;
  local_1a18 = 0;
  local_1a08 = 0;
  local_1a10 = 0;
  local_1980 = (uint *)0x0;
  local_1a28 = 0;
  local_1a00[0] = 0;
  pcVar34 = "Icons";
  cVar2 = s_UIIcons_00fe49dd[1];
  while (cVar2 != '\0') {
    pcVar30 = pcVar34 + -0xfe49de;
    cVar2 = *pcVar34;
    pcVar34 = pcVar34 + 1;
  }
  if (pcVar30 == CEGUI::String::npos) {
                    /* try { // try from 00b5ebfe to 00b5ec02 has its CatchHandler @ 00b604fe */
    std::string::string((string *)local_368,"Length for utf8 encoded string can not be \'npos\'",
                        local_4c);
    plVar24 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00b5ec16 to 00b5ec1a has its CatchHandler @ 00b604ba */
    std::length_error::length_error(plVar24,(string *)local_368);
    if ((allocator *)(local_368[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_368[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_368[0] + -0x18));
      }
    }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00b5ec41 to 00b5ec45 has its CatchHandler @ 00b600d5 */
    __cxa_throw(plVar24,&std::length_error::typeinfo,std::length_error::~length_error);
  }
  lVar12 = 0;
  pcVar34 = pcVar30;
  pbVar16 = (byte *)0xfe49de;
  while (pcVar34 != (char *)0x0) {
    bVar3 = *pbVar16;
    pcVar18 = pcVar34 + -1;
    pbVar28 = pbVar16 + 1;
    if ((char)bVar3 < '\0') {
      if (bVar3 < 0xe0) {
        pcVar18 = pcVar34 + -2;
        pbVar28 = pbVar16 + 2;
      }
      else if (bVar3 < 0xf0) {
        pcVar18 = pcVar34 + -3;
        pbVar28 = pbVar16 + 3;
      }
      else {
        pcVar18 = pcVar34 + -3;
        pbVar28 = pbVar16 + 4;
      }
    }
    lVar12 = lVar12 + 1;
    pcVar34 = pcVar18;
    pbVar16 = pbVar28;
  }
                    /* try { // try from 00b58a5b to 00b58a5f has its CatchHandler @ 00b600d5 */
  CEGUI::String::grow((ulong)&local_1a28);
  if (local_1a20 < 0x21) {
    puVar25 = local_1a00;
    if (pcVar30 == (char *)0x0) goto LAB_00b5b479;
LAB_00b58a87:
    bVar37 = local_1a20 != 0;
LAB_00b58a8d:
    if (bVar37) {
      pcVar34 = (char *)0x0;
      uVar10 = 0;
      uVar26 = local_1a20;
      do {
        bVar3 = pcVar34[0xfe49de];
        uVar11 = (uint)bVar3;
        uVar9 = uVar10 + 1;
        if ((char)bVar3 < '\0') {
          uVar11 = (uint)bVar3;
          if (0xdf < bVar3) {
            if (bVar3 < 0xf0) {
              uVar29 = (ulong)uVar9;
              uVar9 = uVar10 + 3;
              uVar11 = (byte)"UIIcons"[(ulong)(uVar10 + 2) + 1] & 0x3f | (uVar11 & 0xf) << 0xc |
                       ((byte)"UIIcons"[uVar29 + 1] & 0x3f) << 6;
            }
            else {
              uVar29 = (ulong)uVar9;
              uVar9 = uVar10 + 4;
              uVar11 = ((byte)"UIIcons"[uVar29 + 1] & 0x3f) << 0xc |
                       (byte)"UIIcons"[(ulong)(uVar10 + 3) + 1] & 0x3f | (uVar11 & 7) << 0x12 |
                       ((byte)"UIIcons"[(ulong)(uVar10 + 2) + 1] & 0x3f) << 6;
            }
            goto LAB_00b58aa3;
          }
          uVar10 = uVar10 + 2;
          *puVar25 = (byte)"UIIcons"[(ulong)uVar9 + 1] & 0x3f | (uVar11 & 0x1f) << 6;
        }
        else {
LAB_00b58aa3:
          *puVar25 = uVar11;
          uVar10 = uVar9;
        }
        pcVar34 = (char *)(ulong)uVar10;
        if ((pcVar30 <= pcVar34) || (uVar26 = uVar26 - 1, uVar26 == 0)) break;
        puVar25 = puVar25 + 1;
      } while( true );
    }
  }
  else {
    puVar25 = local_1980;
    if (pcVar30 != (char *)0x0) goto LAB_00b58a87;
LAB_00b5b479:
    if (s_UIIcons_00fe49dd[1] != '\0') {
      do {
        cVar2 = *pcVar13;
        pcVar30 = pcVar13 + -0xfe49de;
        pcVar13 = pcVar13 + 1;
      } while (cVar2 != '\0');
      bVar37 = pcVar30 != (char *)0x0 && local_1a20 != 0;
      goto LAB_00b58a8d;
    }
  }
  puVar25 = local_1980;
  if (local_1a20 < 0x21) {
    puVar25 = local_1a00;
  }
  puVar25[lVar12] = 0;
  pcVar30 = (char *)0x0;
  local_1970 = 0x20;
  local_1968 = 0;
  pcVar34 = "DefaultWindow";
  local_1958 = 0;
  local_1960 = 0;
  local_18d0 = (uint *)0x0;
  local_1978 = 0;
  local_1950[0] = 0;
  cVar2 = s_DefaultWindow_00fe499d[0];
  while (pcVar34 = pcVar34 + 1, cVar2 != '\0') {
    pcVar30 = pcVar34 + -0xfe499d;
    cVar2 = *pcVar34;
  }
  local_1a28 = lVar12;
  if (pcVar30 == CEGUI::String::npos) {
                    /* try { // try from 00b5ecd8 to 00b5ecdc has its CatchHandler @ 00b603fc */
    std::string::string((string *)local_378,"Length for utf8 encoded string can not be \'npos\'",
                        local_4e);
    plVar24 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00b5ecf0 to 00b5ecf4 has its CatchHandler @ 00b603e4 */
    std::length_error::length_error(plVar24,(string *)local_378);
    if ((allocator *)(local_378[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_378[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_378[0] + -0x18));
      }
    }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00b5ed1b to 00b5ed1f has its CatchHandler @ 00b60119 */
    __cxa_throw(plVar24,&std::length_error::typeinfo,std::length_error::~length_error);
  }
  lVar12 = 0;
  pcVar34 = pcVar30;
  pbVar16 = (byte *)"DefaultWindow";
  while (pcVar34 != (char *)0x0) {
    bVar3 = *pbVar16;
    pcVar13 = pcVar34 + -1;
    pbVar28 = pbVar16 + 1;
    if ((char)bVar3 < '\0') {
      if (bVar3 < 0xe0) {
        pcVar13 = pcVar34 + -2;
        pbVar28 = pbVar16 + 2;
      }
      else if (bVar3 < 0xf0) {
        pcVar13 = pcVar34 + -3;
        pbVar28 = pbVar16 + 3;
      }
      else {
        pcVar13 = pcVar34 + -3;
        pbVar28 = pbVar16 + 4;
      }
    }
    lVar12 = lVar12 + 1;
    pcVar34 = pcVar13;
    pbVar16 = pbVar28;
  }
                    /* try { // try from 00b58cbe to 00b58cc2 has its CatchHandler @ 00b60119 */
  CEGUI::String::grow((ulong)&local_1978);
  puVar25 = local_1950;
  if (0x20 < local_1970) {
    puVar25 = local_18d0;
  }
  if (pcVar30 == (char *)0x0) {
    if (s_DefaultWindow_00fe499d[0] == '\0') goto LAB_00b58d60;
    do {
      pcVar33 = pcVar33 + 1;
      pcVar30 = pcVar33 + -0xfe499d;
    } while (*pcVar33 != '\0');
    bVar37 = pcVar30 != (char *)0x0 && local_1970 != 0;
  }
  else {
    bVar37 = local_1970 != 0;
  }
  if (bVar37) {
    pcVar34 = (char *)0x0;
    uVar10 = 0;
    uVar26 = local_1970;
    do {
      bVar3 = pcVar34[0xfe499d];
      uVar11 = (uint)bVar3;
      uVar9 = uVar10 + 1;
      if ((char)bVar3 < '\0') {
        uVar11 = (uint)bVar3;
        if (0xdf < bVar3) {
          if (bVar3 < 0xf0) {
            uVar29 = (ulong)uVar9;
            uVar9 = uVar10 + 3;
            uVar11 = (byte)"DefaultWindow"[uVar10 + 2] & 0x3f | (uVar11 & 0xf) << 0xc |
                     ((byte)"DefaultWindow"[uVar29] & 0x3f) << 6;
          }
          else {
            uVar29 = (ulong)uVar9;
            uVar9 = uVar10 + 4;
            uVar11 = ((byte)"DefaultWindow"[uVar29] & 0x3f) << 0xc |
                     (byte)"DefaultWindow"[uVar10 + 3] & 0x3f | (uVar11 & 7) << 0x12 |
                     ((byte)"DefaultWindow"[uVar10 + 2] & 0x3f) << 6;
          }
          goto LAB_00b58d03;
        }
        uVar10 = uVar10 + 2;
        *puVar25 = (byte)"DefaultWindow"[uVar9] & 0x3f | (uVar11 & 0x1f) << 6;
      }
      else {
LAB_00b58d03:
        *puVar25 = uVar11;
        uVar10 = uVar9;
      }
      pcVar34 = (char *)(ulong)uVar10;
      if ((pcVar30 <= pcVar34) || (uVar26 = uVar26 - 1, uVar26 == 0)) break;
      puVar25 = puVar25 + 1;
    } while( true );
  }
LAB_00b58d60:
  puVar25 = local_1950;
  if (0x20 < local_1970) {
    puVar25 = local_18d0;
  }
  puVar25[lVar12] = 0;
  local_1978 = lVar12;
                    /* try { // try from 00b58da1 to 00b58da5 has its CatchHandler @ 00b6012b */
  uVar14 = CEGUI::WindowManager::createWindow
                     (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,(String *)&local_1978,
                      (String *)&local_1a28);
  *(undefined8 *)(this + 0x40) = uVar14;
                    /* try { // try from 00b58dad to 00b58db1 has its CatchHandler @ 00b60119 */
  CEGUI::String::~String((String *)&local_1978);
                    /* try { // try from 00b58dba to 00b58dbe has its CatchHandler @ 00b600d5 */
  CEGUI::String::~String((String *)&local_1a28);
                    /* try { // try from 00b58dc7 to 00b58dec has its CatchHandler @ 00b5fd15 */
  CEGUI::String::~String((String *)&local_1ad8);
  CEGUI::Window::addChildWindow(*(Window **)(this + 0x28));
  CEGUI::Window::getSize();
                    /* try { // try from 00b58df4 to 00b58df8 has its CatchHandler @ 00b5ffa5 */
  CEGUI::Window::setSize(*(UVector2 **)(this + 0x40));
  local_1c30 = 0x20;
  local_1c28 = 0;
  local_1c18 = 0;
  local_1c20 = 0;
  local_1b90 = (uint *)0x0;
  local_1c38 = 0;
  local_1c10[0] = 0;
                    /* try { // try from 00b58e5c to 00b58e60 has its CatchHandler @ 00b5fd15 */
  CEGUI::String::grow((ulong)&local_1c38);
  puVar25 = local_1c10;
  if (0x20 < local_1c30) {
    puVar25 = local_1b90;
  }
  pcVar34 = "False";
  do {
    bVar3 = *pcVar34;
    pcVar34 = pcVar34 + 1;
    *puVar25 = (uint)bVar3;
    puVar25 = puVar25 + 1;
  } while ((byte *)pcVar34 != (byte *)0xfe603f);
  local_1c38 = 5;
  puVar25 = local_1bfc;
  if (0x20 < local_1c30) {
    puVar25 = local_1b90 + 5;
  }
  *puVar25 = 0;
  local_1b80 = 0x20;
  local_1b78 = 0;
  local_1b68 = 0;
  local_1b70 = 0;
  local_1ae0 = (uint *)0x0;
  local_1b88 = 0;
  local_1b60[0] = 0;
                    /* try { // try from 00b58f25 to 00b58f29 has its CatchHandler @ 00b5ffb5 */
  CEGUI::String::grow((ulong)&local_1b88);
  puVar25 = local_1b60;
  if (0x20 < local_1b80) {
    puVar25 = local_1ae0;
  }
  pcVar34 = "RiseOnClick";
  do {
    bVar3 = *pcVar34;
    pcVar34 = pcVar34 + 1;
    *puVar25 = (uint)bVar3;
    puVar25 = puVar25 + 1;
  } while ((byte *)pcVar34 != (byte *)0xfe6039);
  local_1b88 = 0xb;
  puVar25 = local_1b34;
  if (0x20 < local_1b80) {
    puVar25 = local_1ae0 + 0xb;
  }
  *puVar25 = 0;
                    /* try { // try from 00b58f9a to 00b58f9e has its CatchHandler @ 00b5ffc5 */
  CEGUI::PropertySet::setProperty(*(String **)(this + 0x40),(String *)&local_1b88);
                    /* try { // try from 00b58fa2 to 00b58fa6 has its CatchHandler @ 00b5ffb5 */
  CEGUI::String::~String((String *)&local_1b88);
                    /* try { // try from 00b58faa to 00b58fae has its CatchHandler @ 00b5fd15 */
  CEGUI::String::~String((String *)&local_1c38);
  local_4a4 = 0;
  local_4a8 = 0;
  local_49c = 0;
  local_4a0 = 0;
                    /* try { // try from 00b58fe7 to 00b58feb has its CatchHandler @ 00b5ffd5 */
  CEGUI::Window::setPosition(*(UVector2 **)(this + 0x40));
  *(undefined1 *)(*(long *)(this + 0x40) + 0x3e2) = 1;
                    /* try { // try from 00b58ffb to 00b59067 has its CatchHandler @ 00b5fd15 */
  CEGUI::Window::moveToFront();
  local_1ce0 = 0x20;
  local_1cd8 = 0;
  local_1cc8 = 0;
  local_1cd0 = 0;
  local_1c40 = (uint *)0x0;
  local_1ce8 = 0;
  local_1cc0[0] = 0;
  CEGUI::String::grow((ulong)&local_1ce8);
  puVar25 = local_1cc0;
  if (0x20 < local_1ce0) {
    puVar25 = local_1c40;
  }
  pcVar34 = "SlotGlow";
  do {
    bVar3 = *pcVar34;
    pcVar34 = pcVar34 + 1;
    *puVar25 = (uint)bVar3;
    puVar25 = puVar25 + 1;
  } while ((byte *)pcVar34 != (byte *)0xfef810);
  local_1ce8 = 8;
  puVar25 = local_1ca0;
  if (0x20 < local_1ce0) {
    puVar25 = local_1c40 + 8;
  }
  *puVar25 = 0;
                    /* try { // try from 00b590d1 to 00b590d5 has its CatchHandler @ 00b5ffe5 */
  uVar14 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x28));
  *(undefined8 *)(this + 0x1d00) = uVar14;
                    /* try { // try from 00b590e0 to 00b59190 has its CatchHandler @ 00b5fd15 */
  CEGUI::String::~String((String *)&local_1ce8);
  CEGUI::EventSet::setMutedState((bool)((char)*(undefined8 *)(this + 0x1d00) + '8'));
  *(undefined1 *)(*(long *)(this + 0x1d00) + 0x3e2) = 1;
  *(undefined1 *)(*(long *)(this + 0x1d00) + 0x213) = 0;
  CEGUI::Window::removeChildWindow(*(Window **)(*(long *)(this + 0x1d00) + 0xb0));
  local_1d90 = 0x20;
  local_1d88 = 0;
  local_1d78 = 0;
  local_1d80 = 0;
  local_1cf0 = (uint *)0x0;
  local_1d98 = 0;
  local_1d70[0] = 0;
  CEGUI::String::grow((ulong)&local_1d98);
  puVar25 = local_1d70;
  if (0x20 < local_1d90) {
    puVar25 = local_1cf0;
  }
  pcVar34 = "Close";
  do {
    bVar3 = *pcVar34;
    pcVar34 = pcVar34 + 1;
    *puVar25 = (uint)bVar3;
    puVar25 = puVar25 + 1;
  } while ((byte *)pcVar34 != (byte *)0xfef807);
  local_1d98 = 5;
  puVar25 = local_1d5c;
  if (0x20 < local_1d90) {
    puVar25 = local_1cf0 + 5;
  }
  *puVar25 = 0;
                    /* try { // try from 00b591fa to 00b591fe has its CatchHandler @ 00b5fff5 */
  lVar12 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x28));
                    /* try { // try from 00b59205 to 00b5922a has its CatchHandler @ 00b5fd15 */
  CEGUI::String::~String((String *)&local_1d98);
  *(undefined1 *)(lVar12 + 0x213) = 0;
  CEGUI::Window::moveToFront();
  pcVar4 = *(code **)(*(long *)(lVar12 + 0x38) + 0x10);
  local_a8[0] = operator_new(0x20);
  *local_a8[0] = &PTR__MemberFunctionSlot_00fefcd0;
  local_a8[0][2] = 0;
  local_a8[0][1] = handle_CloseButton;
  local_a8[0][3] = this;
                    /* try { // try from 00b5926a to 00b5929f has its CatchHandler @ 00b601fc */
  (*pcVar4)(&local_4b8,lVar12 + 0x38,CEGUI::Window::EventMouseButtonDown,(SubscriberSlot *)local_a8)
  ;
  if ((local_4b8 != (BoundSlot *)0x0) &&
     (iVar7 = *local_4b0, *local_4b0 = iVar7 + -1, iVar7 + -1 == 0)) {
    if (local_4b8 != (BoundSlot *)0x0) {
      CEGUI::BoundSlot::~BoundSlot(local_4b8);
      operator_delete(local_4b8);
    }
    operator_delete(local_4b0);
    local_4b8 = (BoundSlot *)0x0;
    local_4b0 = (int *)0x0;
  }
                    /* try { // try from 00b592d0 to 00b5933c has its CatchHandler @ 00b5fd15 */
  CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_a8);
  local_1e40 = 0x20;
  local_1e38 = 0;
  local_1e28 = 0;
  local_1e30 = 0;
  local_1da0 = (uint *)0x0;
  local_1e48 = 0;
  local_1e20[0] = 0;
  CEGUI::String::grow((ulong)&local_1e48);
  puVar25 = local_1e20;
  if (0x20 < local_1e40) {
    puVar25 = local_1da0;
  }
  pcVar34 = "PaperdollEquip";
  do {
    bVar3 = *pcVar34;
    pcVar34 = pcVar34 + 1;
    *puVar25 = (uint)bVar3;
    puVar25 = puVar25 + 1;
  } while ((byte *)pcVar34 != (byte *)0xfef801);
  local_1e48 = 0xe;
  puVar25 = local_1de8;
  if (0x20 < local_1e40) {
    puVar25 = local_1da0 + 0xe;
  }
  *puVar25 = 0;
                    /* try { // try from 00b593aa to 00b593ae has its CatchHandler @ 00b5ff7f */
  lVar12 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x28));
                    /* try { // try from 00b593b5 to 00b593f2 has its CatchHandler @ 00b5fd15 */
  CEGUI::String::~String((String *)&local_1e48);
  CEGUI::Window::moveToFront();
  *(undefined1 *)(lVar12 + 0x213) = 0;
  CEGUI::Window::setWantsMultiClickEvents(SUB81(lVar12,0));
  *(CInventoryMenu **)(lVar12 + 0x1d8) = this + 0x101c;
  pcVar4 = *(code **)(*(long *)(lVar12 + 0x38) + 0x10);
  local_b8[0] = operator_new(0x20);
  *local_b8[0] = &PTR__MemberFunctionSlot_00fefcd0;
  local_b8[0][2] = 0;
  local_b8[0][1] = handle_ItemClick;
  local_b8[0][3] = this;
                    /* try { // try from 00b59432 to 00b59467 has its CatchHandler @ 00b5ff84 */
  (*pcVar4)(&local_4c8,lVar12 + 0x38,CEGUI::Window::EventMouseButtonDown,(SubscriberSlot *)local_b8)
  ;
  if ((local_4c8 != (BoundSlot *)0x0) &&
     (iVar7 = *local_4c0, *local_4c0 = iVar7 + -1, iVar7 + -1 == 0)) {
    if (local_4c8 != (BoundSlot *)0x0) {
      CEGUI::BoundSlot::~BoundSlot(local_4c8);
      operator_delete(local_4c8);
    }
    operator_delete(local_4c0);
    local_4c8 = (BoundSlot *)0x0;
    local_4c0 = (int *)0x0;
  }
                    /* try { // try from 00b59498 to 00b59504 has its CatchHandler @ 00b5fd15 */
  CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_b8);
  local_1ef0 = 0x20;
  local_1ee8 = 0;
  local_1ed8 = 0;
  local_1ee0 = 0;
  local_1e50 = (uint *)0x0;
  local_1ef8 = 0;
  local_1ed0[0] = 0;
  CEGUI::String::grow((ulong)&local_1ef8);
  puVar25 = local_1ed0;
  if (0x20 < local_1ef0) {
    puVar25 = local_1e50;
  }
  pcVar34 = "RotateLeft";
  do {
    bVar3 = *pcVar34;
    pcVar34 = pcVar34 + 1;
    *puVar25 = (uint)bVar3;
    puVar25 = puVar25 + 1;
  } while ((byte *)pcVar34 != (byte *)0xfef7f2);
  local_1ef8 = 10;
  puVar25 = local_1ea8;
  if (0x20 < local_1ef0) {
    puVar25 = local_1e50 + 10;
  }
  *puVar25 = 0;
                    /* try { // try from 00b59572 to 00b59576 has its CatchHandler @ 00b5ff95 */
  lVar32 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x28));
                    /* try { // try from 00b5957d to 00b595a2 has its CatchHandler @ 00b5fd15 */
  CEGUI::String::~String((String *)&local_1ef8);
  *(undefined1 *)(lVar32 + 0x213) = 0;
  CEGUI::Window::moveToFront();
  pcVar4 = *(code **)(*(long *)(lVar32 + 0x38) + 0x10);
  local_c8[0] = operator_new(0x20);
  lVar12 = lVar32 + 0x38;
  *local_c8[0] = &PTR__MemberFunctionSlot_00fefcd0;
  local_c8[0][2] = 0;
  local_c8[0][1] = handle_RotateLeft;
  local_c8[0][3] = this;
                    /* try { // try from 00b595e5 to 00b5961a has its CatchHandler @ 00b5ff9a */
  (*pcVar4)(&local_4d8,lVar12,CEGUI::Window::EventMouseButtonDown,(SubscriberSlot *)local_c8);
  if ((local_4d8 != (BoundSlot *)0x0) &&
     (iVar7 = *local_4d0, *local_4d0 = iVar7 + -1, iVar7 + -1 == 0)) {
    if (local_4d8 != (BoundSlot *)0x0) {
      CEGUI::BoundSlot::~BoundSlot(local_4d8);
      operator_delete(local_4d8);
    }
    operator_delete(local_4d0);
    local_4d8 = (BoundSlot *)0x0;
    local_4d0 = (int *)0x0;
  }
                    /* try { // try from 00b5964b to 00b59661 has its CatchHandler @ 00b5fd15 */
  CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_c8);
  pcVar4 = *(code **)(*(long *)(lVar32 + 0x38) + 0x10);
  local_d8[0] = operator_new(0x20);
  *local_d8[0] = &PTR__MemberFunctionSlot_00fefcd0;
  local_d8[0][2] = 0;
  local_d8[0][1] = handle_EndRotateLeft;
  local_d8[0][3] = this;
                    /* try { // try from 00b596a0 to 00b596d5 has its CatchHandler @ 00b60005 */
  (*pcVar4)(&local_4e8,lVar12,CEGUI::Window::EventMouseButtonUp,(SubscriberSlot *)local_d8);
  if ((local_4e8 != (BoundSlot *)0x0) &&
     (iVar7 = *local_4e0, *local_4e0 = iVar7 + -1, iVar7 + -1 == 0)) {
    if (local_4e8 != (BoundSlot *)0x0) {
      CEGUI::BoundSlot::~BoundSlot(local_4e8);
      operator_delete(local_4e8);
    }
    operator_delete(local_4e0);
    local_4e8 = (BoundSlot *)0x0;
    local_4e0 = (int *)0x0;
  }
                    /* try { // try from 00b59706 to 00b5971c has its CatchHandler @ 00b5fd15 */
  CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_d8);
  pcVar4 = *(code **)(*(long *)(lVar32 + 0x38) + 0x10);
  local_e8[0] = operator_new(0x20);
  *local_e8[0] = &PTR__MemberFunctionSlot_00fefcd0;
  local_e8[0][2] = 0;
  local_e8[0][1] = handle_EndRotateLeft;
  local_e8[0][3] = this;
                    /* try { // try from 00b5975b to 00b59790 has its CatchHandler @ 00b60015 */
  (*pcVar4)(&local_4f8,lVar12,CEGUI::Window::EventMouseLeaves,(SubscriberSlot *)local_e8);
  if ((local_4f8 != (BoundSlot *)0x0) &&
     (iVar7 = *local_4f0, *local_4f0 = iVar7 + -1, iVar7 + -1 == 0)) {
    if (local_4f8 != (BoundSlot *)0x0) {
      CEGUI::BoundSlot::~BoundSlot(local_4f8);
      operator_delete(local_4f8);
    }
    operator_delete(local_4f0);
    local_4f8 = (BoundSlot *)0x0;
    local_4f0 = (int *)0x0;
  }
                    /* try { // try from 00b597c1 to 00b5982d has its CatchHandler @ 00b5fd15 */
  CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_e8);
  local_1fa0 = 0x20;
  local_1f98 = 0;
  local_1f88 = 0;
  local_1f90 = 0;
  local_1f00 = (uint *)0x0;
  local_1fa8 = 0;
  local_1f80[0] = 0;
  CEGUI::String::grow((ulong)&local_1fa8);
  puVar25 = local_1f80;
  if (0x20 < local_1fa0) {
    puVar25 = local_1f00;
  }
  pcVar34 = "RotateRight";
  do {
    bVar3 = *pcVar34;
    pcVar34 = pcVar34 + 1;
    *puVar25 = (uint)bVar3;
    puVar25 = puVar25 + 1;
  } while ((byte *)pcVar34 != (byte *)0xfef7e7);
  local_1fa8 = 0xb;
  puVar25 = local_1f54;
  if (0x20 < local_1fa0) {
    puVar25 = local_1f00 + 0xb;
  }
  *puVar25 = 0;
                    /* try { // try from 00b5989a to 00b5989e has its CatchHandler @ 00b60186 */
  lVar32 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x28));
                    /* try { // try from 00b598a5 to 00b598ca has its CatchHandler @ 00b5fd15 */
  CEGUI::String::~String((String *)&local_1fa8);
  *(undefined1 *)(lVar32 + 0x213) = 0;
  CEGUI::Window::moveToFront();
  pcVar4 = *(code **)(*(long *)(lVar32 + 0x38) + 0x10);
  local_f8[0] = operator_new(0x20);
  lVar12 = lVar32 + 0x38;
  *local_f8[0] = &PTR__MemberFunctionSlot_00fefcd0;
  local_f8[0][2] = 0;
  local_f8[0][1] = handle_RotateRight;
  local_f8[0][3] = this;
                    /* try { // try from 00b5990d to 00b59942 has its CatchHandler @ 00b6018b */
  (*pcVar4)(&local_508,lVar12,CEGUI::Window::EventMouseButtonDown,(SubscriberSlot *)local_f8);
  if ((local_508 != (BoundSlot *)0x0) &&
     (iVar7 = *local_500, *local_500 = iVar7 + -1, iVar7 + -1 == 0)) {
    if (local_508 != (BoundSlot *)0x0) {
      CEGUI::BoundSlot::~BoundSlot(local_508);
      operator_delete(local_508);
    }
    operator_delete(local_500);
    local_508 = (BoundSlot *)0x0;
    local_500 = (int *)0x0;
  }
                    /* try { // try from 00b59973 to 00b59989 has its CatchHandler @ 00b5fd15 */
  CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_f8);
  pcVar4 = *(code **)(*(long *)(lVar32 + 0x38) + 0x10);
  local_108[0] = operator_new(0x20);
  *local_108[0] = &PTR__MemberFunctionSlot_00fefcd0;
  local_108[0][2] = 0;
  local_108[0][1] = handle_EndRotateRight;
  local_108[0][3] = this;
                    /* try { // try from 00b599c8 to 00b599fd has its CatchHandler @ 00b60195 */
  (*pcVar4)(&local_518,lVar12,CEGUI::Window::EventMouseButtonUp,(SubscriberSlot *)local_108);
  if ((local_518 != (BoundSlot *)0x0) &&
     (iVar7 = *local_510, *local_510 = iVar7 + -1, iVar7 + -1 == 0)) {
    if (local_518 != (BoundSlot *)0x0) {
      CEGUI::BoundSlot::~BoundSlot(local_518);
      operator_delete(local_518);
    }
    operator_delete(local_510);
    local_518 = (BoundSlot *)0x0;
    local_510 = (int *)0x0;
  }
                    /* try { // try from 00b59a2e to 00b59a44 has its CatchHandler @ 00b5fd15 */
  CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_108);
  pcVar4 = *(code **)(*(long *)(lVar32 + 0x38) + 0x10);
  local_118[0] = operator_new(0x20);
  *local_118[0] = &PTR__MemberFunctionSlot_00fefcd0;
  local_118[0][2] = 0;
  local_118[0][1] = handle_EndRotateRight;
  local_118[0][3] = this;
                    /* try { // try from 00b59a83 to 00b59ab8 has its CatchHandler @ 00b601a5 */
  (*pcVar4)(&local_528,lVar12,CEGUI::Window::EventMouseLeaves,(SubscriberSlot *)local_118);
  if ((local_528 != (BoundSlot *)0x0) &&
     (iVar7 = *local_520, *local_520 = iVar7 + -1, iVar7 + -1 == 0)) {
    if (local_528 != (BoundSlot *)0x0) {
      CEGUI::BoundSlot::~BoundSlot(local_528);
      operator_delete(local_528);
    }
    operator_delete(local_520);
    local_528 = (BoundSlot *)0x0;
    local_520 = (int *)0x0;
  }
                    /* try { // try from 00b59ae9 to 00b59c04 has its CatchHandler @ 00b5fd15 */
  CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_118);
  lVar12 = 0;
  uVar10 = 0;
  pCVar36 = this;
  do {
    *(undefined8 *)(this + lVar12 + 0x1028) = 0;
    *(undefined8 *)(this + lVar12 + 0x12b8) = 0;
    *(undefined8 *)(this + lVar12 + 0x17d8) = 0;
    *(undefined8 *)(this + lVar12 + 0x1548) = 0;
    if (*(long *)(*(long *)((long)&::KEquipmentIconName + lVar12) + -0x18) != 0) {
      uVar26 = (ulong)uVar10;
      local_2050 = 0x20;
      local_2048 = 0;
      local_2038 = 0;
      local_2040 = 0;
      local_1fb0 = (undefined4 *)0x0;
      local_2058 = 0;
      local_2030[0] = 0;
      lVar32 = *(long *)(*(long *)((long)&::KEquipmentIconName + lVar12) + -0x18);
      CEGUI::String::grow((ulong)&local_2058);
      puVar23 = local_1fb0;
      if (local_2050 < 0x21) {
        puVar23 = local_2030;
      }
      puVar23[lVar32] = 0;
      if (lVar32 != 0) {
        lVar35 = lVar32;
        do {
          lVar35 = lVar35 + -1;
          puVar23 = local_2030;
          if (0x20 < local_2050) {
            puVar23 = local_1fb0;
          }
          puVar23[lVar35] = (uint)*(byte *)((&::KEquipmentIconName)[uVar26] + lVar35);
        } while (lVar35 != 0);
      }
      local_2058 = lVar32;
                    /* try { // try from 00b59c87 to 00b59c8b has its CatchHandler @ 00b5ff2b */
      lVar35 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x28));
                    /* try { // try from 00b59c97 to 00b59cd3 has its CatchHandler @ 00b5fd15 */
      CEGUI::String::~String((String *)&local_2058);
      *(undefined1 *)(lVar35 + 0x213) = 0;
      CEGUI::Window::setWantsMultiClickEvents(SUB81(lVar35,0));
      *(CInventoryMenu **)(lVar35 + 0x1d8) = this + uVar26 * 4 + 0x80;
      pcVar4 = *(code **)(*(long *)(lVar35 + 0x38) + 0x10);
      local_128[0] = operator_new(0x20);
      lVar32 = lVar35 + 0x38;
      *local_128[0] = &PTR__MemberFunctionSlot_00fefcd0;
      local_128[0][2] = 0;
      local_128[0][1] = handle_ItemClick;
      local_128[0][3] = this;
                    /* try { // try from 00b59d13 to 00b59d4e has its CatchHandler @ 00b5ff40 */
      (*pcVar4)(&local_538,lVar32,CEGUI::Window::EventMouseButtonDown,local_128);
      pBVar6 = local_538;
      if ((local_538 != (BoundSlot *)0x0) &&
         (iVar7 = *local_530, *local_530 = iVar7 + -1, iVar7 + -1 == 0)) {
        if (local_538 != (BoundSlot *)0x0) {
          CEGUI::BoundSlot::~BoundSlot(local_538);
          operator_delete(pBVar6);
        }
        operator_delete(local_530);
        local_538 = (BoundSlot *)0x0;
        local_530 = (int *)0x0;
      }
                    /* try { // try from 00b59d86 to 00b59da1 has its CatchHandler @ 00b5fd15 */
      CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_128);
      pcVar4 = *(code **)(*(long *)(lVar35 + 0x38) + 0x10);
      local_138[0] = operator_new(0x20);
      *local_138[0] = &PTR__MemberFunctionSlot_00fefcd0;
      local_138[0][2] = 0;
      local_138[0][1] = handle_MouseOver;
      local_138[0][3] = this;
                    /* try { // try from 00b59ddd to 00b59e18 has its CatchHandler @ 00b5ff55 */
      (*pcVar4)(&local_548,lVar32,CEGUI::Window::EventMouseEnters,local_138);
      pBVar6 = local_548;
      if ((local_548 != (BoundSlot *)0x0) &&
         (iVar7 = *local_540, *local_540 = iVar7 + -1, iVar7 + -1 == 0)) {
        if (local_548 != (BoundSlot *)0x0) {
          CEGUI::BoundSlot::~BoundSlot(local_548);
          operator_delete(pBVar6);
        }
        operator_delete(local_540);
        local_548 = (BoundSlot *)0x0;
        local_540 = (int *)0x0;
      }
                    /* try { // try from 00b59e50 to 00b59e6b has its CatchHandler @ 00b5fd15 */
      CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_138);
      pcVar4 = *(code **)(*(long *)(lVar35 + 0x38) + 0x10);
      local_148[0] = operator_new(0x20);
      *local_148[0] = &PTR__MemberFunctionSlot_00fefcd0;
      local_148[0][2] = 0;
      local_148[0][1] = handle_MouseOver;
      local_148[0][3] = this;
                    /* try { // try from 00b59ea7 to 00b59ee2 has its CatchHandler @ 00b5ff6a */
      (*pcVar4)(&local_558,lVar32,CEGUI::Window::EventMouseMove,local_148);
      pBVar6 = local_558;
      if ((local_558 != (BoundSlot *)0x0) &&
         (iVar7 = *local_550, *local_550 = iVar7 + -1, iVar7 + -1 == 0)) {
        if (local_558 != (BoundSlot *)0x0) {
          CEGUI::BoundSlot::~BoundSlot(local_558);
          operator_delete(pBVar6);
        }
        operator_delete(local_550);
        local_558 = (BoundSlot *)0x0;
        local_550 = (int *)0x0;
      }
                    /* try { // try from 00b59f1a to 00b59f35 has its CatchHandler @ 00b5fd15 */
      CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_148);
      pcVar4 = *(code **)(*(long *)(lVar35 + 0x38) + 0x10);
      local_158[0] = operator_new(0x20);
      *local_158[0] = &PTR__MemberFunctionSlot_00fefcd0;
      local_158[0][2] = 0;
      local_158[0][1] = handle_MouseOut;
      local_158[0][3] = this;
                    /* try { // try from 00b59f71 to 00b59fa7 has its CatchHandler @ 00b5feda */
      (*pcVar4)(&local_568,lVar32,CEGUI::Window::EventMouseLeaves,local_158);
      pBVar6 = local_568;
      if ((local_568 != (BoundSlot *)0x0) &&
         (iVar7 = *local_560, *local_560 = iVar7 + -1, iVar7 + -1 == 0)) {
        if (local_568 != (BoundSlot *)0x0) {
          CEGUI::BoundSlot::~BoundSlot(local_568);
          operator_delete(pBVar6);
        }
        operator_delete(local_560);
        local_568 = (BoundSlot *)0x0;
        local_560 = (int *)0x0;
      }
                    /* try { // try from 00b59fdd to 00b5a056 has its CatchHandler @ 00b5fd15 */
      CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_158);
      CEGUI::Window::moveToFront();
      *(long *)(this + lVar12 + 0x1028) = lVar35;
      local_2100 = 0x20;
      local_20f8 = 0;
      local_20e8 = 0;
      local_20f0 = 0;
      local_2060 = (uint *)0x0;
      local_2108 = 0;
      local_20e0[0] = 0;
      CEGUI::String::grow((ulong)&local_2108);
      puVar25 = local_2060;
      if (local_2100 < 0x21) {
        puVar25 = local_20e0;
      }
      pbVar16 = (byte *)0xfd0c0d;
      do {
        bVar3 = *pbVar16;
        pbVar16 = pbVar16 + 1;
        *puVar25 = (uint)bVar3;
        puVar25 = puVar25 + 1;
      } while (pbVar16 != (byte *)0xfd0c12);
      local_2108 = 5;
      if (local_2100 < 0x21) {
        puVar25 = local_20cc;
      }
      else {
        puVar25 = local_2060 + 5;
      }
      *puVar25 = 0;
                    /* try { // try from 00b5a0d5 to 00b5a0d9 has its CatchHandler @ 00b5feef */
      CEGUI::PropertySet::getProperty((String *)&local_21b8);
      lVar32 = local_21b8;
                    /* try { // try from 00b5a0f9 to 00b5a0fd has its CatchHandler @ 00b5ff04 */
      CEGUI::String::grow((ulong)(this + uVar26 * 0xb0 + 0x1d08));
      *(long *)(pCVar36 + 0x1d08) = lVar32;
      if (*(ulong *)(pCVar36 + 0x1d10) < 0x21) {
        pCVar20 = this + uVar26 * 0xb0 + 0x1d30;
      }
      else {
        pCVar20 = *(CInventoryMenu **)(pCVar36 + 0x1db0);
      }
      *(undefined4 *)(pCVar20 + lVar32 * 4) = 0;
      if (local_21b0 < 0x21) {
        puVar31 = auStack_2190;
        if (0x20 < *(ulong *)(pCVar36 + 0x1d10)) goto LAB_00b5b28e;
LAB_00b5a153:
        pCVar20 = this + uVar26 * 0xb0 + 0x1d30;
      }
      else {
        puVar31 = local_2110;
        if (*(ulong *)(pCVar36 + 0x1d10) < 0x21) goto LAB_00b5a153;
LAB_00b5b28e:
        pCVar20 = *(CInventoryMenu **)(pCVar36 + 0x1db0);
      }
      memcpy(pCVar20,puVar31,lVar32 * 4);
                    /* try { // try from 00b5a174 to 00b5a178 has its CatchHandler @ 00b5feef */
      CEGUI::String::~String((String *)&local_21b8);
                    /* try { // try from 00b5a181 to 00b5a289 has its CatchHandler @ 00b5fd15 */
      CEGUI::String::~String((String *)&local_2108);
      plVar19 = (long *)CEGUI::Window::getTooltipText();
      lVar32 = *plVar19;
      CEGUI::String::grow((ulong)(this + uVar26 * 0xb0 + 0x5568));
      *(long *)(pCVar36 + 0x5568) = lVar32;
      if (*(ulong *)(pCVar36 + 0x5570) < 0x21) {
        pCVar20 = this + uVar26 * 0xb0 + 0x5590;
      }
      else {
        pCVar20 = *(CInventoryMenu **)(pCVar36 + 0x5610);
      }
      *(undefined4 *)(pCVar20 + lVar32 * 4) = 0;
      if ((ulong)plVar19[1] < 0x21) {
        plVar19 = plVar19 + 5;
        if (*(ulong *)(pCVar36 + 0x5570) < 0x21) goto LAB_00b5a203;
LAB_00b5b247:
        pCVar20 = *(CInventoryMenu **)(pCVar36 + 0x5610);
      }
      else {
        plVar19 = (long *)plVar19[0x15];
        if (0x20 < *(ulong *)(pCVar36 + 0x5570)) goto LAB_00b5b247;
LAB_00b5a203:
        pCVar20 = this + uVar26 * 0xb0 + 0x5590;
      }
      memcpy(pCVar20,plVar19,lVar32 * 4);
      *(undefined8 *)(this + lVar12 + 0x17d8) = 0;
      local_23c0 = 0x20;
      local_23b8 = 0;
      local_23a8 = 0;
      local_23b0 = 0;
      local_2320 = (undefined4 *)0x0;
      local_23c8 = 0;
      local_23a0[0] = 0;
      CEGUI::String::grow((ulong)&local_23c8);
      local_23c8 = 0;
      puVar23 = local_2320;
      if (local_23c0 < 0x21) {
        puVar23 = local_23a0;
      }
      *puVar23 = 0;
                    /* try { // try from 00b5a2cc to 00b5a2d0 has its CatchHandler @ 00b5ff16 */
      std::string::string((string *)local_168,"gui_",&local_3a);
                    /* try { // try from 00b5a2e1 to 00b5a2e5 has its CatchHandler @ 00b60325 */
      STRINGS::uniqueName((STRINGS *)local_178,(string *)local_168);
      local_2310 = 0x20;
      local_2308 = 0;
      local_22f8 = 0;
      local_2300 = 0;
      local_2270 = (undefined4 *)0x0;
      local_2318 = 0;
      local_22f0[0] = 0;
      lVar32 = *(long *)(local_178[0] + -0x18);
                    /* try { // try from 00b5a350 to 00b5a354 has its CatchHandler @ 00b6032d */
      CEGUI::String::grow((ulong)&local_2318);
      puVar23 = local_22f0;
      if (0x20 < local_2310) {
        puVar23 = local_2270;
      }
      puVar23[lVar32] = 0;
      lVar35 = lVar32;
      while (lVar35 != 0) {
        lVar35 = lVar35 + -1;
        puVar23 = local_22f0;
        if (0x20 < local_2310) {
          puVar23 = local_2270;
        }
        puVar23[lVar35] = (uint)*(byte *)(local_178[0] + lVar35);
      }
      pcVar30 = (char *)0x0;
      local_2260 = 0x20;
      local_2258 = 0;
      local_2248 = 0;
      pcVar34 = "GuiLook/StaticImage";
      local_2250 = 0;
      local_21c0 = (uint *)0x0;
      local_2268 = 0;
      local_2240[0] = 0;
      pcVar33 = "GuiLook/StaticImage";
      cVar2 = s_GuiLook_StaticImage_00fd0bff[0];
      while (pcVar34 = pcVar34 + 1, cVar2 != '\0') {
        pcVar30 = pcVar34 + -0xfd0bff;
        cVar2 = *pcVar34;
      }
      local_2318 = lVar32;
      if (pcVar30 == CEGUI::String::npos) {
                    /* try { // try from 00b5ea78 to 00b5ea7c has its CatchHandler @ 00b60625 */
        std::string::string((string *)local_388,"Length for utf8 encoded string can not be \'npos\'"
                            ,local_50);
        plVar24 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00b5ea90 to 00b5ea94 has its CatchHandler @ 00b605f0 */
        std::length_error::length_error(plVar24,(string *)local_388);
        if ((allocator *)(local_388[0] + -0x18) !=
            (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_388[0] + -8);
          iVar7 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar7 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_388[0] + -0x18));
          }
        }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00b5eabb to 00b5eabf has its CatchHandler @ 00b60092 */
        __cxa_throw(plVar24,&std::length_error::typeinfo,std::length_error::~length_error);
      }
      lVar32 = 0;
      pcVar34 = pcVar30;
      pbVar16 = (byte *)"GuiLook/StaticImage";
      while (pcVar34 != (char *)0x0) {
        bVar3 = *pbVar16;
        pcVar13 = pcVar34 + -1;
        pbVar28 = pbVar16 + 1;
        if ((char)bVar3 < '\0') {
          if (bVar3 < 0xe0) {
            pcVar13 = pcVar34 + -2;
            pbVar28 = pbVar16 + 2;
          }
          else if (bVar3 < 0xf0) {
            pcVar13 = pcVar34 + -3;
            pbVar28 = pbVar16 + 3;
          }
          else {
            pcVar13 = pcVar34 + -3;
            pbVar28 = pbVar16 + 4;
          }
        }
        lVar32 = lVar32 + 1;
        pcVar34 = pcVar13;
        pbVar16 = pbVar28;
      }
                    /* try { // try from 00b5a4fb to 00b5a4ff has its CatchHandler @ 00b60092 */
      CEGUI::String::grow((ulong)&local_2268);
      puVar25 = local_21c0;
      if (local_2260 < 0x21) {
        puVar25 = local_2240;
      }
      if (pcVar30 == (char *)0x0) {
        pcVar34 = "GuiLook/StaticImage";
        if (s_GuiLook_StaticImage_00fd0bff[0] != '\0') {
          do {
            pcVar34 = pcVar34 + 1;
            pcVar30 = pcVar34 + -0xfd0bff;
          } while (*pcVar34 != '\0');
          bVar37 = pcVar30 != (char *)0x0 && local_2260 != 0;
          goto LAB_00b5a52d;
        }
      }
      else {
        bVar37 = local_2260 != 0;
LAB_00b5a52d:
        if (bVar37) {
          pcVar34 = (char *)0x0;
          uVar9 = 0;
          uVar26 = local_2260;
          do {
            bVar3 = pcVar34[0xfd0bff];
            uVar27 = (uint)bVar3;
            uVar11 = uVar9 + 1;
            if ((char)bVar3 < '\0') {
              uVar27 = (uint)bVar3;
              if (0xdf < bVar3) {
                if (bVar3 < 0xf0) {
                  uVar29 = (ulong)uVar11;
                  uVar11 = uVar9 + 3;
                  uVar27 = (byte)"GuiLook/StaticImage"[uVar9 + 2] & 0x3f | (uVar27 & 0xf) << 0xc |
                           ((byte)"GuiLook/StaticImage"[uVar29] & 0x3f) << 6;
                }
                else {
                  uVar29 = (ulong)uVar11;
                  uVar11 = uVar9 + 4;
                  uVar27 = ((byte)"GuiLook/StaticImage"[uVar29] & 0x3f) << 0xc |
                           (byte)"GuiLook/StaticImage"[uVar9 + 3] & 0x3f | (uVar27 & 7) << 0x12 |
                           ((byte)"GuiLook/StaticImage"[uVar9 + 2] & 0x3f) << 6;
                }
                goto LAB_00b5a543;
              }
              uVar9 = uVar9 + 2;
              *puVar25 = (byte)"GuiLook/StaticImage"[uVar11] & 0x3f | (uVar27 & 0x1f) << 6;
            }
            else {
LAB_00b5a543:
              *puVar25 = uVar27;
              uVar9 = uVar11;
            }
            pcVar34 = (char *)(ulong)uVar9;
            if ((pcVar30 <= pcVar34) || (uVar26 = uVar26 - 1, uVar26 == 0)) break;
            puVar25 = puVar25 + 1;
          } while( true );
        }
      }
      puVar25 = local_21c0;
      if (local_2260 < 0x21) {
        puVar25 = local_2240;
      }
      puVar25[lVar32] = 0;
      local_2268 = lVar32;
                    /* try { // try from 00b5a5ea to 00b5a5ee has its CatchHandler @ 00b602c6 */
      pUVar21 = (UVector2 *)
                CEGUI::WindowManager::createWindow
                          (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,
                           (String *)&local_2268,(String *)&local_2318);
                    /* try { // try from 00b5a5fa to 00b5a5fe has its CatchHandler @ 00b60092 */
      CEGUI::String::~String((String *)&local_2268);
                    /* try { // try from 00b5a607 to 00b5a60b has its CatchHandler @ 00b6032d */
      CEGUI::String::~String((String *)&local_2318);
      if ((allocator *)(local_178[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_178[0] + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_178[0] + -0x18));
        }
      }
      if ((allocator *)(local_168[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_168[0] + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_168[0] + -0x18));
        }
      }
                    /* try { // try from 00b5a647 to 00b5a6a8 has its CatchHandler @ 00b5fd15 */
      CEGUI::String::~String((String *)&local_23c8);
      CEGUI::Window::addChildWindow(*(Window **)(this + 0x28));
      pUVar21[0x213] = (UVector2)0x0;
      CEGUI::Window::setWantsMultiClickEvents(SUB81(pUVar21,0));
      pUVar21[0x3e2] = (UVector2)0x1;
      CEGUI::EventSet::setMutedState((bool)(SUB81(pUVar21,0) + '8'));
      CEGUI::Window::getPosition();
      CEGUI::Window::setPosition(pUVar21);
      CEGUI::Window::getSize();
                    /* try { // try from 00b5a6af to 00b5a6b3 has its CatchHandler @ 00b602a6 */
      CEGUI::Window::setSize(pUVar21);
      *(UVector2 **)(this + lVar12 + 0x12b8) = pUVar21;
      local_25d0 = 0x20;
      local_25c8 = 0;
      local_25b8 = 0;
      local_25c0 = 0;
      local_2530 = (undefined4 *)0x0;
      local_25d8 = 0;
      local_25b0[0] = 0;
                    /* try { // try from 00b5a719 to 00b5a71d has its CatchHandler @ 00b5fd15 */
      CEGUI::String::grow((ulong)&local_25d8);
      local_25d8 = 0;
      puVar23 = local_2530;
      if (local_25d0 < 0x21) {
        puVar23 = local_25b0;
      }
      *puVar23 = 0;
                    /* try { // try from 00b5a760 to 00b5a764 has its CatchHandler @ 00b602b6 */
      std::string::string((string *)local_188,"gui_",&local_3b);
                    /* try { // try from 00b5a775 to 00b5a779 has its CatchHandler @ 00b602be */
      STRINGS::uniqueName((STRINGS *)local_198,(string *)local_188);
      local_2520 = 0x20;
      local_2518 = 0;
      local_2508 = 0;
      local_2510 = 0;
      local_2480 = (undefined4 *)0x0;
      local_2528 = 0;
      local_2500[0] = 0;
      lVar32 = *(long *)(local_198[0] + -0x18);
                    /* try { // try from 00b5a7e4 to 00b5a7e8 has its CatchHandler @ 00b600ea */
      CEGUI::String::grow((ulong)&local_2528);
      puVar23 = local_2500;
      if (0x20 < local_2520) {
        puVar23 = local_2480;
      }
      puVar23[lVar32] = 0;
      lVar35 = lVar32;
      while (lVar35 != 0) {
        lVar35 = lVar35 + -1;
        puVar23 = local_2500;
        if (0x20 < local_2520) {
          puVar23 = local_2480;
        }
        puVar23[lVar35] = (uint)*(byte *)(local_198[0] + lVar35);
      }
      pcVar30 = (char *)0x0;
      local_2470 = 0x20;
      local_2468 = 0;
      local_2458 = 0;
      pcVar34 = "GuiLook/StaticImage";
      local_2460 = 0;
      local_23d0 = (uint *)0x0;
      local_2478 = 0;
      local_2450[0] = 0;
      cVar2 = s_GuiLook_StaticImage_00fd0bff[0];
      while (pcVar34 = pcVar34 + 1, cVar2 != '\0') {
        pcVar30 = pcVar34 + -0xfd0bff;
        cVar2 = *pcVar34;
      }
      local_2528 = lVar32;
      if (pcVar30 == CEGUI::String::npos) {
                    /* try { // try from 00b5eb9e to 00b5eba2 has its CatchHandler @ 00b60558 */
        std::string::string((string *)local_398,"Length for utf8 encoded string can not be \'npos\'"
                            ,local_54);
        plVar24 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00b5ebb6 to 00b5ebba has its CatchHandler @ 00b60503 */
        std::length_error::length_error(plVar24,(string *)local_398);
        if ((allocator *)(local_398[0] + -0x18) !=
            (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_398[0] + -8);
          iVar7 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar7 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_398[0] + -0x18));
          }
        }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00b5ebe1 to 00b5ebe5 has its CatchHandler @ 00b60138 */
        __cxa_throw(plVar24,&std::length_error::typeinfo,std::length_error::~length_error);
      }
      lVar32 = 0;
      pcVar34 = pcVar30;
      pbVar16 = (byte *)"GuiLook/StaticImage";
      while (pcVar34 != (char *)0x0) {
        bVar3 = *pbVar16;
        pcVar13 = pcVar34 + -1;
        pbVar28 = pbVar16 + 1;
        if ((char)bVar3 < '\0') {
          if (bVar3 < 0xe0) {
            pcVar13 = pcVar34 + -2;
            pbVar28 = pbVar16 + 2;
          }
          else if (bVar3 < 0xf0) {
            pcVar13 = pcVar34 + -3;
            pbVar28 = pbVar16 + 3;
          }
          else {
            pcVar13 = pcVar34 + -3;
            pbVar28 = pbVar16 + 4;
          }
        }
        lVar32 = lVar32 + 1;
        pcVar34 = pcVar13;
        pbVar16 = pbVar28;
      }
                    /* try { // try from 00b5a98b to 00b5a98f has its CatchHandler @ 00b60138 */
      CEGUI::String::grow((ulong)&local_2478);
      puVar25 = local_23d0;
      if (local_2470 < 0x21) {
        puVar25 = local_2450;
      }
      if (pcVar30 == (char *)0x0) {
        pcVar34 = "GuiLook/StaticImage";
        if (s_GuiLook_StaticImage_00fd0bff[0] != '\0') {
          do {
            pcVar34 = pcVar34 + 1;
            pcVar30 = pcVar34 + -0xfd0bff;
          } while (*pcVar34 != '\0');
          bVar37 = pcVar30 != (char *)0x0 && local_2470 != 0;
          goto LAB_00b5a9bd;
        }
      }
      else {
        bVar37 = local_2470 != 0;
LAB_00b5a9bd:
        if (bVar37) {
          pcVar34 = (char *)0x0;
          uVar9 = 0;
          uVar26 = local_2470;
          do {
            bVar3 = pcVar34[0xfd0bff];
            uVar27 = (uint)bVar3;
            uVar11 = uVar9 + 1;
            if ((char)bVar3 < '\0') {
              uVar27 = (uint)bVar3;
              if (0xdf < bVar3) {
                if (bVar3 < 0xf0) {
                  uVar29 = (ulong)uVar11;
                  uVar11 = uVar9 + 3;
                  uVar27 = (byte)"GuiLook/StaticImage"[uVar9 + 2] & 0x3f | (uVar27 & 0xf) << 0xc |
                           ((byte)"GuiLook/StaticImage"[uVar29] & 0x3f) << 6;
                }
                else {
                  uVar29 = (ulong)uVar11;
                  uVar11 = uVar9 + 4;
                  uVar27 = ((byte)"GuiLook/StaticImage"[uVar29] & 0x3f) << 0xc |
                           (byte)"GuiLook/StaticImage"[uVar9 + 3] & 0x3f | (uVar27 & 7) << 0x12 |
                           ((byte)"GuiLook/StaticImage"[uVar9 + 2] & 0x3f) << 6;
                }
                goto LAB_00b5a9d3;
              }
              uVar9 = uVar9 + 2;
              *puVar25 = (byte)"GuiLook/StaticImage"[uVar11] & 0x3f | (uVar27 & 0x1f) << 6;
            }
            else {
LAB_00b5a9d3:
              *puVar25 = uVar27;
              uVar9 = uVar11;
            }
            pcVar34 = (char *)(ulong)uVar9;
            if ((pcVar30 <= pcVar34) || (uVar26 = uVar26 - 1, uVar26 == 0)) break;
            puVar25 = puVar25 + 1;
          } while( true );
        }
      }
      puVar25 = local_23d0;
      if (local_2470 < 0x21) {
        puVar25 = local_2450;
      }
      puVar25[lVar32] = 0;
      local_2478 = lVar32;
                    /* try { // try from 00b5aa7a to 00b5aa7e has its CatchHandler @ 00b60225 */
      pUVar21 = (UVector2 *)
                CEGUI::WindowManager::createWindow
                          (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,
                           (String *)&local_2478,(String *)&local_2528);
                    /* try { // try from 00b5aa8a to 00b5aa8e has its CatchHandler @ 00b60138 */
      CEGUI::String::~String((String *)&local_2478);
                    /* try { // try from 00b5aa97 to 00b5aa9b has its CatchHandler @ 00b600ea */
      CEGUI::String::~String((String *)&local_2528);
      if ((allocator *)(local_198[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_198[0] + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_198[0] + -0x18));
        }
      }
      if ((allocator *)(local_188[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_188[0] + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_188[0] + -0x18));
        }
      }
                    /* try { // try from 00b5aad8 to 00b5ab39 has its CatchHandler @ 00b5fd15 */
      CEGUI::String::~String((String *)&local_25d8);
      CEGUI::Window::addChildWindow(*(Window **)(this + 0x38));
      pUVar21[0x213] = (UVector2)0x0;
      CEGUI::Window::setWantsMultiClickEvents(SUB81(pUVar21,0));
      pUVar21[0x3e2] = (UVector2)0x1;
      CEGUI::EventSet::setMutedState((bool)(SUB81(pUVar21,0) + '8'));
      CEGUI::Window::getPosition();
      CEGUI::Window::setPosition(pUVar21);
      CEGUI::Window::getSize();
                    /* try { // try from 00b5ab40 to 00b5ab44 has its CatchHandler @ 00b601e4 */
      CEGUI::Window::setSize(pUVar21);
      *(UVector2 **)(this + lVar12 + 0x1548) = pUVar21;
      local_27e0 = 0x20;
      local_27d8 = 0;
      local_27c8 = 0;
      local_27d0 = 0;
      local_2740 = (undefined4 *)0x0;
      local_27e8 = 0;
      local_27c0[0] = 0;
                    /* try { // try from 00b5abaa to 00b5abae has its CatchHandler @ 00b5fd15 */
      CEGUI::String::grow((ulong)&local_27e8);
      local_27e8 = 0;
      puVar23 = local_2740;
      if (local_27e0 < 0x21) {
        puVar23 = local_27c0;
      }
      *puVar23 = 0;
                    /* try { // try from 00b5abf1 to 00b5abf5 has its CatchHandler @ 00b601f4 */
      std::string::string((string *)local_1a8,"gui_",&local_3c);
                    /* try { // try from 00b5ac06 to 00b5ac0a has its CatchHandler @ 00b60201 */
      STRINGS::uniqueName((STRINGS *)local_1b8,(string *)local_1a8);
      local_2730 = 0x20;
      local_2728 = 0;
      local_2718 = 0;
      local_2720 = 0;
      local_2690 = (undefined4 *)0x0;
      local_2738 = 0;
      local_2710[0] = 0;
      lVar32 = *(long *)(local_1b8[0] + -0x18);
                    /* try { // try from 00b5ac75 to 00b5ac79 has its CatchHandler @ 00b60209 */
      CEGUI::String::grow((ulong)&local_2738);
      puVar23 = local_2710;
      if (0x20 < local_2730) {
        puVar23 = local_2690;
      }
      puVar23[lVar32] = 0;
      lVar35 = lVar32;
      while (lVar35 != 0) {
        lVar35 = lVar35 + -1;
        puVar23 = local_2710;
        if (0x20 < local_2730) {
          puVar23 = local_2690;
        }
        puVar23[lVar35] = (uint)*(byte *)(local_1b8[0] + lVar35);
      }
      pcVar30 = (char *)0x0;
      local_2680 = 0x20;
      local_2678 = 0;
      local_2668 = 0;
      pcVar34 = "GuiLook/StaticImage";
      local_2670 = 0;
      local_25e0 = (uint *)0x0;
      local_2688 = 0;
      local_2660[0] = 0;
      cVar2 = s_GuiLook_StaticImage_00fd0bff[0];
      while (pcVar34 = pcVar34 + 1, cVar2 != '\0') {
        pcVar30 = pcVar34 + -0xfd0bff;
        cVar2 = *pcVar34;
      }
      local_2738 = lVar32;
      if (pcVar30 == CEGUI::String::npos) {
                    /* try { // try from 00b5ec78 to 00b5ec7c has its CatchHandler @ 00b60485 */
        std::string::string((string *)local_3a8,"Length for utf8 encoded string can not be \'npos\'"
                            ,local_58);
        plVar24 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00b5ec90 to 00b5ec94 has its CatchHandler @ 00b60450 */
        std::length_error::length_error(plVar24,(string *)local_3a8);
        if ((allocator *)(local_3a8[0] + -0x18) !=
            (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_3a8[0] + -8);
          iVar7 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar7 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_3a8[0] + -0x18));
          }
        }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00b5ecbb to 00b5ecbf has its CatchHandler @ 00b6014a */
        __cxa_throw(plVar24,&std::length_error::typeinfo,std::length_error::~length_error);
      }
      lVar32 = 0;
      pcVar34 = pcVar30;
      pbVar16 = (byte *)"GuiLook/StaticImage";
      while (pcVar34 != (char *)0x0) {
        bVar3 = *pbVar16;
        pcVar13 = pcVar34 + -1;
        pbVar28 = pbVar16 + 1;
        if ((char)bVar3 < '\0') {
          if (bVar3 < 0xe0) {
            pcVar13 = pcVar34 + -2;
            pbVar28 = pbVar16 + 2;
          }
          else if (bVar3 < 0xf0) {
            pcVar13 = pcVar34 + -3;
            pbVar28 = pbVar16 + 3;
          }
          else {
            pcVar13 = pcVar34 + -3;
            pbVar28 = pbVar16 + 4;
          }
        }
        lVar32 = lVar32 + 1;
        pcVar34 = pcVar13;
        pbVar16 = pbVar28;
      }
                    /* try { // try from 00b5ae1b to 00b5ae1f has its CatchHandler @ 00b6014a */
      CEGUI::String::grow((ulong)&local_2688);
      puVar25 = local_25e0;
      if (local_2680 < 0x21) {
        puVar25 = local_2660;
      }
      if (pcVar30 == (char *)0x0) {
        if (s_GuiLook_StaticImage_00fd0bff[0] != '\0') {
          do {
            pcVar33 = pcVar33 + 1;
            pcVar30 = pcVar33 + -0xfd0bff;
          } while (*pcVar33 != '\0');
          bVar37 = pcVar30 != (char *)0x0 && local_2680 != 0;
          goto LAB_00b5ae4d;
        }
      }
      else {
        bVar37 = local_2680 != 0;
LAB_00b5ae4d:
        if (bVar37) {
          pcVar34 = (char *)0x0;
          uVar9 = 0;
          uVar26 = local_2680;
          do {
            bVar3 = pcVar34[0xfd0bff];
            uVar27 = (uint)bVar3;
            uVar11 = uVar9 + 1;
            if ((char)bVar3 < '\0') {
              uVar27 = (uint)bVar3;
              if (0xdf < bVar3) {
                if (bVar3 < 0xf0) {
                  uVar29 = (ulong)uVar11;
                  uVar11 = uVar9 + 3;
                  uVar27 = (byte)"GuiLook/StaticImage"[uVar9 + 2] & 0x3f | (uVar27 & 0xf) << 0xc |
                           ((byte)"GuiLook/StaticImage"[uVar29] & 0x3f) << 6;
                }
                else {
                  uVar29 = (ulong)uVar11;
                  uVar11 = uVar9 + 4;
                  uVar27 = ((byte)"GuiLook/StaticImage"[uVar29] & 0x3f) << 0xc |
                           (byte)"GuiLook/StaticImage"[uVar9 + 3] & 0x3f | (uVar27 & 7) << 0x12 |
                           ((byte)"GuiLook/StaticImage"[uVar9 + 2] & 0x3f) << 6;
                }
                goto LAB_00b5ae63;
              }
              uVar9 = uVar9 + 2;
              *puVar25 = (byte)"GuiLook/StaticImage"[uVar11] & 0x3f | (uVar27 & 0x1f) << 6;
            }
            else {
LAB_00b5ae63:
              *puVar25 = uVar27;
              uVar9 = uVar11;
            }
            pcVar34 = (char *)(ulong)uVar9;
            if ((pcVar30 <= pcVar34) || (uVar26 = uVar26 - 1, uVar26 == 0)) break;
            puVar25 = puVar25 + 1;
          } while( true );
        }
      }
      puVar25 = local_25e0;
      if (local_2680 < 0x21) {
        puVar25 = local_2660;
      }
      puVar25[lVar32] = 0;
      local_2688 = lVar32;
                    /* try { // try from 00b5af0a to 00b5af0e has its CatchHandler @ 00b603a3 */
      pUVar21 = (UVector2 *)
                CEGUI::WindowManager::createWindow
                          (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,
                           (String *)&local_2688,(String *)&local_2738);
                    /* try { // try from 00b5af1a to 00b5af1e has its CatchHandler @ 00b6014a */
      CEGUI::String::~String((String *)&local_2688);
                    /* try { // try from 00b5af27 to 00b5af2b has its CatchHandler @ 00b60209 */
      CEGUI::String::~String((String *)&local_2738);
      if ((allocator *)(local_1b8[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_1b8[0] + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_1b8[0] + -0x18));
        }
      }
      if ((allocator *)(local_1a8[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_1a8[0] + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_1a8[0] + -0x18));
        }
      }
                    /* try { // try from 00b5af68 to 00b5afc9 has its CatchHandler @ 00b5fd15 */
      CEGUI::String::~String((String *)&local_27e8);
      CEGUI::Window::addChildWindow(*(Window **)(this + 0x40));
      pUVar21[0x213] = (UVector2)0x0;
      CEGUI::Window::setWantsMultiClickEvents(SUB81(pUVar21,0));
      pUVar21[0x3e2] = (UVector2)0x1;
      CEGUI::EventSet::setMutedState((bool)(SUB81(pUVar21,0) + '8'));
      CEGUI::Window::getPosition();
      CEGUI::Window::setPosition(pUVar21);
      CEGUI::Window::getSize();
                    /* try { // try from 00b5afd0 to 00b5afd4 has its CatchHandler @ 00b60215 */
      CEGUI::Window::setSize(pUVar21);
      *(UVector2 **)(this + lVar12 + 0x1a68) = pUVar21;
    }
    uVar10 = uVar10 + 1;
    lVar12 = lVar12 + 8;
    pCVar36 = pCVar36 + 0xb0;
  } while (uVar10 != 0xc);
  iVar7 = 0;
  pCVar36 = this;
  do {
    *(int *)(pCVar36 + 0x80) = iVar7;
    iVar7 = iVar7 + 1;
    pCVar36 = pCVar36 + 4;
  } while (iVar7 != 1000);
  iVar8 = 100;
  iVar7 = 0;
  do {
    lVar12 = (long)iVar7;
    iVar7 = iVar7 + 1;
    iVar8 = iVar8 + -1;
    *(long *)(this + lVar12 * 8 + 0x8de8) = lVar12;
  } while (iVar8 != 0);
  local_2890 = 0x20;
  local_2888 = 0;
  local_2878 = 0;
  local_2880 = 0;
  local_27f0 = (uint *)0x0;
  local_2898 = 0;
  local_2870[0] = 0;
                    /* try { // try from 00b5b69e to 00b5b6a2 has its CatchHandler @ 00b5fd15 */
  CEGUI::String::grow((ulong)&local_2898);
  puVar25 = local_2870;
  if (0x20 < local_2890) {
    puVar25 = local_27f0;
  }
  pcVar34 = "TabBackpack";
  do {
    bVar3 = *pcVar34;
    pcVar34 = pcVar34 + 1;
    *puVar25 = (uint)bVar3;
    puVar25 = puVar25 + 1;
  } while ((byte *)pcVar34 != (byte *)0xfef7db);
  local_2898 = 0xb;
  puVar25 = local_2844;
  if (0x20 < local_2890) {
    puVar25 = local_27f0 + 0xb;
  }
  *puVar25 = 0;
                    /* try { // try from 00b5b709 to 00b5b70d has its CatchHandler @ 00b5fd05 */
  uVar14 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x48));
  *(undefined8 *)(this + 0x9120) = uVar14;
                    /* try { // try from 00b5b718 to 00b5b784 has its CatchHandler @ 00b5fd15 */
  CEGUI::String::~String((String *)&local_2898);
  local_2940 = 0x20;
  local_2938 = 0;
  local_2928 = 0;
  local_2930 = 0;
  local_28a0 = (uint *)0x0;
  local_2948 = 0;
  local_2920[0] = 0;
  CEGUI::String::grow((ulong)&local_2948);
  puVar25 = local_2920;
  if (0x20 < local_2940) {
    puVar25 = local_28a0;
  }
  pcVar34 = "UnselectedImage";
  do {
    bVar3 = *pcVar34;
    pcVar34 = pcVar34 + 1;
    *puVar25 = (uint)bVar3;
    puVar25 = puVar25 + 1;
  } while ((byte *)pcVar34 != (byte *)0xfef76b);
  local_2948 = 0xf;
  puVar25 = local_28e4;
  if (0x20 < local_2940) {
    puVar25 = local_28a0 + 0xf;
  }
  *puVar25 = 0;
                    /* try { // try from 00b5b807 to 00b5b80b has its CatchHandler @ 00b5fcf9 */
  CEGUI::PropertySet::getProperty((String *)&local_29f8);
                    /* try { // try from 00b5b81e to 00b5b822 has its CatchHandler @ 00b5fcf4 */
  CEGUI::String::grow((ulong)(this + 0x91b0));
  *(long *)(this + 0x91b0) = local_29f8;
  pCVar36 = this + 0x91d8;
  if (0x20 < *(ulong *)(this + 0x91b8)) {
    pCVar36 = *(CInventoryMenu **)(this + 0x9258);
  }
  *(undefined4 *)(pCVar36 + local_29f8 * 4) = 0;
  puVar31 = local_29d0;
  if (0x20 < local_29f0) {
    puVar31 = local_2950;
  }
  pCVar36 = this + 0x91d8;
  if (0x20 < *(ulong *)(this + 0x91b8)) {
    pCVar36 = *(CInventoryMenu **)(this + 0x9258);
  }
  memcpy(pCVar36,puVar31,local_29f8 * 4);
                    /* try { // try from 00b5b889 to 00b5b88d has its CatchHandler @ 00b5fcf9 */
  CEGUI::String::~String((String *)&local_29f8);
                    /* try { // try from 00b5b891 to 00b5b8fd has its CatchHandler @ 00b5fd15 */
  CEGUI::String::~String((String *)&local_2948);
  local_2aa0 = 0x20;
  local_2a98 = 0;
  local_2a88 = 0;
  local_2a90 = 0;
  local_2a00 = (uint *)0x0;
  local_2aa8 = 0;
  local_2a80[0] = 0;
  CEGUI::String::grow((ulong)&local_2aa8);
  puVar25 = local_2a80;
  if (0x20 < local_2aa0) {
    puVar25 = local_2a00;
  }
  pcVar34 = "SelectedImage";
  do {
    bVar3 = *pcVar34;
    pcVar34 = pcVar34 + 1;
    *puVar25 = (uint)bVar3;
    puVar25 = puVar25 + 1;
  } while ((byte *)pcVar34 != (byte *)0xfef7be);
  local_2aa8 = 0xd;
  puVar25 = local_2a4c;
  if (0x20 < local_2aa0) {
    puVar25 = local_2a00 + 0xd;
  }
  *puVar25 = 0;
                    /* try { // try from 00b5b977 to 00b5b97b has its CatchHandler @ 00b5fcf2 */
  CEGUI::PropertySet::getProperty((String *)&local_2b58);
                    /* try { // try from 00b5b98e to 00b5b992 has its CatchHandler @ 00b5fce5 */
  CEGUI::String::grow((ulong)(this + 0x93c0));
  *(long *)(this + 0x93c0) = local_2b58;
  pCVar36 = this + 0x93e8;
  if (0x20 < *(ulong *)(this + 0x93c8)) {
    pCVar36 = *(CInventoryMenu **)(this + 0x9468);
  }
  *(undefined4 *)(pCVar36 + local_2b58 * 4) = 0;
  puVar31 = local_2b30;
  if (0x20 < local_2b50) {
    puVar31 = local_2ab0;
  }
  pCVar36 = this + 0x93e8;
  if (0x20 < *(ulong *)(this + 0x93c8)) {
    pCVar36 = *(CInventoryMenu **)(this + 0x9468);
  }
  memcpy(pCVar36,puVar31,local_2b58 * 4);
                    /* try { // try from 00b5b9f9 to 00b5b9fd has its CatchHandler @ 00b5fcf2 */
  CEGUI::String::~String((String *)&local_2b58);
                    /* try { // try from 00b5ba01 to 00b5ba6d has its CatchHandler @ 00b5fd15 */
  CEGUI::String::~String((String *)&local_2aa8);
  local_2c00 = 0x20;
  local_2bf8 = 0;
  local_2be8 = 0;
  local_2bf0 = 0;
  local_2b60 = (uint *)0x0;
  local_2c08 = 0;
  local_2be0[0] = 0;
  CEGUI::String::grow((ulong)&local_2c08);
  puVar25 = local_2be0;
  if (0x20 < local_2c00) {
    puVar25 = local_2b60;
  }
  pcVar34 = "TabSpell";
  do {
    bVar3 = *pcVar34;
    pcVar34 = pcVar34 + 1;
    *puVar25 = (uint)bVar3;
    puVar25 = puVar25 + 1;
  } while ((byte *)pcVar34 != (byte *)0xfef7cf);
  local_2c08 = 8;
  puVar25 = local_2bc0;
  if (0x20 < local_2c00) {
    puVar25 = local_2b60 + 8;
  }
  *puVar25 = 0;
                    /* try { // try from 00b5bad9 to 00b5badd has its CatchHandler @ 00b5fcd6 */
  uVar14 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x48));
  *(undefined8 *)(this + 0x9128) = uVar14;
                    /* try { // try from 00b5bae8 to 00b5bb54 has its CatchHandler @ 00b5fd15 */
  CEGUI::String::~String((String *)&local_2c08);
  local_2cb0 = 0x20;
  local_2ca8 = 0;
  local_2c98 = 0;
  local_2ca0 = 0;
  local_2c10 = (uint *)0x0;
  local_2cb8 = 0;
  local_2c90[0] = 0;
  CEGUI::String::grow((ulong)&local_2cb8);
  puVar25 = local_2c90;
  if (0x20 < local_2cb0) {
    puVar25 = local_2c10;
  }
  pcVar34 = "UnselectedImage";
  do {
    bVar3 = *pcVar34;
    pcVar34 = pcVar34 + 1;
    *puVar25 = (uint)bVar3;
    puVar25 = puVar25 + 1;
  } while ((byte *)pcVar34 != (byte *)0xfef76b);
  local_2cb8 = 0xf;
  puVar25 = local_2c54;
  if (0x20 < local_2cb0) {
    puVar25 = local_2c10 + 0xf;
  }
  *puVar25 = 0;
                    /* try { // try from 00b5bbcc to 00b5bbd0 has its CatchHandler @ 00b5fcd4 */
  CEGUI::PropertySet::getProperty((String *)&local_2d68);
                    /* try { // try from 00b5bbe3 to 00b5bbe7 has its CatchHandler @ 00b5fcd2 */
  CEGUI::String::grow((ulong)(this + 0x9260));
  *(long *)(this + 0x9260) = local_2d68;
  pCVar36 = this + 0x9288;
  if (0x20 < *(ulong *)(this + 0x9268)) {
    pCVar36 = *(CInventoryMenu **)(this + 0x9308);
  }
  *(undefined4 *)(pCVar36 + local_2d68 * 4) = 0;
  puVar31 = local_2d40;
  if (0x20 < local_2d60) {
    puVar31 = local_2cc0;
  }
  pCVar36 = this + 0x9288;
  if (0x20 < *(ulong *)(this + 0x9268)) {
    pCVar36 = *(CInventoryMenu **)(this + 0x9308);
  }
  memcpy(pCVar36,puVar31,local_2d68 * 4);
                    /* try { // try from 00b5bc4e to 00b5bc52 has its CatchHandler @ 00b5fcd4 */
  CEGUI::String::~String((String *)&local_2d68);
                    /* try { // try from 00b5bc56 to 00b5bcc2 has its CatchHandler @ 00b5fd15 */
  CEGUI::String::~String((String *)&local_2cb8);
  local_2e10 = 0x20;
  local_2e08 = 0;
  local_2df8 = 0;
  local_2e00 = 0;
  local_2d70 = (uint *)0x0;
  local_2e18 = 0;
  local_2df0[0] = 0;
  CEGUI::String::grow((ulong)&local_2e18);
  puVar25 = local_2df0;
  if (0x20 < local_2e10) {
    puVar25 = local_2d70;
  }
  pcVar34 = "SelectedImage";
  do {
    bVar3 = *pcVar34;
    pcVar34 = pcVar34 + 1;
    *puVar25 = (uint)bVar3;
    puVar25 = puVar25 + 1;
  } while ((byte *)pcVar34 != (byte *)0xfef7be);
  local_2e18 = 0xd;
  puVar25 = local_2dbc;
  if (0x20 < local_2e10) {
    puVar25 = local_2d70 + 0xd;
  }
  *puVar25 = 0;
                    /* try { // try from 00b5bd34 to 00b5bd38 has its CatchHandler @ 00b5fccb */
  CEGUI::PropertySet::getProperty((String *)&local_2ec8);
                    /* try { // try from 00b5bd4b to 00b5bd4f has its CatchHandler @ 00b5fcb3 */
  CEGUI::String::grow((ulong)(this + 38000));
  *(long *)(this + 38000) = local_2ec8;
  pCVar36 = this + 0x9498;
  if (0x20 < *(ulong *)(this + 0x9478)) {
    pCVar36 = *(CInventoryMenu **)(this + 0x9518);
  }
  *(undefined4 *)(pCVar36 + local_2ec8 * 4) = 0;
  puVar31 = local_2ea0;
  if (0x20 < local_2ec0) {
    puVar31 = local_2e20;
  }
  pCVar36 = this + 0x9498;
  if (0x20 < *(ulong *)(this + 0x9478)) {
    pCVar36 = *(CInventoryMenu **)(this + 0x9518);
  }
  memcpy(pCVar36,puVar31,local_2ec8 * 4);
                    /* try { // try from 00b5bdb6 to 00b5bdba has its CatchHandler @ 00b5fccb */
  CEGUI::String::~String((String *)&local_2ec8);
                    /* try { // try from 00b5bdbe to 00b5be2a has its CatchHandler @ 00b5fd15 */
  CEGUI::String::~String((String *)&local_2e18);
  local_2f70 = 0x20;
  local_2f68 = 0;
  local_2f58 = 0;
  local_2f60 = 0;
  local_2ed0 = (uint *)0x0;
  local_2f78 = 0;
  local_2f50[0] = 0;
  CEGUI::String::grow((ulong)&local_2f78);
  puVar25 = local_2f50;
  if (0x20 < local_2f70) {
    puVar25 = local_2ed0;
  }
  pcVar34 = "TabFish";
  do {
    bVar3 = *pcVar34;
    pcVar34 = pcVar34 + 1;
    *puVar25 = (uint)bVar3;
    puVar25 = puVar25 + 1;
  } while ((byte *)pcVar34 != (byte *)0xfef7c6);
  local_2f78 = 7;
  puVar25 = local_2f34;
  if (0x20 < local_2f70) {
    puVar25 = local_2ed0 + 7;
  }
  *puVar25 = 0;
                    /* try { // try from 00b5be99 to 00b5be9d has its CatchHandler @ 00b5fb6f */
  uVar14 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x48));
  *(undefined8 *)(this + 0x9130) = uVar14;
                    /* try { // try from 00b5bea8 to 00b5bf14 has its CatchHandler @ 00b5fd15 */
  CEGUI::String::~String((String *)&local_2f78);
  local_3020 = 0x20;
  local_3018 = 0;
  local_3008 = 0;
  local_3010 = 0;
  local_2f80 = (uint *)0x0;
  local_3028 = 0;
  local_3000[0] = 0;
  CEGUI::String::grow((ulong)&local_3028);
  puVar25 = local_3000;
  if (0x20 < local_3020) {
    puVar25 = local_2f80;
  }
  pcVar34 = "UnselectedImage";
  do {
    bVar3 = *pcVar34;
    pcVar34 = pcVar34 + 1;
    *puVar25 = (uint)bVar3;
    puVar25 = puVar25 + 1;
  } while ((byte *)pcVar34 != (byte *)0xfef76b);
  local_3028 = 0xf;
  puVar25 = local_2fc4;
  if (0x20 < local_3020) {
    puVar25 = local_2f80 + 0xf;
  }
  *puVar25 = 0;
                    /* try { // try from 00b5bf8c to 00b5bf90 has its CatchHandler @ 00b5fb6a */
  CEGUI::PropertySet::getProperty((String *)&local_30d8);
                    /* try { // try from 00b5bfa3 to 00b5bfa7 has its CatchHandler @ 00b5fb55 */
  CEGUI::String::grow((ulong)(this + 0x9310));
  *(long *)(this + 0x9310) = local_30d8;
  pCVar36 = this + 0x9338;
  if (0x20 < *(ulong *)(this + 0x9318)) {
    pCVar36 = *(CInventoryMenu **)(this + 0x93b8);
  }
  *(undefined4 *)(pCVar36 + local_30d8 * 4) = 0;
  puVar31 = local_30b0;
  if (0x20 < local_30d0) {
    puVar31 = local_3030;
  }
  pCVar36 = this + 0x9338;
  if (0x20 < *(ulong *)(this + 0x9318)) {
    pCVar36 = *(CInventoryMenu **)(this + 0x93b8);
  }
  memcpy(pCVar36,puVar31,local_30d8 * 4);
                    /* try { // try from 00b5c00d to 00b5c011 has its CatchHandler @ 00b5fb6a */
  CEGUI::String::~String((String *)&local_30d8);
                    /* try { // try from 00b5c015 to 00b5c081 has its CatchHandler @ 00b5fd15 */
  CEGUI::String::~String((String *)&local_3028);
  local_3180 = 0x20;
  local_3178 = 0;
  local_3168 = 0;
  local_3170 = 0;
  local_30e0 = (uint *)0x0;
  local_3188 = 0;
  local_3160[0] = 0;
  CEGUI::String::grow((ulong)&local_3188);
  puVar25 = local_3160;
  if (0x20 < local_3180) {
    puVar25 = local_30e0;
  }
  pcVar34 = "SelectedImage";
  do {
    bVar3 = *pcVar34;
    pcVar34 = pcVar34 + 1;
    *puVar25 = (uint)bVar3;
    puVar25 = puVar25 + 1;
  } while ((byte *)pcVar34 != (byte *)0xfef7be);
  local_3188 = 0xd;
  puVar25 = local_312c;
  if (0x20 < local_3180) {
    puVar25 = local_30e0 + 0xd;
  }
  *puVar25 = 0;
                    /* try { // try from 00b5c0f4 to 00b5c0f8 has its CatchHandler @ 00b5fb45 */
  CEGUI::PropertySet::getProperty((String *)&local_3238);
                    /* try { // try from 00b5c10b to 00b5c10f has its CatchHandler @ 00b5fb35 */
  CEGUI::String::grow((ulong)(this + 0x9520));
  *(long *)(this + 0x9520) = local_3238;
  pCVar36 = this + 0x9548;
  if (0x20 < *(ulong *)(this + 0x9528)) {
    pCVar36 = *(CInventoryMenu **)(this + 0x95c8);
  }
  *(undefined4 *)(pCVar36 + local_3238 * 4) = 0;
  puVar31 = local_3210;
  if (0x20 < local_3230) {
    puVar31 = local_3190;
  }
  pCVar36 = this + 0x9548;
  if (0x20 < *(ulong *)(this + 0x9528)) {
    pCVar36 = *(CInventoryMenu **)(this + 0x95c8);
  }
  memcpy(pCVar36,puVar31,local_3238 * 4);
                    /* try { // try from 00b5c176 to 00b5c17a has its CatchHandler @ 00b5fb45 */
  CEGUI::String::~String((String *)&local_3238);
                    /* try { // try from 00b5c17e to 00b5c214 has its CatchHandler @ 00b5fd15 */
  CEGUI::String::~String((String *)&local_3188);
  CEGUI::Window::setZOrderingEnabled(SUB81(*(undefined8 *)(this + 0x9120),0));
  CEGUI::Window::setZOrderingEnabled(SUB81(*(undefined8 *)(this + 0x9128),0));
  CEGUI::Window::setZOrderingEnabled(SUB81(*(undefined8 *)(this + 0x9130),0));
  local_32e0 = 0x20;
  local_32d8 = 0;
  local_32c8 = 0;
  local_32d0 = 0;
  local_3240 = (uint *)0x0;
  local_32e8 = 0;
  local_32c0[0] = 0;
  CEGUI::String::grow((ulong)&local_32e8);
  puVar25 = local_32c0;
  if (0x20 < local_32e0) {
    puVar25 = local_3240;
  }
  pbVar16 = (byte *)0xfeff6a;
  do {
    bVar3 = *pbVar16;
    pbVar16 = pbVar16 + 1;
    *puVar25 = (uint)bVar3;
    puVar25 = puVar25 + 1;
  } while (pbVar16 != (byte *)0xfeff78);
  local_32e8 = 0xe;
  puVar25 = local_3288;
  if (0x20 < local_32e0) {
    puVar25 = local_3240 + 0xe;
  }
  *puVar25 = 0;
                    /* try { // try from 00b5c281 to 00b5c285 has its CatchHandler @ 00b5fb2a */
  uVar14 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x48));
  *(undefined8 *)(this + 0x9108) = uVar14;
                    /* try { // try from 00b5c290 to 00b5c2fc has its CatchHandler @ 00b5fd15 */
  CEGUI::String::~String((String *)&local_32e8);
  local_3390 = 0x20;
  local_3388 = 0;
  local_3378 = 0;
  local_3380 = 0;
  local_32f0 = (uint *)0x0;
  local_3398 = 0;
  local_3370[0] = 0;
  CEGUI::String::grow((ulong)&local_3398);
  puVar25 = local_3370;
  if (0x20 < local_3390) {
    puVar25 = local_32f0;
  }
  pbVar16 = (byte *)0xfeff5b;
  do {
    bVar3 = *pbVar16;
    pbVar16 = pbVar16 + 1;
    *puVar25 = (uint)bVar3;
    puVar25 = puVar25 + 1;
  } while (pbVar16 != (byte *)0xfeff66);
  local_3398 = 0xb;
  puVar25 = local_3344;
  if (0x20 < local_3390) {
    puVar25 = local_32f0 + 0xb;
  }
  *puVar25 = 0;
                    /* try { // try from 00b5c369 to 00b5c36d has its CatchHandler @ 00b5fb25 */
  uVar14 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x48));
  *(undefined8 *)(this + 0x9110) = uVar14;
                    /* try { // try from 00b5c378 to 00b5c3f2 has its CatchHandler @ 00b5fd15 */
  CEGUI::String::~String((String *)&local_3398);
  CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x9110),0));
  local_3440 = 0x20;
  local_3438 = 0;
  local_3428 = 0;
  local_3430 = 0;
  local_33a0 = (uint *)0x0;
  local_3448 = 0;
  local_3420[0] = 0;
  CEGUI::String::grow((ulong)&local_3448);
  puVar25 = local_3420;
  if (0x20 < local_3440) {
    puVar25 = local_33a0;
  }
  pbVar16 = (byte *)0xfeff4e;
  do {
    bVar3 = *pbVar16;
    pbVar16 = pbVar16 + 1;
    *puVar25 = (uint)bVar3;
    puVar25 = puVar25 + 1;
  } while (pbVar16 != (byte *)0xfeff57);
  local_3448 = 9;
  puVar25 = local_33fc;
  if (0x20 < local_3440) {
    puVar25 = local_33a0 + 9;
  }
  *puVar25 = 0;
                    /* try { // try from 00b5c459 to 00b5c45d has its CatchHandler @ 00b5fb20 */
  uVar14 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x48));
  *(undefined8 *)(this + 0x9118) = uVar14;
                    /* try { // try from 00b5c468 to 00b5c4d2 has its CatchHandler @ 00b5fd15 */
  CEGUI::String::~String((String *)&local_3448);
  CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x9118),0));
  local_44f8 = 1;
  pCVar36 = this;
  do {
    STRINGS::GetValueAsString((uint)local_1c8);
                    /* try { // try from 00b5c4e8 to 00b5c4ec has its CatchHandler @ 00b5fb10 */
    std::operator+((char *)local_1d8,(string *)0xff0cc3);
    local_34f0 = 0x20;
    local_34e8 = 0;
    local_34d8 = 0;
    local_34e0 = 0;
    local_3450 = (undefined4 *)0x0;
    local_34f8 = 0;
    local_34d0[0] = 0;
    lVar12 = *(long *)(local_1d8[0] + -0x18);
                    /* try { // try from 00b5c557 to 00b5c55b has its CatchHandler @ 00b5face */
    CEGUI::String::grow((ulong)&local_34f8);
    puVar23 = local_34d0;
    if (0x20 < local_34f0) {
      puVar23 = local_3450;
    }
    puVar23[lVar12] = 0;
    lVar32 = lVar12;
    while (lVar32 != 0) {
      lVar32 = lVar32 + -1;
      puVar23 = local_34d0;
      if (0x20 < local_34f0) {
        puVar23 = local_3450;
      }
      puVar23[lVar32] = (uint)*(byte *)(local_1d8[0] + lVar32);
    }
    local_34f8 = lVar12;
                    /* try { // try from 00b5c5d3 to 00b5c5d7 has its CatchHandler @ 00b5faf0 */
    lVar12 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x48));
                    /* try { // try from 00b5c5e3 to 00b5c5e7 has its CatchHandler @ 00b5face */
    CEGUI::String::~String((String *)&local_34f8);
    if ((allocator *)(local_1d8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_1d8[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_1d8[0] + -0x18));
      }
    }
    if ((allocator *)(local_1c8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_1c8[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_1c8[0] + -0x18));
      }
    }
                    /* try { // try from 00b5c61e to 00b5c658 has its CatchHandler @ 00b5fd15 */
    CEGUI::Window::moveToFront();
    *(undefined1 *)(lVar12 + 0x213) = 0;
    CEGUI::Window::setWantsMultiClickEvents(SUB81(lVar12,0));
    *(CInventoryMenu **)(lVar12 + 0x1d8) = this + (ulong)(local_44f8 + 0x12) * 4 + 0x80;
    pcVar4 = *(code **)(*(long *)(lVar12 + 0x38) + 0x10);
    local_1e8[0] = operator_new(0x20);
    lVar32 = lVar12 + 0x38;
    *local_1e8[0] = &PTR__MemberFunctionSlot_00fefcd0;
    local_1e8[0][2] = 0;
    local_1e8[0][1] = handle_ItemClick;
    local_1e8[0][3] = this;
                    /* try { // try from 00b5c69b to 00b5c6d0 has its CatchHandler @ 00b5fa67 */
    (*pcVar4)(&local_5a8,lVar32,CEGUI::Window::EventMouseButtonDown,(SubscriberSlot *)local_1e8);
    pBVar6 = local_5a8;
    if ((local_5a8 != (BoundSlot *)0x0) &&
       (iVar7 = *local_5a0, *local_5a0 = iVar7 + -1, iVar7 + -1 == 0)) {
      if (local_5a8 != (BoundSlot *)0x0) {
        CEGUI::BoundSlot::~BoundSlot(local_5a8);
        operator_delete(pBVar6);
      }
      operator_delete(local_5a0);
      local_5a8 = (BoundSlot *)0x0;
      local_5a0 = (int *)0x0;
    }
                    /* try { // try from 00b5c701 to 00b5c717 has its CatchHandler @ 00b5fd15 */
    CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_1e8);
    pcVar4 = *(code **)(*(long *)(lVar12 + 0x38) + 0x10);
    local_1f8[0] = operator_new(0x20);
    *local_1f8[0] = &PTR__MemberFunctionSlot_00fefcd0;
    local_1f8[0][2] = 0;
    local_1f8[0][1] = handle_MouseOver;
    local_1f8[0][3] = this;
                    /* try { // try from 00b5c756 to 00b5c78b has its CatchHandler @ 00b5fa65 */
    (*pcVar4)(&local_5b8,lVar32,CEGUI::Window::EventMouseEnters,(SubscriberSlot *)local_1f8);
    pBVar6 = local_5b8;
    if ((local_5b8 != (BoundSlot *)0x0) &&
       (iVar7 = *local_5b0, *local_5b0 = iVar7 + -1, iVar7 + -1 == 0)) {
      if (local_5b8 != (BoundSlot *)0x0) {
        CEGUI::BoundSlot::~BoundSlot(local_5b8);
        operator_delete(pBVar6);
      }
      operator_delete(local_5b0);
      local_5b8 = (BoundSlot *)0x0;
      local_5b0 = (int *)0x0;
    }
                    /* try { // try from 00b5c7bc to 00b5c7d2 has its CatchHandler @ 00b5fd15 */
    CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_1f8);
    pcVar4 = *(code **)(*(long *)(lVar12 + 0x38) + 0x10);
    local_208[0] = operator_new(0x20);
    *local_208[0] = &PTR__MemberFunctionSlot_00fefcd0;
    local_208[0][2] = 0;
    local_208[0][1] = handle_MouseOver;
    local_208[0][3] = this;
                    /* try { // try from 00b5c811 to 00b5c846 has its CatchHandler @ 00b5fa54 */
    (*pcVar4)(&local_5c8,lVar32,CEGUI::Window::EventMouseMove,(SubscriberSlot *)local_208);
    pBVar6 = local_5c8;
    if ((local_5c8 != (BoundSlot *)0x0) &&
       (iVar7 = *local_5c0, *local_5c0 = iVar7 + -1, iVar7 + -1 == 0)) {
      if (local_5c8 != (BoundSlot *)0x0) {
        CEGUI::BoundSlot::~BoundSlot(local_5c8);
        operator_delete(pBVar6);
      }
      operator_delete(local_5c0);
      local_5c8 = (BoundSlot *)0x0;
      local_5c0 = (int *)0x0;
    }
                    /* try { // try from 00b5c877 to 00b5c88d has its CatchHandler @ 00b5fd15 */
    CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_208);
    pcVar4 = *(code **)(*(long *)(lVar12 + 0x38) + 0x10);
    local_218[0] = operator_new(0x20);
    *local_218[0] = &PTR__MemberFunctionSlot_00fefcd0;
    local_218[0][2] = 0;
    local_218[0][1] = handle_MouseOut;
    local_218[0][3] = this;
                    /* try { // try from 00b5c8cc to 00b5c901 has its CatchHandler @ 00b5fc93 */
    (*pcVar4)(&local_5d8,lVar32,CEGUI::Window::EventMouseLeaves,(SubscriberSlot *)local_218);
    pBVar6 = local_5d8;
    if ((local_5d8 != (BoundSlot *)0x0) &&
       (iVar7 = *local_5d0, *local_5d0 = iVar7 + -1, iVar7 + -1 == 0)) {
      if (local_5d8 != (BoundSlot *)0x0) {
        CEGUI::BoundSlot::~BoundSlot(local_5d8);
        operator_delete(pBVar6);
      }
      operator_delete(local_5d0);
      local_5d8 = (BoundSlot *)0x0;
      local_5d0 = (int *)0x0;
    }
                    /* try { // try from 00b5c932 to 00b5c99f has its CatchHandler @ 00b5fd15 */
    CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_218);
    *(long *)(pCVar36 + 0x10c0) = lVar12;
    local_3700 = 0x20;
    local_36f8 = 0;
    local_36e8 = 0;
    local_36f0 = 0;
    local_3660 = (undefined4 *)0x0;
    local_3708 = 0;
    local_36e0[0] = 0;
    CEGUI::String::grow((ulong)&local_3708);
    local_3708 = 0;
    puVar23 = local_3660;
    if (local_3700 < 0x21) {
      puVar23 = local_36e0;
    }
    *puVar23 = 0;
                    /* try { // try from 00b5c9e2 to 00b5c9e6 has its CatchHandler @ 00b5fc8b */
    std::string::string((string *)local_228,"gui_",&local_3d);
                    /* try { // try from 00b5c9f7 to 00b5c9fb has its CatchHandler @ 00b5fc98 */
    STRINGS::uniqueName((STRINGS *)local_238,(string *)local_228);
    local_3650 = 0x20;
    local_3648 = 0;
    local_3638 = 0;
    local_3640 = 0;
    local_35b0 = (undefined4 *)0x0;
    local_3658 = 0;
    local_3630[0] = 0;
    lVar12 = *(long *)(local_238[0] + -0x18);
                    /* try { // try from 00b5ca66 to 00b5ca6a has its CatchHandler @ 00b5fc18 */
    CEGUI::String::grow((ulong)&local_3658);
    puVar23 = local_3630;
    if (0x20 < local_3650) {
      puVar23 = local_35b0;
    }
    puVar23[lVar12] = 0;
    lVar32 = lVar12;
    while (lVar32 != 0) {
      lVar32 = lVar32 + -1;
      puVar23 = local_3630;
      if (0x20 < local_3650) {
        puVar23 = local_35b0;
      }
      puVar23[lVar32] = (uint)*(byte *)(local_238[0] + lVar32);
    }
    pcVar30 = (char *)0x0;
    pcVar33 = "GuiLook/StaticText";
    local_35a0 = 0x20;
    local_3598 = 0;
    pcVar34 = "GuiLook/StaticText";
    local_3588 = 0;
    local_3590 = 0;
    local_3500 = (uint *)0x0;
    local_35a8 = 0;
    local_3580[0] = 0;
    cVar2 = s_GuiLook_StaticText_00fe4872[0];
    while (pcVar34 = pcVar34 + 1, cVar2 != '\0') {
      pcVar30 = pcVar34 + -0xfe4872;
      cVar2 = *pcVar34;
    }
    local_3658 = lVar12;
    if (pcVar30 == CEGUI::String::npos) {
                    /* try { // try from 00b5ed45 to 00b5ed49 has its CatchHandler @ 00b5f80f */
      std::string::string((string *)local_3b8,"Length for utf8 encoded string can not be \'npos\'",
                          local_5e);
      plVar24 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00b5ed5d to 00b5ed61 has its CatchHandler @ 00b5f7f7 */
      std::length_error::length_error(plVar24,(string *)local_3b8);
      if ((allocator *)(local_3b8[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_3b8[0] + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_3b8[0] + -0x18));
        }
      }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00b5ed89 to 00b5ed8d has its CatchHandler @ 00b5fc20 */
      __cxa_throw(plVar24,&std::length_error::typeinfo,std::length_error::~length_error);
    }
    lVar12 = 0;
    pcVar34 = pcVar30;
    pbVar16 = (byte *)"GuiLook/StaticText";
    while (pcVar34 != (char *)0x0) {
      bVar3 = *pbVar16;
      pcVar13 = pcVar34 + -1;
      pbVar28 = pbVar16 + 1;
      if ((char)bVar3 < '\0') {
        if (bVar3 < 0xe0) {
          pcVar13 = pcVar34 + -2;
          pbVar28 = pbVar16 + 2;
        }
        else if (bVar3 < 0xf0) {
          pcVar13 = pcVar34 + -3;
          pbVar28 = pbVar16 + 3;
        }
        else {
          pcVar13 = pcVar34 + -3;
          pbVar28 = pbVar16 + 4;
        }
      }
      lVar12 = lVar12 + 1;
      pcVar34 = pcVar13;
      pbVar16 = pbVar28;
    }
                    /* try { // try from 00b5cbc3 to 00b5cbc7 has its CatchHandler @ 00b5fc20 */
    CEGUI::String::grow((ulong)&local_35a8);
    puVar25 = local_3500;
    if (local_35a0 < 0x21) {
      puVar25 = local_3580;
    }
    if (pcVar30 == (char *)0x0) {
      if (s_GuiLook_StaticText_00fe4872[0] != '\0') {
        do {
          pcVar33 = pcVar33 + 1;
          pcVar30 = pcVar33 + -0xfe4872;
        } while (*pcVar33 != '\0');
        bVar37 = pcVar30 != (char *)0x0 && local_35a0 != 0;
        goto LAB_00b5cbf5;
      }
    }
    else {
      bVar37 = local_35a0 != 0;
LAB_00b5cbf5:
      if (bVar37) {
        pcVar34 = (char *)0x0;
        uVar10 = 0;
        uVar26 = local_35a0;
        do {
          bVar3 = pcVar34[0xfe4872];
          uVar11 = (uint)bVar3;
          uVar9 = uVar10 + 1;
          if ((char)bVar3 < '\0') {
            uVar11 = (uint)bVar3;
            if (0xdf < bVar3) {
              if (bVar3 < 0xf0) {
                uVar29 = (ulong)uVar9;
                uVar9 = uVar10 + 3;
                uVar11 = (byte)"GuiLook/StaticText"[uVar10 + 2] & 0x3f | (uVar11 & 0xf) << 0xc |
                         ((byte)"GuiLook/StaticText"[uVar29] & 0x3f) << 6;
              }
              else {
                uVar29 = (ulong)uVar9;
                uVar9 = uVar10 + 4;
                uVar11 = ((byte)"GuiLook/StaticText"[uVar29] & 0x3f) << 0xc |
                         (byte)"GuiLook/StaticText"[uVar10 + 3] & 0x3f | (uVar11 & 7) << 0x12 |
                         ((byte)"GuiLook/StaticText"[uVar10 + 2] & 0x3f) << 6;
              }
              goto LAB_00b5cc03;
            }
            uVar10 = uVar10 + 2;
            *puVar25 = (byte)"GuiLook/StaticText"[uVar9] & 0x3f | (uVar11 & 0x1f) << 6;
          }
          else {
LAB_00b5cc03:
            *puVar25 = uVar11;
            uVar10 = uVar9;
          }
          pcVar34 = (char *)(ulong)uVar10;
          if ((pcVar30 <= pcVar34) || (uVar26 = uVar26 - 1, uVar26 == 0)) break;
          puVar25 = puVar25 + 1;
        } while( true );
      }
    }
    puVar25 = local_3500;
    if (local_35a0 < 0x21) {
      puVar25 = local_3580;
    }
    puVar25[lVar12] = 0;
    local_35a8 = lVar12;
                    /* try { // try from 00b5ccaa to 00b5ccae has its CatchHandler @ 00b5f4ae */
    uVar14 = CEGUI::WindowManager::createWindow
                       (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,(String *)&local_35a8,
                        (String *)&local_3658);
    *(undefined8 *)(pCVar36 + 0x1870) = uVar14;
                    /* try { // try from 00b5ccbe to 00b5ccc2 has its CatchHandler @ 00b5fc20 */
    CEGUI::String::~String((String *)&local_35a8);
                    /* try { // try from 00b5cccb to 00b5cccf has its CatchHandler @ 00b5fc18 */
    CEGUI::String::~String((String *)&local_3658);
    if ((allocator *)(local_238[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_238[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_238[0] + -0x18));
      }
    }
    if ((allocator *)(local_228[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_228[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_228[0] + -0x18));
      }
    }
                    /* try { // try from 00b5cd0c to 00b5cd78 has its CatchHandler @ 00b5fd15 */
    CEGUI::String::~String((String *)&local_3708);
    local_37b0 = 0x20;
    local_37a8 = 0;
    local_3798 = 0;
    local_37a0 = 0;
    local_3710 = (uint *)0x0;
    local_37b8 = 0;
    local_3790[0] = 0;
    CEGUI::String::grow((ulong)&local_37b8);
    puVar25 = local_3790;
    if (0x20 < local_37b0) {
      puVar25 = local_3710;
    }
    pcVar34 = "Serif";
    do {
      bVar3 = *pcVar34;
      pcVar34 = pcVar34 + 1;
      *puVar25 = (uint)bVar3;
      puVar25 = puVar25 + 1;
    } while ((byte *)pcVar34 != (byte *)0xfe4949);
    local_37b8 = 5;
    puVar25 = local_377c;
    if (0x20 < local_37b0) {
      puVar25 = local_3710 + 5;
    }
    *puVar25 = 0;
                    /* try { // try from 00b5cded to 00b5cdf1 has its CatchHandler @ 00b5fbd5 */
    CEGUI::Window::setFont(*(String **)(pCVar36 + 0x1870));
                    /* try { // try from 00b5cdf5 to 00b5ce0c has its CatchHandler @ 00b5fd15 */
    CEGUI::String::~String((String *)&local_37b8);
    CEGUI::Window::getSize();
                    /* try { // try from 00b5ce17 to 00b5ce1b has its CatchHandler @ 00b5fbc5 */
    CEGUI::Window::setSize(*(UVector2 **)(pCVar36 + 0x1870));
                    /* try { // try from 00b5ce1f to 00b5ce23 has its CatchHandler @ 00b5fd15 */
    puVar22 = (undefined8 *)CEGUI::Window::getPosition();
    local_5f8 = *puVar22;
    local_5f0 = puVar22[1];
    local_3910 = 0x20;
    local_3908 = 0;
    local_38f8 = 0;
    local_3900 = 0;
    local_3870 = (uint *)0x0;
    local_3918 = 0;
    local_38f0[0] = 0;
                    /* try { // try from 00b5ce9e to 00b5cea2 has its CatchHandler @ 00b5fbb5 */
    CEGUI::String::grow((ulong)&local_3918);
    puVar25 = local_38f0;
    if (0x20 < local_3910) {
      puVar25 = local_3870;
    }
    pcVar34 = "RightAligned";
    do {
      bVar3 = *pcVar34;
      pcVar34 = pcVar34 + 1;
      *puVar25 = (uint)bVar3;
      puVar25 = puVar25 + 1;
    } while ((byte *)pcVar34 != (byte *)0xfe602d);
    local_3918 = 0xc;
    puVar25 = local_38c0;
    if (0x20 < local_3910) {
      puVar25 = local_3870 + 0xc;
    }
    *puVar25 = 0;
    local_3860 = 0x20;
    local_3858 = 0;
    local_3848 = 0;
    local_3850 = 0;
    local_37c0 = (uint *)0x0;
    local_3868 = 0;
    local_3840[0] = 0;
                    /* try { // try from 00b5cf65 to 00b5cf69 has its CatchHandler @ 00b5fba5 */
    CEGUI::String::grow((ulong)&local_3868);
    puVar25 = local_3840;
    if (0x20 < local_3860) {
      puVar25 = local_37c0;
    }
    pcVar34 = "HorzTextFormatting";
    do {
      bVar3 = *pcVar34;
      pcVar34 = pcVar34 + 1;
      *puVar25 = (uint)bVar3;
      puVar25 = puVar25 + 1;
    } while ((byte *)pcVar34 != (byte *)0xfe48cf);
    local_3868 = 0x12;
    puVar25 = local_37f8;
    if (0x20 < local_3860) {
      puVar25 = local_37c0 + 0x12;
    }
    *puVar25 = 0;
                    /* try { // try from 00b5cfe0 to 00b5cfe4 has its CatchHandler @ 00b5fb95 */
    CEGUI::PropertySet::setProperty(*(String **)(pCVar36 + 0x1870),(String *)&local_3868);
                    /* try { // try from 00b5cfe8 to 00b5cfec has its CatchHandler @ 00b5fba5 */
    CEGUI::String::~String((String *)&local_3868);
                    /* try { // try from 00b5cff0 to 00b5d05c has its CatchHandler @ 00b5fbb5 */
    CEGUI::String::~String((String *)&local_3918);
    local_3a70 = 0x20;
    local_3a68 = 0;
    local_3a58 = 0;
    local_3a60 = 0;
    local_39d0 = (uint *)0x0;
    local_3a78 = 0;
    local_3a50[0] = 0;
    CEGUI::String::grow((ulong)&local_3a78);
    puVar25 = local_3a50;
    if (0x20 < local_3a70) {
      puVar25 = local_39d0;
    }
    pcVar34 = "BottomAligned";
    do {
      bVar3 = *pcVar34;
      pcVar34 = pcVar34 + 1;
      *puVar25 = (uint)bVar3;
      puVar25 = puVar25 + 1;
    } while ((byte *)pcVar34 != (byte *)0xfe6020);
    local_3a78 = 0xd;
    puVar25 = local_3a1c;
    if (0x20 < local_3a70) {
      puVar25 = local_39d0 + 0xd;
    }
    *puVar25 = 0;
    local_39c0 = 0x20;
    local_39b8 = 0;
    local_39a8 = 0;
    local_39b0 = 0;
    local_3920 = (uint *)0x0;
    local_39c8 = 0;
    local_39a0[0] = 0;
                    /* try { // try from 00b5d125 to 00b5d129 has its CatchHandler @ 00b5fb85 */
    CEGUI::String::grow((ulong)&local_39c8);
    puVar25 = local_39a0;
    if (0x20 < local_39c0) {
      puVar25 = local_3920;
    }
    pcVar34 = "VertFormatting";
    do {
      bVar3 = *pcVar34;
      pcVar34 = pcVar34 + 1;
      *puVar25 = (uint)bVar3;
      puVar25 = puVar25 + 1;
    } while ((byte *)pcVar34 != (byte *)0xfe48ae);
    local_39c8 = 0xe;
    puVar25 = local_3968;
    if (0x20 < local_39c0) {
      puVar25 = local_3920 + 0xe;
    }
    *puVar25 = 0;
                    /* try { // try from 00b5d1a0 to 00b5d1a4 has its CatchHandler @ 00b5fb75 */
    CEGUI::PropertySet::setProperty(*(String **)(pCVar36 + 0x1870),(String *)&local_39c8);
                    /* try { // try from 00b5d1a8 to 00b5d1ac has its CatchHandler @ 00b5fb85 */
    CEGUI::String::~String((String *)&local_39c8);
                    /* try { // try from 00b5d1b0 to 00b5d263 has its CatchHandler @ 00b5fbb5 */
    CEGUI::String::~String((String *)&local_3a78);
    *(undefined1 *)(*(long *)(pCVar36 + 0x1870) + 0x3e2) = 1;
    CEGUI::Window::setPosition(*(UVector2 **)(pCVar36 + 0x1870));
    CEGUI::Window::addChildWindow(*(Window **)(*(long *)(pCVar36 + 0x10c0) + 0xb0));
    local_3b20 = 0x20;
    local_3b18 = 0;
    local_3b08 = 0;
    local_3b10 = 0;
    local_3a80 = (undefined4 *)0x0;
    local_3b28 = 0;
    local_3b00[0] = 0;
    if (CEGUI::String::npos == (char *)0x0) {
                    /* try { // try from 00b5eda6 to 00b5edaa has its CatchHandler @ 00b5f880 */
      std::string::string((string *)local_3c8,"Length for utf8 encoded string can not be \'npos\'",
                          local_62);
      plVar24 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00b5edbe to 00b5edc2 has its CatchHandler @ 00b5f868 */
      std::length_error::length_error(plVar24,(string *)local_3c8);
      if ((allocator *)(local_3c8[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_3c8[0] + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_3c8[0] + -0x18));
        }
      }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00b5edea to 00b5edee has its CatchHandler @ 00b5fbb5 */
      __cxa_throw(plVar24,&std::length_error::typeinfo,std::length_error::~length_error);
    }
    CEGUI::String::grow((ulong)&local_3b28);
    local_3b28 = 0;
    puVar23 = local_3b00;
    if (0x20 < local_3b20) {
      puVar23 = local_3a80;
    }
    *puVar23 = 0;
                    /* try { // try from 00b5d298 to 00b5d29c has its CatchHandler @ 00b5f7bb */
    CEGUI::Window::setText(*(String **)(pCVar36 + 0x1870));
                    /* try { // try from 00b5d2a0 to 00b5d2d8 has its CatchHandler @ 00b5fbb5 */
    CEGUI::String::~String((String *)&local_3b28);
    CEGUI::colour::colour(local_688,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc);
    CEGUI::PropertyHelper::colourToString(local_3bd8);
    local_3c80 = 0x20;
    local_3c78 = 0;
    local_3c68 = 0;
    local_3c70 = 0;
    local_3be0 = (uint *)0x0;
    local_3c88 = 0;
    local_3c60[0] = 0;
                    /* try { // try from 00b5d33c to 00b5d340 has its CatchHandler @ 00b5f60b */
    CEGUI::String::grow((ulong)&local_3c88);
    puVar25 = local_3c60;
    if (0x20 < local_3c80) {
      puVar25 = local_3be0;
    }
    pbVar16 = (byte *)0xfe4654;
    do {
      bVar3 = *pbVar16;
      pbVar16 = pbVar16 + 1;
      *puVar25 = (uint)bVar3;
      puVar25 = puVar25 + 1;
    } while (pbVar16 != (byte *)0xfe465e);
    local_3c88 = 10;
    puVar25 = local_3c38;
    if (0x20 < local_3c80) {
      puVar25 = local_3be0 + 10;
    }
    *puVar25 = 0;
                    /* try { // try from 00b5d3b0 to 00b5d3b4 has its CatchHandler @ 00b5f5f3 */
    CEGUI::PropertySet::setProperty(*(String **)(pCVar36 + 0x1870),(String *)&local_3c88);
                    /* try { // try from 00b5d3b8 to 00b5d3bc has its CatchHandler @ 00b5f60b */
    CEGUI::String::~String((String *)&local_3c88);
                    /* try { // try from 00b5d3c0 to 00b5d437 has its CatchHandler @ 00b5fbb5 */
    CEGUI::String::~String(local_3bd8);
    CEGUI::Window::setAlwaysOnTop(SUB81(*(undefined8 *)(pCVar36 + 0x1870),0));
    local_3e90 = 0x20;
    local_3e88 = 0;
    local_3e78 = 0;
    local_3e80 = 0;
    local_3df0 = (undefined4 *)0x0;
    local_3e98 = 0;
    local_3e70[0] = 0;
    CEGUI::String::grow((ulong)&local_3e98);
    local_3e98 = 0;
    puVar23 = local_3df0;
    if (local_3e90 < 0x21) {
      puVar23 = local_3e70;
    }
    *puVar23 = 0;
                    /* try { // try from 00b5d47a to 00b5d47e has its CatchHandler @ 00b5f634 */
    std::string::string((string *)local_248,"gui_",&local_3e);
                    /* try { // try from 00b5d48f to 00b5d493 has its CatchHandler @ 00b5f612 */
    STRINGS::uniqueName((STRINGS *)local_258,(string *)local_248);
    local_3de0 = 0x20;
    local_3dd8 = 0;
    local_3dc8 = 0;
    local_3dd0 = 0;
    local_3d40 = (undefined4 *)0x0;
    local_3de8 = 0;
    local_3dc0[0] = 0;
    lVar12 = *(long *)(local_258[0] + -0x18);
                    /* try { // try from 00b5d4fe to 00b5d502 has its CatchHandler @ 00b5f834 */
    CEGUI::String::grow((ulong)&local_3de8);
    puVar23 = local_3dc0;
    if (0x20 < local_3de0) {
      puVar23 = local_3d40;
    }
    puVar23[lVar12] = 0;
    lVar32 = lVar12;
    while (lVar32 != 0) {
      lVar32 = lVar32 + -1;
      puVar23 = local_3dc0;
      if (0x20 < local_3de0) {
        puVar23 = local_3d40;
      }
      puVar23[lVar32] = (uint)*(byte *)(local_258[0] + lVar32);
    }
    pcVar33 = (char *)0x0;
    pcVar34 = "GuiLook/StaticImage";
    local_3d30 = 0x20;
    local_3d28 = 0;
    pcVar30 = "GuiLook/StaticImage";
    local_3d18 = 0;
    local_3d20 = 0;
    local_3c90 = (uint *)0x0;
    local_3d38 = 0;
    local_3d10[0] = 0;
    cVar2 = s_GuiLook_StaticImage_00fd0bff[0];
    while (pcVar30 = pcVar30 + 1, cVar2 != '\0') {
      pcVar33 = pcVar30 + -0xfd0bff;
      cVar2 = *pcVar30;
    }
    local_3de8 = lVar12;
    if (pcVar33 == CEGUI::String::npos) {
                    /* try { // try from 00b5ee07 to 00b5ee0b has its CatchHandler @ 00b5f90a */
      std::string::string((string *)local_3d8,"Length for utf8 encoded string can not be \'npos\'",
                          local_64);
      plVar24 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00b5ee1f to 00b5ee23 has its CatchHandler @ 00b5f8f2 */
      std::length_error::length_error(plVar24,(string *)local_3d8);
      if ((allocator *)(local_3d8[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_3d8[0] + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_3d8[0] + -0x18));
        }
      }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00b5ee4b to 00b5ee4f has its CatchHandler @ 00b5f7b6 */
      __cxa_throw(plVar24,&std::length_error::typeinfo,std::length_error::~length_error);
    }
    lVar12 = 0;
    pcVar30 = pcVar33;
    pbVar16 = (byte *)"GuiLook/StaticImage";
    while (pcVar30 != (char *)0x0) {
      bVar3 = *pbVar16;
      pcVar13 = pcVar30 + -1;
      pbVar28 = pbVar16 + 1;
      if ((char)bVar3 < '\0') {
        if (bVar3 < 0xe0) {
          pcVar13 = pcVar30 + -2;
          pbVar28 = pbVar16 + 2;
        }
        else if (bVar3 < 0xf0) {
          pcVar13 = pcVar30 + -3;
          pbVar28 = pbVar16 + 3;
        }
        else {
          pcVar13 = pcVar30 + -3;
          pbVar28 = pbVar16 + 4;
        }
      }
      lVar12 = lVar12 + 1;
      pcVar30 = pcVar13;
      pbVar16 = pbVar28;
    }
                    /* try { // try from 00b5d6ab to 00b5d6af has its CatchHandler @ 00b5f7b6 */
    CEGUI::String::grow((ulong)&local_3d38);
    if (local_3d30 < 0x21) {
      puVar25 = local_3d10;
      if (pcVar33 == (char *)0x0) goto LAB_00b5e95b;
LAB_00b5d6d7:
      bVar37 = local_3d30 != 0;
LAB_00b5d6dd:
      if (bVar37) {
        pcVar30 = (char *)0x0;
        uVar10 = 0;
        uVar26 = local_3d30;
        do {
          bVar3 = pcVar30[0xfd0bff];
          uVar11 = (uint)bVar3;
          uVar9 = uVar10 + 1;
          if ((char)bVar3 < '\0') {
            uVar11 = (uint)bVar3;
            if (0xdf < bVar3) {
              if (bVar3 < 0xf0) {
                uVar29 = (ulong)uVar9;
                uVar9 = uVar10 + 3;
                uVar11 = (byte)"GuiLook/StaticImage"[uVar10 + 2] & 0x3f | (uVar11 & 0xf) << 0xc |
                         ((byte)"GuiLook/StaticImage"[uVar29] & 0x3f) << 6;
              }
              else {
                uVar29 = (ulong)uVar9;
                uVar9 = uVar10 + 4;
                uVar11 = ((byte)"GuiLook/StaticImage"[uVar29] & 0x3f) << 0xc |
                         (byte)"GuiLook/StaticImage"[uVar10 + 3] & 0x3f | (uVar11 & 7) << 0x12 |
                         ((byte)"GuiLook/StaticImage"[uVar10 + 2] & 0x3f) << 6;
              }
              goto LAB_00b5d6f3;
            }
            uVar10 = uVar10 + 2;
            *puVar25 = (byte)"GuiLook/StaticImage"[uVar9] & 0x3f | (uVar11 & 0x1f) << 6;
          }
          else {
LAB_00b5d6f3:
            *puVar25 = uVar11;
            uVar10 = uVar9;
          }
          pcVar30 = (char *)(ulong)uVar10;
          if ((pcVar33 <= pcVar30) || (uVar26 = uVar26 - 1, uVar26 == 0)) break;
          puVar25 = puVar25 + 1;
        } while( true );
      }
    }
    else {
      puVar25 = local_3c90;
      if (pcVar33 != (char *)0x0) goto LAB_00b5d6d7;
LAB_00b5e95b:
      pcVar30 = "GuiLook/StaticImage";
      if (s_GuiLook_StaticImage_00fd0bff[0] != '\0') {
        do {
          pcVar30 = pcVar30 + 1;
          pcVar33 = pcVar30 + -0xfd0bff;
        } while (*pcVar30 != '\0');
        bVar37 = pcVar33 != (char *)0x0 && local_3d30 != 0;
        goto LAB_00b5d6dd;
      }
    }
    puVar25 = local_3c90;
    if (local_3d30 < 0x21) {
      puVar25 = local_3d10;
    }
    puVar25[lVar12] = 0;
    local_3d38 = lVar12;
                    /* try { // try from 00b5d79a to 00b5d79e has its CatchHandler @ 00b5f787 */
    pUVar21 = (UVector2 *)
              CEGUI::WindowManager::createWindow
                        (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,(String *)&local_3d38,
                         (String *)&local_3de8);
                    /* try { // try from 00b5d7aa to 00b5d7ae has its CatchHandler @ 00b5f7b6 */
    CEGUI::String::~String((String *)&local_3d38);
                    /* try { // try from 00b5d7b7 to 00b5d7bb has its CatchHandler @ 00b5f834 */
    CEGUI::String::~String((String *)&local_3de8);
    if ((allocator *)(local_258[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_258[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_258[0] + -0x18));
      }
    }
    if ((allocator *)(local_248[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_248[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_248[0] + -0x18));
      }
    }
                    /* try { // try from 00b5d7f8 to 00b5d863 has its CatchHandler @ 00b5fbb5 */
    CEGUI::String::~String((String *)&local_3e98);
    CEGUI::Window::addChildWindow(*(Window **)(*(long *)(pCVar36 + 0x10c0) + 0xb0));
    pUVar21[0x213] = (UVector2)0x0;
    CEGUI::Window::setWantsMultiClickEvents(SUB81(pUVar21,0));
    pUVar21[0x3e2] = (UVector2)0x1;
    CEGUI::EventSet::setMutedState((bool)(SUB81(pUVar21,0) + '8'));
    CEGUI::Window::getPosition();
    CEGUI::Window::setPosition(pUVar21);
    CEGUI::Window::getSize();
                    /* try { // try from 00b5d86a to 00b5d86e has its CatchHandler @ 00b5f714 */
    CEGUI::Window::setSize(pUVar21);
    *(UVector2 **)(pCVar36 + 0x1350) = pUVar21;
    local_40a0 = 0x20;
    local_4098 = 0;
    local_4088 = 0;
    local_4090 = 0;
    local_4000 = (undefined4 *)0x0;
    local_40a8 = 0;
    local_4080[0] = 0;
                    /* try { // try from 00b5d8d3 to 00b5d8d7 has its CatchHandler @ 00b5fbb5 */
    CEGUI::String::grow((ulong)&local_40a8);
    local_40a8 = 0;
    puVar23 = local_4000;
    if (local_40a0 < 0x21) {
      puVar23 = local_4080;
    }
    *puVar23 = 0;
                    /* try { // try from 00b5d91a to 00b5d91e has its CatchHandler @ 00b5f70f */
    std::string::string((string *)local_268,"gui_",&local_3f);
                    /* try { // try from 00b5d92f to 00b5d933 has its CatchHandler @ 00b5f70a */
    STRINGS::uniqueName((STRINGS *)local_278,(string *)local_268);
    local_3ff0 = 0x20;
    local_3fe8 = 0;
    local_3fd8 = 0;
    local_3fe0 = 0;
    local_3f50 = (undefined4 *)0x0;
    local_3ff8 = 0;
    local_3fd0[0] = 0;
    lVar12 = *(long *)(local_278[0] + -0x18);
                    /* try { // try from 00b5d99e to 00b5d9a2 has its CatchHandler @ 00b5f702 */
    CEGUI::String::grow((ulong)&local_3ff8);
    puVar23 = local_3f50;
    if (local_3ff0 < 0x21) {
      puVar23 = local_3fd0;
    }
    puVar23[lVar12] = 0;
    if (lVar12 != 0) {
      lVar32 = lVar12;
      do {
        lVar32 = lVar32 + -1;
        puVar23 = local_3fd0;
        if (0x20 < local_3ff0) {
          puVar23 = local_3f50;
        }
        puVar23[lVar32] = (uint)*(byte *)(local_278[0] + lVar32);
      } while (lVar32 != 0);
    }
    pcVar33 = (char *)0x0;
    local_3f40 = 0x20;
    local_3f38 = 0;
    local_3f28 = 0;
    pcVar30 = "GuiLook/StaticImage";
    local_3f30 = 0;
    local_3ea0 = (uint *)0x0;
    local_3f48 = 0;
    local_3f20[0] = 0;
    cVar2 = s_GuiLook_StaticImage_00fd0bff[0];
    while (pcVar30 = pcVar30 + 1, cVar2 != '\0') {
      pcVar33 = pcVar30 + -0xfd0bff;
      cVar2 = *pcVar30;
    }
    local_3ff8 = lVar12;
    if (pcVar33 == CEGUI::String::npos) {
                    /* try { // try from 00b5ee68 to 00b5ee6c has its CatchHandler @ 00b5fa31 */
      std::string::string((string *)local_3e8,"Length for utf8 encoded string can not be \'npos\'",
                          local_68);
      plVar24 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00b5ee80 to 00b5ee84 has its CatchHandler @ 00b5fa19 */
      std::length_error::length_error(plVar24,(string *)local_3e8);
      if ((allocator *)(local_3e8[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_3e8[0] + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_3e8[0] + -0x18));
        }
      }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00b5eeac to 00b5eeb0 has its CatchHandler @ 00b5f8ea */
      __cxa_throw(plVar24,&std::length_error::typeinfo,std::length_error::~length_error);
    }
    lVar12 = 0;
    pcVar30 = pcVar33;
    pbVar16 = (byte *)"GuiLook/StaticImage";
    while (pcVar30 != (char *)0x0) {
      bVar3 = *pbVar16;
      pcVar13 = pcVar30 + -1;
      pbVar28 = pbVar16 + 1;
      if ((char)bVar3 < '\0') {
        if (bVar3 < 0xe0) {
          pcVar13 = pcVar30 + -2;
          pbVar28 = pbVar16 + 2;
        }
        else if (bVar3 < 0xf0) {
          pcVar13 = pcVar30 + -3;
          pbVar28 = pbVar16 + 3;
        }
        else {
          pcVar13 = pcVar30 + -3;
          pbVar28 = pbVar16 + 4;
        }
      }
      lVar12 = lVar12 + 1;
      pcVar30 = pcVar13;
      pbVar16 = pbVar28;
    }
                    /* try { // try from 00b5dbab to 00b5dbaf has its CatchHandler @ 00b5f8ea */
    CEGUI::String::grow((ulong)&local_3f48);
    puVar25 = local_3ea0;
    if (local_3f40 < 0x21) {
      puVar25 = local_3f20;
    }
    if (pcVar33 == (char *)0x0) {
      pcVar30 = "GuiLook/StaticImage";
      if (s_GuiLook_StaticImage_00fd0bff[0] != '\0') {
        do {
          pcVar30 = pcVar30 + 1;
          pcVar33 = pcVar30 + -0xfd0bff;
        } while (*pcVar30 != '\0');
        bVar37 = pcVar33 != (char *)0x0 && local_3f40 != 0;
        goto LAB_00b5dbdd;
      }
    }
    else {
      bVar37 = local_3f40 != 0;
LAB_00b5dbdd:
      if (bVar37) {
        pcVar30 = (char *)0x0;
        uVar10 = 0;
        uVar26 = local_3f40;
        do {
          bVar3 = pcVar30[0xfd0bff];
          uVar11 = (uint)bVar3;
          uVar9 = uVar10 + 1;
          if ((char)bVar3 < '\0') {
            uVar11 = (uint)bVar3;
            if (0xdf < bVar3) {
              if (bVar3 < 0xf0) {
                uVar29 = (ulong)uVar9;
                uVar9 = uVar10 + 3;
                uVar11 = (byte)"GuiLook/StaticImage"[uVar10 + 2] & 0x3f | (uVar11 & 0xf) << 0xc |
                         ((byte)"GuiLook/StaticImage"[uVar29] & 0x3f) << 6;
              }
              else {
                uVar29 = (ulong)uVar9;
                uVar9 = uVar10 + 4;
                uVar11 = ((byte)"GuiLook/StaticImage"[uVar29] & 0x3f) << 0xc |
                         (byte)"GuiLook/StaticImage"[uVar10 + 3] & 0x3f | (uVar11 & 7) << 0x12 |
                         ((byte)"GuiLook/StaticImage"[uVar10 + 2] & 0x3f) << 6;
              }
              goto LAB_00b5dbf3;
            }
            uVar10 = uVar10 + 2;
            *puVar25 = (byte)"GuiLook/StaticImage"[uVar9] & 0x3f | (uVar11 & 0x1f) << 6;
          }
          else {
LAB_00b5dbf3:
            *puVar25 = uVar11;
            uVar10 = uVar9;
          }
          pcVar30 = (char *)(ulong)uVar10;
          if ((pcVar33 <= pcVar30) || (uVar26 = uVar26 - 1, uVar26 == 0)) break;
          puVar25 = puVar25 + 1;
        } while( true );
      }
    }
    puVar25 = local_3ea0;
    if (local_3f40 < 0x21) {
      puVar25 = local_3f20;
    }
    puVar25[lVar12] = 0;
    local_3f48 = lVar12;
                    /* try { // try from 00b5dc9a to 00b5dc9e has its CatchHandler @ 00b5f665 */
    pUVar21 = (UVector2 *)
              CEGUI::WindowManager::createWindow
                        (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,(String *)&local_3f48,
                         (String *)&local_3ff8);
                    /* try { // try from 00b5dcaa to 00b5dcae has its CatchHandler @ 00b5f8ea */
    CEGUI::String::~String((String *)&local_3f48);
                    /* try { // try from 00b5dcb7 to 00b5dcbb has its CatchHandler @ 00b5f702 */
    CEGUI::String::~String((String *)&local_3ff8);
    if ((allocator *)(local_278[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_278[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_278[0] + -0x18));
      }
    }
    if ((allocator *)(local_268[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_268[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_268[0] + -0x18));
      }
    }
                    /* try { // try from 00b5dcf8 to 00b5dd59 has its CatchHandler @ 00b5fbb5 */
    CEGUI::String::~String((String *)&local_40a8);
    CEGUI::Window::addChildWindow(*(Window **)(this + 0x38));
    pUVar21[0x213] = (UVector2)0x0;
    CEGUI::Window::setWantsMultiClickEvents(SUB81(pUVar21,0));
    pUVar21[0x3e2] = (UVector2)0x1;
    CEGUI::EventSet::setMutedState((bool)(SUB81(pUVar21,0) + '8'));
    CEGUI::Window::getPosition();
    CEGUI::Window::setPosition(pUVar21);
    CEGUI::Window::getSize();
                    /* try { // try from 00b5dd60 to 00b5dd64 has its CatchHandler @ 00b5f8b5 */
    CEGUI::Window::setSize(pUVar21);
    *(UVector2 **)(pCVar36 + 0x15e0) = pUVar21;
    local_42b0 = 0x20;
    local_42a8 = 0;
    local_4298 = 0;
    local_42a0 = 0;
    local_4210 = (undefined4 *)0x0;
    local_42b8 = 0;
    local_4290[0] = 0;
                    /* try { // try from 00b5ddc9 to 00b5ddcd has its CatchHandler @ 00b5fbb5 */
    CEGUI::String::grow((ulong)&local_42b8);
    local_42b8 = 0;
    puVar23 = local_4210;
    if (local_42b0 < 0x21) {
      puVar23 = local_4290;
    }
    *puVar23 = 0;
                    /* try { // try from 00b5de10 to 00b5de14 has its CatchHandler @ 00b5f8a9 */
    std::string::string((string *)local_288,"gui_",&local_40);
                    /* try { // try from 00b5de25 to 00b5de29 has its CatchHandler @ 00b5f8a1 */
    STRINGS::uniqueName((STRINGS *)local_298,(string *)local_288);
    local_4200 = 0x20;
    local_41f8 = 0;
    local_41e8 = 0;
    local_41f0 = 0;
    local_4160 = (undefined4 *)0x0;
    local_4208 = 0;
    local_41e0[0] = 0;
    lVar12 = *(long *)(local_298[0] + -0x18);
                    /* try { // try from 00b5de97 to 00b5de9b has its CatchHandler @ 00b5f9e5 */
    CEGUI::String::grow((ulong)&local_4208);
    puVar23 = local_41e0;
    if (0x20 < local_4200) {
      puVar23 = local_4160;
    }
    puVar23[lVar12] = 0;
    if (lVar12 != 0) {
      lVar32 = lVar12;
      do {
        lVar32 = lVar32 + -1;
        puVar23 = local_41e0;
        if (0x20 < local_4200) {
          puVar23 = local_4160;
        }
        puVar23[lVar32] = (uint)*(byte *)(local_298[0] + lVar32);
      } while (lVar32 != 0);
    }
    pcVar33 = (char *)0x0;
    local_4150 = 0x20;
    local_4148 = 0;
    local_4138 = 0;
    pcVar30 = "GuiLook/StaticImage";
    local_4140 = 0;
    local_40b0 = (uint *)0x0;
    local_4158 = 0;
    local_4130[0] = 0;
    cVar2 = s_GuiLook_StaticImage_00fd0bff[0];
    while (pcVar30 = pcVar30 + 1, cVar2 != '\0') {
      pcVar33 = pcVar30 + -0xfd0bff;
      cVar2 = *pcVar30;
    }
    local_4208 = lVar12;
    if (pcVar33 == CEGUI::String::npos) {
                    /* try { // try from 00b5eec9 to 00b5eecd has its CatchHandler @ 00b5fc69 */
      std::string::string((string *)local_3f8,"Length for utf8 encoded string can not be \'npos\'",
                          local_6c);
      plVar24 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00b5eee1 to 00b5eee5 has its CatchHandler @ 00b5fc51 */
      std::length_error::length_error(plVar24,(string *)local_3f8);
      if ((allocator *)(local_3f8[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_3f8[0] + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_3f8[0] + -0x18));
        }
      }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00b5ef0d to 00b5ef11 has its CatchHandler @ 00b5f6fd */
      __cxa_throw(plVar24,&std::length_error::typeinfo,std::length_error::~length_error);
    }
    lVar12 = 0;
    pcVar30 = pcVar33;
    pbVar16 = (byte *)"GuiLook/StaticImage";
    while (pcVar30 != (char *)0x0) {
      bVar3 = *pbVar16;
      pcVar13 = pcVar30 + -1;
      pbVar28 = pbVar16 + 1;
      if ((char)bVar3 < '\0') {
        if (bVar3 < 0xe0) {
          pcVar13 = pcVar30 + -2;
          pbVar28 = pbVar16 + 2;
        }
        else if (bVar3 < 0xf0) {
          pcVar13 = pcVar30 + -3;
          pbVar28 = pbVar16 + 3;
        }
        else {
          pcVar13 = pcVar30 + -3;
          pbVar28 = pbVar16 + 4;
        }
      }
      lVar12 = lVar12 + 1;
      pcVar30 = pcVar13;
      pbVar16 = pbVar28;
    }
                    /* try { // try from 00b5e031 to 00b5e035 has its CatchHandler @ 00b5f6fd */
    CEGUI::String::grow((ulong)&local_4158);
    puVar25 = local_40b0;
    if (local_4150 < 0x21) {
      puVar25 = local_4130;
    }
    if (pcVar33 == (char *)0x0) {
      if (s_GuiLook_StaticImage_00fd0bff[0] != '\0') {
        do {
          pcVar34 = pcVar34 + 1;
          pcVar33 = pcVar34 + -0xfd0bff;
        } while (*pcVar34 != '\0');
        bVar37 = pcVar33 != (char *)0x0 && local_4150 != 0;
        goto LAB_00b5e063;
      }
    }
    else {
      bVar37 = local_4150 != 0;
LAB_00b5e063:
      if (bVar37) {
        pcVar34 = (char *)0x0;
        uVar10 = 0;
        uVar26 = local_4150;
        do {
          bVar3 = pcVar34[0xfd0bff];
          uVar11 = (uint)bVar3;
          uVar9 = uVar10 + 1;
          if ((char)bVar3 < '\0') {
            uVar11 = (uint)bVar3;
            if (0xdf < bVar3) {
              if (bVar3 < 0xf0) {
                uVar29 = (ulong)uVar9;
                uVar9 = uVar10 + 3;
                uVar11 = (byte)"GuiLook/StaticImage"[uVar10 + 2] & 0x3f | (uVar11 & 0xf) << 0xc |
                         ((byte)"GuiLook/StaticImage"[uVar29] & 0x3f) << 6;
              }
              else {
                uVar29 = (ulong)uVar9;
                uVar9 = uVar10 + 4;
                uVar11 = ((byte)"GuiLook/StaticImage"[uVar29] & 0x3f) << 0xc |
                         (byte)"GuiLook/StaticImage"[uVar10 + 3] & 0x3f | (uVar11 & 7) << 0x12 |
                         ((byte)"GuiLook/StaticImage"[uVar10 + 2] & 0x3f) << 6;
              }
              goto LAB_00b5e073;
            }
            uVar10 = uVar10 + 2;
            *puVar25 = (byte)"GuiLook/StaticImage"[uVar9] & 0x3f | (uVar11 & 0x1f) << 6;
          }
          else {
LAB_00b5e073:
            *puVar25 = uVar11;
            uVar10 = uVar9;
          }
          pcVar34 = (char *)(ulong)uVar10;
          if ((pcVar33 <= pcVar34) || (uVar26 = uVar26 - 1, uVar26 == 0)) break;
          puVar25 = puVar25 + 1;
        } while( true );
      }
    }
    puVar25 = local_40b0;
    if (local_4150 < 0x21) {
      puVar25 = local_4130;
    }
    puVar25[lVar12] = 0;
    local_4158 = lVar12;
                    /* try { // try from 00b5e115 to 00b5e119 has its CatchHandler @ 00b5f6b9 */
    pUVar21 = (UVector2 *)
              CEGUI::WindowManager::createWindow
                        (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,(String *)&local_4158,
                         (String *)&local_4208);
                    /* try { // try from 00b5e125 to 00b5e129 has its CatchHandler @ 00b5f6fd */
    CEGUI::String::~String((String *)&local_4158);
                    /* try { // try from 00b5e12d to 00b5e131 has its CatchHandler @ 00b5f9e5 */
    CEGUI::String::~String((String *)&local_4208);
    if ((allocator *)(local_298[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_298[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_298[0] + -0x18));
      }
    }
    if ((allocator *)(local_288[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_288[0] + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_288[0] + -0x18));
      }
    }
                    /* try { // try from 00b5e16e to 00b5e1e1 has its CatchHandler @ 00b5fbb5 */
    CEGUI::String::~String((String *)&local_42b8);
    CEGUI::Window::addChildWindow(*(Window **)(*(long *)(pCVar36 + 0x10c0) + 0xb0));
    pUVar21[0x213] = (UVector2)0x0;
    bVar37 = SUB81(pUVar21,0);
    CEGUI::Window::setWantsMultiClickEvents(bVar37);
    pUVar21[0x3e2] = (UVector2)0x1;
    CEGUI::EventSet::setMutedState((bool)(bVar37 + '8'));
    CEGUI::Window::getPosition();
    CEGUI::Window::setPosition(pUVar21);
    CEGUI::Window::getSize();
                    /* try { // try from 00b5e1e8 to 00b5e1ec has its CatchHandler @ 00b5f972 */
    CEGUI::Window::setSize(pUVar21);
                    /* try { // try from 00b5e1f5 to 00b5e1f9 has its CatchHandler @ 00b5fbb5 */
    CEGUI::Window::setAlwaysOnTop(bVar37);
    *(UVector2 **)(pCVar36 + 0x1b00) = pUVar21;
    local_44f8 = local_44f8 + 1;
    pCVar36 = pCVar36 + 8;
    if (local_44f8 == 0x40) {
      iVar7 = 0;
      local_44d0 = this;
      do {
        iVar7 = iVar7 + 1;
                    /* try { // try from 00b5e236 to 00b5e23a has its CatchHandler @ 00b5fd15 */
        STRINGS::GetValueAsString((uint)local_2a8);
                    /* try { // try from 00b5e250 to 00b5e254 has its CatchHandler @ 00b5f96a */
        std::operator+((char *)local_2b8,(string *)0xfef7ca);
        local_4360 = 0x20;
        local_4358 = 0;
        local_4348 = 0;
        local_4350 = 0;
        local_42c0 = (undefined4 *)0x0;
        local_4368 = 0;
        local_4340[0] = 0;
        lVar12 = *(long *)(local_2b8[0] + -0x18);
                    /* try { // try from 00b5e2ba to 00b5e2be has its CatchHandler @ 00b5f5ee */
        CEGUI::String::grow((ulong)&local_4368);
        puVar23 = local_4340;
        if (0x20 < local_4360) {
          puVar23 = local_42c0;
        }
        puVar23[lVar12] = 0;
        lVar32 = lVar12;
        while (lVar32 != 0) {
          lVar32 = lVar32 + -1;
          puVar23 = local_4340;
          if (0x20 < local_4360) {
            puVar23 = local_42c0;
          }
          puVar23[lVar32] = (uint)*(byte *)(local_2b8[0] + lVar32);
        }
        local_4368 = lVar12;
                    /* try { // try from 00b5e324 to 00b5e328 has its CatchHandler @ 00b5f5c4 */
        lVar12 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x28));
                    /* try { // try from 00b5e32f to 00b5e333 has its CatchHandler @ 00b5f5ee */
        CEGUI::String::~String((String *)&local_4368);
        if ((allocator *)(local_2b8[0] + -0x18) !=
            (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_2b8[0] + -8);
          iVar8 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar8 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_2b8[0] + -0x18));
          }
        }
        if ((allocator *)(local_2a8[0] + -0x18) !=
            (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_2a8[0] + -8);
          iVar8 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar8 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_2a8[0] + -0x18));
          }
        }
        *(undefined1 *)(lVar12 + 0x213) = 0;
                    /* try { // try from 00b5e374 to 00b5e38f has its CatchHandler @ 00b5fd15 */
        CEGUI::Window::setWantsMultiClickEvents(SUB81(lVar12,0));
        pcVar4 = *(code **)(*(long *)(lVar12 + 0x38) + 0x10);
        local_2c8[0] = operator_new(0x20);
        lVar32 = lVar12 + 0x38;
        *local_2c8[0] = &PTR__MemberFunctionSlot_00fefcd0;
        local_2c8[0][2] = 0;
        local_2c8[0][1] = handle_SpellMouseOver;
        local_2c8[0][3] = this;
                    /* try { // try from 00b5e3cf to 00b5e40a has its CatchHandler @ 00b5f541 */
        (*pcVar4)(&local_638,lVar32,CEGUI::Window::EventMouseEnters,local_2c8);
        pBVar6 = local_638;
        if ((local_638 != (BoundSlot *)0x0) &&
           (iVar8 = *local_630, *local_630 = iVar8 + -1, iVar8 + -1 == 0)) {
          if (local_638 != (BoundSlot *)0x0) {
            CEGUI::BoundSlot::~BoundSlot(local_638);
            operator_delete(pBVar6);
          }
          operator_delete(local_630);
          local_638 = (BoundSlot *)0x0;
          local_630 = (int *)0x0;
        }
                    /* try { // try from 00b5e442 to 00b5e45d has its CatchHandler @ 00b5fd15 */
        CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_2c8);
        pcVar4 = *(code **)(*(long *)(lVar12 + 0x38) + 0x10);
        local_2d8[0] = operator_new(0x20);
        *local_2d8[0] = &PTR__MemberFunctionSlot_00fefcd0;
        local_2d8[0][2] = 0;
        local_2d8[0][1] = handle_SpellMouseOver;
        local_2d8[0][3] = this;
                    /* try { // try from 00b5e499 to 00b5e4d4 has its CatchHandler @ 00b5f52c */
        (*pcVar4)(&local_648,lVar32,CEGUI::Window::EventMouseMove,local_2d8);
        pBVar6 = local_648;
        if ((local_648 != (BoundSlot *)0x0) &&
           (iVar8 = *local_640, *local_640 = iVar8 + -1, iVar8 + -1 == 0)) {
          if (local_648 != (BoundSlot *)0x0) {
            CEGUI::BoundSlot::~BoundSlot(local_648);
            operator_delete(pBVar6);
          }
          operator_delete(local_640);
          local_648 = (BoundSlot *)0x0;
          local_640 = (int *)0x0;
        }
                    /* try { // try from 00b5e50c to 00b5e527 has its CatchHandler @ 00b5fd15 */
        CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_2d8);
        pcVar4 = *(code **)(*(long *)(lVar12 + 0x38) + 0x10);
        local_2e8[0] = operator_new(0x20);
        *local_2e8[0] = &PTR__MemberFunctionSlot_00fefcd0;
        local_2e8[0][2] = 0;
        local_2e8[0][1] = handle_SpellMouseOut;
        local_2e8[0][3] = this;
                    /* try { // try from 00b5e563 to 00b5e59e has its CatchHandler @ 00b5f517 */
        (*pcVar4)(&local_658,lVar32,CEGUI::Window::EventMouseLeaves,local_2e8);
        pBVar6 = local_658;
        if ((local_658 != (BoundSlot *)0x0) &&
           (iVar8 = *local_650, *local_650 = iVar8 + -1, iVar8 + -1 == 0)) {
          if (local_658 != (BoundSlot *)0x0) {
            CEGUI::BoundSlot::~BoundSlot(local_658);
            operator_delete(pBVar6);
          }
          operator_delete(local_650);
          local_658 = (BoundSlot *)0x0;
          local_650 = (int *)0x0;
        }
                    /* try { // try from 00b5e5d6 to 00b5e5f1 has its CatchHandler @ 00b5fd15 */
        CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_2e8);
        pcVar4 = *(code **)(*(long *)(lVar12 + 0x38) + 0x10);
        local_2f8[0] = operator_new(0x20);
        *local_2f8[0] = &PTR__MemberFunctionSlot_00fefcd0;
        local_2f8[0][2] = 0;
        local_2f8[0][1] = handle_SetSpell;
        local_2f8[0][3] = this;
                    /* try { // try from 00b5e62d to 00b5e663 has its CatchHandler @ 00b5f502 */
        (*pcVar4)(&local_668,lVar32,CEGUI::Window::EventMouseButtonDown,local_2f8);
        pBVar6 = local_668;
        if ((local_668 != (BoundSlot *)0x0) &&
           (iVar8 = *local_660, *local_660 = iVar8 + -1, iVar8 + -1 == 0)) {
          if (local_668 != (BoundSlot *)0x0) {
            CEGUI::BoundSlot::~BoundSlot(local_668);
            operator_delete(pBVar6);
          }
          operator_delete(local_660);
          local_668 = (BoundSlot *)0x0;
          local_660 = (int *)0x0;
        }
                    /* try { // try from 00b5e699 to 00b5e6bf has its CatchHandler @ 00b5fd15 */
        CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_2f8);
        CEGUI::Window::setID((uint)lVar12);
        *(long *)(local_44d0 + 0x8dc8) = lVar12;
        CEGUI::Window::setID((uint)lVar12);
        local_44d0 = local_44d0 + 8;
      } while (iVar7 != 4);
      local_4410 = 0x20;
      local_4408 = 0;
      local_43f8 = 0;
      local_4400 = 0;
      local_4370 = (uint *)0x0;
      local_4418 = 0;
      local_43f0[0] = 0;
                    /* try { // try from 00b5ef75 to 00b5ef79 has its CatchHandler @ 00b5fd15 */
      CEGUI::String::grow((ulong)&local_4418);
      puVar25 = local_43f0;
      if (0x20 < local_4410) {
        puVar25 = local_4370;
      }
      pcVar34 = "Money";
      do {
        bVar3 = *pcVar34;
        pcVar34 = pcVar34 + 1;
        *puVar25 = (uint)bVar3;
        puVar25 = puVar25 + 1;
      } while ((byte *)pcVar34 != (byte *)0xfef7b0);
      local_4418 = 5;
      puVar25 = local_43dc;
      if (0x20 < local_4410) {
        puVar25 = local_4370 + 5;
      }
      *puVar25 = 0;
                    /* try { // try from 00b5efdf to 00b5efe3 has its CatchHandler @ 00b5f47e */
      uVar14 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x48));
      *(undefined8 *)(this + 0x9190) = uVar14;
                    /* try { // try from 00b5efee to 00b5f045 has its CatchHandler @ 00b5fd15 */
      CEGUI::String::~String((String *)&local_4418);
      local_44c0 = 0x20;
      local_44b8 = 0;
      local_44a8 = 0;
      local_44b0 = 0;
      local_4420 = (uint *)0x0;
      local_44c8 = 0;
      local_44a0[0] = 0;
      CEGUI::String::grow((ulong)&local_44c8);
      puVar25 = local_44a0;
      if (0x20 < local_44c0) {
        puVar25 = local_4420;
      }
      pcVar34 = "WeaponSwitch";
      do {
        bVar3 = *pcVar34;
        pcVar34 = pcVar34 + 1;
        *puVar25 = (uint)bVar3;
        puVar25 = puVar25 + 1;
      } while ((byte *)pcVar34 != (byte *)0xfef7aa);
      local_44c8 = 0xc;
      puVar25 = local_4470;
      if (0x20 < local_44c0) {
        puVar25 = local_4420 + 0xc;
      }
      *puVar25 = 0;
                    /* try { // try from 00b5f0a2 to 00b5f0a6 has its CatchHandler @ 00b5f46e */
      uVar14 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x28));
      *(undefined8 *)(this + 0x9198) = uVar14;
                    /* try { // try from 00b5f0b1 to 00b5f0b5 has its CatchHandler @ 00b5fd15 */
      CEGUI::String::~String((String *)&local_44c8);
      pcVar4 = *(code **)(**(long **)(this + 0x9140) + 0x1a8);
                    /* try { // try from 00b5f0df to 00b5f0e3 has its CatchHandler @ 00b5f461 */
      std::string::string((string *)local_308,"WardrobeCam",&local_41);
                    /* try { // try from 00b5f0ee to 00b5f0f0 has its CatchHandler @ 00b5f451 */
      uVar14 = (*pcVar4)(*(undefined8 *)(this + 0x9140),(string *)local_308);
      *(undefined8 *)(this + 0x9148) = uVar14;
      if ((allocator *)(local_308[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_308[0] + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_308[0] + -0x18));
        }
      }
      local_408 = 0;
      local_404 = 0x3f800000;
      local_400 = 0x40600000;
                    /* try { // try from 00b5f141 to 00b5f1c5 has its CatchHandler @ 00b5fd15 */
      Ogre::Camera::setPosition(*(Vector3 **)(this + 0x9148));
      local_418 = 0;
      local_414 = 0x3f800000;
      local_410 = 0;
      Ogre::Camera::lookAt(*(Vector3 **)(this + 0x9148));
      (**(code **)(**(long **)(this + 0x9148) + 600))(DAT_00fa480c);
      (**(code **)(**(long **)(this + 0x9148) + 0x268))(DAT_00fb2bd8);
      uVar14 = *(undefined8 *)(*(long *)(this + 0x70) + 0x488);
      this_02 = (CRunicCore *)Ogre::NedAllocImpl::allocBytes(0x178,(char *)0x0,0,(char *)0x0);
      uVar5 = *(undefined8 *)(this + 0x70);
                    /* try { // try from 00b5f1d0 to 00b5f1d4 has its CatchHandler @ 00b5f420 */
      CRunicCore::CRunicCore(this_02);
      *(undefined ***)this_02 = &PTR__CSkillTooltip_00fe5f30;
      *(undefined8 *)(this_02 + 0x10) = uVar5;
                    /* try { // try from 00b5f1ea to 00b5f1ee has its CatchHandler @ 00b5f40b */
      std::wstring::wstring
                ((wstring_conflict *)(this_02 + 0x18),(wstring_conflict *)&::EMPTY_WSTRING);
      *(undefined4 *)(this_02 + 0x20) = 0xffffffff;
      *(undefined8 *)(this_02 + 0x28) = uVar14;
      *(CRunicCore **)(this + 0x91a0) = this_02;
                    /* try { // try from 00b5f219 to 00b5f21d has its CatchHandler @ 00b5f406 */
      std::wstring::wstring((wstring_conflict *)local_318,L"media/UI/skilltooltip.layout",&local_42)
      ;
                    /* try { // try from 00b5f22c to 00b5f230 has its CatchHandler @ 00b5f3c9 */
      CSkillTooltip::load(*(CSkillTooltip **)(this + 0x91a0),*(undefined8 *)(this + 0x70),
                          (wstring_conflict *)local_318);
      if ((allocator *)(local_318[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_318[0] + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_318[0] + -0x18));
        }
      }
      if ((allocator *)(local_6c8 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
      {
        LOCK();
        piVar1 = (int *)(local_6c8 + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_6c8 + -0x18));
        }
      }
      if ((allocator *)(local_6d8 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
         ) {
        LOCK();
        piVar1 = (int *)(local_6d8 + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_6d8 + -0x18));
        }
      }
      if ((allocator *)(local_6e0 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
      {
        LOCK();
        piVar1 = (int *)(local_6e0 + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_6e0 + -0x18));
        }
      }
      if ((allocator *)(local_6e8 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
      {
        LOCK();
        piVar1 = (int *)(local_6e8 + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_6e8 + -0x18));
        }
      }
      if (local_698 != (void *)0x0) {
        Ogre::NedAllocImpl::deallocBytes(local_698);
      }
      return;
    }
  } while( true );
}

/* address=00b60770
   symbol=CInventoryMenu::CInventoryMenu */

/* WARNING: Removing unreachable block (ram,0x00b60d9b) */
/* WARNING: Removing unreachable block (ram,0x00b60ec3) */
/* WARNING: Removing unreachable block (ram,0x00b60eb5) */
/* WARNING: Removing unreachable block (ram,0x00b60d29) */
/* WARNING: Removing unreachable block (ram,0x00b60e8e) */
/* CInventoryMenu::CInventoryMenu(CGameUI&, CSettings&, Ogre::RenderWindow*, Ogre::SceneManager*,
   Ogre::SceneManager*, CEGUI::Window*, CResourceManager*) */

void __thiscall
CInventoryMenu::CInventoryMenu
          (CInventoryMenu *this,CGameUI *param_1,CSettings *param_2,RenderWindow *param_3,
          SceneManager *param_4,SceneManager *param_5,Window *param_6,CResourceManager *param_7)

{
  int *piVar1;
  CSoundBankDataInformation *this_00;
  CSoundManager *pCVar2;
  int iVar3;
  long lVar4;
  CSoundBank *this_01;
  long local_98 [2];
  long local_88 [2];
  long local_78 [2];
  long local_68 [2];
  long local_58 [3];
  allocator local_3d;
  allocator local_3c;
  allocator local_3b;
  allocator local_3a;
  allocator local_39 [9];

  CRunicCore::CRunicCore((CRunicCore *)this);
  *(CSettings **)(this + 0x68) = param_2;
  *(undefined ***)this = &PTR__CInventoryMenu_00fefb70;
  *(undefined ***)(this + 0x10) = &PTR__CInventoryMenu_00fefc20;
  *(undefined8 *)(this + 0x50) = 0;
  *(undefined8 *)(this + 0x58) = 0;
  *(Window **)(this + 0x18) = param_6;
  this[0x60] = (CInventoryMenu)0x0;
  lVar4 = 0;
  this[0x61] = (CInventoryMenu)0x1;
  this[0x62] = (CInventoryMenu)0x0;
  *(CGameUI **)(this + 0x70) = param_1;
  *(undefined4 *)(this + 0x78) = 0xffffffff;
  *(undefined4 *)(this + 0x7c) = 0xffffffff;
  *(undefined8 *)(this + 0x1020) = 0;
  do {
    *(undefined8 *)(this + lVar4 + 0x1d10) = 0x20;
    *(undefined8 *)(this + lVar4 + 0x1d18) = 0;
    *(undefined8 *)(this + lVar4 + 0x1d28) = 0;
    *(undefined8 *)(this + lVar4 + 0x1d20) = 0;
    *(undefined8 *)(this + lVar4 + 0x1db0) = 0;
    *(undefined8 *)(this + lVar4 + 0x1d08) = 0;
    *(undefined4 *)(this + lVar4 + 0x1d30) = 0;
    lVar4 = lVar4 + 0xb0;
  } while (lVar4 != 0x3860);
  lVar4 = 0;
  do {
    *(undefined8 *)(this + lVar4 + 0x5570) = 0x20;
    *(undefined8 *)(this + lVar4 + 0x5578) = 0;
    *(undefined8 *)(this + lVar4 + 0x5588) = 0;
    *(undefined8 *)(this + lVar4 + 0x5580) = 0;
    *(undefined8 *)(this + lVar4 + 0x5610) = 0;
    *(undefined8 *)(this + lVar4 + 0x5568) = 0;
    *(undefined4 *)(this + lVar4 + 0x5590) = 0;
    lVar4 = lVar4 + 0xb0;
  } while (lVar4 != 0x3860);
  *(SceneManager **)(this + 0x9138) = param_4;
  *(SceneManager **)(this + 0x9140) = param_5;
  *(RenderWindow **)(this + 0x9150) = param_3;
  *(undefined8 *)(this + 0x9158) = 0;
  this[0x9160] = (CInventoryMenu)0x0;
  *(CResourceManager **)(this + 0x9178) = param_7;
  this[0x9161] = (CInventoryMenu)0x0;
  lVar4 = 0;
  this[0x9162] = (CInventoryMenu)0x0;
  this[0x9163] = (CInventoryMenu)0x0;
  *(undefined8 *)(this + 0x9168) = 0xffffffffffffffff;
  *(undefined8 *)(this + 0x9170) = 0;
  *(undefined4 *)(this + 0x9184) = 0x459c4000;
  *(undefined8 *)(this + 0x9188) = 0;
  *(undefined8 *)(this + 0x91a0) = 0;
  *(undefined4 *)(this + 0x91ac) = 0;
  do {
    *(undefined8 *)(this + lVar4 + 0x91b8) = 0x20;
    *(undefined8 *)(this + lVar4 + 0x91c0) = 0;
    *(undefined8 *)(this + lVar4 + 0x91d0) = 0;
    *(undefined8 *)(this + lVar4 + 0x91c8) = 0;
    *(undefined8 *)(this + lVar4 + 0x9258) = 0;
    *(undefined8 *)(this + lVar4 + 0x91b0) = 0;
    *(undefined4 *)(this + lVar4 + 0x91d8) = 0;
    lVar4 = lVar4 + 0xb0;
  } while (lVar4 != 0x210);
  lVar4 = 0;
  do {
    *(undefined8 *)(this + lVar4 + 0x93c8) = 0x20;
    *(undefined8 *)(this + lVar4 + 0x93d0) = 0;
    *(undefined8 *)(this + lVar4 + 0x93e0) = 0;
    *(undefined8 *)(this + lVar4 + 0x93d8) = 0;
    *(undefined8 *)(this + lVar4 + 0x9468) = 0;
    *(undefined8 *)(this + lVar4 + 0x93c0) = 0;
    *(undefined4 *)(this + lVar4 + 0x93e8) = 0;
    lVar4 = lVar4 + 0xb0;
  } while (lVar4 != 0x210);
                    /* try { // try from 00b60a12 to 00b60a3e has its CatchHandler @ 00b60c6d */
  lVar4 = CMasterResourceManager::getSingleton();
  this_00 = *(CSoundBankDataInformation **)(lVar4 + 0x100);
  lVar4 = CMasterResourceManager::getSingleton();
  pCVar2 = *(CSoundManager **)(lVar4 + 0x98);
  this_01 = (CSoundBank *)Ogre::NedAllocImpl::allocBytes(0xd0,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00b60a4e to 00b60a52 has its CatchHandler @ 00b60e15 */
  CSoundBank::CSoundBank(this_01,pCVar2,false);
  *(CSoundBank **)(this + 0x9188) = this_01;
                    /* try { // try from 00b60a6f to 00b60a73 has its CatchHandler @ 00b60e10 */
  std::wstring::wstring((wstring_conflict *)local_58,L"INVENTORYOPEN",local_39);
                    /* try { // try from 00b60a7c to 00b60a80 has its CatchHandler @ 00b60e27 */
  lVar4 = CSoundBankDataInformation::getSoundDataObject(this_00,(wstring_conflict *)local_58);
  if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_58[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
    }
  }
  if (lVar4 != 0) {
                    /* try { // try from 00b60aad to 00b60ab1 has its CatchHandler @ 00b60c6d */
    CSoundBank::addSample(*(CSoundBank **)(this + 0x9188),0x16,*(longlong *)(lVar4 + 0x20));
  }
                    /* try { // try from 00b60ac1 to 00b60ac5 has its CatchHandler @ 00b60e89 */
  std::wstring::wstring((wstring_conflict *)local_68,L"INVENTORYCLOSE",&local_3a);
                    /* try { // try from 00b60ace to 00b60ad2 has its CatchHandler @ 00b60dfe */
  lVar4 = CSoundBankDataInformation::getSoundDataObject(this_00,(wstring_conflict *)local_68);
  if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_68[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
    }
  }
  if (lVar4 != 0) {
                    /* try { // try from 00b60b00 to 00b60b04 has its CatchHandler @ 00b60c6d */
    CSoundBank::addSample(*(CSoundBank **)(this + 0x9188),0x42,*(longlong *)(lVar4 + 0x20));
  }
                    /* try { // try from 00b60b14 to 00b60b18 has its CatchHandler @ 00b60cd1 */
  std::wstring::wstring((wstring_conflict *)local_78,L"ASSIGNSKILL",&local_3b);
                    /* try { // try from 00b60b21 to 00b60b25 has its CatchHandler @ 00b60d17 */
  lVar4 = CSoundBankDataInformation::getSoundDataObject(this_00,(wstring_conflict *)local_78);
  if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_78[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
    }
  }
  if (lVar4 != 0) {
                    /* try { // try from 00b60b53 to 00b60b57 has its CatchHandler @ 00b60c6d */
    CSoundBank::addSample(*(CSoundBank **)(this + 0x9188),0x1e,*(longlong *)(lVar4 + 0x20));
  }
                    /* try { // try from 00b60b67 to 00b60b6b has its CatchHandler @ 00b60ce2 */
  std::wstring::wstring((wstring_conflict *)local_88,L"ERROR",&local_3c);
                    /* try { // try from 00b60b74 to 00b60b78 has its CatchHandler @ 00b60cd3 */
  lVar4 = CSoundBankDataInformation::getSoundDataObject(this_00,(wstring_conflict *)local_88);
  if ((allocator *)(local_88[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_88[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
    }
  }
  if (lVar4 != 0) {
                    /* try { // try from 00b60ba6 to 00b60baa has its CatchHandler @ 00b60c6d */
    CSoundBank::addSample(*(CSoundBank **)(this + 0x9188),0x18,*(longlong *)(lVar4 + 0x20));
  }
                    /* try { // try from 00b60bba to 00b60bbe has its CatchHandler @ 00b60d34 */
  std::wstring::wstring((wstring_conflict *)local_98,L"WEAPONSWAP",&local_3d);
                    /* try { // try from 00b60bc7 to 00b60bcb has its CatchHandler @ 00b60d6c */
  lVar4 = CSoundBankDataInformation::getSoundDataObject(this_00,(wstring_conflict *)local_98);
  if ((allocator *)(local_98[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_98[0] + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
    }
  }
  if (lVar4 != 0) {
                    /* try { // try from 00b60bf9 to 00b60c5a has its CatchHandler @ 00b60c6d */
    CSoundBank::addSample(*(CSoundBank **)(this + 0x9188),0x12,*(longlong *)(lVar4 + 0x20));
  }
  iVar3 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0x68),KSETTINGS_RES_WIDTH);
  CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0x68),KSETTINGS_RES_HEIGHT);
  this[0x91a8] = (CInventoryMenu)0x0;
  *(float *)(this + 0x9180) = (float)iVar3;
  this[0x91a9] = (CInventoryMenu)0x0;
  this[0x91aa] = (CInventoryMenu)0x0;
  createMenus(this);
  return;
}

/* address=00b60ed0
   symbol=CInventoryMenu::isRight */

/* CInventoryMenu::isRight() */

undefined8 CInventoryMenu::isRight(void)

{
  return 1;
}

/* address=00b60ee0
   symbol=CInventoryMenu::open */

/* CInventoryMenu::open() */

byte __thiscall CInventoryMenu::open(CInventoryMenu *this)

{
  byte bVar1;

  bVar1 = 1;
  if (this[0x60] == (CInventoryMenu)0x0) {
    bVar1 = (byte)this[0x61] ^ 1;
  }
  return bVar1;
}

/* address=00b60f00
   symbol=CInventoryMenu::openPartial */

/* CInventoryMenu::openPartial() */

CInventoryMenu __thiscall CInventoryMenu::openPartial(CInventoryMenu *this)

{
  return this[0x60];
}

/* address=00b60f10
   symbol=CInventoryMenu::screenEdge */

/* CInventoryMenu::screenEdge() */

undefined4 __thiscall CInventoryMenu::screenEdge(CInventoryMenu *this)

{
  return *(undefined4 *)(this + 0x9180);
}

/* address=00b60f20
   symbol=CInventoryMenu::getOwner */

/* CInventoryMenu::getOwner() */

undefined8 __thiscall CInventoryMenu::getOwner(CInventoryMenu *this)

{
  return *(undefined8 *)(this + 0x50);
}

/* export-summary functions=48 failures=0 */
