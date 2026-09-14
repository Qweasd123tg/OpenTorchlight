/* Targeted Ghidra class export.
   namespace=CSkillEffectAndAffixes
   Treat pseudocode as navigation evidence. */


/* address=00cab650
   symbol=CSkillEffectAndAffixes::setDurationOverride */

/* CSkillEffectAndAffixes::setDurationOverride(float) */

void __thiscall
CSkillEffectAndAffixes::setDurationOverride(CSkillEffectAndAffixes *this,float param_1)

{
  long lVar1;
  uint uVar2;
  long *plVar3;
  uint uVar4;
  uint uVar5;
  ulong uVar6;
  long *plVar7;

  if (*(int *)(this + 0x20) != 0) {
    uVar2 = 0;
    do {
      while (uVar2 < *(uint *)(this + 0x24)) {
        uVar6 = (ulong)uVar2;
        uVar2 = uVar2 + 1;
        *(float *)(*(long *)(uVar6 * 8 + *(long *)(this + 0x18)) + 0x24) = param_1;
        if (*(uint *)(this + 0x20) <= uVar2) goto LAB_00cab693;
      }
      uVar2 = uVar2 + 1;
      *(float *)(**(long **)(this + 0x18) + 0x24) = param_1;
    } while (uVar2 < *(uint *)(this + 0x20));
  }
LAB_00cab693:
  if (*(int *)(this + 0x38) != 0) {
    uVar2 = *(uint *)(this + 0x3c);
    plVar3 = *(long **)(this + 0x30);
    uVar5 = 0;
    do {
      uVar6 = (ulong)uVar5;
      uVar4 = 0;
      while( true ) {
        plVar7 = plVar3 + uVar6;
        if (uVar2 <= uVar5) {
          plVar7 = plVar3;
        }
        if (*(uint *)(*plVar7 + 0x20) <= uVar4) break;
        plVar7 = plVar3 + uVar6;
        if (uVar2 <= uVar5) {
          plVar7 = plVar3;
        }
        lVar1 = *plVar7;
        if (uVar5 < *(uint *)(lVar1 + 0x24)) {
          plVar7 = (long *)(uVar6 * 8 + *(long *)(lVar1 + 0x18));
        }
        else {
          plVar7 = *(long **)(lVar1 + 0x18);
        }
        if (*(char *)(*plVar7 + 0x28) == '\0') {
          plVar7 = plVar3 + uVar6;
          if (uVar2 <= uVar5) {
            plVar7 = plVar3;
          }
          lVar1 = *plVar7;
          if (uVar5 < *(uint *)(lVar1 + 0x24)) {
            plVar3 = (long *)(uVar6 * 8 + *(long *)(lVar1 + 0x18));
          }
          else {
            plVar3 = *(long **)(lVar1 + 0x18);
          }
          *(float *)(*plVar3 + 0x24) = param_1;
          plVar3 = *(long **)(this + 0x30);
          uVar2 = *(uint *)(this + 0x3c);
        }
        uVar4 = uVar4 + 1;
      }
      uVar5 = uVar5 + 1;
    } while (uVar5 < *(uint *)(this + 0x38));
  }
  return;
}



/* address=00cab750
   symbol=CSkillEffectAndAffixes::addMinAndMaxValuesOfAnEffect */

/* CSkillEffectAndAffixes::addMinAndMaxValuesOfAnEffect(CResourceManager*, unsigned int, float&,
   float&) */

void __thiscall
CSkillEffectAndAffixes::addMinAndMaxValuesOfAnEffect
          (CSkillEffectAndAffixes *this,CResourceManager *param_1,uint param_2,float *param_3,
          float *param_4)

{
  uint uVar1;
  float fVar2;
  long lVar3;
  CEffect *pCVar4;
  undefined8 *puVar5;
  long *plVar6;
  uint uVar7;
  uint uVar8;
  ulong uVar9;
  uint uVar10;
  ulong uVar11;
  float fVar12;

  if (*(int *)(this + 0x50) != 0) {
    uVar7 = *(uint *)(this + 0x54);
    uVar11 = 0;
    do {
      uVar10 = (uint)uVar11;
      uVar9 = 0;
      while( true ) {
        uVar8 = (uint)uVar9;
        if (uVar10 < uVar7) {
          uVar1 = *(uint *)(*(long *)(uVar11 * 8 + *(long *)(this + 0x48)) + 0x90);
        }
        else {
          uVar1 = *(uint *)(**(long **)(this + 0x48) + 0x90);
        }
        if (uVar1 <= uVar8) break;
        if (uVar10 < uVar7) {
          plVar6 = (long *)(uVar11 * 8 + *(long *)(this + 0x48));
        }
        else {
          plVar6 = *(long **)(this + 0x48);
        }
        lVar3 = *plVar6;
        if (uVar8 < *(uint *)(lVar3 + 0x94)) {
          puVar5 = (undefined8 *)(uVar9 * 8 + *(long *)(lVar3 + 0x88));
        }
        else {
          puVar5 = *(undefined8 **)(lVar3 + 0x88);
        }
        pCVar4 = (CEffect *)*puVar5;
        if ((pCVar4 != (CEffect *)0x0) && (*(uint *)(pCVar4 + 0x1c) == param_2)) {
          fVar2 = *param_3;
          fVar12 = (float)CEffect::getMinCaculatedValue(pCVar4);
          *param_3 = fVar12 + fVar2;
          fVar2 = *param_4;
          fVar12 = (float)CEffect::getMaxCaculatedValue(pCVar4);
          *param_4 = fVar12 + fVar2;
          uVar7 = *(uint *)(this + 0x54);
        }
        uVar9 = (ulong)(uVar8 + 1);
      }
      uVar11 = (ulong)(uVar10 + 1);
    } while (uVar10 + 1 < *(uint *)(this + 0x50));
  }
  if (*(int *)(this + 0x38) != 0) {
    uVar7 = *(uint *)(this + 0x3c);
    uVar11 = 0;
    do {
      uVar10 = (uint)uVar11;
      uVar9 = 0;
      while( true ) {
        uVar8 = (uint)uVar9;
        if (uVar10 < uVar7) {
          uVar1 = *(uint *)(*(long *)(uVar11 * 8 + *(long *)(this + 0x30)) + 0x20);
        }
        else {
          uVar1 = *(uint *)(**(long **)(this + 0x30) + 0x20);
        }
        if (uVar1 <= uVar8) break;
        if (uVar10 < uVar7) {
          plVar6 = (long *)(uVar11 * 8 + *(long *)(this + 0x30));
        }
        else {
          plVar6 = *(long **)(this + 0x30);
        }
        lVar3 = *plVar6;
        if (uVar8 < *(uint *)(lVar3 + 0x24)) {
          puVar5 = (undefined8 *)(uVar9 * 8 + *(long *)(lVar3 + 0x18));
        }
        else {
          puVar5 = *(undefined8 **)(lVar3 + 0x18);
        }
        pCVar4 = (CEffect *)*puVar5;
        if ((pCVar4 != (CEffect *)0x0) && (*(uint *)(pCVar4 + 0x1c) == param_2)) {
          fVar2 = *param_3;
          fVar12 = (float)CEffect::getMinCaculatedValue(pCVar4);
          *param_3 = fVar12 + fVar2;
          fVar2 = *param_4;
          fVar12 = (float)CEffect::getMaxCaculatedValue(pCVar4);
          *param_4 = fVar12 + fVar2;
          uVar7 = *(uint *)(this + 0x3c);
        }
        uVar9 = (ulong)(uVar8 + 1);
      }
      uVar11 = (ulong)(uVar10 + 1);
    } while (uVar10 + 1 < *(uint *)(this + 0x38));
  }
  return;
}



/* address=00cab990
   symbol=CSkillEffectAndAffixes::createAffixesForDisplay */

/* CSkillEffectAndAffixes::createAffixesForDisplay(CResourceManager*) */

void __thiscall
CSkillEffectAndAffixes::createAffixesForDisplay
          (CSkillEffectAndAffixes *this,CResourceManager *param_1)

{
  uint uVar1;
  CAffix *this_00;
  void *pvVar2;
  long *plVar3;
  ulong uVar4;
  uint uVar5;
  long lVar6;
  uint uVar7;

  if ((*(int *)(this + 0x50) == 0) && (*(int *)(this + 0x20) != 0)) {
    uVar5 = 0;
    do {
      if (uVar5 < *(uint *)(this + 0x24)) {
        lVar6 = *(long *)(*(long *)(this + 0x18) + (ulong)uVar5 * 8);
        uVar7 = *(uint *)(lVar6 + 0x18);
      }
      else {
        lVar6 = **(long **)(this + 0x18);
        uVar7 = *(uint *)(lVar6 + 0x18);
      }
      this_00 = (CAffix *)
                CResourceManager::getNewAffixByName
                          (param_1,(wstring_conflict *)(lVar6 + 0x10),uVar7);
      if (this_00 != (CAffix *)0x0) {
        CAffix::setSkillOwner(this_00,*(CSkill **)(this + 0x10));
        if (this_00[0xa8] == (CAffix)0x0) {
          if (uVar5 < *(uint *)(this + 0x24)) {
            plVar3 = (long *)((ulong)uVar5 * 8 + *(long *)(this + 0x18));
          }
          else {
            plVar3 = *(long **)(this + 0x18);
          }
          if (0.0 < *(float *)(*plVar3 + 0x24)) {
            if (uVar5 < *(uint *)(this + 0x24)) {
              plVar3 = (long *)((ulong)uVar5 * 8 + *(long *)(this + 0x18));
            }
            else {
              plVar3 = *(long **)(this + 0x18);
            }
            *(undefined4 *)(this_00 + 0xa4) = *(undefined4 *)(*plVar3 + 0x24);
          }
        }
        uVar7 = *(uint *)(this + 0x50);
        if (uVar7 < *(uint *)(this + 0x54)) {
          pvVar2 = *(void **)(this + 0x48);
        }
        else if (*(long *)(this + 0x48) == 0) {
          *(uint *)(this + 0x54) = *(uint *)(this + 0x58);
          pvVar2 = operator_new__((ulong)*(uint *)(this + 0x58) << 3);
          *(void **)(this + 0x48) = pvVar2;
          uVar7 = *(uint *)(this + 0x50);
        }
        else {
          uVar7 = *(uint *)(this + 0x54) + *(int *)(this + 0x58);
          pvVar2 = operator_new__((ulong)uVar7 << 3);
          if (*(int *)(this + 0x54) != 0) {
            uVar1 = 0;
            do {
              uVar4 = (ulong)uVar1;
              uVar1 = uVar1 + 1;
              *(undefined8 *)((long)pvVar2 + uVar4 * 8) =
                   *(undefined8 *)(*(long *)(this + 0x48) + uVar4 * 8);
            } while (uVar1 < *(uint *)(this + 0x54));
          }
          if (*(void **)(this + 0x48) != (void *)0x0) {
            operator_delete__(*(void **)(this + 0x48));
          }
          *(void **)(this + 0x48) = pvVar2;
          *(uint *)(this + 0x54) = uVar7;
          uVar7 = *(uint *)(this + 0x50);
        }
        *(CAffix **)((long)pvVar2 + (ulong)uVar7 * 8) = this_00;
        *(int *)(this + 0x50) = *(int *)(this + 0x50) + 1;
      }
      uVar5 = uVar5 + 1;
    } while (uVar5 < *(uint *)(this + 0x20));
  }
  return;
}



/* address=00cabb30
   symbol=CSkillEffectAndAffixes::effectsTargetEnemy */

/* CSkillEffectAndAffixes::effectsTargetEnemy(CBaseUnit*) */

undefined8 __thiscall
CSkillEffectAndAffixes::effectsTargetEnemy(CSkillEffectAndAffixes *this,CBaseUnit *param_1)

{
  char cVar1;
  long *plVar2;
  uint uVar3;

  if ((param_1 != (CBaseUnit *)0x0) && (*(int *)(this + 0x20) != 0)) {
    uVar3 = 0;
    do {
      if (uVar3 < *(uint *)(this + 0x24)) {
        plVar2 = (long *)((ulong)uVar3 * 8 + *(long *)(this + 0x18));
      }
      else {
        plVar2 = *(long **)(this + 0x18);
      }
      cVar1 = CBaseUnit::ISA(param_1,*(undefined4 *)(*plVar2 + 0x1c));
      if (cVar1 != '\0') {
        if (uVar3 < *(uint *)(this + 0x24)) {
          plVar2 = (long *)((ulong)uVar3 * 8 + *(long *)(this + 0x18));
        }
        else {
          plVar2 = *(long **)(this + 0x18);
        }
        if (*(int *)(*plVar2 + 0x20) == 0) {
          return 1;
        }
      }
      uVar3 = uVar3 + 1;
    } while (uVar3 < *(uint *)(this + 0x20));
  }
  return 0;
}



/* address=00cabbc0
   symbol=CSkillEffectAndAffixes::canAffixesAndEffectsBeAppliedToUnit */

/* CSkillEffectAndAffixes::canAffixesAndEffectsBeAppliedToUnit(CBaseUnit*, CCharacter*) */

undefined8 __thiscall
CSkillEffectAndAffixes::canAffixesAndEffectsBeAppliedToUnit
          (CSkillEffectAndAffixes *this,CBaseUnit *param_1,CCharacter *param_2)

{
  uint uVar1;
  long lVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  CCharacter *this_00;
  long *plVar7;
  undefined8 *puVar8;
  uint uVar9;
  ulong uVar10;
  uint uVar11;

  this_00 = (CCharacter *)0x0;
  if (*(int *)(param_1 + 0x188) == 0) {
    this_00 = (CCharacter *)param_1;
  }
  if (*(int *)(this + 0x38) != 0) {
    uVar11 = 0;
    do {
      if (uVar11 < *(uint *)(this + 0x3c)) {
        plVar7 = (long *)((ulong)uVar11 * 8 + *(long *)(this + 0x30));
      }
      else {
        plVar7 = *(long **)(this + 0x30);
      }
      cVar3 = CBaseUnit::ISA(param_1,*(undefined4 *)(*plVar7 + 0x30));
      if (cVar3 == '\0') {
        return 0;
      }
      uVar6 = *(uint *)(this + 0x3c);
      if (uVar11 < uVar6) {
        iVar4 = *(int *)(*(long *)((ulong)uVar11 * 8 + *(long *)(this + 0x30)) + 0x34);
        if (iVar4 == 1) goto LAB_00cabe5a;
LAB_00cabc49:
        if (iVar4 == 2) {
          if (this_00 == (CCharacter *)0x0) {
            return 0;
          }
          if (param_2 == (CCharacter *)0x0) {
            return 0;
          }
          if (param_2 != *(CCharacter **)(this_00 + 0x640)) {
            return 0;
          }
        }
        else if (iVar4 == 0) {
          if (param_2 == (CCharacter *)0x0) {
            return 0;
          }
          if (this_00 != (CCharacter *)0x0) {
            iVar4 = CCharacter::alignment(this_00);
            iVar5 = CCharacter::alignment(param_2);
            if (iVar4 == iVar5) {
              return 0;
            }
            uVar6 = *(uint *)(this + 0x3c);
          }
        }
      }
      else {
        iVar4 = *(int *)(**(long **)(this + 0x30) + 0x34);
        if (iVar4 != 1) goto LAB_00cabc49;
LAB_00cabe5a:
        if ((this_00 != param_2) && (this_00 != (CCharacter *)0x0)) {
          return 0;
        }
      }
      if (uVar11 < uVar6) {
        plVar7 = (long *)((ulong)uVar11 * 8 + *(long *)(this + 0x30));
      }
      else {
        plVar7 = *(long **)(this + 0x30);
      }
      if (*(int *)(*plVar7 + 0x20) != 0) {
        uVar10 = 0;
        while( true ) {
          uVar9 = (uint)uVar10;
          if (uVar11 < uVar6) {
            uVar1 = *(uint *)(*(long *)((ulong)uVar11 * 8 + *(long *)(this + 0x30)) + 0x20);
          }
          else {
            uVar1 = *(uint *)(**(long **)(this + 0x30) + 0x20);
          }
          if (uVar1 <= uVar9) break;
          if (uVar11 < uVar6) {
            plVar7 = (long *)((ulong)uVar11 * 8 + *(long *)(this + 0x30));
          }
          else {
            plVar7 = *(long **)(this + 0x30);
          }
          lVar2 = *plVar7;
          if (uVar9 < *(uint *)(lVar2 + 0x24)) {
            puVar8 = (undefined8 *)(uVar10 * 8 + *(long *)(lVar2 + 0x18));
          }
          else {
            puVar8 = *(undefined8 **)(lVar2 + 0x18);
          }
          cVar3 = (**(code **)(*(long *)param_1 + 0x238))(param_1,param_2,param_2,*puVar8);
          if (cVar3 == '\0') {
            return 0;
          }
          uVar6 = *(uint *)(this + 0x3c);
          uVar10 = (ulong)(uVar9 + 1);
        }
      }
      uVar11 = uVar11 + 1;
    } while (uVar11 < *(uint *)(this + 0x38));
  }
  if (*(int *)(this + 0x20) != 0) {
    uVar11 = 0;
    do {
      if (uVar11 < *(uint *)(this + 0x24)) {
        plVar7 = (long *)((ulong)uVar11 * 8 + *(long *)(this + 0x18));
      }
      else {
        plVar7 = *(long **)(this + 0x18);
      }
      cVar3 = CBaseUnit::ISA(param_1,*(undefined4 *)(*plVar7 + 0x1c));
      if (cVar3 == '\0') {
        return 0;
      }
      if (uVar11 < *(uint *)(this + 0x24)) {
        iVar4 = *(int *)(*(long *)((ulong)uVar11 * 8 + *(long *)(this + 0x18)) + 0x20);
        if (iVar4 == 1) goto LAB_00cabed9;
LAB_00cabd76:
        if (iVar4 == 2) {
          if (this_00 == (CCharacter *)0x0) {
            return 0;
          }
          if (param_2 == (CCharacter *)0x0) {
            return 0;
          }
          if (param_2 != *(CCharacter **)(this_00 + 0x640)) {
            return 0;
          }
        }
        else if (iVar4 == 0) {
          if (param_2 == (CCharacter *)0x0) {
            return 0;
          }
          if (this_00 != (CCharacter *)0x0) {
            iVar4 = CCharacter::alignment(this_00);
            iVar5 = CCharacter::alignment(param_2);
            if (iVar4 == iVar5) {
              return 0;
            }
          }
        }
      }
      else {
        iVar4 = *(int *)(**(long **)(this + 0x18) + 0x20);
        if (iVar4 != 1) goto LAB_00cabd76;
LAB_00cabed9:
        if (param_2 == (CCharacter *)0x0) {
          return 0;
        }
        if ((this_00 != param_2) && (this_00 != (CCharacter *)0x0)) {
          return 0;
        }
      }
      uVar11 = uVar11 + 1;
    } while (uVar11 < *(uint *)(this + 0x20));
  }
  return 1;
}



/* address=00cabf10
   symbol=CSkillEffectAndAffixes::getPortalSkillName */

/* CSkillEffectAndAffixes::getPortalSkillName() */

void CSkillEffectAndAffixes::getPortalSkillName(void)

{
  uint uVar1;
  int iVar2;
  long lVar3;
  uint uVar4;
  long *plVar5;
  long *plVar6;
  long in_RSI;
  uint uVar7;
  wstring_conflict *in_RDI;
  long lVar8;

  if (*(uint *)(in_RSI + 0x38) != 0) {
    uVar1 = *(uint *)(in_RSI + 0x3c);
    lVar8 = 0;
    uVar7 = 0;
    do {
      if (uVar7 < uVar1) {
        plVar5 = (long *)(lVar8 + *(long *)(in_RSI + 0x30));
      }
      else {
        plVar5 = *(long **)(in_RSI + 0x30);
      }
      if (*(int *)(*plVar5 + 0x20) != 0) {
        plVar5 = *(long **)(in_RSI + 0x30);
        uVar4 = 0;
        while( true ) {
          plVar6 = (long *)((long)plVar5 + lVar8);
          if (uVar1 <= uVar7) {
            plVar6 = plVar5;
          }
          if (*(uint *)(*plVar6 + 0x20) <= uVar4) break;
          plVar6 = (long *)((long)plVar5 + lVar8);
          if (uVar1 <= uVar7) {
            plVar6 = plVar5;
          }
          lVar3 = *plVar6;
          if (uVar4 < *(uint *)(lVar3 + 0x24)) {
            iVar2 = *(int *)(*(long *)((ulong)uVar4 * 8 + *(long *)(lVar3 + 0x18)) + 0x1c);
          }
          else {
            iVar2 = *(int *)(**(long **)(lVar3 + 0x18) + 0x1c);
          }
          if (iVar2 == 0x71) {
            if (uVar7 < uVar1) {
              lVar8 = plVar5[uVar7];
              uVar1 = *(uint *)(lVar8 + 0x24);
            }
            else {
              lVar8 = *plVar5;
              uVar1 = *(uint *)(lVar8 + 0x24);
            }
            if (uVar4 < uVar1) {
              plVar5 = (long *)((ulong)uVar4 * 8 + *(long *)(lVar8 + 0x18));
            }
            else {
              plVar5 = *(long **)(lVar8 + 0x18);
            }
            std::wstring::wstring(in_RDI,(wstring_conflict *)(*plVar5 + 0x80));
            return;
          }
          uVar4 = uVar4 + 1;
        }
      }
      uVar7 = uVar7 + 1;
      lVar8 = lVar8 + 8;
    } while (uVar7 < *(uint *)(in_RSI + 0x38));
  }
  std::wstring::wstring(in_RDI,(wstring_conflict *)&::EMPTY_WSTRING);
  return;
}



