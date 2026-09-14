/* Targeted Ghidra class export.
   namespace=CSkill
   Treat pseudocode as navigation evidence. */


/* address=00c9cc30
   symbol=CSkill::getSkillRequiredForInvestment */

/* CSkill::getSkillRequiredForInvestment() */

CSkill * __thiscall CSkill::getSkillRequiredForInvestment(CSkill *this)

{
  return this + 0xd0;
}



/* address=00c9cc40
   symbol=CSkill::getLevelRequiredForInvestment */

/* CSkill::getLevelRequiredForInvestment() */

int __thiscall CSkill::getLevelRequiredForInvestment(CSkill *this)

{
  int iVar1;
  uint uVar2;
  long lVar3;
  long *plVar4;
  int iVar5;

  iVar1 = *(int *)(this + 0xa8);
  uVar2 = *(uint *)(this + 0xdc);
  if (iVar1 == 0) {
    lVar3 = *(long *)(this + 0x90);
    iVar5 = 1;
  }
  else {
    lVar3 = **(long **)(this + 0xa0);
    iVar5 = iVar1;
  }
  if (((int)uVar2 <= iVar5) && ((int)uVar2 < iVar1)) {
    if (uVar2 < *(uint *)(this + 0xac)) {
      plVar4 = (long *)((ulong)uVar2 * 8 + *(long *)(this + 0xa0));
    }
    else {
      plVar4 = *(long **)(this + 0xa0);
    }
    if (*plVar4 != 0) {
      if (uVar2 < *(uint *)(this + 0xac)) {
        plVar4 = (long *)((ulong)uVar2 * 8 + *(long *)(this + 0xa0));
      }
      else {
        plVar4 = *(long **)(this + 0xa0);
      }
      lVar3 = *plVar4;
    }
  }
  if ((lVar3 != 0) && (*(int *)(lVar3 + 0x44) != 0)) {
    return *(int *)(lVar3 + 0x44);
  }
  return *(int *)(this + 0xd8) + uVar2;
}



/* address=00c9ccf0
   symbol=CSkill::hasEvent */

/* CSkill::hasEvent(ESKILL_EVENT_TYPE) */

undefined4 __thiscall CSkill::hasEvent(CSkill *this,uint param_2)

{
  int iVar1;
  long lVar2;
  undefined4 uVar3;
  long *plVar4;

  lVar2 = *(long *)(this + 0x90);
  uVar3 = 1;
  if (lVar2 != 0) {
    if (param_2 < 0xb) {
      if (param_2 < *(uint *)(lVar2 + 100)) {
        plVar4 = (long *)((ulong)param_2 * 8 + *(long *)(lVar2 + 0x58));
      }
      else {
        plVar4 = *(long **)(lVar2 + 0x58);
      }
      if (*plVar4 != 0) {
        iVar1 = *(int *)(*plVar4 + 8);
        return CONCAT31((int3)((uint)iVar1 >> 8),iVar1 != 0);
      }
    }
    uVar3 = 0;
  }
  return uVar3;
}



/* address=00c9cd40
   symbol=CSkill::getCanStop */

/* CSkill::getCanStop() */

bool __thiscall CSkill::getCanStop(CSkill *this)

{
  bool bVar1;

  bVar1 = true;
  if (*(long *)(this + 0x90) != 0) {
    bVar1 = *(float *)(*(long *)(this + 0x90) + 0xa0) <= *(float *)(this + 0x108);
  }
  return bVar1;
}



/* address=00c9cd70
   symbol=CSkill::getIsExclusive */

/* CSkill::getIsExclusive() */

undefined1 __thiscall CSkill::getIsExclusive(CSkill *this)

{
  undefined1 uVar1;

  uVar1 = 0;
  if (*(long *)(this + 0x90) != 0) {
    uVar1 = *(undefined1 *)(*(long *)(this + 0x90) + 0xb3);
  }
  return uVar1;
}



/* address=00c9cd90
   symbol=CSkill::getManaCost */

/* CSkill::getManaCost() */

long __thiscall CSkill::getManaCost(CSkill *this)

{
  long lVar1;

  lVar1 = 0;
  if (*(long *)(this + 0x90) != 0) {
    lVar1 = (long)*(float *)(*(long *)(this + 0x90) + 0x78);
  }
  return lVar1;
}



/* address=00c9cdb0
   symbol=CSkill::getRequiresPathable */

/* CSkill::getRequiresPathable() */

CSkill __thiscall CSkill::getRequiresPathable(CSkill *this)

{
  CSkill CVar1;

  CVar1 = (CSkill)0x0;
  if (*(long *)(this + 0x90) != 0) {
    CVar1 = this[0x6a];
  }
  return CVar1;
}



/* address=00c9cdd0
   symbol=CSkill::getCanBeInterrupted */

/* CSkill::getCanBeInterrupted() */

undefined1 __thiscall CSkill::getCanBeInterrupted(CSkill *this)

{
  undefined1 uVar1;

  uVar1 = 0;
  if (*(long *)(this + 0x90) != 0) {
    uVar1 = *(undefined1 *)(*(long *)(this + 0x90) + 0xb1);
  }
  return uVar1;
}



/* address=00c9cdf0
   symbol=CSkill::getManaCostOT */

/* CSkill::getManaCostOT() */

long __thiscall CSkill::getManaCostOT(CSkill *this)

{
  long lVar1;

  lVar1 = 0;
  if (*(long *)(this + 0x90) != 0) {
    lVar1 = (long)*(float *)(*(long *)(this + 0x90) + 0x7c);
  }
  return lVar1;
}



/* address=00c9ce10
   symbol=CSkill::getSkillIcon */

/* CSkill::getSkillIcon() */

undefined8 * __thiscall CSkill::getSkillIcon(CSkill *this)

{
  undefined8 *puVar1;

  puVar1 = &::EMPTY_WSTRING;
  if (*(long *)(this + 0x90) != 0) {
    puVar1 = (undefined8 *)(*(long *)(this + 0x90) + 200);
  }
  return puVar1;
}



/* address=00c9ce30
   symbol=CSkill::getSkillIconInactive */

/* CSkill::getSkillIconInactive() */

undefined8 * __thiscall CSkill::getSkillIconInactive(CSkill *this)

{
  undefined8 *puVar1;

  puVar1 = &::EMPTY_WSTRING;
  if (*(long *)(this + 0x90) != 0) {
    puVar1 = (undefined8 *)(*(long *)(this + 0x90) + 0xd0);
  }
  return puVar1;
}



/* address=00c9ce50
   symbol=CSkill::getName */

/* CSkill::getName() */

undefined8 * __thiscall CSkill::getName(CSkill *this)

{
  undefined8 *puVar1;

  puVar1 = &::EMPTY_WSTRING;
  if (*(long *)(this + 0x90) != 0) {
    puVar1 = (undefined8 *)(*(long *)(this + 0x90) + 0xd8);
  }
  return puVar1;
}



/* address=00c9ce70
   symbol=CSkill::getSkillUsageDescription */

/* CSkill::getSkillUsageDescription() */

undefined8 * __thiscall CSkill::getSkillUsageDescription(CSkill *this)

{
  undefined8 *puVar1;

  puVar1 = &::EMPTY_WSTRING;
  if (*(long *)(this + 0x90) != 0) {
    puVar1 = (undefined8 *)(*(long *)(this + 0x90) + 0xe8);
  }
  return puVar1;
}



/* address=00c9ce90
   symbol=CSkill::getDisplayName */

/* CSkill::getDisplayName() */

undefined8 * __thiscall CSkill::getDisplayName(CSkill *this)

{
  undefined8 *puVar1;

  puVar1 = &::EMPTY_WSTRING;
  if (*(long *)(this + 0x90) != 0) {
    puVar1 = (undefined8 *)(*(long *)(this + 0x90) + 0xe0);
  }
  return puVar1;
}



/* address=00c9ceb0
   symbol=CSkill::getAnimationIndex */

/* CSkill::getAnimationIndex() */

undefined4 __thiscall CSkill::getAnimationIndex(CSkill *this)

{
  undefined4 uVar1;

  uVar1 = 0xffffffff;
  if (*(long *)(this + 0x90) != 0) {
    uVar1 = *(undefined4 *)(this + 0xe4);
  }
  return uVar1;
}



/* address=00c9ced0
   symbol=CSkill::getAnimationIndexDW */

/* CSkill::getAnimationIndexDW() */

undefined4 __thiscall CSkill::getAnimationIndexDW(CSkill *this)

{
  undefined4 uVar1;

  uVar1 = 0xffffffff;
  if (*(long *)(this + 0x90) != 0) {
    uVar1 = *(undefined4 *)(this + 0xe8);
  }
  return uVar1;
}



/* address=00c9cef0
   symbol=CSkill::getAnimationIndexLoopInto */

/* CSkill::getAnimationIndexLoopInto() */

undefined4 __thiscall CSkill::getAnimationIndexLoopInto(CSkill *this)

{
  undefined4 uVar1;

  uVar1 = 0xffffffff;
  if (*(long *)(this + 0x90) != 0) {
    uVar1 = *(undefined4 *)(this + 0xec);
  }
  return uVar1;
}



/* address=00c9cf10
   symbol=CSkill::getAnimationIndexLoopEnd */

/* CSkill::getAnimationIndexLoopEnd() */

undefined4 __thiscall CSkill::getAnimationIndexLoopEnd(CSkill *this)

{
  undefined4 uVar1;

  uVar1 = 0xffffffff;
  if (*(long *)(this + 0x90) != 0) {
    uVar1 = *(undefined4 *)(this + 0xf4);
  }
  return uVar1;
}



/* address=00c9cf30
   symbol=CSkill::getChanceToCast */

/* CSkill::getChanceToCast() */

undefined4 __thiscall CSkill::getChanceToCast(CSkill *this)

{
  undefined4 uVar1;

  uVar1 = 0xffffffff;
  if (*(long *)(this + 0x90) != 0) {
    uVar1 = *(undefined4 *)(*(long *)(this + 0x90) + 0xac);
  }
  return uVar1;
}



/* address=00c9cf50
   symbol=CSkill::getAnimationIndexDWLoopInto */

/* CSkill::getAnimationIndexDWLoopInto() */

undefined4 __thiscall CSkill::getAnimationIndexDWLoopInto(CSkill *this)

{
  undefined4 uVar1;

  uVar1 = 0xffffffff;
  if (*(long *)(this + 0x90) != 0) {
    uVar1 = *(undefined4 *)(this + 0xf0);
  }
  return uVar1;
}



/* address=00c9cf70
   symbol=CSkill::getAnimationSpeedMult */

/* CSkill::getAnimationSpeedMult() */

undefined4 __thiscall CSkill::getAnimationSpeedMult(CSkill *this)

{
  if (*(long *)(this + 0x90) != 0) {
    return *(undefined4 *)(*(long *)(this + 0x90) + 0x94);
  }
  return DAT_00ff4cd8;
}



/* address=00c9cfa0
   symbol=CSkill::getFindTargetAngle */

/* CSkill::getFindTargetAngle() */

undefined4 __thiscall CSkill::getFindTargetAngle(CSkill *this)

{
  if (*(long *)(this + 0x90) != 0) {
    return *(undefined4 *)(*(long *)(this + 0x90) + 0x90);
  }
  return 0;
}



/* address=00c9cfc0
   symbol=CSkill::getRange */

/* CSkill::getRange() */

undefined4 __thiscall CSkill::getRange(CSkill *this)

{
  if (*(long *)(this + 0x90) != 0) {
    return *(undefined4 *)(*(long *)(this + 0x90) + 0x80);
  }
  return DAT_00fa47fc;
}



/* address=00c9cff0
   symbol=CSkill::getRangeMin */

/* CSkill::getRangeMin() */

undefined4 __thiscall CSkill::getRangeMin(CSkill *this)

{
  if (*(long *)(this + 0x90) != 0) {
    return *(undefined4 *)(*(long *)(this + 0x90) + 0x84);
  }
  return 0;
}



/* address=00c9d010
   symbol=CSkill::getRandomRange */

/* CSkill::getRandomRange() */

undefined4 __thiscall CSkill::getRandomRange(CSkill *this)

{
  if (*(long *)(this + 0x90) != 0) {
    return *(undefined4 *)(*(long *)(this + 0x90) + 0x88);
  }
  return DAT_00fa47fc;
}



/* address=00c9d040
   symbol=CSkill::getRandomRangeMin */

/* CSkill::getRandomRangeMin() */

undefined4 __thiscall CSkill::getRandomRangeMin(CSkill *this)

{
  if (*(long *)(this + 0x90) != 0) {
    return *(undefined4 *)(*(long *)(this + 0x90) + 0x8c);
  }
  return 0;
}



/* address=00c9d060
   symbol=CSkill::getMinimumTime */

/* CSkill::getMinimumTime() */

undefined4 __thiscall CSkill::getMinimumTime(CSkill *this)

{
  if (*(long *)(this + 0x90) != 0) {
    return *(undefined4 *)(*(long *)(this + 0x90) + 0xa0);
  }
  return DAT_00fa47fc;
}



/* address=00c9d090
   symbol=CSkill::getTargetType */

/* CSkill::getTargetType() */

undefined4 __thiscall CSkill::getTargetType(CSkill *this)

{
  undefined4 uVar1;

  uVar1 = 0;
  if (*(long *)(this + 0x90) != 0) {
    uVar1 = *(undefined4 *)(*(long *)(this + 0x90) + 0x70);
  }
  return uVar1;
}



/* address=00c9d0b0
   symbol=CSkill::getUnitTypeToTarget */

/* CSkill::getUnitTypeToTarget() */

undefined4 __thiscall CSkill::getUnitTypeToTarget(CSkill *this)

{
  undefined4 uVar1;

  uVar1 = 0;
  if (*(long *)(this + 0x90) != 0) {
    uVar1 = *(undefined4 *)(*(long *)(this + 0x90) + 0x74);
  }
  return uVar1;
}



/* address=00c9d0d0
   symbol=CSkill::getMasterOwner */

/* CSkill::getMasterOwner() */

undefined8 __thiscall CSkill::getMasterOwner(CSkill *this)

{
  undefined8 uVar1;

  uVar1 = 0;
  if (*(long *)(this + 0x20) != 0) {
    uVar1 = *(undefined8 *)(*(long *)(this + 0x20) + 0x88);
  }
  return uVar1;
}



/* address=00c9d0f0
   symbol=CSkill::fillOutStatBonuses */

/* CSkill::fillOutStatBonuses(float (&) [6], bool, unsigned int) */

void __thiscall CSkill::fillOutStatBonuses(CSkill *this,float *param_1,bool param_2,uint param_3)

{
  CSkillProperty *this_00;
  uint uVar1;
  undefined8 *puVar2;

  uVar1 = param_3 - 1;
  this_00 = *(CSkillProperty **)(this + 0x90);
  if ((uVar1 < 0xfffffffe) && (param_3 <= *(uint *)(this + 0xa8))) {
    if (uVar1 < *(uint *)(this + 0xac)) {
      puVar2 = (undefined8 *)((ulong)uVar1 * 8 + *(long *)(this + 0xa0));
    }
    else {
      puVar2 = *(undefined8 **)(this + 0xa0);
    }
    this_00 = (CSkillProperty *)*puVar2;
  }
  if (this_00 == (CSkillProperty *)0x0) {
    return;
  }
  CSkillProperty::fillOutStatBonuses(this_00,param_1,param_2);
  return;
}



/* address=00c9d160
   symbol=CSkill::getOwnerCharacter */

/* CSkill::getOwnerCharacter() */

undefined8 __thiscall CSkill::getOwnerCharacter(CSkill *this)

{
  long lVar1;
  undefined8 uVar2;

  lVar1 = *(long *)(this + 0x30);
  if ((lVar1 != 0) && (*(int *)(lVar1 + 0x188) == 0)) {
    uVar2 = __dynamic_cast(lVar1,&CBaseUnit::typeinfo,&CCharacter::typeinfo,0);
    return uVar2;
  }
  return 0;
}



/* address=00c9d190
   symbol=CSkill::canAffixesAndEffectsBeAppliedToUnit */

/* CSkill::canAffixesAndEffectsBeAppliedToUnit(CBaseUnit*, CCharacter*) */

undefined8 __thiscall
CSkill::canAffixesAndEffectsBeAppliedToUnit(CSkill *this,CBaseUnit *param_1,CCharacter *param_2)

{
  CSkillProperty *this_00;
  undefined8 uVar1;

  this_00 = *(CSkillProperty **)(this + 0x90);
  if (this_00 != (CSkillProperty *)0x0) {
    if (param_2 == (CCharacter *)0x0) {
      param_2 = (CCharacter *)getOwnerCharacter(this);
    }
    uVar1 = CSkillProperty::canAffixesAndEffectsBeAppliedToUnit(this_00,param_1,param_2);
    return uVar1;
  }
  return 0;
}



/* address=00c9d1e0
   symbol=CSkill::getMasterOwnerCharacter */

/* CSkill::getMasterOwnerCharacter() */

undefined8 __thiscall CSkill::getMasterOwnerCharacter(CSkill *this)

{
  long lVar1;
  undefined8 uVar2;

  if ((((*(long *)(this + 0x30) == 0) || (*(int *)(*(long *)(this + 0x30) + 0x188) == 0)) &&
      (*(long *)(this + 0x20) != 0)) &&
     (lVar1 = *(long *)(*(long *)(this + 0x20) + 0x88), lVar1 != 0)) {
    uVar2 = __dynamic_cast(lVar1,&CBaseUnit::typeinfo,&CCharacter::typeinfo,0);
    return uVar2;
  }
  return 0;
}



/* address=00c9d220
   symbol=CSkill::getCoolDown */

/* CSkill::getCoolDown() */

ulong __thiscall CSkill::getCoolDown(CSkill *this)

{
  ulong uVar1;

  if (*(CSkillProperty **)(this + 0x90) != (CSkillProperty *)0x0) {
    uVar1 = CSkillProperty::getCoolDown(*(CSkillProperty **)(this + 0x90));
    return uVar1;
  }
  return (ulong)DAT_00fa47fc;
}



/* address=00c9d250
   symbol=CSkill::getIsInRange */

/* CSkill::getIsInRange(Ogre::Vector3 const&, Ogre::Vector3 const&, CBaseUnit*, CBaseUnit*) */

undefined8 __thiscall
CSkill::getIsInRange
          (CSkill *this,Vector3 *param_1,Vector3 *param_2,CBaseUnit *param_3,CBaseUnit *param_4)

{
  char cVar1;
  long lVar2;
  float fVar3;
  float fVar4;

  fVar3 = SQRT((*(float *)param_1 - *(float *)param_2) * (*(float *)param_1 - *(float *)param_2) +
               (*(float *)(param_1 + 4) - *(float *)(param_2 + 4)) *
               (*(float *)(param_1 + 4) - *(float *)(param_2 + 4)) +
               (*(float *)(param_1 + 8) - *(float *)(param_2 + 8)) *
               (*(float *)(param_1 + 8) - *(float *)(param_2 + 8)));
  if ((this[0x69] != (CSkill)0x0) && (lVar2 = *(long *)(*(long *)(this + 0x18) + 0x18), lVar2 != 0))
  {
    if (param_3 != (CBaseUnit *)0x0) {
      (**(code **)(*(long *)param_3 + 0x268))(param_3,lVar2);
      lVar2 = *(long *)(*(long *)(this + 0x18) + 0x18);
    }
    if (param_4 != (CBaseUnit *)0x0) {
      (**(code **)(*(long *)param_4 + 0x268))(param_4,lVar2);
      lVar2 = *(long *)(*(long *)(this + 0x18) + 0x18);
    }
    cVar1 = CLevel::passableBetween
                      (*(undefined8 *)param_1,*(undefined4 *)(param_1 + 8),lVar2,param_2,0);
    if (param_3 != (CBaseUnit *)0x0) {
      (**(code **)(*(long *)param_3 + 0x270))
                (param_3,*(undefined8 *)(*(long *)(this + 0x18) + 0x18));
    }
    if (param_4 != (CBaseUnit *)0x0) {
      (**(code **)(*(long *)param_4 + 0x270))
                (param_4,*(undefined8 *)(*(long *)(this + 0x18) + 0x18));
    }
    if (cVar1 == '\0') {
      return 0;
    }
  }
  lVar2 = *(long *)(this + 0x90);
  fVar4 = 0.0;
  if (lVar2 != 0) {
    fVar4 = *(float *)(lVar2 + 0x84);
  }
  if (fVar3 < fVar4) {
    return 0;
  }
  fVar4 = DAT_00fa47fc;
  if (lVar2 != 0) {
    fVar4 = *(float *)(lVar2 + 0x80);
  }
  return CONCAT71((int7)((ulong)lVar2 >> 8),fVar3 <= fVar4);
}



/* address=00c9d3c0
   symbol=CSkill::getMaximumDamage */

/* CSkill::getMaximumDamage() */

int __thiscall CSkill::getMaximumDamage(CSkill *this)

{
  int iVar1;
  float fVar2;
  float local_10;
  float local_c [3];

  iVar1 = 0;
  if (*(long *)(this + 0x90) != 0) {
    local_c[0] = 0.0;
    local_10 = 0.0;
    CSkillProperty::addMinAndMaxValuesOfAnEffect
              (*(CSkillProperty **)(this + 0x90),*(CResourceManager **)(this + 0x18),0x34,local_c,
               &local_10);
    fVar2 = ceilf(local_10);
    iVar1 = (int)fVar2;
  }
  return iVar1;
}



/* address=00c9d420
   symbol=CSkill::getMinimumDamage */

/* CSkill::getMinimumDamage() */

int __thiscall CSkill::getMinimumDamage(CSkill *this)

{
  int iVar1;
  float fVar2;
  float local_10;
  float local_c [3];

  iVar1 = 0;
  if (*(long *)(this + 0x90) != 0) {
    local_c[0] = 0.0;
    local_10 = 0.0;
    CSkillProperty::addMinAndMaxValuesOfAnEffect
              (*(CSkillProperty **)(this + 0x90),*(CResourceManager **)(this + 0x18),0x34,local_c,
               &local_10);
    fVar2 = ceilf(local_c[0]);
    iVar1 = (int)fVar2;
  }
  return iVar1;
}



/* address=00c9d480
   symbol=CSkill::getTargetIsValid */

/* CSkill::getTargetIsValid(CCharacter*, CCharacter*, Ogre::Vector3 const*, bool) */

uint __thiscall
CSkill::getTargetIsValid
          (CSkill *this,CCharacter *param_1,CCharacter *param_2,Vector3 *param_3,bool param_4)

{
  long lVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  long lVar5;
  CCharacter *this_00;

  if ((*(long *)(this + 0x90) == 0) ||
     (this_00 = param_2, *(int *)(*(long *)(this + 0x90) + 0x70) != 3)) {
    this_00 = param_1;
  }
  if (this_00 == (CCharacter *)0x0) {
    return 0;
  }
  if ((param_4) || (this[0x6e] != (CSkill)0x0)) {
    iVar3 = CCharacter::HP(this_00);
    if (0 < iVar3) {
      return 0;
    }
  }
  else {
    iVar3 = CCharacter::HP(this_00);
    if (iVar3 < 1) {
      return 0;
    }
  }
  if (((*(long *)(this + 0x90) != 0) && (*(int *)(*(long *)(this + 0x90) + 0x74) != 0)) &&
     (cVar2 = CBaseUnit::ISA((CBaseUnit *)this_00), cVar2 == '\0')) {
    return 0;
  }
  if (*(uint *)(this + 0x80) != 0) {
    lVar5 = 0;
    uVar4 = 0;
    while( true ) {
      if (uVar4 < *(uint *)(this + 0x84)) {
        lVar1 = *(long *)(lVar5 + *(long *)(this + 0x78));
      }
      else {
        lVar1 = **(long **)(this + 0x78);
      }
      if (*(long *)(this_00 + 0x1b0) == lVar1) break;
      uVar4 = uVar4 + 1;
      lVar5 = lVar5 + 8;
      if (*(uint *)(this + 0x80) <= uVar4) {
        return 0;
      }
    }
  }
  if (*(long *)(this + 0x90) != 0) {
    iVar3 = *(int *)(*(long *)(this + 0x90) + 0x70);
    if (iVar3 == 10) {
      if (this_00 == param_2) {
        return 1;
      }
      if (param_2 == *(CCharacter **)(this_00 + 0x640)) {
        return 1;
      }
      if (((param_2 != (CCharacter *)0x0) &&
          (*(CCharacter **)(param_2 + 0x640) != (CCharacter *)0x0)) &&
         (this_00 == *(CCharacter **)(param_2 + 0x640))) {
        return 1;
      }
    }
    else if ((iVar3 == 9) && (param_2 == *(CCharacter **)(this_00 + 0x640))) {
      return 1;
    }
  }
  iVar3 = CCharacter::alignment(param_2);
  if (iVar3 == 0) {
    return 0;
  }
  if ((*(long *)(this + 0x90) == 0) || (*(int *)(*(long *)(this + 0x90) + 0x70) != 4)) {
    uVar4 = CCharacter::isEnemy(param_2,this_00);
    iVar3 = CCharacter::alignment(param_2);
    if (iVar3 != 4) {
      if (*(int *)(this + 0x120) == 2) {
        return uVar4;
      }
      if (*(int *)(this + 0x120) != 1) {
        return 0;
      }
      return uVar4 ^ 1;
    }
  }
  return 1;
}



/* address=00c9d610
   symbol=CSkill::attemptToStopSkill */

/* CSkill::attemptToStopSkill() */

void __thiscall CSkill::attemptToStopSkill(CSkill *this)

{
  char cVar1;
  uint uVar2;

  if (*(int *)(this + 0xc0) != 0) {
    uVar2 = 0;
    do {
      if (uVar2 < *(uint *)(this + 0xc4)) {
        cVar1 = CSkillEvent::canStop(*(CSkillEvent **)((ulong)uVar2 * 8 + *(long *)(this + 0xb8)));
      }
      else {
        cVar1 = CSkillEvent::canStop((CSkillEvent *)**(undefined8 **)(this + 0xb8));
      }
      if (cVar1 == '\0') {
        return;
      }
      uVar2 = uVar2 + 1;
    } while (uVar2 < *(uint *)(this + 0xc0));
  }
  *(undefined4 *)(this + 0x104) = 0x3a83126f;
  return;
}



/* address=00c9d6a0
   symbol=CSkill::weaponRequirementsMet */

