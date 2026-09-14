/* Targeted Ghidra class export.
   namespace=CEffectManager
   Treat pseudocode as navigation evidence. */


/* address=007eb4c0
   symbol=CEffectManager::notifyOfDeletion */

/* CEffectManager::notifyOfDeletion(CCharacter*) */

void CEffectManager::notifyOfDeletion(CCharacter *param_1)

{
  return;
}



/* address=007eb4d0
   symbol=CEffectManager::clearAllUnitReferences */

/* CEffectManager::clearAllUnitReferences() */

void CEffectManager::clearAllUnitReferences(void)

{
  return;
}



/* address=007eb4e0
   symbol=CEffectManager::getEffect */

/* CEffectManager::getEffect(EEFFECT_TYPE) */

undefined8 __thiscall CEffectManager::getEffect(CEffectManager *this,int param_2)

{
  int iVar1;
  uint uVar2;
  long lVar3;
  CEffectManager *pCVar4;
  ulong uVar5;

  uVar5 = 0;
  pCVar4 = this;
  do {
    if (*(uint *)(pCVar4 + 0x30) != 0) {
      lVar3 = 0;
      uVar2 = 0;
      do {
        if (uVar2 < *(uint *)(pCVar4 + 0x34)) {
          iVar1 = *(int *)(*(long *)(lVar3 + *(long *)(pCVar4 + 0x28)) + 0x1c);
        }
        else {
          iVar1 = *(int *)(**(long **)(pCVar4 + 0x28) + 0x1c);
        }
        if (param_2 == iVar1) {
          if (uVar2 < *(uint *)(pCVar4 + 0x34)) {
            return *(undefined8 *)((ulong)uVar2 * 8 + *(long *)(this + uVar5 * 0x18 + 0x28));
          }
          return **(undefined8 **)(this + uVar5 * 0x18 + 0x28);
        }
        uVar2 = uVar2 + 1;
        lVar3 = lVar3 + 8;
      } while (uVar2 < *(uint *)(pCVar4 + 0x30));
    }
    uVar2 = (int)uVar5 + 1;
    uVar5 = (ulong)uVar2;
    pCVar4 = pCVar4 + 0x18;
    if (uVar2 == 2) {
      return 0;
    }
  } while( true );
}



/* address=007eb580
   symbol=CEffectManager::hasEffect */

/* CEffectManager::hasEffect(EEFFECT_TYPE) */

undefined8 __thiscall CEffectManager::hasEffect(CEffectManager *this,int param_2)

{
  int iVar1;
  uint uVar2;
  long lVar3;
  long lVar4;

  lVar4 = 0;
  do {
    if (*(uint *)(this + lVar4 + 0x30) != 0) {
      lVar3 = 0;
      uVar2 = 0;
      do {
        if (uVar2 < *(uint *)(this + lVar4 + 0x34)) {
          iVar1 = *(int *)(*(long *)(lVar3 + *(long *)(this + lVar4 + 0x28)) + 0x1c);
        }
        else {
          iVar1 = *(int *)(**(long **)(this + lVar4 + 0x28) + 0x1c);
        }
        if (param_2 == iVar1) {
          return 1;
        }
        uVar2 = uVar2 + 1;
        lVar3 = lVar3 + 8;
      } while (uVar2 < *(uint *)(this + lVar4 + 0x30));
    }
    lVar4 = lVar4 + 0x18;
    if (lVar4 == 0x30) {
      return 0;
    }
  } while( true );
}



/* address=007eb5f0
   symbol=CEffectManager::getEffectValue */

/* CEffectManager::getEffectValue(EEFFECT_TYPE, EDAMAGE_TYPES) */

float __thiscall CEffectManager::getEffectValue(CEffectManager *this,int param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  long lVar5;
  int iVar6;
  long *plVar7;
  long lVar8;
  long *plVar9;
  float fVar10;
  float fVar11;

  if (param_3 == 7) {
    return *(float *)(this + (long)param_2 * 4 + 0x80);
  }
  fVar10 = 0.0;
  if (*(float *)(this + (long)param_2 * 4 + 0x80) != 0.0) {
    iVar6 = 0;
    do {
      uVar2 = *(uint *)(this + 0x30);
      if (uVar2 != 0) {
        uVar3 = *(uint *)(this + 0x34);
        lVar5 = 0;
        uVar4 = 0;
        do {
          while( true ) {
            if (uVar4 < uVar3) {
              iVar1 = *(int *)(*(long *)(lVar5 + *(long *)(this + 0x28)) + 0x1c);
            }
            else {
              iVar1 = *(int *)(**(long **)(this + 0x28) + 0x1c);
            }
            if (param_2 == iVar1) break;
LAB_007eb645:
            uVar4 = uVar4 + 1;
            lVar5 = lVar5 + 8;
            if (uVar2 <= uVar4) goto LAB_007eb754;
          }
          if (uVar4 < uVar3) {
            plVar7 = (long *)(lVar5 + *(long *)(this + 0x28));
          }
          else {
            plVar7 = *(long **)(this + 0x28);
          }
          if (param_3 != *(int *)(*plVar7 + 0x14)) goto LAB_007eb645;
          if (uVar4 < uVar3) {
            plVar7 = *(long **)(this + 0x28);
            lVar8 = *(long *)((long)plVar7 + lVar5);
            fVar11 = *(float *)(lVar8 + 0xc0);
          }
          else {
            plVar7 = *(long **)(this + 0x28);
            lVar8 = *plVar7;
            fVar11 = *(float *)(lVar8 + 0xc0);
          }
          if (*(float *)(lVar8 + 0x24) != DAT_00fc89b8) {
            plVar9 = plVar7;
            if (uVar4 < uVar3) {
              plVar9 = (long *)(lVar5 + *(long *)(this + 0x28));
            }
            if (*(float *)(*plVar9 + 0x24) != DAT_00fc89bc) {
              plVar9 = plVar7;
              if (uVar4 < uVar3) {
                plVar9 = (long *)(lVar5 + *(long *)(this + 0x28));
              }
              if (*(int *)(*plVar9 + 0x1c) != 7) {
                plVar9 = plVar7;
                if (uVar4 < uVar3) {
                  plVar9 = (long *)(lVar5 + *(long *)(this + 0x28));
                }
                if (*(int *)(*plVar9 + 0x1c) != 6) {
                  plVar9 = plVar7;
                  if (uVar4 < uVar3) {
                    plVar9 = (long *)(lVar5 + *(long *)(this + 0x28));
                  }
                  if (*(int *)(*plVar9 + 0x1c) != 0x7c) {
                    if (uVar4 < uVar3) {
                      plVar7 = (long *)(lVar5 + *(long *)(this + 0x28));
                    }
                    if (*(int *)(*plVar7 + 0x1c) != 0x7b) goto LAB_007eb740;
                  }
                }
              }
              fVar11 = fVar11 * DAT_00fa86dc;
            }
          }
LAB_007eb740:
          uVar4 = uVar4 + 1;
          lVar5 = lVar5 + 8;
          fVar10 = fVar10 + fVar11;
        } while (uVar4 < uVar2);
      }
LAB_007eb754:
      iVar6 = iVar6 + 1;
      this = this + 0x18;
    } while (iVar6 != 2);
  }
  return fVar10;
}



/* address=007eb7c0
   symbol=CEffectManager::getEffectValue */

/* CEffectManager::getEffectValue(EEFFECT_ACTIVATION, EEFFECT_TYPE, EDAMAGE_TYPES) */

float __thiscall
CEffectManager::getEffectValue(CEffectManager *this,int param_2,int param_3,int param_4)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  long lVar5;
  long lVar6;
  long *plVar7;
  float fVar8;
  float fVar9;

  fVar8 = 0.0;
  if (*(float *)(this + (long)param_3 * 4 + 0x80) != 0.0) {
    uVar2 = *(uint *)(this + (long)param_2 * 0x18 + 0x30);
    if (uVar2 != 0) {
      uVar3 = *(uint *)(this + (long)param_2 * 0x18 + 0x34);
      lVar5 = 0;
      uVar4 = 0;
      this = this + (long)param_2 * 0x18 + 0x28;
      do {
        while( true ) {
          if (uVar4 < uVar3) {
            iVar1 = *(int *)(*(long *)(lVar5 + *(long *)this) + 0x1c);
          }
          else {
            iVar1 = *(int *)(**(long **)this + 0x1c);
          }
          if (param_3 == iVar1) break;
LAB_007eb81c:
          uVar4 = uVar4 + 1;
          lVar5 = lVar5 + 8;
          if (uVar2 <= uVar4) {
            return fVar8;
          }
        }
        if (param_4 != 7) {
          if (uVar4 < uVar3) {
            plVar7 = (long *)(lVar5 + *(long *)this);
          }
          else {
            plVar7 = *(long **)this;
          }
          if (param_4 != *(int *)(*plVar7 + 0x14)) goto LAB_007eb81c;
        }
        if (uVar4 < uVar3) {
          lVar6 = *(long *)(*(long *)this + lVar5);
          fVar9 = *(float *)(lVar6 + 0xc0);
        }
        else {
          lVar6 = **(long **)this;
          fVar9 = *(float *)(lVar6 + 0xc0);
        }
        if (*(float *)(lVar6 + 0x24) != DAT_00fc89b8) {
          if (uVar4 < uVar3) {
            plVar7 = (long *)(lVar5 + *(long *)this);
          }
          else {
            plVar7 = *(long **)this;
          }
          if (*(float *)(*plVar7 + 0x24) != DAT_00fc89bc) {
            if (uVar4 < uVar3) {
              iVar1 = *(int *)(*(long *)(lVar5 + *(long *)this) + 0x1c);
            }
            else {
              iVar1 = *(int *)(**(long **)this + 0x1c);
            }
            if (iVar1 != 7) {
              if (uVar4 < uVar3) {
                plVar7 = (long *)(lVar5 + *(long *)this);
              }
              else {
                plVar7 = *(long **)this;
              }
              if (*(int *)(*plVar7 + 0x1c) != 6) {
                if (uVar4 < uVar3) {
                  plVar7 = (long *)(lVar5 + *(long *)this);
                }
                else {
                  plVar7 = *(long **)this;
                }
                if (*(int *)(*plVar7 + 0x1c) != 0x7c) {
                  if (uVar4 < uVar3) {
                    plVar7 = (long *)(lVar5 + *(long *)this);
                  }
                  else {
                    plVar7 = *(long **)this;
                  }
                  if (*(int *)(*plVar7 + 0x1c) != 0x7b) goto LAB_007eb910;
                }
              }
            }
            fVar9 = fVar9 * DAT_00fa86dc;
          }
        }
LAB_007eb910:
        uVar4 = uVar4 + 1;
        lVar5 = lVar5 + 8;
        fVar8 = fVar8 + fVar9;
      } while (uVar4 < uVar2);
    }
  }
  return fVar8;
}



/* address=007eb9c0
   symbol=CEffectManager::hasEffectFromSkill */

/* CEffectManager::hasEffectFromSkill(CSkill const*) */

undefined8 __thiscall CEffectManager::hasEffectFromSkill(CEffectManager *this,CSkill *param_1)

{
  CSkill *pCVar1;
  uint uVar2;
  long lVar3;
  long lVar4;

  lVar4 = 0;
  do {
    if (*(uint *)(this + lVar4 + 0x30) != 0) {
      lVar3 = 0;
      uVar2 = 0;
      do {
        if (uVar2 < *(uint *)(this + lVar4 + 0x34)) {
          pCVar1 = *(CSkill **)(*(long *)(lVar3 + *(long *)(this + lVar4 + 0x28)) + 0x68);
        }
        else {
          pCVar1 = *(CSkill **)(**(long **)(this + lVar4 + 0x28) + 0x68);
        }
        if (param_1 == pCVar1) {
          return 1;
        }
        uVar2 = uVar2 + 1;
        lVar3 = lVar3 + 8;
      } while (uVar2 < *(uint *)(this + lVar4 + 0x30));
    }
    lVar4 = lVar4 + 0x18;
    if (lVar4 == 0x30) {
      return 0;
    }
  } while( true );
}



/* address=007eba30
   symbol=CEffectManager::clearOutDescriptions */

/* CEffectManager::clearOutDescriptions() */

void __thiscall CEffectManager::clearOutDescriptions(CEffectManager *this)

{
  std::wstring::assign((wstring_conflict *)(this + 0x2e0));
  std::wstring::assign((wstring_conflict *)(this + 0x2e8));
  std::wstring::assign((wstring_conflict *)(this + 0x2f0));
  return;
}



/* address=007eba70
   symbol=CEffectManager::removeEffect */

/* CEffectManager::removeEffect(CEffect*, bool) */

undefined8 __thiscall
CEffectManager::removeEffect(CEffectManager *this,CEffect *param_1,bool param_2)

{
  int iVar1;
  CEffect *pCVar2;
  long lVar3;
  long *plVar4;
  undefined8 *puVar5;
  uint uVar6;
  uint uVar7;
  long lVar8;

  lVar8 = (long)*(int *)(param_1 + 0x20);
  if (*(uint *)(this + lVar8 * 0x18 + 0x30) != 0) {
    uVar6 = *(uint *)(this + lVar8 * 0x18 + 0x34);
    uVar7 = 0;
    lVar3 = 0;
    do {
      if (uVar7 < uVar6) {
        pCVar2 = *(CEffect **)(lVar3 + *(long *)(this + lVar8 * 0x18 + 0x28));
      }
      else {
        pCVar2 = (CEffect *)**(long **)(this + lVar8 * 0x18 + 0x28);
      }
      if (param_1 == pCVar2) {
        if (param_2) {
          if (uVar7 < uVar6) {
            plVar4 = (long *)((ulong)uVar7 * 8 + *(long *)(this + lVar8 * 0x18 + 0x28));
          }
          else {
            plVar4 = *(long **)(this + lVar8 * 0x18 + 0x28);
          }
          if (*plVar4 != 0) {
            if (uVar7 < uVar6) {
              plVar4 = (long *)((ulong)uVar7 * 8 + *(long *)(this + lVar8 * 0x18 + 0x28));
            }
            else {
              plVar4 = *(long **)(this + lVar8 * 0x18 + 0x28);
            }
            if ((long *)*plVar4 != (long *)0x0) {
              (**(code **)(*(long *)*plVar4 + 8))();
            }
            iVar1 = *(int *)(pCVar2 + 0x20);
            if (uVar7 < *(uint *)(this + (long)iVar1 * 0x18 + 0x34)) {
              puVar5 = (undefined8 *)
                       ((ulong)uVar7 * 8 + *(long *)(this + (long)iVar1 * 0x18 + 0x28));
            }
            else {
              puVar5 = *(undefined8 **)(this + (long)iVar1 * 0x18 + 0x28);
            }
            *puVar5 = 0;
          }
        }
        iVar1 = *(int *)(pCVar2 + 0x20);
        if (uVar7 < *(uint *)(this + (long)iVar1 * 0x18 + 0x30)) {
          uVar6 = *(uint *)(this + (long)iVar1 * 0x18 + 0x30) - 1;
          *(uint *)(this + (long)iVar1 * 0x18 + 0x30) = uVar6;
          *(undefined8 *)(*(long *)(this + (long)iVar1 * 0x18 + 0x28) + (ulong)uVar7 * 8) =
               *(undefined8 *)(*(long *)(this + (long)iVar1 * 0x18 + 0x28) + (ulong)uVar6 * 8);
        }
        clearOutDescriptions(this);
        return 1;
      }
      uVar7 = uVar7 + 1;
      lVar3 = lVar3 + 8;
    } while (uVar7 < *(uint *)(this + lVar8 * 0x18 + 0x30));
  }
  return 0;
}



/* address=007ebbc0
   symbol=CEffectManager::recalculateEffects */

/* CEffectManager::recalculateEffects() */

void __thiscall CEffectManager::recalculateEffects(CEffectManager *this)

{
  undefined8 *puVar1;
  uint uVar2;
  ulong uVar3;
  long lVar4;

  if (*(long *)(*(long *)(this + 0x2e0) + -0x18) != 0) {
    uVar3 = 0;
    do {
      lVar4 = uVar3 * 8;
      uVar3 = (ulong)((int)uVar3 + 1);
      std::wstring::assign((wstring_conflict *)(this + lVar4 + 0x2e0));
    } while (uVar3 < *(ulong *)(*(long *)(this + 0x2e0) + -0x18));
  }
  lVar4 = 0;
  do {
    if (*(int *)(this + lVar4 + 0x30) != 0) {
      uVar3 = 0;
      do {
        if ((uint)uVar3 < *(uint *)(this + lVar4 + 0x34)) {
          puVar1 = (undefined8 *)(uVar3 * 8 + *(long *)(this + lVar4 + 0x28));
        }
        else {
          puVar1 = *(undefined8 **)(this + lVar4 + 0x28);
        }
        uVar2 = (uint)uVar3 + 1;
        uVar3 = (ulong)uVar2;
        CEffect::getMaxCaculatedValue((CEffect *)*puVar1);
      } while (uVar2 < *(uint *)(this + lVar4 + 0x30));
    }
    lVar4 = lVar4 + 0x18;
  } while (lVar4 != 0x48);
  return;
}



/* address=007ebc60
   symbol=CEffectManager::clearOutAffixEffects */

/* CEffectManager::clearOutAffixEffects() */

void __thiscall CEffectManager::clearOutAffixEffects(CEffectManager *this)

{
  ulong uVar1;
  uint uVar2;

  if (*(int *)(this + 0x18) != 0) {
    uVar2 = 0;
    do {
      while (uVar2 < *(uint *)(this + 0x1c)) {
        uVar1 = (ulong)uVar2;
        uVar2 = uVar2 + 1;
        CAffix::clearEffectsFromOwner(*(CAffix **)(uVar1 * 8 + *(long *)(this + 0x10)));
        if (*(uint *)(this + 0x18) <= uVar2) goto LAB_007ebcab;
      }
      uVar2 = uVar2 + 1;
      CAffix::clearEffectsFromOwner((CAffix *)**(undefined8 **)(this + 0x10));
    } while (uVar2 < *(uint *)(this + 0x18));
  }
LAB_007ebcab:
  clearOutDescriptions(this);
  return;
}



/* address=007ebcc0
   symbol=CEffectManager::addAffixEffectsBackIn */

/* CEffectManager::addAffixEffectsBackIn() */

void __thiscall CEffectManager::addAffixEffectsBackIn(CEffectManager *this)