/* address=00cac040
   symbol=CSkillEffectAndAffixes::applyAffixesAndEffects */

/* CSkillEffectAndAffixes::applyAffixesAndEffects(CBaseUnit*, CCharacter*, Ogre::Vector3 const*,
   bool) */

undefined1 __thiscall
CSkillEffectAndAffixes::applyAffixesAndEffects
          (CSkillEffectAndAffixes *this,CBaseUnit *param_1,CCharacter *param_2,Vector3 *param_3,
          bool param_4)

{
  bool bVar1;
  char cVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  CCharacter *this_00;
  CAffix *this_01;
  undefined8 *puVar6;
  iUnitObserver *piVar7;
  long lVar8;
  long *plVar9;
  long *plVar10;
  CLevel *pCVar11;
  uint uVar12;
  ulong uVar13;
  uint uVar14;
  ulong uVar15;
  long lVar16;
  undefined1 local_42;

  local_42 = 0;
  if (param_1 != (CBaseUnit *)0x0) {
    bVar1 = false;
    this_00 = (CCharacter *)0x0;
    if (*(int *)(param_1 + 0x188) == 0) {
      this_00 = (CCharacter *)param_1;
    }
    if (*(int *)(this + 0x20) != 0) {
      uVar14 = 0;
      do {
        if (uVar14 < *(uint *)(this + 0x24)) {
          plVar9 = (long *)((ulong)uVar14 * 8 + *(long *)(this + 0x18));
        }
        else {
          plVar9 = *(long **)(this + 0x18);
        }
        cVar2 = CBaseUnit::ISA(param_1,*(undefined4 *)(*plVar9 + 0x1c));
        if (cVar2 != '\0') {
          if (param_4) {
            uVar3 = *(uint *)(this + 0x24);
LAB_00cac0da:
            if (uVar14 < uVar3) goto LAB_00cac700;
LAB_00cac0e3:
            lVar16 = **(long **)(this + 0x18);
            uVar3 = *(uint *)(lVar16 + 0x18);
          }
          else {
            uVar3 = *(uint *)(this + 0x24);
            if (uVar14 < uVar3) {
              iVar4 = *(int *)(*(long *)((ulong)uVar14 * 8 + *(long *)(this + 0x18)) + 0x20);
              iVar5 = iVar4 + -1;
              if (iVar5 == 0) {
LAB_00cac7ba:
                if ((param_2 == (CCharacter *)0x0) ||
                   ((this_00 != param_2 && (this_00 != (CCharacter *)0x0)))) goto LAB_00cac200;
                goto LAB_00cac0da;
              }
            }
            else {
              iVar4 = *(int *)(**(long **)(this + 0x18) + 0x20);
              iVar5 = iVar4 + -1;
              if (iVar4 == 1) goto LAB_00cac7ba;
            }
            if (SBORROW4(iVar4,1) == iVar5 < 0) {
              if (iVar4 == 2) {
                if (((this_00 == (CCharacter *)0x0) || (param_2 == (CCharacter *)0x0)) ||
                   (param_2 != *(CCharacter **)(this_00 + 0x640))) goto LAB_00cac200;
              }
              else if (iVar4 == 4) {
                if ((param_2 != (CCharacter *)0x0) && (this_00 != (CCharacter *)0x0)) {
                  cVar2 = CCharacter::isEnemy(this_00,param_2);
                  if ((cVar2 != '\0') || (this_00 == param_2)) goto LAB_00cac200;
                  uVar3 = *(uint *)(this + 0x24);
                }
                goto LAB_00cac6f0;
              }
              goto LAB_00cac0da;
            }
            if (iVar4 != 0) goto LAB_00cac0da;
            if ((param_2 != (CCharacter *)0x0) && (this_00 != (CCharacter *)0x0)) {
              iVar4 = CCharacter::alignment(this_00);
              iVar5 = CCharacter::alignment(param_2);
              if (iVar4 == iVar5) goto LAB_00cac200;
              uVar3 = *(uint *)(this + 0x24);
            }
LAB_00cac6f0:
            if (uVar3 <= uVar14) goto LAB_00cac0e3;
LAB_00cac700:
            lVar16 = *(long *)(*(long *)(this + 0x18) + (ulong)uVar14 * 8);
            uVar3 = *(uint *)(lVar16 + 0x18);
          }
          this_01 = (CAffix *)
                    CResourceManager::getNewAffixByName
                              (*(CResourceManager **)(param_2 + 0x68),
                               (wstring_conflict *)(lVar16 + 0x10),uVar3);
          if (this_01 != (CAffix *)0x0) {
            CAffix::setSkillOwner(this_01,*(CSkill **)(this + 0x10));
            if (uVar14 < *(uint *)(this + 0x24)) {
              plVar9 = (long *)((ulong)uVar14 * 8 + *(long *)(this + 0x18));
            }
            else {
              plVar9 = *(long **)(this + 0x18);
            }
            CAffix::setLevel(this_01,*(uint *)(*plVar9 + 0x18));
            CAffix::setDirection(this_01,param_3);
            if (this_01[0xa8] == (CAffix)0x0) {
              uVar3 = *(uint *)(this + 0x24);
              if (uVar14 < uVar3) {
                plVar9 = *(long **)(this + 0x18);
                plVar10 = plVar9 + uVar14;
              }
              else {
                plVar9 = *(long **)(this + 0x18);
                plVar10 = plVar9;
              }
              if (0.0 < *(float *)(*plVar10 + 0x24)) {
                if (uVar14 < uVar3) {
                  plVar9 = plVar9 + uVar14;
                }
                *(undefined4 *)(this_01 + 0xa4) = *(undefined4 *)(*plVar9 + 0x24);
                goto LAB_00cac17d;
              }
            }
            else {
LAB_00cac17d:
              uVar3 = *(uint *)(this + 0x24);
              plVar9 = *(long **)(this + 0x18);
            }
            if (uVar14 < uVar3) {
              plVar9 = plVar9 + uVar14;
            }
            CBaseUnit::addAffix(param_1,this_01,*(uint *)(*plVar9 + 0x18),(CBaseUnit *)param_2,
                                DAT_00fa8760);
            cVar2 = CAffix::effectHasDuration(this_01,0x34);
            if ((cVar2 == '\0') && (cVar2 = CAffix::effectHasDuration(this_01,7), cVar2 == '\0')) {
              cVar2 = CAffix::effectHasDuration(this_01,0x7c);
              local_42 = 1;
              if (cVar2 == '\0') goto LAB_00cac200;
            }
            piVar7 = (iUnitObserver *)(*(long *)(this + 0x10) + 0x10);
            if (*(long *)(this + 0x10) == 0) {
              piVar7 = (iUnitObserver *)0x0;
            }
            pCVar11 = (CLevel *)0x0;
            if (*(long *)(param_1 + 0x68) != 0) {
              pCVar11 = *(CLevel **)(*(long *)(param_1 + 0x68) + 0x18);
            }
            CLevel::addListenerToUnit(pCVar11,param_1,piVar7);
            bVar1 = true;
            local_42 = 1;
          }
        }
LAB_00cac200:
        uVar14 = uVar14 + 1;
      } while (uVar14 < *(uint *)(this + 0x20));
    }
    if (*(int *)(this + 0x38) != 0) {
      uVar14 = 0;
LAB_00cac228:
      if (uVar14 < *(uint *)(this + 0x3c)) {
        plVar9 = (long *)((ulong)uVar14 * 8 + *(long *)(this + 0x30));
      }
      else {
        plVar9 = *(long **)(this + 0x30);
      }
      cVar2 = CBaseUnit::ISA(param_1,*(undefined4 *)(*plVar9 + 0x30));
      if (cVar2 == '\0') goto LAB_00cac4e8;
      if (param_4) {
        uVar3 = *(uint *)(this + 0x3c);
LAB_00cac25a:
        if (uVar14 < uVar3) {
          plVar9 = (long *)((ulong)uVar14 * 8 + *(long *)(this + 0x30));
        }
        else {
          plVar9 = *(long **)(this + 0x30);
        }
        if (*(int *)(*plVar9 + 0x20) != 0) {
          uVar15 = (ulong)uVar14;
          plVar9 = *(long **)(this + 0x30);
          uVar13 = 0;
          lVar16 = uVar15 * 8;
          while( true ) {
            plVar10 = plVar9 + uVar15;
            if (uVar3 <= uVar14) {
              plVar10 = plVar9;
            }
            uVar12 = (uint)uVar13;
            if (*(uint *)(*plVar10 + 0x20) <= uVar12) break;
            if (param_3 != (Vector3 *)0x0) {
              if (uVar14 < uVar3) {
                plVar9 = plVar9 + uVar15;
              }
              lVar8 = *plVar9;
              if (uVar12 < *(uint *)(lVar8 + 0x24)) {
                puVar6 = (undefined8 *)(uVar13 * 8 + *(long *)(lVar8 + 0x18));
              }
              else {
                puVar6 = *(undefined8 **)(lVar8 + 0x18);
              }
              cVar2 = (**(code **)(*(long *)param_1 + 0x238))(param_1,param_2,param_2,*puVar6);
              if (cVar2 != '\0') {
                if (uVar14 < *(uint *)(this + 0x3c)) {
                  plVar9 = (long *)(lVar16 + *(long *)(this + 0x30));
                }
                else {
                  plVar9 = *(long **)(this + 0x30);
                }
                lVar8 = *plVar9;
                if (uVar12 < *(uint *)(lVar8 + 0x24)) {
                  plVar9 = (long *)(uVar13 * 8 + *(long *)(lVar8 + 0x18));
                }
                else {
                  plVar9 = *(long **)(lVar8 + 0x18);
                }
                lVar8 = *plVar9;
                *(undefined4 *)(lVar8 + 0x98) = *(undefined4 *)param_3;
                *(undefined4 *)(lVar8 + 0x9c) = *(undefined4 *)(param_3 + 4);
                *(undefined4 *)(lVar8 + 0xa0) = *(undefined4 *)(param_3 + 8);
              }
              uVar3 = *(uint *)(this + 0x3c);
              plVar9 = *(long **)(this + 0x30);
            }
            if (uVar14 < uVar3) {
              plVar9 = plVar9 + uVar15;
            }
            lVar8 = *plVar9;
            if (uVar12 < *(uint *)(lVar8 + 0x24)) {
              CEffect::setSkillOwner
                        (*(CEffect **)(uVar13 * 8 + *(long *)(lVar8 + 0x18)),
                         *(CSkill **)(this + 0x10));
              if (uVar14 < *(uint *)(this + 0x3c)) goto LAB_00cac3f0;
LAB_00cac2a6:
              lVar8 = **(long **)(this + 0x30);
              if (*(uint *)(lVar8 + 0x24) <= uVar12) goto LAB_00cac2b7;
LAB_00cac404:
              puVar6 = (undefined8 *)(uVar13 * 8 + *(long *)(lVar8 + 0x18));
            }
            else {
              CEffect::setSkillOwner
                        ((CEffect *)**(undefined8 **)(lVar8 + 0x18),*(CSkill **)(this + 0x10));
              if (*(uint *)(this + 0x3c) <= uVar14) goto LAB_00cac2a6;
LAB_00cac3f0:
              lVar8 = *(long *)(lVar16 + *(long *)(this + 0x30));
              if (uVar12 < *(uint *)(lVar8 + 0x24)) goto LAB_00cac404;
LAB_00cac2b7:
              puVar6 = *(undefined8 **)(lVar8 + 0x18);
            }
            CEffect::setOwner((CEffect *)*puVar6,(CBaseUnit *)param_2,true);
            if (uVar14 < *(uint *)(this + 0x3c)) {
              plVar9 = (long *)(lVar16 + *(long *)(this + 0x30));
            }
            else {
              plVar9 = *(long **)(this + 0x30);
            }
            lVar8 = *plVar9;
            if (uVar12 < *(uint *)(lVar8 + 0x24)) {
              puVar6 = (undefined8 *)(uVar13 * 8 + *(long *)(lVar8 + 0x18));
            }
            else {
              puVar6 = *(undefined8 **)(lVar8 + 0x18);
            }
            cVar2 = (**(code **)(*(long *)param_1 + 0x240))(param_1,param_2,param_2,*puVar6);
            if (cVar2 == '\0') {
              plVar9 = *(long **)(this + 0x30);
              uVar3 = *(uint *)(this + 0x3c);
            }
            else if (bVar1) {
              plVar9 = *(long **)(this + 0x30);
              local_42 = 1;
              uVar3 = *(uint *)(this + 0x3c);
            }
            else {
              uVar3 = *(uint *)(this + 0x3c);
              if (uVar14 < uVar3) {
                plVar9 = *(long **)(this + 0x30);
                plVar10 = plVar9 + uVar15;
              }
              else {
                plVar10 = *(long **)(this + 0x30);
                plVar9 = plVar10;
              }
              lVar8 = *plVar10;
              if (uVar12 < *(uint *)(lVar8 + 0x24)) {
                plVar10 = (long *)(uVar13 * 8 + *(long *)(lVar8 + 0x18));
              }
              else {
                plVar10 = *(long **)(lVar8 + 0x18);
              }
              if (0.0 < *(float *)(*plVar10 + 0x24)) {
                plVar10 = plVar9 + uVar15;
                if (uVar3 <= uVar14) {
                  plVar10 = plVar9;
                }
                lVar8 = *plVar10;
                if (uVar12 < *(uint *)(lVar8 + 0x24)) {
                  plVar10 = (long *)(uVar13 * 8 + *(long *)(lVar8 + 0x18));
                }
                else {
                  plVar10 = *(long **)(lVar8 + 0x18);
                }
                if (*(int *)(*plVar10 + 0x1c) != 0x34) {
                  plVar10 = plVar9 + uVar15;
                  if (uVar3 <= uVar14) {
                    plVar10 = plVar9;
                  }
                  lVar8 = *plVar10;
                  if (uVar12 < *(uint *)(lVar8 + 0x24)) {
                    plVar10 = (long *)(uVar13 * 8 + *(long *)(lVar8 + 0x18));
                  }
                  else {
                    plVar10 = *(long **)(lVar8 + 0x18);
                  }
                  if (*(int *)(*plVar10 + 0x1c) != 7) {
                    plVar10 = plVar9 + uVar15;
                    if (uVar3 <= uVar14) {
                      plVar10 = plVar9;
                    }
                    lVar8 = *plVar10;
                    if (uVar12 < *(uint *)(lVar8 + 0x24)) {
                      plVar10 = (long *)(uVar13 * 8 + *(long *)(lVar8 + 0x18));
                    }
                    else {
                      plVar10 = *(long **)(lVar8 + 0x18);
                    }
                    if (*(int *)(*plVar10 + 0x1c) != 0x7c) goto LAB_00cac554;
                  }
                }
                piVar7 = (iUnitObserver *)(*(long *)(this + 0x10) + 0x10);
                if (*(long *)(this + 0x10) == 0) {
                  piVar7 = (iUnitObserver *)0x0;
                }
                pCVar11 = (CLevel *)0x0;
                if (*(long *)(param_1 + 0x68) != 0) {
                  pCVar11 = *(CLevel **)(*(long *)(param_1 + 0x68) + 0x18);
                }
                CLevel::addListenerToUnit(pCVar11,param_1,piVar7);
                plVar9 = *(long **)(this + 0x30);
                bVar1 = true;
                local_42 = 1;
                uVar3 = *(uint *)(this + 0x3c);
              }
              else {
LAB_00cac554:
                local_42 = 1;
              }
            }
            uVar13 = (ulong)(uVar12 + 1);
          }
        }
      }
      else {
        uVar3 = *(uint *)(this + 0x3c);
        if (uVar3 <= uVar14) {
          iVar4 = *(int *)(**(long **)(this + 0x30) + 0x34);
          iVar5 = iVar4 + -1;
          if (iVar4 != 1) goto LAB_00cac491;
LAB_00cac76a:
          if ((this_00 == param_2) || (this_00 == (CCharacter *)0x0)) goto LAB_00cac25a;
          uVar14 = uVar14 + 1;
          if (*(uint *)(this + 0x38) <= uVar14) {
            return local_42;
          }
          goto LAB_00cac228;
        }
        iVar4 = *(int *)(*(long *)((ulong)uVar14 * 8 + *(long *)(this + 0x30)) + 0x34);
        iVar5 = iVar4 + -1;
        if (iVar5 == 0) goto LAB_00cac76a;
LAB_00cac491:
        if (SBORROW4(iVar4,1) != iVar5 < 0) {
          if (((iVar4 == 0) && (param_2 != (CCharacter *)0x0)) && (this_00 != (CCharacter *)0x0)) {
            iVar4 = CCharacter::alignment(this_00);
            iVar5 = CCharacter::alignment(param_2);
            if (iVar4 == iVar5) goto LAB_00cac4e8;
LAB_00cac888:
            uVar3 = *(uint *)(this + 0x3c);
          }
          goto LAB_00cac25a;
        }
        if (iVar4 != 2) {
          if (((iVar4 != 4) || (param_2 == (CCharacter *)0x0)) || (this_00 == (CCharacter *)0x0))
          goto LAB_00cac25a;
          cVar2 = CCharacter::isEnemy(this_00,param_2);
          if ((cVar2 == '\0') && (this_00 != param_2)) goto LAB_00cac888;
          goto LAB_00cac4e8;
        }
        if ((this_00 != (CCharacter *)0x0) && (param_2 != (CCharacter *)0x0)) {
          if (param_2 == *(CCharacter **)(this_00 + 0x640)) goto LAB_00cac25a;
          uVar14 = uVar14 + 1;
          if (*(uint *)(this + 0x38) <= uVar14) {
            return local_42;
          }
          goto LAB_00cac228;
        }
      }
LAB_00cac4e8:
      uVar14 = uVar14 + 1;
      if (*(uint *)(this + 0x38) <= uVar14) {
        return local_42;
      }
      goto LAB_00cac228;
    }
  }
  return local_42;
}



/* address=00cac960
   symbol=CSkillEffectAndAffixes::isDamaging */

/* CSkillEffectAndAffixes::isDamaging() */

undefined8 __thiscall CSkillEffectAndAffixes::isDamaging(CSkillEffectAndAffixes *this)

