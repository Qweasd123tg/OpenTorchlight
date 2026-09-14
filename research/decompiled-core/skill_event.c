/* Targeted Ghidra class export.
   namespace=CSkillEvent
   Treat pseudocode as navigation evidence. */


/* address=00cb6fa0
   symbol=CSkillEvent::canAffixesAndEffectsBeAppliedToUnit */

/* CSkillEvent::canAffixesAndEffectsBeAppliedToUnit(CBaseUnit*, CCharacter*) */

undefined8 __thiscall
CSkillEvent::canAffixesAndEffectsBeAppliedToUnit
          (CSkillEvent *this,CBaseUnit *param_1,CCharacter *param_2)

{
  undefined8 uVar1;

  if (*(CSkillEffectAndAffixes **)(this + 0xa0) != (CSkillEffectAndAffixes *)0x0) {
    uVar1 = CSkillEffectAndAffixes::canAffixesAndEffectsBeAppliedToUnit
                      (*(CSkillEffectAndAffixes **)(this + 0xa0),param_1,param_2);
    return uVar1;
  }
  return 1;
}



/* address=00cb6fc0
   symbol=CSkillEvent::addMinAndMaxValuesOfAnEffect */

/* CSkillEvent::addMinAndMaxValuesOfAnEffect(CResourceManager*, unsigned int, float&, float&) */

void __thiscall
CSkillEvent::addMinAndMaxValuesOfAnEffect
          (CSkillEvent *this,CResourceManager *param_1,uint param_2,float *param_3,float *param_4)

{
  float fVar1;
  float fVar2;
  CRunicCore *this_00;
  uint uVar3;
  undefined4 uVar4;
  CEquipment *this_01;
  CEquipment *this_02;
  CCharacter *this_03;
  char cVar5;
  float local_2c;

  if (*(CSkillEffectAndAffixes **)(this + 0xa0) != (CSkillEffectAndAffixes *)0x0) {
    CSkillEffectAndAffixes::addMinAndMaxValuesOfAnEffect
              (*(CSkillEffectAndAffixes **)(this + 0xa0),param_1,param_2,param_3,param_4);
  }
  fVar1 = *(float *)(this + 0x150);
  if (fVar1 <= DAT_00fa47f8) {
    return;
  }
  this_03 = *(CCharacter **)(this + 0x70);
  if (this_03 == (CCharacter *)0x0) {
    this_03 = (CCharacter *)CSkill::getMasterOwnerCharacter(*(CSkill **)(this + 0x28));
    this_00 = *(CRunicCore **)(this + 0x70);
    if (this_03 != (CCharacter *)this_00) {
      if (this_00 != (CRunicCore *)0x0) {
        CRunicCore::removeSafePointer(this_00,(TSafePointer *)(this + 0x70),*(uint *)(this + 0x78));
      }
      *(undefined8 *)(this + 0x70) = 0;
      if (this_03 != (CCharacter *)0x0) {
        uVar4 = CRunicCore::addSafePointer((CRunicCore *)this_03,(TSafePointer *)(this + 0x70));
        *(undefined4 *)(this + 0x78) = uVar4;
      }
      *(CCharacter **)(this + 0x70) = this_03;
    }
    if (this_03 == (CCharacter *)0x0) {
      return;
    }
  }
  this_02 = (CEquipment *)0x0;
  this_01 = (CEquipment *)CCharacter::getWeaponInRightHand(this_03);
  if (*(CCharacter **)(this + 0x70) != (CCharacter *)0x0) {
    this_02 = (CEquipment *)CCharacter::getWeaponInLeftHand(*(CCharacter **)(this + 0x70));
  }
  cVar5 = '\0';
  if (*(long *)(this + 0x90) != 0) {
    cVar5 = *(char *)(*(long *)(this + 0x90) + 0xb0);
  }
  if (this_01 == (CEquipment *)0x0) {
    if (this_02 == (CEquipment *)0x0) goto LAB_00cb70b6;
    fVar2 = *param_3;
    uVar3 = CEquipment::minimumDamage(this_02);
    *param_3 = (float)uVar3 * fVar1 + fVar2;
    local_2c = *param_4;
    this_01 = this_02;
  }
  else {
    fVar2 = *param_3;
    uVar3 = CEquipment::minimumDamage(this_01);
    *param_3 = (float)uVar3 * fVar1 + fVar2;
    local_2c = *param_4;
  }
  uVar3 = CEquipment::maximumDamage(this_01);
  *param_4 = (float)uVar3 * fVar1 + local_2c;
LAB_00cb70b6:
  if ((cVar5 != '\0') && (this_02 != (CEquipment *)0x0)) {
    fVar2 = *param_3;
    uVar3 = CEquipment::minimumDamage(this_02);
    *param_3 = (float)uVar3 * fVar1 + fVar2;
    fVar2 = *param_4;
    uVar3 = CEquipment::maximumDamage(this_02);
    *param_4 = (float)uVar3 * fVar1 + fVar2;
  }
  return;
}



/* address=00cb71e0
   symbol=CSkillEvent::getDisplayStats */

/* CSkillEvent::getDisplayStats(CSkillProperty*) */

CSkillProperty * CSkillEvent::getDisplayStats(CSkillProperty *param_1)

{
  long in_RDX;
  long in_RSI;

  if (((*(long *)(in_RSI + 0xa0) != 0) && (*(char *)(in_RSI + 0x13b) == '\0')) &&
     ((in_RDX != 0 || ((*(long *)(in_RSI + 0x90) != 0 || (*(long *)(in_RSI + 0x98) != 0)))))) {
    CSkillEffectAndAffixes::getDisplayStats();
    return param_1;
  }
  std::wstring::wstring((wstring_conflict *)param_1,(wstring_conflict *)&::EMPTY_WSTRING);
  return param_1;
}



/* address=00cb7240
   symbol=CSkillEvent::canEffectPosObject */

/* CSkillEvent::canEffectPosObject(Ogre::Vector3 const&, CPositionableObject*) */

bool __thiscall
CSkillEvent::canEffectPosObject(CSkillEvent *this,Vector3 *param_1,CPositionableObject *param_2)

{
  float fVar1;
  float extraout_XMM0_Db;

  fVar1 = *(float *)(param_1 + 4);
  CPositionableObject::getPosition(param_2,true);
  return (float)((uint)(fVar1 - extraout_XMM0_Db) & DAT_00fa8790) <= DAT_00fa86d4;
}



/* address=00cb7290
   symbol=CSkillEvent::invokeHitSkills */

/* CSkillEvent::invokeHitSkills(CCharacter*) */

void CSkillEvent::invokeHitSkills(CCharacter *param_1)

{
  int iVar1;
  undefined8 uVar2;
  CPositionableObject *in_RSI;
  undefined8 local_38 [2];
  undefined8 local_28 [2];

  if ((in_RSI != (CPositionableObject *)0x0) || (*(long *)(param_1 + 0x28) != 0)) {
    if (*(int *)(param_1 + 0x48) != 4) {
      uVar2 = (**(code **)(**(long **)(in_RSI + 0x58) + 200))();
      local_28[0] = CPositionableObject::getPosition(in_RSI,true);
      CSkill::triggerEvent(*(CSkill **)(param_1 + 0x28),4,local_28,uVar2);
    }
    iVar1 = CCharacter::HP((CCharacter *)in_RSI);
    if ((iVar1 < 1) && (*(int *)(param_1 + 0x48) != 5)) {
      uVar2 = (**(code **)(**(long **)(in_RSI + 0x58) + 200))();
      local_38[0] = CPositionableObject::getPosition(in_RSI,true);
      CSkill::triggerEvent(*(CSkill **)(param_1 + 0x28),5,local_38,uVar2);
    }
  }
  return;
}



/* address=00cb73b0
   symbol=CSkillEvent::getCharacterCanBeHarmedByMissile */

/* non-virtual thunk to CSkillEvent::getCharacterCanBeHarmedByMissile(CMissile*, CCharacter*) */

void __thiscall
CSkillEvent::getCharacterCanBeHarmedByMissile
          (CSkillEvent *this,CMissile *param_1,CCharacter *param_2)

{
  getCharacterCanBeHarmedByMissile(this + -0x18,param_1,param_2);
  return;
}



/* address=00cb73c0
   symbol=CSkillEvent::getCharacterCanBeHarmedByMissile */

/* CSkillEvent::getCharacterCanBeHarmedByMissile(CMissile*, CCharacter*) */

CMissile __thiscall
CSkillEvent::getCharacterCanBeHarmedByMissile
          (CSkillEvent *this,CMissile *param_1,CCharacter *param_2)

{
  char cVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  CCharacter *this_00;
  long *plVar5;
  long lVar6;
  CSkillProperty *this_01;

  this_00 = (CCharacter *)CSkill::getMasterOwnerCharacter(*(CSkill **)(this + 0x28));
  if ((this_00 == (CCharacter *)0x0) && (*(long *)(param_1 + 0x220) != 0)) {
    this_00 = (CCharacter *)
              __dynamic_cast(*(long *)(param_1 + 0x220),&CBaseUnit::typeinfo,&CCharacter::typeinfo,0
                            );
  }
  if ((this[0x14f] == (CSkillEvent)0x0) || (param_2 != this_00)) {
    if (param_2 == (CCharacter *)0x0) {
      return (CMissile)0x0;
    }
    if (*(long *)(this + 0x90) == 0) {
      return (CMissile)0x0;
    }
    if (this[0x14d] == (CSkillEvent)0x0) {
      iVar3 = CCharacter::HP(param_2);
      if (iVar3 < 1) {
        return (CMissile)0x0;
      }
    }
    else {
      iVar3 = CCharacter::HP(param_2);
      if (0 < iVar3) {
        return (CMissile)0x0;
      }
    }
    this_01 = *(CSkillProperty **)(this + 0x90);
    if ((this_01[0xb4] != (CSkillProperty)0x0) && (param_2 != *(CCharacter **)(this + 0x80))) {
      if (param_1 == (CMissile *)0x0) {
        return (CMissile)0x0;
      }
      if (param_1[0x294] == (CMissile)0x0) {
        return (CMissile)0x0;
      }
    }
    if (this_00 == (CCharacter *)0x0) {
      this_00 = (CCharacter *)CSkillProperty::getOwnerCharacter(this_01);
      if (this_00 == (CCharacter *)0x0) {
        return (CMissile)0x1;
      }
      this_01 = *(CSkillProperty **)(this + 0x90);
    }
    if ((*(int *)(this_01 + 0x74) == 0) ||
       (cVar1 = CBaseUnit::ISA((CBaseUnit *)param_2), cVar1 != '\0')) {
      if (*(uint *)(this + 0xe0) == 0) {
LAB_00cb7530:
        if (*(int *)(*(long *)(this + 0x90) + 0x70) == 4) {
          return (CMissile)0x1;
        }
        iVar3 = CSkill::getTargetType(*(CSkill **)(this + 0x28));
        if (((((iVar3 != 10) || (param_2 == this_00)) ||
             (this_00 == *(CCharacter **)(param_2 + 0x640))) ||
            ((*(CCharacter **)(this_00 + 0x640) != (CCharacter *)0x0 &&
             (param_2 == *(CCharacter **)(this_00 + 0x640))))) &&
           ((iVar3 = CSkill::getTargetType(*(CSkill **)(this + 0x28)), iVar3 != 9 ||
            (this_00 == *(CCharacter **)(param_2 + 0x640))))) {
          cVar1 = CCharacter::isEnemy(this_00,param_2);
          if (*(long *)(this_00 + 0x718) == 0) {
            return (CMissile)0x1;
          }
          cVar2 = CAIManager::hasAIFlag(*(long *)(this_00 + 0x718),1);
          if (cVar2 != '\0') {
            return (CMissile)0x1;
          }
          iVar3 = CCharacter::alignment(this_00);
          if (iVar3 == 4) {
            return (CMissile)0x1;
          }
          if (*(int *)(*(long *)(this + 0x90) + 0x50) == 2) {
            if (cVar1 != '\0') {
              return (CMissile)0x1;
            }
          }
          else if ((*(int *)(*(long *)(this + 0x90) + 0x50) == 1) && (cVar1 == '\0')) {
            return (CMissile)0x1;
          }
          if (param_1 != (CMissile *)0x0) {
            return param_1[0x294];
          }
        }
      }
      else {
        lVar6 = 0;
        uVar4 = 0;
        do {
          if (uVar4 < *(uint *)(this + 0xe4)) {
            plVar5 = (long *)(lVar6 + *(long *)(this + 0xd8));
          }
          else {
            plVar5 = *(long **)(this + 0xd8);
          }
          if (*plVar5 == *(long *)(param_2 + 0x1b0)) goto LAB_00cb7530;
          uVar4 = uVar4 + 1;
          lVar6 = lVar6 + 8;
        } while (uVar4 < *(uint *)(this + 0xe0));
      }
    }
  }
  else if (param_2 != (CCharacter *)0x0) {
    return (CMissile)0x1;
  }
  return (CMissile)0x0;
}



/* address=00cb7660
   symbol=CSkillEvent::missileDieing */

/* non-virtual thunk to CSkillEvent::missileDieing(CMissile*) */

void __thiscall CSkillEvent::missileDieing(CSkillEvent *this,CMissile *param_1)

{
  missileDieing((CMissile *)(this + -0x18));
  return;
}



/* address=00cb7670
   symbol=CSkillEvent::missileDieing */

/* CSkillEvent::missileDieing(CMissile*) */

void CSkillEvent::missileDieing(CMissile *param_1)

{
  TSafePointer *pTVar1;
  long *plVar2;
  undefined8 uVar3;
  long *plVar4;
  uint uVar5;
  uint uVar6;
  ulong uVar7;
  CPositionableObject *in_RSI;
  undefined8 local_38 [3];

  if (*(int *)(param_1 + 0xf8) != 0) {
    uVar7 = 0;
    do {
      while( true ) {
        uVar5 = *(uint *)(param_1 + 0xfc);
        uVar6 = (uint)uVar7;
        if (uVar6 < uVar5) break;
        plVar2 = *(long **)(param_1 + 0xf0);
        if (*(long *)*plVar2 != 0) goto LAB_00cb76ab;
LAB_00cb76f1:
        plVar4 = plVar2;
        if (uVar6 < uVar5) {
          plVar4 = plVar2 + uVar7;
        }
        if (*plVar4 != 0) {
          plVar4 = plVar2;
          if (uVar6 < uVar5) {
            plVar4 = plVar2 + uVar7;
          }
          pTVar1 = (TSafePointer *)*plVar4;
          if (pTVar1 != (TSafePointer *)0x0) {
            if (*(CRunicCore **)pTVar1 != (CRunicCore *)0x0) {
                    /* try { // try from 00cb772a to 00cb772e has its CatchHandler @ 00cb7814 */
              CRunicCore::removeSafePointer(*(CRunicCore **)pTVar1,pTVar1,*(uint *)(pTVar1 + 8));
            }
            *(undefined8 *)pTVar1 = 0;
            *(undefined4 *)(pTVar1 + 8) = 0xffffffff;
            Ogre::NedAllocImpl::deallocBytes(pTVar1);
            uVar5 = *(uint *)(param_1 + 0xfc);
            plVar2 = *(long **)(param_1 + 0xf0);
          }
          if (uVar6 < uVar5) {
            plVar2 = plVar2 + uVar7;
          }
          *plVar2 = 0;
        }
        uVar5 = *(uint *)(param_1 + 0xf8);
        if (uVar6 < uVar5) {
          *(uint *)(param_1 + 0xf8) = uVar5 - 1;
          *(undefined8 *)(*(long *)(param_1 + 0xf0) + uVar7 * 8) =
               *(undefined8 *)(*(long *)(param_1 + 0xf0) + (ulong)(uVar5 - 1) * 8);
          uVar5 = *(uint *)(param_1 + 0xf8);
        }
        if (uVar5 <= uVar6) goto LAB_00cb77a0;
      }
      plVar2 = *(long **)(param_1 + 0xf0);
      if (*(long *)plVar2[uVar7] == 0) goto LAB_00cb76f1;
LAB_00cb76ab:
      plVar4 = plVar2;
      if (uVar6 < uVar5) {
        plVar4 = plVar2 + uVar7;
      }
      if (in_RSI == *(CPositionableObject **)*plVar4) goto LAB_00cb76f1;
      uVar7 = (ulong)(uVar6 + 1);
    } while (uVar6 + 1 < *(uint *)(param_1 + 0xf8));
  }
LAB_00cb77a0:
  if ((*(long *)(param_1 + 0x28) != 0) && (*(int *)(param_1 + 0x48) != 7)) {
    uVar3 = (**(code **)(**(long **)(in_RSI + 0x58) + 200))();
    local_38[0] = CPositionableObject::getPosition(in_RSI,true);
    CSkill::triggerEvent(*(CSkill **)(param_1 + 0x28),7,local_38,uVar3,0,0);
  }
  return;
}



/* address=00cb7820
   symbol=CSkillEvent::effectsTargetEnemy */

/* CSkillEvent::effectsTargetEnemy(CBaseUnit*) */

undefined8 __thiscall CSkillEvent::effectsTargetEnemy(CSkillEvent *this,CBaseUnit *param_1)

{
  undefined8 uVar1;
  CSkillEffectAndAffixes *this_00;

  if ((*(long *)(this + 0x90) != 0) &&
     ((this_00 = *(CSkillEffectAndAffixes **)(this + 0xa0), this_00 != (CSkillEffectAndAffixes *)0x0
      || (this_00 = *(CSkillEffectAndAffixes **)(*(long *)(this + 0x90) + 0x20),
         this_00 != (CSkillEffectAndAffixes *)0x0)))) {
    uVar1 = CSkillEffectAndAffixes::effectsTargetEnemy(this_00,param_1);
    return uVar1;
  }
  return 0;
}



/* address=00cb7850
   symbol=CSkillEvent::applyEffects */

/* CSkillEvent::applyEffects(CBaseUnit*, Ogre::Vector3 const*, bool) */

uint CSkillEvent::applyEffects(CBaseUnit *param_1,Vector3 *param_2,bool param_3)

{
  float fVar1;
  char cVar2;
  byte bVar3;
  char cVar4;
  uint uVar5;
  int iVar6;
  CCharacter *this;
  CCharacter *pCVar7;
  CPositionableObject *this_00;
  bool in_CL;
  undefined7 in_register_00000011;
  CBaseUnit *pCVar8;
  undefined8 uVar9;
  float in_XMM1_Da;
  float fVar10;
  uint local_b8;
  float local_88;
  float local_84;
  float local_80;
  undefined8 local_78;
  float local_68;
  float local_64;
  float local_60;
  Vector3 local_58 [16];
  Vector3 local_48 [24];

  if ((*(long *)(param_1 + 0x90) == 0) || (param_2 == (Vector3 *)0x0)) {
    return 0;
  }
  cVar2 = '\x01';
  this = (CCharacter *)__dynamic_cast(param_2,&CBaseUnit::typeinfo,&CCharacter::typeinfo);
  if (this != (CCharacter *)0x0) {
    cVar2 = CCharacter::alive(this);
  }
  if (param_1[0x14a] == (CBaseUnit)0x0) {
    if (*(long *)(param_1 + 0xa0) == 0) goto LAB_00cb7ad0;
LAB_00cb78e0:
    pCVar7 = (CCharacter *)CSkill::getMasterOwnerCharacter(*(CSkill **)(param_1 + 0x28));
    bVar3 = CSkillEffectAndAffixes::applyAffixesAndEffects
                      (*(CSkillEffectAndAffixes **)(param_1 + 0xa0),(CBaseUnit *)param_2,pCVar7,
                       (Vector3 *)CONCAT71(in_register_00000011,param_3),in_CL);
    CSkill::getMasterOwnerCharacter(*(CSkill **)(param_1 + 0x28));
    pCVar8 = *(CBaseUnit **)(param_1 + 0xa0);
  }
  else {
    local_78 = CPositionableObject::getPosition((CPositionableObject *)param_2,true);
    fVar1 = DAT_00fa47fc;
    fVar10 = (float)((ulong)local_78 >> 0x20) + DAT_00fa47fc;
    local_68 = (float)local_78 + 0.0;
    local_60 = in_XMM1_Da + 0.0;
    local_64 = fVar10;
    this_00 = (CPositionableObject *)CSkill::getMasterOwner(*(CSkill **)(param_1 + 0x28));
    uVar9 = CPositionableObject::getPosition(this_00,true);
    local_84 = fVar1 + (float)((ulong)uVar9 >> 0x20);
    local_88 = (float)uVar9 + 0.0;
    local_80 = fVar10 + 0.0;
    cVar4 = CLevel::rayCollision
                      (*(CLevel **)(*(long *)(param_1 + 0x30) + 0x18),(Vector3 *)&local_88,
                       (Vector3 *)&local_68,local_48,local_58,true);
    if (cVar4 != '\0') {
      return 1;
    }
    if (*(long *)(param_1 + 0xa0) != 0) goto LAB_00cb78e0;
LAB_00cb7ad0:
    local_b8 = 0;
    if (*(long *)(*(long *)(param_1 + 0x90) + 0x20) == 0) goto LAB_00cb7928;
    pCVar7 = (CCharacter *)CSkill::getMasterOwnerCharacter(*(CSkill **)(param_1 + 0x28));
    bVar3 = CSkillEffectAndAffixes::applyAffixesAndEffects
                      (*(CSkillEffectAndAffixes **)(*(long *)(param_1 + 0x90) + 0x20),
                       (CBaseUnit *)param_2,pCVar7,(Vector3 *)CONCAT71(in_register_00000011,param_3)
                       ,in_CL);
    CSkill::getMasterOwnerCharacter(*(CSkill **)(param_1 + 0x28));
    pCVar8 = *(CBaseUnit **)(*(long *)(param_1 + 0x90) + 0x20);
  }
  local_b8 = (uint)bVar3;
  uVar5 = CSkillEffectAndAffixes::removeAffixesAndEffects(pCVar8,(CCharacter *)param_2);
  local_b8 = local_b8 | uVar5;
LAB_00cb7928:
  uVar5 = local_b8;
  if (this != (CCharacter *)0x0) {
    CCharacter::updateEffects(0.0,(CLevel *)this);
    uVar5 = local_b8 & 0xff;
    if (cVar2 == '\0') {
      iVar6 = CCharacter::HP(this);
      uVar5 = local_b8 & 0xff;
      if (0 < iVar6) {
        (**(code **)(*(long *)this + 0x348))(this,2);
        uVar5 = local_b8 & 0xff;
      }
    }
  }
  return uVar5;
}



/* address=00cb7b70
   symbol=CSkillEvent::applyWeaponDamage */

/* CSkillEvent::applyWeaponDamage(CCharacter*, CItem*, float, float, bool, bool) */

undefined8 __thiscall
CSkillEvent::applyWeaponDamage
          (CSkillEvent *this,CCharacter *param_1,CItem *param_2,float param_3,float param_4,
          bool param_5,bool param_6)

{
  float fVar1;
  undefined4 uVar2;
  CCharacter *pCVar3;
  uint uVar4;
  char cVar5;
  uint uVar6;
  int iVar7;
  CBaseUnit *pCVar8;
  CBaseUnit *pCVar9;
  undefined8 uVar10;
  CPositionableObject *this_00;
  CBaseUnit *pCVar11;
  CItem *pCVar12;
  undefined8 uVar13;
  float fVar14;
  float fVar15;
  undefined8 local_d8;
  float local_d0;
  undefined8 local_c8;
  float local_c0;
  float local_b8;
  float local_b4;
  float local_b0;
  undefined8 local_a8;
  float local_a0;
  float local_98;
  float local_94;
  float local_90;
  float local_88;
  float local_84;
  float local_80;
  float local_78;
  float local_74;
  float local_70;
  undefined8 local_68;
  float local_60;
  undefined8 local_58;
  float local_50;
  undefined8 local_48;
  float local_40;

  if ((((*(long *)(this + 0x90) == 0) ||
       (*(CPositionableObject **)(this + 0x60) == (CPositionableObject *)0x0)) ||
      (*(float *)(this + 0x150) == 0.0)) ||
     (((!param_6 && (*(char *)(*(long *)(this + 0x90) + 0xb4) != '\0')) &&
      (param_1 != *(CCharacter **)(this + 0x80))))) {
    return 0;
  }
  this_00 = *(CPositionableObject **)(this + 0x60);
  if (*(CPositionableObject **)(this + 0x70) != (CPositionableObject *)0x0) {
    this_00 = *(CPositionableObject **)(this + 0x70);
  }
  fVar14 = param_4;
  if (!param_5) {
    pCVar12 = (CItem *)param_1;
    if (param_1 == (CCharacter *)0x0) {
      pCVar12 = param_2;
    }
    local_48 = CPositionableObject::getPosition(this_00,true);
    local_40 = fVar14;
    cVar5 = canEffectPosObject(this,(Vector3 *)&local_48,(CPositionableObject *)pCVar12);
    if (cVar5 == '\0') {
      return 0;
    }
  }
  if (this[0x14a] != (CSkillEvent)0x0) {
    if (param_1 == (CCharacter *)0x0) {
      if (param_2 == (CItem *)0x0) goto LAB_00cb7c9d;
      local_a8 = CPositionableObject::getPosition((CPositionableObject *)param_2,true);
      fVar1 = DAT_00fa47fc;
      fVar15 = (float)((ulong)local_a8 >> 0x20) + DAT_00fa47fc;
      local_98 = (float)local_a8 + 0.0;
      local_90 = fVar14 + 0.0;
      local_a0 = fVar14;
      local_94 = fVar15;
      local_c8 = CPositionableObject::getPosition(this_00,true);
      local_b4 = fVar1 + (float)((ulong)local_c8 >> 0x20);
      local_b8 = (float)local_c8 + 0.0;
      local_b0 = fVar15 + 0.0;
      local_c0 = fVar15;
      cVar5 = CLevel::rayCollision
                        (*(CLevel **)(*(long *)(this + 0x30) + 0x18),(Vector3 *)&local_b8,
                         (Vector3 *)&local_98,(Vector3 *)&local_78,(Vector3 *)&local_88,true);
      fVar14 = fVar15;
    }
    else {
      local_58 = CPositionableObject::getPosition((CPositionableObject *)param_1,true);
      fVar1 = DAT_00fa47fc;
      fVar15 = (float)((ulong)local_58 >> 0x20) + DAT_00fa47fc;
      local_88 = (float)local_58 + 0.0;
      local_80 = fVar14 + 0.0;
      local_84 = fVar15;
      local_50 = fVar14;
      local_68 = CPositionableObject::getPosition(this_00,true);
      local_74 = fVar1 + (float)((ulong)local_68 >> 0x20);
      local_78 = (float)local_68 + 0.0;
      local_70 = fVar15 + 0.0;
      local_60 = fVar15;
      cVar5 = CLevel::rayCollision
                        (*(CLevel **)(*(long *)(this + 0x30) + 0x18),(Vector3 *)&local_78,
                         (Vector3 *)&local_88,(Vector3 *)&local_b8,(Vector3 *)&local_98,true);
      fVar14 = fVar15;
    }
    if (cVar5 != '\0') {
      return 1;
    }
  }
LAB_00cb7c9d:
  if (*(CEffectManager **)(this_00 + 0x1b8) != (CEffectManager *)0x0) {
    CEffectManager::calculateEffectValues(*(CEffectManager **)(this_00 + 0x1b8));
  }
  pCVar3 = *(CCharacter **)(this_00 + 0x340);
  pCVar12 = *(CItem **)(this_00 + 0x350);
  if (param_1 != (CCharacter *)0x0) {
    CCharacter::setTarget((CCharacter *)this_00,param_1);
  }
  if (param_2 != (CItem *)0x0) {
    CCharacter::setTargetItem((CCharacter *)this_00,param_2);
  }
  pCVar8 = (CBaseUnit *)CCharacter::getWeaponInRightHand((CCharacter *)this_00);
  pCVar9 = (CBaseUnit *)CCharacter::getWeaponInLeftHand((CCharacter *)this_00);
  uVar6 = (-(uint)!param_5 & 0xfffffd00) + 0x30f;
  if (this[0x144] != (CSkillEvent)0x0) {
    uVar6 = uVar6 | 0x400;
  }
  if (this[0x145] != (CSkillEvent)0x0) {
    uVar6 = uVar6 | 0x800;
  }
  uVar4 = uVar6 | 0x1000;
  if (this[0x146] == (CSkillEvent)0x0) {
    uVar4 = uVar6;
  }
  cVar5 = *(char *)(*(long *)(this + 0x90) + 0xb0);
  if (pCVar8 == (CBaseUnit *)0x0) {
    uVar13 = 0;
    if (pCVar9 != (CBaseUnit *)0x0) {
      if (param_1 != (CCharacter *)0x0) {
        uVar2 = *(undefined4 *)(this + 0x17c);
        fVar1 = *(float *)(this + 0x150);
        fVar14 = *(float *)(this + 0x154);
        pCVar11 = pCVar9;
        goto LAB_00cb7d93;
      }
      uVar13 = 1;
      (**(code **)(*(long *)param_2 + 0x280))(param_2,*(undefined8 *)(this + 0x70));
    }
  }
  else if (param_1 == (CCharacter *)0x0) {
    uVar13 = 1;
    (**(code **)(*(long *)param_2 + 0x280))(param_2,*(undefined8 *)(this + 0x70));
  }
  else {
    uVar2 = *(undefined4 *)(this + 0x17c);
    fVar1 = *(float *)(this + 0x150);
    fVar14 = *(float *)(this + 0x154);
    pCVar11 = pCVar8;
LAB_00cb7d93:
    fVar14 = param_4 * fVar14;
    uVar13 = 1;
    CCharacter::performAttack((CCharacter *)(param_3 * fVar1),this_00,pCVar11,uVar4 | 0x10,uVar2);
  }
  if (((cVar5 == '\0') || (param_5)) || (param_1 == (CCharacter *)0x0)) {
LAB_00cb7dce:
    if (pCVar9 != (CBaseUnit *)0x0) goto LAB_00cb7dd7;
  }
  else if (pCVar9 != (CBaseUnit *)0x0) {
    cVar5 = CBaseUnit::ISA(pCVar9,8);
    if ((cVar5 != '\0') &&
       ((*(long *)(this + 0x90) == 0 ||
        (cVar5 = CBaseUnit::ISA(pCVar9,*(undefined4 *)(*(long *)(this + 0x90) + 0x14)),
        cVar5 != '\0')))) {
      fVar14 = param_4 * *(float *)(this + 0x154);
      uVar13 = 1;
      CCharacter::performAttack
                ((CCharacter *)(param_3 * *(float *)(this + 0x150)),this_00,pCVar9,uVar4 | 0x10,
                 *(undefined4 *)(this + 0x17c));
      goto LAB_00cb7dd7;
    }
    goto LAB_00cb7dce;
  }
  if (pCVar8 == (CBaseUnit *)0x0) {
    fVar14 = param_4 * *(float *)(this + 0x154);
    uVar13 = 1;
    CCharacter::performAttack
              ((CCharacter *)(param_3 * *(float *)(this + 0x150)),this_00,0,uVar4 | 0x50,
               *(undefined4 *)(this + 0x17c));
  }
LAB_00cb7dd7:
  if (*(CEffectManager **)(this_00 + 0x1b8) != (CEffectManager *)0x0) {
    CEffectManager::calculateEffectValues(*(CEffectManager **)(this_00 + 0x1b8));
  }
  if ((((param_1 != (CCharacter *)0x0) && (iVar7 = CCharacter::HP(param_1), iVar7 < 1)) &&
      (*(long *)(param_1 + 0x58) != 0)) &&
     ((cVar5 = CBaseUnit::ISA((CBaseUnit *)param_1,0x1d), cVar5 != '\0' &&
      (*(int *)(this + 0x48) != 5)))) {
    uVar10 = (**(code **)(**(long **)(param_1 + 0x58) + 200))();
    local_d8 = CPositionableObject::getPosition((CPositionableObject *)param_1,true);
    local_d0 = fVar14;
    CSkill::triggerEvent(*(CSkill **)(this + 0x28),5,&local_d8,uVar10,param_1,0);
  }
  CCharacter::setTarget((CCharacter *)this_00,pCVar3);
  if (pCVar12 != (CItem *)0x0) {
    CCharacter::setTargetItem((CCharacter *)this_00,pCVar12);
  }
  return uVar13;
}



/* address=00cb8350
   symbol=CSkillEvent::missileApplyingEffects */

/* non-virtual thunk to CSkillEvent::missileApplyingEffects(CMissile*, CCharacter*, Ogre::Vector3
   const*, float, float) */

void __thiscall
CSkillEvent::missileApplyingEffects
          (CSkillEvent *this,CMissile *param_1,CCharacter *param_2,Vector3 *param_3,float param_4,
          float param_5)

{
  missileApplyingEffects(this + -0x18,param_1,param_2,param_3,param_4,param_5);
  return;
}



/* address=00cb8360
   symbol=CSkillEvent::missileApplyingEffects */

/* CSkillEvent::missileApplyingEffects(CMissile*, CCharacter*, Ogre::Vector3 const*, float, float)
    */

uint __thiscall
CSkillEvent::missileApplyingEffects
          (CSkillEvent *this,CMissile *param_1,CCharacter *param_2,Vector3 *param_3,float param_4,
          float param_5)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  undefined8 uVar4;
  CMissile CVar5;
  float fVar6;
  undefined8 local_48;
  float local_40;
  undefined8 local_38;
  float local_30;

  fVar6 = param_5;
  local_38 = CPositionableObject::getPosition((CPositionableObject *)param_1,true);
  local_30 = fVar6;
  cVar1 = canEffectPosObject(this,(Vector3 *)&local_38,(CPositionableObject *)param_2);
  if (cVar1 == '\0') {
    return 0;
  }
  if (*(long *)(this + 0x28) != 0) {
    CVar5 = (CMissile)0x1;
    if ((param_1[0x294] != (CMissile)0x0) || (CVar5 = (CMissile)0x0, *(int *)(this + 0x48) == 6))
    goto LAB_00cb83f6;
    uVar4 = (**(code **)(**(long **)(param_1 + 0x58) + 200))();
    local_48 = CPositionableObject::getPosition((CPositionableObject *)param_1,true);
    local_40 = fVar6;
    CSkill::triggerEvent(*(CSkill **)(this + 0x28),6,&local_48,uVar4,param_2,0);
  }
  CVar5 = param_1[0x294];
LAB_00cb83f6:
  uVar2 = applyWeaponDamage(this,param_2,(CItem *)0x0,param_4,param_5,true,(bool)CVar5);
  uVar3 = applyEffects((CBaseUnit *)this,(Vector3 *)param_2,SUB81(param_3,0));
  invokeHitSkills((CCharacter *)this);
  return uVar2 | uVar3;
}



/* address=00cb84e0
   symbol=CSkillEvent::itemEffectedByDamageShape */

/* non-virtual thunk to CSkillEvent::itemEffectedByDamageShape(CDamageShape*, CItem*) */

void __thiscall
CSkillEvent::itemEffectedByDamageShape(CSkillEvent *this,CDamageShape *param_1,CItem *param_2)

{
  itemEffectedByDamageShape((CDamageShape *)(this + -0x10),(CItem *)param_1);
  return;
}



/* address=00cb84f0
   symbol=CSkillEvent::itemEffectedByDamageShape */

/* CSkillEvent::itemEffectedByDamageShape(CDamageShape*, CItem*) */

undefined4 CSkillEvent::itemEffectedByDamageShape(CDamageShape *param_1,CItem *param_2)