{
  undefined8 *puVar1;
  uint uVar2;

  if (*(int *)(this + 0x18) != 0) {
    uVar2 = 0;
    do {
      if (uVar2 < *(uint *)(this + 0x1c)) {
        CAffix::clearEffectsFromOwner(*(CAffix **)((ulong)uVar2 * 8 + *(long *)(this + 0x10)));
        if (uVar2 < *(uint *)(this + 0x1c)) goto LAB_007ebd1c;
LAB_007ebce9:
        puVar1 = *(undefined8 **)(this + 0x10);
      }
      else {
        CAffix::clearEffectsFromOwner((CAffix *)**(undefined8 **)(this + 0x10));
        if (*(uint *)(this + 0x1c) <= uVar2) goto LAB_007ebce9;
LAB_007ebd1c:
        puVar1 = (undefined8 *)((ulong)uVar2 * 8 + *(long *)(this + 0x10));
      }
      uVar2 = uVar2 + 1;
      CAffix::addEffectsToEffectManager((CAffix *)*puVar1,this);
    } while (uVar2 < *(uint *)(this + 0x18));
  }
  clearOutDescriptions(this);
  return;
}



/* address=007ebd40
   symbol=CEffectManager::clearEffects */

/* CEffectManager::clearEffects(bool) */

void __thiscall CEffectManager::clearEffects(CEffectManager *this,bool param_1)

{
  long lVar1;
  long *plVar2;
  undefined8 *puVar3;
  uint uVar4;
  uint uVar5;
  ulong uVar6;
  CEffectManager *pCVar7;
  int iVar8;

  iVar8 = 0;
  pCVar7 = this;
  if (param_1) {
    do {
      uVar6 = 0;
      if (*(int *)(pCVar7 + 0x30) != 0) {
        do {
          uVar4 = *(uint *)(pCVar7 + 0x34);
          uVar5 = (uint)uVar6;
          if (uVar5 < uVar4) {
            if (*(int *)(*(long *)(uVar6 * 8 + *(long *)(pCVar7 + 0x28)) + 0x1c) != 0x3e)
            goto LAB_007ebe52;
LAB_007ebef3:
            uVar4 = *(uint *)(pCVar7 + 0x30);
          }
          else {
            if (*(int *)(**(long **)(pCVar7 + 0x28) + 0x1c) == 0x3e) goto LAB_007ebef3;
LAB_007ebe52:
            if (uVar5 < uVar4) {
              plVar2 = (long *)(uVar6 * 8 + *(long *)(pCVar7 + 0x28));
            }
            else {
              plVar2 = *(long **)(pCVar7 + 0x28);
            }
            if (*plVar2 != 0) {
              if (uVar5 < uVar4) {
                plVar2 = (long *)(uVar6 * 8 + *(long *)(pCVar7 + 0x28));
              }
              else {
                plVar2 = *(long **)(pCVar7 + 0x28);
              }
              if ((long *)*plVar2 != (long *)0x0) {
                (**(code **)(*(long *)*plVar2 + 8))();
                uVar4 = *(uint *)(pCVar7 + 0x34);
              }
              if (uVar5 < uVar4) {
                puVar3 = (undefined8 *)(uVar6 * 8 + *(long *)(pCVar7 + 0x28));
              }
              else {
                puVar3 = *(undefined8 **)(pCVar7 + 0x28);
              }
              *puVar3 = 0;
            }
            uVar4 = *(uint *)(pCVar7 + 0x30);
            if (uVar5 < uVar4) {
              *(uint *)(pCVar7 + 0x30) = uVar4 - 1;
              *(undefined8 *)(*(long *)(pCVar7 + 0x28) + uVar6 * 8) =
                   *(undefined8 *)(*(long *)(pCVar7 + 0x28) + (ulong)(uVar4 - 1) * 8);
              uVar4 = *(uint *)(pCVar7 + 0x30);
            }
            uVar5 = uVar5 - 1;
          }
          uVar6 = (ulong)(uVar5 + 1);
        } while (uVar5 + 1 < uVar4);
      }
      iVar8 = iVar8 + 1;
      pCVar7 = pCVar7 + 0x18;
    } while (iVar8 != 3);
  }
  uVar4 = 0;
  if (*(int *)(this + 0x18) != 0) {
    do {
      lVar1 = (ulong)uVar4 * 8;
      plVar2 = (long *)(lVar1 + *(long *)(this + 0x10));
      if ((long *)*plVar2 != (long *)0x0) {
        (**(code **)(*(long *)*plVar2 + 8))();
        *(undefined8 *)(*(long *)(this + 0x10) + (ulong)uVar4 * 8) = 0;
        plVar2 = (long *)(lVar1 + *(long *)(this + 0x10));
      }
      *plVar2 = 0;
      uVar4 = uVar4 + 1;
    } while (uVar4 < *(uint *)(this + 0x18));
  }
  *(undefined4 *)(this + 0x18) = 0;
  *(undefined4 *)(this + 0x1c) = 0;
  if (*(void **)(this + 0x10) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x10));
  }
  *(undefined8 *)(this + 0x10) = 0;
  clearOutDescriptions(this);
  *(undefined4 *)(this + 0x2d0) = 0;
  *(undefined4 *)(this + 0x2d4) = 0;
  if (*(void **)(this + 0x2c8) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x2c8));
  }
  *(undefined8 *)(this + 0x2c8) = 0;
  return;
}



/* address=007ebf30
   symbol=CEffectManager::calculateEffectValues */

/* CEffectManager::calculateEffectValues() */

void __thiscall CEffectManager::calculateEffectValues(CEffectManager *this)

{
  long *plVar1;
  uint uVar2;
  long *plVar3;
  long lVar4;
  long *plVar5;
  long *plVar6;
  uint uVar7;
  uint uVar8;
  long *plVar9;
  ulong uVar10;
  uint uVar11;
  ulong uVar12;
  CEffectManager *pCVar13;
  int iVar14;
  CEffectManager *pCVar15;
  float fVar16;

  *(undefined4 *)(this + 0x2d0) = 0;
  *(undefined4 *)(this + 0x2d4) = 0;
  if (*(void **)(this + 0x2c8) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x2c8));
  }
  *(undefined8 *)(this + 0x2c8) = 0;
  iVar14 = 0;
  pCVar15 = this;
  do {
    *(undefined4 *)(pCVar15 + 0x80) = 0;
    pCVar13 = this;
    do {
      uVar12 = 0;
      if (*(int *)(pCVar13 + 0x30) != 0) {
        do {
          while( true ) {
            uVar7 = *(uint *)(pCVar13 + 0x34);
            uVar11 = (uint)uVar12;
            if (uVar7 <= uVar11) break;
            if (*(int *)(*(long *)(uVar12 * 8 + *(long *)(pCVar13 + 0x28)) + 0x1c) == iVar14)
            goto LAB_007ebfe5;
LAB_007ebfbd:
            uVar12 = (ulong)(uVar11 + 1);
            if (*(uint *)(pCVar13 + 0x30) <= uVar11 + 1) goto LAB_007ec23e;
          }
          if (*(int *)(**(long **)(pCVar13 + 0x28) + 0x1c) != iVar14) goto LAB_007ebfbd;
LAB_007ebfe5:
          if (uVar11 < uVar7) {
            plVar6 = (long *)(uVar12 * 8 + *(long *)(pCVar13 + 0x28));
          }
          else {
            plVar6 = *(long **)(pCVar13 + 0x28);
          }
          lVar4 = *plVar6;
          fVar16 = *(float *)(lVar4 + 0x24);
          if ((((fVar16 != DAT_00fc89b8) && (fVar16 != DAT_00fc89bc)) &&
              (fVar16 <= *(float *)(lVar4 + 0x18))) || (*(char *)(lVar4 + 0x34) != '\0'))
          goto LAB_007ebfbd;
          if (uVar11 < uVar7) {
            plVar6 = *(long **)(pCVar13 + 0x28);
            plVar5 = plVar6 + uVar12;
          }
          else {
            plVar5 = *(long **)(pCVar13 + 0x28);
            plVar6 = plVar5;
          }
          if (*(long *)(*plVar5 + 0x130) != 0) {
            plVar5 = plVar6;
            if (uVar11 < uVar7) {
              plVar5 = plVar6 + uVar12;
            }
            uVar8 = *(uint *)(this + 0x2d0);
            if (uVar8 == 0) {
              plVar3 = *(long **)(this + 0x2c8);
LAB_007ec0a8:
              if (uVar11 < uVar7) {
                plVar6 = plVar6 + uVar12;
              }
              lVar4 = *(long *)(*plVar6 + 0x130);
              if (*(uint *)(this + 0x2d4) <= uVar8) {
                if (plVar3 == (long *)0x0) {
                  *(uint *)(this + 0x2d4) = *(uint *)(this + 0x2d8);
                  plVar3 = operator_new__((ulong)*(uint *)(this + 0x2d8) << 3);
                  uVar8 = *(uint *)(this + 0x2d0);
                  *(long **)(this + 0x2c8) = plVar3;
                }
                else {
                  uVar7 = *(uint *)(this + 0x2d4) + *(int *)(this + 0x2d8);
                  plVar3 = operator_new__((ulong)uVar7 << 3);
                  if (*(int *)(this + 0x2d4) != 0) {
                    uVar10 = 0;
                    do {
                      uVar8 = (int)uVar10 + 1;
                      plVar3[uVar10] = *(long *)(*(long *)(this + 0x2c8) + uVar10 * 8);
                      uVar10 = (ulong)uVar8;
                    } while (uVar8 < *(uint *)(this + 0x2d4));
                  }
                  if (*(void **)(this + 0x2c8) != (void *)0x0) {
                    operator_delete__(*(void **)(this + 0x2c8));
                  }
                  uVar8 = *(uint *)(this + 0x2d0);
                  *(long **)(this + 0x2c8) = plVar3;
                  *(uint *)(this + 0x2d4) = uVar7;
                }
              }
              plVar3[uVar8] = lVar4;
              *(int *)(this + 0x2d0) = *(int *)(this + 0x2d0) + 1;
              uVar7 = *(uint *)(pCVar13 + 0x34);
              plVar6 = *(long **)(pCVar13 + 0x28);
            }
            else {
              plVar3 = *(long **)(this + 0x2c8);
              uVar2 = 0;
              plVar9 = plVar3;
              if (*(long *)(*plVar5 + 0x130) != *plVar3) {
                do {
                  uVar2 = uVar2 + 1;
                  if (uVar8 <= uVar2) goto LAB_007ec0a8;
                  plVar1 = plVar9 + 1;
                  plVar9 = plVar9 + 1;
                } while (*(long *)(*plVar5 + 0x130) != *plVar1);
                if (uVar2 == 0xffffffff) goto LAB_007ec0a8;
              }
            }
          }
          if (uVar11 < uVar7) {
            lVar4 = plVar6[uVar12];
            fVar16 = *(float *)(lVar4 + 0xc0);
          }
          else {
            lVar4 = *plVar6;
            fVar16 = *(float *)(lVar4 + 0xc0);
          }
          if (*(float *)(lVar4 + 0x24) != DAT_00fc89b8) {
            plVar5 = plVar6;
            if (uVar11 < uVar7) {
              plVar5 = plVar6 + uVar12;
            }
            if (*(float *)(*plVar5 + 0x24) != DAT_00fc89bc) {
              plVar5 = plVar6;
              if (uVar11 < uVar7) {
                plVar5 = plVar6 + uVar12;
              }
              if (*(int *)(*plVar5 + 0x1c) != 7) {
                plVar5 = plVar6;
                if (uVar11 < uVar7) {
                  plVar5 = plVar6 + uVar12;
                }
                if (*(int *)(*plVar5 + 0x1c) != 6) {
                  plVar5 = plVar6;
                  if (uVar11 < uVar7) {
                    plVar5 = plVar6 + uVar12;
                  }
                  if (*(int *)(*plVar5 + 0x1c) != 0x7c) {
                    if (uVar11 < uVar7) {
                      plVar6 = plVar6 + uVar12;
                    }
                    if (*(int *)(*plVar6 + 0x1c) != 0x7b) goto LAB_007ec220;
                  }
                }
              }
              fVar16 = fVar16 * DAT_00fa86dc;
            }
          }
LAB_007ec220:
          uVar12 = (ulong)(uVar11 + 1);
          *(float *)(pCVar15 + 0x80) = fVar16 + *(float *)(pCVar15 + 0x80);
        } while (uVar11 + 1 < *(uint *)(pCVar13 + 0x30));
      }
LAB_007ec23e:
      pCVar13 = pCVar13 + 0x18;
    } while (pCVar13 != this + 0x30);
    iVar14 = iVar14 + 1;
    pCVar15 = pCVar15 + 4;
    if (iVar14 == 0x91) {
      return;
    }
  } while( true );
}



/* address=007ec320
   symbol=CEffectManager::updateAffixes */

/* CEffectManager::updateAffixes(float) */

void __thiscall CEffectManager::updateAffixes(CEffectManager *this,float param_1)

{
  bool bVar1;
  bool bVar2;
  char cVar3;
  uint uVar4;
  undefined8 *puVar5;
  long *plVar6;
  uint uVar7;

  if (*(int *)(this + 0x18) != 0) {
    uVar7 = 0;
    bVar2 = false;
    do {
      while( true ) {
        bVar1 = bVar2;
        if (uVar7 < *(uint *)(this + 0x1c)) {
          puVar5 = (undefined8 *)((ulong)uVar7 * 8 + *(long *)(this + 0x10));
        }
        else {
          puVar5 = *(undefined8 **)(this + 0x10);
        }
        cVar3 = CAffix::updateAffixDuration((CAffix *)*puVar5,param_1);
        if (cVar3 == '\0') break;
        uVar7 = uVar7 + 1;
        bVar2 = bVar1;
        if (*(uint *)(this + 0x18) <= uVar7) goto LAB_007ec3e9;
      }
      uVar4 = *(uint *)(this + 0x1c);
      if (uVar7 < uVar4) {
        plVar6 = (long *)((ulong)uVar7 * 8 + *(long *)(this + 0x10));
      }
      else {
        plVar6 = *(long **)(this + 0x10);
      }
      if (*plVar6 != 0) {
        if (uVar7 < uVar4) {
          plVar6 = (long *)((ulong)uVar7 * 8 + *(long *)(this + 0x10));
        }
        else {
          plVar6 = *(long **)(this + 0x10);
        }
        if ((long *)*plVar6 != (long *)0x0) {
          (**(code **)(*(long *)*plVar6 + 8))();
          uVar4 = *(uint *)(this + 0x1c);
        }
        if (uVar7 < uVar4) {
          puVar5 = (undefined8 *)((ulong)uVar7 * 8 + *(long *)(this + 0x10));
        }
        else {
          puVar5 = *(undefined8 **)(this + 0x10);
        }
        *puVar5 = 0;
      }
      uVar4 = *(uint *)(this + 0x18);
      if (uVar7 < uVar4) {
        *(uint *)(this + 0x18) = uVar4 - 1;
        *(undefined8 *)(*(long *)(this + 0x10) + (ulong)uVar7 * 8) =
             *(undefined8 *)(*(long *)(this + 0x10) + (ulong)(uVar4 - 1) * 8);
        uVar4 = *(uint *)(this + 0x18);
      }
      bVar1 = true;
      bVar2 = true;
    } while (uVar7 < uVar4);
LAB_007ec3e9:
    if (bVar1) {
      calculateEffectValues(this);
      clearOutDescriptions(this);
      return;
    }
  }
  return;
}



/* address=007ec450
   symbol=CEffectManager::deleteAffix */

/* CEffectManager::deleteAffix(CAffix*) */

undefined8 __thiscall CEffectManager::deleteAffix(CEffectManager *this,CAffix *param_1)

{
  uint uVar1;
  CAffix *pCVar2;
  uint uVar3;
  long lVar4;

  uVar1 = *(uint *)(this + 0x18);
  if (uVar1 != 0) {
    lVar4 = 0;
    uVar3 = 0;
    do {
      if (uVar3 < *(uint *)(this + 0x1c)) {
        pCVar2 = *(CAffix **)(lVar4 + *(long *)(this + 0x10));
      }
      else {
        pCVar2 = (CAffix *)**(undefined8 **)(this + 0x10);
      }
      if (pCVar2 == param_1) {
        if (uVar3 < uVar1) {
          *(uint *)(this + 0x18) = uVar1 - 1;
          *(undefined8 *)(*(long *)(this + 0x10) + (ulong)uVar3 * 8) =
               *(undefined8 *)(*(long *)(this + 0x10) + (ulong)(uVar1 - 1) * 8);
        }
        CAffix::clearEffectsFromOwner(param_1);
        if (param_1 != (CAffix *)0x0) {
          (**(code **)(*(long *)pCVar2 + 8))(param_1);
        }
        calculateEffectValues(this);
        clearOutDescriptions(this);
        return 1;
      }
      uVar3 = uVar3 + 1;
      lVar4 = lVar4 + 8;
    } while (uVar3 < uVar1);
  }
  return 0;
}



/* address=007ec4f0
   symbol=CEffectManager::addAffix */

/* CEffectManager::addAffix(CAffix*, unsigned int, CBaseUnit*, float) */

CAffix * __thiscall
CEffectManager::addAffix
          (CEffectManager *this,CAffix *param_1,uint param_2,CBaseUnit *param_3,float param_4)

{
  uint uVar1;
  void *pvVar2;
  ulong uVar3;
  uint uVar4;

  if (param_1 != (CAffix *)0x0) {
    if (DAT_00fa47f8 < param_4) {
      *(float *)(param_1 + 0xa4) = param_4;
    }
    if (param_2 != 0xffffffff) {
      CAffix::setLevel(param_1,param_2);
    }
    uVar4 = *(uint *)(this + 0x18);
    if (uVar4 < *(uint *)(this + 0x1c)) {
      pvVar2 = *(void **)(this + 0x10);
    }
    else if (*(long *)(this + 0x10) == 0) {
      *(uint *)(this + 0x1c) = *(uint *)(this + 0x20);
      pvVar2 = operator_new__((ulong)*(uint *)(this + 0x20) << 3);
      *(void **)(this + 0x10) = pvVar2;
      uVar4 = *(uint *)(this + 0x18);
    }
    else {
      uVar4 = *(uint *)(this + 0x1c) + *(int *)(this + 0x20);
      pvVar2 = operator_new__((ulong)uVar4 << 3);
      if (*(int *)(this + 0x1c) != 0) {
        uVar1 = 0;
        do {
          uVar3 = (ulong)uVar1;
          uVar1 = uVar1 + 1;
          *(undefined8 *)((long)pvVar2 + uVar3 * 8) =
               *(undefined8 *)(*(long *)(this + 0x10) + uVar3 * 8);
        } while (uVar1 < *(uint *)(this + 0x1c));
      }
      if (*(void **)(this + 0x10) != (void *)0x0) {
        operator_delete__(*(void **)(this + 0x10));
      }
      *(void **)(this + 0x10) = pvVar2;
      *(uint *)(this + 0x1c) = uVar4;
      uVar4 = *(uint *)(this + 0x18);
    }
    *(CAffix **)((long)pvVar2 + (ulong)uVar4 * 8) = param_1;
    *(int *)(this + 0x18) = *(int *)(this + 0x18) + 1;
    CAffix::setOwner(param_1,param_3);
    CAffix::addEffectsToEffectManager(param_1,this);
    calculateEffectValues(this);
    clearOutDescriptions(this);
  }
  return param_1;
}