{
  long lVar1;
  char cVar2;
  uint uVar3;
  undefined8 *puVar4;
  uint uVar5;
  uint uVar6;
  ulong uVar7;
  long lVar8;
  long *plVar9;

  if (*(int *)(this + 0x50) != 0) {
    uVar7 = 0;
    do {
      uVar6 = (uint)uVar7;
      if (uVar6 < *(uint *)(this + 0x54)) {
        puVar4 = (undefined8 *)(uVar7 * 8 + *(long *)(this + 0x48));
      }
      else {
        puVar4 = *(undefined8 **)(this + 0x48);
      }
      cVar2 = CAffix::effectExists((CAffix *)*puVar4,0x34);
      if (cVar2 != '\0') {
        return 1;
      }
      if (uVar6 < *(uint *)(this + 0x54)) {
        puVar4 = (undefined8 *)(uVar7 * 8 + *(long *)(this + 0x48));
      }
      else {
        puVar4 = *(undefined8 **)(this + 0x48);
      }
      cVar2 = CAffix::effectExists((CAffix *)*puVar4,7);
      if (cVar2 != '\0') {
        return 1;
      }
      if (uVar6 < *(uint *)(this + 0x54)) {
        puVar4 = (undefined8 *)(uVar7 * 8 + *(long *)(this + 0x48));
      }
      else {
        puVar4 = *(undefined8 **)(this + 0x48);
      }
      cVar2 = CAffix::effectExists((CAffix *)*puVar4,0x7c);
      if (cVar2 != '\0') {
        return 1;
      }
      uVar7 = (ulong)(uVar6 + 1);
    } while (uVar6 + 1 < *(uint *)(this + 0x50));
  }
  if (*(uint *)(this + 0x38) != 0) {
    uVar6 = *(uint *)(this + 0x3c);
    lVar8 = 0;
    uVar5 = 0;
    do {
      if (uVar5 < uVar6) {
        plVar9 = (long *)(lVar8 + *(long *)(this + 0x30));
      }
      else {
        plVar9 = *(long **)(this + 0x30);
      }
      uVar3 = 0;
      if (*(int *)(*plVar9 + 0x20) != 0) {
        if (uVar5 < uVar6) goto LAB_00cacade;
        do {
          plVar9 = *(long **)(this + 0x30);
          while( true ) {
            if (*(uint *)(*plVar9 + 0x20) <= uVar3) goto LAB_00caca16;
            if (uVar5 < uVar6) {
              plVar9 = (long *)(lVar8 + *(long *)(this + 0x30));
            }
            else {
              plVar9 = *(long **)(this + 0x30);
            }
            lVar1 = *plVar9;
            if (uVar3 < *(uint *)(lVar1 + 0x24)) {
              plVar9 = (long *)((ulong)uVar3 * 8 + *(long *)(lVar1 + 0x18));
            }
            else {
              plVar9 = *(long **)(lVar1 + 0x18);
            }
            if (*(int *)(*plVar9 + 0x1c) == 0x34) {
              return 1;
            }
            if (uVar5 < uVar6) {
              plVar9 = (long *)(lVar8 + *(long *)(this + 0x30));
            }
            else {
              plVar9 = *(long **)(this + 0x30);
            }
            lVar1 = *plVar9;
            if (uVar3 < *(uint *)(lVar1 + 0x24)) {
              plVar9 = (long *)((ulong)uVar3 * 8 + *(long *)(lVar1 + 0x18));
            }
            else {
              plVar9 = *(long **)(lVar1 + 0x18);
            }
            if (*(int *)(*plVar9 + 0x1c) == 7) {
              return 1;
            }
            if (uVar5 < uVar6) {
              plVar9 = (long *)(lVar8 + *(long *)(this + 0x30));
            }
            else {
              plVar9 = *(long **)(this + 0x30);
            }
            lVar1 = *plVar9;
            if (uVar3 < *(uint *)(lVar1 + 0x24)) {
              plVar9 = (long *)((ulong)uVar3 * 8 + *(long *)(lVar1 + 0x18));
            }
            else {
              plVar9 = *(long **)(lVar1 + 0x18);
            }
            if (*(int *)(*plVar9 + 0x1c) == 0x7c) {
              return 1;
            }
            uVar3 = uVar3 + 1;
            if (uVar6 <= uVar5) break;
LAB_00cacade:
            plVar9 = (long *)(lVar8 + *(long *)(this + 0x30));
          }
        } while( true );
      }
LAB_00caca16:
      uVar5 = uVar5 + 1;
      lVar8 = lVar8 + 8;
    } while (uVar5 < *(uint *)(this + 0x38));
  }
  return 0;
}



/* address=00cacb60
   symbol=CSkillEffectAndAffixes::removeAffixesAndEffects */

/* CSkillEffectAndAffixes::removeAffixesAndEffects(CBaseUnit*, CCharacter*) */

undefined8 CSkillEffectAndAffixes::removeAffixesAndEffects(CBaseUnit *param_1,CCharacter *param_2)

{
  char cVar1;
  uint uVar2;
  ulong uVar3;
  wstring_conflict *pwVar4;
  CEffectManager *this;
  undefined8 uVar5;

  if ((param_2 == (CCharacter *)0x0) ||
     (this = *(CEffectManager **)(param_2 + 0x1b8), this == (CEffectManager *)0x0)) {
    uVar5 = 0;
  }
  else {
    uVar5 = 0;
    if (*(int *)(param_1 + 0x68) != 0) {
      uVar3 = 0;
      while( true ) {
        if ((uint)uVar3 < *(uint *)(param_1 + 0x6c)) {
          pwVar4 = (wstring_conflict *)(uVar3 * 8 + *(long *)(param_1 + 0x60));
        }
        else {
          pwVar4 = *(wstring_conflict **)(param_1 + 0x60);
        }
        cVar1 = CEffectManager::deleteAffix(this,pwVar4);
        if (cVar1 != '\0') {
          uVar5 = 1;
        }
        uVar2 = (uint)uVar3 + 1;
        uVar3 = (ulong)uVar2;
        if (*(uint *)(param_1 + 0x68) <= uVar2) break;
        this = *(CEffectManager **)(param_2 + 0x1b8);
      }
    }
    if (*(int *)(param_1 + 0x80) != 0) {
      uVar2 = 0;
      do {
        if (uVar2 < *(uint *)(param_1 + 0x84)) {
          pwVar4 = (wstring_conflict *)((ulong)uVar2 * 8 + *(long *)(param_1 + 0x78));
        }
        else {
          pwVar4 = *(wstring_conflict **)(param_1 + 0x78);
        }
        cVar1 = CEffectManager::removeEffect(*(CEffectManager **)(param_2 + 0x1b8),pwVar4,true);
        if (cVar1 != '\0') {
          uVar5 = 1;
        }
        uVar2 = uVar2 + 1;
      } while (uVar2 < *(uint *)(param_1 + 0x80));
    }
  }
  return uVar5;
}



/* address=00cb2b50
   symbol=CSkillEffectAndAffixes::_GLOBAL__I_CSkillEffectAndAffixes */

/* CSkillEffectAndAffixes::CSkillEffectAndAffixes(CSkill*, CDataGroup*, CSkillEffectAndAffixes*) */

void CSkillEffectAndAffixes::_GLOBAL__I_CSkillEffectAndAffixes(void)