{
  char cVar1;
  undefined4 uVar2;
  CPositionableObject *in_RDX;
  CSkillEffectAndAffixes *this;
  undefined8 local_28 [2];

  uVar2 = 0;
  local_28[0] = CPositionableObject::getPosition((CPositionableObject *)param_2,true);
  cVar1 = canEffectPosObject((CSkillEvent *)param_1,(Vector3 *)local_28,in_RDX);
  if (cVar1 != '\0') {
    uVar2 = applyWeaponDamage((CSkillEvent *)param_1,(CCharacter *)0x0,(CItem *)in_RDX,DAT_00fa47fc,
                              DAT_00fa47fc,false,false);
    this = *(CSkillEffectAndAffixes **)(param_1 + 0xa0);
    if (((this != (CSkillEffectAndAffixes *)0x0) ||
        (this = *(CSkillEffectAndAffixes **)(*(long *)(param_1 + 0x90) + 0x20),
        this != (CSkillEffectAndAffixes *)0x0)) &&
       (cVar1 = CSkillEffectAndAffixes::isDamaging(this), cVar1 != '\0')) {
      uVar2 = 1;
    }
  }
  return uVar2;
}



/* address=00cb85d0
   symbol=CSkillEvent::shouldStop */

/* CSkillEvent::shouldStop() */

undefined8 __thiscall CSkillEvent::shouldStop(CSkillEvent *this)

{
  char cVar1;
  int iVar2;
  undefined8 *puVar3;
  uint uVar4;

  if (((*(int *)(this + 0xf8) != 0) || (DAT_00fa47f8 < *(float *)(this + 0x15c))) ||
     (*(int *)(*(long *)(this + 0x28) + 0x60) == 4)) {
    return 0;
  }
  if (*(CEditorScene **)(this + 0x38) != (CEditorScene *)0x0) {
    iVar2 = CEditorScene::getNumberOfTimelinesUpdating(*(CEditorScene **)(this + 0x38),true);
    if (iVar2 != 0) {
      return 0;
    }
    iVar2 = (**(code **)(**(long **)(this + 0x38) + 0x220))();
    if (iVar2 != 0) {
      return 0;
    }
    if (*(int *)(*(long *)(this + 0x28) + 0xec) != -1) {
      return 0;
    }
    if (*(int *)(this + 200) != 0) {
      uVar4 = 0;
      do {
        if (uVar4 < *(uint *)(this + 0xcc)) {
          puVar3 = (undefined8 *)((ulong)uVar4 * 8 + *(long *)(this + 0xc0));
        }
        else {
          puVar3 = *(undefined8 **)(this + 0xc0);
        }
        cVar1 = CUnitSpawner::getParticlesStillVisible((CUnitSpawner *)*puVar3);
        if (cVar1 != '\0') {
          return 0;
        }
        uVar4 = uVar4 + 1;
      } while (uVar4 < *(uint *)(this + 200));
    }
  }
  return 1;
}



/* address=00cb86c0
   symbol=CSkillEvent::canStop */

/* CSkillEvent::canStop() */

undefined8 __thiscall CSkillEvent::canStop(CSkillEvent *this)

{
  char cVar1;
  int iVar2;
  undefined8 *puVar3;
  uint uVar4;

  if (*(float *)(this + 0x15c) <= DAT_00fa47f8) {
    if ((*(CEditorScene **)(this + 0x38) == (CEditorScene *)0x0) ||
       (*(int *)(*(long *)(this + 0x28) + 0xec) != -1)) {
      return 1;
    }
    iVar2 = CEditorScene::getNumberOfTimelinesUpdating(*(CEditorScene **)(this + 0x38),true);
    if ((iVar2 == 0) && (iVar2 = (**(code **)(**(long **)(this + 0x38) + 0x220))(), iVar2 == 0)) {
      if (*(int *)(this + 200) == 0) {
        return 1;
      }
      uVar4 = 0;
      while( true ) {
        if (uVar4 < *(uint *)(this + 0xcc)) {
          puVar3 = (undefined8 *)((ulong)uVar4 * 8 + *(long *)(this + 0xc0));
        }
        else {
          puVar3 = *(undefined8 **)(this + 0xc0);
        }
        cVar1 = CUnitSpawner::getParticlesStillVisible((CUnitSpawner *)*puVar3);
        if (cVar1 != '\0') break;
        uVar4 = uVar4 + 1;
        if (*(uint *)(this + 200) <= uVar4) {
          return 1;
        }
      }
      return 0;
    }
  }
  return 0;
}



/* address=00cb87a0
   symbol=CSkillEvent::getBonePosition */

/* CSkillEvent::getBonePosition(CBaseUnit*, ESKILL_BONE_ATTACHMENT, bool) */

undefined8 __thiscall
CSkillEvent::getBonePosition
          (CSkillEvent *this,CPositionableObject *param_1,int param_3,char param_4)

{
  float fVar1;
  float fVar2;
  long lVar3;
  float *pfVar4;
  long *plVar5;
  undefined8 uVar6;
  float local_54;
  float local_50;
  float local_28;
  float fStack_24;

  fVar1 = DAT_014241b0;
  local_50 = Ogre::Vector3::ZERO;
  if (param_1 == (CPositionableObject *)0x0) goto LAB_00cb8a00;
  local_54 = DAT_014241b0;
  if (param_4 != '\0') {
    uVar6 = CPositionableObject::getPosition(param_1,true);
    local_28 = (float)uVar6;
    local_50 = local_50 + local_28;
    fStack_24 = (float)((ulong)uVar6 >> 0x20);
    local_54 = (fVar1 + fStack_24) - *(float *)(param_1 + 0x194);
  }
  lVar3 = 0;
  if (((*(long *)(this + 0x50) == 0) ||
      (lVar3 = __dynamic_cast(*(long *)(this + 0x50),&CBaseUnit::typeinfo,&CCharacter::typeinfo,0),
      lVar3 == 0)) && (param_3 == 0)) {
    pfVar4 = (float *)(**(code **)(*(long *)param_1 + 0xa0))(param_1);
    fVar1 = *pfVar4;
switchD_00cb89e3_caseD_1:
    lVar3 = (**(code **)(*(long *)param_1 + 0x1e0))(param_1);
    if ((lVar3 != 0) &&
       (lVar3 = (**(code **)(*(long *)param_1 + 0x1e0))(param_1), *(long *)(lVar3 + 0x60) != 0)) {
      (**(code **)(*(long *)param_1 + 0x1e0))(param_1);
      lVar3 = Ogre::Entity::getMesh();
      if (*(long *)(lVar3 + 8) != 0) {
        (**(code **)(*(long *)param_1 + 0x1e0))(param_1);
        Ogre::Entity::getMesh();
        lVar3 = Ogre::Mesh::getBounds();
        fVar2 = *(float *)(lVar3 + 0x10);
        (**(code **)(*(long *)param_1 + 0x1e0))(param_1);
        Ogre::Entity::getMesh();
        lVar3 = Ogre::Mesh::getBounds();
        local_50 = local_50 + 0.0;
        local_54 = (float)((uint)((fVar2 - *(float *)(lVar3 + 4)) * DAT_00fa4810) & DAT_00fa8790) *
                   fVar1 + local_54;
      }
    }
    goto switchD_00cb89e3_caseD_0;
  }
  pfVar4 = (float *)(**(code **)(*(long *)param_1 + 0xa0))(param_1);
  fVar1 = *pfVar4;
  switch(param_3) {
  default:
    goto switchD_00cb89e3_caseD_0;
  case 1:
    goto switchD_00cb89e3_caseD_1;
  case 2:
    plVar5 = *(long **)(lVar3 + 0x318);
    break;
  case 3:
    plVar5 = *(long **)(lVar3 + 0x2e8);
    goto joined_r0x00cb8aa3;
  case 4:
    plVar5 = *(long **)(lVar3 + 0x2f8);
    break;
  case 5:
    plVar5 = *(long **)(lVar3 + 0x310);
joined_r0x00cb8aa3:
    if (plVar5 == (long *)0x0) {
      local_54 = DAT_014241b0;
      local_50 = Ogre::Vector3::ZERO;
      goto switchD_00cb89e3_caseD_0;
    }
    goto LAB_00cb8a3d;
  case 6:
    plVar5 = *(long **)(lVar3 + 0x308);
  }
  if (plVar5 == (long *)0x0) {
LAB_00cb8a00:
    local_54 = DAT_014241b0;
    local_50 = Ogre::Vector3::ZERO;
  }
  else {
LAB_00cb8a3d:
    pfVar4 = (float *)(**(code **)(*plVar5 + 0xf8))();
    local_54 = pfVar4[1] * fVar1 + local_54;
    local_50 = fVar1 * *pfVar4 + local_50;
  }
switchD_00cb89e3_caseD_0:
  return CONCAT44(local_54,local_50);
}



/* address=00cb8b10
   symbol=CSkillEvent::missileValidateTargetBeforeLaunch */

/* non-virtual thunk to CSkillEvent::missileValidateTargetBeforeLaunch(CMissile*,
   CPositionableObject*, Ogre::Vector3&) */

void __thiscall
CSkillEvent::missileValidateTargetBeforeLaunch
          (CSkillEvent *this,CMissile *param_1,CPositionableObject *param_2,Vector3 *param_3)

{
  missileValidateTargetBeforeLaunch
            ((CMissile *)(this + -0x18),(CPositionableObject *)param_1,(Vector3 *)param_2);
  return;
}



/* address=00cb8b20
   symbol=CSkillEvent::missileValidateTargetBeforeLaunch */

/* CSkillEvent::missileValidateTargetBeforeLaunch(CMissile*, CPositionableObject*, Ogre::Vector3&)
    */

Vector3 * CSkillEvent::missileValidateTargetBeforeLaunch
                    (CMissile *param_1,CPositionableObject *param_2,Vector3 *param_3)

{
  CSkill *this;
  int iVar1;
  Vector3 *pVVar2;
  undefined4 *in_RCX;
  undefined8 uVar3;
  undefined4 in_XMM1_Da;
  undefined4 local_48;
  undefined4 uStack_44;
  undefined4 local_38;
  undefined4 uStack_34;

  if (param_1[0x14f] == (CMissile)0x0) {
    if (*(CSkill **)(param_1 + 0x28) != (CSkill *)0x0) {
      iVar1 = CSkill::getTargetType(*(CSkill **)(param_1 + 0x28));
      if (iVar1 == 0) goto LAB_00cb8c30;
      this = *(CSkill **)(param_1 + 0x28);
      if ((((this != (CSkill *)0x0) && (*(long *)(this + 0x40) != 0)) &&
          (iVar1 = CSkill::getTargetType(this), iVar1 != 1)) &&
         (iVar1 = CSkill::getTargetType(*(CSkill **)(param_1 + 0x28)), iVar1 != 0xb)) {
        uVar3 = CPositionableObject::getPosition
                          (*(CPositionableObject **)(*(long *)(param_1 + 0x28) + 0x40),true);
        local_48 = (undefined4)uVar3;
        *in_RCX = local_48;
        uStack_44 = (undefined4)((ulong)uVar3 >> 0x20);
        in_RCX[1] = uStack_44;
        in_RCX[2] = in_XMM1_Da;
        return *(Vector3 **)(*(long *)(param_1 + 0x28) + 0x40);
      }
    }
    *in_RCX = *(undefined4 *)(param_1 + 0x1f0);
    in_RCX[1] = *(undefined4 *)(param_1 + 500);
    in_RCX[2] = *(undefined4 *)(param_1 + 0x1f8);
  }
  else {
    pVVar2 = (Vector3 *)CSkill::getOwnerCharacter(*(CSkill **)(param_1 + 0x28));
    if (pVVar2 != (Vector3 *)0x0) {
      uVar3 = getBonePosition((CSkillEvent *)param_1,pVVar2,1,1);
      local_38 = (undefined4)uVar3;
      *in_RCX = local_38;
      uStack_34 = (undefined4)((ulong)uVar3 >> 0x20);
      in_RCX[1] = uStack_34;
      in_RCX[2] = in_XMM1_Da;
      param_2[0x144] = (CPositionableObject)0x1;
      return pVVar2;
    }
LAB_00cb8c30:
    param_3 = (Vector3 *)0x0;
  }
  return param_3;
}



/* address=00cc0cc0
   symbol=CSkillEvent::_GLOBAL__I_CSkillEvent */

/* CSkillEvent::CSkillEvent(CSkill*, CSkillProperty*, CResourceManager*, CDataGroup*) */

void CSkillEvent::_GLOBAL__I_CSkillEvent(void)

