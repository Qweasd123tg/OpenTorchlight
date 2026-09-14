/* Targeted Ghidra class export.
   namespace=CDataValue
   Treat pseudocode as navigation evidence. */


/* address=00c62dd0
   symbol=CDataValue::GetDataValueName */

/* CDataValue::GetDataValueName() */

undefined8 * __thiscall CDataValue::GetDataValueName(CDataValue *this)

{
  uint uVar1;
  long lVar2;
  long lVar3;
  long lVar4;
  long lVar5;

  lVar2 = *(long *)(this + 0x28);
  if ((lVar2 == 0) || (uVar1 = *(uint *)(this + 0x20), uVar1 == 0xffffffff)) {
    return &::EMPTY_WSTRING;
  }
  if (*(long *)(lVar2 + 0x30) != 0) {
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

/* address=00c62e40
   symbol=CDataValue::GetValueBool */

/* CDataValue::GetValueBool() */

CDataValue __thiscall CDataValue::GetValueBool(CDataValue *this)

{
  return this[0x18];
}

/* address=00c62e50
   symbol=CDataValue::GetValueInt64 */

/* CDataValue::GetValueInt64() */

undefined8 __thiscall CDataValue::GetValueInt64(CDataValue *this)

{
  return *(undefined8 *)(this + 0x18);
}

/* address=00c62e60
   symbol=CDataValue::GetValueInt32 */

/* CDataValue::GetValueInt32() */

undefined4 __thiscall CDataValue::GetValueInt32(CDataValue *this)

{
  return *(undefined4 *)(this + 0x18);
}

/* address=00c62e70
   symbol=CDataValue::GetValueUInt32 */

/* CDataValue::GetValueUInt32() */

undefined4 __thiscall CDataValue::GetValueUInt32(CDataValue *this)

{
  return *(undefined4 *)(this + 0x18);
}

/* address=00c62e80
   symbol=CDataValue::GetValueFloat32 */

/* CDataValue::GetValueFloat32() */

undefined4 __thiscall CDataValue::GetValueFloat32(CDataValue *this)

{
  return *(undefined4 *)(this + 0x18);
}

/* address=00c62e90
   symbol=CDataValue::GetValueFloat64 */

/* CDataValue::GetValueFloat64() */

undefined8 __thiscall CDataValue::GetValueFloat64(CDataValue *this)

{
  return *(undefined8 *)(this + 0x18);
}

/* address=00c62ea0
   symbol=CDataValue::SetValueBool */

/* CDataValue::SetValueBool(bool) */

void __thiscall CDataValue::SetValueBool(CDataValue *this,bool param_1)

{
  *(undefined4 *)(this + 0x30) = 6;
  this[0x18] = (CDataValue)param_1;
  return;
}

/* address=00c62eb0
   symbol=CDataValue::SetValueInt64 */

/* CDataValue::SetValueInt64(long long) */

void __thiscall CDataValue::SetValueInt64(CDataValue *this,longlong param_1)

{
  *(undefined4 *)(this + 0x30) = 7;
  *(longlong *)(this + 0x18) = param_1;
  return;
}

/* address=00c62ec0
   symbol=CDataValue::SetValueInt32 */

/* CDataValue::SetValueInt32(int) */

void __thiscall CDataValue::SetValueInt32(CDataValue *this,int param_1)

{
  *(undefined4 *)(this + 0x30) = 1;
  *(int *)(this + 0x18) = param_1;
  return;
}

/* address=00c62ed0
   symbol=CDataValue::SetValueUInt32 */

/* CDataValue::SetValueUInt32(unsigned int) */

void __thiscall CDataValue::SetValueUInt32(CDataValue *this,uint param_1)

{
  *(undefined4 *)(this + 0x30) = 4;
  *(uint *)(this + 0x18) = param_1;
  return;
}

/* address=00c62ee0
   symbol=CDataValue::SetValueFloat32 */

/* CDataValue::SetValueFloat32(float) */

void __thiscall CDataValue::SetValueFloat32(CDataValue *this,float param_1)

{
  *(undefined4 *)(this + 0x30) = 2;
  *(float *)(this + 0x18) = param_1;
  return;
}

/* address=00c62ef0
   symbol=CDataValue::SetValueFloat64 */

/* CDataValue::SetValueFloat64(double) */

void __thiscall CDataValue::SetValueFloat64(CDataValue *this,double param_1)

{
  *(undefined4 *)(this + 0x30) = 3;
  *(double *)(this + 0x18) = param_1;
  return;
}

/* address=00c62f00
   symbol=CDataValue::SetValueIsTranslate */

/* CDataValue::SetValueIsTranslate() */

void __thiscall CDataValue::SetValueIsTranslate(CDataValue *this)

{
  if ((*(int *)(this + 0x30) != 8) && (*(int *)(this + 0x30) != 5)) {
    return;
  }
  *(undefined4 *)(this + 0x30) = 8;
  return;
}

/* address=00c62f20
   symbol=CDataValue::_GLOBAL__I_CDataValue */

/* CDataValue::CDataValue(unsigned int, UNIONDATA64BIT, CDataValue::EDATAVALUETYPES,
   TRepository<std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > >*)
    */

void CDataValue::_GLOBAL__I_CDataValue(void)

{
  ::EMPTY_STRING = &DAT_01423a38;
  __cxa_atexit(std::string::~string,&::EMPTY_STRING,&__dso_handle);
  ::EMPTY_WSTRING = &DAT_01424558;
  __cxa_atexit(std::wstring::~wstring,&::EMPTY_WSTRING,&__dso_handle);
  std::ios_base::Init::Init((Init *)&std::__ioinit);
  __cxa_atexit(std::ios_base::Init::~Init,&std::__ioinit,&__dso_handle);
  return;
}

/* address=00c62f90
   symbol=CDataValue::GetValueTypeAsString */

/* CDataValue::GetValueTypeAsString() */

void CDataValue::GetValueTypeAsString(void)

{
  long in_RSI;
  wstring_conflict *in_RDI;
  allocator local_11;
  allocator local_10;
  allocator local_f;
  allocator local_e;
  allocator local_d;
  allocator local_c;
  allocator local_b;
  allocator local_a;
  allocator local_9;

  switch(*(undefined4 *)(in_RSI + 0x30)) {
  default:
                    /* try { // try from 00c62fab to 00c62faf has its CatchHandler @ 00c630d0 */
    std::wstring::wstring(in_RDI,L"Not Set",&local_9);
    return;
  case 1:
                    /* try { // try from 00c62ffa to 00c62ffe has its CatchHandler @ 00c630f2 */
    std::wstring::wstring(in_RDI,L"INTEGER",&local_a);
    return;
  case 2:
                    /* try { // try from 00c6301a to 00c6301e has its CatchHandler @ 00c630e6 */
    std::wstring::wstring(in_RDI,L"FLOAT",&local_c);
    return;
  case 3:
                    /* try { // try from 00c6303a to 00c6303e has its CatchHandler @ 00c630e4 */
    std::wstring::wstring(in_RDI,L"DOUBLE",&local_d);
    return;
  case 4:
                    /* try { // try from 00c6305a to 00c6305e has its CatchHandler @ 00c630e2 */
    std::wstring::wstring(in_RDI,L"UNSIGNED INT",&local_e);
    return;
  case 5:
                    /* try { // try from 00c6307a to 00c6307e has its CatchHandler @ 00c630d6 */
    std::wstring::wstring(in_RDI,L"STRING",&local_f);
    return;
  case 6:
                    /* try { // try from 00c6309a to 00c6309e has its CatchHandler @ 00c630d4 */
    std::wstring::wstring(in_RDI,L"BOOL",&local_11);
    return;
  case 7:
                    /* try { // try from 00c630ba to 00c630be has its CatchHandler @ 00c630d2 */
    std::wstring::wstring(in_RDI,L"INTEGER64",&local_b);
    return;
  case 8:
                    /* try { // try from 00c62fda to 00c62fde has its CatchHandler @ 00c630c8 */
    std::wstring::wstring(in_RDI,L"TRANSLATE",&local_10);
    return;
  }
}

/* address=00c63100
   symbol=CDataValue::GetValueString */

/* CDataValue::GetValueString(bool) */

undefined8 * __thiscall CDataValue::GetValueString(CDataValue *this,bool param_1)

{
  int iVar1;
  uint uVar2;
  long lVar3;
  long lVar4;
  long lVar5;
  undefined8 *puVar6;
  long lVar7;
  CStringTranslate *this_00;
  wstring_conflict *pwVar8;

  iVar1 = *(int *)(this + 0x30);
  if ((iVar1 != 8) && (iVar1 != 5)) {
    return &::EMPTY_WSTRING;
  }
  lVar7 = *(long *)(this + 0x28);
  puVar6 = &::EMPTY_WSTRING;
  if ((lVar7 != 0) && (this[0x10] != (CDataValue)0x0)) {
    if ((param_1) && (iVar1 == 8)) {
      lVar7 = CStringTranslate::getSinglton();
      if (lVar7 != 0) {
        uVar2 = *(uint *)(this + 0x18);
        lVar7 = *(long *)(this + 0x28);
        if ((uVar2 != 0xffffffff) && (*(long *)(lVar7 + 0x30) != 0)) {
          lVar5 = *(long *)(lVar7 + 0x18);
          lVar4 = lVar7 + 0x10;
          while (lVar3 = lVar5, lVar3 != 0) {
            if (*(uint *)(lVar3 + 0x20) < uVar2) {
              lVar5 = *(long *)(lVar3 + 0x18);
            }
            else {
              lVar5 = *(long *)(lVar3 + 0x10);
              lVar4 = lVar3;
            }
          }
          if ((lVar7 + 0x10 != lVar4) && (*(uint *)(lVar4 + 0x20) <= uVar2)) {
            pwVar8 = (wstring_conflict *)(lVar4 + 0x28);
            goto LAB_00c63247;
          }
        }
        pwVar8 = (wstring_conflict *)(lVar7 + 0x98);
LAB_00c63247:
        this_00 = (CStringTranslate *)CStringTranslate::getSinglton();
        puVar6 = (undefined8 *)CStringTranslate::getTranslateString(this_00,pwVar8);
        return puVar6;
      }
      lVar7 = *(long *)(this + 0x28);
    }
    uVar2 = *(uint *)(this + 0x18);
    if ((uVar2 != 0xffffffff) && (*(long *)(lVar7 + 0x30) != 0)) {
      lVar5 = *(long *)(lVar7 + 0x18);
      lVar4 = lVar7 + 0x10;
      while (lVar3 = lVar5, lVar3 != 0) {
        if (*(uint *)(lVar3 + 0x20) < uVar2) {
          lVar5 = *(long *)(lVar3 + 0x18);
        }
        else {
          lVar5 = *(long *)(lVar3 + 0x10);
          lVar4 = lVar3;
        }
      }
      if ((lVar7 + 0x10 != lVar4) && (*(uint *)(lVar4 + 0x20) <= uVar2)) {
        return (undefined8 *)(lVar4 + 0x28);
      }
    }
    puVar6 = (undefined8 *)(lVar7 + 0x98);
  }
  return puVar6;
}

/* address=00c63280
   symbol=CDataValue::GetValueAsString */

/* CDataValue::GetValueAsString() */

void CDataValue::GetValueAsString(void)

{
  wstring_conflict *pwVar1;
  CDataValue *in_RSI;
  wstring_conflict *in_RDI;
  allocator local_9;

  switch(*(undefined4 *)(in_RSI + 0x30)) {
  default:
                    /* try { // try from 00c6329e to 00c632a2 has its CatchHandler @ 00c63376 */
    std::wstring::wstring(in_RDI,L"",&local_9);
    return;
  case 1:
    STRINGS::GetValueAsWString((STRINGS *)in_RDI,*(int *)(in_RSI + 0x18));
    return;
  case 2:
    STRINGS::GetValueAsWString((STRINGS *)in_RDI,*(float *)(in_RSI + 0x18));
    return;
  case 3:
    STRINGS::GetValueAsWString((STRINGS *)in_RDI,*(double *)(in_RSI + 0x18));
    return;
  case 4:
    STRINGS::GetValueAsWString((uint)in_RDI);
    return;
  case 5:
  case 8:
    pwVar1 = (wstring_conflict *)GetValueString(in_RSI,false);
    std::wstring::wstring(in_RDI,pwVar1);
    return;
  case 6:
    STRINGS::GetValueAsWString((STRINGS *)in_RDI,(bool)in_RSI[0x18]);
    return;
  case 7:
    STRINGS::GetValueAsWString((longlong)in_RDI);
    return;
  }
}

/* address=00c63380
   symbol=CDataValue::CDataValue */

/* WARNING: Removing unreachable block (ram,0x00c63812) */
/* WARNING: Removing unreachable block (ram,0x00c637d2) */
/* WARNING: Removing unreachable block (ram,0x00c637e0) */
/* WARNING: Removing unreachable block (ram,0x00c637c2) */
/* CDataValue::CDataValue(unsigned int, UNIONDATA64BIT, CDataValue::EDATAVALUETYPES,
   TRepository<std::wstring >*) */

void __thiscall
CDataValue::CDataValue(CDataValue *this,uint param_1,undefined8 param_3,int param_4,long param_5)

{
  allocator *paVar1;
  wchar_t *pwVar2;
  long lVar3;
  wchar_t wVar4;
  uint uVar5;
  long lVar6;
  long lVar7;
  long lVar8;
  int iVar9;
  long lVar10;
  wstring_conflict *pwVar11;
  uint local_68;
  undefined2 local_64;
  wchar_t *local_58 [2];
  uint local_48;
  undefined2 local_44;

  CRunicCore::CRunicCore((CRunicCore *)this);
  *(undefined ***)this = &PTR__CDataValue_00ff3590;
  *(undefined8 *)(this + 0x18) = param_3;
  *(uint *)(this + 0x20) = param_1;
  *(long *)(this + 0x28) = param_5;
  *(int *)(this + 0x30) = param_4;
  this[0x10] = (CDataValue)(param_4 == 8 || param_4 == 5);
  if (param_1 != 0xffffffff) {
    if (*(long *)(param_5 + 0x30) == 0) {
LAB_00c633e0:
      pwVar11 = (wstring_conflict *)(param_5 + 0x98);
    }
    else {
      lVar6 = *(long *)(param_5 + 0x18);
      lVar3 = param_5 + 0x10;
      while (lVar8 = lVar6, lVar8 != 0) {
        if (*(uint *)(lVar8 + 0x20) < param_1) {
          lVar6 = *(long *)(lVar8 + 0x18);
        }
        else {
          lVar6 = *(long *)(lVar8 + 0x10);
          lVar3 = lVar8;
        }
      }
      if ((param_5 + 0x10 == lVar3) || (param_1 < *(uint *)(lVar3 + 0x20))) goto LAB_00c633e0;
      pwVar11 = (wstring_conflict *)(lVar3 + 0x28);
    }
                    /* try { // try from 00c633f0 to 00c6350f has its CatchHandler @ 00c6380b */
    std::wstring::wstring((wstring_conflict *)local_58,pwVar11);
    pwVar2 = local_58[0];
    paVar1 = (allocator *)(local_58[0] + -6);
    if ((*(size_t *)(local_58[0] + -6) == *(size_t *)(*(wchar_t **)(param_5 + 0x98) + -6)) &&
       (iVar9 = wmemcmp(local_58[0],*(wchar_t **)(param_5 + 0x98),*(size_t *)(local_58[0] + -6)),
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
      lVar6 = *(long *)(param_5 + 0x78);
      lVar3 = param_5 + 0x70;
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
                    /* try { // try from 00c637a2 to 00c637a6 has its CatchHandler @ 00c637f0 */
          lVar10 = std::
                   _Rb_tree<unsigned_int,std::pair<unsigned_int_const,unsigned_short>,std::_Select1st<std::pair<unsigned_int_const,unsigned_short>>,std::less<unsigned_int>,std::allocator<std::pair<unsigned_int_const,unsigned_short>>>
                   ::_M_insert_unique_((_Rb_tree<unsigned_int,std::pair<unsigned_int_const,unsigned_short>,std::_Select1st<std::pair<unsigned_int_const,unsigned_short>>,std::less<unsigned_int>,std::allocator<std::pair<unsigned_int_const,unsigned_short>>>
                                        *)(param_5 + 0x68),lVar10,&local_48);
        }
        *(undefined2 *)(lVar10 + 0x24) = 1;
      }
      else {
        *(short *)(lVar8 + 0x24) = *(short *)(lVar8 + 0x24) + 1;
      }
      if ((allocator *)(local_58[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
      {
        LOCK();
        pwVar2 = local_58[0] + -2;
        wVar4 = *pwVar2;
        *pwVar2 = *pwVar2 + L'\xffffffff';
        UNLOCK();
        if (wVar4 < L'\x01') {
          std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -6));
        }
      }
    }
  }
  if (param_5 == 0) {
    return;
  }
  if (this[0x10] == (CDataValue)0x0) {
    return;
  }
  uVar5 = *(uint *)(this + 0x18);
  if (uVar5 == 0xffffffff) {
    return;
  }
  if (*(long *)(param_5 + 0x30) != 0) {
    lVar6 = *(long *)(param_5 + 0x18);
    lVar3 = param_5 + 0x10;
    while (lVar8 = lVar6, lVar8 != 0) {
      if (*(uint *)(lVar8 + 0x20) < uVar5) {
        lVar6 = *(long *)(lVar8 + 0x18);
      }
      else {
        lVar6 = *(long *)(lVar8 + 0x10);
        lVar3 = lVar8;
      }
    }
    if ((param_5 + 0x10 != lVar3) && (*(uint *)(lVar3 + 0x20) <= uVar5)) {
      pwVar11 = (wstring_conflict *)(lVar3 + 0x28);
      goto LAB_00c63503;
    }
  }
  pwVar11 = (wstring_conflict *)(param_5 + 0x98);
LAB_00c63503:
  std::wstring::wstring((wstring_conflict *)local_58,pwVar11);
  pwVar2 = local_58[0];
  paVar1 = (allocator *)(local_58[0] + -6);
  if ((*(size_t *)(local_58[0] + -6) == *(size_t *)(*(wchar_t **)(param_5 + 0x98) + -6)) &&
     (iVar9 = wmemcmp(local_58[0],*(wchar_t **)(param_5 + 0x98),*(size_t *)(local_58[0] + -6)),
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
    lVar6 = *(long *)(param_5 + 0x78);
    lVar3 = param_5 + 0x70;
    lVar10 = lVar6;
    lVar8 = lVar3;
    while (lVar7 = lVar10, lVar7 != 0) {
      if (*(uint *)(lVar7 + 0x20) < uVar5) {
        lVar10 = *(long *)(lVar7 + 0x18);
      }
      else {
        lVar10 = *(long *)(lVar7 + 0x10);
        lVar8 = lVar7;
      }
    }
    lVar10 = lVar3;
    if ((lVar3 == lVar8) || (uVar5 < *(uint *)(lVar8 + 0x20))) {
      while (lVar8 = lVar6, lVar8 != 0) {
        if (*(uint *)(lVar8 + 0x20) < uVar5) {
          lVar6 = *(long *)(lVar8 + 0x18);
        }
        else {
          lVar6 = *(long *)(lVar8 + 0x10);
          lVar10 = lVar8;
        }
      }
      if ((lVar3 == lVar10) || (uVar5 < *(uint *)(lVar10 + 0x20))) {
        local_64 = 0;
        local_68 = uVar5;
                    /* try { // try from 00c635a6 to 00c635aa has its CatchHandler @ 00c63810 */
        lVar10 = std::
                 _Rb_tree<unsigned_int,std::pair<unsigned_int_const,unsigned_short>,std::_Select1st<std::pair<unsigned_int_const,unsigned_short>>,std::less<unsigned_int>,std::allocator<std::pair<unsigned_int_const,unsigned_short>>>
                 ::_M_insert_unique_((_Rb_tree<unsigned_int,std::pair<unsigned_int_const,unsigned_short>,std::_Select1st<std::pair<unsigned_int_const,unsigned_short>>,std::less<unsigned_int>,std::allocator<std::pair<unsigned_int_const,unsigned_short>>>
                                      *)(param_5 + 0x68),lVar10,&local_68);
      }
      *(undefined2 *)(lVar10 + 0x24) = 1;
    }
    else {
      *(short *)(lVar8 + 0x24) = *(short *)(lVar8 + 0x24) + 1;
    }
    if ((allocator *)(local_58[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      pwVar2 = local_58[0] + -2;
      wVar4 = *pwVar2;
      *pwVar2 = *pwVar2 + L'\xffffffff';
      UNLOCK();
      if (wVar4 < L'\x01') {
        std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -6));
      }
    }
  }
  return;
}

/* address=00c63820
   symbol=CDataValue::~CDataValue */

/* WARNING: Removing unreachable block (ram,0x00c63f06) */
/* WARNING: Removing unreachable block (ram,0x00c63f9c) */
/* WARNING: Removing unreachable block (ram,0x00c63f52) */
/* WARNING: Removing unreachable block (ram,0x00c63fac) */
/* WARNING: Removing unreachable block (ram,0x00c63f60) */
/* WARNING: Removing unreachable block (ram,0x00c63f14) */
/* CDataValue::~CDataValue() */

void __thiscall CDataValue::~CDataValue(CDataValue *this)

{
  _Rb_tree_node_base *p_Var1;
  int *piVar2;
  allocator *paVar3;
  short sVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  ulong uVar8;
  long lVar9;
  _Rb_tree_node_base *p_Var10;
  wchar_t *pwVar11;
  long lVar12;
  _Rb_tree_node_base *p_Var13;
  int iVar14;
  void *pvVar15;
  ulong uVar16;
  wstring_conflict *pwVar17;
  allocator *paVar18;
  _Rb_tree_node_base *p_Var19;
  _Rb_tree_node_base *p_Var20;
  long lVar21;
  _Rb_tree_node_base *local_58;
  wchar_t *local_48 [3];

  lVar6 = *(long *)(this + 0x28);
  *(undefined ***)this = &PTR__CDataValue_00ff3590;
  if (lVar6 == 0) goto LAB_00c639a1;
  uVar5 = *(uint *)(this + 0x20);
  if ((uVar5 == 0xffffffff) || (*(long *)(lVar6 + 0x30) == 0)) {
LAB_00c63858:
    pwVar17 = (wstring_conflict *)(lVar6 + 0x98);
  }
  else {
    lVar12 = *(long *)(lVar6 + 0x18);
    lVar21 = lVar6 + 0x10;
    while (lVar9 = lVar12, lVar9 != 0) {
      if (*(uint *)(lVar9 + 0x20) < uVar5) {
        lVar12 = *(long *)(lVar9 + 0x18);
      }
      else {
        lVar12 = *(long *)(lVar9 + 0x10);
        lVar21 = lVar9;
      }
    }
    if ((lVar6 + 0x10 == lVar21) || (uVar5 < *(uint *)(lVar21 + 0x20))) goto LAB_00c63858;
    pwVar17 = (wstring_conflict *)(lVar21 + 0x28);
  }
                    /* try { // try from 00c63864 to 00c63915 has its CatchHandler @ 00c63f01 */
  std::wstring::wstring((wstring_conflict *)local_48,pwVar17);
  paVar18 = (allocator *)(local_48[0] + -6);
  if ((*(size_t *)(local_48[0] + -6) != *(size_t *)(*(wchar_t **)(lVar6 + 0x98) + -6)) ||
     (iVar14 = wmemcmp(local_48[0],*(wchar_t **)(lVar6 + 0x98),*(size_t *)(local_48[0] + -6)),
     iVar14 != 0)) {
    p_Var1 = (_Rb_tree_node_base *)(lVar6 + 0x70);
    p_Var20 = *(_Rb_tree_node_base **)(lVar6 + 0x78);
    p_Var19 = p_Var1;
    while (p_Var13 = p_Var20, p_Var13 != (_Rb_tree_node_base *)0x0) {
      if (*(uint *)(p_Var13 + 0x20) < uVar5) {
        p_Var20 = *(_Rb_tree_node_base **)(p_Var13 + 0x18);
      }
      else {
        p_Var20 = *(_Rb_tree_node_base **)(p_Var13 + 0x10);
        p_Var19 = p_Var13;
      }
    }
    if ((p_Var1 != p_Var19) && (*(uint *)(p_Var19 + 0x20) <= uVar5)) {
      sVar4 = *(short *)(p_Var19 + 0x24);
      *(short *)(p_Var19 + 0x24) = sVar4 + -1;
      if ((short)(sVar4 + -1) == 0) {
                    /* try { // try from 00c63a30 to 00c63ba8 has its CatchHandler @ 00c63ed2 */
        pvVar15 = (void *)std::_Rb_tree_rebalance_for_erase(p_Var19,p_Var1);
        operator_delete(pvVar15);
        pwVar11 = local_48[0];
        p_Var1 = (_Rb_tree_node_base *)(lVar6 + 0x40);
        *(long *)(lVar6 + 0x90) = *(long *)(lVar6 + 0x90) + -1;
        p_Var19 = *(_Rb_tree_node_base **)(lVar6 + 0x48);
        local_58 = p_Var1;
        if (p_Var19 != (_Rb_tree_node_base *)0x0) {
          uVar7 = *(ulong *)(local_48[0] + -6);
          do {
            uVar8 = *(ulong *)(*(wchar_t **)(p_Var19 + 0x20) + -6);
            uVar16 = uVar7;
            if (uVar8 <= uVar7) {
              uVar16 = uVar8;
            }
            iVar14 = wmemcmp(*(wchar_t **)(p_Var19 + 0x20),pwVar11,uVar16);
            if (iVar14 == 0) {
              lVar21 = uVar8 - uVar7;
              if (0x7fffffff < lVar21) goto LAB_00c63a77;
              if (-0x80000001 < lVar21) {
                iVar14 = (int)lVar21;
                goto LAB_00c63a73;
              }
LAB_00c63abd:
              p_Var20 = *(_Rb_tree_node_base **)(p_Var19 + 0x18);
            }
            else {
LAB_00c63a73:
              if (iVar14 < 0) goto LAB_00c63abd;
LAB_00c63a77:
              p_Var20 = *(_Rb_tree_node_base **)(p_Var19 + 0x10);
              local_58 = p_Var19;
            }
            p_Var19 = p_Var20;
          } while (p_Var19 != (_Rb_tree_node_base *)0x0);
        }
        if (p_Var1 == local_58) {
LAB_00c63b18:
          local_58 = p_Var1;
        }
        else {
          uVar7 = *(ulong *)(local_48[0] + -6);
          uVar8 = *(ulong *)(*(wchar_t **)(local_58 + 0x20) + -6);
          uVar16 = uVar7;
          if (uVar8 <= uVar7) {
            uVar16 = uVar8;
          }
          iVar14 = wmemcmp(local_48[0],*(wchar_t **)(local_58 + 0x20),uVar16);
          if (iVar14 == 0) {
            lVar21 = uVar7 - uVar8;
            if (lVar21 < 0x80000000) {
              if (lVar21 < -0x80000000) goto LAB_00c63b18;
              iVar14 = (int)lVar21;
              goto LAB_00c63def;
            }
          }
          else {
LAB_00c63def:
            if (iVar14 < 0) goto LAB_00c63b18;
          }
        }
        p_Var19 = (_Rb_tree_node_base *)(lVar6 + 0x10);
        p_Var13 = *(_Rb_tree_node_base **)(lVar6 + 0x18);
        p_Var20 = p_Var19;
        while (p_Var10 = p_Var13, p_Var10 != (_Rb_tree_node_base *)0x0) {
          if (*(uint *)(p_Var10 + 0x20) < uVar5) {
            p_Var13 = *(_Rb_tree_node_base **)(p_Var10 + 0x18);
          }
          else {
            p_Var13 = *(_Rb_tree_node_base **)(p_Var10 + 0x10);
            p_Var20 = p_Var10;
          }
        }
        if ((p_Var19 == p_Var20) || (uVar5 < *(uint *)(p_Var20 + 0x20))) {
          p_Var20 = p_Var19;
        }
        if ((p_Var1 != local_58) && (p_Var19 != p_Var20)) {
          pvVar15 = (void *)std::_Rb_tree_rebalance_for_erase(local_58,p_Var1);
          paVar18 = (allocator *)(*(long *)((long)pvVar15 + 0x20) + -0x18);
          if (paVar18 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(*(long *)((long)pvVar15 + 0x20) + -8);
            iVar14 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar14 < 1) {
              std::wstring::_Rep::_M_destroy(paVar18);
            }
          }
          operator_delete(pvVar15);
          *(long *)(lVar6 + 0x60) = *(long *)(lVar6 + 0x60) + -1;
          pvVar15 = (void *)std::_Rb_tree_rebalance_for_erase(p_Var20,p_Var19);
          paVar18 = (allocator *)(*(long *)((long)pvVar15 + 0x28) + -0x18);
          if (paVar18 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(*(long *)((long)pvVar15 + 0x28) + -8);
            iVar14 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar14 < 1) {
              std::wstring::_Rep::_M_destroy(paVar18);
            }
          }
          operator_delete(pvVar15);
          *(long *)(lVar6 + 0x30) = *(long *)(lVar6 + 0x30) + -1;
        }
      }
      paVar18 = (allocator *)(local_48[0] + -6);
    }
  }
  if (paVar18 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    paVar3 = paVar18 + 0x10;
    iVar14 = *(int *)paVar3;
    *(int *)paVar3 = *(int *)paVar3 + -1;
    UNLOCK();
    if (iVar14 < 1) {
      std::wstring::_Rep::_M_destroy(paVar18);
    }
  }
  if ((*(int *)(this + 0x30) != 8) && (*(int *)(this + 0x30) != 5)) goto LAB_00c639a1;
  uVar5 = *(uint *)(this + 0x18);
  lVar6 = *(long *)(this + 0x28);
  if ((uVar5 == 0xffffffff) || (*(long *)(lVar6 + 0x30) == 0)) {
LAB_00c63905:
    pwVar17 = (wstring_conflict *)(lVar6 + 0x98);
  }
  else {
    lVar12 = *(long *)(lVar6 + 0x18);
    lVar21 = lVar6 + 0x10;
    while (lVar9 = lVar12, lVar9 != 0) {
      if (*(uint *)(lVar9 + 0x20) < uVar5) {
        lVar12 = *(long *)(lVar9 + 0x18);
      }
      else {
        lVar12 = *(long *)(lVar9 + 0x10);
        lVar21 = lVar9;
      }
    }
    if ((lVar6 + 0x10 == lVar21) || (uVar5 < *(uint *)(lVar21 + 0x20))) goto LAB_00c63905;
    pwVar17 = (wstring_conflict *)(lVar21 + 0x28);
  }
  std::wstring::wstring((wstring_conflict *)local_48,pwVar17);
  paVar18 = (allocator *)(local_48[0] + -6);
  if ((*(size_t *)(local_48[0] + -6) != *(size_t *)(*(wchar_t **)(lVar6 + 0x98) + -6)) ||
     (iVar14 = wmemcmp(local_48[0],*(wchar_t **)(lVar6 + 0x98),*(size_t *)(local_48[0] + -6)),
     iVar14 != 0)) {
    p_Var1 = (_Rb_tree_node_base *)(lVar6 + 0x70);
    p_Var20 = *(_Rb_tree_node_base **)(lVar6 + 0x78);
    p_Var19 = p_Var1;
    while (p_Var13 = p_Var20, p_Var13 != (_Rb_tree_node_base *)0x0) {
      if (*(uint *)(p_Var13 + 0x20) < uVar5) {
        p_Var20 = *(_Rb_tree_node_base **)(p_Var13 + 0x18);
      }
      else {
        p_Var20 = *(_Rb_tree_node_base **)(p_Var13 + 0x10);
        p_Var19 = p_Var13;
      }
    }
    if ((p_Var1 != p_Var19) && (*(uint *)(p_Var19 + 0x20) <= uVar5)) {
      sVar4 = *(short *)(p_Var19 + 0x24);
      *(short *)(p_Var19 + 0x24) = sVar4 + -1;
      if ((short)(sVar4 + -1) == 0) {
                    /* try { // try from 00c63c55 to 00c63dc8 has its CatchHandler @ 00c63eb5 */
        pvVar15 = (void *)std::_Rb_tree_rebalance_for_erase(p_Var19,p_Var1);
        operator_delete(pvVar15);
        pwVar11 = local_48[0];
        p_Var1 = (_Rb_tree_node_base *)(lVar6 + 0x40);
        *(long *)(lVar6 + 0x90) = *(long *)(lVar6 + 0x90) + -1;
        p_Var19 = *(_Rb_tree_node_base **)(lVar6 + 0x48);
        local_58 = p_Var1;
        if (p_Var19 != (_Rb_tree_node_base *)0x0) {
          uVar7 = *(ulong *)(local_48[0] + -6);
          do {
            uVar8 = *(ulong *)(*(wchar_t **)(p_Var19 + 0x20) + -6);
            uVar16 = uVar8;
            if (uVar7 <= uVar8) {
              uVar16 = uVar7;
            }
            iVar14 = wmemcmp(*(wchar_t **)(p_Var19 + 0x20),pwVar11,uVar16);
            if (iVar14 == 0) {
              lVar21 = uVar8 - uVar7;
              if (0x7fffffff < lVar21) goto LAB_00c63c9f;
              if (-0x80000001 < lVar21) {
                iVar14 = (int)lVar21;
                goto LAB_00c63c9b;
              }
LAB_00c63ce5:
              p_Var20 = *(_Rb_tree_node_base **)(p_Var19 + 0x18);
            }
            else {
LAB_00c63c9b:
              if (iVar14 < 0) goto LAB_00c63ce5;
LAB_00c63c9f:
              p_Var20 = *(_Rb_tree_node_base **)(p_Var19 + 0x10);
              local_58 = p_Var19;
            }
            p_Var19 = p_Var20;
          } while (p_Var19 != (_Rb_tree_node_base *)0x0);
        }
        if (p_Var1 == local_58) {
LAB_00c63e10:
          local_58 = p_Var1;
        }
        else {
          uVar7 = *(ulong *)(local_48[0] + -6);
          uVar8 = *(ulong *)(*(wchar_t **)(local_58 + 0x20) + -6);
          uVar16 = uVar7;
          if (uVar8 <= uVar7) {
            uVar16 = uVar8;
          }
          iVar14 = wmemcmp(local_48[0],*(wchar_t **)(local_58 + 0x20),uVar16);
          if (iVar14 == 0) {
            lVar21 = uVar7 - uVar8;
            if (lVar21 < 0x80000000) {
              if (lVar21 < -0x80000000) goto LAB_00c63e10;
              iVar14 = (int)lVar21;
              goto LAB_00c63e08;
            }
          }
          else {
LAB_00c63e08:
            if (iVar14 < 0) goto LAB_00c63e10;
          }
        }
        p_Var19 = (_Rb_tree_node_base *)(lVar6 + 0x10);
        p_Var13 = *(_Rb_tree_node_base **)(lVar6 + 0x18);
        p_Var20 = p_Var19;
        while (p_Var10 = p_Var13, p_Var10 != (_Rb_tree_node_base *)0x0) {
          if (*(uint *)(p_Var10 + 0x20) < uVar5) {
            p_Var13 = *(_Rb_tree_node_base **)(p_Var10 + 0x18);
          }
          else {
            p_Var13 = *(_Rb_tree_node_base **)(p_Var10 + 0x10);
            p_Var20 = p_Var10;
          }
        }
        if ((p_Var19 == p_Var20) || (uVar5 < *(uint *)(p_Var20 + 0x20))) {
          p_Var20 = p_Var19;
        }
        if ((p_Var1 != local_58) && (p_Var19 != p_Var20)) {
          pvVar15 = (void *)std::_Rb_tree_rebalance_for_erase(local_58,p_Var1);
          paVar18 = (allocator *)(*(long *)((long)pvVar15 + 0x20) + -0x18);
          if (paVar18 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(*(long *)((long)pvVar15 + 0x20) + -8);
            iVar14 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar14 < 1) {
              std::wstring::_Rep::_M_destroy(paVar18);
            }
          }
          operator_delete(pvVar15);
          *(long *)(lVar6 + 0x60) = *(long *)(lVar6 + 0x60) + -1;
          pvVar15 = (void *)std::_Rb_tree_rebalance_for_erase(p_Var20,p_Var19);
          paVar18 = (allocator *)(*(long *)((long)pvVar15 + 0x28) + -0x18);
          if (paVar18 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(*(long *)((long)pvVar15 + 0x28) + -8);
            iVar14 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar14 < 1) {
              std::wstring::_Rep::_M_destroy(paVar18);
            }
          }
          operator_delete(pvVar15);
          *(long *)(lVar6 + 0x30) = *(long *)(lVar6 + 0x30) + -1;
        }
      }
      paVar18 = (allocator *)(local_48[0] + -6);
    }
  }
  if (paVar18 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    paVar3 = paVar18 + 0x10;
    iVar14 = *(int *)paVar3;
    *(int *)paVar3 = *(int *)paVar3 + -1;
    UNLOCK();
    if (iVar14 < 1) {
      std::wstring::_Rep::_M_destroy(paVar18);
    }
  }
