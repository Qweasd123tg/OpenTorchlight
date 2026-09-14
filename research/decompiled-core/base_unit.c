/* Targeted Ghidra class export.
   namespace=CBaseUnit
   Treat pseudocode as navigation evidence. */


/* address=007f5f40
   symbol=CBaseUnit::hasUnitTheme */

/* CBaseUnit::hasUnitTheme(CUnitTheme*) */

undefined4 __thiscall CBaseUnit::hasUnitTheme(CBaseUnit *this,CUnitTheme *param_1)

{
  long *plVar1;
  uint uVar2;
  long *plVar3;

  if (*(uint *)(this + 0x158) != 0) {
    plVar3 = *(long **)(this + 0x150);
    uVar2 = 0;
    if (param_1 == (CUnitTheme *)*plVar3) {
      return 1;
    }
    do {
      uVar2 = uVar2 + 1;
      if (*(uint *)(this + 0x158) <= uVar2) goto LAB_007f5f75;
      plVar1 = plVar3 + 1;
      plVar3 = plVar3 + 1;
    } while (param_1 != (CUnitTheme *)*plVar1);
    if (uVar2 != 0xffffffff) {
      return 1;
    }
  }
LAB_007f5f75:
  if (*(uint *)(this + 0x140) != 0) {
    plVar3 = *(long **)(this + 0x138);
    uVar2 = 0;
    if (param_1 == (CUnitTheme *)*plVar3) {
      return 1;
    }
    while (uVar2 = uVar2 + 1, uVar2 < *(uint *)(this + 0x140)) {
      plVar1 = plVar3 + 1;
      plVar3 = plVar3 + 1;
      if (param_1 == (CUnitTheme *)*plVar1) {
        return CONCAT31((int3)(uVar2 >> 8),uVar2 != 0xffffffff);
      }
    }
  }
  return 0;
}



/* address=007f5fd0
   symbol=CBaseUnit::setSpawnerGuid */

/* CBaseUnit::setSpawnerGuid(long long) */

void __thiscall CBaseUnit::setSpawnerGuid(CBaseUnit *this,longlong param_1)

{
  *(longlong *)(this + 0x180) = param_1;
  return;
}



/* address=007f5fe0
   symbol=CBaseUnit::getCastsShadows */

/* CBaseUnit::getCastsShadows() */

CBaseUnit __thiscall CBaseUnit::getCastsShadows(CBaseUnit *this)

{
  return this[0x1a9];
}



/* address=007f5ff0
   symbol=CBaseUnit::getMinBounds */

/* CBaseUnit::getMinBounds() */

undefined4 * __thiscall CBaseUnit::getMinBounds(CBaseUnit *this)

{
  undefined4 *puVar1;

  puVar1 = &Ogre::Vector3::ZERO;
  if (*(long *)(this + 0x1c0) != 0) {
    puVar1 = (undefined4 *)(*(long *)(this + 0x1c0) + 0x40);
  }
  return puVar1;
}



/* address=007f6010
   symbol=CBaseUnit::getMaxBounds */

/* CBaseUnit::getMaxBounds() */

undefined4 * __thiscall CBaseUnit::getMaxBounds(CBaseUnit *this)

{
  undefined4 *puVar1;

  puVar1 = &Ogre::Vector3::ZERO;
  if (*(long *)(this + 0x1c0) != 0) {
    puVar1 = (undefined4 *)(*(long *)(this + 0x1c0) + 0x4c);
  }
  return puVar1;
}



/* address=007f6030
   symbol=CBaseUnit::getLocalMinBounds */

/* CBaseUnit::getLocalMinBounds() */

undefined4 * __thiscall CBaseUnit::getLocalMinBounds(CBaseUnit *this)

{
  undefined4 *puVar1;

  puVar1 = &Ogre::Vector3::ZERO;
  if (*(long *)(this + 0x1c0) != 0) {
    puVar1 = (undefined4 *)(*(long *)(this + 0x1c0) + 0x28);
  }
  return puVar1;
}



/* address=007f6050
   symbol=CBaseUnit::getLocalMaxBounds */

/* CBaseUnit::getLocalMaxBounds() */

undefined4 * __thiscall CBaseUnit::getLocalMaxBounds(CBaseUnit *this)

{
  undefined4 *puVar1;

  puVar1 = &Ogre::Vector3::ZERO;
  if (*(long *)(this + 0x1c0) != 0) {
    puVar1 = (undefined4 *)(*(long *)(this + 0x1c0) + 0x34);
  }
  return puVar1;
}



/* address=007f6070
   symbol=CBaseUnit::deactivateUnitInLevel */

/* CBaseUnit::deactivateUnitInLevel() */

void __thiscall CBaseUnit::deactivateUnitInLevel(CBaseUnit *this)