{
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
  std::string::string((string *)::KLayoutFunctionNames,"GUIEXITGAME",&aStack_2ee);
  std::string::string((string *)(::KLayoutFunctionNames + 8),"GUIEXITAPPLICATION",&aStack_2ed);
  std::string::string((string *)(::KLayoutFunctionNames + 0x10),"GUINEWGAME",&aStack_2ec);
  std::string::string((string *)(::KLayoutFunctionNames + 0x18),"GUICONTINUEGAME",&aStack_2eb);
  std::string::string((string *)(::KLayoutFunctionNames + 0x20),"GUINEWGAMEMENU",&aStack_2ea);
  std::string::string((string *)(::KLayoutFunctionNames + 0x28),"GUICONTINUEGAMEMENU",&aStack_2e9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x30),"GUICLOSEMENU",&aStack_2e8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x38),"GUIBACK",&aStack_2e7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x40),"GUIDECLINE",&aStack_2e6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x48),"GUIACCEPT",&aStack_2e5);
  std::string::string((string *)(::KLayoutFunctionNames + 0x50),"GUIOK",&aStack_2e4);
  std::string::string((string *)(::KLayoutFunctionNames + 0x58),"GUIPAUSE",&aStack_2e3);
  std::string::string((string *)(::KLayoutFunctionNames + 0x60),"GUISCROLLUP",&aStack_2e2);
  std::string::string((string *)(::KLayoutFunctionNames + 0x68),"GUISCROLLDOWN",&aStack_2e1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x70),"GUISELECT1",&aStack_2e0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x78),"GUISELECT2",&aStack_2df);
  std::string::string((string *)(::KLayoutFunctionNames + 0x80),"GUISELECT3",&aStack_2de);
  std::string::string((string *)(::KLayoutFunctionNames + 0x88),"GUISELECT4",&aStack_2dd);
  std::string::string((string *)(::KLayoutFunctionNames + 0x90),"GUISELECT5",&aStack_2dc);
  std::string::string((string *)(::KLayoutFunctionNames + 0x98),"GUISELECT6",&aStack_2db);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa0),"GUISELECT7",&aStack_2da);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa8),"GUISELECT8",&aStack_2d9);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb0),"GUISELECT9",&aStack_2d8);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb8),"GUISELECT10",&aStack_2d7);
  std::string::string((string *)(::KLayoutFunctionNames + 0xc0),"GUISELECT11",&aStack_2d6);
  std::string::string((string *)(::KLayoutFunctionNames + 200),"GUISELECT12",&aStack_2d5);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd0),"GUISELECT13",&aStack_2d4);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd8),"GUISELECT14",&aStack_2d3);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe0),"GUISELECT15",&aStack_2d2);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe8),"GUISELECT16",&aStack_2d1);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf0),"GUISELECT17",&aStack_2d0);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf8),"GUISELECT18",&aStack_2cf);
  std::string::string((string *)(::KLayoutFunctionNames + 0x100),"GUISELECT19",&aStack_2ce);
  std::string::string((string *)(::KLayoutFunctionNames + 0x108),"GUISELECT20",&aStack_2cd);
  std::string::string((string *)(::KLayoutFunctionNames + 0x110),"GUISELECT21",&aStack_2cc);
  std::string::string((string *)(::KLayoutFunctionNames + 0x118),"GUISELECT22",&aStack_2cb);
  std::string::string((string *)(::KLayoutFunctionNames + 0x120),"GUISELECT23",&aStack_2ca);
  std::string::string((string *)(::KLayoutFunctionNames + 0x128),"GUISELECT24",&aStack_2c9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x130),"GUISELECT25",&aStack_2c8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x138),"GUISELECT26",&aStack_2c7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x140),"GUISELECT27",&aStack_2c6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x148),"GUISELECT28",&aStack_2c5);
  std::string::string((string *)(::KLayoutFunctionNames + 0x150),"GUISELECT29",&aStack_2c4);
  std::string::string((string *)(::KLayoutFunctionNames + 0x158),"GUISELECT30",&aStack_2c3);
  std::string::string((string *)(::KLayoutFunctionNames + 0x160),"GUISELECT31",&aStack_2c2);
  std::string::string((string *)(::KLayoutFunctionNames + 0x168),"GUISELECT32",&aStack_2c1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x170),"GUISELECT33",&aStack_2c0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x178),"GUISELECT34",&aStack_2bf);
  std::string::string((string *)(::KLayoutFunctionNames + 0x180),"GUISELECT35",&aStack_2be);
  std::string::string((string *)(::KLayoutFunctionNames + 0x188),"GUISELECT36",&aStack_2bd);
  std::string::string((string *)(::KLayoutFunctionNames + 400),"GUISELECT37",&aStack_2bc);
  std::string::string((string *)(::KLayoutFunctionNames + 0x198),"GUISELECT38",&aStack_2bb);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a0),"GUISELECT39",&aStack_2ba);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a8),"GUISELECT40",&aStack_2b9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b0),"GUISELECT41",&aStack_2b8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b8),"GUISELECT42",&aStack_2b7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c0),"GUISELECT43",&aStack_2b6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c8),"GUISELECT44",&aStack_2b5);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d0),"GUISELECT45",&aStack_2b4);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d8),"GUISELECT46",&aStack_2b3);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e0),"GUISELECT47",&aStack_2b2);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e8),"GUISELECT48",&aStack_2b1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f0),"GUISELECT49",&aStack_2b0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f8),"GUISELECT50",&aStack_2af);
  std::string::string((string *)(::KLayoutFunctionNames + 0x200),"GUISELECTA",&aStack_2ae);
  std::string::string((string *)(::KLayoutFunctionNames + 0x208),"GUISELECTB",&aStack_2ad);
  std::string::string((string *)(::KLayoutFunctionNames + 0x210),"GUISELECTC",&aStack_2ac);
  std::string::string((string *)(::KLayoutFunctionNames + 0x218),"GUISELECTD",&aStack_2ab);
  std::string::string((string *)(::KLayoutFunctionNames + 0x220),"GUIFEEDPET",&aStack_2aa);
  std::string::string((string *)(::KLayoutFunctionNames + 0x228),"GUIPETPASSIVE",&aStack_2a9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x230),"GUIPETAGGRESSIVE",&aStack_2a8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x238),"GUIPETDEFENSIVE",&aStack_2a7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x240),"GUITOGGLEINVENTORY",&aStack_2a6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x248),"GUITOGGLEQUESTS",&aStack_2a5);
  std::string::string((string *)(::KLayoutFunctionNames + 0x250),"GUITOGGLESTATS",&aStack_2a4);
  std::string::string((string *)(::KLayoutFunctionNames + 600),"GUITOGGLESKILLS",&aStack_2a3);
  std::string::string((string *)(::KLayoutFunctionNames + 0x260),"GUITOGGLEPERKS",&aStack_2a2);
  std::string::string((string *)(::KLayoutFunctionNames + 0x268),"GUITOGGLEJOURNAL",&aStack_2a1);
  std::string::string((string *)(::KLayoutFunctionNames + 0x270),"GUITOGGLEPET",&aStack_2a0);
  std::string::string((string *)(::KLayoutFunctionNames + 0x278),"GUITOGGLEAUTOMAP",&aStack_29f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x280),"GUITOGGLEOPTIONS",&aStack_29e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x288),"GUITOGGLEITEMNAMES",&aStack_29d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x290),"GUIAUTOMAPZOOMIN",&aStack_29c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x298),"GUIAUTOMAPZOOMOUT",&aStack_29b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a0),"GUILEVELUP",&aStack_29a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a8),"GUISTATSUP",&aStack_299);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b0),"GUISKILLUP",&aStack_298);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b8),"GUIPET1",&aStack_297);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c0),"GUIPET2",&aStack_296);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c8),"GUIPET3",&aStack_295);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d0),"GUIDELETE1",&aStack_294);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d8),"GUIDELETE2",&aStack_293);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e0),"GUIDELETE3",&aStack_292);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e8),"GUIDELETE4",&aStack_291);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f0),"GUISETTINGSMENU",&aStack_290);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f8),"GUIPETSELL",&aStack_28f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x300),"NONE",&aStack_28e);
  __cxa_atexit(::__tcf_0,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSOUNDBANK_STRINGS,L"STEP_SOUND",&aStack_28d);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 8),L"STRIKE_SOUND",&aStack_28c);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x10),L"PHYSICALHIT_SOUND",&aStack_28b);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x18),L"ICEHIT_SOUND",&aStack_28a);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x20),L"FIREHIT_SOUND",&aStack_289);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x28),L"ELECTRICHIT_SOUND",&aStack_288);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x30),L"POISONHIT_SOUND",&aStack_287);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x38),L"SHIELDBLOCK",&aStack_286);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x40),L"BLOCK",&aStack_285);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x48),L"CRITICAL_SOUND",&aStack_284);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x50),L"ATTACK_SOUND",&aStack_283);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x58),L"IDLE_SOUND",&aStack_282)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x60),L"DEATH_SOUND",&aStack_281);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x68),L"ROAR_SOUND",&aStack_280)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x70),L"FLEE_SOUND",&aStack_27f)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x78),L"MISS_SOUND",&aStack_27e)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x80),L"FALL_SOUND",&aStack_27d)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x88),L"LAND_SOUND",&aStack_27c)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x90),L"TAKE_SOUND",&aStack_27b)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x98),L"SPAWN_SOUND",&aStack_27a);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa0),L"USE_SOUND",&aStack_279);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa8),L"EQUIP_SOUND",&aStack_278);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb0),L"OPENMENU_SOUND",&aStack_277);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb8),L"BUY_SOUND",&aStack_276);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xc0),L"ERROR_SOUND",&aStack_275);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 200),L"LEVELUP_SOUND",&aStack_274);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd0),L"EFFORT_SOUND",&aStack_273);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd8),L"SPENDPOINT_SOUND",&aStack_272);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe0),L"PORTALENTER_SOUND",&aStack_271);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe8),L"POERTALEXIT_SOUND",&aStack_270);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf0),L"SKILLASSIGN_SOUND",&aStack_26f);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf8),L"QUESTRECEIVED_SOUND",&aStack_26e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x100),L"QUESTCOMPLETED_SOUND",&aStack_26d)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x108),L"LOWMANA_SOUND",&aStack_26c);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x110),L"MISSILEREFLECT_SOUND",&aStack_26b)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x118),L"BADEFFECT_SOUND",&aStack_26a);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x120),L"GOODEFFECT_SOUND",&aStack_269);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x128),L"NPCDIALOG_SOUND",&aStack_268);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x130),L"NPCGREET",&aStack_267);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x138),L"NPCBYE",&aStack_266);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x140),L"NPCPURCHASE",&aStack_265);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x148),L"NPCSELL",&aStack_264);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x150),L"VOICEPETINVENTORYFULL_SOUND",
             &aStack_263);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x158),L"VOICEPETDEPARTED_SOUND",
             &aStack_262);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x160),L"VOICEPETRETURNED_SOUND",
             &aStack_261);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x168),L"VOICEPETFLED_SOUND",&aStack_260);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x170),L"VOICEPETLEVELUP_SOUND",&aStack_25f
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x178),L"VOICEINVENTORYFULL_SOUND",
             &aStack_25e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x180),L"VOICEINSUFFICIENTGOLD_SOUND",
             &aStack_25d);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x188),L"VOICEIMPOSSIBLE_SOUND",&aStack_25c
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 400),L"VOICECANTCAST_SOUND",&aStack_25b);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x198),L"VOICECANTCASTHERE_SOUND",
             &aStack_25a);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a0),L"VOICEHEALTHLOW_SOUND",&aStack_259)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a8),L"VOICEMANALOW_SOUND",&aStack_258);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b0),L"VOICETRAPSPRUNG_SOUND",&aStack_257
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b8),L"VOICEREFRESHED_SOUND",&aStack_256)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c0),L"VOICEPOWERFUL_SOUND",&aStack_255);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c8),L"VOICEHEALTHY_SOUND",&aStack_254);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d0),L"VOICEILL_SOUND",&aStack_253);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d8),L"VOICEPOISONED_SOUND",&aStack_252);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e0),L"VOICELEVELUP_SOUND",&aStack_251);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e8),L"VOICEFAMEUP_SOUND",&aStack_250);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f0),L"VOICESKILLUP_SOUND",&aStack_24f);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f8),L"VOICEFORTUNEGOOD_SOUND",
             &aStack_24e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x200),L"VOICEFORTUNEBAD_SOUND",&aStack_24d
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x208),L"VOICESPELLLEARNED_SOUND",
             &aStack_24c);
  ::KSOUNDBANK_STRINGS._528_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_1,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KALIGNMENT_STRINGS,L"NEUTRAL",&aStack_24b);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 8),L"GOOD",&aStack_24a);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x10),L"EVIL",&aStack_249);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x18),L"ALL",&aStack_248);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x20),L"BERSERK",&aStack_247);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x28),L"EVILBERSERK",&aStack_246);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x30),L"GOODBERSERK",&aStack_245);
  __cxa_atexit(::__tcf_2,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KAITYPE_STRINGS,L"NORMAL",&aStack_244);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 8),L"RANGEDDEFENDER",&aStack_243);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x10),L"DEFENDER",&aStack_242);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x18),L"RANGEDCASTER",&aStack_241);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x20),L"CIRCLER",&aStack_240);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x28),L"RESURRECTER",&aStack_23f);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x30),L"DUMMY",&aStack_23e);
  __cxa_atexit(::__tcf_3,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gDAMAGE_TYPES,L"Physical",&aStack_23d);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 8),L"Magical",&aStack_23c);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x10),L"Fire",&aStack_23b);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x18),L"Ice",&aStack_23a);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x20),L"Electric",&aStack_239);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x28),L"Poison",&aStack_238);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x30),L"All",&aStack_237);
  __cxa_atexit(::__tcf_4,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::gTARGET_TYPES,L"USER",&aStack_236);
  std::wstring::wstring((wstring_conflict *)&DAT_014f12c8,L"ITEM",&aStack_235);
  __cxa_atexit(::__tcf_5,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSFXTypeName,L"STATIONARYTARGET",&aStack_234);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 8),L"STATIONARYOWNER",&aStack_233);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x10),L"STATIONARY",&aStack_232);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x18),L"STATIONARYPORTAL",&aStack_231)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x20),L"BEAM",&aStack_230);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x28),L"FOLLOWOWNER",&aStack_22f);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x30),L"FOLLOWTARGET",&aStack_22e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x38),L"PROJECTILELOCATION",&aStack_22d);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x40),L"PROJECTILECHARACTER",&aStack_22c);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x48),L"PROJECTILELOCATIONERRATIC",&aStack_22b);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x50),L"PROJECTILECHARACTERERRATIC",&aStack_22a);
  __cxa_atexit(::__tcf_6,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KCharacterNames,L"NA",&aStack_229);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 8),L"NA",&aStack_228);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x10),L"NA",&aStack_227);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x18),L"NA",&aStack_226);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x20),L"NA",&aStack_225);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x28),L"NA",&aStack_224);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x30),L"NA",&aStack_223);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x38),L"NA",&aStack_222);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x40),L"Bksp",&aStack_221);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x48),L"Tab",&aStack_220);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x50),L"NA",&aStack_21f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x58),L"NA",&aStack_21e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x60),L"Ctr",&aStack_21d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x68),L"Ret",&aStack_21c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x70),L"NA",&aStack_21b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x78),L"NA",&aStack_21a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x80),L"Shift",&aStack_219);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x88),L"Ctrl",&aStack_218);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x90),L"Alt",&aStack_217);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x98),L"Tab",&aStack_216);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa0),L"NA",&aStack_215);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa8),L"NA",&aStack_214);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb0),L"NA",&aStack_213);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb8),L"NA",&aStack_212);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xc0),L"NA",&aStack_211);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 200),L"NA",&aStack_210);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd0),L"NA",&aStack_20f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd8),L"NA",&aStack_20e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe0),L"NA",&aStack_20d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe8),L"NA",&aStack_20c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf0),L"NA",&aStack_20b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf8),L"NA",&aStack_20a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x100),L"space",&aStack_209);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x108),L"pgup",&aStack_208);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x110),L"pgdn",&aStack_207);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x118),L"end",&aStack_206);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x120),L"home",&aStack_205);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x128),L"left arrow",&aStack_204);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x130),L"up arrow",&aStack_203);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x138),L"right arrow",&aStack_202);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x140),L"down arrow",&aStack_201);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x148),L")",&aStack_200);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x150),L"*",&aStack_1ff);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x158),L"+",&aStack_1fe);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x160),L",",&aStack_1fd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x168),L"ins",&aStack_1fc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x170),L"del",&aStack_1fb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x178),L"/",&aStack_1fa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x180),L"0",&aStack_1f9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x188),L"1",&aStack_1f8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 400),L"2",&aStack_1f7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x198),L"3",&aStack_1f6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a0),L"4",&aStack_1f5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a8),L"5",&aStack_1f4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b0),L"6",&aStack_1f3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b8),L"7",&aStack_1f2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c0),L"8",&aStack_1f1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c8),L"9",&aStack_1f0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d0),L":",&aStack_1ef);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d8),L";",&aStack_1ee);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e0),L"<",&aStack_1ed);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e8),L"=",&aStack_1ec);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f0),L">",&aStack_1eb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f8),L"?",&aStack_1ea);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x200),L"@",&aStack_1e9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x208),L"a",&aStack_1e8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x210),L"b",&aStack_1e7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x218),L"c",&aStack_1e6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x220),L"d",&aStack_1e5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x228),L"e",&aStack_1e4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x230),L"NA",&aStack_1e3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x238),L"g",&aStack_1e2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x240),L"h",&aStack_1e1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x248),L"i",&aStack_1e0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x250),L"j",&aStack_1df);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 600),L"k",&aStack_1de);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x260),L"l",&aStack_1dd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x268),L"m",&aStack_1dc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x270),L"n",&aStack_1db);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x278),L"o",&aStack_1da);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x280),L"p",&aStack_1d9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x288),L"NA",&aStack_1d8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x290),L"r",&aStack_1d7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x298),L"s",&aStack_1d6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a0),L"t",&aStack_1d5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a8),L"u",&aStack_1d4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b0),L"v",&aStack_1d3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b8),L"w",&aStack_1d2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c0),L"x",&aStack_1d1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c8),L"y",&aStack_1d0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d0),L"z",&aStack_1cf);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d8),L"[",&aStack_1ce);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e0),L"\\",&aStack_1cd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e8),L"]",&aStack_1cc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f0),L"^",&aStack_1cb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f8),L"_",&aStack_1ca);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x300),L"NUM 0",&aStack_1c9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x308),L"NUM 1",&aStack_1c8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x310),L"NUM 2",&aStack_1c7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x318),L"NUM 3",&aStack_1c6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 800),L"NUM 4",&aStack_1c5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x328),L"NUM 5",&aStack_1c4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x330),L"NUM 6",&aStack_1c3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x338),L"NUM 7",&aStack_1c2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x340),L"NUM 8",&aStack_1c1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x348),L"NUM 9",&aStack_1c0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x350),L"*",&aStack_1bf);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x358),L"+",&aStack_1be);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x360),L"NA",&aStack_1bd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x368),L"-",&aStack_1bc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x370),L"NA",&aStack_1bb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x378),L"F1",&aStack_1ba);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x380),L"F2",&aStack_1b9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x388),L"F3",&aStack_1b8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x390),L"F4",&aStack_1b7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x398),L"F5",&aStack_1b6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a0),L"F6",&aStack_1b5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a8),L"F7",&aStack_1b4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b0),L"F8",&aStack_1b3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b8),L"F9",&aStack_1b2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c0),L"F10",&aStack_1b1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c8),L"F11",&aStack_1b0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d0),L"F12",&aStack_1af);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d8),L"{",&aStack_1ae);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3e0),L"|",&aStack_1ad);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 1000),L"}",&aStack_1ac);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f0),L"~",&aStack_1ab);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f8),L";",&aStack_1aa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x400),L"=",&aStack_1a9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x408),L".",&aStack_1a8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x410),L"-",&aStack_1a7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x418),L",",&aStack_1a6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x420),L"/",&aStack_1a5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x428),L"`",&aStack_1a4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x430),L"[",&aStack_1a3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x438),L"\\",&aStack_1a2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x440),L"]",&aStack_1a1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x448),L"\'",&aStack_1a0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x450),L"NA",&aStack_19f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x458),L"NA",&aStack_19e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x460),L"NA",&aStack_19d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x468),L"NA",&aStack_19c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x470),L"NA",&aStack_19b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x478),L"NA",&aStack_19a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x480),L"NA",&aStack_199);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x488),L"NA",&aStack_198);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x490),L"NA",&aStack_197);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x498),L"NA",&aStack_196);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a0),L"NA",&aStack_195);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a8),L"NA",&aStack_194);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b0),L"NA",&aStack_193);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b8),L"NA",&aStack_192);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c0),L"NA",&aStack_191);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c8),L"NA",&aStack_190);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d0),L"NA",&aStack_18f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d8),L"NA",&aStack_18e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e0),L"NA",&aStack_18d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e8),L"NA",&aStack_18c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f0),L"NA",&aStack_18b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f8),L"NA",&aStack_18a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x500),L"NA",&aStack_189);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x508),L"NA",&aStack_188);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x510),L"NA",&aStack_187);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x518),L"NA",&aStack_186);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x520),L"NA",&aStack_185);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x528),L"NA",&aStack_184);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x530),L"NA",&aStack_183);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x538),L"NA",&aStack_182);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x540),L"NA",&aStack_181);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x548),L"NA",&aStack_180);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x550),L"NA",&aStack_17f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x558),L"NA",&aStack_17e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x560),L"NA",&aStack_17d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x568),L"NA",&aStack_17c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x570),L"NA",&aStack_17b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x578),L"NA",&aStack_17a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x580),L"NA",&aStack_179);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x588),L"NA",&aStack_178);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x590),L"NA",&aStack_177);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x598),L"NA",&aStack_176);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a0),L"NA",&aStack_175);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a8),L"NA",&aStack_174);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b0),L"NA",&aStack_173);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b8),L"NA",&aStack_172);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c0),L"NA",&aStack_171);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c8),L"NA",&aStack_170);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d0),L";",&aStack_16f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d8),L"=",&aStack_16e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e0),L",",&aStack_16d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e8),L"-",&aStack_16c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f0),L".",&aStack_16b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f8),L"/",&aStack_16a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x600),L"`",&aStack_169);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x608),L"NA",&aStack_168);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x610),L"NA",&aStack_167);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x618),L"NA",&aStack_166);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x620),L"NA",&aStack_165);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x628),L"NA",&aStack_164);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x630),L"NA",&aStack_163);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x638),L"NA",&aStack_162);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x640),L"NA",&aStack_161);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x648),L"NA",&aStack_160);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x650),L"NA",&aStack_15f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x658),L"NA",&aStack_15e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x660),L"NA",&aStack_15d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x668),L"NA",&aStack_15c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x670),L"NA",&aStack_15b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x678),L"NA",&aStack_15a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x680),L"NA",&aStack_159);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x688),L"NA",&aStack_158);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x690),L"NA",&aStack_157);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x698),L"NA",&aStack_156);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a0),L"NA",&aStack_155);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a8),L"NA",&aStack_154);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b0),L"NA",&aStack_153);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b8),L"NA",&aStack_152);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c0),L"NA",&aStack_151);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c8),L"NA",&aStack_150);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d0),L"NA",&aStack_14f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d8),L"[",&aStack_14e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e0),L"\\",&aStack_14d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e8),L"]",&aStack_14c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f0),L"\'",&aStack_14b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f8),L"NA",&aStack_14a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x700),L"NA",&aStack_149);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x708),L"NA",&aStack_148);
  __cxa_atexit(::__tcf_7,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::gSKILL_EVENT_TYPE_NAMES,L"EVENT_START",&aStack_147);
  std::wstring::wstring((wstring_conflict *)&DAT_014f1a68,L"EVENT_END",&aStack_146);
  std::wstring::wstring((wstring_conflict *)&DAT_014f1a70,L"EVENT_TRIGGER",&aStack_145);
  std::wstring::wstring((wstring_conflict *)&DAT_014f1a78,L"EVENT_TRIGGER_TWO",&aStack_144);
  std::wstring::wstring((wstring_conflict *)&DAT_014f1a80,L"EVENT_UNITHIT",&aStack_143);
  std::wstring::wstring((wstring_conflict *)&DAT_014f1a88,L"EVENT_UNITDIE",&aStack_142);
  std::wstring::wstring((wstring_conflict *)&DAT_014f1a90,L"EVENT_MISSILEHIT",&aStack_141);
  std::wstring::wstring((wstring_conflict *)&DAT_014f1a98,L"EVENT_MISSILEDIE",&aStack_140);
  std::wstring::wstring((wstring_conflict *)&DAT_014f1aa0,L"EVENT_DIEBYEFFECT",&aStack_13f);
  std::wstring::wstring((wstring_conflict *)&DAT_014f1aa8,L"EVENT_CASTERDIE",&aStack_13e);
  std::wstring::wstring((wstring_conflict *)&DAT_014f1ab0,L"EVENT_UNIT_CREATE",&aStack_13d);
  __cxa_atexit(::__tcf_8,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_TARGET_TYPE_NAMES,L"NONE",&aStack_13c);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 8),L"POSITION",&aStack_13b);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x10),L"TARGET",&aStack_13a);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x18),L"SELF",&aStack_139)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x20),L"EVERYBODY",&aStack_138);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x28),L"POSITIONRANDOM",&aStack_137);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x30),L"POSITIONFLEE",&aStack_136);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x38),L"ITEM",&aStack_135)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x40),L"UNIDENTIFIEDITEM",&aStack_134
            );
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x48),L"PETS",&aStack_133)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x50),L"SELFANDPETS",&aStack_132);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x58),L"TARGET_POS",&aStack_131);
  __cxa_atexit(::__tcf_9,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_ACTIVATION_TYPE_NAMES,L"ANY",&aStack_130);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 8),L"PROC",&aStack_12f);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 0x10),L"WEAPON",&aStack_12e);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 0x18),L"NORMAL",&aStack_12d);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 0x20),L"PASSIVE",&aStack_12c);
  __cxa_atexit(::__tcf_10,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_TYPE_NAMES,L"SKILL",&aStack_12b);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TYPE_NAMES + 8),L"OFFENSIVE",&aStack_12a);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TYPE_NAMES + 0x10),L"DEFENSIVE",&aStack_129);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TYPE_NAMES + 0x18),L"CHARM",&aStack_128);
  ::gSKILL_TYPE_NAMES._32_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_11,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_TYPE_DISPLAY_NAMES,L"Class Skill",&aStack_127);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TYPE_DISPLAY_NAMES + 8),L"Offensive Spell",&aStack_126);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TYPE_DISPLAY_NAMES + 0x10),L"Defensive Spell",&aStack_125
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TYPE_DISPLAY_NAMES + 0x18),L"Charm Spell",&aStack_124);
  ::gSKILL_TYPE_DISPLAY_NAMES._32_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_12,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_BONE_ATTACHMENT_NAMES,L"",&aStack_123);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 8),L"CENTER",&aStack_122);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x10),L"HEAD",&aStack_121);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x18),L"RIGHTHAND",&aStack_120);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x20),L"LEFTHAND",&aStack_11f);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x28),L"RIGHTSHOULDER",
             &aStack_11e);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x30),L"LEFTSHOULDER",&aStack_11d
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x38),L"POSITION",&aStack_11c);
  __cxa_atexit(::__tcf_13,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEffect_Activation_Names,L"PASSIVE",&aStack_11b);
  std::wstring::wstring((wstring_conflict *)(::gEffect_Activation_Names + 8),L"DYNAMIC",&aStack_11a)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gEffect_Activation_Names + 0x10),L"TRANSFER",&aStack_119);
  __cxa_atexit(::__tcf_14,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEFFECT_STAT_MODIFIER_NAMES,L"MELEE",&aStack_118);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 8),L"RANGED",&aStack_117);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x10),L"DEFENSE",&aStack_116);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x18),L"MAGIC",&aStack_115);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x20),L"LEVEL",&aStack_114);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x28),L"OWNERLEVEL",&aStack_113);
  __cxa_atexit(::__tcf_15,0,&__dso_handle);
  std::string::string((string *)::gEFFECT_STAT_MODIFIER_ICON_NAMES,"iconmelee",&aStack_112);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 8),"iconranged",&aStack_111);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x10),"icondefense",
                      &aStack_110);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x18),"iconmagic",&aStack_10f)
  ;
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x20),"iconmagic",&aStack_10e)
  ;
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x28),"iconmagic",&aStack_10d)
  ;
  __cxa_atexit(::__tcf_16,0,&__dso_handle);
  ParticleUniverse::HALFSCALE._4_4_ = DAT_0142463c * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._0_4_ = Ogre::Vector3::UNIT_SCALE * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._8_4_ = DAT_00fa4810 * DAT_01424640;
  std::wstring::wstring((wstring_conflict *)::gEDITOR_EVENT_NAMES,L"STOP",&aStack_10c);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 8),L"PLAY",&aStack_10b);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x10),L"RELOAD TILES",&aStack_10a);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x18),L"TOGGLE LIGHTING",&aStack_109);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x20),L"SELECT COLLIDABLE",&aStack_108);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x28),L"PAUSE PARTICLES",&aStack_107);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x30),L"UNPAUSE PARTICLES",&aStack_106);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x38),L"COLLISION ALL",&aStack_105);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x40),L"COLLISION MODELS",&aStack_104);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x48),L"COLLISION PREFABS",&aStack_103);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x50),L"COLLISION ROOMPIECES",&aStack_102)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x58),L"COLLISION ROOMPROPS",&aStack_101);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x60),L"RELOAD GRAPHS",&aStack_100);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x68),L"TOGGLE PLAYER LIGHT",&aStack_ff);
  __cxa_atexit(::__tcf_17,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEDITOR_FLAG_NAMES,L"LOGIC ENABLED",&aStack_fe);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 8),L"INGAME MODE",&aStack_fd);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x10),L"SHOW STATS",&aStack_fc);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x18),L"EDIT POSITION",&aStack_fb);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x20),L"EDIT SCALE",&aStack_fa);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x28),L"EDIT ORIENTATION",&aStack_f9);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x30),L"EDIT NONE",&aStack_f8);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x38),L"SHOW HELPERS",&aStack_f7);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x40),L"SHOW GRID",&aStack_f6);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x48),L"SHOW WORKING PLANE",&aStack_f5);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x50),L"SNAP TO GRID",&aStack_f4);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x58),L"SUSPEND EDITOR",&aStack_f3);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x60),L"LIGHTING VISIBLE",&aStack_f2);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x68),L"RECALCULATE LIGHTING",&aStack_f1);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x70),L"SHOW EDGES",&aStack_f0);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x78),L"UPDATE PARTICLES CIRCLE",&aStack_ef
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x80),L"SHOW LOGIC OUTPUT",&aStack_ee);
  __cxa_atexit(::__tcf_18,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::gEDITOR_UPDATE_MASKS,L"OBJECT SELECTION CHANGED",&aStack_ed);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 8),L"OBJECT DATA CHANGED",&aStack_ec);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 0x10),L"OBJECTS CREATED",&aStack_eb);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 0x18),L"REFRESH TREE VIEW",&aStack_ea);
  __cxa_atexit(::__tcf_19,0,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::ALIAS,"1",&aStack_e9);
  __cxa_atexit(std::string::~string,&ParticleUniverse::ALIAS,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::SYSTEM,"2",&aStack_e8);
  __cxa_atexit(std::string::~string,&ParticleUniverse::SYSTEM,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::TECHNIQUE,"3",&aStack_e7);
  __cxa_atexit(std::string::~string,&ParticleUniverse::TECHNIQUE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::RENDERER,"4",&aStack_e6);
  __cxa_atexit(std::string::~string,&ParticleUniverse::RENDERER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EMITTER,"5",&aStack_e5);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EMITTER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::AFFECTOR,"6",&aStack_e4);
  __cxa_atexit(std::string::~string,&ParticleUniverse::AFFECTOR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::OBSERVER,"7",&aStack_e3);
  __cxa_atexit(std::string::~string,&ParticleUniverse::OBSERVER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::HANDLER,"8",&aStack_e2);
  __cxa_atexit(std::string::~string,&ParticleUniverse::HANDLER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::BEHAVIOUR,"9",&aStack_e1);
  __cxa_atexit(std::string::~string,&ParticleUniverse::BEHAVIOUR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EXTERN,"10",&aStack_e0);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EXTERN,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DYNAMIC_ATTRIBUTE,"11",&aStack_df);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DYNAMIC_ATTRIBUTE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DEPENDENCY,"12",&aStack_de);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DEPENDENCY,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_LAYOUT_TYPE_NAMES,L"NORMAL",&aStack_dd);
  std::wstring::wstring((wstring_conflict *)(::g_LAYOUT_TYPE_NAMES + 8),L"PARTICLE",&aStack_dc);
  std::wstring::wstring((wstring_conflict *)(::g_LAYOUT_TYPE_NAMES + 0x10),L"TIMELINE",&aStack_db);
  std::wstring::wstring((wstring_conflict *)(::g_LAYOUT_TYPE_NAMES + 0x18),L"TRIGGER",&aStack_da);
  __cxa_atexit(::__tcf_20,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gPARTICLE_RENDER_TYPE_NAMES,L"Billboard",&aStack_d9);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 8),L"Billboard Up",&aStack_d8);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x10),L"Billboard Forward",
             &aStack_d7);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x18),L"Billboard Up Camera",
             &aStack_d6);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x20),L"Billboard Forward Camera",
             &aStack_d5);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x28),L"Billboard Self",&aStack_d4
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x30),L"Billboard Common",
             &aStack_d3);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x38),L"Billboard Shape",
             &aStack_d2);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x40),L"Box",&aStack_d1);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x48),L"Sphere",&aStack_d0);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x50),L"Entity",&aStack_cf);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x58),L"EntityWorld",&aStack_ce);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x60),L"RibbonTrail",&aStack_cd);
  __cxa_atexit(::__tcf_21,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)&::gPARTICLE_AFFECTOR_FORCE_APPLICATION_TYPES,L"Average",&aStack_cc
            );
  std::wstring::wstring((wstring_conflict *)&DAT_014f1ef8,L"Add",&aStack_cb);
  __cxa_atexit(::__tcf_22,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)&::gPARTICLE_BILLBOARD_ROTATION_TYPES,L"Geometry",&aStack_ca);
  std::wstring::wstring((wstring_conflict *)&DAT_014f1f08,L"Texture",&aStack_c9);
  __cxa_atexit(::__tcf_23,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gPARTICLE_COLLISION_TYPE,L"Stop",&aStack_c8);
  std::wstring::wstring((wstring_conflict *)(::gPARTICLE_COLLISION_TYPE + 8),L"Bounce",&aStack_c7);
  std::wstring::wstring((wstring_conflict *)(::gPARTICLE_COLLISION_TYPE + 0x10),L"Flow",&aStack_c6);
  __cxa_atexit(::__tcf_24,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gPARTICLE_INTERSECTION_TYPE,L"Fast",&aStack_c5);
  std::wstring::wstring((wstring_conflict *)(::gPARTICLE_INTERSECTION_TYPE + 8),L"Box",&aStack_c4);
  ::gPARTICLE_INTERSECTION_TYPE._16_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_25,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS,L"Top Left",&aStack_c3);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 8),L"Top Center",
             &aStack_c2);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x10),L"Top Right",
             &aStack_c1);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x18),L"Center Left",
             &aStack_c0);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x20),L"Center",
             &aStack_bf);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x28),L"Center Right",
             &aStack_be);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x30),L"Bottom Left",
             &aStack_bd);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x38),L"Bottom Center",
             &aStack_bc);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x40),L"Bottom Right",
             &aStack_bb);
  __cxa_atexit(::__tcf_26,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gPARTICLE_MATERIAL_TYPES,L"Alpha",&aStack_ba);
  std::wstring::wstring((wstring_conflict *)(::gPARTICLE_MATERIAL_TYPES + 8),L"Normal",&aStack_b9);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_MATERIAL_TYPES + 0x10),L"Additive",&aStack_b8);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_MATERIAL_TYPES + 0x18),L"Modulate",&aStack_b7);
  __cxa_atexit(::__tcf_27,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEMITTER_TYPES,L"Point",&aStack_b6);
  std::wstring::wstring((wstring_conflict *)(::gEMITTER_TYPES + 8),L"Box",&aStack_b5);
  std::wstring::wstring((wstring_conflict *)(::gEMITTER_TYPES + 0x10),L"Circle",&aStack_b4);
  std::wstring::wstring((wstring_conflict *)(::gEMITTER_TYPES + 0x18),L"Line",&aStack_b3);
  std::wstring::wstring((wstring_conflict *)(::gEMITTER_TYPES + 0x20),L"SphereSurface",&aStack_b2);
  __cxa_atexit(::__tcf_28,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gPOINT_ORDER_NAMES,L"Clockwise",&aStack_b1);
  std::wstring::wstring
            ((wstring_conflict *)(::gPOINT_ORDER_NAMES + 8),L"Counter Clockwise",&aStack_b0);
  std::wstring::wstring((wstring_conflict *)(::gPOINT_ORDER_NAMES + 0x10),L"Random",&aStack_af);
  __cxa_atexit(::__tcf_29,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSHAPE_NAMES,L"Angle",&aStack_ae);
  std::wstring::wstring((wstring_conflict *)(::gSHAPE_NAMES + 8),L"Line",&aStack_ad);
  std::wstring::wstring((wstring_conflict *)(::gSHAPE_NAMES + 0x10),L"Sphere",&aStack_ac);
  std::wstring::wstring((wstring_conflict *)(::gSHAPE_NAMES + 0x18),L"Point",&aStack_ab);
  std::wstring::wstring((wstring_conflict *)(::gSHAPE_NAMES + 0x20),L"Box",&aStack_aa);
  __cxa_atexit(::__tcf_30,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSHAPE_DIRECTION_NAMES,L"Forward",&aStack_a9);
  std::wstring::wstring((wstring_conflict *)(::gSHAPE_DIRECTION_NAMES + 8),L"Down",&aStack_a8);
  std::wstring::wstring((wstring_conflict *)(::gSHAPE_DIRECTION_NAMES + 0x10),L"Up",&aStack_a7);
  std::wstring::wstring
            ((wstring_conflict *)(::gSHAPE_DIRECTION_NAMES + 0x18),L"Outward From Center",&aStack_a6
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gSHAPE_DIRECTION_NAMES + 0x20),L"Inward to Center",&aStack_a5);
  __cxa_atexit(::__tcf_31,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_TYPE_NAMES,L"",&aStack_a4);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 8),L"FIND",&aStack_a3);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x10),L"KILL NUM",&aStack_a2);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x18),L"KILL BOSS",&aStack_a1);
  __cxa_atexit(::__tcf_32,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_DIALOG_TYPE_NAMES,L"ERROR",&aStack_a0);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 8),L"INTRO",&aStack_9f);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x10),L"RETURN",&aStack_9e);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x18),L"COMPLETE",&aStack_9d);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x20),L"PASSIVE",&aStack_9c);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x28),L"DETAILS",&aStack_9b);
  __cxa_atexit(::__tcf_33,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES,"tag_righthand",&aStack_9a);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 8),"tag_lefthand",&aStack_99);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x10),"",&aStack_98);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x18),"Bip01 Head",&aStack_97);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x20),"",&aStack_96);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x28),"Bip01 L Clavicle",&aStack_95);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x30),"",&aStack_94);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x38),"",&aStack_93);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x40),"",&aStack_92);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x48),"",&aStack_91);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x50),"",&aStack_90);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x58),"tag_leftarm",&aStack_8f);
  __cxa_atexit(::__tcf_34,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES_SECONDARY,"",&aStack_8e);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 8),"",&aStack_8d);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x10),"",&aStack_8c);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x18),"",&aStack_8b);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x20),"",&aStack_8a);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x28),"Bip01 R Clavicle",
                      &aStack_89);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x30),"",&aStack_88);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x38),"",&aStack_87);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x40),"",&aStack_86);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x48),"",&aStack_85);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x50),"",&aStack_84);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x58),"",&aStack_83);
  __cxa_atexit(::__tcf_35,0,&__dso_handle);
  std::string::string((string *)::KEquipmentIconName,"EquipLeftHand",&aStack_82);
  std::string::string((string *)(::KEquipmentIconName + 8),"EquipRightHand",&aStack_81);
  std::string::string((string *)(::KEquipmentIconName + 0x10),"EquipGloves",&aStack_80);
  std::string::string((string *)(::KEquipmentIconName + 0x18),"EquipHelm",&aStack_7f);
  std::string::string((string *)(::KEquipmentIconName + 0x20),"EquipChest",&aStack_7e);
  std::string::string((string *)(::KEquipmentIconName + 0x28),"EquipShoulder",&aStack_7d);
  std::string::string((string *)(::KEquipmentIconName + 0x30),"EquipBoots",&aStack_7c);
  std::string::string((string *)(::KEquipmentIconName + 0x38),"EquipBelt",&aStack_7b);
  std::string::string((string *)(::KEquipmentIconName + 0x40),"EquipRing1",&aStack_7a);
  std::string::string((string *)(::KEquipmentIconName + 0x48),"EquipRing2",&aStack_79);
  std::string::string((string *)(::KEquipmentIconName + 0x50),"EquipAmulet",&aStack_78);
  std::string::string((string *)(::KEquipmentIconName + 0x58),"",&aStack_77);
  __cxa_atexit(::__tcf_36,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames,L"CHEST",&aStack_76);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 8),L"GLOVES",&aStack_75);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x10),L"BOOTS",&aStack_74);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x18),L"HELMET",&aStack_73);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x20),L"SHOULDERS",&aStack_72);
  __cxa_atexit(::__tcf_37,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames2,L"",&aStack_71);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 8),L"",&aStack_70);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x10),L"",&aStack_6f);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x18),L"FACE",&aStack_6e);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x20),L"",&aStack_6d);
  __cxa_atexit(::__tcf_38,0,&__dso_handle);
  std::string::string((string *)gMISSILE_PARTICLE_NAMES,"Release",&aStack_6c);
  std::string::string((string *)(gMISSILE_PARTICLE_NAMES + 8),"Alive",&aStack_6b);
  std::string::string((string *)(gMISSILE_PARTICLE_NAMES + 0x10),"Hit",&aStack_6a);
  std::string::string((string *)(gMISSILE_PARTICLE_NAMES + 0x18),"Die",&aStack_69);
  __cxa_atexit(::__tcf_39,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)gSPAWN_TYPE_NAMES,L"Monsters",&aStack_68);
  std::wstring::wstring((wstring_conflict *)(gSPAWN_TYPE_NAMES + 8),L"Items",&aStack_67);
  std::wstring::wstring((wstring_conflict *)(gSPAWN_TYPE_NAMES + 0x10),L"Particle",&aStack_66);
  std::wstring::wstring((wstring_conflict *)(gSPAWN_TYPE_NAMES + 0x18),L"Spawn Class",&aStack_65);
  std::wstring::wstring((wstring_conflict *)(gSPAWN_TYPE_NAMES + 0x20),L"Missiles",&aStack_64);
  std::wstring::wstring((wstring_conflict *)(gSPAWN_TYPE_NAMES + 0x28),L"Unit Type",&aStack_63);
  std::wstring::wstring((wstring_conflict *)(gSPAWN_TYPE_NAMES + 0x30),L"Props",&aStack_62);
  __cxa_atexit(__tcf_40,0,&__dso_handle);
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
  __cxa_atexit(__tcf_41,0,&__dso_handle);
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
  __cxa_atexit(__tcf_42,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)gSKILL_EFFECT_AND_AFFIXES_TARGET_NAMES,L"ENEMY",&aStack_3e);
  std::wstring::wstring
            ((wstring_conflict *)(gSKILL_EFFECT_AND_AFFIXES_TARGET_NAMES + 8),L"SELF",&aStack_3d);
  std::wstring::wstring
            ((wstring_conflict *)(gSKILL_EFFECT_AND_AFFIXES_TARGET_NAMES + 0x10),L"PET",&aStack_3c);
  std::wstring::wstring
            ((wstring_conflict *)(gSKILL_EFFECT_AND_AFFIXES_TARGET_NAMES + 0x18),L"EVERYBODY",
             &aStack_3b);
  std::wstring::wstring
            ((wstring_conflict *)(gSKILL_EFFECT_AND_AFFIXES_TARGET_NAMES + 0x20),L"FRIEND",
             &aStack_3a);
  __cxa_atexit(__tcf_43,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_AIFLAG_TYPE_NAMES,L"AWARE",&aStack_39);
  std::wstring::wstring((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 8),L"BERSERK",&aStack_38);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x10),L"CANNOT INTERRUPT",&aStack_37);
  std::wstring::wstring((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x18),L"FRIGHTEN",&aStack_36);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x20),L"NO LINE OF SIGHT",&aStack_35);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x28),L"NEVER CHANGE TARGET",&aStack_34);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x30),L"CANNOT TARGET",&aStack_33);
  __cxa_atexit(__tcf_44,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_AISTAT_TYPE_NAMES,L"NONE",&aStack_32);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 8),L"HP",&aStack_31);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x10),L"MANA",&aStack_30);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x18),L"HP PCT",&aStack_2f);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x20),L"MANA PCT",&aStack_2e);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x28),L"ACTIVE UNITS",&aStack_2d);
  __cxa_atexit(__tcf_45,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::g_AISTAT_LOGIC_NAMES,L"BELOW",&aStack_2c);
  std::wstring::wstring((wstring_conflict *)&DAT_014f2518,L"ABOVE",&aStack_2b);
  __cxa_atexit(__tcf_46,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_AISTAT_TARGET_NAMES,L"SELF",&aStack_2a);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 8),L"FORMATION",&aStack_29);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 0x10),L"AREA",&aStack_28);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 0x18),L"AREAUNITTYPES",&aStack_27);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 0x20),L"AREAFORMATION",&aStack_26);
  __cxa_atexit(__tcf_47,0,&__dso_handle);
  ::gUnionOf32BitData._0_4_ = 0;
  ::gUnionOf32BitData._4_4_ = 0;
  ::gUnionOf32BitData._8_4_ = 0;
  std::wstring::wstring
            ((wstring_conflict *)::KEditorObjectPropertyTypeNames,L"NOT VALID",&aStack_25);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 8),L"NOT SET",&aStack_24);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x10),L"INTEGER",&aStack_23);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x18),L"FLOAT",&aStack_22);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x20),L"UNSIGNED INTEGER",
             &aStack_21);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x28),L"STRING",&aStack_20);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x30),L"BOOL",&aStack_1f);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x38),L"VECTOR2",&aStack_1e);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x40),L"VECTOR3",&aStack_1d);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x48),L"VECTOR4",&aStack_1c);
  __cxa_atexit(__tcf_48,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)gTIMELINE_INTERP_TYPES,L"Linear",&aStack_1b);
  std::wstring::wstring((wstring_conflict *)(gTIMELINE_INTERP_TYPES + 8),L"Linear Round",&aStack_1a)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(gTIMELINE_INTERP_TYPES + 0x10),L"Linear Round Down",&aStack_19);
  std::wstring::wstring
            ((wstring_conflict *)(gTIMELINE_INTERP_TYPES + 0x18),L"Linear Round Up",&aStack_18);
  std::wstring::wstring((wstring_conflict *)(gTIMELINE_INTERP_TYPES + 0x20),L"Spline",&aStack_17);
  std::wstring::wstring
            ((wstring_conflict *)(gTIMELINE_INTERP_TYPES + 0x28),L"Quaternion",&aStack_16);
  std::wstring::wstring
            ((wstring_conflict *)(gTIMELINE_INTERP_TYPES + 0x30),L"No Interpolation",&aStack_15);
  std::wstring::wstring
            ((wstring_conflict *)(gTIMELINE_INTERP_TYPES + 0x38),L"Use Timeline Default",&aStack_14)
  ;
  __cxa_atexit(__tcf_49,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)gTIMELINE_MODIFICATION_TYPE_NAMES,L"None",&aStack_13);
  std::wstring::wstring
            ((wstring_conflict *)(gTIMELINE_MODIFICATION_TYPE_NAMES + 8),L"Set",&aStack_12);
  std::wstring::wstring
            ((wstring_conflict *)(gTIMELINE_MODIFICATION_TYPE_NAMES + 0x10),L"Multiply",&aStack_11);
  __cxa_atexit(__tcf_50,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gRESOURCE_GROUP_NAMES,L"ITEMS",&aStack_10);
  std::wstring::wstring((wstring_conflict *)(::gRESOURCE_GROUP_NAMES + 8),L"MONSTERS",&aStack_f);
  std::wstring::wstring((wstring_conflict *)(::gRESOURCE_GROUP_NAMES + 0x10),L"PLAYERS",&aStack_e);
  std::wstring::wstring((wstring_conflict *)(::gRESOURCE_GROUP_NAMES + 0x18),L"PROPS",&aStack_d);
  __cxa_atexit(__tcf_51,0,&__dso_handle);
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
  __cxa_atexit(__tcf_52,0,&__dso_handle);
  return;
}



/* address=00cc0cd0
   symbol=CSkillEvent::missileBeingFired */

/* non-virtual thunk to CSkillEvent::missileBeingFired(CMissile*) */

void __thiscall CSkillEvent::missileBeingFired(CSkillEvent *this,CMissile *param_1)

{
  missileBeingFired(this + -0x18,param_1);
  return;
}



/* address=00cc0ce0
   symbol=CSkillEvent::missileBeingFired */

/* CSkillEvent::missileBeingFired(CMissile*) */

void __thiscall CSkillEvent::missileBeingFired(CSkillEvent *this,CMissile *param_1)

{
  undefined4 uVar1;
  uint uVar2;
  TSafePointer *pTVar3;
  void *pvVar4;
  ulong uVar5;
  uint uVar6;

  pTVar3 = (TSafePointer *)Ogre::NedAllocImpl::allocBytes(0x10,(char *)0x0,0,(char *)0x0);
  *(undefined8 *)pTVar3 = 0;
  *(undefined4 *)(pTVar3 + 8) = 0xffffffff;
  if (param_1 != (CMissile *)0x0) {
                    /* try { // try from 00cc0d1c to 00cc0d20 has its CatchHandler @ 00cc0e09 */
    uVar1 = CRunicCore::addSafePointer((CRunicCore *)param_1,pTVar3);
    *(undefined4 *)(pTVar3 + 8) = uVar1;
    *(CMissile **)pTVar3 = param_1;
  }
  uVar2 = *(uint *)(this + 0xf8);
  if (uVar2 < *(uint *)(this + 0xfc)) {
    pvVar4 = *(void **)(this + 0xf0);
  }
  else if (*(long *)(this + 0xf0) == 0) {
    *(uint *)(this + 0xfc) = *(uint *)(this + 0x100);
    pvVar4 = operator_new__((ulong)*(uint *)(this + 0x100) << 3);
    *(void **)(this + 0xf0) = pvVar4;
    uVar2 = *(uint *)(this + 0xf8);
  }
  else {
    uVar6 = *(uint *)(this + 0xfc) + *(int *)(this + 0x100);
    pvVar4 = operator_new__((ulong)uVar6 << 3);
    if (*(int *)(this + 0xfc) != 0) {
      uVar2 = 0;
      do {
        uVar5 = (ulong)uVar2;
        uVar2 = uVar2 + 1;
        *(undefined8 *)((long)pvVar4 + uVar5 * 8) =
             *(undefined8 *)(*(long *)(this + 0xf0) + uVar5 * 8);
      } while (uVar2 < *(uint *)(this + 0xfc));
    }
    if (*(void **)(this + 0xf0) != (void *)0x0) {
      operator_delete__(*(void **)(this + 0xf0));
    }
    uVar2 = *(uint *)(this + 0xf8);
    *(void **)(this + 0xf0) = pvVar4;
    *(uint *)(this + 0xfc) = uVar6;
  }
  *(TSafePointer **)((long)pvVar4 + (ulong)uVar2 * 8) = pTVar3;
  *(int *)(this + 0xf8) = *(int *)(this + 0xf8) + 1;
  return;
}



/* address=00cc1100
   symbol=CSkillEvent::reset */

/* CSkillEvent::reset() */

void __thiscall CSkillEvent::reset(CSkillEvent *this)

{
  uint uVar1;
  long *plVar2;
  long lVar3;
  long lVar4;
  uint uVar5;
  undefined8 *puVar6;
  long lVar7;
  uint uVar8;

  plVar2 = *(long **)(this + 0x38);
  if (plVar2 != (long *)0x0) {
    (**(code **)(*plVar2 + 0x50))(plVar2,0);
  }
  if (*(int *)(this + 0xf8) != 0) {
    uVar8 = 0;
    do {
      while( true ) {
        if (uVar8 < *(uint *)(this + 0xfc)) {
          puVar6 = (undefined8 *)((ulong)uVar8 * 8 + *(long *)(this + 0xf0));
        }
        else {
          puVar6 = *(undefined8 **)(this + 0xf0);
        }
        if (*(long *)*puVar6 != 0) break;
LAB_00cc11a8:
        uVar8 = uVar8 + 1;
        if (*(uint *)(this + 0xf8) <= uVar8) goto LAB_00cc11b9;
      }
      if (uVar8 < *(uint *)(this + 0xfc)) {
        puVar6 = (undefined8 *)((ulong)uVar8 * 8 + *(long *)(this + 0xf0));
      }
      else {
        puVar6 = *(undefined8 **)(this + 0xf0);
      }
      lVar3 = *(long *)*puVar6;
      uVar1 = *(uint *)(lVar3 + 0x1d0);
      if (uVar1 == 0) goto LAB_00cc11a8;
      plVar2 = *(long **)(lVar3 + 0x1c8);
      uVar5 = 0;
      lVar4 = 8;
      if (this + 0x18 == (CSkillEvent *)*plVar2) {
        lVar7 = 0;
      }
      else {
        do {
          lVar7 = lVar4;
          uVar5 = uVar5 + 1;
          if (uVar1 <= uVar5) goto LAB_00cc11a8;
          lVar4 = lVar7 + 8;
        } while (this + 0x18 != *(CSkillEvent **)((long)plVar2 + lVar7));
      }
      uVar8 = uVar8 + 1;
      *(uint *)(lVar3 + 0x1d0) = uVar1 - 1;
      *(long *)((long)plVar2 + lVar7) = plVar2[uVar1 - 1];
    } while (uVar8 < *(uint *)(this + 0xf8));
  }
LAB_00cc11b9:
  *(undefined4 *)(this + 0xf8) = 0;
  *(undefined4 *)(this + 0xfc) = 0;
  if (*(void **)(this + 0xf0) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0xf0));
  }
  *(undefined8 *)(this + 0xf0) = 0;
  this[0x134] = (CSkillEvent)0x0;
  this[0x140] = (CSkillEvent)0x0;
  this[0x135] = (CSkillEvent)0x0;
  this[0x136] = (CSkillEvent)0x0;
  if (*(CRunicCore **)(this + 0x70) != (CRunicCore *)0x0) {
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(this + 0x70),(TSafePointer *)(this + 0x70),*(uint *)(this + 0x78));
    *(undefined8 *)(this + 0x70) = 0;
  }
  if (*(CRunicCore **)(this + 0x60) != (CRunicCore *)0x0) {
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(this + 0x60),(TSafePointer *)(this + 0x60),*(uint *)(this + 0x68));
    *(undefined8 *)(this + 0x60) = 0;
  }
  *(undefined8 *)(this + 0x90) = 0;
  if (*(CRunicCore **)(this + 0x50) != (CRunicCore *)0x0) {
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(this + 0x50),(TSafePointer *)(this + 0x50),*(uint *)(this + 0x58));
    *(undefined8 *)(this + 0x50) = 0;
  }
  return;
}



/* address=00cc12d0
   symbol=CSkillEvent::unitSpawnedFromUnitSpawner */

/* non-virtual thunk to CSkillEvent::unitSpawnedFromUnitSpawner(CUnitSpawner*, CPositionableObject*)
    */

void __thiscall
CSkillEvent::unitSpawnedFromUnitSpawner
          (CSkillEvent *this,CUnitSpawner *param_1,CPositionableObject *param_2)

{
  unitSpawnedFromUnitSpawner(this + -0x20,param_1,param_2);
  return;
}



/* address=00cc12e0
   symbol=CSkillEvent::unitSpawnedFromUnitSpawner */

/* CSkillEvent::unitSpawnedFromUnitSpawner(CUnitSpawner*, CPositionableObject*) */

void __thiscall
CSkillEvent::unitSpawnedFromUnitSpawner
          (CSkillEvent *this,CUnitSpawner *param_1,CPositionableObject *param_2)