{
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
  std::string::string((string *)::KLayoutFunctionNames,"GUIEXITGAME",&aStack_233);
  std::string::string((string *)(::KLayoutFunctionNames + 8),"GUIEXITAPPLICATION",&aStack_232);
  std::string::string((string *)(::KLayoutFunctionNames + 0x10),"GUINEWGAME",&aStack_231);
  std::string::string((string *)(::KLayoutFunctionNames + 0x18),"GUICONTINUEGAME",&aStack_230);
  std::string::string((string *)(::KLayoutFunctionNames + 0x20),"GUINEWGAMEMENU",&aStack_22f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x28),"GUICONTINUEGAMEMENU",&aStack_22e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x30),"GUICLOSEMENU",&aStack_22d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x38),"GUIBACK",&aStack_22c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x40),"GUIDECLINE",&aStack_22b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x48),"GUIACCEPT",&aStack_22a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x50),"GUIOK",&aStack_229);
  std::string::string((string *)(::KLayoutFunctionNames + 0x58),"GUIPAUSE",&aStack_228);
  std::string::string((string *)(::KLayoutFunctionNames + 0x60),"GUISCROLLUP",&aStack_227);
  std::string::string((string *)(::KLayoutFunctionNames + 0x68),"GUISCROLLDOWN",&aStack_226);
  std::string::string((string *)(::KLayoutFunctionNames + 0x70),"GUISELECT1",&aStack_225);
  std::string::string((string *)(::KLayoutFunctionNames + 0x78),"GUISELECT2",&aStack_224);
  std::string::string((string *)(::KLayoutFunctionNames + 0x80),"GUISELECT3",&aStack_223);
  std::string::string((string *)(::KLayoutFunctionNames + 0x88),"GUISELECT4",&aStack_222);
  std::string::string((string *)(::KLayoutFunctionNames + 0x90),"GUISELECT5",&aStack_221);
  std::string::string((string *)(::KLayoutFunctionNames + 0x98),"GUISELECT6",&aStack_220);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa0),"GUISELECT7",&aStack_21f);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa8),"GUISELECT8",&aStack_21e);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb0),"GUISELECT9",&aStack_21d);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb8),"GUISELECT10",&aStack_21c);
  std::string::string((string *)(::KLayoutFunctionNames + 0xc0),"GUISELECT11",&aStack_21b);
  std::string::string((string *)(::KLayoutFunctionNames + 200),"GUISELECT12",&aStack_21a);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd0),"GUISELECT13",&aStack_219);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd8),"GUISELECT14",&aStack_218);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe0),"GUISELECT15",&aStack_217);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe8),"GUISELECT16",&aStack_216);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf0),"GUISELECT17",&aStack_215);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf8),"GUISELECT18",&aStack_214);
  std::string::string((string *)(::KLayoutFunctionNames + 0x100),"GUISELECT19",&aStack_213);
  std::string::string((string *)(::KLayoutFunctionNames + 0x108),"GUISELECT20",&aStack_212);
  std::string::string((string *)(::KLayoutFunctionNames + 0x110),"GUISELECT21",&aStack_211);
  std::string::string((string *)(::KLayoutFunctionNames + 0x118),"GUISELECT22",&aStack_210);
  std::string::string((string *)(::KLayoutFunctionNames + 0x120),"GUISELECT23",&aStack_20f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x128),"GUISELECT24",&aStack_20e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x130),"GUISELECT25",&aStack_20d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x138),"GUISELECT26",&aStack_20c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x140),"GUISELECT27",&aStack_20b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x148),"GUISELECT28",&aStack_20a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x150),"GUISELECT29",&aStack_209);
  std::string::string((string *)(::KLayoutFunctionNames + 0x158),"GUISELECT30",&aStack_208);
  std::string::string((string *)(::KLayoutFunctionNames + 0x160),"GUISELECT31",&aStack_207);
  std::string::string((string *)(::KLayoutFunctionNames + 0x168),"GUISELECT32",&aStack_206);
  std::string::string((string *)(::KLayoutFunctionNames + 0x170),"GUISELECT33",&aStack_205);
  std::string::string((string *)(::KLayoutFunctionNames + 0x178),"GUISELECT34",&aStack_204);
  std::string::string((string *)(::KLayoutFunctionNames + 0x180),"GUISELECT35",&aStack_203);
  std::string::string((string *)(::KLayoutFunctionNames + 0x188),"GUISELECT36",&aStack_202);
  std::string::string((string *)(::KLayoutFunctionNames + 400),"GUISELECT37",&aStack_201);
  std::string::string((string *)(::KLayoutFunctionNames + 0x198),"GUISELECT38",&aStack_200);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a0),"GUISELECT39",&aStack_1ff);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a8),"GUISELECT40",&aStack_1fe);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b0),"GUISELECT41",&aStack_1fd);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b8),"GUISELECT42",&aStack_1fc);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c0),"GUISELECT43",&aStack_1fb);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c8),"GUISELECT44",&aStack_1fa);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d0),"GUISELECT45",&aStack_1f9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d8),"GUISELECT46",&aStack_1f8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e0),"GUISELECT47",&aStack_1f7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e8),"GUISELECT48",&aStack_1f6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f0),"GUISELECT49",&aStack_1f5);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f8),"GUISELECT50",&aStack_1f4);
  std::string::string((string *)(::KLayoutFunctionNames + 0x200),"GUISELECTA",&aStack_1f3);
  std::string::string((string *)(::KLayoutFunctionNames + 0x208),"GUISELECTB",&aStack_1f2);
  std::string::string((string *)(::KLayoutFunctionNames + 0x210),"GUISELECTC",&aStack_1f1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x218),"GUISELECTD",&aStack_1f0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x220),"GUIFEEDPET",&aStack_1ef);
  std::string::string((string *)(::KLayoutFunctionNames + 0x228),"GUIPETPASSIVE",&aStack_1ee);
  std::string::string((string *)(::KLayoutFunctionNames + 0x230),"GUIPETAGGRESSIVE",&aStack_1ed);
  std::string::string((string *)(::KLayoutFunctionNames + 0x238),"GUIPETDEFENSIVE",&aStack_1ec);
  std::string::string((string *)(::KLayoutFunctionNames + 0x240),"GUITOGGLEINVENTORY",&aStack_1eb);
  std::string::string((string *)(::KLayoutFunctionNames + 0x248),"GUITOGGLEQUESTS",&aStack_1ea);
  std::string::string((string *)(::KLayoutFunctionNames + 0x250),"GUITOGGLESTATS",&aStack_1e9);
  std::string::string((string *)(::KLayoutFunctionNames + 600),"GUITOGGLESKILLS",&aStack_1e8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x260),"GUITOGGLEPERKS",&aStack_1e7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x268),"GUITOGGLEJOURNAL",&aStack_1e6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x270),"GUITOGGLEPET",&aStack_1e5);
  std::string::string((string *)(::KLayoutFunctionNames + 0x278),"GUITOGGLEAUTOMAP",&aStack_1e4);
  std::string::string((string *)(::KLayoutFunctionNames + 0x280),"GUITOGGLEOPTIONS",&aStack_1e3);
  std::string::string((string *)(::KLayoutFunctionNames + 0x288),"GUITOGGLEITEMNAMES",&aStack_1e2);
  std::string::string((string *)(::KLayoutFunctionNames + 0x290),"GUIAUTOMAPZOOMIN",&aStack_1e1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x298),"GUIAUTOMAPZOOMOUT",&aStack_1e0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a0),"GUILEVELUP",&aStack_1df);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a8),"GUISTATSUP",&aStack_1de);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b0),"GUISKILLUP",&aStack_1dd);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b8),"GUIPET1",&aStack_1dc);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c0),"GUIPET2",&aStack_1db);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c8),"GUIPET3",&aStack_1da);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d0),"GUIDELETE1",&aStack_1d9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d8),"GUIDELETE2",&aStack_1d8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e0),"GUIDELETE3",&aStack_1d7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e8),"GUIDELETE4",&aStack_1d6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f0),"GUISETTINGSMENU",&aStack_1d5);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f8),"GUIPETSELL",&aStack_1d4);
  std::string::string((string *)(::KLayoutFunctionNames + 0x300),"NONE",&aStack_1d3);
  __cxa_atexit(::__tcf_0,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSOUNDBANK_STRINGS,L"STEP_SOUND",&aStack_1d2);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 8),L"STRIKE_SOUND",&aStack_1d1);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x10),L"PHYSICALHIT_SOUND",&aStack_1d0);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x18),L"ICEHIT_SOUND",&aStack_1cf);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x20),L"FIREHIT_SOUND",&aStack_1ce);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x28),L"ELECTRICHIT_SOUND",&aStack_1cd);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x30),L"POISONHIT_SOUND",&aStack_1cc);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x38),L"SHIELDBLOCK",&aStack_1cb);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x40),L"BLOCK",&aStack_1ca);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x48),L"CRITICAL_SOUND",&aStack_1c9);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x50),L"ATTACK_SOUND",&aStack_1c8);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x58),L"IDLE_SOUND",&aStack_1c7)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x60),L"DEATH_SOUND",&aStack_1c6);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x68),L"ROAR_SOUND",&aStack_1c5)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x70),L"FLEE_SOUND",&aStack_1c4)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x78),L"MISS_SOUND",&aStack_1c3)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x80),L"FALL_SOUND",&aStack_1c2)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x88),L"LAND_SOUND",&aStack_1c1)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x90),L"TAKE_SOUND",&aStack_1c0)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x98),L"SPAWN_SOUND",&aStack_1bf);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa0),L"USE_SOUND",&aStack_1be);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa8),L"EQUIP_SOUND",&aStack_1bd);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb0),L"OPENMENU_SOUND",&aStack_1bc);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb8),L"BUY_SOUND",&aStack_1bb);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xc0),L"ERROR_SOUND",&aStack_1ba);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 200),L"LEVELUP_SOUND",&aStack_1b9);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd0),L"EFFORT_SOUND",&aStack_1b8);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd8),L"SPENDPOINT_SOUND",&aStack_1b7);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe0),L"PORTALENTER_SOUND",&aStack_1b6);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe8),L"POERTALEXIT_SOUND",&aStack_1b5);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf0),L"SKILLASSIGN_SOUND",&aStack_1b4);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf8),L"QUESTRECEIVED_SOUND",&aStack_1b3);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x100),L"QUESTCOMPLETED_SOUND",&aStack_1b2)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x108),L"LOWMANA_SOUND",&aStack_1b1);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x110),L"MISSILEREFLECT_SOUND",&aStack_1b0)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x118),L"BADEFFECT_SOUND",&aStack_1af);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x120),L"GOODEFFECT_SOUND",&aStack_1ae);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x128),L"NPCDIALOG_SOUND",&aStack_1ad);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x130),L"NPCGREET",&aStack_1ac);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x138),L"NPCBYE",&aStack_1ab);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x140),L"NPCPURCHASE",&aStack_1aa);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x148),L"NPCSELL",&aStack_1a9);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x150),L"VOICEPETINVENTORYFULL_SOUND",
             &aStack_1a8);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x158),L"VOICEPETDEPARTED_SOUND",
             &aStack_1a7);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x160),L"VOICEPETRETURNED_SOUND",
             &aStack_1a6);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x168),L"VOICEPETFLED_SOUND",&aStack_1a5);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x170),L"VOICEPETLEVELUP_SOUND",&aStack_1a4
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x178),L"VOICEINVENTORYFULL_SOUND",
             &aStack_1a3);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x180),L"VOICEINSUFFICIENTGOLD_SOUND",
             &aStack_1a2);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x188),L"VOICEIMPOSSIBLE_SOUND",&aStack_1a1
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 400),L"VOICECANTCAST_SOUND",&aStack_1a0);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x198),L"VOICECANTCASTHERE_SOUND",
             &aStack_19f);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a0),L"VOICEHEALTHLOW_SOUND",&aStack_19e)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a8),L"VOICEMANALOW_SOUND",&aStack_19d);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b0),L"VOICETRAPSPRUNG_SOUND",&aStack_19c
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b8),L"VOICEREFRESHED_SOUND",&aStack_19b)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c0),L"VOICEPOWERFUL_SOUND",&aStack_19a);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c8),L"VOICEHEALTHY_SOUND",&aStack_199);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d0),L"VOICEILL_SOUND",&aStack_198);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d8),L"VOICEPOISONED_SOUND",&aStack_197);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e0),L"VOICELEVELUP_SOUND",&aStack_196);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e8),L"VOICEFAMEUP_SOUND",&aStack_195);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f0),L"VOICESKILLUP_SOUND",&aStack_194);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f8),L"VOICEFORTUNEGOOD_SOUND",
             &aStack_193);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x200),L"VOICEFORTUNEBAD_SOUND",&aStack_192
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x208),L"VOICESPELLLEARNED_SOUND",
             &aStack_191);
  ::KSOUNDBANK_STRINGS._528_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_1,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KALIGNMENT_STRINGS,L"NEUTRAL",&aStack_190);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 8),L"GOOD",&aStack_18f);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x10),L"EVIL",&aStack_18e);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x18),L"ALL",&aStack_18d);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x20),L"BERSERK",&aStack_18c);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x28),L"EVILBERSERK",&aStack_18b);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x30),L"GOODBERSERK",&aStack_18a);
  __cxa_atexit(::__tcf_2,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KAITYPE_STRINGS,L"NORMAL",&aStack_189);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 8),L"RANGEDDEFENDER",&aStack_188);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x10),L"DEFENDER",&aStack_187);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x18),L"RANGEDCASTER",&aStack_186);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x20),L"CIRCLER",&aStack_185);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x28),L"RESURRECTER",&aStack_184);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x30),L"DUMMY",&aStack_183);
  __cxa_atexit(::__tcf_3,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gDAMAGE_TYPES,L"Physical",&aStack_182);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 8),L"Magical",&aStack_181);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x10),L"Fire",&aStack_180);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x18),L"Ice",&aStack_17f);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x20),L"Electric",&aStack_17e);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x28),L"Poison",&aStack_17d);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x30),L"All",&aStack_17c);
  __cxa_atexit(::__tcf_4,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::gTARGET_TYPES,L"USER",&aStack_17b);
  std::wstring::wstring((wstring_conflict *)&DAT_014f0008,L"ITEM",&aStack_17a);
  __cxa_atexit(::__tcf_5,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSFXTypeName,L"STATIONARYTARGET",&aStack_179);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 8),L"STATIONARYOWNER",&aStack_178);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x10),L"STATIONARY",&aStack_177);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x18),L"STATIONARYPORTAL",&aStack_176)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x20),L"BEAM",&aStack_175);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x28),L"FOLLOWOWNER",&aStack_174);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x30),L"FOLLOWTARGET",&aStack_173);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x38),L"PROJECTILELOCATION",&aStack_172);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x40),L"PROJECTILECHARACTER",&aStack_171);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x48),L"PROJECTILELOCATIONERRATIC",&aStack_170);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x50),L"PROJECTILECHARACTERERRATIC",&aStack_16f);
  __cxa_atexit(::__tcf_6,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KCharacterNames,L"NA",&aStack_16e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 8),L"NA",&aStack_16d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x10),L"NA",&aStack_16c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x18),L"NA",&aStack_16b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x20),L"NA",&aStack_16a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x28),L"NA",&aStack_169);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x30),L"NA",&aStack_168);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x38),L"NA",&aStack_167);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x40),L"Bksp",&aStack_166);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x48),L"Tab",&aStack_165);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x50),L"NA",&aStack_164);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x58),L"NA",&aStack_163);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x60),L"Ctr",&aStack_162);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x68),L"Ret",&aStack_161);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x70),L"NA",&aStack_160);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x78),L"NA",&aStack_15f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x80),L"Shift",&aStack_15e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x88),L"Ctrl",&aStack_15d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x90),L"Alt",&aStack_15c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x98),L"Tab",&aStack_15b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa0),L"NA",&aStack_15a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa8),L"NA",&aStack_159);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb0),L"NA",&aStack_158);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb8),L"NA",&aStack_157);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xc0),L"NA",&aStack_156);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 200),L"NA",&aStack_155);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd0),L"NA",&aStack_154);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd8),L"NA",&aStack_153);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe0),L"NA",&aStack_152);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe8),L"NA",&aStack_151);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf0),L"NA",&aStack_150);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf8),L"NA",&aStack_14f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x100),L"space",&aStack_14e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x108),L"pgup",&aStack_14d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x110),L"pgdn",&aStack_14c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x118),L"end",&aStack_14b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x120),L"home",&aStack_14a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x128),L"left arrow",&aStack_149);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x130),L"up arrow",&aStack_148);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x138),L"right arrow",&aStack_147);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x140),L"down arrow",&aStack_146);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x148),L")",&aStack_145);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x150),L"*",&aStack_144);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x158),L"+",&aStack_143);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x160),L",",&aStack_142);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x168),L"ins",&aStack_141);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x170),L"del",&aStack_140);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x178),L"/",&aStack_13f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x180),L"0",&aStack_13e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x188),L"1",&aStack_13d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 400),L"2",&aStack_13c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x198),L"3",&aStack_13b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a0),L"4",&aStack_13a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a8),L"5",&aStack_139);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b0),L"6",&aStack_138);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b8),L"7",&aStack_137);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c0),L"8",&aStack_136);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c8),L"9",&aStack_135);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d0),L":",&aStack_134);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d8),L";",&aStack_133);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e0),L"<",&aStack_132);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e8),L"=",&aStack_131);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f0),L">",&aStack_130);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f8),L"?",&aStack_12f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x200),L"@",&aStack_12e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x208),L"a",&aStack_12d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x210),L"b",&aStack_12c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x218),L"c",&aStack_12b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x220),L"d",&aStack_12a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x228),L"e",&aStack_129);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x230),L"NA",&aStack_128);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x238),L"g",&aStack_127);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x240),L"h",&aStack_126);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x248),L"i",&aStack_125);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x250),L"j",&aStack_124);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 600),L"k",&aStack_123);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x260),L"l",&aStack_122);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x268),L"m",&aStack_121);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x270),L"n",&aStack_120);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x278),L"o",&aStack_11f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x280),L"p",&aStack_11e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x288),L"NA",&aStack_11d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x290),L"r",&aStack_11c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x298),L"s",&aStack_11b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a0),L"t",&aStack_11a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a8),L"u",&aStack_119);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b0),L"v",&aStack_118);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b8),L"w",&aStack_117);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c0),L"x",&aStack_116);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c8),L"y",&aStack_115);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d0),L"z",&aStack_114);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d8),L"[",&aStack_113);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e0),L"\\",&aStack_112);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e8),L"]",&aStack_111);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f0),L"^",&aStack_110);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f8),L"_",&aStack_10f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x300),L"NUM 0",&aStack_10e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x308),L"NUM 1",&aStack_10d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x310),L"NUM 2",&aStack_10c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x318),L"NUM 3",&aStack_10b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 800),L"NUM 4",&aStack_10a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x328),L"NUM 5",&aStack_109);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x330),L"NUM 6",&aStack_108);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x338),L"NUM 7",&aStack_107);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x340),L"NUM 8",&aStack_106);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x348),L"NUM 9",&aStack_105);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x350),L"*",&aStack_104);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x358),L"+",&aStack_103);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x360),L"NA",&aStack_102);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x368),L"-",&aStack_101);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x370),L"NA",&aStack_100);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x378),L"F1",&aStack_ff);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x380),L"F2",&aStack_fe);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x388),L"F3",&aStack_fd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x390),L"F4",&aStack_fc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x398),L"F5",&aStack_fb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a0),L"F6",&aStack_fa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a8),L"F7",&aStack_f9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b0),L"F8",&aStack_f8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b8),L"F9",&aStack_f7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c0),L"F10",&aStack_f6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c8),L"F11",&aStack_f5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d0),L"F12",&aStack_f4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d8),L"{",&aStack_f3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3e0),L"|",&aStack_f2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 1000),L"}",&aStack_f1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f0),L"~",&aStack_f0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f8),L";",&aStack_ef);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x400),L"=",&aStack_ee);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x408),L".",&aStack_ed);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x410),L"-",&aStack_ec);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x418),L",",&aStack_eb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x420),L"/",&aStack_ea);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x428),L"`",&aStack_e9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x430),L"[",&aStack_e8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x438),L"\\",&aStack_e7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x440),L"]",&aStack_e6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x448),L"\'",&aStack_e5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x450),L"NA",&aStack_e4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x458),L"NA",&aStack_e3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x460),L"NA",&aStack_e2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x468),L"NA",&aStack_e1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x470),L"NA",&aStack_e0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x478),L"NA",&aStack_df);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x480),L"NA",&aStack_de);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x488),L"NA",&aStack_dd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x490),L"NA",&aStack_dc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x498),L"NA",&aStack_db);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a0),L"NA",&aStack_da);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a8),L"NA",&aStack_d9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b0),L"NA",&aStack_d8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b8),L"NA",&aStack_d7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c0),L"NA",&aStack_d6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c8),L"NA",&aStack_d5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d0),L"NA",&aStack_d4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d8),L"NA",&aStack_d3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e0),L"NA",&aStack_d2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e8),L"NA",&aStack_d1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f0),L"NA",&aStack_d0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f8),L"NA",&aStack_cf);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x500),L"NA",&aStack_ce);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x508),L"NA",&aStack_cd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x510),L"NA",&aStack_cc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x518),L"NA",&aStack_cb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x520),L"NA",&aStack_ca);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x528),L"NA",&aStack_c9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x530),L"NA",&aStack_c8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x538),L"NA",&aStack_c7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x540),L"NA",&aStack_c6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x548),L"NA",&aStack_c5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x550),L"NA",&aStack_c4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x558),L"NA",&aStack_c3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x560),L"NA",&aStack_c2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x568),L"NA",&aStack_c1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x570),L"NA",&aStack_c0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x578),L"NA",&aStack_bf);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x580),L"NA",&aStack_be);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x588),L"NA",&aStack_bd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x590),L"NA",&aStack_bc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x598),L"NA",&aStack_bb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a0),L"NA",&aStack_ba);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a8),L"NA",&aStack_b9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b0),L"NA",&aStack_b8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b8),L"NA",&aStack_b7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c0),L"NA",&aStack_b6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c8),L"NA",&aStack_b5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d0),L";",&aStack_b4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d8),L"=",&aStack_b3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e0),L",",&aStack_b2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e8),L"-",&aStack_b1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f0),L".",&aStack_b0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f8),L"/",&aStack_af);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x600),L"`",&aStack_ae);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x608),L"NA",&aStack_ad);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x610),L"NA",&aStack_ac);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x618),L"NA",&aStack_ab);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x620),L"NA",&aStack_aa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x628),L"NA",&aStack_a9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x630),L"NA",&aStack_a8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x638),L"NA",&aStack_a7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x640),L"NA",&aStack_a6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x648),L"NA",&aStack_a5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x650),L"NA",&aStack_a4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x658),L"NA",&aStack_a3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x660),L"NA",&aStack_a2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x668),L"NA",&aStack_a1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x670),L"NA",&aStack_a0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x678),L"NA",&aStack_9f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x680),L"NA",&aStack_9e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x688),L"NA",&aStack_9d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x690),L"NA",&aStack_9c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x698),L"NA",&aStack_9b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a0),L"NA",&aStack_9a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a8),L"NA",&aStack_99);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b0),L"NA",&aStack_98);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b8),L"NA",&aStack_97);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c0),L"NA",&aStack_96);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c8),L"NA",&aStack_95);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d0),L"NA",&aStack_94);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d8),L"[",&aStack_93);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e0),L"\\",&aStack_92);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e8),L"]",&aStack_91);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f0),L"\'",&aStack_90);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f8),L"NA",&aStack_8f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x700),L"NA",&aStack_8e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x708),L"NA",&aStack_8d);
  __cxa_atexit(::__tcf_7,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_EVENT_TYPE_NAMES,L"EVENT_START",&aStack_8c);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 8),L"EVENT_END",&aStack_8b)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x10),L"EVENT_TRIGGER",&aStack_8a);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x18),L"EVENT_TRIGGER_TWO",&aStack_89)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x20),L"EVENT_UNITHIT",&aStack_88);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x28),L"EVENT_UNITDIE",&aStack_87);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x30),L"EVENT_MISSILEHIT",&aStack_86);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x38),L"EVENT_MISSILEDIE",&aStack_85);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x40),L"EVENT_DIEBYEFFECT",&aStack_84)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x48),L"EVENT_CASTERDIE",&aStack_83);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x50),L"EVENT_UNIT_CREATE",&aStack_82)
  ;
  __cxa_atexit(::__tcf_8,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_TARGET_TYPE_NAMES,L"NONE",&aStack_81);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 8),L"POSITION",&aStack_80)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x10),L"TARGET",&aStack_7f);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x18),L"SELF",&aStack_7e);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x20),L"EVERYBODY",&aStack_7d);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x28),L"POSITIONRANDOM",&aStack_7c);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x30),L"POSITIONFLEE",&aStack_7b);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x38),L"ITEM",&aStack_7a);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x40),L"UNIDENTIFIEDITEM",&aStack_79)
  ;
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x48),L"PETS",&aStack_78);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x50),L"SELFANDPETS",&aStack_77);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x58),L"TARGET_POS",&aStack_76);
  __cxa_atexit(::__tcf_9,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_ACTIVATION_TYPE_NAMES,L"ANY",&aStack_75);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 8),L"PROC",&aStack_74)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 0x10),L"WEAPON",&aStack_73);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 0x18),L"NORMAL",&aStack_72);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 0x20),L"PASSIVE",&aStack_71);
  __cxa_atexit(::__tcf_10,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_TYPE_NAMES,L"SKILL",&aStack_70);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TYPE_NAMES + 8),L"OFFENSIVE",&aStack_6f);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TYPE_NAMES + 0x10),L"DEFENSIVE",&aStack_6e);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TYPE_NAMES + 0x18),L"CHARM",&aStack_6d);
  ::gSKILL_TYPE_NAMES._32_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_11,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_TYPE_DISPLAY_NAMES,L"Class Skill",&aStack_6c);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TYPE_DISPLAY_NAMES + 8),L"Offensive Spell",&aStack_6b);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TYPE_DISPLAY_NAMES + 0x10),L"Defensive Spell",&aStack_6a)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TYPE_DISPLAY_NAMES + 0x18),L"Charm Spell",&aStack_69);
  ::gSKILL_TYPE_DISPLAY_NAMES._32_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_12,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_BONE_ATTACHMENT_NAMES,L"",&aStack_68);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 8),L"CENTER",&aStack_67);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x10),L"HEAD",&aStack_66);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x18),L"RIGHTHAND",&aStack_65);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x20),L"LEFTHAND",&aStack_64);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x28),L"RIGHTSHOULDER",&aStack_63
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x30),L"LEFTSHOULDER",&aStack_62)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x38),L"POSITION",&aStack_61);
  __cxa_atexit(::__tcf_13,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEffect_Activation_Names,L"PASSIVE",&aStack_60);
  std::wstring::wstring((wstring_conflict *)(::gEffect_Activation_Names + 8),L"DYNAMIC",&aStack_5f);
  std::wstring::wstring
            ((wstring_conflict *)(::gEffect_Activation_Names + 0x10),L"TRANSFER",&aStack_5e);
  __cxa_atexit(::__tcf_14,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEFFECT_STAT_MODIFIER_NAMES,L"MELEE",&aStack_5d);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 8),L"RANGED",&aStack_5c);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x10),L"DEFENSE",&aStack_5b);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x18),L"MAGIC",&aStack_5a);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x20),L"LEVEL",&aStack_59);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x28),L"OWNERLEVEL",&aStack_58);
  __cxa_atexit(::__tcf_15,0,&__dso_handle);
  std::string::string((string *)::gEFFECT_STAT_MODIFIER_ICON_NAMES,"iconmelee",&aStack_57);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 8),"iconranged",&aStack_56);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x10),"icondefense",&aStack_55
                     );
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x18),"iconmagic",&aStack_54);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x20),"iconmagic",&aStack_53);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x28),"iconmagic",&aStack_52);
  __cxa_atexit(::__tcf_16,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)&gSKILL_EFFECT_AND_AFFIXES_TARGET_NAMES,L"ENEMY",&aStack_51);
  std::wstring::wstring((wstring_conflict *)&DAT_014f0a08,L"SELF",&aStack_50);
  std::wstring::wstring((wstring_conflict *)&DAT_014f0a10,L"PET",&aStack_4f);
  std::wstring::wstring((wstring_conflict *)&DAT_014f0a18,L"EVERYBODY",&aStack_4e);
  std::wstring::wstring((wstring_conflict *)&DAT_014f0a20,L"FRIEND",&aStack_4d);
  __cxa_atexit(::__tcf_17,0,&__dso_handle);
  ParticleUniverse::HALFSCALE._4_4_ = DAT_0142463c * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._0_4_ = Ogre::Vector3::UNIT_SCALE * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._8_4_ = DAT_00fa4810 * DAT_01424640;
  std::string::string((string *)&ParticleUniverse::ALIAS,"1",&aStack_4c);
  __cxa_atexit(std::string::~string,&ParticleUniverse::ALIAS,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::SYSTEM,"2",&aStack_4b);
  __cxa_atexit(std::string::~string,&ParticleUniverse::SYSTEM,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::TECHNIQUE,"3",&aStack_4a);
  __cxa_atexit(std::string::~string,&ParticleUniverse::TECHNIQUE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::RENDERER,"4",&aStack_49);
  __cxa_atexit(std::string::~string,&ParticleUniverse::RENDERER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EMITTER,"5",&aStack_48);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EMITTER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::AFFECTOR,"6",&aStack_47);
  __cxa_atexit(std::string::~string,&ParticleUniverse::AFFECTOR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::OBSERVER,"7",&aStack_46);
  __cxa_atexit(std::string::~string,&ParticleUniverse::OBSERVER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::HANDLER,"8",&aStack_45);
  __cxa_atexit(std::string::~string,&ParticleUniverse::HANDLER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::BEHAVIOUR,"9",&aStack_44);
  __cxa_atexit(std::string::~string,&ParticleUniverse::BEHAVIOUR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EXTERN,"10",&aStack_43);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EXTERN,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DYNAMIC_ATTRIBUTE,"11",&aStack_42);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DYNAMIC_ATTRIBUTE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DEPENDENCY,"12",&aStack_41);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DEPENDENCY,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_TYPE_NAMES,L"",&aStack_40);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 8),L"FIND",&aStack_3f);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x10),L"KILL NUM",&aStack_3e);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x18),L"KILL BOSS",&aStack_3d);
  __cxa_atexit(::__tcf_18,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_DIALOG_TYPE_NAMES,L"ERROR",&aStack_3c);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 8),L"INTRO",&aStack_3b);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x10),L"RETURN",&aStack_3a);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x18),L"COMPLETE",&aStack_39);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x20),L"PASSIVE",&aStack_38);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x28),L"DETAILS",&aStack_37);
  __cxa_atexit(::__tcf_19,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES,"tag_righthand",&aStack_36);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 8),"tag_lefthand",&aStack_35);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x10),"",&aStack_34);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x18),"Bip01 Head",&aStack_33);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x20),"",&aStack_32);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x28),"Bip01 L Clavicle",&aStack_31);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x30),"",&aStack_30);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x38),"",&aStack_2f);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x40),"",&aStack_2e);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x48),"",&aStack_2d);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x50),"",&aStack_2c);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x58),"tag_leftarm",&aStack_2b);
  __cxa_atexit(::__tcf_20,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES_SECONDARY,"",&aStack_2a);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 8),"",&aStack_29);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x10),"",&aStack_28);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x18),"",&aStack_27);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x20),"",&aStack_26);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x28),"Bip01 R Clavicle",
                      &aStack_25);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x30),"",&aStack_24);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x38),"",&aStack_23);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x40),"",&aStack_22);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x48),"",&aStack_21);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x50),"",&aStack_20);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x58),"",&aStack_1f);
  __cxa_atexit(::__tcf_21,0,&__dso_handle);
  std::string::string((string *)::KEquipmentIconName,"EquipLeftHand",&aStack_1e);
  std::string::string((string *)(::KEquipmentIconName + 8),"EquipRightHand",&aStack_1d);
  std::string::string((string *)(::KEquipmentIconName + 0x10),"EquipGloves",&aStack_1c);
  std::string::string((string *)(::KEquipmentIconName + 0x18),"EquipHelm",&aStack_1b);
  std::string::string((string *)(::KEquipmentIconName + 0x20),"EquipChest",&aStack_1a);
  std::string::string((string *)(::KEquipmentIconName + 0x28),"EquipShoulder",&aStack_19);
  std::string::string((string *)(::KEquipmentIconName + 0x30),"EquipBoots",&aStack_18);
  std::string::string((string *)(::KEquipmentIconName + 0x38),"EquipBelt",&aStack_17);
  std::string::string((string *)(::KEquipmentIconName + 0x40),"EquipRing1",&aStack_16);
  std::string::string((string *)(::KEquipmentIconName + 0x48),"EquipRing2",&aStack_15);
  std::string::string((string *)(::KEquipmentIconName + 0x50),"EquipAmulet",&aStack_14);
  std::string::string((string *)(::KEquipmentIconName + 0x58),"",&aStack_13);
  __cxa_atexit(::__tcf_22,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames,L"CHEST",&aStack_12);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 8),L"GLOVES",&aStack_11);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x10),L"BOOTS",&aStack_10);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x18),L"HELMET",&aStack_f);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x20),L"SHOULDERS",&aStack_e);
  __cxa_atexit(::__tcf_23,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames2,L"",&aStack_d);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 8),L"",&aStack_c);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x10),L"",&aStack_b);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x18),L"FACE",&aStack_a);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x20),L"",&aStack_9);
  __cxa_atexit(::__tcf_24,0,&__dso_handle);
  return;
}



/* address=00cb37a0
   symbol=CSkillEffectAndAffixes::appendName */

/* WARNING: Removing unreachable block (ram,0x00cb38c2) */
/* CSkillEffectAndAffixes::appendName(std::wstring const&) */

void CSkillEffectAndAffixes::appendName(wstring_conflict *param_1)