LAB_00c639a1:
  CRunicCore::~CRunicCore((CRunicCore *)this);
  return;
}

/* address=00c63fc0
   symbol=CDataValue::~CDataValue */

/* CDataValue::~CDataValue() */

void __thiscall CDataValue::~CDataValue(CDataValue *this)

{
  ~CDataValue(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}

/* address=00c63fe0
   symbol=CDataValue::SetDataValueName */

/* WARNING: Removing unreachable block (ram,0x00c6437d) */
/* WARNING: Removing unreachable block (ram,0x00c64388) */
/* WARNING: Removing unreachable block (ram,0x00c64308) */
/* CDataValue::SetDataValueName(std::wstring&) */

void __thiscall CDataValue::SetDataValueName(CDataValue *this,wstring_conflict *param_1)

{
  _Rb_tree_node_base *p_Var1;
  int *piVar2;
  allocator *paVar3;
  short sVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  ulong uVar8;
  long lVar9;
  _Rb_tree_node_base *p_Var10;
  wchar_t *__s2;
  long lVar11;
  _Rb_tree_node_base *p_Var12;
  undefined4 uVar13;
  int iVar14;
  void *pvVar15;
  ulong uVar16;
  wstring_conflict *pwVar17;
  allocator *paVar18;
  _Rb_tree_node_base *p_Var19;
  _Rb_tree_node_base *p_Var20;
  long lVar21;
  _Rb_tree_node_base *local_58;
  wchar_t *local_48 [3];

  if (*(TRepository<std::wstring> **)(this + 0x28) == (TRepository<std::wstring> *)0x0) {
    return;
  }
  uVar5 = *(uint *)(this + 0x20);
  uVar13 = TRepository<std::wstring>::addItem(*(TRepository<std::wstring> **)(this + 0x28),param_1);
  *(undefined4 *)(this + 0x20) = uVar13;
  lVar6 = *(long *)(this + 0x28);
  if ((uVar5 == 0xffffffff) || (*(long *)(lVar6 + 0x30) == 0)) {
LAB_00c6401d:
    pwVar17 = (wstring_conflict *)(lVar6 + 0x98);
  }
  else {
    lVar11 = *(long *)(lVar6 + 0x18);
    lVar21 = lVar6 + 0x10;
    while (lVar9 = lVar11, lVar9 != 0) {
      if (*(uint *)(lVar9 + 0x20) < uVar5) {
        lVar11 = *(long *)(lVar9 + 0x18);
      }
      else {
        lVar11 = *(long *)(lVar9 + 0x10);
        lVar21 = lVar9;
      }
    }
    if ((lVar6 + 0x10 == lVar21) || (uVar5 < *(uint *)(lVar21 + 0x20))) goto LAB_00c6401d;
    pwVar17 = (wstring_conflict *)(lVar21 + 0x28);
  }
  std::wstring::wstring((wstring_conflict *)local_48,pwVar17);
  paVar18 = (allocator *)(local_48[0] + -6);
  if ((*(size_t *)(local_48[0] + -6) == *(size_t *)(*(wchar_t **)(lVar6 + 0x98) + -6)) &&
     (iVar14 = wmemcmp(local_48[0],*(wchar_t **)(lVar6 + 0x98),*(size_t *)(local_48[0] + -6)),
     iVar14 == 0)) goto LAB_00c640a0;
  p_Var1 = (_Rb_tree_node_base *)(lVar6 + 0x70);
  p_Var20 = *(_Rb_tree_node_base **)(lVar6 + 0x78);
  p_Var19 = p_Var1;
  while (p_Var12 = p_Var20, p_Var12 != (_Rb_tree_node_base *)0x0) {
    if (*(uint *)(p_Var12 + 0x20) < uVar5) {
      p_Var20 = *(_Rb_tree_node_base **)(p_Var12 + 0x18);
    }
    else {
      p_Var20 = *(_Rb_tree_node_base **)(p_Var12 + 0x10);
      p_Var19 = p_Var12;
    }
  }
  if ((p_Var1 == p_Var19) || (uVar5 < *(uint *)(p_Var19 + 0x20))) goto LAB_00c640a0;
  sVar4 = *(short *)(p_Var19 + 0x24);
  *(short *)(p_Var19 + 0x24) = sVar4 + -1;
  if ((short)(sVar4 + -1) == 0) {
                    /* try { // try from 00c64110 to 00c64289 has its CatchHandler @ 00c642f3 */
    pvVar15 = (void *)std::_Rb_tree_rebalance_for_erase(p_Var19,p_Var1);
    operator_delete(pvVar15);
    __s2 = local_48[0];
    p_Var1 = (_Rb_tree_node_base *)(lVar6 + 0x40);
    *(long *)(lVar6 + 0x90) = *(long *)(lVar6 + 0x90) + -1;
    p_Var19 = *(_Rb_tree_node_base **)(lVar6 + 0x48);
    local_58 = p_Var1;
    if (p_Var19 != (_Rb_tree_node_base *)0x0) {
      uVar7 = *(ulong *)(local_48[0] + -6);
      do {
        uVar8 = *(ulong *)(*(wchar_t **)(p_Var19 + 0x20) + -6);
        uVar16 = uVar7;
        if (uVar8 <= uVar7) {
          uVar16 = uVar8;
        }
        iVar14 = wmemcmp(*(wchar_t **)(p_Var19 + 0x20),__s2,uVar16);
        if (iVar14 == 0) {
          lVar21 = uVar8 - uVar7;
          if (0x7fffffff < lVar21) goto LAB_00c64157;
          if (-0x80000001 < lVar21) {
            iVar14 = (int)lVar21;
            goto LAB_00c64153;
          }
LAB_00c6419d:
          p_Var20 = *(_Rb_tree_node_base **)(p_Var19 + 0x18);
        }
        else {
LAB_00c64153:
          if (iVar14 < 0) goto LAB_00c6419d;
LAB_00c64157:
          p_Var20 = *(_Rb_tree_node_base **)(p_Var19 + 0x10);
          local_58 = p_Var19;
        }
        p_Var19 = p_Var20;
      } while (p_Var19 != (_Rb_tree_node_base *)0x0);
    }
    if (p_Var1 == local_58) {
LAB_00c641f3:
      local_58 = p_Var1;
    }
    else {
      uVar7 = *(ulong *)(local_48[0] + -6);
      uVar8 = *(ulong *)(*(wchar_t **)(local_58 + 0x20) + -6);
      uVar16 = uVar7;
      if (uVar8 <= uVar7) {
        uVar16 = uVar8;
      }
      iVar14 = wmemcmp(local_48[0],*(wchar_t **)(local_58 + 0x20),uVar16);
      if (iVar14 == 0) {
        lVar21 = uVar7 - uVar8;
        if (lVar21 < 0x80000000) {
          if (lVar21 < -0x80000000) goto LAB_00c641f3;
          iVar14 = (int)lVar21;
          goto LAB_00c641ef;
        }
      }
      else {
LAB_00c641ef:
        if (iVar14 < 0) goto LAB_00c641f3;
      }
    }
    p_Var19 = (_Rb_tree_node_base *)(lVar6 + 0x10);
    p_Var12 = *(_Rb_tree_node_base **)(lVar6 + 0x18);
    p_Var20 = p_Var19;
    while (p_Var10 = p_Var12, p_Var10 != (_Rb_tree_node_base *)0x0) {
      if (*(uint *)(p_Var10 + 0x20) < uVar5) {
        p_Var12 = *(_Rb_tree_node_base **)(p_Var10 + 0x18);
      }
      else {
        p_Var12 = *(_Rb_tree_node_base **)(p_Var10 + 0x10);
        p_Var20 = p_Var10;
      }
    }
    if ((p_Var19 == p_Var20) || (uVar5 < *(uint *)(p_Var20 + 0x20))) {
      p_Var20 = p_Var19;
    }
    if ((p_Var1 != local_58) && (p_Var19 != p_Var20)) {
      pvVar15 = (void *)std::_Rb_tree_rebalance_for_erase(local_58,p_Var1);
      paVar18 = (allocator *)(*(long *)((long)pvVar15 + 0x20) + -0x18);
      if (paVar18 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(*(long *)((long)pvVar15 + 0x20) + -8);
        iVar14 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar14 < 1) {
          std::wstring::_Rep::_M_destroy(paVar18);
        }
      }
      operator_delete(pvVar15);
      *(long *)(lVar6 + 0x60) = *(long *)(lVar6 + 0x60) + -1;
      pvVar15 = (void *)std::_Rb_tree_rebalance_for_erase(p_Var20,p_Var19);
      paVar18 = (allocator *)(*(long *)((long)pvVar15 + 0x28) + -0x18);
      if (paVar18 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(*(long *)((long)pvVar15 + 0x28) + -8);
        iVar14 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar14 < 1) {
          std::wstring::_Rep::_M_destroy(paVar18);
        }
      }
      operator_delete(pvVar15);
      *(long *)(lVar6 + 0x30) = *(long *)(lVar6 + 0x30) + -1;
    }
  }
  paVar18 = (allocator *)(local_48[0] + -6);