{
  this[0x198] = (CBaseUnit)0x0;
                    /* WARNING: Could not recover jumptable at 0x007f6083. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)this + 0x1d0))(this,0);
  return;
}



/* address=007f6090
   symbol=CBaseUnit::setHighlighted */

/* CBaseUnit::setHighlighted(bool) */

void __thiscall CBaseUnit::setHighlighted(CBaseUnit *this,bool param_1)

{
  long lVar1;
  long *plVar2;

  this[0x1a8] = (CBaseUnit)param_1;
  lVar1 = (**(code **)(*(long *)this + 0x1e0))();
  if (lVar1 != 0) {
    plVar2 = (long *)(**(code **)(*(long *)this + 0x1e0))(this);
                    /* WARNING: Could not recover jumptable at 0x007f60ca. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*plVar2 + 0x1e0))(plVar2,this[0x1a8],*(code **)(*plVar2 + 0x1e0));
    return;
  }
  return;
}



/* address=007f60e0
   symbol=CBaseUnit::hasUnitTheme */

/* CBaseUnit::hasUnitTheme(long long) */

void __thiscall CBaseUnit::hasUnitTheme(CBaseUnit *this,longlong param_1)

{
  long lVar1;
  long lVar2;
  long lVar3;
  uint uVar4;
  undefined8 *puVar5;

  lVar2 = CUnitThemes::getSingleton();
  if (lVar2 == 0) {
    return;
  }
  if (*(uint *)(lVar2 + 0x20) != 0) {
    lVar3 = 0;
    uVar4 = 0;
    do {
      if (uVar4 < *(uint *)(lVar2 + 0x24)) {
        lVar1 = *(long *)(*(long *)(lVar3 + *(long *)(lVar2 + 0x18)) + 0x30);
      }
      else {
        lVar1 = *(long *)(**(long **)(lVar2 + 0x18) + 0x30);
      }
      if (param_1 == lVar1) {
        if (uVar4 < *(uint *)(lVar2 + 0x24)) {
          puVar5 = (undefined8 *)((ulong)uVar4 * 8 + *(long *)(lVar2 + 0x18));
        }
        else {
          puVar5 = *(undefined8 **)(lVar2 + 0x18);
        }
        hasUnitTheme(this,(CUnitTheme *)*puVar5);
        return;
      }
      uVar4 = uVar4 + 1;
      lVar3 = lVar3 + 8;
    } while (uVar4 < *(uint *)(lVar2 + 0x20));
  }
  hasUnitTheme(this,(CUnitTheme *)0x0);
  return;
}



/* address=007f6190
   symbol=CBaseUnit::removeEffect */

/* CBaseUnit::removeEffect(std::wstring const&) */

undefined8 __thiscall CBaseUnit::removeEffect(CBaseUnit *this,wstring_conflict *param_1)

{
  undefined8 uVar1;

  if (*(CEffectManager **)(this + 0x1b8) != (CEffectManager *)0x0) {
    uVar1 = CEffectManager::removeEffect(*(CEffectManager **)(this + 0x1b8),param_1,true);
    return uVar1;
  }
  return 0;
}



/* address=007f61c0
   symbol=CBaseUnit::hasEffect */

/* CBaseUnit::hasEffect(EEFFECT_TYPE, std::wstring const&) */

undefined8 CBaseUnit::hasEffect(long param_1)

{
  undefined8 uVar1;

  if (*(long *)(param_1 + 0x1b8) != 0) {
    uVar1 = CEffectManager::hasEffect();
    return uVar1;
  }
  return 0;
}



/* address=007f61e0
   symbol=CBaseUnit::hasEffect */

/* CBaseUnit::hasEffect(EEFFECT_TYPE) */

undefined8 CBaseUnit::hasEffect(long param_1)

{
  undefined8 uVar1;

  if (*(long *)(param_1 + 0x1b8) != 0) {
    uVar1 = CEffectManager::hasEffect();
    return uVar1;
  }
  return 0;
}



/* address=007f6200
   symbol=CBaseUnit::hasEffect */

/* CBaseUnit::hasEffect(std::wstring const&) */

undefined8 __thiscall CBaseUnit::hasEffect(CBaseUnit *this,wstring_conflict *param_1)

{
  undefined8 uVar1;

  if (*(CEffectManager **)(this + 0x1b8) != (CEffectManager *)0x0) {
    uVar1 = CEffectManager::hasEffect(*(CEffectManager **)(this + 0x1b8),param_1);
    return uVar1;
  }
  return 0;
}



/* address=007f6220
   symbol=CBaseUnit::getEffectValue */

/* CBaseUnit::getEffectValue(EEFFECT_TYPE, float, EDAMAGE_TYPES) */

void CBaseUnit::getEffectValue(long param_1)

{
  if (*(long *)(param_1 + 0x1b8) != 0) {
    CEffectManager::getEffectValue();
    return;
  }
  return;
}



/* address=007f6240
   symbol=CBaseUnit::getEffectValue */

/* CBaseUnit::getEffectValue(EEFFECT_TYPE, float, std::wstring const&) */

void CBaseUnit::getEffectValue(long param_1)

{
  if (*(long *)(param_1 + 0x1b8) != 0) {
    CEffectManager::getEffectValue();
    return;
  }
  return;
}



/* address=007f6260
   symbol=CBaseUnit::getEffectValue */

/* CBaseUnit::getEffectValue(EEFFECT_ACTIVATION, EEFFECT_TYPE, float, EDAMAGE_TYPES) */

void CBaseUnit::getEffectValue(long param_1)

{
  if (*(long *)(param_1 + 0x1b8) != 0) {
    CEffectManager::getEffectValue();
    return;
  }
  return;
}



/* address=007f6280
   symbol=CBaseUnit::removeAffix */

/* CBaseUnit::removeAffix(std::wstring const&) */

undefined8 __thiscall CBaseUnit::removeAffix(CBaseUnit *this,wstring_conflict *param_1)

{
  undefined8 uVar1;

  if (*(CEffectManager **)(this + 0x1b8) != (CEffectManager *)0x0) {
    uVar1 = CEffectManager::deleteAffix(*(CEffectManager **)(this + 0x1b8),param_1);
    return uVar1;
  }
  return 0;
}



/* address=007f62a0
   symbol=CBaseUnit::ISA */

/* CBaseUnit::ISA(UNITTYPES::EUNITTYPES) */

undefined8 __thiscall CBaseUnit::ISA(CBaseUnit *this,undefined4 param_2)

{
  undefined8 uVar1;

  if (*(CResourceManager **)(this + 0x68) != (CResourceManager *)0x0) {
    uVar1 = CResourceManager::ISA
                      (*(CResourceManager **)(this + 0x68),*(undefined4 *)(this + 0x1ac),param_2);
    return uVar1;
  }
  return 0;
}



/* address=007f62d0
   symbol=CBaseUnit::getIsQuestUnit */

/* CBaseUnit::getIsQuestUnit() */

bool __thiscall CBaseUnit::getIsQuestUnit(CBaseUnit *this)

{
  char cVar1;
  bool bVar2;

  cVar1 = ISA(this,0x67);
  bVar2 = true;
  if (cVar1 == '\0') {
    bVar2 = *(long *)(this + 0x170) != -1;
  }
  return bVar2;
}



/* address=007f6300
   symbol=CBaseUnit::addToAvoidanceMap */

/* CBaseUnit::addToAvoidanceMap(CLevel&) */

void CBaseUnit::addToAvoidanceMap(CLevel *param_1)

{
  long lVar1;
  char cVar2;
  CLevel *in_RSI;
  float fVar3;
  float fVar4;
  float fVar5;
  float in_XMM1_Da;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  void *local_78;
  float local_68;
  float local_64;
  float local_60;
  float local_58;
  float local_54;
  float local_50;
  float local_48;
  float local_44;
  float local_40;
  float local_38;
  float local_34;
  float local_30;
  undefined8 local_28;

  if ((((*(long *)(param_1 + 0x68) != 0) && (*(long *)(*(long *)(param_1 + 0x68) + 0x18) != 0)) &&
      (param_1[399] != (CLevel)0x0)) && (param_1[0x19b] == (CLevel)0x0)) {
    cVar2 = ISA((CBaseUnit *)param_1,0x1f);
    if (((cVar2 == '\0') && (param_1[0x18d] != (CLevel)0x0)) && (param_1[0x19c] != (CLevel)0x0)) {
      cVar2 = ISA((CBaseUnit *)param_1,0x20);
      if (cVar2 == '\0') {
        local_28 = CPositionableObject::getPosition((CPositionableObject *)param_1,true);
        fVar5 = (float)((ulong)local_28 >> 0x20);
        fVar3 = (float)local_28;
        fVar4 = DAT_00fa4830 + *(float *)(param_1 + 0x194);
        cVar2 = ISA((CBaseUnit *)param_1,0x1d);
        if (cVar2 == '\0') {
          local_60 = fVar4 + in_XMM1_Da;
          local_64 = fVar5 + DAT_00fa47f8;
          local_68 = fVar3 + fVar4;
          local_50 = in_XMM1_Da + (float)(DAT_00fa8780 ^ (uint)fVar4);
          local_58 = fVar3 + (float)(DAT_00fa8780 ^ (uint)fVar4);
          local_54 = local_64;
          CLevel::incrementObjectPassability(in_RSI,(Vector3 *)&local_58,(Vector3 *)&local_68,fVar4)
          ;
        }
        else {
          local_40 = fVar4 + in_XMM1_Da;
          local_44 = fVar5 + DAT_00fa47f8;
          local_48 = fVar3 + fVar4;
          local_30 = in_XMM1_Da + (float)(DAT_00fa8780 ^ (uint)fVar4);
          local_38 = fVar3 + (float)(DAT_00fa8780 ^ (uint)fVar4);
          local_34 = local_44;
          CLevel::incrementMapPassability(in_RSI,(Vector3 *)&local_38,(Vector3 *)&local_48,fVar4);
        }
      }
      else {
        lVar1 = *(long *)(param_1 + 0x1c0);
        local_78 = (void *)0x0;
        local_80 = 1;
        local_98 = *(undefined4 *)(lVar1 + 0x40);
        local_94 = *(undefined4 *)(lVar1 + 0x44);
        local_90 = *(undefined4 *)(lVar1 + 0x48);
        local_8c = *(undefined4 *)(lVar1 + 0x4c);
        local_88 = *(undefined4 *)(lVar1 + 0x50);
        local_84 = *(undefined4 *)(lVar1 + 0x54);
                    /* try { // try from 007f63c1 to 007f63c5 has its CatchHandler @ 007f6592 */
        CLevel::incrementMapPassabilityCollision
                  (in_RSI,(AxisAlignedBox *)&local_98,(CBaseUnit *)param_1);
        if (local_78 != (void *)0x0) {
          Ogre::NedAllocImpl::deallocBytes(local_78);
        }
      }
      param_1[0x19b] = (CLevel)0x1;
      return;
    }
  }
  return;
}



/* address=007f65b0
   symbol=CBaseUnit::removeFromAvoidanceMap */

/* CBaseUnit::removeFromAvoidanceMap(CLevel&) */

void CBaseUnit::removeFromAvoidanceMap(CLevel *param_1)

{
  long lVar1;
  char cVar2;
  CLevel *in_RSI;
  float fVar3;
  float fVar4;
  float fVar5;
  float in_XMM1_Da;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  void *local_78;
  float local_68;
  float local_64;
  float local_60;
  float local_58;
  float local_54;
  float local_50;
  float local_48;
  float local_44;
  float local_40;
  float local_38;
  float local_34;
  float local_30;
  undefined8 local_28;

  if (((*(long *)(param_1 + 0x68) != 0) && (*(long *)(*(long *)(param_1 + 0x68) + 0x18) != 0)) &&
     (param_1[0x19b] != (CLevel)0x0)) {
    cVar2 = ISA((CBaseUnit *)param_1,0x1f);
    if (cVar2 == '\0') {
      cVar2 = ISA((CBaseUnit *)param_1,0x20);
      if (cVar2 == '\0') {
        local_28 = CPositionableObject::getPosition((CPositionableObject *)param_1,true);
        fVar5 = (float)((ulong)local_28 >> 0x20);
        fVar3 = (float)local_28;
        fVar4 = DAT_00fa4830 + *(float *)(param_1 + 0x194);
        cVar2 = ISA((CBaseUnit *)param_1,0x1d);
        if (cVar2 == '\0') {
          local_60 = fVar4 + in_XMM1_Da;
          local_64 = fVar5 + DAT_00fa47f8;
          local_68 = fVar3 + fVar4;
          local_50 = in_XMM1_Da + (float)(DAT_00fa8780 ^ (uint)fVar4);
          local_58 = fVar3 + (float)(DAT_00fa8780 ^ (uint)fVar4);
          local_54 = local_64;
          CLevel::decrementObjectPassability(in_RSI,(Vector3 *)&local_58,(Vector3 *)&local_68,fVar4)
          ;
        }
        else {
          local_40 = fVar4 + in_XMM1_Da;
          local_44 = fVar5 + DAT_00fa47f8;
          local_48 = fVar3 + fVar4;
          local_30 = in_XMM1_Da + (float)(DAT_00fa8780 ^ (uint)fVar4);
          local_38 = fVar3 + (float)(DAT_00fa8780 ^ (uint)fVar4);
          local_34 = local_44;
          CLevel::decrementMapPassability(in_RSI,(Vector3 *)&local_38,(Vector3 *)&local_48,fVar4);
        }
      }
      else {
        lVar1 = *(long *)(param_1 + 0x1c0);
        local_78 = (void *)0x0;
        local_80 = 1;
        local_98 = *(undefined4 *)(lVar1 + 0x40);
        local_94 = *(undefined4 *)(lVar1 + 0x44);
        local_90 = *(undefined4 *)(lVar1 + 0x48);
        local_8c = *(undefined4 *)(lVar1 + 0x4c);
        local_88 = *(undefined4 *)(lVar1 + 0x50);
        local_84 = *(undefined4 *)(lVar1 + 0x54);
                    /* try { // try from 007f6657 to 007f665b has its CatchHandler @ 007f682a */
        CLevel::decrementMapPassabilityCollision
                  (in_RSI,(AxisAlignedBox *)&local_98,(CBaseUnit *)param_1);
        if (local_78 != (void *)0x0) {
          Ogre::NedAllocImpl::deallocBytes(local_78);
        }
      }
      param_1[0x19b] = (CLevel)0x0;
      return;
    }
  }
  return;
}



/* address=007f6850
   symbol=CBaseUnit::broadcastHPThreshholdEvents */

/* CBaseUnit::broadcastHPThreshholdEvents(float, float, float, float) */

void __thiscall
CBaseUnit::broadcastHPThreshholdEvents
          (CBaseUnit *this,float param_1,float param_2,float param_3,float param_4)

{
  char cVar1;
  float *pfVar2;
  int iVar3;
  long lVar4;
  float fVar5;

  if (this[0x1d0] != (CBaseUnit)0x0) {
    cVar1 = ISA(this,0x1c);
    if (((cVar1 == '\0') && (param_4 < DAT_00fa47f8)) && (param_4 + param_2 < param_3)) {
      pfVar2 = (float *)&DAT_00fc92e0;
      iVar3 = 8;
      fVar5 = (param_4 + param_2) / param_1;
      if (this[0x1d1] == (CBaseUnit)0x0) {
        do {
          if ((*pfVar2 < param_2 / param_1) && (fVar5 <= *pfVar2)) {
                    /* WARNING: Could not recover jumptable at 0x007f6968. Too many branches */
                    /* WARNING: Treating indirect jump as call */
            (**(code **)(*(long *)this + 0x30))
                      (this,(&broadcastHPThreshholdEvents(float,float,float,float)::eventsBroadCast)
                            [iVar3]);
            return;
          }
          iVar3 = iVar3 + -1;
          pfVar2 = pfVar2 + -1;
        } while (iVar3 != -1);
      }
      else {
        lVar4 = 0;
        do {
          if ((*(float *)((long)&broadcastHPThreshholdEvents(float,float,float,float)::eventsByPct +
                         lVar4) < param_2 / param_1) &&
             (fVar5 <= *(float *)((long)&broadcastHPThreshholdEvents(float,float,float,float)::
                                         eventsByPct + lVar4))) {
            (**(code **)(*(long *)this + 0x30))
                      (this,*(undefined4 *)
                             ((long)&broadcastHPThreshholdEvents(float,float,float,float)::
                                     eventsBroadCast + lVar4));
          }
          lVar4 = lVar4 + 4;
        } while (lVar4 != 0x24);
      }
    }
  }
  return;
}



/* address=007f6970
   symbol=CBaseUnit::broadcastAlerted */

/* CBaseUnit::broadcastAlerted() */

void __thiscall CBaseUnit::broadcastAlerted(CBaseUnit *this)

{
  char cVar1;

  if (this[0x1d0] != (CBaseUnit)0x0) {
    cVar1 = ISA(this,0x1c);
    if (cVar1 == '\0') {
                    /* WARNING: Could not recover jumptable at 0x007f699e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(*(long *)this + 0x30))(this,0x42);
      return;
    }
  }
  return;
}



/* address=007f69a0
   symbol=CBaseUnit::broadcastKilled */

/* CBaseUnit::broadcastKilled() */

void __thiscall CBaseUnit::broadcastKilled(CBaseUnit *this)

{
  char cVar1;

  cVar1 = ISA(this,0x1c);
  if (cVar1 != '\0') {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x007f69c8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)this + 0x30))(this,0x18);
  return;
}



/* address=007f69d0
   symbol=CBaseUnit::setCastsShadows */

/* CBaseUnit::setCastsShadows(bool) */

void __thiscall CBaseUnit::setCastsShadows(CBaseUnit *this,bool param_1)

{
  CBaseUnit CVar1;
  long lVar2;
  CGenericModel *this_00;

  this[0x1a9] = (CBaseUnit)param_1;
  lVar2 = (**(code **)(*(long *)this + 0x1e0))();
  if (lVar2 != 0) {
    CVar1 = this[0x1a9];
    this_00 = (CGenericModel *)(**(code **)(*(long *)this + 0x1e0))(this);
    CGenericModel::setCastsShadows(this_00,(bool)CVar1);
    return;
  }
  return;
}



/* address=007f6a40
   symbol=CBaseUnit::activateUnitInLevel */

/* CBaseUnit::activateUnitInLevel() */

void __thiscall CBaseUnit::activateUnitInLevel(CBaseUnit *this)

{
  this[0x199] = (CBaseUnit)0x1;
  this[0x19a] = (CBaseUnit)0x1;
  this[0x198] = (CBaseUnit)0x1;
  (**(code **)(*(long *)this + 0x1d0))(this,1);
  setCastsShadows(this,(bool)this[0x1a9]);
  return;
}



/* address=007f6a80
   symbol=CBaseUnit::broadcastUnitState */

/* CBaseUnit::broadcastUnitState(EUNIT_STATES) */

void __thiscall CBaseUnit::broadcastUnitState(CBaseUnit *this,undefined4 param_2)

{
  CLevel *pCVar1;

  if ((*(long *)(this + 0x68) != 0) &&
     (pCVar1 = *(CLevel **)(*(long *)(this + 0x68) + 0x18), pCVar1 != (CLevel *)0x0)) {
    CLevel::unitBroadcastMessage(pCVar1,this,param_2);
    return;
  }
  return;
}



/* address=007f6ab0
   symbol=CBaseUnit::questEventFire */

/* CBaseUnit::questEventFire(EQUEST_EVENTS, CCharacter*, CBaseUnit*) */

void CBaseUnit::questEventFire(long param_1)

{
  if ((*(long *)(param_1 + 0x68) != 0) && (*(long *)(*(long *)(param_1 + 0x68) + 0x18) != 0)) {
    CLevel::questEventFire();
    return;
  }
  return;
}



/* address=007f6ae0
   symbol=CBaseUnit::levelResetting */

/* CBaseUnit::levelResetting() */

void __thiscall CBaseUnit::levelResetting(CBaseUnit *this)

{
  if (*(CSkillManager **)(this + 0x1c8) != (CSkillManager *)0x0) {
    CSkillManager::stopAllSkills(*(CSkillManager **)(this + 0x1c8),true,false,false);
    return;
  }
  return;
}



/* address=007fea20
   symbol=CBaseUnit::_GLOBAL__I_CBaseUnit */

/* CBaseUnit::CBaseUnit(CResourceManager*, EBASEUNIT_TYPE) */

void CBaseUnit::_GLOBAL__I_CBaseUnit(void)

{
  allocator aStack_2f2;
  allocator aStack_2f1;
  allocator aStack_2f0;
  allocator aStack_2ef;
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
  std::string::string((string *)::KLayoutFunctionNames,"GUIEXITGAME",&aStack_2f2);
  std::string::string((string *)(::KLayoutFunctionNames + 8),"GUIEXITAPPLICATION",&aStack_2f1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x10),"GUINEWGAME",&aStack_2f0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x18),"GUICONTINUEGAME",&aStack_2ef);
  std::string::string((string *)(::KLayoutFunctionNames + 0x20),"GUINEWGAMEMENU",&aStack_2ee);
  std::string::string((string *)(::KLayoutFunctionNames + 0x28),"GUICONTINUEGAMEMENU",&aStack_2ed);
  std::string::string((string *)(::KLayoutFunctionNames + 0x30),"GUICLOSEMENU",&aStack_2ec);
  std::string::string((string *)(::KLayoutFunctionNames + 0x38),"GUIBACK",&aStack_2eb);
  std::string::string((string *)(::KLayoutFunctionNames + 0x40),"GUIDECLINE",&aStack_2ea);
  std::string::string((string *)(::KLayoutFunctionNames + 0x48),"GUIACCEPT",&aStack_2e9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x50),"GUIOK",&aStack_2e8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x58),"GUIPAUSE",&aStack_2e7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x60),"GUISCROLLUP",&aStack_2e6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x68),"GUISCROLLDOWN",&aStack_2e5);
  std::string::string((string *)(::KLayoutFunctionNames + 0x70),"GUISELECT1",&aStack_2e4);
  std::string::string((string *)(::KLayoutFunctionNames + 0x78),"GUISELECT2",&aStack_2e3);
  std::string::string((string *)(::KLayoutFunctionNames + 0x80),"GUISELECT3",&aStack_2e2);
  std::string::string((string *)(::KLayoutFunctionNames + 0x88),"GUISELECT4",&aStack_2e1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x90),"GUISELECT5",&aStack_2e0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x98),"GUISELECT6",&aStack_2df);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa0),"GUISELECT7",&aStack_2de);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa8),"GUISELECT8",&aStack_2dd);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb0),"GUISELECT9",&aStack_2dc);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb8),"GUISELECT10",&aStack_2db);
  std::string::string((string *)(::KLayoutFunctionNames + 0xc0),"GUISELECT11",&aStack_2da);
  std::string::string((string *)(::KLayoutFunctionNames + 200),"GUISELECT12",&aStack_2d9);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd0),"GUISELECT13",&aStack_2d8);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd8),"GUISELECT14",&aStack_2d7);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe0),"GUISELECT15",&aStack_2d6);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe8),"GUISELECT16",&aStack_2d5);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf0),"GUISELECT17",&aStack_2d4);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf8),"GUISELECT18",&aStack_2d3);
  std::string::string((string *)(::KLayoutFunctionNames + 0x100),"GUISELECT19",&aStack_2d2);
  std::string::string((string *)(::KLayoutFunctionNames + 0x108),"GUISELECT20",&aStack_2d1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x110),"GUISELECT21",&aStack_2d0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x118),"GUISELECT22",&aStack_2cf);
  std::string::string((string *)(::KLayoutFunctionNames + 0x120),"GUISELECT23",&aStack_2ce);
  std::string::string((string *)(::KLayoutFunctionNames + 0x128),"GUISELECT24",&aStack_2cd);
  std::string::string((string *)(::KLayoutFunctionNames + 0x130),"GUISELECT25",&aStack_2cc);
  std::string::string((string *)(::KLayoutFunctionNames + 0x138),"GUISELECT26",&aStack_2cb);
  std::string::string((string *)(::KLayoutFunctionNames + 0x140),"GUISELECT27",&aStack_2ca);
  std::string::string((string *)(::KLayoutFunctionNames + 0x148),"GUISELECT28",&aStack_2c9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x150),"GUISELECT29",&aStack_2c8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x158),"GUISELECT30",&aStack_2c7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x160),"GUISELECT31",&aStack_2c6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x168),"GUISELECT32",&aStack_2c5);
  std::string::string((string *)(::KLayoutFunctionNames + 0x170),"GUISELECT33",&aStack_2c4);
  std::string::string((string *)(::KLayoutFunctionNames + 0x178),"GUISELECT34",&aStack_2c3);
  std::string::string((string *)(::KLayoutFunctionNames + 0x180),"GUISELECT35",&aStack_2c2);
  std::string::string((string *)(::KLayoutFunctionNames + 0x188),"GUISELECT36",&aStack_2c1);
  std::string::string((string *)(::KLayoutFunctionNames + 400),"GUISELECT37",&aStack_2c0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x198),"GUISELECT38",&aStack_2bf);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a0),"GUISELECT39",&aStack_2be);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a8),"GUISELECT40",&aStack_2bd);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b0),"GUISELECT41",&aStack_2bc);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b8),"GUISELECT42",&aStack_2bb);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c0),"GUISELECT43",&aStack_2ba);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c8),"GUISELECT44",&aStack_2b9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d0),"GUISELECT45",&aStack_2b8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d8),"GUISELECT46",&aStack_2b7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e0),"GUISELECT47",&aStack_2b6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e8),"GUISELECT48",&aStack_2b5);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f0),"GUISELECT49",&aStack_2b4);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f8),"GUISELECT50",&aStack_2b3);
  std::string::string((string *)(::KLayoutFunctionNames + 0x200),"GUISELECTA",&aStack_2b2);
  std::string::string((string *)(::KLayoutFunctionNames + 0x208),"GUISELECTB",&aStack_2b1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x210),"GUISELECTC",&aStack_2b0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x218),"GUISELECTD",&aStack_2af);
  std::string::string((string *)(::KLayoutFunctionNames + 0x220),"GUIFEEDPET",&aStack_2ae);
  std::string::string((string *)(::KLayoutFunctionNames + 0x228),"GUIPETPASSIVE",&aStack_2ad);
  std::string::string((string *)(::KLayoutFunctionNames + 0x230),"GUIPETAGGRESSIVE",&aStack_2ac);
  std::string::string((string *)(::KLayoutFunctionNames + 0x238),"GUIPETDEFENSIVE",&aStack_2ab);
  std::string::string((string *)(::KLayoutFunctionNames + 0x240),"GUITOGGLEINVENTORY",&aStack_2aa);
  std::string::string((string *)(::KLayoutFunctionNames + 0x248),"GUITOGGLEQUESTS",&aStack_2a9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x250),"GUITOGGLESTATS",&aStack_2a8);
  std::string::string((string *)(::KLayoutFunctionNames + 600),"GUITOGGLESKILLS",&aStack_2a7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x260),"GUITOGGLEPERKS",&aStack_2a6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x268),"GUITOGGLEJOURNAL",&aStack_2a5);
  std::string::string((string *)(::KLayoutFunctionNames + 0x270),"GUITOGGLEPET",&aStack_2a4);
  std::string::string((string *)(::KLayoutFunctionNames + 0x278),"GUITOGGLEAUTOMAP",&aStack_2a3);
  std::string::string((string *)(::KLayoutFunctionNames + 0x280),"GUITOGGLEOPTIONS",&aStack_2a2);
  std::string::string((string *)(::KLayoutFunctionNames + 0x288),"GUITOGGLEITEMNAMES",&aStack_2a1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x290),"GUIAUTOMAPZOOMIN",&aStack_2a0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x298),"GUIAUTOMAPZOOMOUT",&aStack_29f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a0),"GUILEVELUP",&aStack_29e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a8),"GUISTATSUP",&aStack_29d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b0),"GUISKILLUP",&aStack_29c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b8),"GUIPET1",&aStack_29b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c0),"GUIPET2",&aStack_29a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c8),"GUIPET3",&aStack_299);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d0),"GUIDELETE1",&aStack_298);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d8),"GUIDELETE2",&aStack_297);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e0),"GUIDELETE3",&aStack_296);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e8),"GUIDELETE4",&aStack_295);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f0),"GUISETTINGSMENU",&aStack_294);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f8),"GUIPETSELL",&aStack_293);
  std::string::string((string *)(::KLayoutFunctionNames + 0x300),"NONE",&aStack_292);
  __cxa_atexit(::__tcf_0,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSOUNDBANK_STRINGS,L"STEP_SOUND",&aStack_291);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 8),L"STRIKE_SOUND",&aStack_290);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x10),L"PHYSICALHIT_SOUND",&aStack_28f);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x18),L"ICEHIT_SOUND",&aStack_28e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x20),L"FIREHIT_SOUND",&aStack_28d);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x28),L"ELECTRICHIT_SOUND",&aStack_28c);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x30),L"POISONHIT_SOUND",&aStack_28b);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x38),L"SHIELDBLOCK",&aStack_28a);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x40),L"BLOCK",&aStack_289);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x48),L"CRITICAL_SOUND",&aStack_288);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x50),L"ATTACK_SOUND",&aStack_287);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x58),L"IDLE_SOUND",&aStack_286)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x60),L"DEATH_SOUND",&aStack_285);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x68),L"ROAR_SOUND",&aStack_284)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x70),L"FLEE_SOUND",&aStack_283)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x78),L"MISS_SOUND",&aStack_282)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x80),L"FALL_SOUND",&aStack_281)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x88),L"LAND_SOUND",&aStack_280)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x90),L"TAKE_SOUND",&aStack_27f)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x98),L"SPAWN_SOUND",&aStack_27e);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa0),L"USE_SOUND",&aStack_27d);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa8),L"EQUIP_SOUND",&aStack_27c);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb0),L"OPENMENU_SOUND",&aStack_27b);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb8),L"BUY_SOUND",&aStack_27a);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xc0),L"ERROR_SOUND",&aStack_279);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 200),L"LEVELUP_SOUND",&aStack_278);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd0),L"EFFORT_SOUND",&aStack_277);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd8),L"SPENDPOINT_SOUND",&aStack_276);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe0),L"PORTALENTER_SOUND",&aStack_275);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe8),L"POERTALEXIT_SOUND",&aStack_274);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf0),L"SKILLASSIGN_SOUND",&aStack_273);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf8),L"QUESTRECEIVED_SOUND",&aStack_272);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x100),L"QUESTCOMPLETED_SOUND",&aStack_271)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x108),L"LOWMANA_SOUND",&aStack_270);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x110),L"MISSILEREFLECT_SOUND",&aStack_26f)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x118),L"BADEFFECT_SOUND",&aStack_26e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x120),L"GOODEFFECT_SOUND",&aStack_26d);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x128),L"NPCDIALOG_SOUND",&aStack_26c);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x130),L"NPCGREET",&aStack_26b);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x138),L"NPCBYE",&aStack_26a);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x140),L"NPCPURCHASE",&aStack_269);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x148),L"NPCSELL",&aStack_268);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x150),L"VOICEPETINVENTORYFULL_SOUND",
             &aStack_267);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x158),L"VOICEPETDEPARTED_SOUND",
             &aStack_266);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x160),L"VOICEPETRETURNED_SOUND",
             &aStack_265);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x168),L"VOICEPETFLED_SOUND",&aStack_264);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x170),L"VOICEPETLEVELUP_SOUND",&aStack_263
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x178),L"VOICEINVENTORYFULL_SOUND",
             &aStack_262);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x180),L"VOICEINSUFFICIENTGOLD_SOUND",
             &aStack_261);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x188),L"VOICEIMPOSSIBLE_SOUND",&aStack_260
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 400),L"VOICECANTCAST_SOUND",&aStack_25f);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x198),L"VOICECANTCASTHERE_SOUND",
             &aStack_25e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a0),L"VOICEHEALTHLOW_SOUND",&aStack_25d)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a8),L"VOICEMANALOW_SOUND",&aStack_25c);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b0),L"VOICETRAPSPRUNG_SOUND",&aStack_25b
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b8),L"VOICEREFRESHED_SOUND",&aStack_25a)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c0),L"VOICEPOWERFUL_SOUND",&aStack_259);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c8),L"VOICEHEALTHY_SOUND",&aStack_258);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d0),L"VOICEILL_SOUND",&aStack_257);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d8),L"VOICEPOISONED_SOUND",&aStack_256);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e0),L"VOICELEVELUP_SOUND",&aStack_255);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e8),L"VOICEFAMEUP_SOUND",&aStack_254);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f0),L"VOICESKILLUP_SOUND",&aStack_253);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f8),L"VOICEFORTUNEGOOD_SOUND",
             &aStack_252);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x200),L"VOICEFORTUNEBAD_SOUND",&aStack_251
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x208),L"VOICESPELLLEARNED_SOUND",
             &aStack_250);
  ::KSOUNDBANK_STRINGS._528_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_1,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KALIGNMENT_STRINGS,L"NEUTRAL",&aStack_24f);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 8),L"GOOD",&aStack_24e);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x10),L"EVIL",&aStack_24d);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x18),L"ALL",&aStack_24c);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x20),L"BERSERK",&aStack_24b);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x28),L"EVILBERSERK",&aStack_24a);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x30),L"GOODBERSERK",&aStack_249);
  __cxa_atexit(::__tcf_2,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KAITYPE_STRINGS,L"NORMAL",&aStack_248);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 8),L"RANGEDDEFENDER",&aStack_247);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x10),L"DEFENDER",&aStack_246);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x18),L"RANGEDCASTER",&aStack_245);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x20),L"CIRCLER",&aStack_244);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x28),L"RESURRECTER",&aStack_243);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x30),L"DUMMY",&aStack_242);
  __cxa_atexit(::__tcf_3,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gDAMAGE_TYPES,L"Physical",&aStack_241);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 8),L"Magical",&aStack_240);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x10),L"Fire",&aStack_23f);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x18),L"Ice",&aStack_23e);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x20),L"Electric",&aStack_23d);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x28),L"Poison",&aStack_23c);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x30),L"All",&aStack_23b);
  __cxa_atexit(::__tcf_4,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::gTARGET_TYPES,L"USER",&aStack_23a);
  std::wstring::wstring((wstring_conflict *)&DAT_01479a88,L"ITEM",&aStack_239);
  __cxa_atexit(::__tcf_5,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSFXTypeName,L"STATIONARYTARGET",&aStack_238);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 8),L"STATIONARYOWNER",&aStack_237);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x10),L"STATIONARY",&aStack_236);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x18),L"STATIONARYPORTAL",&aStack_235)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x20),L"BEAM",&aStack_234);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x28),L"FOLLOWOWNER",&aStack_233);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x30),L"FOLLOWTARGET",&aStack_232);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x38),L"PROJECTILELOCATION",&aStack_231);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x40),L"PROJECTILECHARACTER",&aStack_230);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x48),L"PROJECTILELOCATIONERRATIC",&aStack_22f);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x50),L"PROJECTILECHARACTERERRATIC",&aStack_22e);
  __cxa_atexit(::__tcf_6,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KCharacterNames,L"NA",&aStack_22d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 8),L"NA",&aStack_22c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x10),L"NA",&aStack_22b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x18),L"NA",&aStack_22a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x20),L"NA",&aStack_229);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x28),L"NA",&aStack_228);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x30),L"NA",&aStack_227);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x38),L"NA",&aStack_226);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x40),L"Bksp",&aStack_225);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x48),L"Tab",&aStack_224);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x50),L"NA",&aStack_223);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x58),L"NA",&aStack_222);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x60),L"Ctr",&aStack_221);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x68),L"Ret",&aStack_220);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x70),L"NA",&aStack_21f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x78),L"NA",&aStack_21e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x80),L"Shift",&aStack_21d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x88),L"Ctrl",&aStack_21c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x90),L"Alt",&aStack_21b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x98),L"Tab",&aStack_21a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa0),L"NA",&aStack_219);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa8),L"NA",&aStack_218);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb0),L"NA",&aStack_217);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb8),L"NA",&aStack_216);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xc0),L"NA",&aStack_215);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 200),L"NA",&aStack_214);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd0),L"NA",&aStack_213);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd8),L"NA",&aStack_212);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe0),L"NA",&aStack_211);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe8),L"NA",&aStack_210);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf0),L"NA",&aStack_20f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf8),L"NA",&aStack_20e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x100),L"space",&aStack_20d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x108),L"pgup",&aStack_20c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x110),L"pgdn",&aStack_20b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x118),L"end",&aStack_20a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x120),L"home",&aStack_209);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x128),L"left arrow",&aStack_208);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x130),L"up arrow",&aStack_207);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x138),L"right arrow",&aStack_206);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x140),L"down arrow",&aStack_205);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x148),L")",&aStack_204);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x150),L"*",&aStack_203);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x158),L"+",&aStack_202);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x160),L",",&aStack_201);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x168),L"ins",&aStack_200);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x170),L"del",&aStack_1ff);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x178),L"/",&aStack_1fe);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x180),L"0",&aStack_1fd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x188),L"1",&aStack_1fc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 400),L"2",&aStack_1fb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x198),L"3",&aStack_1fa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a0),L"4",&aStack_1f9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a8),L"5",&aStack_1f8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b0),L"6",&aStack_1f7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b8),L"7",&aStack_1f6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c0),L"8",&aStack_1f5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c8),L"9",&aStack_1f4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d0),L":",&aStack_1f3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d8),L";",&aStack_1f2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e0),L"<",&aStack_1f1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e8),L"=",&aStack_1f0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f0),L">",&aStack_1ef);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f8),L"?",&aStack_1ee);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x200),L"@",&aStack_1ed);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x208),L"a",&aStack_1ec);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x210),L"b",&aStack_1eb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x218),L"c",&aStack_1ea);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x220),L"d",&aStack_1e9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x228),L"e",&aStack_1e8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x230),L"NA",&aStack_1e7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x238),L"g",&aStack_1e6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x240),L"h",&aStack_1e5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x248),L"i",&aStack_1e4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x250),L"j",&aStack_1e3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 600),L"k",&aStack_1e2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x260),L"l",&aStack_1e1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x268),L"m",&aStack_1e0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x270),L"n",&aStack_1df);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x278),L"o",&aStack_1de);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x280),L"p",&aStack_1dd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x288),L"NA",&aStack_1dc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x290),L"r",&aStack_1db);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x298),L"s",&aStack_1da);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a0),L"t",&aStack_1d9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a8),L"u",&aStack_1d8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b0),L"v",&aStack_1d7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b8),L"w",&aStack_1d6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c0),L"x",&aStack_1d5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c8),L"y",&aStack_1d4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d0),L"z",&aStack_1d3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d8),L"[",&aStack_1d2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e0),L"\\",&aStack_1d1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e8),L"]",&aStack_1d0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f0),L"^",&aStack_1cf);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f8),L"_",&aStack_1ce);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x300),L"NUM 0",&aStack_1cd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x308),L"NUM 1",&aStack_1cc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x310),L"NUM 2",&aStack_1cb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x318),L"NUM 3",&aStack_1ca);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 800),L"NUM 4",&aStack_1c9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x328),L"NUM 5",&aStack_1c8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x330),L"NUM 6",&aStack_1c7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x338),L"NUM 7",&aStack_1c6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x340),L"NUM 8",&aStack_1c5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x348),L"NUM 9",&aStack_1c4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x350),L"*",&aStack_1c3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x358),L"+",&aStack_1c2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x360),L"NA",&aStack_1c1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x368),L"-",&aStack_1c0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x370),L"NA",&aStack_1bf);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x378),L"F1",&aStack_1be);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x380),L"F2",&aStack_1bd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x388),L"F3",&aStack_1bc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x390),L"F4",&aStack_1bb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x398),L"F5",&aStack_1ba);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a0),L"F6",&aStack_1b9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a8),L"F7",&aStack_1b8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b0),L"F8",&aStack_1b7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b8),L"F9",&aStack_1b6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c0),L"F10",&aStack_1b5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c8),L"F11",&aStack_1b4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d0),L"F12",&aStack_1b3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d8),L"{",&aStack_1b2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3e0),L"|",&aStack_1b1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 1000),L"}",&aStack_1b0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f0),L"~",&aStack_1af);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f8),L";",&aStack_1ae);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x400),L"=",&aStack_1ad);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x408),L".",&aStack_1ac);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x410),L"-",&aStack_1ab);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x418),L",",&aStack_1aa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x420),L"/",&aStack_1a9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x428),L"`",&aStack_1a8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x430),L"[",&aStack_1a7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x438),L"\\",&aStack_1a6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x440),L"]",&aStack_1a5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x448),L"\'",&aStack_1a4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x450),L"NA",&aStack_1a3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x458),L"NA",&aStack_1a2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x460),L"NA",&aStack_1a1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x468),L"NA",&aStack_1a0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x470),L"NA",&aStack_19f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x478),L"NA",&aStack_19e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x480),L"NA",&aStack_19d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x488),L"NA",&aStack_19c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x490),L"NA",&aStack_19b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x498),L"NA",&aStack_19a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a0),L"NA",&aStack_199);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a8),L"NA",&aStack_198);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b0),L"NA",&aStack_197);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b8),L"NA",&aStack_196);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c0),L"NA",&aStack_195);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c8),L"NA",&aStack_194);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d0),L"NA",&aStack_193);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d8),L"NA",&aStack_192);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e0),L"NA",&aStack_191);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e8),L"NA",&aStack_190);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f0),L"NA",&aStack_18f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f8),L"NA",&aStack_18e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x500),L"NA",&aStack_18d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x508),L"NA",&aStack_18c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x510),L"NA",&aStack_18b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x518),L"NA",&aStack_18a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x520),L"NA",&aStack_189);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x528),L"NA",&aStack_188);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x530),L"NA",&aStack_187);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x538),L"NA",&aStack_186);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x540),L"NA",&aStack_185);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x548),L"NA",&aStack_184);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x550),L"NA",&aStack_183);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x558),L"NA",&aStack_182);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x560),L"NA",&aStack_181);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x568),L"NA",&aStack_180);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x570),L"NA",&aStack_17f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x578),L"NA",&aStack_17e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x580),L"NA",&aStack_17d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x588),L"NA",&aStack_17c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x590),L"NA",&aStack_17b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x598),L"NA",&aStack_17a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a0),L"NA",&aStack_179);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a8),L"NA",&aStack_178);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b0),L"NA",&aStack_177);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b8),L"NA",&aStack_176);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c0),L"NA",&aStack_175);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c8),L"NA",&aStack_174);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d0),L";",&aStack_173);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d8),L"=",&aStack_172);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e0),L",",&aStack_171);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e8),L"-",&aStack_170);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f0),L".",&aStack_16f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f8),L"/",&aStack_16e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x600),L"`",&aStack_16d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x608),L"NA",&aStack_16c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x610),L"NA",&aStack_16b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x618),L"NA",&aStack_16a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x620),L"NA",&aStack_169);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x628),L"NA",&aStack_168);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x630),L"NA",&aStack_167);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x638),L"NA",&aStack_166);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x640),L"NA",&aStack_165);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x648),L"NA",&aStack_164);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x650),L"NA",&aStack_163);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x658),L"NA",&aStack_162);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x660),L"NA",&aStack_161);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x668),L"NA",&aStack_160);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x670),L"NA",&aStack_15f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x678),L"NA",&aStack_15e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x680),L"NA",&aStack_15d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x688),L"NA",&aStack_15c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x690),L"NA",&aStack_15b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x698),L"NA",&aStack_15a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a0),L"NA",&aStack_159);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a8),L"NA",&aStack_158);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b0),L"NA",&aStack_157);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b8),L"NA",&aStack_156);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c0),L"NA",&aStack_155);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c8),L"NA",&aStack_154);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d0),L"NA",&aStack_153);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d8),L"[",&aStack_152);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e0),L"\\",&aStack_151);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e8),L"]",&aStack_150);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f0),L"\'",&aStack_14f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f8),L"NA",&aStack_14e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x700),L"NA",&aStack_14d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x708),L"NA",&aStack_14c);
  __cxa_atexit(::__tcf_7,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEffect_Activation_Names,L"PASSIVE",&aStack_14b);
  std::wstring::wstring((wstring_conflict *)(::gEffect_Activation_Names + 8),L"DYNAMIC",&aStack_14a)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gEffect_Activation_Names + 0x10),L"TRANSFER",&aStack_149);
  __cxa_atexit(::__tcf_8,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEFFECT_STAT_MODIFIER_NAMES,L"MELEE",&aStack_148);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 8),L"RANGED",&aStack_147);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x10),L"DEFENSE",&aStack_146);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x18),L"MAGIC",&aStack_145);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x20),L"LEVEL",&aStack_144);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x28),L"OWNERLEVEL",&aStack_143);
  __cxa_atexit(::__tcf_9,0,&__dso_handle);
  std::string::string((string *)::gEFFECT_STAT_MODIFIER_ICON_NAMES,"iconmelee",&aStack_142);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 8),"iconranged",&aStack_141);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x10),"icondefense",
                      &aStack_140);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x18),"iconmagic",&aStack_13f)
  ;
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x20),"iconmagic",&aStack_13e)
  ;
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x28),"iconmagic",&aStack_13d)
  ;
  __cxa_atexit(::__tcf_10,0,&__dso_handle);
  ParticleUniverse::HALFSCALE._4_4_ = DAT_0142463c * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._0_4_ = Ogre::Vector3::UNIT_SCALE * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._8_4_ = DAT_00fa4810 * DAT_01424640;
  std::string::string((string *)&ParticleUniverse::ALIAS,"1",&aStack_13c);
  __cxa_atexit(std::string::~string,&ParticleUniverse::ALIAS,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::SYSTEM,"2",&aStack_13b);
  __cxa_atexit(std::string::~string,&ParticleUniverse::SYSTEM,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::TECHNIQUE,"3",&aStack_13a);
  __cxa_atexit(std::string::~string,&ParticleUniverse::TECHNIQUE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::RENDERER,"4",&aStack_139);
  __cxa_atexit(std::string::~string,&ParticleUniverse::RENDERER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EMITTER,"5",&aStack_138);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EMITTER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::AFFECTOR,"6",&aStack_137);
  __cxa_atexit(std::string::~string,&ParticleUniverse::AFFECTOR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::OBSERVER,"7",&aStack_136);
  __cxa_atexit(std::string::~string,&ParticleUniverse::OBSERVER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::HANDLER,"8",&aStack_135);
  __cxa_atexit(std::string::~string,&ParticleUniverse::HANDLER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::BEHAVIOUR,"9",&aStack_134);
  __cxa_atexit(std::string::~string,&ParticleUniverse::BEHAVIOUR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EXTERN,"10",&aStack_133);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EXTERN,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DYNAMIC_ATTRIBUTE,"11",&aStack_132);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DYNAMIC_ATTRIBUTE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DEPENDENCY,"12",&aStack_131);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DEPENDENCY,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_TYPE_NAMES,L"",&aStack_130);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 8),L"FIND",&aStack_12f);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x10),L"KILL NUM",&aStack_12e);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x18),L"KILL BOSS",&aStack_12d);
  __cxa_atexit(::__tcf_11,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_DIALOG_TYPE_NAMES,L"ERROR",&aStack_12c);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 8),L"INTRO",&aStack_12b);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x10),L"RETURN",&aStack_12a);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x18),L"COMPLETE",&aStack_129);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x20),L"PASSIVE",&aStack_128);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x28),L"DETAILS",&aStack_127);
  __cxa_atexit(::__tcf_12,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)OGRE_UTILITIES::gPRIMITIVE_NAMES,L"SPHERE",&aStack_126);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 8),L"BOX",&aStack_125);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x10),L"PLANE",&aStack_124);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x18),L"CYLINDER",&aStack_123);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x20),L"CONE",&aStack_122);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x28),L"ARROW",&aStack_121);
  __cxa_atexit(::__tcf_13,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gKEYFRAME_TYPES,L"HIT",&aStack_120);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 8),L"BLENDIN",&aStack_11f);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x10),L"BLENDOUT",&aStack_11e);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x18),L"PLAYSOUND",&aStack_11d);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x20),L"SPAWNPARTICLE",&aStack_11c)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x28),L"SPAWNPARTICLE_STOP_ON_DEATH",
             &aStack_11b);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x30),L"FOOTSTEP",&aStack_11a);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x38),L"SHOWWEAPONTRAIL",&aStack_119);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x40),L"HIDEWEAPONTRAIL",&aStack_118);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x48),L"ATTACKSOUND",&aStack_117);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x50),L"ENABLECOLLISION",&aStack_116);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x58),L"DISABLECOLLISION",&aStack_115);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x60),L"REMOVEPARTICLES",&aStack_114);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x68),L"REMOVEANIMATIONPARTICLES",&aStack_113)
  ;
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x70),L"CAMERASHAKE",&aStack_112);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x78),L"ATTACKEND",&aStack_111);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x80),L"UNTARGETABLE",&aStack_110);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x88),L"TARGETABLE",&aStack_10f);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x90),L"DAMPVELOCITY",&aStack_10e);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x98),L"UNDAMPVELOCITY",&aStack_10d);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xa0),L"SHOWWEAPONS",&aStack_10c);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xa8),L"HIDEWEAPONS",&aStack_10b);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xb0),L"HIDEMESH",&aStack_10a);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xb8),L"SHOWMESH",&aStack_109);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xc0),L"FADEOUTMESH",&aStack_108);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 200),L"FADEINMESH",&aStack_107);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0xd0),L"CAMERASHAKE_NO_FALLOFF",&aStack_106);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0xd8),L"PLAYSOUND_NO_FALLOFF",&aStack_105);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xe0),L"HITTWO",&aStack_104);
  __cxa_atexit(::__tcf_14,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_EVENT_TYPE_NAMES,L"EVENT_START",&aStack_103);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 8),L"EVENT_END",&aStack_102);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x10),L"EVENT_TRIGGER",&aStack_101);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x18),L"EVENT_TRIGGER_TWO",&aStack_100
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x20),L"EVENT_UNITHIT",&aStack_ff);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x28),L"EVENT_UNITDIE",&aStack_fe);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x30),L"EVENT_MISSILEHIT",&aStack_fd);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x38),L"EVENT_MISSILEDIE",&aStack_fc);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x40),L"EVENT_DIEBYEFFECT",&aStack_fb)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x48),L"EVENT_CASTERDIE",&aStack_fa);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x50),L"EVENT_UNIT_CREATE",&aStack_f9)
  ;
  __cxa_atexit(::__tcf_15,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_TARGET_TYPE_NAMES,L"NONE",&aStack_f8);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 8),L"POSITION",&aStack_f7)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x10),L"TARGET",&aStack_f6);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x18),L"SELF",&aStack_f5);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x20),L"EVERYBODY",&aStack_f4);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x28),L"POSITIONRANDOM",&aStack_f3);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x30),L"POSITIONFLEE",&aStack_f2);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x38),L"ITEM",&aStack_f1);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x40),L"UNIDENTIFIEDITEM",&aStack_f0)
  ;
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x48),L"PETS",&aStack_ef);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x50),L"SELFANDPETS",&aStack_ee);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x58),L"TARGET_POS",&aStack_ed);
  __cxa_atexit(::__tcf_16,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_ACTIVATION_TYPE_NAMES,L"ANY",&aStack_ec);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 8),L"PROC",&aStack_eb)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 0x10),L"WEAPON",&aStack_ea);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 0x18),L"NORMAL",&aStack_e9);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 0x20),L"PASSIVE",&aStack_e8);
  __cxa_atexit(::__tcf_17,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_TYPE_NAMES,L"SKILL",&aStack_e7);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TYPE_NAMES + 8),L"OFFENSIVE",&aStack_e6);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TYPE_NAMES + 0x10),L"DEFENSIVE",&aStack_e5);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TYPE_NAMES + 0x18),L"CHARM",&aStack_e4);
  ::gSKILL_TYPE_NAMES._32_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_18,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_TYPE_DISPLAY_NAMES,L"Class Skill",&aStack_e3);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TYPE_DISPLAY_NAMES + 8),L"Offensive Spell",&aStack_e2);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TYPE_DISPLAY_NAMES + 0x10),L"Defensive Spell",&aStack_e1)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TYPE_DISPLAY_NAMES + 0x18),L"Charm Spell",&aStack_e0);
  ::gSKILL_TYPE_DISPLAY_NAMES._32_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_19,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_BONE_ATTACHMENT_NAMES,L"",&aStack_df);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 8),L"CENTER",&aStack_de);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x10),L"HEAD",&aStack_dd);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x18),L"RIGHTHAND",&aStack_dc);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x20),L"LEFTHAND",&aStack_db);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x28),L"RIGHTSHOULDER",&aStack_da
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x30),L"LEFTSHOULDER",&aStack_d9)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x38),L"POSITION",&aStack_d8);
  __cxa_atexit(::__tcf_20,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gOUTPUT_EVENTS_NAMES,L"Triggered",&aStack_d7);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 8),L"Triggered First Time",&aStack_d6);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x10),L"Deactivated",&aStack_d5);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x18),L"Deactivated First Time",
             &aStack_d4);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x20),L"On Visible",&aStack_d3);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x28),L"On Invisible",&aStack_d2);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x30),L"Enabled",&aStack_d1);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x38),L"Disabled",&aStack_d0);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x40),L"Activated",&aStack_cf)
  ;
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x48),L"Reset",&aStack_ce);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x50),L"Initialized",&aStack_cd);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x58),L"Playing",&aStack_cc);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x60),L"Stopped",&aStack_cb);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x68),L"Sound Ended",&aStack_ca);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x70),L"Paused",&aStack_c9);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x78),L"Resumed",&aStack_c8);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x80),L"Incremented",&aStack_c7);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x88),L"First Increment",&aStack_c6);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x90),L"Second Increment",&aStack_c5);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x98),L"Third Increment",&aStack_c4);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xa0),L"Fourth Increment",&aStack_c3);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xa8),L"Fifth Increment",&aStack_c2);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xb0),L"Increment Greater Then Five",
             &aStack_c1);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xb8),L"Monsters Spawned",&aStack_c0);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xc0),L"Monster Killed",&aStack_bf);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 200),L"All Monsters Dead",&aStack_be);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xd0),L"All Units Spawned",&aStack_bd);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xd8),L"Item Picked Up",&aStack_bc);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xe0),L"All Items Picked Up",&aStack_bb);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xe8),L"Item Interacted",&aStack_ba);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xf0),L"All Items Interacted With",
             &aStack_b9);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xf8),L"Particle Started",&aStack_b8);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x100),L"Particle Stopped",&aStack_b7);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x108),L"Particle Paused",&aStack_b6);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x110),L"Particle Resumed",&aStack_b5);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x118),L"Stopped",&aStack_b4);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x120),L"Started",&aStack_b3);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x128),L"Paused",&aStack_b2);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x130),L"Reset to Beginning",&aStack_b1);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x138),L"Reset to End",&aStack_b0);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x140),L"Looped",&aStack_af);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x148),L"Started Backwards",&aStack_ae);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x150),L"Started Forwards",&aStack_ad);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x158),L"Stopped Backwards",&aStack_ac);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x160),L"Stopped Forwards",&aStack_ab);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x168),L"Finished",&aStack_aa)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x170),L"State One",&aStack_a9);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x178),L"State Two",&aStack_a8);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x180),L"Activation Failed",&aStack_a7);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x188),L"One",&aStack_a6);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 400),L"Two",&aStack_a5);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x198),L"Three",&aStack_a4);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1a0),L"Four",&aStack_a3);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1a8),L"Five",&aStack_a2);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1b0),L"FAILED",&aStack_a1);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1b8),L"SUCCESS",&aStack_a0);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1c0),L"Interacted with Unit",&aStack_9f
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1c8),L"HP 90 PCT",&aStack_9e);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1d0),L"HP 80 PCT",&aStack_9d);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1d8),L"HP 70 PCT",&aStack_9c);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1e0),L"HP 60 PCT",&aStack_9b);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1e8),L"HP 50 PCT",&aStack_9a);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1f0),L"HP 40 PCT",&aStack_99);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1f8),L"HP 30 PCT",&aStack_98);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x200),L"HP 20 PCT",&aStack_97);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x208),L"HP 10 PCT",&aStack_96);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x210),L"Monster Alerted",&aStack_95);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x218),L"Player HP Below 90 PCT",
             &aStack_94);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x220),L"Player HP Below 80 PCT",
             &aStack_93);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x228),L"Player HP Below 70 PCT",
             &aStack_92);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x230),L"Player HP Below 60 PCT",
             &aStack_91);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x238),L"Player HP Below 50 PCT",
             &aStack_90);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x240),L"Player HP Below 40 PCT",
             &aStack_8f);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x248),L"Player HP Below 30 PCT",
             &aStack_8e);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x250),L"Player HP Below 20 PCT",
             &aStack_8d);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 600),L"Player HP Below 10 PCT",&aStack_8c
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x260),L"Player HP Above 90 PCT",
             &aStack_8b);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x268),L"Player HP Above 80 PCT",
             &aStack_8a);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x270),L"Player HP Above 70 PCT",
             &aStack_89);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x278),L"Player HP Above 60 PCT",
             &aStack_88);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x280),L"Player HP Above 50 PCT",
             &aStack_87);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x288),L"Player HP Above 40 PCT",
             &aStack_86);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x290),L"Player HP Above 30 PCT",
             &aStack_85);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x298),L"Player HP Above 20 PCT",
             &aStack_84);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2a0),L"Player HP Above 10 PCT",
             &aStack_83);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2a8),L"Accepted",&aStack_82)
  ;
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2b0),L"Declined",&aStack_81)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2b8),L"Camera Moving",&aStack_80);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2c0),L"Camera Stopped",&aStack_7f);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2c8),L"Camera Pausing",&aStack_7e);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2d0),L"Camera Control Restored",
             &aStack_7d);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2d8),L"Interacting",&aStack_7c);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2e0),L"Interacted",&aStack_7b);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2e8),L"Interacted Accepted",&aStack_7a)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2f0),L"Interacted Declined",&aStack_79)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2f8),L"Interacted Closed",&aStack_78);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x300),L"Invulnerable",&aStack_77);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x308),L"Vulnerable",&aStack_76);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x310),L"Quest Active",&aStack_75);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x318),L"Quest Not Active",&aStack_74);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 800),L"Quest Complete",&aStack_73);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x328),L"Quest Not Complete",&aStack_72);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x330),L"Quest Abandoned",&aStack_71);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x338),L"Skill Started",&aStack_70);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x340),L"Skill Stopped",&aStack_6f);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x348),L"Skill Learned",&aStack_6e);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x350),L"Skill Unlearned",&aStack_6d);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x358),L"Item Dropped",&aStack_6c);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x360),L"Item Equipped",&aStack_6b);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x368),L"Item Unequipped",&aStack_6a);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x370),L"End of Path Reached",&aStack_69)
  ;
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x378),L"Clicked",&aStack_68);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x380),L"Animation Stopped",&aStack_67);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x388),L"Animation Playing",&aStack_66);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x390),L"Skip Cutscene",&aStack_65);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x398),L"Level Activated",&aStack_64);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3a0),L"Insufficient funds",&aStack_63);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3a8),L"Money Taken",&aStack_62);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3b0),L"Stop",&aStack_61);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3b8),L"Start",&aStack_60);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3c0),L"Pause",&aStack_5f);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3c8),L"Output 1",&aStack_5e)
  ;
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3d0),L"Output 2",&aStack_5d)
  ;
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3d8),L"Output 3",&aStack_5c)
  ;
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3e0),L"Output 4",&aStack_5b)
  ;
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 1000),L"Output 5",&aStack_5a);
  __cxa_atexit(::__tcf_21,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KContextTipNames,L"TIP_INVENTORY",&aStack_59);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 8),L"TIP_UNIDENTIFIED",&aStack_58)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x10),L"TIP_INVENTORYFULL",&aStack_57);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x18),L"TIP_HEALTHLOW",&aStack_56)
  ;
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x20),L"TIP_MANALOW",&aStack_55);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x28),L"TIP_MERCHANT",&aStack_54);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x30),L"TIP_LEVELUP",&aStack_53);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x38),L"TIP_STATS",&aStack_52);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x40),L"TIP_SPELL",&aStack_51);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x48),L"TIP_WELCOME",&aStack_50);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x50),L"TIP_SOCKETABLE",&aStack_4f);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x58),L"TIP_PETFLEE",&aStack_4e);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x60),L"TIP_GAMBLE",&aStack_4d);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x68),L"TIP_ENCHANT",&aStack_4c);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x70),L"TIP_TRANSMUTE",&aStack_4b)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x78),L"TIP_PETINVENTORY",&aStack_4a);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x80),L"TIP_PETINVENTORYFULL",&aStack_49);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x88),L"TIP_STASH",&aStack_48);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x90),L"TIP_FISHING",&aStack_47);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x98),L"TIP_SPELLFIND",&aStack_46)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xa0),L"TIP_QUESTCOMPLETE",&aStack_45);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xa8),L"TIP_SHAREDSTASH",&aStack_44);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xb0),L"TIP_HOWTOATTACK",&aStack_43);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xb8),L"TIP_TEMP5",&aStack_42);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xc0),L"TIP_TEMP6",&aStack_41);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 200),L"TIP_TEMP7",&aStack_40);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xd0),L"TIP_TEMP8",&aStack_3f);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xd8),L"TIP_TEMP9",&aStack_3e);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xe0),L"TIP_TEMP10",&aStack_3d);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xe8),L"TIP_TEMP11",&aStack_3c);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xf0),L"TIP_TEMP12",&aStack_3b);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xf8),L"TIP_TEMP13",&aStack_3a);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x100),L"TIP_TEMP14",&aStack_39);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x108),L"TIP_TEMP15",&aStack_38);
  __cxa_atexit(::__tcf_22,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES,"tag_righthand",&aStack_37);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 8),"tag_lefthand",&aStack_36);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x10),"",&aStack_35);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x18),"Bip01 Head",&aStack_34);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x20),"",&aStack_33);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x28),"Bip01 L Clavicle",&aStack_32);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x30),"",&aStack_31);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x38),"",&aStack_30);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x40),"",&aStack_2f);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x48),"",&aStack_2e);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x50),"",&aStack_2d);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x58),"tag_leftarm",&aStack_2c);
  __cxa_atexit(::__tcf_23,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES_SECONDARY,"",&aStack_2b);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 8),"",&aStack_2a);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x10),"",&aStack_29);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x18),"",&aStack_28);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x20),"",&aStack_27);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x28),"Bip01 R Clavicle",
                      &aStack_26);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x30),"",&aStack_25);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x38),"",&aStack_24);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x40),"",&aStack_23);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x48),"",&aStack_22);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x50),"",&aStack_21);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x58),"",&aStack_20);
  __cxa_atexit(::__tcf_24,0,&__dso_handle);
  std::string::string((string *)::KEquipmentIconName,"EquipLeftHand",&aStack_1f);
  std::string::string((string *)(::KEquipmentIconName + 8),"EquipRightHand",&aStack_1e);
  std::string::string((string *)(::KEquipmentIconName + 0x10),"EquipGloves",&aStack_1d);
  std::string::string((string *)(::KEquipmentIconName + 0x18),"EquipHelm",&aStack_1c);
  std::string::string((string *)(::KEquipmentIconName + 0x20),"EquipChest",&aStack_1b);
  std::string::string((string *)(::KEquipmentIconName + 0x28),"EquipShoulder",&aStack_1a);
  std::string::string((string *)(::KEquipmentIconName + 0x30),"EquipBoots",&aStack_19);
  std::string::string((string *)(::KEquipmentIconName + 0x38),"EquipBelt",&aStack_18);
  std::string::string((string *)(::KEquipmentIconName + 0x40),"EquipRing1",&aStack_17);
  std::string::string((string *)(::KEquipmentIconName + 0x48),"EquipRing2",&aStack_16);
  std::string::string((string *)(::KEquipmentIconName + 0x50),"EquipAmulet",&aStack_15);
  std::string::string((string *)(::KEquipmentIconName + 0x58),"",&aStack_14);
  __cxa_atexit(::__tcf_25,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames,L"CHEST",&aStack_13);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 8),L"GLOVES",&aStack_12);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x10),L"BOOTS",&aStack_11);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x18),L"HELMET",&aStack_10);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x20),L"SHOULDERS",&aStack_f);
  __cxa_atexit(::__tcf_26,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames2,L"",&aStack_e);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 8),L"",&aStack_d);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x10),L"",&aStack_c);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x18),L"FACE",&aStack_b);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x20),L"",&aStack_a);
  __cxa_atexit(::__tcf_27,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::m_gFileVersionExtension,L".svt",&aStack_9);
  __cxa_atexit(std::wstring::~wstring,&::m_gFileVersionExtension,&__dso_handle);
  return;
}



