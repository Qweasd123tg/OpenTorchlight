/* Targeted Ghidra class export.
   namespace=CEquipment
   Treat pseudocode as navigation evidence. */


/* address=0086d340
   symbol=CEquipment::hasEffects */

/* CEquipment::hasEffects() */

undefined8 __thiscall CEquipment::hasEffects(CEquipment *this)

{
  int iVar1;
  long lVar2;
  uint uVar3;
  long lVar4;

  lVar2 = *(long *)(this + 0x1b8);
  if (lVar2 != 0) {
    if (*(int *)(lVar2 + 0x18) != 0) {
      return 1;
    }
    if (0 < *(int *)(lVar2 + 0x30)) {
      lVar4 = 0;
      uVar3 = 0;
      do {
        if (uVar3 < *(uint *)(lVar2 + 0x34)) {
          iVar1 = *(int *)(*(long *)(lVar4 + *(long *)(lVar2 + 0x28)) + 0x1c);
        }
        else {
          iVar1 = *(int *)(**(long **)(lVar2 + 0x28) + 0x1c);
        }
        if (iVar1 != 0x3e) {
          return 1;
        }
        uVar3 = uVar3 + 1;
        lVar4 = lVar4 + 8;
      } while ((int)uVar3 < *(int *)(lVar2 + 0x30));
    }
  }
  return 0;
}



/* address=0086d3b0
   symbol=CEquipment::getItemName */

/* CEquipment::getItemName() */

CEquipment * __thiscall CEquipment::getItemName(CEquipment *this)

{
  if ((this[0x348] == (CEquipment)0x0) && (*(long *)(*(long *)(this + 0x2d0) + -0x18) != 0)) {
    return this + 0x2d0;
  }
  return this + 0x2d8;
}



/* address=0086d3e0
   symbol=CEquipment::unloadModel */

/* CEquipment::unloadModel() */

void __thiscall CEquipment::unloadModel(CEquipment *this)

{
  if (*(long **)(this + 0x2b0) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x2b0) + 8))();
    *(undefined8 *)(this + 0x2b0) = 0;
  }
  if (*(long **)(this + 0x2b8) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x2b8) + 8))();
    *(undefined8 *)(this + 0x2b8) = 0;
  }
  return;
}



/* address=0086d420
   symbol=CEquipment::minimumDamage */

/* CEquipment::minimumDamage() */

undefined4 __thiscall CEquipment::minimumDamage(CEquipment *this)

{
  return *(undefined4 *)(this + 0x330);
}



/* address=0086d430
   symbol=CEquipment::maximumDamage */

/* CEquipment::maximumDamage() */

undefined4 __thiscall CEquipment::maximumDamage(CEquipment *this)

{
  return *(undefined4 *)(this + 0x334);
}



/* address=0086d440
   symbol=CEquipment::getDamageBonus */

/* CEquipment::getDamageBonus(EDAMAGE_TYPES) */

void __thiscall CEquipment::getDamageBonus(CEquipment *this,int param_2)

{
  uint uVar1;
  long lVar2;
  uint uVar3;
  uint uVar4;
  ulong uVar5;
  long *plVar6;
  ulong uVar7;
  long lVar8;
  long *plVar9;
  long lVar10;

  uVar7 = *(long *)(this + 0x358) - *(long *)(this + 0x350) >> 2;
  if (uVar7 != 0) {
    uVar5 = 0;
    uVar3 = 0;
    do {
      while (*(int *)(*(long *)(this + 0x350) + uVar5 * 4) == param_2) {
        uVar3 = uVar3 + 1;
        uVar5 = (ulong)uVar3;
        if (uVar7 <= uVar5) goto LAB_0086d4a0;
      }
      uVar3 = uVar3 + 1;
      uVar5 = (ulong)uVar3;
    } while (uVar5 < uVar7);
  }
LAB_0086d4a0:
  if (0 < (int)*(uint *)(this + 0x3f0)) {
    lVar10 = 0;
    uVar3 = 0;
    do {
      if (uVar3 < *(uint *)(this + 0x3f4)) {
        plVar6 = (long *)(lVar10 + *(long *)(this + 1000));
      }
      else {
        plVar6 = *(long **)(this + 1000);
      }
      lVar2 = *(long *)(*plVar6 + 0x1b8);
      if ((lVar2 != 0) && (uVar1 = *(uint *)(lVar2 + 0x30), 0 < (int)uVar1)) {
        plVar6 = *(long **)(lVar2 + 0x28);
        lVar8 = 0;
        uVar4 = 0;
LAB_0086d50a:
        do {
          plVar9 = (long *)((long)plVar6 + lVar8);
          if (*(uint *)(lVar2 + 0x34) <= uVar4) {
            plVar9 = plVar6;
          }
          if ((*(int *)(*plVar9 + 0x1c) == 0x34) || (*(int *)(*plVar9 + 0x1c) == 10)) {
            plVar9 = (long *)((long)plVar6 + lVar8);
            if (*(uint *)(lVar2 + 0x34) <= uVar4) {
              plVar9 = plVar6;
            }
            if (param_2 == *(int *)(*plVar9 + 0x14)) {
              uVar4 = uVar4 + 1;
              lVar8 = lVar8 + 8;
              if (uVar4 == uVar1) break;
              goto LAB_0086d50a;
            }
          }
          uVar4 = uVar4 + 1;
          lVar8 = lVar8 + 8;
        } while (uVar4 != uVar1);
      }
      uVar3 = uVar3 + 1;
      lVar10 = lVar10 + 8;
    } while (*(uint *)(this + 0x3f0) != uVar3);
  }
  return;
}



/* address=0086d590
   symbol=CEquipment::removeDamageBonus */

/* CEquipment::removeDamageBonus(EDAMAGE_TYPES, int) */

void CEquipment::removeDamageBonus(void)

{
  return;
}



/* address=0086d5a0
   symbol=CEquipment::canPickup */

/* CEquipment::canPickup(CCharacter*) */

undefined8 CEquipment::canPickup(CCharacter *param_1)

{
  return 1;
}



/* address=0086d5b0
   symbol=CEquipment::canDrop */

/* CEquipment::canDrop(CCharacter*) */

undefined8 CEquipment::canDrop(CCharacter *param_1)

{
  return 1;
}



/* address=0086d5c0
   symbol=CEquipment::incrementStackBy */

/* CEquipment::incrementStackBy(int) */

void __thiscall CEquipment::incrementStackBy(CEquipment *this,int param_1)

{
  int iVar1;

  iVar1 = 0;
  if (-1 < param_1 + *(int *)(this + 0x238)) {
    iVar1 = param_1 + *(int *)(this + 0x238);
  }
  *(int *)(this + 0x238) = iVar1;
  return;
}



/* address=0086d5e0
   symbol=CEquipment::useEquipment */

/* CEquipment::useEquipment(CCharacter*, CCharacter*) */

void CEquipment::useEquipment(CCharacter *param_1,CCharacter *param_2)

{
                    /* WARNING: Could not recover jumptable at 0x0086d5ef. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)param_1 + 0x338))(param_1,0xffffffff);
  return;
}



/* address=0086d600
   symbol=CEquipment::isEffectValidForUnit */

/* CEquipment::isEffectValidForUnit(CCharacter*, CBaseUnit*, CEffect*) */

byte __thiscall
CEquipment::isEffectValidForUnit
          (CEquipment *this,CCharacter *param_1,CBaseUnit *param_2,CEffect *param_3)

{
  if (*(int *)(param_3 + 0x1c) != 0x2e) {
    return 1;
  }
  return (byte)this[0x348] ^ 1;
}



/* address=0086d620
   symbol=CEquipment::missileBeingFired */

/* non-virtual thunk to CEquipment::missileBeingFired(CMissile*) */

void __thiscall CEquipment::missileBeingFired(CEquipment *this,CMissile *param_1)

{
  missileBeingFired((CMissile *)(this + -0x230));
  return;
}



/* address=0086d630
   symbol=CEquipment::missileBeingFired */

/* CEquipment::missileBeingFired(CMissile*) */

void CEquipment::missileBeingFired(CMissile *param_1)

{
  return;
}



/* address=0086d640
   symbol=CEquipment::resetVisualLayout */

/* CEquipment::resetVisualLayout() */

void __thiscall CEquipment::resetVisualLayout(CEquipment *this)

{
  long *plVar1;

  plVar1 = *(long **)(this + 0x428);
  if (plVar1 != (long *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x0086d655. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*plVar1 + 0x50))(plVar1,0);
    return;
  }
  return;
}



/* address=0086d670
   symbol=CEquipment::updateVisualLayout */

/* CEquipment::updateVisualLayout(float) */

void CEquipment::updateVisualLayout(float param_1)

{
  code *pcVar1;
  Vector3 *pVVar2;
  undefined8 uVar3;
  CLayout *pCVar4;
  wstring_conflict *pwVar5;
  ulong in_RSI;
  long in_RDI;
  long *plVar6;
  wstring_conflict local_28 [15];
  allocator local_19 [9];

  if ((*(char *)(in_RDI + 0x430) != '\0') && (*(long *)(in_RDI + 0x2b0) != 0)) {
    plVar6 = *(long **)(in_RDI + 0x428);
    if (plVar6 == (long *)0x0) {
      pCVar4 = Ogre::AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0>>::
               operator_new((AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0>>
                             *)0x1f8,in_RSI);
                    /* try { // try from 0086d758 to 0086d75c has its CatchHandler @ 0086d7cf */
      CLayout::CLayout(pCVar4,*(undefined8 *)(in_RDI + 0x68),2);
      *(CLayout **)(in_RDI + 0x428) = pCVar4;
                    /* try { // try from 0086d776 to 0086d77a has its CatchHandler @ 0086d7f5 */
      std::wstring::wstring(local_28,L"ATTACHEDLAYOUT",local_19);
                    /* try { // try from 0086d78a to 0086d7ae has its CatchHandler @ 0086d7e2 */
      pwVar5 = (wstring_conflict *)
               CDataGroup::GetDataValue(*(CDataGroup **)(in_RDI + 0x1b0),local_28,L"");
      CLayout::loadLayoutFile
                (*(CLayout **)(in_RDI + 0x428),pwVar5,false,(CTimerStatics *)0x0,false,false,0);
                    /* try { // try from 0086d7b2 to 0086d7b6 has its CatchHandler @ 0086d7f5 */
      std::wstring::~wstring(local_28);
      CLayout::start(*(CLayout **)(in_RDI + 0x428));
      plVar6 = *(long **)(in_RDI + 0x428);
    }
    if (*(char *)((long)plVar6 + 0x81) == '\0') {
      (**(code **)(*plVar6 + 0x50))(plVar6,1);
      plVar6 = *(long **)(in_RDI + 0x428);
    }
    (**(code **)(*plVar6 + 0x208))(param_1);
    pVVar2 = (Vector3 *)(**(code **)(**(long **)(*(long *)(in_RDI + 0x2b0) + 0x58) + 0x200))();
    CPositionableObject::setPosition(*(CPositionableObject **)(in_RDI + 0x428),pVVar2);
    pcVar1 = *(code **)(**(long **)(in_RDI + 0x428) + 0x108);
    uVar3 = (**(code **)(**(long **)(*(long *)(in_RDI + 0x2b0) + 0x58) + 0x1f8))();
    (*pcVar1)(*(undefined8 *)(in_RDI + 0x428),uVar3);
  }
  return;
}



/* address=0086d800
   symbol=CEquipment::getDefenseRequirement */

/* CEquipment::getDefenseRequirement(CCharacter*) */

int __thiscall CEquipment::getDefenseRequirement(CEquipment *this,CCharacter *param_1)

{
  char cVar1;
  int iVar2;
  float fVar3;

  iVar2 = 0;
  if (param_1 != (CCharacter *)0x0) {
    fVar3 = (float)CCharacter::getEffectValue(param_1,0x5d,7);
    iVar2 = (int)fVar3;
  }
  cVar1 = CBaseUnit::ISA((CBaseUnit *)this,0xa2);
  if (cVar1 == '\0') {
    cVar1 = CBaseUnit::ISA((CBaseUnit *)this,0xa3);
    if (cVar1 == '\0') {
      cVar1 = CBaseUnit::ISA((CBaseUnit *)this,0xa4);
      if (cVar1 == '\0') {
        cVar1 = CBaseUnit::ISA((CBaseUnit *)this,0xd);
        if (cVar1 == '\0') {
          cVar1 = CBaseUnit::ISA((CBaseUnit *)this,0x81);
          if (cVar1 == '\0') goto LAB_0086d86a;
          if (param_1 == (CCharacter *)0x0) goto LAB_0086d8b0;
          fVar3 = (float)CCharacter::getEffectValue(param_1,0x5f,7);
        }
        else {
          if (param_1 == (CCharacter *)0x0) goto LAB_0086d8b0;
          fVar3 = (float)CCharacter::getEffectValue(param_1,0x5e,7);
        }
      }
      else {
        if (param_1 == (CCharacter *)0x0) goto LAB_0086d8b0;
        fVar3 = (float)CCharacter::getEffectValue(param_1,0x65,7);
      }
    }
    else {
      if (param_1 == (CCharacter *)0x0) goto LAB_0086d8b0;
      fVar3 = (float)CCharacter::getEffectValue(param_1,100,7);
    }
  }
  else if (param_1 == (CCharacter *)0x0) {
LAB_0086d8b0:
    fVar3 = 0.0;
  }
  else {
    fVar3 = (float)CCharacter::getEffectValue(param_1,0x62,7);
  }
  iVar2 = (int)((float)iVar2 + fVar3);
LAB_0086d86a:
  iVar2 = *(int *)(this + 0x288) - iVar2;
  if (iVar2 < 0) {
    iVar2 = 0;
  }
  return iVar2;
}



/* address=0086d970
   symbol=CEquipment::getMagicRequirement */

/* CEquipment::getMagicRequirement(CCharacter*) */

int __thiscall CEquipment::getMagicRequirement(CEquipment *this,CCharacter *param_1)

{
  char cVar1;
  int iVar2;
  float fVar3;

  iVar2 = 0;
  if (param_1 != (CCharacter *)0x0) {
    fVar3 = (float)CCharacter::getEffectValue(param_1,0x5d,7);
    iVar2 = (int)fVar3;
  }
  cVar1 = CBaseUnit::ISA((CBaseUnit *)this,0xa2);
  if (cVar1 == '\0') {
    cVar1 = CBaseUnit::ISA((CBaseUnit *)this,0xa3);
    if (cVar1 == '\0') {
      cVar1 = CBaseUnit::ISA((CBaseUnit *)this,0xa4);
      if (cVar1 == '\0') {
        cVar1 = CBaseUnit::ISA((CBaseUnit *)this,0xd);
        if (cVar1 == '\0') {
          cVar1 = CBaseUnit::ISA((CBaseUnit *)this,0x81);
          if (cVar1 == '\0') goto LAB_0086d9da;
          if (param_1 == (CCharacter *)0x0) goto LAB_0086da20;
          fVar3 = (float)CCharacter::getEffectValue(param_1,0x5f,7);
        }
        else {
          if (param_1 == (CCharacter *)0x0) goto LAB_0086da20;
          fVar3 = (float)CCharacter::getEffectValue(param_1,0x5e,7);
        }
      }
      else {
        if (param_1 == (CCharacter *)0x0) goto LAB_0086da20;
        fVar3 = (float)CCharacter::getEffectValue(param_1,0x65,7);
      }
    }
    else {
      if (param_1 == (CCharacter *)0x0) goto LAB_0086da20;
      fVar3 = (float)CCharacter::getEffectValue(param_1,100,7);
    }
  }
  else if (param_1 == (CCharacter *)0x0) {
LAB_0086da20:
    fVar3 = 0.0;
  }
  else {
    fVar3 = (float)CCharacter::getEffectValue(param_1,0x62,7);
  }
  iVar2 = (int)((float)iVar2 + fVar3);
LAB_0086d9da:
  iVar2 = *(int *)(this + 0x284) - iVar2;
  if (iVar2 < 0) {
    iVar2 = 0;
  }
  return iVar2;
}



/* address=0086dae0
   symbol=CEquipment::getDexterityRequirement */

/* CEquipment::getDexterityRequirement(CCharacter*) */

int __thiscall CEquipment::getDexterityRequirement(CEquipment *this,CCharacter *param_1)

{
  char cVar1;
  int iVar2;
  float fVar3;

  iVar2 = 0;
  if (param_1 != (CCharacter *)0x0) {
    fVar3 = (float)CCharacter::getEffectValue(param_1,0x5d,7);
    iVar2 = (int)fVar3;
  }
  cVar1 = CBaseUnit::ISA((CBaseUnit *)this,0xa2);
  if (cVar1 == '\0') {
    cVar1 = CBaseUnit::ISA((CBaseUnit *)this,0xa3);
    if (cVar1 == '\0') {
      cVar1 = CBaseUnit::ISA((CBaseUnit *)this,0xa4);
      if (cVar1 == '\0') {
        cVar1 = CBaseUnit::ISA((CBaseUnit *)this,0xd);
        if (cVar1 == '\0') {
          cVar1 = CBaseUnit::ISA((CBaseUnit *)this,0x81);
          if (cVar1 == '\0') goto LAB_0086db4a;
          if (param_1 == (CCharacter *)0x0) goto LAB_0086db90;
          fVar3 = (float)CCharacter::getEffectValue(param_1,0x5f,7);
        }
        else {
          if (param_1 == (CCharacter *)0x0) goto LAB_0086db90;
          fVar3 = (float)CCharacter::getEffectValue(param_1,0x5e,7);
        }
      }
      else {
        if (param_1 == (CCharacter *)0x0) goto LAB_0086db90;
        fVar3 = (float)CCharacter::getEffectValue(param_1,0x65,7);
      }
    }
    else {
      if (param_1 == (CCharacter *)0x0) goto LAB_0086db90;
      fVar3 = (float)CCharacter::getEffectValue(param_1,100,7);
    }
  }
  else if (param_1 == (CCharacter *)0x0) {
LAB_0086db90:
    fVar3 = 0.0;
  }
  else {
    fVar3 = (float)CCharacter::getEffectValue(param_1,0x62,7);
  }
  iVar2 = (int)((float)iVar2 + fVar3);
LAB_0086db4a:
  iVar2 = *(int *)(this + 0x280) - iVar2;
  if (iVar2 < 0) {
    iVar2 = 0;
  }
  return iVar2;
}



/* address=0086dc50
   symbol=CEquipment::getStrengthRequirement */

/* CEquipment::getStrengthRequirement(CCharacter*) */

int __thiscall CEquipment::getStrengthRequirement(CEquipment *this,CCharacter *param_1)

{
  char cVar1;
  int iVar2;
  float fVar3;

  iVar2 = 0;
  if (param_1 != (CCharacter *)0x0) {
    fVar3 = (float)CCharacter::getEffectValue(param_1,0x5d,7);
    iVar2 = (int)fVar3;
  }
  cVar1 = CBaseUnit::ISA((CBaseUnit *)this,0xa2);
  if (cVar1 == '\0') {
    cVar1 = CBaseUnit::ISA((CBaseUnit *)this,0xa3);
    if (cVar1 == '\0') {
      cVar1 = CBaseUnit::ISA((CBaseUnit *)this,0xa4);
      if (cVar1 == '\0') {
        cVar1 = CBaseUnit::ISA((CBaseUnit *)this,0xd);
        if (cVar1 == '\0') {
          cVar1 = CBaseUnit::ISA((CBaseUnit *)this,0x81);
          if (cVar1 == '\0') goto LAB_0086dcba;
          if (param_1 == (CCharacter *)0x0) goto LAB_0086dd00;
          fVar3 = (float)CCharacter::getEffectValue(param_1,0x5f,7);
        }
        else {
          if (param_1 == (CCharacter *)0x0) goto LAB_0086dd00;
          fVar3 = (float)CCharacter::getEffectValue(param_1,0x5e,7);
        }
      }
      else {
        if (param_1 == (CCharacter *)0x0) goto LAB_0086dd00;
        fVar3 = (float)CCharacter::getEffectValue(param_1,0x65,7);
      }
    }
    else {
      if (param_1 == (CCharacter *)0x0) goto LAB_0086dd00;
      fVar3 = (float)CCharacter::getEffectValue(param_1,100,7);
    }
  }
  else if (param_1 == (CCharacter *)0x0) {
LAB_0086dd00:
    fVar3 = 0.0;
  }
  else {
    fVar3 = (float)CCharacter::getEffectValue(param_1,0x62,7);
  }
  iVar2 = (int)((float)iVar2 + fVar3);
LAB_0086dcba:
  iVar2 = *(int *)(this + 0x27c) - iVar2;
  if (iVar2 < 0) {
    iVar2 = 0;
  }
  return iVar2;
}



/* address=0086ddc0
   symbol=CEquipment::getLevelRequirement */

/* CEquipment::getLevelRequirement(CCharacter*) */

int __thiscall CEquipment::getLevelRequirement(CEquipment *this,CCharacter *param_1)

{
  char cVar1;
  int iVar2;
  undefined8 uVar3;
  float fVar4;

  if (param_1 == (CCharacter *)0x0) {
    return *(int *)(this + 0x278);
  }
  fVar4 = (float)CCharacter::getEffectValue(param_1,0x5d,7);
  iVar2 = (int)fVar4;
  cVar1 = CBaseUnit::ISA((CBaseUnit *)this,0xa2);
  uVar3 = 0x62;
  if (cVar1 == '\0') {
    cVar1 = CBaseUnit::ISA((CBaseUnit *)this,0xa3,7);
    uVar3 = 100;
    if (cVar1 == '\0') {
      cVar1 = CBaseUnit::ISA((CBaseUnit *)this,0xa4,7);
      uVar3 = 0x65;
      if (cVar1 == '\0') {
        cVar1 = CBaseUnit::ISA((CBaseUnit *)this,0xd,7);
        uVar3 = 0x5e;
        if (cVar1 == '\0') {
          cVar1 = CBaseUnit::ISA((CBaseUnit *)this,0x81,7);
          if (cVar1 == '\0') goto LAB_0086de27;
          uVar3 = 0x5f;
        }
      }
    }
  }
  fVar4 = (float)CCharacter::getEffectValue(param_1,uVar3,7);
  iVar2 = (int)((float)iVar2 + fVar4);
LAB_0086de27:
  iVar2 = *(int *)(this + 0x278) - iVar2;
  if (iVar2 < 0) {
    iVar2 = 0;
  }
  return iVar2;
}



/* address=0086dee0
   symbol=CEquipment::canEnchant */

/* CEquipment::canEnchant() */

undefined8 __thiscall CEquipment::canEnchant(CEquipment *this)

{
  char cVar1;
  undefined8 uVar2;

  cVar1 = CBaseUnit::ISA((CBaseUnit *)this,8);
  if (cVar1 == '\0') {
    cVar1 = CBaseUnit::ISA((CBaseUnit *)this,0xd);
    if (cVar1 == '\0') {
      cVar1 = CBaseUnit::ISA((CBaseUnit *)this,0x11);
      if (cVar1 == '\0') {
        cVar1 = CBaseUnit::ISA((CBaseUnit *)this,0xa0);
        if (cVar1 == '\0') {
          uVar2 = CBaseUnit::ISA((CBaseUnit *)this,0x18);
          return uVar2;
        }
      }
    }
  }
  return 1;
}



/* address=0086df50
   symbol=CEquipment::isMagical */

/* CEquipment::isMagical() */

undefined8 __thiscall CEquipment::isMagical(CEquipment *this)

{
  int iVar1;
  long lVar2;
  char cVar3;
  uint uVar4;
  ulong uVar5;
  long *plVar6;
  long lVar7;

  cVar3 = CBaseUnit::ISA((CBaseUnit *)this,0x37);
  if (cVar3 != '\0') {
    return 1;
  }
  cVar3 = CBaseUnit::ISA((CBaseUnit *)this,0x78);
  if (cVar3 == '\0') {
    uVar5 = *(long *)(this + 0x358) - *(long *)(this + 0x350) >> 2;
    if (uVar5 != 0) {
      uVar4 = 0;
      iVar1 = **(int **)(this + 0x368);
      while( true ) {
        if (iVar1 != 0) {
          return 1;
        }
        uVar4 = uVar4 + 1;
        if (uVar5 <= uVar4) break;
        iVar1 = (*(int **)(this + 0x368))[uVar4];
      }
    }
    lVar2 = *(long *)(this + 0x1b8);
    if (lVar2 != 0) {
      if (*(int *)(lVar2 + 0x18) != 0) {
        return 1;
      }
      if (0 < *(int *)(lVar2 + 0x30)) {
        lVar7 = 0;
        uVar4 = 0;
        do {
          if (uVar4 < *(uint *)(lVar2 + 0x34)) {
            plVar6 = (long *)(lVar7 + *(long *)(lVar2 + 0x28));
          }
          else {
            plVar6 = *(long **)(lVar2 + 0x28);
          }
          if (*(int *)(*plVar6 + 0x1c) != 0x3e) {
            return 1;
          }
          uVar4 = uVar4 + 1;
          lVar7 = lVar7 + 8;
        } while ((int)uVar4 < *(int *)(lVar2 + 0x30));
      }
    }
  }
  return 0;
}



/* address=0086e020
   symbol=CEquipment::removeAffixesThatDontSupportUnitType */

/* CEquipment::removeAffixesThatDontSupportUnitType(UNITTYPES::EUNITTYPES) */

void __thiscall CEquipment::removeAffixesThatDontSupportUnitType(CEquipment *this,uint param_2)

{
  CAffix *this_00;
  char cVar1;
  undefined8 *puVar2;
  long lVar3;
  undefined8 *puVar4;
  uint uVar5;
  long lVar6;
  uint uVar7;
  uint local_54;

  lVar6 = *(long *)(this + 0x1b8);
  if ((lVar6 == 0) || (*(int *)(lVar6 + 0x18) == 0)) {
    return;
  }
  uVar7 = 0;
  local_54 = 0;
  puVar4 = (undefined8 *)0x0;
  uVar5 = 0;
  if (*(int *)(lVar6 + 0x1c) != 0) goto LAB_0086e114;
  do {
    puVar2 = *(undefined8 **)(lVar6 + 0x10);
    while( true ) {
      this_00 = (CAffix *)*puVar2;
                    /* try { // try from 0086e083 to 0086e18e has its CatchHandler @ 0086e1b7 */
      cVar1 = CAffix::canBeAppliedToUnitType(this_00,param_2);
      if (cVar1 == '\0') {
        puVar2 = puVar4;
        if (uVar7 <= local_54) {
          if (puVar4 == (undefined8 *)0x0) {
            puVar2 = operator_new__(8);
            uVar7 = 1;
          }
          else {
            puVar2 = operator_new__((ulong)(uVar7 + 1) << 3);
            if (uVar7 != 0) {
              lVar3 = 0;
              do {
                *(undefined8 *)((long)puVar2 + lVar3) = *(undefined8 *)((long)puVar4 + lVar3);
                lVar3 = lVar3 + 8;
              } while (lVar3 != (ulong)(uVar7 - 1) * 8 + 8);
            }
            operator_delete__(puVar4);
            uVar7 = uVar7 + 1;
          }
        }
        puVar2[local_54] = this_00;
        local_54 = local_54 + 1;
        puVar4 = puVar2;
      }
      uVar5 = uVar5 + 1;
      if (*(uint *)(lVar6 + 0x18) <= uVar5) {
        if (local_54 != 0) {
          lVar6 = 0;
          uVar5 = 0;
          do {
            puVar2 = (undefined8 *)((long)puVar4 + lVar6);
            if (uVar7 <= uVar5) {
              puVar2 = puVar4;
            }
            CEffectManager::deleteAffix(*(CEffectManager **)(this + 0x1b8),(CAffix *)*puVar2);
            uVar5 = uVar5 + 1;
            lVar6 = lVar6 + 8;
          } while (uVar5 < local_54);
        }
        if (puVar4 == (undefined8 *)0x0) {
          return;
        }
        operator_delete__(puVar4);
        return;
      }
      if (*(uint *)(lVar6 + 0x1c) <= uVar5) break;
LAB_0086e114:
      puVar2 = (undefined8 *)((ulong)uVar5 * 8 + *(long *)(lVar6 + 0x10));
    }
  } while( true );
}



/* address=0086e1d0
   symbol=CEquipment::addContainerItem */

/* CEquipment::addContainerItem(CEquipment*) */

void __thiscall CEquipment::addContainerItem(CEquipment *this,CEquipment *param_1)

{
  char cVar1;
  uint uVar2;
  void *pvVar3;
  ulong uVar4;
  uint uVar5;

  uVar5 = *(uint *)(this + 0x3f0);
  if (uVar5 < *(uint *)(this + 0x3e0)) {
    if (uVar5 < *(uint *)(this + 0x3f4)) {
      pvVar3 = *(void **)(this + 1000);
    }
    else if (*(long *)(this + 1000) == 0) {
      *(uint *)(this + 0x3f4) = *(uint *)(this + 0x3f8);
      pvVar3 = operator_new__((ulong)*(uint *)(this + 0x3f8) << 3);
      *(void **)(this + 1000) = pvVar3;
      uVar5 = *(uint *)(this + 0x3f0);
    }
    else {
      uVar5 = *(uint *)(this + 0x3f4) + *(int *)(this + 0x3f8);
      pvVar3 = operator_new__((ulong)uVar5 << 3);
      if (*(int *)(this + 0x3f4) != 0) {
        uVar2 = 0;
        do {
          uVar4 = (ulong)uVar2;
          uVar2 = uVar2 + 1;
          *(undefined8 *)((long)pvVar3 + uVar4 * 8) =
               *(undefined8 *)(*(long *)(this + 1000) + uVar4 * 8);
        } while (uVar2 < *(uint *)(this + 0x3f4));
      }
      if (*(void **)(this + 1000) != (void *)0x0) {
        operator_delete__(*(void **)(this + 1000));
      }
      *(void **)(this + 1000) = pvVar3;
      *(uint *)(this + 0x3f4) = uVar5;
      uVar5 = *(uint *)(this + 0x3f0);
    }
    *(CEquipment **)((long)pvVar3 + (ulong)uVar5 * 8) = param_1;
    *(int *)(this + 0x3f0) = *(int *)(this + 0x3f0) + 1;
    cVar1 = CBaseUnit::ISA((CBaseUnit *)param_1,0x78);
    if (cVar1 != '\0') {
      cVar1 = CBaseUnit::ISA((CBaseUnit *)param_1,0xa0);
      if (cVar1 == '\0') {
        removeAffixesThatDontSupportUnitType(param_1,*(undefined4 *)(this + 0x1ac));
        if (*(CEffectManager **)(param_1 + 0x1b8) != (CEffectManager *)0x0) {
          CEffectManager::calculateEffectValues(*(CEffectManager **)(param_1 + 0x1b8));
          return;
        }
      }
    }
  }
  return;
}



/* address=0086e350
   symbol=CEquipment::missileDieing */

/* non-virtual thunk to CEquipment::missileDieing(CMissile*) */

void __thiscall CEquipment::missileDieing(CEquipment *this,CMissile *param_1)

{
  missileDieing(this + -0x230,param_1);
  return;
}



/* address=0086e360
   symbol=CEquipment::missileDieing */

/* CEquipment::missileDieing(CMissile*) */

void __thiscall CEquipment::missileDieing(CEquipment *this,CMissile *param_1)

{
  TSafePointer *pTVar1;
  long *plVar2;
  long *plVar3;
  uint uVar4;
  uint uVar5;
  ulong uVar6;

  if (*(int *)(this + 0x418) != 0) {
    uVar6 = 0;
    do {
      while( true ) {
        uVar4 = *(uint *)(this + 0x41c);
        uVar5 = (uint)uVar6;
        if (uVar4 <= uVar5) break;
        plVar2 = *(long **)(this + 0x410);
        if (*(long *)plVar2[uVar6] != 0) goto LAB_0086e39b;
LAB_0086e3e1:
        plVar3 = plVar2;
        if (uVar5 < uVar4) {
          plVar3 = plVar2 + uVar6;
        }
        if (*plVar3 != 0) {
          plVar3 = plVar2;
          if (uVar5 < uVar4) {
            plVar3 = plVar2 + uVar6;
          }
          pTVar1 = (TSafePointer *)*plVar3;
          if (pTVar1 != (TSafePointer *)0x0) {
            if (*(CRunicCore **)pTVar1 != (CRunicCore *)0x0) {
                    /* try { // try from 0086e41a to 0086e41e has its CatchHandler @ 0086e49b */
              CRunicCore::removeSafePointer(*(CRunicCore **)pTVar1,pTVar1,*(uint *)(pTVar1 + 8));
            }
            *(undefined8 *)pTVar1 = 0;
            *(undefined4 *)(pTVar1 + 8) = 0xffffffff;
            Ogre::NedAllocImpl::deallocBytes(pTVar1);
            uVar4 = *(uint *)(this + 0x41c);
            plVar2 = *(long **)(this + 0x410);
          }
          if (uVar5 < uVar4) {
            plVar2 = plVar2 + uVar6;
          }
          *plVar2 = 0;
        }
        uVar4 = *(uint *)(this + 0x418);
        if (uVar5 < uVar4) {
          *(uint *)(this + 0x418) = uVar4 - 1;
          *(undefined8 *)(*(long *)(this + 0x410) + uVar6 * 8) =
               *(undefined8 *)(*(long *)(this + 0x410) + (ulong)(uVar4 - 1) * 8);
          uVar4 = *(uint *)(this + 0x418);
        }
        if (uVar4 <= uVar5) {
          return;
        }
      }
      plVar2 = *(long **)(this + 0x410);
      if (*(long *)*plVar2 == 0) goto LAB_0086e3e1;
LAB_0086e39b:
      plVar3 = plVar2;
      if (uVar5 < uVar4) {
        plVar3 = plVar2 + uVar6;
      }
      if (param_1 == *(CMissile **)*plVar3) goto LAB_0086e3e1;
      uVar6 = (ulong)(uVar5 + 1);
    } while (uVar5 + 1 < *(uint *)(this + 0x418));
  }
  return;
}



/* address=0086e4b0
   symbol=CEquipment::getCharacterCanBeHarmedByMissile */

/* non-virtual thunk to CEquipment::getCharacterCanBeHarmedByMissile(CMissile*, CCharacter*) */

void __thiscall
CEquipment::getCharacterCanBeHarmedByMissile(CEquipment *this,CMissile *param_1,CCharacter *param_2)

{
  getCharacterCanBeHarmedByMissile(this + -0x230,param_1,param_2);
  return;
}



/* address=0086e4c0
   symbol=CEquipment::getCharacterCanBeHarmedByMissile */

/* CEquipment::getCharacterCanBeHarmedByMissile(CMissile*, CCharacter*) */

undefined8 __thiscall
CEquipment::getCharacterCanBeHarmedByMissile(CEquipment *this,CMissile *param_1,CCharacter *param_2)

{
  undefined8 uVar1;
  long lVar2;
  CCharacter *this_00;

  uVar1 = 1;
  if (param_1[0x294] == (CMissile)0x0) {
    lVar2 = (**(code **)(*(long *)this + 0x340))();
    uVar1 = 0;
    if (lVar2 != 0) {
      this_00 = (CCharacter *)(**(code **)(*(long *)this + 0x340))(this);
      uVar1 = CCharacter::isEnemy(this_00,param_2);
      return uVar1;
    }
  }
  return uVar1;
}



/* address=0086e530
   symbol=CEquipment::missileApplyingEffects */

/* non-virtual thunk to CEquipment::missileApplyingEffects(CMissile*, CCharacter*, Ogre::Vector3
   const*, float, float) */

void __thiscall
CEquipment::missileApplyingEffects
          (CEquipment *this,CMissile *param_1,CCharacter *param_2,Vector3 *param_3,float param_4,
          float param_5)

{
  missileApplyingEffects
            ((CMissile *)(this + -0x230),(CCharacter *)param_1,(Vector3 *)param_2,param_4,param_5);
  return;
}



/* address=0086e540
   symbol=CEquipment::missileApplyingEffects */

/* CEquipment::missileApplyingEffects(CMissile*, CCharacter*, Ogre::Vector3 const*, float, float) */

undefined8
CEquipment::missileApplyingEffects
          (CMissile *param_1,CCharacter *param_2,Vector3 *param_3,float param_4,float param_5)

{
  char cVar1;
  CCharacter *pCVar2;
  long lVar3;
  undefined8 uVar4;
  undefined8 uVar5;

  pCVar2 = (CCharacter *)0x0;
  if ((((*(long *)(param_2 + 0x220) == 0) ||
       (pCVar2 = (CCharacter *)
                 __dynamic_cast(*(long *)(param_2 + 0x220),&CBaseUnit::typeinfo,
                                &CCharacter::typeinfo,0), pCVar2 == (CCharacter *)0x0)) ||
      (param_3 == (Vector3 *)0x0)) ||
     (cVar1 = CCharacter::isEnemy((CCharacter *)param_3,pCVar2), cVar1 != '\0')) {
    if (param_2[0x294] != (CCharacter)0x0) {
      if (pCVar2 == (CCharacter *)0x0) {
        return 1;
      }
      uVar5 = 0;
      if (*(long *)(param_1 + 0x68) != 0) {
        uVar5 = *(undefined8 *)(*(long *)(param_1 + 0x68) + 0x18);
      }
      CCharacter::rollAttack((CCharacter *)param_4,param_5,pCVar2,uVar5,param_3,param_1,0,7);
      return 1;
    }
    lVar3 = (**(code **)(*(long *)param_1 + 0x340))(param_1);
    if (lVar3 != 0) {
      uVar5 = 0;
      if (*(long *)(param_1 + 0x68) != 0) {
        uVar5 = *(undefined8 *)(*(long *)(param_1 + 0x68) + 0x18);
      }
      uVar4 = (**(code **)(*(long *)param_1 + 0x340))(param_1);
      CCharacter::rollAttack((CCharacter *)param_4,param_5,uVar4,uVar5,param_3,param_1,0,7);
      return 1;
    }
  }
  return 0;
}



/* address=0086e690
   symbol=CEquipment::applyEffectOnUnit */

/* CEquipment::applyEffectOnUnit(CCharacter*, CBaseUnit*, CEffect*) */

undefined8 __thiscall
CEquipment::applyEffectOnUnit
          (CEquipment *this,CCharacter *param_1,CBaseUnit *param_2,CEffect *param_3)

{
  char cVar1;
  undefined8 uVar2;

  cVar1 = (**(code **)(*(long *)this + 0x238))();
  uVar2 = 0;
  if (cVar1 != '\0') {
    if (*(int *)(param_3 + 0x1c) == 0x2e) {
      this[0x348] = (CEquipment)0x1;
      CItem::destroyItemText((CItem *)this);
      uVar2 = 1;
    }
    else {
      CBaseUnit::copyEffect((CBaseUnit *)this,param_2,param_3);
      uVar2 = 0;
    }
  }
  return uVar2;
}



/* address=0086e710
   symbol=CEquipment::canUseOnTarget */

/* CEquipment::canUseOnTarget(CCharacter*, CBaseUnit*) */

bool __thiscall CEquipment::canUseOnTarget(CEquipment *this,CCharacter *param_1,CBaseUnit *param_2)

{
  int iVar1;
  bool bVar2;
  char cVar3;
  int iVar4;
  CCharacter *pCVar5;
  undefined8 *puVar6;
  long lVar7;
  uint uVar8;
  long lVar9;

  if (*(int *)(this + 0x248) != 0) {
    if ((param_2 == (CBaseUnit *)0x0) ||
       (pCVar5 = (CCharacter *)__dynamic_cast(param_2,&CBaseUnit::typeinfo,&CCharacter::typeinfo,0),
       pCVar5 == (CCharacter *)0x0)) {
      pCVar5 = param_1;
    }
    iVar1 = *(int *)(pCVar5 + 0x100);
    iVar4 = getLevelRequirement(this,param_1);
    if (iVar4 <= iVar1) {
      lVar9 = *(long *)(this + 0x1b8);
      if ((lVar9 != 0) && (*(int *)(lVar9 + 0x48) != 0)) {
        uVar8 = 0;
        bVar2 = false;
        do {
          if (uVar8 < *(uint *)(lVar9 + 0x4c)) {
            lVar7 = *(long *)(*(long *)(lVar9 + 0x40) + (ulong)uVar8 * 8);
          }
          else {
            lVar7 = **(long **)(lVar9 + 0x40);
          }
          cVar3 = (**(code **)(*(long *)param_2 + 0x238))
                            (param_2,param_1,*(undefined8 *)(lVar7 + 0x48));
          if (cVar3 != '\0') {
            bVar2 = true;
          }
          uVar8 = uVar8 + 1;
        } while (uVar8 < *(uint *)(lVar9 + 0x48));
        if (!bVar2) {
          return false;
        }
      }
      pCVar5 = (CCharacter *)0x0;
      if (param_2 != (CBaseUnit *)0x0) {
        pCVar5 = (CCharacter *)__dynamic_cast(param_2,&CBaseUnit::typeinfo,&CCharacter::typeinfo,0);
      }
      lVar9 = *(long *)(this + 0x1c8);
      if (lVar9 != 0) {
        if (pCVar5 != (CCharacter *)0x0) {
          cVar3 = CCharacter::performingSkillLoose(pCVar5);
          if (cVar3 != '\0') {
            return false;
          }
          lVar9 = *(long *)(this + 0x1c8);
        }
        if (*(int *)(lVar9 + 0x68) != 0) {
          uVar8 = 0;
          do {
            if (uVar8 < *(uint *)(lVar9 + 0x6c)) {
              puVar6 = (undefined8 *)((ulong)uVar8 * 8 + *(long *)(lVar9 + 0x60));
            }
            else {
              puVar6 = *(undefined8 **)(lVar9 + 0x60);
            }
            cVar3 = CSkill::canAffixesAndEffectsBeAppliedToUnit((CSkill *)*puVar6,param_2,param_1);
            if (cVar3 == '\0') {
              return false;
            }
            uVar8 = uVar8 + 1;
          } while (uVar8 < *(uint *)(lVar9 + 0x68));
        }
      }
      if (pCVar5 == (CCharacter *)0x0) {
        return true;
      }
      cVar3 = CBaseUnit::ISA((CBaseUnit *)this,0x7e);
      if ((cVar3 == '\0') || ((param_2 != (CBaseUnit *)0x0 && (*(long *)(pCVar5 + 0x640) == 0)))) {
        cVar3 = CBaseUnit::ISA((CBaseUnit *)this,0x7d);
        if (cVar3 == '\0') {
          return true;
        }
        if (param_2 != (CBaseUnit *)0x0) {
          return *(long *)(pCVar5 + 0x640) != 0;
        }
      }
    }
  }
  return false;
}



/* address=0086e910
   symbol=CEquipment::useOnTarget */

/* CEquipment::useOnTarget(CCharacter*, CBaseUnit*) */

void __thiscall CEquipment::useOnTarget(CEquipment *this,CCharacter *param_1,CBaseUnit *param_2)

{
  int iVar1;
  long lVar2;
  bool bVar3;
  char cVar4;
  long lVar5;
  undefined8 uVar6;
  uint uVar7;

  if (param_2 == (CBaseUnit *)0x0) {
    return;
  }
  if (((*(int *)(this + 0x238) < 2) && (*(int *)(this + 0x248) < 1)) &&
     (*(int *)(this + 0x248) != -9999)) {
    return;
  }
  lVar2 = *(long *)(this + 0x1b8);
  if (lVar2 != 0) {
    uVar7 = 0;
    bVar3 = false;
    if (*(int *)(lVar2 + 0x48) != 0) {
      do {
        if (uVar7 < *(uint *)(lVar2 + 0x4c)) {
          lVar5 = *(long *)(*(long *)(lVar2 + 0x40) + (ulong)uVar7 * 8);
        }
        else {
          lVar5 = **(long **)(lVar2 + 0x40);
        }
        cVar4 = (**(code **)(*(long *)param_2 + 0x238))
                          (param_2,param_1,*(undefined8 *)(lVar5 + 0x48));
        if (cVar4 != '\0') {
          if (uVar7 < *(uint *)(lVar2 + 0x4c)) {
            cVar4 = (**(code **)(*(long *)param_2 + 0x240))
                              (param_2,param_1,
                               *(undefined8 *)
                                (*(long *)(*(long *)(lVar2 + 0x40) + (ulong)uVar7 * 8) + 0x48));
          }
          else {
            cVar4 = (**(code **)(*(long *)param_2 + 0x240))
                              (param_2,param_1,*(undefined8 *)(**(long **)(lVar2 + 0x40) + 0x48));
          }
          if (cVar4 != '\0') {
            cVar4 = CBaseUnit::ISA((CBaseUnit *)this,0x21);
            if (cVar4 != '\0') {
              CCharacter::incrementJournalStatistic(param_1,0xc,1);
              lVar5 = __dynamic_cast(param_2,&CBaseUnit::typeinfo,&CCharacter::typeinfo);
              if (*(long *)(lVar5 + 0x640) != 0) {
                uVar6 = CSteamStats::getSingleton();
                CSteamStats::incrementStat(uVar6,0x14,1);
                bVar3 = true;
                goto LAB_0086ea10;
              }
            }
            bVar3 = true;
          }
        }
LAB_0086ea10:
        uVar7 = uVar7 + 1;
      } while (uVar7 < *(uint *)(lVar2 + 0x48));
      goto LAB_0086e95c;
    }
  }
  bVar3 = false;
LAB_0086e95c:
  if ((*(long *)(this + 0x1c8) == 0) || (*(int *)(*(long *)(this + 0x1c8) + 0x68) == 0)) {
    if (!bVar3) {
      return;
    }
  }
  else {
    CCharacter::performUnknownSkill((CSkill *)param_1);
  }
  if ((param_1 == (CCharacter *)0x0) || (*(CSoundBank **)(this + 0x1d8) == (CSoundBank *)0x0)) {
    iVar1 = *(int *)(this + 0x238);
  }
  else {
    CSoundBank::playSample
              (*(CSoundBank **)(this + 0x1d8),0x14,*(SceneNode **)(param_1 + 0x58),0.0,0.0,false);
    iVar1 = *(int *)(this + 0x238);
  }
  if (iVar1 < 2) {
    if (*(int *)(this + 0x248) != -9999) {
      *(int *)(this + 0x248) = *(int *)(this + 0x248) + -1;
    }
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x0086eaed. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)this + 0x338))(this,0xffffffff);
  return;
}



/* address=0086eb70
   symbol=CEquipment::playDropSound */

/* CEquipment::playDropSound(Ogre::SceneNode*) */

void __thiscall CEquipment::playDropSound(CEquipment *this,SceneNode *param_1)

{
  if (param_1 == (SceneNode *)0x0) {
    param_1 = *(SceneNode **)(this + 0x58);
  }
  CSoundBank::playSample(*(CSoundBank **)(this + 0x1d8),0x11,param_1,0.0,0.0,false);
  return;
}



/* address=0086eba0
   symbol=CEquipment::playTakeSound */

/* CEquipment::playTakeSound(Ogre::SceneNode*) */

void __thiscall CEquipment::playTakeSound(CEquipment *this,SceneNode *param_1)

{
  if (param_1 == (SceneNode *)0x0) {
    param_1 = *(SceneNode **)(this + 0x58);
  }
  CSoundBank::playSample(*(CSoundBank **)(this + 0x1d8),0x12,param_1,0.0,0.0,false);
  return;
}



/* address=0086ebd0
   symbol=CEquipment::setRenderBehind */

/* CEquipment::setRenderBehind(bool) */

void __thiscall CEquipment::setRenderBehind(CEquipment *this,bool param_1)

{
  CGenericModel *this_00;
  code *UNRECOVERED_JUMPTABLE;
  undefined8 uVar1;
  long *plVar2;

  if (*(CGenericModel **)(this + 0x2b0) != (CGenericModel *)0x0) {
    CGenericModel::setRenderBehind(*(CGenericModel **)(this + 0x2b0),param_1);
    if (param_1) {
      (**(code **)(**(long **)(*(long *)(this + 0x2b0) + 0x60) + 0x140))
                (*(long **)(*(long *)(this + 0x2b0) + 0x60),0x32);
      this_00 = *(CGenericModel **)(this + 0x2b8);
    }
    else {
      (**(code **)(**(long **)(*(long *)(this + 0x2b0) + 0x60) + 0x140))
                (*(long **)(*(long *)(this + 0x2b0) + 0x60),0x58);
      this_00 = *(CGenericModel **)(this + 0x2b8);
    }
    if (this_00 != (CGenericModel *)0x0) {
      CGenericModel::setRenderBehind(this_00,param_1);
      if (param_1) {
        uVar1 = 0x32;
        plVar2 = *(long **)(*(long *)(this + 0x2b8) + 0x60);
        UNRECOVERED_JUMPTABLE = *(code **)(*plVar2 + 0x140);
      }
      else {
        uVar1 = 0x58;
        plVar2 = *(long **)(*(long *)(this + 0x2b8) + 0x60);
        UNRECOVERED_JUMPTABLE = *(code **)(*plVar2 + 0x140);
      }
                    /* WARNING: Could not recover jumptable at 0x0086ec67. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (*UNRECOVERED_JUMPTABLE)(plVar2,uVar1);
      return;
    }
  }
  return;
}



/* address=0086ecd0
   symbol=CEquipment::setHighlighted */

/* CEquipment::setHighlighted(bool) */

void __thiscall CEquipment::setHighlighted(CEquipment *this,bool param_1)

{
  code *UNRECOVERED_JUMPTABLE;
  char cVar1;
  undefined1 uVar2;
  long lVar3;
  long *plVar4;

  cVar1 = (**(code **)(*(long *)this + 0x210))();
  if ((bool)cVar1 != param_1) {
    CItem::setHighlighted((CItem *)this,param_1);
    lVar3 = (**(code **)(*(long *)this + 0x2f0))(this);
    if (lVar3 != 0) {
      plVar4 = (long *)(**(code **)(*(long *)this + 0x2f0))(this);
      UNRECOVERED_JUMPTABLE = *(code **)(*plVar4 + 0x1e0);
      uVar2 = (**(code **)(*(long *)this + 0x210))(this);
                    /* WARNING: Could not recover jumptable at 0x0086ed53. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (*UNRECOVERED_JUMPTABLE)(plVar4,uVar2);
      return;
    }
  }
  return;
}



/* address=0086ed70
   symbol=CEquipment::activateDropParticles */

/* CEquipment::activateDropParticles() */

void __thiscall CEquipment::activateDropParticles(CEquipment *this)

{
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;

  if ((*(CSceneNodeObject **)(this + 0x3d0) != (CSceneNodeObject *)0x0) &&
     (*(long *)(this + 0x2b0) != 0)) {
    CSceneNodeObject::sceneNodeSetParent
              (*(CSceneNodeObject **)(this + 0x3d0),*(SceneNode **)(*(long *)(this + 0x2b0) + 0x58),
               false);
    local_18 = 0;
    local_14 = 0;
    local_10 = 0;
    CPositionableObject::setPosition(*(CPositionableObject **)(this + 0x3d0),(Vector3 *)&local_18);
    CParticle::Start();
  }
  return;
}



/* address=0086ede0
   symbol=CEquipment::setElementalParticlesEnabled */

/* CEquipment::setElementalParticlesEnabled(bool) */

void __thiscall CEquipment::setElementalParticlesEnabled(CEquipment *this,bool param_1)

{
  CParticle *this_00;

  this_00 = *(CParticle **)(this + 0x3c8);
  if (this_00 != (CParticle *)0x0) {
    if (param_1) {
      if (this_00[0x81] == (CParticle)0x0) {
        CParticle::Start();
        return;
      }
    }
    else if (this_00[0x81] != (CParticle)0x0) {
      CParticle::Stop(this_00,true);
      return;
    }
  }
  return;
}



/* address=0086ee20
   symbol=CEquipment::detachFromLocation */

/* CEquipment::detachFromLocation() */

void __thiscall CEquipment::detachFromLocation(CEquipment *this)

{
  MovableObject *pMVar1;
  long lVar2;
  long *plVar3;
  int iVar4;
  CCharacter *pCVar5;

  if (((*(long **)(this + 0x290) != (long *)0x0) && (*(long *)(this + 0x2b0) != 0)) &&
     (*(long *)(*(long *)(this + 0x2b0) + 0x60) != 0)) {
    lVar2 = (**(code **)(**(long **)(this + 0x290) + 0x1e0))();
    if (*(long *)(lVar2 + 0x60) != 0) {
      plVar3 = (long *)Ogre::SceneNode::getParentSceneNode();
      if (plVar3 != (long *)0x0) {
        (**(code **)(*plVar3 + 0x1e0))(plVar3,*(undefined8 *)(*(long *)(this + 0x2b0) + 0x58));
        (**(code **)(**(long **)(this + 0x58) + 0x1a8))
                  (*(long **)(this + 0x58),*(undefined8 *)(*(long *)(this + 0x2b0) + 0x58));
      }
      if (*(CParticle **)(this + 0x3c8) != (CParticle *)0x0) {
        CParticle::Stop(*(CParticle **)(this + 0x3c8),true);
        plVar3 = (long *)Ogre::SceneNode::getParentSceneNode();
        if (plVar3 != (long *)0x0) {
          (**(code **)(*plVar3 + 0x1e0))(plVar3,*(undefined8 *)(*(long *)(this + 0x3c8) + 0x58));
        }
        (**(code **)(**(long **)(this + 0x58) + 0x1a8))
                  (*(long **)(this + 0x58),*(undefined8 *)(*(long *)(this + 0x3c8) + 0x58));
      }
      pCVar5 = *(CCharacter **)(this + 0x290);
      if (*(long *)(pCVar5 + 0x208) != 0) {
        iVar4 = *(int *)(this + 0x298);
        pMVar1 = *(MovableObject **)(*(long *)(pCVar5 + 0x208) + 0x60);
        if ((*(long *)(pCVar5 + (long)iVar4 * 8 + 0x560) != 0) && (pMVar1 != (MovableObject *)0x0))
        {
                    /* try { // try from 0086efb3 to 0086efb7 has its CatchHandler @ 0086efef */
          Ogre::Entity::detachObjectFromBone(pMVar1);
          iVar4 = *(int *)(this + 0x298);
          pCVar5 = *(CCharacter **)(this + 0x290);
        }
        CCharacter::setPaperdollItem(pCVar5,iVar4,0);
      }
      if (*(long *)(this + 0x2b8) != 0) {
        plVar3 = (long *)Ogre::SceneNode::getParentSceneNode();
        (**(code **)(*plVar3 + 0x1e0))(plVar3,*(undefined8 *)(*(long *)(this + 0x2b8) + 0x58));
        pCVar5 = *(CCharacter **)(this + 0x290);
        if (*(long *)(pCVar5 + 0x208) != 0) {
          iVar4 = *(int *)(this + 0x298);
          pMVar1 = *(MovableObject **)(*(long *)(pCVar5 + 0x208) + 0x60);
          if ((*(long *)(pCVar5 + (long)iVar4 * 8 + 0x5c0) != 0) && (pMVar1 != (MovableObject *)0x0)
             ) {
                    /* try { // try from 0086efdb to 0086efdf has its CatchHandler @ 0086effe */
            Ogre::Entity::detachObjectFromBone(pMVar1);
            iVar4 = *(int *)(this + 0x298);
            pCVar5 = *(CCharacter **)(this + 0x290);
          }
          CCharacter::setPaperdollItemSecondary(pCVar5,iVar4,0);
        }
      }
      *(undefined8 *)(this + 0x290) = 0;
    }
  }
  return;
}



/* address=0086f010
   symbol=CEquipment::unequipped */

/* CEquipment::unequipped(CInventory*, CCharacter*, EEQUIP_LOCATIONS) */

void CEquipment::unequipped(CEquipment *param_1)

{
  resetVisualLayout(param_1);
  detachFromLocation(param_1);
  if (param_1[0x1d0] == (CEquipment)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x0086f040. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)param_1 + 0x30))(param_1,0x6d);
  return;
}



/* address=0086f050
   symbol=CEquipment::useEquipment */

/* CEquipment::useEquipment() */

void __thiscall CEquipment::useEquipment(CEquipment *this)

{
  if (*(CInventory **)(this + 0x240) != (CInventory *)0x0) {
    CInventory::useEquipment(*(CInventory **)(this + 0x240),this,(CCharacter *)0x0);
    return;
  }
  return;
}



/* address=0086f080
   symbol=CEquipment::unequip */

/* CEquipment::unequip() */

void __thiscall CEquipment::unequip(CEquipment *this)

{
  if (*(CEquipment **)(this + 0x240) != (CEquipment *)0x0) {
    CInventory::unequipEquipment(*(CEquipment **)(this + 0x240));
    return;
  }
  return;
}



/* address=0086f0a0
   symbol=CEquipment::equip */

/* CEquipment::equip() */

void __thiscall CEquipment::equip(CEquipment *this)

{
  if (*(CInventory **)(this + 0x240) != (CInventory *)0x0) {
    CInventory::equipEquipmentIntoFirstFreeLocation(*(CInventory **)(this + 0x240),this);
    return;
  }
  return;
}



/* address=0086f0c0
   symbol=CEquipment::removedFromInventory */

/* CEquipment::removedFromInventory(CInventory*, CCharacter*) */

void CEquipment::removedFromInventory(CInventory *param_1,CCharacter *param_2)

{
  long lVar1;
  long lVar2;

  lVar1 = *(long *)(param_1 + 0x68);
  lVar2 = 0;
  if (*(int *)(lVar1 + 0x30) != 0) {
    lVar2 = **(long **)(lVar1 + 0x28);
  }
  if (*(long *)(lVar2 + 0x58) != 0) {
    lVar2 = 0;
    if (*(int *)(lVar1 + 0x30) != 0) {
      lVar2 = **(long **)(lVar1 + 0x28);
    }
    CBaseUnit::questEventFire(param_1,5,*(undefined8 *)(lVar2 + 0x58),param_1);
  }
  *(undefined8 *)(param_1 + 0x240) = 0;
  (**(code **)(*(long *)param_1 + 0x18))(param_1,0xffffffffffffffff);
  if (param_1[0x1d0] == (CInventory)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x0086f140. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)param_1 + 0x30))(param_1,0x6b);
  return;
}



/* address=0086f150
   symbol=CEquipment::canEquip */

/* CEquipment::canEquip(CCharacter*, bool) */

bool __thiscall CEquipment::canEquip(CEquipment *this,CCharacter *param_1,bool param_2)

{
  char cVar1;
  bool bVar2;
  CCharacter CVar3;
  int iVar4;
  int iVar5;

  cVar1 = CBaseUnit::ISA((CBaseUnit *)param_1,0x29);
  if ((((cVar1 == '\0') && (cVar1 = CBaseUnit::ISA((CBaseUnit *)param_1,0x80), cVar1 == '\0')) &&
      ((*(CBaseUnit **)(param_1 + 0x640) == (CBaseUnit *)0x0 ||
       ((cVar1 = CBaseUnit::ISA(*(CBaseUnit **)(param_1 + 0x640),0x1c), cVar1 == '\0' ||
        (cVar1 = CBaseUnit::ISA((CBaseUnit *)this,0x27), cVar1 != '\0')))))) &&
     ((CVar3 = param_1[0x4a0], CVar3 == (CCharacter)0x0 || (this[0x348] != (CEquipment)0x0)))) {
    if (param_2) {
      cVar1 = CBaseUnit::ISA((CBaseUnit *)this,8);
      if ((((cVar1 == '\0') && (cVar1 = CBaseUnit::ISA((CBaseUnit *)this,0xd), cVar1 == '\0')) &&
          (cVar1 = CBaseUnit::ISA((CBaseUnit *)this,0x81), cVar1 == '\0')) &&
         (cVar1 = CBaseUnit::ISA((CBaseUnit *)this,0x27), cVar1 == '\0')) goto LAB_0086f17d;
      CVar3 = param_1[0x4a0];
    }
    iVar5 = *(int *)(param_1 + 0x100);
    if (CVar3 != (CCharacter)0x0) {
      iVar4 = getLevelRequirement(this,param_1);
      if ((iVar4 != 0) && (iVar4 = getLevelRequirement(this,param_1), iVar5 < iVar4))
      goto LAB_0086f17d;
      if (param_1[0x4a0] != (CCharacter)0x0) {
        iVar5 = CCharacter::strength(param_1);
        iVar4 = getStrengthRequirement(this,param_1);
        if (iVar5 < iVar4) goto LAB_0086f17d;
        if (param_1[0x4a0] != (CCharacter)0x0) {
          iVar5 = CCharacter::dexterity(param_1);
          iVar4 = getDexterityRequirement(this,param_1);
          if (iVar5 < iVar4) goto LAB_0086f17d;
          if (param_1[0x4a0] != (CCharacter)0x0) {
            iVar5 = CCharacter::magic(param_1);
            iVar4 = getMagicRequirement(this,param_1);
            if (iVar5 < iVar4) goto LAB_0086f17d;
            if (param_1[0x4a0] != (CCharacter)0x0) {
              iVar5 = CCharacter::defense(param_1);
              iVar4 = getDefenseRequirement(this,param_1);
              return iVar4 <= iVar5;
            }
          }
        }
      }
    }
    bVar2 = true;
  }
  else {
LAB_0086f17d:
    bVar2 = false;
  }
  return bVar2;
}



/* address=0086f360
   symbol=CEquipment::DPS */

/* CEquipment::DPS() */

long __thiscall CEquipment::DPS(CEquipment *this)

{
  CEquipment *pCVar1;
  int iVar2;
  long lVar3;
  undefined8 *puVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  float fVar8;
  float fVar9;

  lVar3 = *(long *)(this + 0x2a8);
  if (lVar3 == 0) {
    lVar3 = *(long *)(this + 0x2a0);
  }
  fVar9 = *(float *)(lVar3 + 0x70);
  iVar5 = 0;
  fVar8 = (float)*(int *)(this + 0x334);
  do {
    iVar2 = getDamageBonus(this,iVar5);
    iVar5 = iVar5 + 1;
    fVar8 = fVar8 + (float)iVar2;
  } while (iVar5 != 7);
  if (*(int *)(this + 0x3e0) != 0) {
    uVar7 = 0;
    do {
      if (uVar7 < *(uint *)(this + 0x3f0)) {
        if (uVar7 < *(uint *)(this + 0x3f4)) {
          puVar4 = (undefined8 *)((ulong)uVar7 * 8 + *(long *)(this + 1000));
        }
        else {
          puVar4 = *(undefined8 **)(this + 1000);
        }
        pCVar1 = (CEquipment *)*puVar4;
        if (pCVar1 != (CEquipment *)0x0) {
          uVar6 = 1;
          fVar8 = fVar8 + (float)*(int *)(pCVar1 + 0x334);
          iVar5 = 0;
          do {
            if (iVar5 != 0) {
              iVar2 = getDamageBonus(pCVar1,iVar5);
              fVar8 = fVar8 + (float)iVar2;
              if (6 < uVar6) break;
            }
            iVar5 = iVar5 + 1;
            uVar6 = uVar6 + 1;
          } while( true );
        }
      }
      uVar7 = uVar7 + 1;
    } while (uVar7 < *(uint *)(this + 0x3e0));
  }
  fVar9 = ceilf(fVar8 / (fVar9 * DAT_00fce530));
  return (long)fVar9;
}



/* address=0086f4a0
   symbol=CEquipment::executeProcs */

/* CEquipment::executeProcs(CCharacter*, EEFFECT_TYPE, CBaseUnit*) */

void __thiscall
CEquipment::executeProcs
          (CEquipment *this,CPositionableObject *param_1,int param_3,CPositionableObject *param_4)

{
  char cVar1;
  int iVar2;
  long lVar3;
  undefined8 uVar4;
  undefined8 *puVar5;
  uint uVar6;
  ulong uVar7;
  CPositionableObject *this_00;
  long lVar8;
  long *plVar9;
  int iVar10;
  float fVar11;
  float fVar12;
  undefined8 local_58;
  float local_50;
  undefined8 local_48;
  float local_40;

  cVar1 = CBaseUnit::hasEffect(this,param_3);
  if ((cVar1 != '\0') && (*(long *)(this + 0x1c8) != 0)) {
    iVar10 = 0;
    do {
      lVar8 = (long)iVar10 * 0x18 + *(long *)(this + 0x1b8);
      if (*(int *)(lVar8 + 0x30) != 0) {
        uVar7 = 0;
        plVar9 = (long *)(lVar8 + 0x28);
        do {
          while( true ) {
            uVar6 = (uint)uVar7;
            if (uVar6 < *(uint *)(lVar8 + 0x34)) {
              iVar2 = *(int *)(*(long *)(uVar7 * 8 + *plVar9) + 0x1c);
            }
            else {
              iVar2 = *(int *)(*(long *)*plVar9 + 0x1c);
            }
            if (param_3 == iVar2) break;
LAB_0086f51d:
            uVar7 = (ulong)(uVar6 + 1);
            if (*(uint *)(lVar8 + 0x30) <= uVar6 + 1) goto LAB_0086f678;
          }
          iVar2 = UTILITIES::randomIntegerBetweenVolatile(0,100);
          if (uVar6 < *(uint *)(lVar8 + 0x34)) {
            puVar5 = (undefined8 *)(uVar7 * 8 + *plVar9);
          }
          else {
            puVar5 = (undefined8 *)*plVar9;
          }
          fVar11 = (float)CEffect::value((CEffect *)*puVar5,0);
          fVar12 = (float)iVar2;
          if (fVar11 < fVar12) goto LAB_0086f51d;
          if (uVar6 < *(uint *)(lVar8 + 0x34)) {
            lVar3 = *(long *)(*plVar9 + uVar7 * 8);
            iVar2 = *(int *)(lVar3 + 0x10);
          }
          else {
            lVar3 = *(long *)*plVar9;
            iVar2 = *(int *)(lVar3 + 0x10);
          }
          lVar3 = CSkillManager::getSkill
                            (*(CSkillManager **)(this + 0x1c8),(wstring_conflict *)(lVar3 + 0x80),
                             iVar2);
          if (lVar3 == 0) goto LAB_0086f51d;
          this_00 = param_1;
          if (param_4 != (CPositionableObject *)0x0) {
            this_00 = param_4;
          }
          local_58 = CPositionableObject::getPosition(this_00,true);
          uVar7 = (ulong)(uVar6 + 1);
          local_50 = fVar12;
          uVar4 = (**(code **)(**(long **)(param_1 + 0x58) + 200))();
          local_48 = CPositionableObject::getPosition(param_1,true);
          local_40 = fVar12;
          CSkillManager::executeSkill
                    (*(CSkillManager **)(this + 0x1c8),lVar3,param_1,1,&local_48,uVar4,&local_58,
                     param_4);
        } while (uVar6 + 1 < *(uint *)(lVar8 + 0x30));
      }
LAB_0086f678:
      iVar10 = iVar10 + 1;
    } while (iVar10 != 3);
  }
  return;
}



/* address=0086f6e0
   symbol=CEquipment::destroyIcon */

/* CEquipment::destroyIcon() */

void __thiscall CEquipment::destroyIcon(CEquipment *this)

{
  int iVar1;
  Window *pWVar2;
  undefined8 *puVar3;
  uint uVar4;
  long lVar5;

  if (*(long *)(this + 0x2c8) != 0) {
    pWVar2 = *(Window **)(*(long *)(this + 0x2c8) + 0xb0);
    if (pWVar2 != (Window *)0x0) {
      CEGUI::Window::removeChildWindow(pWVar2);
    }
    CEGUI::WindowManager::destroyWindow(CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton);
    iVar1 = *(int *)(this + 0x3f0);
    *(undefined8 *)(this + 0x2c8) = 0;
    if (0 < iVar1) {
      lVar5 = 0;
      uVar4 = 0;
      do {
        if (uVar4 < *(uint *)(this + 0x3f4)) {
          puVar3 = (undefined8 *)(lVar5 + *(long *)(this + 1000));
        }
        else {
          puVar3 = *(undefined8 **)(this + 1000);
        }
        uVar4 = uVar4 + 1;
        lVar5 = lVar5 + 8;
        destroyIcon((CEquipment *)*puVar3);
      } while ((int)uVar4 < iVar1);
    }
  }
  CItem::destroyItemText((CItem *)this);
  return;
}



/* address=0086f790
   symbol=CEquipment::getAttackSpeedString */

/* CEquipment::getAttackSpeedString(EWeaponSpeed) */

wstring_conflict *
CEquipment::getAttackSpeedString(wstring_conflict *param_1,undefined8 param_2,undefined4 param_3)

{
  int iVar1;
  wstring_conflict awStack_68 [16];
  wstring_conflict local_58 [16];
  wstring_conflict local_48 [16];
  wstring_conflict local_38 [16];
  wstring_conflict local_28 [16];

  std::wstring::wstring(param_1,(wstring_conflict *)&::EMPTY_WSTRING);
  switch(param_3) {
  case 0:
    if ((getAttackSpeedString(EWeaponSpeed)::g_Slowest == '\0') &&
       (iVar1 = __cxa_guard_acquire(&getAttackSpeedString(EWeaponSpeed)::g_Slowest), iVar1 != 0)) {
      getAttackSpeedString(EWeaponSpeed)::g_Slowest = &DAT_01424558;
      __cxa_guard_release(&getAttackSpeedString(EWeaponSpeed)::g_Slowest);
      __cxa_atexit(std::wstring::~wstring,&getAttackSpeedString(EWeaponSpeed)::g_Slowest,
                   &__dso_handle);
    }
    if (*(long *)(getAttackSpeedString(EWeaponSpeed)::g_Slowest + -6) == 0) {
      CStringTranslate::getSinglton();
      CStringTranslate::getTranslateString((wchar_t *)local_28);
                    /* try { // try from 0086f8d5 to 0086f8d9 has its CatchHandler @ 0086fb1d */
      std::wstring::assign((wstring_conflict *)&getAttackSpeedString(EWeaponSpeed)::g_Slowest);
                    /* try { // try from 0086f8dd to 0086f92c has its CatchHandler @ 0086fb32 */
      std::wstring::~wstring(local_28);
    }
    std::wstring::assign(param_1);
    break;
  case 1:
    if ((getAttackSpeedString(EWeaponSpeed)::g_Slow == '\0') &&
       (iVar1 = __cxa_guard_acquire(&getAttackSpeedString(EWeaponSpeed)::g_Slow), iVar1 != 0)) {
      getAttackSpeedString(EWeaponSpeed)::g_Slow = &DAT_01424558;
      __cxa_guard_release(&getAttackSpeedString(EWeaponSpeed)::g_Slow);
      __cxa_atexit(std::wstring::~wstring,&getAttackSpeedString(EWeaponSpeed)::g_Slow,&__dso_handle)
      ;
    }
    if (*(long *)(getAttackSpeedString(EWeaponSpeed)::g_Slow + -6) == 0) {
      CStringTranslate::getSinglton();
      CStringTranslate::getTranslateString((wchar_t *)local_38);
                    /* try { // try from 0086f935 to 0086f939 has its CatchHandler @ 0086fb1b */
      std::wstring::assign((wstring_conflict *)&getAttackSpeedString(EWeaponSpeed)::g_Slow);
                    /* try { // try from 0086f93d to 0086f98c has its CatchHandler @ 0086fb32 */
      std::wstring::~wstring(local_38);
    }
    std::wstring::assign(param_1);
    break;
  case 2:
    if ((getAttackSpeedString(EWeaponSpeed)::g_Average == '\0') &&
       (iVar1 = __cxa_guard_acquire(&getAttackSpeedString(EWeaponSpeed)::g_Average), iVar1 != 0)) {
      getAttackSpeedString(EWeaponSpeed)::g_Average = &DAT_01424558;
      __cxa_guard_release(&getAttackSpeedString(EWeaponSpeed)::g_Average);
      __cxa_atexit(std::wstring::~wstring,&getAttackSpeedString(EWeaponSpeed)::g_Average,
                   &__dso_handle);
    }
    if (*(long *)(getAttackSpeedString(EWeaponSpeed)::g_Average + -6) == 0) {
      CStringTranslate::getSinglton();
      CStringTranslate::getTranslateString((wchar_t *)local_48);
                    /* try { // try from 0086f995 to 0086f999 has its CatchHandler @ 0086fb00 */
      std::wstring::assign((wstring_conflict *)&getAttackSpeedString(EWeaponSpeed)::g_Average);
                    /* try { // try from 0086f99d to 0086f9ae has its CatchHandler @ 0086fb32 */
      std::wstring::~wstring(local_48);
    }
    std::wstring::assign(param_1);
    break;
  case 3:
    if ((getAttackSpeedString(EWeaponSpeed)::g_Fast == '\0') &&
       (iVar1 = __cxa_guard_acquire(&getAttackSpeedString(EWeaponSpeed)::g_Fast), iVar1 != 0)) {
      getAttackSpeedString(EWeaponSpeed)::g_Fast = &DAT_01424558;
      __cxa_guard_release(&getAttackSpeedString(EWeaponSpeed)::g_Fast);
      __cxa_atexit(std::wstring::~wstring,&getAttackSpeedString(EWeaponSpeed)::g_Fast,&__dso_handle)
      ;
    }
    if (*(long *)(getAttackSpeedString(EWeaponSpeed)::g_Fast + -6) == 0) {
                    /* try { // try from 0086f7db to 0086f7f4 has its CatchHandler @ 0086fb32 */
      CStringTranslate::getSinglton();
      CStringTranslate::getTranslateString((wchar_t *)local_58);
                    /* try { // try from 0086f7fd to 0086f801 has its CatchHandler @ 0086fb2f */
      std::wstring::assign((wstring_conflict *)&getAttackSpeedString(EWeaponSpeed)::g_Fast);
                    /* try { // try from 0086f805 to 0086f86f has its CatchHandler @ 0086fb32 */
      std::wstring::~wstring(local_58);
    }
    std::wstring::assign(param_1);
    break;
  case 4:
    if ((getAttackSpeedString(EWeaponSpeed)::g_Fastest == '\0') &&
       (iVar1 = __cxa_guard_acquire(&getAttackSpeedString(EWeaponSpeed)::g_Fastest), iVar1 != 0)) {
      getAttackSpeedString(EWeaponSpeed)::g_Fastest = &DAT_01424558;
      __cxa_guard_release(&getAttackSpeedString(EWeaponSpeed)::g_Fastest);
      __cxa_atexit(std::wstring::~wstring,&getAttackSpeedString(EWeaponSpeed)::g_Fastest,
                   &__dso_handle);
    }
    if (*(long *)(getAttackSpeedString(EWeaponSpeed)::g_Fastest + -6) == 0) {
      CStringTranslate::getSinglton();
      CStringTranslate::getTranslateString((wchar_t *)awStack_68);
                    /* try { // try from 0086f878 to 0086f87c has its CatchHandler @ 0086fb22 */
      std::wstring::assign((wstring_conflict *)&getAttackSpeedString(EWeaponSpeed)::g_Fastest);
                    /* try { // try from 0086f880 to 0086f8cc has its CatchHandler @ 0086fb32 */
      std::wstring::~wstring(awStack_68);
    }
    std::wstring::assign(param_1);
  }
  return param_1;
}



/* address=0086fb40
   symbol=CEquipment::sellPrice */

/* CEquipment::sellPrice() */

int __thiscall CEquipment::sellPrice(CEquipment *this)

{
  long lVar1;
  CCharacter *pCVar2;
  int iVar3;
  CLevel *pCVar4;
  float fVar5;

  if (this[0x348] == (CEquipment)0x0) {
    iVar3 = 1;
    if (0 < *(int *)(this + 0x238)) {
      iVar3 = *(int *)(this + 0x238);
    }
    iVar3 = iVar3 * *(int *)(this + 0x270);
  }
  else {
    iVar3 = 1;
    if (0 < *(int *)(this + 0x238)) {
      iVar3 = *(int *)(this + 0x238);
    }
    iVar3 = iVar3 * *(int *)(this + 0x268);
    if (((*(long *)(this + 0x68) != 0) &&
        (pCVar4 = *(CLevel **)(*(long *)(this + 0x68) + 0x18), pCVar4 != (CLevel *)0x0)) &&
       (lVar1 = CLevel::getPlayer(pCVar4), lVar1 != 0)) {
      pCVar4 = (CLevel *)0x0;
      if (*(long *)(this + 0x68) != 0) {
        pCVar4 = *(CLevel **)(*(long *)(this + 0x68) + 0x18);
      }
      pCVar2 = (CCharacter *)CLevel::getPlayer(pCVar4);
      fVar5 = (float)CCharacter::getEffectValue(pCVar2,0x53,7);
      if (fVar5 / DAT_00fa483c != DAT_00fa47f8) {
        iVar3 = iVar3 + (int)((float)iVar3 * (fVar5 / DAT_00fa483c));
      }
    }
  }
  return iVar3;
}



/* address=0086fc20
   symbol=CEquipment::buyPrice */

/* CEquipment::buyPrice() */

int __thiscall CEquipment::buyPrice(CEquipment *this)

{
  long lVar1;
  CCharacter *pCVar2;
  int iVar3;
  int iVar4;
  CLevel *pCVar5;
  float fVar6;

  if (this[0x348] == (CEquipment)0x0) {
    iVar3 = 1;
    if (0 < *(int *)(this + 0x238)) {
      iVar3 = *(int *)(this + 0x238);
    }
    iVar3 = iVar3 * *(int *)(this + 0x26c);
  }
  else {
    iVar3 = 1;
    if (0 < *(int *)(this + 0x238)) {
      iVar3 = *(int *)(this + 0x238);
    }
    iVar3 = iVar3 * *(int *)(this + 0x264);
    if ((((*(long *)(this + 0x68) != 0) &&
         (pCVar5 = *(CLevel **)(*(long *)(this + 0x68) + 0x18), pCVar5 != (CLevel *)0x0)) &&
        (lVar1 = CLevel::getPlayer(pCVar5), lVar1 != 0)) && (0 < iVar3)) {
      pCVar5 = (CLevel *)0x0;
      if (*(long *)(this + 0x68) != 0) {
        pCVar5 = *(CLevel **)(*(long *)(this + 0x68) + 0x18);
      }
      pCVar2 = (CCharacter *)CLevel::getPlayer(pCVar5);
      fVar6 = (float)CCharacter::getEffectValue(pCVar2,0x53,7);
      if (fVar6 / DAT_00fa483c != DAT_00fa47f8) {
        iVar4 = iVar3 - (int)((float)iVar3 * (fVar6 / DAT_00fa483c));
        iVar3 = 1;
        if (0 < iVar4) {
          iVar3 = iVar4;
        }
      }
    }
  }
  return iVar3;
}



/* address=0086fd10
   symbol=CEquipment::CEquipment */

/* CEquipment::CEquipment(CResourceManager*) */

void __thiscall CEquipment::CEquipment(CEquipment *this,CResourceManager *param_1)

{
  CItem::CItem((CItem *)this,param_1);
  *(undefined ***)this = &PTR__CEquipment_00fd0cf0;
  *(undefined ***)(this + 0x230) = &PTR__CEquipment_00fd1070;
  *(undefined4 *)(this + 0x238) = 1;
  *(undefined4 *)(this + 0x23c) = 1;
  *(undefined8 *)(this + 0x240) = 0;
  *(undefined4 *)(this + 0x248) = 0;
  *(undefined8 *)(this + 0x250) = 0;
  *(undefined4 *)(this + 600) = 0;
  this[0x25c] = (CEquipment)0x0;
  this[0x25d] = (CEquipment)0x0;
  this[0x25e] = (CEquipment)0x1;
  this[0x25f] = (CEquipment)0x0;
  *(undefined4 *)(this + 0x260) = 0;
  *(undefined4 *)(this + 0x274) = 1;
  *(undefined4 *)(this + 0x28c) = 0;
  *(undefined8 *)(this + 0x290) = 0;
  *(undefined8 *)(this + 0x2a0) = 0;
  *(undefined8 *)(this + 0x2a8) = 0;
  *(undefined8 *)(this + 0x2b0) = 0;
  *(undefined8 *)(this + 0x2b8) = 0;
  *(undefined8 *)(this + 0x2c0) = 0;
  *(undefined8 *)(this + 0x2c8) = 0;
                    /* try { // try from 0086fe06 to 0086fe0a has its CatchHandler @ 0086ffdc */
  std::wstring::wstring((wstring_conflict *)(this + 0x2d0),(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 0086fe1a to 0086fe1e has its CatchHandler @ 0087001c */
  std::wstring::wstring((wstring_conflict *)(this + 0x2d8),(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 0086fe2e to 0086fe32 has its CatchHandler @ 00870017 */
  std::wstring::wstring((wstring_conflict *)(this + 0x2e0),(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 0086fe3f to 0086fe43 has its CatchHandler @ 0086fffa */
  std::wstring::wstring((wstring_conflict *)(this + 0x2e8),(wstring_conflict *)&::EMPTY_WSTRING);
  *(undefined4 *)(this + 0x330) = 1;
  *(undefined4 *)(this + 0x334) = 1;
  *(undefined4 *)(this + 0x338) = 0;
  *(undefined4 *)(this + 0x33c) = 0xffffffff;
  *(undefined4 *)(this + 0x340) = 0xffffffff;
  *(undefined4 *)(this + 0x344) = 0;
  this[0x348] = (CEquipment)0x1;
  *(undefined8 *)(this + 0x350) = 0;
  *(undefined8 *)(this + 0x358) = 0;
  *(undefined8 *)(this + 0x360) = 0;
  *(undefined8 *)(this + 0x368) = 0;
  *(undefined8 *)(this + 0x370) = 0;
  *(undefined8 *)(this + 0x378) = 0;
  *(undefined8 *)(this + 0x380) = 0;
  *(undefined8 *)(this + 0x388) = 0;
  *(undefined8 *)(this + 0x390) = 0;
  *(undefined8 *)(this + 0x398) = 0;
  *(undefined8 *)(this + 0x3a0) = 0;
  *(undefined8 *)(this + 0x3a8) = 0;
  *(undefined8 *)(this + 0x3b0) = 0;
  *(undefined8 *)(this + 0x3b8) = 0;
  *(undefined8 *)(this + 0x3c0) = 0;
  *(undefined8 *)(this + 0x3c8) = 0;
  *(undefined8 *)(this + 0x3d0) = 0;
  *(undefined4 **)(this + 0x3d8) = &DAT_01424558;
  *(undefined4 *)(this + 0x3e0) = 0;
  *(undefined8 *)(this + 1000) = 0;
  *(undefined4 *)(this + 0x3f0) = 0;
  *(undefined4 *)(this + 0x3f4) = 0;
  *(undefined4 *)(this + 0x3f8) = 1;
  *(undefined4 **)(this + 0x400) = &DAT_01424558;
  *(undefined4 *)(this + 0x408) = 0;
  *(undefined8 *)(this + 0x410) = 0;
  *(undefined4 *)(this + 0x418) = 0;
  *(undefined4 *)(this + 0x41c) = 0;
  *(undefined4 *)(this + 0x420) = 1;
  *(undefined8 *)(this + 0x428) = 0;
  *(undefined4 *)(this + 0x194) = 0x3ec00000;
  return;
}



/* address=00879e00
   symbol=CEquipment::_GLOBAL__I_CEquipment */

/* CEquipment::CEquipment(CResourceManager*) */

void CEquipment::_GLOBAL__I_CEquipment(void)

{
  allocator aStack_3a6;
  allocator aStack_3a5;
  allocator aStack_3a4;
  allocator aStack_3a3;
  allocator aStack_3a2;
  allocator aStack_3a1;
  allocator aStack_3a0;
  allocator aStack_39f;
  allocator aStack_39e;
  allocator aStack_39d;
  allocator aStack_39c;
  allocator aStack_39b;
  allocator aStack_39a;
  allocator aStack_399;
  allocator aStack_398;
  allocator aStack_397;
  allocator aStack_396;
  allocator aStack_395;
  allocator aStack_394;
  allocator aStack_393;
  allocator aStack_392;
  allocator aStack_391;
  allocator aStack_390;
  allocator aStack_38f;
  allocator aStack_38e;
  allocator aStack_38d;
  allocator aStack_38c;
  allocator aStack_38b;
  allocator aStack_38a;
  allocator aStack_389;
  allocator aStack_388;
  allocator aStack_387;
  allocator aStack_386;
  allocator aStack_385;
  allocator aStack_384;
  allocator aStack_383;
  allocator aStack_382;
  allocator aStack_381;
  allocator aStack_380;
  allocator aStack_37f;
  allocator aStack_37e;
  allocator aStack_37d;
  allocator aStack_37c;
  allocator aStack_37b;
  allocator aStack_37a;
  allocator aStack_379;
  allocator aStack_378;
  allocator aStack_377;
  allocator aStack_376;
  allocator aStack_375;
  allocator aStack_374;
  allocator aStack_373;
  allocator aStack_372;
  allocator aStack_371;
  allocator aStack_370;
  allocator aStack_36f;
  allocator aStack_36e;
  allocator aStack_36d;
  allocator aStack_36c;
  allocator aStack_36b;
  allocator aStack_36a;
  allocator aStack_369;
  allocator aStack_368;
  allocator aStack_367;
  allocator aStack_366;
  allocator aStack_365;
  allocator aStack_364;
  allocator aStack_363;
  allocator aStack_362;
  allocator aStack_361;
  allocator aStack_360;
  allocator aStack_35f;
  allocator aStack_35e;
  allocator aStack_35d;
  allocator aStack_35c;
  allocator aStack_35b;
  allocator aStack_35a;
  allocator aStack_359;
  allocator aStack_358;
  allocator aStack_357;
  allocator aStack_356;
  allocator aStack_355;
  allocator aStack_354;
  allocator aStack_353;
  allocator aStack_352;
  allocator aStack_351;
  allocator aStack_350;
  allocator aStack_34f;
  allocator aStack_34e;
  allocator aStack_34d;
  allocator aStack_34c;
  allocator aStack_34b;
  allocator aStack_34a;
  allocator aStack_349;
  allocator aStack_348;
  allocator aStack_347;
  allocator aStack_346;
  allocator aStack_345;
  allocator aStack_344;
  allocator aStack_343;
  allocator aStack_342;
  allocator aStack_341;
  allocator aStack_340;
  allocator aStack_33f;
  allocator aStack_33e;
  allocator aStack_33d;
  allocator aStack_33c;
  allocator aStack_33b;
  allocator aStack_33a;
  allocator aStack_339;
  allocator aStack_338;
  allocator aStack_337;
  allocator aStack_336;
  allocator aStack_335;
  allocator aStack_334;
  allocator aStack_333;
  allocator aStack_332;
  allocator aStack_331;
  allocator aStack_330;
  allocator aStack_32f;
  allocator aStack_32e;
  allocator aStack_32d;
  allocator aStack_32c;
  allocator aStack_32b;
  allocator aStack_32a;
  allocator aStack_329;
  allocator aStack_328;
  allocator aStack_327;
  allocator aStack_326;
  allocator aStack_325;
  allocator aStack_324;
  allocator aStack_323;
  allocator aStack_322;
  allocator aStack_321;
  allocator aStack_320;
  allocator aStack_31f;
  allocator aStack_31e;
  allocator aStack_31d;
  allocator aStack_31c;
  allocator aStack_31b;
  allocator aStack_31a;
  allocator aStack_319;
  allocator aStack_318;
  allocator aStack_317;
  allocator aStack_316;
  allocator aStack_315;
  allocator aStack_314;
  allocator aStack_313;
  allocator aStack_312;
  allocator aStack_311;
  allocator aStack_310;
  allocator aStack_30f;
  allocator aStack_30e;
  allocator aStack_30d;
  allocator aStack_30c;
  allocator aStack_30b;
  allocator aStack_30a;
  allocator aStack_309;
  allocator aStack_308;
  allocator aStack_307;
  allocator aStack_306;
  allocator aStack_305;
  allocator aStack_304;
  allocator aStack_303;
  allocator aStack_302;
  allocator aStack_301;
  allocator aStack_300;
  allocator aStack_2ff;
  allocator aStack_2fe;
  allocator aStack_2fd;
  allocator aStack_2fc;
  allocator aStack_2fb;
  allocator aStack_2fa;
  allocator aStack_2f9;
  allocator aStack_2f8;
  allocator aStack_2f7;
  allocator aStack_2f6;
  allocator aStack_2f5;
  allocator aStack_2f4;
  allocator aStack_2f3;
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
  allocator aaStack_29 [9];

  ::EMPTY_STRING = &DAT_01423a38;
  __cxa_atexit(std::string::~string,&::EMPTY_STRING,&__dso_handle);
  ::EMPTY_WSTRING = &DAT_01424558;
  __cxa_atexit(std::wstring::~wstring,&::EMPTY_WSTRING,&__dso_handle);
  std::ios_base::Init::Init((Init *)&std::__ioinit);
  __cxa_atexit(std::ios_base::Init::~Init,&std::__ioinit,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gRESOURCE_GROUP_NAMES,L"ITEMS",&aStack_3a6);
  std::wstring::wstring((wstring_conflict *)(::gRESOURCE_GROUP_NAMES + 8),L"MONSTERS",&aStack_3a5);
  std::wstring::wstring((wstring_conflict *)(::gRESOURCE_GROUP_NAMES + 0x10),L"PLAYERS",&aStack_3a4)
  ;
  std::wstring::wstring((wstring_conflict *)(::gRESOURCE_GROUP_NAMES + 0x18),L"PROPS",&aStack_3a3);
  __cxa_atexit(::__tcf_0,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::gRESOURCE_GROUP_FILE_LOCATIONS,L"media/units/items/",&aStack_3a2)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gRESOURCE_GROUP_FILE_LOCATIONS + 8),L"media/units/monsters/",
             &aStack_3a1);
  std::wstring::wstring
            ((wstring_conflict *)(::gRESOURCE_GROUP_FILE_LOCATIONS + 0x10),L"media/units/players/",
             &aStack_3a0);
  std::wstring::wstring
            ((wstring_conflict *)(::gRESOURCE_GROUP_FILE_LOCATIONS + 0x18),L"media/units/props/",
             &aStack_39f);
  __cxa_atexit(::__tcf_1,0,&__dso_handle);
  ParticleUniverse::HALFSCALE._4_4_ = DAT_0142463c * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._0_4_ = Ogre::Vector3::UNIT_SCALE * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._8_4_ = DAT_00fa4810 * DAT_01424640;
  std::string::string((string *)&ParticleUniverse::ALIAS,"1",&aStack_39e);
  __cxa_atexit(std::string::~string,&ParticleUniverse::ALIAS,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::SYSTEM,"2",&aStack_39d);
  __cxa_atexit(std::string::~string,&ParticleUniverse::SYSTEM,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::TECHNIQUE,"3",&aStack_39c);
  __cxa_atexit(std::string::~string,&ParticleUniverse::TECHNIQUE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::RENDERER,"4",&aStack_39b);
  __cxa_atexit(std::string::~string,&ParticleUniverse::RENDERER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EMITTER,"5",&aStack_39a);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EMITTER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::AFFECTOR,"6",&aStack_399);
  __cxa_atexit(std::string::~string,&ParticleUniverse::AFFECTOR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::OBSERVER,"7",&aStack_398);
  __cxa_atexit(std::string::~string,&ParticleUniverse::OBSERVER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::HANDLER,"8",&aStack_397);
  __cxa_atexit(std::string::~string,&ParticleUniverse::HANDLER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::BEHAVIOUR,"9",&aStack_396);
  __cxa_atexit(std::string::~string,&ParticleUniverse::BEHAVIOUR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EXTERN,"10",&aStack_395);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EXTERN,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DYNAMIC_ATTRIBUTE,"11",&aStack_394);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DYNAMIC_ATTRIBUTE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DEPENDENCY,"12",&aStack_393);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DEPENDENCY,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KContextTipNames,L"TIP_INVENTORY",&aStack_392);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 8),L"TIP_UNIDENTIFIED",&aStack_391);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x10),L"TIP_INVENTORYFULL",&aStack_390);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x18),L"TIP_HEALTHLOW",&aStack_38f);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x20),L"TIP_MANALOW",&aStack_38e);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x28),L"TIP_MERCHANT",&aStack_38d)
  ;
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x30),L"TIP_LEVELUP",&aStack_38c);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x38),L"TIP_STATS",&aStack_38b);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x40),L"TIP_SPELL",&aStack_38a);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x48),L"TIP_WELCOME",&aStack_389);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x50),L"TIP_SOCKETABLE",&aStack_388);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x58),L"TIP_PETFLEE",&aStack_387);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x60),L"TIP_GAMBLE",&aStack_386);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x68),L"TIP_ENCHANT",&aStack_385);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x70),L"TIP_TRANSMUTE",&aStack_384);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x78),L"TIP_PETINVENTORY",&aStack_383);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x80),L"TIP_PETINVENTORYFULL",&aStack_382);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x88),L"TIP_STASH",&aStack_381);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x90),L"TIP_FISHING",&aStack_380);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x98),L"TIP_SPELLFIND",&aStack_37f);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xa0),L"TIP_QUESTCOMPLETE",&aStack_37e);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xa8),L"TIP_SHAREDSTASH",&aStack_37d);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xb0),L"TIP_HOWTOATTACK",&aStack_37c);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xb8),L"TIP_TEMP5",&aStack_37b);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xc0),L"TIP_TEMP6",&aStack_37a);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 200),L"TIP_TEMP7",&aStack_379);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xd0),L"TIP_TEMP8",&aStack_378);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xd8),L"TIP_TEMP9",&aStack_377);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xe0),L"TIP_TEMP10",&aStack_376);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xe8),L"TIP_TEMP11",&aStack_375);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xf0),L"TIP_TEMP12",&aStack_374);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xf8),L"TIP_TEMP13",&aStack_373);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x100),L"TIP_TEMP14",&aStack_372);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x108),L"TIP_TEMP15",&aStack_371);
  __cxa_atexit(::__tcf_2,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_TYPE_NAMES,L"",&aStack_370);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 8),L"FIND",&aStack_36f);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x10),L"KILL NUM",&aStack_36e);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x18),L"KILL BOSS",&aStack_36d);
  __cxa_atexit(::__tcf_3,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_DIALOG_TYPE_NAMES,L"ERROR",&aStack_36c);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 8),L"INTRO",&aStack_36b);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x10),L"RETURN",&aStack_36a);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x18),L"COMPLETE",&aStack_369);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x20),L"PASSIVE",&aStack_368);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x28),L"DETAILS",&aStack_367);
  __cxa_atexit(::__tcf_4,0,&__dso_handle);
  std::string::string((string *)::KLayoutFunctionNames,"GUIEXITGAME",&aStack_366);
  std::string::string((string *)(::KLayoutFunctionNames + 8),"GUIEXITAPPLICATION",&aStack_365);
  std::string::string((string *)(::KLayoutFunctionNames + 0x10),"GUINEWGAME",&aStack_364);
  std::string::string((string *)(::KLayoutFunctionNames + 0x18),"GUICONTINUEGAME",&aStack_363);
  std::string::string((string *)(::KLayoutFunctionNames + 0x20),"GUINEWGAMEMENU",&aStack_362);
  std::string::string((string *)(::KLayoutFunctionNames + 0x28),"GUICONTINUEGAMEMENU",&aStack_361);
  std::string::string((string *)(::KLayoutFunctionNames + 0x30),"GUICLOSEMENU",&aStack_360);
  std::string::string((string *)(::KLayoutFunctionNames + 0x38),"GUIBACK",&aStack_35f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x40),"GUIDECLINE",&aStack_35e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x48),"GUIACCEPT",&aStack_35d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x50),"GUIOK",&aStack_35c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x58),"GUIPAUSE",&aStack_35b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x60),"GUISCROLLUP",&aStack_35a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x68),"GUISCROLLDOWN",&aStack_359);
  std::string::string((string *)(::KLayoutFunctionNames + 0x70),"GUISELECT1",&aStack_358);
  std::string::string((string *)(::KLayoutFunctionNames + 0x78),"GUISELECT2",&aStack_357);
  std::string::string((string *)(::KLayoutFunctionNames + 0x80),"GUISELECT3",&aStack_356);
  std::string::string((string *)(::KLayoutFunctionNames + 0x88),"GUISELECT4",&aStack_355);
  std::string::string((string *)(::KLayoutFunctionNames + 0x90),"GUISELECT5",&aStack_354);
  std::string::string((string *)(::KLayoutFunctionNames + 0x98),"GUISELECT6",&aStack_353);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa0),"GUISELECT7",&aStack_352);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa8),"GUISELECT8",&aStack_351);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb0),"GUISELECT9",&aStack_350);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb8),"GUISELECT10",&aStack_34f);
  std::string::string((string *)(::KLayoutFunctionNames + 0xc0),"GUISELECT11",&aStack_34e);
  std::string::string((string *)(::KLayoutFunctionNames + 200),"GUISELECT12",&aStack_34d);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd0),"GUISELECT13",&aStack_34c);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd8),"GUISELECT14",&aStack_34b);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe0),"GUISELECT15",&aStack_34a);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe8),"GUISELECT16",&aStack_349);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf0),"GUISELECT17",&aStack_348);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf8),"GUISELECT18",&aStack_347);
  std::string::string((string *)(::KLayoutFunctionNames + 0x100),"GUISELECT19",&aStack_346);
  std::string::string((string *)(::KLayoutFunctionNames + 0x108),"GUISELECT20",&aStack_345);
  std::string::string((string *)(::KLayoutFunctionNames + 0x110),"GUISELECT21",&aStack_344);
  std::string::string((string *)(::KLayoutFunctionNames + 0x118),"GUISELECT22",&aStack_343);
  std::string::string((string *)(::KLayoutFunctionNames + 0x120),"GUISELECT23",&aStack_342);
  std::string::string((string *)(::KLayoutFunctionNames + 0x128),"GUISELECT24",&aStack_341);
  std::string::string((string *)(::KLayoutFunctionNames + 0x130),"GUISELECT25",&aStack_340);
  std::string::string((string *)(::KLayoutFunctionNames + 0x138),"GUISELECT26",&aStack_33f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x140),"GUISELECT27",&aStack_33e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x148),"GUISELECT28",&aStack_33d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x150),"GUISELECT29",&aStack_33c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x158),"GUISELECT30",&aStack_33b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x160),"GUISELECT31",&aStack_33a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x168),"GUISELECT32",&aStack_339);
  std::string::string((string *)(::KLayoutFunctionNames + 0x170),"GUISELECT33",&aStack_338);
  std::string::string((string *)(::KLayoutFunctionNames + 0x178),"GUISELECT34",&aStack_337);
  std::string::string((string *)(::KLayoutFunctionNames + 0x180),"GUISELECT35",&aStack_336);
  std::string::string((string *)(::KLayoutFunctionNames + 0x188),"GUISELECT36",&aStack_335);
  std::string::string((string *)(::KLayoutFunctionNames + 400),"GUISELECT37",&aStack_334);
  std::string::string((string *)(::KLayoutFunctionNames + 0x198),"GUISELECT38",&aStack_333);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a0),"GUISELECT39",&aStack_332);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a8),"GUISELECT40",&aStack_331);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b0),"GUISELECT41",&aStack_330);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b8),"GUISELECT42",&aStack_32f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c0),"GUISELECT43",&aStack_32e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c8),"GUISELECT44",&aStack_32d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d0),"GUISELECT45",&aStack_32c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d8),"GUISELECT46",&aStack_32b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e0),"GUISELECT47",&aStack_32a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e8),"GUISELECT48",&aStack_329);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f0),"GUISELECT49",&aStack_328);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f8),"GUISELECT50",&aStack_327);
  std::string::string((string *)(::KLayoutFunctionNames + 0x200),"GUISELECTA",&aStack_326);
  std::string::string((string *)(::KLayoutFunctionNames + 0x208),"GUISELECTB",&aStack_325);
  std::string::string((string *)(::KLayoutFunctionNames + 0x210),"GUISELECTC",&aStack_324);
  std::string::string((string *)(::KLayoutFunctionNames + 0x218),"GUISELECTD",&aStack_323);
  std::string::string((string *)(::KLayoutFunctionNames + 0x220),"GUIFEEDPET",&aStack_322);
  std::string::string((string *)(::KLayoutFunctionNames + 0x228),"GUIPETPASSIVE",&aStack_321);
  std::string::string((string *)(::KLayoutFunctionNames + 0x230),"GUIPETAGGRESSIVE",&aStack_320);
  std::string::string((string *)(::KLayoutFunctionNames + 0x238),"GUIPETDEFENSIVE",&aStack_31f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x240),"GUITOGGLEINVENTORY",&aStack_31e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x248),"GUITOGGLEQUESTS",&aStack_31d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x250),"GUITOGGLESTATS",&aStack_31c);
  std::string::string((string *)(::KLayoutFunctionNames + 600),"GUITOGGLESKILLS",&aStack_31b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x260),"GUITOGGLEPERKS",&aStack_31a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x268),"GUITOGGLEJOURNAL",&aStack_319);
  std::string::string((string *)(::KLayoutFunctionNames + 0x270),"GUITOGGLEPET",&aStack_318);
  std::string::string((string *)(::KLayoutFunctionNames + 0x278),"GUITOGGLEAUTOMAP",&aStack_317);
  std::string::string((string *)(::KLayoutFunctionNames + 0x280),"GUITOGGLEOPTIONS",&aStack_316);
  std::string::string((string *)(::KLayoutFunctionNames + 0x288),"GUITOGGLEITEMNAMES",&aStack_315);
  std::string::string((string *)(::KLayoutFunctionNames + 0x290),"GUIAUTOMAPZOOMIN",&aStack_314);
  std::string::string((string *)(::KLayoutFunctionNames + 0x298),"GUIAUTOMAPZOOMOUT",&aStack_313);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a0),"GUILEVELUP",&aStack_312);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a8),"GUISTATSUP",&aStack_311);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b0),"GUISKILLUP",&aStack_310);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b8),"GUIPET1",&aStack_30f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c0),"GUIPET2",&aStack_30e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c8),"GUIPET3",&aStack_30d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d0),"GUIDELETE1",&aStack_30c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d8),"GUIDELETE2",&aStack_30b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e0),"GUIDELETE3",&aStack_30a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e8),"GUIDELETE4",&aStack_309);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f0),"GUISETTINGSMENU",&aStack_308);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f8),"GUIPETSELL",&aStack_307);
  std::string::string((string *)(::KLayoutFunctionNames + 0x300),"NONE",&aStack_306);
  __cxa_atexit(::__tcf_5,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSOUNDBANK_STRINGS,L"STEP_SOUND",&aStack_305);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 8),L"STRIKE_SOUND",&aStack_304);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x10),L"PHYSICALHIT_SOUND",&aStack_303);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x18),L"ICEHIT_SOUND",&aStack_302);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x20),L"FIREHIT_SOUND",&aStack_301);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x28),L"ELECTRICHIT_SOUND",&aStack_300);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x30),L"POISONHIT_SOUND",&aStack_2ff);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x38),L"SHIELDBLOCK",&aStack_2fe);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x40),L"BLOCK",&aStack_2fd);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x48),L"CRITICAL_SOUND",&aStack_2fc);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x50),L"ATTACK_SOUND",&aStack_2fb);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x58),L"IDLE_SOUND",&aStack_2fa)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x60),L"DEATH_SOUND",&aStack_2f9);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x68),L"ROAR_SOUND",&aStack_2f8)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x70),L"FLEE_SOUND",&aStack_2f7)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x78),L"MISS_SOUND",&aStack_2f6)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x80),L"FALL_SOUND",&aStack_2f5)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x88),L"LAND_SOUND",&aStack_2f4)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x90),L"TAKE_SOUND",&aStack_2f3)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x98),L"SPAWN_SOUND",&aStack_2f2);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa0),L"USE_SOUND",&aStack_2f1);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa8),L"EQUIP_SOUND",&aStack_2f0);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb0),L"OPENMENU_SOUND",&aStack_2ef);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb8),L"BUY_SOUND",&aStack_2ee);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xc0),L"ERROR_SOUND",&aStack_2ed);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 200),L"LEVELUP_SOUND",&aStack_2ec);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd0),L"EFFORT_SOUND",&aStack_2eb);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd8),L"SPENDPOINT_SOUND",&aStack_2ea);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe0),L"PORTALENTER_SOUND",&aStack_2e9);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe8),L"POERTALEXIT_SOUND",&aStack_2e8);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf0),L"SKILLASSIGN_SOUND",&aStack_2e7);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf8),L"QUESTRECEIVED_SOUND",&aStack_2e6);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x100),L"QUESTCOMPLETED_SOUND",&aStack_2e5)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x108),L"LOWMANA_SOUND",&aStack_2e4);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x110),L"MISSILEREFLECT_SOUND",&aStack_2e3)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x118),L"BADEFFECT_SOUND",&aStack_2e2);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x120),L"GOODEFFECT_SOUND",&aStack_2e1);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x128),L"NPCDIALOG_SOUND",&aStack_2e0);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x130),L"NPCGREET",&aStack_2df);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x138),L"NPCBYE",&aStack_2de);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x140),L"NPCPURCHASE",&aStack_2dd);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x148),L"NPCSELL",&aStack_2dc);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x150),L"VOICEPETINVENTORYFULL_SOUND",
             &aStack_2db);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x158),L"VOICEPETDEPARTED_SOUND",
             &aStack_2da);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x160),L"VOICEPETRETURNED_SOUND",
             &aStack_2d9);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x168),L"VOICEPETFLED_SOUND",&aStack_2d8);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x170),L"VOICEPETLEVELUP_SOUND",&aStack_2d7
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x178),L"VOICEINVENTORYFULL_SOUND",
             &aStack_2d6);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x180),L"VOICEINSUFFICIENTGOLD_SOUND",
             &aStack_2d5);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x188),L"VOICEIMPOSSIBLE_SOUND",&aStack_2d4
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 400),L"VOICECANTCAST_SOUND",&aStack_2d3);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x198),L"VOICECANTCASTHERE_SOUND",
             &aStack_2d2);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a0),L"VOICEHEALTHLOW_SOUND",&aStack_2d1)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a8),L"VOICEMANALOW_SOUND",&aStack_2d0);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b0),L"VOICETRAPSPRUNG_SOUND",&aStack_2cf
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b8),L"VOICEREFRESHED_SOUND",&aStack_2ce)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c0),L"VOICEPOWERFUL_SOUND",&aStack_2cd);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c8),L"VOICEHEALTHY_SOUND",&aStack_2cc);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d0),L"VOICEILL_SOUND",&aStack_2cb);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d8),L"VOICEPOISONED_SOUND",&aStack_2ca);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e0),L"VOICELEVELUP_SOUND",&aStack_2c9);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e8),L"VOICEFAMEUP_SOUND",&aStack_2c8);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f0),L"VOICESKILLUP_SOUND",&aStack_2c7);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f8),L"VOICEFORTUNEGOOD_SOUND",
             &aStack_2c6);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x200),L"VOICEFORTUNEBAD_SOUND",&aStack_2c5
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x208),L"VOICESPELLLEARNED_SOUND",
             &aStack_2c4);
  ::KSOUNDBANK_STRINGS._528_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_6,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KALIGNMENT_STRINGS,L"NEUTRAL",&aStack_2c3);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 8),L"GOOD",&aStack_2c2);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x10),L"EVIL",&aStack_2c1);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x18),L"ALL",&aStack_2c0);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x20),L"BERSERK",&aStack_2bf);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x28),L"EVILBERSERK",&aStack_2be);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x30),L"GOODBERSERK",&aStack_2bd);
  __cxa_atexit(::__tcf_7,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KAITYPE_STRINGS,L"NORMAL",&aStack_2bc);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 8),L"RANGEDDEFENDER",&aStack_2bb);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x10),L"DEFENDER",&aStack_2ba);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x18),L"RANGEDCASTER",&aStack_2b9);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x20),L"CIRCLER",&aStack_2b8);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x28),L"RESURRECTER",&aStack_2b7);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x30),L"DUMMY",&aStack_2b6);
  __cxa_atexit(::__tcf_8,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gDAMAGE_TYPES,L"Physical",&aStack_2b5);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 8),L"Magical",&aStack_2b4);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x10),L"Fire",&aStack_2b3);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x18),L"Ice",&aStack_2b2);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x20),L"Electric",&aStack_2b1);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x28),L"Poison",&aStack_2b0);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x30),L"All",&aStack_2af);
  __cxa_atexit(::__tcf_9,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::gTARGET_TYPES,L"USER",&aStack_2ae);
  std::wstring::wstring((wstring_conflict *)&DAT_014812a8,L"ITEM",&aStack_2ad);
  __cxa_atexit(::__tcf_10,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSFXTypeName,L"STATIONARYTARGET",&aStack_2ac);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 8),L"STATIONARYOWNER",&aStack_2ab);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x10),L"STATIONARY",&aStack_2aa);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x18),L"STATIONARYPORTAL",&aStack_2a9)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x20),L"BEAM",&aStack_2a8);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x28),L"FOLLOWOWNER",&aStack_2a7);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x30),L"FOLLOWTARGET",&aStack_2a6);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x38),L"PROJECTILELOCATION",&aStack_2a5);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x40),L"PROJECTILECHARACTER",&aStack_2a4);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x48),L"PROJECTILELOCATIONERRATIC",&aStack_2a3);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x50),L"PROJECTILECHARACTERERRATIC",&aStack_2a2);
  __cxa_atexit(::__tcf_11,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KCharacterNames,L"NA",&aStack_2a1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 8),L"NA",&aStack_2a0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x10),L"NA",&aStack_29f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x18),L"NA",&aStack_29e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x20),L"NA",&aStack_29d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x28),L"NA",&aStack_29c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x30),L"NA",&aStack_29b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x38),L"NA",&aStack_29a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x40),L"Bksp",&aStack_299);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x48),L"Tab",&aStack_298);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x50),L"NA",&aStack_297);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x58),L"NA",&aStack_296);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x60),L"Ctr",&aStack_295);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x68),L"Ret",&aStack_294);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x70),L"NA",&aStack_293);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x78),L"NA",&aStack_292);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x80),L"Shift",&aStack_291);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x88),L"Ctrl",&aStack_290);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x90),L"Alt",&aStack_28f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x98),L"Tab",&aStack_28e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa0),L"NA",&aStack_28d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa8),L"NA",&aStack_28c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb0),L"NA",&aStack_28b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb8),L"NA",&aStack_28a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xc0),L"NA",&aStack_289);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 200),L"NA",&aStack_288);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd0),L"NA",&aStack_287);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd8),L"NA",&aStack_286);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe0),L"NA",&aStack_285);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe8),L"NA",&aStack_284);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf0),L"NA",&aStack_283);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf8),L"NA",&aStack_282);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x100),L"space",&aStack_281);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x108),L"pgup",&aStack_280);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x110),L"pgdn",&aStack_27f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x118),L"end",&aStack_27e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x120),L"home",&aStack_27d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x128),L"left arrow",&aStack_27c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x130),L"up arrow",&aStack_27b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x138),L"right arrow",&aStack_27a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x140),L"down arrow",&aStack_279);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x148),L")",&aStack_278);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x150),L"*",&aStack_277);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x158),L"+",&aStack_276);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x160),L",",&aStack_275);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x168),L"ins",&aStack_274);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x170),L"del",&aStack_273);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x178),L"/",&aStack_272);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x180),L"0",&aStack_271);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x188),L"1",&aStack_270);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 400),L"2",&aStack_26f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x198),L"3",&aStack_26e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a0),L"4",&aStack_26d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a8),L"5",&aStack_26c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b0),L"6",&aStack_26b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b8),L"7",&aStack_26a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c0),L"8",&aStack_269);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c8),L"9",&aStack_268);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d0),L":",&aStack_267);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d8),L";",&aStack_266);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e0),L"<",&aStack_265);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e8),L"=",&aStack_264);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f0),L">",&aStack_263);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f8),L"?",&aStack_262);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x200),L"@",&aStack_261);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x208),L"a",&aStack_260);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x210),L"b",&aStack_25f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x218),L"c",&aStack_25e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x220),L"d",&aStack_25d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x228),L"e",&aStack_25c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x230),L"NA",&aStack_25b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x238),L"g",&aStack_25a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x240),L"h",&aStack_259);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x248),L"i",&aStack_258);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x250),L"j",&aStack_257);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 600),L"k",&aStack_256);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x260),L"l",&aStack_255);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x268),L"m",&aStack_254);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x270),L"n",&aStack_253);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x278),L"o",&aStack_252);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x280),L"p",&aStack_251);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x288),L"NA",&aStack_250);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x290),L"r",&aStack_24f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x298),L"s",&aStack_24e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a0),L"t",&aStack_24d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a8),L"u",&aStack_24c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b0),L"v",&aStack_24b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b8),L"w",&aStack_24a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c0),L"x",&aStack_249);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c8),L"y",&aStack_248);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d0),L"z",&aStack_247);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d8),L"[",&aStack_246);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e0),L"\\",&aStack_245);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e8),L"]",&aStack_244);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f0),L"^",&aStack_243);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f8),L"_",&aStack_242);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x300),L"NUM 0",&aStack_241);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x308),L"NUM 1",&aStack_240);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x310),L"NUM 2",&aStack_23f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x318),L"NUM 3",&aStack_23e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 800),L"NUM 4",&aStack_23d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x328),L"NUM 5",&aStack_23c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x330),L"NUM 6",&aStack_23b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x338),L"NUM 7",&aStack_23a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x340),L"NUM 8",&aStack_239);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x348),L"NUM 9",&aStack_238);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x350),L"*",&aStack_237);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x358),L"+",&aStack_236);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x360),L"NA",&aStack_235);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x368),L"-",&aStack_234);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x370),L"NA",&aStack_233);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x378),L"F1",&aStack_232);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x380),L"F2",&aStack_231);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x388),L"F3",&aStack_230);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x390),L"F4",&aStack_22f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x398),L"F5",&aStack_22e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a0),L"F6",&aStack_22d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a8),L"F7",&aStack_22c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b0),L"F8",&aStack_22b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b8),L"F9",&aStack_22a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c0),L"F10",&aStack_229);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c8),L"F11",&aStack_228);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d0),L"F12",&aStack_227);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d8),L"{",&aStack_226);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3e0),L"|",&aStack_225);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 1000),L"}",&aStack_224);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f0),L"~",&aStack_223);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f8),L";",&aStack_222);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x400),L"=",&aStack_221);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x408),L".",&aStack_220);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x410),L"-",&aStack_21f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x418),L",",&aStack_21e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x420),L"/",&aStack_21d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x428),L"`",&aStack_21c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x430),L"[",&aStack_21b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x438),L"\\",&aStack_21a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x440),L"]",&aStack_219);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x448),L"\'",&aStack_218);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x450),L"NA",&aStack_217);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x458),L"NA",&aStack_216);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x460),L"NA",&aStack_215);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x468),L"NA",&aStack_214);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x470),L"NA",&aStack_213);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x478),L"NA",&aStack_212);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x480),L"NA",&aStack_211);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x488),L"NA",&aStack_210);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x490),L"NA",&aStack_20f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x498),L"NA",&aStack_20e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a0),L"NA",&aStack_20d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a8),L"NA",&aStack_20c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b0),L"NA",&aStack_20b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b8),L"NA",&aStack_20a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c0),L"NA",&aStack_209);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c8),L"NA",&aStack_208);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d0),L"NA",&aStack_207);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d8),L"NA",&aStack_206);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e0),L"NA",&aStack_205);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e8),L"NA",&aStack_204);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f0),L"NA",&aStack_203);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f8),L"NA",&aStack_202);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x500),L"NA",&aStack_201);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x508),L"NA",&aStack_200);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x510),L"NA",&aStack_1ff);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x518),L"NA",&aStack_1fe);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x520),L"NA",&aStack_1fd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x528),L"NA",&aStack_1fc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x530),L"NA",&aStack_1fb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x538),L"NA",&aStack_1fa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x540),L"NA",&aStack_1f9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x548),L"NA",&aStack_1f8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x550),L"NA",&aStack_1f7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x558),L"NA",&aStack_1f6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x560),L"NA",&aStack_1f5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x568),L"NA",&aStack_1f4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x570),L"NA",&aStack_1f3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x578),L"NA",&aStack_1f2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x580),L"NA",&aStack_1f1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x588),L"NA",&aStack_1f0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x590),L"NA",&aStack_1ef);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x598),L"NA",&aStack_1ee);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a0),L"NA",&aStack_1ed);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a8),L"NA",&aStack_1ec);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b0),L"NA",&aStack_1eb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b8),L"NA",&aStack_1ea);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c0),L"NA",&aStack_1e9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c8),L"NA",&aStack_1e8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d0),L";",&aStack_1e7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d8),L"=",&aStack_1e6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e0),L",",&aStack_1e5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e8),L"-",&aStack_1e4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f0),L".",&aStack_1e3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f8),L"/",&aStack_1e2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x600),L"`",&aStack_1e1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x608),L"NA",&aStack_1e0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x610),L"NA",&aStack_1df);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x618),L"NA",&aStack_1de);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x620),L"NA",&aStack_1dd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x628),L"NA",&aStack_1dc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x630),L"NA",&aStack_1db);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x638),L"NA",&aStack_1da);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x640),L"NA",&aStack_1d9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x648),L"NA",&aStack_1d8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x650),L"NA",&aStack_1d7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x658),L"NA",&aStack_1d6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x660),L"NA",&aStack_1d5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x668),L"NA",&aStack_1d4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x670),L"NA",&aStack_1d3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x678),L"NA",&aStack_1d2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x680),L"NA",&aStack_1d1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x688),L"NA",&aStack_1d0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x690),L"NA",&aStack_1cf);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x698),L"NA",&aStack_1ce);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a0),L"NA",&aStack_1cd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a8),L"NA",&aStack_1cc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b0),L"NA",&aStack_1cb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b8),L"NA",&aStack_1ca);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c0),L"NA",&aStack_1c9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c8),L"NA",&aStack_1c8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d0),L"NA",&aStack_1c7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d8),L"[",&aStack_1c6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e0),L"\\",&aStack_1c5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e8),L"]",&aStack_1c4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f0),L"\'",&aStack_1c3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f8),L"NA",&aStack_1c2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x700),L"NA",&aStack_1c1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x708),L"NA",&aStack_1c0);
  __cxa_atexit(::__tcf_12,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEffect_Activation_Names,L"PASSIVE",&aStack_1bf);
  std::wstring::wstring((wstring_conflict *)(::gEffect_Activation_Names + 8),L"DYNAMIC",&aStack_1be)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gEffect_Activation_Names + 0x10),L"TRANSFER",&aStack_1bd);
  __cxa_atexit(::__tcf_13,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEFFECT_STAT_MODIFIER_NAMES,L"MELEE",&aStack_1bc);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 8),L"RANGED",&aStack_1bb);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x10),L"DEFENSE",&aStack_1ba);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x18),L"MAGIC",&aStack_1b9);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x20),L"LEVEL",&aStack_1b8);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x28),L"OWNERLEVEL",&aStack_1b7);
  __cxa_atexit(::__tcf_14,0,&__dso_handle);
  std::string::string((string *)::gEFFECT_STAT_MODIFIER_ICON_NAMES,"iconmelee",&aStack_1b6);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 8),"iconranged",&aStack_1b5);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x10),"icondefense",
                      &aStack_1b4);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x18),"iconmagic",&aStack_1b3)
  ;
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x20),"iconmagic",&aStack_1b2)
  ;
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x28),"iconmagic",&aStack_1b1)
  ;
  __cxa_atexit(::__tcf_15,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES,"tag_righthand",&aStack_1b0);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 8),"tag_lefthand",&aStack_1af);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x10),"",&aStack_1ae);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x18),"Bip01 Head",&aStack_1ad);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x20),"",&aStack_1ac);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x28),"Bip01 L Clavicle",&aStack_1ab);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x30),"",&aStack_1aa);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x38),"",&aStack_1a9);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x40),"",&aStack_1a8);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x48),"",&aStack_1a7);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x50),"",&aStack_1a6);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x58),"tag_leftarm",&aStack_1a5);
  __cxa_atexit(::__tcf_16,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES_SECONDARY,"",&aStack_1a4);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 8),"",&aStack_1a3);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x10),"",&aStack_1a2);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x18),"",&aStack_1a1);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x20),"",&aStack_1a0);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x28),"Bip01 R Clavicle",
                      &aStack_19f);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x30),"",&aStack_19e);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x38),"",&aStack_19d);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x40),"",&aStack_19c);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x48),"",&aStack_19b);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x50),"",&aStack_19a);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x58),"",&aStack_199);
  __cxa_atexit(::__tcf_17,0,&__dso_handle);
  std::string::string((string *)::KEquipmentIconName,"EquipLeftHand",&aStack_198);
  std::string::string((string *)(::KEquipmentIconName + 8),"EquipRightHand",&aStack_197);
  std::string::string((string *)(::KEquipmentIconName + 0x10),"EquipGloves",&aStack_196);
  std::string::string((string *)(::KEquipmentIconName + 0x18),"EquipHelm",&aStack_195);
  std::string::string((string *)(::KEquipmentIconName + 0x20),"EquipChest",&aStack_194);
  std::string::string((string *)(::KEquipmentIconName + 0x28),"EquipShoulder",&aStack_193);
  std::string::string((string *)(::KEquipmentIconName + 0x30),"EquipBoots",&aStack_192);
  std::string::string((string *)(::KEquipmentIconName + 0x38),"EquipBelt",&aStack_191);
  std::string::string((string *)(::KEquipmentIconName + 0x40),"EquipRing1",&aStack_190);
  std::string::string((string *)(::KEquipmentIconName + 0x48),"EquipRing2",&aStack_18f);
  std::string::string((string *)(::KEquipmentIconName + 0x50),"EquipAmulet",&aStack_18e);
  std::string::string((string *)(::KEquipmentIconName + 0x58),"",&aStack_18d);
  __cxa_atexit(::__tcf_18,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames,L"CHEST",&aStack_18c);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 8),L"GLOVES",&aStack_18b);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x10),L"BOOTS",&aStack_18a);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x18),L"HELMET",&aStack_189);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x20),L"SHOULDERS",&aStack_188);
  __cxa_atexit(::__tcf_19,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames2,L"",&aStack_187);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 8),L"",&aStack_186);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x10),L"",&aStack_185);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x18),L"FACE",&aStack_184);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x20),L"",&aStack_183);
  __cxa_atexit(::__tcf_20,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)OGRE_UTILITIES::gPRIMITIVE_NAMES,L"SPHERE",&aStack_182);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 8),L"BOX",&aStack_181);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x10),L"PLANE",&aStack_180);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x18),L"CYLINDER",&aStack_17f);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x20),L"CONE",&aStack_17e);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x28),L"ARROW",&aStack_17d);
  __cxa_atexit(::__tcf_21,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEDITOR_EVENT_NAMES,L"STOP",&aStack_17c);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 8),L"PLAY",&aStack_17b);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x10),L"RELOAD TILES",&aStack_17a);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x18),L"TOGGLE LIGHTING",&aStack_179);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x20),L"SELECT COLLIDABLE",&aStack_178);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x28),L"PAUSE PARTICLES",&aStack_177);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x30),L"UNPAUSE PARTICLES",&aStack_176);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x38),L"COLLISION ALL",&aStack_175);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x40),L"COLLISION MODELS",&aStack_174);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x48),L"COLLISION PREFABS",&aStack_173);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x50),L"COLLISION ROOMPIECES",&aStack_172)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x58),L"COLLISION ROOMPROPS",&aStack_171);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x60),L"RELOAD GRAPHS",&aStack_170);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x68),L"TOGGLE PLAYER LIGHT",&aStack_16f);
  __cxa_atexit(::__tcf_22,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEDITOR_FLAG_NAMES,L"LOGIC ENABLED",&aStack_16e);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 8),L"INGAME MODE",&aStack_16d);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x10),L"SHOW STATS",&aStack_16c)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x18),L"EDIT POSITION",&aStack_16b);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x20),L"EDIT SCALE",&aStack_16a)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x28),L"EDIT ORIENTATION",&aStack_169);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x30),L"EDIT NONE",&aStack_168);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x38),L"SHOW HELPERS",&aStack_167);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x40),L"SHOW GRID",&aStack_166);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x48),L"SHOW WORKING PLANE",&aStack_165);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x50),L"SNAP TO GRID",&aStack_164);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x58),L"SUSPEND EDITOR",&aStack_163);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x60),L"LIGHTING VISIBLE",&aStack_162);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x68),L"RECALCULATE LIGHTING",&aStack_161);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x70),L"SHOW EDGES",&aStack_160)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x78),L"UPDATE PARTICLES CIRCLE",
             &aStack_15f);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x80),L"SHOW LOGIC OUTPUT",&aStack_15e);
  __cxa_atexit(::__tcf_23,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::gEDITOR_UPDATE_MASKS,L"OBJECT SELECTION CHANGED",&aStack_15d);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 8),L"OBJECT DATA CHANGED",&aStack_15c);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 0x10),L"OBJECTS CREATED",&aStack_15b);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 0x18),L"REFRESH TREE VIEW",&aStack_15a);
  __cxa_atexit(::__tcf_24,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::m_gFileVersionExtension,L".svt",&aStack_159);
  __cxa_atexit(std::wstring::~wstring,&::m_gFileVersionExtension,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gKEYFRAME_TYPES,L"HIT",&aStack_158);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 8),L"BLENDIN",&aStack_157);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x10),L"BLENDOUT",&aStack_156);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x18),L"PLAYSOUND",&aStack_155);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x20),L"SPAWNPARTICLE",&aStack_154)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x28),L"SPAWNPARTICLE_STOP_ON_DEATH",
             &aStack_153);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x30),L"FOOTSTEP",&aStack_152);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x38),L"SHOWWEAPONTRAIL",&aStack_151);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x40),L"HIDEWEAPONTRAIL",&aStack_150);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x48),L"ATTACKSOUND",&aStack_14f);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x50),L"ENABLECOLLISION",&aStack_14e);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x58),L"DISABLECOLLISION",&aStack_14d);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x60),L"REMOVEPARTICLES",&aStack_14c);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x68),L"REMOVEANIMATIONPARTICLES",&aStack_14b)
  ;
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x70),L"CAMERASHAKE",&aStack_14a);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x78),L"ATTACKEND",&aStack_149);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x80),L"UNTARGETABLE",&aStack_148);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x88),L"TARGETABLE",&aStack_147);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x90),L"DAMPVELOCITY",&aStack_146);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x98),L"UNDAMPVELOCITY",&aStack_145);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xa0),L"SHOWWEAPONS",&aStack_144);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xa8),L"HIDEWEAPONS",&aStack_143);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xb0),L"HIDEMESH",&aStack_142);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xb8),L"SHOWMESH",&aStack_141);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xc0),L"FADEOUTMESH",&aStack_140);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 200),L"FADEINMESH",&aStack_13f);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0xd0),L"CAMERASHAKE_NO_FALLOFF",&aStack_13e);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0xd8),L"PLAYSOUND_NO_FALLOFF",&aStack_13d);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xe0),L"HITTWO",&aStack_13c);
  __cxa_atexit(::__tcf_25,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::g_LEVELLAYOUT_CREATION_NAMES,L"MONSTERSPAWNCLASS",&aStack_13b);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 8),L"CHAMPIONSPAWNCLASS",
             &aStack_13a);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x10),L"PROPSPAWNCLASS",
             &aStack_139);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x18),L"NPCSPAWNCLASS",
             &aStack_138);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x20),L"CREEPSPAWNCLASS",
             &aStack_137);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x28),L"GOLD",&aStack_136);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x30),L"FISHSPAWNCLASS",
             &aStack_135);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x38),L"FORMATIONS",&aStack_134);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x40),L"QUESTMONSTERSPAWNCLASS",
             &aStack_133);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x48),L"QUESTITEMSPAWNCLASS",
             &aStack_132);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x50),L"QUESTCHAMPIONSPAWNCLASS",
             &aStack_131);
  __cxa_atexit(::__tcf_26,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES,
             L"MONSTERSPAWNCLASSRANDOMIZED",&aStack_130);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 8),
             L"CHAMPIONSPAWNCLASSRANDOMIZED",&aStack_12f);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x10),
             L"PROPSPAWNCLASSRANDOMIZED",&aStack_12e);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x18),
             L"NPCSPAWNCLASSRANDOMIZED",&aStack_12d);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x20),
             L"CREEPSPAWNCLASSRANDOMIZED",&aStack_12c);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x28),
             L"GOLDRANDOMIZED",&aStack_12b);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x30),
             L"FISHSPAWNCLASSRANDOMIZED",&aStack_12a);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x38),
             L"FORMATIONSRANDOMIZED",&aStack_129);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x40),
             L"QUESTMONSTERSPAWNCLASSRANDOMIZED",&aStack_128);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x48),
             L"QUESTITEMSPAWNCLASSRANDOMIZED",&aStack_127);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x50),
             L"QUESTCHAMPIONSPAWNCLASSRANDOMIZED",&aStack_126);
  __cxa_atexit(::__tcf_27,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::g_LEVELLAYOUT_CREATION_PATHNODES,L"MONSTERS_PER_METER_MIN",
             &aStack_125);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 8),L"MONSTERS_PER_METER_MAX",
             &aStack_124);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x10),
             L"CHAMPIONS_PER_METER_MIN",&aStack_123);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x18),
             L"CHAMPIONS_PER_METER_MAX",&aStack_122);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x20),L"PROPS_PER_METER_MIN",
             &aStack_121);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x28),L"PROPS_PER_METER_MAX",
             &aStack_120);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x30),L"NPCS_PER_METER_MIN",
             &aStack_11f);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x38),L"NPCS_PER_METER_MAX",
             &aStack_11e);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x40),L"CREEPS_PER_METER_MIN"
             ,&aStack_11d);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x48),L"CREEPS_PER_METER_MAX"
             ,&aStack_11c);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x50),L"GOLD_PER_METER_MIN",
             &aStack_11b);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x58),L"GOLD_PER_METER_MAX",
             &aStack_11a);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x60),L"FISH_PER_METER_MIN",
             &aStack_119);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x68),L"FISH_PER_METER_MAX",
             &aStack_118);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x70),
             L"FORMATIONS_PER_METER_MIN",&aStack_117);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x78),
             L"FORMATIONS_PER_METER_MAX",&aStack_116);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x80),L"",&aStack_115);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x88),L"",&aStack_114);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x90),L"",&aStack_113);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x98),L"",&aStack_112);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0xa0),L"",&aStack_111);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0xa8),L"",&aStack_110);
  __cxa_atexit(::__tcf_28,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::g_LEVELLAYOUT_CREATION_COUNTS,L"MONSTER_MIN",&aStack_10f);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 8),L"MONSTER_MAX",&aStack_10e);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x10),L"CHAMPIONS_MIN",
             &aStack_10d);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x18),L"CHAMPIONS_MAX",
             &aStack_10c);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x20),L"PROPS_MIN",&aStack_10b);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x28),L"PPROPS_MAX",&aStack_10a)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x30),L"NPCS_MIN",&aStack_109);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x38),L"NPCS_MAX",&aStack_108);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x40),L"CREEPS_MIN",&aStack_107)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x48),L"CREEPS_MAX",&aStack_106)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x50),L"GOLD_MIN",&aStack_105);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x58),L"GOLD_MAX",&aStack_104);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x60),L"FISH_MIN",&aStack_103);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x68),L"FISH_MAX",&aStack_102);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x70),L"",&aStack_101);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x78),L"",&aStack_100);
  std::wstring::wstring((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x80),L"",&aStack_ff)
  ;
  std::wstring::wstring((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x88),L"",&aStack_fe)
  ;
  std::wstring::wstring((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x90),L"",&aStack_fd)
  ;
  std::wstring::wstring((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x98),L"",&aStack_fc)
  ;
  std::wstring::wstring((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0xa0),L"",&aStack_fb)
  ;
  std::wstring::wstring((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0xa8),L"",&aStack_fa)
  ;
  __cxa_atexit(::__tcf_29,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_EVENT_TYPE_NAMES,L"EVENT_START",&aStack_f9);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 8),L"EVENT_END",&aStack_f8)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x10),L"EVENT_TRIGGER",&aStack_f7);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x18),L"EVENT_TRIGGER_TWO",&aStack_f6)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x20),L"EVENT_UNITHIT",&aStack_f5);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x28),L"EVENT_UNITDIE",&aStack_f4);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x30),L"EVENT_MISSILEHIT",&aStack_f3);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x38),L"EVENT_MISSILEDIE",&aStack_f2);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x40),L"EVENT_DIEBYEFFECT",&aStack_f1)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x48),L"EVENT_CASTERDIE",&aStack_f0);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x50),L"EVENT_UNIT_CREATE",&aStack_ef)
  ;
  __cxa_atexit(::__tcf_30,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_TARGET_TYPE_NAMES,L"NONE",&aStack_ee);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 8),L"POSITION",&aStack_ed)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x10),L"TARGET",&aStack_ec);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x18),L"SELF",&aStack_eb);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x20),L"EVERYBODY",&aStack_ea);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x28),L"POSITIONRANDOM",&aStack_e9);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x30),L"POSITIONFLEE",&aStack_e8);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x38),L"ITEM",&aStack_e7);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x40),L"UNIDENTIFIEDITEM",&aStack_e6)
  ;
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x48),L"PETS",&aStack_e5);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x50),L"SELFANDPETS",&aStack_e4);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x58),L"TARGET_POS",&aStack_e3);
  __cxa_atexit(::__tcf_31,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_ACTIVATION_TYPE_NAMES,L"ANY",&aStack_e2);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 8),L"PROC",&aStack_e1)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 0x10),L"WEAPON",&aStack_e0);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 0x18),L"NORMAL",&aStack_df);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 0x20),L"PASSIVE",&aStack_de);
  __cxa_atexit(::__tcf_32,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_TYPE_NAMES,L"SKILL",&aStack_dd);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TYPE_NAMES + 8),L"OFFENSIVE",&aStack_dc);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TYPE_NAMES + 0x10),L"DEFENSIVE",&aStack_db);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TYPE_NAMES + 0x18),L"CHARM",&aStack_da);
  ::gSKILL_TYPE_NAMES._32_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_33,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_TYPE_DISPLAY_NAMES,L"Class Skill",&aStack_d9);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TYPE_DISPLAY_NAMES + 8),L"Offensive Spell",&aStack_d8);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TYPE_DISPLAY_NAMES + 0x10),L"Defensive Spell",&aStack_d7)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TYPE_DISPLAY_NAMES + 0x18),L"Charm Spell",&aStack_d6);
  ::gSKILL_TYPE_DISPLAY_NAMES._32_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_34,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_BONE_ATTACHMENT_NAMES,L"",&aStack_d5);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 8),L"CENTER",&aStack_d4);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x10),L"HEAD",&aStack_d3);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x18),L"RIGHTHAND",&aStack_d2);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x20),L"LEFTHAND",&aStack_d1);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x28),L"RIGHTSHOULDER",&aStack_d0
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x30),L"LEFTSHOULDER",&aStack_cf)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x38),L"POSITION",&aStack_ce);
  __cxa_atexit(::__tcf_35,0,&__dso_handle);
  std::string::string((string *)gMISSILE_PARTICLE_NAMES,"Release",&aStack_cd);
  std::string::string((string *)(gMISSILE_PARTICLE_NAMES + 8),"Alive",&aStack_cc);
  std::string::string((string *)(gMISSILE_PARTICLE_NAMES + 0x10),"Hit",&aStack_cb);
  std::string::string((string *)(gMISSILE_PARTICLE_NAMES + 0x18),"Die",&aStack_ca);
  __cxa_atexit(::__tcf_36,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gOUTPUT_EVENTS_NAMES,L"Triggered",&aStack_c9);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 8),L"Triggered First Time",&aStack_c8);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x10),L"Deactivated",&aStack_c7);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x18),L"Deactivated First Time",
             &aStack_c6);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x20),L"On Visible",&aStack_c5);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x28),L"On Invisible",&aStack_c4);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x30),L"Enabled",&aStack_c3);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x38),L"Disabled",&aStack_c2);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x40),L"Activated",&aStack_c1)
  ;
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x48),L"Reset",&aStack_c0);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x50),L"Initialized",&aStack_bf);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x58),L"Playing",&aStack_be);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x60),L"Stopped",&aStack_bd);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x68),L"Sound Ended",&aStack_bc);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x70),L"Paused",&aStack_bb);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x78),L"Resumed",&aStack_ba);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x80),L"Incremented",&aStack_b9);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x88),L"First Increment",&aStack_b8);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x90),L"Second Increment",&aStack_b7);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x98),L"Third Increment",&aStack_b6);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xa0),L"Fourth Increment",&aStack_b5);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xa8),L"Fifth Increment",&aStack_b4);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xb0),L"Increment Greater Then Five",
             &aStack_b3);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xb8),L"Monsters Spawned",&aStack_b2);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xc0),L"Monster Killed",&aStack_b1);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 200),L"All Monsters Dead",&aStack_b0);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xd0),L"All Units Spawned",&aStack_af);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xd8),L"Item Picked Up",&aStack_ae);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xe0),L"All Items Picked Up",&aStack_ad);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xe8),L"Item Interacted",&aStack_ac);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xf0),L"All Items Interacted With",
             &aStack_ab);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xf8),L"Particle Started",&aStack_aa);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x100),L"Particle Stopped",&aStack_a9);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x108),L"Particle Paused",&aStack_a8);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x110),L"Particle Resumed",&aStack_a7);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x118),L"Stopped",&aStack_a6);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x120),L"Started",&aStack_a5);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x128),L"Paused",&aStack_a4);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x130),L"Reset to Beginning",&aStack_a3);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x138),L"Reset to End",&aStack_a2);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x140),L"Looped",&aStack_a1);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x148),L"Started Backwards",&aStack_a0);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x150),L"Started Forwards",&aStack_9f);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x158),L"Stopped Backwards",&aStack_9e);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x160),L"Stopped Forwards",&aStack_9d);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x168),L"Finished",&aStack_9c)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x170),L"State One",&aStack_9b);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x178),L"State Two",&aStack_9a);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x180),L"Activation Failed",&aStack_99);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x188),L"One",&aStack_98);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 400),L"Two",&aStack_97);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x198),L"Three",&aStack_96);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1a0),L"Four",&aStack_95);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1a8),L"Five",&aStack_94);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1b0),L"FAILED",&aStack_93);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1b8),L"SUCCESS",&aStack_92);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1c0),L"Interacted with Unit",&aStack_91
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1c8),L"HP 90 PCT",&aStack_90);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1d0),L"HP 80 PCT",&aStack_8f);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1d8),L"HP 70 PCT",&aStack_8e);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1e0),L"HP 60 PCT",&aStack_8d);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1e8),L"HP 50 PCT",&aStack_8c);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1f0),L"HP 40 PCT",&aStack_8b);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1f8),L"HP 30 PCT",&aStack_8a);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x200),L"HP 20 PCT",&aStack_89);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x208),L"HP 10 PCT",&aStack_88);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x210),L"Monster Alerted",&aStack_87);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x218),L"Player HP Below 90 PCT",
             &aStack_86);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x220),L"Player HP Below 80 PCT",
             &aStack_85);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x228),L"Player HP Below 70 PCT",
             &aStack_84);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x230),L"Player HP Below 60 PCT",
             &aStack_83);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x238),L"Player HP Below 50 PCT",
             &aStack_82);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x240),L"Player HP Below 40 PCT",
             &aStack_81);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x248),L"Player HP Below 30 PCT",
             &aStack_80);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x250),L"Player HP Below 20 PCT",
             &aStack_7f);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 600),L"Player HP Below 10 PCT",&aStack_7e
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x260),L"Player HP Above 90 PCT",
             &aStack_7d);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x268),L"Player HP Above 80 PCT",
             &aStack_7c);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x270),L"Player HP Above 70 PCT",
             &aStack_7b);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x278),L"Player HP Above 60 PCT",
             &aStack_7a);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x280),L"Player HP Above 50 PCT",
             &aStack_79);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x288),L"Player HP Above 40 PCT",
             &aStack_78);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x290),L"Player HP Above 30 PCT",
             &aStack_77);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x298),L"Player HP Above 20 PCT",
             &aStack_76);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2a0),L"Player HP Above 10 PCT",
             &aStack_75);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2a8),L"Accepted",&aStack_74)
  ;
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2b0),L"Declined",&aStack_73)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2b8),L"Camera Moving",&aStack_72);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2c0),L"Camera Stopped",&aStack_71);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2c8),L"Camera Pausing",&aStack_70);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2d0),L"Camera Control Restored",
             &aStack_6f);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2d8),L"Interacting",&aStack_6e);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2e0),L"Interacted",&aStack_6d);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2e8),L"Interacted Accepted",&aStack_6c)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2f0),L"Interacted Declined",&aStack_6b)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2f8),L"Interacted Closed",&aStack_6a);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x300),L"Invulnerable",&aStack_69);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x308),L"Vulnerable",&aStack_68);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x310),L"Quest Active",&aStack_67);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x318),L"Quest Not Active",&aStack_66);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 800),L"Quest Complete",&aStack_65);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x328),L"Quest Not Complete",&aStack_64);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x330),L"Quest Abandoned",&aStack_63);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x338),L"Skill Started",&aStack_62);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x340),L"Skill Stopped",&aStack_61);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x348),L"Skill Learned",&aStack_60);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x350),L"Skill Unlearned",&aStack_5f);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x358),L"Item Dropped",&aStack_5e);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x360),L"Item Equipped",&aStack_5d);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x368),L"Item Unequipped",&aStack_5c);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x370),L"End of Path Reached",&aStack_5b)
  ;
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x378),L"Clicked",&aStack_5a);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x380),L"Animation Stopped",&aStack_59);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x388),L"Animation Playing",&aStack_58);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x390),L"Skip Cutscene",&aStack_57);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x398),L"Level Activated",&aStack_56);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3a0),L"Insufficient funds",&aStack_55);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3a8),L"Money Taken",&aStack_54);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3b0),L"Stop",&aStack_53);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3b8),L"Start",&aStack_52);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3c0),L"Pause",&aStack_51);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3c8),L"Output 1",&aStack_50)
  ;
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3d0),L"Output 2",&aStack_4f)
  ;
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3d8),L"Output 3",&aStack_4e)
  ;
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3e0),L"Output 4",&aStack_4d)
  ;
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 1000),L"Output 5",&aStack_4c);
  __cxa_atexit(::__tcf_37,0,&__dso_handle);
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
  __cxa_atexit(::__tcf_38,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_LAYOUT_TYPE_NAMES,L"NORMAL",&aStack_2c);
  std::wstring::wstring((wstring_conflict *)(::g_LAYOUT_TYPE_NAMES + 8),L"PARTICLE",&aStack_2b);
  std::wstring::wstring((wstring_conflict *)(::g_LAYOUT_TYPE_NAMES + 0x10),L"TIMELINE",&aStack_2a);
  std::wstring::wstring((wstring_conflict *)(::g_LAYOUT_TYPE_NAMES + 0x18),L"TRIGGER",aaStack_29);
  __cxa_atexit(::__tcf_39,0,&__dso_handle);
  return;
}



/* address=00879e10
   symbol=CEquipment::addInherentDamage */

/* CEquipment::addInherentDamage(EDAMAGE_TYPES, int) */

void __thiscall CEquipment::addInherentDamage(CEquipment *this,int param_2,int param_3)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  undefined4 *puVar4;
  ulong uVar5;
  long lVar6;
  ulong uVar7;
  uint uVar8;
  int local_20;
  int local_1c [4];
  undefined4 local_c;

  piVar2 = *(int **)(this + 0x358);
  piVar3 = *(int **)(this + 0x350);
  uVar7 = (long)piVar2 - (long)piVar3 >> 2;
  if (uVar7 != 0) {
    uVar8 = 0;
    lVar6 = 0;
    iVar1 = *piVar3;
    while( true ) {
      if (iVar1 == param_2) {
        *(int *)(lVar6 + *(long *)(this + 0x380)) =
             *(int *)(lVar6 + *(long *)(this + 0x380)) + param_3;
        return;
      }
      uVar8 = uVar8 + 1;
      uVar5 = (ulong)uVar8;
      if (uVar7 <= uVar5) break;
      iVar1 = piVar3[uVar5];
      lVar6 = uVar5 * 4;
    }
  }
  local_20 = param_3;
  local_1c[0] = param_2;
  if (*(int **)(this + 0x360) == piVar2) {
    std::vector<EDAMAGE_TYPES,std::allocator<EDAMAGE_TYPES>>::_M_insert_aux
              ((vector<EDAMAGE_TYPES,std::allocator<EDAMAGE_TYPES>> *)(this + 0x350),piVar2,local_1c
              );
  }
  else {
    lVar6 = 0;
    if (piVar2 != (int *)0x0) {
      *piVar2 = param_2;
      lVar6 = *(long *)(this + 0x358);
    }
    *(long *)(this + 0x358) = lVar6 + 4;
  }
  puVar4 = *(undefined4 **)(this + 0x370);
  local_c = 0;
  if (puVar4 == *(undefined4 **)(this + 0x378)) {
    std::vector<int,std::allocator<int>>::_M_insert_aux
              ((vector<int,std::allocator<int>> *)(this + 0x368),puVar4,&local_c);
  }
  else {
    lVar6 = 0;
    if (puVar4 != (undefined4 *)0x0) {
      *puVar4 = 0;
      lVar6 = *(long *)(this + 0x370);
    }
    *(long *)(this + 0x370) = lVar6 + 4;
  }
  piVar2 = *(int **)(this + 0x388);
  if (piVar2 == *(int **)(this + 0x390)) {
    std::vector<int,std::allocator<int>>::_M_insert_aux
              ((vector<int,std::allocator<int>> *)(this + 0x380),piVar2,&local_20);
  }
  else {
    lVar6 = 0;
    if (piVar2 != (int *)0x0) {
      *piVar2 = local_20;
      lVar6 = *(long *)(this + 0x388);
    }
    *(long *)(this + 0x388) = lVar6 + 4;
  }
  return;
}



/* address=00879f60
   symbol=CEquipment::addDamageBonus */

/* CEquipment::addDamageBonus(EDAMAGE_TYPES, int) */

void __thiscall CEquipment::addDamageBonus(CEquipment *this,int param_2,int param_3)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  undefined4 *puVar4;
  ulong uVar5;
  long lVar6;
  ulong uVar7;
  uint uVar8;
  int local_20;
  int local_1c [4];
  undefined4 local_c;

  piVar2 = *(int **)(this + 0x358);
  piVar3 = *(int **)(this + 0x350);
  uVar7 = (long)piVar2 - (long)piVar3 >> 2;
  if (uVar7 != 0) {
    uVar8 = 0;
    lVar6 = 0;
    iVar1 = *piVar3;
    while( true ) {
      if (iVar1 == param_2) {
        *(int *)(lVar6 + *(long *)(this + 0x368)) =
             *(int *)(lVar6 + *(long *)(this + 0x368)) + param_3;
        return;
      }
      uVar8 = uVar8 + 1;
      uVar5 = (ulong)uVar8;
      if (uVar7 <= uVar5) break;
      iVar1 = piVar3[uVar5];
      lVar6 = uVar5 * 4;
    }
  }
  local_20 = param_3;
  local_1c[0] = param_2;
  if (*(int **)(this + 0x360) == piVar2) {
    std::vector<EDAMAGE_TYPES,std::allocator<EDAMAGE_TYPES>>::_M_insert_aux
              ((vector<EDAMAGE_TYPES,std::allocator<EDAMAGE_TYPES>> *)(this + 0x350),piVar2,local_1c
              );
  }
  else {
    lVar6 = 0;
    if (piVar2 != (int *)0x0) {
      *piVar2 = param_2;
      lVar6 = *(long *)(this + 0x358);
    }
    *(long *)(this + 0x358) = lVar6 + 4;
  }
  piVar2 = *(int **)(this + 0x370);
  if (piVar2 == *(int **)(this + 0x378)) {
    std::vector<int,std::allocator<int>>::_M_insert_aux
              ((vector<int,std::allocator<int>> *)(this + 0x368),piVar2,&local_20);
  }
  else {
    lVar6 = 0;
    if (piVar2 != (int *)0x0) {
      *piVar2 = local_20;
      lVar6 = *(long *)(this + 0x370);
    }
    *(long *)(this + 0x370) = lVar6 + 4;
  }
  puVar4 = *(undefined4 **)(this + 0x388);
  local_c = 0;
  if (puVar4 == *(undefined4 **)(this + 0x390)) {
    std::vector<int,std::allocator<int>>::_M_insert_aux
              ((vector<int,std::allocator<int>> *)(this + 0x380),puVar4,&local_c);
  }
  else {
    lVar6 = 0;
    if (puVar4 != (undefined4 *)0x0) {
      *puVar4 = 0;
      lVar6 = *(long *)(this + 0x388);
    }
    *(long *)(this + 0x388) = lVar6 + 4;
  }
  return;
}



/* address=0087a400
   symbol=CEquipment::updateDrop */

/* CEquipment::updateDrop(float) */

void __thiscall CEquipment::updateDrop(CEquipment *this,float param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  char cVar11;
  CPath *this_00;
  float fVar12;
  float fVar13;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  undefined8 local_18;
  float local_10;

  if (this[0x25c] != (CEquipment)0x0) {
    fVar12 = param_1 * DAT_00fb2bd8 + *(float *)(this + 600);
    *(float *)(this + 600) = fVar12;
    this_00 = *(CPath **)(this + 0x250);
    fVar13 = *(float *)(this_00 + 0x18);
    if (fVar13 <= fVar12) {
      *(float *)(this + 600) = fVar13;
      (**(code **)(*(long *)this + 0x40))(this,1);
      fVar13 = 0.0;
      this[0x25c] = (CEquipment)0x0;
      CSoundBank::playSample
                (*(CSoundBank **)(this + 0x1d8),0x11,*(SceneNode **)(this + 0x58),0.0,0.0,false);
      fVar12 = *(float *)(this + 600);
      this_00 = *(CPath **)(this + 0x250);
    }
    local_18 = CPath::GetSplinePositionAtDistance(this_00,fVar12);
    *(undefined8 *)(this + 0x84) = local_18;
    *(float *)(this + 0x8c) = fVar13;
    local_10 = fVar13;
    CPositionableObject::setPosition((CPositionableObject *)this,(Vector3 *)(this + 0x84));
    cVar11 = CBaseUnit::ISA((CBaseUnit *)this,8);
    if ((((cVar11 != '\0') || (cVar11 = CBaseUnit::ISA((CBaseUnit *)this,0x15), cVar11 != '\0')) ||
        (cVar11 = CBaseUnit::ISA((CBaseUnit *)this,0x21), cVar11 != '\0')) ||
       (cVar11 = CBaseUnit::ISA((CBaseUnit *)this,0x2a), cVar11 != '\0')) {
      fVar12 = *(float *)(this + 600) / *(float *)(*(long *)(this + 0x250) + 0x18);
      fVar13 = DAT_00fa47fc;
      if (fVar12 <= DAT_00fa47fc) {
        fVar13 = fVar12;
      }
      MATH::matrixRotationZ((Matrix4 *)&local_58,fVar13 * DAT_00fa86f0);
      fVar13 = *(float *)(this + 0x2f0);
      fVar12 = *(float *)(this + 0x2f4);
      fVar1 = *(float *)(this + 0x2f8);
      fVar2 = *(float *)(this + 0x2fc);
      fVar3 = *(float *)(this + 0x304);
      fVar4 = *(float *)(this + 0x308);
      fVar5 = *(float *)(this + 0x30c);
      fVar6 = *(float *)(this + 0x300);
      fVar7 = *(float *)(this + 0x310);
      fVar8 = *(float *)(this + 0x314);
      fVar9 = *(float *)(this + 0x318);
      fVar10 = *(float *)(this + 0x31c);
      *(ulong *)(this + 0xc0) =
           CONCAT44(fVar13 * local_54 + fVar12 * local_44 + fVar1 * local_34 + fVar2 * local_24,
                    fVar13 * local_58 + fVar12 * local_48 + fVar1 * local_38 + fVar2 * local_28);
      *(ulong *)(this + 200) =
           CONCAT44(fVar13 * local_4c + fVar12 * local_3c + fVar1 * local_2c + fVar2 * local_1c,
                    fVar13 * local_50 + fVar12 * local_40 + local_30 * fVar1 + local_20 * fVar2);
      fVar13 = *(float *)(this + 800);
      fVar12 = *(float *)(this + 0x324);
      fVar1 = *(float *)(this + 0x328);
      fVar2 = *(float *)(this + 0x32c);
      *(ulong *)(this + 0xd0) =
           CONCAT44(local_54 * fVar6 + local_44 * fVar3 + local_34 * fVar4 + local_24 * fVar5,
                    local_58 * fVar6 + local_48 * fVar3 + local_38 * fVar4 + local_28 * fVar5);
      *(ulong *)(this + 0xd8) =
           CONCAT44(fVar6 * local_4c + fVar3 * local_3c + fVar4 * local_2c + fVar5 * local_1c,
                    local_50 * fVar6 + local_40 * fVar3 + local_30 * fVar4 + local_20 * fVar5);
      *(ulong *)(this + 0xe0) =
           CONCAT44(local_54 * fVar7 + local_44 * fVar8 + local_34 * fVar9 + local_24 * fVar10,
                    local_58 * fVar7 + local_48 * fVar8 + local_38 * fVar9 + local_28 * fVar10);
      *(ulong *)(this + 0xe8) =
           CONCAT44(fVar7 * local_4c + fVar8 * local_3c + fVar9 * local_2c + fVar10 * local_1c,
                    local_50 * fVar7 + local_40 * fVar8 + local_30 * fVar9 + local_20 * fVar10);
      *(ulong *)(this + 0xf0) =
           CONCAT44(local_54 * fVar13 + local_44 * fVar12 + local_34 * fVar1 + local_24 * fVar2,
                    local_58 * fVar13 + local_48 * fVar12 + local_38 * fVar1 + local_28 * fVar2);
      *(ulong *)(this + 0xf8) =
           CONCAT44(fVar13 * local_4c + fVar12 * local_3c + fVar1 * local_2c + fVar2 * local_1c,
                    local_50 * fVar13 + local_40 * fVar12 + local_30 * fVar1 + local_20 * fVar2);
      (**(code **)(*(long *)this + 0x118))(this,this + 0xc0,0);
    }
  }
  return;
}



/* address=0087aa50
   symbol=CEquipment::update */

/* CEquipment::update(Ogre::Camera*, Ogre::Vector3 const&, float) */

void __thiscall CEquipment::update(CEquipment *this,Camera *param_1,Vector3 *param_2,float param_3)

{
  CItem::update((CItem *)this,param_1,param_2,param_3);
  if (this[0x25c] != (CEquipment)0x0) {
    updateDrop(this,param_3);
  }
  updateVisualLayout(param_3);
  return;
}



/* address=0087aaa0
   symbol=CEquipment::drop */

/* CEquipment::drop() */

void __thiscall CEquipment::drop(CEquipment *this)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  undefined8 uVar16;
  undefined8 uVar17;
  undefined8 uVar18;
  undefined8 uVar19;
  undefined8 uVar20;
  undefined8 uVar21;
  undefined8 uVar22;
  char cVar23;
  long lVar24;
  CGenericModel *this_00;
  CPath *pCVar25;
  undefined *puVar26;
  CLevel *pCVar27;
  undefined8 uVar28;
  float fVar29;
  float fVar30;
  float local_a8;
  float local_a4;
  float local_a0;
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined8 local_48;
  float local_40;
  string local_38 [15];
  allocator local_29 [9];

  if ((*(long *)(this + 0x68) != 0) && (*(long *)(*(long *)(this + 0x68) + 0x18) != 0)) {
    fVar29 = (float)UTILITIES::randomBetweenVolatile(0.0,DAT_00fc456c);
    *(undefined8 *)(this + 0xc0) = Ogre::Matrix4::IDENTITY;
    *(undefined8 *)(this + 200) = DAT_01423fc8;
    *(undefined8 *)(this + 0xd0) = DAT_01423fd0;
    *(undefined8 *)(this + 0xd8) = DAT_01423fd8;
    *(undefined8 *)(this + 0xe0) = DAT_01423fe0;
    *(undefined8 *)(this + 0xe8) = DAT_01423fe8;
    *(undefined8 *)(this + 0xf0) = DAT_01423ff0;
    *(undefined8 *)(this + 0xf8) = DAT_01423ff8;
    cVar23 = CBaseUnit::ISA((CBaseUnit *)this,0x6e);
    if (cVar23 == '\0') {
      cVar23 = CBaseUnit::ISA((CBaseUnit *)this,8);
      if (cVar23 == '\0') {
        cVar23 = CBaseUnit::ISA((CBaseUnit *)this,0x15);
        if (cVar23 == '\0') {
          cVar23 = CBaseUnit::ISA((CBaseUnit *)this,0x14);
          if (((cVar23 != '\0') || (cVar23 = CBaseUnit::ISA((CBaseUnit *)this,0xc), cVar23 != '\0'))
             && (*(long **)(this + 0x2b0) != (long *)0x0)) {
            (**(code **)(**(long **)(this + 0x2b0) + 0x58))();
            (**(code **)(**(long **)(this + 0x2b0) + 0x118))
                      (*(long **)(this + 0x2b0),&Ogre::Matrix4::IDENTITY,0);
          }
        }
        else {
          MATH::matrixRotationZ((Matrix4 *)&local_a8,DAT_00fd1100);
          fVar1 = *(float *)(this + 0xc0);
          fVar2 = *(float *)(this + 0xc4);
          fVar3 = *(float *)(this + 200);
          fVar4 = *(float *)(this + 0xcc);
          fVar5 = *(float *)(this + 0xd0);
          fVar6 = *(float *)(this + 0xd4);
          fVar7 = *(float *)(this + 0xd8);
          fVar8 = *(float *)(this + 0xdc);
          fVar9 = *(float *)(this + 0xe0);
          fVar10 = *(float *)(this + 0xe4);
          fVar30 = *(float *)(this + 0xe8);
          fVar11 = *(float *)(this + 0xec);
          fVar12 = *(float *)(this + 0xf0);
          fVar13 = *(float *)(this + 0xf4);
          fVar14 = *(float *)(this + 0xf8);
          fVar15 = *(float *)(this + 0xfc);
          *(ulong *)(this + 0xc0) =
               CONCAT44(fVar1 * local_a4 + fVar2 * local_94 + fVar3 * local_84 + fVar4 * local_74,
                        fVar1 * local_a8 + fVar2 * local_98 + fVar3 * local_88 + fVar4 * local_78);
          *(ulong *)(this + 200) =
               CONCAT44(fVar1 * local_9c + fVar2 * local_8c + fVar3 * local_7c + fVar4 * local_6c,
                        fVar1 * local_a0 + fVar2 * local_90 + local_80 * fVar3 + local_70 * fVar4);
          *(ulong *)(this + 0xd0) =
               CONCAT44(local_a4 * fVar5 + local_94 * fVar6 + local_84 * fVar7 + local_74 * fVar8,
                        local_a8 * fVar5 + local_98 * fVar6 + local_88 * fVar7 + local_78 * fVar8);
          *(ulong *)(this + 0xd8) =
               CONCAT44(fVar5 * local_9c + fVar6 * local_8c + fVar7 * local_7c + fVar8 * local_6c,
                        local_a0 * fVar5 + local_90 * fVar6 + local_80 * fVar7 + local_70 * fVar8);
          *(ulong *)(this + 0xe0) =
               CONCAT44(local_a4 * fVar9 + local_94 * fVar10 + local_84 * fVar30 + local_74 * fVar11
                        ,local_a8 * fVar9 + local_98 * fVar10 + local_88 * fVar30 +
                         local_78 * fVar11);
          *(ulong *)(this + 0xe8) =
               CONCAT44(fVar9 * local_9c + fVar10 * local_8c + fVar30 * local_7c + fVar11 * local_6c
                        ,local_a0 * fVar9 + local_90 * fVar10 + local_80 * fVar30 +
                         local_70 * fVar11);
          *(ulong *)(this + 0xf0) =
               CONCAT44(local_a4 * fVar12 + local_94 * fVar13 + local_84 * fVar14 +
                        local_74 * fVar15,
                        local_a8 * fVar12 + local_98 * fVar13 + local_88 * fVar14 +
                        local_78 * fVar15);
          *(ulong *)(this + 0xf8) =
               CONCAT44(fVar12 * local_9c + fVar13 * local_8c + fVar14 * local_7c +
                        fVar15 * local_6c,
                        local_a0 * fVar12 + local_90 * fVar13 + local_80 * fVar14 +
                        local_70 * fVar15);
        }
      }
      else {
        MATH::matrixRotationZ((Matrix4 *)&local_a8,DAT_00fd10fc);
        fVar1 = *(float *)(this + 0xc0);
        fVar2 = *(float *)(this + 0xc4);
        fVar3 = *(float *)(this + 200);
        fVar4 = *(float *)(this + 0xcc);
        fVar5 = *(float *)(this + 0xd0);
        fVar6 = *(float *)(this + 0xd4);
        fVar7 = *(float *)(this + 0xd8);
        fVar8 = *(float *)(this + 0xdc);
        fVar9 = *(float *)(this + 0xe0);
        fVar10 = *(float *)(this + 0xe4);
        fVar30 = *(float *)(this + 0xe8);
        fVar11 = *(float *)(this + 0xec);
        fVar12 = *(float *)(this + 0xf0);
        fVar13 = *(float *)(this + 0xf4);
        fVar14 = *(float *)(this + 0xf8);
        fVar15 = *(float *)(this + 0xfc);
        *(ulong *)(this + 0xc0) =
             CONCAT44(fVar1 * local_a4 + fVar2 * local_94 + fVar3 * local_84 + fVar4 * local_74,
                      fVar1 * local_a8 + fVar2 * local_98 + fVar3 * local_88 + fVar4 * local_78);
        *(ulong *)(this + 200) =
             CONCAT44(fVar1 * local_9c + fVar2 * local_8c + fVar3 * local_7c + fVar4 * local_6c,
                      fVar1 * local_a0 + fVar2 * local_90 + local_80 * fVar3 + local_70 * fVar4);
        *(ulong *)(this + 0xd0) =
             CONCAT44(local_a4 * fVar5 + local_94 * fVar6 + local_84 * fVar7 + local_74 * fVar8,
                      local_a8 * fVar5 + local_98 * fVar6 + local_88 * fVar7 + local_78 * fVar8);
        *(ulong *)(this + 0xd8) =
             CONCAT44(fVar5 * local_9c + fVar6 * local_8c + fVar7 * local_7c + fVar8 * local_6c,
                      local_a0 * fVar5 + local_90 * fVar6 + local_80 * fVar7 + local_70 * fVar8);
        *(ulong *)(this + 0xe0) =
             CONCAT44(local_a4 * fVar9 + local_94 * fVar10 + local_84 * fVar30 + local_74 * fVar11,
                      local_a8 * fVar9 + local_98 * fVar10 + local_88 * fVar30 + local_78 * fVar11);
        *(ulong *)(this + 0xe8) =
             CONCAT44(fVar9 * local_9c + fVar10 * local_8c + fVar30 * local_7c + fVar11 * local_6c,
                      local_a0 * fVar9 + local_90 * fVar10 + local_80 * fVar30 + local_70 * fVar11);
        *(ulong *)(this + 0xf0) =
             CONCAT44(local_a4 * fVar12 + local_94 * fVar13 + local_84 * fVar14 + local_74 * fVar15,
                      local_a8 * fVar12 + local_98 * fVar13 + local_88 * fVar14 + local_78 * fVar15)
        ;
        *(ulong *)(this + 0xf8) =
             CONCAT44(fVar12 * local_9c + fVar13 * local_8c + fVar14 * local_7c + fVar15 * local_6c,
                      local_a0 * fVar12 + local_90 * fVar13 + local_80 * fVar14 + local_70 * fVar15)
        ;
      }
    }
    else {
      MATH::matrixRotationX((Matrix4 *)&local_a8,DAT_00fd10f8);
      fVar1 = *(float *)(this + 0xc0);
      fVar2 = *(float *)(this + 0xc4);
      fVar3 = *(float *)(this + 200);
      fVar4 = *(float *)(this + 0xcc);
      fVar5 = *(float *)(this + 0xd0);
      fVar6 = *(float *)(this + 0xd4);
      fVar7 = *(float *)(this + 0xd8);
      fVar8 = *(float *)(this + 0xdc);
      fVar9 = *(float *)(this + 0xe0);
      fVar10 = *(float *)(this + 0xe4);
      fVar30 = *(float *)(this + 0xe8);
      fVar11 = *(float *)(this + 0xec);
      fVar12 = *(float *)(this + 0xf0);
      fVar13 = *(float *)(this + 0xf4);
      fVar14 = *(float *)(this + 0xf8);
      fVar15 = *(float *)(this + 0xfc);
      *(ulong *)(this + 0xc0) =
           CONCAT44(fVar1 * local_a4 + fVar2 * local_94 + fVar3 * local_84 + fVar4 * local_74,
                    fVar1 * local_a8 + fVar2 * local_98 + fVar3 * local_88 + fVar4 * local_78);
      *(ulong *)(this + 200) =
           CONCAT44(fVar1 * local_9c + fVar2 * local_8c + fVar3 * local_7c + fVar4 * local_6c,
                    fVar1 * local_a0 + fVar2 * local_90 + local_80 * fVar3 + local_70 * fVar4);
      *(ulong *)(this + 0xd0) =
           CONCAT44(local_a4 * fVar5 + local_94 * fVar6 + local_84 * fVar7 + local_74 * fVar8,
                    local_a8 * fVar5 + local_98 * fVar6 + local_88 * fVar7 + local_78 * fVar8);
      *(ulong *)(this + 0xd8) =
           CONCAT44(fVar5 * local_9c + fVar6 * local_8c + fVar7 * local_7c + fVar8 * local_6c,
                    local_a0 * fVar5 + local_90 * fVar6 + local_80 * fVar7 + local_70 * fVar8);
      *(ulong *)(this + 0xe0) =
           CONCAT44(local_a4 * fVar9 + local_94 * fVar10 + local_84 * fVar30 + local_74 * fVar11,
                    local_a8 * fVar9 + local_98 * fVar10 + local_88 * fVar30 + local_78 * fVar11);
      *(ulong *)(this + 0xe8) =
           CONCAT44(fVar9 * local_9c + fVar10 * local_8c + fVar30 * local_7c + fVar11 * local_6c,
                    local_a0 * fVar9 + local_90 * fVar10 + local_80 * fVar30 + local_70 * fVar11);
      *(ulong *)(this + 0xf0) =
           CONCAT44(local_a4 * fVar12 + local_94 * fVar13 + local_84 * fVar14 + local_74 * fVar15,
                    local_a8 * fVar12 + local_98 * fVar13 + local_88 * fVar14 + local_78 * fVar15);
      *(ulong *)(this + 0xf8) =
           CONCAT44(fVar12 * local_9c + fVar13 * local_8c + fVar14 * local_7c + fVar15 * local_6c,
                    local_a0 * fVar12 + local_90 * fVar13 + local_80 * fVar14 + local_70 * fVar15);
    }
    MATH::matrixRotationY((Matrix4 *)&local_a8,fVar29 * DAT_00fce49c);
    fVar29 = *(float *)(this + 0xc0);
    fVar1 = *(float *)(this + 0xd0);
    fVar2 = *(float *)(this + 0xe0);
    fVar3 = *(float *)(this + 0xf0);
    fVar4 = *(float *)(this + 0xc4);
    fVar5 = *(float *)(this + 0xd4);
    fVar6 = *(float *)(this + 0xe4);
    fVar7 = *(float *)(this + 0xf4);
    fVar8 = *(float *)(this + 200);
    fVar9 = *(float *)(this + 0xd8);
    uVar28 = CONCAT44(local_a8 * fVar4 + local_a4 * fVar5 + local_a0 * fVar6 + local_9c * fVar7,
                      local_a8 * fVar29 + local_a4 * fVar1 + local_a0 * fVar2 + local_9c * fVar3);
    fVar10 = *(float *)(this + 0xe8);
    fVar30 = *(float *)(this + 0xf8) * local_6c;
    *(undefined8 *)(this + 0xc0) = uVar28;
    uVar16 = CONCAT44(local_a8 * *(float *)(this + 0xcc) + local_a4 * *(float *)(this + 0xdc) +
                      local_a0 * *(float *)(this + 0xec) + local_9c * *(float *)(this + 0xfc),
                      local_a8 * fVar8 + local_a4 * fVar9 + *(float *)(this + 0xe8) * local_a0 +
                      *(float *)(this + 0xf8) * local_9c);
    *(undefined8 *)(this + 200) = uVar16;
    uVar17 = CONCAT44(fVar4 * local_98 + fVar5 * local_94 + fVar6 * local_90 + fVar7 * local_8c,
                      fVar29 * local_98 + fVar1 * local_94 + fVar2 * local_90 + fVar3 * local_8c);
    *(undefined8 *)(this + 0xd0) = uVar17;
    uVar18 = CONCAT44(local_98 * *(float *)(this + 0xcc) + local_94 * *(float *)(this + 0xdc) +
                      local_90 * *(float *)(this + 0xec) + local_8c * *(float *)(this + 0xfc),
                      fVar8 * local_98 + fVar9 * local_94 + *(float *)(this + 0xe8) * local_90 +
                      *(float *)(this + 0xf8) * local_8c);
    *(undefined8 *)(this + 0xd8) = uVar18;
    uVar19 = CONCAT44(fVar4 * local_88 + fVar5 * local_84 + fVar6 * local_80 + fVar7 * local_7c,
                      fVar29 * local_88 + fVar1 * local_84 + fVar2 * local_80 + fVar3 * local_7c);
    *(undefined8 *)(this + 0xe0) = uVar19;
    uVar20 = CONCAT44(local_88 * *(float *)(this + 0xcc) + local_84 * *(float *)(this + 0xdc) +
                      local_80 * *(float *)(this + 0xec) + local_7c * *(float *)(this + 0xfc),
                      fVar8 * local_88 + fVar9 * local_84 + *(float *)(this + 0xe8) * local_80 +
                      *(float *)(this + 0xf8) * local_7c);
    *(undefined8 *)(this + 0xe8) = uVar20;
    uVar21 = CONCAT44(fVar4 * local_78 + fVar5 * local_74 + fVar6 * local_70 + fVar7 * local_6c,
                      fVar29 * local_78 + fVar1 * local_74 + fVar2 * local_70 + fVar3 * local_6c);
    *(undefined8 *)(this + 0xf0) = uVar21;
    uVar22 = CONCAT44(local_78 * *(float *)(this + 0xcc) + local_74 * *(float *)(this + 0xdc) +
                      local_70 * *(float *)(this + 0xec) + local_6c * *(float *)(this + 0xfc),
                      fVar8 * local_78 + fVar9 * local_74 + fVar10 * local_70 + fVar30);
    *(undefined8 *)(this + 0x308) = uVar18;
    *(undefined8 *)(this + 0x310) = uVar19;
    *(undefined8 *)(this + 800) = uVar21;
    *(undefined8 *)(this + 0x2f0) = uVar28;
    *(undefined8 *)(this + 0xf8) = uVar22;
    *(undefined8 *)(this + 0x328) = uVar22;
    *(undefined8 *)(this + 0x2f8) = uVar16;
    *(undefined8 *)(this + 0x300) = uVar17;
    *(undefined8 *)(this + 0x318) = uVar20;
    (**(code **)(*(long *)this + 0x118))(this,this + 0xc0,0);
    if (this[0x25e] == (CEquipment)0x0) {
      pCVar27 = (CLevel *)0x0;
      if (*(long *)(this + 0x68) != 0) {
        pCVar27 = *(CLevel **)(*(long *)(this + 0x68) + 0x18);
      }
      local_48 = CLevel::randomOpenItemPosition(pCVar27,(Vector3 *)(this + 0x84),DAT_00fa47fc,false)
      ;
      uVar28 = 0;
      if (*(long *)(this + 0x68) != 0) {
        uVar28 = *(undefined8 *)(*(long *)(this + 0x68) + 0x18);
      }
      local_40 = fVar30;
      fVar29 = (float)CLevel::floorHeight(local_48,uVar28);
      local_48._4_4_ = fVar29 + DAT_00fc67e8;
      cVar23 = CBaseUnit::ISA((CBaseUnit *)this,8);
      if (cVar23 != '\0') {
        local_48._4_4_ = DAT_00fce4dc + local_48._4_4_;
      }
      CSoundBank::playSample
                (*(CSoundBank **)(this + 0x1d8),0x10,*(SceneNode **)(this + 0x58),0.0,0.0,false);
      CPositionableObject::setPosition((CPositionableObject *)this,(Vector3 *)&local_48);
    }
    else {
      fVar29 = 0.0;
      CSoundBank::playSample
                (*(CSoundBank **)(this + 0x1d8),0x10,*(SceneNode **)(this + 0x58),0.0,0.0,false);
      pCVar27 = (CLevel *)0x0;
      if (*(long *)(this + 0x68) != 0) {
        pCVar27 = *(CLevel **)(*(long *)(this + 0x68) + 0x18);
      }
      local_48 = CLevel::randomOpenItemPosition(pCVar27,(Vector3 *)(this + 0x84),DAT_00fce498,false)
      ;
      uVar28 = 0;
      if (*(long *)(this + 0x68) != 0) {
        uVar28 = *(undefined8 *)(*(long *)(this + 0x68) + 0x18);
      }
      local_40 = fVar29;
      fVar29 = (float)CLevel::floorHeight(local_48,fVar29,uVar28);
      local_48._4_4_ = fVar29 + DAT_00fc67e8;
      cVar23 = CBaseUnit::ISA((CBaseUnit *)this,8);
      if (cVar23 != '\0') {
        local_48._4_4_ = DAT_00fce4dc + local_48._4_4_;
      }
      pCVar25 = *(CPath **)(this + 0x250);
      if (pCVar25 == (CPath *)0x0) {
        puVar26 = &DAT_00fc9949;
                    /* try { // try from 0087c468 to 0087c46c has its CatchHandler @ 0087c512 */
        std::string::string(local_38,"DROP",local_29);
        local_58 = 0;
        local_54 = 0;
        local_50 = 0;
                    /* try { // try from 0087c493 to 0087c497 has its CatchHandler @ 0087c50d */
        pCVar25 = Ogre::AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0>>::
                  operator_new((AllocatedObject<Ogre::CategorisedAllocPolicy<(Ogre::MemoryCategory)0>>
                                *)0xc8,(ulong)puVar26);
                    /* try { // try from 0087c4ab to 0087c4af has its CatchHandler @ 0087c4f2 */
        CPath::CPath(pCVar25,local_38,0,&local_58);
        *(CPath **)(this + 0x250) = pCVar25;
                    /* try { // try from 0087c4ba to 0087c4be has its CatchHandler @ 0087c512 */
        std::string::~string(local_38);
        pCVar25 = *(CPath **)(this + 0x250);
      }
      CPath::Clear(pCVar25);
      (**(code **)(*(long *)this + 0x40))(this,0);
      this[0x25c] = (CEquipment)0x1;
      *(undefined4 *)(this + 600) = 0;
      local_60 = (local_40 + *(float *)(this + 0x8c)) * DAT_00fa4810;
      local_68 = ((float)local_48 + *(float *)(this + 0x84)) * DAT_00fa4810;
      fVar29 = (local_48._4_4_ + *(float *)(this + 0x88)) * DAT_00fa4810;
      local_64 = fVar29;
      local_64 = (float)UTILITIES::randomBetweenVolatile(DAT_00fd1104,DAT_00fce4f0);
      local_64 = local_64 + fVar29;
      CPath::AddPoint(*(CPath **)(this + 0x250),(Vector3 *)(this + 0x84),DAT_00fce4d4,DAT_00fa8778);
      CPath::AddPoint(*(CPath **)(this + 0x250),(Vector3 *)&local_68,DAT_00fce4d4,DAT_00fa8778);
      CPath::AddPoint(*(CPath **)(this + 0x250),(Vector3 *)&local_48,DAT_00fce4d4,DAT_00fa8778);
    }
    lVar24 = (**(code **)(*(long *)this + 0x1e0))(this);
    fVar29 = DAT_00fa47fc;
    if (lVar24 != 0) {
      *(float *)(this + 0x204) = DAT_00fa47fc;
      CItem::updateOpacity((CItem *)this,0.0,true);
      this_00 = (CGenericModel *)(**(code **)(*(long *)this + 0x1e0))(this);
      CGenericModel::setOpacity(this_00,fVar29);
      this[0x218] = (CEquipment)0x0;
      (**(code **)(*(long *)this + 0x2c0))(this,1,1);
    }
    setRenderBehind(this,true);
  }
  return;
}



/* address=0087d5f0
   symbol=CEquipment::getFlavorDescription */

/* WARNING: Removing unreachable block (ram,0x0087d69d) */
/* CEquipment::getFlavorDescription() */

void CEquipment::getFlavorDescription(void)

{
  int *piVar1;
  int iVar2;
  wstring_conflict *pwVar3;
  long in_RSI;
  wstring_conflict *in_RDI;
  long local_28;
  allocator local_19;

                    /* try { // try from 0087d616 to 0087d61a has its CatchHandler @ 0087d698 */
  std::wstring::wstring((wstring_conflict *)&local_28,L"DESCRIPTION",&local_19);
                    /* try { // try from 0087d62b to 0087d63a has its CatchHandler @ 0087d685 */
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
  return;
}



/* address=0087d6b0
   symbol=CEquipment::getSet */

/* WARNING: Removing unreachable block (ram,0x0087d75d) */
/* CEquipment::getSet() */

void CEquipment::getSet(void)

{
  int *piVar1;
  int iVar2;
  wstring_conflict *pwVar3;
  long in_RSI;
  wstring_conflict *in_RDI;
  long local_28;
  allocator local_19;

                    /* try { // try from 0087d6d6 to 0087d6da has its CatchHandler @ 0087d758 */
  std::wstring::wstring((wstring_conflict *)&local_28,L"SET",&local_19);
                    /* try { // try from 0087d6eb to 0087d6fa has its CatchHandler @ 0087d745 */
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
  return;
}



/* address=0087d770
   symbol=CEquipment::~CEquipment */

/* WARNING: Removing unreachable block (ram,0x0087dd02) */
/* WARNING: Removing unreachable block (ram,0x0087dd6a) */
/* WARNING: Removing unreachable block (ram,0x0087ddd2) */
/* WARNING: Removing unreachable block (ram,0x0087ddc7) */
/* WARNING: Removing unreachable block (ram,0x0087dd5f) */
/* WARNING: Removing unreachable block (ram,0x0087dcf7) */
/* CEquipment::~CEquipment() */

void __thiscall CEquipment::~CEquipment(CEquipment *this)

{
  allocator *paVar1;
  int *piVar2;
  int iVar3;
  long lVar4;
  CCollisionModel *pCVar5;
  long lVar6;
  uint uVar7;
  long *plVar8;
  CMasterResourceManager *this_00;
  undefined8 *puVar9;
  long lVar10;
  uint uVar11;
  uint uVar12;
  ulong uVar13;

  *(undefined ***)this = &PTR__CEquipment_00fd0cf0;
  *(undefined ***)(this + 0x230) = &PTR__CEquipment_00fd1070;
  if (*(long *)(this + 0x428) != 0) {
                    /* try { // try from 0087d799 to 0087d9f9 has its CatchHandler @ 0087dbb2 */
    resetVisualLayout(this);
    if (*(long **)(this + 0x428) != (long *)0x0) {
      (**(code **)(**(long **)(this + 0x428) + 8))();
      *(undefined8 *)(this + 0x428) = 0;
    }
  }
  if (*(int *)(this + 0x418) != 0) {
    uVar13 = 0;
    do {
      while( true ) {
        uVar11 = *(uint *)(this + 0x41c);
        uVar12 = (uint)uVar13;
        if (uVar12 < uVar11) {
          plVar8 = (long *)(uVar13 * 8 + *(long *)(this + 0x410));
        }
        else {
          plVar8 = *(long **)(this + 0x410);
        }
        if (*plVar8 != 0) break;
LAB_0087d861:
        uVar13 = (ulong)(uVar12 + 1);
        if (*(uint *)(this + 0x418) <= uVar12 + 1) goto LAB_0087d870;
      }
      if (uVar12 < uVar11) {
        puVar9 = (undefined8 *)(uVar13 * 8 + *(long *)(this + 0x410));
      }
      else {
        puVar9 = *(undefined8 **)(this + 0x410);
      }
      if (*(long *)*puVar9 == 0) goto LAB_0087d861;
      if (uVar12 < uVar11) {
        puVar9 = (undefined8 *)(uVar13 * 8 + *(long *)(this + 0x410));
      }
      else {
        puVar9 = *(undefined8 **)(this + 0x410);
      }
      lVar4 = *(long *)*puVar9;
      uVar11 = *(uint *)(lVar4 + 0x1d0);
      if (uVar11 == 0) goto LAB_0087d861;
      plVar8 = *(long **)(lVar4 + 0x1c8);
      uVar7 = 0;
      lVar6 = 8;
      if (this + 0x230 == (CEquipment *)*plVar8) {
        lVar10 = 0;
      }
      else {
        do {
          lVar10 = lVar6;
          uVar7 = uVar7 + 1;
          if (uVar11 <= uVar7) goto LAB_0087d861;
          lVar6 = lVar10 + 8;
        } while (this + 0x230 != *(CEquipment **)((long)plVar8 + lVar10));
      }
      uVar13 = (ulong)(uVar12 + 1);
      *(uint *)(lVar4 + 0x1d0) = uVar11 - 1;
      *(long *)((long)plVar8 + lVar10) = plVar8[uVar11 - 1];
    } while (uVar12 + 1 < *(uint *)(this + 0x418));
  }
LAB_0087d870:
  if (*(int *)(this + 0x3f0) != 0) {
    uVar11 = 0;
    do {
      lVar4 = (ulong)uVar11 * 8;
      plVar8 = (long *)(lVar4 + *(long *)(this + 1000));
      if ((long *)*plVar8 != (long *)0x0) {
        (**(code **)(*(long *)*plVar8 + 8))();
        *(undefined8 *)(*(long *)(this + 1000) + (ulong)uVar11 * 8) = 0;
        plVar8 = (long *)(lVar4 + *(long *)(this + 1000));
      }
      *plVar8 = 0;
      uVar11 = uVar11 + 1;
    } while (uVar11 < *(uint *)(this + 0x3f0));
  }
  *(undefined4 *)(this + 0x3f0) = 0;
  *(undefined4 *)(this + 0x3f4) = 0;
  if (*(void **)(this + 1000) != (void *)0x0) {
    operator_delete__(*(void **)(this + 1000));
  }
  *(undefined8 *)(this + 1000) = 0;
  if (*(long **)(this + 0x3c8) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x3c8) + 8))();
    *(undefined8 *)(this + 0x3c8) = 0;
  }
  if (*(long **)(this + 0x3d0) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x3d0) + 8))();
    *(undefined8 *)(this + 0x3d0) = 0;
  }
  CItem::setVisible((CItem *)this,false,true);
  detachFromLocation(this);
  *(undefined8 *)(this + 0x60) = 0;
  destroyIcon(this);
  if (*(long **)(this + 0x1d8) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x1d8) + 8))();
    *(undefined8 *)(this + 0x1d8) = 0;
  }
  if (*(long **)(this + 0x250) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x250) + 8))();
    *(undefined8 *)(this + 0x250) = 0;
  }
  pCVar5 = *(CCollisionModel **)(this + 0x2c0);
  this_00 = (CMasterResourceManager *)CMasterResourceManager::getSingleton();
  CMasterResourceManager::removeCollisionModel(this_00,pCVar5);
  if (*(long **)(this + 0x2a0) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x2a0) + 8))();
    *(undefined8 *)(this + 0x2a0) = 0;
  }
  if (*(long **)(this + 0x2a8) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x2a8) + 8))();
    *(undefined8 *)(this + 0x2a8) = 0;
  }
  unloadModel(this);
  detachFromLocation(this);
  *(undefined8 *)(this + 0x240) = 0;
  *(undefined8 *)(this + 0x290) = 0;
  if (*(void **)(this + 0x410) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x410));
    *(undefined8 *)(this + 0x410) = 0;
  }
  paVar1 = (allocator *)(*(long *)(this + 0x400) + -0x18);
  if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0x400) + -8);
    iVar3 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar1);
    }
  }
  if (*(void **)(this + 1000) != (void *)0x0) {
    operator_delete__(*(void **)(this + 1000));
    *(undefined8 *)(this + 1000) = 0;
  }
  paVar1 = (allocator *)(*(long *)(this + 0x3d8) + -0x18);
  if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0x3d8) + -8);
    iVar3 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar1);
    }
  }
  if (*(void **)(this + 0x3b0) != (void *)0x0) {
    operator_delete(*(void **)(this + 0x3b0));
  }
  if (*(void **)(this + 0x398) != (void *)0x0) {
    operator_delete(*(void **)(this + 0x398));
  }
  if (*(void **)(this + 0x380) != (void *)0x0) {
    operator_delete(*(void **)(this + 0x380));
  }
  if (*(void **)(this + 0x368) != (void *)0x0) {
    operator_delete(*(void **)(this + 0x368));
  }
  if (*(void **)(this + 0x350) != (void *)0x0) {
    operator_delete(*(void **)(this + 0x350));
  }
  paVar1 = (allocator *)(*(long *)(this + 0x2e8) + -0x18);
  if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0x2e8) + -8);
    iVar3 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar1);
    }
  }
  paVar1 = (allocator *)(*(long *)(this + 0x2e0) + -0x18);
  if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0x2e0) + -8);
    iVar3 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar1);
    }
  }
  paVar1 = (allocator *)(*(long *)(this + 0x2d8) + -0x18);
  if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0x2d8) + -8);
    iVar3 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar1);
    }
  }
  paVar1 = (allocator *)(*(long *)(this + 0x2d0) + -0x18);
  if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0x2d0) + -8);
    iVar3 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar1);
    }
  }
  *(undefined ***)(this + 0x230) = &PTR__iMissile_00fce3f0;
  CItem::~CItem((CItem *)this);
  return;
}



/* address=0087dde0
   symbol=CEquipment::~CEquipment */

/* non-virtual thunk to CEquipment::~CEquipment() */

void __thiscall CEquipment::~CEquipment(CEquipment *this)

{
  ~CEquipment(this + -0x230);
  return;
}



/* address=0087ddf0
   symbol=CEquipment::~CEquipment */

/* non-virtual thunk to CEquipment::~CEquipment() */

void __thiscall CEquipment::~CEquipment(CEquipment *this)

{
  ~CEquipment(this + -0x230);
  return;
}



/* address=0087de00
   symbol=CEquipment::~CEquipment */

/* CEquipment::~CEquipment() */

void __thiscall CEquipment::~CEquipment(CEquipment *this)

{
  ~CEquipment(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}



/* address=0087de20
   symbol=CEquipment::convertEquipment */

/* WARNING: Removing unreachable block (ram,0x0087defe) */
/* CEquipment::convertEquipment(std::wstring) */

void __thiscall CEquipment::convertEquipment(CEquipment *this,wstring_conflict *param_2)

{
  int *piVar1;
  int iVar2;
  long lVar3;
  CUnitResourceList *this_00;
  long lVar4;
  long local_38;
  allocator local_29 [9];

  lVar3 = *(long *)(this + 0x1b0);
                    /* try { // try from 0087de57 to 0087de5b has its CatchHandler @ 0087def9 */
  std::wstring::wstring((wstring_conflict *)&local_38,L"ITEMS",local_29);
                    /* try { // try from 0087de60 to 0087de72 has its CatchHandler @ 0087dee6 */
  this_00 = (CUnitResourceList *)CResourceManager::getMasterResourceList();
  lVar4 = CUnitResourceList::getDataGroupByObjectName(this_00,(wstring_conflict *)&local_38,param_2)
  ;
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
  if (lVar4 != 0) {
    (**(code **)(*(long *)this + 0x1f0))(this,lVar4,lVar3 != 0);
  }
  return;
}



/* address=0087df10
   symbol=CEquipment::createNewEquipment */

/* WARNING: Removing unreachable block (ram,0x0087df89) */
/* CEquipment::createNewEquipment(std::wstring) */

void __thiscall CEquipment::createNewEquipment(CEquipment *this,wstring_conflict *param_2)

{
  int *piVar1;
  int iVar2;
  long local_28 [3];

  std::wstring::wstring((wstring_conflict *)local_28,param_2);
                    /* try { // try from 0087df2f to 0087df33 has its CatchHandler @ 0087df76 */
  convertEquipment(this,local_28);
  if ((allocator *)(local_28[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_28[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_28[0] + -0x18));
    }
  }
  return;
}



/* address=0087dfa0
   symbol=CEquipment::setGraphDamage */

/* WARNING: Removing unreachable block (ram,0x0087e0a9) */
/* CEquipment::setGraphDamage(unsigned int) */

void __thiscall CEquipment::setGraphDamage(CEquipment *this,uint param_1)

{
  int *piVar1;
  int iVar2;
  CGraphManager *this_00;
  CGraph *this_01;
  float fVar3;
  long local_28;
  allocator local_19;

                    /* try { // try from 0087dfcb to 0087dfcf has its CatchHandler @ 0087e0a4 */
  std::wstring::wstring((wstring_conflict *)&local_28,L"BASE_WEAPON_DAMAGE",&local_19);
                    /* try { // try from 0087dfd0 to 0087dfdf has its CatchHandler @ 0087e091 */
  this_00 = (CGraphManager *)CGraphManager::getSingleton();
  this_01 = (CGraph *)CGraphManager::getGraph(this_00,(wstring_conflict *)&local_28);
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
  fVar3 = (float)CGraph::getValue(this_01,(float)*(int *)(this + 0x274),0);
  iVar2 = 5;
  if (*(int *)(this + 0x28c) < 6) {
    iVar2 = *(int *)(this + 0x28c);
  }
  fVar3 = ceilf(fVar3 * ((float)(param_1 + iVar2 * 10) / DAT_00fa483c));
  iVar2 = (int)fVar3;
  *(int *)(this + 0x334) = iVar2;
  *(int *)(this + 0x330) = iVar2;
  *(int *)(this + 0x340) = iVar2;
  return;
}



/* address=0087e0c0
   symbol=CEquipment::setGraphAC */

/* WARNING: Removing unreachable block (ram,0x0087e1c1) */
/* CEquipment::setGraphAC(unsigned int) */

void __thiscall CEquipment::setGraphAC(CEquipment *this,uint param_1)

{
  int *piVar1;
  int iVar2;
  CGraphManager *this_00;
  CGraph *this_01;
  float fVar3;
  long local_28;
  allocator local_19;

                    /* try { // try from 0087e0e0 to 0087e0e4 has its CatchHandler @ 0087e1bc */
  std::wstring::wstring((wstring_conflict *)&local_28,L"ARMOR_PLAYER_BYLEVEL_FORSET",&local_19);
                    /* try { // try from 0087e0e5 to 0087e0f4 has its CatchHandler @ 0087e1a9 */
  this_00 = (CGraphManager *)CGraphManager::getSingleton();
  this_01 = (CGraph *)CGraphManager::getGraph(this_00,(wstring_conflict *)&local_28);
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
  iVar2 = 5;
  if (*(int *)(this + 0x28c) < 6) {
    iVar2 = *(int *)(this + 0x28c);
  }
  fVar3 = (float)CGraph::getValue(this_01,(float)*(int *)(this + 0x274),0);
  fVar3 = ceilf(fVar3 * ((float)(param_1 + iVar2 * 10) / DAT_00fa483c));
  iVar2 = (int)fVar3;
  *(int *)(this + 0x338) = iVar2;
  if (iVar2 < 1) {
    *(undefined4 *)(this + 0x338) = 1;
    iVar2 = 1;
  }
  *(int *)(this + 0x33c) = iVar2;
  return;
}



/* address=0087e1d0
   symbol=CEquipment::enchantPrice */

/* WARNING: Removing unreachable block (ram,0x0087e2b1) */
/* CEquipment::enchantPrice() */

int __thiscall CEquipment::enchantPrice(CEquipment *this)

{
  int *piVar1;
  int iVar2;
  CGraphManager *this_00;
  CGraph *this_01;
  long lVar3;
  float fVar4;
  long local_28;
  allocator local_19 [9];

                    /* try { // try from 0087e1eb to 0087e1ef has its CatchHandler @ 0087e2ac */
  std::wstring::wstring((wstring_conflict *)&local_28,L"PRICE_ENCHANT",local_19);
                    /* try { // try from 0087e1f0 to 0087e1ff has its CatchHandler @ 0087e299 */
  this_00 = (CGraphManager *)CGraphManager::getSingleton();
  this_01 = (CGraph *)CGraphManager::getGraph(this_00,(wstring_conflict *)&local_28);
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
  fVar4 = (float)CGraph::getValue(this_01,(float)*(int *)(this + 0x274),0);
  lVar3 = CGameGlobals::getSingleton();
  iVar2 = (int)(*(float *)(lVar3 + 0x6c) * fVar4 * (float)*(uint *)(this + 0x344)) + (int)fVar4;
  if (iVar2 < 300) {
    iVar2 = 300;
  }
  return iVar2;
}



/* address=0087e2c0
   symbol=CEquipment::setRimlight */

/* WARNING: Removing unreachable block (ram,0x0087e600) */
/* WARNING: Removing unreachable block (ram,0x0087e61c) */
/* WARNING: Removing unreachable block (ram,0x0087e60e) */
/* WARNING: Removing unreachable block (ram,0x0087e62a) */
/* WARNING: Removing unreachable block (ram,0x0087e5f2) */
/* WARNING: Removing unreachable block (ram,0x0087e5ba) */
/* CEquipment::setRimlight(std::wstring) */

void __thiscall CEquipment::setRimlight(CEquipment *this,wstring_conflict *param_2)

{
  int *piVar1;
  int iVar2;
  wstring_conflict *pwVar3;
  long local_78 [2];
  long local_68 [2];
  long local_58 [2];
  long local_48 [2];
  long local_38;
  allocator local_2a;
  allocator local_29;

  if (*(long *)(this + 0x1b0) != 0) {
    if (*(long *)(this + 0x2b0) != 0) {
      std::wstring::wstring((wstring_conflict *)&local_38,param_2);
                    /* try { // try from 0087e316 to 0087e31a has its CatchHandler @ 0087e5a7 */
      CGenericModel::setRimLighting(*(CGenericModel **)(this + 0x2b0),(wstring_conflict *)&local_38)
      ;
      if ((allocator *)(local_38 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
      {
        LOCK();
        piVar1 = (int *)(local_38 + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_38 + -0x18));
        }
      }
                    /* try { // try from 0087e345 to 0087e349 has its CatchHandler @ 0087e5c7 */
      std::wstring::wstring((wstring_conflict *)local_48,L"TEXTURE_OVERRIDE",&local_29);
                    /* try { // try from 0087e359 to 0087e36d has its CatchHandler @ 0087e5d2 */
      pwVar3 = (wstring_conflict *)
               CDataGroup::GetDataValue
                         (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_48,
                          (wstring_conflict *)&::EMPTY_WSTRING);
      std::wstring::wstring((wstring_conflict *)local_68,pwVar3);
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
      if (*(long *)(local_68[0] + -0x18) != 0) {
                    /* try { // try from 0087e48a to 0087e48e has its CatchHandler @ 0087e5cc */
        CGenericModel::setTextureOverride
                  (*(CGenericModel **)(this + 0x2b0),(wstring_conflict *)local_68);
      }
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
    }
    if (*(long *)(this + 0x2b8) != 0) {
      std::wstring::wstring((wstring_conflict *)local_58,param_2);
                    /* try { // try from 0087e3c5 to 0087e3c9 has its CatchHandler @ 0087e5c5 */
      CGenericModel::setRimLighting(*(CGenericModel **)(this + 0x2b8),(wstring_conflict *)local_58);
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
                    /* try { // try from 0087e3ef to 0087e3f3 has its CatchHandler @ 0087e5ec */
      std::wstring::wstring((wstring_conflict *)local_78,L"TEXTURE_OVERRIDE",&local_2a);
                    /* try { // try from 0087e403 to 0087e417 has its CatchHandler @ 0087e5df */
      pwVar3 = (wstring_conflict *)
               CDataGroup::GetDataValue
                         (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_78,
                          (wstring_conflict *)&::EMPTY_WSTRING);
      std::wstring::wstring((wstring_conflict *)local_68,pwVar3);
      if ((allocator *)(local_78[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_78[0] + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
        }
      }
      if (*(long *)(local_68[0] + -0x18) != 0) {
                    /* try { // try from 0087e443 to 0087e447 has its CatchHandler @ 0087e5ee */
        CGenericModel::setTextureOverride
                  (*(CGenericModel **)(this + 0x2b8),(wstring_conflict *)local_68);
      }
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
    }
  }
  return;
}



/* address=0087e640
   symbol=CEquipment::skillDescription */

/* WARNING: Removing unreachable block (ram,0x0087ef7c) */
/* WARNING: Removing unreachable block (ram,0x0087efa6) */
/* WARNING: Removing unreachable block (ram,0x0087f022) */
/* WARNING: Removing unreachable block (ram,0x0087ef6e) */
/* WARNING: Removing unreachable block (ram,0x0087efd0) */
/* WARNING: Removing unreachable block (ram,0x0087f105) */
/* WARNING: Removing unreachable block (ram,0x0087ef10) */
/* WARNING: Removing unreachable block (ram,0x0087efec) */
/* WARNING: Removing unreachable block (ram,0x0087ef8a) */
/* WARNING: Removing unreachable block (ram,0x0087efc2) */
/* WARNING: Removing unreachable block (ram,0x0087ef98) */
/* WARNING: Removing unreachable block (ram,0x0087eeab) */
/* WARNING: Removing unreachable block (ram,0x0087efb4) */
/* WARNING: Removing unreachable block (ram,0x0087effa) */
/* WARNING: Removing unreachable block (ram,0x0087efde) */
/* WARNING: Removing unreachable block (ram,0x0087ef60) */
/* CEquipment::skillDescription() */

wstring_conflict * CEquipment::skillDescription(void)

{
  int *piVar1;
  int iVar2;
  CDataGroup *this;
  uint uVar3;
  int iVar4;
  long *plVar5;
  long in_RSI;
  wstring_conflict *in_RDI;
  CSkillManager *pCVar6;
  long lVar7;
  uint uVar8;
  long local_178;
  void *local_168;
  undefined8 local_160;
  undefined8 local_158;
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
  allocator local_3d;
  allocator local_3c;
  allocator local_3b;
  allocator local_3a;
  allocator local_39 [9];

  if ((skillDescription()::g_Level == '\0') &&
     (iVar4 = __cxa_guard_acquire(&skillDescription()::g_Level), iVar4 != 0)) {
    skillDescription()::g_Level = &DAT_01424558;
    __cxa_guard_release(&skillDescription()::g_Level);
    __cxa_atexit(std::wstring::~wstring,&skillDescription()::g_Level,&__dso_handle);
  }
  if (*(long *)(skillDescription()::g_Level + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_58);
                    /* try { // try from 0087e699 to 0087e69d has its CatchHandler @ 0087ef4d */
    std::wstring::assign((wstring_conflict *)&skillDescription()::g_Level);
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
  std::wstring::wstring(in_RDI,(wstring_conflict *)&::EMPTY_WSTRING);
  local_168 = (void *)0x0;
  local_160 = 0;
  local_158 = 0;
                    /* try { // try from 0087e6f9 to 0087e6fd has its CatchHandler @ 0087ef1b */
  std::wstring::wstring((wstring_conflict *)local_68,L"SKILL_TO_GIVE",local_39);
                    /* try { // try from 0087e70d to 0087e711 has its CatchHandler @ 0087ef00 */
  uVar3 = CDataGroup::GetDataGroupsMatchingName
                    (*(CDataGroup **)(in_RSI + 0x1b0),(wstring_conflict *)local_68,
                     (vector *)&local_168);
  if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_68[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
    }
  }
  if (uVar3 != 0) {
    local_178 = 0;
    uVar8 = 0;
    do {
      this = *(CDataGroup **)((long)local_168 + local_178);
                    /* try { // try from 0087e76e to 0087e772 has its CatchHandler @ 0087eecf */
      std::wstring::wstring((wstring_conflict *)local_78,(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 0087e788 to 0087e78c has its CatchHandler @ 0087eecd */
      std::wstring::wstring((wstring_conflict *)local_88,L"NAME",&local_3a);
                    /* try { // try from 0087e79b to 0087e7aa has its CatchHandler @ 0087eebb */
      CDataGroup::GetDataValue(this,(wstring_conflict *)local_88,(wstring_conflict *)local_78);
      std::wstring::assign((wstring_conflict *)local_78);
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
                    /* try { // try from 0087e7d5 to 0087e7d9 has its CatchHandler @ 0087f057 */
      std::wstring::wstring((wstring_conflict *)local_98,L"DISPLAYNAME",&local_3b);
                    /* try { // try from 0087e7e8 to 0087e7f7 has its CatchHandler @ 0087f0b2 */
      CDataGroup::GetDataValue(this,(wstring_conflict *)local_98,(wstring_conflict *)local_78);
      std::wstring::assign((wstring_conflict *)local_78);
      if ((allocator *)(local_98[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_98[0] + -8);
        iVar4 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar4 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
        }
      }
                    /* try { // try from 0087e822 to 0087e826 has its CatchHandler @ 0087eeb6 */
      std::wstring::wstring((wstring_conflict *)local_a8,L"LEVEL",&local_3c);
                    /* try { // try from 0087e83b to 0087e83f has its CatchHandler @ 0087ee72 */
      iVar4 = CDataGroup::GetDataValue
                        (*(CDataGroup **)(in_RSI + 0x1b0),(wstring_conflict *)local_a8,1);
                    /* try { // try from 0087e858 to 0087e85c has its CatchHandler @ 0087f008 */
      std::wstring::wstring((wstring_conflict *)local_b8,L"LEVEL",&local_3d);
                    /* try { // try from 0087e86b to 0087e86f has its CatchHandler @ 0087f09d */
      iVar4 = CDataGroup::GetDataValue(this,(wstring_conflict *)local_b8,iVar4);
      if ((allocator *)(local_b8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_b8[0] + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
        }
      }
      if ((allocator *)(local_a8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_a8[0] + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
        }
      }
      if (uVar8 != 0) {
                    /* try { // try from 0087e8b2 to 0087e8b6 has its CatchHandler @ 0087f01d */
        std::wstring::wstring((wstring_conflict *)local_c8,in_RDI);
        wcslen(L"\n");
                    /* try { // try from 0087e8cc to 0087e8d0 has its CatchHandler @ 0087f00d */
        std::wstring::append((wchar_t *)local_c8,0xfd0b48);
                    /* try { // try from 0087e8d9 to 0087e8dd has its CatchHandler @ 0087f05c */
        std::wstring::assign(in_RDI);
        if ((allocator *)(local_c8[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_c8[0] + -8);
          iVar2 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar2 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
          }
        }
      }
                    /* try { // try from 0087e8fb to 0087e8ff has its CatchHandler @ 0087f01d */
      STRINGS::GetValueAsWString((STRINGS *)local_118,iVar4);
                    /* try { // try from 0087e910 to 0087e914 has its CatchHandler @ 0087f067 */
      std::operator+((wstring_conflict *)local_d8,in_RDI);
                    /* try { // try from 0087e928 to 0087e92c has its CatchHandler @ 0087f062 */
      std::wstring::wstring((wstring_conflict *)local_e8,(wstring_conflict *)local_d8);
      wcslen(L" ");
                    /* try { // try from 0087e942 to 0087e946 has its CatchHandler @ 0087f030 */
      std::wstring::append((wchar_t *)local_e8,0xfd0b98);
                    /* try { // try from 0087e957 to 0087e95b has its CatchHandler @ 0087f0d9 */
      std::operator+((wstring_conflict *)local_f8,(wstring_conflict *)local_e8);
                    /* try { // try from 0087e96f to 0087e973 has its CatchHandler @ 0087f0d4 */
      std::wstring::wstring((wstring_conflict *)local_108,(wstring_conflict *)local_f8);
      wcslen(L": ");
                    /* try { // try from 0087e989 to 0087e98d has its CatchHandler @ 0087f0c7 */
      std::wstring::append((wchar_t *)local_108,0xfd0b84);
                    /* try { // try from 0087e99b to 0087e99f has its CatchHandler @ 0087f098 */
      std::operator+((wstring_conflict *)local_128,(wstring_conflict *)local_108);
                    /* try { // try from 0087e9aa to 0087e9ae has its CatchHandler @ 0087f06c */
      std::wstring::assign(in_RDI);
      if ((allocator *)(local_128[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_128[0] + -8);
        iVar4 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar4 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_128[0] + -0x18));
        }
      }
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
      if ((allocator *)(local_118[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_118[0] + -8);
        iVar4 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar4 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_118[0] + -0x18));
        }
      }
      if ((allocator *)(local_78[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_78[0] + -8);
        iVar4 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar4 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
        }
      }
      uVar8 = uVar8 + 1;
      local_178 = local_178 + 8;
    } while (uVar8 < uVar3);
  }
  pCVar6 = *(CSkillManager **)(in_RSI + 0x1c8);
  if (pCVar6 != (CSkillManager *)0x0) {
                    /* try { // try from 0087eb3f to 0087eb43 has its CatchHandler @ 0087eecf */
    for (uVar3 = 0; uVar8 = CSkillManager::knownSkills(pCVar6,0), uVar3 < uVar8; uVar3 = uVar3 + 1)
    {
      pCVar6 = *(CSkillManager **)(in_RSI + 0x1c8);
      if (((int)uVar3 < *(int *)(pCVar6 + 0x68)) && (uVar3 != 0xffffffff)) {
        if (uVar3 < *(uint *)(pCVar6 + 0x6c)) {
          plVar5 = (long *)((ulong)uVar3 * 8 + *(long *)(pCVar6 + 0x60));
        }
        else {
          plVar5 = *(long **)(pCVar6 + 0x60);
        }
        lVar7 = *plVar5;
      }
      else {
        lVar7 = 0;
      }
      if (((*(byte *)(lVar7 + 0x6d) & (*(byte *)(lVar7 + 0x6b) ^ 1)) != 0) && (lVar7 != 0)) {
        if (uVar3 != 0) {
                    /* try { // try from 0087eabd to 0087eac1 has its CatchHandler @ 0087eecf */
          std::wstring::wstring((wstring_conflict *)local_138,in_RDI);
          wcslen(L"\n");
                    /* try { // try from 0087ead7 to 0087eadb has its CatchHandler @ 0087f0f2 */
          std::wstring::append((wchar_t *)local_138,0xfd0b48);
                    /* try { // try from 0087eae4 to 0087eae8 has its CatchHandler @ 0087f0e2 */
          std::wstring::assign(in_RDI);
          if ((allocator *)(local_138[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_138[0] + -8);
            iVar4 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar4 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_138[0] + -0x18));
            }
          }
        }
                    /* try { // try from 0087eb0f to 0087eb13 has its CatchHandler @ 0087eecf */
        CSkill::getDescription((CBaseUnit *)local_148,(uint)lVar7,SUB81(in_RSI,0));
                    /* try { // try from 0087eb1c to 0087eb20 has its CatchHandler @ 0087f0f4 */
        std::wstring::append(in_RDI);
        if ((allocator *)(local_148[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_148[0] + -8);
          iVar4 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar4 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_148[0] + -0x18));
          }
        }
        pCVar6 = *(CSkillManager **)(in_RSI + 0x1c8);
      }
    }
  }
  if (local_168 != (void *)0x0) {
    operator_delete(local_168);
  }
  return in_RDI;
}



/* address=0087f120
   symbol=CEquipment::fireMissiles */

/* WARNING: Removing unreachable block (ram,0x0087f86e) */
/* CEquipment::fireMissiles(CCharacter*, CCharacter*) */

undefined8 CEquipment::fireMissiles(CCharacter *param_1,CCharacter *param_2)

{
  long *plVar1;
  int *piVar2;
  int iVar3;
  CResourceManager *pCVar4;
  undefined4 uVar5;
  uint uVar6;
  CCharacter *pCVar7;
  float *pfVar8;
  long lVar9;
  CMissilePreloader *this;
  CRunicCore *this_00;
  TSafePointer *pTVar10;
  void *pvVar11;
  long *plVar12;
  CPositionableObject *in_RDX;
  long *plVar13;
  ulong uVar14;
  uint uVar15;
  undefined8 uVar16;
  float in_XMM1_Da;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float local_cc;
  float local_c8;
  float local_c4;
  float local_c0;
  float local_bc;
  Vector3 local_a8 [16];
  undefined8 local_98;
  float local_90;
  float local_88;
  float local_84;
  float local_80;
  undefined8 local_78;
  undefined8 local_68;
  float local_60;
  float local_58;
  float fStack_54;
  float local_50;
  long local_48;
  allocator local_39 [9];

  if ((*(long *)(*(long *)(param_1 + 0x400) + -0x18) == 0) || (param_2 == (CCharacter *)0x0)) {
    return 0;
  }
  pCVar7 = (CCharacter *)CCharacter::getWeaponInLeftHand(param_2);
  if (param_1 == pCVar7) {
    pfVar8 = (float *)(**(code **)(**(long **)(param_2 + 0x2f8) + 0x200))();
    local_cc = *pfVar8;
    local_bc = pfVar8[1];
    local_c0 = pfVar8[2];
  }
  else {
    pfVar8 = (float *)(**(code **)(**(long **)(param_2 + 0x2e8) + 0x200))();
    local_cc = *pfVar8;
    local_bc = pfVar8[1];
    local_c0 = pfVar8[2];
  }
  local_68 = (**(code **)(*(long *)param_2 + 0x138))(param_2);
  fVar17 = in_XMM1_Da;
  local_60 = in_XMM1_Da;
  if (in_RDX != (CPositionableObject *)0x0) {
    uVar16 = CPositionableObject::getPosition(in_RDX,true);
    local_78._4_4_ = (float)((ulong)uVar16 >> 0x20);
    local_78._0_4_ = (float)uVar16;
    fVar17 = local_78._4_4_ - local_bc;
    fVar19 = (float)local_78 - local_cc;
    local_60 = in_XMM1_Da - local_c0;
    local_68 = CONCAT44(fVar17,fVar19);
    fVar20 = SQRT(fVar19 * fVar19 + fVar17 * fVar17 + local_60 * local_60);
    local_78 = uVar16;
    if (DAT_00fa87a0 < (double)fVar20) {
      fVar20 = DAT_00fa47fc / fVar20;
      fVar17 = fVar17 * fVar20;
      local_60 = local_60 * fVar20;
      local_68 = CONCAT44(fVar17,fVar19 * fVar20);
    }
  }
                    /* try { // try from 0087f2c0 to 0087f2c4 has its CatchHandler @ 0087f81c */
  std::wstring::wstring((wstring_conflict *)&local_48,L"WEAPON_SCALE",local_39);
                    /* try { // try from 0087f2d7 to 0087f2db has its CatchHandler @ 0087f834 */
  fVar19 = (float)CDataGroup::GetDataValue
                            (*(CDataGroup **)(param_2 + 0x1b0),(wstring_conflict *)&local_48,
                             DAT_00fa47fc);
  if ((allocator *)(local_48 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(local_48 + -8);
    iVar3 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_48 + -0x18));
    }
  }
  lVar9 = (**(code **)(*(long *)param_1 + 0x1e0))(param_1);
  if (lVar9 == 0) {
    fVar20 = local_60;
    local_c8 = local_68._4_4_;
    local_c4 = (float)local_68;
  }
  else {
    lVar9 = (**(code **)(*(long *)param_1 + 0x1e0))(param_1);
    lVar9 = (**(code **)(**(long **)(lVar9 + 0x60) + 0xd8))();
    if (*(int *)(lVar9 + 0x18) == 1) {
      fVar18 = *(float *)(lVar9 + 0x10) - *(float *)(lVar9 + 4);
    }
    else {
      fVar18 = Ogre::Math::POS_INFINITY;
      if (*(int *)(lVar9 + 0x18) != 2) {
        fVar18 = DAT_014241b0;
      }
    }
    fVar19 = fVar19 * DAT_00fc676c;
    fVar17 = fVar18 * local_60;
    fVar20 = fVar19 * fVar17;
    local_c8 = local_68._4_4_ * fVar18 * fVar19;
    local_c4 = (float)local_68 * fVar18 * fVar19;
  }
  local_c4 = local_c4 + local_cc;
  local_c8 = local_bc + local_c8;
  local_cc = local_c0 + fVar20;
  pCVar4 = *(CResourceManager **)(param_1 + 0x68);
  this = (CMissilePreloader *)CResourceManager::getMissilePreloader();
  this_00 = (CRunicCore *)
            CMissilePreloader::createNewMissileRef
                      (this,pCVar4,(wstring_conflict *)(param_1 + 0x400));
  if (this_00 == (CRunicCore *)0x0) {
    return 0;
  }
  uVar15 = *(uint *)(this_00 + 0x1d0);
  pCVar7 = param_1 + 0x230;
  if (uVar15 == 0) {
    plVar12 = *(long **)(this_00 + 0x1c8);
  }
  else {
    plVar12 = *(long **)(this_00 + 0x1c8);
    uVar6 = 0;
    plVar13 = plVar12;
    if (pCVar7 == (CCharacter *)*plVar12) goto joined_r0x0087f44b;
    do {
      uVar6 = uVar6 + 1;
      if (uVar15 <= uVar6) goto LAB_0087f428;
      plVar1 = plVar13 + 1;
      plVar13 = plVar13 + 1;
    } while (pCVar7 != (CCharacter *)*plVar1);
    if (uVar6 != 0xffffffff) goto joined_r0x0087f44b;
  }
LAB_0087f428:
  if (*(uint *)(this_00 + 0x1d4) <= uVar15) {
    if (plVar12 == (long *)0x0) {
      *(uint *)(this_00 + 0x1d4) = *(uint *)(this_00 + 0x1d8);
      plVar12 = operator_new__((ulong)*(uint *)(this_00 + 0x1d8) << 3);
      uVar15 = *(uint *)(this_00 + 0x1d0);
      *(long **)(this_00 + 0x1c8) = plVar12;
    }
    else {
      uVar15 = *(uint *)(this_00 + 0x1d4) + *(int *)(this_00 + 0x1d8);
      plVar12 = operator_new__((ulong)uVar15 << 3);
      if (*(int *)(this_00 + 0x1d4) != 0) {
        uVar6 = 0;
        do {
          uVar14 = (ulong)uVar6;
          uVar6 = uVar6 + 1;
          plVar12[uVar14] = *(long *)(*(long *)(this_00 + 0x1c8) + uVar14 * 8);
        } while (uVar6 < *(uint *)(this_00 + 0x1d4));
      }
      if (*(void **)(this_00 + 0x1c8) != (void *)0x0) {
        operator_delete__(*(void **)(this_00 + 0x1c8));
      }
      *(long **)(this_00 + 0x1c8) = plVar12;
      *(uint *)(this_00 + 0x1d4) = uVar15;
      uVar15 = *(uint *)(this_00 + 0x1d0);
    }
  }
  plVar12[uVar15] = (long)pCVar7;
  *(int *)(this_00 + 0x1d0) = *(int *)(this_00 + 0x1d0) + 1;
joined_r0x0087f44b:
  if (in_RDX == (CPositionableObject *)0x0) {
    local_98 = CONCAT44(DAT_014241b0,Ogre::Vector3::ZERO);
    local_90 = DAT_014241b4;
  }
  else {
    local_98 = CPositionableObject::getPosition(in_RDX,true);
    local_90 = fVar17;
  }
  local_80 = Ogre::Vector3::UNIT_Y * local_68._4_4_ - DAT_01424b38 * (float)local_68;
  local_84 = (float)local_68 * DAT_01424b3c - Ogre::Vector3::UNIT_Y * local_60;
  local_88 = local_60 * DAT_01424b38 - DAT_01424b3c * local_68._4_4_;
  Ogre::Quaternion::FromAxes(local_a8,(Vector3 *)&local_88,(Vector3 *)&Ogre::Vector3::UNIT_Y);
  uVar16 = (**(code **)(*(long *)param_1 + 0x340))(param_1);
  local_50 = local_cc;
  local_58 = local_c4;
  fStack_54 = local_c8;
  CMissile::fireMissile
            (CONCAT44(local_c8,local_c4),local_cc,local_98,local_90,this_00,uVar16,local_a8);
  pTVar10 = (TSafePointer *)Ogre::NedAllocImpl::allocBytes(0x10,(char *)0x0,0,(char *)0x0);
  *(undefined4 *)(pTVar10 + 8) = 0xffffffff;
  *(undefined8 *)pTVar10 = 0;
                    /* try { // try from 0087f59b to 0087f59f has its CatchHandler @ 0087f827 */
  uVar5 = CRunicCore::addSafePointer(this_00,pTVar10);
  *(undefined4 *)(pTVar10 + 8) = uVar5;
  *(CRunicCore **)pTVar10 = this_00;
  uVar15 = *(uint *)(param_1 + 0x418);
  if (uVar15 < *(uint *)(param_1 + 0x41c)) {
    pvVar11 = *(void **)(param_1 + 0x410);
  }
  else if (*(long *)(param_1 + 0x410) == 0) {
    *(uint *)(param_1 + 0x41c) = *(uint *)(param_1 + 0x420);
    pvVar11 = operator_new__((ulong)*(uint *)(param_1 + 0x420) * 8);
    *(void **)(param_1 + 0x410) = pvVar11;
    uVar15 = *(uint *)(param_1 + 0x418);
  }
  else {
    uVar15 = *(uint *)(param_1 + 0x41c) + *(int *)(param_1 + 0x420);
    pvVar11 = operator_new__((ulong)uVar15 << 3);
    if (*(int *)(param_1 + 0x41c) != 0) {
      uVar6 = 0;
      do {
        uVar14 = (ulong)uVar6;
        uVar6 = uVar6 + 1;
        *(undefined8 *)((long)pvVar11 + uVar14 * 8) =
             *(undefined8 *)(*(long *)(param_1 + 0x410) + uVar14 * 8);
      } while (uVar6 < *(uint *)(param_1 + 0x41c));
    }
    if (*(void **)(param_1 + 0x410) != (void *)0x0) {
      operator_delete__(*(void **)(param_1 + 0x410));
    }
    *(void **)(param_1 + 0x410) = pvVar11;
    *(uint *)(param_1 + 0x41c) = uVar15;
    uVar15 = *(uint *)(param_1 + 0x418);
  }
  *(TSafePointer **)((long)pvVar11 + (ulong)uVar15 * 8) = pTVar10;
  *(int *)(param_1 + 0x418) = *(int *)(param_1 + 0x418) + 1;
  return 1;
}



/* address=0087f880
   symbol=CEquipment::getMaxSockets */

/* WARNING: Removing unreachable block (ram,0x0087f946) */
/* CEquipment::getMaxSockets() */

ulong __thiscall CEquipment::getMaxSockets(CEquipment *this)

{
  int *piVar1;
  int iVar2;
  ulong uVar3;
  long local_28;
  allocator local_19;

  if (*(long *)(this + 0x1b0) == 0) {
    uVar3 = 0;
  }
  else {
                    /* try { // try from 0087f8b5 to 0087f8d3 has its CatchHandler @ 0087f92e */
    std::wstring::wstring((wstring_conflict *)&local_28,L"MAX_SOCKETS",&local_19);
    uVar3 = CDataGroup::GetDataValue(*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)&local_28,2)
    ;
    if ((allocator *)(local_28 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_28 + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_28 + -0x18));
        uVar3 = uVar3 & 0xffffffff;
      }
    }
  }
  return uVar3;
}



/* address=0087f960
   symbol=CEquipment::addSockets */

/* CEquipment::addSockets() */

void __thiscall CEquipment::addSockets(CEquipment *this)

{
  int iVar1;
  char cVar2;
  int iVar3;
  long lVar4;
  float fVar5;

  iVar3 = getMaxSockets(this);
  if ((((*(int *)(this + 0x3e0) < iVar3) && (*(long *)(this + 0x68) != 0)) &&
      (*(long *)(*(long *)(this + 0x68) + 0x18) != 0)) &&
     (((cVar2 = CBaseUnit::ISA((CBaseUnit *)this,8), cVar2 != '\0' ||
       (cVar2 = CBaseUnit::ISA((CBaseUnit *)this,0xd), cVar2 != '\0')) ||
      ((cVar2 = CBaseUnit::ISA((CBaseUnit *)this,0x11), cVar2 != '\0' ||
       (cVar2 = CBaseUnit::ISA((CBaseUnit *)this,0x18), cVar2 != '\0')))))) {
    iVar1 = *(int *)(this + 0x3e0);
    if (iVar1 < iVar3 + -1) {
      fVar5 = (float)UTILITIES::randomBetweenVolatile(0.0,DAT_00fa871c);
      lVar4 = CGameGlobals::getSingleton();
      iVar3 = iVar1 + 1;
      if (fVar5 < DAT_00fa86e0 * *(float *)(lVar4 + 0x2c)) {
        iVar3 = iVar1 + 2;
      }
      *(int *)(this + 0x3e0) = iVar3;
    }
    else {
      *(int *)(this + 0x3e0) = iVar1 + 1;
    }
  }
  return;
}



/* address=0087fa70
   symbol=CEquipment::isWardrobed */

/* WARNING: Removing unreachable block (ram,0x0087ff06) */
/* WARNING: Removing unreachable block (ram,0x0087ffd7) */
/* WARNING: Removing unreachable block (ram,0x0087ffc9) */
/* WARNING: Removing unreachable block (ram,0x0087ffbe) */
/* WARNING: Removing unreachable block (ram,0x0087ff62) */
/* WARNING: Removing unreachable block (ram,0x0087fe64) */
/* WARNING: Removing unreachable block (ram,0x00880016) */
/* WARNING: Removing unreachable block (ram,0x0087fe72) */
/* WARNING: Removing unreachable block (ram,0x00880024) */
/* CEquipment::isWardrobed(std::wstring) */

undefined8 __thiscall CEquipment::isWardrobed(CEquipment *this,wstring_conflict *param_2)

{
  allocator *paVar1;
  int *piVar2;
  wchar_t *pwVar3;
  wchar_t wVar4;
  size_t sVar5;
  CDataGroup *this_00;
  bool bVar6;
  uint uVar7;
  int iVar8;
  undefined8 *puVar9;
  wstring_conflict *pwVar10;
  allocator *paVar11;
  long lVar12;
  undefined8 uVar13;
  uint uVar14;
  void *local_e8;
  undefined8 local_e0;
  undefined8 local_d8;
  long local_c8 [2];
  long local_b8 [2];
  long local_a8 [2];
  wchar_t *local_98 [2];
  long local_88 [2];
  long local_78 [2];
  long local_68 [2];
  long local_58 [3];
  allocator local_3c;
  allocator local_3b;
  allocator local_3a;
  allocator local_39 [9];

  STRINGS::StringUpper((STRINGS *)local_58,param_2);
                    /* try { // try from 0087fa9d to 0087faa1 has its CatchHandler @ 0087ff9b */
  std::wstring::assign(param_2);
  if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_58[0] + -8);
    iVar8 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar8 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
    }
  }
  local_e8 = (void *)0x0;
  local_e0 = 0;
  local_d8 = 0;
                    /* try { // try from 0087faf0 to 0087faf4 has its CatchHandler @ 0087ff6d */
  std::wstring::wstring((wstring_conflict *)local_68,L"WARDROBE",local_39);
                    /* try { // try from 0087fb04 to 0087fb08 has its CatchHandler @ 0087ff54 */
  uVar7 = CDataGroup::GetDataGroupsMatchingName
                    (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_68,(vector *)&local_e8
                    );
  if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_68[0] + -8);
    iVar8 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar8 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
    }
  }
                    /* try { // try from 0087fb2f to 0087fb33 has its CatchHandler @ 0087ff23 */
  std::wstring::wstring((wstring_conflict *)local_78,(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 0087fb3e to 0087fb42 has its CatchHandler @ 0087ff1e */
  std::wstring::wstring((wstring_conflict *)local_88,(wstring_conflict *)&::EMPTY_WSTRING);
  if (uVar7 != 0) {
    lVar12 = 0;
    uVar14 = 0;
    do {
      this_00 = *(CDataGroup **)((long)local_e8 + lVar12);
                    /* try { // try from 0087fc0d to 0087fc11 has its CatchHandler @ 0087ff19 */
      std::wstring::wstring((wstring_conflict *)local_a8,L"CLASS",&local_3a);
                    /* try { // try from 0087fc1d to 0087fc2e has its CatchHandler @ 0087ffae */
      pwVar10 = (wstring_conflict *)
                CDataGroup::GetDataValue(this_00,(wstring_conflict *)local_a8,L"");
      STRINGS::StringUpper((STRINGS *)local_98,pwVar10);
      if ((allocator *)(local_a8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_a8[0] + -8);
        iVar8 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar8 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
        }
      }
                    /* try { // try from 0087fc49 to 0087fc4d has its CatchHandler @ 0087ff14 */
      iVar8 = std::wstring::compare((wchar_t *)param_2);
      if (iVar8 == 0) {
LAB_0087fb60:
                    /* try { // try from 0087fb7c to 0087fb97 has its CatchHandler @ 0087fea9 */
        std::wstring::wstring((wstring_conflict *)local_b8,L"MESH",&local_3b);
        puVar9 = (undefined8 *)
                 CDataGroup::GetDataValue
                           (this_00,(wstring_conflict *)local_b8,
                            (wstring_conflict *)&::EMPTY_WSTRING);
        sVar5 = *(size_t *)((wchar_t *)*puVar9 + -6);
        if ((sVar5 == *(size_t *)(::EMPTY_WSTRING + -6)) &&
           (iVar8 = wmemcmp((wchar_t *)*puVar9,::EMPTY_WSTRING,sVar5), iVar8 == 0)) {
                    /* try { // try from 0087fcaf to 0087fcca has its CatchHandler @ 0087fea9 */
          std::wstring::wstring((wstring_conflict *)local_c8,L"TEXTURE",&local_3c);
          puVar9 = (undefined8 *)
                   CDataGroup::GetDataValue
                             (this_00,(wstring_conflict *)local_c8,
                              (wstring_conflict *)&::EMPTY_WSTRING);
          sVar5 = *(size_t *)((wchar_t *)*puVar9 + -6);
          if (sVar5 == *(size_t *)(::EMPTY_WSTRING + -6)) {
            iVar8 = wmemcmp((wchar_t *)*puVar9,::EMPTY_WSTRING,sVar5);
            bVar6 = false;
            if (iVar8 != 0) goto LAB_0087fcdf;
          }
          else {
LAB_0087fcdf:
            bVar6 = true;
          }
          if ((allocator *)(local_c8[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_c8[0] + -8);
            iVar8 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar8 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
            }
          }
        }
        else {
          bVar6 = true;
        }
        if ((allocator *)(local_b8[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar2 = (int *)(local_b8[0] + -8);
          iVar8 = *piVar2;
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (iVar8 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
          }
        }
        if (bVar6) {
          if ((allocator *)(local_98[0] + -6) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            pwVar3 = local_98[0] + -2;
            wVar4 = *pwVar3;
            *pwVar3 = *pwVar3 + L'\xffffffff';
            UNLOCK();
            if (wVar4 < L'\x01') {
              uVar13 = 1;
              std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -6));
              goto LAB_0087fd42;
            }
          }
          uVar13 = 1;
          goto LAB_0087fd42;
        }
        paVar11 = (allocator *)(local_98[0] + -6);
      }
      else {
        paVar11 = (allocator *)(local_98[0] + -6);
        if ((*(size_t *)(local_98[0] + -6) == *(size_t *)(*(wchar_t **)param_2 + -6)) &&
           (iVar8 = wmemcmp(local_98[0],*(wchar_t **)param_2,*(size_t *)(local_98[0] + -6)),
           iVar8 == 0)) goto LAB_0087fb60;
      }
      if (paVar11 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        paVar1 = paVar11 + 0x10;
        iVar8 = *(int *)paVar1;
        *(int *)paVar1 = *(int *)paVar1 + -1;
        UNLOCK();
        if (iVar8 < 1) {
          std::wstring::_Rep::_M_destroy(paVar11);
        }
      }
      uVar14 = uVar14 + 1;
      lVar12 = lVar12 + 8;
    } while (uVar14 < uVar7);
  }
  uVar13 = 0;
LAB_0087fd42:
  if ((allocator *)(local_88[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_88[0] + -8);
    iVar8 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar8 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
    }
  }
  if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_78[0] + -8);
    iVar8 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar8 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
    }
  }
  if (local_e8 != (void *)0x0) {
    operator_delete(local_e8);
  }
  return uVar13;
}



/* address=00880030
   symbol=CEquipment::setRequirements */

/* WARNING: Removing unreachable block (ram,0x00880866) */
/* WARNING: Removing unreachable block (ram,0x00880933) */
/* WARNING: Removing unreachable block (ram,0x00880816) */
/* WARNING: Removing unreachable block (ram,0x00880808) */
/* WARNING: Removing unreachable block (ram,0x00880915) */
/* WARNING: Removing unreachable block (ram,0x00880941) */
/* WARNING: Removing unreachable block (ram,0x0088083c) */
/* WARNING: Removing unreachable block (ram,0x00880858) */
/* WARNING: Removing unreachable block (ram,0x0088084a) */
/* WARNING: Removing unreachable block (ram,0x00880925) */
/* CEquipment::setRequirements() */

void __thiscall CEquipment::setRequirements(CEquipment *this)

{
  int *piVar1;
  char cVar2;
  undefined4 uVar3;
  int iVar4;
  CGraphManager *pCVar5;
  CGraph *pCVar6;
  int iVar7;
  float fVar8;
  long local_d8 [2];
  long local_c8 [2];
  long local_b8 [2];
  long local_a8 [2];
  long local_98 [2];
  long local_88 [2];
  long local_78 [2];
  long local_68 [2];
  long local_58 [2];
  long local_48 [2];
  allocator local_32;
  allocator local_31;
  allocator local_30;
  allocator local_2f;
  allocator local_2e;
  allocator local_2d;
  allocator local_2c;
  allocator local_2b;
  allocator local_2a;
  allocator local_29 [9];

                    /* try { // try from 00880058 to 0088005c has its CatchHandler @ 0088089f */
  std::wstring::wstring((wstring_conflict *)local_48,L"LEVEL_REQUIRED",local_29);
                    /* try { // try from 00880069 to 0088006d has its CatchHandler @ 00880892 */
  uVar3 = CDataGroup::GetDataValue(*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_48,0);
  *(undefined4 *)(this + 0x278) = uVar3;
  if ((allocator *)(local_48[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_48[0] + -8);
    iVar7 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar7 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
    }
  }
  iVar7 = 5;
  if (*(int *)(this + 0x28c) < 6) {
    iVar7 = *(int *)(this + 0x28c);
  }
  if ((*(int *)(this + 0x278) == 0) &&
     (((cVar2 = CBaseUnit::ISA((CBaseUnit *)this,8), cVar2 != '\0' ||
       (cVar2 = CBaseUnit::ISA((CBaseUnit *)this,0xd), cVar2 != '\0')) ||
      (cVar2 = CBaseUnit::ISA((CBaseUnit *)this,0x27), cVar2 != '\0')))) {
                    /* try { // try from 0088023d to 00880241 has its CatchHandler @ 008808b7 */
    std::wstring::wstring((wstring_conflict *)local_58,L"ITEM_LEVEL_REQUIREMENTS",&local_2a);
                    /* try { // try from 00880242 to 00880251 has its CatchHandler @ 008808c5 */
    pCVar5 = (CGraphManager *)CGraphManager::getSingleton();
    pCVar6 = (CGraph *)CGraphManager::getGraph(pCVar5,(wstring_conflict *)local_58);
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
    fVar8 = (float)CGraph::getValue(pCVar6,(float)*(int *)(this + 0x274),0);
    fVar8 = floorf(fVar8);
    iVar4 = 0;
    if (1 < (int)fVar8 - iVar7) {
      iVar4 = (int)fVar8 - iVar7;
    }
    *(int *)(this + 0x278) = iVar4;
  }
  iVar7 = 10;
  if (*(int *)(this + 0x28c) < 0xb) {
    iVar7 = *(int *)(this + 0x28c);
  }
                    /* try { // try from 008800de to 008800e2 has its CatchHandler @ 008808e5 */
  std::wstring::wstring((wstring_conflict *)local_68,L"STRENGTH_REQUIRED",&local_2b);
                    /* try { // try from 008800ef to 008800f3 has its CatchHandler @ 008808d5 */
  iVar4 = CDataGroup::GetDataValue(*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_68,0);
  *(int *)(this + 0x27c) = iVar4;
  if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_68[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
    }
    iVar4 = *(int *)(this + 0x27c);
  }
  if ((iVar4 != 0) &&
     ((cVar2 = CBaseUnit::ISA((CBaseUnit *)this,8), cVar2 != '\0' ||
      (cVar2 = CBaseUnit::ISA((CBaseUnit *)this,0xd), cVar2 != '\0')))) {
                    /* try { // try from 008804aa to 008804ae has its CatchHandler @ 008808a2 */
    std::wstring::wstring((wstring_conflict *)local_78,L"ITEM_STRENGTH_REQUIREMENTS",&local_2c);
                    /* try { // try from 008804af to 008804be has its CatchHandler @ 008808a4 */
    pCVar5 = (CGraphManager *)CGraphManager::getSingleton();
    pCVar6 = (CGraph *)CGraphManager::getGraph(pCVar5,(wstring_conflict *)local_78);
    if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_78[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
      }
    }
    fVar8 = (float)CGraph::getValue(pCVar6,(float)*(int *)(this + 0x274),0);
    fVar8 = floorf((fVar8 * (float)*(int *)(this + 0x27c)) / DAT_00fa483c);
    iVar4 = 0;
    if (1 < (int)fVar8 - iVar7) {
      iVar4 = (int)fVar8 - iVar7;
    }
    *(int *)(this + 0x27c) = iVar4;
  }
                    /* try { // try from 0088012c to 00880130 has its CatchHandler @ 00880905 */
  std::wstring::wstring((wstring_conflict *)local_88,L"DEXTERITY_REQUIRED",&local_2d);
                    /* try { // try from 0088013d to 00880141 has its CatchHandler @ 008808f5 */
  iVar4 = CDataGroup::GetDataValue(*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_88,0);
  *(int *)(this + 0x280) = iVar4;
  if ((allocator *)(local_88[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_88[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
    }
    iVar4 = *(int *)(this + 0x280);
  }
  if ((iVar4 != 0) &&
     ((cVar2 = CBaseUnit::ISA((CBaseUnit *)this,8), cVar2 != '\0' ||
      (cVar2 = CBaseUnit::ISA((CBaseUnit *)this,0xd), cVar2 != '\0')))) {
                    /* try { // try from 0088040a to 0088040e has its CatchHandler @ 00880884 */
    std::wstring::wstring((wstring_conflict *)local_98,L"ITEM_DEXTERITY_REQUIREMENTS",&local_2e);
                    /* try { // try from 0088040f to 0088041e has its CatchHandler @ 00880886 */
    pCVar5 = (CGraphManager *)CGraphManager::getSingleton();
    pCVar6 = (CGraph *)CGraphManager::getGraph(pCVar5,(wstring_conflict *)local_98);
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
    fVar8 = (float)CGraph::getValue(pCVar6,(float)*(int *)(this + 0x274),0);
    fVar8 = floorf((fVar8 * (float)*(int *)(this + 0x280)) / DAT_00fa483c);
    iVar4 = 0;
    if (1 < (int)fVar8 - iVar7) {
      iVar4 = (int)fVar8 - iVar7;
    }
    *(int *)(this + 0x280) = iVar4;
  }
                    /* try { // try from 00880177 to 0088017b has its CatchHandler @ 00880876 */
  std::wstring::wstring((wstring_conflict *)local_a8,L"MAGIC_REQUIRED",&local_2f);
                    /* try { // try from 00880188 to 0088018c has its CatchHandler @ 00880874 */
  iVar4 = CDataGroup::GetDataValue(*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_a8,0);
  *(int *)(this + 0x284) = iVar4;
  if ((allocator *)(local_a8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_a8[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
    }
    iVar4 = *(int *)(this + 0x284);
  }
  if ((iVar4 != 0) &&
     ((cVar2 = CBaseUnit::ISA((CBaseUnit *)this,8), cVar2 != '\0' ||
      (cVar2 = CBaseUnit::ISA((CBaseUnit *)this,0xd), cVar2 != '\0')))) {
                    /* try { // try from 0088036a to 0088036e has its CatchHandler @ 00880878 */
    std::wstring::wstring((wstring_conflict *)local_b8,L"ITEM_MAGIC_REQUIREMENTS",&local_30);
                    /* try { // try from 0088036f to 0088037e has its CatchHandler @ 00880882 */
    pCVar5 = (CGraphManager *)CGraphManager::getSingleton();
    pCVar6 = (CGraph *)CGraphManager::getGraph(pCVar5,(wstring_conflict *)local_b8);
    if ((allocator *)(local_b8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_b8[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
      }
    }
    fVar8 = (float)CGraph::getValue(pCVar6,(float)*(int *)(this + 0x274),0);
    fVar8 = floorf((fVar8 * (float)*(int *)(this + 0x284)) / DAT_00fa483c);
    iVar4 = 0;
    if (1 < (int)fVar8 - iVar7) {
      iVar4 = (int)fVar8 - iVar7;
    }
    *(int *)(this + 0x284) = iVar4;
  }
                    /* try { // try from 008801c2 to 008801c6 has its CatchHandler @ 00880837 */
  std::wstring::wstring((wstring_conflict *)local_c8,L"DEFENSE_REQUIRED",&local_31);
                    /* try { // try from 008801d3 to 008801d7 has its CatchHandler @ 00880824 */
  iVar4 = CDataGroup::GetDataValue(*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_c8,0);
  *(int *)(this + 0x288) = iVar4;
  if ((allocator *)(local_c8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_c8[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
    }
    iVar4 = *(int *)(this + 0x288);
  }
  if ((iVar4 != 0) &&
     ((cVar2 = CBaseUnit::ISA((CBaseUnit *)this,8), cVar2 != '\0' ||
      (cVar2 = CBaseUnit::ISA((CBaseUnit *)this,0xd), cVar2 != '\0')))) {
                    /* try { // try from 008802ca to 008802ce has its CatchHandler @ 008808a9 */
    std::wstring::wstring((wstring_conflict *)local_d8,L"ITEM_DEFENSE_REQUIREMENTS",&local_32);
                    /* try { // try from 008802cf to 008802de has its CatchHandler @ 008808b2 */
    pCVar5 = (CGraphManager *)CGraphManager::getSingleton();
    pCVar6 = (CGraph *)CGraphManager::getGraph(pCVar5,(wstring_conflict *)local_d8);
    if ((allocator *)(local_d8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_d8[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
      }
    }
    fVar8 = (float)CGraph::getValue(pCVar6,(float)*(int *)(this + 0x274),0);
    fVar8 = floorf((fVar8 * (float)*(int *)(this + 0x288)) / DAT_00fa483c);
    iVar4 = 0;
    if (1 < (int)fVar8 - iVar7) {
      iVar4 = (int)fVar8 - iVar7;
    }
    *(int *)(this + 0x288) = iVar4;
    return;
  }
  return;
}



/* address=00880950
   symbol=CEquipment::calculateCombatStats */
/* DECOMPILATION FAILED:
Low-level Error: Overriding symbol with different type size */

/* address=00882330
   symbol=CEquipment::improveHeirloom */

/* CEquipment::improveHeirloom() */

void __thiscall CEquipment::improveHeirloom(CEquipment *this)

{
  CEffect *pCVar1;
  undefined8 *puVar2;
  long *plVar3;
  uint uVar4;
  ulong uVar5;
  CEffectManager *this_00;
  CEffectManager *pCVar6;
  int iVar7;
  float fVar8;
  float local_2c;

  calculateCombatStats(this,true);
  if ((*(int *)(this + 0x28c) < 10) &&
     (this_00 = *(CEffectManager **)(this + 0x1b8), this_00 != (CEffectManager *)0x0)) {
    iVar7 = 0;
    do {
      if (*(int *)(this_00 + (long)iVar7 * 0x18 + 0x30) != 0) {
        uVar5 = 0;
        pCVar6 = this_00 + (long)iVar7 * 0x18 + 0x28;
        do {
          uVar4 = (uint)uVar5;
          if (uVar4 < *(uint *)(this_00 + (long)iVar7 * 0x18 + 0x34)) {
            pCVar1 = *(CEffect **)(*(long *)pCVar6 + uVar5 * 8);
            local_2c = *(float *)(pCVar1 + 0xc0);
            fVar8 = (float)CEffect::value(pCVar1,0);
            if (uVar4 < *(uint *)(this_00 + (long)iVar7 * 0x18 + 0x34)) goto LAB_00882477;
LAB_008823bd:
            puVar2 = *(undefined8 **)pCVar6;
          }
          else {
            local_2c = *(float *)((CEffect *)**(undefined8 **)pCVar6 + 0xc0);
            fVar8 = (float)CEffect::value((CEffect *)**(undefined8 **)pCVar6,0);
            if (*(uint *)(this_00 + (long)iVar7 * 0x18 + 0x34) <= uVar4) goto LAB_008823bd;
LAB_00882477:
            puVar2 = (undefined8 *)(uVar5 * 8 + *(long *)pCVar6);
          }
          pCVar1 = (CEffect *)*puVar2;
          *(float *)(pCVar1 + 0xc4) = fVar8 * DAT_00fce4ac;
          CEffect::calculateBaseValue(pCVar1,0);
          if (uVar4 < *(uint *)(this_00 + (long)iVar7 * 0x18 + 0x34)) {
            puVar2 = (undefined8 *)(uVar5 * 8 + *(long *)pCVar6);
          }
          else {
            puVar2 = *(undefined8 **)pCVar6;
          }
          fVar8 = (float)CEffect::value((CEffect *)*puVar2);
          if (uVar4 < *(uint *)(this_00 + (long)iVar7 * 0x18 + 0x34)) {
            plVar3 = (long *)(uVar5 * 8 + *(long *)pCVar6);
          }
          else {
            plVar3 = *(long **)pCVar6;
          }
          *(float *)(*plVar3 + 200) = fVar8 * DAT_00fce4ac;
          CEffect::calculateBaseValue();
          if (uVar4 < *(uint *)(this_00 + (long)iVar7 * 0x18 + 0x34)) {
            plVar3 = (long *)(uVar5 * 8 + *(long *)pCVar6);
          }
          else {
            plVar3 = *(long **)pCVar6;
          }
          uVar5 = (ulong)(uVar4 + 1);
          *(float *)(*plVar3 + 0xc0) = DAT_00fce4ac * local_2c;
        } while (uVar4 + 1 < *(uint *)(this_00 + (long)iVar7 * 0x18 + 0x30));
        this_00 = *(CEffectManager **)(this + 0x1b8);
      }
      iVar7 = iVar7 + 1;
    } while (iVar7 != 3);
    CEffectManager::clearOutDescriptions(this_00);
  }
  setRequirements(this);
  return;
}



/* address=008824f0
   symbol=CEquipment::setItemTextHighlighted */

/* WARNING: Removing unreachable block (ram,0x00882e21) */
/* WARNING: Removing unreachable block (ram,0x00882dd6) */
/* WARNING: Removing unreachable block (ram,0x00882d96) */
/* CEquipment::setItemTextHighlighted(bool) */

void __thiscall CEquipment::setItemTextHighlighted(CEquipment *this,bool param_1)

{
  int *piVar1;
  wchar_t *pwVar2;
  wchar_t wVar3;
  byte bVar4;
  long lVar5;
  char cVar6;
  int iVar7;
  byte *pbVar8;
  undefined4 *puVar9;
  uint *puVar10;
  long lVar11;
  string *this_00;
  bool bVar12;
  String aSStack_8e8 [176];
  String local_838 [176];
  String local_788 [176];
  String local_6d8 [176];
  String local_628 [176];
  String local_578 [176];
  String local_4c8 [176];
  String local_418 [176];
  long local_368;
  ulong local_360;
  undefined8 local_358;
  undefined8 local_350;
  undefined8 local_348;
  undefined4 local_340 [32];
  undefined4 *local_2c0;
  undefined8 local_2b8;
  ulong local_2b0;
  undefined8 local_2a8;
  undefined8 local_2a0;
  undefined8 local_298;
  uint local_290 [10];
  uint local_268 [22];
  uint *local_210;
  long local_208;
  ulong local_200;
  undefined8 local_1f8;
  undefined8 local_1f0;
  undefined8 local_1e8;
  undefined4 local_1e0 [32];
  undefined4 *local_160;
  undefined8 local_158;
  ulong local_150;
  undefined8 local_148;
  undefined8 local_140;
  undefined8 local_138;
  uint local_130 [10];
  uint local_108 [22];
  uint *local_b0;
  undefined1 local_a8 [32];
  wstring_conflict local_88 [16];
  wstring_conflict local_78 [16];
  wstring_conflict local_68 [16];
  long local_58 [2];
  wchar_t *local_48;
  long local_38 [2];

  cVar6 = (**(code **)(*(long *)this + 0x210))();
  if (((bool)cVar6 != param_1) && (*(long *)(this + 0x1e8) != 0)) {
    cVar6 = CBaseUnit::getIsQuestUnit((CBaseUnit *)this);
    if (cVar6 == '\0') {
      bVar12 = false;
      getSet();
      if (*(size_t *)(local_48 + -6) == *(size_t *)(::EMPTY_WSTRING + -6)) {
        iVar7 = wmemcmp(local_48,::EMPTY_WSTRING,*(size_t *)(local_48 + -6));
        bVar12 = iVar7 == 0;
      }
      if ((allocator *)(local_48 + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        pwVar2 = local_48 + -2;
        wVar3 = *pwVar2;
        *pwVar2 = *pwVar2 + L'\xffffffff';
        UNLOCK();
        if (wVar3 < L'\x01') {
          std::wstring::_Rep::_M_destroy((allocator *)(local_48 + -6));
        }
      }
      if (bVar12) {
        cVar6 = CBaseUnit::ISA((CBaseUnit *)this,0x36);
        if (cVar6 == '\0') {
          cVar6 = (**(code **)(*(long *)this + 0x2b0))(this);
          if ((cVar6 == '\0') && (cVar6 = CBaseUnit::ISA((CBaseUnit *)this,0xa0), cVar6 == '\0')) {
            if (param_1) {
              CEGUI::colour::colour(local_a8,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc,DAT_00fa47fc);
            }
            else {
              CEGUI::colour::colour(local_a8,DAT_00fc676c,DAT_00fc676c,DAT_00fc676c,DAT_00fa47fc);
            }
            CEGUI::PropertyHelper::colourToString(local_838);
                    /* try { // try from 00882bff to 00882c03 has its CatchHandler @ 00882d24 */
            CEGUI::String::String(aSStack_8e8,"TextColour");
                    /* try { // try from 00882c11 to 00882c15 has its CatchHandler @ 00882d09 */
            CEGUI::PropertySet::setProperty(*(String **)(this + 0x1e8),aSStack_8e8);
                    /* try { // try from 00882c19 to 00882c1d has its CatchHandler @ 00882d24 */
            CEGUI::String::~String(aSStack_8e8);
            CEGUI::String::~String(local_838);
          }
          else {
            cVar6 = CBaseUnit::ISA((CBaseUnit *)this,0x37);
            if (cVar6 == '\0') {
              if (param_1) {
                CGameGlobals::getSingleton();
                STRINGS::StringConvertToUTF8(local_88);
              }
              else {
                CGameGlobals::getSingleton();
                STRINGS::StringConvertToUTF8(local_88);
              }
              this_00 = (string *)local_88;
                    /* try { // try from 00882c86 to 00882c8a has its CatchHandler @ 00882d5c */
              CEGUI::String::String(local_788,this_00);
                    /* try { // try from 00882c9b to 00882c9f has its CatchHandler @ 00882d73 */
              CEGUI::String::String(local_6d8,"TextColour");
                    /* try { // try from 00882cad to 00882cb1 has its CatchHandler @ 00882d5e */
              CEGUI::PropertySet::setProperty(*(String **)(this + 0x1e8),local_6d8);
                    /* try { // try from 00882cb5 to 00882cb9 has its CatchHandler @ 00882d73 */
              CEGUI::String::~String(local_6d8);
                    /* try { // try from 00882cbd to 00882cc1 has its CatchHandler @ 00882d5c */
              CEGUI::String::~String(local_788);
            }
            else {
              if (param_1) {
                CGameGlobals::getSingleton();
                STRINGS::StringConvertToUTF8(local_78);
              }
              else {
                CGameGlobals::getSingleton();
                STRINGS::StringConvertToUTF8(local_78);
              }
              this_00 = (string *)local_78;
                    /* try { // try from 00882b3f to 00882b43 has its CatchHandler @ 00882d49 */
              CEGUI::String::String(local_628,this_00);
                    /* try { // try from 00882b54 to 00882b58 has its CatchHandler @ 00882d92 */
              CEGUI::String::String(local_578,"TextColour");
                    /* try { // try from 00882b66 to 00882b6a has its CatchHandler @ 00882d87 */
              CEGUI::PropertySet::setProperty(*(String **)(this + 0x1e8),local_578);
                    /* try { // try from 00882b6e to 00882b72 has its CatchHandler @ 00882d92 */
              CEGUI::String::~String(local_578);
                    /* try { // try from 00882b76 to 00882b7a has its CatchHandler @ 00882d49 */
              CEGUI::String::~String(local_628);
            }
            std::string::~string(this_00);
          }
        }
        else {
          if (param_1) {
            CGameGlobals::getSingleton();
            STRINGS::StringConvertToUTF8(local_68);
          }
          else {
            CGameGlobals::getSingleton();
            STRINGS::StringConvertToUTF8(local_68);
          }
                    /* try { // try from 00882a80 to 00882a84 has its CatchHandler @ 00882d44 */
          CEGUI::String::String(local_4c8,(string *)local_68);
                    /* try { // try from 00882a95 to 00882a99 has its CatchHandler @ 00882d85 */
          CEGUI::String::String(local_418,"TextColour");
                    /* try { // try from 00882aa7 to 00882aab has its CatchHandler @ 00882d78 */
          CEGUI::PropertySet::setProperty(*(String **)(this + 0x1e8),local_418);
                    /* try { // try from 00882aaf to 00882ab3 has its CatchHandler @ 00882d85 */
          CEGUI::String::~String(local_418);
                    /* try { // try from 00882ab7 to 00882abb has its CatchHandler @ 00882d44 */
          CEGUI::String::~String(local_4c8);
          std::string::~string((string *)local_68);
        }
      }
      else {
        if (param_1) {
          CGameGlobals::getSingleton();
          STRINGS::StringConvertToUTF8((wstring_conflict *)local_58);
        }
        else {
          CGameGlobals::getSingleton();
          STRINGS::StringConvertToUTF8((wstring_conflict *)local_58);
        }
        local_360 = 0x20;
        local_358 = 0;
        local_348 = 0;
        local_350 = 0;
        local_2c0 = (undefined4 *)0x0;
        local_368 = 0;
        local_340[0] = 0;
        lVar5 = *(long *)(local_58[0] + -0x18);
                    /* try { // try from 00882866 to 0088286a has its CatchHandler @ 00882de7 */
        CEGUI::String::grow((ulong)&local_368);
        puVar9 = local_340;
        if (0x20 < local_360) {
          puVar9 = local_2c0;
        }
        puVar9[lVar5] = 0;
        if (lVar5 != 0) {
          lVar11 = lVar5;
          do {
            lVar11 = lVar11 + -1;
            puVar9 = local_340;
            if (0x20 < local_360) {
              puVar9 = local_2c0;
            }
            puVar9[lVar11] = (uint)*(byte *)(local_58[0] + lVar11);
          } while (lVar11 != 0);
        }
        local_2b0 = 0x20;
        local_2a8 = 0;
        local_298 = 0;
        local_2a0 = 0;
        local_210 = (uint *)0x0;
        local_2b8 = 0;
        local_290[0] = 0;
        local_368 = lVar5;
                    /* try { // try from 0088293a to 0088293e has its CatchHandler @ 00882de2 */
        CEGUI::String::grow((ulong)&local_2b8);
        puVar10 = local_290;
        if (0x20 < local_2b0) {
          puVar10 = local_210;
        }
        pbVar8 = (byte *)0xfe4654;
        do {
          bVar4 = *pbVar8;
          pbVar8 = pbVar8 + 1;
          *puVar10 = (uint)bVar4;
          puVar10 = puVar10 + 1;
        } while (pbVar8 != (byte *)0xfe465e);
        local_2b8 = 10;
        puVar10 = local_268;
        if (0x20 < local_2b0) {
          puVar10 = local_210 + 10;
        }
        *puVar10 = 0;
                    /* try { // try from 008829b0 to 008829b4 has its CatchHandler @ 00882d94 */
        CEGUI::PropertySet::setProperty(*(String **)(this + 0x1e8),(String *)&local_2b8);
                    /* try { // try from 008829b8 to 008829bc has its CatchHandler @ 00882de2 */
        CEGUI::String::~String((String *)&local_2b8);
                    /* try { // try from 008829c0 to 008829c4 has its CatchHandler @ 00882de7 */
        CEGUI::String::~String((String *)&local_368);
        if ((allocator *)(local_58[0] + -0x18) !=
            (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_58[0] + -8);
          iVar7 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar7 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
          }
        }
      }
    }
    else {
      if (param_1) {
        CGameGlobals::getSingleton();
        STRINGS::StringConvertToUTF8((wstring_conflict *)local_38);
      }
      else {
        CGameGlobals::getSingleton();
        STRINGS::StringConvertToUTF8((wstring_conflict *)local_38);
      }
      local_200 = 0x20;
      local_1f8 = 0;
      local_1e8 = 0;
      local_1f0 = 0;
      local_160 = (undefined4 *)0x0;
      local_208 = 0;
      local_1e0[0] = 0;
      lVar5 = *(long *)(local_38[0] + -0x18);
                    /* try { // try from 008825c6 to 008825ca has its CatchHandler @ 00882dd1 */
      CEGUI::String::grow((ulong)&local_208);
      puVar9 = local_1e0;
      if (0x20 < local_200) {
        puVar9 = local_160;
      }
      puVar9[lVar5] = 0;
      if (lVar5 != 0) {
        lVar11 = lVar5;
        do {
          lVar11 = lVar11 + -1;
          puVar9 = local_1e0;
          if (0x20 < local_200) {
            puVar9 = local_160;
          }
          puVar9[lVar11] = (uint)*(byte *)(local_38[0] + lVar11);
        } while (lVar11 != 0);
      }
      local_150 = 0x20;
      local_148 = 0;
      local_138 = 0;
      local_140 = 0;
      local_b0 = (uint *)0x0;
      local_158 = 0;
      local_130[0] = 0;
      local_208 = lVar5;
                    /* try { // try from 0088269a to 0088269e has its CatchHandler @ 00882d29 */
      CEGUI::String::grow((ulong)&local_158);
      puVar10 = local_130;
      if (0x20 < local_150) {
        puVar10 = local_b0;
      }
      pbVar8 = (byte *)0xfe4654;
      do {
        bVar4 = *pbVar8;
        pbVar8 = pbVar8 + 1;
        *puVar10 = (uint)bVar4;
        puVar10 = puVar10 + 1;
      } while (pbVar8 != (byte *)0xfe465e);
      local_158 = 10;
      puVar10 = local_108;
      if (0x20 < local_150) {
        puVar10 = local_b0 + 10;
      }
      *puVar10 = 0;
                    /* try { // try from 00882710 to 00882714 has its CatchHandler @ 00882e1c */
      CEGUI::PropertySet::setProperty(*(String **)(this + 0x1e8),(String *)&local_158);
                    /* try { // try from 00882718 to 0088271c has its CatchHandler @ 00882d29 */
      CEGUI::String::~String((String *)&local_158);
                    /* try { // try from 00882720 to 00882724 has its CatchHandler @ 00882dd1 */
      CEGUI::String::~String((String *)&local_208);
      if ((allocator *)(local_38[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_38[0] + -8);
        iVar7 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_38[0] + -0x18));
        }
      }
    }
    if (param_1) {
      CEGUI::Window::moveToFront();
    }
  }
  return;
}



/* address=00882e30
   symbol=CEquipment::createIcon */

/* WARNING: Removing unreachable block (ram,0x00883beb) */
/* WARNING: Removing unreachable block (ram,0x00883cc9) */
/* WARNING: Removing unreachable block (ram,0x00883b2b) */
/* WARNING: Removing unreachable block (ram,0x00883cea) */
/* WARNING: Removing unreachable block (ram,0x00883dd4) */
/* WARNING: Removing unreachable block (ram,0x008839b4) */
/* WARNING: Removing unreachable block (ram,0x00883b36) */
/* WARNING: Removing unreachable block (ram,0x00883d35) */
/* WARNING: Removing unreachable block (ram,0x008839bf) */
/* WARNING: Removing unreachable block (ram,0x00883de2) */
/* WARNING: Removing unreachable block (ram,0x00883e0d) */
/* WARNING: Removing unreachable block (ram,0x00883cd7) */
/* WARNING: Removing unreachable block (ram,0x00883b8f) */
/* WARNING: Removing unreachable block (ram,0x00883cbb) */
/* WARNING: Removing unreachable block (ram,0x00883a49) */
/* WARNING: Removing unreachable block (ram,0x00883bf6) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CEquipment::createIcon(CGameUI&, bool) */

void __thiscall CEquipment::createIcon(CEquipment *this,CGameUI *param_1,bool param_2)

{
  wchar_t *pwVar1;
  allocator *paVar2;
  int *piVar3;
  wchar_t wVar4;
  byte bVar5;
  CBaseUnit *pCVar6;
  size_t __n;
  CDataGroup *this_00;
  char cVar7;
  uint uVar8;
  int iVar9;
  wstring_conflict *pwVar10;
  undefined8 *puVar11;
  long lVar12;
  long lVar13;
  byte *pbVar14;
  uint *puVar15;
  undefined8 uVar16;
  UVector2 *pUVar17;
  allocator *paVar18;
  long lVar19;
  uint uVar20;
  bool bVar21;
  undefined4 uVar22;
  float fVar23;
  float local_77c;
  float local_770;
  float local_76c;
  undefined8 local_768;
  ulong local_760;
  undefined8 local_758;
  undefined8 local_750;
  undefined8 local_748;
  uint local_740 [5];
  uint local_72c [27];
  uint *local_6c0;
  Image local_6b8 [176];
  String local_608 [176];
  String local_558 [176];
  String local_4a8 [176];
  String local_3f8 [176];
  String local_348 [176];
  String local_298 [176];
  void *local_1e8;
  undefined8 local_1e0;
  undefined8 local_1d8;
  float local_1c8;
  undefined4 local_1c4;
  float local_1c0;
  undefined4 local_1bc;
  float local_1b8;
  undefined4 local_1b4;
  float local_1b0;
  undefined4 local_1ac;
  undefined4 local_1a8;
  undefined4 local_1a4;
  undefined4 local_1a0;
  undefined4 local_19c;
  uchar *local_198 [2];
  long local_188 [2];
  long local_178 [2];
  wchar_t *local_168 [2];
  uchar *local_158 [2];
  long local_148 [2];
  STRINGS local_138 [16];
  string local_128 [16];
  STRINGS local_118 [16];
  string local_108 [16];
  long local_f8 [2];
  long local_e8 [2];
  long local_d8 [2];
  wchar_t *local_c8 [2];
  long local_b8 [2];
  long local_a8 [2];
  wchar_t *local_98 [2];
  long local_88 [2];
  long local_78 [2];
  wchar_t *local_68 [4];
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

  if (*(long *)(this + 0x1b0) == 0) {
    return;
  }
  if ((*(long *)(this + 0x2c8) != 0) && (!param_2)) {
    return;
  }
                    /* try { // try from 00882e83 to 00882e87 has its CatchHandler @ 00883ce2 */
  std::wstring::wstring((wstring_conflict *)local_78,L"ICON",local_39);
                    /* try { // try from 00882e9c to 00882eb0 has its CatchHandler @ 00883d24 */
  pwVar10 = (wstring_conflict *)
            CDataGroup::GetDataValue
                      (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_78,
                       (wstring_conflict *)&::EMPTY_WSTRING);
  std::wstring::wstring((wstring_conflict *)local_68,pwVar10);
  if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar3 = (int *)(local_78[0] + -8);
    iVar9 = *piVar3;
    *piVar3 = *piVar3 + -1;
    UNLOCK();
    if (iVar9 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
    }
  }
  this[0x25d] = (CEquipment)0x0;
                    /* try { // try from 00882ef2 to 00882f21 has its CatchHandler @ 00883a5e */
  if (((*(long *)(this + 0x240) == 0) ||
      (pCVar6 = *(CBaseUnit **)(*(long *)(this + 0x240) + 0x20), pCVar6 == (CBaseUnit *)0x0)) ||
     (cVar7 = CBaseUnit::ISA(pCVar6,0x7f), cVar7 == '\0')) {
    if (*(long *)(param_1 + 0x38) != 0) {
      STRINGS::StringUpper
                ((STRINGS *)local_98,(wstring_conflict *)(*(long *)(param_1 + 0x38) + 0x40));
      local_1e8 = (void *)0x0;
      local_1e0 = 0;
      local_1d8 = 0;
                    /* try { // try from 00882f5e to 00882f62 has its CatchHandler @ 00883b23 */
      std::wstring::wstring((wstring_conflict *)local_a8,L"WARDROBE",&local_3b);
                    /* try { // try from 00882f7a to 00882f7e has its CatchHandler @ 00883ae9 */
      uVar8 = CDataGroup::GetDataGroupsMatchingName
                        (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_a8,
                         (vector *)&local_1e8);
      if ((allocator *)(local_a8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar3 = (int *)(local_a8[0] + -8);
        iVar9 = *piVar3;
        *piVar3 = *piVar3 + -1;
        UNLOCK();
        if (iVar9 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
        }
      }
                    /* try { // try from 00882fa4 to 00882fa8 has its CatchHandler @ 00883df0 */
      std::wstring::wstring((wstring_conflict *)local_b8,(wstring_conflict *)&::EMPTY_WSTRING);
      if (uVar8 != 0) {
        lVar19 = 0;
        uVar20 = 0;
        do {
          this_00 = *(CDataGroup **)((long)local_1e8 + lVar19);
                    /* try { // try from 00883073 to 00883077 has its CatchHandler @ 00883df5 */
          std::wstring::wstring((wstring_conflict *)local_d8,L"CLASS",&local_3c);
                    /* try { // try from 00883083 to 00883097 has its CatchHandler @ 00883dfd */
          pwVar10 = (wstring_conflict *)
                    CDataGroup::GetDataValue(this_00,(wstring_conflict *)local_d8,L"");
          STRINGS::StringUpper((STRINGS *)local_c8,pwVar10);
          if ((allocator *)(local_d8[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar3 = (int *)(local_d8[0] + -8);
            iVar9 = *piVar3;
            *piVar3 = *piVar3 + -1;
            UNLOCK();
            if (iVar9 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
            }
          }
                    /* try { // try from 008830ba to 008830be has its CatchHandler @ 00883ae4 */
          iVar9 = std::wstring::compare((wchar_t *)local_98);
          if (iVar9 == 0) {
LAB_00882fc8:
                    /* try { // try from 00882fdd to 00882fe1 has its CatchHandler @ 00883a65 */
            std::wstring::wstring((wstring_conflict *)local_e8,L"ICON",&local_3d);
                    /* try { // try from 00882ff2 to 00882ff6 has its CatchHandler @ 00883aa6 */
            puVar11 = (undefined8 *)
                      CDataGroup::GetDataValue
                                (this_00,(wstring_conflict *)local_e8,
                                 (wstring_conflict *)&::EMPTY_WSTRING);
            bVar21 = false;
            __n = *(size_t *)((wchar_t *)*puVar11 + -6);
            if (__n == *(size_t *)(::EMPTY_WSTRING + -6)) {
              iVar9 = wmemcmp((wchar_t *)*puVar11,::EMPTY_WSTRING,__n);
              bVar21 = iVar9 == 0;
            }
            if ((allocator *)(local_e8[0] + -0x18) !=
                (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar3 = (int *)(local_e8[0] + -8);
              iVar9 = *piVar3;
              *piVar3 = *piVar3 + -1;
              UNLOCK();
              if (iVar9 < 1) {
                std::wstring::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
              }
            }
            if (!bVar21) {
                    /* try { // try from 008835ad to 008835b1 has its CatchHandler @ 00883b8a */
              std::wstring::wstring((wstring_conflict *)local_f8,L"ICON",&local_3e);
                    /* try { // try from 008835c2 to 008835d6 has its CatchHandler @ 00883b9a */
              CDataGroup::GetDataValue
                        (this_00,(wstring_conflict *)local_f8,(wstring_conflict *)&::EMPTY_WSTRING);
              std::wstring::assign((wstring_conflict *)local_68);
              if ((allocator *)(local_f8[0] + -0x18) !=
                  (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar3 = (int *)(local_f8[0] + -8);
                iVar9 = *piVar3;
                *piVar3 = *piVar3 + -1;
                UNLOCK();
                if (iVar9 < 1) {
                  std::wstring::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
                }
              }
            }
            paVar18 = (allocator *)(local_c8[0] + -6);
          }
          else {
            paVar18 = (allocator *)(local_c8[0] + -6);
            if ((*(size_t *)(local_c8[0] + -6) == *(size_t *)(local_98[0] + -6)) &&
               (iVar9 = wmemcmp(local_c8[0],local_98[0],*(size_t *)(local_c8[0] + -6)), iVar9 == 0))
            goto LAB_00882fc8;
          }
          if (paVar18 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            paVar2 = paVar18 + 0x10;
            iVar9 = *(int *)paVar2;
            *(int *)paVar2 = *(int *)paVar2 + -1;
            UNLOCK();
            if (iVar9 < 1) {
              std::wstring::_Rep::_M_destroy(paVar18);
            }
          }
          uVar20 = uVar20 + 1;
          lVar19 = lVar19 + 8;
        } while (uVar20 < uVar8);
      }
      if ((allocator *)(local_b8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar3 = (int *)(local_b8[0] + -8);
        iVar9 = *piVar3;
        *piVar3 = *piVar3 + -1;
        UNLOCK();
        if (iVar9 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
        }
      }
      if (local_1e8 != (void *)0x0) {
        operator_delete(local_1e8);
      }
      if ((allocator *)(local_98[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
      {
        LOCK();
        pwVar1 = local_98[0] + -2;
        wVar4 = *pwVar1;
        *pwVar1 = *pwVar1 + L'\xffffffff';
        UNLOCK();
        if (wVar4 < L'\x01') {
          std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -6));
        }
      }
    }
  }
  else {
    this[0x25d] = (CEquipment)0x1;
                    /* try { // try from 008836fc to 00883700 has its CatchHandler @ 008839cd */
    std::wstring::wstring((wstring_conflict *)local_88,L"GAMBLER_ICON",&local_3a);
                    /* try { // try from 00883718 to 0088372c has its CatchHandler @ 00883994 */
    CDataGroup::GetDataValue
              (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_88,
               (wstring_conflict *)local_68);
    std::wstring::assign((wstring_conflict *)local_68);
    if ((allocator *)(local_88[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar3 = (int *)(local_88[0] + -8);
      iVar9 = *piVar3;
      *piVar3 = *piVar3 + -1;
      UNLOCK();
      if (iVar9 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
      }
    }
  }
  lVar19 = *(long *)(this + 0x2c8);
  if (lVar19 == 0) {
                    /* try { // try from 00883788 to 0088378c has its CatchHandler @ 00883a5e */
    CEGUI::String::String(local_3f8,"");
                    /* try { // try from 008837a5 to 008837a9 has its CatchHandler @ 00883db2 */
    std::string::string(local_108,"icon_",&local_3f);
                    /* try { // try from 008837b8 to 008837bc has its CatchHandler @ 00883dac */
    STRINGS::uniqueName(local_118,local_108);
                    /* try { // try from 008837cb to 008837cf has its CatchHandler @ 00883da7 */
    CEGUI::String::String(local_348,(string *)local_118);
                    /* try { // try from 008837e0 to 008837e4 has its CatchHandler @ 00883da2 */
    CEGUI::String::String(local_298,(uchar *)"GuiLook/StaticImage");
                    /* try { // try from 008837f5 to 008837f9 has its CatchHandler @ 00883d72 */
    uVar16 = CEGUI::WindowManager::createWindow
                       (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,local_298,local_348);
    *(undefined8 *)(this + 0x2c8) = uVar16;
                    /* try { // try from 00883809 to 0088380d has its CatchHandler @ 00883da2 */
    CEGUI::String::~String(local_298);
                    /* try { // try from 00883811 to 00883815 has its CatchHandler @ 00883da7 */
    CEGUI::String::~String(local_348);
                    /* try { // try from 00883819 to 0088381d has its CatchHandler @ 00883dac */
    std::string::~string((string *)local_118);
                    /* try { // try from 00883821 to 00883825 has its CatchHandler @ 00883db2 */
    std::string::~string(local_108);
                    /* try { // try from 00883829 to 0088383f has its CatchHandler @ 00883a5e */
    CEGUI::String::~String(local_3f8);
    CEGUI::String::String(local_608,"");
                    /* try { // try from 00883858 to 0088385c has its CatchHandler @ 00883d6a */
    std::string::string(local_128,"icon_",&local_40);
                    /* try { // try from 0088386b to 0088386f has its CatchHandler @ 00883d65 */
    STRINGS::uniqueName(local_138,local_128);
                    /* try { // try from 0088387e to 00883882 has its CatchHandler @ 00883d40 */
    CEGUI::String::String(local_558,(string *)local_138);
                    /* try { // try from 00883893 to 00883897 has its CatchHandler @ 00883dcf */
    CEGUI::String::String(local_4a8,(uchar *)"GuiLook/StaticImage");
                    /* try { // try from 008838ad to 008838b1 has its CatchHandler @ 00883db7 */
    pUVar17 = (UVector2 *)
              CEGUI::WindowManager::createWindow
                        (CEGUI::Singleton<CEGUI::WindowManager>::ms_Singleton,local_4a8,local_558);
                    /* try { // try from 008838b8 to 008838bc has its CatchHandler @ 00883dcf */
    CEGUI::String::~String(local_4a8);
                    /* try { // try from 008838c0 to 008838c4 has its CatchHandler @ 00883d40 */
    CEGUI::String::~String(local_558);
                    /* try { // try from 008838c8 to 008838cc has its CatchHandler @ 00883d65 */
    std::string::~string((string *)local_138);
                    /* try { // try from 008838d0 to 008838d4 has its CatchHandler @ 00883d6a */
    std::string::~string(local_128);
                    /* try { // try from 008838dd to 008838e1 has its CatchHandler @ 00883a5e */
    CEGUI::String::~String(local_608);
  }
  else {
    pUVar17 = (UVector2 *)**(undefined8 **)(lVar19 + 0x78);
  }
                    /* try { // try from 0088319f to 008831a3 has its CatchHandler @ 00883a5e */
  uVar22 = CGameUI::scaledY(param_1,DAT_00fd110c);
                    /* try { // try from 008831b7 to 008831bb has its CatchHandler @ 00883a47 */
  local_1a4 = CGameUI::scaledY(param_1,DAT_00fa874c);
  local_1a8 = 0;
  local_1a0 = 0;
  local_19c = uVar22;
                    /* try { // try from 008831fe to 00883202 has its CatchHandler @ 00883a54 */
  CEGUI::Window::setSize(*(UVector2 **)(this + 0x2c8));
  if (*(long *)(local_68[0] + -6) == 0) {
                    /* try { // try from 00883649 to 0088364d has its CatchHandler @ 00883a5e */
    std::operator+((wchar_t *)local_168,(wstring_conflict *)L"No icon specified for equipment ");
                    /* try { // try from 00883661 to 00883665 has its CatchHandler @ 00883bdb */
    STRINGS::StringConvertToNarrow((STRINGS *)local_178,local_168[0]);
                    /* try { // try from 00883666 to 0088367c has its CatchHandler @ 00883c04 */
    uVar16 = Ogre::LogManager::getSingleton();
    Ogre::LogManager::logMessage(uVar16,(STRINGS *)local_178,2,0);
    if ((allocator *)(local_178[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar3 = (int *)(local_178[0] + -8);
      iVar9 = *piVar3;
      *piVar3 = *piVar3 + -1;
      UNLOCK();
      if (iVar9 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_178[0] + -0x18));
      }
    }
    if ((allocator *)(local_168[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      pwVar1 = local_168[0] + -2;
      wVar4 = *pwVar1;
      *pwVar1 = *pwVar1 + L'\xffffffff';
      UNLOCK();
      if (wVar4 < L'\x01') {
        std::wstring::_Rep::_M_destroy((allocator *)(local_168[0] + -6));
        local_77c = DAT_00fd110c;
        local_770 = DAT_00fd110c;
        local_76c = DAT_00fa874c;
        goto LAB_0088330d;
      }
    }
    local_77c = DAT_00fd110c;
    local_770 = DAT_00fd110c;
    local_76c = DAT_00fa874c;
  }
  else {
                    /* try { // try from 00883229 to 0088322d has its CatchHandler @ 00883a59 */
    std::wstring::wstring((wstring_conflict *)local_148,local_68[0],&local_41);
                    /* try { // try from 0088323c to 00883240 has its CatchHandler @ 00883b41 */
    STRINGS::StringConvertToUTF8((wstring_conflict *)local_158);
                    /* try { // try from 0088324e to 00883252 has its CatchHandler @ 00883b51 */
    lVar12 = CGameUI::getImageFromImageSet(param_1,local_158[0]);
    if ((allocator *)(local_158[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar3 = (int *)(local_158[0] + -8);
      iVar9 = *piVar3;
      *piVar3 = *piVar3 + -1;
      UNLOCK();
      if (iVar9 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_158[0] + -0x18));
      }
    }
    if ((allocator *)(local_148[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar3 = (int *)(local_148[0] + -8);
      iVar9 = *piVar3;
      *piVar3 = *piVar3 + -1;
      UNLOCK();
      if (iVar9 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_148[0] + -0x18));
      }
    }
    uVar8 = KSETTINGS_YRATIO;
    if (lVar12 == 0) {
      std::wstring::~wstring((wstring_conflict *)local_68);
      return;
    }
    local_76c = *(float *)(lVar12 + 0x20);
                    /* try { // try from 0088329f to 008832e6 has its CatchHandler @ 00883a5e */
    lVar13 = CMasterResourceManager::getSingleton();
    fVar23 = (float)CDynamicPropertyFile::GetFloat(*(CDynamicPropertyFile **)(lVar13 + 0x90),uVar8);
    uVar8 = KSETTINGS_YRATIO;
    local_76c = local_76c / fVar23;
    local_770 = *(float *)(lVar12 + 0x24);
    lVar12 = CMasterResourceManager::getSingleton();
    fVar23 = (float)CDynamicPropertyFile::GetFloat(*(CDynamicPropertyFile **)(lVar12 + 0x90),uVar8);
    local_770 = local_770 / fVar23;
    local_77c = DAT_00fd110c;
  }
LAB_0088330d:
  local_1b4 = 0;
  local_1ac = 0;
  local_1b8 = (DAT_00fa874c - local_76c) * DAT_00fa4810 * _DAT_00fd1110;
  local_1b0 = ((local_77c - local_770) * DAT_00fa4810) / local_77c;
  DAT_00fd110c = local_77c;
                    /* try { // try from 00883370 to 00883374 has its CatchHandler @ 008839d2 */
  CEGUI::Window::setPosition(pUVar17);
  local_1c8 = _DAT_00fd1110 * local_76c;
  local_1c4 = 0;
  local_1bc = 0;
  local_1c0 = local_770 / local_77c;
                    /* try { // try from 008833c2 to 008833c6 has its CatchHandler @ 008839d4 */
  CEGUI::Window::setSize(pUVar17);
                    /* try { // try from 008833e2 to 008833e6 has its CatchHandler @ 008839d6 */
  std::wstring::wstring((wstring_conflict *)local_188,local_68[0],&local_42);
                    /* try { // try from 008833f2 to 008833f6 has its CatchHandler @ 008839e2 */
  STRINGS::StringConvertToUTF8((wstring_conflict *)local_198);
                    /* try { // try from 00883404 to 0088341b has its CatchHandler @ 008839ef */
  CGameUI::getImageFromImageSet(param_1,local_198[0]);
  CEGUI::PropertyHelper::imageToString(local_6b8);
  local_760 = 0x20;
  local_758 = 0;
  local_748 = 0;
  local_750 = 0;
  local_6c0 = (uint *)0x0;
  local_768 = 0;
  local_740[0] = 0;
                    /* try { // try from 0088346a to 0088346e has its CatchHandler @ 00883a01 */
  CEGUI::String::grow((ulong)&local_768);
  puVar15 = local_740;
  if (0x20 < local_760) {
    puVar15 = local_6c0;
  }
  pbVar14 = (byte *)0xfd0c0d;
  do {
    bVar5 = *pbVar14;
    pbVar14 = pbVar14 + 1;
    *puVar15 = (uint)bVar5;
    puVar15 = puVar15 + 1;
  } while (pbVar14 != (byte *)0xfd0c12);
  local_768 = 5;
  puVar15 = local_72c;
  if (0x20 < local_760) {
    puVar15 = local_6c0 + 5;
  }
  *puVar15 = 0;
                    /* try { // try from 008834d5 to 008834d9 has its CatchHandler @ 00883a0e */
  CEGUI::PropertySet::setProperty((String *)pUVar17,(String *)&local_768);
                    /* try { // try from 008834dd to 008834e1 has its CatchHandler @ 00883a01 */
  CEGUI::String::~String((String *)&local_768);
                    /* try { // try from 008834e5 to 008834e9 has its CatchHandler @ 008839ef */
  CEGUI::String::~String((String *)local_6b8);
  if ((allocator *)(local_198[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar3 = (int *)(local_198[0] + -8);
    iVar9 = *piVar3;
    *piVar3 = *piVar3 + -1;
    UNLOCK();
    if (iVar9 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_198[0] + -0x18));
    }
  }
  if ((allocator *)(local_188[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar3 = (int *)(local_188[0] + -8);
    iVar9 = *piVar3;
    *piVar3 = *piVar3 + -1;
    UNLOCK();
    if (iVar9 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_188[0] + -0x18));
    }
  }
  pUVar17[0x3e2] = (UVector2)0x1;
                    /* try { // try from 00883528 to 00883545 has its CatchHandler @ 00883a5e */
  CEGUI::EventSet::setMutedState((bool)((char)pUVar17 + '8'));
  if (lVar19 == 0) {
    CEGUI::Window::addChildWindow(*(Window **)(this + 0x2c8));
  }
  if ((allocator *)(local_68[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    pwVar1 = local_68[0] + -2;
    wVar4 = *pwVar1;
    *pwVar1 = *pwVar1 + L'\xffffffff';
    UNLOCK();
    if (wVar4 < L'\x01') {
      std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -6));
    }
  }
  return;
}



/* address=00883e20
   symbol=CEquipment::recalculatePrice */

/* WARNING: Removing unreachable block (ram,0x00884593) */
/* WARNING: Removing unreachable block (ram,0x00884585) */
/* WARNING: Removing unreachable block (ram,0x008844e2) */
/* WARNING: Removing unreachable block (ram,0x008845af) */
/* WARNING: Removing unreachable block (ram,0x008845a1) */
/* WARNING: Removing unreachable block (ram,0x008844f2) */
/* WARNING: Removing unreachable block (ram,0x00884575) */
/* WARNING: Removing unreachable block (ram,0x00884502) */
/* WARNING: Removing unreachable block (ram,0x008844c2) */
/* WARNING: Removing unreachable block (ram,0x008844a7) */
/* CEquipment::recalculatePrice() */

void __thiscall CEquipment::recalculatePrice(CEquipment *this)

{
  int *piVar1;
  int iVar2;
  CBaseUnit *pCVar3;
  char cVar4;
  int iVar5;
  CGraphManager *pCVar6;
  CGraph *pCVar7;
  CGraph *pCVar8;
  int iVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  long local_e8 [2];
  long local_d8 [2];
  long local_c8 [2];
  long local_b8 [2];
  long local_a8 [2];
  long local_98 [2];
  long local_88 [2];
  long local_78 [2];
  long local_68 [2];
  long local_58 [2];
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

  *(undefined4 *)(this + 0x264) = 1;
  *(undefined4 *)(this + 0x268) = 1;
                    /* try { // try from 00883e60 to 00883e64 has its CatchHandler @ 00884535 */
  std::wstring::wstring((wstring_conflict *)local_58,L"VALUE",local_39);
                    /* try { // try from 00883e74 to 00883e78 has its CatchHandler @ 00884524 */
  iVar5 = CDataGroup::GetDataValue(*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_58,100);
  if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_58[0] + -8);
    iVar9 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar9 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
    }
  }
  if (iVar5 != 0) {
    iVar9 = 1;
    if (0 < *(int *)(this + 0x274)) {
      iVar9 = *(int *)(this + 0x274);
    }
    cVar4 = CBaseUnit::ISA((CBaseUnit *)this,0x36);
    if (cVar4 == '\0') {
      cVar4 = (**(code **)(*(long *)this + 0x2b0))(this);
      if (cVar4 == '\0') {
                    /* try { // try from 00884275 to 00884279 has its CatchHandler @ 008844d2 */
        std::wstring::wstring((wstring_conflict *)local_a8,L"PRICE_PLAYERBUY_NORMAL",&local_3e);
                    /* try { // try from 0088427a to 00884289 has its CatchHandler @ 008844d0 */
        pCVar6 = (CGraphManager *)CGraphManager::getSingleton();
        pCVar7 = (CGraph *)CGraphManager::getGraph(pCVar6,(wstring_conflict *)local_a8);
        if ((allocator *)(local_a8[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_a8[0] + -8);
          iVar2 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar2 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
          }
        }
                    /* try { // try from 008842b4 to 008842b8 has its CatchHandler @ 00884500 */
        std::wstring::wstring((wstring_conflict *)local_b8,L"PRICE_PLAYERSELL_NORMAL",&local_3f);
                    /* try { // try from 008842b9 to 008842c8 has its CatchHandler @ 008844f0 */
        pCVar6 = (CGraphManager *)CGraphManager::getSingleton();
        pCVar8 = (CGraph *)CGraphManager::getGraph(pCVar6,(wstring_conflict *)local_b8);
        if ((allocator *)(local_b8[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_b8[0] + -8);
          iVar2 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar2 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
          }
        }
      }
      else {
                    /* try { // try from 0088414c to 00884150 has its CatchHandler @ 008844b4 */
        std::wstring::wstring((wstring_conflict *)local_88,L"PRICE_PLAYERBUY_MAGIC",&local_3c);
                    /* try { // try from 00884151 to 00884160 has its CatchHandler @ 008844b2 */
        pCVar6 = (CGraphManager *)CGraphManager::getSingleton();
        pCVar7 = (CGraph *)CGraphManager::getGraph(pCVar6,(wstring_conflict *)local_88);
        if ((allocator *)(local_88[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_88[0] + -8);
          iVar2 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar2 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
          }
        }
                    /* try { // try from 00884191 to 00884195 has its CatchHandler @ 008844b9 */
        std::wstring::wstring((wstring_conflict *)local_98,L"PRICE_PLAYERSELL_MAGIC",&local_3d);
                    /* try { // try from 00884196 to 008841a5 has its CatchHandler @ 00884494 */
        pCVar6 = (CGraphManager *)CGraphManager::getSingleton();
        pCVar8 = (CGraph *)CGraphManager::getGraph(pCVar6,(wstring_conflict *)local_98);
        if ((allocator *)(local_98[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_98[0] + -8);
          iVar2 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar2 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
          }
        }
      }
    }
    else {
                    /* try { // try from 00883ee4 to 00883ee8 has its CatchHandler @ 0088453a */
      std::wstring::wstring((wstring_conflict *)local_68,L"PRICE_PLAYERBUY_UNIQUE",&local_3a);
                    /* try { // try from 00883ee9 to 00883ef8 has its CatchHandler @ 00884545 */
      pCVar6 = (CGraphManager *)CGraphManager::getSingleton();
      pCVar7 = (CGraph *)CGraphManager::getGraph(pCVar6,(wstring_conflict *)local_68);
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
                    /* try { // try from 00883f29 to 00883f2d has its CatchHandler @ 00884555 */
      std::wstring::wstring((wstring_conflict *)local_78,L"PRICE_PLAYERSELL_UNIQUE",&local_3b);
                    /* try { // try from 00883f2e to 00883f3d has its CatchHandler @ 00884565 */
      pCVar6 = (CGraphManager *)CGraphManager::getSingleton();
      pCVar8 = (CGraph *)CGraphManager::getGraph(pCVar6,(wstring_conflict *)local_78);
      if ((allocator *)(local_78[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_78[0] + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
        }
      }
    }
    fVar10 = (float)iVar9;
    fVar11 = (float)CGraph::getValue(pCVar7,fVar10,0);
    fVar12 = (float)CGraph::getValue(pCVar8,fVar10,0);
    fVar14 = DAT_00fa483c;
    fVar13 = (float)iVar5;
    fVar15 = fVar13 / DAT_00fa483c;
    fVar11 = ceilf(fVar11 * fVar15);
    *(int *)(this + 0x264) = (int)fVar11;
    fVar11 = ceilf(fVar12 * fVar15);
    *(int *)(this + 0x268) = (int)fVar11;
    if (((*(long *)(this + 0x240) != 0) &&
        (pCVar3 = *(CBaseUnit **)(*(long *)(this + 0x240) + 0x20), pCVar3 != (CBaseUnit *)0x0)) &&
       (cVar4 = CBaseUnit::ISA(pCVar3,0x7f), cVar4 != '\0')) {
                    /* try { // try from 00884205 to 00884209 has its CatchHandler @ 00884510 */
      std::wstring::wstring((wstring_conflict *)local_c8,L"PRICE_PLAYERGAMBLE_MAGIC",&local_40);
                    /* try { // try from 0088420a to 00884219 has its CatchHandler @ 008844d4 */
      pCVar6 = (CGraphManager *)CGraphManager::getSingleton();
      pCVar7 = (CGraph *)CGraphManager::getGraph(pCVar6,(wstring_conflict *)local_c8);
      if ((allocator *)(local_c8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_c8[0] + -8);
        iVar5 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar5 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
        }
      }
      fVar11 = (float)CGraph::getValue(pCVar7,fVar10,0);
      fVar11 = ceilf(fVar11 * (fVar13 / fVar14));
      *(int *)(this + 0x264) = (int)fVar11;
    }
                    /* try { // try from 00884026 to 0088402a has its CatchHandler @ 00884512 */
    std::wstring::wstring((wstring_conflict *)local_d8,L"PRICE_PLAYERBUY_NORMAL",&local_41);
                    /* try { // try from 0088402b to 0088403a has its CatchHandler @ 00884514 */
    pCVar6 = (CGraphManager *)CGraphManager::getSingleton();
    pCVar7 = (CGraph *)CGraphManager::getGraph(pCVar6,(wstring_conflict *)local_d8);
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
                    /* try { // try from 00884065 to 00884069 has its CatchHandler @ 00884516 */
    std::wstring::wstring((wstring_conflict *)local_e8,L"PRICE_PLAYERSELL_NORMAL",&local_42);
                    /* try { // try from 0088406a to 00884079 has its CatchHandler @ 00884522 */
    pCVar6 = (CGraphManager *)CGraphManager::getSingleton();
    pCVar8 = (CGraph *)CGraphManager::getGraph(pCVar6,(wstring_conflict *)local_e8);
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
    fVar11 = (float)CGraph::getValue(pCVar7,fVar10,0);
    fVar10 = (float)CGraph::getValue(pCVar8,fVar10,0);
    fVar13 = fVar13 / fVar14;
    fVar14 = ceilf(fVar11 * fVar13);
    *(int *)(this + 0x26c) = (int)fVar14;
    fVar14 = ceilf(fVar10 * fVar13);
    *(int *)(this + 0x270) = (int)fVar14;
  }
  return;
}



/* address=008845c0
   symbol=CEquipment::enchant */

/* WARNING: Removing unreachable block (ram,0x00884a15) */
/* CEquipment::enchant(bool) */

void __thiscall CEquipment::enchant(CEquipment *this,bool param_1)

{
  int *piVar1;
  int iVar2;
  char cVar3;
  uint uVar4;
  long lVar5;
  bool bVar6;
  float fVar7;
  float fVar8;
  long local_28;
  allocator local_19;

  cVar3 = CBaseUnit::ISA((CBaseUnit *)this,0x87);
  if (cVar3 != '\0') {
    param_1 = true;
  }
  bVar6 = false;
  cVar3 = CBaseUnit::ISA((CBaseUnit *)this,0x36);
  if (cVar3 != '\0') {
    bVar6 = true;
    if (*(long *)(this + 0x1b8) != 0) {
      bVar6 = *(int *)(*(long *)(this + 0x1b8) + 0x18) == 0;
    }
  }
  cVar3 = CBaseUnit::ISA((CBaseUnit *)this,0x37);
  if (cVar3 == '\0') {
    if (this[0x20a] == (CEquipment)0x0) goto LAB_00884634;
    if (param_1 == false) {
      fVar8 = (float)UTILITIES::randomBetweenVolatile(0.0,DAT_00fa871c);
      lVar5 = CGameGlobals::getSingleton();
      if (DAT_00fa86e0 * *(float *)(lVar5 + 0x24) <= fVar8) goto LAB_00884634;
    }
  }
  cVar3 = CBaseUnit::ISA((CBaseUnit *)this,0x36);
  if (((cVar3 == '\0') || (bVar6)) &&
     (((cVar3 = CBaseUnit::ISA((CBaseUnit *)this,8), cVar3 != '\0' ||
       (((cVar3 = CBaseUnit::ISA((CBaseUnit *)this,0xd), cVar3 != '\0' ||
         (cVar3 = CBaseUnit::ISA((CBaseUnit *)this,0x11), cVar3 != '\0')) ||
        (cVar3 = CBaseUnit::ISA((CBaseUnit *)this,0xa0), cVar3 != '\0')))) ||
      (cVar3 = CBaseUnit::ISA((CBaseUnit *)this,0x18), cVar3 != '\0')))) {
    cVar3 = CBaseUnit::ISA((CBaseUnit *)this,0x36);
    if (cVar3 == '\0') {
      cVar3 = CBaseUnit::ISA((CBaseUnit *)this,0x37);
      if (cVar3 == '\0') {
        lVar5 = CGameGlobals::getSingleton();
        iVar2 = *(int *)(lVar5 + 0x34);
        lVar5 = CGameGlobals::getSingleton();
        uVar4 = UTILITIES::randomIntegerBetweenVolatile(*(int *)(lVar5 + 0x30),iVar2);
      }
      else {
        lVar5 = CGameGlobals::getSingleton();
        iVar2 = *(int *)(lVar5 + 0x3c);
        lVar5 = CGameGlobals::getSingleton();
        uVar4 = UTILITIES::randomIntegerBetweenVolatile(*(int *)(lVar5 + 0x38),iVar2);
      }
    }
    else {
      lVar5 = CGameGlobals::getSingleton();
      iVar2 = *(int *)(lVar5 + 0x44);
      lVar5 = CGameGlobals::getSingleton();
      uVar4 = UTILITIES::randomIntegerBetweenVolatile(*(int *)(lVar5 + 0x40),iVar2);
    }
    CResourceManager::createAffixesForUnit
              (*(CResourceManager **)(this + 0x68),(CBaseUnit *)this,*(uint *)(this + 0x274),uVar4);
    this[0x348] = (CEquipment)0x0;
  }
LAB_00884634:
  cVar3 = CBaseUnit::ISA((CBaseUnit *)this,0x36);
  if ((cVar3 != '\0') &&
     ((*(long *)(this + 0x1b8) == 0 || (*(int *)(*(long *)(this + 0x1b8) + 0x30) == 0)))) {
    lVar5 = CGameGlobals::getSingleton();
    iVar2 = *(int *)(lVar5 + 0x44);
    lVar5 = CGameGlobals::getSingleton();
    uVar4 = UTILITIES::randomIntegerBetweenVolatile(*(int *)(lVar5 + 0x40),iVar2);
    CResourceManager::createAffixesForUnit
              (*(CResourceManager **)(this + 0x68),(CBaseUnit *)this,*(int *)(this + 0x274) + 1,
               uVar4);
    this[0x348] = (CEquipment)0x0;
  }
  if (((*(int *)(this + 0x3e0) == 0) && (*(long *)(this + 0x68) != 0)) &&
     ((*(long *)(*(long *)(this + 0x68) + 0x18) != 0 && (this[0x20a] != (CEquipment)0x0)))) {
    fVar7 = (float)UTILITIES::randomBetweenVolatile(0.0,DAT_00fa871c);
    lVar5 = CGameGlobals::getSingleton();
    fVar8 = DAT_00fa86e0;
    if (((fVar7 < *(float *)(lVar5 + 0x28) * DAT_00fa86e0) &&
        (cVar3 = CBaseUnit::ISA((CBaseUnit *)this,0x36), cVar3 == '\0')) &&
       ((cVar3 = CBaseUnit::ISA((CBaseUnit *)this,8), cVar3 != '\0' ||
        (((cVar3 = CBaseUnit::ISA((CBaseUnit *)this,0xd), cVar3 != '\0' ||
          (cVar3 = CBaseUnit::ISA((CBaseUnit *)this,0x11), cVar3 != '\0')) ||
         (cVar3 = CBaseUnit::ISA((CBaseUnit *)this,0x18), cVar3 != '\0')))))) {
      fVar7 = (float)UTILITIES::randomBetweenVolatile(0.0,DAT_00fa871c);
      lVar5 = CGameGlobals::getSingleton();
      *(uint *)(this + 0x3e0) = (fVar7 < fVar8 * *(float *)(lVar5 + 0x2c)) + 1;
    }
  }
  if (this[0x348] == (CEquipment)0x0) {
                    /* try { // try from 00884792 to 008847ac has its CatchHandler @ 008849fd */
    std::wstring::wstring((wstring_conflict *)&local_28,L"ALWAYS_IDENTIFIED",&local_19);
    cVar3 = CDataGroup::GetDataValue
                      (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)&local_28,false);
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
    if (cVar3 != '\0') {
      this[0x348] = (CEquipment)0x1;
    }
  }
  recalculatePrice(this);
  return;
}



/* address=00884a20
   symbol=CEquipment::addedToInventory */

/* CEquipment::addedToInventory(CInventory*, CCharacter*) */

void __thiscall
CEquipment::addedToInventory(CEquipment *this,CInventory *param_1,CCharacter *param_2)

{
  char cVar1;
  long lVar2;
  long lVar3;

  if ((*(CInventory **)(this + 0x240) != (CInventory *)0x0) &&
     (param_1 != *(CInventory **)(this + 0x240))) {
    lVar2 = *(long *)(this + 0x68);
    lVar3 = 0;
    if (*(int *)(lVar2 + 0x30) != 0) {
      lVar3 = **(long **)(lVar2 + 0x28);
    }
    if (*(long *)(lVar3 + 0x58) != 0) {
      lVar3 = 0;
      if (*(int *)(lVar2 + 0x30) != 0) {
        lVar3 = **(long **)(lVar2 + 0x28);
      }
      CBaseUnit::questEventFire(this,5,*(undefined8 *)(lVar3 + 0x58),this);
    }
  }
  if (this[0x25d] != (CEquipment)0x0) {
    lVar2 = *(long *)(this + 0x68);
    lVar3 = 0;
    if (*(int *)(lVar2 + 0x30) != 0) {
      lVar3 = **(long **)(lVar2 + 0x28);
    }
    if (*(long *)(lVar3 + 0x78) != 0) {
      *(CInventory **)(this + 0x240) = param_1;
      lVar3 = 0;
      if (*(int *)(lVar2 + 0x30) != 0) {
        lVar3 = **(long **)(lVar2 + 0x28);
      }
      createIcon(this,*(CGameUI **)(lVar3 + 0x78),true);
      recalculatePrice(this);
      goto LAB_00884ad7;
    }
  }
  *(CInventory **)(this + 0x240) = param_1;
LAB_00884ad7:
  (**(code **)(*(long *)this + 0x18))(this,*(undefined8 *)(param_2 + 0x10));
  CBaseUnit::broadcastUnitState((CBaseUnit *)this,3);
  cVar1 = CBaseUnit::ISA((CBaseUnit *)param_2,0x1c);
  if ((cVar1 != '\0') ||
     ((*(CBaseUnit **)(param_2 + 0x640) != (CBaseUnit *)0x0 &&
      (cVar1 = CBaseUnit::ISA(*(CBaseUnit **)(param_2 + 0x640),0x1c), cVar1 != '\0')))) {
    lVar2 = 0;
    if (*(int *)(*(long *)(this + 0x68) + 0x30) != 0) {
      lVar2 = **(long **)(*(long *)(this + 0x68) + 0x28);
    }
    CBaseUnit::questEventFire(this,0,*(undefined8 *)(lVar2 + 0x58),this);
  }
  (**(code **)(*(long *)this + 0x30))(this);
  this[0x1f2] = (CEquipment)0x1;
  if (*(CEditorScene **)(this + 0x48) != (CEditorScene *)0x0) {
    CEditorScene::RemoveObjectInScene(*(CEditorScene **)(this + 0x48),(CEditorBaseObject *)this);
  }
  if (*(CParticle **)(this + 0x3d0) != (CParticle *)0x0) {
    CParticle::Stop(*(CParticle **)(this + 0x3d0),false);
  }
  resetVisualLayout(this);
  return;
}



/* address=00884ba0
   symbol=CEquipment::getFullItemName */

/* WARNING: Removing unreachable block (ram,0x00885a4e) */
/* WARNING: Removing unreachable block (ram,0x00885982) */
/* WARNING: Removing unreachable block (ram,0x0088592b) */
/* WARNING: Removing unreachable block (ram,0x0088575f) */
/* WARNING: Removing unreachable block (ram,0x00885920) */
/* WARNING: Removing unreachable block (ram,0x00885a17) */
/* WARNING: Removing unreachable block (ram,0x00885a0c) */
/* WARNING: Removing unreachable block (ram,0x00885a5e) */
/* WARNING: Removing unreachable block (ram,0x008857f1) */
/* WARNING: Removing unreachable block (ram,0x00885864) */
/* WARNING: Removing unreachable block (ram,0x0088586f) */
/* WARNING: Removing unreachable block (ram,0x00885856) */
/* WARNING: Removing unreachable block (ram,0x008857e6) */
/* WARNING: Removing unreachable block (ram,0x008858ba) */
/* CEquipment::getFullItemName(bool) */

wstring_conflict * CEquipment::getFullItemName(bool param_1)

{
  allocator *paVar1;
  int *piVar2;
  wchar_t wVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  long lVar9;
  long *plVar10;
  char in_DL;
  ulong uVar11;
  uint uVar12;
  size_t sVar13;
  long lVar14;
  size_t sVar15;
  CBaseUnit *in_RSI;
  undefined7 in_register_00000039;
  wstring_conflict *this;
  char *pcVar16;
  wchar_t *pwVar17;
  ulong uVar18;
  wchar_t *__s2;
  bool bVar19;
  ulong local_158 [2];
  wchar_t *local_148 [2];
  long local_138 [2];
  long local_128 [2];
  long local_118 [2];
  long local_108 [2];
  long local_f8 [2];
  long local_e8 [2];
  long local_d8 [2];
  wchar_t *local_c8 [2];
  wchar_t *local_b8 [2];
  long local_a8;
  wstring_conflict local_98 [16];
  STRINGS local_88 [16];
  wstring_conflict local_78 [16];
  wchar_t *local_68 [2];
  long local_58 [3];
  allocator local_3a;
  allocator local_39 [9];

  this = (wstring_conflict *)CONCAT71(in_register_00000039,param_1);
  if (((in_DL == '\0') && (in_RSI[0x348] == (CBaseUnit)0x0)) &&
     (*(long *)(*(long *)(in_RSI + 0x2d0) + -0x18) != 0)) {
    std::wstring::wstring(this,(wstring_conflict *)(in_RSI + 0x2d0));
  }
  else {
    std::wstring::wstring((wstring_conflict *)local_58,(wstring_conflict *)(in_RSI + 0x210));
    wcslen(L"{");
                    /* try { // try from 00884c03 to 00884c43 has its CatchHandler @ 00885784 */
    iVar5 = std::wstring::find((wchar_t *)local_58,0xfa3b9c,0);
    wcslen(L"}");
    iVar6 = std::wstring::find((wchar_t *)local_58,0xfa3bac,(long)iVar5);
    std::wstring::wstring((wstring_conflict *)local_68,(wstring_conflict *)&::EMPTY_WSTRING);
    if (((iVar6 != -1) && (iVar5 != -1)) && (iVar5 + 1 < iVar6)) {
      std::wstring::substr((ulong)local_78,(ulong)local_58);
                    /* try { // try from 00884d26 to 00884d2a has its CatchHandler @ 0088577f */
      STRINGS::StringUpper(local_88,local_78);
                    /* try { // try from 00884d36 to 00884d3a has its CatchHandler @ 0088576a */
      std::wstring::assign((wstring_conflict *)local_68);
                    /* try { // try from 00884d3e to 00884d42 has its CatchHandler @ 0088577f */
      std::wstring::~wstring((wstring_conflict *)local_88);
                    /* try { // try from 00884d46 to 00884d93 has its CatchHandler @ 008857b5 */
      std::wstring::~wstring(local_78);
      wcslen(L"");
      std::wstring::replace
                ((ulong)local_58,(long)iVar5,(wchar_t *)(long)((iVar6 - iVar5) + 1),0x1001608);
      std::wstring::substr((ulong)local_98,(ulong)local_68);
                    /* try { // try from 00884d9f to 00884da3 has its CatchHandler @ 00885732 */
      std::wstring::assign((wstring_conflict *)local_68);
                    /* try { // try from 00884da7 to 00884dab has its CatchHandler @ 008857b5 */
      std::wstring::~wstring(local_98);
    }
                    /* try { // try from 00884c6a to 00884c6e has its CatchHandler @ 008857fc */
    if (((in_DL != '\0') || (in_RSI[0x348] != (CBaseUnit)0x0)) &&
       (cVar4 = CBaseUnit::ISA(in_RSI,0x36), cVar4 == '\0')) {
                    /* try { // try from 00884de8 to 00884dec has its CatchHandler @ 008857fc */
      getSet();
      pcVar16 = (char *)(local_a8 + -0x18);
      uVar7 = (uint)(*(long *)(local_a8 + -0x18) == 0);
      if ((allocator *)pcVar16 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
      goto LAB_00885706;
      do {
        if (((char)uVar7 == '\0') || (*(long *)(in_RSI + 0x1b8) == 0)) break;
                    /* try { // try from 00884e40 to 00884e44 has its CatchHandler @ 008857b5 */
        std::wstring::wstring((wstring_conflict *)local_b8,(wstring_conflict *)(in_RSI + 0x2e0));
                    /* try { // try from 00884e60 to 00884e64 has its CatchHandler @ 0088587a */
        std::wstring::wstring((wstring_conflict *)local_c8,(wstring_conflict *)(in_RSI + 0x2e8));
        lVar14 = *(long *)(in_RSI + 0x1b8);
        uVar7 = *(uint *)(lVar14 + 0x18);
        pwVar17 = ::EMPTY_WSTRING;
        if (uVar7 != 0) {
          uVar12 = 0;
          iVar5 = -1;
          sVar15 = *(size_t *)(::EMPTY_WSTRING + -6);
          __s2 = ::EMPTY_WSTRING;
          if (uVar7 != 0) goto LAB_00884f78;
          if (uRam0000000000000074 < 0x80000000) goto LAB_00884f91;
          do {
            uVar7 = *(uint *)(lVar14 + 0x18);
            sVar13 = *(size_t *)(__s2 + -6);
            pwVar17 = __s2;
LAB_00884eb2:
            lVar9 = 0;
            if (uVar12 < uVar7) {
              if (uVar12 < *(uint *)(lVar14 + 0x1c)) {
                plVar10 = (long *)((ulong)uVar12 * 8 + *(long *)(lVar14 + 0x10));
              }
              else {
                plVar10 = *(long **)(lVar14 + 0x10);
              }
              lVar9 = *plVar10;
            }
            if (*(int *)(lVar9 + 0x74) < 0) {
LAB_00884f65:
              pwVar17 = __s2;
              uVar12 = uVar12 + 1;
              sVar15 = *(size_t *)(pwVar17 + -6);
              __s2 = pwVar17;
              if (uVar7 <= uVar12) goto LAB_00885080;
            }
            else {
              lVar9 = 0;
              if (uVar12 < uVar7) {
                if (uVar12 < *(uint *)(lVar14 + 0x1c)) {
                  plVar10 = (long *)((ulong)uVar12 * 8 + *(long *)(lVar14 + 0x10));
                }
                else {
                  plVar10 = *(long **)(lVar14 + 0x10);
                }
                lVar9 = *plVar10;
              }
              sVar15 = *(size_t *)(*(wchar_t **)(lVar9 + 0x60) + -6);
              if ((sVar15 != sVar13) ||
                 (iVar6 = wmemcmp(*(wchar_t **)(lVar9 + 0x60),__s2,sVar13), iVar6 != 0)) {
                lVar9 = 0;
                if (uVar12 < uVar7) {
                  if (uVar12 < *(uint *)(lVar14 + 0x1c)) {
                    plVar10 = (long *)((ulong)uVar12 * 8 + *(long *)(lVar14 + 0x10));
                  }
                  else {
                    plVar10 = *(long **)(lVar14 + 0x10);
                  }
                  lVar9 = *plVar10;
                }
                pwVar17 = *(wchar_t **)(lVar9 + 0x60);
                wcslen(pwVar17);
                    /* try { // try from 00884f2f to 00884fee has its CatchHandler @ 0088599f */
                std::wstring::assign((wchar_t *)local_c8,(ulong)pwVar17);
                lVar9 = 0;
                lVar14 = *(long *)(in_RSI + 0x1b8);
                uVar7 = *(uint *)(lVar14 + 0x18);
                if (uVar12 < uVar7) {
                  if (uVar12 < *(uint *)(lVar14 + 0x1c)) {
                    plVar10 = (long *)((ulong)uVar12 * 8 + *(long *)(lVar14 + 0x10));
                  }
                  else {
                    plVar10 = *(long **)(lVar14 + 0x10);
                  }
                  lVar9 = *plVar10;
                }
                iVar5 = *(int *)(lVar9 + 0x74);
                __s2 = ::EMPTY_WSTRING;
                goto LAB_00884f65;
              }
              uVar12 = uVar12 + 1;
              if (uVar7 <= uVar12) goto LAB_00885080;
            }
LAB_00884f78:
            if (uVar12 < *(uint *)(lVar14 + 0x1c)) {
              plVar10 = (long *)((ulong)uVar12 * 8 + *(long *)(lVar14 + 0x10));
            }
            else {
              plVar10 = *(long **)(lVar14 + 0x10);
            }
          } while (*(int *)(*plVar10 + 0x74) <= iVar5);
LAB_00884f91:
          lVar9 = 0;
          if (uVar12 < uVar7) {
            if (uVar12 < *(uint *)(lVar14 + 0x1c)) {
              plVar10 = (long *)((ulong)uVar12 * 8 + *(long *)(lVar14 + 0x10));
            }
            else {
              plVar10 = *(long **)(lVar14 + 0x10);
            }
            lVar9 = *plVar10;
          }
          sVar13 = *(size_t *)(*(wchar_t **)(lVar9 + 0x58) + -6);
          if ((sVar13 == sVar15) &&
             (iVar6 = wmemcmp(*(wchar_t **)(lVar9 + 0x58),__s2,sVar15), iVar6 == 0)) {
            uVar7 = *(uint *)(lVar14 + 0x18);
          }
          else {
            lVar9 = 0;
            if (uVar12 < uVar7) {
              if (uVar12 < *(uint *)(lVar14 + 0x1c)) {
                plVar10 = (long *)((ulong)uVar12 * 8 + *(long *)(lVar14 + 0x10));
              }
              else {
                plVar10 = *(long **)(lVar14 + 0x10);
              }
              lVar9 = *plVar10;
            }
            pwVar17 = *(wchar_t **)(lVar9 + 0x58);
            wcslen(pwVar17);
            std::wstring::assign((wchar_t *)local_b8,(ulong)pwVar17);
            lVar14 = *(long *)(in_RSI + 0x1b8);
            lVar9 = 0;
            uVar7 = *(uint *)(lVar14 + 0x18);
            if (uVar12 < uVar7) {
              if (uVar12 < *(uint *)(lVar14 + 0x1c)) {
                plVar10 = (long *)((ulong)uVar12 * 8 + *(long *)(lVar14 + 0x10));
              }
              else {
                plVar10 = *(long **)(lVar14 + 0x10);
              }
              lVar9 = *plVar10;
            }
            iVar5 = *(int *)(lVar9 + 0x74);
            sVar13 = *(size_t *)(::EMPTY_WSTRING + -6);
            pwVar17 = ::EMPTY_WSTRING;
            __s2 = ::EMPTY_WSTRING;
          }
          goto LAB_00884eb2;
        }
        sVar15 = *(size_t *)(::EMPTY_WSTRING + -6);
LAB_00885080:
        sVar13 = *(size_t *)(local_b8[0] + -6);
        if ((sVar13 != sVar15) || (iVar5 = wmemcmp(local_b8[0],pwVar17,sVar15), iVar5 != 0)) {
                    /* try { // try from 008850ad to 008850b1 has its CatchHandler @ 00885997 */
          std::wstring::wstring((wstring_conflict *)local_e8,L"[ITEM]",local_39);
                    /* try { // try from 008850c5 to 008850c9 has its CatchHandler @ 00885992 */
          std::wstring::wstring((wstring_conflict *)local_d8,(wstring_conflict *)local_b8);
                    /* try { // try from 008850e3 to 008850e7 has its CatchHandler @ 0088598d */
          STRINGS::replaceWString
                    ((STRINGS *)local_f8,(wstring_conflict *)local_d8,(wstring_conflict *)local_e8,
                     local_58);
                    /* try { // try from 008850f3 to 008850f7 has its CatchHandler @ 00885962 */
          std::wstring::assign((wstring_conflict *)local_58);
          if ((allocator *)(local_f8[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_f8[0] + -8);
            iVar5 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar5 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
            }
          }
          if ((allocator *)(local_d8[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_d8[0] + -8);
            iVar5 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar5 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
            }
          }
          if ((allocator *)(local_e8[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_e8[0] + -8);
            iVar5 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar5 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
            }
          }
                    /* try { // try from 00885153 to 00885157 has its CatchHandler @ 0088599f */
          std::wstring::assign((wstring_conflict *)(in_RSI + 0x2e0));
          sVar13 = *(size_t *)(::EMPTY_WSTRING + -6);
          pwVar17 = ::EMPTY_WSTRING;
        }
        sVar15 = *(size_t *)(local_c8[0] + -6);
        if ((sVar15 != sVar13) || (iVar5 = wmemcmp(local_c8[0],pwVar17,sVar13), iVar5 != 0)) {
                    /* try { // try from 0088518d to 00885191 has its CatchHandler @ 008859b2 */
          std::wstring::wstring((wstring_conflict *)local_118,L"[ITEM]",&local_3a);
                    /* try { // try from 008851a5 to 008851a9 has its CatchHandler @ 008859a6 */
          std::wstring::wstring((wstring_conflict *)local_108,(wstring_conflict *)local_c8);
                    /* try { // try from 008851c0 to 008851c4 has its CatchHandler @ 008859a4 */
          STRINGS::replaceWString
                    ((STRINGS *)local_128,(wstring_conflict *)local_108,
                     (wstring_conflict *)local_118,local_58);
                    /* try { // try from 008851d0 to 008851d4 has its CatchHandler @ 008859a2 */
          std::wstring::assign((wstring_conflict *)local_58);
          if ((allocator *)(local_128[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_128[0] + -8);
            iVar5 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar5 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_128[0] + -0x18));
            }
          }
          if ((allocator *)(local_108[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_108[0] + -8);
            iVar5 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar5 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_108[0] + -0x18));
            }
          }
          if ((allocator *)(local_118[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_118[0] + -8);
            iVar5 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar5 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_118[0] + -0x18));
            }
          }
                    /* try { // try from 0088522a to 00885293 has its CatchHandler @ 0088599f */
          std::wstring::assign((wstring_conflict *)(in_RSI + 0x2e8));
          sVar15 = *(size_t *)(::EMPTY_WSTRING + -6);
          pwVar17 = ::EMPTY_WSTRING;
        }
        if ((*(size_t *)(local_68[0] + -6) == sVar15) &&
           (iVar5 = wmemcmp(local_68[0],pwVar17,sVar15), iVar5 == 0)) {
LAB_008855bc:
          if ((allocator *)(local_c8[0] + -6) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            pwVar17 = local_c8[0] + -2;
            wVar3 = *pwVar17;
            *pwVar17 = *pwVar17 + L'\xffffffff';
            UNLOCK();
            if (wVar3 < L'\x01') {
              std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -6));
            }
          }
          if ((allocator *)(local_b8[0] + -6) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            pwVar17 = local_b8[0] + -2;
            wVar3 = *pwVar17;
            *pwVar17 = *pwVar17 + L'\xffffffff';
            UNLOCK();
            if (wVar3 < L'\x01') {
              std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -6));
            }
          }
          break;
        }
        wcslen(L"{");
        uVar7 = std::wstring::find((wchar_t *)local_58,0xfa3b9c,0);
        wcslen(L"}");
        uVar18 = (ulong)(int)uVar7;
        iVar5 = std::wstring::find((wchar_t *)local_58,0xfa3bac,uVar18);
        if ((uVar7 == 0xffffffff) || (iVar5 == -1)) goto LAB_008855bc;
        uVar11 = (ulong)(int)(uVar7 + 1);
        if (uVar11 <= *(ulong *)(local_58[0] + -0x18)) {
          do {
                    /* try { // try from 008853e9 to 008853ed has its CatchHandler @ 0088599f */
            std::wstring::wstring
                      ((wstring_conflict *)local_138,(wstring_conflict *)local_58,uVar11,
                       (long)(int)((iVar5 - uVar7) + -1));
                    /* try { // try from 008853f8 to 0088544a has its CatchHandler @ 008858b5 */
            STRINGS::StringUpper((STRINGS *)local_148,(wstring_conflict *)local_138);
            pwVar17 = local_148[0];
            bVar19 = false;
            paVar1 = (allocator *)(local_148[0] + -6);
            if (*(size_t *)(local_68[0] + -6) == *(size_t *)(local_148[0] + -6)) {
              iVar6 = wmemcmp(local_68[0],local_148[0],*(size_t *)(local_68[0] + -6));
              bVar19 = iVar6 == 0;
            }
            if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              pwVar17 = pwVar17 + -2;
              wVar3 = *pwVar17;
              *pwVar17 = *pwVar17 + L'\xffffffff';
              UNLOCK();
              if (wVar3 < L'\x01') {
                std::wstring::_Rep::_M_destroy(paVar1);
              }
            }
            if (!bVar19) {
              if ((ulong)(long)iVar5 < *(long *)(local_58[0] + -0x18) - 2U) {
                wcslen(L"}");
                    /* try { // try from 00885304 to 0088538b has its CatchHandler @ 008858b5 */
                iVar5 = std::wstring::find((wchar_t *)local_58,0xfa3bac,(long)(iVar5 + 1));
                if (iVar5 != -1) {
                  wcslen(L"");
                  std::wstring::replace
                            ((ulong)local_58,uVar18,(wchar_t *)(long)(int)((1 - uVar7) + iVar5),
                             0x1001608);
                  goto LAB_00885344;
                }
              }
LAB_008855b2:
                    /* try { // try from 008855b7 to 00885705 has its CatchHandler @ 0088599f */
              std::wstring::~wstring((wstring_conflict *)local_138);
              goto LAB_008855bc;
            }
            std::operator+((wchar_t *)local_158,(wstring_conflict *)&DAT_00fd0920);
                    /* try { // try from 0088545f to 00885463 has its CatchHandler @ 0088588f */
            iVar6 = std::wstring::find((wchar_t *)local_58,local_158[0],(long)iVar5);
            if ((allocator *)(local_158[0] - 0x18) !=
                (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar2 = (int *)(local_158[0] - 8);
              iVar8 = *piVar2;
              *piVar2 = *piVar2 + -1;
              UNLOCK();
              if (iVar8 < 1) {
                std::wstring::_Rep::_M_destroy((allocator *)(local_158[0] - 0x18));
              }
            }
            wcslen(L"}");
                    /* try { // try from 0088549d to 00885504 has its CatchHandler @ 008858b5 */
            iVar8 = std::wstring::find((wchar_t *)local_58,0xfa3bac,(long)(iVar6 + 1));
            if (iVar6 == -1) goto LAB_008855b2;
            wcslen(L"");
            std::wstring::replace
                      ((ulong)local_58,(long)iVar6,(wchar_t *)(long)((1 - iVar6) + iVar8),0x1001608)
            ;
            wcslen(L"");
            std::wstring::replace
                      ((ulong)local_58,uVar18,(wchar_t *)(long)(int)((iVar5 - uVar7) + 1),0x1001608)
            ;
LAB_00885344:
            wcslen(L"{");
            uVar7 = std::wstring::find((wchar_t *)local_58,0xfa3b9c,0);
            wcslen(L"}");
            uVar18 = (ulong)(int)uVar7;
            iVar5 = std::wstring::find((wchar_t *)local_58,0xfa3bac,uVar18);
            if ((allocator *)(local_138[0] + -0x18) !=
                (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar2 = (int *)(local_138[0] + -8);
              iVar6 = *piVar2;
              *piVar2 = *piVar2 + -1;
              UNLOCK();
              if (iVar6 < 1) {
                std::wstring::_Rep::_M_destroy((allocator *)(local_138[0] + -0x18));
              }
            }
            if ((uVar7 == 0xffffffff) || (iVar5 == -1)) goto LAB_008855bc;
            uVar11 = (ulong)(int)(uVar7 + 1);
          } while (uVar11 <= *(ulong *)(local_58[0] + -0x18));
        }
        pcVar16 = "basic_string::substr";
        std::__throw_out_of_range("basic_string::substr");
LAB_00885706:
        LOCK();
        paVar1 = (allocator *)(pcVar16 + 0x10);
        iVar5 = *(int *)paVar1;
        *(int *)paVar1 = *(int *)paVar1 + -1;
        UNLOCK();
        if (iVar5 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)pcVar16);
        }
      } while( true );
    }
                    /* try { // try from 00884c84 to 00884d17 has its CatchHandler @ 008857b5 */
    std::wstring::wstring(this,(wstring_conflict *)local_58);
    if ((allocator *)(local_68[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      pwVar17 = local_68[0] + -2;
      wVar3 = *pwVar17;
      *pwVar17 = *pwVar17 + L'\xffffffff';
      UNLOCK();
      if (wVar3 < L'\x01') {
        std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -6));
      }
    }
    if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar2 = (int *)(local_58[0] + -8);
      iVar5 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
      }
    }
  }
  return this;
}



/* address=00885a70
   symbol=CEquipment::createParticles */

/* WARNING: Removing unreachable block (ram,0x008860c8) */
/* WARNING: Removing unreachable block (ram,0x0088608e) */
/* WARNING: Removing unreachable block (ram,0x008860ec) */
/* CEquipment::createParticles() */

void __thiscall CEquipment::createParticles(CEquipment *this)

{
  wchar_t *pwVar1;
  wchar_t wVar2;
  size_t __n;
  char cVar3;
  int iVar4;
  int iVar5;
  undefined8 uVar6;
  CSceneNodeObject *pCVar7;
  long lVar8;
  int iVar9;
  bool bVar10;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  wchar_t *local_78 [2];
  wchar_t *local_68 [2];
  wchar_t *local_58 [2];
  wchar_t *local_48 [2];
  wstring_conflict local_38 [16];

  __n = *(size_t *)(*(wchar_t **)(this + 0x3d8) + -6);
  if ((__n == *(size_t *)(::EMPTY_WSTRING + -6)) &&
     (iVar5 = wmemcmp(*(wchar_t **)(this + 0x3d8),::EMPTY_WSTRING,__n), iVar5 == 0)) {
    std::wstring::wstring((wstring_conflict *)local_48,(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 00885d2b to 00885d51 has its CatchHandler @ 008860ea */
    cVar3 = CBaseUnit::getIsQuestUnit((CBaseUnit *)this);
    if (cVar3 == '\0') {
                    /* try { // try from 00885e88 to 00885ea1 has its CatchHandler @ 008860ea */
      cVar3 = CBaseUnit::ISA((CBaseUnit *)this,0x36);
      if (cVar3 == '\0') {
                    /* try { // try from 00885f56 to 00885f6c has its CatchHandler @ 008860ea */
        cVar3 = (**(code **)(*(long *)this + 0x2b0))(this);
        if (cVar3 == '\0') {
                    /* try { // try from 00885fe0 to 00885fe4 has its CatchHandler @ 008860ea */
          std::wstring::assign((wchar_t *)local_48);
        }
        else {
          std::wstring::assign((wchar_t *)local_48);
        }
      }
      else {
        std::wstring::assign((wchar_t *)local_48);
      }
    }
    else {
      wcslen(L"QUEST_ITEM");
      std::wstring::assign((wchar_t *)local_48,0xfd0000);
    }
    if (*(long *)(this + 0x3d0) == 0) {
LAB_00885db9:
      uVar6 = CResourceManager::createParticle(*(CResourceManager **)(this + 0x68),local_48[0]);
      *(undefined8 *)(this + 0x3d0) = uVar6;
    }
    else {
                    /* try { // try from 00885d6d to 00885d71 has its CatchHandler @ 008860d7 */
      STRINGS::StringUpper
                ((STRINGS *)local_58,(wstring_conflict *)(*(long *)(this + 0x3d0) + 0x110));
      bVar10 = true;
      if (*(size_t *)(local_58[0] + -6) == *(size_t *)(local_48[0] + -6)) {
        iVar5 = wmemcmp(local_58[0],local_48[0],*(size_t *)(local_58[0] + -6));
        bVar10 = iVar5 != 0;
      }
                    /* try { // try from 00885d92 to 00885dc6 has its CatchHandler @ 008860ea */
      std::wstring::~wstring((wstring_conflict *)local_58);
      if (bVar10) {
        if (*(long **)(this + 0x3d0) != (long *)0x0) {
          (**(code **)(**(long **)(this + 0x3d0) + 8))();
          *(undefined8 *)(this + 0x3d0) = 0;
        }
        goto LAB_00885db9;
      }
    }
    if ((allocator *)(local_48[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      pwVar1 = local_48[0] + -2;
      wVar2 = *pwVar1;
      *pwVar1 = *pwVar1 + L'\xffffffff';
      UNLOCK();
      if (wVar2 < L'\x01') {
        std::wstring::_Rep::_M_destroy((allocator *)(local_48[0] + -6));
      }
    }
    pCVar7 = *(CSceneNodeObject **)(this + 0x3d0);
LAB_00885deb:
    if (pCVar7 != (CSceneNodeObject *)0x0) goto LAB_00885abf;
  }
  else {
    pCVar7 = *(CSceneNodeObject **)(this + 0x3d0);
    if (pCVar7 == (CSceneNodeObject *)0x0) {
      std::wstring::wstring(local_38,(wstring_conflict *)(this + 0x3d8));
                    /* try { // try from 00886004 to 00886017 has its CatchHandler @ 008860fa */
      lVar8 = CMasterResourceManager::getSingleton();
      CParticlePreloader::LoadParticle(*(CParticlePreloader **)(lVar8 + 0xf8),local_38);
      std::wstring::~wstring(local_38);
      pCVar7 = (CSceneNodeObject *)
               CResourceManager::createParticle
                         (*(CResourceManager **)(this + 0x68),*(wchar_t **)(this + 0x3d8));
      *(CSceneNodeObject **)(this + 0x3d0) = pCVar7;
      goto LAB_00885deb;
    }
LAB_00885abf:
    if (((this[0x81] != (CEquipment)0x0) && (*(long *)(this + 0x290) == 0)) &&
       (*(long *)(this + 0x2b0) != 0)) {
      CSceneNodeObject::sceneNodeSetParent
                (pCVar7,*(SceneNode **)(*(long *)(this + 0x2b0) + 0x58),false);
      local_88 = 0;
      local_84 = 0;
      local_80 = 0;
      CPositionableObject::setPosition(*(CPositionableObject **)(this + 0x3d0),(Vector3 *)&local_88)
      ;
      CParticle::Start();
    }
  }
  cVar3 = CBaseUnit::ISA((CBaseUnit *)this,8);
  if (cVar3 == '\0') {
    return;
  }
  iVar4 = getDamageBonus(this,4);
  iVar5 = 0;
  if (0 < iVar4) {
    iVar5 = iVar4;
  }
  iVar9 = (uint)(0 < iVar4) << 2;
  iVar4 = getDamageBonus(this,2);
  if (iVar5 < iVar4) {
    iVar9 = 2;
    iVar5 = iVar4;
  }
  iVar4 = getDamageBonus(this,3);
  if (iVar5 < iVar4) {
    iVar9 = 3;
    iVar5 = iVar4;
  }
  iVar4 = getDamageBonus(this,5);
  if (iVar5 < iVar4) {
    std::wstring::wstring((wstring_conflict *)local_68,(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 00885e1a to 00885e6a has its CatchHandler @ 0088607b */
    cVar3 = CBaseUnit::ISA((CBaseUnit *)this,0x5a);
    if (cVar3 == '\0') {
                    /* try { // try from 00886048 to 0088604c has its CatchHandler @ 0088607b */
      std::wstring::assign((wchar_t *)local_68);
    }
    else {
      std::wstring::assign((wchar_t *)local_68);
    }
  }
  else {
    std::wstring::wstring((wstring_conflict *)local_68,(wstring_conflict *)&::EMPTY_WSTRING);
    if (iVar9 == 3) {
      cVar3 = CBaseUnit::ISA((CBaseUnit *)this,0x5a);
      if (cVar3 == '\0') {
                    /* try { // try from 00885f98 to 00885fcc has its CatchHandler @ 0088607b */
        std::wstring::assign((wchar_t *)local_68);
      }
      else {
        std::wstring::assign((wchar_t *)local_68);
      }
    }
    else if (iVar9 == 4) {
      cVar3 = CBaseUnit::ISA((CBaseUnit *)this,0x5a);
      if (cVar3 == '\0') {
        std::wstring::assign((wchar_t *)local_68);
      }
      else {
        std::wstring::assign((wchar_t *)local_68);
      }
    }
    else if (iVar9 == 2) {
                    /* try { // try from 00885eb8 to 00885f2d has its CatchHandler @ 0088607b */
      cVar3 = CBaseUnit::ISA((CBaseUnit *)this,0x5a);
      if (cVar3 == '\0') {
        std::wstring::assign((wchar_t *)local_68);
      }
      else {
        std::wstring::assign((wchar_t *)local_68);
      }
    }
  }
  if (*(long *)(this + 0x3c8) != 0) {
                    /* try { // try from 00885c2c to 00885c30 has its CatchHandler @ 008860c6 */
    STRINGS::StringUpper((STRINGS *)local_78,(wstring_conflict *)(*(long *)(this + 0x3c8) + 0x110));
    bVar10 = true;
    if (*(size_t *)(local_78[0] + -6) == *(size_t *)(local_68[0] + -6)) {
      iVar5 = wmemcmp(local_78[0],local_68[0],*(size_t *)(local_78[0] + -6));
      bVar10 = iVar5 != 0;
    }
    if ((allocator *)(local_78[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      pwVar1 = local_78[0] + -2;
      wVar2 = *pwVar1;
      *pwVar1 = *pwVar1 + L'\xffffffff';
      UNLOCK();
      if (wVar2 < L'\x01') {
        std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -6));
      }
    }
    if (!bVar10) {
      pCVar7 = *(CSceneNodeObject **)(this + 0x3c8);
      goto LAB_00885c72;
    }
    if (*(long **)(this + 0x3c8) != (long *)0x0) {
      (**(code **)(**(long **)(this + 0x3c8) + 8))();
      *(undefined8 *)(this + 0x3c8) = 0;
    }
  }
  pCVar7 = (CSceneNodeObject *)
           CResourceManager::createParticle(*(CResourceManager **)(this + 0x68),local_68[0]);
  *(CSceneNodeObject **)(this + 0x3c8) = pCVar7;
LAB_00885c72:
  if ((pCVar7 != (CSceneNodeObject *)0x0) && (*(long *)(this + 0x2b0) != 0)) {
                    /* try { // try from 00885c89 to 00885cbf has its CatchHandler @ 0088607b */
    CSceneNodeObject::sceneNodeSetParent
              (pCVar7,*(SceneNode **)(*(long *)(this + 0x2b0) + 0x58),false);
    local_98 = 0;
    local_94 = 0;
    local_90 = 0;
    CPositionableObject::setPosition(*(CPositionableObject **)(this + 0x3c8),(Vector3 *)&local_98);
    CParticle::Start();
  }
  if ((allocator *)(local_68[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    pwVar1 = local_68[0] + -2;
    wVar2 = *pwVar1;
    *pwVar1 = *pwVar1 + L'\xffffffff';
    UNLOCK();
    if (wVar2 < L'\x01') {
      std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -6));
    }
  }
  return;
}



/* address=00886100
   symbol=CEquipment::setActiveInLevel */

/* CEquipment::setActiveInLevel(bool) */

void __thiscall CEquipment::setActiveInLevel(CEquipment *this,bool param_1)

{
  CParticle *this_00;
  SceneNode *pSVar1;
  CSceneNodeObject *this_01;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;

  detachFromLocation(this);
  (**(code **)(*(long *)this + 0x2c0))(this,param_1,1);
  CBaseUnit::updateCullingBounds();
  if (param_1) {
    createParticles(this);
    if (*(long *)(this + 0x2b0) != 0) {
      CItem::snapToGround();
    }
    if (((*(long *)(this + 0x3c8) != 0) && (*(long *)(this + 0x2b0) != 0)) &&
       (pSVar1 = *(SceneNode **)(*(long *)(this + 0x3c8) + 0x58), pSVar1 != (SceneNode *)0x0)) {
      OGRE_UTILITIES::removeChildFromParentNode(pSVar1);
      (**(code **)(**(long **)(*(long *)(this + 0x2b0) + 0x58) + 0x1a8))
                (*(long **)(*(long *)(this + 0x2b0) + 0x58),
                 *(undefined8 *)(*(long *)(this + 0x3c8) + 0x58));
    }
    this_01 = *(CSceneNodeObject **)(this + 0x3d0);
    if (((this_01 != (CSceneNodeObject *)0x0) && (*(long *)(this + 0x2b0) != 0)) &&
       (*(long *)(this_01 + 0x58) != 0)) {
      CSceneNodeObject::sceneNodeSetParent
                (this_01,*(SceneNode **)(*(long *)(this + 0x2b0) + 0x58),false);
      local_28 = 0;
      local_24 = 0;
      local_20 = 0;
      CPositionableObject::setPosition(*(CPositionableObject **)(this + 0x3d0),(Vector3 *)&local_28)
      ;
      CParticle::Start();
      return;
    }
  }
  else {
    this_00 = *(CParticle **)(this + 0x3d0);
    if (((this_00 != (CParticle *)0x0) && (*(long *)(this + 0x2b0) != 0)) &&
       (*(long *)(this_00 + 0x58) != 0)) {
      CParticle::Stop(this_00,false);
      OGRE_UTILITIES::removeChildFromParentNode(*(SceneNode **)(*(long *)(this + 0x3d0) + 0x58));
    }
    CItem::hideItemText((CItem *)this);
  }
  return;
}



/* address=00886240
   symbol=CEquipment::createElementalDamages */

/* CEquipment::createElementalDamages() */

void __thiscall CEquipment::createElementalDamages(CEquipment *this)

{
  uint uVar1;
  undefined4 uVar2;
  CEffectManager *this_00;
  char cVar3;
  long lVar4;
  long *plVar5;
  long *plVar6;
  uint uVar7;
  long lVar8;

  cVar3 = CBaseUnit::ISA((CBaseUnit *)this,8);
  if (cVar3 != '\0') {
    this_00 = *(CEffectManager **)(this + 0x1b8);
    if (this_00 != (CEffectManager *)0x0) {
      if (0 < *(int *)(this_00 + 0x30)) {
        lVar8 = 0;
        uVar7 = 0;
        do {
          while (uVar1 = *(uint *)(this_00 + 0x34), uVar1 <= uVar7) {
            plVar5 = *(long **)(this_00 + 0x28);
            if (*(int *)(*plVar5 + 0x1c) != 0x34) goto LAB_00886299;
LAB_008862d5:
            if (uVar7 < uVar1) {
              lVar4 = *(long *)((long)plVar5 + lVar8);
              uVar2 = *(undefined4 *)(lVar4 + 0x14);
            }
            else {
              lVar4 = *plVar5;
              uVar2 = *(undefined4 *)(lVar4 + 0x14);
            }
            addDamageBonus(this,uVar2,(int)*(float *)(lVar4 + 0xc0));
            if (uVar7 < *(uint *)(this_00 + 0x34)) {
              plVar5 = (long *)(lVar8 + *(long *)(this_00 + 0x28));
            }
            else {
              plVar5 = *(long **)(this_00 + 0x28);
            }
            uVar7 = uVar7 + 1;
            lVar8 = lVar8 + 8;
            *(undefined4 *)(*plVar5 + 0x24) = 0xc4610000;
            if (*(int *)(this_00 + 0x30) <= (int)uVar7) goto LAB_00886319;
          }
          plVar5 = *(long **)(this_00 + 0x28);
          if (*(int *)(*(long *)((long)plVar5 + lVar8) + 0x1c) == 0x34) goto LAB_008862d5;
LAB_00886299:
          plVar6 = (long *)((long)plVar5 + lVar8);
          if (uVar1 <= uVar7) {
            plVar6 = plVar5;
          }
          if (*(int *)(*plVar6 + 0x1c) == 10) goto LAB_008862d5;
          uVar7 = uVar7 + 1;
          lVar8 = lVar8 + 8;
        } while ((int)uVar7 < *(int *)(this_00 + 0x30));
      }
LAB_00886319:
      CEffectManager::deleteDeadEffects(this_00);
    }
    if (*(long *)(this + 0x290) != 0) {
      createParticles(this);
      return;
    }
  }
  return;
}



/* address=00886370
   symbol=CEquipment::clearDamageBonuses */

/* CEquipment::clearDamageBonuses() */

void __thiscall CEquipment::clearDamageBonuses(CEquipment *this)

{
  *(undefined8 *)(this + 0x358) = *(undefined8 *)(this + 0x350);
  *(undefined8 *)(this + 0x370) = *(undefined8 *)(this + 0x368);
  *(undefined8 *)(this + 0x388) = *(undefined8 *)(this + 0x380);
  createElementalDamages(this);
  CItem::destroyItemText((CItem *)this);
  return;
}



/* address=008863b0
   symbol=CEquipment::applySaveState */

/* CEquipment::applySaveState(CItemSaveState&) */

void __thiscall CEquipment::applySaveState(CEquipment *this,CItemSaveState *param_1)

{
  undefined4 uVar1;
  long lVar2;
  undefined4 *puVar3;
  long lVar4;
  CEquipment *pCVar5;
  CEffect *pCVar6;
  long lVar7;
  ulong uVar8;
  uint uVar9;
  long lVar10;
  int iVar11;
  undefined4 local_2c;

  CItem::applySaveState((CItem *)this,param_1);
  *(undefined4 *)(this + 0x28c) = *(undefined4 *)(param_1 + 0x28);
  *(undefined4 *)(this + 0x238) = *(undefined4 *)(param_1 + 0x68);
  *(CItemSaveState *)(this + 0x348) = param_1[0x75];
  std::wstring::assign((wstring_conflict *)(this + 0x2e8));
  std::wstring::assign((wstring_conflict *)(this + 0x2e0));
  *(undefined4 *)(this + 0x344) = *(undefined4 *)(param_1 + 0x6c);
  *(undefined4 *)(this + 0x3e0) = *(undefined4 *)(param_1 + 0x70);
  if (*(int *)(param_1 + 0x78) != -1) {
    *(int *)(this + 0x334) = *(int *)(param_1 + 0x78);
    *(undefined4 *)(this + 0x330) = *(undefined4 *)(param_1 + 0x78);
    *(undefined4 *)(this + 0x340) = *(undefined4 *)(param_1 + 0x78);
  }
  if (*(int *)(param_1 + 0x7c) != -1) {
    *(int *)(this + 0x338) = *(int *)(param_1 + 0x7c);
    *(undefined4 *)(this + 0x33c) = *(undefined4 *)(param_1 + 0x7c);
  }
  lVar7 = *(long *)(param_1 + 0x130);
  lVar4 = *(long *)(param_1 + 0x128);
  if (0 < (int)(lVar7 - lVar4 >> 3)) {
    lVar10 = 0;
    iVar11 = 0;
    do {
      lVar2 = *(long *)(*(long *)(lVar4 + lVar10) + 0x60);
      if (lVar2 != -1) {
        pCVar5 = (CEquipment *)0x0;
        lVar4 = CResourceManager::createUnit(*(CResourceManager **)(this + 0x68),lVar2,1,true,false)
        ;
        if (lVar4 != 0) {
          pCVar5 = (CEquipment *)__dynamic_cast(lVar4,&CBaseUnit::typeinfo,&typeinfo,0);
        }
        (**(code **)(*(long *)pCVar5 + 0x298))
                  (pCVar5,*(undefined8 *)(*(long *)(param_1 + 0x128) + lVar10));
        addContainerItem(this,pCVar5);
        lVar4 = *(long *)(param_1 + 0x128);
        lVar7 = *(long *)(param_1 + 0x130);
      }
      iVar11 = iVar11 + 1;
      lVar10 = lVar10 + 8;
    } while (iVar11 < (int)(lVar7 - lVar4 >> 3));
  }
  lVar4 = 0;
  do {
    lVar7 = *(long *)(param_1 + lVar4 + 0xe0);
    uVar8 = 0;
    if (*(long *)(param_1 + lVar4 + 0xe8) - lVar7 >> 3 != 0) {
      do {
        pCVar6 = *(CEffect **)(lVar7 + uVar8 * 8);
        uVar1 = *(undefined4 *)(pCVar6 + 0xc0);
        pCVar6 = (CEffect *)CBaseUnit::addNewEffect((CBaseUnit *)this,pCVar6);
        if (pCVar6 != (CEffect *)0x0) {
          *(undefined4 *)(pCVar6 + 0xc0) = uVar1;
          CBaseUnit::activateEffect((CBaseUnit *)this,pCVar6);
        }
        lVar7 = *(long *)(param_1 + lVar4 + 0xe0);
        uVar8 = (ulong)((int)uVar8 + 1);
      } while (uVar8 < (ulong)(*(long *)(param_1 + lVar4 + 0xe8) - lVar7 >> 3));
    }
    *(long *)(param_1 + lVar4 + 0xe8) = lVar7;
    lVar4 = lVar4 + 0x18;
  } while (lVar4 != 0x48);
  if (*(CEffectManager **)(this + 0x1b8) != (CEffectManager *)0x0) {
    CEffectManager::calculateEffectValues(*(CEffectManager **)(this + 0x1b8));
  }
  lVar4 = *(long *)(this + 0x368);
  lVar7 = *(long *)(this + 0x350);
  lVar10 = *(long *)(this + 0x358);
  *(long *)(this + 0x370) = lVar4;
  while ((ulong)(lVar4 - *(long *)(this + 0x368) >> 2) < (ulong)(lVar10 - lVar7 >> 2)) {
    puVar3 = *(undefined4 **)(this + 0x370);
    local_2c = 0;
    if (puVar3 == *(undefined4 **)(this + 0x378)) {
      std::vector<int,std::allocator<int>>::_M_insert_aux
                ((vector<int,std::allocator<int>> *)(this + 0x368),puVar3,&local_2c);
      lVar7 = *(long *)(this + 0x350);
      lVar10 = *(long *)(this + 0x358);
    }
    else {
      lVar4 = 0;
      if (puVar3 != (undefined4 *)0x0) {
        *puVar3 = 0;
        lVar4 = *(long *)(this + 0x370);
        lVar7 = *(long *)(this + 0x350);
        lVar10 = *(long *)(this + 0x358);
      }
      *(long *)(this + 0x370) = lVar4 + 4;
    }
    lVar4 = *(long *)(this + 0x370);
  }
  lVar4 = *(long *)(param_1 + 0x140);
  if (*(long *)(param_1 + 0x148) - lVar4 >> 2 != 0) {
    uVar8 = 0;
    uVar9 = 0;
    do {
      uVar9 = uVar9 + 1;
      addDamageBonus(this,*(undefined4 *)(lVar4 + uVar8 * 4),
                     *(undefined4 *)(*(long *)(param_1 + 0x158) + uVar8 * 4));
      lVar4 = *(long *)(param_1 + 0x140);
      uVar8 = (ulong)uVar9;
    } while (uVar8 < (ulong)(*(long *)(param_1 + 0x148) - lVar4 >> 2));
  }
  createElementalDamages(this);
  recalculatePrice(this);
  setRequirements(this);
  return;
}



/* address=008866e0
   symbol=CEquipment::addEnchant */

/* CEquipment::addEnchant(int, int, int) */

void __thiscall CEquipment::addEnchant(CEquipment *this,int param_1,int param_2,int param_3)

{
  char cVar1;
  uint uVar2;

  if (((*(long *)(this + 0x68) != 0) && (*(long *)(*(long *)(this + 0x68) + 0x18) != 0)) &&
     ((cVar1 = CBaseUnit::ISA((CBaseUnit *)this,8), cVar1 != '\0' ||
      (((cVar1 = CBaseUnit::ISA((CBaseUnit *)this,0xd), cVar1 != '\0' ||
        (cVar1 = CBaseUnit::ISA((CBaseUnit *)this,0x11), cVar1 != '\0')) ||
       (cVar1 = CBaseUnit::ISA((CBaseUnit *)this,0x18), cVar1 != '\0')))))) {
    uVar2 = UTILITIES::randomIntegerBetweenVolatile(param_2,param_3);
    CResourceManager::createAffixesForUnit
              (*(CResourceManager **)(this + 0x68),(CBaseUnit *)this,param_1,uVar2);
  }
  if (*(CEffectManager **)(this + 0x1b8) != (CEffectManager *)0x0) {
    CEffectManager::calculateEffectValues(*(CEffectManager **)(this + 0x1b8));
  }
  createElementalDamages(this);
  setRequirements(this);
  recalculatePrice(this);
  return;
}



/* address=008867c0
   symbol=CEquipment::fillSaveState */

/* WARNING: Removing unreachable block (ram,0x00886d27) */
/* CEquipment::fillSaveState(CItemSaveState&, int, bool) */

void CEquipment::fillSaveState(CItemSaveState *param_1,int param_2,bool param_3)

{
  int *piVar1;
  int iVar2;
  CEffect *pCVar3;
  undefined4 *puVar4;
  char cVar5;
  CItemSaveState *this;
  undefined8 *puVar6;
  long *plVar7;
  CEffect *this_00;
  long lVar8;
  long *plVar9;
  ulong uVar10;
  uint uVar11;
  long lVar12;
  undefined4 *puVar13;
  undefined4 in_register_00000034;
  long lVar14;
  long lVar15;
  uint local_64;
  CItemSaveState *local_50;
  long local_48 [3];

  lVar14 = CONCAT44(in_register_00000034,param_2);
  if (((*(long *)(param_1 + 0x1b8) != 0) &&
      (cVar5 = CBaseUnit::ISA((CBaseUnit *)param_1,0x78), cVar5 != '\0')) &&
     (cVar5 = CBaseUnit::ISA((CBaseUnit *)param_1,0xa0), cVar5 == '\0')) {
    CEffectManager::clearOutAffixEffects(*(CEffectManager **)(param_1 + 0x1b8));
  }
  CItem::fillSaveState(param_1,param_2,param_3);
  *(undefined4 *)(lVar14 + 0x28) = *(undefined4 *)(param_1 + 0x28c);
  *(undefined4 *)(lVar14 + 0x68) = *(undefined4 *)(param_1 + 0x238);
  *(CItemSaveState *)(lVar14 + 0x75) = param_1[0x348];
  *(undefined4 *)(lVar14 + 0x70) = *(undefined4 *)(param_1 + 0x3e0);
  *(undefined4 *)(lVar14 + 0x6c) = *(undefined4 *)(param_1 + 0x344);
  if ((param_1[0x25c] != (CItemSaveState)0x0) &&
     (cVar5 = (**(code **)(*(long *)param_1 + 0x48))(param_1), cVar5 == '\0')) {
    *(undefined1 *)(lVar14 + 0x5d) = 1;
  }
  *(undefined4 *)(lVar14 + 0x7c) = *(undefined4 *)(param_1 + 0x33c);
  *(undefined4 *)(lVar14 + 0x78) = *(undefined4 *)(param_1 + 0x340);
  getFullItemName(SUB81(local_48,0));
  if ((allocator *)(local_48[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_48[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
    }
  }
  std::wstring::assign((wstring_conflict *)(lVar14 + 0x20));
  std::wstring::assign((wstring_conflict *)(lVar14 + 0x18));
  createElementalDamages((CEquipment *)param_1);
  iVar2 = *(int *)(param_1 + 0x3f0);
  if (0 < iVar2) {
    lVar15 = 0;
    uVar11 = 0;
    do {
      while( true ) {
        this = (CItemSaveState *)Ogre::NedAllocImpl::allocBytes(0x180,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00886960 to 00886964 has its CatchHandler @ 00886d14 */
        CItemSaveState::CItemSaveState(this);
        if (uVar11 < *(uint *)(param_1 + 0x3f4)) {
          puVar6 = (undefined8 *)(lVar15 + *(long *)(param_1 + 1000));
        }
        else {
          puVar6 = *(undefined8 **)(param_1 + 1000);
        }
        local_50 = this;
        (**(code **)(*(long *)*puVar6 + 0x290))((long *)*puVar6,this,0xffffffff);
        puVar6 = *(undefined8 **)(lVar14 + 0x130);
        if (puVar6 == *(undefined8 **)(lVar14 + 0x138)) break;
        lVar12 = 0;
        if (puVar6 != (undefined8 *)0x0) {
          *puVar6 = local_50;
          lVar12 = *(long *)(lVar14 + 0x130);
        }
        uVar11 = uVar11 + 1;
        lVar15 = lVar15 + 8;
        *(long *)(lVar14 + 0x130) = lVar12 + 8;
        if (iVar2 <= (int)uVar11) goto LAB_008869b0;
      }
      uVar11 = uVar11 + 1;
      lVar15 = lVar15 + 8;
      std::vector<CItemSaveState*,std::allocator<CItemSaveState*>>::_M_insert_aux
                ((vector<CItemSaveState*,std::allocator<CItemSaveState*>> *)(lVar14 + 0x128),puVar6,
                 &local_50);
    } while ((int)uVar11 < iVar2);
  }
LAB_008869b0:
  lVar15 = *(long *)(param_1 + 0x1b8);
  local_64 = 0;
  lVar12 = lVar14;
  if (lVar15 == 0) {
LAB_00886b38:
    lVar15 = *(long *)(param_1 + 0x350);
    if (*(long *)(param_1 + 0x358) - lVar15 >> 2 != 0) {
      uVar10 = 0;
      uVar11 = 0;
      do {
        puVar4 = *(undefined4 **)(lVar14 + 0x148);
        if (puVar4 == *(undefined4 **)(lVar14 + 0x150)) {
          std::vector<EDAMAGE_TYPES,std::allocator<EDAMAGE_TYPES>>::_M_insert_aux
                    ((vector<EDAMAGE_TYPES,std::allocator<EDAMAGE_TYPES>> *)(lVar14 + 0x140));
        }
        else {
          lVar12 = 0;
          if (puVar4 != (undefined4 *)0x0) {
            *puVar4 = *(undefined4 *)(lVar15 + uVar10 * 4);
            lVar12 = *(long *)(lVar14 + 0x148);
          }
          *(long *)(lVar14 + 0x148) = lVar12 + 4;
        }
        puVar4 = *(undefined4 **)(lVar14 + 0x160);
        puVar13 = (undefined4 *)(uVar10 * 4 + *(long *)(param_1 + 0x368));
        if (puVar4 == *(undefined4 **)(lVar14 + 0x168)) {
          std::vector<int,std::allocator<int>>::_M_insert_aux
                    ((vector<int,std::allocator<int>> *)(lVar14 + 0x158),puVar4,puVar13);
        }
        else {
          lVar15 = 0;
          if (puVar4 != (undefined4 *)0x0) {
            *puVar4 = *puVar13;
            lVar15 = *(long *)(lVar14 + 0x160);
          }
          *(long *)(lVar14 + 0x160) = lVar15 + 4;
        }
        uVar11 = uVar11 + 1;
        uVar10 = (ulong)uVar11;
        lVar15 = *(long *)(param_1 + 0x350);
      } while (uVar10 < (ulong)(*(long *)(param_1 + 0x358) - lVar15 >> 2));
    }
    if (((*(long *)(param_1 + 0x1b8) != 0) &&
        (cVar5 = CBaseUnit::ISA((CBaseUnit *)param_1,0x78), cVar5 != '\0')) &&
       (cVar5 = CBaseUnit::ISA((CBaseUnit *)param_1,0xa0), cVar5 == '\0')) {
      CEffectManager::addAffixEffectsBackIn(*(CEffectManager **)(param_1 + 0x1b8));
      return;
    }
    return;
  }
  do {
    lVar15 = lVar15 + (long)(int)local_64 * 0x18;
    if (*(int *)(lVar15 + 0x30) != 0) {
      plVar7 = (long *)(lVar15 + 0x28);
      uVar10 = 0;
      do {
        while( true ) {
          uVar11 = (uint)uVar10;
          if (uVar11 < *(uint *)(lVar15 + 0x34)) {
            puVar6 = (undefined8 *)(uVar10 * 8 + *plVar7);
          }
          else {
            puVar6 = (undefined8 *)*plVar7;
          }
          pCVar3 = (CEffect *)*puVar6;
          this_00 = (CEffect *)Ogre::NedAllocImpl::allocBytes(0x138,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00886a3b to 00886a3f has its CatchHandler @ 00886d01 */
          CEffect::CEffect(this_00,pCVar3);
          local_50 = (CItemSaveState *)this_00;
          CEffect::setOwner(this_00,(CBaseUnit *)0x0,true);
          CEffect::setSkillOwner((CEffect *)local_50,(CSkill *)0x0);
          if (uVar11 < *(uint *)(lVar15 + 0x34)) {
            plVar9 = (long *)(uVar10 * 8 + *plVar7);
          }
          else {
            plVar9 = (long *)*plVar7;
          }
          *(undefined4 *)(local_50 + 0xc0) = *(undefined4 *)(*plVar9 + 0xc0);
          puVar6 = *(undefined8 **)(lVar12 + 0xe8);
          if (puVar6 == *(undefined8 **)(lVar12 + 0xf0)) break;
          lVar8 = 0;
          if (puVar6 != (undefined8 *)0x0) {
            *puVar6 = local_50;
            lVar8 = *(long *)(lVar12 + 0xe8);
          }
          uVar10 = (ulong)(uVar11 + 1);
          *(long *)(lVar12 + 0xe8) = lVar8 + 8;
          if (*(uint *)(lVar15 + 0x30) <= uVar11 + 1) goto LAB_00886b10;
        }
        uVar10 = (ulong)(uVar11 + 1);
        std::vector<CEffect*,std::allocator<CEffect*>>::_M_insert_aux
                  ((vector<CEffect*,std::allocator<CEffect*>> *)
                   (lVar14 + 0xe0 + (ulong)local_64 * 0x18),puVar6,&local_50);
      } while (uVar11 + 1 < *(uint *)(lVar15 + 0x30));
    }
LAB_00886b10:
    local_64 = local_64 + 1;
    lVar12 = lVar12 + 0x18;
    if (local_64 == 3) goto LAB_00886b38;
    lVar15 = *(long *)(param_1 + 0x1b8);
  } while( true );
}



/* address=00886d40
   symbol=CEquipment::attachToGivenLocation */

/* WARNING: Removing unreachable block (ram,0x00887944) */
/* WARNING: Removing unreachable block (ram,0x00887a7c) */
/* WARNING: Removing unreachable block (ram,0x00887881) */
/* WARNING: Removing unreachable block (ram,0x0088788f) */
/* WARNING: Removing unreachable block (ram,0x0088794f) */
/* WARNING: Removing unreachable block (ram,0x0088789a) */
/* CEquipment::attachToGivenLocation(CCharacter*, EEQUIP_LOCATIONS) */

void __thiscall CEquipment::attachToGivenLocation(CEquipment *this,CCharacter *param_1,uint param_3)

{
  int *piVar1;
  int iVar2;
  CParticle *this_00;
  undefined8 uVar3;
  string *psVar4;
  code *pcVar5;
  char cVar6;
  uint uVar7;
  uint uVar8;
  long lVar9;
  Quaternion *pQVar10;
  long *plVar11;
  long *plVar12;
  MaterialPtr *pMVar13;
  long lVar14;
  long lVar15;
  char *pcVar16;
  char *pcVar17;
  bool bVar18;
  byte bVar19;
  float fVar20;
  undefined **local_178 [2];
  int *local_168;
  undefined **local_158;
  string *local_150;
  int *local_148;
  undefined4 local_140;
  undefined8 local_138 [4];
  wstring_conflict local_118 [16];
  wstring_conflict local_108 [16];
  long local_f8 [2];
  long local_e8 [2];
  long local_d8 [2];
  long local_c8 [2];
  wstring_conflict local_b8 [16];
  wstring_conflict local_a8 [16];
  STRINGS local_98 [16];
  string local_88 [16];
  string local_78 [16];
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

  bVar19 = 0;
  std::wstring::wstring((wstring_conflict *)local_58,(wstring_conflict *)(param_1 + 0x40));
                    /* try { // try from 00886d75 to 00886d79 has its CatchHandler @ 00887a22 */
  cVar6 = isWardrobed(this,(wstring_conflict *)local_58);
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
  if (cVar6 != '\0') {
    return;
  }
  if (param_1 == (CCharacter *)0x0) {
    return;
  }
  lVar9 = (**(code **)(*(long *)param_1 + 0x1e0))(param_1);
  if (lVar9 == 0) {
    return;
  }
  lVar9 = (**(code **)(*(long *)param_1 + 0x1e0))(param_1);
  if (*(long *)(lVar9 + 0x60) == 0) {
    return;
  }
  plVar11 = *(long **)(this + 0x2b0);
  if (plVar11 == (long *)0x0) {
    return;
  }
  if (plVar11[0xc] == 0) {
    return;
  }
  (**(code **)(*plVar11 + 0x18))();
  if (*(long **)(this + 0x2b8) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x2b8) + 0x18))();
  }
  resetVisualLayout(this);
  detachFromLocation(this);
  this_00 = *(CParticle **)(this + 0x3d0);
  *(CCharacter **)(this + 0x290) = param_1;
  *(uint *)(this + 0x298) = param_3;
  if (((this_00 != (CParticle *)0x0) && (*(long *)(this + 0x2b0) != 0)) &&
     (*(long *)(this_00 + 0x58) != 0)) {
    CParticle::Stop(this_00,false);
    OGRE_UTILITIES::removeChildFromParentNode(*(SceneNode **)(*(long *)(this + 0x3d0) + 0x58));
  }
  createParticles(this);
  (**(code **)(*(long *)param_1 + 0x1e0))(param_1);
  lVar14 = (long)(int)param_3;
  uVar3 = *(undefined8 *)(*(long *)(this + 0x2b0) + 0x60);
  lVar9 = *(long *)(*(char **)(::KEQUIP_LOCATION_BONES + lVar14 * 8) + -0x18);
  if (lVar9 == *(long *)(::EMPTY_STRING + -0x18)) {
    bVar18 = true;
    lVar15 = lVar9;
    pcVar16 = *(char **)(::KEQUIP_LOCATION_BONES + lVar14 * 8);
    pcVar17 = ::EMPTY_STRING;
    do {
      if (lVar15 == 0) break;
      lVar15 = lVar15 + -1;
      bVar18 = *pcVar16 == *pcVar17;
      pcVar16 = pcVar16 + (ulong)bVar19 * -2 + 1;
      pcVar17 = pcVar17 + (ulong)bVar19 * -2 + 1;
    } while (bVar18);
    if (bVar18) goto LAB_0088711e;
  }
  std::string::string((string *)local_68,(string *)(::KEQUIP_LOCATION_BONES + lVar14 * 8));
                    /* try { // try from 00886ed1 to 00886ed5 has its CatchHandler @ 00887a1c */
  cVar6 = CBaseUnit::ISA((CBaseUnit *)this,0x15);
  if (cVar6 == '\0') {
    if (param_3 < 0xc) goto LAB_008874ff;
  }
  else {
                    /* try { // try from 008874f5 to 008874f9 has its CatchHandler @ 00887a1c */
    std::string::assign((string *)local_68);
LAB_008874ff:
    switch(param_3) {
    case 0:
      plVar11 = *(long **)(param_1 + 0x2e8);
      break;
    case 1:
      plVar11 = *(long **)(param_1 + 0x2f8);
      break;
    case 2:
    case 4:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
      goto switchD_00887501_caseD_2;
    case 3:
      plVar11 = *(long **)(param_1 + 0x318);
      break;
    case 5:
      plVar11 = *(long **)(param_1 + 0x308);
      break;
    default:
      plVar11 = *(long **)(param_1 + 0x300);
    }
    if (plVar11 != (long *)0x0) {
                    /* try { // try from 0088769d to 0088772c has its CatchHandler @ 00887a1c */
      plVar12 = (long *)Ogre::SceneNode::getParentSceneNode();
      if (plVar12 != (long *)0x0) {
        (**(code **)(*plVar12 + 0x1e0))(plVar12,*(undefined8 *)(*(long *)(this + 0x2b0) + 0x58));
      }
      (**(code **)(*plVar11 + 0x1a8))(plVar11,*(undefined8 *)(*(long *)(this + 0x2b0) + 0x58));
      if (*(long *)(this + 0x3c8) != 0) {
        plVar12 = (long *)Ogre::SceneNode::getParentSceneNode();
        if (plVar12 != (long *)0x0) {
          (**(code **)(*plVar12 + 0x1e0))(plVar12,*(undefined8 *)(*(long *)(this + 0x3c8) + 0x58));
        }
        (**(code **)(*plVar11 + 0x1a8))(plVar11,*(undefined8 *)(*(long *)(this + 0x3c8) + 0x58));
        CParticle::Start();
      }
    }
  }
switchD_00887501_caseD_2:
  if (*(long *)(param_1 + 0x208) != 0) {
    psVar4 = *(string **)(*(long *)(param_1 + 0x208) + 0x60);
                    /* try { // try from 00886f1c to 00886f20 has its CatchHandler @ 00887a65 */
    std::string::string(local_78,"itemdummy_",local_39);
                    /* try { // try from 00886f31 to 00886f35 has its CatchHandler @ 00887a58 */
    STRINGS::uniqueName((STRINGS *)local_c8,local_78);
                    /* try { // try from 00886f39 to 00886f3d has its CatchHandler @ 00887a49 */
    std::string::~string(local_78);
                    /* try { // try from 00886f41 to 00886f45 has its CatchHandler @ 00887a44 */
    lVar9 = Ogre::Entity::getMesh();
    local_150 = *(string **)(lVar9 + 8);
    local_148 = *(int **)(lVar9 + 0x10);
    local_140 = *(undefined4 *)(lVar9 + 0x18);
    if (local_148 != (int *)0x0) {
      *local_148 = *local_148 + 1;
    }
    local_158 = (undefined **)0x14247b0;
                    /* try { // try from 00886fad to 00886fca has its CatchHandler @ 00887a72 */
    Ogre::Mesh::clone((string *)local_138,local_150);
    local_138[0] = 0x14247b0;
    Ogre::SharedPtr<Ogre::Mesh>::~SharedPtr((SharedPtr<Ogre::Mesh> *)local_138);
    lVar9 = CMasterResourceManager::getSingleton();
    plVar11 = *(long **)(lVar9 + 0xd0);
    pcVar5 = *(code **)(*plVar11 + 0x268);
                    /* try { // try from 00886ff9 to 00886ffd has its CatchHandler @ 00887a67 */
    std::string::string(local_88,"dummyentity_",&local_3a);
                    /* try { // try from 0088700c to 00887010 has its CatchHandler @ 00887a74 */
    STRINGS::uniqueName(local_98,local_88);
                    /* try { // try from 0088701c to 0088701f has its CatchHandler @ 008879c5 */
    pQVar10 = (Quaternion *)(*pcVar5)(plVar11,local_98,(STRINGS *)local_c8);
                    /* try { // try from 00887028 to 0088702c has its CatchHandler @ 00887a74 */
    std::string::~string((string *)local_98);
                    /* try { // try from 00887030 to 00887034 has its CatchHandler @ 00887a67 */
    std::string::~string(local_88);
                    /* try { // try from 00887038 to 008870dc has its CatchHandler @ 00887a72 */
    uVar7 = Ogre::Entity::getNumSubEntities();
    uVar8 = Ogre::Entity::getNumSubEntities();
    if ((uVar7 == uVar8) && (uVar7 != 0)) {
      uVar8 = 0;
      do {
                    /* try { // try from 00887636 to 00887671 has its CatchHandler @ 00887a72 */
        plVar11 = (long *)Ogre::Entity::getSubEntity((uint)uVar3);
        pMVar13 = (MaterialPtr *)Ogre::Entity::getSubEntity((uint)pQVar10);
        lVar9 = (**(code **)(*(long *)pMVar13 + 0x10))(pMVar13);
        if (*(long *)(lVar9 + 8) != 0) {
          (**(code **)(*plVar11 + 0x10))(plVar11);
          Ogre::SubEntity::setMaterial(pMVar13);
        }
        uVar8 = uVar8 + 1;
      } while (uVar8 < uVar7);
    }
    cVar6 = CBaseUnit::ISA((CBaseUnit *)this,8);
    if (cVar6 == '\0') {
      cVar6 = CBaseUnit::ISA((CBaseUnit *)this,0x15);
      fVar20 = DAT_00fa47fc;
      if (cVar6 != '\0') {
                    /* try { // try from 008877c1 to 008877c5 has its CatchHandler @ 00887a42 */
        std::wstring::wstring(local_b8,L"SHIELD_SCALE",&local_3c);
                    /* try { // try from 008877d8 to 008877dc has its CatchHandler @ 00887a3f */
        fVar20 = (float)CDataGroup::GetDataValue
                                  (*(CDataGroup **)(param_1 + 0x1b0),local_b8,DAT_00fa47fc);
                    /* try { // try from 008877e6 to 008877ea has its CatchHandler @ 00887a42 */
        std::wstring::~wstring(local_b8);
      }
    }
    else {
                    /* try { // try from 008875e8 to 008875ec has its CatchHandler @ 00887a17 */
      std::wstring::wstring(local_a8,L"WEAPON_SCALE",&local_3b);
                    /* try { // try from 008875ff to 00887603 has its CatchHandler @ 00887a0a */
      fVar20 = (float)CDataGroup::GetDataValue
                                (*(CDataGroup **)(param_1 + 0x1b0),local_a8,DAT_00fa47fc);
                    /* try { // try from 0088760d to 00887611 has its CatchHandler @ 00887a17 */
      std::wstring::~wstring(local_a8);
    }
    CCharacter::setPaperdollItem(param_1,param_3,pQVar10);
    plVar11 = (long *)Ogre::Entity::attachObjectToBone
                                (psVar4,(MovableObject *)local_68,pQVar10,
                                 (Vector3 *)&Ogre::Quaternion::IDENTITY);
    if (plVar11 != (long *)0x0) {
      (**(code **)(*plVar11 + 0x108))(fVar20,fVar20,plVar11);
    }
    local_158 = (undefined **)0x14247b0;
                    /* try { // try from 008870eb to 008870ef has its CatchHandler @ 00887a44 */
    Ogre::SharedPtr<Ogre::Mesh>::~SharedPtr((SharedPtr<Ogre::Mesh> *)&local_158);
                    /* try { // try from 008870f5 to 008870f9 has its CatchHandler @ 00887a1c */
    std::string::~string((string *)local_c8);
  }
  if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_68[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
    }
  }
  lVar9 = *(long *)(::EMPTY_STRING + -0x18);
LAB_0088711e:
  if (lVar9 == *(long *)(*(char **)(::KEQUIP_LOCATION_BONES_SECONDARY + lVar14 * 8) + -0x18)) {
    bVar18 = true;
    pcVar16 = *(char **)(::KEQUIP_LOCATION_BONES_SECONDARY + lVar14 * 8);
    pcVar17 = ::EMPTY_STRING;
    do {
      if (lVar9 == 0) break;
      lVar9 = lVar9 + -1;
      bVar18 = *pcVar16 == *pcVar17;
      pcVar16 = pcVar16 + (ulong)bVar19 * -2 + 1;
      pcVar17 = pcVar17 + (ulong)bVar19 * -2 + 1;
    } while (bVar18);
    if (bVar18) {
      return;
    }
  }
  if (*(long *)(this + 0x2b8) != 0) {
    plVar11 = (long *)0x0;
    uVar3 = *(undefined8 *)(*(long *)(this + 0x2b8) + 0x60);
    if ((param_3 == 5) && (plVar11 = *(long **)(param_1 + 0x310), plVar11 != (long *)0x0)) {
      plVar12 = (long *)Ogre::SceneNode::getParentSceneNode();
      if (plVar12 != (long *)0x0) {
        (**(code **)(*plVar12 + 0x1e0))(plVar12,*(undefined8 *)(*(long *)(this + 0x2b8) + 0x58));
      }
      (**(code **)(*plVar11 + 0x1a8))(plVar11,*(undefined8 *)(*(long *)(this + 0x2b8) + 0x58));
    }
    if (*(long *)(this + 0x3c8) != 0) {
      plVar12 = (long *)Ogre::SceneNode::getParentSceneNode();
      if (plVar12 != (long *)0x0) {
        (**(code **)(*plVar12 + 0x1e0))(plVar12,*(undefined8 *)(*(long *)(this + 0x3c8) + 0x58));
      }
      (**(code **)(*plVar11 + 0x1a8))(plVar11,*(undefined8 *)(*(long *)(this + 0x3c8) + 0x58));
      CParticle::Start();
    }
    if (*(long *)(param_1 + 0x208) != 0) {
      psVar4 = *(string **)(*(long *)(param_1 + 0x208) + 0x60);
                    /* try { // try from 008871db to 008871df has its CatchHandler @ 008878b8 */
      std::string::string((string *)local_d8,"itemdummy_",&local_3d);
                    /* try { // try from 008871f3 to 008871f7 has its CatchHandler @ 008878a5 */
      STRINGS::uniqueName((STRINGS *)local_c8,(string *)local_d8);
      if ((allocator *)(local_d8[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_d8[0] + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
        }
      }
                    /* try { // try from 00887214 to 00887218 has its CatchHandler @ 00887985 */
      lVar9 = Ogre::Entity::getMesh();
      local_150 = *(string **)(lVar9 + 8);
      local_148 = *(int **)(lVar9 + 0x10);
      local_140 = *(undefined4 *)(lVar9 + 0x18);
      if (local_148 != (int *)0x0) {
        *local_148 = *local_148 + 1;
      }
      local_158 = (undefined **)0x14247b0;
                    /* try { // try from 0088727d to 008872af has its CatchHandler @ 0088797c */
      Ogre::Mesh::clone((string *)local_178,local_150);
      local_178[0] = &PTR__SharedPtr_00fce650;
      if ((local_168 != (int *)0x0) &&
         (iVar2 = *local_168, *local_168 = iVar2 + -1, iVar2 + -1 == 0)) {
        (*(code *)PTR_destroy_00fce660)((string *)local_178);
      }
      lVar9 = CMasterResourceManager::getSingleton();
      plVar11 = *(long **)(lVar9 + 0xd0);
      pcVar5 = *(code **)(*plVar11 + 0x268);
                    /* try { // try from 008872de to 008872e2 has its CatchHandler @ 00887977 */
      std::string::string((string *)local_e8,"dummyentity_",&local_3e);
                    /* try { // try from 008872f1 to 008872f5 has its CatchHandler @ 00887972 */
      STRINGS::uniqueName((STRINGS *)local_f8,(string *)local_e8);
                    /* try { // try from 00887301 to 00887304 has its CatchHandler @ 0088795a */
      pQVar10 = (Quaternion *)(*pcVar5)(plVar11,(STRINGS *)local_f8,(STRINGS *)local_c8);
      if ((allocator *)(local_f8[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_f8[0] + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
        }
      }
      if ((allocator *)(local_e8[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_e8[0] + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
        }
      }
                    /* try { // try from 00887344 to 00887348 has its CatchHandler @ 0088797c */
      cVar6 = CBaseUnit::ISA((CBaseUnit *)this,8);
      if (cVar6 == '\0') {
                    /* try { // try from 008875a8 to 008875ac has its CatchHandler @ 0088797c */
        cVar6 = CBaseUnit::ISA((CBaseUnit *)this,0x15);
        fVar20 = DAT_00fa47fc;
        if (cVar6 != '\0') {
                    /* try { // try from 0088777a to 0088777e has its CatchHandler @ 008878e7 */
          std::wstring::wstring(local_118,L"SHIELD_SCALE",&local_40);
                    /* try { // try from 00887791 to 00887795 has its CatchHandler @ 008878bd */
          fVar20 = (float)CDataGroup::GetDataValue
                                    (*(CDataGroup **)(param_1 + 0x1b0),local_118,DAT_00fa47fc);
                    /* try { // try from 0088779f to 008877a3 has its CatchHandler @ 008878e7 */
          std::wstring::~wstring(local_118);
        }
      }
      else {
                    /* try { // try from 00887369 to 0088736d has its CatchHandler @ 00887a3a */
        std::wstring::wstring(local_108,L"WEAPON_SCALE",&local_3f);
                    /* try { // try from 00887380 to 00887384 has its CatchHandler @ 00887a35 */
        fVar20 = (float)CDataGroup::GetDataValue
                                  (*(CDataGroup **)(param_1 + 0x1b0),local_108,DAT_00fa47fc);
                    /* try { // try from 0088738e to 00887392 has its CatchHandler @ 00887a3a */
        std::wstring::~wstring(local_108);
      }
                    /* try { // try from 0088739d to 00887488 has its CatchHandler @ 0088797c */
      CCharacter::setPaperdollItemSecondary(param_1,param_3,pQVar10);
      lVar9 = (**(code **)(*(long *)pQVar10 + 0xa0))(pQVar10);
      if (lVar9 != 0) {
        plVar11 = (long *)(**(code **)(*(long *)pQVar10 + 0xa0))(pQVar10);
        (**(code **)(*plVar11 + 0x108))(fVar20,fVar20,plVar11);
      }
      uVar7 = Ogre::Entity::getNumSubEntities();
      uVar8 = Ogre::Entity::getNumSubEntities();
      if ((uVar7 == uVar8) && (uVar7 != 0)) {
        uVar8 = 0;
        do {
          plVar11 = (long *)Ogre::Entity::getSubEntity((uint)uVar3);
          pMVar13 = (MaterialPtr *)Ogre::Entity::getSubEntity((uint)pQVar10);
          lVar9 = (**(code **)(*(long *)pMVar13 + 0x10))(pMVar13);
          if (*(long *)(lVar9 + 8) != 0) {
            (**(code **)(*plVar11 + 0x10))(plVar11);
            Ogre::SubEntity::setMaterial(pMVar13);
          }
          uVar8 = uVar8 + 1;
        } while (uVar8 < uVar7);
      }
      plVar11 = (long *)Ogre::Entity::attachObjectToBone
                                  (psVar4,(MovableObject *)
                                          (::KEQUIP_LOCATION_BONES_SECONDARY + lVar14 * 8),pQVar10,
                                   (Vector3 *)&Ogre::Quaternion::IDENTITY);
      if (plVar11 != (long *)0x0) {
        (**(code **)(*plVar11 + 0x108))(fVar20,fVar20,plVar11);
      }
      local_158 = &PTR__SharedPtr_00fce650;
      if ((local_148 != (int *)0x0) &&
         (iVar2 = *local_148, *local_148 = iVar2 + -1, iVar2 + -1 == 0)) {
                    /* try { // try from 008874b1 to 008874b3 has its CatchHandler @ 00887985 */
        (*(code *)PTR_destroy_00fce660)(&local_158);
      }
      if ((allocator *)(local_c8[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_c8[0] + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
        }
      }
    }
  }
  return;
}



/* address=00887a90
   symbol=CEquipment::equipped */

/* CEquipment::equipped(CInventory*, CCharacter*, EEQUIP_LOCATIONS) */

void __thiscall
CEquipment::equipped(CEquipment *this,undefined8 param_2_00,undefined8 param_2,undefined4 param_4)

{
  resetVisualLayout(this);
  (**(code **)(*(long *)this + 0x208))(this,0);
  setRenderBehind(this,true);
  attachToGivenLocation(this,param_2,param_4);
  if (this[0x1d0] == (CEquipment)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x00887b21. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)this + 0x30))(this,0x6c);
  return;
}



/* address=00887b30
   symbol=CEquipment::loadModel */

/* WARNING: Removing unreachable block (ram,0x008884c6) */
/* WARNING: Removing unreachable block (ram,0x0088890b) */
/* WARNING: Removing unreachable block (ram,0x00888466) */
/* WARNING: Removing unreachable block (ram,0x00888832) */
/* WARNING: Removing unreachable block (ram,0x008888fd) */
/* WARNING: Removing unreachable block (ram,0x008886ce) */
/* WARNING: Removing unreachable block (ram,0x00888510) */
/* WARNING: Removing unreachable block (ram,0x00888581) */
/* WARNING: Removing unreachable block (ram,0x0088863b) */
/* WARNING: Removing unreachable block (ram,0x00888740) */
/* WARNING: Removing unreachable block (ram,0x00888502) */
/* WARNING: Removing unreachable block (ram,0x0088858c) */
/* WARNING: Removing unreachable block (ram,0x0088851e) */
/* WARNING: Removing unreachable block (ram,0x008886be) */
/* WARNING: Removing unreachable block (ram,0x0088874b) */
/* WARNING: Removing unreachable block (ram,0x00888824) */
/* WARNING: Removing unreachable block (ram,0x00888816) */
/* WARNING: Removing unreachable block (ram,0x00888808) */
/* WARNING: Removing unreachable block (ram,0x008888c6) */
/* WARNING: Removing unreachable block (ram,0x00888471) */
/* CEquipment::loadModel(std::wstring, std::wstring) */

void __thiscall
CEquipment::loadModel(CEquipment *this,undefined8 *param_2,wstring_conflict *param_3)

{
  wchar_t *pwVar1;
  int *piVar2;
  wchar_t wVar3;
  size_t __n;
  CDataGroup *this_00;
  bool bVar4;
  uint uVar5;
  int iVar6;
  long lVar7;
  long *plVar8;
  wstring_conflict *pwVar9;
  undefined8 uVar10;
  uint uVar11;
  void *local_198;
  undefined8 local_190;
  undefined8 local_188;
  long local_178 [2];
  long local_168 [2];
  long local_158 [2];
  long local_148 [2];
  wchar_t *local_138 [2];
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
  long local_68 [5];
  allocator local_40;
  allocator local_3f;
  allocator local_3e;
  allocator local_3d;
  allocator local_3c;
  allocator local_3b;
  allocator local_3a;
  allocator local_39 [9];

  if (*(long *)(this + 0x68) != 0) {
    unloadModel(this);
    lVar7 = CResourceManager::createGenericModel
                      (*(CResourceManager **)(this + 0x68),(SceneManager *)0x0,(wchar_t *)*param_2,
                       (wchar_t *)0x0,false,false,true);
    *(long *)(this + 0x2b0) = lVar7;
    if ((*(long **)(lVar7 + 0x58) != (long *)0x0) &&
       (lVar7 = (**(code **)(**(long **)(lVar7 + 0x58) + 0xc0))(), lVar7 != 0)) {
      plVar8 = (long *)(**(code **)(**(long **)(*(long *)(this + 0x2b0) + 0x58) + 0xc0))();
      (**(code **)(*plVar8 + 0x1e0))(plVar8,*(undefined8 *)(*(long *)(this + 0x2b0) + 0x58));
    }
    if (((*(long *)(this + 0x68) == 0) ||
        (lVar7 = *(long *)(*(long *)(this + 0x68) + 0x18), lVar7 == 0)) ||
       (lVar7 = *(long *)(lVar7 + 0x1d8), lVar7 == 0)) {
                    /* try { // try from 008880a0 to 008880a4 has its CatchHandler @ 00888840 */
      std::wstring::wstring
                ((wstring_conflict *)local_68,L"media/sharedtextures/rimlight.dds",local_39);
    }
    else {
                    /* try { // try from 00887bfd to 00887c01 has its CatchHandler @ 00888840 */
      std::wstring::wstring((wstring_conflict *)local_68,(wstring_conflict *)(lVar7 + 0x6d8));
    }
                    /* try { // try from 00887c0c to 00887c10 has its CatchHandler @ 008888b6 */
    CGenericModel::setRimLighting(*(CGenericModel **)(this + 0x2b0));
    if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar2 = (int *)(local_68[0] + -8);
      iVar6 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar6 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
      }
    }
    CGenericModel::setCastsShadows(*(CGenericModel **)(this + 0x2b0),false);
    (**(code **)(**(long **)(this + 0x58) + 0x1a8))
              (*(long **)(this + 0x58),*(undefined8 *)(*(long *)(this + 0x2b0) + 0x58));
    (**(code **)(*(long *)this + 0x2c0))(this,0,1);
    (**(code **)(**(long **)(this + 0x2b0) + 0x58))(0,0);
    plVar8 = *(long **)(*(long *)(this + 0x2b0) + 0x60);
    if (plVar8 == (long *)0x0) {
      std::operator+((wchar_t *)local_138,(wstring_conflict *)L"Error loading model : ");
                    /* try { // try from 008882db to 008882df has its CatchHandler @ 008884d1 */
      STRINGS::StringConvertToNarrow((STRINGS *)local_78,local_138[0]);
                    /* try { // try from 008882e0 to 008882f6 has its CatchHandler @ 008884ab */
      uVar10 = Ogre::LogManager::getSingleton();
      Ogre::LogManager::logMessage(uVar10,(STRINGS *)local_78,2,0);
      if ((allocator *)(local_78[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_78[0] + -8);
        iVar6 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar6 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
        }
      }
      if ((allocator *)(local_138[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
         ) {
        LOCK();
        pwVar1 = local_138[0] + -2;
        wVar3 = *pwVar1;
        *pwVar1 = *pwVar1 + L'\xffffffff';
        UNLOCK();
        if (wVar3 < L'\x01') {
          std::wstring::_Rep::_M_destroy((allocator *)(local_138[0] + -6));
        }
      }
    }
    else {
      (**(code **)(*plVar8 + 0x140))(plVar8,0x32);
      __n = *(size_t *)(*(wchar_t **)param_3 + -6);
      if ((__n == *(size_t *)(::EMPTY_WSTRING + -6)) &&
         (iVar6 = wmemcmp(*(wchar_t **)param_3,::EMPTY_WSTRING,__n), iVar6 == 0)) {
                    /* try { // try from 008880d2 to 008880f0 has its CatchHandler @ 00888848 */
        std::wstring::wstring((wstring_conflict *)local_98,L"MESHFILE_SECONDARY",&local_3a);
        bVar4 = true;
        pwVar9 = (wstring_conflict *)
                 CDataGroup::GetDataValue
                           (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_98,
                            (wstring_conflict *)&::EMPTY_WSTRING);
      }
      else {
        bVar4 = false;
        pwVar9 = param_3;
      }
                    /* try { // try from 00887cc4 to 00887cc8 has its CatchHandler @ 00888848 */
      std::wstring::wstring((wstring_conflict *)local_88,pwVar9);
      if ((bVar4) &&
         ((allocator *)(local_98[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)) {
        LOCK();
        piVar2 = (int *)(local_98[0] + -8);
        iVar6 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar6 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
        }
      }
      if (*(long *)(local_88[0] + -0x18) != 0) {
                    /* try { // try from 00887cf8 to 00887cfc has its CatchHandler @ 00888866 */
        std::wstring::wstring((wstring_conflict *)local_138,(wstring_conflict *)local_88);
        if (*(long *)(*(long *)param_3 + -0x18) == 0) {
                    /* try { // try from 00888111 to 00888115 has its CatchHandler @ 00888646 */
          std::wstring::wstring((wstring_conflict *)local_a8,L"RESOURCEDIRECTORY",&local_3b);
                    /* try { // try from 00888125 to 00888134 has its CatchHandler @ 0088862e */
          CDataGroup::GetDataValue
                    (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_a8,
                     (wstring_conflict *)&::EMPTY_WSTRING);
          std::wstring::assign((wstring_conflict *)local_138);
          if ((allocator *)(local_a8[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_a8[0] + -8);
            iVar6 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar6 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
            }
          }
                    /* try { // try from 00888158 to 0088815c has its CatchHandler @ 008886de */
          std::wstring::wstring((wstring_conflict *)local_b8,(wstring_conflict *)local_138);
          wcslen(L"/");
                    /* try { // try from 00888172 to 00888176 has its CatchHandler @ 008885f5 */
          std::wstring::append((wchar_t *)local_b8,0xfff8b8);
                    /* try { // try from 0088818a to 0088818e has its CatchHandler @ 008885f0 */
          std::operator+((wstring_conflict *)local_c8,(wstring_conflict *)local_b8);
                    /* try { // try from 008881a2 to 008881a6 has its CatchHandler @ 008885eb */
          std::wstring::wstring((wstring_conflict *)local_d8,(wstring_conflict *)local_c8);
          wcslen(L".mesh");
                    /* try { // try from 008881bc to 008881c0 has its CatchHandler @ 008885de */
          std::wstring::append((wchar_t *)local_d8,0xfafb04);
                    /* try { // try from 008881cf to 008881d3 has its CatchHandler @ 008885d9 */
          FILESYSTEM::CleanPath((FILESYSTEM *)local_e8,(wstring_conflict *)local_d8);
                    /* try { // try from 008881da to 008881de has its CatchHandler @ 00888597 */
          std::wstring::assign((wstring_conflict *)local_138);
          if ((allocator *)(local_e8[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_e8[0] + -8);
            iVar6 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar6 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
            }
          }
          if ((allocator *)(local_d8[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_d8[0] + -8);
            iVar6 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar6 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
            }
          }
          if ((allocator *)(local_c8[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_c8[0] + -8);
            iVar6 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar6 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
            }
          }
          if ((allocator *)(local_b8[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_b8[0] + -8);
            iVar6 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar6 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
            }
          }
        }
                    /* try { // try from 00887d29 to 00887d76 has its CatchHandler @ 008886de */
        lVar7 = CResourceManager::createGenericModel
                          (*(CResourceManager **)(this + 0x68),(SceneManager *)0x0,local_138[0],
                           (wchar_t *)0x0,false,false,true);
        *(long *)(this + 0x2b8) = lVar7;
        if ((*(long **)(lVar7 + 0x58) != (long *)0x0) &&
           (lVar7 = (**(code **)(**(long **)(lVar7 + 0x58) + 0xc0))(), lVar7 != 0)) {
          plVar8 = (long *)(**(code **)(**(long **)(*(long *)(this + 0x2b8) + 0x58) + 0xc0))();
          (**(code **)(*plVar8 + 0x1e0))(plVar8,*(undefined8 *)(*(long *)(this + 0x2b8) + 0x58));
        }
        if (((*(long *)(this + 0x68) == 0) ||
            (lVar7 = *(long *)(*(long *)(this + 0x68) + 0x18), lVar7 == 0)) ||
           (lVar7 = *(long *)(lVar7 + 0x1d8), lVar7 == 0)) {
                    /* try { // try from 00888370 to 00888374 has its CatchHandler @ 008886c9 */
          std::wstring::wstring
                    ((wstring_conflict *)local_f8,L"media/sharedtextures/rimlight.dds",&local_3c);
        }
        else {
                    /* try { // try from 00887db3 to 00887db7 has its CatchHandler @ 008886c9 */
          std::wstring::wstring((wstring_conflict *)local_f8,(wstring_conflict *)(lVar7 + 0x6d8));
        }
                    /* try { // try from 00887dc2 to 00887dc6 has its CatchHandler @ 008886d9 */
        CGenericModel::setRimLighting(*(CGenericModel **)(this + 0x2b8));
        if ((allocator *)(local_f8[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar2 = (int *)(local_f8[0] + -8);
          iVar6 = *piVar2;
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (iVar6 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
          }
        }
                    /* try { // try from 00887de5 to 00887e18 has its CatchHandler @ 008886de */
        CGenericModel::setCastsShadows(*(CGenericModel **)(this + 0x2b8),false);
        (**(code **)(**(long **)(this + 0x2b8) + 0x58))(0,0);
        (**(code **)(**(long **)(*(long *)(this + 0x2b8) + 0x60) + 0x140))
                  (*(long **)(*(long *)(this + 0x2b8) + 0x60),0x32);
        if ((allocator *)(local_138[0] + -6) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          pwVar1 = local_138[0] + -2;
          wVar3 = *pwVar1;
          *pwVar1 = *pwVar1 + L'\xffffffff';
          UNLOCK();
          if (wVar3 < L'\x01') {
            std::wstring::_Rep::_M_destroy((allocator *)(local_138[0] + -6));
          }
        }
      }
                    /* try { // try from 00887e46 to 00887e4a has its CatchHandler @ 008886b6 */
      std::wstring::wstring((wstring_conflict *)local_118,L"TEXTURE_OVERRIDE",&local_3d);
                    /* try { // try from 00887e5a to 00887e6e has its CatchHandler @ 008886a6 */
      pwVar9 = (wstring_conflict *)
               CDataGroup::GetDataValue
                         (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_118,
                          (wstring_conflict *)&::EMPTY_WSTRING);
      std::wstring::wstring((wstring_conflict *)local_108,pwVar9);
      if ((allocator *)(local_118[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_118[0] + -8);
        iVar6 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar6 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_118[0] + -0x18));
        }
      }
      if (*(long *)(local_108[0] + -0x18) != 0) {
                    /* try { // try from 00887ea2 to 00887ea6 has its CatchHandler @ 00888756 */
        CGenericModel::setTextureOverride
                  (*(CGenericModel **)(this + 0x2b0),(wstring_conflict *)local_108);
      }
      local_198 = (void *)0x0;
      local_190 = 0;
      local_188 = 0;
                    /* try { // try from 00887eda to 00887ede has its CatchHandler @ 0088876b */
      std::wstring::wstring((wstring_conflict *)local_128,L"TEXTURE_REPLACE",&local_3e);
                    /* try { // try from 00887eee to 00887ef2 has its CatchHandler @ 0088877f */
      uVar5 = CDataGroup::GetDataGroupsMatchingName
                        (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_128,
                         (vector *)&local_198);
      if ((allocator *)(local_128[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_128[0] + -8);
        iVar6 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar6 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_128[0] + -0x18));
        }
      }
      if (uVar5 != 0) {
        lVar7 = 0;
        uVar11 = 0;
        do {
          this_00 = *(CDataGroup **)((long)local_198 + lVar7);
                    /* try { // try from 00887f43 to 00887f47 has its CatchHandler @ 008887bc */
          std::wstring::wstring((wstring_conflict *)local_148,L"NAME",&local_3f);
                    /* try { // try from 00887f55 to 00887f69 has its CatchHandler @ 008887f6 */
          pwVar9 = (wstring_conflict *)
                   CDataGroup::GetDataValue(this_00,(wstring_conflict *)local_148,L"");
          std::wstring::wstring((wstring_conflict *)local_138,pwVar9);
          if ((allocator *)(local_148[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_148[0] + -8);
            iVar6 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar6 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_148[0] + -0x18));
            }
          }
                    /* try { // try from 00887f8e to 00887f92 has its CatchHandler @ 0088886b */
          std::wstring::wstring((wstring_conflict *)local_168,L"TEXTURE",&local_40);
                    /* try { // try from 00887fa0 to 00887fb1 has its CatchHandler @ 008887be */
          pwVar9 = (wstring_conflict *)
                   CDataGroup::GetDataValue(this_00,(wstring_conflict *)local_168,L"");
          std::wstring::wstring((wstring_conflict *)local_158,pwVar9);
          if ((allocator *)(local_168[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_168[0] + -8);
            iVar6 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar6 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_168[0] + -0x18));
            }
          }
                    /* try { // try from 00887fcf to 00887fd3 has its CatchHandler @ 008887da */
          STRINGS::StringConvertToNarrow((STRINGS *)local_178,local_138[0]);
                    /* try { // try from 00887fe3 to 00887fe7 has its CatchHandler @ 008887e9 */
          CGenericModel::setTextureOverrideSingle
                    (*(CGenericModel **)(this + 0x2b0),(string *)local_178,
                     (wstring_conflict *)local_158);
          if ((allocator *)(local_178[0] + -0x18) !=
              (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_178[0] + -8);
            iVar6 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar6 < 1) {
              std::string::_Rep::_M_destroy((allocator *)(local_178[0] + -0x18));
            }
          }
          if ((allocator *)(local_158[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_158[0] + -8);
            iVar6 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar6 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_158[0] + -0x18));
            }
          }
          if ((allocator *)(local_138[0] + -6) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            pwVar1 = local_138[0] + -2;
            wVar3 = *pwVar1;
            *pwVar1 = *pwVar1 + L'\xffffffff';
            UNLOCK();
            if (wVar3 < L'\x01') {
              std::wstring::_Rep::_M_destroy((allocator *)(local_138[0] + -6));
            }
          }
          uVar11 = uVar11 + 1;
          lVar7 = lVar7 + 8;
        } while (uVar11 < uVar5);
      }
      if (local_198 != (void *)0x0) {
        operator_delete(local_198);
      }
      if ((allocator *)(local_108[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_108[0] + -8);
        iVar6 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar6 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_108[0] + -0x18));
        }
      }
      if ((allocator *)(local_88[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_88[0] + -8);
        iVar6 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar6 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
        }
      }
    }
  }
  return;
}



/* address=00888920
   symbol=CEquipment::reskinByClass */

/* WARNING: Removing unreachable block (ram,0x00889055) */
/* WARNING: Removing unreachable block (ram,0x00888eab) */
/* WARNING: Removing unreachable block (ram,0x00889043) */
/* WARNING: Removing unreachable block (ram,0x008890e4) */
/* WARNING: Removing unreachable block (ram,0x008890d4) */
/* WARNING: Removing unreachable block (ram,0x00888f4e) */
/* WARNING: Removing unreachable block (ram,0x008890c6) */
/* WARNING: Removing unreachable block (ram,0x00888e9d) */
/* WARNING: Removing unreachable block (ram,0x00888faf) */
/* WARNING: Removing unreachable block (ram,0x00889100) */
/* WARNING: Removing unreachable block (ram,0x00888ebe) */
/* WARNING: Removing unreachable block (ram,0x00889060) */
/* WARNING: Removing unreachable block (ram,0x008890f2) */
/* CEquipment::reskinByClass(std::wstring) */

void __thiscall CEquipment::reskinByClass(CEquipment *this,wstring_conflict *param_2)

{
  allocator *paVar1;
  int *piVar2;
  wchar_t *pwVar3;
  wchar_t wVar4;
  CDataGroup *this_00;
  wchar_t *pwVar5;
  uint uVar6;
  int iVar7;
  wstring_conflict *pwVar8;
  long lVar9;
  uint uVar10;
  bool bVar11;
  void *local_138;
  undefined8 local_130;
  undefined8 local_128;
  long local_118 [2];
  long local_108 [2];
  wchar_t *local_f8 [2];
  long local_e8 [2];
  wchar_t *local_d8 [2];
  long local_c8 [2];
  long local_b8 [2];
  wchar_t *local_a8 [2];
  long local_98 [2];
  wchar_t *local_88 [2];
  long local_78 [2];
  wchar_t *local_68 [2];
  long local_58 [3];
  allocator local_3c;
  allocator local_3b;
  allocator local_3a;
  allocator local_39 [9];

  if (*(long *)(this + 0x2b0) != 0) {
    local_138 = (void *)0x0;
    local_130 = 0;
    local_128 = 0;
                    /* try { // try from 0088897c to 00888980 has its CatchHandler @ 00888ee3 */
    std::wstring::wstring((wstring_conflict *)local_58,L"WARDROBE",local_39);
                    /* try { // try from 00888995 to 00888999 has its CatchHandler @ 00888f3e */
    uVar6 = CDataGroup::GetDataGroupsMatchingName
                      (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_58,
                       (vector *)&local_138);
    if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar2 = (int *)(local_58[0] + -8);
      iVar7 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
      }
    }
                    /* try { // try from 008889c5 to 008889c9 has its CatchHandler @ 00888f75 */
    std::wstring::wstring((wstring_conflict *)local_68,(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 008889d7 to 008889db has its CatchHandler @ 00888f6b */
    std::wstring::wstring((wstring_conflict *)local_78,(wstring_conflict *)&::EMPTY_WSTRING);
    if (uVar6 != 0) {
      lVar9 = 0;
      uVar10 = 0;
      do {
        this_00 = *(CDataGroup **)((long)local_138 + lVar9);
                    /* try { // try from 00888b00 to 00888b04 has its CatchHandler @ 00888f69 */
        std::wstring::wstring((wstring_conflict *)local_98,L"CLASS",&local_3a);
                    /* try { // try from 00888b10 to 00888b24 has its CatchHandler @ 00888f59 */
        pwVar8 = (wstring_conflict *)
                 CDataGroup::GetDataValue(this_00,(wstring_conflict *)local_98,L"");
        STRINGS::StringUpper((STRINGS *)local_88,pwVar8);
        if ((allocator *)(local_98[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar2 = (int *)(local_98[0] + -8);
          iVar7 = *piVar2;
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (iVar7 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
          }
        }
                    /* try { // try from 00888b47 to 00888b4b has its CatchHandler @ 00888ecc */
        STRINGS::StringUpper((STRINGS *)local_a8,param_2);
        pwVar5 = local_a8[0];
        bVar11 = false;
        paVar1 = (allocator *)(local_a8[0] + -6);
        if (*(size_t *)(local_88[0] + -6) == *(size_t *)(local_a8[0] + -6)) {
          iVar7 = wmemcmp(local_88[0],local_a8[0],*(size_t *)(local_88[0] + -6));
          bVar11 = iVar7 == 0;
        }
        if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          pwVar5 = pwVar5 + -2;
          wVar4 = *pwVar5;
          *pwVar5 = *pwVar5 + L'\xffffffff';
          UNLOCK();
          if (wVar4 < L'\x01') {
            std::wstring::_Rep::_M_destroy(paVar1);
          }
        }
        if (bVar11) {
                    /* try { // try from 00888a26 to 00888a2a has its CatchHandler @ 00888ee1 */
          std::wstring::wstring((wstring_conflict *)local_b8,L"ITEM_MESH",&local_3b);
                    /* try { // try from 00888a3e to 00888a52 has its CatchHandler @ 00889085 */
          CDataGroup::GetDataValue
                    (this_00,(wstring_conflict *)local_b8,(wstring_conflict *)local_68);
          std::wstring::assign((wstring_conflict *)local_68);
          if ((allocator *)(local_b8[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_b8[0] + -8);
            iVar7 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar7 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
            }
          }
                    /* try { // try from 00888a7d to 00888a81 has its CatchHandler @ 00889080 */
          std::wstring::wstring((wstring_conflict *)local_c8,L"ITEM_MESH_SECONDARY",&local_3c);
                    /* try { // try from 00888a95 to 00888aa9 has its CatchHandler @ 0088906b */
          CDataGroup::GetDataValue
                    (this_00,(wstring_conflict *)local_c8,(wstring_conflict *)local_78);
          std::wstring::assign((wstring_conflict *)local_78);
          if ((allocator *)(local_c8[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar2 = (int *)(local_c8[0] + -8);
            iVar7 = *piVar2;
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (iVar7 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
            }
          }
        }
        if ((allocator *)(local_88[0] + -6) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          pwVar5 = local_88[0] + -2;
          wVar4 = *pwVar5;
          *pwVar5 = *pwVar5 + L'\xffffffff';
          UNLOCK();
          if (wVar4 < L'\x01') {
            std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -6));
          }
        }
        uVar10 = uVar10 + 1;
        lVar9 = lVar9 + 8;
      } while (uVar10 < uVar6);
    }
    if ((*(size_t *)(local_68[0] + -6) != *(size_t *)(::EMPTY_WSTRING + -6)) ||
       (iVar7 = wmemcmp(local_68[0],::EMPTY_WSTRING,*(size_t *)(local_68[0] + -6)), iVar7 != 0)) {
                    /* try { // try from 00888bc8 to 00888bcc has its CatchHandler @ 00888eeb */
      std::wstring::wstring
                ((wstring_conflict *)local_e8,(wstring_conflict *)(*(long *)(this + 0x2b0) + 0x110))
      ;
                    /* try { // try from 00888bd8 to 00888bdc has its CatchHandler @ 00888f0d */
      STRINGS::StringUpper((STRINGS *)local_f8,(wstring_conflict *)local_e8);
                    /* try { // try from 00888bed to 00888bf1 has its CatchHandler @ 00888ef5 */
      STRINGS::StringUpper((STRINGS *)local_d8,(wstring_conflict *)local_68);
      pwVar5 = local_f8[0];
      bVar11 = false;
      if (*(size_t *)(local_d8[0] + -6) == *(size_t *)(local_f8[0] + -6)) {
        iVar7 = wmemcmp(local_d8[0],local_f8[0],*(size_t *)(local_d8[0] + -6));
        bVar11 = iVar7 == 0;
      }
      if ((allocator *)(local_d8[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
      {
        LOCK();
        pwVar5 = local_d8[0] + -2;
        wVar4 = *pwVar5;
        *pwVar5 = *pwVar5 + L'\xffffffff';
        UNLOCK();
        pwVar5 = local_f8[0];
        if (wVar4 < L'\x01') {
          std::wstring::_Rep::_M_destroy((allocator *)(local_d8[0] + -6));
          pwVar5 = local_f8[0];
        }
      }
      if ((allocator *)(pwVar5 + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        pwVar3 = pwVar5 + -2;
        wVar4 = *pwVar3;
        *pwVar3 = *pwVar3 + L'\xffffffff';
        UNLOCK();
        if (wVar4 < L'\x01') {
          std::wstring::_Rep::_M_destroy((allocator *)(pwVar5 + -6));
        }
      }
      if ((allocator *)(local_e8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_e8[0] + -8);
        iVar7 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
        }
      }
      if (!bVar11) {
                    /* try { // try from 00888cb5 to 00888cb9 has its CatchHandler @ 00888eeb */
        std::wstring::wstring((wstring_conflict *)local_118,(wstring_conflict *)local_78);
                    /* try { // try from 00888cca to 00888cce has its CatchHandler @ 00888eb6 */
        std::wstring::wstring((wstring_conflict *)local_108,(wstring_conflict *)local_68);
                    /* try { // try from 00888cda to 00888cde has its CatchHandler @ 00888e2d */
        loadModel(this,(wstring_conflict *)local_108,(wstring_conflict *)local_118);
        if ((allocator *)(local_108[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar2 = (int *)(local_108[0] + -8);
          iVar7 = *piVar2;
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (iVar7 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_108[0] + -0x18));
          }
        }
        if ((allocator *)(local_118[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar2 = (int *)(local_118[0] + -8);
          iVar7 = *piVar2;
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (iVar7 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_118[0] + -0x18));
          }
        }
      }
    }
    if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar2 = (int *)(local_78[0] + -8);
      iVar7 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
      }
    }
    if ((allocator *)(local_68[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      pwVar5 = local_68[0] + -2;
      wVar4 = *pwVar5;
      *pwVar5 = *pwVar5 + L'\xffffffff';
      UNLOCK();
      if (wVar4 < L'\x01') {
        std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -6));
      }
    }
    if (local_138 != (void *)0x0) {
      operator_delete(local_138);
    }
  }
  return;
}



/* address=00889110
   symbol=CEquipment::unitInit */
/* DECOMPILATION FAILED:
Low-level Error: Overriding symbol with different type size */

/* address=0088b180
   symbol=CEquipment::effectsDescription */

/* WARNING: Removing unreachable block (ram,0x0088c142) */
/* WARNING: Removing unreachable block (ram,0x0088c08a) */
/* WARNING: Removing unreachable block (ram,0x0088c0c2) */
/* WARNING: Removing unreachable block (ram,0x0088c0a6) */
/* WARNING: Removing unreachable block (ram,0x0088bd71) */
/* WARNING: Removing unreachable block (ram,0x0088bde2) */
/* WARNING: Removing unreachable block (ram,0x0088bf8f) */
/* WARNING: Removing unreachable block (ram,0x0088c060) */
/* WARNING: Removing unreachable block (ram,0x0088c044) */
/* WARNING: Removing unreachable block (ram,0x0088bee0) */
/* WARNING: Removing unreachable block (ram,0x0088c098) */
/* WARNING: Removing unreachable block (ram,0x0088c006) */
/* WARNING: Removing unreachable block (ram,0x0088bf84) */
/* WARNING: Removing unreachable block (ram,0x0088bdd7) */
/* WARNING: Removing unreachable block (ram,0x0088c052) */
/* WARNING: Removing unreachable block (ram,0x0088c0b4) */
/* WARNING: Removing unreachable block (ram,0x0088c07c) */
/* WARNING: Removing unreachable block (ram,0x0088c06e) */
/* WARNING: Removing unreachable block (ram,0x0088bd66) */
/* WARNING: Removing unreachable block (ram,0x0088c015) */
/* CEquipment::effectsDescription(EEFFECT_ACTIVATION, bool, bool) */

wstring_conflict *
CEquipment::effectsDescription
          (wstring_conflict *param_1,CBaseUnit *param_2,int param_3,char param_4,char param_5)

{
  wchar_t *pwVar1;
  wchar_t wVar2;
  size_t __n;
  wchar_t *__s1;
  size_t sVar3;
  char cVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  undefined8 *puVar8;
  int *piVar9;
  long lVar10;
  CEffectManager *pCVar11;
  undefined8 uVar12;
  uint uVar13;
  long lVar14;
  long local_1a8 [2];
  long local_198 [2];
  long local_188 [2];
  long local_178 [2];
  long local_168 [2];
  long local_158 [2];
  long local_148 [2];
  long local_138 [2];
  wchar_t *local_128 [2];
  long local_118 [2];
  wstring_conflict local_108 [16];
  wstring_conflict local_f8 [16];
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

  if ((effectsDescription(EEFFECT_ACTIVATION,bool,bool)::g_Damage == '\0') &&
     (iVar7 = __cxa_guard_acquire(&effectsDescription(EEFFECT_ACTIVATION,bool,bool)::g_Damage),
     iVar7 != 0)) {
    effectsDescription(EEFFECT_ACTIVATION,bool,bool)::g_Damage = &DAT_01424558;
    __cxa_guard_release(&effectsDescription(EEFFECT_ACTIVATION,bool,bool)::g_Damage);
    __cxa_atexit(std::wstring::~wstring,&effectsDescription(EEFFECT_ACTIVATION,bool,bool)::g_Damage,
                 &__dso_handle);
  }
  if (*(long *)(effectsDescription(EEFFECT_ACTIVATION,bool,bool)::g_Damage + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_58);
                    /* try { // try from 0088b1e4 to 0088b1e8 has its CatchHandler @ 0088bec9 */
    std::wstring::assign
              ((wstring_conflict *)&effectsDescription(EEFFECT_ACTIVATION,bool,bool)::g_Damage);
    if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar9 = (int *)(local_58[0] + -8);
      iVar7 = *piVar9;
      *piVar9 = *piVar9 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
      }
    }
  }
                    /* try { // try from 0088b214 to 0088b218 has its CatchHandler @ 0088be95 */
  std::wstring::wstring(param_1,L"",local_39);
  if (param_5 == '\0') {
    if (param_3 == 0) {
      lVar14 = *(long *)(param_2 + 0x358);
      lVar10 = *(long *)(param_2 + 0x350);
      if ((int)((ulong)(lVar14 - lVar10) >> 2) != 0) {
        uVar13 = 0;
        do {
          while (0 < *(int *)(*(long *)(param_2 + 0x368) + (ulong)uVar13 * 4)) {
                    /* try { // try from 0088b281 to 0088b29a has its CatchHandler @ 0088be8b */
            CStringTranslate::getSinglton();
            CStringTranslate::getTranslateString((wchar_t *)local_a8);
                    /* try { // try from 0088b2ad to 0088b2b1 has its CatchHandler @ 0088bded */
            STRINGS::GetValueAsWString
                      ((STRINGS *)local_78,*(int *)(*(long *)(param_2 + 0x368) + (ulong)uVar13 * 4))
            ;
                    /* try { // try from 0088b2ba to 0088b2be has its CatchHandler @ 0088be13 */
            std::wstring::wstring((wstring_conflict *)local_68,param_1);
            wcslen(L"+");
                    /* try { // try from 0088b2d4 to 0088b2d8 has its CatchHandler @ 0088be27 */
            std::wstring::append((wchar_t *)local_68,0xfd0b3c);
                    /* try { // try from 0088b2ec to 0088b2f0 has its CatchHandler @ 0088be36 */
            std::operator+((wstring_conflict *)local_88,(wstring_conflict *)local_68);
                    /* try { // try from 0088b2fc to 0088b300 has its CatchHandler @ 0088be45 */
            std::wstring::wstring((wstring_conflict *)local_98,(wstring_conflict *)local_88);
            wcslen(L" ");
                    /* try { // try from 0088b316 to 0088b31a has its CatchHandler @ 0088be59 */
            std::wstring::append((wchar_t *)local_98,0xfd0b98);
                    /* try { // try from 0088b32e to 0088b332 has its CatchHandler @ 0088be68 */
            std::operator+((wstring_conflict *)local_b8,(wstring_conflict *)local_98);
                    /* try { // try from 0088b33e to 0088b342 has its CatchHandler @ 0088be77 */
            std::wstring::wstring((wstring_conflict *)local_c8,(wstring_conflict *)local_b8);
            wcslen(L" ");
                    /* try { // try from 0088b358 to 0088b35c has its CatchHandler @ 0088c0d0 */
            std::wstring::append((wchar_t *)local_c8,0xfd0b98);
                    /* try { // try from 0088b36d to 0088b371 has its CatchHandler @ 0088c0e2 */
            std::operator+((wstring_conflict *)local_d8,(wstring_conflict *)local_c8);
                    /* try { // try from 0088b37f to 0088b383 has its CatchHandler @ 0088c0f4 */
            std::wstring::assign(param_1);
            if ((allocator *)(local_d8[0] + -0x18) !=
                (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar9 = (int *)(local_d8[0] + -8);
              iVar7 = *piVar9;
              *piVar9 = *piVar9 + -1;
              UNLOCK();
              if (iVar7 < 1) {
                std::wstring::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
              }
            }
            if ((allocator *)(local_c8[0] + -0x18) !=
                (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar9 = (int *)(local_c8[0] + -8);
              iVar7 = *piVar9;
              *piVar9 = *piVar9 + -1;
              UNLOCK();
              if (iVar7 < 1) {
                std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
              }
            }
            if ((allocator *)(local_b8[0] + -0x18) !=
                (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar9 = (int *)(local_b8[0] + -8);
              iVar7 = *piVar9;
              *piVar9 = *piVar9 + -1;
              UNLOCK();
              if (iVar7 < 1) {
                std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
              }
            }
            if ((allocator *)(local_98[0] + -0x18) !=
                (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar9 = (int *)(local_98[0] + -8);
              iVar7 = *piVar9;
              *piVar9 = *piVar9 + -1;
              UNLOCK();
              if (iVar7 < 1) {
                std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
              }
            }
            if ((allocator *)(local_88[0] + -0x18) !=
                (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar9 = (int *)(local_88[0] + -8);
              iVar7 = *piVar9;
              *piVar9 = *piVar9 + -1;
              UNLOCK();
              if (iVar7 < 1) {
                std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
              }
            }
            if ((allocator *)(local_68[0] + -0x18) !=
                (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar9 = (int *)(local_68[0] + -8);
              iVar7 = *piVar9;
              *piVar9 = *piVar9 + -1;
              UNLOCK();
              if (iVar7 < 1) {
                std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
              }
            }
            if ((allocator *)(local_78[0] + -0x18) !=
                (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar9 = (int *)(local_78[0] + -8);
              iVar7 = *piVar9;
              *piVar9 = *piVar9 + -1;
              UNLOCK();
              if (iVar7 < 1) {
                std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
              }
            }
            if ((allocator *)(local_a8[0] + -0x18) !=
                (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar9 = (int *)(local_a8[0] + -8);
              iVar7 = *piVar9;
              *piVar9 = *piVar9 + -1;
              UNLOCK();
              if (iVar7 < 1) {
                std::wstring::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
              }
            }
            lVar14 = *(long *)(param_2 + 0x358);
            lVar10 = *(long *)(param_2 + 0x350);
            uVar5 = (uint)((ulong)(lVar14 - lVar10) >> 2);
            if (uVar13 != uVar5 - 1) {
                    /* try { // try from 0088b45e to 0088b462 has its CatchHandler @ 0088be8b */
              std::wstring::wstring((wstring_conflict *)local_e8,param_1);
              wcslen(L"\n");
                    /* try { // try from 0088b47d to 0088b481 has its CatchHandler @ 0088c108 */
              std::wstring::append((wchar_t *)local_e8,0xfd0b48);
                    /* try { // try from 0088b48f to 0088b493 has its CatchHandler @ 0088c140 */
              std::wstring::assign(param_1);
              if ((allocator *)(local_e8[0] + -0x18) !=
                  (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar9 = (int *)(local_e8[0] + -8);
                iVar7 = *piVar9;
                *piVar9 = *piVar9 + -1;
                UNLOCK();
                if (iVar7 < 1) {
                  std::wstring::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
                }
              }
              lVar14 = *(long *)(param_2 + 0x358);
              lVar10 = *(long *)(param_2 + 0x350);
              uVar5 = (uint)((ulong)(lVar14 - lVar10) >> 2);
            }
            uVar13 = uVar13 + 1;
            if (uVar5 <= uVar13) goto LAB_0088b4f2;
          }
          uVar13 = uVar13 + 1;
        } while (uVar13 < (uint)((ulong)(lVar14 - lVar10) >> 2));
      }
    }
LAB_0088b4f2:
    pCVar11 = *(CEffectManager **)(param_2 + 0x1b8);
    if (pCVar11 != (CEffectManager *)0x0) {
      uVar12 = 0;
      if (param_4 != '\x01') {
                    /* try { // try from 0088b514 to 0088b585 has its CatchHandler @ 0088be8b */
        cVar4 = CBaseUnit::ISA(param_2,0x78);
                    /* try { // try from 0088bb31 to 0088bb35 has its CatchHandler @ 0088be8b */
        if ((cVar4 == '\0') || (cVar4 = CBaseUnit::ISA(param_2,0xa0), cVar4 != '\0')) {
          pCVar11 = *(CEffectManager **)(param_2 + 0x1b8);
          uVar12 = 0;
        }
        else {
          pCVar11 = *(CEffectManager **)(param_2 + 0x1b8);
          uVar12 = 1;
        }
      }
      puVar8 = (undefined8 *)
               CEffectManager::getVisualDescription(pCVar11,param_3,0xffffffff,1,uVar12);
      pwVar1 = ::EMPTY_WSTRING;
      __n = *(size_t *)(::EMPTY_WSTRING + -6);
      if (*(size_t *)((wchar_t *)*puVar8 + -6) == __n) {
        iVar7 = wmemcmp((wchar_t *)*puVar8,::EMPTY_WSTRING,__n);
        if (iVar7 == 0) goto LAB_0088b5c0;
        __s1 = *(wchar_t **)param_1;
        sVar3 = *(size_t *)(__s1 + -6);
      }
      else {
        __s1 = *(wchar_t **)param_1;
        sVar3 = *(size_t *)(__s1 + -6);
      }
      if ((__n == sVar3) && (iVar7 = wmemcmp(__s1,pwVar1,__n), iVar7 == 0)) {
        std::wstring::assign(param_1);
      }
      else {
        std::operator+(local_f8,(wchar_t *)param_1);
                    /* try { // try from 0088b597 to 0088b59b has its CatchHandler @ 0088c03d */
        std::operator+(local_108,local_f8);
                    /* try { // try from 0088b5a4 to 0088b5a8 has its CatchHandler @ 0088c023 */
        std::wstring::assign(param_1);
                    /* try { // try from 0088b5ac to 0088b5b0 has its CatchHandler @ 0088c03d */
        std::wstring::~wstring(local_108);
                    /* try { // try from 0088b5b4 to 0088b60e has its CatchHandler @ 0088be8b */
        std::wstring::~wstring(local_f8);
      }
    }
  }
  else {
    iVar7 = *(int *)(param_2 + 0x3f0);
    std::wstring::wstring((wstring_conflict *)local_118,(wstring_conflict *)&::EMPTY_WSTRING);
    if (0 < iVar7) {
      lVar14 = 0;
      uVar13 = 0;
      do {
        if (uVar13 < *(uint *)(param_2 + 0x3f4)) {
          puVar8 = (undefined8 *)(lVar14 + *(long *)(param_2 + 1000));
        }
        else {
          puVar8 = *(undefined8 **)(param_2 + 1000);
        }
                    /* try { // try from 0088b649 to 0088b64d has its CatchHandler @ 0088bf25 */
        effectsDescription(local_128,*puVar8,param_3,1,0);
        if ((*(size_t *)(local_128[0] + -6) != *(size_t *)(::EMPTY_WSTRING + -6)) ||
           (iVar6 = wmemcmp(local_128[0],::EMPTY_WSTRING,*(size_t *)(local_128[0] + -6)), iVar6 != 0
           )) {
          lVar10 = *(long *)(local_118[0] + -0x18);
          if (lVar10 != 0) {
            if (-1 < *(int *)(local_118[0] + -8)) {
                    /* try { // try from 0088b7ca to 0088b7f2 has its CatchHandler @ 0088c11f */
              std::wstring::_M_leak_hard();
            }
            if (*(int *)(local_118[0] + -4 + lVar10 * 4) != 10) {
              std::wstring::wstring((wstring_conflict *)local_138,(wstring_conflict *)local_118);
              wcslen(L"\n");
                    /* try { // try from 0088b80d to 0088b811 has its CatchHandler @ 0088beeb */
              std::wstring::append((wchar_t *)local_138,0xfd0b48);
                    /* try { // try from 0088b81d to 0088b821 has its CatchHandler @ 0088bf12 */
              std::wstring::assign((wstring_conflict *)local_118);
              if ((allocator *)(local_138[0] + -0x18) !=
                  (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar9 = (int *)(local_138[0] + -8);
                iVar6 = *piVar9;
                *piVar9 = *piVar9 + -1;
                UNLOCK();
                if (iVar6 < 1) {
                  std::wstring::_Rep::_M_destroy((allocator *)(local_138[0] + -0x18));
                }
              }
            }
          }
                    /* try { // try from 0088b68e to 0088b692 has its CatchHandler @ 0088c11f */
          std::operator+((wstring_conflict *)local_148,(wstring_conflict *)local_118);
                    /* try { // try from 0088b69e to 0088b6a2 has its CatchHandler @ 0088c129 */
          std::wstring::assign((wstring_conflict *)local_118);
          if ((allocator *)(local_148[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar9 = (int *)(local_148[0] + -8);
            iVar6 = *piVar9;
            *piVar9 = *piVar9 + -1;
            UNLOCK();
            if (iVar6 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_148[0] + -0x18));
            }
          }
        }
        lVar10 = *(long *)(local_118[0] + -0x18);
        if (lVar10 != 0) {
          if (-1 < *(int *)(local_118[0] + -8)) {
                    /* try { // try from 0088b724 to 0088b74f has its CatchHandler @ 0088c11f */
            std::wstring::_M_leak_hard();
          }
          if (*(int *)(local_118[0] + -4 + lVar10 * 4) == 10) {
            std::wstring::wstring
                      ((wstring_conflict *)local_158,(wstring_conflict *)local_118,0,
                       *(long *)(local_118[0] + -0x18) - 1);
                    /* try { // try from 0088b758 to 0088b75c has its CatchHandler @ 0088bf14 */
            std::wstring::assign((wstring_conflict *)local_118);
            if ((allocator *)(local_158[0] + -0x18) !=
                (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar9 = (int *)(local_158[0] + -8);
              iVar6 = *piVar9;
              *piVar9 = *piVar9 + -1;
              UNLOCK();
              if (iVar6 < 1) {
                std::wstring::_Rep::_M_destroy((allocator *)(local_158[0] + -0x18));
              }
            }
          }
        }
        if ((allocator *)(local_128[0] + -6) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          pwVar1 = local_128[0] + -2;
          wVar2 = *pwVar1;
          *pwVar1 = *pwVar1 + L'\xffffffff';
          UNLOCK();
          if (wVar2 < L'\x01') {
            std::wstring::_Rep::_M_destroy((allocator *)(local_128[0] + -6));
          }
        }
        uVar13 = uVar13 + 1;
        lVar14 = lVar14 + 8;
      } while ((int)uVar13 < iVar7);
    }
    if (*(long *)(local_118[0] + -0x18) != 0) {
                    /* try { // try from 0088bb16 to 0088bb1a has its CatchHandler @ 0088bf25 */
      if ((*(long *)(*(long *)param_1 + -0x18) == 0) ||
         (piVar9 = (int *)std::wstring::operator[]((ulong)param_1), *piVar9 != 10)) {
                    /* try { // try from 0088b8a9 to 0088b8ad has its CatchHandler @ 0088bf25 */
        std::wstring::wstring((wstring_conflict *)local_168,param_1);
        wcslen(L"\n");
                    /* try { // try from 0088b8c3 to 0088b8c7 has its CatchHandler @ 0088c004 */
        std::wstring::append((wchar_t *)local_168,0xfd0b48);
                    /* try { // try from 0088b8d0 to 0088b8d4 has its CatchHandler @ 0088bff2 */
        std::wstring::assign(param_1);
        if ((allocator *)(local_168[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar9 = (int *)(local_168[0] + -8);
          iVar7 = *piVar9;
          *piVar9 = *piVar9 + -1;
          UNLOCK();
          if (iVar7 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_168[0] + -0x18));
          }
        }
      }
                    /* try { // try from 0088b90e to 0088b92b has its CatchHandler @ 0088bf25 */
      CGameGlobals::getSingleton();
      std::wstring::wstring((wstring_conflict *)local_178,param_1);
      wcslen(L"|c");
                    /* try { // try from 0088b941 to 0088b945 has its CatchHandler @ 0088bfe0 */
      std::wstring::append((wchar_t *)local_178,0xfd0b74);
                    /* try { // try from 0088b954 to 0088b958 has its CatchHandler @ 0088bfd9 */
      std::operator+((wstring_conflict *)local_188,(wstring_conflict *)local_178);
                    /* try { // try from 0088b967 to 0088b96b has its CatchHandler @ 0088bfd2 */
      std::operator+((wstring_conflict *)local_198,(wstring_conflict *)local_188);
                    /* try { // try from 0088b977 to 0088b97b has its CatchHandler @ 0088bfc6 */
      std::wstring::wstring((wstring_conflict *)local_1a8,(wstring_conflict *)local_198);
      wcslen(L"|u");
                    /* try { // try from 0088b991 to 0088b995 has its CatchHandler @ 0088bfc4 */
      std::wstring::append((wchar_t *)local_1a8,0xfc8340);
                    /* try { // try from 0088b99e to 0088b9a2 has its CatchHandler @ 0088bf9a */
      std::wstring::assign(param_1);
      if ((allocator *)(local_1a8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar9 = (int *)(local_1a8[0] + -8);
        iVar7 = *piVar9;
        *piVar9 = *piVar9 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_1a8[0] + -0x18));
        }
      }
      if ((allocator *)(local_198[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar9 = (int *)(local_198[0] + -8);
        iVar7 = *piVar9;
        *piVar9 = *piVar9 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_198[0] + -0x18));
        }
      }
      if ((allocator *)(local_188[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar9 = (int *)(local_188[0] + -8);
        iVar7 = *piVar9;
        *piVar9 = *piVar9 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_188[0] + -0x18));
        }
      }
      if ((allocator *)(local_178[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar9 = (int *)(local_178[0] + -8);
        iVar7 = *piVar9;
        *piVar9 = *piVar9 + -1;
        UNLOCK();
        if (iVar7 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_178[0] + -0x18));
        }
      }
    }
    if ((allocator *)(local_118[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar9 = (int *)(local_118[0] + -8);
      iVar7 = *piVar9;
      *piVar9 = *piVar9 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_118[0] + -0x18));
      }
    }
  }
LAB_0088b5c0:
  lVar14 = *(long *)param_1;
  lVar10 = *(long *)(lVar14 + -0x18);
  if (lVar10 != 0) {
    if (-1 < *(int *)(lVar14 + -8)) {
                    /* try { // try from 0088ba8c to 0088bb09 has its CatchHandler @ 0088be8b */
      std::wstring::_M_leak_hard();
      lVar14 = *(long *)param_1;
    }
    if (*(int *)(lVar14 + -4 + lVar10 * 4) != 10) {
      wcslen(L"\n");
      std::wstring::append((wchar_t *)param_1,0xfd0b48);
    }
  }
  return param_1;
}



/* address=0088c150
   symbol=CEquipment::getEquipmentEffects */

/* WARNING: Removing unreachable block (ram,0x0088d025) */
/* CEquipment::getEquipmentEffects() */

void CEquipment::getEquipmentEffects(void)

{
  int *piVar1;
  int iVar2;
  undefined8 uVar3;
  long lVar4;
  long lVar5;
  wstring_conflict *this;
  long in_RSI;
  wstring_conflict *in_RDI;
  wstring_conflict awStack_348 [16];
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
  long local_218 [2];
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
  int *local_148 [2];
  wstring_conflict local_138 [16];
  wstring_conflict local_128 [16];
  int *local_118 [2];
  wstring_conflict local_108 [16];
  int *local_f8 [2];
  wstring_conflict local_e8 [16];
  wstring_conflict local_d8 [16];
  int *local_c8 [2];
  wstring_conflict local_b8 [16];
  int *local_a8 [2];
  wstring_conflict local_98 [16];
  wstring_conflict local_88 [16];
  int *local_78 [2];
  wstring_conflict local_68 [16];
  int *local_58 [2];
  wstring_conflict local_48 [24];

  *(undefined4 **)in_RDI = &DAT_01424558;
  if (*(char *)(in_RSI + 0x348) == '\0') {
    return;
  }
                    /* try { // try from 0088c1a5 to 0088c1a9 has its CatchHandler @ 0088ce42 */
  effectsDescription(local_48,in_RSI,1,0,0);
  this = (wstring_conflict *)local_58;
                    /* try { // try from 0088c1b8 to 0088c1bc has its CatchHandler @ 0088ce4a */
  std::wstring::wstring(this,local_48);
  while (lVar5 = *(long *)(local_58[0] + -6), lVar5 != 0) {
    lVar4 = lVar5;
    if (-1 < local_58[0][-2]) {
                    /* try { // try from 0088c7bd to 0088c7c1 has its CatchHandler @ 0088ce02 */
      std::wstring::_M_leak_hard();
      lVar4 = *(long *)(local_58[0] + -6);
    }
    if (local_58[0][lVar5 + -1] != 10) {
      lVar5 = *(long *)(local_58[0] + -6);
      goto LAB_0088c1df;
    }
                    /* try { // try from 0088cc2c to 0088cc30 has its CatchHandler @ 0088ce02 */
    std::wstring::wstring(local_278,this,0,lVar4 - 1);
                    /* try { // try from 0088cc37 to 0088cc3b has its CatchHandler @ 0088cf3a */
    std::wstring::assign(this);
                    /* try { // try from 0088cc3f to 0088cc43 has its CatchHandler @ 0088ce02 */
    std::wstring::~wstring(local_278);
  }
  lVar5 = 0;
LAB_0088c1df:
  while (lVar5 != 0) {
    if (-1 < local_58[0][-2]) {
                    /* try { // try from 0088c82c to 0088c862 has its CatchHandler @ 0088ce02 */
      std::wstring::_M_leak_hard();
    }
    if (*local_58[0] != 10) break;
    if (*(long *)(local_58[0] + -6) == 0) goto LAB_0088cd73;
    std::wstring::wstring(local_288,this,1,*(long *)(local_58[0] + -6) - 1);
                    /* try { // try from 0088c869 to 0088c86d has its CatchHandler @ 0088ce06 */
    std::wstring::assign(this);
                    /* try { // try from 0088c871 to 0088c875 has its CatchHandler @ 0088ce02 */
    std::wstring::~wstring(local_288);
    lVar5 = *(long *)(local_58[0] + -6);
  }
                    /* try { // try from 0088c20a to 0088c20e has its CatchHandler @ 0088ce52 */
  std::operator+(local_68,in_RDI);
                    /* try { // try from 0088c215 to 0088c219 has its CatchHandler @ 0088ce57 */
  std::wstring::assign(in_RDI);
                    /* try { // try from 0088c21d to 0088c221 has its CatchHandler @ 0088ce52 */
  std::wstring::~wstring(local_68);
                    /* try { // try from 0088c225 to 0088c229 has its CatchHandler @ 0088ce4a */
  std::wstring::~wstring(this);
                    /* try { // try from 0088c22d to 0088c29a has its CatchHandler @ 0088ce42 */
  std::wstring::~wstring(local_48);
  this = (wstring_conflict *)local_78;
  std::wstring::wstring(this,in_RDI);
  while (lVar5 = *(long *)(local_78[0] + -6), lVar5 != 0) {
    lVar4 = lVar5;
    if (-1 < local_78[0][-2]) {
                    /* try { // try from 0088c7f7 to 0088c7fb has its CatchHandler @ 0088ce04 */
      std::wstring::_M_leak_hard();
      lVar4 = *(long *)(local_78[0] + -6);
    }
    if (local_78[0][lVar5 + -1] != 10) {
      lVar5 = *(long *)(local_78[0] + -6);
      goto LAB_0088c267;
    }
                    /* try { // try from 0088cc5c to 0088cc60 has its CatchHandler @ 0088ce04 */
    std::wstring::wstring(local_298,this,0,lVar4 - 1);
                    /* try { // try from 0088cc67 to 0088cc6b has its CatchHandler @ 0088cf3f */
    std::wstring::assign(this);
                    /* try { // try from 0088cc6f to 0088cc73 has its CatchHandler @ 0088ce04 */
    std::wstring::~wstring(local_298);
  }
  lVar5 = 0;
LAB_0088c267:
  while (lVar5 != 0) {
    if (-1 < local_78[0][-2]) {
                    /* try { // try from 0088c8d4 to 0088c90a has its CatchHandler @ 0088ce04 */
      std::wstring::_M_leak_hard();
    }
    if (*local_78[0] != 10) break;
    if (*(long *)(local_78[0] + -6) == 0) goto LAB_0088cd7d;
    std::wstring::wstring(local_2a8,this,1,*(long *)(local_78[0] + -6) - 1);
                    /* try { // try from 0088c911 to 0088c915 has its CatchHandler @ 0088cdec */
    std::wstring::assign(this);
                    /* try { // try from 0088c919 to 0088c91d has its CatchHandler @ 0088ce04 */
    std::wstring::~wstring(local_2a8);
    lVar5 = *(long *)(local_78[0] + -6);
  }
  std::wstring::~wstring(this);
  effectsDescription(local_98);
  this = (wstring_conflict *)local_a8;
                    /* try { // try from 0088c2a9 to 0088c2ad has its CatchHandler @ 0088cfb8 */
  std::wstring::wstring(this,local_98);
  while (lVar5 = *(long *)(local_a8[0] + -6), lVar5 != 0) {
    lVar4 = lVar5;
    if (-1 < local_a8[0][-2]) {
                    /* try { // try from 0088c89f to 0088c8a3 has its CatchHandler @ 0088ce17 */
      std::wstring::_M_leak_hard();
      lVar4 = *(long *)(local_a8[0] + -6);
    }
    if (local_a8[0][lVar5 + -1] != 10) {
      lVar5 = *(long *)(local_a8[0] + -6);
      goto LAB_0088c2d7;
    }
                    /* try { // try from 0088cc8c to 0088cc90 has its CatchHandler @ 0088ce17 */
    std::wstring::wstring(local_2b8,this,0,lVar4 - 1);
                    /* try { // try from 0088cc97 to 0088cc9b has its CatchHandler @ 0088cf45 */
    std::wstring::assign(this);
                    /* try { // try from 0088cc9f to 0088cca3 has its CatchHandler @ 0088ce17 */
    std::wstring::~wstring(local_2b8);
  }
  lVar5 = 0;
LAB_0088c2d7:
  while (lVar5 != 0) {
    if (-1 < local_a8[0][-2]) {
                    /* try { // try from 0088c972 to 0088c9a8 has its CatchHandler @ 0088ce17 */
      std::wstring::_M_leak_hard();
    }
    if (*local_a8[0] != 10) break;
    if (*(long *)(local_a8[0] + -6) == 0) goto LAB_0088cd87;
    std::wstring::wstring(local_2c8,this,1,*(long *)(local_a8[0] + -6) - 1);
                    /* try { // try from 0088c9af to 0088c9b3 has its CatchHandler @ 0088cdf2 */
    std::wstring::assign(this);
                    /* try { // try from 0088c9b7 to 0088c9bb has its CatchHandler @ 0088ce17 */
    std::wstring::~wstring(local_2c8);
    lVar5 = *(long *)(local_a8[0] + -6);
  }
                    /* try { // try from 0088c2fc to 0088c300 has its CatchHandler @ 0088d015 */
  std::operator+(local_88,(wchar_t *)in_RDI);
                    /* try { // try from 0088c312 to 0088c316 has its CatchHandler @ 0088cff5 */
  std::operator+(local_b8,local_88);
                    /* try { // try from 0088c31d to 0088c321 has its CatchHandler @ 0088d005 */
  std::wstring::assign(in_RDI);
                    /* try { // try from 0088c325 to 0088c329 has its CatchHandler @ 0088cff5 */
  std::wstring::~wstring(local_b8);
                    /* try { // try from 0088c32d to 0088c331 has its CatchHandler @ 0088d015 */
  std::wstring::~wstring(local_88);
                    /* try { // try from 0088c335 to 0088c339 has its CatchHandler @ 0088cfb8 */
  std::wstring::~wstring(this);
                    /* try { // try from 0088c33d to 0088c3ad has its CatchHandler @ 0088ce42 */
  std::wstring::~wstring(local_98);
  this = (wstring_conflict *)local_c8;
  std::wstring::wstring(this,in_RDI);
  while (lVar5 = *(long *)(local_c8[0] + -6), lVar5 != 0) {
    lVar4 = lVar5;
    if (-1 < local_c8[0][-2]) {
                    /* try { // try from 0088c93d to 0088c941 has its CatchHandler @ 0088cdee */
      std::wstring::_M_leak_hard();
      lVar4 = *(long *)(local_c8[0] + -6);
    }
    if (local_c8[0][lVar5 + -1] != 10) {
      lVar5 = *(long *)(local_c8[0] + -6);
      goto LAB_0088c377;
    }
                    /* try { // try from 0088ccbc to 0088ccc0 has its CatchHandler @ 0088cdee */
    std::wstring::wstring(local_2d8,this,0,lVar4 - 1);
                    /* try { // try from 0088ccc7 to 0088cccb has its CatchHandler @ 0088ce19 */
    std::wstring::assign(this);
                    /* try { // try from 0088cccf to 0088ccd3 has its CatchHandler @ 0088cdee */
    std::wstring::~wstring(local_2d8);
  }
  lVar5 = 0;
LAB_0088c377:
  while (lVar5 != 0) {
    if (-1 < local_c8[0][-2]) {
                    /* try { // try from 0088ca12 to 0088ca48 has its CatchHandler @ 0088cdee */
      std::wstring::_M_leak_hard();
    }
    if (*local_c8[0] != 10) break;
    if (*(long *)(local_c8[0] + -6) == 0) goto LAB_0088cd91;
    std::wstring::wstring(local_2e8,this,1,*(long *)(local_c8[0] + -6) - 1);
                    /* try { // try from 0088ca4f to 0088ca53 has its CatchHandler @ 0088cf55 */
    std::wstring::assign(this);
                    /* try { // try from 0088ca57 to 0088ca5b has its CatchHandler @ 0088cdee */
    std::wstring::~wstring(local_2e8);
    lVar5 = *(long *)(local_c8[0] + -6);
  }
  std::wstring::~wstring(this);
  effectsDescription(local_e8);
  this = (wstring_conflict *)local_f8;
                    /* try { // try from 0088c3bc to 0088c3c0 has its CatchHandler @ 0088cfbd */
  std::wstring::wstring(this,local_e8);
  while (lVar5 = *(long *)(local_f8[0] + -6), lVar5 != 0) {
    lVar4 = lVar5;
    if (-1 < local_f8[0][-2]) {
                    /* try { // try from 0088c9dd to 0088c9e1 has its CatchHandler @ 0088cdff */
      std::wstring::_M_leak_hard();
      lVar4 = *(long *)(local_f8[0] + -6);
    }
    if (local_f8[0][lVar5 + -1] != 10) {
      lVar5 = *(long *)(local_f8[0] + -6);
      goto LAB_0088c3e7;
    }
                    /* try { // try from 0088ccec to 0088ccf0 has its CatchHandler @ 0088cdff */
    std::wstring::wstring(local_2f8,this,0,lVar4 - 1);
                    /* try { // try from 0088ccf7 to 0088ccfb has its CatchHandler @ 0088ce27 */
    std::wstring::assign(this);
                    /* try { // try from 0088ccff to 0088cd03 has its CatchHandler @ 0088cdff */
    std::wstring::~wstring(local_2f8);
  }
  lVar5 = 0;
LAB_0088c3e7:
LAB_0088c3f0:
  if (lVar5 != 0) {
    if (-1 < local_f8[0][-2]) {
                    /* try { // try from 0088cab4 to 0088caea has its CatchHandler @ 0088cdff */
      std::wstring::_M_leak_hard();
    }
    if (*local_f8[0] == 10) {
      if (*(long *)(local_f8[0] + -6) != 0) goto code_r0x0088cad7;
                    /* try { // try from 0088cd6e to 0088cd72 has its CatchHandler @ 0088cdff */
      std::__throw_out_of_range("basic_string::substr");
LAB_0088cd73:
                    /* try { // try from 0088cd78 to 0088cd7c has its CatchHandler @ 0088ce02 */
      std::__throw_out_of_range("basic_string::substr");
LAB_0088cd7d:
                    /* try { // try from 0088cd82 to 0088cd86 has its CatchHandler @ 0088ce04 */
      std::__throw_out_of_range("basic_string::substr");
LAB_0088cd87:
                    /* try { // try from 0088cd8c to 0088cd90 has its CatchHandler @ 0088ce17 */
      std::__throw_out_of_range("basic_string::substr");
LAB_0088cd91:
                    /* try { // try from 0088cd96 to 0088cd9a has its CatchHandler @ 0088cdee */
      std::__throw_out_of_range("basic_string::substr");
      goto LAB_0088cd9b;
    }
  }
                    /* try { // try from 0088c40c to 0088c410 has its CatchHandler @ 0088cfc5 */
  std::operator+(local_d8,(wchar_t *)in_RDI);
                    /* try { // try from 0088c422 to 0088c426 has its CatchHandler @ 0088cfd5 */
  std::operator+(local_108,local_d8);
                    /* try { // try from 0088c42d to 0088c431 has its CatchHandler @ 0088cfe5 */
  std::wstring::assign(in_RDI);
                    /* try { // try from 0088c435 to 0088c439 has its CatchHandler @ 0088cfd5 */
  std::wstring::~wstring(local_108);
                    /* try { // try from 0088c43d to 0088c441 has its CatchHandler @ 0088cfc5 */
  std::wstring::~wstring(local_d8);
                    /* try { // try from 0088c445 to 0088c449 has its CatchHandler @ 0088cfbd */
  std::wstring::~wstring(this);
                    /* try { // try from 0088c44d to 0088c4c0 has its CatchHandler @ 0088ce42 */
  std::wstring::~wstring(local_e8);
  this = (wstring_conflict *)local_118;
  std::wstring::wstring(this,in_RDI);
  while (lVar5 = *(long *)(local_118[0] + -6), lVar5 != 0) {
    lVar4 = lVar5;
    if (-1 < local_118[0][-2]) {
                    /* try { // try from 0088ca7f to 0088ca83 has its CatchHandler @ 0088cf65 */
      std::wstring::_M_leak_hard();
      lVar4 = *(long *)(local_118[0] + -6);
    }
    if (local_118[0][lVar5 + -1] != 10) {
      lVar5 = *(long *)(local_118[0] + -6);
      goto LAB_0088c487;
    }
                    /* try { // try from 0088cd1c to 0088cd20 has its CatchHandler @ 0088cf65 */
    std::wstring::wstring(local_318,this,0,lVar4 - 1);
                    /* try { // try from 0088cd27 to 0088cd2b has its CatchHandler @ 0088ce34 */
    std::wstring::assign(this);
                    /* try { // try from 0088cd2f to 0088cd33 has its CatchHandler @ 0088cf65 */
    std::wstring::~wstring(local_318);
  }
  lVar5 = 0;
LAB_0088c487:
  while (lVar5 != 0) {
    if (-1 < local_118[0][-2]) {
                    /* try { // try from 0088cbbc to 0088cbf2 has its CatchHandler @ 0088cf65 */
      std::wstring::_M_leak_hard();
    }
    if (*local_118[0] != 10) break;
    if (*(long *)(local_118[0] + -6) == 0) goto LAB_0088cd9b;
    std::wstring::wstring(local_328,this,1,*(long *)(local_118[0] + -6) - 1);
                    /* try { // try from 0088cbf9 to 0088cbfd has its CatchHandler @ 0088cddf */
    std::wstring::assign(this);
                    /* try { // try from 0088cc01 to 0088cc05 has its CatchHandler @ 0088cf65 */
    std::wstring::~wstring(local_328);
    lVar5 = *(long *)(local_118[0] + -6);
  }
  std::wstring::~wstring(this);
  effectsDescription(local_138);
  this = (wstring_conflict *)local_148;
                    /* try { // try from 0088c4cf to 0088c4d3 has its CatchHandler @ 0088cec3 */
  std::wstring::wstring(this,local_138);
  while (lVar5 = *(long *)(local_148[0] + -6), lVar5 != 0) {
    lVar4 = lVar5;
    if (-1 < local_148[0][-2]) {
                    /* try { // try from 0088cb1f to 0088cb88 has its CatchHandler @ 0088cdca */
      std::wstring::_M_leak_hard();
      lVar4 = *(long *)(local_148[0] + -6);
    }
    if (local_148[0][lVar5 + -1] != 10) {
      lVar5 = *(long *)(local_148[0] + -6);
      goto joined_r0x0088cb42;
    }
                    /* try { // try from 0088cd4c to 0088cd50 has its CatchHandler @ 0088cdca */
    std::wstring::wstring(local_338,this,0,lVar4 - 1);
                    /* try { // try from 0088cd57 to 0088cd5b has its CatchHandler @ 0088ce36 */
    std::wstring::assign(this);
                    /* try { // try from 0088cd5f to 0088cd63 has its CatchHandler @ 0088cdca */
    std::wstring::~wstring(local_338);
  }
  lVar5 = 0;
joined_r0x0088cb42:
  do {
    if (lVar5 == 0) {
LAB_0088c500:
                    /* try { // try from 0088c513 to 0088c517 has its CatchHandler @ 0088cec5 */
      std::operator+(local_128,(wchar_t *)in_RDI);
                    /* try { // try from 0088c529 to 0088c52d has its CatchHandler @ 0088ced5 */
      std::operator+(local_158,local_128);
                    /* try { // try from 0088c534 to 0088c538 has its CatchHandler @ 0088cee5 */
      std::wstring::assign(in_RDI);
                    /* try { // try from 0088c53c to 0088c540 has its CatchHandler @ 0088ced5 */
      std::wstring::~wstring(local_158);
                    /* try { // try from 0088c544 to 0088c548 has its CatchHandler @ 0088cec5 */
      std::wstring::~wstring(local_128);
                    /* try { // try from 0088c54c to 0088c550 has its CatchHandler @ 0088cec3 */
      std::wstring::~wstring(this);
                    /* try { // try from 0088c554 to 0088c590 has its CatchHandler @ 0088ce42 */
      std::wstring::~wstring(local_138);
      removeWhiteSpace(local_168);
      std::wstring::~wstring(local_168);
      effectsDescription(local_188);
                    /* try { // try from 0088c59f to 0088c5a3 has its CatchHandler @ 0088cefa */
      removeWhiteSpace(local_198);
                    /* try { // try from 0088c5b7 to 0088c5bb has its CatchHandler @ 0088ceff */
      std::operator+(local_178,(wchar_t *)in_RDI);
                    /* try { // try from 0088c5cd to 0088c5d1 has its CatchHandler @ 0088cf05 */
      std::operator+(local_1a8,local_178);
                    /* try { // try from 0088c5d8 to 0088c5dc has its CatchHandler @ 0088cf15 */
      std::wstring::assign(in_RDI);
                    /* try { // try from 0088c5e0 to 0088c5e4 has its CatchHandler @ 0088cf05 */
      std::wstring::~wstring(local_1a8);
                    /* try { // try from 0088c5e8 to 0088c5ec has its CatchHandler @ 0088ceff */
      std::wstring::~wstring(local_178);
                    /* try { // try from 0088c5f0 to 0088c5f4 has its CatchHandler @ 0088cefa */
      std::wstring::~wstring(local_198);
                    /* try { // try from 0088c5f8 to 0088c637 has its CatchHandler @ 0088ce42 */
      std::wstring::~wstring(local_188);
      removeWhiteSpace(local_1b8);
      std::wstring::~wstring(local_1b8);
      effectsDescription(local_1d8);
                    /* try { // try from 0088c646 to 0088c64a has its CatchHandler @ 0088ce59 */
      removeWhiteSpace(local_1e8);
                    /* try { // try from 0088c65e to 0088c662 has its CatchHandler @ 0088ce62 */
      std::operator+(local_1c8,(wchar_t *)in_RDI);
                    /* try { // try from 0088c674 to 0088c678 has its CatchHandler @ 0088ce72 */
      std::operator+(local_1f8,local_1c8);
                    /* try { // try from 0088c67f to 0088c683 has its CatchHandler @ 0088ce7f */
      std::wstring::assign(in_RDI);
                    /* try { // try from 0088c687 to 0088c68b has its CatchHandler @ 0088ce72 */
      std::wstring::~wstring(local_1f8);
                    /* try { // try from 0088c68f to 0088c693 has its CatchHandler @ 0088ce62 */
      std::wstring::~wstring(local_1c8);
                    /* try { // try from 0088c697 to 0088c69b has its CatchHandler @ 0088ce59 */
      std::wstring::~wstring(local_1e8);
                    /* try { // try from 0088c69f to 0088c6d1 has its CatchHandler @ 0088ce42 */
      std::wstring::~wstring(local_1d8);
      removeWhiteSpace(local_208);
      std::wstring::~wstring(local_208);
      skillDescription();
                    /* try { // try from 0088c6e0 to 0088c6e4 has its CatchHandler @ 0088ce8c */
      removeWhiteSpace(local_238);
                    /* try { // try from 0088c6f8 to 0088c6fc has its CatchHandler @ 0088ce9c */
      std::operator+((wstring_conflict *)local_218,(wchar_t *)in_RDI);
                    /* try { // try from 0088c70e to 0088c712 has its CatchHandler @ 0088cea9 */
      std::operator+(local_248,(wstring_conflict *)local_218);
                    /* try { // try from 0088c719 to 0088c71d has its CatchHandler @ 0088ceb6 */
      std::wstring::assign(in_RDI);
                    /* try { // try from 0088c721 to 0088c725 has its CatchHandler @ 0088cea9 */
      std::wstring::~wstring(local_248);
      if ((allocator *)(local_218[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_218[0] + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_218[0] + -0x18));
        }
      }
                    /* try { // try from 0088c742 to 0088c746 has its CatchHandler @ 0088ce8c */
      std::wstring::~wstring(local_238);
                    /* try { // try from 0088c74a to 0088c790 has its CatchHandler @ 0088ce42 */
      std::wstring::~wstring(local_228);
      removeWhiteSpace(local_258);
      std::wstring::~wstring(local_258);
      if (*(long *)(*(long *)in_RDI + -0x18) == 0) {
        return;
      }
      std::operator+(local_268,(wchar_t *)in_RDI);
                    /* try { // try from 0088c797 to 0088c79b has its CatchHandler @ 0088cdaf */
      std::wstring::assign(in_RDI);
                    /* try { // try from 0088c79f to 0088c7a3 has its CatchHandler @ 0088ce42 */
      std::wstring::~wstring(local_268);
      return;
    }
    if (-1 < local_148[0][-2]) {
      std::wstring::_M_leak_hard();
    }
    if (*local_148[0] != 10) goto LAB_0088c500;
    if (*(long *)(local_148[0] + -6) == 0) goto LAB_0088cda5;
    std::wstring::wstring(awStack_348,this,1,*(long *)(local_148[0] + -6) - 1);
                    /* try { // try from 0088cb8f to 0088cb93 has its CatchHandler @ 0088cf25 */
    std::wstring::assign(this);
                    /* try { // try from 0088cb97 to 0088cb9b has its CatchHandler @ 0088cdca */
    std::wstring::~wstring(awStack_348);
    lVar5 = *(long *)(local_148[0] + -6);
  } while( true );
code_r0x0088cad7:
  std::wstring::wstring(local_308,this,1,*(long *)(local_f8[0] + -6) - 1);
                    /* try { // try from 0088caf1 to 0088caf5 has its CatchHandler @ 0088cf75 */
  std::wstring::assign(this);
                    /* try { // try from 0088caf9 to 0088cafd has its CatchHandler @ 0088cdff */
  std::wstring::~wstring(local_308);
  lVar5 = *(long *)(local_f8[0] + -6);
  goto LAB_0088c3f0;
LAB_0088cd9b:
                    /* try { // try from 0088cda0 to 0088cda4 has its CatchHandler @ 0088cf65 */
  std::__throw_out_of_range("basic_string::substr");
LAB_0088cda5:
                    /* try { // try from 0088cdaa to 0088cdae has its CatchHandler @ 0088cdca */
  uVar3 = std::__throw_out_of_range("basic_string::substr");
                    /* catch() { ... } // from try @ 0088c797 with catch @ 0088cdaf */
  std::wstring::~wstring(this);
  std::wstring::~wstring(in_RDI);
                    /* WARNING: Subroutine does not return */
  _Unwind_Resume(uVar3);
}



/* address=0088d040
   symbol=CEquipment::getEquipmentType */

/* WARNING: Removing unreachable block (ram,0x0088ed12) */
/* WARNING: Removing unreachable block (ram,0x0088ee95) */
/* WARNING: Removing unreachable block (ram,0x0088f27b) */
/* WARNING: Removing unreachable block (ram,0x0088f1c4) */
/* WARNING: Removing unreachable block (ram,0x0088f407) */
/* WARNING: Removing unreachable block (ram,0x0088f245) */
/* WARNING: Removing unreachable block (ram,0x0088f26d) */
/* WARNING: Removing unreachable block (ram,0x0088f2b5) */
/* WARNING: Removing unreachable block (ram,0x0088f255) */
/* WARNING: Removing unreachable block (ram,0x0088f3d2) */
/* WARNING: Removing unreachable block (ram,0x0088edfa) */
/* WARNING: Removing unreachable block (ram,0x0088f1d2) */
/* WARNING: Removing unreachable block (ram,0x0088f3ea) */
/* WARNING: Removing unreachable block (ram,0x0088f3a5) */
/* WARNING: Removing unreachable block (ram,0x0088f3bf) */
/* WARNING: Removing unreachable block (ram,0x0088f319) */
/* CEquipment::getEquipmentType(bool) */

wstring_conflict * CEquipment::getEquipmentType(bool param_1)

{
  int *piVar1;
  long lVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  char in_DL;
  wstring_conflict *pwVar6;
  CBaseUnit *in_RSI;
  undefined7 in_register_00000039;
  wstring_conflict *pwVar7;
  wstring_conflict awStack_518 [16];
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
  long local_318 [2];
  long local_308 [2];
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
  long local_148 [2];
  wstring_conflict local_138 [16];
  long local_128 [2];
  long local_118 [2];
  wstring_conflict local_108 [16];
  wstring_conflict local_f8 [16];
  long local_e8 [2];
  long local_d8 [2];
  long local_c8 [2];
  long local_b8 [2];
  long local_a8 [2];
  long local_98 [2];
  long local_88 [2];
  long local_78 [2];
  long local_68 [2];
  long local_58 [2];
  long local_48 [4];

  pwVar7 = (wstring_conflict *)CONCAT71(in_register_00000039,param_1);
  if ((getEquipmentType(bool)::g_Unidentified == '\0') &&
     (iVar4 = __cxa_guard_acquire(&getEquipmentType(bool)::g_Unidentified), iVar4 != 0)) {
    getEquipmentType(bool)::g_Unidentified = &DAT_01424558;
    __cxa_guard_release(&getEquipmentType(bool)::g_Unidentified);
    __cxa_atexit(std::wstring::~wstring,&getEquipmentType(bool)::g_Unidentified,&__dso_handle);
    lVar2 = *(long *)(getEquipmentType(bool)::g_Unidentified + -6);
  }
  else {
    lVar2 = *(long *)(getEquipmentType(bool)::g_Unidentified + -6);
  }
  if (lVar2 == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_48);
                    /* try { // try from 0088d33d to 0088d341 has its CatchHandler @ 0088f305 */
    std::wstring::assign((wstring_conflict *)&getEquipmentType(bool)::g_Unidentified);
    if ((allocator *)(local_48[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_48[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
      }
    }
  }
  if ((getEquipmentType(bool)::g_Unique == '\0') &&
     (iVar4 = __cxa_guard_acquire(&getEquipmentType(bool)::g_Unique), iVar4 != 0)) {
    getEquipmentType(bool)::g_Unique = &DAT_01424558;
    __cxa_guard_release(&getEquipmentType(bool)::g_Unique);
    __cxa_atexit(std::wstring::~wstring,&getEquipmentType(bool)::g_Unique,&__dso_handle);
  }
  if (*(long *)(getEquipmentType(bool)::g_Unique + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_58);
                    /* try { // try from 0088d47d to 0088d481 has its CatchHandler @ 0088f2ed */
    std::wstring::assign((wstring_conflict *)&getEquipmentType(bool)::g_Unique);
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
  if ((getEquipmentType(bool)::g_Rare == '\0') &&
     (iVar4 = __cxa_guard_acquire(&getEquipmentType(bool)::g_Rare), iVar4 != 0)) {
    getEquipmentType(bool)::g_Rare = &DAT_01424558;
    __cxa_guard_release(&getEquipmentType(bool)::g_Rare);
    __cxa_atexit(std::wstring::~wstring,&getEquipmentType(bool)::g_Rare,&__dso_handle);
    lVar2 = *(long *)(getEquipmentType(bool)::g_Rare + -6);
  }
  else {
    lVar2 = *(long *)(getEquipmentType(bool)::g_Rare + -6);
  }
  if (lVar2 == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_68);
                    /* try { // try from 0088d405 to 0088d409 has its CatchHandler @ 0088f339 */
    std::wstring::assign((wstring_conflict *)&getEquipmentType(bool)::g_Rare);
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
  if ((getEquipmentType(bool)::g_Enchanted == '\0') &&
     (iVar4 = __cxa_guard_acquire(&getEquipmentType(bool)::g_Enchanted), iVar4 != 0)) {
    getEquipmentType(bool)::g_Enchanted = &DAT_01424558;
    __cxa_guard_release(&getEquipmentType(bool)::g_Enchanted);
    __cxa_atexit(std::wstring::~wstring,&getEquipmentType(bool)::g_Enchanted,&__dso_handle);
  }
  if (*(long *)(getEquipmentType(bool)::g_Enchanted + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_78);
                    /* try { // try from 0088d725 to 0088d729 has its CatchHandler @ 0088f2d5 */
    std::wstring::assign((wstring_conflict *)&getEquipmentType(bool)::g_Enchanted);
    if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_78[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
      }
    }
  }
  if ((getEquipmentType(bool)::g_QuestItem == '\0') &&
     (iVar4 = __cxa_guard_acquire(&getEquipmentType(bool)::g_QuestItem), iVar4 != 0)) {
    getEquipmentType(bool)::g_QuestItem = &DAT_01424558;
    __cxa_guard_release(&getEquipmentType(bool)::g_QuestItem);
    __cxa_atexit(std::wstring::~wstring,&getEquipmentType(bool)::g_QuestItem,&__dso_handle);
  }
  if (*(long *)(getEquipmentType(bool)::g_QuestItem + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_88);
                    /* try { // try from 0088d665 to 0088d669 has its CatchHandler @ 0088f312 */
    std::wstring::assign((wstring_conflict *)&getEquipmentType(bool)::g_QuestItem);
    if ((allocator *)(local_88[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
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
  *(undefined4 **)pwVar7 = &DAT_01424558;
                    /* try { // try from 0088d0fd to 0088d189 has its CatchHandler @ 0088f331 */
  cVar3 = CBaseUnit::getIsQuestUnit(in_RSI);
  if (cVar3 != '\0') {
    std::wstring::assign(pwVar7);
  }
  cVar3 = CBaseUnit::ISA();
  if (cVar3 == '\0') {
                    /* try { // try from 0088d518 to 0088d587 has its CatchHandler @ 0088f331 */
    cVar3 = CBaseUnit::ISA();
    if (cVar3 != '\0') {
      if (in_RSI[0x348] == (CBaseUnit)0x0) {
        pwVar6 = local_278;
                    /* try { // try from 0088da73 to 0088da77 has its CatchHandler @ 0088f331 */
        std::operator+(pwVar6,pwVar7);
                    /* try { // try from 0088da8b to 0088da8f has its CatchHandler @ 0088f3ba */
        std::operator+(local_288,(wchar_t *)pwVar6);
                    /* try { // try from 0088da96 to 0088da9a has its CatchHandler @ 0088f3b5 */
        std::wstring::assign(pwVar7);
                    /* try { // try from 0088da9e to 0088daa2 has its CatchHandler @ 0088f3ba */
        std::wstring::~wstring(local_288);
LAB_0088daa3:
                    /* try { // try from 0088daa6 to 0088dafc has its CatchHandler @ 0088f331 */
        std::wstring::~wstring(pwVar6);
      }
      else if (in_DL != '\0') {
                    /* try { // try from 0088dfb8 to 0088dfdc has its CatchHandler @ 0088f331 */
        cVar3 = CBaseUnit::ISA();
        if (cVar3 == '\0') {
                    /* try { // try from 0088e0b8 to 0088e0ed has its CatchHandler @ 0088f331 */
          cVar3 = CBaseUnit::ISA();
          if (cVar3 == '\0') {
            cVar3 = (**(code **)(*(long *)in_RSI + 0x2b0))();
            if (cVar3 == '\0') goto LAB_0088d53b;
            pwVar6 = local_2d8;
            std::operator+(pwVar6,pwVar7);
                    /* try { // try from 0088e101 to 0088e105 has its CatchHandler @ 0088ee21 */
            std::operator+(local_2e8,(wchar_t *)pwVar6);
                    /* try { // try from 0088e10c to 0088e110 has its CatchHandler @ 0088ee0c */
            std::wstring::assign(pwVar7);
                    /* try { // try from 0088e114 to 0088e118 has its CatchHandler @ 0088ee21 */
            std::wstring::~wstring(local_2e8);
          }
          else {
            pwVar6 = local_2b8;
                    /* try { // try from 0088e133 to 0088e137 has its CatchHandler @ 0088f331 */
            std::operator+(pwVar6,pwVar7);
                    /* try { // try from 0088e14b to 0088e14f has its CatchHandler @ 0088f1e2 */
            std::operator+(local_2c8,(wchar_t *)pwVar6);
                    /* try { // try from 0088e156 to 0088e15a has its CatchHandler @ 0088f1dd */
            std::wstring::assign(pwVar7);
                    /* try { // try from 0088e15e to 0088e162 has its CatchHandler @ 0088f1e2 */
            std::wstring::~wstring(local_2c8);
          }
        }
        else {
          pwVar6 = local_298;
          std::operator+(pwVar6,pwVar7);
                    /* try { // try from 0088dff0 to 0088dff4 has its CatchHandler @ 0088f2ca */
          std::operator+(local_2a8,(wchar_t *)pwVar6);
                    /* try { // try from 0088dffb to 0088dfff has its CatchHandler @ 0088f2c5 */
          std::wstring::assign(pwVar7);
                    /* try { // try from 0088e003 to 0088e007 has its CatchHandler @ 0088f2ca */
          std::wstring::~wstring(local_2a8);
        }
        goto LAB_0088daa3;
      }
LAB_0088d53b:
      cVar3 = CBaseUnit::ISA();
      if (cVar3 != '\0') {
        if ((getEquipmentType(bool)::g_Helmet == '\0') &&
           (iVar4 = __cxa_guard_acquire(&getEquipmentType(bool)::g_Helmet), iVar4 != 0)) {
          getEquipmentType(bool)::g_Helmet = &DAT_01424558;
          __cxa_guard_release(&getEquipmentType(bool)::g_Helmet);
          __cxa_atexit(std::wstring::~wstring,&getEquipmentType(bool)::g_Helmet,&__dso_handle);
        }
        if (*(long *)(getEquipmentType(bool)::g_Helmet + -6) == 0) {
          CStringTranslate::getSinglton();
          CStringTranslate::getTranslateString((wchar_t *)local_2f8);
                    /* try { // try from 0088d590 to 0088d594 has its CatchHandler @ 0088f3fd */
          std::wstring::assign((wstring_conflict *)&getEquipmentType(bool)::g_Helmet);
                    /* try { // try from 0088d598 to 0088d5b9 has its CatchHandler @ 0088f331 */
          std::wstring::~wstring(local_2f8);
        }
        CStringTranslate::getSinglton();
        CStringTranslate::getTranslateString((wchar_t *)local_308);
                    /* try { // try from 0088d5cb to 0088d5cf has its CatchHandler @ 0088f3f8 */
        std::operator+((wstring_conflict *)local_318,pwVar7);
                    /* try { // try from 0088d5d6 to 0088d5da has its CatchHandler @ 0088f402 */
        std::wstring::assign(pwVar7);
        if ((allocator *)(local_318[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_318[0] + -8);
          iVar4 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar4 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_318[0] + -0x18));
          }
        }
        if ((allocator *)(local_308[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_308[0] + -8);
          iVar4 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar4 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_308[0] + -0x18));
          }
        }
        goto LAB_0088d1ae;
      }
                    /* try { // try from 0088dd00 to 0088dd44 has its CatchHandler @ 0088f331 */
      cVar3 = CBaseUnit::ISA();
      if (cVar3 == '\0') {
                    /* try { // try from 0088de88 to 0088decc has its CatchHandler @ 0088f331 */
        cVar3 = CBaseUnit::ISA();
        if (cVar3 == '\0') {
          cVar3 = CBaseUnit::ISA();
          if (cVar3 == '\0') {
                    /* try { // try from 0088e66f to 0088e6b3 has its CatchHandler @ 0088f331 */
            cVar3 = CBaseUnit::ISA();
            if (cVar3 == '\0') {
                    /* try { // try from 0088e81e to 0088e862 has its CatchHandler @ 0088f331 */
              cVar3 = CBaseUnit::ISA();
              if (cVar3 == '\0') {
                    /* try { // try from 0088eaa2 to 0088eae6 has its CatchHandler @ 0088f331 */
                cVar3 = CBaseUnit::ISA();
                if (cVar3 != '\0') {
                  if ((getEquipmentType(bool)::g_Shield == '\0') &&
                     (iVar4 = __cxa_guard_acquire(&getEquipmentType(bool)::g_Shield), iVar4 != 0)) {
                    getEquipmentType(bool)::g_Shield = &DAT_01424558;
                    __cxa_guard_release(&getEquipmentType(bool)::g_Shield);
                    __cxa_atexit(std::wstring::~wstring,&getEquipmentType(bool)::g_Shield,
                                 &__dso_handle);
                  }
                  if (*(long *)(getEquipmentType(bool)::g_Shield + -6) == 0) {
                    CStringTranslate::getSinglton();
                    CStringTranslate::getTranslateString((wchar_t *)local_408);
                    /* try { // try from 0088eaef to 0088eaf3 has its CatchHandler @ 0088ef50 */
                    std::wstring::assign((wstring_conflict *)&getEquipmentType(bool)::g_Shield);
                    /* try { // try from 0088eaf7 to 0088eb18 has its CatchHandler @ 0088f331 */
                    std::wstring::~wstring(local_408);
                  }
                  CStringTranslate::getSinglton();
                  pwVar6 = local_418;
                  CStringTranslate::getTranslateString((wchar_t *)pwVar6);
                    /* try { // try from 0088eb2a to 0088eb2e has its CatchHandler @ 0088eeb5 */
                  std::operator+(local_428,pwVar7);
                    /* try { // try from 0088eb35 to 0088eb39 has its CatchHandler @ 0088eeaf */
                  std::wstring::assign(pwVar7);
                    /* try { // try from 0088eb3d to 0088eb41 has its CatchHandler @ 0088eeb5 */
                  std::wstring::~wstring(local_428);
                  goto LAB_0088dda0;
                }
                if ((getEquipmentType(bool)::g_Armor == '\0') &&
                   (iVar4 = __cxa_guard_acquire(&getEquipmentType(bool)::g_Armor), iVar4 != 0)) {
                  getEquipmentType(bool)::g_Armor = &DAT_01424558;
                  __cxa_guard_release(&getEquipmentType(bool)::g_Armor);
                  __cxa_atexit(std::wstring::~wstring,&getEquipmentType(bool)::g_Armor,&__dso_handle
                              );
                }
                if (*(long *)(getEquipmentType(bool)::g_Armor + -6) == 0) {
                    /* try { // try from 0088eb62 to 0088eb7e has its CatchHandler @ 0088f331 */
                  CStringTranslate::getSinglton();
                  CStringTranslate::getTranslateString((wchar_t *)local_438);
                    /* try { // try from 0088eb87 to 0088eb8b has its CatchHandler @ 0088ef0b */
                  std::wstring::assign((wstring_conflict *)&getEquipmentType(bool)::g_Armor);
                    /* try { // try from 0088eb8f to 0088ebab has its CatchHandler @ 0088f331 */
                  std::wstring::~wstring(local_438);
                }
                pwVar6 = local_448;
                std::operator+(pwVar6,pwVar7);
                    /* try { // try from 0088ebb2 to 0088ebb6 has its CatchHandler @ 0088f365 */
                std::wstring::assign(pwVar7);
              }
              else {
                if ((getEquipmentType(bool)::g_ShoulderArmor == '\0') &&
                   (iVar4 = __cxa_guard_acquire(&getEquipmentType(bool)::g_ShoulderArmor),
                   iVar4 != 0)) {
                  getEquipmentType(bool)::g_ShoulderArmor = &DAT_01424558;
                  __cxa_guard_release(&getEquipmentType(bool)::g_ShoulderArmor);
                  __cxa_atexit(std::wstring::~wstring,&getEquipmentType(bool)::g_ShoulderArmor,
                               &__dso_handle);
                }
                if (*(long *)(getEquipmentType(bool)::g_ShoulderArmor + -6) == 0) {
                  CStringTranslate::getSinglton();
                  CStringTranslate::getTranslateString((wchar_t *)local_3e8);
                    /* try { // try from 0088e86b to 0088e86f has its CatchHandler @ 0088eea5 */
                  std::wstring::assign((wstring_conflict *)&getEquipmentType(bool)::g_ShoulderArmor)
                  ;
                    /* try { // try from 0088e873 to 0088e88f has its CatchHandler @ 0088f331 */
                  std::wstring::~wstring(local_3e8);
                }
                pwVar6 = local_3f8;
                std::operator+(pwVar6,pwVar7);
                    /* try { // try from 0088e896 to 0088e89a has its CatchHandler @ 0088ee77 */
                std::wstring::assign(pwVar7);
              }
              goto LAB_0088db35;
            }
            if ((getEquipmentType(bool)::g_ChestArmor == '\0') &&
               (iVar4 = __cxa_guard_acquire(&getEquipmentType(bool)::g_ChestArmor), iVar4 != 0)) {
              getEquipmentType(bool)::g_ChestArmor = &DAT_01424558;
              __cxa_guard_release(&getEquipmentType(bool)::g_ChestArmor);
              __cxa_atexit(std::wstring::~wstring,&getEquipmentType(bool)::g_ChestArmor,
                           &__dso_handle);
            }
            if (*(long *)(getEquipmentType(bool)::g_ChestArmor + -6) == 0) {
              CStringTranslate::getSinglton();
              CStringTranslate::getTranslateString((wchar_t *)local_3b8);
                    /* try { // try from 0088e6bc to 0088e6c0 has its CatchHandler @ 0088ee85 */
              std::wstring::assign((wstring_conflict *)&getEquipmentType(bool)::g_ChestArmor);
                    /* try { // try from 0088e6c4 to 0088e6e5 has its CatchHandler @ 0088f331 */
              std::wstring::~wstring(local_3b8);
            }
            CStringTranslate::getSinglton();
            pwVar6 = local_3c8;
            CStringTranslate::getTranslateString((wchar_t *)pwVar6);
                    /* try { // try from 0088e6f7 to 0088e6fb has its CatchHandler @ 0088ee3b */
            std::operator+(local_3d8,pwVar7);
                    /* try { // try from 0088e702 to 0088e706 has its CatchHandler @ 0088ee26 */
            std::wstring::assign(pwVar7);
                    /* try { // try from 0088e70a to 0088e70e has its CatchHandler @ 0088ee3b */
            std::wstring::~wstring(local_3d8);
          }
          else {
            if ((getEquipmentType(bool)::g_Belt == '\0') &&
               (iVar4 = __cxa_guard_acquire(&getEquipmentType(bool)::g_Belt), iVar4 != 0)) {
              getEquipmentType(bool)::g_Belt = &DAT_01424558;
              __cxa_guard_release(&getEquipmentType(bool)::g_Belt);
              __cxa_atexit(std::wstring::~wstring,&getEquipmentType(bool)::g_Belt,&__dso_handle);
            }
            if (*(long *)(getEquipmentType(bool)::g_Belt + -6) == 0) {
              CStringTranslate::getSinglton();
              CStringTranslate::getTranslateString((wchar_t *)local_388);
                    /* try { // try from 0088e306 to 0088e30a has its CatchHandler @ 0088ee0a */
              std::wstring::assign((wstring_conflict *)&getEquipmentType(bool)::g_Belt);
                    /* try { // try from 0088e30e to 0088e32f has its CatchHandler @ 0088f331 */
              std::wstring::~wstring(local_388);
            }
            CStringTranslate::getSinglton();
            pwVar6 = local_398;
            CStringTranslate::getTranslateString((wchar_t *)pwVar6);
                    /* try { // try from 0088e341 to 0088e345 has its CatchHandler @ 0088f215 */
            std::operator+(local_3a8,pwVar7);
                    /* try { // try from 0088e34c to 0088e350 has its CatchHandler @ 0088f205 */
            std::wstring::assign(pwVar7);
                    /* try { // try from 0088e354 to 0088e358 has its CatchHandler @ 0088f215 */
            std::wstring::~wstring(local_3a8);
          }
        }
        else {
          if ((getEquipmentType(bool)::g_Boots == '\0') &&
             (iVar4 = __cxa_guard_acquire(&getEquipmentType(bool)::g_Boots), iVar4 != 0)) {
            getEquipmentType(bool)::g_Boots = &DAT_01424558;
            __cxa_guard_release(&getEquipmentType(bool)::g_Boots);
            __cxa_atexit(std::wstring::~wstring,&getEquipmentType(bool)::g_Boots,&__dso_handle);
          }
          if (*(long *)(getEquipmentType(bool)::g_Boots + -6) == 0) {
            CStringTranslate::getSinglton();
            CStringTranslate::getTranslateString((wchar_t *)local_358);
                    /* try { // try from 0088ded5 to 0088ded9 has its CatchHandler @ 0088ee08 */
            std::wstring::assign((wstring_conflict *)&getEquipmentType(bool)::g_Boots);
                    /* try { // try from 0088dedd to 0088defe has its CatchHandler @ 0088f331 */
            std::wstring::~wstring(local_358);
          }
          CStringTranslate::getSinglton();
          pwVar6 = local_368;
          CStringTranslate::getTranslateString((wchar_t *)pwVar6);
                    /* try { // try from 0088df10 to 0088df14 has its CatchHandler @ 0088f268 */
          std::operator+(local_378,pwVar7);
                    /* try { // try from 0088df1b to 0088df1f has its CatchHandler @ 0088f263 */
          std::wstring::assign(pwVar7);
                    /* try { // try from 0088df23 to 0088df27 has its CatchHandler @ 0088f268 */
          std::wstring::~wstring(local_378);
        }
      }
      else {
        if ((getEquipmentType(bool)::g_Gloves == '\0') &&
           (iVar4 = __cxa_guard_acquire(&getEquipmentType(bool)::g_Gloves), iVar4 != 0)) {
          getEquipmentType(bool)::g_Gloves = &DAT_01424558;
          __cxa_guard_release(&getEquipmentType(bool)::g_Gloves);
          __cxa_atexit(std::wstring::~wstring,&getEquipmentType(bool)::g_Gloves,&__dso_handle);
        }
        if (*(long *)(getEquipmentType(bool)::g_Gloves + -6) == 0) {
          CStringTranslate::getSinglton();
          CStringTranslate::getTranslateString((wchar_t *)local_328);
                    /* try { // try from 0088dd4d to 0088dd51 has its CatchHandler @ 0088f115 */
          std::wstring::assign((wstring_conflict *)&getEquipmentType(bool)::g_Gloves);
                    /* try { // try from 0088dd55 to 0088dd76 has its CatchHandler @ 0088f331 */
          std::wstring::~wstring(local_328);
        }
        CStringTranslate::getSinglton();
        pwVar6 = local_338;
        CStringTranslate::getTranslateString((wchar_t *)pwVar6);
                    /* try { // try from 0088dd88 to 0088dd8c has its CatchHandler @ 0088f235 */
        std::operator+(local_348,pwVar7);
                    /* try { // try from 0088dd93 to 0088dd97 has its CatchHandler @ 0088f225 */
        std::wstring::assign(pwVar7);
                    /* try { // try from 0088dd9b to 0088dd9f has its CatchHandler @ 0088f235 */
        std::wstring::~wstring(local_348);
      }
LAB_0088dda0:
                    /* try { // try from 0088dda3 to 0088ddfc has its CatchHandler @ 0088f331 */
      std::wstring::~wstring(pwVar6);
      goto LAB_0088d1ae;
    }
    cVar3 = CBaseUnit::ISA();
    if (cVar3 != '\0') {
      if ((getEquipmentType(bool)::g_Socketable == '\0') &&
         (iVar4 = __cxa_guard_acquire(&getEquipmentType(bool)::g_Socketable), iVar4 != 0)) {
        getEquipmentType(bool)::g_Socketable = &DAT_01424558;
        __cxa_guard_release(&getEquipmentType(bool)::g_Socketable);
        __cxa_atexit(std::wstring::~wstring,&getEquipmentType(bool)::g_Socketable,&__dso_handle);
      }
      if (*(long *)(getEquipmentType(bool)::g_Socketable + -6) == 0) {
        CStringTranslate::getSinglton();
        CStringTranslate::getTranslateString((wchar_t *)local_458);
                    /* try { // try from 0088db9d to 0088dba1 has its CatchHandler @ 0088f1f5 */
        std::wstring::assign((wstring_conflict *)&getEquipmentType(bool)::g_Socketable);
                    /* try { // try from 0088dba5 to 0088dbfd has its CatchHandler @ 0088f331 */
        std::wstring::~wstring(local_458);
      }
      std::wstring::assign(pwVar7);
      goto LAB_0088d1ae;
    }
                    /* try { // try from 0088e018 to 0088e06f has its CatchHandler @ 0088f331 */
    cVar3 = CBaseUnit::ISA();
    if (cVar3 == '\0') {
                    /* try { // try from 0088e1f8 to 0088e239 has its CatchHandler @ 0088f331 */
      cVar3 = CBaseUnit::ISA();
      if (cVar3 == '\0') {
                    /* try { // try from 0088e50d to 0088e549 has its CatchHandler @ 0088f331 */
        cVar3 = CBaseUnit::ISA();
        if (cVar3 != '\0') {
          if ((getEquipmentType(bool)::g_Scroll == '\0') &&
             (iVar4 = __cxa_guard_acquire(&getEquipmentType(bool)::g_Scroll), iVar4 != 0)) {
            getEquipmentType(bool)::g_Scroll = &DAT_01424558;
            __cxa_guard_release(&getEquipmentType(bool)::g_Scroll);
            __cxa_atexit(std::wstring::~wstring,&getEquipmentType(bool)::g_Scroll,&__dso_handle);
          }
          if (*(long *)(getEquipmentType(bool)::g_Scroll + -6) == 0) {
            CStringTranslate::getSinglton();
            CStringTranslate::getTranslateString((wchar_t *)awStack_518);
                    /* try { // try from 0088e552 to 0088e556 has its CatchHandler @ 0088ee56 */
            std::wstring::assign((wstring_conflict *)&getEquipmentType(bool)::g_Scroll);
                    /* try { // try from 0088e55a to 0088e5af has its CatchHandler @ 0088f331 */
            std::wstring::~wstring(awStack_518);
          }
          std::wstring::assign(pwVar7);
        }
      }
      else {
        if ((getEquipmentType(bool)::g_Potion == '\0') &&
           (iVar4 = __cxa_guard_acquire(&getEquipmentType(bool)::g_Potion), iVar4 != 0)) {
          getEquipmentType(bool)::g_Potion = &DAT_01424558;
          __cxa_guard_release(&getEquipmentType(bool)::g_Potion);
          __cxa_atexit(std::wstring::~wstring,&getEquipmentType(bool)::g_Potion,&__dso_handle);
        }
        if (*(long *)(getEquipmentType(bool)::g_Potion + -6) == 0) {
          CStringTranslate::getSinglton();
          CStringTranslate::getTranslateString((wchar_t *)local_508);
                    /* try { // try from 0088e242 to 0088e246 has its CatchHandler @ 0088ee54 */
          std::wstring::assign((wstring_conflict *)&getEquipmentType(bool)::g_Potion);
                    /* try { // try from 0088e24a to 0088e278 has its CatchHandler @ 0088f331 */
          std::wstring::~wstring(local_508);
        }
        std::wstring::assign(pwVar7);
      }
      goto LAB_0088d1ae;
    }
    if (in_RSI[0x348] == (CBaseUnit)0x0) {
      pwVar6 = local_468;
      std::operator+(pwVar6,pwVar7);
                    /* try { // try from 0088e28c to 0088e290 has its CatchHandler @ 0088f145 */
      std::operator+(local_478,(wchar_t *)pwVar6);
                    /* try { // try from 0088e297 to 0088e29b has its CatchHandler @ 0088f135 */
      std::wstring::assign(pwVar7);
                    /* try { // try from 0088e29f to 0088e2a3 has its CatchHandler @ 0088f145 */
      std::wstring::~wstring(local_478);
LAB_0088e2a4:
                    /* try { // try from 0088e2a7 to 0088e2fd has its CatchHandler @ 0088f331 */
      std::wstring::~wstring(pwVar6);
    }
    else if (in_DL != '\0') {
                    /* try { // try from 0088e430 to 0088e454 has its CatchHandler @ 0088f331 */
      cVar3 = CBaseUnit::ISA();
      if (cVar3 == '\0') {
        cVar3 = CBaseUnit::ISA();
        if (cVar3 == '\0') {
          cVar3 = (**(code **)(*(long *)in_RSI + 0x2b0))();
          if (cVar3 == '\0') goto LAB_0088e03b;
          pwVar6 = local_4c8;
          std::operator+(pwVar6,pwVar7);
                    /* try { // try from 0088e5c0 to 0088e5c4 has its CatchHandler @ 0088ee44 */
          std::operator+(local_4d8,(wchar_t *)pwVar6);
                    /* try { // try from 0088e5cb to 0088e5cf has its CatchHandler @ 0088ee52 */
          std::wstring::assign(pwVar7);
                    /* try { // try from 0088e5d3 to 0088e5d7 has its CatchHandler @ 0088ee44 */
          std::wstring::~wstring(local_4d8);
        }
        else {
          pwVar6 = local_4a8;
                    /* try { // try from 0088e764 to 0088e768 has its CatchHandler @ 0088f331 */
          std::operator+(pwVar6,pwVar7);
                    /* try { // try from 0088e779 to 0088e77d has its CatchHandler @ 0088ee69 */
          std::operator+(local_4b8,(wchar_t *)pwVar6);
                    /* try { // try from 0088e784 to 0088e788 has its CatchHandler @ 0088ee67 */
          std::wstring::assign(pwVar7);
                    /* try { // try from 0088e78c to 0088e790 has its CatchHandler @ 0088ee69 */
          std::wstring::~wstring(local_4b8);
        }
      }
      else {
        pwVar6 = local_488;
        std::operator+(pwVar6,pwVar7);
                    /* try { // try from 0088e468 to 0088e46c has its CatchHandler @ 0088f342 */
        std::operator+(local_498,(wchar_t *)pwVar6);
                    /* try { // try from 0088e473 to 0088e477 has its CatchHandler @ 0088f3e0 */
        std::wstring::assign(pwVar7);
                    /* try { // try from 0088e47b to 0088e47f has its CatchHandler @ 0088f342 */
        std::wstring::~wstring(local_498);
      }
      goto LAB_0088e2a4;
    }
LAB_0088e03b:
    if ((getEquipmentType(bool)::g_Trinket == '\0') &&
       (iVar4 = __cxa_guard_acquire(&getEquipmentType(bool)::g_Trinket), iVar4 != 0)) {
      getEquipmentType(bool)::g_Trinket = &DAT_01424558;
      __cxa_guard_release(&getEquipmentType(bool)::g_Trinket);
      __cxa_atexit(std::wstring::~wstring,&getEquipmentType(bool)::g_Trinket,&__dso_handle);
    }
    if (*(long *)(getEquipmentType(bool)::g_Trinket + -6) == 0) {
      CStringTranslate::getSinglton();
      CStringTranslate::getTranslateString((wchar_t *)local_4e8);
                    /* try { // try from 0088e078 to 0088e07c has its CatchHandler @ 0088f165 */
      std::wstring::assign((wstring_conflict *)&getEquipmentType(bool)::g_Trinket);
                    /* try { // try from 0088e080 to 0088e099 has its CatchHandler @ 0088f331 */
      std::wstring::~wstring(local_4e8);
    }
    pwVar6 = local_4f8;
    std::operator+(pwVar6,pwVar7);
                    /* try { // try from 0088e0a0 to 0088e0a4 has its CatchHandler @ 0088f2cf */
    std::wstring::assign(pwVar7);
  }
  else {
    if (in_RSI[0x348] == (CBaseUnit)0x0) {
                    /* try { // try from 0088d8a3 to 0088d8a7 has its CatchHandler @ 0088f331 */
      std::operator+((wstring_conflict *)local_98,pwVar7);
                    /* try { // try from 0088d8b6 to 0088d8ba has its CatchHandler @ 0088f355 */
      std::wstring::wstring((wstring_conflict *)local_a8,(wstring_conflict *)local_98);
      wcslen(L" ");
                    /* try { // try from 0088d8d0 to 0088d8d4 has its CatchHandler @ 0088f327 */
      std::wstring::append((wchar_t *)local_a8,0xfd0b98);
                    /* try { // try from 0088d8db to 0088d8df has its CatchHandler @ 0088f32c */
      std::wstring::assign(pwVar7);
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
      if ((allocator *)(local_98[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_98[0] + -8);
        iVar4 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar4 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
        }
      }
    }
    else if (in_DL != '\0') {
                    /* try { // try from 0088d998 to 0088d9bc has its CatchHandler @ 0088f331 */
      cVar3 = CBaseUnit::ISA();
      if (cVar3 == '\0') {
        cVar3 = CBaseUnit::ISA();
        if (cVar3 == '\0') {
          cVar3 = (**(code **)(*(long *)in_RSI + 0x2b0))();
          if (cVar3 != '\0') {
            std::operator+(local_f8,pwVar7);
                    /* try { // try from 0088dc11 to 0088dc15 has its CatchHandler @ 0088f185 */
            std::operator+(local_108,(wchar_t *)local_f8);
                    /* try { // try from 0088dc1c to 0088dc20 has its CatchHandler @ 0088f175 */
            std::wstring::assign(pwVar7);
                    /* try { // try from 0088dc24 to 0088dc28 has its CatchHandler @ 0088f185 */
            std::wstring::~wstring(local_108);
                    /* try { // try from 0088dc2c to 0088dc57 has its CatchHandler @ 0088f331 */
            std::wstring::~wstring(local_f8);
          }
        }
        else {
          std::operator+((wstring_conflict *)local_d8,pwVar7);
                    /* try { // try from 0088dc66 to 0088dc6a has its CatchHandler @ 0088f295 */
          std::wstring::wstring((wstring_conflict *)local_e8,(wstring_conflict *)local_d8);
          wcslen(L" ");
                    /* try { // try from 0088dc80 to 0088dc84 has its CatchHandler @ 0088f28e */
          std::wstring::append((wchar_t *)local_e8,0xfd0b98);
                    /* try { // try from 0088dc8b to 0088dc8f has its CatchHandler @ 0088f289 */
          std::wstring::assign(pwVar7);
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
        }
      }
      else {
        std::operator+((wstring_conflict *)local_b8,pwVar7);
                    /* try { // try from 0088d9cb to 0088d9cf has its CatchHandler @ 0088f395 */
        std::wstring::wstring((wstring_conflict *)local_c8,(wstring_conflict *)local_b8);
        wcslen(L" ");
                    /* try { // try from 0088d9e5 to 0088d9e9 has its CatchHandler @ 0088f385 */
        std::wstring::append((wchar_t *)local_c8,0xfd0b98);
                    /* try { // try from 0088d9f0 to 0088d9f4 has its CatchHandler @ 0088f375 */
        std::wstring::assign(pwVar7);
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
      }
    }
    cVar3 = CBaseUnit::ISA();
    if (cVar3 != '\0') {
      if ((getEquipmentType(bool)::g_Sword == '\0') &&
         (iVar4 = __cxa_guard_acquire(&getEquipmentType(bool)::g_Sword), iVar4 != 0)) {
        getEquipmentType(bool)::g_Sword = &DAT_01424558;
        __cxa_guard_release(&getEquipmentType(bool)::g_Sword);
        __cxa_atexit(std::wstring::~wstring,&getEquipmentType(bool)::g_Sword,&__dso_handle);
      }
      if (*(long *)(getEquipmentType(bool)::g_Sword + -6) == 0) {
        CStringTranslate::getSinglton();
        CStringTranslate::getTranslateString((wchar_t *)local_118);
                    /* try { // try from 0088d245 to 0088d249 has its CatchHandler @ 0088f2f5 */
        std::wstring::assign((wstring_conflict *)&getEquipmentType(bool)::g_Sword);
        if ((allocator *)(local_118[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_118[0] + -8);
          iVar4 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar4 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_118[0] + -0x18));
          }
        }
      }
      std::operator+((wstring_conflict *)local_128,pwVar7);
                    /* try { // try from 0088d190 to 0088d194 has its CatchHandler @ 0088f2ef */
      std::wstring::assign(pwVar7);
      if ((allocator *)(local_128[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_128[0] + -8);
        iVar4 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar4 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_128[0] + -0x18));
        }
      }
      goto LAB_0088d1ae;
    }
                    /* try { // try from 0088d7c8 to 0088d80c has its CatchHandler @ 0088f331 */
    cVar3 = CBaseUnit::ISA();
    if (cVar3 != '\0') {
      if ((getEquipmentType(bool)::g_Bow == '\0') &&
         (iVar4 = __cxa_guard_acquire(&getEquipmentType(bool)::g_Bow), iVar4 != 0)) {
        getEquipmentType(bool)::g_Bow = &DAT_01424558;
        __cxa_guard_release(&getEquipmentType(bool)::g_Bow);
        __cxa_atexit(std::wstring::~wstring,&getEquipmentType(bool)::g_Bow,&__dso_handle);
      }
      if (*(long *)(getEquipmentType(bool)::g_Bow + -6) == 0) {
        CStringTranslate::getSinglton();
        CStringTranslate::getTranslateString((wchar_t *)local_138);
                    /* try { // try from 0088d815 to 0088d819 has its CatchHandler @ 0088f314 */
        std::wstring::assign((wstring_conflict *)&getEquipmentType(bool)::g_Bow);
                    /* try { // try from 0088d81d to 0088d839 has its CatchHandler @ 0088f331 */
        std::wstring::~wstring(local_138);
      }
      std::operator+((wstring_conflict *)local_148,pwVar7);
                    /* try { // try from 0088d840 to 0088d844 has its CatchHandler @ 0088eddf */
      std::wstring::assign(pwVar7);
      if ((allocator *)(local_148[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_148[0] + -8);
        iVar4 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar4 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_148[0] + -0x18));
        }
      }
      goto LAB_0088d1ae;
    }
    cVar3 = CBaseUnit::ISA();
    if (cVar3 == '\0') {
      cVar3 = CBaseUnit::ISA();
      if (cVar3 == '\0') {
                    /* try { // try from 0088e3a6 to 0088e3ea has its CatchHandler @ 0088f331 */
        cVar3 = CBaseUnit::ISA();
        if (cVar3 == '\0') {
                    /* try { // try from 0088e5e5 to 0088e629 has its CatchHandler @ 0088f331 */
          cVar3 = CBaseUnit::ISA();
          if (cVar3 == '\0') {
                    /* try { // try from 0088e8a8 to 0088e8ec has its CatchHandler @ 0088f331 */
            cVar3 = CBaseUnit::ISA();
            if (cVar3 == '\0') {
                    /* try { // try from 0088ebf4 to 0088ec38 has its CatchHandler @ 0088f331 */
              cVar3 = CBaseUnit::ISA();
              if (cVar3 == '\0') {
                    /* try { // try from 0088ed25 to 0088ed65 has its CatchHandler @ 0088f331 */
                cVar3 = CBaseUnit::ISA();
                if (cVar3 == '\0') {
                    /* try { // try from 0088ef7d to 0088efbd has its CatchHandler @ 0088f331 */
                  cVar3 = CBaseUnit::ISA();
                  if (cVar3 == '\0') {
                    if ((getEquipmentType(bool)::g_Weapon == '\0') &&
                       (iVar4 = __cxa_guard_acquire(&getEquipmentType(bool)::g_Weapon), iVar4 != 0))
                    {
                      getEquipmentType(bool)::g_Weapon = &DAT_01424558;
                      __cxa_guard_release(&getEquipmentType(bool)::g_Weapon);
                      __cxa_atexit(std::wstring::~wstring,&getEquipmentType(bool)::g_Weapon,
                                   &__dso_handle);
                    }
                    if (*(long *)(getEquipmentType(bool)::g_Weapon + -6) == 0) {
                    /* try { // try from 0088f060 to 0088f07c has its CatchHandler @ 0088f331 */
                      CStringTranslate::getSinglton();
                      CStringTranslate::getTranslateString((wchar_t *)local_258);
                    /* try { // try from 0088f085 to 0088f089 has its CatchHandler @ 0088f105 */
                      std::wstring::assign((wstring_conflict *)&getEquipmentType(bool)::g_Weapon);
                    /* try { // try from 0088f08d to 0088f0a9 has its CatchHandler @ 0088f331 */
                      std::wstring::~wstring(local_258);
                    }
                    pwVar6 = local_268;
                    std::operator+(pwVar6,pwVar7);
                    /* try { // try from 0088f0b0 to 0088f0b4 has its CatchHandler @ 0088f0f6 */
                    std::wstring::assign(pwVar7);
                  }
                  else {
                    if ((getEquipmentType(bool)::g_Wand == '\0') &&
                       (iVar4 = __cxa_guard_acquire(&getEquipmentType(bool)::g_Wand), iVar4 != 0)) {
                      getEquipmentType(bool)::g_Wand = &DAT_01424558;
                      __cxa_guard_release(&getEquipmentType(bool)::g_Wand);
                      __cxa_atexit(std::wstring::~wstring,&getEquipmentType(bool)::g_Wand,
                                   &__dso_handle);
                    }
                    if (*(long *)(getEquipmentType(bool)::g_Wand + -6) == 0) {
                      CStringTranslate::getSinglton();
                      CStringTranslate::getTranslateString((wchar_t *)local_238);
                    /* try { // try from 0088efc6 to 0088efca has its CatchHandler @ 0088f03c */
                      std::wstring::assign((wstring_conflict *)&getEquipmentType(bool)::g_Wand);
                    /* try { // try from 0088efce to 0088efea has its CatchHandler @ 0088f331 */
                      std::wstring::~wstring(local_238);
                    }
                    pwVar6 = local_248;
                    std::operator+(pwVar6,pwVar7);
                    /* try { // try from 0088eff1 to 0088eff5 has its CatchHandler @ 0088f0fb */
                    std::wstring::assign(pwVar7);
                  }
                }
                else {
                  if ((getEquipmentType(bool)::g_Crossbow == '\0') &&
                     (iVar4 = __cxa_guard_acquire(&getEquipmentType(bool)::g_Crossbow), iVar4 != 0))
                  {
                    getEquipmentType(bool)::g_Crossbow = &DAT_01424558;
                    __cxa_guard_release(&getEquipmentType(bool)::g_Crossbow);
                    __cxa_atexit(std::wstring::~wstring,&getEquipmentType(bool)::g_Crossbow,
                                 &__dso_handle);
                  }
                  if (*(long *)(getEquipmentType(bool)::g_Crossbow + -6) == 0) {
                    CStringTranslate::getSinglton();
                    CStringTranslate::getTranslateString((wchar_t *)local_218);
                    /* try { // try from 0088ed6e to 0088ed72 has its CatchHandler @ 0088ef65 */
                    std::wstring::assign((wstring_conflict *)&getEquipmentType(bool)::g_Crossbow);
                    /* try { // try from 0088ed76 to 0088ed92 has its CatchHandler @ 0088f331 */
                    std::wstring::~wstring(local_218);
                  }
                  pwVar6 = local_228;
                  std::operator+(pwVar6,pwVar7);
                    /* try { // try from 0088ed99 to 0088ed9d has its CatchHandler @ 0088f037 */
                  std::wstring::assign(pwVar7);
                }
              }
              else {
                if ((getEquipmentType(bool)::g_Rifle == '\0') &&
                   (iVar4 = __cxa_guard_acquire(&getEquipmentType(bool)::g_Rifle), iVar4 != 0)) {
                  getEquipmentType(bool)::g_Rifle = &DAT_01424558;
                  __cxa_guard_release(&getEquipmentType(bool)::g_Rifle);
                  __cxa_atexit(std::wstring::~wstring,&getEquipmentType(bool)::g_Rifle,&__dso_handle
                              );
                }
                if (*(long *)(getEquipmentType(bool)::g_Rifle + -6) == 0) {
                  CStringTranslate::getSinglton();
                  CStringTranslate::getTranslateString((wchar_t *)local_1f8);
                    /* try { // try from 0088ec41 to 0088ec45 has its CatchHandler @ 0088ef55 */
                  std::wstring::assign((wstring_conflict *)&getEquipmentType(bool)::g_Rifle);
                    /* try { // try from 0088ec49 to 0088ec65 has its CatchHandler @ 0088f331 */
                  std::wstring::~wstring(local_1f8);
                }
                pwVar6 = local_208;
                std::operator+(pwVar6,pwVar7);
                    /* try { // try from 0088ec6c to 0088ec70 has its CatchHandler @ 0088f3cd */
                std::wstring::assign(pwVar7);
              }
            }
            else {
              if ((getEquipmentType(bool)::g_Pistol == '\0') &&
                 (iVar4 = __cxa_guard_acquire(&getEquipmentType(bool)::g_Pistol), iVar4 != 0)) {
                getEquipmentType(bool)::g_Pistol = &DAT_01424558;
                __cxa_guard_release(&getEquipmentType(bool)::g_Pistol);
                __cxa_atexit(std::wstring::~wstring,&getEquipmentType(bool)::g_Pistol,&__dso_handle)
                ;
              }
              if (*(long *)(getEquipmentType(bool)::g_Pistol + -6) == 0) {
                CStringTranslate::getSinglton();
                CStringTranslate::getTranslateString((wchar_t *)local_1d8);
                    /* try { // try from 0088e8f5 to 0088e8f9 has its CatchHandler @ 0088f3e5 */
                std::wstring::assign((wstring_conflict *)&getEquipmentType(bool)::g_Pistol);
                    /* try { // try from 0088e8fd to 0088e919 has its CatchHandler @ 0088f331 */
                std::wstring::~wstring(local_1d8);
              }
              pwVar6 = local_1e8;
              std::operator+(pwVar6,pwVar7);
                    /* try { // try from 0088e920 to 0088e924 has its CatchHandler @ 0088eeaa */
              std::wstring::assign(pwVar7);
            }
          }
          else {
            if ((getEquipmentType(bool)::g_Staff == '\0') &&
               (iVar4 = __cxa_guard_acquire(&getEquipmentType(bool)::g_Staff), iVar4 != 0)) {
              getEquipmentType(bool)::g_Staff = &DAT_01424558;
              __cxa_guard_release(&getEquipmentType(bool)::g_Staff);
              __cxa_atexit(std::wstring::~wstring,&getEquipmentType(bool)::g_Staff,&__dso_handle);
            }
            if (*(long *)(getEquipmentType(bool)::g_Staff + -6) == 0) {
              CStringTranslate::getSinglton();
              CStringTranslate::getTranslateString((wchar_t *)local_1b8);
                    /* try { // try from 0088e632 to 0088e636 has its CatchHandler @ 0088ee72 */
              std::wstring::assign((wstring_conflict *)&getEquipmentType(bool)::g_Staff);
                    /* try { // try from 0088e63a to 0088e656 has its CatchHandler @ 0088f331 */
              std::wstring::~wstring(local_1b8);
            }
            pwVar6 = local_1c8;
            std::operator+(pwVar6,pwVar7);
                    /* try { // try from 0088e65d to 0088e661 has its CatchHandler @ 0088f347 */
            std::wstring::assign(pwVar7);
          }
        }
        else {
          if ((getEquipmentType(bool)::g_Polearm == '\0') &&
             (iVar4 = __cxa_guard_acquire(&getEquipmentType(bool)::g_Polearm), iVar4 != 0)) {
            getEquipmentType(bool)::g_Polearm = &DAT_01424558;
            __cxa_guard_release(&getEquipmentType(bool)::g_Polearm);
            __cxa_atexit(std::wstring::~wstring,&getEquipmentType(bool)::g_Polearm,&__dso_handle);
          }
          if (*(long *)(getEquipmentType(bool)::g_Polearm + -6) == 0) {
            CStringTranslate::getSinglton();
            CStringTranslate::getTranslateString((wchar_t *)local_198);
                    /* try { // try from 0088e3f3 to 0088e3f7 has its CatchHandler @ 0088ee46 */
            std::wstring::assign((wstring_conflict *)&getEquipmentType(bool)::g_Polearm);
                    /* try { // try from 0088e3fb to 0088e417 has its CatchHandler @ 0088f331 */
            std::wstring::~wstring(local_198);
          }
          pwVar6 = local_1a8;
          std::operator+(pwVar6,pwVar7);
                    /* try { // try from 0088e41e to 0088e422 has its CatchHandler @ 0088ee42 */
          std::wstring::assign(pwVar7);
        }
      }
      else {
        if ((getEquipmentType(bool)::g_Mace == '\0') &&
           (iVar4 = __cxa_guard_acquire(&getEquipmentType(bool)::g_Mace), iVar4 != 0)) {
          getEquipmentType(bool)::g_Mace = &DAT_01424558;
          __cxa_guard_release(&getEquipmentType(bool)::g_Mace);
          __cxa_atexit(std::wstring::~wstring,&getEquipmentType(bool)::g_Mace,&__dso_handle);
        }
        if (*(long *)(getEquipmentType(bool)::g_Mace + -6) == 0) {
          CStringTranslate::getSinglton();
          CStringTranslate::getTranslateString((wchar_t *)local_178);
                    /* try { // try from 0088de05 to 0088de09 has its CatchHandler @ 0088f125 */
          std::wstring::assign((wstring_conflict *)&getEquipmentType(bool)::g_Mace);
                    /* try { // try from 0088de0d to 0088de29 has its CatchHandler @ 0088f331 */
          std::wstring::~wstring(local_178);
        }
        pwVar6 = local_188;
        std::operator+(pwVar6,pwVar7);
                    /* try { // try from 0088de30 to 0088de34 has its CatchHandler @ 0088f155 */
        std::wstring::assign(pwVar7);
      }
    }
    else {
      if ((getEquipmentType(bool)::g_Axe == '\0') &&
         (iVar4 = __cxa_guard_acquire(&getEquipmentType(bool)::g_Axe), iVar4 != 0)) {
        getEquipmentType(bool)::g_Axe = &DAT_01424558;
        __cxa_guard_release(&getEquipmentType(bool)::g_Axe);
        __cxa_atexit(std::wstring::~wstring,&getEquipmentType(bool)::g_Axe,&__dso_handle);
      }
      if (*(long *)(getEquipmentType(bool)::g_Axe + -6) == 0) {
        CStringTranslate::getSinglton();
        CStringTranslate::getTranslateString((wchar_t *)local_158);
                    /* try { // try from 0088db05 to 0088db09 has its CatchHandler @ 0088f1e7 */
        std::wstring::assign((wstring_conflict *)&getEquipmentType(bool)::g_Axe);
                    /* try { // try from 0088db0d to 0088db29 has its CatchHandler @ 0088f331 */
        std::wstring::~wstring(local_158);
      }
      pwVar6 = local_168;
      std::operator+(pwVar6,pwVar7);
                    /* try { // try from 0088db30 to 0088db34 has its CatchHandler @ 0088f2a5 */
      std::wstring::assign(pwVar7);
    }
  }
LAB_0088db35:
                    /* try { // try from 0088db38 to 0088db94 has its CatchHandler @ 0088f331 */
  std::wstring::~wstring(pwVar6);
LAB_0088d1ae:
  wcslen(L"{");
                    /* try { // try from 0088d1c5 to 0088d23c has its CatchHandler @ 0088f331 */
  iVar4 = std::wstring::find((wchar_t *)pwVar7,0xfa3b9c,0);
  wcslen(L"}");
  iVar5 = std::wstring::find((wchar_t *)pwVar7,0xfa3bac,(long)iVar4);
  if (((iVar5 != -1) && (iVar4 != -1)) && (iVar4 + 1 < iVar5)) {
    wcslen(L"");
                    /* try { // try from 0088d2ba to 0088d2be has its CatchHandler @ 0088f331 */
    std::wstring::replace
              ((ulong)pwVar7,(long)iVar4,(wchar_t *)(long)((iVar5 - iVar4) + 1),0x1001608);
  }
  return pwVar7;
}



/* address=0088f420
   symbol=CEquipment::getEquipmentDescription */

/* WARNING: Removing unreachable block (ram,0x00892f5c) */
/* WARNING: Removing unreachable block (ram,0x00892f0a) */
/* WARNING: Removing unreachable block (ram,0x00892e60) */
/* WARNING: Removing unreachable block (ram,0x00892e47) */
/* WARNING: Removing unreachable block (ram,0x00893050) */
/* WARNING: Removing unreachable block (ram,0x00892550) */
/* WARNING: Removing unreachable block (ram,0x008930a2) */
/* WARNING: Removing unreachable block (ram,0x008926a8) */
/* WARNING: Removing unreachable block (ram,0x008926c1) */
/* WARNING: Removing unreachable block (ram,0x0089274d) */
/* WARNING: Removing unreachable block (ram,0x008935b2) */
/* WARNING: Removing unreachable block (ram,0x0089359c) */
/* WARNING: Removing unreachable block (ram,0x00892287) */
/* WARNING: Removing unreachable block (ram,0x008922ae) */
/* WARNING: Removing unreachable block (ram,0x00892279) */
/* WARNING: Removing unreachable block (ram,0x008923ff) */
/* WARNING: Removing unreachable block (ram,0x00892fe2) */
/* WARNING: Removing unreachable block (ram,0x00892c48) */
/* WARNING: Removing unreachable block (ram,0x00893435) */
/* WARNING: Removing unreachable block (ram,0x0089344e) */
/* WARNING: Removing unreachable block (ram,0x0089287e) */
/* WARNING: Removing unreachable block (ram,0x00892853) */
/* WARNING: Removing unreachable block (ram,0x008927e5) */
/* WARNING: Removing unreachable block (ram,0x00892a9a) */
/* WARNING: Removing unreachable block (ram,0x00892a58) */
/* WARNING: Removing unreachable block (ram,0x008929ea) */
/* WARNING: Removing unreachable block (ram,0x0089297c) */
/* WARNING: Removing unreachable block (ram,0x008923ba) */
/* WARNING: Removing unreachable block (ram,0x0089234c) */
/* WARNING: Removing unreachable block (ram,0x008931f5) */
/* WARNING: Removing unreachable block (ram,0x008931b6) */
/* WARNING: Removing unreachable block (ram,0x00892b11) */
/* WARNING: Removing unreachable block (ram,0x00892ade) */
/* WARNING: Removing unreachable block (ram,0x00892c63) */
/* WARNING: Removing unreachable block (ram,0x00892b1f) */
/* WARNING: Removing unreachable block (ram,0x008935e8) */
/* WARNING: Removing unreachable block (ram,0x008935d5) */
/* WARNING: Removing unreachable block (ram,0x00893175) */
/* WARNING: Removing unreachable block (ram,0x00893642) */
/* WARNING: Removing unreachable block (ram,0x00892ad0) */
/* WARNING: Removing unreachable block (ram,0x00892aec) */
/* WARNING: Removing unreachable block (ram,0x00892bda) */
/* WARNING: Removing unreachable block (ram,0x008925c4) */
/* WARNING: Removing unreachable block (ram,0x008923c7) */
/* WARNING: Removing unreachable block (ram,0x00892cb4) */
/* WARNING: Removing unreachable block (ram,0x00892987) */
/* WARNING: Removing unreachable block (ram,0x008929f5) */
/* WARNING: Removing unreachable block (ram,0x00892a63) */
/* WARNING: Removing unreachable block (ram,0x00892aa5) */
/* WARNING: Removing unreachable block (ram,0x008927f0) */
/* WARNING: Removing unreachable block (ram,0x0089285e) */
/* WARNING: Removing unreachable block (ram,0x0089345c) */
/* WARNING: Removing unreachable block (ram,0x00893443) */
/* WARNING: Removing unreachable block (ram,0x00893427) */
/* WARNING: Removing unreachable block (ram,0x00892be5) */
/* WARNING: Removing unreachable block (ram,0x00892fd4) */
/* WARNING: Removing unreachable block (ram,0x008925cf) */
/* WARNING: Removing unreachable block (ram,0x00892292) */
/* WARNING: Removing unreachable block (ram,0x008922ca) */
/* WARNING: Removing unreachable block (ram,0x008922a0) */
/* WARNING: Removing unreachable block (ram,0x008935a7) */
/* WARNING: Removing unreachable block (ram,0x00893634) */
/* WARNING: Removing unreachable block (ram,0x008926cf) */
/* WARNING: Removing unreachable block (ram,0x008926b6) */
/* WARNING: Removing unreachable block (ram,0x0089269a) */
/* WARNING: Removing unreachable block (ram,0x0089255b) */
/* WARNING: Removing unreachable block (ram,0x00893115) */
/* WARNING: Removing unreachable block (ram,0x00892e39) */
/* WARNING: Removing unreachable block (ram,0x00892e55) */
/* WARNING: Removing unreachable block (ram,0x00892e6e) */
/* WARNING: Removing unreachable block (ram,0x00892f15) */
/* WARNING: Removing unreachable block (ram,0x00892ce6) */
/* WARNING: Removing unreachable block (ram,0x00893650) */
/* WARNING: Removing unreachable block (ram,0x00892c53) */
/* WARNING: Removing unreachable block (ram,0x008922d8) */
/* WARNING: Removing unreachable block (ram,0x008922bc) */
/* CEquipment::getEquipmentDescription(bool, bool) */

wstring_conflict * CEquipment::getEquipmentDescription(bool param_1,bool param_2)

{
  int *piVar1;
  wchar_t wVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  long lVar6;
  long lVar7;
  float *pfVar8;
  CCharacter *pCVar9;
  CStringTranslate *this;
  long *plVar10;
  char in_CL;
  size_t sVar11;
  wchar_t *pwVar12;
  char in_DL;
  uint uVar13;
  size_t sVar14;
  long lVar15;
  undefined7 in_register_00000031;
  CEquipment *this_00;
  undefined7 in_register_00000039;
  wstring_conflict *pwVar16;
  CLevel *this_01;
  uint uVar17;
  wstring_conflict *pwVar18;
  wchar_t *pwVar19;
  float fVar20;
  float fVar21;
  long local_888 [2];
  long local_878 [2];
  long local_868 [2];
  wchar_t *local_858 [2];
  long local_848 [2];
  long local_838 [2];
  long local_828 [2];
  long local_818 [2];
  long local_808 [2];
  long local_7f8 [2];
  wstring_conflict local_7e8 [16];
  wstring_conflict local_7d8 [16];
  wstring_conflict local_7c8 [16];
  wstring_conflict local_7b8 [16];
  wstring_conflict local_7a8 [16];
  wstring_conflict local_798 [16];
  wstring_conflict local_788 [16];
  wstring_conflict local_778 [16];
  wstring_conflict local_768 [16];
  wstring_conflict local_758 [16];
  long local_748 [2];
  wstring_conflict local_738 [16];
  wstring_conflict local_728 [16];
  wstring_conflict local_718 [16];
  wstring_conflict local_708 [16];
  wstring_conflict local_6f8 [16];
  wstring_conflict local_6e8 [16];
  wstring_conflict local_6d8 [16];
  long local_6c8 [2];
  long local_6b8 [2];
  long local_6a8 [2];
  long local_698 [2];
  long local_688 [2];
  long local_678 [2];
  long local_668 [2];
  long local_658 [2];
  long local_648 [2];
  wstring_conflict local_638 [16];
  STRINGS local_628 [16];
  wstring_conflict local_618 [16];
  wstring_conflict local_608 [16];
  wstring_conflict local_5f8 [16];
  long local_5e8 [2];
  wstring_conflict local_5d8 [16];
  wstring_conflict local_5c8 [16];
  wstring_conflict local_5b8 [16];
  wstring_conflict local_5a8 [16];
  wstring_conflict local_598 [16];
  wstring_conflict local_588 [16];
  long local_578 [2];
  long local_568 [2];
  long local_558 [2];
  long local_548 [2];
  long local_538 [2];
  long local_528 [2];
  long local_518 [2];
  long local_508 [2];
  long local_4f8 [2];
  long local_4e8 [2];
  long local_4d8 [2];
  wstring_conflict local_4c8 [16];
  wstring_conflict local_4b8 [16];
  wstring_conflict local_4a8 [16];
  wstring_conflict local_498 [16];
  STRINGS local_488 [16];
  wstring_conflict local_478 [16];
  wstring_conflict local_468 [16];
  STRINGS local_458 [16];
  wstring_conflict local_448 [16];
  wstring_conflict local_438 [16];
  wstring_conflict local_428 [16];
  wstring_conflict local_418 [16];
  STRINGS local_408 [16];
  wstring_conflict local_3f8 [16];
  wstring_conflict local_3e8 [16];
  wstring_conflict local_3d8 [16];
  wstring_conflict local_3c8 [16];
  wstring_conflict local_3b8 [16];
  wstring_conflict local_3a8 [16];
  wstring_conflict local_398 [16];
  long local_388 [2];
  wstring_conflict local_378 [16];
  long local_368 [2];
  long local_358 [2];
  wstring_conflict local_348 [16];
  wstring_conflict local_338 [16];
  wstring_conflict local_328 [16];
  wstring_conflict local_318 [16];
  long local_308 [2];
  long local_2f8 [2];
  long local_2e8 [2];
  long local_2d8 [2];
  long local_2c8 [2];
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
  wchar_t *local_158 [2];
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
  long local_98 [13];

  pwVar16 = (wstring_conflict *)CONCAT71(in_register_00000039,param_1);
  this_00 = (CEquipment *)CONCAT71(in_register_00000031,param_2);
  if ((getEquipmentDescription(bool,bool)::g_Unidentified == '\0') &&
     (iVar4 = __cxa_guard_acquire(&getEquipmentDescription(bool,bool)::g_Unidentified), iVar4 != 0))
  {
    getEquipmentDescription(bool,bool)::g_Unidentified = &DAT_01424558;
    __cxa_guard_release(&getEquipmentDescription(bool,bool)::g_Unidentified);
    __cxa_atexit(std::wstring::~wstring,&getEquipmentDescription(bool,bool)::g_Unidentified,
                 &__dso_handle);
    lVar7 = *(long *)(getEquipmentDescription(bool,bool)::g_Unidentified + -6);
  }
  else {
    lVar7 = *(long *)(getEquipmentDescription(bool,bool)::g_Unidentified + -6);
  }
  if (lVar7 == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_98);
                    /* try { // try from 00890ac1 to 00890ac5 has its CatchHandler @ 00893235 */
    std::wstring::assign((wstring_conflict *)&getEquipmentDescription(bool,bool)::g_Unidentified);
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
  }
  if ((getEquipmentDescription(bool,bool)::g_Damage == '\0') &&
     (iVar4 = __cxa_guard_acquire(&getEquipmentDescription(bool,bool)::g_Damage), iVar4 != 0)) {
    getEquipmentDescription(bool,bool)::g_Damage = &DAT_01424558;
    __cxa_guard_release(&getEquipmentDescription(bool,bool)::g_Damage);
    __cxa_atexit(std::wstring::~wstring,&getEquipmentDescription(bool,bool)::g_Damage,&__dso_handle)
    ;
  }
  if (*(long *)(getEquipmentDescription(bool,bool)::g_Damage + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_a8);
                    /* try { // try from 00890bf5 to 00890bf9 has its CatchHandler @ 00893310 */
    std::wstring::assign((wstring_conflict *)&getEquipmentDescription(bool,bool)::g_Damage);
    if ((allocator *)(local_a8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
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
  if ((getEquipmentDescription(bool,bool)::g_Armor == '\0') &&
     (iVar4 = __cxa_guard_acquire(&getEquipmentDescription(bool,bool)::g_Armor), iVar4 != 0)) {
    getEquipmentDescription(bool,bool)::g_Armor = &DAT_01424558;
    __cxa_guard_release(&getEquipmentDescription(bool,bool)::g_Armor);
    __cxa_atexit(std::wstring::~wstring,&getEquipmentDescription(bool,bool)::g_Armor,&__dso_handle);
    lVar7 = *(long *)(getEquipmentDescription(bool,bool)::g_Armor + -6);
  }
  else {
    lVar7 = *(long *)(getEquipmentDescription(bool,bool)::g_Armor + -6);
  }
  if (lVar7 == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_b8);
                    /* try { // try from 00890b82 to 00890b86 has its CatchHandler @ 00892c5e */
    std::wstring::assign((wstring_conflict *)&getEquipmentDescription(bool,bool)::g_Armor);
    if ((allocator *)(local_b8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_b8[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
      }
    }
  }
  if ((getEquipmentDescription(bool,bool)::g_Type == '\0') &&
     (iVar4 = __cxa_guard_acquire(&getEquipmentDescription(bool,bool)::g_Type), iVar4 != 0)) {
    getEquipmentDescription(bool,bool)::g_Type = &DAT_01424558;
    __cxa_guard_release(&getEquipmentDescription(bool,bool)::g_Type);
    __cxa_atexit(std::wstring::~wstring,&getEquipmentDescription(bool,bool)::g_Type,&__dso_handle);
  }
  if (*(long *)(getEquipmentDescription(bool,bool)::g_Type + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_c8);
                    /* try { // try from 00890ee5 to 00890ee9 has its CatchHandler @ 00893162 */
    std::wstring::assign((wstring_conflict *)&getEquipmentDescription(bool,bool)::g_Type);
    if ((allocator *)(local_c8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_c8[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
      }
    }
  }
  if ((getEquipmentDescription(bool,bool)::g_Sockets == '\0') &&
     (iVar4 = __cxa_guard_acquire(&getEquipmentDescription(bool,bool)::g_Sockets), iVar4 != 0)) {
    getEquipmentDescription(bool,bool)::g_Sockets = &DAT_01424558;
    __cxa_guard_release(&getEquipmentDescription(bool,bool)::g_Sockets);
    __cxa_atexit(std::wstring::~wstring,&getEquipmentDescription(bool,bool)::g_Sockets,&__dso_handle
                );
  }
  if (*(long *)(getEquipmentDescription(bool,bool)::g_Sockets + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_d8);
                    /* try { // try from 00890e2d to 00890e31 has its CatchHandler @ 008935e3 */
    std::wstring::assign((wstring_conflict *)&getEquipmentDescription(bool,bool)::g_Sockets);
    if ((allocator *)(local_d8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_d8[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
      }
    }
  }
  if ((getEquipmentDescription(bool,bool)::g_BuyPrice == '\0') &&
     (iVar4 = __cxa_guard_acquire(&getEquipmentDescription(bool,bool)::g_BuyPrice), iVar4 != 0)) {
    getEquipmentDescription(bool,bool)::g_BuyPrice = &DAT_01424558;
    __cxa_guard_release(&getEquipmentDescription(bool,bool)::g_BuyPrice);
    __cxa_atexit(std::wstring::~wstring,&getEquipmentDescription(bool,bool)::g_BuyPrice,
                 &__dso_handle);
  }
  if (*(long *)(getEquipmentDescription(bool,bool)::g_BuyPrice + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_e8);
                    /* try { // try from 00890d75 to 00890d79 has its CatchHandler @ 00893600 */
    std::wstring::assign((wstring_conflict *)&getEquipmentDescription(bool,bool)::g_BuyPrice);
    if ((allocator *)(local_e8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_e8[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
      }
    }
  }
  if ((getEquipmentDescription(bool,bool)::g_SellPrice == '\0') &&
     (iVar4 = __cxa_guard_acquire(&getEquipmentDescription(bool,bool)::g_SellPrice), iVar4 != 0)) {
    getEquipmentDescription(bool,bool)::g_SellPrice = &DAT_01424558;
    __cxa_guard_release(&getEquipmentDescription(bool,bool)::g_SellPrice);
    __cxa_atexit(std::wstring::~wstring,&getEquipmentDescription(bool,bool)::g_SellPrice,
                 &__dso_handle);
    lVar7 = *(long *)(getEquipmentDescription(bool,bool)::g_SellPrice + -6);
  }
  else {
    lVar7 = *(long *)(getEquipmentDescription(bool,bool)::g_SellPrice + -6);
  }
  if (lVar7 == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_f8);
                    /* try { // try from 00890cfa to 00890cfe has its CatchHandler @ 00893315 */
    std::wstring::assign((wstring_conflict *)&getEquipmentDescription(bool,bool)::g_SellPrice);
    if ((allocator *)(local_f8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_f8[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
      }
    }
  }
  if ((getEquipmentDescription(bool,bool)::g_Unique == '\0') &&
     (iVar4 = __cxa_guard_acquire(&getEquipmentDescription(bool,bool)::g_Unique), iVar4 != 0)) {
    getEquipmentDescription(bool,bool)::g_Unique = &DAT_01424558;
    __cxa_guard_release(&getEquipmentDescription(bool,bool)::g_Unique);
    __cxa_atexit(std::wstring::~wstring,&getEquipmentDescription(bool,bool)::g_Unique,&__dso_handle)
    ;
  }
  if (*(long *)(getEquipmentDescription(bool,bool)::g_Unique + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_108);
                    /* try { // try from 0089144d to 00891451 has its CatchHandler @ 00892ab3 */
    std::wstring::assign((wstring_conflict *)&getEquipmentDescription(bool,bool)::g_Unique);
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
  if ((getEquipmentDescription(bool,bool)::g_Rare == '\0') &&
     (iVar4 = __cxa_guard_acquire(&getEquipmentDescription(bool,bool)::g_Rare), iVar4 != 0)) {
    getEquipmentDescription(bool,bool)::g_Rare = &DAT_01424558;
    __cxa_guard_release(&getEquipmentDescription(bool,bool)::g_Rare);
    __cxa_atexit(std::wstring::~wstring,&getEquipmentDescription(bool,bool)::g_Rare,&__dso_handle);
  }
  if (*(long *)(getEquipmentDescription(bool,bool)::g_Rare + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_118);
                    /* try { // try from 00891395 to 00891399 has its CatchHandler @ 00892afa */
    std::wstring::assign((wstring_conflict *)&getEquipmentDescription(bool,bool)::g_Rare);
    if ((allocator *)(local_118[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_118[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_118[0] + -0x18));
      }
    }
  }
  if ((getEquipmentDescription(bool,bool)::g_Enchanted == '\0') &&
     (iVar4 = __cxa_guard_acquire(&getEquipmentDescription(bool,bool)::g_Enchanted), iVar4 != 0)) {
    getEquipmentDescription(bool,bool)::g_Enchanted = &DAT_01424558;
    __cxa_guard_release(&getEquipmentDescription(bool,bool)::g_Enchanted);
    __cxa_atexit(std::wstring::~wstring,&getEquipmentDescription(bool,bool)::g_Enchanted,
                 &__dso_handle);
  }
  if (*(long *)(getEquipmentDescription(bool,bool)::g_Enchanted + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_128);
                    /* try { // try from 008912dd to 008912e1 has its CatchHandler @ 00892ac6 */
    std::wstring::assign((wstring_conflict *)&getEquipmentDescription(bool,bool)::g_Enchanted);
    if ((allocator *)(local_128[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_128[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_128[0] + -0x18));
      }
    }
  }
  *(undefined4 **)pwVar16 = &DAT_01424558;
  if (this_00[0x348] == (CEquipment)0x0) {
                    /* try { // try from 0088f59c to 0088f5a0 has its CatchHandler @ 00892ac8 */
    std::wstring::wstring
              ((wstring_conflict *)local_138,
               (wstring_conflict *)&getEquipmentDescription(bool,bool)::g_Unidentified);
    wcslen(L" ");
                    /* try { // try from 0088f5b6 to 0088f5ba has its CatchHandler @ 008931c2 */
    std::wstring::append((wchar_t *)local_138,0xfd0b98);
                    /* try { // try from 0088f5c1 to 0088f5c5 has its CatchHandler @ 008931b1 */
    std::wstring::assign(pwVar16);
    if ((allocator *)(local_138[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_138[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_138[0] + -0x18));
      }
    }
                    /* try { // try from 0088f5e6 to 0088f601 has its CatchHandler @ 00892ac8 */
    (**(code **)(*(long *)this_00 + 0x2a0))(this_00);
    std::operator+((wstring_conflict *)local_148,pwVar16);
                    /* try { // try from 0088f608 to 0088f60c has its CatchHandler @ 0089316c */
    std::wstring::assign(pwVar16);
    if ((allocator *)(local_148[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_148[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_148[0] + -0x18));
      }
    }
  }
  else {
                    /* try { // try from 0089070f to 00890766 has its CatchHandler @ 00892ac8 */
    (**(code **)(*(long *)this_00 + 0x2a0))(this_00);
    std::wstring::assign(pwVar16);
  }
  if ((this_00[0x348] != (CEquipment)0x0) && (*(long *)(this_00 + 0x1b8) != 0)) {
                    /* try { // try from 0088f65d to 0088f661 has its CatchHandler @ 00892ac8 */
    std::wstring::wstring((wstring_conflict *)local_158,(wstring_conflict *)(this_00 + 0x2e0));
                    /* try { // try from 0088f681 to 0088f685 has its CatchHandler @ 008931e5 */
    std::wstring::wstring((wstring_conflict *)local_858,(wstring_conflict *)(this_00 + 0x2e8));
    lVar7 = *(long *)(this_00 + 0x1b8);
    uVar17 = *(uint *)(lVar7 + 0x18);
    pwVar12 = ::EMPTY_WSTRING;
    if (uVar17 != 0) {
      uVar13 = 0;
      iVar4 = -1;
      sVar11 = *(size_t *)(::EMPTY_WSTRING + -6);
      pwVar19 = ::EMPTY_WSTRING;
      if (uVar17 != 0) goto LAB_0088f795;
      if (uRam0000000000000074 < 0x80000000) goto LAB_0088f7b0;
      do {
        uVar17 = *(uint *)(lVar7 + 0x18);
        sVar14 = *(size_t *)(pwVar19 + -6);
        pwVar12 = pwVar19;
LAB_0088f6d1:
        lVar6 = 0;
        if (uVar13 < uVar17) {
          if (uVar13 < *(uint *)(lVar7 + 0x1c)) {
            plVar10 = (long *)((ulong)uVar13 * 8 + *(long *)(lVar7 + 0x10));
          }
          else {
            plVar10 = *(long **)(lVar7 + 0x10);
          }
          lVar6 = *plVar10;
        }
        if (*(int *)(lVar6 + 0x74) < 0) {
LAB_0088f782:
          pwVar12 = pwVar19;
          sVar11 = *(size_t *)(pwVar12 + -6);
          pwVar19 = pwVar12;
        }
        else {
          lVar6 = 0;
          if (uVar13 < uVar17) {
            if (uVar13 < *(uint *)(lVar7 + 0x1c)) {
              plVar10 = (long *)((ulong)uVar13 * 8 + *(long *)(lVar7 + 0x10));
            }
            else {
              plVar10 = *(long **)(lVar7 + 0x10);
            }
            lVar6 = *plVar10;
          }
          sVar11 = *(size_t *)(*(wchar_t **)(lVar6 + 0x60) + -6);
          if ((sVar11 != sVar14) ||
             (iVar5 = wmemcmp(*(wchar_t **)(lVar6 + 0x60),pwVar19,sVar14), iVar5 != 0)) {
            lVar6 = 0;
            if (uVar13 < uVar17) {
              if (uVar13 < *(uint *)(lVar7 + 0x1c)) {
                plVar10 = (long *)((ulong)uVar13 * 8 + *(long *)(lVar7 + 0x10));
              }
              else {
                plVar10 = *(long **)(lVar7 + 0x10);
              }
              lVar6 = *plVar10;
            }
            pwVar12 = *(wchar_t **)(lVar6 + 0x60);
            wcslen(pwVar12);
                    /* try { // try from 0088f74e to 0088f88c has its CatchHandler @ 00892d0a */
            std::wstring::assign((wchar_t *)local_858,(ulong)pwVar12);
            lVar7 = *(long *)(this_00 + 0x1b8);
            lVar6 = 0;
            uVar17 = *(uint *)(lVar7 + 0x18);
            if (uVar13 < uVar17) {
              if (uVar13 < *(uint *)(lVar7 + 0x1c)) {
                plVar10 = (long *)((ulong)uVar13 * 8 + *(long *)(lVar7 + 0x10));
              }
              else {
                plVar10 = *(long **)(lVar7 + 0x10);
              }
              lVar6 = *plVar10;
            }
            iVar4 = *(int *)(lVar6 + 0x74);
            pwVar19 = ::EMPTY_WSTRING;
            goto LAB_0088f782;
          }
        }
        uVar13 = uVar13 + 1;
        if (uVar17 <= uVar13) goto LAB_0088f860;
LAB_0088f795:
        if (uVar13 < *(uint *)(lVar7 + 0x1c)) {
          plVar10 = (long *)((ulong)uVar13 * 8 + *(long *)(lVar7 + 0x10));
        }
        else {
          plVar10 = *(long **)(lVar7 + 0x10);
        }
      } while (*(int *)(*plVar10 + 0x74) <= iVar4);
LAB_0088f7b0:
      lVar6 = 0;
      if (uVar13 < uVar17) {
        if (uVar13 < *(uint *)(lVar7 + 0x1c)) {
          plVar10 = (long *)((ulong)uVar13 * 8 + *(long *)(lVar7 + 0x10));
        }
        else {
          plVar10 = *(long **)(lVar7 + 0x10);
        }
        lVar6 = *plVar10;
      }
      sVar14 = *(size_t *)(*(wchar_t **)(lVar6 + 0x58) + -6);
      if ((sVar14 == sVar11) &&
         (iVar5 = wmemcmp(*(wchar_t **)(lVar6 + 0x58),pwVar19,sVar11), iVar5 == 0)) {
        uVar17 = *(uint *)(lVar7 + 0x18);
      }
      else {
        lVar6 = 0;
        if (uVar13 < uVar17) {
          if (uVar13 < *(uint *)(lVar7 + 0x1c)) {
            plVar10 = (long *)((ulong)uVar13 * 8 + *(long *)(lVar7 + 0x10));
          }
          else {
            plVar10 = *(long **)(lVar7 + 0x10);
          }
          lVar6 = *plVar10;
        }
        pwVar12 = *(wchar_t **)(lVar6 + 0x58);
        wcslen(pwVar12);
        std::wstring::assign((wchar_t *)local_158,(ulong)pwVar12);
        lVar7 = *(long *)(this_00 + 0x1b8);
        lVar6 = 0;
        uVar17 = *(uint *)(lVar7 + 0x18);
        if (uVar13 < uVar17) {
          if (uVar13 < *(uint *)(lVar7 + 0x1c)) {
            plVar10 = (long *)((ulong)uVar13 * 8 + *(long *)(lVar7 + 0x10));
          }
          else {
            plVar10 = *(long **)(lVar7 + 0x10);
          }
          lVar6 = *plVar10;
        }
        iVar4 = *(int *)(lVar6 + 0x74);
        sVar14 = *(size_t *)(::EMPTY_WSTRING + -6);
        pwVar12 = ::EMPTY_WSTRING;
        pwVar19 = ::EMPTY_WSTRING;
      }
      goto LAB_0088f6d1;
    }
    sVar11 = *(size_t *)(::EMPTY_WSTRING + -6);
LAB_0088f860:
    sVar14 = *(size_t *)(local_158[0] + -6);
    if ((sVar14 != sVar11) || (iVar4 = wmemcmp(local_158[0],pwVar12,sVar11), iVar4 != 0)) {
      std::wstring::wstring((wstring_conflict *)local_168,(wstring_conflict *)local_158);
      wcslen(L" ");
                    /* try { // try from 0088f8a2 to 0088f8a6 has its CatchHandler @ 00893225 */
      std::wstring::append((wchar_t *)local_168,0xfd0b98);
                    /* try { // try from 0088f8b8 to 0088f8bc has its CatchHandler @ 0089321b */
      std::operator+((wstring_conflict *)local_178,(wstring_conflict *)local_168);
                    /* try { // try from 0088f8c3 to 0088f8c7 has its CatchHandler @ 00893220 */
      std::wstring::assign(pwVar16);
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
      if ((allocator *)(local_168[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_168[0] + -8);
        iVar4 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar4 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_168[0] + -0x18));
        }
      }
                    /* try { // try from 0088f92b to 0088f960 has its CatchHandler @ 00892d0a */
      std::wstring::assign((wstring_conflict *)(this_00 + 0x2e0));
      sVar14 = *(size_t *)(::EMPTY_WSTRING + -6);
      pwVar12 = ::EMPTY_WSTRING;
    }
    pwVar19 = local_858[0];
    if ((*(size_t *)(local_858[0] + -6) != sVar14) ||
       (iVar4 = wmemcmp(local_858[0],pwVar12,sVar14), iVar4 != 0)) {
      std::wstring::wstring((wstring_conflict *)local_188,pwVar16);
      wcslen(L" ");
                    /* try { // try from 0088f976 to 0088f97a has its CatchHandler @ 0089235c */
      std::wstring::append((wchar_t *)local_188,0xfd0b98);
                    /* try { // try from 0088f98e to 0088f992 has its CatchHandler @ 00892357 */
      std::operator+((wstring_conflict *)local_198,(wstring_conflict *)local_188);
                    /* try { // try from 0088f999 to 0088f99d has its CatchHandler @ 00892312 */
      std::wstring::assign(pwVar16);
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
                    /* try { // try from 0088f9d7 to 0088f9db has its CatchHandler @ 00892d0a */
      std::wstring::assign((wstring_conflict *)(this_00 + 0x2e8));
      pwVar19 = local_858[0];
    }
    if ((allocator *)(pwVar19 + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      pwVar12 = pwVar19 + -2;
      wVar2 = *pwVar12;
      *pwVar12 = *pwVar12 + L'\xffffffff';
      UNLOCK();
      if (wVar2 < L'\x01') {
        std::wstring::_Rep::_M_destroy((allocator *)(pwVar19 + -6));
      }
    }
    if ((allocator *)(local_158[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      pwVar12 = local_158[0] + -2;
      wVar2 = *pwVar12;
      *pwVar12 = *pwVar12 + L'\xffffffff';
      UNLOCK();
      if (wVar2 < L'\x01') {
        std::wstring::_Rep::_M_destroy((allocator *)(local_158[0] + -6));
      }
    }
  }
  if (*(int *)(this_00 + 0x3e0) != 0) {
                    /* try { // try from 008910d8 to 008910dc has its CatchHandler @ 00892ac8 */
    STRINGS::GetValueAsWString((uint)local_208);
                    /* try { // try from 008910ed to 008910f1 has its CatchHandler @ 00892869 */
    STRINGS::GetValueAsWString((uint)local_1d8);
                    /* try { // try from 00891100 to 00891104 has its CatchHandler @ 0089288c */
    std::wstring::wstring((wstring_conflict *)local_1a8,pwVar16);
    wcslen(L"\n");
                    /* try { // try from 0089111a to 0089111e has its CatchHandler @ 0089289e */
    std::wstring::append((wchar_t *)local_1a8,0xfd0b48);
                    /* try { // try from 0089112f to 00891133 has its CatchHandler @ 008928ab */
    std::operator+((wstring_conflict *)local_1b8,(wstring_conflict *)local_1a8);
                    /* try { // try from 00891147 to 0089114b has its CatchHandler @ 008928b8 */
    std::wstring::wstring((wstring_conflict *)local_1c8,(wstring_conflict *)local_1b8);
    wcslen(L": ");
                    /* try { // try from 00891161 to 00891165 has its CatchHandler @ 008928ca */
    std::wstring::append((wchar_t *)local_1c8,0xfd0b84);
                    /* try { // try from 00891179 to 0089117d has its CatchHandler @ 008928d7 */
    std::operator+((wstring_conflict *)local_1e8,(wstring_conflict *)local_1c8);
                    /* try { // try from 00891191 to 00891195 has its CatchHandler @ 008928e4 */
    std::wstring::wstring((wstring_conflict *)local_1f8,(wstring_conflict *)local_1e8);
    wcslen(L"/");
                    /* try { // try from 008911ab to 008911af has its CatchHandler @ 008928f6 */
    std::wstring::append((wchar_t *)local_1f8,0xfff8b8);
                    /* try { // try from 008911c3 to 008911c7 has its CatchHandler @ 00892903 */
    std::operator+((wstring_conflict *)local_218,(wstring_conflict *)local_1f8);
                    /* try { // try from 008911d3 to 008911d7 has its CatchHandler @ 00892912 */
    std::wstring::assign(pwVar16);
    if ((allocator *)(local_218[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_218[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_218[0] + -0x18));
      }
    }
    if ((allocator *)(local_1f8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_1f8[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_1f8[0] + -0x18));
      }
    }
    if ((allocator *)(local_1e8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_1e8[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_1e8[0] + -0x18));
      }
    }
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
    if ((allocator *)(local_1d8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_1d8[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_1d8[0] + -0x18));
      }
    }
    if ((allocator *)(local_208[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_208[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_208[0] + -0x18));
      }
    }
  }
  if (in_DL != '\0') {
                    /* try { // try from 00890f7b to 00890f8e has its CatchHandler @ 00892ac8 */
    iVar4 = buyPrice(this_00);
    STRINGS::GetValueAsWString((STRINGS *)local_258,iVar4);
                    /* try { // try from 00890f9d to 00890fa1 has its CatchHandler @ 00892afc */
    std::wstring::wstring((wstring_conflict *)local_228,pwVar16);
    wcslen(L"\n");
                    /* try { // try from 00890fb7 to 00890fbb has its CatchHandler @ 00892b2d */
    std::wstring::append((wchar_t *)local_228,0xfd0b48);
                    /* try { // try from 00890fcc to 00890fd0 has its CatchHandler @ 00892b3a */
    std::operator+((wstring_conflict *)local_238,(wstring_conflict *)local_228);
                    /* try { // try from 00890fe4 to 00890fe8 has its CatchHandler @ 00892b47 */
    std::wstring::wstring((wstring_conflict *)local_248,(wstring_conflict *)local_238);
    wcslen(L": ");
                    /* try { // try from 00890ffe to 00891002 has its CatchHandler @ 00892b59 */
    std::wstring::append((wchar_t *)local_248,0xfd0b84);
                    /* try { // try from 00891019 to 0089101d has its CatchHandler @ 00892b66 */
    std::operator+((wstring_conflict *)local_268,(wstring_conflict *)local_248);
                    /* try { // try from 00891024 to 00891028 has its CatchHandler @ 00892b73 */
    std::wstring::assign(pwVar16);
    if ((allocator *)(local_268[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_268[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_268[0] + -0x18));
      }
    }
    if ((allocator *)(local_248[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_248[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_248[0] + -0x18));
      }
    }
    if ((allocator *)(local_238[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_238[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_238[0] + -0x18));
      }
    }
    if ((allocator *)(local_228[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_228[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_228[0] + -0x18));
      }
    }
    if ((allocator *)(local_258[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_258[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_258[0] + -0x18));
      }
    }
  }
  if (in_CL != '\0') {
                    /* try { // try from 0088fa59 to 0088fa6c has its CatchHandler @ 00892ac8 */
    iVar4 = sellPrice(this_00);
    STRINGS::GetValueAsWString((STRINGS *)local_2a8,iVar4);
                    /* try { // try from 0088fa7b to 0088fa7f has its CatchHandler @ 008934cf */
    std::wstring::wstring((wstring_conflict *)local_278,pwVar16);
    wcslen(L"\n");
                    /* try { // try from 0088fa95 to 0088fa99 has its CatchHandler @ 008934c2 */
    std::wstring::append((wchar_t *)local_278,0xfd0b48);
                    /* try { // try from 0088faaa to 0088faae has its CatchHandler @ 008934b8 */
    std::operator+((wstring_conflict *)local_288,(wstring_conflict *)local_278);
                    /* try { // try from 0088fac2 to 0088fac6 has its CatchHandler @ 008934b3 */
    std::wstring::wstring((wstring_conflict *)local_298,(wstring_conflict *)local_288);
    wcslen(L": ");
                    /* try { // try from 0088fadc to 0088fae0 has its CatchHandler @ 008934a6 */
    std::wstring::append((wchar_t *)local_298,0xfd0b84);
                    /* try { // try from 0088faf7 to 0088fafb has its CatchHandler @ 008934a1 */
    std::operator+((wstring_conflict *)local_2b8,(wstring_conflict *)local_298);
                    /* try { // try from 0088fb02 to 0088fb06 has its CatchHandler @ 00893467 */
    std::wstring::assign(pwVar16);
    if ((allocator *)(local_2b8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_2b8[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_2b8[0] + -0x18));
      }
    }
    if ((allocator *)(local_298[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_298[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_298[0] + -0x18));
      }
    }
    if ((allocator *)(local_288[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_288[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_288[0] + -0x18));
      }
    }
    if ((allocator *)(local_278[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_278[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_278[0] + -0x18));
      }
    }
    if ((allocator *)(local_2a8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_2a8[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_2a8[0] + -0x18));
      }
    }
  }
                    /* try { // try from 0088fb7d to 0088fb9c has its CatchHandler @ 00892ac8 */
  cVar3 = CBaseUnit::ISA((CBaseUnit *)this_00,8);
  if (cVar3 == '\0') {
    cVar3 = CBaseUnit::ISA((CBaseUnit *)this_00,0xd);
    if (cVar3 == '\0') {
      cVar3 = CBaseUnit::ISA((CBaseUnit *)this_00,0x27);
      if (cVar3 == '\0') {
                    /* try { // try from 00891650 to 00891690 has its CatchHandler @ 00892ac8 */
        cVar3 = CBaseUnit::ISA((CBaseUnit *)this_00,0x21);
        if (cVar3 == '\0') {
          cVar3 = CBaseUnit::ISA((CBaseUnit *)this_00,0x2a);
          if (cVar3 != '\0') {
            if ((getEquipmentDescription(bool,bool)::g_Scroll == '\0') &&
               (iVar4 = __cxa_guard_acquire(&getEquipmentDescription(bool,bool)::g_Scroll),
               iVar4 != 0)) {
              getEquipmentDescription(bool,bool)::g_Scroll = &DAT_01424558;
              __cxa_guard_release(&getEquipmentDescription(bool,bool)::g_Scroll);
              __cxa_atexit(std::wstring::~wstring,&getEquipmentDescription(bool,bool)::g_Scroll,
                           &__dso_handle);
            }
            if (*(long *)(getEquipmentDescription(bool,bool)::g_Scroll + -6) == 0) {
              CStringTranslate::getSinglton();
              CStringTranslate::getTranslateString((wchar_t *)local_7a8);
                    /* try { // try from 00891c66 to 00891c6a has its CatchHandler @ 00892ccc */
              std::wstring::assign
                        ((wstring_conflict *)&getEquipmentDescription(bool,bool)::g_Scroll);
                    /* try { // try from 00891c6e to 00891c87 has its CatchHandler @ 00892ac8 */
              std::wstring::~wstring(local_7a8);
            }
            std::operator+(local_7b8,(wchar_t *)pwVar16);
                    /* try { // try from 00891ca0 to 00891ca4 has its CatchHandler @ 0089315c */
            std::operator+(local_7c8,local_7b8);
                    /* try { // try from 00891cb8 to 00891cbc has its CatchHandler @ 00893157 */
            std::operator+(local_7d8,(wchar_t *)local_7c8);
                    /* try { // try from 00891cd0 to 00891cd4 has its CatchHandler @ 00893152 */
            std::operator+(local_7e8,local_7d8);
                    /* try { // try from 00891cdb to 00891cdf has its CatchHandler @ 00893125 */
            std::wstring::assign(pwVar16);
                    /* try { // try from 00891ce3 to 00891ce7 has its CatchHandler @ 00893152 */
            std::wstring::~wstring(local_7e8);
                    /* try { // try from 00891ceb to 00891cef has its CatchHandler @ 00893157 */
            std::wstring::~wstring(local_7d8);
                    /* try { // try from 00891cf3 to 00891cf7 has its CatchHandler @ 0089315c */
            std::wstring::~wstring(local_7c8);
                    /* try { // try from 00891d00 to 00891d76 has its CatchHandler @ 00892ac8 */
            std::wstring::~wstring(local_7b8);
          }
        }
        else {
          if ((getEquipmentDescription(bool,bool)::g_Potion == '\0') &&
             (iVar4 = __cxa_guard_acquire(&getEquipmentDescription(bool,bool)::g_Potion), iVar4 != 0
             )) {
            getEquipmentDescription(bool,bool)::g_Potion = &DAT_01424558;
            __cxa_guard_release(&getEquipmentDescription(bool,bool)::g_Potion);
            __cxa_atexit(std::wstring::~wstring,&getEquipmentDescription(bool,bool)::g_Potion,
                         &__dso_handle);
          }
          if (*(long *)(getEquipmentDescription(bool,bool)::g_Potion + -6) == 0) {
                    /* try { // try from 00891b00 to 00891b1c has its CatchHandler @ 00892ac8 */
            CStringTranslate::getSinglton();
            CStringTranslate::getTranslateString((wchar_t *)local_758);
                    /* try { // try from 00891b25 to 00891b29 has its CatchHandler @ 0089304b */
            std::wstring::assign((wstring_conflict *)&getEquipmentDescription(bool,bool)::g_Potion);
                    /* try { // try from 00891b2d to 00891b4e has its CatchHandler @ 00892ac8 */
            std::wstring::~wstring(local_758);
          }
          std::operator+(local_768,(wchar_t *)pwVar16);
                    /* try { // try from 008916a9 to 008916ad has its CatchHandler @ 00893024 */
          std::operator+(local_778,local_768);
                    /* try { // try from 008916c1 to 008916c5 has its CatchHandler @ 0089301f */
          std::operator+(local_788,(wchar_t *)local_778);
                    /* try { // try from 008916d9 to 008916dd has its CatchHandler @ 00892ff7 */
          std::operator+(local_798,local_788);
                    /* try { // try from 008916e4 to 008916e8 has its CatchHandler @ 0089303e */
          std::wstring::assign(pwVar16);
                    /* try { // try from 008916ec to 008916f0 has its CatchHandler @ 00892ff7 */
          std::wstring::~wstring(local_798);
                    /* try { // try from 008916f4 to 008916f8 has its CatchHandler @ 0089301f */
          std::wstring::~wstring(local_788);
                    /* try { // try from 008916fc to 00891700 has its CatchHandler @ 00893024 */
          std::wstring::~wstring(local_778);
                    /* try { // try from 00891709 to 0089172a has its CatchHandler @ 00892ac8 */
          std::wstring::~wstring(local_768);
        }
        goto LAB_008900b7;
      }
      this = (CStringTranslate *)CStringTranslate::getSinglton();
      CStringTranslate::getTranslateString
                (this,(wstring_conflict *)&getEquipmentDescription(bool,bool)::g_Type);
      std::wstring::wstring((wstring_conflict *)local_6a8,pwVar16);
      wcslen(L"\n");
                    /* try { // try from 008907f1 to 008907f5 has its CatchHandler @ 008930b9 */
      std::wstring::append((wchar_t *)local_6a8,0xfd0b48);
                    /* try { // try from 00890807 to 0089080b has its CatchHandler @ 008930b4 */
      std::operator+((wstring_conflict *)local_6b8,(wstring_conflict *)local_6a8);
                    /* try { // try from 0089081a to 0089081e has its CatchHandler @ 008930af */
      std::wstring::wstring((wstring_conflict *)local_6c8,(wstring_conflict *)local_6b8);
      wcslen(L": ");
                    /* try { // try from 00890834 to 00890838 has its CatchHandler @ 008930ad */
      std::wstring::append((wchar_t *)local_6c8,0xfd0b84);
                    /* try { // try from 0089083f to 00890843 has its CatchHandler @ 0089308a */
      std::wstring::assign(pwVar16);
      if ((allocator *)(local_6c8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_6c8[0] + -8);
        iVar4 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar4 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_6c8[0] + -0x18));
        }
      }
      if ((allocator *)(local_6b8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_6b8[0] + -8);
        iVar4 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar4 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_6b8[0] + -0x18));
        }
      }
      if ((allocator *)(local_6a8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_6a8[0] + -8);
        iVar4 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar4 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_6a8[0] + -0x18));
        }
      }
      if (this_00[0x348] != (CEquipment)0x0) {
        cVar3 = CBaseUnit::ISA((CBaseUnit *)this_00,0x36);
        if (cVar3 == '\0') {
                    /* try { // try from 00891f69 to 00891f89 has its CatchHandler @ 00892ac8 */
          cVar3 = CBaseUnit::ISA((CBaseUnit *)this_00,0x37);
          if (cVar3 == '\0') {
                    /* try { // try from 00891fe7 to 0089200c has its CatchHandler @ 00892ac8 */
            cVar3 = (**(code **)(*(long *)this_00 + 0x2b0))(this_00);
            if (cVar3 == '\0') goto LAB_00890897;
            pwVar18 = local_718;
            std::operator+(pwVar18,pwVar16);
                    /* try { // try from 00892020 to 00892024 has its CatchHandler @ 00892cc7 */
            std::operator+(local_728,(wchar_t *)pwVar18);
                    /* try { // try from 0089202b to 0089202f has its CatchHandler @ 00892cc2 */
            std::wstring::assign(pwVar16);
                    /* try { // try from 00892033 to 00892037 has its CatchHandler @ 00892cc7 */
            std::wstring::~wstring(local_728);
          }
          else {
            pwVar18 = local_6f8;
            std::operator+(pwVar18,pwVar16);
                    /* try { // try from 00891f9d to 00891fa1 has its CatchHandler @ 00892ce1 */
            std::operator+(local_708,(wchar_t *)pwVar18);
                    /* try { // try from 00891fa8 to 00891fac has its CatchHandler @ 00892cdc */
            std::wstring::assign(pwVar16);
                    /* try { // try from 00891fb0 to 00891fb4 has its CatchHandler @ 00892ce1 */
            std::wstring::~wstring(local_708);
          }
        }
        else {
          pwVar18 = local_6d8;
          std::operator+(pwVar18,pwVar16);
                    /* try { // try from 00891d8a to 00891d8e has its CatchHandler @ 00892585 */
          std::operator+(local_6e8,(wchar_t *)pwVar18);
                    /* try { // try from 00891d95 to 00891d99 has its CatchHandler @ 0089257e */
          std::wstring::assign(pwVar16);
                    /* try { // try from 00891d9d to 00891da1 has its CatchHandler @ 00892585 */
          std::wstring::~wstring(local_6e8);
        }
                    /* try { // try from 00891da5 to 00891dbd has its CatchHandler @ 00892ac8 */
        std::wstring::~wstring(pwVar18);
      }
LAB_00890897:
      if ((getEquipmentDescription(bool,bool)::g_Trinket == '\0') &&
         (iVar4 = __cxa_guard_acquire(&getEquipmentDescription(bool,bool)::g_Trinket), iVar4 != 0))
      {
        getEquipmentDescription(bool,bool)::g_Trinket = &DAT_01424558;
        __cxa_guard_release(&getEquipmentDescription(bool,bool)::g_Trinket);
        __cxa_atexit(std::wstring::~wstring,&getEquipmentDescription(bool,bool)::g_Trinket,
                     &__dso_handle);
      }
      if (*(long *)(getEquipmentDescription(bool,bool)::g_Trinket + -6) == 0) {
                    /* try { // try from 008908b2 to 008908ce has its CatchHandler @ 00892ac8 */
        CStringTranslate::getSinglton();
        CStringTranslate::getTranslateString((wchar_t *)local_738);
                    /* try { // try from 008908d7 to 008908db has its CatchHandler @ 00893105 */
        std::wstring::assign((wstring_conflict *)&getEquipmentDescription(bool,bool)::g_Trinket);
                    /* try { // try from 008908df to 008908fb has its CatchHandler @ 00892ac8 */
        std::wstring::~wstring(local_738);
      }
      std::operator+((wstring_conflict *)local_748,pwVar16);
                    /* try { // try from 00890902 to 00890906 has its CatchHandler @ 008930f5 */
      std::wstring::assign(pwVar16);
      if ((allocator *)(local_748[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_748[0] + -8);
        iVar4 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar4 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_748[0] + -0x18));
        }
      }
      goto LAB_008900b7;
    }
    std::wstring::wstring((wstring_conflict *)local_558,pwVar16);
    wcslen(L"\n");
                    /* try { // try from 008903c5 to 008903c9 has its CatchHandler @ 008935f6 */
    std::wstring::append((wchar_t *)local_558,0xfd0b48);
                    /* try { // try from 008903dd to 008903e1 has its CatchHandler @ 008935fb */
    std::operator+((wstring_conflict *)local_568,(wstring_conflict *)local_558);
                    /* try { // try from 008903f0 to 008903f4 has its CatchHandler @ 008935bd */
    std::wstring::wstring((wstring_conflict *)local_578,(wstring_conflict *)local_568);
    wcslen(L": ");
                    /* try { // try from 0089040a to 0089040e has its CatchHandler @ 008935c2 */
    std::wstring::append((wchar_t *)local_578,0xfd0b84);
                    /* try { // try from 00890415 to 00890419 has its CatchHandler @ 00893509 */
    std::wstring::assign(pwVar16);
    if ((allocator *)(local_578[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_578[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_578[0] + -0x18));
      }
    }
    if ((allocator *)(local_568[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_568[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_568[0] + -0x18));
      }
    }
    if ((allocator *)(local_558[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_558[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_558[0] + -0x18));
      }
    }
    if (this_00[0x348] != (CEquipment)0x0) {
                    /* try { // try from 00890471 to 00890495 has its CatchHandler @ 00892ac8 */
      cVar3 = CBaseUnit::ISA((CBaseUnit *)this_00,0x36);
      if (cVar3 == '\0') {
        cVar3 = CBaseUnit::ISA((CBaseUnit *)this_00,0x37);
        if (cVar3 == '\0') {
          cVar3 = (**(code **)(*(long *)this_00 + 0x2b0))(this_00);
          if (cVar3 == '\0') goto LAB_008904c9;
          pwVar18 = local_5c8;
          std::operator+(pwVar18,pwVar16);
                    /* try { // try from 00891a81 to 00891a85 has its CatchHandler @ 00892d05 */
          std::operator+(local_5d8,(wchar_t *)pwVar18);
                    /* try { // try from 00891a8c to 00891a90 has its CatchHandler @ 00892cff */
          std::wstring::assign(pwVar16);
                    /* try { // try from 00891a94 to 00891a98 has its CatchHandler @ 00892d05 */
          std::wstring::~wstring(local_5d8);
        }
        else {
          pwVar18 = local_5a8;
          std::operator+(pwVar18,pwVar16);
                    /* try { // try from 00891b62 to 00891b66 has its CatchHandler @ 00892c76 */
          std::operator+(local_5b8,(wchar_t *)pwVar18);
                    /* try { // try from 00891b6d to 00891b71 has its CatchHandler @ 00892c71 */
          std::wstring::assign(pwVar16);
                    /* try { // try from 00891b75 to 00891b79 has its CatchHandler @ 00892c76 */
          std::wstring::~wstring(local_5b8);
        }
      }
      else {
        pwVar18 = local_588;
        std::operator+(pwVar18,pwVar16);
                    /* try { // try from 008904a9 to 008904ad has its CatchHandler @ 008924cf */
        std::operator+(local_598,(wchar_t *)pwVar18);
                    /* try { // try from 008904b4 to 008904b8 has its CatchHandler @ 008924e2 */
        std::wstring::assign(pwVar16);
                    /* try { // try from 008904bc to 008904c0 has its CatchHandler @ 008924cf */
        std::wstring::~wstring(local_598);
      }
                    /* try { // try from 008904c4 to 008904e0 has its CatchHandler @ 00892ac8 */
      std::wstring::~wstring(pwVar18);
    }
LAB_008904c9:
    std::operator+((wstring_conflict *)local_5e8,pwVar16);
                    /* try { // try from 008904e7 to 008904eb has its CatchHandler @ 00892d15 */
    std::wstring::assign(pwVar16);
    if ((allocator *)(local_5e8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_5e8[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_5e8[0] + -0x18));
      }
    }
    iVar4 = *(int *)(this_00 + 0x338);
                    /* try { // try from 00890528 to 0089058d has its CatchHandler @ 00892ac8 */
    fVar20 = (float)(**(code **)(*(long *)this_00 + 0x250))(0,this_00,0x17,7);
    fVar20 = ceilf((fVar20 * (float)iVar4) / DAT_00fa483c);
    fVar21 = (float)(**(code **)(*(long *)this_00 + 0x250))(0,this_00,8,7);
    fVar21 = ceilf(fVar21);
    iVar4 = (int)fVar20 + iVar4 + (int)fVar21;
    if (*(int *)(this_00 + 0x338) == iVar4) {
                    /* try { // try from 008917ca to 008917ce has its CatchHandler @ 00892ac8 */
      STRINGS::GetValueAsWString(local_628,*(int *)(this_00 + 0x338));
                    /* try { // try from 008917df to 008917e3 has its CatchHandler @ 00892fa3 */
      std::operator+(local_5f8,(wchar_t *)pwVar16);
                    /* try { // try from 008917fc to 00891800 has its CatchHandler @ 00892f9e */
      std::operator+(local_608,local_5f8);
                    /* try { // try from 00891814 to 00891818 has its CatchHandler @ 00892f99 */
      std::operator+(local_618,(wchar_t *)local_608);
                    /* try { // try from 0089182f to 00891833 has its CatchHandler @ 00892f67 */
      std::operator+(local_638,local_618);
                    /* try { // try from 0089183a to 0089183e has its CatchHandler @ 00893029 */
      std::wstring::assign(pwVar16);
                    /* try { // try from 00891842 to 00891846 has its CatchHandler @ 00892f67 */
      std::wstring::~wstring(local_638);
                    /* try { // try from 0089184a to 0089184e has its CatchHandler @ 00892f99 */
      std::wstring::~wstring(local_618);
                    /* try { // try from 00891852 to 00891856 has its CatchHandler @ 00892f9e */
      std::wstring::~wstring(local_608);
                    /* try { // try from 0089185f to 00891863 has its CatchHandler @ 00892fa3 */
      std::wstring::~wstring(local_5f8);
                    /* try { // try from 0089186c to 00891892 has its CatchHandler @ 00892ac8 */
      std::wstring::~wstring((wstring_conflict *)local_628);
    }
    else {
      STRINGS::GetValueAsWString((STRINGS *)local_678,iVar4);
                    /* try { // try from 0089059c to 008905a0 has its CatchHandler @ 00892788 */
      std::wstring::wstring((wstring_conflict *)local_648,pwVar16);
      wcslen(L"\n");
                    /* try { // try from 008905b6 to 008905ba has its CatchHandler @ 0089277b */
      std::wstring::append((wchar_t *)local_648,0xfd0b48);
                    /* try { // try from 008905cb to 008905cf has its CatchHandler @ 00892776 */
      std::operator+((wstring_conflict *)local_658,(wstring_conflict *)local_648);
                    /* try { // try from 008905e3 to 008905e7 has its CatchHandler @ 00892771 */
      std::wstring::wstring((wstring_conflict *)local_668,(wstring_conflict *)local_658);
      wcslen(L": ");
                    /* try { // try from 008905fd to 00890601 has its CatchHandler @ 00892764 */
      std::wstring::append((wchar_t *)local_668,0xfd0b84);
                    /* try { // try from 00890615 to 00890619 has its CatchHandler @ 0089275f */
      std::operator+((wstring_conflict *)local_688,(wstring_conflict *)local_668);
                    /* try { // try from 0089062d to 00890631 has its CatchHandler @ 0089275a */
      std::wstring::wstring((wstring_conflict *)local_698,(wstring_conflict *)local_688);
      wcslen(L"*");
                    /* try { // try from 00890647 to 0089064b has its CatchHandler @ 00892758 */
      std::wstring::append((wchar_t *)local_698,0xff3cdc);
                    /* try { // try from 00890652 to 00890656 has its CatchHandler @ 00892706 */
      std::wstring::assign(pwVar16);
      if ((allocator *)(local_698[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_698[0] + -8);
        iVar4 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar4 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_698[0] + -0x18));
        }
      }
      if ((allocator *)(local_688[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_688[0] + -8);
        iVar4 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar4 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_688[0] + -0x18));
        }
      }
      if ((allocator *)(local_668[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_668[0] + -8);
        iVar4 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar4 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_668[0] + -0x18));
        }
      }
      if ((allocator *)(local_658[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_658[0] + -8);
        iVar4 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar4 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_658[0] + -0x18));
        }
      }
      if ((allocator *)(local_648[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_648[0] + -8);
        iVar4 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar4 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_648[0] + -0x18));
        }
      }
      if ((allocator *)(local_678[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_678[0] + -8);
        iVar4 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar4 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_678[0] + -0x18));
        }
      }
    }
    goto LAB_008900b7;
  }
  std::wstring::wstring((wstring_conflict *)local_2c8,pwVar16);
  wcslen(L"\n");
                    /* try { // try from 0088fbb2 to 0088fbb6 has its CatchHandler @ 0089333a */
  std::wstring::append((wchar_t *)local_2c8,0xfd0b48);
                    /* try { // try from 0088fbca to 0088fbce has its CatchHandler @ 008931d5 */
  std::operator+((wstring_conflict *)local_2d8,(wstring_conflict *)local_2c8);
                    /* try { // try from 0088fbdd to 0088fbe1 has its CatchHandler @ 008931cc */
  std::wstring::wstring((wstring_conflict *)local_2e8,(wstring_conflict *)local_2d8);
  wcslen(L": ");
                    /* try { // try from 0088fbf7 to 0088fbfb has its CatchHandler @ 008931c7 */
  std::wstring::append((wchar_t *)local_2e8,0xfd0b84);
                    /* try { // try from 0088fc02 to 0088fc06 has its CatchHandler @ 00893167 */
  std::wstring::assign(pwVar16);
  if ((allocator *)(local_2e8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_2e8[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_2e8[0] + -0x18));
    }
  }
  if ((allocator *)(local_2d8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_2d8[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_2d8[0] + -0x18));
    }
  }
  if ((allocator *)(local_2c8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_2c8[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_2c8[0] + -0x18));
    }
  }
  if (this_00[0x348] != (CEquipment)0x0) {
    cVar3 = CBaseUnit::ISA((CBaseUnit *)this_00,0x36);
    if (cVar3 == '\0') {
      cVar3 = CBaseUnit::ISA((CBaseUnit *)this_00,0x37);
      if (cVar3 == '\0') {
                    /* try { // try from 00891aa5 to 00891aca has its CatchHandler @ 00892ac8 */
        cVar3 = (**(code **)(*(long *)this_00 + 0x2b0))(this_00);
        if (cVar3 == '\0') goto LAB_0088fc5b;
        pwVar18 = local_338;
        std::operator+(pwVar18,pwVar16);
                    /* try { // try from 00891ade to 00891ae2 has its CatchHandler @ 008923ea */
        std::operator+(local_348,(wchar_t *)pwVar18);
                    /* try { // try from 00891ae9 to 00891aed has its CatchHandler @ 008923d2 */
        std::wstring::assign(pwVar16);
                    /* try { // try from 00891af1 to 00891af5 has its CatchHandler @ 008923ea */
        std::wstring::~wstring(local_348);
      }
      else {
        pwVar18 = local_318;
        std::operator+(pwVar18,pwVar16);
                    /* try { // try from 0089077a to 0089077e has its CatchHandler @ 008930d5 */
        std::operator+(local_328,(wchar_t *)pwVar18);
                    /* try { // try from 00890785 to 00890789 has its CatchHandler @ 008930c5 */
        std::wstring::assign(pwVar16);
                    /* try { // try from 0089078d to 00890791 has its CatchHandler @ 008930d5 */
        std::wstring::~wstring(local_328);
      }
                    /* try { // try from 00890795 to 008907db has its CatchHandler @ 00892ac8 */
      std::wstring::~wstring(pwVar18);
    }
    else {
      std::operator+((wstring_conflict *)local_2f8,pwVar16);
                    /* try { // try from 00891739 to 0089173d has its CatchHandler @ 008930e5 */
      std::wstring::wstring((wstring_conflict *)local_308,(wstring_conflict *)local_2f8);
      wcslen(L" ");
                    /* try { // try from 00891753 to 00891757 has its CatchHandler @ 00892ff2 */
      std::wstring::append((wchar_t *)local_308,0xfd0b98);
                    /* try { // try from 0089175e to 00891762 has its CatchHandler @ 00892fed */
      std::wstring::assign(pwVar16);
      if ((allocator *)(local_308[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_308[0] + -8);
        iVar4 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar4 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_308[0] + -0x18));
        }
      }
      if ((allocator *)(local_2f8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_2f8[0] + -8);
        iVar4 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar4 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_2f8[0] + -0x18));
        }
      }
    }
  }
LAB_0088fc5b:
                    /* try { // try from 0088fc63 to 0088fca6 has its CatchHandler @ 00892ac8 */
  cVar3 = CBaseUnit::ISA((CBaseUnit *)this_00,0xb);
  if (cVar3 == '\0') {
                    /* try { // try from 00891580 to 008915c4 has its CatchHandler @ 00892ac8 */
    cVar3 = CBaseUnit::ISA((CBaseUnit *)this_00,0x24);
    if (cVar3 == '\0') {
                    /* try { // try from 00891b87 to 00891bcb has its CatchHandler @ 00892ac8 */
      cVar3 = CBaseUnit::ISA((CBaseUnit *)this_00,0x2c);
      if (cVar3 == '\0') {
        if ((getEquipmentDescription(bool,bool)::g_Weapon == '\0') &&
           (iVar4 = __cxa_guard_acquire(&getEquipmentDescription(bool,bool)::g_Weapon), iVar4 != 0))
        {
          getEquipmentDescription(bool,bool)::g_Weapon = &DAT_01424558;
          __cxa_guard_release(&getEquipmentDescription(bool,bool)::g_Weapon);
          __cxa_atexit(std::wstring::~wstring,&getEquipmentDescription(bool,bool)::g_Weapon,
                       &__dso_handle);
        }
        if (*(long *)(getEquipmentDescription(bool,bool)::g_Weapon + -6) == 0) {
          CStringTranslate::getSinglton();
          CStringTranslate::getTranslateString((wchar_t *)local_3b8);
                    /* try { // try from 00891f2c to 00891f30 has its CatchHandler @ 00892c7b */
          std::wstring::assign((wstring_conflict *)&getEquipmentDescription(bool,bool)::g_Weapon);
                    /* try { // try from 00891f34 to 00891f50 has its CatchHandler @ 00892ac8 */
          std::wstring::~wstring(local_3b8);
        }
        pwVar18 = local_3c8;
        std::operator+(pwVar18,pwVar16);
                    /* try { // try from 00891f57 to 00891f5b has its CatchHandler @ 0089258a */
        std::wstring::assign(pwVar16);
      }
      else {
        if ((getEquipmentDescription(bool,bool)::g_Axe == '\0') &&
           (iVar4 = __cxa_guard_acquire(&getEquipmentDescription(bool,bool)::g_Axe), iVar4 != 0)) {
          getEquipmentDescription(bool,bool)::g_Axe = &DAT_01424558;
          __cxa_guard_release(&getEquipmentDescription(bool,bool)::g_Axe);
          __cxa_atexit(std::wstring::~wstring,&getEquipmentDescription(bool,bool)::g_Axe,
                       &__dso_handle);
        }
        if (*(long *)(getEquipmentDescription(bool,bool)::g_Axe + -6) == 0) {
          CStringTranslate::getSinglton();
          CStringTranslate::getTranslateString((wchar_t *)local_398);
                    /* try { // try from 00891bd4 to 00891bd8 has its CatchHandler @ 00892caf */
          std::wstring::assign((wstring_conflict *)&getEquipmentDescription(bool,bool)::g_Axe);
                    /* try { // try from 00891bdc to 00891bf8 has its CatchHandler @ 00892ac8 */
          std::wstring::~wstring(local_398);
        }
        pwVar18 = local_3a8;
        std::operator+(pwVar18,pwVar16);
                    /* try { // try from 00891bff to 00891c03 has its CatchHandler @ 008924f2 */
        std::wstring::assign(pwVar16);
      }
                    /* try { // try from 00891c07 to 00891c5d has its CatchHandler @ 00892ac8 */
      std::wstring::~wstring(pwVar18);
    }
    else {
      if ((getEquipmentDescription(bool,bool)::g_Bow == '\0') &&
         (iVar4 = __cxa_guard_acquire(&getEquipmentDescription(bool,bool)::g_Bow), iVar4 != 0)) {
        getEquipmentDescription(bool,bool)::g_Bow = &DAT_01424558;
        __cxa_guard_release(&getEquipmentDescription(bool,bool)::g_Bow);
        __cxa_atexit(std::wstring::~wstring,&getEquipmentDescription(bool,bool)::g_Bow,&__dso_handle
                    );
      }
      if (*(long *)(getEquipmentDescription(bool,bool)::g_Bow + -6) == 0) {
        CStringTranslate::getSinglton();
        CStringTranslate::getTranslateString((wchar_t *)local_378);
                    /* try { // try from 008915cd to 008915d1 has its CatchHandler @ 0089240d */
        std::wstring::assign((wstring_conflict *)&getEquipmentDescription(bool,bool)::g_Bow);
                    /* try { // try from 008915d5 to 008915f1 has its CatchHandler @ 00892ac8 */
        std::wstring::~wstring(local_378);
      }
      std::operator+((wstring_conflict *)local_388,pwVar16);
                    /* try { // try from 008915f8 to 008915fc has its CatchHandler @ 008923ef */
      std::wstring::assign(pwVar16);
      if ((allocator *)(local_388[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_388[0] + -8);
        iVar4 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar4 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_388[0] + -0x18));
        }
      }
    }
  }
  else {
    if ((getEquipmentDescription(bool,bool)::g_Sword == '\0') &&
       (iVar4 = __cxa_guard_acquire(&getEquipmentDescription(bool,bool)::g_Sword), iVar4 != 0)) {
      getEquipmentDescription(bool,bool)::g_Sword = &DAT_01424558;
      __cxa_guard_release(&getEquipmentDescription(bool,bool)::g_Sword);
      __cxa_atexit(std::wstring::~wstring,&getEquipmentDescription(bool,bool)::g_Sword,&__dso_handle
                  );
    }
    if (*(long *)(getEquipmentDescription(bool,bool)::g_Sword + -6) == 0) {
                    /* try { // try from 00891502 to 0089151e has its CatchHandler @ 00892ac8 */
      CStringTranslate::getSinglton();
      CStringTranslate::getTranslateString((wchar_t *)local_358);
                    /* try { // try from 00891527 to 0089152b has its CatchHandler @ 008925dd */
      std::wstring::assign((wstring_conflict *)&getEquipmentDescription(bool,bool)::g_Sword);
      if ((allocator *)(local_358[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_358[0] + -8);
        iVar4 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar4 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_358[0] + -0x18));
        }
      }
    }
    std::operator+((wstring_conflict *)local_368,pwVar16);
                    /* try { // try from 0088fcad to 0088fcb1 has its CatchHandler @ 00893504 */
    std::wstring::assign(pwVar16);
    if ((allocator *)(local_368[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_368[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_368[0] + -0x18));
      }
    }
  }
  iVar4 = *(int *)(this_00 + 0x330);
  if ((iVar4 != 0) && (iVar5 = *(int *)(this_00 + 0x334), iVar5 != 0)) {
    if (iVar4 == iVar5) {
      STRINGS::GetValueAsWString(local_408,iVar4);
                    /* try { // try from 00891dce to 00891dd2 has its CatchHandler @ 0089245d */
      std::operator+(local_3d8,(wchar_t *)pwVar16);
                    /* try { // try from 00891de8 to 00891dec has its CatchHandler @ 00892458 */
      std::operator+(local_3e8,local_3d8);
                    /* try { // try from 00891e05 to 00891e09 has its CatchHandler @ 00892453 */
      std::operator+(local_3f8,(wchar_t *)local_3e8);
                    /* try { // try from 00891e20 to 00891e24 has its CatchHandler @ 0089244e */
      std::operator+(local_418,local_3f8);
                    /* try { // try from 00891e2b to 00891e2f has its CatchHandler @ 0089240f */
      std::wstring::assign(pwVar16);
                    /* try { // try from 00891e33 to 00891e37 has its CatchHandler @ 0089244e */
      std::wstring::~wstring(local_418);
                    /* try { // try from 00891e3b to 00891e3f has its CatchHandler @ 00892453 */
      std::wstring::~wstring(local_3f8);
                    /* try { // try from 00891e48 to 00891e4c has its CatchHandler @ 00892458 */
      std::wstring::~wstring(local_3e8);
                    /* try { // try from 00891e55 to 00891e59 has its CatchHandler @ 0089245d */
      std::wstring::~wstring(local_3d8);
                    /* try { // try from 00891e62 to 00891f23 has its CatchHandler @ 00892ac8 */
      std::wstring::~wstring((wstring_conflict *)local_408);
    }
    else {
                    /* try { // try from 0088fcf7 to 0088fcfb has its CatchHandler @ 00892ac8 */
      STRINGS::GetValueAsWString(local_488,iVar5);
                    /* try { // try from 0088fd0c to 0088fd10 has its CatchHandler @ 00892576 */
      STRINGS::GetValueAsWString(local_458,*(int *)(this_00 + 0x330));
                    /* try { // try from 0088fd21 to 0088fd25 has its CatchHandler @ 0089256e */
      std::operator+(local_428,(wchar_t *)pwVar16);
                    /* try { // try from 0088fd3b to 0088fd3f has its CatchHandler @ 00892566 */
      std::operator+(local_438,local_428);
                    /* try { // try from 0088fd55 to 0088fd59 has its CatchHandler @ 008924ca */
      std::operator+(local_448,(wchar_t *)local_438);
                    /* try { // try from 0088fd72 to 0088fd76 has its CatchHandler @ 008924c5 */
      std::operator+(local_468,local_448);
                    /* try { // try from 0088fd8f to 0088fd93 has its CatchHandler @ 008924c0 */
      std::operator+(local_478,(wchar_t *)local_468);
                    /* try { // try from 0088fdaa to 0088fdae has its CatchHandler @ 00892462 */
      std::operator+(local_498,local_478);
                    /* try { // try from 0088fdb5 to 0088fdb9 has its CatchHandler @ 008924d5 */
      std::wstring::assign(pwVar16);
                    /* try { // try from 0088fdbd to 0088fdc1 has its CatchHandler @ 00892462 */
      std::wstring::~wstring(local_498);
                    /* try { // try from 0088fdc5 to 0088fdc9 has its CatchHandler @ 008924c0 */
      std::wstring::~wstring(local_478);
                    /* try { // try from 0088fdd2 to 0088fdd6 has its CatchHandler @ 008924c5 */
      std::wstring::~wstring(local_468);
                    /* try { // try from 0088fddf to 0088fde3 has its CatchHandler @ 008924ca */
      std::wstring::~wstring(local_448);
                    /* try { // try from 0088fdec to 0088fdf0 has its CatchHandler @ 00892566 */
      std::wstring::~wstring(local_438);
                    /* try { // try from 0088fdf9 to 0088fdfd has its CatchHandler @ 0089256e */
      std::wstring::~wstring(local_428);
                    /* try { // try from 0088fe06 to 0088fe0a has its CatchHandler @ 00892576 */
      std::wstring::~wstring((wstring_conflict *)local_458);
                    /* try { // try from 0088fe13 to 0088fedf has its CatchHandler @ 00892ac8 */
      std::wstring::~wstring((wstring_conflict *)local_488);
    }
  }
  lVar7 = *(long *)(this_00 + 0x2a8);
  if (lVar7 == 0) {
    lVar7 = *(long *)(this_00 + 0x2a0);
  }
  iVar4 = 0;
  pfVar8 = (float *)&KWeaponSpeedValues;
  do {
    if (*pfVar8 <= DAT_00fa483c * *(float *)(lVar7 + 0x70)) {
                    /* try { // try from 008919ba to 008919be has its CatchHandler @ 00892ac8 */
      getAttackSpeedString(local_4b8,this_00);
                    /* try { // try from 008919d2 to 008919d6 has its CatchHandler @ 00892cfa */
      std::operator+(local_4a8,(wchar_t *)pwVar16);
                    /* try { // try from 008919ed to 008919f1 has its CatchHandler @ 00892cf5 */
      std::operator+(local_4c8,local_4a8);
                    /* try { // try from 008919f8 to 008919fc has its CatchHandler @ 00892c85 */
      std::wstring::assign(pwVar16);
                    /* try { // try from 00891a00 to 00891a04 has its CatchHandler @ 00892cf5 */
      std::wstring::~wstring(local_4c8);
                    /* try { // try from 00891a08 to 00891a0c has its CatchHandler @ 00892cfa */
      std::wstring::~wstring(local_4a8);
                    /* try { // try from 00891a15 to 00891a6d has its CatchHandler @ 00892ac8 */
      std::wstring::~wstring(local_4b8);
      break;
    }
    iVar4 = iVar4 + 1;
    pfVar8 = pfVar8 + 1;
  } while (iVar4 != 5);
  if (this_00[0x348] != (CEquipment)0x0) {
    lVar6 = *(long *)(this_00 + 0x358);
    lVar7 = *(long *)(this_00 + 0x350);
    if (0 < (int)(lVar6 - lVar7 >> 2)) {
      lVar15 = 0;
      iVar4 = 0;
      do {
        if (0 < *(int *)(*(long *)(this_00 + 0x380) + lVar15)) {
          CStringTranslate::getSinglton();
          CStringTranslate::getTranslateString((wchar_t *)local_518);
                    /* try { // try from 0088fef3 to 0088fef7 has its CatchHandler @ 008935c7 */
          STRINGS::GetValueAsWString
                    ((STRINGS *)local_4e8,*(int *)(*(long *)(this_00 + 0x380) + lVar15));
                    /* try { // try from 0088ff03 to 0088ff07 has its CatchHandler @ 0089331a */
          std::wstring::wstring((wstring_conflict *)local_4d8,pwVar16);
          wcslen(L"\n+");
                    /* try { // try from 0088ff22 to 0088ff26 has its CatchHandler @ 00893325 */
          std::wstring::append((wchar_t *)local_4d8,0xfd0b38);
                    /* try { // try from 0088ff3f to 0088ff43 has its CatchHandler @ 00893245 */
          std::operator+((wstring_conflict *)local_4f8,(wstring_conflict *)local_4d8);
                    /* try { // try from 0088ff54 to 0088ff58 has its CatchHandler @ 00893274 */
          std::wstring::wstring((wstring_conflict *)local_508,(wstring_conflict *)local_4f8);
          wcslen(L" ");
                    /* try { // try from 0088ff73 to 0088ff77 has its CatchHandler @ 00893286 */
          std::wstring::append((wchar_t *)local_508,0xfd0b98);
                    /* try { // try from 0088ff90 to 0088ff94 has its CatchHandler @ 00893298 */
          std::operator+((wstring_conflict *)local_528,(wstring_conflict *)local_508);
                    /* try { // try from 0088ffa0 to 0088ffa4 has its CatchHandler @ 008932aa */
          std::wstring::wstring((wstring_conflict *)local_538,(wstring_conflict *)local_528);
          wcslen(L" ");
                    /* try { // try from 0088ffba to 0088ffbe has its CatchHandler @ 008932bc */
          std::wstring::append((wchar_t *)local_538,0xfd0b98);
                    /* try { // try from 0088ffcf to 0088ffd3 has its CatchHandler @ 008932c9 */
          std::operator+((wstring_conflict *)local_548,(wstring_conflict *)local_538);
                    /* try { // try from 0088ffdf to 0088ffe3 has its CatchHandler @ 008932d6 */
          std::wstring::assign(pwVar16);
          if ((allocator *)(local_548[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_548[0] + -8);
            iVar5 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar5 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_548[0] + -0x18));
            }
          }
          if ((allocator *)(local_538[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_538[0] + -8);
            iVar5 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar5 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_538[0] + -0x18));
            }
          }
          if ((allocator *)(local_528[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_528[0] + -8);
            iVar5 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar5 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_528[0] + -0x18));
            }
          }
          if ((allocator *)(local_508[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_508[0] + -8);
            iVar5 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar5 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_508[0] + -0x18));
            }
          }
          if ((allocator *)(local_4f8[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_4f8[0] + -8);
            iVar5 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar5 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_4f8[0] + -0x18));
            }
          }
          if ((allocator *)(local_4d8[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_4d8[0] + -8);
            iVar5 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar5 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_4d8[0] + -0x18));
            }
          }
          if ((allocator *)(local_4e8[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_4e8[0] + -8);
            iVar5 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar5 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_4e8[0] + -0x18));
            }
          }
          if ((allocator *)(local_518[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_518[0] + -8);
            iVar5 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar5 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_518[0] + -0x18));
            }
          }
          lVar7 = *(long *)(this_00 + 0x350);
          lVar6 = *(long *)(this_00 + 0x358);
        }
        iVar4 = iVar4 + 1;
        lVar15 = lVar15 + 4;
      } while (iVar4 < (int)(lVar6 - lVar7 >> 2));
    }
  }
LAB_008900b7:
  if (*(int *)(this_00 + 0x278) != 0) {
    if ((getEquipmentDescription(bool,bool)::g_RequiresLevel == '\0') &&
       (iVar4 = __cxa_guard_acquire(), iVar4 != 0)) {
      getEquipmentDescription(bool,bool)::g_RequiresLevel = &DAT_01424558;
      __cxa_guard_release(&getEquipmentDescription(bool,bool)::g_RequiresLevel);
      __cxa_atexit(std::wstring::~wstring,&getEquipmentDescription(bool,bool)::g_RequiresLevel,
                   &__dso_handle);
    }
    if (*(long *)(getEquipmentDescription(bool,bool)::g_RequiresLevel + -6) == 0) {
      CStringTranslate::getSinglton();
      CStringTranslate::getTranslateString((wchar_t *)local_7f8);
                    /* try { // try from 0089189b to 0089189f has its CatchHandler @ 00893039 */
      std::wstring::assign((wstring_conflict *)&getEquipmentDescription(bool,bool)::g_RequiresLevel)
      ;
      if ((allocator *)(local_7f8[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_7f8[0] + -8);
        iVar4 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar4 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_7f8[0] + -0x18));
        }
      }
    }
    this_01 = (CLevel *)0x0;
    if (*(long *)(this_00 + 0x68) != 0) {
      this_01 = *(CLevel **)(*(long *)(this_00 + 0x68) + 0x18);
    }
                    /* try { // try from 008900f6 to 00890114 has its CatchHandler @ 00892ac8 */
    pCVar9 = (CCharacter *)CLevel::getPlayer(this_01);
    iVar4 = getLevelRequirement(this_00,pCVar9);
    STRINGS::GetValueAsWString((STRINGS *)local_838,iVar4);
                    /* try { // try from 00890123 to 00890127 has its CatchHandler @ 00893203 */
    std::wstring::wstring((wstring_conflict *)local_808,pwVar16);
    wcslen(L"\n\n");
                    /* try { // try from 0089013d to 00890141 has its CatchHandler @ 0089320b */
    std::wstring::append((wchar_t *)local_808,0xfd0b44);
                    /* try { // try from 00890152 to 00890156 has its CatchHandler @ 008932e8 */
    std::operator+((wstring_conflict *)local_818,(wstring_conflict *)local_808);
                    /* try { // try from 0089016a to 0089016e has its CatchHandler @ 008932f0 */
    std::wstring::wstring((wstring_conflict *)local_828,(wstring_conflict *)local_818);
    wcslen(L": ");
                    /* try { // try from 00890184 to 00890188 has its CatchHandler @ 008932f8 */
    std::wstring::append((wchar_t *)local_828,0xfd0b84);
                    /* try { // try from 0089019f to 008901a3 has its CatchHandler @ 00893308 */
    std::operator+((wstring_conflict *)local_848,(wstring_conflict *)local_828);
                    /* try { // try from 008901aa to 008901ae has its CatchHandler @ 00892d17 */
    std::wstring::assign(pwVar16);
    if ((allocator *)(local_848[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_848[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_848[0] + -0x18));
      }
    }
    if ((allocator *)(local_828[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_828[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_828[0] + -0x18));
      }
    }
    if ((allocator *)(local_818[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_818[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_818[0] + -0x18));
      }
    }
    if ((allocator *)(local_808[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_808[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_808[0] + -0x18));
      }
    }
    if ((allocator *)(local_838[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_838[0] + -8);
      iVar4 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_838[0] + -0x18));
      }
    }
  }
  if (this_00[0x348] != (CEquipment)0x0) {
                    /* try { // try from 0089023c to 00890240 has its CatchHandler @ 00892ac8 */
    getEquipmentEffects();
                    /* try { // try from 0089024b to 00890263 has its CatchHandler @ 00892e79 */
    iVar4 = std::wstring::compare((wchar_t *)local_858);
    if (iVar4 != 0) {
      std::wstring::wstring((wstring_conflict *)local_868,pwVar16);
      wcslen(L"\n");
                    /* try { // try from 00890279 to 0089027d has its CatchHandler @ 00892e8b */
      std::wstring::append((wchar_t *)local_868,0xfd0b48);
                    /* try { // try from 0089028e to 00890292 has its CatchHandler @ 00892e98 */
      std::operator+((wstring_conflict *)local_878,(wstring_conflict *)local_868);
                    /* try { // try from 00890299 to 0089029d has its CatchHandler @ 00892ea5 */
      std::wstring::assign(pwVar16);
      if ((allocator *)(local_878[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_878[0] + -8);
        iVar4 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar4 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_878[0] + -0x18));
        }
      }
      if ((allocator *)(local_868[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_868[0] + -8);
        iVar4 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar4 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_868[0] + -0x18));
        }
      }
    }
    if ((allocator *)(local_858[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      pwVar12 = local_858[0] + -2;
      wVar2 = *pwVar12;
      *pwVar12 = *pwVar12 + L'\xffffffff';
      UNLOCK();
      if (wVar2 < L'\x01') {
        std::wstring::_Rep::_M_destroy((allocator *)(local_858[0] + -6));
      }
    }
  }
  pwVar12 = *(wchar_t **)pwVar16;
  sVar11 = *(size_t *)(pwVar12 + -6);
  if ((sVar11 != *(size_t *)(::EMPTY_WSTRING + -6)) ||
     (iVar4 = wmemcmp(pwVar12,::EMPTY_WSTRING,sVar11), iVar4 != 0)) {
    while( true ) {
      if (L'\xffffffff' < pwVar12[-2]) {
                    /* try { // try from 00890360 to 008903af has its CatchHandler @ 00892ac8 */
        std::wstring::_M_leak_hard();
        pwVar12 = *(wchar_t **)pwVar16;
      }
      if (pwVar12[sVar11 - 1] != L'\n') break;
                    /* try { // try from 00890328 to 0089032c has its CatchHandler @ 00892ac8 */
      std::wstring::wstring((wstring_conflict *)local_888,pwVar16,0,*(long *)(pwVar12 + -6) - 1);
                    /* try { // try from 00890333 to 00890337 has its CatchHandler @ 00892f4c */
      std::wstring::assign(pwVar16);
      if ((allocator *)(local_888[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_888[0] + -8);
        iVar4 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar4 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_888[0] + -0x18));
        }
      }
      pwVar12 = *(wchar_t **)pwVar16;
      sVar11 = *(size_t *)(pwVar12 + -6);
    }
  }
  return pwVar16;
}



/* address=00893660
   symbol=CEquipment::getEquipmentStats */

/* WARNING: Removing unreachable block (ram,0x0089942e) */
/* WARNING: Removing unreachable block (ram,0x008981ff) */
/* WARNING: Removing unreachable block (ram,0x00898436) */
/* WARNING: Removing unreachable block (ram,0x00898a90) */
/* WARNING: Removing unreachable block (ram,0x00898802) */
/* WARNING: Removing unreachable block (ram,0x00899325) */
/* WARNING: Removing unreachable block (ram,0x0089920e) */
/* WARNING: Removing unreachable block (ram,0x00898c94) */
/* WARNING: Removing unreachable block (ram,0x00898618) */
/* WARNING: Removing unreachable block (ram,0x00898cb6) */
/* WARNING: Removing unreachable block (ram,0x00899230) */
/* WARNING: Removing unreachable block (ram,0x00898ef7) */
/* WARNING: Removing unreachable block (ram,0x008985c6) */
/* WARNING: Removing unreachable block (ram,0x0089879c) */
/* WARNING: Removing unreachable block (ram,0x00899280) */
/* WARNING: Removing unreachable block (ram,0x0089831f) */
/* WARNING: Removing unreachable block (ram,0x00898900) */
/* WARNING: Removing unreachable block (ram,0x00899225) */
/* WARNING: Removing unreachable block (ram,0x00898aa7) */
/* WARNING: Removing unreachable block (ram,0x00898819) */
/* WARNING: Removing unreachable block (ram,0x00898de0) */
/* WARNING: Removing unreachable block (ram,0x00898f3e) */
/* WARNING: Removing unreachable block (ram,0x00898461) */
/* WARNING: Removing unreachable block (ram,0x008981e8) */
/* WARNING: Removing unreachable block (ram,0x0089841f) */
/* WARNING: Removing unreachable block (ram,0x008988b9) */
/* WARNING: Removing unreachable block (ram,0x008985d1) */
/* WARNING: Removing unreachable block (ram,0x00898d94) */
/* WARNING: Removing unreachable block (ram,0x00898dab) */
/* WARNING: Removing unreachable block (ram,0x00898382) */
/* WARNING: Removing unreachable block (ram,0x008994e6) */
/* WARNING: Removing unreachable block (ram,0x00898396) */
/* WARNING: Removing unreachable block (ram,0x0089895a) */
/* WARNING: Removing unreachable block (ram,0x00898b40) */
/* WARNING: Removing unreachable block (ram,0x00898b57) */
/* WARNING: Removing unreachable block (ram,0x00898256) */
/* WARNING: Removing unreachable block (ram,0x00898f49) */
/* WARNING: Removing unreachable block (ram,0x00898971) */
/* WARNING: Removing unreachable block (ram,0x0089826a) */
/* WARNING: Removing unreachable block (ram,0x008989d5) */
/* WARNING: Removing unreachable block (ram,0x00898303) */
/* WARNING: Removing unreachable block (ram,0x00898c84) */
/* WARNING: Removing unreachable block (ram,0x00898f02) */
/* WARNING: Removing unreachable block (ram,0x0089860d) */
/* CEquipment::getEquipmentStats() */

wstring_conflict * CEquipment::getEquipmentStats(void)

{
  allocator *paVar1;
  int *piVar2;
  uint *puVar3;
  int iVar4;
  undefined4 *puVar5;
  wstring_conflict *pwVar6;
  char cVar7;
  float *pfVar8;
  CSets *this;
  CSet *pCVar9;
  long *plVar10;
  short *psVar11;
  undefined2 *puVar12;
  short *psVar13;
  uint uVar14;
  undefined8 *puVar15;
  short *psVar16;
  ulong uVar17;
  long lVar18;
  uint *puVar19;
  long lVar20;
  long lVar21;
  long in_RSI;
  wstring_conflict *in_RDI;
  short sVar22;
  int iVar23;
  short sVar24;
  float fVar25;
  short *local_a40;
  uint local_a34;
  undefined8 *local_a18;
  int local_a04;
  short *local_a00;
  undefined2 *local_9f8;
  undefined4 local_9f0;
  undefined8 local_9e8;
  undefined8 local_9e0;
  undefined2 *local_9d8;
  undefined4 local_9d0;
  undefined8 local_9c8;
  undefined8 local_9c0;
  undefined2 *local_9b8;
  undefined4 local_9b0;
  undefined8 local_9a8;
  undefined8 local_9a0;
  short *local_998;
  undefined4 local_990;
  undefined8 local_988;
  undefined8 local_980;
  short *local_978;
  undefined4 local_970;
  undefined8 local_968;
  undefined8 local_960;
  short *local_958;
  undefined4 local_950;
  undefined8 local_948;
  undefined8 local_940;
  undefined2 *local_938;
  undefined4 local_930;
  undefined8 local_928;
  undefined8 local_920;
  short *local_918;
  undefined4 local_910;
  undefined8 local_908;
  undefined8 local_900;
  short *local_8f8;
  int local_8f0;
  undefined8 local_8e8;
  wstring_conflict *local_8e0;
  undefined2 *local_8d8;
  undefined4 local_8d0;
  undefined8 local_8c8;
  undefined8 local_8c0;
  undefined2 *local_8b8;
  undefined4 local_8b0;
  undefined8 local_8a8;
  undefined8 local_8a0;
  undefined2 *local_898;
  undefined4 local_890;
  undefined8 local_888;
  undefined8 local_880;
  undefined2 *local_878;
  undefined4 local_870;
  undefined8 local_868;
  undefined8 local_860;
  undefined2 *local_858;
  undefined4 local_850;
  undefined8 local_848;
  undefined8 local_840;
  undefined2 *local_838;
  undefined4 local_830;
  undefined8 local_828;
  undefined8 local_820;
  undefined2 *local_818 [4];
  undefined2 *local_7f8;
  undefined4 local_7f0;
  undefined8 local_7e8;
  undefined8 local_7e0;
  short *local_7d8;
  int local_7d0;
  undefined8 local_7c8;
  wstring_conflict *local_7c0;
  short *local_7b8;
  undefined4 local_7b0;
  undefined8 local_7a8;
  undefined8 local_7a0;
  short *local_798;
  undefined4 local_790;
  undefined8 local_788;
  undefined8 local_780;
  short *local_778 [4];
  short *local_758;
  undefined4 local_750;
  undefined8 local_748;
  undefined8 local_740;
  short *local_738;
  int local_730;
  undefined8 local_728;
  wstring_conflict *local_720;
  short *local_718;
  undefined4 local_710;
  undefined8 local_708;
  undefined8 local_700;
  short *local_6f8 [4];
  undefined2 *local_6d8;
  undefined4 local_6d0;
  undefined8 local_6c8;
  undefined8 local_6c0;
  undefined2 *local_6b8;
  undefined4 local_6b0;
  undefined8 local_6a8;
  undefined8 local_6a0;
  undefined2 *local_698;
  undefined4 local_690;
  undefined8 local_688;
  undefined8 local_680;
  undefined2 *local_678 [4];
  UTFString local_658 [32];
  undefined2 *local_638;
  undefined4 local_630;
  undefined8 local_628;
  undefined8 local_620;
  short *local_618;
  int local_610;
  undefined8 local_608;
  wstring_conflict *local_600;
  short *local_5f8;
  undefined4 local_5f0;
  undefined8 local_5e8;
  undefined8 local_5e0;
  short *local_5d8 [4];
  UTFString local_5b8 [32];
  undefined2 *local_598;
  undefined4 local_590;
  undefined8 local_588;
  undefined8 local_580;
  uint *local_578 [2];
  wstring_conflict local_568 [16];
  uint *local_558 [2];
  wstring_conflict local_548 [16];
  STRINGS local_538 [16];
  wstring_conflict local_528 [16];
  wstring_conflict local_518 [16];
  wstring_conflict local_508 [16];
  wstring_conflict local_4f8 [16];
  wstring_conflict local_4e8 [16];
  wstring_conflict local_4d8 [16];
  uint *local_4c8 [2];
  wstring_conflict local_4b8 [16];
  STRINGS local_4a8 [16];
  STRINGS local_498 [16];
  wstring_conflict local_488 [16];
  wstring_conflict local_478 [16];
  wstring_conflict local_468 [16];
  uint *local_458 [2];
  wstring_conflict local_448 [16];
  uint *local_438 [2];
  wstring_conflict local_428 [16];
  STRINGS local_418 [16];
  wstring_conflict local_408 [16];
  wstring_conflict local_3f8 [16];
  wstring_conflict local_3e8 [16];
  wstring_conflict local_3d8 [16];
  wstring_conflict local_3c8 [16];
  wstring_conflict local_3b8 [16];
  uint *local_3a8 [2];
  wstring_conflict local_398 [16];
  STRINGS local_388 [16];
  STRINGS local_378 [16];
  wstring_conflict local_368 [16];
  wstring_conflict local_358 [16];
  wstring_conflict local_348 [16];
  wstring_conflict local_338 [16];
  wstring_conflict local_328 [16];
  wstring_conflict local_318 [16];
  wstring_conflict local_308 [16];
  wstring_conflict local_2f8 [16];
  wstring_conflict local_2e8 [16];
  long local_2d8 [2];
  wchar_t *local_2c8 [2];
  wchar_t *local_2b8 [2];
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
  STRINGS local_1e8 [16];
  wstring_conflict local_1d8 [16];
  wstring_conflict local_1c8 [16];
  STRINGS local_1b8 [16];
  wstring_conflict local_1a8 [16];
  wstring_conflict local_198 [16];
  wstring_conflict local_188 [16];
  wstring_conflict local_178 [16];
  wstring_conflict local_168 [16];
  wstring_conflict local_158 [16];
  wstring_conflict local_148 [16];
  STRINGS local_138 [16];
  wstring_conflict local_128 [16];
  wstring_conflict local_118 [16];
  STRINGS local_108 [16];
  wstring_conflict local_f8 [16];
  wstring_conflict local_e8 [16];
  STRINGS local_d8 [16];
  wstring_conflict local_c8 [16];
  wstring_conflict local_b8 [16];
  STRINGS local_a8 [16];
  wstring_conflict local_98 [16];
  wstring_conflict local_88 [16];
  wstring_conflict local_78 [16];
  wstring_conflict local_68 [16];
  wstring_conflict local_58 [26];
  allocator local_3e;
  allocator local_3d;
  allocator local_3c;
  allocator local_3b;
  allocator local_3a;
  allocator local_39 [9];

  *(undefined4 **)in_RDI = &DAT_01424558;
  if ((getEquipmentStats()::g_PhysicalDamage == '\0') &&
     (iVar23 = __cxa_guard_acquire(&getEquipmentStats()::g_PhysicalDamage), iVar23 != 0)) {
    getEquipmentStats()::g_PhysicalDamage = &DAT_01424558;
    __cxa_guard_release(&getEquipmentStats()::g_PhysicalDamage);
    __cxa_atexit(std::wstring::~wstring,&getEquipmentStats()::g_PhysicalDamage,&__dso_handle);
  }
  if (*(long *)(getEquipmentStats()::g_PhysicalDamage + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_58);
                    /* try { // try from 00897b03 to 00897b07 has its CatchHandler @ 00899134 */
    std::wstring::assign((wstring_conflict *)&getEquipmentStats()::g_PhysicalDamage);
                    /* try { // try from 00897b0b to 00897b87 has its CatchHandler @ 008994dc */
    std::wstring::~wstring(local_58);
  }
  if ((getEquipmentStats()::g_Damage == '\0') &&
     (iVar23 = __cxa_guard_acquire(&getEquipmentStats()::g_Damage), iVar23 != 0)) {
    getEquipmentStats()::g_Damage = &DAT_01424558;
    __cxa_guard_release(&getEquipmentStats()::g_Damage);
    __cxa_atexit(std::wstring::~wstring,&getEquipmentStats()::g_Damage,&__dso_handle);
  }
  if (*(long *)(getEquipmentStats()::g_Damage + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_68);
                    /* try { // try from 00897a8c to 00897a90 has its CatchHandler @ 0089912f */
    std::wstring::assign((wstring_conflict *)&getEquipmentStats()::g_Damage);
                    /* try { // try from 00897a94 to 00897afa has its CatchHandler @ 008994dc */
    std::wstring::~wstring(local_68);
  }
  if ((getEquipmentStats()::g_Sockets == '\0') &&
     (iVar23 = __cxa_guard_acquire(&getEquipmentStats()::g_Sockets), iVar23 != 0)) {
    getEquipmentStats()::g_Sockets = &DAT_01424558;
    __cxa_guard_release(&getEquipmentStats()::g_Sockets);
    __cxa_atexit(std::wstring::~wstring,&getEquipmentStats()::g_Sockets,&__dso_handle);
  }
  if (*(long *)(getEquipmentStats()::g_Sockets + -6) == 0) {
                    /* try { // try from 008979f0 to 00897a0c has its CatchHandler @ 008994dc */
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_78);
                    /* try { // try from 00897a15 to 00897a19 has its CatchHandler @ 00898f57 */
    std::wstring::assign((wstring_conflict *)&getEquipmentStats()::g_Sockets);
                    /* try { // try from 00897a1d to 00897a83 has its CatchHandler @ 008994dc */
    std::wstring::~wstring(local_78);
  }
  if ((getEquipmentStats()::g_Set == '\0') &&
     (iVar23 = __cxa_guard_acquire(&getEquipmentStats()::g_Set), iVar23 != 0)) {
    getEquipmentStats()::g_Set = &DAT_01424558;
    __cxa_guard_release(&getEquipmentStats()::g_Set);
    __cxa_atexit(std::wstring::~wstring,&getEquipmentStats()::g_Set,&__dso_handle);
  }
  if (*(long *)(getEquipmentStats()::g_Set + -6) == 0) {
                    /* try { // try from 008936f8 to 00893714 has its CatchHandler @ 008994dc */
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_88);
                    /* try { // try from 0089371d to 00893721 has its CatchHandler @ 008994be */
    std::wstring::assign((wstring_conflict *)&getEquipmentStats()::g_Set);
                    /* try { // try from 00893725 to 0089376f has its CatchHandler @ 008994dc */
    std::wstring::~wstring(local_88);
  }
  cVar7 = CBaseUnit::ISA();
  if (cVar7 != '\0') {
    iVar23 = *(int *)(in_RSI + 0x330);
    if ((0 < iVar23) && (iVar4 = *(int *)(in_RSI + 0x334), 0 < iVar4)) {
      if (iVar23 == iVar4) {
        STRINGS::GetValueAsWString(local_d8,iVar23);
        fVar25 = ceilf((float)*(int *)(in_RSI + 0x334) * DAT_00fa4810);
                    /* try { // try from 00897c1f to 00897c23 has its CatchHandler @ 0089809b */
        STRINGS::GetValueAsWString(local_a8,(int)fVar25);
                    /* try { // try from 00897c39 to 00897c3d has its CatchHandler @ 00898091 */
        std::operator+(local_98,(wchar_t *)&getEquipmentStats()::g_PhysicalDamage);
                    /* try { // try from 00897c4f to 00897c53 has its CatchHandler @ 00898087 */
        std::operator+(local_b8,local_98);
                    /* try { // try from 00897c67 to 00897c6b has its CatchHandler @ 0089807d */
        std::operator+(local_c8,(wchar_t *)local_b8);
                    /* try { // try from 00897c82 to 00897c86 has its CatchHandler @ 0089802a */
        std::operator+(local_e8,local_c8);
                    /* try { // try from 00897c8f to 00897c93 has its CatchHandler @ 00897fee */
        std::wstring::assign(in_RDI);
                    /* try { // try from 00897c97 to 00897c9b has its CatchHandler @ 0089802a */
        std::wstring::~wstring(local_e8);
                    /* try { // try from 00897c9f to 00897ca3 has its CatchHandler @ 0089807d */
        std::wstring::~wstring(local_c8);
                    /* try { // try from 00897ca7 to 00897cab has its CatchHandler @ 00898087 */
        std::wstring::~wstring(local_b8);
                    /* try { // try from 00897caf to 00897cb3 has its CatchHandler @ 00898091 */
        std::wstring::~wstring(local_98);
                    /* try { // try from 00897cb7 to 00897cbb has its CatchHandler @ 0089809b */
        std::wstring::~wstring((wstring_conflict *)local_a8);
                    /* try { // try from 00897cc4 to 00897cc8 has its CatchHandler @ 008994dc */
        std::wstring::~wstring((wstring_conflict *)local_d8);
      }
      else {
        STRINGS::GetValueAsWString(local_138,iVar4);
                    /* try { // try from 00893781 to 00893785 has its CatchHandler @ 00899040 */
        STRINGS::GetValueAsWString(local_108,*(int *)(in_RSI + 0x330));
                    /* try { // try from 0089379b to 0089379f has its CatchHandler @ 0089904a */
        std::operator+(local_f8,(wchar_t *)&getEquipmentStats()::g_PhysicalDamage);
                    /* try { // try from 008937b1 to 008937b5 has its CatchHandler @ 00898f69 */
        std::operator+(local_118,local_f8);
                    /* try { // try from 008937c9 to 008937cd has its CatchHandler @ 00898f90 */
        std::operator+(local_128,(wchar_t *)local_118);
                    /* try { // try from 008937e4 to 008937e8 has its CatchHandler @ 00898f9f */
        std::operator+(local_148,local_128);
                    /* try { // try from 008937f1 to 008937f5 has its CatchHandler @ 00898fae */
        std::wstring::assign(in_RDI);
                    /* try { // try from 008937f9 to 008937fd has its CatchHandler @ 00898f9f */
        std::wstring::~wstring(local_148);
                    /* try { // try from 00893801 to 00893805 has its CatchHandler @ 00898f90 */
        std::wstring::~wstring(local_128);
                    /* try { // try from 00893809 to 0089380d has its CatchHandler @ 00898f69 */
        std::wstring::~wstring(local_118);
                    /* try { // try from 00893811 to 00893815 has its CatchHandler @ 0089904a */
        std::wstring::~wstring(local_f8);
                    /* try { // try from 00893819 to 0089381d has its CatchHandler @ 00899040 */
        std::wstring::~wstring((wstring_conflict *)local_108);
                    /* try { // try from 00893826 to 008938c1 has its CatchHandler @ 008994dc */
        std::wstring::~wstring((wstring_conflict *)local_138);
      }
    }
    if (*(char *)(in_RSI + 0x348) != '\0') {
      lVar18 = *(long *)(in_RSI + 0x358);
      lVar21 = *(long *)(in_RSI + 0x350);
      if (0 < (int)(lVar18 - lVar21 >> 2)) {
        lVar20 = 0;
        iVar23 = 0;
        do {
          iVar4 = *(int *)(*(long *)(in_RSI + 0x380) + lVar20);
          if (iVar4 != 0) {
            fVar25 = ceilf((float)iVar4 * DAT_00fa4810);
            if (*(long *)(*(long *)in_RDI + -0x18) != 0) {
              std::operator+(local_158,(wchar_t *)in_RDI);
                    /* try { // try from 008938cf to 008938d3 has its CatchHandler @ 00898fbf */
              std::wstring::assign(in_RDI);
                    /* try { // try from 008938dc to 008938f0 has its CatchHandler @ 008994dc */
              std::wstring::~wstring(local_158);
            }
            STRINGS::GetValueAsWString(local_1e8,iVar4);
                    /* try { // try from 00893905 to 00893909 has its CatchHandler @ 00898fd6 */
            STRINGS::GetValueAsWString(local_1b8,(int)fVar25);
                    /* try { // try from 0089391d to 00893934 has its CatchHandler @ 00898fed */
            CStringTranslate::getSinglton();
            CStringTranslate::getTranslateString((wchar_t *)local_168);
                    /* try { // try from 0089394a to 0089394e has its CatchHandler @ 0089906b */
            std::operator+(local_178,in_RDI);
                    /* try { // try from 00893964 to 00893968 has its CatchHandler @ 00899082 */
            std::operator+(local_188,(wchar_t *)local_178);
                    /* try { // try from 0089397e to 00893982 has its CatchHandler @ 00899096 */
            std::operator+(local_198,local_188);
                    /* try { // try from 00893998 to 0089399c has its CatchHandler @ 008990aa */
            std::operator+(local_1a8,(wchar_t *)local_198);
                    /* try { // try from 008939b5 to 008939b9 has its CatchHandler @ 008990be */
            std::operator+(local_1c8,local_1a8);
                    /* try { // try from 008939ca to 008939ce has its CatchHandler @ 008990d2 */
            std::operator+(local_1d8,(wchar_t *)local_1c8);
                    /* try { // try from 008939dd to 008939e1 has its CatchHandler @ 008990e6 */
            std::operator+(local_1f8,local_1d8);
                    /* try { // try from 008939ea to 008939ee has its CatchHandler @ 008990f5 */
            std::wstring::assign(in_RDI);
                    /* try { // try from 008939f2 to 008939f6 has its CatchHandler @ 008990e6 */
            std::wstring::~wstring(local_1f8);
                    /* try { // try from 008939fa to 008939fe has its CatchHandler @ 008990d2 */
            std::wstring::~wstring(local_1d8);
                    /* try { // try from 00893a07 to 00893a0b has its CatchHandler @ 008990be */
            std::wstring::~wstring(local_1c8);
                    /* try { // try from 00893a14 to 00893a18 has its CatchHandler @ 008990aa */
            std::wstring::~wstring(local_1a8);
                    /* try { // try from 00893a21 to 00893a25 has its CatchHandler @ 00899096 */
            std::wstring::~wstring(local_198);
                    /* try { // try from 00893a2e to 00893a32 has its CatchHandler @ 00899082 */
            std::wstring::~wstring(local_188);
                    /* try { // try from 00893a3b to 00893a3f has its CatchHandler @ 0089906b */
            std::wstring::~wstring(local_178);
                    /* try { // try from 00893a48 to 00893a4c has its CatchHandler @ 00898fed */
            std::wstring::~wstring(local_168);
                    /* try { // try from 00893a55 to 00893a59 has its CatchHandler @ 00898fd6 */
            std::wstring::~wstring((wstring_conflict *)local_1b8);
                    /* try { // try from 00893a62 to 00893af6 has its CatchHandler @ 008994dc */
            std::wstring::~wstring((wstring_conflict *)local_1e8);
            lVar21 = *(long *)(in_RSI + 0x350);
            lVar18 = *(long *)(in_RSI + 0x358);
          }
          iVar23 = iVar23 + 1;
          lVar20 = lVar20 + 4;
        } while (iVar23 < (int)(lVar18 - lVar21 >> 2));
      }
    }
    lVar21 = *(long *)(in_RSI + 0x2a8);
    if (lVar21 == 0) {
      lVar21 = *(long *)(in_RSI + 0x2a0);
    }
    iVar23 = 0;
    pfVar8 = (float *)&KWeaponSpeedValues;
    do {
      if (*pfVar8 <= DAT_00fa483c * *(float *)(lVar21 + 0x70)) {
        if (*(long *)(*(long *)in_RDI + -0x18) != 0) {
          std::operator+(local_208,(wchar_t *)in_RDI);
                    /* try { // try from 00897b90 to 00897b94 has its CatchHandler @ 008980c6 */
          std::wstring::assign(in_RDI);
                    /* try { // try from 00897b98 to 00897bb1 has its CatchHandler @ 008994dc */
          std::wstring::~wstring(local_208);
        }
        getAttackSpeedString(local_218);
                    /* try { // try from 00897bc5 to 00897bc9 has its CatchHandler @ 008980bf */
        std::operator+(local_228,in_RDI);
                    /* try { // try from 00897bd2 to 00897bd6 has its CatchHandler @ 008980a5 */
        std::wstring::assign(in_RDI);
                    /* try { // try from 00897bda to 00897bde has its CatchHandler @ 008980bf */
        std::wstring::~wstring(local_228);
                    /* try { // try from 00897be2 to 00897bfa has its CatchHandler @ 008994dc */
        std::wstring::~wstring(local_218);
        break;
      }
      iVar23 = iVar23 + 1;
      pfVar8 = pfVar8 + 1;
    } while (iVar23 != 5);
  }
  if (*(int *)(in_RSI + 0x3e0) != 0) {
    if (*(long *)(*(long *)in_RDI + -0x18) != 0) {
      std::operator+(local_238,(wchar_t *)in_RDI);
                    /* try { // try from 00893e77 to 00893e7b has its CatchHandler @ 00898fbd */
      std::wstring::assign(in_RDI);
                    /* try { // try from 00893e7f to 00893e83 has its CatchHandler @ 008994dc */
      std::wstring::~wstring(local_238);
    }
    STRINGS::GetValueAsWString((uint)local_298);
                    /* try { // try from 00893b05 to 00893b09 has its CatchHandler @ 00898eb2 */
    STRINGS::GetValueAsWString((uint)local_268);
                    /* try { // try from 00893b1f to 00893b23 has its CatchHandler @ 00898eab */
    std::operator+(local_248,in_RDI);
                    /* try { // try from 00893b37 to 00893b3b has its CatchHandler @ 00898e83 */
    std::operator+(local_258,(wchar_t *)local_248);
                    /* try { // try from 00893b52 to 00893b56 has its CatchHandler @ 00898e7c */
    std::operator+(local_278,local_258);
                    /* try { // try from 00893b6a to 00893b6e has its CatchHandler @ 00898e75 */
    std::operator+(local_288,(wchar_t *)local_278);
                    /* try { // try from 00893b85 to 00893b89 has its CatchHandler @ 00898e31 */
    std::operator+(local_2a8,local_288);
                    /* try { // try from 00893b92 to 00893b96 has its CatchHandler @ 00899059 */
    std::wstring::assign(in_RDI);
                    /* try { // try from 00893b9a to 00893b9e has its CatchHandler @ 00898e31 */
    std::wstring::~wstring(local_2a8);
                    /* try { // try from 00893ba2 to 00893ba6 has its CatchHandler @ 00898e75 */
    std::wstring::~wstring(local_288);
                    /* try { // try from 00893baa to 00893bae has its CatchHandler @ 00898e7c */
    std::wstring::~wstring(local_278);
                    /* try { // try from 00893bb2 to 00893bb6 has its CatchHandler @ 00898e83 */
    std::wstring::~wstring(local_258);
                    /* try { // try from 00893bba to 00893bbe has its CatchHandler @ 00898eab */
    std::wstring::~wstring(local_248);
                    /* try { // try from 00893bc7 to 00893bcb has its CatchHandler @ 00898eb2 */
    std::wstring::~wstring(local_268);
                    /* try { // try from 00893bd4 to 00893be8 has its CatchHandler @ 008994dc */
    std::wstring::~wstring(local_298);
  }
  getSet();
  if ((getEquipmentStats()::g_SetPieces == '\0') &&
     (iVar23 = __cxa_guard_acquire(&getEquipmentStats()::g_SetPieces), iVar23 != 0)) {
    getEquipmentStats()::g_SetPieces = &DAT_01423a38;
    __cxa_guard_release(&getEquipmentStats()::g_SetPieces);
    __cxa_atexit(std::string::~string,&getEquipmentStats()::g_SetPieces,&__dso_handle);
  }
  if (*(long *)(getEquipmentStats()::g_SetPieces + -0x18) == 0) {
                    /* try { // try from 00893c04 to 00893c20 has its CatchHandler @ 00898e27 */
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_2c8);
                    /* try { // try from 00893c34 to 00893c38 has its CatchHandler @ 00898e15 */
    STRINGS::StringConvertToNarrow((STRINGS *)local_2d8,local_2c8[0]);
                    /* try { // try from 00893c41 to 00893c45 has its CatchHandler @ 00898ee5 */
    std::string::assign((string *)&getEquipmentStats()::g_SetPieces);
    if ((allocator *)(local_2d8[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar2 = (int *)(local_2d8[0] + -8);
      iVar23 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar23 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_2d8[0] + -0x18));
      }
    }
                    /* try { // try from 00893c62 to 00893cf0 has its CatchHandler @ 00898e27 */
    std::wstring::~wstring((wstring_conflict *)local_2c8);
  }
  if ((*(size_t *)(local_2b8[0] + -6) != *(size_t *)(::EMPTY_WSTRING + -6)) ||
     (iVar23 = wmemcmp(local_2b8[0],::EMPTY_WSTRING,*(size_t *)(local_2b8[0] + -6)), iVar23 != 0)) {
    this = (CSets *)CSets::getSingleton();
    pCVar9 = (CSet *)CSets::getSet(this,local_2b8[0]);
    if (pCVar9 != (CSet *)0x0) {
      local_a04 = 0;
      if (*(CInventory **)(in_RSI + 0x240) != (CInventory *)0x0) {
        local_a04 = CInventory::getSetCount(*(CInventory **)(in_RSI + 0x240),pCVar9);
      }
      CGameGlobals::getSingleton();
      std::operator+(local_2e8,(wchar_t *)in_RDI);
                    /* try { // try from 00893d02 to 00893d06 has its CatchHandler @ 00898e8a */
      std::operator+(local_2f8,local_2e8);
                    /* try { // try from 00893d1a to 00893d1e has its CatchHandler @ 00898e9c */
      std::operator+(local_308,local_2f8);
                    /* try { // try from 00893d32 to 00893d36 has its CatchHandler @ 00899001 */
      std::operator+(local_318,(wchar_t *)local_308);
                    /* try { // try from 00893d48 to 00893d4c has its CatchHandler @ 00899013 */
      std::operator+(local_328,local_318);
                    /* try { // try from 00893d60 to 00893d64 has its CatchHandler @ 00899022 */
      std::operator+(local_338,(wchar_t *)local_328);
                    /* try { // try from 00893d6d to 00893d71 has its CatchHandler @ 00899031 */
      std::wstring::assign(in_RDI);
                    /* try { // try from 00893d75 to 00893d79 has its CatchHandler @ 00899022 */
      std::wstring::~wstring(local_338);
                    /* try { // try from 00893d7d to 00893d81 has its CatchHandler @ 00899013 */
      std::wstring::~wstring(local_328);
                    /* try { // try from 00893d85 to 00893d89 has its CatchHandler @ 00899001 */
      std::wstring::~wstring(local_318);
                    /* try { // try from 00893d8d to 00893d91 has its CatchHandler @ 00898e9c */
      std::wstring::~wstring(local_308);
                    /* try { // try from 00893d95 to 00893d99 has its CatchHandler @ 00898e8a */
      std::wstring::~wstring(local_2f8);
                    /* try { // try from 00893d9d to 00893da1 has its CatchHandler @ 00898e27 */
      std::wstring::~wstring(local_2e8);
      if (local_a04 < 1) {
        uVar14 = *(uint *)(pCVar9 + 0x10);
      }
      else {
        if (*(int *)(pCVar9 + 0x10) == 0) goto LAB_00893e31;
        local_a34 = 0;
        do {
          if (local_a34 < *(uint *)(pCVar9 + 0x14)) {
            plVar10 = (long *)((ulong)local_a34 * 8 + *(long *)(pCVar9 + 8));
          }
          else {
            plVar10 = *(long **)(pCVar9 + 8);
          }
          puVar15 = (undefined8 *)*plVar10;
          if (*(int *)((long)puVar15 + 0x14) <= local_a04) {
                    /* try { // try from 00893e9e to 00893ea2 has its CatchHandler @ 00898e27 */
            CAffix::getDisplayStats((CAffix *)local_458,(uint)*puVar15);
                    /* try { // try from 00893eb8 to 00893ebc has its CatchHandler @ 00899054 */
            std::wstring::wstring(local_368,L"\\n",&local_3a);
                    /* try { // try from 00893ed2 to 00893ed6 has its CatchHandler @ 00899104 */
            std::wstring::wstring(local_358,L"\n",local_39);
                    /* try { // try from 00893ee7 to 00893eeb has its CatchHandler @ 0089911b */
            std::wstring::wstring(local_348,(wstring_conflict *)local_458);
                    /* try { // try from 00893f0c to 00893f10 has its CatchHandler @ 00899139 */
            STRINGS::replaceWString(local_378,local_348,local_358,local_368);
                    /* try { // try from 00893f21 to 00893f25 has its CatchHandler @ 0089914d */
            std::wstring::assign((wstring_conflict *)local_458);
                    /* try { // try from 00893f2e to 00893f32 has its CatchHandler @ 00899139 */
            std::wstring::~wstring((wstring_conflict *)local_378);
                    /* try { // try from 00893f3b to 00893f3f has its CatchHandler @ 0089911b */
            std::wstring::~wstring(local_348);
                    /* try { // try from 00893f48 to 00893f4c has its CatchHandler @ 00899104 */
            std::wstring::~wstring(local_358);
                    /* try { // try from 00893f55 to 00893f59 has its CatchHandler @ 00899054 */
            std::wstring::~wstring(local_368);
            local_5f8 = &DAT_01426458;
            local_5e0 = 0;
            local_5f0 = 0;
            local_5e8 = 0;
            local_578[0] = &DAT_01424558;
            wcslen(L" : ");
                    /* try { // try from 00893fbc to 008940e6 has its CatchHandler @ 0089928b */
            std::wstring::assign((wchar_t *)local_578,0xfd0b80);
            std::
            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
            ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                         *)&local_5f8,0,*(ulong *)(local_5f8 + -0xc),0);
            std::
            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
            ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                       *)&local_5f8,*(ulong *)(local_578[0] + -6));
            puVar3 = local_578[0] + *(long *)(local_578[0] + -6);
            if (local_578[0] != puVar3) {
              sVar24 = 0;
              puVar19 = local_578[0];
              do {
                uVar14 = *puVar19;
                lVar21 = 1;
                sVar22 = (short)uVar14;
                if (0xffff < uVar14) {
                  lVar21 = 2;
                  sVar24 = ((ushort)(uVar14 - 0x10000) & 0x3ff) + 0xdc00;
                  sVar22 = ((ushort)(uVar14 - 0x10000 >> 10) & 0x3ff) + 0xd800;
                }
                lVar18 = *(long *)(local_5f8 + -0xc);
                uVar17 = lVar18 + 1;
                if ((*(ulong *)(local_5f8 + -8) < uVar17) || (0 < *(int *)(local_5f8 + -4))) {
                  std::
                  basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                  ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             *)&local_5f8,uVar17);
                  lVar18 = *(long *)(local_5f8 + -0xc);
                }
                local_5f8[lVar18] = sVar22;
                if (local_5f8 != &DAT_01426458) {
                  local_5f8[-4] = 0;
                  local_5f8[-3] = 0;
                  *(ulong *)(local_5f8 + -0xc) = uVar17;
                  local_5f8[uVar17] = 0;
                }
                if (lVar21 == 2) {
                  lVar21 = *(long *)(local_5f8 + -0xc);
                  uVar17 = lVar21 + 1;
                  if ((*(ulong *)(local_5f8 + -8) < uVar17) || (0 < *(int *)(local_5f8 + -4))) {
                    std::
                    basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                    ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                               *)&local_5f8,uVar17);
                    lVar21 = *(long *)(local_5f8 + -0xc);
                  }
                  local_5f8[lVar21] = sVar24;
                  if (local_5f8 != &DAT_01426458) {
                    local_5f8[-4] = 0;
                    local_5f8[-3] = 0;
                    *(ulong *)(local_5f8 + -0xc) = uVar17;
                    local_5f8[uVar17] = 0;
                  }
                }
                puVar19 = puVar19 + 1;
              } while (puVar3 != puVar19);
            }
                    /* try { // try from 00894127 to 0089412b has its CatchHandler @ 0089803b */
            std::wstring::~wstring((wstring_conflict *)local_578);
                    /* try { // try from 00894139 to 0089413d has its CatchHandler @ 00898884 */
            Ogre::UTFString::UTFString(local_5b8,(string *)&getEquipmentStats()::g_SetPieces);
                    /* try { // try from 0089414e to 00894152 has its CatchHandler @ 00898031 */
            STRINGS::GetValueAsWString(local_388,*(int *)((long)puVar15 + 0x14));
                    /* try { // try from 00894168 to 0089416c has its CatchHandler @ 00898073 */
            std::operator+((wchar_t *)local_398,(wstring_conflict *)&DAT_00fd0b90);
                    /* try { // try from 00894182 to 00894186 has its CatchHandler @ 00897f8a */
            std::operator+((wstring_conflict *)local_3a8,(wchar_t *)local_398);
            local_598 = &DAT_01426458;
            local_580 = 0;
            local_590 = 0;
            local_588 = 0;
                    /* try { // try from 008941d2 to 008942d4 has its CatchHandler @ 0089804f */
            std::
            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
            ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                         *)&local_598,0,
                        std::
                        basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                        ::_Rep::_S_empty_rep_storage,0);
            std::
            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
            ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                       *)&local_598,*(ulong *)(local_3a8[0] + -6));
            puVar3 = local_3a8[0] + *(long *)(local_3a8[0] + -6);
            if (local_3a8[0] != puVar3) {
              sVar24 = 0;
              puVar19 = local_3a8[0];
              do {
                uVar14 = *puVar19;
                lVar21 = 1;
                sVar22 = (short)uVar14;
                if (0xffff < uVar14) {
                  lVar21 = 2;
                  sVar24 = ((ushort)(uVar14 - 0x10000) & 0x3ff) + 0xdc00;
                  sVar22 = ((ushort)(uVar14 - 0x10000 >> 10) & 0x3ff) + 0xd800;
                }
                lVar18 = *(long *)(local_598 + -0xc);
                uVar17 = lVar18 + 1;
                if ((*(ulong *)(local_598 + -8) < uVar17) || (0 < *(int *)(local_598 + -4))) {
                  std::
                  basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                  ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             *)&local_598,uVar17);
                  lVar18 = *(long *)(local_598 + -0xc);
                }
                local_598[lVar18] = sVar22;
                if (local_598 != &DAT_01426458) {
                  *(undefined4 *)(local_598 + -4) = 0;
                  *(ulong *)(local_598 + -0xc) = uVar17;
                  local_598[uVar17] = 0;
                }
                if (lVar21 == 2) {
                  lVar21 = *(long *)(local_598 + -0xc);
                  uVar17 = lVar21 + 1;
                  if ((*(ulong *)(local_598 + -8) < uVar17) || (0 < *(int *)(local_598 + -4))) {
                    std::
                    basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                    ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                               *)&local_598,uVar17);
                    lVar21 = *(long *)(local_598 + -0xc);
                  }
                  local_598[lVar21] = sVar24;
                  if (local_598 != &DAT_01426458) {
                    *(undefined4 *)(local_598 + -4) = 0;
                    *(ulong *)(local_598 + -0xc) = uVar17;
                    local_598[uVar17] = 0;
                  }
                }
                puVar19 = puVar19 + 1;
              } while (puVar3 != puVar19);
            }
                    /* try { // try from 00894325 to 00894329 has its CatchHandler @ 00899276 */
            Ogre::operator+((Ogre *)local_5d8,(UTFString *)&local_598,local_5b8);
            local_918 = &DAT_01426458;
            local_900 = 0;
            local_910 = 0;
            local_908 = 0;
            psVar13 = local_918;
            if (local_5d8[0] != &DAT_01426458) {
              if (*(int *)(local_5d8[0] + -4) < 0) {
                    /* try { // try from 008958ec to 008958f0 has its CatchHandler @ 0089846f */
                psVar13 = (short *)std::
                                   basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                                   ::_Rep::_M_clone((_Rep *)(local_5d8[0] + -0xc),
                                                    (allocator *)local_578,0);
                psVar11 = local_918 + -0xc;
              }
              else {
                if ((_Rep *)(local_5d8[0] + -0xc) !=
                    (_Rep *)&std::
                             basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             ::_Rep::_S_empty_rep_storage) {
                  LOCK();
                  *(int *)(local_5d8[0] + -4) = *(int *)(local_5d8[0] + -4) + 1;
                  UNLOCK();
                }
                psVar11 = (short *)&std::
                                    basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                                    ::_Rep::_S_empty_rep_storage;
                psVar13 = local_5d8[0];
              }
              if ((ulong *)psVar11 !=
                  &std::
                   basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                   ::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar2 = (int *)(psVar11 + 8);
                iVar23 = *piVar2;
                *piVar2 = *piVar2 + -1;
                UNLOCK();
                if (iVar23 < 1) {
                  operator_delete(psVar11);
                }
              }
            }
            local_918 = psVar13;
            lVar21 = *(long *)(local_5f8 + -0xc);
            if (lVar21 != 0) {
              lVar18 = *(long *)(local_918 + -0xc);
              uVar17 = lVar18 + lVar21;
              if ((*(ulong *)(local_918 + -8) < uVar17) || (0 < *(int *)(local_918 + -4))) {
                    /* try { // try from 008943ea to 008943ee has its CatchHandler @ 00899175 */
                std::
                basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                           *)&local_918,uVar17);
                lVar18 = *(long *)(local_918 + -0xc);
              }
              if (lVar21 == 1) {
                local_918[lVar18] = *local_5f8;
              }
              else {
                memmove(local_918 + lVar18,local_5f8,lVar21 * 2);
              }
              if (local_918 != &DAT_01426458) {
                local_918[-4] = 0;
                local_918[-3] = 0;
                *(ulong *)(local_918 + -0xc) = uVar17;
                local_918[uVar17] = 0;
              }
            }
            local_618 = &DAT_01426458;
            local_600 = (wstring_conflict *)0x0;
            local_610 = 0;
            local_608 = 0;
            psVar13 = local_618;
            if (local_918 != &DAT_01426458) {
              if (*(int *)(local_918 + -4) < 0) {
                    /* try { // try from 008958a7 to 008958ab has its CatchHandler @ 00898cc4 */
                psVar13 = (short *)std::
                                   basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                                   ::_Rep::_M_clone((_Rep *)(local_918 + -0xc),
                                                    (allocator *)local_578,0);
                psVar11 = local_618 + -0xc;
              }
              else {
                if ((_Rep *)(local_918 + -0xc) !=
                    (_Rep *)&std::
                             basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             ::_Rep::_S_empty_rep_storage) {
                  LOCK();
                  *(int *)(local_918 + -4) = *(int *)(local_918 + -4) + 1;
                  UNLOCK();
                }
                psVar11 = (short *)&std::
                                    basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                                    ::_Rep::_S_empty_rep_storage;
                psVar13 = local_918;
              }
              if ((ulong *)psVar11 !=
                  &std::
                   basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                   ::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar2 = (int *)(psVar11 + 8);
                iVar23 = *piVar2;
                *piVar2 = *piVar2 + -1;
                UNLOCK();
                if (iVar23 < 1) {
                  operator_delete(psVar11);
                }
              }
            }
            local_618 = psVar13;
            Ogre::UTFString::~UTFString((UTFString *)&local_918);
            pwVar6 = local_600;
            if (local_610 != 2) {
              if (local_600 != (wstring_conflict *)0x0) {
                if (local_610 == 3) {
                  if (local_600 != (wstring_conflict *)0x0) {
                    puVar12 = (undefined2 *)(*(long *)local_600 + -0x18);
                    if (puVar12 !=
                        &std::
                         basic_string<unsigned_int,std::char_traits<unsigned_int>,std::allocator<unsigned_int>>
                         ::_Rep::_S_empty_rep_storage) {
                      LOCK();
                      piVar2 = (int *)(*(long *)local_600 + -8);
                      iVar23 = *piVar2;
                      *piVar2 = *piVar2 + -1;
                      UNLOCK();
                      if (iVar23 < 1) {
                        operator_delete(puVar12);
                      }
                    }
                    goto LAB_00895991;
                  }
                }
                else if ((local_610 == 1) && (local_600 != (wstring_conflict *)0x0)) {
                  paVar1 = (allocator *)(*(long *)local_600 + -0x18);
                  if (paVar1 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                    LOCK();
                    piVar2 = (int *)(*(long *)local_600 + -8);
                    iVar23 = *piVar2;
                    *piVar2 = *piVar2 + -1;
                    UNLOCK();
                    if (iVar23 < 1) {
                      std::string::_Rep::_M_destroy(paVar1);
                    }
                  }
LAB_00895991:
                  operator_delete(pwVar6);
                }
                local_600 = (wstring_conflict *)0x0;
                local_608 = 0;
              }
                    /* try { // try from 00895732 to 00895736 has its CatchHandler @ 0089933a */
              local_600 = operator_new(8);
              *(undefined4 **)local_600 = &DAT_01424558;
              local_610 = 2;
            }
                    /* try { // try from 008944d4 to 00894777 has its CatchHandler @ 0089933a */
            std::wstring::_M_mutate((ulong)local_600,0,*(ulong *)(*(long *)local_600 + -0x18));
            pwVar6 = local_600;
            std::wstring::reserve((ulong)local_600);
            psVar13 = local_618 + -0xc;
            if (*(int *)(local_618 + -4) < 0) {
              psVar13 = local_618 + *(long *)(local_618 + -0xc);
            }
            else if ((ulong *)psVar13 ==
                     &std::
                      basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                      ::_Rep::_S_empty_rep_storage) {
              psVar13 = local_618 +
                        std::
                        basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                        ::_Rep::_S_empty_rep_storage;
            }
            else {
              if (*(int *)(local_618 + -4) != 0) {
                std::
                basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             *)&local_618,0,0,0);
                psVar13 = local_618 + -0xc;
              }
              psVar13[8] = -1;
              psVar13[9] = -1;
              psVar11 = local_618 + -0xc;
              psVar13 = local_618 + *(long *)(local_618 + -0xc);
              if ((-1 < *(int *)(local_618 + -4)) &&
                 ((ulong *)psVar11 !=
                  &std::
                   basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                   ::_Rep::_S_empty_rep_storage)) {
                if (*(int *)(local_618 + -4) != 0) {
                  std::
                  basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                  ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                               *)&local_618,0,0,0);
                  psVar11 = local_618 + -0xc;
                }
                psVar11[8] = -1;
                psVar11[9] = -1;
              }
            }
            if (psVar13 != local_618) {
              plVar10 = (long *)(local_618 + -0xc);
              psVar11 = local_618;
              do {
                if ((-1 < (int)plVar10[2]) &&
                   ((ulong *)plVar10 !=
                    &std::
                     basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                     ::_Rep::_S_empty_rep_storage)) {
                  if ((int)plVar10[2] != 0) {
                    std::
                    basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                    ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                                 *)&local_618,0,0,0);
                    plVar10 = (long *)(local_618 + -0xc);
                  }
                  *(undefined4 *)(plVar10 + 2) = 0xffffffff;
                }
                lVar21 = (long)psVar11 - (long)local_618 >> 1;
                uVar14 = (ushort)local_618[lVar21] + 0x2800;
                if ((((ushort)uVar14 < 0x400) &&
                    (uVar17 = lVar21 + 1, uVar17 < *(ulong *)(local_618 + -0xc))) &&
                   ((ushort)(local_618[uVar17] + 0x2400U) < 0x400)) {
                  uVar14 = ((ushort)(local_618[uVar17] + 0x2400U) & 0x3ff | (uVar14 & 0x3ff) << 10)
                           + 0x10000;
                }
                else {
                  uVar14 = (uint)(ushort)local_618[lVar21];
                }
                lVar21 = *(long *)pwVar6;
                lVar18 = *(long *)(lVar21 + -0x18);
                uVar17 = lVar18 + 1;
                if ((*(ulong *)(lVar21 + -0x10) < uVar17) || (0 < *(int *)(lVar21 + -8))) {
                  std::wstring::reserve((ulong)pwVar6);
                  lVar21 = *(long *)pwVar6;
                  lVar18 = *(long *)(lVar21 + -0x18);
                }
                *(uint *)(lVar21 + lVar18 * 4) = uVar14;
                puVar5 = *(undefined4 **)pwVar6;
                if (puVar5 != &DAT_01424558) {
                  puVar5[-2] = 0;
                  *(ulong *)(puVar5 + -6) = uVar17;
                  puVar5[uVar17] = 0;
                }
                plVar10 = (long *)(local_618 + -0xc);
                if ((-1 < *(int *)(local_618 + -4)) &&
                   ((ulong *)plVar10 !=
                    &std::
                     basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                     ::_Rep::_S_empty_rep_storage)) {
                  if (*(int *)(local_618 + -4) != 0) {
                    std::
                    basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                    ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                                 *)&local_618,0,0,0);
                    plVar10 = (long *)(local_618 + -0xc);
                  }
                  *(undefined4 *)(plVar10 + 2) = 0xffffffff;
                  plVar10 = (long *)(local_618 + -0xc);
                }
                psVar16 = psVar11 + 1;
                if (((psVar16 != local_618 + *plVar10) && ((ushort)(psVar11[1] + 0x2400U) < 0x400))
                   && ((ushort)(*psVar11 + 0x2800U) < 0x400)) {
                  psVar16 = psVar11 + 2;
                }
                psVar11 = psVar16;
              } while (psVar16 != psVar13);
            }
            std::wstring::wstring(local_3d8,local_600);
                    /* try { // try from 00894790 to 00894794 has its CatchHandler @ 0089931e */
            std::wstring::wstring(local_3c8,L"\\n",&local_3b);
                    /* try { // try from 008947a8 to 008947ac has its CatchHandler @ 00899330 */
            std::wstring::wstring(local_3b8,(wstring_conflict *)local_458);
                    /* try { // try from 008947c1 to 008947c5 has its CatchHandler @ 008992a2 */
            STRINGS::replaceWString((STRINGS *)local_3e8,local_3b8,local_3c8,local_3d8);
                    /* try { // try from 008947d1 to 008947d5 has its CatchHandler @ 008992d4 */
            std::wstring::assign((wstring_conflict *)local_458);
                    /* try { // try from 008947d9 to 008947dd has its CatchHandler @ 008992a2 */
            std::wstring::~wstring(local_3e8);
                    /* try { // try from 008947e1 to 008947e5 has its CatchHandler @ 00899330 */
            std::wstring::~wstring(local_3b8);
                    /* try { // try from 008947e9 to 008947ed has its CatchHandler @ 0089931e */
            std::wstring::~wstring(local_3c8);
                    /* try { // try from 008947f9 to 008947fd has its CatchHandler @ 0089933a */
            std::wstring::~wstring(local_3d8);
            pwVar6 = local_600;
            if (local_600 != (wstring_conflict *)0x0) {
              if (local_610 == 2) {
                if (local_600 != (wstring_conflict *)0x0) {
                    /* try { // try from 00895864 to 00895868 has its CatchHandler @ 00898c9f */
                  std::wstring::~wstring(local_600);
                  goto LAB_008957f8;
                }
              }
              else if (local_610 == 3) {
                if (local_600 != (wstring_conflict *)0x0) {
                  puVar12 = (undefined2 *)(*(long *)local_600 + -0x18);
                  if (puVar12 !=
                      &std::
                       basic_string<unsigned_int,std::char_traits<unsigned_int>,std::allocator<unsigned_int>>
                       ::_Rep::_S_empty_rep_storage) {
                    LOCK();
                    piVar2 = (int *)(*(long *)local_600 + -8);
                    iVar23 = *piVar2;
                    *piVar2 = *piVar2 + -1;
                    UNLOCK();
                    if (iVar23 < 1) {
                      operator_delete(puVar12);
                    }
                  }
                  goto LAB_008957f8;
                }
              }
              else if ((local_610 == 1) && (local_600 != (wstring_conflict *)0x0)) {
                paVar1 = (allocator *)(*(long *)local_600 + -0x18);
                if (paVar1 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                  LOCK();
                  piVar2 = (int *)(*(long *)local_600 + -8);
                  iVar23 = *piVar2;
                  *piVar2 = *piVar2 + -1;
                  UNLOCK();
                  if (iVar23 < 1) {
                    std::string::_Rep::_M_destroy(paVar1);
                  }
                }
LAB_008957f8:
                operator_delete(pwVar6);
              }
              local_600 = (wstring_conflict *)0x0;
              local_608 = 0;
            }
            if ((ulong *)(local_618 + -0xc) !=
                &std::
                 basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                 ::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar2 = (int *)(local_618 + -4);
              iVar23 = *piVar2;
              *piVar2 = *piVar2 + -1;
              UNLOCK();
              if (iVar23 < 1) {
                operator_delete(local_618 + -0xc);
              }
            }
            Ogre::UTFString::~UTFString((UTFString *)local_5d8);
            Ogre::UTFString::~UTFString((UTFString *)&local_598);
                    /* try { // try from 0089487f to 00894883 has its CatchHandler @ 00897f8a */
            std::wstring::~wstring((wstring_conflict *)local_3a8);
                    /* try { // try from 0089488c to 00894890 has its CatchHandler @ 00898073 */
            std::wstring::~wstring(local_398);
                    /* try { // try from 00894899 to 0089489d has its CatchHandler @ 00898031 */
            std::wstring::~wstring((wstring_conflict *)local_388);
            Ogre::UTFString::~UTFString(local_5b8);
            Ogre::UTFString::~UTFString((UTFString *)&local_5f8);
            local_718 = &DAT_01426458;
            local_700 = 0;
            local_710 = 0;
            local_708 = 0;
            local_578[0] = &DAT_01424558;
            wcslen(L"|u");
                    /* try { // try from 00894917 to 00894a44 has its CatchHandler @ 00899307 */
            std::wstring::assign((wchar_t *)local_578,0xfc8340);
            std::
            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
            ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                         *)&local_718,0,*(ulong *)(local_718 + -0xc),0);
            std::
            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
            ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                       *)&local_718,*(ulong *)(local_578[0] + -6));
            puVar3 = local_578[0] + *(long *)(local_578[0] + -6);
            if (local_578[0] != puVar3) {
              sVar24 = 0;
              puVar19 = local_578[0];
              do {
                uVar14 = *puVar19;
                lVar21 = 1;
                if (0xffff < uVar14) {
                  lVar21 = 2;
                  sVar24 = ((ushort)(uVar14 - 0x10000) & 0x3ff) + 0xdc00;
                  uVar14 = (uint)(ushort)(((ushort)(uVar14 - 0x10000 >> 10) & 0x3ff) + 0xd800);
                }
                lVar18 = *(long *)(local_718 + -0xc);
                uVar17 = lVar18 + 1;
                if ((*(ulong *)(local_718 + -8) < uVar17) || (0 < *(int *)(local_718 + -4))) {
                  std::
                  basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                  ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             *)&local_718,uVar17);
                  lVar18 = *(long *)(local_718 + -0xc);
                }
                local_718[lVar18] = (short)uVar14;
                if (local_718 != &DAT_01426458) {
                  local_718[-4] = 0;
                  local_718[-3] = 0;
                  *(ulong *)(local_718 + -0xc) = uVar17;
                  local_718[uVar17] = 0;
                }
                if (lVar21 == 2) {
                  lVar21 = *(long *)(local_718 + -0xc);
                  uVar17 = lVar21 + 1;
                  if ((*(ulong *)(local_718 + -8) < uVar17) || (0 < *(int *)(local_718 + -4))) {
                    std::
                    basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                    ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                               *)&local_718,uVar17);
                    lVar21 = *(long *)(local_718 + -0xc);
                  }
                  local_718[lVar21] = sVar24;
                  if (local_718 != &DAT_01426458) {
                    local_718[-4] = 0;
                    local_718[-3] = 0;
                    *(ulong *)(local_718 + -0xc) = uVar17;
                    local_718[uVar17] = 0;
                  }
                }
                puVar19 = puVar19 + 1;
              } while (puVar3 != puVar19);
            }
                    /* try { // try from 00894a82 to 00894a86 has its CatchHandler @ 0089877e */
            std::wstring::~wstring((wstring_conflict *)local_578);
            local_6d8 = &DAT_01426458;
            local_6c0 = 0;
            local_6d0 = 0;
            local_6c8 = 0;
                    /* try { // try from 00894ac9 to 00894bda has its CatchHandler @ 0089871c */
            std::
            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
            ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                         *)&local_6d8,0,
                        std::
                        basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                        ::_Rep::_S_empty_rep_storage,0);
            std::
            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
            ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                       *)&local_6d8,*(ulong *)(local_458[0] + -6));
            puVar3 = local_458[0] + *(long *)(local_458[0] + -6);
            if (local_458[0] != puVar3) {
              sVar24 = 0;
              puVar19 = local_458[0];
              do {
                uVar14 = *puVar19;
                lVar21 = 1;
                if (0xffff < uVar14) {
                  lVar21 = 2;
                  sVar24 = ((ushort)(uVar14 - 0x10000) & 0x3ff) + 0xdc00;
                  uVar14 = (uint)(ushort)(((ushort)(uVar14 - 0x10000 >> 10) & 0x3ff) + 0xd800);
                }
                lVar18 = *(long *)(local_6d8 + -0xc);
                uVar17 = lVar18 + 1;
                if ((*(ulong *)(local_6d8 + -8) < uVar17) || (0 < *(int *)(local_6d8 + -4))) {
                  std::
                  basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                  ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             *)&local_6d8,uVar17);
                  lVar18 = *(long *)(local_6d8 + -0xc);
                }
                local_6d8[lVar18] = (short)uVar14;
                if (local_6d8 != &DAT_01426458) {
                  *(undefined4 *)(local_6d8 + -4) = 0;
                  *(ulong *)(local_6d8 + -0xc) = uVar17;
                  local_6d8[uVar17] = 0;
                }
                if (lVar21 == 2) {
                  lVar21 = *(long *)(local_6d8 + -0xc);
                  uVar17 = lVar21 + 1;
                  if ((*(ulong *)(local_6d8 + -8) < uVar17) || (0 < *(int *)(local_6d8 + -4))) {
                    std::
                    basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                    ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                               *)&local_6d8,uVar17);
                    lVar21 = *(long *)(local_6d8 + -0xc);
                  }
                  local_6d8[lVar21] = sVar24;
                  if (local_6d8 != &DAT_01426458) {
                    *(undefined4 *)(local_6d8 + -4) = 0;
                    *(ulong *)(local_6d8 + -0xc) = uVar17;
                    local_6d8[uVar17] = 0;
                  }
                }
                puVar19 = puVar19 + 1;
              } while (puVar3 != puVar19);
            }
            local_698 = &DAT_01426458;
            local_680 = 0;
            local_690 = 0;
            local_688 = 0;
            local_578[0] = &DAT_01424558;
            wcslen(L" : ");
                    /* try { // try from 00894c72 to 00894d92 has its CatchHandler @ 00898898 */
            std::wstring::assign((wchar_t *)local_578,0xfd0b80);
            std::
            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
            ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                         *)&local_698,0,*(ulong *)(local_698 + -0xc),0);
            std::
            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
            ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                       *)&local_698,*(ulong *)(local_578[0] + -6));
            puVar3 = local_578[0] + *(long *)(local_578[0] + -6);
            if (local_578[0] != puVar3) {
              sVar24 = 0;
              puVar19 = local_578[0];
              do {
                uVar14 = *puVar19;
                lVar21 = 1;
                if (0xffff < uVar14) {
                  lVar21 = 2;
                  sVar24 = ((ushort)(uVar14 - 0x10000) & 0x3ff) + 0xdc00;
                  uVar14 = (uint)(ushort)(((ushort)(uVar14 - 0x10000 >> 10) & 0x3ff) + 0xd800);
                }
                lVar18 = *(long *)(local_698 + -0xc);
                uVar17 = lVar18 + 1;
                if ((*(ulong *)(local_698 + -8) < uVar17) || (0 < *(int *)(local_698 + -4))) {
                  std::
                  basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                  ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             *)&local_698,uVar17);
                  lVar18 = *(long *)(local_698 + -0xc);
                }
                local_698[lVar18] = (short)uVar14;
                if (local_698 != &DAT_01426458) {
                  *(undefined4 *)(local_698 + -4) = 0;
                  *(ulong *)(local_698 + -0xc) = uVar17;
                  local_698[uVar17] = 0;
                }
                if (lVar21 == 2) {
                  lVar21 = *(long *)(local_698 + -0xc);
                  uVar17 = lVar21 + 1;
                  if ((*(ulong *)(local_698 + -8) < uVar17) || (0 < *(int *)(local_698 + -4))) {
                    std::
                    basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                    ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                               *)&local_698,uVar17);
                    lVar21 = *(long *)(local_698 + -0xc);
                  }
                  local_698[lVar21] = sVar24;
                  if (local_698 != &DAT_01426458) {
                    *(undefined4 *)(local_698 + -4) = 0;
                    *(ulong *)(local_698 + -0xc) = uVar17;
                    local_698[uVar17] = 0;
                  }
                }
                puVar19 = puVar19 + 1;
              } while (puVar3 != puVar19);
            }
                    /* try { // try from 00894dd0 to 00894dd4 has its CatchHandler @ 008986a7 */
            std::wstring::~wstring((wstring_conflict *)local_578);
                    /* try { // try from 00894de2 to 00894de6 has its CatchHandler @ 00899161 */
            Ogre::UTFString::UTFString(local_658,(string *)&getEquipmentStats()::g_SetPieces);
                    /* try { // try from 00894df7 to 00894dfb has its CatchHandler @ 0089916b */
            STRINGS::GetValueAsWString(local_418,*(int *)((long)puVar15 + 0x14));
                    /* try { // try from 00894dfc to 00894e1e has its CatchHandler @ 00898754 */
            CGameGlobals::getSingleton();
            std::operator+(local_3f8,(wchar_t *)in_RDI);
                    /* try { // try from 00894e32 to 00894e36 has its CatchHandler @ 00898712 */
            std::operator+(local_408,local_3f8);
                    /* try { // try from 00894e4f to 00894e53 has its CatchHandler @ 008988af */
            std::operator+(local_428,local_408);
                    /* try { // try from 00894e69 to 00894e6d has its CatchHandler @ 0089888e */
            std::operator+((wstring_conflict *)local_438,(wchar_t *)local_428);
            local_638 = &DAT_01426458;
            local_620 = 0;
            local_630 = 0;
            local_628 = 0;
                    /* try { // try from 00894eb0 to 00894fb2 has its CatchHandler @ 00898733 */
            std::
            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
            ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                         *)&local_638,0,
                        std::
                        basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                        ::_Rep::_S_empty_rep_storage,0);
            std::
            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
            ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                       *)&local_638,*(ulong *)(local_438[0] + -6));
            puVar3 = local_438[0] + *(long *)(local_438[0] + -6);
            if (local_438[0] != puVar3) {
              sVar24 = 0;
              puVar19 = local_438[0];
              do {
                uVar14 = *puVar19;
                lVar21 = 1;
                if (0xffff < uVar14) {
                  lVar21 = 2;
                  sVar24 = ((ushort)(uVar14 - 0x10000) & 0x3ff) + 0xdc00;
                  uVar14 = (uint)(ushort)(((ushort)(uVar14 - 0x10000 >> 10) & 0x3ff) + 0xd800);
                }
                lVar18 = *(long *)(local_638 + -0xc);
                uVar17 = lVar18 + 1;
                if ((*(ulong *)(local_638 + -8) < uVar17) || (0 < *(int *)(local_638 + -4))) {
                  std::
                  basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                  ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             *)&local_638,uVar17);
                  lVar18 = *(long *)(local_638 + -0xc);
                }
                local_638[lVar18] = (short)uVar14;
                if (local_638 != &DAT_01426458) {
                  *(undefined4 *)(local_638 + -4) = 0;
                  *(ulong *)(local_638 + -0xc) = uVar17;
                  local_638[uVar17] = 0;
                }
                if (lVar21 == 2) {
                  lVar21 = *(long *)(local_638 + -0xc);
                  uVar17 = lVar21 + 1;
                  if ((*(ulong *)(local_638 + -8) < uVar17) || (0 < *(int *)(local_638 + -4))) {
                    std::
                    basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                    ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                               *)&local_638,uVar17);
                    lVar21 = *(long *)(local_638 + -0xc);
                  }
                  local_638[lVar21] = sVar24;
                  if (local_638 != &DAT_01426458) {
                    *(undefined4 *)(local_638 + -4) = 0;
                    *(ulong *)(local_638 + -0xc) = uVar17;
                    local_638[uVar17] = 0;
                  }
                }
                puVar19 = puVar19 + 1;
              } while (puVar3 != puVar19);
            }
                    /* try { // try from 00895000 to 00895004 has its CatchHandler @ 0089874a */
            Ogre::operator+((Ogre *)local_678,(UTFString *)&local_638,local_658);
            local_938 = &DAT_01426458;
            local_920 = 0;
            local_930 = 0;
            local_928 = 0;
            puVar12 = local_938;
            if (local_678[0] != &DAT_01426458) {
              if (*(int *)(local_678[0] + -4) < 0) {
                    /* try { // try from 00895911 to 00895915 has its CatchHandler @ 008984a0 */
                puVar12 = (undefined2 *)
                          std::
                          basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                          ::_Rep::_M_clone((_Rep *)(local_678[0] + -0xc),(allocator *)local_578,0);
                puVar15 = (undefined8 *)(local_938 + -0xc);
              }
              else {
                if ((_Rep *)(local_678[0] + -0xc) !=
                    (_Rep *)&std::
                             basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             ::_Rep::_S_empty_rep_storage) {
                  LOCK();
                  *(int *)(local_678[0] + -4) = *(int *)(local_678[0] + -4) + 1;
                  UNLOCK();
                }
                puVar15 = &std::
                           basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                           ::_Rep::_S_empty_rep_storage;
                puVar12 = local_678[0];
              }
              if (puVar15 !=
                  &std::
                   basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                   ::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar2 = (int *)(puVar15 + 2);
                iVar23 = *piVar2;
                *piVar2 = *piVar2 + -1;
                UNLOCK();
                if (iVar23 < 1) {
                  operator_delete(puVar15);
                }
              }
            }
            local_938 = puVar12;
            lVar21 = *(long *)(local_698 + -0xc);
            if (lVar21 != 0) {
              lVar18 = *(long *)(local_938 + -0xc);
              uVar17 = lVar18 + lVar21;
              if ((*(ulong *)(local_938 + -8) < uVar17) || (0 < *(int *)(local_938 + -4))) {
                    /* try { // try from 008950c2 to 008950c6 has its CatchHandler @ 00898792 */
                std::
                basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                           *)&local_938,uVar17);
                lVar18 = *(long *)(local_938 + -0xc);
              }
              if (lVar21 == 1) {
                local_938[lVar18] = *local_698;
              }
              else {
                memmove(local_938 + lVar18,local_698,lVar21 * 2);
              }
              if (local_938 != &DAT_01426458) {
                *(undefined4 *)(local_938 + -4) = 0;
                *(ulong *)(local_938 + -0xc) = uVar17;
                local_938[uVar17] = 0;
              }
            }
            local_6b8 = &DAT_01426458;
            local_6a0 = 0;
            local_6b0 = 0;
            local_6a8 = 0;
            puVar12 = local_6b8;
            if (local_938 != &DAT_01426458) {
              if (*(int *)(local_938 + -4) < 0) {
                    /* try { // try from 00895956 to 0089595a has its CatchHandler @ 00898579 */
                puVar12 = (undefined2 *)
                          std::
                          basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                          ::_Rep::_M_clone((_Rep *)(local_938 + -0xc),(allocator *)local_578,0);
                puVar15 = (undefined8 *)(local_6b8 + -0xc);
              }
              else {
                if ((_Rep *)(local_938 + -0xc) !=
                    (_Rep *)&std::
                             basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             ::_Rep::_S_empty_rep_storage) {
                  LOCK();
                  *(int *)(local_938 + -4) = *(int *)(local_938 + -4) + 1;
                  UNLOCK();
                }
                puVar15 = &std::
                           basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                           ::_Rep::_S_empty_rep_storage;
                puVar12 = local_938;
              }
              if (puVar15 !=
                  &std::
                   basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                   ::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar2 = (int *)(puVar15 + 2);
                iVar23 = *piVar2;
                *piVar2 = *piVar2 + -1;
                UNLOCK();
                if (iVar23 < 1) {
                  operator_delete(puVar15);
                }
              }
            }
            local_6b8 = puVar12;
            Ogre::UTFString::~UTFString((UTFString *)&local_938);
                    /* try { // try from 00895192 to 00895196 has its CatchHandler @ 008988f6 */
            Ogre::operator+((Ogre *)local_6f8,(UTFString *)&local_6b8,(UTFString *)&local_6d8);
            local_958 = &DAT_01426458;
            local_940 = 0;
            local_950 = 0;
            local_948 = 0;
            psVar13 = local_958;
            if (local_6f8[0] != &DAT_01426458) {
              if (*(int *)(local_6f8[0] + -4) < 0) {
                    /* try { // try from 008958cc to 008958d0 has its CatchHandler @ 008994c5 */
                psVar13 = (short *)std::
                                   basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                                   ::_Rep::_M_clone((_Rep *)(local_6f8[0] + -0xc),
                                                    (allocator *)local_578,0);
                psVar11 = local_958 + -0xc;
              }
              else {
                if ((_Rep *)(local_6f8[0] + -0xc) !=
                    (_Rep *)&std::
                             basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             ::_Rep::_S_empty_rep_storage) {
                  LOCK();
                  *(int *)(local_6f8[0] + -4) = *(int *)(local_6f8[0] + -4) + 1;
                  UNLOCK();
                }
                psVar11 = (short *)&std::
                                    basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                                    ::_Rep::_S_empty_rep_storage;
                psVar13 = local_6f8[0];
              }
              if ((ulong *)psVar11 !=
                  &std::
                   basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                   ::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar2 = (int *)(psVar11 + 8);
                iVar23 = *piVar2;
                *piVar2 = *piVar2 + -1;
                UNLOCK();
                if (iVar23 < 1) {
                  operator_delete(psVar11);
                }
              }
            }
            local_958 = psVar13;
            lVar21 = *(long *)(local_718 + -0xc);
            if (lVar21 != 0) {
              lVar18 = *(long *)(local_958 + -0xc);
              uVar17 = lVar18 + lVar21;
              if ((*(ulong *)(local_958 + -8) < uVar17) || (0 < *(int *)(local_958 + -4))) {
                    /* try { // try from 00895254 to 00895258 has its CatchHandler @ 0089897c */
                std::
                basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                           *)&local_958,uVar17);
                lVar18 = *(long *)(local_958 + -0xc);
              }
              if (lVar21 == 1) {
                local_958[lVar18] = *local_718;
              }
              else {
                memmove(local_958 + lVar18,local_718,lVar21 * 2);
              }
              if (local_958 != &DAT_01426458) {
                local_958[-4] = 0;
                local_958[-3] = 0;
                *(ulong *)(local_958 + -0xc) = uVar17;
                local_958[uVar17] = 0;
              }
            }
            local_738 = &DAT_01426458;
            local_720 = (wstring_conflict *)0x0;
            local_730 = 0;
            local_728 = 0;
            psVar13 = local_738;
            if (local_958 != &DAT_01426458) {
              if (*(int *)(local_958 + -4) < 0) {
                    /* try { // try from 00895931 to 00895935 has its CatchHandler @ 00898540 */
                psVar13 = (short *)std::
                                   basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                                   ::_Rep::_M_clone((_Rep *)(local_958 + -0xc),
                                                    (allocator *)local_578,0);
                local_a00 = local_738 + -0xc;
              }
              else {
                if ((_Rep *)(local_958 + -0xc) !=
                    (_Rep *)&std::
                             basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             ::_Rep::_S_empty_rep_storage) {
                  LOCK();
                  *(int *)(local_958 + -4) = *(int *)(local_958 + -4) + 1;
                  UNLOCK();
                }
                local_a00 = (short *)&std::
                                      basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                                      ::_Rep::_S_empty_rep_storage;
                psVar13 = local_958;
              }
              if ((ulong *)local_a00 !=
                  &std::
                   basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                   ::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar2 = (int *)(local_a00 + 8);
                iVar23 = *piVar2;
                *piVar2 = *piVar2 + -1;
                UNLOCK();
                if (iVar23 < 1) {
                  operator_delete(local_a00);
                }
              }
            }
            local_738 = psVar13;
            Ogre::UTFString::~UTFString((UTFString *)&local_958);
            pwVar6 = local_720;
            if (local_730 != 2) {
              if (local_720 != (wstring_conflict *)0x0) {
                if (local_730 == 3) {
                  if (local_720 != (wstring_conflict *)0x0) {
                    puVar12 = (undefined2 *)(*(long *)local_720 + -0x18);
                    if (puVar12 !=
                        &std::
                         basic_string<unsigned_int,std::char_traits<unsigned_int>,std::allocator<unsigned_int>>
                         ::_Rep::_S_empty_rep_storage) {
                      LOCK();
                      piVar2 = (int *)(*(long *)local_720 + -8);
                      iVar23 = *piVar2;
                      *piVar2 = *piVar2 + -1;
                      UNLOCK();
                      if (iVar23 < 1) {
                        operator_delete(puVar12);
                      }
                    }
                    goto LAB_00895a0d;
                  }
                }
                else if ((local_730 == 1) && (local_720 != (wstring_conflict *)0x0)) {
                  paVar1 = (allocator *)(*(long *)local_720 + -0x18);
                  if (paVar1 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                    LOCK();
                    piVar2 = (int *)(*(long *)local_720 + -8);
                    iVar23 = *piVar2;
                    *piVar2 = *piVar2 + -1;
                    UNLOCK();
                    if (iVar23 < 1) {
                      std::string::_Rep::_M_destroy(paVar1);
                    }
                  }
LAB_00895a0d:
                  operator_delete(pwVar6);
                }
                local_720 = (wstring_conflict *)0x0;
                local_728 = 0;
              }
                    /* try { // try from 008956c2 to 008956c6 has its CatchHandler @ 00898c44 */
              local_720 = operator_new(8);
              *(undefined4 **)local_720 = &DAT_01424558;
              local_730 = 2;
            }
                    /* try { // try from 00895334 to 008955a7 has its CatchHandler @ 00898c44 */
            std::wstring::_M_mutate((ulong)local_720,0,*(ulong *)(*(long *)local_720 + -0x18));
            pwVar6 = local_720;
            std::wstring::reserve((ulong)local_720);
            iVar23 = *(int *)(local_738 + -4);
            psVar13 = local_738 + -0xc;
            if (iVar23 < 0) {
              local_a40 = local_738 + *(long *)(local_738 + -0xc);
            }
            else {
              if ((ulong *)psVar13 ==
                  &std::
                   basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                   ::_Rep::_S_empty_rep_storage) {
                psVar13 = (short *)&std::
                                    basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                                    ::_Rep::_S_empty_rep_storage;
                local_a40 = local_738 +
                            std::
                            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                            ::_Rep::_S_empty_rep_storage;
              }
              else {
                if (iVar23 != 0) {
                  std::
                  basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                  ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                               *)&local_738,0,0,0);
                  psVar13 = local_738 + -0xc;
                }
                psVar13[8] = -1;
                psVar13[9] = -1;
                psVar13 = local_738 + -0xc;
                local_a40 = local_738 + *(long *)(local_738 + -0xc);
                iVar23 = *(int *)(local_738 + -4);
                if (iVar23 < 0) goto LAB_008953fe;
              }
              if ((ulong *)psVar13 !=
                  &std::
                   basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                   ::_Rep::_S_empty_rep_storage) {
                if (iVar23 != 0) {
                  std::
                  basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                  ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                               *)&local_738,0,0,0);
                }
                local_738[-4] = -1;
                local_738[-3] = -1;
              }
            }
LAB_008953fe:
            if (local_a40 != local_738) {
              plVar10 = (long *)(local_738 + -0xc);
              psVar13 = local_738;
              do {
                if ((-1 < (int)plVar10[2]) &&
                   ((ulong *)plVar10 !=
                    &std::
                     basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                     ::_Rep::_S_empty_rep_storage)) {
                  if ((int)plVar10[2] != 0) {
                    std::
                    basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                    ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                                 *)&local_738,0,0,0);
                    plVar10 = (long *)(local_738 + -0xc);
                  }
                  *(undefined4 *)(plVar10 + 2) = 0xffffffff;
                }
                lVar21 = (long)psVar13 - (long)local_738 >> 1;
                uVar14 = (ushort)local_738[lVar21] + 0x2800;
                if ((((ushort)uVar14 < 0x400) &&
                    (uVar17 = lVar21 + 1, uVar17 < *(ulong *)(local_738 + -0xc))) &&
                   ((ushort)(local_738[uVar17] + 0x2400U) < 0x400)) {
                  uVar14 = ((ushort)(local_738[uVar17] + 0x2400U) & 0x3ff | (uVar14 & 0x3ff) << 10)
                           + 0x10000;
                }
                else {
                  uVar14 = (uint)(ushort)local_738[lVar21];
                }
                lVar21 = *(long *)pwVar6;
                lVar18 = *(long *)(lVar21 + -0x18);
                uVar17 = lVar18 + 1;
                if ((*(ulong *)(lVar21 + -0x10) < uVar17) || (0 < *(int *)(lVar21 + -8))) {
                  std::wstring::reserve((ulong)pwVar6);
                  lVar21 = *(long *)pwVar6;
                  lVar18 = *(long *)(lVar21 + -0x18);
                }
                *(uint *)(lVar21 + lVar18 * 4) = uVar14;
                puVar5 = *(undefined4 **)pwVar6;
                if (puVar5 != &DAT_01424558) {
                  puVar5[-2] = 0;
                  *(ulong *)(puVar5 + -6) = uVar17;
                  puVar5[uVar17] = 0;
                }
                plVar10 = (long *)(local_738 + -0xc);
                if ((-1 < *(int *)(local_738 + -4)) &&
                   ((ulong *)plVar10 !=
                    &std::
                     basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                     ::_Rep::_S_empty_rep_storage)) {
                  if (*(int *)(local_738 + -4) != 0) {
                    std::
                    basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                    ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                                 *)&local_738,0,0,0);
                    plVar10 = (long *)(local_738 + -0xc);
                  }
                  *(undefined4 *)(plVar10 + 2) = 0xffffffff;
                  plVar10 = (long *)(local_738 + -0xc);
                }
                psVar11 = psVar13 + 1;
                if (((psVar11 != local_738 + *plVar10) && ((ushort)(psVar13[1] + 0x2400U) < 0x400))
                   && ((ushort)(*psVar13 + 0x2800U) < 0x400)) {
                  psVar11 = psVar13 + 2;
                }
                psVar13 = psVar11;
              } while (psVar11 != local_a40);
            }
            std::wstring::wstring(local_448,local_720);
                    /* try { // try from 008955b0 to 008955b4 has its CatchHandler @ 00899341 */
            std::wstring::assign(in_RDI);
                    /* try { // try from 008955b8 to 008955bc has its CatchHandler @ 00898c44 */
            std::wstring::~wstring(local_448);
            Ogre::UTFString::~UTFString((UTFString *)&local_738);
            Ogre::UTFString::~UTFString((UTFString *)local_6f8);
            Ogre::UTFString::~UTFString((UTFString *)&local_6b8);
            Ogre::UTFString::~UTFString((UTFString *)local_678);
            Ogre::UTFString::~UTFString((UTFString *)&local_638);
                    /* try { // try from 00895601 to 00895605 has its CatchHandler @ 0089888e */
            std::wstring::~wstring((wstring_conflict *)local_438);
                    /* try { // try from 0089560e to 00895612 has its CatchHandler @ 008988af */
            std::wstring::~wstring(local_428);
                    /* try { // try from 0089561b to 0089561f has its CatchHandler @ 00898712 */
            std::wstring::~wstring(local_408);
                    /* try { // try from 00895628 to 0089562c has its CatchHandler @ 00898754 */
            std::wstring::~wstring(local_3f8);
                    /* try { // try from 00895635 to 00895639 has its CatchHandler @ 0089916b */
            std::wstring::~wstring((wstring_conflict *)local_418);
            Ogre::UTFString::~UTFString(local_658);
            Ogre::UTFString::~UTFString((UTFString *)&local_698);
            Ogre::UTFString::~UTFString((UTFString *)&local_6d8);
            Ogre::UTFString::~UTFString((UTFString *)&local_718);
                    /* try { // try from 00895670 to 00895674 has its CatchHandler @ 00898e27 */
            std::wstring::~wstring((wstring_conflict *)local_458);
          }
          local_a34 = local_a34 + 1;
          uVar14 = *(uint *)(pCVar9 + 0x10);
        } while (local_a34 < uVar14);
      }
      if (uVar14 != 0) {
        local_a34 = 0;
        do {
          if (local_a34 < *(uint *)(pCVar9 + 0x14)) {
            plVar10 = (long *)((ulong)local_a34 * 8 + *(long *)(pCVar9 + 8));
          }
          else {
            plVar10 = *(long **)(pCVar9 + 8);
          }
          puVar15 = (undefined8 *)*plVar10;
          if (local_a04 < *(int *)((long)puVar15 + 0x14)) {
                    /* try { // try from 00895ade to 00895ae2 has its CatchHandler @ 00898e27 */
            CAffix::getDisplayStats((CAffix *)local_458,(uint)*puVar15);
                    /* try { // try from 00895af8 to 00895afc has its CatchHandler @ 00898626 */
            std::wstring::wstring(local_488,L"\\n",&local_3d);
                    /* try { // try from 00895b12 to 00895b16 has its CatchHandler @ 00898630 */
            std::wstring::wstring(local_478,L"\n",&local_3c);
                    /* try { // try from 00895b27 to 00895b2b has its CatchHandler @ 00898647 */
            std::wstring::wstring(local_468,(wstring_conflict *)local_458);
                    /* try { // try from 00895b4c to 00895b50 has its CatchHandler @ 0089865b */
            STRINGS::replaceWString(local_498,local_468,local_478);
                    /* try { // try from 00895b61 to 00895b65 has its CatchHandler @ 0089866f */
            std::wstring::assign((wstring_conflict *)local_458);
                    /* try { // try from 00895b6e to 00895b72 has its CatchHandler @ 0089865b */
            std::wstring::~wstring((wstring_conflict *)local_498);
                    /* try { // try from 00895b7b to 00895b7f has its CatchHandler @ 00898647 */
            std::wstring::~wstring(local_468);
                    /* try { // try from 00895b88 to 00895b8c has its CatchHandler @ 00898630 */
            std::wstring::~wstring(local_478);
                    /* try { // try from 00895b95 to 00895b99 has its CatchHandler @ 00898626 */
            std::wstring::~wstring(local_488);
            local_7b8 = &DAT_01426458;
            local_7a0 = 0;
            local_7b0 = 0;
            local_7a8 = 0;
            local_578[0] = &DAT_01424558;
            wcslen(L" : ");
                    /* try { // try from 00895bef to 00895d1c has its CatchHandler @ 00898683 */
            std::wstring::assign((wchar_t *)local_578,0xfd0b80);
            std::
            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
            ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                         *)&local_7b8,0,*(ulong *)(local_7b8 + -0xc),0);
            std::
            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
            ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                       *)&local_7b8,*(ulong *)(local_578[0] + -6));
            puVar3 = local_578[0] + *(long *)(local_578[0] + -6);
            if (local_578[0] != puVar3) {
              sVar24 = 0;
              puVar19 = local_578[0];
              do {
                uVar14 = *puVar19;
                lVar21 = 1;
                sVar22 = (short)uVar14;
                if (0xffff < uVar14) {
                  lVar21 = 2;
                  sVar24 = ((ushort)(uVar14 - 0x10000) & 0x3ff) + 0xdc00;
                  sVar22 = ((ushort)(uVar14 - 0x10000 >> 10) & 0x3ff) + 0xd800;
                }
                lVar18 = *(long *)(local_7b8 + -0xc);
                uVar17 = lVar18 + 1;
                if ((*(ulong *)(local_7b8 + -8) < uVar17) || (0 < *(int *)(local_7b8 + -4))) {
                  std::
                  basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                  ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             *)&local_7b8,uVar17);
                  lVar18 = *(long *)(local_7b8 + -0xc);
                }
                local_7b8[lVar18] = sVar22;
                if (local_7b8 != &DAT_01426458) {
                  local_7b8[-4] = 0;
                  local_7b8[-3] = 0;
                  *(ulong *)(local_7b8 + -0xc) = uVar17;
                  local_7b8[uVar17] = 0;
                }
                if (lVar21 == 2) {
                  lVar21 = *(long *)(local_7b8 + -0xc);
                  uVar17 = lVar21 + 1;
                  if ((*(ulong *)(local_7b8 + -8) < uVar17) || (0 < *(int *)(local_7b8 + -4))) {
                    std::
                    basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                    ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                               *)&local_7b8,uVar17);
                    lVar21 = *(long *)(local_7b8 + -0xc);
                  }
                  local_7b8[lVar21] = sVar24;
                  if (local_7b8 != &DAT_01426458) {
                    local_7b8[-4] = 0;
                    local_7b8[-3] = 0;
                    *(ulong *)(local_7b8 + -0xc) = uVar17;
                    local_7b8[uVar17] = 0;
                  }
                }
                puVar19 = puVar19 + 1;
              } while (puVar3 != puVar19);
            }
                    /* try { // try from 00895d5d to 00895d61 has its CatchHandler @ 00898a2f */
            std::wstring::~wstring((wstring_conflict *)local_578);
                    /* try { // try from 00895d6f to 00895d73 has its CatchHandler @ 00898e01 */
            Ogre::UTFString::UTFString
                      ((UTFString *)local_778,(string *)&getEquipmentStats()::g_SetPieces);
                    /* try { // try from 00895d84 to 00895d88 has its CatchHandler @ 00898e0b */
            STRINGS::GetValueAsWString(local_4a8,*(int *)((long)puVar15 + 0x14));
                    /* try { // try from 00895d9e to 00895da2 has its CatchHandler @ 00898ce3 */
            std::operator+((wchar_t *)local_4b8,(wstring_conflict *)&DAT_00fd0b90);
                    /* try { // try from 00895db8 to 00895dbc has its CatchHandler @ 00898ced */
            std::operator+((wstring_conflict *)local_4c8,(wchar_t *)local_4b8);
            local_758 = &DAT_01426458;
            local_740 = 0;
            local_750 = 0;
            local_748 = 0;
                    /* try { // try from 00895e08 to 00895f0f has its CatchHandler @ 00898cf7 */
            std::
            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
            ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                         *)&local_758,0,
                        std::
                        basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                        ::_Rep::_S_empty_rep_storage,0);
            std::
            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
            ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                       *)&local_758,*(ulong *)(local_4c8[0] + -6));
            puVar3 = local_4c8[0] + *(long *)(local_4c8[0] + -6);
            if (local_4c8[0] != puVar3) {
              sVar24 = 0;
              puVar19 = local_4c8[0];
              do {
                uVar14 = *puVar19;
                lVar21 = 1;
                sVar22 = (short)uVar14;
                if (0xffff < uVar14) {
                  lVar21 = 2;
                  sVar24 = ((ushort)(uVar14 - 0x10000) & 0x3ff) + 0xdc00;
                  sVar22 = ((ushort)(uVar14 - 0x10000 >> 10) & 0x3ff) + 0xd800;
                }
                lVar18 = *(long *)(local_758 + -0xc);
                uVar17 = lVar18 + 1;
                if ((*(ulong *)(local_758 + -8) < uVar17) || (0 < *(int *)(local_758 + -4))) {
                  std::
                  basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                  ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             *)&local_758,uVar17);
                  lVar18 = *(long *)(local_758 + -0xc);
                }
                local_758[lVar18] = sVar22;
                if (local_758 != &DAT_01426458) {
                  local_758[-4] = 0;
                  local_758[-3] = 0;
                  *(ulong *)(local_758 + -0xc) = uVar17;
                  local_758[uVar17] = 0;
                }
                if (lVar21 == 2) {
                  lVar21 = *(long *)(local_758 + -0xc);
                  uVar17 = lVar21 + 1;
                  if ((*(ulong *)(local_758 + -8) < uVar17) || (0 < *(int *)(local_758 + -4))) {
                    std::
                    basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                    ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                               *)&local_758,uVar17);
                    lVar21 = *(long *)(local_758 + -0xc);
                  }
                  local_758[lVar21] = sVar24;
                  if (local_758 != &DAT_01426458) {
                    local_758[-4] = 0;
                    local_758[-3] = 0;
                    *(ulong *)(local_758 + -0xc) = uVar17;
                    local_758[uVar17] = 0;
                  }
                }
                puVar19 = puVar19 + 1;
              } while (puVar3 != puVar19);
            }
            local_978 = &DAT_01426458;
            local_960 = 0;
            local_970 = 0;
            local_968 = 0;
            psVar13 = local_978;
            if (local_758 != &DAT_01426458) {
              if (*(int *)(local_758 + -4) < 0) {
                    /* try { // try from 008977f2 to 008977f6 has its CatchHandler @ 008993d7 */
                psVar13 = (short *)std::
                                   basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                                   ::_Rep::_M_clone((_Rep *)(local_758 + -0xc),
                                                    (allocator *)local_578,0);
                psVar11 = local_978 + -0xc;
              }
              else {
                if ((_Rep *)(local_758 + -0xc) !=
                    (_Rep *)&std::
                             basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             ::_Rep::_S_empty_rep_storage) {
                  LOCK();
                  *(int *)(local_758 + -4) = *(int *)(local_758 + -4) + 1;
                  UNLOCK();
                }
                psVar11 = (short *)&std::
                                    basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                                    ::_Rep::_S_empty_rep_storage;
                psVar13 = local_758;
              }
              if ((ulong *)psVar11 !=
                  &std::
                   basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                   ::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar2 = (int *)(psVar11 + 8);
                iVar23 = *piVar2;
                *piVar2 = *piVar2 + -1;
                UNLOCK();
                if (iVar23 < 1) {
                  operator_delete(psVar11);
                }
              }
            }
            local_978 = psVar13;
            lVar21 = *(long *)(local_778[0] + -0xc);
            if (lVar21 != 0) {
              lVar18 = *(long *)(local_978 + -0xc);
              uVar17 = lVar18 + lVar21;
              if ((*(ulong *)(local_978 + -8) < uVar17) || (0 < *(int *)(local_978 + -4))) {
                    /* try { // try from 00896000 to 00896004 has its CatchHandler @ 00898824 */
                std::
                basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                           *)&local_978,uVar17);
                lVar18 = *(long *)(local_978 + -0xc);
              }
              if (lVar21 == 1) {
                local_978[lVar18] = *local_778[0];
              }
              else {
                memmove(local_978 + lVar18,local_778[0],lVar21 * 2);
              }
              if (local_978 != &DAT_01426458) {
                local_978[-4] = 0;
                local_978[-3] = 0;
                *(ulong *)(local_978 + -0xc) = uVar17;
                local_978[uVar17] = 0;
              }
            }
            local_798 = &DAT_01426458;
            local_780 = 0;
            local_790 = 0;
            local_788 = 0;
            psVar13 = local_798;
            if (local_978 != &DAT_01426458) {
              if (*(int *)(local_978 + -4) < 0) {
                    /* try { // try from 0089772a to 0089772e has its CatchHandler @ 0089936a */
                psVar13 = (short *)std::
                                   basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                                   ::_Rep::_M_clone((_Rep *)(local_978 + -0xc),
                                                    (allocator *)local_578,0);
                psVar11 = local_798 + -0xc;
              }
              else {
                if ((_Rep *)(local_978 + -0xc) !=
                    (_Rep *)&std::
                             basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             ::_Rep::_S_empty_rep_storage) {
                  LOCK();
                  *(int *)(local_978 + -4) = *(int *)(local_978 + -4) + 1;
                  UNLOCK();
                }
                psVar11 = (short *)&std::
                                    basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                                    ::_Rep::_S_empty_rep_storage;
                psVar13 = local_978;
              }
              if ((ulong *)psVar11 !=
                  &std::
                   basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                   ::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar2 = (int *)(psVar11 + 8);
                iVar23 = *piVar2;
                *piVar2 = *piVar2 + -1;
                UNLOCK();
                if (iVar23 < 1) {
                  operator_delete(psVar11);
                }
              }
            }
            local_798 = psVar13;
            Ogre::UTFString::~UTFString((UTFString *)&local_978);
            local_998 = &DAT_01426458;
            local_980 = 0;
            local_990 = 0;
            local_988 = 0;
            psVar13 = local_998;
            if (local_798 != &DAT_01426458) {
              if (*(int *)(local_798 + -4) < 0) {
                    /* try { // try from 008977ca to 008977ce has its CatchHandler @ 008993c0 */
                psVar13 = (short *)std::
                                   basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                                   ::_Rep::_M_clone((_Rep *)(local_798 + -0xc),
                                                    (allocator *)local_578,0);
                psVar11 = local_998 + -0xc;
              }
              else {
                if ((_Rep *)(local_798 + -0xc) !=
                    (_Rep *)&std::
                             basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             ::_Rep::_S_empty_rep_storage) {
                  LOCK();
                  *(int *)(local_798 + -4) = *(int *)(local_798 + -4) + 1;
                  UNLOCK();
                }
                psVar11 = (short *)&std::
                                    basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                                    ::_Rep::_S_empty_rep_storage;
                psVar13 = local_798;
              }
              if ((ulong *)psVar11 !=
                  &std::
                   basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                   ::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar2 = (int *)(psVar11 + 8);
                iVar23 = *piVar2;
                *piVar2 = *piVar2 + -1;
                UNLOCK();
                if (iVar23 < 1) {
                  operator_delete(psVar11);
                }
              }
            }
            local_998 = psVar13;
            lVar21 = *(long *)(local_7b8 + -0xc);
            if (lVar21 != 0) {
              lVar18 = *(long *)(local_998 + -0xc);
              uVar17 = lVar18 + lVar21;
              if ((*(ulong *)(local_998 + -8) < uVar17) || (0 < *(int *)(local_998 + -4))) {
                    /* try { // try from 0089617f to 00896183 has its CatchHandler @ 00898ab2 */
                std::
                basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                           *)&local_998,uVar17);
                lVar18 = *(long *)(local_998 + -0xc);
              }
              if (lVar21 == 1) {
                local_998[lVar18] = *local_7b8;
              }
              else {
                memmove(local_998 + lVar18,local_7b8,lVar21 * 2);
              }
              if (local_998 != &DAT_01426458) {
                local_998[-4] = 0;
                local_998[-3] = 0;
                *(ulong *)(local_998 + -0xc) = uVar17;
                local_998[uVar17] = 0;
              }
            }
            local_7d8 = &DAT_01426458;
            local_7c0 = (wstring_conflict *)0x0;
            local_7d0 = 0;
            local_7c8 = 0;
            psVar13 = local_7d8;
            if (local_998 != &DAT_01426458) {
              if (*(int *)(local_998 + -4) < 0) {
                    /* try { // try from 00897702 to 00897706 has its CatchHandler @ 00899353 */
                psVar13 = (short *)std::
                                   basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                                   ::_Rep::_M_clone((_Rep *)(local_998 + -0xc),
                                                    (allocator *)local_578,0);
                psVar11 = local_7d8 + -0xc;
              }
              else {
                if ((_Rep *)(local_998 + -0xc) !=
                    (_Rep *)&std::
                             basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             ::_Rep::_S_empty_rep_storage) {
                  LOCK();
                  *(int *)(local_998 + -4) = *(int *)(local_998 + -4) + 1;
                  UNLOCK();
                }
                psVar11 = (short *)&std::
                                    basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                                    ::_Rep::_S_empty_rep_storage;
                psVar13 = local_998;
              }
              if ((ulong *)psVar11 !=
                  &std::
                   basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                   ::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar2 = (int *)(psVar11 + 8);
                iVar23 = *piVar2;
                *piVar2 = *piVar2 + -1;
                UNLOCK();
                if (iVar23 < 1) {
                  operator_delete(psVar11);
                }
              }
            }
            local_7d8 = psVar13;
            Ogre::UTFString::~UTFString((UTFString *)&local_998);
            pwVar6 = local_7c0;
            if (local_7d0 != 2) {
              if (local_7c0 != (wstring_conflict *)0x0) {
                if (local_7d0 == 3) {
                  if (local_7c0 != (wstring_conflict *)0x0) {
                    puVar12 = (undefined2 *)(*(long *)local_7c0 + -0x18);
                    if (puVar12 !=
                        &std::
                         basic_string<unsigned_int,std::char_traits<unsigned_int>,std::allocator<unsigned_int>>
                         ::_Rep::_S_empty_rep_storage) {
                      LOCK();
                      piVar2 = (int *)(*(long *)local_7c0 + -8);
                      iVar23 = *piVar2;
                      *piVar2 = *piVar2 + -1;
                      UNLOCK();
                      if (iVar23 < 1) {
                        operator_delete(puVar12);
                      }
                    }
                    goto LAB_008978ad;
                  }
                }
                else if ((local_7d0 == 1) && (local_7c0 != (wstring_conflict *)0x0)) {
                  paVar1 = (allocator *)(*(long *)local_7c0 + -0x18);
                  if (paVar1 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                    LOCK();
                    piVar2 = (int *)(*(long *)local_7c0 + -8);
                    iVar23 = *piVar2;
                    *piVar2 = *piVar2 + -1;
                    UNLOCK();
                    if (iVar23 < 1) {
                      std::string::_Rep::_M_destroy(paVar1);
                    }
                  }
LAB_008978ad:
                  operator_delete(pwVar6);
                }
                local_7c0 = (wstring_conflict *)0x0;
                local_7c8 = 0;
              }
                    /* try { // try from 0089756a to 0089756e has its CatchHandler @ 00898b62 */
              local_7c0 = operator_new(8);
              *(undefined4 **)local_7c0 = &DAT_01424558;
              local_7d0 = 2;
            }
                    /* try { // try from 00896269 to 008964e7 has its CatchHandler @ 00898b62 */
            std::wstring::_M_mutate((ulong)local_7c0,0,*(ulong *)(*(long *)local_7c0 + -0x18));
            pwVar6 = local_7c0;
            std::wstring::reserve((ulong)local_7c0);
            psVar13 = local_7d8 + -0xc;
            if (*(int *)(local_7d8 + -4) < 0) {
              psVar13 = local_7d8 + *(long *)(local_7d8 + -0xc);
            }
            else if ((ulong *)psVar13 ==
                     &std::
                      basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                      ::_Rep::_S_empty_rep_storage) {
              psVar13 = local_7d8 +
                        std::
                        basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                        ::_Rep::_S_empty_rep_storage;
            }
            else {
              if (*(int *)(local_7d8 + -4) != 0) {
                std::
                basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             *)&local_7d8,0,0,0);
                psVar13 = local_7d8 + -0xc;
              }
              psVar13[8] = -1;
              psVar13[9] = -1;
              psVar11 = local_7d8 + -0xc;
              psVar13 = local_7d8 + *(long *)(local_7d8 + -0xc);
              if ((-1 < *(int *)(local_7d8 + -4)) &&
                 ((ulong *)psVar11 !=
                  &std::
                   basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                   ::_Rep::_S_empty_rep_storage)) {
                if (*(int *)(local_7d8 + -4) != 0) {
                  std::
                  basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                  ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                               *)&local_7d8,0,0,0);
                  psVar11 = local_7d8 + -0xc;
                }
                psVar11[8] = -1;
                psVar11[9] = -1;
              }
            }
            if (psVar13 != local_7d8) {
              plVar10 = (long *)(local_7d8 + -0xc);
              psVar11 = local_7d8;
              do {
                if ((-1 < (int)plVar10[2]) &&
                   ((ulong *)plVar10 !=
                    &std::
                     basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                     ::_Rep::_S_empty_rep_storage)) {
                  if ((int)plVar10[2] != 0) {
                    std::
                    basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                    ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                                 *)&local_7d8,0,0,0);
                    plVar10 = (long *)(local_7d8 + -0xc);
                  }
                  *(undefined4 *)(plVar10 + 2) = 0xffffffff;
                }
                lVar21 = (long)psVar11 - (long)local_7d8 >> 1;
                uVar14 = (ushort)local_7d8[lVar21] + 0x2800;
                if ((((ushort)uVar14 < 0x400) &&
                    (uVar17 = lVar21 + 1, uVar17 < *(ulong *)(local_7d8 + -0xc))) &&
                   ((ushort)(local_7d8[uVar17] + 0x2400U) < 0x400)) {
                  uVar14 = ((ushort)(local_7d8[uVar17] + 0x2400U) & 0x3ff | (uVar14 & 0x3ff) << 10)
                           + 0x10000;
                }
                else {
                  uVar14 = (uint)(ushort)local_7d8[lVar21];
                }
                lVar21 = *(long *)pwVar6;
                lVar18 = *(long *)(lVar21 + -0x18);
                uVar17 = lVar18 + 1;
                if ((*(ulong *)(lVar21 + -0x10) < uVar17) || (0 < *(int *)(lVar21 + -8))) {
                  std::wstring::reserve((ulong)pwVar6);
                  lVar21 = *(long *)pwVar6;
                  lVar18 = *(long *)(lVar21 + -0x18);
                }
                *(uint *)(lVar21 + lVar18 * 4) = uVar14;
                puVar5 = *(undefined4 **)pwVar6;
                if (puVar5 != &DAT_01424558) {
                  puVar5[-2] = 0;
                  *(ulong *)(puVar5 + -6) = uVar17;
                  puVar5[uVar17] = 0;
                }
                plVar10 = (long *)(local_7d8 + -0xc);
                if ((-1 < *(int *)(local_7d8 + -4)) &&
                   ((ulong *)plVar10 !=
                    &std::
                     basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                     ::_Rep::_S_empty_rep_storage)) {
                  if (*(int *)(local_7d8 + -4) != 0) {
                    std::
                    basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                    ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                                 *)&local_7d8,0,0,0);
                    plVar10 = (long *)(local_7d8 + -0xc);
                  }
                  *(undefined4 *)(plVar10 + 2) = 0xffffffff;
                  plVar10 = (long *)(local_7d8 + -0xc);
                }
                psVar16 = psVar11 + 1;
                if (((psVar16 != local_7d8 + *plVar10) && ((ushort)(psVar11[1] + 0x2400U) < 0x400))
                   && ((ushort)(*psVar11 + 0x2800U) < 0x400)) {
                  psVar16 = psVar11 + 2;
                }
                psVar11 = psVar16;
              } while (psVar16 != psVar13);
            }
            std::wstring::wstring(local_4f8,local_7c0);
                    /* try { // try from 00896500 to 00896504 has its CatchHandler @ 00898b74 */
            std::wstring::wstring(local_4e8,L"\\n",&local_3e);
                    /* try { // try from 00896518 to 0089651c has its CatchHandler @ 00898ba2 */
            std::wstring::wstring(local_4d8,(wstring_conflict *)local_458);
                    /* try { // try from 00896531 to 00896535 has its CatchHandler @ 00898bb1 */
            STRINGS::replaceWString((STRINGS *)local_508,local_4d8,local_4e8,local_4f8);
                    /* try { // try from 00896541 to 00896545 has its CatchHandler @ 00898bc0 */
            std::wstring::assign((wstring_conflict *)local_458);
                    /* try { // try from 00896549 to 0089654d has its CatchHandler @ 00898bb1 */
            std::wstring::~wstring(local_508);
                    /* try { // try from 00896551 to 00896555 has its CatchHandler @ 00898ba2 */
            std::wstring::~wstring(local_4d8);
                    /* try { // try from 00896559 to 0089655d has its CatchHandler @ 00898b74 */
            std::wstring::~wstring(local_4e8);
                    /* try { // try from 00896561 to 00896565 has its CatchHandler @ 00898b62 */
            std::wstring::~wstring(local_4f8);
            Ogre::UTFString::~UTFString((UTFString *)&local_7d8);
            Ogre::UTFString::~UTFString((UTFString *)&local_798);
            Ogre::UTFString::~UTFString((UTFString *)&local_758);
                    /* try { // try from 00896590 to 00896594 has its CatchHandler @ 00898ced */
            std::wstring::~wstring((wstring_conflict *)local_4c8);
                    /* try { // try from 0089659d to 008965a1 has its CatchHandler @ 00898ce3 */
            std::wstring::~wstring(local_4b8);
                    /* try { // try from 008965aa to 008965ae has its CatchHandler @ 00898e0b */
            std::wstring::~wstring((wstring_conflict *)local_4a8);
            Ogre::UTFString::~UTFString((UTFString *)local_778);
            Ogre::UTFString::~UTFString((UTFString *)&local_7b8);
            local_8d8 = &DAT_01426458;
            local_8c0 = 0;
            local_8d0 = 0;
            local_8c8 = 0;
            local_578[0] = &DAT_01424558;
            wcslen(L"|u");
                    /* try { // try from 0089662b to 00896758 has its CatchHandler @ 00898bcf */
            std::wstring::assign((wchar_t *)local_578,0xfc8340);
            std::
            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
            ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                         *)&local_8d8,0,*(ulong *)(local_8d8 + -0xc),0);
            std::
            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
            ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                       *)&local_8d8,*(ulong *)(local_578[0] + -6));
            puVar3 = local_578[0] + *(long *)(local_578[0] + -6);
            if (local_578[0] != puVar3) {
              sVar24 = 0;
              puVar19 = local_578[0];
              do {
                uVar14 = *puVar19;
                lVar21 = 1;
                sVar22 = (short)uVar14;
                if (0xffff < uVar14) {
                  lVar21 = 2;
                  sVar24 = ((ushort)(uVar14 - 0x10000) & 0x3ff) + 0xdc00;
                  sVar22 = ((ushort)(uVar14 - 0x10000 >> 10) & 0x3ff) + 0xd800;
                }
                lVar18 = *(long *)(local_8d8 + -0xc);
                uVar17 = lVar18 + 1;
                if ((*(ulong *)(local_8d8 + -8) < uVar17) || (0 < *(int *)(local_8d8 + -4))) {
                  std::
                  basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                  ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             *)&local_8d8,uVar17);
                  lVar18 = *(long *)(local_8d8 + -0xc);
                }
                local_8d8[lVar18] = sVar22;
                if (local_8d8 != &DAT_01426458) {
                  *(undefined4 *)(local_8d8 + -4) = 0;
                  *(ulong *)(local_8d8 + -0xc) = uVar17;
                  local_8d8[uVar17] = 0;
                }
                if (lVar21 == 2) {
                  lVar21 = *(long *)(local_8d8 + -0xc);
                  uVar17 = lVar21 + 1;
                  if ((*(ulong *)(local_8d8 + -8) < uVar17) || (0 < *(int *)(local_8d8 + -4))) {
                    std::
                    basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                    ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                               *)&local_8d8,uVar17);
                    lVar21 = *(long *)(local_8d8 + -0xc);
                  }
                  local_8d8[lVar21] = sVar24;
                  if (local_8d8 != &DAT_01426458) {
                    *(undefined4 *)(local_8d8 + -4) = 0;
                    *(ulong *)(local_8d8 + -0xc) = uVar17;
                    local_8d8[uVar17] = 0;
                  }
                }
                puVar19 = puVar19 + 1;
              } while (puVar3 != puVar19);
            }
                    /* try { // try from 00896799 to 0089679d has its CatchHandler @ 00898bf0 */
            std::wstring::~wstring((wstring_conflict *)local_578);
            local_898 = &DAT_01426458;
            local_880 = 0;
            local_890 = 0;
            local_888 = 0;
                    /* try { // try from 008967e0 to 008968e4 has its CatchHandler @ 00898bf7 */
            std::
            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
            ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                         *)&local_898,0,
                        std::
                        basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                        ::_Rep::_S_empty_rep_storage,0);
            std::
            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
            ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                       *)&local_898,*(ulong *)(local_458[0] + -6));
            puVar3 = local_458[0] + *(long *)(local_458[0] + -6);
            if (local_458[0] != puVar3) {
              sVar24 = 0;
              puVar19 = local_458[0];
              do {
                uVar14 = *puVar19;
                lVar21 = 1;
                sVar22 = (short)uVar14;
                if (0xffff < uVar14) {
                  lVar21 = 2;
                  sVar24 = ((ushort)(uVar14 - 0x10000) & 0x3ff) + 0xdc00;
                  sVar22 = ((ushort)(uVar14 - 0x10000 >> 10) & 0x3ff) + 0xd800;
                }
                lVar18 = *(long *)(local_898 + -0xc);
                uVar17 = lVar18 + 1;
                if ((*(ulong *)(local_898 + -8) < uVar17) || (0 < *(int *)(local_898 + -4))) {
                  std::
                  basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                  ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             *)&local_898,uVar17);
                  lVar18 = *(long *)(local_898 + -0xc);
                }
                local_898[lVar18] = sVar22;
                if (local_898 != &DAT_01426458) {
                  *(undefined4 *)(local_898 + -4) = 0;
                  *(ulong *)(local_898 + -0xc) = uVar17;
                  local_898[uVar17] = 0;
                }
                if (lVar21 == 2) {
                  lVar21 = *(long *)(local_898 + -0xc);
                  uVar17 = lVar21 + 1;
                  if ((*(ulong *)(local_898 + -8) < uVar17) || (0 < *(int *)(local_898 + -4))) {
                    std::
                    basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                    ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                               *)&local_898,uVar17);
                    lVar21 = *(long *)(local_898 + -0xc);
                  }
                  local_898[lVar21] = sVar24;
                  if (local_898 != &DAT_01426458) {
                    *(undefined4 *)(local_898 + -4) = 0;
                    *(ulong *)(local_898 + -0xc) = uVar17;
                    local_898[uVar17] = 0;
                  }
                }
                puVar19 = puVar19 + 1;
              } while (puVar3 != puVar19);
            }
            local_858 = &DAT_01426458;
            local_840 = 0;
            local_850 = 0;
            local_848 = 0;
            local_578[0] = &DAT_01424558;
            wcslen(L" : ");
                    /* try { // try from 0089697f to 00896aa0 has its CatchHandler @ 00898a7c */
            std::wstring::assign((wchar_t *)local_578,0xfd0b80);
            std::
            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
            ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                         *)&local_858,0,*(ulong *)(local_858 + -0xc),0);
            std::
            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
            ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                       *)&local_858,*(ulong *)(local_578[0] + -6));
            puVar3 = local_578[0] + *(long *)(local_578[0] + -6);
            if (local_578[0] != puVar3) {
              sVar24 = 0;
              puVar19 = local_578[0];
              do {
                uVar14 = *puVar19;
                lVar21 = 1;
                sVar22 = (short)uVar14;
                if (0xffff < uVar14) {
                  lVar21 = 2;
                  sVar24 = ((ushort)(uVar14 - 0x10000) & 0x3ff) + 0xdc00;
                  sVar22 = ((ushort)(uVar14 - 0x10000 >> 10) & 0x3ff) + 0xd800;
                }
                lVar18 = *(long *)(local_858 + -0xc);
                uVar17 = lVar18 + 1;
                if ((*(ulong *)(local_858 + -8) < uVar17) || (0 < *(int *)(local_858 + -4))) {
                  std::
                  basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                  ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             *)&local_858,uVar17);
                  lVar18 = *(long *)(local_858 + -0xc);
                }
                local_858[lVar18] = sVar22;
                if (local_858 != &DAT_01426458) {
                  *(undefined4 *)(local_858 + -4) = 0;
                  *(ulong *)(local_858 + -0xc) = uVar17;
                  local_858[uVar17] = 0;
                }
                if (lVar21 == 2) {
                  lVar21 = *(long *)(local_858 + -0xc);
                  uVar17 = lVar21 + 1;
                  if ((*(ulong *)(local_858 + -8) < uVar17) || (0 < *(int *)(local_858 + -4))) {
                    std::
                    basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                    ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                               *)&local_858,uVar17);
                    lVar21 = *(long *)(local_858 + -0xc);
                  }
                  local_858[lVar21] = sVar24;
                  if (local_858 != &DAT_01426458) {
                    *(undefined4 *)(local_858 + -4) = 0;
                    *(ulong *)(local_858 + -0xc) = uVar17;
                    local_858[uVar17] = 0;
                  }
                }
                puVar19 = puVar19 + 1;
              } while (puVar3 != puVar19);
            }
                    /* try { // try from 00896ae1 to 00896ae5 has its CatchHandler @ 00898a39 */
            std::wstring::~wstring((wstring_conflict *)local_578);
                    /* try { // try from 00896af3 to 00896af7 has its CatchHandler @ 00898dd6 */
            Ogre::UTFString::UTFString
                      ((UTFString *)local_818,(string *)&getEquipmentStats()::g_SetPieces);
                    /* try { // try from 00896b08 to 00896b0c has its CatchHandler @ 00898df7 */
            STRINGS::GetValueAsWString(local_538,*(int *)((long)puVar15 + 0x14));
                    /* try { // try from 00896b0d to 00896b2f has its CatchHandler @ 008989cb */
            CGameGlobals::getSingleton();
            std::operator+(local_518,(wchar_t *)in_RDI);
                    /* try { // try from 00896b43 to 00896b47 has its CatchHandler @ 008989f1 */
            std::operator+(local_528,local_518);
                    /* try { // try from 00896b60 to 00896b64 has its CatchHandler @ 008989fb */
            std::operator+(local_548,local_528);
                    /* try { // try from 00896b7a to 00896b7e has its CatchHandler @ 00898a05 */
            std::operator+((wstring_conflict *)local_558,(wchar_t *)local_548);
            local_7f8 = &DAT_01426458;
            local_7e0 = 0;
            local_7f0 = 0;
            local_7e8 = 0;
                    /* try { // try from 00896bc1 to 00896cc9 has its CatchHandler @ 00898d0e */
            std::
            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
            ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                         *)&local_7f8,0,
                        std::
                        basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                        ::_Rep::_S_empty_rep_storage,0);
            std::
            basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
            ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                       *)&local_7f8,*(ulong *)(local_558[0] + -6));
            puVar3 = local_558[0] + *(long *)(local_558[0] + -6);
            if (local_558[0] != puVar3) {
              sVar24 = 0;
              puVar19 = local_558[0];
              do {
                uVar14 = *puVar19;
                lVar21 = 1;
                sVar22 = (short)uVar14;
                if (0xffff < uVar14) {
                  lVar21 = 2;
                  sVar24 = ((ushort)(uVar14 - 0x10000) & 0x3ff) + 0xdc00;
                  sVar22 = ((ushort)(uVar14 - 0x10000 >> 10) & 0x3ff) + 0xd800;
                }
                lVar18 = *(long *)(local_7f8 + -0xc);
                uVar17 = lVar18 + 1;
                if ((*(ulong *)(local_7f8 + -8) < uVar17) || (0 < *(int *)(local_7f8 + -4))) {
                  std::
                  basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                  ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             *)&local_7f8,uVar17);
                  lVar18 = *(long *)(local_7f8 + -0xc);
                }
                local_7f8[lVar18] = sVar22;
                if (local_7f8 != &DAT_01426458) {
                  *(undefined4 *)(local_7f8 + -4) = 0;
                  *(ulong *)(local_7f8 + -0xc) = uVar17;
                  local_7f8[uVar17] = 0;
                }
                if (lVar21 == 2) {
                  lVar21 = *(long *)(local_7f8 + -0xc);
                  uVar17 = lVar21 + 1;
                  if ((*(ulong *)(local_7f8 + -8) < uVar17) || (0 < *(int *)(local_7f8 + -4))) {
                    std::
                    basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                    ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                               *)&local_7f8,uVar17);
                    lVar21 = *(long *)(local_7f8 + -0xc);
                  }
                  local_7f8[lVar21] = sVar24;
                  if (local_7f8 != &DAT_01426458) {
                    *(undefined4 *)(local_7f8 + -4) = 0;
                    *(ulong *)(local_7f8 + -0xc) = uVar17;
                    local_7f8[uVar17] = 0;
                  }
                }
                puVar19 = puVar19 + 1;
              } while (puVar3 != puVar19);
            }
            local_9b8 = &DAT_01426458;
            local_9a0 = 0;
            local_9b0 = 0;
            local_9a8 = 0;
            puVar12 = local_9b8;
            if (local_7f8 != &DAT_01426458) {
              if (*(int *)(local_7f8 + -4) < 0) {
                    /* try { // try from 008976b2 to 008976b6 has its CatchHandler @ 00899450 */
                puVar12 = (undefined2 *)
                          std::
                          basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                          ::_Rep::_M_clone((_Rep *)(local_7f8 + -0xc),(allocator *)local_578,0);
                puVar15 = (undefined8 *)(local_9b8 + -0xc);
              }
              else {
                if ((_Rep *)(local_7f8 + -0xc) !=
                    (_Rep *)&std::
                             basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             ::_Rep::_S_empty_rep_storage) {
                  LOCK();
                  *(int *)(local_7f8 + -4) = *(int *)(local_7f8 + -4) + 1;
                  UNLOCK();
                }
                puVar15 = &std::
                           basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                           ::_Rep::_S_empty_rep_storage;
                puVar12 = local_7f8;
              }
              if (puVar15 !=
                  &std::
                   basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                   ::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar2 = (int *)(puVar15 + 2);
                iVar23 = *piVar2;
                *piVar2 = *piVar2 + -1;
                UNLOCK();
                if (iVar23 < 1) {
                  operator_delete(puVar15);
                }
              }
            }
            local_9b8 = puVar12;
            lVar21 = *(long *)(local_818[0] + -0xc);
            if (lVar21 != 0) {
              lVar18 = *(long *)(local_9b8 + -0xc);
              uVar17 = lVar18 + lVar21;
              if ((*(ulong *)(local_9b8 + -8) < uVar17) || (0 < *(int *)(local_9b8 + -4))) {
                    /* try { // try from 00896dba to 00896dbe has its CatchHandler @ 0089810b */
                std::
                basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                           *)&local_9b8,uVar17);
                lVar18 = *(long *)(local_9b8 + -0xc);
              }
              if (lVar21 == 1) {
                local_9b8[lVar18] = *local_818[0];
              }
              else {
                memmove(local_9b8 + lVar18,local_818[0],lVar21 * 2);
              }
              if (local_9b8 != &DAT_01426458) {
                *(undefined4 *)(local_9b8 + -4) = 0;
                *(ulong *)(local_9b8 + -0xc) = uVar17;
                local_9b8[uVar17] = 0;
              }
            }
            local_838 = &DAT_01426458;
            local_820 = 0;
            local_830 = 0;
            local_828 = 0;
            puVar12 = local_838;
            if (local_9b8 != &DAT_01426458) {
              if (*(int *)(local_9b8 + -4) < 0) {
                    /* try { // try from 00897752 to 00897756 has its CatchHandler @ 00899381 */
                puVar12 = (undefined2 *)
                          std::
                          basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                          ::_Rep::_M_clone((_Rep *)(local_9b8 + -0xc),(allocator *)local_578,0);
                puVar15 = (undefined8 *)(local_838 + -0xc);
              }
              else {
                if ((_Rep *)(local_9b8 + -0xc) !=
                    (_Rep *)&std::
                             basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             ::_Rep::_S_empty_rep_storage) {
                  LOCK();
                  *(int *)(local_9b8 + -4) = *(int *)(local_9b8 + -4) + 1;
                  UNLOCK();
                }
                puVar15 = &std::
                           basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                           ::_Rep::_S_empty_rep_storage;
                puVar12 = local_9b8;
              }
              if (puVar15 !=
                  &std::
                   basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                   ::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar2 = (int *)(puVar15 + 2);
                iVar23 = *piVar2;
                *piVar2 = *piVar2 + -1;
                UNLOCK();
                if (iVar23 < 1) {
                  operator_delete(puVar15);
                }
              }
            }
            local_838 = puVar12;
            Ogre::UTFString::~UTFString((UTFString *)&local_9b8);
            local_9d8 = &DAT_01426458;
            local_9c0 = 0;
            local_9d0 = 0;
            local_9c8 = 0;
            puVar12 = local_9d8;
            if (local_838 != &DAT_01426458) {
              if (*(int *)(local_838 + -4) < 0) {
                    /* try { // try from 008977a2 to 008977a6 has its CatchHandler @ 008993ac */
                puVar12 = (undefined2 *)
                          std::
                          basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                          ::_Rep::_M_clone((_Rep *)(local_838 + -0xc),(allocator *)local_578,0);
                puVar15 = (undefined8 *)(local_9d8 + -0xc);
              }
              else {
                if ((_Rep *)(local_838 + -0xc) !=
                    (_Rep *)&std::
                             basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             ::_Rep::_S_empty_rep_storage) {
                  LOCK();
                  *(int *)(local_838 + -4) = *(int *)(local_838 + -4) + 1;
                  UNLOCK();
                }
                puVar15 = &std::
                           basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                           ::_Rep::_S_empty_rep_storage;
                puVar12 = local_838;
              }
              if (puVar15 !=
                  &std::
                   basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                   ::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar2 = (int *)(puVar15 + 2);
                iVar23 = *piVar2;
                *piVar2 = *piVar2 + -1;
                UNLOCK();
                if (iVar23 < 1) {
                  operator_delete(puVar15);
                }
              }
            }
            local_9d8 = puVar12;
            lVar21 = *(long *)(local_858 + -0xc);
            if (lVar21 != 0) {
              lVar18 = *(long *)(local_9d8 + -0xc);
              uVar17 = lVar18 + lVar21;
              if ((*(ulong *)(local_9d8 + -8) < uVar17) || (0 < *(int *)(local_9d8 + -4))) {
                    /* try { // try from 00896f27 to 00896f2b has its CatchHandler @ 008983a1 */
                std::
                basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                           *)&local_9d8,uVar17);
                lVar18 = *(long *)(local_9d8 + -0xc);
              }
              if (lVar21 == 1) {
                local_9d8[lVar18] = *local_858;
              }
              else {
                memmove(local_9d8 + lVar18,local_858,lVar21 * 2);
              }
              if (local_9d8 != &DAT_01426458) {
                *(undefined4 *)(local_9d8 + -4) = 0;
                *(ulong *)(local_9d8 + -0xc) = uVar17;
                local_9d8[uVar17] = 0;
              }
            }
            local_878 = &DAT_01426458;
            local_860 = 0;
            local_870 = 0;
            local_868 = 0;
            puVar12 = local_878;
            if (local_9d8 != &DAT_01426458) {
              if (*(int *)(local_9d8 + -4) < 0) {
                    /* try { // try from 008976da to 008976de has its CatchHandler @ 00899467 */
                puVar12 = (undefined2 *)
                          std::
                          basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                          ::_Rep::_M_clone((_Rep *)(local_9d8 + -0xc),(allocator *)local_578,0);
                puVar15 = (undefined8 *)(local_878 + -0xc);
              }
              else {
                if ((_Rep *)(local_9d8 + -0xc) !=
                    (_Rep *)&std::
                             basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             ::_Rep::_S_empty_rep_storage) {
                  LOCK();
                  *(int *)(local_9d8 + -4) = *(int *)(local_9d8 + -4) + 1;
                  UNLOCK();
                }
                puVar15 = &std::
                           basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                           ::_Rep::_S_empty_rep_storage;
                puVar12 = local_9d8;
              }
              if (puVar15 !=
                  &std::
                   basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                   ::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar2 = (int *)(puVar15 + 2);
                iVar23 = *piVar2;
                *piVar2 = *piVar2 + -1;
                UNLOCK();
                if (iVar23 < 1) {
                  operator_delete(puVar15);
                }
              }
            }
            local_878 = puVar12;
            Ogre::UTFString::~UTFString((UTFString *)&local_9d8);
            local_9f8 = &DAT_01426458;
            local_9e0 = 0;
            local_9f0 = 0;
            local_9e8 = 0;
            puVar12 = local_9f8;
            if (local_878 != &DAT_01426458) {
              if (*(int *)(local_878 + -4) < 0) {
                    /* try { // try from 0089777a to 0089777e has its CatchHandler @ 00899398 */
                puVar12 = (undefined2 *)
                          std::
                          basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                          ::_Rep::_M_clone((_Rep *)(local_878 + -0xc),(allocator *)local_578,0);
                puVar15 = (undefined8 *)(local_9f8 + -0xc);
              }
              else {
                if ((_Rep *)(local_878 + -0xc) !=
                    (_Rep *)&std::
                             basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             ::_Rep::_S_empty_rep_storage) {
                  LOCK();
                  *(int *)(local_878 + -4) = *(int *)(local_878 + -4) + 1;
                  UNLOCK();
                }
                puVar15 = &std::
                           basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                           ::_Rep::_S_empty_rep_storage;
                puVar12 = local_878;
              }
              if (puVar15 !=
                  &std::
                   basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                   ::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar2 = (int *)(puVar15 + 2);
                iVar23 = *piVar2;
                *piVar2 = *piVar2 + -1;
                UNLOCK();
                if (iVar23 < 1) {
                  operator_delete(puVar15);
                }
              }
            }
            local_9f8 = puVar12;
            lVar21 = *(long *)(local_898 + -0xc);
            if (lVar21 != 0) {
              lVar18 = *(long *)(local_9f8 + -0xc);
              uVar17 = lVar18 + lVar21;
              if ((*(ulong *)(local_9f8 + -8) < uVar17) || (0 < *(int *)(local_9f8 + -4))) {
                    /* try { // try from 00897086 to 0089708a has its CatchHandler @ 00898275 */
                std::
                basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                ::reserve((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                           *)&local_9f8,uVar17);
                lVar18 = *(long *)(local_9f8 + -0xc);
              }
              if (lVar21 == 1) {
                local_9f8[lVar18] = *local_898;
              }
              else {
                memmove(local_9f8 + lVar18,local_898,lVar21 * 2);
              }
              if (local_9f8 != &DAT_01426458) {
                *(undefined4 *)(local_9f8 + -4) = 0;
                *(ulong *)(local_9f8 + -0xc) = uVar17;
                local_9f8[uVar17] = 0;
              }
            }
            local_8b8 = &DAT_01426458;
            local_8a0 = 0;
            local_8b0 = 0;
            local_8a8 = 0;
            puVar12 = local_8b8;
            if (local_9f8 != &DAT_01426458) {
              if (*(int *)(local_9f8 + -4) < 0) {
                    /* try { // try from 00897682 to 00897686 has its CatchHandler @ 00899439 */
                puVar12 = (undefined2 *)
                          std::
                          basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                          ::_Rep::_M_clone((_Rep *)(local_9f8 + -0xc),(allocator *)local_578,0);
                local_a18 = (undefined8 *)(local_8b8 + -0xc);
              }
              else {
                if ((_Rep *)(local_9f8 + -0xc) !=
                    (_Rep *)&std::
                             basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             ::_Rep::_S_empty_rep_storage) {
                  LOCK();
                  *(int *)(local_9f8 + -4) = *(int *)(local_9f8 + -4) + 1;
                  UNLOCK();
                }
                local_a18 = &std::
                             basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             ::_Rep::_S_empty_rep_storage;
                puVar12 = local_9f8;
              }
              if (local_a18 !=
                  &std::
                   basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                   ::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar2 = (int *)(local_a18 + 2);
                iVar23 = *piVar2;
                *piVar2 = *piVar2 + -1;
                UNLOCK();
                if (iVar23 < 1) {
                  operator_delete(local_a18);
                }
              }
            }
            local_8b8 = puVar12;
            Ogre::UTFString::~UTFString((UTFString *)&local_9f8);
                    /* try { // try from 00897156 to 0089715a has its CatchHandler @ 008994b4 */
            Ogre::operator+((Ogre *)&local_8f8,(UTFString *)&local_8b8,(UTFString *)&local_8d8);
            pwVar6 = local_8e0;
            if (local_8f0 != 2) {
              if (local_8e0 != (wstring_conflict *)0x0) {
                if (local_8f0 == 3) {
                  if (local_8e0 != (wstring_conflict *)0x0) {
                    puVar12 = (undefined2 *)(*(long *)local_8e0 + -0x18);
                    if (puVar12 !=
                        &std::
                         basic_string<unsigned_int,std::char_traits<unsigned_int>,std::allocator<unsigned_int>>
                         ::_Rep::_S_empty_rep_storage) {
                      LOCK();
                      piVar2 = (int *)(*(long *)local_8e0 + -8);
                      iVar23 = *piVar2;
                      *piVar2 = *piVar2 + -1;
                      UNLOCK();
                      if (iVar23 < 1) {
                        operator_delete(puVar12);
                      }
                    }
                    goto LAB_00897832;
                  }
                }
                else if ((local_8f0 == 1) && (local_8e0 != (wstring_conflict *)0x0)) {
                  paVar1 = (allocator *)(*(long *)local_8e0 + -0x18);
                  if (paVar1 != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
                    LOCK();
                    piVar2 = (int *)(*(long *)local_8e0 + -8);
                    iVar23 = *piVar2;
                    *piVar2 = *piVar2 + -1;
                    UNLOCK();
                    if (iVar23 < 1) {
                      std::string::_Rep::_M_destroy(paVar1);
                    }
                  }
LAB_00897832:
                  operator_delete(pwVar6);
                }
                local_8e0 = (wstring_conflict *)0x0;
                local_8e8 = 0;
              }
                    /* try { // try from 008974fa to 008974fe has its CatchHandler @ 00898b83 */
              local_8e0 = operator_new(8);
              *(undefined4 **)local_8e0 = &DAT_01424558;
              local_8f0 = 2;
            }
                    /* try { // try from 0089717e to 008973e7 has its CatchHandler @ 00898b83 */
            std::wstring::_M_mutate((ulong)local_8e0,0,*(ulong *)(*(long *)local_8e0 + -0x18));
            pwVar6 = local_8e0;
            std::wstring::reserve((ulong)local_8e0);
            psVar13 = local_8f8 + -0xc;
            if (*(int *)(local_8f8 + -4) < 0) {
              psVar13 = local_8f8 + *(long *)(local_8f8 + -0xc);
            }
            else if ((ulong *)psVar13 ==
                     &std::
                      basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                      ::_Rep::_S_empty_rep_storage) {
              psVar13 = local_8f8 +
                        std::
                        basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                        ::_Rep::_S_empty_rep_storage;
            }
            else {
              if (*(int *)(local_8f8 + -4) != 0) {
                std::
                basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                             *)&local_8f8,0,0,0);
                psVar13 = local_8f8 + -0xc;
              }
              psVar13[8] = -1;
              psVar13[9] = -1;
              psVar11 = local_8f8 + -0xc;
              psVar13 = local_8f8 + *(long *)(local_8f8 + -0xc);
              if ((-1 < *(int *)(local_8f8 + -4)) &&
                 ((ulong *)psVar11 !=
                  &std::
                   basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                   ::_Rep::_S_empty_rep_storage)) {
                if (*(int *)(local_8f8 + -4) != 0) {
                  std::
                  basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                  ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                               *)&local_8f8,0,0,0);
                  psVar11 = local_8f8 + -0xc;
                }
                psVar11[8] = -1;
                psVar11[9] = -1;
              }
            }
            if (psVar13 != local_8f8) {
              plVar10 = (long *)(local_8f8 + -0xc);
              psVar11 = local_8f8;
              do {
                if ((-1 < (int)plVar10[2]) &&
                   ((ulong *)plVar10 !=
                    &std::
                     basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                     ::_Rep::_S_empty_rep_storage)) {
                  if ((int)plVar10[2] != 0) {
                    std::
                    basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                    ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                                 *)&local_8f8,0,0,0);
                    plVar10 = (long *)(local_8f8 + -0xc);
                  }
                  *(undefined4 *)(plVar10 + 2) = 0xffffffff;
                }
                lVar21 = (long)psVar11 - (long)local_8f8 >> 1;
                uVar14 = (ushort)local_8f8[lVar21] + 0x2800;
                if ((((ushort)uVar14 < 0x400) &&
                    (uVar17 = lVar21 + 1, uVar17 < *(ulong *)(local_8f8 + -0xc))) &&
                   ((ushort)(local_8f8[uVar17] + 0x2400U) < 0x400)) {
                  uVar14 = ((ushort)(local_8f8[uVar17] + 0x2400U) & 0x3ff | (uVar14 & 0x3ff) << 10)
                           + 0x10000;
                }
                else {
                  uVar14 = (uint)(ushort)local_8f8[lVar21];
                }
                lVar21 = *(long *)pwVar6;
                lVar18 = *(long *)(lVar21 + -0x18);
                uVar17 = lVar18 + 1;
                if ((*(ulong *)(lVar21 + -0x10) < uVar17) || (0 < *(int *)(lVar21 + -8))) {
                  std::wstring::reserve((ulong)pwVar6);
                  lVar21 = *(long *)pwVar6;
                  lVar18 = *(long *)(lVar21 + -0x18);
                }
                *(uint *)(lVar21 + lVar18 * 4) = uVar14;
                puVar5 = *(undefined4 **)pwVar6;
                if (puVar5 != &DAT_01424558) {
                  puVar5[-2] = 0;
                  *(ulong *)(puVar5 + -6) = uVar17;
                  puVar5[uVar17] = 0;
                }
                plVar10 = (long *)(local_8f8 + -0xc);
                if ((-1 < *(int *)(local_8f8 + -4)) &&
                   ((ulong *)plVar10 !=
                    &std::
                     basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                     ::_Rep::_S_empty_rep_storage)) {
                  if (*(int *)(local_8f8 + -4) != 0) {
                    std::
                    basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                    ::_M_mutate((basic_string<unsigned_short,std::char_traits<unsigned_short>,std::allocator<unsigned_short>>
                                 *)&local_8f8,0,0,0);
                    plVar10 = (long *)(local_8f8 + -0xc);
                  }
                  *(undefined4 *)(plVar10 + 2) = 0xffffffff;
                  plVar10 = (long *)(local_8f8 + -0xc);
                }
                psVar16 = psVar11 + 1;
                if (((psVar16 != local_8f8 + *plVar10) && ((ushort)(psVar11[1] + 0x2400U) < 0x400))
                   && ((ushort)(*psVar11 + 0x2800U) < 0x400)) {
                  psVar16 = psVar11 + 2;
                }
                psVar11 = psVar16;
              } while (psVar16 != psVar13);
            }
            std::wstring::wstring(local_568,local_8e0);
                    /* try { // try from 008973f0 to 008973f4 has its CatchHandler @ 0089941c */
            std::wstring::assign(in_RDI);
                    /* try { // try from 008973f8 to 008973fc has its CatchHandler @ 00898b83 */
            std::wstring::~wstring(local_568);
            Ogre::UTFString::~UTFString((UTFString *)&local_8f8);
            Ogre::UTFString::~UTFString((UTFString *)&local_8b8);
            Ogre::UTFString::~UTFString((UTFString *)&local_878);
            Ogre::UTFString::~UTFString((UTFString *)&local_838);
            Ogre::UTFString::~UTFString((UTFString *)&local_7f8);
                    /* try { // try from 00897441 to 00897445 has its CatchHandler @ 00898a05 */
            std::wstring::~wstring((wstring_conflict *)local_558);
                    /* try { // try from 0089744e to 00897452 has its CatchHandler @ 008989fb */
            std::wstring::~wstring(local_548);
                    /* try { // try from 0089745b to 0089745f has its CatchHandler @ 008989f1 */
            std::wstring::~wstring(local_528);
                    /* try { // try from 00897468 to 0089746c has its CatchHandler @ 008989cb */
            std::wstring::~wstring(local_518);
                    /* try { // try from 00897475 to 00897479 has its CatchHandler @ 00898df7 */
            std::wstring::~wstring((wstring_conflict *)local_538);
            Ogre::UTFString::~UTFString((UTFString *)local_818);
            Ogre::UTFString::~UTFString((UTFString *)&local_858);
            Ogre::UTFString::~UTFString((UTFString *)&local_898);
            Ogre::UTFString::~UTFString((UTFString *)&local_8d8);
                    /* try { // try from 008974b0 to 008974b4 has its CatchHandler @ 00898e27 */
            std::wstring::~wstring((wstring_conflict *)local_458);
          }
          local_a34 = local_a34 + 1;
        } while (local_a34 < *(uint *)(pCVar9 + 0x10));
      }
    }
  }
LAB_00893e31:
                    /* try { // try from 00893e39 to 00893e6e has its CatchHandler @ 008994dc */
  std::wstring::~wstring((wstring_conflict *)local_2b8);
  return in_RDI;
}



/* address=00899500
   symbol=CEquipment::missileValidateTargetBeforeLaunch */

/* non-virtual thunk to CEquipment::missileValidateTargetBeforeLaunch(CMissile*,
   CPositionableObject*, Ogre::Vector3&) */

void __thiscall
CEquipment::missileValidateTargetBeforeLaunch
          (CEquipment *this,CMissile *param_1,CPositionableObject *param_2,Vector3 *param_3)

{
  missileValidateTargetBeforeLaunch
            ((CMissile *)(this + -0x230),(CPositionableObject *)param_1,(Vector3 *)param_2);
  return;
}



/* address=00899510
   symbol=CEquipment::missileValidateTargetBeforeLaunch */

/* CEquipment::missileValidateTargetBeforeLaunch(CMissile*, CPositionableObject*, Ogre::Vector3&) */

Vector3 * CEquipment::missileValidateTargetBeforeLaunch
                    (CMissile *param_1,CPositionableObject *param_2,Vector3 *param_3)

{
  return param_3;
}



/* address=00899520
   symbol=CEquipment::getUnitModel */

/* CEquipment::getUnitModel() */

undefined8 __thiscall CEquipment::getUnitModel(CEquipment *this)

{
  return *(undefined8 *)(this + 0x2b0);
}



/* address=00899530
   symbol=CEquipment::getUnitModelSecondary */

/* CEquipment::getUnitModelSecondary() */

undefined8 __thiscall CEquipment::getUnitModelSecondary(CEquipment *this)

{
  return *(undefined8 *)(this + 0x2b8);
}



/* address=00899540
   symbol=CEquipment::getUnitCollisionModel */

/* CEquipment::getUnitCollisionModel() */

undefined8 __thiscall CEquipment::getUnitCollisionModel(CEquipment *this)

{
  return *(undefined8 *)(this + 0x2c0);
}



/* address=00899550
   symbol=CEquipment::getEquippedTo */

/* CEquipment::getEquippedTo() */

undefined8 __thiscall CEquipment::getEquippedTo(CEquipment *this)

{
  return *(undefined8 *)(this + 0x290);
}



/* export-summary functions=109 failures=2 */