LAB_00c640a0:
  if (paVar18 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    paVar3 = paVar18 + 0x10;
    iVar14 = *(int *)paVar3;
    *(int *)paVar3 = *(int *)paVar3 + -1;
    UNLOCK();
    if (iVar14 < 1) {
      std::wstring::_Rep::_M_destroy(paVar18);
    }
  }
  return;
}

/* address=00c643a0
   symbol=CDataValue::CDataValue */

/* WARNING: Removing unreachable block (ram,0x00c64468) */
/* CDataValue::CDataValue(wchar_t const*, TRepository<std::wstring >*) */

void __thiscall CDataValue::CDataValue(CDataValue *this,wchar_t *param_1,TRepository *param_2)

{
  int *piVar1;
  int iVar2;
  long local_28;
  allocator local_19;

  CRunicCore::CRunicCore((CRunicCore *)this);
  *(undefined ***)this = &PTR__CDataValue_00ff3590;
  this[0x10] = (CDataValue)0x0;
  *(undefined8 *)(this + 0x18) = 0;
  *(undefined4 *)(this + 0x20) = 0xffffffff;
  *(TRepository **)(this + 0x28) = param_2;
  *(undefined4 *)(this + 0x30) = 0;
                    /* try { // try from 00c643f1 to 00c643f5 has its CatchHandler @ 00c64463 */
  std::wstring::wstring((wstring_conflict *)&local_28,param_1,&local_19);
                    /* try { // try from 00c643fc to 00c64400 has its CatchHandler @ 00c64448 */
  SetDataValueName(this,(wstring_conflict *)&local_28);
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
  return;
}