/* address=007ec630
   symbol=CEffectManager::cloneAffix */

/* CEffectManager::cloneAffix(CAffix*, unsigned int, CBaseUnit*, float) */

CAffix * __thiscall
CEffectManager::cloneAffix
          (CEffectManager *this,CAffix *param_1,uint param_2,CBaseUnit *param_3,float param_4)

{
  CAffix *this_00;

  this_00 = (CAffix *)0x0;
  if (param_1 != (CAffix *)0x0) {
    this_00 = (CAffix *)Ogre::NedAllocImpl::allocBytes(200,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 007ec68a to 007ec68e has its CatchHandler @ 007ec702 */
    CAffix::CAffix(this_00,param_1,param_2);
    if (this_00 != (CAffix *)0x0) {
      CAffix::addEffectsToEffectManager(this_00,this);
      if (DAT_00fa47f8 < param_4) {
        *(float *)(this_00 + 0xa4) = param_4;
      }
      addAffix(this,this_00,param_2,param_3,param_4);
      clearOutDescriptions(this);
    }
  }
  return this_00;
}



/* address=007ec720
   symbol=CEffectManager::addAffix */

/* CEffectManager::addAffix(std::wstring const&, unsigned int, CBaseUnit*, CResourceManager*, float)
    */

CAffix * __thiscall
CEffectManager::addAffix
          (CEffectManager *this,wstring_conflict *param_1,uint param_2,CBaseUnit *param_3,
          CResourceManager *param_4,float param_5)

{
  CAffix *pCVar1;

  pCVar1 = (CAffix *)0x0;
  if (param_4 != (CResourceManager *)0x0) {
    pCVar1 = (CAffix *)CResourceManager::getNewAffixByName(param_4,param_1,param_2);
    addAffix(this,pCVar1,param_2,param_3,param_5);
    clearOutDescriptions(this);
  }
  return pCVar1;
}



/* address=007ec7a0
   symbol=CEffectManager::transferEffects */

/* CEffectManager::transferEffects(CCharacter*, EEFFECT_ACTIVATION, EEFFECT_TYPE) */

void __thiscall
CEffectManager::transferEffects(CEffectManager *this,long *param_1,int param_3,int param_4)

{
  int iVar1;
  undefined4 uVar2;
  char cVar3;
  long lVar4;
  long *plVar5;
  long *plVar6;
  uint uVar7;
  CEffectManager *pCVar8;
  CEffect *pCVar9;

  if (*(int *)(this + (long)param_3 * 0x18 + 0x30) != 0) {
    uVar7 = 0;
    pCVar8 = this + (long)param_3 * 0x18 + 0x28;
    do {
      while( true ) {
        if (uVar7 < *(uint *)(this + (long)param_3 * 0x18 + 0x34)) {
          iVar1 = *(int *)(*(long *)((ulong)uVar7 * 8 + *(long *)pCVar8) + 0x1c);
        }
        else {
          iVar1 = *(int *)(**(long **)pCVar8 + 0x1c);
        }
        if ((param_4 == iVar1) &&
           (cVar3 = (**(code **)(*param_1 + 0x238))(param_1,param_1,*(undefined8 *)(this + 0x70)),
           cVar3 != '\0')) break;
        uVar7 = uVar7 + 1;
        if (*(uint *)(this + (long)param_3 * 0x18 + 0x30) <= uVar7) {
          return;
        }
      }
      if (uVar7 < *(uint *)(this + (long)param_3 * 0x18 + 0x34)) {
        lVar4 = *(long *)(*(long *)pCVar8 + (ulong)uVar7 * 8);
                    /* WARNING: Load size is inaccurate */
        pCVar9._0_4_ = *(CEffect **)(lVar4 + 0x24);
      }
      else {
        lVar4 = **(long **)pCVar8;
                    /* WARNING: Load size is inaccurate */
        pCVar9._0_4_ = *(CEffect **)(lVar4 + 0x24);
      }
      uVar2 = *(undefined4 *)(lVar4 + 0xc0);
      plVar5 = (long *)Ogre::NedAllocImpl::allocBytes(0x138,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 007ec898 to 007ec89c has its CatchHandler @ 007ec974 */
      CEffect::CEffect(pCVar9._0_4_,uVar2,0,plVar5,param_4,0,1,0);
      *(undefined1 *)((long)plVar5 + 0x33) = 0;
      if (uVar7 < *(uint *)(this + (long)param_3 * 0x18 + 0x34)) {
        plVar6 = (long *)((ulong)uVar7 * 8 + *(long *)pCVar8);
      }
      else {
        plVar6 = *(long **)pCVar8;
      }
      *(undefined1 *)((long)plVar5 + 0x31) = *(undefined1 *)(*plVar6 + 0x31);
      if (uVar7 < *(uint *)(this + (long)param_3 * 0x18 + 0x34)) {
        plVar6 = (long *)((ulong)uVar7 * 8 + *(long *)pCVar8);
      }
      else {
        plVar6 = *(long **)pCVar8;
      }
      uVar7 = uVar7 + 1;
      plVar5[0x26] = *(long *)(*plVar6 + 0x130);
      (**(code **)(*param_1 + 0x240))(param_1,param_1,*(undefined8 *)(this + 0x70),plVar5);
      (**(code **)(*plVar5 + 8))(plVar5);
      clearOutDescriptions(this);
    } while (uVar7 < *(uint *)(this + (long)param_3 * 0x18 + 0x30));
  }
  return;
}



/* address=007f27d0
   symbol=CEffectManager::_GLOBAL__I_CEffectManager */

/* CEffectManager::CEffectManager(CBaseUnit*) */

void CEffectManager::_GLOBAL__I_CEffectManager(void)

{
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
  std::string::string((string *)::KLayoutFunctionNames,"GUIEXITGAME",&aStack_22e);
  std::string::string((string *)(::KLayoutFunctionNames + 8),"GUIEXITAPPLICATION",&aStack_22d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x10),"GUINEWGAME",&aStack_22c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x18),"GUICONTINUEGAME",&aStack_22b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x20),"GUINEWGAMEMENU",&aStack_22a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x28),"GUICONTINUEGAMEMENU",&aStack_229);
  std::string::string((string *)(::KLayoutFunctionNames + 0x30),"GUICLOSEMENU",&aStack_228);
  std::string::string((string *)(::KLayoutFunctionNames + 0x38),"GUIBACK",&aStack_227);
  std::string::string((string *)(::KLayoutFunctionNames + 0x40),"GUIDECLINE",&aStack_226);
  std::string::string((string *)(::KLayoutFunctionNames + 0x48),"GUIACCEPT",&aStack_225);
  std::string::string((string *)(::KLayoutFunctionNames + 0x50),"GUIOK",&aStack_224);
  std::string::string((string *)(::KLayoutFunctionNames + 0x58),"GUIPAUSE",&aStack_223);
  std::string::string((string *)(::KLayoutFunctionNames + 0x60),"GUISCROLLUP",&aStack_222);
  std::string::string((string *)(::KLayoutFunctionNames + 0x68),"GUISCROLLDOWN",&aStack_221);
  std::string::string((string *)(::KLayoutFunctionNames + 0x70),"GUISELECT1",&aStack_220);
  std::string::string((string *)(::KLayoutFunctionNames + 0x78),"GUISELECT2",&aStack_21f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x80),"GUISELECT3",&aStack_21e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x88),"GUISELECT4",&aStack_21d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x90),"GUISELECT5",&aStack_21c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x98),"GUISELECT6",&aStack_21b);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa0),"GUISELECT7",&aStack_21a);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa8),"GUISELECT8",&aStack_219);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb0),"GUISELECT9",&aStack_218);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb8),"GUISELECT10",&aStack_217);
  std::string::string((string *)(::KLayoutFunctionNames + 0xc0),"GUISELECT11",&aStack_216);
  std::string::string((string *)(::KLayoutFunctionNames + 200),"GUISELECT12",&aStack_215);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd0),"GUISELECT13",&aStack_214);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd8),"GUISELECT14",&aStack_213);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe0),"GUISELECT15",&aStack_212);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe8),"GUISELECT16",&aStack_211);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf0),"GUISELECT17",&aStack_210);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf8),"GUISELECT18",&aStack_20f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x100),"GUISELECT19",&aStack_20e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x108),"GUISELECT20",&aStack_20d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x110),"GUISELECT21",&aStack_20c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x118),"GUISELECT22",&aStack_20b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x120),"GUISELECT23",&aStack_20a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x128),"GUISELECT24",&aStack_209);
  std::string::string((string *)(::KLayoutFunctionNames + 0x130),"GUISELECT25",&aStack_208);
  std::string::string((string *)(::KLayoutFunctionNames + 0x138),"GUISELECT26",&aStack_207);
  std::string::string((string *)(::KLayoutFunctionNames + 0x140),"GUISELECT27",&aStack_206);
  std::string::string((string *)(::KLayoutFunctionNames + 0x148),"GUISELECT28",&aStack_205);
  std::string::string((string *)(::KLayoutFunctionNames + 0x150),"GUISELECT29",&aStack_204);
  std::string::string((string *)(::KLayoutFunctionNames + 0x158),"GUISELECT30",&aStack_203);
  std::string::string((string *)(::KLayoutFunctionNames + 0x160),"GUISELECT31",&aStack_202);
  std::string::string((string *)(::KLayoutFunctionNames + 0x168),"GUISELECT32",&aStack_201);
  std::string::string((string *)(::KLayoutFunctionNames + 0x170),"GUISELECT33",&aStack_200);
  std::string::string((string *)(::KLayoutFunctionNames + 0x178),"GUISELECT34",&aStack_1ff);
  std::string::string((string *)(::KLayoutFunctionNames + 0x180),"GUISELECT35",&aStack_1fe);
  std::string::string((string *)(::KLayoutFunctionNames + 0x188),"GUISELECT36",&aStack_1fd);
  std::string::string((string *)(::KLayoutFunctionNames + 400),"GUISELECT37",&aStack_1fc);
  std::string::string((string *)(::KLayoutFunctionNames + 0x198),"GUISELECT38",&aStack_1fb);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a0),"GUISELECT39",&aStack_1fa);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a8),"GUISELECT40",&aStack_1f9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b0),"GUISELECT41",&aStack_1f8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b8),"GUISELECT42",&aStack_1f7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c0),"GUISELECT43",&aStack_1f6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c8),"GUISELECT44",&aStack_1f5);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d0),"GUISELECT45",&aStack_1f4);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d8),"GUISELECT46",&aStack_1f3);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e0),"GUISELECT47",&aStack_1f2);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e8),"GUISELECT48",&aStack_1f1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f0),"GUISELECT49",&aStack_1f0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f8),"GUISELECT50",&aStack_1ef);
  std::string::string((string *)(::KLayoutFunctionNames + 0x200),"GUISELECTA",&aStack_1ee);
  std::string::string((string *)(::KLayoutFunctionNames + 0x208),"GUISELECTB",&aStack_1ed);
  std::string::string((string *)(::KLayoutFunctionNames + 0x210),"GUISELECTC",&aStack_1ec);
  std::string::string((string *)(::KLayoutFunctionNames + 0x218),"GUISELECTD",&aStack_1eb);
  std::string::string((string *)(::KLayoutFunctionNames + 0x220),"GUIFEEDPET",&aStack_1ea);
  std::string::string((string *)(::KLayoutFunctionNames + 0x228),"GUIPETPASSIVE",&aStack_1e9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x230),"GUIPETAGGRESSIVE",&aStack_1e8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x238),"GUIPETDEFENSIVE",&aStack_1e7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x240),"GUITOGGLEINVENTORY",&aStack_1e6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x248),"GUITOGGLEQUESTS",&aStack_1e5);
  std::string::string((string *)(::KLayoutFunctionNames + 0x250),"GUITOGGLESTATS",&aStack_1e4);
  std::string::string((string *)(::KLayoutFunctionNames + 600),"GUITOGGLESKILLS",&aStack_1e3);
  std::string::string((string *)(::KLayoutFunctionNames + 0x260),"GUITOGGLEPERKS",&aStack_1e2);
  std::string::string((string *)(::KLayoutFunctionNames + 0x268),"GUITOGGLEJOURNAL",&aStack_1e1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x270),"GUITOGGLEPET",&aStack_1e0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x278),"GUITOGGLEAUTOMAP",&aStack_1df);
  std::string::string((string *)(::KLayoutFunctionNames + 0x280),"GUITOGGLEOPTIONS",&aStack_1de);
  std::string::string((string *)(::KLayoutFunctionNames + 0x288),"GUITOGGLEITEMNAMES",&aStack_1dd);
  std::string::string((string *)(::KLayoutFunctionNames + 0x290),"GUIAUTOMAPZOOMIN",&aStack_1dc);
  std::string::string((string *)(::KLayoutFunctionNames + 0x298),"GUIAUTOMAPZOOMOUT",&aStack_1db);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a0),"GUILEVELUP",&aStack_1da);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a8),"GUISTATSUP",&aStack_1d9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b0),"GUISKILLUP",&aStack_1d8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b8),"GUIPET1",&aStack_1d7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c0),"GUIPET2",&aStack_1d6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c8),"GUIPET3",&aStack_1d5);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d0),"GUIDELETE1",&aStack_1d4);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d8),"GUIDELETE2",&aStack_1d3);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e0),"GUIDELETE3",&aStack_1d2);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e8),"GUIDELETE4",&aStack_1d1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f0),"GUISETTINGSMENU",&aStack_1d0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f8),"GUIPETSELL",&aStack_1cf);
  std::string::string((string *)(::KLayoutFunctionNames + 0x300),"NONE",&aStack_1ce);
  __cxa_atexit(::__tcf_0,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSOUNDBANK_STRINGS,L"STEP_SOUND",&aStack_1cd);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 8),L"STRIKE_SOUND",&aStack_1cc);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x10),L"PHYSICALHIT_SOUND",&aStack_1cb);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x18),L"ICEHIT_SOUND",&aStack_1ca);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x20),L"FIREHIT_SOUND",&aStack_1c9);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x28),L"ELECTRICHIT_SOUND",&aStack_1c8);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x30),L"POISONHIT_SOUND",&aStack_1c7);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x38),L"SHIELDBLOCK",&aStack_1c6);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x40),L"BLOCK",&aStack_1c5);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x48),L"CRITICAL_SOUND",&aStack_1c4);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x50),L"ATTACK_SOUND",&aStack_1c3);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x58),L"IDLE_SOUND",&aStack_1c2)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x60),L"DEATH_SOUND",&aStack_1c1);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x68),L"ROAR_SOUND",&aStack_1c0)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x70),L"FLEE_SOUND",&aStack_1bf)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x78),L"MISS_SOUND",&aStack_1be)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x80),L"FALL_SOUND",&aStack_1bd)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x88),L"LAND_SOUND",&aStack_1bc)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x90),L"TAKE_SOUND",&aStack_1bb)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x98),L"SPAWN_SOUND",&aStack_1ba);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa0),L"USE_SOUND",&aStack_1b9);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa8),L"EQUIP_SOUND",&aStack_1b8);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb0),L"OPENMENU_SOUND",&aStack_1b7);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb8),L"BUY_SOUND",&aStack_1b6);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xc0),L"ERROR_SOUND",&aStack_1b5);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 200),L"LEVELUP_SOUND",&aStack_1b4);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd0),L"EFFORT_SOUND",&aStack_1b3);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd8),L"SPENDPOINT_SOUND",&aStack_1b2);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe0),L"PORTALENTER_SOUND",&aStack_1b1);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe8),L"POERTALEXIT_SOUND",&aStack_1b0);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf0),L"SKILLASSIGN_SOUND",&aStack_1af);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf8),L"QUESTRECEIVED_SOUND",&aStack_1ae);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x100),L"QUESTCOMPLETED_SOUND",&aStack_1ad)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x108),L"LOWMANA_SOUND",&aStack_1ac);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x110),L"MISSILEREFLECT_SOUND",&aStack_1ab)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x118),L"BADEFFECT_SOUND",&aStack_1aa);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x120),L"GOODEFFECT_SOUND",&aStack_1a9);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x128),L"NPCDIALOG_SOUND",&aStack_1a8);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x130),L"NPCGREET",&aStack_1a7);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x138),L"NPCBYE",&aStack_1a6);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x140),L"NPCPURCHASE",&aStack_1a5);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x148),L"NPCSELL",&aStack_1a4);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x150),L"VOICEPETINVENTORYFULL_SOUND",
             &aStack_1a3);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x158),L"VOICEPETDEPARTED_SOUND",
             &aStack_1a2);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x160),L"VOICEPETRETURNED_SOUND",
             &aStack_1a1);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x168),L"VOICEPETFLED_SOUND",&aStack_1a0);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x170),L"VOICEPETLEVELUP_SOUND",&aStack_19f
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x178),L"VOICEINVENTORYFULL_SOUND",
             &aStack_19e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x180),L"VOICEINSUFFICIENTGOLD_SOUND",
             &aStack_19d);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x188),L"VOICEIMPOSSIBLE_SOUND",&aStack_19c
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 400),L"VOICECANTCAST_SOUND",&aStack_19b);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x198),L"VOICECANTCASTHERE_SOUND",
             &aStack_19a);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a0),L"VOICEHEALTHLOW_SOUND",&aStack_199)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a8),L"VOICEMANALOW_SOUND",&aStack_198);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b0),L"VOICETRAPSPRUNG_SOUND",&aStack_197
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b8),L"VOICEREFRESHED_SOUND",&aStack_196)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c0),L"VOICEPOWERFUL_SOUND",&aStack_195);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c8),L"VOICEHEALTHY_SOUND",&aStack_194);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d0),L"VOICEILL_SOUND",&aStack_193);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d8),L"VOICEPOISONED_SOUND",&aStack_192);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e0),L"VOICELEVELUP_SOUND",&aStack_191);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e8),L"VOICEFAMEUP_SOUND",&aStack_190);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f0),L"VOICESKILLUP_SOUND",&aStack_18f);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f8),L"VOICEFORTUNEGOOD_SOUND",
             &aStack_18e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x200),L"VOICEFORTUNEBAD_SOUND",&aStack_18d
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x208),L"VOICESPELLLEARNED_SOUND",
             &aStack_18c);
  ::KSOUNDBANK_STRINGS._528_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_1,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KALIGNMENT_STRINGS,L"NEUTRAL",&aStack_18b);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 8),L"GOOD",&aStack_18a);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x10),L"EVIL",&aStack_189);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x18),L"ALL",&aStack_188);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x20),L"BERSERK",&aStack_187);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x28),L"EVILBERSERK",&aStack_186);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x30),L"GOODBERSERK",&aStack_185);
  __cxa_atexit(::__tcf_2,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KAITYPE_STRINGS,L"NORMAL",&aStack_184);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 8),L"RANGEDDEFENDER",&aStack_183);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x10),L"DEFENDER",&aStack_182);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x18),L"RANGEDCASTER",&aStack_181);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x20),L"CIRCLER",&aStack_180);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x28),L"RESURRECTER",&aStack_17f);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x30),L"DUMMY",&aStack_17e);
  __cxa_atexit(::__tcf_3,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gDAMAGE_TYPES,L"Physical",&aStack_17d);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 8),L"Magical",&aStack_17c);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x10),L"Fire",&aStack_17b);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x18),L"Ice",&aStack_17a);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x20),L"Electric",&aStack_179);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x28),L"Poison",&aStack_178);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x30),L"All",&aStack_177);
  __cxa_atexit(::__tcf_4,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::gTARGET_TYPES,L"USER",&aStack_176);
  std::wstring::wstring((wstring_conflict *)&DAT_01478808,L"ITEM",&aStack_175);
  __cxa_atexit(::__tcf_5,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSFXTypeName,L"STATIONARYTARGET",&aStack_174);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 8),L"STATIONARYOWNER",&aStack_173);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x10),L"STATIONARY",&aStack_172);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x18),L"STATIONARYPORTAL",&aStack_171)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x20),L"BEAM",&aStack_170);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x28),L"FOLLOWOWNER",&aStack_16f);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x30),L"FOLLOWTARGET",&aStack_16e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x38),L"PROJECTILELOCATION",&aStack_16d);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x40),L"PROJECTILECHARACTER",&aStack_16c);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x48),L"PROJECTILELOCATIONERRATIC",&aStack_16b);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x50),L"PROJECTILECHARACTERERRATIC",&aStack_16a);
  __cxa_atexit(::__tcf_6,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KCharacterNames,L"NA",&aStack_169);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 8),L"NA",&aStack_168);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x10),L"NA",&aStack_167);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x18),L"NA",&aStack_166);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x20),L"NA",&aStack_165);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x28),L"NA",&aStack_164);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x30),L"NA",&aStack_163);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x38),L"NA",&aStack_162);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x40),L"Bksp",&aStack_161);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x48),L"Tab",&aStack_160);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x50),L"NA",&aStack_15f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x58),L"NA",&aStack_15e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x60),L"Ctr",&aStack_15d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x68),L"Ret",&aStack_15c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x70),L"NA",&aStack_15b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x78),L"NA",&aStack_15a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x80),L"Shift",&aStack_159);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x88),L"Ctrl",&aStack_158);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x90),L"Alt",&aStack_157);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x98),L"Tab",&aStack_156);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa0),L"NA",&aStack_155);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa8),L"NA",&aStack_154);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb0),L"NA",&aStack_153);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb8),L"NA",&aStack_152);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xc0),L"NA",&aStack_151);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 200),L"NA",&aStack_150);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd0),L"NA",&aStack_14f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd8),L"NA",&aStack_14e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe0),L"NA",&aStack_14d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe8),L"NA",&aStack_14c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf0),L"NA",&aStack_14b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf8),L"NA",&aStack_14a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x100),L"space",&aStack_149);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x108),L"pgup",&aStack_148);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x110),L"pgdn",&aStack_147);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x118),L"end",&aStack_146);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x120),L"home",&aStack_145);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x128),L"left arrow",&aStack_144);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x130),L"up arrow",&aStack_143);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x138),L"right arrow",&aStack_142);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x140),L"down arrow",&aStack_141);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x148),L")",&aStack_140);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x150),L"*",&aStack_13f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x158),L"+",&aStack_13e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x160),L",",&aStack_13d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x168),L"ins",&aStack_13c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x170),L"del",&aStack_13b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x178),L"/",&aStack_13a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x180),L"0",&aStack_139);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x188),L"1",&aStack_138);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 400),L"2",&aStack_137);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x198),L"3",&aStack_136);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a0),L"4",&aStack_135);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a8),L"5",&aStack_134);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b0),L"6",&aStack_133);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b8),L"7",&aStack_132);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c0),L"8",&aStack_131);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c8),L"9",&aStack_130);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d0),L":",&aStack_12f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d8),L";",&aStack_12e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e0),L"<",&aStack_12d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e8),L"=",&aStack_12c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f0),L">",&aStack_12b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f8),L"?",&aStack_12a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x200),L"@",&aStack_129);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x208),L"a",&aStack_128);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x210),L"b",&aStack_127);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x218),L"c",&aStack_126);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x220),L"d",&aStack_125);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x228),L"e",&aStack_124);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x230),L"NA",&aStack_123);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x238),L"g",&aStack_122);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x240),L"h",&aStack_121);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x248),L"i",&aStack_120);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x250),L"j",&aStack_11f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 600),L"k",&aStack_11e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x260),L"l",&aStack_11d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x268),L"m",&aStack_11c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x270),L"n",&aStack_11b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x278),L"o",&aStack_11a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x280),L"p",&aStack_119);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x288),L"NA",&aStack_118);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x290),L"r",&aStack_117);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x298),L"s",&aStack_116);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a0),L"t",&aStack_115);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a8),L"u",&aStack_114);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b0),L"v",&aStack_113);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b8),L"w",&aStack_112);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c0),L"x",&aStack_111);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c8),L"y",&aStack_110);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d0),L"z",&aStack_10f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d8),L"[",&aStack_10e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e0),L"\\",&aStack_10d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e8),L"]",&aStack_10c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f0),L"^",&aStack_10b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f8),L"_",&aStack_10a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x300),L"NUM 0",&aStack_109);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x308),L"NUM 1",&aStack_108);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x310),L"NUM 2",&aStack_107);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x318),L"NUM 3",&aStack_106);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 800),L"NUM 4",&aStack_105);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x328),L"NUM 5",&aStack_104);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x330),L"NUM 6",&aStack_103);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x338),L"NUM 7",&aStack_102);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x340),L"NUM 8",&aStack_101);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x348),L"NUM 9",&aStack_100);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x350),L"*",&aStack_ff);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x358),L"+",&aStack_fe);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x360),L"NA",&aStack_fd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x368),L"-",&aStack_fc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x370),L"NA",&aStack_fb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x378),L"F1",&aStack_fa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x380),L"F2",&aStack_f9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x388),L"F3",&aStack_f8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x390),L"F4",&aStack_f7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x398),L"F5",&aStack_f6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a0),L"F6",&aStack_f5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a8),L"F7",&aStack_f4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b0),L"F8",&aStack_f3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b8),L"F9",&aStack_f2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c0),L"F10",&aStack_f1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c8),L"F11",&aStack_f0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d0),L"F12",&aStack_ef);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d8),L"{",&aStack_ee);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3e0),L"|",&aStack_ed);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 1000),L"}",&aStack_ec);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f0),L"~",&aStack_eb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f8),L";",&aStack_ea);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x400),L"=",&aStack_e9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x408),L".",&aStack_e8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x410),L"-",&aStack_e7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x418),L",",&aStack_e6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x420),L"/",&aStack_e5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x428),L"`",&aStack_e4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x430),L"[",&aStack_e3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x438),L"\\",&aStack_e2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x440),L"]",&aStack_e1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x448),L"\'",&aStack_e0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x450),L"NA",&aStack_df);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x458),L"NA",&aStack_de);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x460),L"NA",&aStack_dd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x468),L"NA",&aStack_dc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x470),L"NA",&aStack_db);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x478),L"NA",&aStack_da);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x480),L"NA",&aStack_d9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x488),L"NA",&aStack_d8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x490),L"NA",&aStack_d7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x498),L"NA",&aStack_d6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a0),L"NA",&aStack_d5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a8),L"NA",&aStack_d4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b0),L"NA",&aStack_d3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b8),L"NA",&aStack_d2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c0),L"NA",&aStack_d1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c8),L"NA",&aStack_d0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d0),L"NA",&aStack_cf);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d8),L"NA",&aStack_ce);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e0),L"NA",&aStack_cd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e8),L"NA",&aStack_cc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f0),L"NA",&aStack_cb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f8),L"NA",&aStack_ca);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x500),L"NA",&aStack_c9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x508),L"NA",&aStack_c8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x510),L"NA",&aStack_c7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x518),L"NA",&aStack_c6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x520),L"NA",&aStack_c5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x528),L"NA",&aStack_c4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x530),L"NA",&aStack_c3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x538),L"NA",&aStack_c2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x540),L"NA",&aStack_c1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x548),L"NA",&aStack_c0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x550),L"NA",&aStack_bf);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x558),L"NA",&aStack_be);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x560),L"NA",&aStack_bd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x568),L"NA",&aStack_bc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x570),L"NA",&aStack_bb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x578),L"NA",&aStack_ba);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x580),L"NA",&aStack_b9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x588),L"NA",&aStack_b8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x590),L"NA",&aStack_b7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x598),L"NA",&aStack_b6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a0),L"NA",&aStack_b5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a8),L"NA",&aStack_b4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b0),L"NA",&aStack_b3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b8),L"NA",&aStack_b2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c0),L"NA",&aStack_b1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c8),L"NA",&aStack_b0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d0),L";",&aStack_af);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d8),L"=",&aStack_ae);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e0),L",",&aStack_ad);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e8),L"-",&aStack_ac);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f0),L".",&aStack_ab);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f8),L"/",&aStack_aa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x600),L"`",&aStack_a9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x608),L"NA",&aStack_a8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x610),L"NA",&aStack_a7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x618),L"NA",&aStack_a6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x620),L"NA",&aStack_a5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x628),L"NA",&aStack_a4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x630),L"NA",&aStack_a3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x638),L"NA",&aStack_a2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x640),L"NA",&aStack_a1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x648),L"NA",&aStack_a0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x650),L"NA",&aStack_9f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x658),L"NA",&aStack_9e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x660),L"NA",&aStack_9d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x668),L"NA",&aStack_9c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x670),L"NA",&aStack_9b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x678),L"NA",&aStack_9a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x680),L"NA",&aStack_99);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x688),L"NA",&aStack_98);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x690),L"NA",&aStack_97);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x698),L"NA",&aStack_96);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a0),L"NA",&aStack_95);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a8),L"NA",&aStack_94);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b0),L"NA",&aStack_93);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b8),L"NA",&aStack_92);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c0),L"NA",&aStack_91);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c8),L"NA",&aStack_90);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d0),L"NA",&aStack_8f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d8),L"[",&aStack_8e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e0),L"\\",&aStack_8d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e8),L"]",&aStack_8c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f0),L"\'",&aStack_8b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f8),L"NA",&aStack_8a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x700),L"NA",&aStack_89);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x708),L"NA",&aStack_88);
  __cxa_atexit(::__tcf_7,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEffect_Activation_Names,L"PASSIVE",&aStack_87);
  std::wstring::wstring((wstring_conflict *)(::gEffect_Activation_Names + 8),L"DYNAMIC",&aStack_86);
  std::wstring::wstring
            ((wstring_conflict *)(::gEffect_Activation_Names + 0x10),L"TRANSFER",&aStack_85);
  __cxa_atexit(::__tcf_8,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEFFECT_STAT_MODIFIER_NAMES,L"MELEE",&aStack_84);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 8),L"RANGED",&aStack_83);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x10),L"DEFENSE",&aStack_82);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x18),L"MAGIC",&aStack_81);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x20),L"LEVEL",&aStack_80);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x28),L"OWNERLEVEL",&aStack_7f);
  __cxa_atexit(::__tcf_9,0,&__dso_handle);
  std::string::string((string *)::gEFFECT_STAT_MODIFIER_ICON_NAMES,"iconmelee",&aStack_7e);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 8),"iconranged",&aStack_7d);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x10),"icondefense",&aStack_7c
                     );
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x18),"iconmagic",&aStack_7b);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x20),"iconmagic",&aStack_7a);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x28),"iconmagic",&aStack_79);
  __cxa_atexit(::__tcf_10,0,&__dso_handle);
  ParticleUniverse::HALFSCALE._4_4_ = DAT_0142463c * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._0_4_ = Ogre::Vector3::UNIT_SCALE * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._8_4_ = DAT_00fa4810 * DAT_01424640;
  std::string::string((string *)&ParticleUniverse::ALIAS,"1",&aStack_78);
  __cxa_atexit(std::string::~string,&ParticleUniverse::ALIAS,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::SYSTEM,"2",&aStack_77);
  __cxa_atexit(std::string::~string,&ParticleUniverse::SYSTEM,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::TECHNIQUE,"3",&aStack_76);
  __cxa_atexit(std::string::~string,&ParticleUniverse::TECHNIQUE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::RENDERER,"4",&aStack_75);
  __cxa_atexit(std::string::~string,&ParticleUniverse::RENDERER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EMITTER,"5",&aStack_74);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EMITTER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::AFFECTOR,"6",&aStack_73);
  __cxa_atexit(std::string::~string,&ParticleUniverse::AFFECTOR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::OBSERVER,"7",&aStack_72);
  __cxa_atexit(std::string::~string,&ParticleUniverse::OBSERVER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::HANDLER,"8",&aStack_71);
  __cxa_atexit(std::string::~string,&ParticleUniverse::HANDLER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::BEHAVIOUR,"9",&aStack_70);
  __cxa_atexit(std::string::~string,&ParticleUniverse::BEHAVIOUR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EXTERN,"10",&aStack_6f);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EXTERN,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DYNAMIC_ATTRIBUTE,"11",&aStack_6e);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DYNAMIC_ATTRIBUTE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DEPENDENCY,"12",&aStack_6d);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DEPENDENCY,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_TYPE_NAMES,L"",&aStack_6c);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 8),L"FIND",&aStack_6b);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x10),L"KILL NUM",&aStack_6a);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x18),L"KILL BOSS",&aStack_69);
  __cxa_atexit(::__tcf_11,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_DIALOG_TYPE_NAMES,L"ERROR",&aStack_68);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 8),L"INTRO",&aStack_67);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x10),L"RETURN",&aStack_66);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x18),L"COMPLETE",&aStack_65);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x20),L"PASSIVE",&aStack_64);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x28),L"DETAILS",&aStack_63);
  __cxa_atexit(::__tcf_12,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES,"tag_righthand",&aStack_62);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 8),"tag_lefthand",&aStack_61);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x10),"",&aStack_60);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x18),"Bip01 Head",&aStack_5f);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x20),"",&aStack_5e);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x28),"Bip01 L Clavicle",&aStack_5d);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x30),"",&aStack_5c);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x38),"",&aStack_5b);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x40),"",&aStack_5a);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x48),"",&aStack_59);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x50),"",&aStack_58);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x58),"tag_leftarm",&aStack_57);
  __cxa_atexit(::__tcf_13,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES_SECONDARY,"",&aStack_56);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 8),"",&aStack_55);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x10),"",&aStack_54);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x18),"",&aStack_53);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x20),"",&aStack_52);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x28),"Bip01 R Clavicle",
                      &aStack_51);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x30),"",&aStack_50);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x38),"",&aStack_4f);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x40),"",&aStack_4e);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x48),"",&aStack_4d);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x50),"",&aStack_4c);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x58),"",&aStack_4b);
  __cxa_atexit(::__tcf_14,0,&__dso_handle);
  std::string::string((string *)::KEquipmentIconName,"EquipLeftHand",&aStack_4a);
  std::string::string((string *)(::KEquipmentIconName + 8),"EquipRightHand",&aStack_49);
  std::string::string((string *)(::KEquipmentIconName + 0x10),"EquipGloves",&aStack_48);
  std::string::string((string *)(::KEquipmentIconName + 0x18),"EquipHelm",&aStack_47);
  std::string::string((string *)(::KEquipmentIconName + 0x20),"EquipChest",&aStack_46);
  std::string::string((string *)(::KEquipmentIconName + 0x28),"EquipShoulder",&aStack_45);
  std::string::string((string *)(::KEquipmentIconName + 0x30),"EquipBoots",&aStack_44);
  std::string::string((string *)(::KEquipmentIconName + 0x38),"EquipBelt",&aStack_43);
  std::string::string((string *)(::KEquipmentIconName + 0x40),"EquipRing1",&aStack_42);
  std::string::string((string *)(::KEquipmentIconName + 0x48),"EquipRing2",&aStack_41);
  std::string::string((string *)(::KEquipmentIconName + 0x50),"EquipAmulet",&aStack_40);
  std::string::string((string *)(::KEquipmentIconName + 0x58),"",&aStack_3f);
  __cxa_atexit(::__tcf_15,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames,L"CHEST",&aStack_3e);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 8),L"GLOVES",&aStack_3d);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x10),L"BOOTS",&aStack_3c);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x18),L"HELMET",&aStack_3b);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x20),L"SHOULDERS",&aStack_3a);
  __cxa_atexit(::__tcf_16,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames2,L"",&aStack_39);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 8),L"",&aStack_38);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x10),L"",&aStack_37);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x18),L"FACE",&aStack_36);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x20),L"",&aStack_35);
  __cxa_atexit(::__tcf_17,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_EVENT_TYPE_NAMES,L"EVENT_START",&aStack_34);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 8),L"EVENT_END",&aStack_33)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x10),L"EVENT_TRIGGER",&aStack_32);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x18),L"EVENT_TRIGGER_TWO",&aStack_31)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x20),L"EVENT_UNITHIT",&aStack_30);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x28),L"EVENT_UNITDIE",&aStack_2f);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x30),L"EVENT_MISSILEHIT",&aStack_2e);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x38),L"EVENT_MISSILEDIE",&aStack_2d);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x40),L"EVENT_DIEBYEFFECT",&aStack_2c)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x48),L"EVENT_CASTERDIE",&aStack_2b);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x50),L"EVENT_UNIT_CREATE",&aStack_2a)
  ;
  __cxa_atexit(::__tcf_18,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_TARGET_TYPE_NAMES,L"NONE",&aStack_29);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 8),L"POSITION",&aStack_28)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x10),L"TARGET",&aStack_27);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x18),L"SELF",&aStack_26);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x20),L"EVERYBODY",&aStack_25);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x28),L"POSITIONRANDOM",&aStack_24);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x30),L"POSITIONFLEE",&aStack_23);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x38),L"ITEM",&aStack_22);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x40),L"UNIDENTIFIEDITEM",&aStack_21)
  ;
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x48),L"PETS",&aStack_20);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x50),L"SELFANDPETS",&aStack_1f);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x58),L"TARGET_POS",&aStack_1e);
  __cxa_atexit(::__tcf_19,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_ACTIVATION_TYPE_NAMES,L"ANY",&aStack_1d);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 8),L"PROC",&aStack_1c)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 0x10),L"WEAPON",&aStack_1b);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 0x18),L"NORMAL",&aStack_1a);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 0x20),L"PASSIVE",&aStack_19);
  __cxa_atexit(::__tcf_20,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_TYPE_NAMES,L"SKILL",&aStack_18);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TYPE_NAMES + 8),L"OFFENSIVE",&aStack_17);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TYPE_NAMES + 0x10),L"DEFENSIVE",&aStack_16);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TYPE_NAMES + 0x18),L"CHARM",&aStack_15);
  ::gSKILL_TYPE_NAMES._32_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_21,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_TYPE_DISPLAY_NAMES,L"Class Skill",&aStack_14);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TYPE_DISPLAY_NAMES + 8),L"Offensive Spell",&aStack_13);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TYPE_DISPLAY_NAMES + 0x10),L"Defensive Spell",&aStack_12)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TYPE_DISPLAY_NAMES + 0x18),L"Charm Spell",&aStack_11);
  ::gSKILL_TYPE_DISPLAY_NAMES._32_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_22,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_BONE_ATTACHMENT_NAMES,L"",&aStack_10);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 8),L"CENTER",&aStack_f);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x10),L"HEAD",&aStack_e);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x18),L"RIGHTHAND",&aStack_d);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x20),L"LEFTHAND",&aStack_c);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x28),L"RIGHTSHOULDER",&aStack_b)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x30),L"LEFTSHOULDER",&aStack_a);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x38),L"POSITION",&aStack_9);
  __cxa_atexit(::__tcf_23,0,&__dso_handle);
  return;
}



