/* Targeted Ghidra class export.
   namespace=CCombineMenu
   Treat pseudocode as navigation evidence. */


/* address=00acd2c0
   symbol=CCombineMenu::setOwner */

/* CCombineMenu::setOwner(CCharacter*) */

void __thiscall CCombineMenu::setOwner(CCombineMenu *this,CCharacter *param_1)

{
  *(CCharacter **)(this + 0x88) = param_1;
  return;
}

/* address=00acd2d0
   symbol=CCombineMenu::equipmentEquipped */

/* non-virtual thunk to CCombineMenu::equipmentEquipped(CEquipment*) */

void __thiscall CCombineMenu::equipmentEquipped(CCombineMenu *this,CEquipment *param_1)

{
  equipmentEquipped((CEquipment *)(this + -0x10));
  return;
}

/* address=00acd2e0
   symbol=CCombineMenu::equipmentEquipped */

/* CCombineMenu::equipmentEquipped(CEquipment*) */

void CCombineMenu::equipmentEquipped(CEquipment *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x00acd2e7. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)param_1 + 0x48))();
  return;
}

/* address=00acd2f0
   symbol=CCombineMenu::equipmentUnequipped */

/* non-virtual thunk to CCombineMenu::equipmentUnequipped(CEquipment*) */

void __thiscall CCombineMenu::equipmentUnequipped(CCombineMenu *this,CEquipment *param_1)

{
  equipmentUnequipped((CEquipment *)(this + -0x10));
  return;
}

/* address=00acd300
   symbol=CCombineMenu::equipmentUnequipped */

/* CCombineMenu::equipmentUnequipped(CEquipment*) */

void CCombineMenu::equipmentUnequipped(CEquipment *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x00acd307. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)param_1 + 0x48))();
  return;
}

/* address=00acd310
   symbol=CCombineMenu::inventoryDestroyed */

/* non-virtual thunk to CCombineMenu::inventoryDestroyed() */

void __thiscall CCombineMenu::inventoryDestroyed(CCombineMenu *this)

{
  inventoryDestroyed();
  return;
}

/* address=00acd320
   symbol=CCombineMenu::inventoryDestroyed */

/* CCombineMenu::inventoryDestroyed() */

void CCombineMenu::inventoryDestroyed(void)

{
  return;
}

/* address=00acd330
   symbol=CCombineMenu::handle_ItemClick */

/* CCombineMenu::handle_ItemClick(CEGUI::EventArgs const&) */

undefined8 __thiscall CCombineMenu::handle_ItemClick(CCombineMenu *this,EventArgs *param_1)

{
  int iVar1;

  if (*(long *)(param_1 + 0x10) != 0) {
    iVar1 = **(int **)(*(long *)(param_1 + 0x10) + 0x1d8);
    if (*(int *)(param_1 + 0x28) == 0) {
      *(undefined4 *)(this + 0x188) = *(undefined4 *)(this + (long)iVar1 * 4 + 0xe8);
      return 1;
    }
    if (*(int *)(param_1 + 0x28) == 1) {
      *(undefined4 *)(this + 0x18c) = *(undefined4 *)(this + (long)iVar1 * 4 + 0xe8);
      return 1;
    }
  }
  return 1;
}

/* address=00acd390
   symbol=CCombineMenu::handle_MouseThrough */

/* CCombineMenu::handle_MouseThrough(CEGUI::EventArgs const&) */

undefined8 CCombineMenu::handle_MouseThrough(EventArgs *param_1)

{
  param_1[0x1a8] = (EventArgs)0x0;
  return 1;
}

/* address=00acd3a0
   symbol=CCombineMenu::handle_onClick */

/* CCombineMenu::handle_onClick(CEGUI::EventArgs const&) */

undefined8 __thiscall CCombineMenu::handle_onClick(CCombineMenu *this,EventArgs *param_1)

{
  undefined8 uVar1;

  if ((*(int *)(param_1 + 0x28) == 0) && (*(long *)(param_1 + 0x10) != 0)) {
                    /* WARNING: Could not recover jumptable at 0x00acd3c3. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(*(long *)this + 0x98))
                      (this,**(undefined4 **)(*(long *)(param_1 + 0x10) + 0x1d8));
    return uVar1;
  }
  return 1;
}

/* address=00acd3d0
   symbol=CCombineMenu::handle_MouseOut */

/* CCombineMenu::handle_MouseOut(CEGUI::EventArgs const&) */

undefined8 __thiscall CCombineMenu::handle_MouseOut(CCombineMenu *this,EventArgs *param_1)

{
  char cVar1;
  long lVar2;

  if (((*(long *)(param_1 + 0x10) != 0) && (*(long *)(this + 0x90) != 0)) &&
     (lVar2 = CInventory::getEquipmentInSlot
                        (*(CInventory **)(*(long *)(this + 0x90) + 0x490),
                         *(uint *)(this + (long)**(int **)(*(long *)(param_1 + 0x10) + 0x1d8) * 4 +
                                          0xe8)), lVar2 == *(long *)(this + 400))) {
    *(undefined8 *)(this + 400) = 0;
    if ((*(CBaseUnit **)(*(long *)(this + 0xa8) + 0xb8) != (CBaseUnit *)0x0) &&
       (cVar1 = CBaseUnit::ISA(*(CBaseUnit **)(*(long *)(this + 0xa8) + 0xb8),0x78), cVar1 != '\0'))
    {
      return 1;
    }
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x60),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x68),0));
  }
  return 1;
}

/* address=00acd460
   symbol=CCombineMenu::handle_MouseOver */

/* CCombineMenu::handle_MouseOver(CEGUI::EventArgs const&) */

undefined8 __thiscall CCombineMenu::handle_MouseOver(CCombineMenu *this,EventArgs *param_1)

{
  char cVar1;
  CBaseUnit *pCVar2;
  long lVar3;

  if ((*(long *)(param_1 + 0x10) == 0) || (*(long *)(this + 0x90) == 0)) {
    return 1;
  }
  lVar3 = (long)**(int **)(*(long *)(param_1 + 0x10) + 0x1d8);
  pCVar2 = (CBaseUnit *)
           CInventory::getEquipmentInSlot
                     (*(CInventory **)(*(long *)(this + 0x90) + 0x490),
                      *(uint *)(this + lVar3 * 4 + 0xe8));
  if (pCVar2 != (CBaseUnit *)0x0) {
    *(CBaseUnit **)(this + 400) = pCVar2;
    if ((pCVar2[0x348] == (CBaseUnit)0x0) || (*(int *)(pCVar2 + 0x3e0) == 0)) {
      cVar1 = CBaseUnit::ISA(pCVar2,0x78);
      if (cVar1 == '\0') {
        CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x60),0));
        CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x68),0));
        goto LAB_00acd507;
      }
    }
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x68),0));
    CEGUI::Window::moveToFront();
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x60),0));
    CEGUI::Window::moveToFront();
  }
LAB_00acd507:
  lVar3 = lVar3 + 0x28;
  CEGUI::Window::getWidth();
  CEGUI::Window::getHeight();
  cVar1 = CEGUI::Window::isChild(*(Window **)(this + lVar3 * 8 + 8));
  if (cVar1 == '\0') {
    CEGUI::Window::addChildWindow(*(Window **)(this + lVar3 * 8 + 8));
  }
                    /* try { // try from 00acd614 to 00acd618 has its CatchHandler @ 00acd6ee */
  CEGUI::Window::setPosition(*(UVector2 **)(this + 0x1a0));
                    /* try { // try from 00acd675 to 00acd679 has its CatchHandler @ 00acd6e6 */
  CEGUI::Window::setSize(*(UVector2 **)(this + 0x1a0));
  CEGUI::Window::moveToBack();
  this[0x1a8] = (CCombineMenu)0x1;
  return 1;
}

/* address=00acd700
   symbol=CCombineMenu::processInput */

/* CCombineMenu::processInput(void*, float, bool) */

bool CCombineMenu::processInput(void *param_1,float param_2,bool param_3)

{
  long lVar1;
  Window *pWVar2;
  char cVar3;
  char in_DL;
  bool bVar4;

  if (in_DL == '\0') {
    *(undefined8 *)((long)param_1 + 400) = 0;
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)((long)param_1 + 0x60),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)((long)param_1 + 0x68),0));
    pWVar2 = *(Window **)(*(long *)((long)param_1 + 0x1a0) + 0xb0);
    if (pWVar2 != (Window *)0x0) {
      cVar3 = CEGUI::Window::isChild(pWVar2);
      if (cVar3 != '\0') {
        CEGUI::Window::removeChildWindow(*(Window **)(*(long *)((long)param_1 + 0x1a0) + 0xb0));
        return true;
      }
    }
    return true;
  }
  bVar4 = *(char *)((long)param_1 + 0x9a) != '\0';
  if (bVar4) {
    param_2 = (float)(**(code **)(*(long *)param_1 + 0x40))(param_1,0);
    *(undefined1 *)((long)param_1 + 0x9a) = 0;
  }
  if ((*(long *)((long)param_1 + 0x90) != 0) &&
     (lVar1 = *(long *)(*(long *)((long)param_1 + 0xa8) + 0xb8), lVar1 != 0)) {
    cVar3 = CBaseUnit::ISA((CBaseUnit *)param_2,lVar1,0x78);
    if (cVar3 != '\0') {
      CEGUI::Window::setVisible(SUB81(*(undefined8 *)((long)param_1 + 0x68),0));
      CEGUI::Window::moveToFront();
      CEGUI::Window::setVisible(SUB81(*(undefined8 *)((long)param_1 + 0x60),0));
      CEGUI::Window::moveToFront();
      goto LAB_00acd788;
    }
  }
  if (*(long *)((long)param_1 + 400) != 0) {
    if (*(char *)(*(long *)((long)param_1 + 400) + 0x198) == '\0') goto LAB_00acd788;
    *(undefined8 *)((long)param_1 + 400) = 0;
  }
  CEGUI::Window::setVisible(SUB81(*(undefined8 *)((long)param_1 + 0x60),0));
  CEGUI::Window::setVisible(SUB81(*(undefined8 *)((long)param_1 + 0x68),0));
LAB_00acd788:
  if (*(char *)((long)param_1 + 0x1a8) == '\0') {
    pWVar2 = *(Window **)(*(long *)((long)param_1 + 0x1a0) + 0xb0);
    if (pWVar2 != (Window *)0x0) {
      cVar3 = CEGUI::Window::isChild(pWVar2);
      if (cVar3 != '\0') {
        CEGUI::Window::removeChildWindow(*(Window **)(*(long *)((long)param_1 + 0x1a0) + 0xb0));
      }
    }
    *(undefined8 *)((long)param_1 + 400) = 0;
  }
  *(undefined4 *)((long)param_1 + 0x188) = 0xffffffff;
  *(undefined4 *)((long)param_1 + 0x18c) = 0xffffffff;
  return !bVar4;
}

/* address=00acd8d0
   symbol=CCombineMenu::itemUpdatedInMenu */

/* CCombineMenu::itemUpdatedInMenu(CEquipment*, bool) */

void __thiscall CCombineMenu::itemUpdatedInMenu(CCombineMenu *this,CEquipment *param_1,bool param_2)

{
  _Rb_tree_node_base *p_Var1;
  _Rb_tree_node_base *p_Var2;
  _Rb_tree_node_base *p_Var3;
  void *pvVar4;
  _Rb_tree_node_base *p_Var5;
  CEquipment *local_38;
  undefined8 local_30;
  undefined4 local_28;
  undefined8 local_18;
  undefined4 local_10;

  if (g_bDontTrackItemEquipAndUnEquip == '\0') {
    p_Var1 = (_Rb_tree_node_base *)(this + 0x20);
    p_Var3 = *(_Rb_tree_node_base **)(this + 0x28);
    p_Var5 = p_Var1;
    while (p_Var2 = p_Var3, p_Var2 != (_Rb_tree_node_base *)0x0) {
      if (*(CEquipment **)(p_Var2 + 0x20) < param_1) {
        p_Var3 = *(_Rb_tree_node_base **)(p_Var2 + 0x18);
      }
      else {
        p_Var3 = *(_Rb_tree_node_base **)(p_Var2 + 0x10);
        p_Var5 = p_Var2;
      }
    }
    if ((p_Var1 == p_Var5) || (param_1 < *(CEquipment **)(p_Var5 + 0x20))) {
      p_Var5 = p_Var1;
    }
    if (param_2) {
      if ((p_Var1 == p_Var5) && (*(long *)(param_1 + 0x240) != 0)) {
        local_18 = *(undefined8 *)(param_1 + 0x240);
        local_10 = *(undefined4 *)(param_1 + 0x298);
        p_Var3 = *(_Rb_tree_node_base **)(this + 0x28);
        p_Var5 = p_Var1;
        while (p_Var2 = p_Var3, p_Var2 != (_Rb_tree_node_base *)0x0) {
          if (*(CEquipment **)(p_Var2 + 0x20) < param_1) {
            p_Var3 = *(_Rb_tree_node_base **)(p_Var2 + 0x18);
          }
          else {
            p_Var3 = *(_Rb_tree_node_base **)(p_Var2 + 0x10);
            p_Var5 = p_Var2;
          }
        }
        if ((p_Var1 == p_Var5) || (param_1 < *(CEquipment **)(p_Var5 + 0x20))) {
          local_28 = 0;
          local_30 = 0;
          local_38 = param_1;
          p_Var5 = (_Rb_tree_node_base *)
                   std::
                   _Rb_tree<CEquipment*,std::pair<CEquipment*const,std::pair<CInventory*,EEQUIP_LOCATIONS>>,std::_Select1st<std::pair<CEquipment*const,std::pair<CInventory*,EEQUIP_LOCATIONS>>>,std::less<CEquipment*>,std::allocator<std::pair<CEquipment*const,std::pair<CInventory*,EEQUIP_LOCATIONS>>>>
                   ::_M_insert_unique_((_Rb_tree<CEquipment*,std::pair<CEquipment*const,std::pair<CInventory*,EEQUIP_LOCATIONS>>,std::_Select1st<std::pair<CEquipment*const,std::pair<CInventory*,EEQUIP_LOCATIONS>>>,std::less<CEquipment*>,std::allocator<std::pair<CEquipment*const,std::pair<CInventory*,EEQUIP_LOCATIONS>>>>
                                        *)(this + 0x18),p_Var5,&local_38);
        }
        *(undefined8 *)(p_Var5 + 0x28) = local_18;
        *(undefined4 *)(p_Var5 + 0x30) = local_10;
      }
    }
    else if (p_Var1 != p_Var5) {
      pvVar4 = (void *)std::_Rb_tree_rebalance_for_erase(p_Var5,p_Var1);
      operator_delete(pvVar4);
      *(long *)(this + 0x40) = *(long *)(this + 0x40) + -1;
    }
  }
  return;
}

/* address=00acda00
   symbol=CCombineMenu::equipmentDropped */

/* non-virtual thunk to CCombineMenu::equipmentDropped(CEquipment*) */

void __thiscall CCombineMenu::equipmentDropped(CCombineMenu *this,CEquipment *param_1)

{
  equipmentDropped(this + -0x10,param_1);
  return;
}

/* address=00acda10
   symbol=CCombineMenu::equipmentDropped */

/* CCombineMenu::equipmentDropped(CEquipment*) */

void __thiscall CCombineMenu::equipmentDropped(CCombineMenu *this,CEquipment *param_1)

{
  itemUpdatedInMenu(this,param_1,false);
                    /* WARNING: Could not recover jumptable at 0x00acda26. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)this + 0x48))(this);
  return;
}

/* address=00acda30
   symbol=CCombineMenu::equipmentPickedUp */

/* non-virtual thunk to CCombineMenu::equipmentPickedUp(CEquipment*) */

void __thiscall CCombineMenu::equipmentPickedUp(CCombineMenu *this,CEquipment *param_1)

{
  equipmentPickedUp(this + -0x10,param_1);
  return;
}

/* address=00acda40
   symbol=CCombineMenu::equipmentPickedUp */

/* CCombineMenu::equipmentPickedUp(CEquipment*) */

void __thiscall CCombineMenu::equipmentPickedUp(CCombineMenu *this,CEquipment *param_1)

{
  itemUpdatedInMenu(this,param_1,true);
                    /* WARNING: Could not recover jumptable at 0x00acda59. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)this + 0x48))(this);
  return;
}

/* address=00acda60
   symbol=CCombineMenu::setPlayer */

/* CCombineMenu::setPlayer(CCharacter*) */

void __thiscall CCombineMenu::setPlayer(CCombineMenu *this,CCharacter *param_1)

{
  CCharacter *pCVar1;

  pCVar1 = param_1;
  if (*(CCharacter **)(this + 0x90) != param_1) {
    (**(code **)(*(long *)this + 0x90))();
    pCVar1 = *(CCharacter **)(this + 0x90);
  }
  if (pCVar1 != (CCharacter *)0x0) {
    CInventory::removeListener(*(CInventory **)(pCVar1 + 0x490),(iInventoryListener *)(this + 0x10))
    ;
  }
  *(CCharacter **)(this + 0x90) = param_1;
  if (param_1 != (CCharacter *)0x0) {
    CInventory::addListener(*(CInventory **)(param_1 + 0x490),(iInventoryListener *)(this + 0x10));
    return;
  }
  return;
}

/* address=00ad47a0
   symbol=CCombineMenu::_GLOBAL__I_CCombineMenu */

/* CCombineMenu::CCombineMenu(CGameUI&, CSettings&, Ogre::RenderWindow*, Ogre::SceneManager*,
   CEGUI::Window*, CResourceManager*) */

void CCombineMenu::_GLOBAL__I_CCombineMenu(void)

{
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
  std::string::string((string *)::KLayoutFunctionNames,"GUIEXITGAME",&aStack_287);
  std::string::string((string *)(::KLayoutFunctionNames + 8),"GUIEXITAPPLICATION",&aStack_286);
  std::string::string((string *)(::KLayoutFunctionNames + 0x10),"GUINEWGAME",&aStack_285);
  std::string::string((string *)(::KLayoutFunctionNames + 0x18),"GUICONTINUEGAME",&aStack_284);
  std::string::string((string *)(::KLayoutFunctionNames + 0x20),"GUINEWGAMEMENU",&aStack_283);
  std::string::string((string *)(::KLayoutFunctionNames + 0x28),"GUICONTINUEGAMEMENU",&aStack_282);
  std::string::string((string *)(::KLayoutFunctionNames + 0x30),"GUICLOSEMENU",&aStack_281);
  std::string::string((string *)(::KLayoutFunctionNames + 0x38),"GUIBACK",&aStack_280);
  std::string::string((string *)(::KLayoutFunctionNames + 0x40),"GUIDECLINE",&aStack_27f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x48),"GUIACCEPT",&aStack_27e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x50),"GUIOK",&aStack_27d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x58),"GUIPAUSE",&aStack_27c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x60),"GUISCROLLUP",&aStack_27b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x68),"GUISCROLLDOWN",&aStack_27a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x70),"GUISELECT1",&aStack_279);
  std::string::string((string *)(::KLayoutFunctionNames + 0x78),"GUISELECT2",&aStack_278);
  std::string::string((string *)(::KLayoutFunctionNames + 0x80),"GUISELECT3",&aStack_277);
  std::string::string((string *)(::KLayoutFunctionNames + 0x88),"GUISELECT4",&aStack_276);
  std::string::string((string *)(::KLayoutFunctionNames + 0x90),"GUISELECT5",&aStack_275);
  std::string::string((string *)(::KLayoutFunctionNames + 0x98),"GUISELECT6",&aStack_274);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa0),"GUISELECT7",&aStack_273);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa8),"GUISELECT8",&aStack_272);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb0),"GUISELECT9",&aStack_271);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb8),"GUISELECT10",&aStack_270);
  std::string::string((string *)(::KLayoutFunctionNames + 0xc0),"GUISELECT11",&aStack_26f);
  std::string::string((string *)(::KLayoutFunctionNames + 200),"GUISELECT12",&aStack_26e);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd0),"GUISELECT13",&aStack_26d);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd8),"GUISELECT14",&aStack_26c);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe0),"GUISELECT15",&aStack_26b);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe8),"GUISELECT16",&aStack_26a);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf0),"GUISELECT17",&aStack_269);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf8),"GUISELECT18",&aStack_268);
  std::string::string((string *)(::KLayoutFunctionNames + 0x100),"GUISELECT19",&aStack_267);
  std::string::string((string *)(::KLayoutFunctionNames + 0x108),"GUISELECT20",&aStack_266);
  std::string::string((string *)(::KLayoutFunctionNames + 0x110),"GUISELECT21",&aStack_265);
  std::string::string((string *)(::KLayoutFunctionNames + 0x118),"GUISELECT22",&aStack_264);
  std::string::string((string *)(::KLayoutFunctionNames + 0x120),"GUISELECT23",&aStack_263);
  std::string::string((string *)(::KLayoutFunctionNames + 0x128),"GUISELECT24",&aStack_262);
  std::string::string((string *)(::KLayoutFunctionNames + 0x130),"GUISELECT25",&aStack_261);
  std::string::string((string *)(::KLayoutFunctionNames + 0x138),"GUISELECT26",&aStack_260);
  std::string::string((string *)(::KLayoutFunctionNames + 0x140),"GUISELECT27",&aStack_25f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x148),"GUISELECT28",&aStack_25e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x150),"GUISELECT29",&aStack_25d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x158),"GUISELECT30",&aStack_25c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x160),"GUISELECT31",&aStack_25b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x168),"GUISELECT32",&aStack_25a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x170),"GUISELECT33",&aStack_259);
  std::string::string((string *)(::KLayoutFunctionNames + 0x178),"GUISELECT34",&aStack_258);
  std::string::string((string *)(::KLayoutFunctionNames + 0x180),"GUISELECT35",&aStack_257);
  std::string::string((string *)(::KLayoutFunctionNames + 0x188),"GUISELECT36",&aStack_256);
  std::string::string((string *)(::KLayoutFunctionNames + 400),"GUISELECT37",&aStack_255);
  std::string::string((string *)(::KLayoutFunctionNames + 0x198),"GUISELECT38",&aStack_254);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a0),"GUISELECT39",&aStack_253);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a8),"GUISELECT40",&aStack_252);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b0),"GUISELECT41",&aStack_251);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b8),"GUISELECT42",&aStack_250);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c0),"GUISELECT43",&aStack_24f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c8),"GUISELECT44",&aStack_24e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d0),"GUISELECT45",&aStack_24d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d8),"GUISELECT46",&aStack_24c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e0),"GUISELECT47",&aStack_24b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e8),"GUISELECT48",&aStack_24a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f0),"GUISELECT49",&aStack_249);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f8),"GUISELECT50",&aStack_248);
  std::string::string((string *)(::KLayoutFunctionNames + 0x200),"GUISELECTA",&aStack_247);
  std::string::string((string *)(::KLayoutFunctionNames + 0x208),"GUISELECTB",&aStack_246);
  std::string::string((string *)(::KLayoutFunctionNames + 0x210),"GUISELECTC",&aStack_245);
  std::string::string((string *)(::KLayoutFunctionNames + 0x218),"GUISELECTD",&aStack_244);
  std::string::string((string *)(::KLayoutFunctionNames + 0x220),"GUIFEEDPET",&aStack_243);
  std::string::string((string *)(::KLayoutFunctionNames + 0x228),"GUIPETPASSIVE",&aStack_242);
  std::string::string((string *)(::KLayoutFunctionNames + 0x230),"GUIPETAGGRESSIVE",&aStack_241);
  std::string::string((string *)(::KLayoutFunctionNames + 0x238),"GUIPETDEFENSIVE",&aStack_240);
  std::string::string((string *)(::KLayoutFunctionNames + 0x240),"GUITOGGLEINVENTORY",&aStack_23f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x248),"GUITOGGLEQUESTS",&aStack_23e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x250),"GUITOGGLESTATS",&aStack_23d);
  std::string::string((string *)(::KLayoutFunctionNames + 600),"GUITOGGLESKILLS",&aStack_23c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x260),"GUITOGGLEPERKS",&aStack_23b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x268),"GUITOGGLEJOURNAL",&aStack_23a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x270),"GUITOGGLEPET",&aStack_239);
  std::string::string((string *)(::KLayoutFunctionNames + 0x278),"GUITOGGLEAUTOMAP",&aStack_238);
  std::string::string((string *)(::KLayoutFunctionNames + 0x280),"GUITOGGLEOPTIONS",&aStack_237);
  std::string::string((string *)(::KLayoutFunctionNames + 0x288),"GUITOGGLEITEMNAMES",&aStack_236);
  std::string::string((string *)(::KLayoutFunctionNames + 0x290),"GUIAUTOMAPZOOMIN",&aStack_235);
  std::string::string((string *)(::KLayoutFunctionNames + 0x298),"GUIAUTOMAPZOOMOUT",&aStack_234);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a0),"GUILEVELUP",&aStack_233);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a8),"GUISTATSUP",&aStack_232);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b0),"GUISKILLUP",&aStack_231);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b8),"GUIPET1",&aStack_230);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c0),"GUIPET2",&aStack_22f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c8),"GUIPET3",&aStack_22e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d0),"GUIDELETE1",&aStack_22d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d8),"GUIDELETE2",&aStack_22c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e0),"GUIDELETE3",&aStack_22b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e8),"GUIDELETE4",&aStack_22a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f0),"GUISETTINGSMENU",&aStack_229);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f8),"GUIPETSELL",&aStack_228);
  std::string::string((string *)(::KLayoutFunctionNames + 0x300),"NONE",&aStack_227);
  __cxa_atexit(::__tcf_0,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSOUNDBANK_STRINGS,L"STEP_SOUND",&aStack_226);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 8),L"STRIKE_SOUND",&aStack_225);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x10),L"PHYSICALHIT_SOUND",&aStack_224);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x18),L"ICEHIT_SOUND",&aStack_223);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x20),L"FIREHIT_SOUND",&aStack_222);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x28),L"ELECTRICHIT_SOUND",&aStack_221);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x30),L"POISONHIT_SOUND",&aStack_220);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x38),L"SHIELDBLOCK",&aStack_21f);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x40),L"BLOCK",&aStack_21e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x48),L"CRITICAL_SOUND",&aStack_21d);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x50),L"ATTACK_SOUND",&aStack_21c);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x58),L"IDLE_SOUND",&aStack_21b)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x60),L"DEATH_SOUND",&aStack_21a);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x68),L"ROAR_SOUND",&aStack_219)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x70),L"FLEE_SOUND",&aStack_218)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x78),L"MISS_SOUND",&aStack_217)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x80),L"FALL_SOUND",&aStack_216)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x88),L"LAND_SOUND",&aStack_215)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x90),L"TAKE_SOUND",&aStack_214)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x98),L"SPAWN_SOUND",&aStack_213);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa0),L"USE_SOUND",&aStack_212);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa8),L"EQUIP_SOUND",&aStack_211);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb0),L"OPENMENU_SOUND",&aStack_210);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb8),L"BUY_SOUND",&aStack_20f);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xc0),L"ERROR_SOUND",&aStack_20e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 200),L"LEVELUP_SOUND",&aStack_20d);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd0),L"EFFORT_SOUND",&aStack_20c);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd8),L"SPENDPOINT_SOUND",&aStack_20b);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe0),L"PORTALENTER_SOUND",&aStack_20a);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe8),L"POERTALEXIT_SOUND",&aStack_209);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf0),L"SKILLASSIGN_SOUND",&aStack_208);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf8),L"QUESTRECEIVED_SOUND",&aStack_207);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x100),L"QUESTCOMPLETED_SOUND",&aStack_206)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x108),L"LOWMANA_SOUND",&aStack_205);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x110),L"MISSILEREFLECT_SOUND",&aStack_204)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x118),L"BADEFFECT_SOUND",&aStack_203);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x120),L"GOODEFFECT_SOUND",&aStack_202);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x128),L"NPCDIALOG_SOUND",&aStack_201);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x130),L"NPCGREET",&aStack_200);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x138),L"NPCBYE",&aStack_1ff);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x140),L"NPCPURCHASE",&aStack_1fe);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x148),L"NPCSELL",&aStack_1fd);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x150),L"VOICEPETINVENTORYFULL_SOUND",
             &aStack_1fc);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x158),L"VOICEPETDEPARTED_SOUND",
             &aStack_1fb);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x160),L"VOICEPETRETURNED_SOUND",
             &aStack_1fa);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x168),L"VOICEPETFLED_SOUND",&aStack_1f9);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x170),L"VOICEPETLEVELUP_SOUND",&aStack_1f8
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x178),L"VOICEINVENTORYFULL_SOUND",
             &aStack_1f7);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x180),L"VOICEINSUFFICIENTGOLD_SOUND",
             &aStack_1f6);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x188),L"VOICEIMPOSSIBLE_SOUND",&aStack_1f5
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 400),L"VOICECANTCAST_SOUND",&aStack_1f4);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x198),L"VOICECANTCASTHERE_SOUND",
             &aStack_1f3);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a0),L"VOICEHEALTHLOW_SOUND",&aStack_1f2)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a8),L"VOICEMANALOW_SOUND",&aStack_1f1);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b0),L"VOICETRAPSPRUNG_SOUND",&aStack_1f0
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b8),L"VOICEREFRESHED_SOUND",&aStack_1ef)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c0),L"VOICEPOWERFUL_SOUND",&aStack_1ee);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c8),L"VOICEHEALTHY_SOUND",&aStack_1ed);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d0),L"VOICEILL_SOUND",&aStack_1ec);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d8),L"VOICEPOISONED_SOUND",&aStack_1eb);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e0),L"VOICELEVELUP_SOUND",&aStack_1ea);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e8),L"VOICEFAMEUP_SOUND",&aStack_1e9);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f0),L"VOICESKILLUP_SOUND",&aStack_1e8);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f8),L"VOICEFORTUNEGOOD_SOUND",
             &aStack_1e7);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x200),L"VOICEFORTUNEBAD_SOUND",&aStack_1e6
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x208),L"VOICESPELLLEARNED_SOUND",
             &aStack_1e5);
  ::KSOUNDBANK_STRINGS._528_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_1,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KALIGNMENT_STRINGS,L"NEUTRAL",&aStack_1e4);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 8),L"GOOD",&aStack_1e3);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x10),L"EVIL",&aStack_1e2);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x18),L"ALL",&aStack_1e1);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x20),L"BERSERK",&aStack_1e0);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x28),L"EVILBERSERK",&aStack_1df);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x30),L"GOODBERSERK",&aStack_1de);
  __cxa_atexit(::__tcf_2,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KAITYPE_STRINGS,L"NORMAL",&aStack_1dd);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 8),L"RANGEDDEFENDER",&aStack_1dc);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x10),L"DEFENDER",&aStack_1db);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x18),L"RANGEDCASTER",&aStack_1da);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x20),L"CIRCLER",&aStack_1d9);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x28),L"RESURRECTER",&aStack_1d8);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x30),L"DUMMY",&aStack_1d7);
  __cxa_atexit(::__tcf_3,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gDAMAGE_TYPES,L"Physical",&aStack_1d6);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 8),L"Magical",&aStack_1d5);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x10),L"Fire",&aStack_1d4);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x18),L"Ice",&aStack_1d3);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x20),L"Electric",&aStack_1d2);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x28),L"Poison",&aStack_1d1);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x30),L"All",&aStack_1d0);
  __cxa_atexit(::__tcf_4,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::gTARGET_TYPES,L"USER",&aStack_1cf);
  std::wstring::wstring((wstring_conflict *)&DAT_014ba348,L"ITEM",&aStack_1ce);
  __cxa_atexit(::__tcf_5,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSFXTypeName,L"STATIONARYTARGET",&aStack_1cd);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 8),L"STATIONARYOWNER",&aStack_1cc);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x10),L"STATIONARY",&aStack_1cb);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x18),L"STATIONARYPORTAL",&aStack_1ca)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x20),L"BEAM",&aStack_1c9);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x28),L"FOLLOWOWNER",&aStack_1c8);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x30),L"FOLLOWTARGET",&aStack_1c7);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x38),L"PROJECTILELOCATION",&aStack_1c6);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x40),L"PROJECTILECHARACTER",&aStack_1c5);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x48),L"PROJECTILELOCATIONERRATIC",&aStack_1c4);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x50),L"PROJECTILECHARACTERERRATIC",&aStack_1c3);
  __cxa_atexit(::__tcf_6,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KCharacterNames,L"NA",&aStack_1c2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 8),L"NA",&aStack_1c1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x10),L"NA",&aStack_1c0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x18),L"NA",&aStack_1bf);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x20),L"NA",&aStack_1be);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x28),L"NA",&aStack_1bd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x30),L"NA",&aStack_1bc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x38),L"NA",&aStack_1bb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x40),L"Bksp",&aStack_1ba);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x48),L"Tab",&aStack_1b9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x50),L"NA",&aStack_1b8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x58),L"NA",&aStack_1b7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x60),L"Ctr",&aStack_1b6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x68),L"Ret",&aStack_1b5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x70),L"NA",&aStack_1b4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x78),L"NA",&aStack_1b3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x80),L"Shift",&aStack_1b2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x88),L"Ctrl",&aStack_1b1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x90),L"Alt",&aStack_1b0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x98),L"Tab",&aStack_1af);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa0),L"NA",&aStack_1ae);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa8),L"NA",&aStack_1ad);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb0),L"NA",&aStack_1ac);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb8),L"NA",&aStack_1ab);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xc0),L"NA",&aStack_1aa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 200),L"NA",&aStack_1a9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd0),L"NA",&aStack_1a8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd8),L"NA",&aStack_1a7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe0),L"NA",&aStack_1a6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe8),L"NA",&aStack_1a5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf0),L"NA",&aStack_1a4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf8),L"NA",&aStack_1a3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x100),L"space",&aStack_1a2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x108),L"pgup",&aStack_1a1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x110),L"pgdn",&aStack_1a0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x118),L"end",&aStack_19f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x120),L"home",&aStack_19e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x128),L"left arrow",&aStack_19d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x130),L"up arrow",&aStack_19c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x138),L"right arrow",&aStack_19b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x140),L"down arrow",&aStack_19a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x148),L")",&aStack_199);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x150),L"*",&aStack_198);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x158),L"+",&aStack_197);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x160),L",",&aStack_196);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x168),L"ins",&aStack_195);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x170),L"del",&aStack_194);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x178),L"/",&aStack_193);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x180),L"0",&aStack_192);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x188),L"1",&aStack_191);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 400),L"2",&aStack_190);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x198),L"3",&aStack_18f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a0),L"4",&aStack_18e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a8),L"5",&aStack_18d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b0),L"6",&aStack_18c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b8),L"7",&aStack_18b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c0),L"8",&aStack_18a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c8),L"9",&aStack_189);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d0),L":",&aStack_188);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d8),L";",&aStack_187);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e0),L"<",&aStack_186);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e8),L"=",&aStack_185);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f0),L">",&aStack_184);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f8),L"?",&aStack_183);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x200),L"@",&aStack_182);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x208),L"a",&aStack_181);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x210),L"b",&aStack_180);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x218),L"c",&aStack_17f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x220),L"d",&aStack_17e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x228),L"e",&aStack_17d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x230),L"NA",&aStack_17c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x238),L"g",&aStack_17b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x240),L"h",&aStack_17a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x248),L"i",&aStack_179);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x250),L"j",&aStack_178);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 600),L"k",&aStack_177);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x260),L"l",&aStack_176);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x268),L"m",&aStack_175);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x270),L"n",&aStack_174);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x278),L"o",&aStack_173);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x280),L"p",&aStack_172);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x288),L"NA",&aStack_171);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x290),L"r",&aStack_170);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x298),L"s",&aStack_16f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a0),L"t",&aStack_16e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a8),L"u",&aStack_16d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b0),L"v",&aStack_16c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b8),L"w",&aStack_16b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c0),L"x",&aStack_16a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c8),L"y",&aStack_169);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d0),L"z",&aStack_168);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d8),L"[",&aStack_167);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e0),L"\\",&aStack_166);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e8),L"]",&aStack_165);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f0),L"^",&aStack_164);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f8),L"_",&aStack_163);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x300),L"NUM 0",&aStack_162);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x308),L"NUM 1",&aStack_161);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x310),L"NUM 2",&aStack_160);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x318),L"NUM 3",&aStack_15f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 800),L"NUM 4",&aStack_15e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x328),L"NUM 5",&aStack_15d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x330),L"NUM 6",&aStack_15c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x338),L"NUM 7",&aStack_15b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x340),L"NUM 8",&aStack_15a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x348),L"NUM 9",&aStack_159);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x350),L"*",&aStack_158);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x358),L"+",&aStack_157);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x360),L"NA",&aStack_156);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x368),L"-",&aStack_155);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x370),L"NA",&aStack_154);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x378),L"F1",&aStack_153);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x380),L"F2",&aStack_152);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x388),L"F3",&aStack_151);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x390),L"F4",&aStack_150);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x398),L"F5",&aStack_14f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a0),L"F6",&aStack_14e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a8),L"F7",&aStack_14d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b0),L"F8",&aStack_14c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b8),L"F9",&aStack_14b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c0),L"F10",&aStack_14a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c8),L"F11",&aStack_149);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d0),L"F12",&aStack_148);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d8),L"{",&aStack_147);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3e0),L"|",&aStack_146);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 1000),L"}",&aStack_145);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f0),L"~",&aStack_144);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f8),L";",&aStack_143);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x400),L"=",&aStack_142);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x408),L".",&aStack_141);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x410),L"-",&aStack_140);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x418),L",",&aStack_13f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x420),L"/",&aStack_13e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x428),L"`",&aStack_13d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x430),L"[",&aStack_13c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x438),L"\\",&aStack_13b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x440),L"]",&aStack_13a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x448),L"\'",&aStack_139);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x450),L"NA",&aStack_138);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x458),L"NA",&aStack_137);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x460),L"NA",&aStack_136);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x468),L"NA",&aStack_135);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x470),L"NA",&aStack_134);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x478),L"NA",&aStack_133);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x480),L"NA",&aStack_132);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x488),L"NA",&aStack_131);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x490),L"NA",&aStack_130);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x498),L"NA",&aStack_12f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a0),L"NA",&aStack_12e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a8),L"NA",&aStack_12d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b0),L"NA",&aStack_12c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b8),L"NA",&aStack_12b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c0),L"NA",&aStack_12a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c8),L"NA",&aStack_129);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d0),L"NA",&aStack_128);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d8),L"NA",&aStack_127);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e0),L"NA",&aStack_126);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e8),L"NA",&aStack_125);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f0),L"NA",&aStack_124);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f8),L"NA",&aStack_123);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x500),L"NA",&aStack_122);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x508),L"NA",&aStack_121);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x510),L"NA",&aStack_120);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x518),L"NA",&aStack_11f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x520),L"NA",&aStack_11e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x528),L"NA",&aStack_11d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x530),L"NA",&aStack_11c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x538),L"NA",&aStack_11b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x540),L"NA",&aStack_11a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x548),L"NA",&aStack_119);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x550),L"NA",&aStack_118);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x558),L"NA",&aStack_117);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x560),L"NA",&aStack_116);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x568),L"NA",&aStack_115);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x570),L"NA",&aStack_114);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x578),L"NA",&aStack_113);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x580),L"NA",&aStack_112);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x588),L"NA",&aStack_111);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x590),L"NA",&aStack_110);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x598),L"NA",&aStack_10f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a0),L"NA",&aStack_10e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a8),L"NA",&aStack_10d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b0),L"NA",&aStack_10c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b8),L"NA",&aStack_10b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c0),L"NA",&aStack_10a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c8),L"NA",&aStack_109);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d0),L";",&aStack_108);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d8),L"=",&aStack_107);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e0),L",",&aStack_106);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e8),L"-",&aStack_105);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f0),L".",&aStack_104);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f8),L"/",&aStack_103);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x600),L"`",&aStack_102);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x608),L"NA",&aStack_101);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x610),L"NA",&aStack_100);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x618),L"NA",&aStack_ff);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x620),L"NA",&aStack_fe);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x628),L"NA",&aStack_fd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x630),L"NA",&aStack_fc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x638),L"NA",&aStack_fb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x640),L"NA",&aStack_fa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x648),L"NA",&aStack_f9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x650),L"NA",&aStack_f8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x658),L"NA",&aStack_f7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x660),L"NA",&aStack_f6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x668),L"NA",&aStack_f5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x670),L"NA",&aStack_f4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x678),L"NA",&aStack_f3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x680),L"NA",&aStack_f2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x688),L"NA",&aStack_f1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x690),L"NA",&aStack_f0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x698),L"NA",&aStack_ef);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a0),L"NA",&aStack_ee);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a8),L"NA",&aStack_ed);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b0),L"NA",&aStack_ec);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b8),L"NA",&aStack_eb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c0),L"NA",&aStack_ea);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c8),L"NA",&aStack_e9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d0),L"NA",&aStack_e8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d8),L"[",&aStack_e7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e0),L"\\",&aStack_e6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e8),L"]",&aStack_e5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f0),L"\'",&aStack_e4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f8),L"NA",&aStack_e3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x700),L"NA",&aStack_e2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x708),L"NA",&aStack_e1);
  __cxa_atexit(::__tcf_7,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KContextTipNames,L"TIP_INVENTORY",&aStack_e0);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 8),L"TIP_UNIDENTIFIED",&aStack_df)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x10),L"TIP_INVENTORYFULL",&aStack_de);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x18),L"TIP_HEALTHLOW",&aStack_dd)
  ;
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x20),L"TIP_MANALOW",&aStack_dc);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x28),L"TIP_MERCHANT",&aStack_db);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x30),L"TIP_LEVELUP",&aStack_da);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x38),L"TIP_STATS",&aStack_d9);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x40),L"TIP_SPELL",&aStack_d8);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x48),L"TIP_WELCOME",&aStack_d7);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x50),L"TIP_SOCKETABLE",&aStack_d6);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x58),L"TIP_PETFLEE",&aStack_d5);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x60),L"TIP_GAMBLE",&aStack_d4);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x68),L"TIP_ENCHANT",&aStack_d3);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x70),L"TIP_TRANSMUTE",&aStack_d2)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x78),L"TIP_PETINVENTORY",&aStack_d1);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x80),L"TIP_PETINVENTORYFULL",&aStack_d0);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x88),L"TIP_STASH",&aStack_cf);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x90),L"TIP_FISHING",&aStack_ce);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x98),L"TIP_SPELLFIND",&aStack_cd)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xa0),L"TIP_QUESTCOMPLETE",&aStack_cc);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xa8),L"TIP_SHAREDSTASH",&aStack_cb);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xb0),L"TIP_HOWTOATTACK",&aStack_ca);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xb8),L"TIP_TEMP5",&aStack_c9);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xc0),L"TIP_TEMP6",&aStack_c8);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 200),L"TIP_TEMP7",&aStack_c7);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xd0),L"TIP_TEMP8",&aStack_c6);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xd8),L"TIP_TEMP9",&aStack_c5);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xe0),L"TIP_TEMP10",&aStack_c4);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xe8),L"TIP_TEMP11",&aStack_c3);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xf0),L"TIP_TEMP12",&aStack_c2);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xf8),L"TIP_TEMP13",&aStack_c1);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x100),L"TIP_TEMP14",&aStack_c0);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x108),L"TIP_TEMP15",&aStack_bf);
  __cxa_atexit(::__tcf_8,0,&__dso_handle);
  ParticleUniverse::HALFSCALE._4_4_ = DAT_0142463c * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._0_4_ = Ogre::Vector3::UNIT_SCALE * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._8_4_ = DAT_00fa4810 * DAT_01424640;
  std::string::string((string *)&ParticleUniverse::ALIAS,"1",&aStack_be);
  __cxa_atexit(std::string::~string,&ParticleUniverse::ALIAS,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::SYSTEM,"2",&aStack_bd);
  __cxa_atexit(std::string::~string,&ParticleUniverse::SYSTEM,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::TECHNIQUE,"3",&aStack_bc);
  __cxa_atexit(std::string::~string,&ParticleUniverse::TECHNIQUE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::RENDERER,"4",&aStack_bb);
  __cxa_atexit(std::string::~string,&ParticleUniverse::RENDERER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EMITTER,"5",&aStack_ba);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EMITTER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::AFFECTOR,"6",&aStack_b9);
  __cxa_atexit(std::string::~string,&ParticleUniverse::AFFECTOR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::OBSERVER,"7",&aStack_b8);
  __cxa_atexit(std::string::~string,&ParticleUniverse::OBSERVER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::HANDLER,"8",&aStack_b7);
  __cxa_atexit(std::string::~string,&ParticleUniverse::HANDLER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::BEHAVIOUR,"9",&aStack_b6);
  __cxa_atexit(std::string::~string,&ParticleUniverse::BEHAVIOUR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EXTERN,"10",&aStack_b5);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EXTERN,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DYNAMIC_ATTRIBUTE,"11",&aStack_b4);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DYNAMIC_ATTRIBUTE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DEPENDENCY,"12",&aStack_b3);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DEPENDENCY,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_TYPE_NAMES,L"",&aStack_b2);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 8),L"FIND",&aStack_b1);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x10),L"KILL NUM",&aStack_b0);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x18),L"KILL BOSS",&aStack_af);
  __cxa_atexit(::__tcf_9,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_DIALOG_TYPE_NAMES,L"ERROR",&aStack_ae);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 8),L"INTRO",&aStack_ad);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x10),L"RETURN",&aStack_ac);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x18),L"COMPLETE",&aStack_ab);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x20),L"PASSIVE",&aStack_aa);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x28),L"DETAILS",&aStack_a9);
  __cxa_atexit(::__tcf_10,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEffect_Activation_Names,L"PASSIVE",&aStack_a8);
  std::wstring::wstring((wstring_conflict *)(::gEffect_Activation_Names + 8),L"DYNAMIC",&aStack_a7);
  std::wstring::wstring
            ((wstring_conflict *)(::gEffect_Activation_Names + 0x10),L"TRANSFER",&aStack_a6);
  __cxa_atexit(::__tcf_11,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEFFECT_STAT_MODIFIER_NAMES,L"MELEE",&aStack_a5);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 8),L"RANGED",&aStack_a4);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x10),L"DEFENSE",&aStack_a3);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x18),L"MAGIC",&aStack_a2);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x20),L"LEVEL",&aStack_a1);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x28),L"OWNERLEVEL",&aStack_a0);
  __cxa_atexit(::__tcf_12,0,&__dso_handle);
  std::string::string((string *)::gEFFECT_STAT_MODIFIER_ICON_NAMES,"iconmelee",&aStack_9f);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 8),"iconranged",&aStack_9e);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x10),"icondefense",&aStack_9d
                     );
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x18),"iconmagic",&aStack_9c);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x20),"iconmagic",&aStack_9b);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x28),"iconmagic",&aStack_9a);
  __cxa_atexit(::__tcf_13,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES,"tag_righthand",&aStack_99);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 8),"tag_lefthand",&aStack_98);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x10),"",&aStack_97);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x18),"Bip01 Head",&aStack_96);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x20),"",&aStack_95);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x28),"Bip01 L Clavicle",&aStack_94);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x30),"",&aStack_93);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x38),"",&aStack_92);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x40),"",&aStack_91);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x48),"",&aStack_90);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x50),"",&aStack_8f);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x58),"tag_leftarm",&aStack_8e);
  __cxa_atexit(::__tcf_14,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES_SECONDARY,"",&aStack_8d);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 8),"",&aStack_8c);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x10),"",&aStack_8b);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x18),"",&aStack_8a);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x20),"",&aStack_89);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x28),"Bip01 R Clavicle",
                      &aStack_88);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x30),"",&aStack_87);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x38),"",&aStack_86);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x40),"",&aStack_85);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x48),"",&aStack_84);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x50),"",&aStack_83);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x58),"",&aStack_82);
  __cxa_atexit(::__tcf_15,0,&__dso_handle);
  std::string::string((string *)::KEquipmentIconName,"EquipLeftHand",&aStack_81);
  std::string::string((string *)(::KEquipmentIconName + 8),"EquipRightHand",&aStack_80);
  std::string::string((string *)(::KEquipmentIconName + 0x10),"EquipGloves",&aStack_7f);
  std::string::string((string *)(::KEquipmentIconName + 0x18),"EquipHelm",&aStack_7e);
  std::string::string((string *)(::KEquipmentIconName + 0x20),"EquipChest",&aStack_7d);
  std::string::string((string *)(::KEquipmentIconName + 0x28),"EquipShoulder",&aStack_7c);
  std::string::string((string *)(::KEquipmentIconName + 0x30),"EquipBoots",&aStack_7b);
  std::string::string((string *)(::KEquipmentIconName + 0x38),"EquipBelt",&aStack_7a);
  std::string::string((string *)(::KEquipmentIconName + 0x40),"EquipRing1",&aStack_79);
  std::string::string((string *)(::KEquipmentIconName + 0x48),"EquipRing2",&aStack_78);
  std::string::string((string *)(::KEquipmentIconName + 0x50),"EquipAmulet",&aStack_77);
  std::string::string((string *)(::KEquipmentIconName + 0x58),"",&aStack_76);
  __cxa_atexit(::__tcf_16,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames,L"CHEST",&aStack_75);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 8),L"GLOVES",&aStack_74);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x10),L"BOOTS",&aStack_73);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x18),L"HELMET",&aStack_72);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x20),L"SHOULDERS",&aStack_71);
  __cxa_atexit(::__tcf_17,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames2,L"",&aStack_70);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 8),L"",&aStack_6f);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x10),L"",&aStack_6e);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x18),L"FACE",&aStack_6d);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x20),L"",&aStack_6c);
  __cxa_atexit(::__tcf_18,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_AIFLAG_TYPE_NAMES,L"AWARE",&aStack_6b);
  std::wstring::wstring((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 8),L"BERSERK",&aStack_6a);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x10),L"CANNOT INTERRUPT",&aStack_69);
  std::wstring::wstring((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x18),L"FRIGHTEN",&aStack_68);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x20),L"NO LINE OF SIGHT",&aStack_67);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x28),L"NEVER CHANGE TARGET",&aStack_66);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x30),L"CANNOT TARGET",&aStack_65);
  __cxa_atexit(::__tcf_19,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_AISTAT_TYPE_NAMES,L"NONE",&aStack_64);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 8),L"HP",&aStack_63);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x10),L"MANA",&aStack_62);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x18),L"HP PCT",&aStack_61);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x20),L"MANA PCT",&aStack_60);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x28),L"ACTIVE UNITS",&aStack_5f);
  __cxa_atexit(::__tcf_20,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::g_AISTAT_LOGIC_NAMES,L"BELOW",&aStack_5e);
  std::wstring::wstring((wstring_conflict *)&DAT_014baf78,L"ABOVE",&aStack_5d);
  __cxa_atexit(::__tcf_21,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_AISTAT_TARGET_NAMES,L"SELF",&aStack_5c);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 8),L"FORMATION",&aStack_5b);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 0x10),L"AREA",&aStack_5a);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 0x18),L"AREAUNITTYPES",&aStack_59);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 0x20),L"AREAFORMATION",&aStack_58);
  __cxa_atexit(::__tcf_22,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)OGRE_UTILITIES::gPRIMITIVE_NAMES,L"SPHERE",&aStack_57);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 8),L"BOX",&aStack_56);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x10),L"PLANE",&aStack_55);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x18),L"CYLINDER",&aStack_54);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x20),L"CONE",&aStack_53);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x28),L"ARROW",&aStack_52);
  __cxa_atexit(::__tcf_23,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gKEYFRAME_TYPES,L"HIT",&aStack_51);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 8),L"BLENDIN",&aStack_50);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x10),L"BLENDOUT",&aStack_4f);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x18),L"PLAYSOUND",&aStack_4e);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x20),L"SPAWNPARTICLE",&aStack_4d);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x28),L"SPAWNPARTICLE_STOP_ON_DEATH",
             &aStack_4c);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x30),L"FOOTSTEP",&aStack_4b);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x38),L"SHOWWEAPONTRAIL",&aStack_4a);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x40),L"HIDEWEAPONTRAIL",&aStack_49);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x48),L"ATTACKSOUND",&aStack_48);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x50),L"ENABLECOLLISION",&aStack_47);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x58),L"DISABLECOLLISION",&aStack_46);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x60),L"REMOVEPARTICLES",&aStack_45);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x68),L"REMOVEANIMATIONPARTICLES",&aStack_44);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x70),L"CAMERASHAKE",&aStack_43);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x78),L"ATTACKEND",&aStack_42);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x80),L"UNTARGETABLE",&aStack_41);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x88),L"TARGETABLE",&aStack_40);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x90),L"DAMPVELOCITY",&aStack_3f);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x98),L"UNDAMPVELOCITY",&aStack_3e)
  ;
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xa0),L"SHOWWEAPONS",&aStack_3d);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xa8),L"HIDEWEAPONS",&aStack_3c);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xb0),L"HIDEMESH",&aStack_3b);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xb8),L"SHOWMESH",&aStack_3a);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xc0),L"FADEOUTMESH",&aStack_39);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 200),L"FADEINMESH",&aStack_38);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0xd0),L"CAMERASHAKE_NO_FALLOFF",&aStack_37);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0xd8),L"PLAYSOUND_NO_FALLOFF",&aStack_36);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xe0),L"HITTWO",&aStack_35);
  __cxa_atexit(::__tcf_24,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEDITOR_EVENT_NAMES,L"STOP",&aStack_34);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 8),L"PLAY",&aStack_33);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x10),L"RELOAD TILES",&aStack_32);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x18),L"TOGGLE LIGHTING",&aStack_31);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x20),L"SELECT COLLIDABLE",&aStack_30);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x28),L"PAUSE PARTICLES",&aStack_2f);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x30),L"UNPAUSE PARTICLES",&aStack_2e);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x38),L"COLLISION ALL",&aStack_2d);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x40),L"COLLISION MODELS",&aStack_2c);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x48),L"COLLISION PREFABS",&aStack_2b);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x50),L"COLLISION ROOMPIECES",&aStack_2a);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x58),L"COLLISION ROOMPROPS",&aStack_29);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x60),L"RELOAD GRAPHS",&aStack_28);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x68),L"TOGGLE PLAYER LIGHT",&aStack_27);
  __cxa_atexit(::__tcf_25,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEDITOR_FLAG_NAMES,L"LOGIC ENABLED",&aStack_26);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 8),L"INGAME MODE",&aStack_25);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x10),L"SHOW STATS",&aStack_24);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x18),L"EDIT POSITION",&aStack_23);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x20),L"EDIT SCALE",&aStack_22);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x28),L"EDIT ORIENTATION",&aStack_21);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x30),L"EDIT NONE",&aStack_20);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x38),L"SHOW HELPERS",&aStack_1f);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x40),L"SHOW GRID",&aStack_1e);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x48),L"SHOW WORKING PLANE",&aStack_1d);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x50),L"SNAP TO GRID",&aStack_1c);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x58),L"SUSPEND EDITOR",&aStack_1b);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x60),L"LIGHTING VISIBLE",&aStack_1a);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x68),L"RECALCULATE LIGHTING",&aStack_19);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x70),L"SHOW EDGES",&aStack_18);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x78),L"UPDATE PARTICLES CIRCLE",&aStack_17
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x80),L"SHOW LOGIC OUTPUT",&aStack_16);
  __cxa_atexit(::__tcf_26,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::gEDITOR_UPDATE_MASKS,L"OBJECT SELECTION CHANGED",&aStack_15);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 8),L"OBJECT DATA CHANGED",&aStack_14);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 0x10),L"OBJECTS CREATED",&aStack_13);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 0x18),L"REFRESH TREE VIEW",&aStack_12);
  __cxa_atexit(::__tcf_27,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::m_gFileVersionExtension,L".svt",&aStack_11);
  __cxa_atexit(std::wstring::~wstring,&::m_gFileVersionExtension,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gRESOURCE_GROUP_NAMES,L"ITEMS",&aStack_10);
  std::wstring::wstring((wstring_conflict *)(::gRESOURCE_GROUP_NAMES + 8),L"MONSTERS",&aStack_f);
  std::wstring::wstring((wstring_conflict *)(::gRESOURCE_GROUP_NAMES + 0x10),L"PLAYERS",&aStack_e);
  std::wstring::wstring((wstring_conflict *)(::gRESOURCE_GROUP_NAMES + 0x18),L"PROPS",&aStack_d);
  __cxa_atexit(::__tcf_28,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::gRESOURCE_GROUP_FILE_LOCATIONS,L"media/units/items/",&aStack_c);
  std::wstring::wstring
            ((wstring_conflict *)(::gRESOURCE_GROUP_FILE_LOCATIONS + 8),L"media/units/monsters/",
             &aStack_b);
  std::wstring::wstring
            ((wstring_conflict *)(::gRESOURCE_GROUP_FILE_LOCATIONS + 0x10),L"media/units/players/",
             &aStack_a);
  std::wstring::wstring
            ((wstring_conflict *)(::gRESOURCE_GROUP_FILE_LOCATIONS + 0x18),L"media/units/props/",
             &aStack_9);
  __cxa_atexit(::__tcf_29,0,&__dso_handle);
  return;
}

/* address=00ad47b0
   symbol=CCombineMenu::~CCombineMenu */

/* CCombineMenu::~CCombineMenu() */

void __thiscall CCombineMenu::~CCombineMenu(CCombineMenu *this)

{
  *(undefined ***)this = &PTR__CCombineMenu_00fe6270;
  *(undefined ***)(this + 0x10) = &PTR__CCombineMenu_00fe6320;
                    /* try { // try from 00ad47e0 to 00ad4839 has its CatchHandler @ 00ad487a */
  std::
  _Rb_tree<CEquipment*,std::pair<CEquipment*const,std::pair<CInventory*,EEQUIP_LOCATIONS>>,std::_Select1st<std::pair<CEquipment*const,std::pair<CInventory*,EEQUIP_LOCATIONS>>>,std::less<CEquipment*>,std::allocator<std::pair<CEquipment*const,std::pair<CInventory*,EEQUIP_LOCATIONS>>>>
  ::_M_erase((_Rb_tree<CEquipment*,std::pair<CEquipment*const,std::pair<CInventory*,EEQUIP_LOCATIONS>>,std::_Select1st<std::pair<CEquipment*const,std::pair<CInventory*,EEQUIP_LOCATIONS>>>,std::less<CEquipment*>,std::allocator<std::pair<CEquipment*const,std::pair<CInventory*,EEQUIP_LOCATIONS>>>>
              *)(this + 0x18),*(_Rb_tree_node **)(this + 0x28));
  *(undefined8 *)(this + 0x28) = 0;
  *(undefined8 *)(this + 0x40) = 0;
  *(CCombineMenu **)(this + 0x30) = this + 0x20;
  *(CCombineMenu **)(this + 0x38) = this + 0x20;
  setPlayer(this,(CCharacter *)0x0);
  if (*(long **)(this + 200) != (long *)0x0) {
    (**(code **)(**(long **)(this + 200) + 8))();
    *(undefined8 *)(this + 200) = 0;
  }
  if (*(long **)(this + 0xe0) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0xe0) + 8))();
    *(undefined8 *)(this + 0xe0) = 0;
  }
                    /* try { // try from 00ad484c to 00ad4850 has its CatchHandler @ 00ad48a1 */
  std::
  _Rb_tree<CEquipment*,std::pair<CEquipment*const,std::pair<CInventory*,EEQUIP_LOCATIONS>>,std::_Select1st<std::pair<CEquipment*const,std::pair<CInventory*,EEQUIP_LOCATIONS>>>,std::less<CEquipment*>,std::allocator<std::pair<CEquipment*const,std::pair<CInventory*,EEQUIP_LOCATIONS>>>>
  ::_M_erase((_Rb_tree<CEquipment*,std::pair<CEquipment*const,std::pair<CInventory*,EEQUIP_LOCATIONS>>,std::_Select1st<std::pair<CEquipment*const,std::pair<CInventory*,EEQUIP_LOCATIONS>>>,std::less<CEquipment*>,std::allocator<std::pair<CEquipment*const,std::pair<CInventory*,EEQUIP_LOCATIONS>>>>
              *)(this + 0x18),*(_Rb_tree_node **)(this + 0x28));
  *(undefined ***)(this + 0x10) = &PTR__iInventoryListener_00fce450;
  *(undefined ***)this = &PTR__CSubMenu_00fe64b0;
  CRunicCore::~CRunicCore((CRunicCore *)this);
  return;
}

/* address=00ad48b0
   symbol=CCombineMenu::~CCombineMenu */

/* non-virtual thunk to CCombineMenu::~CCombineMenu() */

void __thiscall CCombineMenu::~CCombineMenu(CCombineMenu *this)

{
  ~CCombineMenu(this + -0x10);
  return;
}

/* address=00ad48c0
   symbol=CCombineMenu::~CCombineMenu */

/* non-virtual thunk to CCombineMenu::~CCombineMenu() */

void __thiscall CCombineMenu::~CCombineMenu(CCombineMenu *this)

{
  ~CCombineMenu(this + -0x10);
  return;
}

/* address=00ad48d0
   symbol=CCombineMenu::~CCombineMenu */

/* CCombineMenu::~CCombineMenu() */

void __thiscall CCombineMenu::~CCombineMenu(CCombineMenu *this)

{
  ~CCombineMenu(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}

/* address=00ad48f0
   symbol=CCombineMenu::returnItemsToCorrectLocation */

/* CCombineMenu::returnItemsToCorrectLocation(CEquipment*) */

void CCombineMenu::returnItemsToCorrectLocation(CEquipment *param_1)

{
  _Rb_tree_node_base *p_Var1;
  int iVar2;
  _Rb_tree_node_base *p_Var3;
  _Rb_tree_node_base *p_Var4;
  char cVar5;
  long lVar6;
  void *pvVar7;
  CPositionableObject *this;
  Vector3 *pVVar8;
  CItem *in_RSI;
  CLevel *pCVar9;
  _Rb_tree_node_base *p_Var10;
  CInventory *this_00;
  undefined8 local_68 [2];
  undefined8 local_58 [2];
  undefined8 local_48 [3];

  if (in_RSI == (CItem *)0x0) {
    return;
  }
  this = *(CPositionableObject **)(param_1 + 0x90);
  this_00 = (CInventory *)0x0;
  if (this != (CPositionableObject *)0x0) {
    this_00 = *(CInventory **)(this + 0x490);
  }
  p_Var1 = (_Rb_tree_node_base *)(param_1 + 0x20);
  p_Var10 = *(_Rb_tree_node_base **)(param_1 + 0x28);
  p_Var4 = p_Var1;
  while (p_Var3 = p_Var10, p_Var3 != (_Rb_tree_node_base *)0x0) {
    if (*(CItem **)(p_Var3 + 0x20) < in_RSI) {
      p_Var10 = *(_Rb_tree_node_base **)(p_Var3 + 0x18);
    }
    else {
      p_Var10 = *(_Rb_tree_node_base **)(p_Var3 + 0x10);
      p_Var4 = p_Var3;
    }
  }
  p_Var10 = p_Var1;
  if ((p_Var1 == p_Var4) || (in_RSI < *(CItem **)(p_Var4 + 0x20))) {
LAB_00ad49d3:
    if (((this != (CPositionableObject *)0x0) && (this_00 != (CInventory *)0x0)) &&
       ((cVar5 = CInventory::isEquipmentInInventory(this_00,(CEquipment *)in_RSI), cVar5 == '\0' &&
        (lVar6 = CInventory::pickupEquipment(this_00,(CEquipment *)in_RSI,true), lVar6 == 0)))) {
      local_68[0] = CPositionableObject::getPosition(*(CPositionableObject **)(param_1 + 0x90),true)
      ;
      pCVar9 = (CLevel *)0x0;
      if (*(long *)(*(long *)(param_1 + 0x90) + 0x68) != 0) {
        pCVar9 = *(CLevel **)(*(long *)(*(long *)(param_1 + 0x90) + 0x68) + 0x18);
      }
      CLevel::addItem(pCVar9,in_RSI,(Vector3 *)local_68,true);
      (**(code **)(*(long *)in_RSI + 0x360))();
    }
    if (p_Var1 == p_Var10) {
      return;
    }
  }
  else {
    this_00 = *(CInventory **)(p_Var4 + 0x28);
    iVar2 = *(int *)(p_Var4 + 0x30);
    p_Var10 = p_Var4;
    if (this_00 == (CInventory *)0x0) {
      local_48[0] = CPositionableObject::getPosition(this,true);
      pCVar9 = (CLevel *)0x0;
      if (*(long *)(*(long *)(param_1 + 0x90) + 0x68) != 0) {
        pCVar9 = *(CLevel **)(*(long *)(*(long *)(param_1 + 0x90) + 0x68) + 0x18);
      }
      pVVar8 = (Vector3 *)local_48;
    }
    else {
      if ((((-1 < iVar2) && (iVar2 < 0x13)) &&
          (lVar6 = CInventory::getEquipmentEquippedAt(this_00,iVar2), lVar6 == 0)) &&
         (cVar5 = CInventory::equipEquipmentIntoSpecificLocation(this_00), cVar5 == '\x01')) {
        this = *(CPositionableObject **)(param_1 + 0x90);
        goto LAB_00ad49d3;
      }
      lVar6 = CInventory::pickupEquipment(this_00,(CEquipment *)in_RSI,true);
      if (lVar6 != 0) goto LAB_00ad49a5;
      local_58[0] = CPositionableObject::getPosition(*(CPositionableObject **)(param_1 + 0x90),true)
      ;
      pCVar9 = (CLevel *)0x0;
      if (*(long *)(*(long *)(param_1 + 0x90) + 0x68) != 0) {
        pCVar9 = *(CLevel **)(*(long *)(*(long *)(param_1 + 0x90) + 0x68) + 0x18);
      }
      pVVar8 = (Vector3 *)local_58;
    }
    CLevel::addItem(pCVar9,in_RSI,pVVar8,true);
    (**(code **)(*(long *)in_RSI + 0x360))();
  }
LAB_00ad49a5:
  pvVar7 = (void *)std::_Rb_tree_rebalance_for_erase(p_Var10,p_Var1);
  operator_delete(pvVar7);
  *(long *)(param_1 + 0x40) = *(long *)(param_1 + 0x40) + -1;
  return;
}

/* address=00ad4b80
   symbol=CCombineMenu::equipmentUsed */

/* non-virtual thunk to CCombineMenu::equipmentUsed(CEquipment*) */

void __thiscall CCombineMenu::equipmentUsed(CCombineMenu *this,CEquipment *param_1)

{
  equipmentUsed((CEquipment *)(this + -0x10));
  return;
}

/* address=00ad4b90
   symbol=CCombineMenu::equipmentUsed */

/* CCombineMenu::equipmentUsed(CEquipment*) */

void CCombineMenu::equipmentUsed(CEquipment *param_1)

{
  if (g_bDontTrackItemEquipAndUnEquip == '\0') {
    returnItemsToCorrectLocation(param_1);
  }
                    /* WARNING: Could not recover jumptable at 0x00ad4bad. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)param_1 + 0x48))(param_1);
  return;
}

/* address=00ad4bb0
   symbol=CCombineMenu::handle_CloseButton */

/* CCombineMenu::handle_CloseButton(CEGUI::EventArgs const&) */

undefined8 __thiscall CCombineMenu::handle_CloseButton(CCombineMenu *this,EventArgs *param_1)

{
  long lVar1;

  if (*(int *)(param_1 + 0x28) != 0) {
    return 1;
  }
  this[0x9a] = (CCombineMenu)0x1;
  CCharacter::setTarget(*(CCharacter **)(*(long *)(this + 0xa8) + 0x38),(CCharacter *)0x0);
  lVar1 = *(long *)(*(long *)(this + 0xa8) + 0x1920);
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
  CGameUI::closeRight(*(CGameUI **)(this + 0xa8));
  return 1;
}

/* address=00ad4f10
   symbol=CCombineMenu::update */

/* WARNING: Removing unreachable block (ram,0x00ad529a) */
/* WARNING: Removing unreachable block (ram,0x00ad52a5) */
/* CCombineMenu::update(float) */

void __thiscall CCombineMenu::update(CCombineMenu *this,float param_1)

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

  CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0xa0),KSETTINGS_RES_WIDTH);
  CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0xa0),KSETTINGS_RES_HEIGHT);
  if (this[0x98] == (CCombineMenu)0x0) {
    *(undefined8 *)(this + 400) = 0;
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x60),0));
    CEGUI::Window::setVisible(SUB81(*(undefined8 *)(this + 0x68),0));
    if ((this[0x98] == (CCombineMenu)0x0) && (this[0x99] != (CCombineMenu)0x0)) {
      return;
    }
  }
  if (*(CGenericModel **)(this + 200) != (CGenericModel *)0x0) {
    CGenericModel::updateAnimation(*(CGenericModel **)(this + 200),param_1,false);
    Ogre::Entity::_updateAnimation();
    plVar6 = *(long **)(*(long *)(this + 200) + 0x130);
    pcVar4 = *(code **)(*plVar6 + 0x1b0);
                    /* try { // try from 00ad4fd3 to 00ad4fd7 has its CatchHandler @ 00ad52c9 */
    std::string::string((string *)&local_48,"tag_dropdowntop",local_39);
                    /* try { // try from 00ad4fde to 00ad4fe0 has its CatchHandler @ 00ad52d2 */
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
    uVar9 = CPositionableObject::getPosition(*(CPositionableObject **)(this + 200),false);
    pfVar7 = (float *)(**(code **)(*plVar6 + 0x200))(plVar6);
    fVar2 = pfVar7[1];
    CGameUI::scaledY(*(CGameUI **)(this + 0xa8),*pfVar7 + (float)uVar9);
    CGameUI::scaledY(*(CGameUI **)(this + 0xa8),fVar2 + (float)((ulong)uVar9 >> 0x20));
                    /* try { // try from 00ad50d1 to 00ad50d5 has its CatchHandler @ 00ad52c4 */
    CEGUI::Window::setPosition(*(UVector2 **)(this + 0x58));
  }
  if ((this[0x98] == (CCombineMenu)0x0) && (this[0x99] == (CCombineMenu)0x0)) {
                    /* try { // try from 00ad517b to 00ad5194 has its CatchHandler @ 00ad52b0 */
    std::string::string((string *)local_58,"CLOSE",&local_3a);
    cVar5 = CGenericModel::animationPlaying(*(CGenericModel **)(this + 200),(string *)local_58);
    bVar8 = false;
    if (cVar5 == '\0') {
                    /* try { // try from 00ad51fd to 00ad5216 has its CatchHandler @ 00ad52b0 */
      std::string::string(local_68,"CLOSE",&local_3b);
      cVar5 = CGenericModel::animationQueued(*(CGenericModel **)(this + 200),local_68);
      bVar8 = cVar5 == '\0';
                    /* try { // try from 00ad5220 to 00ad5224 has its CatchHandler @ 00ad5282 */
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
      (**(code **)(**(long **)(this + 200) + 0x50))(*(long **)(this + 200),0);
      CEGUI::Window::removeChildWindow(*(Window **)(this + 0x48));
      this[0x99] = (CCombineMenu)0x1;
    }
  }
  return;
}

/* address=00ad52e0
   symbol=CCombineMenu::setOpen */

/* WARNING: Removing unreachable block (ram,0x00ad5722) */
/* WARNING: Removing unreachable block (ram,0x00ad5732) */
/* WARNING: Removing unreachable block (ram,0x00ad5702) */
/* CCombineMenu::setOpen(bool) */

void __thiscall CCombineMenu::setOpen(CCombineMenu *this,bool param_1)

{
  int *piVar1;
  int iVar2;
  char cVar3;
  long lVar4;
  CEquipment *pCVar5;
  CCombineMenu *pCVar6;
  long local_78 [2];
  long local_68 [2];
  string local_58 [16];
  string local_48 [16];
  long local_38;
  allocator local_2d;
  allocator local_2c;
  allocator local_2b;
  allocator local_2a;
  allocator local_29 [9];

  if (this[0x98] == (CCombineMenu)0x0) {
    if (!param_1) {
      this[0x98] = (CCombineMenu)0x0;
      return;
    }
    std::
    _Rb_tree<CEquipment*,std::pair<CEquipment*const,std::pair<CInventory*,EEQUIP_LOCATIONS>>,std::_Select1st<std::pair<CEquipment*const,std::pair<CInventory*,EEQUIP_LOCATIONS>>>,std::less<CEquipment*>,std::allocator<std::pair<CEquipment*const,std::pair<CInventory*,EEQUIP_LOCATIONS>>>>
    ::_M_erase((_Rb_tree<CEquipment*,std::pair<CEquipment*const,std::pair<CInventory*,EEQUIP_LOCATIONS>>,std::_Select1st<std::pair<CEquipment*const,std::pair<CInventory*,EEQUIP_LOCATIONS>>>,std::less<CEquipment*>,std::allocator<std::pair<CEquipment*const,std::pair<CInventory*,EEQUIP_LOCATIONS>>>>
                *)(this + 0x18),*(_Rb_tree_node **)(this + 0x28));
    *(undefined8 *)(this + 0x28) = 0;
    *(undefined8 *)(this + 0x40) = 0;
    *(CCombineMenu **)(this + 0x30) = this + 0x20;
    *(CCombineMenu **)(this + 0x38) = this + 0x20;
    CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0xa0),KSETTINGS_RES_WIDTH);
    CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0xa0),KSETTINGS_RES_HEIGHT);
    CSoundBank::playSample(*(CSoundBank **)(this + 0xe0),0x16,(SceneNode *)0x0,0.0,0.0,false);
    (**(code **)(**(long **)(this + 200) + 0x50))(*(long **)(this + 200),1);
                    /* try { // try from 00ad544c to 00ad5450 has its CatchHandler @ 00ad56fe */
    std::string::string((string *)&local_38,"CLOSE",local_29);
                    /* try { // try from 00ad545b to 00ad545f has its CatchHandler @ 00ad56d9 */
    cVar3 = CGenericModel::animationPlaying(*(CGenericModel **)(this + 200),(string *)&local_38);
    if ((allocator *)(local_38 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_38 + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_38 + -0x18));
      }
    }
    if (cVar3 == '\0') {
                    /* try { // try from 00ad561a to 00ad561e has its CatchHandler @ 00ad5730 */
      std::string::string(local_58,"OPEN",&local_2b);
                    /* try { // try from 00ad563b to 00ad563f has its CatchHandler @ 00ad5716 */
      CGenericModel::playAnimation
                (*(CGenericModel **)(this + 200),local_58,false,DAT_00fa4824,DAT_00fa8760);
                    /* try { // try from 00ad5643 to 00ad5647 has its CatchHandler @ 00ad5730 */
      std::string::~string(local_58);
    }
    else {
                    /* try { // try from 00ad5490 to 00ad5494 has its CatchHandler @ 00ad5714 */
      std::string::string(local_48,"OPEN",&local_2a);
                    /* try { // try from 00ad54b9 to 00ad54bd has its CatchHandler @ 00ad5712 */
      CGenericModel::blendAnimation
                (*(CGenericModel **)(this + 200),local_48,false,DAT_00fa480c,DAT_00fa4824,
                 DAT_00fa8760);
                    /* try { // try from 00ad54c1 to 00ad54c5 has its CatchHandler @ 00ad5714 */
      std::string::~string(local_48);
    }
                    /* try { // try from 00ad54d8 to 00ad54dc has its CatchHandler @ 00ad570f */
    std::string::string((string *)local_68,"IDLE",&local_2c);
                    /* try { // try from 00ad54fc to 00ad5500 has its CatchHandler @ 00ad570d */
    CGenericModel::queueBlendAnimation
              (*(CGenericModel **)(this + 200),(string *)local_68,true,DAT_00fa480c,DAT_00fa47fc);
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
    CEGUI::Window::addChildWindow(*(Window **)(this + 0x48));
    CEGUI::Window::moveToBack();
    CGameUI::queueTip(*(CGameUI **)(this + 0xa8),0xe);
  }
  else if (!param_1) {
    lVar4 = *(long *)(this + 0x90);
    if (lVar4 != 0) {
      pCVar6 = this;
      while( true ) {
        pCVar5 = (CEquipment *)
                 CInventory::getEquipmentInSlot
                           (*(CInventory **)(lVar4 + 0x490),*(uint *)(pCVar6 + 0xe8));
        if (pCVar5 != (CEquipment *)0x0) {
          g_bDontTrackItemEquipAndUnEquip = 1;
          CInventory::removeEquipment(*(CInventory **)(*(long *)(this + 0x90) + 0x490),pCVar5);
          returnItemsToCorrectLocation((CEquipment *)this);
          g_bDontTrackItemEquipAndUnEquip = 0;
        }
        pCVar6 = pCVar6 + 4;
        if (pCVar6 == this + 0x10) break;
        lVar4 = *(long *)(this + 0x90);
      }
    }
    std::
    _Rb_tree<CEquipment*,std::pair<CEquipment*const,std::pair<CInventory*,EEQUIP_LOCATIONS>>,std::_Select1st<std::pair<CEquipment*const,std::pair<CInventory*,EEQUIP_LOCATIONS>>>,std::less<CEquipment*>,std::allocator<std::pair<CEquipment*const,std::pair<CInventory*,EEQUIP_LOCATIONS>>>>
    ::_M_erase((_Rb_tree<CEquipment*,std::pair<CEquipment*const,std::pair<CInventory*,EEQUIP_LOCATIONS>>,std::_Select1st<std::pair<CEquipment*const,std::pair<CInventory*,EEQUIP_LOCATIONS>>>,std::less<CEquipment*>,std::allocator<std::pair<CEquipment*const,std::pair<CInventory*,EEQUIP_LOCATIONS>>>>
                *)(this + 0x18),*(_Rb_tree_node **)(this + 0x28));
    *(CCombineMenu **)(this + 0x30) = this + 0x20;
    *(undefined8 *)(this + 0x28) = 0;
    *(CCombineMenu **)(this + 0x38) = this + 0x20;
    *(undefined8 *)(this + 0x40) = 0;
    CSoundBank::playSample(*(CSoundBank **)(this + 0xe0),0x42,(SceneNode *)0x0,0.0,0.0,false);
                    /* try { // try from 00ad55ae to 00ad55b2 has its CatchHandler @ 00ad56f9 */
    std::string::string((string *)local_78,"CLOSE",&local_2d);
                    /* try { // try from 00ad55d7 to 00ad55db has its CatchHandler @ 00ad56ec */
    CGenericModel::blendAnimation
              (*(CGenericModel **)(this + 200),(string *)local_78,false,DAT_00fa480c,DAT_00fa4824,
               DAT_00fa8760);
    if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_78[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
      }
    }
    this[0x99] = (CCombineMenu)0x0;
    this[0x98] = (CCombineMenu)0x0;
    return;
  }
  this[0x98] = (CCombineMenu)param_1;
  (**(code **)(*(long *)this + 0x48))(this);
  return;
}

/* address=00ad6470
   symbol=CCombineMenu::performInteraction */

/* WARNING: Removing unreachable block (ram,0x00ad751f) */
/* WARNING: Removing unreachable block (ram,0x00ad7270) */
/* WARNING: Removing unreachable block (ram,0x00ad7444) */
/* WARNING: Removing unreachable block (ram,0x00ad7366) */
/* WARNING: Removing unreachable block (ram,0x00ad7550) */
/* WARNING: Removing unreachable block (ram,0x00ad7219) */
/* WARNING: Removing unreachable block (ram,0x00ad7224) */
/* WARNING: Removing unreachable block (ram,0x00ad730b) */
/* CCombineMenu::performInteraction() */

void __thiscall CCombineMenu::performInteraction(CCombineMenu *this)

{
  int *piVar1;
  wstring_conflict *pwVar2;
  size_t __n;
  CCharacter *pCVar3;
  bool bVar4;
  char cVar5;
  uint uVar6;
  long lVar7;
  CBaseUnit *pCVar8;
  long lVar9;
  long lVar10;
  long lVar11;
  ulong uVar12;
  CEquipment *pCVar13;
  CItem *pCVar14;
  CSpawnClass *this_00;
  undefined8 *puVar15;
  char *pcVar16;
  CUnitResourceList *pCVar17;
  CDataGroup *pCVar18;
  long *plVar19;
  uint uVar20;
  CCombineMenu *pCVar21;
  long lVar22;
  CLevel *this_01;
  uint uVar23;
  long *plVar24;
  uint uVar25;
  int iVar26;
  int iVar27;
  long lVar28;
  float fVar29;
  long *local_180;
  uint local_16c;
  uint local_158;
  uint local_154;
  long *local_150;
  long local_148;
  uint local_13c;
  char *local_118;
  undefined4 local_110;
  uint local_10c;
  undefined4 local_108;
  undefined8 *local_f8;
  uint local_f0;
  uint local_ec;
  undefined4 local_e8;
  undefined8 local_d8;
  float local_d0;
  long local_c8 [2];
  long local_b8 [2];
  long local_a8 [2];
  long local_98 [2];
  long local_88 [2];
  long local_78 [2];
  long local_68 [2];
  undefined4 *local_58 [3];
  allocator local_3f;
  allocator local_3e;
  allocator local_3d;
  allocator local_3c;
  allocator local_3b;
  allocator local_3a;
  allocator local_39 [9];

  local_58[0] = &DAT_01424558;
                    /* try { // try from 00ad6490 to 00ad64a3 has its CatchHandler @ 00ad7179 */
  lVar7 = CRecipes::getSingleton();
  iVar27 = *(int *)(lVar7 + 0x20);
  lVar7 = CRecipes::getSingleton();
  if (iVar27 < 1) {
    local_150 = (long *)0x0;
  }
  else {
    local_148 = 0;
    local_150 = (long *)0x0;
    local_154 = 0;
    local_13c = 0;
    local_158 = 0;
    do {
      if (local_158 < *(uint *)(lVar7 + 0x24)) {
        plVar24 = (long *)(local_148 + *(long *)(lVar7 + 0x18));
      }
      else {
        plVar24 = *(long **)(lVar7 + 0x18);
      }
      lVar22 = *plVar24;
      uVar20 = *(uint *)(lVar22 + 0x10);
      if (uVar20 != 0) {
        lVar28 = 0;
        uVar25 = 0;
        do {
          if (uVar25 < *(uint *)(lVar22 + 0x14)) {
            plVar24 = *(long **)(lVar22 + 8);
            local_16c = (*(int **)((long)plVar24 + lVar28))[4];
            if (**(int **)((long)plVar24 + lVar28) != 0x16) goto LAB_00ad654b;
LAB_00ad6768:
            if (uVar25 < *(uint *)(lVar22 + 0x14)) {
              plVar24 = (long *)(lVar28 + *(long *)(lVar22 + 8));
            }
            lVar9 = *plVar24;
                    /* try { // try from 00ad6790 to 00ad6794 has its CatchHandler @ 00ad735c */
            std::wstring::wstring((wstring_conflict *)local_68,L"ITEMS",local_39);
                    /* try { // try from 00ad679d to 00ad67b4 has its CatchHandler @ 00ad7347 */
            pCVar17 = (CUnitResourceList *)CResourceManager::getMasterResourceList();
            pCVar18 = (CDataGroup *)
                      CUnitResourceList::getDataGroupByObjectName
                                (pCVar17,(wstring_conflict *)local_68,
                                 (wstring_conflict *)(lVar9 + 8));
            if ((allocator *)(local_68[0] + -0x18) !=
                (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar1 = (int *)(local_68[0] + -8);
              iVar26 = *piVar1;
              *piVar1 = *piVar1 + -1;
              UNLOCK();
              if (iVar26 < 1) {
                std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
              }
            }
            if (pCVar18 != (CDataGroup *)0x0) {
                    /* try { // try from 00ad67ef to 00ad67f3 has its CatchHandler @ 00ad7316 */
              std::wstring::wstring((wstring_conflict *)local_78,L"UNIT_GUID",&local_3a);
                    /* try { // try from 00ad6807 to 00ad680b has its CatchHandler @ 00ad72f6 */
              lVar9 = CResourceManager::getUnitGuidByDataGroup
                                (*(CResourceManager **)(this + 0xd0),pCVar18,
                                 (wstring_conflict *)local_78);
              if ((allocator *)(local_78[0] + -0x18) !=
                  (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar1 = (int *)(local_78[0] + -8);
                iVar26 = *piVar1;
                *piVar1 = *piVar1 + -1;
                UNLOCK();
                if (iVar26 < 1) {
                  std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
                }
              }
              pCVar21 = this;
              do {
                    /* try { // try from 00ad684d to 00ad6851 has its CatchHandler @ 00ad7361 */
                lVar10 = CInventory::getEquipmentInSlot
                                   (*(CInventory **)(*(long *)(this + 0x90) + 0x490),
                                    *(uint *)(pCVar21 + 0xe8));
                if (lVar10 != 0) {
                    /* try { // try from 00ad6874 to 00ad6899 has its CatchHandler @ 00ad7424 */
                  std::wstring::wstring((wstring_conflict *)local_88,L"UNIT_GUID",&local_3b);
                  lVar11 = CResourceManager::getUnitGuidByDataGroup
                                     (*(CResourceManager **)(this + 0xd0),
                                      *(CDataGroup **)(lVar10 + 0x1b0),(wstring_conflict *)local_88)
                  ;
                  if ((allocator *)(local_88[0] + -0x18) !=
                      (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                    LOCK();
                    piVar1 = (int *)(local_88[0] + -8);
                    iVar26 = *piVar1;
                    *piVar1 = *piVar1 + -1;
                    UNLOCK();
                    if (iVar26 < 1) {
                      std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
                    }
                  }
                  if (lVar9 == lVar11) {
                    local_16c = local_16c - *(int *)(lVar10 + 0x238);
                  }
                }
                pCVar21 = pCVar21 + 4;
              } while (pCVar21 != this + 0x10);
            }
          }
          else {
            plVar24 = *(long **)(lVar22 + 8);
            local_16c = ((int *)*plVar24)[4];
            if (*(int *)*plVar24 == 0x16) goto LAB_00ad6768;
LAB_00ad654b:
            pCVar21 = this;
            do {
                    /* try { // try from 00ad656d to 00ad6715 has its CatchHandler @ 00ad7361 */
              pCVar8 = (CBaseUnit *)
                       CInventory::getEquipmentInSlot
                                 (*(CInventory **)(*(long *)(this + 0x90) + 0x490),
                                  *(uint *)(pCVar21 + 0xe8));
              if (uVar25 < *(uint *)(lVar22 + 0x14)) {
                if (**(int **)(lVar28 + *(long *)(lVar22 + 8)) != 0x87) goto LAB_00ad6592;
LAB_00ad66d6:
                if (pCVar8 != (CBaseUnit *)0x0) {
                  cVar5 = (**(code **)(*(long *)pCVar8 + 0x2b0))(pCVar8);
                  if ((cVar5 == '\0') || (cVar5 = CBaseUnit::ISA(pCVar8,0x36), cVar5 != '\0')) {
LAB_00ad6597:
                    bVar4 = false;
                  }
                  else {
                    cVar5 = CBaseUnit::ISA(pCVar8,0x37);
                    bVar4 = true;
                    if (cVar5 != '\0') goto LAB_00ad6597;
                  }
                  cVar5 = CBaseUnit::ISA(pCVar8);
                  if ((cVar5 != '\0') || (bVar4)) {
                    local_16c = local_16c - *(int *)(pCVar8 + 0x238);
                  }
                }
              }
              else {
                if (*(int *)**(undefined8 **)(lVar22 + 8) == 0x87) goto LAB_00ad66d6;
LAB_00ad6592:
                if (pCVar8 != (CBaseUnit *)0x0) goto LAB_00ad6597;
              }
              pCVar21 = pCVar21 + 4;
            } while (pCVar21 != this + 0x10);
          }
          if (0 < (int)local_16c) {
            local_180 = local_150;
            goto LAB_00ad668b;
          }
          uVar25 = uVar25 + 1;
          lVar28 = lVar28 + 8;
        } while (uVar25 < uVar20);
      }
      local_180 = local_150;
      uVar20 = local_154;
      if (local_154 <= local_13c) {
        if (local_150 == (long *)0x0) {
                    /* try { // try from 00ad6914 to 00ad6bf3 has its CatchHandler @ 00ad7361 */
          local_180 = operator_new__(0x50);
          uVar20 = 10;
        }
        else {
          uVar20 = local_154 + 10;
          local_180 = operator_new__((ulong)uVar20 << 3);
          if (local_154 != 0) {
            lVar28 = 0;
            do {
              *(undefined8 *)((long)local_180 + lVar28) = *(undefined8 *)((long)local_150 + lVar28);
              lVar28 = lVar28 + 8;
            } while (lVar28 != (ulong)(local_154 - 1) * 8 + 8);
          }
          operator_delete__(local_150);
        }
      }
      local_180[local_13c] = lVar22;
      local_13c = local_13c + 1;
      local_154 = uVar20;
LAB_00ad668b:
      local_158 = local_158 + 1;
      local_148 = local_148 + 8;
      local_150 = local_180;
    } while ((int)local_158 < iVar27);
    if (local_13c != 0) {
      lVar28 = 0;
      uVar25 = 0;
      uVar20 = 0;
      lVar7 = *local_180;
      lVar22 = lVar7;
      do {
        uVar12 = 0;
        uVar23 = 0;
        plVar24 = (long *)((long)local_180 + lVar28);
        while( true ) {
          lVar9 = lVar7;
          if (uVar25 < local_154) {
            lVar9 = *plVar24;
          }
          uVar6 = (uint)uVar12;
          if (*(uint *)(lVar9 + 0x10) <= uVar6) break;
          lVar9 = lVar7;
          if (uVar25 < local_154) {
            lVar9 = *plVar24;
          }
          if (uVar6 < *(uint *)(lVar9 + 0x14)) {
            plVar19 = (long *)(uVar12 * 8 + *(long *)(lVar9 + 8));
          }
          else {
            plVar19 = *(long **)(lVar9 + 8);
          }
          uVar12 = (ulong)(uVar6 + 1);
          uVar23 = uVar23 + *(int *)(*plVar19 + 0x10);
        }
        if (uVar20 < uVar23) {
          if (uVar25 < local_154) {
            uVar20 = *(uint *)(*plVar24 + 0x10);
            lVar22 = *plVar24;
          }
          else {
            uVar20 = *(uint *)(lVar7 + 0x10);
            lVar22 = lVar7;
          }
        }
        uVar25 = uVar25 + 1;
        lVar28 = lVar28 + 8;
      } while (uVar25 < local_13c);
      if (*(int *)(lVar22 + 0x10) != 0) {
        local_16c = 0;
        do {
          while( true ) {
            if (local_16c < *(uint *)(lVar22 + 0x14)) {
              plVar24 = *(long **)(lVar22 + 8);
              iVar27 = *(int *)(plVar24[local_16c] + 0x10);
              iVar26 = *(int *)plVar24[local_16c];
            }
            else {
              plVar24 = *(long **)(lVar22 + 8);
              iVar27 = *(int *)(*plVar24 + 0x10);
              iVar26 = *(int *)*plVar24;
            }
            if (iVar26 == 0x16) break;
            pCVar21 = this;
            do {
              if (0 < iVar27) {
                pCVar13 = (CEquipment *)
                          CInventory::getEquipmentInSlot
                                    (*(CInventory **)(*(long *)(this + 0x90) + 0x490),
                                     *(uint *)(pCVar21 + 0xe8));
                if (*(uint *)(lVar22 + 0x14) <= local_16c) {
                  if (*(int *)**(undefined8 **)(lVar22 + 8) == 0x87) goto LAB_00ad6dd1;
LAB_00ad6a50:
                  if (pCVar13 == (CEquipment *)0x0) goto joined_r0x00ad6ae0;
                  goto LAB_00ad6a55;
                }
                if (**(int **)((ulong)local_16c * 8 + *(long *)(lVar22 + 8)) != 0x87)
                goto LAB_00ad6a50;
LAB_00ad6dd1:
                if (pCVar13 == (CEquipment *)0x0) goto joined_r0x00ad6ae0;
                    /* try { // try from 00ad6de1 to 00ad6e73 has its CatchHandler @ 00ad7361 */
                cVar5 = (**(code **)(*(long *)pCVar13 + 0x2b0))(pCVar13);
                if ((cVar5 == '\0') ||
                   (cVar5 = CBaseUnit::ISA((CBaseUnit *)pCVar13,0x36), cVar5 != '\0')) {
LAB_00ad6a55:
                  bVar4 = false;
                }
                else {
                  cVar5 = CBaseUnit::ISA((CBaseUnit *)pCVar13,0x37);
                  bVar4 = true;
                  if (cVar5 != '\0') goto LAB_00ad6a55;
                }
                if (local_16c < *(uint *)(lVar22 + 0x14)) {
                  puVar15 = (undefined8 *)((ulong)local_16c * 8 + *(long *)(lVar22 + 8));
                }
                else {
                  puVar15 = *(undefined8 **)(lVar22 + 8);
                }
                cVar5 = CBaseUnit::ISA((CBaseUnit *)pCVar13,*(undefined4 *)*puVar15);
                if (cVar5 == '\0') {
                  if (!bVar4) goto joined_r0x00ad6ae0;
                  iVar26 = *(int *)(pCVar13 + 0x238);
                  if (1 < iVar26) goto LAB_00ad6a8f;
LAB_00ad6e42:
                  iVar27 = iVar27 + -1;
                }
                else {
                  iVar26 = *(int *)(pCVar13 + 0x238);
                  if (iVar26 < 2) goto LAB_00ad6e42;
LAB_00ad6a8f:
                  if (iVar27 <= iVar26) {
                    iVar26 = iVar27;
                  }
                  (**(code **)(*(long *)pCVar13 + 0x338))(pCVar13,-iVar26);
                  iVar27 = iVar27 - iVar26;
                  if (0 < *(int *)(pCVar13 + 0x238)) goto joined_r0x00ad6ae0;
                }
                CInventory::removeEquipment
                          (*(CInventory **)(*(long *)(this + 0x90) + 0x490),pCVar13);
                itemUpdatedInMenu(this,pCVar13,false);
                (**(code **)(*(long *)pCVar13 + 8))(pCVar13);
              }
joined_r0x00ad6ae0:
              pCVar21 = pCVar21 + 4;
            } while (pCVar21 != this + 0x10);
LAB_00ad6ae2:
            local_16c = local_16c + 1;
            if (*(uint *)(lVar22 + 0x10) <= local_16c) goto LAB_00ad6af4;
          }
          if (local_16c < *(uint *)(lVar22 + 0x14)) {
            plVar24 = (long *)((ulong)local_16c * 8 + *(long *)(lVar22 + 8));
          }
          lVar7 = *plVar24;
                    /* try { // try from 00ad6ed8 to 00ad6edc has its CatchHandler @ 00ad72c8 */
          std::wstring::wstring((wstring_conflict *)local_98,L"ITEMS",&local_3c);
                    /* try { // try from 00ad6ee5 to 00ad6efc has its CatchHandler @ 00ad72b3 */
          pCVar17 = (CUnitResourceList *)CResourceManager::getMasterResourceList();
          pCVar18 = (CDataGroup *)
                    CUnitResourceList::getDataGroupByObjectName
                              (pCVar17,(wstring_conflict *)local_98,(wstring_conflict *)(lVar7 + 8))
          ;
          if ((allocator *)(local_98[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_98[0] + -8);
            iVar26 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar26 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
            }
          }
          if (pCVar18 == (CDataGroup *)0x0) goto LAB_00ad6ae2;
                    /* try { // try from 00ad6f37 to 00ad6f3b has its CatchHandler @ 00ad727b */
          std::wstring::wstring((wstring_conflict *)local_a8,L"UNIT_GUID",&local_3d);
                    /* try { // try from 00ad6f4f to 00ad6f53 has its CatchHandler @ 00ad725e */
          lVar7 = CResourceManager::getUnitGuidByDataGroup
                            (*(CResourceManager **)(this + 0xd0),pCVar18,
                             (wstring_conflict *)local_a8);
          if ((allocator *)(local_a8[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_a8[0] + -8);
            iVar26 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar26 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
            }
          }
          pCVar21 = this;
          do {
                    /* try { // try from 00ad6f9f to 00ad6fa3 has its CatchHandler @ 00ad7361 */
            if ((0 < iVar27) &&
               (pCVar13 = (CEquipment *)
                          CInventory::getEquipmentInSlot
                                    (*(CInventory **)(*(long *)(this + 0x90) + 0x490),
                                     *(uint *)(pCVar21 + 0xe8)), pCVar13 != (CEquipment *)0x0)) {
                    /* try { // try from 00ad6fc8 to 00ad6fee has its CatchHandler @ 00ad71e9 */
              std::wstring::wstring((wstring_conflict *)local_b8,L"UNIT_GUID",&local_3e);
              lVar28 = CResourceManager::getUnitGuidByDataGroup
                                 (*(CResourceManager **)(this + 0xd0),
                                  *(CDataGroup **)(pCVar13 + 0x1b0),(wstring_conflict *)local_b8);
              if ((allocator *)(local_b8[0] + -0x18) !=
                  (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar1 = (int *)(local_b8[0] + -8);
                iVar26 = *piVar1;
                *piVar1 = *piVar1 + -1;
                UNLOCK();
                if (iVar26 < 1) {
                  std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
                }
              }
              if (lVar7 == lVar28) {
                iVar26 = *(int *)(pCVar13 + 0x238);
                if (iVar26 < 2) {
                  iVar27 = iVar27 + -1;
                }
                else {
                  if (iVar27 <= iVar26) {
                    iVar26 = iVar27;
                  }
                    /* try { // try from 00ad7032 to 00ad7176 has its CatchHandler @ 00ad7361 */
                  (**(code **)(*(long *)pCVar13 + 0x338))(pCVar13,-iVar26);
                  iVar27 = iVar27 - iVar26;
                  if (0 < *(int *)(pCVar13 + 0x238)) goto LAB_00ad7045;
                }
                CInventory::removeEquipment
                          (*(CInventory **)(*(long *)(this + 0x90) + 0x490),pCVar13);
                itemUpdatedInMenu(this,pCVar13,false);
                (**(code **)(*(long *)pCVar13 + 8))(pCVar13);
              }
            }
LAB_00ad7045:
            pCVar21 = pCVar21 + 4;
          } while (pCVar21 != this + 0x10);
          local_16c = local_16c + 1;
        } while (local_16c < *(uint *)(lVar22 + 0x10));
      }
LAB_00ad6af4:
      fVar29 = 0.0;
      CSoundBank::playSample
                (*(CSoundBank **)(this + 0xe0),0x24,*(SceneNode **)(*(long *)(this + 0x90) + 0x58),
                 0.0,0.0,false);
      if (*(CSoundBank **)(*(long *)(this + 0x90) + 0x298) != (CSoundBank *)0x0) {
        fVar29 = DAT_00fa480c;
        CSoundBank::queueGlobalSample
                  (*(CSoundBank **)(*(long *)(this + 0x90) + 0x298),0x3f,0.0,DAT_00fa480c);
      }
      if (*(int *)(lVar22 + 0x28) != 0) {
        pCVar21 = this;
        do {
          pCVar14 = (CItem *)CInventory::getEquipmentInSlot
                                       (*(CInventory **)(*(long *)(this + 0x90) + 0x490),
                                        *(uint *)(pCVar21 + 0xe8));
          if (pCVar14 != (CItem *)0x0) {
            CInventory::removeEquipment
                      (*(CInventory **)(*(long *)(this + 0x90) + 0x490),(CEquipment *)pCVar14);
            lVar7 = CInventory::pickupEquipment
                              (*(CInventory **)(*(long *)(this + 0x90) + 0x490),
                               (CEquipment *)pCVar14,true);
            if (lVar7 == 0) {
                    /* try { // try from 00ad737f to 00ad73e8 has its CatchHandler @ 00ad7361 */
              local_d8 = CPositionableObject::getPosition
                                   (*(CPositionableObject **)(this + 0x90),true);
              this_01 = (CLevel *)0x0;
              if (*(long *)(*(long *)(this + 0x90) + 0x68) != 0) {
                this_01 = *(CLevel **)(*(long *)(*(long *)(this + 0x90) + 0x68) + 0x18);
              }
              local_d0 = fVar29;
              CLevel::addItem(this_01,pCVar14,(Vector3 *)&local_d8,true);
              (**(code **)(*(long *)pCVar14 + 0x360))(pCVar14);
            }
          }
          pCVar21 = pCVar21 + 4;
        } while (pCVar21 != this + 0x10);
        pwVar2 = (wstring_conflict *)**(undefined8 **)(lVar22 + 0x20);
        __n = *(size_t *)(*(wchar_t **)pwVar2 + -6);
        if ((__n == *(size_t *)(::EMPTY_WSTRING + -6)) &&
           (iVar27 = wmemcmp(*(wchar_t **)pwVar2,::EMPTY_WSTRING,__n), iVar27 == 0)) {
          lVar7 = CResourceManager::createEquipment
                            (*(CResourceManager **)(this + 0xd0),*(wchar_t **)(pwVar2 + 8),false,
                             true);
          if (lVar7 != 0) {
            CInventory::pickupEquipment
                      (*(CEquipment **)(*(long *)(this + 0x90) + 0x490),(int)lVar7,
                       SUB41(*(undefined4 *)(this + 0xe8),0));
          }
        }
        else {
          this_00 = (CSpawnClass *)
                    CResourceManager::getSpawnClassByName
                              (*(CResourceManager **)(this + 0xd0),pwVar2);
          if (this_00 == (CSpawnClass *)0x0) {
            if (local_180 != (long *)0x0) {
              operator_delete__(local_180);
            }
            std::wstring::~wstring((wstring_conflict *)local_58);
            return;
          }
          pCVar3 = *(CCharacter **)(this + 0x90);
          local_f8 = (undefined8 *)0x0;
          local_f0 = 0;
          local_ec = 0;
          local_e8 = 2;
          local_118 = (char *)0x0;
          local_110 = 0;
          local_10c = 0;
          local_108 = 2;
                    /* try { // try from 00ad6ca3 to 00ad6ca7 has its CatchHandler @ 00ad752a */
          CSpawnClass::rollSpawnClass
                    (this_00,(TArrayList *)&local_f8,(TArrayList *)&local_118,pCVar3,pCVar3,
                     *(int *)(pCVar3 + 0x100),0xffffffff,0,-1,0,0);
          if (local_f0 != 0) {
            uVar12 = 0;
            while( true ) {
              uVar20 = local_f0;
              if (3 < local_f0) {
                uVar20 = 4;
              }
              uVar25 = (uint)uVar12;
              if (uVar20 <= uVar25) break;
                    /* try { // try from 00ad6d94 to 00ad6d98 has its CatchHandler @ 00ad74d5 */
              std::wstring::wstring((wstring_conflict *)local_c8,L"NAME",&local_3f);
              puVar15 = local_f8;
              if (uVar25 < local_ec) {
                puVar15 = local_f8 + uVar12;
              }
                    /* try { // try from 00ad6ce2 to 00ad6cfd has its CatchHandler @ 00ad745e */
              puVar15 = (undefined8 *)
                        CDataGroup::GetDataValue
                                  ((CDataGroup *)*puVar15,(wstring_conflict *)local_c8,
                                   (wstring_conflict *)&::EMPTY_WSTRING);
              pCVar13 = (CEquipment *)
                        CResourceManager::createEquipment
                                  (*(CResourceManager **)(this + 0xd0),(wchar_t *)*puVar15,false,
                                   true);
              if ((allocator *)(local_c8[0] + -0x18) !=
                  (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar1 = (int *)(local_c8[0] + -8);
                iVar27 = *piVar1;
                *piVar1 = *piVar1 + -1;
                UNLOCK();
                if (iVar27 < 1) {
                  std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
                }
              }
              pcVar16 = local_118;
              if (uVar25 < local_10c) {
                pcVar16 = local_118 + uVar12;
              }
              if (*pcVar16 != '\0') {
                    /* try { // try from 00ad6d3c to 00ad6d66 has its CatchHandler @ 00ad752a */
                CEquipment::enchant(pCVar13,true);
              }
              CInventory::pickupEquipment
                        (*(CEquipment **)(*(long *)(this + 0x90) + 0x490),(int)pCVar13,
                         SUB41(*(undefined4 *)(this + uVar12 * 4 + 0xe8),0));
              uVar12 = (ulong)(uVar25 + 1);
            }
          }
          if (local_118 != (char *)0x0) {
            operator_delete__(local_118);
            local_118 = (char *)0x0;
          }
          if (local_f8 != (undefined8 *)0x0) {
            operator_delete__(local_f8);
            local_f8 = (undefined8 *)0x0;
          }
        }
        CCharacter::incrementJournalStatistic(*(CCharacter **)(this + 0x90),0x10,1);
      }
      goto LAB_00ad710f;
    }
  }
  CSoundBank::playSample
            (*(CSoundBank **)(this + 0xe0),0x18,*(SceneNode **)(*(long *)(this + 0x90) + 0x58),0.0,
             0.0,false);
LAB_00ad710f:
  if (local_150 != (long *)0x0) {
    operator_delete__(local_150);
  }
  if ((allocator *)(local_58[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = local_58[0] + -2;
    iVar27 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar27 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -6));
    }
  }
  return;
}

/* address=00ad7560
   symbol=CCombineMenu::onClick */

/* CCombineMenu::onClick(ELayoutFunction) */

undefined8 __thiscall CCombineMenu::onClick(CCombineMenu *this,int param_2)

{
  long lVar1;

  if (this[0x98] != (CCombineMenu)0x0) {
    if (param_2 == 8) {
      this[0x9a] = (CCombineMenu)0x1;
      CCharacter::setTarget(*(CCharacter **)(*(long *)(this + 0xa8) + 0x38),(CCharacter *)0x0);
      lVar1 = *(long *)(*(long *)(this + 0xa8) + 0x1920);
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
      CGameUI::closeRight(*(CGameUI **)(this + 0xa8));
    }
    else if (param_2 == 9) {
      performInteraction(this);
    }
  }
  return 1;
}

/* address=00ad7690
   symbol=CCombineMenu::mapEventHandlers */

/* CCombineMenu::mapEventHandlers(CEGUI::Window*) */

void __thiscall CCombineMenu::mapEventHandlers(CCombineMenu *this,Window *param_1)

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
                    /* try { // try from 00ad7756 to 00ad77d3 has its CatchHandler @ 00ad7a3c */
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
                    /* try { // try from 00ad7930 to 00ad79ae has its CatchHandler @ 00ad7a3c */
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
                    /* try { // try from 00ad79bb to 00ad79bf has its CatchHandler @ 00ad79f6 */
    CEGUI::String::~String((String *)local_268);
                    /* try { // try from 00ad79c8 to 00ad79cc has its CatchHandler @ 00ad7a2f */
    CEGUI::String::~String((String *)&local_1b8);
  }
                    /* try { // try from 00ad77e2 to 00ad781e has its CatchHandler @ 00ad7a1d */
  CEGUI::String::~String((String *)&local_108);
  if (bVar11) {
    CEGUI::Window::setWantsMultiClickEvents(SUB81(param_1,0));
    pcVar3 = *(code **)(*(long *)(param_1 + 0x38) + 0x10);
    local_48[0] = operator_new(0x20);
    local_48[0][3] = this;
    *local_48[0] = &PTR__MemberFunctionSlot_00fe6410;
    local_48[0][2] = 0;
    local_48[0][1] = 0x59;
                    /* try { // try from 00ad785e to 00ad7893 has its CatchHandler @ 00ad7a22 */
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
                    /* try { // try from 00ad78c4 to 00ad78c8 has its CatchHandler @ 00ad7a1d */
    CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_48);
  }
  return;
}

/* address=00ad7a50
   symbol=CCombineMenu::createMenus */

/* WARNING: Removing unreachable block (ram,0x00add064) */
/* WARNING: Removing unreachable block (ram,0x00add11e) */
/* WARNING: Removing unreachable block (ram,0x00add5ce) */
/* WARNING: Removing unreachable block (ram,0x00add549) */
/* WARNING: Removing unreachable block (ram,0x00add135) */
/* WARNING: Removing unreachable block (ram,0x00add345) */
/* WARNING: Removing unreachable block (ram,0x00adcf92) */
/* WARNING: Removing unreachable block (ram,0x00add4c5) */
/* WARNING: Removing unreachable block (ram,0x00add875) */
/* WARNING: Removing unreachable block (ram,0x00add6be) */
/* WARNING: Removing unreachable block (ram,0x00add431) */
/* WARNING: Removing unreachable block (ram,0x00adcd49) */
/* WARNING: Removing unreachable block (ram,0x00adcdf8) */
/* WARNING: Removing unreachable block (ram,0x00adcd3e) */
/* WARNING: Removing unreachable block (ram,0x00add41c) */
/* WARNING: Removing unreachable block (ram,0x00add263) */
/* WARNING: Removing unreachable block (ram,0x00add810) */
/* WARNING: Removing unreachable block (ram,0x00add258) */
/* WARNING: Removing unreachable block (ram,0x00add777) */
/* WARNING: Removing unreachable block (ram,0x00adcfff) */
/* WARNING: Removing unreachable block (ram,0x00add6ce) */
/* WARNING: Removing unreachable block (ram,0x00add805) */
/* WARNING: Removing unreachable block (ram,0x00add6e1) */
/* WARNING: Removing unreachable block (ram,0x00adcc39) */
/* WARNING: Removing unreachable block (ram,0x00add19d) */
/* WARNING: Removing unreachable block (ram,0x00add53e) */
/* WARNING: Removing unreachable block (ram,0x00add1a8) */
/* WARNING: Removing unreachable block (ram,0x00add1f5) */
/* CCombineMenu::createMenus() */

void __thiscall CCombineMenu::createMenus(CCombineMenu *this)

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
  uint uVar10;
  undefined8 uVar11;
  long lVar12;
  char *pcVar13;
  char *pcVar14;
  UVector2 *pUVar15;
  CFileSystem *this_00;
  byte *pbVar16;
  undefined8 *puVar17;
  undefined4 *puVar18;
  uint *puVar19;
  float *pfVar20;
  float *pfVar21;
  length_error *plVar22;
  ulong uVar23;
  uint uVar24;
  byte *pbVar25;
  ulong uVar26;
  char *pcVar27;
  char *pcVar28;
  long lVar29;
  CCombineMenu *pCVar30;
  char *pcVar31;
  bool bVar32;
  float fVar33;
  float fVar34;
  undefined4 uVar35;
  undefined8 local_2638;
  ulong local_2630;
  undefined8 local_2628;
  undefined8 local_2620;
  undefined8 local_2618;
  undefined4 local_2610 [32];
  undefined4 *local_2590;
  long local_2588;
  ulong local_2580;
  undefined8 local_2578;
  undefined8 local_2570;
  undefined8 local_2568;
  undefined4 local_2560 [32];
  undefined4 *local_24e0;
  long local_24d8;
  ulong local_24d0;
  undefined8 local_24c8;
  undefined8 local_24c0;
  undefined8 local_24b8;
  uint local_24b0 [32];
  uint *local_2430;
  undefined8 local_2428;
  ulong local_2420;
  undefined8 local_2418;
  undefined8 local_2410;
  undefined8 local_2408;
  undefined4 local_2400 [32];
  undefined4 *local_2380;
  long local_2378;
  ulong local_2370;
  undefined8 local_2368;
  undefined8 local_2360;
  undefined8 local_2358;
  undefined4 local_2350 [32];
  undefined4 *local_22d0;
  long local_22c8;
  ulong local_22c0;
  undefined8 local_22b8;
  undefined8 local_22b0;
  undefined8 local_22a8;
  uint local_22a0 [32];
  uint *local_2220;
  undefined8 local_2218;
  ulong local_2210;
  undefined8 local_2208;
  undefined8 local_2200;
  undefined8 local_21f8;
  uint local_21f0 [10];
  uint local_21c8 [22];
  uint *local_2170;
  String local_2168 [176];
  undefined8 local_20b8;
  ulong local_20b0;
  undefined8 local_20a8;
  undefined8 local_20a0;
  undefined8 local_2098;
  undefined4 local_2090 [32];
  undefined4 *local_2010;
  undefined8 local_2008;
  ulong local_2000;
  undefined8 local_1ff8;
  undefined8 local_1ff0;
  undefined8 local_1fe8;
  uint local_1fe0 [13];
  uint local_1fac [19];
  uint *local_1f60;
  undefined8 local_1f58;
  ulong local_1f50;
  undefined8 local_1f48;
  undefined8 local_1f40;
  undefined8 local_1f38;
  uint local_1f30 [14];
  uint local_1ef8 [18];
  uint *local_1eb0;
  undefined8 local_1ea8;
  ulong local_1ea0;
  undefined8 local_1e98;
  undefined8 local_1e90;
  undefined8 local_1e88;
  uint local_1e80 [12];
  uint local_1e50 [20];
  uint *local_1e00;
  undefined8 local_1df8;
  ulong local_1df0;
  undefined8 local_1de8;
  undefined8 local_1de0;
  undefined8 local_1dd8;
  uint local_1dd0 [18];
  uint local_1d88 [14];
  uint *local_1d50;
  undefined8 local_1d48;
  ulong local_1d40;
  undefined8 local_1d38;
  undefined8 local_1d30;
  undefined8 local_1d28;
  uint local_1d20 [5];
  uint local_1d0c [27];
  uint *local_1ca0;
  undefined8 local_1c98;
  ulong local_1c90;
  undefined8 local_1c88;
  undefined8 local_1c80;
  undefined8 local_1c78;
  undefined4 local_1c70 [32];
  undefined4 *local_1bf0;
  long local_1be8;
  ulong local_1be0;
  undefined8 local_1bd8;
  undefined8 local_1bd0;
  undefined8 local_1bc8;
  undefined4 local_1bc0 [32];
  undefined4 *local_1b40;
  long local_1b38;
  ulong local_1b30;
  undefined8 local_1b28;
  undefined8 local_1b20;
  undefined8 local_1b18;
  uint local_1b10 [32];
  uint *local_1a90;
  long local_1a88;
  ulong local_1a80;
  undefined8 local_1a78;
  undefined8 local_1a70;
  undefined8 local_1a68;
  undefined4 local_1a60 [32];
  undefined4 *local_19e0;
  undefined8 local_19d8;
  ulong local_19d0;
  undefined8 local_19c8;
  undefined8 local_19c0;
  undefined8 local_19b8;
  uint local_19b0 [5];
  uint local_199c [27];
  uint *local_1930;
  undefined8 local_1928;
  ulong local_1920;
  undefined8 local_1918;
  undefined8 local_1910;
  undefined8 local_1908;
  uint local_1900 [11];
  uint local_18d4 [21];
  uint *local_1880;
  undefined8 local_1878;
  ulong local_1870;
  undefined8 local_1868;
  undefined8 local_1860;
  undefined8 local_1858;
  undefined4 local_1850 [32];
  undefined4 *local_17d0;
  long local_17c8;
  ulong local_17c0;
  undefined8 local_17b8;
  undefined8 local_17b0;
  undefined8 local_17a8;
  uint local_17a0 [32];
  uint *local_1720;
  long local_1718;
  ulong local_1710;
  undefined8 local_1708;
  undefined8 local_1700;
  undefined8 local_16f8;
  uint local_16f0 [32];
  uint *local_1670;
  undefined8 local_1668;
  ulong local_1660;
  undefined8 local_1658;
  undefined8 local_1650;
  undefined8 local_1648;
  uint local_1640 [5];
  uint local_162c [27];
  uint *local_15c0;
  undefined8 local_15b8;
  ulong local_15b0;
  undefined8 local_15a8;
  undefined8 local_15a0;
  undefined8 local_1598;
  uint local_1590 [11];
  uint local_1564 [21];
  uint *local_1510;
  undefined8 local_1508;
  ulong local_1500;
  undefined8 local_14f8;
  undefined8 local_14f0;
  undefined8 local_14e8;
  undefined4 local_14e0 [32];
  undefined4 *local_1460;
  String local_1458 [176];
  String local_13a8 [176];
  undefined8 local_12f8;
  ulong local_12f0;
  undefined8 local_12e8;
  undefined8 local_12e0;
  undefined8 local_12d8;
  uint local_12d0 [6];
  uint local_12b8 [26];
  uint *local_1250;
  undefined8 local_1248;
  ulong local_1240;
  undefined8 local_1238;
  undefined8 local_1230;
  undefined8 local_1228;
  uint local_1220 [6];
  uint local_1208 [26];
  uint *local_11a0;
  undefined8 local_1198;
  ulong local_1190;
  undefined8 local_1188;
  undefined8 local_1180;
  undefined8 local_1178;
  uint local_1170 [5];
  uint local_115c [27];
  uint *local_10f0;
  Image local_10e8 [176];
  undefined8 local_1038;
  ulong local_1030;
  undefined8 local_1028;
  undefined8 local_1020;
  undefined8 local_1018;
  uint local_1010 [8];
  uint local_ff0 [24];
  uint *local_f90;
  undefined8 local_f88;
  ulong local_f80;
  undefined8 local_f78;
  undefined8 local_f70;
  undefined8 local_f68;
  undefined4 local_f60 [32];
  undefined4 *local_ee0;
  long local_ed8;
  ulong local_ed0;
  undefined8 local_ec8;
  undefined8 local_ec0;
  undefined8 local_eb8;
  undefined4 local_eb0 [32];
  undefined4 *local_e30;
  long local_e28;
  ulong local_e20;
  undefined8 local_e18;
  undefined8 local_e10;
  undefined8 local_e08;
  uint local_e00 [32];
  uint *local_d80;
  undefined8 local_d78;
  ulong local_d70;
  undefined8 local_d68;
  undefined8 local_d60;
  undefined8 local_d58;
  uint local_d50 [5];
  uint local_d3c [27];
  uint *local_cd0;
  long local_cc8;
  ulong local_cc0;
  undefined8 local_cb8;
  undefined8 local_cb0;
  undefined8 local_ca8;
  undefined4 local_ca0 [32];
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
  uint local_b40 [11];
  uint local_b14 [21];
  uint *local_ac0;
  undefined8 local_ab8;
  ulong local_ab0;
  undefined8 local_aa8;
  undefined8 local_aa0;
  undefined8 local_a98;
  undefined4 local_a90 [32];
  undefined4 *local_a10;
  long local_a08;
  ulong local_a00;
  undefined8 local_9f8;
  undefined8 local_9f0;
  undefined8 local_9e8;
  uint local_9e0 [32];
  uint *local_960;
  long local_958;
  ulong local_950;
  undefined8 local_948;
  undefined8 local_940;
  undefined8 local_938;
  uint local_930 [32];
  uint *local_8b0;
  undefined8 local_8a8;
  ulong local_8a0;
  undefined8 local_898;
  undefined8 local_890;
  undefined8 local_888;
  uint local_880 [5];
  uint local_86c [27];
  uint *local_800;
  undefined8 local_7f8;
  ulong local_7f0;
  undefined8 local_7e8;
  undefined8 local_7e0;
  undefined8 local_7d8;
  uint local_7d0 [11];
  uint local_7a4 [21];
  uint *local_750;
  undefined8 local_748;
  ulong local_740;
  undefined8 local_738;
  undefined8 local_730;
  undefined8 local_728;
  undefined4 local_720 [32];
  undefined4 *local_6a0;
  long local_698;
  ulong local_690;
  undefined8 local_688;
  undefined8 local_680;
  undefined8 local_678;
  uint local_670 [32];
  uint *local_5f0;
  long local_5e8;
  ulong local_5e0;
  undefined8 local_5d8;
  undefined8 local_5d0;
  undefined8 local_5c8;
  uint local_5c0 [32];
  uint *local_540;
  long local_538;
  ulong local_530;
  undefined8 local_528;
  undefined8 local_520;
  undefined8 local_518;
  uint local_510 [32];
  uint *local_490;
  long local_488;
  ulong local_480;
  undefined8 local_478;
  undefined8 local_470;
  undefined8 local_468;
  uint local_460 [32];
  uint *local_3e0;
  undefined1 *local_3d8;
  long local_3d0;
  long local_3c8;
  undefined4 local_3c0;
  undefined4 local_3bc;
  undefined1 *local_3b8;
  undefined1 local_3b0;
  undefined4 local_3a8;
  undefined4 local_3a4;
  undefined4 local_3a0;
  undefined4 local_39c;
  undefined4 local_398;
  undefined4 local_394;
  undefined4 local_390;
  void *local_388;
  undefined1 local_378 [48];
  float local_348;
  float local_344;
  float local_340;
  float local_33c;
  undefined8 local_328;
  undefined8 local_320;
  BoundSlot *local_308;
  int *local_300;
  BoundSlot *local_2f8;
  int *local_2f0;
  BoundSlot *local_2e8;
  int *local_2e0;
  BoundSlot *local_2d8;
  int *local_2d0;
  undefined4 local_2c8;
  undefined4 local_2c4;
  undefined4 local_2c0;
  undefined4 local_2bc;
  undefined4 local_2a8;
  undefined4 local_2a4;
  undefined4 local_2a0;
  undefined4 local_29c;
  undefined4 local_288;
  undefined4 local_284;
  undefined4 local_280;
  undefined4 local_27c;
  undefined4 local_278;
  undefined4 local_274;
  undefined4 local_270;
  undefined4 local_26c;
  BoundSlot *local_268;
  int *local_260;
  undefined4 local_258;
  undefined4 local_254;
  undefined4 local_250;
  undefined4 local_24c;
  undefined4 local_248;
  undefined4 local_244;
  undefined4 local_240;
  undefined4 local_23c;
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
  undefined8 *local_108 [2];
  undefined8 *local_f8 [2];
  undefined8 *local_e8 [2];
  undefined8 *local_d8 [2];
  long local_c8 [2];
  long local_b8 [2];
  long local_a8 [2];
  long local_98 [2];
  long local_88 [2];
  undefined8 *local_78 [3];
  allocator local_5f [4];
  allocator local_5b [2];
  allocator local_59 [4];
  allocator local_55 [4];
  allocator local_51 [2];
  allocator local_4f [4];
  allocator local_4b [3];
  allocator local_48 [2];
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

  iVar6 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0xa0),KSETTINGS_RES_WIDTH);
  iVar7 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(this + 0xa0),KSETTINGS_RES_HEIGHT)
  ;
  uVar11 = CResourceManager::createGenericModel
                     (*(CResourceManager **)(this + 0xd0),*(SceneManager **)(this + 0xb0),
                      L"media/ui/models/dropdown/dropdown.mesh",L"",false,false,false);
  *(undefined8 *)(this + 200) = uVar11;
  local_388 = (void *)0x0;
  local_390 = 1;
  local_3a8 = 0xc7c35000;
  local_3a4 = 0xc7c35000;
  local_3a0 = 0xc7c35000;
  local_39c = 0x47c35000;
  local_398 = 0x47c35000;
  local_394 = 0x47c35000;
                    /* try { // try from 00ad7b2a to 00ad7cba has its CatchHandler @ 00adcee5 */
  lVar12 = Ogre::Entity::getMesh();
  Ogre::Mesh::_setBounds(*(AxisAlignedBox **)(lVar12 + 8),SUB81(&local_3a8,0));
  fVar33 = (float)iVar7 / DAT_00fc6774;
  pcVar4 = *(code **)(**(long **)(this + 200) + 0x58);
  fVar34 = (float)CDynamicPropertyFile::GetFloat
                            (*(CDynamicPropertyFile **)(this + 0xa0),KSETTINGS_YRATIO);
  (*pcVar4)(DAT_00fa86f4 * (((float)iVar6 - fVar33) / fVar34) - DAT_00fe6518,0,
            *(undefined8 *)(this + 200));
  (**(code **)(**(long **)(this + 200) + 0x50))(*(long **)(this + 200),0);
  pcVar27 = (char *)0x0;
  pcVar31 = "GuiLook";
  local_480 = 0x20;
  local_478 = 0;
  pcVar28 = "GuiLook";
  local_468 = 0;
  local_470 = 0;
  local_3e0 = (uint *)0x0;
  local_488 = 0;
  local_460[0] = 0;
  cVar2 = s_GuiLook_00fe493c[0];
  while (pcVar28 = pcVar28 + 1, cVar2 != '\0') {
    pcVar27 = pcVar28 + -0xfe493c;
    cVar2 = *pcVar28;
  }
  if (pcVar27 == CEGUI::String::npos) {
                    /* try { // try from 00adc4a8 to 00adc4ac has its CatchHandler @ 00add6c9 */
    std::string::string((string *)local_178,"Length for utf8 encoded string can not be \'npos\'",
                        &local_3e);
    plVar22 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00adc4c0 to 00adc4c4 has its CatchHandler @ 00add622 */
    std::length_error::length_error(plVar22,(string *)local_178);
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
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00adc4eb to 00adc4ef has its CatchHandler @ 00adcee5 */
    __cxa_throw(plVar22,&std::length_error::typeinfo,std::length_error::~length_error);
  }
  lVar12 = 0;
  pcVar28 = pcVar27;
  pbVar16 = (byte *)"GuiLook";
  while (pcVar28 != (char *)0x0) {
    bVar3 = *pbVar16;
    pcVar13 = pcVar28 + -1;
    pbVar25 = pbVar16 + 1;
    if ((char)bVar3 < '\0') {
      if (bVar3 < 0xe0) {
        pcVar13 = pcVar28 + -2;
        pbVar25 = pbVar16 + 2;
      }
      else if (bVar3 < 0xf0) {
        pcVar13 = pcVar28 + -3;
        pbVar25 = pbVar16 + 3;
      }
      else {
        pcVar13 = pcVar28 + -3;
        pbVar25 = pbVar16 + 4;
      }
    }
    lVar12 = lVar12 + 1;
    pcVar28 = pcVar13;
    pbVar16 = pbVar25;
  }
  CEGUI::String::grow((ulong)&local_488);
  if (local_480 < 0x21) {
    puVar19 = local_460;
    if (pcVar27 == (char *)0x0) goto LAB_00ad7e70;
LAB_00ad7cda:
    bVar32 = local_480 != 0;
LAB_00ad7ce0:
    if (bVar32) {
      pcVar31 = (char *)0x0;
      uVar9 = 0;
      uVar23 = local_480;
      do {
        bVar3 = pcVar31[0xfe493c];
        uVar10 = (uint)bVar3;
        uVar8 = uVar9 + 1;
        if ((char)bVar3 < '\0') {
          uVar10 = (uint)bVar3;
          if (0xdf < bVar3) {
            if (bVar3 < 0xf0) {
              uVar26 = (ulong)uVar8;
              uVar8 = uVar9 + 3;
              uVar10 = (byte)"GuiLook"[uVar9 + 2] & 0x3f | (uVar10 & 0xf) << 0xc |
                       ((byte)"GuiLook"[uVar26] & 0x3f) << 6;
            }
            else {
              uVar26 = (ulong)uVar8;
              uVar8 = uVar9 + 4;
              uVar10 = ((byte)"GuiLook"[uVar26] & 0x3f) << 0xc | (byte)"GuiLook"[uVar9 + 3] & 0x3f |
                       (uVar10 & 7) << 0x12 | ((byte)"GuiLook"[uVar9 + 2] & 0x3f) << 6;
            }
            goto LAB_00ad7cf3;
          }
          uVar9 = uVar9 + 2;
          *puVar19 = (byte)"GuiLook"[uVar8] & 0x3f | (uVar10 & 0x1f) << 6;
        }
        else {
LAB_00ad7cf3:
          *puVar19 = uVar10;
          uVar9 = uVar8;
        }
        pcVar31 = (char *)(ulong)uVar9;
        if ((pcVar27 <= pcVar31) || (uVar23 = uVar23 - 1, uVar23 == 0)) break;
        puVar19 = puVar19 + 1;
      } while( true );
    }
  }
  else {
    puVar19 = local_3e0;
    if (pcVar27 != (char *)0x0) goto LAB_00ad7cda;
LAB_00ad7e70:
    if (s_GuiLook_00fe493c[0] != '\0') {
      do {
        pcVar31 = pcVar31 + 1;
        pcVar27 = pcVar31 + -0xfe493c;
      } while (*pcVar31 != '\0');
      bVar32 = pcVar27 != (char *)0x0 && local_480 != 0;
      goto LAB_00ad7ce0;
    }
  }
  puVar19 = local_460;
  if (0x20 < local_480) {
    puVar19 = local_3e0;
  }
  puVar19[lVar12] = 0;
  local_488 = lVar12;
                    /* try { // try from 00ad7d81 to 00ad7d85 has its CatchHandler @ 00adcf16 */
  CEGUI::ImagesetManager::getImageset(CEGUI::Singleton<CEGUI::ImagesetManager>::ms_Singleton);
                    /* try { // try from 00ad7d89 to 00ad7f32 has its CatchHandler @ 00adcee5 */
  CEGUI::String::~String((String *)&local_488);
  pcVar28 = (char *)0x0;
  pcVar27 = "UIIcons";
  local_530 = 0x20;
  local_528 = 0;
  pcVar31 = "UIIcons";
  local_518 = 0;
  local_520 = 0;
  local_490 = (uint *)0x0;
  local_538 = 0;
  local_510[0] = 0;
  cVar2 = s_UIIcons_00fe49dd[0];
  while (pcVar31 = pcVar31 + 1, cVar2 != '\0') {
    pcVar28 = pcVar31 + -0xfe49dd;
    cVar2 = *pcVar31;
  }
  if (pcVar28 == CEGUI::String::npos) {
                    /* try { // try from 00adc598 to 00adc59c has its CatchHandler @ 00add5ed */
    std::string::string((string *)local_188,"Length for utf8 encoded string can not be \'npos\'",
                        local_40);
    plVar22 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00adc5b0 to 00adc5b4 has its CatchHandler @ 00add5b4 */
    std::length_error::length_error(plVar22,(string *)local_188);
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
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00adc5db to 00adc5df has its CatchHandler @ 00adcee5 */
    __cxa_throw(plVar22,&std::length_error::typeinfo,std::length_error::~length_error);
  }
  lVar12 = 0;
  pcVar31 = pcVar28;
  pbVar16 = (byte *)"UIIcons";
  while (pcVar31 != (char *)0x0) {
    bVar3 = *pbVar16;
    pcVar13 = pcVar31 + -1;
    pbVar25 = pbVar16 + 1;
    if ((char)bVar3 < '\0') {
      if (bVar3 < 0xe0) {
        pcVar13 = pcVar31 + -2;
        pbVar25 = pbVar16 + 2;
      }
      else if (bVar3 < 0xf0) {
        pcVar13 = pcVar31 + -3;
        pbVar25 = pbVar16 + 3;
      }
      else {
        pcVar13 = pcVar31 + -3;
        pbVar25 = pbVar16 + 4;
      }
    }
    lVar12 = lVar12 + 1;
    pcVar31 = pcVar13;
    pbVar16 = pbVar25;
  }
  CEGUI::String::grow((ulong)&local_538);
  puVar19 = local_510;
  if (0x20 < local_530) {
    puVar19 = local_490;
  }
  if (pcVar28 == (char *)0x0) {
    if (s_UIIcons_00fe49dd[0] != '\0') {
      do {
        pcVar27 = pcVar27 + 1;
        pcVar28 = pcVar27 + -0xfe49dd;
      } while (*pcVar27 != '\0');
      bVar32 = pcVar28 != (char *)0x0 && local_530 != 0;
      goto LAB_00ad7f5c;
    }
  }
  else {
    bVar32 = local_530 != 0;
LAB_00ad7f5c:
    if (bVar32) {
      pcVar31 = (char *)0x0;
      uVar9 = 0;
      uVar23 = local_530;
      do {
        bVar3 = pcVar31[0xfe49dd];
        uVar10 = (uint)bVar3;
        uVar8 = uVar9 + 1;
        if ((char)bVar3 < '\0') {
          uVar10 = (uint)bVar3;
          if (0xdf < bVar3) {
            if (bVar3 < 0xf0) {
              uVar26 = (ulong)uVar8;
              uVar8 = uVar9 + 3;
              uVar10 = (byte)"UIIcons"[uVar9 + 2] & 0x3f | (uVar10 & 0xf) << 0xc |
                       ((byte)"UIIcons"[uVar26] & 0x3f) << 6;
            }
            else {
              uVar26 = (ulong)uVar8;
              uVar8 = uVar9 + 4;
              uVar10 = ((byte)"UIIcons"[uVar26] & 0x3f) << 0xc | (byte)"UIIcons"[uVar9 + 3] & 0x3f |
                       (uVar10 & 7) << 0x12 | ((byte)"UIIcons"[uVar9 + 2] & 0x3f) << 6;
            }
            goto LAB_00ad7f73;
          }
          uVar9 = uVar9 + 2;
          *puVar19 = (byte)"UIIcons"[uVar8] & 0x3f | (uVar10 & 0x1f) << 6;
        }
        else {
LAB_00ad7f73:
          *puVar19 = uVar10;
          uVar9 = uVar8;
        }
        pcVar31 = (char *)(ulong)uVar9;
        if ((pcVar28 <= pcVar31) || (uVar23 = uVar23 - 1, uVar23 == 0)) break;
        puVar19 = puVar19 + 1;
      } while( true );
    }
  }
  puVar19 = local_510;
  if (0x20 < local_530) {
    puVar19 = local_490;
  }
  puVar19[lVar12] = 0;
  local_538 = lVar12;
                    /* try { // try from 00ad8001 to 00ad8005 has its CatchHandler @ 00adcef5 */
  uVar11 = CEGUI::ImagesetManager::getImageset
                     (CEGUI::Singleton<CEGUI::ImagesetManager>::ms_Singleton);
  *(undefined8 *)(this + 0x198) = uVar11;
                    /* try { // try from 00ad8010 to 00ad8079 has its CatchHandler @ 00adcee5 */
  CEGUI::String::~String((String *)&local_538);
  local_740 = 0x20;
  local_738 = 0;
  local_728 = 0;
  local_730 = 0;
  local_6a0 = (undefined4 *)0x0;
  local_748 = 0;
  local_720[0] = 0;
  CEGUI::String::grow((ulong)&local_748);
  local_748 = 0;
  puVar18 = local_720;
  if (0x20 < local_740) {
    puVar18 = local_6a0;
  }
  *puVar18 = 0;
  pcVar27 = (char *)0x0;
  pcVar31 = "CombineSheet";
  local_690 = 0x20;
  local_688 = 0;
  local_678 = 0;
  local_680 = 0;
  pcVar28 = "CombineSheet";
  local_5f0 = (uint *)0x0;
  local_698 = 0;
  local_670[0] = 0;
  cVar2 = s_CombineSheet_00fe6074[0];
  while (pcVar28 = pcVar28 + 1, cVar2 != '\0') {
    pcVar27 = pcVar28 + -0xfe6074;
    cVar2 = *pcVar28;
  }
  if (pcVar27 == CEGUI::String::npos) {
                    /* try { // try from 00adc658 to 00adc65c has its CatchHandler @ 00add56e */
    std::string::string((string *)local_198,"Length for utf8 encoded string can not be \'npos\'",
                        local_42);
    plVar22 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00adc670 to 00adc674 has its CatchHandler @ 00add554 */
    std::length_error::length_error(plVar22,(string *)local_198);
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
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00adc69b to 00adc69f has its CatchHandler @ 00adce60 */
    __cxa_throw(plVar22,&std::length_error::typeinfo,std::length_error::~length_error);
  }
  lVar12 = 0;
  pcVar28 = pcVar27;
  pbVar16 = (byte *)"CombineSheet";
  while (pcVar28 != (char *)0x0) {
    bVar3 = *pbVar16;
    pcVar13 = pcVar28 + -1;
    pbVar25 = pbVar16 + 1;
    if ((char)bVar3 < '\0') {
      if (bVar3 < 0xe0) {
        pcVar13 = pcVar28 + -2;
        pbVar25 = pbVar16 + 2;
      }
      else if (bVar3 < 0xf0) {
        pcVar13 = pcVar28 + -3;
        pbVar25 = pbVar16 + 3;
      }
      else {
        pcVar13 = pcVar28 + -3;
        pbVar25 = pbVar16 + 4;
      }
    }
    lVar12 = lVar12 + 1;
    pcVar28 = pcVar13;
    pbVar16 = pbVar25;
  }
                    /* try { // try from 00ad81de to 00ad81e2 has its CatchHandler @ 00adce60 */
  CEGUI::String::grow((ulong)&local_698);
  puVar19 = local_670;
  if (0x20 < local_690) {
    puVar19 = local_5f0;
  }
  if (pcVar27 == (char *)0x0) {
    if (s_CombineSheet_00fe6074[0] != '\0') {
      do {
        pcVar31 = pcVar31 + 1;
        pcVar27 = pcVar31 + -0xfe6074;
      } while (*pcVar31 != '\0');
      bVar32 = pcVar27 != (char *)0x0 && local_690 != 0;
      goto LAB_00ad820c;
    }
  }
  else {
    bVar32 = local_690 != 0;
LAB_00ad820c:
    if (bVar32) {
      pcVar31 = (char *)0x0;
      uVar9 = 0;
      uVar23 = local_690;
      do {
        bVar3 = pcVar31[0xfe6074];
        uVar10 = (uint)bVar3;
        uVar8 = uVar9 + 1;
        if ((char)bVar3 < '\0') {
          uVar10 = (uint)bVar3;
          if (0xdf < bVar3) {
            if (bVar3 < 0xf0) {
              uVar26 = (ulong)uVar8;
              uVar8 = uVar9 + 3;
              uVar10 = (byte)"CombineSheet"[uVar9 + 2] & 0x3f | (uVar10 & 0xf) << 0xc |
                       ((byte)"CombineSheet"[uVar26] & 0x3f) << 6;
            }
            else {
              uVar26 = (ulong)uVar8;
              uVar8 = uVar9 + 4;
              uVar10 = ((byte)"CombineSheet"[uVar26] & 0x3f) << 0xc |
                       (byte)"CombineSheet"[uVar9 + 3] & 0x3f | (uVar10 & 7) << 0x12 |
                       ((byte)"CombineSheet"[uVar9 + 2] & 0x3f) << 6;
            }
            goto LAB_00ad8223;
          }
          uVar9 = uVar9 + 2;
          *puVar19 = (byte)"CombineSheet"[uVar8] & 0x3f | (uVar10 & 0x1f) << 6;
        }
        else {
LAB_00ad8223:
          *puVar19 = uVar10;
          uVar9 = uVar8;
        }
        pcVar31 = (char *)(ulong)uVar9;
        if ((pcVar27 <= pcVar31) || (uVar23 = uVar23 - 1, uVar23 == 0)) break;
        puVar19 = puVar19 + 1;
      } while( true );
    }
  }
  puVar19 = local_670;
  if (0x20 < local_690) {
    puVar19 = local_5f0;
  }
  puVar19[lVar12] = 0;
  pcVar27 = (char *)0x0;
  local_5e0 = 0x20;
  local_5d8 = 0;
  pcVar31 = "DefaultWindow";
  local_5c8 = 0;
  local_5d0 = 0;
  local_540 = (uint *)0x0;
  local_5e8 = 0;
  local_5c0[0] = 0;
  pcVar28 = "DefaultWindow";
  cVar2 = s_DefaultWindow_00fe499d[0];
  while (pcVar31 = pcVar31 + 1, cVar2 != '\0') {
    pcVar27 = pcVar31 + -0xfe499d;
    cVar2 = *pcVar31;
  }
  local_698 = lVar12;
  if (pcVar27 == CEGUI::String::npos) {
                    /* try { // try from 00adc751 to 00adc755 has its CatchHandler @ 00add0d2 */
    std::string::string((string *)local_1a8,"Length for utf8 encoded string can not be \'npos\'",
                        local_44);
    plVar22 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00adc769 to 00adc76d has its CatchHandler @ 00add104 */
    std::length_error::length_error(plVar22,(string *)local_1a8);
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
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00adc794 to 00adc798 has its CatchHandler @ 00adce72 */
    __cxa_throw(plVar22,&std::length_error::typeinfo,std::length_error::~length_error);
  }
  lVar12 = 0;
  pcVar31 = pcVar27;
  pbVar16 = (byte *)"DefaultWindow";
  while (pcVar31 != (char *)0x0) {
    bVar3 = *pbVar16;
    pcVar13 = pcVar31 + -1;
    pbVar25 = pbVar16 + 1;
    if ((char)bVar3 < '\0') {
      if (bVar3 < 0xe0) {
        pcVar13 = pcVar31 + -2;
        pbVar25 = pbVar16 + 2;
      }
      else if (bVar3 < 0xf0) {
        pcVar13 = pcVar31 + -3;
        pbVar25 = pbVar16 + 3;
      }
      else {
        pcVar13 = pcVar31 + -3;
        pbVar25 = pbVar16 + 4;
      }
    }
    lVar12 = lVar12 + 1;
    pcVar31 = pcVar13;
    pbVar16 = pbVar25;
  }
                    /* try { // try from 00ad843e to 00ad8442 has its CatchHandler @ 00adce72 */
  CEGUI::String::grow((ulong)&local_5e8);
  puVar19 = local_5c0;
  if (0x20 < local_5e0) {
    puVar19 = local_540;
  }
  if (pcVar27 == (char *)0x0) {
    pcVar31 = "DefaultWindow";
    if (s_DefaultWindow_00fe499d[0] != '\0') {
      do {
        pcVar31 = pcVar31 + 1;
        pcVar27 = pcVar31 + -0xfe499d;
      } while (*pcVar31 != '\0');
      bVar32 = pcVar27 != (char *)0x0 && local_5e0 != 0;
      goto LAB_00ad846c;
    }
  }
  else {
    bVar32 = local_5e0 != 0;
LAB_00ad846c:
    if (bVar32) {
      pcVar31 = (char *)0x0;
      uVar9 = 0;
      uVar23 = local_5e0;
      do {
        bVar3 = pcVar31[0xfe499d];
        uVar10 = (uint)bVar3;
        uVar8 = uVar9 + 1;
        if ((char)bVar3 < '\0') {
          uVar10 = (uint)bVar3;
          if (0xdf < bVar3) {
            if (bVar3 < 0xf0) {
              uVar26 = (ulong)uVar8;
              uVar8 = uVar9 + 3;
              uVar10 = (byte)"DefaultWindow"[uVar9 + 2] & 0x3f | (uVar10 & 0xf) << 0xc |
                       ((byte)"DefaultWindow"[uVar26] & 0x3f) << 6;
            }
            else {
              uVar26 = (ulong)uVar8;
              uVar8 = uVar9 + 4;
              uVar10 = ((byte)"DefaultWindow"[uVar26] & 0x3f) << 0xc |
                       (byte)"DefaultWindow"[uVar9 + 3] & 0x3f | (uVar10 & 7) << 0x12 |
                       ((byte)"DefaultWindow"[uVar9 + 2] & 0x3f) << 6;
            }
            goto LAB_00ad8483;
          }
          uVar9 = uVar9 + 2;
          *puVar19 = (byte)"DefaultWindow"[uVar8] & 0x3f | (uVar10 & 0x1f) << 6;
        }
        else {
LAB_00ad8483:
          *puVar19 = uVar10;
          uVar9 = uVar8;
        }
        pcVar31 = (char *)(ulong)uVar9;
        if ((pcVar27 <= pcVar31) || (uVar23 = uVar23 - 1, uVar23 == 0)) break;
        puVar19 = puVar19 + 1;
      } while( true );
    }
  }
  puVar19 = local_5c0;
  if (0x20 < local_5e0) {
    puVar19 = local_540;
  }
  puVar19[lVar12] = 0;
  local_5e8 = lVar12;
                    /* try { // try from 00ad8517 to 00ad851b has its CatchHandler @ 00adce81 */
  uVar11 = CEGUI::WindowManager::createWindow
                     (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,(String *)&local_5e8,
                      (String *)&local_698);
  *(undefined8 *)(this + 0x50) = uVar11;
                    /* try { // try from 00ad8523 to 00ad8527 has its CatchHandler @ 00adce72 */
  CEGUI::String::~String((String *)&local_5e8);
                    /* try { // try from 00ad852b to 00ad852f has its CatchHandler @ 00adce60 */
  CEGUI::String::~String((String *)&local_698);
                    /* try { // try from 00ad8533 to 00ad8537 has its CatchHandler @ 00adcee5 */
  CEGUI::String::~String((String *)&local_748);
  local_244 = 0;
  local_248 = 0x3f800000;
  local_23c = 0;
  local_240 = 0x3f800000;
                    /* try { // try from 00ad8570 to 00ad8574 has its CatchHandler @ 00adce21 */
  CEGUI::Window::setSize(*(UVector2 **)(this + 0x50));
  local_8a0 = 0x20;
  local_898 = 0;
  local_888 = 0;
  local_890 = 0;
  local_800 = (uint *)0x0;
  local_8a8 = 0;
  local_880[0] = 0;
                    /* try { // try from 00ad85d8 to 00ad85dc has its CatchHandler @ 00adcee5 */
  CEGUI::String::grow((ulong)&local_8a8);
  puVar19 = local_880;
  if (0x20 < local_8a0) {
    puVar19 = local_800;
  }
  pcVar31 = "False";
  do {
    bVar3 = *pcVar31;
    pcVar31 = pcVar31 + 1;
    *puVar19 = (uint)bVar3;
    puVar19 = puVar19 + 1;
  } while ((byte *)pcVar31 != (byte *)0xfe603f);
  local_8a8 = 5;
  puVar19 = local_86c;
  if (0x20 < local_8a0) {
    puVar19 = local_800 + 5;
  }
  *puVar19 = 0;
  local_7f0 = 0x20;
  local_7e8 = 0;
  local_7d8 = 0;
  local_7e0 = 0;
  local_750 = (uint *)0x0;
  local_7f8 = 0;
  local_7d0[0] = 0;
                    /* try { // try from 00ad86a6 to 00ad86aa has its CatchHandler @ 00adce2b */
  CEGUI::String::grow((ulong)&local_7f8);
  puVar19 = local_7d0;
  if (0x20 < local_7f0) {
    puVar19 = local_750;
  }
  pcVar31 = "RiseOnClick";
  do {
    bVar3 = *pcVar31;
    pcVar31 = pcVar31 + 1;
    *puVar19 = (uint)bVar3;
    puVar19 = puVar19 + 1;
  } while ((byte *)pcVar31 != (byte *)0xfe6039);
  local_7f8 = 0xb;
  puVar19 = local_7a4;
  if (0x20 < local_7f0) {
    puVar19 = local_750 + 0xb;
  }
  *puVar19 = 0;
                    /* try { // try from 00ad871c to 00ad8720 has its CatchHandler @ 00adce3d */
  CEGUI::PropertySet::setProperty(*(String **)(this + 0x50),(String *)&local_7f8);
                    /* try { // try from 00ad8724 to 00ad8728 has its CatchHandler @ 00adce2b */
  CEGUI::String::~String((String *)&local_7f8);
                    /* try { // try from 00ad872c to 00ad8730 has its CatchHandler @ 00adcee5 */
  CEGUI::String::~String((String *)&local_8a8);
  local_254 = 0;
  local_258 = 0;
  local_24c = 0;
  local_250 = 0;
                    /* try { // try from 00ad8769 to 00ad876d has its CatchHandler @ 00adce4c */
  CEGUI::Window::setPosition(*(UVector2 **)(this + 0x50));
  *(undefined1 *)(*(long *)(this + 0x50) + 0x3e2) = 1;
                    /* try { // try from 00ad877f to 00ad8799 has its CatchHandler @ 00adcee5 */
  CEGUI::Window::setZOrderingEnabled(SUB81(*(undefined8 *)(this + 0x50),0));
  pcVar4 = *(code **)(*(long *)(*(long *)(this + 0x50) + 0x38) + 0x10);
  local_78[0] = operator_new(0x20);
  *local_78[0] = &PTR__MemberFunctionSlot_00fe6410;
  local_78[0][2] = 0;
  local_78[0][1] = handle_MouseThrough;
  local_78[0][3] = this;
                    /* try { // try from 00ad87dd to 00ad8812 has its CatchHandler @ 00adce4e */
  (*pcVar4)(&local_268,*(long *)(this + 0x50) + 0x38,CEGUI::Window::EventMouseMove,
            (SubscriberSlot *)local_78);
  if ((local_268 != (BoundSlot *)0x0) &&
     (iVar6 = *local_260, *local_260 = iVar6 + -1, iVar6 + -1 == 0)) {
    if (local_268 != (BoundSlot *)0x0) {
      CEGUI::BoundSlot::~BoundSlot(local_268);
      operator_delete(local_268);
    }
    operator_delete(local_260);
    local_268 = (BoundSlot *)0x0;
    local_260 = (int *)0x0;
  }
                    /* try { // try from 00ad8843 to 00ad88ac has its CatchHandler @ 00adcee5 */
  CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_78);
  local_ab0 = 0x20;
  local_aa8 = 0;
  local_a98 = 0;
  local_aa0 = 0;
  local_a10 = (undefined4 *)0x0;
  local_ab8 = 0;
  local_a90[0] = 0;
  CEGUI::String::grow((ulong)&local_ab8);
  local_ab8 = 0;
  puVar18 = local_a90;
  if (0x20 < local_ab0) {
    puVar18 = local_a10;
  }
  *puVar18 = 0;
  pcVar27 = (char *)0x0;
  pcVar13 = "CombineClickBarrier";
  local_a00 = 0x20;
  local_9f8 = 0;
  local_9e8 = 0;
  local_9f0 = 0;
  pcVar31 = "CombineClickBarrier";
  local_960 = (uint *)0x0;
  local_a08 = 0;
  local_9e0[0] = 0;
  cVar2 = s_CombineClickBarrier_00fe6060[0];
  while (pcVar31 = pcVar31 + 1, cVar2 != '\0') {
    pcVar27 = pcVar31 + -0xfe6060;
    cVar2 = *pcVar31;
  }
  if (pcVar27 == CEGUI::String::npos) {
                    /* try { // try from 00adc7be to 00adc7c2 has its CatchHandler @ 00add12e */
    std::string::string((string *)local_1b8,"Length for utf8 encoded string can not be \'npos\'",
                        local_46);
    plVar22 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00adc7d6 to 00adc7da has its CatchHandler @ 00add0b8 */
    std::length_error::length_error(plVar22,(string *)local_1b8);
    if ((allocator *)(local_1b8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_1b8[0] + -8);
      iVar6 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar6 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_1b8[0] + -0x18));
      }
    }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00adc801 to 00adc805 has its CatchHandler @ 00adcf11 */
    __cxa_throw(plVar22,&std::length_error::typeinfo,std::length_error::~length_error);
  }
  lVar12 = 0;
  pcVar31 = pcVar27;
  pbVar16 = (byte *)"CombineClickBarrier";
  while (pcVar31 != (char *)0x0) {
    bVar3 = *pbVar16;
    pcVar14 = pcVar31 + -1;
    pbVar25 = pbVar16 + 1;
    if ((char)bVar3 < '\0') {
      if (bVar3 < 0xe0) {
        pcVar14 = pcVar31 + -2;
        pbVar25 = pbVar16 + 2;
      }
      else if (bVar3 < 0xf0) {
        pcVar14 = pcVar31 + -3;
        pbVar25 = pbVar16 + 3;
      }
      else {
        pcVar14 = pcVar31 + -3;
        pbVar25 = pbVar16 + 4;
      }
    }
    lVar12 = lVar12 + 1;
    pcVar31 = pcVar14;
    pbVar16 = pbVar25;
  }
                    /* try { // try from 00ad8a6e to 00ad8a72 has its CatchHandler @ 00adcf11 */
  CEGUI::String::grow((ulong)&local_a08);
  puVar19 = local_9e0;
  if (0x20 < local_a00) {
    puVar19 = local_960;
  }
  if (pcVar27 == (char *)0x0) {
    if (s_CombineClickBarrier_00fe6060[0] != '\0') {
      do {
        pcVar13 = pcVar13 + 1;
        pcVar27 = pcVar13 + -0xfe6060;
      } while (*pcVar13 != '\0');
      bVar32 = pcVar27 != (char *)0x0 && local_a00 != 0;
      goto LAB_00ad8a9c;
    }
  }
  else {
    bVar32 = local_a00 != 0;
LAB_00ad8a9c:
    if (bVar32) {
      pcVar31 = (char *)0x0;
      uVar9 = 0;
      uVar23 = local_a00;
      do {
        bVar3 = pcVar31[0xfe6060];
        uVar10 = (uint)bVar3;
        uVar8 = uVar9 + 1;
        if ((char)bVar3 < '\0') {
          uVar10 = (uint)bVar3;
          if (0xdf < bVar3) {
            if (bVar3 < 0xf0) {
              uVar26 = (ulong)uVar8;
              uVar8 = uVar9 + 3;
              uVar10 = (byte)"CombineClickBarrier"[uVar9 + 2] & 0x3f | (uVar10 & 0xf) << 0xc |
                       ((byte)"CombineClickBarrier"[uVar26] & 0x3f) << 6;
            }
            else {
              uVar26 = (ulong)uVar8;
              uVar8 = uVar9 + 4;
              uVar10 = ((byte)"CombineClickBarrier"[uVar26] & 0x3f) << 0xc |
                       (byte)"CombineClickBarrier"[uVar9 + 3] & 0x3f | (uVar10 & 7) << 0x12 |
                       ((byte)"CombineClickBarrier"[uVar9 + 2] & 0x3f) << 6;
            }
            goto LAB_00ad8ab3;
          }
          uVar9 = uVar9 + 2;
          *puVar19 = (byte)"CombineClickBarrier"[uVar8] & 0x3f | (uVar10 & 0x1f) << 6;
        }
        else {
LAB_00ad8ab3:
          *puVar19 = uVar10;
          uVar9 = uVar8;
        }
        pcVar31 = (char *)(ulong)uVar9;
        if ((pcVar27 <= pcVar31) || (uVar23 = uVar23 - 1, uVar23 == 0)) break;
        puVar19 = puVar19 + 1;
      } while( true );
    }
  }
  puVar19 = local_9e0;
  if (0x20 < local_a00) {
    puVar19 = local_960;
  }
  puVar19[lVar12] = 0;
  pcVar27 = (char *)0x0;
  local_950 = 0x20;
  local_948 = 0;
  pcVar31 = "DefaultWindow";
  local_938 = 0;
  local_940 = 0;
  local_8b0 = (uint *)0x0;
  local_958 = 0;
  local_930[0] = 0;
  cVar2 = s_DefaultWindow_00fe499d[0];
  while (pcVar31 = pcVar31 + 1, cVar2 != '\0') {
    pcVar27 = pcVar31 + -0xfe499d;
    cVar2 = *pcVar31;
  }
  local_a08 = lVar12;
  if (pcVar27 == CEGUI::String::npos) {
                    /* try { // try from 00adc81e to 00adc822 has its CatchHandler @ 00add083 */
    std::string::string((string *)local_1c8,"Length for utf8 encoded string can not be \'npos\'",
                        local_48);
    plVar22 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00adc836 to 00adc83a has its CatchHandler @ 00add04a */
    std::length_error::length_error(plVar22,(string *)local_1c8);
    if ((allocator *)(local_1c8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_1c8[0] + -8);
      iVar6 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar6 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_1c8[0] + -0x18));
      }
    }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00adc861 to 00adc865 has its CatchHandler @ 00adce90 */
    __cxa_throw(plVar22,&std::length_error::typeinfo,std::length_error::~length_error);
  }
  lVar12 = 0;
  pcVar31 = pcVar27;
  pbVar16 = (byte *)"DefaultWindow";
  while (pcVar31 != (char *)0x0) {
    bVar3 = *pbVar16;
    pcVar13 = pcVar31 + -1;
    pbVar25 = pbVar16 + 1;
    if ((char)bVar3 < '\0') {
      if (bVar3 < 0xe0) {
        pcVar13 = pcVar31 + -2;
        pbVar25 = pbVar16 + 2;
      }
      else if (bVar3 < 0xf0) {
        pcVar13 = pcVar31 + -3;
        pbVar25 = pbVar16 + 3;
      }
      else {
        pcVar13 = pcVar31 + -3;
        pbVar25 = pbVar16 + 4;
      }
    }
    lVar12 = lVar12 + 1;
    pcVar31 = pcVar13;
    pbVar16 = pbVar25;
  }
                    /* try { // try from 00ad8cce to 00ad8cd2 has its CatchHandler @ 00adce90 */
  CEGUI::String::grow((ulong)&local_958);
  puVar19 = local_930;
  if (0x20 < local_950) {
    puVar19 = local_8b0;
  }
  if (pcVar27 == (char *)0x0) {
    pcVar31 = "DefaultWindow";
    if (s_DefaultWindow_00fe499d[0] != '\0') {
      do {
        pcVar31 = pcVar31 + 1;
        pcVar27 = pcVar31 + -0xfe499d;
      } while (*pcVar31 != '\0');
      bVar32 = pcVar27 != (char *)0x0 && local_950 != 0;
      goto LAB_00ad8cfc;
    }
  }
  else {
    bVar32 = local_950 != 0;
LAB_00ad8cfc:
    if (bVar32) {
      pcVar31 = (char *)0x0;
      uVar9 = 0;
      uVar23 = local_950;
      do {
        bVar3 = pcVar31[0xfe499d];
        uVar10 = (uint)bVar3;
        uVar8 = uVar9 + 1;
        if ((char)bVar3 < '\0') {
          uVar10 = (uint)bVar3;
          if (0xdf < bVar3) {
            if (bVar3 < 0xf0) {
              uVar26 = (ulong)uVar8;
              uVar8 = uVar9 + 3;
              uVar10 = (byte)"DefaultWindow"[uVar9 + 2] & 0x3f | (uVar10 & 0xf) << 0xc |
                       ((byte)"DefaultWindow"[uVar26] & 0x3f) << 6;
            }
            else {
              uVar26 = (ulong)uVar8;
              uVar8 = uVar9 + 4;
              uVar10 = ((byte)"DefaultWindow"[uVar26] & 0x3f) << 0xc |
                       (byte)"DefaultWindow"[uVar9 + 3] & 0x3f | (uVar10 & 7) << 0x12 |
                       ((byte)"DefaultWindow"[uVar9 + 2] & 0x3f) << 6;
            }
            goto LAB_00ad8d13;
          }
          uVar9 = uVar9 + 2;
          *puVar19 = (byte)"DefaultWindow"[uVar8] & 0x3f | (uVar10 & 0x1f) << 6;
        }
        else {
LAB_00ad8d13:
          *puVar19 = uVar10;
          uVar9 = uVar8;
        }
        pcVar31 = (char *)(ulong)uVar9;
        if ((pcVar27 <= pcVar31) || (uVar23 = uVar23 - 1, uVar23 == 0)) break;
        puVar19 = puVar19 + 1;
      } while( true );
    }
  }
  puVar19 = local_930;
  if (0x20 < local_950) {
    puVar19 = local_8b0;
  }
  puVar19[lVar12] = 0;
  local_958 = lVar12;
                    /* try { // try from 00ad8da7 to 00ad8dab has its CatchHandler @ 00adce92 */
  pUVar15 = (UVector2 *)
            CEGUI::WindowManager::createWindow
                      (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,(String *)&local_958,
                       (String *)&local_a08);
                    /* try { // try from 00ad8db2 to 00ad8db6 has its CatchHandler @ 00adce90 */
  CEGUI::String::~String((String *)&local_958);
                    /* try { // try from 00ad8dba to 00ad8dbe has its CatchHandler @ 00adcf11 */
  CEGUI::String::~String((String *)&local_a08);
                    /* try { // try from 00ad8dc2 to 00ad8de6 has its CatchHandler @ 00adcee5 */
  CEGUI::String::~String((String *)&local_ab8);
  CEGUI::Window::addChildWindow(*(Window **)(this + 0x50));
  uVar35 = CGameUI::scaledY(*(CGameUI **)(this + 0xa8),DAT_00fa4804);
                    /* try { // try from 00ad8dfc to 00ad8e00 has its CatchHandler @ 00adce94 */
  local_274 = CGameUI::scaledY(*(CGameUI **)(this + 0xa8),DAT_00fe651c);
  local_278 = 0;
  local_270 = 0;
  local_26c = uVar35;
                    /* try { // try from 00ad8e3a to 00ad8e3e has its CatchHandler @ 00adce96 */
  CEGUI::Window::setSize(pUVar15);
  local_c10 = 0x20;
  local_c08 = 0;
  local_bf8 = 0;
  local_c00 = 0;
  local_b70 = (uint *)0x0;
  local_c18 = 0;
  local_bf0[0] = 0;
                    /* try { // try from 00ad8ea2 to 00ad8ea6 has its CatchHandler @ 00adcee5 */
  CEGUI::String::grow((ulong)&local_c18);
  puVar19 = local_bf0;
  if (0x20 < local_c10) {
    puVar19 = local_b70;
  }
  pcVar31 = "False";
  do {
    bVar3 = *pcVar31;
    pcVar31 = pcVar31 + 1;
    *puVar19 = (uint)bVar3;
    puVar19 = puVar19 + 1;
  } while ((byte *)pcVar31 != (byte *)0xfe603f);
  local_c18 = 5;
  puVar19 = local_bdc;
  if (0x20 < local_c10) {
    puVar19 = local_b70 + 5;
  }
  *puVar19 = 0;
  local_b60 = 0x20;
  local_b58 = 0;
  local_b48 = 0;
  local_b50 = 0;
  local_ac0 = (uint *)0x0;
  local_b68 = 0;
  local_b40[0] = 0;
                    /* try { // try from 00ad8f6d to 00ad8f71 has its CatchHandler @ 00adcea5 */
  CEGUI::String::grow((ulong)&local_b68);
  puVar19 = local_b40;
  if (0x20 < local_b60) {
    puVar19 = local_ac0;
  }
  pcVar31 = "RiseOnClick";
  do {
    bVar3 = *pcVar31;
    pcVar31 = pcVar31 + 1;
    *puVar19 = (uint)bVar3;
    puVar19 = puVar19 + 1;
  } while ((byte *)pcVar31 != (byte *)0xfe6039);
  local_b68 = 0xb;
  puVar19 = local_b14;
  if (0x20 < local_b60) {
    puVar19 = local_ac0 + 0xb;
  }
  *puVar19 = 0;
                    /* try { // try from 00ad8fdc to 00ad8fe0 has its CatchHandler @ 00adceb7 */
  CEGUI::PropertySet::setProperty((String *)pUVar15,(String *)&local_b68);
                    /* try { // try from 00ad8fe4 to 00ad8fe8 has its CatchHandler @ 00adcea5 */
  CEGUI::String::~String((String *)&local_b68);
                    /* try { // try from 00ad8fec to 00ad8ff0 has its CatchHandler @ 00adcee5 */
  CEGUI::String::~String((String *)&local_c18);
  local_284 = 0;
  local_288 = 0;
  local_27c = 0;
  local_280 = 0;
                    /* try { // try from 00ad9028 to 00ad902c has its CatchHandler @ 00adcec6 */
  CEGUI::Window::setPosition(pUVar15);
                    /* try { // try from 00ad9030 to 00ad903e has its CatchHandler @ 00adcee5 */
  CEGUI::Window::moveToBack();
  CEGUI::Window::setZOrderingEnabled(SUB81(pUVar15,0));
  local_3d8 = &DAT_01423a38;
                    /* try { // try from 00ad905c to 00ad9060 has its CatchHandler @ 00adcecb */
  std::string::string((string *)&local_3d0,(string *)&::EMPTY_STRING);
                    /* try { // try from 00ad9072 to 00ad9076 has its CatchHandler @ 00adcd88 */
  std::wstring::wstring((wstring_conflict *)&local_3c8,(wstring_conflict *)&::EMPTY_WSTRING);
  local_3c0 = 4;
  local_3bc = 3;
  local_3b8 = &DAT_01423a38;
  local_3b0 = 0;
                    /* try { // try from 00ad90b9 to 00ad90bd has its CatchHandler @ 00adcdb0 */
  std::wstring::wstring((wstring_conflict *)local_88,L"media/ui/combinemenu.layout",local_39);
                    /* try { // try from 00ad90be to 00ad90e0 has its CatchHandler @ 00adcdb5 */
  this_00 = (CFileSystem *)CFileSystem::getSingleton();
  CFileSystem::getFileInfo
            (this_00,(wstring_conflict *)local_88,(CFileInfo *)&local_3d8,false,true,false);
  if ((allocator *)(local_88[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_88[0] + -8);
    iVar6 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar6 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
    }
  }
  local_cc0 = 0x20;
  local_cb8 = 0;
  local_ca8 = 0;
  local_cb0 = 0;
  local_c20 = (undefined4 *)0x0;
  local_cc8 = 0;
  local_ca0[0] = 0;
  lVar12 = *(long *)(local_3d0 + -0x18);
                    /* try { // try from 00ad9167 to 00ad916b has its CatchHandler @ 00adced5 */
  CEGUI::String::grow((ulong)&local_cc8);
  puVar18 = local_ca0;
  if (0x20 < local_cc0) {
    puVar18 = local_c20;
  }
  puVar18[lVar12] = 0;
  if (lVar12 != 0) {
    lVar29 = lVar12;
    do {
      lVar29 = lVar29 + -1;
      puVar18 = local_ca0;
      if (0x20 < local_cc0) {
        puVar18 = local_c20;
      }
      puVar18[lVar29] = (uint)*(byte *)(local_3d0 + lVar29);
    } while (lVar29 != 0);
  }
  local_cc8 = lVar12;
                    /* try { // try from 00ad91e4 to 00ad91e8 has its CatchHandler @ 00adceda */
  uVar11 = CEGUI::WindowManager::loadWindowLayout
                     (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,
                      SUB81((String *)&local_cc8,0));
  *(undefined8 *)(this + 0x58) = uVar11;
                    /* try { // try from 00ad91f0 to 00ad92b6 has its CatchHandler @ 00adced5 */
  CEGUI::String::~String((String *)&local_cc8);
  CGameUI::convertToScreenScale(*(CGameUI **)(this + 0xa8),*(Window **)(this + 0x58),false);
  CGameUI::mapToFunctions(*(CGameUI **)(this + 0xa8),*(Window **)(this + 0x58));
  mapEventHandlers(this,*(Window **)(this + 0x58));
  CEGUI::Window::addChildWindow(*(Window **)(this + 0x50));
  *(undefined1 *)(*(long *)(this + 0x58) + 0x3e2) = 1;
  CEGUI::Window::moveToFront();
  CEGUI::Window::setZOrderingEnabled(SUB81(*(undefined8 *)(this + 0x58),0));
  local_d70 = 0x20;
  local_d68 = 0;
  local_d58 = 0;
  local_d60 = 0;
  local_cd0 = (uint *)0x0;
  local_d78 = 0;
  local_d50[0] = 0;
  CEGUI::String::grow((ulong)&local_d78);
  puVar19 = local_d50;
  if (0x20 < local_d70) {
    puVar19 = local_cd0;
  }
  pbVar16 = (byte *)0xff197a;
  do {
    bVar3 = *pbVar16;
    pbVar16 = pbVar16 + 1;
    *puVar19 = (uint)bVar3;
    puVar19 = puVar19 + 1;
  } while (pbVar16 != (byte *)0xff197f);
  local_d78 = 5;
  puVar19 = local_d3c;
  if (0x20 < local_d70) {
    puVar19 = local_cd0 + 5;
  }
  *puVar19 = 0;
                    /* try { // try from 00ad9321 to 00ad9325 has its CatchHandler @ 00adcdf3 */
  uVar11 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x58));
  *(undefined8 *)(this + 0x70) = uVar11;
                    /* try { // try from 00ad932d to 00ad9396 has its CatchHandler @ 00adced5 */
  CEGUI::String::~String((String *)&local_d78);
  local_f80 = 0x20;
  local_f78 = 0;
  local_f68 = 0;
  local_f70 = 0;
  local_ee0 = (undefined4 *)0x0;
  local_f88 = 0;
  local_f60[0] = 0;
  CEGUI::String::grow((ulong)&local_f88);
  local_f88 = 0;
  puVar18 = local_f60;
  if (0x20 < local_f80) {
    puVar18 = local_ee0;
  }
  *puVar18 = 0;
                    /* try { // try from 00ad93d5 to 00ad93d9 has its CatchHandler @ 00adce03 */
  std::string::string((string *)local_98,"gui_",&local_3a);
                    /* try { // try from 00ad93ea to 00ad93ee has its CatchHandler @ 00adce0d */
  STRINGS::uniqueName((STRINGS *)local_a8,(string *)local_98);
  local_ed0 = 0x20;
  local_ec8 = 0;
  local_eb8 = 0;
  local_ec0 = 0;
  local_e30 = (undefined4 *)0x0;
  local_ed8 = 0;
  local_eb0[0] = 0;
  lVar12 = *(long *)(local_a8[0] + -0x18);
                    /* try { // try from 00ad945c to 00ad9460 has its CatchHandler @ 00adce17 */
  CEGUI::String::grow((ulong)&local_ed8);
  puVar18 = local_eb0;
  if (0x20 < local_ed0) {
    puVar18 = local_e30;
  }
  puVar18[lVar12] = 0;
  if (lVar12 != 0) {
    lVar29 = lVar12;
    do {
      lVar29 = lVar29 + -1;
      puVar18 = local_eb0;
      if (0x20 < local_ed0) {
        puVar18 = local_e30;
      }
      puVar18[lVar29] = (uint)*(byte *)(local_a8[0] + lVar29);
    } while (lVar29 != 0);
  }
  pcVar27 = (char *)0x0;
  local_e20 = 0x20;
  local_e18 = 0;
  local_e08 = 0;
  pcVar31 = "GuiLook/StaticImage";
  local_e10 = 0;
  local_d80 = (uint *)0x0;
  local_e28 = 0;
  local_e00[0] = 0;
  cVar2 = s_GuiLook_StaticImage_00fd0bff[0];
  while (pcVar31 = pcVar31 + 1, cVar2 != '\0') {
    pcVar27 = pcVar31 + -0xfd0bff;
    cVar2 = *pcVar31;
  }
  local_ed8 = lVar12;
  if (pcVar27 == CEGUI::String::npos) {
                    /* try { // try from 00adc87e to 00adc882 has its CatchHandler @ 00adcffa */
    std::string::string((string *)local_1d8,"Length for utf8 encoded string can not be \'npos\'",
                        local_4b);
    plVar22 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00adc896 to 00adc89a has its CatchHandler @ 00adcfe0 */
    std::length_error::length_error(plVar22,(string *)local_1d8);
    if ((allocator *)(local_1d8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_1d8[0] + -8);
      iVar6 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar6 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_1d8[0] + -0x18));
      }
    }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00adc8c1 to 00adc8c5 has its CatchHandler @ 00adcf07 */
    __cxa_throw(plVar22,&std::length_error::typeinfo,std::length_error::~length_error);
  }
  lVar12 = 0;
  pcVar31 = pcVar27;
  pbVar16 = (byte *)"GuiLook/StaticImage";
  while (pcVar31 != (char *)0x0) {
    bVar3 = *pbVar16;
    pcVar13 = pcVar31 + -1;
    pbVar25 = pbVar16 + 1;
    if ((char)bVar3 < '\0') {
      if (bVar3 < 0xe0) {
        pcVar13 = pcVar31 + -2;
        pbVar25 = pbVar16 + 2;
      }
      else if (bVar3 < 0xf0) {
        pcVar13 = pcVar31 + -3;
        pbVar25 = pbVar16 + 3;
      }
      else {
        pcVar13 = pcVar31 + -3;
        pbVar25 = pbVar16 + 4;
      }
    }
    lVar12 = lVar12 + 1;
    pcVar31 = pcVar13;
    pbVar16 = pbVar25;
  }
                    /* try { // try from 00ad969e to 00ad96a2 has its CatchHandler @ 00adcf07 */
  CEGUI::String::grow((ulong)&local_e28);
  if (local_e20 < 0x21) {
    puVar19 = local_e00;
    if (pcVar27 == (char *)0x0) goto LAB_00ada240;
LAB_00ad96c2:
    bVar32 = local_e20 != 0;
LAB_00ad96c8:
    if (bVar32) {
      pcVar31 = (char *)0x0;
      uVar9 = 0;
      uVar23 = local_e20;
      do {
        bVar3 = pcVar31[0xfd0bff];
        uVar10 = (uint)bVar3;
        uVar8 = uVar9 + 1;
        if ((char)bVar3 < '\0') {
          uVar10 = (uint)bVar3;
          if (0xdf < bVar3) {
            if (bVar3 < 0xf0) {
              uVar26 = (ulong)uVar8;
              uVar8 = uVar9 + 3;
              uVar10 = (byte)"GuiLook/StaticImage"[uVar9 + 2] & 0x3f | (uVar10 & 0xf) << 0xc |
                       ((byte)"GuiLook/StaticImage"[uVar26] & 0x3f) << 6;
            }
            else {
              uVar26 = (ulong)uVar8;
              uVar8 = uVar9 + 4;
              uVar10 = ((byte)"GuiLook/StaticImage"[uVar26] & 0x3f) << 0xc |
                       (byte)"GuiLook/StaticImage"[uVar9 + 3] & 0x3f | (uVar10 & 7) << 0x12 |
                       ((byte)"GuiLook/StaticImage"[uVar9 + 2] & 0x3f) << 6;
            }
            goto LAB_00ad96db;
          }
          uVar9 = uVar9 + 2;
          *puVar19 = (byte)"GuiLook/StaticImage"[uVar8] & 0x3f | (uVar10 & 0x1f) << 6;
        }
        else {
LAB_00ad96db:
          *puVar19 = uVar10;
          uVar9 = uVar8;
        }
        pcVar31 = (char *)(ulong)uVar9;
        if ((pcVar27 <= pcVar31) || (uVar23 = uVar23 - 1, uVar23 == 0)) break;
        puVar19 = puVar19 + 1;
      } while( true );
    }
  }
  else {
    puVar19 = local_d80;
    if (pcVar27 != (char *)0x0) goto LAB_00ad96c2;
LAB_00ada240:
    pcVar31 = "GuiLook/StaticImage";
    if (s_GuiLook_StaticImage_00fd0bff[0] != '\0') {
      do {
        pcVar31 = pcVar31 + 1;
        pcVar27 = pcVar31 + -0xfd0bff;
      } while (*pcVar31 != '\0');
      bVar32 = pcVar27 != (char *)0x0 && local_e20 != 0;
      goto LAB_00ad96c8;
    }
  }
  puVar19 = local_e00;
  if (0x20 < local_e20) {
    puVar19 = local_d80;
  }
  puVar19[lVar12] = 0;
  local_e28 = lVar12;
                    /* try { // try from 00ad9767 to 00ad976b has its CatchHandler @ 00adcd54 */
  uVar11 = CEGUI::WindowManager::createWindow
                     (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,(String *)&local_e28,
                      (String *)&local_ed8);
  *(undefined8 *)(this + 0x1a0) = uVar11;
                    /* try { // try from 00ad9776 to 00ad977a has its CatchHandler @ 00adcf07 */
  CEGUI::String::~String((String *)&local_e28);
                    /* try { // try from 00ad977e to 00ad9782 has its CatchHandler @ 00adce17 */
  CEGUI::String::~String((String *)&local_ed8);
  if ((allocator *)(local_a8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_a8[0] + -8);
    iVar6 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar6 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
    }
  }
  if ((allocator *)(local_98[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_98[0] + -8);
    iVar6 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar6 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
    }
  }
                    /* try { // try from 00ad97b9 to 00ad9856 has its CatchHandler @ 00adced5 */
  CEGUI::String::~String((String *)&local_f88);
  CEGUI::EventSet::setMutedState((bool)((char)*(undefined8 *)(this + 0x1a0) + '8'));
  *(undefined1 *)(*(long *)(this + 0x1a0) + 0x3e2) = 1;
  *(undefined1 *)(*(long *)(this + 0x1a0) + 0x213) = 0;
  local_1030 = 0x20;
  local_1028 = 0;
  local_1018 = 0;
  local_1020 = 0;
  local_f90 = (uint *)0x0;
  local_1038 = 0;
  local_1010[0] = 0;
  CEGUI::String::grow((ulong)&local_1038);
  puVar19 = local_1010;
  if (0x20 < local_1030) {
    puVar19 = local_f90;
  }
  pbVar16 = (byte *)0xfe60e6;
  do {
    bVar3 = *pbVar16;
    pbVar16 = pbVar16 + 1;
    *puVar19 = (uint)bVar3;
    puVar19 = puVar19 + 1;
  } while (pbVar16 != (byte *)0xfe60ee);
  local_1038 = 8;
  puVar19 = local_ff0;
  if (0x20 < local_1030) {
    puVar19 = local_f90 + 8;
  }
  *puVar19 = 0;
                    /* try { // try from 00ad98c5 to 00ad98dc has its CatchHandler @ 00adcce4 */
  CEGUI::Imageset::getImage(*(String **)(this + 0x198));
  CEGUI::PropertyHelper::imageToString(local_10e8);
  local_1190 = 0x20;
  local_1188 = 0;
  local_1178 = 0;
  local_1180 = 0;
  local_10f0 = (uint *)0x0;
  local_1198 = 0;
  local_1170[0] = 0;
                    /* try { // try from 00ad9940 to 00ad9944 has its CatchHandler @ 00adccdd */
  CEGUI::String::grow((ulong)&local_1198);
  puVar19 = local_1170;
  if (0x20 < local_1190) {
    puVar19 = local_10f0;
  }
  pbVar16 = (byte *)0xfd0c0d;
  do {
    bVar3 = *pbVar16;
    pbVar16 = pbVar16 + 1;
    *puVar19 = (uint)bVar3;
    puVar19 = puVar19 + 1;
  } while (pbVar16 != (byte *)0xfd0c12);
  local_1198 = 5;
  puVar19 = local_115c;
  if (0x20 < local_1190) {
    puVar19 = local_10f0 + 5;
  }
  *puVar19 = 0;
                    /* try { // try from 00ad99b7 to 00ad99bb has its CatchHandler @ 00adccc6 */
  CEGUI::PropertySet::setProperty(*(String **)(this + 0x1a0),(String *)&local_1198);
                    /* try { // try from 00ad99bf to 00ad99c3 has its CatchHandler @ 00adccdd */
  CEGUI::String::~String((String *)&local_1198);
                    /* try { // try from 00ad99c7 to 00ad99cb has its CatchHandler @ 00adcce4 */
  CEGUI::String::~String((String *)local_10e8);
                    /* try { // try from 00ad99cf to 00ad9a8b has its CatchHandler @ 00adced5 */
  CEGUI::String::~String((String *)&local_1038);
  *(undefined4 *)(this + 0xe8) = 0xf;
  *(undefined4 *)(this + 0xec) = 0x10;
  *(undefined4 *)(this + 0xf0) = 0x11;
  *(undefined4 *)(this + 0xf4) = 0x12;
  *(undefined4 *)(this + 0xf8) = 0;
  *(undefined4 *)(this + 0xfc) = 1;
  *(undefined4 *)(this + 0x100) = 2;
  *(undefined4 *)(this + 0x104) = 3;
  local_1240 = 0x20;
  local_1238 = 0;
  local_1228 = 0;
  local_1230 = 0;
  local_11a0 = (uint *)0x0;
  local_1248 = 0;
  local_1220[0] = 0;
  CEGUI::String::grow((ulong)&local_1248);
  puVar19 = local_1220;
  if (0x20 < local_1240) {
    puVar19 = local_11a0;
  }
  pcVar31 = "Dialog";
  do {
    bVar3 = *pcVar31;
    pcVar31 = pcVar31 + 1;
    *puVar19 = (uint)bVar3;
    puVar19 = puVar19 + 1;
  } while ((byte *)pcVar31 != (byte *)0xfe605f);
  local_1248 = 6;
  puVar19 = local_1208;
  if (0x20 < local_1240) {
    puVar19 = local_11a0 + 6;
  }
  *puVar19 = 0;
                    /* try { // try from 00ad9af9 to 00ad9afd has its CatchHandler @ 00adccb4 */
  uVar11 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x58));
  *(undefined8 *)(this + 0x78) = uVar11;
                    /* try { // try from 00ad9b05 to 00ad9b71 has its CatchHandler @ 00adced5 */
  CEGUI::String::~String((String *)&local_1248);
  local_12f0 = 0x20;
  local_12e8 = 0;
  local_12d8 = 0;
  local_12e0 = 0;
  local_1250 = (uint *)0x0;
  local_12f8 = 0;
  local_12d0[0] = 0;
  CEGUI::String::grow((ulong)&local_12f8);
  puVar19 = local_12d0;
  if (0x20 < local_12f0) {
    puVar19 = local_1250;
  }
  pcVar31 = "Accept";
  do {
    bVar3 = *pcVar31;
    pcVar31 = pcVar31 + 1;
    *puVar19 = (uint)bVar3;
    puVar19 = puVar19 + 1;
  } while ((byte *)pcVar31 != (byte *)0xfe6058);
  local_12f8 = 6;
  puVar19 = local_12b8;
  if (0x20 < local_12f0) {
    puVar19 = local_1250 + 6;
  }
  *puVar19 = 0;
                    /* try { // try from 00ad9bd9 to 00ad9bdd has its CatchHandler @ 00adccb2 */
  uVar11 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x58));
  *(undefined8 *)(this + 0x80) = uVar11;
                    /* try { // try from 00ad9be8 to 00ad9c51 has its CatchHandler @ 00adced5 */
  CEGUI::String::~String((String *)&local_12f8);
  local_1500 = 0x20;
  local_14f8 = 0;
  local_14e8 = 0;
  local_14f0 = 0;
  local_1460 = (undefined4 *)0x0;
  local_1508 = 0;
  local_14e0[0] = 0;
  CEGUI::String::grow((ulong)&local_1508);
  local_1508 = 0;
  puVar18 = local_14e0;
  if (0x20 < local_1500) {
    puVar18 = local_1460;
  }
  *puVar18 = 0;
                    /* try { // try from 00ad9c8b to 00ad9c8f has its CatchHandler @ 00adccab */
  CEGUI::String::String(local_1458,(uchar *)"CombineerSockets");
                    /* try { // try from 00ad9ca0 to 00ad9ca4 has its CatchHandler @ 00adcca4 */
  CEGUI::String::String(local_13a8,(uchar *)"DefaultWindow");
                    /* try { // try from 00ad9cb5 to 00ad9cb9 has its CatchHandler @ 00adcc82 */
  uVar11 = CEGUI::WindowManager::createWindow
                     (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,local_13a8,local_1458);
  *(undefined8 *)(this + 0x60) = uVar11;
                    /* try { // try from 00ad9cc1 to 00ad9cc5 has its CatchHandler @ 00adcca4 */
  CEGUI::String::~String(local_13a8);
                    /* try { // try from 00ad9cc9 to 00ad9ccd has its CatchHandler @ 00adccab */
  CEGUI::String::~String(local_1458);
                    /* try { // try from 00ad9cd1 to 00ad9cf6 has its CatchHandler @ 00adced5 */
  CEGUI::String::~String((String *)&local_1508);
  CEGUI::Window::addChildWindow(*(Window **)(this + 0x58));
  CEGUI::Window::getSize();
                    /* try { // try from 00ad9cfe to 00ad9d02 has its CatchHandler @ 00adcc7f */
  CEGUI::Window::setSize(*(UVector2 **)(this + 0x60));
  local_1660 = 0x20;
  local_1658 = 0;
  local_1648 = 0;
  local_1650 = 0;
  local_15c0 = (uint *)0x0;
  local_1668 = 0;
  local_1640[0] = 0;
                    /* try { // try from 00ad9d66 to 00ad9d6a has its CatchHandler @ 00adced5 */
  CEGUI::String::grow((ulong)&local_1668);
  puVar19 = local_1640;
  if (0x20 < local_1660) {
    puVar19 = local_15c0;
  }
  pcVar31 = "False";
  do {
    bVar3 = *pcVar31;
    pcVar31 = pcVar31 + 1;
    *puVar19 = (uint)bVar3;
    puVar19 = puVar19 + 1;
  } while ((byte *)pcVar31 != (byte *)0xfe603f);
  local_1668 = 5;
  puVar19 = local_162c;
  if (0x20 < local_1660) {
    puVar19 = local_15c0 + 5;
  }
  *puVar19 = 0;
  local_15b0 = 0x20;
  local_15a8 = 0;
  local_1598 = 0;
  local_15a0 = 0;
  local_1510 = (uint *)0x0;
  local_15b8 = 0;
  local_1590[0] = 0;
                    /* try { // try from 00ad9e36 to 00ad9e3a has its CatchHandler @ 00adcc78 */
  CEGUI::String::grow((ulong)&local_15b8);
  puVar19 = local_1590;
  if (0x20 < local_15b0) {
    puVar19 = local_1510;
  }
  pcVar31 = "RiseOnClick";
  do {
    bVar3 = *pcVar31;
    pcVar31 = pcVar31 + 1;
    *puVar19 = (uint)bVar3;
    puVar19 = puVar19 + 1;
  } while ((byte *)pcVar31 != (byte *)0xfe6039);
  local_15b8 = 0xb;
  puVar19 = local_1564;
  if (0x20 < local_15b0) {
    puVar19 = local_1510 + 0xb;
  }
  *puVar19 = 0;
                    /* try { // try from 00ad9eac to 00ad9eb0 has its CatchHandler @ 00adcc5e */
  CEGUI::PropertySet::setProperty(*(String **)(this + 0x60),(String *)&local_15b8);
                    /* try { // try from 00ad9eb4 to 00ad9eb8 has its CatchHandler @ 00adcc78 */
  CEGUI::String::~String((String *)&local_15b8);
                    /* try { // try from 00ad9ebc to 00ad9ec0 has its CatchHandler @ 00adced5 */
  CEGUI::String::~String((String *)&local_1668);
  local_2a4 = 0;
  local_2a8 = 0;
  local_29c = 0;
  local_2a0 = 0;
                    /* try { // try from 00ad9ef9 to 00ad9efd has its CatchHandler @ 00adcc54 */
  CEGUI::Window::setPosition(*(UVector2 **)(this + 0x60));
  *(undefined1 *)(*(long *)(this + 0x60) + 0x3e2) = 1;
                    /* try { // try from 00ad9f0d to 00ad9f76 has its CatchHandler @ 00adced5 */
  CEGUI::Window::moveToFront();
  local_1870 = 0x20;
  local_1868 = 0;
  local_1858 = 0;
  local_1860 = 0;
  local_17d0 = (undefined4 *)0x0;
  local_1878 = 0;
  local_1850[0] = 0;
  CEGUI::String::grow((ulong)&local_1878);
  local_1878 = 0;
  puVar18 = local_1850;
  if (0x20 < local_1870) {
    puVar18 = local_17d0;
  }
  *puVar18 = 0;
  pcVar13 = (char *)0x0;
  pcVar31 = "CombineerSocketsO";
  local_17c0 = 0x20;
  local_17b8 = 0;
  local_17a8 = 0;
  local_17b0 = 0;
  pcVar27 = "CombineerSocketsO";
  local_1720 = (uint *)0x0;
  local_17c8 = 0;
  local_17a0[0] = 0;
  cVar2 = s_CombineerSocketsO_00fe6040[0];
  while (pcVar27 = pcVar27 + 1, cVar2 != '\0') {
    pcVar13 = pcVar27 + -0xfe6040;
    cVar2 = *pcVar27;
  }
  if (pcVar13 == CEGUI::String::npos) {
                    /* try { // try from 00adc93f to 00adc943 has its CatchHandler @ 00add33e */
    std::string::string((string *)local_1e8,"Length for utf8 encoded string can not be \'npos\'",
                        local_4f);
    plVar22 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00adc957 to 00adc95b has its CatchHandler @ 00add324 */
    std::length_error::length_error(plVar22,(string *)local_1e8);
    if ((allocator *)(local_1e8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_1e8[0] + -8);
      iVar6 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar6 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_1e8[0] + -0x18));
      }
    }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00adc983 to 00adc987 has its CatchHandler @ 00add465 */
    __cxa_throw(plVar22,&std::length_error::typeinfo,std::length_error::~length_error);
  }
  lVar12 = 0;
  pcVar27 = pcVar13;
  pbVar16 = (byte *)"CombineerSocketsO";
  while (pcVar27 != (char *)0x0) {
    bVar3 = *pbVar16;
    pcVar14 = pcVar27 + -1;
    pbVar25 = pbVar16 + 1;
    if ((char)bVar3 < '\0') {
      if (bVar3 < 0xe0) {
        pcVar14 = pcVar27 + -2;
        pbVar25 = pbVar16 + 2;
      }
      else if (bVar3 < 0xf0) {
        pcVar14 = pcVar27 + -3;
        pbVar25 = pbVar16 + 3;
      }
      else {
        pcVar14 = pcVar27 + -3;
        pbVar25 = pbVar16 + 4;
      }
    }
    lVar12 = lVar12 + 1;
    pcVar27 = pcVar14;
    pbVar16 = pbVar25;
  }
                    /* try { // try from 00ada2fe to 00ada302 has its CatchHandler @ 00add465 */
  CEGUI::String::grow((ulong)&local_17c8);
  puVar19 = local_17a0;
  if (0x20 < local_17c0) {
    puVar19 = local_1720;
  }
  if (pcVar13 == (char *)0x0) {
    if (s_CombineerSocketsO_00fe6040[0] != '\0') {
      do {
        pcVar31 = pcVar31 + 1;
        pcVar13 = pcVar31 + -0xfe6040;
      } while (*pcVar31 != '\0');
      bVar32 = pcVar13 != (char *)0x0 && local_17c0 != 0;
      goto LAB_00ada32c;
    }
  }
  else {
    bVar32 = local_17c0 != 0;
LAB_00ada32c:
    if (bVar32) {
      pcVar31 = (char *)0x0;
      uVar9 = 0;
      uVar23 = local_17c0;
      do {
        bVar3 = pcVar31[0xfe6040];
        uVar10 = (uint)bVar3;
        uVar8 = uVar9 + 1;
        if ((char)bVar3 < '\0') {
          uVar10 = (uint)bVar3;
          if (0xdf < bVar3) {
            if (bVar3 < 0xf0) {
              uVar26 = (ulong)uVar8;
              uVar8 = uVar9 + 3;
              uVar10 = (byte)"CombineerSocketsO"[uVar9 + 2] & 0x3f | (uVar10 & 0xf) << 0xc |
                       ((byte)"CombineerSocketsO"[uVar26] & 0x3f) << 6;
            }
            else {
              uVar26 = (ulong)uVar8;
              uVar8 = uVar9 + 4;
              uVar10 = ((byte)"CombineerSocketsO"[uVar26] & 0x3f) << 0xc |
                       (byte)"CombineerSocketsO"[uVar9 + 3] & 0x3f | (uVar10 & 7) << 0x12 |
                       ((byte)"CombineerSocketsO"[uVar9 + 2] & 0x3f) << 6;
            }
            goto LAB_00ada343;
          }
          uVar9 = uVar9 + 2;
          *puVar19 = (byte)"CombineerSocketsO"[uVar8] & 0x3f | (uVar10 & 0x1f) << 6;
        }
        else {
LAB_00ada343:
          *puVar19 = uVar10;
          uVar9 = uVar8;
        }
        pcVar31 = (char *)(ulong)uVar9;
        if ((pcVar13 <= pcVar31) || (uVar23 = uVar23 - 1, uVar23 == 0)) break;
        puVar19 = puVar19 + 1;
      } while( true );
    }
  }
  puVar19 = local_17a0;
  if (0x20 < local_17c0) {
    puVar19 = local_1720;
  }
  puVar19[lVar12] = 0;
  pcVar27 = (char *)0x0;
  local_1710 = 0x20;
  local_1708 = 0;
  pcVar31 = "DefaultWindow";
  local_16f8 = 0;
  local_1700 = 0;
  local_1670 = (uint *)0x0;
  local_1718 = 0;
  local_16f0[0] = 0;
  cVar2 = s_DefaultWindow_00fe499d[0];
  while (pcVar31 = pcVar31 + 1, cVar2 != '\0') {
    pcVar27 = pcVar31 + -0xfe499d;
    cVar2 = *pcVar31;
  }
  local_17c8 = lVar12;
  if (pcVar27 == CEGUI::String::npos) {
                    /* try { // try from 00adca01 to 00adca05 has its CatchHandler @ 00add772 */
    std::string::string((string *)local_1f8,"Length for utf8 encoded string can not be \'npos\'",
                        local_51);
    plVar22 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00adca19 to 00adca1d has its CatchHandler @ 00add758 */
    std::length_error::length_error(plVar22,(string *)local_1f8);
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
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00adca45 to 00adca49 has its CatchHandler @ 00adcb61 */
    __cxa_throw(plVar22,&std::length_error::typeinfo,std::length_error::~length_error);
  }
  lVar12 = 0;
  pcVar31 = pcVar27;
  pbVar16 = (byte *)"DefaultWindow";
  while (pcVar31 != (char *)0x0) {
    bVar3 = *pbVar16;
    pcVar13 = pcVar31 + -1;
    pbVar25 = pbVar16 + 1;
    if ((char)bVar3 < '\0') {
      if (bVar3 < 0xe0) {
        pcVar13 = pcVar31 + -2;
        pbVar25 = pbVar16 + 2;
      }
      else if (bVar3 < 0xf0) {
        pcVar13 = pcVar31 + -3;
        pbVar25 = pbVar16 + 3;
      }
      else {
        pcVar13 = pcVar31 + -3;
        pbVar25 = pbVar16 + 4;
      }
    }
    lVar12 = lVar12 + 1;
    pcVar31 = pcVar13;
    pbVar16 = pbVar25;
  }
                    /* try { // try from 00ada4fe to 00ada502 has its CatchHandler @ 00adcb61 */
  CEGUI::String::grow((ulong)&local_1718);
  puVar19 = local_16f0;
  if (0x20 < local_1710) {
    puVar19 = local_1670;
  }
  if (pcVar27 == (char *)0x0) {
    if (s_DefaultWindow_00fe499d[0] == '\0') goto LAB_00ada5a0;
    do {
      pcVar28 = pcVar28 + 1;
      pcVar27 = pcVar28 + -0xfe499d;
    } while (*pcVar28 != '\0');
    bVar32 = pcVar27 != (char *)0x0 && local_1710 != 0;
  }
  else {
    bVar32 = local_1710 != 0;
  }
  if (bVar32) {
    pcVar31 = (char *)0x0;
    uVar9 = 0;
    uVar23 = local_1710;
    do {
      bVar3 = pcVar31[0xfe499d];
      uVar10 = (uint)bVar3;
      uVar8 = uVar9 + 1;
      if ((char)bVar3 < '\0') {
        uVar10 = (uint)bVar3;
        if (0xdf < bVar3) {
          if (bVar3 < 0xf0) {
            uVar26 = (ulong)uVar8;
            uVar8 = uVar9 + 3;
            uVar10 = (byte)"DefaultWindow"[uVar9 + 2] & 0x3f | (uVar10 & 0xf) << 0xc |
                     ((byte)"DefaultWindow"[uVar26] & 0x3f) << 6;
          }
          else {
            uVar26 = (ulong)uVar8;
            uVar8 = uVar9 + 4;
            uVar10 = ((byte)"DefaultWindow"[uVar26] & 0x3f) << 0xc |
                     (byte)"DefaultWindow"[uVar9 + 3] & 0x3f | (uVar10 & 7) << 0x12 |
                     ((byte)"DefaultWindow"[uVar9 + 2] & 0x3f) << 6;
          }
          goto LAB_00ada543;
        }
        uVar9 = uVar9 + 2;
        *puVar19 = (byte)"DefaultWindow"[uVar8] & 0x3f | (uVar10 & 0x1f) << 6;
      }
      else {
LAB_00ada543:
        *puVar19 = uVar10;
        uVar9 = uVar8;
      }
      pcVar31 = (char *)(ulong)uVar9;
      if ((pcVar27 <= pcVar31) || (uVar23 = uVar23 - 1, uVar23 == 0)) break;
      puVar19 = puVar19 + 1;
    } while( true );
  }
LAB_00ada5a0:
  puVar19 = local_16f0;
  if (0x20 < local_1710) {
    puVar19 = local_1670;
  }
  puVar19[lVar12] = 0;
  local_1718 = lVar12;
                    /* try { // try from 00ada5d7 to 00ada5db has its CatchHandler @ 00adcb42 */
  uVar11 = CEGUI::WindowManager::createWindow
                     (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,(String *)&local_1718,
                      (String *)&local_17c8);
  *(undefined8 *)(this + 0x68) = uVar11;
                    /* try { // try from 00ada5e3 to 00ada5e7 has its CatchHandler @ 00adcb61 */
  CEGUI::String::~String((String *)&local_1718);
                    /* try { // try from 00ada5eb to 00ada5ef has its CatchHandler @ 00add465 */
  CEGUI::String::~String((String *)&local_17c8);
                    /* try { // try from 00ada5f3 to 00ada618 has its CatchHandler @ 00adced5 */
  CEGUI::String::~String((String *)&local_1878);
  CEGUI::Window::addChildWindow(*(Window **)(this + 0x58));
  CEGUI::Window::getSize();
                    /* try { // try from 00ada620 to 00ada624 has its CatchHandler @ 00add455 */
  CEGUI::Window::setSize(*(UVector2 **)(this + 0x68));
  local_19d0 = 0x20;
  local_19c8 = 0;
  local_19b8 = 0;
  local_19c0 = 0;
  local_1930 = (uint *)0x0;
  local_19d8 = 0;
  local_19b0[0] = 0;
                    /* try { // try from 00ada688 to 00ada68c has its CatchHandler @ 00adced5 */
  CEGUI::String::grow((ulong)&local_19d8);
  puVar19 = local_19b0;
  if (0x20 < local_19d0) {
    puVar19 = local_1930;
  }
  pcVar31 = "False";
  do {
    bVar3 = *pcVar31;
    pcVar31 = pcVar31 + 1;
    *puVar19 = (uint)bVar3;
    puVar19 = puVar19 + 1;
  } while ((byte *)pcVar31 != (byte *)0xfe603f);
  local_19d8 = 5;
  puVar19 = local_199c;
  if (0x20 < local_19d0) {
    puVar19 = local_1930 + 5;
  }
  *puVar19 = 0;
  local_1920 = 0x20;
  local_1918 = 0;
  local_1908 = 0;
  local_1910 = 0;
  local_1880 = (uint *)0x0;
  local_1928 = 0;
  local_1900[0] = 0;
                    /* try { // try from 00ada758 to 00ada75c has its CatchHandler @ 00add446 */
  CEGUI::String::grow((ulong)&local_1928);
  puVar19 = local_1900;
  if (0x20 < local_1920) {
    puVar19 = local_1880;
  }
  pcVar31 = "RiseOnClick";
  do {
    bVar3 = *pcVar31;
    pcVar31 = pcVar31 + 1;
    *puVar19 = (uint)bVar3;
    puVar19 = puVar19 + 1;
  } while ((byte *)pcVar31 != (byte *)0xfe6039);
  local_1928 = 0xb;
  puVar19 = local_18d4;
  if (0x20 < local_1920) {
    puVar19 = local_1880 + 0xb;
  }
  *puVar19 = 0;
                    /* try { // try from 00ada7cc to 00ada7d0 has its CatchHandler @ 00add441 */
  CEGUI::PropertySet::setProperty(*(String **)(this + 0x68),(String *)&local_1928);
                    /* try { // try from 00ada7d4 to 00ada7d8 has its CatchHandler @ 00add446 */
  CEGUI::String::~String((String *)&local_1928);
                    /* try { // try from 00ada7dc to 00ada7e0 has its CatchHandler @ 00adced5 */
  CEGUI::String::~String((String *)&local_19d8);
  local_2c4 = 0;
  local_2c8 = 0;
  local_2bc = 0;
  local_2c0 = 0;
                    /* try { // try from 00ada819 to 00ada81d has its CatchHandler @ 00add43c */
  CEGUI::Window::setPosition(*(UVector2 **)(this + 0x68));
  *(undefined1 *)(*(long *)(this + 0x68) + 0x3e2) = 1;
                    /* try { // try from 00ada82d to 00ada881 has its CatchHandler @ 00adced5 */
  CEGUI::Window::moveToFront();
  pCVar30 = this;
  uVar9 = 0;
  do {
    uVar8 = uVar9 + 1;
    STRINGS::GetValueAsString((uint)local_b8);
                    /* try { // try from 00ada897 to 00ada89b has its CatchHandler @ 00add42a */
    std::operator+((char *)local_c8,(string *)"ItemSlot");
    local_1a80 = 0x20;
    local_1a78 = 0;
    local_1a68 = 0;
    local_1a70 = 0;
    local_19e0 = (undefined4 *)0x0;
    local_1a88 = 0;
    local_1a60[0] = 0;
    lVar12 = *(long *)(local_c8[0] + -0x18);
                    /* try { // try from 00ada906 to 00ada90a has its CatchHandler @ 00add3e4 */
    CEGUI::String::grow((ulong)&local_1a88);
    puVar18 = local_1a60;
    if (0x20 < local_1a80) {
      puVar18 = local_19e0;
    }
    puVar18[lVar12] = 0;
    lVar29 = lVar12;
    while (lVar29 != 0) {
      lVar29 = lVar29 + -1;
      puVar18 = local_1a60;
      if (0x20 < local_1a80) {
        puVar18 = local_19e0;
      }
      puVar18[lVar29] = (uint)*(byte *)(local_c8[0] + lVar29);
    }
    local_1a88 = lVar12;
                    /* try { // try from 00ada983 to 00ada987 has its CatchHandler @ 00add408 */
    lVar12 = CEGUI::Window::recursiveChildSearch(*(String **)(this + 0x58));
                    /* try { // try from 00ada993 to 00ada997 has its CatchHandler @ 00add3e4 */
    CEGUI::String::~String((String *)&local_1a88);
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
                    /* try { // try from 00ada9cf to 00adaa16 has its CatchHandler @ 00adced5 */
    CEGUI::Window::moveToFront();
    *(undefined1 *)(lVar12 + 0x213) = 0;
    CEGUI::Window::setWantsMultiClickEvents(SUB81(lVar12,0));
    *(CCombineMenu **)(lVar12 + 0x1d8) = this + (ulong)uVar9 * 4 + 0xf8;
    CEGUI::Window::setAlwaysOnTop(SUB81(lVar12,0));
    pcVar4 = *(code **)(*(long *)(lVar12 + 0x38) + 0x10);
    local_d8[0] = operator_new(0x20);
    lVar29 = lVar12 + 0x38;
    *local_d8[0] = &PTR__MemberFunctionSlot_00fe6410;
    local_d8[0][2] = 0;
    local_d8[0][1] = handle_ItemClick;
    local_d8[0][3] = this;
                    /* try { // try from 00adaa59 to 00adaa8e has its CatchHandler @ 00add375 */
    (*pcVar4)(&local_2d8,lVar29,CEGUI::Window::EventMouseButtonDown,(SubscriberSlot *)local_d8);
    pBVar5 = local_2d8;
    if ((local_2d8 != (BoundSlot *)0x0) &&
       (iVar6 = *local_2d0, *local_2d0 = iVar6 + -1, iVar6 + -1 == 0)) {
      if (local_2d8 != (BoundSlot *)0x0) {
        CEGUI::BoundSlot::~BoundSlot(local_2d8);
        operator_delete(pBVar5);
      }
      operator_delete(local_2d0);
      local_2d8 = (BoundSlot *)0x0;
      local_2d0 = (int *)0x0;
    }
                    /* try { // try from 00adaabf to 00adaad5 has its CatchHandler @ 00adced5 */
    CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_d8);
    pcVar4 = *(code **)(*(long *)(lVar12 + 0x38) + 0x10);
    local_e8[0] = operator_new(0x20);
    *local_e8[0] = &PTR__MemberFunctionSlot_00fe6410;
    local_e8[0][2] = 0;
    local_e8[0][1] = handle_MouseOver;
    local_e8[0][3] = this;
                    /* try { // try from 00adab14 to 00adab49 has its CatchHandler @ 00add36b */
    (*pcVar4)(&local_2e8,lVar29,CEGUI::Window::EventMouseEnters,(SubscriberSlot *)local_e8);
    pBVar5 = local_2e8;
    if ((local_2e8 != (BoundSlot *)0x0) &&
       (iVar6 = *local_2e0, *local_2e0 = iVar6 + -1, iVar6 + -1 == 0)) {
      if (local_2e8 != (BoundSlot *)0x0) {
        CEGUI::BoundSlot::~BoundSlot(local_2e8);
        operator_delete(pBVar5);
      }
      operator_delete(local_2e0);
      local_2e8 = (BoundSlot *)0x0;
      local_2e0 = (int *)0x0;
    }
                    /* try { // try from 00adab7a to 00adab90 has its CatchHandler @ 00adced5 */
    CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_e8);
    pcVar4 = *(code **)(*(long *)(lVar12 + 0x38) + 0x10);
    local_f8[0] = operator_new(0x20);
    *local_f8[0] = &PTR__MemberFunctionSlot_00fe6410;
    local_f8[0][2] = 0;
    local_f8[0][1] = handle_MouseOver;
    local_f8[0][3] = this;
                    /* try { // try from 00adabcf to 00adac04 has its CatchHandler @ 00add366 */
    (*pcVar4)(&local_2f8,lVar29,CEGUI::Window::EventMouseMove,(SubscriberSlot *)local_f8);
    pBVar5 = local_2f8;
    if ((local_2f8 != (BoundSlot *)0x0) &&
       (iVar6 = *local_2f0, *local_2f0 = iVar6 + -1, iVar6 + -1 == 0)) {
      if (local_2f8 != (BoundSlot *)0x0) {
        CEGUI::BoundSlot::~BoundSlot(local_2f8);
        operator_delete(pBVar5);
      }
      operator_delete(local_2f0);
      local_2f8 = (BoundSlot *)0x0;
      local_2f0 = (int *)0x0;
    }
                    /* try { // try from 00adac35 to 00adac4b has its CatchHandler @ 00adced5 */
    CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_f8);
    pcVar4 = *(code **)(*(long *)(lVar12 + 0x38) + 0x10);
    local_108[0] = operator_new(0x20);
    *local_108[0] = &PTR__MemberFunctionSlot_00fe6410;
    local_108[0][2] = 0;
    local_108[0][1] = handle_MouseOut;
    local_108[0][3] = this;
                    /* try { // try from 00adac8a to 00adacbf has its CatchHandler @ 00add2a9 */
    (*pcVar4)(&local_308,lVar29,CEGUI::Window::EventMouseLeaves,(SubscriberSlot *)local_108);
    pBVar5 = local_308;
    if ((local_308 != (BoundSlot *)0x0) &&
       (iVar6 = *local_300, *local_300 = iVar6 + -1, iVar6 + -1 == 0)) {
      if (local_308 != (BoundSlot *)0x0) {
        CEGUI::BoundSlot::~BoundSlot(local_308);
        operator_delete(pBVar5);
      }
      operator_delete(local_300);
      local_308 = (BoundSlot *)0x0;
      local_300 = (int *)0x0;
    }
                    /* try { // try from 00adacf0 to 00adad70 has its CatchHandler @ 00adced5 */
    CEGUI::SubscriberSlot::~SubscriberSlot((SubscriberSlot *)local_108);
    CEGUI::Window::moveToFront();
    *(long *)(pCVar30 + 0x148) = lVar12;
    *(undefined8 *)(pCVar30 + 0x168) = 0;
    local_1c90 = 0x20;
    local_1c88 = 0;
    local_1c78 = 0;
    local_1c80 = 0;
    local_1bf0 = (undefined4 *)0x0;
    local_1c98 = 0;
    local_1c70[0] = 0;
    CEGUI::String::grow((ulong)&local_1c98);
    local_1c98 = 0;
    puVar18 = local_1bf0;
    if (local_1c90 < 0x21) {
      puVar18 = local_1c70;
    }
    *puVar18 = 0;
                    /* try { // try from 00adadb3 to 00adadb7 has its CatchHandler @ 00add29f */
    std::string::string((string *)local_118,"gui_",&local_3b);
                    /* try { // try from 00adadc8 to 00adadcc has its CatchHandler @ 00add295 */
    STRINGS::uniqueName((STRINGS *)local_128,(string *)local_118);
    local_1be0 = 0x20;
    local_1bd8 = 0;
    local_1bc8 = 0;
    local_1bd0 = 0;
    local_1b40 = (undefined4 *)0x0;
    local_1be8 = 0;
    local_1bc0[0] = 0;
    lVar12 = *(long *)(local_128[0] + -0x18);
                    /* try { // try from 00adae37 to 00adae3b has its CatchHandler @ 00add28a */
    CEGUI::String::grow((ulong)&local_1be8);
    puVar18 = local_1bc0;
    if (0x20 < local_1be0) {
      puVar18 = local_1b40;
    }
    puVar18[lVar12] = 0;
    lVar29 = lVar12;
    while (lVar29 != 0) {
      lVar29 = lVar29 + -1;
      puVar18 = local_1bc0;
      if (0x20 < local_1be0) {
        puVar18 = local_1b40;
      }
      puVar18[lVar29] = (uint)*(byte *)(local_128[0] + lVar29);
    }
    pcVar28 = (char *)0x0;
    pcVar27 = "GuiLook/StaticText";
    local_1b30 = 0x20;
    local_1b28 = 0;
    pcVar31 = "GuiLook/StaticText";
    local_1b18 = 0;
    local_1b20 = 0;
    local_1a90 = (uint *)0x0;
    local_1b38 = 0;
    local_1b10[0] = 0;
    cVar2 = s_GuiLook_StaticText_00fe4872[0];
    while (pcVar31 = pcVar31 + 1, cVar2 != '\0') {
      pcVar28 = pcVar31 + -0xfe4872;
      cVar2 = *pcVar31;
    }
    local_1be8 = lVar12;
    if (pcVar28 == CEGUI::String::npos) {
                    /* try { // try from 00adc8de to 00adc8e2 has its CatchHandler @ 00adcfad */
      std::string::string((string *)local_208,"Length for utf8 encoded string can not be \'npos\'",
                          local_55);
      plVar22 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00adc8f6 to 00adc8fa has its CatchHandler @ 00adcf44 */
      std::length_error::length_error(plVar22,(string *)local_208);
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
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00adc922 to 00adc926 has its CatchHandler @ 00add285 */
      __cxa_throw(plVar22,&std::length_error::typeinfo,std::length_error::~length_error);
    }
    lVar12 = 0;
    pcVar31 = pcVar28;
    pbVar16 = (byte *)"GuiLook/StaticText";
    while (pcVar31 != (char *)0x0) {
      bVar3 = *pbVar16;
      pcVar13 = pcVar31 + -1;
      pbVar25 = pbVar16 + 1;
      if ((char)bVar3 < '\0') {
        if (bVar3 < 0xe0) {
          pcVar13 = pcVar31 + -2;
          pbVar25 = pbVar16 + 2;
        }
        else if (bVar3 < 0xf0) {
          pcVar13 = pcVar31 + -3;
          pbVar25 = pbVar16 + 3;
        }
        else {
          pcVar13 = pcVar31 + -3;
          pbVar25 = pbVar16 + 4;
        }
      }
      lVar12 = lVar12 + 1;
      pcVar31 = pcVar13;
      pbVar16 = pbVar25;
    }
                    /* try { // try from 00adafdb to 00adafdf has its CatchHandler @ 00add285 */
    CEGUI::String::grow((ulong)&local_1b38);
    puVar19 = local_1a90;
    if (local_1b30 < 0x21) {
      puVar19 = local_1b10;
    }
    if (pcVar28 == (char *)0x0) {
      if (s_GuiLook_StaticText_00fe4872[0] != '\0') {
        do {
          pcVar27 = pcVar27 + 1;
          pcVar28 = pcVar27 + -0xfe4872;
        } while (*pcVar27 != '\0');
        bVar32 = pcVar28 != (char *)0x0 && local_1b30 != 0;
        goto LAB_00adb00d;
      }
    }
    else {
      bVar32 = local_1b30 != 0;
LAB_00adb00d:
      if (bVar32) {
        pcVar31 = (char *)0x0;
        uVar9 = 0;
        uVar23 = local_1b30;
        do {
          bVar3 = pcVar31[0xfe4872];
          uVar24 = (uint)bVar3;
          uVar10 = uVar9 + 1;
          if ((char)bVar3 < '\0') {
            uVar24 = (uint)bVar3;
            if (0xdf < bVar3) {
              if (bVar3 < 0xf0) {
                uVar26 = (ulong)uVar10;
                uVar10 = uVar9 + 3;
                uVar24 = (byte)"GuiLook/StaticText"[uVar9 + 2] & 0x3f | (uVar24 & 0xf) << 0xc |
                         ((byte)"GuiLook/StaticText"[uVar26] & 0x3f) << 6;
              }
              else {
                uVar26 = (ulong)uVar10;
                uVar10 = uVar9 + 4;
                uVar24 = ((byte)"GuiLook/StaticText"[uVar26] & 0x3f) << 0xc |
                         (byte)"GuiLook/StaticText"[uVar9 + 3] & 0x3f | (uVar24 & 7) << 0x12 |
                         ((byte)"GuiLook/StaticText"[uVar9 + 2] & 0x3f) << 6;
              }
              goto LAB_00adb023;
            }
            uVar9 = uVar9 + 2;
            *puVar19 = (byte)"GuiLook/StaticText"[uVar10] & 0x3f | (uVar24 & 0x1f) << 6;
          }
          else {
LAB_00adb023:
            *puVar19 = uVar24;
            uVar9 = uVar10;
          }
          pcVar31 = (char *)(ulong)uVar9;
          if ((pcVar28 <= pcVar31) || (uVar23 = uVar23 - 1, uVar23 == 0)) break;
          puVar19 = puVar19 + 1;
        } while( true );
      }
    }
    puVar19 = local_1a90;
    if (local_1b30 < 0x21) {
      puVar19 = local_1b10;
    }
    puVar19[lVar12] = 0;
    local_1b38 = lVar12;
                    /* try { // try from 00adb0ca to 00adb0ce has its CatchHandler @ 00add26e */
    uVar11 = CEGUI::WindowManager::createWindow
                       (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,(String *)&local_1b38,
                        (String *)&local_1be8);
    *(undefined8 *)(pCVar30 + 0x168) = uVar11;
                    /* try { // try from 00adb0de to 00adb0e2 has its CatchHandler @ 00add285 */
    CEGUI::String::~String((String *)&local_1b38);
                    /* try { // try from 00adb0eb to 00adb0ef has its CatchHandler @ 00add28a */
    CEGUI::String::~String((String *)&local_1be8);
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
                    /* try { // try from 00adb12c to 00adb198 has its CatchHandler @ 00adced5 */
    CEGUI::String::~String((String *)&local_1c98);
    local_1d40 = 0x20;
    local_1d38 = 0;
    local_1d28 = 0;
    local_1d30 = 0;
    local_1ca0 = (uint *)0x0;
    local_1d48 = 0;
    local_1d20[0] = 0;
    CEGUI::String::grow((ulong)&local_1d48);
    puVar19 = local_1d20;
    if (0x20 < local_1d40) {
      puVar19 = local_1ca0;
    }
    pcVar31 = "Serif";
    do {
      bVar3 = *pcVar31;
      pcVar31 = pcVar31 + 1;
      *puVar19 = (uint)bVar3;
      puVar19 = puVar19 + 1;
    } while ((byte *)pcVar31 != (byte *)0xfe4949);
    local_1d48 = 5;
    puVar19 = local_1d0c;
    if (0x20 < local_1d40) {
      puVar19 = local_1ca0 + 5;
    }
    *puVar19 = 0;
                    /* try { // try from 00adb20d to 00adb211 has its CatchHandler @ 00add2d5 */
    CEGUI::Window::setFont(*(String **)(pCVar30 + 0x168));
                    /* try { // try from 00adb215 to 00adb22c has its CatchHandler @ 00adced5 */
    CEGUI::String::~String((String *)&local_1d48);
    CEGUI::Window::getSize();
                    /* try { // try from 00adb237 to 00adb23b has its CatchHandler @ 00add2c5 */
    CEGUI::Window::setSize(*(UVector2 **)(pCVar30 + 0x168));
                    /* try { // try from 00adb23f to 00adb243 has its CatchHandler @ 00adced5 */
    puVar17 = (undefined8 *)CEGUI::Window::getPosition();
    local_328 = *puVar17;
    local_320 = puVar17[1];
    local_1ea0 = 0x20;
    local_1e98 = 0;
    local_1e88 = 0;
    local_1e90 = 0;
    local_1e00 = (uint *)0x0;
    local_1ea8 = 0;
    local_1e80[0] = 0;
                    /* try { // try from 00adb2be to 00adb2c2 has its CatchHandler @ 00add2c0 */
    CEGUI::String::grow((ulong)&local_1ea8);
    puVar19 = local_1e80;
    if (0x20 < local_1ea0) {
      puVar19 = local_1e00;
    }
    pcVar31 = "RightAligned";
    do {
      bVar3 = *pcVar31;
      pcVar31 = pcVar31 + 1;
      *puVar19 = (uint)bVar3;
      puVar19 = puVar19 + 1;
    } while ((byte *)pcVar31 != (byte *)0xfe602d);
    local_1ea8 = 0xc;
    puVar19 = local_1e50;
    if (0x20 < local_1ea0) {
      puVar19 = local_1e00 + 0xc;
    }
    *puVar19 = 0;
    local_1df0 = 0x20;
    local_1de8 = 0;
    local_1dd8 = 0;
    local_1de0 = 0;
    local_1d50 = (uint *)0x0;
    local_1df8 = 0;
    local_1dd0[0] = 0;
                    /* try { // try from 00adb385 to 00adb389 has its CatchHandler @ 00add2bb */
    CEGUI::String::grow((ulong)&local_1df8);
    puVar19 = local_1dd0;
    if (0x20 < local_1df0) {
      puVar19 = local_1d50;
    }
    pcVar31 = "HorzTextFormatting";
    do {
      bVar3 = *pcVar31;
      pcVar31 = pcVar31 + 1;
      *puVar19 = (uint)bVar3;
      puVar19 = puVar19 + 1;
    } while ((byte *)pcVar31 != (byte *)0xfe48cf);
    local_1df8 = 0x12;
    puVar19 = local_1d88;
    if (0x20 < local_1df0) {
      puVar19 = local_1d50 + 0x12;
    }
    *puVar19 = 0;
                    /* try { // try from 00adb400 to 00adb404 has its CatchHandler @ 00adcbc5 */
    CEGUI::PropertySet::setProperty(*(String **)(pCVar30 + 0x168),(String *)&local_1df8);
                    /* try { // try from 00adb408 to 00adb40c has its CatchHandler @ 00add2bb */
    CEGUI::String::~String((String *)&local_1df8);
                    /* try { // try from 00adb410 to 00adb47c has its CatchHandler @ 00add2c0 */
    CEGUI::String::~String((String *)&local_1ea8);
    local_2000 = 0x20;
    local_1ff8 = 0;
    local_1fe8 = 0;
    local_1ff0 = 0;
    local_1f60 = (uint *)0x0;
    local_2008 = 0;
    local_1fe0[0] = 0;
    CEGUI::String::grow((ulong)&local_2008);
    puVar19 = local_1fe0;
    if (0x20 < local_2000) {
      puVar19 = local_1f60;
    }
    pcVar31 = "BottomAligned";
    do {
      bVar3 = *pcVar31;
      pcVar31 = pcVar31 + 1;
      *puVar19 = (uint)bVar3;
      puVar19 = puVar19 + 1;
    } while ((byte *)pcVar31 != (byte *)0xfe6020);
    local_2008 = 0xd;
    puVar19 = local_1fac;
    if (0x20 < local_2000) {
      puVar19 = local_1f60 + 0xd;
    }
    *puVar19 = 0;
    local_1f50 = 0x20;
    local_1f48 = 0;
    local_1f38 = 0;
    local_1f40 = 0;
    local_1eb0 = (uint *)0x0;
    local_1f58 = 0;
    local_1f30[0] = 0;
                    /* try { // try from 00adb545 to 00adb549 has its CatchHandler @ 00adcb0c */
    CEGUI::String::grow((ulong)&local_1f58);
    puVar19 = local_1f30;
    if (0x20 < local_1f50) {
      puVar19 = local_1eb0;
    }
    pcVar31 = "VertFormatting";
    do {
      bVar3 = *pcVar31;
      pcVar31 = pcVar31 + 1;
      *puVar19 = (uint)bVar3;
      puVar19 = puVar19 + 1;
    } while ((byte *)pcVar31 != (byte *)0xfe48ae);
    local_1f58 = 0xe;
    puVar19 = local_1ef8;
    if (0x20 < local_1f50) {
      puVar19 = local_1eb0 + 0xe;
    }
    *puVar19 = 0;
                    /* try { // try from 00adb5c0 to 00adb5c4 has its CatchHandler @ 00add2e5 */
    CEGUI::PropertySet::setProperty(*(String **)(pCVar30 + 0x168),(String *)&local_1f58);
                    /* try { // try from 00adb5c8 to 00adb5cc has its CatchHandler @ 00adcb0c */
    CEGUI::String::~String((String *)&local_1f58);
                    /* try { // try from 00adb5d0 to 00adb683 has its CatchHandler @ 00add2c0 */
    CEGUI::String::~String((String *)&local_2008);
    *(undefined1 *)(*(long *)(pCVar30 + 0x168) + 0x3e2) = 1;
    CEGUI::Window::setPosition(*(UVector2 **)(pCVar30 + 0x168));
    CEGUI::Window::addChildWindow(*(Window **)(*(long *)(pCVar30 + 0x148) + 0xb0));
    local_20b0 = 0x20;
    local_20a8 = 0;
    local_2098 = 0;
    local_20a0 = 0;
    local_2010 = (undefined4 *)0x0;
    local_20b8 = 0;
    local_2090[0] = 0;
    if (CEGUI::String::npos == (char *)0x0) {
                    /* try { // try from 00adc9a0 to 00adc9a4 has its CatchHandler @ 00add4be */
      std::string::string((string *)local_218,"Length for utf8 encoded string can not be \'npos\'",
                          local_59);
      plVar22 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00adc9b8 to 00adc9bc has its CatchHandler @ 00add4a4 */
      std::length_error::length_error(plVar22,(string *)local_218);
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
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00adc9e4 to 00adc9e8 has its CatchHandler @ 00add2c0 */
      __cxa_throw(plVar22,&std::length_error::typeinfo,std::length_error::~length_error);
    }
    CEGUI::String::grow((ulong)&local_20b8);
    local_20b8 = 0;
    puVar18 = local_2090;
    if (0x20 < local_20b0) {
      puVar18 = local_2010;
    }
    *puVar18 = 0;
                    /* try { // try from 00adb6b8 to 00adb6bc has its CatchHandler @ 00add705 */
    CEGUI::Window::setText(*(String **)(pCVar30 + 0x168));
                    /* try { // try from 00adb6c0 to 00adb6f8 has its CatchHandler @ 00add2c0 */
    CEGUI::String::~String((String *)&local_20b8);
    CEGUI::colour::colour(local_378,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc);
    CEGUI::PropertyHelper::colourToString(local_2168);
    local_2210 = 0x20;
    local_2208 = 0;
    local_21f8 = 0;
    local_2200 = 0;
    local_2170 = (uint *)0x0;
    local_2218 = 0;
    local_21f0[0] = 0;
                    /* try { // try from 00adb75c to 00adb760 has its CatchHandler @ 00add6fe */
    CEGUI::String::grow((ulong)&local_2218);
    puVar19 = local_21f0;
    if (0x20 < local_2210) {
      puVar19 = local_2170;
    }
    pbVar16 = (byte *)0xfe4654;
    do {
      bVar3 = *pbVar16;
      pbVar16 = pbVar16 + 1;
      *puVar19 = (uint)bVar3;
      puVar19 = puVar19 + 1;
    } while (pbVar16 != (byte *)0xfe465e);
    local_2218 = 10;
    puVar19 = local_21c8;
    if (0x20 < local_2210) {
      puVar19 = local_2170 + 10;
    }
    *puVar19 = 0;
                    /* try { // try from 00adb7d0 to 00adb7d4 has its CatchHandler @ 00add6f9 */
    CEGUI::PropertySet::setProperty(*(String **)(pCVar30 + 0x168),(String *)&local_2218);
                    /* try { // try from 00adb7d8 to 00adb7dc has its CatchHandler @ 00add6fe */
    CEGUI::String::~String((String *)&local_2218);
                    /* try { // try from 00adb7e0 to 00adb857 has its CatchHandler @ 00add2c0 */
    CEGUI::String::~String(local_2168);
    CEGUI::Window::setAlwaysOnTop(SUB81(*(undefined8 *)(pCVar30 + 0x168),0));
    local_2420 = 0x20;
    local_2418 = 0;
    local_2408 = 0;
    local_2410 = 0;
    local_2380 = (undefined4 *)0x0;
    local_2428 = 0;
    local_2400[0] = 0;
    CEGUI::String::grow((ulong)&local_2428);
    local_2428 = 0;
    puVar18 = local_2380;
    if (local_2420 < 0x21) {
      puVar18 = local_2400;
    }
    *puVar18 = 0;
                    /* try { // try from 00adb89a to 00adb89e has its CatchHandler @ 00add6ef */
    std::string::string((string *)local_138,"gui_",&local_3c);
                    /* try { // try from 00adb8af to 00adb8b3 has its CatchHandler @ 00adcb96 */
    STRINGS::uniqueName((STRINGS *)local_148,(string *)local_138);
    local_2370 = 0x20;
    local_2368 = 0;
    local_2358 = 0;
    local_2360 = 0;
    local_22d0 = (undefined4 *)0x0;
    local_2378 = 0;
    local_2350[0] = 0;
    lVar12 = *(long *)(local_148[0] + -0x18);
                    /* try { // try from 00adb91e to 00adb922 has its CatchHandler @ 00adcb68 */
    CEGUI::String::grow((ulong)&local_2378);
    puVar18 = local_2350;
    if (0x20 < local_2370) {
      puVar18 = local_22d0;
    }
    puVar18[lVar12] = 0;
    lVar29 = lVar12;
    while (lVar29 != 0) {
      lVar29 = lVar29 + -1;
      puVar18 = local_2350;
      if (0x20 < local_2370) {
        puVar18 = local_22d0;
      }
      puVar18[lVar29] = (uint)*(byte *)(local_148[0] + lVar29);
    }
    pcVar28 = (char *)0x0;
    local_22c0 = 0x20;
    local_22b8 = 0;
    local_22a8 = 0;
    pcVar31 = "GuiLook/StaticImage";
    local_22b0 = 0;
    local_2220 = (uint *)0x0;
    local_22c8 = 0;
    local_22a0[0] = 0;
    cVar2 = s_GuiLook_StaticImage_00fd0bff[0];
    while (pcVar31 = pcVar31 + 1, cVar2 != '\0') {
      pcVar28 = pcVar31 + -0xfd0bff;
      cVar2 = *pcVar31;
    }
    local_2378 = lVar12;
    if (pcVar28 == CEGUI::String::npos) {
                    /* try { // try from 00adca62 to 00adca66 has its CatchHandler @ 00add86b */
      std::string::string((string *)local_228,"Length for utf8 encoded string can not be \'npos\'",
                          local_5b);
      plVar22 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00adca7a to 00adca7e has its CatchHandler @ 00add851 */
      std::length_error::length_error(plVar22,(string *)local_228);
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
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00adcaa6 to 00adcaaa has its CatchHandler @ 00add715 */
      __cxa_throw(plVar22,&std::length_error::typeinfo,std::length_error::~length_error);
    }
    lVar12 = 0;
    pcVar31 = pcVar28;
    pbVar16 = (byte *)"GuiLook/StaticImage";
    while (pcVar31 != (char *)0x0) {
      bVar3 = *pbVar16;
      pcVar27 = pcVar31 + -1;
      pbVar25 = pbVar16 + 1;
      if ((char)bVar3 < '\0') {
        if (bVar3 < 0xe0) {
          pcVar27 = pcVar31 + -2;
          pbVar25 = pbVar16 + 2;
        }
        else if (bVar3 < 0xf0) {
          pcVar27 = pcVar31 + -3;
          pbVar25 = pbVar16 + 3;
        }
        else {
          pcVar27 = pcVar31 + -3;
          pbVar25 = pbVar16 + 4;
        }
      }
      lVar12 = lVar12 + 1;
      pcVar31 = pcVar27;
      pbVar16 = pbVar25;
    }
                    /* try { // try from 00adbace to 00adbad2 has its CatchHandler @ 00add715 */
    CEGUI::String::grow((ulong)&local_22c8);
    puVar19 = local_22a0;
    if (0x20 < local_22c0) {
      puVar19 = local_2220;
    }
    if (pcVar28 == (char *)0x0) {
      pcVar31 = "GuiLook/StaticImage";
      if (s_GuiLook_StaticImage_00fd0bff[0] != '\0') {
        do {
          pcVar31 = pcVar31 + 1;
          pcVar28 = pcVar31 + -0xfd0bff;
        } while (*pcVar31 != '\0');
        bVar32 = pcVar28 != (char *)0x0 && local_22c0 != 0;
        goto LAB_00adbafc;
      }
    }
    else {
      bVar32 = local_22c0 != 0;
LAB_00adbafc:
      if (bVar32) {
        pcVar31 = (char *)0x0;
        uVar9 = 0;
        uVar23 = local_22c0;
        do {
          bVar3 = pcVar31[0xfd0bff];
          uVar24 = (uint)bVar3;
          uVar10 = uVar9 + 1;
          if ((char)bVar3 < '\0') {
            uVar24 = (uint)bVar3;
            if (0xdf < bVar3) {
              if (bVar3 < 0xf0) {
                uVar26 = (ulong)uVar10;
                uVar10 = uVar9 + 3;
                uVar24 = (byte)"GuiLook/StaticImage"[uVar9 + 2] & 0x3f | (uVar24 & 0xf) << 0xc |
                         ((byte)"GuiLook/StaticImage"[uVar26] & 0x3f) << 6;
              }
              else {
                uVar26 = (ulong)uVar10;
                uVar10 = uVar9 + 4;
                uVar24 = ((byte)"GuiLook/StaticImage"[uVar26] & 0x3f) << 0xc |
                         (byte)"GuiLook/StaticImage"[uVar9 + 3] & 0x3f | (uVar24 & 7) << 0x12 |
                         ((byte)"GuiLook/StaticImage"[uVar9 + 2] & 0x3f) << 6;
              }
              goto LAB_00adbb13;
            }
            uVar9 = uVar9 + 2;
            *puVar19 = (byte)"GuiLook/StaticImage"[uVar10] & 0x3f | (uVar24 & 0x1f) << 6;
          }
          else {
LAB_00adbb13:
            *puVar19 = uVar24;
            uVar9 = uVar10;
          }
          pcVar31 = (char *)(ulong)uVar9;
          if ((pcVar28 <= pcVar31) || (uVar23 = uVar23 - 1, uVar23 == 0)) break;
          puVar19 = puVar19 + 1;
        } while( true );
      }
    }
    puVar19 = local_22a0;
    if (0x20 < local_22c0) {
      puVar19 = local_2220;
    }
    puVar19[lVar12] = 0;
    local_22c8 = lVar12;
                    /* try { // try from 00adbbb1 to 00adbbb5 has its CatchHandler @ 00add7f3 */
    pUVar15 = (UVector2 *)
              CEGUI::WindowManager::createWindow
                        (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,(String *)&local_22c8,
                         (String *)&local_2378);
                    /* try { // try from 00adbbbc to 00adbbc0 has its CatchHandler @ 00add715 */
    CEGUI::String::~String((String *)&local_22c8);
                    /* try { // try from 00adbbc9 to 00adbbcd has its CatchHandler @ 00adcb68 */
    CEGUI::String::~String((String *)&local_2378);
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
                    /* try { // try from 00adbc0a to 00adbc7d has its CatchHandler @ 00add2c0 */
    CEGUI::String::~String((String *)&local_2428);
    CEGUI::Window::addChildWindow(*(Window **)(*(long *)(pCVar30 + 0x148) + 0xb0));
    pUVar15[0x213] = (UVector2)0x0;
    CEGUI::Window::setWantsMultiClickEvents(SUB81(pUVar15,0));
    pUVar15[0x3e2] = (UVector2)0x1;
    CEGUI::EventSet::setMutedState((bool)(SUB81(pUVar15,0) + '8'));
    CEGUI::Window::getPosition();
    CEGUI::Window::setPosition(pUVar15);
    CEGUI::Window::getSize();
                    /* try { // try from 00adbc84 to 00adbc88 has its CatchHandler @ 00add796 */
    CEGUI::Window::setSize(pUVar15);
    *(UVector2 **)(pCVar30 + 0x108) = pUVar15;
    local_2630 = 0x20;
    local_2628 = 0;
    local_2618 = 0;
    local_2620 = 0;
    local_2590 = (undefined4 *)0x0;
    local_2638 = 0;
    local_2610[0] = 0;
                    /* try { // try from 00adbcd8 to 00adbcdc has its CatchHandler @ 00add2c0 */
    CEGUI::String::grow((ulong)&local_2638);
    local_2638 = 0;
    puVar18 = local_2590;
    if (local_2630 < 0x21) {
      puVar18 = local_2610;
    }
    *puVar18 = 0;
                    /* try { // try from 00adbd16 to 00adbd1a has its CatchHandler @ 00adcbbe */
    std::string::string((string *)local_158,"gui_",&local_3d);
                    /* try { // try from 00adbd2b to 00adbd2f has its CatchHandler @ 00adcb9d */
    STRINGS::uniqueName((STRINGS *)local_168,(string *)local_158);
    local_2580 = 0x20;
    local_2578 = 0;
    local_2568 = 0;
    local_2570 = 0;
    local_24e0 = (undefined4 *)0x0;
    local_2588 = 0;
    local_2560[0] = 0;
    lVar12 = *(long *)(local_168[0] + -0x18);
                    /* try { // try from 00adbd9d to 00adbda1 has its CatchHandler @ 00add81b */
    CEGUI::String::grow((ulong)&local_2588);
    puVar18 = local_2560;
    if (0x20 < local_2580) {
      puVar18 = local_24e0;
    }
    puVar18[lVar12] = 0;
    if (lVar12 != 0) {
      lVar29 = lVar12;
      do {
        lVar29 = lVar29 + -1;
        puVar18 = local_2560;
        if (0x20 < local_2580) {
          puVar18 = local_24e0;
        }
        puVar18[lVar29] = (uint)*(byte *)(local_168[0] + lVar29);
      } while (lVar29 != 0);
    }
    pcVar28 = (char *)0x0;
    local_24d0 = 0x20;
    local_24c8 = 0;
    local_24b8 = 0;
    pcVar31 = "GuiLook/StaticImage";
    local_24c0 = 0;
    local_2430 = (uint *)0x0;
    local_24d8 = 0;
    local_24b0[0] = 0;
    cVar2 = s_GuiLook_StaticImage_00fd0bff[0];
    while (pcVar31 = pcVar31 + 1, cVar2 != '\0') {
      pcVar28 = pcVar31 + -0xfd0bff;
      cVar2 = *pcVar31;
    }
    local_2588 = lVar12;
    if (pcVar28 == CEGUI::String::npos) {
                    /* try { // try from 00adcac3 to 00adcac7 has its CatchHandler @ 00adcc32 */
      std::string::string((string *)local_238,"Length for utf8 encoded string can not be \'npos\'",
                          local_5f);
      plVar22 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00adcadb to 00adcadf has its CatchHandler @ 00adcc03 */
      std::length_error::length_error(plVar22,(string *)local_238);
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
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00adcb07 to 00adcb0b has its CatchHandler @ 00add688 */
      __cxa_throw(plVar22,&std::length_error::typeinfo,std::length_error::~length_error);
    }
    lVar12 = 0;
    pcVar31 = pcVar28;
    pbVar16 = (byte *)"GuiLook/StaticImage";
    while (pcVar31 != (char *)0x0) {
      bVar3 = *pbVar16;
      pcVar27 = pcVar31 + -1;
      pbVar25 = pbVar16 + 1;
      if ((char)bVar3 < '\0') {
        if (bVar3 < 0xe0) {
          pcVar27 = pcVar31 + -2;
          pbVar25 = pbVar16 + 2;
        }
        else if (bVar3 < 0xf0) {
          pcVar27 = pcVar31 + -3;
          pbVar25 = pbVar16 + 3;
        }
        else {
          pcVar27 = pcVar31 + -3;
          pbVar25 = pbVar16 + 4;
        }
      }
      lVar12 = lVar12 + 1;
      pcVar31 = pcVar27;
      pbVar16 = pbVar25;
    }
                    /* try { // try from 00adbffb to 00adbfff has its CatchHandler @ 00add688 */
    CEGUI::String::grow((ulong)&local_24d8);
    if (local_24d0 < 0x21) {
      puVar19 = local_24b0;
      if (pcVar28 == (char *)0x0) goto LAB_00adc601;
LAB_00adc027:
      bVar32 = local_24d0 != 0;
LAB_00adc02d:
      if (bVar32) {
        pcVar31 = (char *)0x0;
        uVar9 = 0;
        uVar23 = local_24d0;
        do {
          bVar3 = pcVar31[0xfd0bff];
          uVar24 = (uint)bVar3;
          uVar10 = uVar9 + 1;
          if ((char)bVar3 < '\0') {
            uVar24 = (uint)bVar3;
            if (0xdf < bVar3) {
              if (bVar3 < 0xf0) {
                uVar26 = (ulong)uVar10;
                uVar10 = uVar9 + 3;
                uVar24 = (byte)"GuiLook/StaticImage"[uVar9 + 2] & 0x3f | (uVar24 & 0xf) << 0xc |
                         ((byte)"GuiLook/StaticImage"[uVar26] & 0x3f) << 6;
              }
              else {
                uVar26 = (ulong)uVar10;
                uVar10 = uVar9 + 4;
                uVar24 = ((byte)"GuiLook/StaticImage"[uVar26] & 0x3f) << 0xc |
                         (byte)"GuiLook/StaticImage"[uVar9 + 3] & 0x3f | (uVar24 & 7) << 0x12 |
                         ((byte)"GuiLook/StaticImage"[uVar9 + 2] & 0x3f) << 6;
              }
              goto LAB_00adc043;
            }
            uVar9 = uVar9 + 2;
            *puVar19 = (byte)"GuiLook/StaticImage"[uVar10] & 0x3f | (uVar24 & 0x1f) << 6;
          }
          else {
LAB_00adc043:
            *puVar19 = uVar24;
            uVar9 = uVar10;
          }
          pcVar31 = (char *)(ulong)uVar9;
          if ((pcVar28 <= pcVar31) || (uVar23 = uVar23 - 1, uVar23 == 0)) break;
          puVar19 = puVar19 + 1;
        } while( true );
      }
    }
    else {
      puVar19 = local_2430;
      if (pcVar28 != (char *)0x0) goto LAB_00adc027;
LAB_00adc601:
      pcVar31 = "GuiLook/StaticImage";
      if (s_GuiLook_StaticImage_00fd0bff[0] != '\0') {
        do {
          pcVar31 = pcVar31 + 1;
          pcVar28 = pcVar31 + -0xfd0bff;
        } while (*pcVar31 != '\0');
        bVar32 = pcVar28 != (char *)0x0 && local_24d0 != 0;
        goto LAB_00adc02d;
      }
    }
    puVar19 = local_2430;
    if (local_24d0 < 0x21) {
      puVar19 = local_24b0;
    }
    puVar19[lVar12] = 0;
    local_24d8 = lVar12;
                    /* try { // try from 00adc0e2 to 00adc0e6 has its CatchHandler @ 00add671 */
    pUVar15 = (UVector2 *)
              CEGUI::WindowManager::createWindow
                        (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,(String *)&local_24d8,
                         (String *)&local_2588);
                    /* try { // try from 00adc0f2 to 00adc0f6 has its CatchHandler @ 00add688 */
    CEGUI::String::~String((String *)&local_24d8);
                    /* try { // try from 00adc0fa to 00adc0fe has its CatchHandler @ 00add81b */
    CEGUI::String::~String((String *)&local_2588);
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
                    /* try { // try from 00adc138 to 00adc195 has its CatchHandler @ 00add2c0 */
    CEGUI::String::~String((String *)&local_2638);
    CEGUI::Window::addChildWindow(*(Window **)(this + 0x68));
    pUVar15[0x213] = (UVector2)0x0;
    CEGUI::Window::setWantsMultiClickEvents(SUB81(pUVar15,0));
    pUVar15[0x3e2] = (UVector2)0x1;
    CEGUI::EventSet::setMutedState((bool)(SUB81(pUVar15,0) + '8'));
    pfVar20 = (float *)CEGUI::Window::getPosition();
    pfVar21 = (float *)CEGUI::Window::getPosition();
    local_33c = pfVar21[3] + pfVar20[3];
    local_340 = pfVar21[2] + pfVar20[2];
    local_348 = *pfVar21 + *pfVar20;
    local_344 = pfVar21[1] + pfVar20[1];
                    /* try { // try from 00adc1f0 to 00adc1f4 has its CatchHandler @ 00add6dc */
    CEGUI::Window::setPosition(pUVar15);
                    /* try { // try from 00adc203 to 00adc207 has its CatchHandler @ 00add2c0 */
    CEGUI::Window::getSize();
                    /* try { // try from 00adc20e to 00adc212 has its CatchHandler @ 00add66c */
    CEGUI::Window::setSize(pUVar15);
    *(UVector2 **)(pCVar30 + 0x128) = pUVar15;
    pCVar30 = pCVar30 + 8;
    uVar9 = uVar8;
    if (uVar8 == 4) {
      if ((allocator *)(local_3b8 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
      {
        LOCK();
        piVar1 = (int *)(local_3b8 + -8);
        iVar6 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar6 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_3b8 + -0x18));
        }
      }
      if ((allocator *)(local_3c8 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
         ) {
        LOCK();
        piVar1 = (int *)(local_3c8 + -8);
        iVar6 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar6 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_3c8 + -0x18));
        }
      }
      if ((allocator *)(local_3d0 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
      {
        LOCK();
        piVar1 = (int *)(local_3d0 + -8);
        iVar6 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar6 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_3d0 + -0x18));
        }
      }
      if ((allocator *)(local_3d8 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
      {
        LOCK();
        piVar1 = (int *)(local_3d8 + -8);
        iVar6 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar6 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_3d8 + -0x18));
        }
      }
      if (local_388 != (void *)0x0) {
        Ogre::NedAllocImpl::deallocBytes(local_388);
      }
      return;
    }
  } while( true );
}

/* address=00add8a0
   symbol=CCombineMenu::CCombineMenu */

/* WARNING: Removing unreachable block (ram,0x00addddc) */
/* WARNING: Removing unreachable block (ram,0x00adddce) */
/* WARNING: Removing unreachable block (ram,0x00adddb2) */
/* WARNING: Removing unreachable block (ram,0x00addd37) */
/* WARNING: Removing unreachable block (ram,0x00adddea) */
/* WARNING: Removing unreachable block (ram,0x00adddc0) */
/* CCombineMenu::CCombineMenu(CGameUI&, CSettings&, Ogre::RenderWindow*, Ogre::SceneManager*,
   CEGUI::Window*, CResourceManager*) */

void __thiscall
CCombineMenu::CCombineMenu
          (CCombineMenu *this,CGameUI *param_1,CSettings *param_2,RenderWindow *param_3,
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
  *(undefined ***)this = &PTR__CCombineMenu_00fe6270;
  *(undefined ***)(this + 0x10) = &PTR__CCombineMenu_00fe6320;
  *(undefined8 *)(this + 0x40) = 0;
  *(undefined4 *)(this + 0x20) = 0;
  *(CCombineMenu **)(this + 0x30) = this + 0x20;
  *(CCombineMenu **)(this + 0x38) = this + 0x20;
  *(undefined8 *)(this + 0x28) = 0;
  *(Window **)(this + 0x48) = param_5;
  *(undefined8 *)(this + 0x88) = 0;
  *(undefined8 *)(this + 0x90) = 0;
  this[0x98] = (CCombineMenu)0x0;
  this[0x99] = (CCombineMenu)0x1;
  this[0x9a] = (CCombineMenu)0x0;
  *(CSettings **)(this + 0xa0) = param_2;
  *(CGameUI **)(this + 0xa8) = param_1;
  *(SceneManager **)(this + 0xb0) = param_4;
  *(RenderWindow **)(this + 0xb8) = param_3;
  *(undefined8 *)(this + 200) = 0;
  *(CResourceManager **)(this + 0xd0) = param_6;
  *(undefined4 *)(this + 0xd8) = 0;
  *(undefined8 *)(this + 0xe0) = 0;
  *(undefined4 *)(this + 0x188) = 0xffffffff;
  *(undefined4 *)(this + 0x18c) = 0xffffffff;
  *(undefined8 *)(this + 400) = 0;
  this[0x1a8] = (CCombineMenu)0x0;
                    /* try { // try from 00add99a to 00add9c1 has its CatchHandler @ 00addd99 */
  lVar4 = CMasterResourceManager::getSingleton();
  this_00 = *(CSoundBankDataInformation **)(lVar4 + 0x100);
  lVar4 = CMasterResourceManager::getSingleton();
  pCVar3 = *(CSoundManager **)(lVar4 + 0x98);
  this_01 = (CSoundBank *)Ogre::NedAllocImpl::allocBytes(0xd0,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00add9cd to 00add9d1 has its CatchHandler @ 00addd66 */
  CSoundBank::CSoundBank(this_01,pCVar3,false);
  *(CSoundBank **)(this + 0xe0) = this_01;
                    /* try { // try from 00add9eb to 00add9ef has its CatchHandler @ 00addd64 */
  std::wstring::wstring((wstring_conflict *)local_58,L"STATSOPEN",local_39);
                    /* try { // try from 00add9f6 to 00add9fa has its CatchHandler @ 00addd77 */
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
                    /* try { // try from 00adda28 to 00adda2c has its CatchHandler @ 00addd99 */
    CSoundBank::addSample(*(CSoundBank **)(this + 0xe0),0x16,*(longlong *)(lVar4 + 0x20));
  }
                    /* try { // try from 00adda3f to 00adda43 has its CatchHandler @ 00addd54 */
  std::wstring::wstring((wstring_conflict *)local_68,L"STATSCLOSE",&local_3a);
                    /* try { // try from 00adda4a to 00adda4e has its CatchHandler @ 00addd47 */
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
                    /* try { // try from 00adda76 to 00adda7a has its CatchHandler @ 00addd99 */
    CSoundBank::addSample(*(CSoundBank **)(this + 0xe0),0x42,*(longlong *)(lVar4 + 0x20));
  }
                    /* try { // try from 00adda8d to 00adda91 has its CatchHandler @ 00addd0f */
  std::wstring::wstring((wstring_conflict *)local_78,L"ERROR",&local_3b);
                    /* try { // try from 00adda98 to 00adda9c has its CatchHandler @ 00addd86 */
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
                    /* try { // try from 00addac4 to 00addac8 has its CatchHandler @ 00addd99 */
    CSoundBank::addSample(*(CSoundBank **)(this + 0xe0),0x18,*(longlong *)(lVar4 + 0x20));
  }
                    /* try { // try from 00addadb to 00addadf has its CatchHandler @ 00addd84 */
  std::wstring::wstring((wstring_conflict *)local_88,L"LOWMANA",&local_3c);
                    /* try { // try from 00addae6 to 00addaea has its CatchHandler @ 00addd92 */
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
                    /* try { // try from 00addb12 to 00addb16 has its CatchHandler @ 00addd99 */
    CSoundBank::addSample(*(CSoundBank **)(this + 0xe0),0x23,*(longlong *)(lVar4 + 0x20));
  }
                    /* try { // try from 00addb29 to 00addb2d has its CatchHandler @ 00addd62 */
  std::wstring::wstring((wstring_conflict *)local_98,L"REVEAL",&local_3d);
                    /* try { // try from 00addb34 to 00addb38 has its CatchHandler @ 00addd56 */
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
                    /* try { // try from 00addb60 to 00addb64 has its CatchHandler @ 00addd99 */
    CSoundBank::addSample(*(CSoundBank **)(this + 0xe0),0x24,*(longlong *)(lVar4 + 0x20));
  }
                    /* try { // try from 00addb77 to 00addb7b has its CatchHandler @ 00addd94 */
  std::wstring::wstring((wstring_conflict *)local_a8,L"GOLDBUY",&local_3e);
                    /* try { // try from 00addb82 to 00addb86 has its CatchHandler @ 00addda5 */
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
                    /* try { // try from 00addbaa to 00addbb6 has its CatchHandler @ 00addd99 */
    CSoundBank::addSample(*(CSoundBank **)(this + 0xe0),0x17,*(longlong *)(lVar4 + 0x20));
  }
  createMenus(this);
  return;
}

/* address=00adde00
   symbol=CCombineMenu::updateLayout */

/* WARNING: Removing unreachable block (ram,0x00adfbaa) */
/* WARNING: Removing unreachable block (ram,0x00adfc05) */
/* WARNING: Removing unreachable block (ram,0x00adfc59) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CCombineMenu::updateLayout() */

void __thiscall CCombineMenu::updateLayout(CCombineMenu *this)

{
  int *piVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  int iVar6;
  byte bVar7;
  CInventory *this_00;
  Window *pWVar8;
  CEquipment *this_01;
  uint uVar9;
  uint uVar10;
  char cVar11;
  uint uVar12;
  uint uVar13;
  long lVar14;
  long lVar15;
  float *pfVar16;
  float *pfVar17;
  byte *pbVar18;
  ulong uVar19;
  char *pcVar20;
  CEquipment *this_02;
  undefined4 *puVar21;
  uint *puVar22;
  length_error *this_03;
  ulong uVar23;
  uint uVar24;
  byte *pbVar25;
  byte *pbVar26;
  ulong uVar27;
  UVector2 *pUVar28;
  CCombineMenu *pCVar29;
  String *this_04;
  bool bVar30;
  uint uVar31;
  float fVar32;
  uint uVar33;
  float fVar34;
  uint uVar35;
  UVector2 *local_14a8;
  CCombineMenu *local_14a0;
  undefined8 local_1438;
  ulong local_1430;
  undefined8 local_1428;
  undefined8 local_1420;
  undefined8 local_1418;
  undefined4 local_1410 [32];
  undefined4 *local_1390;
  undefined8 local_1388;
  ulong local_1380;
  undefined8 local_1378;
  undefined8 local_1370;
  undefined8 local_1368;
  uint local_1360 [5];
  uint local_134c [27];
  uint *local_12e0;
  undefined8 local_12d8;
  ulong local_12d0;
  undefined8 local_12c8;
  undefined8 local_12c0;
  undefined8 local_12b8;
  undefined4 local_12b0 [32];
  undefined4 *local_1230;
  undefined8 local_1228;
  ulong local_1220;
  undefined8 local_1218;
  undefined8 local_1210;
  undefined8 local_1208;
  uint local_1200 [5];
  uint local_11ec [27];
  uint *local_1180;
  undefined8 local_1178;
  ulong local_1170;
  undefined8 local_1168;
  undefined8 local_1160;
  undefined8 local_1158;
  undefined4 local_1150 [32];
  undefined4 *local_10d0;
  undefined8 local_10c8;
  ulong local_10c0;
  undefined8 local_10b8;
  undefined8 local_10b0;
  undefined8 local_10a8;
  uint local_10a0 [5];
  uint local_108c [27];
  uint *local_1020;
  undefined8 local_1018;
  ulong local_1010;
  undefined8 local_1008;
  undefined8 local_1000;
  undefined8 local_ff8;
  undefined4 local_ff0 [32];
  undefined4 *local_f70;
  undefined8 local_f68;
  ulong local_f60;
  undefined8 local_f58;
  undefined8 local_f50;
  undefined8 local_f48;
  uint local_f40 [5];
  uint local_f2c [27];
  uint *local_ec0;
  undefined8 local_eb8;
  ulong local_eb0;
  undefined8 local_ea8;
  undefined8 local_ea0;
  undefined8 local_e98;
  undefined4 local_e90 [32];
  undefined4 *local_e10;
  undefined8 local_e08;
  ulong local_e00;
  undefined8 local_df8;
  undefined8 local_df0;
  undefined8 local_de8;
  uint local_de0 [5];
  uint local_dcc [27];
  uint *local_d60;
  undefined8 local_d58;
  ulong local_d50;
  undefined8 local_d48;
  undefined8 local_d40;
  undefined8 local_d38;
  uint local_d30 [5];
  uint local_d1c [27];
  uint *local_cb0;
  Image local_ca8 [176];
  undefined8 local_bf8;
  ulong local_bf0;
  undefined8 local_be8;
  undefined8 local_be0;
  undefined8 local_bd8;
  uint local_bd0 [13];
  uint local_b9c [19];
  uint *local_b50;
  undefined8 local_b48;
  ulong local_b40;
  undefined8 local_b38;
  undefined8 local_b30;
  undefined8 local_b28;
  uint local_b20 [5];
  uint local_b0c [27];
  uint *local_aa0;
  Image local_a98 [176];
  undefined8 local_9e8;
  ulong local_9e0;
  undefined8 local_9d8;
  undefined8 local_9d0;
  undefined8 local_9c8;
  uint local_9c0 [12];
  uint local_990 [20];
  uint *local_940;
  undefined8 local_938;
  ulong local_930;
  undefined8 local_928;
  undefined8 local_920;
  undefined8 local_918;
  uint local_910 [5];
  uint local_8fc [27];
  uint *local_890;
  Image local_888 [176];
  undefined8 local_7d8;
  ulong local_7d0;
  undefined8 local_7c8;
  undefined8 local_7c0;
  undefined8 local_7b8;
  uint local_7b0 [12];
  uint local_780 [20];
  uint *local_730;
  long local_728;
  ulong local_720;
  undefined8 local_718;
  undefined8 local_710;
  undefined8 local_708;
  uint local_700 [32];
  uint *local_680;
  undefined8 local_678;
  ulong local_670;
  undefined8 local_668;
  undefined8 local_660;
  undefined8 local_658;
  undefined4 local_650 [32];
  undefined4 *local_5d0;
  undefined8 local_5c8;
  ulong local_5c0;
  undefined8 local_5b8;
  undefined8 local_5b0;
  undefined8 local_5a8;
  uint local_5a0 [5];
  uint local_58c [27];
  uint *local_520;
  String local_518 [176];
  Image local_468 [176];
  String local_3b8 [176];
  undefined8 local_308;
  ulong local_300;
  undefined8 local_2f8;
  undefined8 local_2f0;
  undefined8 local_2e8;
  uint local_2e0 [5];
  uint local_2cc [27];
  uint *local_260;
  Image local_258 [176];
  undefined8 local_1a8;
  ulong local_1a0;
  undefined8 local_198;
  undefined8 local_190;
  undefined8 local_188;
  uint local_180 [13];
  uint local_14c [19];
  uint *local_100;
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

  if (((this[0x98] != (CCombineMenu)0x0) && (*(long *)(this + 0x90) != 0)) &&
     (this_00 = *(CInventory **)(*(long *)(this + 0x90) + 0x490), this_00 != (CInventory *)0x0)) {
    while (pWVar8 = *(Window **)(this + 0x60),
          *(long *)(pWVar8 + 0x80) - *(long *)(pWVar8 + 0x78) >> 3 != 0) {
      CEGUI::Window::removeChildWindow(pWVar8);
    }
    pCVar29 = this;
    local_14a0 = this;
    do {
      pWVar8 = *(Window **)(pCVar29 + 0x148);
      if (pWVar8 != (Window *)0x0) {
        if (*(long *)(pWVar8 + 0x80) - *(long *)(pWVar8 + 0x78) >> 3 != 0) {
          CEGUI::Window::removeChildWindow(pWVar8);
        }
        lVar14 = CInventory::getEquipmentRefInSlot(this_00,*(uint *)(local_14a0 + 0xe8));
        if (lVar14 == 0) {
          if (*(long *)(pCVar29 + 0x148) != 0) {
            CEGUI::Window::setVisible(SUB81(*(undefined8 *)(pCVar29 + 0x168),0));
            local_1170 = 0x20;
            local_1168 = 0;
            local_1158 = 0;
            local_1160 = 0;
            local_10d0 = (undefined4 *)0x0;
            local_1178 = 0;
            local_1150[0] = 0;
            CEGUI::String::grow((ulong)&local_1178);
            local_1178 = 0;
            puVar21 = local_1150;
            if (0x20 < local_1170) {
              puVar21 = local_10d0;
            }
            *puVar21 = 0;
            local_10c0 = 0x20;
            local_10b8 = 0;
            local_10a8 = 0;
            local_10b0 = 0;
            local_1020 = (uint *)0x0;
            local_10c8 = 0;
            local_10a0[0] = 0;
                    /* try { // try from 00adf145 to 00adf149 has its CatchHandler @ 00adfaed */
            CEGUI::String::grow((ulong)&local_10c8);
            puVar22 = local_1020;
            if (local_10c0 < 0x21) {
              puVar22 = local_10a0;
            }
            pbVar18 = (byte *)0xfd0c0d;
            do {
              bVar7 = *pbVar18;
              pbVar18 = pbVar18 + 1;
              *puVar22 = (uint)bVar7;
              puVar22 = puVar22 + 1;
            } while (pbVar18 != (byte *)0xfd0c12);
            local_10c8 = 5;
            puVar22 = local_108c;
            if (0x20 < local_10c0) {
              puVar22 = local_1020 + 5;
            }
            *puVar22 = 0;
                    /* try { // try from 00adf1c8 to 00adf1cc has its CatchHandler @ 00adfd85 */
            CEGUI::PropertySet::setProperty(*(String **)(pCVar29 + 0x128),(String *)&local_10c8);
                    /* try { // try from 00adf1d5 to 00adf1d9 has its CatchHandler @ 00adfaed */
            CEGUI::String::~String((String *)&local_10c8);
            CEGUI::String::~String((String *)&local_1178);
            CEGUI::Window::getSize();
                    /* try { // try from 00adf203 to 00adf207 has its CatchHandler @ 00adfd7f */
            CEGUI::Window::setSize(*(UVector2 **)(pCVar29 + 0x128));
            local_12d0 = 0x20;
            local_12c8 = 0;
            local_12b8 = 0;
            local_12c0 = 0;
            local_1230 = (undefined4 *)0x0;
            local_12d8 = 0;
            local_12b0[0] = 0;
            CEGUI::String::grow((ulong)&local_12d8);
            puVar21 = local_12b0;
            if (0x20 < local_12d0) {
              puVar21 = local_1230;
            }
            local_12d8 = 0;
            *puVar21 = 0;
            local_1220 = 0x20;
            local_1218 = 0;
            local_1208 = 0;
            local_1210 = 0;
            local_1180 = (uint *)0x0;
            local_1228 = 0;
            local_1200[0] = 0;
                    /* try { // try from 00adf2f6 to 00adf2fa has its CatchHandler @ 00adfd7a */
            CEGUI::String::grow((ulong)&local_1228);
            puVar22 = local_1180;
            if (local_1220 < 0x21) {
              puVar22 = local_1200;
            }
            pbVar18 = (byte *)0xfd0c0d;
            do {
              bVar7 = *pbVar18;
              pbVar18 = pbVar18 + 1;
              *puVar22 = (uint)bVar7;
              puVar22 = puVar22 + 1;
            } while (pbVar18 != (byte *)0xfd0c12);
            local_1228 = 5;
            puVar22 = local_11ec;
            if (0x20 < local_1220) {
              puVar22 = local_1180 + 5;
            }
            *puVar22 = 0;
                    /* try { // try from 00adf37a to 00adf37e has its CatchHandler @ 00adfd55 */
            CEGUI::PropertySet::setProperty(*(String **)(pCVar29 + 0x108),(String *)&local_1228);
                    /* try { // try from 00adf387 to 00adf38b has its CatchHandler @ 00adfd7a */
            CEGUI::String::~String((String *)&local_1228);
            CEGUI::String::~String((String *)&local_12d8);
            CEGUI::Window::getSize();
                    /* try { // try from 00adf3ba to 00adf3be has its CatchHandler @ 00adfd4f */
            CEGUI::Window::setSize(*(UVector2 **)(pCVar29 + 0x108));
            local_1430 = 0x20;
            local_1428 = 0;
            local_1418 = 0;
            local_1420 = 0;
            local_1390 = (undefined4 *)0x0;
            local_1438 = 0;
            local_1410[0] = 0;
            CEGUI::String::grow((ulong)&local_1438);
            puVar21 = local_1410;
            if (0x20 < local_1430) {
              puVar21 = local_1390;
            }
            local_1438 = 0;
            *puVar21 = 0;
            local_1380 = 0x20;
            local_1378 = 0;
            local_1368 = 0;
            local_1370 = 0;
            local_12e0 = (uint *)0x0;
            local_1388 = 0;
            local_1360[0] = 0;
                    /* try { // try from 00adf4ad to 00adf4b1 has its CatchHandler @ 00adfd4a */
            CEGUI::String::grow((ulong)&local_1388);
            puVar22 = local_12e0;
            if (local_1380 < 0x21) {
              puVar22 = local_1360;
            }
            pbVar18 = (byte *)0xfd0c0d;
            do {
              bVar7 = *pbVar18;
              pbVar18 = pbVar18 + 1;
              *puVar22 = (uint)bVar7;
              puVar22 = puVar22 + 1;
            } while (pbVar18 != (byte *)0xfd0c12);
            local_1388 = 5;
            puVar22 = local_134c;
            if (0x20 < local_1380) {
              puVar22 = local_12e0 + 5;
            }
            *puVar22 = 0;
                    /* try { // try from 00adf532 to 00adf536 has its CatchHandler @ 00adfd25 */
            CEGUI::PropertySet::setProperty(*(String **)(pCVar29 + 0x148),(String *)&local_1388);
                    /* try { // try from 00adf53f to 00adf543 has its CatchHandler @ 00adfd4a */
            CEGUI::String::~String((String *)&local_1388);
            CEGUI::String::~String((String *)&local_1438);
          }
        }
        else {
          this_01 = *(CEquipment **)(lVar14 + 0x10);
          local_14a8 = *(UVector2 **)(this_01 + 0x2c8);
          if (local_14a8 == (UVector2 *)0x0) {
            CEquipment::createIcon(this_01,*(CGameUI **)(this + 0xa8),false);
            local_14a8 = *(UVector2 **)(this_01 + 0x2c8);
            if (local_14a8 != (UVector2 *)0x0) {
              CEGUI::EventSet::setMutedState((bool)((char)local_14a8 + '8'));
              local_14a8[0x3e2] = (UVector2)0x1;
              goto LAB_00addf52;
            }
          }
          else {
LAB_00addf52:
            if (*(Window **)(local_14a8 + 0xb0) != (Window *)0x0) {
              CEGUI::Window::removeChildWindow(*(Window **)(local_14a8 + 0xb0));
            }
            CEGUI::Window::addChildWindow(*(Window **)(pCVar29 + 0x148));
          }
          lVar14 = CEGUI::Window::getPosition();
          lVar15 = CEGUI::Window::getPosition();
          uVar10 = DAT_00fa86f4;
          uVar9 = DAT_00fa4810;
          fVar2 = *(float *)(lVar15 + 0xc);
          fVar3 = *(float *)(lVar14 + 0xc);
          fVar32 = (*(float *)(lVar14 + 8) + *(float *)(lVar15 + 8)) * 0.0;
          uVar31 = -(uint)(0.0 < fVar32);
          uVar35 = DAT_00fa4810 & uVar31;
          uVar33 = ~uVar31 & DAT_00fa86f4;
          pfVar16 = (float *)CEGUI::Window::getPosition();
          pfVar17 = (float *)CEGUI::Window::getPosition();
          fVar4 = pfVar16[1];
          fVar5 = pfVar17[1];
          fVar34 = (*pfVar16 + *pfVar17) * 0.0;
          uVar31 = -(uint)(0.0 < fVar34);
          if (((this_01[0x348] == (CEquipment)0x0) || (*(int *)(this_01 + 0x3e0) == 0)) ||
             (cVar11 = CEGUI::Window::isVisible
                                 (SUB81(*(undefined8 *)(*(long *)(pCVar29 + 0x148) + 0xb0),0)),
             cVar11 == '\0')) {
            local_670 = 0x20;
            local_668 = 0;
            local_658 = 0;
            local_660 = 0;
            local_5d0 = (undefined4 *)0x0;
            local_678 = 0;
            local_650[0] = 0;
            CEGUI::String::grow((ulong)&local_678);
            local_678 = 0;
            puVar21 = local_650;
            if (0x20 < local_670) {
              puVar21 = local_5d0;
            }
            *puVar21 = 0;
            local_5c0 = 0x20;
            local_5b8 = 0;
            local_5a8 = 0;
            local_5b0 = 0;
            local_520 = (uint *)0x0;
            local_5c8 = 0;
            local_5a0[0] = 0;
                    /* try { // try from 00ade184 to 00ade188 has its CatchHandler @ 00adfb5e */
            CEGUI::String::grow((ulong)&local_5c8);
            puVar22 = local_5a0;
            if (0x20 < local_5c0) {
              puVar22 = local_520;
            }
            pbVar18 = (byte *)0xfd0c0d;
            do {
              bVar7 = *pbVar18;
              pbVar18 = pbVar18 + 1;
              *puVar22 = (uint)bVar7;
              puVar22 = puVar22 + 1;
            } while (pbVar18 != (byte *)0xfd0c12);
            local_5c8 = 5;
            puVar22 = local_58c;
            if (0x20 < local_5c0) {
              puVar22 = local_520 + 5;
            }
            *puVar22 = 0;
                    /* try { // try from 00ade1f8 to 00ade1fc has its CatchHandler @ 00adfb9d */
            CEGUI::PropertySet::setProperty(*(String **)(pCVar29 + 0x128),(String *)&local_5c8);
                    /* try { // try from 00ade200 to 00ade204 has its CatchHandler @ 00adfb5e */
            CEGUI::String::~String((String *)&local_5c8);
            CEGUI::String::~String((String *)&local_678);
          }
          else {
            if (*(uint *)(this_01 + 0x3e0) < 2) {
              if (*(uint *)(this_01 + 0x3e0) == 1) {
                CEGUI::String::String(local_3b8,"onesocketglow");
                    /* try { // try from 00adf9ae to 00adf9c5 has its CatchHandler @ 00adfca3 */
                CEGUI::Imageset::getImage(*(String **)(this + 0x198));
                CEGUI::PropertyHelper::imageToString(local_468);
                    /* try { // try from 00adf9d6 to 00adf9da has its CatchHandler @ 00adfc9e */
                CEGUI::String::String(local_518,"Image");
                    /* try { // try from 00adf9e8 to 00adf9ec has its CatchHandler @ 00adfc7b */
                CEGUI::PropertySet::setProperty(*(String **)(pCVar29 + 0x128),local_518);
                    /* try { // try from 00adf9f0 to 00adf9f4 has its CatchHandler @ 00adfc9e */
                CEGUI::String::~String(local_518);
                    /* try { // try from 00adf9f8 to 00adf9fc has its CatchHandler @ 00adfca3 */
                CEGUI::String::~String((String *)local_468);
                CEGUI::String::~String(local_3b8);
              }
            }
            else {
              local_1a0 = 0x20;
              local_198 = 0;
              local_188 = 0;
              local_190 = 0;
              local_100 = (uint *)0x0;
              local_1a8 = 0;
              local_180[0] = 0;
              CEGUI::String::grow((ulong)&local_1a8);
              puVar22 = local_180;
              if (0x20 < local_1a0) {
                puVar22 = local_100;
              }
              pcVar20 = "twosocketglow";
              do {
                bVar7 = *pcVar20;
                pcVar20 = pcVar20 + 1;
                *puVar22 = (uint)bVar7;
                puVar22 = puVar22 + 1;
              } while ((byte *)pcVar20 != (byte *)0xfe60d0);
              local_1a8 = 0xd;
              puVar22 = local_14c;
              if (0x20 < local_1a0) {
                puVar22 = local_100 + 0xd;
              }
              *puVar22 = 0;
                    /* try { // try from 00adf86d to 00adf884 has its CatchHandler @ 00adfcc5 */
              CEGUI::Imageset::getImage(*(String **)(this + 0x198));
              CEGUI::PropertyHelper::imageToString(local_258);
              local_300 = 0x20;
              local_2f8 = 0;
              local_2e8 = 0;
              local_2f0 = 0;
              local_260 = (uint *)0x0;
              local_308 = 0;
              local_2e0[0] = 0;
                    /* try { // try from 00adf8e8 to 00adf8ec has its CatchHandler @ 00adfcc0 */
              CEGUI::String::grow((ulong)&local_308);
              puVar22 = local_2e0;
              if (0x20 < local_300) {
                puVar22 = local_260;
              }
              pbVar18 = (byte *)0xfd0c0d;
              do {
                bVar7 = *pbVar18;
                pbVar18 = pbVar18 + 1;
                *puVar22 = (uint)bVar7;
                puVar22 = puVar22 + 1;
              } while (pbVar18 != (byte *)0xfd0c12);
              local_308 = 5;
              puVar22 = local_2cc;
              if (0x20 < local_300) {
                puVar22 = local_260 + 5;
              }
              *puVar22 = 0;
                    /* try { // try from 00adf95f to 00adf963 has its CatchHandler @ 00adfca8 */
              CEGUI::PropertySet::setProperty(*(String **)(pCVar29 + 0x128),(String *)&local_308);
                    /* try { // try from 00adf967 to 00adf96b has its CatchHandler @ 00adfcc0 */
              CEGUI::String::~String((String *)&local_308);
                    /* try { // try from 00adf96f to 00adf973 has its CatchHandler @ 00adfcc5 */
              CEGUI::String::~String((String *)local_258);
              CEGUI::String::~String((String *)&local_1a8);
            }
            CEGUI::Window::moveToFront();
          }
          if (*(long *)(pCVar29 + 0x168) != 0) {
            bVar30 = SUB81(*(long *)(pCVar29 + 0x168),0);
            if (*(int *)(this_01 + 0x238) < 2) {
              CEGUI::Window::setVisible(bVar30);
            }
            else {
              CEGUI::Window::setVisible(bVar30);
              STRINGS::GetValueAsString((STRINGS *)local_58,*(int *)(this_01 + 0x238));
                    /* try { // try from 00ade25c to 00ade260 has its CatchHandler @ 00adfbb5 */
              std::operator+((char *)&local_48,(string *)&DAT_0103f7f3);
              if ((allocator *)(local_58[0] + -0x18) !=
                  (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar1 = (int *)(local_58[0] + -8);
                iVar6 = *piVar1;
                *piVar1 = *piVar1 + -1;
                UNLOCK();
                if (iVar6 < 1) {
                  std::string::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
                }
              }
              pbVar18 = local_48;
              local_720 = 0x20;
              uVar27 = 0;
              local_718 = 0;
              local_708 = 0;
              local_710 = 0;
              local_680 = (uint *)0x0;
              local_728 = 0;
              local_700[0] = 0;
              bVar7 = *local_48;
              while (bVar7 != 0) {
                uVar27 = uVar27 + 1;
                bVar7 = local_48[uVar27];
              }
              if (uVar27 == CEGUI::String::npos) {
                    /* try { // try from 00adfa35 to 00adfa39 has its CatchHandler @ 00adfc76 */
                std::string::string((string *)local_68,
                                    "Length for utf8 encoded string can not be \'npos\'",local_3a);
                this_03 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00adfa4d to 00adfa51 has its CatchHandler @ 00adfc41 */
                std::length_error::length_error(this_03,(string *)local_68);
                if ((allocator *)(local_68[0] + -0x18) !=
                    (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                  LOCK();
                  piVar1 = (int *)(local_68[0] + -8);
                  iVar6 = *piVar1;
                  *piVar1 = *piVar1 + -1;
                  UNLOCK();
                  if (iVar6 < 1) {
                    std::string::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
                  }
                }
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00adfa79 to 00adfa7d has its CatchHandler @ 00adfb34 */
                __cxa_throw(this_03,&std::length_error::typeinfo,std::length_error::~length_error);
              }
              lVar14 = 0;
              uVar23 = uVar27;
              pbVar25 = local_48;
              while (uVar23 != 0) {
                bVar7 = *pbVar25;
                uVar19 = uVar23 - 1;
                pbVar26 = pbVar25 + 1;
                if ((char)bVar7 < '\0') {
                  if (bVar7 < 0xe0) {
                    uVar19 = uVar23 - 2;
                    pbVar26 = pbVar25 + 2;
                  }
                  else if (bVar7 < 0xf0) {
                    uVar19 = uVar23 - 3;
                    pbVar26 = pbVar25 + 3;
                  }
                  else {
                    uVar19 = uVar23 - 3;
                    pbVar26 = pbVar25 + 4;
                  }
                }
                lVar14 = lVar14 + 1;
                uVar23 = uVar19;
                pbVar25 = pbVar26;
              }
                    /* try { // try from 00adeb2b to 00adeb2f has its CatchHandler @ 00adfb34 */
              CEGUI::String::grow((ulong)&local_728);
              if (local_720 < 0x21) {
                puVar22 = local_700;
                if (uVar27 == 0) goto LAB_00adee86;
LAB_00adeb57:
                bVar30 = local_720 != 0;
LAB_00adeb5d:
                if (bVar30) {
                  uVar19 = 0;
                  uVar23 = local_720;
                  uVar12 = 0;
                  while( true ) {
                    bVar7 = pbVar18[uVar19];
                    uVar24 = (uint)bVar7;
                    uVar13 = uVar12 + 1;
                    if ((char)bVar7 < '\0') {
                      uVar24 = (uint)bVar7;
                      if (bVar7 < 0xe0) {
                        uVar19 = (ulong)uVar13;
                        uVar13 = uVar12 + 2;
                        uVar24 = pbVar18[uVar19] & 0x3f | (uVar24 & 0x1f) << 6;
                      }
                      else if (bVar7 < 0xf0) {
                        uVar19 = (ulong)uVar13;
                        uVar13 = uVar12 + 3;
                        uVar24 = pbVar18[uVar12 + 2] & 0x3f | (uVar24 & 0xf) << 0xc |
                                 (pbVar18[uVar19] & 0x3f) << 6;
                      }
                      else {
                        uVar19 = (ulong)uVar13;
                        uVar13 = uVar12 + 4;
                        uVar24 = (pbVar18[uVar19] & 0x3f) << 0xc | pbVar18[uVar12 + 3] & 0x3f |
                                 (uVar24 & 7) << 0x12 | (pbVar18[uVar12 + 2] & 0x3f) << 6;
                      }
                    }
                    *puVar22 = uVar24;
                    uVar19 = (ulong)uVar13;
                    uVar23 = uVar23 - 1;
                    if ((uVar27 <= uVar19) || (uVar23 == 0)) break;
                    puVar22 = puVar22 + 1;
                    uVar12 = uVar13;
                  }
                }
              }
              else {
                puVar22 = local_680;
                if (uVar27 != 0) goto LAB_00adeb57;
LAB_00adee86:
                if (*pbVar18 != 0) {
                  do {
                    uVar27 = uVar27 + 1;
                  } while (pbVar18[uVar27] != 0);
                  bVar30 = uVar27 != 0 && local_720 != 0;
                  goto LAB_00adeb5d;
                }
              }
              puVar22 = local_680;
              if (local_720 < 0x21) {
                puVar22 = local_700;
              }
              puVar22[lVar14] = 0;
              local_728 = lVar14;
                    /* try { // try from 00ade7fa to 00ade7fe has its CatchHandler @ 00adfb4c */
              CEGUI::Window::setText(*(String **)(pCVar29 + 0x168));
                    /* try { // try from 00ade807 to 00ade80b has its CatchHandler @ 00adfb34 */
              CEGUI::String::~String((String *)&local_728);
              if ((allocator *)(local_48 + -0x18) !=
                  (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                LOCK();
                pbVar18 = local_48 + -8;
                iVar6 = *(int *)pbVar18;
                *(int *)pbVar18 = *(int *)pbVar18 + -1;
                UNLOCK();
                if (iVar6 < 1) {
                  std::string::_Rep::_M_destroy((allocator *)(local_48 + -0x18));
                }
              }
            }
          }
          uVar27 = (ulong)(fVar2 + fVar3 + (float)(int)(fVar32 + (float)(uVar33 | uVar35)));
          if (1 < *(uint *)(this_01 + 0x3e0)) {
            CEGUI::Window::getSize();
            uVar33 = -(uint)(0.0 < local_70 * 0.0);
            uVar27 = (ulong)((float)(uVar27 & 0xffffffff) +
                            ((float)(int)((float)(~uVar33 & DAT_00fa86f4 | DAT_00fa4810 & uVar33) +
                                         local_70 * 0.0) + local_6c) * _DAT_00fe6520);
          }
          cVar11 = CEGUI::Window::isVisible
                             (SUB81(*(undefined8 *)(*(long *)(pCVar29 + 0x148) + 0xb0),0));
          if ((cVar11 != '\0') && (*(int *)(this_01 + 0x3f0) != 0)) {
            uVar33 = 0;
            do {
              if (uVar33 < *(uint *)(this_01 + 0x3f4)) {
                this_02 = *(CEquipment **)((ulong)uVar33 * 8 + *(long *)(this_01 + 1000));
                pUVar28 = *(UVector2 **)(this_02 + 0x2c8);
                if (pUVar28 != (UVector2 *)0x0) goto LAB_00ade95a;
LAB_00adeab4:
                CEquipment::createIcon(this_02,*(CGameUI **)(this + 0xa8),false);
                pUVar28 = *(UVector2 **)(this_02 + 0x2c8);
                if (pUVar28 != (UVector2 *)0x0) {
                  CEGUI::EventSet::setMutedState((bool)((char)pUVar28 + '8'));
                  pUVar28[0x3e2] = (UVector2)0x1;
                  goto LAB_00ade95a;
                }
              }
              else {
                this_02 = (CEquipment *)**(long **)(this_01 + 1000);
                pUVar28 = *(UVector2 **)(this_02 + 0x2c8);
                if (pUVar28 == (UVector2 *)0x0) goto LAB_00adeab4;
LAB_00ade95a:
                if (*(Window **)(pUVar28 + 0xb0) != (Window *)0x0) {
                  CEGUI::Window::removeChildWindow(*(Window **)(pUVar28 + 0xb0));
                }
                CEGUI::Window::addChildWindow(*(Window **)(this + 0x60));
                local_84 = (float)((long)(fVar4 + fVar5 +
                                         (float)(int)((float)(~uVar31 & uVar10 | uVar9 & uVar31) +
                                                     fVar34)) & 0xffffffff);
                local_7c = (float)(uVar27 & 0xffffffff);
                local_88 = 0;
                local_80 = 0;
                    /* try { // try from 00ade9c4 to 00ade9c8 has its CatchHandler @ 00adfbc8 */
                CEGUI::Window::setPosition(pUVar28);
                CEGUI::Window::getSize();
                    /* try { // try from 00ade9e8 to 00ade9ec has its CatchHandler @ 00adfbcd */
                CEGUI::Window::setSize(pUVar28);
                CEGUI::Window::moveToFront();
                pUVar28[0x3e2] = (UVector2)0x1;
              }
              uVar33 = uVar33 + 1;
              CEGUI::Window::getSize();
              uVar35 = -(uint)(0.0 < local_a0 * 0.0);
              if (*(uint *)(this_01 + 0x3f0) <= uVar33) break;
              uVar27 = (ulong)((float)(uVar27 & 0xffffffff) +
                              ((float)(int)((float)(~uVar35 & DAT_00fa86f4 | DAT_00fa4810 & uVar35)
                                           + local_a0 * 0.0) + local_9c) * DAT_00fa4830);
            } while( true );
          }
          cVar11 = CBaseUnit::ISA((CBaseUnit *)this_01,0x36);
          if (cVar11 == '\0') {
            cVar11 = (**(code **)(*(long *)this_01 + 0x2b0))(this_01);
            if (cVar11 == '\0') {
              this_04 = (String *)&local_eb8;
              local_eb0 = 0x20;
              local_ea8 = 0;
              local_e98 = 0;
              local_ea0 = 0;
              local_e10 = (undefined4 *)0x0;
              local_eb8 = 0;
              local_e90[0] = 0;
              CEGUI::String::grow((ulong)this_04);
              local_eb8 = 0;
              puVar21 = local_e90;
              if (0x20 < local_eb0) {
                puVar21 = local_e10;
              }
              *puVar21 = 0;
              local_e00 = 0x20;
              local_df8 = 0;
              local_de8 = 0;
              local_df0 = 0;
              local_d60 = (uint *)0x0;
              local_e08 = 0;
              local_de0[0] = 0;
                    /* try { // try from 00adefa4 to 00adefa8 has its CatchHandler @ 00adfbfa */
              CEGUI::String::grow((ulong)&local_e08);
              puVar22 = local_de0;
              if (0x20 < local_e00) {
                puVar22 = local_d60;
              }
              pbVar18 = (byte *)0xfd0c0d;
              do {
                bVar7 = *pbVar18;
                pbVar18 = pbVar18 + 1;
                *puVar22 = (uint)bVar7;
                puVar22 = puVar22 + 1;
              } while (pbVar18 != (byte *)0xfd0c12);
              local_e08 = 5;
              puVar22 = local_dcc;
              if (0x20 < local_e00) {
                puVar22 = local_d60 + 5;
              }
              *puVar22 = 0;
                    /* try { // try from 00adf00f to 00adf013 has its CatchHandler @ 00adfbf5 */
              CEGUI::PropertySet::setProperty(*(String **)(pCVar29 + 0x108),(String *)&local_e08);
                    /* try { // try from 00adf017 to 00adf01b has its CatchHandler @ 00adfbfa */
              CEGUI::String::~String((String *)&local_e08);
            }
            else {
              cVar11 = CBaseUnit::ISA((CBaseUnit *)this_01,0x37);
              if (cVar11 == '\0') {
                this_04 = (String *)&local_bf8;
                local_bf0 = 0x20;
                local_be8 = 0;
                local_bd8 = 0;
                local_be0 = 0;
                local_b50 = (uint *)0x0;
                local_bf8 = 0;
                local_bd0[0] = 0;
                CEGUI::String::grow((ulong)this_04);
                puVar22 = local_bd0;
                if (0x20 < local_bf0) {
                  puVar22 = local_b50;
                }
                pcVar20 = "greenslotglow";
                do {
                  bVar7 = *pcVar20;
                  pcVar20 = pcVar20 + 1;
                  *puVar22 = (uint)bVar7;
                  puVar22 = puVar22 + 1;
                } while ((byte *)pcVar20 != (byte *)0xfe60c2);
                local_bf8 = 0xd;
                puVar22 = local_b9c;
                if (0x20 < local_bf0) {
                  puVar22 = local_b50 + 0xd;
                }
                *puVar22 = 0;
                    /* try { // try from 00adf645 to 00adf65c has its CatchHandler @ 00adfd15 */
                CEGUI::Imageset::getImage(*(String **)(this + 0x198));
                CEGUI::PropertyHelper::imageToString(local_ca8);
                local_d50 = 0x20;
                local_d48 = 0;
                local_d38 = 0;
                local_d40 = 0;
                local_cb0 = (uint *)0x0;
                local_d58 = 0;
                local_d30[0] = 0;
                    /* try { // try from 00adf6c0 to 00adf6c4 has its CatchHandler @ 00adfd05 */
                CEGUI::String::grow((ulong)&local_d58);
                puVar22 = local_d30;
                if (0x20 < local_d50) {
                  puVar22 = local_cb0;
                }
                pbVar18 = (byte *)0xfd0c0d;
                do {
                  bVar7 = *pbVar18;
                  pbVar18 = pbVar18 + 1;
                  *puVar22 = (uint)bVar7;
                  puVar22 = puVar22 + 1;
                } while (pbVar18 != (byte *)0xfd0c12);
                local_d58 = 5;
                puVar22 = local_d1c;
                if (0x20 < local_d50) {
                  puVar22 = local_cb0 + 5;
                }
                *puVar22 = 0;
                    /* try { // try from 00adf737 to 00adf73b has its CatchHandler @ 00adfcf5 */
                CEGUI::PropertySet::setProperty(*(String **)(pCVar29 + 0x108),(String *)&local_d58);
                    /* try { // try from 00adf73f to 00adf743 has its CatchHandler @ 00adfd05 */
                CEGUI::String::~String((String *)&local_d58);
                    /* try { // try from 00adf747 to 00adf74b has its CatchHandler @ 00adfd15 */
                CEGUI::String::~String((String *)local_ca8);
              }
              else {
                this_04 = (String *)&local_9e8;
                local_9e0 = 0x20;
                local_9d8 = 0;
                local_9c8 = 0;
                local_9d0 = 0;
                local_940 = (uint *)0x0;
                local_9e8 = 0;
                local_9c0[0] = 0;
                CEGUI::String::grow((ulong)this_04);
                puVar22 = local_9c0;
                if (0x20 < local_9e0) {
                  puVar22 = local_940;
                }
                pcVar20 = "blueslotglow";
                do {
                  bVar7 = *pcVar20;
                  pcVar20 = pcVar20 + 1;
                  *puVar22 = (uint)bVar7;
                  puVar22 = puVar22 + 1;
                } while ((byte *)pcVar20 != (byte *)0xfe60b4);
                local_9e8 = 0xc;
                puVar22 = local_990;
                if (0x20 < local_9e0) {
                  puVar22 = local_940 + 0xc;
                }
                *puVar22 = 0;
                    /* try { // try from 00adecfd to 00aded14 has its CatchHandler @ 00adfce5 */
                CEGUI::Imageset::getImage(*(String **)(this + 0x198));
                CEGUI::PropertyHelper::imageToString(local_a98);
                local_b40 = 0x20;
                local_b38 = 0;
                local_b28 = 0;
                local_b30 = 0;
                local_aa0 = (uint *)0x0;
                local_b48 = 0;
                local_b20[0] = 0;
                    /* try { // try from 00aded78 to 00aded7c has its CatchHandler @ 00adfcd5 */
                CEGUI::String::grow((ulong)&local_b48);
                puVar22 = local_b20;
                if (0x20 < local_b40) {
                  puVar22 = local_aa0;
                }
                pbVar18 = (byte *)0xfd0c0d;
                do {
                  bVar7 = *pbVar18;
                  pbVar18 = pbVar18 + 1;
                  *puVar22 = (uint)bVar7;
                  puVar22 = puVar22 + 1;
                } while (pbVar18 != (byte *)0xfd0c12);
                local_b48 = 5;
                puVar22 = local_b0c;
                if (0x20 < local_b40) {
                  puVar22 = local_aa0 + 5;
                }
                *puVar22 = 0;
                    /* try { // try from 00adedef to 00adedf3 has its CatchHandler @ 00adfcca */
                CEGUI::PropertySet::setProperty(*(String **)(pCVar29 + 0x108),(String *)&local_b48);
                    /* try { // try from 00adedf7 to 00adedfb has its CatchHandler @ 00adfcd5 */
                CEGUI::String::~String((String *)&local_b48);
                    /* try { // try from 00adedff to 00adee03 has its CatchHandler @ 00adfce5 */
                CEGUI::String::~String((String *)local_a98);
              }
            }
          }
          else {
            this_04 = (String *)&local_7d8;
            local_7d0 = 0x20;
            local_7c8 = 0;
            local_7b8 = 0;
            local_7c0 = 0;
            local_730 = (uint *)0x0;
            local_7d8 = 0;
            local_7b0[0] = 0;
            CEGUI::String::grow((ulong)this_04);
            puVar22 = local_7b0;
            if (0x20 < local_7d0) {
              puVar22 = local_730;
            }
            pcVar20 = "goldslotglow";
            do {
              bVar7 = *pcVar20;
              pcVar20 = pcVar20 + 1;
              *puVar22 = (uint)bVar7;
              puVar22 = puVar22 + 1;
            } while ((byte *)pcVar20 != (byte *)0xfe60a7);
            local_7d8 = 0xc;
            puVar22 = local_780;
            if (0x20 < local_7d0) {
              puVar22 = local_730 + 0xc;
            }
            *puVar22 = 0;
                    /* try { // try from 00ade42d to 00ade444 has its CatchHandler @ 00adfbd5 */
            CEGUI::Imageset::getImage(*(String **)(this + 0x198));
            CEGUI::PropertyHelper::imageToString(local_888);
            local_930 = 0x20;
            local_928 = 0;
            local_918 = 0;
            local_920 = 0;
            local_890 = (uint *)0x0;
            local_938 = 0;
            local_910[0] = 0;
                    /* try { // try from 00ade4a8 to 00ade4ac has its CatchHandler @ 00adfbe5 */
            CEGUI::String::grow((ulong)&local_938);
            puVar22 = local_910;
            if (0x20 < local_930) {
              puVar22 = local_890;
            }
            pbVar18 = (byte *)0xfd0c0d;
            do {
              bVar7 = *pbVar18;
              pbVar18 = pbVar18 + 1;
              *puVar22 = (uint)bVar7;
              puVar22 = puVar22 + 1;
            } while (pbVar18 != (byte *)0xfd0c12);
            local_938 = 5;
            puVar22 = local_8fc;
            if (0x20 < local_930) {
              puVar22 = local_890 + 5;
            }
            *puVar22 = 0;
                    /* try { // try from 00ade51f to 00ade523 has its CatchHandler @ 00adfb00 */
            CEGUI::PropertySet::setProperty(*(String **)(pCVar29 + 0x108),(String *)&local_938);
                    /* try { // try from 00ade527 to 00ade52b has its CatchHandler @ 00adfbe5 */
            CEGUI::String::~String((String *)&local_938);
                    /* try { // try from 00ade52f to 00ade533 has its CatchHandler @ 00adfbd5 */
            CEGUI::String::~String((String *)local_888);
          }
          CEGUI::String::~String(this_04);
          local_1010 = 0x20;
          local_1008 = 0;
          local_ff8 = 0;
          local_1000 = 0;
          local_f70 = (undefined4 *)0x0;
          local_1018 = 0;
          local_ff0[0] = 0;
          CEGUI::String::grow((ulong)&local_1018);
          local_1018 = 0;
          puVar21 = local_ff0;
          if (0x20 < local_1010) {
            puVar21 = local_f70;
          }
          *puVar21 = 0;
          local_f60 = 0x20;
          local_f58 = 0;
          local_f48 = 0;
          local_f50 = 0;
          local_ec0 = (uint *)0x0;
          local_f68 = 0;
          local_f40[0] = 0;
                    /* try { // try from 00ade62e to 00ade632 has its CatchHandler @ 00adfb15 */
          CEGUI::String::grow((ulong)&local_f68);
          puVar22 = local_f40;
          if (0x20 < local_f60) {
            puVar22 = local_ec0;
          }
          pbVar18 = (byte *)0xfd0c0d;
          do {
            bVar7 = *pbVar18;
            pbVar18 = pbVar18 + 1;
            *puVar22 = (uint)bVar7;
            puVar22 = puVar22 + 1;
          } while (pbVar18 != (byte *)0xfd0c12);
          local_f68 = 5;
          puVar22 = local_f2c;
          if (0x20 < local_f60) {
            puVar22 = local_ec0 + 5;
          }
          *puVar22 = 0;
                    /* try { // try from 00ade69f to 00ade6a3 has its CatchHandler @ 00adfb17 */
          CEGUI::PropertySet::setProperty(*(String **)(pCVar29 + 0x148),(String *)&local_f68);
                    /* try { // try from 00ade6a7 to 00ade6ab has its CatchHandler @ 00adfb15 */
          CEGUI::String::~String((String *)&local_f68);
          CEGUI::String::~String((String *)&local_1018);
          if (local_14a8 != (UVector2 *)0x0) {
            local_b4 = 0;
            local_b8 = 0;
            local_ac = 0x3f800000;
            local_b0 = 0;
                    /* try { // try from 00ade6f9 to 00ade6fd has its CatchHandler @ 00adfb27 */
            CEGUI::Window::setPosition(local_14a8);
            local_c4 = 0;
            local_c8 = 0;
            local_bc = 0;
            local_c0 = 0;
                    /* try { // try from 00ade737 to 00ade73b has its CatchHandler @ 00adfb2f */
            CEGUI::Window::setPosition(local_14a8);
            CEGUI::Window::getSize();
                    /* try { // try from 00ade75b to 00ade75f has its CatchHandler @ 00adfb32 */
            CEGUI::Window::setSize(local_14a8);
            CEGUI::Window::moveToFront();
            CEGUI::Window::update(DAT_00fa4828);
          }
        }
      }
      pCVar29 = pCVar29 + 8;
      local_14a0 = local_14a0 + 4;
    } while (pCVar29 != this + 0x20);
    CEGUI::Window::moveToBack();
    CEGUI::Window::moveToFront();
    CEGUI::Window::moveToFront();
    CEGUI::Window::moveToFront();
  }
  return;
}

/* address=00adfda0
   symbol=CCombineMenu::setSlotIcon */

/* WARNING: Removing unreachable block (ram,0x00ae1452) */
/* WARNING: Removing unreachable block (ram,0x00ae14c6) */
/* WARNING: Removing unreachable block (ram,0x00ae15a5) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CCombineMenu::setSlotIcon(CEquipment*, int) */

void __thiscall CCombineMenu::setSlotIcon(CCombineMenu *this,CEquipment *param_1,int param_2)

{
  int *piVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  int iVar6;
  byte bVar7;
  char cVar8;
  uint uVar9;
  uint uVar10;
  long lVar11;
  long lVar12;
  float *pfVar13;
  float *pfVar14;
  char *pcVar15;
  byte *pbVar16;
  CEquipment *this_00;
  ulong uVar17;
  uint *puVar18;
  undefined4 *puVar19;
  length_error *this_01;
  ulong uVar20;
  long lVar21;
  byte *pbVar22;
  byte *pbVar23;
  UVector2 *pUVar24;
  String *pSVar25;
  ulong uVar26;
  bool bVar27;
  uint uVar28;
  float fVar29;
  uint uVar30;
  float fVar31;
  uint uVar32;
  UVector2 *local_12d0;
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

  lVar21 = (long)param_2;
  lVar11 = CEGUI::Window::getPosition();
  lVar12 = CEGUI::Window::getPosition();
  uVar10 = DAT_00fa86f4;
  uVar9 = DAT_00fa4810;
  fVar2 = *(float *)(lVar12 + 0xc);
  fVar3 = *(float *)(lVar11 + 0xc);
  fVar29 = (*(float *)(lVar11 + 8) + *(float *)(lVar12 + 8)) * 0.0;
  uVar28 = -(uint)(0.0 < fVar29);
  uVar32 = DAT_00fa4810 & uVar28;
  uVar30 = ~uVar28 & DAT_00fa86f4;
  pfVar13 = (float *)CEGUI::Window::getPosition();
  pfVar14 = (float *)CEGUI::Window::getPosition();
  fVar4 = pfVar13[1];
  fVar5 = pfVar14[1];
  fVar31 = (*pfVar13 + *pfVar14) * 0.0;
  uVar28 = -(uint)(0.0 < fVar31);
  local_12d0 = *(UVector2 **)(param_1 + 0x2c8);
  if (local_12d0 == (UVector2 *)0x0) {
    CEquipment::createIcon(param_1,*(CGameUI **)(this + 0xa8),false);
    local_12d0 = *(UVector2 **)(param_1 + 0x2c8);
    if (local_12d0 != (UVector2 *)0x0) {
      CEGUI::EventSet::setMutedState((bool)((char)local_12d0 + '8'));
      local_12d0[0x3e2] = (UVector2)0x1;
      goto LAB_00adfed8;
    }
  }
  else {
LAB_00adfed8:
    if (*(Window **)(local_12d0 + 0xb0) != (Window *)0x0) {
      CEGUI::Window::removeChildWindow(*(Window **)(local_12d0 + 0xb0));
    }
    CEGUI::Window::addChildWindow(*(Window **)(this + lVar21 * 8 + 0x148));
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
    puVar19 = local_630;
    if (0x20 < local_650) {
      puVar19 = local_5b0;
    }
    *puVar19 = 0;
    local_5a0 = 0x20;
    local_598 = 0;
    local_588 = 0;
    local_590 = 0;
    local_500 = (uint *)0x0;
    local_5a8 = 0;
    local_580[0] = 0;
                    /* try { // try from 00ae0216 to 00ae021a has its CatchHandler @ 00ae1505 */
    CEGUI::String::grow((ulong)&local_5a8);
    puVar18 = local_580;
    if (0x20 < local_5a0) {
      puVar18 = local_500;
    }
    pbVar16 = (byte *)0xfd0c0d;
    do {
      bVar7 = *pbVar16;
      pbVar16 = pbVar16 + 1;
      *puVar18 = (uint)bVar7;
      puVar18 = puVar18 + 1;
    } while (pbVar16 != (byte *)0xfd0c12);
    local_5a8 = 5;
    puVar18 = local_56c;
    if (0x20 < local_5a0) {
      puVar18 = local_500 + 5;
    }
    *puVar18 = 0;
                    /* try { // try from 00ae0285 to 00ae0289 has its CatchHandler @ 00ae14e5 */
    CEGUI::PropertySet::setProperty(*(String **)(this + lVar21 * 8 + 0x128),(String *)&local_5a8);
                    /* try { // try from 00ae028d to 00ae0291 has its CatchHandler @ 00ae1505 */
    CEGUI::String::~String((String *)&local_5a8);
    CEGUI::String::~String((String *)&local_658);
  }
  else {
    if (*(uint *)(param_1 + 0x3e0) < 2) {
      CEGUI::String::String(local_398,"onesocketglow");
                    /* try { // try from 00ae1354 to 00ae136b has its CatchHandler @ 00ae13e2 */
      CEGUI::Imageset::getImage(*(String **)(this + 0x198));
      CEGUI::PropertyHelper::imageToString(local_448);
                    /* try { // try from 00ae137c to 00ae1380 has its CatchHandler @ 00ae13db */
      CEGUI::String::String(local_4f8,"Image");
                    /* try { // try from 00ae1394 to 00ae1398 has its CatchHandler @ 00ae13d9 */
      CEGUI::PropertySet::setProperty(*(String **)(this + lVar21 * 8 + 0x128),local_4f8);
                    /* try { // try from 00ae139c to 00ae13a0 has its CatchHandler @ 00ae13db */
      CEGUI::String::~String(local_4f8);
                    /* try { // try from 00ae13a4 to 00ae13a8 has its CatchHandler @ 00ae13e2 */
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
      puVar18 = local_160;
      if (0x20 < local_180) {
        puVar18 = local_e0;
      }
      pcVar15 = "twosocketglow";
      do {
        bVar7 = *pcVar15;
        pcVar15 = pcVar15 + 1;
        *puVar18 = (uint)bVar7;
        puVar18 = puVar18 + 1;
      } while ((byte *)pcVar15 != (byte *)0xfe60d0);
      local_188 = 0xd;
      puVar18 = local_12c;
      if (0x20 < local_180) {
        puVar18 = local_e0 + 0xd;
      }
      *puVar18 = 0;
                    /* try { // try from 00adfffc to 00ae0013 has its CatchHandler @ 00ae150a */
      CEGUI::Imageset::getImage(*(String **)(this + 0x198));
      CEGUI::PropertyHelper::imageToString(local_238);
      local_2e0 = 0x20;
      local_2d8 = 0;
      local_2c8 = 0;
      local_2d0 = 0;
      local_240 = (uint *)0x0;
      local_2e8 = 0;
      local_2c0[0] = 0;
                    /* try { // try from 00ae0077 to 00ae007b has its CatchHandler @ 00ae1442 */
      CEGUI::String::grow((ulong)&local_2e8);
      puVar18 = local_2c0;
      if (0x20 < local_2e0) {
        puVar18 = local_240;
      }
      pbVar16 = (byte *)0xfd0c0d;
      do {
        bVar7 = *pbVar16;
        pbVar16 = pbVar16 + 1;
        *puVar18 = (uint)bVar7;
        puVar18 = puVar18 + 1;
      } while (pbVar16 != (byte *)0xfd0c12);
      local_2e8 = 5;
      puVar18 = local_2ac;
      if (0x20 < local_2e0) {
        puVar18 = local_240 + 5;
      }
      *puVar18 = 0;
                    /* try { // try from 00ae00ee to 00ae00f2 has its CatchHandler @ 00ae1412 */
      CEGUI::PropertySet::setProperty(*(String **)(this + lVar21 * 8 + 0x128),(String *)&local_2e8);
                    /* try { // try from 00ae00f6 to 00ae00fa has its CatchHandler @ 00ae1442 */
      CEGUI::String::~String((String *)&local_2e8);
                    /* try { // try from 00ae00fe to 00ae0102 has its CatchHandler @ 00ae150a */
      CEGUI::String::~String((String *)local_238);
      CEGUI::String::~String((String *)&local_188);
    }
    CEGUI::Window::moveToFront();
  }
  uVar26 = (ulong)(fVar2 + fVar3 + (float)(int)(fVar29 + (float)(uVar30 | uVar32)));
  if (1 < *(uint *)(param_1 + 0x3e0)) {
    CEGUI::Window::getSize();
    uVar30 = -(uint)(0.0 < local_70 * 0.0);
    uVar26 = (ulong)((float)(uVar26 & 0xffffffff) +
                    ((float)(int)((float)(~uVar30 & DAT_00fa86f4 | DAT_00fa4810 & uVar30) +
                                 local_70 * 0.0) + local_6c) * _DAT_00fe6520);
  }
  if (*(int *)(param_1 + 0x3f0) != 0) {
    uVar30 = 0;
    do {
      if (uVar30 < *(uint *)(param_1 + 0x3f4)) {
        this_00 = *(CEquipment **)((ulong)uVar30 * 8 + *(long *)(param_1 + 1000));
        pUVar24 = *(UVector2 **)(this_00 + 0x2c8);
        if (pUVar24 != (UVector2 *)0x0) goto LAB_00ae038a;
LAB_00ae04e0:
        CEquipment::createIcon(this_00,*(CGameUI **)(this + 0xa8),false);
        pUVar24 = *(UVector2 **)(this_00 + 0x2c8);
        if (pUVar24 != (UVector2 *)0x0) {
          CEGUI::EventSet::setMutedState((bool)((char)pUVar24 + '8'));
          pUVar24[0x3e2] = (UVector2)0x1;
          goto LAB_00ae038a;
        }
      }
      else {
        this_00 = (CEquipment *)**(long **)(param_1 + 1000);
        pUVar24 = *(UVector2 **)(this_00 + 0x2c8);
        if (pUVar24 == (UVector2 *)0x0) goto LAB_00ae04e0;
LAB_00ae038a:
        if (*(Window **)(pUVar24 + 0xb0) != (Window *)0x0) {
          CEGUI::Window::removeChildWindow(*(Window **)(pUVar24 + 0xb0));
        }
        CEGUI::Window::addChildWindow(*(Window **)(this + 0x60));
        local_84 = (float)((long)(fVar4 + fVar5 +
                                 (float)(int)((float)(~uVar28 & uVar10 | uVar9 & uVar28) + fVar31))
                          & 0xffffffff);
        local_7c = (float)(uVar26 & 0xffffffff);
        local_88 = 0;
        local_80 = 0;
                    /* try { // try from 00ae03f4 to 00ae03f8 has its CatchHandler @ 00ae14d2 */
        CEGUI::Window::setPosition(pUVar24);
        CEGUI::Window::getSize();
                    /* try { // try from 00ae0416 to 00ae041a has its CatchHandler @ 00ae14d7 */
        CEGUI::Window::setSize(pUVar24);
        CEGUI::Window::moveToFront();
        pUVar24[0x3e2] = (UVector2)0x1;
      }
      uVar30 = uVar30 + 1;
      CEGUI::Window::getSize();
      uVar32 = -(uint)(0.0 < local_a0 * 0.0);
      if (*(uint *)(param_1 + 0x3f0) <= uVar30) break;
      uVar26 = (ulong)((float)(uVar26 & 0xffffffff) +
                      ((float)(int)((float)(~uVar32 & DAT_00fa86f4 | DAT_00fa4810 & uVar32) +
                                   local_a0 * 0.0) + local_9c) * DAT_00fa4830);
    } while( true );
  }
  cVar8 = (**(code **)(*(long *)param_1 + 0x2f8))(param_1,*(undefined8 *)(this + 0x90),0);
  if (cVar8 == '\0') {
    cVar8 = (**(code **)(*(long *)param_1 + 0x2b0))(param_1);
    if (cVar8 == '\0') {
      pSVar25 = (String *)&local_10a8;
      local_10a0 = 0x20;
      local_1098 = 0;
      local_1088 = 0;
      local_1090 = 0;
      local_1000 = (uint *)0x0;
      local_10a8 = 0;
      local_1080[0] = 0;
      CEGUI::String::grow((ulong)pSVar25);
      puVar18 = local_1080;
      if (0x20 < local_10a0) {
        puVar18 = local_1000;
      }
      pbVar16 = (byte *)0xfe60e3;
      do {
        bVar7 = *pbVar16;
        pbVar16 = pbVar16 + 1;
        *puVar18 = (uint)bVar7;
        puVar18 = puVar18 + 1;
      } while (pbVar16 != (byte *)0xfe60ee);
      local_10a8 = 0xb;
      puVar18 = local_1054;
      if (0x20 < local_10a0) {
        puVar18 = local_1000 + 0xb;
      }
      *puVar18 = 0;
                    /* try { // try from 00ae0e84 to 00ae0e9b has its CatchHandler @ 00ae1434 */
      CEGUI::Imageset::getImage(*(String **)(this + 0x198));
      CEGUI::PropertyHelper::imageToString(local_1158);
      local_1200 = 0x20;
      local_11f8 = 0;
      local_11e8 = 0;
      local_11f0 = 0;
      local_1160 = (uint *)0x0;
      local_1208 = 0;
      local_11e0[0] = 0;
                    /* try { // try from 00ae0eff to 00ae0f03 has its CatchHandler @ 00ae1436 */
      CEGUI::String::grow((ulong)&local_1208);
      puVar18 = local_11e0;
      if (0x20 < local_1200) {
        puVar18 = local_1160;
      }
      pbVar16 = (byte *)0xfd0c0d;
      do {
        bVar7 = *pbVar16;
        pbVar16 = pbVar16 + 1;
        *puVar18 = (uint)bVar7;
        puVar18 = puVar18 + 1;
      } while (pbVar16 != (byte *)0xfd0c12);
      local_1208 = 5;
      puVar18 = local_11cc;
      if (0x20 < local_1200) {
        puVar18 = local_1160 + 5;
      }
      *puVar18 = 0;
                    /* try { // try from 00ae0f6e to 00ae0f72 has its CatchHandler @ 00ae1515 */
      CEGUI::PropertySet::setProperty(*(String **)(this + lVar21 * 8 + 0x108),(String *)&local_1208)
      ;
                    /* try { // try from 00ae0f76 to 00ae0f7a has its CatchHandler @ 00ae1436 */
      CEGUI::String::~String((String *)&local_1208);
                    /* try { // try from 00ae0f7e to 00ae0f82 has its CatchHandler @ 00ae1434 */
      CEGUI::String::~String((String *)local_1158);
    }
    else {
      pSVar25 = (String *)&local_e98;
      local_e90 = 0x20;
      local_e88 = 0;
      local_e78 = 0;
      local_e80 = 0;
      local_df0 = (uint *)0x0;
      local_e98 = 0;
      local_e70[0] = 0;
      CEGUI::String::grow((ulong)pSVar25);
      puVar18 = local_e70;
      if (0x20 < local_e90) {
        puVar18 = local_df0;
      }
      pcVar15 = "blueredslotglow";
      do {
        bVar7 = *pcVar15;
        pcVar15 = pcVar15 + 1;
        *puVar18 = (uint)bVar7;
        puVar18 = puVar18 + 1;
      } while ((byte *)pcVar15 != (byte *)0xfe60ee);
      local_e98 = 0xf;
      puVar18 = local_e34;
      if (0x20 < local_e90) {
        puVar18 = local_df0 + 0xf;
      }
      *puVar18 = 0;
                    /* try { // try from 00ae0b8c to 00ae0ba3 has its CatchHandler @ 00ae14dc */
      CEGUI::Imageset::getImage(*(String **)(this + 0x198));
      CEGUI::PropertyHelper::imageToString(local_f48);
      local_ff0 = 0x20;
      local_fe8 = 0;
      local_fd8 = 0;
      local_fe0 = 0;
      local_f50 = (uint *)0x0;
      local_ff8 = 0;
      local_fd0[0] = 0;
                    /* try { // try from 00ae0c07 to 00ae0c0b has its CatchHandler @ 00ae150f */
      CEGUI::String::grow((ulong)&local_ff8);
      puVar18 = local_fd0;
      if (0x20 < local_ff0) {
        puVar18 = local_f50;
      }
      pbVar16 = (byte *)0xfd0c0d;
      do {
        bVar7 = *pbVar16;
        pbVar16 = pbVar16 + 1;
        *puVar18 = (uint)bVar7;
        puVar18 = puVar18 + 1;
      } while (pbVar16 != (byte *)0xfd0c12);
      local_ff8 = 5;
      puVar18 = local_fbc;
      if (0x20 < local_ff0) {
        puVar18 = local_f50 + 5;
      }
      *puVar18 = 0;
                    /* try { // try from 00ae0c76 to 00ae0c7a has its CatchHandler @ 00ae1432 */
      CEGUI::PropertySet::setProperty(*(String **)(this + lVar21 * 8 + 0x108),(String *)&local_ff8);
                    /* try { // try from 00ae0c7e to 00ae0c82 has its CatchHandler @ 00ae150f */
      CEGUI::String::~String((String *)&local_ff8);
                    /* try { // try from 00ae0c86 to 00ae0c8a has its CatchHandler @ 00ae14dc */
      CEGUI::String::~String((String *)local_f48);
    }
LAB_00ae0723:
    CEGUI::String::~String(pSVar25);
  }
  else {
    cVar8 = CBaseUnit::ISA((CBaseUnit *)param_1,0x36);
    if (cVar8 != '\0') {
      pSVar25 = (String *)&local_708;
      local_700 = 0x20;
      local_6f8 = 0;
      local_6e8 = 0;
      local_6f0 = 0;
      local_660 = (uint *)0x0;
      local_708 = 0;
      local_6e0[0] = 0;
      CEGUI::String::grow((ulong)pSVar25);
      puVar18 = local_6e0;
      if (0x20 < local_700) {
        puVar18 = local_660;
      }
      pcVar15 = "goldslotglow";
      do {
        bVar7 = *pcVar15;
        pcVar15 = pcVar15 + 1;
        *puVar18 = (uint)bVar7;
        puVar18 = puVar18 + 1;
      } while ((byte *)pcVar15 != (byte *)0xfe60a7);
      local_708 = 0xc;
      puVar18 = local_6b0;
      if (0x20 < local_700) {
        puVar18 = local_660 + 0xc;
      }
      *puVar18 = 0;
                    /* try { // try from 00ae0624 to 00ae063b has its CatchHandler @ 00ae142c */
      CEGUI::Imageset::getImage(*(String **)(this + 0x198));
      CEGUI::PropertyHelper::imageToString(local_7b8);
      local_860 = 0x20;
      local_858 = 0;
      local_848 = 0;
      local_850 = 0;
      local_7c0 = (uint *)0x0;
      local_868 = 0;
      local_840[0] = 0;
                    /* try { // try from 00ae069f to 00ae06a3 has its CatchHandler @ 00ae1427 */
      CEGUI::String::grow((ulong)&local_868);
      puVar18 = local_840;
      if (0x20 < local_860) {
        puVar18 = local_7c0;
      }
      pbVar16 = (byte *)0xfd0c0d;
      do {
        bVar7 = *pbVar16;
        pbVar16 = pbVar16 + 1;
        *puVar18 = (uint)bVar7;
        puVar18 = puVar18 + 1;
      } while (pbVar16 != (byte *)0xfd0c12);
      local_868 = 5;
      puVar18 = local_82c;
      if (0x20 < local_860) {
        puVar18 = local_7c0 + 5;
      }
      *puVar18 = 0;
                    /* try { // try from 00ae070e to 00ae0712 has its CatchHandler @ 00ae14c1 */
      CEGUI::PropertySet::setProperty(*(String **)(this + lVar21 * 8 + 0x108),(String *)&local_868);
                    /* try { // try from 00ae0716 to 00ae071a has its CatchHandler @ 00ae1427 */
      CEGUI::String::~String((String *)&local_868);
                    /* try { // try from 00ae071e to 00ae0722 has its CatchHandler @ 00ae142c */
      CEGUI::String::~String((String *)local_7b8);
      goto LAB_00ae0723;
    }
    cVar8 = (**(code **)(*(long *)param_1 + 0x2b0))(param_1);
    if (cVar8 == '\0') {
      pSVar25 = (String *)&local_de8;
      local_de0 = 0x20;
      local_dd8 = 0;
      local_dc8 = 0;
      local_dd0 = 0;
      local_d40 = (undefined4 *)0x0;
      local_de8 = 0;
      local_dc0[0] = 0;
      CEGUI::String::grow((ulong)pSVar25);
      local_de8 = 0;
      puVar19 = local_dc0;
      if (0x20 < local_de0) {
        puVar19 = local_d40;
      }
      *puVar19 = 0;
      local_d30 = 0x20;
      local_d28 = 0;
      local_d18 = 0;
      local_d20 = 0;
      local_c90 = (uint *)0x0;
      local_d38 = 0;
      local_d10[0] = 0;
                    /* try { // try from 00ae10d4 to 00ae10d8 has its CatchHandler @ 00ae140d */
      CEGUI::String::grow((ulong)&local_d38);
      puVar18 = local_d10;
      if (0x20 < local_d30) {
        puVar18 = local_c90;
      }
      pbVar16 = (byte *)0xfd0c0d;
      do {
        bVar7 = *pbVar16;
        pbVar16 = pbVar16 + 1;
        *puVar18 = (uint)bVar7;
        puVar18 = puVar18 + 1;
      } while (pbVar16 != (byte *)0xfd0c12);
      local_d38 = 5;
      puVar18 = local_cfc;
      if (0x20 < local_d30) {
        puVar18 = local_c90 + 5;
      }
      *puVar18 = 0;
                    /* try { // try from 00ae1156 to 00ae115a has its CatchHandler @ 00ae13f2 */
      CEGUI::PropertySet::setProperty(*(String **)(this + lVar21 * 8 + 0x108),(String *)&local_d38);
                    /* try { // try from 00ae115e to 00ae1162 has its CatchHandler @ 00ae140d */
      CEGUI::String::~String((String *)&local_d38);
      goto LAB_00ae0723;
    }
    cVar8 = CBaseUnit::ISA((CBaseUnit *)param_1,0x37);
    if (cVar8 == '\0') {
      pSVar25 = local_b28;
      CEGUI::String::String(pSVar25,"greenslotglow");
                    /* try { // try from 00ae12db to 00ae12f2 has its CatchHandler @ 00ae1545 */
      CEGUI::Imageset::getImage(*(String **)(this + 0x198));
      CEGUI::PropertyHelper::imageToString(local_bd8);
                    /* try { // try from 00ae1303 to 00ae1307 has its CatchHandler @ 00ae1535 */
      CEGUI::String::String(local_c88,"Image");
                    /* try { // try from 00ae131b to 00ae131f has its CatchHandler @ 00ae1525 */
      CEGUI::PropertySet::setProperty(*(String **)(this + lVar21 * 8 + 0x108),local_c88);
                    /* try { // try from 00ae1323 to 00ae1327 has its CatchHandler @ 00ae1535 */
      CEGUI::String::~String(local_c88);
                    /* try { // try from 00ae132b to 00ae132f has its CatchHandler @ 00ae1545 */
      CEGUI::String::~String((String *)local_bd8);
    }
    else {
      pSVar25 = local_918;
      CEGUI::String::String(pSVar25,"blueslotglow");
                    /* try { // try from 00ae0d56 to 00ae0d6d has its CatchHandler @ 00ae13e9 */
      CEGUI::Imageset::getImage(*(String **)(this + 0x198));
      CEGUI::PropertyHelper::imageToString(local_9c8);
                    /* try { // try from 00ae0d7e to 00ae0d82 has its CatchHandler @ 00ae13e7 */
      CEGUI::String::String(local_a78,"Image");
                    /* try { // try from 00ae0d96 to 00ae0d9a has its CatchHandler @ 00ae13b6 */
      CEGUI::PropertySet::setProperty(*(String **)(this + lVar21 * 8 + 0x108),local_a78);
                    /* try { // try from 00ae0d9e to 00ae0da2 has its CatchHandler @ 00ae13e7 */
      CEGUI::String::~String(local_a78);
                    /* try { // try from 00ae0da6 to 00ae0daa has its CatchHandler @ 00ae13e9 */
      CEGUI::String::~String((String *)local_9c8);
    }
    CEGUI::String::~String(pSVar25);
  }
  if (local_12d0 != (UVector2 *)0x0) {
    local_b4 = 0;
    local_b8 = 0;
    local_ac = 0x3f800000;
    local_b0 = 0;
                    /* try { // try from 00ae0770 to 00ae0774 has its CatchHandler @ 00ae1444 */
    CEGUI::Window::setPosition(local_12d0);
    local_c4 = 0;
    local_c8 = 0;
    local_bc = 0;
    local_c0 = 0;
                    /* try { // try from 00ae07ae to 00ae07b2 has its CatchHandler @ 00ae144c */
    CEGUI::Window::setPosition(local_12d0);
    CEGUI::Window::getSize();
                    /* try { // try from 00ae07d8 to 00ae07dc has its CatchHandler @ 00ae1460 */
    CEGUI::Window::setSize(local_12d0);
    CEGUI::Window::moveToFront();
    *(CCombineMenu **)(local_12d0 + 0x1d8) = this + lVar21 * 4 + 0xe8;
  }
  if (*(long *)(this + lVar21 * 8 + 0x168) == 0) {
    return;
  }
  bVar27 = SUB81(*(long *)(this + lVar21 * 8 + 0x168),0);
  if (*(int *)(param_1 + 0x238) < 2) {
    CEGUI::Window::setVisible(bVar27);
    return;
  }
  CEGUI::Window::setVisible(bVar27);
  STRINGS::GetValueAsString((STRINGS *)local_58,*(int *)(param_1 + 0x238));
                    /* try { // try from 00ae0858 to 00ae085c has its CatchHandler @ 00ae1462 */
  std::operator+((char *)&local_48,(string *)&DAT_0103f7f3);
  if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_58[0] + -8);
    iVar6 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar6 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
    }
  }
  pbVar16 = local_48;
  local_12b0 = 0x20;
  uVar26 = 0;
  local_12a8 = 0;
  local_1298 = 0;
  local_12a0 = 0;
  local_1210 = (uint *)0x0;
  local_12b8 = 0;
  local_1290[0] = 0;
  bVar7 = *local_48;
  while (bVar7 != 0) {
    uVar26 = uVar26 + 1;
    bVar7 = local_48[uVar26];
  }
  if (uVar26 == CEGUI::String::npos) {
                    /* try { // try from 00ae122b to 00ae122f has its CatchHandler @ 00ae159c */
    std::string::string((string *)local_68,"Length for utf8 encoded string can not be \'npos\'",
                        local_3a);
    this_01 = (length_error *)__cxa_allocate_exception(0x10);
                    /* try { // try from 00ae1243 to 00ae1247 has its CatchHandler @ 00ae1584 */
    std::length_error::length_error(this_01,(string *)local_68);
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
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 00ae126f to 00ae1273 has its CatchHandler @ 00ae1475 */
    __cxa_throw(this_01,&std::length_error::typeinfo,std::length_error::~length_error);
  }
  lVar11 = 0;
  uVar20 = uVar26;
  pbVar22 = local_48;
  while (uVar20 != 0) {
    bVar7 = *pbVar22;
    uVar17 = uVar20 - 1;
    pbVar23 = pbVar22 + 1;
    if ((char)bVar7 < '\0') {
      if (bVar7 < 0xe0) {
        uVar17 = uVar20 - 2;
        pbVar23 = pbVar22 + 2;
      }
      else if (bVar7 < 0xf0) {
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
  CEGUI::String::grow((ulong)&local_12b8);
  puVar18 = local_1290;
  if (0x20 < local_12b0) {
    puVar18 = local_1210;
  }
  if (uVar26 == 0) {
    uVar26 = 0;
    if (*pbVar16 == 0) goto LAB_00ae0930;
    do {
      uVar26 = uVar26 + 1;
    } while (pbVar16[uVar26] != 0);
    bVar27 = uVar26 != 0 && local_12b0 != 0;
  }
  else {
    bVar27 = local_12b0 != 0;
  }
  if (bVar27) {
    uVar17 = 0;
    uVar20 = local_12b0;
    uVar9 = 0;
    while( true ) {
      bVar7 = pbVar16[uVar17];
      uVar28 = (uint)bVar7;
      uVar10 = uVar9 + 1;
      if ((char)bVar7 < '\0') {
        uVar28 = (uint)bVar7;
        if (bVar7 < 0xe0) {
          uVar17 = (ulong)uVar10;
          uVar10 = uVar9 + 2;
          uVar28 = pbVar16[uVar17] & 0x3f | (uVar28 & 0x1f) << 6;
        }
        else if (bVar7 < 0xf0) {
          uVar17 = (ulong)uVar10;
          uVar10 = uVar9 + 3;
          uVar28 = pbVar16[uVar9 + 2] & 0x3f | (uVar28 & 0xf) << 0xc | (pbVar16[uVar17] & 0x3f) << 6
          ;
        }
        else {
          uVar17 = (ulong)uVar10;
          uVar10 = uVar9 + 4;
          uVar28 = (pbVar16[uVar17] & 0x3f) << 0xc | pbVar16[uVar9 + 3] & 0x3f |
                   (uVar28 & 7) << 0x12 | (pbVar16[uVar9 + 2] & 0x3f) << 6;
        }
      }
      *puVar18 = uVar28;
      uVar17 = (ulong)uVar10;
      uVar20 = uVar20 - 1;
      if ((uVar26 <= uVar17) || (uVar20 == 0)) break;
      puVar18 = puVar18 + 1;
      uVar9 = uVar10;
    }
  }
LAB_00ae0930:
  puVar18 = local_1290;
  if (0x20 < local_12b0) {
    puVar18 = local_1210;
  }
  puVar18[lVar11] = 0;
  local_12b8 = lVar11;
                    /* try { // try from 00ae0961 to 00ae0965 has its CatchHandler @ 00ae1488 */
  CEGUI::Window::setText(*(String **)(this + lVar21 * 8 + 0x168));
                    /* try { // try from 00ae0969 to 00ae09ef has its CatchHandler @ 00ae1475 */
  CEGUI::String::~String((String *)&local_12b8);
  if ((allocator *)(local_48 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    pbVar16 = local_48 + -8;
    iVar6 = *(int *)pbVar16;
    *(int *)pbVar16 = *(int *)pbVar16 + -1;
    UNLOCK();
    if (iVar6 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_48 + -0x18));
    }
  }
  return;
}

/* address=00ae15f0
   symbol=CCombineMenu::isRight */

/* CCombineMenu::isRight() */

undefined8 CCombineMenu::isRight(void)

{
  return 0;
}

/* address=00ae1600
   symbol=CCombineMenu::open */

/* CCombineMenu::open() */

byte __thiscall CCombineMenu::open(CCombineMenu *this)

{
  byte bVar1;

  bVar1 = 1;
  if (this[0x98] == (CCombineMenu)0x0) {
    bVar1 = (byte)this[0x99] ^ 1;
  }
  return bVar1;
}

/* address=00ae1620
   symbol=CCombineMenu::openPartial */

/* CCombineMenu::openPartial() */

CCombineMenu __thiscall CCombineMenu::openPartial(CCombineMenu *this)

{
  return this[0x98];
}

/* address=00ae1630
   symbol=CCombineMenu::screenEdge */

/* CCombineMenu::screenEdge() */

undefined4 __thiscall CCombineMenu::screenEdge(CCombineMenu *this)

{
  return *(undefined4 *)(this + 0xd8);
}

/* address=00ae1640
   symbol=CCombineMenu::getOwner */

/* CCombineMenu::getOwner() */

undefined8 __thiscall CCombineMenu::getOwner(CCombineMenu *this)

{
  return *(undefined8 *)(this + 0x88);
}

/* export-summary functions=42 failures=0 */