{
  int *piVar1;
  int iVar2;
  long lVar3;
  long lVar4;
  long *plVar5;
  uint uVar6;
  ulong uVar7;
  uint uVar8;
  long local_48 [3];

  if (*(int *)(param_1 + 0x38) != 0) {
    uVar8 = 0;
    do {
      if (uVar8 < *(uint *)(param_1 + 0x3c)) {
        plVar5 = (long *)((ulong)uVar8 * 8 + *(long *)(param_1 + 0x30));
      }
      else {
        plVar5 = *(long **)(param_1 + 0x30);
      }
      lVar3 = *plVar5;
      if ((lVar3 != 0) && (*(int *)(lVar3 + 0x20) != 0)) {
        uVar7 = 0;
        do {
          if ((uint)uVar7 < *(uint *)(lVar3 + 0x24)) {
            plVar5 = (long *)(uVar7 * 8 + *(long *)(lVar3 + 0x18));
          }
          else {
            plVar5 = *(long **)(lVar3 + 0x18);
          }
          lVar4 = *plVar5;
          std::wstring::wstring((wstring_conflict *)local_48,(wstring_conflict *)(lVar4 + 0x80));
                    /* try { // try from 00cb381c to 00cb3820 has its CatchHandler @ 00cb38cd */
          std::wstring::append((wstring_conflict *)local_48);
                    /* try { // try from 00cb3827 to 00cb382b has its CatchHandler @ 00cb38e0 */
          std::wstring::assign((wstring_conflict *)(lVar4 + 0x80));
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
          uVar6 = (uint)uVar7 + 1;
          uVar7 = (ulong)uVar6;
        } while (uVar6 < *(uint *)(lVar3 + 0x20));
      }
      uVar8 = uVar8 + 1;
    } while (uVar8 < *(uint *)(param_1 + 0x38));
  }
  return;
}



/* address=00cb3980
   symbol=CSkillEffectAndAffixes::getDisplayStats */

/* WARNING: Removing unreachable block (ram,0x00cb3eaf) */
/* WARNING: Removing unreachable block (ram,0x00cb3e2b) */
/* WARNING: Removing unreachable block (ram,0x00cb3dbc) */
/* WARNING: Removing unreachable block (ram,0x00cb3efb) */
/* WARNING: Removing unreachable block (ram,0x00cb3ea4) */
/* CSkillEffectAndAffixes::getDisplayStats() */

wstring_conflict * CSkillEffectAndAffixes::getDisplayStats(void)

{
  wchar_t *pwVar1;
  wchar_t wVar2;
  size_t sVar3;
  size_t sVar4;
  long lVar5;
  int iVar6;
  undefined8 *puVar7;
  long *plVar8;
  uint uVar9;
  CSkillEffectAndAffixes *in_RSI;
  wstring_conflict *in_RDI;
  uint local_84;
  wchar_t *local_78 [2];
  wchar_t *local_68 [2];
  wchar_t *local_58 [2];
  wchar_t *local_48 [3];

  if (*(long *)(in_RSI + 0x10) == 0) {
    std::wstring::wstring(in_RDI,(wstring_conflict *)&::EMPTY_WSTRING);
  }
  else {
    createAffixesForDisplay(in_RSI,*(CResourceManager **)(*(long *)(in_RSI + 0x10) + 0x18));
    std::wstring::wstring((wstring_conflict *)local_48,(wstring_conflict *)(in_RSI + 0x90));
                    /* try { // try from 00cb39c0 to 00cb39fb has its CatchHandler @ 00cb3dd6 */
    CMasterResourceManager::getSingleton();
    if (*(int *)(in_RSI + 0x50) != 0) {
      uVar9 = 0;
      do {
        if (uVar9 < *(uint *)(in_RSI + 0x54)) {
          puVar7 = (undefined8 *)((ulong)uVar9 * 8 + *(long *)(in_RSI + 0x48));
        }
        else {
          puVar7 = *(undefined8 **)(in_RSI + 0x48);
        }
        CAffix::getDisplayStats((CAffix *)local_68,(uint)*puVar7);
        pwVar1 = ::EMPTY_WSTRING;
        sVar3 = *(size_t *)(::EMPTY_WSTRING + -6);
        if (*(size_t *)(local_48[0] + -6) == sVar3) {
          iVar6 = wmemcmp(local_48[0],::EMPTY_WSTRING,sVar3);
          if (iVar6 != 0) {
            sVar4 = *(size_t *)(local_68[0] + -6);
            goto joined_r0x00cb3a97;
          }
        }
        else {
          sVar4 = *(size_t *)(local_68[0] + -6);
joined_r0x00cb3a97:
          if ((sVar3 != sVar4) || (iVar6 = wmemcmp(local_68[0],pwVar1,sVar3), iVar6 != 0)) {
            wcslen(L"\n");
                    /* try { // try from 00cb3a35 to 00cb3a46 has its CatchHandler @ 00cb3deb */
            std::wstring::append((wchar_t *)local_48,0xfd0b48);
          }
        }
        std::wstring::append((wstring_conflict *)local_48);
        if ((allocator *)(local_68[0] + -6) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          pwVar1 = local_68[0] + -2;
          wVar2 = *pwVar1;
          *pwVar1 = *pwVar1 + L'\xffffffff';
          UNLOCK();
          if (wVar2 < L'\x01') {
            std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -6));
          }
        }
        uVar9 = uVar9 + 1;
      } while (uVar9 < *(uint *)(in_RSI + 0x50));
    }
                    /* try { // try from 00cb3ab8 to 00cb3abc has its CatchHandler @ 00cb3dd6 */
    std::wstring::wstring((wstring_conflict *)local_58,(wstring_conflict *)&::EMPTY_WSTRING);
    if (*(int *)(in_RSI + 0x38) != 0) {
      local_84 = 0;
      do {
                    /* try { // try from 00cb3ae8 to 00cb3aec has its CatchHandler @ 00cb3e1c */
        std::wstring::wstring((wstring_conflict *)local_68,(wstring_conflict *)&::EMPTY_WSTRING);
        if (local_84 < *(uint *)(in_RSI + 0x3c)) {
          plVar8 = (long *)((ulong)local_84 * 8 + *(long *)(in_RSI + 0x30));
        }
        else {
          plVar8 = *(long **)(in_RSI + 0x30);
        }
        lVar5 = *plVar8;
        if ((lVar5 != 0) && (*(int *)(lVar5 + 0x20) != 0)) {
          uVar9 = 0;
          do {
            if (uVar9 < *(uint *)(lVar5 + 0x24)) {
              puVar7 = (undefined8 *)((ulong)uVar9 * 8 + *(long *)(lVar5 + 0x18));
            }
            else {
              puVar7 = *(undefined8 **)(lVar5 + 0x18);
            }
                    /* try { // try from 00cb3b31 to 00cb3b35 has its CatchHandler @ 00cb3e36 */
            CEffect::getDisplayStats((uint)local_78,SUB81(*puVar7,0));
            pwVar1 = ::EMPTY_WSTRING;
            sVar3 = *(size_t *)(::EMPTY_WSTRING + -6);
            if (*(size_t *)(local_68[0] + -6) == sVar3) {
              iVar6 = wmemcmp(local_68[0],::EMPTY_WSTRING,sVar3);
              if (iVar6 != 0) {
                sVar4 = *(size_t *)(local_78[0] + -6);
                goto joined_r0x00cb3be2;
              }
            }
            else {
              sVar4 = *(size_t *)(local_78[0] + -6);
joined_r0x00cb3be2:
              if ((sVar3 != sVar4) || (iVar6 = wmemcmp(local_78[0],pwVar1,sVar3), iVar6 != 0)) {
                wcslen(L"\n");
                    /* try { // try from 00cb3b70 to 00cb3b7f has its CatchHandler @ 00cb3e43 */
                std::wstring::append((wchar_t *)local_68,0xfd0b48);
              }
            }
            std::wstring::append((wstring_conflict *)local_68);
            if ((allocator *)(local_78[0] + -6) !=
                (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              pwVar1 = local_78[0] + -2;
              wVar2 = *pwVar1;
              *pwVar1 = *pwVar1 + L'\xffffffff';
              UNLOCK();
              if (wVar2 < L'\x01') {
                std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -6));
              }
            }
            uVar9 = uVar9 + 1;
          } while (uVar9 < *(uint *)(lVar5 + 0x20));
        }
        pwVar1 = ::EMPTY_WSTRING;
        sVar3 = *(size_t *)(::EMPTY_WSTRING + -6);
        if (*(size_t *)(local_58[0] + -6) == sVar3) {
          iVar6 = wmemcmp(local_58[0],::EMPTY_WSTRING,sVar3);
          if (iVar6 != 0) {
            sVar4 = *(size_t *)(local_68[0] + -6);
            goto joined_r0x00cb3d5d;
          }
        }
        else {
          sVar4 = *(size_t *)(local_68[0] + -6);
joined_r0x00cb3d5d:
          if ((sVar3 != sVar4) || (iVar6 = wmemcmp(local_68[0],pwVar1,sVar3), iVar6 != 0)) {
            wcslen(L"\n");
                    /* try { // try from 00cb3c50 to 00cb3c61 has its CatchHandler @ 00cb3e36 */
            std::wstring::append((wchar_t *)local_58,0xfd0b48);
          }
        }
        std::wstring::append((wstring_conflict *)local_58);
        if ((allocator *)(local_68[0] + -6) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          pwVar1 = local_68[0] + -2;
          wVar2 = *pwVar1;
          *pwVar1 = *pwVar1 + L'\xffffffff';
          UNLOCK();
          if (wVar2 < L'\x01') {
            std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -6));
          }
        }
        local_84 = local_84 + 1;
      } while (local_84 < *(uint *)(in_RSI + 0x38));
    }
    pwVar1 = ::EMPTY_WSTRING;
    sVar3 = *(size_t *)(::EMPTY_WSTRING + -6);
    if (((*(size_t *)(local_48[0] + -6) != sVar3) ||
        (iVar6 = wmemcmp(local_48[0],::EMPTY_WSTRING,sVar3), iVar6 != 0)) &&
       ((sVar3 != *(size_t *)(local_58[0] + -6) ||
        (iVar6 = wmemcmp(local_58[0],pwVar1,sVar3), iVar6 != 0)))) {
      wcslen(L"\n");
                    /* try { // try from 00cb3ccb to 00cb3ced has its CatchHandler @ 00cb3e1c */
      std::wstring::append((wchar_t *)local_48,0xfd0b48);
    }
    std::wstring::append((wstring_conflict *)local_48);
    std::wstring::wstring(in_RDI,(wstring_conflict *)local_48);
    if ((allocator *)(local_58[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      pwVar1 = local_58[0] + -2;
      wVar2 = *pwVar1;
      *pwVar1 = *pwVar1 + L'\xffffffff';
      UNLOCK();
      if (wVar2 < L'\x01') {
        std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -6));
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
  }
  return in_RDI;
}



/* address=00cb3f10
   symbol=CSkillEffectAndAffixes::fillOutStatBonuses */

/* WARNING: Removing unreachable block (ram,0x00cb41d5) */
/* CSkillEffectAndAffixes::fillOutStatBonuses(float (&) [6], bool) */

void __thiscall
CSkillEffectAndAffixes::fillOutStatBonuses(CSkillEffectAndAffixes *this,float *param_1,bool param_2)

{
  int *piVar1;
  int iVar2;
  long lVar3;
  undefined8 *puVar4;
  ulong uVar5;
  float *pfVar6;
  int iVar7;
  long *plVar8;
  long lVar9;
  float *pfVar10;
  ulong uVar11;
  uint uVar12;
  uint uVar13;
  float fVar14;
  long local_48;

  if (*(int *)(this + 0x50) == 0) {
    getDisplayStats();
    if ((allocator *)(local_48 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_48 + -8);
      iVar7 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar7 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_48 + -0x18));
      }
    }
    if (*(int *)(this + 0x50) == 0) goto LAB_00cb3f91;
  }
  uVar13 = 0;
  do {
    if (uVar13 < *(uint *)(this + 0x54)) {
      puVar4 = (undefined8 *)((ulong)uVar13 * 8 + *(long *)(this + 0x48));
    }
    else {
      puVar4 = *(undefined8 **)(this + 0x48);
    }
    uVar13 = uVar13 + 1;
    CAffix::fillOutStatBonuses((CAffix *)*puVar4,param_1,param_2);
  } while (uVar13 < *(uint *)(this + 0x50));
LAB_00cb3f91:
  if (*(int *)(this + 0x38) != 0) {
    uVar13 = *(uint *)(this + 0x3c);
    uVar12 = 0;
    do {
      uVar11 = 0;
      if (uVar12 < uVar13) goto LAB_00cb4106;
LAB_00cb3fc0:
      if ((uint)uVar11 < *(uint *)(**(long **)(this + 0x30) + 0x20)) {
        do {
          if (uVar12 < uVar13) {
            plVar8 = (long *)((ulong)uVar12 * 8 + *(long *)(this + 0x30));
          }
          else {
            plVar8 = *(long **)(this + 0x30);
          }
          lVar3 = *plVar8;
          if ((uint)uVar11 < *(uint *)(lVar3 + 0x24)) {
            plVar8 = (long *)(uVar11 * 8 + *(long *)(lVar3 + 0x18));
          }
          else {
            plVar8 = *(long **)(lVar3 + 0x18);
          }
          lVar3 = *plVar8;
          iVar7 = 0;
          pfVar10 = param_1;
          do {
            if (param_2) {
              if (*(uint *)(lVar3 + 0x100) != 0) {
                lVar9 = 0;
                uVar5 = 0;
                do {
                  uVar13 = (uint)uVar5;
                  if (uVar13 < *(uint *)(lVar3 + 0x104)) {
                    iVar2 = *(int *)(lVar9 + *(long *)(lVar3 + 0xf8));
                  }
                  else {
                    iVar2 = **(int **)(lVar3 + 0xf8);
                  }
                  if (iVar7 == iVar2) {
                    if (uVar13 < *(uint *)(lVar3 + 0x11c)) {
                      pfVar6 = (float *)(uVar5 * 4 + *(long *)(lVar3 + 0x110));
                    }
                    else {
                      pfVar6 = *(float **)(lVar3 + 0x110);
                    }
                    fVar14 = *pfVar6;
                    goto LAB_00cb414b;
                  }
                  uVar5 = (ulong)(uVar13 + 1);
                  lVar9 = lVar9 + 4;
                } while (uVar13 + 1 < *(uint *)(lVar3 + 0x100));
              }
              fVar14 = 0.0;
LAB_00cb414b:
              if (fVar14 <= *pfVar10) {
                fVar14 = *pfVar10;
              }
              *pfVar10 = fVar14;
            }
            else {
              if (*(uint *)(lVar3 + 0x100) != 0) {
                lVar9 = 0;
                uVar13 = 0;
                do {
                  if (uVar13 < *(uint *)(lVar3 + 0x104)) {
                    iVar2 = *(int *)(lVar9 + *(long *)(lVar3 + 0xf8));
                  }
                  else {
                    iVar2 = **(int **)(lVar3 + 0xf8);
                  }
                  if (iVar2 == iVar7) {
                    if (uVar13 < *(uint *)(lVar3 + 0x11c)) {
                      fVar14 = *(float *)((ulong)uVar13 * 4 + *(long *)(lVar3 + 0x110));
                    }
                    else {
                      fVar14 = **(float **)(lVar3 + 0x110);
                    }
                    goto LAB_00cb40e3;
                  }
                  uVar13 = uVar13 + 1;
                  lVar9 = lVar9 + 4;
                } while (uVar13 < *(uint *)(lVar3 + 0x100));
              }
              fVar14 = 0.0;
LAB_00cb40e3:
              *pfVar10 = fVar14;
            }
            iVar7 = iVar7 + 1;
            pfVar10 = pfVar10 + 1;
          } while (iVar7 != 6);
          uVar13 = *(uint *)(this + 0x3c);
          uVar11 = (ulong)((uint)uVar11 + 1);
          if (uVar13 <= uVar12) goto LAB_00cb3fc0;
LAB_00cb4106:
          if (*(uint *)(*(long *)((ulong)uVar12 * 8 + *(long *)(this + 0x30)) + 0x20) <=
              (uint)uVar11) break;
        } while( true );
      }
      uVar12 = uVar12 + 1;
    } while (uVar12 < *(uint *)(this + 0x38));
  }
  return;
}



/* address=00cb41e0
   symbol=CSkillEffectAndAffixes::~CSkillEffectAndAffixes */

/* WARNING: Removing unreachable block (ram,0x00cb472a) */
/* WARNING: Removing unreachable block (ram,0x00cb4783) */
/* WARNING: Removing unreachable block (ram,0x00cb47b2) */
/* WARNING: Removing unreachable block (ram,0x00cb47bd) */
/* WARNING: Removing unreachable block (ram,0x00cb46f9) */
/* CSkillEffectAndAffixes::~CSkillEffectAndAffixes() */

void __thiscall CSkillEffectAndAffixes::~CSkillEffectAndAffixes(CSkillEffectAndAffixes *this)

{
  int *piVar1;
  long lVar2;
  int iVar3;
  long lVar4;
  long *plVar5;
  uint uVar6;
  ulong uVar7;
  long *plVar8;
  uint uVar9;
  allocator *paVar10;

  *(undefined ***)this = &PTR__CSkillEffectAndAffixes_00ff4e70;
  if (*(int *)(this + 0x50) != 0) {
    uVar7 = 0;
    do {
      plVar5 = (long *)(uVar7 * 8 + *(long *)(this + 0x48));
      if ((long *)*plVar5 != (long *)0x0) {
                    /* try { // try from 00cb4235 to 00cb44d6 has its CatchHandler @ 00cb4660 */
        (**(code **)(*(long *)*plVar5 + 8))();
        *(undefined8 *)(*(long *)(this + 0x48) + uVar7 * 8) = 0;
        plVar5 = (long *)(uVar7 * 8 + *(long *)(this + 0x48));
      }
      *plVar5 = 0;
      uVar6 = (int)uVar7 + 1;
      uVar7 = (ulong)uVar6;
    } while (uVar6 < *(uint *)(this + 0x50));
  }
  *(undefined4 *)(this + 0x50) = 0;
  *(undefined4 *)(this + 0x54) = 0;
  if (*(void **)(this + 0x48) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x48));
  }
  *(undefined8 *)(this + 0x48) = 0;
  *(undefined4 *)(this + 0x68) = 0;
  *(undefined4 *)(this + 0x6c) = 0;
  plVar5 = *(long **)(this + 0x60);
  if (plVar5 != (long *)0x0) {
    plVar8 = plVar5 + plVar5[-1];
    while (plVar5 != plVar8) {
      plVar8 = plVar8 + -1;
      paVar10 = (allocator *)(*plVar8 + -0x18);
      if (paVar10 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(*plVar8 + -8);
        iVar3 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar3 < 1) {
          std::wstring::_Rep::_M_destroy(paVar10);
        }
        plVar5 = *(long **)(this + 0x60);
      }
    }
    operator_delete__((void *)(*(long *)(this + 0x60) + -8));
  }
  *(undefined8 *)(this + 0x60) = 0;
  *(undefined4 *)(this + 0x80) = 0;
  *(undefined4 *)(this + 0x84) = 0;
  plVar5 = *(long **)(this + 0x78);
  if (plVar5 != (long *)0x0) {
    plVar8 = plVar5 + plVar5[-1];
    while (plVar5 != plVar8) {
      plVar8 = plVar8 + -1;
      paVar10 = (allocator *)(*plVar8 + -0x18);
      if (paVar10 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(*plVar8 + -8);
        iVar3 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar3 < 1) {
          std::wstring::_Rep::_M_destroy(paVar10);
        }
        plVar5 = *(long **)(this + 0x78);
      }
    }
    operator_delete__((void *)(*(long *)(this + 0x78) + -8));
  }
  *(undefined8 *)(this + 0x78) = 0;
  if (*(int *)(this + 0x38) != 0) {
    uVar6 = 0;
    do {
      if (uVar6 < *(uint *)(this + 0x3c)) {
        plVar5 = (long *)((ulong)uVar6 * 8 + *(long *)(this + 0x30));
      }
      else {
        plVar5 = *(long **)(this + 0x30);
      }
      if (*(char *)(*plVar5 + 0x10) != '\0') {
        if (uVar6 < *(uint *)(this + 0x3c)) {
          plVar5 = (long *)((ulong)uVar6 * 8 + *(long *)(this + 0x30));
        }
        else {
          plVar5 = *(long **)(this + 0x30);
        }
        lVar4 = *plVar5;
        if (*(int *)(lVar4 + 0x20) != 0) {
          uVar9 = 0;
          do {
            lVar2 = (ulong)uVar9 * 8;
            plVar5 = (long *)(lVar2 + *(long *)(lVar4 + 0x18));
            if ((long *)*plVar5 != (long *)0x0) {
              (**(code **)(*(long *)*plVar5 + 8))();
              *(undefined8 *)(*(long *)(lVar4 + 0x18) + (ulong)uVar9 * 8) = 0;
              plVar5 = (long *)(lVar2 + *(long *)(lVar4 + 0x18));
            }
            *plVar5 = 0;
            uVar9 = uVar9 + 1;
          } while (uVar9 < *(uint *)(lVar4 + 0x20));
        }
        *(undefined4 *)(lVar4 + 0x20) = 0;
        *(undefined4 *)(lVar4 + 0x24) = 0;
        if (*(void **)(lVar4 + 0x18) != (void *)0x0) {
          operator_delete__(*(void **)(lVar4 + 0x18));
        }
        *(undefined8 *)(lVar4 + 0x18) = 0;
      }
      uVar6 = uVar6 + 1;
    } while (uVar6 < *(uint *)(this + 0x38));
    if (*(uint *)(this + 0x38) != 0) {
      uVar7 = 0;
      do {
        plVar5 = (long *)(uVar7 * 8 + *(long *)(this + 0x30));
        if ((long *)*plVar5 != (long *)0x0) {
          (**(code **)(*(long *)*plVar5 + 8))();
          *(undefined8 *)(*(long *)(this + 0x30) + uVar7 * 8) = 0;
          plVar5 = (long *)(uVar7 * 8 + *(long *)(this + 0x30));
        }
        *plVar5 = 0;
        uVar6 = (int)uVar7 + 1;
        uVar7 = (ulong)uVar6;
      } while (uVar6 < *(uint *)(this + 0x38));
    }
  }
  *(undefined4 *)(this + 0x38) = 0;
  *(undefined4 *)(this + 0x3c) = 0;
  if (*(void **)(this + 0x30) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x30));
  }
  *(undefined8 *)(this + 0x30) = 0;
  if (*(int *)(this + 0x20) != 0) {
    uVar6 = 0;
    do {
      lVar4 = (ulong)uVar6 * 8;
      plVar5 = (long *)(lVar4 + *(long *)(this + 0x18));
      if ((long *)*plVar5 != (long *)0x0) {
        (**(code **)(*(long *)*plVar5 + 8))();
        *(undefined8 *)(*(long *)(this + 0x18) + (ulong)uVar6 * 8) = 0;
        plVar5 = (long *)(lVar4 + *(long *)(this + 0x18));
      }
      *plVar5 = 0;
      uVar6 = uVar6 + 1;
    } while (uVar6 < *(uint *)(this + 0x20));
  }
  *(undefined4 *)(this + 0x20) = 0;
  *(undefined4 *)(this + 0x24) = 0;
  if (*(void **)(this + 0x18) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x18));
  }
  *(undefined8 *)(this + 0x18) = 0;
  paVar10 = (allocator *)(*(long *)(this + 0x90) + -0x18);
  if (paVar10 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(*(long *)(this + 0x90) + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar10);
    }
  }
  plVar5 = *(long **)(this + 0x78);
  if (plVar5 != (long *)0x0) {
    plVar8 = plVar5 + plVar5[-1];
    while (plVar5 != plVar8) {
      plVar8 = plVar8 + -1;
      paVar10 = (allocator *)(*plVar8 + -0x18);
      if (paVar10 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(*plVar8 + -8);
        iVar3 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar3 < 1) {
          std::wstring::_Rep::_M_destroy(paVar10);
        }
        plVar5 = *(long **)(this + 0x78);
      }
    }
    operator_delete__((void *)(*(long *)(this + 0x78) + -8));
    *(undefined8 *)(this + 0x78) = 0;
  }
  plVar5 = *(long **)(this + 0x60);
  if (plVar5 != (long *)0x0) {
    plVar8 = plVar5 + plVar5[-1];
    while (plVar5 != plVar8) {
      plVar8 = plVar8 + -1;
      paVar10 = (allocator *)(*plVar8 + -0x18);
      if (paVar10 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(*plVar8 + -8);
        iVar3 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar3 < 1) {
          std::wstring::_Rep::_M_destroy(paVar10);
        }
        plVar5 = *(long **)(this + 0x60);
      }
    }
    operator_delete__((void *)(*(long *)(this + 0x60) + -8));
    *(undefined8 *)(this + 0x60) = 0;
  }
  if (*(void **)(this + 0x48) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x48));
    *(undefined8 *)(this + 0x48) = 0;
  }
  if (*(void **)(this + 0x30) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x30));
    *(undefined8 *)(this + 0x30) = 0;
  }
  if (*(void **)(this + 0x18) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x18));
    *(undefined8 *)(this + 0x18) = 0;
  }
  CRunicCore::~CRunicCore((CRunicCore *)this);
  return;
}



