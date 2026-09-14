/* Targeted Ghidra class export.
   namespace=CDataGroup
   Treat pseudocode as navigation evidence. */


/* address=00c5ed90
   symbol=CDataGroup::stringRepository */

/* CDataGroup::stringRepository() */

undefined1 * CDataGroup::stringRepository(void)

{
  return g_GlobalRepository;
}

/* address=00c5eda0
   symbol=CDataGroup::RemoveDataGroup */

/* CDataGroup::RemoveDataGroup(CDataGroup*) */

void __thiscall CDataGroup::RemoveDataGroup(CDataGroup *this,CDataGroup *param_1)

{
  uint uVar1;
  long *plVar2;
  long lVar3;
  uint uVar4;
  long lVar5;

  if (param_1 == (CDataGroup *)0x0) {
    return;
  }
  uVar1 = *(uint *)(this + 0x40);
  this[0x58] = (CDataGroup)0x1;
  if (uVar1 == 0) {
LAB_00c5eddd:
                    /* WARNING: Could not recover jumptable at 0x00c5ede7. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*(long *)param_1 + 8))(param_1);
    return;
  }
  plVar2 = *(long **)(this + 0x38);
  uVar4 = 0;
  lVar3 = 8;
  if (param_1 == (CDataGroup *)*plVar2) {
    lVar5 = 0;
  }
  else {
    do {
      lVar5 = lVar3;
      uVar4 = uVar4 + 1;
      if (uVar1 <= uVar4) goto LAB_00c5eddd;
      lVar3 = lVar5 + 8;
    } while (param_1 != *(CDataGroup **)((long)plVar2 + lVar5));
  }
  *(uint *)(this + 0x40) = uVar1 - 1;
  *(long *)((long)plVar2 + lVar5) = plVar2[uVar1 - 1];
                    /* WARNING: Could not recover jumptable at 0x00c5ee0d. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)param_1 + 8))(param_1);
  return;
}

/* address=00c5ee20
   symbol=CDataGroup::GetGroupName */

/* CDataGroup::GetGroupName() */

undefined8 * __thiscall CDataGroup::GetGroupName(CDataGroup *this)

{
  uint uVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  long lVar5;

  lVar2 = *(long *)(this + 0x18);
  if (lVar2 == 0) {
    return &::EMPTY_WSTRING;
  }
  uVar1 = *(uint *)(this + 0x10);
  if ((uVar1 != 0xffffffff) && (*(long *)(lVar2 + 0x30) != 0)) {
    lVar5 = *(long *)(lVar2 + 0x18);
    lVar4 = lVar2 + 0x10;
    while (lVar3 = lVar5, lVar3 != 0) {
      if (*(uint *)(lVar3 + 0x20) < uVar1) {
        lVar5 = *(long *)(lVar3 + 0x18);
      }
      else {
        lVar5 = *(long *)(lVar3 + 0x10);
        lVar4 = lVar3;
      }
    }
    if ((lVar2 + 0x10 != lVar4) && (*(uint *)(lVar4 + 0x20) <= uVar1)) {
      return (undefined8 *)(lVar4 + 0x28);
    }
  }
  return (undefined8 *)(lVar2 + 0x98);
}

/* address=00c5ee90
   symbol=CDataGroup::setDirty */

/* CDataGroup::setDirty(bool) */

void __thiscall CDataGroup::setDirty(CDataGroup *this,bool param_1)

{
  undefined8 *puVar1;
  uint uVar2;

  this[0x58] = (CDataGroup)param_1;
  if (*(int *)(this + 0x40) != 0) {
    uVar2 = 0;
    do {
      if (uVar2 < *(uint *)(this + 0x44)) {
        puVar1 = (undefined8 *)((ulong)uVar2 * 8 + *(long *)(this + 0x38));
      }
      else {
        puVar1 = *(undefined8 **)(this + 0x38);
      }
      uVar2 = uVar2 + 1;
      setDirty((CDataGroup *)*puVar1,param_1);
    } while (uVar2 < *(uint *)(this + 0x40));
  }
  return;
}

/* address=00c5eef0
   symbol=CDataGroup::SaveToFile */

/* CDataGroup::SaveToFile(std::wstring const&, iDataFileSaveAndLoad*) */

undefined4 __thiscall
CDataGroup::SaveToFile(CDataGroup *this,wstring_conflict *param_1,iDataFileSaveAndLoad *param_2)

{
  undefined4 uVar1;

  uVar1 = (**(code **)(*(long *)param_2 + 0x10))(param_2,param_1,this);
  setDirty(this,false);
  return uVar1;
}

/* address=00c5ef30
   symbol=CDataGroup::isDirty */

/* CDataGroup::isDirty() */

undefined8 __thiscall CDataGroup::isDirty(CDataGroup *this)

{
  char cVar1;
  uint uVar2;

  if (this[0x58] != (CDataGroup)0x0) {
    return 1;
  }
  if (*(int *)(this + 0x40) != 0) {
    uVar2 = 0;
    do {
      if (uVar2 < *(uint *)(this + 0x44)) {
        cVar1 = isDirty(*(CDataGroup **)((ulong)uVar2 * 8 + *(long *)(this + 0x38)));
      }
      else {
        cVar1 = isDirty((CDataGroup *)**(undefined8 **)(this + 0x38));
      }
      if (cVar1 != '\0') {
        return 1;
      }
      uVar2 = uVar2 + 1;
    } while (uVar2 < *(uint *)(this + 0x40));
  }
  return 0;
}

/* address=00c5efa0
   symbol=CDataGroup::getStringRepositorySizeInMemory */

/* CDataGroup::getStringRepositorySizeInMemory() */

int CDataGroup::getStringRepositorySizeInMemory(void)

{
  _Rb_tree_node_base *p_Var1;
  int iVar2;

  iVar2 = 0;
  p_Var1 = (_Rb_tree_node_base *)g_GlobalRepository._80_8_;
  if (g_GlobalRepository._80_8_ != 0x14dda20) {
    do {
      iVar2 = iVar2 + (int)*(undefined8 *)(*(long *)(p_Var1 + 0x20) + -0x18) * 4;
      p_Var1 = (_Rb_tree_node_base *)std::_Rb_tree_increment(p_Var1);
    } while (p_Var1 != (_Rb_tree_node_base *)(g_GlobalRepository + 0x40));
  }
  return iVar2;
}

/* address=00c5efe0
   symbol=CDataGroup::CopyDataValue */

/* CDataGroup::CopyDataValue(CDataValue*, TArrayList<CDataValue*>*) */

CDataValue * __thiscall
CDataGroup::CopyDataValue(CDataGroup *this,CDataValue *param_1,TArrayList *param_2)

{
  size_t __n;
  int iVar1;
  undefined8 *puVar2;
  undefined8 *puVar3;
  CDataValue *pCVar4;
  void *pvVar5;
  ulong uVar6;
  uint uVar7;
  uint uVar8;

  if ((param_2 == (TArrayList *)0x0) || (param_1 == (CDataValue *)0x0)) {
    pCVar4 = (CDataValue *)0x0;
  }
  else {
    this[0x58] = (CDataGroup)0x1;
    if (*(int *)(param_2 + 8) != 0) {
      uVar7 = 0;
      do {
        puVar2 = (undefined8 *)CDataValue::GetDataValueName(param_1);
        if (uVar7 < *(uint *)(param_2 + 0xc)) {
          puVar3 = (undefined8 *)((ulong)uVar7 * 8 + *(long *)param_2);
        }
        else {
          puVar3 = *(undefined8 **)param_2;
        }
        puVar3 = (undefined8 *)CDataValue::GetDataValueName((CDataValue *)*puVar3);
        __n = *(size_t *)((wchar_t *)*puVar3 + -6);
        if ((__n == *(size_t *)((wchar_t *)*puVar2 + -6)) &&
           (iVar1 = wmemcmp((wchar_t *)*puVar3,(wchar_t *)*puVar2,__n), iVar1 == 0)) {
          if (uVar7 < *(uint *)(param_2 + 0xc)) {
            puVar2 = (undefined8 *)((ulong)uVar7 * 8 + *(long *)param_2);
          }
          else {
            puVar2 = *(undefined8 **)param_2;
          }
          pCVar4 = (CDataValue *)*puVar2;
          if (uVar7 < *(uint *)(param_2 + 8)) {
            uVar8 = *(uint *)(param_2 + 8) - 1;
            *(uint *)(param_2 + 8) = uVar8;
            *(undefined8 *)(*(long *)param_2 + (ulong)uVar7 * 8) =
                 *(undefined8 *)(*(long *)param_2 + (ulong)uVar8 * 8);
          }
          if (pCVar4 != (CDataValue *)0x0) {
            CDataValue::Copy(pCVar4,param_1,*(TRepository **)(this + 0x18));
            return pCVar4;
          }
          break;
        }
        uVar7 = uVar7 + 1;
      } while (uVar7 < *(uint *)(param_2 + 8));
    }
    pCVar4 = (CDataValue *)Ogre::NedAllocImpl::allocBytes(0x38,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00c5f108 to 00c5f10c has its CatchHandler @ 00c5f1a2 */
    CDataValue::CDataValue(pCVar4,param_1,*(TRepository **)(this + 0x18));
    uVar7 = *(uint *)(this + 0x28);
    if (uVar7 < *(uint *)(this + 0x2c)) {
      pvVar5 = *(void **)(this + 0x20);
    }
    else if (*(long *)(this + 0x20) == 0) {
      *(uint *)(this + 0x2c) = *(uint *)(this + 0x30);
      pvVar5 = operator_new__((ulong)*(uint *)(this + 0x30) << 3);
      *(void **)(this + 0x20) = pvVar5;
      uVar7 = *(uint *)(this + 0x28);
    }
    else {
      uVar8 = *(uint *)(this + 0x2c) + *(int *)(this + 0x30);
      pvVar5 = operator_new__((ulong)uVar8 << 3);
      if (*(int *)(this + 0x2c) != 0) {
        uVar7 = 0;
        do {
          uVar6 = (ulong)uVar7;
          uVar7 = uVar7 + 1;
          *(undefined8 *)((long)pvVar5 + uVar6 * 8) =
               *(undefined8 *)(*(long *)(this + 0x20) + uVar6 * 8);
        } while (uVar7 < *(uint *)(this + 0x2c));
      }
      if (*(void **)(this + 0x20) != (void *)0x0) {
        operator_delete__(*(void **)(this + 0x20));
      }
      uVar7 = *(uint *)(this + 0x28);
      *(void **)(this + 0x20) = pvVar5;
      *(uint *)(this + 0x2c) = uVar8;
    }
    *(CDataValue **)((long)pvVar5 + (ulong)uVar7 * 8) = pCVar4;
    *(int *)(this + 0x28) = *(int *)(this + 0x28) + 1;
  }
  return pCVar4;
}

/* address=00c5f1c0
   symbol=CDataGroup::GetDataValueByName */

/* CDataGroup::GetDataValueByName(std::wstring const&) */

undefined8 __thiscall CDataGroup::GetDataValueByName(CDataGroup *this,wstring_conflict *param_1)

{
  size_t __n;
  int iVar1;
  undefined8 *puVar2;
  uint uVar3;

  if (*(int *)(this + 0x28) != 0) {
    uVar3 = 0;
    do {
      if (uVar3 < *(uint *)(this + 0x2c)) {
        puVar2 = (undefined8 *)((ulong)uVar3 * 8 + *(long *)(this + 0x20));
      }
      else {
        puVar2 = *(undefined8 **)(this + 0x20);
      }
      puVar2 = (undefined8 *)CDataValue::GetDataValueName((CDataValue *)*puVar2);
      __n = *(size_t *)((wchar_t *)*puVar2 + -6);
      if (__n == *(size_t *)(*(wchar_t **)param_1 + -6)) {
        iVar1 = wmemcmp((wchar_t *)*puVar2,*(wchar_t **)param_1,__n);
        if (iVar1 == 0) {
          if (uVar3 < *(uint *)(this + 0x2c)) {
            puVar2 = (undefined8 *)((ulong)uVar3 * 8 + *(long *)(this + 0x20));
          }
          else {
            puVar2 = *(undefined8 **)(this + 0x20);
          }
          return *puVar2;
        }
      }
      uVar3 = uVar3 + 1;
    } while (uVar3 < *(uint *)(this + 0x28));
  }
  return 0;
}

/* address=00c5f250
   symbol=CDataGroup::GetDataValue */

/* CDataGroup::GetDataValue(std::wstring const&, double) */

double __thiscall
CDataGroup::GetDataValue(CDataGroup *this,wstring_conflict *param_1,double param_2)

{
  CDataValue *this_00;
  double dVar1;

  this_00 = (CDataValue *)GetDataValueByName(this,param_1);
  if (this_00 != (CDataValue *)0x0) {
    dVar1 = (double)CDataValue::GetValueFloat64(this_00);
    return dVar1;
  }
  return param_2;
}

/* address=00c5f280
   symbol=CDataGroup::GetDataValue */

/* CDataGroup::GetDataValue(std::wstring const&, float) */

ulong __thiscall CDataGroup::GetDataValue(CDataGroup *this,wstring_conflict *param_1,float param_2)

{
  CDataValue *this_00;
  ulong uVar1;

  this_00 = (CDataValue *)GetDataValueByName(this,param_1);
  if (this_00 != (CDataValue *)0x0) {
    uVar1 = CDataValue::GetValueFloat32(this_00);
    return uVar1;
  }
  return (ulong)(uint)param_2;
}

/* address=00c5f2b0
   symbol=CDataGroup::GetDataValue */

/* CDataGroup::GetDataValue(std::wstring const&, unsigned int) */

ulong __thiscall CDataGroup::GetDataValue(CDataGroup *this,wstring_conflict *param_1,uint param_2)

{
  CDataValue *this_00;
  ulong uVar1;

  this_00 = (CDataValue *)GetDataValueByName(this,param_1);
  if (this_00 != (CDataValue *)0x0) {
    uVar1 = CDataValue::GetValueUInt32(this_00);
    return uVar1;
  }
  return (ulong)param_2;
}

/* address=00c5f2e0
   symbol=CDataGroup::GetDataValue */

/* CDataGroup::GetDataValue(std::wstring const&, long long) */

longlong __thiscall
CDataGroup::GetDataValue(CDataGroup *this,wstring_conflict *param_1,longlong param_2)

{
  CDataValue *this_00;
  longlong lVar1;

  this_00 = (CDataValue *)GetDataValueByName(this,param_1);
  if (this_00 != (CDataValue *)0x0) {
    lVar1 = CDataValue::GetValueInt64(this_00);
    return lVar1;
  }
  return param_2;
}

/* address=00c5f310
   symbol=CDataGroup::GetDataValue */

/* CDataGroup::GetDataValue(std::wstring const&, int) */

ulong __thiscall CDataGroup::GetDataValue(CDataGroup *this,wstring_conflict *param_1,int param_2)

{
  CDataValue *this_00;
  ulong uVar1;

  this_00 = (CDataValue *)GetDataValueByName(this,param_1);
  if (this_00 != (CDataValue *)0x0) {
    uVar1 = CDataValue::GetValueInt32(this_00);
    return uVar1;
  }
  return (ulong)(uint)param_2;
}

/* address=00c5f340
   symbol=CDataGroup::GetDataValue */

/* CDataGroup::GetDataValue(std::wstring const&, bool) */

ulong __thiscall CDataGroup::GetDataValue(CDataGroup *this,wstring_conflict *param_1,bool param_2)

{
  CDataValue *this_00;
  ulong uVar1;
  undefined3 in_register_00000011;

  this_00 = (CDataValue *)GetDataValueByName(this,param_1);
  if (this_00 != (CDataValue *)0x0) {
    uVar1 = CDataValue::GetValueBool(this_00);
    return uVar1;
  }
  return (ulong)CONCAT31(in_register_00000011,param_2);
}

/* address=00c5f370
   symbol=CDataGroup::GetDataValue */

/* CDataGroup::GetDataValue(std::wstring const&, std::wstring const&) */

wstring_conflict * __thiscall
CDataGroup::GetDataValue(CDataGroup *this,wstring_conflict *param_1,wstring_conflict *param_2)

{
  CDataValue *this_00;
  wstring_conflict *pwVar1;

  this_00 = (CDataValue *)GetDataValueByName(this,param_1);
  if (this_00 != (CDataValue *)0x0) {
    pwVar1 = (wstring_conflict *)CDataValue::GetValueString(this_00,true);
    return pwVar1;
  }
  return param_2;
}

/* address=00c5f3a0
   symbol=CDataGroup::GetDataValue */

/* CDataGroup::GetDataValue(std::wstring const&, wchar_t const*) */

undefined8 * __thiscall
CDataGroup::GetDataValue(CDataGroup *this,wstring_conflict *param_1,wchar_t *param_2)

{
  CDataValue *this_00;
  undefined8 *puVar1;

  this_00 = (CDataValue *)GetDataValueByName(this,param_1);
  if (this_00 != (CDataValue *)0x0) {
    puVar1 = (undefined8 *)CDataValue::GetValueString(this_00,true);
    return puVar1;
  }
  wcslen(param_2);
  std::wstring::assign((wchar_t *)&gDataGroupString,(ulong)param_2);
  return &gDataGroupString;
}

/* address=00c5f3e0
   symbol=CDataGroup::GetDataValueType */

/* CDataGroup::GetDataValueType(std::wstring const&) */

undefined4 __thiscall CDataGroup::GetDataValueType(CDataGroup *this,wstring_conflict *param_1)

{
  undefined4 uVar1;
  long lVar2;

  lVar2 = GetDataValueByName(this,param_1);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = *(undefined4 *)(lVar2 + 0x30);
  }
  return uVar1;
}

/* address=00c5f400
   symbol=CDataGroup::_GLOBAL__I_CDataGroup */

/* CDataGroup::CDataGroup(std::basic_string<wchar_t, std::char_traits<wchar_t>,
   std::allocator<wchar_t> > const&, CDataGroup*, unsigned int, unsigned int,
   TRepository<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > >*)
    */

void CDataGroup::_GLOBAL__I_CDataGroup(void)

{
  wstring_conflict awStack_28 [15];
  allocator local_19 [9];

  ::EMPTY_STRING = &DAT_01423a38;
  __cxa_atexit(std::string::~string,&::EMPTY_STRING,&__dso_handle);
  ::EMPTY_WSTRING = &DAT_01424558;
  __cxa_atexit(std::wstring::~wstring,&::EMPTY_WSTRING,&__dso_handle);
  std::ios_base::Init::Init((Init *)&std::__ioinit);
  __cxa_atexit(std::ios_base::Init::~Init,&std::__ioinit,&__dso_handle);
                    /* try { // try from 00c5f471 to 00c5f475 has its CatchHandler @ 00c5f573 */
  std::wstring::wstring((wstring_conflict *)&gDataGroupString,L"",local_19);
  __cxa_atexit(std::wstring::~wstring,&gDataGroupString,&__dso_handle);
  std::wstring::wstring(awStack_28,(wstring_conflict *)&::EMPTY_WSTRING);
  g_GlobalRepository._0_4_ = 0;
  g_GlobalRepository._48_8_ = 0;
  g_GlobalRepository._16_4_ = 0;
  g_GlobalRepository._24_8_ = 0;
  g_GlobalRepository._32_8_ = 0x14dd9f0;
  g_GlobalRepository._40_8_ = 0x14dd9f0;
  g_GlobalRepository._96_8_ = 0;
  g_GlobalRepository._64_4_ = 0;
  g_GlobalRepository._72_8_ = 0;
  g_GlobalRepository._80_8_ = 0x14dda20;
  g_GlobalRepository._88_8_ = 0x14dda20;
  g_GlobalRepository._144_8_ = 0;
  g_GlobalRepository._112_4_ = 0;
  g_GlobalRepository._120_8_ = 0;
  g_GlobalRepository._128_8_ = 0x14dda50;
  g_GlobalRepository._136_8_ = 0x14dda50;
                    /* try { // try from 00c5f54b to 00c5f54f has its CatchHandler @ 00c5f57b */
  std::wstring::wstring((wstring_conflict *)(g_GlobalRepository + 0x98),awStack_28);
  std::wstring::~wstring(awStack_28);
  __cxa_atexit(TRepository<std::wstring>::~TRepository,g_GlobalRepository,&__dso_handle);
  return;
}

/* address=00c5f5e0
   symbol=CDataGroup::SetGroupNameID */

/* WARNING: Removing unreachable block (ram,0x00c5f80f) */
/* WARNING: Removing unreachable block (ram,0x00c5f7ff) */
/* CDataGroup::SetGroupNameID(unsigned int) */

void __thiscall CDataGroup::SetGroupNameID(CDataGroup *this,uint param_1)

{
  allocator *paVar1;
  wchar_t *pwVar2;
  long lVar3;
  wchar_t wVar4;
  long lVar5;
  long lVar6;
  long lVar7;
  long lVar8;
  int iVar9;
  long lVar10;
  wstring_conflict *pwVar11;
  uint local_48;
  undefined2 local_44;
  wchar_t *local_38 [2];

  if (*(long *)(this + 0x18) == 0) {
    return;
  }
  *(uint *)(this + 0x10) = param_1;
  lVar5 = *(long *)(this + 0x18);
  if ((param_1 != 0xffffffff) && (*(long *)(lVar5 + 0x30) != 0)) {
    lVar6 = *(long *)(lVar5 + 0x18);
    lVar3 = lVar5 + 0x10;
    while (lVar8 = lVar6, lVar8 != 0) {
      if (*(uint *)(lVar8 + 0x20) < param_1) {
        lVar6 = *(long *)(lVar8 + 0x18);
      }
      else {
        lVar6 = *(long *)(lVar8 + 0x10);
        lVar3 = lVar8;
      }
    }
    if ((lVar5 + 0x10 != lVar3) && (*(uint *)(lVar3 + 0x20) <= param_1)) {
      pwVar11 = (wstring_conflict *)(lVar3 + 0x28);
      goto LAB_00c5f619;
    }
  }
  pwVar11 = (wstring_conflict *)(lVar5 + 0x98);
LAB_00c5f619:
  std::wstring::wstring((wstring_conflict *)local_38,pwVar11);
  pwVar2 = local_38[0];
  paVar1 = (allocator *)(local_38[0] + -6);
  if ((*(size_t *)(local_38[0] + -6) == *(size_t *)(*(wchar_t **)(lVar5 + 0x98) + -6)) &&
     (iVar9 = wmemcmp(local_38[0],*(wchar_t **)(lVar5 + 0x98),*(size_t *)(local_38[0] + -6)),
     iVar9 == 0)) {
    if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      pwVar2 = pwVar2 + -2;
      wVar4 = *pwVar2;
      *pwVar2 = *pwVar2 + L'\xffffffff';
      UNLOCK();
      if (wVar4 < L'\x01') {
        std::wstring::_Rep::_M_destroy(paVar1);
      }
    }
  }
  else {
    lVar6 = *(long *)(lVar5 + 0x78);
    lVar3 = lVar5 + 0x70;
    lVar10 = lVar6;
    lVar8 = lVar3;
    while (lVar7 = lVar10, lVar7 != 0) {
      if (*(uint *)(lVar7 + 0x20) < param_1) {
        lVar10 = *(long *)(lVar7 + 0x18);
      }
      else {
        lVar10 = *(long *)(lVar7 + 0x10);
        lVar8 = lVar7;
      }
    }
    lVar10 = lVar3;
    if ((lVar3 == lVar8) || (param_1 < *(uint *)(lVar8 + 0x20))) {
      while (lVar8 = lVar6, lVar8 != 0) {
        if (*(uint *)(lVar8 + 0x20) < param_1) {
          lVar6 = *(long *)(lVar8 + 0x18);
        }
        else {
          lVar6 = *(long *)(lVar8 + 0x10);
          lVar10 = lVar8;
        }
      }
      if ((lVar3 == lVar10) || (param_1 < *(uint *)(lVar10 + 0x20))) {
        local_44 = 0;
        local_48 = param_1;
                    /* try { // try from 00c5f6bf to 00c5f6c3 has its CatchHandler @ 00c5f7ec */
        lVar10 = std::
                 _Rb_tree<unsigned_int,std::pair<unsigned_int_const,unsigned_short>,std::_Select1st<std::pair<unsigned_int_const,unsigned_short>>,std::less<unsigned_int>,std::allocator<std::pair<unsigned_int_const,unsigned_short>>>
                 ::_M_insert_unique_((_Rb_tree<unsigned_int,std::pair<unsigned_int_const,unsigned_short>,std::_Select1st<std::pair<unsigned_int_const,unsigned_short>>,std::less<unsigned_int>,std::allocator<std::pair<unsigned_int_const,unsigned_short>>>
                                      *)(lVar5 + 0x68),lVar10,&local_48);
      }
      *(undefined2 *)(lVar10 + 0x24) = 1;
    }
    else {
      *(short *)(lVar8 + 0x24) = *(short *)(lVar8 + 0x24) + 1;
    }
    if ((allocator *)(local_38[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      pwVar2 = local_38[0] + -2;
      wVar4 = *pwVar2;
      *pwVar2 = *pwVar2 + L'\xffffffff';
      UNLOCK();
      if (wVar4 < L'\x01') {
        std::wstring::_Rep::_M_destroy((allocator *)(local_38[0] + -6));
      }
    }
  }
  return;
}

/* address=00c5f820
   symbol=CDataGroup::GetDataValuesMatchingName */

/* CDataGroup::GetDataValuesMatchingName(std::wstring const&, std::vector<CDataValue*,
   std::allocator<CDataValue*> >*) */

ulong __thiscall
CDataGroup::GetDataValuesMatchingName(CDataGroup *this,wstring_conflict *param_1,vector *param_2)

{
  size_t __n;
  int iVar1;
  undefined8 *puVar2;
  long lVar3;
  ulong uVar4;
  undefined8 *puVar5;
  uint uVar6;

  uVar4 = 0;
  if (param_2 != (vector *)0x0) {
    if (*(int *)(this + 0x28) != 0) {
      uVar6 = 0;
      do {
        while( true ) {
          if (uVar6 < *(uint *)(this + 0x2c)) {
            puVar2 = (undefined8 *)((ulong)uVar6 * 8 + *(long *)(this + 0x20));
          }
          else {
            puVar2 = *(undefined8 **)(this + 0x20);
          }
          puVar2 = (undefined8 *)CDataValue::GetDataValueName((CDataValue *)*puVar2);
          __n = *(size_t *)((wchar_t *)*puVar2 + -6);
          if (__n == *(size_t *)(*(wchar_t **)param_1 + -6)) break;
LAB_00c5f86d:
          uVar6 = uVar6 + 1;
          if (*(uint *)(this + 0x28) <= uVar6) goto LAB_00c5f8d7;
        }
        iVar1 = wmemcmp((wchar_t *)*puVar2,*(wchar_t **)param_1,__n);
        if (iVar1 != 0) goto LAB_00c5f86d;
        if (uVar6 < *(uint *)(this + 0x2c)) {
          puVar2 = *(undefined8 **)(param_2 + 8);
          puVar5 = (undefined8 *)((ulong)uVar6 * 8 + *(long *)(this + 0x20));
          if (puVar2 == *(undefined8 **)(param_2 + 0x10)) {
LAB_00c5f900:
            std::vector<CDataValue*,std::allocator<CDataValue*>>::_M_insert_aux
                      ((vector<CDataValue*,std::allocator<CDataValue*>> *)param_2);
            goto LAB_00c5f86d;
          }
        }
        else {
          puVar2 = *(undefined8 **)(param_2 + 8);
          puVar5 = *(undefined8 **)(this + 0x20);
          if (puVar2 == *(undefined8 **)(param_2 + 0x10)) goto LAB_00c5f900;
        }
        lVar3 = 0;
        if (puVar2 != (undefined8 *)0x0) {
          *puVar2 = *puVar5;
          lVar3 = *(long *)(param_2 + 8);
        }
        uVar6 = uVar6 + 1;
        *(long *)(param_2 + 8) = lVar3 + 8;
      } while (uVar6 < *(uint *)(this + 0x28));
    }
LAB_00c5f8d7:
    uVar4 = (ulong)(*(long *)(param_2 + 8) - *(long *)param_2) >> 3;
  }
  return uVar4;
}

/* address=00c5f910
   symbol=CDataGroup::GetDataGroupsMatchingName */

/* CDataGroup::GetDataGroupsMatchingName(std::wstring const&, std::vector<CDataGroup*,
   std::allocator<CDataGroup*> >*) */

ulong __thiscall
CDataGroup::GetDataGroupsMatchingName(CDataGroup *this,wstring_conflict *param_1,vector *param_2)

{
  size_t __n;
  int iVar1;
  undefined8 *puVar2;
  long lVar3;
  ulong uVar4;
  undefined8 *puVar5;
  uint uVar6;

  uVar4 = 0;
  if (param_2 != (vector *)0x0) {
    if (*(int *)(this + 0x40) != 0) {
      uVar6 = 0;
      do {
        while( true ) {
          if (uVar6 < *(uint *)(this + 0x44)) {
            puVar2 = (undefined8 *)((ulong)uVar6 * 8 + *(long *)(this + 0x38));
          }
          else {
            puVar2 = *(undefined8 **)(this + 0x38);
          }
          puVar2 = (undefined8 *)GetGroupName((CDataGroup *)*puVar2);
          __n = *(size_t *)((wchar_t *)*puVar2 + -6);
          if (__n == *(size_t *)(*(wchar_t **)param_1 + -6)) break;
LAB_00c5f95d:
          uVar6 = uVar6 + 1;
          if (*(uint *)(this + 0x40) <= uVar6) goto LAB_00c5f9c7;
        }
        iVar1 = wmemcmp((wchar_t *)*puVar2,*(wchar_t **)param_1,__n);
        if (iVar1 != 0) goto LAB_00c5f95d;
        if (uVar6 < *(uint *)(this + 0x44)) {
          puVar2 = *(undefined8 **)(param_2 + 8);
          puVar5 = (undefined8 *)((ulong)uVar6 * 8 + *(long *)(this + 0x38));
          if (puVar2 == *(undefined8 **)(param_2 + 0x10)) {
LAB_00c5f9f0:
            std::vector<CDataGroup*,std::allocator<CDataGroup*>>::_M_insert_aux
                      ((vector<CDataGroup*,std::allocator<CDataGroup*>> *)param_2);
            goto LAB_00c5f95d;
          }
        }
        else {
          puVar2 = *(undefined8 **)(param_2 + 8);
          puVar5 = *(undefined8 **)(this + 0x38);
          if (puVar2 == *(undefined8 **)(param_2 + 0x10)) goto LAB_00c5f9f0;
        }
        lVar3 = 0;
        if (puVar2 != (undefined8 *)0x0) {
          *puVar2 = *puVar5;
          lVar3 = *(long *)(param_2 + 8);
        }
        uVar6 = uVar6 + 1;
        *(long *)(param_2 + 8) = lVar3 + 8;
      } while (uVar6 < *(uint *)(this + 0x40));
    }
LAB_00c5f9c7:
    uVar4 = (ulong)(*(long *)(param_2 + 8) - *(long *)param_2) >> 3;
  }
  return uVar4;
}

/* address=00c5fa00
   symbol=CDataGroup::AddDataValue */

/* CDataGroup::AddDataValue(unsigned int, UNIONDATA64BIT, CDataValue::EDATAVALUETYPES) */

CDataValue * __thiscall
CDataGroup::AddDataValue(CDataGroup *this,undefined4 param_1,undefined8 param_3,undefined4 param_4)

{
  uint uVar1;
  CDataValue *pCVar2;
  void *pvVar3;
  ulong uVar4;
  uint uVar5;

  this[0x58] = (CDataGroup)0x1;
  pCVar2 = (CDataValue *)Ogre::NedAllocImpl::allocBytes(0x38,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00c5fa50 to 00c5fa54 has its CatchHandler @ 00c5fb1d */
  CDataValue::CDataValue(pCVar2,param_1,param_3,param_4,*(undefined8 *)(this + 0x18));
  uVar1 = *(uint *)(this + 0x28);
  if (uVar1 < *(uint *)(this + 0x2c)) {
    pvVar3 = *(void **)(this + 0x20);
  }
  else if (*(long *)(this + 0x20) == 0) {
    *(uint *)(this + 0x2c) = *(uint *)(this + 0x30);
    pvVar3 = operator_new__((ulong)*(uint *)(this + 0x30) << 3);
    *(void **)(this + 0x20) = pvVar3;
    uVar1 = *(uint *)(this + 0x28);
  }
  else {
    uVar5 = *(uint *)(this + 0x2c) + *(int *)(this + 0x30);
    pvVar3 = operator_new__((ulong)uVar5 << 3);
    if (*(int *)(this + 0x2c) != 0) {
      uVar1 = 0;
      do {
        uVar4 = (ulong)uVar1;
        uVar1 = uVar1 + 1;
        *(undefined8 *)((long)pvVar3 + uVar4 * 8) =
             *(undefined8 *)(*(long *)(this + 0x20) + uVar4 * 8);
      } while (uVar1 < *(uint *)(this + 0x2c));
    }
    if (*(void **)(this + 0x20) != (void *)0x0) {
      operator_delete__(*(void **)(this + 0x20));
    }
    uVar1 = *(uint *)(this + 0x28);
    *(void **)(this + 0x20) = pvVar3;
    *(uint *)(this + 0x2c) = uVar5;
  }
  *(CDataValue **)((long)pvVar3 + (ulong)uVar1 * 8) = pCVar2;
  *(int *)(this + 0x28) = *(int *)(this + 0x28) + 1;
  return pCVar2;
}

/* address=00c5fb30
   symbol=CDataGroup::AddDataValue */

/* CDataGroup::AddDataValue(std::wstring const&, std::wstring const&, bool) */

CDataValue * __thiscall
CDataGroup::AddDataValue
          (CDataGroup *this,wstring_conflict *param_1,wstring_conflict *param_2,bool param_3)

{
  wchar_t *pwVar1;
  uint uVar2;
  CDataValue *this_00;
  void *pvVar3;
  ulong uVar4;
  uint uVar5;

  this[0x58] = (CDataGroup)0x1;
  pwVar1 = *(wchar_t **)param_1;
  this_00 = (CDataValue *)Ogre::NedAllocImpl::allocBytes(0x38,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00c5fb7f to 00c5fb83 has its CatchHandler @ 00c5fc6d */
  CDataValue::CDataValue(this_00,pwVar1,*(TRepository **)(this + 0x18));
  CDataValue::SetValueString(this_00,*(wchar_t **)param_2);
  uVar2 = *(uint *)(this + 0x28);
  if (uVar2 < *(uint *)(this + 0x2c)) {
    pvVar3 = *(void **)(this + 0x20);
  }
  else if (*(long *)(this + 0x20) == 0) {
    *(uint *)(this + 0x2c) = *(uint *)(this + 0x30);
    pvVar3 = operator_new__((ulong)*(uint *)(this + 0x30) << 3);
    *(void **)(this + 0x20) = pvVar3;
    uVar2 = *(uint *)(this + 0x28);
  }
  else {
    uVar5 = *(uint *)(this + 0x2c) + *(int *)(this + 0x30);
    pvVar3 = operator_new__((ulong)uVar5 << 3);
    if (*(int *)(this + 0x2c) != 0) {
      uVar2 = 0;
      do {
        uVar4 = (ulong)uVar2;
        uVar2 = uVar2 + 1;
        *(undefined8 *)((long)pvVar3 + uVar4 * 8) =
             *(undefined8 *)(*(long *)(this + 0x20) + uVar4 * 8);
      } while (uVar2 < *(uint *)(this + 0x2c));
    }
    if (*(void **)(this + 0x20) != (void *)0x0) {
      operator_delete__(*(void **)(this + 0x20));
    }
    uVar2 = *(uint *)(this + 0x28);
    *(void **)(this + 0x20) = pvVar3;
    *(uint *)(this + 0x2c) = uVar5;
  }
  *(CDataValue **)((long)pvVar3 + (ulong)uVar2 * 8) = this_00;
  *(int *)(this + 0x28) = *(int *)(this + 0x28) + 1;
  if (param_3) {
    CDataValue::SetValueIsTranslate(this_00);
  }
  return this_00;
}

/* address=00c5fc80
   symbol=CDataGroup::AddDataValue */

/* WARNING: Removing unreachable block (ram,0x00c5fd3e) */
/* CDataGroup::AddDataValue(std::wstring const&, wchar_t const*, bool) */

undefined8 __thiscall
CDataGroup::AddDataValue(CDataGroup *this,wstring_conflict *param_1,wchar_t *param_2,bool param_3)

{
  int *piVar1;
  int iVar2;
  undefined8 uVar3;
  long local_38;
  allocator local_29 [9];

  this[0x58] = (CDataGroup)0x1;
                    /* try { // try from 00c5fcb5 to 00c5fcb9 has its CatchHandler @ 00c5fd36 */
  std::wstring::wstring((wstring_conflict *)&local_38,param_2,local_29);
                    /* try { // try from 00c5fcc7 to 00c5fccb has its CatchHandler @ 00c5fd23 */
  uVar3 = AddDataValue(this,param_1,(wstring_conflict *)&local_38,param_3);
  if ((allocator *)(local_38 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_38 + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_38 + -0x18));
    }
  }
  return uVar3;
}

/* address=00c5fd50
   symbol=CDataGroup::SetDataValue */

/* CDataGroup::SetDataValue(std::wstring const&, wchar_t const*, bool) */

undefined8 __thiscall
CDataGroup::SetDataValue(CDataGroup *this,wstring_conflict *param_1,wchar_t *param_2,bool param_3)

{
  CDataValue *this_00;
  undefined8 uVar1;

  this_00 = (CDataValue *)GetDataValueByName(this,param_1);
  if (this_00 == (CDataValue *)0x0) {
    AddDataValue(this,param_1,param_2,param_3);
    uVar1 = 1;
  }
  else {
    CDataValue::SetValueString(this_00,param_2);
    uVar1 = 0;
    if (param_3) {
      CDataValue::SetValueIsTranslate(this_00);
      uVar1 = 0;
    }
  }
  return uVar1;
}

/* address=00c5fde0
   symbol=CDataGroup::SetDataValue */

/* CDataGroup::SetDataValue(std::wstring const&, std::wstring const&, bool) */

undefined8 __thiscall
CDataGroup::SetDataValue
          (CDataGroup *this,wstring_conflict *param_1,wstring_conflict *param_2,bool param_3)

{
  CDataValue *this_00;
  undefined8 uVar1;

  this_00 = (CDataValue *)GetDataValueByName(this,param_1);
  if (this_00 == (CDataValue *)0x0) {
    AddDataValue(this,param_1,param_2,param_3);
    uVar1 = 1;
  }
  else {
    CDataValue::SetValueString(this_00,*(wchar_t **)param_2);
    uVar1 = 0;
    if (param_3) {
      CDataValue::SetValueIsTranslate(this_00);
      uVar1 = 0;
    }
  }
  return uVar1;
}

/* address=00c5fe70
   symbol=CDataGroup::AddDataValue */

/* CDataGroup::AddDataValue(std::wstring const&, bool) */

CDataValue * __thiscall
CDataGroup::AddDataValue(CDataGroup *this,wstring_conflict *param_1,bool param_2)

{
  wchar_t *pwVar1;
  uint uVar2;
  CDataValue *this_00;
  void *pvVar3;
  ulong uVar4;
  uint uVar5;

  this[0x58] = (CDataGroup)0x1;
  pwVar1 = *(wchar_t **)param_1;
  this_00 = (CDataValue *)Ogre::NedAllocImpl::allocBytes(0x38,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00c5fea2 to 00c5fea6 has its CatchHandler @ 00c5ff6d */
  CDataValue::CDataValue(this_00,pwVar1,*(TRepository **)(this + 0x18));
  CDataValue::SetValueBool(this_00,param_2);
  uVar2 = *(uint *)(this + 0x28);
  if (uVar2 < *(uint *)(this + 0x2c)) {
    pvVar3 = *(void **)(this + 0x20);
  }
  else if (*(long *)(this + 0x20) == 0) {
    *(uint *)(this + 0x2c) = *(uint *)(this + 0x30);
    pvVar3 = operator_new__((ulong)*(uint *)(this + 0x30) << 3);
    *(void **)(this + 0x20) = pvVar3;
    uVar2 = *(uint *)(this + 0x28);
  }
  else {
    uVar5 = *(uint *)(this + 0x2c) + *(int *)(this + 0x30);
    pvVar3 = operator_new__((ulong)uVar5 << 3);
    if (*(int *)(this + 0x2c) != 0) {
      uVar2 = 0;
      do {
        uVar4 = (ulong)uVar2;
        uVar2 = uVar2 + 1;
        *(undefined8 *)((long)pvVar3 + uVar4 * 8) =
             *(undefined8 *)(*(long *)(this + 0x20) + uVar4 * 8);
      } while (uVar2 < *(uint *)(this + 0x2c));
    }
    if (*(void **)(this + 0x20) != (void *)0x0) {
      operator_delete__(*(void **)(this + 0x20));
    }
    uVar2 = *(uint *)(this + 0x28);
    *(void **)(this + 0x20) = pvVar3;
    *(uint *)(this + 0x2c) = uVar5;
  }
  *(CDataValue **)((long)pvVar3 + (ulong)uVar2 * 8) = this_00;
  *(int *)(this + 0x28) = *(int *)(this + 0x28) + 1;
  return this_00;
}

/* address=00c5ff80
   symbol=CDataGroup::SetDataValue */

/* CDataGroup::SetDataValue(std::wstring const&, bool) */

bool __thiscall CDataGroup::SetDataValue(CDataGroup *this,wstring_conflict *param_1,bool param_2)

{
  CDataValue *this_00;

  this_00 = (CDataValue *)GetDataValueByName(this,param_1);
  if (this_00 == (CDataValue *)0x0) {
    AddDataValue(this,param_1,param_2);
  }
  else {
    CDataValue::SetValueBool(this_00,param_2);
  }
  return this_00 == (CDataValue *)0x0;
}

/* address=00c5fff0
   symbol=CDataGroup::AddDataValue */

/* CDataGroup::AddDataValue(std::wstring const&, long long) */

CDataValue * __thiscall
CDataGroup::AddDataValue(CDataGroup *this,wstring_conflict *param_1,longlong param_2)

{
  wchar_t *pwVar1;
  uint uVar2;
  CDataValue *this_00;
  void *pvVar3;
  ulong uVar4;
  uint uVar5;

  this[0x58] = (CDataGroup)0x1;
  pwVar1 = *(wchar_t **)param_1;
  this_00 = (CDataValue *)Ogre::NedAllocImpl::allocBytes(0x38,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00c60022 to 00c60026 has its CatchHandler @ 00c600dd */
  CDataValue::CDataValue(this_00,pwVar1,*(TRepository **)(this + 0x18));
  CDataValue::SetValueInt64(this_00,param_2);
  uVar2 = *(uint *)(this + 0x28);
  if (uVar2 < *(uint *)(this + 0x2c)) {
    pvVar3 = *(void **)(this + 0x20);
  }
  else if (*(long *)(this + 0x20) == 0) {
    *(uint *)(this + 0x2c) = *(uint *)(this + 0x30);
    pvVar3 = operator_new__((ulong)*(uint *)(this + 0x30) << 3);
    *(void **)(this + 0x20) = pvVar3;
    uVar2 = *(uint *)(this + 0x28);
  }
  else {
    uVar5 = *(uint *)(this + 0x2c) + *(int *)(this + 0x30);
    pvVar3 = operator_new__((ulong)uVar5 << 3);
    if (*(int *)(this + 0x2c) != 0) {
      uVar2 = 0;
      do {
        uVar4 = (ulong)uVar2;
        uVar2 = uVar2 + 1;
        *(undefined8 *)((long)pvVar3 + uVar4 * 8) =
             *(undefined8 *)(*(long *)(this + 0x20) + uVar4 * 8);
      } while (uVar2 < *(uint *)(this + 0x2c));
    }
    if (*(void **)(this + 0x20) != (void *)0x0) {
      operator_delete__(*(void **)(this + 0x20));
    }
    uVar2 = *(uint *)(this + 0x28);
    *(void **)(this + 0x20) = pvVar3;
    *(uint *)(this + 0x2c) = uVar5;
  }
  *(CDataValue **)((long)pvVar3 + (ulong)uVar2 * 8) = this_00;
  *(int *)(this + 0x28) = *(int *)(this + 0x28) + 1;
  return this_00;
}

/* address=00c600f0
   symbol=CDataGroup::SetDataValue */

/* CDataGroup::SetDataValue(std::wstring const&, long long) */

bool __thiscall
CDataGroup::SetDataValue(CDataGroup *this,wstring_conflict *param_1,longlong param_2)

{
  CDataValue *this_00;

  this_00 = (CDataValue *)GetDataValueByName(this,param_1);
  if (this_00 == (CDataValue *)0x0) {
    AddDataValue(this,param_1,param_2);
  }
  else {
    CDataValue::SetValueInt64(this_00,param_2);
  }
  return this_00 == (CDataValue *)0x0;
}

/* address=00c60160
   symbol=CDataGroup::AddDataValue */

/* CDataGroup::AddDataValue(std::wstring const&, int) */

CDataValue * __thiscall
CDataGroup::AddDataValue(CDataGroup *this,wstring_conflict *param_1,int param_2)

{
  wchar_t *pwVar1;
  uint uVar2;
  CDataValue *this_00;
  void *pvVar3;
  ulong uVar4;
  uint uVar5;

  this[0x58] = (CDataGroup)0x1;
  pwVar1 = *(wchar_t **)param_1;
  this_00 = (CDataValue *)Ogre::NedAllocImpl::allocBytes(0x38,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00c60192 to 00c60196 has its CatchHandler @ 00c6024d */
  CDataValue::CDataValue(this_00,pwVar1,*(TRepository **)(this + 0x18));
  CDataValue::SetValueInt32(this_00,param_2);
  uVar2 = *(uint *)(this + 0x28);
  if (uVar2 < *(uint *)(this + 0x2c)) {
    pvVar3 = *(void **)(this + 0x20);
  }
  else if (*(long *)(this + 0x20) == 0) {
    *(uint *)(this + 0x2c) = *(uint *)(this + 0x30);
    pvVar3 = operator_new__((ulong)*(uint *)(this + 0x30) << 3);
    *(void **)(this + 0x20) = pvVar3;
    uVar2 = *(uint *)(this + 0x28);
  }
  else {
    uVar5 = *(uint *)(this + 0x2c) + *(int *)(this + 0x30);
    pvVar3 = operator_new__((ulong)uVar5 << 3);
    if (*(int *)(this + 0x2c) != 0) {
      uVar2 = 0;
      do {
        uVar4 = (ulong)uVar2;
        uVar2 = uVar2 + 1;
        *(undefined8 *)((long)pvVar3 + uVar4 * 8) =
             *(undefined8 *)(*(long *)(this + 0x20) + uVar4 * 8);
      } while (uVar2 < *(uint *)(this + 0x2c));
    }
    if (*(void **)(this + 0x20) != (void *)0x0) {
      operator_delete__(*(void **)(this + 0x20));
    }
    uVar2 = *(uint *)(this + 0x28);
    *(void **)(this + 0x20) = pvVar3;
    *(uint *)(this + 0x2c) = uVar5;
  }
  *(CDataValue **)((long)pvVar3 + (ulong)uVar2 * 8) = this_00;
  *(int *)(this + 0x28) = *(int *)(this + 0x28) + 1;
  return this_00;
}

/* address=00c60260
   symbol=CDataGroup::SetDataValue */

/* CDataGroup::SetDataValue(std::wstring const&, int) */

bool __thiscall CDataGroup::SetDataValue(CDataGroup *this,wstring_conflict *param_1,int param_2)

{
  CDataValue *this_00;

  this_00 = (CDataValue *)GetDataValueByName(this,param_1);
  if (this_00 == (CDataValue *)0x0) {
    AddDataValue(this,param_1,param_2);
  }
  else {
    CDataValue::SetValueInt32(this_00,param_2);
  }
  return this_00 == (CDataValue *)0x0;
}

/* address=00c602d0
   symbol=CDataGroup::AddDataValue */

/* CDataGroup::AddDataValue(std::wstring const&, std::wstring, std::wstring) */

CDataValue * __thiscall
CDataGroup::AddDataValue
          (CDataGroup *this,undefined8 *param_1,wstring_conflict *param_3,wstring_conflict *param_4)

{
  wchar_t *pwVar1;
  uint uVar2;
  CDataValue *this_00;
  void *pvVar3;
  ulong uVar4;
  uint uVar5;

  this[0x58] = (CDataGroup)0x1;
  pwVar1 = (wchar_t *)*param_1;
  this_00 = (CDataValue *)Ogre::NedAllocImpl::allocBytes(0x38,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00c60305 to 00c60309 has its CatchHandler @ 00c603cd */
  CDataValue::CDataValue(this_00,pwVar1,*(TRepository **)(this + 0x18));
  CDataValue::SetValueByString(this_00,param_3,param_4);
  uVar2 = *(uint *)(this + 0x28);
  if (uVar2 < *(uint *)(this + 0x2c)) {
    pvVar3 = *(void **)(this + 0x20);
  }
  else if (*(long *)(this + 0x20) == 0) {
    *(uint *)(this + 0x2c) = *(uint *)(this + 0x30);
    pvVar3 = operator_new__((ulong)*(uint *)(this + 0x30) << 3);
    *(void **)(this + 0x20) = pvVar3;
    uVar2 = *(uint *)(this + 0x28);
  }
  else {
    uVar5 = *(uint *)(this + 0x2c) + *(int *)(this + 0x30);
    pvVar3 = operator_new__((ulong)uVar5 << 3);
    if (*(int *)(this + 0x2c) != 0) {
      uVar2 = 0;
      do {
        uVar4 = (ulong)uVar2;
        uVar2 = uVar2 + 1;
        *(undefined8 *)((long)pvVar3 + uVar4 * 8) =
             *(undefined8 *)(*(long *)(this + 0x20) + uVar4 * 8);
      } while (uVar2 < *(uint *)(this + 0x2c));
    }
    if (*(void **)(this + 0x20) != (void *)0x0) {
      operator_delete__(*(void **)(this + 0x20));
    }
    uVar2 = *(uint *)(this + 0x28);
    *(void **)(this + 0x20) = pvVar3;
    *(uint *)(this + 0x2c) = uVar5;
  }
  *(CDataValue **)((long)pvVar3 + (ulong)uVar2 * 8) = this_00;
  *(int *)(this + 0x28) = *(int *)(this + 0x28) + 1;
  return this_00;
}

/* address=00c603e0
   symbol=CDataGroup::AddDataValue */

/* CDataGroup::AddDataValue(std::wstring const&, double) */

CDataValue * __thiscall
CDataGroup::AddDataValue(CDataGroup *this,wstring_conflict *param_1,double param_2)

{
  wchar_t *pwVar1;
  uint uVar2;
  CDataValue *this_00;
  void *pvVar3;
  ulong uVar4;
  uint uVar5;

  this[0x58] = (CDataGroup)0x1;
  pwVar1 = *(wchar_t **)param_1;
  this_00 = (CDataValue *)Ogre::NedAllocImpl::allocBytes(0x38,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00c60419 to 00c6041d has its CatchHandler @ 00c604dd */
  CDataValue::CDataValue(this_00,pwVar1,*(TRepository **)(this + 0x18));
  CDataValue::SetValueFloat64(this_00,param_2);
  uVar2 = *(uint *)(this + 0x28);
  if (uVar2 < *(uint *)(this + 0x2c)) {
    pvVar3 = *(void **)(this + 0x20);
  }
  else if (*(long *)(this + 0x20) == 0) {
    *(uint *)(this + 0x2c) = *(uint *)(this + 0x30);
    pvVar3 = operator_new__((ulong)*(uint *)(this + 0x30) << 3);
    *(void **)(this + 0x20) = pvVar3;
    uVar2 = *(uint *)(this + 0x28);
  }
  else {
    uVar5 = *(uint *)(this + 0x2c) + *(int *)(this + 0x30);
    pvVar3 = operator_new__((ulong)uVar5 << 3);
    if (*(int *)(this + 0x2c) != 0) {
      uVar2 = 0;
      do {
        uVar4 = (ulong)uVar2;
        uVar2 = uVar2 + 1;
        *(undefined8 *)((long)pvVar3 + uVar4 * 8) =
             *(undefined8 *)(*(long *)(this + 0x20) + uVar4 * 8);
      } while (uVar2 < *(uint *)(this + 0x2c));
    }
    if (*(void **)(this + 0x20) != (void *)0x0) {
      operator_delete__(*(void **)(this + 0x20));
    }
    uVar2 = *(uint *)(this + 0x28);
    *(void **)(this + 0x20) = pvVar3;
    *(uint *)(this + 0x2c) = uVar5;
  }
  *(CDataValue **)((long)pvVar3 + (ulong)uVar2 * 8) = this_00;
  *(int *)(this + 0x28) = *(int *)(this + 0x28) + 1;
  return this_00;
}

/* address=00c604f0
   symbol=CDataGroup::SetDataValue */

/* CDataGroup::SetDataValue(std::wstring const&, double) */

undefined8 __thiscall
CDataGroup::SetDataValue(CDataGroup *this,wstring_conflict *param_1,double param_2)

{
  CDataValue *this_00;

  this_00 = (CDataValue *)GetDataValueByName(this,param_1);
  if (this_00 != (CDataValue *)0x0) {
    CDataValue::SetValueFloat64(this_00,param_2);
    return 0;
  }
  AddDataValue(this,param_1,param_2);
  return 1;
}

/* address=00c60560
   symbol=CDataGroup::AddDataValue */

/* CDataGroup::AddDataValue(std::wstring const&, float) */

CDataValue * __thiscall
CDataGroup::AddDataValue(CDataGroup *this,wstring_conflict *param_1,float param_2)

{
  wchar_t *pwVar1;
  uint uVar2;
  CDataValue *this_00;
  void *pvVar3;
  ulong uVar4;
  uint uVar5;

  this[0x58] = (CDataGroup)0x1;
  pwVar1 = *(wchar_t **)param_1;
  this_00 = (CDataValue *)Ogre::NedAllocImpl::allocBytes(0x38,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00c60599 to 00c6059d has its CatchHandler @ 00c6065d */
  CDataValue::CDataValue(this_00,pwVar1,*(TRepository **)(this + 0x18));
  CDataValue::SetValueFloat32(this_00,param_2);
  uVar2 = *(uint *)(this + 0x28);
  if (uVar2 < *(uint *)(this + 0x2c)) {
    pvVar3 = *(void **)(this + 0x20);
  }
  else if (*(long *)(this + 0x20) == 0) {
    *(uint *)(this + 0x2c) = *(uint *)(this + 0x30);
    pvVar3 = operator_new__((ulong)*(uint *)(this + 0x30) << 3);
    *(void **)(this + 0x20) = pvVar3;
    uVar2 = *(uint *)(this + 0x28);
  }
  else {
    uVar5 = *(uint *)(this + 0x2c) + *(int *)(this + 0x30);
    pvVar3 = operator_new__((ulong)uVar5 << 3);
    if (*(int *)(this + 0x2c) != 0) {
      uVar2 = 0;
      do {
        uVar4 = (ulong)uVar2;
        uVar2 = uVar2 + 1;
        *(undefined8 *)((long)pvVar3 + uVar4 * 8) =
             *(undefined8 *)(*(long *)(this + 0x20) + uVar4 * 8);
      } while (uVar2 < *(uint *)(this + 0x2c));
    }
    if (*(void **)(this + 0x20) != (void *)0x0) {
      operator_delete__(*(void **)(this + 0x20));
    }
    uVar2 = *(uint *)(this + 0x28);
    *(void **)(this + 0x20) = pvVar3;
    *(uint *)(this + 0x2c) = uVar5;
  }
  *(CDataValue **)((long)pvVar3 + (ulong)uVar2 * 8) = this_00;
  *(int *)(this + 0x28) = *(int *)(this + 0x28) + 1;
  return this_00;
}

/* address=00c60670
   symbol=CDataGroup::SetDataValue */

/* CDataGroup::SetDataValue(std::wstring const&, float) */

undefined8 __thiscall
CDataGroup::SetDataValue(CDataGroup *this,wstring_conflict *param_1,float param_2)

{
  CDataValue *this_00;

  this_00 = (CDataValue *)GetDataValueByName(this,param_1);
  if (this_00 != (CDataValue *)0x0) {
    CDataValue::SetValueFloat32(this_00,param_2);
    return 0;
  }
  AddDataValue(this,param_1,param_2);
  return 1;
}

/* address=00c606e0
   symbol=CDataGroup::AddDataValue */

/* CDataGroup::AddDataValue(std::wstring const&, unsigned int) */

CDataValue * __thiscall
CDataGroup::AddDataValue(CDataGroup *this,wstring_conflict *param_1,uint param_2)

{
  wchar_t *pwVar1;
  uint uVar2;
  CDataValue *this_00;
  void *pvVar3;
  ulong uVar4;
  uint uVar5;

  this[0x58] = (CDataGroup)0x1;
  pwVar1 = *(wchar_t **)param_1;
  this_00 = (CDataValue *)Ogre::NedAllocImpl::allocBytes(0x38,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00c60712 to 00c60716 has its CatchHandler @ 00c607dd */
  CDataValue::CDataValue(this_00,pwVar1,*(TRepository **)(this + 0x18));
  CDataValue::SetValueUInt32(this_00,param_2);
  uVar2 = *(uint *)(this + 0x28);
  if (uVar2 < *(uint *)(this + 0x2c)) {
    pvVar3 = *(void **)(this + 0x20);
  }
  else if (*(long *)(this + 0x20) == 0) {
    *(uint *)(this + 0x2c) = *(uint *)(this + 0x30);
    pvVar3 = operator_new__((ulong)*(uint *)(this + 0x30) << 3);
    *(void **)(this + 0x20) = pvVar3;
    uVar2 = *(uint *)(this + 0x28);
  }
  else {
    uVar5 = *(uint *)(this + 0x2c) + *(int *)(this + 0x30);
    pvVar3 = operator_new__((ulong)uVar5 << 3);
    if (*(int *)(this + 0x2c) != 0) {
      uVar2 = 0;
      do {
        uVar4 = (ulong)uVar2;
        uVar2 = uVar2 + 1;
        *(undefined8 *)((long)pvVar3 + uVar4 * 8) =
             *(undefined8 *)(*(long *)(this + 0x20) + uVar4 * 8);
      } while (uVar2 < *(uint *)(this + 0x2c));
    }
    if (*(void **)(this + 0x20) != (void *)0x0) {
      operator_delete__(*(void **)(this + 0x20));
    }
    uVar2 = *(uint *)(this + 0x28);
    *(void **)(this + 0x20) = pvVar3;
    *(uint *)(this + 0x2c) = uVar5;
  }
  *(CDataValue **)((long)pvVar3 + (ulong)uVar2 * 8) = this_00;
  *(int *)(this + 0x28) = *(int *)(this + 0x28) + 1;
  return this_00;
}

/* address=00c607f0
   symbol=CDataGroup::SetDataValue */

/* CDataGroup::SetDataValue(std::wstring const&, unsigned int) */

bool __thiscall CDataGroup::SetDataValue(CDataGroup *this,wstring_conflict *param_1,uint param_2)

{
  CDataValue *this_00;

  this_00 = (CDataValue *)GetDataValueByName(this,param_1);
  if (this_00 == (CDataValue *)0x0) {
    AddDataValue(this,param_1,param_2);
  }
  else {
    CDataValue::SetValueUInt32(this_00,param_2);
  }
  return this_00 == (CDataValue *)0x0;
}

/* address=00c60860
   symbol=CDataGroup::SaveToFile */

/* WARNING: Removing unreachable block (ram,0x00c60aa0) */
/* WARNING: Removing unreachable block (ram,0x00c60a84) */
/* WARNING: Removing unreachable block (ram,0x00c60a74) */
/* WARNING: Removing unreachable block (ram,0x00c60a92) */
/* CDataGroup::SaveToFile(std::wstring const&) */

undefined4 __thiscall CDataGroup::SaveToFile(CDataGroup *this,wstring_conflict *param_1)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  CFileSystem *this_00;
  undefined1 *local_68;
  long local_60;
  long local_58;
  undefined4 local_50;
  undefined4 local_4c;
  undefined1 *local_48;
  char local_40;
  CPairStyle local_38 [24];

  CPairStyle::CPairStyle(local_38);
  local_68 = &DAT_01423a38;
                    /* try { // try from 00c608a0 to 00c608a4 has its CatchHandler @ 00c60a7f */
  std::string::string((string *)&local_60,(string *)&::EMPTY_STRING);
                    /* try { // try from 00c608af to 00c608b3 has its CatchHandler @ 00c60a5e */
  std::wstring::wstring((wstring_conflict *)&local_58,(wstring_conflict *)&::EMPTY_WSTRING);
  local_50 = 4;
  local_4c = 3;
  local_48 = &DAT_01423a38;
  local_40 = '\0';
                    /* try { // try from 00c608d2 to 00c60907 has its CatchHandler @ 00c60a43 */
  this_00 = (CFileSystem *)CFileSystem::getSingleton();
  CFileSystem::getFileInfo(this_00,param_1,(CFileInfo *)&local_68,false,false,false);
  if (local_40 == '\0') {
                    /* try { // try from 00c60989 to 00c6098d has its CatchHandler @ 00c60a43 */
    uVar3 = SaveToFile(this,param_1,(iDataFileSaveAndLoad *)local_38);
  }
  else {
    uVar3 = SaveToFile(this,(wstring_conflict *)&local_58,(iDataFileSaveAndLoad *)local_38);
  }
  if ((allocator *)(local_48 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_48 + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_48 + -0x18));
    }
  }
  if ((allocator *)(local_58 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_58 + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_58 + -0x18));
    }
  }
  if ((allocator *)(local_60 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_60 + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_60 + -0x18));
    }
  }
  if ((allocator *)(local_68 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_68 + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_68 + -0x18));
    }
  }
  CPairStyle::~CPairStyle(local_38);
  return uVar3;
}

/* address=00c60ab0
   symbol=CDataGroup::SetGroupName */

/* WARNING: Removing unreachable block (ram,0x00c61440) */
/* WARNING: Removing unreachable block (ram,0x00c6144d) */
/* WARNING: Removing unreachable block (ram,0x00c613bc) */
/* WARNING: Removing unreachable block (ram,0x00c614c0) */
/* WARNING: Removing unreachable block (ram,0x00c614cb) */
/* WARNING: Removing unreachable block (ram,0x00c6135f) */
/* CDataGroup::SetGroupName(std::wstring const&) */

void __thiscall CDataGroup::SetGroupName(CDataGroup *this,wstring_conflict *param_1)

{
  _Rb_tree_node_base *p_Var1;
  allocator *paVar2;
  int *piVar3;
  wchar_t wVar4;
  short sVar5;
  uint uVar6;
  size_t __n;
  ulong uVar7;
  ulong uVar8;
  uint *puVar9;
  uint *puVar10;
  uint *puVar11;
  _Rb_tree_node_base *p_Var12;
  _Rb_tree_node_base *p_Var13;
  int iVar14;
  uint *puVar15;
  uint *puVar16;
  void *pvVar17;
  size_t sVar18;
  ulong uVar19;
  wstring_conflict *pwVar20;
  uint uVar21;
  _Rb_tree_node_base *p_Var22;
  uint *puVar23;
  wchar_t *pwVar24;
  allocator *paVar25;
  _Rb_tree_node_base *p_Var26;
  long lVar27;
  uint *local_d0;
  _Rb_tree_node_base *local_c8;
  uint *local_b8;
  uint *local_b0;
  wstring_conflict local_a8 [8];
  undefined4 local_a0;
  uint local_98 [2];
  long local_90;
  wchar_t *local_88 [2];
  uint local_78;
  undefined2 local_74;
  uint local_68;
  undefined2 local_64;
  undefined4 *local_58 [2];
  wchar_t *local_48 [3];

  if (*(long *)(this + 0x18) == 0) {
    return;
  }
  std::wstring::wstring((wstring_conflict *)local_48,param_1);
  while (pwVar24 = local_48[0], *local_48[0] == L'/') {
    pwVar24 = local_48[0] + 1;
    wcslen(pwVar24);
                    /* try { // try from 00c60afd to 00c60c50 has its CatchHandler @ 00c6135a */
    std::wstring::assign((wchar_t *)local_48,(ulong)pwVar24);
  }
  __n = *(size_t *)(local_48[0] + -6);
  puVar23 = *(uint **)(this + 0x18);
  uVar6 = *(uint *)(this + 0x10);
  if (__n == *(size_t *)(*(wchar_t **)(puVar23 + 0x26) + -6)) {
    uVar21 = 0xffffffff;
    iVar14 = wmemcmp(local_48[0],*(wchar_t **)(puVar23 + 0x26),__n);
    if (iVar14 != 0) {
      lVar27 = *(long *)(puVar23 + 0x18);
      goto joined_r0x00c60f1e;
    }
  }
  else {
    lVar27 = *(long *)(puVar23 + 0x18);
joined_r0x00c60f1e:
    if (lVar27 == 0) {
      local_c8 = *(_Rb_tree_node_base **)(puVar23 + 0x12);
    }
    else {
      local_c8 = *(_Rb_tree_node_base **)(puVar23 + 0x12);
      puVar15 = puVar23 + 0x10;
      puVar9 = (uint *)local_c8;
      while (puVar9 != (uint *)0x0) {
        uVar7 = *(ulong *)(*(wchar_t **)(puVar9 + 8) + -6);
        sVar18 = __n;
        if (uVar7 <= __n) {
          sVar18 = uVar7;
        }
        iVar14 = wmemcmp(*(wchar_t **)(puVar9 + 8),pwVar24,sVar18);
        if (iVar14 == 0) {
          lVar27 = uVar7 - __n;
          if (0x7fffffff < lVar27) goto LAB_00c60f56;
          if (-0x80000001 < lVar27) {
            iVar14 = (int)lVar27;
            goto LAB_00c60f52;
          }
LAB_00c60fa4:
          puVar9 = *(uint **)(puVar9 + 6);
        }
        else {
LAB_00c60f52:
          if (iVar14 < 0) goto LAB_00c60fa4;
LAB_00c60f56:
          puVar15 = puVar9;
          puVar9 = *(uint **)(puVar9 + 4);
        }
      }
      local_b0 = puVar23 + 0x10;
      if (local_b0 != puVar15) {
        uVar7 = *(ulong *)(*(wchar_t **)(puVar15 + 8) + -6);
        sVar18 = __n;
        if (uVar7 <= __n) {
          sVar18 = uVar7;
        }
        iVar14 = wmemcmp(pwVar24,*(wchar_t **)(puVar15 + 8),sVar18);
        if (iVar14 == 0) {
          lVar27 = __n - uVar7;
          if (lVar27 < 0x80000000) {
            if (lVar27 < -0x80000000) goto LAB_00c60b4e;
            iVar14 = (int)lVar27;
            goto LAB_00c612aa;
          }
        }
        else {
LAB_00c612aa:
          if (iVar14 < 0) goto LAB_00c60b4e;
        }
        uVar21 = puVar15[10];
        if (uVar21 != 0xffffffff) {
          puVar15 = *(uint **)(puVar23 + 0x1e);
          puVar9 = puVar23 + 0x1c;
          puVar16 = puVar15;
          puVar11 = puVar9;
          while (puVar10 = puVar16, puVar10 != (uint *)0x0) {
            if (puVar10[8] < uVar21) {
              puVar16 = *(uint **)(puVar10 + 6);
            }
            else {
              puVar16 = *(uint **)(puVar10 + 4);
              puVar11 = puVar10;
            }
          }
          puVar16 = puVar9;
          if ((puVar9 == puVar11) || (uVar21 < puVar11[8])) {
            while (puVar11 = puVar15, puVar11 != (uint *)0x0) {
              if (puVar11[8] < uVar21) {
                puVar15 = *(uint **)(puVar11 + 6);
              }
              else {
                puVar15 = *(uint **)(puVar11 + 4);
                puVar16 = puVar11;
              }
            }
            if ((puVar9 == puVar16) || (uVar21 < puVar16[8])) {
              local_64 = 0;
              local_68 = uVar21;
                    /* try { // try from 00c612f8 to 00c612fc has its CatchHandler @ 00c6135a */
              puVar16 = (uint *)std::
                                _Rb_tree<unsigned_int,std::pair<unsigned_int_const,unsigned_short>,std::_Select1st<std::pair<unsigned_int_const,unsigned_short>>,std::less<unsigned_int>,std::allocator<std::pair<unsigned_int_const,unsigned_short>>>
                                ::_M_insert_unique_((
                                                  _Rb_tree<unsigned_int,std::pair<unsigned_int_const,unsigned_short>,std::_Select1st<std::pair<unsigned_int_const,unsigned_short>>,std::less<unsigned_int>,std::allocator<std::pair<unsigned_int_const,unsigned_short>>>
                                                  *)(puVar23 + 0x1a),puVar16,&local_68);
            }
            *(undefined2 *)(puVar16 + 9) = 1;
            puVar23 = *(uint **)(this + 0x18);
          }
          else {
            *(short *)(puVar11 + 9) = (short)puVar11[9] + 1;
            puVar23 = *(uint **)(this + 0x18);
          }
          goto LAB_00c60dd0;
        }
      }
    }
LAB_00c60b4e:
    pwVar24 = local_48[0];
    local_b0 = puVar23 + 0x10;
    uVar21 = *puVar23;
    *puVar23 = uVar21 + 1;
    local_b8 = local_b0;
    if (local_c8 != (_Rb_tree_node_base *)0x0) {
      uVar7 = *(ulong *)(local_48[0] + -6);
      do {
        uVar8 = *(ulong *)(*(wchar_t **)((long)local_c8 + 0x20) + -6);
        uVar19 = uVar7;
        if (uVar8 < uVar7) {
          uVar19 = uVar8;
        }
        iVar14 = wmemcmp(*(wchar_t **)((long)local_c8 + 0x20),pwVar24,uVar19);
        if (iVar14 == 0) {
          lVar27 = uVar8 - uVar7;
          if (0x7fffffff < lVar27) goto LAB_00c60b97;
          if (-0x80000001 < lVar27) {
            iVar14 = (int)lVar27;
            goto LAB_00c60b93;
          }
LAB_00c60be3:
          puVar9 = *(uint **)((long)local_c8 + 0x18);
        }
        else {
LAB_00c60b93:
          if (iVar14 < 0) goto LAB_00c60be3;
LAB_00c60b97:
          puVar9 = *(uint **)((long)local_c8 + 0x10);
          local_b8 = (uint *)local_c8;
        }
        local_c8 = (_Rb_tree_node_base *)puVar9;
      } while (local_c8 != (_Rb_tree_node_base *)0x0);
    }
    local_d0 = local_b8;
    if (local_b0 == local_b8) {
LAB_00c60c41:
      std::wstring::wstring(local_a8,(wstring_conflict *)local_48);
      local_a0 = 0;
                    /* try { // try from 00c60c65 to 00c60c69 has its CatchHandler @ 00c613cc */
      local_d0 = (uint *)std::
                         _Rb_tree<std::wstring,std::pair<std::wstring_const,unsigned_int>,std::_Select1st<std::pair<std::wstring_const,unsigned_int>>,std::less<std::wstring>,std::allocator<std::pair<std::wstring_const,unsigned_int>>>
                         ::_M_insert_unique_((_Rb_tree<std::wstring,std::pair<std::wstring_const,unsigned_int>,std::_Select1st<std::pair<std::wstring_const,unsigned_int>>,std::less<std::wstring>,std::allocator<std::pair<std::wstring_const,unsigned_int>>>
                                              *)(puVar23 + 0xe),local_b8,local_a8);
                    /* try { // try from 00c60c72 to 00c60c76 has its CatchHandler @ 00c6135a */
      std::wstring::~wstring(local_a8);
    }
    else {
      uVar7 = *(ulong *)(local_48[0] + -6);
      uVar8 = *(ulong *)(*(wchar_t **)(local_b8 + 8) + -6);
      uVar19 = uVar7;
      if (uVar8 <= uVar7) {
        uVar19 = uVar8;
      }
      iVar14 = wmemcmp(local_48[0],*(wchar_t **)(local_b8 + 8),uVar19);
      if (iVar14 == 0) {
        lVar27 = uVar7 - uVar8;
        if (lVar27 < 0x80000000) {
          if (lVar27 < -0x80000000) goto LAB_00c60c41;
          iVar14 = (int)lVar27;
          goto LAB_00c6128d;
        }
      }
      else {
LAB_00c6128d:
        if (iVar14 < 0) goto LAB_00c60c41;
      }
    }
    local_d0[10] = uVar21;
    puVar15 = puVar23 + 4;
    puVar9 = *(uint **)(puVar23 + 6);
    while (puVar9 != (uint *)0x0) {
      if (puVar9[8] < uVar21) {
        puVar9 = *(uint **)(puVar9 + 6);
      }
      else {
        puVar15 = puVar9;
        puVar9 = *(uint **)(puVar9 + 4);
      }
    }
    if ((puVar23 + 4 == puVar15) || (uVar21 < puVar15[8])) {
      local_58[0] = &DAT_01424558;
      local_98[0] = uVar21;
                    /* try { // try from 00c60ce6 to 00c60cea has its CatchHandler @ 00c613c7 */
      std::wstring::wstring((wstring_conflict *)&local_90,(wstring_conflict *)local_58);
                    /* try { // try from 00c60cf5 to 00c60cf9 has its CatchHandler @ 00c6139e */
      puVar15 = (uint *)std::
                        _Rb_tree<unsigned_int,std::pair<unsigned_int_const,std::wstring>,std::_Select1st<std::pair<unsigned_int_const,std::wstring>>,std::less<unsigned_int>,std::allocator<std::pair<unsigned_int_const,std::wstring>>>
                        ::_M_insert_unique_((_Rb_tree<unsigned_int,std::pair<unsigned_int_const,std::wstring>,std::_Select1st<std::pair<unsigned_int_const,std::wstring>>,std::less<unsigned_int>,std::allocator<std::pair<unsigned_int_const,std::wstring>>>
                                             *)(puVar23 + 2),puVar15,local_98);
      if ((allocator *)(local_90 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
      {
        LOCK();
        piVar3 = (int *)(local_90 + -8);
        iVar14 = *piVar3;
        *piVar3 = *piVar3 + -1;
        UNLOCK();
        if (iVar14 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_90 + -0x18));
        }
      }
      if ((allocator *)(local_58[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
      {
        LOCK();
        piVar3 = local_58[0] + -2;
        iVar14 = *piVar3;
        *piVar3 = *piVar3 + -1;
        UNLOCK();
        if (iVar14 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -6));
        }
      }
    }
                    /* try { // try from 00c60d31 to 00c60e3b has its CatchHandler @ 00c6135a */
    std::wstring::assign((wstring_conflict *)(puVar15 + 10));
    puVar15 = *(uint **)(puVar23 + 0x1e);
    puVar9 = puVar23 + 0x1c;
    puVar16 = puVar15;
    puVar11 = puVar9;
    while (puVar10 = puVar16, puVar10 != (uint *)0x0) {
      if (puVar10[8] < uVar21) {
        puVar16 = *(uint **)(puVar10 + 6);
      }
      else {
        puVar16 = *(uint **)(puVar10 + 4);
        puVar11 = puVar10;
      }
    }
    puVar16 = puVar9;
    if ((puVar9 == puVar11) || (uVar21 < puVar11[8])) {
      while (puVar11 = puVar15, puVar11 != (uint *)0x0) {
        if (puVar11[8] < uVar21) {
          puVar15 = *(uint **)(puVar11 + 6);
        }
        else {
          puVar15 = *(uint **)(puVar11 + 4);
          puVar16 = puVar11;
        }
      }
      if ((puVar9 == puVar16) || (uVar21 < puVar16[8])) {
        local_74 = 0;
        local_78 = uVar21;
        puVar16 = (uint *)std::
                          _Rb_tree<unsigned_int,std::pair<unsigned_int_const,unsigned_short>,std::_Select1st<std::pair<unsigned_int_const,unsigned_short>>,std::less<unsigned_int>,std::allocator<std::pair<unsigned_int_const,unsigned_short>>>
                          ::_M_insert_unique_((_Rb_tree<unsigned_int,std::pair<unsigned_int_const,unsigned_short>,std::_Select1st<std::pair<unsigned_int_const,unsigned_short>>,std::less<unsigned_int>,std::allocator<std::pair<unsigned_int_const,unsigned_short>>>
                                               *)(puVar23 + 0x1a),puVar16,&local_78);
      }
      *(undefined2 *)(puVar16 + 9) = 1;
      puVar23 = *(uint **)(this + 0x18);
    }
    else {
      *(short *)(puVar11 + 9) = (short)puVar11[9] + 1;
      puVar23 = *(uint **)(this + 0x18);
    }
  }
LAB_00c60dd0:
  *(uint *)(this + 0x10) = uVar21;
  if ((uVar6 == 0xffffffff) || (*(long *)(puVar23 + 0xc) == 0)) {
LAB_00c60e2b:
    pwVar20 = (wstring_conflict *)(puVar23 + 0x26);
  }
  else {
    puVar15 = *(uint **)(puVar23 + 6);
    puVar9 = puVar23 + 4;
    while (puVar11 = puVar15, puVar11 != (uint *)0x0) {
      if (puVar11[8] < uVar6) {
        puVar15 = *(uint **)(puVar11 + 6);
      }
      else {
        puVar15 = *(uint **)(puVar11 + 4);
        puVar9 = puVar11;
      }
    }
    if ((puVar23 + 4 == puVar9) || (uVar6 < puVar9[8])) goto LAB_00c60e2b;
    pwVar20 = (wstring_conflict *)(puVar9 + 10);
  }
  std::wstring::wstring((wstring_conflict *)local_88,pwVar20);
  paVar25 = (allocator *)(local_88[0] + -6);
  if ((*(size_t *)(local_88[0] + -6) == *(size_t *)(*(wchar_t **)(puVar23 + 0x26) + -6)) &&
     (iVar14 = wmemcmp(local_88[0],*(wchar_t **)(puVar23 + 0x26),*(size_t *)(local_88[0] + -6)),
     iVar14 == 0)) goto LAB_00c60eba;
  p_Var1 = (_Rb_tree_node_base *)(puVar23 + 0x1c);
  p_Var26 = *(_Rb_tree_node_base **)(puVar23 + 0x1e);
  p_Var22 = p_Var1;
  while (p_Var13 = p_Var26, p_Var13 != (_Rb_tree_node_base *)0x0) {
    if (*(uint *)(p_Var13 + 0x20) < uVar6) {
      p_Var26 = *(_Rb_tree_node_base **)(p_Var13 + 0x18);
    }
    else {
      p_Var26 = *(_Rb_tree_node_base **)(p_Var13 + 0x10);
      p_Var22 = p_Var13;
    }
  }
  if ((p_Var1 == p_Var22) || (uVar6 < *(uint *)(p_Var22 + 0x20))) goto LAB_00c60eba;
  sVar5 = *(short *)(p_Var22 + 0x24);
  *(short *)(p_Var22 + 0x24) = sVar5 + -1;
  if ((short)(sVar5 + -1) == 0) {
                    /* try { // try from 00c6107f to 00c611fa has its CatchHandler @ 00c61311 */
    pvVar17 = (void *)std::_Rb_tree_rebalance_for_erase(p_Var22,p_Var1);
    operator_delete(pvVar17);
    pwVar24 = local_88[0];
    p_Var1 = (_Rb_tree_node_base *)(puVar23 + 0x10);
    *(long *)(puVar23 + 0x24) = *(long *)(puVar23 + 0x24) + -1;
    p_Var22 = *(_Rb_tree_node_base **)(puVar23 + 0x12);
    local_c8 = p_Var1;
    if (p_Var22 != (_Rb_tree_node_base *)0x0) {
      uVar7 = *(ulong *)(local_88[0] + -6);
      do {
        uVar8 = *(ulong *)(*(wchar_t **)(p_Var22 + 0x20) + -6);
        uVar19 = uVar7;
        if (uVar8 <= uVar7) {
          uVar19 = uVar8;
        }
        iVar14 = wmemcmp(*(wchar_t **)(p_Var22 + 0x20),pwVar24,uVar19);
        if (iVar14 == 0) {
          lVar27 = uVar8 - uVar7;
          if (0x7fffffff < lVar27) goto LAB_00c610c7;
          if (-0x80000001 < lVar27) {
            iVar14 = (int)lVar27;
            goto LAB_00c610c3;
          }
LAB_00c6110f:
          p_Var26 = *(_Rb_tree_node_base **)(p_Var22 + 0x18);
        }
        else {
LAB_00c610c3:
          if (iVar14 < 0) goto LAB_00c6110f;
LAB_00c610c7:
          p_Var26 = *(_Rb_tree_node_base **)(p_Var22 + 0x10);
          local_c8 = p_Var22;
        }
        p_Var22 = p_Var26;
      } while (p_Var22 != (_Rb_tree_node_base *)0x0);
    }
    if (p_Var1 == local_c8) {
LAB_00c61166:
      local_c8 = p_Var1;
    }
    else {
      uVar7 = *(ulong *)(local_88[0] + -6);
      uVar8 = *(ulong *)(*(wchar_t **)(local_c8 + 0x20) + -6);
      uVar19 = uVar7;
      if (uVar8 <= uVar7) {
        uVar19 = uVar8;
      }
      iVar14 = wmemcmp(local_88[0],*(wchar_t **)(local_c8 + 0x20),uVar19);
      if (iVar14 == 0) {
        lVar27 = uVar7 - uVar8;
        if (lVar27 < 0x80000000) {
          if (lVar27 < -0x80000000) goto LAB_00c61166;
          iVar14 = (int)lVar27;
          goto LAB_00c61162;
        }
      }
      else {
LAB_00c61162:
        if (iVar14 < 0) goto LAB_00c61166;
      }
    }
    p_Var22 = (_Rb_tree_node_base *)(puVar23 + 4);
    p_Var13 = *(_Rb_tree_node_base **)(puVar23 + 6);
    p_Var26 = p_Var22;
    while (p_Var12 = p_Var13, p_Var12 != (_Rb_tree_node_base *)0x0) {
      if (*(uint *)(p_Var12 + 0x20) < uVar6) {
        p_Var13 = *(_Rb_tree_node_base **)(p_Var12 + 0x18);
      }
      else {
        p_Var13 = *(_Rb_tree_node_base **)(p_Var12 + 0x10);
        p_Var26 = p_Var12;
      }
    }
    if ((p_Var22 == p_Var26) || (uVar6 < *(uint *)(p_Var26 + 0x20))) {
      p_Var26 = p_Var22;
    }
    if ((p_Var1 != local_c8) && (p_Var22 != p_Var26)) {
      pvVar17 = (void *)std::_Rb_tree_rebalance_for_erase(local_c8,p_Var1);
      paVar25 = (allocator *)(*(long *)((long)pvVar17 + 0x20) + -0x18);
      if (paVar25 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar3 = (int *)(*(long *)((long)pvVar17 + 0x20) + -8);
        iVar14 = *piVar3;
        *piVar3 = *piVar3 + -1;
        UNLOCK();
        if (iVar14 < 1) {
          std::wstring::_Rep::_M_destroy(paVar25);
        }
      }
      operator_delete(pvVar17);
      *(long *)(puVar23 + 0x18) = *(long *)(puVar23 + 0x18) + -1;
      pvVar17 = (void *)std::_Rb_tree_rebalance_for_erase(p_Var26,p_Var22);
      paVar25 = (allocator *)(*(long *)((long)pvVar17 + 0x28) + -0x18);
      if (paVar25 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar3 = (int *)(*(long *)((long)pvVar17 + 0x28) + -8);
        iVar14 = *piVar3;
        *piVar3 = *piVar3 + -1;
        UNLOCK();
        if (iVar14 < 1) {
          std::wstring::_Rep::_M_destroy(paVar25);
        }
      }
      operator_delete(pvVar17);
      *(long *)(puVar23 + 0xc) = *(long *)(puVar23 + 0xc) + -1;
      paVar25 = (allocator *)(local_88[0] + -6);
      goto LAB_00c60eba;
    }
  }
  paVar25 = (allocator *)(local_88[0] + -6);
LAB_00c60eba:
  if (paVar25 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    paVar2 = paVar25 + 0x10;
    iVar14 = *(int *)paVar2;
    *(int *)paVar2 = *(int *)paVar2 + -1;
    UNLOCK();
    if (iVar14 < 1) {
      std::wstring::_Rep::_M_destroy(paVar25);
    }
  }
  this[0x58] = (CDataGroup)((byte)this[0x58] | *(uint *)(this + 0x10) != uVar6);
  if ((allocator *)(local_48[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    pwVar24 = local_48[0] + -2;
    wVar4 = *pwVar24;
    *pwVar24 = *pwVar24 + L'\xffffffff';
    UNLOCK();
    if (wVar4 < L'\x01') {
      std::wstring::_Rep::_M_destroy((allocator *)(local_48[0] + -6));
    }
  }
  return;
}

/* address=00c614e0
   symbol=CDataGroup::LoadFile */

/* CDataGroup::LoadFile(std::wstring const&, iDataFileSaveAndLoad*, CTimerStatics*) */

void __thiscall
CDataGroup::LoadFile
          (CDataGroup *this,wstring_conflict *param_1,iDataFileSaveAndLoad *param_2,
          CTimerStatics *param_3)

{
  SetGroupName(this,(wstring_conflict *)&::EMPTY_WSTRING);
  (**(code **)(*(long *)param_2 + 0x18))(param_2,param_1,this,param_3);
  setDirty(this,false);
  return;
}

/* address=00c61550
   symbol=CDataGroup::~CDataGroup */

/* WARNING: Removing unreachable block (ram,0x00c61a99) */
/* WARNING: Removing unreachable block (ram,0x00c61a52) */
/* WARNING: Removing unreachable block (ram,0x00c61a89) */
/* CDataGroup::~CDataGroup() */

void __thiscall CDataGroup::~CDataGroup(CDataGroup *this)

{
  allocator *paVar1;
  int *piVar2;
  _Rb_tree_node_base *p_Var3;
  short sVar4;
  long lVar5;
  TRepository<std::wstring> *this_00;
  ulong uVar6;
  long lVar7;
  _Rb_tree_node_base *p_Var8;
  wchar_t *__s2;
  long lVar9;
  _Rb_tree_node_base *p_Var10;
  int iVar11;
  long *plVar12;
  void *pvVar13;
  _Rb_tree_node_base *p_Var14;
  ulong uVar15;
  uint uVar16;
  ulong uVar17;
  wstring_conflict *pwVar18;
  _Rb_tree_node_base *p_Var19;
  allocator *paVar20;
  long lVar21;
  _Rb_tree_node_base *local_58;
  wchar_t *local_48 [3];

  *(undefined ***)this = &PTR__CDataGroup_00ff33f0;
  if (this[0x59] != (CDataGroup)0x0) goto LAB_00c616b0;
  uVar16 = *(uint *)(this + 0x10);
  if (uVar16 != 0xffffffff) {
    lVar5 = *(long *)(this + 0x18);
    if (*(long *)(lVar5 + 0x30) == 0) {
LAB_00c6158e:
      pwVar18 = (wstring_conflict *)(lVar5 + 0x98);
    }
    else {
      lVar9 = *(long *)(lVar5 + 0x18);
      lVar21 = lVar5 + 0x10;
      while (lVar7 = lVar9, lVar7 != 0) {
        if (*(uint *)(lVar7 + 0x20) < uVar16) {
          lVar9 = *(long *)(lVar7 + 0x18);
        }
        else {
          lVar9 = *(long *)(lVar7 + 0x10);
          lVar21 = lVar7;
        }
      }
      if ((lVar5 + 0x10 == lVar21) || (uVar16 < *(uint *)(lVar21 + 0x20))) goto LAB_00c6158e;
      pwVar18 = (wstring_conflict *)(lVar21 + 0x28);
    }
                    /* try { // try from 00c6159b to 00c61691 has its CatchHandler @ 00c61a4d */
    std::wstring::wstring((wstring_conflict *)local_48,pwVar18);
    paVar20 = (allocator *)(local_48[0] + -6);
    if ((*(size_t *)(local_48[0] + -6) != *(size_t *)(*(wchar_t **)(lVar5 + 0x98) + -6)) ||
       (iVar11 = wmemcmp(local_48[0],*(wchar_t **)(lVar5 + 0x98),*(size_t *)(local_48[0] + -6)),
       iVar11 != 0)) {
      p_Var3 = (_Rb_tree_node_base *)(lVar5 + 0x70);
      p_Var14 = *(_Rb_tree_node_base **)(lVar5 + 0x78);
      p_Var19 = p_Var3;
      while (p_Var10 = p_Var14, p_Var10 != (_Rb_tree_node_base *)0x0) {
        if (*(uint *)(p_Var10 + 0x20) < uVar16) {
          p_Var14 = *(_Rb_tree_node_base **)(p_Var10 + 0x18);
        }
        else {
          p_Var14 = *(_Rb_tree_node_base **)(p_Var10 + 0x10);
          p_Var19 = p_Var10;
        }
      }
      if ((p_Var3 != p_Var19) && (*(uint *)(p_Var19 + 0x20) <= uVar16)) {
        sVar4 = *(short *)(p_Var19 + 0x24);
        *(short *)(p_Var19 + 0x24) = sVar4 + -1;
        if ((short)(sVar4 + -1) == 0) {
                    /* try { // try from 00c617ef to 00c6195c has its CatchHandler @ 00c61a04 */
          pvVar13 = (void *)std::_Rb_tree_rebalance_for_erase(p_Var19,p_Var3);
          operator_delete(pvVar13);
          __s2 = local_48[0];
          p_Var3 = (_Rb_tree_node_base *)(lVar5 + 0x40);
          *(long *)(lVar5 + 0x90) = *(long *)(lVar5 + 0x90) + -1;
          local_58 = p_Var3;
          if (*(_Rb_tree_node_base **)(lVar5 + 0x48) != (_Rb_tree_node_base *)0x0) {
            uVar17 = *(ulong *)(local_48[0] + -6);
            p_Var19 = *(_Rb_tree_node_base **)(lVar5 + 0x48);
            do {
              uVar6 = *(ulong *)(*(wchar_t **)(p_Var19 + 0x20) + -6);
              uVar15 = uVar17;
              if (uVar6 <= uVar17) {
                uVar15 = uVar6;
              }
              iVar11 = wmemcmp(*(wchar_t **)(p_Var19 + 0x20),__s2,uVar15);
              if (iVar11 == 0) {
                lVar21 = uVar6 - uVar17;
                if (0x7fffffff < lVar21) goto LAB_00c61837;
                if (-0x80000001 < lVar21) {
                  iVar11 = (int)lVar21;
                  goto LAB_00c61833;
                }
LAB_00c6187d:
                p_Var14 = *(_Rb_tree_node_base **)(p_Var19 + 0x18);
              }
              else {
LAB_00c61833:
                if (iVar11 < 0) goto LAB_00c6187d;
LAB_00c61837:
                p_Var14 = *(_Rb_tree_node_base **)(p_Var19 + 0x10);
                local_58 = p_Var19;
              }
              p_Var19 = p_Var14;
            } while (p_Var14 != (_Rb_tree_node_base *)0x0);
          }
          if (p_Var3 == local_58) {
LAB_00c6198d:
            local_58 = p_Var3;
          }
          else {
            uVar17 = *(ulong *)(local_48[0] + -6);
            uVar6 = *(ulong *)(*(wchar_t **)(local_58 + 0x20) + -6);
            uVar15 = uVar17;
            if (uVar6 <= uVar17) {
              uVar15 = uVar6;
            }
            iVar11 = wmemcmp(local_48[0],*(wchar_t **)(local_58 + 0x20),uVar15);
            if (iVar11 == 0) {
              lVar21 = uVar17 - uVar6;
              if (lVar21 < 0x80000000) {
                if (lVar21 < -0x80000000) goto LAB_00c6198d;
                iVar11 = (int)lVar21;
                goto LAB_00c618d3;
              }
            }
            else {
LAB_00c618d3:
              if (iVar11 < 0) goto LAB_00c6198d;
            }
          }
          p_Var19 = (_Rb_tree_node_base *)(lVar5 + 0x10);
          p_Var10 = *(_Rb_tree_node_base **)(lVar5 + 0x18);
          p_Var14 = p_Var19;
          while (p_Var8 = p_Var10, p_Var8 != (_Rb_tree_node_base *)0x0) {
            if (*(uint *)(p_Var8 + 0x20) < uVar16) {
              p_Var10 = *(_Rb_tree_node_base **)(p_Var8 + 0x18);
            }
            else {
              p_Var10 = *(_Rb_tree_node_base **)(p_Var8 + 0x10);
              p_Var14 = p_Var8;
            }
          }
          if ((p_Var19 == p_Var14) || (uVar16 < *(uint *)(p_Var14 + 0x20))) {
            p_Var14 = p_Var19;
          }
          if ((p_Var3 != local_58) && (p_Var19 != p_Var14)) {
            pvVar13 = (void *)std::_Rb_tree_rebalance_for_erase(local_58,p_Var3);
            paVar20 = (allocator *)(*(long *)((long)pvVar13 + 0x20) + -0x18);
            if (paVar20 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar2 = (int *)(*(long *)((long)pvVar13 + 0x20) + -8);
              iVar11 = *piVar2;
              *piVar2 = *piVar2 + -1;
              UNLOCK();
              if (iVar11 < 1) {
                std::wstring::_Rep::_M_destroy(paVar20);
              }
            }
            operator_delete(pvVar13);
            *(long *)(lVar5 + 0x60) = *(long *)(lVar5 + 0x60) + -1;
            pvVar13 = (void *)std::_Rb_tree_rebalance_for_erase(p_Var14,p_Var19);
            paVar20 = (allocator *)(*(long *)((long)pvVar13 + 0x28) + -0x18);
            if (paVar20 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar2 = (int *)(*(long *)((long)pvVar13 + 0x28) + -8);
              iVar11 = *piVar2;
              *piVar2 = *piVar2 + -1;
              UNLOCK();
              if (iVar11 < 1) {
                std::wstring::_Rep::_M_destroy(paVar20);
              }
            }
            operator_delete(pvVar13);
            *(long *)(lVar5 + 0x30) = *(long *)(lVar5 + 0x30) + -1;
            paVar20 = (allocator *)(local_48[0] + -6);
            goto LAB_00c61622;
          }
        }
        paVar20 = (allocator *)(local_48[0] + -6);
      }
    }
LAB_00c61622:
    if (paVar20 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      paVar1 = paVar20 + 0x10;
      iVar11 = *(int *)paVar1;
      *(int *)paVar1 = *(int *)paVar1 + -1;
      UNLOCK();
      if (iVar11 < 1) {
        std::wstring::_Rep::_M_destroy(paVar20);
      }
    }
  }
  if (*(int *)(this + 0x40) != 0) {
    uVar17 = 0;
    do {
      if ((uint)uVar17 < *(uint *)(this + 0x44)) {
        plVar12 = (long *)(uVar17 * 8 + *(long *)(this + 0x38));
      }
      else {
        plVar12 = *(long **)(this + 0x38);
      }
      if ((long *)*plVar12 != (long *)0x0) {
        (**(code **)(*(long *)*plVar12 + 8))();
      }
      uVar16 = (uint)uVar17 + 1;
      uVar17 = (ulong)uVar16;
    } while (uVar16 < *(uint *)(this + 0x40));
  }
  if (*(int *)(this + 0x28) != 0) {
    uVar16 = 0;
    do {
      if (uVar16 < *(uint *)(this + 0x2c)) {
        plVar12 = (long *)((ulong)uVar16 * 8 + *(long *)(this + 0x20));
      }
      else {
        plVar12 = *(long **)(this + 0x20);
      }
      if ((long *)*plVar12 != (long *)0x0) {
        (**(code **)(*(long *)*plVar12 + 8))();
      }
      uVar16 = uVar16 + 1;
    } while (uVar16 < *(uint *)(this + 0x28));
  }
LAB_00c616b0:
  *(undefined4 *)(this + 0x40) = 0;
  *(undefined4 *)(this + 0x44) = 0;
  if (*(void **)(this + 0x38) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x38));
  }
  *(undefined8 *)(this + 0x38) = 0;
  *(undefined4 *)(this + 0x28) = 0;
  *(undefined4 *)(this + 0x2c) = 0;
  if (*(void **)(this + 0x20) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x20));
  }
  *(undefined8 *)(this + 0x20) = 0;
  *(undefined4 *)(this + 0x10) = 0xffffffff;
  if (((*(long *)(this + 0x50) == 0) &&
      (this_00 = *(TRepository<std::wstring> **)(this + 0x18),
      this_00 != (TRepository<std::wstring> *)g_GlobalRepository)) &&
     (this_00 != (TRepository<std::wstring> *)0x0)) {
                    /* try { // try from 00c617bd to 00c617c9 has its CatchHandler @ 00c61a4d */
    TRepository<std::wstring>::~TRepository(this_00);
    Ogre::NedAllocImpl::deallocBytes(this_00);
    *(undefined8 *)(this + 0x18) = 0;
  }
  if (*(void **)(this + 0x38) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x38));
    *(undefined8 *)(this + 0x38) = 0;
  }
  if (*(void **)(this + 0x20) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x20));
    *(undefined8 *)(this + 0x20) = 0;
  }
  CRunicCore::~CRunicCore((CRunicCore *)this);
  return;
}

