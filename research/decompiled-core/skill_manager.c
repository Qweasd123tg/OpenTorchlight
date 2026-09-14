/* Targeted Ghidra class export.
   namespace=CSkillManager
   Treat pseudocode as navigation evidence. */


/* address=00cca560
   symbol=CSkillManager::globallyDisableSkills */

/* CSkillManager::globallyDisableSkills(bool) */

void CSkillManager::globallyDisableSkills(bool param_1)

{
  m_gDisableSkillFromBeingCasted = param_1;
  return;
}



/* address=00cca570
   symbol=CSkillManager::getSkillLevel */

/* CSkillManager::getSkillLevel(CSkill*) */

undefined4 __thiscall CSkillManager::getSkillLevel(CSkillManager *this,CSkill *param_1)

{
  undefined4 uVar1;

  uVar1 = 0;
  if (param_1 != (CSkill *)0x0) {
    uVar1 = *(undefined4 *)(param_1 + 0xdc);
  }
  return uVar1;
}



/* address=00cca580
   symbol=CSkillManager::getSkillByGuid */

/* CSkillManager::getSkillByGuid(long long, int) */

undefined8 __thiscall
CSkillManager::getSkillByGuid(CSkillManager *this,longlong param_1,int param_2)

{
  uint uVar1;
  long lVar2;
  uint uVar3;
  long lVar4;
  long *plVar5;

  if (*(uint *)(this + 0x68) != 0) {
    uVar1 = *(uint *)(this + 0x6c);
    lVar4 = 0;
    uVar3 = 0;
    do {
      if (uVar3 < uVar1) {
        lVar2 = *(long *)(*(long *)(lVar4 + *(long *)(this + 0x60)) + 0x150);
      }
      else {
        lVar2 = *(long *)(**(long **)(this + 0x60) + 0x150);
      }
      if (param_1 == lVar2) {
        if (uVar3 < uVar1) {
          plVar5 = (long *)(lVar4 + *(long *)(this + 0x60));
        }
        else {
          plVar5 = *(long **)(this + 0x60);
        }
        if (param_2 == *(int *)(*plVar5 + 0xdc)) {
          if (uVar3 < uVar1) {
            return *(undefined8 *)((ulong)uVar3 * 8 + *(long *)(this + 0x60));
          }
          return **(undefined8 **)(this + 0x60);
        }
      }
      uVar3 = uVar3 + 1;
      lVar4 = lVar4 + 8;
    } while (uVar3 < *(uint *)(this + 0x68));
  }
  return 0;
}



/* address=00cca620
   symbol=CSkillManager::getSkillByGuid */

/* CSkillManager::getSkillByGuid(long long) */

undefined8 __thiscall CSkillManager::getSkillByGuid(CSkillManager *this,longlong param_1)

{
  long lVar1;
  uint uVar2;
  long lVar3;

  if (*(uint *)(this + 0x68) != 0) {
    lVar3 = 0;
    uVar2 = 0;
    do {
      if (uVar2 < *(uint *)(this + 0x6c)) {
        lVar1 = *(long *)(*(long *)(lVar3 + *(long *)(this + 0x60)) + 0x150);
      }
      else {
        lVar1 = *(long *)(**(long **)(this + 0x60) + 0x150);
      }
      if (param_1 == lVar1) {
        if (uVar2 < *(uint *)(this + 0x6c)) {
          return *(undefined8 *)((ulong)uVar2 * 8 + *(long *)(this + 0x60));
        }
        return **(undefined8 **)(this + 0x60);
      }
      uVar2 = uVar2 + 1;
      lVar3 = lVar3 + 8;
    } while (uVar2 < *(uint *)(this + 0x68));
  }
  return 0;
}



/* address=00cca6a0
   symbol=CSkillManager::knownSkills */

/* CSkillManager::knownSkills(ESKILL_ACTIVATION_TYPE) */

int __thiscall CSkillManager::knownSkills(CSkillManager *this,int param_2)

{
  int iVar1;
  long lVar2;
  uint uVar3;
  long *plVar4;

  if (param_2 != 0) {
    iVar1 = 0;
    if (*(uint *)(this + 0x68) != 0) {
      lVar2 = 0;
      uVar3 = 0;
      iVar1 = 0;
      do {
        if (uVar3 < *(uint *)(this + 0x6c)) {
          plVar4 = (long *)(lVar2 + *(long *)(this + 0x60));
        }
        else {
          plVar4 = *(long **)(this + 0x60);
        }
        uVar3 = uVar3 + 1;
        lVar2 = lVar2 + 8;
        iVar1 = iVar1 + (uint)(param_2 == *(int *)(*plVar4 + 0x60));
      } while (uVar3 < *(uint *)(this + 0x68));
    }
    return iVar1;
  }
  return *(int *)(this + 0x68);
}



/* address=00cca700
   symbol=CSkillManager::showWeaponTrailsOnCurrentSkill */

/* CSkillManager::showWeaponTrailsOnCurrentSkill(CEquipment*, CEquipment*) */

undefined8 CSkillManager::showWeaponTrailsOnCurrentSkill(CEquipment *param_1,CEquipment *param_2)

{
  return 0;
}



/* address=00cca710
   symbol=CSkillManager::hideWeaponTrailsOnCurrentSkill */

/* CSkillManager::hideWeaponTrailsOnCurrentSkill() */

void CSkillManager::hideWeaponTrailsOnCurrentSkill(void)

{
  return;
}



/* address=00cca720
   symbol=CSkillManager::getNumOfSkillsExecutableByActivationType */

/* CSkillManager::getNumOfSkillsExecutableByActivationType(ESKILL_ACTIVATION_TYPE) */

int __thiscall
CSkillManager::getNumOfSkillsExecutableByActivationType(CSkillManager *this,int param_2)

{
  uint uVar1;
  int iVar2;
  long lVar3;
  uint uVar4;
  long *plVar5;

  uVar1 = *(uint *)(this + 0x68);
  iVar2 = 0;
  if (uVar1 != 0) {
    lVar3 = 0;
    uVar4 = 0;
    do {
      while (uVar4 < *(uint *)(this + 0x6c)) {
        if (param_2 != *(int *)(*(long *)(lVar3 + *(long *)(this + 0x60)) + 0x60))
        goto LAB_00cca74d;
LAB_00cca76e:
        if (uVar4 < *(uint *)(this + 0x6c)) {
          plVar5 = (long *)(lVar3 + *(long *)(this + 0x60));
        }
        else {
          plVar5 = *(long **)(this + 0x60);
        }
        if (*(float *)(*plVar5 + 0xfc) <= 0.0) {
          iVar2 = iVar2 + 1;
        }
        uVar4 = uVar4 + 1;
        lVar3 = lVar3 + 8;
        if (uVar1 <= uVar4) {
          return iVar2;
        }
      }
      if (param_2 == *(int *)(**(long **)(this + 0x60) + 0x60)) goto LAB_00cca76e;
LAB_00cca74d:
      uVar4 = uVar4 + 1;
      lVar3 = lVar3 + 8;
    } while (uVar4 < uVar1);
  }
  return iVar2;
}



/* address=00cca7b0
   symbol=CSkillManager::getAnySkillsCoolingByActivationType */

/* CSkillManager::getAnySkillsCoolingByActivationType(ESKILL_ACTIVATION_TYPE) */

undefined8 __thiscall
CSkillManager::getAnySkillsCoolingByActivationType(CSkillManager *this,int param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  long *plVar4;
  long lVar5;

  if (*(uint *)(this + 0x68) != 0) {
    lVar5 = 0;
    uVar2 = 0;
    do {
      if (uVar2 < *(uint *)(this + 0x6c)) {
        iVar1 = *(int *)(*(long *)(lVar5 + *(long *)(this + 0x60)) + 0x60);
      }
      else {
        iVar1 = *(int *)(**(long **)(this + 0x60) + 0x60);
      }
      if (param_2 == iVar1) {
        if (uVar2 < *(uint *)(this + 0x6c)) {
          plVar4 = (long *)(lVar5 + *(long *)(this + 0x60));
        }
        else {
          plVar4 = *(long **)(this + 0x60);
        }
        if (0.0 < *(float *)(*plVar4 + 0xfc)) {
          return 1;
        }
      }
      uVar2 = uVar2 + 1;
      lVar5 = lVar5 + 8;
    } while (uVar2 < *(uint *)(this + 0x68));
  }
  uVar2 = *(uint *)(this + 0x50);
  if (uVar2 != 0) {
    lVar5 = 0;
    uVar3 = 0;
    do {
      while (uVar3 < *(uint *)(this + 0x54)) {
        if (param_2 == *(int *)(*(long *)(lVar5 + *(long *)(this + 0x48)) + 0x60))
        goto LAB_00cca87c;
LAB_00cca85c:
        uVar3 = uVar3 + 1;
        lVar5 = lVar5 + 8;
        if (uVar2 <= uVar3) {
          return 0;
        }
      }
      if (param_2 != *(int *)(**(long **)(this + 0x48) + 0x60)) goto LAB_00cca85c;
LAB_00cca87c:
      if (uVar3 < *(uint *)(this + 0x54)) {
        plVar4 = (long *)(lVar5 + *(long *)(this + 0x48));
      }
      else {
        plVar4 = *(long **)(this + 0x48);
      }
      if (0.0 < *(float *)(*plVar4 + 0xfc)) {
        return 1;
      }
      uVar3 = uVar3 + 1;
      lVar5 = lVar5 + 8;
    } while (uVar3 < uVar2);
  }
  return 0;
}



/* address=00cca8c0
   symbol=CSkillManager::getSkillIsCooling */

/* CSkillManager::getSkillIsCooling(CSkill*) */

undefined8 __thiscall CSkillManager::getSkillIsCooling(CSkillManager *this,CSkill *param_1)

{
  long lVar1;
  uint uVar2;
  long *plVar3;
  long lVar4;

  if (*(uint *)(this + 0x68) != 0) {
    lVar4 = 0;
    uVar2 = 0;
    do {
      if (uVar2 < *(uint *)(this + 0x6c)) {
        lVar1 = *(long *)(*(long *)(lVar4 + *(long *)(this + 0x60)) + 0x28);
      }
      else {
        lVar1 = *(long *)(**(long **)(this + 0x60) + 0x28);
      }
      if (lVar1 == *(long *)(param_1 + 0x28)) {
        if (uVar2 < *(uint *)(this + 0x6c)) {
          plVar3 = (long *)(lVar4 + *(long *)(this + 0x60));
        }
        else {
          plVar3 = *(long **)(this + 0x60);
        }
        if (0.0 < *(float *)(*plVar3 + 0xfc)) {
          return 1;
        }
      }
      uVar2 = uVar2 + 1;
      lVar4 = lVar4 + 8;
    } while (uVar2 < *(uint *)(this + 0x68));
  }
  if (*(uint *)(this + 0x50) != 0) {
    lVar4 = 0;
    uVar2 = 0;
    do {
      if (uVar2 < *(uint *)(this + 0x54)) {
        lVar1 = *(long *)(*(long *)(lVar4 + *(long *)(this + 0x48)) + 0x28);
      }
      else {
        lVar1 = *(long *)(**(long **)(this + 0x48) + 0x28);
      }
      if (lVar1 == *(long *)(param_1 + 0x28)) {
        if (uVar2 < *(uint *)(this + 0x54)) {
          plVar3 = (long *)(lVar4 + *(long *)(this + 0x48));
        }
        else {
          plVar3 = *(long **)(this + 0x48);
        }
        if (0.0 < *(float *)(*plVar3 + 0xfc)) {
          return 1;
        }
      }
      uVar2 = uVar2 + 1;
      lVar4 = lVar4 + 8;
    } while (uVar2 < *(uint *)(this + 0x50));
  }
  return 0;
}



/* address=00cca9d0
   symbol=CSkillManager::getSkillCoolingTime */

/* CSkillManager::getSkillCoolingTime(CSkill*) */

void __thiscall CSkillManager::getSkillCoolingTime(CSkillManager *this,CSkill *param_1)

{
  uint uVar1;
  long lVar2;
  uint uVar3;
  uint uVar4;
  long *plVar5;
  long lVar6;
  float fVar7;

  fVar7 = 0.0;
  if (*(uint *)(this + 0x68) != 0) {
    uVar1 = *(uint *)(this + 0x6c);
    lVar6 = 0;
    uVar3 = 0;
    fVar7 = 0.0;
    while( true ) {
      if (uVar3 < uVar1) {
        lVar2 = *(long *)(*(long *)(lVar6 + *(long *)(this + 0x60)) + 0x28);
      }
      else {
        lVar2 = *(long *)(**(long **)(this + 0x60) + 0x28);
      }
      if (lVar2 == *(long *)(param_1 + 0x28)) {
        if (uVar3 < uVar1) {
          plVar5 = (long *)(lVar6 + *(long *)(this + 0x60));
        }
        else {
          plVar5 = *(long **)(this + 0x60);
        }
        if (0.0 < *(float *)(*plVar5 + 0xfc)) {
          if (uVar3 < uVar1) {
            plVar5 = (long *)(lVar6 + *(long *)(this + 0x60));
          }
          else {
            plVar5 = *(long **)(this + 0x60);
          }
          if (fVar7 <= *(float *)(*plVar5 + 0xfc)) {
            fVar7 = *(float *)(*plVar5 + 0xfc);
          }
        }
      }
      if (*(uint *)(this + 0x68) <= uVar3 + 1) break;
      uVar3 = uVar3 + 1;
      lVar6 = lVar6 + 8;
    }
  }
  uVar1 = *(uint *)(this + 0x50);
  if (uVar1 != 0) {
    uVar3 = *(uint *)(this + 0x54);
    lVar6 = 0;
    uVar4 = 0;
    do {
      while( true ) {
        if (uVar4 < uVar3) {
          lVar2 = *(long *)(*(long *)(lVar6 + *(long *)(this + 0x48)) + 0x28);
        }
        else {
          lVar2 = *(long *)(**(long **)(this + 0x48) + 0x28);
        }
        if (lVar2 == *(long *)(param_1 + 0x28)) break;
LAB_00ccaaad:
        uVar4 = uVar4 + 1;
        lVar6 = lVar6 + 8;
        if (uVar1 <= uVar4) {
          return;
        }
      }
      if (uVar4 < uVar3) {
        plVar5 = (long *)(lVar6 + *(long *)(this + 0x48));
      }
      else {
        plVar5 = *(long **)(this + 0x48);
      }
      if (*(float *)(*plVar5 + 0xfc) <= 0.0) goto LAB_00ccaaad;
      if (uVar4 < uVar3) {
        plVar5 = (long *)(lVar6 + *(long *)(this + 0x48));
      }
      else {
        plVar5 = *(long **)(this + 0x48);
      }
      uVar4 = uVar4 + 1;
      lVar6 = lVar6 + 8;
      if (fVar7 <= *(float *)(*plVar5 + 0xfc)) {
        fVar7 = *(float *)(*plVar5 + 0xfc);
      }
    } while (uVar4 < uVar1);
  }
  return;
}



/* address=00ccab50
   symbol=CSkillManager::getSkillPoints */

/* CSkillManager::getSkillPoints() */

int __thiscall CSkillManager::getSkillPoints(CSkillManager *this)

{
  uint uVar1;
  int iVar2;
  long *plVar3;
  uint uVar4;
  long lVar5;

  iVar2 = 0;
  if (*(uint *)(this + 0x68) != 0) {
    uVar1 = *(uint *)(this + 0x6c);
    lVar5 = 0;
    uVar4 = 0;
    do {
      if (uVar4 < uVar1) {
        plVar3 = (long *)(lVar5 + *(long *)(this + 0x60));
      }
      else {
        plVar3 = *(long **)(this + 0x60);
      }
      if ((*(byte *)(*plVar3 + 0x6d) & (*(byte *)(*plVar3 + 0x6b) ^ 1)) != 0) {
        if (uVar4 < uVar1) {
          plVar3 = (long *)(lVar5 + *(long *)(this + 0x60));
        }
        else {
          plVar3 = *(long **)(this + 0x60);
        }
        if (*(int *)(*plVar3 + 0x5c) == 0) {
          if (uVar4 < uVar1) {
            plVar3 = (long *)(lVar5 + *(long *)(this + 0x60));
          }
          else {
            plVar3 = *(long **)(this + 0x60);
          }
          iVar2 = iVar2 + *(int *)(*plVar3 + 0xdc);
        }
      }
      uVar4 = uVar4 + 1;
      lVar5 = lVar5 + 8;
    } while (uVar4 < *(uint *)(this + 0x68));
  }
  return iVar2;
}



/* address=00ccac00
   symbol=CSkillManager::getSkillCanBeExecuted */

/* CSkillManager::getSkillCanBeExecuted(CSkill*, CBaseUnit*, ESKILL_ACTIVATION_TYPE, Ogre::Vector3
   const&, CBaseUnit*, bool) */

undefined8 __thiscall
CSkillManager::getSkillCanBeExecuted
          (CSkillManager *this,CSkill *param_1,undefined8 param_2,undefined4 param_4,
          undefined8 param_5,undefined8 param_6,undefined1 param_7)

{
  char cVar1;
  undefined8 uVar2;

  if (param_1 != (CSkill *)0x0) {
    cVar1 = getSkillIsCooling(this,param_1);
    if (cVar1 == '\0') {
      uVar2 = CSkill::requirementsMet(param_1,param_2,param_4,param_5,param_6,param_7);
      return uVar2;
    }
  }
  return 0;
}



/* address=00ccacb0
   symbol=CSkillManager::triggerSkillEvent */

/* CSkillManager::triggerSkillEvent(ESKILL_EVENT_TYPE, Ogre::Vector3 const&, Ogre::Quaternion
   const&, CBaseUnit*) */

void __thiscall
CSkillManager::triggerSkillEvent
          (CSkillManager *this,undefined4 param_2,undefined8 param_3,undefined8 param_4,
          undefined8 param_5)

