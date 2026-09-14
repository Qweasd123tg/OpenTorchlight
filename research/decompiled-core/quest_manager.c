/* Targeted Ghidra class export.
   namespace=CQuestManager
   Treat pseudocode as navigation evidence. */


/* address=00d264a0
   symbol=CQuestManager::getSingleton */

/* CQuestManager::getSingleton() */

undefined8 CQuestManager::getSingleton(void)

{
  return g_pQuestManager;
}

/* address=00d264b0
   symbol=CQuestManager::setPlayer */

/* CQuestManager::setPlayer(CPlayer*) */

void __thiscall CQuestManager::setPlayer(CQuestManager *this,CPlayer *param_1)

{
  *(CPlayer **)(this + 0x10) = param_1;
  return;
}

/* address=00d264c0
   symbol=CQuestManager::update */

/* CQuestManager::update(float) */

void CQuestManager::update(float param_1)

{
  return;
}

/* address=00d264d0
   symbol=CQuestManager::getPlayerHasQuest */

/* CQuestManager::getPlayerHasQuest(CQuest*) */

undefined8 __thiscall CQuestManager::getPlayerHasQuest(CQuestManager *this,CQuest *param_1)

{
  long *plVar1;
  long *plVar2;
  uint uVar3;

  if (*(uint *)(this + 0x20) != 0) {
    plVar2 = *(long **)(this + 0x18);
    uVar3 = 0;
    if (param_1 == (CQuest *)*plVar2) {
      return 1;
    }
    while (uVar3 = uVar3 + 1, uVar3 < *(uint *)(this + 0x20)) {
      plVar1 = plVar2 + 1;
      plVar2 = plVar2 + 1;
      if (param_1 == (CQuest *)*plVar1) {
        return CONCAT71((int7)((ulong)*plVar1 >> 8),uVar3 != 0xffffffff);
      }
    }
  }
  return 0;
}

/* address=00d26520
   symbol=CQuestManager::destroyIcons */

/* CQuestManager::destroyIcons() */

void __thiscall CQuestManager::destroyIcons(CQuestManager *this)

{
  _Rb_tree_node_base *p_Var1;

  for (p_Var1 = *(_Rb_tree_node_base **)(this + 0x58); p_Var1 != (_Rb_tree_node_base *)(this + 0x48)
      ; p_Var1 = (_Rb_tree_node_base *)std::_Rb_tree_increment(p_Var1)) {
    CQuest::destroyIcons(*(CQuest **)(p_Var1 + 0x28));
  }
  return;
}

/* address=00d26560
   symbol=CQuestManager::resetQuestManager */

/* CQuestManager::resetQuestManager(bool) */

void __thiscall CQuestManager::resetQuestManager(CQuestManager *this,bool param_1)

{
  _Rb_tree_node_base *p_Var1;

  *(undefined4 *)(this + 0x20) = 0;
  *(undefined4 *)(this + 0x24) = 0;
  if (*(void **)(this + 0x18) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x18));
  }
  p_Var1 = *(_Rb_tree_node_base **)(this + 0x88);
  *(undefined8 *)(this + 0x18) = 0;
  for (; p_Var1 != (_Rb_tree_node_base *)(this + 0x78);
      p_Var1 = (_Rb_tree_node_base *)std::_Rb_tree_increment(p_Var1)) {
    p_Var1[0x28] = (_Rb_tree_node_base)0x0;
  }
  for (p_Var1 = *(_Rb_tree_node_base **)(this + 0x58); p_Var1 != (_Rb_tree_node_base *)(this + 0x48)
      ; p_Var1 = (_Rb_tree_node_base *)std::_Rb_tree_increment(p_Var1)) {
    CQuest::reinitializeQuest(*(CQuest **)(p_Var1 + 0x28),param_1,false);
  }
  return;
}

/* address=00d265f0
   symbol=CQuestManager::getDetailsForQuest */

/* CQuestManager::getDetailsForQuest(CQuest*) */

CQuest * CQuestManager::getDetailsForQuest(CQuest *param_1)

{
  long in_RDX;

  if (in_RDX != 0) {
    CQuest::getQuestDetails();
    return param_1;
  }
  std::wstring::wstring((wstring_conflict *)param_1,(wstring_conflict *)&::EMPTY_WSTRING);
  return param_1;
}

/* address=00d26620
   symbol=CQuestManager::giveRewardForQuest */

/* CQuestManager::giveRewardForQuest(CQuest*) */

void __thiscall CQuestManager::giveRewardForQuest(CQuestManager *this,CQuest *param_1)

{
  if (param_1 != (CQuest *)0x0) {
    CQuest::giveRewardForQuest(param_1);
    return;
  }
  return;
}

/* address=00d26640
   symbol=CQuestManager::populate */

/* CQuestManager::populate(CLevel*) */

void __thiscall CQuestManager::populate(CQuestManager *this,CLevel *param_1)

{
  _Rb_tree_node_base *p_Var1;

  for (p_Var1 = *(_Rb_tree_node_base **)(this + 0x58); p_Var1 != (_Rb_tree_node_base *)(this + 0x48)
      ; p_Var1 = (_Rb_tree_node_base *)std::_Rb_tree_increment(p_Var1)) {
    CQuest::populate(*(CQuest **)(p_Var1 + 0x28),param_1);
  }
  return;
}

/* address=00d2d8e0
   symbol=CQuestManager::getQuestIsActive */

/* CQuestManager::getQuestIsActive(std::wstring const&) */

undefined8 __thiscall CQuestManager::getQuestIsActive(CQuestManager *this,wstring_conflict *param_1)

{
  uint uVar1;
  uint uVar2;
  wchar_t *__s2;
  size_t __n;
  wchar_t *__s1;
  size_t sVar3;
  int iVar4;
  uint uVar5;
  long lVar6;

  uVar1 = *(uint *)(this + 0x20);
  if (uVar1 != 0) {
    __s2 = *(wchar_t **)param_1;
    uVar2 = *(uint *)(this + 0x24);
    lVar6 = 0;
    uVar5 = 0;
    __n = *(size_t *)(__s2 + -6);
    do {
      if (uVar5 < uVar2) {
        __s1 = *(wchar_t **)(*(long *)(lVar6 + *(long *)(this + 0x18)) + 0x50);
        sVar3 = *(size_t *)(__s1 + -6);
      }
      else {
        __s1 = *(wchar_t **)(**(long **)(this + 0x18) + 0x50);
        sVar3 = *(size_t *)(__s1 + -6);
      }
      if ((sVar3 == __n) && (iVar4 = wmemcmp(__s1,__s2,__n), iVar4 == 0)) {
        return 1;
      }
      uVar5 = uVar5 + 1;
      lVar6 = lVar6 + 8;
    } while (uVar5 < uVar1);
  }
  return 0;
}

/* address=00d2dca0
   symbol=CQuestManager::getQuestComplete */

/* CQuestManager::getQuestComplete(std::wstring const&) */

CQuestManager __thiscall
CQuestManager::getQuestComplete(CQuestManager *this,wstring_conflict *param_1)

{
  CQuestManager *pCVar1;
  wchar_t *__s2;
  ulong uVar2;
  ulong uVar3;
  CQuestManager *pCVar4;
  int iVar5;
  ulong uVar6;
  CQuestManager *pCVar7;
  long lVar8;
  CQuestManager *pCVar9;

  pCVar1 = this + 0x78;
  pCVar7 = *(CQuestManager **)(this + 0x80);
  pCVar9 = pCVar1;
  if (pCVar7 != (CQuestManager *)0x0) {
    __s2 = *(wchar_t **)param_1;
    uVar2 = *(ulong *)(__s2 + -6);
    do {
      uVar3 = *(ulong *)(*(wchar_t **)(pCVar7 + 0x20) + -6);
      uVar6 = uVar3;
      if (uVar2 <= uVar3) {
        uVar6 = uVar2;
      }
      iVar5 = wmemcmp(*(wchar_t **)(pCVar7 + 0x20),__s2,uVar6);
      if (iVar5 == 0) {
        lVar8 = uVar3 - uVar2;
        if (0x7fffffff < lVar8) goto LAB_00d2dcd6;
        if (-0x80000001 < lVar8) {
          iVar5 = (int)lVar8;
          goto LAB_00d2dcd2;
        }
LAB_00d2dd18:
        pCVar4 = *(CQuestManager **)(pCVar7 + 0x18);
      }
      else {
LAB_00d2dcd2:
        if (iVar5 < 0) goto LAB_00d2dd18;
LAB_00d2dcd6:
        pCVar4 = *(CQuestManager **)(pCVar7 + 0x10);
        pCVar9 = pCVar7;
      }
      pCVar7 = pCVar4;
    } while (pCVar7 != (CQuestManager *)0x0);
  }
  if (pCVar1 != pCVar9) {
    uVar2 = *(ulong *)(*(wchar_t **)(pCVar9 + 0x20) + -6);
    uVar3 = *(ulong *)(*(wchar_t **)param_1 + -6);
    uVar6 = uVar3;
    if (uVar2 <= uVar3) {
      uVar6 = uVar2;
    }
    iVar5 = wmemcmp(*(wchar_t **)param_1,*(wchar_t **)(pCVar9 + 0x20),uVar6);
    if (iVar5 == 0) {
      lVar8 = uVar3 - uVar2;
      if (0x7fffffff < lVar8) goto LAB_00d2dd86;
      if (lVar8 < -0x80000000) {
        return (CQuestManager)0x0;
      }
      iVar5 = (int)lVar8;
    }
    if (-1 < iVar5) {
LAB_00d2dd86:
      return pCVar9[0x28];
    }
  }
  return (CQuestManager)0x0;
}

/* address=00d2dda0
   symbol=CQuestManager::getQuestByName */

/* CQuestManager::getQuestByName(std::wstring const&) */

undefined8 __thiscall CQuestManager::getQuestByName(CQuestManager *this,wstring_conflict *param_1)

{
  CQuestManager *pCVar1;
  wchar_t *__s2;
  ulong uVar2;
  ulong uVar3;
  CQuestManager *pCVar4;
  int iVar5;
  ulong uVar6;
  CQuestManager *pCVar7;
  long lVar8;
  CQuestManager *pCVar9;

  pCVar1 = this + 0x48;
  pCVar7 = *(CQuestManager **)(this + 0x50);
  pCVar9 = pCVar1;
  if (pCVar7 != (CQuestManager *)0x0) {
    __s2 = *(wchar_t **)param_1;
    uVar2 = *(ulong *)(__s2 + -6);
    do {
      uVar3 = *(ulong *)(*(wchar_t **)(pCVar7 + 0x20) + -6);
      uVar6 = uVar3;
      if (uVar2 <= uVar3) {
        uVar6 = uVar2;
      }
      iVar5 = wmemcmp(*(wchar_t **)(pCVar7 + 0x20),__s2,uVar6);
      if (iVar5 == 0) {
        lVar8 = uVar3 - uVar2;
        if (0x7fffffff < lVar8) goto LAB_00d2ddd6;
        if (-0x80000001 < lVar8) {
          iVar5 = (int)lVar8;
          goto LAB_00d2ddd2;
        }
LAB_00d2de18:
        pCVar4 = *(CQuestManager **)(pCVar7 + 0x18);
      }
      else {
LAB_00d2ddd2:
        if (iVar5 < 0) goto LAB_00d2de18;
LAB_00d2ddd6:
        pCVar4 = *(CQuestManager **)(pCVar7 + 0x10);
        pCVar9 = pCVar7;
      }
      pCVar7 = pCVar4;
    } while (pCVar7 != (CQuestManager *)0x0);
  }
  if (pCVar1 != pCVar9) {
    uVar2 = *(ulong *)(*(wchar_t **)(pCVar9 + 0x20) + -6);
    uVar3 = *(ulong *)(*(wchar_t **)param_1 + -6);
    uVar6 = uVar3;
    if (uVar2 <= uVar3) {
      uVar6 = uVar2;
    }
    iVar5 = wmemcmp(*(wchar_t **)param_1,*(wchar_t **)(pCVar9 + 0x20),uVar6);
    if (iVar5 == 0) {
      lVar8 = uVar3 - uVar2;
      if (0x7fffffff < lVar8) goto LAB_00d2de86;
      if (lVar8 < -0x80000000) {
        return 0;
      }
      iVar5 = (int)lVar8;
    }
    if (-1 < iVar5) {
LAB_00d2de86:
      return *(undefined8 *)(pCVar9 + 0x28);
    }
  }
  return 0;
}

/* address=00d2e700
   symbol=CQuestManager::getQuestNames */

/* WARNING: Removing unreachable block (ram,0x00d2e8dd) */
/* WARNING: Removing unreachable block (ram,0x00d2e924) */
/* CQuestManager::getQuestNames(TArrayList<std::wstring >&) */

void __thiscall CQuestManager::getQuestNames(CQuestManager *this,TArrayList *param_1)

{
  int *piVar1;
  int iVar2;
  ulong *puVar3;
  long *plVar4;
  CQuestManager *pCVar5;
  uint uVar6;
  ulong uVar7;
  long lVar8;
  long *plVar9;
  allocator *paVar10;
  ulong *puVar11;
  uint uVar12;
  long local_48 [3];

  pCVar5 = *(CQuestManager **)(this + 0x58);
  if (pCVar5 != this + 0x48) {
    do {
      std::wstring::wstring((wstring_conflict *)local_48,(wstring_conflict *)(pCVar5 + 0x20));
      uVar6 = *(uint *)(param_1 + 8);
      if (uVar6 < *(uint *)(param_1 + 0xc)) {
        puVar11 = *(ulong **)param_1;
      }
      else if (*(long *)param_1 == 0) {
        uVar7 = (ulong)*(uint *)(param_1 + 0x10);
        *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0x10);
                    /* try { // try from 00d2e874 to 00d2e878 has its CatchHandler @ 00d2e911 */
        puVar3 = operator_new__(uVar7 * 8 + 8);
        *puVar3 = uVar7;
        puVar11 = puVar3 + 1;
        if (uVar7 != 0) {
          lVar8 = uVar7 - 2;
          do {
            lVar8 = lVar8 + -1;
            puVar3[1] = (ulong)&DAT_01424558;
            puVar3 = puVar3 + 1;
          } while (lVar8 != -2);
        }
        *(ulong **)param_1 = puVar11;
        uVar6 = *(uint *)(param_1 + 8);
      }
      else {
        uVar12 = *(uint *)(param_1 + 0xc) + *(int *)(param_1 + 0x10);
        uVar7 = (ulong)uVar12;
                    /* try { // try from 00d2e766 to 00d2e816 has its CatchHandler @ 00d2e911 */
        puVar3 = operator_new__(uVar7 * 8 + 8);
        *puVar3 = uVar7;
        puVar11 = puVar3 + 1;
        if (uVar7 != 0) {
          lVar8 = uVar7 - 2;
          do {
            lVar8 = lVar8 + -1;
            puVar3[1] = (ulong)&DAT_01424558;
            puVar3 = puVar3 + 1;
          } while (lVar8 != -2);
        }
        if (*(int *)(param_1 + 0xc) != 0) {
          uVar6 = 0;
          do {
            std::wstring::assign((wstring_conflict *)(puVar11 + uVar6));
            uVar6 = uVar6 + 1;
          } while (uVar6 < *(uint *)(param_1 + 0xc));
        }
        plVar4 = *(long **)param_1;
        if (plVar4 != (long *)0x0) {
          plVar9 = plVar4 + plVar4[-1];
          while (plVar9 != plVar4) {
            plVar9 = plVar9 + -1;
            paVar10 = (allocator *)(*plVar9 + -0x18);
            if (paVar10 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar1 = (int *)(*plVar9 + -8);
              iVar2 = *piVar1;
              *piVar1 = *piVar1 + -1;
              UNLOCK();
              if (iVar2 < 1) {
                std::wstring::_Rep::_M_destroy(paVar10);
              }
              plVar4 = *(long **)param_1;
            }
          }
          operator_delete__(plVar9 + -1);
        }
        uVar6 = *(uint *)(param_1 + 8);
        *(ulong **)param_1 = puVar11;
        *(uint *)(param_1 + 0xc) = uVar12;
      }
      std::wstring::assign((wstring_conflict *)(puVar11 + uVar6));
      *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 1;
      if ((allocator *)(local_48[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_48[0] + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
        }
      }
      pCVar5 = (CQuestManager *)std::_Rb_tree_increment((_Rb_tree_node_base *)pCVar5);
    } while (pCVar5 != this + 0x48);
  }
  return;
}

/* address=00d2e930
   symbol=CQuestManager::~CQuestManager */

/* CQuestManager::~CQuestManager() */

void __thiscall CQuestManager::~CQuestManager(CQuestManager *this)