/* address=007fea30
   symbol=CBaseUnit::CBaseUnit */

/* CBaseUnit::CBaseUnit(CResourceManager*, EBASEUNIT_TYPE) */

void __thiscall CBaseUnit::CBaseUnit(CBaseUnit *this,CResourceManager *param_1,undefined4 param_3)

{
  CRunicCore *this_00;

  CPositionableObject::CPositionableObject((CPositionableObject *)this,param_1,(SceneManager *)0x0);
  *(undefined ***)this = &PTR__CBaseUnit_00fc8fd0;
  *(undefined4 *)(this + 0x100) = 1;
  *(undefined8 *)(this + 0x108) = 0;
  *(undefined4 *)(this + 0x110) = 0;
  *(undefined4 *)(this + 0x114) = 0;
  *(undefined4 *)(this + 0x118) = 1;
  *(undefined8 *)(this + 0x120) = 0;
  *(undefined4 *)(this + 0x128) = 0;
  *(undefined4 *)(this + 300) = 0;
  *(undefined4 *)(this + 0x130) = 1;
  *(undefined8 *)(this + 0x138) = 0;
  *(undefined4 *)(this + 0x140) = 0;
  *(undefined4 *)(this + 0x144) = 0;
  *(undefined4 *)(this + 0x148) = 1;
  *(undefined8 *)(this + 0x150) = 0;
  *(undefined4 *)(this + 0x158) = 0;
  *(undefined4 *)(this + 0x15c) = 0;
  *(undefined4 *)(this + 0x160) = 1;
  *(undefined8 *)(this + 0x170) = 0xffffffffffffffff;
  *(undefined4 *)(this + 0x178) = 0xffffffff;
  *(undefined4 *)(this + 0x17c) = 0xffffffff;
  *(undefined8 *)(this + 0x180) = 0xffffffffffffffff;
  *(undefined4 *)(this + 0x188) = param_3;
  this[0x18c] = (CBaseUnit)0x1;
  this[0x18d] = (CBaseUnit)0x1;
  this[0x18e] = (CBaseUnit)0x0;
  this[399] = (CBaseUnit)0x1;
  this[400] = (CBaseUnit)0x0;
  this[0x191] = (CBaseUnit)0x0;
  *(undefined4 *)(this + 0x194) = 0x3e99999a;
  this[0x198] = (CBaseUnit)0x0;
  this[0x199] = (CBaseUnit)0x0;
  this[0x19a] = (CBaseUnit)0x0;
  this[0x19b] = (CBaseUnit)0x0;
  this[0x19c] = (CBaseUnit)0x0;
  *(undefined8 *)(this + 0x1a0) = 0xffffffffffffffff;
  this[0x1a8] = (CBaseUnit)0x0;
  this[0x1a9] = (CBaseUnit)0x1;
  *(undefined4 *)(this + 0x1ac) = 0;
  *(undefined8 *)(this + 0x1b0) = 0;
  *(undefined8 *)(this + 0x1b8) = 0;
  *(undefined8 *)(this + 0x1c0) = 0;
  *(undefined8 *)(this + 0x1c8) = 0;
  this[0x1d0] = (CBaseUnit)0x0;
  this[0x1d1] = (CBaseUnit)0x0;
  this[0x82] = (CBaseUnit)0x1;
                    /* try { // try from 007febe5 to 007febf9 has its CatchHandler @ 007fec97 */
  CSceneNodeObject::setVisible((CSceneNodeObject *)this,false);
  this_00 = (CRunicCore *)Ogre::NedAllocImpl::allocBytes(0xb8,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 007fec00 to 007fec04 has its CatchHandler @ 007fecda */
  CRunicCore::CRunicCore(this_00);
  *(undefined ***)this_00 = &PTR__CCullingBounds_00fc9310;
  *(undefined4 *)(this_00 + 0x18) = 0xbf400000;
  *(undefined4 *)(this_00 + 0x14) = 0;
  *(undefined4 *)(this_00 + 0x10) = 0xbf400000;
  *(undefined4 *)(this_00 + 0x24) = 0x3f400000;
  *(undefined4 *)(this_00 + 0x20) = 0x40000000;
  *(undefined4 *)(this_00 + 0x1c) = 0x3f400000;
  *(undefined4 *)(this_00 + 0x30) = 0xbf400000;
  *(undefined4 *)(this_00 + 0x2c) = 0;
  *(undefined4 *)(this_00 + 0x28) = 0xbf400000;
  *(undefined4 *)(this_00 + 0x3c) = 0x3f400000;
  *(undefined4 *)(this_00 + 0x38) = 0x40000000;
  *(undefined4 *)(this_00 + 0x34) = 0x3f400000;
  *(undefined4 *)(this_00 + 0x48) = 0xbf400000;
  *(undefined4 *)(this_00 + 0x44) = 0;
  *(undefined4 *)(this_00 + 0x40) = 0xbf400000;
  *(undefined4 *)(this_00 + 0x54) = 0x3f400000;
  *(undefined4 *)(this_00 + 0x50) = 0x40000000;
  *(undefined4 *)(this_00 + 0x4c) = 0x3f400000;
  *(CRunicCore **)(this + 0x1c0) = this_00;
  return;
}



/* address=007fecf0
   symbol=CBaseUnit::addAffix */

/* CBaseUnit::addAffix(CAffix*, unsigned int, CBaseUnit*, float) */

void __thiscall
CBaseUnit::addAffix(CBaseUnit *this,CAffix *param_1,uint param_2,CBaseUnit *param_3,float param_4)

{
  CEffectManager *this_00;

  this_00 = *(CEffectManager **)(this + 0x1b8);
  if (this_00 == (CEffectManager *)0x0) {
    this_00 = (CEffectManager *)Ogre::NedAllocImpl::allocBytes(0x2f8,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 007fed8c to 007fed90 has its CatchHandler @ 007fed9a */
    CEffectManager::CEffectManager(this_00,this);
    *(CEffectManager **)(this + 0x1b8) = this_00;
  }
  CEffectManager::addAffix(this_00,param_1,param_2,param_3,param_4);
  return;
}



/* address=007fedb0
   symbol=CBaseUnit::addAffix */

/* CBaseUnit::addAffix(std::wstring const&, unsigned int, CBaseUnit*, float) */

void __thiscall
CBaseUnit::addAffix(CBaseUnit *this,wstring_conflict *param_1,uint param_2,CBaseUnit *param_3,
                   float param_4)

{
  CEffectManager *this_00;

  this_00 = *(CEffectManager **)(this + 0x1b8);
  if (this_00 == (CEffectManager *)0x0) {
    this_00 = (CEffectManager *)Ogre::NedAllocImpl::allocBytes(0x2f8,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 007fee4c to 007fee50 has its CatchHandler @ 007fee5a */
    CEffectManager::CEffectManager(this_00,this);
    *(CEffectManager **)(this + 0x1b8) = this_00;
  }
  CEffectManager::addAffix
            (this_00,param_1,param_2,param_3,*(CResourceManager **)(this + 0x68),param_4);
  return;
}



/* address=007fee70
   symbol=CBaseUnit::~CBaseUnit */

/* CBaseUnit::~CBaseUnit() */

void __thiscall CBaseUnit::~CBaseUnit(CBaseUnit *this)

{
  CLevel *this_00;

  *(undefined ***)this = &PTR__CBaseUnit_00fc8fd0;
  if (((this[0x191] != (CBaseUnit)0x0) && (*(long *)(this + 0x68) != 0)) &&
     (this_00 = *(CLevel **)(*(long *)(this + 0x68) + 0x18), this_00 != (CLevel *)0x0)) {
                    /* try { // try from 007fee9f to 007fef0f has its CatchHandler @ 007fef98 */
    CLevel::removeUnit(this_00,this,false);
  }
  broadcastUnitState(this,0);
  *(undefined8 *)(this + 0x1a0) = 0xffffffffffffffff;
  *(undefined8 *)(this + 0x1b0) = 0;
  if (*(long **)(this + 0x1c0) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x1c0) + 8))();
    *(undefined8 *)(this + 0x1c0) = 0;
  }
  if (*(long **)(this + 0x1b8) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x1b8) + 8))();
    *(undefined8 *)(this + 0x1b8) = 0;
  }
  if (*(long **)(this + 0x1c8) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x1c8) + 8))();
    *(undefined8 *)(this + 0x1c8) = 0;
  }
  if (*(void **)(this + 0x150) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x150));
    *(undefined8 *)(this + 0x150) = 0;
  }
  if (*(void **)(this + 0x138) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x138));
    *(undefined8 *)(this + 0x138) = 0;
  }
  if (*(void **)(this + 0x120) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x120));
    *(undefined8 *)(this + 0x120) = 0;
  }
  if (*(void **)(this + 0x108) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x108));
    *(undefined8 *)(this + 0x108) = 0;
  }
  CPositionableObject::~CPositionableObject((CPositionableObject *)this);
  return;
}