/* CSkill::weaponRequirementsMet(CCharacter*) */

undefined8 __thiscall CSkill::weaponRequirementsMet(CSkill *this,CCharacter *param_1)

{
  bool bVar1;
  char cVar2;
  char cVar3;
  CBaseUnit *pCVar4;
  CBaseUnit *pCVar5;
  undefined8 uVar6;

  cVar3 = *(char *)(*(long *)(this + 0x90) + 0x18);
  pCVar4 = (CBaseUnit *)CCharacter::getWeaponInRightHand(param_1);
  pCVar5 = (CBaseUnit *)CCharacter::getWeaponInLeftHand(param_1);
  if (pCVar4 == (CBaseUnit *)0x0) {
LAB_00c9d790:
    bVar1 = false;
  }
  else {
    bVar1 = true;
    cVar2 = CBaseUnit::ISA(pCVar4,*(undefined4 *)(*(long *)(this + 0x90) + 0x10));
    if (cVar2 == '\0') goto LAB_00c9d790;
  }
  if (pCVar5 != (CBaseUnit *)0x0) {
    cVar2 = CBaseUnit::ISA(pCVar5,*(undefined4 *)(*(long *)(this + 0x90) + 0x14));
    uVar6 = 1;
    if (cVar2 != '\0') goto LAB_00c9d729;
  }
  uVar6 = 0;
LAB_00c9d729:
  if (cVar3 == '\0') {
    if ((bVar1) || (*(int *)(*(long *)(this + 0x90) + 0x10) == 0)) {
      return 1;
    }
    if (((pCVar5 != (CBaseUnit *)0x0) && (cVar3 = CBaseUnit::ISA(pCVar5,0x26), cVar3 != '\0')) &&
       (cVar3 = CBaseUnit::ISA(pCVar5,10), cVar3 != '\0')) {
      uVar6 = CBaseUnit::ISA(pCVar5,*(undefined4 *)(*(long *)(this + 0x90) + 0x10));
      return uVar6;
    }
  }
  else if (bVar1) {
    return uVar6;
  }
  return 0;
}



/* address=00c9d7f0
   symbol=CSkill::requirementsMet */

/* CSkill::requirementsMet(CBaseUnit*, ESKILL_ACTIVATION_TYPE, Ogre::Vector3 const*, CBaseUnit*,
   bool) */

undefined8
CSkill::requirementsMet
          (undefined8 param_1_00,undefined4 param_2,CSkill *param_1,CBaseUnit *param_4,int param_5,
          Vector3 *param_6,CPositionableObject *param_7,char param_8)

{
  int iVar1;
  char cVar2;
  CCharacter *pCVar3;
  undefined8 uVar4;
  long lVar5;
  undefined8 local_48;
  undefined4 local_40;
  undefined8 local_38;
  undefined4 local_30;
  undefined8 local_28;
  undefined4 local_20;

  if (m_gAllowSkillTesting == '\0') {
    if (((((param_1[0x6d] != (CSkill)0x0) &&
          (lVar5 = *(long *)(param_1 + 0x90), param_4 != (CBaseUnit *)0x0)) && (lVar5 != 0)) &&
        (((param_5 == 0 || (*(int *)(param_1 + 0x60) == param_5)) || (*(int *)(param_1 + 0x60) == 0)
         ))) && (*(int *)(param_1 + 0x124) != 0)) {
      if (*(CUnitTheme **)(lVar5 + 0xb8) != (CUnitTheme *)0x0) {
        cVar2 = CBaseUnit::hasUnitTheme(param_4,*(CUnitTheme **)(lVar5 + 0xb8));
        if (cVar2 == '\0') goto LAB_00c9d870;
        lVar5 = *(long *)(param_1 + 0x90);
      }
      if (((*(CUnitTheme **)(lVar5 + 0xc0) == (CUnitTheme *)0x0) ||
          (cVar2 = CBaseUnit::hasUnitTheme(param_4,*(CUnitTheme **)(lVar5 + 0xc0)), cVar2 == '\0'))
         && ((param_1[0x70] == (CSkill)0x0 ||
             ((*(CEffectManager **)(param_4 + 0x1b8) == (CEffectManager *)0x0 ||
              (cVar2 = CEffectManager::hasEffect(*(CEffectManager **)(param_4 + 0x1b8),0x80),
              cVar2 == '\0')))))) {
        iVar1 = *(int *)(*(long *)(param_1 + 0x90) + 0x70);
        if (iVar1 == 2) {
          if (param_7 != (CPositionableObject *)0x0) {
            if (param_8 == '\0') {
              local_48 = CPositionableObject::getPosition(param_7,true);
              local_40 = param_2;
              local_38 = CPositionableObject::getPosition((CPositionableObject *)param_4,true);
              local_30 = param_2;
              cVar2 = getIsInRange(param_1,(Vector3 *)&local_38,(Vector3 *)&local_48,param_4,
                                   (CBaseUnit *)param_7);
joined_r0x00c9da6b:
              if (cVar2 == '\0') goto LAB_00c9d870;
            }
LAB_00c9d93e:
            pCVar3 = (CCharacter *)
                     __dynamic_cast(param_4,&CBaseUnit::typeinfo,&CCharacter::typeinfo,0);
            if (pCVar3 != (CCharacter *)0x0) {
              uVar4 = weaponRequirementsMet(param_1,pCVar3);
              return uVar4;
            }
            goto LAB_00c9d890;
          }
        }
        else {
          if (iVar1 < 3) {
            if (iVar1 == 1) {
              if (param_6 == (Vector3 *)0x0) goto LAB_00c9d870;
              if (param_8 == '\0') {
                local_28 = CPositionableObject::getPosition((CPositionableObject *)param_4,true);
                local_20 = param_2;
                cVar2 = getIsInRange(param_1,(Vector3 *)&local_28,param_6,param_4,
                                     (CBaseUnit *)param_7);
                goto joined_r0x00c9da6b;
              }
            }
            goto LAB_00c9d93e;
          }
          if (iVar1 == 7) {
            if ((param_7 != (CPositionableObject *)0x0) &&
               (cVar2 = CBaseUnit::ISA((CBaseUnit *)param_7,2), cVar2 != '\0')) goto LAB_00c9d93e;
          }
          else if (((iVar1 != 8) ||
                   ((param_7 == (CPositionableObject *)0x0 ||
                    (cVar2 = CBaseUnit::ISA((CBaseUnit *)param_7,2), cVar2 == '\0')))) ||
                  ((lVar5 = __dynamic_cast(param_7,&CBaseUnit::typeinfo,&CEquipment::typeinfo,0),
                   lVar5 != 0 && (*(char *)(lVar5 + 0x348) == '\0')))) goto LAB_00c9d93e;
        }
      }
    }
LAB_00c9d870:
    uVar4 = 0;
  }
  else {
LAB_00c9d890:
    uVar4 = 1;
  }
  return uVar4;
}



/* address=00c9db10
   symbol=CSkill::rollCancelChance */

/* CSkill::rollCancelChance() */

bool __thiscall CSkill::rollCancelChance(CSkill *this)

{
  int iVar1;

  if (99 < *(int *)(this + 0x11c)) {
    return true;
  }
  iVar1 = UTILITIES::randomIntegerBetweenVolatile(0,100);
  return iVar1 <= *(int *)(this + 0x11c);
}



/* address=00c9db40
   symbol=CSkill::rollCastChance */

/* CSkill::rollCastChance() */

bool __thiscall CSkill::rollCastChance(CSkill *this)

{
  int iVar1;

  if (99 < *(int *)(this + 0x118)) {
    return true;
  }
  iVar1 = UTILITIES::randomIntegerBetweenVolatile(0,100);
  return iVar1 <= *(int *)(this + 0x118);
}



/* address=00c9db70
   symbol=CSkill::rollSkillChance */

/* CSkill::rollSkillChance() */

bool __thiscall CSkill::rollSkillChance(CSkill *this)

{
  uint uVar1;

  if ((*(long *)(this + 0x90) != 0) && (*(uint *)(*(long *)(this + 0x90) + 0xac) < 100)) {
    uVar1 = UTILITIES::randomIntegerBetweenVolatile(0,100);
    if (*(long *)(this + 0x90) != 0) {
      return uVar1 <= *(uint *)(*(long *)(this + 0x90) + 0xac);
    }
  }
  return true;
}



/* address=00ca47a0
   symbol=CSkill::_GLOBAL__I_CSkill */

/* CSkill::CSkill(CResourceManager*, CDataGroup*) */

void CSkill::_GLOBAL__I_CSkill(void)