/* address=00c64480
   symbol=CDataValue::SetValueString */

/* WARNING: Removing unreachable block (ram,0x00c64879) */
/* WARNING: Removing unreachable block (ram,0x00c64900) */
/* WARNING: Removing unreachable block (ram,0x00c648f5) */
/* WARNING: Removing unreachable block (ram,0x00c6486e) */
/* CDataValue::SetValueString(wchar_t const*) */

void __thiscall CDataValue::SetValueString(CDataValue *this,wchar_t *param_1)

{
  int *piVar1;
  allocator *paVar2;
  _Rb_tree_node_base *p_Var3;
  short sVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  ulong uVar8;
  long lVar9;
  _Rb_tree_node_base *p_Var10;
  wchar_t *__s2;
  long lVar11;
  _Rb_tree_node_base *p_Var12;
  undefined4 uVar13;
  int iVar14;
  void *pvVar15;
  ulong uVar16;
  wstring_conflict *pwVar17;
  allocator *paVar18;
  _Rb_tree_node_base *p_Var19;
  _Rb_tree_node_base *p_Var20;
  long lVar21;
  _Rb_tree_node_base *local_68;
  wchar_t *local_58 [2];
  long local_48;
  allocator local_39 [9];

  if (param_1 == (wchar_t *)0x0) {
    return;
  }
  if ((*(int *)(this + 0x30) != 8) && (*(int *)(this + 0x30) != 5)) {
    *(undefined4 *)(this + 0x30) = 5;
  }
  this[0x10] = (CDataValue)0x1;
  if (*(long *)(this + 0x28) == 0) {
    return;
  }
                    /* try { // try from 00c644bf to 00c644c3 has its CatchHandler @ 00c64886 */
  std::wstring::wstring((wstring_conflict *)&local_48,param_1,local_39);
  uVar5 = *(uint *)(this + 0x18);
  if ((int)uVar5 < 1) goto LAB_00c64579;
  lVar6 = *(long *)(this + 0x28);
  if (*(long *)(lVar6 + 0x30) == 0) {
LAB_00c644df:
    pwVar17 = (wstring_conflict *)(lVar6 + 0x98);
  }
  else {
    lVar11 = *(long *)(lVar6 + 0x18);
    lVar21 = lVar6 + 0x10;
    while (lVar9 = lVar11, lVar9 != 0) {
      if (*(uint *)(lVar9 + 0x20) < uVar5) {
        lVar11 = *(long *)(lVar9 + 0x18);
      }
      else {
        lVar11 = *(long *)(lVar9 + 0x10);
        lVar21 = lVar9;
      }
    }
    if ((lVar6 + 0x10 == lVar21) || (uVar5 < *(uint *)(lVar21 + 0x20))) goto LAB_00c644df;
    pwVar17 = (wstring_conflict *)(lVar21 + 0x28);
  }
                    /* try { // try from 00c644ec to 00c64586 has its CatchHandler @ 00c6488e */
  std::wstring::wstring((wstring_conflict *)local_58,pwVar17);
  paVar18 = (allocator *)(local_58[0] + -6);
  if ((*(size_t *)(local_58[0] + -6) != *(size_t *)(*(wchar_t **)(lVar6 + 0x98) + -6)) ||
     (iVar14 = wmemcmp(local_58[0],*(wchar_t **)(lVar6 + 0x98),*(size_t *)(local_58[0] + -6)),
     iVar14 != 0)) {
    p_Var3 = (_Rb_tree_node_base *)(lVar6 + 0x70);
    p_Var20 = *(_Rb_tree_node_base **)(lVar6 + 0x78);
    p_Var19 = p_Var3;
    while (p_Var12 = p_Var20, p_Var12 != (_Rb_tree_node_base *)0x0) {
      if (*(uint *)(p_Var12 + 0x20) < uVar5) {
        p_Var20 = *(_Rb_tree_node_base **)(p_Var12 + 0x18);
      }
      else {
        p_Var20 = *(_Rb_tree_node_base **)(p_Var12 + 0x10);
        p_Var19 = p_Var12;
      }
    }
    if ((p_Var3 != p_Var19) && (*(uint *)(p_Var19 + 0x20) <= uVar5)) {
      sVar4 = *(short *)(p_Var19 + 0x24);
      *(short *)(p_Var19 + 0x24) = sVar4 + -1;
      if ((short)(sVar4 + -1) == 0) {
                    /* try { // try from 00c64638 to 00c647b1 has its CatchHandler @ 00c64822 */
        pvVar15 = (void *)std::_Rb_tree_rebalance_for_erase(p_Var19,p_Var3);
        operator_delete(pvVar15);
        __s2 = local_58[0];
        p_Var3 = (_Rb_tree_node_base *)(lVar6 + 0x40);
        *(long *)(lVar6 + 0x90) = *(long *)(lVar6 + 0x90) + -1;
        p_Var19 = *(_Rb_tree_node_base **)(lVar6 + 0x48);
        local_68 = p_Var3;
        if (p_Var19 != (_Rb_tree_node_base *)0x0) {
          uVar7 = *(ulong *)(local_58[0] + -6);
          do {
            uVar8 = *(ulong *)(*(wchar_t **)(p_Var19 + 0x20) + -6);
            uVar16 = uVar8;
            if (uVar7 <= uVar8) {
              uVar16 = uVar7;
            }
            iVar14 = wmemcmp(*(wchar_t **)(p_Var19 + 0x20),__s2,uVar16);
            if (iVar14 == 0) {
              lVar21 = uVar8 - uVar7;
              if (0x7fffffff < lVar21) goto LAB_00c64687;
              if (-0x80000001 < lVar21) {
                iVar14 = (int)lVar21;
                goto LAB_00c64683;
              }
LAB_00c646cd:
              p_Var20 = *(_Rb_tree_node_base **)(p_Var19 + 0x18);
            }
            else {
LAB_00c64683:
              if (iVar14 < 0) goto LAB_00c646cd;
LAB_00c64687:
              p_Var20 = *(_Rb_tree_node_base **)(p_Var19 + 0x10);
              local_68 = p_Var19;
            }
            p_Var19 = p_Var20;
          } while (p_Var19 != (_Rb_tree_node_base *)0x0);
        }
        if (p_Var3 == local_68) {
LAB_00c647ef:
          local_68 = p_Var3;
        }
        else {
          uVar7 = *(ulong *)(local_58[0] + -6);
          uVar8 = *(ulong *)(*(wchar_t **)(local_68 + 0x20) + -6);
          uVar16 = uVar7;
          if (uVar8 <= uVar7) {
            uVar16 = uVar8;
          }
          iVar14 = wmemcmp(local_58[0],*(wchar_t **)(local_68 + 0x20),uVar16);
          if (iVar14 == 0) {
            lVar21 = uVar7 - uVar8;
            if (lVar21 < 0x80000000) {
              if (lVar21 < -0x80000000) goto LAB_00c647ef;
              iVar14 = (int)lVar21;
              goto LAB_00c647e7;
            }
          }
          else {
LAB_00c647e7:
            if (iVar14 < 0) goto LAB_00c647ef;
          }
        }
        p_Var19 = (_Rb_tree_node_base *)(lVar6 + 0x10);
        p_Var12 = *(_Rb_tree_node_base **)(lVar6 + 0x18);
        p_Var20 = p_Var19;
        while (p_Var10 = p_Var12, p_Var10 != (_Rb_tree_node_base *)0x0) {
          if (*(uint *)(p_Var10 + 0x20) < uVar5) {
            p_Var12 = *(_Rb_tree_node_base **)(p_Var10 + 0x18);
          }
          else {
            p_Var12 = *(_Rb_tree_node_base **)(p_Var10 + 0x10);
            p_Var20 = p_Var10;
          }
        }
        if ((p_Var19 == p_Var20) || (uVar5 < *(uint *)(p_Var20 + 0x20))) {
          p_Var20 = p_Var19;
        }
        if ((p_Var3 != local_68) && (p_Var19 != p_Var20)) {
          pvVar15 = (void *)std::_Rb_tree_rebalance_for_erase(local_68,p_Var3);
          paVar18 = (allocator *)(*(long *)((long)pvVar15 + 0x20) + -0x18);
          if (paVar18 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(*(long *)((long)pvVar15 + 0x20) + -8);
            iVar14 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar14 < 1) {
              std::wstring::_Rep::_M_destroy(paVar18);
            }
          }
          operator_delete(pvVar15);
          *(long *)(lVar6 + 0x60) = *(long *)(lVar6 + 0x60) + -1;
          pvVar15 = (void *)std::_Rb_tree_rebalance_for_erase(p_Var20,p_Var19);
          paVar18 = (allocator *)(*(long *)((long)pvVar15 + 0x28) + -0x18);
          if (paVar18 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(*(long *)((long)pvVar15 + 0x28) + -8);
            iVar14 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar14 < 1) {
              std::wstring::_Rep::_M_destroy(paVar18);
            }
          }
          operator_delete(pvVar15);
          *(long *)(lVar6 + 0x30) = *(long *)(lVar6 + 0x30) + -1;
        }
      }
      paVar18 = (allocator *)(local_58[0] + -6);
    }
  }
  if (paVar18 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    paVar2 = paVar18 + 0x10;
    iVar14 = *(int *)paVar2;
    *(int *)paVar2 = *(int *)paVar2 + -1;
    UNLOCK();
    if (iVar14 < 1) {
      std::wstring::_Rep::_M_destroy(paVar18);
    }
  }