/* address=00c61ab0
   symbol=CDataGroup::~CDataGroup */

/* CDataGroup::~CDataGroup() */

void __thiscall CDataGroup::~CDataGroup(CDataGroup *this)

{
  ~CDataGroup(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}

/* address=00c61ad0
   symbol=CDataGroup::CDataGroup */

/* CDataGroup::CDataGroup(std::wstring const&, CDataGroup*, unsigned int, unsigned int,
   TRepository<std::wstring >*) */

void __thiscall
CDataGroup::CDataGroup
          (CDataGroup *this,wstring_conflict *param_1,CDataGroup *param_2,uint param_3,uint param_4,
          TRepository *param_5)

{
  CRunicCore::CRunicCore((CRunicCore *)this);
  *(undefined ***)this = &PTR__CDataGroup_00ff33f0;
  *(undefined4 *)(this + 0x10) = 0xffffffff;
  *(undefined8 *)(this + 0x18) = 0;
  *(undefined8 *)(this + 0x20) = 0;
  *(undefined4 *)(this + 0x28) = 0;
  *(undefined4 *)(this + 0x2c) = 0;
  *(uint *)(this + 0x30) = param_3;
  *(undefined8 *)(this + 0x38) = 0;
  *(undefined4 *)(this + 0x40) = 0;
  *(undefined4 *)(this + 0x44) = 0;
  *(uint *)(this + 0x48) = param_4;
  *(CDataGroup **)(this + 0x50) = param_2;
  this[0x58] = (CDataGroup)0x0;
  this[0x59] = (CDataGroup)0x0;
  if (param_5 == (TRepository *)0x0) {
    if (param_2 == (CDataGroup *)0x0) {
      *(undefined1 **)(this + 0x18) = g_GlobalRepository;
    }
    else {
      *(undefined8 *)(this + 0x18) = *(undefined8 *)(param_2 + 0x18);
    }
  }
  else {
    *(TRepository **)(this + 0x18) = param_5;
  }
                    /* try { // try from 00c61b6e to 00c61b72 has its CatchHandler @ 00c61bba */
  SetGroupName(this,param_1);
  return;
}

/* address=00c61c00
   symbol=CDataGroup::AddDataGroup */

/* CDataGroup::AddDataGroup(std::wstring const&) */

CDataGroup * __thiscall CDataGroup::AddDataGroup(CDataGroup *this,wstring_conflict *param_1)

{
  uint uVar1;
  CDataGroup *this_00;
  void *pvVar2;
  ulong uVar3;
  uint uVar4;

  this[0x58] = (CDataGroup)0x1;
  this_00 = (CDataGroup *)Ogre::NedAllocImpl::allocBytes(0x60,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00c61c51 to 00c61c55 has its CatchHandler @ 00c61d1d */
  CDataGroup(this_00,param_1,this,0x14,10,(TRepository *)0x0);
  uVar1 = *(uint *)(this + 0x40);
  if (uVar1 < *(uint *)(this + 0x44)) {
    pvVar2 = *(void **)(this + 0x38);
  }
  else if (*(long *)(this + 0x38) == 0) {
    *(uint *)(this + 0x44) = *(uint *)(this + 0x48);
    pvVar2 = operator_new__((ulong)*(uint *)(this + 0x48) << 3);
    *(void **)(this + 0x38) = pvVar2;
    uVar1 = *(uint *)(this + 0x40);
  }
  else {
    uVar4 = *(uint *)(this + 0x44) + *(int *)(this + 0x48);
    pvVar2 = operator_new__((ulong)uVar4 << 3);
    if (*(int *)(this + 0x44) != 0) {
      uVar1 = 0;
      do {
        uVar3 = (ulong)uVar1;
        uVar1 = uVar1 + 1;
        *(undefined8 *)((long)pvVar2 + uVar3 * 8) =
             *(undefined8 *)(*(long *)(this + 0x38) + uVar3 * 8);
      } while (uVar1 < *(uint *)(this + 0x44));
    }
    if (*(void **)(this + 0x38) != (void *)0x0) {
      operator_delete__(*(void **)(this + 0x38));
    }
    uVar1 = *(uint *)(this + 0x40);
    *(void **)(this + 0x38) = pvVar2;
    *(uint *)(this + 0x44) = uVar4;
  }
  *(CDataGroup **)((long)pvVar2 + (ulong)uVar1 * 8) = this_00;
  *(int *)(this + 0x40) = *(int *)(this + 0x40) + 1;
  return this_00;
}

/* address=00c61d30
   symbol=CDataGroup::GetDataGroupByName */

/* CDataGroup::GetDataGroupByName(std::wstring const&, bool) */

undefined8 __thiscall
CDataGroup::GetDataGroupByName(CDataGroup *this,wstring_conflict *param_1,bool param_2)

{
  uint uVar1;
  size_t __n;
  int iVar2;
  undefined8 *puVar3;
  undefined8 uVar4;
  uint uVar5;

  uVar1 = *(uint *)(this + 0x40);
  if (uVar1 != 0) {
    uVar5 = 0;
    do {
      if (uVar1 == 0xffffffff) break;
      if (uVar5 < *(uint *)(this + 0x44)) {
        puVar3 = (undefined8 *)((ulong)uVar5 * 8 + *(long *)(this + 0x38));
      }
      else {
        puVar3 = *(undefined8 **)(this + 0x38);
      }
      puVar3 = (undefined8 *)GetGroupName((CDataGroup *)*puVar3);
      __n = *(size_t *)((wchar_t *)*puVar3 + -6);
      if ((__n == *(size_t *)(*(wchar_t **)param_1 + -6)) &&
         (iVar2 = wmemcmp((wchar_t *)*puVar3,*(wchar_t **)param_1,__n), iVar2 == 0)) {
        if (uVar5 < *(uint *)(this + 0x44)) {
          puVar3 = (undefined8 *)((ulong)uVar5 * 8 + *(long *)(this + 0x38));
        }
        else {
          puVar3 = *(undefined8 **)(this + 0x38);
        }
        return *puVar3;
      }
      uVar1 = *(uint *)(this + 0x40);
      uVar5 = uVar5 + 1;
    } while (uVar5 < uVar1);
  }
  if (param_2) {
    uVar4 = AddDataGroup(this,param_1);
    return uVar4;
  }
  return 0;
}

/* address=00c61e00
   symbol=CDataGroup::CopyDataGroup */

/* CDataGroup::CopyDataGroup(CDataGroup*, bool) */

CDataGroup * __thiscall CDataGroup::CopyDataGroup(CDataGroup *this,CDataGroup *param_1,bool param_2)

{
  int iVar1;
  void *pvVar2;
  undefined8 *puVar3;
  wstring_conflict *pwVar4;
  CDataGroup *this_00;
  ulong uVar5;
  uint uVar6;
  ulong uVar7;
  undefined8 uVar8;
  uint uVar9;
  void *local_58;
  uint local_50;
  uint local_4c;
  uint local_48;

  if (param_1 != (CDataGroup *)0x0) {
    this[0x58] = (CDataGroup)0x1;
    local_58 = (void *)0x0;
    local_50 = 0;
    local_4c = 0;
    local_48 = *(int *)(this + 0x28) + 1;
    if (*(int *)(this + 0x28) != 0) {
      uVar7 = 0;
      if (*(int *)(this + 0x2c) != 0) goto LAB_00c61f17;
LAB_00c61e70:
      uVar8 = **(undefined8 **)(this + 0x20);
      pvVar2 = local_58;
      uVar9 = local_4c;
      if (local_50 < local_4c) goto LAB_00c61ee7;
      do {
        if (local_58 == (void *)0x0) {
          local_4c = local_48;
          pvVar2 = operator_new__((ulong)local_48 << 3);
          uVar9 = local_4c;
        }
        else {
          uVar9 = local_4c + local_48;
                    /* try { // try from 00c61e96 to 00c6200d has its CatchHandler @ 00c6206c */
          pvVar2 = operator_new__((ulong)uVar9 << 3);
          if (local_4c != 0) {
            uVar6 = 0;
            do {
              uVar5 = (ulong)uVar6;
              uVar6 = uVar6 + 1;
              *(undefined8 *)((long)pvVar2 + uVar5 * 8) =
                   *(undefined8 *)((long)local_58 + uVar5 * 8);
            } while (uVar6 < local_4c);
          }
          if (local_58 != (void *)0x0) {
            operator_delete__(local_58);
          }
        }
LAB_00c61ee7:
        do {
          local_4c = uVar9;
          local_58 = pvVar2;
          uVar9 = (int)uVar7 + 1;
          uVar7 = (ulong)uVar9;
          *(undefined8 *)((long)local_58 + (ulong)local_50 * 8) = uVar8;
          local_50 = local_50 + 1;
          if (*(uint *)(this + 0x28) <= uVar9) goto LAB_00c61f77;
          if (*(uint *)(this + 0x2c) <= uVar9) goto LAB_00c61e70;
LAB_00c61f17:
          uVar8 = *(undefined8 *)(uVar7 * 8 + *(long *)(this + 0x20));
          pvVar2 = local_58;
          uVar9 = local_4c;
        } while (local_50 < local_4c);
      } while( true );
    }
LAB_00c61f77:
    uVar9 = *(uint *)(param_1 + 0x28);
    if (*(uint *)(this + 0x30) < uVar9) {
      iVar1 = uVar9 + 1;
      if (iVar1 == 0) {
        iVar1 = 1;
      }
      *(int *)(this + 0x30) = iVar1;
      uVar9 = *(uint *)(param_1 + 0x28);
    }
    if (uVar9 != 0) {
      uVar7 = 0;
      do {
        if ((uint)uVar7 < *(uint *)(param_1 + 0x2c)) {
          puVar3 = (undefined8 *)(uVar7 * 8 + *(long *)(param_1 + 0x20));
        }
        else {
          puVar3 = *(undefined8 **)(param_1 + 0x20);
        }
        CopyDataValue(this,(CDataValue *)*puVar3,(TArrayList *)&local_58);
        uVar9 = (uint)uVar7 + 1;
        uVar7 = (ulong)uVar9;
      } while (uVar9 < *(uint *)(param_1 + 0x28));
    }
    uVar9 = *(uint *)(param_1 + 0x40);
    if (*(uint *)(this + 0x48) < uVar9) {
      iVar1 = uVar9 + 1;
      if (iVar1 == 0) {
        iVar1 = 1;
      }
      *(int *)(this + 0x48) = iVar1;
      uVar9 = *(uint *)(param_1 + 0x40);
    }
    if (uVar9 != 0) {
      uVar9 = 0;
      do {
        if (uVar9 < *(uint *)(param_1 + 0x44)) {
          puVar3 = (undefined8 *)((ulong)uVar9 * 8 + *(long *)(param_1 + 0x38));
        }
        else {
          puVar3 = *(undefined8 **)(param_1 + 0x38);
        }
        pwVar4 = (wstring_conflict *)GetGroupName((CDataGroup *)*puVar3);
        this_00 = (CDataGroup *)AddDataGroup(this,pwVar4);
        if (uVar9 < *(uint *)(param_1 + 0x44)) {
          puVar3 = (undefined8 *)((ulong)uVar9 * 8 + *(long *)(param_1 + 0x38));
        }
        else {
          puVar3 = *(undefined8 **)(param_1 + 0x38);
        }
        CopyDataGroup(this_00,(CDataGroup *)*puVar3,param_2);
        uVar9 = uVar9 + 1;
      } while (uVar9 < *(uint *)(param_1 + 0x40));
    }
    if (local_58 != (void *)0x0) {
      operator_delete__(local_58);
    }
  }
  return param_1;
}

/* address=00c62090
   symbol=CDataGroup::LoadFile */

/* WARNING: Removing unreachable block (ram,0x00c625c2) */
/* WARNING: Removing unreachable block (ram,0x00c62611) */
/* WARNING: Removing unreachable block (ram,0x00c626b9) */
/* WARNING: Removing unreachable block (ram,0x00c62721) */
/* WARNING: Removing unreachable block (ram,0x00c62716) */
/* WARNING: Removing unreachable block (ram,0x00c626ae) */
/* WARNING: Removing unreachable block (ram,0x00c625cd) */
/* WARNING: Removing unreachable block (ram,0x00c62562) */
/* CDataGroup::LoadFile(std::wstring const&, CTimerStatics*) */

void __thiscall
CDataGroup::LoadFile(CDataGroup *this,wstring_conflict *param_1,CTimerStatics *param_2)

{
  int *piVar1;
  int iVar2;
  CFileSystem *pCVar3;
  long lVar4;
  void *pvVar5;
  undefined8 uVar6;
  uint uVar7;
  ulong uVar8;
  ulong uVar9;
  uint uVar10;
  uint uVar11;
  undefined1 *local_98;
  long local_90;
  long local_88;
  int local_80;
  int iStack_7c;
  undefined1 *local_78;
  char local_70;
  CPairStyle local_68 [16];
  string local_58 [31];
  allocator local_39 [9];

  local_98 = &DAT_01423a38;
                    /* try { // try from 00c620be to 00c620c2 has its CatchHandler @ 00c62657 */
  std::string::string((string *)&local_90,(string *)&::EMPTY_STRING);
                    /* try { // try from 00c620d1 to 00c620d5 has its CatchHandler @ 00c62634 */
  std::wstring::wstring((wstring_conflict *)&local_88,(wstring_conflict *)&::EMPTY_WSTRING);
  local_80 = 4;
  iStack_7c = 3;
  local_78 = &DAT_01423a38;
  local_70 = '\0';
                    /* try { // try from 00c620f4 to 00c623ec has its CatchHandler @ 00c6261c */
  pCVar3 = (CFileSystem *)CFileSystem::getSingleton();
  lVar4 = CFileSystem::getDataGroup(pCVar3,param_1);
  if (lVar4 == 0) {
    if (local_70 == '\0') {
                    /* try { // try from 00c624f5 to 00c62526 has its CatchHandler @ 00c6261c */
      pCVar3 = (CFileSystem *)CFileSystem::getSingleton();
      CFileSystem::getFileInfo(pCVar3,param_1,(CFileInfo *)&local_98,false,true,false);
    }
    if (local_80 == 0) {
                    /* try { // try from 00c624cc to 00c624d0 has its CatchHandler @ 00c6273c */
      std::string::string(local_58,
                          "Error in attempting to load file. Trying to load compressed file. DataGroups can\'t load compressed files."
                          ,local_39);
                    /* try { // try from 00c624d1 to 00c624e7 has its CatchHandler @ 00c6272c */
      uVar6 = Ogre::LogManager::getSingleton();
      Ogre::LogManager::logMessage(uVar6,local_58,3,0);
                    /* try { // try from 00c624eb to 00c624ef has its CatchHandler @ 00c6273c */
      std::string::~string(local_58);
    }
    if (CONCAT44(iStack_7c,local_80) == 1) {
      CBinaryStyle::CBinaryStyle((CBinaryStyle *)local_68);
                    /* try { // try from 00c62533 to 00c62537 has its CatchHandler @ 00c62545 */
      LoadFile(this,param_1,(iDataFileSaveAndLoad *)local_68,param_2);
                    /* try { // try from 00c6253b to 00c6253f has its CatchHandler @ 00c6261c */
      CBinaryStyle::~CBinaryStyle((CBinaryStyle *)local_68);
    }
    else if ((iStack_7c - 1U < 2) && (local_80 == 1)) {
      COgreResourceFile::COgreResourceFile((COgreResourceFile *)local_68);
                    /* try { // try from 00c624a8 to 00c624ac has its CatchHandler @ 00c62624 */
      LoadFile(this,param_1,(iDataFileSaveAndLoad *)local_68,param_2);
                    /* try { // try from 00c624b0 to 00c624b4 has its CatchHandler @ 00c6261c */
      COgreResourceFile::~COgreResourceFile((COgreResourceFile *)local_68);
    }
    else {
      CPairStyle::CPairStyle(local_68);
                    /* try { // try from 00c623f9 to 00c623fd has its CatchHandler @ 00c62601 */
      LoadFile(this,param_1,(iDataFileSaveAndLoad *)local_68,param_2);
                    /* try { // try from 00c62401 to 00c6249b has its CatchHandler @ 00c6261c */
      CPairStyle::~CPairStyle(local_68);
    }
    if ((allocator *)(local_78 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_78 + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_78 + -0x18));
      }
    }
    if ((allocator *)(local_88 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_88 + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_88 + -0x18));
      }
    }
    if ((allocator *)(local_90 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_90 + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_90 + -0x18));
      }
    }
    if ((allocator *)(local_98 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_98 + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_98 + -0x18));
      }
    }
  }
  else {
    this[0x59] = (CDataGroup)0x1;
    iVar2 = *(int *)(lVar4 + 0x40);
    if (iVar2 == 0) {
      iVar2 = 1;
    }
    *(int *)(this + 0x48) = iVar2;
    if (*(int *)(lVar4 + 0x40) != 0) {
      uVar7 = *(uint *)(this + 0x40);
      uVar9 = 0;
      do {
        if ((uint)uVar9 < *(uint *)(lVar4 + 0x44)) {
          uVar10 = *(uint *)(this + 0x44);
          uVar6 = *(undefined8 *)(uVar9 * 8 + *(long *)(lVar4 + 0x38));
          if (uVar10 <= uVar7) goto LAB_00c62160;
LAB_00c62364:
          pvVar5 = *(void **)(this + 0x38);
        }
        else {
          uVar10 = *(uint *)(this + 0x44);
          uVar6 = **(undefined8 **)(lVar4 + 0x38);
          if (uVar7 < uVar10) goto LAB_00c62364;
LAB_00c62160:
          if (*(long *)(this + 0x38) == 0) {
            *(uint *)(this + 0x44) = *(uint *)(this + 0x48);
            pvVar5 = operator_new__((ulong)*(uint *)(this + 0x48) << 3);
            *(void **)(this + 0x38) = pvVar5;
            uVar7 = *(uint *)(this + 0x40);
          }
          else {
            iVar2 = *(int *)(this + 0x48);
            pvVar5 = operator_new__((ulong)(uVar10 + iVar2) << 3);
            if (*(int *)(this + 0x44) != 0) {
              uVar8 = 0;
              do {
                uVar7 = (int)uVar8 + 1;
                *(undefined8 *)((long)pvVar5 + uVar8 * 8) =
                     *(undefined8 *)(*(long *)(this + 0x38) + uVar8 * 8);
                uVar8 = (ulong)uVar7;
              } while (uVar7 < *(uint *)(this + 0x44));
            }
            if (*(void **)(this + 0x38) != (void *)0x0) {
              operator_delete__(*(void **)(this + 0x38));
            }
            uVar7 = *(uint *)(this + 0x40);
            *(void **)(this + 0x38) = pvVar5;
            *(uint *)(this + 0x44) = uVar10 + iVar2;
          }
        }
        uVar10 = (uint)uVar9 + 1;
        uVar9 = (ulong)uVar10;
        *(undefined8 *)((long)pvVar5 + (ulong)uVar7 * 8) = uVar6;
        uVar7 = *(int *)(this + 0x40) + 1;
        *(uint *)(this + 0x40) = uVar7;
      } while (uVar10 < *(uint *)(lVar4 + 0x40));
    }
    iVar2 = *(int *)(lVar4 + 0x28);
    if (iVar2 == 0) {
      iVar2 = 1;
    }
    *(int *)(this + 0x30) = iVar2;
    if (*(int *)(lVar4 + 0x28) != 0) {
      uVar7 = *(uint *)(this + 0x28);
      uVar10 = 0;
      do {
        if (uVar10 < *(uint *)(lVar4 + 0x2c)) {
          uVar11 = *(uint *)(this + 0x2c);
          uVar6 = *(undefined8 *)((ulong)uVar10 * 8 + *(long *)(lVar4 + 0x20));
          if (uVar11 <= uVar7) goto LAB_00c62230;
LAB_00c6233c:
          pvVar5 = *(void **)(this + 0x20);
        }
        else {
          uVar11 = *(uint *)(this + 0x2c);
          uVar6 = **(undefined8 **)(lVar4 + 0x20);
          if (uVar7 < uVar11) goto LAB_00c6233c;
LAB_00c62230:
          if (*(long *)(this + 0x20) == 0) {
            *(uint *)(this + 0x2c) = *(uint *)(this + 0x30);
            pvVar5 = operator_new__((ulong)*(uint *)(this + 0x30) << 3);
            *(void **)(this + 0x20) = pvVar5;
            uVar7 = *(uint *)(this + 0x28);
          }
          else {
            iVar2 = *(int *)(this + 0x30);
            pvVar5 = operator_new__((ulong)(uVar11 + iVar2) << 3);
            if (*(int *)(this + 0x2c) != 0) {
              uVar9 = 0;
              do {
                uVar7 = (int)uVar9 + 1;
                *(undefined8 *)((long)pvVar5 + uVar9 * 8) =
                     *(undefined8 *)(*(long *)(this + 0x20) + uVar9 * 8);
                uVar9 = (ulong)uVar7;
              } while (uVar7 < *(uint *)(this + 0x2c));
            }
            if (*(void **)(this + 0x20) != (void *)0x0) {
              operator_delete__(*(void **)(this + 0x20));
            }
            uVar7 = *(uint *)(this + 0x28);
            *(void **)(this + 0x20) = pvVar5;
            *(uint *)(this + 0x2c) = uVar11 + iVar2;
          }
        }
        uVar10 = uVar10 + 1;
        *(undefined8 *)((long)pvVar5 + (ulong)uVar7 * 8) = uVar6;
        uVar7 = *(int *)(this + 0x28) + 1;
        *(uint *)(this + 0x28) = uVar7;
      } while (uVar10 < *(uint *)(lVar4 + 0x28));
    }
    *(undefined4 *)(this + 0x10) = *(undefined4 *)(lVar4 + 0x10);
    if ((allocator *)(local_78 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_78 + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_78 + -0x18));
      }
    }
    if ((allocator *)(local_88 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_88 + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_88 + -0x18));
      }
    }
    if ((allocator *)(local_90 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_90 + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_90 + -0x18));
      }
    }
    if ((allocator *)(local_98 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_98 + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_98 + -0x18));
      }
    }
  }
  return;
}

/* export-summary functions=50 failures=0 */