{
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
  std::string::string((string *)::KLayoutFunctionNames,"GUIEXITGAME",&aStack_280);
  std::string::string((string *)(::KLayoutFunctionNames + 8),"GUIEXITAPPLICATION",&aStack_27f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x10),"GUINEWGAME",&aStack_27e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x18),"GUICONTINUEGAME",&aStack_27d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x20),"GUINEWGAMEMENU",&aStack_27c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x28),"GUICONTINUEGAMEMENU",&aStack_27b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x30),"GUICLOSEMENU",&aStack_27a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x38),"GUIBACK",&aStack_279);
  std::string::string((string *)(::KLayoutFunctionNames + 0x40),"GUIDECLINE",&aStack_278);
  std::string::string((string *)(::KLayoutFunctionNames + 0x48),"GUIACCEPT",&aStack_277);
  std::string::string((string *)(::KLayoutFunctionNames + 0x50),"GUIOK",&aStack_276);
  std::string::string((string *)(::KLayoutFunctionNames + 0x58),"GUIPAUSE",&aStack_275);
  std::string::string((string *)(::KLayoutFunctionNames + 0x60),"GUISCROLLUP",&aStack_274);
  std::string::string((string *)(::KLayoutFunctionNames + 0x68),"GUISCROLLDOWN",&aStack_273);
  std::string::string((string *)(::KLayoutFunctionNames + 0x70),"GUISELECT1",&aStack_272);
  std::string::string((string *)(::KLayoutFunctionNames + 0x78),"GUISELECT2",&aStack_271);
  std::string::string((string *)(::KLayoutFunctionNames + 0x80),"GUISELECT3",&aStack_270);
  std::string::string((string *)(::KLayoutFunctionNames + 0x88),"GUISELECT4",&aStack_26f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x90),"GUISELECT5",&aStack_26e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x98),"GUISELECT6",&aStack_26d);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa0),"GUISELECT7",&aStack_26c);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa8),"GUISELECT8",&aStack_26b);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb0),"GUISELECT9",&aStack_26a);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb8),"GUISELECT10",&aStack_269);
  std::string::string((string *)(::KLayoutFunctionNames + 0xc0),"GUISELECT11",&aStack_268);
  std::string::string((string *)(::KLayoutFunctionNames + 200),"GUISELECT12",&aStack_267);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd0),"GUISELECT13",&aStack_266);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd8),"GUISELECT14",&aStack_265);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe0),"GUISELECT15",&aStack_264);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe8),"GUISELECT16",&aStack_263);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf0),"GUISELECT17",&aStack_262);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf8),"GUISELECT18",&aStack_261);
  std::string::string((string *)(::KLayoutFunctionNames + 0x100),"GUISELECT19",&aStack_260);
  std::string::string((string *)(::KLayoutFunctionNames + 0x108),"GUISELECT20",&aStack_25f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x110),"GUISELECT21",&aStack_25e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x118),"GUISELECT22",&aStack_25d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x120),"GUISELECT23",&aStack_25c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x128),"GUISELECT24",&aStack_25b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x130),"GUISELECT25",&aStack_25a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x138),"GUISELECT26",&aStack_259);
  std::string::string((string *)(::KLayoutFunctionNames + 0x140),"GUISELECT27",&aStack_258);
  std::string::string((string *)(::KLayoutFunctionNames + 0x148),"GUISELECT28",&aStack_257);
  std::string::string((string *)(::KLayoutFunctionNames + 0x150),"GUISELECT29",&aStack_256);
  std::string::string((string *)(::KLayoutFunctionNames + 0x158),"GUISELECT30",&aStack_255);
  std::string::string((string *)(::KLayoutFunctionNames + 0x160),"GUISELECT31",&aStack_254);
  std::string::string((string *)(::KLayoutFunctionNames + 0x168),"GUISELECT32",&aStack_253);
  std::string::string((string *)(::KLayoutFunctionNames + 0x170),"GUISELECT33",&aStack_252);
  std::string::string((string *)(::KLayoutFunctionNames + 0x178),"GUISELECT34",&aStack_251);
  std::string::string((string *)(::KLayoutFunctionNames + 0x180),"GUISELECT35",&aStack_250);
  std::string::string((string *)(::KLayoutFunctionNames + 0x188),"GUISELECT36",&aStack_24f);
  std::string::string((string *)(::KLayoutFunctionNames + 400),"GUISELECT37",&aStack_24e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x198),"GUISELECT38",&aStack_24d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a0),"GUISELECT39",&aStack_24c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a8),"GUISELECT40",&aStack_24b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b0),"GUISELECT41",&aStack_24a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b8),"GUISELECT42",&aStack_249);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c0),"GUISELECT43",&aStack_248);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c8),"GUISELECT44",&aStack_247);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d0),"GUISELECT45",&aStack_246);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d8),"GUISELECT46",&aStack_245);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e0),"GUISELECT47",&aStack_244);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e8),"GUISELECT48",&aStack_243);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f0),"GUISELECT49",&aStack_242);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f8),"GUISELECT50",&aStack_241);
  std::string::string((string *)(::KLayoutFunctionNames + 0x200),"GUISELECTA",&aStack_240);
  std::string::string((string *)(::KLayoutFunctionNames + 0x208),"GUISELECTB",&aStack_23f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x210),"GUISELECTC",&aStack_23e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x218),"GUISELECTD",&aStack_23d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x220),"GUIFEEDPET",&aStack_23c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x228),"GUIPETPASSIVE",&aStack_23b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x230),"GUIPETAGGRESSIVE",&aStack_23a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x238),"GUIPETDEFENSIVE",&aStack_239);
  std::string::string((string *)(::KLayoutFunctionNames + 0x240),"GUITOGGLEINVENTORY",&aStack_238);
  std::string::string((string *)(::KLayoutFunctionNames + 0x248),"GUITOGGLEQUESTS",&aStack_237);
  std::string::string((string *)(::KLayoutFunctionNames + 0x250),"GUITOGGLESTATS",&aStack_236);
  std::string::string((string *)(::KLayoutFunctionNames + 600),"GUITOGGLESKILLS",&aStack_235);
  std::string::string((string *)(::KLayoutFunctionNames + 0x260),"GUITOGGLEPERKS",&aStack_234);
  std::string::string((string *)(::KLayoutFunctionNames + 0x268),"GUITOGGLEJOURNAL",&aStack_233);
  std::string::string((string *)(::KLayoutFunctionNames + 0x270),"GUITOGGLEPET",&aStack_232);
  std::string::string((string *)(::KLayoutFunctionNames + 0x278),"GUITOGGLEAUTOMAP",&aStack_231);
  std::string::string((string *)(::KLayoutFunctionNames + 0x280),"GUITOGGLEOPTIONS",&aStack_230);
  std::string::string((string *)(::KLayoutFunctionNames + 0x288),"GUITOGGLEITEMNAMES",&aStack_22f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x290),"GUIAUTOMAPZOOMIN",&aStack_22e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x298),"GUIAUTOMAPZOOMOUT",&aStack_22d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a0),"GUILEVELUP",&aStack_22c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a8),"GUISTATSUP",&aStack_22b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b0),"GUISKILLUP",&aStack_22a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b8),"GUIPET1",&aStack_229);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c0),"GUIPET2",&aStack_228);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c8),"GUIPET3",&aStack_227);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d0),"GUIDELETE1",&aStack_226);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d8),"GUIDELETE2",&aStack_225);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e0),"GUIDELETE3",&aStack_224);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e8),"GUIDELETE4",&aStack_223);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f0),"GUISETTINGSMENU",&aStack_222);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f8),"GUIPETSELL",&aStack_221);
  std::string::string((string *)(::KLayoutFunctionNames + 0x300),"NONE",&aStack_220);
  __cxa_atexit(::__tcf_0,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSOUNDBANK_STRINGS,L"STEP_SOUND",&aStack_21f);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 8),L"STRIKE_SOUND",&aStack_21e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x10),L"PHYSICALHIT_SOUND",&aStack_21d);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x18),L"ICEHIT_SOUND",&aStack_21c);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x20),L"FIREHIT_SOUND",&aStack_21b);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x28),L"ELECTRICHIT_SOUND",&aStack_21a);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x30),L"POISONHIT_SOUND",&aStack_219);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x38),L"SHIELDBLOCK",&aStack_218);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x40),L"BLOCK",&aStack_217);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x48),L"CRITICAL_SOUND",&aStack_216);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x50),L"ATTACK_SOUND",&aStack_215);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x58),L"IDLE_SOUND",&aStack_214)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x60),L"DEATH_SOUND",&aStack_213);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x68),L"ROAR_SOUND",&aStack_212)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x70),L"FLEE_SOUND",&aStack_211)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x78),L"MISS_SOUND",&aStack_210)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x80),L"FALL_SOUND",&aStack_20f)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x88),L"LAND_SOUND",&aStack_20e)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x90),L"TAKE_SOUND",&aStack_20d)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x98),L"SPAWN_SOUND",&aStack_20c);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa0),L"USE_SOUND",&aStack_20b);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa8),L"EQUIP_SOUND",&aStack_20a);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb0),L"OPENMENU_SOUND",&aStack_209);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb8),L"BUY_SOUND",&aStack_208);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xc0),L"ERROR_SOUND",&aStack_207);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 200),L"LEVELUP_SOUND",&aStack_206);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd0),L"EFFORT_SOUND",&aStack_205);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd8),L"SPENDPOINT_SOUND",&aStack_204);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe0),L"PORTALENTER_SOUND",&aStack_203);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe8),L"POERTALEXIT_SOUND",&aStack_202);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf0),L"SKILLASSIGN_SOUND",&aStack_201);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf8),L"QUESTRECEIVED_SOUND",&aStack_200);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x100),L"QUESTCOMPLETED_SOUND",&aStack_1ff)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x108),L"LOWMANA_SOUND",&aStack_1fe);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x110),L"MISSILEREFLECT_SOUND",&aStack_1fd)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x118),L"BADEFFECT_SOUND",&aStack_1fc);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x120),L"GOODEFFECT_SOUND",&aStack_1fb);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x128),L"NPCDIALOG_SOUND",&aStack_1fa);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x130),L"NPCGREET",&aStack_1f9);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x138),L"NPCBYE",&aStack_1f8);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x140),L"NPCPURCHASE",&aStack_1f7);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x148),L"NPCSELL",&aStack_1f6);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x150),L"VOICEPETINVENTORYFULL_SOUND",
             &aStack_1f5);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x158),L"VOICEPETDEPARTED_SOUND",
             &aStack_1f4);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x160),L"VOICEPETRETURNED_SOUND",
             &aStack_1f3);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x168),L"VOICEPETFLED_SOUND",&aStack_1f2);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x170),L"VOICEPETLEVELUP_SOUND",&aStack_1f1
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x178),L"VOICEINVENTORYFULL_SOUND",
             &aStack_1f0);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x180),L"VOICEINSUFFICIENTGOLD_SOUND",
             &aStack_1ef);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x188),L"VOICEIMPOSSIBLE_SOUND",&aStack_1ee
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 400),L"VOICECANTCAST_SOUND",&aStack_1ed);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x198),L"VOICECANTCASTHERE_SOUND",
             &aStack_1ec);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a0),L"VOICEHEALTHLOW_SOUND",&aStack_1eb)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a8),L"VOICEMANALOW_SOUND",&aStack_1ea);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b0),L"VOICETRAPSPRUNG_SOUND",&aStack_1e9
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b8),L"VOICEREFRESHED_SOUND",&aStack_1e8)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c0),L"VOICEPOWERFUL_SOUND",&aStack_1e7);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c8),L"VOICEHEALTHY_SOUND",&aStack_1e6);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d0),L"VOICEILL_SOUND",&aStack_1e5);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d8),L"VOICEPOISONED_SOUND",&aStack_1e4);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e0),L"VOICELEVELUP_SOUND",&aStack_1e3);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e8),L"VOICEFAMEUP_SOUND",&aStack_1e2);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f0),L"VOICESKILLUP_SOUND",&aStack_1e1);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f8),L"VOICEFORTUNEGOOD_SOUND",
             &aStack_1e0);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x200),L"VOICEFORTUNEBAD_SOUND",&aStack_1df
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x208),L"VOICESPELLLEARNED_SOUND",
             &aStack_1de);
  ::KSOUNDBANK_STRINGS._528_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_1,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::KALIGNMENT_STRINGS,L"NEUTRAL",&aStack_1dd);
  std::wstring::wstring((wstring_conflict *)&DAT_014ee8a8,L"GOOD",&aStack_1dc);
  std::wstring::wstring((wstring_conflict *)&DAT_014ee8b0,L"EVIL",&aStack_1db);
  std::wstring::wstring((wstring_conflict *)&DAT_014ee8b8,L"ALL",&aStack_1da);
  std::wstring::wstring((wstring_conflict *)&DAT_014ee8c0,L"BERSERK",&aStack_1d9);
  std::wstring::wstring((wstring_conflict *)&DAT_014ee8c8,L"EVILBERSERK",&aStack_1d8);
  std::wstring::wstring((wstring_conflict *)&DAT_014ee8d0,L"GOODBERSERK",&aStack_1d7);
  __cxa_atexit(::__tcf_2,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KAITYPE_STRINGS,L"NORMAL",&aStack_1d6);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 8),L"RANGEDDEFENDER",&aStack_1d5);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x10),L"DEFENDER",&aStack_1d4);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x18),L"RANGEDCASTER",&aStack_1d3);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x20),L"CIRCLER",&aStack_1d2);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x28),L"RESURRECTER",&aStack_1d1);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x30),L"DUMMY",&aStack_1d0);
  __cxa_atexit(::__tcf_3,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gDAMAGE_TYPES,L"Physical",&aStack_1cf);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 8),L"Magical",&aStack_1ce);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x10),L"Fire",&aStack_1cd);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x18),L"Ice",&aStack_1cc);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x20),L"Electric",&aStack_1cb);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x28),L"Poison",&aStack_1ca);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x30),L"All",&aStack_1c9);
  __cxa_atexit(::__tcf_4,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::gTARGET_TYPES,L"USER",&aStack_1c8);
  std::wstring::wstring((wstring_conflict *)&DAT_014ee968,L"ITEM",&aStack_1c7);
  __cxa_atexit(::__tcf_5,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSFXTypeName,L"STATIONARYTARGET",&aStack_1c6);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 8),L"STATIONARYOWNER",&aStack_1c5);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x10),L"STATIONARY",&aStack_1c4);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x18),L"STATIONARYPORTAL",&aStack_1c3)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x20),L"BEAM",&aStack_1c2);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x28),L"FOLLOWOWNER",&aStack_1c1);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x30),L"FOLLOWTARGET",&aStack_1c0);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x38),L"PROJECTILELOCATION",&aStack_1bf);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x40),L"PROJECTILECHARACTER",&aStack_1be);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x48),L"PROJECTILELOCATIONERRATIC",&aStack_1bd);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x50),L"PROJECTILECHARACTERERRATIC",&aStack_1bc);
  __cxa_atexit(::__tcf_6,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KCharacterNames,L"NA",&aStack_1bb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 8),L"NA",&aStack_1ba);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x10),L"NA",&aStack_1b9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x18),L"NA",&aStack_1b8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x20),L"NA",&aStack_1b7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x28),L"NA",&aStack_1b6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x30),L"NA",&aStack_1b5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x38),L"NA",&aStack_1b4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x40),L"Bksp",&aStack_1b3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x48),L"Tab",&aStack_1b2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x50),L"NA",&aStack_1b1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x58),L"NA",&aStack_1b0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x60),L"Ctr",&aStack_1af);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x68),L"Ret",&aStack_1ae);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x70),L"NA",&aStack_1ad);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x78),L"NA",&aStack_1ac);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x80),L"Shift",&aStack_1ab);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x88),L"Ctrl",&aStack_1aa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x90),L"Alt",&aStack_1a9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x98),L"Tab",&aStack_1a8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa0),L"NA",&aStack_1a7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa8),L"NA",&aStack_1a6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb0),L"NA",&aStack_1a5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb8),L"NA",&aStack_1a4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xc0),L"NA",&aStack_1a3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 200),L"NA",&aStack_1a2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd0),L"NA",&aStack_1a1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd8),L"NA",&aStack_1a0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe0),L"NA",&aStack_19f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe8),L"NA",&aStack_19e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf0),L"NA",&aStack_19d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf8),L"NA",&aStack_19c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x100),L"space",&aStack_19b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x108),L"pgup",&aStack_19a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x110),L"pgdn",&aStack_199);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x118),L"end",&aStack_198);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x120),L"home",&aStack_197);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x128),L"left arrow",&aStack_196);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x130),L"up arrow",&aStack_195);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x138),L"right arrow",&aStack_194);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x140),L"down arrow",&aStack_193);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x148),L")",&aStack_192);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x150),L"*",&aStack_191);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x158),L"+",&aStack_190);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x160),L",",&aStack_18f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x168),L"ins",&aStack_18e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x170),L"del",&aStack_18d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x178),L"/",&aStack_18c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x180),L"0",&aStack_18b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x188),L"1",&aStack_18a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 400),L"2",&aStack_189);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x198),L"3",&aStack_188);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a0),L"4",&aStack_187);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a8),L"5",&aStack_186);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b0),L"6",&aStack_185);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b8),L"7",&aStack_184);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c0),L"8",&aStack_183);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c8),L"9",&aStack_182);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d0),L":",&aStack_181);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d8),L";",&aStack_180);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e0),L"<",&aStack_17f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e8),L"=",&aStack_17e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f0),L">",&aStack_17d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f8),L"?",&aStack_17c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x200),L"@",&aStack_17b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x208),L"a",&aStack_17a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x210),L"b",&aStack_179);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x218),L"c",&aStack_178);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x220),L"d",&aStack_177);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x228),L"e",&aStack_176);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x230),L"NA",&aStack_175);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x238),L"g",&aStack_174);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x240),L"h",&aStack_173);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x248),L"i",&aStack_172);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x250),L"j",&aStack_171);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 600),L"k",&aStack_170);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x260),L"l",&aStack_16f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x268),L"m",&aStack_16e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x270),L"n",&aStack_16d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x278),L"o",&aStack_16c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x280),L"p",&aStack_16b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x288),L"NA",&aStack_16a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x290),L"r",&aStack_169);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x298),L"s",&aStack_168);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a0),L"t",&aStack_167);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a8),L"u",&aStack_166);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b0),L"v",&aStack_165);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b8),L"w",&aStack_164);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c0),L"x",&aStack_163);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c8),L"y",&aStack_162);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d0),L"z",&aStack_161);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d8),L"[",&aStack_160);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e0),L"\\",&aStack_15f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e8),L"]",&aStack_15e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f0),L"^",&aStack_15d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f8),L"_",&aStack_15c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x300),L"NUM 0",&aStack_15b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x308),L"NUM 1",&aStack_15a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x310),L"NUM 2",&aStack_159);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x318),L"NUM 3",&aStack_158);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 800),L"NUM 4",&aStack_157);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x328),L"NUM 5",&aStack_156);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x330),L"NUM 6",&aStack_155);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x338),L"NUM 7",&aStack_154);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x340),L"NUM 8",&aStack_153);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x348),L"NUM 9",&aStack_152);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x350),L"*",&aStack_151);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x358),L"+",&aStack_150);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x360),L"NA",&aStack_14f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x368),L"-",&aStack_14e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x370),L"NA",&aStack_14d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x378),L"F1",&aStack_14c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x380),L"F2",&aStack_14b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x388),L"F3",&aStack_14a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x390),L"F4",&aStack_149);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x398),L"F5",&aStack_148);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a0),L"F6",&aStack_147);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a8),L"F7",&aStack_146);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b0),L"F8",&aStack_145);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b8),L"F9",&aStack_144);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c0),L"F10",&aStack_143);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c8),L"F11",&aStack_142);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d0),L"F12",&aStack_141);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d8),L"{",&aStack_140);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3e0),L"|",&aStack_13f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 1000),L"}",&aStack_13e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f0),L"~",&aStack_13d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f8),L";",&aStack_13c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x400),L"=",&aStack_13b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x408),L".",&aStack_13a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x410),L"-",&aStack_139);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x418),L",",&aStack_138);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x420),L"/",&aStack_137);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x428),L"`",&aStack_136);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x430),L"[",&aStack_135);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x438),L"\\",&aStack_134);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x440),L"]",&aStack_133);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x448),L"\'",&aStack_132);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x450),L"NA",&aStack_131);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x458),L"NA",&aStack_130);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x460),L"NA",&aStack_12f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x468),L"NA",&aStack_12e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x470),L"NA",&aStack_12d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x478),L"NA",&aStack_12c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x480),L"NA",&aStack_12b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x488),L"NA",&aStack_12a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x490),L"NA",&aStack_129);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x498),L"NA",&aStack_128);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a0),L"NA",&aStack_127);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a8),L"NA",&aStack_126);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b0),L"NA",&aStack_125);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b8),L"NA",&aStack_124);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c0),L"NA",&aStack_123);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c8),L"NA",&aStack_122);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d0),L"NA",&aStack_121);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d8),L"NA",&aStack_120);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e0),L"NA",&aStack_11f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e8),L"NA",&aStack_11e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f0),L"NA",&aStack_11d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f8),L"NA",&aStack_11c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x500),L"NA",&aStack_11b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x508),L"NA",&aStack_11a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x510),L"NA",&aStack_119);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x518),L"NA",&aStack_118);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x520),L"NA",&aStack_117);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x528),L"NA",&aStack_116);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x530),L"NA",&aStack_115);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x538),L"NA",&aStack_114);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x540),L"NA",&aStack_113);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x548),L"NA",&aStack_112);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x550),L"NA",&aStack_111);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x558),L"NA",&aStack_110);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x560),L"NA",&aStack_10f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x568),L"NA",&aStack_10e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x570),L"NA",&aStack_10d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x578),L"NA",&aStack_10c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x580),L"NA",&aStack_10b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x588),L"NA",&aStack_10a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x590),L"NA",&aStack_109);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x598),L"NA",&aStack_108);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a0),L"NA",&aStack_107);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a8),L"NA",&aStack_106);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b0),L"NA",&aStack_105);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b8),L"NA",&aStack_104);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c0),L"NA",&aStack_103);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c8),L"NA",&aStack_102);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d0),L";",&aStack_101);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d8),L"=",&aStack_100);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e0),L",",&aStack_ff);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e8),L"-",&aStack_fe);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f0),L".",&aStack_fd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f8),L"/",&aStack_fc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x600),L"`",&aStack_fb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x608),L"NA",&aStack_fa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x610),L"NA",&aStack_f9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x618),L"NA",&aStack_f8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x620),L"NA",&aStack_f7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x628),L"NA",&aStack_f6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x630),L"NA",&aStack_f5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x638),L"NA",&aStack_f4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x640),L"NA",&aStack_f3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x648),L"NA",&aStack_f2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x650),L"NA",&aStack_f1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x658),L"NA",&aStack_f0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x660),L"NA",&aStack_ef);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x668),L"NA",&aStack_ee);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x670),L"NA",&aStack_ed);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x678),L"NA",&aStack_ec);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x680),L"NA",&aStack_eb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x688),L"NA",&aStack_ea);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x690),L"NA",&aStack_e9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x698),L"NA",&aStack_e8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a0),L"NA",&aStack_e7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a8),L"NA",&aStack_e6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b0),L"NA",&aStack_e5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b8),L"NA",&aStack_e4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c0),L"NA",&aStack_e3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c8),L"NA",&aStack_e2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d0),L"NA",&aStack_e1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d8),L"[",&aStack_e0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e0),L"\\",&aStack_df);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e8),L"]",&aStack_de);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f0),L"\'",&aStack_dd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f8),L"NA",&aStack_dc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x700),L"NA",&aStack_db);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x708),L"NA",&aStack_da);
  __cxa_atexit(::__tcf_7,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_EVENT_TYPE_NAMES,L"EVENT_START",&aStack_d9);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 8),L"EVENT_END",&aStack_d8)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x10),L"EVENT_TRIGGER",&aStack_d7);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x18),L"EVENT_TRIGGER_TWO",&aStack_d6)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x20),L"EVENT_UNITHIT",&aStack_d5);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x28),L"EVENT_UNITDIE",&aStack_d4);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x30),L"EVENT_MISSILEHIT",&aStack_d3);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x38),L"EVENT_MISSILEDIE",&aStack_d2);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x40),L"EVENT_DIEBYEFFECT",&aStack_d1)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x48),L"EVENT_CASTERDIE",&aStack_d0);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x50),L"EVENT_UNIT_CREATE",&aStack_cf)
  ;
  __cxa_atexit(::__tcf_8,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_TARGET_TYPE_NAMES,L"NONE",&aStack_ce);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 8),L"POSITION",&aStack_cd)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x10),L"TARGET",&aStack_cc);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x18),L"SELF",&aStack_cb);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x20),L"EVERYBODY",&aStack_ca);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x28),L"POSITIONRANDOM",&aStack_c9);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x30),L"POSITIONFLEE",&aStack_c8);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x38),L"ITEM",&aStack_c7);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x40),L"UNIDENTIFIEDITEM",&aStack_c6)
  ;
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x48),L"PETS",&aStack_c5);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x50),L"SELFANDPETS",&aStack_c4);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x58),L"TARGET_POS",&aStack_c3);
  __cxa_atexit(::__tcf_9,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::gSKILL_ACTIVATION_TYPE_NAMES,L"ANY",&aStack_c2);
  std::wstring::wstring((wstring_conflict *)&DAT_014ef1c8,L"PROC",&aStack_c1);
  std::wstring::wstring((wstring_conflict *)&DAT_014ef1d0,L"WEAPON",&aStack_c0);
  std::wstring::wstring((wstring_conflict *)&DAT_014ef1d8,L"NORMAL",&aStack_bf);
  std::wstring::wstring((wstring_conflict *)&DAT_014ef1e0,L"PASSIVE",&aStack_be);
  __cxa_atexit(::__tcf_10,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::gSKILL_TYPE_NAMES,L"SKILL",&aStack_bd);
  std::wstring::wstring((wstring_conflict *)&DAT_014ef208,L"OFFENSIVE",&aStack_bc);
  std::wstring::wstring((wstring_conflict *)&DAT_014ef210,L"DEFENSIVE",&aStack_bb);
  std::wstring::wstring((wstring_conflict *)&DAT_014ef218,L"CHARM",&aStack_ba);
  DAT_014ef220 = &DAT_01424558;
  __cxa_atexit(::__tcf_11,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_TYPE_DISPLAY_NAMES,L"Class Skill",&aStack_b9);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TYPE_DISPLAY_NAMES + 8),L"Offensive Spell",&aStack_b8);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TYPE_DISPLAY_NAMES + 0x10),L"Defensive Spell",&aStack_b7)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TYPE_DISPLAY_NAMES + 0x18),L"Charm Spell",&aStack_b6);
  ::gSKILL_TYPE_DISPLAY_NAMES._32_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_12,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_BONE_ATTACHMENT_NAMES,L"",&aStack_b5);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 8),L"CENTER",&aStack_b4);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x10),L"HEAD",&aStack_b3);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x18),L"RIGHTHAND",&aStack_b2);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x20),L"LEFTHAND",&aStack_b1);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x28),L"RIGHTSHOULDER",&aStack_b0
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x30),L"LEFTSHOULDER",&aStack_af)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x38),L"POSITION",&aStack_ae);
  __cxa_atexit(::__tcf_13,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEffect_Activation_Names,L"PASSIVE",&aStack_ad);
  std::wstring::wstring((wstring_conflict *)(::gEffect_Activation_Names + 8),L"DYNAMIC",&aStack_ac);
  std::wstring::wstring
            ((wstring_conflict *)(::gEffect_Activation_Names + 0x10),L"TRANSFER",&aStack_ab);
  __cxa_atexit(::__tcf_14,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEFFECT_STAT_MODIFIER_NAMES,L"MELEE",&aStack_aa);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 8),L"RANGED",&aStack_a9);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x10),L"DEFENSE",&aStack_a8);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x18),L"MAGIC",&aStack_a7);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x20),L"LEVEL",&aStack_a6);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x28),L"OWNERLEVEL",&aStack_a5);
  __cxa_atexit(::__tcf_15,0,&__dso_handle);
  std::string::string((string *)::gEFFECT_STAT_MODIFIER_ICON_NAMES,"iconmelee",&aStack_a4);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 8),"iconranged",&aStack_a3);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x10),"icondefense",&aStack_a2
                     );
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x18),"iconmagic",&aStack_a1);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x20),"iconmagic",&aStack_a0);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x28),"iconmagic",&aStack_9f);
  __cxa_atexit(::__tcf_16,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEDITOR_EVENT_NAMES,L"STOP",&aStack_9e);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 8),L"PLAY",&aStack_9d);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x10),L"RELOAD TILES",&aStack_9c);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x18),L"TOGGLE LIGHTING",&aStack_9b);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x20),L"SELECT COLLIDABLE",&aStack_9a);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x28),L"PAUSE PARTICLES",&aStack_99);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x30),L"UNPAUSE PARTICLES",&aStack_98);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x38),L"COLLISION ALL",&aStack_97);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x40),L"COLLISION MODELS",&aStack_96);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x48),L"COLLISION PREFABS",&aStack_95);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x50),L"COLLISION ROOMPIECES",&aStack_94);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x58),L"COLLISION ROOMPROPS",&aStack_93);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x60),L"RELOAD GRAPHS",&aStack_92);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x68),L"TOGGLE PLAYER LIGHT",&aStack_91);
  __cxa_atexit(::__tcf_17,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEDITOR_FLAG_NAMES,L"LOGIC ENABLED",&aStack_90);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 8),L"INGAME MODE",&aStack_8f);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x10),L"SHOW STATS",&aStack_8e);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x18),L"EDIT POSITION",&aStack_8d);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x20),L"EDIT SCALE",&aStack_8c);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x28),L"EDIT ORIENTATION",&aStack_8b);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x30),L"EDIT NONE",&aStack_8a);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x38),L"SHOW HELPERS",&aStack_89);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x40),L"SHOW GRID",&aStack_88);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x48),L"SHOW WORKING PLANE",&aStack_87);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x50),L"SNAP TO GRID",&aStack_86);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x58),L"SUSPEND EDITOR",&aStack_85);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x60),L"LIGHTING VISIBLE",&aStack_84);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x68),L"RECALCULATE LIGHTING",&aStack_83);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x70),L"SHOW EDGES",&aStack_82);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x78),L"UPDATE PARTICLES CIRCLE",&aStack_81
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x80),L"SHOW LOGIC OUTPUT",&aStack_80);
  __cxa_atexit(::__tcf_18,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::gEDITOR_UPDATE_MASKS,L"OBJECT SELECTION CHANGED",&aStack_7f);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 8),L"OBJECT DATA CHANGED",&aStack_7e);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 0x10),L"OBJECTS CREATED",&aStack_7d);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 0x18),L"REFRESH TREE VIEW",&aStack_7c);
  __cxa_atexit(::__tcf_19,0,&__dso_handle);
  ParticleUniverse::HALFSCALE._4_4_ = DAT_0142463c * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._0_4_ = Ogre::Vector3::UNIT_SCALE * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._8_4_ = DAT_00fa4810 * DAT_01424640;
  std::string::string((string *)&ParticleUniverse::ALIAS,"1",&aStack_7b);
  __cxa_atexit(std::string::~string,&ParticleUniverse::ALIAS,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::SYSTEM,"2",&aStack_7a);
  __cxa_atexit(std::string::~string,&ParticleUniverse::SYSTEM,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::TECHNIQUE,"3",&aStack_79);
  __cxa_atexit(std::string::~string,&ParticleUniverse::TECHNIQUE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::RENDERER,"4",&aStack_78);
  __cxa_atexit(std::string::~string,&ParticleUniverse::RENDERER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EMITTER,"5",&aStack_77);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EMITTER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::AFFECTOR,"6",&aStack_76);
  __cxa_atexit(std::string::~string,&ParticleUniverse::AFFECTOR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::OBSERVER,"7",&aStack_75);
  __cxa_atexit(std::string::~string,&ParticleUniverse::OBSERVER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::HANDLER,"8",&aStack_74);
  __cxa_atexit(std::string::~string,&ParticleUniverse::HANDLER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::BEHAVIOUR,"9",&aStack_73);
  __cxa_atexit(std::string::~string,&ParticleUniverse::BEHAVIOUR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EXTERN,"10",&aStack_72);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EXTERN,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DYNAMIC_ATTRIBUTE,"11",&aStack_71);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DYNAMIC_ATTRIBUTE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DEPENDENCY,"12",&aStack_70);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DEPENDENCY,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_LAYOUT_TYPE_NAMES,L"NORMAL",&aStack_6f);
  std::wstring::wstring((wstring_conflict *)(::g_LAYOUT_TYPE_NAMES + 8),L"PARTICLE",&aStack_6e);
  std::wstring::wstring((wstring_conflict *)(::g_LAYOUT_TYPE_NAMES + 0x10),L"TIMELINE",&aStack_6d);
  std::wstring::wstring((wstring_conflict *)(::g_LAYOUT_TYPE_NAMES + 0x18),L"TRIGGER",&aStack_6c);
  __cxa_atexit(::__tcf_20,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_TYPE_NAMES,L"",&aStack_6b);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 8),L"FIND",&aStack_6a);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x10),L"KILL NUM",&aStack_69);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x18),L"KILL BOSS",&aStack_68);
  __cxa_atexit(::__tcf_21,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_DIALOG_TYPE_NAMES,L"ERROR",&aStack_67);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 8),L"INTRO",&aStack_66);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x10),L"RETURN",&aStack_65);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x18),L"COMPLETE",&aStack_64);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x20),L"PASSIVE",&aStack_63);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x28),L"DETAILS",&aStack_62);
  __cxa_atexit(::__tcf_22,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)OGRE_UTILITIES::gPRIMITIVE_NAMES,L"SPHERE",&aStack_61);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 8),L"BOX",&aStack_60);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x10),L"PLANE",&aStack_5f);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x18),L"CYLINDER",&aStack_5e);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x20),L"CONE",&aStack_5d);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x28),L"ARROW",&aStack_5c);
  __cxa_atexit(::__tcf_23,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gKEYFRAME_TYPES,L"HIT",&aStack_5b);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 8),L"BLENDIN",&aStack_5a);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x10),L"BLENDOUT",&aStack_59);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x18),L"PLAYSOUND",&aStack_58);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x20),L"SPAWNPARTICLE",&aStack_57);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x28),L"SPAWNPARTICLE_STOP_ON_DEATH",
             &aStack_56);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x30),L"FOOTSTEP",&aStack_55);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x38),L"SHOWWEAPONTRAIL",&aStack_54);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x40),L"HIDEWEAPONTRAIL",&aStack_53);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x48),L"ATTACKSOUND",&aStack_52);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x50),L"ENABLECOLLISION",&aStack_51);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x58),L"DISABLECOLLISION",&aStack_50);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x60),L"REMOVEPARTICLES",&aStack_4f);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x68),L"REMOVEANIMATIONPARTICLES",&aStack_4e);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x70),L"CAMERASHAKE",&aStack_4d);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x78),L"ATTACKEND",&aStack_4c);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x80),L"UNTARGETABLE",&aStack_4b);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x88),L"TARGETABLE",&aStack_4a);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x90),L"DAMPVELOCITY",&aStack_49);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x98),L"UNDAMPVELOCITY",&aStack_48)
  ;
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xa0),L"SHOWWEAPONS",&aStack_47);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xa8),L"HIDEWEAPONS",&aStack_46);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xb0),L"HIDEMESH",&aStack_45);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xb8),L"SHOWMESH",&aStack_44);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xc0),L"FADEOUTMESH",&aStack_43);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 200),L"FADEINMESH",&aStack_42);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0xd0),L"CAMERASHAKE_NO_FALLOFF",&aStack_41);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0xd8),L"PLAYSOUND_NO_FALLOFF",&aStack_40);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xe0),L"HITTWO",&aStack_3f);
  __cxa_atexit(::__tcf_24,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES,"tag_righthand",&aStack_3e);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 8),"tag_lefthand",&aStack_3d);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x10),"",&aStack_3c);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x18),"Bip01 Head",&aStack_3b);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x20),"",&aStack_3a);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x28),"Bip01 L Clavicle",&aStack_39);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x30),"",&aStack_38);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x38),"",&aStack_37);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x40),"",&aStack_36);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x48),"",&aStack_35);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x50),"",&aStack_34);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x58),"tag_leftarm",&aStack_33);
  __cxa_atexit(::__tcf_25,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES_SECONDARY,"",&aStack_32);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 8),"",&aStack_31);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x10),"",&aStack_30);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x18),"",&aStack_2f);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x20),"",&aStack_2e);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x28),"Bip01 R Clavicle",
                      &aStack_2d);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x30),"",&aStack_2c);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x38),"",&aStack_2b);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x40),"",&aStack_2a);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x48),"",&aStack_29);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x50),"",&aStack_28);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x58),"",&aStack_27);
  __cxa_atexit(::__tcf_26,0,&__dso_handle);
  std::string::string((string *)::KEquipmentIconName,"EquipLeftHand",&aStack_26);
  std::string::string((string *)(::KEquipmentIconName + 8),"EquipRightHand",&aStack_25);
  std::string::string((string *)(::KEquipmentIconName + 0x10),"EquipGloves",&aStack_24);
  std::string::string((string *)(::KEquipmentIconName + 0x18),"EquipHelm",&aStack_23);
  std::string::string((string *)(::KEquipmentIconName + 0x20),"EquipChest",&aStack_22);
  std::string::string((string *)(::KEquipmentIconName + 0x28),"EquipShoulder",&aStack_21);
  std::string::string((string *)(::KEquipmentIconName + 0x30),"EquipBoots",&aStack_20);
  std::string::string((string *)(::KEquipmentIconName + 0x38),"EquipBelt",&aStack_1f);
  std::string::string((string *)(::KEquipmentIconName + 0x40),"EquipRing1",&aStack_1e);
  std::string::string((string *)(::KEquipmentIconName + 0x48),"EquipRing2",&aStack_1d);
  std::string::string((string *)(::KEquipmentIconName + 0x50),"EquipAmulet",&aStack_1c);
  std::string::string((string *)(::KEquipmentIconName + 0x58),"",&aStack_1b);
  __cxa_atexit(::__tcf_27,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames,L"CHEST",&aStack_1a);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 8),L"GLOVES",&aStack_19);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x10),L"BOOTS",&aStack_18);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x18),L"HELMET",&aStack_17);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x20),L"SHOULDERS",&aStack_16);
  __cxa_atexit(::__tcf_28,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames2,L"",&aStack_15);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 8),L"",&aStack_14);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x10),L"",&aStack_13);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x18),L"FACE",&aStack_12);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x20),L"",&aStack_11);
  __cxa_atexit(::__tcf_29,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gRESOURCE_GROUP_NAMES,L"ITEMS",&aStack_10);
  std::wstring::wstring((wstring_conflict *)(::gRESOURCE_GROUP_NAMES + 8),L"MONSTERS",&aStack_f);
  std::wstring::wstring((wstring_conflict *)(::gRESOURCE_GROUP_NAMES + 0x10),L"PLAYERS",&aStack_e);
  std::wstring::wstring((wstring_conflict *)(::gRESOURCE_GROUP_NAMES + 0x18),L"PROPS",&aStack_d);
  __cxa_atexit(::__tcf_30,0,&__dso_handle);
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
  __cxa_atexit(::__tcf_31,0,&__dso_handle);
  return;
}



/* address=00ca4a00
   symbol=CSkill::assignSkillAnimations */

/* WARNING: Removing unreachable block (ram,0x00ca5203) */
/* WARNING: Removing unreachable block (ram,0x00ca51f8) */
/* WARNING: Removing unreachable block (ram,0x00ca5297) */
/* CSkill::assignSkillAnimations(CBaseUnit*) */

void __thiscall CSkill::assignSkillAnimations(CSkill *this,CBaseUnit *param_1)