/* address=007f2a30
   symbol=CEffectManager::getEffects */

/* CEffectManager::getEffects(TArrayList<CEffect*>*) */

void __thiscall CEffectManager::getEffects(CEffectManager *this,TArrayList *param_1)

{
  uint uVar1;
  undefined8 uVar2;
  void *pvVar3;
  ulong uVar4;
  uint uVar5;
  uint uVar6;
  undefined8 *puVar7;
  uint uVar8;
  long local_40;

  if (param_1 != (TArrayList *)0x0) {
    local_40 = 0;
    do {
      uVar1 = *(uint *)(this + local_40 + 0x30);
      puVar7 = *(undefined8 **)(this + local_40 + 0x28);
      if ((puVar7 != (undefined8 *)0x0) && (uVar1 != 0)) {
        uVar5 = *(uint *)(param_1 + 8);
        uVar6 = 0;
        do {
          uVar2 = *puVar7;
          if (uVar5 < *(uint *)(param_1 + 0xc)) {
            pvVar3 = *(void **)param_1;
          }
          else if (*(long *)param_1 == 0) {
            *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0x10);
            pvVar3 = operator_new__((ulong)*(uint *)(param_1 + 0x10) << 3);
            uVar5 = *(uint *)(param_1 + 8);
            *(void **)param_1 = pvVar3;
          }
          else {
            uVar8 = *(uint *)(param_1 + 0xc) + *(int *)(param_1 + 0x10);
            pvVar3 = operator_new__((ulong)uVar8 << 3);
            if (*(int *)(param_1 + 0xc) != 0) {
              uVar5 = 0;
              do {
                uVar4 = (ulong)uVar5;
                uVar5 = uVar5 + 1;
                *(undefined8 *)((long)pvVar3 + uVar4 * 8) =
                     *(undefined8 *)(*(long *)param_1 + uVar4 * 8);
              } while (uVar5 < *(uint *)(param_1 + 0xc));
            }
            if (*(void **)param_1 != (void *)0x0) {
              operator_delete__(*(void **)param_1);
            }
            uVar5 = *(uint *)(param_1 + 8);
            *(void **)param_1 = pvVar3;
            *(uint *)(param_1 + 0xc) = uVar8;
          }
          uVar6 = uVar6 + 1;
          puVar7 = puVar7 + 1;
          *(undefined8 *)((long)pvVar3 + (ulong)uVar5 * 8) = uVar2;
          uVar5 = *(int *)(param_1 + 8) + 1;
          *(uint *)(param_1 + 8) = uVar5;
        } while (uVar6 < uVar1);
      }
      local_40 = local_40 + 0x18;
    } while (local_40 != 0x48);
  }
  return;
}