{
  long lVar1;
  uint uVar2;
  long *plVar3;
  undefined8 *puVar4;
  uint uVar5;
  undefined4 *puVar6;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;

  if (*(int *)(this + 0x50) != 0) {
    uVar5 = 0;
    do {
      if (uVar5 < *(uint *)(this + 0x54)) {
        uVar2 = CSkill::getTargetType(*(CSkill **)((ulong)uVar5 * 8 + *(long *)(this + 0x48)));
        if (6 < uVar2) goto LAB_00ccad66;
LAB_00ccacf1:
        if ((1L << ((byte)uVar2 & 0x3f) & 0x62U) == 0) goto LAB_00ccad66;
        if (uVar5 < *(uint *)(this + 0x54)) {
          plVar3 = (long *)((ulong)uVar5 * 8 + *(long *)(this + 0x48));
        }
        else {
          plVar3 = *(long **)(this + 0x48);
        }
        lVar1 = *plVar3;
        local_44 = *(undefined4 *)(lVar1 + 0x54);
        local_48 = *(undefined4 *)(lVar1 + 0x50);
        local_40 = *(undefined4 *)(lVar1 + 0x58);
        if (uVar5 < *(uint *)(this + 0x54)) {
          puVar4 = (undefined8 *)((ulong)uVar5 * 8 + *(long *)(this + 0x48));
          puVar6 = &local_48;
        }
        else {
          puVar4 = *(undefined8 **)(this + 0x48);
          puVar6 = &local_48;
        }
      }
      else {
        uVar2 = CSkill::getTargetType((CSkill *)**(undefined8 **)(this + 0x48));
        if (uVar2 < 7) goto LAB_00ccacf1;
LAB_00ccad66:
        if (uVar5 < *(uint *)(this + 0x54)) {
          puVar4 = (undefined8 *)((ulong)uVar5 * 8 + *(long *)(this + 0x48));
        }
        else {
          puVar4 = *(undefined8 **)(this + 0x48);
        }
        puVar6 = (undefined4 *)(undefined1 *)0x0;
      }
      uVar5 = uVar5 + 1;
      CSkill::triggerEvent((CSkill *)*puVar4,param_2,param_3,param_4,param_5,puVar6);
    } while (uVar5 < *(uint *)(this + 0x50));
  }
  return;
}



/* address=00ccadc0
   symbol=CSkillManager::stopAllSkills */

/* CSkillManager::stopAllSkills(bool, bool, bool) */

void __thiscall
CSkillManager::stopAllSkills(CSkillManager *this,bool param_1,bool param_2,bool param_3)

{
  char cVar1;
  uint uVar2;
  long *plVar3;
  undefined8 *puVar4;
  uint uVar5;

  if (*(int *)(this + 0x50) != 0) {
    uVar5 = 0;
    do {
      if (param_3) {
        uVar2 = *(uint *)(this + 0x54);
        if (param_1) goto LAB_00ccae02;
LAB_00ccae48:
        if (param_2) {
          if (uVar5 < uVar2) {
            puVar4 = (undefined8 *)((ulong)uVar5 * 8 + *(long *)(this + 0x48));
          }
          else {
            puVar4 = *(undefined8 **)(this + 0x48);
          }
          cVar1 = CSkill::hasEvent((CSkill *)*puVar4,9);
          if (cVar1 == '\0') {
            uVar2 = *(uint *)(this + 0x54);
            if (uVar5 < uVar2) {
              plVar3 = (long *)((ulong)uVar5 * 8 + *(long *)(this + 0x48));
            }
            else {
              plVar3 = *(long **)(this + 0x48);
            }
            if (*(char *)(*plVar3 + 0x67) == '\0') goto LAB_00ccae4f;
          }
        }
        else {
LAB_00ccae4f:
          if (uVar5 < uVar2) {
            puVar4 = (undefined8 *)((ulong)uVar5 * 8 + *(long *)(this + 0x48));
          }
          else {
            puVar4 = *(undefined8 **)(this + 0x48);
          }
          CSkill::attemptToStopSkill((CSkill *)*puVar4);
        }
      }
      else {
        uVar2 = *(uint *)(this + 0x54);
        if (uVar5 < uVar2) {
          plVar3 = (long *)((ulong)uVar5 * 8 + *(long *)(this + 0x48));
        }
        else {
          plVar3 = *(long **)(this + 0x48);
        }
        if (*(int *)(*plVar3 + 0x60) == 4) goto LAB_00ccae23;
        if (!param_1) goto LAB_00ccae48;
LAB_00ccae02:
        if (param_2) {
          if (uVar5 < uVar2) {
            puVar4 = (undefined8 *)((ulong)uVar5 * 8 + *(long *)(this + 0x48));
          }
          else {
            puVar4 = *(undefined8 **)(this + 0x48);
          }
          cVar1 = CSkill::hasEvent((CSkill *)*puVar4,9);
          if (cVar1 == '\0') {
            if (uVar5 < *(uint *)(this + 0x54)) {
              plVar3 = (long *)((ulong)uVar5 * 8 + *(long *)(this + 0x48));
            }
            else {
              plVar3 = *(long **)(this + 0x48);
            }
            if (*(char *)(*plVar3 + 0x67) == '\0') goto LAB_00ccae1b;
          }
        }
        else {
LAB_00ccae1b:
          CSkill::stopSkill();
        }
      }
LAB_00ccae23:
      uVar5 = uVar5 + 1;
    } while (uVar5 < *(uint *)(this + 0x50));
  }
  return;
}



/* address=00cd0d90
   symbol=CSkillManager::getSkillIsUpdatingByName */

/* CSkillManager::getSkillIsUpdatingByName(std::wstring const&) */

undefined8 __thiscall
CSkillManager::getSkillIsUpdatingByName(CSkillManager *this,wstring_conflict *param_1)

{
  size_t __n;
  int iVar1;
  undefined8 *puVar2;
  uint uVar3;

  if (*(int *)(this + 0x50) != 0) {
    uVar3 = 0;
    do {
      if (uVar3 < *(uint *)(this + 0x54)) {
        puVar2 = (undefined8 *)((ulong)uVar3 * 8 + *(long *)(this + 0x48));
      }
      else {
        puVar2 = *(undefined8 **)(this + 0x48);
      }
      puVar2 = (undefined8 *)CSkill::getName((CSkill *)*puVar2);
      __n = *(size_t *)((wchar_t *)*puVar2 + -6);
      if ((__n == *(size_t *)(*(wchar_t **)param_1 + -6)) &&
         (iVar1 = wmemcmp((wchar_t *)*puVar2,*(wchar_t **)param_1,__n), iVar1 == 0)) {
        return 1;
      }
      uVar3 = uVar3 + 1;
    } while (uVar3 < *(uint *)(this + 0x50));
  }
  return 0;
}



/* address=00cd1060
   symbol=CSkillManager::clearAllUnitReferences */

/* CSkillManager::clearAllUnitReferences() */

void __thiscall CSkillManager::clearAllUnitReferences(CSkillManager *this)

{
  long lVar1;
  _Rb_tree_node_base *p_Var2;
  long *plVar3;
  uint uVar4;
  ulong uVar5;

  for (p_Var2 = *(_Rb_tree_node_base **)(this + 0x30); p_Var2 != (_Rb_tree_node_base *)(this + 0x20)
      ; p_Var2 = (_Rb_tree_node_base *)std::_Rb_tree_increment(p_Var2)) {
    lVar1 = *(long *)**(undefined8 **)(p_Var2 + 0x28);
    if (*(CRunicCore **)(lVar1 + 0x30) != (CRunicCore *)0x0) {
      CRunicCore::removeSafePointer
                (*(CRunicCore **)(lVar1 + 0x30),(TSafePointer *)(lVar1 + 0x30),
                 *(uint *)(lVar1 + 0x38));
      *(undefined8 *)(lVar1 + 0x30) = 0;
    }
  }
  if (*(int *)(this + 0x50) != 0) {
    uVar5 = 0;
    do {
      if ((uint)uVar5 < *(uint *)(this + 0x54)) {
        plVar3 = (long *)(uVar5 * 8 + *(long *)(this + 0x48));
      }
      else {
        plVar3 = *(long **)(this + 0x48);
      }
      lVar1 = *plVar3;
      if (*(CRunicCore **)(lVar1 + 0x40) != (CRunicCore *)0x0) {
        CRunicCore::removeSafePointer
                  (*(CRunicCore **)(lVar1 + 0x40),(TSafePointer *)(lVar1 + 0x40),
                   *(uint *)(lVar1 + 0x48));
        *(undefined8 *)(lVar1 + 0x40) = 0;
      }
      if (*(CRunicCore **)(lVar1 + 0x30) != (CRunicCore *)0x0) {
        CRunicCore::removeSafePointer
                  (*(CRunicCore **)(lVar1 + 0x30),(TSafePointer *)(lVar1 + 0x30),
                   *(uint *)(lVar1 + 0x38));
        *(undefined8 *)(lVar1 + 0x30) = 0;
      }
      uVar4 = (uint)uVar5 + 1;
      uVar5 = (ulong)uVar4;
    } while (uVar4 < *(uint *)(this + 0x50));
  }
  if (*(int *)(this + 0x68) != 0) {
    uVar4 = 0;
    do {
      if (uVar4 < *(uint *)(this + 0x6c)) {
        plVar3 = (long *)((ulong)uVar4 * 8 + *(long *)(this + 0x60));
      }
      else {
        plVar3 = *(long **)(this + 0x60);
      }
      lVar1 = *plVar3;
      if (*(CRunicCore **)(lVar1 + 0x40) != (CRunicCore *)0x0) {
        CRunicCore::removeSafePointer
                  (*(CRunicCore **)(lVar1 + 0x40),(TSafePointer *)(lVar1 + 0x40),
                   *(uint *)(lVar1 + 0x48));
        *(undefined8 *)(lVar1 + 0x40) = 0;
      }
      if (*(CRunicCore **)(lVar1 + 0x30) != (CRunicCore *)0x0) {
        CRunicCore::removeSafePointer
                  (*(CRunicCore **)(lVar1 + 0x30),(TSafePointer *)(lVar1 + 0x30),
                   *(uint *)(lVar1 + 0x38));
        *(undefined8 *)(lVar1 + 0x30) = 0;
      }
      uVar4 = uVar4 + 1;
    } while (uVar4 < *(uint *)(this + 0x68));
  }
  return;
}



/* address=00cd11b0
   symbol=CSkillManager::notifyOfDeletion */

/* CSkillManager::notifyOfDeletion(CCharacter*) */

void __thiscall CSkillManager::notifyOfDeletion(CSkillManager *this,CCharacter *param_1)

{
  long lVar1;
  CSkillManager *pCVar2;
  CCharacter *pCVar3;
  uint uVar4;
  CSkill *pCVar5;

  for (pCVar2 = *(CSkillManager **)(this + 0x30); pCVar2 != this + 0x20;
      pCVar2 = (CSkillManager *)std::_Rb_tree_increment((_Rb_tree_node_base *)pCVar2)) {
    while (pCVar3 = (CCharacter *)
                    CSkill::getOwnerCharacter(*(CSkill **)**(undefined8 **)(pCVar2 + 0x28)),
          pCVar3 == param_1) {
      lVar1 = *(long *)**(undefined8 **)(pCVar2 + 0x28);
      if (*(CRunicCore **)(lVar1 + 0x30) == (CRunicCore *)0x0) break;
      CRunicCore::removeSafePointer
                (*(CRunicCore **)(lVar1 + 0x30),(TSafePointer *)(lVar1 + 0x30),
                 *(uint *)(lVar1 + 0x38));
      *(undefined8 *)(lVar1 + 0x30) = 0;
      pCVar2 = (CSkillManager *)std::_Rb_tree_increment((_Rb_tree_node_base *)pCVar2);
      if (pCVar2 == this + 0x20) goto LAB_00cd1230;
    }
  }
LAB_00cd1230:
  if (*(int *)(this + 0x50) != 0) {
    uVar4 = 0;
LAB_00cd126c:
    do {
      if (uVar4 < *(uint *)(this + 0x54)) {
        pCVar5 = *(CSkill **)((ulong)uVar4 * 8 + *(long *)(this + 0x48));
        if (*(CCharacter **)(pCVar5 + 0x40) != param_1) goto LAB_00cd1255;
LAB_00cd1286:
        if (param_1 == (CCharacter *)0x0) goto LAB_00cd1255;
        CRunicCore::removeSafePointer
                  ((CRunicCore *)param_1,(TSafePointer *)(pCVar5 + 0x40),*(uint *)(pCVar5 + 0x48));
        *(undefined8 *)(pCVar5 + 0x40) = 0;
        pCVar3 = (CCharacter *)CSkill::getOwnerCharacter(pCVar5);
      }
      else {
        pCVar5 = (CSkill *)**(long **)(this + 0x48);
        if (*(CCharacter **)(pCVar5 + 0x40) == param_1) goto LAB_00cd1286;
LAB_00cd1255:
        pCVar3 = (CCharacter *)CSkill::getOwnerCharacter(pCVar5);
      }
      if ((param_1 != pCVar3) || (*(CRunicCore **)(pCVar5 + 0x30) == (CRunicCore *)0x0)) {
        uVar4 = uVar4 + 1;
        if (*(uint *)(this + 0x50) <= uVar4) break;
        goto LAB_00cd126c;
      }
      uVar4 = uVar4 + 1;
      CRunicCore::removeSafePointer
                (*(CRunicCore **)(pCVar5 + 0x30),(TSafePointer *)(pCVar5 + 0x30),
                 *(uint *)(pCVar5 + 0x38));
      *(undefined8 *)(pCVar5 + 0x30) = 0;
    } while (uVar4 < *(uint *)(this + 0x50));
  }
  if (*(int *)(this + 0x68) == 0) {
    return;
  }
  uVar4 = 0;
  do {
    if (uVar4 < *(uint *)(this + 0x6c)) {
      pCVar5 = *(CSkill **)((ulong)uVar4 * 8 + *(long *)(this + 0x60));
      if (*(CCharacter **)(pCVar5 + 0x40) != param_1) goto LAB_00cd1305;
LAB_00cd1336:
      if (param_1 == (CCharacter *)0x0) goto LAB_00cd1305;
      CRunicCore::removeSafePointer
                ((CRunicCore *)param_1,(TSafePointer *)(pCVar5 + 0x40),*(uint *)(pCVar5 + 0x48));
      *(undefined8 *)(pCVar5 + 0x40) = 0;
      pCVar3 = (CCharacter *)CSkill::getOwnerCharacter(pCVar5);
    }
    else {
      pCVar5 = (CSkill *)**(long **)(this + 0x60);
      if (*(CCharacter **)(pCVar5 + 0x40) == param_1) goto LAB_00cd1336;
LAB_00cd1305:
      pCVar3 = (CCharacter *)CSkill::getOwnerCharacter(pCVar5);
    }
    if ((param_1 == pCVar3) && (*(CRunicCore **)(pCVar5 + 0x30) != (CRunicCore *)0x0)) {
      uVar4 = uVar4 + 1;
      CRunicCore::removeSafePointer
                (*(CRunicCore **)(pCVar5 + 0x30),(TSafePointer *)(pCVar5 + 0x30),
                 *(uint *)(pCVar5 + 0x38));
      *(undefined8 *)(pCVar5 + 0x30) = 0;
      if (*(uint *)(this + 0x68) <= uVar4) {
        return;
      }
    }
    else {
      uVar4 = uVar4 + 1;
      if (*(uint *)(this + 0x68) <= uVar4) {
        return;
      }
    }
  } while( true );
}



/* address=00cd13a0
   symbol=CSkillManager::notifyOfDeletion */

/* CSkillManager::notifyOfDeletion(CItem*) */

void __thiscall CSkillManager::notifyOfDeletion(CSkillManager *this,CItem *param_1)

{
  CItem *pCVar1;
  _Rb_tree_node_base *p_Var2;
  uint uVar3;
  ulong uVar4;
  long lVar5;

  for (p_Var2 = *(_Rb_tree_node_base **)(this + 0x30); (_Rb_tree_node_base *)(this + 0x20) != p_Var2
      ; p_Var2 = (_Rb_tree_node_base *)std::_Rb_tree_increment(p_Var2)) {
    while ((lVar5 = *(long *)**(undefined8 **)(p_Var2 + 0x28), *(CItem **)(lVar5 + 0x30) != param_1
           || (param_1 == (CItem *)0x0))) {
      p_Var2 = (_Rb_tree_node_base *)std::_Rb_tree_increment(p_Var2);
      if ((_Rb_tree_node_base *)(this + 0x20) == p_Var2) goto LAB_00cd1418;
    }
    CRunicCore::removeSafePointer
              ((CRunicCore *)param_1,(TSafePointer *)(lVar5 + 0x30),*(uint *)(lVar5 + 0x38));
    *(undefined8 *)(lVar5 + 0x30) = 0;
  }
LAB_00cd1418:
  if (*(int *)(this + 0x50) != 0) {
    uVar4 = 0;
LAB_00cd144d:
    do {
      uVar3 = (uint)uVar4;
      if (uVar3 < *(uint *)(this + 0x54)) {
        lVar5 = *(long *)(uVar4 * 8 + *(long *)(this + 0x48));
        if (*(CItem **)(lVar5 + 0x40) == param_1) goto LAB_00cd1467;
LAB_00cd143d:
        pCVar1 = *(CItem **)(lVar5 + 0x30);
      }
      else {
        lVar5 = **(long **)(this + 0x48);
        if (*(CItem **)(lVar5 + 0x40) != param_1) goto LAB_00cd143d;
LAB_00cd1467:
        if (param_1 == (CItem *)0x0) goto LAB_00cd143d;
        CRunicCore::removeSafePointer
                  ((CRunicCore *)param_1,(TSafePointer *)(lVar5 + 0x40),*(uint *)(lVar5 + 0x48));
        pCVar1 = *(CItem **)(lVar5 + 0x30);
        *(undefined8 *)(lVar5 + 0x40) = 0;
      }
      if ((pCVar1 != param_1) || (param_1 == (CItem *)0x0)) {
        uVar4 = (ulong)(uVar3 + 1);
        if (*(uint *)(this + 0x50) <= uVar3 + 1) break;
        goto LAB_00cd144d;
      }
      uVar4 = (ulong)(uVar3 + 1);
      CRunicCore::removeSafePointer
                ((CRunicCore *)param_1,(TSafePointer *)(lVar5 + 0x30),*(uint *)(lVar5 + 0x38));
      *(undefined8 *)(lVar5 + 0x30) = 0;
    } while (uVar3 + 1 < *(uint *)(this + 0x50));
  }
  if (*(int *)(this + 0x68) == 0) {
    return;
  }
  uVar3 = 0;
  do {
    if (uVar3 < *(uint *)(this + 0x6c)) {
      lVar5 = *(long *)((ulong)uVar3 * 8 + *(long *)(this + 0x60));
      if (*(CItem **)(lVar5 + 0x40) == param_1) goto LAB_00cd1507;
LAB_00cd14dd:
      pCVar1 = *(CItem **)(lVar5 + 0x30);
    }
    else {
      lVar5 = **(long **)(this + 0x60);
      if (*(CItem **)(lVar5 + 0x40) != param_1) goto LAB_00cd14dd;
LAB_00cd1507:
      if (param_1 == (CItem *)0x0) goto LAB_00cd14dd;
      CRunicCore::removeSafePointer
                ((CRunicCore *)param_1,(TSafePointer *)(lVar5 + 0x40),*(uint *)(lVar5 + 0x48));
      pCVar1 = *(CItem **)(lVar5 + 0x30);
      *(undefined8 *)(lVar5 + 0x40) = 0;
    }
    if ((pCVar1 == param_1) && (param_1 != (CItem *)0x0)) {
      uVar3 = uVar3 + 1;
      CRunicCore::removeSafePointer
                ((CRunicCore *)param_1,(TSafePointer *)(lVar5 + 0x30),*(uint *)(lVar5 + 0x38));
      *(undefined8 *)(lVar5 + 0x30) = 0;
      if (*(uint *)(this + 0x68) <= uVar3) {
        return;
      }
    }
    else {
      uVar3 = uVar3 + 1;
      if (*(uint *)(this + 0x68) <= uVar3) {
        return;
      }
    }
  } while( true );
}