{
  int *piVar1;
  char cVar2;
  int iVar3;
  CGenericModel *this_00;
  long lVar4;
  CBaseUnit *pCVar5;
  CCharacter *this_01;
  long lVar6;
  long lVar7;
  char *pcVar8;
  char *pcVar9;
  bool bVar10;
  byte bVar11;
  float fVar12;
  undefined4 uVar13;
  long local_a8 [2];
  string local_98 [16];
  string local_88 [16];
  string local_78 [16];
  string local_68 [16];
  string local_58 [16];
  string local_48 [26];
  allocator local_2e;
  allocator local_2d;
  allocator local_2c;
  allocator local_2b;
  allocator local_2a;
  allocator local_29;

  bVar11 = 0;
  if (param_1 == (CBaseUnit *)0x0) {
    return;
  }
  if (*(long *)(this + 0x90) == 0) {
    return;
  }
  this_00 = (CGenericModel *)(**(code **)(*(long *)param_1 + 0x1e0))(param_1);
  if (this_00 == (CGenericModel *)0x0) {
    *(undefined4 *)(this + 0xe4) = 0xffffffff;
    *(undefined4 *)(this + 0xe8) = 0xffffffff;
    *(undefined4 *)(this + 0xec) = 0xffffffff;
    *(undefined4 *)(this + 0xf0) = 0xffffffff;
    *(undefined4 *)(this + 0x100) = 0x3f800000;
    return;
  }
  lVar4 = __dynamic_cast(param_1,&CBaseUnit::typeinfo,&CCharacter::typeinfo,0);
  if (lVar4 == 0) {
    lVar6 = *(long *)(this + 0x90);
  }
  else {
    lVar6 = *(long *)(this + 0x90);
    if ((*(char *)(lVar6 + 0xb5) != '\0') && (*(CInventory **)(lVar4 + 0x490) != (CInventory *)0x0))
    {
      pCVar5 = (CBaseUnit *)CInventory::getEquipmentEquippedAt(*(CInventory **)(lVar4 + 0x490),0);
      lVar4 = CInventory::getEquipmentEquippedAt(*(CInventory **)(lVar4 + 0x490),1);
      if ((pCVar5 == (CBaseUnit *)0x0) ||
         (cVar2 = CBaseUnit::ISA(pCVar5,*(undefined4 *)(*(long *)(this + 0x90) + 0x10)),
         cVar2 == '\0')) {
        if (lVar4 == 0) {
          iVar3 = *(int *)(this + 0xe4);
          goto LAB_00ca4de4;
        }
        lVar4 = *(long *)(lVar4 + 0x2a8);
      }
      else {
        lVar4 = *(long *)(pCVar5 + 0x2a0);
      }
      iVar3 = CGenericModel::findRandomAnimation(this_00,(string *)(lVar4 + 0x10));
      *(int *)(this + 0xe8) = iVar3;
      *(int *)(this + 0xe4) = iVar3;
LAB_00ca4de4:
      if (iVar3 == -1) {
                    /* try { // try from 00ca4f52 to 00ca4f56 has its CatchHandler @ 00ca5282 */
        std::string::string(local_48,"ATTACK",&local_29);
                    /* try { // try from 00ca4f5d to 00ca4f61 has its CatchHandler @ 00ca527c */
        uVar13 = CGenericModel::findRandomAnimation(this_00,local_48);
        *(undefined4 *)(this + 0xe8) = uVar13;
        *(undefined4 *)(this + 0xe4) = uVar13;
                    /* try { // try from 00ca4f71 to 00ca4f75 has its CatchHandler @ 00ca5282 */
        std::string::~string(local_48);
        iVar3 = *(int *)(this + 0xe4);
        if (iVar3 == -1) {
                    /* try { // try from 00ca4f97 to 00ca4f9b has its CatchHandler @ 00ca5277 */
          std::string::string(local_58,"RSLASH",&local_2a);
                    /* try { // try from 00ca4fa2 to 00ca4fa6 has its CatchHandler @ 00ca5266 */
          uVar13 = CGenericModel::findRandomAnimation(this_00,local_58);
          *(undefined4 *)(this + 0xe8) = uVar13;
          *(undefined4 *)(this + 0xe4) = uVar13;
                    /* try { // try from 00ca4fb6 to 00ca4fba has its CatchHandler @ 00ca5277 */
          std::string::~string(local_58);
          iVar3 = *(int *)(this + 0xe4);
          if (iVar3 == -1) {
            return;
          }
        }
      }
      uVar13 = CGenericModel::getAnimationLengthSeconds(this_00,iVar3);
      *(undefined4 *)(this + 0x100) = uVar13;
      return;
    }
  }
  lVar4 = *(long *)(*(char **)(lVar6 + 0xf8) + -0x18);
  if (lVar4 == *(long *)(::EMPTY_STRING + -0x18)) {
    bVar10 = true;
    lVar7 = lVar4;
    pcVar8 = *(char **)(lVar6 + 0xf8);
    pcVar9 = ::EMPTY_STRING;
    do {
      if (lVar7 == 0) break;
      lVar7 = lVar7 + -1;
      bVar10 = *pcVar8 == *pcVar9;
      pcVar8 = pcVar8 + (ulong)bVar11 * -2 + 1;
      pcVar9 = pcVar9 + (ulong)bVar11 * -2 + 1;
    } while (bVar10);
    if (!bVar10) goto LAB_00ca4b03;
  }
  else {
LAB_00ca4b03:
    if (*(long *)(*(wchar_t **)(this + 0x128) + -6) == 0) {
      std::string::string((string *)local_a8,(string *)(lVar6 + 0xf8));
    }
    else {
      STRINGS::StringConvertToNarrow((STRINGS *)local_a8,*(wchar_t **)(this + 0x128));
    }
                    /* try { // try from 00ca4b23 to 00ca4b4a has its CatchHandler @ 00ca5286 */
    iVar3 = CGenericModel::getAnimationIndex(this_00,(string *)local_a8);
    *(int *)(this + 0xe8) = iVar3;
    *(int *)(this + 0xe4) = iVar3;
    if (iVar3 == -1) {
                    /* try { // try from 00ca4fd6 to 00ca4fda has its CatchHandler @ 00ca5286 */
      iVar3 = CGenericModel::findRandomAnimation(this_00,(string *)local_a8);
      *(int *)(this + 0xe8) = iVar3;
      *(int *)(this + 0xe4) = iVar3;
      if (iVar3 != -1) goto LAB_00ca4b3d;
                    /* try { // try from 00ca5002 to 00ca5006 has its CatchHandler @ 00ca5245 */
      std::string::string(local_68,"ATTACK",&local_2b);
                    /* try { // try from 00ca500d to 00ca5011 has its CatchHandler @ 00ca5243 */
      uVar13 = CGenericModel::findRandomAnimation(this_00,local_68);
      *(undefined4 *)(this + 0xe8) = uVar13;
      *(undefined4 *)(this + 0xe4) = uVar13;
                    /* try { // try from 00ca5021 to 00ca5025 has its CatchHandler @ 00ca5245 */
      std::string::~string(local_68);
      iVar3 = *(int *)(this + 0xe4);
      if (iVar3 != -1) goto LAB_00ca4b43;
                    /* try { // try from 00ca5047 to 00ca504b has its CatchHandler @ 00ca5241 */
      std::string::string(local_78,"RSLASH",&local_2c);
                    /* try { // try from 00ca5052 to 00ca5056 has its CatchHandler @ 00ca5234 */
      uVar13 = CGenericModel::findRandomAnimation(this_00,local_78);
      *(undefined4 *)(this + 0xe8) = uVar13;
      *(undefined4 *)(this + 0xe4) = uVar13;
                    /* try { // try from 00ca5066 to 00ca506a has its CatchHandler @ 00ca5241 */
      std::string::~string(local_78);
      iVar3 = *(int *)(this + 0xe4);
      if (iVar3 != -1) goto LAB_00ca4b43;
    }
    else {
LAB_00ca4b3d:
      iVar3 = *(int *)(this + 0xe4);
LAB_00ca4b43:
      uVar13 = CGenericModel::getAnimationLengthSeconds(this_00,iVar3);
      *(undefined4 *)(this + 0x100) = uVar13;
    }
    if ((allocator *)(local_a8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_a8[0] + -8);
      iVar3 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar3 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
      }
    }
    lVar6 = *(long *)(this + 0x90);
    lVar4 = *(long *)(::EMPTY_STRING + -0x18);
  }
  lVar7 = *(long *)(*(char **)(lVar6 + 0x108) + -0x18);
  if (lVar7 == lVar4) {
    bVar10 = true;
    pcVar8 = *(char **)(lVar6 + 0x108);
    pcVar9 = ::EMPTY_STRING;
    do {
      if (lVar4 == 0) break;
      lVar4 = lVar4 + -1;
      bVar10 = *pcVar8 == *pcVar9;
      pcVar8 = pcVar8 + (ulong)bVar11 * -2 + 1;
      pcVar9 = pcVar9 + (ulong)bVar11 * -2 + 1;
    } while (bVar10);
    if (!bVar10) goto LAB_00ca4b8e;
  }
  else {
LAB_00ca4b8e:
    if (*(long *)(*(wchar_t **)(this + 0x138) + -6) == 0) {
      std::string::string((string *)local_a8,(string *)(lVar6 + 0x108));
    }
    else {
      STRINGS::StringConvertToNarrow((STRINGS *)local_a8,*(wchar_t **)(this + 0x138));
    }
                    /* try { // try from 00ca4bb5 to 00ca4bb9 has its CatchHandler @ 00ca5292 */
    iVar3 = CGenericModel::getAnimationIndex(this_00,(string *)local_a8);
    *(int *)(this + 0xf0) = iVar3;
    *(int *)(this + 0xec) = iVar3;
    if (iVar3 == -1) {
                    /* try { // try from 00ca4ef6 to 00ca4efa has its CatchHandler @ 00ca5292 */
      uVar13 = CGenericModel::findRandomAnimation(this_00,(string *)local_a8);
      *(undefined4 *)(this + 0xf0) = uVar13;
      *(undefined4 *)(this + 0xec) = uVar13;
    }
    if ((allocator *)(local_a8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_a8[0] + -8);
      iVar3 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar3 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
      }
    }
    lVar6 = *(long *)(this + 0x90);
    lVar7 = *(long *)(::EMPTY_STRING + -0x18);
  }
  if (*(long *)(*(char **)(lVar6 + 0x110) + -0x18) == lVar7) {
    bVar10 = true;
    pcVar8 = *(char **)(lVar6 + 0x110);
    pcVar9 = ::EMPTY_STRING;
    do {
      if (lVar7 == 0) break;
      lVar7 = lVar7 + -1;
      bVar10 = *pcVar8 == *pcVar9;
      pcVar8 = pcVar8 + (ulong)bVar11 * -2 + 1;
      pcVar9 = pcVar9 + (ulong)bVar11 * -2 + 1;
    } while (bVar10);
    if (!bVar10) goto LAB_00ca4c07;
  }
  else {
LAB_00ca4c07:
    if (*(long *)(*(wchar_t **)(this + 0x148) + -6) == 0) {
      std::string::string((string *)local_a8,(string *)(lVar6 + 0x110));
    }
    else {
      STRINGS::StringConvertToNarrow((STRINGS *)local_a8,*(wchar_t **)(this + 0x148));
    }
                    /* try { // try from 00ca4c2e to 00ca4c32 has its CatchHandler @ 00ca5284 */
    iVar3 = CGenericModel::getAnimationIndex(this_00,(string *)local_a8);
    *(int *)(this + 0xf4) = iVar3;
    if (iVar3 == -1) {
                    /* try { // try from 00ca4f2e to 00ca4f32 has its CatchHandler @ 00ca5284 */
      uVar13 = CGenericModel::findRandomAnimation(this_00,(string *)local_a8);
      *(undefined4 *)(this + 0xf4) = uVar13;
    }
    if ((allocator *)(local_a8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_a8[0] + -8);
      iVar3 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar3 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
      }
    }
  }
  this_01 = (CCharacter *)__dynamic_cast(param_1,&CBaseUnit::typeinfo,&CCharacter::typeinfo,0);
  if (this_01 == (CCharacter *)0x0) {
    return;
  }
  pCVar5 = (CBaseUnit *)CCharacter::getWeaponInLeftHand(this_01);
  if (pCVar5 == (CBaseUnit *)0x0) {
    return;
  }
  cVar2 = CBaseUnit::ISA(pCVar5,*(undefined4 *)(*(long *)(this + 0x90) + 0x14));
  if (cVar2 == '\0') {
    return;
  }
  lVar4 = *(long *)(this + 0x90);
  lVar6 = *(long *)(*(char **)(lVar4 + 0x100) + -0x18);
  if (lVar6 == *(long *)(::EMPTY_STRING + -0x18)) {
    bVar10 = true;
    lVar7 = lVar6;
    pcVar8 = *(char **)(lVar4 + 0x100);
    pcVar9 = ::EMPTY_STRING;
    do {
      if (lVar7 == 0) break;
      lVar7 = lVar7 + -1;
      bVar10 = *pcVar8 == *pcVar9;
      pcVar8 = pcVar8 + (ulong)bVar11 * -2 + 1;
      pcVar9 = pcVar9 + (ulong)bVar11 * -2 + 1;
    } while (bVar10);
    if (bVar10) goto LAB_00ca4d35;
  }
  if (*(long *)(*(long *)(this + 0x138) + -0x18) == 0) {
    std::string::string((string *)local_a8,(string *)(lVar4 + 0x100));
  }
  else {
    STRINGS::StringConvertToNarrow((STRINGS *)local_a8,*(wchar_t **)(this + 0x130));
  }
                    /* try { // try from 00ca4ce9 to 00ca4d0a has its CatchHandler @ 00ca5221 */
  iVar3 = CGenericModel::getAnimationIndex(this_00,(string *)local_a8);
  *(int *)(this + 0xe8) = iVar3;
  if (iVar3 == -1) {
                    /* try { // try from 00ca50e2 to 00ca50e6 has its CatchHandler @ 00ca5221 */
    iVar3 = CGenericModel::findRandomAnimation(this_00,(string *)local_a8);
    *(int *)(this + 0xe8) = iVar3;
    if (iVar3 != -1) goto LAB_00ca4cfd;
                    /* try { // try from 00ca5108 to 00ca510c has its CatchHandler @ 00ca5264 */
    std::string::string(local_88,"ATTACK",&local_2d);
                    /* try { // try from 00ca5113 to 00ca5117 has its CatchHandler @ 00ca5262 */
    uVar13 = CGenericModel::findRandomAnimation(this_00,local_88);
    *(undefined4 *)(this + 0xe8) = uVar13;
                    /* try { // try from 00ca5121 to 00ca5125 has its CatchHandler @ 00ca5264 */
    std::string::~string(local_88);
    iVar3 = *(int *)(this + 0xe8);
    if (iVar3 != -1) goto LAB_00ca4d03;
                    /* try { // try from 00ca5147 to 00ca514b has its CatchHandler @ 00ca525f */
    std::string::string(local_98,"RSLASH",&local_2e);
                    /* try { // try from 00ca5152 to 00ca5156 has its CatchHandler @ 00ca5252 */
    uVar13 = CGenericModel::findRandomAnimation(this_00,local_98);
    *(undefined4 *)(this + 0xe8) = uVar13;
                    /* try { // try from 00ca5160 to 00ca5164 has its CatchHandler @ 00ca525f */
    std::string::~string(local_98);
    iVar3 = *(int *)(this + 0xe8);
    if (iVar3 != -1) goto LAB_00ca4d03;
  }
  else {
LAB_00ca4cfd:
    iVar3 = *(int *)(this + 0xe8);
LAB_00ca4d03:
    fVar12 = (float)CGenericModel::getAnimationLengthSeconds(this_00,iVar3);
    if (fVar12 <= *(float *)(this + 0x100)) {
      fVar12 = *(float *)(this + 0x100);
    }
    *(float *)(this + 0x100) = fVar12;
  }
  std::string::~string((string *)local_a8);
  lVar4 = *(long *)(this + 0x90);
  lVar6 = *(long *)(::EMPTY_STRING + -0x18);
LAB_00ca4d35:
  if (*(long *)(*(char **)(lVar4 + 0x118) + -0x18) == lVar6) {
    bVar10 = true;
    pcVar8 = *(char **)(lVar4 + 0x118);
    pcVar9 = ::EMPTY_STRING;
    do {
      if (lVar6 == 0) break;
      lVar6 = lVar6 + -1;
      bVar10 = *pcVar8 == *pcVar9;
      pcVar8 = pcVar8 + (ulong)bVar11 * -2 + 1;
      pcVar9 = pcVar9 + (ulong)bVar11 * -2 + 1;
    } while (bVar10);
    if (bVar10) {
      return;
    }
  }
  if (*(long *)(*(wchar_t **)(this + 0x140) + -6) == 0) {
    std::string::string((string *)local_a8,(string *)(lVar4 + 0x118));
  }
  else {
    STRINGS::StringConvertToNarrow((STRINGS *)local_a8,*(wchar_t **)(this + 0x140));
  }
                    /* try { // try from 00ca4d6d to 00ca4d71 has its CatchHandler @ 00ca520e */
  iVar3 = CGenericModel::getAnimationIndex(this_00,(string *)local_a8);
  *(int *)(this + 0xf0) = iVar3;
  if (iVar3 == -1) {
                    /* try { // try from 00ca50cc to 00ca50d0 has its CatchHandler @ 00ca520e */
    uVar13 = CGenericModel::findRandomAnimation(this_00,(string *)local_a8);
    *(undefined4 *)(this + 0xf0) = uVar13;
  }
  std::string::~string((string *)local_a8);
  return;
}



/* address=00ca52b0
   symbol=CSkill::getSkillLevelDescription */

/* CSkill::getSkillLevelDescription(CBaseUnit*, unsigned int) */

CBaseUnit * CSkill::getSkillLevelDescription(CBaseUnit *param_1,uint param_2)

{
  TSafePointer<CBaseUnit> *this;
  uint uVar1;
  CRunicCore *this_00;
  undefined4 uVar2;
  long *plVar3;
  int in_ECX;
  uint uVar4;
  CRunicCore *in_RDX;
  undefined4 in_register_00000034;
  long lVar5;
  long lVar6;
  uint uVar7;

  lVar5 = CONCAT44(in_register_00000034,param_2);
  if (*(long *)(lVar5 + 0x90) != 0) {
    this_00 = *(CRunicCore **)(lVar5 + 0x30);
    this = (TSafePointer<CBaseUnit> *)(lVar5 + 0x30);
    if (in_RDX != this_00) {
      if (this_00 != (CRunicCore *)0x0) {
        CRunicCore::removeSafePointer(this_00,(TSafePointer *)this,*(uint *)(lVar5 + 0x38));
      }
      *(undefined8 *)(lVar5 + 0x30) = 0;
      if (in_RDX != (CRunicCore *)0x0) {
        uVar2 = CRunicCore::addSafePointer(in_RDX,(TSafePointer *)this);
        *(undefined4 *)(lVar5 + 0x38) = uVar2;
      }
      *(CRunicCore **)(lVar5 + 0x30) = in_RDX;
    }
    uVar7 = in_ECX - 1;
    if (0xfffffffd < uVar7) {
      uVar7 = *(int *)(lVar5 + 0xe0) - 1;
    }
    uVar1 = *(uint *)(lVar5 + 0xa8);
    if (uVar1 == 0) {
      lVar6 = *(long *)(lVar5 + 0x90);
      uVar4 = 1;
    }
    else {
      lVar6 = **(long **)(lVar5 + 0xa0);
      uVar4 = uVar1;
    }
    if ((uVar7 <= uVar4) && (uVar7 < uVar1)) {
      if (uVar7 < *(uint *)(lVar5 + 0xac)) {
        plVar3 = (long *)((ulong)uVar7 * 8 + *(long *)(lVar5 + 0xa0));
      }
      else {
        plVar3 = *(long **)(lVar5 + 0xa0);
      }
      if (*plVar3 != 0) {
        if (uVar7 < *(uint *)(lVar5 + 0xac)) {
          plVar3 = (long *)((ulong)uVar7 * 8 + *(long *)(lVar5 + 0xa0));
        }
        else {
          plVar3 = *(long **)(lVar5 + 0xa0);
        }
        lVar6 = *plVar3;
      }
    }
    if (lVar6 != 0) {
      CSkillProperty::getSkillDescription();
      return param_1;
    }
    TSafePointer<CBaseUnit>::setObject(this,(CBaseUnit *)this_00);
  }
  std::wstring::wstring((wstring_conflict *)param_1,(wstring_conflict *)&::EMPTY_WSTRING);
  return param_1;
}



/* address=00ca5420
   symbol=CSkill::getSkillLevelStats */

/* CSkill::getSkillLevelStats(CBaseUnit*, unsigned int) */

CBaseUnit * CSkill::getSkillLevelStats(CBaseUnit *param_1,uint param_2)

{
  TSafePointer<CBaseUnit> *this;
  uint uVar1;
  CRunicCore *this_00;
  undefined4 uVar2;
  long *plVar3;
  int in_ECX;
  uint uVar4;
  CRunicCore *in_RDX;
  undefined4 in_register_00000034;
  long lVar5;
  long lVar6;
  uint uVar7;

  lVar5 = CONCAT44(in_register_00000034,param_2);
  if (*(long *)(lVar5 + 0x90) != 0) {
    this_00 = *(CRunicCore **)(lVar5 + 0x30);
    this = (TSafePointer<CBaseUnit> *)(lVar5 + 0x30);
    if (in_RDX != this_00) {
      if (this_00 != (CRunicCore *)0x0) {
        CRunicCore::removeSafePointer(this_00,(TSafePointer *)this,*(uint *)(lVar5 + 0x38));
      }
      *(undefined8 *)(lVar5 + 0x30) = 0;
      if (in_RDX != (CRunicCore *)0x0) {
        uVar2 = CRunicCore::addSafePointer(in_RDX,(TSafePointer *)this);
        *(undefined4 *)(lVar5 + 0x38) = uVar2;
      }
      *(CRunicCore **)(lVar5 + 0x30) = in_RDX;
    }
    uVar7 = in_ECX - 1;
    if (0xfffffffd < uVar7) {
      uVar7 = *(int *)(lVar5 + 0xe0) - 1;
    }
    uVar1 = *(uint *)(lVar5 + 0xa8);
    if (uVar1 == 0) {
      lVar6 = *(long *)(lVar5 + 0x90);
      uVar4 = 1;
    }
    else {
      lVar6 = **(long **)(lVar5 + 0xa0);
      uVar4 = uVar1;
    }
    if ((uVar7 <= uVar4) && (uVar7 < uVar1)) {
      if (uVar7 < *(uint *)(lVar5 + 0xac)) {
        plVar3 = (long *)((ulong)uVar7 * 8 + *(long *)(lVar5 + 0xa0));
      }
      else {
        plVar3 = *(long **)(lVar5 + 0xa0);
      }
      if (*plVar3 != 0) {
        if (uVar7 < *(uint *)(lVar5 + 0xac)) {
          plVar3 = (long *)((ulong)uVar7 * 8 + *(long *)(lVar5 + 0xa0));
        }
        else {
          plVar3 = *(long **)(lVar5 + 0xa0);
        }
        lVar6 = *plVar3;
      }
    }
    if (lVar6 != 0) {
      CSkillProperty::getSkillStats();
      return param_1;
    }
    TSafePointer<CBaseUnit>::setObject(this,(CBaseUnit *)this_00);
  }
  std::wstring::wstring((wstring_conflict *)param_1,(wstring_conflict *)&::EMPTY_WSTRING);
  return param_1;
}



/* address=00ca5590
   symbol=CSkill::getSkillLevelManaCostOT */

/* CSkill::getSkillLevelManaCostOT(CBaseUnit*, unsigned int) */

int __thiscall CSkill::getSkillLevelManaCostOT(CSkill *this,CBaseUnit *param_1,uint param_2)

{
  TSafePointer<CBaseUnit> *this_00;
  uint uVar1;
  CRunicCore *this_01;
  undefined4 uVar2;
  int iVar3;
  long lVar4;
  uint uVar5;
  uint uVar6;
  long *plVar7;

  iVar3 = 0;
  if (*(long *)(this + 0x90) != 0) {
    this_01 = *(CRunicCore **)(this + 0x30);
    this_00 = (TSafePointer<CBaseUnit> *)(this + 0x30);
    if (param_1 != (CBaseUnit *)this_01) {
      if (this_01 != (CRunicCore *)0x0) {
        CRunicCore::removeSafePointer(this_01,(TSafePointer *)this_00,*(uint *)(this + 0x38));
      }
      *(undefined8 *)(this + 0x30) = 0;
      if (param_1 != (CBaseUnit *)0x0) {
        uVar2 = CRunicCore::addSafePointer((CRunicCore *)param_1,(TSafePointer *)this_00);
        *(undefined4 *)(this + 0x38) = uVar2;
      }
      *(CBaseUnit **)(this + 0x30) = param_1;
    }
    uVar6 = param_2 - 1;
    if (0xfffffffd < uVar6) {
      uVar6 = *(int *)(this + 0xe0) - 1;
    }
    uVar1 = *(uint *)(this + 0xa8);
    if (uVar1 == 0) {
      lVar4 = *(long *)(this + 0x90);
      uVar5 = 1;
    }
    else {
      lVar4 = **(long **)(this + 0xa0);
      uVar5 = uVar1;
    }
    if ((uVar6 <= uVar5) && (uVar6 < uVar1)) {
      if (uVar6 < *(uint *)(this + 0xac)) {
        plVar7 = (long *)((ulong)uVar6 * 8 + *(long *)(this + 0xa0));
      }
      else {
        plVar7 = *(long **)(this + 0xa0);
      }
      if (*plVar7 != 0) {
        if (uVar6 < *(uint *)(this + 0xac)) {
          plVar7 = (long *)((ulong)uVar6 * 8 + *(long *)(this + 0xa0));
        }
        else {
          plVar7 = *(long **)(this + 0xa0);
        }
        lVar4 = *plVar7;
      }
    }
    if (lVar4 == 0) {
      TSafePointer<CBaseUnit>::setObject(this_00,(CBaseUnit *)this_01);
      iVar3 = 0;
    }
    else {
      iVar3 = (int)*(float *)(lVar4 + 0x7c);
    }
  }
  return iVar3;
}



/* address=00ca56d0
   symbol=CSkill::getSkillLevelManaCost */

/* CSkill::getSkillLevelManaCost(CBaseUnit*, unsigned int) */

int __thiscall CSkill::getSkillLevelManaCost(CSkill *this,CBaseUnit *param_1,uint param_2)

{
  TSafePointer<CBaseUnit> *this_00;
  uint uVar1;
  CRunicCore *this_01;
  undefined4 uVar2;
  int iVar3;
  long lVar4;
  uint uVar5;
  uint uVar6;
  long *plVar7;

  iVar3 = 0;
  if (*(long *)(this + 0x90) != 0) {
    this_01 = *(CRunicCore **)(this + 0x30);
    this_00 = (TSafePointer<CBaseUnit> *)(this + 0x30);
    if (param_1 != (CBaseUnit *)this_01) {
      if (this_01 != (CRunicCore *)0x0) {
        CRunicCore::removeSafePointer(this_01,(TSafePointer *)this_00,*(uint *)(this + 0x38));
      }
      *(undefined8 *)(this + 0x30) = 0;
      if (param_1 != (CBaseUnit *)0x0) {
        uVar2 = CRunicCore::addSafePointer((CRunicCore *)param_1,(TSafePointer *)this_00);
        *(undefined4 *)(this + 0x38) = uVar2;
      }
      *(CBaseUnit **)(this + 0x30) = param_1;
    }
    uVar6 = param_2 - 1;
    if (0xfffffffd < uVar6) {
      uVar6 = *(int *)(this + 0xe0) - 1;
    }
    uVar1 = *(uint *)(this + 0xa8);
    if (uVar1 == 0) {
      lVar4 = *(long *)(this + 0x90);
      uVar5 = 1;
    }
    else {
      lVar4 = **(long **)(this + 0xa0);
      uVar5 = uVar1;
    }
    if ((uVar6 <= uVar5) && (uVar6 < uVar1)) {
      if (uVar6 < *(uint *)(this + 0xac)) {
        plVar7 = (long *)((ulong)uVar6 * 8 + *(long *)(this + 0xa0));
      }
      else {
        plVar7 = *(long **)(this + 0xa0);
      }
      if (*plVar7 != 0) {
        if (uVar6 < *(uint *)(this + 0xac)) {
          plVar7 = (long *)((ulong)uVar6 * 8 + *(long *)(this + 0xa0));
        }
        else {
          plVar7 = *(long **)(this + 0xa0);
        }
        lVar4 = *plVar7;
      }
    }
    if (lVar4 == 0) {
      TSafePointer<CBaseUnit>::setObject(this_00,(CBaseUnit *)this_01);
      iVar3 = 0;
    }
    else {
      iVar3 = (int)*(float *)(lVar4 + 0x78);
    }
  }
  return iVar3;
}



/* address=00ca5810
   symbol=CSkill::getSkillLevelCooldown */

/* CSkill::getSkillLevelCooldown(CBaseUnit*, unsigned int) */

int __thiscall CSkill::getSkillLevelCooldown(CSkill *this,CBaseUnit *param_1,uint param_2)

{
  TSafePointer<CBaseUnit> *this_00;
  uint uVar1;
  CRunicCore *this_01;
  undefined4 uVar2;
  int iVar3;
  long *plVar4;
  uint uVar5;
  CSkillProperty *this_02;
  uint uVar6;
  undefined8 *puVar7;
  float fVar8;

  iVar3 = 0;
  if (*(long *)(this + 0x90) != 0) {
    this_01 = *(CRunicCore **)(this + 0x30);
    this_00 = (TSafePointer<CBaseUnit> *)(this + 0x30);
    if (param_1 != (CBaseUnit *)this_01) {
      if (this_01 != (CRunicCore *)0x0) {
        CRunicCore::removeSafePointer(this_01,(TSafePointer *)this_00,*(uint *)(this + 0x38));
      }
      *(undefined8 *)(this + 0x30) = 0;
      if (param_1 != (CBaseUnit *)0x0) {
        uVar2 = CRunicCore::addSafePointer((CRunicCore *)param_1,(TSafePointer *)this_00);
        *(undefined4 *)(this + 0x38) = uVar2;
      }
      *(CBaseUnit **)(this + 0x30) = param_1;
    }
    uVar6 = param_2 - 1;
    if (0xfffffffd < uVar6) {
      uVar6 = *(int *)(this + 0xe0) - 1;
    }
    uVar1 = *(uint *)(this + 0xa8);
    if (uVar1 == 0) {
      this_02 = *(CSkillProperty **)(this + 0x90);
      uVar5 = 1;
    }
    else {
      this_02 = (CSkillProperty *)**(undefined8 **)(this + 0xa0);
      uVar5 = uVar1;
    }
    if ((uVar6 <= uVar5) && (uVar6 < uVar1)) {
      if (uVar6 < *(uint *)(this + 0xac)) {
        plVar4 = (long *)((ulong)uVar6 * 8 + *(long *)(this + 0xa0));
      }
      else {
        plVar4 = *(long **)(this + 0xa0);
      }
      if (*plVar4 != 0) {
        if (uVar6 < *(uint *)(this + 0xac)) {
          puVar7 = (undefined8 *)((ulong)uVar6 * 8 + *(long *)(this + 0xa0));
        }
        else {
          puVar7 = *(undefined8 **)(this + 0xa0);
        }
        this_02 = (CSkillProperty *)*puVar7;
      }
    }
    if (this_02 == (CSkillProperty *)0x0) {
      TSafePointer<CBaseUnit>::setObject(this_00,(CBaseUnit *)this_01);
      iVar3 = 0;
    }
    else {
      fVar8 = (float)CSkillProperty::getCoolDown(this_02);
      iVar3 = (int)fVar8;
    }
  }
  return iVar3;
}