/* address=00cb47d0
   symbol=CSkillEffectAndAffixes::~CSkillEffectAndAffixes */

/* CSkillEffectAndAffixes::~CSkillEffectAndAffixes() */

void __thiscall CSkillEffectAndAffixes::~CSkillEffectAndAffixes(CSkillEffectAndAffixes *this)

{
  ~CSkillEffectAndAffixes(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}



/* address=00cb47f0
   symbol=CSkillEffectAndAffixes::CSkillEffectAndAffixes */

/* WARNING: Removing unreachable block (ram,0x00cb63ed) */
/* WARNING: Removing unreachable block (ram,0x00cb64c6) */
/* WARNING: Removing unreachable block (ram,0x00cb645f) */
/* WARNING: Removing unreachable block (ram,0x00cb6545) */
/* WARNING: Removing unreachable block (ram,0x00cb6649) */
/* WARNING: Removing unreachable block (ram,0x00cb6746) */
/* WARNING: Removing unreachable block (ram,0x00cb6814) */
/* WARNING: Removing unreachable block (ram,0x00cb6916) */
/* WARNING: Removing unreachable block (ram,0x00cb69b2) */
/* WARNING: Removing unreachable block (ram,0x00cb6a53) */
/* WARNING: Removing unreachable block (ram,0x00cb6b30) */
/* WARNING: Removing unreachable block (ram,0x00cb6bb2) */
/* WARNING: Removing unreachable block (ram,0x00cb6e45) */
/* WARNING: Removing unreachable block (ram,0x00cb6cfb) */
/* WARNING: Removing unreachable block (ram,0x00cb6e53) */
/* WARNING: Removing unreachable block (ram,0x00cb6c06) */
/* WARNING: Removing unreachable block (ram,0x00cb6b65) */
/* WARNING: Removing unreachable block (ram,0x00cb6acd) */
/* WARNING: Removing unreachable block (ram,0x00cb6a16) */
/* WARNING: Removing unreachable block (ram,0x00cb69bd) */
/* WARNING: Removing unreachable block (ram,0x00cb68ac) */
/* WARNING: Removing unreachable block (ram,0x00cb679b) */
/* WARNING: Removing unreachable block (ram,0x00cb66e1) */
/* WARNING: Removing unreachable block (ram,0x00cb663e) */
/* WARNING: Removing unreachable block (ram,0x00cb6550) */
/* WARNING: Removing unreachable block (ram,0x00cb656c) */
/* WARNING: Removing unreachable block (ram,0x00cb63f8) */
/* WARNING: Removing unreachable block (ram,0x00cb655e) */
/* WARNING: Removing unreachable block (ram,0x00cb66d6) */
/* WARNING: Removing unreachable block (ram,0x00cb68a1) */
/* WARNING: Removing unreachable block (ram,0x00cb65e9) */
/* CSkillEffectAndAffixes::CSkillEffectAndAffixes(CSkill*, CDataGroup*, CSkillEffectAndAffixes*) */

void __thiscall
CSkillEffectAndAffixes::CSkillEffectAndAffixes
          (CSkillEffectAndAffixes *this,CSkill *param_1,CDataGroup *param_2,
          CSkillEffectAndAffixes *param_3)

{
  int *piVar1;
  wchar_t wVar2;
  size_t __n;
  wchar_t *__s1;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  wstring_conflict *pwVar7;
  long lVar8;
  CDataGroup *pCVar9;
  CRunicCore *pCVar10;
  void *pvVar11;
  long lVar12;
  wchar_t *pwVar13;
  CDataGroup *this_00;
  ulong *puVar14;
  long *plVar15;
  long *plVar16;
  CEffect *this_01;
  ulong uVar17;
  uint uVar18;
  ulong uVar19;
  int iVar20;
  size_t sVar21;
  allocator *paVar22;
  uint uVar23;
  ulong *puVar24;
  undefined8 uVar25;
  uint uVar26;
  undefined8 *puVar27;
  undefined4 uVar28;
  int local_2a0;
  undefined4 local_294;
  wstring_conflict *local_290;
  uint local_284;
  void *local_278;
  long local_270;
  undefined8 local_268;
  void *local_258;
  long local_250;
  undefined8 local_248;
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
  long local_a8 [2];
  wchar_t *local_98 [2];
  wchar_t *local_88 [2];
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
  *(undefined ***)this = &PTR__CSkillEffectAndAffixes_00ff4e70;
  *(CSkill **)(this + 0x10) = param_1;
  *(undefined8 *)(this + 0x18) = 0;
  *(undefined4 *)(this + 0x20) = 0;
  *(undefined4 *)(this + 0x24) = 0;
  *(undefined4 *)(this + 0x28) = 10;
  *(undefined8 *)(this + 0x30) = 0;
  *(undefined4 *)(this + 0x38) = 0;
  *(undefined4 *)(this + 0x3c) = 0;
  *(undefined4 *)(this + 0x40) = 10;
  *(undefined8 *)(this + 0x48) = 0;
  *(undefined4 *)(this + 0x50) = 0;
  *(undefined4 *)(this + 0x54) = 0;
  *(undefined4 *)(this + 0x58) = 10;
  *(undefined8 *)(this + 0x60) = 0;
  *(undefined4 *)(this + 0x68) = 0;
  *(undefined4 *)(this + 0x6c) = 0;
  *(undefined4 *)(this + 0x70) = 10;
  *(undefined8 *)(this + 0x78) = 0;
  *(undefined4 *)(this + 0x80) = 0;
  *(undefined4 *)(this + 0x84) = 0;
  *(undefined4 *)(this + 0x88) = 10;
  *(undefined4 **)(this + 0x90) = &DAT_01424558;
                    /* try { // try from 00cb48e3 to 00cb48e7 has its CatchHandler @ 00cb620c */
  STRINGS::GetValueAsWString((uint)local_78);
                    /* try { // try from 00cb48fd to 00cb4901 has its CatchHandler @ 00cb6d67 */
  std::wstring::wstring((wstring_conflict *)local_88,L"",local_39);
                    /* try { // try from 00cb4917 to 00cb491b has its CatchHandler @ 00cb6d46 */
  std::wstring::wstring((wstring_conflict *)local_98,L"",&local_3a);
                    /* try { // try from 00cb4934 to 00cb4938 has its CatchHandler @ 00cb6d2f */
  std::wstring::wstring((wstring_conflict *)local_a8,L"TARGET",&local_3b);
                    /* try { // try from 00cb4949 to 00cb495d has its CatchHandler @ 00cb6d06 */
  pwVar7 = (wstring_conflict *)
           CDataGroup::GetDataValue
                     (param_2,(wstring_conflict *)local_a8,(wstring_conflict *)local_98);
  STRINGS::StringUpper((STRINGS *)local_b8,pwVar7);
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
  }
  if (*(long *)(local_b8[0] + -0x18) == 0) {
                    /* try { // try from 00cb4995 to 00cb49fd has its CatchHandler @ 00cb6c97 */
    uVar3 = CSkill::getTargetType(param_1);
    switch(uVar3) {
    case 2:
      if (*(int *)(param_1 + 0x120) == 1) {
        std::wstring::assign((wstring_conflict *)local_b8);
      }
      else {
        std::wstring::assign((wstring_conflict *)local_b8);
      }
      break;
    case 3:
    case 10:
                    /* try { // try from 00cb6c8d to 00cb6cf5 has its CatchHandler @ 00cb6c97 */
      std::wstring::assign((wstring_conflict *)local_b8);
      break;
    case 4:
      std::wstring::assign((wstring_conflict *)local_b8);
      break;
    case 9:
                    /* try { // try from 00cb6dcf to 00cb6df6 has its CatchHandler @ 00cb6c97 */
      std::wstring::assign((wstring_conflict *)local_b8);
    }
  }
  iVar4 = STRINGS::getStringIndex
                    ((wstring_conflict *)local_b8,
                     (wstring_conflict *)&gSKILL_EFFECT_AND_AFFIXES_TARGET_NAMES,5,0,false);
                    /* try { // try from 00cb4a1a to 00cb4a1e has its CatchHandler @ 00cb6db1 */
  std::wstring::wstring((wstring_conflict *)local_c8,L"EFFECTS",&local_3c);
                    /* try { // try from 00cb4a29 to 00cb4a2d has its CatchHandler @ 00cb6d88 */
  lVar8 = CDataGroup::GetDataGroupByName(param_2,(wstring_conflict *)local_c8,false);
  if ((allocator *)(local_c8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_c8[0] + -8);
    iVar20 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar20 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
    }
  }
  if (lVar8 == 0) {
    uVar3 = 0;
    pCVar9 = param_2;
  }
  else {
                    /* try { // try from 00cb4a6c to 00cb4a70 has its CatchHandler @ 00cb6c6f */
    std::wstring::wstring((wstring_conflict *)local_d8,L"EFFECTS",&local_3d);
                    /* try { // try from 00cb4a7b to 00cb4a7f has its CatchHandler @ 00cb6c46 */
    pCVar9 = (CDataGroup *)
             CDataGroup::GetDataGroupByName(param_2,(wstring_conflict *)local_d8,false);
    if ((allocator *)(local_d8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_d8[0] + -8);
      iVar20 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar20 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
      }
    }
                    /* try { // try from 00cb4ac1 to 00cb4ac5 has its CatchHandler @ 00cb6c11 */
    std::wstring::wstring((wstring_conflict *)local_e8,L"ADDITIONALDESCRIPTION",&local_3e);
                    /* try { // try from 00cb4ad1 to 00cb4ae2 has its CatchHandler @ 00cb6be9 */
    CDataGroup::GetDataValue(pCVar9,(wstring_conflict *)local_e8,(wstring_conflict *)(this + 0x90));
    std::wstring::assign((wstring_conflict *)(this + 0x90));
    if ((allocator *)(local_e8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_e8[0] + -8);
      iVar20 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar20 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
      }
    }
                    /* try { // try from 00cb4b15 to 00cb4b19 has its CatchHandler @ 00cb6bae */
    std::wstring::wstring((wstring_conflict *)local_f8,L"TARGETTYPE",&local_3f);
                    /* try { // try from 00cb4b28 to 00cb4b3c has its CatchHandler @ 00cb6ba1 */
    CDataGroup::GetDataValue(pCVar9,(wstring_conflict *)local_f8,(wstring_conflict *)local_88);
    std::wstring::assign((wstring_conflict *)local_88);
    if ((allocator *)(local_f8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_f8[0] + -8);
      iVar20 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar20 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
      }
    }
                    /* try { // try from 00cb4b6f to 00cb4b73 has its CatchHandler @ 00cb6b70 */
    std::wstring::wstring((wstring_conflict *)local_108,L"TARGET",&local_40);
                    /* try { // try from 00cb4b82 to 00cb4b99 has its CatchHandler @ 00cb6b60 */
    pwVar7 = (wstring_conflict *)
             CDataGroup::GetDataValue
                       (pCVar9,(wstring_conflict *)local_108,(wstring_conflict *)local_98);
    STRINGS::StringUpper((STRINGS *)local_118,pwVar7);
                    /* try { // try from 00cb4ba5 to 00cb4ba9 has its CatchHandler @ 00cb6b3b */
    std::wstring::assign((wstring_conflict *)local_98);
    if ((allocator *)(local_118[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_118[0] + -8);
      iVar20 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar20 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_118[0] + -0x18));
      }
    }
    if ((allocator *)(local_108[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_108[0] + -8);
      iVar20 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar20 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_108[0] + -0x18));
      }
    }
    pwVar13 = ::EMPTY_WSTRING;
    sVar21 = *(size_t *)(local_88[0] + -6);
    if (sVar21 == *(size_t *)(::EMPTY_WSTRING + -6)) {
      uVar3 = 0;
      iVar20 = wmemcmp(local_88[0],::EMPTY_WSTRING,sVar21);
      if (iVar20 != 0) goto LAB_00cb4bfb;
    }
    else {
LAB_00cb4bfb:
                    /* try { // try from 00cb4bfb to 00cb4c13 has its CatchHandler @ 00cb6c97 */
      lVar8 = CMasterResourceManager::getSingleton();
      uVar3 = CHierarchy::getTypeIDByName
                        (*(CHierarchy **)(lVar8 + 0x80),(wstring_conflict *)local_88);
      sVar21 = *(size_t *)(::EMPTY_WSTRING + -6);
      pwVar13 = ::EMPTY_WSTRING;
    }
    __s1 = local_98[0];
    __n = *(size_t *)(local_98[0] + -6);
    if ((__n != sVar21) || (iVar20 = wmemcmp(local_98[0],pwVar13,sVar21), iVar20 != 0)) {
      puVar27 = &gSKILL_EFFECT_AND_AFFIXES_TARGET_NAMES;
      iVar20 = 0;
      do {
        if ((__n == *(size_t *)((wchar_t *)*puVar27 + -6)) &&
           (iVar6 = wmemcmp(__s1,(wchar_t *)*puVar27,__n), iVar6 == 0)) {
          iVar4 = iVar20;
        }
        iVar20 = iVar20 + 1;
        puVar27 = puVar27 + 1;
      } while (iVar20 != 5);
    }
  }
  local_290 = (wstring_conflict *)(this + 0x90);
  local_258 = (void *)0x0;
  local_250 = 0;
  local_248 = 0;
                    /* try { // try from 00cb4ca7 to 00cb4cab has its CatchHandler @ 00cb6ac8 */
  std::wstring::wstring((wstring_conflict *)local_128,L"EFFECT",&local_41);
                    /* try { // try from 00cb4cba to 00cb4cbe has its CatchHandler @ 00cb6aab */
  CDataGroup::GetDataGroupsMatchingName(pCVar9,(wstring_conflict *)local_128,(vector *)&local_258);
  if ((allocator *)(local_128[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_128[0] + -8);
    iVar20 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar20 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_128[0] + -0x18));
    }
  }
  if (local_250 - (long)local_258 >> 3 != 0) {
                    /* try { // try from 00cb5fef to 00cb5ff3 has its CatchHandler @ 00cb6a6a */
    pCVar10 = (CRunicCore *)Ogre::NedAllocImpl::allocBytes(0x38,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00cb5ffa to 00cb5ffe has its CatchHandler @ 00cb634b */
    CRunicCore::CRunicCore(pCVar10);
    *(undefined ***)pCVar10 = &PTR__CSkillEffectData_00ff4ed0;
    *(undefined8 *)(pCVar10 + 0x18) = 0;
    *(undefined4 *)(pCVar10 + 0x20) = 0;
    *(undefined4 *)(pCVar10 + 0x24) = 0;
    *(undefined4 *)(pCVar10 + 0x28) = 10;
    *(undefined4 *)(pCVar10 + 0x30) = uVar3;
    *(int *)(pCVar10 + 0x34) = iVar4;
    pCVar10[0x10] = (CRunicCore)0x1;
    if (local_250 - (long)local_258 >> 3 != 0) {
      uVar17 = 0;
      do {
        pCVar9 = *(CDataGroup **)((long)local_258 + uVar17 * 8);
                    /* try { // try from 00cb6067 to 00cb606b has its CatchHandler @ 00cb6a6a */
        this_01 = (CEffect *)Ogre::NedAllocImpl::allocBytes(0x138,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00cb6077 to 00cb607b has its CatchHandler @ 00cb62e8 */
        CEffect::CEffect(this_01,pCVar9,(CBaseUnit *)0x0);
        uVar26 = *(uint *)(pCVar10 + 0x20);
        if (uVar26 < *(uint *)(pCVar10 + 0x24)) {
          pvVar11 = *(void **)(pCVar10 + 0x18);
        }
        else if (*(long *)(pCVar10 + 0x18) == 0) {
          *(uint *)(pCVar10 + 0x24) = *(uint *)(pCVar10 + 0x28);
          pvVar11 = operator_new__((ulong)*(uint *)(pCVar10 + 0x28) << 3);
          *(void **)(pCVar10 + 0x18) = pvVar11;
          uVar26 = *(uint *)(pCVar10 + 0x20);
        }
        else {
          uVar5 = *(uint *)(pCVar10 + 0x24) + *(int *)(pCVar10 + 0x28);
                    /* try { // try from 00cb60a2 to 00cb61a9 has its CatchHandler @ 00cb6a6a */
          pvVar11 = operator_new__((ulong)uVar5 << 3);
          if (*(int *)(pCVar10 + 0x24) != 0) {
            uVar26 = 0;
            do {
              uVar19 = (ulong)uVar26;
              uVar26 = uVar26 + 1;
              *(undefined8 *)((long)pvVar11 + uVar19 * 8) =
                   *(undefined8 *)(*(long *)(pCVar10 + 0x18) + uVar19 * 8);
            } while (uVar26 < *(uint *)(pCVar10 + 0x24));
          }
          if (*(void **)(pCVar10 + 0x18) != (void *)0x0) {
            operator_delete__(*(void **)(pCVar10 + 0x18));
          }
          *(void **)(pCVar10 + 0x18) = pvVar11;
          uVar26 = *(uint *)(pCVar10 + 0x20);
          *(uint *)(pCVar10 + 0x24) = uVar5;
        }
        uVar17 = (ulong)((int)uVar17 + 1);
        *(CEffect **)((long)pvVar11 + (ulong)uVar26 * 8) = this_01;
        *(int *)(pCVar10 + 0x20) = *(int *)(pCVar10 + 0x20) + 1;
      } while (uVar17 < (ulong)(local_250 - (long)local_258 >> 3));
    }
    uVar26 = *(uint *)(this + 0x38);
    if (uVar26 < *(uint *)(this + 0x3c)) {
      pvVar11 = *(void **)(this + 0x30);
    }
    else if (*(long *)(this + 0x30) == 0) {
      *(uint *)(this + 0x3c) = *(uint *)(this + 0x40);
                    /* try { // try from 00cb62a4 to 00cb62a8 has its CatchHandler @ 00cb6a6a */
      pvVar11 = operator_new__((ulong)*(uint *)(this + 0x40) << 3);
      *(void **)(this + 0x30) = pvVar11;
      uVar26 = *(uint *)(this + 0x38);
    }
    else {
      uVar26 = *(uint *)(this + 0x3c) + *(int *)(this + 0x40);
      pvVar11 = operator_new__((ulong)uVar26 << 3);
      for (uVar17 = 0; (uint)uVar17 < *(uint *)(this + 0x3c); uVar17 = (ulong)((uint)uVar17 + 1)) {
        *(undefined8 *)((long)pvVar11 + uVar17 * 8) =
             *(undefined8 *)(*(long *)(this + 0x30) + uVar17 * 8);
      }
      if (*(void **)(this + 0x30) != (void *)0x0) {
        operator_delete__(*(void **)(this + 0x30));
      }
      *(void **)(this + 0x30) = pvVar11;
      *(uint *)(this + 0x3c) = uVar26;
      uVar26 = *(uint *)(this + 0x38);
    }
    *(CRunicCore **)((long)pvVar11 + (ulong)uVar26 * 8) = pCVar10;
    *(int *)(this + 0x38) = *(int *)(this + 0x38) + 1;
    if (local_250 - (long)local_258 >> 3 != 0) goto LAB_00cb4f4d;
  }
  if ((param_3 != (CSkillEffectAndAffixes *)0x0) && (*(int *)(param_3 + 0x38) != 0)) {
    uVar26 = 0;
    do {
                    /* try { // try from 00cb4d28 to 00cb4d2c has its CatchHandler @ 00cb6a6a */
      pCVar10 = (CRunicCore *)Ogre::NedAllocImpl::allocBytes(0x38,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00cb4d33 to 00cb4d37 has its CatchHandler @ 00cb6a65 */
      CRunicCore::CRunicCore(pCVar10);
      *(undefined ***)pCVar10 = &PTR__CSkillEffectData_00ff4ed0;
      pCVar10[0x10] = (CRunicCore)0x0;
      *(undefined8 *)(pCVar10 + 0x18) = 0;
      *(undefined4 *)(pCVar10 + 0x20) = 0;
      *(undefined4 *)(pCVar10 + 0x24) = 0;
      *(undefined4 *)(pCVar10 + 0x28) = 10;
      *(undefined4 *)(pCVar10 + 0x30) = 0;
      *(undefined4 *)(pCVar10 + 0x34) = 0;
      if (uVar26 < *(uint *)(param_3 + 0x3c)) {
        plVar16 = (long *)((ulong)uVar26 * 8 + *(long *)(param_3 + 0x30));
      }
      else {
        plVar16 = *(long **)(param_3 + 0x30);
      }
      *(undefined4 *)(pCVar10 + 0x30) = *(undefined4 *)(*plVar16 + 0x30);
      if (uVar26 < *(uint *)(param_3 + 0x3c)) {
        plVar16 = (long *)((ulong)uVar26 * 8 + *(long *)(param_3 + 0x30));
      }
      else {
        plVar16 = *(long **)(param_3 + 0x30);
      }
      lVar8 = (ulong)uVar26 * 8;
      uVar23 = 0;
      uVar3 = *(undefined4 *)(*plVar16 + 0x34);
      pCVar10[0x10] = (CRunicCore)0x0;
      *(undefined4 *)(pCVar10 + 0x34) = uVar3;
      uVar5 = *(uint *)(param_3 + 0x3c);
      if (uVar26 < uVar5) goto LAB_00cb4ea2;
LAB_00cb4dd8:
      if (uVar23 < *(uint *)(**(long **)(param_3 + 0x30) + 0x20)) {
        do {
          if (uVar26 < uVar5) {
            plVar16 = (long *)(lVar8 + *(long *)(param_3 + 0x30));
          }
          else {
            plVar16 = *(long **)(param_3 + 0x30);
          }
          lVar12 = *plVar16;
          if (uVar23 < *(uint *)(lVar12 + 0x24)) {
            uVar18 = *(uint *)(pCVar10 + 0x20);
            uVar25 = *(undefined8 *)((ulong)uVar23 * 8 + *(long *)(lVar12 + 0x18));
            uVar5 = *(uint *)(pCVar10 + 0x24);
            if (uVar18 < uVar5) goto LAB_00cb5d0c;
LAB_00cb4e1d:
            if (*(long *)(pCVar10 + 0x18) == 0) {
              *(uint *)(pCVar10 + 0x24) = *(uint *)(pCVar10 + 0x28);
                    /* try { // try from 00cb5d3c to 00cb5d40 has its CatchHandler @ 00cb6a6a */
              pvVar11 = operator_new__((ulong)*(uint *)(pCVar10 + 0x28) << 3);
              *(void **)(pCVar10 + 0x18) = pvVar11;
              uVar18 = *(uint *)(pCVar10 + 0x20);
            }
            else {
              iVar4 = *(int *)(pCVar10 + 0x28);
                    /* try { // try from 00cb4e35 to 00cb4ee6 has its CatchHandler @ 00cb6a6a */
              pvVar11 = operator_new__((ulong)(uVar5 + iVar4) << 3);
              if (*(int *)(pCVar10 + 0x24) != 0) {
                uVar17 = 0;
                do {
                  uVar18 = (int)uVar17 + 1;
                  *(undefined8 *)((long)pvVar11 + uVar17 * 8) =
                       *(undefined8 *)(*(long *)(pCVar10 + 0x18) + uVar17 * 8);
                  uVar17 = (ulong)uVar18;
                } while (uVar18 < *(uint *)(pCVar10 + 0x24));
              }
              if (*(void **)(pCVar10 + 0x18) != (void *)0x0) {
                operator_delete__(*(void **)(pCVar10 + 0x18));
              }
              *(void **)(pCVar10 + 0x18) = pvVar11;
              *(uint *)(pCVar10 + 0x24) = uVar5 + iVar4;
              uVar18 = *(uint *)(pCVar10 + 0x20);
            }
          }
          else {
            uVar18 = *(uint *)(pCVar10 + 0x20);
            uVar25 = **(undefined8 **)(lVar12 + 0x18);
            uVar5 = *(uint *)(pCVar10 + 0x24);
            if (uVar5 <= uVar18) goto LAB_00cb4e1d;
LAB_00cb5d0c:
            pvVar11 = *(void **)(pCVar10 + 0x18);
          }
          uVar23 = uVar23 + 1;
          *(undefined8 *)((long)pvVar11 + (ulong)uVar18 * 8) = uVar25;
          *(int *)(pCVar10 + 0x20) = *(int *)(pCVar10 + 0x20) + 1;
          uVar5 = *(uint *)(param_3 + 0x3c);
          if (uVar5 <= uVar26) goto LAB_00cb4dd8;
LAB_00cb4ea2:
          if (*(uint *)(*(long *)(lVar8 + *(long *)(param_3 + 0x30)) + 0x20) <= uVar23) break;
        } while( true );
      }
      uVar5 = *(uint *)(this + 0x38);
      if (uVar5 < *(uint *)(this + 0x3c)) {
        pvVar11 = *(void **)(this + 0x30);
      }
      else if (*(long *)(this + 0x30) == 0) {
        *(uint *)(this + 0x3c) = *(uint *)(this + 0x40);
                    /* try { // try from 00cb5efc to 00cb5f00 has its CatchHandler @ 00cb6a6a */
        pvVar11 = operator_new__((ulong)*(uint *)(this + 0x40) << 3);
        *(void **)(this + 0x30) = pvVar11;
        uVar5 = *(uint *)(this + 0x38);
      }
      else {
        uVar23 = *(uint *)(this + 0x3c) + *(int *)(this + 0x40);
        pvVar11 = operator_new__((ulong)uVar23 << 3);
        if (*(int *)(this + 0x3c) != 0) {
          uVar5 = 0;
          do {
            uVar17 = (ulong)uVar5;
            uVar5 = uVar5 + 1;
            *(undefined8 *)((long)pvVar11 + uVar17 * 8) =
                 *(undefined8 *)(*(long *)(this + 0x30) + uVar17 * 8);
          } while (uVar5 < *(uint *)(this + 0x3c));
        }
        if (*(void **)(this + 0x30) != (void *)0x0) {
          operator_delete__(*(void **)(this + 0x30));
        }
        uVar5 = *(uint *)(this + 0x38);
        *(void **)(this + 0x30) = pvVar11;
        *(uint *)(this + 0x3c) = uVar23;
      }
      uVar26 = uVar26 + 1;
      *(CRunicCore **)((long)pvVar11 + (ulong)uVar5 * 8) = pCVar10;
      *(int *)(this + 0x38) = *(int *)(this + 0x38) + 1;
    } while (uVar26 < *(uint *)(param_3 + 0x38));
  }
LAB_00cb4f4d:
  local_278 = (void *)0x0;
  local_270 = 0;
  local_268 = 0;
                    /* try { // try from 00cb4f80 to 00cb4f84 has its CatchHandler @ 00cb6a5e */
  std::wstring::wstring((wstring_conflict *)local_138,L"AFFIXES",&local_42);
                    /* try { // try from 00cb4f92 to 00cb4f96 has its CatchHandler @ 00cb6a4e */
  CDataGroup::GetDataGroupsMatchingName(param_2,(wstring_conflict *)local_138,(vector *)&local_278);
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
  if (local_270 - (long)local_278 >> 3 != 0) {
    uVar17 = 0;
    local_284 = 0;
    do {
                    /* try { // try from 00cb5005 to 00cb5009 has its CatchHandler @ 00cb6a11 */
      std::wstring::wstring((wstring_conflict *)local_148,L"AFFIXLEVEL",&local_43);
      lVar8 = uVar17 * 8;
                    /* try { // try from 00cb502d to 00cb5031 has its CatchHandler @ 00cb69fc */
      uVar3 = CDataGroup::GetDataValue
                        (*(CDataGroup **)((long)local_278 + uVar17 * 8),
                         (wstring_conflict *)local_148,1);
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
                    /* try { // try from 00cb5065 to 00cb5069 has its CatchHandler @ 00cb69cb */
      std::wstring::wstring((wstring_conflict *)local_158,L"DURATION",&local_44);
                    /* try { // try from 00cb5088 to 00cb508c has its CatchHandler @ 00cb699d */
      uVar28 = CDataGroup::GetDataValue
                         (*(CDataGroup **)((long)local_278 + lVar8),(wstring_conflict *)local_158,
                          DAT_00fa8760);
      if ((allocator *)(local_158[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_158[0] + -8);
        iVar4 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar4 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_158[0] + -0x18));
        }
      }
                    /* try { // try from 00cb50c2 to 00cb50c6 has its CatchHandler @ 00cb696c */
      std::wstring::wstring((wstring_conflict *)local_168,L"TARGETTYPE",&local_45);
                    /* try { // try from 00cb50e2 to 00cb50f6 has its CatchHandler @ 00cb6957 */
      CDataGroup::GetDataValue
                (*(CDataGroup **)((long)local_278 + lVar8),(wstring_conflict *)local_168,
                 (wstring_conflict *)&::EMPTY_WSTRING);
      std::wstring::assign((wstring_conflict *)local_88);
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
                    /* try { // try from 00cb5129 to 00cb512d has its CatchHandler @ 00cb6922 */
      std::wstring::wstring((wstring_conflict *)local_178,L"ADDITIONALDESCRIPTION",&local_46);
                    /* try { // try from 00cb5144 to 00cb5155 has its CatchHandler @ 00cb6911 */
      CDataGroup::GetDataValue
                (*(CDataGroup **)((long)local_278 + lVar8),(wstring_conflict *)local_178,local_290);
      std::wstring::assign(local_290);
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
      if (*(size_t *)(local_88[0] + -6) == *(size_t *)(::EMPTY_WSTRING + -6)) {
        iVar4 = wmemcmp(local_88[0],::EMPTY_WSTRING,*(size_t *)(local_88[0] + -6));
        local_294 = 0;
        if (iVar4 != 0) goto LAB_00cb518d;
      }
      else {
LAB_00cb518d:
                    /* try { // try from 00cb519c to 00cb51c3 has its CatchHandler @ 00cb68d9 */
        lVar12 = CMasterResourceManager::getSingleton();
        local_294 = CHierarchy::getTypeIDByName
                              (*(CHierarchy **)(lVar12 + 0x80),(wstring_conflict *)local_88);
      }
                    /* try { // try from 00cb51e0 to 00cb51e4 has its CatchHandler @ 00cb68d4 */
      std::wstring::wstring((wstring_conflict *)local_188,L"TARGET",&local_47);
                    /* try { // try from 00cb51fb to 00cb5212 has its CatchHandler @ 00cb68cf */
      pwVar7 = (wstring_conflict *)
               CDataGroup::GetDataValue
                         (*(CDataGroup **)((long)local_278 + lVar8),(wstring_conflict *)local_188,
                          (wstring_conflict *)&::EMPTY_WSTRING);
      STRINGS::StringUpper((STRINGS *)local_198,pwVar7);
                    /* try { // try from 00cb521e to 00cb5222 has its CatchHandler @ 00cb68b7 */
      std::wstring::assign((wstring_conflict *)local_98);
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
      pwVar13 = local_98[0];
      sVar21 = *(size_t *)(local_98[0] + -6);
      if (sVar21 == *(size_t *)(::EMPTY_WSTRING + -6)) {
        iVar4 = wmemcmp(local_98[0],::EMPTY_WSTRING,sVar21);
        local_2a0 = 0;
        if (iVar4 != 0) goto LAB_00cb5274;
      }
      else {
LAB_00cb5274:
        puVar27 = &gSKILL_EFFECT_AND_AFFIXES_TARGET_NAMES;
        iVar20 = 0;
        iVar4 = 0;
        local_2a0 = 0;
        do {
          if ((sVar21 == *(size_t *)((wchar_t *)*puVar27 + -6)) &&
             (iVar6 = wmemcmp(pwVar13,(wchar_t *)*puVar27,sVar21), local_2a0 = iVar4, iVar6 == 0)) {
            local_2a0 = iVar20;
            iVar4 = iVar20;
          }
          iVar20 = iVar20 + 1;
          puVar27 = puVar27 + 1;
        } while (iVar20 != 5);
      }
      lVar8 = *(long *)((long)local_278 + lVar8);
      if ((lVar8 != -0x20) && (*(int *)(lVar8 + 0x28) != 0)) {
        uVar26 = 0;
        do {
          if (uVar26 < *(uint *)(lVar8 + 0x2c)) {
            plVar16 = (long *)((ulong)uVar26 * 8 + *(long *)(lVar8 + 0x20));
          }
          else {
            plVar16 = *(long **)(lVar8 + 0x20);
          }
          if ((*(int *)(*plVar16 + 0x30) == 8) || (*(int *)(*plVar16 + 0x30) == 5)) {
            if (uVar26 < *(uint *)(lVar8 + 0x2c)) {
              puVar27 = (undefined8 *)((ulong)uVar26 * 8 + *(long *)(lVar8 + 0x20));
            }
            else {
              puVar27 = *(undefined8 **)(lVar8 + 0x20);
            }
                    /* try { // try from 00cb532d to 00cb5374 has its CatchHandler @ 00cb68d9 */
            pwVar13 = (wchar_t *)CDataValue::GetDataValueName((CDataValue *)*puVar27);
            iVar4 = std::wstring::compare(pwVar13);
            if (iVar4 == 0) {
              pCVar10 = (CRunicCore *)Ogre::NedAllocImpl::allocBytes(0x28,(char *)0x0,0,(char *)0x0)
              ;
                    /* try { // try from 00cb537b to 00cb537f has its CatchHandler @ 00cb6844 */
              CRunicCore::CRunicCore(pCVar10);
              *(undefined ***)pCVar10 = &PTR__CSkillAffixData_00ff4f50;
                    /* try { // try from 00cb5399 to 00cb539d has its CatchHandler @ 00cb681f */
              std::wstring::wstring
                        ((wstring_conflict *)(pCVar10 + 0x10),(wstring_conflict *)&::EMPTY_WSTRING);
              *(undefined4 *)(pCVar10 + 0x18) = 0;
              *(undefined4 *)(pCVar10 + 0x1c) = 0;
              *(undefined4 *)(pCVar10 + 0x20) = 0;
              *(undefined4 *)(pCVar10 + 0x24) = 0xbf800000;
              if (uVar26 < *(uint *)(lVar8 + 0x2c)) {
                puVar27 = (undefined8 *)((ulong)uVar26 * 8 + *(long *)(lVar8 + 0x20));
              }
              else {
                puVar27 = *(undefined8 **)(lVar8 + 0x20);
              }
                    /* try { // try from 00cb53e5 to 00cb5544 has its CatchHandler @ 00cb68d9 */
              CDataValue::GetValueString((CDataValue *)*puVar27,true);
              std::wstring::assign((wstring_conflict *)(pCVar10 + 0x10));
              *(undefined4 *)(pCVar10 + 0x18) = uVar3;
              *(undefined4 *)(pCVar10 + 0x24) = uVar28;
              *(int *)(pCVar10 + 0x20) = local_2a0;
              *(undefined4 *)(pCVar10 + 0x1c) = local_294;
              uVar5 = *(uint *)(this + 0x20);
              if (uVar5 < *(uint *)(this + 0x24)) {
                pvVar11 = *(void **)(this + 0x18);
              }
              else if (*(long *)(this + 0x18) == 0) {
                *(uint *)(this + 0x24) = *(uint *)(this + 0x28);
                    /* try { // try from 00cb5da4 to 00cb5da8 has its CatchHandler @ 00cb68d9 */
                pvVar11 = operator_new__((ulong)*(uint *)(this + 0x28) << 3);
                *(void **)(this + 0x18) = pvVar11;
                uVar5 = *(uint *)(this + 0x20);
              }
              else {
                uVar23 = *(uint *)(this + 0x24) + *(int *)(this + 0x28);
                pvVar11 = operator_new__((ulong)uVar23 << 3);
                if (*(int *)(this + 0x24) != 0) {
                  uVar5 = 0;
                  do {
                    uVar17 = (ulong)uVar5;
                    uVar5 = uVar5 + 1;
                    *(undefined8 *)((long)pvVar11 + uVar17 * 8) =
                         *(undefined8 *)(*(long *)(this + 0x18) + uVar17 * 8);
                  } while (uVar5 < *(uint *)(this + 0x24));
                }
                if (*(void **)(this + 0x18) != (void *)0x0) {
                  operator_delete__(*(void **)(this + 0x18));
                }
                *(void **)(this + 0x18) = pvVar11;
                uVar5 = *(uint *)(this + 0x20);
                *(uint *)(this + 0x24) = uVar23;
              }
              *(CRunicCore **)((long)pvVar11 + (ulong)uVar5 * 8) = pCVar10;
              *(int *)(this + 0x20) = *(int *)(this + 0x20) + 1;
            }
          }
          uVar26 = uVar26 + 1;
        } while (uVar26 < *(uint *)(lVar8 + 0x28));
      }
      local_284 = local_284 + 1;
      uVar17 = (ulong)local_284;
    } while (uVar17 < (ulong)(local_270 - (long)local_278 >> 3));
  }
  if (((*(int *)(this + 0x20) == 0) && (param_3 != (CSkillEffectAndAffixes *)0x0)) &&
     (*(int *)(param_3 + 0x20) != 0)) {
    uVar26 = 0;
    do {
      pCVar10 = (CRunicCore *)Ogre::NedAllocImpl::allocBytes(0x28,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00cb554b to 00cb554f has its CatchHandler @ 00cb680f */
      CRunicCore::CRunicCore(pCVar10);
      *(undefined ***)pCVar10 = &PTR__CSkillAffixData_00ff4f50;
                    /* try { // try from 00cb5564 to 00cb5568 has its CatchHandler @ 00cb67e5 */
      std::wstring::wstring
                ((wstring_conflict *)(pCVar10 + 0x10),(wstring_conflict *)&::EMPTY_WSTRING);
      *(undefined4 *)(pCVar10 + 0x18) = 0;
      *(undefined4 *)(pCVar10 + 0x1c) = 0;
      *(undefined4 *)(pCVar10 + 0x20) = 0;
      *(undefined4 *)(pCVar10 + 0x24) = 0xbf800000;
                    /* try { // try from 00cb55b6 to 00cb5649 has its CatchHandler @ 00cb68d9 */
      std::wstring::assign((wstring_conflict *)(pCVar10 + 0x10));
      if (uVar26 < *(uint *)(param_3 + 0x24)) {
        plVar16 = (long *)((ulong)uVar26 * 8 + *(long *)(param_3 + 0x18));
      }
      else {
        plVar16 = *(long **)(param_3 + 0x18);
      }
      *(undefined4 *)(pCVar10 + 0x18) = *(undefined4 *)(*plVar16 + 0x18);
      if (uVar26 < *(uint *)(param_3 + 0x24)) {
        plVar16 = (long *)((ulong)uVar26 * 8 + *(long *)(param_3 + 0x18));
      }
      else {
        plVar16 = *(long **)(param_3 + 0x18);
      }
      *(undefined4 *)(pCVar10 + 0x1c) = *(undefined4 *)(*plVar16 + 0x1c);
      if (uVar26 < *(uint *)(param_3 + 0x24)) {
        plVar16 = (long *)((ulong)uVar26 * 8 + *(long *)(param_3 + 0x18));
      }
      else {
        plVar16 = *(long **)(param_3 + 0x18);
      }
      *(undefined4 *)(pCVar10 + 0x20) = *(undefined4 *)(*plVar16 + 0x20);
      uVar5 = *(uint *)(this + 0x20);
      if (uVar5 < *(uint *)(this + 0x24)) {
        pvVar11 = *(void **)(this + 0x18);
      }
      else if (*(long *)(this + 0x18) == 0) {
        *(uint *)(this + 0x24) = *(uint *)(this + 0x28);
                    /* try { // try from 00cb5f30 to 00cb5f34 has its CatchHandler @ 00cb68d9 */
        pvVar11 = operator_new__((ulong)*(uint *)(this + 0x28) * 8);
        *(void **)(this + 0x18) = pvVar11;
        uVar5 = *(uint *)(this + 0x20);
      }
      else {
        uVar23 = *(uint *)(this + 0x24) + *(int *)(this + 0x28);
        pvVar11 = operator_new__((ulong)uVar23 << 3);
        if (*(int *)(this + 0x24) != 0) {
          uVar5 = 0;
          do {
            uVar17 = (ulong)uVar5;
            uVar5 = uVar5 + 1;
            *(undefined8 *)((long)pvVar11 + uVar17 * 8) =
                 *(undefined8 *)(*(long *)(this + 0x18) + uVar17 * 8);
          } while (uVar5 < *(uint *)(this + 0x24));
        }
        if (*(void **)(this + 0x18) != (void *)0x0) {
          operator_delete__(*(void **)(this + 0x18));
        }
        uVar5 = *(uint *)(this + 0x20);
        *(void **)(this + 0x18) = pvVar11;
        *(uint *)(this + 0x24) = uVar23;
      }
      uVar26 = uVar26 + 1;
      *(CRunicCore **)((long)pvVar11 + (ulong)uVar5 * 8) = pCVar10;
      *(int *)(this + 0x20) = *(int *)(this + 0x20) + 1;
    } while (uVar26 < *(uint *)(param_3 + 0x20));
  }
                    /* try { // try from 00cb56c5 to 00cb56c9 has its CatchHandler @ 00cb67dc */
  std::wstring::wstring((wstring_conflict *)local_1a8,L"AFFIXESREMOVE",&local_48);
                    /* try { // try from 00cb56d4 to 00cb56d8 has its CatchHandler @ 00cb67d7 */
  pCVar9 = (CDataGroup *)CDataGroup::GetDataGroupByName(param_2,(wstring_conflict *)local_1a8,false)
  ;
  if ((allocator *)(local_1a8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_1a8[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_1a8[0] + -0x18));
    }
  }
                    /* try { // try from 00cb570e to 00cb5712 has its CatchHandler @ 00cb67a6 */
  std::wstring::wstring((wstring_conflict *)local_1b8,L"EFFECTSREMOVE",&local_49);
                    /* try { // try from 00cb571d to 00cb5721 has its CatchHandler @ 00cb677e */
  this_00 = (CDataGroup *)
            CDataGroup::GetDataGroupByName(param_2,(wstring_conflict *)local_1b8,false);
  if ((allocator *)(local_1b8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_1b8[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_1b8[0] + -0x18));
    }
  }
  if (pCVar9 != (CDataGroup *)0x0) {
                    /* try { // try from 00cb5760 to 00cb5764 has its CatchHandler @ 00cb6741 */
    std::wstring::wstring((wstring_conflict *)local_1c8,L"ADDITIONALDESCRIPTION",&local_4a);
                    /* try { // try from 00cb5770 to 00cb5781 has its CatchHandler @ 00cb6731 */
    CDataGroup::GetDataValue(pCVar9,(wstring_conflict *)local_1c8,local_290);
    std::wstring::assign(local_290);
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
    if (*(int *)(pCVar9 + 0x28) != 0) {
      uVar26 = 0;
      do {
        if (uVar26 < *(uint *)(pCVar9 + 0x2c)) {
          plVar16 = (long *)((ulong)uVar26 * 8 + *(long *)(pCVar9 + 0x20));
        }
        else {
          plVar16 = *(long **)(pCVar9 + 0x20);
        }
        if ((*(int *)(*plVar16 + 0x30) == 8) || (*(int *)(*plVar16 + 0x30) == 5)) {
          if (uVar26 < *(uint *)(pCVar9 + 0x2c)) {
            puVar27 = (undefined8 *)((ulong)uVar26 * 8 + *(long *)(pCVar9 + 0x20));
          }
          else {
            puVar27 = *(undefined8 **)(pCVar9 + 0x20);
          }
                    /* try { // try from 00cb57f8 to 00cb5811 has its CatchHandler @ 00cb68d9 */
          pwVar7 = (wstring_conflict *)CDataValue::GetValueString((CDataValue *)*puVar27,true);
          std::wstring::wstring((wstring_conflict *)local_1d8,pwVar7);
          uVar5 = *(uint *)(this + 0x68);
          if (uVar5 < *(uint *)(this + 0x6c)) {
            puVar24 = *(ulong **)(this + 0x60);
          }
          else if (*(long *)(this + 0x60) == 0) {
            uVar17 = (ulong)*(uint *)(this + 0x70);
            *(uint *)(this + 0x6c) = *(uint *)(this + 0x70);
                    /* try { // try from 00cb5fab to 00cb5faf has its CatchHandler @ 00cb66ec */
            puVar14 = operator_new__(uVar17 * 8 + 8);
            *puVar14 = uVar17;
            puVar24 = puVar14 + 1;
            while (uVar17 = uVar17 - 1, uVar17 != 0xffffffffffffffff) {
              puVar14[1] = (ulong)&DAT_01424558;
              puVar14 = puVar14 + 1;
            }
            *(ulong **)(this + 0x60) = puVar24;
            uVar5 = *(uint *)(this + 0x68);
          }
          else {
            uVar5 = *(uint *)(this + 0x6c) + *(int *)(this + 0x70);
            uVar17 = (ulong)uVar5;
                    /* try { // try from 00cb583f to 00cb5915 has its CatchHandler @ 00cb66ec */
            puVar14 = operator_new__(uVar17 * 8 + 8);
            *puVar14 = uVar17;
            puVar24 = puVar14 + 1;
            while (uVar17 = uVar17 - 1, uVar17 != 0xffffffffffffffff) {
              puVar14[1] = (ulong)&DAT_01424558;
              puVar14 = puVar14 + 1;
            }
            if (*(int *)(this + 0x6c) != 0) {
              uVar23 = 0;
              do {
                std::wstring::assign((wstring_conflict *)(puVar24 + uVar23));
                uVar23 = uVar23 + 1;
              } while (uVar23 < *(uint *)(this + 0x6c));
            }
            lVar8 = *(long *)(this + 0x60);
            if (lVar8 != 0) {
              plVar16 = (long *)(lVar8 + *(long *)(lVar8 + -8) * 8);
              do {
                plVar15 = *(long **)(this + 0x60);
                while( true ) {
                  do {
                    if (plVar16 == plVar15) {
                      operator_delete__((void *)(*(long *)(this + 0x60) + -8));
                      goto LAB_00cb58f3;
                    }
                    plVar16 = plVar16 + -1;
                    paVar22 = (allocator *)(*plVar16 + -0x18);
                  } while (paVar22 == (allocator *)&std::wstring::_Rep::_S_empty_rep_storage);
                  LOCK();
                  piVar1 = (int *)(*plVar16 + -8);
                  iVar4 = *piVar1;
                  *piVar1 = *piVar1 + -1;
                  UNLOCK();
                  if (0 < iVar4) break;
                  std::wstring::_Rep::_M_destroy(paVar22);
                  plVar15 = *(long **)(this + 0x60);
                }
              } while( true );
            }
LAB_00cb58f3:
            *(ulong **)(this + 0x60) = puVar24;
            *(uint *)(this + 0x6c) = uVar5;
            uVar5 = *(uint *)(this + 0x68);
          }
          std::wstring::assign((wstring_conflict *)(puVar24 + uVar5));
          *(int *)(this + 0x68) = *(int *)(this + 0x68) + 1;
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
        }
        uVar26 = uVar26 + 1;
      } while (uVar26 < *(uint *)(pCVar9 + 0x28));
    }
  }
  if (this_00 != (CDataGroup *)0x0) {
                    /* try { // try from 00cb5963 to 00cb5967 has its CatchHandler @ 00cb6671 */
    std::wstring::wstring((wstring_conflict *)local_1e8,L"ADDITIONALDESCRIPTION",&local_4b);
                    /* try { // try from 00cb5973 to 00cb5984 has its CatchHandler @ 00cb6654 */
    CDataGroup::GetDataValue(this_00,(wstring_conflict *)local_1e8,local_290);
    std::wstring::assign(local_290);
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
    if (*(int *)(this_00 + 0x28) != 0) {
      uVar26 = 0;
      do {
        if (uVar26 < *(uint *)(this_00 + 0x2c)) {
          plVar16 = (long *)((ulong)uVar26 * 8 + *(long *)(this_00 + 0x20));
        }
        else {
          plVar16 = *(long **)(this_00 + 0x20);
        }
        if ((*(int *)(*plVar16 + 0x30) == 8) || (*(int *)(*plVar16 + 0x30) == 5)) {
          if (uVar26 < *(uint *)(this_00 + 0x2c)) {
            puVar27 = (undefined8 *)((ulong)uVar26 * 8 + *(long *)(this_00 + 0x20));
          }
          else {
            puVar27 = *(undefined8 **)(this_00 + 0x20);
          }
                    /* try { // try from 00cb5a05 to 00cb5a23 has its CatchHandler @ 00cb68d9 */
          pwVar7 = (wstring_conflict *)CDataValue::GetValueString((CDataValue *)*puVar27,true);
          std::wstring::wstring((wstring_conflict *)local_1f8,pwVar7);
          uVar5 = *(uint *)(this + 0x80);
          if (uVar5 < *(uint *)(this + 0x84)) {
            puVar24 = *(ulong **)(this + 0x78);
          }
          else if (*(long *)(this + 0x78) == 0) {
            uVar17 = (ulong)*(uint *)(this + 0x88);
            *(uint *)(this + 0x84) = *(uint *)(this + 0x88);
                    /* try { // try from 00cb5f5d to 00cb5f61 has its CatchHandler @ 00cb65f4 */
            puVar14 = operator_new__(uVar17 * 8 + 8);
            *puVar14 = uVar17;
            puVar24 = puVar14 + 1;
            while (uVar17 = uVar17 - 1, uVar17 != 0xffffffffffffffff) {
              puVar14[1] = (ulong)&DAT_01424558;
              puVar14 = puVar14 + 1;
            }
            *(ulong **)(this + 0x78) = puVar24;
            uVar5 = *(uint *)(this + 0x80);
          }
          else {
            uVar5 = *(uint *)(this + 0x84) + *(int *)(this + 0x88);
            uVar17 = (ulong)uVar5;
                    /* try { // try from 00cb5a5a to 00cb5b24 has its CatchHandler @ 00cb65f4 */
            puVar14 = operator_new__(uVar17 * 8 + 8);
            *puVar14 = uVar17;
            puVar24 = puVar14 + 1;
            while (uVar17 = uVar17 - 1, uVar17 != 0xffffffffffffffff) {
              puVar14[1] = (ulong)&DAT_01424558;
              puVar14 = puVar14 + 1;
            }
            if (*(int *)(this + 0x84) != 0) {
              uVar23 = 0;
              do {
                std::wstring::assign((wstring_conflict *)(puVar24 + uVar23));
                uVar23 = uVar23 + 1;
              } while (uVar23 < *(uint *)(this + 0x84));
            }
            lVar8 = *(long *)(this + 0x78);
            if (lVar8 != 0) {
              plVar16 = (long *)(lVar8 + *(long *)(lVar8 + -8) * 8);
              do {
                plVar15 = *(long **)(this + 0x78);
                while( true ) {
                  do {
                    if (plVar16 == plVar15) {
                      operator_delete__((void *)(*(long *)(this + 0x78) + -8));
                      goto LAB_00cb5afb;
                    }
                    plVar16 = plVar16 + -1;
                    paVar22 = (allocator *)(*plVar16 + -0x18);
                  } while (paVar22 == (allocator *)&std::wstring::_Rep::_S_empty_rep_storage);
                  LOCK();
                  piVar1 = (int *)(*plVar16 + -8);
                  iVar4 = *piVar1;
                  *piVar1 = *piVar1 + -1;
                  UNLOCK();
                  if (0 < iVar4) break;
                  std::wstring::_Rep::_M_destroy(paVar22);
                  plVar15 = *(long **)(this + 0x78);
                }
              } while( true );
            }
LAB_00cb5afb:
            *(ulong **)(this + 0x78) = puVar24;
            *(uint *)(this + 0x84) = uVar5;
            uVar5 = *(uint *)(this + 0x80);
          }
          std::wstring::assign((wstring_conflict *)(puVar24 + uVar5));
          *(int *)(this + 0x80) = *(int *)(this + 0x80) + 1;
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
        }
        uVar26 = uVar26 + 1;
      } while (uVar26 < *(uint *)(this_00 + 0x28));
    }
  }
                    /* try { // try from 00cb5b6d to 00cb5b71 has its CatchHandler @ 00cb6589 */
  std::wstring::wstring((wstring_conflict *)local_208,L"\n",&local_4c);
                    /* try { // try from 00cb5b8a to 00cb5b8e has its CatchHandler @ 00cb6584 */
  std::wstring::wstring((wstring_conflict *)local_218,L"\\n",&local_4d);
                    /* try { // try from 00cb5b9f to 00cb5ba3 has its CatchHandler @ 00cb657f */
  std::wstring::wstring((wstring_conflict *)local_228,local_290);
                    /* try { // try from 00cb5bb8 to 00cb5bbc has its CatchHandler @ 00cb657a */
  STRINGS::replaceWString
            ((STRINGS *)local_238,(wstring_conflict *)local_228,(wstring_conflict *)local_218,
             (wstring_conflict *)local_208);
                    /* try { // try from 00cb5bc5 to 00cb5bc9 has its CatchHandler @ 00cb64fd */
  std::wstring::assign(local_290);
  if ((allocator *)(local_238[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_238[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_238[0] + -0x18));
    }
  }
  if ((allocator *)(local_228[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_228[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_228[0] + -0x18));
    }
  }
  if ((allocator *)(local_218[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_218[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_218[0] + -0x18));
    }
  }
  if ((allocator *)(local_208[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_208[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_208[0] + -0x18));
    }
  }
                    /* try { // try from 00cb5c4a to 00cb5c4e has its CatchHandler @ 00cb68d9 */
  createAffixesForDisplay(this,*(CResourceManager **)(*(long *)(this + 0x10) + 0x18));
  if (local_278 != (void *)0x0) {
    operator_delete(local_278);
  }
  if (local_258 != (void *)0x0) {
    operator_delete(local_258);
  }
  if ((allocator *)(local_b8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_b8[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
    }
  }
  if ((allocator *)(local_98[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    pwVar13 = local_98[0] + -2;
    wVar2 = *pwVar13;
    *pwVar13 = *pwVar13 + L'\xffffffff';
    UNLOCK();
    if (wVar2 < L'\x01') {
      std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -6));
    }
  }
  if ((allocator *)(local_88[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    pwVar13 = local_88[0] + -2;
    wVar2 = *pwVar13;
    *pwVar13 = *pwVar13 + L'\xffffffff';
    UNLOCK();
    if (wVar2 < L'\x01') {
      std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -6));
    }
  }
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
  return;
}