/* address=00cd1570
   symbol=CSkillManager::getPositionForSkill */

/* WARNING: Removing unreachable block (ram,0x00cd1832) */
/* WARNING: Removing unreachable block (ram,0x00cd18d4) */
/* CSkillManager::getPositionForSkill(CSkill*, CBaseUnit*) */

CSkillManager * __thiscall
CSkillManager::getPositionForSkill(CSkillManager *this,CSkill *param_1,CBaseUnit *param_2)

{
  undefined4 uVar1;
  CPositionableObject *this_00;
  double dVar2;
  int iVar3;
  long lVar4;
  float *pfVar5;
  undefined4 uVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float local_b8;
  float fStack_b4;
  float local_a8;
  float fStack_a4;
  float local_98;
  float fStack_94;
  float local_68;
  float fStack_64;
  float local_58;
  float fStack_54;
  float local_48;
  float fStack_44;
  float local_38;
  float fStack_34;
  float local_28;
  float fStack_24;

  uVar6 = *(undefined4 *)(param_1 + 0x58);
  uVar1 = *(undefined4 *)(param_1 + 0x50);
  *(undefined4 *)(this + 0x7c) = *(undefined4 *)(param_1 + 0x54);
  *(undefined4 *)(this + 0x80) = uVar6;
  *(undefined4 *)(this + 0x78) = uVar1;
  iVar3 = CSkill::getTargetType(param_1);
  if (iVar3 == 5) {
    uVar6 = UTILITIES::randomBetweenVolatile(DAT_00fa8760,DAT_00fa47fc);
    *(undefined4 *)(this + 0x78) = uVar6;
    fVar7 = (float)UTILITIES::randomBetweenVolatile(DAT_00fa8760,DAT_00fa47fc);
    fVar8 = *(float *)(this + 0x78);
    fVar9 = *(float *)(this + 0x80);
    *(float *)(this + 0x7c) = fVar7;
    dVar2 = DAT_00fa87a0;
    fVar13 = SQRT(fVar8 * fVar8 + fVar7 * fVar7 + fVar9 * fVar9);
    if (DAT_00fa87a0 < (double)fVar13) {
      fVar13 = DAT_00fa47fc / fVar13;
      *(float *)(this + 0x78) = fVar8 * fVar13;
      *(float *)(this + 0x7c) = fVar7 * fVar13;
      *(float *)(this + 0x80) = fVar13 * fVar9;
    }
    fVar8 = (float)CSkill::getRandomRange(param_1);
    fVar9 = (float)CSkill::getRandomRangeMin(param_1);
    fVar8 = fVar8 - fVar9;
    fVar13 = *(float *)(this + 0x78) * fVar8;
    fVar7 = *(float *)(this + 0x7c) * fVar8;
    fVar8 = fVar8 * *(float *)(this + 0x80);
    *(float *)(this + 0x78) = fVar13;
    *(float *)(this + 0x7c) = fVar7;
    *(float *)(this + 0x80) = fVar8;
    fVar9 = SQRT(fVar13 * fVar13 + fVar7 * fVar7 + fVar8 * fVar8);
    if (dVar2 < (double)fVar9) {
      fVar9 = DAT_00fa47fc / fVar9;
      fVar13 = fVar13 * fVar9;
      fVar7 = fVar7 * fVar9;
      fVar8 = fVar8 * fVar9;
    }
    fVar9 = (float)CSkill::getRandomRangeMin(param_1);
    this_00 = *(CPositionableObject **)(this + 0x88);
    fVar8 = fVar8 * fVar9 + *(float *)(this + 0x80);
    *(float *)(this + 0x78) = fVar13 * fVar9 + *(float *)(this + 0x78);
    *(float *)(this + 0x7c) = fVar7 * fVar9 + *(float *)(this + 0x7c);
    *(float *)(this + 0x80) = fVar8;
    if (this_00 == (CPositionableObject *)0x0) {
      if (param_2 == (CBaseUnit *)0x0) goto LAB_00cd19f8;
      fVar9 = (float)(*(uint *)(param_2 + 0x194) ^ DAT_00fa8780);
      uVar10 = CPositionableObject::getPosition((CPositionableObject *)param_2,true);
      fStack_b4 = (float)((ulong)uVar10 >> 0x20);
      fVar9 = fVar9 + fStack_b4;
      local_b8 = (float)uVar10;
      local_a8 = local_b8;
    }
    else {
      if (param_2 != (CBaseUnit *)0x0) {
        fVar7 = (float)CPositionableObject::getPosition(this_00,true);
        fVar9 = fVar8;
        fVar13 = (float)CPositionableObject::getPosition((CPositionableObject *)param_2,true);
        fVar13 = fVar13 - fVar7;
        fVar9 = fVar9 - fVar8;
        fVar12 = fVar13 * fVar13 + 0.0 + fVar9 * fVar9;
        fVar14 = SQRT(fVar12);
        fVar7 = (float)CSkill::getRange(param_1);
        fVar8 = fVar14;
        if (fVar7 <= fVar14) {
          fVar8 = fVar7;
        }
        fVar7 = (float)CSkill::getRangeMin(param_1);
        if (fVar8 <= fVar7) {
          fVar8 = fVar7;
        }
        fVar7 = 0.0;
        if (dVar2 < (double)fVar14) {
          fVar14 = DAT_00fa47fc / fVar14;
          fVar13 = fVar13 * fVar14;
          fVar7 = fVar14 * 0.0;
          fVar9 = fVar9 * fVar14;
        }
        fVar14 = (float)(*(uint *)(*(CPositionableObject **)(this + 0x88) + 0x194) ^ DAT_00fa8780);
        uVar10 = CPositionableObject::getPosition(*(CPositionableObject **)(this + 0x88),true);
        fStack_94 = (float)((ulong)uVar10 >> 0x20);
        local_98 = (float)uVar10;
        *(float *)(this + 0x80) = fVar9 * fVar8 + fVar12 + 0.0 + *(float *)(this + 0x80);
        *(float *)(this + 0x7c) = fVar7 * fVar8 + fStack_94 + fVar14 + *(float *)(this + 0x7c);
        *(float *)(this + 0x78) = fVar13 * fVar8 + local_98 + 0.0 + *(float *)(this + 0x78);
        goto LAB_00cd19f8;
      }
      fVar9 = (float)(*(uint *)(this_00 + 0x194) ^ DAT_00fa8780);
      uVar10 = CPositionableObject::getPosition(this_00,true);
      fStack_a4 = (float)((ulong)uVar10 >> 0x20);
      fVar9 = fVar9 + fStack_a4;
      local_a8 = (float)uVar10;
    }
    *(float *)(this + 0x78) = local_a8 + 0.0 + *(float *)(this + 0x78);
    *(float *)(this + 0x7c) = fVar9 + *(float *)(this + 0x7c);
    *(float *)(this + 0x80) = fVar8 + 0.0 + *(float *)(this + 0x80);
  }
  else if (iVar3 == 6) {
    uVar6 = UTILITIES::randomBetweenVolatile(DAT_00fa8760,DAT_00fa47fc);
    *(undefined4 *)(this + 0x78) = uVar6;
    fVar7 = (float)UTILITIES::randomBetweenVolatile(DAT_00fa8760,DAT_00fa47fc);
    fVar8 = *(float *)(this + 0x78);
    fVar9 = *(float *)(this + 0x80);
    *(float *)(this + 0x7c) = fVar7;
    dVar2 = DAT_00fa87a0;
    fVar13 = SQRT(fVar8 * fVar8 + fVar7 * fVar7 + fVar9 * fVar9);
    if (DAT_00fa87a0 < (double)fVar13) {
      fVar13 = DAT_00fa47fc / fVar13;
      *(float *)(this + 0x78) = fVar8 * fVar13;
      *(float *)(this + 0x7c) = fVar7 * fVar13;
      *(float *)(this + 0x80) = fVar13 * fVar9;
    }
    fVar8 = (float)CSkill::getRange(param_1);
    fVar9 = (float)CSkill::getRangeMin(param_1);
    fVar8 = fVar8 - fVar9;
    fVar13 = *(float *)(this + 0x78) * fVar8;
    fVar7 = *(float *)(this + 0x7c) * fVar8;
    fVar8 = fVar8 * *(float *)(this + 0x80);
    *(float *)(this + 0x78) = fVar13;
    *(float *)(this + 0x7c) = fVar7;
    *(float *)(this + 0x80) = fVar8;
    fVar9 = SQRT(fVar13 * fVar13 + fVar7 * fVar7 + fVar8 * fVar8);
    if (dVar2 < (double)fVar9) {
      fVar9 = DAT_00fa47fc / fVar9;
      fVar13 = fVar13 * fVar9;
      fVar7 = fVar7 * fVar9;
      fVar8 = fVar8 * fVar9;
    }
    fVar9 = (float)CSkill::getRangeMin(param_1);
    fVar7 = (fVar7 * fVar9 + *(float *)(this + 0x7c)) * DAT_00fce520;
    fVar8 = (fVar8 * fVar9 + *(float *)(this + 0x80)) * DAT_00fce520;
    *(float *)(this + 0x78) = (fVar13 * fVar9 + *(float *)(this + 0x78)) * DAT_00fce520;
    *(float *)(this + 0x7c) = fVar7;
    *(float *)(this + 0x80) = fVar8;
    if (param_2 == (CBaseUnit *)0x0) {
      if (*(CPositionableObject **)(this + 0x88) == (CPositionableObject *)0x0) goto LAB_00cd19f8;
      uVar10 = CPositionableObject::getPosition(*(CPositionableObject **)(this + 0x88),true);
      local_68 = (float)uVar10;
      *(float *)(this + 0x78) = *(float *)(this + 0x78) + local_68;
      fStack_64 = (float)((ulong)uVar10 >> 0x20);
      *(float *)(this + 0x7c) = *(float *)(this + 0x7c) + fStack_64;
      *(float *)(this + 0x80) = *(float *)(this + 0x80) + fVar8;
      fVar8 = (float)CSkill::getRange(param_1);
      param_2 = *(CBaseUnit **)(this + 0x88);
      lVar4 = *(long *)param_2;
    }
    else {
      if (*(CPositionableObject **)(this + 0x88) != (CPositionableObject *)0x0) {
        uVar10 = CPositionableObject::getPosition(*(CPositionableObject **)(this + 0x88),true);
        local_28 = (float)uVar10;
        *(float *)(this + 0x78) = *(float *)(this + 0x78) + local_28;
        fStack_24 = (float)((ulong)uVar10 >> 0x20);
        *(float *)(this + 0x7c) = *(float *)(this + 0x7c) + fStack_24;
        *(float *)(this + 0x80) = *(float *)(this + 0x80) + fVar8;
        uVar10 = CPositionableObject::getPosition(*(CPositionableObject **)(this + 0x88),true);
        fVar9 = fVar8;
        uVar11 = CPositionableObject::getPosition((CPositionableObject *)param_2,true);
        fStack_34 = (float)((ulong)uVar11 >> 0x20);
        local_38 = (float)uVar11;
        fStack_44 = (float)((ulong)uVar10 >> 0x20);
        fStack_34 = fStack_34 - fStack_44;
        local_48 = (float)uVar10;
        local_38 = local_38 - local_48;
        fVar9 = fVar9 - fVar8;
        fVar8 = SQRT(local_38 * local_38 + fStack_34 * fStack_34 + fVar9 * fVar9);
        if (dVar2 < (double)fVar8) {
          fVar8 = DAT_00fa47fc / fVar8;
          local_38 = local_38 * fVar8;
          fStack_34 = fStack_34 * fVar8;
          fVar9 = fVar9 * fVar8;
        }
        fVar7 = (float)CSkill::getRange(param_1);
        fStack_34 = fStack_34 * DAT_00fa86f4;
        fVar9 = fVar9 * DAT_00fa86f4;
        fVar8 = *(float *)(*(long *)(this + 0x88) + 0x194);
        *(float *)(this + 0x78) = local_38 * DAT_00fa86f4 * fVar7 + 0.0 + *(float *)(this + 0x78);
        *(float *)(this + 0x7c) = (fStack_34 * fVar7 - fVar8) + *(float *)(this + 0x7c);
        *(float *)(this + 0x80) = fVar9 * fVar7 + 0.0 + *(float *)(this + 0x80);
        goto LAB_00cd19f8;
      }
      uVar10 = CPositionableObject::getPosition((CPositionableObject *)param_2,true);
      local_58 = (float)uVar10;
      *(float *)(this + 0x78) = *(float *)(this + 0x78) + local_58;
      fStack_54 = (float)((ulong)uVar10 >> 0x20);
      *(float *)(this + 0x7c) = *(float *)(this + 0x7c) + fStack_54;
      *(float *)(this + 0x80) = *(float *)(this + 0x80) + fVar8;
      fVar8 = (float)CSkill::getRange(param_1);
      lVar4 = *(long *)param_2;
    }
    pfVar5 = (float *)(**(code **)(lVar4 + 0x130))(param_2);
    fVar7 = pfVar5[1] * DAT_00fa86f4;
    fVar13 = DAT_00fa86f4 * *pfVar5;
    fVar9 = *(float *)(*(long *)(this + 0x88) + 0x194);
    *(float *)(this + 0x80) = pfVar5[2] * DAT_00fa86f4 * fVar8 + 0.0 + *(float *)(this + 0x80);
    *(float *)(this + 0x7c) = (fVar7 * fVar8 - fVar9) + *(float *)(this + 0x7c);
    *(float *)(this + 0x78) = fVar13 * fVar8 + 0.0 + *(float *)(this + 0x78);
  }
  else if (iVar3 != 1) {
    return (CSkillManager *)0x0;
  }
LAB_00cd19f8:
  return this + 0x78;
}



/* address=00cd2a70
   symbol=CSkillManager::CSkillManager */

/* CSkillManager::CSkillManager(CResourceManager*, CBaseUnit*) */

void __thiscall
CSkillManager::CSkillManager(CSkillManager *this,CResourceManager *param_1,CBaseUnit *param_2)

{
  undefined4 uVar1;

  CRunicCore::CRunicCore((CRunicCore *)this);
  *(undefined ***)this = &PTR__CSkillManager_00ff5d30;
  *(CResourceManager **)(this + 0x10) = param_1;
  *(undefined8 *)(this + 0x40) = 0;
  *(undefined4 *)(this + 0x20) = 0;
  *(undefined8 *)(this + 0x28) = 0;
  *(CSkillManager **)(this + 0x30) = this + 0x20;
  *(CSkillManager **)(this + 0x38) = this + 0x20;
  *(undefined8 *)(this + 0x48) = 0;
  *(undefined4 *)(this + 0x50) = 0;
  *(undefined4 *)(this + 0x54) = 0;
  *(undefined4 *)(this + 0x58) = 10;
  *(undefined8 *)(this + 0x60) = 0;
  *(undefined4 *)(this + 0x68) = 0;
  *(undefined4 *)(this + 0x6c) = 0;
  *(undefined4 *)(this + 0x70) = 10;
  *(undefined8 *)(this + 0x88) = 0;
  *(undefined4 *)(this + 0x90) = 0xffffffff;
  if (param_2 != (CBaseUnit *)0x0) {
                    /* try { // try from 00cd2b1d to 00cd2b21 has its CatchHandler @ 00cd2b42 */
    uVar1 = CRunicCore::addSafePointer((CRunicCore *)param_2,(TSafePointer *)(this + 0x88));
    *(undefined4 *)(this + 0x90) = uVar1;
    *(CBaseUnit **)(this + 0x88) = param_2;
  }
  return;
}



/* address=00cd2b80
   symbol=CSkillManager::knowsSkill */

/* WARNING: Removing unreachable block (ram,0x00cd2ccc) */
/* CSkillManager::knowsSkill(std::wstring const&) */

uint __thiscall CSkillManager::knowsSkill(CSkillManager *this,wstring_conflict *param_1)