{
  long *plVar1;
  CRunicCore *this_00;
  CRunicCore *this_01;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  long lVar6;
  long *plVar7;
  CCharacter *this_02;
  CGenericModel *pCVar8;
  long *plVar9;
  ulong uVar10;
  CSkillEvent *pCVar11;
  float local_40;
  undefined4 local_3c;
  long local_38 [3];

  if (param_2 != (CPositionableObject *)0x0) {
    lVar6 = __dynamic_cast(param_2,&CPositionableObject::typeinfo,&CMissile::typeinfo,0);
    if (lVar6 == 0) {
      this_02 = (CCharacter *)
                __dynamic_cast(param_2,&CPositionableObject::typeinfo,&CCharacter::typeinfo,0);
      if ((this_02 != (CCharacter *)0x0) && (*(CCharacter **)(this + 0x70) != (CCharacter *)0x0)) {
        uVar2 = CCharacter::alignment(*(CCharacter **)(this + 0x70));
        CCharacter::setAlignment(this_02,uVar2);
        (**(code **)(*(long *)this_02 + 0x318))
                  (this_02,*(undefined4 *)(*(long *)(this + 0x70) + 0x100),0);
        if (this[0x143] != (CSkillEvent)0x0) {
          CCharacter::addPet(*(CCharacter **)(this + 0x70),this_02);
        }
        if (this[0x14e] != (CSkillEvent)0x0) {
          std::string::string((string *)local_38,(string *)&::EMPTY_STRING);
                    /* try { // try from 00cc14f8 to 00cc155d has its CatchHandler @ 00cc1692 */
          lVar6 = (**(code **)(**(long **)(this + 0x70) + 0x1e0))();
          if (lVar6 == 0) {
            local_40 = DAT_00fa47fc;
            local_3c = 0;
          }
          else {
            uVar4 = CCharacter::getAnimationPlaying(*(CCharacter **)(this + 0x70));
            pCVar8 = (CGenericModel *)(**(code **)(**(long **)(this + 0x70) + 0x1e0))();
            CGenericModel::getAnimationName(pCVar8,uVar4);
            std::string::assign((string *)local_38);
            pCVar8 = (CGenericModel *)(**(code **)(**(long **)(this + 0x70) + 0x1e0))();
            local_3c = CGenericModel::getAnimationTime(pCVar8);
            lVar6 = (**(code **)(**(long **)(this + 0x70) + 0x1e0))();
            local_40 = *(float *)(lVar6 + 0x240);
          }
                    /* try { // try from 00cc1630 to 00cc168c has its CatchHandler @ 00cc1692 */
          if ((*(long *)(local_38[0] + -0x18) != 0) &&
             (lVar6 = (**(code **)(*(long *)this_02 + 0x1e0))(this_02), lVar6 != 0)) {
            pCVar8 = (CGenericModel *)(**(code **)(*(long *)this_02 + 0x1e0))(this_02);
            iVar5 = CGenericModel::getAnimationIndex(pCVar8,(string *)local_38);
            if (-1 < iVar5) {
              CCharacter::setAIPlayAnimation(this_02,(string *)local_38,false,DAT_00fa480c,local_40)
              ;
              (**(code **)(*(long *)this_02 + 0x300))(local_3c,this_02);
            }
          }
          std::string::~string((string *)local_38);
        }
        applyEffects((CBaseUnit *)this,(Vector3 *)this_02,false);
        if (this[0x142] != (CSkillEvent)0x0) {
          uVar2 = CCharacter::getEffectValue(this_02,0x2f,7);
          *(undefined4 *)(this + 0x15c) = uVar2;
        }
      }
    }
    else {
      this_00 = *(CRunicCore **)(this + 0x70);
      this_01 = *(CRunicCore **)(lVar6 + 0x220);
      if (this_00 != this_01) {
        if (this_01 != (CRunicCore *)0x0) {
          CRunicCore::removeSafePointer
                    (this_01,(TSafePointer *)(lVar6 + 0x220),*(uint *)(lVar6 + 0x228));
        }
        *(undefined8 *)(lVar6 + 0x220) = 0;
        if (this_00 != (CRunicCore *)0x0) {
          uVar2 = CRunicCore::addSafePointer(this_00,(TSafePointer *)(lVar6 + 0x220));
          *(undefined4 *)(lVar6 + 0x228) = uVar2;
        }
        *(CRunicCore **)(lVar6 + 0x220) = this_00;
      }
      uVar4 = *(uint *)(lVar6 + 0x1d0);
      pCVar11 = this + 0x18;
      if (uVar4 == 0) {
        plVar7 = *(long **)(lVar6 + 0x1c8);
      }
      else {
        plVar7 = *(long **)(lVar6 + 0x1c8);
        uVar3 = 0;
        plVar9 = plVar7;
        if (pCVar11 == (CSkillEvent *)*plVar7) {
          return;
        }
        do {
          uVar3 = uVar3 + 1;
          if (uVar4 <= uVar3) goto LAB_00cc13b8;
          plVar1 = plVar9 + 1;
          plVar9 = plVar9 + 1;
        } while (pCVar11 != (CSkillEvent *)*plVar1);
        if (uVar3 != 0xffffffff) {
          return;
        }
      }
LAB_00cc13b8:
      if (*(uint *)(lVar6 + 0x1d4) <= uVar4) {
        if (plVar7 == (long *)0x0) {
          *(uint *)(lVar6 + 0x1d4) = *(uint *)(lVar6 + 0x1d8);
          plVar7 = operator_new__((ulong)*(uint *)(lVar6 + 0x1d8) << 3);
          uVar4 = *(uint *)(lVar6 + 0x1d0);
          *(long **)(lVar6 + 0x1c8) = plVar7;
        }
        else {
          uVar3 = *(uint *)(lVar6 + 0x1d4) + *(int *)(lVar6 + 0x1d8);
          plVar7 = operator_new__((ulong)uVar3 << 3);
          if (*(int *)(lVar6 + 0x1d4) != 0) {
            uVar4 = 0;
            do {
              uVar10 = (ulong)uVar4;
              uVar4 = uVar4 + 1;
              plVar7[uVar10] = *(long *)(*(long *)(lVar6 + 0x1c8) + uVar10 * 8);
            } while (uVar4 < *(uint *)(lVar6 + 0x1d4));
          }
          if (*(void **)(lVar6 + 0x1c8) != (void *)0x0) {
            operator_delete__(*(void **)(lVar6 + 0x1c8));
          }
          uVar4 = *(uint *)(lVar6 + 0x1d0);
          *(long **)(lVar6 + 0x1c8) = plVar7;
          *(uint *)(lVar6 + 0x1d4) = uVar3;
        }
      }
      plVar7[uVar4] = (long)pCVar11;
      *(int *)(lVar6 + 0x1d0) = *(int *)(lVar6 + 0x1d0) + 1;
    }
  }
  return;
}



/* address=00cc16b0
   symbol=CSkillEvent::~CSkillEvent */

/* CSkillEvent::~CSkillEvent() */

void __thiscall CSkillEvent::~CSkillEvent(CSkillEvent *this)

{
  CSkillEvent *pCVar1;
  long lVar2;
  long *plVar3;
  uint uVar4;

  *(undefined ***)this = &PTR__CSkillEvent_00ff59f0;
  *(undefined ***)(this + 0x10) = &PTR__CSkillEvent_00ff5a58;
  *(undefined ***)(this + 0x18) = &PTR__CSkillEvent_00ff5a90;
  *(undefined ***)(this + 0x20) = &PTR__CSkillEvent_00ff5ad8;
                    /* try { // try from 00cc16e4 to 00cc18ea has its CatchHandler @ 00cc1a9b */
  reset(this);
  pCVar1 = this + 0xa8;
  if (*(int *)(this + 0xb0) != 0) {
    uVar4 = 0;
    do {
      lVar2 = (ulong)uVar4 * 8;
      plVar3 = (long *)(lVar2 + *(long *)pCVar1);
      if ((long *)*plVar3 != (long *)0x0) {
        (**(code **)(*(long *)*plVar3 + 8))();
        *(undefined8 *)(*(long *)pCVar1 + (ulong)uVar4 * 8) = 0;
        plVar3 = (long *)(lVar2 + *(long *)pCVar1);
      }
      *plVar3 = 0;
      uVar4 = uVar4 + 1;
    } while (uVar4 < *(uint *)(this + 0xb0));
  }
  *(undefined4 *)(this + 0xb0) = 0;
  *(undefined4 *)(this + 0xb4) = 0;
  if (*(void **)(this + 0xa8) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0xa8));
  }
  *(undefined8 *)(this + 0xa8) = 0;
  *(undefined4 *)(this + 0xe0) = 0;
  *(undefined4 *)(this + 0xe4) = 0;
  if (*(void **)(this + 0xd8) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0xd8));
  }
  *(undefined8 *)(this + 0xd8) = 0;
  *(undefined8 *)(this + 0x220) = 0;
  if (*(int *)(this + 0x118) != 0) {
    uVar4 = 0;
    do {
      lVar2 = (ulong)uVar4 * 8;
      plVar3 = (long *)(lVar2 + *(long *)(this + 0x110));
      if ((long *)*plVar3 != (long *)0x0) {
        (**(code **)(*(long *)*plVar3 + 8))();
        *(undefined8 *)(*(long *)(this + 0x110) + (ulong)uVar4 * 8) = 0;
        plVar3 = (long *)(lVar2 + *(long *)(this + 0x110));
      }
      *plVar3 = 0;
      uVar4 = uVar4 + 1;
    } while (uVar4 < *(uint *)(this + 0x118));
  }
  *(undefined4 *)(this + 0x118) = 0;
  *(undefined4 *)(this + 0x11c) = 0;
  if (*(void **)(this + 0x110) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x110));
  }
  *(undefined8 *)(this + 0x110) = 0;
  this[0x134] = (CSkillEvent)0x0;
  *(undefined8 *)(this + 0x40) = 0;
  *(undefined8 *)(this + 0x28) = 0;
  if (*(CRunicCore **)(this + 0x70) != (CRunicCore *)0x0) {
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(this + 0x70),(TSafePointer *)(this + 0x70),*(uint *)(this + 0x78));
    *(undefined8 *)(this + 0x70) = 0;
  }
  if (*(long **)(this + 0x170) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x170) + 8))();
    *(undefined8 *)(this + 0x170) = 0;
  }
  if (*(long **)(this + 0x38) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x38) + 8))();
    *(undefined8 *)(this + 0x38) = 0;
  }
  if (*(long **)(this + 0xa0) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0xa0) + 8))();
    *(undefined8 *)(this + 0xa0) = 0;
  }
  if (*(long **)(this + 0x128) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x128) + 8))();
    *(undefined8 *)(this + 0x128) = 0;
  }
  *(undefined ***)(this + 0x180) = &PTR__CSkillEventPause_00ff5c30;
  if (*(CRunicCore **)(this + 0x1c0) != (CRunicCore *)0x0) {
                    /* try { // try from 00cc1921 to 00cc1925 has its CatchHandler @ 00cc1ba0 */
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(this + 0x1c0),(TSafePointer *)(this + 0x1c0),*(uint *)(this + 0x1c8)
              );
  }
  *(undefined8 *)(this + 0x1c0) = 0;
  *(undefined4 *)(this + 0x1c8) = 0xffffffff;
                    /* try { // try from 00cc193e to 00cc1942 has its CatchHandler @ 00cc1b98 */
  CRunicCore::~CRunicCore((CRunicCore *)(this + 0x180));
  if (*(void **)(this + 0x110) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x110));
    *(undefined8 *)(this + 0x110) = 0;
  }
  if (*(void **)(this + 0xf0) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0xf0));
    *(undefined8 *)(this + 0xf0) = 0;
  }
  if (*(void **)(this + 0xd8) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0xd8));
    *(undefined8 *)(this + 0xd8) = 0;
  }
  if (*(void **)(this + 0xc0) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0xc0));
    *(undefined8 *)(this + 0xc0) = 0;
  }
  if (*(void **)(this + 0xa8) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0xa8));
    *(undefined8 *)(this + 0xa8) = 0;
  }
  if (*(CRunicCore **)(this + 0x80) != (CRunicCore *)0x0) {
                    /* try { // try from 00cc19e8 to 00cc19ec has its CatchHandler @ 00cc1b93 */
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(this + 0x80),(TSafePointer *)(this + 0x80),*(uint *)(this + 0x88));
  }
  *(undefined8 *)(this + 0x80) = 0;
  *(undefined4 *)(this + 0x88) = 0xffffffff;
  if (*(CRunicCore **)(this + 0x70) != (CRunicCore *)0x0) {
                    /* try { // try from 00cc1a11 to 00cc1a15 has its CatchHandler @ 00cc1b8e */
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(this + 0x70),(TSafePointer *)(this + 0x70),*(uint *)(this + 0x78));
  }
  *(undefined8 *)(this + 0x70) = 0;
  *(undefined4 *)(this + 0x78) = 0xffffffff;
  if (*(CRunicCore **)(this + 0x60) != (CRunicCore *)0x0) {
                    /* try { // try from 00cc1a35 to 00cc1a39 has its CatchHandler @ 00cc1b89 */
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(this + 0x60),(TSafePointer *)(this + 0x60),*(uint *)(this + 0x68));
  }
  *(undefined8 *)(this + 0x60) = 0;
  *(undefined4 *)(this + 0x68) = 0xffffffff;
  if (*(CRunicCore **)(this + 0x50) != (CRunicCore *)0x0) {
                    /* try { // try from 00cc1a59 to 00cc1a5d has its CatchHandler @ 00cc1b84 */
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(this + 0x50),(TSafePointer *)(this + 0x50),*(uint *)(this + 0x58));
  }
  *(undefined8 *)(this + 0x50) = 0;
  *(undefined4 *)(this + 0x58) = 0xffffffff;
  *(undefined ***)(this + 0x20) = &PTR__iUnitSpawner_00ff5cb0;
  *(undefined ***)(this + 0x18) = &PTR__iMissile_00fce3f0;
  *(undefined ***)(this + 0x10) = &PTR__iDamageShape_00ff5cf0;
  CRunicCore::~CRunicCore((CRunicCore *)this);
  return;
}



/* address=00cc1bb0
   symbol=CSkillEvent::~CSkillEvent */

/* non-virtual thunk to CSkillEvent::~CSkillEvent() */

void __thiscall CSkillEvent::~CSkillEvent(CSkillEvent *this)

{
  ~CSkillEvent(this + -0x20);
  return;
}



/* address=00cc1bc0
   symbol=CSkillEvent::~CSkillEvent */

/* non-virtual thunk to CSkillEvent::~CSkillEvent() */

void __thiscall CSkillEvent::~CSkillEvent(CSkillEvent *this)

{
  ~CSkillEvent(this + -0x18);
  return;
}



/* address=00cc1bd0
   symbol=CSkillEvent::~CSkillEvent */

/* non-virtual thunk to CSkillEvent::~CSkillEvent() */

void __thiscall CSkillEvent::~CSkillEvent(CSkillEvent *this)

{
  ~CSkillEvent(this + -0x10);
  return;
}



/* address=00cc1be0
   symbol=CSkillEvent::~CSkillEvent */

/* non-virtual thunk to CSkillEvent::~CSkillEvent() */

void __thiscall CSkillEvent::~CSkillEvent(CSkillEvent *this)

{
  ~CSkillEvent(this + -0x20);
  return;
}



/* address=00cc1bf0
   symbol=CSkillEvent::~CSkillEvent */

/* non-virtual thunk to CSkillEvent::~CSkillEvent() */

void __thiscall CSkillEvent::~CSkillEvent(CSkillEvent *this)

{
  ~CSkillEvent(this + -0x18);
  return;
}



/* address=00cc1c00
   symbol=CSkillEvent::~CSkillEvent */

/* non-virtual thunk to CSkillEvent::~CSkillEvent() */

void __thiscall CSkillEvent::~CSkillEvent(CSkillEvent *this)

{
  ~CSkillEvent(this + -0x10);
  return;
}



/* address=00cc1c10
   symbol=CSkillEvent::~CSkillEvent */

/* CSkillEvent::~CSkillEvent() */

void __thiscall CSkillEvent::~CSkillEvent(CSkillEvent *this)

{
  ~CSkillEvent(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}



/* address=00cc1c30
   symbol=CSkillEvent::characterEffectedByDamageShape */

/* non-virtual thunk to CSkillEvent::characterEffectedByDamageShape(CDamageShape*, CCharacter*,
   Ogre::Vector3*) */

void __thiscall
CSkillEvent::characterEffectedByDamageShape
          (CSkillEvent *this,CDamageShape *param_1,CCharacter *param_2,Vector3 *param_3)

{
  characterEffectedByDamageShape
            ((CDamageShape *)(this + -0x10),(CCharacter *)param_1,(Vector3 *)param_2);
  return;
}



/* address=00cc1c40
   symbol=CSkillEvent::characterEffectedByDamageShape */

/* CSkillEvent::characterEffectedByDamageShape(CDamageShape*, CCharacter*, Ogre::Vector3*) */

uint CSkillEvent::characterEffectedByDamageShape
               (CDamageShape *param_1,CCharacter *param_2,Vector3 *param_3)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  long lVar4;
  CPositionableObject *this;
  float *in_RCX;
  float fVar5;
  float fVar6;
  float in_XMM1_Da;
  float fVar7;
  undefined8 local_38 [2];

  local_38[0] = CPositionableObject::getPosition((CPositionableObject *)param_2,true);
  uVar2 = 0;
  cVar1 = canEffectPosObject((CSkillEvent *)param_1,(Vector3 *)local_38,
                             (CPositionableObject *)param_3);
  if (cVar1 != '\0') {
    if (*(int *)(param_2 + 0x104) == 4) {
      lVar4 = CSkillProperty::getOwnerCharacter(*(CSkillProperty **)(param_1 + 0x90));
      if ((lVar4 != 0) && (in_RCX != (float *)0x0)) {
        this = (CPositionableObject *)
               CSkillProperty::getOwnerCharacter(*(CSkillProperty **)(param_1 + 0x90));
        fVar5 = (float)CPositionableObject::getPosition(this,true);
        fVar7 = in_XMM1_Da;
        fVar6 = (float)CPositionableObject::getPosition((CPositionableObject *)param_3,true);
        fVar6 = fVar6 - fVar5;
        in_RCX[1] = 0.0;
        fVar7 = fVar7 - in_XMM1_Da;
        *in_RCX = fVar6;
        in_RCX[2] = fVar7;
        fVar5 = SQRT(fVar6 * fVar6 + 0.0 + fVar7 * fVar7);
        if (DAT_00fa87a0 < (double)fVar5) {
          fVar5 = DAT_00fa47fc / fVar5;
          *in_RCX = fVar6 * fVar5;
          in_RCX[1] = fVar5 * 0.0;
          in_RCX[2] = fVar5 * fVar7;
        }
      }
    }
    uVar2 = applyEffects((CBaseUnit *)param_1,param_3,SUB81(in_RCX,0));
    uVar3 = applyWeaponDamage((CSkillEvent *)param_1,(CCharacter *)param_3,(CItem *)0x0,DAT_00fa47fc
                              ,DAT_00fa47fc,false,false);
    uVar2 = uVar2 | uVar3;
    invokeHitSkills((CCharacter *)param_1);
  }
  return uVar2;
}



/* address=00cc1e30
   symbol=CSkillEvent::getCharacterCanBeAffectedByDamageShape */

/* non-virtual thunk to CSkillEvent::getCharacterCanBeAffectedByDamageShape(CDamageShape*,
   CCharacter*) */

void __thiscall
CSkillEvent::getCharacterCanBeAffectedByDamageShape
          (CSkillEvent *this,CDamageShape *param_1,CCharacter *param_2)

{
  getCharacterCanBeAffectedByDamageShape((CDamageShape *)(this + -0x10),(CCharacter *)param_1);
  return;
}



/* address=00cc1e40
   symbol=CSkillEvent::getCharacterCanBeAffectedByDamageShape */

/* CSkillEvent::getCharacterCanBeAffectedByDamageShape(CDamageShape*, CCharacter*) */

uint CSkillEvent::getCharacterCanBeAffectedByDamageShape(CDamageShape *param_1,CCharacter *param_2)

{
  CCharacter CVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  CCharacter *this;
  long *plVar5;
  CCharacter *in_RDX;
  long lVar6;
  undefined8 local_38 [3];

  local_38[0] = CPositionableObject::getPosition((CPositionableObject *)param_2,true);
  CVar1 = param_2[0x1a8];
  this = (CCharacter *)CSkill::getMasterOwnerCharacter(*(CSkill **)(param_1 + 0x28));
  if ((in_RDX != (CCharacter *)0x0) && (*(long *)(param_1 + 0x90) != 0)) {
    if ((CVar1 == (CCharacter)0x0) && (param_1[0x14d] == (CDamageShape)0x0)) {
      iVar3 = CCharacter::HP(in_RDX);
      if (iVar3 < 1) {
        return 0;
      }
    }
    else {
      iVar3 = CCharacter::HP(in_RDX);
      if (0 < iVar3) {
        return 0;
      }
    }
    if (((*(CSkillProperty **)(param_1 + 0x90))[0xb4] == (CSkillProperty)0x0) ||
       (in_RDX == *(CCharacter **)(param_1 + 0x80))) {
      if ((this == (CCharacter *)0x0) &&
         (this = (CCharacter *)
                 CSkillProperty::getOwnerCharacter(*(CSkillProperty **)(param_1 + 0x90)),
         this == (CCharacter *)0x0)) {
        return 1;
      }
      cVar2 = canEffectPosObject((CSkillEvent *)param_1,(Vector3 *)local_38,
                                 (CPositionableObject *)in_RDX);
      if ((cVar2 != '\0') &&
         ((*(int *)(*(long *)(param_1 + 0x90) + 0x74) == 0 ||
          (cVar2 = CBaseUnit::ISA(), cVar2 != '\0')))) {
        if (*(uint *)(param_1 + 0xe0) == 0) {
LAB_00cc1fa8:
          if (*(int *)(*(long *)(param_1 + 0x90) + 0x70) == 4) {
            return 1;
          }
          iVar3 = CSkill::getTargetType(*(CSkill **)(param_1 + 0x28));
          if (((((iVar3 != 10) || (in_RDX == this)) || (this == *(CCharacter **)(in_RDX + 0x640)))
              || ((*(CCharacter **)(this + 0x640) != (CCharacter *)0x0 &&
                  (in_RDX == *(CCharacter **)(this + 0x640))))) &&
             ((iVar3 = CSkill::getTargetType(*(CSkill **)(param_1 + 0x28)), iVar3 != 9 ||
              (this == *(CCharacter **)(in_RDX + 0x640))))) {
            uVar4 = CCharacter::isEnemy(this,in_RDX);
            if (*(long *)(this + 0x718) == 0) {
              return 1;
            }
            cVar2 = CAIManager::hasAIFlag(*(long *)(this + 0x718),1);
            if (cVar2 != '\0') {
              return 1;
            }
            iVar3 = CCharacter::alignment(this);
            if (iVar3 == 4) {
              return 1;
            }
            if (*(int *)(*(long *)(param_1 + 0x90) + 0x50) == 2) {
              return uVar4;
            }
            if (*(int *)(*(long *)(param_1 + 0x90) + 0x50) == 1) {
              return uVar4 ^ 1;
            }
          }
        }
        else {
          lVar6 = 0;
          uVar4 = 0;
          do {
            if (uVar4 < *(uint *)(param_1 + 0xe4)) {
              plVar5 = (long *)(lVar6 + *(long *)(param_1 + 0xd8));
            }
            else {
              plVar5 = *(long **)(param_1 + 0xd8);
            }
            if (*plVar5 == *(long *)(in_RDX + 0x1b0)) goto LAB_00cc1fa8;
            uVar4 = uVar4 + 1;
            lVar6 = lVar6 + 8;
          } while (uVar4 < *(uint *)(param_1 + 0xe0));
        }
      }
    }
  }
  return 0;
}



/* address=00cc3980
   symbol=CSkillEvent::disableAllDamageShapes */

/* WARNING: Removing unreachable block (ram,0x00cc3a95) */
/* CSkillEvent::disableAllDamageShapes() */

void __thiscall CSkillEvent::disableAllDamageShapes(CSkillEvent *this)

{
  int *piVar1;
  int iVar2;
  undefined8 *puVar3;
  uint uVar4;
  undefined8 *local_48;
  uint local_40;
  uint local_3c;
  undefined4 local_38;
  long local_28;
  allocator local_19;

  if (*(long *)(this + 0x38) != 0) {
    local_48 = (undefined8 *)0x0;
    local_40 = 0;
    local_3c = 0;
    local_38 = 10;
                    /* try { // try from 00cc39c8 to 00cc39cc has its CatchHandler @ 00cc3a47 */
    std::wstring::wstring((wstring_conflict *)&local_28,L"Damage Shape",&local_19);
                    /* try { // try from 00cc39d7 to 00cc39db has its CatchHandler @ 00cc3a88 */
    CEditorScene::GetObjectsCreatedByADescriptor
              (*(CEditorScene **)(this + 0x38),(wstring_conflict *)&local_28,(TArrayList *)&local_48
              );
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
    uVar4 = 0;
    if (local_40 != 0) {
      do {
        puVar3 = local_48;
        if (uVar4 < local_3c) {
          puVar3 = local_48 + uVar4;
        }
                    /* try { // try from 00cc3a0c to 00cc3a0e has its CatchHandler @ 00cc3a5a */
        (**(code **)(*(long *)*puVar3 + 0x40))((long *)*puVar3,0);
        uVar4 = uVar4 + 1;
      } while (uVar4 < local_40);
    }
    if (local_48 != (undefined8 *)0x0) {
      operator_delete__(local_48);
    }
  }
  return;
}



/* address=00cc3aa0
   symbol=CSkillEvent::addListeners */

/* WARNING: Removing unreachable block (ram,0x00cc4003) */
/* WARNING: Removing unreachable block (ram,0x00cc3fcd) */
/* CSkillEvent::addListeners() */

void __thiscall CSkillEvent::addListeners(CSkillEvent *this)

{
  CSkillEvent *pCVar1;
  long *plVar2;
  int *piVar3;
  int iVar4;
  long lVar5;
  uint uVar6;
  uint uVar7;
  long *plVar8;
  long lVar9;
  long *plVar10;
  void *pvVar11;
  ulong uVar12;
  ulong uVar13;
  long *plVar14;
  uint uVar15;
  long local_58 [2];
  long local_48;
  allocator local_3a;
  allocator local_39 [9];

  if (*(long *)(this + 0x38) != 0) {
                    /* try { // try from 00cc3ace to 00cc3ad2 has its CatchHandler @ 00cc3f9d */
    std::wstring::wstring((wstring_conflict *)&local_48,L"Damage Shape",local_39);
                    /* try { // try from 00cc3ada to 00cc3ade has its CatchHandler @ 00cc3fcb */
    plVar8 = (long *)CEditorScene::GetObjectsCreatedByADescriptor
                               (*(CEditorScene **)(this + 0x38),(wstring_conflict *)&local_48);
    if ((allocator *)(local_48 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar3 = (int *)(local_48 + -8);
      iVar4 = *piVar3;
      *piVar3 = *piVar3 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_48 + -0x18));
      }
    }
    if ((plVar8 != (long *)0x0) && ((int)plVar8[1] != 0)) {
      pCVar1 = this + 0x10;
      uVar12 = 0;
      do {
        if ((uint)uVar12 < *(uint *)((long)plVar8 + 0xc)) {
          plVar10 = (long *)(uVar12 * 8 + *plVar8);
        }
        else {
          plVar10 = (long *)*plVar8;
        }
        if ((*plVar10 != 0) &&
           (lVar9 = __dynamic_cast(*plVar10,&CEditorBaseObject::typeinfo,&CDamageShape::typeinfo,0),
           lVar9 != 0)) {
          if (this[0x14d] != (CSkillEvent)0x0) {
            *(undefined1 *)(lVar9 + 0x1a8) = 1;
          }
          if (0 < *(int *)(this + 0x168)) {
            *(int *)(lVar9 + 0x1f8) = *(int *)(this + 0x168);
          }
          uVar15 = *(uint *)(lVar9 + 0x1d0);
          if (uVar15 == 0) {
            plVar10 = *(long **)(lVar9 + 0x1c8);
LAB_00cc3bb0:
            if (*(uint *)(lVar9 + 0x1d4) <= uVar15) {
              if (plVar10 == (long *)0x0) {
                *(uint *)(lVar9 + 0x1d4) = *(uint *)(lVar9 + 0x1d8);
                plVar10 = operator_new__((ulong)*(uint *)(lVar9 + 0x1d8) << 3);
                uVar15 = *(uint *)(lVar9 + 0x1d0);
                *(long **)(lVar9 + 0x1c8) = plVar10;
              }
              else {
                uVar6 = *(uint *)(lVar9 + 0x1d4) + *(int *)(lVar9 + 0x1d8);
                plVar10 = operator_new__((ulong)uVar6 << 3);
                if (*(int *)(lVar9 + 0x1d4) != 0) {
                  uVar13 = 0;
                  do {
                    uVar15 = (int)uVar13 + 1;
                    plVar10[uVar13] = *(long *)(*(long *)(lVar9 + 0x1c8) + uVar13 * 8);
                    uVar13 = (ulong)uVar15;
                  } while (uVar15 < *(uint *)(lVar9 + 0x1d4));
                }
                if (*(void **)(lVar9 + 0x1c8) != (void *)0x0) {
                  operator_delete__(*(void **)(lVar9 + 0x1c8));
                }
                uVar15 = *(uint *)(lVar9 + 0x1d0);
                *(long **)(lVar9 + 0x1c8) = plVar10;
                *(uint *)(lVar9 + 0x1d4) = uVar6;
              }
            }
            plVar10[uVar15] = (long)pCVar1;
            *(int *)(lVar9 + 0x1d0) = *(int *)(lVar9 + 0x1d0) + 1;
LAB_00cc3c4b:
            lVar5 = *(long *)(this + 0x40);
          }
          else {
            plVar10 = *(long **)(lVar9 + 0x1c8);
            uVar6 = 0;
            plVar14 = plVar10;
            if (pCVar1 == (CSkillEvent *)*plVar10) goto LAB_00cc3c4b;
            do {
              uVar6 = uVar6 + 1;
              if (uVar15 <= uVar6) goto LAB_00cc3bb0;
              plVar2 = plVar14 + 1;
              plVar14 = plVar14 + 1;
            } while (pCVar1 != (CSkillEvent *)*plVar2);
            if (uVar6 == 0xffffffff) goto LAB_00cc3bb0;
            lVar5 = *(long *)(this + 0x40);
          }
          if (lVar5 == 0) {
            *(long *)(this + 0x40) = lVar9;
          }
        }
        uVar15 = (uint)uVar12 + 1;
        uVar12 = (ulong)uVar15;
      } while (uVar15 < *(uint *)(plVar8 + 1));
    }
                    /* try { // try from 00cc3c76 to 00cc3c7a has its CatchHandler @ 00cc3fd8 */
    std::wstring::wstring((wstring_conflict *)local_58,L"Unit Spawner",&local_3a);
                    /* try { // try from 00cc3c82 to 00cc3c86 has its CatchHandler @ 00cc3f8a */
    plVar8 = (long *)CEditorScene::GetObjectsCreatedByADescriptor
                               (*(CEditorScene **)(this + 0x38),(wstring_conflict *)local_58);
    if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar3 = (int *)(local_58[0] + -8);
      iVar4 = *piVar3;
      *piVar3 = *piVar3 + -1;
      UNLOCK();
      if (iVar4 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
      }
    }
    if ((plVar8 != (long *)0x0) && ((int)plVar8[1] != 0)) {
      pCVar1 = this + 0x20;
      uVar15 = 0;
      do {
        if (uVar15 < *(uint *)((long)plVar8 + 0xc)) {
          plVar10 = (long *)((ulong)uVar15 * 8 + *plVar8);
        }
        else {
          plVar10 = (long *)*plVar8;
        }
        if ((*plVar10 != 0) &&
           (lVar9 = __dynamic_cast(*plVar10,&CEditorBaseObject::typeinfo,&CUnitSpawner::typeinfo,0),
           lVar9 != 0)) {
          uVar6 = *(uint *)(this + 200);
          if (uVar6 < *(uint *)(this + 0xcc)) {
            pvVar11 = *(void **)(this + 0xc0);
          }
          else if (*(long *)(this + 0xc0) == 0) {
            *(uint *)(this + 0xcc) = *(uint *)(this + 0xd0);
            pvVar11 = operator_new__((ulong)*(uint *)(this + 0xd0) << 3);
            uVar6 = *(uint *)(this + 200);
            *(void **)(this + 0xc0) = pvVar11;
          }
          else {
            uVar6 = *(uint *)(this + 0xcc) + *(int *)(this + 0xd0);
            pvVar11 = operator_new__((ulong)uVar6 << 3);
            if (*(int *)(this + 0xcc) != 0) {
              uVar12 = 0;
              do {
                uVar7 = (int)uVar12 + 1;
                *(undefined8 *)((long)pvVar11 + uVar12 * 8) =
                     *(undefined8 *)(*(long *)(this + 0xc0) + uVar12 * 8);
                uVar12 = (ulong)uVar7;
              } while (uVar7 < *(uint *)(this + 0xcc));
            }
            if (*(void **)(this + 0xc0) != (void *)0x0) {
              operator_delete__(*(void **)(this + 0xc0));
            }
            *(void **)(this + 0xc0) = pvVar11;
            *(uint *)(this + 0xcc) = uVar6;
            uVar6 = *(uint *)(this + 200);
          }
          *(long *)((long)pvVar11 + (ulong)uVar6 * 8) = lVar9;
          *(int *)(this + 200) = *(int *)(this + 200) + 1;
          uVar6 = *(uint *)(lVar9 + 0x220);
          if (uVar6 == 0) {
            plVar10 = *(long **)(lVar9 + 0x218);
LAB_00cc3d68:
            if (*(uint *)(lVar9 + 0x224) <= uVar6) {
              if (plVar10 == (long *)0x0) {
                *(uint *)(lVar9 + 0x224) = *(uint *)(lVar9 + 0x228);
                plVar10 = operator_new__((ulong)*(uint *)(lVar9 + 0x228) * 8);
                uVar6 = *(uint *)(lVar9 + 0x220);
                *(long **)(lVar9 + 0x218) = plVar10;
              }
              else {
                uVar7 = *(uint *)(lVar9 + 0x224) + *(int *)(lVar9 + 0x228);
                plVar10 = operator_new__((ulong)uVar7 << 3);
                if (*(int *)(lVar9 + 0x224) != 0) {
                  uVar6 = 0;
                  do {
                    uVar12 = (ulong)uVar6;
                    uVar6 = uVar6 + 1;
                    plVar10[uVar12] = *(long *)(*(long *)(lVar9 + 0x218) + uVar12 * 8);
                  } while (uVar6 < *(uint *)(lVar9 + 0x224));
                }
                if (*(void **)(lVar9 + 0x218) != (void *)0x0) {
                  operator_delete__(*(void **)(lVar9 + 0x218));
                }
                uVar6 = *(uint *)(lVar9 + 0x220);
                *(long **)(lVar9 + 0x218) = plVar10;
                *(uint *)(lVar9 + 0x224) = uVar7;
              }
            }
            plVar10[uVar6] = (long)pCVar1;
            *(int *)(lVar9 + 0x220) = *(int *)(lVar9 + 0x220) + 1;
          }
          else {
            plVar10 = *(long **)(lVar9 + 0x218);
            uVar7 = 0;
            plVar14 = plVar10;
            if (pCVar1 != (CSkillEvent *)*plVar10) {
              do {
                uVar7 = uVar7 + 1;
                if (uVar6 <= uVar7) goto LAB_00cc3d68;
                plVar2 = plVar14 + 1;
                plVar14 = plVar14 + 1;
              } while (pCVar1 != (CSkillEvent *)*plVar2);
              if (uVar7 == 0xffffffff) goto LAB_00cc3d68;
            }
          }
        }
        uVar15 = uVar15 + 1;
      } while (uVar15 < *(uint *)(plVar8 + 1));
    }
  }
  return;
}



/* address=00cc4010
   symbol=CSkillEvent::stopAllParticles */

/* WARNING: Removing unreachable block (ram,0x00cc423f) */
/* WARNING: Removing unreachable block (ram,0x00cc4285) */
/* CSkillEvent::stopAllParticles(bool) */

void __thiscall CSkillEvent::stopAllParticles(CSkillEvent *this,bool param_1)

{
  int *piVar1;
  int iVar2;
  undefined8 *puVar3;
  uint uVar4;
  ulong uVar5;
  undefined8 *local_68;
  uint local_60;
  uint local_5c;
  undefined4 local_58;
  long local_48 [2];
  long local_38;
  allocator local_2a;
  allocator local_29 [9];

  if (*(long *)(this + 0x38) != 0) {
    local_68 = (undefined8 *)0x0;
    local_60 = 0;
    local_5c = 0;
    local_58 = 10;
                    /* try { // try from 00cc405d to 00cc4061 has its CatchHandler @ 00cc424a */
    std::wstring::wstring((wstring_conflict *)&local_38,L"Particle",local_29);
                    /* try { // try from 00cc406c to 00cc4070 has its CatchHandler @ 00cc4232 */
    CEditorScene::GetObjectsCreatedByADescriptor
              (*(CEditorScene **)(this + 0x38),(wstring_conflict *)&local_38,(TArrayList *)&local_68
              );
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
    uVar4 = 0;
    if (local_60 != 0) {
      do {
        puVar3 = local_68;
        if (uVar4 < local_5c) {
          puVar3 = local_68 + uVar4;
        }
                    /* try { // try from 00cc40aa to 00cc40af has its CatchHandler @ 00cc41f6 */
        (**(code **)(*(long *)*puVar3 + 0x200))();
        uVar4 = uVar4 + 1;
      } while (uVar4 < local_60);
    }
    local_60 = 0;
    local_5c = 0;
    if (local_68 != (undefined8 *)0x0) {
      operator_delete__(local_68);
    }
    local_68 = (undefined8 *)0x0;
                    /* try { // try from 00cc4180 to 00cc4184 has its CatchHandler @ 00cc427a */
    std::wstring::wstring((wstring_conflict *)local_48,L"Layout Link Particle",&local_2a);
                    /* try { // try from 00cc418f to 00cc4193 has its CatchHandler @ 00cc4278 */
    CEditorScene::GetObjectsCreatedByADescriptor
              (*(CEditorScene **)(this + 0x38),(wstring_conflict *)local_48,(TArrayList *)&local_68)
    ;
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
    if (local_60 != 0) {
      uVar5 = 0;
      do {
        puVar3 = local_68;
        if ((uint)uVar5 < local_5c) {
          puVar3 = local_68 + uVar5;
        }
                    /* try { // try from 00cc41d2 to 00cc41d6 has its CatchHandler @ 00cc41f6 */
        CLayout::stop((CLayout *)*puVar3,param_1);
        uVar4 = (uint)uVar5 + 1;
        uVar5 = (ulong)uVar4;
      } while (uVar4 < local_60);
    }
    if (local_68 != (undefined8 *)0x0) {
      operator_delete__(local_68);
      local_68 = (undefined8 *)0x0;
    }
  }
  if (*(int *)(this + 200) != 0) {
    uVar4 = 0;
    do {
      if (uVar4 < *(uint *)(this + 0xcc)) {
        puVar3 = (undefined8 *)((ulong)uVar4 * 8 + *(long *)(this + 0xc0));
      }
      else {
        puVar3 = *(undefined8 **)(this + 0xc0);
      }
      uVar4 = uVar4 + 1;
      CUnitSpawner::stopAllParticles((CUnitSpawner *)*puVar3);
    } while (uVar4 < *(uint *)(this + 200));
  }
  return;
}



