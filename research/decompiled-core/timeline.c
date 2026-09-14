/* Targeted Ghidra class export.
   namespace=CTimeline
   Treat pseudocode as navigation evidence. */


/* address=007b6540
   symbol=CTimeline::setDurationModificationTime */

/* CTimeline::setDurationModificationTime(float) */

void __thiscall CTimeline::setDurationModificationTime(CTimeline *this,float param_1)

{
  if (*(int *)(this + 0xa8) == 1) {
    *(float *)(this + 0x94) = param_1;
    return;
  }
  if (*(int *)(this + 0xa8) != 2) {
    return;
  }
  *(float *)(this + 0x94) = param_1 * *(float *)(this + 0x94);
  return;
}

/* address=007b6580
   symbol=CTimeline::Pause */

/* CTimeline::Pause() */

void __thiscall CTimeline::Pause(CTimeline *this)

{
  if (this[0xa1] == (CTimeline)0x0) {
    return;
  }
  this[0xa1] = (CTimeline)0x0;
                    /* WARNING: Could not recover jumptable at 0x007b65a3. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)this + 0x30))(this,0x25);
  return;
}

/* address=007b65b0
   symbol=CTimeline::GetProperty */

/* CTimeline::GetProperty(long long, int, bool) */

undefined8 __thiscall
CTimeline::GetProperty(CTimeline *this,longlong param_1,int param_2,bool param_3)

{
  long lVar1;
  CTimeline *pCVar2;
  CTimeline *pCVar3;
  long lVar4;
  long lVar5;
  CTimeline *pCVar6;

  if ((param_2 != -1) && (param_1 != -1)) {
    pCVar6 = *(CTimeline **)(this + 0x68);
    pCVar3 = this + 0x60;
    while (pCVar2 = pCVar6, pCVar2 != (CTimeline *)0x0) {
      if (*(long *)(pCVar2 + 0x20) < param_1) {
        pCVar6 = *(CTimeline **)(pCVar2 + 0x18);
      }
      else {
        pCVar6 = *(CTimeline **)(pCVar2 + 0x10);
        pCVar3 = pCVar2;
      }
    }
    if ((this + 0x60 != pCVar3) && (*(long *)(pCVar3 + 0x20) <= param_1)) {
      lVar1 = *(long *)(pCVar3 + 0x28) + 8;
      lVar4 = lVar1;
      lVar5 = *(long *)(*(long *)(pCVar3 + 0x28) + 0x10);
      while (lVar5 != 0) {
        if ((*(int *)(lVar5 + 0x20) < param_2) ||
           ((*(int *)(lVar5 + 0x20) <= param_2 && (*(byte *)(lVar5 + 0x24) < param_3)))) {
          lVar5 = *(long *)(lVar5 + 0x18);
        }
        else {
          lVar4 = lVar5;
          lVar5 = *(long *)(lVar5 + 0x10);
        }
      }
      if (((lVar1 != lVar4) && (*(int *)(lVar4 + 0x20) <= param_2)) &&
         ((*(int *)(lVar4 + 0x20) < param_2 || (*(byte *)(lVar4 + 0x24) <= param_3)))) {
        return *(undefined8 *)(lVar4 + 0x28);
      }
    }
  }
  return 0;
}

/* address=007b6680
   symbol=CTimeline::GetNumberOfPropertiesForObjectInTimeline */

/* CTimeline::GetNumberOfPropertiesForObjectInTimeline(long long) */

undefined4 __thiscall
CTimeline::GetNumberOfPropertiesForObjectInTimeline(CTimeline *this,longlong param_1)

{
  CTimeline *pCVar1;
  CTimeline *pCVar2;
  CTimeline *pCVar3;

  if (param_1 != -1) {
    pCVar3 = *(CTimeline **)(this + 0x68);
    pCVar2 = this + 0x60;
    while (pCVar1 = pCVar3, pCVar1 != (CTimeline *)0x0) {
      if (*(long *)(pCVar1 + 0x20) < param_1) {
        pCVar3 = *(CTimeline **)(pCVar1 + 0x18);
      }
      else {
        pCVar3 = *(CTimeline **)(pCVar1 + 0x10);
        pCVar2 = pCVar1;
      }
    }
    if ((this + 0x60 != pCVar2) && (*(long *)(pCVar2 + 0x20) <= param_1)) {
      return *(undefined4 *)(*(long *)(pCVar2 + 0x28) + 0x28);
    }
  }
  return 0;
}

/* address=007b66e0
   symbol=CTimeline::GetNumberOfPointsForAProperty */

/* CTimeline::GetNumberOfPointsForAProperty(long long, int, bool) */

int __thiscall
CTimeline::GetNumberOfPointsForAProperty(CTimeline *this,longlong param_1,int param_2,bool param_3)

{
  int iVar1;
  long lVar2;

  if ((-1 < param_2) && (param_1 != -1)) {
    lVar2 = GetProperty(this,param_1,param_2,param_3);
    if ((lVar2 != 0) && (lVar2 = *(long *)(lVar2 + 0x40), lVar2 != 0)) {
      iVar1 = 0;
      do {
        lVar2 = *(long *)(lVar2 + 8);
        iVar1 = iVar1 + 1;
      } while (lVar2 != 0);
      return iVar1;
    }
  }
  return 0;
}

/* address=007b6720
   symbol=CTimeline::SetEnabled */

/* CTimeline::SetEnabled(bool) */

void __thiscall CTimeline::SetEnabled(CTimeline *this,bool param_1)

{
  this[0xa1] = (CTimeline)param_1;
  return;
}

/* address=007b6730
   symbol=CTimeline::GetPropertyPointInterpolationType */

/* CTimeline::GetPropertyPointInterpolationType(long long, int) */

longlong CTimeline::GetPropertyPointInterpolationType(longlong param_1,int param_2)

{
  long lVar1;
  int in_ECX;
  longlong in_RDX;
  undefined4 in_register_00000034;

  lVar1 = GetProperty((CTimeline *)CONCAT44(in_register_00000034,param_2),in_RDX,in_ECX,false);
  if (lVar1 != 0) {
    std::wstring::wstring
              ((wstring_conflict *)param_1,
               (wstring_conflict *)(&gTIMELINE_INTERP_TYPES + *(int *)(lVar1 + 0x48)));
    return param_1;
  }
  std::wstring::wstring((wstring_conflict *)param_1,(wstring_conflict *)&gTIMELINE_INTERP_TYPES);
  return param_1;
}

/* address=007b6780
   symbol=CTimeline::SetPropertyPointValue */

/* CTimeline::SetPropertyPointValue(long long, int, int, void*, unsigned int) */

void __thiscall
CTimeline::SetPropertyPointValue
          (CTimeline *this,longlong param_1,int param_2,int param_3,void *param_4,uint param_5)

{
  CTimelineProperty *this_00;

  this_00 = (CTimelineProperty *)GetProperty(this,param_1,param_2,false);
  if (this_00 != (CTimelineProperty *)0x0) {
    CTimelineProperty::SetValueAtPoint(this_00,param_3,param_4,param_5);
    return;
  }
  return;
}

/* address=007b67f0
   symbol=CTimeline::GetPropertyPointTimePercent */

/* CTimeline::GetPropertyPointTimePercent(long long, int, int, bool) */

undefined8 __thiscall
CTimeline::GetPropertyPointTimePercent
          (CTimeline *this,longlong param_1,int param_2,int param_3,bool param_4)

{
  CTimelineProperty *this_00;
  undefined8 uVar1;

  this_00 = (CTimelineProperty *)GetProperty(this,param_1,param_2,param_4);
  if (this_00 != (CTimelineProperty *)0x0) {
    uVar1 = CTimelineProperty::GetTimePercentAtPoint(this_00,param_3);
    return uVar1;
  }
  return 0;
}

/* address=007b6820
   symbol=CTimeline::GetPropertyPointValue */

/* CTimeline::GetPropertyPointValue(long long, int, int, unsigned int&) */

void __thiscall
CTimeline::GetPropertyPointValue
          (CTimeline *this,longlong param_1,int param_2,int param_3,uint *param_4)

{
  CTimelineProperty *this_00;

  this_00 = (CTimelineProperty *)GetProperty(this,param_1,param_2,false);
  if (this_00 != (CTimelineProperty *)0x0) {
    CTimelineProperty::GetValueAtPoint(this_00,param_3,param_4);
    return;
  }
  return;
}

/* address=007b6870
   symbol=CTimeline::SetPropertyPointTimePercent */

/* CTimeline::SetPropertyPointTimePercent(long long, int, int, float, bool) */

void __thiscall
CTimeline::SetPropertyPointTimePercent
          (CTimeline *this,longlong param_1,int param_2,int param_3,float param_4,bool param_5)

{
  CTimelineProperty *this_00;

  this_00 = (CTimelineProperty *)GetProperty(this,param_1,param_2,param_5);
  if (this_00 != (CTimelineProperty *)0x0) {
    CTimelineProperty::SetTimePercentAtPoint(this_00,param_3,param_4);
    return;
  }
  return;
}

/* address=007b68b0
   symbol=CTimeline::SetPropertyPointValueByString */

/* CTimeline::SetPropertyPointValueByString(long long, int, int, std::wstring&) */

void __thiscall
CTimeline::SetPropertyPointValueByString
          (CTimeline *this,longlong param_1,int param_2,int param_3,wstring_conflict *param_4)

{
  CTimelineProperty *this_00;

  this_00 = (CTimelineProperty *)GetProperty(this,param_1,param_2,false);
  if (this_00 != (CTimelineProperty *)0x0) {
    CTimelineProperty::SetValueAtPointByString(this_00,param_3,param_4);
    return;
  }
  return;
}

/* address=007b6900
   symbol=CTimeline::SetPropertyPointInterpolationType */

/* CTimeline::SetPropertyPointInterpolationType(long long, int, ETIMELINE_INTERP_TYPES) */

void __thiscall
CTimeline::SetPropertyPointInterpolationType
          (CTimeline *this,longlong param_1,int param_2,undefined4 param_4)

{
  CTimelineProperty *pCVar1;

  pCVar1 = (CTimelineProperty *)GetProperty(this,param_1,param_2,false);
  if (pCVar1 != (CTimelineProperty *)0x0) {
    CTimelineProperty::SetInterpolationType(pCVar1,param_4);
    return;
  }
  return;
}

/* address=007b6930
   symbol=CTimeline::RemovePointFromProperty */

/* CTimeline::RemovePointFromProperty(long long, int, int, bool) */

undefined8 __thiscall
CTimeline::RemovePointFromProperty
          (CTimeline *this,longlong param_1,int param_2,int param_3,bool param_4)

{
  CTimelineProperty *this_00;
  undefined8 uVar1;

  this_00 = (CTimelineProperty *)GetProperty(this,param_1,param_2,param_4);
  if (this_00 != (CTimelineProperty *)0x0) {
    uVar1 = CTimelineProperty::RemovePoint(this_00,param_3);
    return uVar1;
  }
  return 1;
}

/* address=007b6960
   symbol=CTimeline::AddPointToProperty */

/* CTimeline::AddPointToProperty(long long, int, bool) */

undefined8 __thiscall
CTimeline::AddPointToProperty(CTimeline *this,longlong param_1,int param_2,bool param_3)

{
  CTimelineProperty *this_00;
  undefined8 uVar1;

  this_00 = (CTimelineProperty *)GetProperty(this,param_1,param_2,param_3);
  if (this_00 != (CTimelineProperty *)0x0) {
    uVar1 = CTimelineProperty::AddPoint(this_00);
    return uVar1;
  }
  return 0xffffffff;
}

/* address=007b6990
   symbol=CTimeline::RemoveProperty */

/* CTimeline::RemoveProperty(long long, int, bool) */

undefined8 __thiscall
CTimeline::RemoveProperty(CTimeline *this,longlong param_1,int param_2,bool param_3)

{
  CTimeline *pCVar1;
  CTimeline *pCVar2;
  _Rb_tree_node_base *p_Var3;
  _Rb_tree_node_base *p_Var4;
  _Rb_tree_node_base *p_Var5;
  void *pvVar6;
  long lVar7;
  _Rb_tree_node_base *p_Var8;

  pCVar2 = this + 0x60;
  pCVar1 = *(CTimeline **)(this + 0x68);
  while (pCVar1 != (CTimeline *)0x0) {
    if (*(long *)(pCVar1 + 0x20) < param_1) {
      pCVar1 = *(CTimeline **)(pCVar1 + 0x18);
    }
    else {
      pCVar2 = pCVar1;
      pCVar1 = *(CTimeline **)(pCVar1 + 0x10);
    }
  }
  if ((this + 0x60 != pCVar2) && (*(long *)(pCVar2 + 0x20) <= param_1)) {
    lVar7 = *(long *)(pCVar2 + 0x28);
    p_Var8 = (_Rb_tree_node_base *)(lVar7 + 8);
    p_Var5 = *(_Rb_tree_node_base **)(lVar7 + 0x10);
    p_Var4 = p_Var8;
    while (p_Var3 = p_Var5, p_Var3 != (_Rb_tree_node_base *)0x0) {
      if ((*(int *)(p_Var3 + 0x20) < param_2) ||
         ((*(int *)(p_Var3 + 0x20) <= param_2 && ((byte)p_Var3[0x24] < param_3)))) {
        p_Var5 = *(_Rb_tree_node_base **)(p_Var3 + 0x18);
      }
      else {
        p_Var5 = *(_Rb_tree_node_base **)(p_Var3 + 0x10);
        p_Var4 = p_Var3;
      }
    }
    if (((p_Var8 != p_Var4) && (*(int *)(p_Var4 + 0x20) <= param_2)) &&
       ((*(int *)(p_Var4 + 0x20) < param_2 || ((byte)p_Var4[0x24] <= param_3)))) {
      if (*(long **)(p_Var4 + 0x28) != (long *)0x0) {
        (**(code **)(**(long **)(p_Var4 + 0x28) + 8))();
        *(undefined8 *)(p_Var4 + 0x28) = 0;
        lVar7 = *(long *)(pCVar2 + 0x28);
        p_Var8 = (_Rb_tree_node_base *)(lVar7 + 8);
      }
      pvVar6 = (void *)std::_Rb_tree_rebalance_for_erase(p_Var4,p_Var8);
      operator_delete(pvVar6);
      *(long *)(lVar7 + 0x28) = *(long *)(lVar7 + 0x28) + -1;
      return 1;
    }
  }
  return 0;
}

/* address=007b6a90
   symbol=CTimeline::RemoveObjectByID */

/* CTimeline::RemoveObjectByID(long long) */

undefined8 __thiscall CTimeline::RemoveObjectByID(CTimeline *this,longlong param_1)

{
  _Rb_tree_node_base *p_Var1;
  _Rb_tree<std::pair<int,bool>,std::pair<std::pair<int,bool>const,CTimelineProperty*>,std::_Select1st<std::pair<std::pair<int,bool>const,CTimelineProperty*>>,std::less<std::pair<int,bool>>,std::allocator<std::pair<std::pair<int,bool>const,CTimelineProperty*>>>
  *p_Var2;
  _Rb_tree<std::pair<int,bool>,std::pair<std::pair<int,bool>const,CTimelineProperty*>,std::_Select1st<std::pair<std::pair<int,bool>const,CTimelineProperty*>>,std::less<std::pair<int,bool>>,std::allocator<std::pair<std::pair<int,bool>const,CTimelineProperty*>>>
  *this_00;
  _Rb_tree_node_base *p_Var3;
  _Rb_tree_node_base *p_Var4;
  _Rb_tree_node_base *p_Var5;
  void *pvVar6;
  undefined8 uVar7;

  uVar7 = 0;
  if (param_1 != -1) {
    p_Var1 = (_Rb_tree_node_base *)(this + 0x60);
    p_Var5 = *(_Rb_tree_node_base **)(this + 0x68);
    p_Var4 = p_Var1;
    while (p_Var3 = p_Var5, p_Var3 != (_Rb_tree_node_base *)0x0) {
      if (*(long *)(p_Var3 + 0x20) < param_1) {
        p_Var5 = *(_Rb_tree_node_base **)(p_Var3 + 0x18);
      }
      else {
        p_Var5 = *(_Rb_tree_node_base **)(p_Var3 + 0x10);
        p_Var4 = p_Var3;
      }
    }
    if ((p_Var1 == p_Var4) || (param_1 < *(long *)(p_Var4 + 0x20))) {
      return 1;
    }
    this_00 = *(_Rb_tree<std::pair<int,bool>,std::pair<std::pair<int,bool>const,CTimelineProperty*>,std::_Select1st<std::pair<std::pair<int,bool>const,CTimelineProperty*>>,std::less<std::pair<int,bool>>,std::allocator<std::pair<std::pair<int,bool>const,CTimelineProperty*>>>
                **)(p_Var4 + 0x28);
    p_Var2 = this_00 + 8;
    for (p_Var5 = *(_Rb_tree_node_base **)(this_00 + 0x18);
        p_Var2 != (_Rb_tree<std::pair<int,bool>,std::pair<std::pair<int,bool>const,CTimelineProperty*>,std::_Select1st<std::pair<std::pair<int,bool>const,CTimelineProperty*>>,std::less<std::pair<int,bool>>,std::allocator<std::pair<std::pair<int,bool>const,CTimelineProperty*>>>
                   *)p_Var5; p_Var5 = (_Rb_tree_node_base *)std::_Rb_tree_increment(p_Var5)) {
      if (*(long **)(p_Var5 + 0x28) != (long *)0x0) {
        (**(code **)(**(long **)(p_Var5 + 0x28) + 8))();
        *(undefined8 *)(p_Var5 + 0x28) = 0;
      }
    }
    std::
    _Rb_tree<std::pair<int,bool>,std::pair<std::pair<int,bool>const,CTimelineProperty*>,std::_Select1st<std::pair<std::pair<int,bool>const,CTimelineProperty*>>,std::less<std::pair<int,bool>>,std::allocator<std::pair<std::pair<int,bool>const,CTimelineProperty*>>>
    ::_M_erase(this_00,*(_Rb_tree_node **)(this_00 + 0x10));
    *(_Rb_tree<std::pair<int,bool>,std::pair<std::pair<int,bool>const,CTimelineProperty*>,std::_Select1st<std::pair<std::pair<int,bool>const,CTimelineProperty*>>,std::less<std::pair<int,bool>>,std::allocator<std::pair<std::pair<int,bool>const,CTimelineProperty*>>>
      **)(this_00 + 0x18) = p_Var2;
    *(undefined8 *)(this_00 + 0x10) = 0;
    *(_Rb_tree<std::pair<int,bool>,std::pair<std::pair<int,bool>const,CTimelineProperty*>,std::_Select1st<std::pair<std::pair<int,bool>const,CTimelineProperty*>>,std::less<std::pair<int,bool>>,std::allocator<std::pair<std::pair<int,bool>const,CTimelineProperty*>>>
      **)(this_00 + 0x20) = p_Var2;
    *(undefined8 *)(this_00 + 0x28) = 0;
    pvVar6 = (void *)std::_Rb_tree_rebalance_for_erase(p_Var4,p_Var1);
    operator_delete(pvVar6);
    *(long *)(this + 0x80) = *(long *)(this + 0x80) + -1;
                    /* try { // try from 007b6b75 to 007b6b79 has its CatchHandler @ 007b6bb4 */
    std::
    _Rb_tree<std::pair<int,bool>,std::pair<std::pair<int,bool>const,CTimelineProperty*>,std::_Select1st<std::pair<std::pair<int,bool>const,CTimelineProperty*>>,std::less<std::pair<int,bool>>,std::allocator<std::pair<std::pair<int,bool>const,CTimelineProperty*>>>
    ::_M_erase(this_00,*(_Rb_tree_node **)(this_00 + 0x10));
    operator_delete(this_00);
    uVar7 = 1;
  }
  return uVar7;
}

/* address=007b6bc0
   symbol=CTimeline::GetPropertyIDForObjectInTimelineByIndex */

/* CTimeline::GetPropertyIDForObjectInTimelineByIndex(long long, int) */

undefined8 __thiscall
CTimeline::GetPropertyIDForObjectInTimelineByIndex(CTimeline *this,longlong param_1,int param_2)

{
  long lVar1;
  CTimeline *pCVar2;
  CTimeline *pCVar3;
  CTimeline *pCVar4;
  _Rb_tree_node_base *p_Var5;

  if ((-1 < param_2) && (param_1 != -1)) {
    pCVar4 = *(CTimeline **)(this + 0x68);
    pCVar3 = this + 0x60;
    while (pCVar2 = pCVar4, pCVar2 != (CTimeline *)0x0) {
      if (*(long *)(pCVar2 + 0x20) < param_1) {
        pCVar4 = *(CTimeline **)(pCVar2 + 0x18);
      }
      else {
        pCVar4 = *(CTimeline **)(pCVar2 + 0x10);
        pCVar3 = pCVar2;
      }
    }
    if (((this + 0x60 != pCVar3) && (*(long *)(pCVar3 + 0x20) <= param_1)) &&
       (lVar1 = *(long *)(pCVar3 + 0x28), (ulong)(uint)param_2 < *(ulong *)(lVar1 + 0x28))) {
      p_Var5 = *(_Rb_tree_node_base **)(lVar1 + 0x18);
      if (p_Var5 != (_Rb_tree_node_base *)(lVar1 + 8)) {
        while( true ) {
          if (param_2 == 0) {
            return *(undefined8 *)(p_Var5 + 0x20);
          }
          p_Var5 = (_Rb_tree_node_base *)std::_Rb_tree_increment(p_Var5);
          if (p_Var5 == (_Rb_tree_node_base *)(lVar1 + 8)) break;
          param_2 = param_2 + -1;
        }
      }
    }
  }
  return 0xffffffff;
}

/* address=007b6c70
   symbol=CTimeline::GetObjectIDInTimelineByIndex */

/* CTimeline::GetObjectIDInTimelineByIndex(int) */

undefined8 __thiscall CTimeline::GetObjectIDInTimelineByIndex(CTimeline *this,int param_1)

{
  _Rb_tree_node_base *p_Var1;

  if ((-1 < param_1) && ((ulong)(uint)param_1 < *(ulong *)(this + 0x80))) {
    p_Var1 = *(_Rb_tree_node_base **)(this + 0x70);
    if (p_Var1 != (_Rb_tree_node_base *)(this + 0x60)) {
      while( true ) {
        if (param_1 == 0) {
          return *(undefined8 *)(p_Var1 + 0x20);
        }
        p_Var1 = (_Rb_tree_node_base *)std::_Rb_tree_increment(p_Var1);
        if (p_Var1 == (_Rb_tree_node_base *)(this + 0x60)) break;
        param_1 = param_1 + -1;
      }
    }
  }
  return 0xffffffffffffffff;
}

/* address=007b6cd0
   symbol=CTimeline::resetPropertiesToPercent */

/* CTimeline::resetPropertiesToPercent(float) */

void __thiscall CTimeline::resetPropertiesToPercent(CTimeline *this,float param_1)

{
  long lVar1;
  _Rb_tree_node_base *p_Var2;
  _Rb_tree_node_base *p_Var3;

  for (p_Var3 = *(_Rb_tree_node_base **)(this + 0x70); p_Var3 != (_Rb_tree_node_base *)(this + 0x60)
      ; p_Var3 = (_Rb_tree_node_base *)std::_Rb_tree_increment(p_Var3)) {
    p_Var2 = *(_Rb_tree_node_base **)(*(long *)(p_Var3 + 0x28) + 0x18);
    if (p_Var2 != (_Rb_tree_node_base *)(*(long *)(p_Var3 + 0x28) + 8)) {
      do {
        lVar1 = *(long *)(p_Var2 + 0x28);
        *(float *)(lVar1 + 0x24) = param_1;
        *(undefined1 *)(lVar1 + 0x60) = 0;
        p_Var2 = (_Rb_tree_node_base *)std::_Rb_tree_increment(p_Var2);
      } while (p_Var2 != (_Rb_tree_node_base *)(*(long *)(p_Var3 + 0x28) + 8));
    }
  }
  return;
}

/* address=007b6d50
   symbol=CTimeline::GetPointIDInTimelinePropertyByIndex */

/* CTimeline::GetPointIDInTimelinePropertyByIndex(long long, int, int, bool) */

undefined8 __thiscall
CTimeline::GetPointIDInTimelinePropertyByIndex
          (CTimeline *this,longlong param_1,int param_2,int param_3,bool param_4)

{
  CTimelineProperty *this_00;
  undefined8 uVar1;

  if (((-1 < param_2) && (param_1 != -1)) && (-1 < param_3)) {
    this_00 = (CTimelineProperty *)GetProperty(this,param_1,param_2,param_4);
    if (this_00 != (CTimelineProperty *)0x0) {
      uVar1 = CTimelineProperty::GetTimelinePointIDByIndex(this_00,param_3);
      return uVar1;
    }
  }
  return 0xffffffff;
}

/* address=007b6d90
   symbol=CTimeline::AddProperty */

/* CTimeline::AddProperty(CEditorScene*, long long, int, bool) */

void __thiscall
CTimeline::AddProperty
          (CTimeline *this,CEditorScene *param_1,longlong param_2,int param_3,bool param_4)

{
  CTimeline *pCVar1;
  CDescriptor *this_00;
  CTimeline *pCVar2;
  long lVar3;
  long lVar4;
  CTimeline *pCVar5;
  long lVar6;
  CDescriptorProp *pCVar7;
  map<std::pair<int,bool>,CTimelineProperty*,std::less<std::pair<int,bool>>,std::allocator<std::pair<std::pair<int,bool>const,CTimelineProperty*>>>
  *this_01;
  CTimeline *pCVar8;
  undefined8 *puVar9;
  CTimeline *pCVar10;
  CTimelineProperty *local_78;
  longlong local_68 [3];
  undefined8 local_50;
  int local_48;
  undefined1 local_44;

  if (((((param_2 != -1) && (param_1 != (CEditorScene *)0x0)) && (param_3 != -1)) &&
      ((lVar6 = GetProperty(this,param_2,param_3,param_4), lVar6 == 0 &&
       (lVar6 = CEditorScene::GetObjectInScene(param_1,param_2), lVar6 != 0)))) &&
     ((this_00 = *(CDescriptor **)(lVar6 + 0x38), this_00 != (CDescriptor *)0x0 &&
      (pCVar7 = (CDescriptorProp *)CDescriptor::GetPropertyByIndex(this_00,param_3),
      pCVar7 != (CDescriptorProp *)0x0)))) {
    if (param_4) {
      local_78 = (CTimelineProperty *)Ogre::NedAllocImpl::allocBytes(0x68,(char *)0x0,0,(char *)0x0)
      ;
                    /* try { // try from 007b6fcc to 007b6fd0 has its CatchHandler @ 007b710d */
      CTimelineProperty::CTimelineProperty(local_78,this,param_1,this_00,param_3,true,param_2);
    }
    else {
      local_78 = (CTimelineProperty *)Ogre::NedAllocImpl::allocBytes(0x68,(char *)0x0,0,(char *)0x0)
      ;
                    /* try { // try from 007b6e94 to 007b6e98 has its CatchHandler @ 007b70f8 */
      CTimelineProperty::CTimelineProperty(local_78,this,param_1,this_00,pCVar7,param_2);
    }
    if (local_78 != (CTimelineProperty *)0x0) {
      CTimelineProperty::SetInterpolationType(local_78,*(undefined4 *)(this + 0xa4));
      pCVar10 = *(CTimeline **)(this + 0x68);
      pCVar1 = this + 0x60;
      pCVar5 = pCVar10;
      pCVar8 = pCVar1;
      while (pCVar2 = pCVar5, pCVar2 != (CTimeline *)0x0) {
        if (*(long *)(pCVar2 + 0x20) < param_2) {
          pCVar5 = *(CTimeline **)(pCVar2 + 0x18);
        }
        else {
          pCVar5 = *(CTimeline **)(pCVar2 + 0x10);
          pCVar8 = pCVar2;
        }
      }
      local_48 = param_3;
      local_44 = param_4;
      if ((pCVar1 == pCVar8) || (param_2 < *(long *)(pCVar8 + 0x20))) {
        this_01 = operator_new(0x30);
        *(undefined8 *)(this_01 + 0x28) = 0;
        *(undefined4 *)(this_01 + 8) = 0;
        *(undefined8 *)(this_01 + 0x10) = 0;
        *(map<std::pair<int,bool>,CTimelineProperty*,std::less<std::pair<int,bool>>,std::allocator<std::pair<std::pair<int,bool>const,CTimelineProperty*>>>
          **)(this_01 + 0x18) = this_01 + 8;
        *(map<std::pair<int,bool>,CTimelineProperty*,std::less<std::pair<int,bool>>,std::allocator<std::pair<std::pair<int,bool>const,CTimelineProperty*>>>
          **)(this_01 + 0x20) = this_01 + 8;
        pCVar10 = pCVar1;
        pCVar8 = *(CTimeline **)(this + 0x68);
        while (pCVar8 != (CTimeline *)0x0) {
          if (*(long *)(pCVar8 + 0x20) < param_2) {
            pCVar8 = *(CTimeline **)(pCVar8 + 0x18);
          }
          else {
            pCVar10 = pCVar8;
            pCVar8 = *(CTimeline **)(pCVar8 + 0x10);
          }
        }
        if ((pCVar1 == pCVar10) || (param_2 < *(long *)(pCVar10 + 0x20))) {
          local_50 = 0;
          local_68[2] = param_2;
          pCVar10 = (CTimeline *)
                    std::
                    _Rb_tree<long_long,std::pair<long_long_const,std::map<std::pair<int,bool>,CTimelineProperty*,std::less<std::pair<int,bool>>,std::allocator<std::pair<std::pair<int,bool>const,CTimelineProperty*>>>*>,std::_Select1st<std::pair<long_long_const,std::map<std::pair<int,bool>,CTimelineProperty*,std::less<std::pair<int,bool>>,std::allocator<std::pair<std::pair<int,bool>const,CTimelineProperty*>>>*>>,std::less<long_long>,std::allocator<std::pair<long_long_const,std::map<std::pair<int,bool>,CTimelineProperty*,std::less<std::pair<int,bool>>,std::allocator<std::pair<std::pair<int,bool>const,CTimelineProperty*>>>*>>>
                    ::_M_insert_unique_((_Rb_tree<long_long,std::pair<long_long_const,std::map<std::pair<int,bool>,CTimelineProperty*,std::less<std::pair<int,bool>>,std::allocator<std::pair<std::pair<int,bool>const,CTimelineProperty*>>>*>,std::_Select1st<std::pair<long_long_const,std::map<std::pair<int,bool>,CTimelineProperty*,std::less<std::pair<int,bool>>,std::allocator<std::pair<std::pair<int,bool>const,CTimelineProperty*>>>*>>,std::less<long_long>,std::allocator<std::pair<long_long_const,std::map<std::pair<int,bool>,CTimelineProperty*,std::less<std::pair<int,bool>>,std::allocator<std::pair<std::pair<int,bool>const,CTimelineProperty*>>>*>>>
                                         *)(this + 0x58),pCVar10,local_68 + 2);
        }
        *(map<std::pair<int,bool>,CTimelineProperty*,std::less<std::pair<int,bool>>,std::allocator<std::pair<std::pair<int,bool>const,CTimelineProperty*>>>
          **)(pCVar10 + 0x28) = this_01;
        puVar9 = (undefined8 *)
                 std::
                 map<std::pair<int,bool>,CTimelineProperty*,std::less<std::pair<int,bool>>,std::allocator<std::pair<std::pair<int,bool>const,CTimelineProperty*>>>
                 ::operator[](this_01,(pair *)&local_48);
        *puVar9 = local_78;
      }
      else {
        lVar6 = *(long *)(pCVar8 + 0x28) + 8;
        lVar3 = lVar6;
        lVar4 = *(long *)(*(long *)(pCVar8 + 0x28) + 0x10);
        while (lVar4 != 0) {
          if ((*(int *)(lVar4 + 0x20) < param_3) ||
             ((*(int *)(lVar4 + 0x20) <= param_3 && (*(byte *)(lVar4 + 0x24) < param_4)))) {
            lVar4 = *(long *)(lVar4 + 0x18);
          }
          else {
            lVar3 = lVar4;
            lVar4 = *(long *)(lVar4 + 0x10);
          }
        }
        pCVar8 = pCVar1;
        if (((lVar6 == lVar3) || (param_3 < *(int *)(lVar3 + 0x20))) ||
           ((param_3 <= *(int *)(lVar3 + 0x20) && (param_4 < *(byte *)(lVar3 + 0x24))))) {
          while (pCVar5 = pCVar10, pCVar5 != (CTimeline *)0x0) {
            if (*(long *)(pCVar5 + 0x20) < param_2) {
              pCVar10 = *(CTimeline **)(pCVar5 + 0x18);
            }
            else {
              pCVar10 = *(CTimeline **)(pCVar5 + 0x10);
              pCVar8 = pCVar5;
            }
          }
          if ((pCVar1 == pCVar8) || (param_2 < *(long *)(pCVar8 + 0x20))) {
            local_68[1] = 0;
            local_68[0] = param_2;
            pCVar8 = (CTimeline *)
                     std::
                     _Rb_tree<long_long,std::pair<long_long_const,std::map<std::pair<int,bool>,CTimelineProperty*,std::less<std::pair<int,bool>>,std::allocator<std::pair<std::pair<int,bool>const,CTimelineProperty*>>>*>,std::_Select1st<std::pair<long_long_const,std::map<std::pair<int,bool>,CTimelineProperty*,std::less<std::pair<int,bool>>,std::allocator<std::pair<std::pair<int,bool>const,CTimelineProperty*>>>*>>,std::less<long_long>,std::allocator<std::pair<long_long_const,std::map<std::pair<int,bool>,CTimelineProperty*,std::less<std::pair<int,bool>>,std::allocator<std::pair<std::pair<int,bool>const,CTimelineProperty*>>>*>>>
                     ::_M_insert_unique_((_Rb_tree<long_long,std::pair<long_long_const,std::map<std::pair<int,bool>,CTimelineProperty*,std::less<std::pair<int,bool>>,std::allocator<std::pair<std::pair<int,bool>const,CTimelineProperty*>>>*>,std::_Select1st<std::pair<long_long_const,std::map<std::pair<int,bool>,CTimelineProperty*,std::less<std::pair<int,bool>>,std::allocator<std::pair<std::pair<int,bool>const,CTimelineProperty*>>>*>>,std::less<long_long>,std::allocator<std::pair<long_long_const,std::map<std::pair<int,bool>,CTimelineProperty*,std::less<std::pair<int,bool>>,std::allocator<std::pair<std::pair<int,bool>const,CTimelineProperty*>>>*>>>
                                          *)(this + 0x58),pCVar8,local_68);
          }
          puVar9 = (undefined8 *)
                   std::
                   map<std::pair<int,bool>,CTimelineProperty*,std::less<std::pair<int,bool>>,std::allocator<std::pair<std::pair<int,bool>const,CTimelineProperty*>>>
                   ::operator[](*(map<std::pair<int,bool>,CTimelineProperty*,std::less<std::pair<int,bool>>,std::allocator<std::pair<std::pair<int,bool>const,CTimelineProperty*>>>
                                  **)(pCVar8 + 0x28),(pair *)&local_48);
          *puVar9 = local_78;
        }
        else {
          (**(code **)(*(long *)local_78 + 8))(local_78);
        }
      }
    }
  }
  return;
}

/* address=007b7110
   symbol=CTimeline::loadTimelineFromBinaryFile */

/* CTimeline::loadTimelineFromBinaryFile(CEditorScene*, COgreReader*, CDescriptorLoadConfiguration*)
    */

void __thiscall
CTimeline::loadTimelineFromBinaryFile
          (CTimeline *this,CEditorScene *param_1,COgreReader *param_2,
          CDescriptorLoadConfiguration *param_3)

{
  int iVar1;
  long lVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  ulong uVar5;
  long lVar6;
  uint uVar7;
  CTimelineProperty *local_90;
  uint local_84;
  uint local_74;
  longlong local_60;
  uint local_58;
  undefined4 local_54;
  float local_50;
  uint local_4c;
  int local_48;
  uint local_44;
  uint local_40;
  bool local_39 [9];

  if (((param_2 != (COgreReader *)0x0) && (param_1 != (CEditorScene *)0x0)) &&
     (param_3 != (CDescriptorLoadConfiguration *)0x0)) {
    local_40 = 0;
    COgreReader::read(param_2,&local_40,4);
    if (local_40 != 0) {
      local_74 = 0;
      do {
        local_60 = 0;
        local_44 = 0;
        COgreReader::read(param_2,&local_60,8);
        COgreReader::read(param_2,&local_44,4);
        local_60 = CDescriptorLoadConfiguration::getRemappedID(param_3,local_60);
        lVar2 = CEditorScene::GetObjectInScene(param_1,local_60);
        if (local_44 != 0) {
          local_84 = 0;
          do {
            local_48 = 0;
            local_39[0] = false;
            local_4c = 0;
            COgreReader::read(param_2,&local_48,4);
            COgreReader::read(param_2,local_39,1);
            COgreReader::read(param_2,&local_4c,4);
            local_90 = (CTimelineProperty *)0x0;
            if (lVar2 != 0) {
              AddProperty(this,param_1,local_60,local_48,local_39[0]);
              local_90 = (CTimelineProperty *)GetProperty(this,local_60,local_48,local_39[0]);
            }
            if (local_4c != 0) {
              uVar7 = 0;
              do {
                while( true ) {
                  local_50 = 0.0;
                  local_54 = 0;
                  iVar1 = -1;
                  COgreReader::read(param_2,&local_50,4);
                  COgreReader::read(param_2,&local_54,4);
                  if (lVar2 != 0) {
                    iVar1 = AddPointToProperty(this,local_60,local_48,local_39[0]);
                    SetPropertyPointTimePercent(this,local_60,local_48,iVar1,local_50,local_39[0]);
                    SetPropertyPointInterpolationType(this,local_60,local_48,local_54);
                  }
                  if (local_39[0] == false) break;
LAB_007b7290:
                  uVar7 = uVar7 + 1;
                  if (local_4c <= uVar7) goto LAB_007b73e0;
                }
                local_58 = 0;
                COgreReader::read(param_2,&local_58,4);
                uVar5 = (ulong)local_58;
                puVar3 = operator_new__(uVar5 * 4);
                if (uVar5 != 0) {
                  lVar6 = uVar5 - 2;
                  puVar4 = puVar3;
                  do {
                    lVar6 = lVar6 + -1;
                    *puVar4 = 0;
                    puVar4 = puVar4 + 1;
                  } while (lVar6 != -2);
                }
                COgreReader::read(param_2,puVar3,local_58 << 2);
                if (lVar2 != 0) {
                  CTimelineProperty::SetValueAtPoint(local_90,iVar1,puVar3,local_58);
                }
                if (puVar3 == (undefined4 *)0x0) goto LAB_007b7290;
                uVar7 = uVar7 + 1;
                operator_delete__(puVar3);
              } while (uVar7 < local_4c);
            }
LAB_007b73e0:
            local_84 = local_84 + 1;
          } while (local_84 < local_44);
        }
        local_74 = local_74 + 1;
      } while (local_74 < local_40);
    }
  }
  return;
}

/* address=007b7420
   symbol=CTimeline::UpdateTimeline */

/* CTimeline::UpdateTimeline(float) */

float __thiscall CTimeline::UpdateTimeline(CTimeline *this,float param_1)

{
  CTimeline CVar1;
  char cVar2;
  _Rb_tree_node_base *p_Var3;
  _Rb_tree_node_base *p_Var4;
  long lVar5;
  undefined8 uVar6;
  CTimeline CVar7;
  float fVar8;
  float fVar9;

  fVar9 = DAT_00fa47fc;
  if (this[0x89] == (CTimeline)0x0) {
    if (this[0xa0] == (CTimeline)0x0) {
      if (*(float *)(this + 0x94) <= *(float *)(this + 0x98)) goto LAB_007b744d;
    }
    else if (*(float *)(this + 0x98) <= 0.0) {
LAB_007b744d:
      this[0xa1] = (CTimeline)0x0;
      return fVar9;
    }
  }
  if ((this[0xa1] == (CTimeline)0x0) &&
     (cVar2 = CResourceManager::getEditorIsRunning(), cVar2 == '\0')) {
    if (0.0 < *(float *)(this + 0x94)) {
      return *(float *)(this + 0x98) / *(float *)(this + 0x94);
    }
    return DAT_00fa47fc;
  }
  if (this[0xa0] == (CTimeline)0x0) {
    fVar9 = *(float *)(this + 0x90);
    if (fVar9 <= 0.0) goto LAB_007b7500;
LAB_007b74a6:
    fVar8 = param_1 + *(float *)(this + 0x9c);
    *(float *)(this + 0x9c) = fVar8;
    if (fVar8 < fVar9) {
      fVar9 = *(float *)(this + 0x98);
    }
    else {
      fVar9 = fVar9 + *(float *)(this + 0x98);
      *(float *)(this + 0x98) = fVar9;
      *(float *)(this + 0x9c) = fVar8 - *(float *)(this + 0x90);
    }
  }
  else {
    fVar9 = *(float *)(this + 0x90);
    param_1 = (float)((uint)param_1 ^ DAT_00fa8780);
    if (0.0 < fVar9) goto LAB_007b74a6;
LAB_007b7500:
    fVar9 = *(float *)(this + 0x98) + param_1;
    *(float *)(this + 0x98) = fVar9;
  }
  CVar7 = this[0xa1];
  CVar1 = CVar7;
  if (this[0xa0] == (CTimeline)0x0) {
    fVar8 = *(float *)(this + 0x94);
    if (fVar9 < fVar8) goto LAB_007b753d;
    if (this[0x89] == (CTimeline)0x0) {
      *(float *)(this + 0x98) = fVar8;
      (**(code **)(*(long *)this + 0x30))(this,0x2d);
      (**(code **)(*(long *)this + 0x30))(this,0x23);
      lVar5 = *(long *)this;
      uVar6 = 0x2c;
LAB_007b772a:
      CVar7 = (CTimeline)0x0;
      (**(code **)(lVar5 + 0x30))(this,uVar6);
      fVar8 = *(float *)(this + 0x94);
      CVar1 = this[0xa1];
      goto LAB_007b753d;
    }
    *(float *)(this + 0x98) = fVar9 - fVar8;
  }
  else {
    if (0.0 <= fVar9) {
      fVar8 = *(float *)(this + 0x94);
      goto LAB_007b753d;
    }
    if (this[0x89] == (CTimeline)0x0) {
      *(undefined4 *)(this + 0x98) = 0;
      (**(code **)(*(long *)this + 0x30))(this,0x2d);
      (**(code **)(*(long *)this + 0x30))(this,0x23);
      lVar5 = *(long *)this;
      uVar6 = 0x2b;
      goto LAB_007b772a;
    }
    *(float *)(this + 0x98) = fVar9 + *(float *)(this + 0x94);
  }
  (**(code **)(*(long *)this + 0x30))(this,0x28);
  fVar8 = *(float *)(this + 0x94);
  CVar1 = this[0xa1];
LAB_007b753d:
  fVar9 = DAT_00fa47fc;
  if (0.0 < fVar8) {
    fVar9 = *(float *)(this + 0x98) / fVar8;
  }
  if ((CVar1 != (CTimeline)0x0) || (cVar2 = CResourceManager::getEditorIsRunning(), cVar2 != '\0'))
  {
    for (p_Var4 = *(_Rb_tree_node_base **)(this + 0x70);
        (_Rb_tree_node_base *)(this + 0x60) != p_Var4;
        p_Var4 = (_Rb_tree_node_base *)std::_Rb_tree_increment(p_Var4)) {
      p_Var3 = *(_Rb_tree_node_base **)(*(long *)(p_Var4 + 0x28) + 0x18);
      if (p_Var3 != (_Rb_tree_node_base *)(*(long *)(p_Var4 + 0x28) + 8)) {
        do {
          CTimelineProperty::Update(*(CTimelineProperty **)(p_Var3 + 0x28),fVar9,(bool)this[0xa0]);
          p_Var3 = (_Rb_tree_node_base *)std::_Rb_tree_increment(p_Var3);
        } while (p_Var3 != (_Rb_tree_node_base *)(*(long *)(p_Var4 + 0x28) + 8));
      }
    }
  }
  cVar2 = CResourceManager::getEditorIsRunning();
  if (cVar2 == '\0') {
    this[0xa1] = CVar7;
  }
  return fVar9;
}

/* address=007b77a0
   symbol=CTimeline::~CTimeline */

/* CTimeline::~CTimeline() */

void __thiscall CTimeline::~CTimeline(CTimeline *this)

{
  _Rb_tree_node_base *p_Var1;
  _Rb_tree_node_base *p_Var2;
  _Rb_tree<std::pair<int,bool>,std::pair<std::pair<int,bool>const,CTimelineProperty*>,std::_Select1st<std::pair<std::pair<int,bool>const,CTimelineProperty*>>,std::less<std::pair<int,bool>>,std::allocator<std::pair<std::pair<int,bool>const,CTimelineProperty*>>>
  *this_00;

  p_Var2 = *(_Rb_tree_node_base **)(this + 0x70);
  *(undefined ***)this = &PTR__CTimeline_00fc7570;
  for (; p_Var2 != (_Rb_tree_node_base *)(this + 0x60);
      p_Var2 = (_Rb_tree_node_base *)std::_Rb_tree_increment(p_Var2)) {
    this_00 = *(_Rb_tree<std::pair<int,bool>,std::pair<std::pair<int,bool>const,CTimelineProperty*>,std::_Select1st<std::pair<std::pair<int,bool>const,CTimelineProperty*>>,std::less<std::pair<int,bool>>,std::allocator<std::pair<std::pair<int,bool>const,CTimelineProperty*>>>
                **)(p_Var2 + 0x28);
    p_Var1 = *(_Rb_tree_node_base **)(this_00 + 0x18);
    while (p_Var1 != (_Rb_tree_node_base *)(this_00 + 8)) {
      if (*(long **)(p_Var1 + 0x28) != (long *)0x0) {
                    /* try { // try from 007b77ef to 007b7804 has its CatchHandler @ 007b788c */
        (**(code **)(**(long **)(p_Var1 + 0x28) + 8))();
        *(undefined8 *)(p_Var1 + 0x28) = 0;
      }
      p_Var1 = (_Rb_tree_node_base *)std::_Rb_tree_increment(p_Var1);
      this_00 = *(_Rb_tree<std::pair<int,bool>,std::pair<std::pair<int,bool>const,CTimelineProperty*>,std::_Select1st<std::pair<std::pair<int,bool>const,CTimelineProperty*>>,std::less<std::pair<int,bool>>,std::allocator<std::pair<std::pair<int,bool>const,CTimelineProperty*>>>
                  **)(p_Var2 + 0x28);
    }
    if (this_00 !=
        (_Rb_tree<std::pair<int,bool>,std::pair<std::pair<int,bool>const,CTimelineProperty*>,std::_Select1st<std::pair<std::pair<int,bool>const,CTimelineProperty*>>,std::less<std::pair<int,bool>>,std::allocator<std::pair<std::pair<int,bool>const,CTimelineProperty*>>>
         *)0x0) {
                    /* try { // try from 007b7821 to 007b7825 has its CatchHandler @ 007b78ab */
      std::
      _Rb_tree<std::pair<int,bool>,std::pair<std::pair<int,bool>const,CTimelineProperty*>,std::_Select1st<std::pair<std::pair<int,bool>const,CTimelineProperty*>>,std::less<std::pair<int,bool>>,std::allocator<std::pair<std::pair<int,bool>const,CTimelineProperty*>>>
      ::_M_erase(this_00,*(_Rb_tree_node **)(this_00 + 0x10));
      operator_delete(this_00);
    }
                    /* try { // try from 007b7834 to 007b7850 has its CatchHandler @ 007b788c */
  }
  std::
  _Rb_tree<long_long,std::pair<long_long_const,std::map<std::pair<int,bool>,CTimelineProperty*,std::less<std::pair<int,bool>>,std::allocator<std::pair<std::pair<int,bool>const,CTimelineProperty*>>>*>,std::_Select1st<std::pair<long_long_const,std::map<std::pair<int,bool>,CTimelineProperty*,std::less<std::pair<int,bool>>,std::allocator<std::pair<std::pair<int,bool>const,CTimelineProperty*>>>*>>,std::less<long_long>,std::allocator<std::pair<long_long_const,std::map<std::pair<int,bool>,CTimelineProperty*,std::less<std::pair<int,bool>>,std::allocator<std::pair<std::pair<int,bool>const,CTimelineProperty*>>>*>>>
  ::_M_erase((_Rb_tree<long_long,std::pair<long_long_const,std::map<std::pair<int,bool>,CTimelineProperty*,std::less<std::pair<int,bool>>,std::allocator<std::pair<std::pair<int,bool>const,CTimelineProperty*>>>*>,std::_Select1st<std::pair<long_long_const,std::map<std::pair<int,bool>,CTimelineProperty*,std::less<std::pair<int,bool>>,std::allocator<std::pair<std::pair<int,bool>const,CTimelineProperty*>>>*>>,std::less<long_long>,std::allocator<std::pair<long_long_const,std::map<std::pair<int,bool>,CTimelineProperty*,std::less<std::pair<int,bool>>,std::allocator<std::pair<std::pair<int,bool>const,CTimelineProperty*>>>*>>>
              *)(this + 0x58),*(_Rb_tree_node **)(this + 0x68));
  *(_Rb_tree_node_base **)(this + 0x70) = p_Var2;
  *(undefined8 *)(this + 0x68) = 0;
  *(_Rb_tree_node_base **)(this + 0x78) = p_Var2;
  *(undefined8 *)(this + 0x80) = 0;
                    /* try { // try from 007b7871 to 007b7875 has its CatchHandler @ 007b78b4 */
  std::
  _Rb_tree<long_long,std::pair<long_long_const,std::map<std::pair<int,bool>,CTimelineProperty*,std::less<std::pair<int,bool>>,std::allocator<std::pair<std::pair<int,bool>const,CTimelineProperty*>>>*>,std::_Select1st<std::pair<long_long_const,std::map<std::pair<int,bool>,CTimelineProperty*,std::less<std::pair<int,bool>>,std::allocator<std::pair<std::pair<int,bool>const,CTimelineProperty*>>>*>>,std::less<long_long>,std::allocator<std::pair<long_long_const,std::map<std::pair<int,bool>,CTimelineProperty*,std::less<std::pair<int,bool>>,std::allocator<std::pair<std::pair<int,bool>const,CTimelineProperty*>>>*>>>
  ::_M_erase((_Rb_tree<long_long,std::pair<long_long_const,std::map<std::pair<int,bool>,CTimelineProperty*,std::less<std::pair<int,bool>>,std::allocator<std::pair<std::pair<int,bool>const,CTimelineProperty*>>>*>,std::_Select1st<std::pair<long_long_const,std::map<std::pair<int,bool>,CTimelineProperty*,std::less<std::pair<int,bool>>,std::allocator<std::pair<std::pair<int,bool>const,CTimelineProperty*>>>*>>,std::less<long_long>,std::allocator<std::pair<long_long_const,std::map<std::pair<int,bool>,CTimelineProperty*,std::less<std::pair<int,bool>>,std::allocator<std::pair<std::pair<int,bool>const,CTimelineProperty*>>>*>>>
              *)(this + 0x58),(_Rb_tree_node *)0x0);
  CEditorBaseObject::~CEditorBaseObject((CEditorBaseObject *)this);
  return;
}

/* address=007b78c0
   symbol=CTimeline::~CTimeline */

/* CTimeline::~CTimeline() */

void __thiscall CTimeline::~CTimeline(CTimeline *this)

{
  ~CTimeline(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}

/* address=007b78e0
   symbol=CTimeline::CTimeline */

/* CTimeline::CTimeline() */

void __thiscall CTimeline::CTimeline(CTimeline *this)

{
  CEditorBaseObject::CEditorBaseObject((CEditorBaseObject *)this);
  *(undefined ***)this = &PTR__CTimeline_00fc7570;
  *(undefined8 *)(this + 0x80) = 0;
  *(undefined4 *)(this + 0x60) = 0;
  *(undefined8 *)(this + 0x68) = 0;
  *(CTimeline **)(this + 0x70) = this + 0x60;
  *(CTimeline **)(this + 0x78) = this + 0x60;
  this[0x88] = (CTimeline)0x0;
  this[0x89] = (CTimeline)0x0;
  this[0x8a] = (CTimeline)0x1;
  this[0x8b] = (CTimeline)0x1;
  this[0x8c] = (CTimeline)0x0;
  *(undefined4 *)(this + 0x90) = 0;
  *(undefined4 *)(this + 0x94) = 0x3f800000;
  *(undefined4 *)(this + 0x98) = 0xbc23d70a;
  *(undefined4 *)(this + 0x9c) = 0;
  this[0xa0] = (CTimeline)0x0;
  this[0xa1] = (CTimeline)0x0;
  this[0xa2] = (CTimeline)0x0;
  this[0xa3] = (CTimeline)0x1;
  *(undefined4 *)(this + 0xa4) = 0;
  *(undefined4 *)(this + 0xa8) = 0;
  return;
}

/* address=007baa20
   symbol=CTimeline::_GLOBAL__I_CTimeline */

/* CTimeline::CTimeline() */

void CTimeline::_GLOBAL__I_CTimeline(void)

{
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
  ::gUnionOf32BitData._0_4_ = 0;
  ::gUnionOf32BitData._4_4_ = 0;
  ::gUnionOf32BitData._8_4_ = 0;
  std::wstring::wstring
            ((wstring_conflict *)::KEditorObjectPropertyTypeNames,L"NOT VALID",&aStack_126);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 8),L"NOT SET",&aStack_125);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x10),L"INTEGER",&aStack_124);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x18),L"FLOAT",&aStack_123);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x20),L"UNSIGNED INTEGER",
             &aStack_122);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x28),L"STRING",&aStack_121);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x30),L"BOOL",&aStack_120);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x38),L"VECTOR2",&aStack_11f);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x40),L"VECTOR3",&aStack_11e);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x48),L"VECTOR4",&aStack_11d);
  __cxa_atexit(::__tcf_0,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&gTIMELINE_INTERP_TYPES,L"Linear",&aStack_11c);
  std::wstring::wstring((wstring_conflict *)&DAT_01472068,L"Linear Round",&aStack_11b);
  std::wstring::wstring((wstring_conflict *)&DAT_01472070,L"Linear Round Down",&aStack_11a);
  std::wstring::wstring((wstring_conflict *)&DAT_01472078,L"Linear Round Up",&aStack_119);
  std::wstring::wstring((wstring_conflict *)&DAT_01472080,L"Spline",&aStack_118);
  std::wstring::wstring((wstring_conflict *)&DAT_01472088,L"Quaternion",&aStack_117);
  std::wstring::wstring((wstring_conflict *)&DAT_01472090,L"No Interpolation",&aStack_116);
  std::wstring::wstring((wstring_conflict *)&DAT_01472098,L"Use Timeline Default",&aStack_115);
  __cxa_atexit(::__tcf_1,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)gTIMELINE_MODIFICATION_TYPE_NAMES,L"None",&aStack_114);
  std::wstring::wstring
            ((wstring_conflict *)(gTIMELINE_MODIFICATION_TYPE_NAMES + 8),L"Set",&aStack_113);
  std::wstring::wstring
            ((wstring_conflict *)(gTIMELINE_MODIFICATION_TYPE_NAMES + 0x10),L"Multiply",&aStack_112)
  ;
  __cxa_atexit(::__tcf_2,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEDITOR_EVENT_NAMES,L"STOP",&aStack_111);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 8),L"PLAY",&aStack_110);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x10),L"RELOAD TILES",&aStack_10f);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x18),L"TOGGLE LIGHTING",&aStack_10e);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x20),L"SELECT COLLIDABLE",&aStack_10d);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x28),L"PAUSE PARTICLES",&aStack_10c);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x30),L"UNPAUSE PARTICLES",&aStack_10b);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x38),L"COLLISION ALL",&aStack_10a);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x40),L"COLLISION MODELS",&aStack_109);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x48),L"COLLISION PREFABS",&aStack_108);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x50),L"COLLISION ROOMPIECES",&aStack_107)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x58),L"COLLISION ROOMPROPS",&aStack_106);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x60),L"RELOAD GRAPHS",&aStack_105);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x68),L"TOGGLE PLAYER LIGHT",&aStack_104);
  __cxa_atexit(::__tcf_3,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEDITOR_FLAG_NAMES,L"LOGIC ENABLED",&aStack_103);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 8),L"INGAME MODE",&aStack_102);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x10),L"SHOW STATS",&aStack_101)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x18),L"EDIT POSITION",&aStack_100);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x20),L"EDIT SCALE",&aStack_ff);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x28),L"EDIT ORIENTATION",&aStack_fe);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x30),L"EDIT NONE",&aStack_fd);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x38),L"SHOW HELPERS",&aStack_fc);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x40),L"SHOW GRID",&aStack_fb);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x48),L"SHOW WORKING PLANE",&aStack_fa);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x50),L"SNAP TO GRID",&aStack_f9);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x58),L"SUSPEND EDITOR",&aStack_f8);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x60),L"LIGHTING VISIBLE",&aStack_f7);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x68),L"RECALCULATE LIGHTING",&aStack_f6);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x70),L"SHOW EDGES",&aStack_f5);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x78),L"UPDATE PARTICLES CIRCLE",&aStack_f4
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x80),L"SHOW LOGIC OUTPUT",&aStack_f3);
  __cxa_atexit(::__tcf_4,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::gEDITOR_UPDATE_MASKS,L"OBJECT SELECTION CHANGED",&aStack_f2);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 8),L"OBJECT DATA CHANGED",&aStack_f1);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 0x10),L"OBJECTS CREATED",&aStack_f0);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 0x18),L"REFRESH TREE VIEW",&aStack_ef);
  __cxa_atexit(::__tcf_5,0,&__dso_handle);
  ParticleUniverse::HALFSCALE._4_4_ = DAT_0142463c * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._0_4_ = Ogre::Vector3::UNIT_SCALE * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._8_4_ = DAT_00fa4810 * DAT_01424640;
  std::string::string((string *)&ParticleUniverse::ALIAS,"1",&aStack_ee);
  __cxa_atexit(std::string::~string,&ParticleUniverse::ALIAS,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::SYSTEM,"2",&aStack_ed);
  __cxa_atexit(std::string::~string,&ParticleUniverse::SYSTEM,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::TECHNIQUE,"3",&aStack_ec);
  __cxa_atexit(std::string::~string,&ParticleUniverse::TECHNIQUE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::RENDERER,"4",&aStack_eb);
  __cxa_atexit(std::string::~string,&ParticleUniverse::RENDERER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EMITTER,"5",&aStack_ea);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EMITTER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::AFFECTOR,"6",&aStack_e9);
  __cxa_atexit(std::string::~string,&ParticleUniverse::AFFECTOR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::OBSERVER,"7",&aStack_e8);
  __cxa_atexit(std::string::~string,&ParticleUniverse::OBSERVER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::HANDLER,"8",&aStack_e7);
  __cxa_atexit(std::string::~string,&ParticleUniverse::HANDLER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::BEHAVIOUR,"9",&aStack_e6);
  __cxa_atexit(std::string::~string,&ParticleUniverse::BEHAVIOUR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EXTERN,"10",&aStack_e5);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EXTERN,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DYNAMIC_ATTRIBUTE,"11",&aStack_e4);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DYNAMIC_ATTRIBUTE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DEPENDENCY,"12",&aStack_e3);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DEPENDENCY,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gOUTPUT_EVENTS_NAMES,L"Triggered",&aStack_e2);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 8),L"Triggered First Time",&aStack_e1);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x10),L"Deactivated",&aStack_e0);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x18),L"Deactivated First Time",
             &aStack_df);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x20),L"On Visible",&aStack_de);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x28),L"On Invisible",&aStack_dd);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x30),L"Enabled",&aStack_dc);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x38),L"Disabled",&aStack_db);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x40),L"Activated",&aStack_da)
  ;
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x48),L"Reset",&aStack_d9);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x50),L"Initialized",&aStack_d8);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x58),L"Playing",&aStack_d7);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x60),L"Stopped",&aStack_d6);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x68),L"Sound Ended",&aStack_d5);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x70),L"Paused",&aStack_d4);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x78),L"Resumed",&aStack_d3);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x80),L"Incremented",&aStack_d2);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x88),L"First Increment",&aStack_d1);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x90),L"Second Increment",&aStack_d0);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x98),L"Third Increment",&aStack_cf);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xa0),L"Fourth Increment",&aStack_ce);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xa8),L"Fifth Increment",&aStack_cd);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xb0),L"Increment Greater Then Five",
             &aStack_cc);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xb8),L"Monsters Spawned",&aStack_cb);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xc0),L"Monster Killed",&aStack_ca);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 200),L"All Monsters Dead",&aStack_c9);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xd0),L"All Units Spawned",&aStack_c8);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xd8),L"Item Picked Up",&aStack_c7);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xe0),L"All Items Picked Up",&aStack_c6);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xe8),L"Item Interacted",&aStack_c5);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xf0),L"All Items Interacted With",
             &aStack_c4);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xf8),L"Particle Started",&aStack_c3);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x100),L"Particle Stopped",&aStack_c2);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x108),L"Particle Paused",&aStack_c1);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x110),L"Particle Resumed",&aStack_c0);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x118),L"Stopped",&aStack_bf);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x120),L"Started",&aStack_be);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x128),L"Paused",&aStack_bd);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x130),L"Reset to Beginning",&aStack_bc);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x138),L"Reset to End",&aStack_bb);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x140),L"Looped",&aStack_ba);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x148),L"Started Backwards",&aStack_b9);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x150),L"Started Forwards",&aStack_b8);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x158),L"Stopped Backwards",&aStack_b7);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x160),L"Stopped Forwards",&aStack_b6);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x168),L"Finished",&aStack_b5)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x170),L"State One",&aStack_b4);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x178),L"State Two",&aStack_b3);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x180),L"Activation Failed",&aStack_b2);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x188),L"One",&aStack_b1);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 400),L"Two",&aStack_b0);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x198),L"Three",&aStack_af);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1a0),L"Four",&aStack_ae);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1a8),L"Five",&aStack_ad);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1b0),L"FAILED",&aStack_ac);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1b8),L"SUCCESS",&aStack_ab);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1c0),L"Interacted with Unit",&aStack_aa
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1c8),L"HP 90 PCT",&aStack_a9);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1d0),L"HP 80 PCT",&aStack_a8);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1d8),L"HP 70 PCT",&aStack_a7);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1e0),L"HP 60 PCT",&aStack_a6);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1e8),L"HP 50 PCT",&aStack_a5);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1f0),L"HP 40 PCT",&aStack_a4);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1f8),L"HP 30 PCT",&aStack_a3);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x200),L"HP 20 PCT",&aStack_a2);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x208),L"HP 10 PCT",&aStack_a1);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x210),L"Monster Alerted",&aStack_a0);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x218),L"Player HP Below 90 PCT",
             &aStack_9f);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x220),L"Player HP Below 80 PCT",
             &aStack_9e);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x228),L"Player HP Below 70 PCT",
             &aStack_9d);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x230),L"Player HP Below 60 PCT",
             &aStack_9c);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x238),L"Player HP Below 50 PCT",
             &aStack_9b);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x240),L"Player HP Below 40 PCT",
             &aStack_9a);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x248),L"Player HP Below 30 PCT",
             &aStack_99);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x250),L"Player HP Below 20 PCT",
             &aStack_98);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 600),L"Player HP Below 10 PCT",&aStack_97
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x260),L"Player HP Above 90 PCT",
             &aStack_96);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x268),L"Player HP Above 80 PCT",
             &aStack_95);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x270),L"Player HP Above 70 PCT",
             &aStack_94);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x278),L"Player HP Above 60 PCT",
             &aStack_93);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x280),L"Player HP Above 50 PCT",
             &aStack_92);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x288),L"Player HP Above 40 PCT",
             &aStack_91);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x290),L"Player HP Above 30 PCT",
             &aStack_90);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x298),L"Player HP Above 20 PCT",
             &aStack_8f);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2a0),L"Player HP Above 10 PCT",
             &aStack_8e);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2a8),L"Accepted",&aStack_8d)
  ;
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2b0),L"Declined",&aStack_8c)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2b8),L"Camera Moving",&aStack_8b);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2c0),L"Camera Stopped",&aStack_8a);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2c8),L"Camera Pausing",&aStack_89);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2d0),L"Camera Control Restored",
             &aStack_88);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2d8),L"Interacting",&aStack_87);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2e0),L"Interacted",&aStack_86);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2e8),L"Interacted Accepted",&aStack_85)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2f0),L"Interacted Declined",&aStack_84)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2f8),L"Interacted Closed",&aStack_83);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x300),L"Invulnerable",&aStack_82);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x308),L"Vulnerable",&aStack_81);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x310),L"Quest Active",&aStack_80);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x318),L"Quest Not Active",&aStack_7f);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 800),L"Quest Complete",&aStack_7e);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x328),L"Quest Not Complete",&aStack_7d);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x330),L"Quest Abandoned",&aStack_7c);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x338),L"Skill Started",&aStack_7b);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x340),L"Skill Stopped",&aStack_7a);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x348),L"Skill Learned",&aStack_79);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x350),L"Skill Unlearned",&aStack_78);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x358),L"Item Dropped",&aStack_77);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x360),L"Item Equipped",&aStack_76);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x368),L"Item Unequipped",&aStack_75);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x370),L"End of Path Reached",&aStack_74)
  ;
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x378),L"Clicked",&aStack_73);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x380),L"Animation Stopped",&aStack_72);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x388),L"Animation Playing",&aStack_71);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x390),L"Skip Cutscene",&aStack_70);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x398),L"Level Activated",&aStack_6f);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3a0),L"Insufficient funds",&aStack_6e);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3a8),L"Money Taken",&aStack_6d);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3b0),L"Stop",&aStack_6c);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3b8),L"Start",&aStack_6b);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3c0),L"Pause",&aStack_6a);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3c8),L"Output 1",&aStack_69)
  ;
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3d0),L"Output 2",&aStack_68)
  ;
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3d8),L"Output 3",&aStack_67)
  ;
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3e0),L"Output 4",&aStack_66)
  ;
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 1000),L"Output 5",&aStack_65);
  __cxa_atexit(::__tcf_6,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gINPUT_EVENT_NAMES,L"Show",&aStack_64);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 8),L"Hide",&aStack_63);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x10),L"Enable",&aStack_62);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x18),L"Disable",&aStack_61);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x20),L"Enable and Show",&aStack_60);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x28),L"Disable and Hide",&aStack_5f);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x30),L"Reset",&aStack_5e);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x38),L"Add",&aStack_5d);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x40),L"Subtract",&aStack_5c);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x48),L"Play",&aStack_5b);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x50),L"Stop",&aStack_5a);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x58),L"Pause",&aStack_59);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x60),L"Resume",&aStack_58);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x68),L"Play Level Music",&aStack_57);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x70),L"Increment",&aStack_56);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x78),L"Activate",&aStack_55);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x80),L"Start Particle",&aStack_54);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x88),L"Stop Particle",&aStack_53);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x90),L"Force Stop Particle",&aStack_52);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x98),L"Pause Particle",&aStack_51);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0xa0),L"Resume Particle",&aStack_50);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0xa8),L"Play",&aStack_4f);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0xb0),L"Play Backwards",&aStack_4e);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0xb8),L"Stop",&aStack_4d);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0xc0),L"Stop to End",&aStack_4c)
  ;
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 200),L"Pause",&aStack_4b);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0xd0),L"Reset",&aStack_4a);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0xd8),L"Reset To End",&aStack_49);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0xe0),L"Fast Forward To End",&aStack_48);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0xe8),L"Rewind to Start",&aStack_47);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0xf0),L"Set State One",&aStack_46);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0xf8),L"Set State Two",&aStack_45);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x100),L"Spawn Units",&aStack_44);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x108),L"Destroy Spawned Units",&aStack_43)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x110),L"Hide And Disable Spawned Units",
             &aStack_42);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x118),L"Increment Level Delta",&aStack_41)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x120),L"Decrement Level Delta",&aStack_40)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x128),L"Activate Warper",&aStack_3f);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x130),L"Activate Teleport",&aStack_3e);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x138),L"Roll",&aStack_3d);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x140),L"Input 1",&aStack_3c);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x148),L"Input 2",&aStack_3b);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x150),L"Input 3",&aStack_3a);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x158),L"Input 4",&aStack_39);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x160),L"Input 5",&aStack_38);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x168),L"Input 6",&aStack_37);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x170),L"Trigger",&aStack_36);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x178),L"Toggle",&aStack_35);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x180),L"Interact",&aStack_34);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x188),L"Make Invulnerable",&aStack_33);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 400),L"Make Vulnerable",&aStack_32);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x198),L"Start Camera",&aStack_31);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x1a0),L"Camera Off",&aStack_30)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x1a8),L"Force Accept",&aStack_2f);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x1b0),L"Force Not Accepted",&aStack_2e);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x1b8),L"Force Complete",&aStack_2d);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x1c0),L"Force Not Complete",&aStack_2c);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x1c8),L"Start Skill",&aStack_2b);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x1d0),L"Stop Skill",&aStack_2a)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x1d8),L"Learn Skill",&aStack_29);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x1e0),L"Unlearn Skill",&aStack_28);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x1e8),L"Alert Monster",&aStack_27);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x1f0),L"Enable Targeting",&aStack_26);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x1f8),L"Disable Targeting",&aStack_25);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x200),L"Enable Targeting & Alert",
             &aStack_24);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x208),L"Hunt",&aStack_23);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x210),L"Play",&aStack_22);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x218),L"Play Looping",&aStack_21);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x220),L"Stop",&aStack_20);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x228),L"Stop and Idle",&aStack_1f);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x230),L"Cannot be Targeted",&aStack_1e);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x238),L"Can be Targeted",&aStack_1d);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x240),L"Add as Pet",&aStack_1c)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x248),L"Remove as Pet",&aStack_1b);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x250),L"Kill Monster",&aStack_1a);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 600),L"Warp Pets to Player",&aStack_19);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x260),L"Heal Player",&aStack_18);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x268),L"Collidable",&aStack_17)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x270),L"Not Collidable",&aStack_16);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x278),L"Take Money",&aStack_15)
  ;
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x280),L"Show Tip",&aStack_14);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x288),L"Clear History",&aStack_13);
  std::wstring::wstring
            ((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x290),L"Stop Skills",&aStack_12);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x298),L"Kill Pets",&aStack_11);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x2a0),L"Stop",&aStack_10);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x2a8),L"Start",&aStack_f);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x2b0),L"Pause",&aStack_e);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x2b8),L"Input1",&aStack_d);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x2c0),L"Input2",&aStack_c);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x2c8),L"Input3",&aStack_b);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x2d0),L"Input4",&aStack_a);
  std::wstring::wstring((wstring_conflict *)(::gINPUT_EVENT_NAMES + 0x2d8),L"Input5",&aStack_9);
  __cxa_atexit(::__tcf_7,0,&__dso_handle);
  return;
}