/* address=007f2b70
   symbol=CEffectManager::getAffix */

/* CEffectManager::getAffix(std::wstring const&) */

undefined8 __thiscall CEffectManager::getAffix(CEffectManager *this,wstring_conflict *param_1)

{
  uint uVar1;
  uint uVar2;
  wchar_t *__s2;
  size_t __n;
  wchar_t *__s1;
  size_t sVar3;
  int iVar4;
  uint uVar5;
  undefined8 *puVar6;
  long lVar7;

  uVar1 = *(uint *)(this + 0x18);
  if (uVar1 != 0) {
    __s2 = *(wchar_t **)param_1;
    uVar2 = *(uint *)(this + 0x1c);
    lVar7 = 0;
    uVar5 = 0;
    __n = *(size_t *)(__s2 + -6);
    do {
      if (uVar5 < uVar2) {
        __s1 = *(wchar_t **)(*(long *)(lVar7 + *(long *)(this + 0x10)) + 0x50);
        sVar3 = *(size_t *)(__s1 + -6);
      }
      else {
        __s1 = *(wchar_t **)(**(long **)(this + 0x10) + 0x50);
        sVar3 = *(size_t *)(__s1 + -6);
      }
      if ((sVar3 == __n) && (iVar4 = wmemcmp(__s1,__s2,__n), iVar4 == 0)) {
        if (uVar5 < uVar2) {
          puVar6 = (undefined8 *)((ulong)uVar5 * 8 + *(long *)(this + 0x10));
        }
        else {
          puVar6 = *(undefined8 **)(this + 0x10);
        }
        return *puVar6;
      }
      uVar5 = uVar5 + 1;
      lVar7 = lVar7 + 8;
    } while (uVar5 < uVar1);
  }
  return 0;
}



/* address=007f2c30
   symbol=CEffectManager::removeEffect */

/* CEffectManager::removeEffect(std::wstring const&, bool) */

char __thiscall
CEffectManager::removeEffect(CEffectManager *this,wstring_conflict *param_1,bool param_2)

{
  size_t __n;
  int iVar1;
  long *plVar2;
  undefined8 *puVar3;
  uint uVar4;
  ulong uVar5;
  CEffectManager *pCVar6;
  uint uVar7;
  char cVar8;
  int iVar9;

  iVar9 = 0;
  cVar8 = '\0';
  pCVar6 = this;
  do {
    uVar5 = 0;
    if (*(int *)(pCVar6 + 0x30) != 0) {
      do {
        while( true ) {
          uVar7 = *(uint *)(pCVar6 + 0x34);
          uVar4 = (uint)uVar5;
          if (uVar4 < uVar7) {
            plVar2 = (long *)(uVar5 * 8 + *(long *)(pCVar6 + 0x28));
          }
          else {
            plVar2 = *(long **)(pCVar6 + 0x28);
          }
          __n = *(size_t *)(*(wchar_t **)(*plVar2 + 0x80) + -6);
          if ((__n == *(size_t *)(*(wchar_t **)param_1 + -6)) &&
             (iVar1 = wmemcmp(*(wchar_t **)(*plVar2 + 0x80),*(wchar_t **)param_1,__n), iVar1 == 0))
          break;
          uVar5 = (ulong)(uVar4 + 1);
          if (*(uint *)(pCVar6 + 0x30) <= uVar4 + 1) goto LAB_007f2d3a;
        }
        if (param_2) {
          if (uVar4 < uVar7) {
            plVar2 = (long *)(uVar5 * 8 + *(long *)(pCVar6 + 0x28));
          }
          else {
            plVar2 = *(long **)(pCVar6 + 0x28);
          }
          if (*plVar2 != 0) {
            if (uVar4 < uVar7) {
              plVar2 = (long *)(uVar5 * 8 + *(long *)(pCVar6 + 0x28));
            }
            else {
              plVar2 = *(long **)(pCVar6 + 0x28);
            }
            if ((long *)*plVar2 != (long *)0x0) {
              (**(code **)(*(long *)*plVar2 + 8))();
              uVar7 = *(uint *)(pCVar6 + 0x34);
            }
            if (uVar4 < uVar7) {
              puVar3 = (undefined8 *)(uVar5 * 8 + *(long *)(pCVar6 + 0x28));
            }
            else {
              puVar3 = *(undefined8 **)(pCVar6 + 0x28);
            }
            *puVar3 = 0;
          }
        }
        uVar7 = *(uint *)(pCVar6 + 0x30);
        if (uVar4 < uVar7) {
          *(uint *)(pCVar6 + 0x30) = uVar7 - 1;
          *(undefined8 *)(*(long *)(pCVar6 + 0x28) + uVar5 * 8) =
               *(undefined8 *)(*(long *)(pCVar6 + 0x28) + (ulong)(uVar7 - 1) * 8);
          uVar7 = *(uint *)(pCVar6 + 0x30);
        }
        cVar8 = '\x01';
      } while (uVar4 < uVar7);
    }
LAB_007f2d3a:
    iVar9 = iVar9 + 1;
    pCVar6 = pCVar6 + 0x18;
    if (iVar9 == 3) {
      if (cVar8 != '\0') {
        clearOutDescriptions(this);
      }
      return cVar8;
    }
  } while( true );
}



/* address=007f2da0
   symbol=CEffectManager::deleteAffix */

/* CEffectManager::deleteAffix(std::wstring const&) */

char __thiscall CEffectManager::deleteAffix(CEffectManager *this,wstring_conflict *param_1)

{
  size_t __n;
  int iVar1;
  uint uVar2;
  long *plVar3;
  undefined8 *puVar4;
  uint uVar5;
  char cVar6;

  cVar6 = '\0';
  uVar5 = 0;
  if (*(int *)(this + 0x18) != 0) {
    do {
      while( true ) {
        uVar2 = *(uint *)(this + 0x1c);
        if (uVar5 < uVar2) {
          plVar3 = (long *)((ulong)uVar5 * 8 + *(long *)(this + 0x10));
        }
        else {
          plVar3 = *(long **)(this + 0x10);
        }
        __n = *(size_t *)(*(wchar_t **)(*plVar3 + 0x50) + -6);
        if ((__n == *(size_t *)(*(wchar_t **)param_1 + -6)) &&
           (iVar1 = wmemcmp(*(wchar_t **)(*plVar3 + 0x50),*(wchar_t **)param_1,__n), iVar1 == 0))
        break;
        uVar5 = uVar5 + 1;
        if (*(uint *)(this + 0x18) <= uVar5) goto LAB_007f2e97;
      }
      if (uVar5 < uVar2) {
        puVar4 = (undefined8 *)((ulong)uVar5 * 8 + *(long *)(this + 0x10));
      }
      else {
        puVar4 = *(undefined8 **)(this + 0x10);
      }
      CAffix::clearEffectsFromOwner((CAffix *)*puVar4);
      uVar2 = *(uint *)(this + 0x1c);
      if (uVar5 < uVar2) {
        plVar3 = (long *)((ulong)uVar5 * 8 + *(long *)(this + 0x10));
      }
      else {
        plVar3 = *(long **)(this + 0x10);
      }
      if (*plVar3 != 0) {
        if (uVar5 < uVar2) {
          plVar3 = (long *)((ulong)uVar5 * 8 + *(long *)(this + 0x10));
        }
        else {
          plVar3 = *(long **)(this + 0x10);
        }
        if ((long *)*plVar3 != (long *)0x0) {
          (**(code **)(*(long *)*plVar3 + 8))();
          uVar2 = *(uint *)(this + 0x1c);
        }
        if (uVar5 < uVar2) {
          puVar4 = (undefined8 *)((ulong)uVar5 * 8 + *(long *)(this + 0x10));
        }
        else {
          puVar4 = *(undefined8 **)(this + 0x10);
        }
        *puVar4 = 0;
      }
      uVar2 = *(uint *)(this + 0x18);
      if (uVar5 < uVar2) {
        *(uint *)(this + 0x18) = uVar2 - 1;
        *(undefined8 *)(*(long *)(this + 0x10) + (ulong)uVar5 * 8) =
             *(undefined8 *)(*(long *)(this + 0x10) + (ulong)(uVar2 - 1) * 8);
        uVar2 = *(uint *)(this + 0x18);
      }
      cVar6 = '\x01';
    } while (uVar5 < uVar2);
LAB_007f2e97:
    if (cVar6 != '\0') {
      calculateEffectValues(this);
      clearOutDescriptions(this);
      return cVar6;
    }
  }
  return '\0';
}



/* address=007f2f10
   symbol=CEffectManager::addNewEffect */

/* CEffectManager::addNewEffect(CEffect*) */

CEffect * __thiscall CEffectManager::addNewEffect(CEffectManager *this,CEffect *param_1)

{
  float fVar1;
  size_t __n;
  uint uVar2;
  int iVar3;
  void *pvVar4;
  long *plVar5;
  uint uVar6;
  ulong uVar7;
  long lVar8;
  CEffectManager *pCVar9;
  int iVar10;
  long lVar11;

  iVar10 = 0;
  pCVar9 = this;
  if (param_1[0x31] != (CEffect)0x0) {
    do {
      uVar7 = 0;
      if (*(int *)(pCVar9 + 0x30) != 0) {
        do {
          uVar2 = *(uint *)(pCVar9 + 0x34);
          uVar6 = (uint)uVar7;
          if (uVar6 < uVar2) {
            plVar5 = (long *)(uVar7 * 8 + *(long *)(pCVar9 + 0x28));
          }
          else {
            plVar5 = *(long **)(pCVar9 + 0x28);
          }
          __n = *(size_t *)(*(wchar_t **)(*plVar5 + 0x80) + -6);
          if ((__n == *(size_t *)(*(wchar_t **)(param_1 + 0x80) + -6)) &&
             (iVar3 = wmemcmp(*(wchar_t **)(*plVar5 + 0x80),*(wchar_t **)(param_1 + 0x80),__n),
             iVar3 == 0)) {
            if (uVar6 < uVar2) {
              plVar5 = (long *)(uVar7 * 8 + *(long *)(pCVar9 + 0x28));
            }
            else {
              plVar5 = *(long **)(pCVar9 + 0x28);
            }
            if (*(int *)(*plVar5 + 0x1c) == *(int *)(param_1 + 0x1c)) {
              if (uVar6 < uVar2) {
                plVar5 = (long *)(uVar7 * 8 + *(long *)(pCVar9 + 0x28));
              }
              else {
                plVar5 = *(long **)(pCVar9 + 0x28);
              }
              lVar8 = *plVar5;
              fVar1 = *(float *)(lVar8 + 0x24);
              if ((((fVar1 == DAT_00fc89b8) || (fVar1 == DAT_00fc89bc)) ||
                  (*(float *)(lVar8 + 0x18) < fVar1)) && (*(char *)(lVar8 + 0x34) == '\0')) {
                if (uVar6 < uVar2) {
                  plVar5 = (long *)(uVar7 * 8 + *(long *)(pCVar9 + 0x28));
                }
                else {
                  plVar5 = *(long **)(pCVar9 + 0x28);
                }
                lVar8 = *plVar5;
                fVar1 = *(float *)(lVar8 + 0x24);
                if ((fVar1 != DAT_00fc89b8) && (fVar1 != DAT_00fc89bc)) {
                  *(float *)(lVar8 + 0x18) = fVar1;
                }
                *(undefined1 *)(lVar8 + 0x34) = 1;
              }
            }
          }
          uVar7 = (ulong)(uVar6 + 1);
        } while (uVar6 + 1 < *(uint *)(pCVar9 + 0x30));
      }
      iVar10 = iVar10 + 1;
      pCVar9 = pCVar9 + 0x18;
    } while (iVar10 != 3);
  }
  if ((*(CBaseUnit **)(this + 0x70) != (CBaseUnit *)0x0) && (*(long *)(param_1 + 0x48) == 0)) {
    CEffect::setOwner(param_1,*(CBaseUnit **)(this + 0x70),true);
  }
  lVar8 = (long)*(int *)(param_1 + 0x20);
  lVar11 = lVar8 * 0x18;
  uVar2 = *(uint *)(this + lVar11 + 0x30);
  if (uVar2 < *(uint *)(this + lVar11 + 0x34)) {
    pvVar4 = *(void **)(this + lVar11 + 0x28);
  }
  else if (*(long *)(this + lVar11 + 0x28) == 0) {
    *(undefined4 *)(this + lVar11 + 0x34) = *(undefined4 *)(this + lVar11 + 0x38);
    pvVar4 = operator_new__((ulong)*(uint *)(this + lVar11 + 0x38) << 3);
    *(void **)(this + lVar11 + 0x28) = pvVar4;
    uVar2 = *(uint *)(this + lVar11 + 0x30);
  }
  else {
    uVar2 = *(uint *)(this + lVar11 + 0x34) + *(int *)(this + lVar11 + 0x38);
    pvVar4 = operator_new__((ulong)uVar2 << 3);
    if (*(int *)(this + lVar11 + 0x34) != 0) {
      uVar7 = 0;
      do {
        uVar6 = (int)uVar7 + 1;
        *(undefined8 *)((long)pvVar4 + uVar7 * 8) =
             *(undefined8 *)(*(long *)(this + lVar11 + 0x28) + uVar7 * 8);
        uVar7 = (ulong)uVar6;
      } while (uVar6 < *(uint *)(this + lVar11 + 0x28 + 0xc));
    }
    if (*(void **)(this + lVar8 * 0x18 + 0x28) != (void *)0x0) {
      operator_delete__(*(void **)(this + lVar8 * 0x18 + 0x28));
    }
    *(void **)(this + lVar8 * 0x18 + 0x28) = pvVar4;
    *(uint *)(this + lVar8 * 0x18 + 0x34) = uVar2;
    uVar2 = *(uint *)(this + lVar8 * 0x18 + 0x30);
  }
  *(CEffect **)((long)pvVar4 + (ulong)uVar2 * 8) = param_1;
  *(int *)(this + lVar8 * 0x18 + 0x30) = *(int *)(this + lVar8 * 0x18 + 0x30) + 1;
  clearOutDescriptions(this);
  return param_1;
}



/* address=007f31a0
   symbol=CEffectManager::cloneEffect */