{
  CSkillManager *pCVar1;
  wchar_t wVar2;
  ulong uVar3;
  ulong uVar4;
  CSkillManager *pCVar5;
  int iVar6;
  uint uVar7;
  ulong uVar8;
  CSkillManager *pCVar9;
  long lVar10;
  CSkillManager *pCVar11;
  allocator *local_50;
  wchar_t *local_48 [3];

  pCVar1 = this + 0x20;
  STRINGS::StringUpper((STRINGS *)local_48,param_1);
  pCVar9 = *(CSkillManager **)(this + 0x28);
  pCVar11 = pCVar1;
  if (pCVar9 != (CSkillManager *)0x0) {
    uVar3 = *(ulong *)(local_48[0] + -6);
    do {
      uVar4 = *(ulong *)(*(wchar_t **)(pCVar9 + 0x20) + -6);
      uVar8 = uVar4;
      if (uVar3 <= uVar4) {
        uVar8 = uVar3;
      }
      iVar6 = wmemcmp(*(wchar_t **)(pCVar9 + 0x20),local_48[0],uVar8);
      if (iVar6 == 0) {
        lVar10 = uVar4 - uVar3;
        if (0x7fffffff < lVar10) goto LAB_00cd2bce;
        if (-0x80000001 < lVar10) {
          iVar6 = (int)lVar10;
          goto LAB_00cd2bca;
        }
LAB_00cd2c10:
        pCVar5 = *(CSkillManager **)(pCVar9 + 0x18);
      }
      else {
LAB_00cd2bca:
        if (iVar6 < 0) goto LAB_00cd2c10;
LAB_00cd2bce:
        pCVar5 = *(CSkillManager **)(pCVar9 + 0x10);
        pCVar11 = pCVar9;
      }
      pCVar9 = pCVar5;
    } while (pCVar9 != (CSkillManager *)0x0);
  }
  local_50 = (allocator *)(local_48[0] + -6);
  if (pCVar1 == pCVar11) {
LAB_00cd2c5e:
    uVar7 = 0;
  }
  else {
    uVar3 = *(ulong *)local_50;
    uVar4 = *(ulong *)(*(wchar_t **)(pCVar11 + 0x20) + -6);
    uVar8 = uVar3;
    if (uVar4 <= uVar3) {
      uVar8 = uVar4;
    }
    uVar7 = wmemcmp(local_48[0],*(wchar_t **)(pCVar11 + 0x20),uVar8);
    if (uVar7 == 0) {
      lVar10 = uVar3 - uVar4;
      uVar7 = 1;
      if (0x7fffffff < lVar10) goto LAB_00cd2c6f;
      if (lVar10 < -0x80000000) goto LAB_00cd2c5e;
      uVar7 = (uint)lVar10;
    }
    uVar7 = ~uVar7 >> 0x1f;
  }
LAB_00cd2c6f:
  if (local_50 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    local_48[0] = local_48[0] + -2;
    wVar2 = *local_48[0];
    *local_48[0] = *local_48[0] + L'\xffffffff';
    UNLOCK();
    if (wVar2 < L'\x01') {
      std::wstring::_Rep::_M_destroy(local_50);
    }
  }
  return uVar7;
}



/* address=00cd2ce0
   symbol=CSkillManager::getSkill */

/* WARNING: Removing unreachable block (ram,0x00cd2e85) */
/* WARNING: Removing unreachable block (ram,0x00cd2e92) */
/* CSkillManager::getSkill(std::wstring const&, int) */

undefined8 __thiscall
CSkillManager::getSkill(CSkillManager *this,wstring_conflict *param_1,int param_2)

{
  allocator *paVar1;
  wchar_t *pwVar2;
  wchar_t wVar3;
  int iVar4;
  wstring_conflict *pwVar5;
  undefined8 uVar6;
  long *plVar7;
  undefined8 *puVar8;
  uint uVar9;
  bool bVar10;
  wchar_t *local_58 [2];
  wchar_t *local_48 [3];

  STRINGS::StringUpper((STRINGS *)local_48,param_1);
  if (*(int *)(this + 0x68) != 0) {
    uVar9 = 0;
    do {
      if (uVar9 < *(uint *)(this + 0x6c)) {
        puVar8 = (undefined8 *)((ulong)uVar9 * 8 + *(long *)(this + 0x60));
      }
      else {
        puVar8 = *(undefined8 **)(this + 0x60);
      }
                    /* try { // try from 00cd2d28 to 00cd2d37 has its CatchHandler @ 00cd2e72 */
      pwVar5 = (wstring_conflict *)CSkill::getName((CSkill *)*puVar8);
      STRINGS::StringUpper((STRINGS *)local_58,pwVar5);
      pwVar2 = local_58[0];
      paVar1 = (allocator *)(local_58[0] + -6);
      if ((*(size_t *)(local_58[0] + -6) == *(size_t *)(local_48[0] + -6)) &&
         (iVar4 = wmemcmp(local_58[0],local_48[0],*(size_t *)(local_58[0] + -6)), iVar4 == 0)) {
        if (uVar9 < *(uint *)(this + 0x6c)) {
          plVar7 = (long *)((ulong)uVar9 * 8 + *(long *)(this + 0x60));
        }
        else {
          plVar7 = *(long **)(this + 0x60);
        }
        bVar10 = param_2 == *(int *)(*plVar7 + 0xdc);
      }
      else {
        bVar10 = false;
      }
      if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        pwVar2 = pwVar2 + -2;
        wVar3 = *pwVar2;
        *pwVar2 = *pwVar2 + L'\xffffffff';
        UNLOCK();
        if (wVar3 < L'\x01') {
          std::wstring::_Rep::_M_destroy(paVar1);
        }
      }
      if (bVar10) {
        if (uVar9 < *(uint *)(this + 0x6c)) {
          puVar8 = (undefined8 *)((ulong)uVar9 * 8 + *(long *)(this + 0x60));
        }
        else {
          puVar8 = *(undefined8 **)(this + 0x60);
        }
        uVar6 = *puVar8;
        goto LAB_00cd2d6e;
      }
      uVar9 = uVar9 + 1;
    } while (uVar9 < *(uint *)(this + 0x68));
  }
  uVar6 = 0;
LAB_00cd2d6e:
  if ((allocator *)(local_48[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    pwVar2 = local_48[0] + -2;
    wVar3 = *pwVar2;
    *pwVar2 = *pwVar2 + L'\xffffffff';
    UNLOCK();
    if (wVar3 < L'\x01') {
      std::wstring::_Rep::_M_destroy((allocator *)(local_48[0] + -6));
    }
  }
  return uVar6;
}



/* address=00cd2ea0
   symbol=CSkillManager::attemptDeleteOfSkill */

/* WARNING: Removing unreachable block (ram,0x00cd3024) */
/* CSkillManager::attemptDeleteOfSkill(CSkill*) */

void __thiscall CSkillManager::attemptDeleteOfSkill(CSkillManager *this,CSkill *param_1)

{
  CSkillManager *pCVar1;
  wchar_t wVar2;
  ulong uVar3;
  ulong uVar4;
  CSkillManager *pCVar5;
  int iVar6;
  wstring_conflict *pwVar7;
  ulong uVar8;
  CSkillManager *pCVar9;
  long lVar10;
  CSkillManager *pCVar11;
  allocator *local_58;
  wchar_t *local_48 [3];

  pCVar1 = this + 0x20;
  pwVar7 = (wstring_conflict *)CSkill::getName(param_1);
  STRINGS::StringUpper((STRINGS *)local_48,pwVar7);
  pCVar9 = *(CSkillManager **)(this + 0x28);
  pCVar11 = pCVar1;
  if (pCVar9 != (CSkillManager *)0x0) {
    uVar3 = *(ulong *)(local_48[0] + -6);
    do {
      uVar4 = *(ulong *)(*(wchar_t **)(pCVar9 + 0x20) + -6);
      uVar8 = uVar4;
      if (uVar3 <= uVar4) {
        uVar8 = uVar3;
      }
      iVar6 = wmemcmp(*(wchar_t **)(pCVar9 + 0x20),local_48[0],uVar8);
      if (iVar6 == 0) {
        lVar10 = uVar4 - uVar3;
        if (0x7fffffff < lVar10) goto LAB_00cd2efe;
        if (-0x80000001 < lVar10) {
          iVar6 = (int)lVar10;
          goto LAB_00cd2efa;
        }
LAB_00cd2f40:
        pCVar5 = *(CSkillManager **)(pCVar9 + 0x18);
      }
      else {
LAB_00cd2efa:
        if (iVar6 < 0) goto LAB_00cd2f40;
LAB_00cd2efe:
        pCVar5 = *(CSkillManager **)(pCVar9 + 0x10);
        pCVar11 = pCVar9;
      }
      pCVar9 = pCVar5;
    } while (pCVar9 != (CSkillManager *)0x0);
  }
  local_58 = (allocator *)(local_48[0] + -6);
  if (pCVar1 != pCVar11) {
    uVar3 = *(ulong *)local_58;
    uVar4 = *(ulong *)(*(wchar_t **)(pCVar11 + 0x20) + -6);
    uVar8 = uVar3;
    if (uVar4 <= uVar3) {
      uVar8 = uVar4;
    }
    iVar6 = wmemcmp(local_48[0],*(wchar_t **)(pCVar11 + 0x20),uVar8);
    if (iVar6 == 0) {
      lVar10 = uVar3 - uVar4;
      if (0x7fffffff < lVar10) goto LAB_00cd2f93;
      if (lVar10 < -0x80000000) goto LAB_00cd2f90;
      iVar6 = (int)lVar10;
    }
    if (-1 < iVar6) goto LAB_00cd2f93;
  }
LAB_00cd2f90:
  pCVar11 = pCVar1;
LAB_00cd2f93:
  if (local_58 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    local_48[0] = local_48[0] + -2;
    wVar2 = *local_48[0];
    *local_48[0] = *local_48[0] + L'\xffffffff';
    UNLOCK();
    if (wVar2 < L'\x01') {
      std::wstring::_Rep::_M_destroy(local_58);
    }
  }
  if ((pCVar1 == pCVar11) && (param_1 != (CSkill *)0x0)) {
    (**(code **)(*(long *)param_1 + 8))(param_1);
    return;
  }
  return;
}



/* address=00cd3040
   symbol=CSkillManager::~CSkillManager */

/* CSkillManager::~CSkillManager() */

void __thiscall CSkillManager::~CSkillManager(CSkillManager *this)

{
  long *plVar1;
  undefined8 *puVar2;
  long *plVar3;
  _Rb_tree_node_base *p_Var4;
  uint uVar5;
  ulong uVar6;

  *(undefined ***)this = &PTR__CSkillManager_00ff5d30;
  if (*(int *)(this + 0x50) != 0) {
    uVar5 = 0;
    do {
      if (uVar5 < *(uint *)(this + 0x54)) {
        puVar2 = (undefined8 *)((ulong)uVar5 * 8 + *(long *)(this + 0x48));
      }
      else {
        puVar2 = *(undefined8 **)(this + 0x48);
      }
                    /* try { // try from 00cd3072 to 00cd3155 has its CatchHandler @ 00cd31e8 */
      attemptDeleteOfSkill(this,(CSkill *)*puVar2);
      uVar5 = uVar5 + 1;
    } while (uVar5 < *(uint *)(this + 0x50));
  }
  for (p_Var4 = *(_Rb_tree_node_base **)(this + 0x30); p_Var4 != (_Rb_tree_node_base *)(this + 0x20)
      ; p_Var4 = (_Rb_tree_node_base *)std::_Rb_tree_increment(p_Var4)) {
    plVar1 = *(long **)(p_Var4 + 0x28);
    if ((int)plVar1[1] != 0) {
      uVar6 = 0;
      do {
        plVar3 = (long *)(uVar6 * 8 + *plVar1);
        if ((long *)*plVar3 != (long *)0x0) {
          (**(code **)(*(long *)*plVar3 + 8))();
          *(undefined8 *)(*plVar1 + uVar6 * 8) = 0;
          plVar3 = (long *)(uVar6 * 8 + *plVar1);
        }
        *plVar3 = 0;
        uVar5 = (int)uVar6 + 1;
        uVar6 = (ulong)uVar5;
      } while (uVar5 < *(uint *)(plVar1 + 1));
    }
    *(undefined4 *)(plVar1 + 1) = 0;
    *(undefined4 *)((long)plVar1 + 0xc) = 0;
    if ((void *)*plVar1 != (void *)0x0) {
      operator_delete__((void *)*plVar1);
    }
    *plVar1 = 0;
    puVar2 = *(undefined8 **)(p_Var4 + 0x28);
    if (puVar2 != (undefined8 *)0x0) {
      if ((void *)*puVar2 != (void *)0x0) {
        operator_delete__((void *)*puVar2);
        *puVar2 = 0;
      }
      Ogre::NedAllocImpl::deallocBytes(puVar2);
      *(undefined8 *)(p_Var4 + 0x28) = 0;
    }
  }
  if (*(CRunicCore **)(this + 0x88) != (CRunicCore *)0x0) {
                    /* try { // try from 00cd317e to 00cd3182 has its CatchHandler @ 00cd3259 */
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(this + 0x88),(TSafePointer *)(this + 0x88),*(uint *)(this + 0x90));
  }
  *(undefined8 *)(this + 0x88) = 0;
  *(undefined4 *)(this + 0x90) = 0xffffffff;
  if (*(void **)(this + 0x60) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x60));
    *(undefined8 *)(this + 0x60) = 0;
  }
  if (*(void **)(this + 0x48) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x48));
    *(undefined8 *)(this + 0x48) = 0;
  }
                    /* try { // try from 00cd31cd to 00cd31d1 has its CatchHandler @ 00cd325b */
  std::
  _Rb_tree<std::wstring,std::pair<std::wstring_const,TArrayList<CSkill*>*>,std::_Select1st<std::pair<std::wstring_const,TArrayList<CSkill*>*>>,std::less<std::wstring>,std::allocator<std::pair<std::wstring_const,TArrayList<CSkill*>*>>>
  ::_M_erase((_Rb_tree<std::wstring,std::pair<std::wstring_const,TArrayList<CSkill*>*>,std::_Select1st<std::pair<std::wstring_const,TArrayList<CSkill*>*>>,std::less<std::wstring>,std::allocator<std::pair<std::wstring_const,TArrayList<CSkill*>*>>>
              *)(this + 0x18),*(_Rb_tree_node **)(this + 0x28));
  CRunicCore::~CRunicCore((CRunicCore *)this);
  return;
}



/* address=00cd3270
   symbol=CSkillManager::~CSkillManager */

/* CSkillManager::~CSkillManager() */

void __thiscall CSkillManager::~CSkillManager(CSkillManager *this)

{
  ~CSkillManager(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}



/* address=00cd3290
   symbol=CSkillManager::getSkill */

/* WARNING: Removing unreachable block (ram,0x00cd340a) */
/* CSkillManager::getSkill(std::wstring const&) */

undefined8 __thiscall CSkillManager::getSkill(CSkillManager *this,wstring_conflict *param_1)

{
  CSkillManager *pCVar1;
  wchar_t wVar2;
  ulong uVar3;
  ulong uVar4;
  CSkillManager *pCVar5;
  int iVar6;
  ulong uVar7;
  CSkillManager *pCVar8;
  long lVar9;
  CSkillManager *pCVar10;
  allocator *local_50;
  wchar_t *local_48 [3];

  pCVar1 = this + 0x20;
  STRINGS::StringUpper((STRINGS *)local_48,param_1);
  pCVar8 = *(CSkillManager **)(this + 0x28);
  pCVar10 = pCVar1;
  if (pCVar8 != (CSkillManager *)0x0) {
    uVar3 = *(ulong *)(local_48[0] + -6);
    do {
      uVar4 = *(ulong *)(*(wchar_t **)(pCVar8 + 0x20) + -6);
      uVar7 = uVar4;
      if (uVar3 <= uVar4) {
        uVar7 = uVar3;
      }
      iVar6 = wmemcmp(*(wchar_t **)(pCVar8 + 0x20),local_48[0],uVar7);
      if (iVar6 == 0) {
        lVar9 = uVar4 - uVar3;
        if (0x7fffffff < lVar9) goto LAB_00cd32de;
        if (-0x80000001 < lVar9) {
          iVar6 = (int)lVar9;
          goto LAB_00cd32da;
        }
LAB_00cd3320:
        pCVar5 = *(CSkillManager **)(pCVar8 + 0x18);
      }
      else {
LAB_00cd32da:
        if (iVar6 < 0) goto LAB_00cd3320;
LAB_00cd32de:
        pCVar5 = *(CSkillManager **)(pCVar8 + 0x10);
        pCVar10 = pCVar8;
      }
      pCVar8 = pCVar5;
    } while (pCVar8 != (CSkillManager *)0x0);
  }
  local_50 = (allocator *)(local_48[0] + -6);
  if (pCVar1 != pCVar10) {
    uVar3 = *(ulong *)local_50;
    uVar4 = *(ulong *)(*(wchar_t **)(pCVar10 + 0x20) + -6);
    uVar7 = uVar3;
    if (uVar4 <= uVar3) {
      uVar7 = uVar4;
    }
    iVar6 = wmemcmp(local_48[0],*(wchar_t **)(pCVar10 + 0x20),uVar7);
    if (iVar6 == 0) {
      lVar9 = uVar3 - uVar4;
      if (0x7fffffff < lVar9) goto LAB_00cd3373;
      if (lVar9 < -0x80000000) goto LAB_00cd3370;
      iVar6 = (int)lVar9;
    }
    if (-1 < iVar6) goto LAB_00cd3373;
  }
LAB_00cd3370:
  pCVar10 = pCVar1;
LAB_00cd3373:
  if (local_50 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    local_48[0] = local_48[0] + -2;
    wVar2 = *local_48[0];
    *local_48[0] = *local_48[0] + L'\xffffffff';
    UNLOCK();
    if (wVar2 < L'\x01') {
      std::wstring::_Rep::_M_destroy(local_50);
    }
  }
  if ((pCVar1 != pCVar10) && (*(int *)(*(undefined8 **)(pCVar10 + 0x28) + 1) != 0)) {
    return *(undefined8 *)**(undefined8 **)(pCVar10 + 0x28);
  }
  return 0;
}



/* address=00cd3420
   symbol=CSkillManager::getSkillLevel */

/* CSkillManager::getSkillLevel(std::wstring const&) */

undefined4 __thiscall CSkillManager::getSkillLevel(CSkillManager *this,wstring_conflict *param_1)

{
  undefined4 uVar1;
  long lVar2;

  lVar2 = getSkill(this,param_1);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = *(undefined4 *)(lVar2 + 0xdc);
  }
  return uVar1;
}



/* address=00cd3440
   symbol=CSkillManager::stopSkillsByName */

/* WARNING: Removing unreachable block (ram,0x00cd35fa) */
/* WARNING: Removing unreachable block (ram,0x00cd35ed) */
/* CSkillManager::stopSkillsByName(std::wstring, bool) */

void __thiscall
CSkillManager::stopSkillsByName(CSkillManager *this,wstring_conflict *param_2,char param_3)