/* address=007baa30
   symbol=CTimeline::saveTimelineToBinaryFile */

/* CTimeline::saveTimelineToBinaryFile(CEditorScene*, std::ofstream*) */

void __thiscall
CTimeline::saveTimelineToBinaryFile(CTimeline *this,CEditorScene *param_1,ofstream *param_2)

{
  uint uVar1;
  CTimeline *pCVar2;
  CTimeline *pCVar3;
  bool bVar4;
  CTimeline *pCVar5;
  char cVar6;
  int iVar7;
  long lVar8;
  long lVar9;
  undefined8 uVar10;
  CTimelineProperty *this_00;
  int iVar11;
  uint uVar12;
  int local_a8;
  int local_a4;
  uint local_94;
  undefined8 local_68;
  undefined8 local_58;
  uint local_50;
  undefined4 local_4c;
  undefined4 local_48;
  int local_44;
  undefined4 local_40;
  int local_3c [3];

  uVar1 = *(uint *)(this + 0x80);
  local_3c[0] = 0;
  if (uVar1 != 0) {
    uVar12 = 0;
    do {
      lVar8 = GetObjectIDInTimelineByIndex(this,uVar12);
      if (lVar8 != -1) {
        lVar9 = CEditorScene::GetObjectInScene(param_1,lVar8);
        pCVar3 = this + 0x60;
        pCVar2 = *(CTimeline **)(this + 0x68);
        while (pCVar2 != (CTimeline *)0x0) {
          if (*(long *)(pCVar2 + 0x20) < lVar8) {
            pCVar2 = *(CTimeline **)(pCVar2 + 0x18);
          }
          else {
            pCVar3 = pCVar2;
            pCVar2 = *(CTimeline **)(pCVar2 + 0x10);
          }
        }
        if (((((this + 0x60 != pCVar3) && (*(long *)(pCVar3 + 0x20) <= lVar8)) &&
             (*(int *)(*(long *)(pCVar3 + 0x28) + 0x28) != 0)) &&
            ((lVar9 != 0 && (*(long *)(lVar9 + 0x38) != 0)))) &&
           (cVar6 = CEditorBaseObject::HasBaseObjectFlag(lVar9,1), cVar6 == '\0')) {
          local_3c[0] = local_3c[0] + 1;
        }
      }
      uVar12 = uVar12 + 1;
    } while (uVar12 < uVar1);
  }
  std::ostream::write((char *)param_2,(long)local_3c);
  if ((local_3c[0] != 0) && (uVar1 != 0)) {
    pCVar2 = this + 0x60;
    local_94 = 1;
    local_a4 = 0;
    do {
      lVar8 = GetObjectIDInTimelineByIndex(this,local_a4);
      if (lVar8 != -1) {
        lVar9 = CEditorScene::GetObjectInScene(param_1,lVar8);
        pCVar5 = pCVar2;
        pCVar3 = *(CTimeline **)(this + 0x68);
        while (pCVar3 != (CTimeline *)0x0) {
          if (*(long *)(pCVar3 + 0x20) < lVar8) {
            pCVar3 = *(CTimeline **)(pCVar3 + 0x18);
          }
          else {
            pCVar5 = pCVar3;
            pCVar3 = *(CTimeline **)(pCVar3 + 0x10);
          }
        }
        if ((((pCVar2 != pCVar5) && (*(long *)(pCVar5 + 0x20) <= lVar8)) &&
            (*(int *)(*(long *)(pCVar5 + 0x28) + 0x28) != 0)) &&
           (((lVar9 != 0 && (*(long *)(lVar9 + 0x38) != 0)) &&
            (cVar6 = CEditorBaseObject::HasBaseObjectFlag(lVar9,1), cVar6 == '\0')))) {
          lVar8 = GetObjectIDInTimelineByIndex(this,local_a4);
          lVar9 = CEditorScene::GetObjectInScene(param_1,lVar8);
          if (lVar8 == -1) {
LAB_007bacc8:
            local_40 = 0;
          }
          else {
            pCVar5 = pCVar2;
            pCVar3 = *(CTimeline **)(this + 0x68);
            while (pCVar3 != (CTimeline *)0x0) {
              if (*(long *)(pCVar3 + 0x20) < lVar8) {
                pCVar3 = *(CTimeline **)(pCVar3 + 0x18);
              }
              else {
                pCVar5 = pCVar3;
                pCVar3 = *(CTimeline **)(pCVar3 + 0x10);
              }
            }
            if ((pCVar5 == pCVar2) || (lVar8 < *(long *)(pCVar5 + 0x20))) goto LAB_007bacc8;
            local_40 = *(undefined4 *)(*(long *)(pCVar5 + 0x28) + 0x28);
          }
          local_58 = *(undefined8 *)(lVar9 + 0x20);
          std::ostream::write((char *)param_2,(long)&local_58);
          std::ostream::write((char *)param_2,(long)&local_40);
          local_68 = GetPropertyIDForObjectInTimelineByIndex(this,lVar8,0);
          if (-1 < (int)local_68) {
            local_a8 = 0;
            do {
              std::ostream::write((char *)param_2,(long)&local_68);
              std::ostream::write((char *)param_2,(long)&local_68 + 4);
              local_44 = GetNumberOfPointsForAProperty
                                   (this,lVar8,(int)local_68,(bool)local_68._4_1_);
              std::ostream::write((char *)param_2,(long)&local_44);
              if (local_44 != 0) {
                iVar7 = GetPointIDInTimelinePropertyByIndex
                                  (this,lVar8,(int)local_68,0,(bool)local_68._4_1_);
                if (-1 < iVar7) {
                  iVar11 = 0;
                  do {
                    this_00 = (CTimelineProperty *)
                              GetProperty(this,lVar8,(int)local_68,(bool)local_68._4_1_);
                    local_48 = CTimelineProperty::GetTimePercentAtPoint(this_00,iVar7);
                    local_4c = *(undefined4 *)(this_00 + 0x48);
                    std::ostream::write((char *)param_2,(long)&local_48);
                    std::ostream::write((char *)param_2,(long)&local_4c);
                    if (local_68._4_1_ == '\0') {
                      local_50 = 0;
                      lVar9 = CTimelineProperty::GetValueAtPoint(this_00,iVar7,&local_50);
                      std::ostream::write((char *)param_2,(long)&local_50);
                      std::ostream::write((char *)param_2,lVar9);
                    }
                    iVar11 = iVar11 + 1;
                    iVar7 = GetPointIDInTimelinePropertyByIndex
                                      (this,lVar8,(int)local_68,iVar11,(bool)local_68._4_1_);
                  } while (-1 < iVar7);
                }
              }
              local_a8 = local_a8 + 1;
              uVar10 = GetPropertyIDForObjectInTimelineByIndex(this,lVar8,local_a8);
              local_68._0_5_ = (undefined5)uVar10;
            } while (-1 < (int)uVar10);
          }
        }
      }
      local_a4 = local_a4 + 1;
      bVar4 = local_94 < uVar1;
      local_94 = local_94 + 1;
    } while (bVar4);
  }
  return;
}