/* CEffectManager::cloneEffect(CBaseUnit*, CEffect*) */

CEffect * __thiscall
CEffectManager::cloneEffect(CEffectManager *this,CBaseUnit *param_1,CEffect *param_2)

{
  CEffect *this_00;

  if ((*(long *)(param_2 + 0xb8) == 0) ||
     (this != *(CEffectManager **)(*(long *)(param_2 + 0xb8) + 0x38))) {
    this_00 = (CEffect *)Ogre::NedAllocImpl::allocBytes(0x138,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 007f31f4 to 007f31f8 has its CatchHandler @ 007f325d */
    CEffect::CEffect(this_00,param_2);
    CEffect::setOwner(this_00,param_1,true);
    addNewEffect(this,this_00);
    if (*(CBaseUnit **)(this + 0x70) != (CBaseUnit *)0x0) {
      CBaseUnit::activateEffect(*(CBaseUnit **)(this + 0x70),this_00);
    }
    clearOutDescriptions(this);
    param_2 = this_00;
  }
  else {
    addNewEffect(this,param_2);
  }
  return param_2;
}



/* address=007f3270
   symbol=CEffectManager::cloneEffects */

/* CEffectManager::cloneEffects(CBaseUnit*, TArrayList<CEffect*>*) */

void __thiscall
CEffectManager::cloneEffects(CEffectManager *this,CBaseUnit *param_1,TArrayList *param_2)

{
  undefined8 *puVar1;
  uint uVar2;

  if (param_2 != (TArrayList *)0x0) {
    if (*(int *)(param_2 + 8) != 0) {
      uVar2 = 0;
      do {
        if (uVar2 < *(uint *)(param_2 + 0xc)) {
          puVar1 = (undefined8 *)((ulong)uVar2 * 8 + *(long *)param_2);
        }
        else {
          puVar1 = *(undefined8 **)param_2;
        }
        uVar2 = uVar2 + 1;
        cloneEffect(this,param_1,(CEffect *)*puVar1);
      } while (uVar2 < *(uint *)(param_2 + 8));
    }
    clearOutDescriptions(this);
    return;
  }
  return;
}



/* address=007f32f0
   symbol=CEffectManager::getEffectValue */

/* CEffectManager::getEffectValue(EEFFECT_TYPE, std::wstring const&) */

void __thiscall CEffectManager::getEffectValue(CEffectManager *this,int param_2,undefined8 *param_3)

{
  uint uVar1;
  uint uVar2;
  size_t __n;
  int iVar3;
  long *plVar4;
  uint uVar5;
  long lVar6;
  int iVar7;

  if (*(float *)(this + (long)param_2 * 4 + 0x80) != 0.0) {
    iVar7 = 0;
    do {
      uVar1 = *(uint *)(this + 0x30);
      if (uVar1 != 0) {
        uVar2 = *(uint *)(this + 0x34);
        lVar6 = 0;
        uVar5 = 0;
        do {
          while( true ) {
            if (uVar5 < uVar2) {
              iVar3 = *(int *)(*(long *)(lVar6 + *(long *)(this + 0x28)) + 0x1c);
            }
            else {
              iVar3 = *(int *)(**(long **)(this + 0x28) + 0x1c);
            }
            if (param_2 == iVar3) break;
LAB_007f334e:
            uVar5 = uVar5 + 1;
            lVar6 = lVar6 + 8;
            if (uVar1 <= uVar5) goto LAB_007f3494;
          }
          if (uVar5 < uVar2) {
            plVar4 = (long *)(lVar6 + *(long *)(this + 0x28));
          }
          else {
            plVar4 = *(long **)(this + 0x28);
          }
          __n = *(size_t *)(*(wchar_t **)(*plVar4 + 0x80) + -6);
          if ((__n != *(size_t *)((wchar_t *)*param_3 + -6)) ||
             (iVar3 = wmemcmp(*(wchar_t **)(*plVar4 + 0x80),(wchar_t *)*param_3,__n), iVar3 != 0))
          goto LAB_007f334e;
          uVar5 = uVar5 + 1;
          lVar6 = lVar6 + 8;
        } while (uVar5 < uVar1);
      }
LAB_007f3494:
      iVar7 = iVar7 + 1;
      this = this + 0x18;
    } while (iVar7 != 2);
  }
  return;
}



/* address=007f34f0
   symbol=CEffectManager::hasEffect */

/* CEffectManager::hasEffect(EEFFECT_TYPE, std::wstring const&) */

undefined8 __thiscall
CEffectManager::hasEffect(CEffectManager *this,int param_2,undefined8 *param_3)

{
  uint uVar1;
  uint uVar2;
  size_t __n;
  int iVar3;
  long *plVar4;
  uint uVar5;
  long lVar6;
  long lVar7;

  lVar7 = 0;
  do {
    uVar1 = *(uint *)(this + lVar7 + 0x30);
    if (uVar1 != 0) {
      uVar2 = *(uint *)(this + lVar7 + 0x34);
      lVar6 = 0;
      uVar5 = 0;
      do {
        if (uVar5 < uVar2) {
          iVar3 = *(int *)(*(long *)(lVar6 + *(long *)(this + lVar7 + 0x28)) + 0x1c);
        }
        else {
          iVar3 = *(int *)(**(long **)(this + lVar7 + 0x28) + 0x1c);
        }
        if (param_2 == iVar3) {
          if (uVar5 < uVar2) {
            plVar4 = (long *)(lVar6 + *(long *)(this + lVar7 + 0x28));
          }
          else {
            plVar4 = *(long **)(this + lVar7 + 0x28);
          }
          __n = *(size_t *)(*(wchar_t **)(*plVar4 + 0x80) + -6);
          if ((__n == *(size_t *)((wchar_t *)*param_3 + -6)) &&
             (iVar3 = wmemcmp(*(wchar_t **)(*plVar4 + 0x80),(wchar_t *)*param_3,__n), iVar3 == 0)) {
            return 1;
          }
        }
        uVar5 = uVar5 + 1;
        lVar6 = lVar6 + 8;
      } while (uVar5 < uVar1);
    }
    lVar7 = lVar7 + 0x18;
    if (lVar7 == 0x30) {
      return 0;
    }
  } while( true );
}



/* address=007f35e0
   symbol=CEffectManager::hasEffect */

/* CEffectManager::hasEffect(std::wstring const&) */

undefined8 __thiscall CEffectManager::hasEffect(CEffectManager *this,wstring_conflict *param_1)

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
  long lVar7;

  lVar7 = 0;
  do {
    uVar1 = *(uint *)(this + lVar7 + 0x30);
    if (uVar1 != 0) {
      uVar2 = *(uint *)(this + lVar7 + 0x34);
      lVar6 = 0;
      uVar5 = 0;
      __s2 = *(wchar_t **)param_1;
      __n = *(size_t *)(__s2 + -6);
      do {
        if (uVar5 < uVar2) {
          __s1 = *(wchar_t **)(*(long *)(lVar6 + *(long *)(this + lVar7 + 0x28)) + 0x80);
          sVar3 = *(size_t *)(__s1 + -6);
        }
        else {
          __s1 = *(wchar_t **)(**(long **)(this + lVar7 + 0x28) + 0x80);
          sVar3 = *(size_t *)(__s1 + -6);
        }
        if ((sVar3 == __n) && (iVar4 = wmemcmp(__s1,__s2,__n), iVar4 == 0)) {
          return 1;
        }
        uVar5 = uVar5 + 1;
        lVar6 = lVar6 + 8;
      } while (uVar5 < uVar1);
    }
    lVar7 = lVar7 + 0x18;
    if (lVar7 == 0x30) {
      return 0;
    }
  } while( true );
}



/* address=007f36c0
   symbol=CEffectManager::getEffect */

/* CEffectManager::getEffect(std::wstring const&, unsigned int) */

undefined8 __thiscall
CEffectManager::getEffect(CEffectManager *this,wstring_conflict *param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  wchar_t *__s2;
  size_t __n;
  wchar_t *__s1;
  size_t sVar3;
  int iVar4;
  undefined8 *puVar5;
  uint uVar6;
  ulong uVar7;
  long lVar8;
  CEffectManager *pCVar9;
  uint local_4c;

  local_4c = 0;
  pCVar9 = this;
  do {
    uVar1 = *(uint *)(pCVar9 + 0x30);
    if (uVar1 != 0) {
      uVar2 = *(uint *)(pCVar9 + 0x34);
      lVar8 = 0;
      uVar7 = 0;
      __s2 = *(wchar_t **)param_1;
      __n = *(size_t *)(__s2 + -6);
      do {
        while( true ) {
          uVar6 = (uint)uVar7;
          if (uVar6 < uVar2) {
            __s1 = *(wchar_t **)(*(long *)(lVar8 + *(long *)(pCVar9 + 0x28)) + 0x80);
            sVar3 = *(size_t *)(__s1 + -6);
          }
          else {
            __s1 = *(wchar_t **)(**(long **)(pCVar9 + 0x28) + 0x80);
            sVar3 = *(size_t *)(__s1 + -6);
          }
          if ((sVar3 == __n) && (iVar4 = wmemcmp(__s1,__s2,__n), iVar4 == 0)) break;
          uVar7 = (ulong)(uVar6 + 1);
          lVar8 = lVar8 + 8;
          if (uVar1 <= uVar6 + 1) goto LAB_007f3779;
        }
        if (param_2 == 0) {
          if (uVar6 < uVar2) {
            puVar5 = (undefined8 *)(uVar7 * 8 + *(long *)(this + (ulong)local_4c * 0x18 + 0x28));
          }
          else {
            puVar5 = *(undefined8 **)(this + (ulong)local_4c * 0x18 + 0x28);
          }
          return *puVar5;
        }
        uVar7 = (ulong)(uVar6 + 1);
        param_2 = param_2 - 1;
        lVar8 = lVar8 + 8;
      } while (uVar6 + 1 < uVar1);
    }
LAB_007f3779:
    local_4c = local_4c + 1;
    pCVar9 = pCVar9 + 0x18;
    if (local_4c == 2) {
      return 0;
    }
  } while( true );
}



/* address=007f37f0
   symbol=CEffectManager::deleteDeadEffects */

/* CEffectManager::deleteDeadEffects() */

void __thiscall CEffectManager::deleteDeadEffects(CEffectManager *this)

{
  float fVar1;
  uint uVar2;
  size_t sVar3;
  long lVar4;
  bool bVar5;
  int iVar6;
  long *plVar7;
  long *plVar8;
  CEffectManager *pCVar9;
  uint uVar10;
  long *plVar11;
  CEffectManager *pCVar12;
  uint uVar13;
  ulong uVar14;
  uint uVar15;

  bVar5 = false;
  pCVar9 = this;
  do {
    uVar14 = 0;
    if (*(int *)(pCVar9 + 0x30) != 0) {
      do {
        uVar15 = *(uint *)(pCVar9 + 0x34);
        uVar13 = (uint)uVar14;
        if (uVar13 < uVar15) {
          plVar11 = *(long **)(pCVar9 + 0x28);
          plVar8 = plVar11 + uVar14;
        }
        else {
          plVar8 = *(long **)(pCVar9 + 0x28);
          plVar11 = plVar8;
        }
        if (*(float *)(*plVar8 + 0x24) == DAT_00fc89b8) {
LAB_007f385d:
          plVar8 = plVar11;
          if (uVar13 < uVar15) {
            plVar8 = plVar11 + uVar14;
          }
          sVar3 = *(size_t *)(*(wchar_t **)(*plVar8 + 0x88) + -6);
          pCVar12 = this;
          if ((sVar3 != *(size_t *)(::EMPTY_WSTRING + -6)) ||
             (iVar6 = wmemcmp(*(wchar_t **)(*plVar8 + 0x88),::EMPTY_WSTRING,sVar3), iVar6 != 0)) {
            do {
              uVar10 = 0;
              if (*(int *)(pCVar12 + 0x30) != 0) {
                do {
                  while( true ) {
                    plVar8 = plVar11 + uVar14;
                    if (uVar15 <= uVar13) {
                      plVar8 = plVar11;
                    }
                    uVar2 = *(uint *)(pCVar12 + 0x34);
                    if (uVar10 < uVar2) {
                      plVar7 = (long *)((ulong)uVar10 * 8 + *(long *)(pCVar12 + 0x28));
                    }
                    else {
                      plVar7 = *(long **)(pCVar12 + 0x28);
                    }
                    sVar3 = *(size_t *)(*(wchar_t **)(*plVar7 + 0x80) + -6);
                    if ((sVar3 == *(size_t *)(*(wchar_t **)(*plVar8 + 0x88) + -6)) &&
                       (iVar6 = wmemcmp(*(wchar_t **)(*plVar7 + 0x80),*(wchar_t **)(*plVar8 + 0x88),
                                        sVar3), iVar6 == 0)) break;
                    uVar10 = uVar10 + 1;
                    if (*(uint *)(pCVar12 + 0x30) <= uVar10) goto LAB_007f396c;
                  }
                  if (uVar10 < uVar2) {
                    plVar8 = (long *)((ulong)uVar10 * 8 + *(long *)(pCVar12 + 0x28));
                  }
                  else {
                    plVar8 = *(long **)(pCVar12 + 0x28);
                  }
                  lVar4 = *plVar8;
                  fVar1 = *(float *)(lVar4 + 0x24);
                  if ((fVar1 != DAT_00fc89b8) && (fVar1 != DAT_00fc89bc)) {
                    *(float *)(lVar4 + 0x18) = fVar1;
                  }
                  *(undefined1 *)(lVar4 + 0x34) = 1;
                  uVar10 = uVar10 + 1;
                  uVar15 = *(uint *)(pCVar9 + 0x34);
                  plVar11 = *(long **)(pCVar9 + 0x28);
                } while (uVar10 < *(uint *)(pCVar12 + 0x30));
              }
LAB_007f396c:
              pCVar12 = pCVar12 + 0x18;
            } while (pCVar12 != this + 0x48);
          }
          plVar8 = plVar11;
          if (uVar13 < uVar15) {
            plVar8 = plVar11 + uVar14;
          }
          if (*(long *)(*plVar8 + 0xb8) == 0) {
            plVar8 = plVar11;
            if (uVar13 < uVar15) {
              plVar8 = plVar11 + uVar14;
            }
            if (*plVar8 != 0) {
              plVar8 = plVar11;
              if (uVar13 < uVar15) {
                plVar8 = plVar11 + uVar14;
              }
              if ((long *)*plVar8 != (long *)0x0) {
                (**(code **)(*(long *)*plVar8 + 8))();
                uVar15 = *(uint *)(pCVar9 + 0x34);
                plVar11 = *(long **)(pCVar9 + 0x28);
              }
              if (uVar13 < uVar15) {
                plVar11 = plVar11 + uVar14;
              }
              *plVar11 = 0;
            }
            uVar15 = *(uint *)(pCVar9 + 0x30);
            if (uVar13 < uVar15) {
              *(uint *)(pCVar9 + 0x30) = uVar15 - 1;
              *(undefined8 *)(*(long *)(pCVar9 + 0x28) + uVar14 * 8) =
                   *(undefined8 *)(*(long *)(pCVar9 + 0x28) + (ulong)(uVar15 - 1) * 8);
              uVar15 = *(uint *)(pCVar9 + 0x30);
            }
          }
          else {
            uVar15 = *(uint *)(pCVar9 + 0x30);
            if (uVar13 < uVar15) {
              *(uint *)(pCVar9 + 0x30) = uVar15 - 1;
              plVar11[uVar14] = plVar11[uVar15 - 1];
              uVar15 = *(uint *)(pCVar9 + 0x30);
            }
          }
          uVar13 = uVar13 - 1;
          bVar5 = true;
        }
        else {
          plVar8 = plVar11;
          if (uVar13 < uVar15) {
            plVar8 = plVar11 + uVar14;
          }
          lVar4 = *plVar8;
          fVar1 = *(float *)(lVar4 + 0x24);
          if ((((fVar1 != DAT_00fc89b8) && (fVar1 != DAT_00fc89bc)) &&
              (fVar1 <= *(float *)(lVar4 + 0x18))) || (*(char *)(lVar4 + 0x34) != '\0'))
          goto LAB_007f385d;
          uVar15 = *(uint *)(pCVar9 + 0x30);
        }
        uVar14 = (ulong)(uVar13 + 1);
      } while (uVar13 + 1 < uVar15);
    }
    pCVar9 = pCVar9 + 0x18;
    if (pCVar9 == this + 0x48) {
      if (bVar5) {
        clearOutDescriptions(this);
        return;
      }
      return;
    }
  } while( true );
}



/* address=007f3b50
   symbol=CEffectManager::removeNonSavedEffects */

/* CEffectManager::removeNonSavedEffects() */

void __thiscall CEffectManager::removeNonSavedEffects(CEffectManager *this)

{
  float fVar1;
  long lVar2;
  uint uVar3;
  long *plVar4;
  long lVar5;

  lVar5 = 0;
  do {
    uVar3 = 0;
    if (*(int *)(this + lVar5 + 0x30) != 0) {
      do {
        if (uVar3 < *(uint *)(this + lVar5 + 0x34)) {
          plVar4 = (long *)((ulong)uVar3 * 8 + *(long *)(this + lVar5 + 0x28));
        }
        else {
          plVar4 = *(long **)(this + lVar5 + 0x28);
        }
        if (*(char *)(*plVar4 + 0x33) == '\0') {
          if (uVar3 < *(uint *)(this + lVar5 + 0x34)) {
            plVar4 = (long *)((ulong)uVar3 * 8 + *(long *)(this + lVar5 + 0x28));
          }
          else {
            plVar4 = *(long **)(this + lVar5 + 0x28);
          }
          lVar2 = *plVar4;
          fVar1 = *(float *)(lVar2 + 0x24);
          if ((fVar1 != DAT_00fc89b8) && (fVar1 != DAT_00fc89bc)) {
            *(float *)(lVar2 + 0x18) = fVar1;
          }
          *(undefined1 *)(lVar2 + 0x34) = 1;
        }
        uVar3 = uVar3 + 1;
      } while (uVar3 < *(uint *)(this + lVar5 + 0x30));
    }
    lVar5 = lVar5 + 0x18;
  } while (lVar5 != 0x48);
  deleteDeadEffects(this);
  return;
}



/* address=007f4550
   symbol=CEffectManager::~CEffectManager */

/* WARNING: Removing unreachable block (ram,0x007f46dc) */
/* CEffectManager::~CEffectManager() */

void __thiscall CEffectManager::~CEffectManager(CEffectManager *this)