/* address=00ca5950
   symbol=CSkill::triggerEvent */

/* CSkill::triggerEvent(ESKILL_EVENT_TYPE, Ogre::Vector3 const&, Ogre::Quaternion const&,
   CBaseUnit*, Ogre::Vector3 const*) */

undefined1 __thiscall
CSkill::triggerEvent
          (CSkill *this,uint param_2,undefined8 *param_3,undefined8 param_4,undefined8 param_5,
          undefined8 param_6)

{
  uint uVar1;
  long *plVar2;
  void *pvVar3;
  uint uVar4;
  long *plVar5;
  long lVar6;
  ulong uVar7;
  long lVar8;
  uint uVar9;
  long lVar10;
  long *plVar11;
  uint local_6c;
  uint local_5c;
  undefined1 local_3d;

  lVar10 = *(long *)(this + 0x90);
  if (lVar10 == 0) {
    return 0;
  }
  if (this[100] == (CSkill)0x0) {
    if (param_2 != 8) {
      return 0;
    }
  }
  else if (param_2 != 8) {
    local_3d = 0;
    goto LAB_00ca599f;
  }
  local_3d = triggerEvent(this,5,param_3,param_4,param_5,param_6);
  lVar10 = *(long *)(this + 0x90);
LAB_00ca599f:
  if (param_2 < 0xb) {
    if (param_2 < *(uint *)(lVar10 + 100)) {
      plVar5 = (long *)((ulong)param_2 * 8 + *(long *)(lVar10 + 0x58));
    }
    else {
      plVar5 = *(long **)(lVar10 + 0x58);
    }
    plVar5 = (long *)*plVar5;
    if ((plVar5 != (long *)0x0) && ((int)plVar5[1] != 0)) {
      local_6c = 0;
      local_5c = 0;
      uVar9 = 0;
      plVar11 = (long *)0x0;
      do {
        while( true ) {
          if (uVar9 < *(uint *)((long)plVar5 + 0xc)) {
            lVar10 = *(long *)((ulong)uVar9 * 8 + *plVar5);
            lVar6 = *(long *)(lVar10 + 0x220);
          }
          else {
            lVar10 = *(long *)*plVar5;
            lVar6 = *(long *)(lVar10 + 0x220);
          }
          if (lVar6 == 0) break;
LAB_00ca5a09:
          uVar9 = uVar9 + 1;
          if (*(uint *)(plVar5 + 1) <= uVar9) goto LAB_00ca5ade;
        }
        if (*(char *)(lVar10 + 0x140) == '\0') {
          if (local_6c != 0) {
            uVar1 = 0;
            lVar6 = 8;
            if (*plVar11 == 0) {
              lVar8 = 0;
            }
            else {
              do {
                lVar8 = lVar6;
                uVar1 = uVar1 + 1;
                if (local_6c <= uVar1) goto LAB_00ca5c79;
                lVar6 = lVar8 + 8;
              } while (*(long *)((long)plVar11 + lVar8) != 0);
            }
            local_6c = local_6c - 1;
            *(long *)((long)plVar11 + lVar8) = plVar11[local_6c];
          }
LAB_00ca5c79:
          CSkillEvent::startEvent
                    (*param_3,*(undefined4 *)(param_3 + 1),lVar10,*(undefined8 *)(this + 0x30),
                     *(undefined8 *)(this + 0x90),param_4,param_5,param_6);
          uVar1 = *(uint *)(this + 0xc0);
          if (uVar1 < *(uint *)(this + 0xc4)) {
            pvVar3 = *(void **)(this + 0xb8);
          }
          else if (*(long *)(this + 0xb8) == 0) {
            *(uint *)(this + 0xc4) = *(uint *)(this + 200);
                    /* try { // try from 00ca5df4 to 00ca5e14 has its CatchHandler @ 00ca5e25 */
            pvVar3 = operator_new__((ulong)*(uint *)(this + 200) << 3);
            *(void **)(this + 0xb8) = pvVar3;
            uVar1 = *(uint *)(this + 0xc0);
          }
          else {
            uVar1 = *(uint *)(this + 0xc4) + *(int *)(this + 200);
            pvVar3 = operator_new__((ulong)uVar1 << 3);
            if (*(int *)(this + 0xc4) != 0) {
              uVar7 = 0;
              do {
                uVar4 = (int)uVar7 + 1;
                *(undefined8 *)((long)pvVar3 + uVar7 * 8) =
                     *(undefined8 *)(*(long *)(this + 0xb8) + uVar7 * 8);
                uVar7 = (ulong)uVar4;
              } while (uVar4 < *(uint *)(this + 0xc4));
            }
            if (*(void **)(this + 0xb8) != (void *)0x0) {
              operator_delete__(*(void **)(this + 0xb8));
            }
            *(void **)(this + 0xb8) = pvVar3;
            *(uint *)(this + 0xc4) = uVar1;
            uVar1 = *(uint *)(this + 0xc0);
          }
          *(long *)((long)pvVar3 + (ulong)uVar1 * 8) = lVar10;
          *(int *)(this + 0xc0) = *(int *)(this + 0xc0) + 1;
          local_3d = 1;
          goto LAB_00ca5a09;
        }
        if (*(char *)(lVar10 + 0x14c) == '\0') goto LAB_00ca5a09;
        plVar2 = plVar11;
        if (local_5c <= local_6c) {
          if (plVar11 == (long *)0x0) {
            plVar2 = operator_new__(0x28);
            local_5c = 5;
          }
          else {
                    /* try { // try from 00ca5a76 to 00ca5d86 has its CatchHandler @ 00ca5e25 */
            plVar2 = operator_new__((ulong)(local_5c + 5) << 3);
            if (local_5c != 0) {
              lVar6 = 0;
              do {
                *(undefined8 *)((long)plVar2 + lVar6) = *(undefined8 *)((long)plVar11 + lVar6);
                lVar6 = lVar6 + 8;
              } while (lVar6 != (ulong)(local_5c - 1) * 8 + 8);
            }
            operator_delete__(plVar11);
            local_5c = local_5c + 5;
          }
        }
        uVar9 = uVar9 + 1;
        plVar2[local_6c] = lVar10;
        local_6c = local_6c + 1;
        plVar11 = plVar2;
      } while (uVar9 < *(uint *)(plVar5 + 1));
LAB_00ca5ade:
      if (local_6c != 0) {
        lVar10 = 0;
        uVar9 = 0;
        do {
          plVar5 = (long *)((long)plVar11 + lVar10);
          if (local_5c <= uVar9) {
            plVar5 = plVar11;
          }
          lVar6 = CSkillProperty::cloneEventForSkill
                            (*(CSkillProperty **)(this + 0x90),(CSkillEvent *)*plVar5);
          if (lVar6 != 0) {
            uVar1 = *(uint *)(this + 0xc0);
            if (uVar1 < *(uint *)(this + 0xc4)) {
              pvVar3 = *(void **)(this + 0xb8);
            }
            else if (*(long *)(this + 0xb8) == 0) {
              *(uint *)(this + 0xc4) = *(uint *)(this + 200);
              pvVar3 = operator_new__((ulong)*(uint *)(this + 200) << 3);
              *(void **)(this + 0xb8) = pvVar3;
              uVar1 = *(uint *)(this + 0xc0);
            }
            else {
              uVar1 = *(uint *)(this + 0xc4) + *(int *)(this + 200);
              pvVar3 = operator_new__((ulong)uVar1 << 3);
              if (*(int *)(this + 0xc4) != 0) {
                uVar7 = 0;
                do {
                  uVar4 = (int)uVar7 + 1;
                  *(undefined8 *)((long)pvVar3 + uVar7 * 8) =
                       *(undefined8 *)(*(long *)(this + 0xb8) + uVar7 * 8);
                  uVar7 = (ulong)uVar4;
                } while (uVar4 < *(uint *)(this + 0xc4));
              }
              if (*(void **)(this + 0xb8) != (void *)0x0) {
                operator_delete__(*(void **)(this + 0xb8));
              }
              *(void **)(this + 0xb8) = pvVar3;
              *(uint *)(this + 0xc4) = uVar1;
              uVar1 = *(uint *)(this + 0xc0);
            }
            *(long *)((long)pvVar3 + (ulong)uVar1 * 8) = lVar6;
            *(int *)(this + 0xc0) = *(int *)(this + 0xc0) + 1;
            CSkillEvent::startEvent
                      (*param_3,*(undefined4 *)(param_3 + 1),lVar6,*(undefined8 *)(this + 0x30),
                       *(undefined8 *)(this + 0x90),param_4,param_5,param_6);
          }
          uVar9 = uVar9 + 1;
          lVar10 = lVar10 + 8;
        } while (uVar9 < local_6c);
      }
      if (plVar11 != (long *)0x0) {
        operator_delete__(plVar11);
      }
    }
  }
  return local_3d;
}



/* address=00ca5e40
   symbol=CSkill::unitStateChange */

/* non-virtual thunk to CSkill::unitStateChange(CBaseUnit*, EUNIT_STATES) */

void __thiscall CSkill::unitStateChange(CSkill *this)

{
  unitStateChange(this + -0x10);
  return;
}



/* address=00ca5e50
   symbol=CSkill::unitStateChange */

/* CSkill::unitStateChange(CBaseUnit*, EUNIT_STATES) */

void CSkill::unitStateChange
               (undefined8 param_1_00,undefined4 param_2,CSkill *param_1,CBaseUnit *param_4,
               int param_5)

{
  long *plVar1;
  char cVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  CLevel *pCVar5;
  undefined8 local_38;
  undefined4 local_30;

  if (param_4 != (CBaseUnit *)0x0) {
    if (param_5 == 1) {
      pCVar5 = (CLevel *)0x0;
      if (*(long *)(param_4 + 0x68) != 0) {
        pCVar5 = *(CLevel **)(*(long *)(param_4 + 0x68) + 0x18);
      }
      CLevel::removeListenerFromUnit(pCVar5,param_4,(iUnitObserver *)(param_1 + 0x10));
    }
    else if (param_5 == 4) {
      pCVar5 = (CLevel *)0x0;
      if (*(long *)(param_4 + 0x68) != 0) {
        pCVar5 = *(CLevel **)(*(long *)(param_4 + 0x68) + 0x18);
      }
      CLevel::removeListenerFromUnit(pCVar5,param_4,(iUnitObserver *)(param_1 + 0x10));
      if (*(CEffectManager **)(param_4 + 0x1b8) != (CEffectManager *)0x0) {
        cVar2 = CEffectManager::hasEffectFromSkill(*(CEffectManager **)(param_4 + 0x1b8),param_1);
        if ((cVar2 != '\0') && (plVar1 = *(long **)(param_4 + 0x58), plVar1 != (long *)0x0)) {
          uVar3 = __dynamic_cast(param_4,&CBaseUnit::typeinfo,&CCharacter::typeinfo,0);
          uVar4 = (**(code **)(*plVar1 + 200))(plVar1);
          local_38 = CPositionableObject::getPosition((CPositionableObject *)param_4,true);
          local_30 = param_2;
          triggerEvent(param_1,8,&local_38,uVar4,uVar3,0);
        }
      }
    }
  }
  return;
}



/* address=00ca5f80
   symbol=CSkill::stopSkill */

/* CSkill::stopSkill() */

void CSkill::stopSkill(void)

{
  long lVar1;
  long *plVar2;
  undefined8 *puVar3;
  uint uVar4;
  ulong uVar5;
  long in_RDI;
  uint uVar6;
  long lVar7;

  if ((((*(int *)(in_RDI + 0x60) == 4) || (*(int *)(in_RDI + 0xec) != -1)) &&
      (*(long **)(in_RDI + 0x30) != (long *)0x0)) && (*(char *)(in_RDI + 0x65) == '\0')) {
    (**(code **)(**(long **)(in_RDI + 0x30) + 0xf0))();
    CPositionableObject::getPosition(*(CPositionableObject **)(in_RDI + 0x30),true);
    triggerEvent();
    *(undefined1 *)(in_RDI + 0x65) = 1;
  }
  lVar1 = *(long *)(in_RDI + 0x90);
  if (lVar1 == 0) {
LAB_00ca60d0:
    if (*(CRunicCore **)(in_RDI + 0x40) != (CRunicCore *)0x0) {
      CRunicCore::removeSafePointer
                (*(CRunicCore **)(in_RDI + 0x40),(TSafePointer *)(in_RDI + 0x40),
                 *(uint *)(in_RDI + 0x48));
      *(undefined8 *)(in_RDI + 0x40) = 0;
    }
    *(undefined4 *)(in_RDI + 0xc0) = 0;
    *(undefined4 *)(in_RDI + 0xc4) = 0;
    if (*(void **)(in_RDI + 0xb8) != (void *)0x0) {
      operator_delete__(*(void **)(in_RDI + 0xb8));
    }
    *(undefined8 *)(in_RDI + 0xb8) = 0;
    *(undefined1 *)(in_RDI + 100) = 0;
    *(undefined4 *)(in_RDI + 0x108) = 0;
    *(undefined4 *)(in_RDI + 0xf8) = 0x3f800000;
    *(undefined4 *)(in_RDI + 0x50) = Ogre::Vector3::ZERO;
    *(undefined4 *)(in_RDI + 0x54) = DAT_014241b0;
    *(undefined4 *)(in_RDI + 0x58) = DAT_014241b4;
    return;
  }
  lVar7 = 0;
  uVar6 = 0;
  if (*(int *)(lVar1 + 100) != 0) goto LAB_00ca60c3;
  do {
    plVar2 = *(long **)(lVar1 + 0x58);
    while( true ) {
      plVar2 = (long *)*plVar2;
      if ((int)plVar2[1] != 0) {
        uVar5 = 0;
        do {
          if ((uint)uVar5 < *(uint *)((long)plVar2 + 0xc)) {
            puVar3 = (undefined8 *)(uVar5 * 8 + *plVar2);
          }
          else {
            puVar3 = (undefined8 *)*plVar2;
          }
          uVar4 = (uint)uVar5 + 1;
          uVar5 = (ulong)uVar4;
          CSkillEvent::resetEvent((CSkillEvent *)*puVar3);
        } while (uVar4 < *(uint *)(plVar2 + 1));
      }
      uVar6 = uVar6 + 1;
      lVar7 = lVar7 + 8;
      if (uVar6 == 0xb) goto LAB_00ca60d0;
      lVar1 = *(long *)(in_RDI + 0x90);
      if (*(uint *)(lVar1 + 100) <= uVar6) break;
LAB_00ca60c3:
      plVar2 = (long *)(lVar7 + *(long *)(lVar1 + 0x58));
    }
  } while( true );
}



/* address=00ca6160
   symbol=CSkill::updateSkill */

/* CSkill::updateSkill(float) */

void __thiscall CSkill::updateSkill(CSkill *this,float param_1)

{
  char cVar1;
  uint uVar2;
  undefined8 *puVar3;
  uint uVar4;
  float fVar5;
  undefined4 uVar6;
  undefined8 local_38;
  undefined8 local_30;
  undefined8 local_28;
  float local_20;

  if (*(long *)(this + 0x30) == 0) {
    stopSkill();
  }
  *(float *)(this + 0xfc) = *(float *)(this + 0xfc) - param_1;
  if (this[100] != (CSkill)0x0) {
    fVar5 = *(float *)(this + 0x108) + param_1 * *(float *)(this + 0xf8);
    *(float *)(this + 0x108) = fVar5;
    if ((*(long *)(this + 0x90) == 0) || (*(char *)(*(long *)(this + 0x90) + 0xb2) == '\0')) {
      fVar5 = *(float *)(this + 0x104) - param_1 * *(float *)(this + 0xf8);
      *(float *)(this + 0x104) = fVar5;
    }
    uVar6 = 0;
    uVar4 = 0;
    if (*(int *)(this + 0xc0) != 0) {
      do {
        while (cVar1 = CSkillEvent::updateEvent(*(float *)(this + 0xf8) * param_1), cVar1 == '\0') {
          if (uVar4 < *(uint *)(this + 0xc4)) {
            puVar3 = (undefined8 *)((ulong)uVar4 * 8 + *(long *)(this + 0xb8));
          }
          else {
            puVar3 = *(undefined8 **)(this + 0xb8);
          }
          CSkillEvent::stopEvent((CSkillEvent *)*puVar3);
          uVar2 = *(uint *)(this + 0xc0);
          if (uVar4 < uVar2) {
            *(uint *)(this + 0xc0) = uVar2 - 1;
            *(undefined8 *)(*(long *)(this + 0xb8) + (ulong)uVar4 * 8) =
                 *(undefined8 *)(*(long *)(this + 0xb8) + (ulong)(uVar2 - 1) * 8);
            uVar2 = *(uint *)(this + 0xc0);
          }
          if (uVar2 <= uVar4) goto LAB_00ca6289;
        }
        uVar2 = *(uint *)(this + 0xc0);
        uVar4 = uVar4 + 1;
      } while (uVar4 < uVar2);
LAB_00ca6289:
      if (uVar2 != 0) {
        fVar5 = *(float *)(*(long *)(this + 0x90) + 0xa4);
        uVar6 = 0;
        if ((fVar5 <= 0.0) && (*(int *)(this + 0xec) == -1)) {
          return;
        }
      }
    }
    if (((*(float *)(this + 0x104) <= 0.0) && (*(int *)(this + 0x60) != 4)) &&
       (*(float *)(*(long *)(this + 0x90) + 0xa4) <= *(float *)(this + 0x108))) {
      if ((*(long **)(this + 0x30) != (long *)0x0) && (this[0x65] == (CSkill)0x0)) {
        local_38 = (**(code **)(**(long **)(this + 0x30) + 0xf0))();
        local_30 = CONCAT44(uVar6,fVar5);
        local_28 = CPositionableObject::getPosition(*(CPositionableObject **)(this + 0x30),true);
        local_20 = fVar5;
        cVar1 = triggerEvent(this,1,&local_28,&local_38,0,0);
        if (cVar1 != '\0') {
          this[0x65] = (CSkill)0x1;
          return;
        }
        this[0x65] = (CSkill)0x1;
      }
      stopSkill();
      return;
    }
  }
  return;
}



/* address=00ca7210
   symbol=CSkill::~CSkill */

/* WARNING: Removing unreachable block (ram,0x00ca7618) */
/* WARNING: Removing unreachable block (ram,0x00ca7680) */
/* WARNING: Removing unreachable block (ram,0x00ca76e8) */
/* WARNING: Removing unreachable block (ram,0x00ca76dd) */
/* WARNING: Removing unreachable block (ram,0x00ca7675) */
/* WARNING: Removing unreachable block (ram,0x00ca760d) */
/* CSkill::~CSkill() */

void __thiscall CSkill::~CSkill(CSkill *this)

{
  allocator *paVar1;
  int *piVar2;
  int iVar3;
  uint uVar4;
  undefined8 *puVar5;
  long *plVar6;
  uint uVar7;

  *(undefined ***)this = &PTR__CSkill_00ff4c50;
  *(undefined ***)(this + 0x10) = &PTR__CSkill_00ff4c78;
  if (*(CLevel **)(*(long *)(this + 0x18) + 0x18) != (CLevel *)0x0) {
                    /* try { // try from 00ca7241 to 00ca73b9 has its CatchHandler @ 00ca74ef */
    CLevel::removeListenerFromUnits
              (*(CLevel **)(*(long *)(this + 0x18) + 0x18),(iUnitObserver *)(this + 0x10));
  }
  uVar7 = *(uint *)(this + 0xa8);
  while (uVar7 != 0) {
    uVar4 = *(uint *)(this + 0xac);
    uVar7 = uVar7 - 1;
    if (uVar7 < uVar4) {
      plVar6 = (long *)((ulong)uVar7 * 8 + *(long *)(this + 0xa0));
    }
    else {
      plVar6 = *(long **)(this + 0xa0);
    }
    if (*plVar6 != 0) {
      if (uVar7 < uVar4) {
        plVar6 = (long *)((ulong)uVar7 * 8 + *(long *)(this + 0xa0));
      }
      else {
        plVar6 = *(long **)(this + 0xa0);
      }
      if (*plVar6 != 0) {
        if (uVar7 < uVar4) {
          plVar6 = (long *)((ulong)uVar7 * 8 + *(long *)(this + 0xa0));
        }
        else {
          plVar6 = *(long **)(this + 0xa0);
        }
        if ((long *)*plVar6 != (long *)0x0) {
          (**(code **)(*(long *)*plVar6 + 8))();
          uVar4 = *(uint *)(this + 0xac);
        }
        if (uVar7 < uVar4) {
          puVar5 = (undefined8 *)((ulong)uVar7 * 8 + *(long *)(this + 0xa0));
        }
        else {
          puVar5 = *(undefined8 **)(this + 0xa0);
        }
        *puVar5 = 0;
      }
    }
  }
  if (*(long **)(this + 0x98) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x98) + 8))();
    *(undefined8 *)(this + 0x98) = 0;
  }
  *(undefined4 *)(this + 0x80) = 0;
  *(undefined4 *)(this + 0x84) = 0;
  if (*(void **)(this + 0x78) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x78));
  }
  *(undefined8 *)(this + 0x78) = 0;
  *(undefined4 *)(this + 0xa8) = 0;
  *(undefined4 *)(this + 0xac) = 0;
  if (*(void **)(this + 0xa0) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0xa0));
  }
  *(undefined8 *)(this + 0xa0) = 0;
  *(undefined8 *)(this + 0x90) = 0;
  this[100] = (CSkill)0x0;
  if (*(CRunicCore **)(this + 0x30) != (CRunicCore *)0x0) {
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(this + 0x30),(TSafePointer *)(this + 0x30),*(uint *)(this + 0x38));
    *(undefined8 *)(this + 0x30) = 0;
  }
  paVar1 = (allocator *)(*(long *)(this + 0x148) + -0x18);
  if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0x148) + -8);
    iVar3 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar1);
    }
  }
  paVar1 = (allocator *)(*(long *)(this + 0x140) + -0x18);
  if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0x140) + -8);
    iVar3 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar1);
    }
  }
  paVar1 = (allocator *)(*(long *)(this + 0x138) + -0x18);
  if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0x138) + -8);
    iVar3 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar1);
    }
  }
  paVar1 = (allocator *)(*(long *)(this + 0x130) + -0x18);
  if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0x130) + -8);
    iVar3 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar1);
    }
  }
  paVar1 = (allocator *)(*(long *)(this + 0x128) + -0x18);
  if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0x128) + -8);
    iVar3 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar1);
    }
  }
  paVar1 = (allocator *)(*(long *)(this + 0xd0) + -0x18);
  if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0xd0) + -8);
    iVar3 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar1);
    }
  }
  if (*(void **)(this + 0xb8) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0xb8));
    *(undefined8 *)(this + 0xb8) = 0;
  }
  if (*(void **)(this + 0xa0) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0xa0));
    *(undefined8 *)(this + 0xa0) = 0;
  }
  if (*(void **)(this + 0x78) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x78));
    *(undefined8 *)(this + 0x78) = 0;
  }
  if (*(CRunicCore **)(this + 0x40) != (CRunicCore *)0x0) {
                    /* try { // try from 00ca749d to 00ca74a1 has its CatchHandler @ 00ca75b6 */
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(this + 0x40),(TSafePointer *)(this + 0x40),*(uint *)(this + 0x48));
  }
  *(undefined8 *)(this + 0x40) = 0;
  *(undefined4 *)(this + 0x48) = 0xffffffff;
  if (*(CRunicCore **)(this + 0x30) != (CRunicCore *)0x0) {
                    /* try { // try from 00ca74c0 to 00ca74c4 has its CatchHandler @ 00ca75b1 */
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(this + 0x30),(TSafePointer *)(this + 0x30),*(uint *)(this + 0x38));
  }
  *(undefined8 *)(this + 0x30) = 0;
  *(undefined4 *)(this + 0x38) = 0xffffffff;
  *(undefined ***)(this + 0x10) = &PTR__iUnitObserver_00fdb290;
  CRunicCore::~CRunicCore((CRunicCore *)this);
  return;
}



/* address=00ca7700
   symbol=CSkill::~CSkill */

/* non-virtual thunk to CSkill::~CSkill() */

void __thiscall CSkill::~CSkill(CSkill *this)

{
  ~CSkill(this + -0x10);
  return;
}



/* address=00ca7710
   symbol=CSkill::~CSkill */

/* non-virtual thunk to CSkill::~CSkill() */

void __thiscall CSkill::~CSkill(CSkill *this)

{
  ~CSkill(this + -0x10);
  return;
}



/* address=00ca7720
   symbol=CSkill::~CSkill */

/* CSkill::~CSkill() */

void __thiscall CSkill::~CSkill(CSkill *this)