/* address=00cb6e60
   symbol=CSkillEffectAndAffixes::CSkillEffectData::~CSkillEffectData */

/* CSkillEffectAndAffixes::CSkillEffectData::~CSkillEffectData() */

void __thiscall CSkillEffectAndAffixes::CSkillEffectData::~CSkillEffectData(CSkillEffectData *this)

{
  *(undefined ***)this = &PTR__CSkillEffectData_00ff4ed0;
  if (*(void **)(this + 0x18) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x18));
    *(undefined8 *)(this + 0x18) = 0;
  }
  CRunicCore::~CRunicCore((CRunicCore *)this);
  return;
}



/* address=00cb6e90
   symbol=CSkillEffectAndAffixes::CSkillEffectData::~CSkillEffectData */

/* CSkillEffectAndAffixes::CSkillEffectData::~CSkillEffectData() */

void __thiscall CSkillEffectAndAffixes::CSkillEffectData::~CSkillEffectData(CSkillEffectData *this)

{
  *(undefined ***)this = &PTR__CSkillEffectData_00ff4ed0;
  if (*(void **)(this + 0x18) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x18));
    *(undefined8 *)(this + 0x18) = 0;
  }
  CRunicCore::~CRunicCore((CRunicCore *)this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}



/* address=00cb6ed0
   symbol=CSkillEffectAndAffixes::CSkillAffixData::~CSkillAffixData */

