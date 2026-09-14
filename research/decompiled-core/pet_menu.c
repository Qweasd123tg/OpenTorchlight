/* Targeted Ghidra class export.
   namespace=CPetMenu
   Treat pseudocode as navigation evidence. */


/* address=00b88720
   symbol=CPetMenu::equipmentDropped */

/* non-virtual thunk to CPetMenu::equipmentDropped(CEquipment*) */

void __thiscall CPetMenu::equipmentDropped(CPetMenu *this,CEquipment *param_1)

{
  equipmentDropped((CEquipment *)(this + -0x10));
  return;
}

/* address=00b88730
   symbol=CPetMenu::equipmentDropped */

/* CPetMenu::equipmentDropped(CEquipment*) */

void CPetMenu::equipmentDropped(CEquipment *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x00b88737. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)param_1 + 0x48))();
  return;
}

/* address=00b88740
   symbol=CPetMenu::equipmentEquipped */

/* non-virtual thunk to CPetMenu::equipmentEquipped(CEquipment*) */

void __thiscall CPetMenu::equipmentEquipped(CPetMenu *this,CEquipment *param_1)

{
  equipmentEquipped((CEquipment *)(this + -0x10));
  return;
}

/* address=00b88750
   symbol=CPetMenu::equipmentEquipped */

/* CPetMenu::equipmentEquipped(CEquipment*) */

void CPetMenu::equipmentEquipped(CEquipment *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x00b88757. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)param_1 + 0x48))();
  return;
}

/* address=00b88760
   symbol=CPetMenu::equipmentUsed */

/* non-virtual thunk to CPetMenu::equipmentUsed(CEquipment*) */

void __thiscall CPetMenu::equipmentUsed(CPetMenu *this,CEquipment *param_1)

{
  equipmentUsed((CEquipment *)(this + -0x10));
  return;
}

/* address=00b88770
   symbol=CPetMenu::equipmentUsed */

/* CPetMenu::equipmentUsed(CEquipment*) */

void CPetMenu::equipmentUsed(CEquipment *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x00b88777. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)param_1 + 0x48))();
  return;
}

/* address=00b88780
   symbol=CPetMenu::inventoryDestroyed */

/* non-virtual thunk to CPetMenu::inventoryDestroyed() */

void __thiscall CPetMenu::inventoryDestroyed(CPetMenu *this)

{
  inventoryDestroyed();
  return;
}

/* address=00b88790
   symbol=CPetMenu::inventoryDestroyed */

/* CPetMenu::inventoryDestroyed() */

void CPetMenu::inventoryDestroyed(void)

{
  return;
}

/* address=00b887a0
   symbol=CPetMenu::handle_ItemClick */

/* CPetMenu::handle_ItemClick(CEGUI::EventArgs const&) */

undefined8 __thiscall CPetMenu::handle_ItemClick(CPetMenu *this,EventArgs *param_1)

{
  undefined4 uVar1;

  if (*(long *)(param_1 + 0x10) != 0) {
    uVar1 = **(undefined4 **)(*(long *)(param_1 + 0x10) + 0x1d8);
    if (*(int *)(param_1 + 0x28) == 0) {
      *(undefined4 *)(this + 0x98) = uVar1;
      return 1;
    }
    if (*(int *)(param_1 + 0x28) == 1) {
      *(undefined4 *)(this + 0x9c) = uVar1;
      return 1;
    }
  }
  return 1;
}

/* address=00b887f0
   symbol=CPetMenu::handle_CloseButton */

/* CPetMenu::handle_CloseButton(CEGUI::EventArgs const&) */

undefined8 __thiscall CPetMenu::handle_CloseButton(CPetMenu *this,EventArgs *param_1)

{
  if (*(int *)(param_1 + 0x28) == 0) {
    this[0x6a] = (CPetMenu)0x1;
  }
  return 1;
}

/* address=00b88810
   symbol=CPetMenu::handle_RotateLeft */

/* CPetMenu::handle_RotateLeft(CEGUI::EventArgs const&) */

undefined8 CPetMenu::handle_RotateLeft(EventArgs *param_1)

{
  param_1[0x9198] = (EventArgs)0x1;
  return 1;
}

/* address=00b88820
   symbol=CPetMenu::handle_EndRotateLeft */

/* CPetMenu::handle_EndRotateLeft(CEGUI::EventArgs const&) */

undefined8 CPetMenu::handle_EndRotateLeft(EventArgs *param_1)

{
  param_1[0x9198] = (EventArgs)0x0;
  return 1;
}

/* address=00b88830
   symbol=CPetMenu::handle_RotateRight */

/* CPetMenu::handle_RotateRight(CEGUI::EventArgs const&) */

undefined8 CPetMenu::handle_RotateRight(EventArgs *param_1)

{
  param_1[0x9199] = (EventArgs)0x1;
  return 1;
}

/* address=00b88840
   symbol=CPetMenu::handle_EndRotateRight */

/* CPetMenu::handle_EndRotateRight(CEGUI::EventArgs const&) */

undefined8 CPetMenu::handle_EndRotateRight(EventArgs *param_1)

{
  param_1[0x9199] = (EventArgs)0x0;
  return 1;
}

/* address=00b88850
   symbol=CPetMenu::handle_MouseThrough */

/* CPetMenu::handle_MouseThrough(CEGUI::EventArgs const&) */

undefined8 CPetMenu::handle_MouseThrough(EventArgs *param_1)

{
  param_1[0x9188] = (EventArgs)0x0;
  param_1[0x9189] = (EventArgs)0x0;
  return 1;
}

/* address=00b88870
   symbol=CPetMenu::handle_onClick */

/* CPetMenu::handle_onClick(CEGUI::EventArgs const&) */

undefined8 __thiscall CPetMenu::handle_onClick(CPetMenu *this,EventArgs *param_1)

{
  undefined8 uVar1;

  if ((*(int *)(param_1 + 0x28) == 0) && (*(long *)(param_1 + 0x10) != 0)) {
                    /* WARNING: Could not recover jumptable at 0x00b88893. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(*(long *)this + 0x98))
                      (this,**(undefined4 **)(*(long *)(param_1 + 0x10) + 0x1d8));
    return uVar1;
  }
  return 1;
}

/* address=00b888a0
   symbol=CPetMenu::setTab */

/* CPetMenu::setTab(int) */

void __thiscall CPetMenu::setTab(CPetMenu *this,int param_1)

{
                    /* WARNING: Could not recover jumptable at 0x00b888ad. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)this + 0x98))(this,param_1 + 0xe);
  return;
}

/* address=00b888b0
   symbol=CPetMenu::handle_SpellMouseOver */

/* CPetMenu::handle_SpellMouseOver(CEGUI::EventArgs const&) */

undefined8 __thiscall CPetMenu::handle_SpellMouseOver(CPetMenu *this,EventArgs *param_1)

{
  undefined8 uVar1;

  if (*(long *)(param_1 + 0x10) != 0) {
    uVar1 = **(undefined8 **)(*(long *)(param_1 + 0x10) + 0x1d8);
    this[0x9189] = (CPetMenu)0x1;
    *(undefined8 *)(this + 0x9190) = uVar1;
  }
  return 1;
}

/* address=00b888e0
   symbol=CPetMenu::handle_SpellMouseOut */

/* CPetMenu::handle_SpellMouseOut(CEGUI::EventArgs const&) */

undefined8 CPetMenu::handle_SpellMouseOut(EventArgs *param_1)

{
  return 1;
}

/* address=00b888f0
   symbol=CPetMenu::onClick */

/* CPetMenu::onClick(ELayoutFunction) */

undefined8 __thiscall CPetMenu::onClick(CPetMenu *this,int param_2)

{
  String *this_00;
  String aSStack_228 [176];
  String local_178 [176];
  String local_c8 [184];

  if (this[0x68] == (CPetMenu)0x0) {
    return 1;
  }
  if (param_2 == 0xf) {
    this_00 = local_178;
    CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x91d8),0));
    CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x91e0),0));
    CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x91e8),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x91c0),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x91c8),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x91d0),0));
    *(undefined4 *)(this + 0x6c) = 1;
    this[0x91f9] = (CPetMenu)0x0;
    CEGUI::String::String(this_00,"UnselectedImage");
                    /* try { // try from 00b889be to 00b889c2 has its CatchHandler @ 00b88b2b */
    CEGUI::PropertySet::setProperty(*(String **)(this + 0x91e0),this_00);
  }
  else {
    if (param_2 == 0x10) {
      CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x91d8),0));
      CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x91e0),0));
      CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x91e8),0));
      CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x91c0),0));
      CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x91c8),0));
      CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x91d0),0));
      *(undefined4 *)(this + 0x6c) = 2;
      this[0x91fa] = (CPetMenu)0x0;
      CEGUI::String::String(aSStack_228,"UnselectedImage");
                    /* try { // try from 00b88b06 to 00b88b0a has its CatchHandler @ 00b88b3e */
      CEGUI::PropertySet::setProperty(*(String **)(this + 0x91e8),aSStack_228);
      CEGUI::String::~String(aSStack_228);
      (**(code **)(*(long *)this + 0x48))(this);
      return 1;
    }
    if (param_2 != 0xe) {
      return 1;
    }
    this_00 = local_c8;
    CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x91d8),0));
    CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x91e0),0));
    CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x91e8),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x91c0),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x91c8),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x91d0),0));
    *(undefined4 *)(this + 0x6c) = 0;
    this[0x91f8] = (CPetMenu)0x0;
    CEGUI::String::String(this_00,"UnselectedImage");
                    /* try { // try from 00b88a74 to 00b88a78 has its CatchHandler @ 00b88b51 */
    CEGUI::PropertySet::setProperty(*(String **)(this + 0x91d8),this_00);
  }
  CEGUI::String::~String(this_00);
  (**(code **)(*(long *)this + 0x48))(this);
  return 1;
}

/* address=00b88b60
   symbol=CPetMenu::processInput */

/* CPetMenu::processInput(void*, float, bool) */

bool CPetMenu::processInput(void *param_1,float param_2,bool param_3)

{
  long lVar1;
  char cVar2;
  char in_DL;
  bool bVar3;

  if (in_DL == '\0') {
    *(undefined8 *)((long)param_1 + 0x1370) = 0;
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)((long)param_1 + 0x30),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)((long)param_1 + 0x40),0));
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
  bVar3 = *(char *)((long)param_1 + 0x6a) != '\0';
  if (bVar3) {
    param_2 = (float)(**(code **)(*(long *)param_1 + 0x40))(param_1,0);
    *(undefined1 *)((long)param_1 + 0x6a) = 0;
  }
  lVar1 = *(long *)(*(long *)((long)param_1 + 0x90) + 0xb8);
  if ((lVar1 == 0) || (cVar2 = CBaseUnit::ISA((CBaseUnit *)param_2,lVar1,0x78), cVar2 == '\0')) {
    if (*(long *)((long)param_1 + 0x1370) != 0) {
      if (*(char *)(*(long *)((long)param_1 + 0x1370) + 0x198) == '\0') goto LAB_00b88bcf;
      *(undefined8 *)((long)param_1 + 0x1370) = 0;
    }
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)((long)param_1 + 0x30),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)((long)param_1 + 0x40),0));
    cVar2 = *(char *)((long)param_1 + 0x9188);
  }
  else {
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)((long)param_1 + 0x40),0));
    CEGUI::Window::moveToFront();
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)((long)param_1 + 0x30),0));
    CEGUI::Window::moveToFront();
LAB_00b88bcf:
    cVar2 = *(char *)((long)param_1 + 0x9188);
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
  *(undefined4 *)((long)param_1 + 0x98) = 0xffffffff;
  *(undefined4 *)((long)param_1 + 0x9c) = 0xffffffff;
  return !bVar3;
}

/* address=00b88d40
   symbol=CPetMenu::handle_MouseOut */

/* CPetMenu::handle_MouseOut(CEGUI::EventArgs const&) */

undefined8 __thiscall CPetMenu::handle_MouseOut(CPetMenu *this,EventArgs *param_1)

{
  char cVar1;
  long lVar2;

  if (((*(long *)(param_1 + 0x10) != 0) && (*(long *)(this + 0x58) != 0)) &&
     (lVar2 = CInventory::getEquipmentInSlot
                        (*(CInventory **)(*(long *)(this + 0x58) + 0x490),
                         **(uint **)(*(long *)(param_1 + 0x10) + 0x1d8)),
     lVar2 == *(long *)(this + 0x1370))) {
    *(undefined8 *)(this + 0x1370) = 0;
    if ((*(CBaseUnit **)(*(long *)(this + 0x90) + 0xb8) != (CBaseUnit *)0x0) &&
       (cVar1 = CBaseUnit::ISA(*(CBaseUnit **)(*(long *)(this + 0x90) + 0xb8),0x78), cVar1 != '\0'))
    {
      return 1;
    }
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x30),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x40),0));
  }
  return 1;
}

/* address=00b88dd0
   symbol=CPetMenu::handle_SetSpell */

/* CPetMenu::handle_SetSpell(CEGUI::EventArgs const&) */

undefined8 __thiscall CPetMenu::handle_SetSpell(CPetMenu *this,EventArgs *param_1)

{
  long lVar1;
  long lVar2;
  CCharacter *pCVar3;
  bool bVar4;
  char cVar5;
  long lVar6;
  CAchievements *pCVar7;
  CAchievement *this_00;
  CLevel *pCVar8;

  lVar1 = *(long *)(param_1 + 0x10);
  if (lVar1 == 0) {
    return 1;
  }
  lVar6 = *(long *)(this + 0x90);
  if (*(CBaseUnit **)(lVar6 + 200) != (CBaseUnit *)0x0) {
    cVar5 = CBaseUnit::ISA(*(CBaseUnit **)(lVar6 + 200),0x29);
    if (cVar5 != '\0') {
      lVar6 = *(long *)(this + 0x90);
      bVar4 = true;
      lVar2 = *(long *)(lVar6 + 0xb8);
      goto joined_r0x00b88e5c;
    }
    lVar6 = *(long *)(this + 0x90);
  }
  lVar2 = *(long *)(lVar6 + 0xb8);
  bVar4 = false;
joined_r0x00b88e5c:
  if (lVar2 != 0) {
    cVar5 = CBaseUnit::ISA();
    if ((cVar5 != '\0') && (!bVar4)) {
      pCVar3 = *(CCharacter **)(this + 0x58);
      if ((*(int *)(pCVar3 + 0x330) != 0x2a) && (*(int *)(pCVar3 + 0x330) != 0x29)) {
        pCVar8 = (CLevel *)0x0;
        if (*(long *)(pCVar3 + 0x68) != 0) {
          pCVar8 = *(CLevel **)(*(long *)(pCVar3 + 0x68) + 0x18);
        }
        CGameUI::performItemUse
                  (*(CGameUI **)(this + 0x90),pCVar8,
                   *(CEquipment **)(*(CGameUI **)(this + 0x90) + 0xb8),
                   *(CCharacter **)(pCVar3 + 0x640),*(CCharacter **)(pCVar3 + 0x640),pCVar3);
        (**(code **)(*(long *)this + 0x48))(this);
        pCVar7 = (CAchievements *)CAchievements::getSingleton();
        this_00 = (CAchievement *)CAchievements::getAchievement(pCVar7,0x1f);
        CAchievement::forceComplete(this_00);
        return 1;
      }
      CSoundBank::playSample(*(CSoundBank **)(this + 0x91b8),0x18,(SceneNode *)0x0,0.0,0.0,false);
      return 1;
    }
    lVar6 = *(long *)(this + 0x90);
  }
  cVar5 = CKeyManager::keyHeld((CKeyManager *)(lVar6 + 0x590),0x11);
  if (cVar5 == '\0') {
    return 1;
  }
  CCharacter::unLearnSpell(*(CCharacter **)(this + 0x58),*(int *)(lVar1 + 0x170));
  (**(code **)(*(long *)this + 0x48))(this);
  CSoundBank::playSample(*(CSoundBank **)(this + 0x91b8),0x1e,(SceneNode *)0x0,0.0,0.0,false);
  return 1;
}

/* address=00b88f70
   symbol=CPetMenu::setOwner */

/* CPetMenu::setOwner(CCharacter*) */

void __thiscall CPetMenu::setOwner(CPetMenu *this,CCharacter *param_1)

{
  CCharacter *pCVar1;
  CCharacter *pCVar2;

  pCVar1 = *(CCharacter **)(this + 0x58);
  pCVar2 = param_1;
  if (pCVar1 != param_1) {
    (**(code **)(*(long *)this + 0x90))();
    pCVar2 = *(CCharacter **)(this + 0x58);
  }
  if ((pCVar2 != (CCharacter *)0x0) && (*(CInventory **)(pCVar2 + 0x490) != (CInventory *)0x0)) {
    CInventory::removeListener(*(CInventory **)(pCVar2 + 0x490),(iInventoryListener *)(this + 0x10))
    ;
  }
  *(CCharacter **)(this + 0x58) = param_1;
  if ((param_1 != (CCharacter *)0x0) && (*(CInventory **)(param_1 + 0x490) != (CInventory *)0x0)) {
    CInventory::addListener(*(CInventory **)(param_1 + 0x490),(iInventoryListener *)(this + 0x10));
  }
  if (pCVar1 != param_1) {
    (**(code **)(*(long *)this + 0x48))(this);
  }
  this[0x91f8] = (CPetMenu)0x0;
  this[0x91f9] = (CPetMenu)0x0;
  this[0x91fa] = (CPetMenu)0x0;
  return;
}

/* address=00b89020
   symbol=CPetMenu::checkForUpdate */

/* CPetMenu::checkForUpdate(CEquipment*) */

void __thiscall CPetMenu::checkForUpdate(CPetMenu *this,CEquipment *param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;

  if ((param_1 != (CEquipment *)0x0) &&
     (*(CInventory **)(*(long *)(this + 0x58) + 0x490) != (CInventory *)0x0)) {
    iVar2 = CInventory::getRequiredPane(*(CInventory **)(*(long *)(this + 0x58) + 0x490),param_1);
    iVar3 = CInventory::findEquipmentSlot(*(CInventory **)(*(long *)(this + 0x58) + 0x490),param_1);
    if (0x12 < iVar3) {
      if (iVar2 == 1) {
        cVar1 = CEGUI::Window::isVisible(SUB81(*(undefined8 *)(this + 0x91c8),0));
        if (cVar1 == '\0') {
          this[0x91f9] = (CPetMenu)0x1;
        }
      }
      else if (iVar2 == 2) {
        cVar1 = CEGUI::Window::isVisible(SUB81(*(undefined8 *)(this + 0x91d0),0));
        if (cVar1 == '\0') {
          this[0x91fa] = (CPetMenu)0x1;
        }
      }
      else if (iVar2 == 0) {
        cVar1 = CEGUI::Window::isVisible(SUB81(*(undefined8 *)(this + 0x91c0),0));
        if (cVar1 == '\0') {
          this[0x91f8] = (CPetMenu)0x1;
        }
      }
    }
  }
  return;
}

/* address=00b89100
   symbol=CPetMenu::equipmentUnequipped */

/* non-virtual thunk to CPetMenu::equipmentUnequipped(CEquipment*) */

void __thiscall CPetMenu::equipmentUnequipped(CPetMenu *this,CEquipment *param_1)

{
  equipmentUnequipped(this + -0x10,param_1);
  return;
}

/* address=00b89110
   symbol=CPetMenu::equipmentUnequipped */

/* CPetMenu::equipmentUnequipped(CEquipment*) */

void __thiscall CPetMenu::equipmentUnequipped(CPetMenu *this,CEquipment *param_1)

{
  checkForUpdate(this,param_1);
                    /* WARNING: Could not recover jumptable at 0x00b89124. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)this + 0x48))(this);
  return;
}

/* address=00b89130
   symbol=CPetMenu::equipmentPickedUp */

/* non-virtual thunk to CPetMenu::equipmentPickedUp(CEquipment*) */

void __thiscall CPetMenu::equipmentPickedUp(CPetMenu *this,CEquipment *param_1)

{
  equipmentPickedUp(this + -0x10,param_1);
  return;
}

/* address=00b89140
   symbol=CPetMenu::equipmentPickedUp */

/* CPetMenu::equipmentPickedUp(CEquipment*) */

void __thiscall CPetMenu::equipmentPickedUp(CPetMenu *this,CEquipment *param_1)

{
  checkForUpdate(this,param_1);
                    /* WARNING: Could not recover jumptable at 0x00b89154. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)this + 0x48))(this);
  return;
}

/* address=00b91240
   symbol=CPetMenu::_GLOBAL__I_CPetMenu */

/* CPetMenu::CPetMenu(CGameUI&, CSettings&, Ogre::RenderWindow*, Ogre::SceneManager*,
   Ogre::SceneManager*, CEGUI::Window*, CResourceManager*) */

void CPetMenu::_GLOBAL__I_CPetMenu(void)

{
  allocator aStack_2ee;
  allocator aStack_2ed;
  allocator aStack_2ec;
  allocator aStack_2eb;
  allocator aStack_2ea;
  allocator aStack_2e9;
  allocator aStack_2e8;
  allocator aStack_2e7;
  allocator aStack_2e6;
  allocator aStack_2e5;
  allocator aStack_2e4;
  allocator aStack_2e3;
  allocator aStack_2e2;
  allocator aStack_2e1;
  allocator aStack_2e0;
  allocator aStack_2df;
  allocator aStack_2de;
  allocator aStack_2dd;
  allocator aStack_2dc;
  allocator aStack_2db;
  allocator aStack_2da;
  allocator aStack_2d9;
  allocator aStack_2d8;
  allocator aStack_2d7;
  allocator aStack_2d6;
  allocator aStack_2d5;
  allocator aStack_2d4;
  allocator aStack_2d3;
  allocator aStack_2d2;
  allocator aStack_2d1;
  allocator aStack_2d0;
  allocator aStack_2cf;
  allocator aStack_2ce;
  allocator aStack_2cd;
  allocator aStack_2cc;
  allocator aStack_2cb;
  allocator aStack_2ca;
  allocator aStack_2c9;
  allocator aStack_2c8;
  allocator aStack_2c7;
  allocator aStack_2c6;
  allocator aStack_2c5;
  allocator aStack_2c4;
  allocator aStack_2c3;
  allocator aStack_2c2;
  allocator aStack_2c1;
  allocator aStack_2c0;
  allocator aStack_2bf;
  allocator aStack_2be;
  allocator aStack_2bd;
  allocator aStack_2bc;
  allocator aStack_2bb;
  allocator aStack_2ba;
  allocator aStack_2b9;
  allocator aStack_2b8;
  allocator aStack_2b7;
  allocator aStack_2b6;
  allocator aStack_2b5;
  allocator aStack_2b4;
  allocator aStack_2b3;
  allocator aStack_2b2;
  allocator aStack_2b1;
  allocator aStack_2b0;
  allocator aStack_2af;
  allocator aStack_2ae;
  allocator aStack_2ad;
  allocator aStack_2ac;
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
  std::string::string((string *)::KLayoutFunctionNames,"GUIEXITGAME",&aStack_2ee);
  std::string::string((string *)(::KLayoutFunctionNames + 8),"GUIEXITAPPLICATION",&aStack_2ed);
  std::string::string((string *)(::KLayoutFunctionNames + 0x10),"GUINEWGAME",&aStack_2ec);
  std::string::string((string *)(::KLayoutFunctionNames + 0x18),"GUICONTINUEGAME",&aStack_2eb);
  std::string::string((string *)(::KLayoutFunctionNames + 0x20),"GUINEWGAMEMENU",&aStack_2ea);
  std::string::string((string *)(::KLayoutFunctionNames + 0x28),"GUICONTINUEGAMEMENU",&aStack_2e9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x30),"GUICLOSEMENU",&aStack_2e8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x38),"GUIBACK",&aStack_2e7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x40),"GUIDECLINE",&aStack_2e6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x48),"GUIACCEPT",&aStack_2e5);
  std::string::string((string *)(::KLayoutFunctionNames + 0x50),"GUIOK",&aStack_2e4);
  std::string::string((string *)(::KLayoutFunctionNames + 0x58),"GUIPAUSE",&aStack_2e3);
  std::string::string((string *)(::KLayoutFunctionNames + 0x60),"GUISCROLLUP",&aStack_2e2);
  std::string::string((string *)(::KLayoutFunctionNames + 0x68),"GUISCROLLDOWN",&aStack_2e1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x70),"GUISELECT1",&aStack_2e0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x78),"GUISELECT2",&aStack_2df);
  std::string::string((string *)(::KLayoutFunctionNames + 0x80),"GUISELECT3",&aStack_2de);
  std::string::string((string *)(::KLayoutFunctionNames + 0x88),"GUISELECT4",&aStack_2dd);
  std::string::string((string *)(::KLayoutFunctionNames + 0x90),"GUISELECT5",&aStack_2dc);
  std::string::string((string *)(::KLayoutFunctionNames + 0x98),"GUISELECT6",&aStack_2db);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa0),"GUISELECT7",&aStack_2da);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa8),"GUISELECT8",&aStack_2d9);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb0),"GUISELECT9",&aStack_2d8);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb8),"GUISELECT10",&aStack_2d7);
  std::string::string((string *)(::KLayoutFunctionNames + 0xc0),"GUISELECT11",&aStack_2d6);
  std::string::string((string *)(::KLayoutFunctionNames + 200),"GUISELECT12",&aStack_2d5);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd0),"GUISELECT13",&aStack_2d4);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd8),"GUISELECT14",&aStack_2d3);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe0),"GUISELECT15",&aStack_2d2);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe8),"GUISELECT16",&aStack_2d1);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf0),"GUISELECT17",&aStack_2d0);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf8),"GUISELECT18",&aStack_2cf);
  std::string::string((string *)(::KLayoutFunctionNames + 0x100),"GUISELECT19",&aStack_2ce);
  std::string::string((string *)(::KLayoutFunctionNames + 0x108),"GUISELECT20",&aStack_2cd);
  std::string::string((string *)(::KLayoutFunctionNames + 0x110),"GUISELECT21",&aStack_2cc);
  std::string::string((string *)(::KLayoutFunctionNames + 0x118),"GUISELECT22",&aStack_2cb);
  std::string::string((string *)(::KLayoutFunctionNames + 0x120),"GUISELECT23",&aStack_2ca);
  std::string::string((string *)(::KLayoutFunctionNames + 0x128),"GUISELECT24",&aStack_2c9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x130),"GUISELECT25",&aStack_2c8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x138),"GUISELECT26",&aStack_2c7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x140),"GUISELECT27",&aStack_2c6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x148),"GUISELECT28",&aStack_2c5);
  std::string::string((string *)(::KLayoutFunctionNames + 0x150),"GUISELECT29",&aStack_2c4);
  std::string::string((string *)(::KLayoutFunctionNames + 0x158),"GUISELECT30",&aStack_2c3);
  std::string::string((string *)(::KLayoutFunctionNames + 0x160),"GUISELECT31",&aStack_2c2);
  std::string::string((string *)(::KLayoutFunctionNames + 0x168),"GUISELECT32",&aStack_2c1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x170),"GUISELECT33",&aStack_2c0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x178),"GUISELECT34",&aStack_2bf);
  std::string::string((string *)(::KLayoutFunctionNames + 0x180),"GUISELECT35",&aStack_2be);
  std::string::string((string *)(::KLayoutFunctionNames + 0x188),"GUISELECT36",&aStack_2bd);
  std::string::string((string *)(::KLayoutFunctionNames + 400),"GUISELECT37",&aStack_2bc);
  std::string::string((string *)(::KLayoutFunctionNames + 0x198),"GUISELECT38",&aStack_2bb);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a0),"GUISELECT39",&aStack_2ba);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a8),"GUISELECT40",&aStack_2b9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b0),"GUISELECT41",&aStack_2b8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b8),"GUISELECT42",&aStack_2b7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c0),"GUISELECT43",&aStack_2b6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c8),"GUISELECT44",&aStack_2b5);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d0),"GUISELECT45",&aStack_2b4);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d8),"GUISELECT46",&aStack_2b3);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e0),"GUISELECT47",&aStack_2b2);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e8),"GUISELECT48",&aStack_2b1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f0),"GUISELECT49",&aStack_2b0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f8),"GUISELECT50",&aStack_2af);
  std::string::string((string *)(::KLayoutFunctionNames + 0x200),"GUISELECTA",&aStack_2ae);
  std::string::string((string *)(::KLayoutFunctionNames + 0x208),"GUISELECTB",&aStack_2ad);
  std::string::string((string *)(::KLayoutFunctionNames + 0x210),"GUISELECTC",&aStack_2ac);
  std::string::string((string *)(::KLayoutFunctionNames + 0x218),"GUISELECTD",&aStack_2ab);
  std::string::string((string *)(::KLayoutFunctionNames + 0x220),"GUIFEEDPET",&aStack_2aa);
  std::string::string((string *)(::KLayoutFunctionNames + 0x228),"GUIPETPASSIVE",&aStack_2a9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x230),"GUIPETAGGRESSIVE",&aStack_2a8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x238),"GUIPETDEFENSIVE",&aStack_2a7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x240),"GUITOGGLEINVENTORY",&aStack_2a6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x248),"GUITOGGLEQUESTS",&aStack_2a5);
  std::string::string((string *)(::KLayoutFunctionNames + 0x250),"GUITOGGLESTATS",&aStack_2a4);
  std::string::string((string *)(::KLayoutFunctionNames + 600),"GUITOGGLESKILLS",&aStack_2a3);
  std::string::string((string *)(::KLayoutFunctionNames + 0x260),"GUITOGGLEPERKS",&aStack_2a2);
  std::string::string((string *)(::KLayoutFunctionNames + 0x268),"GUITOGGLEJOURNAL",&aStack_2a1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x270),"GUITOGGLEPET",&aStack_2a0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x278),"GUITOGGLEAUTOMAP",&aStack_29f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x280),"GUITOGGLEOPTIONS",&aStack_29e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x288),"GUITOGGLEITEMNAMES",&aStack_29d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x290),"GUIAUTOMAPZOOMIN",&aStack_29c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x298),"GUIAUTOMAPZOOMOUT",&aStack_29b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a0),"GUILEVELUP",&aStack_29a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a8),"GUISTATSUP",&aStack_299);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b0),"GUISKILLUP",&aStack_298);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b8),"GUIPET1",&aStack_297);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c0),"GUIPET2",&aStack_296);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c8),"GUIPET3",&aStack_295);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d0),"GUIDELETE1",&aStack_294);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d8),"GUIDELETE2",&aStack_293);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e0),"GUIDELETE3",&aStack_292);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e8),"GUIDELETE4",&aStack_291);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f0),"GUISETTINGSMENU",&aStack_290);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f8),"GUIPETSELL",&aStack_28f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x300),"NONE",&aStack_28e);
  __cxa_atexit(::__tcf_0,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSOUNDBANK_STRINGS,L"STEP_SOUND",&aStack_28d);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 8),L"STRIKE_SOUND",&aStack_28c);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x10),L"PHYSICALHIT_SOUND",&aStack_28b);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x18),L"ICEHIT_SOUND",&aStack_28a);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x20),L"FIREHIT_SOUND",&aStack_289);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x28),L"ELECTRICHIT_SOUND",&aStack_288);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x30),L"POISONHIT_SOUND",&aStack_287);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x38),L"SHIELDBLOCK",&aStack_286);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x40),L"BLOCK",&aStack_285);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x48),L"CRITICAL_SOUND",&aStack_284);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x50),L"ATTACK_SOUND",&aStack_283);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x58),L"IDLE_SOUND",&aStack_282)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x60),L"DEATH_SOUND",&aStack_281);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x68),L"ROAR_SOUND",&aStack_280)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x70),L"FLEE_SOUND",&aStack_27f)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x78),L"MISS_SOUND",&aStack_27e)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x80),L"FALL_SOUND",&aStack_27d)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x88),L"LAND_SOUND",&aStack_27c)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x90),L"TAKE_SOUND",&aStack_27b)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x98),L"SPAWN_SOUND",&aStack_27a);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa0),L"USE_SOUND",&aStack_279);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa8),L"EQUIP_SOUND",&aStack_278);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb0),L"OPENMENU_SOUND",&aStack_277);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb8),L"BUY_SOUND",&aStack_276);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xc0),L"ERROR_SOUND",&aStack_275);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 200),L"LEVELUP_SOUND",&aStack_274);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd0),L"EFFORT_SOUND",&aStack_273);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd8),L"SPENDPOINT_SOUND",&aStack_272);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe0),L"PORTALENTER_SOUND",&aStack_271);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe8),L"POERTALEXIT_SOUND",&aStack_270);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf0),L"SKILLASSIGN_SOUND",&aStack_26f);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf8),L"QUESTRECEIVED_SOUND",&aStack_26e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x100),L"QUESTCOMPLETED_SOUND",&aStack_26d)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x108),L"LOWMANA_SOUND",&aStack_26c);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x110),L"MISSILEREFLECT_SOUND",&aStack_26b)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x118),L"BADEFFECT_SOUND",&aStack_26a);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x120),L"GOODEFFECT_SOUND",&aStack_269);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x128),L"NPCDIALOG_SOUND",&aStack_268);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x130),L"NPCGREET",&aStack_267);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x138),L"NPCBYE",&aStack_266);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x140),L"NPCPURCHASE",&aStack_265);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x148),L"NPCSELL",&aStack_264);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x150),L"VOICEPETINVENTORYFULL_SOUND",
             &aStack_263);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x158),L"VOICEPETDEPARTED_SOUND",
             &aStack_262);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x160),L"VOICEPETRETURNED_SOUND",
             &aStack_261);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x168),L"VOICEPETFLED_SOUND",&aStack_260);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x170),L"VOICEPETLEVELUP_SOUND",&aStack_25f
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x178),L"VOICEINVENTORYFULL_SOUND",
             &aStack_25e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x180),L"VOICEINSUFFICIENTGOLD_SOUND",
             &aStack_25d);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x188),L"VOICEIMPOSSIBLE_SOUND",&aStack_25c
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 400),L"VOICECANTCAST_SOUND",&aStack_25b);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x198),L"VOICECANTCASTHERE_SOUND",
             &aStack_25a);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a0),L"VOICEHEALTHLOW_SOUND",&aStack_259)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a8),L"VOICEMANALOW_SOUND",&aStack_258);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b0),L"VOICETRAPSPRUNG_SOUND",&aStack_257
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b8),L"VOICEREFRESHED_SOUND",&aStack_256)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c0),L"VOICEPOWERFUL_SOUND",&aStack_255);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c8),L"VOICEHEALTHY_SOUND",&aStack_254);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d0),L"VOICEILL_SOUND",&aStack_253);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d8),L"VOICEPOISONED_SOUND",&aStack_252);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e0),L"VOICELEVELUP_SOUND",&aStack_251);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e8),L"VOICEFAMEUP_SOUND",&aStack_250);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f0),L"VOICESKILLUP_SOUND",&aStack_24f);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f8),L"VOICEFORTUNEGOOD_SOUND",
             &aStack_24e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x200),L"VOICEFORTUNEBAD_SOUND",&aStack_24d
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x208),L"VOICESPELLLEARNED_SOUND",
             &aStack_24c);
  ::KSOUNDBANK_STRINGS._528_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_1,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KALIGNMENT_STRINGS,L"NEUTRAL",&aStack_24b);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 8),L"GOOD",&aStack_24a);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x10),L"EVIL",&aStack_249);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x18),L"ALL",&aStack_248);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x20),L"BERSERK",&aStack_247);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x28),L"EVILBERSERK",&aStack_246);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x30),L"GOODBERSERK",&aStack_245);
  __cxa_atexit(::__tcf_2,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KAITYPE_STRINGS,L"NORMAL",&aStack_244);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 8),L"RANGEDDEFENDER",&aStack_243);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x10),L"DEFENDER",&aStack_242);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x18),L"RANGEDCASTER",&aStack_241);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x20),L"CIRCLER",&aStack_240);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x28),L"RESURRECTER",&aStack_23f);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x30),L"DUMMY",&aStack_23e);
  __cxa_atexit(::__tcf_3,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gDAMAGE_TYPES,L"Physical",&aStack_23d);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 8),L"Magical",&aStack_23c);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x10),L"Fire",&aStack_23b);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x18),L"Ice",&aStack_23a);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x20),L"Electric",&aStack_239);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x28),L"Poison",&aStack_238);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x30),L"All",&aStack_237);
  __cxa_atexit(::__tcf_4,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::gTARGET_TYPES,L"USER",&aStack_236);
  std::wstring::wstring((wstring_conflict *)&DAT_014cb968,L"ITEM",&aStack_235);
  __cxa_atexit(::__tcf_5,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSFXTypeName,L"STATIONARYTARGET",&aStack_234);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 8),L"STATIONARYOWNER",&aStack_233);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x10),L"STATIONARY",&aStack_232);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x18),L"STATIONARYPORTAL",&aStack_231)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x20),L"BEAM",&aStack_230);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x28),L"FOLLOWOWNER",&aStack_22f);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x30),L"FOLLOWTARGET",&aStack_22e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x38),L"PROJECTILELOCATION",&aStack_22d);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x40),L"PROJECTILECHARACTER",&aStack_22c);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x48),L"PROJECTILELOCATIONERRATIC",&aStack_22b);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x50),L"PROJECTILECHARACTERERRATIC",&aStack_22a);
  __cxa_atexit(::__tcf_6,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KCharacterNames,L"NA",&aStack_229);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 8),L"NA",&aStack_228);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x10),L"NA",&aStack_227);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x18),L"NA",&aStack_226);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x20),L"NA",&aStack_225);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x28),L"NA",&aStack_224);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x30),L"NA",&aStack_223);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x38),L"NA",&aStack_222);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x40),L"Bksp",&aStack_221);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x48),L"Tab",&aStack_220);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x50),L"NA",&aStack_21f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x58),L"NA",&aStack_21e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x60),L"Ctr",&aStack_21d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x68),L"Ret",&aStack_21c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x70),L"NA",&aStack_21b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x78),L"NA",&aStack_21a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x80),L"Shift",&aStack_219);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x88),L"Ctrl",&aStack_218);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x90),L"Alt",&aStack_217);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x98),L"Tab",&aStack_216);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa0),L"NA",&aStack_215);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa8),L"NA",&aStack_214);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb0),L"NA",&aStack_213);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb8),L"NA",&aStack_212);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xc0),L"NA",&aStack_211);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 200),L"NA",&aStack_210);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd0),L"NA",&aStack_20f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd8),L"NA",&aStack_20e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe0),L"NA",&aStack_20d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe8),L"NA",&aStack_20c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf0),L"NA",&aStack_20b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf8),L"NA",&aStack_20a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x100),L"space",&aStack_209);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x108),L"pgup",&aStack_208);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x110),L"pgdn",&aStack_207);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x118),L"end",&aStack_206);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x120),L"home",&aStack_205);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x128),L"left arrow",&aStack_204);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x130),L"up arrow",&aStack_203);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x138),L"right arrow",&aStack_202);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x140),L"down arrow",&aStack_201);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x148),L")",&aStack_200);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x150),L"*",&aStack_1ff);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x158),L"+",&aStack_1fe);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x160),L",",&aStack_1fd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x168),L"ins",&aStack_1fc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x170),L"del",&aStack_1fb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x178),L"/",&aStack_1fa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x180),L"0",&aStack_1f9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x188),L"1",&aStack_1f8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 400),L"2",&aStack_1f7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x198),L"3",&aStack_1f6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a0),L"4",&aStack_1f5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a8),L"5",&aStack_1f4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b0),L"6",&aStack_1f3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b8),L"7",&aStack_1f2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c0),L"8",&aStack_1f1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c8),L"9",&aStack_1f0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d0),L":",&aStack_1ef);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d8),L";",&aStack_1ee);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e0),L"<",&aStack_1ed);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e8),L"=",&aStack_1ec);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f0),L">",&aStack_1eb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f8),L"?",&aStack_1ea);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x200),L"@",&aStack_1e9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x208),L"a",&aStack_1e8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x210),L"b",&aStack_1e7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x218),L"c",&aStack_1e6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x220),L"d",&aStack_1e5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x228),L"e",&aStack_1e4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x230),L"NA",&aStack_1e3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x238),L"g",&aStack_1e2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x240),L"h",&aStack_1e1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x248),L"i",&aStack_1e0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x250),L"j",&aStack_1df);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 600),L"k",&aStack_1de);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x260),L"l",&aStack_1dd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x268),L"m",&aStack_1dc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x270),L"n",&aStack_1db);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x278),L"o",&aStack_1da);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x280),L"p",&aStack_1d9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x288),L"NA",&aStack_1d8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x290),L"r",&aStack_1d7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x298),L"s",&aStack_1d6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a0),L"t",&aStack_1d5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a8),L"u",&aStack_1d4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b0),L"v",&aStack_1d3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b8),L"w",&aStack_1d2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c0),L"x",&aStack_1d1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c8),L"y",&aStack_1d0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d0),L"z",&aStack_1cf);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d8),L"[",&aStack_1ce);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e0),L"\\",&aStack_1cd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e8),L"]",&aStack_1cc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f0),L"^",&aStack_1cb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f8),L"_",&aStack_1ca);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x300),L"NUM 0",&aStack_1c9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x308),L"NUM 1",&aStack_1c8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x310),L"NUM 2",&aStack_1c7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x318),L"NUM 3",&aStack_1c6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 800),L"NUM 4",&aStack_1c5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x328),L"NUM 5",&aStack_1c4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x330),L"NUM 6",&aStack_1c3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x338),L"NUM 7",&aStack_1c2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x340),L"NUM 8",&aStack_1c1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x348),L"NUM 9",&aStack_1c0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x350),L"*",&aStack_1bf);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x358),L"+",&aStack_1be);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x360),L"NA",&aStack_1bd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x368),L"-",&aStack_1bc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x370),L"NA",&aStack_1bb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x378),L"F1",&aStack_1ba);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x380),L"F2",&aStack_1b9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x388),L"F3",&aStack_1b8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x390),L"F4",&aStack_1b7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x398),L"F5",&aStack_1b6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a0),L"F6",&aStack_1b5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a8),L"F7",&aStack_1b4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b0),L"F8",&aStack_1b3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b8),L"F9",&aStack_1b2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c0),L"F10",&aStack_1b1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c8),L"F11",&aStack_1b0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d0),L"F12",&aStack_1af);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d8),L"{",&aStack_1ae);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3e0),L"|",&aStack_1ad);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 1000),L"}",&aStack_1ac);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f0),L"~",&aStack_1ab);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f8),L";",&aStack_1aa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x400),L"=",&aStack_1a9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x408),L".",&aStack_1a8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x410),L"-",&aStack_1a7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x418),L",",&aStack_1a6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x420),L"/",&aStack_1a5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x428),L"`",&aStack_1a4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x430),L"[",&aStack_1a3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x438),L"\\",&aStack_1a2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x440),L"]",&aStack_1a1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x448),L"\'",&aStack_1a0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x450),L"NA",&aStack_19f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x458),L"NA",&aStack_19e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x460),L"NA",&aStack_19d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x468),L"NA",&aStack_19c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x470),L"NA",&aStack_19b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x478),L"NA",&aStack_19a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x480),L"NA",&aStack_199);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x488),L"NA",&aStack_198);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x490),L"NA",&aStack_197);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x498),L"NA",&aStack_196);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a0),L"NA",&aStack_195);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a8),L"NA",&aStack_194);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b0),L"NA",&aStack_193);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b8),L"NA",&aStack_192);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c0),L"NA",&aStack_191);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c8),L"NA",&aStack_190);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d0),L"NA",&aStack_18f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d8),L"NA",&aStack_18e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e0),L"NA",&aStack_18d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e8),L"NA",&aStack_18c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f0),L"NA",&aStack_18b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f8),L"NA",&aStack_18a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x500),L"NA",&aStack_189);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x508),L"NA",&aStack_188);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x510),L"NA",&aStack_187);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x518),L"NA",&aStack_186);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x520),L"NA",&aStack_185);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x528),L"NA",&aStack_184);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x530),L"NA",&aStack_183);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x538),L"NA",&aStack_182);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x540),L"NA",&aStack_181);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x548),L"NA",&aStack_180);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x550),L"NA",&aStack_17f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x558),L"NA",&aStack_17e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x560),L"NA",&aStack_17d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x568),L"NA",&aStack_17c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x570),L"NA",&aStack_17b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x578),L"NA",&aStack_17a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x580),L"NA",&aStack_179);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x588),L"NA",&aStack_178);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x590),L"NA",&aStack_177);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x598),L"NA",&aStack_176);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a0),L"NA",&aStack_175);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a8),L"NA",&aStack_174);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b0),L"NA",&aStack_173);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b8),L"NA",&aStack_172);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c0),L"NA",&aStack_171);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c8),L"NA",&aStack_170);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d0),L";",&aStack_16f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d8),L"=",&aStack_16e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e0),L",",&aStack_16d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e8),L"-",&aStack_16c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f0),L".",&aStack_16b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f8),L"/",&aStack_16a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x600),L"`",&aStack_169);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x608),L"NA",&aStack_168);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x610),L"NA",&aStack_167);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x618),L"NA",&aStack_166);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x620),L"NA",&aStack_165);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x628),L"NA",&aStack_164);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x630),L"NA",&aStack_163);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x638),L"NA",&aStack_162);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x640),L"NA",&aStack_161);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x648),L"NA",&aStack_160);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x650),L"NA",&aStack_15f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x658),L"NA",&aStack_15e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x660),L"NA",&aStack_15d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x668),L"NA",&aStack_15c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x670),L"NA",&aStack_15b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x678),L"NA",&aStack_15a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x680),L"NA",&aStack_159);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x688),L"NA",&aStack_158);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x690),L"NA",&aStack_157);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x698),L"NA",&aStack_156);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a0),L"NA",&aStack_155);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a8),L"NA",&aStack_154);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b0),L"NA",&aStack_153);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b8),L"NA",&aStack_152);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c0),L"NA",&aStack_151);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c8),L"NA",&aStack_150);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d0),L"NA",&aStack_14f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d8),L"[",&aStack_14e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e0),L"\\",&aStack_14d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e8),L"]",&aStack_14c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f0),L"\'",&aStack_14b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f8),L"NA",&aStack_14a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x700),L"NA",&aStack_149);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x708),L"NA",&aStack_148);
  __cxa_atexit(::__tcf_7,0,&__dso_handle);
  ParticleUniverse::HALFSCALE._4_4_ = DAT_0142463c * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._0_4_ = Ogre::Vector3::UNIT_SCALE * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._8_4_ = DAT_00fa4810 * DAT_01424640;
  std::string::string((string *)&ParticleUniverse::ALIAS,"1",&aStack_147);
  __cxa_atexit(std::string::~string,&ParticleUniverse::ALIAS,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::SYSTEM,"2",&aStack_146);
  __cxa_atexit(std::string::~string,&ParticleUniverse::SYSTEM,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::TECHNIQUE,"3",&aStack_145);
  __cxa_atexit(std::string::~string,&ParticleUniverse::TECHNIQUE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::RENDERER,"4",&aStack_144);
  __cxa_atexit(std::string::~string,&ParticleUniverse::RENDERER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EMITTER,"5",&aStack_143);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EMITTER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::AFFECTOR,"6",&aStack_142);
  __cxa_atexit(std::string::~string,&ParticleUniverse::AFFECTOR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::OBSERVER,"7",&aStack_141);
  __cxa_atexit(std::string::~string,&ParticleUniverse::OBSERVER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::HANDLER,"8",&aStack_140);
  __cxa_atexit(std::string::~string,&ParticleUniverse::HANDLER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::BEHAVIOUR,"9",&aStack_13f);
  __cxa_atexit(std::string::~string,&ParticleUniverse::BEHAVIOUR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EXTERN,"10",&aStack_13e);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EXTERN,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DYNAMIC_ATTRIBUTE,"11",&aStack_13d);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DYNAMIC_ATTRIBUTE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DEPENDENCY,"12",&aStack_13c);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DEPENDENCY,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES,"tag_righthand",&aStack_13b);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 8),"tag_lefthand",&aStack_13a);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x10),"",&aStack_139);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x18),"Bip01 Head",&aStack_138);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x20),"",&aStack_137);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x28),"Bip01 L Clavicle",&aStack_136);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x30),"",&aStack_135);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x38),"",&aStack_134);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x40),"",&aStack_133);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x48),"",&aStack_132);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x50),"",&aStack_131);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x58),"tag_leftarm",&aStack_130);
  __cxa_atexit(::__tcf_8,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES_SECONDARY,"",&aStack_12f);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 8),"",&aStack_12e);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x10),"",&aStack_12d);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x18),"",&aStack_12c);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x20),"",&aStack_12b);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x28),"Bip01 R Clavicle",
                      &aStack_12a);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x30),"",&aStack_129);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x38),"",&aStack_128);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x40),"",&aStack_127);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x48),"",&aStack_126);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x50),"",&aStack_125);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x58),"",&aStack_124);
  __cxa_atexit(::__tcf_9,0,&__dso_handle);
  std::string::string((string *)&::KEquipmentIconName,"EquipLeftHand",&aStack_123);
  std::string::string((string *)&DAT_014cc228,"EquipRightHand",&aStack_122);
  std::string::string((string *)&DAT_014cc230,"EquipGloves",&aStack_121);
  std::string::string((string *)&DAT_014cc238,"EquipHelm",&aStack_120);
  std::string::string((string *)&DAT_014cc240,"EquipChest",&aStack_11f);
  std::string::string((string *)&DAT_014cc248,"EquipShoulder",&aStack_11e);
  std::string::string((string *)&DAT_014cc250,"EquipBoots",&aStack_11d);
  std::string::string((string *)&DAT_014cc258,"EquipBelt",&aStack_11c);
  std::string::string((string *)&DAT_014cc260,"EquipRing1",&aStack_11b);
  std::string::string((string *)&DAT_014cc268,"EquipRing2",&aStack_11a);
  std::string::string((string *)&DAT_014cc270,"EquipAmulet",&aStack_119);
  std::string::string((string *)&DAT_014cc278,"",&aStack_118);
  __cxa_atexit(::__tcf_10,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_TYPE_NAMES,L"",&aStack_117);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 8),L"FIND",&aStack_116);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x10),L"KILL NUM",&aStack_115);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x18),L"KILL BOSS",&aStack_114);
  __cxa_atexit(::__tcf_11,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_DIALOG_TYPE_NAMES,L"ERROR",&aStack_113);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 8),L"INTRO",&aStack_112);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x10),L"RETURN",&aStack_111);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x18),L"COMPLETE",&aStack_110);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x20),L"PASSIVE",&aStack_10f);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x28),L"DETAILS",&aStack_10e);
  __cxa_atexit(::__tcf_12,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEffect_Activation_Names,L"PASSIVE",&aStack_10d);
  std::wstring::wstring((wstring_conflict *)(::gEffect_Activation_Names + 8),L"DYNAMIC",&aStack_10c)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gEffect_Activation_Names + 0x10),L"TRANSFER",&aStack_10b);
  __cxa_atexit(::__tcf_13,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEFFECT_STAT_MODIFIER_NAMES,L"MELEE",&aStack_10a);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 8),L"RANGED",&aStack_109);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x10),L"DEFENSE",&aStack_108);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x18),L"MAGIC",&aStack_107);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x20),L"LEVEL",&aStack_106);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x28),L"OWNERLEVEL",&aStack_105);
  __cxa_atexit(::__tcf_14,0,&__dso_handle);
  std::string::string((string *)::gEFFECT_STAT_MODIFIER_ICON_NAMES,"iconmelee",&aStack_104);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 8),"iconranged",&aStack_103);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x10),"icondefense",
                      &aStack_102);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x18),"iconmagic",&aStack_101)
  ;
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x20),"iconmagic",&aStack_100)
  ;
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x28),"iconmagic",&aStack_ff);
  __cxa_atexit(::__tcf_15,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KContextTipNames,L"TIP_INVENTORY",&aStack_fe);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 8),L"TIP_UNIDENTIFIED",&aStack_fd)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x10),L"TIP_INVENTORYFULL",&aStack_fc);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x18),L"TIP_HEALTHLOW",&aStack_fb)
  ;
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x20),L"TIP_MANALOW",&aStack_fa);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x28),L"TIP_MERCHANT",&aStack_f9);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x30),L"TIP_LEVELUP",&aStack_f8);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x38),L"TIP_STATS",&aStack_f7);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x40),L"TIP_SPELL",&aStack_f6);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x48),L"TIP_WELCOME",&aStack_f5);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x50),L"TIP_SOCKETABLE",&aStack_f4);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x58),L"TIP_PETFLEE",&aStack_f3);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x60),L"TIP_GAMBLE",&aStack_f2);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x68),L"TIP_ENCHANT",&aStack_f1);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x70),L"TIP_TRANSMUTE",&aStack_f0)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x78),L"TIP_PETINVENTORY",&aStack_ef);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x80),L"TIP_PETINVENTORYFULL",&aStack_ee);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x88),L"TIP_STASH",&aStack_ed);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x90),L"TIP_FISHING",&aStack_ec);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x98),L"TIP_SPELLFIND",&aStack_eb)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xa0),L"TIP_QUESTCOMPLETE",&aStack_ea);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xa8),L"TIP_SHAREDSTASH",&aStack_e9);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xb0),L"TIP_HOWTOATTACK",&aStack_e8);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xb8),L"TIP_TEMP5",&aStack_e7);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xc0),L"TIP_TEMP6",&aStack_e6);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 200),L"TIP_TEMP7",&aStack_e5);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xd0),L"TIP_TEMP8",&aStack_e4);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xd8),L"TIP_TEMP9",&aStack_e3);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xe0),L"TIP_TEMP10",&aStack_e2);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xe8),L"TIP_TEMP11",&aStack_e1);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xf0),L"TIP_TEMP12",&aStack_e0);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xf8),L"TIP_TEMP13",&aStack_df);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x100),L"TIP_TEMP14",&aStack_de);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x108),L"TIP_TEMP15",&aStack_dd);
  __cxa_atexit(::__tcf_16,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames,L"CHEST",&aStack_dc);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 8),L"GLOVES",&aStack_db);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x10),L"BOOTS",&aStack_da);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x18),L"HELMET",&aStack_d9);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x20),L"SHOULDERS",&aStack_d8);
  __cxa_atexit(::__tcf_17,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames2,L"",&aStack_d7);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 8),L"",&aStack_d6);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x10),L"",&aStack_d5);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x18),L"FACE",&aStack_d4);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x20),L"",&aStack_d3);
  __cxa_atexit(::__tcf_18,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_AIFLAG_TYPE_NAMES,L"AWARE",&aStack_d2);
  std::wstring::wstring((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 8),L"BERSERK",&aStack_d1);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x10),L"CANNOT INTERRUPT",&aStack_d0);
  std::wstring::wstring((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x18),L"FRIGHTEN",&aStack_cf);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x20),L"NO LINE OF SIGHT",&aStack_ce);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x28),L"NEVER CHANGE TARGET",&aStack_cd);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x30),L"CANNOT TARGET",&aStack_cc);
  __cxa_atexit(::__tcf_19,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_AISTAT_TYPE_NAMES,L"NONE",&aStack_cb);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 8),L"HP",&aStack_ca);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x10),L"MANA",&aStack_c9);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x18),L"HP PCT",&aStack_c8);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x20),L"MANA PCT",&aStack_c7);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x28),L"ACTIVE UNITS",&aStack_c6);
  __cxa_atexit(::__tcf_20,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::g_AISTAT_LOGIC_NAMES,L"BELOW",&aStack_c5);
  std::wstring::wstring((wstring_conflict *)&DAT_014cc598,L"ABOVE",&aStack_c4);
  __cxa_atexit(::__tcf_21,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_AISTAT_TARGET_NAMES,L"SELF",&aStack_c3);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 8),L"FORMATION",&aStack_c2);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 0x10),L"AREA",&aStack_c1);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 0x18),L"AREAUNITTYPES",&aStack_c0);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 0x20),L"AREAFORMATION",&aStack_bf);
  __cxa_atexit(::__tcf_22,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)OGRE_UTILITIES::gPRIMITIVE_NAMES,L"SPHERE",&aStack_be);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 8),L"BOX",&aStack_bd);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x10),L"PLANE",&aStack_bc);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x18),L"CYLINDER",&aStack_bb);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x20),L"CONE",&aStack_ba);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x28),L"ARROW",&aStack_b9);
  __cxa_atexit(::__tcf_23,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gKEYFRAME_TYPES,L"HIT",&aStack_b8);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 8),L"BLENDIN",&aStack_b7);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x10),L"BLENDOUT",&aStack_b6);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x18),L"PLAYSOUND",&aStack_b5);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x20),L"SPAWNPARTICLE",&aStack_b4);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x28),L"SPAWNPARTICLE_STOP_ON_DEATH",
             &aStack_b3);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x30),L"FOOTSTEP",&aStack_b2);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x38),L"SHOWWEAPONTRAIL",&aStack_b1);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x40),L"HIDEWEAPONTRAIL",&aStack_b0);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x48),L"ATTACKSOUND",&aStack_af);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x50),L"ENABLECOLLISION",&aStack_ae);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x58),L"DISABLECOLLISION",&aStack_ad);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x60),L"REMOVEPARTICLES",&aStack_ac);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x68),L"REMOVEANIMATIONPARTICLES",&aStack_ab);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x70),L"CAMERASHAKE",&aStack_aa);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x78),L"ATTACKEND",&aStack_a9);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x80),L"UNTARGETABLE",&aStack_a8);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x88),L"TARGETABLE",&aStack_a7);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x90),L"DAMPVELOCITY",&aStack_a6);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x98),L"UNDAMPVELOCITY",&aStack_a5)
  ;
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xa0),L"SHOWWEAPONS",&aStack_a4);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xa8),L"HIDEWEAPONS",&aStack_a3);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xb0),L"HIDEMESH",&aStack_a2);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xb8),L"SHOWMESH",&aStack_a1);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xc0),L"FADEOUTMESH",&aStack_a0);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 200),L"FADEINMESH",&aStack_9f);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0xd0),L"CAMERASHAKE_NO_FALLOFF",&aStack_9e);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0xd8),L"PLAYSOUND_NO_FALLOFF",&aStack_9d);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xe0),L"HITTWO",&aStack_9c);
  __cxa_atexit(::__tcf_24,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEDITOR_EVENT_NAMES,L"STOP",&aStack_9b);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 8),L"PLAY",&aStack_9a);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x10),L"RELOAD TILES",&aStack_99);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x18),L"TOGGLE LIGHTING",&aStack_98);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x20),L"SELECT COLLIDABLE",&aStack_97);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x28),L"PAUSE PARTICLES",&aStack_96);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x30),L"UNPAUSE PARTICLES",&aStack_95);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x38),L"COLLISION ALL",&aStack_94);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x40),L"COLLISION MODELS",&aStack_93);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x48),L"COLLISION PREFABS",&aStack_92);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x50),L"COLLISION ROOMPIECES",&aStack_91);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x58),L"COLLISION ROOMPROPS",&aStack_90);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x60),L"RELOAD GRAPHS",&aStack_8f);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x68),L"TOGGLE PLAYER LIGHT",&aStack_8e);
  __cxa_atexit(::__tcf_25,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEDITOR_FLAG_NAMES,L"LOGIC ENABLED",&aStack_8d);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 8),L"INGAME MODE",&aStack_8c);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x10),L"SHOW STATS",&aStack_8b);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x18),L"EDIT POSITION",&aStack_8a);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x20),L"EDIT SCALE",&aStack_89);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x28),L"EDIT ORIENTATION",&aStack_88);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x30),L"EDIT NONE",&aStack_87);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x38),L"SHOW HELPERS",&aStack_86);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x40),L"SHOW GRID",&aStack_85);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x48),L"SHOW WORKING PLANE",&aStack_84);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x50),L"SNAP TO GRID",&aStack_83);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x58),L"SUSPEND EDITOR",&aStack_82);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x60),L"LIGHTING VISIBLE",&aStack_81);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x68),L"RECALCULATE LIGHTING",&aStack_80);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x70),L"SHOW EDGES",&aStack_7f);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x78),L"UPDATE PARTICLES CIRCLE",&aStack_7e
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x80),L"SHOW LOGIC OUTPUT",&aStack_7d);
  __cxa_atexit(::__tcf_26,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::gEDITOR_UPDATE_MASKS,L"OBJECT SELECTION CHANGED",&aStack_7c);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 8),L"OBJECT DATA CHANGED",&aStack_7b);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 0x10),L"OBJECTS CREATED",&aStack_7a);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 0x18),L"REFRESH TREE VIEW",&aStack_79);
  __cxa_atexit(::__tcf_27,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::m_gFileVersionExtension,L".svt",&aStack_78);
  __cxa_atexit(std::wstring::~wstring,&::m_gFileVersionExtension,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_EVENT_TYPE_NAMES,L"EVENT_START",&aStack_77);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 8),L"EVENT_END",&aStack_76)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x10),L"EVENT_TRIGGER",&aStack_75);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x18),L"EVENT_TRIGGER_TWO",&aStack_74)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x20),L"EVENT_UNITHIT",&aStack_73);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x28),L"EVENT_UNITDIE",&aStack_72);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x30),L"EVENT_MISSILEHIT",&aStack_71);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x38),L"EVENT_MISSILEDIE",&aStack_70);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x40),L"EVENT_DIEBYEFFECT",&aStack_6f)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x48),L"EVENT_CASTERDIE",&aStack_6e);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x50),L"EVENT_UNIT_CREATE",&aStack_6d)
  ;
  __cxa_atexit(::__tcf_28,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_TARGET_TYPE_NAMES,L"NONE",&aStack_6c);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 8),L"POSITION",&aStack_6b)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x10),L"TARGET",&aStack_6a);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x18),L"SELF",&aStack_69);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x20),L"EVERYBODY",&aStack_68);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x28),L"POSITIONRANDOM",&aStack_67);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x30),L"POSITIONFLEE",&aStack_66);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x38),L"ITEM",&aStack_65);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x40),L"UNIDENTIFIEDITEM",&aStack_64)
  ;
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x48),L"PETS",&aStack_63);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x50),L"SELFANDPETS",&aStack_62);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x58),L"TARGET_POS",&aStack_61);
  __cxa_atexit(::__tcf_29,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_ACTIVATION_TYPE_NAMES,L"ANY",&aStack_60);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 8),L"PROC",&aStack_5f)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 0x10),L"WEAPON",&aStack_5e);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 0x18),L"NORMAL",&aStack_5d);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 0x20),L"PASSIVE",&aStack_5c);
  __cxa_atexit(::__tcf_30,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_TYPE_NAMES,L"SKILL",&aStack_5b);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TYPE_NAMES + 8),L"OFFENSIVE",&aStack_5a);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TYPE_NAMES + 0x10),L"DEFENSIVE",&aStack_59);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TYPE_NAMES + 0x18),L"CHARM",&aStack_58);
  ::gSKILL_TYPE_NAMES._32_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_31,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_TYPE_DISPLAY_NAMES,L"Class Skill",&aStack_57);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TYPE_DISPLAY_NAMES + 8),L"Offensive Spell",&aStack_56);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TYPE_DISPLAY_NAMES + 0x10),L"Defensive Spell",&aStack_55)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TYPE_DISPLAY_NAMES + 0x18),L"Charm Spell",&aStack_54);
  ::gSKILL_TYPE_DISPLAY_NAMES._32_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_32,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_BONE_ATTACHMENT_NAMES,L"",&aStack_53);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 8),L"CENTER",&aStack_52);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x10),L"HEAD",&aStack_51);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x18),L"RIGHTHAND",&aStack_50);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x20),L"LEFTHAND",&aStack_4f);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x28),L"RIGHTSHOULDER",&aStack_4e
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x30),L"LEFTSHOULDER",&aStack_4d)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x38),L"POSITION",&aStack_4c);
  __cxa_atexit(::__tcf_33,0,&__dso_handle);
  ::g_strStatDefines._0_4_ = 1;
  ::g_strStatDefines._4_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 8),"STAT_DEATHS",&aStack_4b);
  ::g_strStatDefines[0x10] = 0;
  ::g_strStatDefines._24_4_ = 2;
  ::g_strStatDefines._28_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x20),"STAT_BREAKABLES",&aStack_4a);
  ::g_strStatDefines[0x28] = 0;
  ::g_strStatDefines._48_4_ = 3;
  ::g_strStatDefines._52_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x38),"STAT_CRITICAL_STRIKES",&aStack_49);
  ::g_strStatDefines[0x40] = 0;
  ::g_strStatDefines._72_4_ = 4;
  ::g_strStatDefines._76_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x50),"STAT_MAX_DMG_DONE",&aStack_48);
  ::g_strStatDefines[0x58] = 0;
  ::g_strStatDefines._96_4_ = 5;
  ::g_strStatDefines._100_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x68),"STAT_MONSTERS_KILLED",&aStack_47);
  ::g_strStatDefines[0x70] = 0;
  ::g_strStatDefines._120_4_ = 6;
  ::g_strStatDefines._124_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x80),"STAT_DEEPEST_FLOOR",&aStack_46);
  ::g_strStatDefines[0x88] = 0;
  ::g_strStatDefines._144_4_ = 7;
  ::g_strStatDefines._148_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x98),"STAT_FISH_CAUGHT",&aStack_45);
  ::g_strStatDefines[0xa0] = 0;
  ::g_strStatDefines._168_4_ = 8;
  ::g_strStatDefines._172_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0xb0),"STAT_ENCHANTER_FAILS",&aStack_44);
  ::g_strStatDefines[0xb8] = 0;
  ::g_strStatDefines._192_4_ = 9;
  ::g_strStatDefines._196_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 200),"STAT_RECIPES_MADE",&aStack_43);
  ::g_strStatDefines[0xd0] = 0;
  ::g_strStatDefines._216_4_ = 10;
  ::g_strStatDefines._220_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0xe0),"STAT_GAMBLE_COUNT",&aStack_42);
  ::g_strStatDefines[0xe8] = 0;
  ::g_strStatDefines._240_4_ = 0xb;
  ::g_strStatDefines._244_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0xf8),"STAT_QUESTS_COMPLETED",&aStack_41);
  ::g_strStatDefines[0x100] = 0;
  ::g_strStatDefines._264_4_ = 0xc;
  ::g_strStatDefines._268_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x110),"STAT_RETIRED_COUNT",&aStack_40);
  ::g_strStatDefines[0x118] = 0;
  ::g_strStatDefines._288_4_ = 0xd;
  ::g_strStatDefines._292_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x128),"STAT_RETIRED_LVLS_TOTAL",&aStack_3f);
  ::g_strStatDefines[0x130] = 0;
  ::g_strStatDefines._312_4_ = 0xe;
  ::g_strStatDefines._316_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x140),"STAT_GOLD_COLLECTED",&aStack_3e);
  ::g_strStatDefines[0x148] = 0;
  ::g_strStatDefines._336_4_ = 0xf;
  ::g_strStatDefines._340_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x158),"STAT_LEVERS_PULLED",&aStack_3d);
  ::g_strStatDefines[0x160] = 0;
  ::g_strStatDefines._360_4_ = 0x10;
  ::g_strStatDefines._364_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x170),"STAT_TOTAL_STEPS",&aStack_3c);
  ::g_strStatDefines[0x178] = 0;
  ::g_strStatDefines._384_4_ = 0x11;
  ::g_strStatDefines._388_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x188),"STAT_TOTAL_POTIONS_USED",&aStack_3b);
  ::g_strStatDefines[400] = 0;
  ::g_strStatDefines._408_4_ = 0x12;
  ::g_strStatDefines._412_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x1a0),"STAT_TOTAL_ITEMS_SOLD",&aStack_3a);
  ::g_strStatDefines[0x1a8] = 0;
  ::g_strStatDefines._432_4_ = 0x13;
  ::g_strStatDefines._436_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x1b8),"STAT_DEATHS_HARDCORE",&aStack_39);
  ::g_strStatDefines[0x1c0] = 0;
  ::g_strStatDefines._456_4_ = 0x14;
  ::g_strStatDefines._460_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x1d0),"STAT_TROLL_CHMPS",&aStack_38);
  ::g_strStatDefines[0x1d8] = 0;
  ::g_strStatDefines._480_4_ = 0x15;
  ::g_strStatDefines._484_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x1e8),"STAT_POTIONS_PET",&aStack_37);
  ::g_strStatDefines[0x1f0] = 0;
  ::g_strStatDefines._504_4_ = 0x16;
  ::g_strStatDefines._508_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x200),"STAT_WIN_VANQ",&aStack_36);
  ::g_strStatDefines[0x208] = 0;
  ::g_strStatDefines._528_4_ = 0x17;
  ::g_strStatDefines._532_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x218),"STAT_WIN_ALCH",&aStack_35);
  ::g_strStatDefines[0x220] = 0;
  ::g_strStatDefines._552_4_ = 0x18;
  ::g_strStatDefines._556_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x230),"STAT_WIN_DESTROYER",&aStack_34);
  ::g_strStatDefines[0x238] = 0;
  ::g_strStatDefines._576_4_ = 0x19;
  ::g_strStatDefines._580_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x248),"STAT_EXPLODE_ENEMY",&aStack_33);
  ::g_strStatDefines[0x250] = 0;
  ::g_strStatDefines._600_4_ = 0x1a;
  ::g_strStatDefines._604_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x260),"STAT_QUESTS_COMPLETED_HATCH",
                      &aStack_32);
  ::g_strStatDefines[0x268] = 0;
  ::g_strStatDefines._624_4_ = 0x1b;
  ::g_strStatDefines._628_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x278),"STAT_QUESTS_COMPLETED_GARR",&aStack_31
                     );
  ::g_strStatDefines[0x280] = 0;
  ::g_strStatDefines._648_4_ = 0x1c;
  ::g_strStatDefines._652_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x290),"STAT_HORSE_TALK",&aStack_30);
  ::g_strStatDefines[0x298] = 0;
  ::g_strStatDefines._672_4_ = 0xffffffff;
  ::g_strStatDefines._676_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x2a8),"PLAYER_DEATHS",&aStack_2f);
  ::g_strStatDefines[0x2b0] = 0;
  ::g_strStatDefines._696_4_ = 0xffffffff;
  ::g_strStatDefines._700_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x2c0),"PLAYER_GOLD",&aStack_2e);
  ::g_strStatDefines[0x2c8] = 0;
  ::g_strStatDefines._720_4_ = 0xffffffff;
  ::g_strStatDefines._724_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x2d8),"NONE",&aStack_2d);
  ::g_strStatDefines[0x2e0] = 0;
  __cxa_atexit(::__tcf_34,0,&__dso_handle);
  std::string::string((string *)g_strAchievementsCodeName,"TORCHLIGHT_ACHIEVEMENT_FIRSTLEVEL",
                      &aStack_2c);
  std::string::string((string *)(g_strAchievementsCodeName + 8),"BEAST_OF_BURDEN",&aStack_2b);
  std::string::string((string *)(g_strAchievementsCodeName + 0x10),"PET_SEND_TO_TOWN",&aStack_2a);
  std::string::string((string *)(g_strAchievementsCodeName + 0x18),"PET_FEED_FISH_ANY",&aStack_29);
  std::string::string((string *)(g_strAchievementsCodeName + 0x20),"PET_FEED_FISH_PERMANENT",
                      &aStack_28);
  std::string::string((string *)(g_strAchievementsCodeName + 0x28),"GAMBLE_UNIQUE",&aStack_27);
  std::string::string((string *)(g_strAchievementsCodeName + 0x30),"MAX_FAME",&aStack_26);
  std::string::string((string *)(g_strAchievementsCodeName + 0x38),"KILL_BRINK",&aStack_25);
  std::string::string((string *)(g_strAchievementsCodeName + 0x40),"KILL_LICH",&aStack_24);
  std::string::string((string *)(g_strAchievementsCodeName + 0x48),"KILL_ROOT_GOLEM",&aStack_23);
  std::string::string((string *)(g_strAchievementsCodeName + 0x50),"KILL_EMBER_COLOSSUS",&aStack_22)
  ;
  std::string::string((string *)(g_strAchievementsCodeName + 0x58),"KILL_TROLL_BOSS",&aStack_21);
  std::string::string((string *)(g_strAchievementsCodeName + 0x60),"KILL_MEDEA",&aStack_20);
  std::string::string((string *)(g_strAchievementsCodeName + 0x68),"KILL_ALRIC",&aStack_1f);
  std::string::string((string *)(g_strAchievementsCodeName + 0x70),"BEASTSLAYERI",&aStack_1e);
  std::string::string((string *)(g_strAchievementsCodeName + 0x78),"BEASTSLAYERII",&aStack_1d);
  std::string::string((string *)(g_strAchievementsCodeName + 0x80),"BEASTSLAYERIII",&aStack_1c);
  std::string::string((string *)(g_strAchievementsCodeName + 0x88),"HARDCORE_VICTOR",&aStack_1b);
  std::string::string((string *)(g_strAchievementsCodeName + 0x90),"HARDCORE_HERO",&aStack_1a);
  std::string::string((string *)(g_strAchievementsCodeName + 0x98),"HARDCORE_CHAMPION",&aStack_19);
  std::string::string((string *)(g_strAchievementsCodeName + 0xa0),"HARDCORE_GOD",&aStack_18);
  std::string::string((string *)(g_strAchievementsCodeName + 0xa8),"SPEEDY",&aStack_17);
  std::string::string((string *)(g_strAchievementsCodeName + 0xb0),"SPEED_KING",&aStack_16);
  std::string::string((string *)(g_strAchievementsCodeName + 0xb8),"HAT_TRICK",&aStack_15);
  std::string::string((string *)(g_strAchievementsCodeName + 0xc0),"PLAYER_LEVEL_65",&aStack_14);
  std::string::string((string *)(g_strAchievementsCodeName + 200),"PLAYER_LEVEL_100",&aStack_13);
  std::string::string((string *)(g_strAchievementsCodeName + 0xd0),"MODS_1",&aStack_12);
  std::string::string((string *)(g_strAchievementsCodeName + 0xd8),"MODS_5",&aStack_11);
  std::string::string((string *)(g_strAchievementsCodeName + 0xe0),"MODS_10",&aStack_10);
  std::string::string((string *)(g_strAchievementsCodeName + 0xe8),"ENCHANTER_FAILURE_FIRST",
                      &aStack_f);
  std::string::string((string *)(g_strAchievementsCodeName + 0xf0),"PET_MIMIC",&aStack_e);
  std::string::string((string *)(g_strAchievementsCodeName + 0xf8),"PET_TRAINER",&aStack_d);
  std::string::string((string *)(g_strAchievementsCodeName + 0x100),"ENCHANTER_SUCCESS_5",&aStack_c)
  ;
  std::string::string((string *)(g_strAchievementsCodeName + 0x108),"ENCHANTER_SUCCESS_10",&aStack_b
                     );
  std::string::string((string *)(g_strAchievementsCodeName + 0x110),"PERFECT_VICTORY",&aStack_a);
  std::string::string((string *)(g_strAchievementsCodeName + 0x118),"PLAYER_GOLD_IN_POCKET",
                      &aStack_9);
  __cxa_atexit(::__tcf_35,0,&__dso_handle);
  return;
}

/* address=00b91250
   symbol=CPetMenu::~CPetMenu */

/* CPetMenu::~CPetMenu() */

void __thiscall CPetMenu::~CPetMenu(CPetMenu *this)

{
  String *this_00;

  *(undefined ***)this = &PTR__CPetMenu_00ff06f0;
  *(undefined ***)(this + 0x10) = &PTR__CPetMenu_00ff07a0;
                    /* try { // try from 00b9126e to 00b912e5 has its CatchHandler @ 00b913c4 */
  setOwner(this,(CCharacter *)0x0);
  if (*(long *)(this + 0x9170) != 0) {
    (**(code **)(**(long **)(this + 0x9168) + 0x1c0))();
  }
  *(undefined8 *)(this + 0x9170) = 0;
  if (*(long **)(this + 0x91a0) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x91a0) + 8))();
    *(undefined8 *)(this + 0x91a0) = 0;
  }
  if (*(long **)(this + 0x91b8) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x91b8) + 8))();
    *(undefined8 *)(this + 0x91b8) = 0;
  }
  if (*(long **)(this + 0x91f0) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x91f0) + 8))();
    *(undefined8 *)(this + 0x91f0) = 0;
  }
                    /* try { // try from 00b912fb to 00b9131a has its CatchHandler @ 00b91443 */
  CEGUI::String::~String((String *)(this + 0x9570));
  CEGUI::String::~String((String *)(this + 0x94c0));
  CEGUI::String::~String((String *)(this + 0x9410));
                    /* try { // try from 00b91325 to 00b91344 has its CatchHandler @ 00b9141c */
  CEGUI::String::~String((String *)(this + 0x9360));
  CEGUI::String::~String((String *)(this + 0x92b0));
  CEGUI::String::~String((String *)(this + 0x9200));
  this_00 = (String *)(this + 0x9108);
  do {
    this_00 = this_00 + -0xb0;
                    /* try { // try from 00b91362 to 00b91366 has its CatchHandler @ 00b9146a */
    CEGUI::String::~String(this_00);
  } while (this_00 != (String *)(this + 0x58a8));
  do {
    this_00 = this_00 + -0xb0;
                    /* try { // try from 00b91382 to 00b91386 has its CatchHandler @ 00b913eb */
    CEGUI::String::~String(this_00);
  } while (this_00 != (String *)(this + 0x2048));
  if (*(void **)(this + 0x70) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x70));
    *(undefined8 *)(this + 0x70) = 0;
  }
  *(undefined ***)(this + 0x10) = &PTR__iInventoryListener_00fce450;
  *(undefined ***)this = &PTR__CSubMenu_00fe64b0;
  CRunicCore::~CRunicCore((CRunicCore *)this);
  return;
}

/* address=00b91490
   symbol=CPetMenu::~CPetMenu */

/* non-virtual thunk to CPetMenu::~CPetMenu() */

void __thiscall CPetMenu::~CPetMenu(CPetMenu *this)

{
  ~CPetMenu(this + -0x10);
  return;
}

/* address=00b914a0
   symbol=CPetMenu::~CPetMenu */

/* non-virtual thunk to CPetMenu::~CPetMenu() */

void __thiscall CPetMenu::~CPetMenu(CPetMenu *this)

{
  ~CPetMenu(this + -0x10);
  return;
}

/* address=00b914b0
   symbol=CPetMenu::~CPetMenu */

/* CPetMenu::~CPetMenu() */

void __thiscall CPetMenu::~CPetMenu(CPetMenu *this)

{
  ~CPetMenu(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}

/* address=00b914d0
   symbol=CPetMenu::handle_MouseOver */

/* CPetMenu::handle_MouseOver(CEGUI::EventArgs const&) */

undefined8 __thiscall CPetMenu::handle_MouseOver(CPetMenu *this,EventArgs *param_1)

{
  Window *pWVar1;
  char cVar2;
  CBaseUnit *pCVar3;

  if (*(long *)(param_1 + 0x10) == 0) {
    return 1;
  }
  if (*(long *)(this + 0x58) != 0) {
    pCVar3 = (CBaseUnit *)
             CInventory::getEquipmentInSlot
                       (*(CInventory **)(*(long *)(this + 0x58) + 0x490),
                        **(uint **)(*(long *)(param_1 + 0x10) + 0x1d8));
    if (pCVar3 != (CBaseUnit *)0x0) {
      *(CBaseUnit **)(this + 0x1370) = pCVar3;
      if (((pCVar3[0x348] == (CBaseUnit)0x0) || (*(int *)(pCVar3 + 0x3e0) == 0)) &&
         (cVar2 = CBaseUnit::ISA(pCVar3,0x78), cVar2 == '\0')) {
        CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x30),0));
        CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x40),0));
      }
      else {
        CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x40),0));
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
                    /* try { // try from 00b9176c to 00b91770 has its CatchHandler @ 00b91853 */
    CEGUI::Window::setPosition(*(UVector2 **)(this + 0x9110));
                    /* try { // try from 00b917cd to 00b917d1 has its CatchHandler @ 00b9184b */
    CEGUI::Window::setSize(*(UVector2 **)(this + 0x9110));
    CEGUI::Window::moveToBack();
    this[0x9188] = (CPetMenu)0x1;
    return 1;
  }
  return 1;
}

/* address=00b92aa0
   symbol=CPetMenu::setOpen */

/* WARNING: Removing unreachable block (ram,0x00b93028) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CPetMenu::setOpen(bool) */

void __thiscall CPetMenu::setOpen(CPetMenu *this,bool param_1)

{
  int *piVar1;
  Window *pWVar2;
  code *pcVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  CGameUI *pCVar7;
  Camera *pCVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  long local_78 [2];
  string local_68 [16];
  string local_58 [16];
  string local_48 [16];
  string local_38 [11];
  allocator local_2d;
  allocator local_2c;
  allocator local_2b;
  allocator local_2a;
  allocator local_29;

  if (((!param_1) || (*(long *)(this + 0x58) == 0)) ||
     ((iVar5 = *(int *)(*(long *)(this + 0x58) + 0x330), iVar5 != 0x29 && (iVar5 != 0x2a)))) {
    if (this[0x68] == (CPetMenu)0x0) {
      if (!param_1) {
        this[0x68] = (CPetMenu)0x0;
        return;
      }
      CSoundBank::playSample(*(CSoundBank **)(this + 0x91b8),0x16,(SceneNode *)0x0,0.0,0.0,false);
      iVar5 = CDynamicPropertyFile::GetInt
                        (*(CDynamicPropertyFile **)(this + 0x88),KSETTINGS_RES_WIDTH);
      fVar9 = (float)iVar5;
      iVar5 = CDynamicPropertyFile::GetInt
                        (*(CDynamicPropertyFile **)(this + 0x88),KSETTINGS_RES_HEIGHT);
      (**(code **)(**(long **)(this + 0x91a0) + 0x50))(*(long **)(this + 0x91a0),1);
                    /* try { // try from 00b92c5d to 00b92c61 has its CatchHandler @ 00b93035 */
      std::string::string(local_38,"CLOSE",&local_29);
                    /* try { // try from 00b92c6c to 00b92c70 has its CatchHandler @ 00b93033 */
      cVar4 = CGenericModel::animationPlaying(*(CGenericModel **)(this + 0x91a0),local_38);
                    /* try { // try from 00b92c77 to 00b92c7b has its CatchHandler @ 00b93035 */
      std::string::~string(local_38);
      if (cVar4 == '\0') {
                    /* try { // try from 00b92c9a to 00b92c9e has its CatchHandler @ 00b93056 */
        std::string::string(local_58,"OPEN",&local_2b);
                    /* try { // try from 00b92cbb to 00b92cbf has its CatchHandler @ 00b93054 */
        CGenericModel::playAnimation
                  (*(CGenericModel **)(this + 0x91a0),local_58,false,DAT_00fa4824,DAT_00fa8760);
                    /* try { // try from 00b92cc3 to 00b92cc7 has its CatchHandler @ 00b93056 */
        std::string::~string(local_58);
      }
      else {
                    /* try { // try from 00b92df8 to 00b92dfc has its CatchHandler @ 00b93023 */
        std::string::string(local_48,"OPEN",&local_2a);
                    /* try { // try from 00b92e21 to 00b92e25 has its CatchHandler @ 00b93010 */
        CGenericModel::blendAnimation
                  (*(CGenericModel **)(this + 0x91a0),local_48,false,DAT_00fa480c,DAT_00fa4824,
                   DAT_00fa8760);
                    /* try { // try from 00b92e29 to 00b92e2d has its CatchHandler @ 00b93023 */
        std::string::~string(local_48);
      }
                    /* try { // try from 00b92cdd to 00b92ce1 has its CatchHandler @ 00b93052 */
      std::string::string(local_68,"IDLE",&local_2c);
                    /* try { // try from 00b92d01 to 00b92d05 has its CatchHandler @ 00b93049 */
      CGenericModel::queueBlendAnimation
                (*(CGenericModel **)(this + 0x91a0),local_68,true,DAT_00fa480c,DAT_00fa47fc);
                    /* try { // try from 00b92d09 to 00b92d0d has its CatchHandler @ 00b93052 */
      std::string::~string(local_68);
      CEGUI::Window::addChildWindow(*(Window **)(this + 0x18));
      CEGUI::Window::moveToBack();
      CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x91d8),0));
      CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x91e0),0));
      CEGUI::RadioButton::setSelected(SUB81(*(undefined8 *)(this + 0x91e8),0));
      CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x91c0),0));
      CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x91c8),0));
      CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x91d0),0));
      *(undefined4 *)(this + 0x6c) = 0;
      CEGUI::Window::moveToBack();
      CEGUI::Window::moveToFront();
      CEGUI::Window::moveToFront();
      if (*(long *)(this + 0x9180) == 0) {
        pCVar8 = (Camera *)
                 (**(code **)(**(long **)(this + 0x9178) + 0x48))
                           (0,0,DAT_00fa47fc,*(long **)(this + 0x9178),
                            *(undefined8 *)(this + 0x9170),4);
        *(Camera **)(this + 0x9180) = pCVar8;
        fVar11 = *(float *)(this + 0x91b4);
        fVar10 = (float)CGameUI::scaledY(*(CGameUI **)(this + 0x90),DAT_00fce514);
        fVar12 = (fVar11 + fVar10) / fVar9;
        fVar10 = (float)CGameUI::scaledY(*(CGameUI **)(this + 0x90),DAT_00fefd58);
        fVar11 = fVar10 / fVar9;
        if (fVar12 < 0.0) {
          fVar11 = fVar10 / fVar9 + fVar12;
          fVar12 = 0.0;
          fVar9 = DAT_00fa47fc / fVar9 + 0.0;
          if (fVar11 <= fVar9) {
            fVar11 = fVar9;
          }
        }
        fVar9 = (float)CGameUI::scaledY(*(CGameUI **)(this + 0x90),DAT_00ff08c8);
        fVar10 = (float)CGameUI::scaledY(*(CGameUI **)(this + 0x90),_DAT_00ff08cc);
        Ogre::Viewport::setDimensions(fVar12,fVar10 / (float)iVar5,fVar11,fVar9 / (float)iVar5);
        Ogre::Viewport::setBackgroundColour(*(ColourValue **)(this + 0x9180));
        Ogre::Viewport::setClearEveryFrame(SUB81(*(undefined8 *)(this + 0x9180),0),1);
        pcVar3 = *(code **)(**(long **)(this + 0x9170) + 0x278);
        iVar5 = Ogre::Viewport::getActualWidth();
        iVar6 = Ogre::Viewport::getActualHeight();
        (*pcVar3)((float)iVar5 / (float)iVar6,*(undefined8 *)(this + 0x9170));
        Ogre::Viewport::setCamera(pCVar8);
      }
      pCVar7 = (CGameUI *)CResourceManager::getGameUI();
      CGameUI::queueTip(pCVar7,0xf);
    }
    else if (!param_1) {
      if ((*(long *)(this + 0x91f0) != 0) &&
         (pWVar2 = *(Window **)(*(long *)(*(long *)(this + 0x91f0) + 0x30) + 0xb0),
         pWVar2 != (Window *)0x0)) {
        CEGUI::Window::removeChildWindow(pWVar2);
      }
      CSoundBank::playSample(*(CSoundBank **)(this + 0x91b8),0x42,(SceneNode *)0x0,0.0,0.0,false);
                    /* try { // try from 00b92b8a to 00b92b8e has its CatchHandler @ 00b93047 */
      std::string::string((string *)local_78,"CLOSE",&local_2d);
                    /* try { // try from 00b92bb3 to 00b92bb7 has its CatchHandler @ 00b93037 */
      CGenericModel::blendAnimation
                (*(CGenericModel **)(this + 0x91a0),(string *)local_78,false,DAT_00fa480c,
                 DAT_00fa4824,DAT_00fa8760);
      if ((allocator *)(local_78[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_78[0] + -8);
        iVar5 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar5 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
        }
      }
      this[0x69] = (CPetMenu)0x0;
      this[0x68] = (CPetMenu)0x0;
      return;
    }
    this[0x68] = (CPetMenu)param_1;
    (**(code **)(*(long *)this + 0x48))(this);
  }
  return;
}

/* address=00b93070
   symbol=CPetMenu::mapEventHandlers */

/* CPetMenu::mapEventHandlers(CEGUI::Window*) */

void __thiscall CPetMenu::mapEventHandlers(CPetMenu *this,Window *param_1)

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
  String local_1b8 [176];
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
                    /* try { // try from 00b93136 to 00b931b3 has its CatchHandler @ 00b93342 */
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
                    /* try { // try from 00b932b5 to 00b932d2 has its CatchHandler @ 00b93342 */
    CEGUI::String::String(local_1b8,"onClick");
    CEGUI::PropertySet::getProperty((String *)local_268);
    bVar11 = local_268[0] != 0;
                    /* try { // try from 00b932df to 00b932e3 has its CatchHandler @ 00b93315 */
    CEGUI::String::~String((String *)local_268);
                    /* try { // try from 00b932ec to 00b932f0 has its CatchHandler @ 00b93334 */
    CEGUI::String::~String(local_1b8);
  }
                    /* try { // try from 00b931c2 to 00b931f1 has its CatchHandler @ 00b93339 */
  CEGUI::String::~String((String *)&local_108);
  if (bVar11) {
    pcVar3 = *(code **)(*(long *)(param_1 + 0x38) + 0x10);
    local_48[0] = operator_new(0x20);
    local_48[0][3] = this;
    *local_48[0] = &PTR__MemberFunctionSlot_00ff0850;
    local_48[0][2] = 0;
    local_48[0][1] = 0x59;
                    /* try { // try from 00b93231 to 00b93266 has its CatchHandler @ 00b932f6 */
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
                    /* try { // try from 00b93297 to 00b9329b has its CatchHandler @ 00b93339 */
    CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_48);
  }
  return;
}

/* address=00b93350
   symbol=CPetMenu::createMenus */

/* WARNING: Removing unreachable block (ram,0x00b9a687) */
/* WARNING: Removing unreachable block (ram,0x00b9a704) */
/* WARNING: Removing unreachable block (ram,0x00b9a1e6) */
/* WARNING: Removing unreachable block (ram,0x00b99dbc) */
/* WARNING: Removing unreachable block (ram,0x00b99daf) */
/* WARNING: Removing unreachable block (ram,0x00b99c7d) */
/* WARNING: Removing unreachable block (ram,0x00b9aa5a) */
/* WARNING: Removing unreachable block (ram,0x00b9a570) */
/* WARNING: Removing unreachable block (ram,0x00b99c88) */
/* WARNING: Removing unreachable block (ram,0x00b99ee4) */
/* WARNING: Removing unreachable block (ram,0x00b9a12b) */
/* WARNING: Removing unreachable block (ram,0x00b9a6c9) */
/* WARNING: Removing unreachable block (ram,0x00b9a6d7) */
/* WARNING: Removing unreachable block (ram,0x00b9a692) */
/* WARNING: Removing unreachable block (ram,0x00b99fb4) */
/* WARNING: Removing unreachable block (ram,0x00b99eef) */
/* WARNING: Removing unreachable block (ram,0x00b9a57b) */
/* WARNING: Removing unreachable block (ram,0x00b9a084) */
/* WARNING: Removing unreachable block (ram,0x00b9a136) */
/* WARNING: Removing unreachable block (ram,0x00b9a297) */
/* WARNING: Removing unreachable block (ram,0x00b99fbf) */
/* WARNING: Removing unreachable block (ram,0x00b9a2a2) */
/* WARNING: Removing unreachable block (ram,0x00b9a08f) */
/* WARNING: Removing unreachable block (ram,0x00b9a35a) */
/* WARNING: Removing unreachable block (ram,0x00b9a365) */
/* CPetMenu::createMenus() */

void __thiscall CPetMenu::createMenus(CPetMenu *this)

{
  int *piVar1;
  byte bVar2;
  code *pcVar3;
  undefined8 uVar4;
  BoundSlot *pBVar5;
  int iVar6;
  int iVar7;
  CGenericModel *this_00;
  long lVar8;
  undefined8 uVar9;
  char *pcVar10;
  CFileSystem *this_01;
  String *pSVar11;
  byte *pbVar12;
  String *pSVar13;
  long *plVar14;
  CPetMenu *pCVar15;
  UVector2 *pUVar16;
  undefined8 *puVar17;
  uint *puVar18;
  undefined4 *puVar19;
  CRunicCore *this_02;
  CPetMenu *pCVar20;
  long lVar21;
  undefined1 *puVar22;
  bool bVar23;
  ulong uVar24;
  CPetMenu *pCVar25;
  long *plVar26;
  float fVar27;
  float fVar28;
  uint local_48c4;
  CPetMenu *local_48b8;
  long local_4898;
  ulong local_4890;
  undefined8 local_4888;
  undefined8 local_4880;
  undefined8 local_4878;
  undefined4 local_4870 [32];
  undefined4 *local_47f0;
  undefined8 local_47e8;
  ulong local_47e0;
  undefined8 local_47d8;
  undefined8 local_47d0;
  undefined8 local_47c8;
  undefined4 local_47c0 [32];
  undefined4 *local_4740;
  long local_4738;
  ulong local_4730;
  undefined8 local_4728;
  undefined8 local_4720;
  undefined8 local_4718;
  undefined4 local_4710 [32];
  undefined4 *local_4690;
  String local_4688 [176];
  undefined8 local_45d8;
  ulong local_45d0;
  undefined8 local_45c8;
  undefined8 local_45c0;
  undefined8 local_45b8;
  undefined4 local_45b0 [32];
  undefined4 *local_4530;
  long local_4528;
  ulong local_4520;
  undefined8 local_4518;
  undefined8 local_4510;
  undefined8 local_4508;
  undefined4 local_4500 [32];
  undefined4 *local_4480;
  String local_4478 [176];
  undefined8 local_43c8;
  ulong local_43c0;
  undefined8 local_43b8;
  undefined8 local_43b0;
  undefined8 local_43a8;
  undefined4 local_43a0 [32];
  undefined4 *local_4320;
  long local_4318;
  ulong local_4310;
  undefined8 local_4308;
  undefined8 local_4300;
  undefined8 local_42f8;
  undefined4 local_42f0 [32];
  undefined4 *local_4270;
  String local_4268 [176];
  undefined8 local_41b8;
  ulong local_41b0;
  undefined8 local_41a8;
  undefined8 local_41a0;
  undefined8 local_4198;
  uint local_4190 [10];
  uint local_4168 [22];
  uint *local_4110;
  String local_4108 [176];
  String local_4058 [176];
  undefined8 local_3fa8;
  ulong local_3fa0;
  undefined8 local_3f98;
  undefined8 local_3f90;
  undefined8 local_3f88;
  uint local_3f80 [13];
  uint local_3f4c [19];
  uint *local_3f00;
  undefined8 local_3ef8;
  ulong local_3ef0;
  undefined8 local_3ee8;
  undefined8 local_3ee0;
  undefined8 local_3ed8;
  uint local_3ed0 [14];
  uint local_3e98 [18];
  uint *local_3e50;
  undefined8 local_3e48;
  ulong local_3e40;
  undefined8 local_3e38;
  undefined8 local_3e30;
  undefined8 local_3e28;
  uint local_3e20 [12];
  uint local_3df0 [20];
  uint *local_3da0;
  undefined8 local_3d98;
  ulong local_3d90;
  undefined8 local_3d88;
  undefined8 local_3d80;
  undefined8 local_3d78;
  uint local_3d70 [18];
  uint local_3d28 [14];
  uint *local_3cf0;
  undefined8 local_3ce8;
  ulong local_3ce0;
  undefined8 local_3cd8;
  undefined8 local_3cd0;
  undefined8 local_3cc8;
  uint local_3cc0 [5];
  uint local_3cac [27];
  uint *local_3c40;
  undefined8 local_3c38;
  ulong local_3c30;
  undefined8 local_3c28;
  undefined8 local_3c20;
  undefined8 local_3c18;
  undefined4 local_3c10 [32];
  undefined4 *local_3b90;
  long local_3b88;
  ulong local_3b80;
  undefined8 local_3b78;
  undefined8 local_3b70;
  undefined8 local_3b68;
  undefined4 local_3b60 [32];
  undefined4 *local_3ae0;
  String local_3ad8 [176];
  long local_3a28;
  ulong local_3a20;
  undefined8 local_3a18;
  undefined8 local_3a10;
  undefined8 local_3a08;
  undefined4 local_3a00 [32];
  undefined4 *local_3980;
  undefined8 local_3978;
  ulong local_3970;
  undefined8 local_3968;
  undefined8 local_3960;
  undefined8 local_3958;
  uint local_3950 [9];
  uint local_392c [23];
  uint *local_38d0;
  undefined8 local_38c8;
  ulong local_38c0;
  undefined8 local_38b8;
  undefined8 local_38b0;
  undefined8 local_38a8;
  uint local_38a0 [11];
  uint local_3874 [21];
  uint *local_3820;
  undefined8 local_3818;
  ulong local_3810;
  undefined8 local_3808;
  undefined8 local_3800;
  undefined8 local_37f8;
  uint local_37f0 [14];
  uint local_37b8 [18];
  uint *local_3770;
  long local_3768;
  ulong local_3760;
  undefined1 local_3740 [128];
  undefined1 *local_36c0;
  undefined8 local_36b8;
  ulong local_36b0;
  undefined8 local_36a8;
  undefined8 local_36a0;
  undefined8 local_3698;
  uint local_3690 [13];
  uint local_365c [19];
  uint *local_3610;
  long local_3608;
  ulong local_3600;
  undefined1 local_35e0 [128];
  undefined1 *local_3560;
  undefined8 local_3558;
  ulong local_3550;
  undefined8 local_3548;
  undefined8 local_3540;
  undefined8 local_3538;
  uint local_3530 [15];
  uint local_34f4 [17];
  uint *local_34b0;
  undefined8 local_34a8;
  ulong local_34a0;
  undefined8 local_3498;
  undefined8 local_3490;
  undefined8 local_3488;
  uint local_3480 [7];
  uint local_3464 [25];
  uint *local_3400;
  long local_33f8;
  ulong local_33f0;
  undefined1 local_33d0 [128];
  undefined1 *local_3350;
  undefined8 local_3348;
  ulong local_3340;
  undefined8 local_3338;
  undefined8 local_3330;
  undefined8 local_3328;
  uint local_3320 [13];
  uint local_32ec [19];
  uint *local_32a0;
  long local_3298;
  ulong local_3290;
  undefined1 local_3270 [128];
  undefined1 *local_31f0;
  undefined8 local_31e8;
  ulong local_31e0;
  undefined8 local_31d8;
  undefined8 local_31d0;
  undefined8 local_31c8;
  uint local_31c0 [15];
  uint local_3184 [17];
  uint *local_3140;
  undefined8 local_3138;
  ulong local_3130;
  undefined8 local_3128;
  undefined8 local_3120;
  undefined8 local_3118;
  uint local_3110 [8];
  uint local_30f0 [24];
  uint *local_3090;
  long local_3088;
  ulong local_3080;
  undefined1 local_3060 [128];
  undefined1 *local_2fe0;
  undefined8 local_2fd8;
  ulong local_2fd0;
  undefined8 local_2fc8;
  undefined8 local_2fc0;
  undefined8 local_2fb8;
  uint local_2fb0 [13];
  uint local_2f7c [19];
  uint *local_2f30;
  long local_2f28;
  ulong local_2f20;
  undefined1 local_2f00 [128];
  undefined1 *local_2e80;
  undefined8 local_2e78;
  ulong local_2e70;
  undefined8 local_2e68;
  undefined8 local_2e60;
  undefined8 local_2e58;
  uint local_2e50 [15];
  uint local_2e14 [17];
  uint *local_2dd0;
  undefined8 local_2dc8;
  ulong local_2dc0;
  undefined8 local_2db8;
  undefined8 local_2db0;
  undefined8 local_2da8;
  uint local_2da0 [11];
  uint local_2d74 [21];
  uint *local_2d20;
  undefined8 local_2d18;
  ulong local_2d10;
  undefined8 local_2d08;
  undefined8 local_2d00;
  undefined8 local_2cf8;
  undefined4 local_2cf0 [32];
  undefined4 *local_2c70;
  long local_2c68;
  ulong local_2c60;
  undefined8 local_2c58;
  undefined8 local_2c50;
  undefined8 local_2c48;
  undefined4 local_2c40 [32];
  undefined4 *local_2bc0;
  String local_2bb8 [176];
  undefined8 local_2b08;
  ulong local_2b00;
  undefined8 local_2af8;
  undefined8 local_2af0;
  undefined8 local_2ae8;
  undefined4 local_2ae0 [32];
  undefined4 *local_2a60;
  long local_2a58;
  ulong local_2a50;
  undefined8 local_2a48;
  undefined8 local_2a40;
  undefined8 local_2a38;
  undefined4 local_2a30 [32];
  undefined4 *local_29b0;
  String local_29a8 [176];
  undefined8 local_28f8;
  ulong local_28f0;
  undefined8 local_28e8;
  undefined8 local_28e0;
  undefined8 local_28d8;
  undefined4 local_28d0 [32];
  undefined4 *local_2850;
  long local_2848;
  ulong local_2840;
  undefined8 local_2838;
  undefined8 local_2830;
  undefined8 local_2828;
  undefined4 local_2820 [32];
  undefined4 *local_27a0;
  String local_2798 [176];
  long local_26e8;
  ulong local_26e0;
  undefined1 auStack_26c0 [128];
  undefined1 *local_2640;
  undefined8 local_2638;
  ulong local_2630;
  undefined8 local_2628;
  undefined8 local_2620;
  undefined8 local_2618;
  uint local_2610 [5];
  uint local_25fc [27];
  uint *local_2590;
  long local_2588;
  ulong local_2580;
  undefined8 local_2578;
  undefined8 local_2570;
  undefined8 local_2568;
  undefined4 local_2560 [32];
  undefined4 *local_24e0;
  undefined8 local_24d8;
  ulong local_24d0;
  undefined8 local_24c8;
  undefined8 local_24c0;
  undefined8 local_24b8;
  uint local_24b0 [11];
  uint local_2484 [21];
  uint *local_2430;
  undefined8 local_2428;
  ulong local_2420;
  undefined8 local_2418;
  undefined8 local_2410;
  undefined8 local_2408;
  uint local_2400 [10];
  uint local_23d8 [22];
  uint *local_2380;
  undefined8 local_2378;
  ulong local_2370;
  undefined8 local_2368;
  undefined8 local_2360;
  undefined8 local_2358;
  uint local_2350 [14];
  uint local_2318 [18];
  uint *local_22d0;
  undefined8 local_22c8;
  ulong local_22c0;
  undefined8 local_22b8;
  undefined8 local_22b0;
  undefined8 local_22a8;
  uint local_22a0 [5];
  uint local_228c [27];
  uint *local_2220;
  undefined8 local_2218;
  ulong local_2210;
  undefined8 local_2208;
  undefined8 local_2200;
  undefined8 local_21f8;
  uint local_21f0 [8];
  uint local_21d0 [24];
  uint *local_2170;
  undefined8 local_2168;
  ulong local_2160;
  undefined8 local_2158;
  undefined8 local_2150;
  undefined8 local_2148;
  uint local_2140 [5];
  uint local_212c [27];
  uint *local_20c0;
  undefined8 local_20b8;
  ulong local_20b0;
  undefined8 local_20a8;
  undefined8 local_20a0;
  undefined8 local_2098;
  uint local_2090 [11];
  uint local_2064 [21];
  uint *local_2010;
  undefined8 local_2008;
  ulong local_2000;
  undefined8 local_1ff8;
  undefined8 local_1ff0;
  undefined8 local_1fe8;
  undefined4 local_1fe0 [32];
  undefined4 *local_1f60;
  String local_1f58 [176];
  String local_1ea8 [176];
  undefined8 local_1df8;
  ulong local_1df0;
  undefined8 local_1de8;
  undefined8 local_1de0;
  undefined8 local_1dd8;
  uint local_1dd0 [5];
  uint local_1dbc [27];
  uint *local_1d50;
  undefined8 local_1d48;
  ulong local_1d40;
  undefined8 local_1d38;
  undefined8 local_1d30;
  undefined8 local_1d28;
  uint local_1d20 [11];
  uint local_1cf4 [21];
  uint *local_1ca0;
  undefined8 local_1c98;
  ulong local_1c90;
  undefined8 local_1c88;
  undefined8 local_1c80;
  undefined8 local_1c78;
  undefined4 local_1c70 [32];
  undefined4 *local_1bf0;
  String local_1be8 [176];
  String local_1b38 [176];
  undefined8 local_1a88;
  ulong local_1a80;
  undefined8 local_1a78;
  undefined8 local_1a70;
  undefined8 local_1a68;
  uint local_1a60 [5];
  uint local_1a4c [27];
  uint *local_19e0;
  undefined8 local_19d8;
  ulong local_19d0;
  undefined8 local_19c8;
  undefined8 local_19c0;
  undefined8 local_19b8;
  uint local_19b0 [11];
  uint local_1984 [21];
  uint *local_1930;
  undefined8 local_1928;
  ulong local_1920;
  undefined8 local_1918;
  undefined8 local_1910;
  undefined8 local_1908;
  undefined4 local_1900 [32];
  undefined4 *local_1880;
  String local_1878 [176];
  String local_17c8 [176];
  undefined8 local_1718;
  ulong local_1710;
  undefined8 local_1708;
  undefined8 local_1700;
  undefined8 local_16f8;
  uint local_16f0 [5];
  uint local_16dc [27];
  uint *local_1670;
  undefined8 local_1668;
  ulong local_1660;
  undefined8 local_1658;
  undefined8 local_1650;
  undefined8 local_1648;
  uint local_1640 [11];
  uint local_1614 [21];
  uint *local_15c0;
  undefined8 local_15b8;
  ulong local_15b0;
  undefined8 local_15a8;
  undefined8 local_15a0;
  undefined8 local_1598;
  uint local_1590 [8];
  uint local_1570 [24];
  uint *local_1510;
  undefined8 local_1508;
  ulong local_1500;
  undefined8 local_14f8;
  undefined8 local_14f0;
  undefined8 local_14e8;
  uint local_14e0 [5];
  uint local_14cc [27];
  uint *local_1460;
  undefined8 local_1458;
  ulong local_1450;
  undefined8 local_1448;
  undefined8 local_1440;
  undefined8 local_1438;
  uint local_1430 [11];
  uint local_1404 [21];
  uint *local_13b0;
  undefined8 local_13a8;
  ulong local_13a0;
  undefined8 local_1398;
  undefined8 local_1390;
  undefined8 local_1388;
  uint local_1380 [11];
  uint local_1354 [21];
  uint *local_1300;
  undefined8 local_12f8;
  ulong local_12f0;
  undefined8 local_12e8;
  undefined8 local_12e0;
  undefined8 local_12d8;
  uint local_12d0 [5];
  uint local_12bc [27];
  uint *local_1250;
  undefined8 local_1248;
  ulong local_1240;
  undefined8 local_1238;
  undefined8 local_1230;
  undefined8 local_1228;
  uint local_1220 [11];
  uint local_11f4 [21];
  uint *local_11a0;
  undefined8 local_1198;
  ulong local_1190;
  undefined8 local_1188;
  undefined8 local_1180;
  undefined8 local_1178;
  uint local_1170 [7];
  uint local_1154 [25];
  uint *local_10f0;
  undefined8 local_10e8;
  ulong local_10e0;
  undefined8 local_10d8;
  undefined8 local_10d0;
  undefined8 local_10c8;
  uint local_10c0 [7];
  uint local_10a4 [25];
  uint *local_1040;
  undefined8 local_1038;
  ulong local_1030;
  undefined8 local_1028;
  undefined8 local_1020;
  undefined8 local_1018;
  uint local_1010 [11];
  uint local_fe4 [21];
  uint *local_f90;
  undefined8 local_f88;
  ulong local_f80;
  undefined8 local_f78;
  undefined8 local_f70;
  undefined8 local_f68;
  uint local_f60 [12];
  uint local_f30 [20];
  uint *local_ee0;
  undefined8 local_ed8;
  ulong local_ed0;
  undefined8 local_ec8;
  undefined8 local_ec0;
  undefined8 local_eb8;
  uint local_eb0 [11];
  uint local_e84 [21];
  uint *local_e30;
  undefined8 local_e28;
  ulong local_e20;
  undefined8 local_e18;
  undefined8 local_e10;
  undefined8 local_e08;
  undefined4 local_e00 [4];
  undefined4 local_df0 [28];
  undefined4 *local_d80;
  undefined8 local_d78;
  ulong local_d70;
  undefined8 local_d68;
  undefined8 local_d60;
  undefined8 local_d58;
  undefined4 local_d50 [2];
  undefined4 local_d48 [30];
  undefined4 *local_cd0;
  undefined8 local_cc8;
  ulong local_cc0;
  undefined8 local_cb8;
  undefined8 local_cb0;
  undefined8 local_ca8;
  undefined4 local_ca0 [2];
  undefined4 local_c98 [30];
  undefined4 *local_c20;
  undefined8 local_c18;
  ulong local_c10;
  undefined8 local_c08;
  undefined8 local_c00;
  undefined8 local_bf8;
  uint local_bf0 [5];
  uint local_bdc [27];
  uint *local_b70;
  undefined8 local_b68;
  ulong local_b60;
  undefined8 local_b58;
  undefined8 local_b50;
  undefined8 local_b48;
  uint local_b40 [13];
  uint local_b0c [19];
  uint *local_ac0;
  long local_ab8;
  ulong local_ab0;
  undefined8 local_aa8;
  undefined8 local_aa0;
  undefined8 local_a98;
  undefined4 local_a90 [32];
  undefined4 *local_a10;
  undefined8 local_a08;
  ulong local_a00;
  undefined8 local_9f8;
  undefined8 local_9f0;
  undefined8 local_9e8;
  uint local_9e0 [5];
  uint local_9cc [27];
  uint *local_960;
  undefined8 local_958;
  ulong local_950;
  undefined8 local_948;
  undefined8 local_940;
  undefined8 local_938;
  uint local_930 [11];
  uint local_904 [21];
  uint *local_8b0;
  undefined8 local_8a8;
  ulong local_8a0;
  undefined8 local_898;
  undefined8 local_890;
  undefined8 local_888;
  undefined4 local_880 [32];
  undefined4 *local_800;
  String local_7f8 [176];
  String local_748 [176];
  String local_698 [176];
  undefined1 *local_5e8;
  long local_5e0;
  long local_5d8;
  undefined4 local_5d0;
  undefined4 local_5cc;
  undefined1 *local_5c8;
  undefined1 local_5c0;
  undefined4 local_5b8;
  undefined4 local_5b4;
  undefined4 local_5b0;
  undefined4 local_5ac;
  undefined4 local_5a8;
  undefined4 local_5a4;
  undefined4 local_5a0;
  void *local_598;
  undefined1 local_588 [32];
  BoundSlot *local_568;
  int *local_560;
  BoundSlot *local_558;
  int *local_550;
  BoundSlot *local_548;
  int *local_540;
  BoundSlot *local_538;
  int *local_530;
  undefined8 local_4f8;
  undefined8 local_4f0;
  BoundSlot *local_4d8;
  int *local_4d0;
  BoundSlot *local_4c8;
  int *local_4c0;
  BoundSlot *local_4b8;
  int *local_4b0;
  BoundSlot *local_4a8;
  int *local_4a0;
  BoundSlot *local_468;
  int *local_460;
  BoundSlot *local_458;
  int *local_450;
  BoundSlot *local_448;
  int *local_440;
  BoundSlot *local_438;
  int *local_430;
  BoundSlot *local_428;
  int *local_420;
  BoundSlot *local_418;
  int *local_410;
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
  BoundSlot *local_3b8;
  int *local_3b0;
  undefined4 local_3a8;
  undefined4 local_3a4;
  undefined4 local_3a0;
  undefined4 local_39c;
  undefined4 local_388;
  undefined4 local_384;
  undefined4 local_380;
  undefined4 local_37c;
  undefined4 local_368;
  undefined4 local_364;
  undefined4 local_360;
  undefined4 local_35c;
  BoundSlot *local_348;
  int *local_340;
  undefined4 local_338;
  undefined4 local_334;
  undefined4 local_330;
  undefined4 local_32c;
  undefined4 local_328;
  undefined4 local_324;
  undefined4 local_320;
  undefined4 local_31c;
  undefined4 local_318;
  undefined4 local_314;
  undefined4 local_310;
  undefined4 local_308;
  undefined4 local_304;
  undefined4 local_300;
  long local_2f8 [2];
  long local_2e8 [2];
  undefined8 *local_2d8 [2];
  undefined8 *local_2c8 [2];
  undefined8 *local_2b8 [2];
  undefined8 *local_2a8 [2];
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
  undefined8 *local_1f8 [2];
  undefined8 *local_1e8 [2];
  undefined8 *local_1d8 [2];
  undefined8 *local_1c8 [2];
  long local_1b8 [2];
  long local_1a8 [2];
  long local_198 [2];
  long local_188 [2];
  long local_178 [2];
  long local_168 [2];
  long local_158 [2];
  long local_148 [2];
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
  undefined8 *local_98 [2];
  undefined8 *local_88 [2];
  long local_78 [2];
  undefined8 *local_68 [4];
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

  iVar6 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0x88),KSETTINGS_RES_WIDTH);
  iVar7 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0x88),KSETTINGS_RES_HEIGHT)
  ;
  this_00 = (CGenericModel *)
            CResourceManager::createGenericModel
                      (*(CResourceManager **)(this + 0x91a8),*(SceneManager **)(this + 0x9160),
                       L"media/ui/models/pet/pet.mesh",L"",false,false,false);
  *(CGenericModel **)(this + 0x91a0) = this_00;
  CGenericModel::generateExtremes(this_00,5,true);
  local_598 = (void *)0x0;
  local_5a0 = 1;
  local_5b8 = 0xc7c35000;
  local_5b4 = 0xc7c35000;
  local_5b0 = 0xc7c35000;
  local_5ac = 0x47c35000;
  local_5a8 = 0x47c35000;
  local_5a4 = 0x47c35000;
                    /* try { // try from 00b93448 to 00b934ed has its CatchHandler @ 00b9a80c */
  lVar8 = Ogre::Entity::getMesh();
  Ogre::Mesh::_setBounds(*(AxisAlignedBox **)(lVar8 + 8),SUB81(&local_5b8,0));
  fVar27 = (float)iVar7 / DAT_00fc6774;
  pcVar3 = *(code **)(**(long **)(this + 0x91a0) + 0x58);
  fVar28 = (float)CDynamicPropertyFile::GetFloat
                            (*(CDynamicPropertyFile **)(this + 0x88),KSETTINGS_YRATIO);
  (*pcVar3)(DAT_00fa86f4 * (((float)iVar6 - fVar27) / fVar28),0,*(undefined8 *)(this + 0x91a0));
  (**(code **)(**(long **)(this + 0x91a0) + 0x50))(*(long **)(this + 0x91a0),0);
  CEGUI::String::String(local_698,(uchar *)"UIIcons");
                    /* try { // try from 00b934f8 to 00b934fc has its CatchHandler @ 00b9a814 */
  uVar9 = CEGUI::ImagesetManager::getImageset
                    (CEGUI::Singleton<CEGUI::ImagesetManager>::ms_Singleton);
  *(undefined8 *)(this + 0x9108) = uVar9;
                    /* try { // try from 00b93508 to 00b93571 has its CatchHandler @ 00b9a80c */
  CEGUI::String::~String(local_698);
  local_8a0 = 0x20;
  local_898 = 0;
  local_888 = 0;
  local_890 = 0;
  local_800 = (undefined4 *)0x0;
  local_8a8 = 0;
  local_880[0] = 0;
  CEGUI::String::grow((ulong)&local_8a8);
  local_8a8 = 0;
  puVar19 = local_880;
  if (0x20 < local_8a0) {
    puVar19 = local_800;
  }
  *puVar19 = 0;
                    /* try { // try from 00b935ab to 00b935af has its CatchHandler @ 00b9a824 */
  CEGUI::String::String(local_7f8,(uchar *)"PetSheet");
                    /* try { // try from 00b935c0 to 00b935c4 has its CatchHandler @ 00b9a835 */
  CEGUI::String::String(local_748,(uchar *)"DefaultWindow");
                    /* try { // try from 00b935d5 to 00b935d9 has its CatchHandler @ 00b9a842 */
  uVar9 = CEGUI::WindowManager::createWindow
                    (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,local_748,local_7f8);
  *(undefined8 *)(this + 0x20) = uVar9;
                    /* try { // try from 00b935e2 to 00b935e6 has its CatchHandler @ 00b9a835 */
  CEGUI::String::~String(local_748);
                    /* try { // try from 00b935ea to 00b935ee has its CatchHandler @ 00b9a824 */
  CEGUI::String::~String(local_7f8);
                    /* try { // try from 00b935f2 to 00b935f6 has its CatchHandler @ 00b9a80c */
  CEGUI::String::~String((String *)&local_8a8);
  local_324 = 0;
  local_328 = 0x3f800000;
  local_31c = 0;
  local_320 = 0x3f800000;
                    /* try { // try from 00b93630 to 00b93634 has its CatchHandler @ 00b9a84f */
  CEGUI::Window::setSize(*(UVector2 **)(this + 0x20));
  local_a00 = 0x20;
  local_9f8 = 0;
  local_9e8 = 0;
  local_9f0 = 0;
  local_960 = (uint *)0x0;
  local_a08 = 0;
  local_9e0[0] = 0;
                    /* try { // try from 00b93698 to 00b9369c has its CatchHandler @ 00b9a80c */
  CEGUI::String::grow((ulong)&local_a08);
  puVar18 = local_9e0;
  if (0x20 < local_a00) {
    puVar18 = local_960;
  }
  pcVar10 = "False";
  do {
    bVar2 = *pcVar10;
    pcVar10 = pcVar10 + 1;
    *puVar18 = (uint)bVar2;
    puVar18 = puVar18 + 1;
  } while ((byte *)pcVar10 != (byte *)0xfe603f);
  local_a08 = 5;
  puVar18 = local_9cc;
  if (0x20 < local_a00) {
    puVar18 = local_960 + 5;
  }
  *puVar18 = 0;
  local_950 = 0x20;
  local_948 = 0;
  local_938 = 0;
  local_940 = 0;
  local_8b0 = (uint *)0x0;
  local_958 = 0;
  local_930[0] = 0;
                    /* try { // try from 00b93765 to 00b93769 has its CatchHandler @ 00b9a852 */
  CEGUI::String::grow((ulong)&local_958);
  puVar18 = local_930;
  if (0x20 < local_950) {
    puVar18 = local_8b0;
  }
  pcVar10 = "RiseOnClick";
  do {
    bVar2 = *pcVar10;
    pcVar10 = pcVar10 + 1;
    *puVar18 = (uint)bVar2;
    puVar18 = puVar18 + 1;
  } while ((byte *)pcVar10 != (byte *)0xfe6039);
  local_958 = 0xb;
  puVar18 = local_904;
  if (0x20 < local_950) {
    puVar18 = local_8b0 + 0xb;
  }
  *puVar18 = 0;
                    /* try { // try from 00b937dd to 00b937e1 has its CatchHandler @ 00b9a862 */
  CEGUI::PropertySet::setProperty(*(String **)(this + 0x20),(String *)&local_958);
                    /* try { // try from 00b937e5 to 00b937e9 has its CatchHandler @ 00b9a852 */
  CEGUI::String::~String((String *)&local_958);
                    /* try { // try from 00b937ed to 00b937f1 has its CatchHandler @ 00b9a80c */
  CEGUI::String::~String((String *)&local_a08);
  local_334 = 0;
  local_338 = 0;
  local_32c = 0;
  local_330 = 0;
                    /* try { // try from 00b9382b to 00b9382f has its CatchHandler @ 00b9a8c8 */
  CEGUI::Window::setPosition(*(UVector2 **)(this + 0x20));
  *(undefined1 *)(*(long *)(this + 0x20) + 0x3e2) = 1;
                    /* try { // try from 00b93843 to 00b9385e has its CatchHandler @ 00b9a80c */
  CEGUI::Window::setZOrderingEnabled(SUB81(*(undefined8 *)(this + 0x20),0));
  pcVar3 = *(code **)(*(long *)(*(long *)(this + 0x20) + 0x38) + 0x10);
  local_68[0] = operator_new(0x20);
  *local_68[0] = &PTR__MemberFunctionSlot_00ff0850;
  local_68[0][2] = 0;
  local_68[0][1] = handle_MouseThrough;
  local_68[0][3] = this;
                    /* try { // try from 00b938a3 to 00b938d7 has its CatchHandler @ 00b9aa45 */
  (*pcVar3)(&local_348,*(long *)(this + 0x20) + 0x38,CEGUI::Window::EventMouseMove);
  if ((local_348 != (BoundSlot *)0x0) &&
     (iVar6 = *local_340, *local_340 = iVar6 + -1, iVar6 + -1 == 0)) {
    if (local_348 != (BoundSlot *)0x0) {
      CEGUI::BoundSlot::~BoundSlot(local_348);
      operator_delete(local_348);
    }
    operator_delete(local_340);
    local_348 = (BoundSlot *)0x0;
    local_340 = (int *)0x0;
  }
                    /* try { // try from 00b93908 to 00b9390c has its CatchHandler @ 00b9a80c */
  CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_68);
  local_5e8 = &DAT_01423a38;
                    /* try { // try from 00b9392a to 00b9392e has its CatchHandler @ 00b99bab */
  std::string::string((string *)&local_5e0,(string *)&::EMPTY_STRING);
                    /* try { // try from 00b93940 to 00b93944 has its CatchHandler @ 00b9a86f */
  std::wstring::wstring((wstring_conflict *)&local_5d8,(wstring_conflict *)&::EMPTY_WSTRING);
  local_5d0 = 4;
  local_5cc = 3;
  local_5c8 = &DAT_01423a38;
  local_5c0 = 0;
                    /* try { // try from 00b93987 to 00b9398b has its CatchHandler @ 00b9a888 */
  std::wstring::wstring((wstring_conflict *)local_78,L"media/ui/petmenu.layout",local_39);
                    /* try { // try from 00b9398c to 00b939ae has its CatchHandler @ 00b9a88d */
  this_01 = (CFileSystem *)CFileSystem::getSingleton();
  CFileSystem::getFileInfo
            (this_01,(wstring_conflict *)local_78,(CFileInfo *)&local_5e8,false,true,false);
  if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_78[0] + -8);
    iVar6 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar6 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
    }
  }
  local_ab0 = 0x20;
  local_aa8 = 0;
  local_a98 = 0;
  local_aa0 = 0;
  local_a10 = (undefined4 *)0x0;
  local_ab8 = 0;
  local_a90[0] = 0;
  lVar8 = *(long *)(local_5e0 + -0x18);
                    /* try { // try from 00b93a35 to 00b93a39 has its CatchHandler @ 00b9a724 */
  CEGUI::String::grow((ulong)&local_ab8);
  puVar19 = local_a90;
  if (0x20 < local_ab0) {
    puVar19 = local_a10;
  }
  puVar19[lVar8] = 0;
  if (lVar8 != 0) {
    lVar21 = lVar8;
    do {
      lVar21 = lVar21 + -1;
      puVar19 = local_a90;
      if (0x20 < local_ab0) {
        puVar19 = local_a10;
      }
      puVar19[lVar21] = (uint)*(byte *)(local_5e0 + lVar21);
    } while (lVar21 != 0);
  }
  local_ab8 = lVar8;
                    /* try { // try from 00b93aac to 00b93ab0 has its CatchHandler @ 00b9a729 */
  pSVar11 = (String *)
            CEGUI::WindowManager::loadWindowLayout
                      (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,
                       SUB81((String *)&local_ab8,0));
                    /* try { // try from 00b93ab7 to 00b93b50 has its CatchHandler @ 00b9a724 */
  CEGUI::String::~String((String *)&local_ab8);
  CGameUI::convertToScreenScale(*(CGameUI **)(this + 0x90),(Window *)pSVar11,false);
  CGameUI::mapToFunctions(*(CGameUI **)(this + 0x90),(Window *)pSVar11);
  mapEventHandlers(this,(Window *)pSVar11);
  local_b60 = 0x20;
  local_b58 = 0;
  local_b48 = 0;
  local_b50 = 0;
  local_ac0 = (uint *)0x0;
  local_b68 = 0;
  local_b40[0] = 0;
  CEGUI::String::grow((ulong)&local_b68);
  puVar18 = local_b40;
  if (0x20 < local_b60) {
    puVar18 = local_ac0;
  }
  pcVar10 = "CharacterName";
  do {
    bVar2 = *pcVar10;
    pcVar10 = pcVar10 + 1;
    *puVar18 = (uint)bVar2;
    puVar18 = puVar18 + 1;
  } while ((byte *)pcVar10 != (byte *)0xff053a);
  local_b68 = 0xd;
  puVar18 = local_b0c;
  if (0x20 < local_b60) {
    puVar18 = local_ac0 + 0xd;
  }
  *puVar18 = 0;
                    /* try { // try from 00b93bb8 to 00b93bbc has its CatchHandler @ 00b9a735 */
  uVar9 = CEGUI::Window::recursiveChildSearch(pSVar11);
  *(undefined8 *)(this + 0x9118) = uVar9;
                    /* try { // try from 00b93bc8 to 00b93c34 has its CatchHandler @ 00b9a724 */
  CEGUI::String::~String((String *)&local_b68);
  local_c10 = 0x20;
  local_c08 = 0;
  local_bf8 = 0;
  local_c00 = 0;
  local_b70 = (uint *)0x0;
  local_c18 = 0;
  local_bf0[0] = 0;
  CEGUI::String::grow((ulong)&local_c18);
  puVar18 = local_bf0;
  if (0x20 < local_c10) {
    puVar18 = local_b70;
  }
  pbVar12 = (byte *)0xfe46fc;
  do {
    bVar2 = *pbVar12;
    pbVar12 = pbVar12 + 1;
    *puVar18 = (uint)bVar2;
    puVar18 = puVar18 + 1;
  } while (pbVar12 != (byte *)0xfe4701);
  local_c18 = 5;
  puVar18 = local_bdc;
  if (0x20 < local_c10) {
    puVar18 = local_b70 + 5;
  }
  *puVar18 = 0;
                    /* try { // try from 00b93ca0 to 00b93ca4 has its CatchHandler @ 00b9a745 */
  uVar9 = CEGUI::Window::recursiveChildSearch(pSVar11);
  *(undefined8 *)(this + 0x9120) = uVar9;
                    /* try { // try from 00b93cb0 to 00b93d1c has its CatchHandler @ 00b9a724 */
  CEGUI::String::~String((String *)&local_c18);
  local_cc0 = 0x20;
  local_cb8 = 0;
  local_ca8 = 0;
  local_cb0 = 0;
  local_c20 = (undefined4 *)0x0;
  local_cc8 = 0;
  local_ca0[0] = 0;
  CEGUI::String::grow((ulong)&local_cc8);
  puVar19 = local_ca0;
  if (0x20 < local_cc0) {
    puVar19 = local_c20;
  }
  *puVar19 = 0x58;
  puVar19[1] = 0x50;
  puVar19 = local_c98;
  local_cc8 = 2;
  if (0x20 < local_cc0) {
    puVar19 = local_c20 + 2;
  }
  *puVar19 = 0;
                    /* try { // try from 00b93d74 to 00b93d78 has its CatchHandler @ 00b9a755 */
  uVar9 = CEGUI::Window::recursiveChildSearch(pSVar11);
  *(undefined8 *)(this + 0x9158) = uVar9;
                    /* try { // try from 00b93d84 to 00b93df0 has its CatchHandler @ 00b9a724 */
  CEGUI::String::~String((String *)&local_cc8);
  local_d70 = 0x20;
  local_d68 = 0;
  local_d58 = 0;
  local_d60 = 0;
  local_cd0 = (undefined4 *)0x0;
  local_d78 = 0;
  local_d50[0] = 0;
  CEGUI::String::grow((ulong)&local_d78);
  puVar19 = local_d50;
  if (0x20 < local_d70) {
    puVar19 = local_cd0;
  }
  *puVar19 = 0x48;
  puVar19[1] = 0x50;
  puVar19 = local_d48;
  local_d78 = 2;
  if (0x20 < local_d70) {
    puVar19 = local_cd0 + 2;
  }
  *puVar19 = 0;
                    /* try { // try from 00b93e48 to 00b93e4c has its CatchHandler @ 00b9a765 */
  uVar9 = CEGUI::Window::recursiveChildSearch(pSVar11);
  *(undefined8 *)(this + 0x9150) = uVar9;
                    /* try { // try from 00b93e58 to 00b93ec4 has its CatchHandler @ 00b9a724 */
  CEGUI::String::~String((String *)&local_d78);
  local_e20 = 0x20;
  local_e18 = 0;
  local_e08 = 0;
  local_e10 = 0;
  local_d80 = (undefined4 *)0x0;
  local_e28 = 0;
  local_e00[0] = 0;
  CEGUI::String::grow((ulong)&local_e28);
  puVar19 = local_e00;
  if (0x20 < local_e20) {
    puVar19 = local_d80;
  }
  *puVar19 = 0x4d;
  puVar19[1] = 0x61;
  puVar19[2] = 0x6e;
  puVar19[3] = 0x61;
  puVar19 = local_df0;
  local_e28 = 4;
  if (0x20 < local_e20) {
    puVar19 = local_d80 + 4;
  }
  *puVar19 = 0;
                    /* try { // try from 00b93f2a to 00b93f2e has its CatchHandler @ 00b9a775 */
  uVar9 = CEGUI::Window::recursiveChildSearch(pSVar11);
  *(undefined8 *)(this + 0x9148) = uVar9;
                    /* try { // try from 00b93f3a to 00b93fa6 has its CatchHandler @ 00b9a724 */
  CEGUI::String::~String((String *)&local_e28);
  local_ed0 = 0x20;
  local_ec8 = 0;
  local_eb8 = 0;
  local_ec0 = 0;
  local_e30 = (uint *)0x0;
  local_ed8 = 0;
  local_eb0[0] = 0;
  CEGUI::String::grow((ulong)&local_ed8);
  puVar18 = local_eb0;
  if (0x20 < local_ed0) {
    puVar18 = local_e30;
  }
  pcVar10 = "MeleeDamage";
  do {
    bVar2 = *pcVar10;
    pcVar10 = pcVar10 + 1;
    *puVar18 = (uint)bVar2;
    puVar18 = puVar18 + 1;
  } while ((byte *)pcVar10 != (byte *)0xff052c);
  local_ed8 = 0xb;
  puVar18 = local_e84;
  if (0x20 < local_ed0) {
    puVar18 = local_e30 + 0xb;
  }
  *puVar18 = 0;
                    /* try { // try from 00b94010 to 00b94014 has its CatchHandler @ 00b9a785 */
  uVar9 = CEGUI::Window::recursiveChildSearch(pSVar11);
  *(undefined8 *)(this + 0x9128) = uVar9;
                    /* try { // try from 00b94020 to 00b9408c has its CatchHandler @ 00b9a724 */
  CEGUI::String::~String((String *)&local_ed8);
  local_f80 = 0x20;
  local_f78 = 0;
  local_f68 = 0;
  local_f70 = 0;
  local_ee0 = (uint *)0x0;
  local_f88 = 0;
  local_f60[0] = 0;
  CEGUI::String::grow((ulong)&local_f88);
  puVar18 = local_f60;
  if (0x20 < local_f80) {
    puVar18 = local_ee0;
  }
  pcVar10 = "RangedDamage";
  do {
    bVar2 = *pcVar10;
    pcVar10 = pcVar10 + 1;
    *puVar18 = (uint)bVar2;
    puVar18 = puVar18 + 1;
  } while ((byte *)pcVar10 != (byte *)0xff0520);
  local_f88 = 0xc;
  puVar18 = local_f30;
  if (0x20 < local_f80) {
    puVar18 = local_ee0 + 0xc;
  }
  *puVar18 = 0;
                    /* try { // try from 00b940f8 to 00b940fc has its CatchHandler @ 00b9a795 */
  uVar9 = CEGUI::Window::recursiveChildSearch(pSVar11);
  *(undefined8 *)(this + 0x9130) = uVar9;
                    /* try { // try from 00b94108 to 00b94174 has its CatchHandler @ 00b9a724 */
  CEGUI::String::~String((String *)&local_f88);
  local_1030 = 0x20;
  local_1028 = 0;
  local_1018 = 0;
  local_1020 = 0;
  local_f90 = (uint *)0x0;
  local_1038 = 0;
  local_1010[0] = 0;
  CEGUI::String::grow((ulong)&local_1038);
  puVar18 = local_1010;
  if (0x20 < local_1030) {
    puVar18 = local_f90;
  }
  pcVar10 = "MagicDamage";
  do {
    bVar2 = *pcVar10;
    pcVar10 = pcVar10 + 1;
    *puVar18 = (uint)bVar2;
    puVar18 = puVar18 + 1;
  } while ((byte *)pcVar10 != (byte *)0xff0513);
  local_1038 = 0xb;
  puVar18 = local_fe4;
  if (0x20 < local_1030) {
    puVar18 = local_f90 + 0xb;
  }
  *puVar18 = 0;
                    /* try { // try from 00b941e0 to 00b941e4 has its CatchHandler @ 00b9a7a5 */
  uVar9 = CEGUI::Window::recursiveChildSearch(pSVar11);
  *(undefined8 *)(this + 0x9138) = uVar9;
                    /* try { // try from 00b941f0 to 00b9425c has its CatchHandler @ 00b9a724 */
  CEGUI::String::~String((String *)&local_1038);
  local_10e0 = 0x20;
  local_10d8 = 0;
  local_10c8 = 0;
  local_10d0 = 0;
  local_1040 = (uint *)0x0;
  local_10e8 = 0;
  local_10c0[0] = 0;
  CEGUI::String::grow((ulong)&local_10e8);
  puVar18 = local_10c0;
  if (0x20 < local_10e0) {
    puVar18 = local_1040;
  }
  pbVar12 = (byte *)0xff187d;
  do {
    bVar2 = *pbVar12;
    pbVar12 = pbVar12 + 1;
    *puVar18 = (uint)bVar2;
    puVar18 = puVar18 + 1;
  } while (pbVar12 != (byte *)0xff1884);
  local_10e8 = 7;
  puVar18 = local_10a4;
  if (0x20 < local_10e0) {
    puVar18 = local_1040 + 7;
  }
  *puVar18 = 0;
                    /* try { // try from 00b942c8 to 00b942cc has its CatchHandler @ 00b9a7b5 */
  uVar9 = CEGUI::Window::recursiveChildSearch(pSVar11);
  *(undefined8 *)(this + 0x9140) = uVar9;
                    /* try { // try from 00b942d8 to 00b94344 has its CatchHandler @ 00b9a724 */
  CEGUI::String::~String((String *)&local_10e8);
  local_1190 = 0x20;
  local_1188 = 0;
  local_1178 = 0;
  local_1180 = 0;
  local_10f0 = (uint *)0x0;
  local_1198 = 0;
  local_1170[0] = 0;
  CEGUI::String::grow((ulong)&local_1198);
  puVar18 = local_1170;
  if (0x20 < local_1190) {
    puVar18 = local_10f0;
  }
  pbVar12 = (byte *)0xfe4a28;
  do {
    bVar2 = *pbVar12;
    pbVar12 = pbVar12 + 1;
    *puVar18 = (uint)bVar2;
    puVar18 = puVar18 + 1;
  } while (pbVar12 != (byte *)0xfe4a2f);
  local_1198 = 7;
  puVar18 = local_1154;
  if (0x20 < local_1190) {
    puVar18 = local_10f0 + 7;
  }
  *puVar18 = 0;
                    /* try { // try from 00b943b0 to 00b943b4 has its CatchHandler @ 00b9a7ca */
  pSVar13 = (String *)CEGUI::Window::recursiveChildSearch(pSVar11);
                    /* try { // try from 00b943bb to 00b94443 has its CatchHandler @ 00b9a724 */
  CEGUI::String::~String((String *)&local_1198);
  CEGUI::Window::removeChildWindow(*(Window **)(pSVar13 + 0xb0));
  CEGUI::Window::addChildWindow(*(Window **)(this + 0x20));
  local_12f0 = 0x20;
  local_12e8 = 0;
  local_12d8 = 0;
  local_12e0 = 0;
  local_1250 = (uint *)0x0;
  local_12f8 = 0;
  local_12d0[0] = 0;
  CEGUI::String::grow((ulong)&local_12f8);
  puVar18 = local_12d0;
  if (0x20 < local_12f0) {
    puVar18 = local_1250;
  }
  pcVar10 = "False";
  do {
    bVar2 = *pcVar10;
    pcVar10 = pcVar10 + 1;
    *puVar18 = (uint)bVar2;
    puVar18 = puVar18 + 1;
  } while ((byte *)pcVar10 != (byte *)0xfe603f);
  local_12f8 = 5;
  puVar18 = local_12bc;
  if (0x20 < local_12f0) {
    puVar18 = local_1250 + 5;
  }
  *puVar18 = 0;
  local_1240 = 0x20;
  local_1238 = 0;
  local_1228 = 0;
  local_1230 = 0;
  local_11a0 = (uint *)0x0;
  local_1248 = 0;
  local_1220[0] = 0;
                    /* try { // try from 00b94505 to 00b94509 has its CatchHandler @ 00b9a7da */
  CEGUI::String::grow((ulong)&local_1248);
  puVar18 = local_1220;
  if (0x20 < local_1240) {
    puVar18 = local_11a0;
  }
  pcVar10 = "RiseOnClick";
  do {
    bVar2 = *pcVar10;
    pcVar10 = pcVar10 + 1;
    *puVar18 = (uint)bVar2;
    puVar18 = puVar18 + 1;
  } while ((byte *)pcVar10 != (byte *)0xfe6039);
  local_1248 = 0xb;
  puVar18 = local_11f4;
  if (0x20 < local_1240) {
    puVar18 = local_11a0 + 0xb;
  }
  *puVar18 = 0;
                    /* try { // try from 00b94578 to 00b9457c has its CatchHandler @ 00b9a7ea */
  CEGUI::PropertySet::setProperty(pSVar13,(String *)&local_1248);
                    /* try { // try from 00b94580 to 00b94584 has its CatchHandler @ 00b9a7da */
  CEGUI::String::~String((String *)&local_1248);
                    /* try { // try from 00b94588 to 00b94606 has its CatchHandler @ 00b9a724 */
  CEGUI::String::~String((String *)&local_12f8);
  CEGUI::Window::moveToBack();
  CEGUI::Window::setZOrderingEnabled(SUB81(pSVar13,0));
  local_13a0 = 0x20;
  local_1398 = 0;
  local_1388 = 0;
  local_1390 = 0;
  local_1300 = (uint *)0x0;
  local_13a8 = 0;
  local_1380[0] = 0;
  CEGUI::String::grow((ulong)&local_13a8);
  puVar18 = local_1380;
  if (0x20 < local_13a0) {
    puVar18 = local_1300;
  }
  pcVar10 = "BottomFrame";
  do {
    bVar2 = *pcVar10;
    pcVar10 = pcVar10 + 1;
    *puVar18 = (uint)bVar2;
    puVar18 = puVar18 + 1;
  } while ((byte *)pcVar10 != (byte *)0xfef825);
  local_13a8 = 0xb;
  puVar18 = local_1354;
  if (0x20 < local_13a0) {
    puVar18 = local_1300 + 0xb;
  }
  *puVar18 = 0;
                    /* try { // try from 00b94670 to 00b94674 has its CatchHandler @ 00b9a7f7 */
  uVar9 = CEGUI::Window::recursiveChildSearch(pSVar11);
  *(undefined8 *)(this + 0x48) = uVar9;
                    /* try { // try from 00b9467d to 00b94709 has its CatchHandler @ 00b9a724 */
  CEGUI::String::~String((String *)&local_13a8);
  CEGUI::Window::removeChildWindow(*(Window **)(*(long *)(this + 0x48) + 0xb0));
  CEGUI::Window::addChildWindow(*(Window **)(this + 0x20));
  local_1500 = 0x20;
  local_14f8 = 0;
  local_14e8 = 0;
  local_14f0 = 0;
  local_1460 = (uint *)0x0;
  local_1508 = 0;
  local_14e0[0] = 0;
  CEGUI::String::grow((ulong)&local_1508);
  puVar18 = local_14e0;
  if (0x20 < local_1500) {
    puVar18 = local_1460;
  }
  pcVar10 = "False";
  do {
    bVar2 = *pcVar10;
    pcVar10 = pcVar10 + 1;
    *puVar18 = (uint)bVar2;
    puVar18 = puVar18 + 1;
  } while ((byte *)pcVar10 != (byte *)0xfe603f);
  local_1508 = 5;
  puVar18 = local_14cc;
  if (0x20 < local_1500) {
    puVar18 = local_1460 + 5;
  }
  *puVar18 = 0;
  local_1450 = 0x20;
  local_1448 = 0;
  local_1438 = 0;
  local_1440 = 0;
  local_13b0 = (uint *)0x0;
  local_1458 = 0;
  local_1430[0] = 0;
                    /* try { // try from 00b947d5 to 00b947d9 has its CatchHandler @ 00b9a7fc */
  CEGUI::String::grow((ulong)&local_1458);
  puVar18 = local_1430;
  if (0x20 < local_1450) {
    puVar18 = local_13b0;
  }
  pcVar10 = "RiseOnClick";
  do {
    bVar2 = *pcVar10;
    pcVar10 = pcVar10 + 1;
    *puVar18 = (uint)bVar2;
    puVar18 = puVar18 + 1;
  } while ((byte *)pcVar10 != (byte *)0xfe6039);
  local_1458 = 0xb;
  puVar18 = local_1404;
  if (0x20 < local_1450) {
    puVar18 = local_13b0 + 0xb;
  }
  *puVar18 = 0;
                    /* try { // try from 00b9484a to 00b9484e has its CatchHandler @ 00b9a9f5 */
  CEGUI::PropertySet::setProperty(*(String **)(this + 0x48),(String *)&local_1458);
                    /* try { // try from 00b94852 to 00b94856 has its CatchHandler @ 00b9a7fc */
  CEGUI::String::~String((String *)&local_1458);
                    /* try { // try from 00b9485a to 00b948dc has its CatchHandler @ 00b9a724 */
  CEGUI::String::~String((String *)&local_1508);
  CEGUI::Window::moveToFront();
  CEGUI::Window::setZOrderingEnabled(SUB81(*(undefined8 *)(this + 0x48),0));
  local_15b0 = 0x20;
  local_15a8 = 0;
  local_1598 = 0;
  local_15a0 = 0;
  local_1510 = (uint *)0x0;
  local_15b8 = 0;
  local_1590[0] = 0;
  CEGUI::String::grow((ulong)&local_15b8);
  puVar18 = local_1590;
  if (0x20 < local_15b0) {
    puVar18 = local_1510;
  }
  pcVar10 = "TopFrame";
  do {
    bVar2 = *pcVar10;
    pcVar10 = pcVar10 + 1;
    *puVar18 = (uint)bVar2;
    puVar18 = puVar18 + 1;
  } while ((byte *)pcVar10 != (byte *)0xfef819);
  local_15b8 = 8;
  puVar18 = local_1570;
  if (0x20 < local_15b0) {
    puVar18 = local_1510 + 8;
  }
  *puVar18 = 0;
                    /* try { // try from 00b94948 to 00b9494c has its CatchHandler @ 00b9aa0a */
  uVar9 = CEGUI::Window::recursiveChildSearch(pSVar11);
  *(undefined8 *)(this + 0x28) = uVar9;
                    /* try { // try from 00b94955 to 00b949e1 has its CatchHandler @ 00b9a724 */
  CEGUI::String::~String((String *)&local_15b8);
  CEGUI::Window::removeChildWindow(*(Window **)(*(long *)(this + 0x28) + 0xb0));
  CEGUI::Window::addChildWindow(*(Window **)(this + 0x20));
  local_1710 = 0x20;
  local_1708 = 0;
  local_16f8 = 0;
  local_1700 = 0;
  local_1670 = (uint *)0x0;
  local_1718 = 0;
  local_16f0[0] = 0;
  CEGUI::String::grow((ulong)&local_1718);
  puVar18 = local_16f0;
  if (0x20 < local_1710) {
    puVar18 = local_1670;
  }
  pcVar10 = "False";
  do {
    bVar2 = *pcVar10;
    pcVar10 = pcVar10 + 1;
    *puVar18 = (uint)bVar2;
    puVar18 = puVar18 + 1;
  } while ((byte *)pcVar10 != (byte *)0xfe603f);
  local_1718 = 5;
  puVar18 = local_16dc;
  if (0x20 < local_1710) {
    puVar18 = local_1670 + 5;
  }
  *puVar18 = 0;
  local_1660 = 0x20;
  local_1658 = 0;
  local_1648 = 0;
  local_1650 = 0;
  local_15c0 = (uint *)0x0;
  local_1668 = 0;
  local_1640[0] = 0;
                    /* try { // try from 00b94aa5 to 00b94aa9 has its CatchHandler @ 00b9aa0f */
  CEGUI::String::grow((ulong)&local_1668);
  puVar18 = local_1640;
  if (0x20 < local_1660) {
    puVar18 = local_15c0;
  }
  pcVar10 = "RiseOnClick";
  do {
    bVar2 = *pcVar10;
    pcVar10 = pcVar10 + 1;
    *puVar18 = (uint)bVar2;
    puVar18 = puVar18 + 1;
  } while ((byte *)pcVar10 != (byte *)0xfe6039);
  local_1668 = 0xb;
  puVar18 = local_1614;
  if (0x20 < local_1660) {
    puVar18 = local_15c0 + 0xb;
  }
  *puVar18 = 0;
                    /* try { // try from 00b94b1a to 00b94b1e has its CatchHandler @ 00b9aa15 */
  CEGUI::PropertySet::setProperty(*(String **)(this + 0x28),(String *)&local_1668);
                    /* try { // try from 00b94b22 to 00b94b26 has its CatchHandler @ 00b9aa0f */
  CEGUI::String::~String((String *)&local_1668);
                    /* try { // try from 00b94b2a to 00b94ba9 has its CatchHandler @ 00b9a724 */
  CEGUI::String::~String((String *)&local_1718);
  CEGUI::Window::moveToFront();
  CEGUI::Window::setZOrderingEnabled(SUB81(*(undefined8 *)(this + 0x28),0));
  local_1920 = 0x20;
  local_1918 = 0;
  local_1908 = 0;
  local_1910 = 0;
  local_1880 = (undefined4 *)0x0;
  local_1928 = 0;
  local_1900[0] = 0;
  CEGUI::String::grow((ulong)&local_1928);
  local_1928 = 0;
  puVar19 = local_1900;
  if (0x20 < local_1920) {
    puVar19 = local_1880;
  }
  *puVar19 = 0;
                    /* try { // try from 00b94be3 to 00b94be7 has its CatchHandler @ 00b9a975 */
  CEGUI::String::String(local_1878,(uchar *)"PSockets");
                    /* try { // try from 00b94bf8 to 00b94bfc has its CatchHandler @ 00b9a985 */
  CEGUI::String::String(local_17c8,(uchar *)"DefaultWindow");
                    /* try { // try from 00b94c0d to 00b94c11 has its CatchHandler @ 00b9a995 */
  uVar9 = CEGUI::WindowManager::createWindow
                    (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,local_17c8,local_1878);
  *(undefined8 *)(this + 0x30) = uVar9;
                    /* try { // try from 00b94c1a to 00b94c1e has its CatchHandler @ 00b9a985 */
  CEGUI::String::~String(local_17c8);
                    /* try { // try from 00b94c22 to 00b94c26 has its CatchHandler @ 00b9a975 */
  CEGUI::String::~String(local_1878);
                    /* try { // try from 00b94c2a to 00b94c52 has its CatchHandler @ 00b9a724 */
  CEGUI::String::~String((String *)&local_1928);
  CEGUI::Window::addChildWindow(*(Window **)(this + 0x28));
  CEGUI::Window::getSize();
                    /* try { // try from 00b94c5b to 00b94c5f has its CatchHandler @ 00b9a9a5 */
  CEGUI::Window::setSize(*(UVector2 **)(this + 0x30));
  local_1a80 = 0x20;
  local_1a78 = 0;
  local_1a68 = 0;
  local_1a70 = 0;
  local_19e0 = (uint *)0x0;
  local_1a88 = 0;
  local_1a60[0] = 0;
                    /* try { // try from 00b94cc3 to 00b94cc7 has its CatchHandler @ 00b9a724 */
  CEGUI::String::grow((ulong)&local_1a88);
  puVar18 = local_1a60;
  if (0x20 < local_1a80) {
    puVar18 = local_19e0;
  }
  pcVar10 = "False";
  do {
    bVar2 = *pcVar10;
    pcVar10 = pcVar10 + 1;
    *puVar18 = (uint)bVar2;
    puVar18 = puVar18 + 1;
  } while ((byte *)pcVar10 != (byte *)0xfe603f);
  local_1a88 = 5;
  puVar18 = local_1a4c;
  if (0x20 < local_1a80) {
    puVar18 = local_19e0 + 5;
  }
  *puVar18 = 0;
  local_19d0 = 0x20;
  local_19c8 = 0;
  local_19b8 = 0;
  local_19c0 = 0;
  local_1930 = (uint *)0x0;
  local_19d8 = 0;
  local_19b0[0] = 0;
                    /* try { // try from 00b94d8d to 00b94d91 has its CatchHandler @ 00b9a9b5 */
  CEGUI::String::grow((ulong)&local_19d8);
  puVar18 = local_19b0;
  if (0x20 < local_19d0) {
    puVar18 = local_1930;
  }
  pcVar10 = "RiseOnClick";
  do {
    bVar2 = *pcVar10;
    pcVar10 = pcVar10 + 1;
    *puVar18 = (uint)bVar2;
    puVar18 = puVar18 + 1;
  } while ((byte *)pcVar10 != (byte *)0xfe6039);
  local_19d8 = 0xb;
  puVar18 = local_1984;
  if (0x20 < local_19d0) {
    puVar18 = local_1930 + 0xb;
  }
  *puVar18 = 0;
                    /* try { // try from 00b94dfa to 00b94dfe has its CatchHandler @ 00b9a9c5 */
  CEGUI::PropertySet::setProperty(*(String **)(this + 0x30),(String *)&local_19d8);
                    /* try { // try from 00b94e02 to 00b94e06 has its CatchHandler @ 00b9a9b5 */
  CEGUI::String::~String((String *)&local_19d8);
                    /* try { // try from 00b94e0a to 00b94e0e has its CatchHandler @ 00b9a724 */
  CEGUI::String::~String((String *)&local_1a88);
  local_364 = 0;
  local_368 = 0;
  local_35c = 0;
  local_360 = 0;
                    /* try { // try from 00b94e48 to 00b94e4c has its CatchHandler @ 00b9a9d5 */
  CEGUI::Window::setPosition(*(UVector2 **)(this + 0x30));
  *(undefined1 *)(*(long *)(this + 0x30) + 0x3e2) = 1;
                    /* try { // try from 00b94e5e to 00b94ec7 has its CatchHandler @ 00b9a724 */
  CEGUI::Window::moveToFront();
  local_1c90 = 0x20;
  local_1c88 = 0;
  local_1c78 = 0;
  local_1c80 = 0;
  local_1bf0 = (undefined4 *)0x0;
  local_1c98 = 0;
  local_1c70[0] = 0;
  CEGUI::String::grow((ulong)&local_1c98);
  local_1c98 = 0;
  puVar19 = local_1c70;
  if (0x20 < local_1c90) {
    puVar19 = local_1bf0;
  }
  *puVar19 = 0;
                    /* try { // try from 00b94f01 to 00b94f05 has its CatchHandler @ 00b9a9e5 */
  CEGUI::String::String(local_1be8,(uchar *)"PSocketsO");
                    /* try { // try from 00b94f16 to 00b94f1a has its CatchHandler @ 00b9a8cd */
  CEGUI::String::String(local_1b38,(uchar *)"DefaultWindow");
                    /* try { // try from 00b94f2b to 00b94f2f has its CatchHandler @ 00b9a8dd */
  uVar9 = CEGUI::WindowManager::createWindow
                    (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,local_1b38,local_1be8);
  *(undefined8 *)(this + 0x40) = uVar9;
                    /* try { // try from 00b94f38 to 00b94f3c has its CatchHandler @ 00b9a8cd */
  CEGUI::String::~String(local_1b38);
                    /* try { // try from 00b94f40 to 00b94f44 has its CatchHandler @ 00b9a9e5 */
  CEGUI::String::~String(local_1be8);
                    /* try { // try from 00b94f48 to 00b94f70 has its CatchHandler @ 00b9a724 */
  CEGUI::String::~String((String *)&local_1c98);
  CEGUI::Window::addChildWindow(*(Window **)(this + 0x28));
  CEGUI::Window::getSize();
                    /* try { // try from 00b94f79 to 00b94f7d has its CatchHandler @ 00b9a8ea */
  CEGUI::Window::setSize(*(UVector2 **)(this + 0x40));
  local_1df0 = 0x20;
  local_1de8 = 0;
  local_1dd8 = 0;
  local_1de0 = 0;
  local_1d50 = (uint *)0x0;
  local_1df8 = 0;
  local_1dd0[0] = 0;
                    /* try { // try from 00b94fe1 to 00b94fe5 has its CatchHandler @ 00b9a724 */
  CEGUI::String::grow((ulong)&local_1df8);
  puVar18 = local_1dd0;
  if (0x20 < local_1df0) {
    puVar18 = local_1d50;
  }
  pcVar10 = "False";
  do {
    bVar2 = *pcVar10;
    pcVar10 = pcVar10 + 1;
    *puVar18 = (uint)bVar2;
    puVar18 = puVar18 + 1;
  } while ((byte *)pcVar10 != (byte *)0xfe603f);
  local_1df8 = 5;
  puVar18 = local_1dbc;
  if (0x20 < local_1df0) {
    puVar18 = local_1d50 + 5;
  }
  *puVar18 = 0;
  local_1d40 = 0x20;
  local_1d38 = 0;
  local_1d28 = 0;
  local_1d30 = 0;
  local_1ca0 = (uint *)0x0;
  local_1d48 = 0;
  local_1d20[0] = 0;
                    /* try { // try from 00b950ad to 00b950b1 has its CatchHandler @ 00b9a8ef */
  CEGUI::String::grow((ulong)&local_1d48);
  puVar18 = local_1d20;
  if (0x20 < local_1d40) {
    puVar18 = local_1ca0;
  }
  pcVar10 = "RiseOnClick";
  do {
    bVar2 = *pcVar10;
    pcVar10 = pcVar10 + 1;
    *puVar18 = (uint)bVar2;
    puVar18 = puVar18 + 1;
  } while ((byte *)pcVar10 != (byte *)0xfe6039);
  local_1d48 = 0xb;
  puVar18 = local_1cf4;
  if (0x20 < local_1d40) {
    puVar18 = local_1ca0 + 0xb;
  }
  *puVar18 = 0;
                    /* try { // try from 00b9511a to 00b9511e has its CatchHandler @ 00b9a8f5 */
  CEGUI::PropertySet::setProperty(*(String **)(this + 0x40),(String *)&local_1d48);
                    /* try { // try from 00b95122 to 00b95126 has its CatchHandler @ 00b9a8ef */
  CEGUI::String::~String((String *)&local_1d48);
                    /* try { // try from 00b9512a to 00b9512e has its CatchHandler @ 00b9a724 */
  CEGUI::String::~String((String *)&local_1df8);
  local_384 = 0;
  local_388 = 0;
  local_37c = 0;
  local_380 = 0;
                    /* try { // try from 00b95168 to 00b9516c has its CatchHandler @ 00b9a90a */
  CEGUI::Window::setPosition(*(UVector2 **)(this + 0x40));
  *(undefined1 *)(*(long *)(this + 0x40) + 0x3e2) = 1;
                    /* try { // try from 00b9517e to 00b951e7 has its CatchHandler @ 00b9a724 */
  CEGUI::Window::moveToFront();
  local_2000 = 0x20;
  local_1ff8 = 0;
  local_1fe8 = 0;
  local_1ff0 = 0;
  local_1f60 = (undefined4 *)0x0;
  local_2008 = 0;
  local_1fe0[0] = 0;
  CEGUI::String::grow((ulong)&local_2008);
  local_2008 = 0;
  puVar19 = local_1fe0;
  if (0x20 < local_2000) {
    puVar19 = local_1f60;
  }
  *puVar19 = 0;
                    /* try { // try from 00b95221 to 00b95225 has its CatchHandler @ 00b9a90f */
  CEGUI::String::String(local_1f58,(uchar *)"PIcons");
                    /* try { // try from 00b95236 to 00b9523a has its CatchHandler @ 00b9a915 */
  CEGUI::String::String(local_1ea8,(uchar *)"DefaultWindow");
                    /* try { // try from 00b9524b to 00b9524f has its CatchHandler @ 00b9a922 */
  uVar9 = CEGUI::WindowManager::createWindow
                    (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,local_1ea8,local_1f58);
  *(undefined8 *)(this + 0x38) = uVar9;
                    /* try { // try from 00b95258 to 00b9525c has its CatchHandler @ 00b9a915 */
  CEGUI::String::~String(local_1ea8);
                    /* try { // try from 00b95260 to 00b95264 has its CatchHandler @ 00b9a90f */
  CEGUI::String::~String(local_1f58);
                    /* try { // try from 00b95268 to 00b95290 has its CatchHandler @ 00b9a724 */
  CEGUI::String::~String((String *)&local_2008);
  CEGUI::Window::addChildWindow(*(Window **)(this + 0x28));
  CEGUI::Window::getSize();
                    /* try { // try from 00b95299 to 00b9529d has its CatchHandler @ 00b9a924 */
  CEGUI::Window::setSize(*(UVector2 **)(this + 0x38));
  local_2160 = 0x20;
  local_2158 = 0;
  local_2148 = 0;
  local_2150 = 0;
  local_20c0 = (uint *)0x0;
  local_2168 = 0;
  local_2140[0] = 0;
                    /* try { // try from 00b95301 to 00b95305 has its CatchHandler @ 00b9a724 */
  CEGUI::String::grow((ulong)&local_2168);
  puVar18 = local_2140;
  if (0x20 < local_2160) {
    puVar18 = local_20c0;
  }
  pcVar10 = "False";
  do {
    bVar2 = *pcVar10;
    pcVar10 = pcVar10 + 1;
    *puVar18 = (uint)bVar2;
    puVar18 = puVar18 + 1;
  } while ((byte *)pcVar10 != (byte *)0xfe603f);
  local_2168 = 5;
  puVar18 = local_212c;
  if (0x20 < local_2160) {
    puVar18 = local_20c0 + 5;
  }
  *puVar18 = 0;
  local_20b0 = 0x20;
  local_20a8 = 0;
  local_2098 = 0;
  local_20a0 = 0;
  local_2010 = (uint *)0x0;
  local_20b8 = 0;
  local_2090[0] = 0;
                    /* try { // try from 00b953cf to 00b953d3 has its CatchHandler @ 00b9a929 */
  CEGUI::String::grow((ulong)&local_20b8);
  puVar18 = local_2090;
  if (0x20 < local_20b0) {
    puVar18 = local_2010;
  }
  pcVar10 = "RiseOnClick";
  do {
    bVar2 = *pcVar10;
    pcVar10 = pcVar10 + 1;
    *puVar18 = (uint)bVar2;
    puVar18 = puVar18 + 1;
  } while ((byte *)pcVar10 != (byte *)0xfe6039);
  local_20b8 = 0xb;
  puVar18 = local_2064;
  if (0x20 < local_20b0) {
    puVar18 = local_2010 + 0xb;
  }
  *puVar18 = 0;
                    /* try { // try from 00b9543a to 00b9543e has its CatchHandler @ 00b9a935 */
  CEGUI::PropertySet::setProperty(*(String **)(this + 0x38),(String *)&local_20b8);
                    /* try { // try from 00b95442 to 00b95446 has its CatchHandler @ 00b9a929 */
  CEGUI::String::~String((String *)&local_20b8);
                    /* try { // try from 00b9544a to 00b9544e has its CatchHandler @ 00b9a724 */
  CEGUI::String::~String((String *)&local_2168);
  local_3a4 = 0;
  local_3a8 = 0;
  local_39c = 0;
  local_3a0 = 0;
                    /* try { // try from 00b95488 to 00b9548c has its CatchHandler @ 00b9a942 */
  CEGUI::Window::setPosition(*(UVector2 **)(this + 0x38));
  *(undefined1 *)(*(long *)(this + 0x38) + 0x3e2) = 1;
                    /* try { // try from 00b9549e to 00b9550a has its CatchHandler @ 00b9a724 */
  CEGUI::Window::moveToFront();
  local_2210 = 0x20;
  local_2208 = 0;
  local_21f8 = 0;
  local_2200 = 0;
  local_2170 = (uint *)0x0;
  local_2218 = 0;
  local_21f0[0] = 0;
  CEGUI::String::grow((ulong)&local_2218);
  puVar18 = local_21f0;
  if (0x20 < local_2210) {
    puVar18 = local_2170;
  }
  pcVar10 = "SlotGlow";
  do {
    bVar2 = *pcVar10;
    pcVar10 = pcVar10 + 1;
    *puVar18 = (uint)bVar2;
    puVar18 = puVar18 + 1;
  } while ((byte *)pcVar10 != (byte *)0xfef810);
  local_2218 = 8;
  puVar18 = local_21d0;
  if (0x20 < local_2210) {
    puVar18 = local_2170 + 8;
  }
  *puVar18 = 0;
                    /* try { // try from 00b9557a to 00b9557e has its CatchHandler @ 00b9a947 */
  uVar9 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x28));
  *(undefined8 *)(this + 0x9110) = uVar9;
                    /* try { // try from 00b9558a to 00b9563e has its CatchHandler @ 00b9a724 */
  CEGUI::String::~String((String *)&local_2218);
  CEGUI::EventSet::setMutedState((bool)((char)*(undefined8 *)(this + 0x9110) + '8'));
  *(undefined1 *)(*(long *)(this + 0x9110) + 0x3e2) = 1;
  *(undefined1 *)(*(long *)(this + 0x9110) + 0x213) = 0;
  CEGUI::Window::removeChildWindow(*(Window **)(*(long *)(this + 0x9110) + 0xb0));
  local_22c0 = 0x20;
  local_22b8 = 0;
  local_22a8 = 0;
  local_22b0 = 0;
  local_2220 = (uint *)0x0;
  local_22c8 = 0;
  local_22a0[0] = 0;
  CEGUI::String::grow((ulong)&local_22c8);
  puVar18 = local_22a0;
  if (0x20 < local_22c0) {
    puVar18 = local_2220;
  }
  pcVar10 = "Close";
  do {
    bVar2 = *pcVar10;
    pcVar10 = pcVar10 + 1;
    *puVar18 = (uint)bVar2;
    puVar18 = puVar18 + 1;
  } while ((byte *)pcVar10 != (byte *)0xfef807);
  local_22c8 = 5;
  puVar18 = local_228c;
  if (0x20 < local_22c0) {
    puVar18 = local_2220 + 5;
  }
  *puVar18 = 0;
                    /* try { // try from 00b956aa to 00b956ae has its CatchHandler @ 00b9a955 */
  lVar8 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x28));
                    /* try { // try from 00b956b5 to 00b956da has its CatchHandler @ 00b9a724 */
  CEGUI::String::~String((String *)&local_22c8);
  *(undefined1 *)(lVar8 + 0x213) = 0;
  CEGUI::Window::moveToFront();
  pcVar3 = *(code **)(*(long *)(lVar8 + 0x38) + 0x10);
  local_88[0] = operator_new(0x20);
  *local_88[0] = &PTR__MemberFunctionSlot_00ff0850;
  local_88[0][2] = 0;
  local_88[0][1] = handle_CloseButton;
  local_88[0][3] = this;
                    /* try { // try from 00b9571a to 00b9574f has its CatchHandler @ 00b9a965 */
  (*pcVar3)(&local_3b8,lVar8 + 0x38,CEGUI::Window::EventMouseButtonDown,(SubscriberSlot *)local_88);
  if ((local_3b8 != (BoundSlot *)0x0) &&
     (iVar6 = *local_3b0, *local_3b0 = iVar6 + -1, iVar6 + -1 == 0)) {
    if (local_3b8 != (BoundSlot *)0x0) {
      CEGUI::BoundSlot::~BoundSlot(local_3b8);
      operator_delete(local_3b8);
    }
    operator_delete(local_3b0);
    local_3b8 = (BoundSlot *)0x0;
    local_3b0 = (int *)0x0;
  }
                    /* try { // try from 00b95780 to 00b957ec has its CatchHandler @ 00b9a724 */
  CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_88);
  local_2370 = 0x20;
  local_2368 = 0;
  local_2358 = 0;
  local_2360 = 0;
  local_22d0 = (uint *)0x0;
  local_2378 = 0;
  local_2350[0] = 0;
  CEGUI::String::grow((ulong)&local_2378);
  puVar18 = local_2350;
  if (0x20 < local_2370) {
    puVar18 = local_22d0;
  }
  pcVar10 = "PaperdollEquip";
  do {
    bVar2 = *pcVar10;
    pcVar10 = pcVar10 + 1;
    *puVar18 = (uint)bVar2;
    puVar18 = puVar18 + 1;
  } while ((byte *)pcVar10 != (byte *)0xfef801);
  local_2378 = 0xe;
  puVar18 = local_2318;
  if (0x20 < local_2370) {
    puVar18 = local_22d0 + 0xe;
  }
  *puVar18 = 0;
                    /* try { // try from 00b9585a to 00b9585e has its CatchHandler @ 00b9aa25 */
  lVar8 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x28));
                    /* try { // try from 00b95865 to 00b958a3 has its CatchHandler @ 00b9a724 */
  CEGUI::String::~String((String *)&local_2378);
  CEGUI::Window::moveToFront();
  *(undefined1 *)(lVar8 + 0x213) = 0;
  CEGUI::Window::setWantsMultiClickEvents(SUB81(lVar8,0));
  *(CPetMenu **)(lVar8 + 0x1d8) = this + 0x103c;
  pcVar3 = *(code **)(*(long *)(lVar8 + 0x38) + 0x10);
  local_98[0] = operator_new(0x20);
  *local_98[0] = &PTR__MemberFunctionSlot_00ff0850;
  local_98[0][2] = 0;
  local_98[0][1] = handle_ItemClick;
  local_98[0][3] = this;
                    /* try { // try from 00b958e3 to 00b95918 has its CatchHandler @ 00b9aa35 */
  (*pcVar3)(&local_3c8,lVar8 + 0x38,CEGUI::Window::EventMouseButtonDown,(SubscriberSlot *)local_98);
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
                    /* try { // try from 00b95949 to 00b959b5 has its CatchHandler @ 00b9a724 */
  CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_98);
  local_2420 = 0x20;
  local_2418 = 0;
  local_2408 = 0;
  local_2410 = 0;
  local_2380 = (uint *)0x0;
  local_2428 = 0;
  local_2400[0] = 0;
  CEGUI::String::grow((ulong)&local_2428);
  puVar18 = local_2400;
  if (0x20 < local_2420) {
    puVar18 = local_2380;
  }
  pcVar10 = "RotateLeft";
  do {
    bVar2 = *pcVar10;
    pcVar10 = pcVar10 + 1;
    *puVar18 = (uint)bVar2;
    puVar18 = puVar18 + 1;
  } while ((byte *)pcVar10 != (byte *)0xfef7f2);
  local_2428 = 10;
  puVar18 = local_23d8;
  if (0x20 < local_2420) {
    puVar18 = local_2380 + 10;
  }
  *puVar18 = 0;
                    /* try { // try from 00b95a22 to 00b95a26 has its CatchHandler @ 00b9a712 */
  lVar21 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x28));
                    /* try { // try from 00b95a2d to 00b95a52 has its CatchHandler @ 00b9a724 */
  CEGUI::String::~String((String *)&local_2428);
  *(undefined1 *)(lVar21 + 0x213) = 0;
  CEGUI::Window::moveToFront();
  pcVar3 = *(code **)(*(long *)(lVar21 + 0x38) + 0x10);
  local_a8[0] = operator_new(0x20);
  lVar8 = lVar21 + 0x38;
  *local_a8[0] = &PTR__MemberFunctionSlot_00ff0850;
  local_a8[0][2] = 0;
  local_a8[0][1] = handle_RotateLeft;
  local_a8[0][3] = this;
                    /* try { // try from 00b95a95 to 00b95ac9 has its CatchHandler @ 00b9a717 */
  (*pcVar3)(&local_3d8,lVar8,CEGUI::Window::EventMouseButtonDown,(SubscriberSlot *)local_a8);
  if ((local_3d8 != (BoundSlot *)0x0) &&
     (iVar6 = *local_3d0, *local_3d0 = iVar6 + -1, iVar6 + -1 == 0)) {
    if (local_3d8 != (BoundSlot *)0x0) {
      CEGUI::BoundSlot::~BoundSlot(local_3d8);
      operator_delete(local_3d8);
    }
    operator_delete(local_3d0);
    local_3d8 = (BoundSlot *)0x0;
    local_3d0 = (int *)0x0;
  }
                    /* try { // try from 00b95afa to 00b95b10 has its CatchHandler @ 00b9a724 */
  CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_a8);
  pcVar3 = *(code **)(*(long *)(lVar21 + 0x38) + 0x10);
  local_b8[0] = operator_new(0x20);
  *local_b8[0] = &PTR__MemberFunctionSlot_00ff0850;
  local_b8[0][2] = 0;
  local_b8[0][1] = handle_EndRotateLeft;
  local_b8[0][3] = this;
                    /* try { // try from 00b95b4f to 00b95b83 has its CatchHandler @ 00b9a719 */
  (*pcVar3)(&local_3e8,lVar8,CEGUI::Window::EventMouseButtonUp,(SubscriberSlot *)local_b8);
  if ((local_3e8 != (BoundSlot *)0x0) &&
     (iVar6 = *local_3e0, *local_3e0 = iVar6 + -1, iVar6 + -1 == 0)) {
    if (local_3e8 != (BoundSlot *)0x0) {
      CEGUI::BoundSlot::~BoundSlot(local_3e8);
      operator_delete(local_3e8);
    }
    operator_delete(local_3e0);
    local_3e8 = (BoundSlot *)0x0;
    local_3e0 = (int *)0x0;
  }
                    /* try { // try from 00b95bb4 to 00b95bca has its CatchHandler @ 00b9a724 */
  CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_b8);
  pcVar3 = *(code **)(*(long *)(lVar21 + 0x38) + 0x10);
  local_c8[0] = operator_new(0x20);
  *local_c8[0] = &PTR__MemberFunctionSlot_00ff0850;
  local_c8[0][2] = 0;
  local_c8[0][1] = handle_EndRotateLeft;
  local_c8[0][3] = this;
                    /* try { // try from 00b95c09 to 00b95c3d has its CatchHandler @ 00b9a722 */
  (*pcVar3)(&local_3f8,lVar8,CEGUI::Window::EventMouseLeaves,(SubscriberSlot *)local_c8);
  if ((local_3f8 != (BoundSlot *)0x0) &&
     (iVar6 = *local_3f0, *local_3f0 = iVar6 + -1, iVar6 + -1 == 0)) {
    if (local_3f8 != (BoundSlot *)0x0) {
      CEGUI::BoundSlot::~BoundSlot(local_3f8);
      operator_delete(local_3f8);
    }
    operator_delete(local_3f0);
    local_3f8 = (BoundSlot *)0x0;
    local_3f0 = (int *)0x0;
  }
                    /* try { // try from 00b95c6e to 00b95cda has its CatchHandler @ 00b9a724 */
  CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_c8);
  local_24d0 = 0x20;
  local_24c8 = 0;
  local_24b8 = 0;
  local_24c0 = 0;
  local_2430 = (uint *)0x0;
  local_24d8 = 0;
  local_24b0[0] = 0;
  CEGUI::String::grow((ulong)&local_24d8);
  puVar18 = local_24b0;
  if (0x20 < local_24d0) {
    puVar18 = local_2430;
  }
  pcVar10 = "RotateRight";
  do {
    bVar2 = *pcVar10;
    pcVar10 = pcVar10 + 1;
    *puVar18 = (uint)bVar2;
    puVar18 = puVar18 + 1;
  } while ((byte *)pcVar10 != (byte *)0xfef7e7);
  local_24d8 = 0xb;
  puVar18 = local_2484;
  if (0x20 < local_24d0) {
    puVar18 = local_2430 + 0xb;
  }
  *puVar18 = 0;
                    /* try { // try from 00b95d4a to 00b95d4e has its CatchHandler @ 00b9a62a */
  lVar21 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x28));
                    /* try { // try from 00b95d55 to 00b95d7a has its CatchHandler @ 00b9a724 */
  CEGUI::String::~String((String *)&local_24d8);
  *(undefined1 *)(lVar21 + 0x213) = 0;
  CEGUI::Window::moveToFront();
  pcVar3 = *(code **)(*(long *)(lVar21 + 0x38) + 0x10);
  local_d8[0] = operator_new(0x20);
  lVar8 = lVar21 + 0x38;
  *local_d8[0] = &PTR__MemberFunctionSlot_00ff0850;
  local_d8[0][2] = 0;
  local_d8[0][1] = handle_RotateRight;
  local_d8[0][3] = this;
                    /* try { // try from 00b95dbd to 00b95df1 has its CatchHandler @ 00b9a702 */
  (*pcVar3)(&local_408,lVar8,CEGUI::Window::EventMouseButtonDown,(SubscriberSlot *)local_d8);
  if ((local_408 != (BoundSlot *)0x0) &&
     (iVar6 = *local_400, *local_400 = iVar6 + -1, iVar6 + -1 == 0)) {
    if (local_408 != (BoundSlot *)0x0) {
      CEGUI::BoundSlot::~BoundSlot(local_408);
      operator_delete(local_408);
    }
    operator_delete(local_400);
    local_408 = (BoundSlot *)0x0;
    local_400 = (int *)0x0;
  }
                    /* try { // try from 00b95e22 to 00b95e38 has its CatchHandler @ 00b9a724 */
  CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_d8);
  pcVar3 = *(code **)(*(long *)(lVar21 + 0x38) + 0x10);
  local_e8[0] = operator_new(0x20);
  *local_e8[0] = &PTR__MemberFunctionSlot_00ff0850;
  local_e8[0][2] = 0;
  local_e8[0][1] = handle_EndRotateRight;
  local_e8[0][3] = this;
                    /* try { // try from 00b95e77 to 00b95eab has its CatchHandler @ 00b9a6e2 */
  (*pcVar3)(&local_418,lVar8,CEGUI::Window::EventMouseButtonUp,(SubscriberSlot *)local_e8);
  if ((local_418 != (BoundSlot *)0x0) &&
     (iVar6 = *local_410, *local_410 = iVar6 + -1, iVar6 + -1 == 0)) {
    if (local_418 != (BoundSlot *)0x0) {
      CEGUI::BoundSlot::~BoundSlot(local_418);
      operator_delete(local_418);
    }
    operator_delete(local_410);
    local_418 = (BoundSlot *)0x0;
    local_410 = (int *)0x0;
  }
                    /* try { // try from 00b95edc to 00b95ef2 has its CatchHandler @ 00b9a724 */
  CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_e8);
  pcVar3 = *(code **)(*(long *)(lVar21 + 0x38) + 0x10);
  local_f8[0] = operator_new(0x20);
  *local_f8[0] = &PTR__MemberFunctionSlot_00ff0850;
  local_f8[0][2] = 0;
  local_f8[0][1] = handle_EndRotateRight;
  local_f8[0][3] = this;
                    /* try { // try from 00b95f31 to 00b95f65 has its CatchHandler @ 00b9a6f2 */
  (*pcVar3)(&local_428,lVar8,CEGUI::Window::EventMouseLeaves,(SubscriberSlot *)local_f8);
  if ((local_428 != (BoundSlot *)0x0) &&
     (iVar6 = *local_420, *local_420 = iVar6 + -1, iVar6 + -1 == 0)) {
    if (local_428 != (BoundSlot *)0x0) {
      CEGUI::BoundSlot::~BoundSlot(local_428);
      operator_delete(local_428);
    }
    operator_delete(local_420);
    local_428 = (BoundSlot *)0x0;
    local_420 = (int *)0x0;
  }
                    /* try { // try from 00b95f96 to 00b960bd has its CatchHandler @ 00b9a724 */
  CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_f8);
  plVar26 = &::KEquipmentIconName;
  local_48c4 = 0;
  pCVar20 = this;
  pCVar25 = this;
  do {
    *(undefined8 *)(pCVar20 + 0x1378) = 0;
    *(undefined8 *)(pCVar20 + 0x1898) = 0;
    *(undefined8 *)(pCVar20 + 0x1db8) = 0;
    *(undefined8 *)(pCVar20 + 0x1b28) = 0;
    if (*(long *)(*plVar26 + -0x18) != 0) {
      uVar24 = (ulong)local_48c4;
      local_2580 = 0x20;
      local_2578 = 0;
      local_2568 = 0;
      local_2570 = 0;
      local_24e0 = (undefined4 *)0x0;
      local_2588 = 0;
      local_2560[0] = 0;
      lVar8 = *(long *)(*plVar26 + -0x18);
      CEGUI::String::grow((ulong)&local_2588);
      puVar19 = local_24e0;
      if (local_2580 < 0x21) {
        puVar19 = local_2560;
      }
      puVar19[lVar8] = 0;
      if (lVar8 != 0) {
        lVar21 = lVar8;
        do {
          lVar21 = lVar21 + -1;
          puVar19 = local_2560;
          if (0x20 < local_2580) {
            puVar19 = local_24e0;
          }
          puVar19[lVar21] = (uint)*(byte *)((&::KEquipmentIconName)[uVar24] + lVar21);
        } while (lVar21 != 0);
      }
      local_2588 = lVar8;
                    /* try { // try from 00b96146 to 00b9614a has its CatchHandler @ 00b9a3d7 */
      lVar8 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x28));
                    /* try { // try from 00b96156 to 00b961a2 has its CatchHandler @ 00b9a724 */
      CEGUI::String::~String((String *)&local_2588);
      if (lVar8 != 0) {
        CEGUI::Window::moveToFront();
        *(undefined1 *)(lVar8 + 0x213) = 0;
        CEGUI::Window::setWantsMultiClickEvents(SUB81(lVar8,0));
        *(CPetMenu **)(lVar8 + 0x1d8) = this + uVar24 * 4 + 0xa0;
        pcVar3 = *(code **)(*(long *)(lVar8 + 0x38) + 0x10);
        local_108[0] = operator_new(0x20);
        lVar21 = lVar8 + 0x38;
        *local_108[0] = &PTR__MemberFunctionSlot_00ff0850;
        local_108[0][2] = 0;
        local_108[0][1] = handle_ItemClick;
        local_108[0][3] = this;
                    /* try { // try from 00b961e9 to 00b96224 has its CatchHandler @ 00b9a3ec */
        (*pcVar3)(&local_438,lVar21,CEGUI::Window::EventMouseButtonDown,local_108);
        pBVar5 = local_438;
        if ((local_438 != (BoundSlot *)0x0) &&
           (iVar6 = *local_430, *local_430 = iVar6 + -1, iVar6 + -1 == 0)) {
          if (local_438 != (BoundSlot *)0x0) {
            CEGUI::BoundSlot::~BoundSlot(local_438);
            operator_delete(pBVar5);
          }
          operator_delete(local_430);
          local_438 = (BoundSlot *)0x0;
          local_430 = (int *)0x0;
        }
                    /* try { // try from 00b9625c to 00b96277 has its CatchHandler @ 00b9a724 */
        CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_108);
        pcVar3 = *(code **)(*(long *)(lVar8 + 0x38) + 0x10);
        local_118[0] = operator_new(0x20);
        *local_118[0] = &PTR__MemberFunctionSlot_00ff0850;
        local_118[0][2] = 0;
        local_118[0][1] = handle_MouseOver;
        local_118[0][3] = this;
                    /* try { // try from 00b962b5 to 00b962f0 has its CatchHandler @ 00b9a455 */
        (*pcVar3)(&local_448,lVar21,CEGUI::Window::EventMouseEnters,local_118);
        pBVar5 = local_448;
        if ((local_448 != (BoundSlot *)0x0) &&
           (iVar6 = *local_440, *local_440 = iVar6 + -1, iVar6 + -1 == 0)) {
          if (local_448 != (BoundSlot *)0x0) {
            CEGUI::BoundSlot::~BoundSlot(local_448);
            operator_delete(pBVar5);
          }
          operator_delete(local_440);
          local_448 = (BoundSlot *)0x0;
          local_440 = (int *)0x0;
        }
                    /* try { // try from 00b96328 to 00b96343 has its CatchHandler @ 00b9a724 */
        CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_118);
        pcVar3 = *(code **)(*(long *)(lVar8 + 0x38) + 0x10);
        local_128[0] = operator_new(0x20);
        *local_128[0] = &PTR__MemberFunctionSlot_00ff0850;
        local_128[0][2] = 0;
        local_128[0][1] = handle_MouseOver;
        local_128[0][3] = this;
                    /* try { // try from 00b96381 to 00b963bc has its CatchHandler @ 00b9a46a */
        (*pcVar3)(&local_458,lVar21,CEGUI::Window::EventMouseMove,local_128);
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
                    /* try { // try from 00b963f4 to 00b9640f has its CatchHandler @ 00b9a724 */
        CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_128);
        pcVar3 = *(code **)(*(long *)(lVar8 + 0x38) + 0x10);
        local_138[0] = operator_new(0x20);
        *local_138[0] = &PTR__MemberFunctionSlot_00ff0850;
        local_138[0][2] = 0;
        local_138[0][1] = handle_MouseOut;
        local_138[0][3] = this;
                    /* try { // try from 00b9644d to 00b96488 has its CatchHandler @ 00b9a47f */
        (*pcVar3)(&local_468,lVar21,CEGUI::Window::EventMouseLeaves,local_138);
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
                    /* try { // try from 00b964c0 to 00b96538 has its CatchHandler @ 00b9a724 */
        CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_138);
        CEGUI::Window::moveToFront();
        *(long *)(pCVar20 + 0x1378) = lVar8;
        local_2630 = 0x20;
        local_2628 = 0;
        local_2618 = 0;
        local_2620 = 0;
        local_2590 = (uint *)0x0;
        local_2638 = 0;
        local_2610[0] = 0;
        CEGUI::String::grow((ulong)&local_2638);
        puVar18 = local_2590;
        if (local_2630 < 0x21) {
          puVar18 = local_2610;
        }
        pbVar12 = (byte *)0xfd0c0d;
        do {
          bVar2 = *pbVar12;
          pbVar12 = pbVar12 + 1;
          *puVar18 = (uint)bVar2;
          puVar18 = puVar18 + 1;
        } while (pbVar12 != (byte *)0xfd0c12);
        local_2638 = 5;
        if (local_2630 < 0x21) {
          puVar18 = local_25fc;
        }
        else {
          puVar18 = local_2590 + 5;
        }
        *puVar18 = 0;
                    /* try { // try from 00b965b5 to 00b965b9 has its CatchHandler @ 00b9a494 */
        CEGUI::PropertySet::getProperty((String *)&local_26e8);
        lVar8 = local_26e8;
                    /* try { // try from 00b965e0 to 00b965e4 has its CatchHandler @ 00b9a4a9 */
        CEGUI::String::grow((ulong)(this + uVar24 * 0xb0 + 0x2048));
        *(long *)(pCVar25 + 0x2048) = lVar8;
        if (*(ulong *)(pCVar25 + 0x2050) < 0x21) {
          pCVar15 = this + uVar24 * 0xb0 + 0x2070;
        }
        else {
          pCVar15 = *(CPetMenu **)(pCVar25 + 0x20f0);
        }
        *(undefined4 *)(pCVar15 + lVar8 * 4) = 0;
        if (local_26e0 < 0x21) {
          puVar22 = auStack_26c0;
          if (0x20 < *(ulong *)(pCVar25 + 0x2050)) goto LAB_00b96f7b;
LAB_00b96644:
          pCVar15 = this + uVar24 * 0xb0 + 0x2070;
        }
        else {
          puVar22 = local_2640;
          if (*(ulong *)(pCVar25 + 0x2050) < 0x21) goto LAB_00b96644;
LAB_00b96f7b:
          pCVar15 = *(CPetMenu **)(pCVar25 + 0x20f0);
        }
        memcpy(pCVar15,puVar22,lVar8 << 2);
                    /* try { // try from 00b96667 to 00b9666b has its CatchHandler @ 00b9a494 */
        CEGUI::String::~String((String *)&local_26e8);
                    /* try { // try from 00b96674 to 00b96790 has its CatchHandler @ 00b9a724 */
        CEGUI::String::~String((String *)&local_2638);
        plVar14 = (long *)CEGUI::Window::getTooltipText();
        lVar8 = *plVar14;
        CEGUI::String::grow((ulong)(this + uVar24 * 0xb0 + 0x58a8));
        *(long *)(pCVar25 + 0x58a8) = lVar8;
        if (*(ulong *)(pCVar25 + 0x58b0) < 0x21) {
          pCVar15 = this + uVar24 * 0xb0 + 0x58d0;
        }
        else {
          pCVar15 = *(CPetMenu **)(pCVar25 + 0x5950);
        }
        *(undefined4 *)(pCVar15 + lVar8 * 4) = 0;
        if ((ulong)plVar14[1] < 0x21) {
          plVar14 = plVar14 + 5;
          if (*(ulong *)(pCVar25 + 0x58b0) < 0x21) goto LAB_00b96709;
LAB_00b96f3e:
          pCVar15 = *(CPetMenu **)(pCVar25 + 0x5950);
        }
        else {
          plVar14 = (long *)plVar14[0x15];
          if (0x20 < *(ulong *)(pCVar25 + 0x58b0)) goto LAB_00b96f3e;
LAB_00b96709:
          pCVar15 = this + uVar24 * 0xb0 + 0x58d0;
        }
        memcpy(pCVar15,plVar14,lVar8 << 2);
        *(undefined8 *)(pCVar20 + 0x1db8) = 0;
        local_28f0 = 0x20;
        local_28e8 = 0;
        local_28d8 = 0;
        local_28e0 = 0;
        local_2850 = (undefined4 *)0x0;
        local_28f8 = 0;
        local_28d0[0] = 0;
        CEGUI::String::grow((ulong)&local_28f8);
        local_28f8 = 0;
        puVar19 = local_2850;
        if (local_28f0 < 0x21) {
          puVar19 = local_28d0;
        }
        *puVar19 = 0;
                    /* try { // try from 00b967d3 to 00b967d7 has its CatchHandler @ 00b9a4bb */
        std::string::string((string *)local_148,"gui_",&local_3a);
                    /* try { // try from 00b967e8 to 00b967ec has its CatchHandler @ 00b9a4d0 */
        STRINGS::uniqueName((STRINGS *)local_158,(string *)local_148);
        local_2840 = 0x20;
        local_2838 = 0;
        local_2828 = 0;
        local_2830 = 0;
        local_27a0 = (undefined4 *)0x0;
        local_2848 = 0;
        local_2820[0] = 0;
        lVar8 = *(long *)(local_158[0] + -0x18);
                    /* try { // try from 00b96857 to 00b9685b has its CatchHandler @ 00b9a4e2 */
        CEGUI::String::grow((ulong)&local_2848);
        puVar19 = local_2820;
        if (0x20 < local_2840) {
          puVar19 = local_27a0;
        }
        puVar19[lVar8] = 0;
        lVar21 = lVar8;
        while (lVar21 != 0) {
          lVar21 = lVar21 + -1;
          puVar19 = local_2820;
          if (0x20 < local_2840) {
            puVar19 = local_27a0;
          }
          puVar19[lVar21] = (uint)*(byte *)(local_158[0] + lVar21);
        }
        local_2848 = lVar8;
                    /* try { // try from 00b968d4 to 00b968d8 has its CatchHandler @ 00b9a4f4 */
        CEGUI::String::String(local_2798,(uchar *)"GuiLook/StaticImage");
                    /* try { // try from 00b968f8 to 00b968fc has its CatchHandler @ 00b9a506 */
        pUVar16 = (UVector2 *)
                  CEGUI::WindowManager::createWindow
                            (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,local_2798,
                             (String *)&local_2848);
                    /* try { // try from 00b96908 to 00b9690c has its CatchHandler @ 00b9a4f4 */
        CEGUI::String::~String(local_2798);
                    /* try { // try from 00b96915 to 00b96919 has its CatchHandler @ 00b9a4e2 */
        CEGUI::String::~String((String *)&local_2848);
        if ((allocator *)(local_158[0] + -0x18) !=
            (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_158[0] + -8);
          iVar6 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar6 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_158[0] + -0x18));
          }
        }
        if ((allocator *)(local_148[0] + -0x18) !=
            (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_148[0] + -8);
          iVar6 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar6 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_148[0] + -0x18));
          }
        }
                    /* try { // try from 00b96955 to 00b969b1 has its CatchHandler @ 00b9a724 */
        CEGUI::String::~String((String *)&local_28f8);
        CEGUI::Window::addChildWindow(*(Window **)(this + 0x28));
        pUVar16[0x213] = (UVector2)0x0;
        CEGUI::Window::setWantsMultiClickEvents(SUB81(pUVar16,0));
        pUVar16[0x3e2] = (UVector2)0x1;
        CEGUI::EventSet::setMutedState((bool)(SUB81(pUVar16,0) + '8'));
        CEGUI::Window::getPosition();
        CEGUI::Window::setPosition(pUVar16);
        CEGUI::Window::getSize();
                    /* try { // try from 00b969bd to 00b969c1 has its CatchHandler @ 00b9a586 */
        CEGUI::Window::setSize(pUVar16);
        *(UVector2 **)(pCVar20 + 0x1898) = pUVar16;
        local_2b00 = 0x20;
        local_2af8 = 0;
        local_2ae8 = 0;
        local_2af0 = 0;
        local_2a60 = (undefined4 *)0x0;
        local_2b08 = 0;
        local_2ae0[0] = 0;
                    /* try { // try from 00b96a26 to 00b96a2a has its CatchHandler @ 00b9a724 */
        CEGUI::String::grow((ulong)&local_2b08);
        local_2b08 = 0;
        puVar19 = local_2a60;
        if (local_2b00 < 0x21) {
          puVar19 = local_2ae0;
        }
        *puVar19 = 0;
                    /* try { // try from 00b96a6d to 00b96a71 has its CatchHandler @ 00b9a58b */
        std::string::string((string *)local_168,"gui_",&local_3b);
                    /* try { // try from 00b96a82 to 00b96a86 has its CatchHandler @ 00b9a593 */
        STRINGS::uniqueName((STRINGS *)local_178,(string *)local_168);
        local_2a50 = 0x20;
        local_2a48 = 0;
        local_2a38 = 0;
        local_2a40 = 0;
        local_29b0 = (undefined4 *)0x0;
        local_2a58 = 0;
        local_2a30[0] = 0;
        lVar8 = *(long *)(local_178[0] + -0x18);
                    /* try { // try from 00b96af1 to 00b96af5 has its CatchHandler @ 00b9a59b */
        CEGUI::String::grow((ulong)&local_2a58);
        puVar19 = local_2a30;
        if (0x20 < local_2a50) {
          puVar19 = local_29b0;
        }
        puVar19[lVar8] = 0;
        lVar21 = lVar8;
        while (lVar21 != 0) {
          lVar21 = lVar21 + -1;
          puVar19 = local_2a30;
          if (0x20 < local_2a50) {
            puVar19 = local_29b0;
          }
          puVar19[lVar21] = (uint)*(byte *)(local_178[0] + lVar21);
        }
        local_2a58 = lVar8;
                    /* try { // try from 00b96b6c to 00b96b70 has its CatchHandler @ 00b9a1f1 */
        CEGUI::String::String(local_29a8,(uchar *)"GuiLook/StaticImage");
                    /* try { // try from 00b96b90 to 00b96b94 has its CatchHandler @ 00b9a22d */
        pUVar16 = (UVector2 *)
                  CEGUI::WindowManager::createWindow
                            (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,local_29a8,
                             (String *)&local_2a58);
                    /* try { // try from 00b96ba0 to 00b96ba4 has its CatchHandler @ 00b9a1f1 */
        CEGUI::String::~String(local_29a8);
                    /* try { // try from 00b96bad to 00b96bb1 has its CatchHandler @ 00b9a59b */
        CEGUI::String::~String((String *)&local_2a58);
        if ((allocator *)(local_178[0] + -0x18) !=
            (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_178[0] + -8);
          iVar6 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar6 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_178[0] + -0x18));
          }
        }
        if ((allocator *)(local_168[0] + -0x18) !=
            (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_168[0] + -8);
          iVar6 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar6 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_168[0] + -0x18));
          }
        }
                    /* try { // try from 00b96bee to 00b96c4a has its CatchHandler @ 00b9a724 */
        CEGUI::String::~String((String *)&local_2b08);
        CEGUI::Window::addChildWindow(*(Window **)(this + 0x40));
        pUVar16[0x213] = (UVector2)0x0;
        CEGUI::Window::setWantsMultiClickEvents(SUB81(pUVar16,0));
        pUVar16[0x3e2] = (UVector2)0x1;
        CEGUI::EventSet::setMutedState((bool)(SUB81(pUVar16,0) + '8'));
        CEGUI::Window::getPosition();
        CEGUI::Window::setPosition(pUVar16);
        CEGUI::Window::getSize();
                    /* try { // try from 00b96c56 to 00b96c5a has its CatchHandler @ 00b9a2ad */
        CEGUI::Window::setSize(pUVar16);
        *(UVector2 **)(pCVar20 + 0x1b28) = pUVar16;
        local_2d10 = 0x20;
        local_2d08 = 0;
        local_2cf8 = 0;
        local_2d00 = 0;
        local_2c70 = (undefined4 *)0x0;
        local_2d18 = 0;
        local_2cf0[0] = 0;
                    /* try { // try from 00b96cc2 to 00b96cc6 has its CatchHandler @ 00b9a724 */
        CEGUI::String::grow((ulong)&local_2d18);
        local_2d18 = 0;
        puVar19 = local_2cf0;
        if (0x20 < local_2d10) {
          puVar19 = local_2c70;
        }
        *puVar19 = 0;
                    /* try { // try from 00b96d05 to 00b96d09 has its CatchHandler @ 00b9a2b2 */
        std::string::string((string *)local_188,"gui_",&local_3c);
                    /* try { // try from 00b96d1a to 00b96d1e has its CatchHandler @ 00b9a2b7 */
        STRINGS::uniqueName((STRINGS *)local_198,(string *)local_188);
        local_2c60 = 0x20;
        local_2c58 = 0;
        local_2c48 = 0;
        local_2c50 = 0;
        local_2bc0 = (undefined4 *)0x0;
        local_2c68 = 0;
        local_2c40[0] = 0;
        lVar8 = *(long *)(local_198[0] + -0x18);
                    /* try { // try from 00b96d89 to 00b96d8d has its CatchHandler @ 00b9a2cc */
        CEGUI::String::grow((ulong)&local_2c68);
        puVar19 = local_2c40;
        if (0x20 < local_2c60) {
          puVar19 = local_2bc0;
        }
        puVar19[lVar8] = 0;
        lVar21 = lVar8;
        while (lVar21 != 0) {
          lVar21 = lVar21 + -1;
          puVar19 = local_2c40;
          if (0x20 < local_2c60) {
            puVar19 = local_2bc0;
          }
          puVar19[lVar21] = (uint)*(byte *)(local_198[0] + lVar21);
        }
        local_2c68 = lVar8;
                    /* try { // try from 00b96e02 to 00b96e06 has its CatchHandler @ 00b9a2de */
        CEGUI::String::String(local_2bb8,(uchar *)"GuiLook/StaticImage");
                    /* try { // try from 00b96e21 to 00b96e25 has its CatchHandler @ 00b9a2f0 */
        pUVar16 = (UVector2 *)
                  CEGUI::WindowManager::createWindow
                            (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,local_2bb8,
                             (String *)&local_2c68);
                    /* try { // try from 00b96e31 to 00b96e35 has its CatchHandler @ 00b9a2de */
        CEGUI::String::~String(local_2bb8);
                    /* try { // try from 00b96e3e to 00b96e42 has its CatchHandler @ 00b9a2cc */
        CEGUI::String::~String((String *)&local_2c68);
        if ((allocator *)(local_198[0] + -0x18) !=
            (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_198[0] + -8);
          iVar6 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar6 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_198[0] + -0x18));
          }
        }
        if ((allocator *)(local_188[0] + -0x18) !=
            (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_188[0] + -8);
          iVar6 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar6 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_188[0] + -0x18));
          }
        }
                    /* try { // try from 00b96e7a to 00b96ee8 has its CatchHandler @ 00b9a724 */
        CEGUI::String::~String((String *)&local_2d18);
        CEGUI::Window::addChildWindow(*(Window **)(*(long *)(pCVar20 + 0x1378) + 0xb0));
        pUVar16[0x213] = (UVector2)0x0;
        bVar23 = SUB81(pUVar16,0);
        CEGUI::Window::setWantsMultiClickEvents(bVar23);
        pUVar16[0x3e2] = (UVector2)0x1;
        CEGUI::EventSet::setMutedState((bool)(bVar23 + '8'));
        CEGUI::Window::getPosition();
        CEGUI::Window::setPosition(pUVar16);
        CEGUI::Window::getSize();
                    /* try { // try from 00b96eef to 00b96ef3 has its CatchHandler @ 00b9a370 */
        CEGUI::Window::setSize(pUVar16);
                    /* try { // try from 00b96efc to 00b9704a has its CatchHandler @ 00b9a724 */
        CEGUI::Window::setAlwaysOnTop(bVar23);
        *(UVector2 **)(pCVar20 + 0x1608) = pUVar16;
      }
    }
    local_48c4 = local_48c4 + 1;
    pCVar20 = pCVar20 + 8;
    plVar26 = plVar26 + 1;
    pCVar25 = pCVar25 + 0xb0;
    if (local_48c4 == 0xc) {
      iVar6 = 0;
      pCVar20 = this;
      do {
        *(int *)(pCVar20 + 0xa0) = iVar6;
        iVar6 = iVar6 + 1;
        pCVar20 = pCVar20 + 4;
      } while (iVar6 != 1000);
      iVar7 = 100;
      iVar6 = 0;
      do {
        lVar8 = (long)iVar6;
        iVar6 = iVar6 + 1;
        iVar7 = iVar7 + -1;
        *(long *)(this + lVar8 * 8 + 0x1050) = lVar8;
      } while (iVar7 != 0);
      local_2dc0 = 0x20;
      local_2db8 = 0;
      local_2da8 = 0;
      local_2db0 = 0;
      local_2d20 = (uint *)0x0;
      local_2dc8 = 0;
      local_2da0[0] = 0;
      CEGUI::String::grow((ulong)&local_2dc8);
      puVar18 = local_2da0;
      if (0x20 < local_2dc0) {
        puVar18 = local_2d20;
      }
      pcVar10 = "TabBackpack";
      do {
        bVar2 = *pcVar10;
        pcVar10 = pcVar10 + 1;
        *puVar18 = (uint)bVar2;
        puVar18 = puVar18 + 1;
      } while ((byte *)pcVar10 != (byte *)0xfef7db);
      local_2dc8 = 0xb;
      puVar18 = local_2d74;
      if (0x20 < local_2dc0) {
        puVar18 = local_2d20 + 0xb;
      }
      *puVar18 = 0;
                    /* try { // try from 00b970ba to 00b970be has its CatchHandler @ 00b9a375 */
      uVar9 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x48));
      *(undefined8 *)(this + 0x91d8) = uVar9;
                    /* try { // try from 00b970ca to 00b97136 has its CatchHandler @ 00b9a724 */
      CEGUI::String::~String((String *)&local_2dc8);
      local_2e70 = 0x20;
      local_2e68 = 0;
      local_2e58 = 0;
      local_2e60 = 0;
      local_2dd0 = (uint *)0x0;
      local_2e78 = 0;
      local_2e50[0] = 0;
      CEGUI::String::grow((ulong)&local_2e78);
      puVar18 = local_2e50;
      if (0x20 < local_2e70) {
        puVar18 = local_2dd0;
      }
      pcVar10 = "UnselectedImage";
      do {
        bVar2 = *pcVar10;
        pcVar10 = pcVar10 + 1;
        *puVar18 = (uint)bVar2;
        puVar18 = puVar18 + 1;
      } while ((byte *)pcVar10 != (byte *)0xfef76b);
      local_2e78 = 0xf;
      puVar18 = local_2e14;
      if (0x20 < local_2e70) {
        puVar18 = local_2dd0 + 0xf;
      }
      *puVar18 = 0;
                    /* try { // try from 00b971b0 to 00b971b4 has its CatchHandler @ 00b9a37a */
      CEGUI::PropertySet::getProperty((String *)&local_2f28);
                    /* try { // try from 00b971c8 to 00b971cc has its CatchHandler @ 00b9a385 */
      CEGUI::String::grow((ulong)(this + 0x9200));
      *(long *)(this + 0x9200) = local_2f28;
      pCVar20 = this + 0x9228;
      if (0x20 < *(ulong *)(this + 0x9208)) {
        pCVar20 = *(CPetMenu **)(this + 0x92a8);
      }
      *(undefined4 *)(pCVar20 + local_2f28 * 4) = 0;
      puVar22 = local_2f00;
      if (0x20 < local_2f20) {
        puVar22 = local_2e80;
      }
      pCVar20 = this + 0x9228;
      if (0x20 < *(ulong *)(this + 0x9208)) {
        pCVar20 = *(CPetMenu **)(this + 0x92a8);
      }
      memcpy(pCVar20,puVar22,local_2f28 * 4);
                    /* try { // try from 00b97239 to 00b9723d has its CatchHandler @ 00b9a37a */
      CEGUI::String::~String((String *)&local_2f28);
                    /* try { // try from 00b97241 to 00b972ad has its CatchHandler @ 00b9a724 */
      CEGUI::String::~String((String *)&local_2e78);
      local_2fd0 = 0x20;
      local_2fc8 = 0;
      local_2fb8 = 0;
      local_2fc0 = 0;
      local_2f30 = (uint *)0x0;
      local_2fd8 = 0;
      local_2fb0[0] = 0;
      CEGUI::String::grow((ulong)&local_2fd8);
      puVar18 = local_2fb0;
      if (0x20 < local_2fd0) {
        puVar18 = local_2f30;
      }
      pcVar10 = "SelectedImage";
      do {
        bVar2 = *pcVar10;
        pcVar10 = pcVar10 + 1;
        *puVar18 = (uint)bVar2;
        puVar18 = puVar18 + 1;
      } while ((byte *)pcVar10 != (byte *)0xfef7be);
      local_2fd8 = 0xd;
      puVar18 = local_2f7c;
      if (0x20 < local_2fd0) {
        puVar18 = local_2f30 + 0xd;
      }
      *puVar18 = 0;
                    /* try { // try from 00b97328 to 00b9732c has its CatchHandler @ 00b9a39a */
      CEGUI::PropertySet::getProperty((String *)&local_3088);
                    /* try { // try from 00b97340 to 00b97344 has its CatchHandler @ 00b9a39f */
      CEGUI::String::grow((ulong)(this + 0x9410));
      *(long *)(this + 0x9410) = local_3088;
      pCVar20 = this + 0x9438;
      if (0x20 < *(ulong *)(this + 0x9418)) {
        pCVar20 = *(CPetMenu **)(this + 0x94b8);
      }
      *(undefined4 *)(pCVar20 + local_3088 * 4) = 0;
      puVar22 = local_3060;
      if (0x20 < local_3080) {
        puVar22 = local_2fe0;
      }
      pCVar20 = this + 0x9438;
      if (0x20 < *(ulong *)(this + 0x9418)) {
        pCVar20 = *(CPetMenu **)(this + 0x94b8);
      }
      memcpy(pCVar20,puVar22,local_3088 * 4);
                    /* try { // try from 00b973b1 to 00b973b5 has its CatchHandler @ 00b9a39a */
      CEGUI::String::~String((String *)&local_3088);
                    /* try { // try from 00b973b9 to 00b97425 has its CatchHandler @ 00b9a724 */
      CEGUI::String::~String((String *)&local_2fd8);
      local_3130 = 0x20;
      local_3128 = 0;
      local_3118 = 0;
      local_3120 = 0;
      local_3090 = (uint *)0x0;
      local_3138 = 0;
      local_3110[0] = 0;
      CEGUI::String::grow((ulong)&local_3138);
      puVar18 = local_3110;
      if (0x20 < local_3130) {
        puVar18 = local_3090;
      }
      pcVar10 = "TabSpell";
      do {
        bVar2 = *pcVar10;
        pcVar10 = pcVar10 + 1;
        *puVar18 = (uint)bVar2;
        puVar18 = puVar18 + 1;
      } while ((byte *)pcVar10 != (byte *)0xfef7cf);
      local_3138 = 8;
      puVar18 = local_30f0;
      if (0x20 < local_3130) {
        puVar18 = local_3090 + 8;
      }
      *puVar18 = 0;
                    /* try { // try from 00b97492 to 00b97496 has its CatchHandler @ 00b9a3a2 */
      uVar9 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x48));
      *(undefined8 *)(this + 0x91e0) = uVar9;
                    /* try { // try from 00b974a2 to 00b9750e has its CatchHandler @ 00b9a724 */
      CEGUI::String::~String((String *)&local_3138);
      local_31e0 = 0x20;
      local_31d8 = 0;
      local_31c8 = 0;
      local_31d0 = 0;
      local_3140 = (uint *)0x0;
      local_31e8 = 0;
      local_31c0[0] = 0;
      CEGUI::String::grow((ulong)&local_31e8);
      puVar18 = local_31c0;
      if (0x20 < local_31e0) {
        puVar18 = local_3140;
      }
      pcVar10 = "UnselectedImage";
      do {
        bVar2 = *pcVar10;
        pcVar10 = pcVar10 + 1;
        *puVar18 = (uint)bVar2;
        puVar18 = puVar18 + 1;
      } while ((byte *)pcVar10 != (byte *)0xfef76b);
      local_31e8 = 0xf;
      puVar18 = local_3184;
      if (0x20 < local_31e0) {
        puVar18 = local_3140 + 0xf;
      }
      *puVar18 = 0;
                    /* try { // try from 00b97588 to 00b9758c has its CatchHandler @ 00b9a3a7 */
      CEGUI::PropertySet::getProperty((String *)&local_3298);
                    /* try { // try from 00b975a0 to 00b975a4 has its CatchHandler @ 00b9a3b5 */
      CEGUI::String::grow((ulong)(this + 0x92b0));
      *(long *)(this + 0x92b0) = local_3298;
      pCVar20 = this + 0x92d8;
      if (0x20 < *(ulong *)(this + 0x92b8)) {
        pCVar20 = *(CPetMenu **)(this + 0x9358);
      }
      *(undefined4 *)(pCVar20 + local_3298 * 4) = 0;
      puVar22 = local_3270;
      if (0x20 < local_3290) {
        puVar22 = local_31f0;
      }
      pCVar20 = this + 0x92d8;
      if (0x20 < *(ulong *)(this + 0x92b8)) {
        pCVar20 = *(CPetMenu **)(this + 0x9358);
      }
      memcpy(pCVar20,puVar22,local_3298 * 4);
                    /* try { // try from 00b97611 to 00b97615 has its CatchHandler @ 00b9a3a7 */
      CEGUI::String::~String((String *)&local_3298);
                    /* try { // try from 00b97619 to 00b97685 has its CatchHandler @ 00b9a724 */
      CEGUI::String::~String((String *)&local_31e8);
      local_3340 = 0x20;
      local_3338 = 0;
      local_3328 = 0;
      local_3330 = 0;
      local_32a0 = (uint *)0x0;
      local_3348 = 0;
      local_3320[0] = 0;
      CEGUI::String::grow((ulong)&local_3348);
      puVar18 = local_3320;
      if (0x20 < local_3340) {
        puVar18 = local_32a0;
      }
      pcVar10 = "SelectedImage";
      do {
        bVar2 = *pcVar10;
        pcVar10 = pcVar10 + 1;
        *puVar18 = (uint)bVar2;
        puVar18 = puVar18 + 1;
      } while ((byte *)pcVar10 != (byte *)0xfef7be);
      local_3348 = 0xd;
      puVar18 = local_32ec;
      if (0x20 < local_3340) {
        puVar18 = local_32a0 + 0xd;
      }
      *puVar18 = 0;
                    /* try { // try from 00b97700 to 00b97704 has its CatchHandler @ 00b9a3c2 */
      CEGUI::PropertySet::getProperty((String *)&local_33f8);
                    /* try { // try from 00b97718 to 00b9771c has its CatchHandler @ 00b9a3c7 */
      CEGUI::String::grow((ulong)(this + 0x94c0));
      *(long *)(this + 0x94c0) = local_33f8;
      pCVar20 = this + 0x94e8;
      if (0x20 < *(ulong *)(this + 0x94c8)) {
        pCVar20 = *(CPetMenu **)(this + 0x9568);
      }
      *(undefined4 *)(pCVar20 + local_33f8 * 4) = 0;
      puVar22 = local_33d0;
      if (0x20 < local_33f0) {
        puVar22 = local_3350;
      }
      pCVar20 = this + 0x94e8;
      if (0x20 < *(ulong *)(this + 0x94c8)) {
        pCVar20 = *(CPetMenu **)(this + 0x9568);
      }
      memcpy(pCVar20,puVar22,local_33f8 * 4);
                    /* try { // try from 00b97789 to 00b9778d has its CatchHandler @ 00b9a3c2 */
      CEGUI::String::~String((String *)&local_33f8);
                    /* try { // try from 00b97791 to 00b977fd has its CatchHandler @ 00b9a724 */
      CEGUI::String::~String((String *)&local_3348);
      local_34a0 = 0x20;
      local_3498 = 0;
      local_3488 = 0;
      local_3490 = 0;
      local_3400 = (uint *)0x0;
      local_34a8 = 0;
      local_3480[0] = 0;
      CEGUI::String::grow((ulong)&local_34a8);
      puVar18 = local_3480;
      if (0x20 < local_34a0) {
        puVar18 = local_3400;
      }
      pcVar10 = "TabFish";
      do {
        bVar2 = *pcVar10;
        pcVar10 = pcVar10 + 1;
        *puVar18 = (uint)bVar2;
        puVar18 = puVar18 + 1;
      } while ((byte *)pcVar10 != (byte *)0xfef7c6);
      local_34a8 = 7;
      puVar18 = local_3464;
      if (0x20 < local_34a0) {
        puVar18 = local_3400 + 7;
      }
      *puVar18 = 0;
                    /* try { // try from 00b9786a to 00b9786e has its CatchHandler @ 00b9a3d2 */
      uVar9 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x48));
      *(undefined8 *)(this + 0x91e8) = uVar9;
                    /* try { // try from 00b9787a to 00b978e6 has its CatchHandler @ 00b9a724 */
      CEGUI::String::~String((String *)&local_34a8);
      local_3550 = 0x20;
      local_3548 = 0;
      local_3538 = 0;
      local_3540 = 0;
      local_34b0 = (uint *)0x0;
      local_3558 = 0;
      local_3530[0] = 0;
      CEGUI::String::grow((ulong)&local_3558);
      puVar18 = local_3530;
      if (0x20 < local_3550) {
        puVar18 = local_34b0;
      }
      pcVar10 = "UnselectedImage";
      do {
        bVar2 = *pcVar10;
        pcVar10 = pcVar10 + 1;
        *puVar18 = (uint)bVar2;
        puVar18 = puVar18 + 1;
      } while ((byte *)pcVar10 != (byte *)0xfef76b);
      local_3558 = 0xf;
      puVar18 = local_34f4;
      if (0x20 < local_3550) {
        puVar18 = local_34b0 + 0xf;
      }
      *puVar18 = 0;
                    /* try { // try from 00b97960 to 00b97964 has its CatchHandler @ 00b9a415 */
      CEGUI::PropertySet::getProperty((String *)&local_3608);
                    /* try { // try from 00b97978 to 00b9797c has its CatchHandler @ 00b9a425 */
      CEGUI::String::grow((ulong)(this + 0x9360));
      *(long *)(this + 0x9360) = local_3608;
      pCVar20 = this + 0x9388;
      if (0x20 < *(ulong *)(this + 0x9368)) {
        pCVar20 = *(CPetMenu **)(this + 0x9408);
      }
      *(undefined4 *)(pCVar20 + local_3608 * 4) = 0;
      puVar22 = local_35e0;
      if (0x20 < local_3600) {
        puVar22 = local_3560;
      }
      pCVar20 = this + 0x9388;
      if (0x20 < *(ulong *)(this + 0x9368)) {
        pCVar20 = *(CPetMenu **)(this + 0x9408);
      }
      memcpy(pCVar20,puVar22,local_3608 * 4);
                    /* try { // try from 00b979e9 to 00b979ed has its CatchHandler @ 00b9a415 */
      CEGUI::String::~String((String *)&local_3608);
                    /* try { // try from 00b979f1 to 00b97a5d has its CatchHandler @ 00b9a724 */
      CEGUI::String::~String((String *)&local_3558);
      local_36b0 = 0x20;
      local_36a8 = 0;
      local_3698 = 0;
      local_36a0 = 0;
      local_3610 = (uint *)0x0;
      local_36b8 = 0;
      local_3690[0] = 0;
      CEGUI::String::grow((ulong)&local_36b8);
      puVar18 = local_3690;
      if (0x20 < local_36b0) {
        puVar18 = local_3610;
      }
      pcVar10 = "SelectedImage";
      do {
        bVar2 = *pcVar10;
        pcVar10 = pcVar10 + 1;
        *puVar18 = (uint)bVar2;
        puVar18 = puVar18 + 1;
      } while ((byte *)pcVar10 != (byte *)0xfef7be);
      local_36b8 = 0xd;
      puVar18 = local_365c;
      if (0x20 < local_36b0) {
        puVar18 = local_3610 + 0xd;
      }
      *puVar18 = 0;
                    /* try { // try from 00b97ad8 to 00b97adc has its CatchHandler @ 00b9a435 */
      CEGUI::PropertySet::getProperty((String *)&local_3768);
                    /* try { // try from 00b97af0 to 00b97af4 has its CatchHandler @ 00b9a445 */
      CEGUI::String::grow((ulong)(this + 0x9570));
      *(long *)(this + 0x9570) = local_3768;
      pCVar20 = this + 0x9598;
      if (0x20 < *(ulong *)(this + 0x9578)) {
        pCVar20 = *(CPetMenu **)(this + 0x9618);
      }
      *(undefined4 *)(pCVar20 + local_3768 * 4) = 0;
      puVar22 = local_3740;
      if (0x20 < local_3760) {
        puVar22 = local_36c0;
      }
      pCVar20 = this + 0x9598;
      if (0x20 < *(ulong *)(this + 0x9578)) {
        pCVar20 = *(CPetMenu **)(this + 0x9618);
      }
      memcpy(pCVar20,puVar22,local_3768 * 4);
                    /* try { // try from 00b97b61 to 00b97b65 has its CatchHandler @ 00b9a435 */
      CEGUI::String::~String((String *)&local_3768);
                    /* try { // try from 00b97b69 to 00b97c02 has its CatchHandler @ 00b9a724 */
      CEGUI::String::~String((String *)&local_36b8);
      CEGUI::Window::setZOrderingEnabled(SUB81(*(undefined8 *)(this + 0x91d8),0));
      CEGUI::Window::setZOrderingEnabled(SUB81(*(undefined8 *)(this + 0x91e0),0));
      CEGUI::Window::setZOrderingEnabled(SUB81(*(undefined8 *)(this + 0x91e8),0));
      local_3810 = 0x20;
      local_3808 = 0;
      local_37f8 = 0;
      local_3800 = 0;
      local_3770 = (uint *)0x0;
      local_3818 = 0;
      local_37f0[0] = 0;
      CEGUI::String::grow((ulong)&local_3818);
      puVar18 = local_37f0;
      if (0x20 < local_3810) {
        puVar18 = local_3770;
      }
      pbVar12 = (byte *)0xfeff6a;
      do {
        bVar2 = *pbVar12;
        pbVar12 = pbVar12 + 1;
        *puVar18 = (uint)bVar2;
        puVar18 = puVar18 + 1;
      } while (pbVar12 != (byte *)0xfeff78);
      local_3818 = 0xe;
      puVar18 = local_37b8;
      if (0x20 < local_3810) {
        puVar18 = local_3770 + 0xe;
      }
      *puVar18 = 0;
                    /* try { // try from 00b97c6a to 00b97c6e has its CatchHandler @ 00b9a401 */
      uVar9 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x48));
      *(undefined8 *)(this + 0x91c0) = uVar9;
                    /* try { // try from 00b97c7a to 00b97ce6 has its CatchHandler @ 00b9a724 */
      CEGUI::String::~String((String *)&local_3818);
      local_38c0 = 0x20;
      local_38b8 = 0;
      local_38a8 = 0;
      local_38b0 = 0;
      local_3820 = (uint *)0x0;
      local_38c8 = 0;
      local_38a0[0] = 0;
      CEGUI::String::grow((ulong)&local_38c8);
      puVar18 = local_38a0;
      if (0x20 < local_38c0) {
        puVar18 = local_3820;
      }
      pbVar12 = (byte *)0xfeff5b;
      do {
        bVar2 = *pbVar12;
        pbVar12 = pbVar12 + 1;
        *puVar18 = (uint)bVar2;
        puVar18 = puVar18 + 1;
      } while (pbVar12 != (byte *)0xfeff66);
      local_38c8 = 0xb;
      puVar18 = local_3874;
      if (0x20 < local_38c0) {
        puVar18 = local_3820 + 0xb;
      }
      *puVar18 = 0;
                    /* try { // try from 00b97d52 to 00b97d56 has its CatchHandler @ 00b9a406 */
      uVar9 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x48));
      *(undefined8 *)(this + 0x91c8) = uVar9;
                    /* try { // try from 00b97d62 to 00b97ddd has its CatchHandler @ 00b9a724 */
      CEGUI::String::~String((String *)&local_38c8);
      CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x91c8),0));
      local_3970 = 0x20;
      local_3968 = 0;
      local_3958 = 0;
      local_3960 = 0;
      local_38d0 = (uint *)0x0;
      local_3978 = 0;
      local_3950[0] = 0;
      CEGUI::String::grow((ulong)&local_3978);
      puVar18 = local_3950;
      if (0x20 < local_3970) {
        puVar18 = local_38d0;
      }
      pbVar12 = (byte *)0xfeff4e;
      do {
        bVar2 = *pbVar12;
        pbVar12 = pbVar12 + 1;
        *puVar18 = (uint)bVar2;
        puVar18 = puVar18 + 1;
      } while (pbVar12 != (byte *)0xfeff57);
      local_3978 = 9;
      puVar18 = local_392c;
      if (0x20 < local_3970) {
        puVar18 = local_38d0 + 9;
      }
      *puVar18 = 0;
                    /* try { // try from 00b97e4a to 00b97e4e has its CatchHandler @ 00b99bd5 */
      uVar9 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x48));
      *(undefined8 *)(this + 0x91d0) = uVar9;
                    /* try { // try from 00b97e5a to 00b97ec1 has its CatchHandler @ 00b9a724 */
      CEGUI::String::~String((String *)&local_3978);
      CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x91d0),0));
      local_48c4 = 1;
      pCVar20 = this;
      do {
        STRINGS::GetValueAsString((uint)local_1a8);
                    /* try { // try from 00b97ed7 to 00b97edb has its CatchHandler @ 00b99bef */
        std::operator+((char *)local_1b8,(string *)0xff0cc3);
        local_3a20 = 0x20;
        local_3a18 = 0;
        local_3a08 = 0;
        local_3a10 = 0;
        local_3980 = (undefined4 *)0x0;
        local_3a28 = 0;
        local_3a00[0] = 0;
        lVar8 = *(long *)(local_1b8[0] + -0x18);
                    /* try { // try from 00b97f46 to 00b97f4a has its CatchHandler @ 00b99c01 */
        CEGUI::String::grow((ulong)&local_3a28);
        puVar19 = local_3a00;
        if (0x20 < local_3a20) {
          puVar19 = local_3980;
        }
        puVar19[lVar8] = 0;
        lVar21 = lVar8;
        while (lVar21 != 0) {
          lVar21 = lVar21 + -1;
          puVar19 = local_3a00;
          if (0x20 < local_3a20) {
            puVar19 = local_3980;
          }
          puVar19[lVar21] = (uint)*(byte *)(local_1b8[0] + lVar21);
        }
        local_3a28 = lVar8;
                    /* try { // try from 00b97fc2 to 00b97fc6 has its CatchHandler @ 00b99c13 */
        lVar8 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x48));
                    /* try { // try from 00b97fd2 to 00b97fd6 has its CatchHandler @ 00b99c01 */
        CEGUI::String::~String((String *)&local_3a28);
        if ((allocator *)(local_1b8[0] + -0x18) !=
            (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_1b8[0] + -8);
          iVar6 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar6 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_1b8[0] + -0x18));
          }
        }
        if ((allocator *)(local_1a8[0] + -0x18) !=
            (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_1a8[0] + -8);
          iVar6 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar6 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_1a8[0] + -0x18));
          }
        }
                    /* try { // try from 00b9800d to 00b9804b has its CatchHandler @ 00b9a724 */
        CEGUI::Window::moveToFront();
        *(undefined1 *)(lVar8 + 0x213) = 0;
        CEGUI::Window::setWantsMultiClickEvents(SUB81(lVar8,0));
        *(CPetMenu **)(lVar8 + 0x1d8) = this + (ulong)(local_48c4 + 0x12) * 4 + 0xa0;
        pcVar3 = *(code **)(*(long *)(lVar8 + 0x38) + 0x10);
        local_1c8[0] = operator_new(0x20);
        lVar21 = lVar8 + 0x38;
        *local_1c8[0] = &PTR__MemberFunctionSlot_00ff0850;
        local_1c8[0][2] = 0;
        local_1c8[0][1] = handle_ItemClick;
        local_1c8[0][3] = this;
                    /* try { // try from 00b9808b to 00b980c6 has its CatchHandler @ 00b99c93 */
        (*pcVar3)(&local_4a8,lVar21,CEGUI::Window::EventMouseButtonDown,local_1c8);
        pBVar5 = local_4a8;
        if ((local_4a8 != (BoundSlot *)0x0) &&
           (iVar6 = *local_4a0, *local_4a0 = iVar6 + -1, iVar6 + -1 == 0)) {
          if (local_4a8 != (BoundSlot *)0x0) {
            CEGUI::BoundSlot::~BoundSlot(local_4a8);
            operator_delete(pBVar5);
          }
          operator_delete(local_4a0);
          local_4a8 = (BoundSlot *)0x0;
          local_4a0 = (int *)0x0;
        }
                    /* try { // try from 00b980fe to 00b98119 has its CatchHandler @ 00b9a724 */
        CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_1c8);
        pcVar3 = *(code **)(*(long *)(lVar8 + 0x38) + 0x10);
        local_1d8[0] = operator_new(0x20);
        *local_1d8[0] = &PTR__MemberFunctionSlot_00ff0850;
        local_1d8[0][2] = 0;
        local_1d8[0][1] = handle_MouseOver;
        local_1d8[0][3] = this;
                    /* try { // try from 00b98155 to 00b98190 has its CatchHandler @ 00b99ca8 */
        (*pcVar3)(&local_4b8,lVar21,CEGUI::Window::EventMouseEnters,local_1d8);
        pBVar5 = local_4b8;
        if ((local_4b8 != (BoundSlot *)0x0) &&
           (iVar6 = *local_4b0, *local_4b0 = iVar6 + -1, iVar6 + -1 == 0)) {
          if (local_4b8 != (BoundSlot *)0x0) {
            CEGUI::BoundSlot::~BoundSlot(local_4b8);
            operator_delete(pBVar5);
          }
          operator_delete(local_4b0);
          local_4b8 = (BoundSlot *)0x0;
          local_4b0 = (int *)0x0;
        }
                    /* try { // try from 00b981c8 to 00b981e3 has its CatchHandler @ 00b9a724 */
        CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_1d8);
        pcVar3 = *(code **)(*(long *)(lVar8 + 0x38) + 0x10);
        local_1e8[0] = operator_new(0x20);
        *local_1e8[0] = &PTR__MemberFunctionSlot_00ff0850;
        local_1e8[0][2] = 0;
        local_1e8[0][1] = handle_MouseOver;
        local_1e8[0][3] = this;
                    /* try { // try from 00b9821f to 00b9825a has its CatchHandler @ 00b99cbd */
        (*pcVar3)(&local_4c8,lVar21,CEGUI::Window::EventMouseMove,local_1e8);
        pBVar5 = local_4c8;
        if ((local_4c8 != (BoundSlot *)0x0) &&
           (iVar6 = *local_4c0, *local_4c0 = iVar6 + -1, iVar6 + -1 == 0)) {
          if (local_4c8 != (BoundSlot *)0x0) {
            CEGUI::BoundSlot::~BoundSlot(local_4c8);
            operator_delete(pBVar5);
          }
          operator_delete(local_4c0);
          local_4c8 = (BoundSlot *)0x0;
          local_4c0 = (int *)0x0;
        }
                    /* try { // try from 00b98292 to 00b982ad has its CatchHandler @ 00b9a724 */
        CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_1e8);
        pcVar3 = *(code **)(*(long *)(lVar8 + 0x38) + 0x10);
        local_1f8[0] = operator_new(0x20);
        *local_1f8[0] = &PTR__MemberFunctionSlot_00ff0850;
        local_1f8[0][2] = 0;
        local_1f8[0][1] = handle_MouseOut;
        local_1f8[0][3] = this;
                    /* try { // try from 00b982e9 to 00b9831f has its CatchHandler @ 00b99cd2 */
        (*pcVar3)(&local_4d8,lVar21,CEGUI::Window::EventMouseLeaves,local_1f8);
        pBVar5 = local_4d8;
        if ((local_4d8 != (BoundSlot *)0x0) &&
           (iVar6 = *local_4d0, *local_4d0 = iVar6 + -1, iVar6 + -1 == 0)) {
          if (local_4d8 != (BoundSlot *)0x0) {
            CEGUI::BoundSlot::~BoundSlot(local_4d8);
            operator_delete(pBVar5);
          }
          operator_delete(local_4d0);
          local_4d8 = (BoundSlot *)0x0;
          local_4d0 = (int *)0x0;
        }
                    /* try { // try from 00b98355 to 00b983c2 has its CatchHandler @ 00b9a724 */
        CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_1f8);
        *(long *)(pCVar20 + 0x1410) = lVar8;
        local_3c30 = 0x20;
        local_3c28 = 0;
        local_3c18 = 0;
        local_3c20 = 0;
        local_3b90 = (undefined4 *)0x0;
        local_3c38 = 0;
        local_3c10[0] = 0;
        CEGUI::String::grow((ulong)&local_3c38);
        local_3c38 = 0;
        puVar19 = local_3b90;
        if (local_3c30 < 0x21) {
          puVar19 = local_3c10;
        }
        *puVar19 = 0;
                    /* try { // try from 00b98405 to 00b98409 has its CatchHandler @ 00b99ce7 */
        std::string::string((string *)local_208,"gui_",&local_3d);
                    /* try { // try from 00b9841a to 00b9841e has its CatchHandler @ 00b99cfc */
        STRINGS::uniqueName((STRINGS *)local_218,(string *)local_208);
        local_3b80 = 0x20;
        local_3b78 = 0;
        local_3b68 = 0;
        local_3b70 = 0;
        local_3ae0 = (undefined4 *)0x0;
        local_3b88 = 0;
        local_3b60[0] = 0;
        lVar8 = *(long *)(local_218[0] + -0x18);
                    /* try { // try from 00b98489 to 00b9848d has its CatchHandler @ 00b99d0e */
        CEGUI::String::grow((ulong)&local_3b88);
        puVar19 = local_3b60;
        if (0x20 < local_3b80) {
          puVar19 = local_3ae0;
        }
        puVar19[lVar8] = 0;
        lVar21 = lVar8;
        while (lVar21 != 0) {
          lVar21 = lVar21 + -1;
          puVar19 = local_3b60;
          if (0x20 < local_3b80) {
            puVar19 = local_3ae0;
          }
          puVar19[lVar21] = (uint)*(byte *)(local_218[0] + lVar21);
        }
        local_3b88 = lVar8;
                    /* try { // try from 00b984ff to 00b98503 has its CatchHandler @ 00b99d20 */
        CEGUI::String::String(local_3ad8,(uchar *)"GuiLook/StaticText");
                    /* try { // try from 00b9851e to 00b98522 has its CatchHandler @ 00b99d32 */
        uVar9 = CEGUI::WindowManager::createWindow
                          (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,local_3ad8,
                           (String *)&local_3b88);
        *(undefined8 *)(pCVar20 + 0x1e50) = uVar9;
                    /* try { // try from 00b9852d to 00b98531 has its CatchHandler @ 00b99d20 */
        CEGUI::String::~String(local_3ad8);
                    /* try { // try from 00b9853a to 00b9853e has its CatchHandler @ 00b99d0e */
        CEGUI::String::~String((String *)&local_3b88);
        if ((allocator *)(local_218[0] + -0x18) !=
            (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_218[0] + -8);
          iVar6 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar6 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_218[0] + -0x18));
          }
        }
        if ((allocator *)(local_208[0] + -0x18) !=
            (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_208[0] + -8);
          iVar6 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar6 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_208[0] + -0x18));
          }
        }
                    /* try { // try from 00b9857b to 00b985e7 has its CatchHandler @ 00b9a724 */
        CEGUI::String::~String((String *)&local_3c38);
        local_3ce0 = 0x20;
        local_3cd8 = 0;
        local_3cc8 = 0;
        local_3cd0 = 0;
        local_3c40 = (uint *)0x0;
        local_3ce8 = 0;
        local_3cc0[0] = 0;
        CEGUI::String::grow((ulong)&local_3ce8);
        puVar18 = local_3cc0;
        if (0x20 < local_3ce0) {
          puVar18 = local_3c40;
        }
        pcVar10 = "Serif";
        do {
          bVar2 = *pcVar10;
          pcVar10 = pcVar10 + 1;
          *puVar18 = (uint)bVar2;
          puVar18 = puVar18 + 1;
        } while ((byte *)pcVar10 != (byte *)0xfe4949);
        local_3ce8 = 5;
        puVar18 = local_3cac;
        if (0x20 < local_3ce0) {
          puVar18 = local_3c40 + 5;
        }
        *puVar18 = 0;
                    /* try { // try from 00b98654 to 00b98658 has its CatchHandler @ 00b99d9f */
        CEGUI::Window::setFont(*(String **)(pCVar20 + 0x1e50));
                    /* try { // try from 00b9865c to 00b98673 has its CatchHandler @ 00b9a724 */
        CEGUI::String::~String((String *)&local_3ce8);
        CEGUI::Window::getSize();
                    /* try { // try from 00b9867e to 00b98682 has its CatchHandler @ 00b99d97 */
        CEGUI::Window::setSize(*(UVector2 **)(pCVar20 + 0x1e50));
                    /* try { // try from 00b98686 to 00b9868a has its CatchHandler @ 00b9a724 */
        puVar17 = (undefined8 *)CEGUI::Window::getPosition();
        local_4f8 = *puVar17;
        local_4f0 = puVar17[1];
        local_3e40 = 0x20;
        local_3e38 = 0;
        local_3e28 = 0;
        local_3e30 = 0;
        local_3da0 = (uint *)0x0;
        local_3e48 = 0;
        local_3e20[0] = 0;
                    /* try { // try from 00b98702 to 00b98706 has its CatchHandler @ 00b99dba */
        CEGUI::String::grow((ulong)&local_3e48);
        puVar18 = local_3da0;
        if (local_3e40 < 0x21) {
          puVar18 = local_3e20;
        }
        pcVar10 = "RightAligned";
        do {
          bVar2 = *pcVar10;
          pcVar10 = pcVar10 + 1;
          *puVar18 = (uint)bVar2;
          puVar18 = puVar18 + 1;
        } while ((byte *)pcVar10 != (byte *)0xfe602d);
        local_3e48 = 0xc;
        if (local_3e40 < 0x21) {
          puVar18 = local_3df0;
        }
        else {
          puVar18 = local_3da0 + 0xc;
        }
        *puVar18 = 0;
        local_3d90 = 0x20;
        local_3d88 = 0;
        local_3d78 = 0;
        local_3d80 = 0;
        local_3cf0 = (uint *)0x0;
        local_3d98 = 0;
        local_3d70[0] = 0;
                    /* try { // try from 00b987d5 to 00b987d9 has its CatchHandler @ 00b99dc7 */
        CEGUI::String::grow((ulong)&local_3d98);
        puVar18 = local_3d70;
        if (0x20 < local_3d90) {
          puVar18 = local_3cf0;
        }
        pcVar10 = "HorzTextFormatting";
        do {
          bVar2 = *pcVar10;
          pcVar10 = pcVar10 + 1;
          *puVar18 = (uint)bVar2;
          puVar18 = puVar18 + 1;
        } while ((byte *)pcVar10 != (byte *)0xfe48cf);
        local_3d98 = 0x12;
        puVar18 = local_3d28;
        if (0x20 < local_3d90) {
          puVar18 = local_3cf0 + 0x12;
        }
        *puVar18 = 0;
                    /* try { // try from 00b98854 to 00b98858 has its CatchHandler @ 00b99ddc */
        CEGUI::PropertySet::setProperty(*(String **)(pCVar20 + 0x1e50),(String *)&local_3d98);
                    /* try { // try from 00b9885c to 00b98860 has its CatchHandler @ 00b99dc7 */
        CEGUI::String::~String((String *)&local_3d98);
                    /* try { // try from 00b98869 to 00b988d2 has its CatchHandler @ 00b99dba */
        CEGUI::String::~String((String *)&local_3e48);
        local_3fa0 = 0x20;
        local_3f98 = 0;
        local_3f88 = 0;
        local_3f90 = 0;
        local_3f00 = (uint *)0x0;
        local_3fa8 = 0;
        local_3f80[0] = 0;
        CEGUI::String::grow((ulong)&local_3fa8);
        puVar18 = local_3f00;
        if (local_3fa0 < 0x21) {
          puVar18 = local_3f80;
        }
        pcVar10 = "BottomAligned";
        do {
          bVar2 = *pcVar10;
          pcVar10 = pcVar10 + 1;
          *puVar18 = (uint)bVar2;
          puVar18 = puVar18 + 1;
        } while ((byte *)pcVar10 != (byte *)0xfe6020);
        local_3fa8 = 0xd;
        if (local_3fa0 < 0x21) {
          puVar18 = local_3f4c;
        }
        else {
          puVar18 = local_3f00 + 0xd;
        }
        *puVar18 = 0;
        local_3ef0 = 0x20;
        local_3ee8 = 0;
        local_3ed8 = 0;
        local_3ee0 = 0;
        local_3e50 = (uint *)0x0;
        local_3ef8 = 0;
        local_3ed0[0] = 0;
                    /* try { // try from 00b9899d to 00b989a1 has its CatchHandler @ 00b99de9 */
        CEGUI::String::grow((ulong)&local_3ef8);
        puVar18 = local_3ed0;
        if (0x20 < local_3ef0) {
          puVar18 = local_3e50;
        }
        pcVar10 = "VertFormatting";
        do {
          bVar2 = *pcVar10;
          pcVar10 = pcVar10 + 1;
          *puVar18 = (uint)bVar2;
          puVar18 = puVar18 + 1;
        } while ((byte *)pcVar10 != (byte *)0xfe48ae);
        local_3ef8 = 0xe;
        puVar18 = local_3e98;
        if (0x20 < local_3ef0) {
          puVar18 = local_3e50 + 0xe;
        }
        *puVar18 = 0;
                    /* try { // try from 00b98a14 to 00b98a18 has its CatchHandler @ 00b99dfe */
        CEGUI::PropertySet::setProperty(*(String **)(pCVar20 + 0x1e50),(String *)&local_3ef8);
                    /* try { // try from 00b98a1c to 00b98a20 has its CatchHandler @ 00b99de9 */
        CEGUI::String::~String((String *)&local_3ef8);
                    /* try { // try from 00b98a29 to 00b98a7e has its CatchHandler @ 00b99dba */
        CEGUI::String::~String((String *)&local_3fa8);
        *(undefined1 *)(*(long *)(pCVar20 + 0x1e50) + 0x3e2) = 1;
        CEGUI::Window::setPosition(*(UVector2 **)(pCVar20 + 0x1e50));
        CEGUI::Window::addChildWindow(*(Window **)(*(long *)(pCVar20 + 0x1410) + 0xb0));
        CEGUI::String::String(local_4058,"");
                    /* try { // try from 00b98a89 to 00b98a8d has its CatchHandler @ 00b99e0b */
        CEGUI::Window::setText(*(String **)(pCVar20 + 0x1e50));
                    /* try { // try from 00b98a91 to 00b98ac6 has its CatchHandler @ 00b99dba */
        CEGUI::String::~String(local_4058);
        CEGUI::colour::colour(local_588,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc);
        CEGUI::PropertyHelper::colourToString(local_4108);
        local_41b0 = 0x20;
        local_41a8 = 0;
        local_4198 = 0;
        local_41a0 = 0;
        local_4110 = (uint *)0x0;
        local_41b8 = 0;
        local_4190[0] = 0;
                    /* try { // try from 00b98b2a to 00b98b2e has its CatchHandler @ 00b99e0d */
        CEGUI::String::grow((ulong)&local_41b8);
        puVar18 = local_4190;
        if (0x20 < local_41b0) {
          puVar18 = local_4110;
        }
        pbVar12 = (byte *)0xfe4654;
        do {
          bVar2 = *pbVar12;
          pbVar12 = pbVar12 + 1;
          *puVar18 = (uint)bVar2;
          puVar18 = puVar18 + 1;
        } while (pbVar12 != (byte *)0xfe465e);
        local_41b8 = 10;
        puVar18 = local_4168;
        if (0x20 < local_41b0) {
          puVar18 = local_4110 + 10;
        }
        *puVar18 = 0;
                    /* try { // try from 00b98ba4 to 00b98ba8 has its CatchHandler @ 00b99e22 */
        CEGUI::PropertySet::setProperty(*(String **)(pCVar20 + 0x1e50),(String *)&local_41b8);
                    /* try { // try from 00b98bac to 00b98bb0 has its CatchHandler @ 00b99e0d */
        CEGUI::String::~String((String *)&local_41b8);
                    /* try { // try from 00b98bb9 to 00b98c30 has its CatchHandler @ 00b99dba */
        CEGUI::String::~String(local_4108);
        CEGUI::Window::setAlwaysOnTop(SUB81(*(undefined8 *)(pCVar20 + 0x1e50),0));
        local_43c0 = 0x20;
        local_43b8 = 0;
        local_43a8 = 0;
        local_43b0 = 0;
        local_4320 = (undefined4 *)0x0;
        local_43c8 = 0;
        local_43a0[0] = 0;
        CEGUI::String::grow((ulong)&local_43c8);
        local_43c8 = 0;
        puVar19 = local_4320;
        if (local_43c0 < 0x21) {
          puVar19 = local_43a0;
        }
        *puVar19 = 0;
                    /* try { // try from 00b98c73 to 00b98c77 has its CatchHandler @ 00b99e2f */
        std::string::string((string *)local_228,"gui_",&local_3e);
                    /* try { // try from 00b98c88 to 00b98c8c has its CatchHandler @ 00b99e44 */
        STRINGS::uniqueName((STRINGS *)local_238,(string *)local_228);
        local_4310 = 0x20;
        local_4308 = 0;
        local_42f8 = 0;
        local_4300 = 0;
        local_4270 = (undefined4 *)0x0;
        local_4318 = 0;
        local_42f0[0] = 0;
        lVar8 = *(long *)(local_238[0] + -0x18);
                    /* try { // try from 00b98cf7 to 00b98cfb has its CatchHandler @ 00b99e56 */
        CEGUI::String::grow((ulong)&local_4318);
        puVar19 = local_42f0;
        if (0x20 < local_4310) {
          puVar19 = local_4270;
        }
        puVar19[lVar8] = 0;
        lVar21 = lVar8;
        while (lVar21 != 0) {
          lVar21 = lVar21 + -1;
          puVar19 = local_42f0;
          if (0x20 < local_4310) {
            puVar19 = local_4270;
          }
          puVar19[lVar21] = (uint)*(byte *)(local_238[0] + lVar21);
        }
        local_4318 = lVar8;
                    /* try { // try from 00b98d6c to 00b98d70 has its CatchHandler @ 00b99e68 */
        CEGUI::String::String(local_4268,(uchar *)"GuiLook/StaticImage");
                    /* try { // try from 00b98d90 to 00b98d94 has its CatchHandler @ 00b99e7a */
        pUVar16 = (UVector2 *)
                  CEGUI::WindowManager::createWindow
                            (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,local_4268,
                             (String *)&local_4318);
                    /* try { // try from 00b98da0 to 00b98da4 has its CatchHandler @ 00b99e68 */
        CEGUI::String::~String(local_4268);
                    /* try { // try from 00b98dad to 00b98db1 has its CatchHandler @ 00b99e56 */
        CEGUI::String::~String((String *)&local_4318);
        if ((allocator *)(local_238[0] + -0x18) !=
            (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_238[0] + -8);
          iVar6 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar6 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_238[0] + -0x18));
          }
        }
        if ((allocator *)(local_228[0] + -0x18) !=
            (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_228[0] + -8);
          iVar6 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar6 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_228[0] + -0x18));
          }
        }
                    /* try { // try from 00b98dee to 00b98e53 has its CatchHandler @ 00b99dba */
        CEGUI::String::~String((String *)&local_43c8);
        CEGUI::Window::addChildWindow(*(Window **)(*(long *)(pCVar20 + 0x1410) + 0xb0));
        pUVar16[0x213] = (UVector2)0x0;
        CEGUI::Window::setWantsMultiClickEvents(SUB81(pUVar16,0));
        pUVar16[0x3e2] = (UVector2)0x1;
        CEGUI::EventSet::setMutedState((bool)(SUB81(pUVar16,0) + '8'));
        CEGUI::Window::getPosition();
        CEGUI::Window::setPosition(pUVar16);
        CEGUI::Window::getSize();
                    /* try { // try from 00b98e5f to 00b98e63 has its CatchHandler @ 00b99efa */
        CEGUI::Window::setSize(pUVar16);
        *(UVector2 **)(pCVar20 + 0x1930) = pUVar16;
        local_45d0 = 0x20;
        local_45c8 = 0;
        local_45b8 = 0;
        local_45c0 = 0;
        local_4530 = (undefined4 *)0x0;
        local_45d8 = 0;
        local_45b0[0] = 0;
                    /* try { // try from 00b98ec8 to 00b98ecc has its CatchHandler @ 00b99dba */
        CEGUI::String::grow((ulong)&local_45d8);
        local_45d8 = 0;
        puVar19 = local_4530;
        if (local_45d0 < 0x21) {
          puVar19 = local_45b0;
        }
        *puVar19 = 0;
                    /* try { // try from 00b98f0f to 00b98f13 has its CatchHandler @ 00b99eff */
        std::string::string((string *)local_248,"gui_",&local_3f);
                    /* try { // try from 00b98f24 to 00b98f28 has its CatchHandler @ 00b99f14 */
        STRINGS::uniqueName((STRINGS *)local_258,(string *)local_248);
        local_4520 = 0x20;
        local_4518 = 0;
        local_4508 = 0;
        local_4510 = 0;
        local_4480 = (undefined4 *)0x0;
        local_4528 = 0;
        local_4500[0] = 0;
        lVar8 = *(long *)(local_258[0] + -0x18);
                    /* try { // try from 00b98f93 to 00b98f97 has its CatchHandler @ 00b99f26 */
        CEGUI::String::grow((ulong)&local_4528);
        puVar19 = local_4480;
        if (local_4520 < 0x21) {
          puVar19 = local_4500;
        }
        puVar19[lVar8] = 0;
        if (lVar8 != 0) {
          lVar21 = lVar8;
          do {
            lVar21 = lVar21 + -1;
            puVar19 = local_4500;
            if (0x20 < local_4520) {
              puVar19 = local_4480;
            }
            puVar19[lVar21] = (uint)*(byte *)(local_258[0] + lVar21);
          } while (lVar21 != 0);
        }
        local_4528 = lVar8;
                    /* try { // try from 00b9901c to 00b99020 has its CatchHandler @ 00b99f38 */
        CEGUI::String::String(local_4478,(uchar *)"GuiLook/StaticImage");
                    /* try { // try from 00b99040 to 00b99044 has its CatchHandler @ 00b99f4a */
        pUVar16 = (UVector2 *)
                  CEGUI::WindowManager::createWindow
                            (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,local_4478,
                             (String *)&local_4528);
                    /* try { // try from 00b99050 to 00b99054 has its CatchHandler @ 00b99f38 */
        CEGUI::String::~String(local_4478);
                    /* try { // try from 00b9905d to 00b99061 has its CatchHandler @ 00b99f26 */
        CEGUI::String::~String((String *)&local_4528);
        if ((allocator *)(local_258[0] + -0x18) !=
            (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_258[0] + -8);
          iVar6 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar6 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_258[0] + -0x18));
          }
        }
        if ((allocator *)(local_248[0] + -0x18) !=
            (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_248[0] + -8);
          iVar6 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar6 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_248[0] + -0x18));
          }
        }
                    /* try { // try from 00b9909e to 00b990fa has its CatchHandler @ 00b99dba */
        CEGUI::String::~String((String *)&local_45d8);
        CEGUI::Window::addChildWindow(*(Window **)(this + 0x40));
        pUVar16[0x213] = (UVector2)0x0;
        CEGUI::Window::setWantsMultiClickEvents(SUB81(pUVar16,0));
        pUVar16[0x3e2] = (UVector2)0x1;
        CEGUI::EventSet::setMutedState((bool)(SUB81(pUVar16,0) + '8'));
        CEGUI::Window::getPosition();
        CEGUI::Window::setPosition(pUVar16);
        CEGUI::Window::getSize();
                    /* try { // try from 00b99106 to 00b9910a has its CatchHandler @ 00b99fca */
        CEGUI::Window::setSize(pUVar16);
        *(UVector2 **)(pCVar20 + 0x1bc0) = pUVar16;
        local_47e0 = 0x20;
        local_47d8 = 0;
        local_47c8 = 0;
        local_47d0 = 0;
        local_4740 = (undefined4 *)0x0;
        local_47e8 = 0;
        local_47c0[0] = 0;
                    /* try { // try from 00b9916f to 00b99173 has its CatchHandler @ 00b99dba */
        CEGUI::String::grow((ulong)&local_47e8);
        local_47e8 = 0;
        puVar19 = local_4740;
        if (local_47e0 < 0x21) {
          puVar19 = local_47c0;
        }
        *puVar19 = 0;
                    /* try { // try from 00b991b6 to 00b991ba has its CatchHandler @ 00b99fcf */
        std::string::string((string *)local_268,"gui_",&local_40);
                    /* try { // try from 00b991cb to 00b991cf has its CatchHandler @ 00b99fe4 */
        STRINGS::uniqueName((STRINGS *)local_278,(string *)local_268);
        local_4730 = 0x20;
        local_4728 = 0;
        local_4718 = 0;
        local_4720 = 0;
        local_4690 = (undefined4 *)0x0;
        local_4738 = 0;
        local_4710[0] = 0;
        lVar8 = *(long *)(local_278[0] + -0x18);
                    /* try { // try from 00b9923a to 00b9923e has its CatchHandler @ 00b99ff6 */
        CEGUI::String::grow((ulong)&local_4738);
        puVar19 = local_4690;
        if (local_4730 < 0x21) {
          puVar19 = local_4710;
        }
        puVar19[lVar8] = 0;
        if (lVar8 != 0) {
          lVar21 = lVar8;
          do {
            lVar21 = lVar21 + -1;
            puVar19 = local_4710;
            if (0x20 < local_4730) {
              puVar19 = local_4690;
            }
            puVar19[lVar21] = (uint)*(byte *)(local_278[0] + lVar21);
          } while (lVar21 != 0);
        }
        local_4738 = lVar8;
                    /* try { // try from 00b992c4 to 00b992c8 has its CatchHandler @ 00b9a008 */
        CEGUI::String::String(local_4688,(uchar *)"GuiLook/StaticImage");
                    /* try { // try from 00b992e8 to 00b992ec has its CatchHandler @ 00b9a01a */
        pUVar16 = (UVector2 *)
                  CEGUI::WindowManager::createWindow
                            (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,local_4688,
                             (String *)&local_4738);
                    /* try { // try from 00b992f8 to 00b992fc has its CatchHandler @ 00b9a008 */
        CEGUI::String::~String(local_4688);
                    /* try { // try from 00b99305 to 00b99309 has its CatchHandler @ 00b99ff6 */
        CEGUI::String::~String((String *)&local_4738);
        if ((allocator *)(local_278[0] + -0x18) !=
            (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_278[0] + -8);
          iVar6 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar6 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_278[0] + -0x18));
          }
        }
        if ((allocator *)(local_268[0] + -0x18) !=
            (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_268[0] + -8);
          iVar6 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar6 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_268[0] + -0x18));
          }
        }
                    /* try { // try from 00b99346 to 00b993a2 has its CatchHandler @ 00b99dba */
        CEGUI::String::~String((String *)&local_47e8);
        CEGUI::Window::addChildWindow(*(Window **)(this + 0x38));
        pUVar16[0x213] = (UVector2)0x0;
        CEGUI::Window::setWantsMultiClickEvents(SUB81(pUVar16,0));
        pUVar16[0x3e2] = (UVector2)0x1;
        CEGUI::EventSet::setMutedState((bool)(SUB81(pUVar16,0) + '8'));
        CEGUI::Window::getPosition();
        CEGUI::Window::setPosition(pUVar16);
        CEGUI::Window::getSize();
                    /* try { // try from 00b993ae to 00b993b2 has its CatchHandler @ 00b9a09a */
        CEGUI::Window::setSize(pUVar16);
        *(UVector2 **)(pCVar20 + 0x16a0) = pUVar16;
        local_48c4 = local_48c4 + 1;
        pCVar20 = pCVar20 + 8;
      } while (local_48c4 != 0x40);
      iVar6 = 0;
      local_48b8 = this;
      do {
        iVar6 = iVar6 + 1;
                    /* try { // try from 00b993ec to 00b993f0 has its CatchHandler @ 00b9a724 */
        STRINGS::GetValueAsString((uint)local_288);
                    /* try { // try from 00b99406 to 00b9940a has its CatchHandler @ 00b9a09f */
        std::operator+((char *)local_298,(string *)0xfef7ca);
        local_4890 = 0x20;
        local_4888 = 0;
        local_4878 = 0;
        local_4880 = 0;
        local_47f0 = (undefined4 *)0x0;
        local_4898 = 0;
        local_4870[0] = 0;
        lVar8 = *(long *)(local_298[0] + -0x18);
                    /* try { // try from 00b9945e to 00b99462 has its CatchHandler @ 00b9a0b4 */
        CEGUI::String::grow((ulong)&local_4898);
        puVar19 = local_4870;
        if (0x20 < local_4890) {
          puVar19 = local_47f0;
        }
        puVar19[lVar8] = 0;
        lVar21 = lVar8;
        while (lVar21 != 0) {
          lVar21 = lVar21 + -1;
          puVar19 = local_4870;
          if (0x20 < local_4890) {
            puVar19 = local_47f0;
          }
          puVar19[lVar21] = (uint)*(byte *)(local_298[0] + lVar21);
        }
        local_4898 = lVar8;
                    /* try { // try from 00b994c2 to 00b994c6 has its CatchHandler @ 00b9a0c6 */
        lVar8 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x28));
                    /* try { // try from 00b994cd to 00b994d1 has its CatchHandler @ 00b9a0b4 */
        CEGUI::String::~String((String *)&local_4898);
        if ((allocator *)(local_298[0] + -0x18) !=
            (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_298[0] + -8);
          iVar7 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar7 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_298[0] + -0x18));
          }
        }
        if ((allocator *)(local_288[0] + -0x18) !=
            (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_288[0] + -8);
          iVar7 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar7 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_288[0] + -0x18));
          }
        }
        if (lVar8 == 0) {
          *(undefined8 *)(local_48b8 + 0x1040) = 0;
        }
        else {
          *(undefined1 *)(lVar8 + 0x213) = 0;
                    /* try { // try from 00b9951b to 00b99536 has its CatchHandler @ 00b9a724 */
          CEGUI::Window::setWantsMultiClickEvents(SUB81(lVar8,0));
          pcVar3 = *(code **)(*(long *)(lVar8 + 0x38) + 0x10);
          local_2a8[0] = operator_new(0x20);
          lVar21 = lVar8 + 0x38;
          *local_2a8[0] = &PTR__MemberFunctionSlot_00ff0850;
          local_2a8[0][2] = 0;
          local_2a8[0][1] = handle_SpellMouseOver;
          local_2a8[0][3] = this;
                    /* try { // try from 00b99576 to 00b995b1 has its CatchHandler @ 00b9a141 */
          (*pcVar3)(&local_538,lVar21,CEGUI::Window::EventMouseEnters,local_2a8);
          pBVar5 = local_538;
          if ((local_538 != (BoundSlot *)0x0) &&
             (iVar7 = *local_530, *local_530 = iVar7 + -1, iVar7 + -1 == 0)) {
            if (local_538 != (BoundSlot *)0x0) {
              CEGUI::BoundSlot::~BoundSlot(local_538);
              operator_delete(pBVar5);
            }
            operator_delete(local_530);
            local_538 = (BoundSlot *)0x0;
            local_530 = (int *)0x0;
          }
                    /* try { // try from 00b995e9 to 00b99604 has its CatchHandler @ 00b9a724 */
          CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_2a8);
          pcVar3 = *(code **)(*(long *)(lVar8 + 0x38) + 0x10);
          local_2b8[0] = operator_new(0x20);
          *local_2b8[0] = &PTR__MemberFunctionSlot_00ff0850;
          local_2b8[0][2] = 0;
          local_2b8[0][1] = handle_SpellMouseOver;
          local_2b8[0][3] = this;
                    /* try { // try from 00b99640 to 00b9967b has its CatchHandler @ 00b9a156 */
          (*pcVar3)(&local_548,lVar21,CEGUI::Window::EventMouseMove,local_2b8);
          pBVar5 = local_548;
          if ((local_548 != (BoundSlot *)0x0) &&
             (iVar7 = *local_540, *local_540 = iVar7 + -1, iVar7 + -1 == 0)) {
            if (local_548 != (BoundSlot *)0x0) {
              CEGUI::BoundSlot::~BoundSlot(local_548);
              operator_delete(pBVar5);
            }
            operator_delete(local_540);
            local_548 = (BoundSlot *)0x0;
            local_540 = (int *)0x0;
          }
                    /* try { // try from 00b996b3 to 00b996ce has its CatchHandler @ 00b9a724 */
          CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_2b8);
          pcVar3 = *(code **)(*(long *)(lVar8 + 0x38) + 0x10);
          local_2c8[0] = operator_new(0x20);
          *local_2c8[0] = &PTR__MemberFunctionSlot_00ff0850;
          local_2c8[0][2] = 0;
          local_2c8[0][1] = handle_SpellMouseOut;
          local_2c8[0][3] = this;
                    /* try { // try from 00b9970a to 00b99745 has its CatchHandler @ 00b9a16b */
          (*pcVar3)(&local_558,lVar21,CEGUI::Window::EventMouseLeaves,local_2c8);
          pBVar5 = local_558;
          if ((local_558 != (BoundSlot *)0x0) &&
             (iVar7 = *local_550, *local_550 = iVar7 + -1, iVar7 + -1 == 0)) {
            if (local_558 != (BoundSlot *)0x0) {
              CEGUI::BoundSlot::~BoundSlot(local_558);
              operator_delete(pBVar5);
            }
            operator_delete(local_550);
            local_558 = (BoundSlot *)0x0;
            local_550 = (int *)0x0;
          }
                    /* try { // try from 00b9977d to 00b99798 has its CatchHandler @ 00b9a724 */
          CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_2c8);
          pcVar3 = *(code **)(*(long *)(lVar8 + 0x38) + 0x10);
          local_2d8[0] = operator_new(0x20);
          *local_2d8[0] = &PTR__MemberFunctionSlot_00ff0850;
          local_2d8[0][2] = 0;
          local_2d8[0][1] = handle_SetSpell;
          local_2d8[0][3] = this;
                    /* try { // try from 00b997d4 to 00b9980a has its CatchHandler @ 00b9a180 */
          (*pcVar3)(&local_568,lVar21,CEGUI::Window::EventMouseButtonDown);
          pBVar5 = local_568;
          if ((local_568 != (BoundSlot *)0x0) &&
             (iVar7 = *local_560, *local_560 = iVar7 + -1, iVar7 + -1 == 0)) {
            if (local_568 != (BoundSlot *)0x0) {
              CEGUI::BoundSlot::~BoundSlot(local_568);
              operator_delete(pBVar5);
            }
            operator_delete(local_560);
            local_568 = (BoundSlot *)0x0;
            local_560 = (int *)0x0;
          }
                    /* try { // try from 00b99840 to 00b99866 has its CatchHandler @ 00b9a724 */
          CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_2d8);
          CEGUI::Window::setID((uint)lVar8);
          *(long *)(local_48b8 + 0x1040) = lVar8;
          CEGUI::Window::setID((uint)lVar8);
        }
        local_48b8 = local_48b8 + 8;
      } while (iVar6 != 2);
      pcVar3 = *(code **)(**(long **)(this + 0x9168) + 0x1a8);
                    /* try { // try from 00b99970 to 00b99974 has its CatchHandler @ 00b9a195 */
      std::string::string((string *)local_2e8,"PetWardrobeCam",&local_41);
                    /* try { // try from 00b99980 to 00b99981 has its CatchHandler @ 00b9a19a */
      uVar9 = (*pcVar3)(*(undefined8 *)(this + 0x9168),(string *)local_2e8);
      *(undefined8 *)(this + 0x9170) = uVar9;
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
      local_308 = 0;
      local_304 = 0x3f800000;
      local_300 = 0x40600000;
                    /* try { // try from 00b999d5 to 00b99a60 has its CatchHandler @ 00b9a724 */
      Ogre::Camera::setPosition(*(Vector3 **)(this + 0x9170));
      local_318 = 0;
      local_314 = 0x3f800000;
      local_310 = 0;
      Ogre::Camera::lookAt(*(Vector3 **)(this + 0x9170));
      (**(code **)(**(long **)(this + 0x9170) + 600))(DAT_00fa480c);
      (**(code **)(**(long **)(this + 0x9170) + 0x268))(DAT_00fb2bd8);
      uVar9 = *(undefined8 *)(*(long *)(this + 0x90) + 0x488);
      this_02 = (CRunicCore *)Ogre::NedAllocImpl::allocBytes(0x178,(char *)0x0,0,(char *)0x0);
      uVar4 = *(undefined8 *)(this + 0x90);
                    /* try { // try from 00b99a6f to 00b99a73 has its CatchHandler @ 00b9a1d6 */
      CRunicCore::CRunicCore(this_02);
      *(undefined ***)this_02 = &PTR__CSkillTooltip_00fe5f30;
      *(undefined8 *)(this_02 + 0x10) = uVar4;
                    /* try { // try from 00b99a89 to 00b99a8d has its CatchHandler @ 00b9a5a5 */
      std::wstring::wstring
                ((wstring_conflict *)(this_02 + 0x18),(wstring_conflict *)&::EMPTY_WSTRING);
      *(undefined4 *)(this_02 + 0x20) = 0xffffffff;
      *(undefined8 *)(this_02 + 0x28) = uVar9;
      *(CRunicCore **)(this + 0x91f0) = this_02;
                    /* try { // try from 00b99ab9 to 00b99abd has its CatchHandler @ 00b9a5b5 */
      std::wstring::wstring((wstring_conflict *)local_2f8,L"media/UI/skilltooltip.layout",&local_42)
      ;
                    /* try { // try from 00b99ad1 to 00b99ad5 has its CatchHandler @ 00b9a5ba */
      CSkillTooltip::load(*(CSkillTooltip **)(this + 0x91f0),*(undefined8 *)(this + 0x90),
                          (wstring_conflict *)local_2f8);
      if ((allocator *)(local_2f8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_2f8[0] + -8);
        iVar6 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar6 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_2f8[0] + -0x18));
        }
      }
      if ((allocator *)(local_5c8 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
      {
        LOCK();
        piVar1 = (int *)(local_5c8 + -8);
        iVar6 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar6 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_5c8 + -0x18));
        }
      }
      if ((allocator *)(local_5d8 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
         ) {
        LOCK();
        piVar1 = (int *)(local_5d8 + -8);
        iVar6 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar6 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_5d8 + -0x18));
        }
      }
      if ((allocator *)(local_5e0 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
      {
        LOCK();
        piVar1 = (int *)(local_5e0 + -8);
        iVar6 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar6 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_5e0 + -0x18));
        }
      }
      if ((allocator *)(local_5e8 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
      {
        LOCK();
        piVar1 = (int *)(local_5e8 + -8);
        iVar6 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar6 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_5e8 + -0x18));
        }
      }
      if (local_598 != (void *)0x0) {
        Ogre::NedAllocImpl::deallocBytes(local_598);
      }
      return;
    }
  } while( true );
}

/* address=00b9aa70
   symbol=CPetMenu::CPetMenu */

/* WARNING: Removing unreachable block (ram,0x00b9b088) */
/* WARNING: Removing unreachable block (ram,0x00b9affe) */
/* WARNING: Removing unreachable block (ram,0x00b9af88) */
/* CPetMenu::CPetMenu(CGameUI&, CSettings&, Ogre::RenderWindow*, Ogre::SceneManager*,
   Ogre::SceneManager*, CEGUI::Window*, CResourceManager*) */

void __thiscall
CPetMenu::CPetMenu(CPetMenu *this,CGameUI *param_1,CSettings *param_2,RenderWindow *param_3,
                  SceneManager *param_4,SceneManager *param_5,Window *param_6,
                  CResourceManager *param_7)

{
  int *piVar1;
  int iVar2;
  CSoundBankDataInformation *this_00;
  CSoundManager *pCVar3;
  long lVar4;
  CSoundBank *this_01;
  long local_68 [2];
  long local_58 [2];
  long local_48;
  allocator local_3b;
  allocator local_3a;
  allocator local_39 [9];

  CRunicCore::CRunicCore((CRunicCore *)this);
  *(CSettings **)(this + 0x88) = param_2;
  *(undefined ***)this = &PTR__CPetMenu_00ff06f0;
  *(undefined ***)(this + 0x10) = &PTR__CPetMenu_00ff07a0;
  *(undefined8 *)(this + 0x58) = 0;
  *(undefined8 *)(this + 0x60) = 0;
  *(Window **)(this + 0x18) = param_6;
  this[0x68] = (CPetMenu)0x0;
  lVar4 = 0;
  this[0x69] = (CPetMenu)0x1;
  this[0x6a] = (CPetMenu)0x0;
  *(undefined4 *)(this + 0x6c) = 0;
  *(undefined8 *)(this + 0x70) = 0;
  *(undefined4 *)(this + 0x78) = 0;
  *(undefined4 *)(this + 0x7c) = 0;
  *(undefined4 *)(this + 0x80) = 10;
  *(CGameUI **)(this + 0x90) = param_1;
  *(undefined4 *)(this + 0x98) = 0xffffffff;
  *(undefined4 *)(this + 0x9c) = 0xffffffff;
  *(undefined8 *)(this + 0x1370) = 0;
  do {
    *(undefined8 *)(this + lVar4 + 0x2050) = 0x20;
    *(undefined8 *)(this + lVar4 + 0x2058) = 0;
    *(undefined8 *)(this + lVar4 + 0x2068) = 0;
    *(undefined8 *)(this + lVar4 + 0x2060) = 0;
    *(undefined8 *)(this + lVar4 + 0x20f0) = 0;
    *(undefined8 *)(this + lVar4 + 0x2048) = 0;
    *(undefined4 *)(this + lVar4 + 0x2070) = 0;
    lVar4 = lVar4 + 0xb0;
  } while (lVar4 != 0x3860);
  lVar4 = 0;
  do {
    *(undefined8 *)(this + lVar4 + 0x58b0) = 0x20;
    *(undefined8 *)(this + lVar4 + 0x58b8) = 0;
    *(undefined8 *)(this + lVar4 + 0x58c8) = 0;
    *(undefined8 *)(this + lVar4 + 0x58c0) = 0;
    *(undefined8 *)(this + lVar4 + 0x5950) = 0;
    *(undefined8 *)(this + lVar4 + 0x58a8) = 0;
    *(undefined4 *)(this + lVar4 + 0x58d0) = 0;
    lVar4 = lVar4 + 0xb0;
  } while (lVar4 != 0x3860);
  *(SceneManager **)(this + 0x9160) = param_4;
  *(SceneManager **)(this + 0x9168) = param_5;
  *(RenderWindow **)(this + 0x9178) = param_3;
  *(undefined8 *)(this + 0x9180) = 0;
  this[0x9188] = (CPetMenu)0x0;
  *(CResourceManager **)(this + 0x91a8) = param_7;
  this[0x9189] = (CPetMenu)0x0;
  lVar4 = 0;
  *(undefined8 *)(this + 0x9190) = 0xffffffffffffffff;
  this[0x9198] = (CPetMenu)0x0;
  this[0x9199] = (CPetMenu)0x0;
  *(undefined8 *)(this + 0x91a0) = 0;
  *(undefined4 *)(this + 0x91b0) = 0;
  *(undefined4 *)(this + 0x91b4) = 0xc59c4000;
  *(undefined8 *)(this + 0x91b8) = 0;
  *(undefined8 *)(this + 0x91f0) = 0;
  *(undefined4 *)(this + 0x91fc) = 0;
  do {
    *(undefined8 *)(this + lVar4 + 0x9208) = 0x20;
    *(undefined8 *)(this + lVar4 + 0x9210) = 0;
    *(undefined8 *)(this + lVar4 + 0x9220) = 0;
    *(undefined8 *)(this + lVar4 + 0x9218) = 0;
    *(undefined8 *)(this + lVar4 + 0x92a8) = 0;
    *(undefined8 *)(this + lVar4 + 0x9200) = 0;
    *(undefined4 *)(this + lVar4 + 0x9228) = 0;
    lVar4 = lVar4 + 0xb0;
  } while (lVar4 != 0x210);
  lVar4 = 0;
  do {
    *(undefined8 *)(this + lVar4 + 0x9418) = 0x20;
    *(undefined8 *)(this + lVar4 + 0x9420) = 0;
    *(undefined8 *)(this + lVar4 + 0x9430) = 0;
    *(undefined8 *)(this + lVar4 + 0x9428) = 0;
    *(undefined8 *)(this + lVar4 + 0x94b8) = 0;
    *(undefined8 *)(this + lVar4 + 0x9410) = 0;
    *(undefined4 *)(this + lVar4 + 0x9438) = 0;
    lVar4 = lVar4 + 0xb0;
  } while (lVar4 != 0x210);
                    /* try { // try from 00b9ad56 to 00b9ad82 has its CatchHandler @ 00b9af00 */
  lVar4 = CMasterResourceManager::getSingleton();
  this_00 = *(CSoundBankDataInformation **)(lVar4 + 0x100);
  lVar4 = CMasterResourceManager::getSingleton();
  pCVar3 = *(CSoundManager **)(lVar4 + 0x98);
  this_01 = (CSoundBank *)Ogre::NedAllocImpl::allocBytes(0xd0,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00b9ad92 to 00b9ad96 has its CatchHandler @ 00b9b00e */
  CSoundBank::CSoundBank(this_01,pCVar3,false);
  *(CSoundBank **)(this + 0x91b8) = this_01;
                    /* try { // try from 00b9adb3 to 00b9adb7 has its CatchHandler @ 00b9b009 */
  std::wstring::wstring((wstring_conflict *)&local_48,L"STATSOPEN",local_39);
                    /* try { // try from 00b9adc0 to 00b9adc4 has its CatchHandler @ 00b9afec */
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
                    /* try { // try from 00b9adf1 to 00b9adf5 has its CatchHandler @ 00b9af00 */
    CSoundBank::addSample(*(CSoundBank **)(this + 0x91b8),0x16,*(longlong *)(lVar4 + 0x20));
  }
                    /* try { // try from 00b9ae05 to 00b9ae09 has its CatchHandler @ 00b9b032 */
  std::wstring::wstring((wstring_conflict *)local_58,L"STATSCLOSE",&local_3a);
                    /* try { // try from 00b9ae12 to 00b9ae16 has its CatchHandler @ 00b9b020 */
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
                    /* try { // try from 00b9ae44 to 00b9ae48 has its CatchHandler @ 00b9af00 */
    CSoundBank::addSample(*(CSoundBank **)(this + 0x91b8),0x42,*(longlong *)(lVar4 + 0x20));
  }
                    /* try { // try from 00b9ae58 to 00b9ae5c has its CatchHandler @ 00b9afb4 */
  std::wstring::wstring((wstring_conflict *)local_68,L"ERROR",&local_3b);
                    /* try { // try from 00b9ae65 to 00b9ae69 has its CatchHandler @ 00b9af5c */
  lVar4 = CSoundBankDataInformation::getSoundDataObject(this_00,(wstring_conflict *)local_68);
  if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_68[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
    }
  }
  if (lVar4 != 0) {
                    /* try { // try from 00b9ae97 to 00b9aed5 has its CatchHandler @ 00b9af00 */
    CSoundBank::addSample(*(CSoundBank **)(this + 0x91b8),0x18,*(longlong *)(lVar4 + 0x20));
  }
  CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0x88),KSETTINGS_RES_WIDTH);
  CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0x88),KSETTINGS_RES_HEIGHT);
  *(undefined4 *)(this + 0x91b0) = 0;
  createMenus(this);
  this[0x91f8] = (CPetMenu)0x0;
  this[0x91f9] = (CPetMenu)0x0;
  this[0x91fa] = (CPetMenu)0x0;
  return;
}

/* address=00b9b0d0
   symbol=CPetMenu::update */

/* WARNING: Removing unreachable block (ram,0x00ba0591) */
/* WARNING: Removing unreachable block (ram,0x00ba0e2e) */
/* WARNING: Removing unreachable block (ram,0x00ba0e47) */
/* WARNING: Removing unreachable block (ram,0x00ba0eb5) */
/* WARNING: Removing unreachable block (ram,0x00ba0f23) */
/* WARNING: Removing unreachable block (ram,0x00ba0d2e) */
/* WARNING: Removing unreachable block (ram,0x00ba0dbb) */
/* WARNING: Removing unreachable block (ram,0x00ba140a) */
/* WARNING: Removing unreachable block (ram,0x00ba1485) */
/* WARNING: Removing unreachable block (ram,0x00ba158a) */
/* WARNING: Removing unreachable block (ram,0x00ba15ec) */
/* WARNING: Removing unreachable block (ram,0x00ba1679) */
/* WARNING: Removing unreachable block (ram,0x00ba1278) */
/* WARNING: Removing unreachable block (ram,0x00ba12d2) */
/* WARNING: Removing unreachable block (ram,0x00ba10a0) */
/* WARNING: Removing unreachable block (ram,0x00ba0793) */
/* WARNING: Removing unreachable block (ram,0x00ba10ae) */
/* WARNING: Removing unreachable block (ram,0x00ba0964) */
/* WARNING: Removing unreachable block (ram,0x00ba10b9) */
/* WARNING: Removing unreachable block (ram,0x00ba0785) */
/* WARNING: Removing unreachable block (ram,0x00ba086b) */
/* WARNING: Removing unreachable block (ram,0x00ba0b97) */
/* WARNING: Removing unreachable block (ram,0x00ba09c4) */
/* WARNING: Removing unreachable block (ram,0x00ba08f3) */
/* WARNING: Removing unreachable block (ram,0x00b9fdbe) */
/* WARNING: Removing unreachable block (ram,0x00ba0a49) */
/* WARNING: Removing unreachable block (ram,0x00ba0be1) */
/* WARNING: Removing unreachable block (ram,0x00ba0aa2) */
/* WARNING: Removing unreachable block (ram,0x00ba0c1e) */
/* WARNING: Removing unreachable block (ram,0x00ba0adf) */
/* WARNING: Removing unreachable block (ram,0x00ba0b75) */
/* WARNING: Removing unreachable block (ram,0x00ba0aed) */
/* WARNING: Removing unreachable block (ram,0x00ba0b2d) */
/* WARNING: Removing unreachable block (ram,0x00ba0972) */
/* WARNING: Removing unreachable block (ram,0x00b9fff0) */
/* WARNING: Removing unreachable block (ram,0x00ba11ec) */
/* WARNING: Removing unreachable block (ram,0x00b9fffb) */
/* WARNING: Removing unreachable block (ram,0x00b9ff81) */
/* WARNING: Removing unreachable block (ram,0x00ba0103) */
/* WARNING: Removing unreachable block (ram,0x00ba0c37) */
/* WARNING: Removing unreachable block (ram,0x00ba00a8) */
/* WARNING: Removing unreachable block (ram,0x00ba015a) */
/* WARNING: Removing unreachable block (ram,0x00ba01b0) */
/* WARNING: Removing unreachable block (ram,0x00ba0bec) */
/* WARNING: Removing unreachable block (ram,0x00ba01bb) */
/* WARNING: Removing unreachable block (ram,0x00ba02c5) */
/* WARNING: Removing unreachable block (ram,0x00ba0320) */
/* WARNING: Removing unreachable block (ram,0x00ba07a1) */
/* WARNING: Removing unreachable block (ram,0x00ba0372) */
/* WARNING: Removing unreachable block (ram,0x00ba097d) */
/* WARNING: Removing unreachable block (ram,0x00ba067d) */
/* WARNING: Removing unreachable block (ram,0x00ba04b5) */
/* WARNING: Removing unreachable block (ram,0x00ba060a) */
/* WARNING: Removing unreachable block (ram,0x00ba0476) */
/* WARNING: Removing unreachable block (ram,0x00ba06ed) */
/* WARNING: Removing unreachable block (ram,0x00ba037d) */
/* WARNING: Removing unreachable block (ram,0x00ba0a01) */
/* WARNING: Removing unreachable block (ram,0x00ba0c29) */
/* WARNING: Removing unreachable block (ram,0x00ba02d0) */
/* WARNING: Removing unreachable block (ram,0x00ba0267) */
/* WARNING: Removing unreachable block (ram,0x00ba0ad4) */
/* WARNING: Removing unreachable block (ram,0x00ba0c45) */
/* WARNING: Removing unreachable block (ram,0x00ba0203) */
/* WARNING: Removing unreachable block (ram,0x00ba00b3) */
/* WARNING: Removing unreachable block (ram,0x00ba0a7b) */
/* WARNING: Removing unreachable block (ram,0x00ba0ba5) */
/* WARNING: Removing unreachable block (ram,0x00b9ff8c) */
/* WARNING: Removing unreachable block (ram,0x00ba0045) */
/* WARNING: Removing unreachable block (ram,0x00ba0a3e) */
/* WARNING: Removing unreachable block (ram,0x00ba0b38) */
/* WARNING: Removing unreachable block (ram,0x00b9fe93) */
/* WARNING: Removing unreachable block (ram,0x00b9fea1) */
/* WARNING: Removing unreachable block (ram,0x00ba0afb) */
/* WARNING: Removing unreachable block (ram,0x00ba11e1) */
/* WARNING: Removing unreachable block (ram,0x00ba0a86) */
/* WARNING: Removing unreachable block (ram,0x00ba11d6) */
/* WARNING: Removing unreachable block (ram,0x00ba11fa) */
/* WARNING: Removing unreachable block (ram,0x00ba1183) */
/* WARNING: Removing unreachable block (ram,0x00ba09cf) */
/* WARNING: Removing unreachable block (ram,0x00ba1178) */
/* WARNING: Removing unreachable block (ram,0x00ba0a0c) */
/* WARNING: Removing unreachable block (ram,0x00ba1125) */
/* WARNING: Removing unreachable block (ram,0x00b9fdc9) */
/* WARNING: Removing unreachable block (ram,0x00ba111a) */
/* WARNING: Removing unreachable block (ram,0x00b9fe85) */
/* WARNING: Removing unreachable block (ram,0x00ba10c7) */
/* WARNING: Removing unreachable block (ram,0x00ba08e8) */
/* WARNING: Removing unreachable block (ram,0x00ba0a94) */
/* WARNING: Removing unreachable block (ram,0x00ba098b) */
/* WARNING: Removing unreachable block (ram,0x00ba0876) */
/* WARNING: Removing unreachable block (ram,0x00ba1092) */
/* WARNING: Removing unreachable block (ram,0x00ba1283) */
/* WARNING: Removing unreachable block (ram,0x00ba1328) */
/* WARNING: Removing unreachable block (ram,0x00ba166e) */
/* WARNING: Removing unreachable block (ram,0x00ba1595) */
/* WARNING: Removing unreachable block (ram,0x00ba14dc) */
/* WARNING: Removing unreachable block (ram,0x00ba147a) */
/* WARNING: Removing unreachable block (ram,0x00ba13ff) */
/* WARNING: Removing unreachable block (ram,0x00ba0d39) */
/* WARNING: Removing unreachable block (ram,0x00ba0cb9) */
/* WARNING: Removing unreachable block (ram,0x00ba0f18) */
/* WARNING: Removing unreachable block (ram,0x00ba0eaa) */
/* WARNING: Removing unreachable block (ram,0x00ba0e3c) */
/* WARNING: Removing unreachable block (ram,0x00ba0540) */
/* WARNING: Removing unreachable block (ram,0x00ba0535) */
/* WARNING: Removing unreachable block (ram,0x00b9d982) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CPetMenu::update(float) */

void CPetMenu::update(float param_1)

{
  ulong uVar1;
  int *piVar2;
  undefined2 *puVar3;
  uint *puVar4;
  string sVar5;
  undefined1 *puVar6;
  code *pcVar7;
  CSkillManager *this;
  Window *pWVar8;
  undefined1 uVar9;
  string *psVar10;
  char cVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  CMasterResourceManager *this_00;
  short *psVar18;
  undefined *puVar19;
  uchar *puVar20;
  float *pfVar21;
  CSkill *pCVar22;
  undefined4 *puVar23;
  uint uVar24;
  ulong uVar25;
  long lVar26;
  long *plVar27;
  uint *puVar28;
  ulong uVar29;
  short *psVar30;
  uint uVar31;
  long lVar32;
  long *in_RDI;
  allocator *paVar33;
  undefined4 *puVar34;
  float *pfVar35;
  String *pSVar36;
  short sVar37;
  short sVar38;
  bool bVar39;
  byte bVar40;
  float fVar41;
  float fVar42;
  float fVar43;
  float fVar44;
  undefined8 extraout_XMM0_Qa;
  undefined8 extraout_XMM0_Qb;
  undefined1 auVar46 [16];
  float in_XMM1_Da;
  float fVar47;
  float fVar48;
  short *local_3658;
  int local_3650;
  short *local_3640;
  String local_3608 [176];
  String local_3558 [176];
  String local_34a8 [176];
  String local_33f8 [176];
  String local_3348 [176];
  String local_3298 [176];
  String local_31e8 [176];
  String local_3138 [176];
  String local_3088 [176];
  String local_2fd8 [176];
  String local_2f28 [176];
  String local_2e78 [176];
  String local_2dc8 [176];
  String local_2d18 [176];
  String local_2c68 [176];
  String local_2bb8 [176];
  String local_2b08 [176];
  String local_2a58 [176];
  String local_29a8 [176];
  String local_28f8 [176];
  String local_2848 [176];
  String local_2798 [176];
  String local_26e8 [176];
  String local_2638 [176];
  String local_2588 [176];
  String local_24d8 [176];
  String local_2428 [176];
  String local_2378 [176];
  String local_22c8 [176];
  String local_2218 [176];
  String local_2168 [176];
  String local_20b8 [176];
  String local_2008 [176];
  String local_1f58 [176];
  String local_1ea8 [176];
  String local_1df8 [176];
  String local_1d48 [176];
  String local_1c98 [176];
  String local_1be8 [176];
  String local_1b38 [176];
  String local_1a88 [176];
  String local_19d8 [176];
  String local_1928 [176];
  String local_1878 [176];
  String local_17c8 [176];
  String local_1718 [176];
  String local_1668 [176];
  String local_15b8 [176];
  String local_1508 [176];
  String local_1458 [176];
  String local_13a8 [176];
  String local_12f8 [176];
  String local_1248 [176];
  String local_1198 [176];
  String local_10e8 [176];
  String local_1038 [176];
  String local_f88 [176];
  String local_ed8 [176];
  String local_e28 [176];
  String local_d78 [176];
  String local_cc8 [176];
  String local_c18 [176];
  String local_b68 [176];
  String local_ab8 [176];
  String local_a08 [176];
  String local_958 [176];
  String local_8a8 [176];
  String local_7f8 [176];
  String local_748 [176];
  String local_698 [176];
  float local_5e8;
  float local_5e4;
  float local_5e0;
  float local_5dc;
  float local_5d8;
  float local_5d4;
  float local_5d0;
  float local_5cc;
  float local_5c8;
  float local_5c4;
  float local_5c0;
  float local_5bc;
  float local_5b8;
  float local_5b4;
  float local_5b0;
  float local_5ac;
  float local_5a8;
  float local_5a4;
  float local_5a0;
  float local_59c;
  float local_598;
  float local_594;
  float local_590;
  float local_58c;
  float local_588;
  float local_584;
  float local_580;
  float local_57c;
  float local_578;
  float local_574;
  float local_570;
  float local_56c;
  float local_568;
  float fStack_564;
  float local_560;
  float local_55c;
  float local_558;
  float local_554;
  float local_550;
  float local_54c;
  float local_548;
  float local_544;
  float local_540;
  float local_53c;
  float local_538;
  float local_534;
  float local_530;
  float local_52c;
  float local_528;
  float fStack_524;
  float local_520;
  float local_51c;
  float local_518;
  float local_514;
  float local_510;
  float local_50c;
  float local_508;
  float local_504;
  float local_500;
  float local_4fc;
  float local_4f8;
  float local_4f4;
  float local_4f0;
  float local_4ec;
  float local_4e8;
  float fStack_4e4;
  float local_4e0;
  float local_4dc;
  float local_4d8;
  float local_4d4;
  float local_4d0;
  float local_4cc;
  float local_4c8;
  float local_4c4;
  float local_4c0;
  float local_4bc;
  float local_4b8;
  float local_4b4;
  float local_4b0;
  float local_4ac;
  undefined4 local_4a8;
  float fStack_4a4;
  float local_4a0;
  float local_49c;
  float local_498;
  float local_494;
  float local_490;
  float local_48c;
  float local_488;
  float local_484;
  float local_480;
  float local_47c;
  float local_478;
  float local_474;
  float local_470;
  float local_46c;
  short *local_468;
  int local_460;
  undefined8 local_458;
  long *local_450;
  short *local_448;
  int local_440;
  undefined8 local_438;
  long *local_430;
  short *local_428;
  int local_420;
  undefined8 local_418;
  long *local_410;
  short *local_408;
  int local_400;
  undefined8 local_3f8;
  long *local_3f0;
  short *local_3e8;
  int local_3e0;
  undefined8 local_3d8;
  string *local_3d0;
  short *local_3c8;
  int local_3c0;
  undefined8 local_3b8;
  long *local_3b0;
  short *local_3a8;
  int local_3a0;
  undefined8 local_398;
  long *local_390;
  short *local_388;
  int local_380;
  undefined8 local_378;
  long *local_370;
  short *local_368;
  int local_360;
  undefined8 local_358;
  long *local_350;
  short *local_348;
  int local_340;
  undefined8 local_338;
  long *local_330;
  short *local_328;
  int local_320;
  undefined8 local_318;
  long *local_310;
  short *local_308;
  int local_300;
  undefined8 local_2f8;
  long *local_2f0;
  short *local_2e8;
  int local_2e0;
  undefined8 local_2d8;
  long *local_2d0;
  undefined4 local_2c8;
  float local_2c4;
  undefined4 local_2c0;
  uint local_2bc;
  undefined4 local_2b8;
  float local_2b4;
  undefined4 local_2b0;
  uint local_2ac;
  undefined8 local_2a8;
  float local_2a0;
  undefined8 local_298;
  float local_290;
  undefined8 local_288;
  float local_280;
  string local_268 [16];
  string local_258 [16];
  long local_248 [2];
  long local_238 [2];
  long local_228 [2];
  long local_218 [2];
  long local_208 [2];
  long local_1f8 [2];
  long local_1e8 [2];
  long local_1d8 [2];
  long local_1c8 [2];
  long local_1b8 [2];
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
  long local_108 [2];
  uchar *local_f8 [2];
  long local_e8 [2];
  long local_d8 [2];
  uchar *local_c8 [2];
  long local_b8 [2];
  uchar *local_a8 [2];
  uchar *local_98 [2];
  long local_88 [8];
  allocator local_44 [2];
  allocator local_42 [4];
  allocator local_3e;
  allocator local_3d;
  allocator local_3c;
  allocator local_3b;
  allocator local_3a;
  allocator local_39 [9];
  undefined1 auVar45 [16];

  bVar40 = 0;
  fVar41 = param_1 + *(float *)((long)in_RDI + 0x91fc);
  bVar39 = DAT_00fa47fc <= fVar41;
  *(float *)((long)in_RDI + 0x91fc) = fVar41;
  if (bVar39) {
    do {
      fVar41 = fVar41 - DAT_00fa47fc;
    } while (DAT_00fa47fc <= fVar41);
    *(float *)((long)in_RDI + 0x91fc) = fVar41;
  }
  uVar31 = 1;
  plVar27 = in_RDI;
  do {
    if ((char)plVar27[0x123f] == '\0') {
LAB_00b9b2a8:
      if (2 < uVar31) break;
    }
    else {
      local_3650 = (int)in_RDI;
      if ((int)plVar27 != local_3650) {
        if ((int)plVar27 - local_3650 == 1) {
          cVar11 = CEGUI::Window::isVisible(SUB81(in_RDI[0x1239],0));
          if (cVar11 != '\0') {
            pSVar36 = local_b68;
            *(undefined1 *)((long)in_RDI + 0x91f9) = 1;
            CEGUI::String::String(pSVar36,"UnselectedImage");
                    /* try { // try from 00b9f7cd to 00b9f7d1 has its CatchHandler @ 00ba0901 */
            CEGUI::PropertySet::setProperty((String *)in_RDI[0x123c],pSVar36);
            goto LAB_00b9d944;
          }
          if (*(float *)((long)in_RDI + 0x91fc) <= DAT_00fa4810) {
            CEGUI::String::String(local_e28,"UnselectedImage");
                    /* try { // try from 00b9fa2f to 00b9fa33 has its CatchHandler @ 00ba08bf */
            CEGUI::PropertySet::getProperty(local_ed8);
                    /* try { // try from 00b9fa3c to 00b9fa40 has its CatchHandler @ 00ba089f */
            cVar11 = CEGUI::operator!=(local_ed8,(String *)(in_RDI + 0x1256));
                    /* try { // try from 00b9fa47 to 00b9fa4b has its CatchHandler @ 00ba08bf */
            CEGUI::String::~String(local_ed8);
            CEGUI::String::~String(local_e28);
            if (cVar11 != '\0') {
              CEGUI::String::String(local_f88,"UnselectedImage");
                    /* try { // try from 00b9fa83 to 00b9fa87 has its CatchHandler @ 00ba088c */
              CEGUI::PropertySet::setProperty((String *)in_RDI[0x123c],local_f88);
              CEGUI::String::~String(local_f88);
            }
          }
          else {
            CEGUI::String::String(local_c18,"UnselectedImage");
                    /* try { // try from 00b9f5b4 to 00b9f5b8 has its CatchHandler @ 00b9ff05 */
            CEGUI::PropertySet::getProperty(local_cc8);
                    /* try { // try from 00b9f5c1 to 00b9f5c5 has its CatchHandler @ 00b9feea */
            cVar11 = CEGUI::operator!=(local_cc8,(String *)(in_RDI + 0x1298));
                    /* try { // try from 00b9f5d0 to 00b9f5d4 has its CatchHandler @ 00b9ff05 */
            CEGUI::String::~String(local_cc8);
            CEGUI::String::~String(local_c18);
            if (cVar11 != '\0') {
              pSVar36 = local_d78;
              CEGUI::String::String(pSVar36,"UnselectedImage");
                    /* try { // try from 00b9f614 to 00b9f618 has its CatchHandler @ 00b9fed7 */
              CEGUI::PropertySet::setProperty((String *)in_RDI[0x123c],pSVar36);
              goto LAB_00b9d85a;
            }
          }
        }
        else {
          cVar11 = CEGUI::Window::isVisible(SUB81(in_RDI[0x123a],0));
          if (cVar11 == '\0') {
            if (*(float *)((long)in_RDI + 0x91fc) <= DAT_00fa4810) {
              CEGUI::String::String(local_12f8,"UnselectedImage");
                    /* try { // try from 00b9fbad to 00b9fbb1 has its CatchHandler @ 00ba1382 */
              CEGUI::PropertySet::getProperty(local_13a8);
                    /* try { // try from 00b9fbbf to 00b9fbc3 has its CatchHandler @ 00ba135d */
              cVar11 = CEGUI::operator!=(local_13a8,(String *)(in_RDI + 0x126c));
                    /* try { // try from 00b9fbcf to 00b9fbd3 has its CatchHandler @ 00ba1382 */
              CEGUI::String::~String(local_13a8);
              CEGUI::String::~String(local_12f8);
              if (cVar11 != '\0') {
                CEGUI::String::String(local_1458,"UnselectedImage");
                    /* try { // try from 00b9fc15 to 00b9fc19 has its CatchHandler @ 00ba1345 */
                CEGUI::PropertySet::setProperty((String *)in_RDI[0x123d],local_1458);
                CEGUI::String::~String(local_1458);
              }
            }
            else {
              CEGUI::String::String(local_10e8,"UnselectedImage");
                    /* try { // try from 00b9b232 to 00b9b236 has its CatchHandler @ 00b9fcc8 */
              CEGUI::PropertySet::getProperty(local_1198);
                    /* try { // try from 00b9b244 to 00b9b248 has its CatchHandler @ 00ba0f6d */
              cVar11 = CEGUI::operator!=(local_1198,(String *)(in_RDI + 0x12ae));
                    /* try { // try from 00b9b254 to 00b9b258 has its CatchHandler @ 00b9fcc8 */
              CEGUI::String::~String(local_1198);
              CEGUI::String::~String(local_10e8);
              if (cVar11 != '\0') {
                CEGUI::String::String(local_1248,"UnselectedImage");
                    /* try { // try from 00b9b296 to 00b9b29a has its CatchHandler @ 00ba0f55 */
                CEGUI::PropertySet::setProperty((String *)in_RDI[0x123d],local_1248);
                CEGUI::String::~String(local_1248);
              }
            }
          }
          else {
            *(undefined1 *)((long)in_RDI + 0x91fa) = 1;
            CEGUI::String::String(local_1038,"UnselectedImage");
                    /* try { // try from 00b9f85c to 00b9f860 has its CatchHandler @ 00b9fe65 */
            CEGUI::PropertySet::setProperty((String *)in_RDI[0x123d],local_1038);
            CEGUI::String::~String(local_1038);
          }
        }
        goto LAB_00b9b2a8;
      }
      cVar11 = CEGUI::Window::isVisible(SUB81(in_RDI[0x1238],0));
      if (cVar11 == '\0') {
        if (*(float *)((long)in_RDI + 0x91fc) <= DAT_00fa4810) {
          CEGUI::String::String(local_958,"UnselectedImage");
                    /* try { // try from 00b9ed90 to 00b9ed94 has its CatchHandler @ 00ba099b */
          CEGUI::PropertySet::getProperty(local_a08);
                    /* try { // try from 00b9ed9d to 00b9eda1 has its CatchHandler @ 00ba0996 */
          cVar11 = CEGUI::operator!=(local_a08,(String *)(in_RDI + 0x1240));
                    /* try { // try from 00b9edac to 00b9edb0 has its CatchHandler @ 00ba099b */
          CEGUI::String::~String(local_a08);
          CEGUI::String::~String(local_958);
          if (cVar11 != '\0') {
            pSVar36 = local_ab8;
            CEGUI::String::String(pSVar36,"UnselectedImage");
                    /* try { // try from 00b9edf0 to 00b9edf4 has its CatchHandler @ 00ba0b6a */
            CEGUI::PropertySet::setProperty((String *)in_RDI[0x123b],pSVar36);
            goto LAB_00b9d85a;
          }
        }
        else {
          CEGUI::String::String(local_748,"UnselectedImage");
                    /* try { // try from 00b9d7f5 to 00b9d7f9 has its CatchHandler @ 00ba05b6 */
          CEGUI::PropertySet::getProperty(local_7f8);
                    /* try { // try from 00b9d802 to 00b9d806 has its CatchHandler @ 00ba05a9 */
          cVar11 = CEGUI::operator!=(local_7f8,(String *)(in_RDI + 0x1282));
                    /* try { // try from 00b9d811 to 00b9d815 has its CatchHandler @ 00ba05b6 */
          CEGUI::String::~String(local_7f8);
          CEGUI::String::~String(local_748);
          if (cVar11 != '\0') {
            pSVar36 = local_8a8;
            CEGUI::String::String(pSVar36,"UnselectedImage");
                    /* try { // try from 00b9d855 to 00b9d859 has its CatchHandler @ 00ba06c2 */
            CEGUI::PropertySet::setProperty((String *)in_RDI[0x123b],pSVar36);
LAB_00b9d85a:
            CEGUI::String::~String(pSVar36);
          }
        }
        goto LAB_00b9b2a8;
      }
      pSVar36 = local_698;
      *(undefined1 *)(in_RDI + 0x123f) = 1;
      CEGUI::String::String(pSVar36,"UnselectedImage");
                    /* try { // try from 00b9d93f to 00b9d943 has its CatchHandler @ 00ba059c */
      CEGUI::PropertySet::setProperty((String *)in_RDI[0x123b],pSVar36);
LAB_00b9d944:
      CEGUI::String::~String(pSVar36);
    }
    plVar27 = (long *)((long)plVar27 + 1);
    uVar31 = uVar31 + 1;
  } while( true );
  if ((((char)in_RDI[0xd] != '\0') && (in_RDI[0xb] != 0)) &&
     ((iVar12 = *(int *)(in_RDI[0xb] + 0x330), iVar12 == 0x29 || (iVar12 == 0x2a)))) {
    (**(code **)(*in_RDI + 0x40))(in_RDI,0);
  }
  iVar12 = CDynamicPropertyFile::GetInt((CDynamicPropertyFile *)in_RDI[0x11],KSETTINGS_RES_WIDTH);
  iVar13 = CDynamicPropertyFile::GetInt((CDynamicPropertyFile *)in_RDI[0x11],KSETTINGS_RES_HEIGHT);
  if ((char)in_RDI[0x1233] == '\0') {
    if (*(char *)((long)in_RDI + 0x9199) != '\0') {
      pfVar21 = (float *)(**(code **)(**(long **)(in_RDI[0xb] + 0x208) + 0xe8))();
      pfVar35 = &local_528;
      for (lVar32 = 0x10; lVar32 != 0; lVar32 = lVar32 + -1) {
        *pfVar35 = *pfVar21;
        pfVar21 = pfVar21 + (ulong)bVar40 * -2 + 1;
        pfVar35 = pfVar35 + (ulong)bVar40 * -2 + 1;
      }
      MATH::matrixRotationY((Matrix4 *)&local_568,param_1 * _DAT_00fefd64);
      local_5e8 = local_528 * local_568 + fStack_524 * local_558 + local_520 * local_548 +
                  local_51c * local_538;
      local_5e4 = local_528 * fStack_564 + fStack_524 * local_554 + local_520 * local_544 +
                  local_51c * local_534;
      local_5e0 = local_528 * local_560 + fStack_524 * local_550 + local_540 * local_520 +
                  local_530 * local_51c;
      local_5dc = local_528 * local_55c + fStack_524 * local_54c + local_520 * local_53c +
                  local_51c * local_52c;
      local_5d8 = local_568 * local_518 + local_558 * local_514 + local_548 * local_510 +
                  local_538 * local_50c;
      local_5d4 = fStack_564 * local_518 + local_554 * local_514 + local_544 * local_510 +
                  local_534 * local_50c;
      local_5d0 = local_560 * local_518 + local_550 * local_514 + local_540 * local_510 +
                  local_530 * local_50c;
      local_5cc = local_518 * local_55c + local_514 * local_54c + local_510 * local_53c +
                  local_50c * local_52c;
      local_5c8 = local_568 * local_508 + local_558 * local_504 + local_548 * local_500 +
                  local_538 * local_4fc;
      local_5c4 = fStack_564 * local_508 + local_554 * local_504 + local_544 * local_500 +
                  local_534 * local_4fc;
      local_5c0 = local_560 * local_508 + local_550 * local_504 + local_540 * local_500 +
                  local_530 * local_4fc;
      local_5bc = local_508 * local_55c + local_504 * local_54c + local_500 * local_53c +
                  local_4fc * local_52c;
      in_XMM1_Da = local_530 * local_4ec;
      local_5b8 = local_568 * local_4f8 + local_558 * local_4f4 + local_548 * local_4f0 +
                  local_538 * local_4ec;
      local_5b4 = fStack_564 * local_4f8 + local_554 * local_4f4 + local_544 * local_4f0 +
                  local_534 * local_4ec;
      local_5b0 = local_560 * local_4f8 + local_550 * local_4f4 + local_540 * local_4f0 + in_XMM1_Da
      ;
      local_5ac = local_4f8 * local_55c + local_4f4 * local_54c + local_4f0 * local_53c +
                  local_4ec * local_52c;
      pfVar21 = &local_5e8;
      pfVar35 = &local_528;
      for (lVar32 = 0x10; lVar32 != 0; lVar32 = lVar32 + -1) {
        *pfVar35 = *pfVar21;
        pfVar21 = pfVar21 + (ulong)bVar40 * -2 + 1;
        pfVar35 = pfVar35 + (ulong)bVar40 * -2 + 1;
      }
      (**(code **)(**(long **)(in_RDI[0xb] + 0x208) + 0x118))
                (*(long **)(in_RDI[0xb] + 0x208),&local_528,0);
    }
  }
  else {
    puVar23 = (undefined4 *)(**(code **)(**(long **)(in_RDI[0xb] + 0x208) + 0xe8))();
    puVar34 = &local_4a8;
    for (lVar32 = 0x10; lVar32 != 0; lVar32 = lVar32 + -1) {
      *puVar34 = *puVar23;
      puVar23 = puVar23 + (ulong)bVar40 * -2 + 1;
      puVar34 = puVar34 + (ulong)bVar40 * -2 + 1;
    }
    MATH::matrixRotationY((Matrix4 *)&local_4e8,param_1 * _DAT_00fefd60);
    local_5a8 = local_4a8 * local_4e8 + fStack_4a4 * local_4d8 + local_4a0 * local_4c8 +
                local_49c * local_4b8;
    local_5a4 = local_4a8 * fStack_4e4 + fStack_4a4 * local_4d4 + local_4a0 * local_4c4 +
                local_49c * local_4b4;
    local_5a0 = local_4a8 * local_4e0 + fStack_4a4 * local_4d0 + local_4c0 * local_4a0 +
                local_4b0 * local_49c;
    local_59c = local_4a8 * local_4dc + fStack_4a4 * local_4cc + local_4a0 * local_4bc +
                local_49c * local_4ac;
    local_598 = local_4e8 * local_498 + local_4d8 * local_494 + local_4c8 * local_490 +
                local_4b8 * local_48c;
    local_594 = fStack_4e4 * local_498 + local_4d4 * local_494 + local_4c4 * local_490 +
                local_4b4 * local_48c;
    local_590 = local_4e0 * local_498 + local_4d0 * local_494 + local_4c0 * local_490 +
                local_4b0 * local_48c;
    local_58c = local_498 * local_4dc + local_494 * local_4cc + local_490 * local_4bc +
                local_48c * local_4ac;
    local_588 = local_4e8 * local_488 + local_4d8 * local_484 + local_4c8 * local_480 +
                local_4b8 * local_47c;
    local_584 = fStack_4e4 * local_488 + local_4d4 * local_484 + local_4c4 * local_480 +
                local_4b4 * local_47c;
    local_580 = local_4e0 * local_488 + local_4d0 * local_484 + local_4c0 * local_480 +
                local_4b0 * local_47c;
    local_57c = local_488 * local_4dc + local_484 * local_4cc + local_480 * local_4bc +
                local_47c * local_4ac;
    in_XMM1_Da = local_4b0 * local_46c;
    local_578 = local_4e8 * local_478 + local_4d8 * local_474 + local_4c8 * local_470 +
                local_4b8 * local_46c;
    local_574 = fStack_4e4 * local_478 + local_4d4 * local_474 + local_4c4 * local_470 +
                local_4b4 * local_46c;
    local_570 = local_4e0 * local_478 + local_4d0 * local_474 + local_4c0 * local_470 + in_XMM1_Da;
    local_56c = local_478 * local_4dc + local_474 * local_4cc + local_470 * local_4bc +
                local_46c * local_4ac;
    pfVar21 = &local_5a8;
    pfVar35 = (float *)&local_4a8;
    for (lVar32 = 0x10; lVar32 != 0; lVar32 = lVar32 + -1) {
      *pfVar35 = *pfVar21;
      pfVar21 = pfVar21 + (ulong)bVar40 * -2 + 1;
      pfVar35 = pfVar35 + (ulong)bVar40 * -2 + 1;
    }
    (**(code **)(**(long **)(in_RDI[0xb] + 0x208) + 0x118))
              (*(long **)(in_RDI[0xb] + 0x208),&local_4a8,0);
  }
  if ((char)in_RDI[0xd] == '\0') {
    in_RDI[0x26e] = 0;
    CEGUI::Window::setVisible(SUB81(in_RDI[6],0));
    CEGUI::Window::setVisible(SUB81(in_RDI[8],0));
    if (((char)in_RDI[0xd] == '\0') && (*(char *)((long)in_RDI + 0x69) != '\0')) {
      if (in_RDI[0x123e] == 0) {
        return;
      }
      pWVar8 = *(Window **)(*(long *)(in_RDI[0x123e] + 0x30) + 0xb0);
      goto joined_r0x00b9dfea;
    }
  }
  if (in_RDI[0xb] != 0) {
    if ((update(float)::g_XP == '\0') &&
       (iVar14 = __cxa_guard_acquire(&update(float)::g_XP), iVar14 != 0)) {
      update(float)::g_XP = &DAT_01424558;
      __cxa_guard_release(&update(float)::g_XP);
      __cxa_atexit(std::wstring::~wstring,&update(float)::g_XP,&__dso_handle);
    }
    if (*(long *)(update(float)::g_XP + -6) == 0) {
      CStringTranslate::getSinglton();
      CStringTranslate::getTranslateString((wchar_t *)local_88);
                    /* try { // try from 00b9b3a4 to 00b9b3a8 has its CatchHandler @ 00ba05e7 */
      std::wstring::assign((wstring_conflict *)&update(float)::g_XP);
      if ((allocator *)(local_88[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_88[0] + -8);
        iVar14 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar14 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
        }
      }
    }
    STRINGS::GetValueAsString((uint)local_98);
                    /* try { // try from 00b9b3f9 to 00b9b3fd has its CatchHandler @ 00ba07e5 */
    cVar11 = CEGUI::operator!=((String *)(in_RDI[0x1224] + 0xc0),(string *)local_98);
    if (cVar11 != '\0') {
                    /* try { // try from 00b9d8d5 to 00b9d8d9 has its CatchHandler @ 00ba07e5 */
      CEGUI::String::String(local_1508,local_98[0]);
                    /* try { // try from 00b9d8e9 to 00b9d8ed has its CatchHandler @ 00ba05fa */
      CEGUI::Window::setText((String *)in_RDI[0x1224]);
                    /* try { // try from 00b9d8f1 to 00b9d8f5 has its CatchHandler @ 00ba07e5 */
      CEGUI::String::~String(local_1508);
    }
                    /* try { // try from 00b9b429 to 00b9b42d has its CatchHandler @ 00ba07b9 */
    std::wstring::wstring((wstring_conflict *)local_b8,*(wchar_t **)(in_RDI[0xb] + 0x4c0),local_39);
                    /* try { // try from 00b9b439 to 00b9b43d has its CatchHandler @ 00ba07c5 */
    STRINGS::StringConvertToUTF8((wstring_conflict *)local_a8);
    if ((allocator *)(local_b8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar2 = (int *)(local_b8[0] + -8);
      iVar14 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar14 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
      }
    }
                    /* try { // try from 00b9b472 to 00b9b4ab has its CatchHandler @ 00ba04ad */
    cVar11 = CEGUI::operator!=((String *)(in_RDI[0x1223] + 0xc0),(string *)local_a8);
    if (cVar11 != '\0') {
                    /* try { // try from 00b9d89c to 00b9d8a0 has its CatchHandler @ 00ba04ad */
      CEGUI::String::String(local_15b8,local_a8[0]);
                    /* try { // try from 00b9d8b0 to 00b9d8b4 has its CatchHandler @ 00ba06b2 */
      CEGUI::Window::setText((String *)in_RDI[0x1223]);
                    /* try { // try from 00b9d8b8 to 00b9d8bc has its CatchHandler @ 00ba04ad */
      CEGUI::String::~String(local_15b8);
    }
    iVar14 = *(int *)(in_RDI[0xb] + 0x100);
    this_00 = (CMasterResourceManager *)CMasterResourceManager::getSingleton();
    iVar14 = CMasterResourceManager::experienceGate(this_00,iVar14);
    STRINGS::GetValueAsString((STRINGS *)local_e8,iVar14);
    local_3c8 = &DAT_01426458;
    local_3b0 = (long *)0x0;
    local_3c0 = 0;
    local_3b8 = 0;
                    /* try { // try from 00b9b4eb to 00b9b4ef has its CatchHandler @ 00ba04c0 */
    Ogre::UTFString::assign((UTFString *)&local_3c8,(string *)local_e8);
    local_388 = &DAT_01426458;
    local_370 = (long *)0x0;
    local_380 = 0;
    local_378 = 0;
                    /* try { // try from 00b9b537 to 00b9b53b has its CatchHandler @ 00ba0415 */
    std::string::string((string *)&local_4a8,"/",local_42);
                    /* try { // try from 00b9b551 to 00b9b555 has its CatchHandler @ 00ba0434 */
    Ogre::UTFString::assign((UTFString *)&local_388,(string *)&local_4a8);
    paVar33 = (allocator *)(CONCAT44(fStack_4a4,local_4a8) + -0x18);
    if (paVar33 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(CONCAT44(fStack_4a4,local_4a8) + -8);
      iVar14 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar14 < 1) {
        std::string::_Rep::_M_destroy(paVar33);
      }
    }
                    /* try { // try from 00b9b586 to 00b9b58a has its CatchHandler @ 00ba046e */
    STRINGS::GetValueAsString((STRINGS *)local_d8,*(int *)(in_RDI[0xb] + 0x448));
    local_348 = &DAT_01426458;
    local_330 = (long *)0x0;
    local_340 = 0;
    local_338 = 0;
                    /* try { // try from 00b9b5ca to 00b9b5ce has its CatchHandler @ 00ba0688 */
    Ogre::UTFString::assign((UTFString *)&local_348,(string *)local_d8);
    local_308 = &DAT_01426458;
    local_2f0 = (long *)0x0;
    local_300 = 0;
    local_2f8 = 0;
                    /* try { // try from 00b9b60e to 00b9b612 has its CatchHandler @ 00ba069d */
    std::string::string((string *)&local_4a8,":",local_44);
                    /* try { // try from 00b9b628 to 00b9b62c has its CatchHandler @ 00ba0615 */
    Ogre::UTFString::assign((UTFString *)&local_308,(string *)&local_4a8);
    paVar33 = (allocator *)(CONCAT44(fStack_4a4,local_4a8) + -0x18);
    if (paVar33 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(CONCAT44(fStack_4a4,local_4a8) + -8);
      iVar14 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar14 < 1) {
        std::string::_Rep::_M_destroy(paVar33);
      }
    }
    local_2e8 = &DAT_01426458;
    local_2d0 = (long *)0x0;
    local_2e0 = 0;
    local_2d8 = 0;
                    /* try { // try from 00b9b692 to 00b9b7a1 has its CatchHandler @ 00ba065b */
    std::
    basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>::
    _M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
               *)&local_2e8,0,
              std::
              basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
              ::_Rep::_S_empty_rep_storage,0);
    std::
    basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>::
    reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
             *)&local_2e8,*(ulong *)(update(float)::g_XP + -6));
    puVar4 = update(float)::g_XP + *(long *)(update(float)::g_XP + -6);
    if (update(float)::g_XP != puVar4) {
      sVar38 = 0;
      puVar28 = update(float)::g_XP;
      do {
        uVar31 = *puVar28;
        lVar32 = 1;
        sVar37 = (short)uVar31;
        if (0xffff < uVar31) {
          lVar32 = 2;
          sVar38 = ((ushort)(uVar31 - 0x10000) & 0x3ff) + 0xdc00;
          sVar37 = ((ushort)(uVar31 - 0x10000 >> 10) & 0x3ff) + 0xd800;
        }
        lVar26 = *(long *)(local_2e8 + -0xc);
        uVar25 = lVar26 + 1;
        if ((*(ulong *)(local_2e8 + -8) < uVar25) || (0 < *(int *)(local_2e8 + -4))) {
          std::
          basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
          ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                     *)&local_2e8,uVar25);
          lVar26 = *(long *)(local_2e8 + -0xc);
        }
        local_2e8[lVar26] = sVar37;
        if (local_2e8 != &DAT_01426458) {
          local_2e8[-4] = 0;
          local_2e8[-3] = 0;
          *(ulong *)(local_2e8 + -0xc) = uVar25;
          local_2e8[uVar25] = 0;
        }
        if (lVar32 == 2) {
          lVar32 = *(long *)(local_2e8 + -0xc);
          uVar25 = lVar32 + 1;
          if ((*(ulong *)(local_2e8 + -8) < uVar25) || (0 < *(int *)(local_2e8 + -4))) {
            std::
            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
            ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                       *)&local_2e8,uVar25);
            lVar32 = *(long *)(local_2e8 + -0xc);
          }
          local_2e8[lVar32] = sVar38;
          if (local_2e8 != &DAT_01426458) {
            local_2e8[-4] = 0;
            local_2e8[-3] = 0;
            *(ulong *)(local_2e8 + -0xc) = uVar25;
            local_2e8[uVar25] = 0;
          }
        }
        puVar28 = puVar28 + 1;
      } while (puVar4 != puVar28);
    }
    local_408 = &DAT_01426458;
    local_3f0 = (long *)0x0;
    local_400 = 0;
    local_3f8 = 0;
    psVar30 = local_408;
    if (local_2e8 != &DAT_01426458) {
      if (*(int *)(local_2e8 + -4) < 0) {
                    /* try { // try from 00b9f892 to 00b9f896 has its CatchHandler @ 00ba0030 */
        psVar30 = (short *)std::
                           basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                           ::_Rep::_M_clone((_Rep *)(local_2e8 + -0xc),(allocator *)&local_4a8,0);
        psVar18 = local_408 + -0xc;
      }
      else {
        if ((_Rep *)(local_2e8 + -0xc) !=
            (_Rep *)&std::
                     basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                     ::_Rep::_S_empty_rep_storage) {
          LOCK();
          *(int *)(local_2e8 + -4) = *(int *)(local_2e8 + -4) + 1;
          UNLOCK();
        }
        psVar18 = (short *)&std::
                            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                            ::_Rep::_S_empty_rep_storage;
        psVar30 = local_2e8;
      }
      if ((ulong *)psVar18 !=
          &std::
           basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
           ::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(psVar18 + 8);
        iVar14 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar14 < 1) {
          operator_delete(psVar18);
        }
      }
    }
    local_408 = psVar30;
    lVar32 = *(long *)(local_308 + -0xc);
    if (lVar32 != 0) {
      lVar26 = *(long *)(local_408 + -0xc);
      uVar25 = lVar26 + lVar32;
      if ((*(ulong *)(local_408 + -8) < uVar25) || (0 < *(int *)(local_408 + -4))) {
                    /* try { // try from 00b9b887 to 00b9b88b has its CatchHandler @ 00ba05ae */
        std::
        basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
        ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                   *)&local_408,uVar25);
        lVar26 = *(long *)(local_408 + -0xc);
      }
      if (lVar32 == 1) {
        local_408[lVar26] = *local_308;
      }
      else {
        memmove(local_408 + lVar26,local_308,lVar32 * 2);
      }
      if (local_408 != &DAT_01426458) {
        local_408[-4] = 0;
        local_408[-3] = 0;
        *(ulong *)(local_408 + -0xc) = uVar25;
        local_408[uVar25] = 0;
      }
    }
    local_328 = &DAT_01426458;
    local_310 = (long *)0x0;
    local_320 = 0;
    local_318 = 0;
    psVar30 = local_328;
    if (local_408 != &DAT_01426458) {
      if (*(int *)(local_408 + -4) < 0) {
                    /* try { // try from 00b9f96e to 00b9f972 has its CatchHandler @ 00ba03b1 */
        psVar30 = (short *)std::
                           basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                           ::_Rep::_M_clone((_Rep *)(local_408 + -0xc),(allocator *)&local_4a8,0);
        psVar18 = local_328 + -0xc;
      }
      else {
        if ((_Rep *)(local_408 + -0xc) !=
            (_Rep *)&std::
                     basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                     ::_Rep::_S_empty_rep_storage) {
          LOCK();
          *(int *)(local_408 + -4) = *(int *)(local_408 + -4) + 1;
          UNLOCK();
        }
        psVar18 = (short *)&std::
                            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                            ::_Rep::_S_empty_rep_storage;
        psVar30 = local_408;
      }
      if ((ulong *)psVar18 !=
          &std::
           basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
           ::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(psVar18 + 8);
        iVar14 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar14 < 1) {
          operator_delete(psVar18);
        }
      }
    }
    local_328 = psVar30;
    plVar27 = local_3f0;
    if (local_3f0 != (long *)0x0) {
      if (local_400 == 2) {
        if (local_3f0 != (long *)0x0) {
          paVar33 = (allocator *)(*local_3f0 + -0x18);
          if (paVar33 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(*local_3f0 + -8);
            iVar14 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar14 < 1) {
              std::wstring::_Rep::_M_destroy(paVar33);
            }
          }
          goto LAB_00b9eeb1;
        }
      }
      else if (local_400 == 3) {
        if (local_3f0 != (long *)0x0) {
          puVar3 = (undefined2 *)(*local_3f0 + -0x18);
          if (puVar3 != &std::
                         basic_string<unsigned_int,std::char_traits<unsigned_int>,std::allocator<unsigned_int>>
                         ::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(*local_3f0 + -8);
            iVar14 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar14 < 1) {
              operator_delete(puVar3);
            }
          }
          goto LAB_00b9eeb1;
        }
      }
      else if ((local_400 == 1) && (local_3f0 != (long *)0x0)) {
        paVar33 = (allocator *)(*local_3f0 + -0x18);
        if (paVar33 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar2 = (int *)(*local_3f0 + -8);
          iVar14 = *piVar2;
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (iVar14 < 1) {
            std::string::_Rep::_M_destroy(paVar33);
          }
        }
LAB_00b9eeb1:
        operator_delete(plVar27);
      }
      local_3f0 = (long *)0x0;
      local_3f8 = 0;
    }
    if ((ulong *)(local_408 + -0xc) !=
        &std::
         basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
         ::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_408 + -4);
      iVar14 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar14 < 1) {
        operator_delete(local_408 + -0xc);
      }
    }
    local_428 = &DAT_01426458;
    local_410 = (long *)0x0;
    local_420 = 0;
    local_418 = 0;
    psVar30 = local_428;
    if (local_328 != &DAT_01426458) {
      if (*(int *)(local_328 + -4) < 0) {
                    /* try { // try from 00b9f914 to 00b9f918 has its CatchHandler @ 00ba0145 */
        psVar30 = (short *)std::
                           basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                           ::_Rep::_M_clone((_Rep *)(local_328 + -0xc),(allocator *)&local_4a8,0);
        psVar18 = local_428 + -0xc;
      }
      else {
        if ((_Rep *)(local_328 + -0xc) !=
            (_Rep *)&std::
                     basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                     ::_Rep::_S_empty_rep_storage) {
          LOCK();
          *(int *)(local_328 + -4) = *(int *)(local_328 + -4) + 1;
          UNLOCK();
        }
        psVar18 = (short *)&std::
                            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                            ::_Rep::_S_empty_rep_storage;
        psVar30 = local_328;
      }
      if ((ulong *)psVar18 !=
          &std::
           basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
           ::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(psVar18 + 8);
        iVar14 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar14 < 1) {
          operator_delete(psVar18);
        }
      }
    }
    local_428 = psVar30;
    lVar32 = *(long *)(local_348 + -0xc);
    if (lVar32 != 0) {
      lVar26 = *(long *)(local_428 + -0xc);
      uVar25 = lVar26 + lVar32;
      if ((*(ulong *)(local_428 + -8) < uVar25) || (0 < *(int *)(local_428 + -4))) {
                    /* try { // try from 00b9ba5e to 00b9ba62 has its CatchHandler @ 00ba021a */
        std::
        basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
        ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                   *)&local_428,uVar25);
        lVar26 = *(long *)(local_428 + -0xc);
      }
      if (lVar32 == 1) {
        local_428[lVar26] = *local_348;
      }
      else {
        memmove(local_428 + lVar26,local_348,lVar32 * 2);
      }
      if (local_428 != &DAT_01426458) {
        local_428[-4] = 0;
        local_428[-3] = 0;
        *(ulong *)(local_428 + -0xc) = uVar25;
        local_428[uVar25] = 0;
      }
    }
    local_368 = &DAT_01426458;
    local_350 = (long *)0x0;
    local_360 = 0;
    local_358 = 0;
    psVar30 = local_368;
    if (local_428 != &DAT_01426458) {
      if (*(int *)(local_428 + -4) < 0) {
                    /* try { // try from 00b9f950 to 00b9f954 has its CatchHandler @ 00ba0394 */
        psVar30 = (short *)std::
                           basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                           ::_Rep::_M_clone((_Rep *)(local_428 + -0xc),(allocator *)&local_4a8,0);
        psVar18 = local_368 + -0xc;
      }
      else {
        if ((_Rep *)(local_428 + -0xc) !=
            (_Rep *)&std::
                     basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                     ::_Rep::_S_empty_rep_storage) {
          LOCK();
          *(int *)(local_428 + -4) = *(int *)(local_428 + -4) + 1;
          UNLOCK();
        }
        psVar18 = (short *)&std::
                            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                            ::_Rep::_S_empty_rep_storage;
        psVar30 = local_428;
      }
      if ((ulong *)psVar18 !=
          &std::
           basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
           ::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(psVar18 + 8);
        iVar14 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar14 < 1) {
          operator_delete(psVar18);
        }
      }
    }
    local_368 = psVar30;
    plVar27 = local_410;
    if (local_410 != (long *)0x0) {
      if (local_420 == 2) {
        if (local_410 != (long *)0x0) {
          paVar33 = (allocator *)(*local_410 + -0x18);
          if (paVar33 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(*local_410 + -8);
            iVar14 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar14 < 1) {
              std::wstring::_Rep::_M_destroy(paVar33);
            }
          }
          goto LAB_00b9ef2e;
        }
      }
      else if (local_420 == 3) {
        if (local_410 != (long *)0x0) {
          puVar3 = (undefined2 *)(*local_410 + -0x18);
          if (puVar3 != &std::
                         basic_string<unsigned_int,std::char_traits<unsigned_int>,std::allocator<unsigned_int>>
                         ::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(*local_410 + -8);
            iVar14 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar14 < 1) {
              operator_delete(puVar3);
            }
          }
          goto LAB_00b9ef2e;
        }
      }
      else if ((local_420 == 1) && (local_410 != (long *)0x0)) {
        paVar33 = (allocator *)(*local_410 + -0x18);
        if (paVar33 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar2 = (int *)(*local_410 + -8);
          iVar14 = *piVar2;
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (iVar14 < 1) {
            std::string::_Rep::_M_destroy(paVar33);
          }
        }
LAB_00b9ef2e:
        operator_delete(plVar27);
      }
      local_410 = (long *)0x0;
      local_418 = 0;
    }
    if ((ulong *)(local_428 + -0xc) !=
        &std::
         basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
         ::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_428 + -4);
      iVar14 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar14 < 1) {
        operator_delete(local_428 + -0xc);
      }
    }
    local_448 = &DAT_01426458;
    local_430 = (long *)0x0;
    local_440 = 0;
    local_438 = 0;
    psVar30 = local_448;
    if (local_368 != &DAT_01426458) {
      if (*(int *)(local_368 + -4) < 0) {
                    /* try { // try from 00b9f8d8 to 00b9f8dc has its CatchHandler @ 00ba00ee */
        psVar30 = (short *)std::
                           basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                           ::_Rep::_M_clone((_Rep *)(local_368 + -0xc),(allocator *)&local_4a8,0);
        psVar18 = local_448 + -0xc;
      }
      else {
        if ((_Rep *)(local_368 + -0xc) !=
            (_Rep *)&std::
                     basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                     ::_Rep::_S_empty_rep_storage) {
          LOCK();
          *(int *)(local_368 + -4) = *(int *)(local_368 + -4) + 1;
          UNLOCK();
        }
        psVar18 = (short *)&std::
                            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                            ::_Rep::_S_empty_rep_storage;
        psVar30 = local_368;
      }
      if ((ulong *)psVar18 !=
          &std::
           basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
           ::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(psVar18 + 8);
        iVar14 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar14 < 1) {
          operator_delete(psVar18);
        }
      }
    }
    local_448 = psVar30;
    lVar32 = *(long *)(local_388 + -0xc);
    if (lVar32 != 0) {
      lVar26 = *(long *)(local_448 + -0xc);
      uVar25 = lVar26 + lVar32;
      if ((*(ulong *)(local_448 + -8) < uVar25) || (0 < *(int *)(local_448 + -4))) {
                    /* try { // try from 00b9bc2a to 00b9bc2e has its CatchHandler @ 00ba010e */
        std::
        basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
        ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                   *)&local_448,uVar25);
        lVar26 = *(long *)(local_448 + -0xc);
      }
      if (lVar32 == 1) {
        local_448[lVar26] = *local_388;
      }
      else {
        memmove(local_448 + lVar26,local_388,lVar32 * 2);
      }
      if (local_448 != &DAT_01426458) {
        local_448[-4] = 0;
        local_448[-3] = 0;
        *(ulong *)(local_448 + -0xc) = uVar25;
        local_448[uVar25] = 0;
      }
    }
    local_3a8 = &DAT_01426458;
    local_390 = (long *)0x0;
    local_3a0 = 0;
    local_398 = 0;
    psVar30 = local_3a8;
    if (local_448 != &DAT_01426458) {
      if (*(int *)(local_448 + -4) < 0) {
                    /* try { // try from 00b9f932 to 00b9f936 has its CatchHandler @ 00ba024a */
        psVar30 = (short *)std::
                           basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                           ::_Rep::_M_clone((_Rep *)(local_448 + -0xc),(allocator *)&local_4a8,0);
        psVar18 = local_3a8 + -0xc;
      }
      else {
        if ((_Rep *)(local_448 + -0xc) !=
            (_Rep *)&std::
                     basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                     ::_Rep::_S_empty_rep_storage) {
          LOCK();
          *(int *)(local_448 + -4) = *(int *)(local_448 + -4) + 1;
          UNLOCK();
        }
        psVar18 = (short *)&std::
                            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                            ::_Rep::_S_empty_rep_storage;
        psVar30 = local_448;
      }
      if ((ulong *)psVar18 !=
          &std::
           basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
           ::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(psVar18 + 8);
        iVar14 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar14 < 1) {
          operator_delete(psVar18);
        }
      }
    }
    local_3a8 = psVar30;
    plVar27 = local_430;
    if (local_430 != (long *)0x0) {
      if (local_440 == 2) {
        if (local_430 != (long *)0x0) {
          paVar33 = (allocator *)(*local_430 + -0x18);
          if (paVar33 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(*local_430 + -8);
            iVar14 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar14 < 1) {
              std::wstring::_Rep::_M_destroy(paVar33);
            }
          }
          goto LAB_00b9f054;
        }
      }
      else if (local_440 == 3) {
        if (local_430 != (long *)0x0) {
          puVar3 = (undefined2 *)(*local_430 + -0x18);
          if (puVar3 != &std::
                         basic_string<unsigned_int,std::char_traits<unsigned_int>,std::allocator<unsigned_int>>
                         ::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(*local_430 + -8);
            iVar14 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar14 < 1) {
              operator_delete(puVar3);
            }
          }
          goto LAB_00b9f054;
        }
      }
      else if ((local_440 == 1) && (local_430 != (long *)0x0)) {
        paVar33 = (allocator *)(*local_430 + -0x18);
        if (paVar33 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar2 = (int *)(*local_430 + -8);
          iVar14 = *piVar2;
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (iVar14 < 1) {
            std::string::_Rep::_M_destroy(paVar33);
          }
        }
LAB_00b9f054:
        operator_delete(plVar27);
      }
      local_430 = (long *)0x0;
      local_438 = 0;
    }
    if ((ulong *)(local_448 + -0xc) !=
        &std::
         basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
         ::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_448 + -4);
      iVar14 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar14 < 1) {
        operator_delete(local_448 + -0xc);
      }
    }
    local_468 = &DAT_01426458;
    local_450 = (long *)0x0;
    local_460 = 0;
    local_458 = 0;
    psVar30 = local_468;
    if (local_3a8 != &DAT_01426458) {
      if (*(int *)(local_3a8 + -4) < 0) {
                    /* try { // try from 00b9f8f6 to 00b9f8fa has its CatchHandler @ 00ba030b */
        psVar30 = (short *)std::
                           basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                           ::_Rep::_M_clone((_Rep *)(local_3a8 + -0xc),(allocator *)&local_4a8,0);
        psVar18 = local_468 + -0xc;
      }
      else {
        if ((_Rep *)(local_3a8 + -0xc) !=
            (_Rep *)&std::
                     basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                     ::_Rep::_S_empty_rep_storage) {
          LOCK();
          *(int *)(local_3a8 + -4) = *(int *)(local_3a8 + -4) + 1;
          UNLOCK();
        }
        psVar18 = (short *)&std::
                            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                            ::_Rep::_S_empty_rep_storage;
        psVar30 = local_3a8;
      }
      if ((ulong *)psVar18 !=
          &std::
           basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
           ::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(psVar18 + 8);
        iVar14 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar14 < 1) {
          operator_delete(psVar18);
        }
      }
    }
    local_468 = psVar30;
    lVar32 = *(long *)(local_3c8 + -0xc);
    if (lVar32 != 0) {
      lVar26 = *(long *)(local_468 + -0xc);
      uVar25 = lVar26 + lVar32;
      if ((*(ulong *)(local_468 + -8) < uVar25) || (0 < *(int *)(local_468 + -4))) {
                    /* try { // try from 00b9bdf3 to 00b9bdf7 has its CatchHandler @ 00b9ff2a */
        std::
        basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
        ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                   *)&local_468,uVar25);
        lVar26 = *(long *)(local_468 + -0xc);
      }
      if (lVar32 == 1) {
        local_468[lVar26] = *local_3c8;
      }
      else {
        memmove(local_468 + lVar26,local_3c8,lVar32 * 2);
      }
      if (local_468 != &DAT_01426458) {
        local_468[-4] = 0;
        local_468[-3] = 0;
        *(ulong *)(local_468 + -0xc) = uVar25;
        local_468[uVar25] = 0;
      }
    }
    local_3e8 = &DAT_01426458;
    local_3d0 = (string *)0x0;
    local_3e0 = 0;
    local_3d8 = 0;
    psVar30 = local_3e8;
    if (local_468 != &DAT_01426458) {
      if (*(int *)(local_468 + -4) < 0) {
                    /* try { // try from 00b9f8b5 to 00b9f8b9 has its CatchHandler @ 00ba01e6 */
        psVar30 = (short *)std::
                           basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                           ::_Rep::_M_clone((_Rep *)(local_468 + -0xc),(allocator *)&local_4a8,0);
        local_3658 = local_3e8 + -0xc;
      }
      else {
        if ((_Rep *)(local_468 + -0xc) !=
            (_Rep *)&std::
                     basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                     ::_Rep::_S_empty_rep_storage) {
          LOCK();
          *(int *)(local_468 + -4) = *(int *)(local_468 + -4) + 1;
          UNLOCK();
        }
        local_3658 = (short *)&std::
                               basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                               ::_Rep::_S_empty_rep_storage;
        psVar30 = local_468;
      }
      if ((ulong *)local_3658 !=
          &std::
           basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
           ::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_3658 + 8);
        iVar14 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar14 < 1) {
          operator_delete(local_3658);
        }
      }
    }
    local_3e8 = psVar30;
    plVar27 = local_450;
    if (local_450 != (long *)0x0) {
      if (local_460 == 2) {
        if (local_450 != (long *)0x0) {
          paVar33 = (allocator *)(*local_450 + -0x18);
          if (paVar33 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(*local_450 + -8);
            iVar14 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar14 < 1) {
              std::wstring::_Rep::_M_destroy(paVar33);
            }
          }
          goto LAB_00b9ee34;
        }
      }
      else if (local_460 == 3) {
        if (local_450 != (long *)0x0) {
          puVar3 = (undefined2 *)(*local_450 + -0x18);
          if (puVar3 != &std::
                         basic_string<unsigned_int,std::char_traits<unsigned_int>,std::allocator<unsigned_int>>
                         ::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(*local_450 + -8);
            iVar14 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar14 < 1) {
              operator_delete(puVar3);
            }
          }
          goto LAB_00b9ee34;
        }
      }
      else if ((local_460 == 1) && (local_450 != (long *)0x0)) {
        paVar33 = (allocator *)(*local_450 + -0x18);
        if (paVar33 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar2 = (int *)(*local_450 + -8);
          iVar14 = *piVar2;
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (iVar14 < 1) {
            std::string::_Rep::_M_destroy(paVar33);
          }
        }
LAB_00b9ee34:
        operator_delete(plVar27);
      }
      local_450 = (long *)0x0;
      local_458 = 0;
    }
    if ((ulong *)(local_468 + -0xc) !=
        &std::
         basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
         ::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_468 + -4);
      iVar14 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar14 < 1) {
        operator_delete(local_468 + -0xc);
      }
    }
    psVar10 = local_3d0;
    if (local_3e0 != 1) {
      if (local_3d0 != (string *)0x0) {
        if (local_3e0 == 2) {
          if (local_3d0 != (string *)0x0) {
            paVar33 = (allocator *)(*(long *)local_3d0 + -0x18);
            if (paVar33 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar2 = (int *)(*(long *)local_3d0 + -8);
              iVar14 = *piVar2;
              *piVar2 = *piVar2 + -1;
              UNLOCK();
              if (iVar14 < 1) {
                std::wstring::_Rep::_M_destroy(paVar33);
              }
            }
            goto LAB_00b9f128;
          }
        }
        else if (local_3e0 == 3) {
          if (local_3d0 != (string *)0x0) {
            puVar3 = (undefined2 *)(*(long *)local_3d0 + -0x18);
            if (puVar3 != &std::
                           basic_string<unsigned_int,std::char_traits<unsigned_int>,std::allocator<unsigned_int>>
                           ::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar2 = (int *)(*(long *)local_3d0 + -8);
              iVar14 = *piVar2;
              *piVar2 = *piVar2 + -1;
              UNLOCK();
              if (iVar14 < 1) {
                operator_delete(puVar3);
              }
            }
            goto LAB_00b9f128;
          }
        }
        else if ((local_3e0 == 1) && (local_3d0 != (string *)0x0)) {
          paVar33 = (allocator *)(*(long *)local_3d0 + -0x18);
          if (paVar33 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(*(long *)local_3d0 + -8);
            iVar14 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar14 < 1) {
              std::string::_Rep::_M_destroy(paVar33);
            }
          }
LAB_00b9f128:
          operator_delete(psVar10);
        }
        local_3d0 = (string *)0x0;
        local_3d8 = 0;
      }
                    /* try { // try from 00b9bf66 to 00b9c2a4 has its CatchHandler @ 00b9fdd7 */
      local_3d0 = operator_new(8);
      *(undefined1 **)local_3d0 = &DAT_01423a38;
      local_3e0 = 1;
    }
    std::string::_M_mutate((ulong)local_3d0,0,*(ulong *)(*(long *)local_3d0 + -0x18));
    psVar10 = local_3d0;
    std::string::reserve((ulong)local_3d0);
    iVar14 = *(int *)(local_3e8 + -4);
    psVar30 = local_3e8 + -0xc;
    if (iVar14 < 0) {
      local_3640 = local_3e8 + *(long *)(local_3e8 + -0xc);
    }
    else {
      if ((ulong *)psVar30 ==
          &std::
           basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
           ::_Rep::_S_empty_rep_storage) {
        psVar30 = (short *)&std::
                            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                            ::_Rep::_S_empty_rep_storage;
        local_3640 = local_3e8 +
                     std::
                     basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                     ::_Rep::_S_empty_rep_storage;
      }
      else {
        if (iVar14 != 0) {
          std::
          basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
          ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                       *)&local_3e8,0,0,0);
          psVar30 = local_3e8 + -0xc;
        }
        psVar30[8] = -1;
        psVar30[9] = -1;
        psVar30 = local_3e8 + -0xc;
        local_3640 = local_3e8 + *(long *)(local_3e8 + -0xc);
        iVar14 = *(int *)(local_3e8 + -4);
        if (iVar14 < 0) goto LAB_00b9c089;
      }
      if ((ulong *)psVar30 !=
          &std::
           basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
           ::_Rep::_S_empty_rep_storage) {
        if (iVar14 != 0) {
          std::
          basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
          ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                       *)&local_3e8,0,0,0);
        }
        local_3e8[-4] = -1;
        local_3e8[-3] = -1;
      }
    }
LAB_00b9c089:
    if (local_3640 != local_3e8) {
      plVar27 = (long *)(local_3e8 + -0xc);
      local_3658 = local_3e8;
      do {
        if ((-1 < (int)plVar27[2]) &&
           ((ulong *)plVar27 !=
            &std::
             basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
             ::_Rep::_S_empty_rep_storage)) {
          if ((int)plVar27[2] != 0) {
            std::
            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
            ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                         *)&local_3e8,0,0,0);
            plVar27 = (long *)(local_3e8 + -0xc);
          }
          *(undefined4 *)(plVar27 + 2) = 0xffffffff;
        }
        lVar32 = (long)local_3658 - (long)local_3e8 >> 1;
        uVar31 = (ushort)local_3e8[lVar32] + 0x2800;
        if ((((ushort)uVar31 < 0x400) &&
            (uVar25 = lVar32 + 1, uVar25 < *(ulong *)(local_3e8 + -0xc))) &&
           ((ushort)(local_3e8[uVar25] + 0x2400U) < 0x400)) {
          uVar31 = ((ushort)(local_3e8[uVar25] + 0x2400U) & 0x3ff | (uVar31 & 0x3ff) << 10) +
                   0x10000;
        }
        else {
          uVar31 = (uint)(ushort)local_3e8[lVar32];
        }
        uVar25 = 1;
        if ((uVar31 & 0x3ffff80) == 0) {
switchD_00b9d9af_caseD_0:
          local_4a8 = (float)(CONCAT31(local_4a8._1_3_,(char)uVar31) & 0xffffff7f);
        }
        else {
          lVar32 = 1;
          uVar25 = 2;
          uVar24 = uVar31;
          if ((uVar31 & 0x3fff800) != 0) {
            lVar32 = 2;
            uVar25 = 3;
            if ((uVar31 & 0x3ff0000) != 0) {
              lVar32 = 3;
              uVar25 = 4;
            }
          }
          do {
            uVar31 = uVar24 >> 6;
            ((string *)&local_4a8)[lVar32] = (string)((byte)uVar24 & 0x3f | 0x80);
            lVar32 = lVar32 + -1;
            uVar24 = uVar31;
          } while (lVar32 != 0);
          uVar9 = (undefined1)uVar31;
          switch(uVar25) {
          default:
            goto switchD_00b9d9af_caseD_0;
          case 2:
            local_4a8 = (float)(CONCAT31(local_4a8._1_3_,uVar9) & 0xffffff1f | 0xc0);
            break;
          case 3:
            local_4a8 = (float)(CONCAT31(local_4a8._1_3_,uVar9) & 0xffffff0f | 0xe0);
            break;
          case 4:
            local_4a8 = (float)(CONCAT31(local_4a8._1_3_,uVar9) & 0xffffff07 | 0xf0);
            break;
          case 5:
            local_4a8 = (float)(CONCAT31(local_4a8._1_3_,uVar9) & 0xffffff03 | 0xf8);
            break;
          case 6:
            local_4a8 = (float)(CONCAT31(local_4a8._1_3_,uVar9) & 0xffffff01 | 0xfc);
          }
        }
        uVar29 = 0;
        do {
          lVar32 = *(long *)psVar10;
          sVar5 = ((string *)&local_4a8)[uVar29];
          lVar26 = *(long *)(lVar32 + -0x18);
          uVar1 = lVar26 + 1;
          if ((*(ulong *)(lVar32 + -0x10) < uVar1) || (0 < *(int *)(lVar32 + -8))) {
            std::string::reserve((ulong)psVar10);
            lVar32 = *(long *)psVar10;
            lVar26 = *(long *)(lVar32 + -0x18);
          }
          *(string *)(lVar32 + lVar26) = sVar5;
          puVar6 = *(undefined1 **)psVar10;
          if (puVar6 != &DAT_01423a38) {
            *(undefined4 *)(puVar6 + -8) = 0;
            *(ulong *)(puVar6 + -0x18) = uVar1;
            puVar6[uVar1] = 0;
          }
          uVar29 = uVar29 + 1;
        } while (uVar29 < uVar25);
        plVar27 = (long *)(local_3e8 + -0xc);
        if ((-1 < *(int *)(local_3e8 + -4)) &&
           ((ulong *)plVar27 !=
            &std::
             basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
             ::_Rep::_S_empty_rep_storage)) {
          if (*(int *)(local_3e8 + -4) != 0) {
            std::
            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
            ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                         *)&local_3e8,0,0,0);
            plVar27 = (long *)(local_3e8 + -0xc);
          }
          *(undefined4 *)(plVar27 + 2) = 0xffffffff;
          plVar27 = (long *)(local_3e8 + -0xc);
        }
        psVar30 = local_3658 + 1;
        if (((psVar30 != local_3e8 + *plVar27) && ((ushort)(local_3658[1] + 0x2400U) < 0x400)) &&
           ((ushort)(*local_3658 + 0x2800U) < 0x400)) {
          psVar30 = local_3658 + 2;
        }
        local_3658 = psVar30;
      } while (psVar30 != local_3640);
    }
    std::string::string((string *)local_c8,local_3d0);
    psVar10 = local_3d0;
    if (local_3d0 != (string *)0x0) {
      if (local_3e0 == 2) {
        if (local_3d0 != (string *)0x0) {
          paVar33 = (allocator *)(*(long *)local_3d0 + -0x18);
          if (paVar33 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(*(long *)local_3d0 + -8);
            iVar14 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar14 < 1) {
              std::wstring::_Rep::_M_destroy(paVar33);
            }
          }
          goto LAB_00b9ea54;
        }
      }
      else if (local_3e0 == 3) {
        if (local_3d0 != (string *)0x0) {
          puVar3 = (undefined2 *)(*(long *)local_3d0 + -0x18);
          if (puVar3 != &std::
                         basic_string<unsigned_int,std::char_traits<unsigned_int>,std::allocator<unsigned_int>>
                         ::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(*(long *)local_3d0 + -8);
            iVar14 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar14 < 1) {
              operator_delete(puVar3);
            }
          }
          goto LAB_00b9ea54;
        }
      }
      else if ((local_3e0 == 1) && (local_3d0 != (string *)0x0)) {
        paVar33 = (allocator *)(*(long *)local_3d0 + -0x18);
        if (paVar33 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar2 = (int *)(*(long *)local_3d0 + -8);
          iVar14 = *piVar2;
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (iVar14 < 1) {
            std::string::_Rep::_M_destroy(paVar33);
          }
        }
LAB_00b9ea54:
        operator_delete(psVar10);
      }
      local_3d0 = (string *)0x0;
      local_3d8 = 0;
    }
    if ((ulong *)(local_3e8 + -0xc) !=
        &std::
         basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
         ::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_3e8 + -4);
      iVar14 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar14 < 1) {
        operator_delete(local_3e8 + -0xc);
      }
    }
    plVar27 = local_390;
    if (local_390 != (long *)0x0) {
      if (local_3a0 == 2) {
        if (local_390 != (long *)0x0) {
          paVar33 = (allocator *)(*local_390 + -0x18);
          if (paVar33 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(*local_390 + -8);
            iVar14 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar14 < 1) {
              std::wstring::_Rep::_M_destroy(paVar33);
            }
          }
          goto LAB_00b9e9d7;
        }
      }
      else if (local_3a0 == 3) {
        if (local_390 != (long *)0x0) {
          puVar3 = (undefined2 *)(*local_390 + -0x18);
          if (puVar3 != &std::
                         basic_string<unsigned_int,std::char_traits<unsigned_int>,std::allocator<unsigned_int>>
                         ::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(*local_390 + -8);
            iVar14 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar14 < 1) {
              operator_delete(puVar3);
            }
          }
          goto LAB_00b9e9d7;
        }
      }
      else if ((local_3a0 == 1) && (local_390 != (long *)0x0)) {
        paVar33 = (allocator *)(*local_390 + -0x18);
        if (paVar33 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar2 = (int *)(*local_390 + -8);
          iVar14 = *piVar2;
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (iVar14 < 1) {
            std::string::_Rep::_M_destroy(paVar33);
          }
        }
LAB_00b9e9d7:
        operator_delete(plVar27);
      }
      local_390 = (long *)0x0;
      local_398 = 0;
    }
    if ((ulong *)(local_3a8 + -0xc) !=
        &std::
         basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
         ::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_3a8 + -4);
      iVar14 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar14 < 1) {
        operator_delete(local_3a8 + -0xc);
      }
    }
    plVar27 = local_350;
    if (local_350 != (long *)0x0) {
      if (local_360 == 2) {
        if (local_350 != (long *)0x0) {
          paVar33 = (allocator *)(*local_350 + -0x18);
          if (paVar33 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(*local_350 + -8);
            iVar14 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar14 < 1) {
              std::wstring::_Rep::_M_destroy(paVar33);
            }
          }
          goto LAB_00b9ead1;
        }
      }
      else if (local_360 == 3) {
        if (local_350 != (long *)0x0) {
          puVar3 = (undefined2 *)(*local_350 + -0x18);
          if (puVar3 != &std::
                         basic_string<unsigned_int,std::char_traits<unsigned_int>,std::allocator<unsigned_int>>
                         ::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(*local_350 + -8);
            iVar14 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar14 < 1) {
              operator_delete(puVar3);
            }
          }
          goto LAB_00b9ead1;
        }
      }
      else if ((local_360 == 1) && (local_350 != (long *)0x0)) {
        paVar33 = (allocator *)(*local_350 + -0x18);
        if (paVar33 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar2 = (int *)(*local_350 + -8);
          iVar14 = *piVar2;
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (iVar14 < 1) {
            std::string::_Rep::_M_destroy(paVar33);
          }
        }
LAB_00b9ead1:
        operator_delete(plVar27);
      }
      local_350 = (long *)0x0;
      local_358 = 0;
    }
    if ((ulong *)(local_368 + -0xc) !=
        &std::
         basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
         ::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_368 + -4);
      iVar14 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar14 < 1) {
        operator_delete(local_368 + -0xc);
      }
    }
    plVar27 = local_310;
    if (local_310 != (long *)0x0) {
      if (local_320 == 2) {
        if (local_310 != (long *)0x0) {
          paVar33 = (allocator *)(*local_310 + -0x18);
          if (paVar33 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(*local_310 + -8);
            iVar14 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar14 < 1) {
              std::wstring::_Rep::_M_destroy(paVar33);
            }
          }
          goto LAB_00b9ebeb;
        }
      }
      else if (local_320 == 3) {
        if (local_310 != (long *)0x0) {
          puVar3 = (undefined2 *)(*local_310 + -0x18);
          if (puVar3 != &std::
                         basic_string<unsigned_int,std::char_traits<unsigned_int>,std::allocator<unsigned_int>>
                         ::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(*local_310 + -8);
            iVar14 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar14 < 1) {
              operator_delete(puVar3);
            }
          }
          goto LAB_00b9ebeb;
        }
      }
      else if ((local_320 == 1) && (local_310 != (long *)0x0)) {
        paVar33 = (allocator *)(*local_310 + -0x18);
        if (paVar33 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar2 = (int *)(*local_310 + -8);
          iVar14 = *piVar2;
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (iVar14 < 1) {
            std::string::_Rep::_M_destroy(paVar33);
          }
        }
LAB_00b9ebeb:
        operator_delete(plVar27);
      }
      local_310 = (long *)0x0;
      local_318 = 0;
    }
    if ((ulong *)(local_328 + -0xc) !=
        &std::
         basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
         ::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_328 + -4);
      iVar14 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar14 < 1) {
        operator_delete(local_328 + -0xc);
      }
    }
    plVar27 = local_2d0;
    if (local_2d0 != (long *)0x0) {
      if (local_2e0 == 2) {
        if (local_2d0 != (long *)0x0) {
          paVar33 = (allocator *)(*local_2d0 + -0x18);
          if (paVar33 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(*local_2d0 + -8);
            iVar14 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar14 < 1) {
              std::wstring::_Rep::_M_destroy(paVar33);
            }
          }
          goto LAB_00b9f1ee;
        }
      }
      else if (local_2e0 == 3) {
        if (local_2d0 != (long *)0x0) {
          puVar3 = (undefined2 *)(*local_2d0 + -0x18);
          if (puVar3 != &std::
                         basic_string<unsigned_int,std::char_traits<unsigned_int>,std::allocator<unsigned_int>>
                         ::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(*local_2d0 + -8);
            iVar14 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar14 < 1) {
              operator_delete(puVar3);
            }
          }
          goto LAB_00b9f1ee;
        }
      }
      else if ((local_2e0 == 1) && (local_2d0 != (long *)0x0)) {
        paVar33 = (allocator *)(*local_2d0 + -0x18);
        if (paVar33 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar2 = (int *)(*local_2d0 + -8);
          iVar14 = *piVar2;
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (iVar14 < 1) {
            std::string::_Rep::_M_destroy(paVar33);
          }
        }
LAB_00b9f1ee:
        operator_delete(plVar27);
      }
      local_2d0 = (long *)0x0;
      local_2d8 = 0;
    }
    if ((ulong *)(local_2e8 + -0xc) !=
        &std::
         basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
         ::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_2e8 + -4);
      iVar14 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar14 < 1) {
        operator_delete(local_2e8 + -0xc);
      }
    }
    plVar27 = local_2f0;
    if (local_2f0 != (long *)0x0) {
      if (local_300 == 2) {
        if (local_2f0 != (long *)0x0) {
          paVar33 = (allocator *)(*local_2f0 + -0x18);
          if (paVar33 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(*local_2f0 + -8);
            iVar14 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar14 < 1) {
              std::wstring::_Rep::_M_destroy(paVar33);
            }
          }
          goto LAB_00b9ed09;
        }
      }
      else if (local_300 == 3) {
        if (local_2f0 != (long *)0x0) {
          puVar3 = (undefined2 *)(*local_2f0 + -0x18);
          if (puVar3 != &std::
                         basic_string<unsigned_int,std::char_traits<unsigned_int>,std::allocator<unsigned_int>>
                         ::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(*local_2f0 + -8);
            iVar14 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar14 < 1) {
              operator_delete(puVar3);
            }
          }
          goto LAB_00b9ed09;
        }
      }
      else if ((local_300 == 1) && (local_2f0 != (long *)0x0)) {
        paVar33 = (allocator *)(*local_2f0 + -0x18);
        if (paVar33 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar2 = (int *)(*local_2f0 + -8);
          iVar14 = *piVar2;
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (iVar14 < 1) {
            std::string::_Rep::_M_destroy(paVar33);
          }
        }
LAB_00b9ed09:
        operator_delete(plVar27);
      }
      local_2f0 = (long *)0x0;
      local_2f8 = 0;
    }
    if ((ulong *)(local_308 + -0xc) !=
        &std::
         basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
         ::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_308 + -4);
      iVar14 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar14 < 1) {
        operator_delete(local_308 + -0xc);
      }
    }
    plVar27 = local_330;
    if (local_330 != (long *)0x0) {
      if (local_340 == 2) {
        if (local_330 != (long *)0x0) {
          paVar33 = (allocator *)(*local_330 + -0x18);
          if (paVar33 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(*local_330 + -8);
            iVar14 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar14 < 1) {
              std::wstring::_Rep::_M_destroy(paVar33);
            }
          }
          goto LAB_00b9f26b;
        }
      }
      else if (local_340 == 3) {
        if (local_330 != (long *)0x0) {
          puVar3 = (undefined2 *)(*local_330 + -0x18);
          if (puVar3 != &std::
                         basic_string<unsigned_int,std::char_traits<unsigned_int>,std::allocator<unsigned_int>>
                         ::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(*local_330 + -8);
            iVar14 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar14 < 1) {
              operator_delete(puVar3);
            }
          }
          goto LAB_00b9f26b;
        }
      }
      else if ((local_340 == 1) && (local_330 != (long *)0x0)) {
        paVar33 = (allocator *)(*local_330 + -0x18);
        if (paVar33 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar2 = (int *)(*local_330 + -8);
          iVar14 = *piVar2;
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (iVar14 < 1) {
            std::string::_Rep::_M_destroy(paVar33);
          }
        }
LAB_00b9f26b:
        operator_delete(plVar27);
      }
      local_330 = (long *)0x0;
      local_338 = 0;
    }
    if ((ulong *)(local_348 + -0xc) !=
        &std::
         basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
         ::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_348 + -4);
      iVar14 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar14 < 1) {
        operator_delete(local_348 + -0xc);
      }
    }
    if ((allocator *)(local_d8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar2 = (int *)(local_d8[0] + -8);
      iVar14 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar14 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
      }
    }
    plVar27 = local_370;
    if (local_370 != (long *)0x0) {
      if (local_380 == 2) {
        if (local_370 != (long *)0x0) {
          paVar33 = (allocator *)(*local_370 + -0x18);
          if (paVar33 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(*local_370 + -8);
            iVar14 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar14 < 1) {
              std::wstring::_Rep::_M_destroy(paVar33);
            }
          }
          goto LAB_00b9f385;
        }
      }
      else if (local_380 == 3) {
        if (local_370 != (long *)0x0) {
          puVar3 = (undefined2 *)(*local_370 + -0x18);
          if (puVar3 != &std::
                         basic_string<unsigned_int,std::char_traits<unsigned_int>,std::allocator<unsigned_int>>
                         ::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(*local_370 + -8);
            iVar14 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar14 < 1) {
              operator_delete(puVar3);
            }
          }
          goto LAB_00b9f385;
        }
      }
      else if ((local_380 == 1) && (local_370 != (long *)0x0)) {
        paVar33 = (allocator *)(*local_370 + -0x18);
        if (paVar33 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar2 = (int *)(*local_370 + -8);
          iVar14 = *piVar2;
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (iVar14 < 1) {
            std::string::_Rep::_M_destroy(paVar33);
          }
        }
LAB_00b9f385:
        operator_delete(plVar27);
      }
      local_370 = (long *)0x0;
      local_378 = 0;
    }
    if ((ulong *)(local_388 + -0xc) !=
        &std::
         basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
         ::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_388 + -4);
      iVar14 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar14 < 1) {
        operator_delete(local_388 + -0xc);
      }
    }
    plVar27 = local_3b0;
    if (local_3b0 != (long *)0x0) {
      if (local_3c0 == 2) {
        if (local_3b0 != (long *)0x0) {
          paVar33 = (allocator *)(*local_3b0 + -0x18);
          if (paVar33 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(*local_3b0 + -8);
            iVar14 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar14 < 1) {
              std::wstring::_Rep::_M_destroy(paVar33);
            }
          }
          goto LAB_00b9f458;
        }
      }
      else if (local_3c0 == 3) {
        if (local_3b0 != (long *)0x0) {
          puVar3 = (undefined2 *)(*local_3b0 + -0x18);
          if (puVar3 != &std::
                         basic_string<unsigned_int,std::char_traits<unsigned_int>,std::allocator<unsigned_int>>
                         ::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(*local_3b0 + -8);
            iVar14 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar14 < 1) {
              operator_delete(puVar3);
            }
          }
          goto LAB_00b9f458;
        }
      }
      else if ((local_3c0 == 1) && (local_3b0 != (long *)0x0)) {
        paVar33 = (allocator *)(*local_3b0 + -0x18);
        if (paVar33 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar2 = (int *)(*local_3b0 + -8);
          iVar14 = *piVar2;
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (iVar14 < 1) {
            std::string::_Rep::_M_destroy(paVar33);
          }
        }
LAB_00b9f458:
        operator_delete(plVar27);
      }
      local_3b0 = (long *)0x0;
      local_3b8 = 0;
    }
    if ((ulong *)(local_3c8 + -0xc) !=
        &std::
         basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
         ::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_3c8 + -4);
      iVar14 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar14 < 1) {
        operator_delete(local_3c8 + -0xc);
      }
    }
    if ((allocator *)(local_e8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar2 = (int *)(local_e8[0] + -8);
      iVar14 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar14 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
      }
    }
                    /* try { // try from 00b9c630 to 00b9c650 has its CatchHandler @ 00ba0fba */
    cVar11 = CEGUI::operator!=((String *)(in_RDI[0x122b] + 0xc0),(string *)local_c8);
    if (cVar11 != '\0') {
      CEGUI::String::String(local_1668,local_c8[0]);
                    /* try { // try from 00b9c660 to 00b9c664 has its CatchHandler @ 00ba0faa */
      CEGUI::Window::setText((String *)in_RDI[0x122b]);
                    /* try { // try from 00b9c668 to 00b9c6b4 has its CatchHandler @ 00ba0fba */
      CEGUI::String::~String(local_1668);
    }
    iVar14 = CCharacter::maximumDamageForDisplay((CCharacter *)in_RDI[0xb],true,false,true);
    iVar15 = CCharacter::maximumDamageForDisplay((CCharacter *)in_RDI[0xb],true,false,false);
    STRINGS::GetValueAsString((STRINGS *)local_128,iVar15);
                    /* try { // try from 00b9c6c7 to 00b9c6dd has its CatchHandler @ 00ba0f95 */
    iVar16 = CCharacter::minimumDamageForDisplay((CCharacter *)in_RDI[0xb],true,false,false);
    STRINGS::GetValueAsString((STRINGS *)local_108,iVar16);
                    /* try { // try from 00b9c6ec to 00b9c6f0 has its CatchHandler @ 00ba12df */
    std::string::string((string *)local_118,(string *)local_108);
                    /* try { // try from 00b9c6fe to 00b9c702 has its CatchHandler @ 00ba12dd */
    std::string::append((char *)local_118,0x103f694);
                    /* try { // try from 00b9c711 to 00b9c715 has its CatchHandler @ 00ba12ba */
    std::operator+((string *)local_f8,(string *)local_118);
    if ((allocator *)(local_118[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar2 = (int *)(local_118[0] + -8);
      iVar16 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar16 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_118[0] + -0x18));
      }
    }
    if ((allocator *)(local_108[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar2 = (int *)(local_108[0] + -8);
      iVar16 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar16 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_108[0] + -0x18));
      }
    }
    if ((allocator *)(local_128[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar2 = (int *)(local_128[0] + -8);
      iVar16 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar16 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_128[0] + -0x18));
      }
    }
                    /* try { // try from 00b9c77f to 00b9c7a3 has its CatchHandler @ 00ba1218 */
    cVar11 = CEGUI::operator!=((String *)(in_RDI[0x1225] + 0xc0),(string *)local_f8);
    if (cVar11 != '\0') {
      CEGUI::String::String(local_1718,local_f8[0]);
                    /* try { // try from 00b9c7b3 to 00b9c7b7 has its CatchHandler @ 00ba1208 */
      CEGUI::Window::setText((String *)in_RDI[0x1225]);
                    /* try { // try from 00b9c7bb to 00b9c7e3 has its CatchHandler @ 00ba1218 */
      CEGUI::String::~String(local_1718);
      if (iVar15 < iVar14) {
        pSVar36 = local_1878;
                    /* try { // try from 00b9fc3c to 00b9fc40 has its CatchHandler @ 00ba1218 */
        CEGUI::String::String(pSVar36,"FFFF0000");
                    /* try { // try from 00b9fc51 to 00b9fc55 has its CatchHandler @ 00ba1696 */
        CEGUI::String::String(local_17c8,"TextColour");
                    /* try { // try from 00b9fc68 to 00b9fc6c has its CatchHandler @ 00ba1691 */
        CEGUI::PropertySet::setProperty((String *)in_RDI[0x1225],local_17c8);
                    /* try { // try from 00b9fc70 to 00b9fc74 has its CatchHandler @ 00ba1696 */
        CEGUI::String::~String(local_17c8);
      }
      else if (iVar14 < iVar15) {
        pSVar36 = local_19d8;
        CEGUI::String::String(pSVar36,"FFc0c0ff");
                    /* try { // try from 00b9c7f4 to 00b9c7f8 has its CatchHandler @ 00ba133a */
        CEGUI::String::String(local_1928,"TextColour");
                    /* try { // try from 00b9c80b to 00b9c80f has its CatchHandler @ 00b9fd82 */
        CEGUI::PropertySet::setProperty((String *)in_RDI[0x1225],local_1928);
                    /* try { // try from 00b9c813 to 00b9c817 has its CatchHandler @ 00ba133a */
        CEGUI::String::~String(local_1928);
      }
      else {
        pSVar36 = local_1b38;
                    /* try { // try from 00b9f512 to 00b9f516 has its CatchHandler @ 00ba1218 */
        CEGUI::String::String(pSVar36,"FFFFFFFF");
                    /* try { // try from 00b9f527 to 00b9f52b has its CatchHandler @ 00b9fe7d */
        CEGUI::String::String(local_1a88,"TextColour");
                    /* try { // try from 00b9f53e to 00b9f542 has its CatchHandler @ 00ba077e */
        CEGUI::PropertySet::setProperty((String *)in_RDI[0x1225],local_1a88);
                    /* try { // try from 00b9f546 to 00b9f54a has its CatchHandler @ 00b9fe7d */
        CEGUI::String::~String(local_1a88);
      }
                    /* try { // try from 00b9c81b to 00b9c861 has its CatchHandler @ 00ba1218 */
      CEGUI::String::~String(pSVar36);
    }
    iVar14 = CCharacter::maximumDamageForDisplay((CCharacter *)in_RDI[0xb],false,false,true);
    iVar15 = CCharacter::maximumDamageForDisplay((CCharacter *)in_RDI[0xb],false,false,false);
    STRINGS::GetValueAsString((STRINGS *)local_158,iVar15);
                    /* try { // try from 00b9c871 to 00b9c887 has its CatchHandler @ 00b9fd72 */
    iVar16 = CCharacter::minimumDamageForDisplay((CCharacter *)in_RDI[0xb],false,false,false);
    STRINGS::GetValueAsString((STRINGS *)local_138,iVar16);
                    /* try { // try from 00b9c896 to 00b9c89a has its CatchHandler @ 00ba1335 */
    std::string::string((string *)local_148,(string *)local_138);
                    /* try { // try from 00b9c8a8 to 00b9c8ac has its CatchHandler @ 00ba1333 */
    std::string::append((char *)local_148,0x103f694);
                    /* try { // try from 00b9c8bb to 00b9c8bf has its CatchHandler @ 00ba1310 */
    std::operator+((string *)&local_568,(string *)local_148);
    if ((allocator *)(local_148[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar2 = (int *)(local_148[0] + -8);
      iVar16 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar16 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_148[0] + -0x18));
      }
    }
    if ((allocator *)(local_138[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar2 = (int *)(local_138[0] + -8);
      iVar16 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar16 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_138[0] + -0x18));
      }
    }
    if ((allocator *)(local_158[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar2 = (int *)(local_158[0] + -8);
      iVar16 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar16 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_158[0] + -0x18));
      }
    }
                    /* try { // try from 00b9c929 to 00b9c94d has its CatchHandler @ 00ba160e */
    cVar11 = CEGUI::operator!=((String *)(in_RDI[0x1226] + 0xc0),(string *)&local_568);
    if (cVar11 != '\0') {
      CEGUI::String::String(local_1be8,(uchar *)CONCAT44(fStack_564,local_568));
                    /* try { // try from 00b9c95d to 00b9c961 has its CatchHandler @ 00ba15fe */
      CEGUI::Window::setText((String *)in_RDI[0x1226]);
                    /* try { // try from 00b9c965 to 00b9c98d has its CatchHandler @ 00ba160e */
      CEGUI::String::~String(local_1be8);
      if (iVar15 < iVar14) {
        pSVar36 = local_1d48;
                    /* try { // try from 00b9fc8a to 00b9fc8e has its CatchHandler @ 00ba160e */
        CEGUI::String::String(pSVar36,"FFFF0000");
                    /* try { // try from 00b9fc9f to 00b9fca3 has its CatchHandler @ 00b9fd41 */
        CEGUI::String::String(local_1c98,"TextColour");
                    /* try { // try from 00b9fcb6 to 00b9fcba has its CatchHandler @ 00b9fd34 */
        CEGUI::PropertySet::setProperty((String *)in_RDI[0x1226],local_1c98);
                    /* try { // try from 00b9fcbe to 00b9fcc2 has its CatchHandler @ 00b9fd41 */
        CEGUI::String::~String(local_1c98);
      }
      else if (iVar14 < iVar15) {
        pSVar36 = local_1ea8;
        CEGUI::String::String(pSVar36,"FFc0c0ff");
                    /* try { // try from 00b9c99e to 00b9c9a2 has its CatchHandler @ 00b9fce0 */
        CEGUI::String::String(local_1df8,"TextColour");
                    /* try { // try from 00b9c9b5 to 00b9c9b9 has its CatchHandler @ 00ba168c */
        CEGUI::PropertySet::setProperty((String *)in_RDI[0x1226],local_1df8);
                    /* try { // try from 00b9c9bd to 00b9c9c1 has its CatchHandler @ 00b9fce0 */
        CEGUI::String::~String(local_1df8);
      }
      else {
        pSVar36 = local_2008;
                    /* try { // try from 00b9e885 to 00b9e889 has its CatchHandler @ 00ba160e */
        CEGUI::String::String(pSVar36,"FFFFFFFF");
                    /* try { // try from 00b9e89a to 00b9e89e has its CatchHandler @ 00b9feb4 */
        CEGUI::String::String(local_1f58,"TextColour");
                    /* try { // try from 00b9e8b1 to 00b9e8b5 has its CatchHandler @ 00b9feaf */
        CEGUI::PropertySet::setProperty((String *)in_RDI[0x1226],local_1f58);
                    /* try { // try from 00b9e8b9 to 00b9e8bd has its CatchHandler @ 00b9feb4 */
        CEGUI::String::~String(local_1f58);
      }
                    /* try { // try from 00b9c9c5 to 00b9ca6d has its CatchHandler @ 00ba160e */
      CEGUI::String::~String(pSVar36);
    }
    iVar15 = CCharacter::minimumDamageForDisplay((CCharacter *)in_RDI[0xb],false,true,false);
    iVar16 = CCharacter::minimumDamageForDisplay((CCharacter *)in_RDI[0xb],true,true,false);
    iVar14 = iVar16;
    if (((iVar15 != 0) && (iVar14 = iVar15, iVar16 != 0)) && (iVar16 < iVar15)) {
      iVar14 = iVar16;
    }
    iVar16 = CCharacter::maximumDamageForDisplay((CCharacter *)in_RDI[0xb],false,true,true);
    iVar15 = CCharacter::maximumDamageForDisplay((CCharacter *)in_RDI[0xb],false,true,false);
    iVar17 = CCharacter::maximumDamageForDisplay((CCharacter *)in_RDI[0xb],true,true,false);
    if (iVar15 <= iVar17) {
      iVar15 = iVar17;
    }
    STRINGS::GetValueAsString((STRINGS *)local_188,iVar15);
                    /* try { // try from 00b9ca7b to 00b9ca7f has its CatchHandler @ 00ba1684 */
    STRINGS::GetValueAsString((STRINGS *)local_168,iVar14);
                    /* try { // try from 00b9ca8e to 00b9ca92 has its CatchHandler @ 00ba15f9 */
    std::string::string((string *)local_178,(string *)local_168);
                    /* try { // try from 00b9caa0 to 00b9caa4 has its CatchHandler @ 00ba15f7 */
    std::string::append((char *)local_178,0x103f694);
                    /* try { // try from 00b9cab3 to 00b9cab7 has its CatchHandler @ 00ba15cc */
    std::operator+((string *)&local_528,(string *)local_178);
    if ((allocator *)(local_178[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar2 = (int *)(local_178[0] + -8);
      iVar14 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar14 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_178[0] + -0x18));
      }
    }
    if ((allocator *)(local_168[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar2 = (int *)(local_168[0] + -8);
      iVar14 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar14 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_168[0] + -0x18));
      }
    }
    if ((allocator *)(local_188[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar2 = (int *)(local_188[0] + -8);
      iVar14 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar14 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_188[0] + -0x18));
      }
    }
                    /* try { // try from 00b9cb21 to 00b9cb45 has its CatchHandler @ 00ba152a */
    cVar11 = CEGUI::operator!=((String *)(in_RDI[0x1227] + 0xc0),(string *)&local_528);
    if (cVar11 != '\0') {
      CEGUI::String::String(local_20b8,(uchar *)CONCAT44(fStack_524,local_528));
                    /* try { // try from 00b9cb55 to 00b9cb59 has its CatchHandler @ 00ba1515 */
      CEGUI::Window::setText((String *)in_RDI[0x1227]);
                    /* try { // try from 00b9cb5d to 00b9cb85 has its CatchHandler @ 00ba152a */
      CEGUI::String::~String(local_20b8);
      if (iVar15 < iVar16) {
        pSVar36 = local_2218;
                    /* try { // try from 00b9fb41 to 00b9fb45 has its CatchHandler @ 00ba152a */
        CEGUI::String::String(pSVar36,"FFFF0000");
                    /* try { // try from 00b9fb56 to 00b9fb5a has its CatchHandler @ 00ba0f87 */
        CEGUI::String::String(local_2168,"TextColour");
                    /* try { // try from 00b9fb6d to 00b9fb71 has its CatchHandler @ 00ba0f82 */
        CEGUI::PropertySet::setProperty((String *)in_RDI[0x1227],local_2168);
                    /* try { // try from 00b9fb75 to 00b9fb79 has its CatchHandler @ 00ba0f87 */
        CEGUI::String::~String(local_2168);
      }
      else if (iVar16 < iVar15) {
        pSVar36 = local_2378;
        CEGUI::String::String(pSVar36,"FFc0c0ff");
                    /* try { // try from 00b9cb96 to 00b9cb9a has its CatchHandler @ 00b9fd65 */
        CEGUI::String::String(local_22c8,"TextColour");
                    /* try { // try from 00b9cbad to 00b9cbb1 has its CatchHandler @ 00ba14f3 */
        CEGUI::PropertySet::setProperty((String *)in_RDI[0x1227],local_22c8);
                    /* try { // try from 00b9cbb5 to 00b9cbb9 has its CatchHandler @ 00b9fd65 */
        CEGUI::String::~String(local_22c8);
      }
      else {
        pSVar36 = local_24d8;
                    /* try { // try from 00b9e8d3 to 00b9e8d7 has its CatchHandler @ 00ba152a */
        CEGUI::String::String(pSVar36,"FFFFFFFF");
                    /* try { // try from 00b9e8e8 to 00b9e8ec has its CatchHandler @ 00ba0b92 */
        CEGUI::String::String(local_2428,"TextColour");
                    /* try { // try from 00b9e8ff to 00b9e903 has its CatchHandler @ 00ba0b82 */
        CEGUI::PropertySet::setProperty((String *)in_RDI[0x1227],local_2428);
                    /* try { // try from 00b9e907 to 00b9e90b has its CatchHandler @ 00ba0b92 */
        CEGUI::String::~String(local_2428);
      }
                    /* try { // try from 00b9cbbd to 00b9cbf4 has its CatchHandler @ 00ba152a */
      CEGUI::String::~String(pSVar36);
    }
    iVar14 = CCharacter::baseAC((CCharacter *)in_RDI[0xb]);
    iVar15 = CCharacter::AC((CCharacter *)in_RDI[0xb]);
    STRINGS::GetValueAsString((STRINGS *)local_1b8,iVar15);
                    /* try { // try from 00b9cbfe to 00b9cc14 has its CatchHandler @ 00ba14ee */
    iVar16 = CCharacter::minimumAC((CCharacter *)in_RDI[0xb]);
    STRINGS::GetValueAsString((STRINGS *)local_198,iVar16);
                    /* try { // try from 00b9cc23 to 00b9cc27 has its CatchHandler @ 00ba14e9 */
    std::string::string((string *)local_1a8,(string *)local_198);
                    /* try { // try from 00b9cc35 to 00b9cc39 has its CatchHandler @ 00ba14e7 */
    std::string::append((char *)local_1a8,0x103f694);
                    /* try { // try from 00b9cc4b to 00b9cc4f has its CatchHandler @ 00ba14bc */
    std::operator+((string *)&local_4e8,(string *)local_1a8);
    if ((allocator *)(local_1a8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar2 = (int *)(local_1a8[0] + -8);
      iVar16 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar16 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_1a8[0] + -0x18));
      }
    }
    if ((allocator *)(local_198[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar2 = (int *)(local_198[0] + -8);
      iVar16 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar16 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_198[0] + -0x18));
      }
    }
    if ((allocator *)(local_1b8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar2 = (int *)(local_1b8[0] + -8);
      iVar16 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar16 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_1b8[0] + -0x18));
      }
    }
                    /* try { // try from 00b9ccb4 to 00b9ccf8 has its CatchHandler @ 00ba141a */
    cVar11 = CEGUI::operator!=((String *)(in_RDI[0x1228] + 0xc0),(string *)&local_4e8);
    if (cVar11 != '\0') {
                    /* try { // try from 00b9e7e2 to 00b9e7e6 has its CatchHandler @ 00ba141a */
      CEGUI::String::String(local_2588,(uchar *)CONCAT44(fStack_4e4,local_4e8));
                    /* try { // try from 00b9e7f6 to 00b9e7fa has its CatchHandler @ 00b9fd43 */
      CEGUI::Window::setText((String *)in_RDI[0x1228]);
                    /* try { // try from 00b9e7fe to 00b9e826 has its CatchHandler @ 00ba141a */
      CEGUI::String::~String(local_2588);
      if (iVar15 < iVar14) {
        pSVar36 = local_26e8;
                    /* try { // try from 00b9faf3 to 00b9faf7 has its CatchHandler @ 00ba141a */
        CEGUI::String::String(pSVar36,"FFFF0000");
                    /* try { // try from 00b9fb08 to 00b9fb0c has its CatchHandler @ 00ba1505 */
        CEGUI::String::String(local_2638,"TextColour");
                    /* try { // try from 00b9fb1f to 00b9fb23 has its CatchHandler @ 00ba14f8 */
        CEGUI::PropertySet::setProperty((String *)in_RDI[0x1228],local_2638);
                    /* try { // try from 00b9fb27 to 00b9fb2b has its CatchHandler @ 00ba1505 */
        CEGUI::String::~String(local_2638);
      }
      else if (iVar14 < iVar15) {
        pSVar36 = local_2848;
                    /* try { // try from 00b9f7e7 to 00b9f7eb has its CatchHandler @ 00ba141a */
        CEGUI::String::String(pSVar36,"FFc0c0ff");
                    /* try { // try from 00b9f7fc to 00b9f800 has its CatchHandler @ 00ba0bb8 */
        CEGUI::String::String(local_2798,"TextColour");
                    /* try { // try from 00b9f813 to 00b9f817 has its CatchHandler @ 00ba0bb3 */
        CEGUI::PropertySet::setProperty((String *)in_RDI[0x1228],local_2798);
                    /* try { // try from 00b9f81b to 00b9f81f has its CatchHandler @ 00ba0bb8 */
        CEGUI::String::~String(local_2798);
      }
      else {
        pSVar36 = local_29a8;
        CEGUI::String::String(pSVar36,"FFFFFFFF");
                    /* try { // try from 00b9e837 to 00b9e83b has its CatchHandler @ 00b9fed2 */
        CEGUI::String::String(local_28f8,"TextColour");
                    /* try { // try from 00b9e84e to 00b9e852 has its CatchHandler @ 00b9feb9 */
        CEGUI::PropertySet::setProperty((String *)in_RDI[0x1228],local_28f8);
                    /* try { // try from 00b9e856 to 00b9e85a has its CatchHandler @ 00b9fed2 */
        CEGUI::String::~String(local_28f8);
      }
                    /* try { // try from 00b9e85e to 00b9e862 has its CatchHandler @ 00ba141a */
      CEGUI::String::~String(pSVar36);
    }
    if ((update(float)::g_MP == '\0') &&
       (iVar14 = __cxa_guard_acquire(&update(float)::g_MP), iVar14 != 0)) {
      DAT_014ccf48 = 0x20;
      _DAT_014ccf50 = 0;
      _DAT_014ccf60 = 0;
      _DAT_014ccf58 = 0;
      DAT_014ccfe8 = (undefined *)0x0;
      update(float)::g_MP = 0;
      _DAT_014ccf68 = 0;
      __cxa_guard_release(&update(float)::g_MP);
      __cxa_atexit(CEGUI::String::~String,&update(float)::g_MP,&__dso_handle);
    }
    if (update(float)::g_MP == 0) {
      CStringTranslate::getSinglton();
      CStringTranslate::getTranslateString((wchar_t *)local_1c8);
                    /* try { // try from 00b9cd07 to 00b9cd0b has its CatchHandler @ 00ba1415 */
      STRINGS::StringConvertToUTF8((wstring_conflict *)local_1d8);
      lVar32 = *(long *)(local_1d8[0] + -0x18);
                    /* try { // try from 00b9cd20 to 00b9cd24 has its CatchHandler @ 00ba13e7 */
      CEGUI::String::grow(0x14ccf40);
      puVar19 = &DAT_014ccf68;
      if (0x20 < DAT_014ccf48) {
        puVar19 = DAT_014ccfe8;
      }
      update(float)::g_MP = lVar32;
      *(undefined4 *)(puVar19 + lVar32 * 4) = 0;
      while (lVar32 != 0) {
        lVar32 = lVar32 + -1;
        puVar19 = &DAT_014ccf68;
        if (0x20 < DAT_014ccf48) {
          puVar19 = DAT_014ccfe8;
        }
        *(uint *)(puVar19 + lVar32 * 4) = (uint)*(byte *)(local_1d8[0] + lVar32);
      }
      if ((allocator *)(local_1d8[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_1d8[0] + -8);
        iVar14 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar14 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_1d8[0] + -0x18));
        }
      }
      if ((allocator *)(local_1c8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_1c8[0] + -8);
        iVar14 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar14 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_1c8[0] + -0x18));
        }
      }
    }
                    /* try { // try from 00b9cdc0 to 00b9cdd6 has its CatchHandler @ 00ba141a */
    iVar14 = CCharacter::maxMana((CCharacter *)in_RDI[0xb]);
    STRINGS::GetValueAsString((STRINGS *)local_1e8,iVar14);
                    /* try { // try from 00b9cdec to 00b9cdf0 has its CatchHandler @ 00ba1387 */
    CEGUI::operator+(local_2b08,(char *)&update(float)::g_MP);
                    /* try { // try from 00b9ce02 to 00b9ce06 has its CatchHandler @ 00ba0dae */
    CEGUI::operator+(local_2a58,(string *)local_2b08);
                    /* try { // try from 00b9ce0a to 00b9ce0e has its CatchHandler @ 00ba0d96 */
    CEGUI::String::~String(local_2b08);
    if ((allocator *)(local_1e8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar2 = (int *)(local_1e8[0] + -8);
      iVar14 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar14 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_1e8[0] + -0x18));
      }
    }
                    /* try { // try from 00b9ce3f to 00b9ce83 has its CatchHandler @ 00ba0d62 */
    cVar11 = CEGUI::operator!=((String *)(in_RDI[0x1229] + 0xc0),local_2a58);
    if (cVar11 != '\0') {
                    /* try { // try from 00b9dff8 to 00b9e00f has its CatchHandler @ 00ba0d62 */
      puVar20 = (uchar *)CEGUI::String::build_utf8_buff();
      CEGUI::String::String(local_2bb8,puVar20);
                    /* try { // try from 00b9e01f to 00b9e023 has its CatchHandler @ 00ba0dc6 */
      CEGUI::Window::setText((String *)in_RDI[0x1229]);
                    /* try { // try from 00b9e027 to 00b9e063 has its CatchHandler @ 00ba0d62 */
      CEGUI::String::~String(local_2bb8);
      iVar14 = CCharacter::maxMana((CCharacter *)in_RDI[0xb]);
      if (iVar14 < *(int *)((CCharacter *)in_RDI[0xb] + 0x43c)) {
        pSVar36 = local_2d18;
        CEGUI::String::String(pSVar36,"FFFF0000");
                    /* try { // try from 00b9e074 to 00b9e078 has its CatchHandler @ 00ba0f33 */
        CEGUI::String::String(local_2c68,"TextColour");
                    /* try { // try from 00b9e08b to 00b9e08f has its CatchHandler @ 00ba0f2e */
        CEGUI::PropertySet::setProperty((String *)in_RDI[0x1229],local_2c68);
                    /* try { // try from 00b9e093 to 00b9e097 has its CatchHandler @ 00ba0f33 */
        CEGUI::String::~String(local_2c68);
      }
      else {
                    /* try { // try from 00b9f99e to 00b9f9cc has its CatchHandler @ 00ba0d62 */
        iVar14 = CCharacter::maxMana((CCharacter *)in_RDI[0xb]);
        if (*(int *)(in_RDI[0xb] + 0x43c) < iVar14) {
          pSVar36 = local_2e78;
          CEGUI::String::String(pSVar36,"FFc0c0ff");
                    /* try { // try from 00b9f9dd to 00b9f9e1 has its CatchHandler @ 00ba0884 */
          CEGUI::String::String(local_2dc8,"TextColour");
                    /* try { // try from 00b9f9f4 to 00b9f9f8 has its CatchHandler @ 00b9ff0a */
          CEGUI::PropertySet::setProperty((String *)in_RDI[0x1229],local_2dc8);
                    /* try { // try from 00b9f9fc to 00b9fa00 has its CatchHandler @ 00ba0884 */
          CEGUI::String::~String(local_2dc8);
        }
        else {
          pSVar36 = local_2fd8;
                    /* try { // try from 00b9faa5 to 00b9faa9 has its CatchHandler @ 00ba0d62 */
          CEGUI::String::String(pSVar36,"FFFFFFFF");
                    /* try { // try from 00b9faba to 00b9fabe has its CatchHandler @ 00ba0f45 */
          CEGUI::String::String(local_2f28,"TextColour");
                    /* try { // try from 00b9fad1 to 00b9fad5 has its CatchHandler @ 00ba0f38 */
          CEGUI::PropertySet::setProperty((String *)in_RDI[0x1229],local_2f28);
                    /* try { // try from 00b9fad9 to 00b9fadd has its CatchHandler @ 00ba0f45 */
          CEGUI::String::~String(local_2f28);
        }
      }
                    /* try { // try from 00b9e09b to 00b9e09f has its CatchHandler @ 00ba0d62 */
      CEGUI::String::~String(pSVar36);
    }
    if ((update(float)::g_HP == '\0') &&
       (iVar14 = __cxa_guard_acquire(&update(float)::g_HP), iVar14 != 0)) {
      DAT_014cce88 = 0x20;
      _DAT_014cce90 = 0;
      _DAT_014ccea0 = 0;
      _DAT_014cce98 = 0;
      DAT_014ccf28 = (undefined *)0x0;
      update(float)::g_HP = 0;
      _DAT_014ccea8 = 0;
      __cxa_guard_release(&update(float)::g_HP);
      __cxa_atexit(CEGUI::String::~String,&update(float)::g_HP,&__dso_handle);
    }
    if (update(float)::g_HP == 0) {
      CStringTranslate::getSinglton();
      CStringTranslate::getTranslateString((wchar_t *)local_1f8);
                    /* try { // try from 00b9ce92 to 00b9ce96 has its CatchHandler @ 00ba0d5c */
      STRINGS::StringConvertToUTF8((wstring_conflict *)local_208);
      lVar32 = *(long *)(local_208[0] + -0x18);
                    /* try { // try from 00b9ceab to 00b9ceaf has its CatchHandler @ 00ba0d44 */
      CEGUI::String::grow(0x14cce80);
      puVar19 = &DAT_014ccea8;
      if (0x20 < DAT_014cce88) {
        puVar19 = DAT_014ccf28;
      }
      update(float)::g_HP = lVar32;
      *(undefined4 *)(puVar19 + lVar32 * 4) = 0;
      while (lVar32 != 0) {
        lVar32 = lVar32 + -1;
        puVar19 = &DAT_014ccea8;
        if (0x20 < DAT_014cce88) {
          puVar19 = DAT_014ccf28;
        }
        *(uint *)(puVar19 + lVar32 * 4) = (uint)*(byte *)(local_208[0] + lVar32);
      }
      if ((allocator *)(local_208[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_208[0] + -8);
        iVar14 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar14 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_208[0] + -0x18));
        }
      }
      if ((allocator *)(local_1f8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_1f8[0] + -8);
        iVar14 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar14 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_1f8[0] + -0x18));
        }
      }
    }
                    /* try { // try from 00b9cf4b to 00b9cf61 has its CatchHandler @ 00ba0d62 */
    iVar14 = CCharacter::maxHP((CCharacter *)in_RDI[0xb]);
    STRINGS::GetValueAsString((STRINGS *)local_218,iVar14);
                    /* try { // try from 00b9cf77 to 00b9cf7b has its CatchHandler @ 00ba0cd1 */
    CEGUI::operator+(local_3138,(char *)&update(float)::g_HP);
                    /* try { // try from 00b9cf8d to 00b9cf91 has its CatchHandler @ 00ba0cc4 */
    CEGUI::operator+(local_3088,(string *)local_3138);
                    /* try { // try from 00b9cf95 to 00b9cf99 has its CatchHandler @ 00ba0ca1 */
    CEGUI::String::~String(local_3138);
    if ((allocator *)(local_218[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar2 = (int *)(local_218[0] + -8);
      iVar14 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar14 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_218[0] + -0x18));
      }
    }
                    /* try { // try from 00b9cfca to 00b9cff1 has its CatchHandler @ 00ba0c6d */
    cVar11 = CEGUI::operator!=((String *)(in_RDI[0x122a] + 0xc0),local_3088);
    if (cVar11 != '\0') {
      puVar20 = (uchar *)CEGUI::String::build_utf8_buff();
      CEGUI::String::String(local_31e8,puVar20);
                    /* try { // try from 00b9d001 to 00b9d005 has its CatchHandler @ 00ba0c5d */
      CEGUI::Window::setText((String *)in_RDI[0x122a]);
                    /* try { // try from 00b9d009 to 00b9d045 has its CatchHandler @ 00ba0c6d */
      CEGUI::String::~String(local_31e8);
      iVar14 = CCharacter::maxHP((CCharacter *)in_RDI[0xb]);
      if (iVar14 < *(int *)((CCharacter *)in_RDI[0xb] + 0x418)) {
        pSVar36 = local_3348;
        CEGUI::String::String(pSVar36,"FFFF0000");
                    /* try { // try from 00b9d056 to 00b9d05a has its CatchHandler @ 00ba0c58 */
        CEGUI::String::String(local_3298,"TextColour");
                    /* try { // try from 00b9d06d to 00b9d071 has its CatchHandler @ 00ba0c53 */
        CEGUI::PropertySet::setProperty((String *)in_RDI[0x122a],local_3298);
                    /* try { // try from 00b9d075 to 00b9d079 has its CatchHandler @ 00ba0c58 */
        CEGUI::String::~String(local_3298);
      }
      else {
                    /* try { // try from 00b9f61e to 00b9f64c has its CatchHandler @ 00ba0c6d */
        iVar14 = CCharacter::maxHP((CCharacter *)in_RDI[0xb]);
        if (*(int *)(in_RDI[0xb] + 0x418) < iVar14) {
          pSVar36 = local_34a8;
          CEGUI::String::String(pSVar36,"FFc0c0ff");
                    /* try { // try from 00b9f65d to 00b9f661 has its CatchHandler @ 00ba0842 */
          CEGUI::String::String(local_33f8,"TextColour");
                    /* try { // try from 00b9f674 to 00b9f678 has its CatchHandler @ 00ba083d */
          CEGUI::PropertySet::setProperty((String *)in_RDI[0x122a],local_33f8);
                    /* try { // try from 00b9f67c to 00b9f680 has its CatchHandler @ 00ba0842 */
          CEGUI::String::~String(local_33f8);
        }
        else {
          pSVar36 = local_3608;
                    /* try { // try from 00b9f75a to 00b9f75e has its CatchHandler @ 00ba0c6d */
          CEGUI::String::String(pSVar36,"FFFFFFFF");
                    /* try { // try from 00b9f76f to 00b9f773 has its CatchHandler @ 00ba092a */
          CEGUI::String::String(local_3558,"TextColour");
                    /* try { // try from 00b9f786 to 00b9f78a has its CatchHandler @ 00ba081d */
          CEGUI::PropertySet::setProperty((String *)in_RDI[0x122a],local_3558);
                    /* try { // try from 00b9f78e to 00b9f792 has its CatchHandler @ 00ba092a */
          CEGUI::String::~String(local_3558);
        }
      }
                    /* try { // try from 00b9d07d to 00b9d081 has its CatchHandler @ 00ba0c6d */
      CEGUI::String::~String(pSVar36);
    }
                    /* try { // try from 00b9d085 to 00b9d089 has its CatchHandler @ 00ba0d62 */
    CEGUI::String::~String(local_3088);
                    /* try { // try from 00b9d08d to 00b9d091 has its CatchHandler @ 00ba141a */
    CEGUI::String::~String(local_2a58);
    paVar33 = (allocator *)(CONCAT44(fStack_4e4,local_4e8) + -0x18);
    if (paVar33 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(CONCAT44(fStack_4e4,local_4e8) + -8);
      iVar14 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar14 < 1) {
        std::string::_Rep::_M_destroy(paVar33);
      }
    }
    paVar33 = (allocator *)(CONCAT44(fStack_524,local_528) + -0x18);
    if (paVar33 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(CONCAT44(fStack_524,local_528) + -8);
      iVar14 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar14 < 1) {
        std::string::_Rep::_M_destroy(paVar33);
      }
    }
    paVar33 = (allocator *)(CONCAT44(fStack_564,local_568) + -0x18);
    if (paVar33 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(CONCAT44(fStack_564,local_568) + -8);
      iVar14 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar14 < 1) {
        std::string::_Rep::_M_destroy(paVar33);
      }
    }
    if ((allocator *)(local_f8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar2 = (int *)(local_f8[0] + -8);
      iVar14 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar14 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
      }
    }
    if ((allocator *)(local_c8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar2 = (int *)(local_c8[0] + -8);
      iVar14 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar14 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
      }
    }
    if ((allocator *)(local_a8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar2 = (int *)(local_a8[0] + -8);
      iVar14 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar14 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
      }
    }
    if ((allocator *)(local_98[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar2 = (int *)(local_98[0] + -8);
      iVar14 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar14 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
      }
    }
  }
  CGenericModel::updateAnimation((CGenericModel *)in_RDI[0x1234],param_1,false);
  Ogre::Entity::_updateAnimation();
  plVar27 = *(long **)(in_RDI[0x1234] + 0x130);
  pcVar7 = *(code **)(*plVar27 + 0x1b0);
                    /* try { // try from 00b9d1d1 to 00b9d1d5 has its CatchHandler @ 00ba07d5 */
  std::string::string((string *)local_228,"tag_toppet",&local_3a);
                    /* try { // try from 00b9d1dc to 00b9d1dd has its CatchHandler @ 00ba07da */
  plVar27 = (long *)(*pcVar7)(plVar27);
  if ((allocator *)(local_228[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_228[0] + -8);
    iVar14 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar14 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_228[0] + -0x18));
    }
  }
  fVar41 = (float)iVar12;
  fVar47 = (float)iVar13;
  local_288 = CPositionableObject::getPosition((CPositionableObject *)in_RDI[0x1234],false);
  local_280 = in_XMM1_Da;
  pfVar21 = (float *)(**(code **)(*plVar27 + 0x200))(plVar27);
  fVar48 = pfVar21[1] + local_288._4_4_;
  fVar42 = (float)CGameUI::scaledY((CGameUI *)in_RDI[0x12],*pfVar21 + (float)local_288);
  fVar43 = fVar41 * DAT_00fa4810;
  fVar42 = fVar42 + fVar43;
  fVar48 = (float)CGameUI::scaledY((CGameUI *)in_RDI[0x12],fVar48);
  uVar31 = (uint)(fVar47 * DAT_00fa86f4 + fVar48) ^ DAT_00fa8780;
  *(float *)((long)in_RDI + 0x91b4) = fVar42;
  local_2b8 = 0;
  local_2b0 = 0;
  local_2b4 = fVar42;
  local_2ac = uVar31;
                    /* try { // try from 00b9d355 to 00b9d359 has its CatchHandler @ 00ba052d */
  CEGUI::Window::setPosition((UVector2 *)in_RDI[5]);
  plVar27 = *(long **)(in_RDI[0x1234] + 0x130);
  pcVar7 = *(code **)(*plVar27 + 0x1b0);
                    /* try { // try from 00b9d38f to 00b9d393 has its CatchHandler @ 00ba054b */
  std::string::string((string *)local_238,"tag_bottompet",&local_3b);
                    /* try { // try from 00b9d39a to 00b9d39c has its CatchHandler @ 00ba0556 */
  plVar27 = (long *)(*pcVar7)(plVar27);
  if ((allocator *)(local_238[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_238[0] + -8);
    iVar12 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar12 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_238[0] + -0x18));
    }
  }
  local_298 = CPositionableObject::getPosition((CPositionableObject *)in_RDI[0x1234],false);
  local_290 = fVar42;
  pfVar21 = (float *)(**(code **)(*plVar27 + 0x200))(plVar27);
  local_2c4 = (float)CGameUI::scaledY((CGameUI *)in_RDI[0x12],*pfVar21 + (float)local_298);
  local_2c4 = local_2c4 + fVar43;
  local_2c8 = 0;
  local_2c0 = 0;
  local_2bc = uVar31;
                    /* try { // try from 00b9d469 to 00b9d46d has its CatchHandler @ 00ba058f */
  CEGUI::Window::setPosition((UVector2 *)in_RDI[9]);
  plVar27 = *(long **)(in_RDI[0x1234] + 0x130);
  pcVar7 = *(code **)(*plVar27 + 0x1b0);
                    /* try { // try from 00b9d4a3 to 00b9d4a7 has its CatchHandler @ 00ba07af */
  std::string::string((string *)local_248,"tag_bottompetright",&local_3c);
                    /* try { // try from 00b9d4ae to 00b9d4b0 has its CatchHandler @ 00ba07b4 */
  plVar27 = (long *)(*pcVar7)(plVar27);
  if ((allocator *)(local_248[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_248[0] + -8);
    iVar12 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar12 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_248[0] + -0x18));
    }
  }
  local_2a8 = CPositionableObject::getPosition((CPositionableObject *)in_RDI[0x1234],false);
  local_2a0 = fVar42;
  pfVar21 = (float *)(**(code **)(*plVar27 + 0x200))(plVar27);
  fVar48 = (float)CGameUI::scaledY((CGameUI *)in_RDI[0x12],*pfVar21 + (float)local_2a8);
  fVar44 = (float)CGameUI::scaledY((CGameUI *)in_RDI[0x12],DAT_00fa8738);
  fVar42 = *(float *)((long)in_RDI + 0x91b4);
  fVar44 = (fVar48 + fVar43) - fVar44;
  *(uint *)(in_RDI + 0x1236) = (uint)fVar44 & -(uint)(0.0 < fVar44);
  fVar43 = (float)CGameUI::scaledY((CGameUI *)in_RDI[0x12],DAT_00fce514);
  fVar43 = (fVar42 + fVar43) / fVar41;
  fVar48 = (float)CGameUI::scaledY((CGameUI *)in_RDI[0x12],DAT_00fefd58);
  fVar42 = fVar48 / fVar41;
  if (fVar43 < 0.0) {
    fVar42 = fVar48 / fVar41 + fVar43;
    fVar41 = DAT_00fa47fc / fVar41 + 0.0;
    fVar43 = 0.0;
    if (fVar42 <= fVar41) {
      fVar42 = fVar41;
    }
  }
  if (in_RDI[0x1230] != 0) {
    fVar41 = (float)CGameUI::scaledY((CGameUI *)in_RDI[0x12],DAT_00ff08c8);
    fVar48 = (float)CGameUI::scaledY((CGameUI *)in_RDI[0x12],_DAT_00ff08cc);
    Ogre::Viewport::setDimensions(fVar43,fVar48 / fVar47,fVar42,fVar41 / fVar47);
    pcVar7 = *(code **)(*(long *)in_RDI[0x122e] + 0x278);
    iVar12 = Ogre::Viewport::getActualWidth();
    iVar13 = Ogre::Viewport::getActualHeight();
    auVar45._8_8_ = extraout_XMM0_Qb;
    auVar45._0_8_ = extraout_XMM0_Qa;
    auVar46._4_12_ = auVar45._4_12_;
    auVar46._0_4_ = (float)iVar12 / (float)iVar13;
    (*pcVar7)(auVar46._0_8_,in_RDI[0x122e]);
  }
  if (((char)in_RDI[0xd] == '\0') && (*(char *)((long)in_RDI + 0x69) == '\0')) {
                    /* try { // try from 00b9f6b9 to 00b9f6d7 has its CatchHandler @ 00ba074e */
    std::string::string(local_258,"CLOSE",&local_3d);
    cVar11 = CGenericModel::animationPlaying((CGenericModel *)in_RDI[0x1234],local_258);
    bVar39 = false;
    if (cVar11 == '\0') {
                    /* try { // try from 00ba071c to 00ba073a has its CatchHandler @ 00ba074e */
      std::string::string(local_268,"CLOSE",&local_3e);
      cVar11 = CGenericModel::animationQueued((CGenericModel *)in_RDI[0x1234],local_268);
      bVar39 = cVar11 == '\0';
                    /* try { // try from 00ba0744 to 00ba0748 has its CatchHandler @ 00ba0779 */
      std::string::~string(local_268);
    }
                    /* try { // try from 00b9f6e6 to 00b9f6ea has its CatchHandler @ 00ba06e8 */
    std::string::~string(local_258);
    if (bVar39) {
      (**(code **)(*(long *)in_RDI[0x1234] + 0x50))((long *)in_RDI[0x1234],0);
      *(undefined1 *)((long)in_RDI + 0x69) = 1;
      (**(code **)(*(long *)in_RDI[0x122f] + 0x60))((long *)in_RDI[0x122f],4);
      CEGUI::Window::removeChildWindow((Window *)in_RDI[3]);
      in_RDI[0x1230] = 0;
    }
  }
  if ((*(char *)((long)in_RDI + 0x9189) != '\0') && (in_RDI[0xb] != 0)) {
    this = *(CSkillManager **)(in_RDI[0xb] + 0x1c8);
    if (this == (CSkillManager *)0x0) {
      return;
    }
    pCVar22 = (CSkill *)CSkillManager::getSkillByGuid(this,in_RDI[0x1232]);
    if (pCVar22 == (CSkill *)0x0) {
      return;
    }
    CSkillTooltip::showTooltip
              ((CSkillTooltip *)in_RDI[0x123e],(CBaseUnit *)in_RDI[0xb],pCVar22,
               (float)*(long *)(in_RDI[0x12] + 0x12d0),(float)*(long *)(in_RDI[0x12] + 0x12d8));
    return;
  }
  pWVar8 = *(Window **)(*(long *)(in_RDI[0x123e] + 0x30) + 0xb0);
joined_r0x00b9dfea:
  if (pWVar8 != (Window *)0x0) {
    CEGUI::Window::removeChildWindow(pWVar8);
  }
  return;
}

/* address=00ba16b0
   symbol=CPetMenu::setSlotIcon */

/* WARNING: Removing unreachable block (ram,0x00ba2529) */
/* WARNING: Removing unreachable block (ram,0x00ba2595) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CPetMenu::setSlotIcon(CEquipment*, int, int) */

void __thiscall CPetMenu::setSlotIcon(CPetMenu *this,CEquipment *param_1,int param_2,int param_3)

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
  uint *puVar14;
  CEquipment *this_00;
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
  String local_1568 [176];
  Image local_14b8 [176];
  String local_1408 [176];
  String local_1358 [176];
  Image local_12a8 [176];
  String local_11f8 [176];
  String local_1148 [176];
  String local_1098 [176];
  String local_fe8 [176];
  Image local_f38 [176];
  String local_e88 [176];
  String local_dd8 [176];
  Image local_d28 [176];
  String local_c78 [176];
  String local_bc8 [176];
  Image local_b18 [176];
  String local_a68 [176];
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
  String local_648 [176];
  String local_598 [176];
  String local_4e8 [176];
  Image local_438 [176];
  String local_388 [176];
  String local_2d8 [176];
  Image local_228 [176];
  String local_178 [184];
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
    CEquipment::createIcon(param_1,*(CGameUI **)(this + 0x90),false);
    pUVar17 = *(UVector2 **)(param_1 + 0x2c8);
    if (pUVar17 != (UVector2 *)0x0) {
      CEGUI::EventSet::setMutedState((bool)((char)pUVar17 + '8'));
      pUVar17[0x3e2] = (UVector2)0x1;
      goto LAB_00ba179c;
    }
  }
  else {
LAB_00ba179c:
    if (*(Window **)(pUVar17 + 0xb0) != (Window *)0x0) {
      CEGUI::Window::removeChildWindow(*(Window **)(pUVar17 + 0xb0));
    }
    CEGUI::Window::addChildWindow(*(Window **)(this + lVar16 * 8 + 0x1378));
    local_64 = 0;
    local_68 = 0;
    local_5c = 0x3f800000;
    local_60 = 0;
                    /* try { // try from 00ba17fc to 00ba1800 has its CatchHandler @ 00ba25f5 */
    CEGUI::Window::setPosition(pUVar17);
    local_74 = 0;
    local_78 = 0;
    local_6c = 0;
    local_70 = 0;
                    /* try { // try from 00ba1838 to 00ba183c has its CatchHandler @ 00ba2607 */
    CEGUI::Window::setPosition(pUVar17);
    CEGUI::Window::getSize();
                    /* try { // try from 00ba1860 to 00ba1864 has its CatchHandler @ 00ba2605 */
    CEGUI::Window::setSize(pUVar17);
    CEGUI::Window::moveToFront();
    *(CPetMenu **)(pUVar17 + 0x1d8) = this + (long)param_3 * 4 + 0xa0;
  }
  if ((param_1[0x348] == (CEquipment)0x0) || (*(uint *)(param_1 + 0x3e0) == 0)) {
    CEGUI::String::String(local_648,"");
                    /* try { // try from 00ba18bd to 00ba18c1 has its CatchHandler @ 00ba2667 */
    CEGUI::String::String(local_598,"Image");
                    /* try { // try from 00ba18d5 to 00ba18d9 has its CatchHandler @ 00ba25d2 */
    CEGUI::PropertySet::setProperty(*(String **)(this + lVar16 * 8 + 0x1b28),local_598);
                    /* try { // try from 00ba18dd to 00ba18e1 has its CatchHandler @ 00ba2667 */
    CEGUI::String::~String(local_598);
    CEGUI::String::~String(local_648);
  }
  else {
    if (*(uint *)(param_1 + 0x3e0) < 2) {
      pSVar19 = local_388;
      CEGUI::String::String(pSVar19,"onesocketglow");
                    /* try { // try from 00ba2438 to 00ba244f has its CatchHandler @ 00ba24bc */
      CEGUI::Imageset::getImage(*(String **)(this + 0x9108));
      CEGUI::PropertyHelper::imageToString(local_438);
                    /* try { // try from 00ba2460 to 00ba2464 has its CatchHandler @ 00ba24b7 */
      CEGUI::String::String(local_4e8,"Image");
                    /* try { // try from 00ba2478 to 00ba247c has its CatchHandler @ 00ba24b5 */
      CEGUI::PropertySet::setProperty(*(String **)(this + lVar16 * 8 + 0x1b28),local_4e8);
                    /* try { // try from 00ba2480 to 00ba2484 has its CatchHandler @ 00ba24b7 */
      CEGUI::String::~String(local_4e8);
                    /* try { // try from 00ba2488 to 00ba248c has its CatchHandler @ 00ba24bc */
      CEGUI::String::~String((String *)local_438);
    }
    else {
      pSVar19 = local_178;
      CEGUI::String::String(pSVar19,"twosocketglow");
                    /* try { // try from 00ba210c to 00ba2123 has its CatchHandler @ 00ba2662 */
      CEGUI::Imageset::getImage(*(String **)(this + 0x9108));
      CEGUI::PropertyHelper::imageToString(local_228);
                    /* try { // try from 00ba2134 to 00ba2138 has its CatchHandler @ 00ba2635 */
      CEGUI::String::String(local_2d8,"Image");
                    /* try { // try from 00ba214c to 00ba2150 has its CatchHandler @ 00ba2645 */
      CEGUI::PropertySet::setProperty(*(String **)(this + lVar16 * 8 + 0x1b28),local_2d8);
                    /* try { // try from 00ba2154 to 00ba2158 has its CatchHandler @ 00ba2635 */
      CEGUI::String::~String(local_2d8);
                    /* try { // try from 00ba215c to 00ba2160 has its CatchHandler @ 00ba2662 */
      CEGUI::String::~String((String *)local_228);
    }
    CEGUI::String::~String(pSVar19);
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
                    /* try { // try from 00ba19c5 to 00ba19dc has its CatchHandler @ 00ba261a */
    CEGUI::Imageset::getImage(*(String **)(this + 0x9108));
    CEGUI::PropertyHelper::imageToString(local_7a8);
    local_850 = 0x20;
    local_848 = 0;
    local_838 = 0;
    local_840 = 0;
    local_7b0 = (uint *)0x0;
    local_858 = 0;
    local_830[0] = 0;
                    /* try { // try from 00ba1a40 to 00ba1a44 has its CatchHandler @ 00ba2609 */
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
                    /* try { // try from 00ba1aad to 00ba1ab1 has its CatchHandler @ 00ba2622 */
    CEGUI::PropertySet::setProperty(*(String **)(this + lVar16 * 8 + 0x1608),(String *)&local_858);
                    /* try { // try from 00ba1ab5 to 00ba1ab9 has its CatchHandler @ 00ba2609 */
    CEGUI::String::~String((String *)&local_858);
                    /* try { // try from 00ba1abd to 00ba1ac1 has its CatchHandler @ 00ba261a */
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
                    /* try { // try from 00ba1efe to 00ba1f02 has its CatchHandler @ 00ba25cd */
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
                    /* try { // try from 00ba1f6d to 00ba1f71 has its CatchHandler @ 00ba262f */
    CEGUI::PropertySet::setProperty(*(String **)(this + lVar16 * 8 + 0x1608),(String *)&local_908);
                    /* try { // try from 00ba1f75 to 00ba1f79 has its CatchHandler @ 00ba25cd */
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
        if (pUVar17 != (UVector2 *)0x0) goto LAB_00ba1bba;
LAB_00ba1d10:
        CEquipment::createIcon(this_00,*(CGameUI **)(this + 0x90),false);
        pUVar17 = *(UVector2 **)(this_00 + 0x2c8);
        if (pUVar17 != (UVector2 *)0x0) {
          CEGUI::EventSet::setMutedState((bool)((char)pUVar17 + '8'));
          pUVar17[0x3e2] = (UVector2)0x1;
          goto LAB_00ba1bba;
        }
      }
      else {
        this_00 = (CEquipment *)**(long **)(param_1 + 1000);
        pUVar17 = *(UVector2 **)(this_00 + 0x2c8);
        if (pUVar17 == (UVector2 *)0x0) goto LAB_00ba1d10;
LAB_00ba1bba:
        if (*(Window **)(pUVar17 + 0xb0) != (Window *)0x0) {
          CEGUI::Window::removeChildWindow(*(Window **)(pUVar17 + 0xb0));
        }
        CEGUI::Window::addChildWindow(*(Window **)(this + 0x30));
        local_a4 = (float)((long)((float)(int)((float)(~uVar21 & uVar8 | uVar7 & uVar21) +
                                              fVar3 * 0.0) + fVar4) & 0xffffffff);
        local_9c = (float)(uVar20 & 0xffffffff);
        local_a8 = 0;
        local_a0 = 0;
                    /* try { // try from 00ba1c24 to 00ba1c28 has its CatchHandler @ 00ba261f */
        CEGUI::Window::setPosition(pUVar17);
        CEGUI::Window::getSize();
                    /* try { // try from 00ba1c46 to 00ba1c4a has its CatchHandler @ 00ba2655 */
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
  cVar9 = (**(code **)(*(long *)param_1 + 0x2f8))
                    (param_1,*(undefined8 *)(*(long *)(this + 0x58) + 0x640),0);
  if (cVar9 == '\0') {
    cVar9 = (**(code **)(*(long *)param_1 + 0x2b0))(param_1);
    if (cVar9 == '\0') {
      pSVar19 = local_1408;
      CEGUI::String::String(pSVar19,"redslotglow");
                    /* try { // try from 00ba1fb3 to 00ba1fca has its CatchHandler @ 00ba25a2 */
      CEGUI::Imageset::getImage(*(String **)(this + 0x9108));
      CEGUI::PropertyHelper::imageToString(local_14b8);
                    /* try { // try from 00ba1fdb to 00ba1fdf has its CatchHandler @ 00ba25a7 */
      CEGUI::String::String(local_1568,"Image");
                    /* try { // try from 00ba1ff3 to 00ba1ff7 has its CatchHandler @ 00ba25ac */
      CEGUI::PropertySet::setProperty(*(String **)(this + lVar16 * 8 + 0x1898),local_1568);
                    /* try { // try from 00ba1ffb to 00ba1fff has its CatchHandler @ 00ba25a7 */
      CEGUI::String::~String(local_1568);
                    /* try { // try from 00ba2003 to 00ba2007 has its CatchHandler @ 00ba25a2 */
      CEGUI::String::~String((String *)local_14b8);
    }
    else {
      pSVar19 = local_11f8;
      CEGUI::String::String(pSVar19,"blueredslotglow");
                    /* try { // try from 00ba21c6 to 00ba21dd has its CatchHandler @ 00ba256d */
      CEGUI::Imageset::getImage(*(String **)(this + 0x9108));
      CEGUI::PropertyHelper::imageToString(local_12a8);
                    /* try { // try from 00ba21ee to 00ba21f2 has its CatchHandler @ 00ba2585 */
      CEGUI::String::String(local_1358,"Image");
                    /* try { // try from 00ba2206 to 00ba220a has its CatchHandler @ 00ba2572 */
      CEGUI::PropertySet::setProperty(*(String **)(this + lVar16 * 8 + 0x1898),local_1358);
                    /* try { // try from 00ba220e to 00ba2212 has its CatchHandler @ 00ba2585 */
      CEGUI::String::~String(local_1358);
                    /* try { // try from 00ba2216 to 00ba221a has its CatchHandler @ 00ba256d */
      CEGUI::String::~String((String *)local_12a8);
    }
  }
  else {
    cVar9 = CBaseUnit::ISA((CBaseUnit *)param_1,0x36);
    if (cVar9 == '\0') {
      cVar9 = (**(code **)(*(long *)param_1 + 0x2b0))(param_1);
      if (cVar9 == '\0') {
        CEGUI::String::String(local_1148,"");
                    /* try { // try from 00ba2333 to 00ba2337 has its CatchHandler @ 00ba24e5 */
        CEGUI::String::String(local_1098,"Image");
                    /* try { // try from 00ba234b to 00ba234f has its CatchHandler @ 00ba24c6 */
        CEGUI::PropertySet::setProperty(*(String **)(this + lVar16 * 8 + 0x1898),local_1098);
                    /* try { // try from 00ba2353 to 00ba2357 has its CatchHandler @ 00ba24e5 */
        CEGUI::String::~String(local_1098);
        CEGUI::String::~String(local_1148);
        goto LAB_00ba2010;
      }
      cVar9 = CBaseUnit::ISA((CBaseUnit *)param_1,0x37);
      if (cVar9 == '\0') {
        pSVar19 = local_e88;
        CEGUI::String::String(pSVar19,"greenslotglow");
                    /* try { // try from 00ba23bf to 00ba23d6 has its CatchHandler @ 00ba2695 */
        CEGUI::Imageset::getImage(*(String **)(this + 0x9108));
        CEGUI::PropertyHelper::imageToString(local_f38);
                    /* try { // try from 00ba23e7 to 00ba23eb has its CatchHandler @ 00ba2685 */
        CEGUI::String::String(local_fe8,"Image");
                    /* try { // try from 00ba23ff to 00ba2403 has its CatchHandler @ 00ba2675 */
        CEGUI::PropertySet::setProperty(*(String **)(this + lVar16 * 8 + 0x1898),local_fe8);
                    /* try { // try from 00ba2407 to 00ba240b has its CatchHandler @ 00ba2685 */
        CEGUI::String::~String(local_fe8);
                    /* try { // try from 00ba240f to 00ba2413 has its CatchHandler @ 00ba2695 */
        CEGUI::String::~String((String *)local_f38);
      }
      else {
        pSVar19 = local_c78;
        CEGUI::String::String(pSVar19,"blueslotglow");
                    /* try { // try from 00ba2268 to 00ba227f has its CatchHandler @ 00ba24c4 */
        CEGUI::Imageset::getImage(*(String **)(this + 0x9108));
        CEGUI::PropertyHelper::imageToString(local_d28);
                    /* try { // try from 00ba2290 to 00ba2294 has its CatchHandler @ 00ba24c2 */
        CEGUI::String::String(local_dd8,"Image");
                    /* try { // try from 00ba22a8 to 00ba22ac has its CatchHandler @ 00ba2492 */
        CEGUI::PropertySet::setProperty(*(String **)(this + lVar16 * 8 + 0x1898),local_dd8);
                    /* try { // try from 00ba22b0 to 00ba22b4 has its CatchHandler @ 00ba24c2 */
        CEGUI::String::~String(local_dd8);
                    /* try { // try from 00ba22b8 to 00ba22bc has its CatchHandler @ 00ba24c4 */
        CEGUI::String::~String((String *)local_d28);
      }
    }
    else {
      pSVar19 = local_a68;
      CEGUI::String::String(pSVar19,"goldslotglow");
                    /* try { // try from 00ba1dad to 00ba1dc4 has its CatchHandler @ 00ba2577 */
      CEGUI::Imageset::getImage(*(String **)(this + 0x9108));
      CEGUI::PropertyHelper::imageToString(local_b18);
                    /* try { // try from 00ba1dd5 to 00ba1dd9 has its CatchHandler @ 00ba25d7 */
      CEGUI::String::String(local_bc8,"Image");
                    /* try { // try from 00ba1ded to 00ba1df1 has its CatchHandler @ 00ba25e5 */
      CEGUI::PropertySet::setProperty(*(String **)(this + lVar16 * 8 + 0x1898),local_bc8);
                    /* try { // try from 00ba1df5 to 00ba1df9 has its CatchHandler @ 00ba25d7 */
      CEGUI::String::~String(local_bc8);
                    /* try { // try from 00ba1dfd to 00ba1e01 has its CatchHandler @ 00ba2577 */
      CEGUI::String::~String((String *)local_b18);
    }
  }
  CEGUI::String::~String(pSVar19);
LAB_00ba2010:
  if (*(long *)(this + lVar16 * 8 + 0x1db8) != 0) {
    bVar18 = SUB81(*(long *)(this + lVar16 * 8 + 0x1db8),0);
    if (*(int *)(param_1 + 0x238) < 2) {
      CEGUI::Window::setVisible(bVar18);
    }
    else {
      CEGUI::Window::setVisible(bVar18);
      STRINGS::GetValueAsString((STRINGS *)local_58,*(int *)(param_1 + 0x238));
                    /* try { // try from 00ba2068 to 00ba206c has its CatchHandler @ 00ba25b5 */
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
                    /* try { // try from 00ba2096 to 00ba209a has its CatchHandler @ 00ba2516 */
      CEGUI::String::String(local_1618,local_48[0]);
                    /* try { // try from 00ba20ab to 00ba20af has its CatchHandler @ 00ba2534 */
      CEGUI::Window::setText(*(String **)(this + lVar16 * 8 + 0x1db8));
                    /* try { // try from 00ba20b3 to 00ba20b7 has its CatchHandler @ 00ba2516 */
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

/* address=00ba26b0
   symbol=CPetMenu::updateLayout */

/* WARNING: Removing unreachable block (ram,0x00ba501d) */
/* WARNING: Removing unreachable block (ram,0x00ba50dd) */
/* WARNING: Removing unreachable block (ram,0x00ba4ced) */
/* WARNING: Removing unreachable block (ram,0x00ba4c8e) */
/* WARNING: Removing unreachable block (ram,0x00ba5000) */
/* WARNING: Removing unreachable block (ram,0x00ba516f) */
/* WARNING: Removing unreachable block (ram,0x00ba4cf8) */
/* WARNING: Removing unreachable block (ram,0x00ba506a) */
/* WARNING: Removing unreachable block (ram,0x00ba50e8) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CPetMenu::updateLayout() */

void __thiscall CPetMenu::updateLayout(CPetMenu *this)

{
  wchar_t *pwVar1;
  int *piVar2;
  wchar_t wVar3;
  byte bVar4;
  CInventory *this_00;
  Window *pWVar5;
  float fVar6;
  float fVar7;
  char cVar8;
  int iVar9;
  float *pfVar10;
  byte *pbVar11;
  char *pcVar12;
  CEquipment *this_01;
  uchar *puVar13;
  CSkill *this_02;
  long *plVar14;
  undefined4 *puVar15;
  uint *puVar16;
  undefined8 *puVar17;
  long lVar18;
  UVector2 *pUVar19;
  ulong uVar20;
  uint uVar21;
  CPetMenu *pCVar22;
  String *pSVar23;
  CEquipment *pCVar24;
  uint uVar25;
  uint uVar26;
  uint uVar27;
  float fVar28;
  float fVar29;
  float fVar30;
  float fVar31;
  uint uVar32;
  int local_22c8;
  UVector2 *local_22b8;
  String local_2268 [176];
  undefined8 local_21b8;
  ulong local_21b0;
  undefined8 local_21a8;
  undefined8 local_21a0;
  undefined8 local_2198;
  undefined4 local_2190 [32];
  undefined4 *local_2110;
  undefined8 local_2108;
  ulong local_2100;
  undefined8 local_20f8;
  undefined8 local_20f0;
  undefined8 local_20e8;
  uint local_20e0 [5];
  uint local_20cc [27];
  uint *local_2060;
  undefined8 local_2058;
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
  uint local_1f80 [5];
  uint local_1f6c [27];
  uint *local_1f00;
  undefined8 local_1ef8;
  ulong local_1ef0;
  undefined8 local_1ee8;
  undefined8 local_1ee0;
  undefined8 local_1ed8;
  undefined4 local_1ed0 [32];
  undefined4 *local_1e50;
  undefined8 local_1e48;
  ulong local_1e40;
  undefined8 local_1e38;
  undefined8 local_1e30;
  undefined8 local_1e28;
  uint local_1e20 [5];
  uint local_1e0c [27];
  uint *local_1da0;
  String local_1d98 [176];
  String local_1ce8 [176];
  String local_1c38 [176];
  String local_1b88 [176];
  String local_1ad8 [176];
  Image local_1a28 [176];
  String local_1978 [176];
  String local_18c8 [176];
  String local_1818 [176];
  String local_1768 [176];
  String local_16b8 [176];
  String local_1608 [176];
  undefined8 local_1558;
  ulong local_1550;
  undefined8 local_1548;
  undefined8 local_1540;
  undefined8 local_1538;
  undefined4 local_1530 [32];
  undefined4 *local_14b0;
  String local_14a8 [176];
  String local_13f8 [176];
  undefined8 local_1348;
  ulong local_1340;
  undefined8 local_1338;
  undefined8 local_1330;
  undefined8 local_1328;
  undefined4 local_1320 [32];
  undefined4 *local_12a0;
  undefined8 local_1298;
  ulong local_1290;
  undefined8 local_1288;
  undefined8 local_1280;
  undefined8 local_1278;
  uint local_1270 [5];
  uint local_125c [27];
  uint *local_11f0;
  undefined8 local_11e8;
  ulong local_11e0;
  undefined8 local_11d8;
  undefined8 local_11d0;
  undefined8 local_11c8;
  undefined4 local_11c0 [32];
  undefined4 *local_1140;
  undefined8 local_1138;
  ulong local_1130;
  undefined8 local_1128;
  undefined8 local_1120;
  undefined8 local_1118;
  uint local_1110 [5];
  uint local_10fc [27];
  uint *local_1090;
  undefined8 local_1088;
  ulong local_1080;
  undefined8 local_1078;
  undefined8 local_1070;
  undefined8 local_1068;
  uint local_1060 [5];
  uint local_104c [27];
  uint *local_fe0;
  Image local_fd8 [176];
  undefined8 local_f28;
  ulong local_f20;
  undefined8 local_f18;
  undefined8 local_f10;
  undefined8 local_f08;
  uint local_f00 [13];
  uint local_ecc [19];
  uint *local_e80;
  undefined8 local_e78;
  ulong local_e70;
  undefined8 local_e68;
  undefined8 local_e60;
  undefined8 local_e58;
  uint local_e50 [5];
  uint local_e3c [27];
  uint *local_dd0;
  Image local_dc8 [176];
  undefined8 local_d18;
  ulong local_d10;
  undefined8 local_d08;
  undefined8 local_d00;
  undefined8 local_cf8;
  uint local_cf0 [12];
  uint local_cc0 [20];
  uint *local_c70;
  undefined8 local_c68;
  ulong local_c60;
  undefined8 local_c58;
  undefined8 local_c50;
  undefined8 local_c48;
  uint local_c40 [5];
  uint local_c2c [27];
  uint *local_bc0;
  Image local_bb8 [176];
  undefined8 local_b08;
  ulong local_b00;
  undefined8 local_af8;
  undefined8 local_af0;
  undefined8 local_ae8;
  uint local_ae0 [12];
  uint local_ab0 [20];
  uint *local_a60;
  undefined8 local_a58;
  ulong local_a50;
  undefined8 local_a48;
  undefined8 local_a40;
  undefined8 local_a38;
  undefined4 local_a30 [32];
  undefined4 *local_9b0;
  undefined8 local_9a8;
  ulong local_9a0;
  undefined8 local_998;
  undefined8 local_990;
  undefined8 local_988;
  uint local_980 [5];
  uint local_96c [27];
  uint *local_900;
  undefined8 local_8f8;
  ulong local_8f0;
  undefined8 local_8e8;
  undefined8 local_8e0;
  undefined8 local_8d8;
  uint local_8d0 [5];
  uint local_8bc [27];
  uint *local_850;
  Image local_848 [176];
  undefined8 local_798;
  ulong local_790;
  undefined8 local_788;
  undefined8 local_780;
  undefined8 local_778;
  uint local_770 [12];
  uint local_740 [20];
  uint *local_6f0;
  undefined8 local_6e8;
  ulong local_6e0;
  undefined8 local_6d8;
  undefined8 local_6d0;
  undefined8 local_6c8;
  undefined4 local_6c0 [32];
  undefined4 *local_640;
  undefined8 local_638;
  ulong local_630;
  undefined8 local_628;
  undefined8 local_620;
  undefined8 local_618;
  uint local_610 [5];
  uint local_5fc [27];
  uint *local_590;
  String local_588 [176];
  Image local_4d8 [176];
  String local_428 [176];
  undefined8 local_378;
  ulong local_370;
  undefined8 local_368;
  undefined8 local_360;
  undefined8 local_358;
  uint local_350 [5];
  uint local_33c [27];
  uint *local_2d0;
  Image local_2c8 [176];
  undefined8 local_218;
  ulong local_210;
  undefined8 local_208;
  undefined8 local_200;
  undefined8 local_1f8;
  uint local_1f0 [13];
  uint local_1bc [19];
  uint *local_170;
  float local_148;
  float local_144;
  undefined4 local_140;
  float local_13c;
  undefined4 local_138;
  undefined4 local_134;
  undefined4 local_130;
  undefined4 local_12c;
  undefined4 local_128;
  undefined4 local_124;
  undefined4 local_120;
  undefined4 local_11c;
  float local_110;
  float local_10c;
  undefined4 local_f8;
  float local_f4;
  undefined4 local_f0;
  float local_ec;
  float local_e0;
  float local_dc;
  uchar *local_d8 [2];
  long local_c8 [2];
  uchar *local_b8 [2];
  long local_a8 [2];
  wchar_t *local_98 [2];
  long local_88 [2];
  wchar_t *local_78 [2];
  long local_68 [2];
  wchar_t *local_58 [5];

  if (((*(long *)(this + 0x58) != 0) && (this[0x68] != (CPetMenu)0x0)) &&
     (this_00 = *(CInventory **)(*(long *)(this + 0x58) + 0x490), this_00 != (CInventory *)0x0)) {
    while (pWVar5 = *(Window **)(this + 0x30),
          *(long *)(pWVar5 + 0x80) - *(long *)(pWVar5 + 0x78) >> 3 != 0) {
      CEGUI::Window::removeChildWindow(pWVar5);
    }
    lVar18 = 0;
    do {
      while ((pWVar5 = *(Window **)(this + lVar18 + 0x1378), pWVar5 != (Window *)0x0 &&
             (*(long *)(pWVar5 + 0x80) - *(long *)(pWVar5 + 0x78) >> 3 != 0))) {
        lVar18 = lVar18 + 8;
        CEGUI::Window::removeChildWindow(pWVar5);
        if (lVar18 == 0x60) goto LAB_00ba2760;
      }
      lVar18 = lVar18 + 8;
    } while (lVar18 != 0x60);
LAB_00ba2760:
    uVar21 = 0;
    pCVar22 = this;
    do {
      while (*(long *)(pCVar22 + 0x1378) == 0) {
LAB_00ba313c:
        uVar21 = uVar21 + 1;
        pCVar22 = pCVar22 + 8;
        if (uVar21 == 0xc) goto LAB_00ba3150;
      }
      lVar18 = CInventory::getEquipmentRefInSlot(this_00,uVar21);
      if (lVar18 == 0) {
        if (*(long *)(pCVar22 + 0x1378) != 0) {
          local_1550 = 0x20;
          local_1548 = 0;
          local_1538 = 0;
          local_1540 = 0;
          local_14b0 = (undefined4 *)0x0;
          local_1558 = 0;
          local_1530[0] = 0;
          CEGUI::String::grow((ulong)&local_1558);
          puVar15 = local_1530;
          if (0x20 < local_1550) {
            puVar15 = local_14b0;
          }
          local_1558 = 0;
          *puVar15 = 0;
                    /* try { // try from 00ba2fa0 to 00ba2fa4 has its CatchHandler @ 00ba4ea5 */
          CEGUI::String::String(local_14a8,"Image");
                    /* try { // try from 00ba2fb7 to 00ba2fbb has its CatchHandler @ 00ba4ebd */
          CEGUI::PropertySet::setProperty(*(String **)(pCVar22 + 0x1608),local_14a8);
                    /* try { // try from 00ba2fbf to 00ba2fc3 has its CatchHandler @ 00ba4ea5 */
          CEGUI::String::~String(local_14a8);
          CEGUI::String::~String((String *)&local_1558);
          CEGUI::String::String(local_16b8,"");
                    /* try { // try from 00ba2ff6 to 00ba2ffa has its CatchHandler @ 00ba4eca */
          CEGUI::String::String(local_1608,"Image");
                    /* try { // try from 00ba3008 to 00ba300c has its CatchHandler @ 00ba4ecf */
          CEGUI::PropertySet::setProperty(*(String **)(pCVar22 + 0x1b28),local_1608);
                    /* try { // try from 00ba3010 to 00ba3014 has its CatchHandler @ 00ba4eca */
          CEGUI::String::~String(local_1608);
          CEGUI::String::~String(local_16b8);
          CEGUI::Window::getSize();
                    /* try { // try from 00ba303e to 00ba3042 has its CatchHandler @ 00ba4ed5 */
          CEGUI::Window::setSize(*(UVector2 **)(pCVar22 + 0x1b28));
          CEGUI::String::String(local_1818,"");
                    /* try { // try from 00ba3068 to 00ba306c has its CatchHandler @ 00ba4ee5 */
          CEGUI::String::String(local_1768,"Image");
                    /* try { // try from 00ba307a to 00ba307e has its CatchHandler @ 00ba4ef5 */
          CEGUI::PropertySet::setProperty(*(String **)(pCVar22 + 0x1898),local_1768);
                    /* try { // try from 00ba3082 to 00ba3086 has its CatchHandler @ 00ba4ee5 */
          CEGUI::String::~String(local_1768);
          CEGUI::String::~String(local_1818);
          CEGUI::Window::getSize();
                    /* try { // try from 00ba30b0 to 00ba30b4 has its CatchHandler @ 00ba4f05 */
          CEGUI::Window::setSize(*(UVector2 **)(pCVar22 + 0x1898));
          puVar13 = (uchar *)CEGUI::String::build_utf8_buff();
          CEGUI::String::String(local_18c8,puVar13);
                    /* try { // try from 00ba30ef to 00ba30f3 has its CatchHandler @ 00ba4f15 */
          CEGUI::Window::setTooltipText(*(String **)(pCVar22 + 0x1378));
          CEGUI::String::~String(local_18c8);
          CEGUI::String::String(local_1978,"Image");
                    /* try { // try from 00ba312f to 00ba3133 has its CatchHandler @ 00ba4f2d */
          CEGUI::PropertySet::setProperty(*(String **)(pCVar22 + 0x1378),local_1978);
          CEGUI::String::~String(local_1978);
        }
        goto LAB_00ba313c;
      }
      pCVar24 = *(CEquipment **)(lVar18 + 0x10);
      local_22b8 = *(UVector2 **)(pCVar24 + 0x2c8);
      if (local_22b8 == (UVector2 *)0x0) {
        CEquipment::createIcon(pCVar24,*(CGameUI **)(this + 0x90),false);
        local_22b8 = *(UVector2 **)(pCVar24 + 0x2c8);
        if (local_22b8 != (UVector2 *)0x0) {
          CEGUI::EventSet::setMutedState((bool)((char)local_22b8 + '8'));
          local_22b8[0x3e2] = (UVector2)0x1;
          goto LAB_00ba2806;
        }
      }
      else {
LAB_00ba2806:
        if (*(Window **)(local_22b8 + 0xb0) != (Window *)0x0) {
          CEGUI::Window::removeChildWindow(*(Window **)(local_22b8 + 0xb0));
        }
        CEGUI::Window::addChildWindow(*(Window **)(pCVar22 + 0x1378));
      }
      pfVar10 = (float *)CEGUI::Window::getPosition();
      fVar7 = DAT_00fa86f4;
      fVar6 = DAT_00fa4810;
      fVar30 = *pfVar10;
      uVar25 = -(uint)(0.0 < fVar30 * 0.0);
      uVar32 = (uint)DAT_00fa4810 & uVar25;
      uVar27 = ~uVar25 & (uint)DAT_00fa86f4;
      fVar28 = pfVar10[1];
      lVar18 = CEGUI::Window::getPosition();
      fVar31 = *(float *)(lVar18 + 8) * 0.0;
      uVar25 = -(uint)(0.0 < fVar31);
      fVar29 = *(float *)(lVar18 + 0xc);
      if (((pCVar24[0x348] == (CEquipment)0x0) || (*(int *)(pCVar24 + 0x3e0) == 0)) ||
         (cVar8 = CEGUI::Window::isVisible
                            (SUB81(*(undefined8 *)(*(long *)(pCVar22 + 0x1378) + 0xb0),0)),
         cVar8 == '\0')) {
        local_6e0 = 0x20;
        local_6d8 = 0;
        local_6c8 = 0;
        local_6d0 = 0;
        local_640 = (undefined4 *)0x0;
        local_6e8 = 0;
        local_6c0[0] = 0;
        CEGUI::String::grow((ulong)&local_6e8);
        local_6e8 = 0;
        puVar15 = local_6c0;
        if (0x20 < local_6e0) {
          puVar15 = local_640;
        }
        *puVar15 = 0;
        local_630 = 0x20;
        local_628 = 0;
        local_618 = 0;
        local_620 = 0;
        local_590 = (uint *)0x0;
        local_638 = 0;
        local_610[0] = 0;
                    /* try { // try from 00ba29d1 to 00ba29d5 has its CatchHandler @ 00ba4d59 */
        CEGUI::String::grow((ulong)&local_638);
        puVar16 = local_590;
        if (local_630 < 0x21) {
          puVar16 = local_610;
        }
        pbVar11 = (byte *)0xfd0c0d;
        do {
          bVar4 = *pbVar11;
          pbVar11 = pbVar11 + 1;
          *puVar16 = (uint)bVar4;
          puVar16 = puVar16 + 1;
        } while (pbVar11 != (byte *)0xfd0c12);
        local_638 = 5;
        puVar16 = local_5fc;
        if (0x20 < local_630) {
          puVar16 = local_590 + 5;
        }
        *puVar16 = 0;
                    /* try { // try from 00ba2a5a to 00ba2a5e has its CatchHandler @ 00ba4d34 */
        CEGUI::PropertySet::setProperty(*(String **)(pCVar22 + 0x1b28),(String *)&local_638);
                    /* try { // try from 00ba2a67 to 00ba2a6b has its CatchHandler @ 00ba4d59 */
        CEGUI::String::~String((String *)&local_638);
        CEGUI::String::~String((String *)&local_6e8);
      }
      else {
        if (*(uint *)(pCVar24 + 0x3e0) < 2) {
          if (*(uint *)(pCVar24 + 0x3e0) == 1) {
            CEGUI::String::String(local_428,"onesocketglow");
                    /* try { // try from 00ba4967 to 00ba497e has its CatchHandler @ 00ba5118 */
            CEGUI::Imageset::getImage(*(String **)(this + 0x9108));
            CEGUI::PropertyHelper::imageToString(local_4d8);
                    /* try { // try from 00ba498f to 00ba4993 has its CatchHandler @ 00ba5130 */
            CEGUI::String::String(local_588,"Image");
                    /* try { // try from 00ba49a1 to 00ba49a5 has its CatchHandler @ 00ba513d */
            CEGUI::PropertySet::setProperty(*(String **)(pCVar22 + 0x1b28),local_588);
                    /* try { // try from 00ba49a9 to 00ba49ad has its CatchHandler @ 00ba5130 */
            CEGUI::String::~String(local_588);
                    /* try { // try from 00ba49b1 to 00ba49b5 has its CatchHandler @ 00ba5118 */
            CEGUI::String::~String((String *)local_4d8);
            CEGUI::String::~String(local_428);
          }
        }
        else {
          local_210 = 0x20;
          local_208 = 0;
          local_1f8 = 0;
          local_200 = 0;
          local_170 = (uint *)0x0;
          local_218 = 0;
          local_1f0[0] = 0;
          CEGUI::String::grow((ulong)&local_218);
          puVar16 = local_1f0;
          if (0x20 < local_210) {
            puVar16 = local_170;
          }
          pcVar12 = "twosocketglow";
          do {
            bVar4 = *pcVar12;
            pcVar12 = pcVar12 + 1;
            *puVar16 = (uint)bVar4;
            puVar16 = puVar16 + 1;
          } while ((byte *)pcVar12 != (byte *)0xfe60d0);
          local_218 = 0xd;
          puVar16 = local_1bc;
          if (0x20 < local_210) {
            puVar16 = local_170 + 0xd;
          }
          *puVar16 = 0;
                    /* try { // try from 00ba442d to 00ba4441 has its CatchHandler @ 00ba50d8 */
          CEGUI::Imageset::getImage(*(String **)(this + 0x9108));
          CEGUI::PropertyHelper::imageToString(local_2c8);
          local_370 = 0x20;
          local_368 = 0;
          local_358 = 0;
          local_360 = 0;
          local_2d0 = (uint *)0x0;
          local_378 = 0;
          local_350[0] = 0;
                    /* try { // try from 00ba44a5 to 00ba44a9 has its CatchHandler @ 00ba50f6 */
          CEGUI::String::grow((ulong)&local_378);
          puVar16 = local_350;
          if (0x20 < local_370) {
            puVar16 = local_2d0;
          }
          pbVar11 = (byte *)0xfd0c0d;
          do {
            bVar4 = *pbVar11;
            pbVar11 = pbVar11 + 1;
            *puVar16 = (uint)bVar4;
            puVar16 = puVar16 + 1;
          } while (pbVar11 != (byte *)0xfd0c12);
          local_378 = 5;
          puVar16 = local_33c;
          if (0x20 < local_370) {
            puVar16 = local_2d0 + 5;
          }
          *puVar16 = 0;
                    /* try { // try from 00ba4524 to 00ba4528 has its CatchHandler @ 00ba510b */
          CEGUI::PropertySet::setProperty(*(String **)(pCVar22 + 0x1b28),(String *)&local_378);
                    /* try { // try from 00ba452c to 00ba4530 has its CatchHandler @ 00ba50f6 */
          CEGUI::String::~String((String *)&local_378);
                    /* try { // try from 00ba4539 to 00ba453d has its CatchHandler @ 00ba50d8 */
          CEGUI::String::~String((String *)local_2c8);
          CEGUI::String::~String((String *)&local_218);
        }
        CEGUI::Window::moveToFront();
      }
      if (pCVar24[0x348] == (CEquipment)0x0) {
        pSVar23 = (String *)&local_798;
        local_790 = 0x20;
        local_788 = 0;
        local_778 = 0;
        local_780 = 0;
        local_6f0 = (uint *)0x0;
        local_798 = 0;
        local_770[0] = 0;
        CEGUI::String::grow((ulong)pSVar23);
        puVar16 = local_770;
        if (0x20 < local_790) {
          puVar16 = local_6f0;
        }
        pcVar12 = "unidentified";
        do {
          bVar4 = *pcVar12;
          pcVar12 = pcVar12 + 1;
          *puVar16 = (uint)bVar4;
          puVar16 = puVar16 + 1;
        } while ((byte *)pcVar12 != (byte *)0xfef79d);
        local_798 = 0xc;
        puVar16 = local_740;
        if (0x20 < local_790) {
          puVar16 = local_6f0 + 0xc;
        }
        *puVar16 = 0;
                    /* try { // try from 00ba2b5d to 00ba2b71 has its CatchHandler @ 00ba4d84 */
        CEGUI::Imageset::getImage(*(String **)(this + 0x9108));
        CEGUI::PropertyHelper::imageToString(local_848);
        local_8f0 = 0x20;
        local_8e8 = 0;
        local_8d8 = 0;
        local_8e0 = 0;
        local_850 = (uint *)0x0;
        local_8f8 = 0;
        local_8d0[0] = 0;
                    /* try { // try from 00ba2bd5 to 00ba2bd9 has its CatchHandler @ 00ba4d7f */
        CEGUI::String::grow((ulong)&local_8f8);
        puVar16 = local_8d0;
        if (0x20 < local_8f0) {
          puVar16 = local_850;
        }
        pbVar11 = (byte *)0xfd0c0d;
        do {
          bVar4 = *pbVar11;
          pbVar11 = pbVar11 + 1;
          *puVar16 = (uint)bVar4;
          puVar16 = puVar16 + 1;
        } while (pbVar11 != (byte *)0xfd0c12);
        local_8f8 = 5;
        puVar16 = local_8bc;
        if (0x20 < local_8f0) {
          puVar16 = local_850 + 5;
        }
        *puVar16 = 0;
                    /* try { // try from 00ba2c54 to 00ba2c58 has its CatchHandler @ 00ba4d62 */
        CEGUI::PropertySet::setProperty(*(String **)(pCVar22 + 0x1608),(String *)&local_8f8);
                    /* try { // try from 00ba2c5c to 00ba2c60 has its CatchHandler @ 00ba4d7f */
        CEGUI::String::~String((String *)&local_8f8);
                    /* try { // try from 00ba2c69 to 00ba2c6d has its CatchHandler @ 00ba4d84 */
        CEGUI::String::~String((String *)local_848);
      }
      else {
        pSVar23 = (String *)&local_a58;
        local_a50 = 0x20;
        local_a48 = 0;
        local_a38 = 0;
        local_a40 = 0;
        local_9b0 = (undefined4 *)0x0;
        local_a58 = 0;
        local_a30[0] = 0;
        CEGUI::String::grow((ulong)pSVar23);
        local_a58 = 0;
        puVar15 = local_a30;
        if (0x20 < local_a50) {
          puVar15 = local_9b0;
        }
        *puVar15 = 0;
        local_9a0 = 0x20;
        local_998 = 0;
        local_988 = 0;
        local_990 = 0;
        local_900 = (uint *)0x0;
        local_9a8 = 0;
        local_980[0] = 0;
                    /* try { // try from 00ba410b to 00ba410f has its CatchHandler @ 00ba4d06 */
        CEGUI::String::grow((ulong)&local_9a8);
        puVar16 = local_980;
        if (0x20 < local_9a0) {
          puVar16 = local_900;
        }
        pbVar11 = (byte *)0xfd0c0d;
        do {
          bVar4 = *pbVar11;
          pbVar11 = pbVar11 + 1;
          *puVar16 = (uint)bVar4;
          puVar16 = puVar16 + 1;
        } while (pbVar11 != (byte *)0xfd0c12);
        local_9a8 = 5;
        puVar16 = local_96c;
        if (0x20 < local_9a0) {
          puVar16 = local_900 + 5;
        }
        *puVar16 = 0;
                    /* try { // try from 00ba417f to 00ba4183 has its CatchHandler @ 00ba4cd2 */
        CEGUI::PropertySet::setProperty(*(String **)(pCVar22 + 0x1608),(String *)&local_9a8);
                    /* try { // try from 00ba4187 to 00ba418b has its CatchHandler @ 00ba4d06 */
        CEGUI::String::~String((String *)&local_9a8);
      }
      CEGUI::String::~String(pSVar23);
      fVar29 = (float)(int)(fVar31 + (float)(~uVar25 & (uint)fVar7 | (uint)fVar6 & uVar25)) + fVar29
      ;
      if (1 < *(uint *)(pCVar24 + 0x3e0)) {
        CEGUI::Window::getSize();
        uVar25 = -(uint)(0.0 < local_e0 * 0.0);
        fVar29 = ((float)(int)((float)(~uVar25 & (uint)DAT_00fa86f4 | (uint)DAT_00fa4810 & uVar25) +
                              local_e0 * 0.0) + local_dc) * _DAT_00fe6520 + fVar29;
      }
      cVar8 = CEGUI::Window::isVisible(SUB81(*(undefined8 *)(*(long *)(pCVar22 + 0x1378) + 0xb0),0))
      ;
      if ((cVar8 != '\0') && (*(int *)(pCVar24 + 0x3f0) != 0)) {
        uVar25 = 0;
        do {
          if (uVar25 < *(uint *)(pCVar24 + 0x3f4)) {
            this_01 = *(CEquipment **)((ulong)uVar25 * 8 + *(long *)(pCVar24 + 1000));
            pUVar19 = *(UVector2 **)(this_01 + 0x2c8);
            if (pUVar19 != (UVector2 *)0x0) goto LAB_00ba2d5a;
LAB_00ba2eb2:
            CEquipment::createIcon(this_01,*(CGameUI **)(this + 0x90),false);
            pUVar19 = *(UVector2 **)(this_01 + 0x2c8);
            if (pUVar19 != (UVector2 *)0x0) {
              CEGUI::EventSet::setMutedState((bool)((char)pUVar19 + '8'));
              pUVar19[0x3e2] = (UVector2)0x1;
              goto LAB_00ba2d5a;
            }
          }
          else {
            this_01 = (CEquipment *)**(long **)(pCVar24 + 1000);
            pUVar19 = *(UVector2 **)(this_01 + 0x2c8);
            if (pUVar19 == (UVector2 *)0x0) goto LAB_00ba2eb2;
LAB_00ba2d5a:
            if (*(Window **)(pUVar19 + 0xb0) != (Window *)0x0) {
              CEGUI::Window::removeChildWindow(*(Window **)(pUVar19 + 0xb0));
            }
            cVar8 = CEGUI::Window::isChild(*(Window **)(this + 0x30));
            if (cVar8 == '\0') {
              CEGUI::Window::addChildWindow(*(Window **)(this + 0x30));
            }
            else if (pUVar19 == (UVector2 *)0x0) goto LAB_00ba2e05;
            local_f8 = 0;
            local_f0 = 0;
            local_f4 = (float)(int)((float)(uVar27 | uVar32) + fVar30 * 0.0) + fVar28;
            local_ec = fVar29;
                    /* try { // try from 00ba2dcd to 00ba2dd1 has its CatchHandler @ 00ba4d5e */
            CEGUI::Window::setPosition(pUVar19);
            CEGUI::Window::getSize();
                    /* try { // try from 00ba2df1 to 00ba2df5 has its CatchHandler @ 00ba4d2a */
            CEGUI::Window::setSize(pUVar19);
            CEGUI::Window::moveToFront();
            pUVar19[0x3e2] = (UVector2)0x1;
          }
LAB_00ba2e05:
          uVar25 = uVar25 + 1;
          CEGUI::Window::getSize();
          uVar26 = -(uint)(0.0 < local_110 * 0.0);
          if (*(uint *)(pCVar24 + 0x3f0) <= uVar25) break;
          fVar29 = ((float)(int)((float)(~uVar26 & (uint)DAT_00fa86f4 | (uint)DAT_00fa4810 & uVar26)
                                + local_110 * 0.0) + local_10c) * DAT_00fa4830 + fVar29;
        } while( true );
      }
      cVar8 = CBaseUnit::ISA((CBaseUnit *)pCVar24,0x36);
      if (cVar8 == '\0') {
        cVar8 = (**(code **)(*(long *)pCVar24 + 0x2b0))(pCVar24);
        if (cVar8 == '\0') {
          pSVar23 = (String *)&local_11e8;
          local_11e0 = 0x20;
          local_11d8 = 0;
          local_11c8 = 0;
          local_11d0 = 0;
          local_1140 = (undefined4 *)0x0;
          local_11e8 = 0;
          local_11c0[0] = 0;
          CEGUI::String::grow((ulong)pSVar23);
          local_11e8 = 0;
          puVar15 = local_11c0;
          if (0x20 < local_11e0) {
            puVar15 = local_1140;
          }
          *puVar15 = 0;
          local_1130 = 0x20;
          local_1128 = 0;
          local_1118 = 0;
          local_1120 = 0;
          local_1090 = (uint *)0x0;
          local_1138 = 0;
          local_1110[0] = 0;
                    /* try { // try from 00ba4299 to 00ba429d has its CatchHandler @ 00ba4d86 */
          CEGUI::String::grow((ulong)&local_1138);
          puVar16 = local_1110;
          if (0x20 < local_1130) {
            puVar16 = local_1090;
          }
          pbVar11 = (byte *)0xfd0c0d;
          do {
            bVar4 = *pbVar11;
            pbVar11 = pbVar11 + 1;
            *puVar16 = (uint)bVar4;
            puVar16 = puVar16 + 1;
          } while (pbVar11 != (byte *)0xfd0c12);
          local_1138 = 5;
          puVar16 = local_10fc;
          if (0x20 < local_1130) {
            puVar16 = local_1090 + 5;
          }
          *puVar16 = 0;
                    /* try { // try from 00ba430f to 00ba4313 has its CatchHandler @ 00ba4d32 */
          CEGUI::PropertySet::setProperty(*(String **)(pCVar22 + 0x1898),(String *)&local_1138);
                    /* try { // try from 00ba4317 to 00ba431b has its CatchHandler @ 00ba4d86 */
          CEGUI::String::~String((String *)&local_1138);
        }
        else {
          cVar8 = CBaseUnit::ISA((CBaseUnit *)pCVar24,0x37);
          if (cVar8 == '\0') {
            pSVar23 = (String *)&local_f28;
            local_f20 = 0x20;
            local_f18 = 0;
            local_f08 = 0;
            local_f10 = 0;
            local_e80 = (uint *)0x0;
            local_f28 = 0;
            local_f00[0] = 0;
            CEGUI::String::grow((ulong)pSVar23);
            puVar16 = local_f00;
            if (0x20 < local_f20) {
              puVar16 = local_e80;
            }
            pcVar12 = "greenslotglow";
            do {
              bVar4 = *pcVar12;
              pcVar12 = pcVar12 + 1;
              *puVar16 = (uint)bVar4;
              puVar16 = puVar16 + 1;
            } while ((byte *)pcVar12 != (byte *)0xfe60c2);
            local_f28 = 0xd;
            puVar16 = local_ecc;
            if (0x20 < local_f20) {
              puVar16 = local_e80 + 0xd;
            }
            *puVar16 = 0;
                    /* try { // try from 00ba463d to 00ba4654 has its CatchHandler @ 00ba4f32 */
            CEGUI::Imageset::getImage(*(String **)(this + 0x9108));
            CEGUI::PropertyHelper::imageToString(local_fd8);
            local_1080 = 0x20;
            local_1078 = 0;
            local_1068 = 0;
            local_1070 = 0;
            local_fe0 = (uint *)0x0;
            local_1088 = 0;
            local_1060[0] = 0;
                    /* try { // try from 00ba46b8 to 00ba46bc has its CatchHandler @ 00ba4f37 */
            CEGUI::String::grow((ulong)&local_1088);
            puVar16 = local_1060;
            if (0x20 < local_1080) {
              puVar16 = local_fe0;
            }
            pbVar11 = (byte *)0xfd0c0d;
            do {
              bVar4 = *pbVar11;
              pbVar11 = pbVar11 + 1;
              *puVar16 = (uint)bVar4;
              puVar16 = puVar16 + 1;
            } while (pbVar11 != (byte *)0xfd0c12);
            local_1088 = 5;
            puVar16 = local_104c;
            if (0x20 < local_1080) {
              puVar16 = local_fe0 + 5;
            }
            *puVar16 = 0;
                    /* try { // try from 00ba472f to 00ba4733 has its CatchHandler @ 00ba4f45 */
            CEGUI::PropertySet::setProperty(*(String **)(pCVar22 + 0x1898),(String *)&local_1088);
                    /* try { // try from 00ba4737 to 00ba473b has its CatchHandler @ 00ba4f37 */
            CEGUI::String::~String((String *)&local_1088);
                    /* try { // try from 00ba473f to 00ba4743 has its CatchHandler @ 00ba4f32 */
            CEGUI::String::~String((String *)local_fd8);
          }
          else {
            pSVar23 = (String *)&local_d18;
            local_d10 = 0x20;
            local_d08 = 0;
            local_cf8 = 0;
            local_d00 = 0;
            local_c70 = (uint *)0x0;
            local_d18 = 0;
            local_cf0[0] = 0;
            CEGUI::String::grow((ulong)pSVar23);
            puVar16 = local_cf0;
            if (0x20 < local_d10) {
              puVar16 = local_c70;
            }
            pcVar12 = "blueslotglow";
            do {
              bVar4 = *pcVar12;
              pcVar12 = pcVar12 + 1;
              *puVar16 = (uint)bVar4;
              puVar16 = puVar16 + 1;
            } while ((byte *)pcVar12 != (byte *)0xfe60b4);
            local_d18 = 0xc;
            puVar16 = local_cc0;
            if (0x20 < local_d10) {
              puVar16 = local_c70 + 0xc;
            }
            *puVar16 = 0;
                    /* try { // try from 00ba3f0d to 00ba3f24 has its CatchHandler @ 00ba4f55 */
            CEGUI::Imageset::getImage(*(String **)(this + 0x9108));
            CEGUI::PropertyHelper::imageToString(local_dc8);
            local_e70 = 0x20;
            local_e68 = 0;
            local_e58 = 0;
            local_e60 = 0;
            local_dd0 = (uint *)0x0;
            local_e78 = 0;
            local_e50[0] = 0;
                    /* try { // try from 00ba3f88 to 00ba3f8c has its CatchHandler @ 00ba4f65 */
            CEGUI::String::grow((ulong)&local_e78);
            puVar16 = local_e50;
            if (0x20 < local_e70) {
              puVar16 = local_dd0;
            }
            pbVar11 = (byte *)0xfd0c0d;
            do {
              bVar4 = *pbVar11;
              pbVar11 = pbVar11 + 1;
              *puVar16 = (uint)bVar4;
              puVar16 = puVar16 + 1;
            } while (pbVar11 != (byte *)0xfd0c12);
            local_e78 = 5;
            puVar16 = local_e3c;
            if (0x20 < local_e70) {
              puVar16 = local_dd0 + 5;
            }
            *puVar16 = 0;
                    /* try { // try from 00ba3fff to 00ba4003 has its CatchHandler @ 00ba4f75 */
            CEGUI::PropertySet::setProperty(*(String **)(pCVar22 + 0x1898),(String *)&local_e78);
                    /* try { // try from 00ba4007 to 00ba400b has its CatchHandler @ 00ba4f65 */
            CEGUI::String::~String((String *)&local_e78);
                    /* try { // try from 00ba400f to 00ba4013 has its CatchHandler @ 00ba4f55 */
            CEGUI::String::~String((String *)local_dc8);
          }
        }
      }
      else {
        pSVar23 = (String *)&local_b08;
        local_b00 = 0x20;
        local_af8 = 0;
        local_ae8 = 0;
        local_af0 = 0;
        local_a60 = (uint *)0x0;
        local_b08 = 0;
        local_ae0[0] = 0;
        CEGUI::String::grow((ulong)pSVar23);
        puVar16 = local_ae0;
        if (0x20 < local_b00) {
          puVar16 = local_a60;
        }
        pcVar12 = "goldslotglow";
        do {
          bVar4 = *pcVar12;
          pcVar12 = pcVar12 + 1;
          *puVar16 = (uint)bVar4;
          puVar16 = puVar16 + 1;
        } while ((byte *)pcVar12 != (byte *)0xfe60a7);
        local_b08 = 0xc;
        puVar16 = local_ab0;
        if (0x20 < local_b00) {
          puVar16 = local_a60 + 0xc;
        }
        *puVar16 = 0;
                    /* try { // try from 00ba39ed to 00ba3a04 has its CatchHandler @ 00ba4d8b */
        CEGUI::Imageset::getImage(*(String **)(this + 0x9108));
        CEGUI::PropertyHelper::imageToString(local_bb8);
        local_c60 = 0x20;
        local_c58 = 0;
        local_c48 = 0;
        local_c50 = 0;
        local_bc0 = (uint *)0x0;
        local_c68 = 0;
        local_c40[0] = 0;
                    /* try { // try from 00ba3a68 to 00ba3a6c has its CatchHandler @ 00ba4e0f */
        CEGUI::String::grow((ulong)&local_c68);
        puVar16 = local_c40;
        if (0x20 < local_c60) {
          puVar16 = local_bc0;
        }
        pbVar11 = (byte *)0xfd0c0d;
        do {
          bVar4 = *pbVar11;
          pbVar11 = pbVar11 + 1;
          *puVar16 = (uint)bVar4;
          puVar16 = puVar16 + 1;
        } while (pbVar11 != (byte *)0xfd0c12);
        local_c68 = 5;
        puVar16 = local_c2c;
        if (0x20 < local_c60) {
          puVar16 = local_bc0 + 5;
        }
        *puVar16 = 0;
                    /* try { // try from 00ba3adf to 00ba3ae3 has its CatchHandler @ 00ba4df7 */
        CEGUI::PropertySet::setProperty(*(String **)(pCVar22 + 0x1898),(String *)&local_c68);
                    /* try { // try from 00ba3ae7 to 00ba3aeb has its CatchHandler @ 00ba4e0f */
        CEGUI::String::~String((String *)&local_c68);
                    /* try { // try from 00ba3aef to 00ba3af3 has its CatchHandler @ 00ba4d8b */
        CEGUI::String::~String((String *)local_bb8);
      }
      CEGUI::String::~String(pSVar23);
      local_1340 = 0x20;
      local_1338 = 0;
      local_1328 = 0;
      local_1330 = 0;
      local_12a0 = (undefined4 *)0x0;
      local_1348 = 0;
      local_1320[0] = 0;
      CEGUI::String::grow((ulong)&local_1348);
      puVar15 = local_1320;
      if (0x20 < local_1340) {
        puVar15 = local_12a0;
      }
      local_1348 = 0;
      *puVar15 = 0;
      local_1290 = 0x20;
      local_1288 = 0;
      local_1278 = 0;
      local_1280 = 0;
      local_11f0 = (uint *)0x0;
      local_1298 = 0;
      local_1270[0] = 0;
                    /* try { // try from 00ba3be7 to 00ba3beb has its CatchHandler @ 00ba4df2 */
      CEGUI::String::grow((ulong)&local_1298);
      puVar16 = local_11f0;
      if (local_1290 < 0x21) {
        puVar16 = local_1270;
      }
      pbVar11 = (byte *)0xfd0c0d;
      do {
        bVar4 = *pbVar11;
        pbVar11 = pbVar11 + 1;
        *puVar16 = (uint)bVar4;
        puVar16 = puVar16 + 1;
      } while (pbVar11 != (byte *)0xfd0c12);
      local_1298 = 5;
      puVar16 = local_125c;
      if (0x20 < local_1290) {
        puVar16 = local_11f0 + 5;
      }
      *puVar16 = 0;
                    /* try { // try from 00ba3c6a to 00ba3c6e has its CatchHandler @ 00ba4dcd */
      CEGUI::PropertySet::setProperty(*(String **)(pCVar22 + 0x1378),(String *)&local_1298);
                    /* try { // try from 00ba3c77 to 00ba3c7b has its CatchHandler @ 00ba4df2 */
      CEGUI::String::~String((String *)&local_1298);
      CEGUI::String::~String((String *)&local_1348);
      if (local_22b8 != (UVector2 *)0x0) {
        local_124 = 0;
        local_128 = 0;
        local_11c = 0x3f800000;
        local_120 = 0;
                    /* try { // try from 00ba3cce to 00ba3cd2 has its CatchHandler @ 00ba4d28 */
        CEGUI::Window::setPosition(local_22b8);
        local_134 = 0;
        local_138 = 0;
        local_12c = 0;
        local_130 = 0;
                    /* try { // try from 00ba3d0c to 00ba3d10 has its CatchHandler @ 00ba4d26 */
        CEGUI::Window::setPosition(local_22b8);
        CEGUI::Window::getSize();
        fVar28 = local_148 * 0.0;
        fVar30 = DAT_00fa4810;
        if (fVar28 <= 0.0) {
          fVar30 = DAT_00fa86f4;
        }
        local_140 = 0;
        local_148 = 0.0;
        local_144 = (float)(int)(fVar28 + fVar30) + local_144;
        local_13c = DAT_00fce498 * local_144;
                    /* try { // try from 00ba3d9d to 00ba3dbd has its CatchHandler @ 00ba4d1e */
        CEGUI::Window::setSize(local_22b8);
        CEGUI::Window::moveToFront();
        CEGUI::Window::update(DAT_00fa4828);
      }
      CEGUI::String::String(local_13f8,"");
                    /* try { // try from 00ba3ddd to 00ba3de1 has its CatchHandler @ 00ba4d0b */
      CEGUI::Window::setTooltipText(*(String **)(pCVar22 + 0x1378));
      pCVar22 = pCVar22 + 8;
      CEGUI::String::~String(local_13f8);
      uVar21 = uVar21 + 1;
    } while (uVar21 != 0xc);
LAB_00ba3150:
    uVar21 = 0;
    pCVar22 = this;
    do {
      if (*(long *)(pCVar22 + 0x1040) != 0) {
        if ((updateLayout()::g_RemoveASpell == '\0') &&
           (iVar9 = __cxa_guard_acquire(&updateLayout()::g_RemoveASpell), iVar9 != 0)) {
          updateLayout()::g_RemoveASpell = &DAT_01423a38;
          __cxa_guard_release(&updateLayout()::g_RemoveASpell);
          __cxa_atexit(std::string::~string,&updateLayout()::g_RemoveASpell,&__dso_handle);
        }
        if (*(long *)(updateLayout()::g_RemoveASpell + -0x18) == 0) {
          CStringTranslate::getSinglton();
          CStringTranslate::getTranslateString((wchar_t *)local_58);
                    /* try { // try from 00ba4a6f to 00ba4a73 has its CatchHandler @ 00ba514a */
          STRINGS::StringConvertToNarrow((STRINGS *)local_68,local_58[0]);
                    /* try { // try from 00ba4a7c to 00ba4a80 has its CatchHandler @ 00ba5162 */
          std::string::assign((string *)&updateLayout()::g_RemoveASpell);
          if ((allocator *)(local_68[0] + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_68[0] + -8);
            iVar9 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar9 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
            }
          }
          if ((allocator *)(local_58[0] + -6) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            pwVar1 = local_58[0] + -2;
            wVar3 = *pwVar1;
            *pwVar1 = *pwVar1 + L'\xffffffff';
            UNLOCK();
            if (wVar3 < L'\x01') {
              std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -6));
            }
          }
        }
        if ((updateLayout()::g_RemoveASpell2 == '\0') &&
           (iVar9 = __cxa_guard_acquire(&updateLayout()::g_RemoveASpell2), iVar9 != 0)) {
          updateLayout()::g_RemoveASpell2 = &DAT_01423a38;
          __cxa_guard_release(&updateLayout()::g_RemoveASpell2);
          __cxa_atexit(std::string::~string,&updateLayout()::g_RemoveASpell2,&__dso_handle);
        }
        if (*(long *)(updateLayout()::g_RemoveASpell2 + -0x18) == 0) {
          CStringTranslate::getSinglton();
          CStringTranslate::getTranslateString((wchar_t *)local_78);
                    /* try { // try from 00ba4bd6 to 00ba4bda has its CatchHandler @ 00ba4c76 */
          STRINGS::StringConvertToNarrow((STRINGS *)local_88,local_78[0]);
                    /* try { // try from 00ba4be3 to 00ba4be7 has its CatchHandler @ 00ba4c99 */
          std::string::assign((string *)&updateLayout()::g_RemoveASpell2);
          if ((allocator *)(local_88[0] + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_88[0] + -8);
            iVar9 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar9 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
            }
          }
          if ((allocator *)(local_78[0] + -6) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            pwVar1 = local_78[0] + -2;
            wVar3 = *pwVar1;
            *pwVar1 = *pwVar1 + L'\xffffffff';
            UNLOCK();
            if (wVar3 < L'\x01') {
              std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -6));
            }
          }
        }
        if ((updateLayout()::g_DragASpell == '\0') &&
           (iVar9 = __cxa_guard_acquire(&updateLayout()::g_DragASpell), iVar9 != 0)) {
          updateLayout()::g_DragASpell = &DAT_01423a38;
          __cxa_guard_release(&updateLayout()::g_DragASpell);
          __cxa_atexit(std::string::~string,&updateLayout()::g_DragASpell,&__dso_handle);
        }
        if (*(long *)(updateLayout()::g_DragASpell + -0x18) == 0) {
          CStringTranslate::getSinglton();
          CStringTranslate::getTranslateString((wchar_t *)local_98);
                    /* try { // try from 00ba3201 to 00ba3205 has its CatchHandler @ 00ba4f85 */
          STRINGS::StringConvertToNarrow((STRINGS *)local_a8,local_98[0]);
                    /* try { // try from 00ba320e to 00ba3212 has its CatchHandler @ 00ba4f9d */
          std::string::assign((string *)&updateLayout()::g_DragASpell);
          if ((allocator *)(local_a8[0] + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_a8[0] + -8);
            iVar9 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar9 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
            }
          }
          if ((allocator *)(local_98[0] + -6) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            pwVar1 = local_98[0] + -2;
            wVar3 = *pwVar1;
            *pwVar1 = *pwVar1 + L'\xffffffff';
            UNLOCK();
            if (wVar3 < L'\x01') {
              std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -6));
            }
          }
        }
        this_02 = (CSkill *)CCharacter::getKnownSpell(*(CCharacter **)(this + 0x58),uVar21);
        if ((this_02 == (CSkill *)0x0) ||
           (plVar14 = (long *)CSkill::getSkillIcon(this_02), *(long *)(*plVar14 + -0x18) == 0)) {
          CEGUI::String::String(local_1ce8,"");
                    /* try { // try from 00ba32b0 to 00ba32b4 has its CatchHandler @ 00ba4ea0 */
          CEGUI::String::String(local_1c38,"Image");
                    /* try { // try from 00ba32cc to 00ba32d0 has its CatchHandler @ 00ba4e7b */
          CEGUI::PropertySet::setProperty(*(String **)(pCVar22 + 0x1040),local_1c38);
                    /* try { // try from 00ba32d9 to 00ba32dd has its CatchHandler @ 00ba4ea0 */
          CEGUI::String::~String(local_1c38);
          CEGUI::String::~String(local_1ce8);
          *(CPetMenu **)(*(long *)(pCVar22 + 0x1040) + 0x1d8) = this + 0x1368;
          CEGUI::String::String(local_1d98,updateLayout()::g_DragASpell);
                    /* try { // try from 00ba3321 to 00ba3325 has its CatchHandler @ 00ba4e63 */
          CEGUI::Window::setTooltipText(*(String **)(pCVar22 + 0x1040));
          CEGUI::String::~String(local_1d98);
        }
        else {
          puVar17 = (undefined8 *)CSkill::getSkillIcon(this_02);
          STRINGS::StringConvertToNarrow((STRINGS *)local_b8,(wchar_t *)*puVar17);
                    /* try { // try from 00ba47d1 to 00ba47e5 has its CatchHandler @ 00ba4ffb */
          CGameUI::getImageFromImageSet(*(CGameUI **)(this + 0x90),local_b8[0]);
          CEGUI::PropertyHelper::imageToString(local_1a28);
                    /* try { // try from 00ba47f3 to 00ba47f7 has its CatchHandler @ 00ba4fd6 */
          CEGUI::String::String(local_1ad8,"Image");
                    /* try { // try from 00ba480f to 00ba4813 has its CatchHandler @ 00ba500b */
          CEGUI::PropertySet::setProperty(*(String **)(pCVar22 + 0x1040),local_1ad8);
                    /* try { // try from 00ba481c to 00ba4820 has its CatchHandler @ 00ba4fd6 */
          CEGUI::String::~String(local_1ad8);
                    /* try { // try from 00ba4829 to 00ba482d has its CatchHandler @ 00ba4ffb */
          CEGUI::String::~String((String *)local_1a28);
          if ((allocator *)(local_b8[0] + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_b8[0] + -8);
            iVar9 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar9 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
            }
          }
          *(undefined8 *)(pCVar22 + 0x1050) = *(undefined8 *)(this_02 + 0x150);
          *(CPetMenu **)(*(long *)(pCVar22 + 0x1040) + 0x1d8) = this + (ulong)uVar21 * 8 + 0x1050;
          std::string::string((string *)local_c8,(string *)&updateLayout()::g_RemoveASpell);
                    /* try { // try from 00ba4888 to 00ba488c has its CatchHandler @ 00ba5057 */
          std::string::append((char *)local_c8,0xfa04e8);
                    /* try { // try from 00ba489d to 00ba48a1 has its CatchHandler @ 00ba5075 */
          std::operator+((string *)local_d8,(string *)local_c8);
                    /* try { // try from 00ba48b2 to 00ba48b6 has its CatchHandler @ 00ba5088 */
          CEGUI::String::String(local_1b88,local_d8[0]);
                    /* try { // try from 00ba48c6 to 00ba48ca has its CatchHandler @ 00ba509a */
          CEGUI::Window::setTooltipText(*(String **)(pCVar22 + 0x1040));
                    /* try { // try from 00ba48d3 to 00ba48d7 has its CatchHandler @ 00ba5088 */
          CEGUI::String::~String(local_1b88);
          if ((allocator *)(local_d8[0] + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_d8[0] + -8);
            iVar9 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar9 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
            }
          }
          if ((allocator *)(local_c8[0] + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_c8[0] + -8);
            iVar9 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar9 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
            }
          }
        }
      }
      uVar21 = uVar21 + 1;
      pCVar22 = pCVar22 + 8;
    } while (uVar21 != 2);
    local_22c8 = 0x13;
    pCVar22 = this;
    do {
      local_1ef0 = 0x20;
      local_1ee8 = 0;
      local_1ed8 = 0;
      local_1ee0 = 0;
      local_1e50 = (undefined4 *)0x0;
      local_1ef8 = 0;
      local_1ed0[0] = 0;
      CEGUI::String::grow((ulong)&local_1ef8);
      puVar15 = local_1ed0;
      if (0x20 < local_1ef0) {
        puVar15 = local_1e50;
      }
      local_1ef8 = 0;
      *puVar15 = 0;
      local_1e40 = 0x20;
      local_1e38 = 0;
      local_1e28 = 0;
      local_1e30 = 0;
      local_1da0 = (uint *)0x0;
      local_1e48 = 0;
      local_1e20[0] = 0;
                    /* try { // try from 00ba3496 to 00ba349a has its CatchHandler @ 00ba4e5e */
      CEGUI::String::grow((ulong)&local_1e48);
      puVar16 = local_1e20;
      if (0x20 < local_1e40) {
        puVar16 = local_1da0;
      }
      pbVar11 = (byte *)0xfd0c0d;
      do {
        bVar4 = *pbVar11;
        pbVar11 = pbVar11 + 1;
        *puVar16 = (uint)bVar4;
        puVar16 = puVar16 + 1;
      } while (pbVar11 != (byte *)0xfd0c12);
      local_1e48 = 5;
      puVar16 = local_1e0c;
      if (0x20 < local_1e40) {
        puVar16 = local_1da0 + 5;
      }
      *puVar16 = 0;
                    /* try { // try from 00ba3514 to 00ba3518 has its CatchHandler @ 00ba4e3e */
      CEGUI::PropertySet::setProperty(*(String **)(pCVar22 + 0x1930),(String *)&local_1e48);
                    /* try { // try from 00ba351c to 00ba3520 has its CatchHandler @ 00ba4e5e */
      CEGUI::String::~String((String *)&local_1e48);
      CEGUI::String::~String((String *)&local_1ef8);
      local_2050 = 0x20;
      local_2048 = 0;
      local_2038 = 0;
      local_2040 = 0;
      local_1fb0 = (undefined4 *)0x0;
      local_2058 = 0;
      local_2030[0] = 0;
      CEGUI::String::grow((ulong)&local_2058);
      puVar15 = local_2030;
      if (0x20 < local_2050) {
        puVar15 = local_1fb0;
      }
      local_2058 = 0;
      *puVar15 = 0;
      local_1fa0 = 0x20;
      local_1f98 = 0;
      local_1f88 = 0;
      local_1f90 = 0;
      local_1f00 = (uint *)0x0;
      local_1fa8 = 0;
      local_1f80[0] = 0;
                    /* try { // try from 00ba3614 to 00ba3618 has its CatchHandler @ 00ba4e39 */
      CEGUI::String::grow((ulong)&local_1fa8);
      pbVar11 = (byte *)0xfd0c0d;
      puVar16 = local_1f80;
      if (0x20 < local_1fa0) {
        puVar16 = local_1f00;
      }
      do {
        bVar4 = *pbVar11;
        pbVar11 = pbVar11 + 1;
        *puVar16 = (uint)bVar4;
        puVar16 = puVar16 + 1;
      } while (pbVar11 != (byte *)0xfd0c12);
      local_1fa8 = 5;
      puVar16 = local_1f6c;
      if (0x20 < local_1fa0) {
        puVar16 = local_1f00 + 5;
      }
      *puVar16 = 0;
                    /* try { // try from 00ba3689 to 00ba368d has its CatchHandler @ 00ba4e19 */
      CEGUI::PropertySet::setProperty(*(String **)(pCVar22 + 0x1bc0),(String *)&local_1fa8);
                    /* try { // try from 00ba3691 to 00ba3695 has its CatchHandler @ 00ba4e39 */
      CEGUI::String::~String((String *)&local_1fa8);
      CEGUI::String::~String((String *)&local_2058);
      local_21b0 = 0x20;
      local_21a8 = 0;
      local_2198 = 0;
      local_21a0 = 0;
      local_2110 = (undefined4 *)0x0;
      local_21b8 = 0;
      local_2190[0] = 0;
      CEGUI::String::grow((ulong)&local_21b8);
      puVar15 = local_2190;
      if (0x20 < local_21b0) {
        puVar15 = local_2110;
      }
      local_21b8 = 0;
      *puVar15 = 0;
      local_2100 = 0x20;
      local_20f8 = 0;
      local_20e8 = 0;
      local_20f0 = 0;
      local_2060 = (uint *)0x0;
      local_2108 = 0;
      local_20e0[0] = 0;
                    /* try { // try from 00ba3789 to 00ba378d has its CatchHandler @ 00ba4e14 */
      CEGUI::String::grow((ulong)&local_2108);
      pbVar11 = (byte *)0xfd0c0d;
      puVar16 = local_20e0;
      if (0x20 < local_2100) {
        puVar16 = local_2060;
      }
      do {
        bVar4 = *pbVar11;
        pbVar11 = pbVar11 + 1;
        *puVar16 = (uint)bVar4;
        puVar16 = puVar16 + 1;
      } while (pbVar11 != (byte *)0xfd0c12);
      local_2108 = 5;
      puVar16 = local_20cc;
      if (0x20 < local_2100) {
        puVar16 = local_2060 + 5;
      }
      *puVar16 = 0;
                    /* try { // try from 00ba3802 to 00ba3806 has its CatchHandler @ 00ba4dad */
      CEGUI::PropertySet::setProperty(*(String **)(pCVar22 + 0x16a0),(String *)&local_2108);
                    /* try { // try from 00ba380a to 00ba380e has its CatchHandler @ 00ba4e14 */
      CEGUI::String::~String((String *)&local_2108);
      CEGUI::String::~String((String *)&local_21b8);
      if (*(long *)(pCVar22 + 0x1e50) != 0) {
        CEGUI::String::String(local_2268,"");
                    /* try { // try from 00ba3847 to 00ba384b has its CatchHandler @ 00ba4d95 */
        CEGUI::Window::setText(*(String **)(pCVar22 + 0x1e50));
        CEGUI::String::~String(local_2268);
      }
      pWVar5 = *(Window **)(pCVar22 + 0x1410);
      if (*(long *)(pWVar5 + 0x80) - *(long *)(pWVar5 + 0x78) >> 3 != 0) {
        CEGUI::Window::removeChildWindow(pWVar5);
      }
      local_22c8 = local_22c8 + 1;
      pCVar22 = pCVar22 + 8;
    } while (local_22c8 != 0x52);
    if (*(int *)(this_00 + 0x38) != 0) {
      uVar20 = 0;
      do {
        uVar21 = (uint)uVar20;
        if (uVar21 < *(uint *)(this_00 + 0x3c)) {
          plVar14 = *(long **)(this_00 + 0x30);
          lVar18 = plVar14[uVar20];
          pCVar24 = *(CEquipment **)(lVar18 + 0x10);
        }
        else {
          plVar14 = *(long **)(this_00 + 0x30);
          lVar18 = *plVar14;
          pCVar24 = *(CEquipment **)(lVar18 + 0x10);
        }
        if (0x12 < *(int *)(lVar18 + 0x18)) {
          if (uVar21 < *(uint *)(this_00 + 0x3c)) {
            plVar14 = (long *)(uVar20 * 8 + *(long *)(this_00 + 0x30));
          }
          iVar9 = CInventory::getItemPane(this_00,*(uint *)(*plVar14 + 0x18));
          if (iVar9 == *(int *)(this + 0x6c)) {
            if (uVar21 < *(uint *)(this_00 + 0x3c)) {
              plVar14 = (long *)(uVar20 * 8 + *(long *)(this_00 + 0x30));
            }
            else {
              plVar14 = *(long **)(this_00 + 0x30);
            }
            setSlotIcon(this,pCVar24,*(int *)(*plVar14 + 0x18),*(int *)(*plVar14 + 0x18));
          }
        }
        uVar20 = (ulong)(uVar21 + 1);
      } while (uVar21 + 1 < *(uint *)(this_00 + 0x38));
    }
    CEGUI::Window::moveToBack();
    CEGUI::Window::moveToFront();
    CEGUI::Window::moveToFront();
    CEGUI::Window::moveToFront();
    CEGUI::Window::moveToFront();
  }
  return;
}

/* address=00ba5180
   symbol=CPetMenu::isRight */

/* CPetMenu::isRight() */

undefined8 CPetMenu::isRight(void)

{
  return 0;
}

/* address=00ba5190
   symbol=CPetMenu::open */

/* CPetMenu::open() */

byte __thiscall CPetMenu::open(CPetMenu *this)

{
  byte bVar1;

  bVar1 = 1;
  if (this[0x68] == (CPetMenu)0x0) {
    bVar1 = (byte)this[0x69] ^ 1;
  }
  return bVar1;
}

/* address=00ba51b0
   symbol=CPetMenu::openPartial */

/* CPetMenu::openPartial() */

CPetMenu __thiscall CPetMenu::openPartial(CPetMenu *this)

{
  return this[0x68];
}

/* address=00ba51c0
   symbol=CPetMenu::screenEdge */

/* CPetMenu::screenEdge() */

undefined4 __thiscall CPetMenu::screenEdge(CPetMenu *this)

{
  return *(undefined4 *)(this + 0x91b0);
}

/* address=00ba51d0
   symbol=CPetMenu::getOwner */

/* CPetMenu::getOwner() */

undefined8 __thiscall CPetMenu::getOwner(CPetMenu *this)

{
  return *(undefined8 *)(this + 0x58);
}

/* export-summary functions=47 failures=0 */