{
  ~CSkill(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}



/* address=00ca7740
   symbol=CSkill::calculateEffectiveSkillLevel */

/* WARNING: Removing unreachable block (ram,0x00ca79f2) */
/* WARNING: Removing unreachable block (ram,0x00ca7a10) */
/* CSkill::calculateEffectiveSkillLevel() */

bool __thiscall CSkill::calculateEffectiveSkillLevel(CSkill *this)

{
  int *piVar1;
  code *pcVar2;
  int iVar3;
  CCharacter *pCVar4;
  int iVar5;
  wstring_conflict *pwVar6;
  float fVar7;
  long local_48 [2];
  long local_38 [2];

  iVar5 = *(int *)(this + 0xdc);
  pCVar4 = (CCharacter *)getMasterOwnerCharacter(this);
  if ((pCVar4 != (CCharacter *)0x0) && (iVar5 != 0)) {
    pcVar2 = *(code **)(*(long *)pCVar4 + 600);
    pwVar6 = (wstring_conflict *)&::EMPTY_WSTRING;
    if (*(long *)(this + 0x90) != 0) {
      pwVar6 = (wstring_conflict *)(*(long *)(this + 0x90) + 0xd8);
    }
    STRINGS::StringUpper((STRINGS *)local_38,pwVar6);
                    /* try { // try from 00ca77be to 00ca77c0 has its CatchHandler @ 00ca79fd */
    fVar7 = (float)(*pcVar2)(0,pCVar4,0x52,(STRINGS *)local_38);
    iVar5 = iVar5 + (int)fVar7;
    if ((allocator *)(local_38[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_38[0] + -8);
      iVar3 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar3 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_38[0] + -0x18));
      }
    }
    iVar3 = *(int *)(this + 0x5c);
    if (iVar3 == 2) {
      fVar7 = (float)CCharacter::getEffectValue(pCVar4,0x56,7);
      iVar5 = iVar5 + (int)fVar7;
    }
    else if (iVar3 == 3) {
      fVar7 = (float)CCharacter::getEffectValue(pCVar4,0x57,7);
      iVar5 = iVar5 + (int)fVar7;
    }
    else if (iVar3 == 1) {
      fVar7 = (float)CCharacter::getEffectValue(pCVar4,0x55,7);
      iVar5 = iVar5 + (int)fVar7;
    }
    pCVar4 = *(CCharacter **)(pCVar4 + 0x640);
    if (pCVar4 != (CCharacter *)0x0) {
      pcVar2 = *(code **)(*(long *)pCVar4 + 600);
      pwVar6 = (wstring_conflict *)&::EMPTY_WSTRING;
      if (*(long *)(this + 0x90) != 0) {
        pwVar6 = (wstring_conflict *)(*(long *)(this + 0x90) + 0xd8);
      }
      STRINGS::StringUpper((STRINGS *)local_48,pwVar6);
                    /* try { // try from 00ca7857 to 00ca7859 has its CatchHandler @ 00ca79df */
      fVar7 = (float)(*pcVar2)(0,pCVar4,0x52,local_48);
      iVar5 = iVar5 + (int)fVar7;
      if ((allocator *)(local_48[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_48[0] + -8);
        iVar3 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar3 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
        }
      }
      iVar3 = *(int *)(this + 0x5c);
      if (iVar3 == 2) {
        fVar7 = (float)CCharacter::getEffectValue(pCVar4,0x56,7);
        iVar5 = iVar5 + (int)fVar7;
      }
      else if (iVar3 == 3) {
        fVar7 = (float)CCharacter::getEffectValue(pCVar4,0x57,7);
        iVar5 = iVar5 + (int)fVar7;
      }
      else if (iVar3 == 1) {
        fVar7 = (float)CCharacter::getEffectValue(pCVar4,0x55,7);
        iVar5 = iVar5 + (int)fVar7;
      }
    }
  }
  iVar3 = 1;
  if (*(int *)(this + 0xa8) != 0) {
    iVar3 = *(int *)(this + 0xa8);
  }
  if (iVar3 <= iVar5) {
    iVar5 = iVar3;
  }
  iVar3 = *(int *)(this + 0xe0);
  if (iVar5 != iVar3) {
    *(int *)(this + 0xe0) = iVar5;
    _setLevelOfSkillFromSkillManager(this,*(uint *)(this + 0xdc));
  }
  return iVar5 != iVar3;
}



/* address=00ca7a20
   symbol=CSkill::_setLevelOfSkillFromSkillManager */

/* CSkill::_setLevelOfSkillFromSkillManager(unsigned int) */

void __thiscall CSkill::_setLevelOfSkillFromSkillManager(CSkill *this,uint param_1)

{
  uint uVar1;
  uint uVar2;
  undefined8 *puVar3;

  if (param_1 == 0xffffffff) {
    *(undefined4 *)(this + 0xdc) = 1;
  }
  else {
    uVar1 = 1;
    if (*(uint *)(this + 0xa8) != 0) {
      uVar1 = *(uint *)(this + 0xa8);
    }
    if (uVar1 < param_1) {
      *(uint *)(this + 0xdc) = uVar1;
    }
    else {
      *(uint *)(this + 0xdc) = param_1;
    }
  }
  calculateEffectiveSkillLevel(this);
  uVar1 = *(uint *)(this + 0xa8);
  if ((uVar1 != 0) && (*(int *)(this + 0xe0) != 0)) {
    uVar2 = *(int *)(this + 0xe0) - 1;
    if (uVar2 < uVar1) {
      if (uVar2 < *(uint *)(this + 0xac)) {
        puVar3 = (undefined8 *)((ulong)uVar2 * 8 + *(long *)(this + 0xa0));
      }
      else {
        puVar3 = *(undefined8 **)(this + 0xa0);
      }
      *(undefined8 *)(this + 0x90) = *puVar3;
      return;
    }
    if (uVar1 - 1 < *(uint *)(this + 0xac)) {
      puVar3 = (undefined8 *)((ulong)(uVar1 - 1) * 8 + *(long *)(this + 0xa0));
    }
    else {
      puVar3 = *(undefined8 **)(this + 0xa0);
    }
    *(undefined8 *)(this + 0x90) = *puVar3;
    return;
  }
  *(undefined8 *)(this + 0x90) = *(undefined8 *)(this + 0x98);
  return;
}



/* address=00ca7b10
   symbol=CSkill::CSkill */

/* WARNING: Removing unreachable block (ram,0x00ca8d85) */
/* WARNING: Removing unreachable block (ram,0x00ca8b47) */
/* WARNING: Removing unreachable block (ram,0x00ca8a7c) */
/* WARNING: Removing unreachable block (ram,0x00ca8b95) */
/* WARNING: Removing unreachable block (ram,0x00ca8c25) */
/* WARNING: Removing unreachable block (ram,0x00ca8ce9) */
/* WARNING: Removing unreachable block (ram,0x00ca8e65) */
/* WARNING: Removing unreachable block (ram,0x00ca8f85) */
/* WARNING: Removing unreachable block (ram,0x00ca8f35) */
/* WARNING: Removing unreachable block (ram,0x00ca8d7a) */
/* WARNING: Removing unreachable block (ram,0x00ca9035) */
/* WARNING: Removing unreachable block (ram,0x00ca9138) */
/* WARNING: Removing unreachable block (ram,0x00ca90db) */
/* WARNING: Removing unreachable block (ram,0x00ca8b39) */
/* WARNING: Removing unreachable block (ram,0x00ca912a) */
/* WARNING: Removing unreachable block (ram,0x00ca8fee) */
/* WARNING: Removing unreachable block (ram,0x00ca90cb) */
/* WARNING: Removing unreachable block (ram,0x00ca8f73) */
/* WARNING: Removing unreachable block (ram,0x00ca8ea3) */
/* WARNING: Removing unreachable block (ram,0x00ca8cd9) */
/* WARNING: Removing unreachable block (ram,0x00ca8c63) */
/* WARNING: Removing unreachable block (ram,0x00ca8bde) */
/* WARNING: Removing unreachable block (ram,0x00ca8ab5) */
/* WARNING: Removing unreachable block (ram,0x00ca8b83) */
/* WARNING: Removing unreachable block (ram,0x00ca8dd4) */
/* WARNING: Removing unreachable block (ram,0x00ca8d95) */
/* CSkill::CSkill(CResourceManager*, CDataGroup*) */

void __thiscall CSkill::CSkill(CSkill *this,CResourceManager *param_1,CDataGroup *param_2)