LAB_00c64579:
  uVar13 = TRepository<std::wstring>::addItem
                     (*(TRepository<std::wstring> **)(this + 0x28),(wstring_conflict *)&local_48);
  *(undefined4 *)(this + 0x18) = uVar13;
  if ((allocator *)(local_48 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_48 + -8);
    iVar14 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar14 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_48 + -0x18));
    }
  }
  return;
}

/* address=00c64910
   symbol=CDataValue::SetValueByString */

/* CDataValue::SetValueByString(std::wstring const&, std::wstring&) */

void __thiscall
CDataValue::SetValueByString(CDataValue *this,wstring_conflict *param_1,wstring_conflict *param_2)

{
  undefined8 uVar1;
  CDataValue CVar2;
  int iVar3;
  undefined4 uVar4;

  iVar3 = std::wstring::compare((wchar_t *)param_1);
  if (iVar3 == 0) {
    uVar4 = STRINGS::GetInt(param_2);
    *(undefined4 *)(this + 0x30) = 1;
    *(undefined4 *)(this + 0x18) = uVar4;
  }
  else {
    iVar3 = std::wstring::compare((wchar_t *)param_1);
    if (iVar3 == 0) {
      uVar1 = STRINGS::GetInt64(param_2);
      *(undefined4 *)(this + 0x30) = 7;
      *(undefined8 *)(this + 0x18) = uVar1;
    }
    else {
      iVar3 = std::wstring::compare((wchar_t *)param_1);
      if (iVar3 == 0) {
        uVar4 = STRINGS::GetFloat(param_2);
        *(undefined4 *)(this + 0x30) = 2;
        *(undefined4 *)(this + 0x18) = uVar4;
      }
      else {
        iVar3 = std::wstring::compare((wchar_t *)param_1);
        if (iVar3 == 0) {
          uVar1 = STRINGS::GetFloat64(param_2);
          *(undefined4 *)(this + 0x30) = 3;
          *(undefined8 *)(this + 0x18) = uVar1;
        }
        else {
          iVar3 = std::wstring::compare((wchar_t *)param_1);
          if (iVar3 == 0) {
            uVar4 = STRINGS::GetInt(param_2);
            *(undefined4 *)(this + 0x30) = 4;
            *(undefined4 *)(this + 0x18) = uVar4;
          }
          else {
            iVar3 = std::wstring::compare((wchar_t *)param_1);
            if (iVar3 == 0) {
              CVar2 = (CDataValue)STRINGS::GetBool(param_2);
              *(undefined4 *)(this + 0x30) = 6;
              this[0x18] = CVar2;
            }
            else {
              iVar3 = std::wstring::compare((wchar_t *)param_1);
              if (iVar3 != 0) {
                iVar3 = std::wstring::compare((wchar_t *)param_1);
                if (iVar3 != 0) {
                  *(undefined4 *)(this + 0x18) = 0xffffffff;
                  SetValueString(this,*(wchar_t **)param_2);
                  return;
                }
              }
              *(undefined4 *)(this + 0x18) = 0xffffffff;
              SetValueString(this,*(wchar_t **)param_2);
              *(undefined4 *)(this + 0x30) = 8;
            }
          }
        }
      }
    }
  }
  return;
}