{
  _Rb_tree_node_base *p_Var1;

  *(undefined ***)this = &PTR__CQuestManager_00ff7790;
  *(undefined4 *)(this + 0x20) = 0;
  *(undefined4 *)(this + 0x24) = 0;
  if (*(void **)(this + 0x18) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x18));
  }
  *(undefined8 *)(this + 0x18) = 0;
  for (p_Var1 = *(_Rb_tree_node_base **)(this + 0x58); p_Var1 != (_Rb_tree_node_base *)(this + 0x48)
      ; p_Var1 = (_Rb_tree_node_base *)std::_Rb_tree_increment(p_Var1)) {
    if (*(long **)(p_Var1 + 0x28) != (long *)0x0) {
                    /* try { // try from 00d2e9bf to 00d2ead0 has its CatchHandler @ 00d2eb5a */
      (**(code **)(**(long **)(p_Var1 + 0x28) + 8))();
      *(undefined8 *)(p_Var1 + 0x28) = 0;
    }
  }
  std::
  _Rb_tree<std::wstring,std::pair<std::wstring_const,CQuest*>,std::_Select1st<std::pair<std::wstring_const,CQuest*>>,std::less<std::wstring>,std::allocator<std::pair<std::wstring_const,CQuest*>>>
  ::_M_erase((_Rb_tree<std::wstring,std::pair<std::wstring_const,CQuest*>,std::_Select1st<std::pair<std::wstring_const,CQuest*>>,std::less<std::wstring>,std::allocator<std::pair<std::wstring_const,CQuest*>>>
              *)(this + 0x40),*(_Rb_tree_node **)(this + 0x50));
  *(_Rb_tree_node_base **)(this + 0x58) = p_Var1;
  *(undefined8 *)(this + 0x50) = 0;
  *(_Rb_tree_node_base **)(this + 0x60) = p_Var1;
  *(undefined8 *)(this + 0x68) = 0;
  std::
  _Rb_tree<CDataGroup*,std::pair<CDataGroup*const,TArrayList<CQuest*>*>,std::_Select1st<std::pair<CDataGroup*const,TArrayList<CQuest*>*>>,std::less<CDataGroup*>,std::allocator<std::pair<CDataGroup*const,TArrayList<CQuest*>*>>>
  ::_M_erase((_Rb_tree<CDataGroup*,std::pair<CDataGroup*const,TArrayList<CQuest*>*>,std::_Select1st<std::pair<CDataGroup*const,TArrayList<CQuest*>*>>,std::less<CDataGroup*>,std::allocator<std::pair<CDataGroup*const,TArrayList<CQuest*>*>>>
              *)(this + 0xa0),*(_Rb_tree_node **)(this + 0xb0));
  *(CQuestManager **)(this + 0xb8) = this + 0xa8;
  *(undefined8 *)(this + 0xb0) = 0;
  *(CQuestManager **)(this + 0xc0) = this + 0xa8;
  *(undefined8 *)(this + 200) = 0;
  std::
  _Rb_tree<std::wstring,std::pair<std::wstring_const,bool>,std::_Select1st<std::pair<std::wstring_const,bool>>,std::less<std::wstring>,std::allocator<std::pair<std::wstring_const,bool>>>
  ::_M_erase((_Rb_tree<std::wstring,std::pair<std::wstring_const,bool>,std::_Select1st<std::pair<std::wstring_const,bool>>,std::less<std::wstring>,std::allocator<std::pair<std::wstring_const,bool>>>
              *)(this + 0x70),*(_Rb_tree_node **)(this + 0x80));
  *(undefined8 *)(this + 0x80) = 0;
  *(CQuestManager **)(this + 0x88) = this + 0x78;
  *(CQuestManager **)(this + 0x90) = this + 0x78;
  *(undefined8 *)(this + 0x98) = 0;
  if (*(long **)(this + 0x30) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x30) + 8))();
    *(undefined8 *)(this + 0x30) = 0;
  }
  g_pQuestManager = 0;
                    /* try { // try from 00d2eaf8 to 00d2eafc has its CatchHandler @ 00d2ebe2 */
  std::
  _Rb_tree<CDataGroup*,std::pair<CDataGroup*const,TArrayList<CQuest*>*>,std::_Select1st<std::pair<CDataGroup*const,TArrayList<CQuest*>*>>,std::less<CDataGroup*>,std::allocator<std::pair<CDataGroup*const,TArrayList<CQuest*>*>>>
  ::_M_erase((_Rb_tree<CDataGroup*,std::pair<CDataGroup*const,TArrayList<CQuest*>*>,std::_Select1st<std::pair<CDataGroup*const,TArrayList<CQuest*>*>>,std::less<CDataGroup*>,std::allocator<std::pair<CDataGroup*const,TArrayList<CQuest*>*>>>
              *)(this + 0xa0),*(_Rb_tree_node **)(this + 0xb0));
                    /* try { // try from 00d2eb0c to 00d2eb10 has its CatchHandler @ 00d2ebd9 */
  std::
  _Rb_tree<std::wstring,std::pair<std::wstring_const,bool>,std::_Select1st<std::pair<std::wstring_const,bool>>,std::less<std::wstring>,std::allocator<std::pair<std::wstring_const,bool>>>
  ::_M_erase((_Rb_tree<std::wstring,std::pair<std::wstring_const,bool>,std::_Select1st<std::pair<std::wstring_const,bool>>,std::less<std::wstring>,std::allocator<std::pair<std::wstring_const,bool>>>
              *)(this + 0x70),*(_Rb_tree_node **)(this + 0x80));
                    /* try { // try from 00d2eb1d to 00d2eb21 has its CatchHandler @ 00d2ebd7 */
  std::
  _Rb_tree<std::wstring,std::pair<std::wstring_const,CQuest*>,std::_Select1st<std::pair<std::wstring_const,CQuest*>>,std::less<std::wstring>,std::allocator<std::pair<std::wstring_const,CQuest*>>>
  ::_M_erase((_Rb_tree<std::wstring,std::pair<std::wstring_const,CQuest*>,std::_Select1st<std::pair<std::wstring_const,CQuest*>>,std::less<std::wstring>,std::allocator<std::pair<std::wstring_const,CQuest*>>>
              *)(this + 0x40),*(_Rb_tree_node **)(this + 0x50));
  if (*(void **)(this + 0x18) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x18));
    *(undefined8 *)(this + 0x18) = 0;
  }
  CRunicCore::~CRunicCore((CRunicCore *)this);
  return;
}

/* address=00d2ebf0
   symbol=CQuestManager::~CQuestManager */

/* CQuestManager::~CQuestManager() */

void __thiscall CQuestManager::~CQuestManager(CQuestManager *this)

{
  ~CQuestManager(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}

/* address=00d2ec10
   symbol=CQuestManager::save */

/* WARNING: Removing unreachable block (ram,0x00d2f002) */
/* WARNING: Removing unreachable block (ram,0x00d2efd4) */
/* CQuestManager::save(_IO_FILE*) */

void __thiscall CQuestManager::save(CQuestManager *this,_IO_FILE *param_1)

{
  int *piVar1;
  wchar_t *pwVar2;
  ulong uVar3;
  ulong uVar4;
  CQuest *this_00;
  _Rb_tree_node_base *p_Var5;
  int iVar6;
  _Rb_tree_node_base *p_Var7;
  _Rb_tree_node_base *p_Var8;
  undefined8 *puVar9;
  ulong uVar10;
  uint uVar11;
  _Rb_tree_node_base *p_Var12;
  _Rb_tree_node_base *p_Var13;
  long lVar14;
  long lVar15;
  _Rb_tree_node_base *local_90;
  void *local_68 [2];
  long local_58;
  undefined4 local_4c;
  uint local_48;
  undefined4 local_44;
  int local_40;
  ushort local_3c [6];

  local_40 = 0;
  for (p_Var7 = *(_Rb_tree_node_base **)(this + 0x88); p_Var7 != (_Rb_tree_node_base *)(this + 0x78)
      ; p_Var7 = (_Rb_tree_node_base *)std::_Rb_tree_increment(p_Var7)) {
    if (p_Var7[0x28] != (_Rb_tree_node_base)0x0) {
      local_40 = local_40 + 1;
    }
  }
  fwrite(&local_40,4,1,param_1);
  p_Var8 = *(_Rb_tree_node_base **)(this + 0x58);
  do {
    if (p_Var8 == (_Rb_tree_node_base *)(this + 0x48)) {
      local_44 = *(undefined4 *)(this + 0x20);
      fwrite(&local_44,4,1,param_1);
      if (0 < *(int *)(this + 0x20)) {
        lVar15 = 0;
        uVar11 = 0;
        do {
          lVar14 = ftell(param_1);
          local_48 = (uint)lVar14;
          fwrite(&local_48,4,1,param_1);
          if (uVar11 < *(uint *)(this + 0x24)) {
            puVar9 = (undefined8 *)(lVar15 + *(long *)(this + 0x18));
          }
          else {
            puVar9 = *(undefined8 **)(this + 0x18);
          }
          this_00 = (CQuest *)*puVar9;
          std::wstring::wstring((wstring_conflict *)&local_58,(wstring_conflict *)(this_00 + 0x50));
          local_3c[0] = (ushort)*(undefined8 *)(local_58 + -0x18);
                    /* try { // try from 00d2ee5c to 00d2ee6d has its CatchHandler @ 00d2effc */
          fwrite(local_3c,2,1,param_1);
          UTF32ToUTF16((wstring_conflict *)local_68);
                    /* try { // try from 00d2ee85 to 00d2eec5 has its CatchHandler @ 00d2efaf */
          fwrite(local_68[0],(long)(int)((uint)local_3c[0] * 2),1,param_1);
          CQuest::save(this_00,param_1);
          lVar14 = ftell(param_1);
          local_4c = (undefined4)lVar14;
          fseek(param_1,(ulong)local_48,0);
          fwrite(&local_4c,4,1,param_1);
          fseek(param_1,0,2);
          if ((undefined8 *)((long)local_68[0] + -0x18) !=
              &std::
               basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
               ::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)((long)local_68[0] + -8);
            iVar6 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar6 < 1) {
              operator_delete((undefined8 *)((long)local_68[0] + -0x18));
            }
          }
          if ((allocator *)(local_58 + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_58 + -8);
            iVar6 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar6 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_58 + -0x18));
            }
          }
          uVar11 = uVar11 + 1;
          lVar15 = lVar15 + 8;
        } while ((int)uVar11 < *(int *)(this + 0x20));
      }
      return;
    }
    local_3c[0] = (ushort)*(undefined8 *)(*(long *)(p_Var8 + 0x20) + -0x18);
    lVar15 = *(long *)(p_Var8 + 0x28);
    p_Var12 = *(_Rb_tree_node_base **)(this + 0x80);
    p_Var13 = p_Var7;
    if (p_Var12 != (_Rb_tree_node_base *)0x0) {
      pwVar2 = *(wchar_t **)(lVar15 + 0x50);
      uVar3 = *(ulong *)(pwVar2 + -6);
      do {
        uVar4 = *(ulong *)(*(wchar_t **)(p_Var12 + 0x20) + -6);
        uVar10 = uVar4;
        if (uVar3 <= uVar4) {
          uVar10 = uVar3;
        }
        iVar6 = wmemcmp(*(wchar_t **)(p_Var12 + 0x20),pwVar2,uVar10);
        if (iVar6 == 0) {
          lVar14 = uVar4 - uVar3;
          if (0x7fffffff < lVar14) goto LAB_00d2ecef;
          if (-0x80000001 < lVar14) {
            iVar6 = (int)lVar14;
            goto LAB_00d2eceb;
          }
LAB_00d2ed31:
          p_Var5 = *(_Rb_tree_node_base **)(p_Var12 + 0x18);
        }
        else {
LAB_00d2eceb:
          if (iVar6 < 0) goto LAB_00d2ed31;
LAB_00d2ecef:
          p_Var5 = *(_Rb_tree_node_base **)(p_Var12 + 0x10);
          p_Var13 = p_Var12;
        }
        p_Var12 = p_Var5;
      } while (p_Var12 != (_Rb_tree_node_base *)0x0);
    }
    local_90 = p_Var7;
    if (p_Var7 != p_Var13) {
      pwVar2 = *(wchar_t **)(lVar15 + 0x50);
      uVar3 = *(ulong *)(*(wchar_t **)(p_Var13 + 0x20) + -6);
      uVar4 = *(ulong *)(pwVar2 + -6);
      uVar10 = uVar4;
      if (uVar3 <= uVar4) {
        uVar10 = uVar3;
      }
      iVar6 = wmemcmp(pwVar2,*(wchar_t **)(p_Var13 + 0x20),uVar10);
      if (iVar6 == 0) {
        lVar15 = uVar4 - uVar3;
        local_90 = p_Var13;
        if ((0x7fffffff < lVar15) || (local_90 = p_Var7, lVar15 < -0x80000000)) goto LAB_00d2ed97;
        iVar6 = (int)lVar15;
      }
      local_90 = p_Var13;
      if (iVar6 < 0) {
        local_90 = p_Var7;
      }
    }
LAB_00d2ed97:
    if (local_90[0x28] != (_Rb_tree_node_base)0x0) {
      fwrite(local_3c,2,1,param_1);
      WriteUTF32ToUTF16(param_1,(wstring_conflict *)(p_Var8 + 0x20),(ulong)local_3c[0]);
    }
    p_Var8 = (_Rb_tree_node_base *)std::_Rb_tree_increment(p_Var8);
  } while( true );
}

/* address=00d2f020
   symbol=CQuestManager::removeQuest */

/* WARNING: Removing unreachable block (ram,0x00d2f2ae) */
/* CQuestManager::removeQuest(CQuest*, bool) */

undefined8 __thiscall CQuestManager::removeQuest(CQuestManager *this,CQuest *param_1,bool param_2)

{
  long *plVar1;
  wchar_t *pwVar2;
  allocator *paVar3;
  wchar_t wVar4;
  long *plVar5;
  int iVar6;
  uint uVar7;
  undefined8 *puVar8;
  long *plVar9;
  uint uVar10;
  bool bVar11;
  wchar_t *local_48 [3];

  if (param_1 == (CQuest *)0x0) {
    return 0;
  }
  uVar10 = *(uint *)(this + 0x20);
  if (uVar10 != 0) {
    plVar5 = *(long **)(this + 0x18);
    uVar7 = 0;
    plVar9 = plVar5;
    if (param_1 == (CQuest *)*plVar5) {
      uVar7 = 0;
    }
    else {
      do {
        uVar7 = uVar7 + 1;
        if (uVar10 <= uVar7) goto LAB_00d2f078;
        plVar1 = plVar9 + 1;
        plVar9 = plVar9 + 1;
      } while (param_1 != (CQuest *)*plVar1);
      if (uVar7 == 0xffffffff) goto LAB_00d2f078;
    }
    *(uint *)(this + 0x20) = uVar10 - 1;
    plVar5[uVar7] = plVar5[uVar10 - 1];
  }
LAB_00d2f078:
  CQuest::initializeQuestWithNPC(param_1,(CBaseUnit *)0x0);
  CQuest::setQuestAccepted(param_1,false);
  if (param_2) {
    CQuest::cleanUp(param_1,false);
    CQuest::reinitializeQuest(param_1,true,false);
  }
  if (*(int *)(param_1 + 0x1b8) != 0) {
    uVar10 = 0;
    do {
      if (uVar10 < *(uint *)(param_1 + 0x1bc)) {
        puVar8 = (undefined8 *)((ulong)uVar10 * 8 + *(long *)(param_1 + 0x1b0));
      }
      else {
        puVar8 = *(undefined8 **)(param_1 + 0x1b0);
      }
      if (*(long *)*puVar8 != 0) {
        if (uVar10 < *(uint *)(param_1 + 0x1bc)) {
          puVar8 = (undefined8 *)((ulong)uVar10 * 8 + *(long *)(param_1 + 0x1b0));
        }
        else {
          puVar8 = *(undefined8 **)(param_1 + 0x1b0);
        }
        std::wstring::wstring
                  ((wstring_conflict *)local_48,(wstring_conflict *)(*(long *)*puVar8 + 0xa8));
        pwVar2 = local_48[0];
        bVar11 = false;
        paVar3 = (allocator *)(local_48[0] + -6);
        if (*(size_t *)(local_48[0] + -6) == *(size_t *)(*(wchar_t **)(param_1 + 0x50) + -6)) {
          iVar6 = wmemcmp(local_48[0],*(wchar_t **)(param_1 + 0x50),*(size_t *)(local_48[0] + -6));
          bVar11 = iVar6 == 0;
        }
        if (paVar3 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          pwVar2 = pwVar2 + -2;
          wVar4 = *pwVar2;
          *pwVar2 = *pwVar2 + L'\xffffffff';
          UNLOCK();
          if (wVar4 < L'\x01') {
            std::wstring::_Rep::_M_destroy(paVar3);
          }
        }
        if (bVar11) {
          if (uVar10 < *(uint *)(param_1 + 0x1bc)) {
            puVar8 = (undefined8 *)((ulong)uVar10 * 8 + *(long *)(param_1 + 0x1b0));
          }
          else {
            puVar8 = *(undefined8 **)(param_1 + 0x1b0);
          }
          CQuestController::questHasBeenAccepted(*(CQuestController **)*puVar8,false);
          if (param_2) {
            if (uVar10 < *(uint *)(param_1 + 0x1bc)) {
              puVar8 = (undefined8 *)((ulong)uVar10 * 8 + *(long *)(param_1 + 0x1b0));
            }
            else {
              puVar8 = *(undefined8 **)(param_1 + 0x1b0);
            }
            CQuestController::questHasBeenAbandoned(*(CQuestController **)*puVar8);
          }
        }
      }
      uVar10 = uVar10 + 1;
    } while (uVar10 < *(uint *)(param_1 + 0x1b8));
  }
  CLevel::updateNPCIcons(*(CLevel **)(*(long *)(this + 0x38) + 0x18));
  CLevel::updateAutomapIcons();
  return 1;
}

/* address=00d2f470
   symbol=CQuestManager::questEventUpdate */
/* DECOMPILATION FAILED:
Low-level Error: Overriding symbol with different type size */

/* address=00d2f8a0
   symbol=CQuestManager::load */

/* WARNING: Removing unreachable block (ram,0x00d30034) */
/* WARNING: Removing unreachable block (ram,0x00d30042) */
/* WARNING: Removing unreachable block (ram,0x00d300bd) */
/* WARNING: Removing unreachable block (ram,0x00d2ffe8) */
/* WARNING: Removing unreachable block (ram,0x00d2fff3) */
/* WARNING: Removing unreachable block (ram,0x00d300c8) */
/* CQuestManager::load(_IO_FILE*, unsigned int, CResourceManager*) */

void __thiscall
CQuestManager::load(CQuestManager *this,_IO_FILE *param_1,uint param_2,CResourceManager *param_3)