{
  wchar_t *pwVar1;
  int *piVar2;
  wchar_t wVar3;
  size_t sVar4;
  CSkill CVar5;
  uint uVar6;
  undefined4 uVar7;
  int iVar8;
  CSkillProperty *pCVar9;
  CDataGroup *pCVar10;
  undefined8 uVar11;
  wstring_conflict *pwVar12;
  long lVar13;
  CUnitResourceList *this_00;
  long lVar14;
  long *plVar15;
  void *pvVar16;
  uint uVar17;
  ulong uVar18;
  int iVar19;
  uint uVar20;
  undefined8 *puVar21;
  CSkillProperty *local_240;
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
  wchar_t *local_e8 [2];
  long local_d8 [2];
  long local_c8 [2];
  long local_b8 [2];
  wchar_t *local_a8 [2];
  long local_98 [2];
  long local_88 [2];
  long local_78 [5];
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

  CRunicCore::CRunicCore((CRunicCore *)this);
  *(undefined ***)this = &PTR__CSkill_00ff4c50;
  *(undefined ***)(this + 0x10) = &PTR__CSkill_00ff4c78;
  *(CResourceManager **)(this + 0x18) = param_1;
  *(undefined8 *)(this + 0x20) = 0;
  *(CDataGroup **)(this + 0x28) = param_2;
  *(undefined8 *)(this + 0x30) = 0;
  *(undefined4 *)(this + 0x38) = 0xffffffff;
  *(undefined8 *)(this + 0x40) = 0;
  *(undefined4 *)(this + 0x48) = 0xffffffff;
  *(undefined4 *)(this + 0x5c) = 0;
  *(undefined4 *)(this + 0x60) = 0;
  this[100] = (CSkill)0x0;
  this[0x65] = (CSkill)0x0;
  this[0x66] = (CSkill)0x1;
  this[0x67] = (CSkill)0x0;
  this[0x68] = (CSkill)0x0;
  this[0x69] = (CSkill)0x0;
  this[0x6a] = (CSkill)0x0;
  this[0x6c] = (CSkill)0x0;
  this[0x6d] = (CSkill)0x1;
  this[0x6f] = (CSkill)0x0;
  this[0x70] = (CSkill)0x1;
  *(undefined8 *)(this + 0x78) = 0;
  *(undefined4 *)(this + 0x80) = 0;
  *(undefined4 *)(this + 0x84) = 0;
  *(undefined4 *)(this + 0x88) = 2;
  *(undefined8 *)(this + 0x90) = 0;
  *(undefined8 *)(this + 0x98) = 0;
  *(undefined8 *)(this + 0xa0) = 0;
  *(undefined4 *)(this + 0xa8) = 0;
  *(undefined4 *)(this + 0xac) = 0;
  *(undefined4 *)(this + 0xb0) = 10;
  *(undefined8 *)(this + 0xb8) = 0;
  *(undefined4 *)(this + 0xc0) = 0;
  *(undefined4 *)(this + 0xc4) = 0;
  *(undefined4 *)(this + 200) = 10;
                    /* try { // try from 00ca7c48 to 00ca7c4c has its CatchHandler @ 00ca8d1a */
  std::wstring::wstring((wstring_conflict *)(this + 0xd0),(wstring_conflict *)&::EMPTY_WSTRING);
  *(undefined4 *)(this + 0xd8) = 1;
  *(undefined4 *)(this + 0xdc) = 0;
  *(undefined4 *)(this + 0xe0) = 0;
  *(undefined4 *)(this + 0xe4) = 0xffffffff;
  *(undefined4 *)(this + 0xe8) = 0xffffffff;
  *(undefined4 *)(this + 0xec) = 0xffffffff;
  *(undefined4 *)(this + 0xf0) = 0xffffffff;
  *(undefined4 *)(this + 0xf4) = 0xffffffff;
  *(undefined4 *)(this + 0xf8) = 0x3f800000;
  *(undefined4 *)(this + 0xfc) = 0;
  *(undefined4 *)(this + 0x100) = 0;
  *(undefined4 *)(this + 0x104) = 0;
  *(undefined4 *)(this + 0x108) = 0;
  *(undefined4 *)(this + 0x10c) = 0xffffffff;
  *(undefined4 *)(this + 0x110) = 0xffffffff;
  *(undefined4 *)(this + 0x114) = 0xffffffff;
  *(undefined4 *)(this + 0x118) = 100;
  *(undefined4 *)(this + 0x11c) = 0;
  *(undefined4 *)(this + 0x120) = 2;
  *(undefined4 *)(this + 0x124) = 0xffffffff;
                    /* try { // try from 00ca7d29 to 00ca7d2d has its CatchHandler @ 00ca8afc */
  std::wstring::wstring((wstring_conflict *)(this + 0x128),(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 00ca7d42 to 00ca7d46 has its CatchHandler @ 00ca8b31 */
  std::wstring::wstring((wstring_conflict *)(this + 0x130),(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 00ca7d5b to 00ca7d5f has its CatchHandler @ 00ca8968 */
  std::wstring::wstring((wstring_conflict *)(this + 0x138),(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 00ca7d74 to 00ca7d78 has its CatchHandler @ 00ca8e1a */
  std::wstring::wstring((wstring_conflict *)(this + 0x140),(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 00ca7d8d to 00ca7d91 has its CatchHandler @ 00ca8e12 */
  std::wstring::wstring((wstring_conflict *)(this + 0x148),(wstring_conflict *)&::EMPTY_WSTRING);
  *(undefined8 *)(this + 0x150) = 0xffffffffffffffff;
  *(undefined4 *)(this + 0x158) = 0;
  if (param_2 != (CDataGroup *)0x0) {
                    /* try { // try from 00ca7dbb to 00ca7dbf has its CatchHandler @ 00ca8e0a */
    pCVar9 = (CSkillProperty *)Ogre::NedAllocImpl::allocBytes(0x120,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00ca7dd6 to 00ca7dda has its CatchHandler @ 00ca8dfa */
    CSkillProperty::CSkillProperty
              (pCVar9,this,*(CResourceManager **)(this + 0x18),(CSkillProperty *)0x0,
               *(CDataGroup **)(this + 0x28),0);
    *(CSkillProperty **)(this + 0x98) = pCVar9;
    if (*(long *)(this + 0x28) != 0) {
      uVar20 = 1;
      do {
                    /* try { // try from 00ca7e7f to 00ca7e83 has its CatchHandler @ 00ca8e0a */
        STRINGS::GetValueAsWString((uint)local_78);
                    /* try { // try from 00ca7e94 to 00ca7e98 has its CatchHandler @ 00ca8de5 */
        std::operator+((wchar_t *)local_88,(wstring_conflict *)L"LEVEL");
                    /* try { // try from 00ca7ea2 to 00ca7ea6 has its CatchHandler @ 00ca908a */
        pCVar10 = (CDataGroup *)
                  CDataGroup::GetDataGroupByName
                            (*(CDataGroup **)(this + 0x28),(wstring_conflict *)local_88,false);
        if ((allocator *)(local_88[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar2 = (int *)(local_88[0] + -8);
          iVar19 = *piVar2;
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (iVar19 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
          }
        }
        if ((allocator *)(local_78[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar2 = (int *)(local_78[0] + -8);
          iVar19 = *piVar2;
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (iVar19 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
          }
        }
        if (pCVar10 == (CDataGroup *)0x0) break;
        if (*(int *)(this + 0xa8) == 0) {
          local_240 = *(CSkillProperty **)(this + 0x98);
        }
        else {
          uVar6 = *(int *)(this + 0xa8) - 1;
          if (uVar6 < *(uint *)(this + 0xac)) {
            puVar21 = (undefined8 *)((ulong)uVar6 * 8 + *(long *)(this + 0xa0));
          }
          else {
            puVar21 = *(undefined8 **)(this + 0xa0);
          }
          local_240 = (CSkillProperty *)*puVar21;
        }
                    /* try { // try from 00ca7e17 to 00ca7e1b has its CatchHandler @ 00ca8e0a */
        pCVar9 = (CSkillProperty *)Ogre::NedAllocImpl::allocBytes(0x120,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00ca7e34 to 00ca7e38 has its CatchHandler @ 00ca90e9 */
        CSkillProperty::CSkillProperty
                  (pCVar9,this,*(CResourceManager **)(this + 0x18),local_240,pCVar10,uVar20);
        uVar6 = *(uint *)(this + 0xa8);
        if (uVar6 < *(uint *)(this + 0xac)) {
          pvVar16 = *(void **)(this + 0xa0);
        }
        else if (*(long *)(this + 0xa0) == 0) {
          *(uint *)(this + 0xac) = *(uint *)(this + 0xb0);
          pvVar16 = operator_new__((ulong)*(uint *)(this + 0xb0) << 3);
          *(void **)(this + 0xa0) = pvVar16;
          uVar6 = *(uint *)(this + 0xa8);
        }
        else {
          uVar6 = *(uint *)(this + 0xac) + *(int *)(this + 0xb0);
                    /* try { // try from 00ca7f3c to 00ca7fce has its CatchHandler @ 00ca8e0a */
          pvVar16 = operator_new__((ulong)uVar6 << 3);
          if (*(int *)(this + 0xac) != 0) {
            uVar18 = 0;
            do {
              uVar17 = (int)uVar18 + 1;
              *(undefined8 *)((long)pvVar16 + uVar18 * 8) =
                   *(undefined8 *)(*(long *)(this + 0xa0) + uVar18 * 8);
              uVar18 = (ulong)uVar17;
            } while (uVar17 < *(uint *)(this + 0xac));
          }
          if (*(void **)(this + 0xa0) != (void *)0x0) {
            operator_delete__(*(void **)(this + 0xa0));
          }
          *(void **)(this + 0xa0) = pvVar16;
          *(uint *)(this + 0xac) = uVar6;
          uVar6 = *(uint *)(this + 0xa8);
        }
        *(CSkillProperty **)((long)pvVar16 + (ulong)uVar6 * 8) = pCVar9;
        *(int *)(this + 0xa8) = *(int *)(this + 0xa8) + 1;
        uVar20 = uVar20 + 1;
      } while (pCVar10 != (CDataGroup *)0x0);
    }
                    /* try { // try from 00ca84f8 to 00ca84fc has its CatchHandler @ 00ca8fa8 */
    std::wstring::wstring((wstring_conflict *)local_98,L"ACTIVATION_TYPE",local_39);
                    /* try { // try from 00ca8509 to 00ca851d has its CatchHandler @ 00ca8f98 */
    pwVar12 = (wstring_conflict *)
              CDataGroup::GetDataValue
                        (*(CDataGroup **)(this + 0x28),(wstring_conflict *)local_98,
                         (wstring_conflict *)&::EMPTY_WSTRING);
    STRINGS::StringUpper((STRINGS *)local_a8,pwVar12);
    if ((allocator *)(local_98[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar2 = (int *)(local_98[0] + -8);
      iVar19 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar19 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
      }
    }
    pwVar1 = local_a8[0];
    sVar4 = *(size_t *)(local_a8[0] + -6);
    if ((sVar4 != *(size_t *)(::EMPTY_WSTRING + -6)) ||
       (iVar19 = wmemcmp(local_a8[0],::EMPTY_WSTRING,sVar4), iVar19 != 0)) {
      puVar21 = &::gSKILL_ACTIVATION_TYPE_NAMES;
      iVar19 = 0;
      do {
        if ((sVar4 == *(size_t *)((wchar_t *)*puVar21 + -6)) &&
           (iVar8 = wmemcmp(pwVar1,(wchar_t *)*puVar21,sVar4), iVar8 == 0)) {
          *(int *)(this + 0x60) = iVar19;
          break;
        }
        iVar19 = iVar19 + 1;
        puVar21 = puVar21 + 1;
      } while (iVar19 != 5);
    }
                    /* try { // try from 00ca8590 to 00ca8594 has its CatchHandler @ 00ca8d12 */
    std::wstring::wstring((wstring_conflict *)local_b8,L"SKILL_TYPE",&local_3a);
                    /* try { // try from 00ca85a1 to 00ca85b8 has its CatchHandler @ 00ca8d0c */
    pwVar12 = (wstring_conflict *)
              CDataGroup::GetDataValue
                        (*(CDataGroup **)(this + 0x28),(wstring_conflict *)local_b8,
                         (wstring_conflict *)&::EMPTY_WSTRING);
    STRINGS::StringUpper((STRINGS *)local_c8,pwVar12);
                    /* try { // try from 00ca85c4 to 00ca85c8 has its CatchHandler @ 00ca8cf4 */
    std::wstring::assign((wstring_conflict *)local_a8);
    if ((allocator *)(local_c8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar2 = (int *)(local_c8[0] + -8);
      iVar19 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar19 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
      }
    }
    if ((allocator *)(local_b8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar2 = (int *)(local_b8[0] + -8);
      iVar19 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar19 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
      }
    }
    pwVar1 = local_a8[0];
    sVar4 = *(size_t *)(local_a8[0] + -6);
    if ((sVar4 != *(size_t *)(::EMPTY_WSTRING + -6)) ||
       (iVar19 = wmemcmp(local_a8[0],::EMPTY_WSTRING,sVar4), iVar19 != 0)) {
      puVar21 = &::gSKILL_TYPE_NAMES;
      iVar19 = 0;
      do {
        if ((sVar4 == *(size_t *)((wchar_t *)*puVar21 + -6)) &&
           (iVar8 = wmemcmp(pwVar1,(wchar_t *)*puVar21,sVar4), iVar8 == 0)) {
          *(int *)(this + 0x5c) = iVar19;
          break;
        }
        iVar19 = iVar19 + 1;
        puVar21 = puVar21 + 1;
      } while (iVar19 != 4);
    }
                    /* try { // try from 00ca864a to 00ca864e has its CatchHandler @ 00ca9055 */
    std::wstring::wstring((wstring_conflict *)local_d8,L"TARGET_ALIGNMENT",&local_3b);
                    /* try { // try from 00ca865b to 00ca866f has its CatchHandler @ 00ca9025 */
    pwVar12 = (wstring_conflict *)
              CDataGroup::GetDataValue
                        (*(CDataGroup **)(this + 0x28),(wstring_conflict *)local_d8,
                         (wstring_conflict *)&::EMPTY_WSTRING);
    std::wstring::wstring((wstring_conflict *)local_e8,pwVar12);
    if ((allocator *)(local_d8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar2 = (int *)(local_d8[0] + -8);
      iVar19 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar19 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
      }
    }
    pwVar1 = local_e8[0];
    sVar4 = *(size_t *)(local_e8[0] + -6);
    if ((sVar4 != *(size_t *)(::EMPTY_WSTRING + -6)) ||
       (iVar19 = wmemcmp(local_e8[0],::EMPTY_WSTRING,sVar4), iVar19 != 0)) {
      puVar21 = &::KALIGNMENT_STRINGS;
      iVar19 = 0;
      do {
        if ((sVar4 == *(size_t *)((wchar_t *)*puVar21 + -6)) &&
           (iVar8 = wmemcmp((wchar_t *)*puVar21,pwVar1,sVar4), iVar8 == 0)) {
          *(int *)(this + 0x120) = iVar19;
          break;
        }
        iVar19 = iVar19 + 1;
        puVar21 = puVar21 + 1;
      } while (iVar19 != 7);
    }
                    /* try { // try from 00ca86de to 00ca86e2 has its CatchHandler @ 00ca8f93 */
    std::wstring::wstring((wstring_conflict *)local_f8,L"TARGET_SPECIFIC_UNITS",&local_3c);
                    /* try { // try from 00ca86ec to 00ca86f0 has its CatchHandler @ 00ca90f9 */
    lVar13 = CDataGroup::GetDataGroupByName
                       (*(CDataGroup **)(this + 0x28),(wstring_conflict *)local_f8,false);
    if ((allocator *)(local_f8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar2 = (int *)(local_f8[0] + -8);
      iVar19 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar19 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
      }
    }
    if ((lVar13 != 0) && (*(int *)(lVar13 + 0x28) != 0)) {
      uVar20 = 0;
      do {
        if (uVar20 < *(uint *)(lVar13 + 0x2c)) {
          plVar15 = (long *)((ulong)uVar20 * 8 + *(long *)(lVar13 + 0x20));
        }
        else {
          plVar15 = *(long **)(lVar13 + 0x20);
        }
        if ((*(int *)(*plVar15 + 0x30) == 8) || (*(int *)(*plVar15 + 0x30) == 5)) {
          if (uVar20 < *(uint *)(lVar13 + 0x2c)) {
            puVar21 = (undefined8 *)((ulong)uVar20 * 8 + *(long *)(lVar13 + 0x20));
          }
          else {
            puVar21 = *(undefined8 **)(lVar13 + 0x20);
          }
                    /* try { // try from 00ca874e to 00ca885b has its CatchHandler @ 00ca8d90 */
          pwVar12 = (wstring_conflict *)CDataValue::GetValueString((CDataValue *)*puVar21,true);
          this_00 = (CUnitResourceList *)CUnitResourceList::getSingleton();
          lVar14 = CUnitResourceList::getDataGroupByObjectName(this_00,pwVar12);
          if (lVar14 != 0) {
            uVar6 = *(uint *)(this + 0x80);
            if (uVar6 < *(uint *)(this + 0x84)) {
              pvVar16 = *(void **)(this + 0x78);
            }
            else if (*(long *)(this + 0x78) == 0) {
              *(uint *)(this + 0x84) = *(uint *)(this + 0x88);
              pvVar16 = operator_new__((ulong)*(uint *)(this + 0x88) << 3);
              *(void **)(this + 0x78) = pvVar16;
              uVar6 = *(uint *)(this + 0x80);
            }
            else {
              uVar6 = *(uint *)(this + 0x84) + *(int *)(this + 0x88);
              pvVar16 = operator_new__((ulong)uVar6 << 3);
              if (*(int *)(this + 0x84) != 0) {
                uVar18 = 0;
                do {
                  uVar17 = (int)uVar18 + 1;
                  *(undefined8 *)((long)pvVar16 + uVar18 * 8) =
                       *(undefined8 *)(*(long *)(this + 0x78) + uVar18 * 8);
                  uVar18 = (ulong)uVar17;
                } while (uVar17 < *(uint *)(this + 0x84));
              }
              if (*(void **)(this + 0x78) != (void *)0x0) {
                operator_delete__(*(void **)(this + 0x78));
              }
              *(void **)(this + 0x78) = pvVar16;
              *(uint *)(this + 0x84) = uVar6;
              uVar6 = *(uint *)(this + 0x80);
            }
            *(long *)((long)pvVar16 + (ulong)uVar6 * 8) = lVar14;
            *(int *)(this + 0x80) = *(int *)(this + 0x80) + 1;
          }
        }
        uVar20 = uVar20 + 1;
      } while (uVar20 < *(uint *)(lVar13 + 0x28));
    }
                    /* try { // try from 00ca7ff9 to 00ca7ffd has its CatchHandler @ 00ca90d6 */
    std::wstring::wstring((wstring_conflict *)local_108,L"TARGET_CORPSES",&local_3d);
                    /* try { // try from 00ca8007 to 00ca800b has its CatchHandler @ 00ca90c6 */
    CVar5 = (CSkill)CDataGroup::GetDataValue
                              (*(CDataGroup **)(this + 0x28),(wstring_conflict *)local_108,false);
    this[0x6e] = CVar5;
    if ((allocator *)(local_108[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_108[0] + -8);
      iVar19 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar19 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_108[0] + -0x18));
      }
    }
                    /* try { // try from 00ca803c to 00ca8040 has its CatchHandler @ 00ca8f29 */
    std::wstring::wstring((wstring_conflict *)local_118,L"LEVEL_REQUIRED",&local_3e);
                    /* try { // try from 00ca804d to 00ca8051 has its CatchHandler @ 00ca8f24 */
    uVar7 = CDataGroup::GetDataValue(*(CDataGroup **)(this + 0x28),(wstring_conflict *)local_118,1);
    *(undefined4 *)(this + 0xd8) = uVar7;
    if ((allocator *)(local_118[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_118[0] + -8);
      iVar19 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar19 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_118[0] + -0x18));
      }
    }
                    /* try { // try from 00ca8085 to 00ca8089 has its CatchHandler @ 00ca8eea */
    std::wstring::wstring((wstring_conflict *)local_128,L"MAX_INVEST_LEVEL",&local_3f);
                    /* try { // try from 00ca8093 to 00ca8097 has its CatchHandler @ 00ca8f6e */
    uVar7 = CDataGroup::GetDataValue(*(CDataGroup **)(this + 0x28),(wstring_conflict *)local_128,0);
    *(undefined4 *)(this + 0x158) = uVar7;
    if ((allocator *)(local_128[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_128[0] + -8);
      iVar19 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar19 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_128[0] + -0x18));
      }
    }
                    /* try { // try from 00ca80cb to 00ca80cf has its CatchHandler @ 00ca8f7e */
    std::wstring::wstring((wstring_conflict *)local_138,L"COLUMN",&local_40);
                    /* try { // try from 00ca80dc to 00ca80e0 has its CatchHandler @ 00ca8ee5 */
    uVar7 = CDataGroup::GetDataValue
                      (*(CDataGroup **)(this + 0x28),(wstring_conflict *)local_138,0xffffffff);
    *(undefined4 *)(this + 0x10c) = uVar7;
    if ((allocator *)(local_138[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_138[0] + -8);
      iVar19 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar19 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_138[0] + -0x18));
      }
    }
                    /* try { // try from 00ca8114 to 00ca8118 has its CatchHandler @ 00ca8eae */
    std::wstring::wstring((wstring_conflict *)local_148,L"ROW",&local_41);
                    /* try { // try from 00ca8125 to 00ca8129 has its CatchHandler @ 00ca8e9e */
    uVar7 = CDataGroup::GetDataValue
                      (*(CDataGroup **)(this + 0x28),(wstring_conflict *)local_148,0xffffffff);
    *(undefined4 *)(this + 0x110) = uVar7;
    if ((allocator *)(local_148[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_148[0] + -8);
      iVar19 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar19 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_148[0] + -0x18));
      }
    }
                    /* try { // try from 00ca815d to 00ca8161 has its CatchHandler @ 00ca8e58 */
    std::wstring::wstring((wstring_conflict *)local_158,L"PANE",&local_42);
                    /* try { // try from 00ca816b to 00ca816f has its CatchHandler @ 00ca8e53 */
    uVar7 = CDataGroup::GetDataValue(*(CDataGroup **)(this + 0x28),(wstring_conflict *)local_158,0);
    *(undefined4 *)(this + 0x114) = uVar7;
    if ((allocator *)(local_158[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_158[0] + -8);
      iVar19 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar19 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_158[0] + -0x18));
      }
    }
                    /* try { // try from 00ca81a3 to 00ca81a7 has its CatchHandler @ 00ca8e22 */
    std::wstring::wstring((wstring_conflict *)local_168,L"CHARGES",&local_43);
                    /* try { // try from 00ca81b4 to 00ca81b8 has its CatchHandler @ 00ca8cd4 */
    uVar7 = CDataGroup::GetDataValue
                      (*(CDataGroup **)(this + 0x28),(wstring_conflict *)local_168,0xffffffff);
    *(undefined4 *)(this + 0x124) = uVar7;
    if ((allocator *)(local_168[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_168[0] + -8);
      iVar19 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar19 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_168[0] + -0x18));
      }
    }
                    /* try { // try from 00ca81ec to 00ca81f0 has its CatchHandler @ 00ca8ce4 */
    std::wstring::wstring((wstring_conflict *)local_178,L"HIDDEN",&local_44);
                    /* try { // try from 00ca81fa to 00ca81fe has its CatchHandler @ 00ca8ca1 */
    CVar5 = (CSkill)CDataGroup::GetDataValue
                              (*(CDataGroup **)(this + 0x28),(wstring_conflict *)local_178,false);
    this[0x6b] = CVar5;
    if ((allocator *)(local_178[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_178[0] + -8);
      iVar19 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar19 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_178[0] + -0x18));
      }
    }
                    /* try { // try from 00ca822f to 00ca8233 has its CatchHandler @ 00ca8c6e */
    std::wstring::wstring((wstring_conflict *)local_188,L"ALLOWS_TURNING",&local_45);
                    /* try { // try from 00ca8240 to 00ca8244 has its CatchHandler @ 00ca8c5e */
    CVar5 = (CSkill)CDataGroup::GetDataValue
                              (*(CDataGroup **)(this + 0x28),(wstring_conflict *)local_188,true);
    this[0x66] = CVar5;
    if ((allocator *)(local_188[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_188[0] + -8);
      iVar19 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar19 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_188[0] + -0x18));
      }
    }
                    /* try { // try from 00ca8275 to 00ca8279 has its CatchHandler @ 00ca8c1f */
    std::wstring::wstring((wstring_conflict *)local_198,L"MOVES_TO_TARGET",&local_46);
                    /* try { // try from 00ca8283 to 00ca8287 has its CatchHandler @ 00ca8c1a */
    CVar5 = (CSkill)CDataGroup::GetDataValue
                              (*(CDataGroup **)(this + 0x28),(wstring_conflict *)local_198,false);
    this[0x68] = CVar5;
    if ((allocator *)(local_198[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_198[0] + -8);
      iVar19 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar19 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_198[0] + -0x18));
      }
    }
                    /* try { // try from 00ca82b8 to 00ca82bc has its CatchHandler @ 00ca8be9 */
    std::wstring::wstring((wstring_conflict *)local_1a8,L"DONT_STOP_ON_DEATH",&local_47);
                    /* try { // try from 00ca82c6 to 00ca82ca has its CatchHandler @ 00ca8bd9 */
    CVar5 = (CSkill)CDataGroup::GetDataValue
                              (*(CDataGroup **)(this + 0x28),(wstring_conflict *)local_1a8,false);
    this[0x67] = CVar5;
    if ((allocator *)(local_1a8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_1a8[0] + -8);
      iVar19 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar19 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_1a8[0] + -0x18));
      }
    }
                    /* try { // try from 00ca82fb to 00ca82ff has its CatchHandler @ 00ca8ba8 */
    std::wstring::wstring((wstring_conflict *)local_1b8,L"CAN_BE_SILENCED",&local_48);
                    /* try { // try from 00ca830c to 00ca8310 has its CatchHandler @ 00ca8ba3 */
    CVar5 = (CSkill)CDataGroup::GetDataValue
                              (*(CDataGroup **)(this + 0x28),(wstring_conflict *)local_1b8,true);
    this[0x70] = CVar5;
    if ((allocator *)(local_1b8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_1b8[0] + -8);
      iVar19 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar19 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_1b8[0] + -0x18));
      }
    }
                    /* try { // try from 00ca8341 to 00ca8345 has its CatchHandler @ 00ca8ac2 */
    std::wstring::wstring((wstring_conflict *)local_1c8,L"CAN_LEFT_MAP",&local_49);
                    /* try { // try from 00ca834f to 00ca8353 has its CatchHandler @ 00ca8ab3 */
    CVar5 = (CSkill)CDataGroup::GetDataValue
                              (*(CDataGroup **)(this + 0x28),(wstring_conflict *)local_1c8,false);
    this[0x6f] = CVar5;
    if ((allocator *)(local_1c8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_1c8[0] + -8);
      iVar19 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar19 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_1c8[0] + -0x18));
      }
    }
                    /* try { // try from 00ca8381 to 00ca8385 has its CatchHandler @ 00ca8a7a */
    std::wstring::wstring((wstring_conflict *)local_1d8,L"USEWEAPONANIMATION",&local_4a);
                    /* try { // try from 00ca838f to 00ca8393 has its CatchHandler @ 00ca8a6d */
    CVar5 = (CSkill)CDataGroup::GetDataValue
                              (*(CDataGroup **)(this + 0x28),(wstring_conflict *)local_1d8,false);
    this[0x6c] = CVar5;
    if ((allocator *)(local_1d8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_1d8[0] + -8);
      iVar19 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar19 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_1d8[0] + -0x18));
      }
    }
                    /* try { // try from 00ca83be to 00ca83c2 has its CatchHandler @ 00ca8a01 */
    std::wstring::wstring((wstring_conflict *)local_1e8,L"REQUIRES_PASSABLE_LOS",&local_4b);
                    /* try { // try from 00ca83cc to 00ca83d0 has its CatchHandler @ 00ca8b7e */
    CVar5 = (CSkill)CDataGroup::GetDataValue
                              (*(CDataGroup **)(this + 0x28),(wstring_conflict *)local_1e8,false);
    this[0x69] = CVar5;
    if ((allocator *)(local_1e8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_1e8[0] + -8);
      iVar19 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar19 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_1e8[0] + -0x18));
      }
    }
                    /* try { // try from 00ca83fb to 00ca83ff has its CatchHandler @ 00ca8b8e */
    std::wstring::wstring((wstring_conflict *)local_1f8,L"REQUIRES_PATHABLE",&local_4c);
                    /* try { // try from 00ca8409 to 00ca840d has its CatchHandler @ 00ca8af7 */
    CVar5 = (CSkill)CDataGroup::GetDataValue
                              (*(CDataGroup **)(this + 0x28),(wstring_conflict *)local_1f8,false);
    this[0x6a] = CVar5;
    if ((allocator *)(local_1f8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_1f8[0] + -8);
      iVar19 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar19 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_1f8[0] + -0x18));
      }
    }
                    /* try { // try from 00ca8438 to 00ca843c has its CatchHandler @ 00ca8ddf */
    std::wstring::wstring((wstring_conflict *)local_208,L"UNIQUE_GUID",&local_4d);
                    /* try { // try from 00ca844b to 00ca844f has its CatchHandler @ 00ca8dcf */
    uVar11 = CDataGroup::GetDataValue
                       (*(CDataGroup **)(this + 0x28),(wstring_conflict *)local_208,-1);
    *(undefined8 *)(this + 0x150) = uVar11;
    if ((allocator *)(local_208[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_208[0] + -8);
      iVar19 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar19 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_208[0] + -0x18));
      }
    }
    if ((allocator *)(local_e8[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      pwVar1 = local_e8[0] + -2;
      wVar3 = *pwVar1;
      *pwVar1 = *pwVar1 + L'\xffffffff';
      UNLOCK();
      if (wVar3 < L'\x01') {
        std::wstring::_Rep::_M_destroy((allocator *)(local_e8[0] + -6));
      }
    }
    if ((allocator *)(local_a8[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      pwVar1 = local_a8[0] + -2;
      wVar3 = *pwVar1;
      *pwVar1 = *pwVar1 + L'\xffffffff';
      UNLOCK();
      if (wVar3 < L'\x01') {
        std::wstring::_Rep::_M_destroy((allocator *)(local_a8[0] + -6));
      }
    }
  }
                    /* try { // try from 00ca84bf to 00ca84c3 has its CatchHandler @ 00ca8e0a */
  _setLevelOfSkillFromSkillManager(this,*(uint *)(this + 0xdc));
  return;
}



/* address=00ca9150
   symbol=CSkill::startSkill */

/* CSkill::startSkill(CBaseUnit*, ESKILL_ACTIVATION_TYPE, Ogre::Vector3 const&, Ogre::Quaternion
   const&, Ogre::Vector3 const&, CBaseUnit*) */

undefined8 __thiscall
CSkill::startSkill(CSkill *this,CBaseUnit *param_1,undefined8 param_3,undefined8 param_4,
                  undefined8 param_5,undefined4 *param_6,CRunicCore *param_7)

{
  CRunicCore *pCVar1;
  char cVar2;
  undefined4 uVar3;

  if ((param_1 != (CBaseUnit *)0x0) && (*(long *)(this + 0x90) != 0)) {
    this[0x65] = (CSkill)0x0;
    assignSkillAnimations(this,param_1);
    calculateEffectiveSkillLevel(this);
    cVar2 = rollSkillChance(this);
    if (cVar2 != '\0') {
      pCVar1 = *(CRunicCore **)(this + 0x30);
      if (param_1 != (CBaseUnit *)pCVar1) {
        if (pCVar1 != (CRunicCore *)0x0) {
          CRunicCore::removeSafePointer(pCVar1,(TSafePointer *)(this + 0x30),*(uint *)(this + 0x38))
          ;
        }
        *(undefined8 *)(this + 0x30) = 0;
        uVar3 = CRunicCore::addSafePointer((CRunicCore *)param_1,(TSafePointer *)(this + 0x30));
        *(CBaseUnit **)(this + 0x30) = param_1;
        *(undefined4 *)(this + 0x38) = uVar3;
      }
      pCVar1 = *(CRunicCore **)(this + 0x40);
      if (param_7 != pCVar1) {
        if (pCVar1 != (CRunicCore *)0x0) {
          CRunicCore::removeSafePointer(pCVar1,(TSafePointer *)(this + 0x40),*(uint *)(this + 0x48))
          ;
        }
        *(undefined8 *)(this + 0x40) = 0;
        if (param_7 != (CRunicCore *)0x0) {
          uVar3 = CRunicCore::addSafePointer(param_7,(TSafePointer *)(this + 0x40));
          *(undefined4 *)(this + 0x48) = uVar3;
        }
        *(CRunicCore **)(this + 0x40) = param_7;
      }
      *(undefined4 *)(this + 0x50) = *param_6;
      *(undefined4 *)(this + 0x54) = param_6[1];
      *(undefined4 *)(this + 0x58) = param_6[2];
      if (*(int *)(*(long *)(this + 0x30) + 0x188) == 0) {
        *(undefined4 *)(*(long *)(this + 0x90) + 0x50) = *(undefined4 *)(this + 0x120);
      }
      this[100] = (CSkill)0x1;
      uVar3 = CSkillProperty::getCoolDown(*(CSkillProperty **)(this + 0x90));
      *(undefined4 *)(this + 0xfc) = uVar3;
      *(undefined4 *)(this + 0x108) = 0;
      *(undefined4 *)(this + 0xf8) = 0x3f800000;
      *(undefined4 *)(this + 0x104) = *(undefined4 *)(this + 0x100);
      triggerEvent(this,0,param_4,param_5,param_7,param_6);
      return 1;
    }
  }
  return 0;
}



/* address=00ca92e0
   symbol=CSkill::getDescription */

/* WARNING: Removing unreachable block (ram,0x00ca99e1) */
/* WARNING: Removing unreachable block (ram,0x00ca9b02) */
/* WARNING: Removing unreachable block (ram,0x00ca99ef) */
/* WARNING: Removing unreachable block (ram,0x00ca9b92) */
/* WARNING: Removing unreachable block (ram,0x00ca9bae) */
/* WARNING: Removing unreachable block (ram,0x00ca9bbc) */
/* WARNING: Removing unreachable block (ram,0x00ca99fd) */
/* WARNING: Removing unreachable block (ram,0x00ca9ba0) */
/* CSkill::getDescription(CBaseUnit*, unsigned int, bool) */

CBaseUnit * CSkill::getDescription(CBaseUnit *param_1,uint param_2,bool param_3)

{
  TSafePointer<CBaseUnit> *this;
  int *piVar1;
  uint uVar2;
  CRunicCore *this_00;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  int in_ECX;
  uint uVar6;
  undefined7 in_register_00000011;
  CRunicCore *pCVar7;
  long *plVar8;
  undefined4 in_register_00000034;
  long lVar9;
  char in_R8B;
  long lVar10;
  long local_138;
  long local_128 [2];
  long local_118 [2];
  long local_108 [2];
  long local_f8 [2];
  wstring_conflict local_e8 [16];
  wstring_conflict local_d8 [16];
  STRINGS local_c8 [16];
  wstring_conflict local_b8 [16];
  wstring_conflict local_a8 [16];
  wstring_conflict local_98 [16];
  wstring_conflict local_88 [16];
  wstring_conflict local_78 [16];
  long local_68 [2];
  undefined4 *local_58 [2];
  long local_48 [3];

  lVar9 = CONCAT44(in_register_00000034,param_2);
  pCVar7 = (CRunicCore *)CONCAT71(in_register_00000011,param_3);
  if (*(long *)(lVar9 + 0x90) != 0) {
    this_00 = *(CRunicCore **)(lVar9 + 0x30);
    this = (TSafePointer<CBaseUnit> *)(lVar9 + 0x30);
    if (pCVar7 != this_00) {
      if (this_00 != (CRunicCore *)0x0) {
        CRunicCore::removeSafePointer(this_00,(TSafePointer *)this,*(uint *)(lVar9 + 0x38));
      }
      *(undefined8 *)(lVar9 + 0x30) = 0;
      if (pCVar7 != (CRunicCore *)0x0) {
        uVar3 = CRunicCore::addSafePointer(pCVar7,(TSafePointer *)this);
        *(undefined4 *)(lVar9 + 0x38) = uVar3;
      }
      *(CRunicCore **)(lVar9 + 0x30) = pCVar7;
    }
    if ((getDescription(CBaseUnit*,unsigned_int,bool)::g_ManaCost == '\0') &&
       (iVar5 = __cxa_guard_acquire(&getDescription(CBaseUnit*,unsigned_int,bool)::g_ManaCost),
       iVar5 != 0)) {
      getDescription(CBaseUnit*,unsigned_int,bool)::g_ManaCost = &DAT_01424558;
      __cxa_guard_release(&getDescription(CBaseUnit*,unsigned_int,bool)::g_ManaCost);
      __cxa_atexit(std::wstring::~wstring,&getDescription(CBaseUnit*,unsigned_int,bool)::g_ManaCost,
                   &__dso_handle);
    }
    if (*(long *)(getDescription(CBaseUnit*,unsigned_int,bool)::g_ManaCost + -6) == 0) {
      CStringTranslate::getSinglton();
      CStringTranslate::getTranslateString((wchar_t *)local_48);
                    /* try { // try from 00ca951d to 00ca9521 has its CatchHandler @ 00ca9b65 */
      std::wstring::assign
                ((wstring_conflict *)&getDescription(CBaseUnit*,unsigned_int,bool)::g_ManaCost);
      if ((allocator *)(local_48[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_48[0] + -8);
        iVar5 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar5 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
        }
      }
    }
    uVar4 = in_ECX - 1;
    if (0xfffffffd < uVar4) {
      uVar4 = *(int *)(lVar9 + 0xe0) - 1;
    }
    uVar2 = *(uint *)(lVar9 + 0xa8);
    if (uVar2 == 0) {
      lVar10 = *(long *)(lVar9 + 0x90);
      uVar6 = 1;
    }
    else {
      lVar10 = **(long **)(lVar9 + 0xa0);
      uVar6 = uVar2;
    }
    if ((uVar4 <= uVar6) && (uVar4 < uVar2)) {
      if (uVar4 < *(uint *)(lVar9 + 0xac)) {
        plVar8 = (long *)((ulong)uVar4 * 8 + *(long *)(lVar9 + 0xa0));
      }
      else {
        plVar8 = *(long **)(lVar9 + 0xa0);
      }
      if (*plVar8 != 0) {
        if (uVar4 < *(uint *)(lVar9 + 0xac)) {
          plVar8 = (long *)((ulong)uVar4 * 8 + *(long *)(lVar9 + 0xa0));
        }
        else {
          plVar8 = *(long **)(lVar9 + 0xa0);
        }
        lVar10 = *plVar8;
      }
    }
    if (lVar10 != 0) {
      local_58[0] = &DAT_01424558;
      if (in_R8B == '\0') {
        if (DAT_00fa47f8 < *(float *)(lVar10 + 0x78)) {
          STRINGS::GetValueAsWString((STRINGS *)local_108,*(float *)(lVar10 + 0x78));
                    /* try { // try from 00ca979c to 00ca97a0 has its CatchHandler @ 00ca9a8b */
          std::wstring::wstring
                    ((wstring_conflict *)local_f8,
                     (wstring_conflict *)&getDescription(CBaseUnit*,unsigned_int,bool)::g_ManaCost);
          wcslen(L":");
                    /* try { // try from 00ca97b8 to 00ca97bc has its CatchHandler @ 00ca9a74 */
          std::wstring::append((wchar_t *)local_f8,0xfe4ec0);
                    /* try { // try from 00ca97cc to 00ca97d0 has its CatchHandler @ 00ca9a67 */
          std::operator+((wstring_conflict *)local_118,(wstring_conflict *)local_f8);
                    /* try { // try from 00ca97db to 00ca97df has its CatchHandler @ 00ca9a5a */
          std::wstring::wstring((wstring_conflict *)local_128,(wstring_conflict *)local_118);
          wcslen(L"\n");
                    /* try { // try from 00ca97f7 to 00ca97fb has its CatchHandler @ 00ca9a43 */
          std::wstring::append((wchar_t *)local_128,0xfd0b48);
                    /* try { // try from 00ca980c to 00ca9810 has its CatchHandler @ 00ca9a08 */
          std::wstring::assign((wstring_conflict *)local_58);
          if ((allocator *)(local_128[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_128[0] + -8);
            iVar5 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar5 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_128[0] + -0x18));
            }
          }
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
          if ((allocator *)(local_f8[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_f8[0] + -8);
            iVar5 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar5 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
            }
          }
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
      }
      else {
                    /* try { // try from 00ca95c8 to 00ca95cc has its CatchHandler @ 00ca9b8a */
        std::wstring::wstring((wstring_conflict *)local_68,(wstring_conflict *)(lVar10 + 0xe0));
        wcslen(L"\n");
                    /* try { // try from 00ca95e7 to 00ca95eb has its CatchHandler @ 00ca9b33 */
        std::wstring::append((wchar_t *)local_68,0xfd0b48);
                    /* try { // try from 00ca95ff to 00ca9603 has its CatchHandler @ 00ca9b50 */
        std::wstring::assign((wstring_conflict *)local_58);
        if ((allocator *)(local_68[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_68[0] + -8);
          iVar5 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar5 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
          }
        }
        if (DAT_00fa47f8 < *(float *)(lVar10 + 0x78)) {
                    /* try { // try from 00ca9639 to 00ca963d has its CatchHandler @ 00ca9b8a */
          STRINGS::GetValueAsWString(local_c8,*(float *)(lVar10 + 0x78));
                    /* try { // try from 00ca9649 to 00ca964d has its CatchHandler @ 00ca9b2e */
          CSkillProperty::getSkillDescription();
                    /* try { // try from 00ca9661 to 00ca9665 has its CatchHandler @ 00ca9b29 */
          std::operator+(local_88,(wstring_conflict *)local_58);
                    /* try { // try from 00ca967b to 00ca967f has its CatchHandler @ 00ca9b24 */
          std::operator+(local_98,(wchar_t *)local_88);
                    /* try { // try from 00ca9695 to 00ca9699 has its CatchHandler @ 00ca9b1f */
          std::operator+(local_a8,local_98);
                    /* try { // try from 00ca96af to 00ca96b3 has its CatchHandler @ 00ca9b1a */
          std::operator+(local_b8,(wchar_t *)local_a8);
                    /* try { // try from 00ca96c9 to 00ca96cd has its CatchHandler @ 00ca9b15 */
          std::operator+(local_d8,local_b8);
                    /* try { // try from 00ca96dd to 00ca96e1 has its CatchHandler @ 00ca9b10 */
          std::operator+(local_e8,(wchar_t *)local_d8);
                    /* try { // try from 00ca96ea to 00ca96ee has its CatchHandler @ 00ca9a98 */
          std::wstring::assign((wstring_conflict *)local_58);
                    /* try { // try from 00ca96f4 to 00ca96f8 has its CatchHandler @ 00ca9b10 */
          std::wstring::~wstring(local_e8);
                    /* try { // try from 00ca96fe to 00ca9702 has its CatchHandler @ 00ca9b15 */
          std::wstring::~wstring(local_d8);
                    /* try { // try from 00ca970b to 00ca970f has its CatchHandler @ 00ca9b1a */
          std::wstring::~wstring(local_b8);
                    /* try { // try from 00ca9718 to 00ca971c has its CatchHandler @ 00ca9b1f */
          std::wstring::~wstring(local_a8);
                    /* try { // try from 00ca9725 to 00ca9729 has its CatchHandler @ 00ca9b24 */
          std::wstring::~wstring(local_98);
                    /* try { // try from 00ca9732 to 00ca9736 has its CatchHandler @ 00ca9b29 */
          std::wstring::~wstring(local_88);
                    /* try { // try from 00ca973f to 00ca9743 has its CatchHandler @ 00ca9b2e */
          std::wstring::~wstring(local_78);
                    /* try { // try from 00ca974c to 00ca9791 has its CatchHandler @ 00ca9b8a */
          std::wstring::~wstring((wstring_conflict *)local_c8);
        }
      }
                    /* try { // try from 00ca9419 to 00ca941d has its CatchHandler @ 00ca9b8a */
      CSkillProperty::getSkillStats();
                    /* try { // try from 00ca9426 to 00ca942a has its CatchHandler @ 00ca9b78 */
      std::wstring::append((wstring_conflict *)local_58);
      if ((allocator *)(local_138 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
         ) {
        LOCK();
        piVar1 = (int *)(local_138 + -8);
        iVar5 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar5 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_138 + -0x18));
        }
      }
      if (local_58[0][*(long *)(local_58[0] + -6) + -1] != 10) {
        wcslen(L"\n");
                    /* try { // try from 00ca9469 to 00ca94b0 has its CatchHandler @ 00ca9b8a */
        std::wstring::append((wchar_t *)local_58,0xfd0b48);
      }
      pCVar7 = *(CRunicCore **)(lVar9 + 0x30);
      if (this_00 != pCVar7) {
        if (pCVar7 != (CRunicCore *)0x0) {
          CRunicCore::removeSafePointer(pCVar7,(TSafePointer *)this,*(uint *)(lVar9 + 0x38));
        }
        *(undefined8 *)(lVar9 + 0x30) = 0;
        if (this_00 != (CRunicCore *)0x0) {
          uVar3 = CRunicCore::addSafePointer(this_00,(TSafePointer *)this);
          *(undefined4 *)(lVar9 + 0x38) = uVar3;
        }
        *(CRunicCore **)(lVar9 + 0x30) = this_00;
      }
      std::wstring::wstring((wstring_conflict *)param_1,(wstring_conflict *)local_58);
      if ((allocator *)(local_58[0] + -6) == (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
      {
        return param_1;
      }
      LOCK();
      piVar1 = local_58[0] + -2;
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (0 < iVar5) {
        return param_1;
      }
      std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -6));
      return param_1;
    }
    TSafePointer<CBaseUnit>::setObject(this,(CBaseUnit *)this_00);
  }
  std::wstring::wstring((wstring_conflict *)param_1,(wstring_conflict *)&::EMPTY_WSTRING);
  return param_1;
}