{
  int *piVar1;
  int iVar2;
  TSafePointer *pTVar3;
  allocator *paVar4;
  CEffectManager *pCVar5;

  pTVar3 = (TSafePointer *)(this + 0x70);
  *(undefined ***)this = &PTR__CEffectManager_00fc8b10;
                    /* try { // try from 007f456e to 007f4586 has its CatchHandler @ 007f4690 */
  clearEffects(this,false);
  if (*(CRunicCore **)(this + 0x70) != (CRunicCore *)0x0) {
    CRunicCore::removeSafePointer(*(CRunicCore **)(this + 0x70),pTVar3,*(uint *)(this + 0x78));
    *(undefined8 *)(this + 0x70) = 0;
  }
  pCVar5 = this + 0x2f8;
  do {
    pCVar5 = pCVar5 + -8;
    paVar4 = (allocator *)(*(long *)pCVar5 + -0x18);
    if (paVar4 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(*(long *)pCVar5 + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy(paVar4);
      }
    }
  } while (pCVar5 != this + 0x2e0);
  if (*(void **)(this + 0x2c8) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x2c8));
    *(undefined8 *)(this + 0x2c8) = 0;
  }
  if (*(CRunicCore **)(this + 0x70) != (CRunicCore *)0x0) {
                    /* try { // try from 007f45f9 to 007f45fd has its CatchHandler @ 007f46b4 */
    CRunicCore::removeSafePointer(*(CRunicCore **)(this + 0x70),pTVar3,*(uint *)(this + 0x78));
  }
  *(undefined8 *)(this + 0x70) = 0;
  *(undefined4 *)(this + 0x78) = 0xffffffff;
  do {
    pTVar3 = pTVar3 + -0x18;
    if (*(void **)pTVar3 != (void *)0x0) {
      operator_delete__(*(void **)pTVar3);
      *(undefined8 *)pTVar3 = 0;
    }
  } while (pTVar3 != (TSafePointer *)(this + 0x28));
  if (*(void **)(this + 0x10) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x10));
    *(undefined8 *)(this + 0x10) = 0;
  }
  CRunicCore::~CRunicCore((CRunicCore *)this);
  return;
}



/* address=007f4760
   symbol=CEffectManager::~CEffectManager */

/* CEffectManager::~CEffectManager() */

void __thiscall CEffectManager::~CEffectManager(CEffectManager *this)