/* address=00c64ad0
   symbol=CDataValue::SetValueTranslate */

/* CDataValue::SetValueTranslate(wchar_t const*) */

void __thiscall CDataValue::SetValueTranslate(CDataValue *this,wchar_t *param_1)

{
  *(undefined4 *)(this + 0x30) = 8;
  SetValueString(this,param_1);
  return;
}

/* address=00c64ae0
   symbol=CDataValue::Copy */

/* CDataValue::Copy(CDataValue*, TRepository<std::wstring >*) */

void __thiscall CDataValue::Copy(CDataValue *this,CDataValue *param_1,TRepository *param_2)

{
  wstring_conflict *pwVar1;
  undefined8 *puVar2;

  if (param_1 != (CDataValue *)0x0) {
    *(TRepository **)(this + 0x28) = param_2;
    pwVar1 = (wstring_conflict *)GetDataValueName(param_1);
    SetDataValueName(this,pwVar1);
    *(undefined4 *)(this + 0x30) = *(undefined4 *)(param_1 + 0x30);
    if (param_1[0x10] != (CDataValue)0x0) {
      *(undefined4 *)(this + 0x18) = 0xffffffff;
      puVar2 = (undefined8 *)GetValueString(param_1,true);
      SetValueString(this,(wchar_t *)*puVar2);
      return;
    }
    *(undefined8 *)(this + 0x18) = *(undefined8 *)(param_1 + 0x18);
  }
  return;
}

/* address=00c64b70
   symbol=CDataValue::CDataValue */

/* CDataValue::CDataValue(CDataValue*, TRepository<std::wstring >*) */

void __thiscall CDataValue::CDataValue(CDataValue *this,CDataValue *param_1,TRepository *param_2)

{
  CRunicCore::CRunicCore((CRunicCore *)this);
  *(undefined ***)this = &PTR__CDataValue_00ff3590;
  this[0x10] = (CDataValue)0x0;
  *(undefined8 *)(this + 0x18) = 0;
  *(undefined4 *)(this + 0x20) = 0xffffffff;
  *(TRepository **)(this + 0x28) = param_2;
  *(undefined4 *)(this + 0x30) = 0;
                    /* try { // try from 00c64bbf to 00c64bc3 has its CatchHandler @ 00c64bd7 */
  Copy(this,param_1,param_2);
  return;
}

/* export-summary functions=28 failures=0 */