/* address=00cc42a0
   symbol=CSkillEvent::stopEvent */

/* CSkillEvent::stopEvent() */

void __thiscall CSkillEvent::stopEvent(CSkillEvent *this)

{
  this[0x134] = (CSkillEvent)0x0;
  if (*(CLayout **)(this + 0x38) != (CLayout *)0x0) {
    CLayout::stop(*(CLayout **)(this + 0x38),false);
  }
  stopAllParticles(this,*(int *)(*(long *)(this + 0x28) + 0xec) != -1);
  disableAllDamageShapes(this);
  return;
}



/* address=00cc42e0
   symbol=CSkillEvent::resetEvent */

/* CSkillEvent::resetEvent() */

void __thiscall CSkillEvent::resetEvent(CSkillEvent *this)

{
  stopEvent(this);
  this[0x140] = (CSkillEvent)0x0;
  return;
}



/* address=00cc4300
   symbol=CSkillEvent::startEvent */

/* WARNING: Removing unreachable block (ram,0x00cc5a29) */
/* WARNING: Removing unreachable block (ram,0x00cc57b4) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CSkillEvent::startEvent(CBaseUnit*, CSkillProperty*, Ogre::Vector3, Ogre::Quaternion const&,
   CBaseUnit*, Ogre::Vector3 const*) */

undefined8
CSkillEvent::startEvent
          (undefined8 param_1_00,float param_2_00,CSkillEvent *param_1,CRunicCore *param_2,
          long param_5,Quaternion *param_6,CBaseUnit *param_7,float *param_8)