/* address=00ca9bd0
   symbol=CSkill::getDescriptionRequirments */

/* WARNING: Removing unreachable block (ram,0x00caab72) */
/* WARNING: Removing unreachable block (ram,0x00caaa6e) */
/* WARNING: Removing unreachable block (ram,0x00caaafc) */
/* WARNING: Removing unreachable block (ram,0x00caaae0) */
/* WARNING: Removing unreachable block (ram,0x00caab0a) */
/* WARNING: Removing unreachable block (ram,0x00caab18) */
/* WARNING: Removing unreachable block (ram,0x00caaaee) */
/* WARNING: Removing unreachable block (ram,0x00caabc0) */
/* WARNING: Removing unreachable block (ram,0x00caaa60) */
/* WARNING: Removing unreachable block (ram,0x00caa9d7) */
/* WARNING: Removing unreachable block (ram,0x00caaac2) */
/* WARNING: Removing unreachable block (ram,0x00caa907) */
/* WARNING: Removing unreachable block (ram,0x00caaad0) */
/* WARNING: Removing unreachable block (ram,0x00caab8e) */
/* WARNING: Removing unreachable block (ram,0x00caab9c) */
/* WARNING: Removing unreachable block (ram,0x00caabb2) */
/* WARNING: Removing unreachable block (ram,0x00caa9ea) */
/* WARNING: Removing unreachable block (ram,0x00caa915) */
/* WARNING: Removing unreachable block (ram,0x00caabce) */
/* WARNING: Removing unreachable block (ram,0x00caaa06) */
/* WARNING: Removing unreachable block (ram,0x00caa9f8) */
/* WARNING: Removing unreachable block (ram,0x00caaa52) */
/* WARNING: Removing unreachable block (ram,0x00caab80) */
/* CSkill::getDescriptionRequirments(CBaseUnit*) */

CBaseUnit * CSkill::getDescriptionRequirments(CBaseUnit *param_1)

{
  int *piVar1;
  char cVar2;
  long lVar3;
  int iVar4;
  CCharacter *pCVar5;
  long in_RDX;
  CSkill *in_RSI;
  long local_1c8 [2];
  long local_1b8 [2];
  long local_1a8 [2];
  long local_198 [2];
  long local_188 [2];
  long local_178 [2];
  wstring_conflict local_168 [16];
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
  long local_a8 [2];
  long local_98 [2];
  long local_88 [2];
  long local_78 [2];
  long local_68 [2];
  long local_58 [3];
  allocator local_39 [9];

  if (((in_RDX == 0) || (*(long *)(in_RSI + 0x90) == 0)) ||
     (pCVar5 = (CCharacter *)__dynamic_cast(), pCVar5 == (CCharacter *)0x0)) {
    std::wstring::wstring((wstring_conflict *)param_1,(wstring_conflict *)&::EMPTY_WSTRING);
    return param_1;
  }
  weaponRequirementsMet(in_RSI,pCVar5);
  cVar2 = *(char *)(*(long *)(in_RSI + 0x90) + 0x18);
  if ((getDescriptionRequirments(CBaseUnit*)::g_Weapon == '\0') &&
     (iVar4 = __cxa_guard_acquire(&getDescriptionRequirments(CBaseUnit*)::g_Weapon), iVar4 != 0)) {
    getDescriptionRequirments(CBaseUnit*)::g_Weapon = &DAT_01424558;
    __cxa_guard_release(&getDescriptionRequirments(CBaseUnit*)::g_Weapon);
    __cxa_atexit(std::wstring::~wstring,&getDescriptionRequirments(CBaseUnit*)::g_Weapon,
                 &__dso_handle);
    lVar3 = *(long *)(getDescriptionRequirments(CBaseUnit*)::g_Weapon + -6);
  }
  else {
    lVar3 = *(long *)(getDescriptionRequirments(CBaseUnit*)::g_Weapon + -6);
  }
  if (lVar3 == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_58);
                    /* try { // try from 00caa115 to 00caa119 has its CatchHandler @ 00caab65 */
    std::wstring::assign((wstring_conflict *)&getDescriptionRequirments(CBaseUnit*)::g_Weapon);
    if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_58[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
      }
    }
  }
  if ((getDescriptionRequirments(CBaseUnit*)::g_Weapons == '\0') &&
     (iVar4 = __cxa_guard_acquire(&getDescriptionRequirments(CBaseUnit*)::g_Weapons), iVar4 != 0)) {
    getDescriptionRequirments(CBaseUnit*)::g_Weapons = &DAT_01424558;
    __cxa_guard_release(&getDescriptionRequirments(CBaseUnit*)::g_Weapons);
    __cxa_atexit(std::wstring::~wstring,&getDescriptionRequirments(CBaseUnit*)::g_Weapons,
                 &__dso_handle);
  }
  if (*(long *)(getDescriptionRequirments(CBaseUnit*)::g_Weapons + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_68);
                    /* try { // try from 00ca9c91 to 00ca9c95 has its CatchHandler @ 00caab46 */
    std::wstring::assign((wstring_conflict *)&getDescriptionRequirments(CBaseUnit*)::g_Weapons);
    if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_68[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
      }
    }
  }
                    /* try { // try from 00ca9cc7 to 00ca9ccb has its CatchHandler @ 00caab3e */
  std::wstring::wstring((wstring_conflict *)local_78,L"",local_39);
  if (cVar2 == '\0') {
    if ((*(int *)(*(long *)(in_RSI + 0x90) + 0x10) == 0) &&
       (*(int *)(*(long *)(in_RSI + 0x90) + 0x14) == 0)) goto LAB_00caa020;
  }
  else {
    if ((getDescriptionRequirments(CBaseUnit*)::g_DuelWieldOnly == '\0') &&
       (iVar4 = __cxa_guard_acquire(&getDescriptionRequirments(CBaseUnit*)::g_DuelWieldOnly),
       iVar4 != 0)) {
      getDescriptionRequirments(CBaseUnit*)::g_DuelWieldOnly = &DAT_01424558;
      __cxa_guard_release(&getDescriptionRequirments(CBaseUnit*)::g_DuelWieldOnly);
      __cxa_atexit(std::wstring::~wstring,&getDescriptionRequirments(CBaseUnit*)::g_DuelWieldOnly,
                   &__dso_handle);
    }
    if (*(long *)(getDescriptionRequirments(CBaseUnit*)::g_DuelWieldOnly + -6) == 0) {
                    /* try { // try from 00caa1b0 to 00caa1cc has its CatchHandler @ 00caab4e */
      CStringTranslate::getSinglton();
      CStringTranslate::getTranslateString((wchar_t *)local_88);
                    /* try { // try from 00caa1d5 to 00caa1d9 has its CatchHandler @ 00caa8ec */
      std::wstring::assign
                ((wstring_conflict *)&getDescriptionRequirments(CBaseUnit*)::g_DuelWieldOnly);
      if ((allocator *)(local_88[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_88[0] + -8);
        iVar4 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar4 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
        }
      }
    }
                    /* try { // try from 00ca9d04 to 00ca9d08 has its CatchHandler @ 00caab4e */
    std::wstring::wstring
              ((wstring_conflict *)local_98,
               (wstring_conflict *)&getDescriptionRequirments(CBaseUnit*)::g_DuelWieldOnly);
    wcslen(L".\n");
                    /* try { // try from 00ca9d1e to 00ca9d22 has its CatchHandler @ 00caab52 */
    std::wstring::append((wchar_t *)local_98,0xff4c20);
                    /* try { // try from 00ca9d29 to 00ca9d2d has its CatchHandler @ 00caab57 */
    std::wstring::assign((wstring_conflict *)local_78);
    if ((allocator *)(local_98[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_98[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
      }
    }
    iVar4 = *(int *)(*(long *)(in_RSI + 0x90) + 0x10);
    if ((iVar4 != 0) && (iVar4 == *(int *)(*(long *)(in_RSI + 0x90) + 0x14))) {
      if ((getDescriptionRequirments(CBaseUnit*)::g_RightAndLeftReq == '\0') &&
         (iVar4 = __cxa_guard_acquire(&getDescriptionRequirments(CBaseUnit*)::g_RightAndLeftReq),
         iVar4 != 0)) {
        getDescriptionRequirments(CBaseUnit*)::g_RightAndLeftReq = &DAT_01424558;
        __cxa_guard_release(&getDescriptionRequirments(CBaseUnit*)::g_RightAndLeftReq);
        __cxa_atexit(std::wstring::~wstring,
                     &getDescriptionRequirments(CBaseUnit*)::g_RightAndLeftReq,&__dso_handle);
      }
      if (*(long *)(getDescriptionRequirments(CBaseUnit*)::g_RightAndLeftReq + -6) == 0) {
                    /* try { // try from 00caa24c to 00caa268 has its CatchHandler @ 00caab4e */
        CStringTranslate::getSinglton();
        CStringTranslate::getTranslateString((wchar_t *)local_a8);
                    /* try { // try from 00caa271 to 00caa275 has its CatchHandler @ 00caaade */
        std::wstring::assign
                  ((wstring_conflict *)&getDescriptionRequirments(CBaseUnit*)::g_RightAndLeftReq);
        if ((allocator *)(local_a8[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_a8[0] + -8);
          iVar4 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar4 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
          }
        }
      }
                    /* try { // try from 00caa29d to 00caa2a1 has its CatchHandler @ 00caab4e */
      getWeaponString(local_c8,*(undefined4 *)(*(long *)(in_RSI + 0x90) + 0x10));
                    /* try { // try from 00caa2b2 to 00caa2b6 has its CatchHandler @ 00caa9ab */
      std::wstring::wstring
                ((wstring_conflict *)local_b8,
                 (wstring_conflict *)&getDescriptionRequirments(CBaseUnit*)::g_RightAndLeftReq);
      wcslen(L" ");
                    /* try { // try from 00caa2cc to 00caa2d0 has its CatchHandler @ 00caa99e */
      std::wstring::append((wchar_t *)local_b8,0xfd0b98);
                    /* try { // try from 00caa2e4 to 00caa2e8 has its CatchHandler @ 00caa999 */
      std::operator+((wstring_conflict *)local_d8,(wstring_conflict *)local_b8);
                    /* try { // try from 00caa2fc to 00caa300 has its CatchHandler @ 00caa96f */
      std::wstring::wstring((wstring_conflict *)local_e8,(wstring_conflict *)local_d8);
      wcslen(L" ");
                    /* try { // try from 00caa316 to 00caa31a has its CatchHandler @ 00caa9bd */
      std::wstring::append((wchar_t *)local_e8,0xfd0b98);
                    /* try { // try from 00caa32e to 00caa332 has its CatchHandler @ 00caa9b0 */
      std::operator+((wstring_conflict *)local_f8,(wstring_conflict *)local_e8);
                    /* try { // try from 00caa339 to 00caa33d has its CatchHandler @ 00caa9ca */
      std::wstring::append((wstring_conflict *)local_78);
      if ((allocator *)(local_f8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_f8[0] + -8);
        iVar4 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar4 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
        }
      }
      if ((allocator *)(local_e8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_e8[0] + -8);
        iVar4 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar4 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
        }
      }
      if ((allocator *)(local_d8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_d8[0] + -8);
        iVar4 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar4 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
        }
      }
      if ((allocator *)(local_b8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_b8[0] + -8);
        iVar4 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar4 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
        }
      }
      if ((allocator *)(local_c8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_c8[0] + -8);
        iVar4 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar4 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
        }
      }
      goto LAB_00caa020;
    }
  }
  if ((getDescriptionRequirments(CBaseUnit*)::g_RightReq == '\0') &&
     (iVar4 = __cxa_guard_acquire(&getDescriptionRequirments(CBaseUnit*)::g_RightReq), iVar4 != 0))
  {
    getDescriptionRequirments(CBaseUnit*)::g_RightReq = &DAT_01424558;
    __cxa_guard_release(&getDescriptionRequirments(CBaseUnit*)::g_RightReq);
    __cxa_atexit(std::wstring::~wstring,&getDescriptionRequirments(CBaseUnit*)::g_RightReq,
                 &__dso_handle);
  }
  if (*(long *)(getDescriptionRequirments(CBaseUnit*)::g_RightReq + -6) == 0) {
                    /* try { // try from 00caa3e0 to 00caa3fc has its CatchHandler @ 00caab4e */
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_108);
                    /* try { // try from 00caa405 to 00caa409 has its CatchHandler @ 00caa9e5 */
    std::wstring::assign((wstring_conflict *)&getDescriptionRequirments(CBaseUnit*)::g_RightReq);
    if ((allocator *)(local_108[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_108[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_108[0] + -0x18));
      }
    }
  }
                    /* try { // try from 00ca9d8c to 00ca9d90 has its CatchHandler @ 00caab4e */
  getWeaponString(local_128,*(undefined4 *)(*(long *)(in_RSI + 0x90) + 0x10));
                    /* try { // try from 00ca9da1 to 00ca9da5 has its CatchHandler @ 00caabaa */
  std::wstring::wstring
            ((wstring_conflict *)local_118,
             (wstring_conflict *)&getDescriptionRequirments(CBaseUnit*)::g_RightReq);
  wcslen(L" ");
                    /* try { // try from 00ca9dbb to 00ca9dbf has its CatchHandler @ 00caab26 */
  std::wstring::append((wchar_t *)local_118,0xfd0b98);
                    /* try { // try from 00ca9dd3 to 00ca9dd7 has its CatchHandler @ 00caab36 */
  std::operator+((wstring_conflict *)local_138,(wstring_conflict *)local_118);
                    /* try { // try from 00ca9deb to 00ca9def has its CatchHandler @ 00caa920 */
  std::wstring::wstring((wstring_conflict *)local_148,(wstring_conflict *)local_138);
  wcslen(L" ");
                    /* try { // try from 00ca9e05 to 00ca9e09 has its CatchHandler @ 00caa947 */
  std::wstring::append((wchar_t *)local_148,0xfd0b98);
                    /* try { // try from 00ca9e1a to 00ca9e1e has its CatchHandler @ 00caa954 */
  std::operator+((wstring_conflict *)local_158,(wstring_conflict *)local_148);
                    /* try { // try from 00ca9e25 to 00ca9e29 has its CatchHandler @ 00caa962 */
  std::wstring::append((wstring_conflict *)local_78);
  if ((allocator *)(local_158[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_158[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_158[0] + -0x18));
    }
  }
  if ((allocator *)(local_148[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_148[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_148[0] + -0x18));
    }
  }
  if ((allocator *)(local_138[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_138[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_138[0] + -0x18));
    }
  }
  if ((allocator *)(local_118[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_118[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_118[0] + -0x18));
    }
  }
  if ((allocator *)(local_128[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_128[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_128[0] + -0x18));
    }
  }
  if ((*(char *)(*(long *)(in_RSI + 0x90) + 0xb0) != '\0') &&
     (*(int *)(*(long *)(in_RSI + 0x90) + 0x14) != 0)) {
    if ((getDescriptionRequirments(CBaseUnit*)::g_LeftReq == '\0') &&
       (iVar4 = __cxa_guard_acquire(&getDescriptionRequirments(CBaseUnit*)::g_LeftReq), iVar4 != 0))
    {
      getDescriptionRequirments(CBaseUnit*)::g_LeftReq = &DAT_01424558;
      __cxa_guard_release(&getDescriptionRequirments(CBaseUnit*)::g_LeftReq);
      __cxa_atexit(std::wstring::~wstring,&getDescriptionRequirments(CBaseUnit*)::g_LeftReq,
                   &__dso_handle);
    }
    if (*(long *)(getDescriptionRequirments(CBaseUnit*)::g_LeftReq + -6) == 0) {
                    /* try { // try from 00ca9ed2 to 00ca9eeb has its CatchHandler @ 00caab4e */
      CStringTranslate::getSinglton();
      CStringTranslate::getTranslateString((wchar_t *)local_168);
                    /* try { // try from 00ca9ef4 to 00ca9ef8 has its CatchHandler @ 00caaab2 */
      std::wstring::assign((wstring_conflict *)&getDescriptionRequirments(CBaseUnit*)::g_LeftReq);
                    /* try { // try from 00ca9efc to 00ca9f14 has its CatchHandler @ 00caab4e */
      std::wstring::~wstring(local_168);
    }
    getWeaponString(local_198,*(undefined4 *)(*(long *)(in_RSI + 0x90) + 0x14));
                    /* try { // try from 00ca9f24 to 00ca9f28 has its CatchHandler @ 00caaaaa */
    std::operator+((wchar_t *)local_178,(wstring_conflict *)&DAT_00fd0b48);
                    /* try { // try from 00ca9f36 to 00ca9f3a has its CatchHandler @ 00caaaa5 */
    std::wstring::wstring((wstring_conflict *)local_188,(wstring_conflict *)local_178);
    wcslen(L" ");
                    /* try { // try from 00ca9f50 to 00ca9f54 has its CatchHandler @ 00caaa98 */
    std::wstring::append((wchar_t *)local_188,0xfd0b98);
                    /* try { // try from 00ca9f62 to 00ca9f66 has its CatchHandler @ 00caaa93 */
    std::operator+((wstring_conflict *)local_1a8,(wstring_conflict *)local_188);
                    /* try { // try from 00ca9f74 to 00ca9f78 has its CatchHandler @ 00caaa8e */
    std::wstring::wstring((wstring_conflict *)local_1b8,(wstring_conflict *)local_1a8);
    wcslen(L" ");
                    /* try { // try from 00ca9f8e to 00ca9f92 has its CatchHandler @ 00caaa81 */
    std::wstring::append((wchar_t *)local_1b8,0xfd0b98);
                    /* try { // try from 00ca9f9e to 00ca9fa2 has its CatchHandler @ 00caaa7c */
    std::operator+((wstring_conflict *)local_1c8,(wstring_conflict *)local_1b8);
                    /* try { // try from 00ca9fa9 to 00ca9fad has its CatchHandler @ 00caaa14 */
    std::wstring::append((wstring_conflict *)local_78);
    if ((allocator *)(local_1c8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_1c8[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_1c8[0] + -0x18));
      }
    }
    if ((allocator *)(local_1b8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_1b8[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_1b8[0] + -0x18));
      }
    }
    if ((allocator *)(local_1a8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_1a8[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_1a8[0] + -0x18));
      }
    }
    if ((allocator *)(local_188[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_188[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_188[0] + -0x18));
      }
    }
    if ((allocator *)(local_178[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_178[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_178[0] + -0x18));
      }
    }
    if ((allocator *)(local_198[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_198[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_198[0] + -0x18));
      }
    }
  }
LAB_00caa020:
                    /* try { // try from 00caa026 to 00caa02a has its CatchHandler @ 00caab4e */
  std::wstring::wstring((wstring_conflict *)param_1,(wstring_conflict *)local_78);
  if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_78[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
    }
  }
  return param_1;
}



/* address=00caabe0
   symbol=CSkill::getSkillTypeDisplayName */

/* WARNING: Removing unreachable block (ram,0x00caaf99) */
/* WARNING: Removing unreachable block (ram,0x00caafe2) */
/* WARNING: Removing unreachable block (ram,0x00caafa7) */
/* WARNING: Removing unreachable block (ram,0x00caaff0) */
/* CSkill::getSkillTypeDisplayName() */

void CSkill::getSkillTypeDisplayName(void)

{
  int *piVar1;
  int iVar2;
  long in_RSI;
  wstring_conflict *in_RDI;
  long local_58 [2];
  long local_48 [2];
  long local_38 [2];
  long local_28 [2];

  std::wstring::wstring(in_RDI,(wstring_conflict *)&::EMPTY_WSTRING);
  iVar2 = *(int *)(in_RSI + 0x5c);
  if (iVar2 == 1) {
    if ((getSkillTypeDisplayName()::g_OffensiveSpell == '\0') &&
       (iVar2 = __cxa_guard_acquire(&getSkillTypeDisplayName()::g_OffensiveSpell), iVar2 != 0)) {
      getSkillTypeDisplayName()::g_OffensiveSpell = &DAT_01424558;
      __cxa_guard_release(&getSkillTypeDisplayName()::g_OffensiveSpell);
      __cxa_atexit(std::wstring::~wstring,&getSkillTypeDisplayName()::g_OffensiveSpell,&__dso_handle
                  );
    }
    if (*(long *)(getSkillTypeDisplayName()::g_OffensiveSpell + -6) == 0) {
      CStringTranslate::getSinglton();
      CStringTranslate::getTranslateString((wchar_t *)local_38);
                    /* try { // try from 00caad51 to 00caad55 has its CatchHandler @ 00caafb2 */
      std::wstring::assign((wstring_conflict *)&getSkillTypeDisplayName()::g_OffensiveSpell);
      if ((allocator *)(local_38[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_38[0] + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_38[0] + -0x18));
        }
      }
    }
                    /* try { // try from 00caad74 to 00caae79 has its CatchHandler @ 00caafb4 */
    std::wstring::assign(in_RDI);
  }
  else if (iVar2 < 2) {
    if (iVar2 == 0) {
      if ((getSkillTypeDisplayName()::g_ClassSkill == '\0') &&
         (iVar2 = __cxa_guard_acquire(&getSkillTypeDisplayName()::g_ClassSkill), iVar2 != 0)) {
        getSkillTypeDisplayName()::g_ClassSkill = &DAT_01424558;
        __cxa_guard_release(&getSkillTypeDisplayName()::g_ClassSkill);
        __cxa_atexit(std::wstring::~wstring,&getSkillTypeDisplayName()::g_ClassSkill,&__dso_handle);
      }
      if (*(long *)(getSkillTypeDisplayName()::g_ClassSkill + -6) == 0) {
        CStringTranslate::getSinglton();
        CStringTranslate::getTranslateString((wchar_t *)local_28);
                    /* try { // try from 00caae82 to 00caae86 has its CatchHandler @ 00caaf97 */
        std::wstring::assign((wstring_conflict *)&getSkillTypeDisplayName()::g_ClassSkill);
        if ((allocator *)(local_28[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_28[0] + -8);
          iVar2 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar2 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_28[0] + -0x18));
          }
        }
      }
                    /* try { // try from 00caaea5 to 00caaea9 has its CatchHandler @ 00caafb4 */
      std::wstring::assign(in_RDI);
    }
  }
  else if (iVar2 == 2) {
    if ((getSkillTypeDisplayName()::g_DefensiveSpell == '\0') &&
       (iVar2 = __cxa_guard_acquire(&getSkillTypeDisplayName()::g_DefensiveSpell), iVar2 != 0)) {
      getSkillTypeDisplayName()::g_DefensiveSpell = &DAT_01424558;
      __cxa_guard_release(&getSkillTypeDisplayName()::g_DefensiveSpell);
      __cxa_atexit(std::wstring::~wstring,&getSkillTypeDisplayName()::g_DefensiveSpell,&__dso_handle
                  );
    }
    if (*(long *)(getSkillTypeDisplayName()::g_DefensiveSpell + -6) == 0) {
                    /* try { // try from 00caac5b to 00caac74 has its CatchHandler @ 00caafb4 */
      CStringTranslate::getSinglton();
      CStringTranslate::getTranslateString((wchar_t *)local_48);
                    /* try { // try from 00caac7d to 00caac81 has its CatchHandler @ 00caaf61 */
      std::wstring::assign((wstring_conflict *)&getSkillTypeDisplayName()::g_DefensiveSpell);
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
                    /* try { // try from 00caaca0 to 00caacdf has its CatchHandler @ 00caafb4 */
    std::wstring::assign(in_RDI);
  }
  else if (iVar2 == 3) {
    if ((getSkillTypeDisplayName()::g_CharmSpell == '\0') &&
       (iVar2 = __cxa_guard_acquire(&getSkillTypeDisplayName()::g_CharmSpell), iVar2 != 0)) {
      getSkillTypeDisplayName()::g_CharmSpell = &DAT_01424558;
      __cxa_guard_release(&getSkillTypeDisplayName()::g_CharmSpell);
      __cxa_atexit(std::wstring::~wstring,&getSkillTypeDisplayName()::g_CharmSpell,&__dso_handle);
    }
    if (*(long *)(getSkillTypeDisplayName()::g_CharmSpell + -6) == 0) {
      CStringTranslate::getSinglton();
      CStringTranslate::getTranslateString((wchar_t *)local_58);
                    /* try { // try from 00caace8 to 00caacec has its CatchHandler @ 00caaf46 */
      std::wstring::assign((wstring_conflict *)&getSkillTypeDisplayName()::g_CharmSpell);
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
                    /* try { // try from 00caad0a to 00caad48 has its CatchHandler @ 00caafb4 */
    std::wstring::assign(in_RDI);
  }
  return;
}



/* export-summary functions=68 failures=0 */