/* address=007feff0
   symbol=CBaseUnit::~CBaseUnit */

/* CBaseUnit::~CBaseUnit() */

void __thiscall CBaseUnit::~CBaseUnit(CBaseUnit *this)

{
  ~CBaseUnit(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}



/* address=007ff010
   symbol=CBaseUnit::addSkillByName */

/* CBaseUnit::addSkillByName(std::wstring const&, bool) */

CSkill * CBaseUnit::addSkillByName(wstring_conflict *param_1,bool param_2)

{
  CSkill *this;
  CSkillManager *this_00;
  undefined7 in_register_00000031;

  this_00 = *(CSkillManager **)(param_1 + 0x1c8);
  if (this_00 == (CSkillManager *)0x0) {
    this_00 = (CSkillManager *)Ogre::NedAllocImpl::allocBytes(0x98,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 007ff0a0 to 007ff0a4 has its CatchHandler @ 007ff0ae */
    CSkillManager::CSkillManager
              (this_00,*(CResourceManager **)(param_1 + 0x68),(CBaseUnit *)param_1);
    *(CSkillManager **)(param_1 + 0x1c8) = this_00;
  }
  this = (CSkill *)
         CSkillManager::addSkill
                   (this_00,(wstring_conflict *)CONCAT71(in_register_00000031,param_2),true);
  if (this != (CSkill *)0x0) {
    CSkill::assignSkillAnimations(this,(CBaseUnit *)param_1);
  }
  return this;
}



/* address=007ff0d0
   symbol=CBaseUnit::addNewEffect */

/* CBaseUnit::addNewEffect(CEffect*) */

undefined8 __thiscall CBaseUnit::addNewEffect(CBaseUnit *this,CEffect *param_1)

{
  undefined8 uVar1;
  CEffectManager *this_00;

  if (param_1 != (CEffect *)0x0) {
    this_00 = *(CEffectManager **)(this + 0x1b8);
    if (this_00 == (CEffectManager *)0x0) {
      this_00 = (CEffectManager *)Ogre::NedAllocImpl::allocBytes(0x2f8,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 007ff144 to 007ff148 has its CatchHandler @ 007ff173 */
      CEffectManager::CEffectManager(this_00,this);
      *(CEffectManager **)(this + 0x1b8) = this_00;
    }
    uVar1 = CEffectManager::addNewEffect(this_00,param_1);
    return uVar1;
  }
  return 0;
}



/* address=007ff190
   symbol=CBaseUnit::copyEffect */

/* CBaseUnit::copyEffect(CBaseUnit*, CEffect*) */

undefined8 __thiscall CBaseUnit::copyEffect(CBaseUnit *this,CBaseUnit *param_1,CEffect *param_2)

{
  undefined8 uVar1;
  CEffectManager *this_00;

  if (param_2 != (CEffect *)0x0) {
    this_00 = *(CEffectManager **)(this + 0x1b8);
    if (this_00 == (CEffectManager *)0x0) {
      this_00 = (CEffectManager *)Ogre::NedAllocImpl::allocBytes(0x2f8,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 007ff214 to 007ff218 has its CatchHandler @ 007ff247 */
      CEffectManager::CEffectManager(this_00,this);
      *(CEffectManager **)(this + 0x1b8) = this_00;
    }
    uVar1 = CEffectManager::cloneEffect(this_00,param_1,param_2);
    return uVar1;
  }
  return 0;
}



/* address=007ff260
   symbol=CBaseUnit::copyEffects */

/* CBaseUnit::copyEffects(CBaseUnit*, TArrayList<CEffect*> const*) */

void __thiscall CBaseUnit::copyEffects(CBaseUnit *this,CBaseUnit *param_1,TArrayList *param_2)

{
  undefined8 *puVar1;
  uint uVar2;

  if ((param_2 != (TArrayList *)0x0) && (*(int *)(param_2 + 8) != 0)) {
    uVar2 = 0;
    do {
      if (uVar2 < *(uint *)(param_2 + 0xc)) {
        puVar1 = (undefined8 *)((ulong)uVar2 * 8 + *(long *)param_2);
      }
      else {
        puVar1 = *(undefined8 **)param_2;
      }
      uVar2 = uVar2 + 1;
      copyEffect(this,param_1,(CEffect *)*puVar1);
    } while (uVar2 < *(uint *)(param_2 + 8));
  }
  return;
}



/* address=007ff2d0
   symbol=CBaseUnit::cloneSkill */

/* CBaseUnit::cloneSkill(CSkill*) */

CSkill * __thiscall CBaseUnit::cloneSkill(CBaseUnit *this,CSkill *param_1)

{
  CSkill *this_00;
  CSkillManager *this_01;

  this_00 = (CSkill *)0x0;
  if (param_1 != (CSkill *)0x0) {
    this_01 = *(CSkillManager **)(this + 0x1c8);
    if (this_01 == (CSkillManager *)0x0) {
      this_01 = (CSkillManager *)Ogre::NedAllocImpl::allocBytes(0x98,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 007ff360 to 007ff364 has its CatchHandler @ 007ff36e */
      CSkillManager::CSkillManager(this_01,*(CResourceManager **)(this + 0x68),this);
      *(CSkillManager **)(this + 0x1c8) = this_01;
    }
    this_00 = (CSkill *)CSkillManager::addSkill(this_01,param_1,true,false);
    CSkill::assignSkillAnimations(this_00,this);
  }
  return this_00;
}



/* address=007ff390
   symbol=CBaseUnit::hasUnitTheme */

/* CBaseUnit::hasUnitTheme(std::wstring const&) */

undefined8 __thiscall CBaseUnit::hasUnitTheme(CBaseUnit *this,wstring_conflict *param_1)

{
  uint uVar1;
  uint uVar2;
  wchar_t *__s2;
  size_t __n;
  wchar_t *__s1;
  size_t sVar3;
  int iVar4;
  long lVar5;
  undefined8 uVar6;
  uint uVar7;
  undefined8 *puVar8;
  long lVar9;
  CUnitTheme *pCVar10;

  lVar5 = CUnitThemes::getSingleton();
  if (lVar5 == 0) {
    return 0;
  }
  uVar1 = *(uint *)(lVar5 + 0x20);
  if (uVar1 != 0) {
    __s2 = *(wchar_t **)param_1;
    uVar2 = *(uint *)(lVar5 + 0x24);
    lVar9 = 0;
    uVar7 = 0;
    __n = *(size_t *)(__s2 + -6);
    do {
      if (uVar7 < uVar2) {
        __s1 = *(wchar_t **)(*(long *)(lVar9 + *(long *)(lVar5 + 0x18)) + 0x28);
        sVar3 = *(size_t *)(__s1 + -6);
      }
      else {
        __s1 = *(wchar_t **)(**(long **)(lVar5 + 0x18) + 0x28);
        sVar3 = *(size_t *)(__s1 + -6);
      }
      if ((sVar3 == __n) && (iVar4 = wmemcmp(__s1,__s2,__n), iVar4 == 0)) {
        if (uVar7 < uVar2) {
          puVar8 = (undefined8 *)((ulong)uVar7 * 8 + *(long *)(lVar5 + 0x18));
        }
        else {
          puVar8 = *(undefined8 **)(lVar5 + 0x18);
        }
        pCVar10 = (CUnitTheme *)*puVar8;
        goto LAB_007ff442;
      }
      uVar7 = uVar7 + 1;
      lVar9 = lVar9 + 8;
    } while (uVar7 < uVar1);
  }
  pCVar10 = (CUnitTheme *)0x0;
LAB_007ff442:
  uVar6 = hasUnitTheme(this,pCVar10);
  return uVar6;
}



/* address=007ff6d0
   symbol=CBaseUnit::update */

/* CBaseUnit::update(Ogre::Camera*, Ogre::Vector3 const&, float) */

void CBaseUnit::update(Camera *param_1,Vector3 *param_2,float param_3)

{
  long *plVar1;
  long lVar2;
  undefined8 uVar3;
  uint uVar4;
  uint uVar5;
  void *pvVar6;
  long *plVar7;
  undefined8 *puVar8;
  ulong uVar9;
  long *plVar10;
  uint uVar11;
  uint uVar12;

  if (*(CSkillManager **)(param_1 + 0x1c8) != (CSkillManager *)0x0) {
    CSkillManager::update(*(CSkillManager **)(param_1 + 0x1c8),param_3);
  }
  if (*(int *)(param_1 + 0x128) != 0) {
    uVar9 = 0;
    do {
      if ((uint)uVar9 < *(uint *)(param_1 + 300)) {
        puVar8 = (undefined8 *)(uVar9 * 8 + *(long *)(param_1 + 0x120));
      }
      else {
        puVar8 = *(undefined8 **)(param_1 + 0x120);
      }
      uVar11 = (uint)uVar9 + 1;
      uVar9 = (ulong)uVar11;
      (**(code **)(*(long *)param_1 + 0x1d8))(param_1,*puVar8,1);
    } while (uVar11 < *(uint *)(param_1 + 0x128));
  }
  *(undefined4 *)(param_1 + 0x128) = 0;
  *(undefined4 *)(param_1 + 300) = 0;
  if (*(void **)(param_1 + 0x120) != (void *)0x0) {
    operator_delete__(*(void **)(param_1 + 0x120));
  }
  *(undefined8 *)(param_1 + 0x120) = 0;
  if (*(int *)(param_1 + 0x110) != 0) {
    uVar11 = 0;
    do {
      if (uVar11 < *(uint *)(param_1 + 0x114)) {
        puVar8 = (undefined8 *)((ulong)uVar11 * 8 + *(long *)(param_1 + 0x108));
      }
      else {
        puVar8 = *(undefined8 **)(param_1 + 0x108);
      }
      uVar11 = uVar11 + 1;
      (**(code **)(*(long *)param_1 + 0x1d8))(param_1,*puVar8,0);
    } while (uVar11 < *(uint *)(param_1 + 0x110));
  }
  *(undefined4 *)(param_1 + 0x110) = 0;
  *(undefined4 *)(param_1 + 0x114) = 0;
  if (*(void **)(param_1 + 0x108) != (void *)0x0) {
    operator_delete__(*(void **)(param_1 + 0x108));
  }
  *(undefined8 *)(param_1 + 0x108) = 0;
  if (*(CEffectManager **)(param_1 + 0x1b8) != (CEffectManager *)0x0) {
    CEffectManager::updateAffixes(*(CEffectManager **)(param_1 + 0x1b8),param_3);
    lVar2 = *(long *)(param_1 + 0x1b8);
    if (lVar2 != -0x2c8) {
      if (*(int *)(lVar2 + 0x2d0) == 0) {
        uVar11 = *(uint *)(param_1 + 0x158);
        uVar12 = uVar11;
      }
      else {
        uVar12 = *(uint *)(param_1 + 0x158);
        uVar9 = 0;
        uVar11 = uVar12;
        do {
          uVar5 = (uint)uVar9;
          if (uVar5 < *(uint *)(lVar2 + 0x2d4)) {
            plVar7 = (long *)(uVar9 * 8 + *(long *)(lVar2 + 0x2c8));
          }
          else {
            plVar7 = *(long **)(lVar2 + 0x2c8);
          }
          if (uVar11 == 0) {
LAB_007ff8a8:
            if (uVar5 < *(uint *)(lVar2 + 0x2d4)) {
              puVar8 = (undefined8 *)(uVar9 * 8 + *(long *)(lVar2 + 0x2c8));
            }
            else {
              puVar8 = *(undefined8 **)(lVar2 + 0x2c8);
            }
            (**(code **)(*(long *)param_1 + 0x1d8))(param_1,*puVar8,0);
            if (uVar5 < *(uint *)(lVar2 + 0x2d4)) {
              puVar8 = (undefined8 *)(uVar9 * 8 + *(long *)(lVar2 + 0x2c8));
            }
            else {
              puVar8 = *(undefined8 **)(lVar2 + 0x2c8);
            }
            uVar11 = *(uint *)(param_1 + 0x158);
            uVar3 = *puVar8;
            if (uVar11 < *(uint *)(param_1 + 0x15c)) {
              pvVar6 = *(void **)(param_1 + 0x150);
            }
            else if (*(long *)(param_1 + 0x150) == 0) {
              *(uint *)(param_1 + 0x15c) = *(uint *)(param_1 + 0x160);
              pvVar6 = operator_new__((ulong)*(uint *)(param_1 + 0x160) << 3);
              uVar11 = *(uint *)(param_1 + 0x158);
              *(void **)(param_1 + 0x150) = pvVar6;
            }
            else {
              uVar12 = *(uint *)(param_1 + 0x15c) + *(int *)(param_1 + 0x160);
              pvVar6 = operator_new__((ulong)uVar12 << 3);
              if (*(int *)(param_1 + 0x15c) != 0) {
                uVar11 = 0;
                do {
                  uVar9 = (ulong)uVar11;
                  uVar11 = uVar11 + 1;
                  *(undefined8 *)((long)pvVar6 + uVar9 * 8) =
                       *(undefined8 *)(*(long *)(param_1 + 0x150) + uVar9 * 8);
                } while (uVar11 < *(uint *)(param_1 + 0x15c));
              }
              if (*(void **)(param_1 + 0x150) != (void *)0x0) {
                operator_delete__(*(void **)(param_1 + 0x150));
              }
              uVar11 = *(uint *)(param_1 + 0x158);
              *(void **)(param_1 + 0x150) = pvVar6;
              *(uint *)(param_1 + 0x15c) = uVar12;
            }
            *(undefined8 *)((long)pvVar6 + (ulong)uVar11 * 8) = uVar3;
            uVar11 = *(int *)(param_1 + 0x158) + 1;
            *(uint *)(param_1 + 0x158) = uVar11;
            uVar12 = uVar11;
          }
          else {
            plVar10 = *(long **)(param_1 + 0x150);
            uVar4 = 0;
            if (*plVar7 != *plVar10) {
              do {
                uVar4 = uVar4 + 1;
                if (uVar11 <= uVar4) goto LAB_007ff8a8;
                plVar1 = plVar10 + 1;
                plVar10 = plVar10 + 1;
              } while (*plVar7 != *plVar1);
              if (uVar4 == 0xffffffff) goto LAB_007ff8a8;
            }
          }
          uVar9 = (ulong)(uVar5 + 1);
        } while (uVar5 + 1 < *(uint *)(lVar2 + 0x2d0));
      }
      if (uVar11 != 0) {
        uVar11 = 0;
        do {
          if (uVar11 < *(uint *)(param_1 + 0x15c)) {
            plVar7 = (long *)((ulong)uVar11 * 8 + *(long *)(param_1 + 0x150));
          }
          else {
            plVar7 = *(long **)(param_1 + 0x150);
          }
          if (*(uint *)(lVar2 + 0x2d0) == 0) {
LAB_007ffa00:
            if (uVar11 < *(uint *)(param_1 + 0x15c)) {
              puVar8 = (undefined8 *)((ulong)uVar11 * 8 + *(long *)(param_1 + 0x150));
            }
            else {
              puVar8 = *(undefined8 **)(param_1 + 0x150);
            }
            (**(code **)(*(long *)param_1 + 0x1d8))(param_1,*puVar8,1);
            uVar12 = *(uint *)(param_1 + 0x158);
            if (uVar11 < uVar12) {
              *(uint *)(param_1 + 0x158) = uVar12 - 1;
              *(undefined8 *)(*(long *)(param_1 + 0x150) + (ulong)uVar11 * 8) =
                   *(undefined8 *)(*(long *)(param_1 + 0x150) + (ulong)(uVar12 - 1) * 8);
              uVar12 = *(uint *)(param_1 + 0x158);
            }
            uVar11 = uVar11 - 1;
          }
          else {
            plVar10 = *(long **)(lVar2 + 0x2c8);
            uVar5 = 0;
            if (*plVar7 != *plVar10) {
              do {
                uVar5 = uVar5 + 1;
                if (*(uint *)(lVar2 + 0x2d0) <= uVar5) goto LAB_007ffa00;
                plVar1 = plVar10 + 1;
                plVar10 = plVar10 + 1;
              } while (*plVar7 != *plVar1);
              if (uVar5 == 0xffffffff) goto LAB_007ffa00;
            }
          }
          uVar11 = uVar11 + 1;
        } while (uVar11 < uVar12);
      }
    }
  }
  return;
}



/* address=007ffb70
   symbol=CBaseUnit::removeUnitTheme */

/* CBaseUnit::removeUnitTheme(CUnitTheme*) */

void __thiscall CBaseUnit::removeUnitTheme(CBaseUnit *this,CUnitTheme *param_1)

{
  long *plVar1;
  long lVar2;
  uint uVar3;
  void *pvVar4;
  long *plVar5;
  ulong uVar6;
  long lVar7;
  uint uVar8;

  if (*(uint *)(this + 0x140) != 0) {
    plVar5 = *(long **)(this + 0x138);
    uVar3 = 0;
    if (param_1 != (CUnitTheme *)*plVar5) {
      do {
        uVar3 = uVar3 + 1;
        if (*(uint *)(this + 0x140) <= uVar3) {
          return;
        }
        plVar1 = plVar5 + 1;
        plVar5 = plVar5 + 1;
      } while (param_1 != (CUnitTheme *)*plVar1);
      if (uVar3 == 0xffffffff) {
        return;
      }
    }
    uVar3 = *(uint *)(this + 0x128);
    if (uVar3 < *(uint *)(this + 300)) {
      pvVar4 = *(void **)(this + 0x120);
    }
    else if (*(long *)(this + 0x120) == 0) {
      *(uint *)(this + 300) = *(uint *)(this + 0x130);
      pvVar4 = operator_new__((ulong)*(uint *)(this + 0x130) << 3);
      *(void **)(this + 0x120) = pvVar4;
      uVar3 = *(uint *)(this + 0x128);
    }
    else {
      uVar8 = *(uint *)(this + 300) + *(int *)(this + 0x130);
      pvVar4 = operator_new__((ulong)uVar8 << 3);
      if (*(int *)(this + 300) != 0) {
        uVar3 = 0;
        do {
          uVar6 = (ulong)uVar3;
          uVar3 = uVar3 + 1;
          *(undefined8 *)((long)pvVar4 + uVar6 * 8) =
               *(undefined8 *)(*(long *)(this + 0x120) + uVar6 * 8);
        } while (uVar3 < *(uint *)(this + 300));
      }
      if (*(void **)(this + 0x120) != (void *)0x0) {
        operator_delete__(*(void **)(this + 0x120));
      }
      uVar3 = *(uint *)(this + 0x128);
      *(void **)(this + 0x120) = pvVar4;
      *(uint *)(this + 300) = uVar8;
    }
    *(CUnitTheme **)((long)pvVar4 + (ulong)uVar3 * 8) = param_1;
    uVar3 = *(uint *)(this + 0x110);
    *(int *)(this + 0x128) = *(int *)(this + 0x128) + 1;
    if (uVar3 != 0) {
      plVar5 = *(long **)(this + 0x108);
      uVar8 = 0;
      lVar2 = 8;
      if (param_1 == (CUnitTheme *)*plVar5) {
        lVar7 = 0;
      }
      else {
        do {
          lVar7 = lVar2;
          uVar8 = uVar8 + 1;
          if (uVar3 <= uVar8) goto LAB_007ffc9c;
          lVar2 = lVar7 + 8;
        } while (param_1 != *(CUnitTheme **)((long)plVar5 + lVar7));
      }
      *(uint *)(this + 0x110) = uVar3 - 1;
      *(long *)((long)plVar5 + lVar7) = plVar5[uVar3 - 1];
    }
LAB_007ffc9c:
    uVar3 = *(uint *)(this + 0x140);
    if (uVar3 != 0) {
      plVar5 = *(long **)(this + 0x138);
      uVar8 = 0;
      lVar2 = 8;
      if (param_1 == (CUnitTheme *)*plVar5) {
        lVar7 = 0;
      }
      else {
        do {
          lVar7 = lVar2;
          uVar8 = uVar8 + 1;
          if (uVar3 <= uVar8) {
            return;
          }
          lVar2 = lVar7 + 8;
        } while (param_1 != *(CUnitTheme **)((long)plVar5 + lVar7));
      }
      *(uint *)(this + 0x140) = uVar3 - 1;
      *(long *)((long)plVar5 + lVar7) = plVar5[uVar3 - 1];
      return;
    }
  }
  return;
}



/* address=007ffd60
   symbol=CBaseUnit::removeUnitTheme */

/* CBaseUnit::removeUnitTheme(std::wstring const&) */

void __thiscall CBaseUnit::removeUnitTheme(CBaseUnit *this,wstring_conflict *param_1)

{
  uint uVar1;
  uint uVar2;
  wchar_t *__s2;
  size_t __n;
  wchar_t *__s1;
  size_t sVar3;
  int iVar4;
  long lVar5;
  uint uVar6;
  undefined8 *puVar7;
  long lVar8;
  CUnitTheme *pCVar9;

  lVar5 = CUnitThemes::getSingleton();
  if (lVar5 == 0) {
    return;
  }
  uVar1 = *(uint *)(lVar5 + 0x20);
  if (uVar1 != 0) {
    __s2 = *(wchar_t **)param_1;
    uVar2 = *(uint *)(lVar5 + 0x24);
    lVar8 = 0;
    uVar6 = 0;
    __n = *(size_t *)(__s2 + -6);
    do {
      if (uVar6 < uVar2) {
        __s1 = *(wchar_t **)(*(long *)(lVar8 + *(long *)(lVar5 + 0x18)) + 0x28);
        sVar3 = *(size_t *)(__s1 + -6);
      }
      else {
        __s1 = *(wchar_t **)(**(long **)(lVar5 + 0x18) + 0x28);
        sVar3 = *(size_t *)(__s1 + -6);
      }
      if ((sVar3 == __n) && (iVar4 = wmemcmp(__s1,__s2,__n), iVar4 == 0)) {
        if (uVar6 < uVar2) {
          puVar7 = (undefined8 *)((ulong)uVar6 * 8 + *(long *)(lVar5 + 0x18));
        }
        else {
          puVar7 = *(undefined8 **)(lVar5 + 0x18);
        }
        pCVar9 = (CUnitTheme *)*puVar7;
        goto LAB_007ffe22;
      }
      uVar6 = uVar6 + 1;
      lVar8 = lVar8 + 8;
    } while (uVar6 < uVar1);
  }
  pCVar9 = (CUnitTheme *)0x0;
LAB_007ffe22:
  removeUnitTheme(this,pCVar9);
  return;
}



/* address=007ffe50
   symbol=CBaseUnit::removeUnitTheme */

/* CBaseUnit::removeUnitTheme(long long) */

void __thiscall CBaseUnit::removeUnitTheme(CBaseUnit *this,longlong param_1)

{
  long lVar1;
  long lVar2;
  long lVar3;
  uint uVar4;
  undefined8 *puVar5;

  lVar2 = CUnitThemes::getSingleton();
  if (lVar2 == 0) {
    return;
  }
  if (*(uint *)(lVar2 + 0x20) != 0) {
    lVar3 = 0;
    uVar4 = 0;
    do {
      if (uVar4 < *(uint *)(lVar2 + 0x24)) {
        lVar1 = *(long *)(*(long *)(lVar3 + *(long *)(lVar2 + 0x18)) + 0x30);
      }
      else {
        lVar1 = *(long *)(**(long **)(lVar2 + 0x18) + 0x30);
      }
      if (param_1 == lVar1) {
        if (uVar4 < *(uint *)(lVar2 + 0x24)) {
          puVar5 = (undefined8 *)((ulong)uVar4 * 8 + *(long *)(lVar2 + 0x18));
        }
        else {
          puVar5 = *(undefined8 **)(lVar2 + 0x18);
        }
        removeUnitTheme(this,(CUnitTheme *)*puVar5);
        return;
      }
      uVar4 = uVar4 + 1;
      lVar3 = lVar3 + 8;
    } while (uVar4 < *(uint *)(lVar2 + 0x20));
  }
  removeUnitTheme(this,(CUnitTheme *)0x0);
  return;
}



/* address=007fff00
   symbol=CBaseUnit::updateCullingBounds */

/* CBaseUnit::updateCullingBounds() */

void CBaseUnit::updateCullingBounds(void)

{
  long lVar1;
  float fVar2;
  float fVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  long lVar9;
  long lVar10;
  CPositionableObject *this;
  CPositionableObject *in_RDI;
  float fVar11;
  undefined8 uVar12;
  float in_XMM1_Da;
  float fVar13;
  float fVar14;
  float fVar15;
  float local_d8;
  float local_d4;
  float local_d0;
  float local_88;
  float fStack_84;
  float local_80;
  float local_78;
  float fStack_74;
  float local_70;
  float local_68;
  float fStack_64;
  float local_60;
  float local_58;
  float fStack_54;
  float local_50;
  float fStack_4c;
  float local_38;
  float fStack_34;
  float local_28;
  float fStack_24;

  if (*(long *)(in_RDI + 0x1c0) != 0) {
    uVar12 = CPositionableObject::getPosition(in_RDI,true);
    fStack_24 = (float)((ulong)uVar12 >> 0x20);
    local_28 = (float)uVar12;
    local_d4 = fStack_24;
    local_d8 = local_28;
    fVar13 = in_XMM1_Da;
    lVar10 = (**(code **)(*(long *)in_RDI + 0x1e0))();
    local_d0 = in_XMM1_Da;
    if (lVar10 != 0) {
      lVar10 = (**(code **)(*(long *)in_RDI + 0x1e0))();
      fStack_34 = DAT_014241b0;
      local_38 = Ogre::Vector3::ZERO;
      local_d0 = DAT_014241b4;
      if (lVar10 != 0) {
        this = (CPositionableObject *)(**(code **)(*(long *)in_RDI + 0x1e0))();
        uVar12 = CPositionableObject::getPosition(this,false);
        fStack_34 = (float)((ulong)uVar12 >> 0x20);
        local_38 = (float)uVar12;
        local_d0 = fVar13;
      }
      local_d8 = local_38 + local_28;
      local_d4 = fStack_34 + fStack_24;
      local_d0 = local_d0 + in_XMM1_Da;
    }
    local_80 = (float)*(undefined8 *)(in_RDI + 200);
    local_70 = (float)*(undefined8 *)(in_RDI + 0xd8);
    local_60 = (float)*(undefined8 *)(in_RDI + 0xe8);
    local_58 = (float)*(undefined8 *)(in_RDI + 0xf0);
    lVar9 = *(long *)(in_RDI + 0x1c0);
    fStack_54 = (float)((ulong)*(undefined8 *)(in_RDI + 0xf0) >> 0x20);
    local_50 = (float)*(undefined8 *)(in_RDI + 0xf8);
    fVar13 = *(float *)(lVar9 + 0x10);
    lVar10 = lVar9 + 0x4c;
    lVar1 = lVar9 + 0x40;
    fStack_4c = (float)((ulong)*(undefined8 *)(in_RDI + 0xf8) >> 0x20);
    fVar2 = *(float *)(lVar9 + 0x14);
    fVar3 = *(float *)(lVar9 + 0x18);
    local_88 = (float)*(undefined8 *)(in_RDI + 0xc0);
    fStack_84 = (float)((ulong)*(undefined8 *)(in_RDI + 0xc0) >> 0x20);
    local_78 = (float)*(undefined8 *)(in_RDI + 0xd0);
    fVar14 = DAT_00fa47fc / (local_58 * fVar13 + fStack_54 * fVar2 + local_50 * fVar3 + fStack_4c);
    fStack_74 = (float)((ulong)*(undefined8 *)(in_RDI + 0xd0) >> 0x20);
    fVar11 = (local_88 * fVar13 + fStack_84 * fVar2 + local_80 * fVar3 + local_d8) * fVar14;
    local_68 = (float)*(undefined8 *)(in_RDI + 0xe0);
    fStack_64 = (float)((ulong)*(undefined8 *)(in_RDI + 0xe0) >> 0x20);
    fVar15 = (local_78 * fVar13 + fStack_74 * fVar2 + local_70 * fVar3 + local_d4) * fVar14;
    *(float *)(lVar9 + 0x44) = fVar15;
    *(float *)(lVar9 + 0x40) = fVar11;
    fVar14 = (fVar13 * local_68 + fVar2 * fStack_64 + fVar3 * local_60 + local_d0) * fVar14;
    *(float *)(lVar9 + 0x48) = fVar14;
    *(float *)(lVar9 + 0x50) = fVar15;
    *(float *)(lVar9 + 0x54) = fVar14;
    *(float *)(lVar9 + 0x4c) = fVar11;
    MATH::expandBounds((MATH *)CONCAT44(fVar15,fVar11),lVar1,lVar10);
    fVar13 = *(float *)(lVar9 + 0x1c);
    fVar2 = *(float *)(lVar9 + 0x20);
    fVar3 = *(float *)(lVar9 + 0x24);
    fVar11 = DAT_00fa47fc / (local_58 * fVar13 + fStack_54 * fVar2 + local_50 * fVar3 + fStack_4c);
    MATH::expandBounds((MATH *)CONCAT44((local_78 * fVar13 + fStack_74 * fVar2 + local_70 * fVar3 +
                                        local_d4) * fVar11,
                                        (fVar13 * local_88 + fVar2 * fStack_84 + fVar3 * local_80 +
                                        local_d8) * fVar11),lVar1,lVar10);
    fVar13 = *(float *)(lVar9 + 0x14);
    fVar2 = *(float *)(lVar9 + 0x10);
    fVar3 = *(float *)(lVar9 + 0x24);
    fVar11 = DAT_00fa47fc / (local_58 * fVar2 + fStack_54 * fVar13 + local_50 * fVar3 + fStack_4c);
    MATH::expandBounds((MATH *)CONCAT44((local_78 * fVar2 + fStack_74 * fVar13 + local_70 * fVar3 +
                                        local_d4) * fVar11,
                                        (fVar2 * local_88 + fVar13 * fStack_84 + fVar3 * local_80 +
                                        local_d8) * fVar11),lVar1,lVar10);
    fVar13 = *(float *)(lVar9 + 0x20);
    fVar2 = *(float *)(lVar9 + 0x10);
    fVar3 = *(float *)(lVar9 + 0x24);
    fVar11 = DAT_00fa47fc / (local_58 * fVar2 + fStack_54 * fVar13 + local_50 * fVar3 + fStack_4c);
    MATH::expandBounds((MATH *)CONCAT44((local_78 * fVar2 + fStack_74 * fVar13 + local_70 * fVar3 +
                                        local_d4) * fVar11,
                                        (fVar2 * local_88 + fVar13 * fStack_84 + fVar3 * local_80 +
                                        local_d8) * fVar11),lVar1,lVar10);
    fVar13 = *(float *)(lVar9 + 0x20);
    fVar2 = *(float *)(lVar9 + 0x10);
    fVar3 = *(float *)(lVar9 + 0x18);
    fVar11 = DAT_00fa47fc / (local_58 * fVar2 + fStack_54 * fVar13 + local_50 * fVar3 + fStack_4c);
    MATH::expandBounds((MATH *)CONCAT44((local_78 * fVar2 + fStack_74 * fVar13 + local_70 * fVar3 +
                                        local_d4) * fVar11,
                                        (fVar2 * local_88 + fVar13 * fStack_84 + fVar3 * local_80 +
                                        local_d8) * fVar11),lVar1,lVar10);
    fVar13 = *(float *)(lVar9 + 0x14);
    fVar2 = *(float *)(lVar9 + 0x1c);
    fVar3 = *(float *)(lVar9 + 0x18);
    fVar11 = DAT_00fa47fc / (local_58 * fVar2 + fStack_54 * fVar13 + local_50 * fVar3 + fStack_4c);
    MATH::expandBounds((MATH *)CONCAT44((local_78 * fVar2 + fStack_74 * fVar13 + local_70 * fVar3 +
                                        local_d4) * fVar11,
                                        (fVar2 * local_88 + fVar13 * fStack_84 + fVar3 * local_80 +
                                        local_d8) * fVar11),lVar1,lVar10);
    fVar13 = *(float *)(lVar9 + 0x20);
    fVar2 = *(float *)(lVar9 + 0x1c);
    fVar3 = *(float *)(lVar9 + 0x18);
    fVar11 = DAT_00fa47fc / (local_58 * fVar2 + fStack_54 * fVar13 + local_50 * fVar3 + fStack_4c);
    MATH::expandBounds((MATH *)CONCAT44((local_78 * fVar2 + fStack_74 * fVar13 + local_70 * fVar3 +
                                        local_d4) * fVar11,
                                        (fVar2 * local_88 + fVar13 * fStack_84 + fVar3 * local_80 +
                                        local_d8) * fVar11),lVar1,lVar10);
    fVar13 = *(float *)(lVar9 + 0x14);
    fVar2 = *(float *)(lVar9 + 0x1c);
    fVar3 = *(float *)(lVar9 + 0x24);
    fVar11 = DAT_00fa47fc / (local_58 * fVar2 + fStack_54 * fVar13 + local_50 * fVar3 + fStack_4c);
    MATH::expandBounds((MATH *)CONCAT44((local_78 * fVar2 + fStack_74 * fVar13 + local_70 * fVar3 +
                                        local_d4) * fVar11,
                                        (fVar2 * local_88 + fVar13 * fStack_84 + fVar3 * local_80 +
                                        local_d8) * fVar11),lVar1,lVar10);
    uVar4 = *(undefined4 *)(lVar9 + 0x48);
    uVar5 = *(undefined4 *)(lVar9 + 0x44);
    uVar6 = *(undefined4 *)(lVar9 + 0x40);
    uVar7 = *(undefined4 *)(lVar9 + 0x4c);
    uVar8 = *(undefined4 *)(lVar9 + 0x50);
    *(undefined4 *)(lVar9 + 0x60) = uVar4;
    *(undefined4 *)(lVar9 + 0x6c) = uVar4;
    *(undefined4 *)(lVar9 + 0x78) = uVar4;
    *(undefined4 *)(lVar9 + 0x84) = uVar4;
    uVar4 = *(undefined4 *)(lVar9 + 0x54);
    *(undefined4 *)(lVar9 + 0x58) = uVar6;
    *(undefined4 *)(lVar9 + 0x5c) = uVar5;
    *(undefined4 *)(lVar9 + 100) = uVar7;
    *(undefined4 *)(lVar9 + 0x68) = uVar5;
    *(undefined4 *)(lVar9 + 0x70) = uVar6;
    *(undefined4 *)(lVar9 + 0x74) = uVar8;
    *(undefined4 *)(lVar9 + 0x7c) = uVar7;
    *(undefined4 *)(lVar9 + 0x80) = uVar8;
    *(undefined4 *)(lVar9 + 0x88) = uVar6;
    *(undefined4 *)(lVar9 + 0x8c) = uVar5;
    *(undefined4 *)(lVar9 + 0x90) = uVar4;
    *(undefined4 *)(lVar9 + 0x94) = uVar7;
    *(undefined4 *)(lVar9 + 0x98) = uVar5;
    *(undefined4 *)(lVar9 + 0x9c) = uVar4;
    *(undefined4 *)(lVar9 + 0xa0) = uVar6;
    *(undefined4 *)(lVar9 + 0xa4) = uVar8;
    *(undefined4 *)(lVar9 + 0xa8) = uVar4;
    *(undefined4 *)(lVar9 + 0xac) = uVar7;
    *(undefined4 *)(lVar9 + 0xb0) = uVar8;
    *(undefined4 *)(lVar9 + 0xb4) = uVar4;
  }
  return;
}



/* address=00800a20
   symbol=CBaseUnit::addUnitTheme */

/* CBaseUnit::addUnitTheme(CUnitTheme*) */

void __thiscall CBaseUnit::addUnitTheme(CBaseUnit *this,CUnitTheme *param_1)

{
  long *plVar1;
  long lVar2;
  uint uVar3;
  uint uVar4;
  void *pvVar5;
  long *plVar6;
  ulong uVar7;
  long lVar8;

  if (*(uint *)(this + 0x140) != 0) {
    plVar6 = *(long **)(this + 0x138);
    uVar3 = 0;
    if (param_1 == (CUnitTheme *)*plVar6) {
      return;
    }
    do {
      uVar3 = uVar3 + 1;
      if (*(uint *)(this + 0x140) <= uVar3) goto LAB_00800a68;
      plVar1 = plVar6 + 1;
      plVar6 = plVar6 + 1;
    } while (param_1 != (CUnitTheme *)*plVar1);
    if (uVar3 != 0xffffffff) {
      return;
    }
  }
LAB_00800a68:
  uVar3 = *(uint *)(this + 0x128);
  if (uVar3 != 0) {
    plVar6 = *(long **)(this + 0x120);
    uVar4 = 0;
    lVar2 = 8;
    if (param_1 == (CUnitTheme *)*plVar6) {
      lVar8 = 0;
    }
    else {
      do {
        lVar8 = lVar2;
        uVar4 = uVar4 + 1;
        if (uVar3 <= uVar4) goto LAB_00800aa8;
        lVar2 = lVar8 + 8;
      } while (param_1 != *(CUnitTheme **)((long)plVar6 + lVar8));
    }
    *(uint *)(this + 0x128) = uVar3 - 1;
    *(long *)((long)plVar6 + lVar8) = plVar6[uVar3 - 1];
  }
LAB_00800aa8:
  uVar3 = *(uint *)(this + 0x110);
  if (uVar3 < *(uint *)(this + 0x114)) {
    pvVar5 = *(void **)(this + 0x108);
  }
  else if (*(long *)(this + 0x108) == 0) {
    *(uint *)(this + 0x114) = *(uint *)(this + 0x118);
    pvVar5 = operator_new__((ulong)*(uint *)(this + 0x118) << 3);
    *(void **)(this + 0x108) = pvVar5;
    uVar3 = *(uint *)(this + 0x110);
  }
  else {
    uVar4 = *(uint *)(this + 0x114) + *(int *)(this + 0x118);
    pvVar5 = operator_new__((ulong)uVar4 << 3);
    if (*(int *)(this + 0x114) != 0) {
      uVar3 = 0;
      do {
        uVar7 = (ulong)uVar3;
        uVar3 = uVar3 + 1;
        *(undefined8 *)((long)pvVar5 + uVar7 * 8) =
             *(undefined8 *)(*(long *)(this + 0x108) + uVar7 * 8);
      } while (uVar3 < *(uint *)(this + 0x114));
    }
    if (*(void **)(this + 0x108) != (void *)0x0) {
      operator_delete__(*(void **)(this + 0x108));
    }
    uVar3 = *(uint *)(this + 0x110);
    *(void **)(this + 0x108) = pvVar5;
    *(uint *)(this + 0x114) = uVar4;
  }
  *(CUnitTheme **)((long)pvVar5 + (ulong)uVar3 * 8) = param_1;
  uVar3 = *(uint *)(this + 0x140);
  *(int *)(this + 0x110) = *(int *)(this + 0x110) + 1;
  if (uVar3 < *(uint *)(this + 0x144)) {
    pvVar5 = *(void **)(this + 0x138);
  }
  else if (*(long *)(this + 0x138) == 0) {
    *(uint *)(this + 0x144) = *(uint *)(this + 0x148);
    pvVar5 = operator_new__((ulong)*(uint *)(this + 0x148) << 3);
    *(void **)(this + 0x138) = pvVar5;
    uVar3 = *(uint *)(this + 0x140);
  }
  else {
    uVar4 = *(uint *)(this + 0x144) + *(int *)(this + 0x148);
    pvVar5 = operator_new__((ulong)uVar4 << 3);
    if (*(int *)(this + 0x144) != 0) {
      uVar3 = 0;
      do {
        uVar7 = (ulong)uVar3;
        uVar3 = uVar3 + 1;
        *(undefined8 *)((long)pvVar5 + uVar7 * 8) =
             *(undefined8 *)(*(long *)(this + 0x138) + uVar7 * 8);
      } while (uVar3 < *(uint *)(this + 0x144));
    }
    if (*(void **)(this + 0x138) != (void *)0x0) {
      operator_delete__(*(void **)(this + 0x138));
    }
    uVar3 = *(uint *)(this + 0x140);
    *(void **)(this + 0x138) = pvVar5;
    *(uint *)(this + 0x144) = uVar4;
  }
  *(CUnitTheme **)((long)pvVar5 + (ulong)uVar3 * 8) = param_1;
  *(int *)(this + 0x140) = *(int *)(this + 0x140) + 1;
  return;
}



/* address=00800ca0
   symbol=CBaseUnit::setEditorThemeID */

/* CBaseUnit::setEditorThemeID(unsigned int) */

void __thiscall CBaseUnit::setEditorThemeID(CBaseUnit *this,uint param_1)

{
  char cVar1;
  long lVar2;
  undefined8 *puVar3;
  uint uVar4;

  cVar1 = CResourceManager::getEditorIsRunning();
  if (cVar1 != '\0') {
    *(uint *)(this + 0x168) = param_1;
    lVar2 = CUnitThemes::getSingleton();
    if (*(int *)(lVar2 + 0x20) != 0) {
      uVar4 = 1;
      do {
        if (uVar4 == param_1) {
          if (param_1 - 1 < *(uint *)(lVar2 + 0x24)) {
            puVar3 = (undefined8 *)((ulong)(param_1 - 1) * 8 + *(long *)(lVar2 + 0x18));
          }
          else {
            puVar3 = *(undefined8 **)(lVar2 + 0x18);
          }
          addUnitTheme(this,(CUnitTheme *)*puVar3);
        }
        else {
          if (uVar4 - 1 < *(uint *)(lVar2 + 0x24)) {
            puVar3 = (undefined8 *)((ulong)(uVar4 - 1) * 8 + *(long *)(lVar2 + 0x18));
          }
          else {
            puVar3 = *(undefined8 **)(lVar2 + 0x18);
          }
          removeUnitTheme(this,(CUnitTheme *)*puVar3);
        }
        uVar4 = uVar4 + 1;
      } while (uVar4 <= *(uint *)(lVar2 + 0x20));
    }
  }
  return;
}



/* address=00800d90
   symbol=CBaseUnit::addUnitTheme */

/* CBaseUnit::addUnitTheme(std::wstring const&) */

void __thiscall CBaseUnit::addUnitTheme(CBaseUnit *this,wstring_conflict *param_1)

{
  uint uVar1;
  uint uVar2;
  wchar_t *__s2;
  size_t __n;
  wchar_t *__s1;
  size_t sVar3;
  int iVar4;
  long lVar5;
  uint uVar6;
  undefined8 *puVar7;
  long lVar8;
  CUnitTheme *pCVar9;

  lVar5 = CUnitThemes::getSingleton();
  if (lVar5 == 0) {
    return;
  }
  uVar1 = *(uint *)(lVar5 + 0x20);
  if (uVar1 != 0) {
    __s2 = *(wchar_t **)param_1;
    uVar2 = *(uint *)(lVar5 + 0x24);
    lVar8 = 0;
    uVar6 = 0;
    __n = *(size_t *)(__s2 + -6);
    do {
      if (uVar6 < uVar2) {
        __s1 = *(wchar_t **)(*(long *)(lVar8 + *(long *)(lVar5 + 0x18)) + 0x28);
        sVar3 = *(size_t *)(__s1 + -6);
      }
      else {
        __s1 = *(wchar_t **)(**(long **)(lVar5 + 0x18) + 0x28);
        sVar3 = *(size_t *)(__s1 + -6);
      }
      if ((sVar3 == __n) && (iVar4 = wmemcmp(__s1,__s2,__n), iVar4 == 0)) {
        if (uVar6 < uVar2) {
          puVar7 = (undefined8 *)((ulong)uVar6 * 8 + *(long *)(lVar5 + 0x18));
        }
        else {
          puVar7 = *(undefined8 **)(lVar5 + 0x18);
        }
        pCVar9 = (CUnitTheme *)*puVar7;
        goto LAB_00800e52;
      }
      uVar6 = uVar6 + 1;
      lVar8 = lVar8 + 8;
    } while (uVar6 < uVar1);
  }
  pCVar9 = (CUnitTheme *)0x0;
LAB_00800e52:
  addUnitTheme(this,pCVar9);
  return;
}



/* address=00800e80
   symbol=CBaseUnit::selectRandomSkill */

/* CBaseUnit::selectRandomSkill() */

undefined4 __thiscall CBaseUnit::selectRandomSkill(CBaseUnit *this)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined **local_88 [2];
  void *local_78;
  void *local_60;
  void *local_48;

  if (*(CSkillManager **)(this + 0x1c8) != (CSkillManager *)0x0) {
    uVar2 = 0xffffffff;
    iVar1 = CSkillManager::knownSkills(*(CSkillManager **)(this + 0x1c8),0);
    if (0 < iVar1) {
      iVar3 = 0;
      CRandomizer::CRandomizer((CRandomizer *)local_88,0);
      do {
                    /* try { // try from 00800eca to 00800edd has its CatchHandler @ 00800f58 */
        CRandomizer::addChoice((CRandomizer *)local_88,iVar3,1);
        iVar3 = iVar3 + 1;
      } while (iVar3 < iVar1);
      uVar2 = CRandomizer::getRandom((CRandomizer *)local_88);
      local_88[0] = &PTR__CRandomizer_00fc8a30;
      if (local_48 != (void *)0x0) {
        operator_delete__(local_48);
        local_48 = (void *)0x0;
      }
      if (local_60 != (void *)0x0) {
        operator_delete__(local_60);
        local_60 = (void *)0x0;
      }
      if (local_78 != (void *)0x0) {
        operator_delete__(local_78);
        local_78 = (void *)0x0;
      }
      CRunicCore::~CRunicCore((CRunicCore *)local_88);
    }
    return uVar2;
  }
  return 0xffffffff;
}



/* address=00800f70
   symbol=CBaseUnit::rayCollision */

/* CBaseUnit::rayCollision(Ogre::Vector3 const&, Ogre::Vector3 const&, Ogre::Vector3&,
   Ogre::Vector3&, bool) */

undefined8 __thiscall
CBaseUnit::rayCollision
          (CBaseUnit *this,Vector3 *param_1,Vector3 *param_2,Vector3 *param_3,Vector3 *param_4,
          bool param_5)

{
  char cVar1;
  long lVar2;
  Vector3 *pVVar3;
  Vector3 *pVVar4;
  Matrix3 *pMVar5;
  CPositionableObject *this_00;
  undefined8 uVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float local_168;
  float local_164;
  float local_160;
  float local_15c;
  float local_158;
  float local_154;
  float local_150;
  float local_14c;
  float local_148;
  float local_144;
  float local_140;
  float local_13c;
  float local_138;
  float local_134;
  float local_130;
  float local_12c;
  undefined4 local_128;
  undefined4 local_124;
  undefined4 local_120;
  undefined4 uStack_11c;
  undefined4 local_118;
  undefined4 local_114;
  undefined4 local_110;
  undefined4 uStack_10c;
  undefined4 local_108;
  undefined4 local_104;
  undefined4 local_100;
  undefined4 uStack_fc;
  undefined8 local_f8;
  undefined8 local_f0;
  undefined4 local_e8;
  undefined4 local_e4;
  undefined4 local_e0;
  undefined4 local_dc;
  undefined4 local_d8;
  undefined4 local_d4;
  undefined4 local_d0;
  undefined4 local_cc;
  undefined4 local_c8;
  undefined4 local_b8;
  undefined4 uStack_b4;
  undefined8 local_a8;
  float local_a0;
  undefined8 local_98;
  float local_90;
  undefined8 local_88;
  float local_80;
  float local_78;
  float local_74;
  float local_70;
  float local_68;
  float local_64;
  float local_60;
  undefined8 local_58;
  undefined4 local_50;
  undefined8 local_48;
  undefined4 local_40;
  float local_3c [3];

  lVar2 = (**(code **)(*(long *)this + 0x1e8))();
  if ((lVar2 != 0) &&
     (((this[0x18d] != (CBaseUnit)0x0 && (this[0x19c] != (CBaseUnit)0x0)) || (param_5)))) {
    local_58 = *(undefined8 *)param_1;
    fVar7 = *(float *)(param_2 + 8);
    local_50 = *(undefined4 *)(param_1 + 8);
    local_3c[0] = 99999.0;
    local_48 = local_58;
    local_40 = local_50;
    MATH::expandBounds(*(MATH **)param_2,(Vector3 *)&local_48,(Vector3 *)&local_58);
    pVVar3 = (Vector3 *)(**(code **)(*(long *)this + 0x220))(this);
    pVVar4 = (Vector3 *)(**(code **)(*(long *)this + 0x218))(this);
    cVar1 = MATH::boundsIntersect(pVVar4,pVVar3,(Vector3 *)&local_48,(Vector3 *)&local_58);
    if (cVar1 != '\0') {
      pMVar5 = (Matrix3 *)(**(code **)(**(long **)(this + 0x58) + 0x1f8))();
      Ogre::Quaternion::ToRotationMatrix(pMVar5);
      local_f8 = DAT_01423ff0;
      local_f0 = DAT_01423ff8;
      local_128 = local_e8;
      local_124 = local_e4;
      _local_120 = CONCAT44((int)((ulong)DAT_01423fc8 >> 0x20),local_e0);
      local_118 = local_dc;
      local_114 = local_d8;
      _local_110 = CONCAT44((int)((ulong)DAT_01423fd8 >> 0x20),local_d4);
      local_108 = local_d0;
      local_104 = local_cc;
      _local_100 = CONCAT44((int)((ulong)DAT_01423fe8 >> 0x20),local_c8);
      Ogre::Matrix4::inverse();
      lVar2 = (**(code **)(*(long *)this + 0x1e0))(this);
      fVar9 = Ogre::Vector3::ZERO;
      fVar11 = DAT_014241b0;
      fVar13 = DAT_014241b4;
      if (lVar2 != 0) {
        this_00 = (CPositionableObject *)(**(code **)(*(long *)this + 0x1e0))(this);
        uVar6 = CPositionableObject::getPosition(this_00,false);
        local_98._0_4_ = (float)uVar6;
        local_98._4_4_ = (float)((ulong)uVar6 >> 0x20);
        fVar9 = (float)local_98;
        fVar11 = local_98._4_4_;
        fVar13 = fVar7;
        local_98 = uVar6;
        local_90 = fVar7;
      }
      uVar6 = CPositionableObject::getPosition((CPositionableObject *)this,true);
      local_88._4_4_ = (float)((ulong)uVar6 >> 0x20);
      fVar11 = fVar11 + local_88._4_4_;
      local_88._0_4_ = (float)uVar6;
      fVar9 = fVar9 + (float)local_88;
      fVar13 = fVar13 + fVar7;
      fVar15 = *(float *)(param_1 + 4) - fVar11;
      fVar16 = *(float *)param_1 - fVar9;
      fVar14 = *(float *)(param_1 + 8) - fVar13;
      fVar10 = *(float *)(param_2 + 4) - fVar11;
      fVar8 = *(float *)(param_2 + 8) - fVar13;
      fVar12 = *(float *)param_2 - fVar9;
      local_60 = DAT_00fa47fc /
                 (fVar16 * local_138 + fVar15 * local_134 + fVar14 * local_130 + local_12c);
      local_68 = (fVar16 * local_168 + fVar15 * local_164 + fVar14 * local_160 + local_15c) *
                 local_60;
      local_70 = DAT_00fa47fc /
                 (local_138 * fVar12 + local_134 * fVar10 + local_130 * fVar8 + local_12c);
      local_78 = (local_168 * fVar12 + local_164 * fVar10 + local_160 * fVar8 + local_15c) *
                 local_70;
      local_64 = (local_158 * fVar16 + local_154 * fVar15 + local_150 * fVar14 + local_14c) *
                 local_60;
      local_60 = (fVar16 * local_148 + fVar15 * local_144 + fVar14 * local_140 + local_13c) *
                 local_60;
      fVar14 = fVar8 * local_140;
      local_74 = (local_158 * fVar12 + local_154 * fVar10 + local_150 * fVar8 + local_14c) *
                 local_70;
      local_70 = (fVar12 * local_148 + fVar10 * local_144 + fVar14 + local_13c) * local_70;
      local_88 = uVar6;
      local_80 = fVar7;
      lVar2 = (**(code **)(*(long *)this + 0x1e8))(this);
      cVar1 = CCollisionList::rayCollision
                        (*(CCollisionList **)(lVar2 + 0x38),(Vector3 *)&local_68,
                         (Vector3 *)&local_78,param_3,param_4,local_3c);
      if (cVar1 != '\0') {
        uVar6 = Ogre::Matrix4::operator*((Matrix4 *)&local_128,param_3);
        local_a8._0_4_ = (undefined4)uVar6;
        *(undefined4 *)param_3 = (undefined4)local_a8;
        local_a8._4_4_ = (undefined4)((ulong)uVar6 >> 0x20);
        *(undefined4 *)(param_3 + 4) = local_a8._4_4_;
        *(float *)(param_3 + 8) = fVar14;
        local_a8 = uVar6;
        local_a0 = fVar14;
        uVar6 = Ogre::Matrix4::operator*((Matrix4 *)&local_128,param_4);
        local_b8 = (undefined4)uVar6;
        *(undefined4 *)param_4 = local_b8;
        uStack_b4 = (undefined4)((ulong)uVar6 >> 0x20);
        *(undefined4 *)(param_4 + 4) = uStack_b4;
        *(float *)(param_4 + 8) = fVar14;
        *(float *)param_3 = fVar9 + *(float *)param_3;
        *(float *)(param_3 + 4) = fVar11 + *(float *)(param_3 + 4);
        *(float *)(param_3 + 8) = fVar13 + *(float *)(param_3 + 8);
        return 1;
      }
    }
  }
  return 0;
}



/* address=00801610
   symbol=CBaseUnit::sphereCollision */

/* CBaseUnit::sphereCollision(Ogre::Vector3 const&, Ogre::Vector3 const&, float, Ogre::Vector3&,
   Ogre::Vector3&, Ogre::Vector3&) */

undefined8 __thiscall
CBaseUnit::sphereCollision
          (CBaseUnit *this,Vector3 *param_1,Vector3 *param_2,float param_3,Vector3 *param_4,
          Vector3 *param_5,Vector3 *param_6)

{
  char cVar1;
  long lVar2;
  Vector3 *pVVar3;
  Vector3 *pVVar4;
  Matrix3 *pMVar5;
  CPositionableObject *this_00;
  float fVar6;
  undefined8 uVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float local_178;
  float local_174;
  float local_170;
  float local_16c;
  float local_168;
  float local_164;
  float local_160;
  float local_15c;
  float local_158;
  float local_154;
  float local_150;
  float local_14c;
  float local_148;
  float local_144;
  float local_140;
  float local_13c;
  undefined4 local_138;
  undefined4 local_134;
  undefined4 local_130;
  undefined4 uStack_12c;
  undefined4 local_128;
  undefined4 local_124;
  undefined4 local_120;
  undefined4 uStack_11c;
  undefined4 local_118;
  undefined4 local_114;
  undefined4 local_110;
  undefined4 uStack_10c;
  undefined8 local_108;
  undefined8 local_100;
  undefined4 local_f8;
  undefined4 local_f4;
  undefined4 local_f0;
  undefined4 local_ec;
  undefined4 local_e8;
  undefined4 local_e4;
  undefined4 local_e0;
  undefined4 local_dc;
  undefined4 local_d8;
  undefined4 local_c8;
  undefined4 uStack_c4;
  undefined8 local_b8;
  float local_b0;
  undefined8 local_a8;
  float local_a0;
  undefined8 local_98;
  float local_90;
  undefined8 local_88;
  float local_80;
  float local_78;
  float local_74;
  float local_70;
  float local_68;
  float local_64;
  float local_60;
  undefined8 local_58;
  float local_50;
  undefined8 local_48;
  float local_40;
  float local_3c [3];

  lVar2 = (**(code **)(*(long *)this + 0x1e8))();
  if (((lVar2 != 0) && (this[0x18d] != (CBaseUnit)0x0)) && (this[0x19c] != (CBaseUnit)0x0)) {
    local_58 = *(undefined8 *)param_1;
    local_50 = *(float *)(param_1 + 8);
    local_3c[0] = 99999.0;
    local_48 = local_58;
    local_40 = local_50;
    MATH::expandBounds(*(MATH **)param_2,*(undefined4 *)(param_2 + 8),(Vector3 *)&local_48,
                       (Vector3 *)&local_58);
    fVar6 = param_3 * DAT_00fc4568;
    local_40 = fVar6 + local_40;
    local_48 = CONCAT44(local_48._4_4_ + fVar6,(float)local_48 + fVar6);
    fVar6 = param_3 + param_3;
    fVar8 = local_58._4_4_ + fVar6;
    local_50 = fVar6 + local_50;
    local_58 = CONCAT44(fVar8,(float)local_58 + fVar6);
    pVVar3 = (Vector3 *)(**(code **)(*(long *)this + 0x220))(this);
    pVVar4 = (Vector3 *)(**(code **)(*(long *)this + 0x218))(this);
    cVar1 = MATH::boundsIntersect(pVVar4,pVVar3,(Vector3 *)&local_48,(Vector3 *)&local_58);
    if (cVar1 != '\0') {
      pMVar5 = (Matrix3 *)(**(code **)(**(long **)(this + 0x58) + 0x1f8))();
      Ogre::Quaternion::ToRotationMatrix(pMVar5);
      local_108 = DAT_01423ff0;
      local_100 = DAT_01423ff8;
      local_138 = local_f8;
      local_134 = local_f4;
      _local_130 = CONCAT44((int)((ulong)DAT_01423fc8 >> 0x20),local_f0);
      local_128 = local_ec;
      local_124 = local_e8;
      _local_120 = CONCAT44((int)((ulong)DAT_01423fd8 >> 0x20),local_e4);
      local_118 = local_e0;
      local_114 = local_dc;
      _local_110 = CONCAT44((int)((ulong)DAT_01423fe8 >> 0x20),local_d8);
      Ogre::Matrix4::inverse();
      lVar2 = (**(code **)(*(long *)this + 0x1e0))(this);
      fVar6 = Ogre::Vector3::ZERO;
      fVar11 = DAT_014241b0;
      fVar13 = DAT_014241b4;
      if (lVar2 != 0) {
        this_00 = (CPositionableObject *)(**(code **)(*(long *)this + 0x1e0))(this);
        uVar7 = CPositionableObject::getPosition(this_00,false);
        local_98._0_4_ = (float)uVar7;
        local_98._4_4_ = (float)((ulong)uVar7 >> 0x20);
        fVar6 = (float)local_98;
        fVar11 = local_98._4_4_;
        fVar13 = fVar8;
        local_98 = uVar7;
        local_90 = fVar8;
      }
      uVar7 = CPositionableObject::getPosition((CPositionableObject *)this,true);
      local_88._4_4_ = (float)((ulong)uVar7 >> 0x20);
      fVar11 = fVar11 + local_88._4_4_;
      local_88._0_4_ = (float)uVar7;
      fVar6 = fVar6 + (float)local_88;
      fVar13 = fVar13 + fVar8;
      fVar15 = *(float *)(param_1 + 4) - fVar11;
      fVar16 = *(float *)param_1 - fVar6;
      fVar14 = *(float *)(param_1 + 8) - fVar13;
      fVar10 = *(float *)(param_2 + 4) - fVar11;
      fVar9 = *(float *)(param_2 + 8) - fVar13;
      fVar12 = *(float *)param_2 - fVar6;
      local_60 = DAT_00fa47fc /
                 (fVar16 * local_148 + fVar15 * local_144 + fVar14 * local_140 + local_13c);
      local_68 = (fVar16 * local_178 + fVar15 * local_174 + fVar14 * local_170 + local_16c) *
                 local_60;
      local_70 = DAT_00fa47fc /
                 (local_148 * fVar12 + local_144 * fVar10 + local_140 * fVar9 + local_13c);
      local_78 = (local_178 * fVar12 + local_174 * fVar10 + local_170 * fVar9 + local_16c) *
                 local_70;
      local_64 = (local_168 * fVar16 + local_164 * fVar15 + local_160 * fVar14 + local_15c) *
                 local_60;
      local_60 = (fVar16 * local_158 + fVar15 * local_154 + fVar14 * local_150 + local_14c) *
                 local_60;
      fVar14 = fVar9 * local_150;
      local_74 = (local_168 * fVar12 + local_164 * fVar10 + local_160 * fVar9 + local_15c) *
                 local_70;
      local_70 = (fVar12 * local_158 + fVar10 * local_154 + fVar14 + local_14c) * local_70;
      local_88 = uVar7;
      local_80 = fVar8;
      lVar2 = (**(code **)(*(long *)this + 0x1e8))(this);
      cVar1 = CCollisionList::sphereCollision
                        (*(CCollisionList **)(lVar2 + 0x38),(Vector3 *)&local_68,
                         (Vector3 *)&local_78,param_3,param_4,param_5,param_6,local_3c);
      if (cVar1 != '\0') {
        uVar7 = Ogre::Matrix4::operator*((Matrix4 *)&local_138,param_5);
        local_a8._0_4_ = (undefined4)uVar7;
        *(undefined4 *)param_5 = (undefined4)local_a8;
        local_a8._4_4_ = (undefined4)((ulong)uVar7 >> 0x20);
        *(undefined4 *)(param_5 + 4) = local_a8._4_4_;
        *(float *)(param_5 + 8) = fVar14;
        local_a8 = uVar7;
        local_a0 = fVar14;
        uVar7 = Ogre::Matrix4::operator*((Matrix4 *)&local_138,param_6);
        local_b8._0_4_ = (undefined4)uVar7;
        *(undefined4 *)param_6 = (undefined4)local_b8;
        local_b8._4_4_ = (undefined4)((ulong)uVar7 >> 0x20);
        *(undefined4 *)(param_6 + 4) = local_b8._4_4_;
        *(float *)(param_6 + 8) = fVar14;
        local_b8 = uVar7;
        local_b0 = fVar14;
        uVar7 = Ogre::Matrix4::operator*((Matrix4 *)&local_138,param_4);
        local_c8 = (undefined4)uVar7;
        *(undefined4 *)param_4 = local_c8;
        uStack_c4 = (undefined4)((ulong)uVar7 >> 0x20);
        *(undefined4 *)(param_4 + 4) = uStack_c4;
        *(float *)(param_4 + 8) = fVar14;
        *(float *)param_5 = fVar6 + *(float *)param_5;
        *(float *)(param_5 + 4) = fVar11 + *(float *)(param_5 + 4);
        *(float *)(param_5 + 8) = fVar13 + *(float *)(param_5 + 8);
        *(float *)param_4 = fVar6 + *(float *)param_4;
        *(float *)(param_4 + 4) = fVar11 + *(float *)(param_4 + 4);
        *(float *)(param_4 + 8) = fVar13 + *(float *)(param_4 + 8);
        return 1;
      }
    }
  }
  return 0;
}



/* address=008029d0
   symbol=CBaseUnit::getUnitDataName */

/* WARNING: Removing unreachable block (ram,0x00802a96) */
/* CBaseUnit::getUnitDataName() */

void CBaseUnit::getUnitDataName(void)

{
  int *piVar1;
  int iVar2;
  wstring_conflict *pwVar3;
  long in_RSI;
  wstring_conflict *in_RDI;
  long local_28;
  allocator local_19;

  if (*(long *)(in_RSI + 0x1b0) == 0) {
    std::wstring::wstring(in_RDI,(wstring_conflict *)&::EMPTY_WSTRING);
  }
  else {
                    /* try { // try from 00802a00 to 00802a04 has its CatchHandler @ 00802a91 */
    std::wstring::wstring((wstring_conflict *)&local_28,L"NAME",&local_19);
                    /* try { // try from 00802a14 to 00802a23 has its CatchHandler @ 00802a7e */
    pwVar3 = (wstring_conflict *)
             CDataGroup::GetDataValue
                       (*(CDataGroup **)(in_RSI + 0x1b0),(wstring_conflict *)&local_28,
                        (wstring_conflict *)&::EMPTY_WSTRING);
    std::wstring::wstring(in_RDI,pwVar3);
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
  }
  return;
}



/* address=00802ab0
   symbol=CBaseUnit::reapplyEffects */

/* WARNING: Removing unreachable block (ram,0x00802c6f) */
/* WARNING: Removing unreachable block (ram,0x00802c8b) */
/* CBaseUnit::reapplyEffects(bool) */

void __thiscall CBaseUnit::reapplyEffects(CBaseUnit *this,bool param_1)

{
  int *piVar1;
  int iVar2;
  CDataGroup *pCVar3;
  long lVar4;
  CEffectManager *this_00;
  long local_48 [2];
  long local_38;
  allocator local_2a;
  allocator local_29 [9];

  if (*(long *)(this + 0x1b0) != 0) {
                    /* try { // try from 00802aee to 00802af2 has its CatchHandler @ 00802c57 */
    std::wstring::wstring((wstring_conflict *)&local_38,L"EFFECTS",local_29);
                    /* try { // try from 00802aff to 00802b03 has its CatchHandler @ 00802c62 */
    pCVar3 = (CDataGroup *)
             CDataGroup::GetDataGroupByName
                       (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)&local_38,false);
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
                    /* try { // try from 00802b2f to 00802b33 has its CatchHandler @ 00802c7c */
    std::wstring::wstring((wstring_conflict *)local_48,L"EFFECT",&local_2a);
                    /* try { // try from 00802b40 to 00802b44 has its CatchHandler @ 00802c7a */
    lVar4 = CDataGroup::GetDataGroupByName
                      (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_48,false);
    if ((allocator *)(local_48[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_48[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
      }
    }
    if ((lVar4 != 0) || (pCVar3 != (CDataGroup *)0x0)) {
      this_00 = *(CEffectManager **)(this + 0x1b8);
      if (this_00 == (CEffectManager *)0x0) {
        this_00 = (CEffectManager *)Ogre::NedAllocImpl::allocBytes(0x2f8,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00802be4 to 00802be8 has its CatchHandler @ 00802c7e */
        CEffectManager::CEffectManager(this_00,this);
        *(CEffectManager **)(this + 0x1b8) = this_00;
        param_1 = false;
      }
      if (pCVar3 == (CDataGroup *)0x0) {
        CEffectManager::createEffects(this_00,*(CDataGroup **)(this + 0x1b0),param_1);
      }
      else {
        CEffectManager::createEffects(this_00,pCVar3,param_1);
      }
    }
  }
  return;
}



/* address=00802ca0
   symbol=CBaseUnit::unitInitThemes */

/* WARNING: Removing unreachable block (ram,0x00802e25) */
/* WARNING: Removing unreachable block (ram,0x00802e1a) */
/* CBaseUnit::unitInitThemes() */

void __thiscall CBaseUnit::unitInitThemes(CBaseUnit *this)

{
  int *piVar1;
  int iVar2;
  long lVar3;
  wstring_conflict *pwVar4;
  long *plVar5;
  undefined8 *puVar6;
  uint uVar7;
  long local_58 [2];
  long local_48;
  allocator local_39 [9];

  if (*(long *)(this + 0x1b0) != 0) {
                    /* try { // try from 00802cd1 to 00802cd5 has its CatchHandler @ 00802dec */
    std::wstring::wstring((wstring_conflict *)&local_48,L"THEMES",local_39);
                    /* try { // try from 00802ce2 to 00802ce6 has its CatchHandler @ 00802ddf */
    lVar3 = CDataGroup::GetDataGroupByName
                      (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)&local_48,false);
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
    if ((lVar3 != 0) && (*(int *)(lVar3 + 0x28) != 0)) {
      uVar7 = 0;
      do {
        if (uVar7 < *(uint *)(lVar3 + 0x2c)) {
          plVar5 = (long *)((ulong)uVar7 * 8 + *(long *)(lVar3 + 0x20));
        }
        else {
          plVar5 = *(long **)(lVar3 + 0x20);
        }
        if ((*(int *)(*plVar5 + 0x30) == 8) || (*(int *)(*plVar5 + 0x30) == 5)) {
          if (uVar7 < *(uint *)(lVar3 + 0x2c)) {
            puVar6 = (undefined8 *)((ulong)uVar7 * 8 + *(long *)(lVar3 + 0x20));
          }
          else {
            puVar6 = *(undefined8 **)(lVar3 + 0x20);
          }
          pwVar4 = (wstring_conflict *)CDataValue::GetValueString((CDataValue *)*puVar6,true);
          STRINGS::StringUpper((STRINGS *)local_58,pwVar4);
                    /* try { // try from 00802d62 to 00802d66 has its CatchHandler @ 00802dcc */
          addUnitTheme(this,(wstring_conflict *)local_58);
          if ((allocator *)(local_58[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_58[0] + -8);
            iVar2 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar2 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
            }
          }
        }
        uVar7 = uVar7 + 1;
      } while (uVar7 < *(uint *)(lVar3 + 0x28));
    }
  }
  return;
}



/* address=00802e30
   symbol=CBaseUnit::reapplyAffixes */

/* WARNING: Removing unreachable block (ram,0x008030cd) */
/* WARNING: Removing unreachable block (ram,0x00803097) */
/* WARNING: Removing unreachable block (ram,0x008030f2) */
/* CBaseUnit::reapplyAffixes(bool) */

void __thiscall CBaseUnit::reapplyAffixes(CBaseUnit *this,bool param_1)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  long lVar4;
  long lVar5;
  wstring_conflict *pwVar6;
  undefined8 *puVar7;
  CEffectManager *this_00;
  uint uVar8;
  long local_68 [2];
  long local_58 [2];
  long local_48;
  allocator local_3a;
  allocator local_39 [9];

  if (*(long *)(this + 0x1b0) != 0) {
                    /* try { // try from 00802e64 to 00802e68 has its CatchHandler @ 00803095 */
    std::wstring::wstring((wstring_conflict *)&local_48,L"AFFIXES",local_39);
                    /* try { // try from 00802e76 to 00802e7a has its CatchHandler @ 00803088 */
    lVar4 = CDataGroup::GetDataGroupByName
                      (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)&local_48,false);
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
      if (*(long *)(this + 0x1b8) == 0) {
        this_00 = (CEffectManager *)Ogre::NedAllocImpl::allocBytes(0x2f8,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00803005 to 00803009 has its CatchHandler @ 00803047 */
        CEffectManager::CEffectManager(this_00,this);
        *(CEffectManager **)(this + 0x1b8) = this_00;
        param_1 = false;
      }
      iVar2 = *(int *)(this + 0x100);
                    /* try { // try from 00802ec6 to 00802eca has its CatchHandler @ 0080305a */
      std::wstring::wstring((wstring_conflict *)local_58,L"LEVEL",&local_3a);
                    /* try { // try from 00802ed9 to 00802edd has its CatchHandler @ 008030cb */
      uVar3 = CDataGroup::GetDataValue
                        (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_58,iVar2);
      if ((allocator *)(local_58[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_58[0] + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
        }
      }
      if (*(int *)(lVar4 + 0x28) != 0) {
        uVar8 = 0;
        do {
          while (param_1 != false) {
            if (uVar8 < *(uint *)(lVar4 + 0x2c)) {
              puVar7 = (undefined8 *)((ulong)uVar8 * 8 + *(long *)(lVar4 + 0x20));
            }
            else {
              puVar7 = *(undefined8 **)(lVar4 + 0x20);
            }
                    /* try { // try from 00802f25 to 00802f4a has its CatchHandler @ 008030d8 */
            pwVar6 = (wstring_conflict *)CDataValue::GetValueString((CDataValue *)*puVar7,true);
            STRINGS::StringUpper((STRINGS *)local_68,pwVar6);
            lVar5 = CEffectManager::getAffix
                              (*(CEffectManager **)(this + 0x1b8),(wstring_conflict *)local_68);
            if ((allocator *)(local_68[0] + -0x18) !=
                (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar1 = (int *)(local_68[0] + -8);
              iVar2 = *piVar1;
              *piVar1 = *piVar1 + -1;
              UNLOCK();
              if (iVar2 < 1) {
                std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
              }
            }
            if (lVar5 == 0) break;
            uVar8 = uVar8 + 1;
            if (*(uint *)(lVar4 + 0x28) <= uVar8) {
              return;
            }
          }
          if (uVar8 < *(uint *)(lVar4 + 0x2c)) {
            puVar7 = (undefined8 *)((ulong)uVar8 * 8 + *(long *)(lVar4 + 0x20));
          }
          else {
            puVar7 = *(undefined8 **)(lVar4 + 0x20);
          }
          uVar8 = uVar8 + 1;
          pwVar6 = (wstring_conflict *)CDataValue::GetValueString((CDataValue *)*puVar7,true);
          addAffix(this,pwVar6,uVar3,this,DAT_00fa8760);
        } while (uVar8 < *(uint *)(lVar4 + 0x28));
      }
    }
  }
  return;
}



/* address=00803100
   symbol=CBaseUnit::unitInit */

/* WARNING: Removing unreachable block (ram,0x008045fd) */
/* WARNING: Removing unreachable block (ram,0x00804aba) */
/* WARNING: Removing unreachable block (ram,0x00804a9e) */
/* WARNING: Removing unreachable block (ram,0x00804af2) */
/* WARNING: Removing unreachable block (ram,0x00804b00) */
/* WARNING: Removing unreachable block (ram,0x00804c75) */
/* WARNING: Removing unreachable block (ram,0x00804ad6) */
/* WARNING: Removing unreachable block (ram,0x00804ac8) */
/* WARNING: Removing unreachable block (ram,0x00804b1c) */
/* WARNING: Removing unreachable block (ram,0x00804a12) */
/* WARNING: Removing unreachable block (ram,0x00804a2e) */
/* WARNING: Removing unreachable block (ram,0x00804a4a) */
/* WARNING: Removing unreachable block (ram,0x00804a66) */
/* WARNING: Removing unreachable block (ram,0x008049da) */
/* WARNING: Removing unreachable block (ram,0x008049f6) */
/* WARNING: Removing unreachable block (ram,0x008049be) */
/* WARNING: Removing unreachable block (ram,0x008049b0) */
/* WARNING: Removing unreachable block (ram,0x00804788) */
/* WARNING: Removing unreachable block (ram,0x008048e0) */
/* WARNING: Removing unreachable block (ram,0x00804d32) */
/* WARNING: Removing unreachable block (ram,0x00804c5e) */
/* WARNING: Removing unreachable block (ram,0x00804927) */
/* WARNING: Removing unreachable block (ram,0x00804995) */
/* WARNING: Removing unreachable block (ram,0x00804d24) */
/* WARNING: Removing unreachable block (ram,0x00804820) */
/* WARNING: Removing unreachable block (ram,0x008048d0) */
/* WARNING: Removing unreachable block (ram,0x0080485f) */
/* WARNING: Removing unreachable block (ram,0x00804b2a) */
/* WARNING: Removing unreachable block (ram,0x008049cc) */
/* WARNING: Removing unreachable block (ram,0x00804a04) */
/* WARNING: Removing unreachable block (ram,0x008049e8) */
/* WARNING: Removing unreachable block (ram,0x00804a74) */
/* WARNING: Removing unreachable block (ram,0x00804a58) */
/* WARNING: Removing unreachable block (ram,0x00804a3c) */
/* WARNING: Removing unreachable block (ram,0x00804a20) */
/* WARNING: Removing unreachable block (ram,0x00804b0e) */
/* WARNING: Removing unreachable block (ram,0x00804ae4) */
/* WARNING: Removing unreachable block (ram,0x00804a90) */
/* WARNING: Removing unreachable block (ram,0x00804a82) */
/* WARNING: Removing unreachable block (ram,0x00804ca1) */
/* WARNING: Removing unreachable block (ram,0x00804c93) */
/* WARNING: Removing unreachable block (ram,0x00804c85) */
/* WARNING: Removing unreachable block (ram,0x008045b8) */
/* WARNING: Removing unreachable block (ram,0x00804b38) */
/* WARNING: Removing unreachable block (ram,0x008045ef) */
/* WARNING: Removing unreachable block (ram,0x00804aac) */
/* WARNING: Removing unreachable block (ram,0x00804b54) */
/* WARNING: Removing unreachable block (ram,0x00804b46) */
/* WARNING: Removing unreachable block (ram,0x008049a2) */
/* CBaseUnit::unitInit(CDataGroup*, bool) */

void __thiscall CBaseUnit::unitInit(CBaseUnit *this,CDataGroup *param_1,bool param_2)

{
  int *piVar1;
  wchar_t *pwVar2;
  wchar_t wVar3;
  code *pcVar4;
  CDataGroup *this_00;
  bool bVar5;
  CBaseUnit CVar6;
  undefined1 uVar7;
  char cVar8;
  undefined4 uVar9;
  uint uVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  int iVar13;
  undefined4 uVar14;
  undefined4 uVar15;
  undefined4 uVar16;
  undefined4 uVar17;
  undefined8 uVar18;
  wstring_conflict *pwVar19;
  long lVar20;
  CGameClient *this_01;
  float fVar21;
  float fVar22;
  long local_388;
  uint local_380;
  void *local_358;
  undefined8 local_350;
  undefined8 local_348;
  long local_338 [2];
  long local_328 [2];
  long local_318 [2];
  long local_308 [2];
  long local_2f8 [2];
  long local_2e8 [2];
  long local_2d8 [2];
  long local_2c8 [2];
  wchar_t *local_2b8 [2];
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
  long local_e8 [2];
  long local_d8 [2];
  long local_c8 [2];
  long local_b8 [2];
  wchar_t *local_a8 [2];
  long local_98 [8];
  allocator local_54;
  allocator local_53;
  allocator local_52;
  allocator local_51;
  allocator local_50;
  allocator local_4f;
  allocator local_4e;
  allocator local_4d;
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

  if (param_1 != (CDataGroup *)0x0) {
    *(CDataGroup **)(this + 0x1b0) = param_1;
                    /* try { // try from 00803147 to 0080314b has its CatchHandler @ 008045ad */
    std::wstring::wstring((wstring_conflict *)local_98,L"UNIT_GUID",local_39);
                    /* try { // try from 0080315d to 00803161 has its CatchHandler @ 00804963 */
    uVar18 = CResourceManager::getUnitGuidByDataGroup
                       (*(CResourceManager **)(this + 0x68),param_1,(wstring_conflict *)local_98);
    *(undefined8 *)(this + 0x1a0) = uVar18;
    if ((allocator *)(local_98[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_98[0] + -8);
      iVar13 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar13 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
      }
    }
                    /* try { // try from 008031a0 to 008031a4 has its CatchHandler @ 00804932 */
    std::wstring::wstring((wstring_conflict *)local_b8,L"UNITTYPE",&local_3a);
                    /* try { // try from 008031b2 to 008031c6 has its CatchHandler @ 00804917 */
    pwVar19 = (wstring_conflict *)
              CDataGroup::GetDataValue
                        (param_1,(wstring_conflict *)local_b8,(wstring_conflict *)&::EMPTY_WSTRING);
    std::wstring::wstring((wstring_conflict *)local_a8,pwVar19);
    if ((allocator *)(local_b8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_b8[0] + -8);
      iVar13 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar13 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
      }
    }
    if ((*(size_t *)(local_a8[0] + -6) != *(size_t *)(::EMPTY_WSTRING + -6)) ||
       (iVar13 = wmemcmp(local_a8[0],::EMPTY_WSTRING,*(size_t *)(local_a8[0] + -6)), iVar13 != 0)) {
                    /* try { // try from 0080320a to 0080320e has its CatchHandler @ 0080470d */
      uVar9 = CResourceManager::getUnitTypeByName
                        (*(CResourceManager **)(this + 0x68),(wstring_conflict *)local_a8);
      *(undefined4 *)(this + 0x1ac) = uVar9;
    }
                    /* try { // try from 00803232 to 00803236 has its CatchHandler @ 00804705 */
    std::wstring::wstring((wstring_conflict *)local_d8,L"NAME",&local_3b);
                    /* try { // try from 00803244 to 00803258 has its CatchHandler @ 008046f4 */
    pwVar19 = (wstring_conflict *)
              CDataGroup::GetDataValue
                        (param_1,(wstring_conflict *)local_d8,(wstring_conflict *)&::EMPTY_WSTRING);
    std::wstring::wstring((wstring_conflict *)local_c8,pwVar19);
    if ((allocator *)(local_d8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_d8[0] + -8);
      iVar13 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar13 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
      }
    }
                    /* try { // try from 00803286 to 0080328a has its CatchHandler @ 00804be7 */
    std::wstring::wstring((wstring_conflict *)local_e8,L"SCALE",&local_3c);
                    /* try { // try from 0080329b to 0080329f has its CatchHandler @ 00804be2 */
    fVar21 = (float)CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_e8,DAT_00fa47fc);
    if ((allocator *)(local_e8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_e8[0] + -8);
      iVar13 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar13 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
      }
    }
                    /* try { // try from 008032d3 to 008032d7 has its CatchHandler @ 00804818 */
    std::wstring::wstring((wstring_conflict *)local_f8,L"SCALE_VARIATION",&local_3d);
                    /* try { // try from 008032e3 to 008032e7 has its CatchHandler @ 00804808 */
    fVar22 = (float)CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_f8,0.0);
    if ((allocator *)(local_f8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_f8[0] + -8);
      iVar13 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar13 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
      }
    }
    pcVar4 = *(code **)(*(long *)this + 0x90);
                    /* try { // try from 00803312 to 00803323 has its CatchHandler @ 00804caf */
    fVar22 = (float)UTILITIES::randomBetweenVolatile(0.0,fVar22);
    (*pcVar4)(fVar22 + fVar21,this);
                    /* try { // try from 0080333c to 00803340 has its CatchHandler @ 00804ce5 */
    std::wstring::wstring((wstring_conflict *)local_108,L"SHADOWS",&local_3e);
                    /* try { // try from 0080334e to 0080335f has its CatchHandler @ 00804cd5 */
    bVar5 = (bool)CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_108,true);
    setCastsShadows(this,bVar5);
    if ((allocator *)(local_108[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_108[0] + -8);
      iVar13 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar13 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_108[0] + -0x18));
      }
    }
                    /* try { // try from 0080338d to 00803391 has its CatchHandler @ 00804c28 */
    std::wstring::wstring((wstring_conflict *)local_118,L"BLOCK",&local_3f);
                    /* try { // try from 0080339c to 008033a0 has its CatchHandler @ 008048cb */
    CVar6 = (CBaseUnit)CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_118,false);
    this[0x18e] = CVar6;
    if ((allocator *)(local_118[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_118[0] + -8);
      iVar13 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar13 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_118[0] + -0x18));
      }
    }
                    /* try { // try from 008033d9 to 008033dd has its CatchHandler @ 008048db */
    std::wstring::wstring((wstring_conflict *)local_128,L"OCCUPIESNODES",&local_40);
                    /* try { // try from 008033eb to 008033ef has its CatchHandler @ 0080489a */
    CVar6 = (CBaseUnit)CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_128,true);
    this[399] = CVar6;
    if ((allocator *)(local_128[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_128[0] + -8);
      iVar13 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar13 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_128[0] + -0x18));
      }
    }
                    /* try { // try from 00803428 to 0080342c has its CatchHandler @ 0080486c */
    std::wstring::wstring((wstring_conflict *)local_138,L"COLLIDEABLE",&local_41);
                    /* try { // try from 0080343a to 0080343e has its CatchHandler @ 0080486a */
    CVar6 = (CBaseUnit)CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_138,true);
    this[0x18d] = CVar6;
    if ((allocator *)(local_138[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_138[0] + -8);
      iVar13 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar13 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_138[0] + -0x18));
      }
      CVar6 = this[0x18d];
    }
    if (CVar6 == (CBaseUnit)0x0) {
      this[0x19c] = (CBaseUnit)0x0;
    }
    if (!param_2) {
      reapplyEffects(this,false);
    }
    local_358 = (void *)0x0;
    local_350 = 0;
    local_348 = 0;
                    /* try { // try from 008034ad to 008034b1 has its CatchHandler @ 00804786 */
    std::wstring::wstring((wstring_conflict *)local_148,L"SKILL",&local_42);
                    /* try { // try from 008034bf to 008034c3 has its CatchHandler @ 00804776 */
    uVar10 = CDataGroup::GetDataGroupsMatchingName
                       (param_1,(wstring_conflict *)local_148,(vector *)&local_358);
    if ((allocator *)(local_148[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_148[0] + -8);
      iVar13 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar13 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_148[0] + -0x18));
      }
    }
    if (uVar10 != 0) {
      local_388 = 0;
      local_380 = 0;
      do {
        this_00 = *(CDataGroup **)((long)local_358 + local_388);
                    /* try { // try from 008037be to 008037c2 has its CatchHandler @ 00804742 */
        std::wstring::wstring((wstring_conflict *)local_158,(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 008037d8 to 008037dc has its CatchHandler @ 008046b9 */
        std::wstring::wstring((wstring_conflict *)local_168,L"NAME",&local_43);
                    /* try { // try from 008037f0 to 00803804 has its CatchHandler @ 008046a7 */
        CDataGroup::GetDataValue
                  (this_00,(wstring_conflict *)local_168,(wstring_conflict *)local_158);
        std::wstring::assign((wstring_conflict *)local_158);
        if ((allocator *)(local_168[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_168[0] + -8);
          iVar13 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar13 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_168[0] + -0x18));
          }
        }
        iVar13 = *(int *)(this + 0x100);
                    /* try { // try from 0080383a to 0080383e has its CatchHandler @ 008046be */
        std::wstring::wstring((wstring_conflict *)local_178,L"LEVEL",&local_44);
                    /* try { // try from 0080384e to 00803852 has its CatchHandler @ 008047bf */
        iVar13 = CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_178,iVar13);
                    /* try { // try from 0080386a to 0080386e has its CatchHandler @ 008047ba */
        std::wstring::wstring((wstring_conflict *)local_188,L"LEVEL",&local_45);
                    /* try { // try from 0080387c to 00803880 has its CatchHandler @ 00804798 */
        CDataGroup::GetDataValue(this_00,(wstring_conflict *)local_188,iVar13);
        if ((allocator *)(local_188[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_188[0] + -8);
          iVar13 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar13 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_188[0] + -0x18));
          }
        }
        if ((allocator *)(local_178[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_178[0] + -8);
          iVar13 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar13 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_178[0] + -0x18));
          }
        }
                    /* try { // try from 008038c7 to 008038cb has its CatchHandler @ 00804793 */
        std::wstring::wstring((wstring_conflict *)local_198,L"LEVEL_REQUIRED",&local_46);
                    /* try { // try from 008038d7 to 008038db has its CatchHandler @ 0080497a */
        uVar9 = CDataGroup::GetDataValue(this_00,(wstring_conflict *)local_198,1);
        if ((allocator *)(local_198[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_198[0] + -8);
          iVar13 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar13 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_198[0] + -0x18));
          }
        }
                    /* try { // try from 0080390d to 00803911 has its CatchHandler @ 00804985 */
        std::wstring::wstring((wstring_conflict *)local_1b8,L"SKILL_REQUIRED",&local_47);
                    /* try { // try from 0080391d to 00803931 has its CatchHandler @ 008047c2 */
        pwVar19 = (wstring_conflict *)
                  CDataGroup::GetDataValue
                            (this_00,(wstring_conflict *)local_1b8,
                             (wstring_conflict *)&::EMPTY_WSTRING);
        std::wstring::wstring((wstring_conflict *)local_1a8,pwVar19);
        if ((allocator *)(local_1b8[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_1b8[0] + -8);
          iVar13 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar13 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_1b8[0] + -0x18));
          }
        }
                    /* try { // try from 0080395f to 00803963 has its CatchHandler @ 00804975 */
        std::wstring::wstring((wstring_conflict *)local_1c8,L"COLUMN",&local_48);
                    /* try { // try from 0080396f to 00803973 has its CatchHandler @ 0080472a */
        uVar14 = CDataGroup::GetDataValue(this_00,(wstring_conflict *)local_1c8,0xffffffff);
        if ((allocator *)(local_1c8[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_1c8[0] + -8);
          iVar13 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar13 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_1c8[0] + -0x18));
          }
        }
                    /* try { // try from 008039a5 to 008039a9 has its CatchHandler @ 0080473c */
        std::wstring::wstring((wstring_conflict *)local_1d8,L"ROW",&local_49);
                    /* try { // try from 008039b5 to 008039b9 has its CatchHandler @ 0080473a */
        uVar15 = CDataGroup::GetDataValue(this_00,(wstring_conflict *)local_1d8,0xffffffff);
        if ((allocator *)(local_1d8[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_1d8[0] + -8);
          iVar13 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar13 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_1d8[0] + -0x18));
          }
        }
                    /* try { // try from 008039eb to 008039ef has its CatchHandler @ 00804722 */
        std::wstring::wstring((wstring_conflict *)local_1e8,L"PANE",&local_4a);
                    /* try { // try from 008039f8 to 008039fc has its CatchHandler @ 00804bd5 */
        uVar16 = CDataGroup::GetDataValue(this_00,(wstring_conflict *)local_1e8,0);
        if ((allocator *)(local_1e8[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_1e8[0] + -8);
          iVar13 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar13 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_1e8[0] + -0x18));
          }
        }
                    /* try { // try from 00803a2e to 00803a32 has its CatchHandler @ 00804c6e */
        std::wstring::wstring((wstring_conflict *)local_1f8,L"CHARGES",&local_4b);
                    /* try { // try from 00803a40 to 00803a44 has its CatchHandler @ 00804c69 */
        iVar13 = CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_1f8,0xffffffff);
                    /* try { // try from 00803a60 to 00803a64 has its CatchHandler @ 00804c59 */
        std::wstring::wstring((wstring_conflict *)local_208,L"CHARGES",&local_4c);
                    /* try { // try from 00803a6e to 00803a72 has its CatchHandler @ 00804bda */
        uVar17 = CDataGroup::GetDataValue(this_00,(wstring_conflict *)local_208,iVar13);
        if ((allocator *)(local_208[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_208[0] + -8);
          iVar13 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar13 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_208[0] + -0x18));
          }
        }
        if ((allocator *)(local_1f8[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_1f8[0] + -8);
          iVar13 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar13 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_1f8[0] + -0x18));
          }
        }
                    /* try { // try from 00803ab9 to 00803abd has its CatchHandler @ 00804bc2 */
        std::wstring::wstring((wstring_conflict *)local_218,L"ENABLED",&local_4d);
                    /* try { // try from 00803acb to 00803acf has its CatchHandler @ 00804bb9 */
        bVar5 = (bool)CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_218,true);
                    /* try { // try from 00803aec to 00803af0 has its CatchHandler @ 00804bb4 */
        std::wstring::wstring((wstring_conflict *)local_228,L"ENABLED",&local_4e);
                    /* try { // try from 00803afa to 00803afe has its CatchHandler @ 00804b9c */
        uVar7 = CDataGroup::GetDataValue(this_00,(wstring_conflict *)local_228,bVar5);
        if ((allocator *)(local_228[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_228[0] + -8);
          iVar13 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar13 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_228[0] + -0x18));
          }
        }
        if ((allocator *)(local_218[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_218[0] + -8);
          iVar13 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar13 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_218[0] + -0x18));
          }
        }
                    /* try { // try from 00803b45 to 00803b49 has its CatchHandler @ 00804b97 */
        std::wstring::wstring((wstring_conflict *)local_248,L"ANIMATION_OVERRIDE",&local_4f);
                    /* try { // try from 00803b55 to 00803b69 has its CatchHandler @ 00804b92 */
        pwVar19 = (wstring_conflict *)
                  CDataGroup::GetDataValue(this_00,(wstring_conflict *)local_248,L"");
        std::wstring::wstring((wstring_conflict *)local_238,pwVar19);
        if ((allocator *)(local_248[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_248[0] + -8);
          iVar13 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar13 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_248[0] + -0x18));
          }
        }
                    /* try { // try from 00803b97 to 00803b9b has its CatchHandler @ 00804bc7 */
        std::wstring::wstring((wstring_conflict *)local_268,L"ANIMATION_OVERRIDEDW",&local_50);
                    /* try { // try from 00803ba7 to 00803bbb has its CatchHandler @ 00804b6a */
        pwVar19 = (wstring_conflict *)
                  CDataGroup::GetDataValue(this_00,(wstring_conflict *)local_268,L"");
        std::wstring::wstring((wstring_conflict *)local_258,pwVar19);
        if ((allocator *)(local_268[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_268[0] + -8);
          iVar13 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar13 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_268[0] + -0x18));
          }
        }
                    /* try { // try from 00803be9 to 00803bed has its CatchHandler @ 00804b8a */
        std::wstring::wstring((wstring_conflict *)local_288,L"ANIMATION_OVERRIDELOOP",&local_51);
                    /* try { // try from 00803bf9 to 00803c0d has its CatchHandler @ 00804b7a */
        pwVar19 = (wstring_conflict *)
                  CDataGroup::GetDataValue(this_00,(wstring_conflict *)local_288,L"");
        std::wstring::wstring((wstring_conflict *)local_278,pwVar19);
        if ((allocator *)(local_288[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_288[0] + -8);
          iVar13 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar13 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_288[0] + -0x18));
          }
        }
                    /* try { // try from 00803c3b to 00803c3f has its CatchHandler @ 00804b62 */
        std::wstring::wstring((wstring_conflict *)local_2a8,L"ANIMATION_OVERRIDELOOPDW",&local_52);
                    /* try { // try from 00803c4b to 00803c62 has its CatchHandler @ 00804712 */
        pwVar19 = (wstring_conflict *)
                  CDataGroup::GetDataValue(this_00,(wstring_conflict *)local_2a8,L"");
        std::wstring::wstring((wstring_conflict *)local_298,pwVar19);
        if ((allocator *)(local_2a8[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_2a8[0] + -8);
          iVar13 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar13 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_2a8[0] + -0x18));
          }
        }
                    /* try { // try from 00803c87 to 00803cb4 has its CatchHandler @ 008046f2 */
        lVar20 = addSkillByName((wstring_conflict *)this,SUB81(local_158,0));
        if (lVar20 == 0) {
          std::operator+((wchar_t *)local_2b8,(wstring_conflict *)L"Skill not found : ");
                    /* try { // try from 00803cc8 to 00803ccc has its CatchHandler @ 008046c2 */
          STRINGS::StringConvertToNarrow((STRINGS *)local_2c8,local_2b8[0]);
                    /* try { // try from 00803ccd to 00803ce3 has its CatchHandler @ 00804cb4 */
          uVar18 = Ogre::LogManager::getSingleton();
          Ogre::LogManager::logMessage(uVar18,(STRINGS *)local_2c8,2,0);
          if ((allocator *)(local_2c8[0] + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_2c8[0] + -8);
            iVar13 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar13 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_2c8[0] + -0x18));
            }
          }
          if ((allocator *)(local_2b8[0] + -6) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            pwVar2 = local_2b8[0] + -2;
            wVar3 = *pwVar2;
            *pwVar2 = *pwVar2 + L'\xffffffff';
            UNLOCK();
            if (wVar3 < L'\x01') {
              std::wstring::_Rep::_M_destroy((allocator *)(local_2b8[0] + -6));
            }
          }
          if ((allocator *)(local_298[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_298[0] + -8);
            iVar13 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar13 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_298[0] + -0x18));
            }
          }
          if ((allocator *)(local_278[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_278[0] + -8);
            iVar13 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar13 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_278[0] + -0x18));
            }
          }
          if ((allocator *)(local_258[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_258[0] + -8);
            iVar13 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar13 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_258[0] + -0x18));
            }
          }
          if ((allocator *)(local_238[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_238[0] + -8);
            iVar13 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar13 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_238[0] + -0x18));
            }
          }
          if ((allocator *)(local_1a8[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_1a8[0] + -8);
            iVar13 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar13 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_1a8[0] + -0x18));
            }
          }
          if ((allocator *)(local_158[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_158[0] + -8);
            iVar13 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar13 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_158[0] + -0x18));
            }
          }
        }
        else {
                    /* try { // try from 00803520 to 00803524 has its CatchHandler @ 008046e5 */
          std::wstring::wstring((wstring_conflict *)local_2d8,L"CHANCE",&local_53);
                    /* try { // try from 00803530 to 00803534 has its CatchHandler @ 00804cc5 */
          uVar11 = CDataGroup::GetDataValue(this_00,(wstring_conflict *)local_2d8,0x28);
          if ((allocator *)(local_2d8[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_2d8[0] + -8);
            iVar13 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar13 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_2d8[0] + -0x18));
            }
          }
                    /* try { // try from 00803565 to 00803569 has its CatchHandler @ 0080469f */
          std::wstring::wstring((wstring_conflict *)local_2e8,L"CANCEL_CHANCE",&local_54);
                    /* try { // try from 00803572 to 00803576 has its CatchHandler @ 0080468f */
          uVar12 = CDataGroup::GetDataValue(this_00,(wstring_conflict *)local_2e8,0);
          if ((allocator *)(local_2e8[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_2e8[0] + -8);
            iVar13 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar13 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_2e8[0] + -0x18));
            }
          }
          *(undefined4 *)(lVar20 + 0x118) = uVar11;
          *(undefined4 *)(lVar20 + 0x11c) = uVar12;
                    /* try { // try from 008035ac to 008035b0 has its CatchHandler @ 008046f2 */
          std::wstring::wstring((wstring_conflict *)local_2f8,(wstring_conflict *)local_238);
                    /* try { // try from 008035bb to 008035bf has its CatchHandler @ 0080468a */
          std::wstring::assign((wstring_conflict *)(lVar20 + 0x128));
          if ((allocator *)(local_2f8[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_2f8[0] + -8);
            iVar13 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar13 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_2f8[0] + -0x18));
            }
          }
                    /* try { // try from 008035e8 to 008035ec has its CatchHandler @ 008046f2 */
          std::wstring::wstring((wstring_conflict *)local_308,(wstring_conflict *)local_278);
                    /* try { // try from 008035f7 to 008035fb has its CatchHandler @ 00804608 */
          std::wstring::assign((wstring_conflict *)(lVar20 + 0x138));
          if ((allocator *)(local_308[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_308[0] + -8);
            iVar13 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar13 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_308[0] + -0x18));
            }
          }
                    /* try { // try from 00803624 to 00803628 has its CatchHandler @ 008046f2 */
          std::wstring::wstring((wstring_conflict *)local_318,(wstring_conflict *)local_258);
                    /* try { // try from 00803633 to 00803637 has its CatchHandler @ 00804cca */
          std::wstring::assign((wstring_conflict *)(lVar20 + 0x130));
          if ((allocator *)(local_318[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_318[0] + -8);
            iVar13 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar13 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_318[0] + -0x18));
            }
          }
                    /* try { // try from 0080365b to 0080365f has its CatchHandler @ 008046f2 */
          std::wstring::wstring((wstring_conflict *)local_328,(wstring_conflict *)local_298);
                    /* try { // try from 0080366a to 0080366e has its CatchHandler @ 008046d5 */
          std::wstring::assign((wstring_conflict *)(lVar20 + 0x140));
          if ((allocator *)(local_328[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_328[0] + -8);
            iVar13 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar13 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_328[0] + -0x18));
            }
          }
          *(undefined4 *)(lVar20 + 0xd8) = uVar9;
                    /* try { // try from 0080369e to 008036a2 has its CatchHandler @ 008046f2 */
          std::wstring::wstring((wstring_conflict *)local_338,(wstring_conflict *)local_1a8);
                    /* try { // try from 008036ad to 008036b1 has its CatchHandler @ 008046c7 */
          std::wstring::assign((wstring_conflict *)(lVar20 + 0xd0));
          if ((allocator *)(local_338[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_338[0] + -8);
            iVar13 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar13 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_338[0] + -0x18));
            }
          }
          *(undefined4 *)(lVar20 + 0x10c) = uVar14;
          *(undefined4 *)(lVar20 + 0x110) = uVar15;
          *(undefined4 *)(lVar20 + 0x114) = uVar16;
          *(undefined4 *)(lVar20 + 0x124) = uVar17;
          *(undefined1 *)(lVar20 + 0x6d) = uVar7;
                    /* try { // try from 00803707 to 0080370b has its CatchHandler @ 008046f2 */
          CSkillManager::setSkillLevel(*(CSkill **)(this + 0x1c8),(uint)lVar20);
          if ((allocator *)(local_298[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_298[0] + -8);
            iVar13 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar13 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_298[0] + -0x18));
            }
          }
          if ((allocator *)(local_278[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_278[0] + -8);
            iVar13 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar13 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_278[0] + -0x18));
            }
          }
          if ((allocator *)(local_258[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_258[0] + -8);
            iVar13 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar13 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_258[0] + -0x18));
            }
          }
          if ((allocator *)(local_238[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_238[0] + -8);
            iVar13 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar13 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_238[0] + -0x18));
            }
          }
          if ((allocator *)(local_1a8[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_1a8[0] + -8);
            iVar13 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar13 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_1a8[0] + -0x18));
            }
          }
          if ((allocator *)(local_158[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_158[0] + -8);
            iVar13 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar13 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_158[0] + -0x18));
            }
          }
        }
        local_380 = local_380 + 1;
        local_388 = local_388 + 8;
      } while (local_380 < uVar10);
    }
    if (local_358 != (void *)0x0) {
      operator_delete(local_358);
    }
    if ((!param_2) || (cVar8 = ISA(this), cVar8 != '\0')) {
                    /* try { // try from 00803de1 to 00803ec7 has its CatchHandler @ 00804caf */
      reapplyAffixes(this,false);
    }
    if (*(CEffectManager **)(this + 0x1b8) != (CEffectManager *)0x0) {
      CEffectManager::calculateEffectValues(*(CEffectManager **)(this + 0x1b8));
    }
    cVar8 = ISA(this,0xaa);
    if (cVar8 != '\0') {
      this_01 = (CGameClient *)0x0;
      if (*(int *)(*(long *)(this + 0x68) + 0x30) != 0) {
        this_01 = (CGameClient *)**(undefined8 **)(*(long *)(this + 0x68) + 0x28);
      }
      cVar8 = CGameClient::getPlayerIsCheat(this_01);
      if (cVar8 != '\0') {
        this[400] = (CBaseUnit)0x1;
      }
    }
    if ((allocator *)(local_c8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_c8[0] + -8);
      iVar13 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar13 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
      }
    }
    if ((allocator *)(local_a8[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      pwVar2 = local_a8[0] + -2;
      wVar3 = *pwVar2;
      *pwVar2 = *pwVar2 + L'\xffffffff';
      UNLOCK();
      if (wVar3 < L'\x01') {
        std::wstring::_Rep::_M_destroy((allocator *)(local_a8[0] + -6));
      }
    }
  }
  return;
}