{
  CQuestManager *pCVar1;
  wchar_t *pwVar2;
  int *piVar3;
  allocator *paVar4;
  wchar_t wVar5;
  ulong uVar6;
  CQuestManager *pCVar7;
  char cVar8;
  int iVar9;
  int iVar10;
  void *pvVar11;
  CQuest *pCVar12;
  ulong uVar13;
  CQuestManager *pCVar14;
  ulong uVar15;
  uint uVar16;
  CQuestManager *pCVar17;
  long lVar18;
  uint uVar19;
  allocator *local_c0;
  long local_88;
  undefined1 local_80;
  wchar_t *local_78 [2];
  long local_68 [2];
  wchar_t *local_58;
  uint local_50;
  int local_4c;
  uint local_48;
  ushort local_42 [4];
  allocator local_3a;
  allocator local_39 [9];

  resetQuestManager(this,false);
  local_48 = 0;
  fread(&local_48,4,1,param_1);
  if (local_48 != 0) {
    pCVar1 = this + 0x78;
    uVar16 = 0;
    do {
      local_42[0] = 0;
      fread(local_42,2,1,param_1);
      FILESYSTEM::ReadWString((FILESYSTEM *)&local_58,param_1,(uint)local_42[0]);
      pwVar2 = local_58;
      pCVar17 = *(CQuestManager **)(this + 0x80);
      pCVar14 = pCVar1;
      if (pCVar17 != (CQuestManager *)0x0) {
        uVar15 = *(ulong *)(local_58 + -6);
        do {
          uVar6 = *(ulong *)(*(wchar_t **)(pCVar17 + 0x20) + -6);
          uVar13 = uVar6;
          if (uVar15 <= uVar6) {
            uVar13 = uVar15;
          }
          iVar9 = wmemcmp(*(wchar_t **)(pCVar17 + 0x20),pwVar2,uVar13);
          if (iVar9 == 0) {
            lVar18 = uVar6 - uVar15;
            if (0x7fffffff < lVar18) goto LAB_00d2f9a7;
            if (-0x80000001 < lVar18) {
              iVar9 = (int)lVar18;
              goto LAB_00d2f9a3;
            }
LAB_00d2f9e9:
            pCVar7 = *(CQuestManager **)(pCVar17 + 0x18);
          }
          else {
LAB_00d2f9a3:
            if (iVar9 < 0) goto LAB_00d2f9e9;
LAB_00d2f9a7:
            pCVar7 = *(CQuestManager **)(pCVar17 + 0x10);
            pCVar14 = pCVar17;
          }
          pCVar17 = pCVar7;
        } while (pCVar17 != (CQuestManager *)0x0);
      }
      local_c0 = (allocator *)(pwVar2 + -6);
      if (pCVar1 == pCVar14) {
        local_c0 = (allocator *)(pwVar2 + -6);
      }
      else {
        uVar15 = *(ulong *)local_c0;
        uVar6 = *(ulong *)(*(wchar_t **)(pCVar14 + 0x20) + -6);
        uVar13 = uVar15;
        if (uVar6 <= uVar15) {
          uVar13 = uVar6;
        }
        iVar9 = wmemcmp(pwVar2,*(wchar_t **)(pCVar14 + 0x20),uVar13);
        if (iVar9 == 0) {
          lVar18 = uVar15 - uVar6;
          if (lVar18 < 0x80000000) {
            if (lVar18 < -0x80000000) goto LAB_00d2fa54;
            iVar9 = (int)lVar18;
            goto LAB_00d2fa3e;
          }
        }
        else {
LAB_00d2fa3e:
          if (iVar9 < 0) goto LAB_00d2fa54;
        }
        pCVar14[0x28] = (CQuestManager)0x1;
        local_c0 = (allocator *)(local_58 + -6);
      }
LAB_00d2fa54:
      if (local_c0 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        paVar4 = local_c0 + 0x10;
        iVar9 = *(int *)paVar4;
        *(int *)paVar4 = *(int *)paVar4 + -1;
        UNLOCK();
        if (iVar9 < 1) {
          std::wstring::_Rep::_M_destroy(local_c0);
        }
      }
      uVar16 = uVar16 + 1;
    } while (uVar16 < local_48);
  }
  fread(&local_4c,4,1,param_1);
  if (0 < local_4c) {
    pCVar1 = this + 0x48;
    iVar9 = 0;
    do {
      local_50 = 0;
      fread(&local_50,4,1,param_1);
      local_42[0] = 0;
      fread(local_42,2,1,param_1);
      FILESYSTEM::ReadWString((FILESYSTEM *)&local_58,param_1,(uint)local_42[0]);
      pwVar2 = local_58;
      pCVar17 = *(CQuestManager **)(this + 0x50);
      pCVar14 = pCVar1;
      if (pCVar17 != (CQuestManager *)0x0) {
        uVar15 = *(ulong *)(local_58 + -6);
        do {
          uVar6 = *(ulong *)(*(wchar_t **)(pCVar17 + 0x20) + -6);
          uVar13 = uVar6;
          if (uVar15 <= uVar6) {
            uVar13 = uVar15;
          }
          iVar10 = wmemcmp(*(wchar_t **)(pCVar17 + 0x20),pwVar2,uVar13);
          if (iVar10 == 0) {
            lVar18 = uVar6 - uVar15;
            if (0x7fffffff < lVar18) goto LAB_00d2fb57;
            if (-0x80000001 < lVar18) {
              iVar10 = (int)lVar18;
              goto LAB_00d2fb53;
            }
LAB_00d2fb9b:
            pCVar7 = *(CQuestManager **)(pCVar17 + 0x18);
          }
          else {
LAB_00d2fb53:
            if (iVar10 < 0) goto LAB_00d2fb9b;
LAB_00d2fb57:
            pCVar7 = *(CQuestManager **)(pCVar17 + 0x10);
            pCVar14 = pCVar17;
          }
          pCVar17 = pCVar7;
        } while (pCVar17 != (CQuestManager *)0x0);
      }
      if (pCVar1 == pCVar14) {
LAB_00d2fcf0:
        fseek(param_1,(ulong)local_50,0);
        if ((allocator *)(local_58 + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
        {
          LOCK();
          pwVar2 = local_58 + -2;
          wVar5 = *pwVar2;
          *pwVar2 = *pwVar2 + L'\xffffffff';
          UNLOCK();
          if (wVar5 < L'\x01') {
            std::wstring::_Rep::_M_destroy((allocator *)(local_58 + -6));
          }
        }
      }
      else {
        uVar15 = *(ulong *)(local_58 + -6);
        uVar6 = *(ulong *)(*(wchar_t **)(pCVar14 + 0x20) + -6);
        uVar13 = uVar15;
        if (uVar6 <= uVar15) {
          uVar13 = uVar6;
        }
        iVar10 = wmemcmp(local_58,*(wchar_t **)(pCVar14 + 0x20),uVar13);
        if (iVar10 == 0) {
          lVar18 = uVar15 - uVar6;
          if (lVar18 < 0x80000000) {
            if (lVar18 < -0x80000000) goto LAB_00d2fcf0;
            iVar10 = (int)lVar18;
            goto LAB_00d2fbfc;
          }
        }
        else {
LAB_00d2fbfc:
          if (iVar10 < 0) goto LAB_00d2fcf0;
        }
        pCVar12 = *(CQuest **)(pCVar14 + 0x28);
        if (pCVar12 == (CQuest *)0x0) goto LAB_00d2fcf0;
                    /* try { // try from 00d2fc22 to 00d2fda0 has its CatchHandler @ 00d30057 */
        CQuest::load(pCVar12,param_1,param_3,param_2);
        uVar16 = *(uint *)(this + 0x20);
        if (uVar16 < *(uint *)(this + 0x24)) {
          pvVar11 = *(void **)(this + 0x18);
        }
        else if (*(long *)(this + 0x18) == 0) {
          *(uint *)(this + 0x24) = *(uint *)(this + 0x28);
          pvVar11 = operator_new__((ulong)*(uint *)(this + 0x28) << 3);
          *(void **)(this + 0x18) = pvVar11;
          uVar16 = *(uint *)(this + 0x20);
        }
        else {
          uVar19 = *(uint *)(this + 0x24) + *(int *)(this + 0x28);
          pvVar11 = operator_new__((ulong)uVar19 << 3);
          if (*(int *)(this + 0x24) != 0) {
            uVar16 = 0;
            do {
              uVar15 = (ulong)uVar16;
              uVar16 = uVar16 + 1;
              *(undefined8 *)((long)pvVar11 + uVar15 * 8) =
                   *(undefined8 *)(*(long *)(this + 0x18) + uVar15 * 8);
            } while (uVar16 < *(uint *)(this + 0x24));
          }
          if (*(void **)(this + 0x18) != (void *)0x0) {
            operator_delete__(*(void **)(this + 0x18));
          }
          uVar16 = *(uint *)(this + 0x20);
          *(void **)(this + 0x18) = pvVar11;
          *(uint *)(this + 0x24) = uVar19;
        }
        *(CQuest **)((long)pvVar11 + (ulong)uVar16 * 8) = pCVar12;
        *(int *)(this + 0x20) = *(int *)(this + 0x20) + 1;
        if ((pCVar12[0x26] == (CQuest)0x0) &&
           (cVar8 = CQuest::getQuestHasRandomPieces(pCVar12), cVar8 != '\0')) {
          CQuest::reinitializeQuest(pCVar12,true,false);
        }
        if ((allocator *)(local_58 + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
        {
          LOCK();
          pwVar2 = local_58 + -2;
          wVar5 = *pwVar2;
          *pwVar2 = *pwVar2 + L'\xffffffff';
          UNLOCK();
          if (wVar5 < L'\x01') {
            std::wstring::_Rep::_M_destroy((allocator *)(local_58 + -6));
          }
        }
      }
      iVar9 = iVar9 + 1;
    } while (iVar9 < local_4c);
  }
  if (0x14 < param_2) {
    return;
  }
                    /* try { // try from 00d2fddd to 00d2fde1 has its CatchHandler @ 00d2ffe0 */
  std::wstring::wstring((wstring_conflict *)local_68,L"COMPLETEGAME",local_39);
  pCVar12 = (CQuest *)getQuestByName(this,(wstring_conflict *)local_68);
  if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar3 = (int *)(local_68[0] + -8);
    iVar9 = *piVar3;
    *piVar3 = *piVar3 + -1;
    UNLOCK();
    if (iVar9 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
    }
  }
  if (pCVar12 == (CQuest *)0x0) {
    return;
  }
  CQuest::reinitializeQuest(pCVar12,true,false);
                    /* try { // try from 00d2fe33 to 00d2fe37 has its CatchHandler @ 00d30098 */
  std::wstring::wstring((wstring_conflict *)local_78,L"COMPLETEGAME",&local_3a);
  pwVar2 = local_78[0];
  pCVar1 = this + 0x78;
  pCVar17 = *(CQuestManager **)(this + 0x80);
  pCVar14 = pCVar1;
  if (pCVar17 != (CQuestManager *)0x0) {
    uVar15 = *(ulong *)(local_78[0] + -6);
    do {
      uVar6 = *(ulong *)(*(wchar_t **)(pCVar17 + 0x20) + -6);
      uVar13 = uVar6;
      if (uVar15 <= uVar6) {
        uVar13 = uVar15;
      }
      iVar9 = wmemcmp(*(wchar_t **)(pCVar17 + 0x20),pwVar2,uVar13);
      if (iVar9 == 0) {
        lVar18 = uVar6 - uVar15;
        if (0x7fffffff < lVar18) goto LAB_00d2fe6c;
        if (-0x80000001 < lVar18) {
          iVar9 = (int)lVar18;
          goto LAB_00d2fe68;
        }
LAB_00d2feb0:
        pCVar7 = *(CQuestManager **)(pCVar17 + 0x18);
      }
      else {
LAB_00d2fe68:
        if (iVar9 < 0) goto LAB_00d2feb0;
LAB_00d2fe6c:
        pCVar7 = *(CQuestManager **)(pCVar17 + 0x10);
        pCVar14 = pCVar17;
      }
      pCVar17 = pCVar7;
    } while (pCVar17 != (CQuestManager *)0x0);
  }
  if (pCVar1 != pCVar14) {
    uVar15 = *(ulong *)(local_78[0] + -6);
    uVar6 = *(ulong *)(*(wchar_t **)(pCVar14 + 0x20) + -6);
    uVar13 = uVar15;
    if (uVar6 <= uVar15) {
      uVar13 = uVar6;
    }
    uVar16 = wmemcmp(local_78[0],*(wchar_t **)(pCVar14 + 0x20),uVar13);
    uVar13 = (ulong)uVar16;
    if (uVar16 == 0) {
      uVar13 = uVar15 - uVar6;
      if (0x7fffffff < (long)uVar13) goto LAB_00d2ff6c;
      if ((long)uVar13 < -0x80000000) goto LAB_00d2ff05;
    }
    if (-1 < (int)uVar13) goto LAB_00d2ff6c;
  }
LAB_00d2ff05:
                    /* try { // try from 00d2ff10 to 00d2ff14 has its CatchHandler @ 00d300b8 */
  std::wstring::wstring((wstring_conflict *)&local_88,(wstring_conflict *)local_78);
  local_80 = 0;
                    /* try { // try from 00d2ff24 to 00d2ff28 has its CatchHandler @ 00d300a3 */
  pCVar14 = (CQuestManager *)
            std::
            _Rb_tree<std::wstring,std::pair<std::wstring_const,bool>,std::_Select1st<std::pair<std::wstring_const,bool>>,std::less<std::wstring>,std::allocator<std::pair<std::wstring_const,bool>>>
            ::_M_insert_unique_((_Rb_tree<std::wstring,std::pair<std::wstring_const,bool>,std::_Select1st<std::pair<std::wstring_const,bool>>,std::less<std::wstring>,std::allocator<std::pair<std::wstring_const,bool>>>
                                 *)(this + 0x70),pCVar14,(wstring_conflict *)&local_88);
  if ((allocator *)(local_88 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar3 = (int *)(local_88 + -8);
    iVar9 = *piVar3;
    *piVar3 = *piVar3 + -1;
    UNLOCK();
    if (iVar9 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_88 + -0x18));
    }
  }
LAB_00d2ff6c:
  pCVar14[0x28] = (CQuestManager)0x0;
  if ((allocator *)(local_78[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    pwVar2 = local_78[0] + -2;
    wVar5 = *pwVar2;
    *pwVar2 = *pwVar2 + L'\xffffffff';
    UNLOCK();
    if (wVar5 < L'\x01') {
      std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -6));
    }
  }
  return;
}

/* address=00d300e0
   symbol=CQuestManager::getQuestForNPC */

/* WARNING: Removing unreachable block (ram,0x00d307cb) */
/* WARNING: Removing unreachable block (ram,0x00d30820) */
/* CQuestManager::getQuestForNPC(CBaseUnit*) */

CQuest * __thiscall CQuestManager::getQuestForNPC(CQuestManager *this,CBaseUnit *param_1)

{
  int *piVar1;
  allocator *paVar2;
  int iVar3;
  CDataGroup *this_00;
  undefined8 uVar4;
  ulong uVar5;
  wchar_t *__s2;
  CQuestManager *pCVar6;
  char cVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  undefined8 *puVar11;
  ulong uVar12;
  CQuestManager *pCVar13;
  wstring_conflict *pwVar14;
  long *plVar15;
  long lVar16;
  ulong uVar17;
  long lVar18;
  CQuestManager *pCVar19;
  CQuestManager *pCVar20;
  CQuest *this_01;
  uint uVar21;
  long lVar22;
  ulong uVar23;
  uint uVar24;
  undefined8 *local_a8;
  allocator *local_80;
  long local_68 [2];
  wchar_t *local_58 [2];
  wstring_conflict local_48 [15];
  allocator local_39 [9];

  if ((param_1 == (CBaseUnit *)0x0) ||
     (this_00 = *(CDataGroup **)(param_1 + 0x1b0), this_00 == (CDataGroup *)0x0)) {
    return (CQuest *)0x0;
  }
  pCVar19 = *(CQuestManager **)(this + 0xb0);
  pCVar13 = this + 0xa8;
  while (pCVar20 = pCVar19, pCVar20 != (CQuestManager *)0x0) {
    if (*(CDataGroup **)(pCVar20 + 0x20) < this_00) {
      pCVar19 = *(CQuestManager **)(pCVar20 + 0x18);
    }
    else {
      pCVar19 = *(CQuestManager **)(pCVar20 + 0x10);
      pCVar13 = pCVar20;
    }
  }
  if (((this + 0xa8 != pCVar13) && (*(CDataGroup **)(pCVar13 + 0x20) <= this_00)) &&
     (plVar15 = *(long **)(pCVar13 + 0x28), (int)plVar15[1] != 0)) {
    local_a8 = (undefined8 *)0x0;
    uVar24 = 0;
    uVar8 = 0;
    uVar21 = 0;
    if (*(int *)((long)plVar15 + 0xc) != 0) goto LAB_00d3027e;
    do {
      puVar11 = (undefined8 *)*plVar15;
      while( true ) {
                    /* try { // try from 00d301cb to 00d3039e has its CatchHandler @ 00d307db */
        cVar7 = CQuest::getQuestIsValidForNPC((CQuest *)*puVar11,param_1);
        uVar23 = (ulong)uVar8;
        if (cVar7 != '\0') {
          plVar15 = *(long **)(pCVar13 + 0x28);
          if (uVar21 < *(uint *)((long)plVar15 + 0xc)) {
            puVar11 = (undefined8 *)((ulong)uVar21 * 8 + *plVar15);
          }
          else {
            puVar11 = (undefined8 *)*plVar15;
          }
          uVar4 = *puVar11;
          uVar23 = (ulong)uVar8;
          if (uVar8 <= uVar24) {
            if (local_a8 == (undefined8 *)0x0) {
              local_a8 = operator_new__(0x50);
              uVar23 = 10;
            }
            else {
              uVar23 = (ulong)(uVar8 + 10);
              puVar11 = operator_new__(uVar23 << 3);
              if (uVar8 != 0) {
                lVar16 = 0;
                do {
                  *(undefined8 *)((long)puVar11 + lVar16) = *(undefined8 *)((long)local_a8 + lVar16)
                  ;
                  lVar16 = lVar16 + 8;
                } while (lVar16 != (ulong)(uVar8 - 1) * 8 + 8);
              }
              operator_delete__(local_a8);
              local_a8 = puVar11;
            }
          }
          uVar12 = (ulong)uVar24;
          uVar24 = uVar24 + 1;
          local_a8[uVar12] = uVar4;
        }
        plVar15 = *(long **)(pCVar13 + 0x28);
        uVar21 = uVar21 + 1;
        if (*(uint *)(plVar15 + 1) <= uVar21) goto LAB_00d302a0;
        uVar8 = (uint)uVar23;
        if (*(uint *)((long)plVar15 + 0xc) <= uVar21) break;
LAB_00d3027e:
        puVar11 = (undefined8 *)((ulong)uVar21 * 8 + *plVar15);
      }
    } while( true );
  }
  local_a8 = (undefined8 *)0x0;
  uVar24 = 0;
  uVar23 = 0;
LAB_00d302a0:
  uVar21 = (uint)uVar23;
  if (*(uint *)(this + 0x20) != 0) {
    uVar8 = 0;
    lVar16 = 0;
    do {
      if (uVar8 < *(uint *)(this + 0x24)) {
        lVar22 = *(long *)(*(long *)(lVar16 + *(long *)(this + 0x18)) + 0x1e8);
      }
      else {
        lVar22 = *(long *)(**(long **)(this + 0x18) + 0x1e8);
      }
      if (lVar22 == *(long *)(param_1 + 0x1b0)) {
        if (uVar8 < *(uint *)(this + 0x24)) {
          puVar11 = (undefined8 *)((ulong)uVar8 * 8 + *(long *)(this + 0x18));
        }
        else {
          puVar11 = *(undefined8 **)(this + 0x18);
        }
        this_01 = (CQuest *)*puVar11;
        goto LAB_00d30316;
      }
      uVar8 = uVar8 + 1;
      lVar16 = lVar16 + 8;
    } while (uVar8 < *(uint *)(this + 0x20));
  }
  if (uVar24 == 0) {
                    /* try { // try from 00d303ca to 00d303ce has its CatchHandler @ 00d307d6 */
    std::wstring::wstring(local_48,L"QUESTS",local_39);
                    /* try { // try from 00d303d9 to 00d303dd has its CatchHandler @ 00d307dd */
    lVar16 = CDataGroup::GetDataGroupByName(this_00,local_48,false);
                    /* try { // try from 00d303e6 to 00d303ea has its CatchHandler @ 00d307d6 */
    std::wstring::~wstring(local_48);
    if ((lVar16 != 0) && (*(int *)(lVar16 + 0x28) != 0)) {
      uVar8 = 0;
      pCVar13 = this + 0x48;
      do {
        if (uVar8 < *(uint *)(lVar16 + 0x2c)) {
          plVar15 = (long *)((ulong)uVar8 * 8 + *(long *)(lVar16 + 0x20));
        }
        else {
          plVar15 = *(long **)(lVar16 + 0x20);
        }
        if ((*(int *)(*plVar15 + 0x30) == 8) || (*(int *)(*plVar15 + 0x30) == 5)) {
          if (uVar8 < *(uint *)(lVar16 + 0x2c)) {
            puVar11 = (undefined8 *)((ulong)uVar8 * 8 + *(long *)(lVar16 + 0x20));
          }
          else {
            puVar11 = *(undefined8 **)(lVar16 + 0x20);
          }
                    /* try { // try from 00d30465 to 00d30476 has its CatchHandler @ 00d307db */
          pwVar14 = (wstring_conflict *)CDataValue::GetValueString((CDataValue *)*puVar11,true);
          STRINGS::StringUpper((STRINGS *)local_58,pwVar14);
          __s2 = local_58[0];
          pCVar19 = *(CQuestManager **)(this + 0x50);
          uVar21 = (uint)uVar23;
          pCVar20 = pCVar13;
          if (pCVar19 != (CQuestManager *)0x0) {
            uVar12 = *(ulong *)(local_58[0] + -6);
            do {
              uVar5 = *(ulong *)(*(wchar_t **)(pCVar19 + 0x20) + -6);
              uVar17 = uVar12;
              if (uVar5 <= uVar12) {
                uVar17 = uVar5;
              }
              iVar9 = wmemcmp(*(wchar_t **)(pCVar19 + 0x20),__s2,uVar17);
              if (iVar9 == 0) {
                lVar22 = uVar5 - uVar12;
                if (0x7fffffff < lVar22) goto LAB_00d304be;
                if (-0x80000001 < lVar22) {
                  iVar9 = (int)lVar22;
                  goto LAB_00d304ba;
                }
LAB_00d30500:
                pCVar6 = *(CQuestManager **)(pCVar19 + 0x18);
              }
              else {
LAB_00d304ba:
                if (iVar9 < 0) goto LAB_00d30500;
LAB_00d304be:
                pCVar6 = *(CQuestManager **)(pCVar19 + 0x10);
                pCVar20 = pCVar19;
              }
              pCVar19 = pCVar6;
            } while (pCVar19 != (CQuestManager *)0x0);
          }
          local_80 = (allocator *)(__s2 + -6);
          if (pCVar13 == pCVar20) {
            local_80 = (allocator *)(__s2 + -6);
          }
          else {
            uVar12 = *(ulong *)local_80;
            uVar5 = *(ulong *)(*(wchar_t **)(pCVar20 + 0x20) + -6);
            uVar17 = uVar12;
            if (uVar5 <= uVar12) {
              uVar17 = uVar5;
            }
            iVar9 = wmemcmp(__s2,*(wchar_t **)(pCVar20 + 0x20),uVar17);
            if (iVar9 == 0) {
              lVar22 = uVar12 - uVar5;
              if (lVar22 < 0x80000000) {
                if (lVar22 < -0x80000000) goto LAB_00d30583;
                iVar9 = (int)lVar22;
                goto LAB_00d3055b;
              }
            }
            else {
LAB_00d3055b:
              if (iVar9 < 0) goto LAB_00d30583;
            }
            if ((*(CQuest **)(pCVar20 + 0x28))[0x26] == (CQuest)0x0) {
                    /* try { // try from 00d3060e to 00d3066e has its CatchHandler @ 00d30768 */
              cVar7 = CQuest::getQuestIsValidForNPC(*(CQuest **)(pCVar20 + 0x28),param_1);
              if (cVar7 == '\0') {
                local_80 = (allocator *)(local_58[0] + -6);
              }
              else {
                lVar22 = *(long *)(pCVar20 + 0x28);
                if (*(long *)(lVar22 + 0x1e8) == *(long *)(param_1 + 0x1b0)) {
                  iVar9 = *(int *)(lVar22 + 0x20);
                    /* try { // try from 00d306f8 to 00d30714 has its CatchHandler @ 00d307b4 */
                  std::wstring::wstring
                            ((wstring_conflict *)local_68,(wstring_conflict *)(lVar22 + 0x30));
                  iVar10 = CPlayer::getMaxDepth(*(CPlayer **)(this + 0x10),local_68);
                  if ((allocator *)(local_68[0] + -0x18) !=
                      (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                    LOCK();
                    piVar1 = (int *)(local_68[0] + -8);
                    iVar3 = *piVar1;
                    *piVar1 = *piVar1 + -1;
                    UNLOCK();
                    if (iVar3 < 1) {
                      std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
                    }
                  }
                  if (iVar10 < iVar9) {
                    this_01 = *(CQuest **)(pCVar20 + 0x28);
                    /* try { // try from 00d3075e to 00d30762 has its CatchHandler @ 00d307db */
                    std::wstring::~wstring((wstring_conflict *)local_58);
                    goto LAB_00d30316;
                  }
                  lVar22 = *(long *)(pCVar20 + 0x28);
                }
                if (uVar21 <= uVar24) {
                  if (local_a8 == (undefined8 *)0x0) {
                    /* try { // try from 00d30741 to 00d30745 has its CatchHandler @ 00d30768 */
                    local_a8 = operator_new__(0x50);
                    uVar23 = 10;
                  }
                  else {
                    uVar23 = (ulong)(uVar21 + 10);
                    puVar11 = operator_new__((ulong)(uVar21 + 10) << 3);
                    if (uVar21 != 0) {
                      lVar18 = 0;
                      do {
                        *(undefined8 *)((long)puVar11 + lVar18) =
                             *(undefined8 *)((long)local_a8 + lVar18);
                        lVar18 = lVar18 + 8;
                      } while (lVar18 != (ulong)(uVar21 - 1) * 8 + 8);
                    }
                    operator_delete__(local_a8);
                    local_a8 = puVar11;
                  }
                }
                uVar12 = (ulong)uVar24;
                uVar24 = uVar24 + 1;
                local_a8[uVar12] = lVar22;
                local_80 = (allocator *)(local_58[0] + -6);
              }
            }
            else {
              local_80 = (allocator *)(__s2 + -6);
            }
          }
LAB_00d30583:
          if (local_80 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            paVar2 = local_80 + 0x10;
            iVar9 = *(int *)paVar2;
            *(int *)paVar2 = *(int *)paVar2 + -1;
            UNLOCK();
            if (iVar9 < 1) {
              std::wstring::_Rep::_M_destroy(local_80);
            }
          }
        }
        uVar21 = (uint)uVar23;
        uVar8 = uVar8 + 1;
      } while (uVar8 < *(uint *)(lVar16 + 0x28));
      if (uVar24 != 0) goto LAB_00d3036f;
    }
    this_01 = (CQuest *)0x0;
  }
  else {
LAB_00d3036f:
    uVar8 = UTILITIES::randomIntegerBetweenVolatile(0,uVar24 - 1);
    puVar11 = local_a8;
    if (uVar8 < uVar21) {
      puVar11 = local_a8 + uVar8;
    }
    this_01 = (CQuest *)*puVar11;
    if (this_01 != (CQuest *)0x0) {
      CQuest::initializeQuestWithNPC(this_01,param_1);
    }
  }
LAB_00d30316:
  if (local_a8 != (undefined8 *)0x0) {
    operator_delete__(local_a8);
  }
  return this_01;
}

/* address=00d30830
   symbol=CQuestManager::getNPCIcon */

/* CQuestManager::getNPCIcon(CCharacter*) */

undefined4 __thiscall CQuestManager::getNPCIcon(CQuestManager *this,CCharacter *param_1)

{
  char cVar1;
  uint uVar2;
  CQuest *this_00;
  long *plVar3;
  long lVar4;

  if (((param_1 == (CCharacter *)0x0) ||
      (cVar1 = CBaseUnit::ISA((CBaseUnit *)param_1,0x68), cVar1 == '\0')) ||
     (*(long *)(this + 0x10) == 0)) {
    return 0xffffffff;
  }
  this_00 = (CQuest *)getQuestForNPC(this,(CBaseUnit *)param_1);
  if (this_00 == (CQuest *)0x0) {
    return 0xffffffff;
  }
  if (*(uint *)(this + 0x20) != 0) {
    lVar4 = 0;
    uVar2 = 0;
    do {
      if (uVar2 < *(uint *)(this + 0x24)) {
        plVar3 = (long *)(lVar4 + *(long *)(this + 0x18));
      }
      else {
        plVar3 = *(long **)(this + 0x18);
      }
      if (this_00 == (CQuest *)*plVar3) break;
      uVar2 = uVar2 + 1;
      lVar4 = lVar4 + 8;
    } while (uVar2 < *(uint *)(this + 0x20));
  }
  lVar4 = CQuest::getQuestDialog(this_00,(CBaseUnit *)param_1);
  if (lVar4 == 0) {
    return 0xffffffff;
  }
  if (*(char *)(lVar4 + 0x75) == '\0') {
    return 0xffffffff;
  }
  uVar2 = *(int *)(lVar4 + 0x70) - 1;
  if (3 < uVar2) {
    return 0xffffffff;
  }
  return *(undefined4 *)(CSWTCH_4688 + (ulong)uVar2 * 4);
}

/* address=00d30900
   symbol=CQuestManager::calculateNPCIcon */

/* WARNING: Removing unreachable block (ram,0x00d30f53) */
/* WARNING: Removing unreachable block (ram,0x00d31125) */
/* WARNING: Removing unreachable block (ram,0x00d30f45) */
/* WARNING: Removing unreachable block (ram,0x00d31115) */
/* CQuestManager::calculateNPCIcon(CCharacter*) */

undefined8 __thiscall CQuestManager::calculateNPCIcon(CQuestManager *this,CCharacter *param_1)

{
  int *piVar1;
  int iVar2;
  CQuest *pCVar3;
  bool bVar4;
  char cVar5;
  uint uVar6;
  CQuest *this_00;
  long lVar7;
  CGameUI *this_01;
  wstring_conflict awStack_198 [16];
  wstring_conflict local_188 [16];
  wstring_conflict local_178 [16];
  wstring_conflict local_168 [16];
  wstring_conflict local_158 [16];
  wstring_conflict local_148 [16];
  wstring_conflict local_138 [16];
  wstring_conflict local_128 [16];
  wstring_conflict local_118 [16];
  wstring_conflict local_108 [16];
  wstring_conflict local_f8 [16];
  wstring_conflict local_e8 [16];
  wstring_conflict local_d8 [16];
  wstring_conflict local_c8 [16];
  wstring_conflict local_b8 [16];
  wstring_conflict local_a8 [16];
  wstring_conflict local_98 [16];
  long local_88 [2];
  long local_78 [2];
  long local_68 [2];
  long local_58 [3];
  allocator local_3d;
  allocator local_3c;
  allocator local_3b;
  allocator local_3a;
  allocator local_39;
  allocator local_38;
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

  if ((param_1 != (CCharacter *)0x0) && (*(long *)(this + 0x10) != 0)) {
    this_00 = (CQuest *)getQuestForNPC(this,(CBaseUnit *)param_1);
                    /* try { // try from 00d30949 to 00d3094d has its CatchHandler @ 00d310fa */
    std::wstring::wstring((wstring_conflict *)local_58,L"QUEST COMPLETE",&local_29);
                    /* try { // try from 00d30954 to 00d30958 has its CatchHandler @ 00d310e5 */
    CBaseUnit::removeUnitTheme((CBaseUnit *)param_1,(wstring_conflict *)local_58);
    if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_58[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
      }
    }
                    /* try { // try from 00d3098c to 00d30990 has its CatchHandler @ 00d30fc2 */
    std::wstring::wstring((wstring_conflict *)local_68,L"QUEST INCOMPLETE",&local_2a);
                    /* try { // try from 00d30997 to 00d3099b has its CatchHandler @ 00d310d5 */
    CBaseUnit::removeUnitTheme((CBaseUnit *)param_1,(wstring_conflict *)local_68);
    if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_68[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
      }
    }
                    /* try { // try from 00d309c9 to 00d309cd has its CatchHandler @ 00d310c5 */
    std::wstring::wstring((wstring_conflict *)local_78,L"QUEST GIVING",&local_2b);
                    /* try { // try from 00d309d4 to 00d309d8 has its CatchHandler @ 00d30fd4 */
    CBaseUnit::removeUnitTheme((CBaseUnit *)param_1,(wstring_conflict *)local_78);
    if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_78[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
      }
    }
                    /* try { // try from 00d30a06 to 00d30a0a has its CatchHandler @ 00d30fd2 */
    std::wstring::wstring((wstring_conflict *)local_88,L"QUEST PASSIVE",&local_2c);
                    /* try { // try from 00d30a11 to 00d30a15 has its CatchHandler @ 00d30fc4 */
    CBaseUnit::removeUnitTheme((CBaseUnit *)param_1,(wstring_conflict *)local_88);
    if ((allocator *)(local_88[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_88[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
      }
    }
    lVar7 = CGameUI::getSingleton();
    if (lVar7 != 0) {
      this_01 = (CGameUI *)CGameUI::getSingleton();
      cVar5 = CGameUI::getUIIsInCinematic(this_01);
      if (cVar5 != '\0') {
        return 1;
      }
    }
    if ((this_00 != (CQuest *)0x0) &&
       ((cVar5 = (**(code **)(*(long *)param_1 + 0x48))(param_1), cVar5 != '\0' ||
        (param_1[0x70d] == (CCharacter)0x0)))) {
      if (*(uint *)(this + 0x20) != 0) {
        lVar7 = 0;
        uVar6 = 0;
        do {
          if (uVar6 < *(uint *)(this + 0x24)) {
            pCVar3 = *(CQuest **)(lVar7 + *(long *)(this + 0x18));
          }
          else {
            pCVar3 = (CQuest *)**(long **)(this + 0x18);
          }
          if (this_00 == pCVar3) {
            bVar4 = true;
            goto LAB_00d30ae2;
          }
          uVar6 = uVar6 + 1;
          lVar7 = lVar7 + 8;
        } while (uVar6 < *(uint *)(this + 0x20));
      }
      bVar4 = false;
LAB_00d30ae2:
      lVar7 = CQuest::getQuestDialog(this_00,(CBaseUnit *)param_1);
      if (lVar7 != 0) {
        if (*(char *)(lVar7 + 0x75) == '\0') {
          return 1;
        }
        if (*(long *)(*(long *)(lVar7 + 0x98) + -0x18) != 0) {
          CBaseUnit::addUnitTheme((CBaseUnit *)param_1,(wstring_conflict *)(lVar7 + 0x98));
          return 1;
        }
        if (*(int *)(lVar7 + 0x70) == 4) {
          if (*(char *)(lVar7 + 0x76) == '\0') {
                    /* try { // try from 00d30cda to 00d30cde has its CatchHandler @ 00d30f84 */
            std::wstring::wstring(local_98,L"QUEST PASSIVE",&local_2d);
                    /* try { // try from 00d30ce5 to 00d30ce9 has its CatchHandler @ 00d30f92 */
            CBaseUnit::addUnitTheme((CBaseUnit *)param_1,local_98);
                    /* try { // try from 00d30ced to 00d30cf1 has its CatchHandler @ 00d30f84 */
            std::wstring::~wstring(local_98);
          }
          else {
                    /* try { // try from 00d30e6c to 00d30e70 has its CatchHandler @ 00d31105 */
            std::wstring::wstring(local_a8,L"QUEST PASSIVE",&local_2e);
                    /* try { // try from 00d30e77 to 00d30e7b has its CatchHandler @ 00d310ff */
            CBaseUnit::removeUnitTheme((CBaseUnit *)param_1,local_a8);
                    /* try { // try from 00d30e7f to 00d30e83 has its CatchHandler @ 00d31105 */
            std::wstring::~wstring(local_a8);
          }
                    /* try { // try from 00d30d0a to 00d30d0e has its CatchHandler @ 00d30f86 */
          std::wstring::wstring(local_b8,L"QUEST COMPLETE",&local_2f);
                    /* try { // try from 00d30d15 to 00d30d19 has its CatchHandler @ 00d30fa4 */
          CBaseUnit::removeUnitTheme((CBaseUnit *)param_1,local_b8);
                    /* try { // try from 00d30d1d to 00d30d21 has its CatchHandler @ 00d30f86 */
          std::wstring::~wstring(local_b8);
                    /* try { // try from 00d30d3a to 00d30d3e has its CatchHandler @ 00d30fa2 */
          std::wstring::wstring(local_c8,L"QUEST INCOMPLETE",&local_30);
                    /* try { // try from 00d30d45 to 00d30d49 has its CatchHandler @ 00d30f96 */
          CBaseUnit::removeUnitTheme((CBaseUnit *)param_1,local_c8);
                    /* try { // try from 00d30d4d to 00d30d51 has its CatchHandler @ 00d30fa2 */
          std::wstring::~wstring(local_c8);
                    /* try { // try from 00d30d6a to 00d30d6e has its CatchHandler @ 00d30f94 */
          std::wstring::wstring(local_d8,L"QUEST GIVING",&local_31);
                    /* try { // try from 00d30d75 to 00d30d79 has its CatchHandler @ 00d30fb6 */
          CBaseUnit::removeUnitTheme((CBaseUnit *)param_1,local_d8);
                    /* try { // try from 00d30d7d to 00d30d81 has its CatchHandler @ 00d30f94 */
          std::wstring::~wstring(local_d8);
          return 1;
        }
        if (bVar4) {
          cVar5 = CQuest::isComplete(this_00,false);
          if (cVar5 != '\0') {
                    /* try { // try from 00d30b48 to 00d30b4c has its CatchHandler @ 00d30f82 */
            std::wstring::wstring(local_128,L"QUEST COMPLETE",&local_36);
                    /* try { // try from 00d30b53 to 00d30b57 has its CatchHandler @ 00d30f78 */
            CBaseUnit::addUnitTheme((CBaseUnit *)param_1,local_128);
                    /* try { // try from 00d30b5b to 00d30b5f has its CatchHandler @ 00d30f82 */
            std::wstring::~wstring(local_128);
                    /* try { // try from 00d30b75 to 00d30b79 has its CatchHandler @ 00d30f76 */
            std::wstring::wstring(local_138,L"QUEST INCOMPLETE",&local_37);
                    /* try { // try from 00d30b80 to 00d30b84 has its CatchHandler @ 00d30f69 */
            CBaseUnit::removeUnitTheme((CBaseUnit *)param_1,local_138);
                    /* try { // try from 00d30b88 to 00d30b8c has its CatchHandler @ 00d30f76 */
            std::wstring::~wstring(local_138);
                    /* try { // try from 00d30ba2 to 00d30ba6 has its CatchHandler @ 00d30f5e */
            std::wstring::wstring(local_148,L"QUEST GIVING",&local_38);
                    /* try { // try from 00d30bad to 00d30bb1 has its CatchHandler @ 00d30fb2 */
            CBaseUnit::removeUnitTheme((CBaseUnit *)param_1,local_148);
                    /* try { // try from 00d30bb5 to 00d30bb9 has its CatchHandler @ 00d30f5e */
            std::wstring::~wstring(local_148);
                    /* try { // try from 00d30bcf to 00d30bd3 has its CatchHandler @ 00d30fa6 */
            std::wstring::wstring(local_158,L"QUEST PASSIVE",&local_39);
                    /* try { // try from 00d30bda to 00d30bde has its CatchHandler @ 00d30fb4 */
            CBaseUnit::removeUnitTheme((CBaseUnit *)param_1,local_158);
                    /* try { // try from 00d30be2 to 00d30be6 has its CatchHandler @ 00d30fa6 */
            std::wstring::~wstring(local_158);
            return 1;
          }
                    /* try { // try from 00d30db5 to 00d30db9 has its CatchHandler @ 00d31035 */
          std::wstring::wstring(local_168,L"QUEST COMPLETE",&local_3a);
                    /* try { // try from 00d30dc0 to 00d30dc4 has its CatchHandler @ 00d31025 */
          CBaseUnit::removeUnitTheme((CBaseUnit *)param_1,local_168);
                    /* try { // try from 00d30dc8 to 00d30dcc has its CatchHandler @ 00d31035 */
          std::wstring::~wstring(local_168);
                    /* try { // try from 00d30de2 to 00d30de6 has its CatchHandler @ 00d31015 */
          std::wstring::wstring(local_178,L"QUEST GIVING",&local_3b);
                    /* try { // try from 00d30ded to 00d30df1 has its CatchHandler @ 00d31005 */
          CBaseUnit::removeUnitTheme((CBaseUnit *)param_1,local_178);
                    /* try { // try from 00d30df5 to 00d30df9 has its CatchHandler @ 00d31015 */
          std::wstring::~wstring(local_178);
                    /* try { // try from 00d30e0f to 00d30e13 has its CatchHandler @ 00d30ff5 */
          std::wstring::wstring(local_188,L"QUEST PASSIVE",&local_3c);
                    /* try { // try from 00d30e1a to 00d30e1e has its CatchHandler @ 00d30fef */
          CBaseUnit::removeUnitTheme((CBaseUnit *)param_1,local_188);
                    /* try { // try from 00d30e22 to 00d30e26 has its CatchHandler @ 00d30ff5 */
          std::wstring::~wstring(local_188);
                    /* try { // try from 00d30e37 to 00d30e3b has its CatchHandler @ 00d30fea */
          std::wstring::wstring(awStack_198,L"QUEST INCOMPLETE",&local_3d);
                    /* try { // try from 00d30e42 to 00d30e46 has its CatchHandler @ 00d30fd6 */
          CBaseUnit::addUnitTheme((CBaseUnit *)param_1,awStack_198);
                    /* try { // try from 00d30e4a to 00d30e4e has its CatchHandler @ 00d30fea */
          std::wstring::~wstring(awStack_198);
          return 1;
        }
                    /* try { // try from 00d30c08 to 00d30c0c has its CatchHandler @ 00d310b5 */
        std::wstring::wstring(local_e8,L"QUEST GIVING",&local_32);
                    /* try { // try from 00d30c13 to 00d30c17 has its CatchHandler @ 00d310a5 */
        CBaseUnit::addUnitTheme((CBaseUnit *)param_1,local_e8);
                    /* try { // try from 00d30c1b to 00d30c1f has its CatchHandler @ 00d310b5 */
        std::wstring::~wstring(local_e8);
                    /* try { // try from 00d30c38 to 00d30c3c has its CatchHandler @ 00d31095 */
        std::wstring::wstring(local_f8,L"QUEST COMPLETE",&local_33);
                    /* try { // try from 00d30c43 to 00d30c47 has its CatchHandler @ 00d31085 */
        CBaseUnit::removeUnitTheme((CBaseUnit *)param_1,local_f8);
                    /* try { // try from 00d30c4b to 00d30c4f has its CatchHandler @ 00d31095 */
        std::wstring::~wstring(local_f8);
                    /* try { // try from 00d30c68 to 00d30c6c has its CatchHandler @ 00d31075 */
        std::wstring::wstring(local_108,L"QUEST INCOMPLETE",&local_34);
                    /* try { // try from 00d30c73 to 00d30c77 has its CatchHandler @ 00d31065 */
        CBaseUnit::removeUnitTheme((CBaseUnit *)param_1,local_108);
                    /* try { // try from 00d30c7b to 00d30c7f has its CatchHandler @ 00d31075 */
        std::wstring::~wstring(local_108);
                    /* try { // try from 00d30c98 to 00d30c9c has its CatchHandler @ 00d31055 */
        std::wstring::wstring(local_118,L"QUEST PASSIVE",&local_35);
                    /* try { // try from 00d30ca3 to 00d30ca7 has its CatchHandler @ 00d31045 */
        CBaseUnit::removeUnitTheme((CBaseUnit *)param_1,local_118);
                    /* try { // try from 00d30cab to 00d30caf has its CatchHandler @ 00d31055 */
        std::wstring::~wstring(local_118);
        return 1;
      }
    }
  }
  return 0;
}

/* address=00d31140
   symbol=CQuestManager::getDialogsForNPC */

/* CQuestManager::getDialogsForNPC(TArrayList<CQuestDialog*>&, CBaseUnit*, bool) */

void __thiscall
CQuestManager::getDialogsForNPC
          (CQuestManager *this,TArrayList *param_1,CBaseUnit *param_2,bool param_3)

{
  uint uVar1;
  long lVar2;
  void *pvVar3;
  CQuest *pCVar4;
  undefined8 *puVar5;
  ulong uVar6;
  uint uVar7;
  uint uVar8;

  if (param_2 != (CBaseUnit *)0x0) {
    if (*(int *)(this + 0x20) != 0) {
      uVar8 = 0;
      do {
        if (uVar8 < *(uint *)(this + 0x24)) {
          puVar5 = (undefined8 *)((ulong)uVar8 * 8 + *(long *)(this + 0x18));
        }
        else {
          puVar5 = *(undefined8 **)(this + 0x18);
        }
        lVar2 = CQuest::getQuestDialog((CQuest *)*puVar5,param_2);
        if (lVar2 != 0) {
          uVar1 = *(uint *)(param_1 + 8);
          if (uVar1 < *(uint *)(param_1 + 0xc)) {
            pvVar3 = *(void **)param_1;
          }
          else if (*(long *)param_1 == 0) {
            *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0x10);
            pvVar3 = operator_new__((ulong)*(uint *)(param_1 + 0x10) << 3);
            uVar1 = *(uint *)(param_1 + 8);
            *(void **)param_1 = pvVar3;
          }
          else {
            uVar1 = *(uint *)(param_1 + 0xc) + *(int *)(param_1 + 0x10);
            pvVar3 = operator_new__((ulong)uVar1 << 3);
            if (*(int *)(param_1 + 0xc) != 0) {
              uVar6 = 0;
              do {
                uVar7 = (int)uVar6 + 1;
                *(undefined8 *)((long)pvVar3 + uVar6 * 8) =
                     *(undefined8 *)(*(long *)param_1 + uVar6 * 8);
                uVar6 = (ulong)uVar7;
              } while (uVar7 < *(uint *)(param_1 + 0xc));
            }
            if (*(void **)param_1 != (void *)0x0) {
              operator_delete__(*(void **)param_1);
            }
            *(void **)param_1 = pvVar3;
            *(uint *)(param_1 + 0xc) = uVar1;
            uVar1 = *(uint *)(param_1 + 8);
          }
          *(long *)((long)pvVar3 + (ulong)uVar1 * 8) = lVar2;
          *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 1;
        }
        uVar8 = uVar8 + 1;
      } while (uVar8 < *(uint *)(this + 0x20));
    }
    pCVar4 = (CQuest *)getQuestForNPC(this,param_2);
    if (pCVar4 != (CQuest *)0x0) {
      lVar2 = CQuest::getQuestDialog(pCVar4,param_2);
      if (lVar2 != 0) {
        uVar8 = *(uint *)(param_1 + 8);
        if (uVar8 < *(uint *)(param_1 + 0xc)) {
          pvVar3 = *(void **)param_1;
        }
        else if (*(long *)param_1 == 0) {
          *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0x10);
          pvVar3 = operator_new__((ulong)*(uint *)(param_1 + 0x10) << 3);
          uVar8 = *(uint *)(param_1 + 8);
          *(void **)param_1 = pvVar3;
        }
        else {
          uVar1 = *(uint *)(param_1 + 0xc) + *(int *)(param_1 + 0x10);
          pvVar3 = operator_new__((ulong)uVar1 << 3);
          if (*(int *)(param_1 + 0xc) != 0) {
            uVar8 = 0;
            do {
              uVar6 = (ulong)uVar8;
              uVar8 = uVar8 + 1;
              *(undefined8 *)((long)pvVar3 + uVar6 * 8) =
                   *(undefined8 *)(*(long *)param_1 + uVar6 * 8);
            } while (uVar8 < *(uint *)(param_1 + 0xc));
          }
          if (*(void **)param_1 != (void *)0x0) {
            operator_delete__(*(void **)param_1);
          }
          uVar8 = *(uint *)(param_1 + 8);
          *(void **)param_1 = pvVar3;
          *(uint *)(param_1 + 0xc) = uVar1;
        }
        *(long *)((long)pvVar3 + (ulong)uVar8 * 8) = lVar2;
        *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 1;
      }
      if ((param_3) && (*(int *)(param_1 + 8) == 0)) {
        pCVar4 = (CQuest *)getQuestForNPC(this,param_2);
        if (pCVar4 != (CQuest *)0x0) {
          lVar2 = CQuest::getQuestDialog(pCVar4,param_2);
          if (lVar2 != 0) {
            uVar8 = *(uint *)(param_1 + 8);
            if (uVar8 < *(uint *)(param_1 + 0xc)) {
              pvVar3 = *(void **)param_1;
            }
            else if (*(long *)param_1 == 0) {
              *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0x10);
              pvVar3 = operator_new__((ulong)*(uint *)(param_1 + 0x10) << 3);
              uVar8 = *(uint *)(param_1 + 8);
              *(void **)param_1 = pvVar3;
            }
            else {
              uVar1 = *(uint *)(param_1 + 0xc) + *(int *)(param_1 + 0x10);
              pvVar3 = operator_new__((ulong)uVar1 << 3);
              if (*(int *)(param_1 + 0xc) != 0) {
                uVar6 = 0;
                do {
                  uVar8 = (int)uVar6 + 1;
                  *(undefined8 *)((long)pvVar3 + uVar6 * 8) =
                       *(undefined8 *)(*(long *)param_1 + uVar6 * 8);
                  uVar6 = (ulong)uVar8;
                } while (uVar8 < *(uint *)(param_1 + 0xc));
              }
              if (*(void **)param_1 != (void *)0x0) {
                operator_delete__(*(void **)param_1);
              }
              uVar8 = *(uint *)(param_1 + 8);
              *(void **)param_1 = pvVar3;
              *(uint *)(param_1 + 0xc) = uVar1;
            }
            *(long *)((long)pvVar3 + (ulong)uVar8 * 8) = lVar2;
            *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 1;
          }
        }
      }
    }
  }
  return;
}

