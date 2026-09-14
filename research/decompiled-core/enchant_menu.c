/* Targeted Ghidra class export.
   namespace=CEnchantMenu
   Treat pseudocode as navigation evidence. */


/* address=00b1ba30
   symbol=CEnchantMenu::setOwner */

/* CEnchantMenu::setOwner(CCharacter*) */

void __thiscall CEnchantMenu::setOwner(CEnchantMenu *this,CCharacter *param_1)

{
  *(CCharacter **)(this + 0x58) = param_1;
  *(undefined8 *)(this + 0x68) = 0;
  return;
}

/* address=00b1ba40
   symbol=CEnchantMenu::setOwnerItem */

/* CEnchantMenu::setOwnerItem(CItem*) */

void __thiscall CEnchantMenu::setOwnerItem(CEnchantMenu *this,CItem *param_1)

{
  *(undefined8 *)(this + 0x58) = 0;
  *(CItem **)(this + 0x68) = param_1;
  return;
}

/* address=00b1ba50
   symbol=CEnchantMenu::equipmentPickedUp */

/* non-virtual thunk to CEnchantMenu::equipmentPickedUp(CEquipment*) */

void __thiscall CEnchantMenu::equipmentPickedUp(CEnchantMenu *this,CEquipment *param_1)

{
  equipmentPickedUp((CEquipment *)(this + -0x10));
  return;
}

/* address=00b1ba60
   symbol=CEnchantMenu::equipmentPickedUp */

/* CEnchantMenu::equipmentPickedUp(CEquipment*) */

void CEnchantMenu::equipmentPickedUp(CEquipment *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x00b1ba67. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)param_1 + 0x48))();
  return;
}

/* address=00b1ba70
   symbol=CEnchantMenu::equipmentDropped */

/* non-virtual thunk to CEnchantMenu::equipmentDropped(CEquipment*) */

void __thiscall CEnchantMenu::equipmentDropped(CEnchantMenu *this,CEquipment *param_1)

{
  equipmentDropped((CEquipment *)(this + -0x10));
  return;
}

/* address=00b1ba80
   symbol=CEnchantMenu::equipmentDropped */

/* CEnchantMenu::equipmentDropped(CEquipment*) */

void CEnchantMenu::equipmentDropped(CEquipment *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x00b1ba87. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)param_1 + 0x48))();
  return;
}

/* address=00b1ba90
   symbol=CEnchantMenu::equipmentEquipped */

/* non-virtual thunk to CEnchantMenu::equipmentEquipped(CEquipment*) */

void __thiscall CEnchantMenu::equipmentEquipped(CEnchantMenu *this,CEquipment *param_1)

{
  equipmentEquipped((CEquipment *)(this + -0x10));
  return;
}

/* address=00b1baa0
   symbol=CEnchantMenu::equipmentEquipped */

/* CEnchantMenu::equipmentEquipped(CEquipment*) */

void CEnchantMenu::equipmentEquipped(CEquipment *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x00b1baa7. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)param_1 + 0x48))();
  return;
}

/* address=00b1bab0
   symbol=CEnchantMenu::equipmentUnequipped */

/* non-virtual thunk to CEnchantMenu::equipmentUnequipped(CEquipment*) */

void __thiscall CEnchantMenu::equipmentUnequipped(CEnchantMenu *this,CEquipment *param_1)

{
  equipmentUnequipped((CEquipment *)(this + -0x10));
  return;
}

/* address=00b1bac0
   symbol=CEnchantMenu::equipmentUnequipped */

/* CEnchantMenu::equipmentUnequipped(CEquipment*) */

void CEnchantMenu::equipmentUnequipped(CEquipment *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x00b1bac7. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)param_1 + 0x48))();
  return;
}

/* address=00b1bad0
   symbol=CEnchantMenu::equipmentUsed */

/* non-virtual thunk to CEnchantMenu::equipmentUsed(CEquipment*) */

void __thiscall CEnchantMenu::equipmentUsed(CEnchantMenu *this,CEquipment *param_1)

{
  equipmentUsed((CEquipment *)(this + -0x10));
  return;
}

/* address=00b1bae0
   symbol=CEnchantMenu::equipmentUsed */

/* CEnchantMenu::equipmentUsed(CEquipment*) */

void CEnchantMenu::equipmentUsed(CEquipment *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x00b1bae7. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)param_1 + 0x48))();
  return;
}

/* address=00b1baf0
   symbol=CEnchantMenu::inventoryDestroyed */

/* non-virtual thunk to CEnchantMenu::inventoryDestroyed() */

void __thiscall CEnchantMenu::inventoryDestroyed(CEnchantMenu *this)

{
  inventoryDestroyed();
  return;
}

/* address=00b1bb00
   symbol=CEnchantMenu::inventoryDestroyed */

/* CEnchantMenu::inventoryDestroyed() */

void CEnchantMenu::inventoryDestroyed(void)

{
  return;
}

/* address=00b1bb10
   symbol=CEnchantMenu::handle_ItemClick */

/* CEnchantMenu::handle_ItemClick(CEGUI::EventArgs const&) */

undefined8 __thiscall CEnchantMenu::handle_ItemClick(CEnchantMenu *this,EventArgs *param_1)

{
  int iVar1;

  if (*(long *)(param_1 + 0x10) != 0) {
    iVar1 = **(int **)(*(long *)(param_1 + 0x10) + 0x1d8);
    if (*(int *)(param_1 + 0x28) == 0) {
      *(undefined4 *)(this + 0xe8) = *(undefined4 *)(this + (long)iVar1 * 4 + 0xc0);
      return 1;
    }
    if (*(int *)(param_1 + 0x28) == 1) {
      *(undefined4 *)(this + 0xec) = *(undefined4 *)(this + (long)iVar1 * 4 + 0xc0);
      return 1;
    }
  }
  return 1;
}

/* address=00b1bb70
   symbol=CEnchantMenu::handle_MouseThrough */

/* CEnchantMenu::handle_MouseThrough(CEGUI::EventArgs const&) */

undefined8 CEnchantMenu::handle_MouseThrough(EventArgs *param_1)

{
  param_1[0x108] = (EventArgs)0x0;
  return 1;
}

/* address=00b1bb80
   symbol=CEnchantMenu::handle_onClick */

/* CEnchantMenu::handle_onClick(CEGUI::EventArgs const&) */

undefined8 __thiscall CEnchantMenu::handle_onClick(CEnchantMenu *this,EventArgs *param_1)

{
  undefined8 uVar1;

  if ((*(int *)(param_1 + 0x28) == 0) && (*(long *)(param_1 + 0x10) != 0)) {
                    /* WARNING: Could not recover jumptable at 0x00b1bba3. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(*(long *)this + 0x98))
                      (this,**(undefined4 **)(*(long *)(param_1 + 0x10) + 0x1d8));
    return uVar1;
  }
  return 1;
}

/* address=00b1bbb0
   symbol=CEnchantMenu::handle_MouseOut */

/* CEnchantMenu::handle_MouseOut(CEGUI::EventArgs const&) */

undefined8 __thiscall CEnchantMenu::handle_MouseOut(CEnchantMenu *this,EventArgs *param_1)

{
  char cVar1;
  long lVar2;

  if (((*(long *)(param_1 + 0x10) != 0) && (*(long *)(this + 0x60) != 0)) &&
     (lVar2 = CInventory::getEquipmentInSlot
                        (*(CInventory **)(*(long *)(this + 0x60) + 0x490),
                         *(uint *)(this + (long)**(int **)(*(long *)(param_1 + 0x10) + 0x1d8) * 4 +
                                          0xc0)), lVar2 == *(long *)(this + 0xf0))) {
    *(undefined8 *)(this + 0xf0) = 0;
    if ((*(CBaseUnit **)(*(long *)(this + 0x80) + 0xb8) != (CBaseUnit *)0x0) &&
       (cVar1 = CBaseUnit::ISA(*(CBaseUnit **)(*(long *)(this + 0x80) + 0xb8),0x78), cVar1 != '\0'))
    {
      return 1;
    }
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x30),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x38),0));
  }
  return 1;
}

/* address=00b1bc40
   symbol=CEnchantMenu::handle_MouseOver */

/* CEnchantMenu::handle_MouseOver(CEGUI::EventArgs const&) */

undefined8 __thiscall CEnchantMenu::handle_MouseOver(CEnchantMenu *this,EventArgs *param_1)

{
  char cVar1;
  CBaseUnit *pCVar2;
  long lVar3;

  if ((*(long *)(param_1 + 0x10) == 0) || (*(long *)(this + 0x60) == 0)) {
    return 1;
  }
  lVar3 = (long)**(int **)(*(long *)(param_1 + 0x10) + 0x1d8);
  pCVar2 = (CBaseUnit *)
           CInventory::getEquipmentInSlot
                     (*(CInventory **)(*(long *)(this + 0x60) + 0x490),
                      *(uint *)(this + lVar3 * 4 + 0xc0));
  if (pCVar2 != (CBaseUnit *)0x0) {
    *(CBaseUnit **)(this + 0xf0) = pCVar2;
    if ((pCVar2[0x348] == (CBaseUnit)0x0) || (*(int *)(pCVar2 + 0x3e0) == 0)) {
      cVar1 = CBaseUnit::ISA(pCVar2,0x78);
      if (cVar1 == '\0') {
        CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x30),0));
        CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x38),0));
        goto LAB_00b1bce7;
      }
    }
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x38),0));
    CEGUI::Window::moveToFront();
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x30),0));
    CEGUI::Window::moveToFront();
  }
LAB_00b1bce7:
  lVar3 = lVar3 + 0x1a;
  CEGUI::Window::getWidth();
  CEGUI::Window::getHeight();
  cVar1 = CEGUI::Window::isChild(*(Window **)(this + lVar3 * 8 + 8));
  if (cVar1 == '\0') {
    CEGUI::Window::addChildWindow(*(Window **)(this + lVar3 * 8 + 8));
  }
                    /* try { // try from 00b1bdf4 to 00b1bdf8 has its CatchHandler @ 00b1bece */
  CEGUI::Window::setPosition(*(UVector2 **)(this + 0x100));
                    /* try { // try from 00b1be55 to 00b1be59 has its CatchHandler @ 00b1bec6 */
  CEGUI::Window::setSize(*(UVector2 **)(this + 0x100));
  CEGUI::Window::moveToBack();
  this[0x108] = (CEnchantMenu)0x1;
  return 1;
}

/* address=00b1bee0
   symbol=CEnchantMenu::processInput */

/* CEnchantMenu::processInput(void*, float, bool) */

bool CEnchantMenu::processInput(void *param_1,float param_2,bool param_3)

{
  long lVar1;
  Window *pWVar2;
  char cVar3;
  char in_DL;
  bool bVar4;

  if (in_DL == '\0') {
    *(undefined8 *)((long)param_1 + 0xf0) = 0;
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)((long)param_1 + 0x30),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)((long)param_1 + 0x38),0));
    pWVar2 = *(Window **)(*(long *)((long)param_1 + 0x100) + 0xb0);
    if (pWVar2 != (Window *)0x0) {
      cVar3 = CEGUI::Window::isChild(pWVar2);
      if (cVar3 != '\0') {
        CEGUI::Window::removeChildWindow(*(Window **)(*(long *)((long)param_1 + 0x100) + 0xb0));
        return true;
      }
    }
    return true;
  }
  bVar4 = *(char *)((long)param_1 + 0x72) != '\0';
  if (bVar4) {
    param_2 = (float)(**(code **)(*(long *)param_1 + 0x40))(param_1,0);
    *(undefined1 *)((long)param_1 + 0x72) = 0;
  }
  if ((*(long *)((long)param_1 + 0x60) != 0) &&
     (lVar1 = *(long *)(*(long *)((long)param_1 + 0x80) + 0xb8), lVar1 != 0)) {
    cVar3 = CBaseUnit::ISA((CBaseUnit *)param_2,lVar1,0x78);
    if (cVar3 != '\0') {
      CEGUI::Window::setVisible(SUB81(*(undefined8 *)((long)param_1 + 0x38),0));
      CEGUI::Window::moveToFront();
      CEGUI::Window::setVisible(SUB81(*(undefined8 *)((long)param_1 + 0x30),0));
      CEGUI::Window::moveToFront();
      goto LAB_00b1bf62;
    }
  }
  if (*(long *)((long)param_1 + 0xf0) == 0) {
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)((long)param_1 + 0x30),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)((long)param_1 + 0x38),0));
  }
  else if (*(char *)(*(long *)((long)param_1 + 0xf0) + 0x198) != '\0') {
    *(undefined8 *)((long)param_1 + 0xf0) = 0;
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)((long)param_1 + 0x38),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)((long)param_1 + 0x30),0));
  }
LAB_00b1bf62:
  if (*(char *)((long)param_1 + 0x108) == '\0') {
    pWVar2 = *(Window **)(*(long *)((long)param_1 + 0x100) + 0xb0);
    if (pWVar2 != (Window *)0x0) {
      cVar3 = CEGUI::Window::isChild(pWVar2);
      if (cVar3 != '\0') {
        CEGUI::Window::removeChildWindow(*(Window **)(*(long *)((long)param_1 + 0x100) + 0xb0));
      }
    }
    *(undefined8 *)((long)param_1 + 0xf0) = 0;
  }
  *(undefined4 *)((long)param_1 + 0xe8) = 0xffffffff;
  *(undefined4 *)((long)param_1 + 0xec) = 0xffffffff;
  return !bVar4;
}

/* address=00b1c0c0
   symbol=CEnchantMenu::setPlayer */

/* CEnchantMenu::setPlayer(CCharacter*) */

void __thiscall CEnchantMenu::setPlayer(CEnchantMenu *this,CCharacter *param_1)

{
  CCharacter *pCVar1;

  pCVar1 = param_1;
  if (*(CCharacter **)(this + 0x60) != param_1) {
    (**(code **)(*(long *)this + 0x90))();
    pCVar1 = *(CCharacter **)(this + 0x60);
  }
  if (pCVar1 != (CCharacter *)0x0) {
    CInventory::removeListener(*(CInventory **)(pCVar1 + 0x490),(iInventoryListener *)(this + 0x10))
    ;
  }
  *(CCharacter **)(this + 0x60) = param_1;
  if (param_1 != (CCharacter *)0x0) {
    CInventory::addListener(*(CInventory **)(param_1 + 0x490),(iInventoryListener *)(this + 0x10));
    return;
  }
  return;
}

/* address=00b23ab0
   symbol=CEnchantMenu::_GLOBAL__I_CEnchantMenu */

/* CEnchantMenu::CEnchantMenu(CGameUI&, CSettings&, Ogre::RenderWindow*, Ogre::SceneManager*,
   CEGUI::Window*, CResourceManager*) */

void CEnchantMenu::_GLOBAL__I_CEnchantMenu(void)

{
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
  std::string::string((string *)::KLayoutFunctionNames,"GUIEXITGAME",&aStack_2c2);
  std::string::string((string *)(::KLayoutFunctionNames + 8),"GUIEXITAPPLICATION",&aStack_2c1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x10),"GUINEWGAME",&aStack_2c0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x18),"GUICONTINUEGAME",&aStack_2bf);
  std::string::string((string *)(::KLayoutFunctionNames + 0x20),"GUINEWGAMEMENU",&aStack_2be);
  std::string::string((string *)(::KLayoutFunctionNames + 0x28),"GUICONTINUEGAMEMENU",&aStack_2bd);
  std::string::string((string *)(::KLayoutFunctionNames + 0x30),"GUICLOSEMENU",&aStack_2bc);
  std::string::string((string *)(::KLayoutFunctionNames + 0x38),"GUIBACK",&aStack_2bb);
  std::string::string((string *)(::KLayoutFunctionNames + 0x40),"GUIDECLINE",&aStack_2ba);
  std::string::string((string *)(::KLayoutFunctionNames + 0x48),"GUIACCEPT",&aStack_2b9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x50),"GUIOK",&aStack_2b8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x58),"GUIPAUSE",&aStack_2b7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x60),"GUISCROLLUP",&aStack_2b6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x68),"GUISCROLLDOWN",&aStack_2b5);
  std::string::string((string *)(::KLayoutFunctionNames + 0x70),"GUISELECT1",&aStack_2b4);
  std::string::string((string *)(::KLayoutFunctionNames + 0x78),"GUISELECT2",&aStack_2b3);
  std::string::string((string *)(::KLayoutFunctionNames + 0x80),"GUISELECT3",&aStack_2b2);
  std::string::string((string *)(::KLayoutFunctionNames + 0x88),"GUISELECT4",&aStack_2b1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x90),"GUISELECT5",&aStack_2b0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x98),"GUISELECT6",&aStack_2af);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa0),"GUISELECT7",&aStack_2ae);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa8),"GUISELECT8",&aStack_2ad);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb0),"GUISELECT9",&aStack_2ac);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb8),"GUISELECT10",&aStack_2ab);
  std::string::string((string *)(::KLayoutFunctionNames + 0xc0),"GUISELECT11",&aStack_2aa);
  std::string::string((string *)(::KLayoutFunctionNames + 200),"GUISELECT12",&aStack_2a9);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd0),"GUISELECT13",&aStack_2a8);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd8),"GUISELECT14",&aStack_2a7);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe0),"GUISELECT15",&aStack_2a6);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe8),"GUISELECT16",&aStack_2a5);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf0),"GUISELECT17",&aStack_2a4);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf8),"GUISELECT18",&aStack_2a3);
  std::string::string((string *)(::KLayoutFunctionNames + 0x100),"GUISELECT19",&aStack_2a2);
  std::string::string((string *)(::KLayoutFunctionNames + 0x108),"GUISELECT20",&aStack_2a1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x110),"GUISELECT21",&aStack_2a0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x118),"GUISELECT22",&aStack_29f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x120),"GUISELECT23",&aStack_29e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x128),"GUISELECT24",&aStack_29d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x130),"GUISELECT25",&aStack_29c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x138),"GUISELECT26",&aStack_29b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x140),"GUISELECT27",&aStack_29a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x148),"GUISELECT28",&aStack_299);
  std::string::string((string *)(::KLayoutFunctionNames + 0x150),"GUISELECT29",&aStack_298);
  std::string::string((string *)(::KLayoutFunctionNames + 0x158),"GUISELECT30",&aStack_297);
  std::string::string((string *)(::KLayoutFunctionNames + 0x160),"GUISELECT31",&aStack_296);
  std::string::string((string *)(::KLayoutFunctionNames + 0x168),"GUISELECT32",&aStack_295);
  std::string::string((string *)(::KLayoutFunctionNames + 0x170),"GUISELECT33",&aStack_294);
  std::string::string((string *)(::KLayoutFunctionNames + 0x178),"GUISELECT34",&aStack_293);
  std::string::string((string *)(::KLayoutFunctionNames + 0x180),"GUISELECT35",&aStack_292);
  std::string::string((string *)(::KLayoutFunctionNames + 0x188),"GUISELECT36",&aStack_291);
  std::string::string((string *)(::KLayoutFunctionNames + 400),"GUISELECT37",&aStack_290);
  std::string::string((string *)(::KLayoutFunctionNames + 0x198),"GUISELECT38",&aStack_28f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a0),"GUISELECT39",&aStack_28e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a8),"GUISELECT40",&aStack_28d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b0),"GUISELECT41",&aStack_28c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b8),"GUISELECT42",&aStack_28b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c0),"GUISELECT43",&aStack_28a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c8),"GUISELECT44",&aStack_289);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d0),"GUISELECT45",&aStack_288);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d8),"GUISELECT46",&aStack_287);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e0),"GUISELECT47",&aStack_286);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e8),"GUISELECT48",&aStack_285);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f0),"GUISELECT49",&aStack_284);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f8),"GUISELECT50",&aStack_283);
  std::string::string((string *)(::KLayoutFunctionNames + 0x200),"GUISELECTA",&aStack_282);
  std::string::string((string *)(::KLayoutFunctionNames + 0x208),"GUISELECTB",&aStack_281);
  std::string::string((string *)(::KLayoutFunctionNames + 0x210),"GUISELECTC",&aStack_280);
  std::string::string((string *)(::KLayoutFunctionNames + 0x218),"GUISELECTD",&aStack_27f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x220),"GUIFEEDPET",&aStack_27e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x228),"GUIPETPASSIVE",&aStack_27d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x230),"GUIPETAGGRESSIVE",&aStack_27c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x238),"GUIPETDEFENSIVE",&aStack_27b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x240),"GUITOGGLEINVENTORY",&aStack_27a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x248),"GUITOGGLEQUESTS",&aStack_279);
  std::string::string((string *)(::KLayoutFunctionNames + 0x250),"GUITOGGLESTATS",&aStack_278);
  std::string::string((string *)(::KLayoutFunctionNames + 600),"GUITOGGLESKILLS",&aStack_277);
  std::string::string((string *)(::KLayoutFunctionNames + 0x260),"GUITOGGLEPERKS",&aStack_276);
  std::string::string((string *)(::KLayoutFunctionNames + 0x268),"GUITOGGLEJOURNAL",&aStack_275);
  std::string::string((string *)(::KLayoutFunctionNames + 0x270),"GUITOGGLEPET",&aStack_274);
  std::string::string((string *)(::KLayoutFunctionNames + 0x278),"GUITOGGLEAUTOMAP",&aStack_273);
  std::string::string((string *)(::KLayoutFunctionNames + 0x280),"GUITOGGLEOPTIONS",&aStack_272);
  std::string::string((string *)(::KLayoutFunctionNames + 0x288),"GUITOGGLEITEMNAMES",&aStack_271);
  std::string::string((string *)(::KLayoutFunctionNames + 0x290),"GUIAUTOMAPZOOMIN",&aStack_270);
  std::string::string((string *)(::KLayoutFunctionNames + 0x298),"GUIAUTOMAPZOOMOUT",&aStack_26f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a0),"GUILEVELUP",&aStack_26e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a8),"GUISTATSUP",&aStack_26d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b0),"GUISKILLUP",&aStack_26c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b8),"GUIPET1",&aStack_26b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c0),"GUIPET2",&aStack_26a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c8),"GUIPET3",&aStack_269);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d0),"GUIDELETE1",&aStack_268);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d8),"GUIDELETE2",&aStack_267);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e0),"GUIDELETE3",&aStack_266);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e8),"GUIDELETE4",&aStack_265);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f0),"GUISETTINGSMENU",&aStack_264);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f8),"GUIPETSELL",&aStack_263);
  std::string::string((string *)(::KLayoutFunctionNames + 0x300),"NONE",&aStack_262);
  __cxa_atexit(::__tcf_0,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSOUNDBANK_STRINGS,L"STEP_SOUND",&aStack_261);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 8),L"STRIKE_SOUND",&aStack_260);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x10),L"PHYSICALHIT_SOUND",&aStack_25f);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x18),L"ICEHIT_SOUND",&aStack_25e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x20),L"FIREHIT_SOUND",&aStack_25d);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x28),L"ELECTRICHIT_SOUND",&aStack_25c);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x30),L"POISONHIT_SOUND",&aStack_25b);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x38),L"SHIELDBLOCK",&aStack_25a);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x40),L"BLOCK",&aStack_259);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x48),L"CRITICAL_SOUND",&aStack_258);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x50),L"ATTACK_SOUND",&aStack_257);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x58),L"IDLE_SOUND",&aStack_256)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x60),L"DEATH_SOUND",&aStack_255);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x68),L"ROAR_SOUND",&aStack_254)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x70),L"FLEE_SOUND",&aStack_253)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x78),L"MISS_SOUND",&aStack_252)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x80),L"FALL_SOUND",&aStack_251)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x88),L"LAND_SOUND",&aStack_250)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x90),L"TAKE_SOUND",&aStack_24f)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x98),L"SPAWN_SOUND",&aStack_24e);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa0),L"USE_SOUND",&aStack_24d);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa8),L"EQUIP_SOUND",&aStack_24c);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb0),L"OPENMENU_SOUND",&aStack_24b);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb8),L"BUY_SOUND",&aStack_24a);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xc0),L"ERROR_SOUND",&aStack_249);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 200),L"LEVELUP_SOUND",&aStack_248);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd0),L"EFFORT_SOUND",&aStack_247);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd8),L"SPENDPOINT_SOUND",&aStack_246);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe0),L"PORTALENTER_SOUND",&aStack_245);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe8),L"POERTALEXIT_SOUND",&aStack_244);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf0),L"SKILLASSIGN_SOUND",&aStack_243);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf8),L"QUESTRECEIVED_SOUND",&aStack_242);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x100),L"QUESTCOMPLETED_SOUND",&aStack_241)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x108),L"LOWMANA_SOUND",&aStack_240);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x110),L"MISSILEREFLECT_SOUND",&aStack_23f)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x118),L"BADEFFECT_SOUND",&aStack_23e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x120),L"GOODEFFECT_SOUND",&aStack_23d);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x128),L"NPCDIALOG_SOUND",&aStack_23c);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x130),L"NPCGREET",&aStack_23b);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x138),L"NPCBYE",&aStack_23a);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x140),L"NPCPURCHASE",&aStack_239);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x148),L"NPCSELL",&aStack_238);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x150),L"VOICEPETINVENTORYFULL_SOUND",
             &aStack_237);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x158),L"VOICEPETDEPARTED_SOUND",
             &aStack_236);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x160),L"VOICEPETRETURNED_SOUND",
             &aStack_235);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x168),L"VOICEPETFLED_SOUND",&aStack_234);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x170),L"VOICEPETLEVELUP_SOUND",&aStack_233
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x178),L"VOICEINVENTORYFULL_SOUND",
             &aStack_232);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x180),L"VOICEINSUFFICIENTGOLD_SOUND",
             &aStack_231);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x188),L"VOICEIMPOSSIBLE_SOUND",&aStack_230
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 400),L"VOICECANTCAST_SOUND",&aStack_22f);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x198),L"VOICECANTCASTHERE_SOUND",
             &aStack_22e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a0),L"VOICEHEALTHLOW_SOUND",&aStack_22d)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a8),L"VOICEMANALOW_SOUND",&aStack_22c);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b0),L"VOICETRAPSPRUNG_SOUND",&aStack_22b
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b8),L"VOICEREFRESHED_SOUND",&aStack_22a)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c0),L"VOICEPOWERFUL_SOUND",&aStack_229);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c8),L"VOICEHEALTHY_SOUND",&aStack_228);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d0),L"VOICEILL_SOUND",&aStack_227);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d8),L"VOICEPOISONED_SOUND",&aStack_226);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e0),L"VOICELEVELUP_SOUND",&aStack_225);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e8),L"VOICEFAMEUP_SOUND",&aStack_224);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f0),L"VOICESKILLUP_SOUND",&aStack_223);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f8),L"VOICEFORTUNEGOOD_SOUND",
             &aStack_222);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x200),L"VOICEFORTUNEBAD_SOUND",&aStack_221
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x208),L"VOICESPELLLEARNED_SOUND",
             &aStack_220);
  ::KSOUNDBANK_STRINGS._528_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_1,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KALIGNMENT_STRINGS,L"NEUTRAL",&aStack_21f);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 8),L"GOOD",&aStack_21e);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x10),L"EVIL",&aStack_21d);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x18),L"ALL",&aStack_21c);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x20),L"BERSERK",&aStack_21b);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x28),L"EVILBERSERK",&aStack_21a);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x30),L"GOODBERSERK",&aStack_219);
  __cxa_atexit(::__tcf_2,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KAITYPE_STRINGS,L"NORMAL",&aStack_218);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 8),L"RANGEDDEFENDER",&aStack_217);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x10),L"DEFENDER",&aStack_216);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x18),L"RANGEDCASTER",&aStack_215);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x20),L"CIRCLER",&aStack_214);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x28),L"RESURRECTER",&aStack_213);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x30),L"DUMMY",&aStack_212);
  __cxa_atexit(::__tcf_3,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gDAMAGE_TYPES,L"Physical",&aStack_211);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 8),L"Magical",&aStack_210);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x10),L"Fire",&aStack_20f);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x18),L"Ice",&aStack_20e);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x20),L"Electric",&aStack_20d);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x28),L"Poison",&aStack_20c);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x30),L"All",&aStack_20b);
  __cxa_atexit(::__tcf_4,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::gTARGET_TYPES,L"USER",&aStack_20a);
  std::wstring::wstring((wstring_conflict *)&DAT_014c1c28,L"ITEM",&aStack_209);
  __cxa_atexit(::__tcf_5,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSFXTypeName,L"STATIONARYTARGET",&aStack_208);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 8),L"STATIONARYOWNER",&aStack_207);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x10),L"STATIONARY",&aStack_206);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x18),L"STATIONARYPORTAL",&aStack_205)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x20),L"BEAM",&aStack_204);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x28),L"FOLLOWOWNER",&aStack_203);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x30),L"FOLLOWTARGET",&aStack_202);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x38),L"PROJECTILELOCATION",&aStack_201);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x40),L"PROJECTILECHARACTER",&aStack_200);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x48),L"PROJECTILELOCATIONERRATIC",&aStack_1ff);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x50),L"PROJECTILECHARACTERERRATIC",&aStack_1fe);
  __cxa_atexit(::__tcf_6,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KCharacterNames,L"NA",&aStack_1fd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 8),L"NA",&aStack_1fc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x10),L"NA",&aStack_1fb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x18),L"NA",&aStack_1fa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x20),L"NA",&aStack_1f9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x28),L"NA",&aStack_1f8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x30),L"NA",&aStack_1f7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x38),L"NA",&aStack_1f6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x40),L"Bksp",&aStack_1f5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x48),L"Tab",&aStack_1f4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x50),L"NA",&aStack_1f3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x58),L"NA",&aStack_1f2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x60),L"Ctr",&aStack_1f1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x68),L"Ret",&aStack_1f0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x70),L"NA",&aStack_1ef);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x78),L"NA",&aStack_1ee);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x80),L"Shift",&aStack_1ed);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x88),L"Ctrl",&aStack_1ec);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x90),L"Alt",&aStack_1eb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x98),L"Tab",&aStack_1ea);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa0),L"NA",&aStack_1e9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa8),L"NA",&aStack_1e8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb0),L"NA",&aStack_1e7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb8),L"NA",&aStack_1e6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xc0),L"NA",&aStack_1e5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 200),L"NA",&aStack_1e4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd0),L"NA",&aStack_1e3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd8),L"NA",&aStack_1e2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe0),L"NA",&aStack_1e1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe8),L"NA",&aStack_1e0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf0),L"NA",&aStack_1df);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf8),L"NA",&aStack_1de);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x100),L"space",&aStack_1dd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x108),L"pgup",&aStack_1dc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x110),L"pgdn",&aStack_1db);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x118),L"end",&aStack_1da);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x120),L"home",&aStack_1d9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x128),L"left arrow",&aStack_1d8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x130),L"up arrow",&aStack_1d7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x138),L"right arrow",&aStack_1d6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x140),L"down arrow",&aStack_1d5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x148),L")",&aStack_1d4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x150),L"*",&aStack_1d3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x158),L"+",&aStack_1d2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x160),L",",&aStack_1d1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x168),L"ins",&aStack_1d0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x170),L"del",&aStack_1cf);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x178),L"/",&aStack_1ce);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x180),L"0",&aStack_1cd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x188),L"1",&aStack_1cc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 400),L"2",&aStack_1cb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x198),L"3",&aStack_1ca);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a0),L"4",&aStack_1c9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a8),L"5",&aStack_1c8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b0),L"6",&aStack_1c7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b8),L"7",&aStack_1c6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c0),L"8",&aStack_1c5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c8),L"9",&aStack_1c4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d0),L":",&aStack_1c3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d8),L";",&aStack_1c2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e0),L"<",&aStack_1c1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e8),L"=",&aStack_1c0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f0),L">",&aStack_1bf);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f8),L"?",&aStack_1be);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x200),L"@",&aStack_1bd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x208),L"a",&aStack_1bc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x210),L"b",&aStack_1bb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x218),L"c",&aStack_1ba);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x220),L"d",&aStack_1b9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x228),L"e",&aStack_1b8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x230),L"NA",&aStack_1b7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x238),L"g",&aStack_1b6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x240),L"h",&aStack_1b5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x248),L"i",&aStack_1b4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x250),L"j",&aStack_1b3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 600),L"k",&aStack_1b2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x260),L"l",&aStack_1b1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x268),L"m",&aStack_1b0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x270),L"n",&aStack_1af);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x278),L"o",&aStack_1ae);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x280),L"p",&aStack_1ad);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x288),L"NA",&aStack_1ac);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x290),L"r",&aStack_1ab);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x298),L"s",&aStack_1aa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a0),L"t",&aStack_1a9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a8),L"u",&aStack_1a8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b0),L"v",&aStack_1a7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b8),L"w",&aStack_1a6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c0),L"x",&aStack_1a5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c8),L"y",&aStack_1a4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d0),L"z",&aStack_1a3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d8),L"[",&aStack_1a2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e0),L"\\",&aStack_1a1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e8),L"]",&aStack_1a0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f0),L"^",&aStack_19f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f8),L"_",&aStack_19e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x300),L"NUM 0",&aStack_19d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x308),L"NUM 1",&aStack_19c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x310),L"NUM 2",&aStack_19b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x318),L"NUM 3",&aStack_19a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 800),L"NUM 4",&aStack_199);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x328),L"NUM 5",&aStack_198);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x330),L"NUM 6",&aStack_197);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x338),L"NUM 7",&aStack_196);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x340),L"NUM 8",&aStack_195);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x348),L"NUM 9",&aStack_194);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x350),L"*",&aStack_193);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x358),L"+",&aStack_192);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x360),L"NA",&aStack_191);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x368),L"-",&aStack_190);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x370),L"NA",&aStack_18f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x378),L"F1",&aStack_18e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x380),L"F2",&aStack_18d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x388),L"F3",&aStack_18c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x390),L"F4",&aStack_18b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x398),L"F5",&aStack_18a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a0),L"F6",&aStack_189);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a8),L"F7",&aStack_188);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b0),L"F8",&aStack_187);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b8),L"F9",&aStack_186);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c0),L"F10",&aStack_185);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c8),L"F11",&aStack_184);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d0),L"F12",&aStack_183);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d8),L"{",&aStack_182);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3e0),L"|",&aStack_181);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 1000),L"}",&aStack_180);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f0),L"~",&aStack_17f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f8),L";",&aStack_17e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x400),L"=",&aStack_17d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x408),L".",&aStack_17c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x410),L"-",&aStack_17b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x418),L",",&aStack_17a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x420),L"/",&aStack_179);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x428),L"`",&aStack_178);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x430),L"[",&aStack_177);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x438),L"\\",&aStack_176);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x440),L"]",&aStack_175);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x448),L"\'",&aStack_174);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x450),L"NA",&aStack_173);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x458),L"NA",&aStack_172);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x460),L"NA",&aStack_171);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x468),L"NA",&aStack_170);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x470),L"NA",&aStack_16f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x478),L"NA",&aStack_16e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x480),L"NA",&aStack_16d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x488),L"NA",&aStack_16c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x490),L"NA",&aStack_16b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x498),L"NA",&aStack_16a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a0),L"NA",&aStack_169);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a8),L"NA",&aStack_168);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b0),L"NA",&aStack_167);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b8),L"NA",&aStack_166);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c0),L"NA",&aStack_165);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c8),L"NA",&aStack_164);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d0),L"NA",&aStack_163);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d8),L"NA",&aStack_162);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e0),L"NA",&aStack_161);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e8),L"NA",&aStack_160);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f0),L"NA",&aStack_15f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f8),L"NA",&aStack_15e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x500),L"NA",&aStack_15d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x508),L"NA",&aStack_15c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x510),L"NA",&aStack_15b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x518),L"NA",&aStack_15a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x520),L"NA",&aStack_159);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x528),L"NA",&aStack_158);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x530),L"NA",&aStack_157);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x538),L"NA",&aStack_156);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x540),L"NA",&aStack_155);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x548),L"NA",&aStack_154);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x550),L"NA",&aStack_153);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x558),L"NA",&aStack_152);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x560),L"NA",&aStack_151);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x568),L"NA",&aStack_150);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x570),L"NA",&aStack_14f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x578),L"NA",&aStack_14e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x580),L"NA",&aStack_14d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x588),L"NA",&aStack_14c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x590),L"NA",&aStack_14b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x598),L"NA",&aStack_14a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a0),L"NA",&aStack_149);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a8),L"NA",&aStack_148);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b0),L"NA",&aStack_147);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b8),L"NA",&aStack_146);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c0),L"NA",&aStack_145);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c8),L"NA",&aStack_144);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d0),L";",&aStack_143);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d8),L"=",&aStack_142);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e0),L",",&aStack_141);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e8),L"-",&aStack_140);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f0),L".",&aStack_13f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f8),L"/",&aStack_13e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x600),L"`",&aStack_13d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x608),L"NA",&aStack_13c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x610),L"NA",&aStack_13b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x618),L"NA",&aStack_13a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x620),L"NA",&aStack_139);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x628),L"NA",&aStack_138);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x630),L"NA",&aStack_137);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x638),L"NA",&aStack_136);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x640),L"NA",&aStack_135);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x648),L"NA",&aStack_134);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x650),L"NA",&aStack_133);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x658),L"NA",&aStack_132);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x660),L"NA",&aStack_131);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x668),L"NA",&aStack_130);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x670),L"NA",&aStack_12f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x678),L"NA",&aStack_12e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x680),L"NA",&aStack_12d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x688),L"NA",&aStack_12c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x690),L"NA",&aStack_12b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x698),L"NA",&aStack_12a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a0),L"NA",&aStack_129);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a8),L"NA",&aStack_128);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b0),L"NA",&aStack_127);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b8),L"NA",&aStack_126);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c0),L"NA",&aStack_125);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c8),L"NA",&aStack_124);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d0),L"NA",&aStack_123);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d8),L"[",&aStack_122);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e0),L"\\",&aStack_121);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e8),L"]",&aStack_120);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f0),L"\'",&aStack_11f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f8),L"NA",&aStack_11e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x700),L"NA",&aStack_11d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x708),L"NA",&aStack_11c);
  __cxa_atexit(::__tcf_7,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KContextTipNames,L"TIP_INVENTORY",&aStack_11b);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 8),L"TIP_UNIDENTIFIED",&aStack_11a);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x10),L"TIP_INVENTORYFULL",&aStack_119);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x18),L"TIP_HEALTHLOW",&aStack_118);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x20),L"TIP_MANALOW",&aStack_117);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x28),L"TIP_MERCHANT",&aStack_116)
  ;
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x30),L"TIP_LEVELUP",&aStack_115);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x38),L"TIP_STATS",&aStack_114);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x40),L"TIP_SPELL",&aStack_113);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x48),L"TIP_WELCOME",&aStack_112);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x50),L"TIP_SOCKETABLE",&aStack_111);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x58),L"TIP_PETFLEE",&aStack_110);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x60),L"TIP_GAMBLE",&aStack_10f);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x68),L"TIP_ENCHANT",&aStack_10e);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x70),L"TIP_TRANSMUTE",&aStack_10d);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x78),L"TIP_PETINVENTORY",&aStack_10c);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x80),L"TIP_PETINVENTORYFULL",&aStack_10b);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x88),L"TIP_STASH",&aStack_10a);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x90),L"TIP_FISHING",&aStack_109);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x98),L"TIP_SPELLFIND",&aStack_108);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xa0),L"TIP_QUESTCOMPLETE",&aStack_107);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xa8),L"TIP_SHAREDSTASH",&aStack_106);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xb0),L"TIP_HOWTOATTACK",&aStack_105);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xb8),L"TIP_TEMP5",&aStack_104);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xc0),L"TIP_TEMP6",&aStack_103);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 200),L"TIP_TEMP7",&aStack_102);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xd0),L"TIP_TEMP8",&aStack_101);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xd8),L"TIP_TEMP9",&aStack_100);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xe0),L"TIP_TEMP10",&aStack_ff);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xe8),L"TIP_TEMP11",&aStack_fe);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xf0),L"TIP_TEMP12",&aStack_fd);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xf8),L"TIP_TEMP13",&aStack_fc);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x100),L"TIP_TEMP14",&aStack_fb);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x108),L"TIP_TEMP15",&aStack_fa);
  __cxa_atexit(::__tcf_8,0,&__dso_handle);
  ParticleUniverse::HALFSCALE._4_4_ = DAT_0142463c * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._0_4_ = Ogre::Vector3::UNIT_SCALE * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._8_4_ = DAT_00fa4810 * DAT_01424640;
  std::string::string((string *)&ParticleUniverse::ALIAS,"1",&aStack_f9);
  __cxa_atexit(std::string::~string,&ParticleUniverse::ALIAS,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::SYSTEM,"2",&aStack_f8);
  __cxa_atexit(std::string::~string,&ParticleUniverse::SYSTEM,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::TECHNIQUE,"3",&aStack_f7);
  __cxa_atexit(std::string::~string,&ParticleUniverse::TECHNIQUE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::RENDERER,"4",&aStack_f6);
  __cxa_atexit(std::string::~string,&ParticleUniverse::RENDERER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EMITTER,"5",&aStack_f5);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EMITTER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::AFFECTOR,"6",&aStack_f4);
  __cxa_atexit(std::string::~string,&ParticleUniverse::AFFECTOR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::OBSERVER,"7",&aStack_f3);
  __cxa_atexit(std::string::~string,&ParticleUniverse::OBSERVER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::HANDLER,"8",&aStack_f2);
  __cxa_atexit(std::string::~string,&ParticleUniverse::HANDLER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::BEHAVIOUR,"9",&aStack_f1);
  __cxa_atexit(std::string::~string,&ParticleUniverse::BEHAVIOUR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EXTERN,"10",&aStack_f0);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EXTERN,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DYNAMIC_ATTRIBUTE,"11",&aStack_ef);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DYNAMIC_ATTRIBUTE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DEPENDENCY,"12",&aStack_ee);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DEPENDENCY,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_TYPE_NAMES,L"",&aStack_ed);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 8),L"FIND",&aStack_ec);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x10),L"KILL NUM",&aStack_eb);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x18),L"KILL BOSS",&aStack_ea);
  __cxa_atexit(::__tcf_9,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_DIALOG_TYPE_NAMES,L"ERROR",&aStack_e9);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 8),L"INTRO",&aStack_e8);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x10),L"RETURN",&aStack_e7);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x18),L"COMPLETE",&aStack_e6);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x20),L"PASSIVE",&aStack_e5);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x28),L"DETAILS",&aStack_e4);
  __cxa_atexit(::__tcf_10,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEffect_Activation_Names,L"PASSIVE",&aStack_e3);
  std::wstring::wstring((wstring_conflict *)(::gEffect_Activation_Names + 8),L"DYNAMIC",&aStack_e2);
  std::wstring::wstring
            ((wstring_conflict *)(::gEffect_Activation_Names + 0x10),L"TRANSFER",&aStack_e1);
  __cxa_atexit(::__tcf_11,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEFFECT_STAT_MODIFIER_NAMES,L"MELEE",&aStack_e0);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 8),L"RANGED",&aStack_df);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x10),L"DEFENSE",&aStack_de);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x18),L"MAGIC",&aStack_dd);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x20),L"LEVEL",&aStack_dc);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x28),L"OWNERLEVEL",&aStack_db);
  __cxa_atexit(::__tcf_12,0,&__dso_handle);
  std::string::string((string *)::gEFFECT_STAT_MODIFIER_ICON_NAMES,"iconmelee",&aStack_da);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 8),"iconranged",&aStack_d9);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x10),"icondefense",&aStack_d8
                     );
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x18),"iconmagic",&aStack_d7);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x20),"iconmagic",&aStack_d6);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x28),"iconmagic",&aStack_d5);
  __cxa_atexit(::__tcf_13,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES,"tag_righthand",&aStack_d4);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 8),"tag_lefthand",&aStack_d3);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x10),"",&aStack_d2);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x18),"Bip01 Head",&aStack_d1);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x20),"",&aStack_d0);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x28),"Bip01 L Clavicle",&aStack_cf);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x30),"",&aStack_ce);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x38),"",&aStack_cd);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x40),"",&aStack_cc);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x48),"",&aStack_cb);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x50),"",&aStack_ca);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x58),"tag_leftarm",&aStack_c9);
  __cxa_atexit(::__tcf_14,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES_SECONDARY,"",&aStack_c8);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 8),"",&aStack_c7);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x10),"",&aStack_c6);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x18),"",&aStack_c5);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x20),"",&aStack_c4);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x28),"Bip01 R Clavicle",
                      &aStack_c3);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x30),"",&aStack_c2);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x38),"",&aStack_c1);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x40),"",&aStack_c0);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x48),"",&aStack_bf);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x50),"",&aStack_be);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x58),"",&aStack_bd);
  __cxa_atexit(::__tcf_15,0,&__dso_handle);
  std::string::string((string *)::KEquipmentIconName,"EquipLeftHand",&aStack_bc);
  std::string::string((string *)(::KEquipmentIconName + 8),"EquipRightHand",&aStack_bb);
  std::string::string((string *)(::KEquipmentIconName + 0x10),"EquipGloves",&aStack_ba);
  std::string::string((string *)(::KEquipmentIconName + 0x18),"EquipHelm",&aStack_b9);
  std::string::string((string *)(::KEquipmentIconName + 0x20),"EquipChest",&aStack_b8);
  std::string::string((string *)(::KEquipmentIconName + 0x28),"EquipShoulder",&aStack_b7);
  std::string::string((string *)(::KEquipmentIconName + 0x30),"EquipBoots",&aStack_b6);
  std::string::string((string *)(::KEquipmentIconName + 0x38),"EquipBelt",&aStack_b5);
  std::string::string((string *)(::KEquipmentIconName + 0x40),"EquipRing1",&aStack_b4);
  std::string::string((string *)(::KEquipmentIconName + 0x48),"EquipRing2",&aStack_b3);
  std::string::string((string *)(::KEquipmentIconName + 0x50),"EquipAmulet",&aStack_b2);
  std::string::string((string *)(::KEquipmentIconName + 0x58),"",&aStack_b1);
  __cxa_atexit(::__tcf_16,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames,L"CHEST",&aStack_b0);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 8),L"GLOVES",&aStack_af);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x10),L"BOOTS",&aStack_ae);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x18),L"HELMET",&aStack_ad);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x20),L"SHOULDERS",&aStack_ac);
  __cxa_atexit(::__tcf_17,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames2,L"",&aStack_ab);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 8),L"",&aStack_aa);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x10),L"",&aStack_a9);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x18),L"FACE",&aStack_a8);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x20),L"",&aStack_a7);
  __cxa_atexit(::__tcf_18,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_AIFLAG_TYPE_NAMES,L"AWARE",&aStack_a6);
  std::wstring::wstring((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 8),L"BERSERK",&aStack_a5);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x10),L"CANNOT INTERRUPT",&aStack_a4);
  std::wstring::wstring((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x18),L"FRIGHTEN",&aStack_a3);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x20),L"NO LINE OF SIGHT",&aStack_a2);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x28),L"NEVER CHANGE TARGET",&aStack_a1);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x30),L"CANNOT TARGET",&aStack_a0);
  __cxa_atexit(::__tcf_19,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_AISTAT_TYPE_NAMES,L"NONE",&aStack_9f);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 8),L"HP",&aStack_9e);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x10),L"MANA",&aStack_9d);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x18),L"HP PCT",&aStack_9c);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x20),L"MANA PCT",&aStack_9b);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x28),L"ACTIVE UNITS",&aStack_9a);
  __cxa_atexit(::__tcf_20,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::g_AISTAT_LOGIC_NAMES,L"BELOW",&aStack_99);
  std::wstring::wstring((wstring_conflict *)&DAT_014c2858,L"ABOVE",&aStack_98);
  __cxa_atexit(::__tcf_21,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_AISTAT_TARGET_NAMES,L"SELF",&aStack_97);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 8),L"FORMATION",&aStack_96);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 0x10),L"AREA",&aStack_95);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 0x18),L"AREAUNITTYPES",&aStack_94);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 0x20),L"AREAFORMATION",&aStack_93);
  __cxa_atexit(::__tcf_22,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)OGRE_UTILITIES::gPRIMITIVE_NAMES,L"SPHERE",&aStack_92);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 8),L"BOX",&aStack_91);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x10),L"PLANE",&aStack_90);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x18),L"CYLINDER",&aStack_8f);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x20),L"CONE",&aStack_8e);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x28),L"ARROW",&aStack_8d);
  __cxa_atexit(::__tcf_23,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gKEYFRAME_TYPES,L"HIT",&aStack_8c);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 8),L"BLENDIN",&aStack_8b);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x10),L"BLENDOUT",&aStack_8a);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x18),L"PLAYSOUND",&aStack_89);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x20),L"SPAWNPARTICLE",&aStack_88);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x28),L"SPAWNPARTICLE_STOP_ON_DEATH",
             &aStack_87);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x30),L"FOOTSTEP",&aStack_86);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x38),L"SHOWWEAPONTRAIL",&aStack_85);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x40),L"HIDEWEAPONTRAIL",&aStack_84);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x48),L"ATTACKSOUND",&aStack_83);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x50),L"ENABLECOLLISION",&aStack_82);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x58),L"DISABLECOLLISION",&aStack_81);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x60),L"REMOVEPARTICLES",&aStack_80);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x68),L"REMOVEANIMATIONPARTICLES",&aStack_7f);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x70),L"CAMERASHAKE",&aStack_7e);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x78),L"ATTACKEND",&aStack_7d);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x80),L"UNTARGETABLE",&aStack_7c);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x88),L"TARGETABLE",&aStack_7b);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x90),L"DAMPVELOCITY",&aStack_7a);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x98),L"UNDAMPVELOCITY",&aStack_79)
  ;
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xa0),L"SHOWWEAPONS",&aStack_78);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xa8),L"HIDEWEAPONS",&aStack_77);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xb0),L"HIDEMESH",&aStack_76);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xb8),L"SHOWMESH",&aStack_75);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xc0),L"FADEOUTMESH",&aStack_74);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 200),L"FADEINMESH",&aStack_73);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0xd0),L"CAMERASHAKE_NO_FALLOFF",&aStack_72);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0xd8),L"PLAYSOUND_NO_FALLOFF",&aStack_71);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xe0),L"HITTWO",&aStack_70);
  __cxa_atexit(::__tcf_24,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEDITOR_EVENT_NAMES,L"STOP",&aStack_6f);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 8),L"PLAY",&aStack_6e);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x10),L"RELOAD TILES",&aStack_6d);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x18),L"TOGGLE LIGHTING",&aStack_6c);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x20),L"SELECT COLLIDABLE",&aStack_6b);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x28),L"PAUSE PARTICLES",&aStack_6a);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x30),L"UNPAUSE PARTICLES",&aStack_69);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x38),L"COLLISION ALL",&aStack_68);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x40),L"COLLISION MODELS",&aStack_67);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x48),L"COLLISION PREFABS",&aStack_66);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x50),L"COLLISION ROOMPIECES",&aStack_65);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x58),L"COLLISION ROOMPROPS",&aStack_64);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x60),L"RELOAD GRAPHS",&aStack_63);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x68),L"TOGGLE PLAYER LIGHT",&aStack_62);
  __cxa_atexit(::__tcf_25,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEDITOR_FLAG_NAMES,L"LOGIC ENABLED",&aStack_61);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 8),L"INGAME MODE",&aStack_60);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x10),L"SHOW STATS",&aStack_5f);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x18),L"EDIT POSITION",&aStack_5e);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x20),L"EDIT SCALE",&aStack_5d);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x28),L"EDIT ORIENTATION",&aStack_5c);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x30),L"EDIT NONE",&aStack_5b);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x38),L"SHOW HELPERS",&aStack_5a);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x40),L"SHOW GRID",&aStack_59);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x48),L"SHOW WORKING PLANE",&aStack_58);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x50),L"SNAP TO GRID",&aStack_57);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x58),L"SUSPEND EDITOR",&aStack_56);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x60),L"LIGHTING VISIBLE",&aStack_55);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x68),L"RECALCULATE LIGHTING",&aStack_54);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x70),L"SHOW EDGES",&aStack_53);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x78),L"UPDATE PARTICLES CIRCLE",&aStack_52
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x80),L"SHOW LOGIC OUTPUT",&aStack_51);
  __cxa_atexit(::__tcf_26,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::gEDITOR_UPDATE_MASKS,L"OBJECT SELECTION CHANGED",&aStack_50);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 8),L"OBJECT DATA CHANGED",&aStack_4f);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 0x10),L"OBJECTS CREATED",&aStack_4e);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 0x18),L"REFRESH TREE VIEW",&aStack_4d);
  __cxa_atexit(::__tcf_27,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::m_gFileVersionExtension,L".svt",&aStack_4c);
  __cxa_atexit(std::wstring::~wstring,&::m_gFileVersionExtension,&__dso_handle);
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
  __cxa_atexit(::__tcf_28,0,&__dso_handle);
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
  __cxa_atexit(::__tcf_29,0,&__dso_handle);
  return;
}

/* address=00b23ac0
   symbol=CEnchantMenu::~CEnchantMenu */

/* CEnchantMenu::~CEnchantMenu() */

void __thiscall CEnchantMenu::~CEnchantMenu(CEnchantMenu *this)

{
  *(undefined ***)this = &PTR__CEnchantMenu_00fef2b0;
  *(undefined ***)(this + 0x10) = &PTR__CEnchantMenu_00fef360;
                    /* try { // try from 00b23ad9 to 00b23b0c has its CatchHandler @ 00b23b34 */
  setPlayer(this,(CCharacter *)0x0);
  if (*(long **)(this + 0xa0) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0xa0) + 8))();
    *(undefined8 *)(this + 0xa0) = 0;
  }
  if (*(long **)(this + 0xb8) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0xb8) + 8))();
    *(undefined8 *)(this + 0xb8) = 0;
  }
  *(undefined ***)(this + 0x10) = &PTR__iInventoryListener_00fce450;
  *(undefined ***)this = &PTR__CSubMenu_00fe64b0;
  CRunicCore::~CRunicCore((CRunicCore *)this);
  return;
}

/* address=00b23b60
   symbol=CEnchantMenu::~CEnchantMenu */

/* non-virtual thunk to CEnchantMenu::~CEnchantMenu() */

void __thiscall CEnchantMenu::~CEnchantMenu(CEnchantMenu *this)

{
  ~CEnchantMenu(this + -0x10);
  return;
}

/* address=00b23b70
   symbol=CEnchantMenu::~CEnchantMenu */

/* non-virtual thunk to CEnchantMenu::~CEnchantMenu() */

void __thiscall CEnchantMenu::~CEnchantMenu(CEnchantMenu *this)

{
  ~CEnchantMenu(this + -0x10);
  return;
}

/* address=00b23b80
   symbol=CEnchantMenu::~CEnchantMenu */

/* CEnchantMenu::~CEnchantMenu() */

void __thiscall CEnchantMenu::~CEnchantMenu(CEnchantMenu *this)

{
  ~CEnchantMenu(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}

/* address=00b23ba0
   symbol=CEnchantMenu::handle_CloseButton */

/* CEnchantMenu::handle_CloseButton(CEGUI::EventArgs const&) */

undefined8 __thiscall CEnchantMenu::handle_CloseButton(CEnchantMenu *this,EventArgs *param_1)

{
  long lVar1;

  if (*(int *)(param_1 + 0x28) != 0) {
    return 1;
  }
  this[0x72] = (CEnchantMenu)0x1;
  CCharacter::setTarget(*(CCharacter **)(*(long *)(this + 0x80) + 0x38),(CCharacter *)0x0);
  lVar1 = *(long *)(*(long *)(this + 0x80) + 0x1920);
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
  CGameUI::closeRight(*(CGameUI **)(this + 0x80));
  return 1;
}

/* address=00b23fd0
   symbol=CEnchantMenu::update */

/* WARNING: Removing unreachable block (ram,0x00b243a9) */
/* WARNING: Removing unreachable block (ram,0x00b2438a) */
/* CEnchantMenu::update(float) */

void __thiscall CEnchantMenu::update(CEnchantMenu *this,float param_1)

{
  int *piVar1;
  float fVar2;
  int iVar3;
  code *pcVar4;
  char cVar5;
  long *plVar6;
  float *pfVar7;
  bool bVar8;
  undefined8 uVar9;
  string local_68 [16];
  long local_58 [2];
  long local_48;
  allocator local_3b;
  allocator local_3a;
  allocator local_39 [9];

  CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0x78),KSETTINGS_RES_WIDTH);
  CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0x78),KSETTINGS_RES_HEIGHT);
  if (this[0x70] == (CEnchantMenu)0x0) {
    *(undefined8 *)(this + 0xf0) = 0;
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x30),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x38),0));
    if ((this[0x70] == (CEnchantMenu)0x0) && (this[0x71] != (CEnchantMenu)0x0)) {
      return;
    }
  }
  if (*(CGenericModel **)(this + 0xa0) != (CGenericModel *)0x0) {
    CGenericModel::updateAnimation(*(CGenericModel **)(this + 0xa0),param_1,false);
    Ogre::Entity::_updateAnimation();
    plVar6 = *(long **)(*(long *)(this + 0xa0) + 0x130);
    pcVar4 = *(code **)(*plVar6 + 0x1b0);
                    /* try { // try from 00b2408a to 00b2408e has its CatchHandler @ 00b24395 */
    std::string::string((string *)&local_48,"tag_dropdowntop",local_39);
                    /* try { // try from 00b24095 to 00b24097 has its CatchHandler @ 00b24397 */
    plVar6 = (long *)(*pcVar4)(plVar6);
    if ((allocator *)(local_48 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_48 + -8);
      iVar3 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar3 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_48 + -0x18));
      }
    }
    uVar9 = CPositionableObject::getPosition(*(CPositionableObject **)(this + 0xa0),false);
    pfVar7 = (float *)(**(code **)(*plVar6 + 0x200))(plVar6);
    fVar2 = pfVar7[1];
    CGameUI::scaledY(*(CGameUI **)(this + 0x80),*pfVar7 + (float)uVar9);
    CGameUI::scaledY(*(CGameUI **)(this + 0x80),fVar2 + (float)((ulong)uVar9 >> 0x20));
                    /* try { // try from 00b24188 to 00b2418c has its CatchHandler @ 00b24385 */
    CEGUI::Window::setPosition(*(UVector2 **)(this + 0x28));
  }
  if ((this[0x70] == (CEnchantMenu)0x0) && (this[0x71] == (CEnchantMenu)0x0)) {
                    /* try { // try from 00b24233 to 00b2424c has its CatchHandler @ 00b2435e */
    std::string::string((string *)local_58,"CLOSE",&local_3a);
    cVar5 = CGenericModel::animationPlaying(*(CGenericModel **)(this + 0xa0),(string *)local_58);
    bVar8 = false;
    if (cVar5 == '\0') {
                    /* try { // try from 00b242d5 to 00b242ee has its CatchHandler @ 00b2435e */
      std::string::string(local_68,"CLOSE",&local_3b);
      cVar5 = CGenericModel::animationQueued(*(CGenericModel **)(this + 0xa0),local_68);
      bVar8 = cVar5 == '\0';
                    /* try { // try from 00b242f8 to 00b242fc has its CatchHandler @ 00b243a4 */
      std::string::~string(local_68);
    }
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
    if (bVar8) {
      (**(code **)(**(long **)(this + 0xa0) + 0x50))(*(long **)(this + 0xa0),0);
      CEGUI::Window::removeChildWindow(*(Window **)(this + 0x18));
      this[0x71] = (CEnchantMenu)0x1;
      if (this[0x73] != (CEnchantMenu)0x0) {
        this[0x73] = (CEnchantMenu)0x0;
        CGameUI::requestSetGameState(*(CGameUI **)(this + 0x80),0,2);
      }
    }
  }
  return;
}

/* address=00b243c0
   symbol=CEnchantMenu::setOpen */

/* WARNING: Removing unreachable block (ram,0x00b252a5) */
/* WARNING: Removing unreachable block (ram,0x00b2504d) */
/* WARNING: Removing unreachable block (ram,0x00b250d4) */
/* CEnchantMenu::setOpen(bool, EAIState) */

void CEnchantMenu::setOpen
               (undefined8 param_1,undefined4 param_2,long *param_3,char param_4,undefined4 param_5)

{
  int *piVar1;
  char cVar2;
  int iVar3;
  CItem *pCVar4;
  long lVar5;
  CLevel *this;
  String local_918 [176];
  String local_868 [176];
  String local_7b8 [176];
  String local_708 [176];
  String local_658 [176];
  String local_5a8 [176];
  String local_4f8 [176];
  String local_448 [176];
  String local_398 [176];
  String local_2e8 [176];
  undefined8 local_238;
  undefined4 local_230;
  long local_228 [2];
  long local_218 [2];
  string local_208 [16];
  string local_1f8 [16];
  long local_1e8 [2];
  uchar *local_1d8 [2];
  wstring_conflict local_1c8 [16];
  uchar *local_1b8 [2];
  wstring_conflict local_1a8 [16];
  uchar *local_198 [2];
  wstring_conflict local_188 [16];
  uchar *local_178 [2];
  wstring_conflict local_168 [16];
  uchar *local_158 [2];
  wstring_conflict local_148 [16];
  uchar *local_138 [2];
  wstring_conflict local_128 [16];
  uchar *local_118 [2];
  wstring_conflict local_108 [16];
  uchar *local_f8 [2];
  wstring_conflict local_e8 [16];
  uchar *local_d8 [2];
  wstring_conflict local_c8 [16];
  uchar *local_b8 [2];
  wstring_conflict local_a8 [16];
  wstring_conflict local_98 [16];
  wstring_conflict local_88 [16];
  wstring_conflict local_78 [16];
  wstring_conflict local_68 [16];
  wstring_conflict local_58 [16];
  wstring_conflict local_48 [17];
  allocator local_37;
  allocator local_36;
  allocator local_35;
  allocator local_34;
  allocator local_33;
  allocator local_32;
  allocator local_31;
  allocator local_30;
  allocator local_2f;
  allocator local_2e;
  allocator local_2d;
  allocator local_2c;
  allocator local_2b;
  allocator local_2a;
  allocator local_29;

  *(undefined4 *)((long)param_3 + 0x10c) = param_5;
  if ((char)param_3[0xe] == '\0') {
    if (param_4 == '\0') {
      *(undefined1 *)(param_3 + 0xe) = 0;
      return;
    }
    CDynamicPropertyFile::GetInt((CDynamicPropertyFile *)param_3[0xf],KSETTINGS_RES_WIDTH);
    CDynamicPropertyFile::GetInt((CDynamicPropertyFile *)param_3[0xf],KSETTINGS_RES_HEIGHT);
    if ((setOpen(bool,EAIState)::g_Enchant == '\0') &&
       (iVar3 = __cxa_guard_acquire(&setOpen(bool,EAIState)::g_Enchant), iVar3 != 0)) {
      setOpen(bool,EAIState)::g_Enchant = &DAT_01424558;
      __cxa_guard_release(&setOpen(bool,EAIState)::g_Enchant);
      __cxa_atexit(std::wstring::~wstring,&setOpen(bool,EAIState)::g_Enchant,&__dso_handle);
    }
    if (*(long *)(setOpen(bool,EAIState)::g_Enchant + -6) == 0) {
      CStringTranslate::getSinglton();
      CStringTranslate::getTranslateString((wchar_t *)local_48);
                    /* try { // try from 00b24f35 to 00b24f39 has its CatchHandler @ 00b250a4 */
      std::wstring::assign((wstring_conflict *)&setOpen(bool,EAIState)::g_Enchant);
      std::wstring::~wstring(local_48);
    }
    if ((setOpen(bool,EAIState)::g_Destroy == '\0') &&
       (iVar3 = __cxa_guard_acquire(&setOpen(bool,EAIState)::g_Destroy), iVar3 != 0)) {
      setOpen(bool,EAIState)::g_Destroy = &DAT_01424558;
      __cxa_guard_release(&setOpen(bool,EAIState)::g_Destroy);
      __cxa_atexit(std::wstring::~wstring,&setOpen(bool,EAIState)::g_Destroy,&__dso_handle);
    }
    if (*(long *)(setOpen(bool,EAIState)::g_Destroy + -6) == 0) {
      CStringTranslate::getSinglton();
      CStringTranslate::getTranslateString((wchar_t *)local_58);
                    /* try { // try from 00b24eb5 to 00b24eb9 has its CatchHandler @ 00b25265 */
      std::wstring::assign((wstring_conflict *)&setOpen(bool,EAIState)::g_Destroy);
      std::wstring::~wstring(local_58);
    }
    if ((setOpen(bool,EAIState)::g_Sockets == '\0') &&
       (iVar3 = __cxa_guard_acquire(&setOpen(bool,EAIState)::g_Sockets), iVar3 != 0)) {
      setOpen(bool,EAIState)::g_Sockets = &DAT_01424558;
      __cxa_guard_release(&setOpen(bool,EAIState)::g_Sockets);
      __cxa_atexit(std::wstring::~wstring,&setOpen(bool,EAIState)::g_Sockets,&__dso_handle);
    }
    if (*(long *)(setOpen(bool,EAIState)::g_Sockets + -6) == 0) {
      CStringTranslate::getSinglton();
      CStringTranslate::getTranslateString((wchar_t *)local_68);
                    /* try { // try from 00b24e35 to 00b24e39 has its CatchHandler @ 00b25255 */
      std::wstring::assign((wstring_conflict *)&setOpen(bool,EAIState)::g_Sockets);
      std::wstring::~wstring(local_68);
    }
    if ((setOpen(bool,EAIState)::g_Recover == '\0') &&
       (iVar3 = __cxa_guard_acquire(&setOpen(bool,EAIState)::g_Recover), iVar3 != 0)) {
      setOpen(bool,EAIState)::g_Recover = &DAT_01424558;
      __cxa_guard_release(&setOpen(bool,EAIState)::g_Recover);
      __cxa_atexit(std::wstring::~wstring,&setOpen(bool,EAIState)::g_Recover,&__dso_handle);
    }
    if (*(long *)(setOpen(bool,EAIState)::g_Recover + -6) == 0) {
      CStringTranslate::getSinglton();
      CStringTranslate::getTranslateString((wchar_t *)local_78);
                    /* try { // try from 00b24db5 to 00b24db9 has its CatchHandler @ 00b25245 */
      std::wstring::assign((wstring_conflict *)&setOpen(bool,EAIState)::g_Recover);
      std::wstring::~wstring(local_78);
    }
    if ((setOpen(bool,EAIState)::g_Retire == '\0') &&
       (iVar3 = __cxa_guard_acquire(&setOpen(bool,EAIState)::g_Retire), iVar3 != 0)) {
      setOpen(bool,EAIState)::g_Retire = &DAT_01424558;
      __cxa_guard_release(&setOpen(bool,EAIState)::g_Retire);
      __cxa_atexit(std::wstring::~wstring,&setOpen(bool,EAIState)::g_Retire,&__dso_handle);
    }
    if (*(long *)(setOpen(bool,EAIState)::g_Retire + -6) == 0) {
      CStringTranslate::getSinglton();
      CStringTranslate::getTranslateString((wchar_t *)local_88);
                    /* try { // try from 00b24d35 to 00b24d39 has its CatchHandler @ 00b2523f */
      std::wstring::assign((wstring_conflict *)&setOpen(bool,EAIState)::g_Retire);
      std::wstring::~wstring(local_88);
    }
    if ((setOpen(bool,EAIState)::g_Heirloom == '\0') &&
       (iVar3 = __cxa_guard_acquire(&setOpen(bool,EAIState)::g_Heirloom), iVar3 != 0)) {
      setOpen(bool,EAIState)::g_Heirloom = &DAT_01424558;
      __cxa_guard_release(&setOpen(bool,EAIState)::g_Heirloom);
      __cxa_atexit(std::wstring::~wstring,&setOpen(bool,EAIState)::g_Heirloom,&__dso_handle);
    }
    if (*(long *)(setOpen(bool,EAIState)::g_Heirloom + -6) == 0) {
      CStringTranslate::getSinglton();
      CStringTranslate::getTranslateString((wchar_t *)local_98);
                    /* try { // try from 00b24cbd to 00b24cc1 has its CatchHandler @ 00b2523a */
      std::wstring::assign((wstring_conflict *)&setOpen(bool,EAIState)::g_Heirloom);
      std::wstring::~wstring(local_98);
    }
    switch(*(undefined4 *)((long)param_3 + 0x10c)) {
    case 0x15:
                    /* try { // try from 00b24b5d to 00b24b61 has its CatchHandler @ 00b250a2 */
      std::wstring::wstring(local_a8,setOpen(bool,EAIState)::g_Enchant,&local_29);
                    /* try { // try from 00b24b70 to 00b24b74 has its CatchHandler @ 00b25096 */
      STRINGS::StringConvertToUTF8((wstring_conflict *)local_b8);
                    /* try { // try from 00b24b88 to 00b24b8c has its CatchHandler @ 00b25094 */
      CEGUI::String::String(local_2e8,local_b8[0]);
                    /* try { // try from 00b24b94 to 00b24b98 has its CatchHandler @ 00b25092 */
      CEGUI::Window::setText((String *)param_3[8]);
                    /* try { // try from 00b24b9c to 00b24ba0 has its CatchHandler @ 00b25094 */
      CEGUI::String::~String(local_2e8);
                    /* try { // try from 00b24ba4 to 00b24ba8 has its CatchHandler @ 00b25096 */
      std::string::~string((string *)local_b8);
                    /* try { // try from 00b24bac to 00b24bb0 has its CatchHandler @ 00b250a2 */
      std::wstring::~wstring(local_a8);
                    /* try { // try from 00b24bcb to 00b24bcf has its CatchHandler @ 00b25086 */
      std::wstring::wstring(local_c8,setOpen(bool,EAIState)::g_Enchant,&local_2a);
                    /* try { // try from 00b24bde to 00b24be2 has its CatchHandler @ 00b25084 */
      STRINGS::StringConvertToUTF8((wstring_conflict *)local_d8);
                    /* try { // try from 00b24bf6 to 00b24bfa has its CatchHandler @ 00b25082 */
      CEGUI::String::String(local_398,local_d8[0]);
                    /* try { // try from 00b24c02 to 00b24c06 has its CatchHandler @ 00b25076 */
      CEGUI::Window::setText((String *)param_3[10]);
                    /* try { // try from 00b24c0a to 00b24c0e has its CatchHandler @ 00b25082 */
      CEGUI::String::~String(local_398);
                    /* try { // try from 00b24c12 to 00b24c16 has its CatchHandler @ 00b25084 */
      std::string::~string((string *)local_d8);
                    /* try { // try from 00b24c1a to 00b24c1e has its CatchHandler @ 00b25086 */
      std::wstring::~wstring(local_c8);
      break;
    case 0x16:
                    /* try { // try from 00b24a7c to 00b24a80 has its CatchHandler @ 00b25215 */
      std::wstring::wstring(local_e8,setOpen(bool,EAIState)::g_Enchant,&local_2b);
                    /* try { // try from 00b24a8f to 00b24a93 has its CatchHandler @ 00b25205 */
      STRINGS::StringConvertToUTF8((wstring_conflict *)local_f8);
                    /* try { // try from 00b24aa7 to 00b24aab has its CatchHandler @ 00b251f5 */
      CEGUI::String::String(local_448,local_f8[0]);
                    /* try { // try from 00b24ab3 to 00b24ab7 has its CatchHandler @ 00b251e5 */
      CEGUI::Window::setText((String *)param_3[8]);
                    /* try { // try from 00b24abb to 00b24abf has its CatchHandler @ 00b251f5 */
      CEGUI::String::~String(local_448);
                    /* try { // try from 00b24ac3 to 00b24ac7 has its CatchHandler @ 00b25205 */
      std::string::~string((string *)local_f8);
                    /* try { // try from 00b24acb to 00b24acf has its CatchHandler @ 00b25215 */
      std::wstring::~wstring(local_e8);
                    /* try { // try from 00b24aea to 00b24aee has its CatchHandler @ 00b251d5 */
      std::wstring::wstring(local_108,setOpen(bool,EAIState)::g_Enchant,&local_2c);
                    /* try { // try from 00b24afd to 00b24b01 has its CatchHandler @ 00b251c5 */
      STRINGS::StringConvertToUTF8((wstring_conflict *)local_118);
                    /* try { // try from 00b24b15 to 00b24b19 has its CatchHandler @ 00b25048 */
      CEGUI::String::String(local_4f8,local_118[0]);
                    /* try { // try from 00b24b21 to 00b24b25 has its CatchHandler @ 00b25025 */
      CEGUI::Window::setText((String *)param_3[10]);
                    /* try { // try from 00b24b29 to 00b24b2d has its CatchHandler @ 00b25048 */
      CEGUI::String::~String(local_4f8);
                    /* try { // try from 00b24b31 to 00b24b35 has its CatchHandler @ 00b251c5 */
      std::string::~string((string *)local_118);
                    /* try { // try from 00b24b39 to 00b24b3d has its CatchHandler @ 00b251d5 */
      std::wstring::~wstring(local_108);
      break;
    case 0x19:
                    /* try { // try from 00b24537 to 00b2453b has its CatchHandler @ 00b25074 */
      std::wstring::wstring(local_168,setOpen(bool,EAIState)::g_Sockets,&local_2f);
                    /* try { // try from 00b2454a to 00b2454e has its CatchHandler @ 00b25072 */
      STRINGS::StringConvertToUTF8((wstring_conflict *)local_178);
                    /* try { // try from 00b24562 to 00b24566 has its CatchHandler @ 00b25069 */
      CEGUI::String::String(local_708,local_178[0]);
                    /* try { // try from 00b2456e to 00b24572 has its CatchHandler @ 00b25067 */
      CEGUI::Window::setText((String *)param_3[8]);
                    /* try { // try from 00b24576 to 00b2457a has its CatchHandler @ 00b25069 */
      CEGUI::String::~String(local_708);
                    /* try { // try from 00b2457e to 00b24582 has its CatchHandler @ 00b25072 */
      std::string::~string((string *)local_178);
                    /* try { // try from 00b24586 to 00b2458a has its CatchHandler @ 00b25074 */
      std::wstring::~wstring(local_168);
                    /* try { // try from 00b245a5 to 00b245a9 has its CatchHandler @ 00b25062 */
      std::wstring::wstring(local_188,setOpen(bool,EAIState)::g_Destroy,&local_30);
                    /* try { // try from 00b245b8 to 00b245bc has its CatchHandler @ 00b2505c */
      STRINGS::StringConvertToUTF8((wstring_conflict *)local_198);
                    /* try { // try from 00b245d0 to 00b245d4 has its CatchHandler @ 00b2505a */
      CEGUI::String::String(local_7b8,local_198[0]);
                    /* try { // try from 00b245dc to 00b245e0 has its CatchHandler @ 00b25058 */
      CEGUI::Window::setText((String *)param_3[10]);
                    /* try { // try from 00b245e4 to 00b245e8 has its CatchHandler @ 00b2505a */
      CEGUI::String::~String(local_7b8);
                    /* try { // try from 00b245ec to 00b245f0 has its CatchHandler @ 00b2505c */
      std::string::~string((string *)local_198);
                    /* try { // try from 00b245f4 to 00b245f8 has its CatchHandler @ 00b25062 */
      std::wstring::~wstring(local_188);
      break;
    case 0x1a:
                    /* try { // try from 00b2499b to 00b2499f has its CatchHandler @ 00b250f5 */
      std::wstring::wstring(local_128,setOpen(bool,EAIState)::g_Sockets,&local_2d);
                    /* try { // try from 00b249ae to 00b249b2 has its CatchHandler @ 00b250ec */
      STRINGS::StringConvertToUTF8((wstring_conflict *)local_138);
                    /* try { // try from 00b249c6 to 00b249ca has its CatchHandler @ 00b250e7 */
      CEGUI::String::String(local_5a8,local_138[0]);
                    /* try { // try from 00b249d2 to 00b249d6 has its CatchHandler @ 00b250e2 */
      CEGUI::Window::setText((String *)param_3[8]);
                    /* try { // try from 00b249da to 00b249de has its CatchHandler @ 00b250e7 */
      CEGUI::String::~String(local_5a8);
                    /* try { // try from 00b249e2 to 00b249e6 has its CatchHandler @ 00b250ec */
      std::string::~string((string *)local_138);
                    /* try { // try from 00b249ea to 00b249ee has its CatchHandler @ 00b250f5 */
      std::wstring::~wstring(local_128);
                    /* try { // try from 00b24a09 to 00b24a0d has its CatchHandler @ 00b25175 */
      std::wstring::wstring(local_148,setOpen(bool,EAIState)::g_Recover,&local_2e);
                    /* try { // try from 00b24a1c to 00b24a20 has its CatchHandler @ 00b25165 */
      STRINGS::StringConvertToUTF8((wstring_conflict *)local_158);
                    /* try { // try from 00b24a34 to 00b24a38 has its CatchHandler @ 00b25155 */
      CEGUI::String::String(local_658,local_158[0]);
                    /* try { // try from 00b24a40 to 00b24a44 has its CatchHandler @ 00b25145 */
      CEGUI::Window::setText((String *)param_3[10]);
                    /* try { // try from 00b24a48 to 00b24a4c has its CatchHandler @ 00b25155 */
      CEGUI::String::~String(local_658);
                    /* try { // try from 00b24a50 to 00b24a54 has its CatchHandler @ 00b25165 */
      std::string::~string((string *)local_158);
                    /* try { // try from 00b24a58 to 00b24a5c has its CatchHandler @ 00b25175 */
      std::wstring::~wstring(local_148);
      break;
    case 0x1b:
                    /* try { // try from 00b248bd to 00b248c1 has its CatchHandler @ 00b251b5 */
      std::wstring::wstring(local_1a8,setOpen(bool,EAIState)::g_Heirloom,&local_31);
                    /* try { // try from 00b248d0 to 00b248d4 has its CatchHandler @ 00b251a5 */
      STRINGS::StringConvertToUTF8((wstring_conflict *)local_1b8);
                    /* try { // try from 00b248e8 to 00b248ec has its CatchHandler @ 00b25195 */
      CEGUI::String::String(local_868,local_1b8[0]);
                    /* try { // try from 00b248f4 to 00b248f8 has its CatchHandler @ 00b25185 */
      CEGUI::Window::setText((String *)param_3[8]);
                    /* try { // try from 00b248fc to 00b24900 has its CatchHandler @ 00b25195 */
      CEGUI::String::~String(local_868);
                    /* try { // try from 00b24904 to 00b24908 has its CatchHandler @ 00b251a5 */
      std::string::~string((string *)local_1b8);
                    /* try { // try from 00b2490c to 00b24910 has its CatchHandler @ 00b251b5 */
      std::wstring::~wstring(local_1a8);
                    /* try { // try from 00b2492b to 00b2492f has its CatchHandler @ 00b25135 */
      std::wstring::wstring(local_1c8,setOpen(bool,EAIState)::g_Retire,&local_32);
                    /* try { // try from 00b2493e to 00b24942 has its CatchHandler @ 00b25125 */
      STRINGS::StringConvertToUTF8((wstring_conflict *)local_1d8);
                    /* try { // try from 00b24953 to 00b24957 has its CatchHandler @ 00b25115 */
      CEGUI::String::String(local_918,local_1d8[0]);
                    /* try { // try from 00b2495f to 00b24963 has its CatchHandler @ 00b25105 */
      CEGUI::Window::setText((String *)param_3[10]);
                    /* try { // try from 00b24967 to 00b2496b has its CatchHandler @ 00b25115 */
      CEGUI::String::~String(local_918);
                    /* try { // try from 00b2496f to 00b24973 has its CatchHandler @ 00b25125 */
      std::string::~string((string *)local_1d8);
                    /* try { // try from 00b24977 to 00b2497b has its CatchHandler @ 00b25135 */
      std::wstring::~wstring(local_1c8);
    }
    CSoundBank::playSample((CSoundBank *)param_3[0x17],0x16,(SceneNode *)0x0,0.0,0.0,false);
    (**(code **)(*(long *)param_3[0x14] + 0x50))((long *)param_3[0x14],1);
                    /* try { // try from 00b24645 to 00b24649 has its CatchHandler @ 00b250c6 */
    std::string::string((string *)local_1e8,"CLOSE",&local_33);
                    /* try { // try from 00b24654 to 00b24658 has its CatchHandler @ 00b250c4 */
    cVar2 = CGenericModel::animationPlaying((CGenericModel *)param_3[0x14],(string *)local_1e8);
    if ((allocator *)(local_1e8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_1e8[0] + -8);
      iVar3 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar3 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_1e8[0] + -0x18));
      }
    }
    if (cVar2 == '\0') {
                    /* try { // try from 00b24870 to 00b24874 has its CatchHandler @ 00b25285 */
      std::string::string(local_208,"OPEN",&local_35);
                    /* try { // try from 00b24891 to 00b24895 has its CatchHandler @ 00b25275 */
      CGenericModel::playAnimation
                ((CGenericModel *)param_3[0x14],local_208,false,DAT_00fa4824,DAT_00fa8760);
                    /* try { // try from 00b24899 to 00b2489d has its CatchHandler @ 00b25285 */
      std::string::~string(local_208);
    }
    else {
                    /* try { // try from 00b24692 to 00b24696 has its CatchHandler @ 00b250d2 */
      std::string::string(local_1f8,"OPEN",&local_34);
                    /* try { // try from 00b246bb to 00b246bf has its CatchHandler @ 00b250c2 */
      CGenericModel::blendAnimation
                ((CGenericModel *)param_3[0x14],local_1f8,false,DAT_00fa480c,DAT_00fa4824,
                 DAT_00fa8760);
                    /* try { // try from 00b246c3 to 00b246c7 has its CatchHandler @ 00b250d2 */
      std::string::~string(local_1f8);
    }
                    /* try { // try from 00b246e0 to 00b246e4 has its CatchHandler @ 00b250bf */
    std::string::string((string *)local_218,"IDLE",&local_36);
                    /* try { // try from 00b24704 to 00b24708 has its CatchHandler @ 00b250b2 */
    CGenericModel::queueBlendAnimation
              ((CGenericModel *)param_3[0x14],(string *)local_218,true,DAT_00fa480c,DAT_00fa47fc);
    if ((allocator *)(local_218[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_218[0] + -8);
      iVar3 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar3 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_218[0] + -0x18));
      }
    }
    CEGUI::Window::addChildWindow((Window *)param_3[3]);
    CEGUI::Window::moveToBack();
    CGameUI::queueTip((CGameUI *)param_3[0x10],0xd);
  }
  else if (param_4 == '\0') {
    if ((param_3[0xc] != 0) &&
       (pCVar4 = (CItem *)CInventory::getEquipmentInSlot(*(CInventory **)(param_3[0xc] + 0x490),0xe)
       , pCVar4 != (CItem *)0x0)) {
      CInventory::removeEquipment(*(CInventory **)(param_3[0xc] + 0x490),(CEquipment *)pCVar4);
      lVar5 = CInventory::pickupEquipment
                        (*(CInventory **)(param_3[0xc] + 0x490),(CEquipment *)pCVar4,true);
      if (lVar5 == 0) {
        local_238 = CPositionableObject::getPosition((CPositionableObject *)param_3[0xc],true);
        this = (CLevel *)0x0;
        if (*(long *)(param_3[0xc] + 0x68) != 0) {
          this = *(CLevel **)(*(long *)(param_3[0xc] + 0x68) + 0x18);
        }
        local_230 = param_2;
        CLevel::addItem(this,pCVar4,(Vector3 *)&local_238,true);
        (**(code **)(*(long *)pCVar4 + 0x360))(pCVar4);
      }
    }
    CSoundBank::playSample((CSoundBank *)param_3[0x17],0x42,(SceneNode *)0x0,0.0,0.0,false);
                    /* try { // try from 00b24487 to 00b2448b has its CatchHandler @ 00b25295 */
    std::string::string((string *)local_228,"CLOSE",&local_37);
                    /* try { // try from 00b244b0 to 00b244b4 has its CatchHandler @ 00b25225 */
    CGenericModel::blendAnimation
              ((CGenericModel *)param_3[0x14],(string *)local_228,false,DAT_00fa480c,DAT_00fa4824,
               DAT_00fa8760);
    if ((allocator *)(local_228[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_228[0] + -8);
      iVar3 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar3 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_228[0] + -0x18));
      }
    }
    *(undefined1 *)((long)param_3 + 0x71) = 0;
    *(undefined1 *)(param_3 + 0xe) = 0;
    return;
  }
  *(char *)(param_3 + 0xe) = param_4;
  (**(code **)(*param_3 + 0x48))(param_3);
  return;
}

/* address=00b252c0
   symbol=CEnchantMenu::mapEventHandlers */

/* CEnchantMenu::mapEventHandlers(CEGUI::Window*) */

void __thiscall CEnchantMenu::mapEventHandlers(CEnchantMenu *this,Window *param_1)

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
                    /* try { // try from 00b25386 to 00b25403 has its CatchHandler @ 00b2566c */
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
                    /* try { // try from 00b25560 to 00b255de has its CatchHandler @ 00b2566c */
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
                    /* try { // try from 00b255eb to 00b255ef has its CatchHandler @ 00b25626 */
    CEGUI::String::~String((String *)local_268);
                    /* try { // try from 00b255f8 to 00b255fc has its CatchHandler @ 00b2565f */
    CEGUI::String::~String((String *)&local_1b8);
  }
                    /* try { // try from 00b25412 to 00b2544e has its CatchHandler @ 00b2564d */
  CEGUI::String::~String((String *)&local_108);
  if (bVar11) {
    CEGUI::Window::setWantsMultiClickEvents(SUB81(param_1,0));
    pcVar3 = *(code **)(*(long *)(param_1 + 0x38) + 0x10);
    local_48[0] = operator_new(0x20);
    local_48[0][3] = this;
    *local_48[0] = &PTR__MemberFunctionSlot_00fef410;
    local_48[0][2] = 0;
    local_48[0][1] = 0x59;
                    /* try { // try from 00b2548e to 00b254c3 has its CatchHandler @ 00b25652 */
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
                    /* try { // try from 00b254f4 to 00b254f8 has its CatchHandler @ 00b2564d */
    CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_48);
  }
  return;
}

/* address=00b26290
   symbol=CEnchantMenu::performInteraction */

/* WARNING: Removing unreachable block (ram,0x00b29539) */
/* WARNING: Removing unreachable block (ram,0x00b294b5) */
/* WARNING: Removing unreachable block (ram,0x00b2905a) */
/* WARNING: Removing unreachable block (ram,0x00b2901a) */
/* WARNING: Removing unreachable block (ram,0x00b28ffa) */
/* WARNING: Removing unreachable block (ram,0x00b2903a) */
/* WARNING: Removing unreachable block (ram,0x00b2904a) */
/* WARNING: Removing unreachable block (ram,0x00b2900a) */
/* WARNING: Removing unreachable block (ram,0x00b2902a) */
/* WARNING: Removing unreachable block (ram,0x00b2906d) */
/* WARNING: Removing unreachable block (ram,0x00b294ef) */
/* WARNING: Removing unreachable block (ram,0x00b29549) */
/* WARNING: Removing unreachable block (ram,0x00b294fd) */
/* CEnchantMenu::performInteraction() */

void __thiscall CEnchantMenu::performInteraction(CEnchantMenu *this)

{
  int *piVar1;
  undefined8 *puVar2;
  CBaseUnit *this_00;
  bool bVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  CEquipment *this_01;
  undefined8 uVar8;
  CAchievements *pCVar9;
  CAchievement *pCVar10;
  long *plVar11;
  long lVar12;
  uint uVar13;
  SceneNode *pSVar14;
  CLevel *pCVar15;
  CSoundBank *this_02;
  float fVar16;
  float fVar17;
  float fVar18;
  undefined4 uVar19;
  undefined8 local_7c8;
  undefined4 local_7c0;
  undefined8 local_7b8;
  undefined4 local_7b0;
  undefined8 local_7a8;
  float local_7a0;
  undefined8 local_798;
  float local_790;
  wstring_conflict local_788 [16];
  wstring_conflict local_778 [16];
  wstring_conflict local_768 [16];
  wstring_conflict local_758 [16];
  wstring_conflict local_748 [16];
  wstring_conflict local_738 [16];
  wstring_conflict local_728 [16];
  wstring_conflict local_718 [16];
  wstring_conflict local_708 [16];
  wstring_conflict local_6f8 [16];
  wstring_conflict local_6e8 [16];
  wstring_conflict local_6d8 [16];
  wstring_conflict local_6c8 [16];
  wstring_conflict local_6b8 [16];
  wstring_conflict local_6a8 [16];
  wstring_conflict local_698 [16];
  wstring_conflict local_688 [16];
  wstring_conflict local_678 [16];
  wstring_conflict local_668 [16];
  wstring_conflict local_658 [16];
  wstring_conflict local_648 [16];
  wstring_conflict local_638 [16];
  wstring_conflict local_628 [16];
  wstring_conflict local_618 [16];
  wstring_conflict local_608 [16];
  wstring_conflict local_5f8 [16];
  wstring_conflict local_5e8 [16];
  wstring_conflict local_5d8 [16];
  wstring_conflict local_5c8 [16];
  wstring_conflict local_5b8 [16];
  wstring_conflict local_5a8 [16];
  wstring_conflict local_598 [16];
  wstring_conflict local_588 [16];
  wstring_conflict local_578 [16];
  wstring_conflict local_568 [16];
  wstring_conflict local_558 [16];
  wstring_conflict local_548 [16];
  wstring_conflict local_538 [16];
  wstring_conflict local_528 [16];
  wstring_conflict local_518 [16];
  wstring_conflict local_508 [16];
  wstring_conflict local_4f8 [16];
  wstring_conflict local_4e8 [16];
  wstring_conflict local_4d8 [16];
  wstring_conflict local_4c8 [16];
  wstring_conflict local_4b8 [16];
  wstring_conflict local_4a8 [16];
  wstring_conflict local_498 [16];
  wstring_conflict local_488 [16];
  wstring_conflict local_478 [16];
  wstring_conflict local_468 [16];
  wstring_conflict local_458 [16];
  wstring_conflict local_448 [16];
  wstring_conflict local_438 [16];
  wstring_conflict local_428 [16];
  wstring_conflict local_418 [16];
  wstring_conflict local_408 [16];
  wstring_conflict local_3f8 [16];
  wstring_conflict local_3e8 [16];
  wstring_conflict local_3d8 [16];
  wstring_conflict local_3c8 [16];
  wstring_conflict local_3b8 [16];
  wstring_conflict local_3a8 [16];
  wstring_conflict local_398 [16];
  wstring_conflict local_388 [16];
  wstring_conflict local_378 [16];
  wstring_conflict local_368 [16];
  wstring_conflict local_358 [16];
  wstring_conflict local_348 [16];
  wstring_conflict local_338 [16];
  wstring_conflict local_328 [16];
  wstring_conflict local_318 [16];
  wstring_conflict local_308 [16];
  wstring_conflict local_2f8 [16];
  wstring_conflict local_2e8 [16];
  wstring_conflict local_2d8 [16];
  wstring_conflict local_2c8 [16];
  wstring_conflict local_2b8 [16];
  wstring_conflict local_2a8 [16];
  wstring_conflict local_298 [16];
  wstring_conflict local_288 [16];
  wstring_conflict local_278 [16];
  wstring_conflict local_268 [16];
  wstring_conflict local_258 [16];
  wstring_conflict local_248 [16];
  wstring_conflict local_238 [16];
  wstring_conflict local_228 [16];
  wstring_conflict local_218 [16];
  wstring_conflict local_208 [16];
  wstring_conflict local_1f8 [16];
  wstring_conflict local_1e8 [16];
  wstring_conflict local_1d8 [16];
  wstring_conflict local_1c8 [16];
  wstring_conflict local_1b8 [16];
  wstring_conflict local_1a8 [16];
  wstring_conflict local_198 [16];
  wstring_conflict local_188 [16];
  wstring_conflict local_178 [16];
  wstring_conflict local_168 [16];
  wstring_conflict local_158 [16];
  wstring_conflict local_148 [16];
  wstring_conflict local_138 [16];
  undefined4 *local_128 [2];
  long local_118 [2];
  long local_108 [2];
  long local_f8 [2];
  long local_e8 [2];
  long local_d8 [2];
  long local_c8 [2];
  long local_b8 [2];
  long local_a8 [2];
  long local_98 [2];
  long local_88 [2];
  long local_78 [2];
  long local_68 [3];
  allocator local_4c;
  allocator local_4b;
  allocator local_4a;
  allocator local_49;
  allocator local_48;
  allocator local_47;
  allocator local_46;
  allocator local_45;
  allocator local_44;
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

  if ((performInteraction()::g_AncientRites == '\0') && (iVar5 = __cxa_guard_acquire(), iVar5 != 0))
  {
    performInteraction()::g_AncientRites = &DAT_01424558;
    __cxa_guard_release(&performInteraction()::g_AncientRites);
    __cxa_atexit(std::wstring::~wstring,&performInteraction()::g_AncientRites,&__dso_handle);
  }
  if (*(long *)(performInteraction()::g_AncientRites + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_68);
                    /* try { // try from 00b26ff5 to 00b26ff9 has its CatchHandler @ 00b29038 */
    std::wstring::assign((wstring_conflict *)&performInteraction()::g_AncientRites);
    if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_68[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
      }
    }
  }
  if ((performInteraction()::g_NothingHappens == '\0') &&
     (iVar5 = __cxa_guard_acquire(), iVar5 != 0)) {
    performInteraction()::g_NothingHappens = &DAT_01424558;
    __cxa_guard_release(&performInteraction()::g_NothingHappens);
    __cxa_atexit(std::wstring::~wstring,&performInteraction()::g_NothingHappens,&__dso_handle);
  }
  if (*(long *)(performInteraction()::g_NothingHappens + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_78);
                    /* try { // try from 00b26f35 to 00b26f39 has its CatchHandler @ 00b29028 */
    std::wstring::assign((wstring_conflict *)&performInteraction()::g_NothingHappens);
    if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_78[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
      }
    }
  }
  if ((performInteraction()::g_AddedSockets == '\0') && (iVar5 = __cxa_guard_acquire(), iVar5 != 0))
  {
    performInteraction()::g_AddedSockets = &DAT_01424558;
    __cxa_guard_release(&performInteraction()::g_AddedSockets);
    __cxa_atexit(std::wstring::~wstring,&performInteraction()::g_AddedSockets,&__dso_handle);
  }
  if (*(long *)(performInteraction()::g_AddedSockets + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_88);
                    /* try { // try from 00b26e75 to 00b26e79 has its CatchHandler @ 00b28fe7 */
    std::wstring::assign((wstring_conflict *)&performInteraction()::g_AddedSockets);
    if ((allocator *)(local_88[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_88[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
      }
    }
  }
  if ((performInteraction()::g_AddedEnchantments == '\0') &&
     (iVar5 = __cxa_guard_acquire(), iVar5 != 0)) {
    performInteraction()::g_AddedEnchantments = &DAT_01424558;
    __cxa_guard_release(&performInteraction()::g_AddedEnchantments);
    __cxa_atexit(std::wstring::~wstring,&performInteraction()::g_AddedEnchantments,&__dso_handle);
  }
  if (*(long *)(performInteraction()::g_AddedEnchantments + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_98);
                    /* try { // try from 00b26db5 to 00b26db9 has its CatchHandler @ 00b2912e */
    std::wstring::assign((wstring_conflict *)&performInteraction()::g_AddedEnchantments);
    if ((allocator *)(local_98[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_98[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
      }
    }
  }
  if ((performInteraction()::g_RemovedEnchantments == '\0') &&
     (iVar5 = __cxa_guard_acquire(), iVar5 != 0)) {
    performInteraction()::g_RemovedEnchantments = &DAT_01424558;
    __cxa_guard_release(&performInteraction()::g_RemovedEnchantments);
    __cxa_atexit(std::wstring::~wstring,&performInteraction()::g_RemovedEnchantments,&__dso_handle);
  }
  if (*(long *)(performInteraction()::g_RemovedEnchantments + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_a8);
                    /* try { // try from 00b26cf5 to 00b26cf9 has its CatchHandler @ 00b29018 */
    std::wstring::assign((wstring_conflict *)&performInteraction()::g_RemovedEnchantments);
    if ((allocator *)(local_a8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_a8[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
      }
    }
  }
  if ((performInteraction()::g_YouPlunge == '\0') && (iVar5 = __cxa_guard_acquire(), iVar5 != 0)) {
    performInteraction()::g_YouPlunge = &DAT_01424558;
    __cxa_guard_release(&performInteraction()::g_YouPlunge);
    __cxa_atexit(std::wstring::~wstring,&performInteraction()::g_YouPlunge,&__dso_handle);
  }
  if (*(long *)(performInteraction()::g_YouPlunge + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_b8);
                    /* try { // try from 00b26c35 to 00b26c39 has its CatchHandler @ 00b29008 */
    std::wstring::assign((wstring_conflict *)&performInteraction()::g_YouPlunge);
    if ((allocator *)(local_b8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_b8[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
      }
    }
  }
  if ((performInteraction()::g_IntoTheLight == '\0') && (iVar5 = __cxa_guard_acquire(), iVar5 != 0))
  {
    performInteraction()::g_IntoTheLight = &DAT_01424558;
    __cxa_guard_release(&performInteraction()::g_IntoTheLight);
    __cxa_atexit(std::wstring::~wstring,&performInteraction()::g_IntoTheLight,&__dso_handle);
  }
  if (*(long *)(performInteraction()::g_IntoTheLight + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_c8);
                    /* try { // try from 00b26b75 to 00b26b79 has its CatchHandler @ 00b29058 */
    std::wstring::assign((wstring_conflict *)&performInteraction()::g_IntoTheLight);
    if ((allocator *)(local_c8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_c8[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
      }
    }
  }
  if ((performInteraction()::g_TheGemsWithin == '\0') && (iVar5 = __cxa_guard_acquire(), iVar5 != 0)
     ) {
    performInteraction()::g_TheGemsWithin = &DAT_01424558;
    __cxa_guard_release(&performInteraction()::g_TheGemsWithin);
    __cxa_atexit(std::wstring::~wstring,&performInteraction()::g_TheGemsWithin,&__dso_handle);
  }
  if (*(long *)(performInteraction()::g_TheGemsWithin + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_d8);
                    /* try { // try from 00b26ab5 to 00b26ab9 has its CatchHandler @ 00b29048 */
    std::wstring::assign((wstring_conflict *)&performInteraction()::g_TheGemsWithin);
    if ((allocator *)(local_d8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_d8[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
      }
    }
  }
  if ((performInteraction()::g_AreDestroyed == '\0') && (iVar5 = __cxa_guard_acquire(), iVar5 != 0))
  {
    performInteraction()::g_AreDestroyed = &DAT_01424558;
    __cxa_guard_release(&performInteraction()::g_AreDestroyed);
    __cxa_atexit(std::wstring::~wstring,&performInteraction()::g_AreDestroyed,&__dso_handle);
  }
  if (*(long *)(performInteraction()::g_AreDestroyed + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_e8);
                    /* try { // try from 00b269f5 to 00b269f9 has its CatchHandler @ 00b294ad */
    std::wstring::assign((wstring_conflict *)&performInteraction()::g_AreDestroyed);
    if ((allocator *)(local_e8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_e8[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
      }
    }
  }
  if ((performInteraction()::g_GemsRecovered == '\0') && (iVar5 = __cxa_guard_acquire(), iVar5 != 0)
     ) {
    performInteraction()::g_GemsRecovered = &DAT_01424558;
    __cxa_guard_release(&performInteraction()::g_GemsRecovered);
    __cxa_atexit(std::wstring::~wstring,&performInteraction()::g_GemsRecovered,&__dso_handle);
  }
  if (*(long *)(performInteraction()::g_GemsRecovered + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_f8);
                    /* try { // try from 00b26935 to 00b26939 has its CatchHandler @ 00b29068 */
    std::wstring::assign((wstring_conflict *)&performInteraction()::g_GemsRecovered);
    if ((allocator *)(local_f8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_f8[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
      }
    }
  }
  if ((performInteraction()::g_Sockets == '\0') && (iVar5 = __cxa_guard_acquire(), iVar5 != 0)) {
    performInteraction()::g_Sockets = &DAT_01424558;
    __cxa_guard_release(&performInteraction()::g_Sockets);
    __cxa_atexit(std::wstring::~wstring,&performInteraction()::g_Sockets,&__dso_handle);
  }
  if (*(long *)(performInteraction()::g_Sockets + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_108);
                    /* try { // try from 00b26875 to 00b26879 has its CatchHandler @ 00b29534 */
    std::wstring::assign((wstring_conflict *)&performInteraction()::g_Sockets);
    if ((allocator *)(local_108[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_108[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_108[0] + -0x18));
      }
    }
  }
  if ((performInteraction()::g_Enchant == '\0') && (iVar5 = __cxa_guard_acquire(), iVar5 != 0)) {
    performInteraction()::g_Enchant = &DAT_01424558;
    __cxa_guard_release(&performInteraction()::g_Enchant);
    __cxa_atexit(std::wstring::~wstring,&performInteraction()::g_Enchant,&__dso_handle);
  }
  if (*(long *)(performInteraction()::g_Enchant + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_118);
                    /* try { // try from 00b26439 to 00b2643d has its CatchHandler @ 00b29544 */
    std::wstring::assign((wstring_conflict *)&performInteraction()::g_Enchant);
    if ((allocator *)(local_118[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_118[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_118[0] + -0x18));
      }
    }
  }
  iVar5 = UTILITIES::randomIntegerBetweenVolatile(0,1);
  local_128[0] = &DAT_01424558;
  switch(*(undefined4 *)(this + 0x10c)) {
  case 0x15:
                    /* try { // try from 00b270a8 to 00b2710b has its CatchHandler @ 00b29129 */
    this_01 = (CEquipment *)
              CInventory::getEquipmentInSlot(*(CInventory **)(*(long *)(this + 0x60) + 0x490),0xe);
    if ((this_01 == (CEquipment *)0x0) ||
       ((((cVar4 = CBaseUnit::ISA((CBaseUnit *)this_01,8), cVar4 == '\0' &&
          (cVar4 = CBaseUnit::ISA((CBaseUnit *)this_01,0xd), cVar4 == '\0')) &&
         (cVar4 = CBaseUnit::ISA((CBaseUnit *)this_01,0x11), cVar4 == '\0')) &&
        (cVar4 = CBaseUnit::ISA((CBaseUnit *)this_01,0x18), cVar4 == '\0')))) goto LAB_00b28450;
    (**(code **)(*(long *)this_01 + 0x2a0))(this_01);
    std::operator+(local_138,(wchar_t *)&performInteraction()::g_AncientRites);
                    /* try { // try from 00b27127 to 00b2712b has its CatchHandler @ 00b29114 */
    std::operator+(local_148,local_138);
                    /* try { // try from 00b27149 to 00b2714d has its CatchHandler @ 00b29173 */
    std::operator+(local_158,(wchar_t *)local_148);
                    /* try { // try from 00b2716e to 00b27172 has its CatchHandler @ 00b2916e */
    std::operator+(local_168,local_158);
                    /* try { // try from 00b2718e to 00b27192 has its CatchHandler @ 00b29169 */
    std::operator+(local_178,(wchar_t *)local_168);
                    /* try { // try from 00b271a1 to 00b271a5 has its CatchHandler @ 00b29135 */
    std::wstring::assign((wstring_conflict *)local_128);
                    /* try { // try from 00b271a9 to 00b271ad has its CatchHandler @ 00b29169 */
    std::wstring::~wstring(local_178);
                    /* try { // try from 00b271b1 to 00b271b5 has its CatchHandler @ 00b2916e */
    std::wstring::~wstring(local_168);
                    /* try { // try from 00b271be to 00b271c2 has its CatchHandler @ 00b29173 */
    std::wstring::~wstring(local_158);
                    /* try { // try from 00b271cb to 00b271cf has its CatchHandler @ 00b29114 */
    std::wstring::~wstring(local_148);
                    /* try { // try from 00b271d8 to 00b271dc has its CatchHandler @ 00b29129 */
    std::wstring::~wstring(local_138);
                    /* try { // try from 00b271f2 to 00b271f6 has its CatchHandler @ 00b293ca */
    std::wstring::wstring(local_1a8,L"\n",&local_3a);
                    /* try { // try from 00b2720c to 00b27210 has its CatchHandler @ 00b293c2 */
    std::wstring::wstring(local_198,L"\\n",local_39);
                    /* try { // try from 00b2721f to 00b27223 has its CatchHandler @ 00b293ba */
    std::wstring::wstring(local_188,(wstring_conflict *)local_128);
                    /* try { // try from 00b27242 to 00b27246 has its CatchHandler @ 00b293b2 */
    STRINGS::replaceWString((STRINGS *)local_1b8,local_188,local_198);
                    /* try { // try from 00b2724d to 00b27251 has its CatchHandler @ 00b2929e */
    std::wstring::assign((wstring_conflict *)local_128);
                    /* try { // try from 00b27255 to 00b27259 has its CatchHandler @ 00b293b2 */
    std::wstring::~wstring(local_1b8);
                    /* try { // try from 00b2725d to 00b27261 has its CatchHandler @ 00b293ba */
    std::wstring::~wstring(local_188);
                    /* try { // try from 00b2726a to 00b2726e has its CatchHandler @ 00b293c2 */
    std::wstring::~wstring(local_198);
                    /* try { // try from 00b27277 to 00b2727b has its CatchHandler @ 00b293ca */
    std::wstring::~wstring(local_1a8);
                    /* try { // try from 00b2727f to 00b27386 has its CatchHandler @ 00b29129 */
    iVar6 = CEquipment::enchantPrice(this_01);
    if (iVar6 <= *(int *)(*(long *)(this + 0x60) + 0x444)) {
      iVar6 = CEquipment::enchantPrice(this_01);
      CCharacter::giveGold(*(CCharacter **)(this + 0x60),-iVar6);
      CSoundBank::playSample
                (*(CSoundBank **)(this + 0xb8),0x17,*(SceneNode **)(*(long *)(this + 0x60) + 0x58),
                 0.0,0.0,false);
      uVar13 = *(uint *)(this_01 + 0x344);
      lVar12 = CGameGlobals::getSingleton();
      fVar18 = *(float *)(lVar12 + 0x8c);
      lVar12 = CGameGlobals::getSingleton();
      fVar16 = (float)uVar13 * fVar18 + *(float *)(lVar12 + 0x70);
      lVar12 = CGameGlobals::getSingleton();
      fVar18 = *(float *)(lVar12 + 0x74);
      if (fVar16 <= *(float *)(lVar12 + 0x74)) {
        fVar18 = fVar16;
      }
      fVar17 = (float)UTILITIES::randomBetweenVolatile(0.0,DAT_00fa871c);
      fVar16 = DAT_00fa86e0;
      if ((fVar18 * DAT_00fa86e0 < fVar17) || (*(long *)(this_01 + 0x1b8) == 0)) {
        iVar6 = *(int *)(this_01 + 0x3e0);
        iVar7 = CEquipment::getMaxSockets(this_01);
        if (iVar6 < iVar7) {
          fVar18 = (float)UTILITIES::randomBetweenVolatile(0.0,DAT_00fa871c);
          lVar12 = CGameGlobals::getSingleton();
          if (fVar16 * *(float *)(lVar12 + 100) <= fVar18) goto LAB_00b28862;
          (**(code **)(*(long *)this_01 + 0x2a0))(this_01);
          std::operator+(local_258,(wchar_t *)&performInteraction()::g_AncientRites);
                    /* try { // try from 00b28c53 to 00b28c57 has its CatchHandler @ 00b28eb9 */
          std::operator+(local_268,local_258);
                    /* try { // try from 00b28c70 to 00b28c74 has its CatchHandler @ 00b28eb4 */
          std::operator+(local_278,(wchar_t *)local_268);
                    /* try { // try from 00b28c88 to 00b28c8c has its CatchHandler @ 00b28eaf */
          std::operator+(local_288,local_278);
                    /* try { // try from 00b28ca0 to 00b28ca4 has its CatchHandler @ 00b28eaa */
          std::operator+(local_298,(wchar_t *)local_288);
                    /* try { // try from 00b28cab to 00b28caf has its CatchHandler @ 00b28e73 */
          std::wstring::assign((wstring_conflict *)local_128);
                    /* try { // try from 00b28cb3 to 00b28cb7 has its CatchHandler @ 00b28eaa */
          std::wstring::~wstring(local_298);
                    /* try { // try from 00b28cbb to 00b28cbf has its CatchHandler @ 00b28eaf */
          std::wstring::~wstring(local_288);
                    /* try { // try from 00b28cc3 to 00b28cc7 has its CatchHandler @ 00b28eb4 */
          std::wstring::~wstring(local_278);
                    /* try { // try from 00b28cd0 to 00b28cd4 has its CatchHandler @ 00b28eb9 */
          std::wstring::~wstring(local_268);
                    /* try { // try from 00b28cdd to 00b28ce1 has its CatchHandler @ 00b29129 */
          std::wstring::~wstring(local_258);
                    /* try { // try from 00b28cf7 to 00b28cfb has its CatchHandler @ 00b28e6e */
          std::wstring::wstring(local_2c8,L"\n",&local_3e);
                    /* try { // try from 00b28d14 to 00b28d18 has its CatchHandler @ 00b28e69 */
          std::wstring::wstring(local_2b8,L"\\n",&local_3d);
                    /* try { // try from 00b28d27 to 00b28d2b has its CatchHandler @ 00b28e64 */
          std::wstring::wstring(local_2a8,(wstring_conflict *)local_128);
                    /* try { // try from 00b28d45 to 00b28d49 has its CatchHandler @ 00b28e34 */
          STRINGS::replaceWString((STRINGS *)local_2d8,local_2a8,local_2b8);
                    /* try { // try from 00b28d50 to 00b28d54 has its CatchHandler @ 00b28ed0 */
          std::wstring::assign((wstring_conflict *)local_128);
                    /* try { // try from 00b28d58 to 00b28d5c has its CatchHandler @ 00b28e34 */
          std::wstring::~wstring(local_2d8);
                    /* try { // try from 00b28d60 to 00b28d64 has its CatchHandler @ 00b28e64 */
          std::wstring::~wstring(local_2a8);
                    /* try { // try from 00b28d68 to 00b28d6c has its CatchHandler @ 00b28e69 */
          std::wstring::~wstring(local_2b8);
                    /* try { // try from 00b28d75 to 00b28d79 has its CatchHandler @ 00b28e6e */
          std::wstring::~wstring(local_2c8);
          fVar18 = 0.0;
                    /* try { // try from 00b28d96 to 00b28e2e has its CatchHandler @ 00b29129 */
          CSoundBank::playSample
                    (*(CSoundBank **)(this + 0xb8),0x24,
                     *(SceneNode **)(*(long *)(this + 0x60) + 0x58),0.0,0.0,false);
          if (*(CSoundBank **)(*(long *)(this + 0x60) + 0x298) != (CSoundBank *)0x0) {
            fVar18 = DAT_00fa47fc;
            CSoundBank::queueGlobalSample
                      (*(CSoundBank **)(*(long *)(this + 0x60) + 0x298),0x3f,DAT_00fa47fc,
                       DAT_00fa47fc);
          }
          CEquipment::addSockets(this_01);
        }
        else {
LAB_00b28862:
          fVar18 = (float)UTILITIES::randomBetweenVolatile(0.0,DAT_00fa871c);
          lVar12 = CGameGlobals::getSingleton();
          if (fVar16 * *(float *)(lVar12 + 0x68) < fVar18) {
            lVar12 = *(long *)(this + 0x60);
            if (*(CSoundBank **)(lVar12 + 0x298) != (CSoundBank *)0x0) {
              CSoundBank::queueGlobalSample
                        (*(CSoundBank **)(lVar12 + 0x298),0x40,DAT_00fa47fc,DAT_00fa47fc);
              lVar12 = *(long *)(this + 0x60);
            }
            fVar18 = 0.0;
            CSoundBank::playSample
                      (*(CSoundBank **)(this + 0xb8),0x23,*(SceneNode **)(lVar12 + 0x58),0.0,0.0,
                       false);
            bVar3 = false;
            goto LAB_00b2753c;
          }
          (**(code **)(*(long *)this_01 + 0x2a0))(this_01);
          std::operator+(local_2e8,(wchar_t *)&performInteraction()::g_AncientRites);
                    /* try { // try from 00b28a3a to 00b28a3e has its CatchHandler @ 00b294a8 */
          std::operator+(local_2f8,local_2e8);
                    /* try { // try from 00b28a54 to 00b28a58 has its CatchHandler @ 00b294a3 */
          std::operator+(local_308,(wchar_t *)local_2f8);
                    /* try { // try from 00b28a71 to 00b28a75 has its CatchHandler @ 00b2949e */
          std::operator+(local_318,local_308);
                    /* try { // try from 00b28a89 to 00b28a8d has its CatchHandler @ 00b29499 */
          std::operator+(local_328,(wchar_t *)local_318);
                    /* try { // try from 00b28a94 to 00b28a98 has its CatchHandler @ 00b2945a */
          std::wstring::assign((wstring_conflict *)local_128);
                    /* try { // try from 00b28a9c to 00b28aa0 has its CatchHandler @ 00b29499 */
          std::wstring::~wstring(local_328);
                    /* try { // try from 00b28aa4 to 00b28aa8 has its CatchHandler @ 00b2949e */
          std::wstring::~wstring(local_318);
                    /* try { // try from 00b28ab1 to 00b28ab5 has its CatchHandler @ 00b294a3 */
          std::wstring::~wstring(local_308);
                    /* try { // try from 00b28abe to 00b28ac2 has its CatchHandler @ 00b294a8 */
          std::wstring::~wstring(local_2f8);
                    /* try { // try from 00b28acb to 00b28acf has its CatchHandler @ 00b29129 */
          std::wstring::~wstring(local_2e8);
                    /* try { // try from 00b28ae5 to 00b28ae9 has its CatchHandler @ 00b29455 */
          std::wstring::wstring(local_358,L"\n",&local_40);
                    /* try { // try from 00b28aff to 00b28b03 has its CatchHandler @ 00b2944c */
          std::wstring::wstring(local_348,L"\\n",&local_3f);
                    /* try { // try from 00b28b12 to 00b28b16 has its CatchHandler @ 00b29444 */
          std::wstring::wstring(local_338,(wstring_conflict *)local_128);
                    /* try { // try from 00b28b35 to 00b28b39 has its CatchHandler @ 00b29289 */
          STRINGS::replaceWString((STRINGS *)local_368,local_338,local_348);
                    /* try { // try from 00b28b40 to 00b28b44 has its CatchHandler @ 00b29257 */
          std::wstring::assign((wstring_conflict *)local_128);
                    /* try { // try from 00b28b48 to 00b28b4c has its CatchHandler @ 00b29289 */
          std::wstring::~wstring(local_368);
                    /* try { // try from 00b28b50 to 00b28b54 has its CatchHandler @ 00b29444 */
          std::wstring::~wstring(local_338);
                    /* try { // try from 00b28b5d to 00b28b61 has its CatchHandler @ 00b2944c */
          std::wstring::~wstring(local_348);
                    /* try { // try from 00b28b6a to 00b28b6e has its CatchHandler @ 00b29455 */
          std::wstring::~wstring(local_358);
          fVar18 = 0.0;
                    /* try { // try from 00b28b8b to 00b28c3f has its CatchHandler @ 00b29129 */
          CSoundBank::playSample
                    (*(CSoundBank **)(this + 0xb8),0x24,
                     *(SceneNode **)(*(long *)(this + 0x60) + 0x58),0.0,0.0,false);
          if (*(CSoundBank **)(*(long *)(this + 0x60) + 0x298) != (CSoundBank *)0x0) {
            fVar18 = DAT_00fa47fc;
            CSoundBank::queueGlobalSample
                      (*(CSoundBank **)(*(long *)(this + 0x60) + 0x298),0x3f,DAT_00fa47fc,
                       DAT_00fa47fc);
          }
          iVar6 = 4;
          if (3 < *(uint *)(this_01 + 0x274)) {
            iVar6 = *(int *)(this_01 + 0x274);
          }
          CEquipment::addEnchant(this_01,iVar6,iVar5 + 1,iVar5 + 2);
        }
        *(int *)(this_01 + 0x344) = *(int *)(this_01 + 0x344) + 1;
        bVar3 = false;
      }
      else {
        (**(code **)(*(long *)this_01 + 0x2a0))(this_01);
        std::operator+(local_1c8,(wchar_t *)&performInteraction()::g_AncientRites);
                    /* try { // try from 00b2739a to 00b2739e has its CatchHandler @ 00b2943f */
        std::operator+(local_1d8,local_1c8);
                    /* try { // try from 00b273b7 to 00b273bb has its CatchHandler @ 00b2943a */
        std::operator+(local_1e8,(wchar_t *)local_1d8);
                    /* try { // try from 00b273cf to 00b273d3 has its CatchHandler @ 00b29435 */
        std::operator+(local_1f8,local_1e8);
                    /* try { // try from 00b273e7 to 00b273eb has its CatchHandler @ 00b29430 */
        std::operator+(local_208,(wchar_t *)local_1f8);
                    /* try { // try from 00b273f2 to 00b273f6 has its CatchHandler @ 00b293f6 */
        std::wstring::assign((wstring_conflict *)local_128);
                    /* try { // try from 00b273fa to 00b273fe has its CatchHandler @ 00b29430 */
        std::wstring::~wstring(local_208);
                    /* try { // try from 00b27402 to 00b27406 has its CatchHandler @ 00b29435 */
        std::wstring::~wstring(local_1f8);
                    /* try { // try from 00b2740a to 00b2740e has its CatchHandler @ 00b2943a */
        std::wstring::~wstring(local_1e8);
                    /* try { // try from 00b27417 to 00b2741b has its CatchHandler @ 00b2943f */
        std::wstring::~wstring(local_1d8);
                    /* try { // try from 00b27424 to 00b27428 has its CatchHandler @ 00b29129 */
        std::wstring::~wstring(local_1c8);
                    /* try { // try from 00b2743e to 00b27442 has its CatchHandler @ 00b293f1 */
        std::wstring::wstring(local_238,L"\n",&local_3c);
                    /* try { // try from 00b2745b to 00b2745f has its CatchHandler @ 00b293ec */
        std::wstring::wstring(local_228,L"\\n",&local_3b);
                    /* try { // try from 00b2746e to 00b27472 has its CatchHandler @ 00b293cf */
        std::wstring::wstring(local_218,(wstring_conflict *)local_128);
                    /* try { // try from 00b2748c to 00b27490 has its CatchHandler @ 00b2958c */
        STRINGS::replaceWString((STRINGS *)local_248,local_218,local_228);
                    /* try { // try from 00b27497 to 00b2749b has its CatchHandler @ 00b29574 */
        std::wstring::assign((wstring_conflict *)local_128);
                    /* try { // try from 00b2749f to 00b274a3 has its CatchHandler @ 00b2958c */
        std::wstring::~wstring(local_248);
                    /* try { // try from 00b274a7 to 00b274ab has its CatchHandler @ 00b293cf */
        std::wstring::~wstring(local_218);
                    /* try { // try from 00b274af to 00b274b3 has its CatchHandler @ 00b293ec */
        std::wstring::~wstring(local_228);
                    /* try { // try from 00b274bc to 00b274c0 has its CatchHandler @ 00b293f1 */
        std::wstring::~wstring(local_238);
                    /* try { // try from 00b274c8 to 00b275ba has its CatchHandler @ 00b29129 */
        CEffectManager::clearOutAffixEffects(*(CEffectManager **)(this_01 + 0x1b8));
        CEffectManager::clearEffects(*(CEffectManager **)(this_01 + 0x1b8),true);
        CEquipment::clearDamageBonuses(this_01);
        *(undefined4 *)(this_01 + 0x344) = 0;
        lVar12 = *(long *)(this + 0x60);
        if (*(CSoundBank **)(lVar12 + 0x298) != (CSoundBank *)0x0) {
          CSoundBank::queueGlobalSample
                    (*(CSoundBank **)(lVar12 + 0x298),0x40,DAT_00fa47fc,DAT_00fa47fc);
          lVar12 = *(long *)(this + 0x60);
        }
        fVar18 = 0.0;
        CSoundBank::playSample
                  (*(CSoundBank **)(this + 0xb8),0x23,*(SceneNode **)(lVar12 + 0x58),0.0,0.0,false);
        bVar3 = true;
      }
LAB_00b2753c:
      this_01[0x348] = (CEquipment)0x1;
      CItem::destroyItemText((CItem *)this_01);
      CInventory::removeEquipment(*(CInventory **)(*(long *)(this + 0x60) + 0x490),this_01);
      lVar12 = CInventory::pickupEquipment
                         (*(CInventory **)(*(long *)(this + 0x60) + 0x490),this_01,true);
      if (lVar12 == 0) {
        local_798 = CPositionableObject::getPosition(*(CPositionableObject **)(this + 0x60),true);
        pCVar15 = (CLevel *)0x0;
        if (*(long *)(*(long *)(this + 0x60) + 0x68) != 0) {
          pCVar15 = *(CLevel **)(*(long *)(*(long *)(this + 0x60) + 0x68) + 0x18);
        }
        local_790 = fVar18;
        CLevel::addItem(pCVar15,(CItem *)this_01,(Vector3 *)&local_798,true);
        (**(code **)(*(long *)this_01 + 0x360))(this_01);
      }
      this[0x72] = (CEnchantMenu)0x1;
      CCharacter::setTarget(*(CCharacter **)(*(long *)(this + 0x80) + 0x38),(CCharacter *)0x0);
      CGameClient::clearMouseClickUnits(*(CGameClient **)(*(long *)(this + 0x80) + 0x1920));
      std::wstring::wstring(local_388,(wstring_conflict *)local_128);
                    /* try { // try from 00b275cb to 00b275cf has its CatchHandler @ 00b28ee0 */
      std::wstring::wstring(local_378,(wstring_conflict *)&performInteraction()::g_Enchant);
                    /* try { // try from 00b275df to 00b275e3 has its CatchHandler @ 00b28f22 */
      CGameUI::openModalDialog(*(CGameUI **)(this + 0x80),local_378,local_388,0);
                    /* try { // try from 00b275e7 to 00b275eb has its CatchHandler @ 00b28ee0 */
      std::wstring::~wstring(local_378);
                    /* try { // try from 00b275ef to 00b27683 has its CatchHandler @ 00b29129 */
      std::wstring::~wstring(local_388);
      CGameUI::clearMenuMouseOvers(*(CGameUI **)(this + 0x80));
      goto LAB_00b27ba4;
    }
    pSVar14 = *(SceneNode **)(*(long *)(this + 0x60) + 0x58);
    this_02 = *(CSoundBank **)(this + 0xb8);
    goto LAB_00b28467;
  case 0x16:
    this_01 = (CEquipment *)
              CInventory::getEquipmentInSlot(*(CInventory **)(*(long *)(this + 0x60) + 0x490),0xe);
    if ((this_01 == (CEquipment *)0x0) ||
       (((cVar4 = CBaseUnit::ISA((CBaseUnit *)this_01,8), cVar4 == '\0' &&
         (cVar4 = CBaseUnit::ISA((CBaseUnit *)this_01,0xd), cVar4 == '\0')) &&
        ((cVar4 = CBaseUnit::ISA((CBaseUnit *)this_01,0x11), cVar4 == '\0' &&
         (cVar4 = CBaseUnit::ISA((CBaseUnit *)this_01,0x18), cVar4 == '\0')))))) goto LAB_00b28450;
    (**(code **)(*(long *)this_01 + 0x2a0))(this_01);
    std::operator+(local_398,(wchar_t *)&performInteraction()::g_YouPlunge);
                    /* try { // try from 00b2769f to 00b276a3 has its CatchHandler @ 00b29252 */
    std::operator+(local_3a8,local_398);
                    /* try { // try from 00b276c1 to 00b276c5 has its CatchHandler @ 00b2924c */
    std::operator+(local_3b8,(wchar_t *)local_3a8);
                    /* try { // try from 00b276e3 to 00b276e7 has its CatchHandler @ 00b29247 */
    std::operator+(local_3c8,local_3b8);
                    /* try { // try from 00b27705 to 00b27709 has its CatchHandler @ 00b29242 */
    std::operator+(local_3d8,(wchar_t *)local_3c8);
                    /* try { // try from 00b2772a to 00b2772e has its CatchHandler @ 00b2923c */
    std::operator+(local_3e8,local_3d8);
                    /* try { // try from 00b2774a to 00b2774e has its CatchHandler @ 00b29237 */
    std::operator+(local_3f8,(wchar_t *)local_3e8);
                    /* try { // try from 00b2775d to 00b27761 has its CatchHandler @ 00b291de */
    std::wstring::assign((wstring_conflict *)local_128);
                    /* try { // try from 00b27765 to 00b27769 has its CatchHandler @ 00b29237 */
    std::wstring::~wstring(local_3f8);
                    /* try { // try from 00b2776d to 00b27771 has its CatchHandler @ 00b2923c */
    std::wstring::~wstring(local_3e8);
                    /* try { // try from 00b2777a to 00b2777e has its CatchHandler @ 00b29242 */
    std::wstring::~wstring(local_3d8);
                    /* try { // try from 00b27787 to 00b2778b has its CatchHandler @ 00b29247 */
    std::wstring::~wstring(local_3c8);
                    /* try { // try from 00b27794 to 00b27798 has its CatchHandler @ 00b2924c */
    std::wstring::~wstring(local_3b8);
                    /* try { // try from 00b277a1 to 00b277a5 has its CatchHandler @ 00b29252 */
    std::wstring::~wstring(local_3a8);
                    /* try { // try from 00b277ae to 00b277b2 has its CatchHandler @ 00b29129 */
    std::wstring::~wstring(local_398);
                    /* try { // try from 00b277c8 to 00b277cc has its CatchHandler @ 00b291d9 */
    std::wstring::wstring(local_428,L"\n",&local_42);
                    /* try { // try from 00b277e2 to 00b277e6 has its CatchHandler @ 00b291d4 */
    std::wstring::wstring(local_418,L"\\n",&local_41);
                    /* try { // try from 00b277f5 to 00b277f9 has its CatchHandler @ 00b291cf */
    std::wstring::wstring(local_408,(wstring_conflict *)local_128);
                    /* try { // try from 00b27818 to 00b2781c has its CatchHandler @ 00b291ca */
    STRINGS::replaceWString((STRINGS *)local_438,local_408,local_418);
                    /* try { // try from 00b27823 to 00b27827 has its CatchHandler @ 00b29198 */
    std::wstring::assign((wstring_conflict *)local_128);
                    /* try { // try from 00b2782b to 00b2782f has its CatchHandler @ 00b291ca */
    std::wstring::~wstring(local_438);
                    /* try { // try from 00b27833 to 00b27837 has its CatchHandler @ 00b291cf */
    std::wstring::~wstring(local_408);
                    /* try { // try from 00b27840 to 00b27844 has its CatchHandler @ 00b291d4 */
    std::wstring::~wstring(local_418);
                    /* try { // try from 00b2784d to 00b27851 has its CatchHandler @ 00b291d9 */
    std::wstring::~wstring(local_428);
    uVar13 = *(uint *)(this_01 + 0x344);
                    /* try { // try from 00b27863 to 00b27914 has its CatchHandler @ 00b29129 */
    lVar12 = CGameGlobals::getSingleton();
    fVar18 = *(float *)(lVar12 + 0x94);
    lVar12 = CGameGlobals::getSingleton();
    fVar16 = (float)uVar13 * fVar18 + *(float *)(lVar12 + 0x80);
    lVar12 = CGameGlobals::getSingleton();
    fVar18 = *(float *)(lVar12 + 0x84);
    if (fVar16 <= *(float *)(lVar12 + 0x84)) {
      fVar18 = fVar16;
    }
    fVar17 = (float)UTILITIES::randomBetweenVolatile(0.0,DAT_00fa871c);
    fVar16 = DAT_00fa86e0;
    if ((fVar18 * DAT_00fa86e0 < fVar17) || (*(long *)(this_01 + 0x1b8) == 0)) {
      iVar6 = *(int *)(this_01 + 0x3e0);
      iVar7 = CEquipment::getMaxSockets(this_01);
      if (iVar6 < iVar7) {
        fVar18 = (float)UTILITIES::randomBetweenVolatile(0.0,DAT_00fa871c);
        lVar12 = CGameGlobals::getSingleton();
        if (fVar16 * *(float *)(lVar12 + 0x78) <= fVar18) goto LAB_00b28188;
        (**(code **)(*(long *)this_01 + 0x2a0))(this_01);
        std::operator+(local_4d8,(wchar_t *)&performInteraction()::g_YouPlunge);
                    /* try { // try from 00b28546 to 00b2854a has its CatchHandler @ 00b28fe2 */
        std::operator+(local_4e8,local_4d8);
                    /* try { // try from 00b28560 to 00b28564 has its CatchHandler @ 00b28fdd */
        std::operator+(local_4f8,(wchar_t *)local_4e8);
                    /* try { // try from 00b2857a to 00b2857e has its CatchHandler @ 00b28fd8 */
        std::operator+(local_508,local_4f8);
                    /* try { // try from 00b28597 to 00b2859b has its CatchHandler @ 00b28fd3 */
        std::operator+(local_518,(wchar_t *)local_508);
                    /* try { // try from 00b285af to 00b285b3 has its CatchHandler @ 00b28fce */
        std::operator+(local_528,local_518);
                    /* try { // try from 00b285c7 to 00b285cb has its CatchHandler @ 00b28fc9 */
        std::operator+(local_538,(wchar_t *)local_528);
                    /* try { // try from 00b285d2 to 00b285d6 has its CatchHandler @ 00b28f75 */
        std::wstring::assign((wstring_conflict *)local_128);
                    /* try { // try from 00b285da to 00b285de has its CatchHandler @ 00b28fc9 */
        std::wstring::~wstring(local_538);
                    /* try { // try from 00b285e2 to 00b285e6 has its CatchHandler @ 00b28fce */
        std::wstring::~wstring(local_528);
                    /* try { // try from 00b285ea to 00b285ee has its CatchHandler @ 00b28fd3 */
        std::wstring::~wstring(local_518);
                    /* try { // try from 00b285f7 to 00b285fb has its CatchHandler @ 00b28fd8 */
        std::wstring::~wstring(local_508);
                    /* try { // try from 00b28604 to 00b28608 has its CatchHandler @ 00b28fdd */
        std::wstring::~wstring(local_4f8);
                    /* try { // try from 00b28611 to 00b28615 has its CatchHandler @ 00b28fe2 */
        std::wstring::~wstring(local_4e8);
                    /* try { // try from 00b2861e to 00b28622 has its CatchHandler @ 00b29129 */
        std::wstring::~wstring(local_4d8);
                    /* try { // try from 00b28638 to 00b2863c has its CatchHandler @ 00b28f6b */
        std::wstring::wstring(local_568,L"\n",&local_46);
                    /* try { // try from 00b28655 to 00b28659 has its CatchHandler @ 00b28f66 */
        std::wstring::wstring(local_558,L"\\n",&local_45);
                    /* try { // try from 00b28668 to 00b2866c has its CatchHandler @ 00b28f61 */
        std::wstring::wstring(local_548,(wstring_conflict *)local_128);
                    /* try { // try from 00b28686 to 00b2868a has its CatchHandler @ 00b28f5c */
        STRINGS::replaceWString((STRINGS *)local_578,local_548,local_558);
                    /* try { // try from 00b28691 to 00b28695 has its CatchHandler @ 00b28f2f */
        std::wstring::assign((wstring_conflict *)local_128);
                    /* try { // try from 00b28699 to 00b2869d has its CatchHandler @ 00b28f5c */
        std::wstring::~wstring(local_578);
                    /* try { // try from 00b286a1 to 00b286a5 has its CatchHandler @ 00b28f61 */
        std::wstring::~wstring(local_548);
                    /* try { // try from 00b286a9 to 00b286ad has its CatchHandler @ 00b28f66 */
        std::wstring::~wstring(local_558);
                    /* try { // try from 00b286b6 to 00b286ba has its CatchHandler @ 00b28f6b */
        std::wstring::~wstring(local_568);
        fVar18 = 0.0;
                    /* try { // try from 00b286d7 to 00b28744 has its CatchHandler @ 00b29129 */
        CSoundBank::playSample
                  (*(CSoundBank **)(this + 0xb8),0x24,*(SceneNode **)(*(long *)(this + 0x60) + 0x58)
                   ,0.0,0.0,false);
        CEquipment::addSockets(this_01);
      }
      else {
LAB_00b28188:
        fVar18 = (float)UTILITIES::randomBetweenVolatile(0.0,DAT_00fa871c);
        lVar12 = CGameGlobals::getSingleton();
        if (fVar16 * *(float *)(lVar12 + 0x7c) < fVar18) {
          fVar18 = 0.0;
          CSoundBank::playSample
                    (*(CSoundBank **)(this + 0xb8),0x23,
                     *(SceneNode **)(*(long *)(this + 0x60) + 0x58),0.0,0.0,false);
          bVar3 = false;
          if (*(CSoundBank **)(*(long *)(this + 0x60) + 0x298) != (CSoundBank *)0x0) {
            fVar18 = DAT_00fa47fc;
            CSoundBank::queueGlobalSample
                      (*(CSoundBank **)(*(long *)(this + 0x60) + 0x298),0x40,DAT_00fa47fc,
                       DAT_00fa47fc);
          }
          goto LAB_00b27aca;
        }
        (**(code **)(*(long *)this_01 + 0x2a0))(this_01);
        std::operator+(local_588,(wchar_t *)&performInteraction()::g_YouPlunge);
                    /* try { // try from 00b281f2 to 00b281f6 has its CatchHandler @ 00b28ebe */
        std::operator+(local_598,local_588);
                    /* try { // try from 00b2820c to 00b28210 has its CatchHandler @ 00b2963c */
        std::operator+(local_5a8,(wchar_t *)local_598);
                    /* try { // try from 00b28226 to 00b2822a has its CatchHandler @ 00b29637 */
        std::operator+(local_5b8,local_5a8);
                    /* try { // try from 00b28240 to 00b28244 has its CatchHandler @ 00b29632 */
        std::operator+(local_5c8,(wchar_t *)local_5b8);
                    /* try { // try from 00b2825d to 00b28261 has its CatchHandler @ 00b2962c */
        std::operator+(local_5d8,local_5c8);
                    /* try { // try from 00b28275 to 00b28279 has its CatchHandler @ 00b29627 */
        std::operator+(local_5e8,(wchar_t *)local_5d8);
                    /* try { // try from 00b28280 to 00b28284 has its CatchHandler @ 00b295db */
        std::wstring::assign((wstring_conflict *)local_128);
                    /* try { // try from 00b28288 to 00b2828c has its CatchHandler @ 00b29627 */
        std::wstring::~wstring(local_5e8);
                    /* try { // try from 00b28290 to 00b28294 has its CatchHandler @ 00b2962c */
        std::wstring::~wstring(local_5d8);
                    /* try { // try from 00b2829d to 00b282a1 has its CatchHandler @ 00b29632 */
        std::wstring::~wstring(local_5c8);
                    /* try { // try from 00b282aa to 00b282ae has its CatchHandler @ 00b29637 */
        std::wstring::~wstring(local_5b8);
                    /* try { // try from 00b282b7 to 00b282bb has its CatchHandler @ 00b2963c */
        std::wstring::~wstring(local_5a8);
                    /* try { // try from 00b282c4 to 00b282c8 has its CatchHandler @ 00b28ebe */
        std::wstring::~wstring(local_598);
                    /* try { // try from 00b282d1 to 00b282d5 has its CatchHandler @ 00b29129 */
        std::wstring::~wstring(local_588);
                    /* try { // try from 00b282eb to 00b282ef has its CatchHandler @ 00b295d6 */
        std::wstring::wstring(local_618,L"\n",&local_48);
                    /* try { // try from 00b28305 to 00b28309 has its CatchHandler @ 00b295ce */
        std::wstring::wstring(local_608,L"\\n",&local_47);
                    /* try { // try from 00b28318 to 00b2831c has its CatchHandler @ 00b29385 */
        std::wstring::wstring(local_5f8,(wstring_conflict *)local_128);
                    /* try { // try from 00b2833b to 00b2833f has its CatchHandler @ 00b29379 */
        STRINGS::replaceWString((STRINGS *)local_628,local_5f8,local_608);
                    /* try { // try from 00b28346 to 00b2834a has its CatchHandler @ 00b28ef0 */
        std::wstring::assign((wstring_conflict *)local_128);
                    /* try { // try from 00b2834e to 00b28352 has its CatchHandler @ 00b29379 */
        std::wstring::~wstring(local_628);
                    /* try { // try from 00b28356 to 00b2835a has its CatchHandler @ 00b29385 */
        std::wstring::~wstring(local_5f8);
                    /* try { // try from 00b28363 to 00b28367 has its CatchHandler @ 00b295ce */
        std::wstring::~wstring(local_608);
                    /* try { // try from 00b28370 to 00b28374 has its CatchHandler @ 00b295d6 */
        std::wstring::~wstring(local_618);
        fVar18 = 0.0;
                    /* try { // try from 00b28391 to 00b28532 has its CatchHandler @ 00b29129 */
        CSoundBank::playSample
                  (*(CSoundBank **)(this + 0xb8),0x24,*(SceneNode **)(*(long *)(this + 0x60) + 0x58)
                   ,0.0,0.0,false);
        iVar6 = 4;
        if (3 < *(uint *)(*(long *)(this + 0x60) + 0x100)) {
          iVar6 = *(int *)(*(long *)(this + 0x60) + 0x100);
        }
        CEquipment::addEnchant(this_01,iVar6,iVar5 + 1,iVar5 + 2);
      }
      if (*(CSoundBank **)(*(long *)(this + 0x60) + 0x298) != (CSoundBank *)0x0) {
        fVar18 = DAT_00fa47fc;
        CSoundBank::queueGlobalSample
                  (*(CSoundBank **)(*(long *)(this + 0x60) + 0x298),0x3f,DAT_00fa47fc,DAT_00fa47fc);
      }
      *(int *)(this_01 + 0x344) = *(int *)(this_01 + 0x344) + 1;
      bVar3 = false;
    }
    else {
      (**(code **)(*(long *)this_01 + 0x2a0))(this_01);
      std::operator+(local_448,(wchar_t *)&performInteraction()::g_YouPlunge);
                    /* try { // try from 00b27928 to 00b2792c has its CatchHandler @ 00b29190 */
      std::operator+(local_458,local_448);
                    /* try { // try from 00b27945 to 00b27949 has its CatchHandler @ 00b29188 */
      std::operator+(local_468,(wchar_t *)local_458);
                    /* try { // try from 00b2795d to 00b27961 has its CatchHandler @ 00b29180 */
      std::operator+(local_478,local_468);
                    /* try { // try from 00b27975 to 00b27979 has its CatchHandler @ 00b29178 */
      std::operator+(local_488,(wchar_t *)local_478);
                    /* try { // try from 00b27980 to 00b27984 has its CatchHandler @ 00b290d5 */
      std::wstring::assign((wstring_conflict *)local_128);
                    /* try { // try from 00b27988 to 00b2798c has its CatchHandler @ 00b29178 */
      std::wstring::~wstring(local_488);
                    /* try { // try from 00b27990 to 00b27994 has its CatchHandler @ 00b29180 */
      std::wstring::~wstring(local_478);
                    /* try { // try from 00b27998 to 00b2799c has its CatchHandler @ 00b29188 */
      std::wstring::~wstring(local_468);
                    /* try { // try from 00b279a5 to 00b279a9 has its CatchHandler @ 00b29190 */
      std::wstring::~wstring(local_458);
                    /* try { // try from 00b279b2 to 00b279b6 has its CatchHandler @ 00b29129 */
      std::wstring::~wstring(local_448);
                    /* try { // try from 00b279cc to 00b279d0 has its CatchHandler @ 00b290cc */
      std::wstring::wstring(local_4b8,L"\n",&local_44);
                    /* try { // try from 00b279e9 to 00b279ed has its CatchHandler @ 00b290c7 */
      std::wstring::wstring(local_4a8,L"\\n",&local_43);
                    /* try { // try from 00b279fc to 00b27a00 has its CatchHandler @ 00b290c2 */
      std::wstring::wstring(local_498,(wstring_conflict *)local_128);
                    /* try { // try from 00b27a1a to 00b27a1e has its CatchHandler @ 00b290bd */
      STRINGS::replaceWString((STRINGS *)local_4c8,local_498,local_4a8);
                    /* try { // try from 00b27a25 to 00b27a29 has its CatchHandler @ 00b29090 */
      std::wstring::assign((wstring_conflict *)local_128);
                    /* try { // try from 00b27a2d to 00b27a31 has its CatchHandler @ 00b290bd */
      std::wstring::~wstring(local_4c8);
                    /* try { // try from 00b27a35 to 00b27a39 has its CatchHandler @ 00b290c2 */
      std::wstring::~wstring(local_498);
                    /* try { // try from 00b27a3d to 00b27a41 has its CatchHandler @ 00b290c7 */
      std::wstring::~wstring(local_4a8);
                    /* try { // try from 00b27a4a to 00b27a4e has its CatchHandler @ 00b290cc */
      std::wstring::~wstring(local_4b8);
                    /* try { // try from 00b27a56 to 00b27b48 has its CatchHandler @ 00b29129 */
      CEffectManager::clearOutAffixEffects(*(CEffectManager **)(this_01 + 0x1b8));
      CEffectManager::clearEffects(*(CEffectManager **)(this_01 + 0x1b8),true);
      CEquipment::clearDamageBonuses(this_01);
      fVar18 = 0.0;
      CSoundBank::playSample
                (*(CSoundBank **)(this + 0xb8),0x23,*(SceneNode **)(*(long *)(this + 0x60) + 0x58),
                 0.0,0.0,false);
      if (*(CSoundBank **)(*(long *)(this + 0x60) + 0x298) != (CSoundBank *)0x0) {
        fVar18 = DAT_00fa47fc;
        CSoundBank::queueGlobalSample
                  (*(CSoundBank **)(*(long *)(this + 0x60) + 0x298),0x40,DAT_00fa47fc,DAT_00fa47fc);
      }
      *(undefined4 *)(this_01 + 0x344) = 0;
      bVar3 = true;
    }
LAB_00b27aca:
    this_01[0x348] = (CEquipment)0x1;
    CItem::destroyItemText((CItem *)this_01);
    CInventory::removeEquipment(*(CInventory **)(*(long *)(this + 0x60) + 0x490),this_01);
    lVar12 = CInventory::pickupEquipment
                       (*(CInventory **)(*(long *)(this + 0x60) + 0x490),this_01,true);
    if (lVar12 == 0) {
      local_7a8 = CPositionableObject::getPosition(*(CPositionableObject **)(this + 0x60),true);
      pCVar15 = (CLevel *)0x0;
      if (*(long *)(*(long *)(this + 0x60) + 0x68) != 0) {
        pCVar15 = *(CLevel **)(*(long *)(*(long *)(this + 0x60) + 0x68) + 0x18);
      }
      local_7a0 = fVar18;
      CLevel::addItem(pCVar15,(CItem *)this_01,(Vector3 *)&local_7a8,true);
      (**(code **)(*(long *)this_01 + 0x360))(this_01);
    }
    this[0x72] = (CEnchantMenu)0x1;
    CCharacter::setTarget(*(CCharacter **)(*(long *)(this + 0x80) + 0x38),(CCharacter *)0x0);
    CGameClient::clearMouseClickUnits(*(CGameClient **)(*(long *)(this + 0x80) + 0x1920));
    std::wstring::wstring(local_648,(wstring_conflict *)local_128);
                    /* try { // try from 00b27b59 to 00b27b5d has its CatchHandler @ 00b2908b */
    std::wstring::wstring(local_638,(wstring_conflict *)&performInteraction()::g_Enchant);
                    /* try { // try from 00b27b6d to 00b27b71 has its CatchHandler @ 00b2910f */
    CGameUI::openModalDialog(*(CGameUI **)(this + 0x80),local_638,local_648,0);
                    /* try { // try from 00b27b75 to 00b27b79 has its CatchHandler @ 00b2908b */
    std::wstring::~wstring(local_638);
                    /* try { // try from 00b27b7d to 00b27c4e has its CatchHandler @ 00b29129 */
    std::wstring::~wstring(local_648);
    CGameUI::clearMenuMouseOvers(*(CGameUI **)(this + 0x80));
    plVar11 = *(long **)(this + 0x68);
    if (plVar11 != (long *)0x0) {
      (**(code **)(*plVar11 + 0x280))(plVar11,*(undefined8 *)(this + 0x60));
    }
LAB_00b27ba4:
    (**(code **)(*(long *)this + 0x48))(this);
    CCharacter::incrementJournalStatistic(*(CCharacter **)(this + 0x60),0x11,1);
    goto LAB_00b2675a;
  default:
    goto switchD_00b26486_caseD_17;
  case 0x19:
    this_01 = (CEquipment *)
              CInventory::getEquipmentInSlot(*(CInventory **)(*(long *)(this + 0x60) + 0x490),0xe);
    if (((this_01 == (CEquipment *)0x0) || (*(int *)(this_01 + 0x3e0) == 0)) ||
       (*(int *)(this_01 + 0x3f0) == 0)) goto LAB_00b28450;
    (**(code **)(*(long *)this_01 + 0x2a0))(this_01);
    std::operator+(local_658,(wchar_t *)&performInteraction()::g_TheGemsWithin);
                    /* try { // try from 00b27c6a to 00b27c6e has its CatchHandler @ 00b29357 */
    std::operator+(local_668,local_658);
                    /* try { // try from 00b27c8f to 00b27c93 has its CatchHandler @ 00b29352 */
    std::operator+(local_678,(wchar_t *)local_668);
                    /* try { // try from 00b27caf to 00b27cb3 has its CatchHandler @ 00b2934b */
    std::operator+(local_688,local_678);
                    /* try { // try from 00b27ccf to 00b27cd3 has its CatchHandler @ 00b29346 */
    std::operator+(local_698,(wchar_t *)local_688);
                    /* try { // try from 00b27ce2 to 00b27ce6 has its CatchHandler @ 00b2930c */
    std::wstring::assign((wstring_conflict *)local_128);
                    /* try { // try from 00b27cea to 00b27cee has its CatchHandler @ 00b29346 */
    std::wstring::~wstring(local_698);
                    /* try { // try from 00b27cf2 to 00b27cf6 has its CatchHandler @ 00b2934b */
    std::wstring::~wstring(local_688);
                    /* try { // try from 00b27cfa to 00b27cfe has its CatchHandler @ 00b29352 */
    std::wstring::~wstring(local_678);
                    /* try { // try from 00b27d07 to 00b27d0b has its CatchHandler @ 00b29357 */
    std::wstring::~wstring(local_668);
                    /* try { // try from 00b27d14 to 00b27d18 has its CatchHandler @ 00b29129 */
    std::wstring::~wstring(local_658);
                    /* try { // try from 00b27d2e to 00b27d32 has its CatchHandler @ 00b29307 */
    std::wstring::wstring(local_6c8,L"\n",&local_4a);
                    /* try { // try from 00b27d4b to 00b27d4f has its CatchHandler @ 00b295c9 */
    std::wstring::wstring(local_6b8,L"\\n",&local_49);
                    /* try { // try from 00b27d5e to 00b27d62 has its CatchHandler @ 00b295c4 */
    std::wstring::wstring(local_6a8,(wstring_conflict *)local_128);
                    /* try { // try from 00b27d7c to 00b27d80 has its CatchHandler @ 00b295bf */
    STRINGS::replaceWString((STRINGS *)local_6d8,local_6a8,local_6b8);
                    /* try { // try from 00b27d87 to 00b27d8b has its CatchHandler @ 00b29592 */
    std::wstring::assign((wstring_conflict *)local_128);
                    /* try { // try from 00b27d8f to 00b27d93 has its CatchHandler @ 00b295bf */
    std::wstring::~wstring(local_6d8);
                    /* try { // try from 00b27d97 to 00b27d9b has its CatchHandler @ 00b295c4 */
    std::wstring::~wstring(local_6a8);
                    /* try { // try from 00b27d9f to 00b27da3 has its CatchHandler @ 00b295c9 */
    std::wstring::~wstring(local_6b8);
                    /* try { // try from 00b27dac to 00b27db0 has its CatchHandler @ 00b29307 */
    std::wstring::~wstring(local_6c8);
    uVar19 = 0;
                    /* try { // try from 00b27dcd to 00b27ed7 has its CatchHandler @ 00b29129 */
    CSoundBank::playSample
              (*(CSoundBank **)(this + 0xb8),0x24,*(SceneNode **)(*(long *)(this + 0x60) + 0x58),0.0
               ,0.0,false);
    if (*(int *)(this_01 + 0x3f0) != 0) {
      uVar13 = 0;
      do {
        lVar12 = (ulong)uVar13 * 8;
        plVar11 = (long *)(lVar12 + *(long *)(this_01 + 1000));
        if ((long *)*plVar11 != (long *)0x0) {
          (**(code **)(*(long *)*plVar11 + 8))();
          *(undefined8 *)(*(long *)(this_01 + 1000) + (ulong)uVar13 * 8) = 0;
          plVar11 = (long *)(lVar12 + *(long *)(this_01 + 1000));
        }
        *plVar11 = 0;
        uVar13 = uVar13 + 1;
      } while (uVar13 < *(uint *)(this_01 + 0x3f0));
    }
    *(undefined4 *)(this_01 + 0x3f0) = 0;
    *(undefined4 *)(this_01 + 0x3f4) = 0;
    if (*(void **)(this_01 + 1000) != (void *)0x0) {
      operator_delete__(*(void **)(this_01 + 1000));
    }
    *(undefined8 *)(this_01 + 1000) = 0;
    CInventory::removeEquipment(*(CInventory **)(*(long *)(this + 0x60) + 0x490),this_01);
    lVar12 = CInventory::pickupEquipment
                       (*(CInventory **)(*(long *)(this + 0x60) + 0x490),this_01,true);
    if (lVar12 == 0) {
      local_7b8 = CPositionableObject::getPosition(*(CPositionableObject **)(this + 0x60),true);
      pCVar15 = (CLevel *)0x0;
      if (*(long *)(*(long *)(this + 0x60) + 0x68) != 0) {
        pCVar15 = *(CLevel **)(*(long *)(*(long *)(this + 0x60) + 0x68) + 0x18);
      }
      local_7b0 = uVar19;
      CLevel::addItem(pCVar15,(CItem *)this_01,(Vector3 *)&local_7b8,true);
      (**(code **)(*(long *)this_01 + 0x360))(this_01);
    }
    this[0x72] = (CEnchantMenu)0x1;
    CCharacter::setTarget(*(CCharacter **)(*(long *)(this + 0x80) + 0x38),(CCharacter *)0x0);
    CGameClient::clearMouseClickUnits(*(CGameClient **)(*(long *)(this + 0x80) + 0x1920));
    std::wstring::wstring(local_6f8,(wstring_conflict *)local_128);
                    /* try { // try from 00b27ee8 to 00b27eec has its CatchHandler @ 00b2907b */
    std::wstring::wstring(local_6e8,(wstring_conflict *)&performInteraction()::g_Sockets);
                    /* try { // try from 00b27efc to 00b27f00 has its CatchHandler @ 00b2928e */
    CGameUI::openModalDialog(*(CGameUI **)(this + 0x80),local_6e8,local_6f8,0);
                    /* try { // try from 00b27f04 to 00b27f08 has its CatchHandler @ 00b2907b */
    std::wstring::~wstring(local_6e8);
                    /* try { // try from 00b27f0c to 00b27f9a has its CatchHandler @ 00b29129 */
    std::wstring::~wstring(local_6f8);
    CGameUI::clearMenuMouseOvers(*(CGameUI **)(this + 0x80));
    (**(code **)(*(long *)this + 0x48))(this);
    break;
  case 0x1a:
    this_01 = (CEquipment *)
              CInventory::getEquipmentInSlot(*(CInventory **)(*(long *)(this + 0x60) + 0x490),0xe);
    if (((this_01 != (CEquipment *)0x0) && (*(int *)(this_01 + 0x3e0) != 0)) &&
       (*(int *)(this_01 + 0x3f0) != 0)) {
      std::operator+(local_728,(wchar_t *)&performInteraction()::g_GemsRecovered);
                    /* try { // try from 00b27fa9 to 00b27fad has its CatchHandler @ 00b292f7 */
      std::wstring::assign((wstring_conflict *)local_128);
                    /* try { // try from 00b27fb1 to 00b27fb5 has its CatchHandler @ 00b29129 */
      std::wstring::~wstring(local_728);
                    /* try { // try from 00b27fcb to 00b27fcf has its CatchHandler @ 00b292f2 */
      std::wstring::wstring(local_758,L"\n",&local_4c);
                    /* try { // try from 00b27fe8 to 00b27fec has its CatchHandler @ 00b292ed */
      std::wstring::wstring(local_748,L"\\n",&local_4b);
                    /* try { // try from 00b27ffb to 00b27fff has its CatchHandler @ 00b292d0 */
      std::wstring::wstring(local_738,(wstring_conflict *)local_128);
                    /* try { // try from 00b28019 to 00b2801d has its CatchHandler @ 00b29374 */
      STRINGS::replaceWString((STRINGS *)local_768,local_738,local_748);
                    /* try { // try from 00b28024 to 00b28028 has its CatchHandler @ 00b2935c */
      std::wstring::assign((wstring_conflict *)local_128);
                    /* try { // try from 00b2802c to 00b28030 has its CatchHandler @ 00b29374 */
      std::wstring::~wstring(local_768);
                    /* try { // try from 00b28034 to 00b28038 has its CatchHandler @ 00b292d0 */
      std::wstring::~wstring(local_738);
                    /* try { // try from 00b2803c to 00b28040 has its CatchHandler @ 00b292ed */
      std::wstring::~wstring(local_748);
                    /* try { // try from 00b28049 to 00b2804d has its CatchHandler @ 00b292f2 */
      std::wstring::~wstring(local_758);
      uVar19 = 0;
                    /* try { // try from 00b2806a to 00b281de has its CatchHandler @ 00b29129 */
      CSoundBank::playSample
                (*(CSoundBank **)(this + 0xb8),0x24,*(SceneNode **)(*(long *)(this + 0x60) + 0x58),
                 0.0,0.0,false);
      while (0 < *(int *)(this_01 + 0x3f0)) {
        puVar2 = *(undefined8 **)(this_01 + 1000);
        uVar13 = *(int *)(this_01 + 0x3f0) - 1;
        this_00 = (CBaseUnit *)*puVar2;
        *(uint *)(this_01 + 0x3f0) = uVar13;
        *puVar2 = puVar2[uVar13];
        cVar4 = CBaseUnit::ISA(this_00,0xa0);
        if (cVar4 == '\0') {
          CBaseUnit::reapplyEffects(this_00,true);
          CBaseUnit::reapplyAffixes(this_00,true);
          if (0 < *(int *)(this_00 + 0x28c)) {
            CEquipment::improveHeirloom((CEquipment *)this_00);
          }
        }
        lVar12 = CInventory::pickupEquipment
                           (*(CInventory **)(*(long *)(this + 0x60) + 0x490),(CEquipment *)this_00,
                            true);
        if (lVar12 == 0) {
          local_7c8 = CPositionableObject::getPosition(*(CPositionableObject **)(this + 0x60),true);
          pCVar15 = (CLevel *)0x0;
          if (*(long *)(*(long *)(this + 0x60) + 0x68) != 0) {
            pCVar15 = *(CLevel **)(*(long *)(*(long *)(this + 0x60) + 0x68) + 0x18);
          }
          local_7c0 = uVar19;
          CLevel::addItem(pCVar15,(CItem *)this_00,(Vector3 *)&local_7c8,true);
          (**(code **)(*(long *)this_00 + 0x360))(this_00);
        }
      }
      CInventory::removeEquipment(*(CInventory **)(*(long *)(this + 0x60) + 0x490),this_01);
      (**(code **)(*(long *)this_01 + 8))(this_01);
      this[0x72] = (CEnchantMenu)0x1;
      CCharacter::setTarget(*(CCharacter **)(*(long *)(this + 0x80) + 0x38),(CCharacter *)0x0);
      CGameClient::clearMouseClickUnits(*(CGameClient **)(*(long *)(this + 0x80) + 0x1920));
      std::wstring::wstring(local_788,(wstring_conflict *)local_128);
                    /* try { // try from 00b28755 to 00b28759 has its CatchHandler @ 00b2956f */
      std::wstring::wstring(local_778,(wstring_conflict *)&performInteraction()::g_Sockets);
                    /* try { // try from 00b28769 to 00b2876d has its CatchHandler @ 00b29557 */
      CGameUI::openModalDialog(*(CGameUI **)(this + 0x80),local_778,local_788,0);
                    /* try { // try from 00b28771 to 00b28775 has its CatchHandler @ 00b2956f */
      std::wstring::~wstring(local_778);
                    /* try { // try from 00b28779 to 00b28a26 has its CatchHandler @ 00b29129 */
      std::wstring::~wstring(local_788);
      CGameUI::clearMenuMouseOvers(*(CGameUI **)(this + 0x80));
      (**(code **)(*(long *)this + 0x48))(this);
      goto switchD_00b26486_caseD_17;
    }
LAB_00b28450:
    this_02 = *(CSoundBank **)(this + 0xb8);
    pSVar14 = *(SceneNode **)(*(long *)(this + 0x60) + 0x58);
LAB_00b28467:
    CSoundBank::playSample(this_02,0x18,pSVar14,0.0,0.0,false);
    break;
  case 0x1b:
                    /* try { // try from 00b264a8 to 00b2663c has its CatchHandler @ 00b29129 */
    this_01 = (CEquipment *)
              CInventory::getEquipmentInSlot(*(CInventory **)(*(long *)(this + 0x60) + 0x490),0xe);
    if (this_01 == (CEquipment *)0x0) {
      CSoundBank::playSample
                (*(CSoundBank **)(this + 0xb8),0x18,*(SceneNode **)(*(long *)(this + 0x60) + 0x58),
                 0.0,0.0,false);
      goto switchD_00b26486_caseD_17;
    }
    this[0x73] = (CEnchantMenu)0x1;
    this[0x72] = (CEnchantMenu)0x1;
    CCharacter::setTarget(*(CCharacter **)(*(long *)(this + 0x80) + 0x38),(CCharacter *)0x0);
    lVar12 = *(long *)(*(long *)(this + 0x80) + 0x1920);
    if (*(CRunicCore **)(lVar12 + 0x1f8) != (CRunicCore *)0x0) {
      CRunicCore::removeSafePointer
                (*(CRunicCore **)(lVar12 + 0x1f8),(TSafePointer *)(lVar12 + 0x1f8),
                 *(uint *)(lVar12 + 0x200));
      *(undefined8 *)(lVar12 + 0x1f8) = 0;
    }
    if (*(CRunicCore **)(lVar12 + 0x1e8) != (CRunicCore *)0x0) {
      CRunicCore::removeSafePointer
                (*(CRunicCore **)(lVar12 + 0x1e8),(TSafePointer *)(lVar12 + 0x1e8),
                 *(uint *)(lVar12 + 0x1f0));
      *(undefined8 *)(lVar12 + 0x1e8) = 0;
    }
    if (*(CRunicCore **)(lVar12 + 0x1c8) != (CRunicCore *)0x0) {
      CRunicCore::removeSafePointer
                (*(CRunicCore **)(lVar12 + 0x1c8),(TSafePointer *)(lVar12 + 0x1c8),
                 *(uint *)(lVar12 + 0x1d0));
      *(undefined8 *)(lVar12 + 0x1c8) = 0;
    }
    if (*(CRunicCore **)(lVar12 + 0x1d8) != (CRunicCore *)0x0) {
      CRunicCore::removeSafePointer
                (*(CRunicCore **)(lVar12 + 0x1d8),(TSafePointer *)(lVar12 + 0x1d8),
                 *(uint *)(lVar12 + 0x1e0));
      *(undefined8 *)(lVar12 + 0x1d8) = 0;
    }
    CGameUI::closeRight(*(CGameUI **)(this + 0x80));
    CInventory::removeEquipment(*(CInventory **)(*(long *)(this + 0x60) + 0x490),this_01);
    iVar5 = *(int *)(this_01 + 0x28c);
    if (iVar5 == 0) {
      (**(code **)(*(long *)this_01 + 0x2a0))(this_01);
      std::operator+(local_708,(wchar_t *)(*(long *)(this + 0x60) + 0x4c0));
                    /* try { // try from 00b2664e to 00b26652 has its CatchHandler @ 00b293ad */
      std::operator+(local_718,local_708);
                    /* try { // try from 00b2665d to 00b26661 has its CatchHandler @ 00b2938d */
      std::wstring::assign((wstring_conflict *)(this_01 + 0x210));
                    /* try { // try from 00b26665 to 00b26669 has its CatchHandler @ 00b293ad */
      std::wstring::~wstring(local_718);
                    /* try { // try from 00b26675 to 00b267dc has its CatchHandler @ 00b29129 */
      std::wstring::~wstring(local_708);
      iVar5 = *(int *)(this_01 + 0x28c);
    }
    *(int *)(this_01 + 0x28c) = iVar5 + 1;
    CEquipment::improveHeirloom(this_01);
    *(CEquipment **)(*(long *)(*(long *)(this + 0x80) + 0x1920) + 0x3900) = this_01;
    *(int *)(*(long *)(*(long *)(this + 0x80) + 0x1920) + 0x3908) =
         *(int *)(*(long *)(*(long *)(this + 0x80) + 0x38) + 0xa10) + 1;
    *(undefined1 *)(*(long *)(this + 0x60) + 0xa14) = 1;
    uVar8 = CSteamStats::getSingleton();
    CSteamStats::incrementStat(uVar8,0xb,1);
    uVar19 = *(undefined4 *)(*(long *)(this + 0x60) + 0x100);
    uVar8 = CSteamStats::getSingleton();
    CSteamStats::incrementStat(uVar8,0xc,uVar19);
    CGameUI::clearMenuMouseOvers(*(CGameUI **)(this + 0x80));
    (**(code **)(*(long *)this + 0x48))(this);
  }
  bVar3 = false;
LAB_00b2675a:
  if ((this_01 != (CEquipment *)0x0) && (*(int *)(this + 0x10c) - 0x15U < 2)) {
    if (bVar3) {
      if (*(int *)(this_01 + 0x344) == 0) {
        pCVar9 = (CAchievements *)CAchievements::getSingleton();
        pCVar10 = (CAchievement *)CAchievements::getAchievement(pCVar9,0x1d);
        CAchievement::forceComplete(pCVar10);
      }
      uVar8 = CSteamStats::getSingleton();
      CSteamStats::incrementStat(uVar8,7,1);
    }
    else {
      if (*(int *)(this_01 + 0x344) == 5) {
        pCVar9 = (CAchievements *)CAchievements::getSingleton();
        pCVar10 = (CAchievement *)CAchievements::getAchievement(pCVar9,0x20);
      }
      else {
        if (*(int *)(this_01 + 0x344) != 10) goto switchD_00b26486_caseD_17;
        pCVar9 = (CAchievements *)CAchievements::getSingleton();
        pCVar10 = (CAchievement *)CAchievements::getAchievement(pCVar9,0x21);
      }
      CAchievement::forceComplete(pCVar10);
    }
  }
switchD_00b26486_caseD_17:
  if ((allocator *)(local_128[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = local_128[0] + -2;
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_128[0] + -6));
    }
  }
  return;
}

/* address=00b29650
   symbol=CEnchantMenu::onClick */

/* CEnchantMenu::onClick(ELayoutFunction) */

undefined8 __thiscall CEnchantMenu::onClick(CEnchantMenu *this,int param_2)

{
  long lVar1;

  if (this[0x70] != (CEnchantMenu)0x0) {
    if (param_2 == 8) {
      this[0x72] = (CEnchantMenu)0x1;
      CCharacter::setTarget(*(CCharacter **)(*(long *)(this + 0x80) + 0x38),(CCharacter *)0x0);
      lVar1 = *(long *)(*(long *)(this + 0x80) + 0x1920);
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
      CGameUI::closeRight(*(CGameUI **)(this + 0x80));
    }
    else if (param_2 == 9) {
      performInteraction(this);
    }
  }
  return 1;
}

/* address=00b29780
   symbol=CEnchantMenu::setSlotIcon */

/* WARNING: Removing unreachable block (ram,0x00b2ade2) */
/* WARNING: Removing unreachable block (ram,0x00b2ae56) */
/* WARNING: Removing unreachable block (ram,0x00b2af35) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CEnchantMenu::setSlotIcon(CEquipment*, int) */

void __thiscall CEnchantMenu::setSlotIcon(CEnchantMenu *this,CEquipment *param_1,int param_2)

{
  int *piVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  byte bVar6;
  char cVar7;
  uint uVar8;
  uint uVar9;
  long lVar10;
  float *pfVar11;
  char *pcVar12;
  byte *pbVar13;
  CEquipment *this_00;
  ulong uVar14;
  uint *puVar15;
  undefined4 *puVar16;
  length_error *this_01;
  ulong uVar17;
  long lVar18;
  byte *pbVar19;
  byte *pbVar20;
  UVector2 *pUVar21;
  String *pSVar22;
  ulong uVar23;
  bool bVar24;
  uint uVar25;
  float fVar26;
  uint uVar27;
  uint uVar28;
  UVector2 *local_12c8;
  long local_12b8;
  ulong local_12b0;
  undefined8 local_12a8;
  undefined8 local_12a0;
  undefined8 local_1298;
  uint local_1290 [32];
  uint *local_1210;
  undefined8 local_1208;
  ulong local_1200;
  undefined8 local_11f8;
  undefined8 local_11f0;
  undefined8 local_11e8;
  uint local_11e0 [5];
  uint local_11cc [27];
  uint *local_1160;
  Image local_1158 [176];
  undefined8 local_10a8;
  ulong local_10a0;
  undefined8 local_1098;
  undefined8 local_1090;
  undefined8 local_1088;
  uint local_1080 [11];
  uint local_1054 [21];
  uint *local_1000;
  undefined8 local_ff8;
  ulong local_ff0;
  undefined8 local_fe8;
  undefined8 local_fe0;
  undefined8 local_fd8;
  uint local_fd0 [5];
  uint local_fbc [27];
  uint *local_f50;
  Image local_f48 [176];
  undefined8 local_e98;
  ulong local_e90;
  undefined8 local_e88;
  undefined8 local_e80;
  undefined8 local_e78;
  uint local_e70 [15];
  uint local_e34 [17];
  uint *local_df0;
  undefined8 local_de8;
  ulong local_de0;
  undefined8 local_dd8;
  undefined8 local_dd0;
  undefined8 local_dc8;
  undefined4 local_dc0 [32];
  undefined4 *local_d40;
  undefined8 local_d38;
  ulong local_d30;
  undefined8 local_d28;
  undefined8 local_d20;
  undefined8 local_d18;
  uint local_d10 [5];
  uint local_cfc [27];
  uint *local_c90;
  String local_c88 [176];
  Image local_bd8 [176];
  String local_b28 [176];
  String local_a78 [176];
  Image local_9c8 [176];
  String local_918 [176];
  undefined8 local_868;
  ulong local_860;
  undefined8 local_858;
  undefined8 local_850;
  undefined8 local_848;
  uint local_840 [5];
  uint local_82c [27];
  uint *local_7c0;
  Image local_7b8 [176];
  undefined8 local_708;
  ulong local_700;
  undefined8 local_6f8;
  undefined8 local_6f0;
  undefined8 local_6e8;
  uint local_6e0 [12];
  uint local_6b0 [20];
  uint *local_660;
  undefined8 local_658;
  ulong local_650;
  undefined8 local_648;
  undefined8 local_640;
  undefined8 local_638;
  undefined4 local_630 [32];
  undefined4 *local_5b0;
  undefined8 local_5a8;
  ulong local_5a0;
  undefined8 local_598;
  undefined8 local_590;
  undefined8 local_588;
  uint local_580 [5];
  uint local_56c [27];
  uint *local_500;
  String local_4f8 [176];
  Image local_448 [176];
  String local_398 [176];
  undefined8 local_2e8;
  ulong local_2e0;
  undefined8 local_2d8;
  undefined8 local_2d0;
  undefined8 local_2c8;
  uint local_2c0 [5];
  uint local_2ac [27];
  uint *local_240;
  Image local_238 [176];
  undefined8 local_188;
  ulong local_180;
  undefined8 local_178;
  undefined8 local_170;
  undefined8 local_168;
  uint local_160 [13];
  uint local_12c [19];
  uint *local_e0;
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  float local_a0;
  float local_9c;
  undefined4 local_88;
  float local_84;
  undefined4 local_80;
  float local_7c;
  float local_70;
  float local_6c;
  long local_68 [2];
  long local_58 [2];
  byte *local_48;
  allocator local_3a [10];

  lVar18 = (long)param_2;
  lVar10 = CEGUI::Window::getPosition();
  uVar9 = DAT_00fa86f4;
  uVar8 = DAT_00fa4810;
  fVar26 = *(float *)(lVar10 + 8) * 0.0;
  uVar25 = -(uint)(0.0 < fVar26);
  uVar28 = DAT_00fa4810 & uVar25;
  uVar27 = ~uVar25 & DAT_00fa86f4;
  fVar2 = *(float *)(lVar10 + 0xc);
  pfVar11 = (float *)CEGUI::Window::getPosition();
  fVar3 = *pfVar11;
  uVar25 = -(uint)(0.0 < fVar3 * 0.0);
  fVar4 = pfVar11[1];
  local_12c8 = *(UVector2 **)(param_1 + 0x2c8);
  if (local_12c8 == (UVector2 *)0x0) {
    CEquipment::createIcon(param_1,*(CGameUI **)(this + 0x80),false);
    local_12c8 = *(UVector2 **)(param_1 + 0x2c8);
    if (local_12c8 != (UVector2 *)0x0) {
      CEGUI::EventSet::setMutedState((bool)((char)local_12c8 + '8'));
      local_12c8[0x3e2] = (UVector2)0x1;
      goto LAB_00b29867;
    }
  }
  else {
LAB_00b29867:
    if (*(Window **)(local_12c8 + 0xb0) != (Window *)0x0) {
      CEGUI::Window::removeChildWindow(*(Window **)(local_12c8 + 0xb0));
    }
  }
  if ((param_1[0x348] == (CEquipment)0x0) || (*(uint *)(param_1 + 0x3e0) == 0)) {
    local_650 = 0x20;
    local_648 = 0;
    local_638 = 0;
    local_640 = 0;
    local_5b0 = (undefined4 *)0x0;
    local_658 = 0;
    local_630[0] = 0;
    CEGUI::String::grow((ulong)&local_658);
    local_658 = 0;
    puVar16 = local_630;
    if (0x20 < local_650) {
      puVar16 = local_5b0;
    }
    *puVar16 = 0;
    local_5a0 = 0x20;
    local_598 = 0;
    local_588 = 0;
    local_590 = 0;
    local_500 = (uint *)0x0;
    local_5a8 = 0;
    local_580[0] = 0;
                    /* try { // try from 00b29b96 to 00b29b9a has its CatchHandler @ 00b2ae95 */
    CEGUI::String::grow((ulong)&local_5a8);
    puVar15 = local_580;
    if (0x20 < local_5a0) {
      puVar15 = local_500;
    }
    pbVar13 = (byte *)0xfd0c0d;
    do {
      bVar6 = *pbVar13;
      pbVar13 = pbVar13 + 1;
      *puVar15 = (uint)bVar6;
      puVar15 = puVar15 + 1;
    } while (pbVar13 != (byte *)0xfd0c12);
    local_5a8 = 5;
    puVar15 = local_56c;
    if (0x20 < local_5a0) {
      puVar15 = local_500 + 5;
    }
    *puVar15 = 0;
                    /* try { // try from 00b29c05 to 00b29c09 has its CatchHandler @ 00b2ae75 */
    CEGUI::PropertySet::setProperty(*(String **)(this + lVar18 * 8 + 0xd0),(String *)&local_5a8);
                    /* try { // try from 00b29c0d to 00b29c11 has its CatchHandler @ 00b2ae95 */
    CEGUI::String::~String((String *)&local_5a8);
    CEGUI::String::~String((String *)&local_658);
  }
  else {
    if (*(uint *)(param_1 + 0x3e0) < 2) {
      CEGUI::String::String(local_398,"onesocketglow");
                    /* try { // try from 00b2ace4 to 00b2acfb has its CatchHandler @ 00b2ad72 */
      CEGUI::Imageset::getImage(*(String **)(this + 0xf8));
      CEGUI::PropertyHelper::imageToString(local_448);
                    /* try { // try from 00b2ad0c to 00b2ad10 has its CatchHandler @ 00b2ad6b */
      CEGUI::String::String(local_4f8,"Image");
                    /* try { // try from 00b2ad24 to 00b2ad28 has its CatchHandler @ 00b2ad69 */
      CEGUI::PropertySet::setProperty(*(String **)(this + lVar18 * 8 + 0xd0),local_4f8);
                    /* try { // try from 00b2ad2c to 00b2ad30 has its CatchHandler @ 00b2ad6b */
      CEGUI::String::~String(local_4f8);
                    /* try { // try from 00b2ad34 to 00b2ad38 has its CatchHandler @ 00b2ad72 */
      CEGUI::String::~String((String *)local_448);
      CEGUI::String::~String(local_398);
    }
    else {
      local_180 = 0x20;
      local_178 = 0;
      local_168 = 0;
      local_170 = 0;
      local_e0 = (uint *)0x0;
      local_188 = 0;
      local_160[0] = 0;
      CEGUI::String::grow((ulong)&local_188);
      puVar15 = local_160;
      if (0x20 < local_180) {
        puVar15 = local_e0;
      }
      pcVar12 = "twosocketglow";
      do {
        bVar6 = *pcVar12;
        pcVar12 = pcVar12 + 1;
        *puVar15 = (uint)bVar6;
        puVar15 = puVar15 + 1;
      } while ((byte *)pcVar12 != (byte *)0xfe60d0);
      local_188 = 0xd;
      puVar15 = local_12c;
      if (0x20 < local_180) {
        puVar15 = local_e0 + 0xd;
      }
      *puVar15 = 0;
                    /* try { // try from 00b2997c to 00b29993 has its CatchHandler @ 00b2ae9a */
      CEGUI::Imageset::getImage(*(String **)(this + 0xf8));
      CEGUI::PropertyHelper::imageToString(local_238);
      local_2e0 = 0x20;
      local_2d8 = 0;
      local_2c8 = 0;
      local_2d0 = 0;
      local_240 = (uint *)0x0;
      local_2e8 = 0;
      local_2c0[0] = 0;
                    /* try { // try from 00b299f7 to 00b299fb has its CatchHandler @ 00b2add2 */
      CEGUI::String::grow((ulong)&local_2e8);
      puVar15 = local_2c0;
      if (0x20 < local_2e0) {
        puVar15 = local_240;
      }
      pbVar13 = (byte *)0xfd0c0d;
      do {
        bVar6 = *pbVar13;
        pbVar13 = pbVar13 + 1;
        *puVar15 = (uint)bVar6;
        puVar15 = puVar15 + 1;
      } while (pbVar13 != (byte *)0xfd0c12);
      local_2e8 = 5;
      puVar15 = local_2ac;
      if (0x20 < local_2e0) {
        puVar15 = local_240 + 5;
      }
      *puVar15 = 0;
                    /* try { // try from 00b29a6e to 00b29a72 has its CatchHandler @ 00b2ada2 */
      CEGUI::PropertySet::setProperty(*(String **)(this + lVar18 * 8 + 0xd0),(String *)&local_2e8);
                    /* try { // try from 00b29a76 to 00b29a7a has its CatchHandler @ 00b2add2 */
      CEGUI::String::~String((String *)&local_2e8);
                    /* try { // try from 00b29a7e to 00b29a82 has its CatchHandler @ 00b2ae9a */
      CEGUI::String::~String((String *)local_238);
      CEGUI::String::~String((String *)&local_188);
    }
    CEGUI::Window::moveToFront();
  }
  uVar23 = (ulong)((float)(int)(fVar26 + (float)(uVar27 | uVar28)) + fVar2);
  if (1 < *(uint *)(param_1 + 0x3e0)) {
    CEGUI::Window::getSize();
    uVar27 = -(uint)(0.0 < local_70 * 0.0);
    uVar23 = (ulong)((float)(uVar23 & 0xffffffff) +
                    ((float)(int)((float)(~uVar27 & DAT_00fa86f4 | DAT_00fa4810 & uVar27) +
                                 local_70 * 0.0) + local_6c) * _DAT_00fe6520);
  }
  if (*(int *)(param_1 + 0x3f0) != 0) {
    uVar27 = 0;
    do {
      if (uVar27 < *(uint *)(param_1 + 0x3f4)) {
        this_00 = *(CEquipment **)((ulong)uVar27 * 8 + *(long *)(param_1 + 1000));
        pUVar21 = *(UVector2 **)(this_00 + 0x2c8);
        if (pUVar21 != (UVector2 *)0x0) goto LAB_00b29d0a;
LAB_00b29e60:
        CEquipment::createIcon(this_00,*(CGameUI **)(this + 0x80),false);
        pUVar21 = *(UVector2 **)(this_00 + 0x2c8);
        if (pUVar21 != (UVector2 *)0x0) {
          CEGUI::EventSet::setMutedState((bool)((char)pUVar21 + '8'));
          pUVar21[0x3e2] = (UVector2)0x1;
          goto LAB_00b29d0a;
        }
      }
      else {
        this_00 = (CEquipment *)**(long **)(param_1 + 1000);
        pUVar21 = *(UVector2 **)(this_00 + 0x2c8);
        if (pUVar21 == (UVector2 *)0x0) goto LAB_00b29e60;
LAB_00b29d0a:
        if (*(Window **)(pUVar21 + 0xb0) != (Window *)0x0) {
          CEGUI::Window::removeChildWindow(*(Window **)(pUVar21 + 0xb0));
        }
        CEGUI::Window::addChildWindow(*(Window **)(this + 0x30));
        local_84 = (float)((long)((float)(int)((float)(~uVar25 & uVar9 | uVar8 & uVar25) +
                                              fVar3 * 0.0) + fVar4) & 0xffffffff);
        local_7c = (float)(uVar23 & 0xffffffff);
        local_88 = 0;
        local_80 = 0;
                    /* try { // try from 00b29d74 to 00b29d78 has its CatchHandler @ 00b2ae62 */
        CEGUI::Window::setPosition(pUVar21);
        CEGUI::Window::getSize();
                    /* try { // try from 00b29d96 to 00b29d9a has its CatchHandler @ 00b2ae67 */
        CEGUI::Window::setSize(pUVar21);
        CEGUI::Window::moveToFront();
        pUVar21[0x3e2] = (UVector2)0x1;
      }
      uVar27 = uVar27 + 1;
      CEGUI::Window::getSize();
      uVar28 = -(uint)(0.0 < local_a0 * 0.0);
      if (*(uint *)(param_1 + 0x3f0) <= uVar27) break;
      uVar23 = (ulong)((float)(uVar23 & 0xffffffff) +
                      ((float)(int)((float)(~uVar28 & DAT_00fa86f4 | DAT_00fa4810 & uVar28) +
                                   local_a0 * 0.0) + local_9c) * DAT_00fa4830);
    } while( true );
  }
  cVar7 = (**(code **)(*(long *)param_1 + 0x2f8))(param_1,*(undefined8 *)(this + 0x60),0);
  if (cVar7 == '\0') {
    cVar7 = (**(code **)(*(long *)param_1 + 0x2b0))(param_1);
    if (cVar7 == '\0') {
      pSVar22 = (String *)&local_10a8;
      local_10a0 = 0x20;
      local_1098 = 0;
      local_1088 = 0;
      local_1090 = 0;
      local_1000 = (uint *)0x0;
      local_10a8 = 0;
      local_1080[0] = 0;
      CEGUI::String::grow((ulong)pSVar22);
      puVar15 = local_1080;
      if (0x20 < local_10a0) {
        puVar15 = local_1000;
      }
      pbVar13 = (byte *)0xfe60e3;
      do {
        bVar6 = *pbVar13;
        pbVar13 = pbVar13 + 1;
        *puVar15 = (uint)bVar6;
        puVar15 = puVar15 + 1;
      } while (pbVar13 != (byte *)0xfe60ee);
      local_10a8 = 0xb;
      puVar15 = local_1054;
      if (0x20 < local_10a0) {
        puVar15 = local_1000 + 0xb;
      }
      *puVar15 = 0;
                    /* try { // try from 00b2a814 to 00b2a82b has its CatchHandler @ 00b2adc4 */
      CEGUI::Imageset::getImage(*(String **)(this + 0xf8));
      CEGUI::PropertyHelper::imageToString(local_1158);
      local_1200 = 0x20;
      local_11f8 = 0;
      local_11e8 = 0;
      local_11f0 = 0;
      local_1160 = (uint *)0x0;
      local_1208 = 0;
      local_11e0[0] = 0;
                    /* try { // try from 00b2a88f to 00b2a893 has its CatchHandler @ 00b2adc6 */
      CEGUI::String::grow((ulong)&local_1208);
      puVar15 = local_11e0;
      if (0x20 < local_1200) {
        puVar15 = local_1160;
      }
      pbVar13 = (byte *)0xfd0c0d;
      do {
        bVar6 = *pbVar13;
        pbVar13 = pbVar13 + 1;
        *puVar15 = (uint)bVar6;
        puVar15 = puVar15 + 1;
      } while (pbVar13 != (byte *)0xfd0c12);
      local_1208 = 5;
      puVar15 = local_11cc;
      if (0x20 < local_1200) {
        puVar15 = local_1160 + 5;
      }
      *puVar15 = 0;
                    /* try { // try from 00b2a8fe to 00b2a902 has its CatchHandler @ 00b2aea5 */
      CEGUI::PropertySet::setProperty(*(String **)(this + lVar18 * 8 + 200),(String *)&local_1208);
                    /* try { // try from 00b2a906 to 00b2a90a has its CatchHandler @ 00b2adc6 */
      CEGUI::String::~String((String *)&local_1208);
                    /* try { // try from 00b2a90e to 00b2a912 has its CatchHandler @ 00b2adc4 */
      CEGUI::String::~String((String *)local_1158);
    }
    else {
      pSVar22 = (String *)&local_e98;
      local_e90 = 0x20;
      local_e88 = 0;
      local_e78 = 0;
      local_e80 = 0;
      local_df0 = (uint *)0x0;
      local_e98 = 0;
      local_e70[0] = 0;
      CEGUI::String::grow((ulong)pSVar22);
      puVar15 = local_e70;
      if (0x20 < local_e90) {
        puVar15 = local_df0;
      }
      pcVar12 = "blueredslotglow";
      do {
        bVar6 = *pcVar12;
        pcVar12 = pcVar12 + 1;
        *puVar15 = (uint)bVar6;
        puVar15 = puVar15 + 1;
      } while ((byte *)pcVar12 != (byte *)0xfe60ee);
      local_e98 = 0xf;
      puVar15 = local_e34;
      if (0x20 < local_e90) {
        puVar15 = local_df0 + 0xf;
      }
      *puVar15 = 0;
                    /* try { // try from 00b2a51c to 00b2a533 has its CatchHandler @ 00b2ae6c */
      CEGUI::Imageset::getImage(*(String **)(this + 0xf8));
      CEGUI::PropertyHelper::imageToString(local_f48);
      local_ff0 = 0x20;
      local_fe8 = 0;
      local_fd8 = 0;
      local_fe0 = 0;
      local_f50 = (uint *)0x0;
      local_ff8 = 0;
      local_fd0[0] = 0;
                    /* try { // try from 00b2a597 to 00b2a59b has its CatchHandler @ 00b2ae9f */
      CEGUI::String::grow((ulong)&local_ff8);
      puVar15 = local_fd0;
      if (0x20 < local_ff0) {
        puVar15 = local_f50;
      }
      pbVar13 = (byte *)0xfd0c0d;
      do {
        bVar6 = *pbVar13;
        pbVar13 = pbVar13 + 1;
        *puVar15 = (uint)bVar6;
        puVar15 = puVar15 + 1;
      } while (pbVar13 != (byte *)0xfd0c12);
      local_ff8 = 5;
      puVar15 = local_fbc;
      if (0x20 < local_ff0) {
        puVar15 = local_f50 + 5;
      }
      *puVar15 = 0;
                    /* try { // try from 00b2a606 to 00b2a60a has its CatchHandler @ 00b2adc2 */
      CEGUI::PropertySet::setProperty(*(String **)(this + lVar18 * 8 + 200),(String *)&local_ff8);
                    /* try { // try from 00b2a60e to 00b2a612 has its CatchHandler @ 00b2ae9f */
      CEGUI::String::~String((String *)&local_ff8);
                    /* try { // try from 00b2a616 to 00b2a61a has its CatchHandler @ 00b2ae6c */
      CEGUI::String::~String((String *)local_f48);
    }
LAB_00b2a0a3:
    CEGUI::String::~String(pSVar22);
  }
  else {
    cVar7 = CBaseUnit::ISA((CBaseUnit *)param_1,0x36);
    if (cVar7 != '\0') {
      pSVar22 = (String *)&local_708;
      local_700 = 0x20;
      local_6f8 = 0;
      local_6e8 = 0;
      local_6f0 = 0;
      local_660 = (uint *)0x0;
      local_708 = 0;
      local_6e0[0] = 0;
      CEGUI::String::grow((ulong)pSVar22);
      puVar15 = local_6e0;
      if (0x20 < local_700) {
        puVar15 = local_660;
      }
      pcVar12 = "goldslotglow";
      do {
        bVar6 = *pcVar12;
        pcVar12 = pcVar12 + 1;
        *puVar15 = (uint)bVar6;
        puVar15 = puVar15 + 1;
      } while ((byte *)pcVar12 != (byte *)0xfe60a7);
      local_708 = 0xc;
      puVar15 = local_6b0;
      if (0x20 < local_700) {
        puVar15 = local_660 + 0xc;
      }
      *puVar15 = 0;
                    /* try { // try from 00b29fa4 to 00b29fbb has its CatchHandler @ 00b2adbc */
      CEGUI::Imageset::getImage(*(String **)(this + 0xf8));
      CEGUI::PropertyHelper::imageToString(local_7b8);
      local_860 = 0x20;
      local_858 = 0;
      local_848 = 0;
      local_850 = 0;
      local_7c0 = (uint *)0x0;
      local_868 = 0;
      local_840[0] = 0;
                    /* try { // try from 00b2a01f to 00b2a023 has its CatchHandler @ 00b2adb7 */
      CEGUI::String::grow((ulong)&local_868);
      puVar15 = local_840;
      if (0x20 < local_860) {
        puVar15 = local_7c0;
      }
      pbVar13 = (byte *)0xfd0c0d;
      do {
        bVar6 = *pbVar13;
        pbVar13 = pbVar13 + 1;
        *puVar15 = (uint)bVar6;
        puVar15 = puVar15 + 1;
      } while (pbVar13 != (byte *)0xfd0c12);
      local_868 = 5;
      puVar15 = local_82c;
      if (0x20 < local_860) {
        puVar15 = local_7c0 + 5;
      }
      *puVar15 = 0;
                    /* try { // try from 00b2a08e to 00b2a092 has its CatchHandler @ 00b2ae51 */
      CEGUI::PropertySet::setProperty(*(String **)(this + lVar18 * 8 + 200),(String *)&local_868);
                    /* try { // try from 00b2a096 to 00b2a09a has its CatchHandler @ 00b2adb7 */
      CEGUI::String::~String((String *)&local_868);
                    /* try { // try from 00b2a09e to 00b2a0a2 has its CatchHandler @ 00b2adbc */
      CEGUI::String::~String((String *)local_7b8);
      goto LAB_00b2a0a3;
    }
    cVar7 = (**(code **)(*(long *)param_1 + 0x2b0))(param_1);
    if (cVar7 == '\0') {
      pSVar22 = (String *)&local_de8;
      local_de0 = 0x20;
      local_dd8 = 0;
      local_dc8 = 0;
      local_dd0 = 0;
      local_d40 = (undefined4 *)0x0;
      local_de8 = 0;
      local_dc0[0] = 0;
      CEGUI::String::grow((ulong)pSVar22);
      local_de8 = 0;
      puVar16 = local_dc0;
      if (0x20 < local_de0) {
        puVar16 = local_d40;
      }
      *puVar16 = 0;
      local_d30 = 0x20;
      local_d28 = 0;
      local_d18 = 0;
      local_d20 = 0;
      local_c90 = (uint *)0x0;
      local_d38 = 0;
      local_d10[0] = 0;
                    /* try { // try from 00b2aa64 to 00b2aa68 has its CatchHandler @ 00b2ad9d */
      CEGUI::String::grow((ulong)&local_d38);
      puVar15 = local_d10;
      if (0x20 < local_d30) {
        puVar15 = local_c90;
      }
      pbVar13 = (byte *)0xfd0c0d;
      do {
        bVar6 = *pbVar13;
        pbVar13 = pbVar13 + 1;
        *puVar15 = (uint)bVar6;
        puVar15 = puVar15 + 1;
      } while (pbVar13 != (byte *)0xfd0c12);
      local_d38 = 5;
      puVar15 = local_cfc;
      if (0x20 < local_d30) {
        puVar15 = local_c90 + 5;
      }
      *puVar15 = 0;
                    /* try { // try from 00b2aae6 to 00b2aaea has its CatchHandler @ 00b2ad82 */
      CEGUI::PropertySet::setProperty(*(String **)(this + lVar18 * 8 + 200),(String *)&local_d38);
                    /* try { // try from 00b2aaee to 00b2aaf2 has its CatchHandler @ 00b2ad9d */
      CEGUI::String::~String((String *)&local_d38);
      goto LAB_00b2a0a3;
    }
    cVar7 = CBaseUnit::ISA((CBaseUnit *)param_1,0x37);
    if (cVar7 == '\0') {
      pSVar22 = local_b28;
      CEGUI::String::String(pSVar22,"greenslotglow");
                    /* try { // try from 00b2ac6b to 00b2ac82 has its CatchHandler @ 00b2aed5 */
      CEGUI::Imageset::getImage(*(String **)(this + 0xf8));
      CEGUI::PropertyHelper::imageToString(local_bd8);
                    /* try { // try from 00b2ac93 to 00b2ac97 has its CatchHandler @ 00b2aec5 */
      CEGUI::String::String(local_c88,"Image");
                    /* try { // try from 00b2acab to 00b2acaf has its CatchHandler @ 00b2aeb5 */
      CEGUI::PropertySet::setProperty(*(String **)(this + lVar18 * 8 + 200),local_c88);
                    /* try { // try from 00b2acb3 to 00b2acb7 has its CatchHandler @ 00b2aec5 */
      CEGUI::String::~String(local_c88);
                    /* try { // try from 00b2acbb to 00b2acbf has its CatchHandler @ 00b2aed5 */
      CEGUI::String::~String((String *)local_bd8);
    }
    else {
      pSVar22 = local_918;
      CEGUI::String::String(pSVar22,"blueslotglow");
                    /* try { // try from 00b2a6e6 to 00b2a6fd has its CatchHandler @ 00b2ad79 */
      CEGUI::Imageset::getImage(*(String **)(this + 0xf8));
      CEGUI::PropertyHelper::imageToString(local_9c8);
                    /* try { // try from 00b2a70e to 00b2a712 has its CatchHandler @ 00b2ad77 */
      CEGUI::String::String(local_a78,"Image");
                    /* try { // try from 00b2a726 to 00b2a72a has its CatchHandler @ 00b2ad46 */
      CEGUI::PropertySet::setProperty(*(String **)(this + lVar18 * 8 + 200),local_a78);
                    /* try { // try from 00b2a72e to 00b2a732 has its CatchHandler @ 00b2ad77 */
      CEGUI::String::~String(local_a78);
                    /* try { // try from 00b2a736 to 00b2a73a has its CatchHandler @ 00b2ad79 */
      CEGUI::String::~String((String *)local_9c8);
    }
    CEGUI::String::~String(pSVar22);
  }
  if (local_12c8 != (UVector2 *)0x0) {
    CEGUI::Window::addChildWindow(*(Window **)(this + lVar18 * 8 + 0xd8));
    local_b4 = 0;
    local_b8 = 0;
    local_ac = 0x3f800000;
    local_b0 = 0;
                    /* try { // try from 00b2a107 to 00b2a10b has its CatchHandler @ 00b2add4 */
    CEGUI::Window::setPosition(local_12c8);
    local_c4 = 0;
    local_c8 = 0;
    local_bc = 0;
    local_c0 = 0;
                    /* try { // try from 00b2a145 to 00b2a149 has its CatchHandler @ 00b2addc */
    CEGUI::Window::setPosition(local_12c8);
    CEGUI::Window::getSize();
                    /* try { // try from 00b2a16f to 00b2a173 has its CatchHandler @ 00b2adf0 */
    CEGUI::Window::setSize(local_12c8);
    CEGUI::Window::moveToFront();
    *(CEnchantMenu **)(local_12c8 + 0x1d8) = this + lVar18 * 4 + 0xc0;
  }
  if (*(long *)(this + lVar18 * 8 + 0xe0) == 0) {
    return;
  }
  bVar24 = SUB81(*(long *)(this + lVar18 * 8 + 0xe0),0);
  if (*(int *)(param_1 + 0x238) < 2) {
    CEGUI::Window::setVisible(bVar24);
    return;
  }
  CEGUI::Window::setVisible(bVar24);
  STRINGS::GetValueAsString((STRINGS *)local_58,*(int *)(param_1 + 0x238));
                    /* try { // try from 00b2a1ef to 00b2a1f3 has its CatchHandler @ 00b2adf2 */
  std::operator+((char *)&local_48,(string *)&DAT_0103f7f3);
  if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_58[0] + -8);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
    }
  }
  pbVar13 = local_48;
  local_12b0 = 0x20;
  uVar23 = 0;
  local_12a8 = 0;
  local_1298 = 0;
  local_12a0 = 0;
  local_1210 = (uint *)0x0;
  local_12b8 = 0;
  local_1290[0] = 0;
  bVar6 = *local_48;
  while (bVar6 != 0) {
    uVar23 = uVar23 + 1;
    bVar6 = local_48[uVar23];
  }
  if (uVar23 == CEGUI::String::npos) {
                    /* try { // try from 00b2abbb to 00b2abbf has its CatchHandler @ 00b2af2c */
    std::string::string((string *)local_68,"Length for utf8 encoded string can not be \'npos\'",
                        local_3a);
    this_01 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00b2abd3 to 00b2abd7 has its CatchHandler @ 00b2af14 */
    std::length_error::length_error(this_01,(string *)local_68);
    if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_68[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
      }
    }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00b2abff to 00b2ac03 has its CatchHandler @ 00b2ae05 */
    __cxa_throw(this_01,&std::length_error::typeinfo,std::length_error::~length_error);
  }
  lVar10 = 0;
  uVar17 = uVar23;
  pbVar19 = local_48;
  while (uVar17 != 0) {
    bVar6 = *pbVar19;
    uVar14 = uVar17 - 1;
    pbVar20 = pbVar19 + 1;
    if ((char)bVar6 < '\0') {
      if (bVar6 < 0xe0) {
        uVar14 = uVar17 - 2;
        pbVar20 = pbVar19 + 2;
      }
      else if (bVar6 < 0xf0) {
        uVar14 = uVar17 - 3;
        pbVar20 = pbVar19 + 3;
      }
      else {
        uVar14 = uVar17 - 3;
        pbVar20 = pbVar19 + 4;
      }
    }
    lVar10 = lVar10 + 1;
    uVar17 = uVar14;
    pbVar19 = pbVar20;
  }
  CEGUI::String::grow((ulong)&local_12b8);
  puVar15 = local_1290;
  if (0x20 < local_12b0) {
    puVar15 = local_1210;
  }
  if (uVar23 == 0) {
    uVar23 = 0;
    if (*pbVar13 == 0) goto LAB_00b2a2c0;
    do {
      uVar23 = uVar23 + 1;
    } while (pbVar13[uVar23] != 0);
    bVar24 = uVar23 != 0 && local_12b0 != 0;
  }
  else {
    bVar24 = local_12b0 != 0;
  }
  if (bVar24) {
    uVar14 = 0;
    uVar17 = local_12b0;
    uVar8 = 0;
    while( true ) {
      bVar6 = pbVar13[uVar14];
      uVar25 = (uint)bVar6;
      uVar9 = uVar8 + 1;
      if ((char)bVar6 < '\0') {
        uVar25 = (uint)bVar6;
        if (bVar6 < 0xe0) {
          uVar14 = (ulong)uVar9;
          uVar9 = uVar8 + 2;
          uVar25 = pbVar13[uVar14] & 0x3f | (uVar25 & 0x1f) << 6;
        }
        else if (bVar6 < 0xf0) {
          uVar14 = (ulong)uVar9;
          uVar9 = uVar8 + 3;
          uVar25 = pbVar13[uVar8 + 2] & 0x3f | (uVar25 & 0xf) << 0xc | (pbVar13[uVar14] & 0x3f) << 6
          ;
        }
        else {
          uVar14 = (ulong)uVar9;
          uVar9 = uVar8 + 4;
          uVar25 = (pbVar13[uVar14] & 0x3f) << 0xc | pbVar13[uVar8 + 3] & 0x3f |
                   (uVar25 & 7) << 0x12 | (pbVar13[uVar8 + 2] & 0x3f) << 6;
        }
      }
      *puVar15 = uVar25;
      uVar14 = (ulong)uVar9;
      uVar17 = uVar17 - 1;
      if ((uVar23 <= uVar14) || (uVar17 == 0)) break;
      puVar15 = puVar15 + 1;
      uVar8 = uVar9;
    }
  }
LAB_00b2a2c0:
  puVar15 = local_1290;
  if (0x20 < local_12b0) {
    puVar15 = local_1210;
  }
  puVar15[lVar10] = 0;
  local_12b8 = lVar10;
                    /* try { // try from 00b2a2f1 to 00b2a2f5 has its CatchHandler @ 00b2ae18 */
  CEGUI::Window::setText(*(String **)(this + lVar18 * 8 + 0xe0));
                    /* try { // try from 00b2a2f9 to 00b2a37f has its CatchHandler @ 00b2ae05 */
  CEGUI::String::~String((String *)&local_12b8);
  if ((allocator *)(local_48 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    pbVar13 = local_48 + -8;
    iVar5 = *(int *)pbVar13;
    *(int *)pbVar13 = *(int *)pbVar13 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_48 + -0x18));
    }
  }
  return;
}

/* address=00b2af60
   symbol=CEnchantMenu::updateLayout */

/* WARNING: Removing unreachable block (ram,0x00b2df77) */
/* WARNING: Removing unreachable block (ram,0x00b2da49) */
/* WARNING: Removing unreachable block (ram,0x00b2dd95) */
/* WARNING: Removing unreachable block (ram,0x00b2dcfe) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CEnchantMenu::updateLayout() */

void __thiscall CEnchantMenu::updateLayout(CEnchantMenu *this)

{
  int *piVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  byte bVar5;
  CInventory *this_00;
  Window *pWVar6;
  CEquipment *this_01;
  char cVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  long lVar11;
  long lVar12;
  float *pfVar13;
  float *pfVar14;
  char *pcVar15;
  byte *pbVar16;
  ulong uVar17;
  uint *puVar18;
  undefined4 *puVar19;
  length_error *this_02;
  ulong uVar20;
  uint uVar21;
  byte *pbVar22;
  byte *pbVar23;
  ulong uVar24;
  UVector2 *pUVar25;
  wstring_conflict *this_03;
  String *pSVar26;
  CEquipment *this_04;
  bool bVar27;
  uint uVar28;
  uint uVar29;
  float fVar30;
  uint uVar31;
  float fVar32;
  uint uVar33;
  float fVar34;
  UVector2 *local_2368;
  String local_2348 [176];
  String local_2298 [176];
  String local_21e8 [176];
  String local_2138 [176];
  String local_2088 [176];
  String local_1fd8 [176];
  String local_1f28 [176];
  String local_1e78 [176];
  String local_1dc8 [176];
  String local_1d18 [176];
  String local_1c68 [176];
  String local_1bb8 [176];
  String local_1b08 [176];
  String local_1a58 [176];
  String local_19a8 [176];
  String local_18f8 [176];
  String local_1848 [176];
  String local_1798 [176];
  String local_16e8 [176];
  String local_1638 [176];
  String local_1588 [176];
  String local_14d8 [176];
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
  uint local_1350 [5];
  uint local_133c [27];
  uint *local_12d0;
  String local_12c8 [176];
  String local_1218 [176];
  String local_1168 [176];
  Image local_10b8 [176];
  String local_1008 [176];
  String local_f58 [176];
  Image local_ea8 [176];
  String local_df8 [176];
  undefined8 local_d48;
  ulong local_d40;
  undefined8 local_d38;
  undefined8 local_d30;
  undefined8 local_d28;
  uint local_d20 [5];
  uint local_d0c [27];
  uint *local_ca0;
  Image local_c98 [176];
  undefined8 local_be8;
  ulong local_be0;
  undefined8 local_bd8;
  undefined8 local_bd0;
  undefined8 local_bc8;
  uint local_bc0 [12];
  uint local_b90 [20];
  uint *local_b40;
  long local_b38;
  ulong local_b30;
  undefined8 local_b28;
  undefined8 local_b20;
  undefined8 local_b18;
  uint local_b10 [32];
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
  String local_928 [176];
  Image local_878 [176];
  String local_7c8 [176];
  undefined8 local_718;
  ulong local_710;
  undefined8 local_708;
  undefined8 local_700;
  undefined8 local_6f8;
  uint local_6f0 [5];
  uint local_6dc [27];
  uint *local_670;
  Image local_668 [176];
  undefined8 local_5b8;
  ulong local_5b0;
  undefined8 local_5a8;
  undefined8 local_5a0;
  undefined8 local_598;
  uint local_590 [13];
  uint local_55c [19];
  uint *local_510;
  undefined4 local_4d8;
  undefined4 local_4d4;
  undefined4 local_4d0;
  undefined4 local_4cc;
  undefined4 local_4c8;
  undefined4 local_4c4;
  undefined4 local_4c0;
  undefined4 local_4bc;
  float local_4b0;
  float local_4ac;
  undefined4 local_498;
  float local_494;
  undefined4 local_490;
  float local_48c;
  float local_480;
  float local_47c;
  long local_478 [2];
  uchar *local_468 [2];
  wstring_conflict local_458 [16];
  uchar *local_448 [2];
  wstring_conflict local_438 [16];
  uchar *local_428 [2];
  wstring_conflict local_418 [16];
  uchar *local_408 [2];
  wstring_conflict local_3f8 [16];
  wstring_conflict local_3e8 [16];
  wstring_conflict local_3d8 [16];
  wstring_conflict local_3c8 [16];
  wstring_conflict local_3b8 [16];
  uchar *local_3a8 [2];
  wstring_conflict local_398 [16];
  wstring_conflict local_388 [16];
  uchar *local_378 [2];
  wstring_conflict local_368 [16];
  wstring_conflict local_358 [16];
  uchar *local_348 [2];
  wstring_conflict local_338 [16];
  wstring_conflict local_328 [16];
  uchar *local_318 [2];
  wstring_conflict local_308 [16];
  wstring_conflict local_2f8 [16];
  uchar *local_2e8 [2];
  wstring_conflict local_2d8 [16];
  wstring_conflict local_2c8 [16];
  uchar *local_2b8 [2];
  wstring_conflict local_2a8 [16];
  wstring_conflict local_298 [16];
  uchar *local_288 [2];
  wstring_conflict local_278 [16];
  wstring_conflict local_268 [16];
  uchar *local_258 [2];
  wstring_conflict local_248 [16];
  wstring_conflict local_238 [16];
  STRINGS local_228 [16];
  wstring_conflict local_218 [16];
  wstring_conflict local_208 [16];
  wstring_conflict local_1f8 [16];
  wstring_conflict local_1e8 [16];
  wstring_conflict local_1d8 [16];
  uchar *local_1c8 [2];
  wstring_conflict local_1b8 [16];
  wstring_conflict local_1a8 [16];
  uchar *local_198 [2];
  wstring_conflict local_188 [16];
  wstring_conflict local_178 [16];
  uchar *local_168 [2];
  wstring_conflict local_158 [16];
  wstring_conflict local_148 [16];
  STRINGS local_138 [16];
  wstring_conflict local_128 [16];
  wstring_conflict local_118 [16];
  wstring_conflict local_108 [16];
  wstring_conflict local_f8 [16];
  STRINGS local_e8 [16];
  wstring_conflict local_d8 [16];
  wstring_conflict local_c8 [16];
  wstring_conflict local_b8 [16];
  uchar *local_a8 [2];
  wstring_conflict local_98 [16];
  wstring_conflict local_88 [16];
  long local_78 [2];
  byte *local_68 [2];
  long local_58 [2];
  allocator local_48 [2];
  allocator local_46;
  allocator local_45;
  allocator local_44;
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

  if (this[0x70] == (CEnchantMenu)0x0) {
    return;
  }
  if (*(long *)(this + 0x60) == 0) {
    return;
  }
  this_00 = *(CInventory **)(*(long *)(this + 0x60) + 0x490);
  if (this_00 == (CInventory *)0x0) {
    return;
  }
  while (pWVar6 = *(Window **)(this + 0x30),
        *(long *)(pWVar6 + 0x80) - *(long *)(pWVar6 + 0x78) >> 3 != 0) {
    CEGUI::Window::removeChildWindow(pWVar6);
  }
  std::wstring::wstring((wstring_conflict *)local_58,(wstring_conflict *)&::EMPTY_WSTRING);
  pWVar6 = *(Window **)(this + 0xd8);
  if (pWVar6 == (Window *)0x0) goto switchD_00b2c090_caseD_17;
  if (*(long *)(pWVar6 + 0x80) - *(long *)(pWVar6 + 0x78) >> 3 != 0) {
    CEGUI::Window::removeChildWindow(pWVar6);
  }
                    /* try { // try from 00b2b011 to 00b2b204 has its CatchHandler @ 00b2df72 */
  lVar11 = CInventory::getEquipmentRefInSlot(this_00,*(uint *)(this + 0xc0));
  if (lVar11 == 0) {
    if (*(long *)(this + 0xd8) != 0) {
      if ((updateLayout()::g_PlaceHereToEnchant == '\0') &&
         (iVar10 = __cxa_guard_acquire(&updateLayout()::g_PlaceHereToEnchant), iVar10 != 0)) {
        updateLayout()::g_PlaceHereToEnchant = &DAT_01424558;
        __cxa_guard_release(&updateLayout()::g_PlaceHereToEnchant);
        __cxa_atexit(std::wstring::~wstring,&updateLayout()::g_PlaceHereToEnchant,&__dso_handle);
      }
      if (*(long *)(updateLayout()::g_PlaceHereToEnchant + -6) == 0) {
        CStringTranslate::getSinglton();
        CStringTranslate::getTranslateString((wchar_t *)local_3b8);
                    /* try { // try from 00b2ccfc to 00b2cd00 has its CatchHandler @ 00b2db85 */
        std::wstring::assign((wstring_conflict *)&updateLayout()::g_PlaceHereToEnchant);
                    /* try { // try from 00b2cd04 to 00b2cd6a has its CatchHandler @ 00b2df72 */
        std::wstring::~wstring(local_3b8);
      }
      if ((updateLayout()::g_PlaceItemHereToDestroySocketable == '\0') &&
         (iVar10 = __cxa_guard_acquire(&updateLayout()::g_PlaceItemHereToDestroySocketable),
         iVar10 != 0)) {
        updateLayout()::g_PlaceItemHereToDestroySocketable = &DAT_01424558;
        __cxa_guard_release(&updateLayout()::g_PlaceItemHereToDestroySocketable);
        __cxa_atexit(std::wstring::~wstring,&updateLayout()::g_PlaceItemHereToDestroySocketable,
                     &__dso_handle);
      }
      if (*(long *)(updateLayout()::g_PlaceItemHereToDestroySocketable + -6) == 0) {
        CStringTranslate::getSinglton();
        CStringTranslate::getTranslateString((wchar_t *)local_3c8);
                    /* try { // try from 00b2cd73 to 00b2cd77 has its CatchHandler @ 00b2db95 */
        std::wstring::assign
                  ((wstring_conflict *)&updateLayout()::g_PlaceItemHereToDestroySocketable);
                    /* try { // try from 00b2cd7b to 00b2cd7f has its CatchHandler @ 00b2df72 */
        std::wstring::~wstring(local_3c8);
      }
      if ((updateLayout()::g_PlaceItemHereToDestroyGems == '\0') &&
         (iVar10 = __cxa_guard_acquire(&updateLayout()::g_PlaceItemHereToDestroyGems), iVar10 != 0))
      {
        updateLayout()::g_PlaceItemHereToDestroyGems = &DAT_01424558;
        __cxa_guard_release(&updateLayout()::g_PlaceItemHereToDestroyGems);
        __cxa_atexit(std::wstring::~wstring,&updateLayout()::g_PlaceItemHereToDestroyGems,
                     &__dso_handle);
      }
      if (*(long *)(updateLayout()::g_PlaceItemHereToDestroyGems + -6) == 0) {
        CStringTranslate::getSinglton();
        CStringTranslate::getTranslateString((wchar_t *)local_3d8);
                    /* try { // try from 00b2cc85 to 00b2cc89 has its CatchHandler @ 00b2db75 */
        std::wstring::assign((wstring_conflict *)&updateLayout()::g_PlaceItemHereToDestroyGems);
                    /* try { // try from 00b2cc8d to 00b2ccf3 has its CatchHandler @ 00b2df72 */
        std::wstring::~wstring(local_3d8);
      }
      if ((updateLayout()::g_PlaceItemHereToPassDown == '\0') &&
         (iVar10 = __cxa_guard_acquire(&updateLayout()::g_PlaceItemHereToPassDown), iVar10 != 0)) {
        updateLayout()::g_PlaceItemHereToPassDown = &DAT_01424558;
        __cxa_guard_release(&updateLayout()::g_PlaceItemHereToPassDown);
        __cxa_atexit(std::wstring::~wstring,&updateLayout()::g_PlaceItemHereToPassDown,&__dso_handle
                    );
      }
      if (*(long *)(updateLayout()::g_PlaceItemHereToPassDown + -6) == 0) {
                    /* try { // try from 00b2cbe9 to 00b2cc05 has its CatchHandler @ 00b2df72 */
        CStringTranslate::getSinglton();
        CStringTranslate::getTranslateString((wchar_t *)local_3e8);
                    /* try { // try from 00b2cc0e to 00b2cc12 has its CatchHandler @ 00b2db65 */
        std::wstring::assign((wstring_conflict *)&updateLayout()::g_PlaceItemHereToPassDown);
                    /* try { // try from 00b2cc16 to 00b2cc7c has its CatchHandler @ 00b2df72 */
        std::wstring::~wstring(local_3e8);
      }
      switch(*(undefined4 *)(this + 0x10c)) {
      case 0x15:
      case 0x16:
                    /* try { // try from 00b2cf38 to 00b2cf3c has its CatchHandler @ 00b2dbd5 */
        std::wstring::wstring(local_3f8,updateLayout()::g_PlaceHereToEnchant,&local_43);
                    /* try { // try from 00b2cf4b to 00b2cf4f has its CatchHandler @ 00b2dbc5 */
        STRINGS::StringConvertToUTF8((wstring_conflict *)local_408);
                    /* try { // try from 00b2cf63 to 00b2cf67 has its CatchHandler @ 00b2dbb5 */
        CEGUI::String::String(local_1d18,local_408[0]);
                    /* try { // try from 00b2cf6f to 00b2cf73 has its CatchHandler @ 00b2dba5 */
        CEGUI::Window::setText(*(String **)(this + 0x48));
                    /* try { // try from 00b2cf77 to 00b2cf7b has its CatchHandler @ 00b2dbb5 */
        CEGUI::String::~String(local_1d18);
                    /* try { // try from 00b2cf7f to 00b2cf83 has its CatchHandler @ 00b2dbc5 */
        std::string::~string((string *)local_408);
                    /* try { // try from 00b2cf87 to 00b2cf8b has its CatchHandler @ 00b2dbd5 */
        std::wstring::~wstring(local_3f8);
        break;
      case 0x19:
                    /* try { // try from 00b2cec5 to 00b2cec9 has its CatchHandler @ 00b2da02 */
        std::wstring::wstring(local_438,updateLayout()::g_PlaceItemHereToDestroyGems,&local_45);
                    /* try { // try from 00b2ced8 to 00b2cedc has its CatchHandler @ 00b2d9fc */
        STRINGS::StringConvertToUTF8((wstring_conflict *)local_448);
                    /* try { // try from 00b2cef0 to 00b2cef4 has its CatchHandler @ 00b2d9f7 */
        CEGUI::String::String(local_1e78,local_448[0]);
                    /* try { // try from 00b2cefc to 00b2cf00 has its CatchHandler @ 00b2d9d7 */
        CEGUI::Window::setText(*(String **)(this + 0x48));
                    /* try { // try from 00b2cf04 to 00b2cf08 has its CatchHandler @ 00b2d9f7 */
        CEGUI::String::~String(local_1e78);
                    /* try { // try from 00b2cf0c to 00b2cf10 has its CatchHandler @ 00b2d9fc */
        std::string::~string((string *)local_448);
                    /* try { // try from 00b2cf14 to 00b2cf18 has its CatchHandler @ 00b2da02 */
        std::wstring::~wstring(local_438);
        break;
      case 0x1a:
                    /* try { // try from 00b2ce52 to 00b2ce56 has its CatchHandler @ 00b2dc85 */
        std::wstring::wstring
                  (local_418,updateLayout()::g_PlaceItemHereToDestroySocketable,&local_44);
                    /* try { // try from 00b2ce65 to 00b2ce69 has its CatchHandler @ 00b2dc75 */
        STRINGS::StringConvertToUTF8((wstring_conflict *)local_428);
                    /* try { // try from 00b2ce7d to 00b2ce81 has its CatchHandler @ 00b2dc65 */
        CEGUI::String::String(local_1dc8,local_428[0]);
                    /* try { // try from 00b2ce89 to 00b2ce8d has its CatchHandler @ 00b2dc55 */
        CEGUI::Window::setText(*(String **)(this + 0x48));
                    /* try { // try from 00b2ce91 to 00b2ce95 has its CatchHandler @ 00b2dc65 */
        CEGUI::String::~String(local_1dc8);
                    /* try { // try from 00b2ce99 to 00b2ce9d has its CatchHandler @ 00b2dc75 */
        std::string::~string((string *)local_428);
                    /* try { // try from 00b2cea1 to 00b2cea5 has its CatchHandler @ 00b2dc85 */
        std::wstring::~wstring(local_418);
        break;
      case 0x1b:
                    /* try { // try from 00b2cddf to 00b2cde3 has its CatchHandler @ 00b2da14 */
        std::wstring::wstring(local_458,updateLayout()::g_PlaceItemHereToPassDown,&local_46);
                    /* try { // try from 00b2cdf2 to 00b2cdf6 has its CatchHandler @ 00b2da12 */
        STRINGS::StringConvertToUTF8((wstring_conflict *)local_468);
                    /* try { // try from 00b2ce0a to 00b2ce0e has its CatchHandler @ 00b2da0c */
        CEGUI::String::String(local_1f28,local_468[0]);
                    /* try { // try from 00b2ce16 to 00b2ce1a has its CatchHandler @ 00b2da0a */
        CEGUI::Window::setText(*(String **)(this + 0x48));
                    /* try { // try from 00b2ce1e to 00b2ce22 has its CatchHandler @ 00b2da0c */
        CEGUI::String::~String(local_1f28);
                    /* try { // try from 00b2ce26 to 00b2ce2a has its CatchHandler @ 00b2da12 */
        std::string::~string((string *)local_468);
                    /* try { // try from 00b2ce2e to 00b2ce32 has its CatchHandler @ 00b2da14 */
        std::wstring::~wstring(local_458);
      }
                    /* try { // try from 00b2c598 to 00b2c5b1 has its CatchHandler @ 00b2df72 */
      CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0xe0),0));
      CEGUI::String::String(local_2088,"");
                    /* try { // try from 00b2c5c2 to 00b2c5c6 has its CatchHandler @ 00b2df55 */
      CEGUI::String::String(local_1fd8,"Image");
                    /* try { // try from 00b2c5d4 to 00b2c5d8 has its CatchHandler @ 00b2db15 */
      CEGUI::PropertySet::setProperty(*(String **)(this + 0xd0),local_1fd8);
                    /* try { // try from 00b2c5dc to 00b2c5e0 has its CatchHandler @ 00b2df55 */
      CEGUI::String::~String(local_1fd8);
                    /* try { // try from 00b2c5e4 to 00b2c5ff has its CatchHandler @ 00b2df72 */
      CEGUI::String::~String(local_2088);
      CEGUI::Window::getSize();
                    /* try { // try from 00b2c60a to 00b2c60e has its CatchHandler @ 00b2db0a */
      CEGUI::Window::setSize(*(UVector2 **)(this + 0xd0));
                    /* try { // try from 00b2c61f to 00b2c623 has its CatchHandler @ 00b2df72 */
      CEGUI::String::String(local_21e8,"");
                    /* try { // try from 00b2c634 to 00b2c638 has its CatchHandler @ 00b2db05 */
      CEGUI::String::String(local_2138,"Image");
                    /* try { // try from 00b2c646 to 00b2c64a has its CatchHandler @ 00b2dafc */
      CEGUI::PropertySet::setProperty(*(String **)(this + 200),local_2138);
                    /* try { // try from 00b2c64e to 00b2c652 has its CatchHandler @ 00b2db05 */
      CEGUI::String::~String(local_2138);
                    /* try { // try from 00b2c656 to 00b2c671 has its CatchHandler @ 00b2df72 */
      CEGUI::String::~String(local_21e8);
      CEGUI::Window::getSize();
                    /* try { // try from 00b2c67c to 00b2c680 has its CatchHandler @ 00b2df47 */
      CEGUI::Window::setSize(*(UVector2 **)(this + 200));
                    /* try { // try from 00b2c68e to 00b2c692 has its CatchHandler @ 00b2df72 */
      CEGUI::String::String(local_2348,"");
                    /* try { // try from 00b2c6a3 to 00b2c6a7 has its CatchHandler @ 00b2df42 */
      CEGUI::String::String(local_2298,"Image");
                    /* try { // try from 00b2c6b5 to 00b2c6b9 has its CatchHandler @ 00b2dc95 */
      CEGUI::PropertySet::setProperty(*(String **)(this + 0xd8),local_2298);
                    /* try { // try from 00b2c6bd to 00b2c6c1 has its CatchHandler @ 00b2df42 */
      CEGUI::String::~String(local_2298);
                    /* try { // try from 00b2c6c5 to 00b2c6e3 has its CatchHandler @ 00b2df72 */
      CEGUI::String::~String(local_2348);
    }
    goto switchD_00b2c090_caseD_17;
  }
  this_01 = *(CEquipment **)(lVar11 + 0x10);
  local_2368 = *(UVector2 **)(this_01 + 0x2c8);
  if (local_2368 == (UVector2 *)0x0) {
                    /* try { // try from 00b2d206 to 00b2d323 has its CatchHandler @ 00b2df72 */
    CEquipment::createIcon(this_01,*(CGameUI **)(this + 0x80),false);
    local_2368 = *(UVector2 **)(this_01 + 0x2c8);
    if (local_2368 != (UVector2 *)0x0) {
      CEGUI::EventSet::setMutedState((bool)((char)local_2368 + '8'));
      local_2368[0x3e2] = (UVector2)0x1;
      goto LAB_00b2b038;
    }
  }
  else {
LAB_00b2b038:
    if (*(Window **)(local_2368 + 0xb0) != (Window *)0x0) {
      CEGUI::Window::removeChildWindow(*(Window **)(local_2368 + 0xb0));
    }
    CEGUI::Window::addChildWindow(*(Window **)(this + 0xd8));
  }
  lVar11 = CEGUI::Window::getPosition();
  lVar12 = CEGUI::Window::getPosition();
  fVar2 = *(float *)(lVar12 + 0xc);
  fVar34 = *(float *)(lVar11 + 0xc);
  fVar32 = (*(float *)(lVar11 + 8) + *(float *)(lVar12 + 8)) * 0.0;
  uVar28 = -(uint)(0.0 < fVar32);
  uVar29 = DAT_00fa4810 & uVar28;
  uVar31 = ~uVar28 & DAT_00fa86f4;
  pfVar13 = (float *)CEGUI::Window::getPosition();
  pfVar14 = (float *)CEGUI::Window::getPosition();
  fVar3 = pfVar13[1];
  fVar4 = pfVar14[1];
  fVar30 = (*pfVar13 + *pfVar14) * 0.0;
  uVar28 = -(uint)(0.0 < fVar30);
  uVar33 = DAT_00fa4810 & uVar28;
  uVar28 = ~uVar28 & DAT_00fa86f4;
  if (((this_01[0x348] == (CEquipment)0x0) || (*(int *)(this_01 + 0x3e0) == 0)) ||
     (cVar7 = CEGUI::Window::isVisible(SUB81(*(undefined8 *)(*(long *)(this + 0xd8) + 0xb0),0)),
     cVar7 == '\0')) {
    local_a80 = 0x20;
    local_a78 = 0;
    local_a68 = 0;
    local_a70 = 0;
    local_9e0 = (undefined4 *)0x0;
    local_a88 = 0;
    local_a60[0] = 0;
    CEGUI::String::grow((ulong)&local_a88);
    local_a88 = 0;
    puVar19 = local_a60;
    if (0x20 < local_a80) {
      puVar19 = local_9e0;
    }
    *puVar19 = 0;
    local_9d0 = 0x20;
    local_9c8 = 0;
    local_9b8 = 0;
    local_9c0 = 0;
    local_930 = (uint *)0x0;
    local_9d8 = 0;
    local_9b0[0] = 0;
                    /* try { // try from 00b2b485 to 00b2b489 has its CatchHandler @ 00b2df65 */
    CEGUI::String::grow((ulong)&local_9d8);
    puVar18 = local_9b0;
    if (0x20 < local_9d0) {
      puVar18 = local_930;
    }
    pbVar16 = (byte *)0xfd0c0d;
    do {
      bVar5 = *pbVar16;
      pbVar16 = pbVar16 + 1;
      *puVar18 = (uint)bVar5;
      puVar18 = puVar18 + 1;
    } while (pbVar16 != (byte *)0xfd0c12);
    local_9d8 = 5;
    puVar18 = local_99c;
    if (0x20 < local_9d0) {
      puVar18 = local_930 + 5;
    }
    *puVar18 = 0;
                    /* try { // try from 00b2b500 to 00b2b504 has its CatchHandler @ 00b2df2a */
    CEGUI::PropertySet::setProperty(*(String **)(this + 0xd0),(String *)&local_9d8);
                    /* try { // try from 00b2b508 to 00b2b50c has its CatchHandler @ 00b2df65 */
    CEGUI::String::~String((String *)&local_9d8);
                    /* try { // try from 00b2b510 to 00b2b553 has its CatchHandler @ 00b2df72 */
    CEGUI::String::~String((String *)&local_a88);
  }
  else {
    if (*(uint *)(this_01 + 0x3e0) < 2) {
      if (*(uint *)(this_01 + 0x3e0) == 1) {
                    /* try { // try from 00b2cfae to 00b2cfb2 has its CatchHandler @ 00b2df72 */
        CEGUI::String::String(local_7c8,"onesocketglow");
                    /* try { // try from 00b2cfbd to 00b2cfd4 has its CatchHandler @ 00b2dfcf */
        CEGUI::Imageset::getImage(*(String **)(this + 0xf8));
        CEGUI::PropertyHelper::imageToString(local_878);
                    /* try { // try from 00b2cfe5 to 00b2cfe9 has its CatchHandler @ 00b2dfca */
        CEGUI::String::String(local_928,"Image");
                    /* try { // try from 00b2cff7 to 00b2cffb has its CatchHandler @ 00b2ded5 */
        CEGUI::PropertySet::setProperty(*(String **)(this + 0xd0),local_928);
                    /* try { // try from 00b2cfff to 00b2d003 has its CatchHandler @ 00b2dfca */
        CEGUI::String::~String(local_928);
                    /* try { // try from 00b2d007 to 00b2d00b has its CatchHandler @ 00b2dfcf */
        CEGUI::String::~String((String *)local_878);
                    /* try { // try from 00b2d00f to 00b2d050 has its CatchHandler @ 00b2df72 */
        CEGUI::String::~String(local_7c8);
      }
    }
    else {
      local_5b0 = 0x20;
      local_5a8 = 0;
      local_598 = 0;
      local_5a0 = 0;
      local_510 = (uint *)0x0;
      local_5b8 = 0;
      local_590[0] = 0;
      CEGUI::String::grow((ulong)&local_5b8);
      puVar18 = local_590;
      if (0x20 < local_5b0) {
        puVar18 = local_510;
      }
      pcVar15 = "twosocketglow";
      do {
        bVar5 = *pcVar15;
        pcVar15 = pcVar15 + 1;
        *puVar18 = (uint)bVar5;
        puVar18 = puVar18 + 1;
      } while ((byte *)pcVar15 != (byte *)0xfe60d0);
      local_5b8 = 0xd;
      puVar18 = local_55c;
      if (0x20 < local_5b0) {
        puVar18 = local_510 + 0xd;
      }
      *puVar18 = 0;
                    /* try { // try from 00b2b275 to 00b2b28c has its CatchHandler @ 00b2def5 */
      CEGUI::Imageset::getImage(*(String **)(this + 0xf8));
      CEGUI::PropertyHelper::imageToString(local_668);
      local_710 = 0x20;
      local_708 = 0;
      local_6f8 = 0;
      local_700 = 0;
      local_670 = (uint *)0x0;
      local_718 = 0;
      local_6f0[0] = 0;
                    /* try { // try from 00b2b2f0 to 00b2b2f4 has its CatchHandler @ 00b2da54 */
      CEGUI::String::grow((ulong)&local_718);
      puVar18 = local_6f0;
      if (0x20 < local_710) {
        puVar18 = local_670;
      }
      pbVar16 = (byte *)0xfd0c0d;
      do {
        bVar5 = *pbVar16;
        pbVar16 = pbVar16 + 1;
        *puVar18 = (uint)bVar5;
        puVar18 = puVar18 + 1;
      } while (pbVar16 != (byte *)0xfd0c12);
      local_718 = 5;
      puVar18 = local_6dc;
      if (0x20 < local_710) {
        puVar18 = local_670 + 5;
      }
      *puVar18 = 0;
                    /* try { // try from 00b2b367 to 00b2b36b has its CatchHandler @ 00b2d952 */
      CEGUI::PropertySet::setProperty(*(String **)(this + 0xd0),(String *)&local_718);
                    /* try { // try from 00b2b36f to 00b2b373 has its CatchHandler @ 00b2da54 */
      CEGUI::String::~String((String *)&local_718);
                    /* try { // try from 00b2b377 to 00b2b37b has its CatchHandler @ 00b2def5 */
      CEGUI::String::~String((String *)local_668);
                    /* try { // try from 00b2b37f to 00b2b3fc has its CatchHandler @ 00b2df72 */
      CEGUI::String::~String((String *)&local_5b8);
    }
    CEGUI::Window::moveToFront();
  }
  if (*(long *)(this + 0xe0) != 0) {
    bVar27 = SUB81(*(long *)(this + 0xe0),0);
    if (*(int *)(this_01 + 0x238) < 2) {
      CEGUI::Window::setVisible(bVar27);
    }
    else {
      CEGUI::Window::setVisible(bVar27);
      STRINGS::GetValueAsString((STRINGS *)local_78,*(int *)(this_01 + 0x238));
                    /* try { // try from 00b2b564 to 00b2b568 has its CatchHandler @ 00b2df15 */
      std::operator+((char *)local_68,(string *)&DAT_0103f7f3);
      if ((allocator *)(local_78[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_78[0] + -8);
        iVar10 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar10 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
        }
      }
      pbVar16 = local_68[0];
      local_b30 = 0x20;
      uVar24 = 0;
      local_b28 = 0;
      local_b18 = 0;
      local_b20 = 0;
      local_a90 = (uint *)0x0;
      local_b38 = 0;
      local_b10[0] = 0;
      bVar5 = *local_68[0];
      while (bVar5 != 0) {
        uVar24 = uVar24 + 1;
        bVar5 = local_68[0][uVar24];
      }
      if (uVar24 == CEGUI::String::npos) {
                    /* try { // try from 00b2d1b1 to 00b2d1b5 has its CatchHandler @ 00b2dcf9 */
        std::string::string((string *)local_478,"Length for utf8 encoded string can not be \'npos\'"
                            ,local_48);
        this_02 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00b2d1c9 to 00b2d1cd has its CatchHandler @ 00b2dcd4 */
        std::length_error::length_error(this_02,(string *)local_478);
        if ((allocator *)(local_478[0] + -0x18) !=
            (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_478[0] + -8);
          iVar10 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar10 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_478[0] + -0x18));
          }
        }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00b2d1f5 to 00b2d1f9 has its CatchHandler @ 00b2de1a */
        __cxa_throw(this_02,&std::length_error::typeinfo,std::length_error::~length_error);
      }
      lVar11 = 0;
      uVar20 = uVar24;
      pbVar22 = local_68[0];
      while (uVar20 != 0) {
        bVar5 = *pbVar22;
        uVar17 = uVar20 - 1;
        pbVar23 = pbVar22 + 1;
        if ((char)bVar5 < '\0') {
          if (bVar5 < 0xe0) {
            uVar17 = uVar20 - 2;
            pbVar23 = pbVar22 + 2;
          }
          else if (bVar5 < 0xf0) {
            uVar17 = uVar20 - 3;
            pbVar23 = pbVar22 + 3;
          }
          else {
            uVar17 = uVar20 - 3;
            pbVar23 = pbVar22 + 4;
          }
        }
        lVar11 = lVar11 + 1;
        uVar20 = uVar17;
        pbVar22 = pbVar23;
      }
                    /* try { // try from 00b2c29e to 00b2c2a2 has its CatchHandler @ 00b2de1a */
      CEGUI::String::grow((ulong)&local_b38);
      puVar18 = local_b10;
      if (0x20 < local_b30) {
        puVar18 = local_a90;
      }
      if (uVar24 == 0) {
        if (*pbVar16 != 0) {
          uVar24 = 0;
          do {
            uVar24 = uVar24 + 1;
          } while (pbVar16[uVar24] != 0);
          bVar27 = uVar24 != 0 && local_b30 != 0;
          goto LAB_00b2c2cc;
        }
      }
      else {
        bVar27 = local_b30 != 0;
LAB_00b2c2cc:
        if (bVar27) {
          uVar17 = 0;
          uVar20 = local_b30;
          uVar8 = 0;
          while( true ) {
            bVar5 = pbVar16[uVar17];
            uVar21 = (uint)bVar5;
            uVar9 = uVar8 + 1;
            if ((char)bVar5 < '\0') {
              uVar21 = (uint)bVar5;
              if (bVar5 < 0xe0) {
                uVar17 = (ulong)uVar9;
                uVar9 = uVar8 + 2;
                uVar21 = pbVar16[uVar17] & 0x3f | (uVar21 & 0x1f) << 6;
              }
              else if (bVar5 < 0xf0) {
                uVar17 = (ulong)uVar9;
                uVar9 = uVar8 + 3;
                uVar21 = pbVar16[uVar8 + 2] & 0x3f | (uVar21 & 0xf) << 0xc |
                         (pbVar16[uVar17] & 0x3f) << 6;
              }
              else {
                uVar17 = (ulong)uVar9;
                uVar9 = uVar8 + 4;
                uVar21 = (pbVar16[uVar17] & 0x3f) << 0xc | pbVar16[uVar8 + 3] & 0x3f |
                         (uVar21 & 7) << 0x12 | (pbVar16[uVar8 + 2] & 0x3f) << 6;
              }
            }
            *puVar18 = uVar21;
            uVar17 = (ulong)uVar9;
            uVar20 = uVar20 - 1;
            if ((uVar24 <= uVar17) || (uVar20 == 0)) break;
            puVar18 = puVar18 + 1;
            uVar8 = uVar9;
          }
        }
      }
      puVar18 = local_b10;
      if (0x20 < local_b30) {
        puVar18 = local_a90;
      }
      puVar18[lVar11] = 0;
      local_b38 = lVar11;
                    /* try { // try from 00b2b949 to 00b2b94d has its CatchHandler @ 00b2de05 */
      CEGUI::Window::setText(*(String **)(this + 0xe0));
                    /* try { // try from 00b2b951 to 00b2b955 has its CatchHandler @ 00b2de1a */
      CEGUI::String::~String((String *)&local_b38);
      if ((allocator *)(local_68[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        pbVar16 = local_68[0] + -8;
        iVar10 = *(int *)pbVar16;
        *(int *)pbVar16 = *(int *)pbVar16 + -1;
        UNLOCK();
        if (iVar10 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
        }
      }
    }
  }
  uVar24 = (ulong)(fVar2 + fVar34 + (float)(int)(fVar32 + (float)(uVar31 | uVar29)));
  if (1 < *(uint *)(this_01 + 0x3e0)) {
                    /* try { // try from 00b2b9e8 to 00b2bac1 has its CatchHandler @ 00b2df72 */
    CEGUI::Window::getSize();
    uVar29 = -(uint)(0.0 < local_480 * 0.0);
    uVar24 = (ulong)(((float)(int)((float)(~uVar29 & DAT_00fa86f4 | DAT_00fa4810 & uVar29) +
                                  local_480 * 0.0) + local_47c) * _DAT_00fe6520 +
                    (float)(uVar24 & 0xffffffff));
  }
  cVar7 = CEGUI::Window::isVisible(SUB81(*(undefined8 *)(*(long *)(this + 0xd8) + 0xb0),0));
  if ((cVar7 != '\0') && (*(int *)(this_01 + 0x3f0) != 0)) {
    uVar29 = 0;
    do {
      if (uVar29 < *(uint *)(this_01 + 0x3f4)) {
        this_04 = *(CEquipment **)((ulong)uVar29 * 8 + *(long *)(this_01 + 1000));
        pUVar25 = *(UVector2 **)(this_04 + 0x2c8);
        if (pUVar25 != (UVector2 *)0x0) goto LAB_00b2baa2;
LAB_00b2bbfe:
        CEquipment::createIcon(this_04,*(CGameUI **)(this + 0x80),false);
        pUVar25 = *(UVector2 **)(this_04 + 0x2c8);
        if (pUVar25 != (UVector2 *)0x0) {
          CEGUI::EventSet::setMutedState((bool)((char)pUVar25 + '8'));
          pUVar25[0x3e2] = (UVector2)0x1;
          goto LAB_00b2baa2;
        }
      }
      else {
        this_04 = (CEquipment *)**(long **)(this_01 + 1000);
        pUVar25 = *(UVector2 **)(this_04 + 0x2c8);
        if (pUVar25 == (UVector2 *)0x0) goto LAB_00b2bbfe;
LAB_00b2baa2:
        if (*(Window **)(pUVar25 + 0xb0) != (Window *)0x0) {
          CEGUI::Window::removeChildWindow(*(Window **)(pUVar25 + 0xb0));
        }
        CEGUI::Window::addChildWindow(*(Window **)(this + 0x30));
        local_494 = (float)((long)(fVar3 + fVar4 + (float)(int)((float)(uVar28 | uVar33) + fVar30))
                           & 0xffffffff);
        local_48c = (float)(uVar24 & 0xffffffff);
        local_498 = 0;
        local_490 = 0;
                    /* try { // try from 00b2bb0b to 00b2bb0f has its CatchHandler @ 00b2dbe5 */
        CEGUI::Window::setPosition(pUVar25);
                    /* try { // try from 00b2bb1f to 00b2bb23 has its CatchHandler @ 00b2df72 */
        CEGUI::Window::getSize();
                    /* try { // try from 00b2bb2f to 00b2bb33 has its CatchHandler @ 00b2ddf5 */
        CEGUI::Window::setSize(pUVar25);
                    /* try { // try from 00b2bb37 to 00b2bcbc has its CatchHandler @ 00b2df72 */
        CEGUI::Window::moveToFront();
        pUVar25[0x3e2] = (UVector2)0x1;
      }
      CEGUI::Window::getSize();
      uVar29 = uVar29 + 1;
      uVar31 = -(uint)(0.0 < local_4b0 * 0.0);
      if (*(uint *)(this_01 + 0x3f0) <= uVar29) break;
      uVar24 = (ulong)(((float)(int)((float)(~uVar31 & DAT_00fa86f4 | DAT_00fa4810 & uVar31) +
                                    local_4b0 * 0.0) + local_4ac) * DAT_00fa4830 +
                      (float)(uVar24 & 0xffffffff));
    } while( true );
  }
  cVar7 = CBaseUnit::ISA((CBaseUnit *)this_01,0x36);
  if (cVar7 == '\0') {
                    /* try { // try from 00b2c377 to 00b2c3ae has its CatchHandler @ 00b2df72 */
    cVar7 = (**(code **)(*(long *)this_01 + 0x2b0))(this_01);
    if (cVar7 == '\0') {
      pSVar26 = local_12c8;
      CEGUI::String::String(pSVar26,"");
                    /* try { // try from 00b2c4cf to 00b2c4d3 has its CatchHandler @ 00b2d997 */
      CEGUI::String::String(local_1218,"Image");
                    /* try { // try from 00b2c4e1 to 00b2c4e5 has its CatchHandler @ 00b2d985 */
      CEGUI::PropertySet::setProperty(*(String **)(this + 200),local_1218);
                    /* try { // try from 00b2c4e9 to 00b2c4ed has its CatchHandler @ 00b2d997 */
      CEGUI::String::~String(local_1218);
      goto LAB_00b2be34;
    }
    cVar7 = CBaseUnit::ISA((CBaseUnit *)this_01,0x37);
    if (cVar7 == '\0') {
      pSVar26 = local_1008;
      CEGUI::String::String(pSVar26,"greenslotglow");
                    /* try { // try from 00b2c3b9 to 00b2c3d0 has its CatchHandler @ 00b2ddaa */
      CEGUI::Imageset::getImage(*(String **)(this + 0xf8));
      CEGUI::PropertyHelper::imageToString(local_10b8);
                    /* try { // try from 00b2c3e1 to 00b2c3e5 has its CatchHandler @ 00b2dda5 */
      CEGUI::String::String(local_1168,"Image");
                    /* try { // try from 00b2c3f3 to 00b2c3f7 has its CatchHandler @ 00b2dd85 */
      CEGUI::PropertySet::setProperty(*(String **)(this + 200),local_1168);
                    /* try { // try from 00b2c3fb to 00b2c3ff has its CatchHandler @ 00b2dda5 */
      CEGUI::String::~String(local_1168);
                    /* try { // try from 00b2c403 to 00b2c407 has its CatchHandler @ 00b2ddaa */
      CEGUI::String::~String((String *)local_10b8);
    }
    else {
      pSVar26 = local_df8;
      CEGUI::String::String(pSVar26,"blueslotglow");
                    /* try { // try from 00b2c6ee to 00b2c705 has its CatchHandler @ 00b2dc1f */
      CEGUI::Imageset::getImage(*(String **)(this + 0xf8));
      CEGUI::PropertyHelper::imageToString(local_ea8);
                    /* try { // try from 00b2c716 to 00b2c71a has its CatchHandler @ 00b2dc1a */
      CEGUI::String::String(local_f58,"Image");
                    /* try { // try from 00b2c728 to 00b2c72c has its CatchHandler @ 00b2dbf5 */
      CEGUI::PropertySet::setProperty(*(String **)(this + 200),local_f58);
                    /* try { // try from 00b2c730 to 00b2c734 has its CatchHandler @ 00b2dc1a */
      CEGUI::String::~String(local_f58);
                    /* try { // try from 00b2c738 to 00b2c73c has its CatchHandler @ 00b2dc1f */
      CEGUI::String::~String((String *)local_ea8);
    }
                    /* try { // try from 00b2c40b to 00b2c4be has its CatchHandler @ 00b2df72 */
    CEGUI::String::~String(pSVar26);
  }
  else {
    pSVar26 = (String *)&local_be8;
    local_be0 = 0x20;
    local_bd8 = 0;
    local_bc8 = 0;
    local_bd0 = 0;
    local_b40 = (uint *)0x0;
    local_be8 = 0;
    local_bc0[0] = 0;
    CEGUI::String::grow((ulong)pSVar26);
    puVar18 = local_bc0;
    if (0x20 < local_be0) {
      puVar18 = local_b40;
    }
    pcVar15 = "goldslotglow";
    do {
      bVar5 = *pcVar15;
      pcVar15 = pcVar15 + 1;
      *puVar18 = (uint)bVar5;
      puVar18 = puVar18 + 1;
    } while ((byte *)pcVar15 != (byte *)0xfe60a7);
    local_be8 = 0xc;
    puVar18 = local_b90;
    if (0x20 < local_be0) {
      puVar18 = local_b40 + 0xc;
    }
    *puVar18 = 0;
                    /* try { // try from 00b2bd2d to 00b2bd44 has its CatchHandler @ 00b2dde5 */
    CEGUI::Imageset::getImage(*(String **)(this + 0xf8));
    CEGUI::PropertyHelper::imageToString(local_c98);
    local_d40 = 0x20;
    local_d38 = 0;
    local_d28 = 0;
    local_d30 = 0;
    local_ca0 = (uint *)0x0;
    local_d48 = 0;
    local_d20[0] = 0;
                    /* try { // try from 00b2bda8 to 00b2bdac has its CatchHandler @ 00b2de85 */
    CEGUI::String::grow((ulong)&local_d48);
    puVar18 = local_d20;
    if (0x20 < local_d40) {
      puVar18 = local_ca0;
    }
    pbVar16 = (byte *)0xfd0c0d;
    do {
      bVar5 = *pbVar16;
      pbVar16 = pbVar16 + 1;
      *puVar18 = (uint)bVar5;
      puVar18 = puVar18 + 1;
    } while (pbVar16 != (byte *)0xfd0c12);
    local_d48 = 5;
    puVar18 = local_d0c;
    if (0x20 < local_d40) {
      puVar18 = local_ca0 + 5;
    }
    *puVar18 = 0;
                    /* try { // try from 00b2be1f to 00b2be23 has its CatchHandler @ 00b2de75 */
    CEGUI::PropertySet::setProperty(*(String **)(this + 200),(String *)&local_d48);
                    /* try { // try from 00b2be27 to 00b2be2b has its CatchHandler @ 00b2de85 */
    CEGUI::String::~String((String *)&local_d48);
                    /* try { // try from 00b2be2f to 00b2be33 has its CatchHandler @ 00b2dde5 */
    CEGUI::String::~String((String *)local_c98);
LAB_00b2be34:
                    /* try { // try from 00b2be37 to 00b2bea0 has its CatchHandler @ 00b2df72 */
    CEGUI::String::~String(pSVar26);
  }
  local_1420 = 0x20;
  local_1418 = 0;
  local_1408 = 0;
  local_1410 = 0;
  local_1380 = (undefined4 *)0x0;
  local_1428 = 0;
  local_1400[0] = 0;
  CEGUI::String::grow((ulong)&local_1428);
  local_1428 = 0;
  puVar19 = local_1400;
  if (0x20 < local_1420) {
    puVar19 = local_1380;
  }
  *puVar19 = 0;
  local_1370 = 0x20;
  local_1368 = 0;
  local_1358 = 0;
  local_1360 = 0;
  local_12d0 = (uint *)0x0;
  local_1378 = 0;
  local_1350[0] = 0;
                    /* try { // try from 00b2bf2e to 00b2bf32 has its CatchHandler @ 00b2de65 */
  CEGUI::String::grow((ulong)&local_1378);
  puVar18 = local_1350;
  if (0x20 < local_1370) {
    puVar18 = local_12d0;
  }
  pbVar16 = (byte *)0xfd0c0d;
  do {
    bVar5 = *pbVar16;
    pbVar16 = pbVar16 + 1;
    *puVar18 = (uint)bVar5;
    puVar18 = puVar18 + 1;
  } while (pbVar16 != (byte *)0xfd0c12);
  local_1378 = 5;
  puVar18 = local_133c;
  if (0x20 < local_1370) {
    puVar18 = local_12d0 + 5;
  }
  *puVar18 = 0;
                    /* try { // try from 00b2bf9f to 00b2bfa3 has its CatchHandler @ 00b2de55 */
  CEGUI::PropertySet::setProperty(*(String **)(this + 0xd8),(String *)&local_1378);
                    /* try { // try from 00b2bfa7 to 00b2bfab has its CatchHandler @ 00b2de65 */
  CEGUI::String::~String((String *)&local_1378);
                    /* try { // try from 00b2bfaf to 00b2bfb3 has its CatchHandler @ 00b2df72 */
  CEGUI::String::~String((String *)&local_1428);
  if (local_2368 != (UVector2 *)0x0) {
    local_4c4 = 0;
    local_4c8 = 0;
    local_4bc = 0x3f800000;
    local_4c0 = 0;
                    /* try { // try from 00b2bff9 to 00b2bffd has its CatchHandler @ 00b2e025 */
    CEGUI::Window::setPosition(local_2368);
    local_4d4 = 0;
    local_4d8 = 0;
    local_4cc = 0;
    local_4d0 = 0;
                    /* try { // try from 00b2c037 to 00b2c03b has its CatchHandler @ 00b2e015 */
    CEGUI::Window::setPosition(local_2368);
                    /* try { // try from 00b2c04e to 00b2c052 has its CatchHandler @ 00b2df72 */
    CEGUI::Window::getSize();
                    /* try { // try from 00b2c05b to 00b2c05f has its CatchHandler @ 00b2e035 */
    CEGUI::Window::setSize(local_2368);
                    /* try { // try from 00b2c065 to 00b2c0fb has its CatchHandler @ 00b2df72 */
    CEGUI::Window::moveToFront();
    CEGUI::Window::update(DAT_00fa4828);
  }
  switch(*(undefined4 *)(this + 0x10c)) {
  case 0x15:
                    /* try { // try from 00b2c18c to 00b2c1e8 has its CatchHandler @ 00b2df72 */
    cVar7 = CBaseUnit::ISA((CBaseUnit *)this_01,8);
                    /* try { // try from 00b2caf2 to 00b2cb60 has its CatchHandler @ 00b2df72 */
    if ((((cVar7 == '\0') && (cVar7 = CBaseUnit::ISA((CBaseUnit *)this_01,0xd), cVar7 == '\0')) &&
        (cVar7 = CBaseUnit::ISA((CBaseUnit *)this_01,0x11), cVar7 == '\0')) &&
       (cVar7 = CBaseUnit::ISA((CBaseUnit *)this_01,0x18), cVar7 == '\0')) {
      if ((updateLayout()::g_CannotEnchant == '\0') &&
         (iVar10 = __cxa_guard_acquire(&updateLayout()::g_CannotEnchant), iVar10 != 0)) {
        updateLayout()::g_CannotEnchant = &DAT_01424558;
        __cxa_guard_release(&updateLayout()::g_CannotEnchant);
        __cxa_atexit(std::wstring::~wstring,&updateLayout()::g_CannotEnchant,&__dso_handle);
      }
      if (*(long *)(updateLayout()::g_CannotEnchant + -6) == 0) {
        CStringTranslate::getSinglton();
        CStringTranslate::getTranslateString((wchar_t *)local_178);
                    /* try { // try from 00b2cb69 to 00b2cb6d has its CatchHandler @ 00b2da44 */
        std::wstring::assign((wstring_conflict *)&updateLayout()::g_CannotEnchant);
                    /* try { // try from 00b2cb71 to 00b2cb75 has its CatchHandler @ 00b2df72 */
        std::wstring::~wstring(local_178);
      }
                    /* try { // try from 00b2cb90 to 00b2cb94 has its CatchHandler @ 00b2df95 */
      std::wstring::wstring(local_188,updateLayout()::g_CannotEnchant,&local_3a);
                    /* try { // try from 00b2cba3 to 00b2cba7 has its CatchHandler @ 00b2df8f */
      STRINGS::StringConvertToUTF8((wstring_conflict *)local_198);
                    /* try { // try from 00b2cbbb to 00b2cbbf has its CatchHandler @ 00b2df8a */
      CEGUI::String::String(local_1638,local_198[0]);
                    /* try { // try from 00b2cbc7 to 00b2cbcb has its CatchHandler @ 00b2df85 */
      CEGUI::Window::setText(*(String **)(this + 0x48));
                    /* try { // try from 00b2cbcf to 00b2cbd3 has its CatchHandler @ 00b2df8a */
      CEGUI::String::~String(local_1638);
                    /* try { // try from 00b2cbd7 to 00b2cbdb has its CatchHandler @ 00b2df8f */
      std::string::~string((string *)local_198);
                    /* try { // try from 00b2cbdf to 00b2cbe3 has its CatchHandler @ 00b2df95 */
      std::wstring::~wstring(local_188);
      break;
    }
    iVar10 = *(int *)(this_01 + 0x344);
    lVar11 = CGameGlobals::getSingleton();
    if (*(int *)(lVar11 + 0x88) <= iVar10) {
      if ((updateLayout()::g_MaxEnchant == '\0') &&
         (iVar10 = __cxa_guard_acquire(&updateLayout()::g_MaxEnchant), iVar10 != 0)) {
        updateLayout()::g_MaxEnchant = &DAT_01424558;
        __cxa_guard_release(&updateLayout()::g_MaxEnchant);
        __cxa_atexit(std::wstring::~wstring,&updateLayout()::g_MaxEnchant,&__dso_handle);
      }
      if (*(long *)(updateLayout()::g_MaxEnchant + -6) == 0) {
        CStringTranslate::getSinglton();
        CStringTranslate::getTranslateString((wchar_t *)local_88);
                    /* try { // try from 00b2c1f1 to 00b2c1f5 has its CatchHandler @ 00b2dfe5 */
        std::wstring::assign((wstring_conflict *)&updateLayout()::g_MaxEnchant);
                    /* try { // try from 00b2c1f9 to 00b2c1fd has its CatchHandler @ 00b2df72 */
        std::wstring::~wstring(local_88);
      }
                    /* try { // try from 00b2c218 to 00b2c21c has its CatchHandler @ 00b2de45 */
      std::wstring::wstring(local_98,updateLayout()::g_MaxEnchant,local_39);
                    /* try { // try from 00b2c22b to 00b2c22f has its CatchHandler @ 00b2de35 */
      STRINGS::StringConvertToUTF8((wstring_conflict *)local_a8);
                    /* try { // try from 00b2c243 to 00b2c247 has its CatchHandler @ 00b2de25 */
      CEGUI::String::String(local_14d8,local_a8[0]);
                    /* try { // try from 00b2c24f to 00b2c253 has its CatchHandler @ 00b2de1f */
      CEGUI::Window::setText(*(String **)(this + 0x48));
                    /* try { // try from 00b2c257 to 00b2c25b has its CatchHandler @ 00b2de25 */
      CEGUI::String::~String(local_14d8);
                    /* try { // try from 00b2c25f to 00b2c263 has its CatchHandler @ 00b2de35 */
      std::string::~string((string *)local_a8);
                    /* try { // try from 00b2c267 to 00b2c26b has its CatchHandler @ 00b2de45 */
      std::wstring::~wstring(local_98);
      break;
    }
    if ((updateLayout()::g_EnchantPrice == '\0') &&
       (iVar10 = __cxa_guard_acquire(&updateLayout()::g_EnchantPrice), iVar10 != 0)) {
      updateLayout()::g_EnchantPrice = &DAT_01424558;
      __cxa_guard_release(&updateLayout()::g_EnchantPrice);
      __cxa_atexit(std::wstring::~wstring,&updateLayout()::g_EnchantPrice,&__dso_handle);
    }
    if (*(long *)(updateLayout()::g_EnchantPrice + -6) == 0) {
      CStringTranslate::getSinglton();
      CStringTranslate::getTranslateString((wchar_t *)local_b8);
                    /* try { // try from 00b2d8e2 to 00b2d8e6 has its CatchHandler @ 00b2d972 */
      std::wstring::assign((wstring_conflict *)&updateLayout()::g_EnchantPrice);
                    /* try { // try from 00b2d8ea to 00b2d8ee has its CatchHandler @ 00b2df72 */
      std::wstring::~wstring(local_b8);
    }
    if ((updateLayout()::g_Disenchant == '\0') &&
       (iVar10 = __cxa_guard_acquire(&updateLayout()::g_Disenchant), iVar10 != 0)) {
      updateLayout()::g_Disenchant = &DAT_01424558;
      __cxa_guard_release(&updateLayout()::g_Disenchant);
      __cxa_atexit(std::wstring::~wstring,&updateLayout()::g_Disenchant,&__dso_handle);
    }
    if (*(long *)(updateLayout()::g_Disenchant + -6) == 0) {
                    /* try { // try from 00b2b681 to 00b2b69d has its CatchHandler @ 00b2df72 */
      CStringTranslate::getSinglton();
      CStringTranslate::getTranslateString((wchar_t *)local_c8);
                    /* try { // try from 00b2b6a6 to 00b2b6aa has its CatchHandler @ 00b2d974 */
      std::wstring::assign((wstring_conflict *)&updateLayout()::g_Disenchant);
                    /* try { // try from 00b2b6ae to 00b2b70f has its CatchHandler @ 00b2df72 */
      std::wstring::~wstring(local_c8);
    }
    uVar28 = *(uint *)(this_01 + 0x344);
    lVar11 = CGameGlobals::getSingleton();
    fVar2 = *(float *)(lVar11 + 0x8c);
    lVar11 = CGameGlobals::getSingleton();
    fVar34 = (float)uVar28 * fVar2 + *(float *)(lVar11 + 0x70);
    lVar11 = CGameGlobals::getSingleton();
    fVar2 = *(float *)(lVar11 + 0x74);
    if (fVar34 <= *(float *)(lVar11 + 0x74)) {
      fVar2 = fVar34;
    }
    STRINGS::GetValueAsWString(local_138,fVar2);
                    /* try { // try from 00b2b713 to 00b2b726 has its CatchHandler @ 00b2daf7 */
    iVar10 = CEquipment::enchantPrice(this_01);
    STRINGS::GetValueAsWString(local_e8,iVar10);
                    /* try { // try from 00b2b739 to 00b2b73d has its CatchHandler @ 00b2daf2 */
    std::operator+(local_d8,(wchar_t *)&updateLayout()::g_EnchantPrice);
                    /* try { // try from 00b2b756 to 00b2b75a has its CatchHandler @ 00b2daec */
    std::operator+(local_f8,local_d8);
                    /* try { // try from 00b2b773 to 00b2b777 has its CatchHandler @ 00b2dae7 */
    std::operator+(local_108,(wchar_t *)local_f8);
                    /* try { // try from 00b2b78b to 00b2b78f has its CatchHandler @ 00b2dae2 */
    std::operator+(local_118,local_108);
                    /* try { // try from 00b2b7a3 to 00b2b7a7 has its CatchHandler @ 00b2dadb */
    std::operator+(local_128,(wchar_t *)local_118);
                    /* try { // try from 00b2b7be to 00b2b7c2 has its CatchHandler @ 00b2dad6 */
    std::operator+(local_148,local_128);
                    /* try { // try from 00b2b7d6 to 00b2b7da has its CatchHandler @ 00b2da76 */
    std::operator+(local_158,(wchar_t *)local_148);
                    /* try { // try from 00b2b7e6 to 00b2b7ea has its CatchHandler @ 00b2dfb5 */
    std::wstring::assign((wstring_conflict *)local_58);
                    /* try { // try from 00b2b7ee to 00b2b7f2 has its CatchHandler @ 00b2da76 */
    std::wstring::~wstring(local_158);
                    /* try { // try from 00b2b7f6 to 00b2b7fa has its CatchHandler @ 00b2dad6 */
    std::wstring::~wstring(local_148);
                    /* try { // try from 00b2b7fe to 00b2b802 has its CatchHandler @ 00b2dadb */
    std::wstring::~wstring(local_128);
                    /* try { // try from 00b2b806 to 00b2b80a has its CatchHandler @ 00b2dae2 */
    std::wstring::~wstring(local_118);
                    /* try { // try from 00b2b80e to 00b2b812 has its CatchHandler @ 00b2dae7 */
    std::wstring::~wstring(local_108);
                    /* try { // try from 00b2b81b to 00b2b81f has its CatchHandler @ 00b2daec */
    std::wstring::~wstring(local_f8);
                    /* try { // try from 00b2b828 to 00b2b82c has its CatchHandler @ 00b2daf2 */
    std::wstring::~wstring(local_d8);
                    /* try { // try from 00b2b835 to 00b2b839 has its CatchHandler @ 00b2daf7 */
    std::wstring::~wstring((wstring_conflict *)local_e8);
                    /* try { // try from 00b2b842 to 00b2b85e has its CatchHandler @ 00b2df72 */
    std::wstring::~wstring((wstring_conflict *)local_138);
    this_03 = (wstring_conflict *)local_168;
    STRINGS::StringConvertToUTF8(this_03);
                    /* try { // try from 00b2b872 to 00b2b876 has its CatchHandler @ 00b2dfa5 */
    CEGUI::String::String(local_1588,local_168[0]);
                    /* try { // try from 00b2b87e to 00b2b882 has its CatchHandler @ 00b2dfd5 */
    CEGUI::Window::setText(*(String **)(this + 0x48));
                    /* try { // try from 00b2b886 to 00b2b88a has its CatchHandler @ 00b2dfa5 */
    CEGUI::String::~String(local_1588);
    goto LAB_00b2b88b;
  case 0x16:
    cVar7 = CBaseUnit::ISA((CBaseUnit *)this_01,8);
                    /* try { // try from 00b2c9f3 to 00b2ca61 has its CatchHandler @ 00b2df72 */
    if ((((cVar7 == '\0') && (cVar7 = CBaseUnit::ISA((CBaseUnit *)this_01,0xd), cVar7 == '\0')) &&
        (cVar7 = CBaseUnit::ISA((CBaseUnit *)this_01,0x11), cVar7 == '\0')) &&
       (cVar7 = CBaseUnit::ISA((CBaseUnit *)this_01,0x18), cVar7 == '\0')) {
      if ((updateLayout()::g_CannotEnchant == '\0') &&
         (iVar10 = __cxa_guard_acquire(&updateLayout()::g_CannotEnchant), iVar10 != 0)) {
        updateLayout()::g_CannotEnchant = &DAT_01424558;
        __cxa_guard_release(&updateLayout()::g_CannotEnchant);
        __cxa_atexit(std::wstring::~wstring,&updateLayout()::g_CannotEnchant,&__dso_handle);
      }
      if (*(long *)(updateLayout()::g_CannotEnchant + -6) == 0) {
        CStringTranslate::getSinglton();
        CStringTranslate::getTranslateString((wchar_t *)local_268);
                    /* try { // try from 00b2ca6a to 00b2ca6e has its CatchHandler @ 00b2da5c */
        std::wstring::assign((wstring_conflict *)&updateLayout()::g_CannotEnchant);
                    /* try { // try from 00b2ca72 to 00b2ca76 has its CatchHandler @ 00b2df72 */
        std::wstring::~wstring(local_268);
      }
                    /* try { // try from 00b2ca91 to 00b2ca95 has its CatchHandler @ 00b2ddd5 */
      std::wstring::wstring(local_278,updateLayout()::g_CannotEnchant,&local_3c);
                    /* try { // try from 00b2caa4 to 00b2caa8 has its CatchHandler @ 00b2ddc5 */
      STRINGS::StringConvertToUTF8((wstring_conflict *)local_288);
                    /* try { // try from 00b2cabc to 00b2cac0 has its CatchHandler @ 00b2ddb5 */
      CEGUI::String::String(local_1848,local_288[0]);
                    /* try { // try from 00b2cac8 to 00b2cacc has its CatchHandler @ 00b2ddaf */
      CEGUI::Window::setText(*(String **)(this + 0x48));
                    /* try { // try from 00b2cad0 to 00b2cad4 has its CatchHandler @ 00b2ddb5 */
      CEGUI::String::~String(local_1848);
                    /* try { // try from 00b2cad8 to 00b2cadc has its CatchHandler @ 00b2ddc5 */
      std::string::~string((string *)local_288);
                    /* try { // try from 00b2cae0 to 00b2cae4 has its CatchHandler @ 00b2ddd5 */
      std::wstring::~wstring(local_278);
      break;
    }
    iVar10 = *(int *)(this_01 + 0x344);
    lVar11 = CGameGlobals::getSingleton();
    if (*(int *)(lVar11 + 0x90) <= iVar10) {
      if ((updateLayout()::g_MaxEnchant == '\0') &&
         (iVar10 = __cxa_guard_acquire(&updateLayout()::g_MaxEnchant), iVar10 != 0)) {
        updateLayout()::g_MaxEnchant = &DAT_01424558;
        __cxa_guard_release(&updateLayout()::g_MaxEnchant);
        __cxa_atexit(std::wstring::~wstring,&updateLayout()::g_MaxEnchant,&__dso_handle);
      }
      if (*(long *)(updateLayout()::g_MaxEnchant + -6) == 0) {
        CStringTranslate::getSinglton();
        CStringTranslate::getTranslateString((wchar_t *)local_1a8);
                    /* try { // try from 00b2c104 to 00b2c108 has its CatchHandler @ 00b2d94d */
        std::wstring::assign((wstring_conflict *)&updateLayout()::g_MaxEnchant);
                    /* try { // try from 00b2c10c to 00b2c110 has its CatchHandler @ 00b2df72 */
        std::wstring::~wstring(local_1a8);
      }
                    /* try { // try from 00b2c12b to 00b2c12f has its CatchHandler @ 00b2dd75 */
      std::wstring::wstring(local_1b8,updateLayout()::g_MaxEnchant,&local_3b);
                    /* try { // try from 00b2c13e to 00b2c142 has its CatchHandler @ 00b2dd65 */
      STRINGS::StringConvertToUTF8((wstring_conflict *)local_1c8);
                    /* try { // try from 00b2c156 to 00b2c15a has its CatchHandler @ 00b2dd55 */
      CEGUI::String::String(local_16e8,local_1c8[0]);
                    /* try { // try from 00b2c162 to 00b2c166 has its CatchHandler @ 00b2dd45 */
      CEGUI::Window::setText(*(String **)(this + 0x48));
                    /* try { // try from 00b2c16a to 00b2c16e has its CatchHandler @ 00b2dd55 */
      CEGUI::String::~String(local_16e8);
                    /* try { // try from 00b2c172 to 00b2c176 has its CatchHandler @ 00b2dd65 */
      std::string::~string((string *)local_1c8);
                    /* try { // try from 00b2c17a to 00b2c17e has its CatchHandler @ 00b2dd75 */
      std::wstring::~wstring(local_1b8);
      break;
    }
    if ((updateLayout()::g_PressEnchant == '\0') &&
       (iVar10 = __cxa_guard_acquire(&updateLayout()::g_PressEnchant), iVar10 != 0)) {
      updateLayout()::g_PressEnchant = &DAT_01424558;
      __cxa_guard_release(&updateLayout()::g_PressEnchant);
      __cxa_atexit(std::wstring::~wstring,&updateLayout()::g_PressEnchant,&__dso_handle);
    }
    if (*(long *)(updateLayout()::g_PressEnchant + -6) == 0) {
                    /* try { // try from 00b2d746 to 00b2d762 has its CatchHandler @ 00b2df72 */
      CStringTranslate::getSinglton();
      CStringTranslate::getTranslateString((wchar_t *)local_1d8);
                    /* try { // try from 00b2d76b to 00b2d76f has its CatchHandler @ 00b2d8f4 */
      std::wstring::assign((wstring_conflict *)&updateLayout()::g_PressEnchant);
                    /* try { // try from 00b2d773 to 00b2d8d9 has its CatchHandler @ 00b2df72 */
      std::wstring::~wstring(local_1d8);
    }
    if ((updateLayout()::g_Disenchant == '\0') &&
       (iVar10 = __cxa_guard_acquire(&updateLayout()::g_Disenchant), iVar10 != 0)) {
      updateLayout()::g_Disenchant = &DAT_01424558;
      __cxa_guard_release(&updateLayout()::g_Disenchant);
      __cxa_atexit(std::wstring::~wstring,&updateLayout()::g_Disenchant,&__dso_handle);
    }
    if (*(long *)(updateLayout()::g_Disenchant + -6) == 0) {
                    /* try { // try from 00b2d566 to 00b2d582 has its CatchHandler @ 00b2df72 */
      CStringTranslate::getSinglton();
      CStringTranslate::getTranslateString((wchar_t *)local_1e8);
                    /* try { // try from 00b2d58b to 00b2d58f has its CatchHandler @ 00b2d96f */
      std::wstring::assign((wstring_conflict *)&updateLayout()::g_Disenchant);
                    /* try { // try from 00b2d593 to 00b2d5fa has its CatchHandler @ 00b2df72 */
      std::wstring::~wstring(local_1e8);
    }
    uVar28 = *(uint *)(this_01 + 0x344);
    lVar11 = CGameGlobals::getSingleton();
    fVar2 = *(float *)(lVar11 + 0x94);
    lVar11 = CGameGlobals::getSingleton();
    fVar34 = (float)uVar28 * fVar2 + *(float *)(lVar11 + 0x80);
    lVar11 = CGameGlobals::getSingleton();
    fVar2 = *(float *)(lVar11 + 0x84);
    if (fVar34 <= *(float *)(lVar11 + 0x84)) {
      fVar2 = fVar34;
    }
    STRINGS::GetValueAsWString(local_228,fVar2);
                    /* try { // try from 00b2d610 to 00b2d614 has its CatchHandler @ 00b2d948 */
    std::operator+(local_1f8,(wchar_t *)&updateLayout()::g_PressEnchant);
                    /* try { // try from 00b2d628 to 00b2d62c has its CatchHandler @ 00b2d92e */
    std::operator+(local_208,local_1f8);
                    /* try { // try from 00b2d640 to 00b2d644 has its CatchHandler @ 00b2d9d2 */
    std::operator+(local_218,(wchar_t *)local_208);
                    /* try { // try from 00b2d65b to 00b2d65f has its CatchHandler @ 00b2d9c9 */
    std::operator+(local_238,local_218);
                    /* try { // try from 00b2d673 to 00b2d677 has its CatchHandler @ 00b2d9c4 */
    std::operator+(local_248,(wchar_t *)local_238);
                    /* try { // try from 00b2d683 to 00b2d687 has its CatchHandler @ 00b2d99c */
    std::wstring::assign((wstring_conflict *)local_58);
                    /* try { // try from 00b2d68b to 00b2d68f has its CatchHandler @ 00b2d9c4 */
    std::wstring::~wstring(local_248);
                    /* try { // try from 00b2d693 to 00b2d697 has its CatchHandler @ 00b2d9c9 */
    std::wstring::~wstring(local_238);
                    /* try { // try from 00b2d69b to 00b2d69f has its CatchHandler @ 00b2d9d2 */
    std::wstring::~wstring(local_218);
                    /* try { // try from 00b2d6a3 to 00b2d6a7 has its CatchHandler @ 00b2d92e */
    std::wstring::~wstring(local_208);
                    /* try { // try from 00b2d6ab to 00b2d6af has its CatchHandler @ 00b2d948 */
    std::wstring::~wstring(local_1f8);
                    /* try { // try from 00b2d6b8 to 00b2d6d4 has its CatchHandler @ 00b2df72 */
    std::wstring::~wstring((wstring_conflict *)local_228);
    this_03 = (wstring_conflict *)local_258;
    STRINGS::StringConvertToUTF8(this_03);
                    /* try { // try from 00b2d6e8 to 00b2d6ec has its CatchHandler @ 00b2d929 */
    CEGUI::String::String(local_1798,local_258[0]);
                    /* try { // try from 00b2d6f4 to 00b2d6f8 has its CatchHandler @ 00b2d914 */
    CEGUI::Window::setText(*(String **)(this + 0x48));
                    /* try { // try from 00b2d6fc to 00b2d700 has its CatchHandler @ 00b2d929 */
    CEGUI::String::~String(local_1798);
LAB_00b2b88b:
                    /* try { // try from 00b2b88e to 00b2b90f has its CatchHandler @ 00b2df72 */
    std::string::~string((string *)this_03);
    break;
  case 0x19:
    if ((*(int *)(this_01 + 0x3e0) == 0) || (*(int *)(this_01 + 0x3f0) == 0)) {
      if ((updateLayout()::g_NoGem == '\0') &&
         (iVar10 = __cxa_guard_acquire(&updateLayout()::g_NoGem), iVar10 != 0)) {
        updateLayout()::g_NoGem = &DAT_01424558;
        __cxa_guard_release(&updateLayout()::g_NoGem);
        __cxa_atexit(std::wstring::~wstring,&updateLayout()::g_NoGem,&__dso_handle);
      }
      if (*(long *)(updateLayout()::g_NoGem + -6) == 0) {
        CStringTranslate::getSinglton();
        CStringTranslate::getTranslateString((wchar_t *)local_328);
                    /* try { // try from 00b2d059 to 00b2d05d has its CatchHandler @ 00b2df05 */
        std::wstring::assign((wstring_conflict *)&updateLayout()::g_NoGem);
                    /* try { // try from 00b2d061 to 00b2d065 has its CatchHandler @ 00b2df72 */
        std::wstring::~wstring(local_328);
      }
                    /* try { // try from 00b2d080 to 00b2d084 has its CatchHandler @ 00b2dd35 */
      std::wstring::wstring(local_338,updateLayout()::g_NoGem,&local_40);
                    /* try { // try from 00b2d093 to 00b2d097 has its CatchHandler @ 00b2dd25 */
      STRINGS::StringConvertToUTF8((wstring_conflict *)local_348);
                    /* try { // try from 00b2d0ab to 00b2d0af has its CatchHandler @ 00b2dd1c */
      CEGUI::String::String(local_1b08,local_348[0]);
                    /* try { // try from 00b2d0b7 to 00b2d0bb has its CatchHandler @ 00b2dd17 */
      CEGUI::Window::setText(*(String **)(this + 0x48));
                    /* try { // try from 00b2d0bf to 00b2d0c3 has its CatchHandler @ 00b2dd1c */
      CEGUI::String::~String(local_1b08);
                    /* try { // try from 00b2d0c7 to 00b2d0cb has its CatchHandler @ 00b2dd25 */
      std::string::~string((string *)local_348);
                    /* try { // try from 00b2d0cf to 00b2d0d3 has its CatchHandler @ 00b2dd35 */
      std::wstring::~wstring(local_338);
    }
    else {
      if ((updateLayout()::g_PressDestroyGem == '\0') &&
         (iVar10 = __cxa_guard_acquire(&updateLayout()::g_PressDestroyGem), iVar10 != 0)) {
        updateLayout()::g_PressDestroyGem = &DAT_01424558;
        __cxa_guard_release(&updateLayout()::g_PressDestroyGem);
        __cxa_atexit(std::wstring::~wstring,&updateLayout()::g_PressDestroyGem,&__dso_handle);
      }
      if (*(long *)(updateLayout()::g_PressDestroyGem + -6) == 0) {
                    /* try { // try from 00b2c868 to 00b2c884 has its CatchHandler @ 00b2df72 */
        CStringTranslate::getSinglton();
        CStringTranslate::getTranslateString((wchar_t *)local_2f8);
                    /* try { // try from 00b2c88d to 00b2c891 has its CatchHandler @ 00b2e045 */
        std::wstring::assign((wstring_conflict *)&updateLayout()::g_PressDestroyGem);
                    /* try { // try from 00b2c895 to 00b2c899 has its CatchHandler @ 00b2df72 */
        std::wstring::~wstring(local_2f8);
      }
                    /* try { // try from 00b2c8b4 to 00b2c8b8 has its CatchHandler @ 00b2e085 */
      std::wstring::wstring(local_308,updateLayout()::g_PressDestroyGem,&local_3f);
                    /* try { // try from 00b2c8c7 to 00b2c8cb has its CatchHandler @ 00b2e075 */
      STRINGS::StringConvertToUTF8((wstring_conflict *)local_318);
                    /* try { // try from 00b2c8df to 00b2c8e3 has its CatchHandler @ 00b2e065 */
      CEGUI::String::String(local_1a58,local_318[0]);
                    /* try { // try from 00b2c8eb to 00b2c8ef has its CatchHandler @ 00b2e055 */
      CEGUI::Window::setText(*(String **)(this + 0x48));
                    /* try { // try from 00b2c8f3 to 00b2c8f7 has its CatchHandler @ 00b2e065 */
      CEGUI::String::~String(local_1a58);
                    /* try { // try from 00b2c8fb to 00b2c8ff has its CatchHandler @ 00b2e075 */
      std::string::~string((string *)local_318);
                    /* try { // try from 00b2c903 to 00b2c907 has its CatchHandler @ 00b2e085 */
      std::wstring::~wstring(local_308);
    }
    break;
  case 0x1a:
    if ((*(int *)(this_01 + 0x3e0) == 0) || (*(int *)(this_01 + 0x3f0) == 0)) {
      if ((updateLayout()::g_NoGemsToRecover == '\0') &&
         (iVar10 = __cxa_guard_acquire(&updateLayout()::g_NoGemsToRecover), iVar10 != 0)) {
        updateLayout()::g_NoGemsToRecover = &DAT_01424558;
        __cxa_guard_release(&updateLayout()::g_NoGemsToRecover);
        __cxa_atexit(std::wstring::~wstring,&updateLayout()::g_NoGemsToRecover,&__dso_handle);
      }
      if (*(long *)(updateLayout()::g_NoGemsToRecover + -6) == 0) {
                    /* try { // try from 00b2d0f4 to 00b2d110 has its CatchHandler @ 00b2df72 */
        CStringTranslate::getSinglton();
        CStringTranslate::getTranslateString((wchar_t *)local_2c8);
                    /* try { // try from 00b2d119 to 00b2d11d has its CatchHandler @ 00b2dee5 */
        std::wstring::assign((wstring_conflict *)&updateLayout()::g_NoGemsToRecover);
                    /* try { // try from 00b2d121 to 00b2d125 has its CatchHandler @ 00b2df72 */
        std::wstring::~wstring(local_2c8);
      }
                    /* try { // try from 00b2d140 to 00b2d144 has its CatchHandler @ 00b2dc45 */
      std::wstring::wstring(local_2d8,updateLayout()::g_NoGemsToRecover,&local_3e);
                    /* try { // try from 00b2d153 to 00b2d157 has its CatchHandler @ 00b2dc35 */
      STRINGS::StringConvertToUTF8((wstring_conflict *)local_2e8);
                    /* try { // try from 00b2d16b to 00b2d16f has its CatchHandler @ 00b2dc29 */
      CEGUI::String::String(local_19a8,local_2e8[0]);
                    /* try { // try from 00b2d177 to 00b2d17b has its CatchHandler @ 00b2dc24 */
      CEGUI::Window::setText(*(String **)(this + 0x48));
                    /* try { // try from 00b2d17f to 00b2d183 has its CatchHandler @ 00b2dc29 */
      CEGUI::String::~String(local_19a8);
                    /* try { // try from 00b2d187 to 00b2d18b has its CatchHandler @ 00b2dc35 */
      std::string::~string((string *)local_2e8);
                    /* try { // try from 00b2d18f to 00b2d193 has its CatchHandler @ 00b2dc45 */
      std::wstring::~wstring(local_2d8);
    }
    else {
      if ((updateLayout()::g_PressRecover == '\0') &&
         (iVar10 = __cxa_guard_acquire(&updateLayout()::g_PressRecover), iVar10 != 0)) {
        updateLayout()::g_PressRecover = &DAT_01424558;
        __cxa_guard_release(&updateLayout()::g_PressRecover);
        __cxa_atexit(std::wstring::~wstring,&updateLayout()::g_PressRecover,&__dso_handle);
      }
      if (*(long *)(updateLayout()::g_PressRecover + -6) == 0) {
                    /* try { // try from 00b2c788 to 00b2c7a4 has its CatchHandler @ 00b2df72 */
        CStringTranslate::getSinglton();
        CStringTranslate::getTranslateString((wchar_t *)local_298);
                    /* try { // try from 00b2c7ad to 00b2c7b1 has its CatchHandler @ 00b2dff5 */
        std::wstring::assign((wstring_conflict *)&updateLayout()::g_PressRecover);
                    /* try { // try from 00b2c7b5 to 00b2c7b9 has its CatchHandler @ 00b2df72 */
        std::wstring::~wstring(local_298);
      }
                    /* try { // try from 00b2c7d4 to 00b2c7d8 has its CatchHandler @ 00b2dec5 */
      std::wstring::wstring(local_2a8,updateLayout()::g_PressRecover,&local_3d);
                    /* try { // try from 00b2c7e7 to 00b2c7eb has its CatchHandler @ 00b2deb5 */
      STRINGS::StringConvertToUTF8((wstring_conflict *)local_2b8);
                    /* try { // try from 00b2c7ff to 00b2c803 has its CatchHandler @ 00b2dea5 */
      CEGUI::String::String(local_18f8,local_2b8[0]);
                    /* try { // try from 00b2c80b to 00b2c80f has its CatchHandler @ 00b2de95 */
      CEGUI::Window::setText(*(String **)(this + 0x48));
                    /* try { // try from 00b2c813 to 00b2c817 has its CatchHandler @ 00b2dea5 */
      CEGUI::String::~String(local_18f8);
                    /* try { // try from 00b2c81b to 00b2c81f has its CatchHandler @ 00b2deb5 */
      std::string::~string((string *)local_2b8);
                    /* try { // try from 00b2c823 to 00b2c827 has its CatchHandler @ 00b2dec5 */
      std::wstring::~wstring(local_2a8);
    }
    break;
  case 0x1b:
                    /* try { // try from 00b2c915 to 00b2c959 has its CatchHandler @ 00b2df72 */
    cVar7 = CBaseUnit::ISA((CBaseUnit *)this_01,8);
    if (((cVar7 == '\0') && (cVar7 = CBaseUnit::ISA((CBaseUnit *)this_01,0xd), cVar7 == '\0')) &&
       (cVar7 = CBaseUnit::ISA((CBaseUnit *)this_01,0x27), cVar7 == '\0')) {
      if ((updateLayout()::g_NoHeirloom == '\0') &&
         (iVar10 = __cxa_guard_acquire(&updateLayout()::g_NoHeirloom), iVar10 != 0)) {
        updateLayout()::g_NoHeirloom = &DAT_01424558;
        __cxa_guard_release(&updateLayout()::g_NoHeirloom);
        __cxa_atexit(std::wstring::~wstring,&updateLayout()::g_NoHeirloom,&__dso_handle);
      }
      if (*(long *)(updateLayout()::g_NoHeirloom + -6) == 0) {
        CStringTranslate::getSinglton();
        CStringTranslate::getTranslateString((wchar_t *)local_388);
                    /* try { // try from 00b2d32c to 00b2d330 has its CatchHandler @ 00b2d979 */
        std::wstring::assign((wstring_conflict *)&updateLayout()::g_NoHeirloom);
                    /* try { // try from 00b2d334 to 00b2d338 has its CatchHandler @ 00b2df72 */
        std::wstring::~wstring(local_388);
      }
                    /* try { // try from 00b2d353 to 00b2d357 has its CatchHandler @ 00b2da74 */
      std::wstring::wstring(local_398,updateLayout()::g_NoHeirloom,&local_42);
                    /* try { // try from 00b2d366 to 00b2d36a has its CatchHandler @ 00b2da72 */
      STRINGS::StringConvertToUTF8((wstring_conflict *)local_3a8);
                    /* try { // try from 00b2d37e to 00b2d382 has its CatchHandler @ 00b2da66 */
      CEGUI::String::String(local_1c68,local_3a8[0]);
                    /* try { // try from 00b2d38a to 00b2d38e has its CatchHandler @ 00b2da61 */
      CEGUI::Window::setText(*(String **)(this + 0x48));
                    /* try { // try from 00b2d392 to 00b2d396 has its CatchHandler @ 00b2da66 */
      CEGUI::String::~String(local_1c68);
                    /* try { // try from 00b2d39a to 00b2d39e has its CatchHandler @ 00b2da72 */
      std::string::~string((string *)local_3a8);
                    /* try { // try from 00b2d3a2 to 00b2d3a6 has its CatchHandler @ 00b2da74 */
      std::wstring::~wstring(local_398);
    }
    else {
      if ((updateLayout()::g_PressRetire == '\0') &&
         (iVar10 = __cxa_guard_acquire(&updateLayout()::g_PressRetire), iVar10 != 0)) {
        updateLayout()::g_PressRetire = &DAT_01424558;
        __cxa_guard_release(&updateLayout()::g_PressRetire);
        __cxa_atexit(std::wstring::~wstring,&updateLayout()::g_PressRetire,&__dso_handle);
      }
      if (*(long *)(updateLayout()::g_PressRetire + -6) == 0) {
        CStringTranslate::getSinglton();
        CStringTranslate::getTranslateString((wchar_t *)local_358);
                    /* try { // try from 00b2c962 to 00b2c966 has its CatchHandler @ 00b2e005 */
        std::wstring::assign((wstring_conflict *)&updateLayout()::g_PressRetire);
                    /* try { // try from 00b2c96a to 00b2c96e has its CatchHandler @ 00b2df72 */
        std::wstring::~wstring(local_358);
      }
                    /* try { // try from 00b2c989 to 00b2c98d has its CatchHandler @ 00b2db55 */
      std::wstring::wstring(local_368,updateLayout()::g_PressRetire,&local_41);
                    /* try { // try from 00b2c99c to 00b2c9a0 has its CatchHandler @ 00b2db45 */
      STRINGS::StringConvertToUTF8((wstring_conflict *)local_378);
                    /* try { // try from 00b2c9b4 to 00b2c9b8 has its CatchHandler @ 00b2db35 */
      CEGUI::String::String(local_1bb8,local_378[0]);
                    /* try { // try from 00b2c9c0 to 00b2c9c4 has its CatchHandler @ 00b2db25 */
      CEGUI::Window::setText(*(String **)(this + 0x48));
                    /* try { // try from 00b2c9c8 to 00b2c9cc has its CatchHandler @ 00b2db35 */
      CEGUI::String::~String(local_1bb8);
                    /* try { // try from 00b2c9d0 to 00b2c9d4 has its CatchHandler @ 00b2db45 */
      std::string::~string((string *)local_378);
                    /* try { // try from 00b2c9d8 to 00b2c9dc has its CatchHandler @ 00b2db55 */
      std::wstring::~wstring(local_368);
    }
  }
switchD_00b2c090_caseD_17:
  CEGUI::Window::moveToBack();
  CEGUI::Window::moveToFront();
  CEGUI::Window::moveToFront();
  CEGUI::Window::moveToFront();
  if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_58[0] + -8);
    iVar10 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar10 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
    }
  }
  return;
}

/* address=00b2e0a0
   symbol=CEnchantMenu::createMenus */

/* WARNING: Removing unreachable block (ram,0x00b33735) */
/* WARNING: Removing unreachable block (ram,0x00b33b4a) */
/* WARNING: Removing unreachable block (ram,0x00b335ee) */
/* WARNING: Removing unreachable block (ram,0x00b33139) */
/* WARNING: Removing unreachable block (ram,0x00b33a2e) */
/* WARNING: Removing unreachable block (ram,0x00b33a70) */
/* WARNING: Removing unreachable block (ram,0x00b33901) */
/* WARNING: Removing unreachable block (ram,0x00b33d17) */
/* WARNING: Removing unreachable block (ram,0x00b33552) */
/* WARNING: Removing unreachable block (ram,0x00b331bb) */
/* WARNING: Removing unreachable block (ram,0x00b33394) */
/* WARNING: Removing unreachable block (ram,0x00b331b0) */
/* WARNING: Removing unreachable block (ram,0x00b330d4) */
/* WARNING: Removing unreachable block (ram,0x00b33965) */
/* WARNING: Removing unreachable block (ram,0x00b33a39) */
/* WARNING: Removing unreachable block (ram,0x00b33a7e) */
/* WARNING: Removing unreachable block (ram,0x00b33d25) */
/* WARNING: Removing unreachable block (ram,0x00b33bf5) */
/* WARNING: Removing unreachable block (ram,0x00b33ad9) */
/* WARNING: Removing unreachable block (ram,0x00b3364f) */
/* WARNING: Removing unreachable block (ram,0x00b3379e) */
/* WARNING: Removing unreachable block (ram,0x00b339c8) */
/* WARNING: Removing unreachable block (ram,0x00b33803) */
/* WARNING: Removing unreachable block (ram,0x00b33743) */
/* WARNING: Removing unreachable block (ram,0x00b339b6) */
/* WARNING: Removing unreachable block (ram,0x00b33547) */
/* CEnchantMenu::createMenus() */

void __thiscall CEnchantMenu::createMenus(CEnchantMenu *this)

{
  int *piVar1;
  char cVar2;
  byte bVar3;
  code *pcVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  undefined8 uVar9;
  long lVar10;
  char *pcVar11;
  char *pcVar12;
  UVector2 *pUVar13;
  CFileSystem *this_00;
  byte *pbVar14;
  char *pcVar15;
  undefined8 *puVar16;
  uint *puVar17;
  undefined4 *puVar18;
  float *pfVar19;
  float *pfVar20;
  length_error *plVar21;
  ulong uVar22;
  uint uVar23;
  byte *pbVar24;
  ulong uVar25;
  char *pcVar26;
  long lVar27;
  char *pcVar28;
  char *pcVar29;
  bool bVar30;
  float fVar31;
  float fVar32;
  undefined4 uVar33;
  undefined8 local_2618;
  ulong local_2610;
  undefined8 local_2608;
  undefined8 local_2600;
  undefined8 local_25f8;
  undefined4 local_25f0 [32];
  undefined4 *local_2570;
  long local_2568;
  ulong local_2560;
  undefined8 local_2558;
  undefined8 local_2550;
  undefined8 local_2548;
  undefined4 local_2540 [32];
  undefined4 *local_24c0;
  String local_24b8 [176];
  undefined8 local_2408;
  ulong local_2400;
  undefined8 local_23f8;
  undefined8 local_23f0;
  undefined8 local_23e8;
  undefined4 local_23e0 [32];
  undefined4 *local_2360;
  long local_2358;
  ulong local_2350;
  undefined8 local_2348;
  undefined8 local_2340;
  undefined8 local_2338;
  undefined4 local_2330 [32];
  undefined4 *local_22b0;
  long local_22a8;
  ulong local_22a0;
  undefined8 local_2298;
  undefined8 local_2290;
  undefined8 local_2288;
  uint local_2280 [32];
  uint *local_2200;
  undefined8 local_21f8;
  ulong local_21f0;
  undefined8 local_21e8;
  undefined8 local_21e0;
  undefined8 local_21d8;
  uint local_21d0 [5];
  uint local_21bc [27];
  uint *local_2150;
  undefined8 local_2148;
  ulong local_2140;
  undefined8 local_2138;
  undefined8 local_2130;
  undefined8 local_2128;
  uint local_2120 [11];
  uint local_20f4 [21];
  uint *local_20a0;
  undefined8 local_2098;
  ulong local_2090;
  undefined8 local_2088;
  undefined8 local_2080;
  undefined8 local_2078;
  undefined4 local_2070 [32];
  undefined4 *local_1ff0;
  long local_1fe8;
  ulong local_1fe0;
  undefined8 local_1fd8;
  undefined8 local_1fd0;
  undefined8 local_1fc8;
  uint local_1fc0 [32];
  uint *local_1f40;
  long local_1f38;
  ulong local_1f30;
  undefined8 local_1f28;
  undefined8 local_1f20;
  undefined8 local_1f18;
  uint local_1f10 [32];
  uint *local_1e90;
  undefined8 local_1e88;
  ulong local_1e80;
  undefined8 local_1e78;
  undefined8 local_1e70;
  undefined8 local_1e68;
  uint local_1e60 [5];
  uint local_1e4c [27];
  uint *local_1de0;
  undefined8 local_1dd8;
  ulong local_1dd0;
  undefined8 local_1dc8;
  undefined8 local_1dc0;
  undefined8 local_1db8;
  uint local_1db0 [11];
  uint local_1d84 [21];
  uint *local_1d30;
  undefined8 local_1d28;
  ulong local_1d20;
  undefined8 local_1d18;
  undefined8 local_1d10;
  undefined8 local_1d08;
  undefined4 local_1d00 [32];
  undefined4 *local_1c80;
  long local_1c78;
  ulong local_1c70;
  undefined8 local_1c68;
  undefined8 local_1c60;
  undefined8 local_1c58;
  uint local_1c50 [32];
  uint *local_1bd0;
  long local_1bc8;
  ulong local_1bc0;
  undefined8 local_1bb8;
  undefined8 local_1bb0;
  undefined8 local_1ba8;
  uint local_1ba0 [32];
  uint *local_1b20;
  undefined8 local_1b18;
  ulong local_1b10;
  undefined8 local_1b08;
  undefined8 local_1b00;
  undefined8 local_1af8;
  uint local_1af0 [10];
  uint local_1ac8 [22];
  uint *local_1a70;
  String local_1a68 [176];
  undefined8 local_19b8;
  ulong local_19b0;
  undefined8 local_19a8;
  undefined8 local_19a0;
  undefined8 local_1998;
  undefined4 local_1990 [32];
  undefined4 *local_1910;
  undefined8 local_1908;
  ulong local_1900;
  undefined8 local_18f8;
  undefined8 local_18f0;
  undefined8 local_18e8;
  uint local_18e0 [13];
  uint local_18ac [19];
  uint *local_1860;
  undefined8 local_1858;
  ulong local_1850;
  undefined8 local_1848;
  undefined8 local_1840;
  undefined8 local_1838;
  uint local_1830 [14];
  uint local_17f8 [18];
  uint *local_17b0;
  undefined8 local_17a8;
  ulong local_17a0;
  undefined8 local_1798;
  undefined8 local_1790;
  undefined8 local_1788;
  uint local_1780 [12];
  uint local_1750 [20];
  uint *local_1700;
  undefined8 local_16f8;
  ulong local_16f0;
  undefined8 local_16e8;
  undefined8 local_16e0;
  undefined8 local_16d8;
  uint local_16d0 [18];
  uint local_1688 [14];
  uint *local_1650;
  undefined8 local_1648;
  ulong local_1640;
  undefined8 local_1638;
  undefined8 local_1630;
  undefined8 local_1628;
  uint local_1620 [5];
  uint local_160c [27];
  uint *local_15a0;
  undefined8 local_1598;
  ulong local_1590;
  undefined8 local_1588;
  undefined8 local_1580;
  undefined8 local_1578;
  undefined4 local_1570 [32];
  undefined4 *local_14f0;
  long local_14e8;
  ulong local_14e0;
  undefined8 local_14d8;
  undefined8 local_14d0;
  undefined8 local_14c8;
  undefined4 local_14c0 [32];
  undefined4 *local_1440;
  long local_1438;
  ulong local_1430;
  undefined8 local_1428;
  undefined8 local_1420;
  undefined8 local_1418;
  uint local_1410 [32];
  uint *local_1390;
  undefined8 local_1388;
  ulong local_1380;
  undefined8 local_1378;
  undefined8 local_1370;
  undefined8 local_1368;
  uint local_1360 [8];
  uint local_1340 [24];
  uint *local_12e0;
  undefined8 local_12d8;
  ulong local_12d0;
  undefined8 local_12c8;
  undefined8 local_12c0;
  undefined8 local_12b8;
  uint local_12b0 [6];
  uint local_1298 [26];
  uint *local_1230;
  undefined8 local_1228;
  ulong local_1220;
  undefined8 local_1218;
  undefined8 local_1210;
  undefined8 local_1208;
  uint local_1200 [6];
  uint local_11e8 [26];
  uint *local_1180;
  undefined8 local_1178;
  ulong local_1170;
  undefined8 local_1168;
  undefined8 local_1160;
  undefined8 local_1158;
  uint local_1150 [5];
  uint local_113c [27];
  uint *local_10d0;
  Image local_10c8 [176];
  undefined8 local_1018;
  ulong local_1010;
  undefined8 local_1008;
  undefined8 local_1000;
  undefined8 local_ff8;
  uint local_ff0 [8];
  uint local_fd0 [24];
  uint *local_f70;
  undefined8 local_f68;
  ulong local_f60;
  undefined8 local_f58;
  undefined8 local_f50;
  undefined8 local_f48;
  undefined4 local_f40 [32];
  undefined4 *local_ec0;
  long local_eb8;
  ulong local_eb0;
  undefined8 local_ea8;
  undefined8 local_ea0;
  undefined8 local_e98;
  undefined4 local_e90 [32];
  undefined4 *local_e10;
  long local_e08;
  ulong local_e00;
  undefined8 local_df8;
  undefined8 local_df0;
  undefined8 local_de8;
  uint local_de0 [32];
  uint *local_d60;
  undefined8 local_d58;
  ulong local_d50;
  undefined8 local_d48;
  undefined8 local_d40;
  undefined8 local_d38;
  uint local_d30 [5];
  uint local_d1c [27];
  uint *local_cb0;
  long local_ca8;
  ulong local_ca0;
  undefined8 local_c98;
  undefined8 local_c90;
  undefined8 local_c88;
  undefined4 local_c80 [32];
  undefined4 *local_c00;
  undefined8 local_bf8;
  ulong local_bf0;
  undefined8 local_be8;
  undefined8 local_be0;
  undefined8 local_bd8;
  uint local_bd0 [5];
  uint local_bbc [27];
  uint *local_b50;
  undefined8 local_b48;
  ulong local_b40;
  undefined8 local_b38;
  undefined8 local_b30;
  undefined8 local_b28;
  uint local_b20 [11];
  uint local_af4 [21];
  uint *local_aa0;
  undefined8 local_a98;
  ulong local_a90;
  undefined8 local_a88;
  undefined8 local_a80;
  undefined8 local_a78;
  undefined4 local_a70 [32];
  undefined4 *local_9f0;
  long local_9e8;
  ulong local_9e0;
  undefined8 local_9d8;
  undefined8 local_9d0;
  undefined8 local_9c8;
  uint local_9c0 [32];
  uint *local_940;
  String local_938 [176];
  undefined8 local_888;
  ulong local_880;
  undefined8 local_878;
  undefined8 local_870;
  undefined8 local_868;
  uint local_860 [5];
  uint local_84c [27];
  uint *local_7e0;
  undefined8 local_7d8;
  ulong local_7d0;
  undefined8 local_7c8;
  undefined8 local_7c0;
  undefined8 local_7b8;
  uint local_7b0 [11];
  uint local_784 [21];
  uint *local_730;
  undefined8 local_728;
  ulong local_720;
  undefined8 local_718;
  undefined8 local_710;
  undefined8 local_708;
  undefined4 local_700 [32];
  undefined4 *local_680;
  long local_678;
  ulong local_670;
  undefined8 local_668;
  undefined8 local_660;
  undefined8 local_658;
  uint local_650 [32];
  uint *local_5d0;
  long local_5c8;
  ulong local_5c0;
  undefined8 local_5b8;
  undefined8 local_5b0;
  undefined8 local_5a8;
  uint local_5a0 [32];
  uint *local_520;
  long local_518;
  ulong local_510;
  undefined8 local_508;
  undefined8 local_500;
  undefined8 local_4f8;
  uint local_4f0 [32];
  uint *local_470;
  long local_468;
  ulong local_460;
  undefined8 local_458;
  undefined8 local_450;
  undefined8 local_448;
  uint local_440 [32];
  uint *local_3c0;
  undefined1 *local_3b8;
  long local_3b0;
  long local_3a8;
  undefined4 local_3a0;
  undefined4 local_39c;
  undefined1 *local_398;
  undefined1 local_390;
  undefined4 local_388;
  undefined4 local_384;
  undefined4 local_380;
  undefined4 local_37c;
  undefined4 local_378;
  undefined4 local_374;
  undefined4 local_370;
  void *local_368;
  undefined1 local_358 [48];
  float local_328;
  float local_324;
  float local_320;
  float local_31c;
  undefined4 local_308;
  undefined4 local_304;
  undefined4 local_300;
  undefined4 local_2fc;
  undefined4 local_2e8;
  undefined4 local_2e4;
  undefined4 local_2e0;
  undefined4 local_2dc;
  undefined8 local_2c8;
  undefined8 local_2c0;
  BoundSlot *local_2a8;
  int *local_2a0;
  BoundSlot *local_298;
  int *local_290;
  BoundSlot *local_288;
  int *local_280;
  BoundSlot *local_278;
  int *local_270;
  undefined4 local_268;
  undefined4 local_264;
  undefined4 local_260;
  undefined4 local_25c;
  undefined4 local_258;
  undefined4 local_254;
  undefined4 local_250;
  undefined4 local_24c;
  BoundSlot *local_248;
  int *local_240;
  undefined4 local_238;
  undefined4 local_234;
  undefined4 local_230;
  undefined4 local_22c;
  undefined4 local_228;
  undefined4 local_224;
  undefined4 local_220;
  undefined4 local_21c;
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
  long local_f8 [2];
  undefined8 *local_e8 [2];
  undefined8 *local_d8 [2];
  undefined8 *local_c8 [2];
  undefined8 *local_b8 [2];
  long local_a8 [2];
  long local_98 [2];
  long local_88 [2];
  undefined8 *local_78 [3];
  allocator local_5b [2];
  allocator local_59 [2];
  allocator local_57 [2];
  allocator local_55 [2];
  allocator local_53 [2];
  allocator local_51 [4];
  allocator local_4d [4];
  allocator local_49 [3];
  allocator local_46 [2];
  allocator local_44 [2];
  allocator local_42 [2];
  allocator local_40 [2];
  allocator local_3e;
  allocator local_3d;
  allocator local_3c;
  allocator local_3b;
  allocator local_3a;
  allocator local_39 [9];

  iVar5 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0x78),KSETTINGS_RES_WIDTH);
  iVar6 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0x78),KSETTINGS_RES_HEIGHT)
  ;
  uVar9 = CResourceManager::createGenericModel
                    (*(CResourceManager **)(this + 0xa8),*(SceneManager **)(this + 0x88),
                     L"media/ui/models/dropdown/dropdown.mesh",L"",false,false,false);
  *(undefined8 *)(this + 0xa0) = uVar9;
  local_368 = (void *)0x0;
  local_370 = 1;
  local_388 = 0xc7c35000;
  local_384 = 0xc7c35000;
  local_380 = 0xc7c35000;
  local_37c = 0x47c35000;
  local_378 = 0x47c35000;
  local_374 = 0x47c35000;
                    /* try { // try from 00b2e174 to 00b2e2fa has its CatchHandler @ 00b3326c */
  lVar10 = Ogre::Entity::getMesh();
  Ogre::Mesh::_setBounds(*(AxisAlignedBox **)(lVar10 + 8),SUB81(&local_388,0));
  fVar31 = (float)iVar6 / DAT_00fc6774;
  pcVar4 = *(code **)(**(long **)(this + 0xa0) + 0x58);
  fVar32 = (float)CDynamicPropertyFile::GetFloat
                            (*(CDynamicPropertyFile **)(this + 0x78),KSETTINGS_YRATIO);
  (*pcVar4)(DAT_00fa86f4 * (((float)iVar5 - fVar31) / fVar32) - DAT_00fe6518,0,
            *(undefined8 *)(this + 0xa0));
  (**(code **)(**(long **)(this + 0xa0) + 0x50))(*(long **)(this + 0xa0),0);
  pcVar26 = (char *)0x0;
  pcVar28 = "GuiLook";
  local_460 = 0x20;
  local_458 = 0;
  pcVar29 = "GuiLook";
  local_448 = 0;
  local_450 = 0;
  local_3c0 = (uint *)0x0;
  local_468 = 0;
  local_440[0] = 0;
  cVar2 = s_GuiLook_00fe493c[0];
  while (pcVar29 = pcVar29 + 1, cVar2 != '\0') {
    pcVar26 = pcVar29 + -0xfe493c;
    cVar2 = *pcVar29;
  }
  if (pcVar26 == CEGUI::String::npos) {
                    /* try { // try from 00b328d8 to 00b328dc has its CatchHandler @ 00b33894 */
    std::string::string((string *)local_158,"Length for utf8 encoded string can not be \'npos\'",
                        &local_3e);
    plVar21 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00b328f0 to 00b328f4 has its CatchHandler @ 00b3399c */
    std::length_error::length_error(plVar21,(string *)local_158);
    if ((allocator *)(local_158[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_158[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_158[0] + -0x18));
      }
    }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00b3291b to 00b3291f has its CatchHandler @ 00b3326c */
    __cxa_throw(plVar21,&std::length_error::typeinfo,std::length_error::~length_error);
  }
  lVar10 = 0;
  pcVar29 = pcVar26;
  pbVar14 = (byte *)"GuiLook";
  while (pcVar29 != (char *)0x0) {
    bVar3 = *pbVar14;
    pcVar11 = pcVar29 + -1;
    pbVar24 = pbVar14 + 1;
    if ((char)bVar3 < '\0') {
      if (bVar3 < 0xe0) {
        pcVar11 = pcVar29 + -2;
        pbVar24 = pbVar14 + 2;
      }
      else if (bVar3 < 0xf0) {
        pcVar11 = pcVar29 + -3;
        pbVar24 = pbVar14 + 3;
      }
      else {
        pcVar11 = pcVar29 + -3;
        pbVar24 = pbVar14 + 4;
      }
    }
    lVar10 = lVar10 + 1;
    pcVar29 = pcVar11;
    pbVar14 = pbVar24;
  }
  CEGUI::String::grow((ulong)&local_468);
  if (local_460 < 0x21) {
    puVar17 = local_440;
    if (pcVar26 != (char *)0x0) goto LAB_00b2e31a;
LAB_00b2e4b0:
    if (s_GuiLook_00fe493c[0] != '\0') {
      do {
        pcVar28 = pcVar28 + 1;
        pcVar26 = pcVar28 + -0xfe493c;
      } while (*pcVar28 != '\0');
      bVar30 = pcVar26 != (char *)0x0 && local_460 != 0;
      goto LAB_00b2e320;
    }
  }
  else {
    puVar17 = local_3c0;
    if (pcVar26 == (char *)0x0) goto LAB_00b2e4b0;
LAB_00b2e31a:
    bVar30 = local_460 != 0;
LAB_00b2e320:
    if (bVar30) {
      pcVar29 = (char *)0x0;
      uVar8 = 0;
      uVar22 = local_460;
      do {
        bVar3 = pcVar29[0xfe493c];
        uVar23 = (uint)bVar3;
        uVar7 = uVar8 + 1;
        if ((char)bVar3 < '\0') {
          uVar23 = (uint)bVar3;
          if (0xdf < bVar3) {
            if (bVar3 < 0xf0) {
              uVar25 = (ulong)uVar7;
              uVar7 = uVar8 + 3;
              uVar23 = (byte)"GuiLook"[uVar8 + 2] & 0x3f | (uVar23 & 0xf) << 0xc |
                       ((byte)"GuiLook"[uVar25] & 0x3f) << 6;
            }
            else {
              uVar25 = (ulong)uVar7;
              uVar7 = uVar8 + 4;
              uVar23 = ((byte)"GuiLook"[uVar25] & 0x3f) << 0xc | (byte)"GuiLook"[uVar8 + 3] & 0x3f |
                       (uVar23 & 7) << 0x12 | ((byte)"GuiLook"[uVar8 + 2] & 0x3f) << 6;
            }
            goto LAB_00b2e333;
          }
          uVar8 = uVar8 + 2;
          *puVar17 = (byte)"GuiLook"[uVar7] & 0x3f | (uVar23 & 0x1f) << 6;
        }
        else {
LAB_00b2e333:
          *puVar17 = uVar23;
          uVar8 = uVar7;
        }
        pcVar29 = (char *)(ulong)uVar8;
        if ((pcVar26 <= pcVar29) || (uVar22 = uVar22 - 1, uVar22 == 0)) break;
        puVar17 = puVar17 + 1;
      } while( true );
    }
  }
  puVar17 = local_440;
  if (0x20 < local_460) {
    puVar17 = local_3c0;
  }
  puVar17[lVar10] = 0;
  local_468 = lVar10;
                    /* try { // try from 00b2e3c1 to 00b2e3c5 has its CatchHandler @ 00b33475 */
  CEGUI::ImagesetManager::getImageset(CEGUI::Singleton<CEGUI::ImagesetManager>::ms_Singleton);
                    /* try { // try from 00b2e3c9 to 00b2e572 has its CatchHandler @ 00b3326c */
  CEGUI::String::~String((String *)&local_468);
  pcVar26 = (char *)0x0;
  pcVar28 = "UIIcons";
  local_510 = 0x20;
  local_508 = 0;
  pcVar29 = "UIIcons";
  local_4f8 = 0;
  local_500 = 0;
  local_470 = (uint *)0x0;
  local_518 = 0;
  local_4f0[0] = 0;
  cVar2 = s_UIIcons_00fe49dd[0];
  while (pcVar29 = pcVar29 + 1, cVar2 != '\0') {
    pcVar26 = pcVar29 + -0xfe49dd;
    cVar2 = *pcVar29;
  }
  if (pcVar26 == CEGUI::String::npos) {
                    /* try { // try from 00b329e8 to 00b329ec has its CatchHandler @ 00b339c3 */
    std::string::string((string *)local_168,"Length for utf8 encoded string can not be \'npos\'",
                        local_40);
    plVar21 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00b32a00 to 00b32a04 has its CatchHandler @ 00b3384a */
    std::length_error::length_error(plVar21,(string *)local_168);
    if ((allocator *)(local_168[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_168[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_168[0] + -0x18));
      }
    }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00b32a2b to 00b32a2f has its CatchHandler @ 00b3326c */
    __cxa_throw(plVar21,&std::length_error::typeinfo,std::length_error::~length_error);
  }
  lVar10 = 0;
  pcVar29 = pcVar26;
  pbVar14 = (byte *)"UIIcons";
  while (pcVar29 != (char *)0x0) {
    bVar3 = *pbVar14;
    pcVar11 = pcVar29 + -1;
    pbVar24 = pbVar14 + 1;
    if ((char)bVar3 < '\0') {
      if (bVar3 < 0xe0) {
        pcVar11 = pcVar29 + -2;
        pbVar24 = pbVar14 + 2;
      }
      else if (bVar3 < 0xf0) {
        pcVar11 = pcVar29 + -3;
        pbVar24 = pbVar14 + 3;
      }
      else {
        pcVar11 = pcVar29 + -3;
        pbVar24 = pbVar14 + 4;
      }
    }
    lVar10 = lVar10 + 1;
    pcVar29 = pcVar11;
    pbVar14 = pbVar24;
  }
  CEGUI::String::grow((ulong)&local_518);
  puVar17 = local_4f0;
  if (0x20 < local_510) {
    puVar17 = local_470;
  }
  if (pcVar26 == (char *)0x0) {
    if (s_UIIcons_00fe49dd[0] != '\0') {
      do {
        pcVar28 = pcVar28 + 1;
        pcVar26 = pcVar28 + -0xfe49dd;
      } while (*pcVar28 != '\0');
      bVar30 = pcVar26 != (char *)0x0 && local_510 != 0;
      goto LAB_00b2e59c;
    }
  }
  else {
    bVar30 = local_510 != 0;
LAB_00b2e59c:
    if (bVar30) {
      pcVar29 = (char *)0x0;
      uVar8 = 0;
      uVar22 = local_510;
      do {
        bVar3 = pcVar29[0xfe49dd];
        uVar23 = (uint)bVar3;
        uVar7 = uVar8 + 1;
        if ((char)bVar3 < '\0') {
          uVar23 = (uint)bVar3;
          if (0xdf < bVar3) {
            if (bVar3 < 0xf0) {
              uVar25 = (ulong)uVar7;
              uVar7 = uVar8 + 3;
              uVar23 = (byte)"UIIcons"[uVar8 + 2] & 0x3f | (uVar23 & 0xf) << 0xc |
                       ((byte)"UIIcons"[uVar25] & 0x3f) << 6;
            }
            else {
              uVar25 = (ulong)uVar7;
              uVar7 = uVar8 + 4;
              uVar23 = ((byte)"UIIcons"[uVar25] & 0x3f) << 0xc | (byte)"UIIcons"[uVar8 + 3] & 0x3f |
                       (uVar23 & 7) << 0x12 | ((byte)"UIIcons"[uVar8 + 2] & 0x3f) << 6;
            }
            goto LAB_00b2e5b3;
          }
          uVar8 = uVar8 + 2;
          *puVar17 = (byte)"UIIcons"[uVar7] & 0x3f | (uVar23 & 0x1f) << 6;
        }
        else {
LAB_00b2e5b3:
          *puVar17 = uVar23;
          uVar8 = uVar7;
        }
        pcVar29 = (char *)(ulong)uVar8;
        if ((pcVar26 <= pcVar29) || (uVar22 = uVar22 - 1, uVar22 == 0)) break;
        puVar17 = puVar17 + 1;
      } while( true );
    }
  }
  puVar17 = local_4f0;
  if (0x20 < local_510) {
    puVar17 = local_470;
  }
  puVar17[lVar10] = 0;
  local_518 = lVar10;
                    /* try { // try from 00b2e641 to 00b2e645 has its CatchHandler @ 00b33425 */
  uVar9 = CEGUI::ImagesetManager::getImageset
                    (CEGUI::Singleton<CEGUI::ImagesetManager>::ms_Singleton);
  *(undefined8 *)(this + 0xf8) = uVar9;
                    /* try { // try from 00b2e650 to 00b2e6b9 has its CatchHandler @ 00b3326c */
  CEGUI::String::~String((String *)&local_518);
  local_720 = 0x20;
  local_718 = 0;
  local_708 = 0;
  local_710 = 0;
  local_680 = (undefined4 *)0x0;
  local_728 = 0;
  local_700[0] = 0;
  CEGUI::String::grow((ulong)&local_728);
  local_728 = 0;
  puVar18 = local_700;
  if (0x20 < local_720) {
    puVar18 = local_680;
  }
  *puVar18 = 0;
  pcVar28 = (char *)0x0;
  pcVar29 = "EnchantSheet";
  local_670 = 0x20;
  local_668 = 0;
  local_658 = 0;
  local_660 = 0;
  pcVar26 = "EnchantSheet";
  local_5d0 = (uint *)0x0;
  local_678 = 0;
  local_650[0] = 0;
  cVar2 = s_EnchantSheet_00fee5e5[0];
  while (pcVar26 = pcVar26 + 1, cVar2 != '\0') {
    pcVar28 = pcVar26 + -0xfee5e5;
    cVar2 = *pcVar26;
  }
  if (pcVar28 == CEGUI::String::npos) {
                    /* try { // try from 00b32ae8 to 00b32aec has its CatchHandler @ 00b33815 */
    std::string::string((string *)local_178,"Length for utf8 encoded string can not be \'npos\'",
                        local_42);
    plVar21 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00b32b00 to 00b32b04 has its CatchHandler @ 00b337e9 */
    std::length_error::length_error(plVar21,(string *)local_178);
    if ((allocator *)(local_178[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_178[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_178[0] + -0x18));
      }
    }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00b32b2b to 00b32b2f has its CatchHandler @ 00b3344e */
    __cxa_throw(plVar21,&std::length_error::typeinfo,std::length_error::~length_error);
  }
  lVar10 = 0;
  pcVar26 = pcVar28;
  pbVar14 = (byte *)"EnchantSheet";
  while (pcVar26 != (char *)0x0) {
    bVar3 = *pbVar14;
    pcVar11 = pcVar26 + -1;
    pbVar24 = pbVar14 + 1;
    if ((char)bVar3 < '\0') {
      if (bVar3 < 0xe0) {
        pcVar11 = pcVar26 + -2;
        pbVar24 = pbVar14 + 2;
      }
      else if (bVar3 < 0xf0) {
        pcVar11 = pcVar26 + -3;
        pbVar24 = pbVar14 + 3;
      }
      else {
        pcVar11 = pcVar26 + -3;
        pbVar24 = pbVar14 + 4;
      }
    }
    lVar10 = lVar10 + 1;
    pcVar26 = pcVar11;
    pbVar14 = pbVar24;
  }
                    /* try { // try from 00b2e81e to 00b2e822 has its CatchHandler @ 00b3344e */
  CEGUI::String::grow((ulong)&local_678);
  puVar17 = local_650;
  if (0x20 < local_670) {
    puVar17 = local_5d0;
  }
  if (pcVar28 == (char *)0x0) {
    if (s_EnchantSheet_00fee5e5[0] != '\0') {
      do {
        pcVar29 = pcVar29 + 1;
        pcVar28 = pcVar29 + -0xfee5e5;
      } while (*pcVar29 != '\0');
      bVar30 = pcVar28 != (char *)0x0 && local_670 != 0;
      goto LAB_00b2e84c;
    }
  }
  else {
    bVar30 = local_670 != 0;
LAB_00b2e84c:
    if (bVar30) {
      pcVar29 = (char *)0x0;
      uVar8 = 0;
      uVar22 = local_670;
      do {
        bVar3 = pcVar29[0xfee5e5];
        uVar23 = (uint)bVar3;
        uVar7 = uVar8 + 1;
        if ((char)bVar3 < '\0') {
          uVar23 = (uint)bVar3;
          if (0xdf < bVar3) {
            if (bVar3 < 0xf0) {
              uVar25 = (ulong)uVar7;
              uVar7 = uVar8 + 3;
              uVar23 = (byte)"EnchantSheet"[uVar8 + 2] & 0x3f | (uVar23 & 0xf) << 0xc |
                       ((byte)"EnchantSheet"[uVar25] & 0x3f) << 6;
            }
            else {
              uVar25 = (ulong)uVar7;
              uVar7 = uVar8 + 4;
              uVar23 = ((byte)"EnchantSheet"[uVar25] & 0x3f) << 0xc |
                       (byte)"EnchantSheet"[uVar8 + 3] & 0x3f | (uVar23 & 7) << 0x12 |
                       ((byte)"EnchantSheet"[uVar8 + 2] & 0x3f) << 6;
            }
            goto LAB_00b2e863;
          }
          uVar8 = uVar8 + 2;
          *puVar17 = (byte)"EnchantSheet"[uVar7] & 0x3f | (uVar23 & 0x1f) << 6;
        }
        else {
LAB_00b2e863:
          *puVar17 = uVar23;
          uVar8 = uVar7;
        }
        pcVar29 = (char *)(ulong)uVar8;
        if ((pcVar28 <= pcVar29) || (uVar22 = uVar22 - 1, uVar22 == 0)) break;
        puVar17 = puVar17 + 1;
      } while( true );
    }
  }
  puVar17 = local_650;
  if (0x20 < local_670) {
    puVar17 = local_5d0;
  }
  puVar17[lVar10] = 0;
  pcVar28 = (char *)0x0;
  local_5c0 = 0x20;
  local_5b8 = 0;
  pcVar29 = "DefaultWindow";
  local_5a8 = 0;
  local_5b0 = 0;
  local_520 = (uint *)0x0;
  local_5c8 = 0;
  local_5a0[0] = 0;
  pcVar26 = "DefaultWindow";
  cVar2 = s_DefaultWindow_00fe499d[0];
  while (pcVar29 = pcVar29 + 1, cVar2 != '\0') {
    pcVar28 = pcVar29 + -0xfe499d;
    cVar2 = *pcVar29;
  }
  local_678 = lVar10;
  if (pcVar28 == CEGUI::String::npos) {
                    /* try { // try from 00b32be6 to 00b32bea has its CatchHandler @ 00b33799 */
    std::string::string((string *)local_188,"Length for utf8 encoded string can not be \'npos\'",
                        local_44);
    plVar21 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00b32bfe to 00b32c02 has its CatchHandler @ 00b3377f */
    std::length_error::length_error(plVar21,(string *)local_188);
    if ((allocator *)(local_188[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_188[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_188[0] + -0x18));
      }
    }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00b32c29 to 00b32c2d has its CatchHandler @ 00b33437 */
    __cxa_throw(plVar21,&std::length_error::typeinfo,std::length_error::~length_error);
  }
  lVar10 = 0;
  pcVar29 = pcVar28;
  pbVar14 = (byte *)"DefaultWindow";
  while (pcVar29 != (char *)0x0) {
    bVar3 = *pbVar14;
    pcVar11 = pcVar29 + -1;
    pbVar24 = pbVar14 + 1;
    if ((char)bVar3 < '\0') {
      if (bVar3 < 0xe0) {
        pcVar11 = pcVar29 + -2;
        pbVar24 = pbVar14 + 2;
      }
      else if (bVar3 < 0xf0) {
        pcVar11 = pcVar29 + -3;
        pbVar24 = pbVar14 + 3;
      }
      else {
        pcVar11 = pcVar29 + -3;
        pbVar24 = pbVar14 + 4;
      }
    }
    lVar10 = lVar10 + 1;
    pcVar29 = pcVar11;
    pbVar14 = pbVar24;
  }
                    /* try { // try from 00b2ea7e to 00b2ea82 has its CatchHandler @ 00b33437 */
  CEGUI::String::grow((ulong)&local_5c8);
  puVar17 = local_5a0;
  if (0x20 < local_5c0) {
    puVar17 = local_520;
  }
  if (pcVar28 == (char *)0x0) {
    pcVar29 = "DefaultWindow";
    if (s_DefaultWindow_00fe499d[0] != '\0') {
      do {
        pcVar29 = pcVar29 + 1;
        pcVar28 = pcVar29 + -0xfe499d;
      } while (*pcVar29 != '\0');
      bVar30 = pcVar28 != (char *)0x0 && local_5c0 != 0;
      goto LAB_00b2eaac;
    }
  }
  else {
    bVar30 = local_5c0 != 0;
LAB_00b2eaac:
    if (bVar30) {
      pcVar29 = (char *)0x0;
      uVar8 = 0;
      uVar22 = local_5c0;
      do {
        bVar3 = pcVar29[0xfe499d];
        uVar23 = (uint)bVar3;
        uVar7 = uVar8 + 1;
        if ((char)bVar3 < '\0') {
          uVar23 = (uint)bVar3;
          if (0xdf < bVar3) {
            if (bVar3 < 0xf0) {
              uVar25 = (ulong)uVar7;
              uVar7 = uVar8 + 3;
              uVar23 = (byte)"DefaultWindow"[uVar8 + 2] & 0x3f | (uVar23 & 0xf) << 0xc |
                       ((byte)"DefaultWindow"[uVar25] & 0x3f) << 6;
            }
            else {
              uVar25 = (ulong)uVar7;
              uVar7 = uVar8 + 4;
              uVar23 = ((byte)"DefaultWindow"[uVar25] & 0x3f) << 0xc |
                       (byte)"DefaultWindow"[uVar8 + 3] & 0x3f | (uVar23 & 7) << 0x12 |
                       ((byte)"DefaultWindow"[uVar8 + 2] & 0x3f) << 6;
            }
            goto LAB_00b2eac3;
          }
          uVar8 = uVar8 + 2;
          *puVar17 = (byte)"DefaultWindow"[uVar7] & 0x3f | (uVar23 & 0x1f) << 6;
        }
        else {
LAB_00b2eac3:
          *puVar17 = uVar23;
          uVar8 = uVar7;
        }
        pcVar29 = (char *)(ulong)uVar8;
        if ((pcVar28 <= pcVar29) || (uVar22 = uVar22 - 1, uVar22 == 0)) break;
        puVar17 = puVar17 + 1;
      } while( true );
    }
  }
  puVar17 = local_5a0;
  if (0x20 < local_5c0) {
    puVar17 = local_520;
  }
  puVar17[lVar10] = 0;
  local_5c8 = lVar10;
                    /* try { // try from 00b2eb57 to 00b2eb5b has its CatchHandler @ 00b3343c */
  uVar9 = CEGUI::WindowManager::createWindow
                    (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,(String *)&local_5c8,
                     (String *)&local_678);
  *(undefined8 *)(this + 0x20) = uVar9;
                    /* try { // try from 00b2eb63 to 00b2eb67 has its CatchHandler @ 00b33437 */
  CEGUI::String::~String((String *)&local_5c8);
                    /* try { // try from 00b2eb6b to 00b2eb6f has its CatchHandler @ 00b3344e */
  CEGUI::String::~String((String *)&local_678);
                    /* try { // try from 00b2eb73 to 00b2eb77 has its CatchHandler @ 00b3326c */
  CEGUI::String::~String((String *)&local_728);
  local_224 = 0;
  local_228 = 0x3f800000;
  local_21c = 0;
  local_220 = 0x3f800000;
                    /* try { // try from 00b2ebb0 to 00b2ebb4 has its CatchHandler @ 00b333cf */
  CEGUI::Window::setSize(*(UVector2 **)(this + 0x20));
  local_880 = 0x20;
  local_878 = 0;
  local_868 = 0;
  local_870 = 0;
  local_7e0 = (uint *)0x0;
  local_888 = 0;
  local_860[0] = 0;
                    /* try { // try from 00b2ec18 to 00b2ec1c has its CatchHandler @ 00b3326c */
  CEGUI::String::grow((ulong)&local_888);
  puVar17 = local_860;
  if (0x20 < local_880) {
    puVar17 = local_7e0;
  }
  pcVar29 = "False";
  do {
    bVar3 = *pcVar29;
    pcVar29 = pcVar29 + 1;
    *puVar17 = (uint)bVar3;
    puVar17 = puVar17 + 1;
  } while ((byte *)pcVar29 != (byte *)0xfe603f);
  local_888 = 5;
  puVar17 = local_84c;
  if (0x20 < local_880) {
    puVar17 = local_7e0 + 5;
  }
  *puVar17 = 0;
  local_7d0 = 0x20;
  local_7c8 = 0;
  local_7b8 = 0;
  local_7c0 = 0;
  local_730 = (uint *)0x0;
  local_7d8 = 0;
  local_7b0[0] = 0;
                    /* try { // try from 00b2ece6 to 00b2ecea has its CatchHandler @ 00b333d4 */
  CEGUI::String::grow((ulong)&local_7d8);
  puVar17 = local_7b0;
  if (0x20 < local_7d0) {
    puVar17 = local_730;
  }
  pcVar29 = "RiseOnClick";
  do {
    bVar3 = *pcVar29;
    pcVar29 = pcVar29 + 1;
    *puVar17 = (uint)bVar3;
    puVar17 = puVar17 + 1;
  } while ((byte *)pcVar29 != (byte *)0xfe6039);
  local_7d8 = 0xb;
  puVar17 = local_784;
  if (0x20 < local_7d0) {
    puVar17 = local_730 + 0xb;
  }
  *puVar17 = 0;
                    /* try { // try from 00b2ed5c to 00b2ed60 has its CatchHandler @ 00b333e6 */
  CEGUI::PropertySet::setProperty(*(String **)(this + 0x20),(String *)&local_7d8);
                    /* try { // try from 00b2ed64 to 00b2ed68 has its CatchHandler @ 00b333d4 */
  CEGUI::String::~String((String *)&local_7d8);
                    /* try { // try from 00b2ed6c to 00b2ed70 has its CatchHandler @ 00b3326c */
  CEGUI::String::~String((String *)&local_888);
  local_234 = 0;
  local_238 = 0;
  local_22c = 0;
  local_230 = 0;
                    /* try { // try from 00b2eda9 to 00b2edad has its CatchHandler @ 00b333f5 */
  CEGUI::Window::setPosition(*(UVector2 **)(this + 0x20));
  *(undefined1 *)(*(long *)(this + 0x20) + 0x3e2) = 1;
                    /* try { // try from 00b2edbf to 00b2edd9 has its CatchHandler @ 00b3326c */
  CEGUI::Window::setZOrderingEnabled(SUB81(*(undefined8 *)(this + 0x20),0));
  pcVar4 = *(code **)(*(long *)(*(long *)(this + 0x20) + 0x38) + 0x10);
  local_78[0] = operator_new(0x20);
  *local_78[0] = &PTR__MemberFunctionSlot_00fef410;
  local_78[0][2] = 0;
  local_78[0][1] = handle_MouseThrough;
  local_78[0][3] = this;
                    /* try { // try from 00b2ee1d to 00b2ee52 has its CatchHandler @ 00b33482 */
  (*pcVar4)(&local_248,*(long *)(this + 0x20) + 0x38,CEGUI::Window::EventMouseMove,
            (SubscriberSlot *)local_78);
  if ((local_248 != (BoundSlot *)0x0) &&
     (iVar5 = *local_240, *local_240 = iVar5 + -1, iVar5 + -1 == 0)) {
    if (local_248 != (BoundSlot *)0x0) {
      CEGUI::BoundSlot::~BoundSlot(local_248);
      operator_delete(local_248);
    }
    operator_delete(local_240);
    local_248 = (BoundSlot *)0x0;
    local_240 = (int *)0x0;
  }
                    /* try { // try from 00b2ee83 to 00b2eeec has its CatchHandler @ 00b3326c */
  CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_78);
  local_a90 = 0x20;
  local_a88 = 0;
  local_a78 = 0;
  local_a80 = 0;
  local_9f0 = (undefined4 *)0x0;
  local_a98 = 0;
  local_a70[0] = 0;
  CEGUI::String::grow((ulong)&local_a98);
  local_a98 = 0;
  puVar18 = local_a70;
  if (0x20 < local_a90) {
    puVar18 = local_9f0;
  }
  *puVar18 = 0;
  pcVar28 = (char *)0x0;
  pcVar11 = "EnchantClickBarrier";
  local_9e0 = 0x20;
  local_9d8 = 0;
  local_9c8 = 0;
  local_9d0 = 0;
  pcVar29 = "EnchantClickBarrier";
  local_940 = (uint *)0x0;
  local_9e8 = 0;
  local_9c0[0] = 0;
  cVar2 = s_EnchantClickBarrier_00fee5d1[0];
  while (pcVar29 = pcVar29 + 1, cVar2 != '\0') {
    pcVar28 = pcVar29 + -0xfee5d1;
    cVar2 = *pcVar29;
  }
  if (pcVar28 == CEGUI::String::npos) {
                    /* try { // try from 00b32c80 to 00b32c84 has its CatchHandler @ 00b3374e */
    std::string::string((string *)local_198,"Length for utf8 encoded string can not be \'npos\'",
                        local_46);
    plVar21 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00b32c98 to 00b32c9c has its CatchHandler @ 00b336f3 */
    std::length_error::length_error(plVar21,(string *)local_198);
    if ((allocator *)(local_198[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_198[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_198[0] + -0x18));
      }
    }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00b32cc3 to 00b32cc7 has its CatchHandler @ 00b3322a */
    __cxa_throw(plVar21,&std::length_error::typeinfo,std::length_error::~length_error);
  }
  lVar10 = 0;
  pcVar29 = pcVar28;
  pbVar14 = (byte *)"EnchantClickBarrier";
  while (pcVar29 != (char *)0x0) {
    bVar3 = *pbVar14;
    pcVar12 = pcVar29 + -1;
    pbVar24 = pbVar14 + 1;
    if ((char)bVar3 < '\0') {
      if (bVar3 < 0xe0) {
        pcVar12 = pcVar29 + -2;
        pbVar24 = pbVar14 + 2;
      }
      else if (bVar3 < 0xf0) {
        pcVar12 = pcVar29 + -3;
        pbVar24 = pbVar14 + 3;
      }
      else {
        pcVar12 = pcVar29 + -3;
        pbVar24 = pbVar14 + 4;
      }
    }
    lVar10 = lVar10 + 1;
    pcVar29 = pcVar12;
    pbVar14 = pbVar24;
  }
                    /* try { // try from 00b2f0ae to 00b2f0b2 has its CatchHandler @ 00b3322a */
  CEGUI::String::grow((ulong)&local_9e8);
  puVar17 = local_9c0;
  if (0x20 < local_9e0) {
    puVar17 = local_940;
  }
  if (pcVar28 == (char *)0x0) {
    if (s_EnchantClickBarrier_00fee5d1[0] != '\0') {
      do {
        pcVar11 = pcVar11 + 1;
        pcVar28 = pcVar11 + -0xfee5d1;
      } while (*pcVar11 != '\0');
      bVar30 = pcVar28 != (char *)0x0 && local_9e0 != 0;
      goto LAB_00b2f0dc;
    }
  }
  else {
    bVar30 = local_9e0 != 0;
LAB_00b2f0dc:
    if (bVar30) {
      pcVar29 = (char *)0x0;
      uVar8 = 0;
      uVar22 = local_9e0;
      do {
        bVar3 = pcVar29[0xfee5d1];
        uVar23 = (uint)bVar3;
        uVar7 = uVar8 + 1;
        if ((char)bVar3 < '\0') {
          uVar23 = (uint)bVar3;
          if (0xdf < bVar3) {
            if (bVar3 < 0xf0) {
              uVar25 = (ulong)uVar7;
              uVar7 = uVar8 + 3;
              uVar23 = (byte)"EnchantClickBarrier"[uVar8 + 2] & 0x3f | (uVar23 & 0xf) << 0xc |
                       ((byte)"EnchantClickBarrier"[uVar25] & 0x3f) << 6;
            }
            else {
              uVar25 = (ulong)uVar7;
              uVar7 = uVar8 + 4;
              uVar23 = ((byte)"EnchantClickBarrier"[uVar25] & 0x3f) << 0xc |
                       (byte)"EnchantClickBarrier"[uVar8 + 3] & 0x3f | (uVar23 & 7) << 0x12 |
                       ((byte)"EnchantClickBarrier"[uVar8 + 2] & 0x3f) << 6;
            }
            goto LAB_00b2f0f3;
          }
          uVar8 = uVar8 + 2;
          *puVar17 = (byte)"EnchantClickBarrier"[uVar7] & 0x3f | (uVar23 & 0x1f) << 6;
        }
        else {
LAB_00b2f0f3:
          *puVar17 = uVar23;
          uVar8 = uVar7;
        }
        pcVar29 = (char *)(ulong)uVar8;
        if ((pcVar28 <= pcVar29) || (uVar22 = uVar22 - 1, uVar22 == 0)) break;
        puVar17 = puVar17 + 1;
      } while( true );
    }
  }
  puVar17 = local_9c0;
  if (0x20 < local_9e0) {
    puVar17 = local_940;
  }
  puVar17[lVar10] = 0;
  local_9e8 = lVar10;
                    /* try { // try from 00b2f187 to 00b2f18b has its CatchHandler @ 00b3323c */
  CEGUI::String::String(local_938,(uchar *)"DefaultWindow");
                    /* try { // try from 00b2f19c to 00b2f1a0 has its CatchHandler @ 00b332d9 */
  pUVar13 = (UVector2 *)
            CEGUI::WindowManager::createWindow
                      (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,local_938,
                       (String *)&local_9e8);
                    /* try { // try from 00b2f1a7 to 00b2f1ab has its CatchHandler @ 00b3323c */
  CEGUI::String::~String(local_938);
                    /* try { // try from 00b2f1af to 00b2f1b3 has its CatchHandler @ 00b3322a */
  CEGUI::String::~String((String *)&local_9e8);
                    /* try { // try from 00b2f1b7 to 00b2f1db has its CatchHandler @ 00b3326c */
  CEGUI::String::~String((String *)&local_a98);
  CEGUI::Window::addChildWindow(*(Window **)(this + 0x20));
  uVar33 = CGameUI::scaledY(*(CGameUI **)(this + 0x80),DAT_00fa4804);
                    /* try { // try from 00b2f1f1 to 00b2f1f5 has its CatchHandler @ 00b332eb */
  local_254 = CGameUI::scaledY(*(CGameUI **)(this + 0x80),DAT_00fe651c);
  local_258 = 0;
  local_250 = 0;
  local_24c = uVar33;
                    /* try { // try from 00b2f22f to 00b2f233 has its CatchHandler @ 00b332f0 */
  CEGUI::Window::setSize(pUVar13);
  local_bf0 = 0x20;
  local_be8 = 0;
  local_bd8 = 0;
  local_be0 = 0;
  local_b50 = (uint *)0x0;
  local_bf8 = 0;
  local_bd0[0] = 0;
                    /* try { // try from 00b2f297 to 00b2f29b has its CatchHandler @ 00b3326c */
  CEGUI::String::grow((ulong)&local_bf8);
  puVar17 = local_bd0;
  if (0x20 < local_bf0) {
    puVar17 = local_b50;
  }
  pcVar29 = "False";
  do {
    bVar3 = *pcVar29;
    pcVar29 = pcVar29 + 1;
    *puVar17 = (uint)bVar3;
    puVar17 = puVar17 + 1;
  } while ((byte *)pcVar29 != (byte *)0xfe603f);
  local_bf8 = 5;
  puVar17 = local_bbc;
  if (0x20 < local_bf0) {
    puVar17 = local_b50 + 5;
  }
  *puVar17 = 0;
  local_b40 = 0x20;
  local_b38 = 0;
  local_b28 = 0;
  local_b30 = 0;
  local_aa0 = (uint *)0x0;
  local_b48 = 0;
  local_b20[0] = 0;
                    /* try { // try from 00b2f365 to 00b2f369 has its CatchHandler @ 00b332f5 */
  CEGUI::String::grow((ulong)&local_b48);
  puVar17 = local_b20;
  if (0x20 < local_b40) {
    puVar17 = local_aa0;
  }
  pcVar29 = "RiseOnClick";
  do {
    bVar3 = *pcVar29;
    pcVar29 = pcVar29 + 1;
    *puVar17 = (uint)bVar3;
    puVar17 = puVar17 + 1;
  } while ((byte *)pcVar29 != (byte *)0xfe6039);
  local_b48 = 0xb;
  puVar17 = local_af4;
  if (0x20 < local_b40) {
    puVar17 = local_aa0 + 0xb;
  }
  *puVar17 = 0;
                    /* try { // try from 00b2f3dc to 00b2f3e0 has its CatchHandler @ 00b33307 */
  CEGUI::PropertySet::setProperty((String *)pUVar13,(String *)&local_b48);
                    /* try { // try from 00b2f3e4 to 00b2f3e8 has its CatchHandler @ 00b332f5 */
  CEGUI::String::~String((String *)&local_b48);
                    /* try { // try from 00b2f3ec to 00b2f3f0 has its CatchHandler @ 00b3326c */
  CEGUI::String::~String((String *)&local_bf8);
  local_264 = 0;
  local_268 = 0;
  local_25c = 0;
  local_260 = 0;
                    /* try { // try from 00b2f428 to 00b2f42c has its CatchHandler @ 00b33316 */
  CEGUI::Window::setPosition(pUVar13);
                    /* try { // try from 00b2f430 to 00b2f43e has its CatchHandler @ 00b3326c */
  CEGUI::Window::moveToBack();
  CEGUI::Window::setZOrderingEnabled(SUB81(pUVar13,0));
  local_3b8 = &DAT_01423a38;
                    /* try { // try from 00b2f45c to 00b2f460 has its CatchHandler @ 00b3331b */
  std::string::string((string *)&local_3b0,(string *)&::EMPTY_STRING);
                    /* try { // try from 00b2f472 to 00b2f476 has its CatchHandler @ 00b33332 */
  std::wstring::wstring((wstring_conflict *)&local_3a8,(wstring_conflict *)&::EMPTY_WSTRING);
  local_3a0 = 4;
  local_39c = 3;
  local_398 = &DAT_01423a38;
  local_390 = 0;
                    /* try { // try from 00b2f4b9 to 00b2f4bd has its CatchHandler @ 00b3334a */
  std::wstring::wstring((wstring_conflict *)local_88,L"media/ui/enchantmenu.layout",local_39);
                    /* try { // try from 00b2f4be to 00b2f4e0 has its CatchHandler @ 00b33354 */
  this_00 = (CFileSystem *)CFileSystem::getSingleton();
  CFileSystem::getFileInfo
            (this_00,(wstring_conflict *)local_88,(CFileInfo *)&local_3b8,false,true,false);
  if ((allocator *)(local_88[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_88[0] + -8);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
    }
  }
  local_ca0 = 0x20;
  local_c98 = 0;
  local_c88 = 0;
  local_c90 = 0;
  local_c00 = (undefined4 *)0x0;
  local_ca8 = 0;
  local_c80[0] = 0;
  lVar10 = *(long *)(local_3b0 + -0x18);
                    /* try { // try from 00b2f567 to 00b2f56b has its CatchHandler @ 00b33392 */
  CEGUI::String::grow((ulong)&local_ca8);
  puVar18 = local_c80;
  if (0x20 < local_ca0) {
    puVar18 = local_c00;
  }
  puVar18[lVar10] = 0;
  if (lVar10 != 0) {
    lVar27 = lVar10;
    do {
      lVar27 = lVar27 + -1;
      puVar18 = local_c80;
      if (0x20 < local_ca0) {
        puVar18 = local_c00;
      }
      puVar18[lVar27] = (uint)*(byte *)(local_3b0 + lVar27);
    } while (lVar27 != 0);
  }
  local_ca8 = lVar10;
                    /* try { // try from 00b2f5e4 to 00b2f5e8 has its CatchHandler @ 00b3339f */
  uVar9 = CEGUI::WindowManager::loadWindowLayout
                    (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,
                     SUB81((String *)&local_ca8,0));
  *(undefined8 *)(this + 0x28) = uVar9;
                    /* try { // try from 00b2f5f0 to 00b2f6b6 has its CatchHandler @ 00b33392 */
  CEGUI::String::~String((String *)&local_ca8);
  CGameUI::convertToScreenScale(*(CGameUI **)(this + 0x80),*(Window **)(this + 0x28),false);
  CGameUI::mapToFunctions(*(CGameUI **)(this + 0x80),*(Window **)(this + 0x28));
  mapEventHandlers(this,*(Window **)(this + 0x28));
  CEGUI::Window::addChildWindow(*(Window **)(this + 0x20));
  *(undefined1 *)(*(long *)(this + 0x28) + 0x3e2) = 1;
  CEGUI::Window::moveToFront();
  CEGUI::Window::setZOrderingEnabled(SUB81(*(undefined8 *)(this + 0x28),0));
  local_d50 = 0x20;
  local_d48 = 0;
  local_d38 = 0;
  local_d40 = 0;
  local_cb0 = (uint *)0x0;
  local_d58 = 0;
  local_d30[0] = 0;
  CEGUI::String::grow((ulong)&local_d58);
  puVar17 = local_d30;
  if (0x20 < local_d50) {
    puVar17 = local_cb0;
  }
  pbVar14 = (byte *)0xff197a;
  do {
    bVar3 = *pbVar14;
    pbVar14 = pbVar14 + 1;
    *puVar17 = (uint)bVar3;
    puVar17 = puVar17 + 1;
  } while (pbVar14 != (byte *)0xff197f);
  local_d58 = 5;
  puVar17 = local_d1c;
  if (0x20 < local_d50) {
    puVar17 = local_cb0 + 5;
  }
  *puVar17 = 0;
                    /* try { // try from 00b2f721 to 00b2f725 has its CatchHandler @ 00b333b1 */
  uVar9 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x28));
  *(undefined8 *)(this + 0x40) = uVar9;
                    /* try { // try from 00b2f72d to 00b2f796 has its CatchHandler @ 00b33392 */
  CEGUI::String::~String((String *)&local_d58);
  local_f60 = 0x20;
  local_f58 = 0;
  local_f48 = 0;
  local_f50 = 0;
  local_ec0 = (undefined4 *)0x0;
  local_f68 = 0;
  local_f40[0] = 0;
  CEGUI::String::grow((ulong)&local_f68);
  local_f68 = 0;
  puVar18 = local_f40;
  if (0x20 < local_f60) {
    puVar18 = local_ec0;
  }
  *puVar18 = 0;
                    /* try { // try from 00b2f7d5 to 00b2f7d9 has its CatchHandler @ 00b333b6 */
  std::string::string((string *)local_98,"gui_",&local_3a);
                    /* try { // try from 00b2f7ea to 00b2f7ee has its CatchHandler @ 00b333c5 */
  STRINGS::uniqueName((STRINGS *)local_a8,(string *)local_98);
  local_eb0 = 0x20;
  local_ea8 = 0;
  local_e98 = 0;
  local_ea0 = 0;
  local_e10 = (undefined4 *)0x0;
  local_eb8 = 0;
  local_e90[0] = 0;
  lVar10 = *(long *)(local_a8[0] + -0x18);
                    /* try { // try from 00b2f85c to 00b2f860 has its CatchHandler @ 00b332cf */
  CEGUI::String::grow((ulong)&local_eb8);
  puVar18 = local_e90;
  if (0x20 < local_eb0) {
    puVar18 = local_e10;
  }
  puVar18[lVar10] = 0;
  if (lVar10 != 0) {
    lVar27 = lVar10;
    do {
      lVar27 = lVar27 + -1;
      puVar18 = local_e90;
      if (0x20 < local_eb0) {
        puVar18 = local_e10;
      }
      puVar18[lVar27] = (uint)*(byte *)(local_a8[0] + lVar27);
    } while (lVar27 != 0);
  }
  pcVar28 = (char *)0x0;
  local_e00 = 0x20;
  local_df8 = 0;
  local_de8 = 0;
  pcVar29 = "GuiLook/StaticImage";
  local_df0 = 0;
  local_d60 = (uint *)0x0;
  local_e08 = 0;
  local_de0[0] = 0;
  pcVar11 = "GuiLook/StaticImage";
  cVar2 = s_GuiLook_StaticImage_00fd0bff[0];
  while (pcVar29 = pcVar29 + 1, cVar2 != '\0') {
    pcVar28 = pcVar29 + -0xfd0bff;
    cVar2 = *pcVar29;
  }
  local_eb8 = lVar10;
  if (pcVar28 == CEGUI::String::npos) {
                    /* try { // try from 00b32d2d to 00b32d31 has its CatchHandler @ 00b336ee */
    std::string::string((string *)local_1a8,"Length for utf8 encoded string can not be \'npos\'",
                        local_49);
    plVar21 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00b32d45 to 00b32d49 has its CatchHandler @ 00b336a8 */
    std::length_error::length_error(plVar21,(string *)local_1a8);
    if ((allocator *)(local_1a8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_1a8[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_1a8[0] + -0x18));
      }
    }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00b32d70 to 00b32d74 has its CatchHandler @ 00b331e7 */
    __cxa_throw(plVar21,&std::length_error::typeinfo,std::length_error::~length_error);
  }
  lVar10 = 0;
  pcVar29 = pcVar28;
  pbVar14 = (byte *)"GuiLook/StaticImage";
  while (pcVar29 != (char *)0x0) {
    bVar3 = *pbVar14;
    pcVar12 = pcVar29 + -1;
    pbVar24 = pbVar14 + 1;
    if ((char)bVar3 < '\0') {
      if (bVar3 < 0xe0) {
        pcVar12 = pcVar29 + -2;
        pbVar24 = pbVar14 + 2;
      }
      else if (bVar3 < 0xf0) {
        pcVar12 = pcVar29 + -3;
        pbVar24 = pbVar14 + 3;
      }
      else {
        pcVar12 = pcVar29 + -3;
        pbVar24 = pbVar14 + 4;
      }
    }
    lVar10 = lVar10 + 1;
    pcVar29 = pcVar12;
    pbVar14 = pbVar24;
  }
                    /* try { // try from 00b2fa6e to 00b2fa72 has its CatchHandler @ 00b331e7 */
  CEGUI::String::grow((ulong)&local_e08);
  puVar17 = local_de0;
  if (0x20 < local_e00) {
    puVar17 = local_d60;
  }
  if (pcVar28 == (char *)0x0) {
    pcVar29 = "GuiLook/StaticImage";
    if (s_GuiLook_StaticImage_00fd0bff[0] != '\0') {
      do {
        pcVar29 = pcVar29 + 1;
        pcVar28 = pcVar29 + -0xfd0bff;
      } while (*pcVar29 != '\0');
      bVar30 = pcVar28 != (char *)0x0 && local_e00 != 0;
      goto LAB_00b2fa9c;
    }
  }
  else {
    bVar30 = local_e00 != 0;
LAB_00b2fa9c:
    if (bVar30) {
      pcVar29 = (char *)0x0;
      uVar8 = 0;
      uVar22 = local_e00;
      do {
        bVar3 = pcVar29[0xfd0bff];
        uVar23 = (uint)bVar3;
        uVar7 = uVar8 + 1;
        if ((char)bVar3 < '\0') {
          uVar23 = (uint)bVar3;
          if (0xdf < bVar3) {
            if (bVar3 < 0xf0) {
              uVar25 = (ulong)uVar7;
              uVar7 = uVar8 + 3;
              uVar23 = (byte)"GuiLook/StaticImage"[uVar8 + 2] & 0x3f | (uVar23 & 0xf) << 0xc |
                       ((byte)"GuiLook/StaticImage"[uVar25] & 0x3f) << 6;
            }
            else {
              uVar25 = (ulong)uVar7;
              uVar7 = uVar8 + 4;
              uVar23 = ((byte)"GuiLook/StaticImage"[uVar25] & 0x3f) << 0xc |
                       (byte)"GuiLook/StaticImage"[uVar8 + 3] & 0x3f | (uVar23 & 7) << 0x12 |
                       ((byte)"GuiLook/StaticImage"[uVar8 + 2] & 0x3f) << 6;
            }
            goto LAB_00b2fab3;
          }
          uVar8 = uVar8 + 2;
          *puVar17 = (byte)"GuiLook/StaticImage"[uVar7] & 0x3f | (uVar23 & 0x1f) << 6;
        }
        else {
LAB_00b2fab3:
          *puVar17 = uVar23;
          uVar8 = uVar7;
        }
        pcVar29 = (char *)(ulong)uVar8;
        if ((pcVar28 <= pcVar29) || (uVar22 = uVar22 - 1, uVar22 == 0)) break;
        puVar17 = puVar17 + 1;
      } while( true );
    }
  }
  puVar17 = local_de0;
  if (0x20 < local_e00) {
    puVar17 = local_d60;
  }
  puVar17[lVar10] = 0;
  local_e08 = lVar10;
                    /* try { // try from 00b2fb47 to 00b2fb4b has its CatchHandler @ 00b3321b */
  uVar9 = CEGUI::WindowManager::createWindow
                    (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,(String *)&local_e08,
                     (String *)&local_eb8);
  *(undefined8 *)(this + 0x100) = uVar9;
                    /* try { // try from 00b2fb56 to 00b2fb5a has its CatchHandler @ 00b331e7 */
  CEGUI::String::~String((String *)&local_e08);
                    /* try { // try from 00b2fb5e to 00b2fb62 has its CatchHandler @ 00b332cf */
  CEGUI::String::~String((String *)&local_eb8);
  if ((allocator *)(local_a8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_a8[0] + -8);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
    }
  }
  if ((allocator *)(local_98[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_98[0] + -8);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
    }
  }
                    /* try { // try from 00b2fb99 to 00b2fc36 has its CatchHandler @ 00b33392 */
  CEGUI::String::~String((String *)&local_f68);
  CEGUI::EventSet::setMutedState((bool)((char)*(undefined8 *)(this + 0x100) + '8'));
  *(undefined1 *)(*(long *)(this + 0x100) + 0x3e2) = 1;
  *(undefined1 *)(*(long *)(this + 0x100) + 0x213) = 0;
  local_1010 = 0x20;
  local_1008 = 0;
  local_ff8 = 0;
  local_1000 = 0;
  local_f70 = (uint *)0x0;
  local_1018 = 0;
  local_ff0[0] = 0;
  CEGUI::String::grow((ulong)&local_1018);
  puVar17 = local_ff0;
  if (0x20 < local_1010) {
    puVar17 = local_f70;
  }
  pbVar14 = (byte *)0xfe60e6;
  do {
    bVar3 = *pbVar14;
    pbVar14 = pbVar14 + 1;
    *puVar17 = (uint)bVar3;
    puVar17 = puVar17 + 1;
  } while (pbVar14 != (byte *)0xfe60ee);
  local_1018 = 8;
  puVar17 = local_fd0;
  if (0x20 < local_1010) {
    puVar17 = local_f70 + 8;
  }
  *puVar17 = 0;
                    /* try { // try from 00b2fca5 to 00b2fcbc has its CatchHandler @ 00b331c6 */
  CEGUI::Imageset::getImage(*(String **)(this + 0xf8));
  CEGUI::PropertyHelper::imageToString(local_10c8);
  local_1170 = 0x20;
  local_1168 = 0;
  local_1158 = 0;
  local_1160 = 0;
  local_10d0 = (uint *)0x0;
  local_1178 = 0;
  local_1150[0] = 0;
                    /* try { // try from 00b2fd20 to 00b2fd24 has its CatchHandler @ 00b331d8 */
  CEGUI::String::grow((ulong)&local_1178);
  puVar17 = local_1150;
  if (0x20 < local_1170) {
    puVar17 = local_10d0;
  }
  pbVar14 = (byte *)0xfd0c0d;
  do {
    bVar3 = *pbVar14;
    pbVar14 = pbVar14 + 1;
    *puVar17 = (uint)bVar3;
    puVar17 = puVar17 + 1;
  } while (pbVar14 != (byte *)0xfd0c12);
  local_1178 = 5;
  puVar17 = local_113c;
  if (0x20 < local_1170) {
    puVar17 = local_10d0 + 5;
  }
  *puVar17 = 0;
                    /* try { // try from 00b2fd97 to 00b2fd9b has its CatchHandler @ 00b3324b */
  CEGUI::PropertySet::setProperty(*(String **)(this + 0x100),(String *)&local_1178);
                    /* try { // try from 00b2fd9f to 00b2fda3 has its CatchHandler @ 00b331d8 */
  CEGUI::String::~String((String *)&local_1178);
                    /* try { // try from 00b2fda7 to 00b2fdab has its CatchHandler @ 00b331c6 */
  CEGUI::String::~String((String *)local_10c8);
                    /* try { // try from 00b2fdaf to 00b2fe2f has its CatchHandler @ 00b33392 */
  CEGUI::String::~String((String *)&local_1018);
  *(undefined4 *)(this + 0xc0) = 0xe;
  *(undefined4 *)(this + 0xc4) = 0;
  local_1220 = 0x20;
  local_1218 = 0;
  local_1208 = 0;
  local_1210 = 0;
  local_1180 = (uint *)0x0;
  local_1228 = 0;
  local_1200[0] = 0;
  CEGUI::String::grow((ulong)&local_1228);
  puVar17 = local_1200;
  if (0x20 < local_1220) {
    puVar17 = local_1180;
  }
  pcVar29 = "Dialog";
  do {
    bVar3 = *pcVar29;
    pcVar29 = pcVar29 + 1;
    *puVar17 = (uint)bVar3;
    puVar17 = puVar17 + 1;
  } while ((byte *)pcVar29 != (byte *)0xfe605f);
  local_1228 = 6;
  puVar17 = local_11e8;
  if (0x20 < local_1220) {
    puVar17 = local_1180 + 6;
  }
  *puVar17 = 0;
                    /* try { // try from 00b2fe99 to 00b2fe9d has its CatchHandler @ 00b3325a */
  uVar9 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x28));
  *(undefined8 *)(this + 0x48) = uVar9;
                    /* try { // try from 00b2fea5 to 00b2ff11 has its CatchHandler @ 00b33392 */
  CEGUI::String::~String((String *)&local_1228);
  local_12d0 = 0x20;
  local_12c8 = 0;
  local_12b8 = 0;
  local_12c0 = 0;
  local_1230 = (uint *)0x0;
  local_12d8 = 0;
  local_12b0[0] = 0;
  CEGUI::String::grow((ulong)&local_12d8);
  puVar17 = local_12b0;
  if (0x20 < local_12d0) {
    puVar17 = local_1230;
  }
  pcVar29 = "Accept";
  do {
    bVar3 = *pcVar29;
    pcVar29 = pcVar29 + 1;
    *puVar17 = (uint)bVar3;
    puVar17 = puVar17 + 1;
  } while ((byte *)pcVar29 != (byte *)0xfe6058);
  local_12d8 = 6;
  puVar17 = local_1298;
  if (0x20 < local_12d0) {
    puVar17 = local_1230 + 6;
  }
  *puVar17 = 0;
                    /* try { // try from 00b2ff79 to 00b2ff7d has its CatchHandler @ 00b333fa */
  uVar9 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x28));
  *(undefined8 *)(this + 0x50) = uVar9;
                    /* try { // try from 00b2ff85 to 00b2fff1 has its CatchHandler @ 00b33392 */
  CEGUI::String::~String((String *)&local_12d8);
  local_1380 = 0x20;
  local_1378 = 0;
  local_1368 = 0;
  local_1370 = 0;
  local_12e0 = (uint *)0x0;
  local_1388 = 0;
  local_1360[0] = 0;
  CEGUI::String::grow((ulong)&local_1388);
  puVar17 = local_1360;
  if (0x20 < local_1380) {
    puVar17 = local_12e0;
  }
  pcVar29 = "ItemSlot";
  do {
    bVar3 = *pcVar29;
    pcVar29 = pcVar29 + 1;
    *puVar17 = (uint)bVar3;
    puVar17 = puVar17 + 1;
  } while ((byte *)pcVar29 != (byte *)0xfe609a);
  local_1388 = 8;
  puVar17 = local_1340;
  if (0x20 < local_1380) {
    puVar17 = local_12e0 + 8;
  }
  *puVar17 = 0;
                    /* try { // try from 00b30059 to 00b3005d has its CatchHandler @ 00b33405 */
  lVar27 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x28));
                    /* try { // try from 00b30064 to 00b300af has its CatchHandler @ 00b33392 */
  CEGUI::String::~String((String *)&local_1388);
  CEGUI::Window::moveToFront();
  *(undefined1 *)(lVar27 + 0x213) = 0;
  CEGUI::Window::setWantsMultiClickEvents(SUB81(lVar27,0));
  *(CEnchantMenu **)(lVar27 + 0x1d8) = this + 0xc4;
  CEGUI::Window::setAlwaysOnTop(SUB81(lVar27,0));
  pcVar4 = *(code **)(*(long *)(lVar27 + 0x38) + 0x10);
  local_b8[0] = operator_new(0x20);
  lVar10 = lVar27 + 0x38;
  *local_b8[0] = &PTR__MemberFunctionSlot_00fef410;
  local_b8[0][2] = 0;
  local_b8[0][1] = handle_ItemClick;
  local_b8[0][3] = this;
                    /* try { // try from 00b300f2 to 00b30127 has its CatchHandler @ 00b33276 */
  (*pcVar4)(&local_278,lVar10,CEGUI::Window::EventMouseButtonDown,(SubscriberSlot *)local_b8);
  if ((local_278 != (BoundSlot *)0x0) &&
     (iVar5 = *local_270, *local_270 = iVar5 + -1, iVar5 + -1 == 0)) {
    if (local_278 != (BoundSlot *)0x0) {
      CEGUI::BoundSlot::~BoundSlot(local_278);
      operator_delete(local_278);
    }
    operator_delete(local_270);
    local_278 = (BoundSlot *)0x0;
    local_270 = (int *)0x0;
  }
                    /* try { // try from 00b30158 to 00b3016e has its CatchHandler @ 00b33392 */
  CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_b8);
  pcVar4 = *(code **)(*(long *)(lVar27 + 0x38) + 0x10);
  local_c8[0] = operator_new(0x20);
  *local_c8[0] = &PTR__MemberFunctionSlot_00fef410;
  local_c8[0][2] = 0;
  local_c8[0][1] = handle_MouseOver;
  local_c8[0][3] = this;
                    /* try { // try from 00b301ad to 00b301e2 has its CatchHandler @ 00b33458 */
  (*pcVar4)(&local_288,lVar10,CEGUI::Window::EventMouseEnters,(SubscriberSlot *)local_c8);
  if ((local_288 != (BoundSlot *)0x0) &&
     (iVar5 = *local_280, *local_280 = iVar5 + -1, iVar5 + -1 == 0)) {
    if (local_288 != (BoundSlot *)0x0) {
      CEGUI::BoundSlot::~BoundSlot(local_288);
      operator_delete(local_288);
    }
    operator_delete(local_280);
    local_288 = (BoundSlot *)0x0;
    local_280 = (int *)0x0;
  }
                    /* try { // try from 00b30213 to 00b30229 has its CatchHandler @ 00b33392 */
  CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_c8);
  pcVar4 = *(code **)(*(long *)(lVar27 + 0x38) + 0x10);
  local_d8[0] = operator_new(0x20);
  *local_d8[0] = &PTR__MemberFunctionSlot_00fef410;
  local_d8[0][2] = 0;
  local_d8[0][1] = handle_MouseOver;
  local_d8[0][3] = this;
                    /* try { // try from 00b30268 to 00b3029d has its CatchHandler @ 00b33465 */
  (*pcVar4)(&local_298,lVar10,CEGUI::Window::EventMouseMove,(SubscriberSlot *)local_d8);
  if ((local_298 != (BoundSlot *)0x0) &&
     (iVar5 = *local_290, *local_290 = iVar5 + -1, iVar5 + -1 == 0)) {
    if (local_298 != (BoundSlot *)0x0) {
      CEGUI::BoundSlot::~BoundSlot(local_298);
      operator_delete(local_298);
    }
    operator_delete(local_290);
    local_298 = (BoundSlot *)0x0;
    local_290 = (int *)0x0;
  }
                    /* try { // try from 00b302ce to 00b302e4 has its CatchHandler @ 00b33392 */
  CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_d8);
  pcVar4 = *(code **)(*(long *)(lVar27 + 0x38) + 0x10);
  local_e8[0] = operator_new(0x20);
  *local_e8[0] = &PTR__MemberFunctionSlot_00fef410;
  local_e8[0][2] = 0;
  local_e8[0][1] = handle_MouseOut;
  local_e8[0][3] = this;
                    /* try { // try from 00b30323 to 00b30358 has its CatchHandler @ 00b33453 */
  (*pcVar4)(&local_2a8,lVar10,CEGUI::Window::EventMouseLeaves,(SubscriberSlot *)local_e8);
  if ((local_2a8 != (BoundSlot *)0x0) &&
     (iVar5 = *local_2a0, *local_2a0 = iVar5 + -1, iVar5 + -1 == 0)) {
    if (local_2a8 != (BoundSlot *)0x0) {
      CEGUI::BoundSlot::~BoundSlot(local_2a8);
      operator_delete(local_2a8);
    }
    operator_delete(local_2a0);
    local_2a8 = (BoundSlot *)0x0;
    local_2a0 = (int *)0x0;
  }
                    /* try { // try from 00b30389 to 00b30409 has its CatchHandler @ 00b33392 */
  CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_e8);
  CEGUI::Window::moveToFront();
  *(long *)(this + 0xd8) = lVar27;
  *(undefined8 *)(this + 0xe0) = 0;
  local_1590 = 0x20;
  local_1588 = 0;
  local_1578 = 0;
  local_1580 = 0;
  local_14f0 = (undefined4 *)0x0;
  local_1598 = 0;
  local_1570[0] = 0;
  CEGUI::String::grow((ulong)&local_1598);
  local_1598 = 0;
  puVar18 = local_14f0;
  if (local_1590 < 0x21) {
    puVar18 = local_1570;
  }
  *puVar18 = 0;
                    /* try { // try from 00b3044c to 00b30450 has its CatchHandler @ 00b33415 */
  std::string::string((string *)local_f8,"gui_",&local_3b);
                    /* try { // try from 00b30461 to 00b30465 has its CatchHandler @ 00b33288 */
  STRINGS::uniqueName((STRINGS *)local_108,(string *)local_f8);
  local_14e0 = 0x20;
  local_14d8 = 0;
  local_14c8 = 0;
  local_14d0 = 0;
  local_1440 = (undefined4 *)0x0;
  local_14e8 = 0;
  local_14c0[0] = 0;
  lVar10 = *(long *)(local_108[0] + -0x18);
                    /* try { // try from 00b304d3 to 00b304d7 has its CatchHandler @ 00b332ac */
  CEGUI::String::grow((ulong)&local_14e8);
  puVar18 = local_14c0;
  if (0x20 < local_14e0) {
    puVar18 = local_1440;
  }
  puVar18[lVar10] = 0;
  if (lVar10 != 0) {
    lVar27 = lVar10;
    do {
      lVar27 = lVar27 + -1;
      puVar18 = local_14c0;
      if (0x20 < local_14e0) {
        puVar18 = local_1440;
      }
      puVar18[lVar27] = (uint)*(byte *)(local_108[0] + lVar27);
    } while (lVar27 != 0);
  }
  pcVar28 = (char *)0x0;
  pcVar12 = "GuiLook/StaticText";
  local_1430 = 0x20;
  local_1428 = 0;
  pcVar29 = "GuiLook/StaticText";
  local_1418 = 0;
  local_1420 = 0;
  local_1390 = (uint *)0x0;
  local_1438 = 0;
  local_1410[0] = 0;
  cVar2 = s_GuiLook_StaticText_00fe4872[0];
  while (pcVar29 = pcVar29 + 1, cVar2 != '\0') {
    pcVar28 = pcVar29 + -0xfe4872;
    cVar2 = *pcVar29;
  }
  local_14e8 = lVar10;
  if (pcVar28 == CEGUI::String::npos) {
                    /* try { // try from 00b32d8d to 00b32d91 has its CatchHandler @ 00b3366e */
    std::string::string((string *)local_1b8,"Length for utf8 encoded string can not be \'npos\'",
                        local_4d);
    plVar21 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00b32da5 to 00b32da9 has its CatchHandler @ 00b33635 */
    std::length_error::length_error(plVar21,(string *)local_1b8);
    if ((allocator *)(local_1b8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_1b8[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_1b8[0] + -0x18));
      }
    }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00b32dd1 to 00b32dd5 has its CatchHandler @ 00b332c0 */
    __cxa_throw(plVar21,&std::length_error::typeinfo,std::length_error::~length_error);
  }
  lVar10 = 0;
  pcVar29 = pcVar28;
  pbVar14 = (byte *)"GuiLook/StaticText";
  while (pcVar29 != (char *)0x0) {
    bVar3 = *pbVar14;
    pcVar15 = pcVar29 + -1;
    pbVar24 = pbVar14 + 1;
    if ((char)bVar3 < '\0') {
      if (bVar3 < 0xe0) {
        pcVar15 = pcVar29 + -2;
        pbVar24 = pbVar14 + 2;
      }
      else if (bVar3 < 0xf0) {
        pcVar15 = pcVar29 + -3;
        pbVar24 = pbVar14 + 3;
      }
      else {
        pcVar15 = pcVar29 + -3;
        pbVar24 = pbVar14 + 4;
      }
    }
    lVar10 = lVar10 + 1;
    pcVar29 = pcVar15;
    pbVar14 = pbVar24;
  }
                    /* try { // try from 00b3071b to 00b3071f has its CatchHandler @ 00b332c0 */
  CEGUI::String::grow((ulong)&local_1438);
  if (local_1430 < 0x21) {
    puVar17 = local_1410;
    if (pcVar28 != (char *)0x0) goto LAB_00b30747;
LAB_00b31261:
    if (s_GuiLook_StaticText_00fe4872[0] != '\0') {
      do {
        pcVar12 = pcVar12 + 1;
        pcVar28 = pcVar12 + -0xfe4872;
      } while (*pcVar12 != '\0');
      bVar30 = pcVar28 != (char *)0x0 && local_1430 != 0;
      goto LAB_00b3074d;
    }
  }
  else {
    puVar17 = local_1390;
    if (pcVar28 == (char *)0x0) goto LAB_00b31261;
LAB_00b30747:
    bVar30 = local_1430 != 0;
LAB_00b3074d:
    if (bVar30) {
      pcVar29 = (char *)0x0;
      uVar8 = 0;
      uVar22 = local_1430;
      do {
        bVar3 = pcVar29[0xfe4872];
        uVar23 = (uint)bVar3;
        uVar7 = uVar8 + 1;
        if ((char)bVar3 < '\0') {
          uVar23 = (uint)bVar3;
          if (0xdf < bVar3) {
            if (bVar3 < 0xf0) {
              uVar25 = (ulong)uVar7;
              uVar7 = uVar8 + 3;
              uVar23 = (byte)"GuiLook/StaticText"[uVar8 + 2] & 0x3f | (uVar23 & 0xf) << 0xc |
                       ((byte)"GuiLook/StaticText"[uVar25] & 0x3f) << 6;
            }
            else {
              uVar25 = (ulong)uVar7;
              uVar7 = uVar8 + 4;
              uVar23 = ((byte)"GuiLook/StaticText"[uVar25] & 0x3f) << 0xc |
                       (byte)"GuiLook/StaticText"[uVar8 + 3] & 0x3f | (uVar23 & 7) << 0x12 |
                       ((byte)"GuiLook/StaticText"[uVar8 + 2] & 0x3f) << 6;
            }
            goto LAB_00b30763;
          }
          uVar8 = uVar8 + 2;
          *puVar17 = (byte)"GuiLook/StaticText"[uVar7] & 0x3f | (uVar23 & 0x1f) << 6;
        }
        else {
LAB_00b30763:
          *puVar17 = uVar23;
          uVar8 = uVar7;
        }
        pcVar29 = (char *)(ulong)uVar8;
        if ((pcVar28 <= pcVar29) || (uVar22 = uVar22 - 1, uVar22 == 0)) break;
        puVar17 = puVar17 + 1;
      } while( true );
    }
  }
  puVar17 = local_1390;
  if (local_1430 < 0x21) {
    puVar17 = local_1410;
  }
  puVar17[lVar10] = 0;
  local_1438 = lVar10;
                    /* try { // try from 00b30805 to 00b30809 has its CatchHandler @ 00b33530 */
  uVar9 = CEGUI::WindowManager::createWindow
                    (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,(String *)&local_1438,
                     (String *)&local_14e8);
  *(undefined8 *)(this + 0xe0) = uVar9;
                    /* try { // try from 00b30819 to 00b3081d has its CatchHandler @ 00b332c0 */
  CEGUI::String::~String((String *)&local_1438);
                    /* try { // try from 00b30821 to 00b30825 has its CatchHandler @ 00b332ac */
  CEGUI::String::~String((String *)&local_14e8);
  if ((allocator *)(local_108[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_108[0] + -8);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_108[0] + -0x18));
    }
  }
  if ((allocator *)(local_f8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_f8[0] + -8);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
    }
  }
                    /* try { // try from 00b30862 to 00b308ce has its CatchHandler @ 00b33392 */
  CEGUI::String::~String((String *)&local_1598);
  local_1640 = 0x20;
  local_1638 = 0;
  local_1628 = 0;
  local_1630 = 0;
  local_15a0 = (uint *)0x0;
  local_1648 = 0;
  local_1620[0] = 0;
  CEGUI::String::grow((ulong)&local_1648);
  puVar17 = local_1620;
  if (0x20 < local_1640) {
    puVar17 = local_15a0;
  }
  pcVar29 = "Serif";
  do {
    bVar3 = *pcVar29;
    pcVar29 = pcVar29 + 1;
    *puVar17 = (uint)bVar3;
    puVar17 = puVar17 + 1;
  } while ((byte *)pcVar29 != (byte *)0xfe4949);
  local_1648 = 5;
  puVar17 = local_160c;
  if (0x20 < local_1640) {
    puVar17 = local_15a0 + 5;
  }
  *puVar17 = 0;
                    /* try { // try from 00b3093c to 00b30940 has its CatchHandler @ 00b334c5 */
  CEGUI::Window::setFont(*(String **)(this + 0xe0));
                    /* try { // try from 00b30944 to 00b3095b has its CatchHandler @ 00b33392 */
  CEGUI::String::~String((String *)&local_1648);
  CEGUI::Window::getSize();
                    /* try { // try from 00b30966 to 00b3096a has its CatchHandler @ 00b334b5 */
  CEGUI::Window::setSize(*(UVector2 **)(this + 0xe0));
                    /* try { // try from 00b3096e to 00b30972 has its CatchHandler @ 00b33392 */
  puVar16 = (undefined8 *)CEGUI::Window::getPosition();
  local_2c8 = *puVar16;
  local_2c0 = puVar16[1];
  local_17a0 = 0x20;
  local_1798 = 0;
  local_1788 = 0;
  local_1790 = 0;
  local_1700 = (uint *)0x0;
  local_17a8 = 0;
  local_1780[0] = 0;
                    /* try { // try from 00b309ed to 00b309f1 has its CatchHandler @ 00b334ab */
  CEGUI::String::grow((ulong)&local_17a8);
  puVar17 = local_1780;
  if (0x20 < local_17a0) {
    puVar17 = local_1700;
  }
  pcVar29 = "RightAligned";
  do {
    bVar3 = *pcVar29;
    pcVar29 = pcVar29 + 1;
    *puVar17 = (uint)bVar3;
    puVar17 = puVar17 + 1;
  } while ((byte *)pcVar29 != (byte *)0xfe602d);
  local_17a8 = 0xc;
  puVar17 = local_1750;
  if (0x20 < local_17a0) {
    puVar17 = local_1700 + 0xc;
  }
  *puVar17 = 0;
  local_16f0 = 0x20;
  local_16e8 = 0;
  local_16d8 = 0;
  local_16e0 = 0;
  local_1650 = (uint *)0x0;
  local_16f8 = 0;
  local_16d0[0] = 0;
                    /* try { // try from 00b30ab6 to 00b30aba has its CatchHandler @ 00b334a6 */
  CEGUI::String::grow((ulong)&local_16f8);
  puVar17 = local_16d0;
  if (0x20 < local_16f0) {
    puVar17 = local_1650;
  }
  pcVar29 = "HorzTextFormatting";
  do {
    bVar3 = *pcVar29;
    pcVar29 = pcVar29 + 1;
    *puVar17 = (uint)bVar3;
    puVar17 = puVar17 + 1;
  } while ((byte *)pcVar29 != (byte *)0xfe48cf);
  local_16f8 = 0x12;
  puVar17 = local_1688;
  if (0x20 < local_16f0) {
    puVar17 = local_1650 + 0x12;
  }
  *puVar17 = 0;
                    /* try { // try from 00b30b2f to 00b30b33 has its CatchHandler @ 00b33494 */
  CEGUI::PropertySet::setProperty(*(String **)(this + 0xe0),(String *)&local_16f8);
                    /* try { // try from 00b30b37 to 00b30b3b has its CatchHandler @ 00b334a6 */
  CEGUI::String::~String((String *)&local_16f8);
                    /* try { // try from 00b30b3f to 00b30bab has its CatchHandler @ 00b334ab */
  CEGUI::String::~String((String *)&local_17a8);
  local_1900 = 0x20;
  local_18f8 = 0;
  local_18e8 = 0;
  local_18f0 = 0;
  local_1860 = (uint *)0x0;
  local_1908 = 0;
  local_18e0[0] = 0;
  CEGUI::String::grow((ulong)&local_1908);
  puVar17 = local_18e0;
  if (0x20 < local_1900) {
    puVar17 = local_1860;
  }
  pcVar29 = "BottomAligned";
  do {
    bVar3 = *pcVar29;
    pcVar29 = pcVar29 + 1;
    *puVar17 = (uint)bVar3;
    puVar17 = puVar17 + 1;
  } while ((byte *)pcVar29 != (byte *)0xfe6020);
  local_1908 = 0xd;
  puVar17 = local_18ac;
  if (0x20 < local_1900) {
    puVar17 = local_1860 + 0xd;
  }
  *puVar17 = 0;
  local_1850 = 0x20;
  local_1848 = 0;
  local_1838 = 0;
  local_1840 = 0;
  local_17b0 = (uint *)0x0;
  local_1858 = 0;
  local_1830[0] = 0;
                    /* try { // try from 00b30c76 to 00b30c7a has its CatchHandler @ 00b33562 */
  CEGUI::String::grow((ulong)&local_1858);
  puVar17 = local_1830;
  if (0x20 < local_1850) {
    puVar17 = local_17b0;
  }
  pcVar29 = "VertFormatting";
  do {
    bVar3 = *pcVar29;
    pcVar29 = pcVar29 + 1;
    *puVar17 = (uint)bVar3;
    puVar17 = puVar17 + 1;
  } while ((byte *)pcVar29 != (byte *)0xfe48ae);
  local_1858 = 0xe;
  puVar17 = local_17f8;
  if (0x20 < local_1850) {
    puVar17 = local_17b0 + 0xe;
  }
  *puVar17 = 0;
                    /* try { // try from 00b30cef to 00b30cf3 has its CatchHandler @ 00b3355d */
  CEGUI::PropertySet::setProperty(*(String **)(this + 0xe0),(String *)&local_1858);
                    /* try { // try from 00b30cf7 to 00b30cfb has its CatchHandler @ 00b33562 */
  CEGUI::String::~String((String *)&local_1858);
                    /* try { // try from 00b30cff to 00b30db2 has its CatchHandler @ 00b334ab */
  CEGUI::String::~String((String *)&local_1908);
  *(undefined1 *)(*(long *)(this + 0xe0) + 0x3e2) = 1;
  CEGUI::Window::setPosition(*(UVector2 **)(this + 0xe0));
  CEGUI::Window::addChildWindow(*(Window **)(*(long *)(this + 0xd8) + 0xb0));
  local_19b0 = 0x20;
  local_19a8 = 0;
  local_1998 = 0;
  local_19a0 = 0;
  local_1910 = (undefined4 *)0x0;
  local_19b8 = 0;
  local_1990[0] = 0;
  if (CEGUI::String::npos == (char *)0x0) {
                    /* try { // try from 00b32dee to 00b32df2 has its CatchHandler @ 00b33ad4 */
    std::string::string((string *)local_1c8,"Length for utf8 encoded string can not be \'npos\'",
                        local_51);
    plVar21 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00b32e06 to 00b32e0a has its CatchHandler @ 00b33aba */
    std::length_error::length_error(plVar21,(string *)local_1c8);
    if ((allocator *)(local_1c8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_1c8[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_1c8[0] + -0x18));
      }
    }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00b32e32 to 00b32e36 has its CatchHandler @ 00b334ab */
    __cxa_throw(plVar21,&std::length_error::typeinfo,std::length_error::~length_error);
  }
  CEGUI::String::grow((ulong)&local_19b8);
  local_19b8 = 0;
  puVar18 = local_1990;
  if (0x20 < local_19b0) {
    puVar18 = local_1910;
  }
  *puVar18 = 0;
                    /* try { // try from 00b30de6 to 00b30dea has its CatchHandler @ 00b33575 */
  CEGUI::Window::setText(*(String **)(this + 0xe0));
                    /* try { // try from 00b30dee to 00b30e26 has its CatchHandler @ 00b334ab */
  CEGUI::String::~String((String *)&local_19b8);
  CEGUI::colour::colour(local_358,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc);
  CEGUI::PropertyHelper::colourToString(local_1a68);
  local_1b10 = 0x20;
  local_1b08 = 0;
  local_1af8 = 0;
  local_1b00 = 0;
  local_1a70 = (uint *)0x0;
  local_1b18 = 0;
  local_1af0[0] = 0;
                    /* try { // try from 00b30e8a to 00b30e8e has its CatchHandler @ 00b33567 */
  CEGUI::String::grow((ulong)&local_1b18);
  puVar17 = local_1af0;
  if (0x20 < local_1b10) {
    puVar17 = local_1a70;
  }
  pbVar14 = (byte *)0xfe4654;
  do {
    bVar3 = *pbVar14;
    pbVar14 = pbVar14 + 1;
    *puVar17 = (uint)bVar3;
    puVar17 = puVar17 + 1;
  } while (pbVar14 != (byte *)0xfe465e);
  local_1b18 = 10;
  puVar17 = local_1ac8;
  if (0x20 < local_1b10) {
    puVar17 = local_1a70 + 10;
  }
  *puVar17 = 0;
                    /* try { // try from 00b30eff to 00b30f03 has its CatchHandler @ 00b33a89 */
  CEGUI::PropertySet::setProperty(*(String **)(this + 0xe0),(String *)&local_1b18);
                    /* try { // try from 00b30f07 to 00b30f0b has its CatchHandler @ 00b33567 */
  CEGUI::String::~String((String *)&local_1b18);
                    /* try { // try from 00b30f0f to 00b30f86 has its CatchHandler @ 00b334ab */
  CEGUI::String::~String(local_1a68);
  CEGUI::Window::setAlwaysOnTop(SUB81(*(undefined8 *)(this + 0xe0),0));
  local_1d20 = 0x20;
  local_1d18 = 0;
  local_1d08 = 0;
  local_1d10 = 0;
  local_1c80 = (undefined4 *)0x0;
  local_1d28 = 0;
  local_1d00[0] = 0;
  CEGUI::String::grow((ulong)&local_1d28);
  local_1d28 = 0;
  puVar18 = local_1c80;
  if (local_1d20 < 0x21) {
    puVar18 = local_1d00;
  }
  *puVar18 = 0;
  pcVar12 = (char *)0x0;
  pcVar29 = "EnchanterSockets";
  local_1c70 = 0x20;
  local_1c68 = 0;
  local_1c58 = 0;
  local_1c60 = 0;
  pcVar28 = "EnchanterSockets";
  local_1bd0 = (uint *)0x0;
  local_1c78 = 0;
  local_1c50[0] = 0;
  cVar2 = s_EnchanterSockets_00fee5c0[0];
  while (pcVar28 = pcVar28 + 1, cVar2 != '\0') {
    pcVar12 = pcVar28 + -0xfee5c0;
    cVar2 = *pcVar28;
  }
  if (pcVar12 == CEGUI::String::npos) {
                    /* try { // try from 00b32e4f to 00b32e53 has its CatchHandler @ 00b33b48 */
    std::string::string((string *)local_1d8,"Length for utf8 encoded string can not be \'npos\'",
                        local_53);
    plVar21 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00b32e67 to 00b32e6b has its CatchHandler @ 00b33b2e */
    std::length_error::length_error(plVar21,(string *)local_1d8);
    if ((allocator *)(local_1d8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_1d8[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_1d8[0] + -0x18));
      }
    }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00b32e93 to 00b32e97 has its CatchHandler @ 00b33af8 */
    __cxa_throw(plVar21,&std::length_error::typeinfo,std::length_error::~length_error);
  }
  lVar10 = 0;
  pcVar28 = pcVar12;
  pbVar14 = (byte *)"EnchanterSockets";
  while (pcVar28 != (char *)0x0) {
    bVar3 = *pbVar14;
    pcVar15 = pcVar28 + -1;
    pbVar24 = pbVar14 + 1;
    if ((char)bVar3 < '\0') {
      if (bVar3 < 0xe0) {
        pcVar15 = pcVar28 + -2;
        pbVar24 = pbVar14 + 2;
      }
      else if (bVar3 < 0xf0) {
        pcVar15 = pcVar28 + -3;
        pbVar24 = pbVar14 + 3;
      }
      else {
        pcVar15 = pcVar28 + -3;
        pbVar24 = pbVar14 + 4;
      }
    }
    lVar10 = lVar10 + 1;
    pcVar28 = pcVar15;
    pbVar14 = pbVar24;
  }
                    /* try { // try from 00b3130e to 00b31312 has its CatchHandler @ 00b33af8 */
  CEGUI::String::grow((ulong)&local_1c78);
  puVar17 = local_1c50;
  if (0x20 < local_1c70) {
    puVar17 = local_1bd0;
  }
  if (pcVar12 == (char *)0x0) {
    if (s_EnchanterSockets_00fee5c0[0] != '\0') {
      do {
        pcVar29 = pcVar29 + 1;
        pcVar12 = pcVar29 + -0xfee5c0;
      } while (*pcVar29 != '\0');
      bVar30 = pcVar12 != (char *)0x0 && local_1c70 != 0;
      goto LAB_00b3133c;
    }
  }
  else {
    bVar30 = local_1c70 != 0;
LAB_00b3133c:
    if (bVar30) {
      pcVar29 = (char *)0x0;
      uVar8 = 0;
      uVar22 = local_1c70;
      do {
        bVar3 = pcVar29[0xfee5c0];
        uVar23 = (uint)bVar3;
        uVar7 = uVar8 + 1;
        if ((char)bVar3 < '\0') {
          uVar23 = (uint)bVar3;
          if (0xdf < bVar3) {
            if (bVar3 < 0xf0) {
              uVar25 = (ulong)uVar7;
              uVar7 = uVar8 + 3;
              uVar23 = (byte)"EnchanterSockets"[uVar8 + 2] & 0x3f | (uVar23 & 0xf) << 0xc |
                       ((byte)"EnchanterSockets"[uVar25] & 0x3f) << 6;
            }
            else {
              uVar25 = (ulong)uVar7;
              uVar7 = uVar8 + 4;
              uVar23 = ((byte)"EnchanterSockets"[uVar25] & 0x3f) << 0xc |
                       (byte)"EnchanterSockets"[uVar8 + 3] & 0x3f | (uVar23 & 7) << 0x12 |
                       ((byte)"EnchanterSockets"[uVar8 + 2] & 0x3f) << 6;
            }
            goto LAB_00b31353;
          }
          uVar8 = uVar8 + 2;
          *puVar17 = (byte)"EnchanterSockets"[uVar7] & 0x3f | (uVar23 & 0x1f) << 6;
        }
        else {
LAB_00b31353:
          *puVar17 = uVar23;
          uVar8 = uVar7;
        }
        pcVar29 = (char *)(ulong)uVar8;
        if ((pcVar12 <= pcVar29) || (uVar22 = uVar22 - 1, uVar22 == 0)) break;
        puVar17 = puVar17 + 1;
      } while( true );
    }
  }
  puVar17 = local_1c50;
  if (0x20 < local_1c70) {
    puVar17 = local_1bd0;
  }
  puVar17[lVar10] = 0;
  pcVar28 = (char *)0x0;
  local_1bc0 = 0x20;
  local_1bb8 = 0;
  pcVar29 = "DefaultWindow";
  local_1ba8 = 0;
  local_1bb0 = 0;
  local_1b20 = (uint *)0x0;
  local_1bc8 = 0;
  local_1ba0[0] = 0;
  cVar2 = s_DefaultWindow_00fe499d[0];
  while (pcVar29 = pcVar29 + 1, cVar2 != '\0') {
    pcVar28 = pcVar29 + -0xfe499d;
    cVar2 = *pcVar29;
  }
  local_1c78 = lVar10;
  if (pcVar28 == CEGUI::String::npos) {
                    /* try { // try from 00b32eb0 to 00b32eb4 has its CatchHandler @ 00b33bee */
    std::string::string((string *)local_1e8,"Length for utf8 encoded string can not be \'npos\'",
                        local_55);
    plVar21 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00b32ec8 to 00b32ecc has its CatchHandler @ 00b33bd4 */
    std::length_error::length_error(plVar21,(string *)local_1e8);
    if ((allocator *)(local_1e8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_1e8[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_1e8[0] + -0x18));
      }
    }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00b32ef4 to 00b32ef8 has its CatchHandler @ 00b330df */
    __cxa_throw(plVar21,&std::length_error::typeinfo,std::length_error::~length_error);
  }
  lVar10 = 0;
  pcVar29 = pcVar28;
  pbVar14 = (byte *)"DefaultWindow";
  while (pcVar29 != (char *)0x0) {
    bVar3 = *pbVar14;
    pcVar12 = pcVar29 + -1;
    pbVar24 = pbVar14 + 1;
    if ((char)bVar3 < '\0') {
      if (bVar3 < 0xe0) {
        pcVar12 = pcVar29 + -2;
        pbVar24 = pbVar14 + 2;
      }
      else if (bVar3 < 0xf0) {
        pcVar12 = pcVar29 + -3;
        pbVar24 = pbVar14 + 3;
      }
      else {
        pcVar12 = pcVar29 + -3;
        pbVar24 = pbVar14 + 4;
      }
    }
    lVar10 = lVar10 + 1;
    pcVar29 = pcVar12;
    pbVar14 = pbVar24;
  }
                    /* try { // try from 00b3155e to 00b31562 has its CatchHandler @ 00b330df */
  CEGUI::String::grow((ulong)&local_1bc8);
  puVar17 = local_1ba0;
  if (0x20 < local_1bc0) {
    puVar17 = local_1b20;
  }
  if (pcVar28 == (char *)0x0) {
    pcVar29 = "DefaultWindow";
    if (s_DefaultWindow_00fe499d[0] != '\0') {
      do {
        pcVar29 = pcVar29 + 1;
        pcVar28 = pcVar29 + -0xfe499d;
      } while (*pcVar29 != '\0');
      bVar30 = pcVar28 != (char *)0x0 && local_1bc0 != 0;
      goto LAB_00b3158c;
    }
  }
  else {
    bVar30 = local_1bc0 != 0;
LAB_00b3158c:
    if (bVar30) {
      pcVar29 = (char *)0x0;
      uVar8 = 0;
      uVar22 = local_1bc0;
      do {
        bVar3 = pcVar29[0xfe499d];
        uVar23 = (uint)bVar3;
        uVar7 = uVar8 + 1;
        if ((char)bVar3 < '\0') {
          uVar23 = (uint)bVar3;
          if (0xdf < bVar3) {
            if (bVar3 < 0xf0) {
              uVar25 = (ulong)uVar7;
              uVar7 = uVar8 + 3;
              uVar23 = (byte)"DefaultWindow"[uVar8 + 2] & 0x3f | (uVar23 & 0xf) << 0xc |
                       ((byte)"DefaultWindow"[uVar25] & 0x3f) << 6;
            }
            else {
              uVar25 = (ulong)uVar7;
              uVar7 = uVar8 + 4;
              uVar23 = ((byte)"DefaultWindow"[uVar25] & 0x3f) << 0xc |
                       (byte)"DefaultWindow"[uVar8 + 3] & 0x3f | (uVar23 & 7) << 0x12 |
                       ((byte)"DefaultWindow"[uVar8 + 2] & 0x3f) << 6;
            }
            goto LAB_00b315a3;
          }
          uVar8 = uVar8 + 2;
          *puVar17 = (byte)"DefaultWindow"[uVar7] & 0x3f | (uVar23 & 0x1f) << 6;
        }
        else {
LAB_00b315a3:
          *puVar17 = uVar23;
          uVar8 = uVar7;
        }
        pcVar29 = (char *)(ulong)uVar8;
        if ((pcVar28 <= pcVar29) || (uVar22 = uVar22 - 1, uVar22 == 0)) break;
        puVar17 = puVar17 + 1;
      } while( true );
    }
  }
  puVar17 = local_1ba0;
  if (0x20 < local_1bc0) {
    puVar17 = local_1b20;
  }
  puVar17[lVar10] = 0;
  local_1bc8 = lVar10;
                    /* try { // try from 00b3163c to 00b31640 has its CatchHandler @ 00b3301c */
  uVar9 = CEGUI::WindowManager::createWindow
                    (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,(String *)&local_1bc8,
                     (String *)&local_1c78);
  *(undefined8 *)(this + 0x30) = uVar9;
                    /* try { // try from 00b31648 to 00b3164c has its CatchHandler @ 00b330df */
  CEGUI::String::~String((String *)&local_1bc8);
                    /* try { // try from 00b31650 to 00b31654 has its CatchHandler @ 00b33af8 */
  CEGUI::String::~String((String *)&local_1c78);
                    /* try { // try from 00b3165d to 00b31682 has its CatchHandler @ 00b334ab */
  CEGUI::String::~String((String *)&local_1d28);
  CEGUI::Window::addChildWindow(*(Window **)(this + 0x28));
  CEGUI::Window::getSize();
                    /* try { // try from 00b3168a to 00b3168e has its CatchHandler @ 00b33b85 */
  CEGUI::Window::setSize(*(UVector2 **)(this + 0x30));
  local_1e80 = 0x20;
  local_1e78 = 0;
  local_1e68 = 0;
  local_1e70 = 0;
  local_1de0 = (uint *)0x0;
  local_1e88 = 0;
  local_1e60[0] = 0;
                    /* try { // try from 00b316f2 to 00b316f6 has its CatchHandler @ 00b334ab */
  CEGUI::String::grow((ulong)&local_1e88);
  puVar17 = local_1e60;
  if (0x20 < local_1e80) {
    puVar17 = local_1de0;
  }
  pcVar29 = "False";
  do {
    bVar3 = *pcVar29;
    pcVar29 = pcVar29 + 1;
    *puVar17 = (uint)bVar3;
    puVar17 = puVar17 + 1;
  } while ((byte *)pcVar29 != (byte *)0xfe603f);
  local_1e88 = 5;
  puVar17 = local_1e4c;
  if (0x20 < local_1e80) {
    puVar17 = local_1de0 + 5;
  }
  *puVar17 = 0;
  local_1dd0 = 0x20;
  local_1dc8 = 0;
  local_1db8 = 0;
  local_1dc0 = 0;
  local_1d30 = (uint *)0x0;
  local_1dd8 = 0;
  local_1db0[0] = 0;
                    /* try { // try from 00b317c0 to 00b317c4 has its CatchHandler @ 00b33b75 */
  CEGUI::String::grow((ulong)&local_1dd8);
  puVar17 = local_1db0;
  if (0x20 < local_1dd0) {
    puVar17 = local_1d30;
  }
  pcVar29 = "RiseOnClick";
  do {
    bVar3 = *pcVar29;
    pcVar29 = pcVar29 + 1;
    *puVar17 = (uint)bVar3;
    puVar17 = puVar17 + 1;
  } while ((byte *)pcVar29 != (byte *)0xfe6039);
  local_1dd8 = 0xb;
  puVar17 = local_1d84;
  if (0x20 < local_1dd0) {
    puVar17 = local_1d30 + 0xb;
  }
  *puVar17 = 0;
                    /* try { // try from 00b31836 to 00b3183a has its CatchHandler @ 00b33b6e */
  CEGUI::PropertySet::setProperty(*(String **)(this + 0x30),(String *)&local_1dd8);
                    /* try { // try from 00b3183e to 00b31842 has its CatchHandler @ 00b33b75 */
  CEGUI::String::~String((String *)&local_1dd8);
                    /* try { // try from 00b31846 to 00b3184a has its CatchHandler @ 00b334ab */
  CEGUI::String::~String((String *)&local_1e88);
  local_2e4 = 0;
  local_2e8 = 0;
  local_2dc = 0;
  local_2e0 = 0;
                    /* try { // try from 00b31883 to 00b31887 has its CatchHandler @ 00b33b69 */
  CEGUI::Window::setPosition(*(UVector2 **)(this + 0x30));
  *(undefined1 *)(*(long *)(this + 0x30) + 0x3e2) = 1;
                    /* try { // try from 00b31897 to 00b318fd has its CatchHandler @ 00b334ab */
  CEGUI::Window::moveToFront();
  local_2090 = 0x20;
  local_2088 = 0;
  local_2078 = 0;
  local_2080 = 0;
  local_1ff0 = (undefined4 *)0x0;
  local_2098 = 0;
  local_2070[0] = 0;
  CEGUI::String::grow((ulong)&local_2098);
  local_2098 = 0;
  puVar18 = local_1ff0;
  if (local_2090 < 0x21) {
    puVar18 = local_2070;
  }
  *puVar18 = 0;
  pcVar12 = (char *)0x0;
  pcVar29 = "EnchanterSocketsO";
  local_1fe0 = 0x20;
  local_1fd8 = 0;
  local_1fc8 = 0;
  local_1fd0 = 0;
  pcVar28 = "EnchanterSocketsO";
  local_1f40 = (uint *)0x0;
  local_1fe8 = 0;
  local_1fc0[0] = 0;
  cVar2 = s_EnchanterSocketsO_00fee5ae[0];
  while (pcVar28 = pcVar28 + 1, cVar2 != '\0') {
    pcVar12 = pcVar28 + -0xfee5ae;
    cVar2 = *pcVar28;
  }
  if (pcVar12 == CEGUI::String::npos) {
                    /* try { // try from 00b32f11 to 00b32f15 has its CatchHandler @ 00b335e7 */
    std::string::string((string *)local_1f8,"Length for utf8 encoded string can not be \'npos\'",
                        local_57);
    plVar21 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00b32f29 to 00b32f2d has its CatchHandler @ 00b335d0 */
    std::length_error::length_error(plVar21,(string *)local_1f8);
    if ((allocator *)(local_1f8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_1f8[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_1f8[0] + -0x18));
      }
    }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00b32f55 to 00b32f59 has its CatchHandler @ 00b33b95 */
    __cxa_throw(plVar21,&std::length_error::typeinfo,std::length_error::~length_error);
  }
  lVar10 = 0;
  pcVar28 = pcVar12;
  pbVar14 = (byte *)"EnchanterSocketsO";
  while (pcVar28 != (char *)0x0) {
    bVar3 = *pbVar14;
    pcVar15 = pcVar28 + -1;
    pbVar24 = pbVar14 + 1;
    if ((char)bVar3 < '\0') {
      if (bVar3 < 0xe0) {
        pcVar15 = pcVar28 + -2;
        pbVar24 = pbVar14 + 2;
      }
      else if (bVar3 < 0xf0) {
        pcVar15 = pcVar28 + -3;
        pbVar24 = pbVar14 + 3;
      }
      else {
        pcVar15 = pcVar28 + -3;
        pbVar24 = pbVar14 + 4;
      }
    }
    lVar10 = lVar10 + 1;
    pcVar28 = pcVar15;
    pbVar14 = pbVar24;
  }
                    /* try { // try from 00b31a6e to 00b31a72 has its CatchHandler @ 00b33b95 */
  CEGUI::String::grow((ulong)&local_1fe8);
  puVar17 = local_1fc0;
  if (0x20 < local_1fe0) {
    puVar17 = local_1f40;
  }
  if (pcVar12 == (char *)0x0) {
    if (s_EnchanterSocketsO_00fee5ae[0] != '\0') {
      do {
        pcVar29 = pcVar29 + 1;
        pcVar12 = pcVar29 + -0xfee5ae;
      } while (*pcVar29 != '\0');
      bVar30 = pcVar12 != (char *)0x0 && local_1fe0 != 0;
      goto LAB_00b31a9c;
    }
  }
  else {
    bVar30 = local_1fe0 != 0;
LAB_00b31a9c:
    if (bVar30) {
      pcVar29 = (char *)0x0;
      uVar8 = 0;
      uVar22 = local_1fe0;
      do {
        bVar3 = pcVar29[0xfee5ae];
        uVar23 = (uint)bVar3;
        uVar7 = uVar8 + 1;
        if ((char)bVar3 < '\0') {
          uVar23 = (uint)bVar3;
          if (0xdf < bVar3) {
            if (bVar3 < 0xf0) {
              uVar25 = (ulong)uVar7;
              uVar7 = uVar8 + 3;
              uVar23 = (byte)"EnchanterSocketsO"[uVar8 + 2] & 0x3f | (uVar23 & 0xf) << 0xc |
                       ((byte)"EnchanterSocketsO"[uVar25] & 0x3f) << 6;
            }
            else {
              uVar25 = (ulong)uVar7;
              uVar7 = uVar8 + 4;
              uVar23 = ((byte)"EnchanterSocketsO"[uVar25] & 0x3f) << 0xc |
                       (byte)"EnchanterSocketsO"[uVar8 + 3] & 0x3f | (uVar23 & 7) << 0x12 |
                       ((byte)"EnchanterSocketsO"[uVar8 + 2] & 0x3f) << 6;
            }
            goto LAB_00b31ab3;
          }
          uVar8 = uVar8 + 2;
          *puVar17 = (byte)"EnchanterSocketsO"[uVar7] & 0x3f | (uVar23 & 0x1f) << 6;
        }
        else {
LAB_00b31ab3:
          *puVar17 = uVar23;
          uVar8 = uVar7;
        }
        pcVar29 = (char *)(ulong)uVar8;
        if ((pcVar12 <= pcVar29) || (uVar22 = uVar22 - 1, uVar22 == 0)) break;
        puVar17 = puVar17 + 1;
      } while( true );
    }
  }
  puVar17 = local_1fc0;
  if (0x20 < local_1fe0) {
    puVar17 = local_1f40;
  }
  puVar17[lVar10] = 0;
  pcVar28 = (char *)0x0;
  local_1f30 = 0x20;
  local_1f28 = 0;
  pcVar29 = "DefaultWindow";
  local_1f18 = 0;
  local_1f20 = 0;
  local_1e90 = (uint *)0x0;
  local_1f38 = 0;
  local_1f10[0] = 0;
  cVar2 = s_DefaultWindow_00fe499d[0];
  while (pcVar29 = pcVar29 + 1, cVar2 != '\0') {
    pcVar28 = pcVar29 + -0xfe499d;
    cVar2 = *pcVar29;
  }
  local_1fe8 = lVar10;
  if (pcVar28 == CEGUI::String::npos) {
                    /* try { // try from 00b32f72 to 00b32f76 has its CatchHandler @ 00b33ccf */
    std::string::string((string *)local_208,"Length for utf8 encoded string can not be \'npos\'",
                        local_59);
    plVar21 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00b32f8a to 00b32f8e has its CatchHandler @ 00b33cb5 */
    std::length_error::length_error(plVar21,(string *)local_208);
    if ((allocator *)(local_208[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_208[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_208[0] + -0x18));
      }
    }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00b32fb6 to 00b32fba has its CatchHandler @ 00b33585 */
    __cxa_throw(plVar21,&std::length_error::typeinfo,std::length_error::~length_error);
  }
  lVar10 = 0;
  pcVar29 = pcVar28;
  pbVar14 = (byte *)"DefaultWindow";
  while (pcVar29 != (char *)0x0) {
    bVar3 = *pbVar14;
    pcVar12 = pcVar29 + -1;
    pbVar24 = pbVar14 + 1;
    if ((char)bVar3 < '\0') {
      if (bVar3 < 0xe0) {
        pcVar12 = pcVar29 + -2;
        pbVar24 = pbVar14 + 2;
      }
      else if (bVar3 < 0xf0) {
        pcVar12 = pcVar29 + -3;
        pbVar24 = pbVar14 + 3;
      }
      else {
        pcVar12 = pcVar29 + -3;
        pbVar24 = pbVar14 + 4;
      }
    }
    lVar10 = lVar10 + 1;
    pcVar29 = pcVar12;
    pbVar14 = pbVar24;
  }
                    /* try { // try from 00b31cce to 00b31cd2 has its CatchHandler @ 00b33585 */
  CEGUI::String::grow((ulong)&local_1f38);
  puVar17 = local_1f10;
  if (0x20 < local_1f30) {
    puVar17 = local_1e90;
  }
  if (pcVar28 == (char *)0x0) {
    if (s_DefaultWindow_00fe499d[0] != '\0') {
      do {
        pcVar26 = pcVar26 + 1;
        pcVar28 = pcVar26 + -0xfe499d;
      } while (*pcVar26 != '\0');
      bVar30 = pcVar28 != (char *)0x0 && local_1f30 != 0;
      goto LAB_00b31cfc;
    }
  }
  else {
    bVar30 = local_1f30 != 0;
LAB_00b31cfc:
    if (bVar30) {
      pcVar29 = (char *)0x0;
      uVar8 = 0;
      uVar22 = local_1f30;
      do {
        bVar3 = pcVar29[0xfe499d];
        uVar23 = (uint)bVar3;
        uVar7 = uVar8 + 1;
        if ((char)bVar3 < '\0') {
          uVar23 = (uint)bVar3;
          if (0xdf < bVar3) {
            if (bVar3 < 0xf0) {
              uVar25 = (ulong)uVar7;
              uVar7 = uVar8 + 3;
              uVar23 = (byte)"DefaultWindow"[uVar8 + 2] & 0x3f | (uVar23 & 0xf) << 0xc |
                       ((byte)"DefaultWindow"[uVar25] & 0x3f) << 6;
            }
            else {
              uVar25 = (ulong)uVar7;
              uVar7 = uVar8 + 4;
              uVar23 = ((byte)"DefaultWindow"[uVar25] & 0x3f) << 0xc |
                       (byte)"DefaultWindow"[uVar8 + 3] & 0x3f | (uVar23 & 7) << 0x12 |
                       ((byte)"DefaultWindow"[uVar8 + 2] & 0x3f) << 6;
            }
            goto LAB_00b31d13;
          }
          uVar8 = uVar8 + 2;
          *puVar17 = (byte)"DefaultWindow"[uVar7] & 0x3f | (uVar23 & 0x1f) << 6;
        }
        else {
LAB_00b31d13:
          *puVar17 = uVar23;
          uVar8 = uVar7;
        }
        pcVar29 = (char *)(ulong)uVar8;
        if ((pcVar28 <= pcVar29) || (uVar22 = uVar22 - 1, uVar22 == 0)) break;
        puVar17 = puVar17 + 1;
      } while( true );
    }
  }
  puVar17 = local_1f10;
  if (0x20 < local_1f30) {
    puVar17 = local_1e90;
  }
  puVar17[lVar10] = 0;
  local_1f38 = lVar10;
                    /* try { // try from 00b31dac to 00b31db0 has its CatchHandler @ 00b33c55 */
  uVar9 = CEGUI::WindowManager::createWindow
                    (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,(String *)&local_1f38,
                     (String *)&local_1fe8);
  *(undefined8 *)(this + 0x38) = uVar9;
                    /* try { // try from 00b31db8 to 00b31dbc has its CatchHandler @ 00b33585 */
  CEGUI::String::~String((String *)&local_1f38);
                    /* try { // try from 00b31dc0 to 00b31dc4 has its CatchHandler @ 00b33b95 */
  CEGUI::String::~String((String *)&local_1fe8);
                    /* try { // try from 00b31dcd to 00b31df2 has its CatchHandler @ 00b334ab */
  CEGUI::String::~String((String *)&local_2098);
  CEGUI::Window::addChildWindow(*(Window **)(this + 0x28));
  CEGUI::Window::getSize();
                    /* try { // try from 00b31dfa to 00b31dfe has its CatchHandler @ 00b33c45 */
  CEGUI::Window::setSize(*(UVector2 **)(this + 0x38));
  local_21f0 = 0x20;
  local_21e8 = 0;
  local_21d8 = 0;
  local_21e0 = 0;
  local_2150 = (uint *)0x0;
  local_21f8 = 0;
  local_21d0[0] = 0;
                    /* try { // try from 00b31e62 to 00b31e66 has its CatchHandler @ 00b334ab */
  CEGUI::String::grow((ulong)&local_21f8);
  puVar17 = local_21d0;
  if (0x20 < local_21f0) {
    puVar17 = local_2150;
  }
  pcVar29 = "False";
  do {
    bVar3 = *pcVar29;
    pcVar29 = pcVar29 + 1;
    *puVar17 = (uint)bVar3;
    puVar17 = puVar17 + 1;
  } while ((byte *)pcVar29 != (byte *)0xfe603f);
  local_21f8 = 5;
  puVar17 = local_21bc;
  if (0x20 < local_21f0) {
    puVar17 = local_2150 + 5;
  }
  *puVar17 = 0;
  local_2140 = 0x20;
  local_2138 = 0;
  local_2128 = 0;
  local_2130 = 0;
  local_20a0 = (uint *)0x0;
  local_2148 = 0;
  local_2120[0] = 0;
                    /* try { // try from 00b31f30 to 00b31f34 has its CatchHandler @ 00b33c3e */
  CEGUI::String::grow((ulong)&local_2148);
  puVar17 = local_2120;
  if (0x20 < local_2140) {
    puVar17 = local_20a0;
  }
  pcVar29 = "RiseOnClick";
  do {
    bVar3 = *pcVar29;
    pcVar29 = pcVar29 + 1;
    *puVar17 = (uint)bVar3;
    puVar17 = puVar17 + 1;
  } while ((byte *)pcVar29 != (byte *)0xfe6039);
  local_2148 = 0xb;
  puVar17 = local_20f4;
  if (0x20 < local_2140) {
    puVar17 = local_20a0 + 0xb;
  }
  *puVar17 = 0;
                    /* try { // try from 00b31fa6 to 00b31faa has its CatchHandler @ 00b33c39 */
  CEGUI::PropertySet::setProperty(*(String **)(this + 0x38),(String *)&local_2148);
                    /* try { // try from 00b31fae to 00b31fb2 has its CatchHandler @ 00b33c3e */
  CEGUI::String::~String((String *)&local_2148);
                    /* try { // try from 00b31fb6 to 00b31fba has its CatchHandler @ 00b334ab */
  CEGUI::String::~String((String *)&local_21f8);
  local_304 = 0;
  local_308 = 0;
  local_2fc = 0;
  local_300 = 0;
                    /* try { // try from 00b31ff3 to 00b31ff7 has its CatchHandler @ 00b33c34 */
  CEGUI::Window::setPosition(*(UVector2 **)(this + 0x38));
  *(undefined1 *)(*(long *)(this + 0x38) + 0x3e2) = 1;
                    /* try { // try from 00b32007 to 00b3206d has its CatchHandler @ 00b334ab */
  CEGUI::Window::moveToFront();
  local_2400 = 0x20;
  local_23f8 = 0;
  local_23e8 = 0;
  local_23f0 = 0;
  local_2360 = (undefined4 *)0x0;
  local_2408 = 0;
  local_23e0[0] = 0;
  CEGUI::String::grow((ulong)&local_2408);
  local_2408 = 0;
  puVar18 = local_2360;
  if (local_2400 < 0x21) {
    puVar18 = local_23e0;
  }
  *puVar18 = 0;
                    /* try { // try from 00b320b0 to 00b320b4 has its CatchHandler @ 00b33c2a */
  std::string::string((string *)local_118,"gui_",&local_3c);
                    /* try { // try from 00b320c5 to 00b320c9 has its CatchHandler @ 00b33c20 */
  STRINGS::uniqueName((STRINGS *)local_128,(string *)local_118);
  local_2350 = 0x20;
  local_2348 = 0;
  local_2338 = 0;
  local_2340 = 0;
  local_22b0 = (undefined4 *)0x0;
  local_2358 = 0;
  local_2330[0] = 0;
  lVar10 = *(long *)(local_128[0] + -0x18);
                    /* try { // try from 00b32137 to 00b3213b has its CatchHandler @ 00b33c16 */
  CEGUI::String::grow((ulong)&local_2358);
  puVar18 = local_2330;
  if (0x20 < local_2350) {
    puVar18 = local_22b0;
  }
  puVar18[lVar10] = 0;
  if (lVar10 != 0) {
    lVar27 = lVar10;
    do {
      lVar27 = lVar27 + -1;
      puVar18 = local_2330;
      if (0x20 < local_2350) {
        puVar18 = local_22b0;
      }
      puVar18[lVar27] = (uint)*(byte *)(local_128[0] + lVar27);
    } while (lVar27 != 0);
  }
  pcVar26 = (char *)0x0;
  local_22a0 = 0x20;
  local_2298 = 0;
  local_2288 = 0;
  pcVar29 = "GuiLook/StaticImage";
  local_2290 = 0;
  local_2200 = (uint *)0x0;
  local_22a8 = 0;
  local_2280[0] = 0;
  cVar2 = s_GuiLook_StaticImage_00fd0bff[0];
  while (pcVar29 = pcVar29 + 1, cVar2 != '\0') {
    pcVar26 = pcVar29 + -0xfd0bff;
    cVar2 = *pcVar29;
  }
  local_2358 = lVar10;
  if (pcVar26 == CEGUI::String::npos) {
                    /* try { // try from 00b32fd3 to 00b32fd7 has its CatchHandler @ 00b3312f */
    std::string::string((string *)local_218,"Length for utf8 encoded string can not be \'npos\'",
                        local_5b);
    plVar21 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00b32feb to 00b32fef has its CatchHandler @ 00b33115 */
    std::length_error::length_error(plVar21,(string *)local_218);
    if ((allocator *)(local_218[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_218[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_218[0] + -0x18));
      }
    }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00b33017 to 00b3301b has its CatchHandler @ 00b33cb0 */
    __cxa_throw(plVar21,&std::length_error::typeinfo,std::length_error::~length_error);
  }
  lVar10 = 0;
  pcVar29 = pcVar26;
  pbVar14 = (byte *)"GuiLook/StaticImage";
  while (pcVar29 != (char *)0x0) {
    bVar3 = *pbVar14;
    pcVar28 = pcVar29 + -1;
    pbVar24 = pbVar14 + 1;
    if ((char)bVar3 < '\0') {
      if (bVar3 < 0xe0) {
        pcVar28 = pcVar29 + -2;
        pbVar24 = pbVar14 + 2;
      }
      else if (bVar3 < 0xf0) {
        pcVar28 = pcVar29 + -3;
        pbVar24 = pbVar14 + 3;
      }
      else {
        pcVar28 = pcVar29 + -3;
        pbVar24 = pbVar14 + 4;
      }
    }
    lVar10 = lVar10 + 1;
    pcVar29 = pcVar28;
    pbVar14 = pbVar24;
  }
                    /* try { // try from 00b3234e to 00b32352 has its CatchHandler @ 00b33cb0 */
  CEGUI::String::grow((ulong)&local_22a8);
  puVar17 = local_2280;
  if (0x20 < local_22a0) {
    puVar17 = local_2200;
  }
  if (pcVar26 == (char *)0x0) {
    if (s_GuiLook_StaticImage_00fd0bff[0] == '\0') goto LAB_00b323f0;
    do {
      pcVar11 = pcVar11 + 1;
      pcVar26 = pcVar11 + -0xfd0bff;
    } while (*pcVar11 != '\0');
    bVar30 = pcVar26 != (char *)0x0 && local_22a0 != 0;
  }
  else {
    bVar30 = local_22a0 != 0;
  }
  if (bVar30) {
    pcVar29 = (char *)0x0;
    uVar8 = 0;
    uVar22 = local_22a0;
    do {
      bVar3 = pcVar29[0xfd0bff];
      uVar23 = (uint)bVar3;
      uVar7 = uVar8 + 1;
      if ((char)bVar3 < '\0') {
        uVar23 = (uint)bVar3;
        if (0xdf < bVar3) {
          if (bVar3 < 0xf0) {
            uVar25 = (ulong)uVar7;
            uVar7 = uVar8 + 3;
            uVar23 = (byte)"GuiLook/StaticImage"[uVar8 + 2] & 0x3f | (uVar23 & 0xf) << 0xc |
                     ((byte)"GuiLook/StaticImage"[uVar25] & 0x3f) << 6;
          }
          else {
            uVar25 = (ulong)uVar7;
            uVar7 = uVar8 + 4;
            uVar23 = ((byte)"GuiLook/StaticImage"[uVar25] & 0x3f) << 0xc |
                     (byte)"GuiLook/StaticImage"[uVar8 + 3] & 0x3f | (uVar23 & 7) << 0x12 |
                     ((byte)"GuiLook/StaticImage"[uVar8 + 2] & 0x3f) << 6;
          }
          goto LAB_00b32393;
        }
        uVar8 = uVar8 + 2;
        *puVar17 = (byte)"GuiLook/StaticImage"[uVar7] & 0x3f | (uVar23 & 0x1f) << 6;
      }
      else {
LAB_00b32393:
        *puVar17 = uVar23;
        uVar8 = uVar7;
      }
      pcVar29 = (char *)(ulong)uVar8;
      if ((pcVar26 <= pcVar29) || (uVar22 = uVar22 - 1, uVar22 == 0)) break;
      puVar17 = puVar17 + 1;
    } while( true );
  }
LAB_00b323f0:
  puVar17 = local_2280;
  if (0x20 < local_22a0) {
    puVar17 = local_2200;
  }
  puVar17[lVar10] = 0;
  local_22a8 = lVar10;
                    /* try { // try from 00b3242c to 00b32430 has its CatchHandler @ 00b33093 */
  pUVar13 = (UVector2 *)
            CEGUI::WindowManager::createWindow
                      (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,(String *)&local_22a8,
                       (String *)&local_2358);
                    /* try { // try from 00b32437 to 00b3243b has its CatchHandler @ 00b33cb0 */
  CEGUI::String::~String((String *)&local_22a8);
                    /* try { // try from 00b3243f to 00b32443 has its CatchHandler @ 00b33c16 */
  CEGUI::String::~String((String *)&local_2358);
  if ((allocator *)(local_128[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_128[0] + -8);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_128[0] + -0x18));
    }
  }
  if ((allocator *)(local_118[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_118[0] + -8);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_118[0] + -0x18));
    }
  }
                    /* try { // try from 00b32480 to 00b324f8 has its CatchHandler @ 00b334ab */
  CEGUI::String::~String((String *)&local_2408);
  CEGUI::Window::addChildWindow(*(Window **)(*(long *)(this + 0xd8) + 0xb0));
  pUVar13[0x213] = (UVector2)0x0;
  bVar30 = SUB81(pUVar13,0);
  CEGUI::Window::setWantsMultiClickEvents(bVar30);
  pUVar13[0x3e2] = (UVector2)0x1;
  CEGUI::EventSet::setMutedState((bool)(bVar30 + '8'));
  CEGUI::Window::setZOrderingEnabled(bVar30);
  CEGUI::Window::getPosition();
  CEGUI::Window::setPosition(pUVar13);
  CEGUI::Window::getSize();
                    /* try { // try from 00b324ff to 00b32503 has its CatchHandler @ 00b33c7b */
  CEGUI::Window::setSize(pUVar13);
  *(UVector2 **)(this + 200) = pUVar13;
  local_2610 = 0x20;
  local_2608 = 0;
  local_25f8 = 0;
  local_2600 = 0;
  local_2570 = (undefined4 *)0x0;
  local_2618 = 0;
  local_25f0[0] = 0;
                    /* try { // try from 00b32556 to 00b3255a has its CatchHandler @ 00b334ab */
  CEGUI::String::grow((ulong)&local_2618);
  local_2618 = 0;
  puVar18 = local_25f0;
  if (0x20 < local_2610) {
    puVar18 = local_2570;
  }
  *puVar18 = 0;
                    /* try { // try from 00b32593 to 00b32597 has its CatchHandler @ 00b33c71 */
  std::string::string((string *)local_138,"gui_",&local_3d);
                    /* try { // try from 00b325a8 to 00b325ac has its CatchHandler @ 00b33c67 */
  STRINGS::uniqueName((STRINGS *)local_148,(string *)local_138);
  local_2560 = 0x20;
  local_2558 = 0;
  local_2548 = 0;
  local_2550 = 0;
  local_24c0 = (undefined4 *)0x0;
  local_2568 = 0;
  local_2540[0] = 0;
  lVar10 = *(long *)(local_148[0] + -0x18);
                    /* try { // try from 00b3261a to 00b3261e has its CatchHandler @ 00b33913 */
  CEGUI::String::grow((ulong)&local_2568);
  puVar18 = local_2540;
  if (0x20 < local_2560) {
    puVar18 = local_24c0;
  }
  puVar18[lVar10] = 0;
  if (lVar10 != 0) {
    lVar27 = lVar10;
    do {
      lVar27 = lVar27 + -1;
      puVar18 = local_2540;
      if (0x20 < local_2560) {
        puVar18 = local_24c0;
      }
      puVar18[lVar27] = (uint)*(byte *)(local_148[0] + lVar27);
    } while (lVar27 != 0);
  }
  local_2568 = lVar10;
                    /* try { // try from 00b3269d to 00b326a1 has its CatchHandler @ 00b3390c */
  CEGUI::String::String(local_24b8,(uchar *)"GuiLook/StaticImage");
                    /* try { // try from 00b326b2 to 00b326b6 has its CatchHandler @ 00b338c5 */
  pUVar13 = (UVector2 *)
            CEGUI::WindowManager::createWindow
                      (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,local_24b8,
                       (String *)&local_2568);
                    /* try { // try from 00b326bd to 00b326c1 has its CatchHandler @ 00b3390c */
  CEGUI::String::~String(local_24b8);
                    /* try { // try from 00b326c5 to 00b326c9 has its CatchHandler @ 00b33913 */
  CEGUI::String::~String((String *)&local_2568);
  if ((allocator *)(local_148[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_148[0] + -8);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_148[0] + -0x18));
    }
  }
  if ((allocator *)(local_138[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_138[0] + -8);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_138[0] + -0x18));
    }
  }
                    /* try { // try from 00b32701 to 00b3274e has its CatchHandler @ 00b334ab */
  CEGUI::String::~String((String *)&local_2618);
  CEGUI::Window::addChildWindow(*(Window **)(this + 0x38));
  pUVar13[0x213] = (UVector2)0x0;
  CEGUI::Window::setWantsMultiClickEvents(SUB81(pUVar13,0));
  pUVar13[0x3e2] = (UVector2)0x1;
  CEGUI::EventSet::setMutedState((bool)(SUB81(pUVar13,0) + '8'));
  pfVar19 = (float *)CEGUI::Window::getPosition();
  pfVar20 = (float *)CEGUI::Window::getPosition();
  local_31c = pfVar20[3] + pfVar19[3];
  local_320 = pfVar20[2] + pfVar19[2];
  local_328 = *pfVar20 + *pfVar19;
  local_324 = pfVar20[1] + pfVar19[1];
                    /* try { // try from 00b327ac to 00b327b0 has its CatchHandler @ 00b3391a */
  CEGUI::Window::setPosition(pUVar13);
                    /* try { // try from 00b327bf to 00b327c3 has its CatchHandler @ 00b334ab */
  CEGUI::Window::getSize();
                    /* try { // try from 00b327ca to 00b327ce has its CatchHandler @ 00b3394b */
  CEGUI::Window::setSize(pUVar13);
  *(UVector2 **)(this + 0xd0) = pUVar13;
                    /* try { // try from 00b327dd to 00b327e1 has its CatchHandler @ 00b334ab */
  CEGUI::Window::moveToFront();
  if ((allocator *)(local_398 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_398 + -8);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_398 + -0x18));
    }
  }
  if ((allocator *)(local_3a8 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_3a8 + -8);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_3a8 + -0x18));
    }
  }
  if ((allocator *)(local_3b0 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_3b0 + -8);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_3b0 + -0x18));
    }
  }
  if ((allocator *)(local_3b8 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_3b8 + -8);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_3b8 + -0x18));
    }
  }
  if (local_368 != (void *)0x0) {
    Ogre::NedAllocImpl::deallocBytes(local_368);
  }
  return;
}

/* address=00b33d30
   symbol=CEnchantMenu::CEnchantMenu */

/* WARNING: Removing unreachable block (ram,0x00b3421e) */
/* WARNING: Removing unreachable block (ram,0x00b34210) */
/* WARNING: Removing unreachable block (ram,0x00b341f4) */
/* WARNING: Removing unreachable block (ram,0x00b34191) */
/* WARNING: Removing unreachable block (ram,0x00b3422c) */
/* WARNING: Removing unreachable block (ram,0x00b34202) */
/* CEnchantMenu::CEnchantMenu(CGameUI&, CSettings&, Ogre::RenderWindow*, Ogre::SceneManager*,
   CEGUI::Window*, CResourceManager*) */

void __thiscall
CEnchantMenu::CEnchantMenu
          (CEnchantMenu *this,CGameUI *param_1,CSettings *param_2,RenderWindow *param_3,
          SceneManager *param_4,Window *param_5,CResourceManager *param_6)

{
  int *piVar1;
  int iVar2;
  CSoundBankDataInformation *this_00;
  CSoundManager *pCVar3;
  long lVar4;
  CSoundBank *this_01;
  long local_a8 [2];
  long local_98 [2];
  long local_88 [2];
  long local_78 [2];
  long local_68 [2];
  long local_58 [3];
  allocator local_3e;
  allocator local_3d;
  allocator local_3c;
  allocator local_3b;
  allocator local_3a;
  allocator local_39 [9];

  CRunicCore::CRunicCore((CRunicCore *)this);
  *(undefined ***)this = &PTR__CEnchantMenu_00fef2b0;
  *(undefined ***)(this + 0x10) = &PTR__CEnchantMenu_00fef360;
  *(Window **)(this + 0x18) = param_5;
  *(undefined8 *)(this + 0x58) = 0;
  *(undefined8 *)(this + 0x60) = 0;
  *(undefined8 *)(this + 0x68) = 0;
  this[0x70] = (CEnchantMenu)0x0;
  this[0x71] = (CEnchantMenu)0x1;
  this[0x72] = (CEnchantMenu)0x0;
  this[0x73] = (CEnchantMenu)0x0;
  *(CSettings **)(this + 0x78) = param_2;
  *(CGameUI **)(this + 0x80) = param_1;
  *(SceneManager **)(this + 0x88) = param_4;
  *(RenderWindow **)(this + 0x90) = param_3;
  *(undefined8 *)(this + 0xa0) = 0;
  *(CResourceManager **)(this + 0xa8) = param_6;
  *(undefined4 *)(this + 0xb0) = 0;
  *(undefined8 *)(this + 0xb8) = 0;
  *(undefined4 *)(this + 0xe8) = 0xffffffff;
  *(undefined4 *)(this + 0xec) = 0xffffffff;
  *(undefined8 *)(this + 0xf0) = 0;
  this[0x108] = (CEnchantMenu)0x0;
                    /* try { // try from 00b33e01 to 00b33e28 has its CatchHandler @ 00b341e6 */
  lVar4 = CMasterResourceManager::getSingleton();
  this_00 = *(CSoundBankDataInformation **)(lVar4 + 0x100);
  lVar4 = CMasterResourceManager::getSingleton();
  pCVar3 = *(CSoundManager **)(lVar4 + 0x98);
  this_01 = (CSoundBank *)Ogre::NedAllocImpl::allocBytes(0xd0,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00b33e34 to 00b33e38 has its CatchHandler @ 00b341b6 */
  CSoundBank::CSoundBank(this_01,pCVar3,false);
  *(CSoundBank **)(this + 0xb8) = this_01;
                    /* try { // try from 00b33e52 to 00b33e56 has its CatchHandler @ 00b341b4 */
  std::wstring::wstring((wstring_conflict *)local_58,L"STATSOPEN",local_39);
                    /* try { // try from 00b33e5d to 00b33e61 has its CatchHandler @ 00b341c7 */
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
                    /* try { // try from 00b33e8f to 00b33e93 has its CatchHandler @ 00b341e6 */
    CSoundBank::addSample(*(CSoundBank **)(this + 0xb8),0x16,*(longlong *)(lVar4 + 0x20));
  }
                    /* try { // try from 00b33ea6 to 00b33eaa has its CatchHandler @ 00b341a9 */
  std::wstring::wstring((wstring_conflict *)local_68,L"STATSCLOSE",&local_3a);
                    /* try { // try from 00b33eb1 to 00b33eb5 has its CatchHandler @ 00b3419c */
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
                    /* try { // try from 00b33edd to 00b33ee1 has its CatchHandler @ 00b341e6 */
    CSoundBank::addSample(*(CSoundBank **)(this + 0xb8),0x42,*(longlong *)(lVar4 + 0x20));
  }
                    /* try { // try from 00b33ef4 to 00b33ef8 has its CatchHandler @ 00b34176 */
  std::wstring::wstring((wstring_conflict *)local_78,L"ERROR",&local_3b);
                    /* try { // try from 00b33eff to 00b33f03 has its CatchHandler @ 00b341d6 */
  lVar4 = CSoundBankDataInformation::getSoundDataObject(this_00,(wstring_conflict *)local_78);
  if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_78[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
    }
  }
  if (lVar4 != 0) {
                    /* try { // try from 00b33f2b to 00b33f2f has its CatchHandler @ 00b341e6 */
    CSoundBank::addSample(*(CSoundBank **)(this + 0xb8),0x18,*(longlong *)(lVar4 + 0x20));
  }
                    /* try { // try from 00b33f42 to 00b33f46 has its CatchHandler @ 00b341d4 */
  std::wstring::wstring((wstring_conflict *)local_88,L"LOWMANA",&local_3c);
                    /* try { // try from 00b33f4d to 00b33f51 has its CatchHandler @ 00b341e2 */
  lVar4 = CSoundBankDataInformation::getSoundDataObject(this_00,(wstring_conflict *)local_88);
  if ((allocator *)(local_88[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_88[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
    }
  }
  if (lVar4 != 0) {
                    /* try { // try from 00b33f79 to 00b33f7d has its CatchHandler @ 00b341e6 */
    CSoundBank::addSample(*(CSoundBank **)(this + 0xb8),0x23,*(longlong *)(lVar4 + 0x20));
  }
                    /* try { // try from 00b33f90 to 00b33f94 has its CatchHandler @ 00b341b2 */
  std::wstring::wstring((wstring_conflict *)local_98,L"REVEAL",&local_3d);
                    /* try { // try from 00b33f9b to 00b33f9f has its CatchHandler @ 00b341ab */
  lVar4 = CSoundBankDataInformation::getSoundDataObject(this_00,(wstring_conflict *)local_98);
  if ((allocator *)(local_98[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_98[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
    }
  }
  if (lVar4 != 0) {
                    /* try { // try from 00b33fc7 to 00b33fcb has its CatchHandler @ 00b341e6 */
    CSoundBank::addSample(*(CSoundBank **)(this + 0xb8),0x24,*(longlong *)(lVar4 + 0x20));
  }
                    /* try { // try from 00b33fde to 00b33fe2 has its CatchHandler @ 00b341e4 */
  std::wstring::wstring((wstring_conflict *)local_a8,L"GOLDBUY",&local_3e);
                    /* try { // try from 00b33fe9 to 00b33fed has its CatchHandler @ 00b341f2 */
  lVar4 = CSoundBankDataInformation::getSoundDataObject(this_00,(wstring_conflict *)local_a8);
  if ((allocator *)(local_a8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_a8[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
    }
  }
  if (lVar4 != 0) {
                    /* try { // try from 00b34011 to 00b3401d has its CatchHandler @ 00b341e6 */
    CSoundBank::addSample(*(CSoundBank **)(this + 0xb8),0x17,*(longlong *)(lVar4 + 0x20));
  }
  createMenus(this);
  return;
}

/* address=00b34240
   symbol=CEnchantMenu::isRight */

/* CEnchantMenu::isRight() */

undefined8 CEnchantMenu::isRight(void)

{
  return 0;
}

/* address=00b34250
   symbol=CEnchantMenu::open */

/* CEnchantMenu::open() */

byte __thiscall CEnchantMenu::open(CEnchantMenu *this)

{
  byte bVar1;

  bVar1 = 1;
  if (this[0x70] == (CEnchantMenu)0x0) {
    bVar1 = (byte)this[0x71] ^ 1;
  }
  return bVar1;
}

/* address=00b34270
   symbol=CEnchantMenu::openPartial */

/* CEnchantMenu::openPartial() */

CEnchantMenu __thiscall CEnchantMenu::openPartial(CEnchantMenu *this)

{
  return this[0x70];
}

/* address=00b34280
   symbol=CEnchantMenu::screenEdge */

/* CEnchantMenu::screenEdge() */

undefined4 __thiscall CEnchantMenu::screenEdge(CEnchantMenu *this)

{
  return *(undefined4 *)(this + 0xb0);
}

/* address=00b34290
   symbol=CEnchantMenu::getOwner */

/* CEnchantMenu::getOwner() */

undefined8 __thiscall CEnchantMenu::getOwner(CEnchantMenu *this)

{
  return *(undefined8 *)(this + 0x58);
}

/* address=00b343a0
   symbol=CEnchantMenu::setOpen */

/* CEnchantMenu::setOpen(bool) */

void __thiscall CEnchantMenu::setOpen(CEnchantMenu *this,bool param_1)

{
  setOpen(this,param_1,0x15);
  return;
}

/* export-summary functions=42 failures=0 */