/* address=00804d40
   symbol=CBaseUnit::activateEffect */

/* WARNING: Removing unreachable block (ram,0x00804f22) */
/* CBaseUnit::activateEffect(CEffect*) */

void __thiscall CBaseUnit::activateEffect(CBaseUnit *this,CEffect *param_1)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  CSkill *pCVar4;
  undefined8 uVar5;
  float fVar6;
  STRINGS aSStack_68 [16];
  wchar_t *local_58 [2];
  long local_48 [3];

  if ((*(int *)(param_1 + 0x1c) - 0x4aU < 0x20) &&
     ((1L << ((byte)(*(int *)(param_1 + 0x1c) - 0x4aU) & 0x3f) & 0x80000087U) != 0)) {
    std::wstring::wstring((wstring_conflict *)local_48,(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 00804da6 to 00804ea4 has its CatchHandler @ 00804f0f */
    std::wstring::assign((wstring_conflict *)local_48);
    fVar6 = (float)CEffect::value(param_1,1);
    iVar2 = (int)fVar6;
    if ((int)fVar6 == 0) {
      iVar2 = -1;
    }
    pCVar4 = (CSkill *)
             addSkillByName((wstring_conflict *)this,SUB81((wstring_conflict *)local_48,0));
    if (pCVar4 == (CSkill *)0x0) {
      std::operator+((wchar_t *)local_58,(wstring_conflict *)L"Skill not found : ");
                    /* try { // try from 00804ead to 00804eb1 has its CatchHandler @ 00804f42 */
      STRINGS::StringConvertToNarrow(aSStack_68,local_58[0]);
                    /* try { // try from 00804eb2 to 00804ec8 has its CatchHandler @ 00804f2d */
      uVar5 = Ogre::LogManager::getSingleton();
      Ogre::LogManager::logMessage(uVar5,aSStack_68,2,0);
                    /* try { // try from 00804ecc to 00804ed0 has its CatchHandler @ 00804f42 */
      std::string::~string((string *)aSStack_68);
                    /* try { // try from 00804ed4 to 00804ed8 has its CatchHandler @ 00804f0f */
      std::wstring::~wstring((wstring_conflict *)local_58);
      std::wstring::~wstring((wstring_conflict *)local_48);
    }
    else {
      *(undefined4 *)(pCVar4 + 0x10c) = 0xffffffff;
      *(int *)(pCVar4 + 0x124) = iVar2;
      CSkillManager::setSkillLevel(*(CSkill **)(this + 0x1c8),(uint)pCVar4);
      uVar3 = CSkillManager::getSkillLevel(*(CSkillManager **)(this + 0x1c8),pCVar4);
      if (uVar3 == 0xffffffff) {
        *(undefined4 *)(param_1 + 0x10) = 0;
        uVar3 = 0;
      }
      else {
        *(uint *)(param_1 + 0x10) = uVar3;
        if (1000 < uVar3) {
          uVar3 = 0;
        }
      }
      *(uint *)(param_1 + 0x10) = uVar3;
      CEffect::calculateBaseValue(param_1,0);
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
    }
  }
  return;
}



/* address=00804f50
   symbol=CBaseUnit::dontUseOnFull */

/* WARNING: Removing unreachable block (ram,0x00805017) */
/* CBaseUnit::dontUseOnFull() */

bool __thiscall CBaseUnit::dontUseOnFull(CBaseUnit *this)

{
  int *piVar1;
  int iVar2;
  char cVar3;
  bool bVar4;
  long local_28;
  allocator local_19;

  if (*(long *)(this + 0x1b0) == 0) {
    bVar4 = false;
  }
  else {
                    /* try { // try from 00804f85 to 00804fa0 has its CatchHandler @ 00804fff */
    std::wstring::wstring((wstring_conflict *)&local_28,L"DONT_USE_ON_FULL",&local_19);
    cVar3 = CDataGroup::GetDataValue
                      (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)&local_28,false);
    bVar4 = cVar3 != '\0';
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
  }
  return bVar4;
}