{
  ~CEffectManager(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}



/* address=007f4810
   symbol=CEffectManager::getVisualDescription */

/* WARNING: Removing unreachable block (ram,0x007f545e) */
/* WARNING: Removing unreachable block (ram,0x007f546c) */
/* WARNING: Removing unreachable block (ram,0x007f584b) */
/* WARNING: Removing unreachable block (ram,0x007f54da) */
/* WARNING: Removing unreachable block (ram,0x007f5602) */
/* WARNING: Removing unreachable block (ram,0x007f55f4) */
/* WARNING: Removing unreachable block (ram,0x007f5610) */
/* WARNING: Removing unreachable block (ram,0x007f55e6) */
/* WARNING: Removing unreachable block (ram,0x007f56fc) */
/* WARNING: Removing unreachable block (ram,0x007f56a8) */
/* WARNING: Removing unreachable block (ram,0x007f57e0) */
/* WARNING: Removing unreachable block (ram,0x007f5774) */
/* WARNING: Removing unreachable block (ram,0x007f577f) */
/* WARNING: Removing unreachable block (ram,0x007f569d) */
/* CEffectManager::getVisualDescription(EEFFECT_ACTIVATION, unsigned int, bool, bool) */

CEffectManager * __thiscall
CEffectManager::getVisualDescription
          (CEffectManager *this,int param_2,undefined8 param_3,undefined8 param_4,char param_5)

{
  undefined **ppuVar1;
  int *piVar2;
  wstring_conflict *pwVar3;
  CRunicCore CVar4;
  size_t sVar5;
  ulong uVar6;
  undefined **ppuVar7;
  CRunicCore CVar8;
  char cVar9;
  int iVar10;
  int iVar11;
  long lVar12;
  ulong *puVar13;
  undefined8 *puVar14;
  long lVar15;
  uint uVar16;
  ulong uVar17;
  CRunicCore *pCVar18;
  CRunicCore *pCVar19;
  CRunicCore *pCVar20;
  uint uVar21;
  long lVar22;
  uint uVar23;
  uint uVar24;
  float fVar25;
  undefined **local_198 [2];
  float local_188;
  float local_184;
  float local_180;
  float local_17c;
  float local_178;
  float local_174;
  CRunicCore local_170;
  int local_16c;
  long local_168;
  undefined **local_158 [2];
  float local_148;
  float local_144;
  float local_140;
  float local_13c;
  float local_138;
  float local_134;
  CRunicCore local_130;
  int local_12c;
  long local_128;
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
  long local_58 [5];

  lVar12 = (long)param_2;
  sVar5 = *(size_t *)(*(wchar_t **)(this + (lVar12 + 0x5c) * 8) + -6);
  if ((sVar5 == *(size_t *)(::EMPTY_WSTRING + -6)) &&
     (iVar10 = wmemcmp(*(wchar_t **)(this + (lVar12 + 0x5c) * 8),::EMPTY_WSTRING,sVar5), iVar10 == 0
     )) {
    lVar22 = (lVar12 + 0x5c) * 8;
    if (*(int *)(this + lVar12 * 0x18 + 0x30) != 0) {
      uVar16 = 0;
      pCVar19 = (CRunicCore *)0x0;
      uVar21 = 0;
      uVar24 = 0;
      if (*(int *)(this + lVar12 * 0x18 + 0x34) != 0) goto LAB_007f4c2f;
LAB_007f48f8:
      puVar14 = *(undefined8 **)(this + lVar12 * 0x18 + 0x28);
      do {
                    /* try { // try from 007f4913 to 007f4917 has its CatchHandler @ 007f53f0 */
        CEffect::getVisualCalculatedValues((uint)local_158,SUB81(*puVar14,0));
        CVar8 = local_130;
        if (uVar21 != 0) {
          lVar22 = 0;
          uVar17 = 0;
          do {
            uVar23 = (uint)uVar17;
            pCVar20 = pCVar19 + lVar22;
            if (uVar24 <= uVar23) {
              pCVar20 = pCVar19;
            }
            CVar4 = pCVar20[0x28];
            if ((CVar4 == CVar8) && (iVar10 = *(int *)(pCVar20 + 0x2c), iVar10 == local_12c)) {
              uVar6 = *(ulong *)(pCVar20 + 0x30);
              if ((uVar6 != 0) && (local_128 != 0)) {
                if (*(int *)(uVar6 + 0x14) != *(int *)(local_128 + 0x14)) goto LAB_007f494a;
                if (iVar10 == 0x52) {
                  sVar5 = *(size_t *)(*(wchar_t **)(uVar6 + 0x80) + -6);
                  if ((sVar5 != *(size_t *)(*(wchar_t **)(local_128 + 0x80) + -6)) ||
                     (iVar11 = wmemcmp(*(wchar_t **)(uVar6 + 0x80),*(wchar_t **)(local_128 + 0x80),
                                       sVar5), iVar11 != 0)) goto LAB_007f494a;
                }
              }
              pCVar20 = pCVar19;
              if (uVar23 < uVar24) {
                pCVar20 = pCVar19 + uVar17 * 0x38;
              }
              if ((CVar4 != pCVar20[0x28]) || (*(int *)(pCVar20 + 0x2c) != iVar10))
              goto LAB_007f4be8;
              uVar17 = *(ulong *)(pCVar20 + 0x30);
              if ((uVar17 != 0) && (local_128 != 0)) {
                if (*(int *)(uVar17 + 0x14) != *(int *)(local_128 + 0x14)) goto LAB_007f4be8;
                if (iVar10 == 0x52) {
                  sVar5 = *(size_t *)(*(wchar_t **)(uVar17 + 0x80) + -6);
                  if ((sVar5 != *(size_t *)(*(wchar_t **)(local_128 + 0x80) + -6)) ||
                     (iVar10 = wmemcmp(*(wchar_t **)(uVar17 + 0x80),*(wchar_t **)(local_128 + 0x80),
                                       sVar5), iVar10 != 0)) goto LAB_007f4be8;
                }
              }
              fVar25 = local_148;
              if (local_148 <= *(float *)(pCVar20 + 0x10)) {
                fVar25 = *(float *)(pCVar20 + 0x10);
              }
              *(float *)(pCVar20 + 0x10) = fVar25;
              *(float *)(pCVar20 + 0x14) = *(float *)(pCVar20 + 0x14) + local_144;
              *(float *)(pCVar20 + 0x18) = *(float *)(pCVar20 + 0x18) + local_140;
              *(float *)(pCVar20 + 0x1c) = *(float *)(pCVar20 + 0x1c) + local_13c;
              *(float *)(pCVar20 + 0x20) = *(float *)(pCVar20 + 0x20) + local_138;
              *(float *)(pCVar20 + 0x24) = *(float *)(pCVar20 + 0x24) + local_134;
              goto LAB_007f4be8;
            }
LAB_007f494a:
            uVar17 = (ulong)(uVar23 + 1);
            lVar22 = lVar22 + 0x38;
          } while (uVar23 + 1 < uVar21);
        }
                    /* try { // try from 007f495b to 007f495f has its CatchHandler @ 007f58e7 */
        CRunicCore::CRunicCore((CRunicCore *)local_198);
        local_198[0] = &PTR__CEffectDisplayValues_00fc8970;
        local_16c = local_12c;
        local_168 = local_128;
        local_188 = local_148;
        local_170 = local_130;
        local_184 = local_144;
        local_180 = local_140;
        local_17c = local_13c;
        local_178 = local_138;
        local_174 = local_134;
        pCVar20 = pCVar19;
        uVar23 = uVar24;
        if (uVar24 <= uVar21) {
          if (pCVar19 == (CRunicCore *)0x0) {
                    /* try { // try from 007f4db3 to 007f4db7 has its CatchHandler @ 007f58e2 */
            puVar14 = (undefined8 *)Ogre::NedAllocImpl::allocBytes(0x238,(char *)0x0,0,(char *)0x0);
            lVar22 = 8;
            pCVar20 = (CRunicCore *)(puVar14 + 1);
            *puVar14 = 10;
            pCVar19 = pCVar20;
            while( true ) {
                    /* try { // try from 007f4de7 to 007f4deb has its CatchHandler @ 007f5856 */
              CRunicCore::CRunicCore(pCVar19);
              lVar22 = lVar22 + -1;
              *(undefined ***)pCVar19 = &PTR__CEffectDisplayValues_00fc8970;
              *(undefined4 *)(pCVar19 + 0x10) = 0;
              pCVar19[0x28] = (CRunicCore)0x0;
              *(undefined4 *)(pCVar19 + 0x2c) = 0;
              *(undefined4 *)(pCVar19 + 0x14) = 0;
              *(undefined4 *)(pCVar19 + 0x18) = 0;
              *(undefined4 *)(pCVar19 + 0x1c) = 0;
              *(undefined4 *)(pCVar19 + 0x20) = 0;
              *(undefined4 *)(pCVar19 + 0x24) = 0;
              if (lVar22 == -2) break;
              pCVar19 = pCVar19 + 0x38;
            }
            uVar23 = 10;
          }
          else {
            uVar23 = uVar24 + 10;
            uVar17 = (ulong)uVar23;
                    /* try { // try from 007f4a26 to 007f4a2a has its CatchHandler @ 007f58e2 */
            puVar13 = (ulong *)Ogre::NedAllocImpl::allocBytes
                                         (uVar17 * 0x38 + 8,(char *)0x0,0,(char *)0x0);
            *puVar13 = uVar17;
            lVar22 = uVar17 - 1;
            pCVar20 = (CRunicCore *)(puVar13 + 1);
            pCVar18 = pCVar20;
            if (lVar22 != -1) {
              while( true ) {
                    /* try { // try from 007f4a5f to 007f4a63 has its CatchHandler @ 007f5882 */
                CRunicCore::CRunicCore(pCVar18);
                lVar22 = lVar22 + -1;
                *(undefined ***)pCVar18 = &PTR__CEffectDisplayValues_00fc8970;
                *(undefined4 *)(pCVar18 + 0x10) = 0;
                pCVar18[0x28] = (CRunicCore)0x0;
                *(undefined4 *)(pCVar18 + 0x2c) = 0;
                *(undefined4 *)(pCVar18 + 0x14) = 0;
                *(undefined4 *)(pCVar18 + 0x18) = 0;
                *(undefined4 *)(pCVar18 + 0x1c) = 0;
                *(undefined4 *)(pCVar18 + 0x20) = 0;
                *(undefined4 *)(pCVar18 + 0x24) = 0;
                if (lVar22 == -1) break;
                pCVar18 = pCVar18 + 0x38;
              }
            }
            if (uVar24 != 0) {
              lVar22 = 0;
              do {
                lVar15 = lVar22 + 0x38;
                *(undefined4 *)(pCVar20 + lVar22 + 0x2c) = *(undefined4 *)(pCVar19 + lVar22 + 0x2c);
                *(undefined8 *)(pCVar20 + lVar22 + 0x30) = *(undefined8 *)(pCVar19 + lVar22 + 0x30);
                *(undefined4 *)(pCVar20 + lVar22 + 0x10) = *(undefined4 *)(pCVar19 + lVar22 + 0x10);
                pCVar20[lVar22 + 0x28] = pCVar19[lVar22 + 0x28];
                *(undefined4 *)(pCVar20 + lVar22 + 0x14) = *(undefined4 *)(pCVar19 + lVar22 + 0x14);
                *(undefined4 *)(pCVar20 + lVar22 + 0x18) = *(undefined4 *)(pCVar19 + lVar22 + 0x18);
                *(undefined4 *)(pCVar20 + lVar22 + 0x1c) = *(undefined4 *)(pCVar19 + lVar22 + 0x1c);
                *(undefined4 *)(pCVar20 + lVar22 + 0x20) = *(undefined4 *)(pCVar19 + lVar22 + 0x20);
                *(undefined4 *)(pCVar20 + lVar22 + 0x24) = *(undefined4 *)(pCVar19 + lVar22 + 0x24);
                lVar22 = lVar15;
              } while (lVar15 != ((ulong)(uVar24 - 1) + 1) * 0x38);
            }
            pCVar18 = pCVar19 + *(ulong *)(pCVar19 + -8) * 0x38;
            while (pCVar19 != pCVar18) {
              pCVar18 = pCVar18 + -0x38;
                    /* try { // try from 007f4b4a to 007f4b59 has its CatchHandler @ 007f58e2 */
              (*(code *)**(undefined8 **)pCVar18)(pCVar18);
            }
            Ogre::NedAllocImpl::deallocBytes(pCVar19 + -8);
          }
        }
        *(int *)(pCVar20 + (ulong)uVar21 * 0x38 + 0x2c) = local_16c;
        *(long *)(pCVar20 + (ulong)uVar21 * 0x38 + 0x30) = local_168;
        *(float *)(pCVar20 + (ulong)uVar21 * 0x38 + 0x10) = local_188;
        pCVar20[(ulong)uVar21 * 0x38 + 0x28] = local_170;
        *(float *)(pCVar20 + (ulong)uVar21 * 0x38 + 0x14) = local_184;
        *(float *)(pCVar20 + (ulong)uVar21 * 0x38 + 0x18) = local_180;
        *(float *)(pCVar20 + (ulong)uVar21 * 0x38 + 0x1c) = local_17c;
        *(float *)(pCVar20 + (ulong)uVar21 * 0x38 + 0x20) = local_178;
        *(float *)(pCVar20 + (ulong)uVar21 * 0x38 + 0x24) = local_174;
        local_198[0] = &PTR__CEffectDisplayValues_00fc8970;
                    /* try { // try from 007f4be3 to 007f4be7 has its CatchHandler @ 007f58e7 */
        CRunicCore::~CRunicCore((CRunicCore *)local_198);
        pCVar19 = pCVar20;
        uVar21 = uVar21 + 1;
        uVar24 = uVar23;
LAB_007f4be8:
        local_158[0] = &PTR__CEffectDisplayValues_00fc8970;
                    /* try { // try from 007f4bfc to 007f4c00 has its CatchHandler @ 007f53f0 */
        CRunicCore::~CRunicCore((CRunicCore *)local_158);
        uVar16 = uVar16 + 1;
        if (*(uint *)(this + lVar12 * 0x18 + 0x30) <= uVar16) {
          if (uVar21 != 0) {
            lVar22 = 0;
            uVar16 = 0;
            iVar10 = 0;
            pwVar3 = (wstring_conflict *)(this + lVar12 * 8 + 0x2e0);
            do {
                    /* try { // try from 007f4f3f to 007f4f43 has its CatchHandler @ 007f53f0 */
              std::wstring::wstring
                        ((wstring_conflict *)local_158,(wstring_conflict *)&::EMPTY_WSTRING);
              pCVar20 = pCVar19 + lVar22;
              if (uVar24 <= uVar16) {
                pCVar20 = pCVar19;
              }
              uVar17 = *(ulong *)(pCVar20 + 0x30);
              if (param_2 == 2) {
                CEffect::getDisplayStats((CEffectDisplayValues *)local_78);
                    /* try { // try from 007f5142 to 007f515b has its CatchHandler @ 007f563a */
                CStringTranslate::getSinglton();
                CStringTranslate::getTranslateString((wchar_t *)local_58);
                    /* try { // try from 007f516c to 007f5170 has its CatchHandler @ 007f5635 */
                std::wstring::wstring((wstring_conflict *)local_68,(wstring_conflict *)local_58);
                wcslen(L" ");
                    /* try { // try from 007f518b to 007f518f has its CatchHandler @ 007f5623 */
                std::wstring::append((wchar_t *)local_68,0xfd0b98);
                    /* try { // try from 007f51a8 to 007f51ac has its CatchHandler @ 007f561e */
                std::operator+((wstring_conflict *)local_88,(wstring_conflict *)local_68);
                    /* try { // try from 007f51bd to 007f51c1 has its CatchHandler @ 007f55aa */
                std::wstring::assign((wstring_conflict *)local_158);
                if ((allocator *)(local_88[0] + -0x18) !=
                    (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                  LOCK();
                  piVar2 = (int *)(local_88[0] + -8);
                  iVar11 = *piVar2;
                  *piVar2 = *piVar2 + -1;
                  UNLOCK();
                  if (iVar11 < 1) {
                    std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
                  }
                }
                if ((allocator *)(local_68[0] + -0x18) !=
                    (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                  LOCK();
                  piVar2 = (int *)(local_68[0] + -8);
                  iVar11 = *piVar2;
                  *piVar2 = *piVar2 + -1;
                  UNLOCK();
                  if (iVar11 < 1) {
                    std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
                  }
                }
                if ((allocator *)(local_58[0] + -0x18) !=
                    (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                  LOCK();
                  piVar2 = (int *)(local_58[0] + -8);
                  iVar11 = *piVar2;
                  *piVar2 = *piVar2 + -1;
                  UNLOCK();
                  if (iVar11 < 1) {
                    std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
                  }
                }
                if ((allocator *)(local_78[0] + -0x18) !=
                    (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                  LOCK();
                  piVar2 = (int *)(local_78[0] + -8);
                  iVar11 = *piVar2;
                  *piVar2 = *piVar2 + -1;
                  UNLOCK();
                  if (iVar11 < 1) {
                    std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
                  }
                }
              }
              else {
                    /* try { // try from 007f4f77 to 007f4f7b has its CatchHandler @ 007f5843 */
                CEffect::getDisplayStats((CEffectDisplayValues *)local_98);
                    /* try { // try from 007f4f8c to 007f4f90 has its CatchHandler @ 007f582e */
                std::wstring::assign((wstring_conflict *)local_158);
                if ((allocator *)(local_98[0] + -0x18) !=
                    (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                  LOCK();
                  piVar2 = (int *)(local_98[0] + -8);
                  iVar11 = *piVar2;
                  *piVar2 = *piVar2 + -1;
                  UNLOCK();
                  if (iVar11 < 1) {
                    std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
                  }
                }
              }
              ppuVar7 = local_158[0];
              if ((local_158[0][-3] != *(undefined **)(::EMPTY_WSTRING + -6)) ||
                 (iVar11 = wmemcmp((wchar_t *)local_158[0],::EMPTY_WSTRING,(size_t)local_158[0][-3])
                 , iVar11 != 0)) {
                    /* try { // try from 007f4feb to 007f5033 has its CatchHandler @ 007f5843 */
                    /* try { // try from 007f534c to 007f5350 has its CatchHandler @ 007f5843 */
                if (((param_5 != '\0') && (*(CAffix **)(uVar17 + 0xb8) != (CAffix *)0x0)) &&
                   (((cVar9 = CAffix::canBeAppliedToUnitType(*(CAffix **)(uVar17 + 0xb8),8),
                     cVar9 == '\0' ||
                     (cVar9 = CAffix::canBeAppliedToUnitType(*(CAffix **)(uVar17 + 0xb8),0xd),
                     cVar9 == '\0')) && (*(CAffix **)(uVar17 + 0xb8) != (CAffix *)0x0)))) {
                  cVar9 = CAffix::canBeAppliedToUnitType(*(CAffix **)(uVar17 + 0xb8),8);
                  if (cVar9 == '\0') {
                    /* try { // try from 007f5250 to 007f5269 has its CatchHandler @ 007f5843 */
                    CStringTranslate::getSinglton();
                    CStringTranslate::getTranslateString((wchar_t *)local_d8);
                    /* try { // try from 007f527d to 007f5281 has its CatchHandler @ 007f54f7 */
                    std::wstring::wstring((wstring_conflict *)local_e8,(wstring_conflict *)local_d8)
                    ;
                    wcslen(L":\n     ");
                    /* try { // try from 007f5297 to 007f529b has its CatchHandler @ 007f54ea */
                    std::wstring::append((wchar_t *)local_e8,0xfc8a88);
                    /* try { // try from 007f52af to 007f52b3 has its CatchHandler @ 007f54e5 */
                    std::operator+((wstring_conflict *)local_f8,(wstring_conflict *)local_e8);
                    /* try { // try from 007f52c4 to 007f52c8 has its CatchHandler @ 007f54a3 */
                    std::wstring::assign((wstring_conflict *)local_158);
                    if ((allocator *)(local_f8[0] + -0x18) !=
                        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                      LOCK();
                      piVar2 = (int *)(local_f8[0] + -8);
                      iVar11 = *piVar2;
                      *piVar2 = *piVar2 + -1;
                      UNLOCK();
                      if (iVar11 < 1) {
                        std::wstring::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
                      }
                    }
                    if ((allocator *)(local_e8[0] + -0x18) !=
                        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                      LOCK();
                      piVar2 = (int *)(local_e8[0] + -8);
                      iVar11 = *piVar2;
                      *piVar2 = *piVar2 + -1;
                      UNLOCK();
                      if (iVar11 < 1) {
                        std::wstring::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
                      }
                    }
                    if ((allocator *)(local_d8[0] + -0x18) !=
                        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                      LOCK();
                      piVar2 = (int *)(local_d8[0] + -8);
                      iVar11 = *piVar2;
                      *piVar2 = *piVar2 + -1;
                      UNLOCK();
                      if (iVar11 < 1) {
                        std::wstring::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
                      }
                    }
                  }
                  else {
                    CStringTranslate::getSinglton();
                    CStringTranslate::getTranslateString((wchar_t *)local_a8);
                    /* try { // try from 007f5047 to 007f504b has its CatchHandler @ 007f57fd */
                    std::wstring::wstring((wstring_conflict *)local_b8,(wstring_conflict *)local_a8)
                    ;
                    wcslen(L":\n     ");
                    /* try { // try from 007f5061 to 007f5065 has its CatchHandler @ 007f57f0 */
                    std::wstring::append((wchar_t *)local_b8,0xfc8a88);
                    /* try { // try from 007f5079 to 007f507d has its CatchHandler @ 007f57eb */
                    std::operator+((wstring_conflict *)local_c8,(wstring_conflict *)local_b8);
                    /* try { // try from 007f508e to 007f5092 has its CatchHandler @ 007f57b6 */
                    std::wstring::assign((wstring_conflict *)local_158);
                    if ((allocator *)(local_c8[0] + -0x18) !=
                        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                      LOCK();
                      piVar2 = (int *)(local_c8[0] + -8);
                      iVar11 = *piVar2;
                      *piVar2 = *piVar2 + -1;
                      UNLOCK();
                      if (iVar11 < 1) {
                        std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
                      }
                    }
                    if ((allocator *)(local_b8[0] + -0x18) !=
                        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                      LOCK();
                      piVar2 = (int *)(local_b8[0] + -8);
                      iVar11 = *piVar2;
                      *piVar2 = *piVar2 + -1;
                      UNLOCK();
                      if (iVar11 < 1) {
                        std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
                      }
                    }
                    if ((allocator *)(local_a8[0] + -0x18) !=
                        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                      LOCK();
                      piVar2 = (int *)(local_a8[0] + -8);
                      iVar11 = *piVar2;
                      *piVar2 = *piVar2 + -1;
                      UNLOCK();
                      if (iVar11 < 1) {
                        std::wstring::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
                      }
                    }
                  }
                }
                if (iVar10 == 0) {
                    /* try { // try from 007f50f9 to 007f5141 has its CatchHandler @ 007f5843 */
                  std::wstring::assign(pwVar3);
                }
                else {
                    /* try { // try from 007f4e88 to 007f4e8c has its CatchHandler @ 007f5843 */
                  std::wstring::wstring((wstring_conflict *)local_108,pwVar3);
                  wcslen(L"\n");
                    /* try { // try from 007f4ea2 to 007f4ea6 has its CatchHandler @ 007f570c */
                  std::wstring::append((wchar_t *)local_108,0xfd0b48);
                    /* try { // try from 007f4eba to 007f4ebe has its CatchHandler @ 007f5707 */
                  std::operator+((wstring_conflict *)local_118,(wstring_conflict *)local_108);
                    /* try { // try from 007f4ecc to 007f4ed0 has its CatchHandler @ 007f56df */
                  std::wstring::assign(pwVar3);
                  if ((allocator *)(local_118[0] + -0x18) !=
                      (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                    LOCK();
                    piVar2 = (int *)(local_118[0] + -8);
                    iVar11 = *piVar2;
                    *piVar2 = *piVar2 + -1;
                    UNLOCK();
                    if (iVar11 < 1) {
                      std::wstring::_Rep::_M_destroy((allocator *)(local_118[0] + -0x18));
                    }
                  }
                  if ((allocator *)(local_108[0] + -0x18) !=
                      (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                    LOCK();
                    piVar2 = (int *)(local_108[0] + -8);
                    iVar11 = *piVar2;
                    *piVar2 = *piVar2 + -1;
                    UNLOCK();
                    if (iVar11 < 1) {
                      std::wstring::_Rep::_M_destroy((allocator *)(local_108[0] + -0x18));
                    }
                  }
                }
                iVar10 = iVar10 + 1;
                ppuVar7 = local_158[0];
              }
              if ((allocator *)(ppuVar7 + -3) !=
                  (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                LOCK();
                ppuVar1 = ppuVar7 + -1;
                iVar11 = *(int *)ppuVar1;
                *(int *)ppuVar1 = *(int *)ppuVar1 + -1;
                UNLOCK();
                if (iVar11 < 1) {
                  std::wstring::_Rep::_M_destroy((allocator *)(ppuVar7 + -3));
                }
              }
              uVar16 = uVar16 + 1;
              lVar22 = lVar22 + 0x38;
            } while (uVar16 < uVar21);
          }
          if (pCVar19 == (CRunicCore *)0x0) {
            return this + lVar12 * 8 + 0x2e0;
          }
          pCVar20 = pCVar19 + *(ulong *)(pCVar19 + -8) * 0x38;
          while (pCVar20 != pCVar19) {
            pCVar20 = pCVar20 + -0x38;
                    /* try { // try from 007f53aa to 007f53b9 has its CatchHandler @ 007f5416 */
            (*(code *)**(undefined8 **)pCVar20)(pCVar20);
          }
          Ogre::NedAllocImpl::deallocBytes(pCVar19 + -8);
          return this + lVar12 * 8 + 0x2e0;
        }
        if (*(uint *)(this + lVar12 * 0x18 + 0x34) <= uVar16) goto LAB_007f48f8;
LAB_007f4c2f:
        puVar14 = (undefined8 *)((ulong)uVar16 * 8 + *(long *)(this + lVar12 * 0x18 + 0x28));
      } while( true );
    }
  }
  else {
    lVar22 = lVar12 * 8 + 0x2e0;
  }
  return this + lVar22;
}



/* address=007f58f0
   symbol=CEffectManager::createEffect */

/* WARNING: Removing unreachable block (ram,0x007f5b1b) */
/* WARNING: Removing unreachable block (ram,0x007f5ba5) */
/* WARNING: Removing unreachable block (ram,0x007f5bb0) */
/* CEffectManager::createEffect(CDataGroup*, bool) */

void __thiscall CEffectManager::createEffect(CEffectManager *this,CDataGroup *param_1,bool param_2)

{
  int *piVar1;
  wchar_t wVar2;
  uint uVar3;
  uint uVar4;
  size_t __n;
  size_t sVar5;
  CBaseUnit *pCVar6;
  int iVar7;
  wchar_t *pwVar8;
  wstring_conflict *pwVar9;
  allocator *paVar10;
  CEffect *this_00;
  uint uVar11;
  long lVar12;
  long lVar13;
  long local_58 [2];
  wchar_t *local_48;
  allocator local_39 [9];

  if (param_1 != (CDataGroup *)0x0) {
    pwVar8 = (wchar_t *)CDataGroup::GetGroupName(param_1);
    iVar7 = std::wstring::compare(pwVar8);
    if (iVar7 == 0) {
      if (param_2) {
                    /* try { // try from 007f595d to 007f5961 has its CatchHandler @ 007f5b10 */
        std::wstring::wstring((wstring_conflict *)local_58,L"NAME",local_39);
                    /* try { // try from 007f596f to 007f5980 has its CatchHandler @ 007f5b2e */
        pwVar9 = (wstring_conflict *)
                 CDataGroup::GetDataValue
                           (param_1,(wstring_conflict *)local_58,
                            (wstring_conflict *)&::EMPTY_WSTRING);
        STRINGS::StringUpper((STRINGS *)&local_48,pwVar9);
        if ((allocator *)(local_58[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_58[0] + -8);
          iVar7 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar7 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
          }
        }
        lVar13 = 0;
        paVar10 = (allocator *)(local_48 + -6);
        __n = *(size_t *)(local_48 + -6);
        if (__n != 0) {
          do {
            uVar3 = *(uint *)(this + lVar13 + 0x30);
            if (uVar3 != 0) {
              uVar4 = *(uint *)(this + lVar13 + 0x34);
              lVar12 = 0;
              uVar11 = 0;
              do {
                if (uVar11 < uVar4) {
                  pwVar8 = *(wchar_t **)(*(long *)(lVar12 + *(long *)(this + lVar13 + 0x28)) + 0x80)
                  ;
                  sVar5 = *(size_t *)(pwVar8 + -6);
                }
                else {
                  pwVar8 = *(wchar_t **)(**(long **)(this + lVar13 + 0x28) + 0x80);
                  sVar5 = *(size_t *)(pwVar8 + -6);
                }
                if ((__n == sVar5) && (iVar7 = wmemcmp(pwVar8,local_48,__n), iVar7 == 0)) {
                  if (paVar10 == (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                    return;
                  }
                  LOCK();
                  local_48 = local_48 + -2;
                  wVar2 = *local_48;
                  *local_48 = *local_48 + L'\xffffffff';
                  UNLOCK();
                  if (L'\0' < wVar2) {
                    return;
                  }
                  std::wstring::_Rep::_M_destroy(paVar10);
                  return;
                }
                uVar11 = uVar11 + 1;
                lVar12 = lVar12 + 8;
              } while (uVar11 < uVar3);
            }
            lVar13 = lVar13 + 0x18;
          } while (lVar13 != 0x48);
        }
        if (paVar10 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          local_48 = local_48 + -2;
          wVar2 = *local_48;
          *local_48 = *local_48 + L'\xffffffff';
          UNLOCK();
          if (wVar2 < L'\x01') {
            std::wstring::_Rep::_M_destroy(paVar10);
          }
        }
      }
      pCVar6 = *(CBaseUnit **)(this + 0x70);
      this_00 = (CEffect *)Ogre::NedAllocImpl::allocBytes(0x138,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 007f5ae2 to 007f5ae6 has its CatchHandler @ 007f5b64 */
      CEffect::CEffect(this_00,param_1,pCVar6);
      addNewEffect(this,this_00);
      if (*(CBaseUnit **)(this + 0x70) != (CBaseUnit *)0x0) {
        CBaseUnit::activateEffect(*(CBaseUnit **)(this + 0x70),this_00);
      }
      clearOutDescriptions(this);
    }
  }
  return;
}



/* address=007f5bd0
   symbol=CEffectManager::createEffects */

/* WARNING: Removing unreachable block (ram,0x007f5d44) */
/* CEffectManager::createEffects(CDataGroup*, bool) */

uint __thiscall CEffectManager::createEffects(CEffectManager *this,CDataGroup *param_1,bool param_2)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  wchar_t *pwVar4;
  long lVar5;
  uint uVar6;
  void *local_58;
  undefined8 local_50;
  undefined8 local_48;
  long local_38;
  allocator local_29;

  if (param_1 == (CDataGroup *)0x0) {
    return 0;
  }
  pwVar4 = (wchar_t *)CDataGroup::GetGroupName(param_1);
  iVar2 = std::wstring::compare(pwVar4);
  if (iVar2 == 0) {
    createEffect(this,param_1,param_2);
    return 1;
  }
  local_58 = (void *)0x0;
  local_50 = 0;
  local_48 = 0;
                    /* try { // try from 007f5c37 to 007f5c3b has its CatchHandler @ 007f5cf3 */
  std::wstring::wstring((wstring_conflict *)&local_38,L"EFFECT",&local_29);
                    /* try { // try from 007f5c45 to 007f5c49 has its CatchHandler @ 007f5d0c */
  uVar3 = CDataGroup::GetDataGroupsMatchingName
                    (param_1,(wstring_conflict *)&local_38,(vector *)&local_58);
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
  if (uVar3 != 0) {
    lVar5 = 0;
    uVar6 = 0;
    do {
                    /* try { // try from 007f5c7e to 007f5c96 has its CatchHandler @ 007f5d42 */
      createEffect(this,*(CDataGroup **)((long)local_58 + lVar5),param_2);
      uVar6 = uVar6 + 1;
      lVar5 = lVar5 + 8;
    } while (uVar6 < uVar3);
  }
  clearOutDescriptions(this);
  if (local_58 != (void *)0x0) {
    operator_delete(local_58);
  }
  return uVar3;
}



/* address=007f5d50
   symbol=CEffectManager::CEffectManager */

/* CEffectManager::CEffectManager(CBaseUnit*) */

void __thiscall CEffectManager::CEffectManager(CEffectManager *this,CBaseUnit *param_1)

{
  undefined4 uVar1;
  long lVar2;

  CRunicCore::CRunicCore((CRunicCore *)this);
  *(undefined ***)this = &PTR__CEffectManager_00fc8b10;
  *(undefined8 *)(this + 0x10) = 0;
  lVar2 = 0;
  *(undefined4 *)(this + 0x18) = 0;
  *(undefined4 *)(this + 0x1c) = 0;
  *(undefined4 *)(this + 0x20) = 1;
  do {
    *(undefined8 *)(this + lVar2 + 0x28) = 0;
    *(undefined4 *)(this + lVar2 + 0x30) = 0;
    *(undefined4 *)(this + lVar2 + 0x34) = 0;
    *(undefined4 *)(this + lVar2 + 0x38) = 10;
    lVar2 = lVar2 + 0x18;
  } while (lVar2 != 0x48);
  *(undefined8 *)(this + 0x70) = 0;
  *(undefined4 *)(this + 0x78) = 0xffffffff;
  if (param_1 != (CBaseUnit *)0x0) {
                    /* try { // try from 007f5df0 to 007f5df4 has its CatchHandler @ 007f5e8d */
    uVar1 = CRunicCore::addSafePointer((CRunicCore *)param_1,(TSafePointer *)(this + 0x70));
    *(undefined4 *)(this + 0x78) = uVar1;
    *(CBaseUnit **)(this + 0x70) = param_1;
  }
  *(undefined8 *)(this + 0x2c8) = 0;
  *(undefined4 *)(this + 0x2d0) = 0;
  *(undefined4 *)(this + 0x2d4) = 0;
  *(undefined4 *)(this + 0x2d8) = 1;
  *(undefined4 **)(this + 0x2e0) = &DAT_01424558;
  *(undefined4 **)(this + 0x2e8) = &DAT_01424558;
  *(undefined4 **)(this + 0x2f0) = &DAT_01424558;
  *(undefined4 *)(this + 0x38) = 1;
  *(undefined4 *)(this + 0x50) = 1;
  *(undefined4 *)(this + 0x68) = 1;
                    /* try { // try from 007f5e65 to 007f5e69 has its CatchHandler @ 007f5eb5 */
  calculateEffectValues(this);
  return;
}



/* export-summary functions=40 failures=0 */