/* address=007baef0
   symbol=CTimeline::SetTimelinePercentDone */

/* CTimeline::SetTimelinePercentDone(float) */

float __thiscall CTimeline::SetTimelinePercentDone(CTimeline *this,float param_1)

{
  char cVar1;
  _Rb_tree_node_base *p_Var2;
  _Rb_tree_node_base *p_Var3;
  float fVar4;
  float fVar5;

  if (DAT_00fa47fc <= param_1) {
    param_1 = DAT_00fa47fc;
  }
  *(float *)(this + 0x98) = *(float *)(this + 0x94) * param_1;
  *(undefined4 *)(this + 0x9c) = 0;
  if (0.0 < *(float *)(this + 0x90)) {
    fVar5 = (*(float *)(this + 0x94) * param_1) / *(float *)(this + 0x90);
    fVar4 = (float)(int)fVar5;
    *(float *)(this + 0x98) = *(float *)(this + 0x90) * fVar4;
    *(float *)(this + 0x9c) = fVar5 - fVar4;
  }
  if ((this[0xa1] != (CTimeline)0x0) ||
     (cVar1 = CResourceManager::getEditorIsRunning(), cVar1 != '\0')) {
    for (p_Var3 = *(_Rb_tree_node_base **)(this + 0x70);
        (_Rb_tree_node_base *)(this + 0x60) != p_Var3;
        p_Var3 = (_Rb_tree_node_base *)std::_Rb_tree_increment(p_Var3)) {
      p_Var2 = *(_Rb_tree_node_base **)(*(long *)(p_Var3 + 0x28) + 0x18);
      if (p_Var2 != (_Rb_tree_node_base *)(*(long *)(p_Var3 + 0x28) + 8)) {
        do {
          CTimelineProperty::Update(*(CTimelineProperty **)(p_Var2 + 0x28),param_1,(bool)this[0xa0])
          ;
          p_Var2 = (_Rb_tree_node_base *)std::_Rb_tree_increment(p_Var2);
        } while (p_Var2 != (_Rb_tree_node_base *)(*(long *)(p_Var3 + 0x28) + 8));
      }
    }
  }
  return param_1;
}