/* address=00d31410
   symbol=CQuestManager::loadQuests */

/* WARNING: Removing unreachable block (ram,0x00d32103) */
/* WARNING: Removing unreachable block (ram,0x00d32172) */
/* WARNING: Removing unreachable block (ram,0x00d31f32) */
/* WARNING: Removing unreachable block (ram,0x00d31f27) */
/* WARNING: Removing unreachable block (ram,0x00d320c5) */
/* WARNING: Removing unreachable block (ram,0x00d31fd6) */
/* WARNING: Removing unreachable block (ram,0x00d321d9) */
/* WARNING: Removing unreachable block (ram,0x00d32123) */
/* WARNING: Removing unreachable block (ram,0x00d3205b) */
/* WARNING: Removing unreachable block (ram,0x00d32066) */
/* WARNING: Removing unreachable block (ram,0x00d321ce) */
/* CQuestManager::loadQuests() */

void __thiscall CQuestManager::loadQuests(CQuestManager *this)

{
  CQuestManager *pCVar1;
  CQuestManager *pCVar2;
  int *piVar3;
  CQuestManager *pCVar4;
  wchar_t *pwVar5;
  CQuestManager *pCVar6;
  char cVar7;
  int iVar8;
  uint uVar9;
  CFileSystem *pCVar10;
  undefined8 uVar11;
  CQuest *this_00;
  ulong uVar12;
  CQuestManager *pCVar13;
  CQuestManager *pCVar14;
  void *pvVar15;
  long *plVar16;
  wstring_conflict *pwVar17;
  ulong uVar18;
  uint uVar19;
  wstring_conflict *pwVar20;
  long lVar21;
  ulong uVar22;
  ulong *puVar23;
  allocator *paVar24;
  uint local_16c;
  ulong *local_128;
  uint local_120;
  uint local_11c;
  undefined4 local_118;
  wstring_conflict *local_108;
  uint local_100;
  uint local_fc;
  undefined4 local_f8;
  long local_e8;
  undefined1 local_e0;
  ulong local_d8 [2];
  long local_c8 [2];
  long local_b8 [2];
  long local_a8 [2];
  char *local_98 [2];
  long local_88 [2];
  long local_78 [2];
  long local_68 [2];
  long local_58 [3];
  allocator local_3c;
  allocator local_3b;
  allocator local_3a;
  allocator local_39 [9];

  local_108 = (wstring_conflict *)0x0;
  local_100 = 0;
  local_fc = 0;
  local_f8 = 10;
                    /* try { // try from 00d31469 to 00d3146d has its CatchHandler @ 00d31e52 */
  std::wstring::wstring((wstring_conflict *)local_68,L"*.dat",&local_3a);
                    /* try { // try from 00d31486 to 00d3148a has its CatchHandler @ 00d31ec2 */
  std::wstring::wstring((wstring_conflict *)local_58,L"media/quests/",local_39);
                    /* try { // try from 00d3148b to 00d314c0 has its CatchHandler @ 00d31fa7 */
  pCVar10 = (CFileSystem *)CFileSystem::getSingleton();
  CFileSystem::getFileList
            (pCVar10,(wstring_conflict *)local_58,&local_108,(wstring_conflict *)local_68,1,1,0,0);
  if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar3 = (int *)(local_58[0] + -8);
    iVar8 = *piVar3;
    *piVar3 = *piVar3 + -1;
    UNLOCK();
    if (iVar8 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
    }
  }
  if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar3 = (int *)(local_68[0] + -8);
    iVar8 = *piVar3;
    *piVar3 = *piVar3 + -1;
    UNLOCK();
    if (iVar8 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
    }
  }
  local_128 = (ulong *)0x0;
  local_120 = 0;
  local_11c = 0;
  local_118 = 100;
  if (local_100 != 0) {
    pCVar1 = this + 0x78;
    pCVar2 = this + 0x48;
    pCVar4 = this + 0xa8;
    local_16c = 0;
    do {
                    /* try { // try from 00d31674 to 00d31678 has its CatchHandler @ 00d31f3d */
      this_00 = (CQuest *)Ogre::NedAllocImpl::allocBytes(0x218,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00d31686 to 00d3168a has its CatchHandler @ 00d31f61 */
      CQuest::CQuest(this_00,*(CResourceManager **)(this + 0x38),this);
      pwVar20 = local_108;
      if (local_16c < local_fc) {
        pwVar20 = local_108 + (ulong)local_16c * 8;
      }
                    /* try { // try from 00d3157b to 00d315c2 has its CatchHandler @ 00d31f3d */
      cVar7 = CQuest::loadQuestData(this_00,pwVar20);
      if (cVar7 == '\0') {
        if (this_00 != (CQuest *)0x0) {
          (**(code **)(*(long *)this_00 + 8))(this_00);
        }
        pwVar20 = local_108;
        if (local_16c < local_fc) {
          pwVar20 = local_108 + (ulong)local_16c * 8;
        }
        STRINGS::StringConvertToNarrow((STRINGS *)local_78,*(wchar_t **)pwVar20);
                    /* try { // try from 00d315d3 to 00d315d7 has its CatchHandler @ 00d31f6e */
        std::operator+((char *)local_98,(string *)"Unable to load quest from file: ");
        if ((allocator *)(local_78[0] + -0x18) !=
            (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar3 = (int *)(local_78[0] + -8);
          iVar8 = *piVar3;
          *piVar3 = *piVar3 + -1;
          UNLOCK();
          if (iVar8 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
          }
        }
                    /* try { // try from 00d3160d to 00d31611 has its CatchHandler @ 00d31fe1 */
        std::string::string((string *)local_88,local_98[0],&local_3b);
                    /* try { // try from 00d31612 to 00d31628 has its CatchHandler @ 00d31ff6 */
        uVar11 = Ogre::LogManager::getSingleton();
        Ogre::LogManager::logMessage(uVar11,(string *)local_88,3);
        if ((allocator *)(local_88[0] + -0x18) !=
            (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar3 = (int *)(local_88[0] + -8);
          iVar8 = *piVar3;
          *piVar3 = *piVar3 + -1;
          UNLOCK();
          if (iVar8 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
          }
        }
        if ((allocator *)(local_98[0] + -0x18) !=
            (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar3 = (int *)(local_98[0] + -8);
          iVar8 = *piVar3;
          *piVar3 = *piVar3 + -1;
          UNLOCK();
          if (iVar8 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
          }
        }
      }
      else {
        pCVar14 = *(CQuestManager **)(this + 0x80);
        pCVar13 = pCVar1;
        if (pCVar14 != (CQuestManager *)0x0) {
          pwVar5 = *(wchar_t **)(this_00 + 0x50);
          uVar22 = *(ulong *)(pwVar5 + -6);
          do {
            uVar18 = *(ulong *)(*(wchar_t **)(pCVar14 + 0x20) + -6);
            uVar12 = uVar18;
            if (uVar22 <= uVar18) {
              uVar12 = uVar22;
            }
            iVar8 = wmemcmp(*(wchar_t **)(pCVar14 + 0x20),pwVar5,uVar12);
            if (iVar8 == 0) {
              lVar21 = uVar18 - uVar22;
              if (0x7fffffff < lVar21) goto LAB_00d3170e;
              if (-0x80000001 < lVar21) {
                iVar8 = (int)lVar21;
                goto LAB_00d3170a;
              }
LAB_00d31750:
              pCVar6 = *(CQuestManager **)(pCVar14 + 0x18);
            }
            else {
LAB_00d3170a:
              if (iVar8 < 0) goto LAB_00d31750;
LAB_00d3170e:
              pCVar6 = *(CQuestManager **)(pCVar14 + 0x10);
              pCVar13 = pCVar14;
            }
            pCVar14 = pCVar6;
          } while (pCVar14 != (CQuestManager *)0x0);
        }
        if (pCVar1 == pCVar13) {
LAB_00d318a0:
          pCVar14 = *(CQuestManager **)(this + 0x50);
          pCVar13 = pCVar2;
          if (pCVar14 != (CQuestManager *)0x0) {
            pwVar5 = *(wchar_t **)(this_00 + 0x50);
            uVar22 = *(ulong *)(pwVar5 + -6);
            do {
              uVar18 = *(ulong *)(*(wchar_t **)(pCVar14 + 0x20) + -6);
              uVar12 = uVar18;
              if (uVar22 <= uVar18) {
                uVar12 = uVar22;
              }
              iVar8 = wmemcmp(*(wchar_t **)(pCVar14 + 0x20),pwVar5,uVar12);
              if (iVar8 == 0) {
                lVar21 = uVar18 - uVar22;
                if (0x7fffffff < lVar21) goto LAB_00d318d6;
                if (-0x80000001 < lVar21) {
                  iVar8 = (int)lVar21;
                  goto LAB_00d318d2;
                }
LAB_00d31918:
                pCVar6 = *(CQuestManager **)(pCVar14 + 0x18);
              }
              else {
LAB_00d318d2:
                if (iVar8 < 0) goto LAB_00d31918;
LAB_00d318d6:
                pCVar6 = *(CQuestManager **)(pCVar14 + 0x10);
                pCVar13 = pCVar14;
              }
              pCVar14 = pCVar6;
            } while (pCVar14 != (CQuestManager *)0x0);
          }
          if (pCVar2 == pCVar13) {
LAB_00d31987:
                    /* try { // try from 00d31994 to 00d31998 has its CatchHandler @ 00d31f3d */
            std::wstring::wstring((wstring_conflict *)local_c8,(wstring_conflict *)(this_00 + 0x50))
            ;
            local_c8[1] = 0;
                    /* try { // try from 00d319b5 to 00d319b9 has its CatchHandler @ 00d3210e */
            pCVar13 = (CQuestManager *)
                      std::
                      _Rb_tree<std::wstring,std::pair<std::wstring_const,CQuest*>,std::_Select1st<std::pair<std::wstring_const,CQuest*>>,std::less<std::wstring>,std::allocator<std::pair<std::wstring_const,CQuest*>>>
                      ::_M_insert_unique_((_Rb_tree<std::wstring,std::pair<std::wstring_const,CQuest*>,std::_Select1st<std::pair<std::wstring_const,CQuest*>>,std::less<std::wstring>,std::allocator<std::pair<std::wstring_const,CQuest*>>>
                                           *)(this + 0x40),pCVar13,local_c8);
            if ((allocator *)(local_c8[0] + -0x18) !=
                (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar3 = (int *)(local_c8[0] + -8);
              iVar8 = *piVar3;
              *piVar3 = *piVar3 + -1;
              UNLOCK();
              if (iVar8 < 1) {
                std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
              }
            }
          }
          else {
            uVar22 = *(ulong *)(*(wchar_t **)(this_00 + 0x50) + -6);
            uVar18 = *(ulong *)(*(wchar_t **)(pCVar13 + 0x20) + -6);
            uVar12 = uVar22;
            if (uVar18 <= uVar22) {
              uVar12 = uVar18;
            }
            uVar9 = wmemcmp(*(wchar_t **)(this_00 + 0x50),*(wchar_t **)(pCVar13 + 0x20),uVar12);
            uVar12 = (ulong)uVar9;
            if (uVar9 == 0) {
              uVar12 = uVar22 - uVar18;
              if ((long)uVar12 < 0x80000000) {
                if ((long)uVar12 < -0x80000000) goto LAB_00d31987;
                goto LAB_00d31dab;
              }
            }
            else {
LAB_00d31dab:
              if ((int)uVar12 < 0) goto LAB_00d31987;
            }
          }
          *(CQuest **)(pCVar13 + 0x28) = this_00;
          pCVar14 = *(CQuestManager **)(this + 0x80);
          pCVar13 = pCVar1;
          if (pCVar14 != (CQuestManager *)0x0) {
            pwVar5 = *(wchar_t **)(this_00 + 0x50);
            uVar22 = *(ulong *)(pwVar5 + -6);
            do {
              uVar18 = *(ulong *)(*(wchar_t **)(pCVar14 + 0x20) + -6);
              uVar12 = uVar18;
              if (uVar22 <= uVar18) {
                uVar12 = uVar22;
              }
              iVar8 = wmemcmp(*(wchar_t **)(pCVar14 + 0x20),pwVar5,uVar12);
              if (iVar8 == 0) {
                lVar21 = uVar18 - uVar22;
                if (0x7fffffff < lVar21) goto LAB_00d31a14;
                if (-0x80000001 < lVar21) {
                  iVar8 = (int)lVar21;
                  goto LAB_00d31a10;
                }
LAB_00d31a56:
                pCVar6 = *(CQuestManager **)(pCVar14 + 0x18);
              }
              else {
LAB_00d31a10:
                if (iVar8 < 0) goto LAB_00d31a56;
LAB_00d31a14:
                pCVar6 = *(CQuestManager **)(pCVar14 + 0x10);
                pCVar13 = pCVar14;
              }
              pCVar14 = pCVar6;
            } while (pCVar14 != (CQuestManager *)0x0);
          }
          if (pCVar1 == pCVar13) {
LAB_00d31ac5:
                    /* try { // try from 00d31ad2 to 00d31ad6 has its CatchHandler @ 00d31f3d */
            std::wstring::wstring
                      ((wstring_conflict *)&local_e8,(wstring_conflict *)(this_00 + 0x50));
            local_e0 = 0;
                    /* try { // try from 00d31aef to 00d31af3 has its CatchHandler @ 00d3215d */
            pCVar13 = (CQuestManager *)
                      std::
                      _Rb_tree<std::wstring,std::pair<std::wstring_const,bool>,std::_Select1st<std::pair<std::wstring_const,bool>>,std::less<std::wstring>,std::allocator<std::pair<std::wstring_const,bool>>>
                      ::_M_insert_unique_((_Rb_tree<std::wstring,std::pair<std::wstring_const,bool>,std::_Select1st<std::pair<std::wstring_const,bool>>,std::less<std::wstring>,std::allocator<std::pair<std::wstring_const,bool>>>
                                           *)(this + 0x70),pCVar13,&local_e8);
            if ((allocator *)(local_e8 + -0x18) !=
                (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar3 = (int *)(local_e8 + -8);
              iVar8 = *piVar3;
              *piVar3 = *piVar3 + -1;
              UNLOCK();
              if (iVar8 < 1) {
                std::wstring::_Rep::_M_destroy((allocator *)(local_e8 + -0x18));
              }
            }
          }
          else {
            uVar22 = *(ulong *)(*(wchar_t **)(this_00 + 0x50) + -6);
            uVar18 = *(ulong *)(*(wchar_t **)(pCVar13 + 0x20) + -6);
            uVar12 = uVar22;
            if (uVar18 <= uVar22) {
              uVar12 = uVar18;
            }
            uVar9 = wmemcmp(*(wchar_t **)(this_00 + 0x50),*(wchar_t **)(pCVar13 + 0x20),uVar12);
            uVar12 = (ulong)uVar9;
            if (uVar9 == 0) {
              uVar12 = uVar22 - uVar18;
              if ((long)uVar12 < 0x80000000) {
                if ((long)uVar12 < -0x80000000) goto LAB_00d31ac5;
                goto LAB_00d31d9e;
              }
            }
            else {
LAB_00d31d9e:
              if ((int)uVar12 < 0) goto LAB_00d31ac5;
            }
          }
          pCVar13[0x28] = (CQuestManager)0x0;
          local_120 = 0;
          local_11c = 0;
          if (local_128 != (ulong *)0x0) {
            operator_delete__(local_128);
          }
          local_128 = (ulong *)0x0;
                    /* try { // try from 00d31b45 to 00d31d68 has its CatchHandler @ 00d31f3d */
          CQuest::getAllNPCUnitDataInvolvedInQuest(this_00,(TArrayList *)&local_128);
          if (local_120 != 0) {
            uVar22 = 0;
            if (local_11c != 0) goto LAB_00d31c57;
LAB_00d31b68:
            pCVar14 = *(CQuestManager **)(this + 0xb0);
            puVar23 = local_128;
            if (pCVar14 == (CQuestManager *)0x0) goto LAB_00d31c80;
LAB_00d31b7d:
            pCVar13 = pCVar4;
            do {
              if (*(ulong *)(pCVar14 + 0x20) < *puVar23) {
                pCVar6 = *(CQuestManager **)(pCVar14 + 0x18);
              }
              else {
                pCVar6 = *(CQuestManager **)(pCVar14 + 0x10);
                pCVar13 = pCVar14;
              }
              pCVar14 = pCVar6;
            } while (pCVar14 != (CQuestManager *)0x0);
            if (pCVar4 == pCVar13) goto LAB_00d31c80;
            if (*puVar23 < *(ulong *)(pCVar13 + 0x20)) goto LAB_00d31c80;
            plVar16 = *(long **)(pCVar13 + 0x28);
            uVar19 = *(uint *)(plVar16 + 1);
            uVar9 = *(uint *)((long)plVar16 + 0xc);
            if (uVar19 < uVar9) goto LAB_00d31d50;
            do {
              if (*plVar16 == 0) {
                *(uint *)((long)plVar16 + 0xc) = *(uint *)(plVar16 + 2);
                pvVar15 = operator_new__((ulong)*(uint *)(plVar16 + 2) << 3);
                *plVar16 = (long)pvVar15;
                uVar19 = *(uint *)(plVar16 + 1);
              }
              else {
                uVar9 = uVar9 + (int)plVar16[2];
                pvVar15 = operator_new__((ulong)uVar9 << 3);
                if (*(int *)((long)plVar16 + 0xc) != 0) {
                  uVar18 = 0;
                  do {
                    uVar19 = (int)uVar18 + 1;
                    *(undefined8 *)((long)pvVar15 + uVar18 * 8) =
                         *(undefined8 *)(*plVar16 + uVar18 * 8);
                    uVar18 = (ulong)uVar19;
                  } while (uVar19 < *(uint *)((long)plVar16 + 0xc));
                }
                if ((void *)*plVar16 != (void *)0x0) {
                  operator_delete__((void *)*plVar16);
                }
                uVar19 = *(uint *)(plVar16 + 1);
                *plVar16 = (long)pvVar15;
                *(uint *)((long)plVar16 + 0xc) = uVar9;
              }
              while( true ) {
                uVar9 = (int)uVar22 + 1;
                uVar22 = (ulong)uVar9;
                *(CQuest **)((long)pvVar15 + (ulong)uVar19 * 8) = this_00;
                *(int *)(plVar16 + 1) = (int)plVar16[1] + 1;
                if (local_120 <= uVar9) goto LAB_00d31653;
                if (local_11c <= uVar9) goto LAB_00d31b68;
LAB_00d31c57:
                pCVar14 = *(CQuestManager **)(this + 0xb0);
                puVar23 = local_128 + uVar22;
                if (pCVar14 != (CQuestManager *)0x0) goto LAB_00d31b7d;
LAB_00d31c80:
                plVar16 = (long *)Ogre::NedAllocImpl::allocBytes(0x18,(char *)0x0,0,(char *)0x0);
                *plVar16 = 0;
                *(undefined4 *)(plVar16 + 1) = 0;
                *(undefined4 *)((long)plVar16 + 0xc) = 0;
                *(undefined4 *)(plVar16 + 2) = 2;
                if ((uint)uVar22 < local_11c) {
                  pCVar14 = *(CQuestManager **)(this + 0xb0);
                  puVar23 = local_128 + uVar22;
                }
                else {
                  pCVar14 = *(CQuestManager **)(this + 0xb0);
                  puVar23 = local_128;
                }
                pCVar13 = pCVar4;
                if (pCVar14 == (CQuestManager *)0x0) {
                  uVar18 = *puVar23;
                }
                else {
                  uVar18 = *puVar23;
                  do {
                    if (*(ulong *)(pCVar14 + 0x20) < uVar18) {
                      pCVar6 = *(CQuestManager **)(pCVar14 + 0x18);
                    }
                    else {
                      pCVar6 = *(CQuestManager **)(pCVar14 + 0x10);
                      pCVar13 = pCVar14;
                    }
                    pCVar14 = pCVar6;
                  } while (pCVar14 != (CQuestManager *)0x0);
                }
                if ((pCVar4 == pCVar13) || (uVar18 < *(ulong *)(pCVar13 + 0x20))) {
                  local_d8[1] = 0;
                  local_d8[0] = uVar18;
                  pCVar13 = (CQuestManager *)
                            std::
                            _Rb_tree<CDataGroup*,std::pair<CDataGroup*const,TArrayList<CQuest*>*>,std::_Select1st<std::pair<CDataGroup*const,TArrayList<CQuest*>*>>,std::less<CDataGroup*>,std::allocator<std::pair<CDataGroup*const,TArrayList<CQuest*>*>>>
                            ::_M_insert_unique_((_Rb_tree<CDataGroup*,std::pair<CDataGroup*const,TArrayList<CQuest*>*>,std::_Select1st<std::pair<CDataGroup*const,TArrayList<CQuest*>*>>,std::less<CDataGroup*>,std::allocator<std::pair<CDataGroup*const,TArrayList<CQuest*>*>>>
                                                 *)(this + 0xa0),pCVar13,local_d8);
                }
                *(long **)(pCVar13 + 0x28) = plVar16;
                uVar19 = *(uint *)(plVar16 + 1);
                uVar9 = *(uint *)((long)plVar16 + 0xc);
                if (uVar9 <= uVar19) break;
LAB_00d31d50:
                pvVar15 = (void *)*plVar16;
              }
            } while( true );
          }
        }
        else {
          pwVar5 = *(wchar_t **)(this_00 + 0x50);
          uVar22 = *(ulong *)(pwVar5 + -6);
          uVar18 = *(ulong *)(*(wchar_t **)(pCVar13 + 0x20) + -6);
          uVar12 = uVar22;
          if (uVar18 <= uVar22) {
            uVar12 = uVar18;
          }
          iVar8 = wmemcmp(pwVar5,*(wchar_t **)(pCVar13 + 0x20),uVar12);
          if (iVar8 == 0) {
            lVar21 = uVar22 - uVar18;
            if (lVar21 < 0x80000000) {
              if (lVar21 < -0x80000000) goto LAB_00d318a0;
              iVar8 = (int)lVar21;
              goto LAB_00d317b6;
            }
          }
          else {
LAB_00d317b6:
            if (iVar8 < 0) goto LAB_00d318a0;
          }
                    /* try { // try from 00d317c9 to 00d317cd has its CatchHandler @ 00d31f3d */
          STRINGS::StringConvertToNarrow((STRINGS *)local_a8,pwVar5);
                    /* try { // try from 00d317e3 to 00d317e7 has its CatchHandler @ 00d32071 */
          std::operator+((char *)local_98,
                         (string *)"There appears to be two quests named the samething. ");
          if ((allocator *)(local_a8[0] + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar3 = (int *)(local_a8[0] + -8);
            iVar8 = *piVar3;
            *piVar3 = *piVar3 + -1;
            UNLOCK();
            if (iVar8 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
            }
          }
                    /* try { // try from 00d3181d to 00d31821 has its CatchHandler @ 00d320b2 */
          std::string::string((string *)local_b8,local_98[0],&local_3c);
                    /* try { // try from 00d31822 to 00d31838 has its CatchHandler @ 00d320b7 */
          uVar11 = Ogre::LogManager::getSingleton();
          Ogre::LogManager::logMessage(uVar11,(string *)local_b8,3);
          if ((allocator *)(local_b8[0] + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar3 = (int *)(local_b8[0] + -8);
            iVar8 = *piVar3;
            *piVar3 = *piVar3 + -1;
            UNLOCK();
            if (iVar8 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
            }
          }
                    /* try { // try from 00d31855 to 00d31857 has its CatchHandler @ 00d320fe */
          (**(code **)(*(long *)this_00 + 8))(this_00);
          if ((allocator *)(local_98[0] + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar3 = (int *)(local_98[0] + -8);
            iVar8 = *piVar3;
            *piVar3 = *piVar3 + -1;
            UNLOCK();
            if (iVar8 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
            }
          }
        }
      }
LAB_00d31653:
      local_16c = local_16c + 1;
    } while (local_16c < local_100);
    if (local_128 != (ulong *)0x0) {
      operator_delete__(local_128);
      local_128 = (ulong *)0x0;
    }
  }
  if (local_108 != (wstring_conflict *)0x0) {
    pwVar20 = local_108 + *(long *)(local_108 + -8) * 8;
    pwVar17 = local_108;
    while (pwVar17 != pwVar20) {
      pwVar20 = pwVar20 + -8;
      paVar24 = (allocator *)(*(long *)pwVar20 + -0x18);
      if (paVar24 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar3 = (int *)(*(long *)pwVar20 + -8);
        iVar8 = *piVar3;
        *piVar3 = *piVar3 + -1;
        UNLOCK();
        pwVar17 = local_108;
        if (iVar8 < 1) {
          std::wstring::_Rep::_M_destroy(paVar24);
          pwVar17 = local_108;
        }
      }
    }
    operator_delete__(pwVar17 + -8);
  }
  return;
}

/* address=00d321f0
   symbol=CQuestManager::reloadQuests */

/* CQuestManager::reloadQuests() */

void __thiscall CQuestManager::reloadQuests(CQuestManager *this)

{
  _Rb_tree_node_base *p_Var1;

  *(undefined4 *)(this + 0x20) = 0;
  *(undefined4 *)(this + 0x24) = 0;
  if (*(void **)(this + 0x18) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x18));
  }
  p_Var1 = *(_Rb_tree_node_base **)(this + 0x58);
  *(undefined8 *)(this + 0x18) = 0;
  for (; p_Var1 != (_Rb_tree_node_base *)(this + 0x48);
      p_Var1 = (_Rb_tree_node_base *)std::_Rb_tree_increment(p_Var1)) {
    if (*(long **)(p_Var1 + 0x28) != (long *)0x0) {
      (**(code **)(**(long **)(p_Var1 + 0x28) + 8))();
      *(undefined8 *)(p_Var1 + 0x28) = 0;
    }
  }
  std::
  _Rb_tree<std::wstring,std::pair<std::wstring_const,CQuest*>,std::_Select1st<std::pair<std::wstring_const,CQuest*>>,std::less<std::wstring>,std::allocator<std::pair<std::wstring_const,CQuest*>>>
  ::_M_erase((_Rb_tree<std::wstring,std::pair<std::wstring_const,CQuest*>,std::_Select1st<std::pair<std::wstring_const,CQuest*>>,std::less<std::wstring>,std::allocator<std::pair<std::wstring_const,CQuest*>>>
              *)(this + 0x40),*(_Rb_tree_node **)(this + 0x50));
  *(_Rb_tree_node_base **)(this + 0x58) = p_Var1;
  *(_Rb_tree_node_base **)(this + 0x60) = p_Var1;
  *(undefined8 *)(this + 0x50) = 0;
  *(undefined8 *)(this + 0x68) = 0;
  std::
  _Rb_tree<CDataGroup*,std::pair<CDataGroup*const,TArrayList<CQuest*>*>,std::_Select1st<std::pair<CDataGroup*const,TArrayList<CQuest*>*>>,std::less<CDataGroup*>,std::allocator<std::pair<CDataGroup*const,TArrayList<CQuest*>*>>>
  ::_M_erase((_Rb_tree<CDataGroup*,std::pair<CDataGroup*const,TArrayList<CQuest*>*>,std::_Select1st<std::pair<CDataGroup*const,TArrayList<CQuest*>*>>,std::less<CDataGroup*>,std::allocator<std::pair<CDataGroup*const,TArrayList<CQuest*>*>>>
              *)(this + 0xa0),*(_Rb_tree_node **)(this + 0xb0));
  *(undefined8 *)(this + 0xb0) = 0;
  *(undefined8 *)(this + 200) = 0;
  *(CQuestManager **)(this + 0xb8) = this + 0xa8;
  *(CQuestManager **)(this + 0xc0) = this + 0xa8;
  std::
  _Rb_tree<std::wstring,std::pair<std::wstring_const,bool>,std::_Select1st<std::pair<std::wstring_const,bool>>,std::less<std::wstring>,std::allocator<std::pair<std::wstring_const,bool>>>
  ::_M_erase((_Rb_tree<std::wstring,std::pair<std::wstring_const,bool>,std::_Select1st<std::pair<std::wstring_const,bool>>,std::less<std::wstring>,std::allocator<std::pair<std::wstring_const,bool>>>
              *)(this + 0x70),*(_Rb_tree_node **)(this + 0x80));
  *(undefined8 *)(this + 0x80) = 0;
  *(undefined8 *)(this + 0x98) = 0;
  *(CQuestManager **)(this + 0x88) = this + 0x78;
  *(CQuestManager **)(this + 0x90) = this + 0x78;
  loadQuests(this);
  return;
}

/* address=00d32300
   symbol=CQuestManager::CQuestManager */

/* WARNING: Removing unreachable block (ram,0x00d325d7) */
/* WARNING: Removing unreachable block (ram,0x00d32597) */
/* CQuestManager::CQuestManager(CResourceManager*) */

void __thiscall CQuestManager::CQuestManager(CQuestManager *this,CResourceManager *param_1)

{
  int *piVar1;
  int iVar2;
  CSoundManager *pCVar3;
  CSoundBankDataInformation *this_00;
  long lVar4;
  CSoundBank *this_01;
  long local_38 [2];
  long local_28;
  allocator local_1a;
  allocator local_19;

  CRunicCore::CRunicCore((CRunicCore *)this);
  *(undefined ***)this = &PTR__CQuestManager_00ff7790;
  *(undefined8 *)(this + 0x10) = 0;
  *(undefined8 *)(this + 0x18) = 0;
  *(undefined4 *)(this + 0x20) = 0;
  *(CQuestManager **)(this + 0x58) = this + 0x48;
  *(CQuestManager **)(this + 0x60) = this + 0x48;
  *(undefined4 *)(this + 0x24) = 0;
  *(undefined4 *)(this + 0x28) = 10;
  *(CQuestManager **)(this + 0x88) = this + 0x78;
  *(CQuestManager **)(this + 0x90) = this + 0x78;
  *(CResourceManager **)(this + 0x38) = param_1;
  *(undefined8 *)(this + 0x68) = 0;
  *(undefined4 *)(this + 0x48) = 0;
  *(undefined8 *)(this + 0x50) = 0;
  *(undefined8 *)(this + 0x98) = 0;
  *(undefined4 *)(this + 0x78) = 0;
  *(undefined8 *)(this + 0x80) = 0;
  *(undefined8 *)(this + 200) = 0;
  *(undefined4 *)(this + 0xa8) = 0;
  *(undefined8 *)(this + 0xb0) = 0;
  *(CQuestManager **)(this + 0xb8) = this + 0xa8;
  *(CQuestManager **)(this + 0xc0) = this + 0xa8;
  if (g_pQuestManager == (CQuestManager *)0x0) {
    g_pQuestManager = this;
                    /* try { // try from 00d323ff to 00d3241a has its CatchHandler @ 00d324e7 */
    lVar4 = CMasterResourceManager::getSingleton();
    pCVar3 = *(CSoundManager **)(lVar4 + 0x98);
    this_01 = (CSoundBank *)Ogre::NedAllocImpl::allocBytes(0xd0,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00d32426 to 00d3242a has its CatchHandler @ 00d325e7 */
    CSoundBank::CSoundBank(this_01,pCVar3,false);
    *(CSoundBank **)(this + 0x30) = this_01;
                    /* try { // try from 00d3242f to 00d32433 has its CatchHandler @ 00d324e7 */
    lVar4 = CMasterResourceManager::getSingleton();
    this_00 = *(CSoundBankDataInformation **)(lVar4 + 0x100);
                    /* try { // try from 00d3244d to 00d32451 has its CatchHandler @ 00d325e2 */
    std::wstring::wstring((wstring_conflict *)&local_28,L"QUESTRECEIVED",&local_19);
                    /* try { // try from 00d32458 to 00d3245c has its CatchHandler @ 00d325d5 */
    lVar4 = CSoundBankDataInformation::getSoundDataObject(this_00,(wstring_conflict *)&local_28);
    if ((allocator *)(local_28 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_28 + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_28 + -0x18));
      }
    }
    if (lVar4 != 0) {
                    /* try { // try from 00d32485 to 00d32489 has its CatchHandler @ 00d324e7 */
      CSoundBank::addSample(*(CSoundBank **)(this + 0x30),0x1f,*(longlong *)(lVar4 + 0x20));
    }
                    /* try { // try from 00d3249c to 00d324a0 has its CatchHandler @ 00d32592 */
    std::wstring::wstring((wstring_conflict *)local_38,L"QUESTCOMPLETED",&local_1a);
                    /* try { // try from 00d324a7 to 00d324ab has its CatchHandler @ 00d32582 */
    lVar4 = CSoundBankDataInformation::getSoundDataObject(this_00,(wstring_conflict *)local_38);
    if ((allocator *)(local_38[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_38[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_38[0] + -0x18));
      }
    }
    if (lVar4 != 0) {
                    /* try { // try from 00d324d5 to 00d324e1 has its CatchHandler @ 00d324e7 */
      CSoundBank::addSample(*(CSoundBank **)(this + 0x30),0x20,*(longlong *)(lVar4 + 0x20));
    }
    loadQuests(this);
  }
  return;
}

/* address=00d32600
   symbol=CQuestManager::completeQuest */

/* WARNING: Removing unreachable block (ram,0x00d32ec3) */
/* WARNING: Removing unreachable block (ram,0x00d32f89) */
/* WARNING: Removing unreachable block (ram,0x00d33011) */
/* WARNING: Removing unreachable block (ram,0x00d33080) */
/* WARNING: Removing unreachable block (ram,0x00d3312a) */
/* WARNING: Removing unreachable block (ram,0x00d3313a) */
/* WARNING: Removing unreachable block (ram,0x00d330af) */
/* WARNING: Removing unreachable block (ram,0x00d3301e) */
/* WARNING: Removing unreachable block (ram,0x00d32f94) */
/* WARNING: Removing unreachable block (ram,0x00d32f05) */
/* WARNING: Removing unreachable block (ram,0x00d32eb8) */
/* CQuestManager::completeQuest(CQuest*) */

undefined8 __thiscall CQuestManager::completeQuest(CQuestManager *this,CQuest *param_1)

{
  long *plVar1;
  CQuestManager *pCVar2;
  wstring_conflict *pwVar3;
  allocator *paVar4;
  int *piVar5;
  wchar_t *pwVar6;
  int iVar7;
  wchar_t wVar8;
  long *plVar9;
  ulong uVar10;
  ulong uVar11;
  CQuestManager *pCVar12;
  int iVar13;
  uint uVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  undefined8 *puVar18;
  wstring_conflict *pwVar19;
  CSteamStats *pCVar20;
  undefined8 uVar21;
  CAchievements *pCVar22;
  CAchievement *pCVar23;
  long *plVar24;
  ulong uVar25;
  uint uVar26;
  CQuestManager *pCVar27;
  long lVar28;
  wchar_t *pwVar29;
  bool bVar30;
  CQuestManager *local_130;
  long local_118;
  undefined1 local_110;
  wstring_conflict local_108 [16];
  wstring_conflict local_f8 [16];
  long local_e8 [2];
  wchar_t *local_d8 [2];
  wchar_t *local_c8 [2];
  wchar_t *local_b8 [2];
  long local_a8 [2];
  wchar_t *local_98 [2];
  wchar_t *local_88 [2];
  long local_78 [2];
  wchar_t *local_68 [2];
  wchar_t *local_58 [3];
  allocator local_3a;
  allocator local_39 [9];

  if (param_1 == (CQuest *)0x0) {
    return 0;
  }
  if (*(long *)(this + 0x10) != 0) {
    giveRewardForQuest(this,param_1);
  }
  CQuest::setQuestAccepted(param_1,false);
  CQuest::initializeQuestWithNPC(param_1,(CBaseUnit *)0x0);
  CQuest::setIsComplete(param_1,(bool)((byte)param_1[0x20b] ^ 1));
  uVar26 = *(uint *)(this + 0x20);
  if (uVar26 != 0) {
    plVar9 = *(long **)(this + 0x18);
    uVar14 = 0;
    plVar24 = plVar9;
    if (param_1 == (CQuest *)*plVar9) {
      uVar14 = 0;
    }
    else {
      do {
        uVar14 = uVar14 + 1;
        if (uVar26 <= uVar14) goto LAB_00d32690;
        plVar1 = plVar24 + 1;
        plVar24 = plVar24 + 1;
      } while (param_1 != (CQuest *)*plVar1);
      if (uVar14 == 0xffffffff) goto LAB_00d32690;
    }
    *(uint *)(this + 0x20) = uVar26 - 1;
    plVar9[uVar14] = plVar9[uVar26 - 1];
  }
LAB_00d32690:
  pCVar2 = this + 0x78;
  pwVar3 = (wstring_conflict *)(param_1 + 0x50);
  pCVar27 = *(CQuestManager **)(this + 0x80);
  local_130 = pCVar2;
  if (pCVar27 != (CQuestManager *)0x0) {
    pwVar29 = *(wchar_t **)(param_1 + 0x50);
    uVar10 = *(ulong *)(pwVar29 + -6);
    do {
      uVar11 = *(ulong *)(*(wchar_t **)(pCVar27 + 0x20) + -6);
      uVar25 = uVar11;
      if (uVar10 <= uVar11) {
        uVar25 = uVar10;
      }
      iVar13 = wmemcmp(*(wchar_t **)(pCVar27 + 0x20),pwVar29,uVar25);
      if (iVar13 == 0) {
        lVar28 = uVar11 - uVar10;
        if (0x7fffffff < lVar28) goto LAB_00d326c7;
        if (-0x80000001 < lVar28) {
          iVar13 = (int)lVar28;
          goto LAB_00d326c3;
        }
LAB_00d3270d:
        pCVar12 = *(CQuestManager **)(pCVar27 + 0x18);
      }
      else {
LAB_00d326c3:
        if (iVar13 < 0) goto LAB_00d3270d;
LAB_00d326c7:
        pCVar12 = *(CQuestManager **)(pCVar27 + 0x10);
        local_130 = pCVar27;
      }
      pCVar27 = pCVar12;
    } while (pCVar27 != (CQuestManager *)0x0);
  }
  if (pCVar2 == local_130) {
LAB_00d32b00:
    std::wstring::wstring((wstring_conflict *)&local_118,pwVar3);
    local_110 = 0;
                    /* try { // try from 00d32b23 to 00d32b27 has its CatchHandler @ 00d330ba */
    local_130 = (CQuestManager *)
                std::
                _Rb_tree<std::wstring,std::pair<std::wstring_const,bool>,std::_Select1st<std::pair<std::wstring_const,bool>>,std::less<std::wstring>,std::allocator<std::pair<std::wstring_const,bool>>>
                ::_M_insert_unique_((_Rb_tree<std::wstring,std::pair<std::wstring_const,bool>,std::_Select1st<std::pair<std::wstring_const,bool>>,std::less<std::wstring>,std::allocator<std::pair<std::wstring_const,bool>>>
                                     *)(this + 0x70),local_130,(wstring_conflict *)&local_118);
    if ((allocator *)(local_118 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar5 = (int *)(local_118 + -8);
      iVar13 = *piVar5;
      *piVar5 = *piVar5 + -1;
      UNLOCK();
      if (iVar13 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_118 + -0x18));
      }
    }
  }
  else {
    uVar10 = *(ulong *)(*(wchar_t **)(param_1 + 0x50) + -6);
    uVar11 = *(ulong *)(*(wchar_t **)(local_130 + 0x20) + -6);
    uVar25 = uVar10;
    if (uVar11 <= uVar10) {
      uVar25 = uVar11;
    }
    iVar13 = wmemcmp(*(wchar_t **)(param_1 + 0x50),*(wchar_t **)(local_130 + 0x20),uVar25);
    if (iVar13 == 0) {
      lVar28 = uVar10 - uVar11;
      if (lVar28 < 0x80000000) {
        if (lVar28 < -0x80000000) goto LAB_00d32b00;
        iVar13 = (int)lVar28;
        goto LAB_00d32766;
      }
    }
    else {
LAB_00d32766:
      if (iVar13 < 0) goto LAB_00d32b00;
    }
  }
  local_130[0x28] = (CQuestManager)((byte)param_1[0x20b] ^ 1);
  if (*(int *)(param_1 + 0x1b8) != 0) {
    uVar26 = 0;
    do {
      if (uVar26 < *(uint *)(param_1 + 0x1bc)) {
        puVar18 = (undefined8 *)((ulong)uVar26 * 8 + *(long *)(param_1 + 0x1b0));
      }
      else {
        puVar18 = *(undefined8 **)(param_1 + 0x1b0);
      }
      if (*(long *)*puVar18 != 0) {
        if (uVar26 < *(uint *)(param_1 + 0x1bc)) {
          puVar18 = (undefined8 *)((ulong)uVar26 * 8 + *(long *)(param_1 + 0x1b0));
        }
        else {
          puVar18 = *(undefined8 **)(param_1 + 0x1b0);
        }
        std::wstring::wstring
                  ((wstring_conflict *)local_58,(wstring_conflict *)(*(long *)*puVar18 + 0xa8));
        pwVar29 = local_58[0];
        bVar30 = false;
        paVar4 = (allocator *)(local_58[0] + -6);
        if (*(size_t *)(local_58[0] + -6) == *(size_t *)(*(wchar_t **)(param_1 + 0x50) + -6)) {
          iVar13 = wmemcmp(local_58[0],*(wchar_t **)(param_1 + 0x50),*(size_t *)(local_58[0] + -6));
          bVar30 = iVar13 == 0;
        }
        if (paVar4 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          pwVar29 = pwVar29 + -2;
          wVar8 = *pwVar29;
          *pwVar29 = *pwVar29 + L'\xffffffff';
          UNLOCK();
          if (wVar8 < L'\x01') {
            std::wstring::_Rep::_M_destroy(paVar4);
          }
        }
        if (bVar30) {
          if (uVar26 < *(uint *)(param_1 + 0x1bc)) {
            puVar18 = (undefined8 *)((ulong)uVar26 * 8 + *(long *)(param_1 + 0x1b0));
          }
          else {
            puVar18 = *(undefined8 **)(param_1 + 0x1b0);
          }
          CQuestController::questHasBeenCompleted(*(CQuestController **)*puVar18,true);
        }
      }
      uVar26 = uVar26 + 1;
    } while (uVar26 < *(uint *)(param_1 + 0x1b8));
  }
  if (*(CLevel **)(*(long *)(this + 0x38) + 0x18) != (CLevel *)0x0) {
    CLevel::updateNPCIcons(*(CLevel **)(*(long *)(this + 0x38) + 0x18));
    CLevel::updateAutomapIcons();
  }
                    /* try { // try from 00d328aa to 00d32949 has its CatchHandler @ 00d330cd */
  std::wstring::wstring((wstring_conflict *)local_78,L"PalaceAlricDead",local_39);
  STRINGS::StringUpper((STRINGS *)local_88,(wstring_conflict *)local_78);
  STRINGS::StringUpper((STRINGS *)local_68,pwVar3);
  pwVar29 = local_68[0];
  if ((*(size_t *)(local_68[0] + -6) == *(size_t *)(local_88[0] + -6)) &&
     (iVar13 = wmemcmp(local_68[0],local_88[0],*(size_t *)(local_68[0] + -6)), iVar13 == 0)) {
    bVar30 = true;
    local_68[0] = pwVar29;
    goto LAB_00d329a7;
  }
  std::wstring::wstring((wstring_conflict *)local_a8,L"PalacePT2",&local_3a);
  STRINGS::StringUpper((STRINGS *)local_b8,(wstring_conflict *)local_a8);
  STRINGS::StringUpper((STRINGS *)local_98,pwVar3);
  pwVar29 = local_b8[0];
  if (*(size_t *)(local_98[0] + -6) == *(size_t *)(local_b8[0] + -6)) {
    iVar13 = wmemcmp(local_98[0],local_b8[0],*(size_t *)(local_98[0] + -6));
    bVar30 = true;
    if (iVar13 != 0) goto LAB_00d3296c;
  }
  else {
LAB_00d3296c:
    bVar30 = false;
  }
  if ((allocator *)(local_98[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    pwVar29 = local_98[0] + -2;
    wVar8 = *pwVar29;
    *pwVar29 = *pwVar29 + L'\xffffffff';
    UNLOCK();
    pwVar29 = local_b8[0];
    if (wVar8 < L'\x01') {
      std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -6));
      pwVar29 = local_b8[0];
    }
  }
  if ((allocator *)(pwVar29 + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    pwVar6 = pwVar29 + -2;
    wVar8 = *pwVar6;
    *pwVar6 = *pwVar6 + L'\xffffffff';
    UNLOCK();
    if (wVar8 < L'\x01') {
      std::wstring::_Rep::_M_destroy((allocator *)(pwVar29 + -6));
    }
  }
  if ((allocator *)(local_a8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar5 = (int *)(local_a8[0] + -8);
    iVar13 = *piVar5;
    *piVar5 = *piVar5 + -1;
    UNLOCK();
    if (iVar13 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
    }
  }
LAB_00d329a7:
  if ((allocator *)(local_68[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    pwVar29 = local_68[0] + -2;
    wVar8 = *pwVar29;
    *pwVar29 = *pwVar29 + L'\xffffffff';
    UNLOCK();
    if (wVar8 < L'\x01') {
      std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -6));
    }
  }
  if ((allocator *)(local_88[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    pwVar29 = local_88[0] + -2;
    wVar8 = *pwVar29;
    *pwVar29 = *pwVar29 + L'\xffffffff';
    UNLOCK();
    if (wVar8 < L'\x01') {
      std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -6));
    }
  }
  if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar5 = (int *)(local_78[0] + -8);
    iVar13 = *piVar5;
    *piVar5 = *piVar5 + -1;
    UNLOCK();
    if (iVar13 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
    }
  }
  if (bVar30) {
    pCVar22 = (CAchievements *)CAchievements::getSingleton();
    pCVar23 = (CAchievement *)CAchievements::getAchievement(pCVar22,0xd);
    CAchievement::forceComplete(pCVar23);
  }
  uVar26 = KSETTINGS_RETIREE_QUEST;
  if (*(long *)(this + 0x10) != 0) {
    lVar28 = CMasterResourceManager::getSingleton();
    pwVar19 = (wstring_conflict *)
              CDynamicPropertyFile::GetString(*(CDynamicPropertyFile **)(lVar28 + 0x90),uVar26);
    STRINGS::StringUpper((STRINGS *)local_d8,pwVar19);
                    /* try { // try from 00d32a2c to 00d32a30 has its CatchHandler @ 00d32f10 */
    STRINGS::StringUpper((STRINGS *)local_c8,pwVar3);
    pwVar29 = local_d8[0];
    bVar30 = false;
    if (*(size_t *)(local_c8[0] + -6) == *(size_t *)(local_d8[0] + -6)) {
      iVar13 = wmemcmp(local_c8[0],local_d8[0],*(size_t *)(local_c8[0] + -6));
      bVar30 = iVar13 == 0;
    }
    if ((allocator *)(local_c8[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      pwVar29 = local_c8[0] + -2;
      wVar8 = *pwVar29;
      *pwVar29 = *pwVar29 + L'\xffffffff';
      UNLOCK();
      pwVar29 = local_d8[0];
      if (wVar8 < L'\x01') {
        std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -6));
        pwVar29 = local_d8[0];
      }
    }
    if ((allocator *)(pwVar29 + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      pwVar6 = pwVar29 + -2;
      wVar8 = *pwVar6;
      *pwVar6 = *pwVar6 + L'\xffffffff';
      UNLOCK();
      if (wVar8 < L'\x01') {
        std::wstring::_Rep::_M_destroy((allocator *)(pwVar29 + -6));
      }
    }
    uVar26 = KSETTINGS_GAME_COMPLETED_ONCE;
    if (bVar30) {
      lVar28 = CMasterResourceManager::getSingleton();
      CDynamicPropertyFile::SetInt(*(CDynamicPropertyFile **)(lVar28 + 0x90),uVar26,1);
      if (((*(int *)(*(long *)(this + 0x38) + 0x30) != 0) &&
          (lVar28 = **(long **)(*(long *)(this + 0x38) + 0x28), lVar28 != 0)) &&
         (*(int *)(lVar28 + 0x38d0) == 1)) {
        pCVar20 = (CSteamStats *)CSteamStats::getSingleton();
        iVar13 = CSteamStats::getStatInt(pCVar20,0x17);
        pCVar20 = (CSteamStats *)CSteamStats::getSingleton();
        iVar15 = CSteamStats::getStatInt(pCVar20,0x16);
        pCVar20 = (CSteamStats *)CSteamStats::getSingleton();
        iVar16 = CSteamStats::getStatInt(pCVar20,0x15);
                    /* try { // try from 00d32c59 to 00d32c70 has its CatchHandler @ 00d32e85 */
        CPlayer::getPlayerClassName();
        iVar17 = std::wstring::compare((wchar_t *)local_e8);
        if ((allocator *)(local_e8[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar5 = (int *)(local_e8[0] + -8);
          iVar7 = *piVar5;
          *piVar5 = *piVar5 + -1;
          UNLOCK();
          if (iVar7 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
          }
        }
        if (iVar17 == 0 && iVar13 == 0) {
          uVar21 = CSteamStats::getSingleton();
          CSteamStats::incrementStat(uVar21,0x17,1);
          iVar13 = iVar13 + 1;
          bVar30 = iVar16 != 0;
        }
        else {
                    /* try { // try from 00d32d42 to 00d32d59 has its CatchHandler @ 00d32e57 */
          CPlayer::getPlayerClassName();
          iVar17 = std::wstring::compare((wchar_t *)local_f8);
          if ((iVar17 == 0) && (iVar15 == 0)) {
            iVar15 = 1;
            std::wstring::~wstring(local_f8);
            uVar21 = CSteamStats::getSingleton();
            CSteamStats::incrementStat(uVar21,0x16,1);
            bVar30 = iVar16 != 0;
          }
          else {
            std::wstring::~wstring(local_f8);
                    /* try { // try from 00d32d75 to 00d32d8c has its CatchHandler @ 00d32e3f */
            CPlayer::getPlayerClassName();
            iVar17 = std::wstring::compare((wchar_t *)local_108);
            if ((iVar17 == 0) && (iVar16 == 0)) {
              std::wstring::~wstring(local_108);
              uVar21 = CSteamStats::getSingleton();
              CSteamStats::incrementStat(uVar21,0x15,1);
              bVar30 = true;
            }
            else {
              std::wstring::~wstring(local_108);
              bVar30 = iVar16 != 0;
            }
          }
        }
        if (((iVar13 != 0) && (bVar30)) && (iVar15 != 0)) {
          pCVar22 = (CAchievements *)CAchievements::getSingleton();
          pCVar23 = (CAchievement *)CAchievements::getAchievement(pCVar22,0x17);
          CAchievement::forceComplete(pCVar23);
          return 1;
        }
      }
    }
  }
  return 1;
}

/* address=00d33150
   symbol=CQuestManager::giveQuest */
/* DECOMPILATION FAILED:
Low-level Error: Overriding symbol with different type size */

/* address=00d339d0
   symbol=CQuestManager::resetQuest */

/* WARNING: Removing unreachable block (ram,0x00d33d2a) */
/* WARNING: Removing unreachable block (ram,0x00d33d1b) */
/* CQuestManager::resetQuest(CQuest*) */

void __thiscall CQuestManager::resetQuest(CQuestManager *this,CQuest *param_1)

{
  long *plVar1;
  int *piVar2;
  allocator *paVar3;
  wchar_t wVar4;
  long *plVar5;
  wchar_t *pwVar6;
  ulong uVar7;
  ulong uVar8;
  CQuestManager *pCVar9;
  int iVar10;
  uint uVar11;
  undefined8 *puVar12;
  CQuestManager *pCVar13;
  long *plVar14;
  CQuestManager *pCVar15;
  ulong uVar16;
  uint uVar17;
  CQuestManager *pCVar18;
  long lVar19;
  bool bVar20;
  long local_58;
  undefined1 local_50;
  wchar_t *local_48 [3];

  if (param_1 == (CQuest *)0x0) {
    return;
  }
  uVar17 = *(uint *)(this + 0x20);
  if (uVar17 != 0) {
    plVar5 = *(long **)(this + 0x18);
    uVar11 = 0;
    plVar14 = plVar5;
    if (param_1 == (CQuest *)*plVar5) {
      uVar11 = 0;
    }
    else {
      do {
        uVar11 = uVar11 + 1;
        if (uVar17 <= uVar11) goto LAB_00d33a28;
        plVar1 = plVar14 + 1;
        plVar14 = plVar14 + 1;
      } while (param_1 != (CQuest *)*plVar1);
      if (uVar11 == 0xffffffff) goto LAB_00d33a28;
    }
    *(uint *)(this + 0x20) = uVar17 - 1;
    plVar5[uVar11] = plVar5[uVar17 - 1];
  }
LAB_00d33a28:
  pCVar15 = this + 0x78;
  pCVar18 = *(CQuestManager **)(this + 0x80);
  pCVar13 = pCVar15;
  if (pCVar18 != (CQuestManager *)0x0) {
    pwVar6 = *(wchar_t **)(param_1 + 0x50);
    uVar7 = *(ulong *)(pwVar6 + -6);
    do {
      uVar8 = *(ulong *)(*(wchar_t **)(pCVar18 + 0x20) + -6);
      uVar16 = uVar7;
      if (uVar8 <= uVar7) {
        uVar16 = uVar8;
      }
      iVar10 = wmemcmp(*(wchar_t **)(pCVar18 + 0x20),pwVar6,uVar16);
      if (iVar10 == 0) {
        lVar19 = uVar8 - uVar7;
        if (0x7fffffff < lVar19) goto LAB_00d33a67;
        if (-0x80000001 < lVar19) {
          iVar10 = (int)lVar19;
          goto LAB_00d33a63;
        }
LAB_00d33aa9:
        pCVar9 = *(CQuestManager **)(pCVar18 + 0x18);
      }
      else {
LAB_00d33a63:
        if (iVar10 < 0) goto LAB_00d33aa9;
LAB_00d33a67:
        pCVar9 = *(CQuestManager **)(pCVar18 + 0x10);
        pCVar13 = pCVar18;
      }
      pCVar18 = pCVar9;
    } while (pCVar18 != (CQuestManager *)0x0);
  }
  if (pCVar15 != pCVar13) {
    uVar7 = *(ulong *)(*(wchar_t **)(param_1 + 0x50) + -6);
    uVar8 = *(ulong *)(*(wchar_t **)(pCVar13 + 0x20) + -6);
    uVar16 = uVar7;
    if (uVar8 <= uVar7) {
      uVar16 = uVar8;
    }
    iVar10 = wmemcmp(*(wchar_t **)(param_1 + 0x50),*(wchar_t **)(pCVar13 + 0x20),uVar16);
    if (iVar10 == 0) {
      lVar19 = uVar7 - uVar8;
      if (0x7fffffff < lVar19) goto LAB_00d33b07;
      if (lVar19 < -0x80000000) goto LAB_00d33c60;
      iVar10 = (int)lVar19;
    }
    if (-1 < iVar10) goto LAB_00d33b07;
  }
LAB_00d33c60:
  std::wstring::wstring((wstring_conflict *)&local_58,(wstring_conflict *)(param_1 + 0x50));
  local_50 = 0;
                    /* try { // try from 00d33c86 to 00d33c8a has its CatchHandler @ 00d33d08 */
  pCVar13 = (CQuestManager *)
            std::
            _Rb_tree<std::wstring,std::pair<std::wstring_const,bool>,std::_Select1st<std::pair<std::wstring_const,bool>>,std::less<std::wstring>,std::allocator<std::pair<std::wstring_const,bool>>>
            ::_M_insert_unique_((_Rb_tree<std::wstring,std::pair<std::wstring_const,bool>,std::_Select1st<std::pair<std::wstring_const,bool>>,std::less<std::wstring>,std::allocator<std::pair<std::wstring_const,bool>>>
                                 *)(this + 0x70),pCVar13,(wstring_conflict *)&local_58);
  if ((allocator *)(local_58 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(local_58 + -8);
    iVar10 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar10 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_58 + -0x18));
    }
  }
LAB_00d33b07:
  pCVar13[0x28] = (CQuestManager)0x0;
  if (*(int *)(param_1 + 0x1b8) != 0) {
    uVar17 = 0;
    do {
      if (uVar17 < *(uint *)(param_1 + 0x1bc)) {
        puVar12 = (undefined8 *)((ulong)uVar17 * 8 + *(long *)(param_1 + 0x1b0));
      }
      else {
        puVar12 = *(undefined8 **)(param_1 + 0x1b0);
      }
      if (*(long *)*puVar12 != 0) {
        if (uVar17 < *(uint *)(param_1 + 0x1bc)) {
          puVar12 = (undefined8 *)((ulong)uVar17 * 8 + *(long *)(param_1 + 0x1b0));
        }
        else {
          puVar12 = *(undefined8 **)(param_1 + 0x1b0);
        }
        std::wstring::wstring
                  ((wstring_conflict *)local_48,(wstring_conflict *)(*(long *)*puVar12 + 0xa8));
        pwVar6 = local_48[0];
        bVar20 = false;
        paVar3 = (allocator *)(local_48[0] + -6);
        if (*(size_t *)(local_48[0] + -6) == *(size_t *)(*(wchar_t **)(param_1 + 0x50) + -6)) {
          iVar10 = wmemcmp(local_48[0],*(wchar_t **)(param_1 + 0x50),*(size_t *)(local_48[0] + -6));
          bVar20 = iVar10 == 0;
        }
        if (paVar3 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          pwVar6 = pwVar6 + -2;
          wVar4 = *pwVar6;
          *pwVar6 = *pwVar6 + L'\xffffffff';
          UNLOCK();
          if (wVar4 < L'\x01') {
            std::wstring::_Rep::_M_destroy(paVar3);
          }
        }
        if (bVar20) {
          if (uVar17 < *(uint *)(param_1 + 0x1bc)) {
            puVar12 = (undefined8 *)((ulong)uVar17 * 8 + *(long *)(param_1 + 0x1b0));
          }
          else {
            puVar12 = *(undefined8 **)(param_1 + 0x1b0);
          }
          CQuestController::questHasBeenCompleted(*(CQuestController **)*puVar12,false);
        }
      }
      uVar17 = uVar17 + 1;
    } while (uVar17 < *(uint *)(param_1 + 0x1b8));
  }
  return;
}

/* export-summary functions=29 failures=2 */