{
  int *piVar1;
  CSkillEvent *pCVar2;
  float fVar3;
  undefined8 uVar4;
  CParticle *this;
  code *pcVar5;
  bool bVar6;
  char cVar7;
  undefined4 uVar8;
  int iVar9;
  CRunicCore *this_00;
  float *pfVar10;
  CRunicCore *pCVar11;
  Vector3 *pVVar12;
  long lVar13;
  long *plVar14;
  CRunicCore *pCVar15;
  void *pvVar16;
  undefined8 *puVar17;
  undefined8 uVar18;
  uint uVar19;
  ulong uVar20;
  Vector3 *pVVar21;
  CRandomizer *this_01;
  uint uVar22;
  uint uVar23;
  float fVar24;
  float fVar25;
  float fVar26;
  float extraout_XMM1_Da;
  float extraout_XMM1_Da_00;
  float extraout_XMM1_Da_01;
  float extraout_XMM1_Da_02;
  float extraout_XMM1_Da_03;
  float extraout_XMM1_Da_04;
  float extraout_XMM1_Da_05;
  float extraout_XMM1_Da_06;
  float extraout_XMM1_Da_07;
  float extraout_XMM1_Da_08;
  float extraout_XMM1_Da_09;
  CBaseUnit *local_200;
  uint local_1f4;
  float local_1e8;
  float local_1e4;
  CBaseUnit *local_1e0;
  CPositionableObject *local_1d8;
  float local_1cc;
  long *local_198;
  uint local_190;
  uint local_18c;
  undefined4 local_188;
  long *local_178;
  uint local_170;
  uint local_16c;
  undefined4 local_168;
  Vector3 local_158 [16];
  undefined8 local_148;
  float local_140;
  float local_138;
  float local_134;
  float local_130;
  undefined8 local_128;
  float local_120;
  undefined8 local_118;
  float local_110;
  undefined8 local_108;
  float local_100;
  undefined8 local_f8;
  float local_f0;
  undefined8 local_e8;
  float local_e0;
  undefined8 local_d8;
  float local_d0;
  float local_c8;
  float local_c4;
  float local_c0;
  undefined8 local_b8;
  float local_b0;
  undefined8 local_a8;
  float local_a0;
  float local_98;
  float local_94;
  float local_90;
  undefined8 local_88;
  float local_80;
  undefined8 local_78;
  float local_70;
  undefined8 local_68;
  float local_60;
  long local_58 [2];
  long local_48;
  allocator local_3a;
  allocator local_39 [9];

  local_1cc = (float)((ulong)param_1_00 >> 0x20);
  local_1e4 = (float)param_1_00;
  if ((param_5 == 0) || (param_2 == (CRunicCore *)0x0)) {
    return 0;
  }
  if ((param_1[0x1dd] != (CSkillEvent)0x0) && (param_1[0x1dc] == (CSkillEvent)0x0)) {
    param_1[0x134] = (CSkillEvent)0x1;
    param_1[0x140] = (CSkillEvent)0x1;
    *(CRunicCore **)(param_1 + 400) = param_2;
    *(long *)(param_1 + 0x198) = param_5;
    *(float *)(param_1 + 0x1a0) = local_1e4;
    *(float *)(param_1 + 0x1a8) = param_2_00;
    *(float *)(param_1 + 0x1a4) = local_1cc;
    *(undefined4 *)(param_1 + 0x1ac) = *(undefined4 *)param_6;
    *(undefined4 *)(param_1 + 0x1b0) = *(undefined4 *)(param_6 + 4);
    *(undefined4 *)(param_1 + 0x1b4) = *(undefined4 *)(param_6 + 8);
    *(undefined4 *)(param_1 + 0x1b8) = *(undefined4 *)(param_6 + 0xc);
    TSafePointer<CBaseUnit>::setObject((TSafePointer<CBaseUnit> *)(param_1 + 0x1c0),param_7);
    pfVar10 = &Ogre::Vector3::ZERO;
    if (param_8 != (float *)0x0) {
      pfVar10 = param_8;
    }
    *(float *)(param_1 + 0x1d0) = *pfVar10;
    *(float *)(param_1 + 0x1d4) = pfVar10[1];
    fVar25 = pfVar10[2];
    param_1[0x1dc] = (CSkillEvent)0x1;
    *(float *)(param_1 + 0x1d8) = fVar25;
    uVar8 = UTILITIES::randomBetweenVolatile
                      (*(float *)(param_1 + 0x1e0),*(float *)(param_1 + 0x1e4));
    *(undefined4 *)(param_1 + 0x1e8) = uVar8;
    return 1;
  }
  param_1[0x1dc] = (CSkillEvent)0x0;
  *(undefined4 *)(param_1 + 0x1f0) = *(undefined4 *)(param_1 + 0x208);
  *(undefined4 *)(param_1 + 500) = *(undefined4 *)(param_1 + 0x20c);
  *(undefined4 *)(param_1 + 0x1f8) = *(undefined4 *)(param_1 + 0x210);
  local_200 = param_7;
  if (param_7 == (CBaseUnit *)0x0) {
    local_200 = *(CBaseUnit **)(*(long *)(param_1 + 0x28) + 0x40);
  }
  this_00 = (CRunicCore *)0x0;
  if (*(int *)(param_5 + 0x70) != 0xb) {
    this_00 = (CRunicCore *)local_200;
  }
  pCVar15 = *(CRunicCore **)(param_1 + 0x80);
  if (this_00 != pCVar15) {
    if (pCVar15 != (CRunicCore *)0x0) {
      CRunicCore::removeSafePointer
                (pCVar15,(TSafePointer *)(param_1 + 0x80),*(uint *)(param_1 + 0x88));
    }
    *(undefined8 *)(param_1 + 0x80) = 0;
    if (this_00 != (CRunicCore *)0x0) {
      uVar8 = CRunicCore::addSafePointer(this_00,(TSafePointer *)(param_1 + 0x80));
      *(undefined4 *)(param_1 + 0x88) = uVar8;
    }
    *(CRunicCore **)(param_1 + 0x80) = this_00;
  }
  *(undefined4 *)(param_1 + 0x15c) = *(undefined4 *)(param_1 + 0x158);
  fVar24 = (float)CSkill::getRange(*(CSkill **)(param_1 + 0x28));
  *(float *)(param_1 + 0x160) = fVar24;
  pfVar10 = (float *)(**(code **)(*(long *)param_2 + 0x130))(param_2);
  fVar25 = pfVar10[2];
  fVar26 = *pfVar10;
  *(undefined4 *)(param_1 + 0x200) = 0;
  *(float *)(param_1 + 0x204) = fVar25 * fVar24;
  *(float *)(param_1 + 0x1fc) = fVar24 * fVar26;
  local_1d8 = (CPositionableObject *)0x0;
  if (this_00 != (CRunicCore *)0x0) {
    local_1d8 = (CPositionableObject *)
                __dynamic_cast(this_00,&CBaseUnit::typeinfo,&CCharacter::typeinfo);
  }
  local_1e8 = param_2_00;
  if (param_1[0x14b] == (CSkillEvent)0x0) {
    if (this_00 == (CRunicCore *)0x0) {
LAB_00cc4b8a:
      if (param_8 != (float *)0x0) {
        fVar25 = SQRT((*param_8 - local_1e4) * (*param_8 - local_1e4) + 0.0 +
                      (param_8[2] - param_2_00) * (param_8[2] - param_2_00));
        *(float *)(param_1 + 0x160) = fVar25;
        fVar25 = fVar25 - *(float *)(param_2 + 0x194);
        *(uint *)(param_1 + 0x160) = (uint)fVar25 & -(uint)(0.0 < fVar25);
        fVar25 = *param_8;
        *(float *)(param_1 + 0x1f0) = fVar25;
        *(float *)(param_1 + 500) = param_8[1];
        fVar26 = param_8[2];
        *(float *)(param_1 + 0x1f8) = fVar26;
        *(float *)(param_1 + 0x1fc) = fVar25 - local_1e4;
        *(undefined4 *)(param_1 + 0x200) = 0;
        *(float *)(param_1 + 0x204) = fVar26 - param_2_00;
      }
    }
    else {
      local_78 = CPositionableObject::getPosition((CPositionableObject *)this_00,true);
      fVar25 = (float)local_78 - local_1e4;
      fVar25 = SQRT(fVar25 * fVar25 + 0.0 +
                    (extraout_XMM1_Da - param_2_00) * (extraout_XMM1_Da - param_2_00));
      *(float *)(param_1 + 0x160) = fVar25;
      fVar25 = fVar25 - (*(float *)(this_00 + 0x194) + *(float *)(param_2 + 0x194));
      *(uint *)(param_1 + 0x160) = (uint)fVar25 & -(uint)(0.0 < fVar25);
      local_70 = extraout_XMM1_Da;
      local_88 = CPositionableObject::getPosition((CPositionableObject *)this_00,true);
      *(undefined8 *)(param_1 + 0x1f0) = local_88;
      *(float *)(param_1 + 0x1f8) = extraout_XMM1_Da_00;
      *(float *)(param_1 + 500) = (float)((ulong)local_88 >> 0x20) - *(float *)(this_00 + 0x194);
      *(float *)(param_1 + 0x1fc) = (float)local_88 - local_1e4;
      *(float *)(param_1 + 0x204) = extraout_XMM1_Da_00 - param_2_00;
      *(undefined4 *)(param_1 + 0x200) = 0;
      local_80 = extraout_XMM1_Da_00;
    }
  }
  else if (this_00 == (CRunicCore *)0x0) {
    if (param_8 == (float *)0x0) goto LAB_00cc4b8a;
    local_1e4 = *param_8;
    local_1cc = param_8[1];
    local_1e8 = param_8[2];
  }
  else {
    local_68 = CPositionableObject::getPosition((CPositionableObject *)this_00,true);
    local_1e4 = (float)local_68;
    local_1cc = (float)((ulong)local_68 >> 0x20) - *(float *)(this_00 + 0x194);
    local_1e8 = extraout_XMM1_Da_05;
    local_60 = extraout_XMM1_Da_05;
  }
  fVar25 = (float)CSkill::getRange(*(CSkill **)(param_1 + 0x28));
  if (*(float *)(param_1 + 0x160) <= fVar25) {
    fVar25 = *(float *)(param_1 + 0x160);
  }
  *(long *)(param_1 + 0x90) = param_5;
  *(float *)(param_1 + 0x160) = fVar25;
  reset(param_1);
  param_1[0x140] = (CSkillEvent)0x1;
  *(long *)(param_1 + 0x90) = param_5;
  pCVar15 = *(CRunicCore **)(param_1 + 0x50);
  if (param_2 != pCVar15) {
    if (pCVar15 != (CRunicCore *)0x0) {
      CRunicCore::removeSafePointer
                (pCVar15,(TSafePointer *)(param_1 + 0x50),*(uint *)(param_1 + 0x58));
    }
    *(undefined8 *)(param_1 + 0x50) = 0;
    uVar8 = CRunicCore::addSafePointer(param_2,(TSafePointer *)(param_1 + 0x50));
    *(undefined4 *)(param_1 + 0x58) = uVar8;
    *(CRunicCore **)(param_1 + 0x50) = param_2;
  }
  if (param_2 != (CRunicCore *)0x0) {
    pCVar11 = (CRunicCore *)__dynamic_cast(param_2,&CBaseUnit::typeinfo,&CCharacter::typeinfo);
    pCVar15 = *(CRunicCore **)(param_1 + 0x60);
    if (pCVar11 != pCVar15) {
      if (pCVar15 != (CRunicCore *)0x0) {
        CRunicCore::removeSafePointer
                  (pCVar15,(TSafePointer *)(param_1 + 0x60),*(uint *)(param_1 + 0x68));
      }
      *(undefined8 *)(param_1 + 0x60) = 0;
      if (pCVar11 != (CRunicCore *)0x0) {
        uVar8 = CRunicCore::addSafePointer(pCVar11,(TSafePointer *)(param_1 + 0x60));
        *(undefined4 *)(param_1 + 0x68) = uVar8;
      }
      *(CRunicCore **)(param_1 + 0x60) = pCVar11;
    }
    pCVar11 = (CRunicCore *)CSkill::getMasterOwnerCharacter(*(CSkill **)(param_1 + 0x28));
    pCVar15 = *(CRunicCore **)(param_1 + 0x70);
    if (pCVar11 != pCVar15) {
      if (pCVar15 != (CRunicCore *)0x0) {
        CRunicCore::removeSafePointer
                  (pCVar15,(TSafePointer *)(param_1 + 0x70),*(uint *)(param_1 + 0x78));
      }
      *(undefined8 *)(param_1 + 0x70) = 0;
      if (pCVar11 != (CRunicCore *)0x0) {
        uVar8 = CRunicCore::addSafePointer(pCVar11,(TSafePointer *)(param_1 + 0x70));
        *(undefined4 *)(param_1 + 0x78) = uVar8;
      }
      *(CRunicCore **)(param_1 + 0x70) = pCVar11;
    }
    if (*(long *)(param_1 + 0x60) != 0) {
      pVVar12 = (Vector3 *)CSkill::getMasterOwnerCharacter(*(CSkill **)(param_1 + 0x28));
      if ((((pVVar12 == (Vector3 *)0x0) ||
           (iVar9 = CSkill::getTargetType(*(CSkill **)(param_1 + 0x28)), iVar9 == 10)) ||
          (iVar9 = CSkill::getTargetType(*(CSkill **)(param_1 + 0x28)), iVar9 == 3)) ||
         ((iVar9 = CSkill::getTargetType(*(CSkill **)(param_1 + 0x28)), iVar9 != 9 ||
          (pVVar21 = *(Vector3 **)(pVVar12 + 0x640), pVVar21 == (Vector3 *)0x0)))) {
        pVVar21 = pVVar12;
      }
      applyEffects((CBaseUnit *)param_1,pVVar21,false);
    }
    plVar14 = *(long **)(param_1 + 0x38);
    param_1[0x134] = (CSkillEvent)0x1;
    if (plVar14 != (long *)0x0) {
      (**(code **)(*plVar14 + 0x50))(plVar14,0);
      if ((*(long *)(param_1 + 0x60) == 0) || (*(int *)(param_1 + 0x108) == 0)) {
        local_98 = Ogre::Vector3::ZERO;
        local_90 = DAT_014241b4;
        local_94 = DAT_014241b0;
        if (this_00 != (CRunicCore *)0x0) {
          fVar25 = *(float *)(param_1 + 0x164);
          if ((((fVar25 != 0.0) || (NAN(fVar25))) &&
              (lVar13 = __dynamic_cast(this_00,&CBaseUnit::typeinfo,&CCharacter::typeinfo),
              local_98 = Ogre::Vector3::ZERO, local_90 = DAT_014241b4, local_94 = DAT_014241b0,
              lVar13 != 0)) &&
             ((*(char *)(lVar13 + 0x321) != '\0' &&
              (*(float *)(lVar13 + 0x28c) <= *(float *)(lVar13 + 0x290) &&
               *(float *)(lVar13 + 0x290) != *(float *)(lVar13 + 0x28c))))) {
            pfVar10 = (float *)(**(code **)(*(long *)this_00 + 0x130))(this_00);
            local_98 = fVar25 * *pfVar10;
            local_90 = pfVar10[2] * fVar25;
            local_94 = pfVar10[1] * fVar25;
          }
        }
        local_90 = local_90 + local_1e8;
        local_94 = local_94 + local_1cc;
        local_98 = local_98 + local_1e4;
        CPositionableObject::setPosition
                  (*(CPositionableObject **)(param_1 + 0x38),(Vector3 *)&local_98);
        iVar9 = CSkill::getTargetType(*(CSkill **)(param_1 + 0x28));
        if (((iVar9 == 1) ||
            (iVar9 = CSkill::getTargetType(*(CSkill **)(param_1 + 0x28)), iVar9 == 0xb)) ||
           ((iVar9 = CSkill::getTargetType(*(CSkill **)(param_1 + 0x28)), iVar9 == 6 ||
            (iVar9 = CSkill::getTargetType(*(CSkill **)(param_1 + 0x28)), iVar9 == 5)))) {
          local_b8 = CPositionableObject::getPosition((CPositionableObject *)param_2,true);
          local_b0 = extraout_XMM1_Da_08;
          local_a8 = CPositionableObject::getPosition
                               (*(CPositionableObject **)(param_1 + 0x38),true);
          fVar25 = (float)local_a8 - (float)local_b8;
          local_f0 = extraout_XMM1_Da_09 - local_b0;
          local_f8 = (ulong)(uint)fVar25;
          local_a0 = extraout_XMM1_Da_09;
          if (DAT_00fa4810 < SQRT(fVar25 * fVar25 + 0.0 + local_f0 * local_f0)) {
            Ogre::Vector3::normalise((Vector3 *)&local_f8);
            pcVar5 = *(code **)(**(long **)(param_1 + 0x38) + 0x108);
            local_c0 = Ogre::Vector3::UNIT_Y * local_f8._4_4_ - DAT_01424b38 * (float)local_f8;
            local_c4 = (float)local_f8 * DAT_01424b3c - Ogre::Vector3::UNIT_Y * local_f0;
            local_c8 = local_f0 * DAT_01424b38 - DAT_01424b3c * local_f8._4_4_;
            Ogre::Quaternion::FromAxes
                      (local_158,(Vector3 *)&local_c8,(Vector3 *)&Ogre::Vector3::UNIT_Y);
            (*pcVar5)(*(undefined8 *)(param_1 + 0x38),local_158);
            goto LAB_00cc4909;
          }
        }
        (**(code **)(**(long **)(param_1 + 0x38) + 0x108))(*(long **)(param_1 + 0x38),param_6);
      }
      else {
        local_f8 = getBonePosition(param_1);
        local_f0 = extraout_XMM1_Da_06;
        CPositionableObject::setPosition
                  (*(CPositionableObject **)(param_1 + 0x38),(Vector3 *)&local_f8);
        pcVar5 = *(code **)(**(long **)(param_1 + 0x38) + 0x118);
        uVar18 = (**(code **)(**(long **)(param_1 + 0x60) + 0xe8))();
        (*pcVar5)(*(undefined8 *)(param_1 + 0x38),uVar18,0);
      }
LAB_00cc4909:
      pCVar2 = param_1 + 0xa8;
      (**(code **)(**(long **)(param_1 + 0x38) + 0x50))(*(long **)(param_1 + 0x38),1);
      CLayout::start(*(CLayout **)(param_1 + 0x38));
      local_168 = 10;
      local_170 = 0;
      local_16c = 0;
      local_178 = (long *)0x0;
      if (*(int *)(param_1 + 0xb0) != 0) {
        uVar22 = 0;
        do {
          lVar13 = (ulong)uVar22 * 8;
          plVar14 = (long *)(lVar13 + *(long *)pCVar2);
          if ((long *)*plVar14 != (long *)0x0) {
                    /* try { // try from 00cc498a to 00cc498c has its CatchHandler @ 00cc5743 */
            (**(code **)(*(long *)*plVar14 + 8))();
            *(undefined8 *)(*(long *)pCVar2 + (ulong)uVar22 * 8) = 0;
            plVar14 = (long *)(lVar13 + *(long *)pCVar2);
          }
          *plVar14 = 0;
          uVar22 = uVar22 + 1;
        } while (uVar22 < *(uint *)(param_1 + 0xb0));
      }
      *(undefined4 *)(param_1 + 0xb0) = 0;
      *(undefined4 *)(param_1 + 0xb4) = 0;
      if (*(void **)(param_1 + 0xa8) != (void *)0x0) {
        operator_delete__(*(void **)(param_1 + 0xa8));
      }
      *(undefined8 *)(param_1 + 0xa8) = 0;
                    /* try { // try from 00cc49f7 to 00cc49fb has its CatchHandler @ 00cc5a14 */
      std::wstring::wstring((wstring_conflict *)&local_48,L"Emitter",local_39);
                    /* try { // try from 00cc4a13 to 00cc4a17 has its CatchHandler @ 00cc5a0f */
      CEditorScene::GetObjectsCreatedByADescriptor
                (*(CEditorScene **)(param_1 + 0x38),(wstring_conflict *)&local_48,
                 (TArrayList *)&local_178);
      if ((allocator *)(local_48 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
      {
        LOCK();
        piVar1 = (int *)(local_48 + -8);
        iVar9 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar9 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_48 + -0x18));
        }
      }
      uVar22 = 0;
      if (local_170 != 0) {
        do {
          if (uVar22 < local_16c) {
            lVar13 = local_178[uVar22];
            iVar9 = *(int *)(lVar13 + 0x128);
          }
          else {
            lVar13 = *local_178;
            iVar9 = *(int *)(lVar13 + 0x128);
          }
          if (iVar9 == 3) {
            uVar18 = *(undefined8 *)(lVar13 + 0x110);
            uVar4 = *(undefined8 *)(*(long *)(lVar13 + 0x108) + 0x48);
                    /* try { // try from 00cc4ab0 to 00cc4ab4 has its CatchHandler @ 00cc5743 */
            pCVar15 = (CRunicCore *)Ogre::NedAllocImpl::allocBytes(0x20,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00cc4abb to 00cc4abf has its CatchHandler @ 00cc57f1 */
            CRunicCore::CRunicCore(pCVar15);
            *(undefined ***)pCVar15 = &PTR__CLineEmitterWrapper_00ff5bb0;
            *(undefined8 *)(pCVar15 + 0x10) = uVar4;
            *(undefined8 *)(pCVar15 + 0x18) = uVar18;
            uVar19 = *(uint *)(param_1 + 0xb0);
            if (uVar19 < *(uint *)(param_1 + 0xb4)) {
              pvVar16 = *(void **)(param_1 + 0xa8);
            }
            else if (*(long *)(param_1 + 0xa8) == 0) {
              *(uint *)(param_1 + 0xb4) = *(uint *)(param_1 + 0xb8);
                    /* try { // try from 00cc5604 to 00cc5608 has its CatchHandler @ 00cc5743 */
              pvVar16 = operator_new__((ulong)*(uint *)(param_1 + 0xb8) * 8);
              *(void **)(param_1 + 0xa8) = pvVar16;
              uVar19 = *(uint *)(param_1 + 0xb0);
            }
            else {
              uVar23 = *(uint *)(param_1 + 0xb4) + *(int *)(param_1 + 0xb8);
                    /* try { // try from 00cc4b02 to 00cc4b06 has its CatchHandler @ 00cc5743 */
              pvVar16 = operator_new__((ulong)uVar23 << 3);
              if (*(int *)(param_1 + 0xb4) != 0) {
                uVar19 = 0;
                do {
                  uVar20 = (ulong)uVar19;
                  uVar19 = uVar19 + 1;
                  *(undefined8 *)((long)pvVar16 + uVar20 * 8) =
                       *(undefined8 *)(*(long *)pCVar2 + uVar20 * 8);
                } while (uVar19 < *(uint *)(param_1 + 0xb4));
              }
              if (*(void **)(param_1 + 0xa8) != (void *)0x0) {
                operator_delete__(*(void **)(param_1 + 0xa8));
              }
              uVar19 = *(uint *)(param_1 + 0xb0);
              *(void **)(param_1 + 0xa8) = pvVar16;
              *(uint *)(param_1 + 0xb4) = uVar23;
            }
            *(CRunicCore **)((long)pvVar16 + (ulong)uVar19 * 8) = pCVar15;
            *(int *)(param_1 + 0xb0) = *(int *)(param_1 + 0xb0) + 1;
          }
          uVar22 = uVar22 + 1;
        } while (uVar22 < local_170);
      }
      local_170 = 0;
      local_16c = 0;
      if (local_178 != (long *)0x0) {
        operator_delete__(local_178);
      }
      local_178 = (long *)0x0;
                    /* try { // try from 00cc4d7f to 00cc4d83 has its CatchHandler @ 00cc5801 */
      std::wstring::wstring((wstring_conflict *)local_58,L"Layout Link Particle",&local_3a);
                    /* try { // try from 00cc4d90 to 00cc4d94 has its CatchHandler @ 00cc57a7 */
      CEditorScene::GetObjectsCreatedByADescriptor
                (*(CEditorScene **)(param_1 + 0x38),(wstring_conflict *)local_58,
                 (TArrayList *)&local_178);
      if ((allocator *)(local_58[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_58[0] + -8);
        iVar9 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar9 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
        }
      }
      local_198 = (long *)0x0;
      local_190 = 0;
      local_18c = 0;
      local_188 = 5;
      if (local_170 != 0) {
        local_1f4 = 0;
        do {
          plVar14 = local_178;
          if (local_1f4 < local_16c) {
            plVar14 = local_178 + local_1f4;
          }
          this = *(CParticle **)(*plVar14 + 0x1f0);
          if (this != (CParticle *)0x0) {
                    /* try { // try from 00cc4e25 to 00cc4e9a has its CatchHandler @ 00cc5806 */
            CParticle::getAllEmitters(this,(TArrayList *)&local_198);
          }
          if (local_190 != 0) {
            uVar22 = 0;
            do {
              plVar14 = local_198;
              if (uVar22 < local_18c) {
                plVar14 = local_198 + uVar22;
              }
              iVar9 = std::string::compare((char *)(*plVar14 + 0x128));
              if (iVar9 == 0) {
                plVar14 = local_198;
                if (uVar22 < local_18c) {
                  plVar14 = local_198 + uVar22;
                }
                lVar13 = *plVar14;
                pCVar15 = (CRunicCore *)
                          Ogre::NedAllocImpl::allocBytes(0x20,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00cc4ea1 to 00cc4ea5 has its CatchHandler @ 00cc57bf */
                CRunicCore::CRunicCore(pCVar15);
                *(undefined ***)pCVar15 = &PTR__CLineEmitterWrapper_00ff5bb0;
                *(CParticle **)(pCVar15 + 0x10) = this;
                *(long *)(pCVar15 + 0x18) = lVar13;
                uVar19 = *(uint *)(param_1 + 0xb0);
                if (uVar19 < *(uint *)(param_1 + 0xb4)) {
                  pvVar16 = *(void **)(param_1 + 0xa8);
                }
                else if (*(long *)(param_1 + 0xa8) == 0) {
                  *(uint *)(param_1 + 0xb4) = *(uint *)(param_1 + 0xb8);
                    /* try { // try from 00cc55c4 to 00cc55c8 has its CatchHandler @ 00cc5806 */
                  pvVar16 = operator_new__((ulong)*(uint *)(param_1 + 0xb8) * 8);
                  *(void **)(param_1 + 0xa8) = pvVar16;
                  uVar19 = *(uint *)(param_1 + 0xb0);
                }
                else {
                  uVar23 = *(uint *)(param_1 + 0xb4) + *(int *)(param_1 + 0xb8);
                    /* try { // try from 00cc4ee8 to 00cc4f9b has its CatchHandler @ 00cc5806 */
                  pvVar16 = operator_new__((ulong)uVar23 << 3);
                  if (*(int *)(param_1 + 0xb4) != 0) {
                    uVar20 = 0;
                    do {
                      uVar19 = (int)uVar20 + 1;
                      *(undefined8 *)((long)pvVar16 + uVar20 * 8) =
                           *(undefined8 *)(*(long *)pCVar2 + uVar20 * 8);
                      uVar20 = (ulong)uVar19;
                    } while (uVar19 < *(uint *)(param_1 + 0xb4));
                  }
                  if (*(void **)(param_1 + 0xa8) != (void *)0x0) {
                    operator_delete__(*(void **)(param_1 + 0xa8));
                  }
                  uVar19 = *(uint *)(param_1 + 0xb0);
                  *(void **)(param_1 + 0xa8) = pvVar16;
                  *(uint *)(param_1 + 0xb4) = uVar23;
                }
                *(CRunicCore **)((long)pvVar16 + (ulong)uVar19 * 8) = pCVar15;
                *(int *)(param_1 + 0xb0) = *(int *)(param_1 + 0xb0) + 1;
              }
              uVar22 = uVar22 + 1;
            } while (uVar22 < local_190);
          }
          local_1f4 = local_1f4 + 1;
        } while (local_1f4 < local_170);
      }
      *(float *)(param_1 + 0x15c) = _DAT_00ff4020 + *(float *)(param_1 + 0x15c);
      updateEvent(0.0);
      if (local_198 != (long *)0x0) {
        operator_delete__(local_198);
        local_198 = (long *)0x0;
      }
      if (local_178 != (long *)0x0) {
        operator_delete__(local_178);
        local_178 = (long *)0x0;
      }
    }
  }
  lVar13 = CSkill::getOwnerCharacter(*(CSkill **)(param_1 + 0x28));
  if ((lVar13 != 0) && (*(long *)(param_1 + 0x170) != 0)) {
    plVar14 = *(long **)(param_1 + 0x80);
    fVar26 = Ogre::Vector3::ZERO;
    fVar25 = DAT_014241b0;
    fVar24 = DAT_014241b4;
    if (plVar14 != (long *)0x0) {
      fVar3 = *(float *)(param_1 + 0x164);
      if ((((fVar3 != 0.0) || (NAN(fVar3))) &&
          (lVar13 = __dynamic_cast(plVar14,&CBaseUnit::typeinfo,&CCharacter::typeinfo),
          fVar26 = Ogre::Vector3::ZERO, fVar25 = DAT_014241b0, fVar24 = DAT_014241b4, lVar13 != 0))
         && ((*(char *)(lVar13 + 0x321) != '\0' &&
             (*(float *)(lVar13 + 0x28c) <= *(float *)(lVar13 + 0x290) &&
              *(float *)(lVar13 + 0x290) != *(float *)(lVar13 + 0x28c))))) {
        pfVar10 = (float *)(**(code **)(*plVar14 + 0x130))(plVar14);
        fVar26 = fVar3 * *pfVar10;
        fVar25 = pfVar10[1] * fVar3;
        fVar24 = pfVar10[2] * fVar3;
      }
    }
    local_f0 = fVar24 + *(float *)(param_1 + 0x1f8);
    local_f8 = CONCAT44(fVar25 + *(float *)(param_1 + 500),fVar26 + *(float *)(param_1 + 0x1f0));
    CPathController::setArrayOfVectors(*(CPathController **)(param_1 + 0x170),(float *)&local_f8,3);
    *(undefined1 *)(*(long *)(param_1 + 0x170) + 0x134) = 1;
    plVar14 = (long *)CSkill::getOwnerCharacter(*(CSkill **)(param_1 + 0x28));
    (**(code **)(*plVar14 + 0x310))(plVar14,*(undefined8 *)(param_1 + 0x170));
  }
  if ((param_1[0x138] == (CSkillEvent)0x0) || (this_00 == (CRunicCore *)0x0)) {
    bVar6 = false;
  }
  else {
    cVar7 = CBaseUnit::ISA((CBaseUnit *)this_00,0x1d);
    if (cVar7 == '\0') {
      if (local_1d8 == (CPositionableObject *)0x0) {
        iVar9 = CSkill::getTargetType(*(CSkill **)(param_1 + 0x28));
        if ((iVar9 != 7) &&
           (iVar9 = CSkill::getTargetType(*(CSkill **)(param_1 + 0x28)), iVar9 != 8))
        goto LAB_00cc583f;
        applyEffects((CBaseUnit *)param_1,(Vector3 *)this_00,false);
        bVar6 = true;
      }
      else {
        if (*(CPositionableObject **)(param_1 + 0x50) == (CPositionableObject *)0x0) {
          pVVar12 = (Vector3 *)0x0;
        }
        else {
          pVVar12 = (Vector3 *)&local_f8;
          local_e8 = CPositionableObject::getPosition
                               (*(CPositionableObject **)(param_1 + 0x50),true);
          local_e0 = extraout_XMM1_Da_01;
          local_d8 = CPositionableObject::getPosition(local_1d8,true);
          local_f0 = extraout_XMM1_Da_02 - local_e0;
          local_f8 = CONCAT44((float)((ulong)local_d8 >> 0x20) - local_e8._4_4_,
                              (float)local_d8 - (float)local_e8);
          local_d0 = extraout_XMM1_Da_02;
          Ogre::Vector3::normalise(pVVar12);
        }
        applyEffects((CBaseUnit *)param_1,(Vector3 *)local_1d8,SUB81(pVVar12,0));
        applyWeaponDamage(param_1,(CCharacter *)local_1d8,(CItem *)0x0,DAT_00fa47fc,DAT_00fa47fc,
                          false,false);
        invokeHitSkills((CCharacter *)param_1);
        bVar6 = true;
      }
    }
    else {
      cVar7 = effectsTargetEnemy(param_1,(CBaseUnit *)this_00);
      if (cVar7 == '\0') {
LAB_00cc583f:
        bVar6 = true;
      }
      else {
        (**(code **)(*(long *)this_00 + 0x280))(this_00,*(undefined8 *)(param_1 + 0x50));
        bVar6 = true;
      }
    }
  }
  iVar9 = *(int *)(param_1 + 0x48);
  if (iVar9 < 7) {
    if (iVar9 < 4) {
      if ((iVar9 == 0) && (0.0 < *(float *)(*(long *)(param_1 + 0x90) + 0xa8))) {
        CGameSpeed::getSingleton();
        CGameSpeed::addSpeedModifier(*(undefined4 *)(*(long *)(param_1 + 0x90) + 0xa8),0);
      }
      goto LAB_00cc529d;
    }
  }
  else if (iVar9 != 8) goto LAB_00cc529d;
  if ((!bVar6) && (local_1d8 != (CPositionableObject *)0x0)) {
    if (*(CPositionableObject **)(param_1 + 0x50) == (CPositionableObject *)0x0) {
      applyEffects((CBaseUnit *)param_1,(Vector3 *)local_1d8,false);
    }
    else {
      local_118 = CPositionableObject::getPosition(*(CPositionableObject **)(param_1 + 0x50),true);
      local_110 = extraout_XMM1_Da_03;
      local_108 = CPositionableObject::getPosition(local_1d8,true);
      local_f0 = extraout_XMM1_Da_04 - local_110;
      local_f8 = CONCAT44((float)((ulong)local_108 >> 0x20) - local_118._4_4_,
                          (float)local_108 - (float)local_118);
      local_100 = extraout_XMM1_Da_04;
      Ogre::Vector3::normalise((Vector3 *)&local_f8);
      applyEffects((CBaseUnit *)param_1,(Vector3 *)local_1d8,SUB81((Vector3 *)&local_f8,0));
    }
  }
LAB_00cc529d:
  if (param_8 == (float *)0x0) {
    local_130 = local_1e8;
    local_134 = local_1cc;
    local_138 = local_1e4;
    local_128 = 0;
    local_120 = 0.0;
    if (this_00 == (CRunicCore *)0x0) {
      local_128 = CONCAT44(local_1cc,local_1e4);
      local_120 = local_1e8;
    }
    else {
      local_148 = CPositionableObject::getPosition((CPositionableObject *)this_00,true);
      local_140 = extraout_XMM1_Da_07;
      local_128 = local_148;
      local_120 = extraout_XMM1_Da_07;
    }
  }
  else {
    local_128 = *(undefined8 *)param_8;
    local_120 = param_8[2];
    local_130 = local_1e8;
    local_134 = local_1cc;
    local_138 = local_1e4;
  }
  local_200 = (CBaseUnit *)this_00;
  local_1e0 = (CBaseUnit *)param_2;
  if (param_1[0x13a] != (CSkillEvent)0x0) {
    local_138 = (float)local_128;
    local_134 = local_128._4_4_;
    local_130 = local_120;
    local_200 = (CBaseUnit *)0x0;
    local_1e0 = (CBaseUnit *)this_00;
  }
  if (*(int *)(param_1 + 0x130) == 0) {
    if (*(int *)(param_1 + 0x118) != 0) {
      uVar22 = 0;
      do {
        if (uVar22 < *(uint *)(param_1 + 0x11c)) {
          puVar17 = (undefined8 *)((ulong)uVar22 * 8 + *(long *)(param_1 + 0x110));
        }
        else {
          puVar17 = *(undefined8 **)(param_1 + 0x110);
        }
        uVar22 = uVar22 + 1;
        CExecuteSkillProps::executeSkill
                  ((CExecuteSkillProps *)*puVar17,local_1e0,(Vector3 *)&local_138,param_6,
                   (Vector3 *)&local_128,local_200,*(int *)(*(long *)(param_1 + 0x28) + 0xdc));
      } while (uVar22 < *(uint *)(param_1 + 0x118));
    }
  }
  else {
    this_01 = *(CRandomizer **)(param_1 + 0x128);
    if ((this_01 != (CRandomizer *)0x0) && (0 < *(int *)(param_1 + 0x130))) {
      iVar9 = 0;
      while( true ) {
        uVar22 = CRandomizer::getRandom(this_01);
        if (uVar22 < *(uint *)(param_1 + 0x11c)) {
          puVar17 = (undefined8 *)((ulong)uVar22 * 8 + *(long *)(param_1 + 0x110));
        }
        else {
          puVar17 = *(undefined8 **)(param_1 + 0x110);
        }
        iVar9 = iVar9 + 1;
        CExecuteSkillProps::executeSkill
                  ((CExecuteSkillProps *)*puVar17,local_1e0,(Vector3 *)&local_138,param_6,
                   (Vector3 *)&local_128,local_200,*(int *)(*(long *)(param_1 + 0x28) + 0xdc));
        if (*(int *)(param_1 + 0x130) <= iVar9) break;
        this_01 = *(CRandomizer **)(param_1 + 0x128);
      }
    }
  }
  return 1;
}



/* address=00cc5c20
   symbol=CSkillEvent::updateEvent */

/* CSkillEvent::updateEvent(float) */

uint CSkillEvent::updateEvent(float param_1)

{
  CSkillEvent CVar1;
  code *pcVar2;
  bool bVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  long lVar7;
  float *pfVar8;
  Vector3 *pVVar9;
  long *plVar10;
  CPositionableObject *pCVar11;
  long lVar12;
  uint uVar13;
  long *plVar14;
  CSkillEvent *in_RDI;
  float fVar15;
  float fVar16;
  undefined8 uVar17;
  float in_XMM1_Da;
  float fVar18;
  undefined4 in_XMM1_Db;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  float fVar25;
  float fVar26;
  float fVar27;
  float fVar28;
  undefined8 local_128;
  undefined8 local_120;
  undefined8 local_118;
  float local_110;
  float local_108;
  float local_104;
  float local_100;
  undefined8 local_f8;
  float local_f0;
  undefined8 local_e8;
  float local_e0;
  float local_d8;
  float local_d4;
  float local_d0;
  undefined8 local_c8;
  float local_c0;
  undefined8 local_b8;
  float local_b0;
  undefined8 local_a8;
  float local_a0;
  undefined8 local_98;
  float local_90;
  float local_88;
  float local_84;
  float local_80;
  undefined8 local_78;
  float local_70;
  float local_68;
  float local_64;
  float local_60;
  float local_58;
  float local_54;
  float local_50;
  undefined8 local_48;
  float local_40;

  fVar16 = DAT_00fa47f8;
  if (in_RDI[0x1dc] == (CSkillEvent)0x0) {
LAB_00cc5ceb:
    if (*(long *)(in_RDI + 0x90) != 0) {
      if (*(long *)(in_RDI + 0x80) == 0) {
        TSafePointer<CBaseUnit>::setObject
                  ((TSafePointer<CBaseUnit> *)(in_RDI + 0x80),
                   *(CBaseUnit **)(*(long *)(in_RDI + 0x28) + 0x40));
      }
      if ((in_RDI[0x134] == (CSkillEvent)0x0) ||
         (*(float *)(in_RDI + 0x15c) = *(float *)(in_RDI + 0x15c) - param_1,
         *(long *)(in_RDI + 0x38) == 0)) {
        uVar13 = canStop(in_RDI);
        return uVar13 ^ 1;
      }
      if ((in_RDI[0x137] != (CSkillEvent)0x0) &&
         (lVar7 = CSkillProperty::getOwnerCharacter(*(CSkillProperty **)(in_RDI + 0x90)), lVar7 != 0
         )) {
        plVar10 = (long *)CSkillProperty::getOwnerCharacter(*(CSkillProperty **)(in_RDI + 0x90));
        local_50 = DAT_014241b4;
        local_58 = Ogre::Vector3::ZERO;
        local_54 = DAT_014241b0;
        if (plVar10 != (long *)0x0) {
          fVar16 = *(float *)(in_RDI + 0x164);
          if ((((fVar16 != DAT_00fa47f8) || (NAN(fVar16) || NAN(DAT_00fa47f8))) &&
              (lVar7 = __dynamic_cast(plVar10,&CBaseUnit::typeinfo,&CCharacter::typeinfo,0),
              local_50 = DAT_014241b4, local_58 = Ogre::Vector3::ZERO, local_54 = DAT_014241b0,
              lVar7 != 0)) &&
             ((*(char *)(lVar7 + 0x321) != '\0' &&
              (*(float *)(lVar7 + 0x28c) <= *(float *)(lVar7 + 0x290) &&
               *(float *)(lVar7 + 0x290) != *(float *)(lVar7 + 0x28c))))) {
            pfVar8 = (float *)(**(code **)(*plVar10 + 0x130))(plVar10);
            local_50 = pfVar8[2] * fVar16;
            local_58 = fVar16 * *pfVar8;
            local_54 = pfVar8[1] * fVar16;
          }
        }
        pCVar11 = (CPositionableObject *)
                  CSkillProperty::getOwnerCharacter(*(CSkillProperty **)(in_RDI + 0x90));
        uVar17 = CPositionableObject::getPosition(pCVar11,true);
        local_48._4_4_ = (float)((ulong)uVar17 >> 0x20);
        local_54 = local_54 + local_48._4_4_;
        local_48._0_4_ = (float)uVar17;
        local_58 = local_58 + (float)local_48;
        local_50 = local_50 + in_XMM1_Da;
        local_48 = uVar17;
        local_40 = in_XMM1_Da;
        CPositionableObject::setPosition
                  (*(CPositionableObject **)(in_RDI + 0x38),(Vector3 *)&local_58);
        pcVar2 = *(code **)(**(long **)(in_RDI + 0x38) + 0x108);
        lVar7 = CSkillProperty::getOwnerCharacter(*(CSkillProperty **)(in_RDI + 0x90));
        (**(code **)(**(long **)(lVar7 + 0x58) + 200))();
        (*pcVar2)(*(undefined8 *)(in_RDI + 0x38));
      }
      if (in_RDI[0x13e] != (CSkillEvent)0x0) {
        if ((*(long *)(in_RDI + 0x80) == 0) || (in_RDI[0x148] != (CSkillEvent)0x0)) {
          CSkillProperty::getOwnerCharacter(*(CSkillProperty **)(in_RDI + 0x90));
          local_f8 = getBonePosition();
          local_f0 = in_XMM1_Da;
          plVar10 = (long *)CSkillProperty::getOwnerCharacter(*(CSkillProperty **)(in_RDI + 0x90));
          pfVar8 = (float *)(**(code **)(*plVar10 + 0xe8))(plVar10);
          fVar15 = DAT_00fa47fc /
                   (pfVar8[0xc] * (float)local_f8 + pfVar8[0xd] * local_f8._4_4_ +
                    pfVar8[0xe] * local_f0 + pfVar8[0xf]);
          fVar21 = (*pfVar8 * (float)local_f8 + pfVar8[1] * local_f8._4_4_ + pfVar8[2] * local_f0 +
                   pfVar8[3]) * fVar15;
          fVar18 = (pfVar8[4] * (float)local_f8 + pfVar8[5] * local_f8._4_4_ + pfVar8[6] * local_f0
                   + pfVar8[7]) * fVar15;
          fVar19 = ((float)local_f8 * pfVar8[8] + local_f8._4_4_ * pfVar8[9] + local_f0 * pfVar8[10]
                   + pfVar8[0xb]) * fVar15;
          lVar7 = CSkillProperty::getOwnerCharacter(*(CSkillProperty **)(in_RDI + 0x90));
          fVar16 = *(float *)(lVar7 + 0x194);
          pCVar11 = (CPositionableObject *)
                    CSkillProperty::getOwnerCharacter(*(CSkillProperty **)(in_RDI + 0x90));
          uVar17 = CPositionableObject::getPosition(pCVar11,true);
          local_78._4_4_ = (float)((ulong)uVar17 >> 0x20);
          local_78._0_4_ = (float)uVar17;
          local_108 = fVar21 + (float)local_78;
          local_100 = fVar19 + fVar15;
          local_104 = (local_78._4_4_ - fVar16) + fVar18;
          local_78 = uVar17;
          local_70 = fVar15;
          fVar16 = (float)CSkill::getRange(*(CSkill **)(in_RDI + 0x28));
          plVar10 = (long *)CSkillProperty::getOwnerCharacter(*(CSkillProperty **)(in_RDI + 0x90));
          pfVar8 = (float *)(**(code **)(*plVar10 + 0x130))(plVar10);
          in_XMM1_Db = 0;
          in_XMM1_Da = *pfVar8 * fVar16 + local_108;
          local_110 = fVar16 * pfVar8[2] + local_100;
          local_118 = CONCAT44(pfVar8[1] * fVar16 + local_104,in_XMM1_Da);
          if ((in_RDI[0x149] != (CSkillEvent)0x0) &&
             (cVar4 = CLevel::rayCollision
                                (*(CLevel **)(*(long *)(in_RDI + 0x30) + 0x18),(Vector3 *)&local_108
                                 ,(Vector3 *)&local_118,(Vector3 *)&local_d8,(Vector3 *)&local_c8,
                                 true), cVar4 != '\0')) {
            in_XMM1_Db = 0;
            local_110 = local_c0 * DAT_00fef758 + local_d0;
            in_XMM1_Da = local_c8._4_4_ * DAT_00fef758 + local_d4;
            local_118 = CONCAT44(in_XMM1_Da,DAT_00fef758 * (float)local_c8 + local_d8);
          }
          CPositionableObject::setPosition
                    (*(CPositionableObject **)(in_RDI + 0x38),(Vector3 *)&local_118);
          pcVar2 = *(code **)(**(long **)(in_RDI + 0x38) + 0x118);
          plVar10 = (long *)CSkillProperty::getOwnerCharacter(*(CSkillProperty **)(in_RDI + 0x90));
          uVar17 = (**(code **)(*plVar10 + 0xe8))(plVar10);
          (*pcVar2)(*(undefined8 *)(in_RDI + 0x38),uVar17,0);
        }
        else {
          local_f8 = getBonePosition();
          plVar10 = *(long **)(in_RDI + 0x80);
          fVar16 = DAT_014241b4;
          local_64 = DAT_014241b0;
          local_68 = Ogre::Vector3::ZERO;
          local_f0 = in_XMM1_Da;
          if (plVar10 != (long *)0x0) {
            fVar15 = *(float *)(in_RDI + 0x164);
            if ((((fVar15 != DAT_00fa47f8) || (NAN(fVar15) || NAN(DAT_00fa47f8))) &&
                (lVar7 = __dynamic_cast(plVar10,&CBaseUnit::typeinfo,&CCharacter::typeinfo,0),
                fVar16 = DAT_014241b4, local_64 = DAT_014241b0, local_68 = Ogre::Vector3::ZERO,
                lVar7 != 0)) &&
               ((*(char *)(lVar7 + 0x321) != '\0' &&
                (*(float *)(lVar7 + 0x28c) <= *(float *)(lVar7 + 0x290) &&
                 *(float *)(lVar7 + 0x290) != *(float *)(lVar7 + 0x28c))))) {
              pfVar8 = (float *)(**(code **)(*plVar10 + 0x130))(plVar10);
              fVar16 = pfVar8[2] * fVar15;
              local_64 = pfVar8[1] * fVar15;
              local_68 = fVar15 * *pfVar8;
            }
          }
          in_XMM1_Db = 0;
          local_64 = local_64 + local_f8._4_4_;
          local_68 = local_68 + (float)local_f8;
          in_XMM1_Da = fVar16 + local_f0;
          local_60 = in_XMM1_Da;
          CPositionableObject::setPosition
                    (*(CPositionableObject **)(in_RDI + 0x38),(Vector3 *)&local_68);
          pcVar2 = *(code **)(**(long **)(in_RDI + 0x38) + 0x108);
          (**(code **)(**(long **)(*(long *)(in_RDI + 0x80) + 0x58) + 200))();
          (*pcVar2)(*(undefined8 *)(in_RDI + 0x38));
        }
      }
      if (((in_RDI[0x178] != (CSkillEvent)0x0) && (*(long *)(in_RDI + 0x170) != 0)) &&
         (*(long *)(in_RDI + 0x80) != 0)) {
        local_c8 = getBonePosition();
        plVar14 = *(long **)(in_RDI + 0x170);
        plVar10 = *(long **)(in_RDI + 0x80);
        pcVar2 = *(code **)(*plVar14 + 0x1a8);
        fVar16 = DAT_014241b0;
        local_80 = DAT_014241b4;
        local_88 = Ogre::Vector3::ZERO;
        local_c0 = in_XMM1_Da;
        if (plVar10 != (long *)0x0) {
          fVar15 = *(float *)(in_RDI + 0x164);
          if ((((fVar15 != DAT_00fa47f8) || (NAN(fVar15) || NAN(DAT_00fa47f8))) &&
              (lVar7 = __dynamic_cast(plVar10,&CBaseUnit::typeinfo,&CCharacter::typeinfo,0),
              fVar16 = DAT_014241b0, local_80 = DAT_014241b4, local_88 = Ogre::Vector3::ZERO,
              lVar7 != 0)) &&
             ((*(char *)(lVar7 + 0x321) != '\0' &&
              (*(float *)(lVar7 + 0x28c) <= *(float *)(lVar7 + 0x290) &&
               *(float *)(lVar7 + 0x290) != *(float *)(lVar7 + 0x28c))))) {
            pfVar8 = (float *)(**(code **)(*plVar10 + 0x130))(plVar10);
            plVar14 = *(long **)(in_RDI + 0x170);
            fVar16 = pfVar8[1] * fVar15;
            local_80 = pfVar8[2] * fVar15;
            local_88 = fVar15 * *pfVar8;
          }
        }
        in_XMM1_Db = 0;
        in_XMM1_Da = fVar16 + local_c8._4_4_;
        local_88 = local_88 + (float)local_c8;
        local_80 = local_80 + local_c0;
        local_84 = in_XMM1_Da;
        (*pcVar2)(plVar14);
      }
      if (*(int *)(*(long *)(in_RDI + 0x28) + 0xec) == -1) {
        iVar5 = CEditorScene::getNumberOfTimelinesUpdating(*(CEditorScene **)(in_RDI + 0x38),true);
        (**(code **)(**(long **)(in_RDI + 0x38) + 0x208))();
        if (iVar5 == 0) goto LAB_00cc62bc;
        iVar6 = CEditorScene::getNumberOfTimelinesUpdating(*(CEditorScene **)(in_RDI + 0x38),true);
        if (iVar6 == 0) goto LAB_00cc62d5;
        in_XMM1_Da = *(float *)(in_RDI + 0x158);
        in_XMM1_Db = 0;
        if ((in_XMM1_Da <= 0.0) || (0.0 < *(float *)(in_RDI + 0x15c))) goto LAB_00cc62bc;
LAB_00cc6d31:
        stopAllParticles(in_RDI,false);
      }
      else {
        iVar5 = 0;
        (**(code **)(**(long **)(in_RDI + 0x38) + 0x208))();
LAB_00cc62bc:
        if (*(long *)(in_RDI + 0x170) != 0) {
          if (*(char *)(*(long *)(in_RDI + 0x170) + 0x136) == '\0') {
            in_XMM1_Da = *(float *)(in_RDI + 0x158);
            in_XMM1_Db = 0;
            if (in_XMM1_Da <= 0.0) goto LAB_00cc62ea;
            fVar16 = *(float *)(in_RDI + 0x15c);
          }
          else {
LAB_00cc62d5:
            fVar16 = *(float *)(in_RDI + 0x15c);
          }
          if (fVar16 <= 0.0) goto LAB_00cc6d31;
        }
      }
LAB_00cc62ea:
      if ((((iVar5 != 0) && (*(long *)(in_RDI + 0x40) != 0)) && (in_RDI[0x139] != (CSkillEvent)0x0))
         && (lVar7 = CSkillProperty::getOwnerCharacter(*(CSkillProperty **)(in_RDI + 0x90)),
            lVar7 != 0)) {
        local_c8 = CPositionableObject::getPosition(*(CPositionableObject **)(in_RDI + 0x40),false);
        local_c0 = in_XMM1_Da;
        if ((*(CSkill **)(in_RDI + 0x28) == (CSkill *)0x0) ||
           (iVar5 = CSkill::getTargetType(*(CSkill **)(in_RDI + 0x28)), iVar5 != 1)) {
          if (in_RDI[0x13f] != (CSkillEvent)0x0) {
            in_XMM1_Db = 0;
            in_XMM1_Da = (float)local_c8 * *(float *)(in_RDI + 0x160);
            local_c0 = *(float *)(in_RDI + 0x160) * local_c0;
            local_c8 = CONCAT44(local_c8._4_4_,in_XMM1_Da);
          }
          local_128 = (**(code **)(**(long **)(in_RDI + 0x38) + 0xf0))();
          local_120 = CONCAT44(in_XMM1_Db,in_XMM1_Da);
          uVar17 = Ogre::Quaternion::operator*((Quaternion *)&local_128,(Vector3 *)&local_c8);
          local_c8._0_4_ = (float)uVar17;
          local_a8._4_4_ = (float)((ulong)uVar17 >> 0x20);
          local_c8._4_4_ = local_a8._4_4_;
          local_c0 = in_XMM1_Da;
          local_a8 = uVar17;
          local_a0 = in_XMM1_Da;
          uVar17 = CPositionableObject::getPosition(*(CPositionableObject **)(in_RDI + 0x38),true);
          local_b8._0_4_ = (float)uVar17;
          local_b8._4_4_ = (float)((ulong)uVar17 >> 0x20);
          local_c8 = CONCAT44(local_c8._4_4_ + local_b8._4_4_,(float)local_c8 + (float)local_b8);
          local_c0 = local_c0 + in_XMM1_Da;
          local_b8 = uVar17;
          local_b0 = in_XMM1_Da;
        }
        else {
          in_XMM1_Da = *(float *)(in_RDI + 0x204) * local_c0;
          local_c8._4_4_ = *(float *)(in_RDI + 0x200) * local_c0;
          local_c8._0_4_ = local_c0 * *(float *)(in_RDI + 0x1fc);
          local_c0 = in_XMM1_Da;
          uVar17 = CPositionableObject::getPosition(*(CPositionableObject **)(in_RDI + 0x38),true);
          local_98._0_4_ = (float)uVar17;
          local_98._4_4_ = (float)((ulong)uVar17 >> 0x20);
          local_c8 = CONCAT44(local_c8._4_4_ + local_98._4_4_,(float)local_c8 + (float)local_98);
          local_c0 = local_c0 + in_XMM1_Da;
          local_98 = uVar17;
          local_90 = in_XMM1_Da;
        }
        CVar1 = in_RDI[0x13c];
        pVVar9 = (Vector3 *)CSkillProperty::getOwnerCharacter(*(CSkillProperty **)(in_RDI + 0x90));
        cVar4 = CCharacter::moveToPosition(pVVar9,SUB81(&local_c8,0),(bool)CVar1);
        if (cVar4 == '\0') {
          stopEvent(in_RDI);
        }
      }
      if (((in_RDI[0x147] != (CSkillEvent)0x0) || (in_RDI[0x148] != (CSkillEvent)0x0)) &&
         (*(int *)(in_RDI + 0xb0) != 0)) {
        uVar13 = 0;
        do {
          CSkillProperty::getOwnerCharacter(*(CSkillProperty **)(in_RDI + 0x90));
          local_c8 = getBonePosition();
          local_c0 = in_XMM1_Da;
          plVar10 = (long *)CSkillProperty::getOwnerCharacter(*(CSkillProperty **)(in_RDI + 0x90));
          pfVar8 = (float *)(**(code **)(*plVar10 + 0xe8))(plVar10);
          fVar24 = pfVar8[1] * local_c8._4_4_;
          fVar27 = pfVar8[5] * local_c8._4_4_;
          fVar22 = DAT_00fa47fc /
                   (pfVar8[0xc] * (float)local_c8 + pfVar8[0xd] * local_c8._4_4_ +
                    pfVar8[0xe] * local_c0 + pfVar8[0xf]);
          fVar23 = *pfVar8 * (float)local_c8;
          fVar25 = pfVar8[2] * local_c0;
          fVar26 = pfVar8[4] * (float)local_c8;
          fVar16 = pfVar8[3];
          fVar28 = pfVar8[6] * local_c0;
          fVar18 = local_c0 * pfVar8[10];
          fVar20 = (float)local_c8 * pfVar8[8] + local_c8._4_4_ * pfVar8[9] + fVar18;
          fVar15 = pfVar8[7];
          fVar19 = pfVar8[0xb];
          lVar7 = CSkillProperty::getOwnerCharacter(*(CSkillProperty **)(in_RDI + 0x90));
          fVar21 = *(float *)(lVar7 + 0x194);
          pCVar11 = (CPositionableObject *)
                    CSkillProperty::getOwnerCharacter(*(CSkillProperty **)(in_RDI + 0x90));
          uVar17 = CPositionableObject::getPosition(pCVar11,true);
          local_e8._4_4_ = (float)((ulong)uVar17 >> 0x20);
          local_e8._0_4_ = (float)uVar17;
          local_d8 = (fVar23 + fVar24 + fVar25 + fVar16) * fVar22 + (float)local_e8;
          local_d0 = (fVar20 + fVar19) * fVar22 + fVar18;
          local_d4 = (local_e8._4_4_ - fVar21) + (fVar26 + fVar27 + fVar28 + fVar15) * fVar22;
          if (uVar13 < *(uint *)(in_RDI + 0xb4)) {
            plVar10 = (long *)((ulong)uVar13 * 8 + *(long *)(in_RDI + 0xa8));
          }
          else {
            plVar10 = *(long **)(in_RDI + 0xa8);
          }
          local_e8 = uVar17;
          local_e0 = fVar18;
          CPositionableObject::setPosition
                    (*(CPositionableObject **)(*plVar10 + 0x10),(Vector3 *)&local_c8);
          if ((*(long *)(in_RDI + 0x80) == 0) || (in_RDI[0x148] != (CSkillEvent)0x0)) {
            fVar16 = (float)CSkill::getRange(*(CSkill **)(in_RDI + 0x28));
            plVar10 = (long *)CSkillProperty::getOwnerCharacter(*(CSkillProperty **)(in_RDI + 0x90))
            ;
            pfVar8 = (float *)(**(code **)(*plVar10 + 0x130))(plVar10);
            local_f0 = fVar16 * pfVar8[2] + local_d0;
            local_f8 = CONCAT44(pfVar8[1] * fVar16 + local_d4,*pfVar8 * fVar16 + local_d8);
            if ((in_RDI[0x149] != (CSkillEvent)0x0) &&
               (cVar4 = CLevel::rayCollision
                                  (*(CLevel **)(*(long *)(in_RDI + 0x30) + 0x18),
                                   (Vector3 *)&local_d8,(Vector3 *)&local_f8,(Vector3 *)&local_108,
                                   (Vector3 *)&local_118,true), cVar4 != '\0')) {
              local_f0 = DAT_00fef758 * local_110 + local_100;
              local_f8 = CONCAT44(DAT_00fef758 * local_118._4_4_ + local_104,
                                  DAT_00fef758 * (float)local_118 + local_108);
            }
            plVar10 = (long *)CSkillProperty::getOwnerCharacter(*(CSkillProperty **)(in_RDI + 0x90))
            ;
            fVar16 = DAT_014241b4;
            in_XMM1_Da = DAT_014241b0;
            fVar15 = Ogre::Vector3::ZERO;
            if (plVar10 != (long *)0x0) {
              fVar19 = *(float *)(in_RDI + 0x164);
              if ((((fVar19 != 0.0) || (NAN(fVar19))) &&
                  (lVar7 = __dynamic_cast(plVar10,&CBaseUnit::typeinfo,&CCharacter::typeinfo),
                  fVar16 = DAT_014241b4, in_XMM1_Da = DAT_014241b0, fVar15 = Ogre::Vector3::ZERO,
                  lVar7 != 0)) &&
                 ((*(char *)(lVar7 + 0x321) != '\0' &&
                  (*(float *)(lVar7 + 0x28c) <= *(float *)(lVar7 + 0x290) &&
                   *(float *)(lVar7 + 0x290) != *(float *)(lVar7 + 0x28c))))) {
                pfVar8 = (float *)(**(code **)(*plVar10 + 0x130))(plVar10);
                fVar16 = pfVar8[2] * fVar19;
                in_XMM1_Da = pfVar8[1] * fVar19;
                fVar15 = *pfVar8 * fVar19;
              }
            }
            local_f0 = (local_f0 - local_d0) + fVar16;
            in_XMM1_Da = (local_f8._4_4_ - local_d4) + in_XMM1_Da;
            local_f8 = CONCAT44(in_XMM1_Da,((float)local_f8 - local_d8) + fVar15);
            if (uVar13 < *(uint *)(in_RDI + 0xb4)) {
              plVar10 = (long *)((ulong)uVar13 * 8 + *(long *)(in_RDI + 0xa8));
            }
            else {
              plVar10 = *(long **)(in_RDI + 0xa8);
            }
            ParticleUniverse::LineEmitter::setEnd
                      (*(LineEmitter **)(*plVar10 + 0x18),(Vector3 *)&local_f8);
          }
          else {
            local_118 = getBonePosition();
            local_110 = fVar18;
            if ((in_RDI[0x149] != (CSkillEvent)0x0) &&
               (cVar4 = CLevel::rayCollision
                                  (*(CLevel **)(*(long *)(in_RDI + 0x30) + 0x18),
                                   (Vector3 *)&local_d8,(Vector3 *)&local_118,(Vector3 *)&local_108,
                                   (Vector3 *)&local_f8,true), cVar4 != '\0')) {
              local_110 = DAT_00fef758 * local_f0 + local_100;
              local_118 = CONCAT44(DAT_00fef758 * local_f8._4_4_ + local_104,
                                   DAT_00fef758 * (float)local_f8 + local_108);
            }
            plVar10 = *(long **)(in_RDI + 0x80);
            fVar16 = DAT_014241b4;
            in_XMM1_Da = DAT_014241b0;
            fVar15 = Ogre::Vector3::ZERO;
            if (plVar10 != (long *)0x0) {
              fVar19 = *(float *)(in_RDI + 0x164);
              if ((((fVar19 != 0.0) || (NAN(fVar19))) &&
                  (lVar7 = __dynamic_cast(plVar10,&CBaseUnit::typeinfo,&CCharacter::typeinfo),
                  fVar16 = DAT_014241b4, in_XMM1_Da = DAT_014241b0, fVar15 = Ogre::Vector3::ZERO,
                  lVar7 != 0)) &&
                 ((*(char *)(lVar7 + 0x321) != '\0' &&
                  (*(float *)(lVar7 + 0x28c) <= *(float *)(lVar7 + 0x290) &&
                   *(float *)(lVar7 + 0x290) != *(float *)(lVar7 + 0x28c))))) {
                pfVar8 = (float *)(**(code **)(*plVar10 + 0x130))(plVar10);
                fVar16 = pfVar8[2] * fVar19;
                in_XMM1_Da = pfVar8[1] * fVar19;
                fVar15 = *pfVar8 * fVar19;
              }
            }
            local_110 = (local_110 - local_d0) + fVar16;
            in_XMM1_Da = (local_118._4_4_ - local_d4) + in_XMM1_Da;
            local_118 = CONCAT44(in_XMM1_Da,((float)local_118 - local_d8) + fVar15);
            if (uVar13 < *(uint *)(in_RDI + 0xb4)) {
              plVar10 = (long *)((ulong)uVar13 * 8 + *(long *)(in_RDI + 0xa8));
            }
            else {
              plVar10 = *(long **)(in_RDI + 0xa8);
            }
            ParticleUniverse::LineEmitter::setEnd
                      (*(LineEmitter **)(*plVar10 + 0x18),(Vector3 *)&local_118);
          }
          uVar13 = uVar13 + 1;
        } while (uVar13 < *(uint *)(in_RDI + 0xb0));
      }
      if (((in_RDI[0x141] != (CSkillEvent)0x0) && (*(long *)(in_RDI + 0x90) != 0)) &&
         (*(Vector3 **)(in_RDI + 0x80) != (Vector3 *)0x0)) {
        applyEffects((CBaseUnit *)in_RDI,*(Vector3 **)(in_RDI + 0x80),false);
      }
      cVar4 = shouldStop(in_RDI);
      if (cVar4 == '\0') goto LAB_00cc5e50;
      if (((*(long *)(in_RDI + 0x170) != 0) &&
          (lVar7 = CSkillProperty::getOwnerCharacter(*(CSkillProperty **)(in_RDI + 0x90)),
          lVar7 != 0)) &&
         (lVar7 = *(long *)(in_RDI + 0x170),
         lVar12 = CSkillProperty::getOwnerCharacter(*(CSkillProperty **)(in_RDI + 0x90)),
         lVar7 == *(long *)(lVar12 + 0x750))) {
        plVar10 = (long *)CSkillProperty::getOwnerCharacter(*(CSkillProperty **)(in_RDI + 0x90));
        (**(code **)(*plVar10 + 0x310))(plVar10,0);
      }
      disableAllDamageShapes(in_RDI);
      if (*(long **)(in_RDI + 0x38) != (long *)0x0) {
        (**(code **)(**(long **)(in_RDI + 0x38) + 0x58))();
        return 0;
      }
    }
    uVar13 = 0;
  }
  else {
    fVar15 = *(float *)(in_RDI + 0x1e8) - param_1;
    bVar3 = NAN(DAT_00fa47f8);
    *(float *)(in_RDI + 0x1e8) = fVar15;
    if ((fVar15 <= fVar16) && (!NAN(fVar15) && !bVar3)) {
      in_XMM1_Da = *(float *)(in_RDI + 0x1a8);
      in_XMM1_Db = 0;
      startEvent(*(undefined8 *)(in_RDI + 0x1a0));
      goto LAB_00cc5ceb;
    }
LAB_00cc5e50:
    uVar13 = 1;
  }
  return uVar13;
}



/* address=00cc71d0
   symbol=CSkillEvent::CSkillEvent */

/* WARNING: Removing unreachable block (ram,0x00cc97b0) */
/* WARNING: Removing unreachable block (ram,0x00cc9a42) */
/* WARNING: Removing unreachable block (ram,0x00cc9756) */
/* WARNING: Removing unreachable block (ram,0x00cc9a35) */
/* WARNING: Removing unreachable block (ram,0x00cc96e8) */
/* WARNING: Removing unreachable block (ram,0x00cc96ac) */
/* WARNING: Removing unreachable block (ram,0x00cc9629) */
/* WARNING: Removing unreachable block (ram,0x00cc9493) */
/* WARNING: Removing unreachable block (ram,0x00cc9573) */
/* WARNING: Removing unreachable block (ram,0x00cc9ec9) */
/* WARNING: Removing unreachable block (ram,0x00cca3fb) */
/* WARNING: Removing unreachable block (ram,0x00cca319) */
/* WARNING: Removing unreachable block (ram,0x00cca18f) */
/* WARNING: Removing unreachable block (ram,0x00cca213) */
/* WARNING: Removing unreachable block (ram,0x00cca365) */
/* WARNING: Removing unreachable block (ram,0x00cc9f75) */
/* WARNING: Removing unreachable block (ram,0x00cca003) */
/* WARNING: Removing unreachable block (ram,0x00cca03f) */
/* WARNING: Removing unreachable block (ram,0x00cca0b9) */
/* WARNING: Removing unreachable block (ram,0x00cc9c13) */
/* WARNING: Removing unreachable block (ram,0x00cc9cf3) */
/* WARNING: Removing unreachable block (ram,0x00cc9d3d) */
/* WARNING: Removing unreachable block (ram,0x00cc9db9) */
/* WARNING: Removing unreachable block (ram,0x00cc9e52) */
/* WARNING: Removing unreachable block (ram,0x00cc9382) */
/* WARNING: Removing unreachable block (ram,0x00cc9277) */
/* WARNING: Removing unreachable block (ram,0x00cc9304) */
/* WARNING: Removing unreachable block (ram,0x00cc9ad5) */
/* WARNING: Removing unreachable block (ram,0x00cc9b85) */
/* WARNING: Removing unreachable block (ram,0x00cc9b13) */
/* WARNING: Removing unreachable block (ram,0x00cc9a88) */
/* WARNING: Removing unreachable block (ram,0x00cc92f9) */
/* WARNING: Removing unreachable block (ram,0x00cc9267) */
/* WARNING: Removing unreachable block (ram,0x00cc93ea) */
/* WARNING: Removing unreachable block (ram,0x00cca3b1) */
/* WARNING: Removing unreachable block (ram,0x00cc9e15) */
/* WARNING: Removing unreachable block (ram,0x00cc9dc4) */
/* WARNING: Removing unreachable block (ram,0x00cc9cb5) */
/* WARNING: Removing unreachable block (ram,0x00cc9cfe) */
/* WARNING: Removing unreachable block (ram,0x00cc9bd5) */
/* WARNING: Removing unreachable block (ram,0x00cca0c4) */
/* WARNING: Removing unreachable block (ram,0x00cca13b) */
/* WARNING: Removing unreachable block (ram,0x00cc9fbd) */
/* WARNING: Removing unreachable block (ram,0x00cc9f1d) */
/* WARNING: Removing unreachable block (ram,0x00cca266) */
/* WARNING: Removing unreachable block (ram,0x00cca1d5) */
/* WARNING: Removing unreachable block (ram,0x00cca375) */
/* WARNING: Removing unreachable block (ram,0x00cca406) */
/* WARNING: Removing unreachable block (ram,0x00cca3bf) */
/* WARNING: Removing unreachable block (ram,0x00cc9535) */
/* WARNING: Removing unreachable block (ram,0x00cc957e) */
/* WARNING: Removing unreachable block (ram,0x00cc945a) */
/* WARNING: Removing unreachable block (ram,0x00cc9634) */
/* WARNING: Removing unreachable block (ram,0x00cc96a1) */
/* WARNING: Removing unreachable block (ram,0x00cc974b) */
/* WARNING: Removing unreachable block (ram,0x00cc99df) */
/* WARNING: Removing unreachable block (ram,0x00cc9952) */
/* WARNING: Removing unreachable block (ram,0x00cc9800) */
/* WARNING: Removing unreachable block (ram,0x00cca146) */
/* CSkillEvent::CSkillEvent(CSkill*, CSkillProperty*, CResourceManager*, CDataGroup*) */

void __thiscall
CSkillEvent::CSkillEvent
          (CSkillEvent *this,CSkill *param_1,CSkillProperty *param_2,CResourceManager *param_3,
          CDataGroup *param_4)

{
  allocator *paVar1;
  int *piVar2;
  wchar_t wVar3;
  size_t __n;
  undefined8 uVar4;
  undefined8 uVar5;
  CParticle *this_00;
  CDataGroup *pCVar6;
  CSkillEvent CVar7;
  char cVar8;
  int iVar9;
  uint uVar10;
  undefined8 *puVar11;
  CRandomizer *this_01;
  wstring_conflict *pwVar12;
  long lVar13;
  CUnitResourceList *this_02;
  long lVar14;
  long *plVar15;
  CPathController *this_03;
  CLayout *this_04;
  CRunicCore *pCVar16;
  void *pvVar17;
  wchar_t *pwVar18;
  CSkillEffectAndAffixes *this_05;
  CExecuteSkillProps *this_06;
  ulong uVar19;
  int iVar20;
  uint uVar21;
  undefined8 *puVar22;
  uint uVar23;
  bool bVar24;
  bool bVar25;
  float fVar26;
  undefined4 uVar27;
  uint local_4cc;
  void *local_4a8;
  long local_4a0;
  undefined8 local_498;
  long *local_488;
  uint local_480;
  uint local_47c;
  undefined4 local_478;
  wchar_t *local_468;
  uint local_460;
  uint local_45c;
  undefined4 local_458;
  long local_448 [2];
  long local_438 [2];
  long local_428 [2];
  long local_418 [2];
  long local_408 [2];
  long local_3f8 [2];
  long local_3e8 [2];
  long local_3d8 [2];
  long local_3c8 [2];
  long local_3b8 [2];
  long local_3a8 [2];
  long local_398 [2];
  long local_388 [2];
  long local_378 [2];
  long local_368 [2];
  long local_358 [2];
  long local_348 [2];
  long local_338 [2];
  long local_328 [2];
  long local_318 [2];
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
  long local_158 [2];
  wchar_t *local_148 [2];
  long local_138 [2];
  long local_128 [2];
  wchar_t *local_118 [2];
  long local_108 [2];
  long local_f8 [2];
  long local_e8 [2];
  long local_d8 [2];
  long local_c8 [2];
  long local_b8 [9];
  allocator local_6e;
  allocator local_6d;
  allocator local_6c;
  allocator local_6b;
  allocator local_6a;
  allocator local_69;
  allocator local_68;
  allocator local_67;
  allocator local_66;
  allocator local_65;
  allocator local_64;
  allocator local_63;
  allocator local_62;
  allocator local_61;
  allocator local_60;
  allocator local_5f;
  allocator local_5e;
  allocator local_5d;
  allocator local_5c;
  allocator local_5b;
  allocator local_5a;
  allocator local_59;
  allocator local_58;
  allocator local_57;
  allocator local_56;
  allocator local_55;
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

  CRunicCore::CRunicCore((CRunicCore *)this);
  *(undefined ***)this = &PTR__CSkillEvent_00ff59f0;
  *(undefined ***)(this + 0x10) = &PTR__CSkillEvent_00ff5a58;
  *(undefined ***)(this + 0x18) = &PTR__CSkillEvent_00ff5a90;
  *(undefined ***)(this + 0x20) = &PTR__CSkillEvent_00ff5ad8;
  *(CResourceManager **)(this + 0x30) = param_3;
  *(undefined8 *)(this + 0x38) = 0;
  *(undefined8 *)(this + 0x40) = 0;
  *(undefined4 *)(this + 0x48) = 0;
  *(undefined8 *)(this + 0x50) = 0;
  *(CSkill **)(this + 0x28) = param_1;
  *(undefined4 *)(this + 0x58) = 0xffffffff;
  *(undefined8 *)(this + 0x60) = 0;
  *(undefined4 *)(this + 0x68) = 0xffffffff;
  *(undefined8 *)(this + 0x70) = 0;
  *(undefined4 *)(this + 0x78) = 0xffffffff;
  *(undefined8 *)(this + 0x80) = 0;
  *(undefined4 *)(this + 0x88) = 0xffffffff;
  *(undefined8 *)(this + 0x90) = 0;
  *(undefined8 *)(this + 0xa0) = 0;
  *(undefined8 *)(this + 0xa8) = 0;
  *(undefined4 *)(this + 0xb0) = 0;
  *(undefined4 *)(this + 0xb4) = 0;
  *(CSkillProperty **)(this + 0x98) = param_2;
  *(undefined4 *)(this + 0xb8) = 4;
  *(undefined8 *)(this + 0xc0) = 0;
  *(undefined4 *)(this + 200) = 0;
  *(undefined4 *)(this + 0xcc) = 0;
  *(undefined4 *)(this + 0xd0) = 10;
  *(undefined8 *)(this + 0xd8) = 0;
  *(undefined4 *)(this + 0xe0) = 0;
  *(undefined4 *)(this + 0xe4) = 0;
  *(undefined4 *)(this + 0xe8) = 2;
  *(undefined8 *)(this + 0xf0) = 0;
  *(undefined4 *)(this + 0xf8) = 0;
  *(undefined4 *)(this + 0xfc) = 0;
  *(undefined4 *)(this + 0x100) = 10;
  *(undefined4 *)(this + 0x108) = 0;
  *(undefined4 *)(this + 0x10c) = 0;
  *(undefined8 *)(this + 0x110) = 0;
  *(undefined4 *)(this + 0x118) = 0;
  *(undefined4 *)(this + 0x11c) = 0;
  *(undefined4 *)(this + 0x120) = 2;
  *(undefined8 *)(this + 0x128) = 0;
  this[0x134] = (CSkillEvent)0x0;
  this[0x135] = (CSkillEvent)0x0;
  this[0x136] = (CSkillEvent)0x0;
  this[0x137] = (CSkillEvent)0x0;
  this[0x139] = (CSkillEvent)0x0;
  this[0x13c] = (CSkillEvent)0x0;
  this[0x13d] = (CSkillEvent)0x0;
  this[0x13e] = (CSkillEvent)0x0;
  this[0x13f] = (CSkillEvent)0x0;
  this[0x140] = (CSkillEvent)0x0;
  this[0x141] = (CSkillEvent)0x0;
  this[0x142] = (CSkillEvent)0x0;
  this[0x143] = (CSkillEvent)0x1;
  this[0x144] = (CSkillEvent)0x0;
  this[0x145] = (CSkillEvent)0x0;
  this[0x146] = (CSkillEvent)0x1;
  this[0x147] = (CSkillEvent)0x1;
  this[0x148] = (CSkillEvent)0x0;
  this[0x149] = (CSkillEvent)0x0;
  this[0x14a] = (CSkillEvent)0x0;
  this[0x14b] = (CSkillEvent)0x0;
  this[0x14e] = (CSkillEvent)0x0;
  this[0x14f] = (CSkillEvent)0x0;
  *(undefined4 *)(this + 0x150) = 0;
  *(undefined4 *)(this + 0x154) = 0;
  *(undefined4 *)(this + 0x15c) = 0;
  *(undefined4 *)(this + 0x160) = 0;
  *(undefined4 *)(this + 0x164) = 0;
  *(undefined4 *)(this + 0x168) = 0xffffffff;
  *(undefined8 *)(this + 0x170) = 0;
  this[0x178] = (CSkillEvent)0x0;
  *(undefined4 *)(this + 0x17c) = 7;
                    /* try { // try from 00cc7497 to 00cc749b has its CatchHandler @ 00cc9b75 */
  CRunicCore::CRunicCore((CRunicCore *)(this + 0x180));
  *(undefined ***)(this + 0x180) = &PTR__CSkillEventPause_00ff5c30;
  *(undefined4 *)(this + 0x1ac) = 0x3f800000;
  *(undefined4 *)(this + 0x1b0) = 0;
  *(undefined4 *)(this + 0x1b4) = 0;
  *(undefined4 *)(this + 0x1b8) = 0;
  *(undefined8 *)(this + 0x1c0) = 0;
  *(undefined4 *)(this + 0x1c8) = 0xffffffff;
  this[0x1dc] = (CSkillEvent)0x0;
  this[0x1dd] = (CSkillEvent)0x0;
  *(undefined4 *)(this + 0x1e0) = 0;
  *(undefined4 *)(this + 0x1e4) = 0;
  *(undefined4 *)(this + 0x1e8) = 0;
  *(undefined4 *)(this + 0x208) = 0;
  *(undefined4 *)(this + 0x20c) = 0;
  *(undefined4 *)(this + 0x210) = 0;
  *(undefined8 *)(this + 0x220) = 0;
  *(CDataGroup **)(this + 0x218) = param_4;
  if (*(long *)(this + 0x28) == 0) {
    return;
  }
  if (param_4 == (CDataGroup *)0x0) goto LAB_00cc769d;
  puVar22 = &::gSKILL_EVENT_TYPE_NAMES;
  iVar20 = 0;
  do {
                    /* try { // try from 00cc7578 to 00cc757c has its CatchHandler @ 00cc9b65 */
    puVar11 = (undefined8 *)CDataGroup::GetGroupName(param_4);
    __n = *(size_t *)((wchar_t *)*puVar11 + -6);
    if ((__n == *(size_t *)((wchar_t *)*puVar22 + -6)) &&
       (iVar9 = wmemcmp((wchar_t *)*puVar11,(wchar_t *)*puVar22,__n), iVar9 == 0)) {
      *(int *)(this + 0x48) = iVar20;
    }
    iVar20 = iVar20 + 1;
    puVar22 = puVar22 + 1;
  } while (iVar20 != 0xb);
                    /* try { // try from 00cc7700 to 00cc7704 has its CatchHandler @ 00cc9b56 */
  std::wstring::wstring((wstring_conflict *)local_b8,L"USEDPS",local_39);
                    /* try { // try from 00cc770f to 00cc7713 has its CatchHandler @ 00cc9b51 */
  CVar7 = (CSkillEvent)CDataGroup::GetDataValue(param_4,(wstring_conflict *)local_b8,false);
  this[0x144] = CVar7;
  if ((allocator *)(local_b8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_b8[0] + -8);
    iVar20 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar20 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
    }
  }
                    /* try { // try from 00cc774b to 00cc774f has its CatchHandler @ 00cc9b1e */
  std::wstring::wstring((wstring_conflict *)local_c8,L"NOSTRIKEPARTICLES",&local_3a);
                    /* try { // try from 00cc775a to 00cc775e has its CatchHandler @ 00cc9b0e */
  CVar7 = (CSkillEvent)CDataGroup::GetDataValue(param_4,(wstring_conflict *)local_c8,false);
  this[0x145] = CVar7;
  if ((allocator *)(local_c8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_c8[0] + -8);
    iVar20 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar20 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
    }
  }
                    /* try { // try from 00cc7797 to 00cc779b has its CatchHandler @ 00cc9ace */
  std::wstring::wstring((wstring_conflict *)local_d8,L"NOSTEALEFFECTS",&local_3b);
                    /* try { // try from 00cc77a9 to 00cc77ad has its CatchHandler @ 00cc9ac9 */
  CVar7 = (CSkillEvent)CDataGroup::GetDataValue(param_4,(wstring_conflict *)local_d8,true);
  this[0x146] = CVar7;
  if ((allocator *)(local_d8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_d8[0] + -8);
    iVar20 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar20 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
    }
  }
                    /* try { // try from 00cc77e6 to 00cc77ea has its CatchHandler @ 00cc9a98 */
  std::wstring::wstring((wstring_conflict *)local_e8,L"WEAPONDAMAGEPCT",&local_3c);
                    /* try { // try from 00cc77f6 to 00cc77fa has its CatchHandler @ 00cc9a93 */
  fVar26 = (float)CDataGroup::GetDataValue(param_4,(wstring_conflict *)local_e8,0.0);
  *(float *)(this + 0x150) = fVar26;
  if ((allocator *)(local_e8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_e8[0] + -8);
    iVar20 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar20 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
    }
    fVar26 = *(float *)(this + 0x150);
  }
  *(uint *)(this + 0x150) = (uint)(fVar26 / DAT_00fa483c) & -(uint)(0.0 < fVar26 / DAT_00fa483c);
                    /* try { // try from 00cc785f to 00cc7863 has its CatchHandler @ 00cc9a52 */
  std::wstring::wstring((wstring_conflict *)local_f8,L"SOAKSCALEPCT",&local_3d);
                    /* try { // try from 00cc7874 to 00cc7878 has its CatchHandler @ 00cc9a4d */
  fVar26 = (float)CDataGroup::GetDataValue(param_4,(wstring_conflict *)local_f8,DAT_00fa483c);
  *(float *)(this + 0x154) = fVar26;
  if ((allocator *)(local_f8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_f8[0] + -8);
    iVar20 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar20 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
    }
    fVar26 = *(float *)(this + 0x154);
  }
  *(uint *)(this + 0x154) = (uint)(fVar26 / DAT_00fa483c) & -(uint)(0.0 < fVar26 / DAT_00fa483c);
  if (*(float *)(this + 0x150) != 0.0) {
                    /* try { // try from 00cc78ec to 00cc78f0 has its CatchHandler @ 00cc92c1 */
    std::wstring::wstring((wstring_conflict *)local_108,L"DAMAGE_TYPE",&local_3e);
                    /* try { // try from 00cc78fe to 00cc791a has its CatchHandler @ 00cc92b1 */
    pwVar12 = (wstring_conflict *)
              CDataGroup::GetDataValue
                        (param_4,(wstring_conflict *)local_108,(wstring_conflict *)&::EMPTY_WSTRING)
    ;
    STRINGS::StringUpper((STRINGS *)&local_468,pwVar12);
    if ((allocator *)(local_108[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_108[0] + -8);
      iVar20 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar20 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_108[0] + -0x18));
      }
    }
    uVar21 = 0;
    do {
                    /* try { // try from 00cc796c to 00cc7970 has its CatchHandler @ 00cc9175 */
      STRINGS::StringUpper
                ((STRINGS *)local_118,(wstring_conflict *)(::gDAMAGE_TYPES + (ulong)uVar21 * 8));
      pwVar18 = local_118[0];
      bVar24 = false;
      paVar1 = (allocator *)(local_118[0] + -6);
      if (*(size_t *)(local_468 + -6) == *(size_t *)(local_118[0] + -6)) {
        iVar20 = wmemcmp(local_468,local_118[0],*(size_t *)(local_468 + -6));
        bVar24 = iVar20 == 0;
      }
      if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        pwVar18 = pwVar18 + -2;
        wVar3 = *pwVar18;
        *pwVar18 = *pwVar18 + L'\xffffffff';
        UNLOCK();
        if (wVar3 < L'\x01') {
          std::wstring::_Rep::_M_destroy(paVar1);
        }
      }
      if (bVar24) {
        *(uint *)(this + 0x17c) = uVar21;
        break;
      }
      uVar21 = uVar21 + 1;
    } while (uVar21 != 7);
    if ((allocator *)(local_468 + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      pwVar18 = local_468 + -2;
      wVar3 = *pwVar18;
      *pwVar18 = *pwVar18 + L'\xffffffff';
      UNLOCK();
      if (wVar3 < L'\x01') {
        std::wstring::_Rep::_M_destroy((allocator *)(local_468 + -6));
      }
    }
  }
                    /* try { // try from 00cc79fd to 00cc7a01 has its CatchHandler @ 00cc93e5 */
  std::wstring::wstring((wstring_conflict *)local_128,L"TARGET_SPECIFIC_UNITS",&local_3f);
                    /* try { // try from 00cc7a0c to 00cc7a10 has its CatchHandler @ 00cc93d4 */
  lVar13 = CDataGroup::GetDataGroupByName(param_4,(wstring_conflict *)local_128,false);
  if ((allocator *)(local_128[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_128[0] + -8);
    iVar20 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar20 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_128[0] + -0x18));
    }
  }
  if ((lVar13 != 0) && (*(int *)(lVar13 + 0x28) != 0)) {
    uVar21 = 0;
    do {
      if (uVar21 < *(uint *)(lVar13 + 0x2c)) {
        plVar15 = (long *)((ulong)uVar21 * 8 + *(long *)(lVar13 + 0x20));
      }
      else {
        plVar15 = *(long **)(lVar13 + 0x20);
      }
      if ((*(int *)(*plVar15 + 0x30) == 8) || (*(int *)(*plVar15 + 0x30) == 5)) {
        if (uVar21 < *(uint *)(lVar13 + 0x2c)) {
          puVar22 = (undefined8 *)((ulong)uVar21 * 8 + *(long *)(lVar13 + 0x20));
        }
        else {
          puVar22 = *(undefined8 **)(lVar13 + 0x20);
        }
                    /* try { // try from 00cc7a76 to 00cc7b84 has its CatchHandler @ 00cc9b65 */
        pwVar12 = (wstring_conflict *)CDataValue::GetValueString((CDataValue *)*puVar22,true);
        this_02 = (CUnitResourceList *)CUnitResourceList::getSingleton();
        lVar14 = CUnitResourceList::getDataGroupByObjectName(this_02,pwVar12);
        if (lVar14 != 0) {
          uVar10 = *(uint *)(this + 0xe0);
          if (uVar10 < *(uint *)(this + 0xe4)) {
            pvVar17 = *(void **)(this + 0xd8);
          }
          else if (*(long *)(this + 0xd8) == 0) {
            *(uint *)(this + 0xe4) = *(uint *)(this + 0xe8);
            pvVar17 = operator_new__((ulong)*(uint *)(this + 0xe8) << 3);
            *(void **)(this + 0xd8) = pvVar17;
            uVar10 = *(uint *)(this + 0xe0);
          }
          else {
            uVar10 = *(uint *)(this + 0xe4) + *(int *)(this + 0xe8);
            pvVar17 = operator_new__((ulong)uVar10 << 3);
            if (*(int *)(this + 0xe4) != 0) {
              uVar23 = 0;
              do {
                uVar19 = (ulong)uVar23;
                uVar23 = uVar23 + 1;
                *(undefined8 *)((long)pvVar17 + uVar19 * 8) =
                     *(undefined8 *)(*(long *)(this + 0xd8) + uVar19 * 8);
              } while (uVar23 < *(uint *)(this + 0xe4));
            }
            if (*(void **)(this + 0xd8) != (void *)0x0) {
              operator_delete__(*(void **)(this + 0xd8));
            }
            *(void **)(this + 0xd8) = pvVar17;
            *(uint *)(this + 0xe4) = uVar10;
            uVar10 = *(uint *)(this + 0xe0);
          }
          *(long *)((long)pvVar17 + (ulong)uVar10 * 8) = lVar14;
          *(int *)(this + 0xe0) = *(int *)(this + 0xe0) + 1;
        }
      }
      uVar21 = uVar21 + 1;
    } while (uVar21 < *(uint *)(lVar13 + 0x28));
  }
                    /* try { // try from 00cc7bb2 to 00cc7bb6 has its CatchHandler @ 00cc93a2 */
  std::wstring::wstring((wstring_conflict *)local_138,L"FILE",&local_40);
                    /* try { // try from 00cc7bc4 to 00cc7bd8 has its CatchHandler @ 00cc9372 */
  pwVar12 = (wstring_conflict *)
            CDataGroup::GetDataValue
                      (param_4,(wstring_conflict *)local_138,(wstring_conflict *)&::EMPTY_WSTRING);
  std::wstring::wstring((wstring_conflict *)local_148,pwVar12);
  if ((allocator *)(local_138[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_138[0] + -8);
    iVar20 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar20 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_138[0] + -0x18));
    }
  }
                    /* try { // try from 00cc7c0b to 00cc7c0f has its CatchHandler @ 00cc9341 */
  std::wstring::wstring((wstring_conflict *)local_158,L"MINDELAY",&local_41);
                    /* try { // try from 00cc7c1b to 00cc7c1f has its CatchHandler @ 00cc9324 */
  uVar27 = CDataGroup::GetDataValue(param_4,(wstring_conflict *)local_158,0.0);
  *(undefined4 *)(this + 0x1e0) = uVar27;
  if ((allocator *)(local_158[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_158[0] + -8);
    iVar20 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar20 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_158[0] + -0x18));
    }
  }
                    /* try { // try from 00cc7c5a to 00cc7c5e has its CatchHandler @ 00cc9e62 */
  std::wstring::wstring((wstring_conflict *)local_168,L"MAXDELAY",&local_42);
                    /* try { // try from 00cc7c6a to 00cc7c6e has its CatchHandler @ 00cc9e5d */
  fVar26 = (float)CDataGroup::GetDataValue(param_4,(wstring_conflict *)local_168,0.0);
  *(float *)(this + 0x1e4) = fVar26;
  if ((allocator *)(local_168[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_168[0] + -8);
    iVar20 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar20 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_168[0] + -0x18));
    }
    fVar26 = *(float *)(this + 0x1e4);
  }
  this[0x1dc] = (CSkillEvent)0x0;
  this[0x1dd] = (CSkillEvent)(0.0 < fVar26);
                    /* try { // try from 00cc7cbd to 00cc7cc1 has its CatchHandler @ 00cc9e05 */
  std::wstring::wstring((wstring_conflict *)local_178,L"APPLYEFFECTS",&local_43);
                    /* try { // try from 00cc7ccc to 00cc7cd0 has its CatchHandler @ 00cc9e00 */
  CVar7 = (CSkillEvent)CDataGroup::GetDataValue(param_4,(wstring_conflict *)local_178,false);
  this[0x138] = CVar7;
  if ((allocator *)(local_178[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_178[0] + -8);
    iVar20 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar20 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_178[0] + -0x18));
    }
  }
                    /* try { // try from 00cc7d09 to 00cc7d0d has its CatchHandler @ 00cc9dcf */
  std::wstring::wstring((wstring_conflict *)local_188,L"CASTFROMTARGET",&local_44);
                    /* try { // try from 00cc7d18 to 00cc7d1c has its CatchHandler @ 00cc9db4 */
  CVar7 = (CSkillEvent)CDataGroup::GetDataValue(param_4,(wstring_conflict *)local_188,false);
  this[0x13a] = CVar7;
  if ((allocator *)(local_188[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_188[0] + -8);
    iVar20 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar20 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_188[0] + -0x18));
    }
  }
                    /* try { // try from 00cc7d55 to 00cc7d59 has its CatchHandler @ 00cc9d7e */
  std::wstring::wstring((wstring_conflict *)local_198,L"STATSHIDDEN",&local_45);
                    /* try { // try from 00cc7d64 to 00cc7d68 has its CatchHandler @ 00cc9d79 */
  CVar7 = (CSkillEvent)CDataGroup::GetDataValue(param_4,(wstring_conflict *)local_198,false);
  this[0x13b] = CVar7;
  if ((allocator *)(local_198[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_198[0] + -8);
    iVar20 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar20 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_198[0] + -0x18));
    }
  }
                    /* try { // try from 00cc7da1 to 00cc7da5 has its CatchHandler @ 00cc9d48 */
  std::wstring::wstring((wstring_conflict *)local_1a8,L"DURATIONOVERRIDEMS",&local_46);
                    /* try { // try from 00cc7db0 to 00cc7db4 has its CatchHandler @ 00cc9d38 */
  iVar20 = CDataGroup::GetDataValue(param_4,(wstring_conflict *)local_1a8,0);
  *(float *)(this + 0x158) = (float)iVar20 / DAT_00fa871c;
  if ((allocator *)(local_1a8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_1a8[0] + -8);
    iVar20 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar20 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_1a8[0] + -0x18));
    }
  }
                    /* try { // try from 00cc7dfb to 00cc7dff has its CatchHandler @ 00cc9ca9 */
  std::wstring::wstring((wstring_conflict *)local_1b8,L"TARGET_AHEAD_OF_UNIT",&local_47);
                    /* try { // try from 00cc7e0b to 00cc7e0f has its CatchHandler @ 00cc9ca4 */
  uVar27 = CDataGroup::GetDataValue(param_4,(wstring_conflict *)local_1b8,0.0);
  *(undefined4 *)(this + 0x164) = uVar27;
  if ((allocator *)(local_1b8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_1b8[0] + -8);
    iVar20 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar20 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_1b8[0] + -0x18));
    }
  }
                    /* try { // try from 00cc7e4a to 00cc7e4e has its CatchHandler @ 00cc9c65 */
  std::wstring::wstring((wstring_conflict *)local_1c8,L"TARGET_CORPSES",&local_48);
                    /* try { // try from 00cc7e59 to 00cc7e5d has its CatchHandler @ 00cc9cee */
  CVar7 = (CSkillEvent)CDataGroup::GetDataValue(param_4,(wstring_conflict *)local_1c8,false);
  this[0x14d] = CVar7;
  if ((allocator *)(local_1c8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_1c8[0] + -8);
    iVar20 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar20 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_1c8[0] + -0x18));
    }
  }
  bVar24 = (bool)gSKILL_EVENT_TYPE_CLONE_ALLOWED[*(int *)(this + 0x48)];
                    /* try { // try from 00cc7ea2 to 00cc7ea6 has its CatchHandler @ 00cc9c5a */
  std::wstring::wstring((wstring_conflict *)local_1d8,L"CAN_CLONE",&local_49);
                    /* try { // try from 00cc7eb2 to 00cc7eb6 has its CatchHandler @ 00cc9c55 */
  CVar7 = (CSkillEvent)CDataGroup::GetDataValue(param_4,(wstring_conflict *)local_1d8,bVar24);
  this[0x14c] = CVar7;
  if ((allocator *)(local_1d8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_1d8[0] + -8);
    iVar20 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar20 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_1d8[0] + -0x18));
    }
  }
                    /* try { // try from 00cc7eef to 00cc7ef3 has its CatchHandler @ 00cc9c1e */
  std::wstring::wstring((wstring_conflict *)local_1e8,L"MAX_UNITS_HIT",&local_4a);
                    /* try { // try from 00cc7eff to 00cc7f03 has its CatchHandler @ 00cc9c0e */
  uVar27 = CDataGroup::GetDataValue(param_4,(wstring_conflict *)local_1e8,-1);
  *(undefined4 *)(this + 0x168) = uVar27;
  if ((allocator *)(local_1e8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_1e8[0] + -8);
    iVar20 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar20 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_1e8[0] + -0x18));
    }
  }
                    /* try { // try from 00cc7f3c to 00cc7f40 has its CatchHandler @ 00cc9bc6 */
  std::wstring::wstring((wstring_conflict *)local_1f8,L"TARGET_POS_X",&local_4b);
                    /* try { // try from 00cc7f4c to 00cc7f50 has its CatchHandler @ 00cc9bc1 */
  uVar27 = CDataGroup::GetDataValue(param_4,(wstring_conflict *)local_1f8,0.0);
  *(undefined4 *)(this + 0x208) = uVar27;
  if ((allocator *)(local_1f8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_1f8[0] + -8);
    iVar20 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar20 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_1f8[0] + -0x18));
    }
  }
                    /* try { // try from 00cc7f8b to 00cc7f8f has its CatchHandler @ 00cc9b90 */
  std::wstring::wstring((wstring_conflict *)local_208,L"TARGET_POS_Y",&local_4c);
                    /* try { // try from 00cc7f9b to 00cc7f9f has its CatchHandler @ 00cca0b4 */
  uVar27 = CDataGroup::GetDataValue(param_4,(wstring_conflict *)local_208,0.0);
  *(undefined4 *)(this + 0x20c) = uVar27;
  if ((allocator *)(local_208[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_208[0] + -8);
    iVar20 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar20 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_208[0] + -0x18));
    }
  }
                    /* try { // try from 00cc7fda to 00cc7fde has its CatchHandler @ 00cca080 */
  std::wstring::wstring((wstring_conflict *)local_218,L"TARGET_POS_Z",&local_4d);
                    /* try { // try from 00cc7fea to 00cc7fee has its CatchHandler @ 00cca07b */
  uVar27 = CDataGroup::GetDataValue(param_4,(wstring_conflict *)local_218,0.0);
  *(undefined4 *)(this + 0x210) = uVar27;
  if ((allocator *)(local_218[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_218[0] + -8);
    iVar20 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar20 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_218[0] + -0x18));
    }
  }
                    /* try { // try from 00cc8029 to 00cc802d has its CatchHandler @ 00cca04a */
  std::wstring::wstring((wstring_conflict *)local_228,L"PATHTOTARGET",&local_4e);
                    /* try { // try from 00cc8038 to 00cc803c has its CatchHandler @ 00cca03a */
  cVar8 = CDataGroup::GetDataValue(param_4,(wstring_conflict *)local_228,false);
  if ((allocator *)(local_228[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_228[0] + -8);
    iVar20 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar20 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_228[0] + -0x18));
    }
  }
  if (cVar8 != '\0') {
                    /* try { // try from 00cc8068 to 00cc806c has its CatchHandler @ 00cca0e5 */
    this_03 = (CPathController *)Ogre::NedAllocImpl::allocBytes(0x198,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00cc8077 to 00cc807b has its CatchHandler @ 00cca0d9 */
    CPathController::CPathController(this_03,*(CResourceManager **)(this + 0x30));
    *(CPathController **)(this + 0x170) = this_03;
                    /* try { // try from 00cc809b to 00cc809f has its CatchHandler @ 00cca0d4 */
    std::wstring::wstring((wstring_conflict *)local_238,L"PATHFOLLOWSTARGET",&local_4f);
                    /* try { // try from 00cc80aa to 00cc80ae has its CatchHandler @ 00cca0cf */
    CVar7 = (CSkillEvent)CDataGroup::GetDataValue(param_4,(wstring_conflict *)local_238,false);
    this[0x178] = CVar7;
    if ((allocator *)(local_238[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_238[0] + -8);
      iVar20 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar20 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_238[0] + -0x18));
      }
    }
  }
  if ((*(size_t *)(local_148[0] + -6) != *(size_t *)(::EMPTY_WSTRING + -6)) ||
     (iVar20 = wmemcmp(local_148[0],::EMPTY_WSTRING,*(size_t *)(local_148[0] + -6)), iVar20 != 0)) {
                    /* try { // try from 00cc80f7 to 00cc80fb has its CatchHandler @ 00cca0e5 */
    this_04 = (CLayout *)Ogre::NedAllocImpl::allocBytes(0x1f8,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00cc810b to 00cc810f has its CatchHandler @ 00cca10a */
    CLayout::CLayout(this_04,*(undefined8 *)(this + 0x30),2);
    *(CLayout **)(this + 0x38) = this_04;
                    /* try { // try from 00cc8130 to 00cc8134 has its CatchHandler @ 00cca0e5 */
    CLayout::loadLayoutFile
              (this_04,(wstring_conflict *)local_148,false,(CTimerStatics *)0x0,false,false,0);
    local_468 = (wchar_t *)0x0;
    local_460 = 0;
    local_45c = 0;
    local_458 = 10;
                    /* try { // try from 00cc817a to 00cc817e has its CatchHandler @ 00cca0f5 */
    std::wstring::wstring((wstring_conflict *)local_248,L"Layout Link",&local_50);
                    /* try { // try from 00cc8193 to 00cc8197 has its CatchHandler @ 00cc9ffe */
    CEditorScene::GetObjectsCreatedByADescriptor
              (*(CEditorScene **)(this + 0x38),(wstring_conflict *)local_248,
               (TArrayList *)&local_468);
    if ((allocator *)(local_248[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_248[0] + -8);
      iVar20 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar20 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_248[0] + -0x18));
      }
    }
                    /* try { // try from 00cc81ca to 00cc81ce has its CatchHandler @ 00cc9fc8 */
    std::wstring::wstring((wstring_conflict *)local_258,L"Layout Link Particle",&local_51);
                    /* try { // try from 00cc81db to 00cc81df has its CatchHandler @ 00cc9fb8 */
    CEditorScene::GetObjectsCreatedByADescriptor
              (*(CEditorScene **)(this + 0x38),(wstring_conflict *)local_258,
               (TArrayList *)&local_468);
    if ((allocator *)(local_258[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_258[0] + -8);
      iVar20 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar20 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_258[0] + -0x18));
      }
    }
                    /* try { // try from 00cc8212 to 00cc8216 has its CatchHandler @ 00cc9f87 */
    std::wstring::wstring((wstring_conflict *)local_268,L"Layout Link Timeline",&local_52);
                    /* try { // try from 00cc8223 to 00cc8227 has its CatchHandler @ 00cc9f82 */
    CEditorScene::GetObjectsCreatedByADescriptor
              (*(CEditorScene **)(this + 0x38),(wstring_conflict *)local_268,
               (TArrayList *)&local_468);
    if ((allocator *)(local_268[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_268[0] + -8);
      iVar20 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar20 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_268[0] + -0x18));
      }
    }
    uVar21 = 0;
    if (local_460 != 0) {
      do {
        pwVar18 = local_468;
        if (uVar21 < local_45c) {
          pwVar18 = (wchar_t *)((long)local_468 + (ulong)uVar21 * 8);
        }
                    /* try { // try from 00cc825d to 00cc8261 has its CatchHandler @ 00cc9fcd */
        CLayout::setStartOnLoad(*(CLayout **)pwVar18,false);
        uVar21 = uVar21 + 1;
      } while (uVar21 < local_460);
    }
    local_460 = 0;
    local_45c = 0;
    if (local_468 != (wchar_t *)0x0) {
      operator_delete__(local_468);
    }
    local_468 = (wchar_t *)0x0;
                    /* try { // try from 00cc82d3 to 00cc82d7 has its CatchHandler @ 00cc9f69 */
    std::wstring::wstring((wstring_conflict *)local_278,L"Emitter",&local_53);
                    /* try { // try from 00cc82e4 to 00cc82e8 has its CatchHandler @ 00cc9f64 */
    CEditorScene::GetObjectsCreatedByADescriptor
              (*(CEditorScene **)(this + 0x38),(wstring_conflict *)local_278,
               (TArrayList *)&local_468);
    if ((allocator *)(local_278[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_278[0] + -8);
      iVar20 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar20 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_278[0] + -0x18));
      }
    }
    if (local_460 != 0) {
      uVar21 = 0;
      do {
        if (uVar21 < local_45c) {
          lVar13 = *(long *)((long)local_468 + (ulong)uVar21 * 8);
          iVar20 = *(int *)(lVar13 + 0x128);
        }
        else {
          lVar13 = *(long *)local_468;
          iVar20 = *(int *)(lVar13 + 0x128);
        }
        if (iVar20 == 3) {
          uVar4 = *(undefined8 *)(lVar13 + 0x110);
          uVar5 = *(undefined8 *)(*(long *)(lVar13 + 0x108) + 0x48);
                    /* try { // try from 00cc8384 to 00cc8388 has its CatchHandler @ 00cc9fcd */
          pCVar16 = (CRunicCore *)Ogre::NedAllocImpl::allocBytes(0x20,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00cc838f to 00cc8393 has its CatchHandler @ 00cc9f28 */
          CRunicCore::CRunicCore(pCVar16);
          *(undefined ***)pCVar16 = &PTR__CLineEmitterWrapper_00ff5bb0;
          *(undefined8 *)(pCVar16 + 0x10) = uVar5;
          *(undefined8 *)(pCVar16 + 0x18) = uVar4;
          uVar10 = *(uint *)(this + 0xb0);
          if (uVar10 < *(uint *)(this + 0xb4)) {
            pvVar17 = *(void **)(this + 0xa8);
          }
          else if (*(long *)(this + 0xa8) == 0) {
            *(uint *)(this + 0xb4) = *(uint *)(this + 0xb8);
            pvVar17 = operator_new__((ulong)*(uint *)(this + 0xb8) * 8);
            *(void **)(this + 0xa8) = pvVar17;
            uVar10 = *(uint *)(this + 0xb0);
          }
          else {
            uVar23 = *(uint *)(this + 0xb4) + *(int *)(this + 0xb8);
                    /* try { // try from 00cc83ce to 00cc8451 has its CatchHandler @ 00cc9fcd */
            pvVar17 = operator_new__((ulong)uVar23 << 3);
            if (*(int *)(this + 0xb4) != 0) {
              uVar10 = 0;
              do {
                uVar19 = (ulong)uVar10;
                uVar10 = uVar10 + 1;
                *(undefined8 *)((long)pvVar17 + uVar19 * 8) =
                     *(undefined8 *)(*(long *)(this + 0xa8) + uVar19 * 8);
              } while (uVar10 < *(uint *)(this + 0xb4));
            }
            if (*(void **)(this + 0xa8) != (void *)0x0) {
              operator_delete__(*(void **)(this + 0xa8));
            }
            uVar10 = *(uint *)(this + 0xb0);
            *(void **)(this + 0xa8) = pvVar17;
            *(uint *)(this + 0xb4) = uVar23;
          }
          *(CRunicCore **)((long)pvVar17 + (ulong)uVar10 * 8) = pCVar16;
          *(int *)(this + 0xb0) = *(int *)(this + 0xb0) + 1;
        }
        uVar21 = uVar21 + 1;
      } while (uVar21 < local_460);
    }
    local_460 = 0;
    local_45c = 0;
    if (local_468 != (wchar_t *)0x0) {
      operator_delete__(local_468);
    }
    local_468 = (wchar_t *)0x0;
                    /* try { // try from 00cc84b0 to 00cc84b4 has its CatchHandler @ 00cc9ee4 */
    std::wstring::wstring((wstring_conflict *)local_288,L"Layout Link Particle",&local_54);
                    /* try { // try from 00cc84c1 to 00cc84c5 has its CatchHandler @ 00cc9ed4 */
    CEditorScene::GetObjectsCreatedByADescriptor
              (*(CEditorScene **)(this + 0x38),(wstring_conflict *)local_288,
               (TArrayList *)&local_468);
    if ((allocator *)(local_288[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_288[0] + -8);
      iVar20 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar20 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_288[0] + -0x18));
      }
    }
    local_488 = (long *)0x0;
    local_480 = 0;
    local_47c = 0;
    local_478 = 5;
    if (local_460 != 0) {
      local_4cc = 0;
      do {
        pwVar18 = local_468;
        if (local_4cc < local_45c) {
          pwVar18 = (wchar_t *)((long)local_468 + (ulong)local_4cc * 8);
        }
        this_00 = *(CParticle **)(*(long *)pwVar18 + 0x1f0);
        if (this_00 != (CParticle *)0x0) {
                    /* try { // try from 00cc8551 to 00cc85b6 has its CatchHandler @ 00cc9f18 */
          CParticle::getAllEmitters(this_00,(TArrayList *)&local_488);
        }
        if (local_480 != 0) {
          uVar19 = 0;
          do {
            uVar21 = (uint)uVar19;
            plVar15 = local_488;
            if (uVar21 < local_47c) {
              plVar15 = local_488 + uVar19;
            }
            iVar20 = std::string::compare((char *)(*plVar15 + 0x128));
            if (iVar20 == 0) {
              plVar15 = local_488;
              if (uVar21 < local_47c) {
                plVar15 = local_488 + uVar19;
              }
              lVar13 = *plVar15;
              pCVar16 = (CRunicCore *)Ogre::NedAllocImpl::allocBytes(0x20,(char *)0x0,0,(char *)0x0)
              ;
                    /* try { // try from 00cc85bd to 00cc85c1 has its CatchHandler @ 00cca225 */
              CRunicCore::CRunicCore(pCVar16);
              *(undefined ***)pCVar16 = &PTR__CLineEmitterWrapper_00ff5bb0;
              *(CParticle **)(pCVar16 + 0x10) = this_00;
              *(long *)(pCVar16 + 0x18) = lVar13;
              uVar10 = *(uint *)(this + 0xb0);
              if (uVar10 < *(uint *)(this + 0xb4)) {
                pvVar17 = *(void **)(this + 0xa8);
              }
              else if (*(long *)(this + 0xa8) == 0) {
                *(uint *)(this + 0xb4) = *(uint *)(this + 0xb8);
                    /* try { // try from 00cc87c4 to 00cc87c8 has its CatchHandler @ 00cc9f18 */
                pvVar17 = operator_new__((ulong)*(uint *)(this + 0xb8) * 8);
                *(void **)(this + 0xa8) = pvVar17;
                uVar10 = *(uint *)(this + 0xb0);
              }
              else {
                uVar23 = *(uint *)(this + 0xb4) + *(int *)(this + 0xb8);
                    /* try { // try from 00cc8604 to 00cc8608 has its CatchHandler @ 00cc9f18 */
                pvVar17 = operator_new__((ulong)uVar23 << 3);
                if (*(int *)(this + 0xb4) != 0) {
                  uVar10 = 0;
                  do {
                    uVar19 = (ulong)uVar10;
                    uVar10 = uVar10 + 1;
                    *(undefined8 *)((long)pvVar17 + uVar19 * 8) =
                         *(undefined8 *)(*(long *)(this + 0xa8) + uVar19 * 8);
                  } while (uVar10 < *(uint *)(this + 0xb4));
                }
                if (*(void **)(this + 0xa8) != (void *)0x0) {
                  operator_delete__(*(void **)(this + 0xa8));
                }
                uVar10 = *(uint *)(this + 0xb0);
                *(void **)(this + 0xa8) = pvVar17;
                *(uint *)(this + 0xb4) = uVar23;
              }
              *(CRunicCore **)((long)pvVar17 + (ulong)uVar10 * 8) = pCVar16;
              *(int *)(this + 0xb0) = *(int *)(this + 0xb0) + 1;
            }
            uVar19 = (ulong)(uVar21 + 1);
          } while (uVar21 + 1 < local_480);
        }
        local_4cc = local_4cc + 1;
      } while (local_4cc < local_460);
    }
    local_460 = 0;
    local_45c = 0;
    if (local_468 != (wchar_t *)0x0) {
      operator_delete__(local_468);
    }
    local_468 = (wchar_t *)0x0;
                    /* try { // try from 00cc86da to 00cc86de has its CatchHandler @ 00cca272 */
    std::wstring::wstring((wstring_conflict *)local_298,L"Sound",&local_55);
                    /* try { // try from 00cc86eb to 00cc86ef has its CatchHandler @ 00cca261 */
    CEditorScene::GetObjectsCreatedByADescriptor
              (*(CEditorScene **)(this + 0x38),(wstring_conflict *)local_298,
               (TArrayList *)&local_468);
    if ((allocator *)(local_298[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_298[0] + -8);
      iVar20 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar20 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_298[0] + -0x18));
      }
    }
    uVar21 = 0;
    if (local_460 != 0) {
      do {
        pwVar18 = local_468;
        if (uVar21 < local_45c) {
          pwVar18 = (wchar_t *)((long)local_468 + (ulong)uVar21 * 8);
        }
        lVar13 = *(long *)pwVar18;
        *(undefined1 *)(lVar13 + 0x120) = 0;
        lVar13 = *(long *)(lVar13 + 0x118);
        if (lVar13 != 0) {
          *(undefined1 *)(lVar13 + 0xa8) = 1;
        }
        uVar21 = uVar21 + 1;
      } while (uVar21 < local_460);
    }
    local_460 = 0;
    local_45c = 0;
    if (local_468 != (wchar_t *)0x0) {
      operator_delete__(local_468);
    }
    local_468 = (wchar_t *)0x0;
                    /* try { // try from 00cc883c to 00cc8840 has its CatchHandler @ 00cca21e */
    std::wstring::wstring((wstring_conflict *)local_2a8,L"Timeline",&local_56);
                    /* try { // try from 00cc884d to 00cc8851 has its CatchHandler @ 00cca20e */
    CEditorScene::GetObjectsCreatedByADescriptor
              (*(CEditorScene **)(this + 0x38),(wstring_conflict *)local_2a8,
               (TArrayList *)&local_468);
    if ((allocator *)(local_2a8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_2a8[0] + -8);
      iVar20 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar20 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_2a8[0] + -0x18));
      }
    }
    uVar21 = 0;
    if (local_460 != 0) {
      do {
        pwVar18 = local_468;
        if (uVar21 < local_45c) {
          pwVar18 = local_468 + (ulong)uVar21 * 2;
        }
        uVar21 = uVar21 + 1;
        *(undefined1 *)(*(long *)pwVar18 + 0x8a) = 0;
      } while (uVar21 < local_460);
    }
                    /* try { // try from 00cc88c9 to 00cc88cd has its CatchHandler @ 00cca1d0 */
    std::wstring::wstring((wstring_conflict *)local_2b8,L"MAKEPET",&local_57);
                    /* try { // try from 00cc88db to 00cc88df has its CatchHandler @ 00cca1cb */
    CVar7 = (CSkillEvent)CDataGroup::GetDataValue(param_4,(wstring_conflict *)local_2b8,true);
    this[0x143] = CVar7;
    if ((allocator *)(local_2b8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_2b8[0] + -8);
      iVar20 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar20 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_2b8[0] + -0x18));
      }
    }
                    /* try { // try from 00cc8918 to 00cc891c has its CatchHandler @ 00cca19a */
    std::wstring::wstring((wstring_conflict *)local_2c8,L"ATTACH_LINE_EMITTER",&local_58);
                    /* try { // try from 00cc8927 to 00cc892b has its CatchHandler @ 00cca18a */
    CVar7 = (CSkillEvent)CDataGroup::GetDataValue(param_4,(wstring_conflict *)local_2c8,false);
    this[0x147] = CVar7;
    if ((allocator *)(local_2c8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_2c8[0] + -8);
      iVar20 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar20 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_2c8[0] + -0x18));
      }
    }
                    /* try { // try from 00cc8964 to 00cc8968 has its CatchHandler @ 00cca159 */
    std::wstring::wstring
              ((wstring_conflict *)local_2d8,L"ATTACH_LINE_EMITTER_TO_MAX_DISTANCE",&local_59);
                    /* try { // try from 00cc8973 to 00cc8977 has its CatchHandler @ 00cca154 */
    CVar7 = (CSkillEvent)CDataGroup::GetDataValue(param_4,(wstring_conflict *)local_2d8,false);
    this[0x148] = CVar7;
    if ((allocator *)(local_2d8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_2d8[0] + -8);
      iVar20 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar20 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_2d8[0] + -0x18));
      }
    }
                    /* try { // try from 00cc89b0 to 00cc89b4 has its CatchHandler @ 00cca324 */
    std::wstring::wstring((wstring_conflict *)local_2e8,L"LINE_EMITTER_COLLIDES",&local_5a);
                    /* try { // try from 00cc89bf to 00cc89c3 has its CatchHandler @ 00cca314 */
    CVar7 = (CSkillEvent)CDataGroup::GetDataValue(param_4,(wstring_conflict *)local_2e8,false);
    this[0x149] = CVar7;
    if ((allocator *)(local_2e8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_2e8[0] + -8);
      iVar20 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar20 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_2e8[0] + -0x18));
      }
    }
                    /* try { // try from 00cc89fc to 00cc8a00 has its CatchHandler @ 00cca35a */
    std::wstring::wstring((wstring_conflict *)local_2f8,L"DAMAGE_REQUIRES_LOS",&local_5b);
                    /* try { // try from 00cc8a0b to 00cc8a0f has its CatchHandler @ 00cca355 */
    CVar7 = (CSkillEvent)CDataGroup::GetDataValue(param_4,(wstring_conflict *)local_2f8,false);
    this[0x14a] = CVar7;
    if ((allocator *)(local_2f8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_2f8[0] + -8);
      iVar20 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar20 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_2f8[0] + -0x18));
      }
    }
                    /* try { // try from 00cc8a48 to 00cc8a4c has its CatchHandler @ 00cca2a7 */
    std::wstring::wstring((wstring_conflict *)local_308,L"MATCH_PET_DURATION",&local_5c);
                    /* try { // try from 00cc8a57 to 00cc8a5b has its CatchHandler @ 00cca3f6 */
    CVar7 = (CSkillEvent)CDataGroup::GetDataValue(param_4,(wstring_conflict *)local_308,false);
    this[0x142] = CVar7;
    if ((allocator *)(local_308[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_308[0] + -8);
      iVar20 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar20 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_308[0] + -0x18));
      }
    }
                    /* try { // try from 00cc8a94 to 00cc8a98 has its CatchHandler @ 00cca2e1 */
    std::wstring::wstring((wstring_conflict *)local_318,L"ATTACHES",&local_5d);
                    /* try { // try from 00cc8aa3 to 00cc8aa7 has its CatchHandler @ 00cca2dc */
    CVar7 = (CSkillEvent)CDataGroup::GetDataValue(param_4,(wstring_conflict *)local_318,false);
    this[0x137] = CVar7;
    if ((allocator *)(local_318[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_318[0] + -8);
      iVar20 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar20 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_318[0] + -0x18));
      }
    }
                    /* try { // try from 00cc8ae0 to 00cc8ae4 has its CatchHandler @ 00cca380 */
    std::wstring::wstring((wstring_conflict *)local_328,L"ATTACHTOTARGET",&local_5e);
                    /* try { // try from 00cc8aef to 00cc8af3 has its CatchHandler @ 00cc9ec4 */
    CVar7 = (CSkillEvent)CDataGroup::GetDataValue(param_4,(wstring_conflict *)local_328,false);
    this[0x13e] = CVar7;
    if ((allocator *)(local_328[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_328[0] + -8);
      iVar20 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar20 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_328[0] + -0x18));
      }
    }
                    /* try { // try from 00cc8b2c to 00cc8b30 has its CatchHandler @ 00cc9529 */
    std::wstring::wstring((wstring_conflict *)local_338,L"ATTACHOWNER",&local_5f);
                    /* try { // try from 00cc8b3b to 00cc8b3f has its CatchHandler @ 00cc9524 */
    CVar7 = (CSkillEvent)CDataGroup::GetDataValue(param_4,(wstring_conflict *)local_338,false);
    this[0x139] = CVar7;
    if ((allocator *)(local_338[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_338[0] + -8);
      iVar20 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar20 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_338[0] + -0x18));
      }
    }
                    /* try { // try from 00cc8b78 to 00cc8b7c has its CatchHandler @ 00cc94e5 */
    std::wstring::wstring((wstring_conflict *)local_348,L"ATTACHIGNORESUNITS",&local_60);
                    /* try { // try from 00cc8b87 to 00cc8b8b has its CatchHandler @ 00cc956e */
    CVar7 = (CSkillEvent)CDataGroup::GetDataValue(param_4,(wstring_conflict *)local_348,false);
    this[0x13c] = CVar7;
    if ((allocator *)(local_348[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_348[0] + -8);
      iVar20 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar20 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_348[0] + -0x18));
      }
    }
                    /* try { // try from 00cc8bc4 to 00cc8bc8 has its CatchHandler @ 00cc94da */
    std::wstring::wstring((wstring_conflict *)local_358,L"ATTACHIGNORESOBSTRUCTIONS",&local_61);
                    /* try { // try from 00cc8bd3 to 00cc8bd7 has its CatchHandler @ 00cc94d5 */
    CVar7 = (CSkillEvent)CDataGroup::GetDataValue(param_4,(wstring_conflict *)local_358,false);
    this[0x13d] = CVar7;
    if ((allocator *)(local_358[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_358[0] + -8);
      iVar20 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar20 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_358[0] + -0x18));
      }
    }
                    /* try { // try from 00cc8c10 to 00cc8c14 has its CatchHandler @ 00cc949e */
    std::wstring::wstring((wstring_conflict *)local_368,L"SCALEATTACHDISTANCE",&local_62);
                    /* try { // try from 00cc8c1f to 00cc8c23 has its CatchHandler @ 00cc9491 */
    CVar7 = (CSkillEvent)CDataGroup::GetDataValue(param_4,(wstring_conflict *)local_368,false);
    this[0x13f] = CVar7;
    if ((allocator *)(local_368[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_368[0] + -8);
      iVar20 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar20 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_368[0] + -0x18));
      }
    }
                    /* try { // try from 00cc8c5c to 00cc8c60 has its CatchHandler @ 00cc9458 */
    std::wstring::wstring((wstring_conflict *)local_378,L"PLACEONTARGET",&local_63);
                    /* try { // try from 00cc8c6b to 00cc8c6f has its CatchHandler @ 00cc944b */
    CVar7 = (CSkillEvent)CDataGroup::GetDataValue(param_4,(wstring_conflict *)local_378,false);
    this[0x14b] = CVar7;
    if ((allocator *)(local_378[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_378[0] + -8);
      iVar20 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar20 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_378[0] + -0x18));
      }
    }
                    /* try { // try from 00cc8ca8 to 00cc8cac has its CatchHandler @ 00cc93f5 */
    std::wstring::wstring((wstring_conflict *)local_388,L"SYNCH_PETS_TO_OWNER",&local_64);
                    /* try { // try from 00cc8cb7 to 00cc8cbb has its CatchHandler @ 00cc9624 */
    CVar7 = (CSkillEvent)CDataGroup::GetDataValue(param_4,(wstring_conflict *)local_388,false);
    this[0x14e] = CVar7;
    if ((allocator *)(local_388[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_388[0] + -8);
      iVar20 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar20 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_388[0] + -0x18));
      }
    }
                    /* try { // try from 00cc8cf4 to 00cc8cf8 has its CatchHandler @ 00cc95e6 */
    std::wstring::wstring((wstring_conflict *)local_398,L"MISSILE_TARGET_SELF",&local_65);
                    /* try { // try from 00cc8d03 to 00cc8d07 has its CatchHandler @ 00cc95e1 */
    CVar7 = (CSkillEvent)CDataGroup::GetDataValue(param_4,(wstring_conflict *)local_398,false);
    this[0x14f] = CVar7;
    if ((allocator *)(local_398[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_398[0] + -8);
      iVar20 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar20 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_398[0] + -0x18));
      }
    }
                    /* try { // try from 00cc8d40 to 00cc8d44 has its CatchHandler @ 00cc95a9 */
    std::wstring::wstring((wstring_conflict *)local_3a8,L"FIREFROMBONE",&local_66);
                    /* try { // try from 00cc8d52 to 00cc8d69 has its CatchHandler @ 00cc95a4 */
    pwVar12 = (wstring_conflict *)
              CDataGroup::GetDataValue
                        (param_4,(wstring_conflict *)local_3a8,(wstring_conflict *)&::EMPTY_WSTRING)
    ;
    STRINGS::StringUpper((STRINGS *)local_3b8,pwVar12);
                    /* try { // try from 00cc8d7c to 00cc8d80 has its CatchHandler @ 00cc958c */
    uVar27 = STRINGS::getStringIndex
                       ((wstring_conflict *)local_3b8,
                        (wstring_conflict *)::gSKILL_BONE_ATTACHMENT_NAMES,8,0,false);
    *(undefined4 *)(this + 0x108) = uVar27;
    if ((allocator *)(local_3b8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_3b8[0] + -8);
      iVar20 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar20 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_3b8[0] + -0x18));
      }
    }
    if ((allocator *)(local_3a8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_3a8[0] + -8);
      iVar20 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar20 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_3a8[0] + -0x18));
      }
    }
                    /* try { // try from 00cc8dd3 to 00cc8dd7 has its CatchHandler @ 00cc9644 */
    std::wstring::wstring((wstring_conflict *)local_3c8,L"FIREATBONE",&local_67);
                    /* try { // try from 00cc8de5 to 00cc8dfc has its CatchHandler @ 00cc963f */
    pwVar12 = (wstring_conflict *)
              CDataGroup::GetDataValue
                        (param_4,(wstring_conflict *)local_3c8,(wstring_conflict *)&::EMPTY_WSTRING)
    ;
    STRINGS::StringUpper((STRINGS *)local_3d8,pwVar12);
                    /* try { // try from 00cc8e0f to 00cc8e13 has its CatchHandler @ 00cc96e3 */
    uVar27 = STRINGS::getStringIndex
                       ((wstring_conflict *)local_3d8,
                        (wstring_conflict *)::gSKILL_BONE_ATTACHMENT_NAMES,8,0,false);
    *(undefined4 *)(this + 0x10c) = uVar27;
    if ((allocator *)(local_3d8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_3d8[0] + -8);
      iVar20 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar20 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_3d8[0] + -0x18));
      }
    }
    if ((allocator *)(local_3c8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_3c8[0] + -8);
      iVar20 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar20 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_3c8[0] + -0x18));
      }
    }
    if (local_488 != (long *)0x0) {
      operator_delete__(local_488);
      local_488 = (long *)0x0;
    }
    if (local_468 != (wchar_t *)0x0) {
      operator_delete__(local_468);
      local_468 = (wchar_t *)0x0;
    }
  }
  bVar24 = false;
                    /* try { // try from 00cc8ea9 to 00cc8ec1 has its CatchHandler @ 00cc9902 */
  std::wstring::wstring((wstring_conflict *)local_3e8,L"EFFECT",&local_68);
  lVar13 = CDataGroup::GetDataGroupByName(param_4,(wstring_conflict *)local_3e8,false);
  if (lVar13 == 0) {
                    /* try { // try from 00cc9855 to 00cc98a8 has its CatchHandler @ 00cc9902 */
    std::wstring::wstring((wstring_conflict *)local_3f8,L"EFFECTS",&local_69);
    bVar24 = true;
    lVar13 = CDataGroup::GetDataGroupByName(param_4,(wstring_conflict *)local_3f8,false);
    if (lVar13 != 0) goto LAB_00cc8ecb;
    std::wstring::wstring((wstring_conflict *)local_408,L"AFFIXES",&local_6a);
    lVar13 = CDataGroup::GetDataGroupByName(param_4,(wstring_conflict *)local_408,false);
    bVar25 = true;
    if (lVar13 == 0) {
                    /* try { // try from 00cc9978 to 00cc9991 has its CatchHandler @ 00cc9902 */
      std::wstring::wstring((wstring_conflict *)local_418,L"AFFIXESREMOVE",&local_6b);
      lVar13 = CDataGroup::GetDataGroupByName(param_4,(wstring_conflict *)local_418,false);
      bVar25 = lVar13 != 0;
      if ((allocator *)(local_418[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar2 = (int *)(local_418[0] + -8);
        iVar20 = *piVar2;
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (iVar20 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_418[0] + -0x18));
        }
      }
    }
    if ((allocator *)(local_408[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_408[0] + -8);
      iVar20 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar20 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_408[0] + -0x18));
      }
    }