{
  allocator *paVar1;
  wchar_t *pwVar2;
  int *piVar3;
  wchar_t wVar4;
  int iVar5;
  wstring_conflict *pwVar6;
  undefined8 *puVar7;
  uint uVar8;
  bool bVar9;
  wchar_t *local_58 [2];
  long local_48 [3];

  STRINGS::StringUpper((STRINGS *)local_48,param_2);
                    /* try { // try from 00cd346b to 00cd346f has its CatchHandler @ 00cd35da */
  std::wstring::assign(param_2);
  if ((allocator *)(local_48[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar3 = (int *)(local_48[0] + -8);
    iVar5 = *piVar3;
    *piVar3 = *piVar3 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
    }
  }
  uVar8 = 0;
  if (*(int *)(this + 0x50) != 0) {
    do {
      while( true ) {
        if (uVar8 < *(uint *)(this + 0x54)) {
          puVar7 = (undefined8 *)((ulong)uVar8 * 8 + *(long *)(this + 0x48));
        }
        else {
          puVar7 = *(undefined8 **)(this + 0x48);
        }
        pwVar6 = (wstring_conflict *)CSkill::getName((CSkill *)*puVar7);
        STRINGS::StringUpper((STRINGS *)local_58,pwVar6);
        pwVar2 = local_58[0];
        bVar9 = false;
        paVar1 = (allocator *)(local_58[0] + -6);
        if (*(size_t *)(local_58[0] + -6) == *(size_t *)(*(wchar_t **)param_2 + -6)) {
          iVar5 = wmemcmp(local_58[0],*(wchar_t **)param_2,*(size_t *)(local_58[0] + -6));
          bVar9 = iVar5 == 0;
        }
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
        if (bVar9) break;
LAB_00cd34f8:
        uVar8 = uVar8 + 1;
        if (*(uint *)(this + 0x50) <= uVar8) {
          return;
        }
      }
      if (param_3 != '\0') {
        CSkill::stopSkill();
        goto LAB_00cd34f8;
      }
      if (uVar8 < *(uint *)(this + 0x54)) {
        puVar7 = (undefined8 *)((ulong)uVar8 * 8 + *(long *)(this + 0x48));
      }
      else {
        puVar7 = *(undefined8 **)(this + 0x48);
      }
      uVar8 = uVar8 + 1;
      CSkill::attemptToStopSkill((CSkill *)*puVar7);
    } while (uVar8 < *(uint *)(this + 0x50));
  }
  return;
}



/* address=00cd3610
   symbol=CSkillManager::deleteSpecificSkill */

/* WARNING: Removing unreachable block (ram,0x00cd3aa8) */
/* WARNING: Removing unreachable block (ram,0x00cd3abd) */
/* CSkillManager::deleteSpecificSkill(CSkill*) */

void __thiscall CSkillManager::deleteSpecificSkill(CSkillManager *this,CSkill *param_1)

{
  _Rb_tree_node_base *p_Var1;
  long *plVar2;
  allocator *paVar3;
  int *piVar4;
  wchar_t wVar5;
  size_t __n;
  ulong uVar6;
  CSkill *pCVar7;
  bool bVar8;
  _Rb_tree_node_base *p_Var9;
  int iVar10;
  undefined8 *puVar11;
  undefined8 *puVar12;
  wstring_conflict *pwVar13;
  void *pvVar14;
  long *plVar15;
  uint uVar16;
  ulong uVar17;
  long *plVar18;
  long lVar19;
  uint uVar20;
  ulong uVar21;
  _Rb_tree_node_base *p_Var22;
  long lVar23;
  uint uVar24;
  _Rb_tree_node_base *local_60;
  allocator *local_50;
  wchar_t *local_48 [3];

  uVar20 = *(uint *)(this + 0x68);
  if (uVar20 == 0) {
LAB_00cd3a22:
    bVar8 = false;
  }
  else {
    plVar15 = *(long **)(this + 0x60);
    uVar24 = 0;
    lVar23 = 8;
    if (param_1 == (CSkill *)*plVar15) {
      lVar19 = 0;
    }
    else {
      do {
        lVar19 = lVar23;
        uVar24 = uVar24 + 1;
        if (uVar20 <= uVar24) goto LAB_00cd3660;
        lVar23 = lVar19 + 8;
      } while (param_1 != *(CSkill **)((long)plVar15 + lVar19));
    }
    *(uint *)(this + 0x68) = uVar20 - 1;
    *(long *)((long)plVar15 + lVar19) = plVar15[uVar20 - 1];
    if (*(int *)(this + 0x68) == 0) goto LAB_00cd3a22;
LAB_00cd3660:
    uVar21 = 0;
    bVar8 = false;
    do {
      while( true ) {
        puVar11 = (undefined8 *)CSkill::getName(param_1);
        uVar20 = (uint)uVar21;
        if (uVar20 < *(uint *)(this + 0x6c)) {
          puVar12 = (undefined8 *)(uVar21 * 8 + *(long *)(this + 0x60));
        }
        else {
          puVar12 = *(undefined8 **)(this + 0x60);
        }
        puVar12 = (undefined8 *)CSkill::getName((CSkill *)*puVar12);
        __n = *(size_t *)((wchar_t *)*puVar12 + -6);
        if ((__n == *(size_t *)((wchar_t *)*puVar11 + -6)) &&
           (iVar10 = wmemcmp((wchar_t *)*puVar12,(wchar_t *)*puVar11,__n), iVar10 == 0)) break;
        uVar21 = (ulong)(uVar20 + 1);
        if (*(uint *)(this + 0x68) <= uVar20 + 1) goto LAB_00cd36ec;
      }
      if (uVar20 < *(uint *)(this + 0x6c)) {
        plVar15 = (long *)(uVar21 * 8 + *(long *)(this + 0x60));
      }
      else {
        plVar15 = *(long **)(this + 0x60);
      }
      if (*(int *)(*plVar15 + 0xdc) == *(int *)(param_1 + 0xdc)) {
        bVar8 = true;
      }
      uVar21 = (ulong)(uVar20 + 1);
    } while (uVar20 + 1 < *(uint *)(this + 0x68));
  }
LAB_00cd36ec:
  if (0 < *(int *)(this + 0x50)) {
    uVar20 = 0;
    do {
      while (*(uint *)(this + 0x54) <= uVar20) {
        if (param_1 == (CSkill *)**(long **)(this + 0x48)) goto LAB_00cd372b;
LAB_00cd3709:
        uVar20 = uVar20 + 1;
        if (*(int *)(this + 0x50) <= (int)uVar20) goto LAB_00cd3750;
      }
      if (param_1 != *(CSkill **)((ulong)uVar20 * 8 + *(long *)(this + 0x48))) goto LAB_00cd3709;
LAB_00cd372b:
      CSkill::stopSkill();
      uVar24 = *(uint *)(this + 0x50);
      if (uVar20 < uVar24) {
        *(uint *)(this + 0x50) = uVar24 - 1;
        *(undefined8 *)(*(long *)(this + 0x48) + (ulong)uVar20 * 8) =
             *(undefined8 *)(*(long *)(this + 0x48) + (ulong)(uVar24 - 1) * 8);
        uVar24 = *(uint *)(this + 0x50);
      }
    } while ((int)uVar20 < (int)uVar24);
  }
LAB_00cd3750:
  pwVar13 = (wstring_conflict *)CSkill::getName(param_1);
  STRINGS::StringUpper((STRINGS *)local_48,pwVar13);
  p_Var22 = *(_Rb_tree_node_base **)(this + 0x28);
  p_Var1 = (_Rb_tree_node_base *)(this + 0x20);
  local_60 = p_Var1;
  if (p_Var22 != (_Rb_tree_node_base *)0x0) {
    uVar21 = *(ulong *)(local_48[0] + -6);
    do {
      uVar6 = *(ulong *)(*(wchar_t **)(p_Var22 + 0x20) + -6);
      uVar17 = uVar21;
      if (uVar6 <= uVar21) {
        uVar17 = uVar6;
      }
      iVar10 = wmemcmp(*(wchar_t **)(p_Var22 + 0x20),local_48[0],uVar17);
      if (iVar10 == 0) {
        lVar23 = uVar6 - uVar21;
        if (0x7fffffff < lVar23) goto LAB_00cd37a7;
        if (-0x80000001 < lVar23) {
          iVar10 = (int)lVar23;
          goto LAB_00cd37a3;
        }
LAB_00cd37ef:
        p_Var9 = *(_Rb_tree_node_base **)(p_Var22 + 0x18);
      }
      else {
LAB_00cd37a3:
        if (iVar10 < 0) goto LAB_00cd37ef;
LAB_00cd37a7:
        p_Var9 = *(_Rb_tree_node_base **)(p_Var22 + 0x10);
        local_60 = p_Var22;
      }
      p_Var22 = p_Var9;
    } while (p_Var22 != (_Rb_tree_node_base *)0x0);
  }
  local_50 = (allocator *)(local_48[0] + -6);
  if (p_Var1 != local_60) {
    uVar21 = *(ulong *)(*(wchar_t **)(local_60 + 0x20) + -6);
    uVar6 = *(ulong *)local_50;
    uVar17 = uVar6;
    if (uVar21 <= uVar6) {
      uVar17 = uVar21;
    }
    iVar10 = wmemcmp(local_48[0],*(wchar_t **)(local_60 + 0x20),uVar17);
    if (iVar10 == 0) {
      lVar23 = uVar6 - uVar21;
      if (0x7fffffff < lVar23) goto LAB_00cd3855;
      if (lVar23 < -0x80000000) goto LAB_00cd3850;
      iVar10 = (int)lVar23;
    }
    if (-1 < iVar10) goto LAB_00cd3855;
  }
LAB_00cd3850:
  local_60 = p_Var1;
LAB_00cd3855:
  if (local_50 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    local_48[0] = local_48[0] + -2;
    wVar5 = *local_48[0];
    *local_48[0] = *local_48[0] + L'\xffffffff';
    UNLOCK();
    if (wVar5 < L'\x01') {
      std::wstring::_Rep::_M_destroy(local_50);
    }
  }
  if (p_Var1 != local_60) {
    plVar15 = *(long **)(local_60 + 0x28);
    uVar20 = *(uint *)(plVar15 + 1);
    if (0 < (int)uVar20) {
      uVar24 = 0;
      do {
        if (uVar24 < *(uint *)((long)plVar15 + 0xc)) {
          plVar18 = (long *)((ulong)uVar24 * 8 + *plVar15);
        }
        else {
          plVar18 = (long *)*plVar15;
        }
        pCVar7 = (CSkill *)*plVar18;
        if ((pCVar7 == param_1) || (!bVar8)) {
          if (*(uint *)(this + 0x50) == 0) {
LAB_00cd38d9:
            if (uVar24 < uVar20) {
              *(uint *)(plVar15 + 1) = uVar20 - 1;
              *(undefined8 *)(*plVar15 + (ulong)uVar24 * 8) =
                   *(undefined8 *)(*plVar15 + (ulong)(uVar20 - 1) * 8);
            }
            if (pCVar7 != (CSkill *)0x0) {
              (**(code **)(*(long *)pCVar7 + 8))();
            }
            plVar15 = *(long **)(local_60 + 0x28);
            uVar24 = uVar24 - 1;
          }
          else {
            plVar18 = *(long **)(this + 0x48);
            uVar16 = 0;
            if (pCVar7 != (CSkill *)*plVar18) {
              do {
                uVar16 = uVar16 + 1;
                if (*(uint *)(this + 0x50) <= uVar16) goto LAB_00cd38d9;
                plVar2 = plVar18 + 1;
                plVar18 = plVar18 + 1;
              } while (pCVar7 != (CSkill *)*plVar2);
              if (uVar16 == 0xffffffff) goto LAB_00cd38d9;
            }
          }
        }
        uVar20 = *(uint *)(plVar15 + 1);
        uVar24 = uVar24 + 1;
      } while ((int)uVar24 < (int)uVar20);
    }
    if ((!bVar8) || (*(long *)(this + 0x40) == 0)) {
      if ((void *)*plVar15 != (void *)0x0) {
        operator_delete__((void *)*plVar15);
        *plVar15 = 0;
      }
      Ogre::NedAllocImpl::deallocBytes(plVar15);
      *(undefined8 *)(local_60 + 0x28) = 0;
      pvVar14 = (void *)std::_Rb_tree_rebalance_for_erase(local_60,p_Var1);
      paVar3 = (allocator *)(*(long *)((long)pvVar14 + 0x20) + -0x18);
      if (paVar3 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar4 = (int *)(*(long *)((long)pvVar14 + 0x20) + -8);
        iVar10 = *piVar4;
        *piVar4 = *piVar4 + -1;
        UNLOCK();
        if (iVar10 < 1) {
          std::wstring::_Rep::_M_destroy(paVar3);
        }
      }
      operator_delete(pvVar14);
      *(long *)(this + 0x40) = *(long *)(this + 0x40) + -1;
    }
  }
  return;
}



/* address=00cd3ad0
   symbol=CSkillManager::decrementSkillCharges */

/* WARNING: Removing unreachable block (ram,0x00cd3c87) */
/* CSkillManager::decrementSkillCharges(CSkill*) */

void __thiscall CSkillManager::decrementSkillCharges(CSkillManager *this,CSkill *param_1)

{
  CSkillManager *pCVar1;
  wchar_t wVar2;
  ulong uVar3;
  ulong uVar4;
  undefined8 *puVar5;
  CSkillManager *pCVar6;
  int iVar7;
  uint uVar8;
  wstring_conflict *pwVar9;
  uint uVar10;
  ulong uVar11;
  long *plVar12;
  CSkillManager *pCVar13;
  long lVar14;
  allocator *paVar15;
  CSkillManager *local_50;
  wchar_t *local_48 [3];

  if (param_1 == (CSkill *)0x0) {
    return;
  }
  pCVar1 = this + 0x20;
  pwVar9 = (wstring_conflict *)CSkill::getName(param_1);
  STRINGS::StringUpper((STRINGS *)local_48,pwVar9);
  pCVar13 = *(CSkillManager **)(this + 0x28);
  local_50 = pCVar1;
  if (pCVar13 != (CSkillManager *)0x0) {
    uVar3 = *(ulong *)(local_48[0] + -6);
    do {
      uVar4 = *(ulong *)(*(wchar_t **)(pCVar13 + 0x20) + -6);
      uVar11 = uVar4;
      if (uVar3 <= uVar4) {
        uVar11 = uVar3;
      }
      iVar7 = wmemcmp(*(wchar_t **)(pCVar13 + 0x20),local_48[0],uVar11);
      if (iVar7 == 0) {
        lVar14 = uVar4 - uVar3;
        if (0x7fffffff < lVar14) goto LAB_00cd3b2e;
        if (-0x80000001 < lVar14) {
          iVar7 = (int)lVar14;
          goto LAB_00cd3b2a;
        }
LAB_00cd3b72:
        pCVar6 = *(CSkillManager **)(pCVar13 + 0x18);
      }
      else {
LAB_00cd3b2a:
        if (iVar7 < 0) goto LAB_00cd3b72;
LAB_00cd3b2e:
        pCVar6 = *(CSkillManager **)(pCVar13 + 0x10);
        local_50 = pCVar13;
      }
      pCVar13 = pCVar6;
    } while (pCVar13 != (CSkillManager *)0x0);
  }
  paVar15 = (allocator *)(local_48[0] + -6);
  if (pCVar1 != local_50) {
    uVar3 = *(ulong *)paVar15;
    uVar4 = *(ulong *)(*(wchar_t **)(local_50 + 0x20) + -6);
    uVar11 = uVar3;
    if (uVar4 <= uVar3) {
      uVar11 = uVar4;
    }
    iVar7 = wmemcmp(local_48[0],*(wchar_t **)(local_50 + 0x20),uVar11);
    if (iVar7 == 0) {
      lVar14 = uVar3 - uVar4;
      if (0x7fffffff < lVar14) goto LAB_00cd3bba;
      if (lVar14 < -0x80000000) goto LAB_00cd3c44;
      iVar7 = (int)lVar14;
    }
    if (-1 < iVar7) goto LAB_00cd3bba;
  }
LAB_00cd3c44:
  local_50 = pCVar1;
LAB_00cd3bba:
  if (paVar15 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    local_48[0] = local_48[0] + -2;
    wVar2 = *local_48[0];
    *local_48[0] = *local_48[0] + L'\xffffffff';
    UNLOCK();
    if (wVar2 < L'\x01') {
      std::wstring::_Rep::_M_destroy(paVar15);
    }
  }
  if (pCVar1 != local_50) {
    puVar5 = *(undefined8 **)(local_50 + 0x28);
    plVar12 = (long *)*puVar5;
    uVar10 = *(uint *)((long)puVar5 + 0xc);
    iVar7 = *(int *)(*plVar12 + 0x124);
    if ((0 < iVar7) && (*(int *)(puVar5 + 1) != 0)) {
      uVar8 = 0;
      while( true ) {
        if (uVar8 < uVar10) {
          plVar12 = plVar12 + uVar8;
        }
        uVar8 = uVar8 + 1;
        *(int *)(*plVar12 + 0x124) = iVar7 + -1;
        puVar5 = *(undefined8 **)(local_50 + 0x28);
        if (*(uint *)(puVar5 + 1) <= uVar8) break;
        uVar10 = *(uint *)((long)puVar5 + 0xc);
        plVar12 = (long *)*puVar5;
      }
    }
  }
  return;
}



/* address=00cd3ca0
   symbol=CSkillManager::deleteSkill */

/* WARNING: Removing unreachable block (ram,0x00cd3f7e) */
/* WARNING: Removing unreachable block (ram,0x00cd3f8e) */
/* CSkillManager::deleteSkill(std::wstring const&) */

void __thiscall CSkillManager::deleteSkill(CSkillManager *this,wstring_conflict *param_1)

{
  _Rb_tree_node_base *p_Var1;
  long *plVar2;
  allocator *paVar3;
  int *piVar4;
  wchar_t wVar5;
  ulong uVar6;
  ulong uVar7;
  _Rb_tree_node_base *p_Var8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  void *pvVar12;
  long *plVar13;
  ulong uVar14;
  long *plVar15;
  long lVar16;
  _Rb_tree_node_base *p_Var17;
  uint uVar18;
  long lVar19;
  _Rb_tree_node_base *p_Var20;
  allocator *local_50;
  wchar_t *local_48 [3];

  STRINGS::StringUpper((STRINGS *)local_48,param_1);
  p_Var17 = *(_Rb_tree_node_base **)(this + 0x28);
  p_Var1 = (_Rb_tree_node_base *)(this + 0x20);
  p_Var20 = p_Var1;
  if (p_Var17 != (_Rb_tree_node_base *)0x0) {
    uVar6 = *(ulong *)(local_48[0] + -6);
    do {
      uVar7 = *(ulong *)(*(wchar_t **)(p_Var17 + 0x20) + -6);
      uVar14 = uVar7;
      if (uVar6 <= uVar7) {
        uVar14 = uVar6;
      }
      iVar9 = wmemcmp(*(wchar_t **)(p_Var17 + 0x20),local_48[0],uVar14);
      if (iVar9 == 0) {
        lVar19 = uVar7 - uVar6;
        if (0x7fffffff < lVar19) goto LAB_00cd3cf7;
        if (-0x80000001 < lVar19) {
          iVar9 = (int)lVar19;
          goto LAB_00cd3cf3;
        }
LAB_00cd3d39:
        p_Var8 = *(_Rb_tree_node_base **)(p_Var17 + 0x18);
      }
      else {
LAB_00cd3cf3:
        if (iVar9 < 0) goto LAB_00cd3d39;
LAB_00cd3cf7:
        p_Var8 = *(_Rb_tree_node_base **)(p_Var17 + 0x10);
        p_Var20 = p_Var17;
      }
      p_Var17 = p_Var8;
    } while (p_Var17 != (_Rb_tree_node_base *)0x0);
  }
  local_50 = (allocator *)(local_48[0] + -6);
  if (p_Var1 != p_Var20) {
    uVar6 = *(ulong *)local_50;
    uVar7 = *(ulong *)(*(wchar_t **)(p_Var20 + 0x20) + -6);
    uVar14 = uVar6;
    if (uVar7 <= uVar6) {
      uVar14 = uVar7;
    }
    iVar9 = wmemcmp(local_48[0],*(wchar_t **)(p_Var20 + 0x20),uVar14);
    if (iVar9 == 0) {
      lVar19 = uVar6 - uVar7;
      if (0x7fffffff < lVar19) goto LAB_00cd3d91;
      if (lVar19 < -0x80000000) goto LAB_00cd3d8c;
      iVar9 = (int)lVar19;
    }
    if (-1 < iVar9) goto LAB_00cd3d91;
  }
LAB_00cd3d8c:
  p_Var20 = p_Var1;
LAB_00cd3d91:
  if (local_50 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    local_48[0] = local_48[0] + -2;
    wVar5 = *local_48[0];
    *local_48[0] = *local_48[0] + L'\xffffffff';
    UNLOCK();
    if (wVar5 < L'\x01') {
      std::wstring::_Rep::_M_destroy(local_50);
    }
  }
  if (p_Var1 != p_Var20) {
    plVar13 = *(long **)(p_Var20 + 0x28);
    if ((int)plVar13[1] != 0) {
      uVar18 = 0;
      do {
        if (uVar18 < *(uint *)((long)plVar13 + 0xc)) {
          plVar13 = (long *)((ulong)uVar18 * 8 + *plVar13);
        }
        else {
          plVar13 = (long *)*plVar13;
        }
        uVar11 = *(uint *)(this + 0x68);
        plVar13 = (long *)*plVar13;
        if (uVar11 != 0) {
          plVar15 = *(long **)(this + 0x60);
          uVar10 = 0;
          lVar19 = 8;
          if (plVar13 == (long *)*plVar15) {
            lVar16 = 0;
          }
          else {
            do {
              lVar16 = lVar19;
              uVar10 = uVar10 + 1;
              if (uVar11 <= uVar10) goto LAB_00cd3e08;
              lVar19 = lVar16 + 8;
            } while (plVar13 != *(long **)((long)plVar15 + lVar16));
          }
          *(uint *)(this + 0x68) = uVar11 - 1;
          *(long *)((long)plVar15 + lVar16) = plVar15[uVar11 - 1];
        }
LAB_00cd3e08:
        if (*(uint *)(this + 0x50) == 0) {
LAB_00cd3e38:
          if (plVar13 != (long *)0x0) {
            (**(code **)(*plVar13 + 8))();
          }
        }
        else {
          plVar15 = *(long **)(this + 0x48);
          uVar11 = 0;
          if (plVar13 != (long *)*plVar15) {
            do {
              uVar11 = uVar11 + 1;
              if (*(uint *)(this + 0x50) <= uVar11) goto LAB_00cd3e38;
              plVar2 = plVar15 + 1;
              plVar15 = plVar15 + 1;
            } while (plVar13 != (long *)*plVar2);
            if (uVar11 == 0xffffffff) goto LAB_00cd3e38;
          }
        }
        plVar13 = *(long **)(p_Var20 + 0x28);
        uVar18 = uVar18 + 1;
      } while (uVar18 < *(uint *)(plVar13 + 1));
    }
    if ((void *)*plVar13 != (void *)0x0) {
      operator_delete__((void *)*plVar13);
      *plVar13 = 0;
    }
    Ogre::NedAllocImpl::deallocBytes(plVar13);
    *(undefined8 *)(p_Var20 + 0x28) = 0;
    pvVar12 = (void *)std::_Rb_tree_rebalance_for_erase(p_Var20,p_Var1);
    paVar3 = (allocator *)(*(long *)((long)pvVar12 + 0x20) + -0x18);
    if (paVar3 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar4 = (int *)(*(long *)((long)pvVar12 + 0x20) + -8);
      iVar9 = *piVar4;
      *piVar4 = *piVar4 + -1;
      UNLOCK();
      if (iVar9 < 1) {
        std::wstring::_Rep::_M_destroy(paVar3);
      }
    }
    operator_delete(pvVar12);
    *(long *)(this + 0x40) = *(long *)(this + 0x40) + -1;
  }
  return;
}



/* address=00cd3fa0
   symbol=CSkillManager::deleteSkill */

/* CSkillManager::deleteSkill(CSkill*) */

void __thiscall CSkillManager::deleteSkill(CSkillManager *this,CSkill *param_1)

{
  wstring_conflict *pwVar1;

  if (param_1 != (CSkill *)0x0) {
    pwVar1 = (wstring_conflict *)CSkill::getName(param_1);
    deleteSkill(this,pwVar1);
    return;
  }
  return;
}



/* address=00cd3fd0
   symbol=CSkillManager::addSkill */

/* WARNING: Removing unreachable block (ram,0x00cd45ab) */
/* CSkillManager::addSkill(CSkill*, bool, bool) */

CSkill * __thiscall
CSkillManager::addSkill(CSkillManager *this,CSkill *param_1,bool param_2,bool param_3)

{
  CSkillManager *pCVar1;
  wchar_t wVar2;
  ulong uVar3;
  long *plVar4;
  CDataGroup *pCVar5;
  wchar_t *__s2;
  int iVar6;
  uint uVar7;
  wstring_conflict *pwVar8;
  void *pvVar9;
  CSkill *this_00;
  undefined8 *puVar10;
  CSkillManager *pCVar11;
  CSkillManager *pCVar12;
  CSkillManager *pCVar13;
  ulong uVar14;
  ulong uVar15;
  uint uVar16;
  long lVar17;
  allocator *paVar18;
  CSkillManager *local_a0;
  CSkillManager *local_98;
  CSkillManager *local_80;
  wstring_conflict local_78 [8];
  undefined8 local_70;
  wchar_t *local_68 [2];
  wchar_t *local_58 [2];
  wchar_t *local_48 [3];

  if (param_1 == (CSkill *)0x0) {
    return (CSkill *)0x0;
  }
  this_00 = param_1;
  if (param_2) {
    pCVar5 = *(CDataGroup **)(param_1 + 0x28);
    uVar7 = *(uint *)(param_1 + 0xdc);
    this_00 = (CSkill *)Ogre::NedAllocImpl::allocBytes(0x160,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00cd41eb to 00cd41ef has its CatchHandler @ 00cd4598 */
    CSkill::CSkill(this_00,*(CResourceManager **)(this + 0x10),pCVar5);
    CSkill::_setLevelOfSkillFromSkillManager(this_00,uVar7);
    this_00[0x6b] = (CSkill)(((byte)param_1[0x6d] & ((byte)param_1[0x6b] ^ 1)) == 0);
    *(undefined4 *)(this_00 + 0x124) = *(undefined4 *)(param_1 + 0x124);
    *(undefined4 *)(this_00 + 0x10c) = *(undefined4 *)(param_1 + 0x10c);
  }
  pwVar8 = (wstring_conflict *)CSkill::getName(this_00);
  STRINGS::StringUpper((STRINGS *)local_48,pwVar8);
  pCVar1 = this + 0x20;
  pCVar13 = *(CSkillManager **)(this + 0x28);
  local_a0 = pCVar1;
  if (pCVar13 != (CSkillManager *)0x0) {
    uVar14 = *(ulong *)(local_48[0] + -6);
    do {
      uVar3 = *(ulong *)(*(wchar_t **)(pCVar13 + 0x20) + -6);
      uVar15 = uVar3;
      if (uVar14 <= uVar3) {
        uVar15 = uVar14;
      }
      iVar6 = wmemcmp(*(wchar_t **)(pCVar13 + 0x20),local_48[0],uVar15);
      if (iVar6 == 0) {
        lVar17 = uVar3 - uVar14;
        if (0x7fffffff < lVar17) goto LAB_00cd4057;
        if (-0x80000001 < lVar17) {
          iVar6 = (int)lVar17;
          goto LAB_00cd4053;
        }
LAB_00cd409b:
        pCVar12 = *(CSkillManager **)(pCVar13 + 0x18);
      }
      else {
LAB_00cd4053:
        if (iVar6 < 0) goto LAB_00cd409b;
LAB_00cd4057:
        pCVar12 = *(CSkillManager **)(pCVar13 + 0x10);
        local_a0 = pCVar13;
      }
      pCVar13 = pCVar12;
    } while (pCVar13 != (CSkillManager *)0x0);
  }
  paVar18 = (allocator *)(local_48[0] + -6);
  if (pCVar1 == local_a0) {
LAB_00cd40fb:
    local_98 = pCVar1;
  }
  else {
    uVar14 = *(ulong *)paVar18;
    uVar3 = *(ulong *)(*(wchar_t **)(local_a0 + 0x20) + -6);
    uVar15 = uVar14;
    if (uVar3 <= uVar14) {
      uVar15 = uVar3;
    }
    iVar6 = wmemcmp(local_48[0],*(wchar_t **)(local_a0 + 0x20),uVar15);
    local_98 = local_a0;
    if (iVar6 == 0) {
      lVar17 = uVar14 - uVar3;
      if (lVar17 < 0x80000000) {
        if (lVar17 < -0x80000000) goto LAB_00cd40fb;
        iVar6 = (int)lVar17;
        goto LAB_00cd40f7;
      }
    }
    else {
LAB_00cd40f7:
      if (iVar6 < 0) goto LAB_00cd40fb;
    }
  }
  if (paVar18 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    local_48[0] = local_48[0] + -2;
    wVar2 = *local_48[0];
    *local_48[0] = *local_48[0] + L'\xffffffff';
    UNLOCK();
    if (wVar2 < L'\x01') {
      std::wstring::_Rep::_M_destroy(paVar18);
    }
  }
  if (pCVar1 != local_98) {
    if (param_3) {
      uVar7 = *(uint *)(this + 0x68);
      if (uVar7 < *(uint *)(this + 0x6c)) {
        pvVar9 = *(void **)(this + 0x60);
      }
      else if (*(long *)(this + 0x60) == 0) {
        *(uint *)(this + 0x6c) = *(uint *)(this + 0x70);
        pvVar9 = operator_new__((ulong)*(uint *)(this + 0x70) << 3);
        *(void **)(this + 0x60) = pvVar9;
        uVar7 = *(uint *)(this + 0x68);
      }
      else {
        uVar16 = *(uint *)(this + 0x6c) + *(int *)(this + 0x70);
        pvVar9 = operator_new__((ulong)uVar16 << 3);
        if (*(int *)(this + 0x6c) != 0) {
          uVar7 = 0;
          do {
            uVar14 = (ulong)uVar7;
            uVar7 = uVar7 + 1;
            *(undefined8 *)((long)pvVar9 + uVar14 * 8) =
                 *(undefined8 *)(*(long *)(this + 0x60) + uVar14 * 8);
          } while (uVar7 < *(uint *)(this + 0x6c));
        }
        if (*(void **)(this + 0x60) != (void *)0x0) {
          operator_delete__(*(void **)(this + 0x60));
        }
        uVar7 = *(uint *)(this + 0x68);
        *(void **)(this + 0x60) = pvVar9;
        *(uint *)(this + 0x6c) = uVar16;
      }
      *(CSkill **)((long)pvVar9 + (ulong)uVar7 * 8) = this_00;
      *(int *)(this + 0x68) = *(int *)(this + 0x68) + 1;
    }
    goto LAB_00cd4126;
  }
  puVar10 = (undefined8 *)Ogre::NedAllocImpl::allocBytes(0x18,(char *)0x0,0,(char *)0x0);
  *puVar10 = 0;
  *(undefined4 *)(puVar10 + 1) = 0;
  *(undefined4 *)((long)puVar10 + 0xc) = 0;
  *(undefined4 *)(puVar10 + 2) = 1;
  pwVar8 = (wstring_conflict *)CSkill::getName(this_00);
  STRINGS::StringUpper((STRINGS *)local_58,pwVar8);
  pCVar13 = pCVar1;
  if (*(CSkillManager **)(this + 0x28) != (CSkillManager *)0x0) {
    uVar14 = *(ulong *)(local_58[0] + -6);
    pCVar12 = *(CSkillManager **)(this + 0x28);
    do {
      uVar3 = *(ulong *)(*(wchar_t **)(pCVar12 + 0x20) + -6);
      uVar15 = uVar3;
      if (uVar14 <= uVar3) {
        uVar15 = uVar14;
      }
      iVar6 = wmemcmp(*(wchar_t **)(pCVar12 + 0x20),local_58[0],uVar15);
      if (iVar6 == 0) {
        lVar17 = uVar3 - uVar14;
        if (0x7fffffff < lVar17) goto LAB_00cd436f;
        if (-0x80000001 < lVar17) {
          iVar6 = (int)lVar17;
          goto LAB_00cd436b;
        }
LAB_00cd43b3:
        pCVar11 = *(CSkillManager **)(pCVar12 + 0x18);
      }
      else {
LAB_00cd436b:
        if (iVar6 < 0) goto LAB_00cd43b3;
LAB_00cd436f:
        pCVar11 = *(CSkillManager **)(pCVar12 + 0x10);
        pCVar13 = pCVar12;
      }
      pCVar12 = pCVar11;
    } while (pCVar11 != (CSkillManager *)0x0);
  }
                    /* try { // try from 00cd43d8 to 00cd43dc has its CatchHandler @ 00cd4549 */
  if ((pCVar13 == pCVar1) ||
     (iVar6 = std::wstring::compare((wstring_conflict *)local_58), iVar6 < 0)) {
                    /* try { // try from 00cd4486 to 00cd448a has its CatchHandler @ 00cd4549 */
    std::wstring::wstring(local_78,(wstring_conflict *)local_58);
    local_70 = 0;
                    /* try { // try from 00cd449e to 00cd44a2 has its CatchHandler @ 00cd455e */
    pCVar13 = (CSkillManager *)
              std::
              _Rb_tree<std::wstring,std::pair<std::wstring_const,TArrayList<CSkill*>*>,std::_Select1st<std::pair<std::wstring_const,TArrayList<CSkill*>*>>,std::less<std::wstring>,std::allocator<std::pair<std::wstring_const,TArrayList<CSkill*>*>>>
              ::_M_insert_unique_((_Rb_tree<std::wstring,std::pair<std::wstring_const,TArrayList<CSkill*>*>,std::_Select1st<std::pair<std::wstring_const,TArrayList<CSkill*>*>>,std::less<std::wstring>,std::allocator<std::pair<std::wstring_const,TArrayList<CSkill*>*>>>
                                   *)(this + 0x18),pCVar13,local_78);
                    /* try { // try from 00cd44a9 to 00cd44ad has its CatchHandler @ 00cd4549 */
    std::wstring::~wstring(local_78);
  }
  *(undefined8 **)(pCVar13 + 0x28) = puVar10;
  std::wstring::~wstring((wstring_conflict *)local_58);
  pwVar8 = (wstring_conflict *)CSkill::getName(this_00);
  STRINGS::StringUpper((STRINGS *)local_68,pwVar8);
  __s2 = local_68[0];
  local_80 = pCVar1;
  if (*(CSkillManager **)(this + 0x28) != (CSkillManager *)0x0) {
    uVar14 = *(ulong *)(local_68[0] + -6);
    pCVar13 = *(CSkillManager **)(this + 0x28);
    do {
      uVar3 = *(ulong *)(*(wchar_t **)(pCVar13 + 0x20) + -6);
      uVar15 = uVar3;
      if (uVar14 <= uVar3) {
        uVar15 = uVar14;
      }
      iVar6 = wmemcmp(*(wchar_t **)(pCVar13 + 0x20),__s2,uVar15);
      if (iVar6 == 0) {
        lVar17 = uVar3 - uVar14;
        if (0x7fffffff < lVar17) goto LAB_00cd442f;
        if (-0x80000001 < lVar17) {
          iVar6 = (int)lVar17;
          goto LAB_00cd442b;
        }
LAB_00cd4473:
        pCVar12 = *(CSkillManager **)(pCVar13 + 0x18);
      }
      else {
LAB_00cd442b:
        if (iVar6 < 0) goto LAB_00cd4473;
LAB_00cd442f:
        pCVar12 = *(CSkillManager **)(pCVar13 + 0x10);
        local_80 = pCVar13;
      }
      pCVar13 = pCVar12;
    } while (pCVar12 != (CSkillManager *)0x0);
  }
  local_98 = pCVar1;
  if (pCVar1 != local_80) {
    uVar14 = *(ulong *)(local_68[0] + -6);
    uVar3 = *(ulong *)(*(wchar_t **)(local_80 + 0x20) + -6);
    uVar15 = uVar14;
    if (uVar3 <= uVar14) {
      uVar15 = uVar3;
    }
    iVar6 = wmemcmp(local_68[0],*(wchar_t **)(local_80 + 0x20),uVar15);
    if (iVar6 == 0) {
      lVar17 = uVar14 - uVar3;
      if (lVar17 < 0x80000000) {
        if (lVar17 < -0x80000000) goto LAB_00cd4509;
        iVar6 = (int)lVar17;
        goto LAB_00cd44fb;
      }
    }
    else {
LAB_00cd44fb:
      if (iVar6 < 0) goto LAB_00cd4509;
    }
    local_98 = local_80;
  }
LAB_00cd4509:
  std::wstring::~wstring((wstring_conflict *)local_68);
  TArrayList<CSkill*>::add((TArrayList<CSkill*> *)(this + 0x60),this_00);
LAB_00cd4126:
  plVar4 = *(long **)(local_98 + 0x28);
  uVar7 = *(uint *)(plVar4 + 1);
  if (uVar7 < *(uint *)((long)plVar4 + 0xc)) {
    pvVar9 = (void *)*plVar4;
  }
  else if (*plVar4 == 0) {
    *(uint *)((long)plVar4 + 0xc) = *(uint *)(plVar4 + 2);
    pvVar9 = operator_new__((ulong)*(uint *)(plVar4 + 2) << 3);
    *plVar4 = (long)pvVar9;
    uVar7 = *(uint *)(plVar4 + 1);
  }
  else {
    uVar16 = *(uint *)((long)plVar4 + 0xc) + (int)plVar4[2];
    pvVar9 = operator_new__((ulong)uVar16 << 3);
    if (*(int *)((long)plVar4 + 0xc) != 0) {
      uVar7 = 0;
      do {
        uVar14 = (ulong)uVar7;
        uVar7 = uVar7 + 1;
        *(undefined8 *)((long)pvVar9 + uVar14 * 8) = *(undefined8 *)(*plVar4 + uVar14 * 8);
      } while (uVar7 < *(uint *)((long)plVar4 + 0xc));
    }
    if ((void *)*plVar4 != (void *)0x0) {
      operator_delete__((void *)*plVar4);
    }
    uVar7 = *(uint *)(plVar4 + 1);
    *plVar4 = (long)pvVar9;
    *(uint *)((long)plVar4 + 0xc) = uVar16;
  }
  *(CSkill **)((long)pvVar9 + (ulong)uVar7 * 8) = this_00;
  *(int *)(plVar4 + 1) = (int)plVar4[1] + 1;
  *(CSkillManager **)(this_00 + 0x20) = this;
  return this_00;
}



/* address=00cd45c0
   symbol=CSkillManager::executeSkill */

/* WARNING: Removing unreachable block (ram,0x00cd491e) */
/* CSkillManager::executeSkill(std::wstring const&, CBaseUnit*, ESKILL_ACTIVATION_TYPE,
   Ogre::Vector3 const&, Ogre::Quaternion const&, Ogre::Vector3 const&, CBaseUnit*, int) */

CSkill * __thiscall
CSkillManager::executeSkill
          (CSkillManager *this,wstring_conflict *param_1,undefined8 param_2,undefined4 param_4,
          undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,uint param_9)

{
  CSkillManager *pCVar1;
  wchar_t wVar2;
  ulong uVar3;
  ulong uVar4;
  CSkillManager *pCVar5;
  char cVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  long *plVar10;
  CSkill *this_00;
  ulong uVar11;
  long *plVar12;
  CSkillManager *pCVar13;
  CSkill *pCVar14;
  long *plVar15;
  long lVar16;
  CSkillManager *pCVar17;
  allocator *local_70;
  wchar_t *local_48 [3];

  if (m_gDisableSkillFromBeingCasted != '\0') {
    return (CSkill *)0x0;
  }
  STRINGS::StringUpper((STRINGS *)local_48,param_1);
  pCVar13 = *(CSkillManager **)(this + 0x28);
  pCVar1 = this + 0x20;
  pCVar17 = pCVar1;
  if (pCVar13 != (CSkillManager *)0x0) {
    uVar3 = *(ulong *)(local_48[0] + -6);
    do {
      uVar4 = *(ulong *)(*(wchar_t **)(pCVar13 + 0x20) + -6);
      uVar11 = uVar4;
      if (uVar3 <= uVar4) {
        uVar11 = uVar3;
      }
      iVar7 = wmemcmp(*(wchar_t **)(pCVar13 + 0x20),local_48[0],uVar11);
      if (iVar7 == 0) {
        lVar16 = uVar4 - uVar3;
        if (0x7fffffff < lVar16) goto LAB_00cd4647;
        if (-0x80000001 < lVar16) {
          iVar7 = (int)lVar16;
          goto LAB_00cd4643;
        }
LAB_00cd4689:
        pCVar5 = *(CSkillManager **)(pCVar13 + 0x18);
      }
      else {
LAB_00cd4643:
        if (iVar7 < 0) goto LAB_00cd4689;
LAB_00cd4647:
        pCVar5 = *(CSkillManager **)(pCVar13 + 0x10);
        pCVar17 = pCVar13;
      }
      pCVar13 = pCVar5;
    } while (pCVar13 != (CSkillManager *)0x0);
  }
  local_70 = (allocator *)(local_48[0] + -6);
  if (pCVar1 == pCVar17) {
LAB_00cd46e0:
    pCVar17 = pCVar1;
  }
  else {
    uVar3 = *(ulong *)local_70;
    uVar4 = *(ulong *)(*(wchar_t **)(pCVar17 + 0x20) + -6);
    uVar11 = uVar3;
    if (uVar4 <= uVar3) {
      uVar11 = uVar4;
    }
    iVar7 = wmemcmp(local_48[0],*(wchar_t **)(pCVar17 + 0x20),uVar11);
    if (iVar7 == 0) {
      lVar16 = uVar3 - uVar4;
      if (lVar16 < 0x80000000) {
        if (lVar16 < -0x80000000) goto LAB_00cd46e0;
        iVar7 = (int)lVar16;
        goto LAB_00cd4803;
      }
    }
    else {
LAB_00cd4803:
      if (iVar7 < 0) goto LAB_00cd46e0;
    }
  }
  if (local_70 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    local_48[0] = local_48[0] + -2;
    wVar2 = *local_48[0];
    *local_48[0] = *local_48[0] + L'\xffffffff';
    UNLOCK();
    if (wVar2 < L'\x01') {
      std::wstring::_Rep::_M_destroy(local_70);
    }
  }
  if (pCVar1 == pCVar17) {
    return (CSkill *)0x0;
  }
  plVar10 = *(long **)(pCVar17 + 0x28);
  if (*(uint *)(plVar10 + 1) == 0) {
    return (CSkill *)0x0;
  }
  uVar9 = *(uint *)((long)plVar10 + 0xc);
  plVar12 = (long *)*plVar10;
  lVar16 = 0;
  uVar8 = 0;
  pCVar14 = (CSkill *)0x0;
  do {
    plVar15 = (long *)((long)plVar12 + lVar16);
    if (uVar9 <= uVar8) {
      plVar15 = plVar12;
    }
    if (*(char *)(*plVar15 + 100) == '\0') {
      if (uVar8 < uVar9) {
        plVar12 = plVar12 + uVar8;
      }
      this_00 = (CSkill *)*plVar12;
      if (this_00 != (CSkill *)0x0) goto LAB_00cd4766;
      break;
    }
    plVar15 = (long *)((long)plVar12 + lVar16);
    if (uVar9 <= uVar8) {
      plVar15 = plVar12;
    }
    uVar8 = uVar8 + 1;
    lVar16 = lVar16 + 8;
    pCVar14 = (CSkill *)*plVar15;
  } while (uVar8 < *(uint *)(plVar10 + 1));
  if (pCVar14 == (CSkill *)0x0) {
    return (CSkill *)0x0;
  }
  this_00 = (CSkill *)addSkill(this,pCVar14,true,false);
  CSkill::_setLevelOfSkillFromSkillManager(this_00,param_9);
  if (this_00 == (CSkill *)0x0) {
    return (CSkill *)0x0;
  }
LAB_00cd4766:
  cVar6 = CSkill::getIsExclusive(this_00);
  if (cVar6 == '\0') {
    uVar8 = *(uint *)(this + 0x50);
  }
  else {
    if (*(int *)(this + 0x50) == 0) goto LAB_00cd47a8;
    uVar9 = 0;
    do {
      if (uVar9 < *(uint *)(this + 0x54)) {
        plVar10 = (long *)((ulong)uVar9 * 8 + *(long *)(this + 0x48));
      }
      else {
        plVar10 = *(long **)(this + 0x48);
      }
      if (*(long *)(*plVar10 + 0x150) == *(long *)(this_00 + 0x150)) {
        CSkill::stopSkill();
      }
      uVar8 = *(uint *)(this + 0x50);
      uVar9 = uVar9 + 1;
    } while (uVar9 < uVar8);
  }
  if (uVar8 != 0) {
    plVar10 = *(long **)(this + 0x48);
    uVar9 = 0;
    if (this_00 == (CSkill *)*plVar10) {
      return (CSkill *)0x0;
    }
    do {
      uVar9 = uVar9 + 1;
      if (uVar8 <= uVar9) goto LAB_00cd47a8;
      plVar12 = plVar10 + 1;
      plVar10 = plVar10 + 1;
    } while (this_00 != (CSkill *)*plVar12);
    if (uVar9 != 0xffffffff) {
      return (CSkill *)0x0;
    }
  }
LAB_00cd47a8:
  cVar6 = CSkill::startSkill(this_00,param_2,param_4,param_5,param_6,param_7,param_8);
  if (cVar6 == '\0') {
    return (CSkill *)0x0;
  }
  TArrayList<CSkill*>::add((TArrayList<CSkill*> *)(this + 0x48),this_00);
  decrementSkillCharges(this,this_00);
  return this_00;
}



/* address=00cd4930
   symbol=CSkillManager::executeSkill */

/* CSkillManager::executeSkill(CSkill*, CBaseUnit*, ESKILL_ACTIVATION_TYPE, Ogre::Vector3 const&,
   Ogre::Quaternion const&, Ogre::Vector3 const&, CBaseUnit*) */

CSkill * __thiscall
CSkillManager::executeSkill
          (CSkillManager *this,CSkill *param_1,undefined8 param_2,undefined4 param_4,
          undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  long *plVar1;
  undefined4 uVar2;
  char cVar3;
  uint uVar4;
  undefined8 uVar5;
  CSkill *pCVar6;
  ulong uVar7;
  uint uVar8;
  long *plVar9;

  if (param_1 == (CSkill *)0x0) {
    return (CSkill *)0x0;
  }
  if (m_gDisableSkillFromBeingCasted != '\0') {
    return (CSkill *)0x0;
  }
  cVar3 = CSkill::getIsExclusive(param_1);
  if (cVar3 == '\0') {
    uVar8 = *(uint *)(this + 0x50);
  }
  else {
    if (*(int *)(this + 0x50) == 0) goto LAB_00cd49dc;
    uVar7 = 0;
    do {
      if ((uint)uVar7 < *(uint *)(this + 0x54)) {
        plVar9 = (long *)(uVar7 * 8 + *(long *)(this + 0x48));
      }
      else {
        plVar9 = *(long **)(this + 0x48);
      }
      if (*(long *)(*plVar9 + 0x150) == *(long *)(param_1 + 0x150)) {
        CSkill::stopSkill();
      }
      uVar8 = *(uint *)(this + 0x50);
      uVar4 = (uint)uVar7 + 1;
      uVar7 = (ulong)uVar4;
    } while (uVar4 < uVar8);
  }
  if (uVar8 == 0) {
LAB_00cd49dc:
    cVar3 = CSkill::startSkill(param_1,param_2,param_4,param_5,param_6,param_7,param_8);
    if (cVar3 == '\0') {
      return (CSkill *)0x0;
    }
    TArrayList<CSkill*>::add((TArrayList<CSkill*> *)(this + 0x48),param_1);
    decrementSkillCharges(this,param_1);
    return param_1;
  }
  plVar9 = *(long **)(this + 0x48);
  uVar4 = 0;
  if (param_1 != (CSkill *)*plVar9) {
    do {
      uVar4 = uVar4 + 1;
      if (uVar8 <= uVar4) goto LAB_00cd49dc;
      plVar1 = plVar9 + 1;
      plVar9 = plVar9 + 1;
    } while (param_1 != (CSkill *)*plVar1);
    if (uVar4 == 0xffffffff) goto LAB_00cd49dc;
  }
  uVar2 = *(undefined4 *)(param_1 + 0xdc);
  uVar5 = CSkill::getName(param_1);
  pCVar6 = (CSkill *)executeSkill(this,uVar5,param_2,param_4,param_5,param_6,param_7,param_8,uVar2);
  return pCVar6;
}



/* address=00cd4b00
   symbol=CSkillManager::startPassiveSkills */

/* CSkillManager::startPassiveSkills(CBaseUnit*, Ogre::Vector3 const&, Ogre::Quaternion const&,
   Ogre::Vector3 const&) */

void __thiscall
CSkillManager::startPassiveSkills
          (CSkillManager *this,CBaseUnit *param_1,Vector3 *param_2,Quaternion *param_3,
          Vector3 *param_4)

{
  int iVar1;
  CSkill *this_00;
  char cVar2;
  CCharacter *pCVar3;
  undefined8 *puVar4;
  uint uVar5;

  if (*(int *)(this + 0x50) != 0) {
    uVar5 = 0;
    do {
      while (*(uint *)(this + 0x54) <= uVar5) {
        if (*(int *)(**(long **)(this + 0x48) + 0x60) != 4) goto LAB_00cd4b3d;
LAB_00cd4b6b:
        uVar5 = uVar5 + 1;
        CSkill::stopSkill();
        if (*(uint *)(this + 0x50) <= uVar5) goto LAB_00cd4b7b;
      }
      if (*(int *)(*(long *)((ulong)uVar5 * 8 + *(long *)(this + 0x48)) + 0x60) == 4)
      goto LAB_00cd4b6b;
LAB_00cd4b3d:
      uVar5 = uVar5 + 1;
    } while (uVar5 < *(uint *)(this + 0x50));
  }
LAB_00cd4b7b:
  update(this,0.0);
  if (((param_1 != (CBaseUnit *)0x0) &&
      (pCVar3 = (CCharacter *)__dynamic_cast(param_1,&CBaseUnit::typeinfo,&CCharacter::typeinfo,0),
      pCVar3 != (CCharacter *)0x0)) && (*(int *)(this + 0x68) != 0)) {
    uVar5 = 0;
    do {
      while( true ) {
        if (uVar5 < *(uint *)(this + 0x6c)) {
          iVar1 = *(int *)(*(long *)((ulong)uVar5 * 8 + *(long *)(this + 0x60)) + 0x60);
        }
        else {
          iVar1 = *(int *)(**(long **)(this + 0x60) + 0x60);
        }
        if (iVar1 == 4) break;
LAB_00cd4bcd:
        uVar5 = uVar5 + 1;
        if (*(uint *)(this + 0x68) <= uVar5) {
          return;
        }
      }
      if (uVar5 < *(uint *)(this + 0x6c)) {
        puVar4 = (undefined8 *)((ulong)uVar5 * 8 + *(long *)(this + 0x60));
      }
      else {
        puVar4 = *(undefined8 **)(this + 0x60);
      }
      this_00 = (CSkill *)*puVar4;
      CSkill::calculateEffectiveSkillLevel(this_00);
      if (*(int *)(this_00 + 0xe0) == 0) goto LAB_00cd4bcd;
      if (uVar5 < *(uint *)(this + 0x6c)) {
        puVar4 = (undefined8 *)((ulong)uVar5 * 8 + *(long *)(this + 0x60));
      }
      else {
        puVar4 = *(undefined8 **)(this + 0x60);
      }
      cVar2 = CSkill::weaponRequirementsMet((CSkill *)*puVar4,pCVar3);
      if (cVar2 == '\0') goto LAB_00cd4bcd;
      if (uVar5 < *(uint *)(this + 0x6c)) {
        puVar4 = (undefined8 *)((ulong)uVar5 * 8 + *(long *)(this + 0x60));
      }
      else {
        puVar4 = *(undefined8 **)(this + 0x60);
      }
      uVar5 = uVar5 + 1;
      executeSkill(this,*puVar4,param_1,4,param_2,param_3,param_4,param_1);
    } while (uVar5 < *(uint *)(this + 0x68));
  }
  return;
}



/* address=00cd4cd0
   symbol=CSkillManager::setSkillLevel */

/* WARNING: Removing unreachable block (ram,0x00cd5071) */
/* CSkillManager::setSkillLevel(CSkill*, unsigned int) */

void CSkillManager::setSkillLevel(CSkill *param_1,uint param_2)

{
  CSkill *pCVar1;
  wchar_t wVar2;
  size_t __n;
  ulong uVar3;
  CSkill *pCVar4;
  int iVar5;
  undefined8 *puVar6;
  undefined8 *puVar7;
  wstring_conflict *pwVar8;
  uint in_EDX;
  ulong uVar9;
  long *plVar10;
  uint uVar11;
  CSkill *pCVar12;
  ulong uVar13;
  undefined4 in_register_00000034;
  CSkill *this;
  long lVar14;
  CSkill *local_a0;
  allocator *local_90;
  undefined8 local_78 [2];
  undefined8 local_68 [2];
  undefined8 local_58 [2];
  wchar_t *local_48 [3];

  this = (CSkill *)CONCAT44(in_register_00000034,param_2);
  if (((*(int *)(this + 0x60) == 4) && (in_EDX != 0)) && (*(int *)(param_1 + 0x50) != 0)) {
    uVar13 = 0;
    do {
      if ((uint)uVar13 < *(uint *)(param_1 + 0x54)) {
        iVar5 = *(int *)(*(long *)(uVar13 * 8 + *(long *)(param_1 + 0x48)) + 0x60);
      }
      else {
        iVar5 = *(int *)(**(long **)(param_1 + 0x48) + 0x60);
      }
      if (iVar5 == 4) {
        CSkill::stopSkill();
      }
      uVar11 = (uint)uVar13 + 1;
      uVar13 = (ulong)uVar11;
    } while (uVar11 < *(uint *)(param_1 + 0x50));
  }
  if (*(int *)(param_1 + 0x68) != 0) {
    uVar11 = 0;
    do {
      while( true ) {
        if (uVar11 < *(uint *)(param_1 + 0x6c)) {
          puVar7 = (undefined8 *)((ulong)uVar11 * 8 + *(long *)(param_1 + 0x60));
        }
        else {
          puVar7 = *(undefined8 **)(param_1 + 0x60);
        }
        puVar7 = (undefined8 *)CSkill::getName((CSkill *)*puVar7);
        puVar6 = (undefined8 *)CSkill::getName(this);
        __n = *(size_t *)((wchar_t *)*puVar6 + -6);
        if ((__n == *(size_t *)((wchar_t *)*puVar7 + -6)) &&
           (iVar5 = wmemcmp((wchar_t *)*puVar6,(wchar_t *)*puVar7,__n), iVar5 == 0)) break;
        uVar11 = uVar11 + 1;
        if (*(uint *)(param_1 + 0x68) <= uVar11) goto LAB_00cd4d70;
      }
      uVar11 = uVar11 + 1;
      CSkill::_setLevelOfSkillFromSkillManager(this,in_EDX);
    } while (uVar11 < *(uint *)(param_1 + 0x68));
  }
LAB_00cd4d70:
  pwVar8 = (wstring_conflict *)CSkill::getName(this);
  STRINGS::StringUpper((STRINGS *)local_48,pwVar8);
  pCVar12 = *(CSkill **)(param_1 + 0x28);
  pCVar1 = param_1 + 0x20;
  local_a0 = pCVar1;
  if (pCVar12 != (CSkill *)0x0) {
    uVar13 = *(ulong *)(local_48[0] + -6);
    do {
      uVar3 = *(ulong *)(*(wchar_t **)(pCVar12 + 0x20) + -6);
      uVar9 = uVar3;
      if (uVar13 <= uVar3) {
        uVar9 = uVar13;
      }
      iVar5 = wmemcmp(*(wchar_t **)(pCVar12 + 0x20),local_48[0],uVar9);
      if (iVar5 == 0) {
        lVar14 = uVar3 - uVar13;
        if (0x7fffffff < lVar14) goto LAB_00cd4dbf;
        if (-0x80000001 < lVar14) {
          iVar5 = (int)lVar14;
          goto LAB_00cd4dbb;
        }
LAB_00cd4e03:
        pCVar4 = *(CSkill **)(pCVar12 + 0x18);
      }
      else {
LAB_00cd4dbb:
        if (iVar5 < 0) goto LAB_00cd4e03;
LAB_00cd4dbf:
        pCVar4 = *(CSkill **)(pCVar12 + 0x10);
        local_a0 = pCVar12;
      }
      pCVar12 = pCVar4;
    } while (pCVar12 != (CSkill *)0x0);
  }
  local_90 = (allocator *)(local_48[0] + -6);
  if (pCVar1 != local_a0) {
    uVar13 = *(ulong *)local_90;
    uVar3 = *(ulong *)(*(wchar_t **)(local_a0 + 0x20) + -6);
    uVar9 = uVar13;
    if (uVar3 <= uVar13) {
      uVar9 = uVar3;
    }
    iVar5 = wmemcmp(local_48[0],*(wchar_t **)(local_a0 + 0x20),uVar9);
    if (iVar5 == 0) {
      lVar14 = uVar13 - uVar3;
      if (0x7fffffff < lVar14) goto LAB_00cd4e5f;
      if (lVar14 < -0x80000000) goto LAB_00cd4e5a;
      iVar5 = (int)lVar14;
    }
    if (-1 < iVar5) goto LAB_00cd4e5f;
  }
LAB_00cd4e5a:
  local_a0 = pCVar1;
LAB_00cd4e5f:
  if (local_90 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    local_48[0] = local_48[0] + -2;
    wVar2 = *local_48[0];
    *local_48[0] = *local_48[0] + L'\xffffffff';
    UNLOCK();
    if (wVar2 < L'\x01') {
      std::wstring::_Rep::_M_destroy(local_90);
    }
  }
  if ((pCVar1 != local_a0) && (plVar10 = *(long **)(local_a0 + 0x28), (int)plVar10[1] != 0)) {
    uVar11 = 0;
    do {
      if (uVar11 < *(uint *)((long)plVar10 + 0xc)) {
        puVar7 = (undefined8 *)((ulong)uVar11 * 8 + *plVar10);
      }
      else {
        puVar7 = (undefined8 *)*plVar10;
      }
      uVar11 = uVar11 + 1;
      CSkill::_setLevelOfSkillFromSkillManager((CSkill *)*puVar7,in_EDX);
      plVar10 = *(long **)(local_a0 + 0x28);
    } while (uVar11 < *(uint *)(plVar10 + 1));
  }
  if ((*(int *)(this + 0x60) == 4) && (in_EDX != 0)) {
    local_68[0] = CPositionableObject::getPosition(*(CPositionableObject **)(param_1 + 0x88),true);
    local_78[0] = (**(code **)(**(long **)(param_1 + 0x88) + 0xf0))();
    local_58[0] = CPositionableObject::getPosition(*(CPositionableObject **)(param_1 + 0x88),true);
    startPassiveSkills((CSkillManager *)param_1,*(CBaseUnit **)(param_1 + 0x88),(Vector3 *)local_58,
                       (Quaternion *)local_78,(Vector3 *)local_68);
  }
  return;
}



/* address=00cd5090
   symbol=CSkillManager::resetSkillLevels */

/* CSkillManager::resetSkillLevels() */

void __thiscall CSkillManager::resetSkillLevels(CSkillManager *this)

{
  uint uVar1;
  long *plVar2;
  undefined8 *puVar3;
  uint uVar4;

  if (*(int *)(this + 0x68) != 0) {
    uVar4 = 0;
    do {
      uVar1 = *(uint *)(this + 0x6c);
      if (uVar4 < uVar1) {
        plVar2 = (long *)((ulong)uVar4 * 8 + *(long *)(this + 0x60));
      }
      else {
        plVar2 = *(long **)(this + 0x60);
      }
      if ((*(byte *)(*plVar2 + 0x6d) & (*(byte *)(*plVar2 + 0x6b) ^ 1)) != 0) {
        if (uVar4 < uVar1) {
          plVar2 = (long *)((ulong)uVar4 * 8 + *(long *)(this + 0x60));
        }
        else {
          plVar2 = *(long **)(this + 0x60);
        }
        if (*(int *)(*plVar2 + 0x5c) == 0) {
          if (uVar4 < uVar1) {
            puVar3 = (undefined8 *)((ulong)uVar4 * 8 + *(long *)(this + 0x60));
          }
          else {
            puVar3 = *(undefined8 **)(this + 0x60);
          }
          setSkillLevel((CSkill *)this,(uint)*puVar3);
        }
      }
      uVar4 = uVar4 + 1;
    } while (uVar4 < *(uint *)(this + 0x68));
  }
  return;
}



/* address=00cd5140
   symbol=CSkillManager::update */

/* CSkillManager::update(float) */

void __thiscall CSkillManager::update(CSkillManager *this,float param_1)

{
  CSkill *this_00;
  char cVar1;
  uint uVar2;
  undefined8 *puVar3;
  uint uVar4;
  ulong uVar5;

  if (*(int *)(this + 0x50) != 0) {
    uVar5 = 0;
    do {
      while( true ) {
        uVar4 = (uint)uVar5;
        if (uVar4 < *(uint *)(this + 0x54)) {
          puVar3 = (undefined8 *)(uVar5 * 8 + *(long *)(this + 0x48));
        }
        else {
          puVar3 = *(undefined8 **)(this + 0x48);
        }
        this_00 = (CSkill *)*puVar3;
        CSkill::updateSkill(this_00,param_1);
        if ((this_00[100] != (CSkill)0x0) || (0.0 < *(float *)(this_00 + 0xfc))) break;
        CSkill::stopSkill();
        if (uVar4 < *(uint *)(this + 0x50)) {
          uVar2 = *(uint *)(this + 0x50) - 1;
          *(uint *)(this + 0x50) = uVar2;
          *(undefined8 *)(*(long *)(this + 0x48) + uVar5 * 8) =
               *(undefined8 *)(*(long *)(this + 0x48) + (ulong)uVar2 * 8);
        }
        uVar4 = uVar4 - 1;
        attemptDeleteOfSkill(this,this_00);
LAB_00cd51be:
        uVar5 = (ulong)(uVar4 + 1);
        if (*(uint *)(this + 0x50) <= uVar4 + 1) {
          return;
        }
      }
      if ((*(int *)(this_00 + 0x60) != 4) ||
         (cVar1 = CSkill::calculateEffectiveSkillLevel(this_00), cVar1 == '\0')) goto LAB_00cd51be;
      uVar5 = (ulong)(uVar4 + 1);
      setSkillLevel((CSkill *)this,(uint)this_00);
    } while (uVar4 + 1 < *(uint *)(this + 0x50));
  }
  return;
}



/* address=00cd5220
   symbol=CSkillManager::setSkillLevel */

/* CSkillManager::setSkillLevel(std::wstring const&, unsigned int) */

void CSkillManager::setSkillLevel(wstring_conflict *param_1,uint param_2)

{
  uint uVar1;
  undefined4 in_register_00000034;

  uVar1 = getSkill((CSkillManager *)param_1,
                   (wstring_conflict *)CONCAT44(in_register_00000034,param_2));
  setSkillLevel((CSkill *)param_1,uVar1);
  return;
}



/* address=00cd5260
   symbol=CSkillManager::fireSkillsOnDeath */

/* CSkillManager::fireSkillsOnDeath(CBaseUnit*, ESKILL_ACTIVATION_TYPE, Ogre::Vector3 const&,
   Ogre::Quaternion const&, Ogre::Vector3 const&, CCharacter*) */

void __thiscall
CSkillManager::fireSkillsOnDeath
          (CSkillManager *this,undefined8 param_1,undefined4 param_3,undefined8 param_4,
          undefined8 param_5,long param_6,undefined8 param_7)

{
  char cVar1;
  int iVar2;
  undefined8 *puVar3;
  long lVar4;
  uint uVar5;

  if (*(int *)(this + 0x68) != 0) {
    uVar5 = 0;
    do {
      while( true ) {
        if (uVar5 < *(uint *)(this + 0x6c)) {
          puVar3 = (undefined8 *)((ulong)uVar5 * 8 + *(long *)(this + 0x60));
        }
        else {
          puVar3 = *(undefined8 **)(this + 0x60);
        }
        cVar1 = CSkill::hasEvent((CSkill *)*puVar3,9);
        if (cVar1 != '\0') break;
LAB_00cd533f:
        uVar5 = uVar5 + 1;
        if (*(uint *)(this + 0x68) <= uVar5) goto LAB_00cd53e7;
      }
      if (uVar5 < *(uint *)(this + 0x6c)) {
        iVar2 = CSkill::getTargetType(*(CSkill **)((ulong)uVar5 * 8 + *(long *)(this + 0x60)));
      }
      else {
        iVar2 = CSkill::getTargetType((CSkill *)**(undefined8 **)(this + 0x60));
      }
      if (iVar2 != 1) {
        if (uVar5 < *(uint *)(this + 0x6c)) {
          puVar3 = (undefined8 *)((ulong)uVar5 * 8 + *(long *)(this + 0x60));
        }
        else {
          puVar3 = *(undefined8 **)(this + 0x60);
        }
        iVar2 = CSkill::getTargetType((CSkill *)*puVar3);
        if (iVar2 != 5) {
          if (uVar5 < *(uint *)(this + 0x6c)) {
            puVar3 = (undefined8 *)((ulong)uVar5 * 8 + *(long *)(this + 0x60));
          }
          else {
            puVar3 = *(undefined8 **)(this + 0x60);
          }
          iVar2 = CSkill::getTargetType((CSkill *)*puVar3);
          if (iVar2 != 6) {
            if (uVar5 < *(uint *)(this + 0x6c)) {
              puVar3 = (undefined8 *)((ulong)uVar5 * 8 + *(long *)(this + 0x60));
            }
            else {
              puVar3 = *(undefined8 **)(this + 0x60);
            }
            executeSkill(this,*puVar3,param_1,param_3,param_4,param_5,param_6,param_7);
            goto LAB_00cd533f;
          }
        }
      }
      if (uVar5 < *(uint *)(this + 0x6c)) {
        puVar3 = (undefined8 *)((ulong)uVar5 * 8 + *(long *)(this + 0x60));
      }
      else {
        puVar3 = *(undefined8 **)(this + 0x60);
      }
      lVar4 = getPositionForSkill(this,(CSkill *)*puVar3,(CBaseUnit *)0x0);
      if (lVar4 == 0) {
        lVar4 = param_6;
      }
      if (uVar5 < *(uint *)(this + 0x6c)) {
        puVar3 = (undefined8 *)((ulong)uVar5 * 8 + *(long *)(this + 0x60));
      }
      else {
        puVar3 = *(undefined8 **)(this + 0x60);
      }
      param_7 = 0;
      uVar5 = uVar5 + 1;
      executeSkill(this,*puVar3,param_1,param_3,param_4,param_5,lVar4,0);
    } while (uVar5 < *(uint *)(this + 0x68));
  }
LAB_00cd53e7:
  triggerSkillEvent(this,9,param_4,param_5,param_7);
  return;
}



/* address=00cd5460
   symbol=CSkillManager::fireSkillsOnCreate */

/* CSkillManager::fireSkillsOnCreate(CBaseUnit*, ESKILL_ACTIVATION_TYPE, Ogre::Vector3 const&,
   Ogre::Quaternion const&, Ogre::Vector3 const&, CCharacter*) */

void __thiscall
CSkillManager::fireSkillsOnCreate
          (CSkillManager *this,undefined8 param_1,undefined4 param_3,undefined8 param_4,
          undefined8 param_5,undefined8 param_6,undefined8 param_7)

{
  char cVar1;
  undefined8 *puVar2;
  uint uVar3;

  uVar3 = 0;
  if (*(int *)(this + 0x68) != 0) {
    do {
      if (uVar3 < *(uint *)(this + 0x6c)) {
        puVar2 = (undefined8 *)((ulong)uVar3 * 8 + *(long *)(this + 0x60));
      }
      else {
        puVar2 = *(undefined8 **)(this + 0x60);
      }
      cVar1 = CSkill::hasEvent((CSkill *)*puVar2,10);
      if (cVar1 != '\0') {
        if (uVar3 < *(uint *)(this + 0x6c)) {
          puVar2 = (undefined8 *)((ulong)uVar3 * 8 + *(long *)(this + 0x60));
        }
        else {
          puVar2 = *(undefined8 **)(this + 0x60);
        }
        executeSkill(this,*puVar2,param_1,param_3,param_4,param_5,param_6,param_7);
      }
      uVar3 = uVar3 + 1;
    } while (uVar3 < *(uint *)(this + 0x68));
  }
  triggerSkillEvent(this,10,param_4,param_5,param_7);
  return;
}



/* address=00cd5530
   symbol=CSkillManager::addSkill */

/* WARNING: Removing unreachable block (ram,0x00cd56cb) */
/* CSkillManager::addSkill(std::wstring const&, bool) */

undefined8 __thiscall
CSkillManager::addSkill(CSkillManager *this,wstring_conflict *param_1,bool param_2)

{
  CSkillManager *pCVar1;
  wchar_t wVar2;
  ulong uVar3;
  ulong uVar4;
  CSkillManager *pCVar5;
  int iVar6;
  CSkill *pCVar7;
  undefined8 uVar8;
  ulong uVar9;
  CSkillManager *pCVar10;
  long lVar11;
  CSkillManager *pCVar12;
  allocator *local_60;
  wchar_t *local_48 [3];

  if (param_2) goto LAB_00cd5660;
  STRINGS::StringUpper((STRINGS *)local_48,param_1);
  pCVar10 = *(CSkillManager **)(this + 0x28);
  pCVar1 = this + 0x20;
  pCVar12 = pCVar1;
  if (pCVar10 != (CSkillManager *)0x0) {
    uVar3 = *(ulong *)(local_48[0] + -6);
    do {
      uVar4 = *(ulong *)(*(wchar_t **)(pCVar10 + 0x20) + -6);
      uVar9 = uVar4;
      if (uVar3 <= uVar4) {
        uVar9 = uVar3;
      }
      iVar6 = wmemcmp(*(wchar_t **)(pCVar10 + 0x20),local_48[0],uVar9);
      if (iVar6 == 0) {
        lVar11 = uVar4 - uVar3;
        if (0x7fffffff < lVar11) goto LAB_00cd5597;
        if (-0x80000001 < lVar11) {
          iVar6 = (int)lVar11;
          goto LAB_00cd5593;
        }
LAB_00cd55d9:
        pCVar5 = *(CSkillManager **)(pCVar10 + 0x18);
      }
      else {
LAB_00cd5593:
        if (iVar6 < 0) goto LAB_00cd55d9;
LAB_00cd5597:
        pCVar5 = *(CSkillManager **)(pCVar10 + 0x10);
        pCVar12 = pCVar10;
      }
      pCVar10 = pCVar5;
    } while (pCVar10 != (CSkillManager *)0x0);
  }
  local_60 = (allocator *)(local_48[0] + -6);
  if (pCVar1 == pCVar12) {
LAB_00cd562a:
    pCVar12 = pCVar1;
  }
  else {
    uVar3 = *(ulong *)local_60;
    uVar4 = *(ulong *)(*(wchar_t **)(pCVar12 + 0x20) + -6);
    uVar9 = uVar3;
    if (uVar4 <= uVar3) {
      uVar9 = uVar4;
    }
    iVar6 = wmemcmp(local_48[0],*(wchar_t **)(pCVar12 + 0x20),uVar9);
    if (iVar6 == 0) {
      lVar11 = uVar3 - uVar4;
      if (lVar11 < 0x80000000) {
        if (lVar11 < -0x80000000) goto LAB_00cd562a;
        iVar6 = (int)lVar11;
        goto LAB_00cd5626;
      }
    }
    else {
LAB_00cd5626:
      if (iVar6 < 0) goto LAB_00cd562a;
    }
  }
  if (local_60 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    local_48[0] = local_48[0] + -2;
    wVar2 = *local_48[0];
    *local_48[0] = *local_48[0] + L'\xffffffff';
    UNLOCK();
    if (wVar2 < L'\x01') {
      std::wstring::_Rep::_M_destroy(local_60);
    }
  }
  if (pCVar1 != pCVar12) {
    return *(undefined8 *)**(undefined8 **)(pCVar12 + 0x28);
  }
LAB_00cd5660:
  pCVar7 = (CSkill *)CSkillParser::getSkill(*(CResourceManager **)(this + 0x10),param_1);
  uVar8 = 0;
  if (pCVar7 != (CSkill *)0x0) {
    uVar8 = addSkill(this,pCVar7,false,param_2);
  }
  return uVar8;
}



/* export-summary functions=44 failures=0 */