/* address=00805100
   symbol=CBaseUnit::unitThemeUpdated */

/* CBaseUnit::unitThemeUpdated(CUnitTheme*, bool) */

void CBaseUnit::unitThemeUpdated(CUnitTheme *param_1,bool param_2)

{
  return;
}



/* address=00805110
   symbol=CBaseUnit::getHighlighted */

/* CBaseUnit::getHighlighted() */

CBaseUnit __thiscall CBaseUnit::getHighlighted(CBaseUnit *this)

{
  return this[0x1a8];
}



/* address=00805120
   symbol=CBaseUnit::isEffectValidForUnit */

/* CBaseUnit::isEffectValidForUnit(CCharacter*, CBaseUnit*, CEffect*) */

undefined8 CBaseUnit::isEffectValidForUnit(CCharacter *param_1,CBaseUnit *param_2,CEffect *param_3)

{
  return 0;
}



/* address=00805130
   symbol=CBaseUnit::applyEffectOnUnit */

/* CBaseUnit::applyEffectOnUnit(CCharacter*, CBaseUnit*, CEffect*) */

undefined8 CBaseUnit::applyEffectOnUnit(CCharacter *param_1,CBaseUnit *param_2,CEffect *param_3)

{
  return 0;
}



/* address=00805140
   symbol=CBaseUnit::deactivateEffect */

/* CBaseUnit::deactivateEffect(CEffect*) */

void CBaseUnit::deactivateEffect(CEffect *param_1)

{
  return;
}



/* address=00805150
   symbol=CBaseUnit::setLevel */

/* CBaseUnit::setLevel(unsigned int) */

void __thiscall CBaseUnit::setLevel(CBaseUnit *this,uint param_1)

{
  *(uint *)(this + 0x100) = param_1;
  return;
}



/* address=0085acb0
   symbol=CBaseUnit::isPlayer */

/* CBaseUnit::isPlayer() */

void __thiscall CBaseUnit::isPlayer(CBaseUnit *this)

{
  ISA(this,0x1c);
  return;
}



/* export-summary functions=67 failures=0 */