/* WARNING: Removing unreachable block (ram,0x00cb6f20) */
/* CSkillEffectAndAffixes::CSkillAffixData::~CSkillAffixData() */

void __thiscall CSkillEffectAndAffixes::CSkillAffixData::~CSkillAffixData(CSkillAffixData *this)

{
  allocator *paVar1;
  int *piVar2;
  int iVar3;

  *(undefined ***)this = &PTR__CSkillAffixData_00ff4f50;
  paVar1 = (allocator *)(*(long *)(this + 0x10) + -0x18);
  if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0x10) + -8);
    iVar3 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar1);
    }
  }
  CRunicCore::~CRunicCore((CRunicCore *)this);
  return;
}



/* address=00cb6f30
   symbol=CSkillEffectAndAffixes::CSkillAffixData::~CSkillAffixData */

/* WARNING: Removing unreachable block (ram,0x00cb6f88) */
/* CSkillEffectAndAffixes::CSkillAffixData::~CSkillAffixData() */

void __thiscall CSkillEffectAndAffixes::CSkillAffixData::~CSkillAffixData(CSkillAffixData *this)

{
  allocator *paVar1;
  int *piVar2;
  int iVar3;

  *(undefined ***)this = &PTR__CSkillAffixData_00ff4f50;
  paVar1 = (allocator *)(*(long *)(this + 0x10) + -0x18);
  if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0x10) + -8);
    iVar3 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar1);
    }
  }
  CRunicCore::~CRunicCore((CRunicCore *)this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}



/* export-summary functions=20 failures=0 */