LAB_00cc8ed5:
    if ((allocator *)(local_3f8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_3f8[0] + -8);
      iVar20 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar20 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_3f8[0] + -0x18));
      }
    }
  }
  else {
LAB_00cc8ecb:
    bVar25 = true;
    if (bVar24) goto LAB_00cc8ed5;
  }
  if ((allocator *)(local_3e8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_3e8[0] + -8);
    iVar20 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar20 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_3e8[0] + -0x18));
    }
  }
  if (bVar25) {
    CVar7 = this[0x141];
                    /* try { // try from 00cc8f32 to 00cc8f36 has its CatchHandler @ 00cc9a2e */
    std::wstring::wstring((wstring_conflict *)local_428,L"APPLYEFFECTSALWAYS",&local_6c);
                    /* try { // try from 00cc8f42 to 00cc8f46 has its CatchHandler @ 00cc9a29 */
    CVar7 = (CSkillEvent)CDataGroup::GetDataValue(param_4,(wstring_conflict *)local_428,(bool)CVar7)
    ;
    this[0x141] = CVar7;
    if ((allocator *)(local_428[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar2 = (int *)(local_428[0] + -8);
      iVar20 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar20 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_428[0] + -0x18));
      }
    }
                    /* try { // try from 00cc8f72 to 00cc8f76 has its CatchHandler @ 00cca0e5 */
    this_05 = (CSkillEffectAndAffixes *)
              Ogre::NedAllocImpl::allocBytes(0x98,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00cc8f88 to 00cc8f8c has its CatchHandler @ 00cc99ed */
    CSkillEffectAndAffixes::CSkillEffectAndAffixes
              (this_05,*(CSkill **)(this + 0x28),param_4,(CSkillEffectAndAffixes *)0x0);
    *(CSkillEffectAndAffixes **)(this + 0xa0) = this_05;
  }
                    /* try { // try from 00cc8f97 to 00cc8f9b has its CatchHandler @ 00cca0e5 */
  addListeners(this);
  local_4a8 = (void *)0x0;
  local_4a0 = 0;
  local_498 = 0;
                    /* try { // try from 00cc8fcf to 00cc8fd3 has its CatchHandler @ 00cc980b */
  std::wstring::wstring((wstring_conflict *)local_438,L"EXECUTE_SKILL",&local_6d);
                    /* try { // try from 00cc8fe1 to 00cc8fe5 has its CatchHandler @ 00cc97fe */
  CDataGroup::GetDataGroupsMatchingName(param_4,(wstring_conflict *)local_438,(vector *)&local_4a8);
  if ((allocator *)(local_438[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_438[0] + -8);
    iVar20 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar20 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_438[0] + -0x18));
    }
  }
  if (local_4a0 - (long)local_4a8 >> 3 != 0) {
    uVar19 = 0;
    uVar21 = 0;
    do {
      pCVar6 = *(CDataGroup **)((long)local_4a8 + uVar19 * 8);
                    /* try { // try from 00cc9065 to 00cc9069 has its CatchHandler @ 00cc97cf */
      this_06 = (CExecuteSkillProps *)Ogre::NedAllocImpl::allocBytes(0x28,(char *)0x0,0,(char *)0x0)
      ;
                    /* try { // try from 00cc907b to 00cc907f has its CatchHandler @ 00cc97cd */
      CExecuteSkillProps::CExecuteSkillProps(this_06,param_1,this,pCVar6);
      uVar10 = *(uint *)(this + 0x118);
      if (uVar10 < *(uint *)(this + 0x11c)) {
        pvVar17 = *(void **)(this + 0x110);
      }
      else if (*(long *)(this + 0x110) == 0) {
        *(uint *)(this + 0x11c) = *(uint *)(this + 0x120);
        pvVar17 = operator_new__((ulong)*(uint *)(this + 0x120) << 3);
        *(void **)(this + 0x110) = pvVar17;
        uVar10 = *(uint *)(this + 0x118);
      }
      else {
        uVar10 = *(uint *)(this + 0x11c) + *(int *)(this + 0x120);
                    /* try { // try from 00cc90aa to 00cc911c has its CatchHandler @ 00cc97cf */
        pvVar17 = operator_new__((ulong)uVar10 << 3);
        if (*(int *)(this + 0x11c) != 0) {
          uVar23 = 0;
          do {
            uVar19 = (ulong)uVar23;
            uVar23 = uVar23 + 1;
            *(undefined8 *)((long)pvVar17 + uVar19 * 8) =
                 *(undefined8 *)(*(long *)(this + 0x110) + uVar19 * 8);
          } while (uVar23 < *(uint *)(this + 0x11c));
        }
        if (*(void **)(this + 0x110) != (void *)0x0) {
          operator_delete__(*(void **)(this + 0x110));
        }
        *(void **)(this + 0x110) = pvVar17;
        *(uint *)(this + 0x11c) = uVar10;
        uVar10 = *(uint *)(this + 0x118);
      }
      uVar21 = uVar21 + 1;
      *(CExecuteSkillProps **)((long)pvVar17 + (ulong)uVar10 * 8) = this_06;
      *(int *)(this + 0x118) = *(int *)(this + 0x118) + 1;
      uVar19 = (ulong)uVar21;
    } while (uVar19 < (ulong)(local_4a0 - (long)local_4a8 >> 3));
  }
                    /* try { // try from 00cc75b4 to 00cc75b8 has its CatchHandler @ 00cc97bb */
  std::wstring::wstring((wstring_conflict *)local_448,L"EXECUTE_SKILL_COUNT",&local_6e);
                    /* try { // try from 00cc75c3 to 00cc75c7 has its CatchHandler @ 00cc978d */
  uVar27 = CDataGroup::GetDataValue(param_4,(wstring_conflict *)local_448,0);
  *(undefined4 *)(this + 0x130) = uVar27;
  if ((allocator *)(local_448[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_448[0] + -8);
    iVar20 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar20 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_448[0] + -0x18));
    }
  }
  if ((*(int *)(this + 0x118) != 0) && (0 < *(int *)(this + 0x130))) {
                    /* try { // try from 00cc7605 to 00cc7609 has its CatchHandler @ 00cc97cf */
    this_01 = (CRandomizer *)Ogre::NedAllocImpl::allocBytes(0x68,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00cc7615 to 00cc7619 has its CatchHandler @ 00cc97c0 */
    CRandomizer::CRandomizer(this_01,0);
    *(CRandomizer **)(this + 0x128) = this_01;
    if (*(int *)(this + 0x118) != 0) {
      uVar21 = 0;
      while( true ) {
                    /* try { // try from 00cc7641 to 00cc7645 has its CatchHandler @ 00cc97cf */
        CRandomizer::addChoice(this_01,uVar21,100);
        uVar21 = uVar21 + 1;
        if (*(uint *)(this + 0x118) <= uVar21) break;
        this_01 = *(CRandomizer **)(this + 0x128);
      }
    }
  }
  if (local_4a8 != (void *)0x0) {
    operator_delete(local_4a8);
  }
  if ((allocator *)(local_148[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    pwVar18 = local_148[0] + -2;
    wVar3 = *pwVar18;
    *pwVar18 = *pwVar18 + L'\xffffffff';
    UNLOCK();
    if (wVar3 < L'\x01') {
      std::wstring::_Rep::_M_destroy((allocator *)(local_148[0] + -6));
    }
  }
LAB_00cc769d:
  fVar26 = 0.0;
  if (param_2 != (CSkillProperty *)0x0) {
    fVar26 = *(float *)(param_2 + 0xa4);
  }
  if (fVar26 <= *(float *)(this + 0x158)) {
    fVar26 = *(float *)(this + 0x158);
  }
  if ((0.0 < fVar26) && (*(CSkillEffectAndAffixes **)(this + 0xa0) != (CSkillEffectAndAffixes *)0x0)
     ) {
                    /* try { // try from 00cc76d1 to 00cc76d5 has its CatchHandler @ 00cc9b65 */
    CSkillEffectAndAffixes::setDurationOverride(*(CSkillEffectAndAffixes **)(this + 0xa0),fVar26);
  }
  return;
}



/* address=00cca440
   symbol=CSkillEvent::CLineEmitterWrapper::~CLineEmitterWrapper */

/* CSkillEvent::CLineEmitterWrapper::~CLineEmitterWrapper() */

void __thiscall CSkillEvent::CLineEmitterWrapper::~CLineEmitterWrapper(CLineEmitterWrapper *this)

{
  *(undefined ***)this = &PTR__CLineEmitterWrapper_00ff5bb0;
  CRunicCore::~CRunicCore((CRunicCore *)this);
  return;
}



/* address=00cca470
   symbol=CSkillEvent::CLineEmitterWrapper::~CLineEmitterWrapper */

/* CSkillEvent::CLineEmitterWrapper::~CLineEmitterWrapper() */

void __thiscall CSkillEvent::CLineEmitterWrapper::~CLineEmitterWrapper(CLineEmitterWrapper *this)

{
  *(undefined ***)this = &PTR__CLineEmitterWrapper_00ff5bb0;
  CRunicCore::~CRunicCore((CRunicCore *)this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}



/* address=00cca490
   symbol=CSkillEvent::CSkillEventPause::~CSkillEventPause */

/* CSkillEvent::CSkillEventPause::~CSkillEventPause() */

void __thiscall CSkillEvent::CSkillEventPause::~CSkillEventPause(CSkillEventPause *this)

{
  *(undefined ***)this = &PTR__CSkillEventPause_00ff5c30;
  if (*(CRunicCore **)(this + 0x40) != (CRunicCore *)0x0) {
                    /* try { // try from 00cca4af to 00cca4b3 has its CatchHandler @ 00cca4d0 */
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(this + 0x40),(TSafePointer *)(this + 0x40),*(uint *)(this + 0x48));
  }
  *(undefined8 *)(this + 0x40) = 0;
  *(undefined4 *)(this + 0x48) = 0xffffffff;
  CRunicCore::~CRunicCore((CRunicCore *)this);
  return;
}



/* address=00cca4f0
   symbol=CSkillEvent::CSkillEventPause::~CSkillEventPause */

/* CSkillEvent::CSkillEventPause::~CSkillEventPause() */

void __thiscall CSkillEvent::CSkillEventPause::~CSkillEventPause(CSkillEventPause *this)

{
  *(undefined ***)this = &PTR__CSkillEventPause_00ff5c30;
  if (*(CRunicCore **)(this + 0x40) != (CRunicCore *)0x0) {
                    /* try { // try from 00cca50f to 00cca513 has its CatchHandler @ 00cca538 */
    CRunicCore::removeSafePointer
              (*(CRunicCore **)(this + 0x40),(TSafePointer *)(this + 0x40),*(uint *)(this + 0x48));
  }
  *(undefined8 *)(this + 0x40) = 0;
  *(undefined4 *)(this + 0x48) = 0xffffffff;
  CRunicCore::~CRunicCore((CRunicCore *)this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}



/* export-summary functions=51 failures=0 */