/* address=007bb000
   symbol=CTimeline::Play_Backwards */

/* CTimeline::Play_Backwards() */

void __thiscall CTimeline::Play_Backwards(CTimeline *this)

{
  if ((this[0xa1] != (CTimeline)0x0) && (this[0xa0] != (CTimeline)0x0)) {
    return;
  }
  this[0xa0] = (CTimeline)0x1;
  this[0xa1] = (CTimeline)0x1;
  resetPropertiesToPercent(this,DAT_00fc75dc);
  SetTimelinePercentDone(this,DAT_00fc75dc);
  (**(code **)(*(long *)this + 0x30))(this,0x24);
                    /* WARNING: Could not recover jumptable at 0x007bb059. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)this + 0x30))(this,0x29);
  return;
}

/* address=007bb070
   symbol=CTimeline::Play */

/* CTimeline::Play(bool) */

void __thiscall CTimeline::Play(CTimeline *this,bool param_1)

{
  if (!param_1) {
    Play_Backwards(this);
    return;
  }
  if ((this[0xa1] != (CTimeline)0x0) && (this[0xa0] == (CTimeline)0x0)) {
    return;
  }
  this[0xa0] = (CTimeline)0x0;
  this[0xa1] = (CTimeline)0x1;
  resetPropertiesToPercent(this,DAT_00fc75d8);
  SetTimelinePercentDone(this,DAT_00fc75d8);
  (**(code **)(*(long *)this + 0x30))(this,0x24);
                    /* WARNING: Could not recover jumptable at 0x007bb0ce. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)this + 0x30))(this,0x2a);
  return;
}

/* address=007bb0f0
   symbol=CTimeline::StopToBeginning */

/* CTimeline::StopToBeginning() */

void __thiscall CTimeline::StopToBeginning(CTimeline *this)

{
  if (this[0xa1] == (CTimeline)0x0) {
    return;
  }
  this[0xa1] = (CTimeline)0x0;
  resetPropertiesToPercent(this,DAT_00fc75d8);
  SetTimelinePercentDone(this,DAT_00fc75d8);
  (**(code **)(*(long *)this + 0x30))(this,0x23);
                    /* WARNING: Could not recover jumptable at 0x007bb14b. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)this + 0x30))(this,~-(uint)(this[0xa0] == (CTimeline)0x0) + 0x2c);
  return;
}

/* address=007bb150
   symbol=CTimeline::StopToEnd */

/* CTimeline::StopToEnd() */

void __thiscall CTimeline::StopToEnd(CTimeline *this)

{
  if (this[0xa1] == (CTimeline)0x0) {
    return;
  }
  this[0xa1] = (CTimeline)0x0;
  resetPropertiesToPercent(this,DAT_00fc75dc);
  SetTimelinePercentDone(this,DAT_00fc75dc);
  (**(code **)(*(long *)this + 0x30))(this,0x23);
                    /* WARNING: Could not recover jumptable at 0x007bb1ab. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)this + 0x30))(this,~-(uint)(this[0xa0] == (CTimeline)0x0) + 0x2c);
  return;
}

/* address=007bb1b0
   symbol=CTimeline::Stop */

/* CTimeline::Stop() */

void __thiscall CTimeline::Stop(CTimeline *this)

{
  if (this[0xa0] == (CTimeline)0x0) {
    if (DAT_00fa47f8 < *(float *)(this + 0x98)) {
      StopToBeginning(this);
      return;
    }
  }
  else if (*(float *)(this + 0x98) <= DAT_00fa47fc && DAT_00fa47fc != *(float *)(this + 0x98)) {
    StopToEnd(this);
    return;
  }
  return;
}

/* address=007bb200
   symbol=CTimeline::rewindToStart */

/* CTimeline::rewindToStart() */

void __thiscall CTimeline::rewindToStart(CTimeline *this)

{
  float fVar1;

  fVar1 = DAT_00fc75d8;
  this[0xa1] = (CTimeline)0x1;
  resetPropertiesToPercent(this,fVar1);
  SetTimelinePercentDone(this,DAT_00fc75d8);
  (**(code **)(*(long *)this + 0x30))(this,0x23);
  (**(code **)(*(long *)this + 0x30))(this,0x2b);
  this[0xa1] = (CTimeline)0x0;
  return;
}

/* address=007bb250
   symbol=CTimeline::fastFowardToEnd */

/* CTimeline::fastFowardToEnd() */

void __thiscall CTimeline::fastFowardToEnd(CTimeline *this)

{
  float fVar1;

  fVar1 = DAT_00fc75dc;
  this[0xa1] = (CTimeline)0x1;
  resetPropertiesToPercent(this,fVar1);
  SetTimelinePercentDone(this,DAT_00fc75dc);
  (**(code **)(*(long *)this + 0x30))(this,0x23);
  (**(code **)(*(long *)this + 0x30))(this,0x2c);
  this[0xa1] = (CTimeline)0x0;
  return;
}

/* address=007bb2a0
   symbol=CTimeline::Reset_To_Beginning */

/* CTimeline::Reset_To_Beginning() */

void __thiscall CTimeline::Reset_To_Beginning(CTimeline *this)

{
  if (*(float *)(this + 0x98) != DAT_00fc75d8) {
    resetPropertiesToPercent(this,DAT_00fc75d8);
    SetTimelinePercentDone(this,DAT_00fc75d8);
                    /* WARNING: Could not recover jumptable at 0x007bb2f0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*(long *)this + 0x30))(this,0x26);
    return;
  }
  return;
}

/* address=007bb300
   symbol=CTimeline::Reset_To_End */

/* CTimeline::Reset_To_End() */

void __thiscall CTimeline::Reset_To_End(CTimeline *this)

{
  if (*(float *)(this + 0x98) != DAT_00fc75dc) {
    resetPropertiesToPercent(this,DAT_00fc75dc);
    SetTimelinePercentDone(this,DAT_00fc75dc);
                    /* WARNING: Could not recover jumptable at 0x007bb350. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*(long *)this + 0x30))(this,0x27);
    return;
  }
  return;
}

/* address=007bb720
   symbol=CTimeline::saveTimelineToDataGroup */

/* WARNING: Removing unreachable block (ram,0x007bbef5) */
/* WARNING: Removing unreachable block (ram,0x007bbe1c) */
/* WARNING: Removing unreachable block (ram,0x007bc0b6) */
/* WARNING: Removing unreachable block (ram,0x007bc025) */
/* WARNING: Removing unreachable block (ram,0x007bbfc3) */
/* WARNING: Removing unreachable block (ram,0x007bbe64) */
/* WARNING: Removing unreachable block (ram,0x007bc0ab) */
/* WARNING: Removing unreachable block (ram,0x007bbe6f) */
/* WARNING: Removing unreachable block (ram,0x007bbfd5) */
/* WARNING: Removing unreachable block (ram,0x007bbf86) */
/* WARNING: Removing unreachable block (ram,0x007bbeea) */
/* WARNING: Removing unreachable block (ram,0x007bc063) */
/* WARNING: Removing unreachable block (ram,0x007bbf32) */
/* CTimeline::saveTimelineToDataGroup(CEditorScene*, CDataGroup*) */

void __thiscall
CTimeline::saveTimelineToDataGroup(CTimeline *this,CEditorScene *param_1,CDataGroup *param_2)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  longlong lVar4;
  CDescriptor *this_00;
  bool bVar5;
  char cVar6;
  int iVar7;
  uint uVar8;
  CDataGroup *this_01;
  long lVar9;
  long lVar10;
  CDataGroup *this_02;
  long lVar11;
  CTimelineProperty *this_03;
  CDataGroup *this_04;
  undefined8 uVar12;
  int iVar13;
  float fVar14;
  CDataGroup *local_190;
  int local_184;
  uint local_164;
  int local_160;
  long local_138 [2];
  long local_128 [2];
  long local_118 [2];
  long local_108 [2];
  long local_f8 [2];
  long local_e8 [2];
  long local_d8 [2];
  long local_c8 [2];
  long local_b8 [2];
  undefined8 local_a8;
  long local_98 [2];
  long local_88 [2];
  long local_78 [2];
  long local_68 [4];
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

  uVar3 = *(uint *)(this + 0x80);
                    /* try { // try from 007bb760 to 007bb764 has its CatchHandler @ 007bbe62 */
  std::wstring::wstring((wstring_conflict *)local_68,L"TIMELINEDATA",local_39);
                    /* try { // try from 007bb76b to 007bb76f has its CatchHandler @ 007bbe55 */
  this_01 = (CDataGroup *)CDataGroup::AddDataGroup(param_2,(wstring_conflict *)local_68);
  if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_68[0] + -8);
    iVar7 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar7 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
    }
  }
  lVar4 = *(longlong *)(this + 0x20);
                    /* try { // try from 007bb7b1 to 007bb7b5 has its CatchHandler @ 007bbe27 */
  std::wstring::wstring((wstring_conflict *)local_78,L"ID",&local_3a);
                    /* try { // try from 007bb7c1 to 007bb7c5 has its CatchHandler @ 007bbfbe */
  CDataGroup::AddDataValue(this_01,(wstring_conflict *)local_78,lVar4);
  if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_78[0] + -8);
    iVar7 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar7 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
    }
  }
  if (uVar3 != 0) {
    local_164 = 1;
    local_160 = 0;
    do {
      lVar9 = GetObjectIDInTimelineByIndex(this,local_160);
      if (lVar9 != -1) {
        lVar10 = CEditorScene::GetObjectInScene(param_1,lVar9);
        if ((lVar10 != 0) && (cVar6 = CEditorBaseObject::HasBaseObjectFlag(lVar10,8), cVar6 == '\0')
           ) {
                    /* try { // try from 007bb85a to 007bb85e has its CatchHandler @ 007bbe11 */
          std::wstring::wstring((wstring_conflict *)local_88,L"TIMELINEOBJECT",&local_3b);
                    /* try { // try from 007bb867 to 007bb86b has its CatchHandler @ 007bc0a6 */
          this_02 = (CDataGroup *)CDataGroup::AddDataGroup(this_01,(wstring_conflict *)local_88);
          if ((allocator *)(local_88[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_88[0] + -8);
            iVar7 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar7 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
            }
          }
          lVar4 = *(longlong *)(lVar10 + 0x20);
                    /* try { // try from 007bb8a7 to 007bb8ab has its CatchHandler @ 007bc075 */
          std::wstring::wstring((wstring_conflict *)local_98,L"OBJECTID",&local_3c);
                    /* try { // try from 007bb8b7 to 007bb8bb has its CatchHandler @ 007bc06e */
          CDataGroup::AddDataValue(this_02,(wstring_conflict *)local_98,lVar4);
          if ((allocator *)(local_98[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_98[0] + -8);
            iVar7 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar7 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
            }
          }
          this_00 = *(CDescriptor **)(lVar10 + 0x38);
          if (this_00 != (CDescriptor *)0x0) {
            local_a8 = GetPropertyIDForObjectInTimelineByIndex(this,lVar9,0);
            local_184 = 0;
LAB_007bb908:
            uVar8 = (uint)local_a8;
            if (-1 < (int)(uint)local_a8) {
              do {
                if (local_a8._4_1_ == '\0') {
                  lVar11 = CDescriptor::GetPropertyByIndex(this_00,uVar8);
                  if (lVar11 == 0) goto LAB_007bb908;
                    /* try { // try from 007bb94f to 007bb953 has its CatchHandler @ 007bbee5 */
                  std::wstring::wstring
                            ((wstring_conflict *)local_b8,L"TIMELINEOBJECTPROPERTY",&local_3d);
                    /* try { // try from 007bb95c to 007bb960 has its CatchHandler @ 007bbed4 */
                  local_190 = (CDataGroup *)
                              CDataGroup::AddDataGroup(this_02,(wstring_conflict *)local_b8);
                  if ((allocator *)(local_b8[0] + -0x18) !=
                      (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                    LOCK();
                    piVar1 = (int *)(local_b8[0] + -8);
                    iVar7 = *piVar1;
                    *piVar1 = *piVar1 + -1;
                    UNLOCK();
                    if (iVar7 < 1) {
                      std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
                    }
                  }
                    /* try { // try from 007bb997 to 007bb99b has its CatchHandler @ 007bbea3 */
                  std::wstring::wstring
                            ((wstring_conflict *)local_c8,L"OBJECTPROPERTYNAME",&local_3e);
                    /* try { // try from 007bb9a9 to 007bb9ad has its CatchHandler @ 007bc05e */
                  CDataGroup::AddDataValue
                            (local_190,(wstring_conflict *)local_c8,
                             (wstring_conflict *)(lVar11 + 0x10),false);
                  if ((allocator *)(local_c8[0] + -0x18) !=
                      (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                    LOCK();
                    piVar1 = (int *)(local_c8[0] + -8);
                    iVar7 = *piVar1;
                    *piVar1 = *piVar1 + -1;
                    UNLOCK();
                    if (iVar7 < 1) {
                      std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
                    }
                  }
                }
                else {
                    /* try { // try from 007bbc48 to 007bbc4c has its CatchHandler @ 007bc019 */
                  std::wstring::wstring
                            ((wstring_conflict *)local_d8,L"TIMELINEOBJECTEVENT",&local_3f);
                    /* try { // try from 007bbc55 to 007bbc59 has its CatchHandler @ 007bc014 */
                  local_190 = (CDataGroup *)
                              CDataGroup::AddDataGroup(this_02,(wstring_conflict *)local_d8);
                  if ((allocator *)(local_d8[0] + -0x18) !=
                      (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                    LOCK();
                    piVar1 = (int *)(local_d8[0] + -8);
                    iVar7 = *piVar1;
                    *piVar1 = *piVar1 + -1;
                    UNLOCK();
                    if (iVar7 < 1) {
                      std::wstring::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
                    }
                  }
                  lVar11 = CDescriptor::GetInputLogicWrapper
                                     (*(CDescriptor **)(lVar10 + 0x38),(uint)local_a8);
                  if (lVar11 == 0) goto LAB_007bb908;
                    /* try { // try from 007bbcae to 007bbcb2 has its CatchHandler @ 007bbfe3 */
                  std::wstring::wstring((wstring_conflict *)local_e8,L"OBJECTEVENTNAME",&local_40);
                    /* try { // try from 007bbcc0 to 007bbcc4 has its CatchHandler @ 007bbfce */
                  CDataGroup::AddDataValue
                            (local_190,(wstring_conflict *)local_e8,
                             (wstring_conflict *)(lVar11 + 0x20),false);
                  if ((allocator *)(local_e8[0] + -0x18) !=
                      (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                    LOCK();
                    piVar1 = (int *)(local_e8[0] + -8);
                    iVar7 = *piVar1;
                    *piVar1 = *piVar1 + -1;
                    UNLOCK();
                    if (iVar7 < 1) {
                      std::wstring::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
                    }
                  }
                }
                iVar7 = GetPointIDInTimelinePropertyByIndex
                                  (this,lVar9,(uint)local_a8,0,(bool)local_a8._4_1_);
                if (-1 < iVar7) {
                  iVar13 = 0;
                  do {
                    this_03 = (CTimelineProperty *)
                              GetProperty(this,lVar9,(uint)local_a8,(bool)local_a8._4_1_);
                    if (this_03 == (CTimelineProperty *)0x0) {
LAB_007bbbb0:
                    }
                    else {
                    /* try { // try from 007bba61 to 007bba65 has its CatchHandler @ 007bbf2d */
                      std::wstring::wstring((wstring_conflict *)local_f8,L"TIMELINEPOINT",&local_41)
                      ;
                    /* try { // try from 007bba73 to 007bba77 has its CatchHandler @ 007bbf18 */
                      this_04 = (CDataGroup *)
                                CDataGroup::AddDataGroup(local_190,(wstring_conflict *)local_f8);
                      if ((allocator *)(local_f8[0] + -0x18) !=
                          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                        LOCK();
                        piVar1 = (int *)(local_f8[0] + -8);
                        iVar2 = *piVar1;
                        *piVar1 = *piVar1 + -1;
                        UNLOCK();
                        if (iVar2 < 1) {
                          std::wstring::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
                        }
                      }
                      fVar14 = (float)CTimelineProperty::GetTimePercentAtPoint(this_03,iVar7);
                    /* try { // try from 007bbab6 to 007bbaba has its CatchHandler @ 007bbe7d */
                      std::wstring::wstring((wstring_conflict *)local_108,L"TIMEPERCENT",&local_42);
                    /* try { // try from 007bbacc to 007bbad0 has its CatchHandler @ 007bbf03 */
                      CDataGroup::AddDataValue(this_04,(wstring_conflict *)local_108,fVar14);
                      if ((allocator *)(local_108[0] + -0x18) !=
                          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                        LOCK();
                        piVar1 = (int *)(local_108[0] + -8);
                        iVar7 = *piVar1;
                        *piVar1 = *piVar1 + -1;
                        UNLOCK();
                        if (iVar7 < 1) {
                          std::wstring::_Rep::_M_destroy((allocator *)(local_108[0] + -0x18));
                        }
                      }
                      iVar7 = *(int *)(this_03 + 0x48);
                    /* try { // try from 007bbb07 to 007bbb0b has its CatchHandler @ 007bbf81 */
                      std::wstring::wstring
                                ((wstring_conflict *)local_118,L"INTERPOLATION",&local_43);
                    /* try { // try from 007bbb1c to 007bbb20 has its CatchHandler @ 007bbf6c */
                      CDataGroup::AddDataValue
                                (this_04,(wstring_conflict *)local_118,
                                 (wstring_conflict *)(&gTIMELINE_INTERP_TYPES + iVar7),false);
                      if ((allocator *)(local_118[0] + -0x18) !=
                          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                        LOCK();
                        piVar1 = (int *)(local_118[0] + -8);
                        iVar7 = *piVar1;
                        *piVar1 = *piVar1 + -1;
                        UNLOCK();
                        if (iVar7 < 1) {
                          std::wstring::_Rep::_M_destroy((allocator *)(local_118[0] + -0x18));
                        }
                      }
                      if (local_a8._4_1_ == '\0') {
                        CTimelineProperty::GetValueAtPointAsString((int)local_128);
                    /* try { // try from 007bbb6d to 007bbb71 has its CatchHandler @ 007bbe9e */
                        std::wstring::wstring((wstring_conflict *)local_138,L"VALUE",&local_44);
                    /* try { // try from 007bbb84 to 007bbb88 has its CatchHandler @ 007bbe7f */
                        CDataGroup::AddDataValue
                                  (this_04,(wstring_conflict *)local_138,
                                   (wstring_conflict *)local_128,false);
                        if ((allocator *)(local_138[0] + -0x18) !=
                            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                          LOCK();
                          piVar1 = (int *)(local_138[0] + -8);
                          iVar7 = *piVar1;
                          *piVar1 = *piVar1 + -1;
                          UNLOCK();
                          if (iVar7 < 1) {
                            std::wstring::_Rep::_M_destroy((allocator *)(local_138[0] + -0x18));
                          }
                        }
                        if ((allocator *)(local_128[0] + -0x18) !=
                            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                          LOCK();
                          piVar1 = (int *)(local_128[0] + -8);
                          iVar7 = *piVar1;
                          *piVar1 = *piVar1 + -1;
                          UNLOCK();
                          if (iVar7 < 1) {
                            std::wstring::_Rep::_M_destroy((allocator *)(local_128[0] + -0x18));
                            goto LAB_007bb9f8;
                          }
                        }
                        goto LAB_007bbbb0;
                      }
                    }
LAB_007bb9f8:
                    iVar13 = iVar13 + 1;
                    iVar7 = GetPointIDInTimelinePropertyByIndex
                                      (this,lVar9,(uint)local_a8,iVar13,(bool)local_a8._4_1_);
                  } while (-1 < iVar7);
                }
                local_184 = local_184 + 1;
                uVar12 = GetPropertyIDForObjectInTimelineByIndex(this,lVar9,local_184);
                uVar8 = (uint)uVar12;
                local_a8._0_5_ = (undefined5)uVar12;
                if ((int)uVar8 < 0) break;
              } while( true );
            }
          }
        }
        GetObjectIDInTimelineByIndex(this,local_164);
      }
      local_160 = local_160 + 1;
      bVar5 = local_164 < uVar3;
      local_164 = local_164 + 1;
    } while (bVar5);
  }
  return;
}

/* address=007bc0d0
   symbol=CTimeline::loadTimelineFromDataGroup */

/* WARNING: Removing unreachable block (ram,0x007bc8c2) */
/* WARNING: Removing unreachable block (ram,0x007bc8db) */
/* WARNING: Removing unreachable block (ram,0x007bc953) */
/* WARNING: Removing unreachable block (ram,0x007bcba5) */
/* WARNING: Removing unreachable block (ram,0x007bc8b7) */
/* WARNING: Removing unreachable block (ram,0x007bcb69) */
/* WARNING: Removing unreachable block (ram,0x007bcbb7) */
/* WARNING: Removing unreachable block (ram,0x007bcade) */
/* WARNING: Removing unreachable block (ram,0x007bc945) */
/* WARNING: Removing unreachable block (ram,0x007bca6c) */
/* WARNING: Removing unreachable block (ram,0x007bc8cd) */
/* WARNING: Removing unreachable block (ram,0x007bc9ce) */
/* WARNING: Removing unreachable block (ram,0x007bc9c3) */
/* WARNING: Removing unreachable block (ram,0x007bc960) */
/* CTimeline::loadTimelineFromDataGroup(CEditorScene*, CDataGroup*, CDescriptorLoadConfiguration*)
    */

void __thiscall
CTimeline::loadTimelineFromDataGroup
          (CTimeline *this,CEditorScene *param_1,CDataGroup *param_2,
          CDescriptorLoadConfiguration *param_3)

{
  int *piVar1;
  wchar_t wVar2;
  uint uVar3;
  CDataGroup *this_00;
  CDescriptor *this_01;
  CDataGroup *this_02;
  size_t sVar4;
  CDataGroup *this_03;
  wchar_t *pwVar5;
  int iVar6;
  int iVar7;
  CDataGroup *this_04;
  longlong lVar8;
  long lVar9;
  long lVar10;
  wchar_t *pwVar11;
  wstring_conflict *pwVar12;
  long lVar13;
  uint uVar14;
  undefined8 *puVar15;
  float fVar16;
  uint local_17c;
  bool local_155;
  uint local_154;
  uint local_12c;
  long local_120;
  long local_108 [2];
  long local_f8 [2];
  long local_e8 [2];
  wchar_t *local_d8 [2];
  long local_c8 [2];
  long local_b8 [2];
  wchar_t *local_a8 [2];
  long local_98 [2];
  wchar_t *local_88 [2];
  long local_78 [2];
  long local_68 [2];
  long local_58 [3];
  allocator local_40;
  allocator local_3f;
  allocator local_3e;
  allocator local_3d;
  allocator local_3c;
  allocator local_3b;
  allocator local_3a;
  allocator local_39 [9];

  if (((param_2 != (CDataGroup *)0x0) && (param_1 != (CEditorScene *)0x0)) &&
     (param_3 != (CDescriptorLoadConfiguration *)0x0)) {
                    /* try { // try from 007bc126 to 007bc12a has its CatchHandler @ 007bc87c */
    std::wstring::wstring((wstring_conflict *)local_58,L"TIMELINEDATA",local_39);
                    /* try { // try from 007bc133 to 007bc137 has its CatchHandler @ 007bc87e */
    this_04 = (CDataGroup *)
              CDataGroup::GetDataGroupByName(param_2,(wstring_conflict *)local_58,false);
    if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_58[0] + -8);
      iVar6 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar6 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
      }
    }
    if (this_04 != (CDataGroup *)0x0) {
                    /* try { // try from 007bc17c to 007bc180 has its CatchHandler @ 007bc871 */
      std::wstring::wstring((wstring_conflict *)local_68,L"ID",&local_3a);
                    /* try { // try from 007bc18d to 007bc191 has its CatchHandler @ 007bcb64 */
      lVar8 = CDataGroup::GetDataValue(this_04,(wstring_conflict *)local_68,-1);
      if ((allocator *)(local_68[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_68[0] + -8);
        iVar6 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar6 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
        }
      }
      lVar9 = CDescriptorLoadConfiguration::getRemappedID(param_3,lVar8);
      if (lVar9 == *(long *)(this + 0x10)) {
        uVar3 = *(uint *)(this_04 + 0x40);
        local_120 = 0;
        for (local_12c = 0; local_12c < uVar3; local_12c = local_12c + 1) {
          if (local_12c < *(uint *)(this_04 + 0x44)) {
            puVar15 = (undefined8 *)(local_120 + *(long *)(this_04 + 0x38));
          }
          else {
            puVar15 = *(undefined8 **)(this_04 + 0x38);
          }
          this_00 = (CDataGroup *)*puVar15;
                    /* try { // try from 007bc227 to 007bc22b has its CatchHandler @ 007bcb26 */
          std::wstring::wstring((wstring_conflict *)local_78,L"OBJECTID",&local_3b);
                    /* try { // try from 007bc238 to 007bc23c has its CatchHandler @ 007bcba0 */
          lVar8 = CDataGroup::GetDataValue(this_00,(wstring_conflict *)local_78,-1);
          if ((allocator *)(local_78[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_78[0] + -8);
            iVar6 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar6 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
            }
          }
          lVar9 = CDescriptorLoadConfiguration::getRemappedID(param_3,lVar8);
          if (((lVar9 != -1) &&
              (lVar10 = CEditorScene::GetObjectInScene(param_1,lVar9), lVar10 != 0)) &&
             ((this_01 = *(CDescriptor **)(lVar10 + 0x38), this_01 != (CDescriptor *)0x0 &&
              (*(int *)(this_00 + 0x40) != 0)))) {
            local_154 = 0;
            do {
              if (local_154 < *(uint *)(this_00 + 0x44)) {
                puVar15 = (undefined8 *)((ulong)local_154 * 8 + *(long *)(this_00 + 0x38));
              }
              else {
                puVar15 = *(undefined8 **)(this_00 + 0x38);
              }
              this_02 = (CDataGroup *)*puVar15;
              pwVar11 = (wchar_t *)CDataGroup::GetGroupName(this_02);
              iVar6 = std::wstring::compare(pwVar11);
              if (iVar6 != 0) {
                pwVar11 = (wchar_t *)CDataGroup::GetGroupName(this_02);
                iVar6 = std::wstring::compare(pwVar11);
                if (iVar6 != 0) {
                  return;
                }
              }
                    /* try { // try from 007bc303 to 007bc307 has its CatchHandler @ 007bcbb2 */
              std::wstring::wstring((wstring_conflict *)local_98,L"OBJECTPROPERTYNAME",&local_3c);
                    /* try { // try from 007bc313 to 007bc327 has its CatchHandler @ 007bcb21 */
              pwVar12 = (wstring_conflict *)
                        CDataGroup::GetDataValue
                                  (this_02,(wstring_conflict *)local_98,
                                   (wstring_conflict *)&::EMPTY_WSTRING);
              STRINGS::StringUpper((STRINGS *)local_88,pwVar12);
              if ((allocator *)(local_98[0] + -0x18) !=
                  (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar1 = (int *)(local_98[0] + -8);
                iVar6 = *piVar1;
                *piVar1 = *piVar1 + -1;
                UNLOCK();
                if (iVar6 < 1) {
                  std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
                }
              }
                    /* try { // try from 007bc355 to 007bc359 has its CatchHandler @ 007bcae9 */
              std::wstring::wstring((wstring_conflict *)local_b8,L"OBJECTEVENTNAME",&local_3d);
                    /* try { // try from 007bc365 to 007bc379 has its CatchHandler @ 007bcace */
              pwVar12 = (wstring_conflict *)
                        CDataGroup::GetDataValue
                                  (this_02,(wstring_conflict *)local_b8,
                                   (wstring_conflict *)&::EMPTY_WSTRING);
              std::wstring::wstring((wstring_conflict *)local_a8,pwVar12);
              if ((allocator *)(local_b8[0] + -0x18) !=
                  (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar1 = (int *)(local_b8[0] + -8);
                iVar6 = *piVar1;
                *piVar1 = *piVar1 + -1;
                UNLOCK();
                if (iVar6 < 1) {
                  std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
                }
              }
              pwVar11 = ::EMPTY_WSTRING;
              sVar4 = *(size_t *)(local_88[0] + -6);
              if ((sVar4 == *(size_t *)(::EMPTY_WSTRING + -6)) &&
                 (iVar6 = wmemcmp(local_88[0],::EMPTY_WSTRING,sVar4), pwVar5 = local_a8[0],
                 iVar6 == 0)) {
                if ((sVar4 != *(size_t *)(local_a8[0] + -6)) ||
                   (iVar6 = wmemcmp(local_a8[0],pwVar11,sVar4), iVar6 != 0)) {
                    /* try { // try from 007bc707 to 007bc72a has its CatchHandler @ 007bca96 */
                  lVar13 = CDescriptor::GetInputLogicWrapper(*(CDescriptor **)(lVar10 + 0x38),0);
                  local_17c = 0;
                  while (pwVar5 = local_a8[0], lVar13 != 0) {
                    if ((*(size_t *)(local_a8[0] + -6) ==
                         *(size_t *)(*(wchar_t **)(lVar13 + 0x20) + -6)) &&
                       (iVar6 = wmemcmp(local_a8[0],*(wchar_t **)(lVar13 + 0x20),
                                        *(size_t *)(local_a8[0] + -6)), iVar6 == 0)) {
                      local_155 = true;
                      pwVar5 = local_a8[0];
                      if (local_17c != 0xffffffff) goto LAB_007bc3d2;
                      break;
                    }
                    local_17c = local_17c + 1;
                    lVar13 = CDescriptor::GetInputLogicWrapper
                                       (*(CDescriptor **)(lVar10 + 0x38),local_17c);
                  }
                }
LAB_007bc76f:
                if ((allocator *)(pwVar5 + -6) !=
                    (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                  LOCK();
                  pwVar11 = pwVar5 + -2;
                  wVar2 = *pwVar11;
                  *pwVar11 = *pwVar11 + L'\xffffffff';
                  UNLOCK();
                  if (wVar2 < L'\x01') {
                    std::wstring::_Rep::_M_destroy((allocator *)(pwVar5 + -6));
                  }
                }
                if ((allocator *)(local_88[0] + -6) !=
                    (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                  LOCK();
                  pwVar11 = local_88[0] + -2;
                  wVar2 = *pwVar11;
                  *pwVar11 = *pwVar11 + L'\xffffffff';
                  UNLOCK();
                  if (wVar2 < L'\x01') {
                    std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -6));
                  }
                }
              }
              else {
                    /* try { // try from 007bc3b9 to 007bc3f5 has its CatchHandler @ 007bca96 */
                local_17c = CDescriptor::GetPropertyID(this_01,(wstring_conflict *)local_88);
                local_155 = false;
                pwVar5 = local_a8[0];
                if (local_17c == 0xffffffff) goto LAB_007bc76f;
LAB_007bc3d2:
                AddProperty(this,param_1,lVar9,local_17c,local_155);
                if (*(int *)(this_02 + 0x40) != 0) {
                  uVar14 = 0;
                  do {
                    if (uVar14 < *(uint *)(this_02 + 0x44)) {
                      puVar15 = (undefined8 *)((ulong)uVar14 * 8 + *(long *)(this_02 + 0x38));
                    }
                    else {
                      puVar15 = *(undefined8 **)(this_02 + 0x38);
                    }
                    this_03 = (CDataGroup *)*puVar15;
                    /* try { // try from 007bc432 to 007bc436 has its CatchHandler @ 007bca94 */
                    std::wstring::wstring((wstring_conflict *)local_c8,L"TIMEPERCENT",&local_3e);
                    /* try { // try from 007bc447 to 007bc44b has its CatchHandler @ 007bca7f */
                    fVar16 = (float)CDataGroup::GetDataValue
                                              (this_03,(wstring_conflict *)local_c8,0.0);
                    if ((allocator *)(local_c8[0] + -0x18) !=
                        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                      LOCK();
                      piVar1 = (int *)(local_c8[0] + -8);
                      iVar6 = *piVar1;
                      *piVar1 = *piVar1 + -1;
                      UNLOCK();
                      if (iVar6 < 1) {
                        std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
                      }
                    }
                    /* try { // try from 007bc47c to 007bc480 has its CatchHandler @ 007bca77 */
                    std::wstring::wstring((wstring_conflict *)local_e8,L"INTERPOLATION",&local_3f);
                    /* try { // try from 007bc493 to 007bc4a7 has its CatchHandler @ 007bca58 */
                    pwVar12 = (wstring_conflict *)
                              CDataGroup::GetDataValue
                                        (this_03,(wstring_conflict *)local_e8,
                                         (wstring_conflict *)&DAT_01472098);
                    std::wstring::wstring((wstring_conflict *)local_d8,pwVar12);
                    if ((allocator *)(local_e8[0] + -0x18) !=
                        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                      LOCK();
                      piVar1 = (int *)(local_e8[0] + -8);
                      iVar6 = *piVar1;
                      *piVar1 = *piVar1 + -1;
                      UNLOCK();
                      if (iVar6 < 1) {
                        std::wstring::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
                      }
                    }
                    pwVar11 = local_d8[0];
                    puVar15 = &gTIMELINE_INTERP_TYPES;
                    iVar6 = 0;
                    sVar4 = *(size_t *)(local_d8[0] + -6);
                    do {
                      if ((*(size_t *)((wchar_t *)*puVar15 + -6) == sVar4) &&
                         (iVar7 = wmemcmp(pwVar11,(wchar_t *)*puVar15,sVar4), iVar7 == 0))
                      goto LAB_007bc4fe;
                      iVar6 = iVar6 + 1;
                      puVar15 = puVar15 + 1;
                    } while (iVar6 != 8);
                    iVar6 = 7;
LAB_007bc4fe:
                    /* try { // try from 007bc510 to 007bc54d has its CatchHandler @ 007bca53 */
                    iVar7 = AddPointToProperty(this,lVar9,local_17c,local_155);
                    SetPropertyPointTimePercent(this,lVar9,local_17c,iVar7,fVar16,local_155);
                    SetPropertyPointInterpolationType(this,lVar9,local_17c,iVar6);
                    if (local_155 == false) {
                    /* try { // try from 007bc56e to 007bc572 has its CatchHandler @ 007bca6a */
                      std::wstring::wstring((wstring_conflict *)local_108,L"VALUE",&local_40);
                    /* try { // try from 007bc585 to 007bc599 has its CatchHandler @ 007bca41 */
                      pwVar12 = (wstring_conflict *)
                                CDataGroup::GetDataValue
                                          (this_03,(wstring_conflict *)local_108,
                                           (wstring_conflict *)&::EMPTY_WSTRING);
                      std::wstring::wstring((wstring_conflict *)local_f8,pwVar12);
                      if ((allocator *)(local_108[0] + -0x18) !=
                          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                        LOCK();
                        piVar1 = (int *)(local_108[0] + -8);
                        iVar6 = *piVar1;
                        *piVar1 = *piVar1 + -1;
                        UNLOCK();
                        if (iVar6 < 1) {
                          std::wstring::_Rep::_M_destroy((allocator *)(local_108[0] + -0x18));
                        }
                      }
                    /* try { // try from 007bc5c8 to 007bc5cc has its CatchHandler @ 007bc9d9 */
                      SetPropertyPointValueByString
                                (this,lVar9,local_17c,iVar7,(wstring_conflict *)local_f8);
                      if ((allocator *)(local_f8[0] + -0x18) !=
                          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                        LOCK();
                        piVar1 = (int *)(local_f8[0] + -8);
                        iVar6 = *piVar1;
                        *piVar1 = *piVar1 + -1;
                        UNLOCK();
                        if (iVar6 < 1) {
                          std::wstring::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
                        }
                      }
                    }
                    if ((allocator *)(local_d8[0] + -6) !=
                        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                      LOCK();
                      pwVar11 = local_d8[0] + -2;
                      wVar2 = *pwVar11;
                      *pwVar11 = *pwVar11 + L'\xffffffff';
                      UNLOCK();
                      if (wVar2 < L'\x01') {
                        std::wstring::_Rep::_M_destroy((allocator *)(local_d8[0] + -6));
                      }
                    }
                    uVar14 = uVar14 + 1;
                  } while (uVar14 < *(uint *)(this_02 + 0x40));
                }
                if ((allocator *)(local_a8[0] + -6) !=
                    (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                  LOCK();
                  pwVar11 = local_a8[0] + -2;
                  wVar2 = *pwVar11;
                  *pwVar11 = *pwVar11 + L'\xffffffff';
                  UNLOCK();
                  if (wVar2 < L'\x01') {
                    std::wstring::_Rep::_M_destroy((allocator *)(local_a8[0] + -6));
                  }
                }
                if ((allocator *)(local_88[0] + -6) !=
                    (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                  LOCK();
                  pwVar11 = local_88[0] + -2;
                  wVar2 = *pwVar11;
                  *pwVar11 = *pwVar11 + L'\xffffffff';
                  UNLOCK();
                  if (wVar2 < L'\x01') {
                    std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -6));
                  }
                }
              }
              local_154 = local_154 + 1;
            } while (local_154 < *(uint *)(this_00 + 0x40));
          }
          local_120 = local_120 + 8;
        }
        Reset_To_Beginning(this);
      }
    }
  }
  return;
}

/* export-summary functions=41 failures=0 */
