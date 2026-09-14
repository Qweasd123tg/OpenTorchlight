/* Targeted Ghidra class export.
   namespace=CMonster
   Treat pseudocode as navigation evidence. */


/* address=008d4ba0
   symbol=CMonster::getRangeAI */

/* CMonster::getRangeAI(float, CLevel&) */

void CMonster::getRangeAI(float param_1,CLevel *param_2)

{
  param_2[0x321] = (CLevel)0x1;
  if (param_2[0x264] != (CLevel)0x0) {
    return;
  }
  if (*(long *)(param_2 + 0x340) != 0) {
                    /* WARNING: Could not recover jumptable at 0x008d4bc9. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*(long *)param_2 + 0x348))(param_2,4);
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x008d4be7. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)param_2 + 0x348))(param_2,2);
  return;
}

/* address=008d4bf0
   symbol=CMonster::hasOffensiveSkill */

/* CMonster::hasOffensiveSkill() */

undefined8 __thiscall CMonster::hasOffensiveSkill(CMonster *this)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined8 *puVar5;
  long lVar6;
  uint uVar7;
  uint uVar8;
  long *plVar9;
  CSkill *this_00;
  long lVar10;

  if (*(CSkillManager **)(this + 0x1c8) != (CSkillManager *)0x0) {
    iVar2 = CSkillManager::knownSkills(*(CSkillManager **)(this + 0x1c8),0);
    lVar6 = *(long *)(this + 0x1c8);
    uVar7 = *(uint *)(lVar6 + 0x68);
    if (uVar7 != 0) {
      plVar9 = *(long **)(lVar6 + 0x60);
      uVar8 = 0;
      lVar10 = *plVar9;
      while ((*(long *)(this + 0x398) != lVar10 && (uVar8 = uVar8 + 1, uVar8 < uVar7))) {
        lVar10 = plVar9[1];
        plVar9 = plVar9 + 1;
      }
    }
    if (0 < iVar2) {
      lVar10 = 0;
      uVar8 = 0;
      while( true ) {
        this_00 = (CSkill *)0x0;
        if ((int)uVar8 < (int)uVar7) {
          if (uVar8 < *(uint *)(lVar6 + 0x6c)) {
            puVar5 = (undefined8 *)(lVar10 + *(long *)(lVar6 + 0x60));
          }
          else {
            puVar5 = *(undefined8 **)(lVar6 + 0x60);
          }
          this_00 = (CSkill *)*puVar5;
        }
        iVar3 = CCharacter::mana((CCharacter *)this);
        iVar4 = CSkill::getManaCost(this_00);
        if (iVar4 <= iVar3) {
          iVar3 = CCharacter::mana((CCharacter *)this);
          iVar4 = CSkill::getManaCostOT(this_00);
          if ((iVar4 <= iVar3) &&
             (cVar1 = CSkillManager::getSkillIsCooling(*(CSkillManager **)(this + 0x1c8),this_00),
             cVar1 == '\0')) {
            lVar6 = *(long *)(this_00 + 0x90);
            if ((lVar6 == 0) && (*(int *)(this_00 + 0xa8) != 0)) {
              lVar6 = **(long **)(this_00 + 0xa0);
            }
            if ((*(int *)(lVar6 + 0x50) == 2) &&
               (((byte)this_00[0x6d] & ((byte)this_00[0x6b] ^ 1)) != 0)) {
              return 1;
            }
          }
        }
        uVar8 = uVar8 + 1;
        lVar10 = lVar10 + 8;
        if (iVar2 <= (int)uVar8) break;
        lVar6 = *(long *)(this + 0x1c8);
        uVar7 = *(uint *)(lVar6 + 0x68);
      }
    }
  }
  return 0;
}

/* address=008d4d60
   symbol=CMonster::hasDefensiveSkill */

/* CMonster::hasDefensiveSkill() */

undefined8 __thiscall CMonster::hasDefensiveSkill(CMonster *this)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined8 *puVar5;
  long lVar6;
  uint uVar7;
  long lVar8;
  uint uVar9;
  long *plVar10;
  CSkill *this_00;
  long lVar11;

  if (*(CSkillManager **)(this + 0x1c8) != (CSkillManager *)0x0) {
    iVar2 = CSkillManager::knownSkills(*(CSkillManager **)(this + 0x1c8),0);
    lVar6 = *(long *)(this + 0x1c8);
    uVar7 = *(uint *)(lVar6 + 0x68);
    if (uVar7 != 0) {
      plVar10 = *(long **)(lVar6 + 0x60);
      uVar9 = 0;
      lVar11 = *plVar10;
      while ((*(long *)(this + 0x398) != lVar11 && (uVar9 = uVar9 + 1, uVar9 < uVar7))) {
        lVar11 = plVar10[1];
        plVar10 = plVar10 + 1;
      }
    }
    if (0 < iVar2) {
      lVar11 = 0;
      uVar9 = 0;
      do {
        this_00 = (CSkill *)0x0;
        if ((int)uVar9 < (int)uVar7) {
          if (uVar9 < *(uint *)(lVar6 + 0x6c)) {
            puVar5 = (undefined8 *)(lVar11 + *(long *)(lVar6 + 0x60));
          }
          else {
            puVar5 = *(undefined8 **)(lVar6 + 0x60);
          }
          this_00 = (CSkill *)*puVar5;
        }
        iVar3 = CCharacter::mana((CCharacter *)this);
        iVar4 = CSkill::getManaCost(this_00);
        if (iVar4 <= iVar3) {
          iVar3 = CCharacter::mana((CCharacter *)this);
          iVar4 = CSkill::getManaCostOT(this_00);
          if ((iVar4 <= iVar3) &&
             (cVar1 = CSkillManager::getSkillIsCooling(*(CSkillManager **)(this + 0x1c8),this_00),
             cVar1 == '\0')) {
            lVar6 = *(long *)(this_00 + 0x90);
            lVar8 = lVar6;
            if ((lVar6 == 0) && (*(int *)(this_00 + 0xa8) != 0)) {
              lVar8 = **(long **)(this_00 + 0xa0);
            }
            if (*(int *)(lVar8 + 0x70) != 3) {
              lVar8 = lVar6;
              if ((lVar6 == 0) && (*(int *)(this_00 + 0xa8) != 0)) {
                lVar8 = **(long **)(this_00 + 0xa0);
              }
              if (*(int *)(lVar8 + 0x70) != 10) {
                if ((lVar6 == 0) && (*(int *)(this_00 + 0xa8) != 0)) {
                  lVar6 = **(long **)(this_00 + 0xa0);
                }
                if (((*(int *)(lVar6 + 0x70) != 9) && (*(int *)(this_00 + 0x5c) != 2)) &&
                   (*(int *)(this_00 + 0x5c) != 3)) goto LAB_008d4dd8;
              }
            }
            if (((byte)this_00[0x6d] & ((byte)this_00[0x6b] ^ 1)) != 0) {
              return 1;
            }
          }
        }
LAB_008d4dd8:
        uVar9 = uVar9 + 1;
        lVar11 = lVar11 + 8;
        if (iVar2 <= (int)uVar9) {
          return 0;
        }
        lVar6 = *(long *)(this + 0x1c8);
        uVar7 = *(uint *)(lVar6 + 0x68);
      } while( true );
    }
  }
  return 0;
}

/* address=008d4f60
   symbol=CMonster::selectOffensiveSkill */

/* CMonster::selectOffensiveSkill(bool) */

void __thiscall CMonster::selectOffensiveSkill(CMonster *this,bool param_1)

{
  CRandomizer *this_00;
  CSkill *pCVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  long lVar7;
  undefined8 *puVar8;
  long *plVar9;
  uint uVar10;
  CSkill *pCVar11;
  long lVar12;
  CSkill *local_48;

  if (*(long *)(this + 0x1c8) != 0) {
    iVar3 = CSkillManager::knownSkills();
    pCVar11 = *(CSkill **)(this + 0x398);
    uVar10 = *(uint *)(*(long *)(this + 0x1c8) + 0x68);
    if (uVar10 != 0) {
      plVar9 = *(long **)(*(long *)(this + 0x1c8) + 0x60);
      uVar4 = 0;
      pCVar1 = (CSkill *)*plVar9;
      while ((pCVar11 != pCVar1 && (uVar4 = uVar4 + 1, uVar4 < uVar10))) {
        pCVar1 = (CSkill *)plVar9[1];
        plVar9 = plVar9 + 1;
      }
    }
    if (0 < iVar3) {
      this_00 = (CRandomizer *)(this + 0x780);
      lVar12 = 0;
      uVar10 = 0;
      CRandomizer::clear(this_00);
      CCharacter::setActiveSkill((CCharacter *)this,(CSkill *)0x0,false);
      do {
        lVar7 = *(long *)(this + 0x1c8);
        local_48 = (CSkill *)0x0;
        if ((int)uVar10 < *(int *)(lVar7 + 0x68)) {
          if (uVar10 < *(uint *)(lVar7 + 0x6c)) {
            puVar8 = (undefined8 *)(lVar12 + *(long *)(lVar7 + 0x60));
          }
          else {
            puVar8 = *(undefined8 **)(lVar7 + 0x60);
          }
          local_48 = (CSkill *)*puVar8;
        }
        iVar5 = CCharacter::mana((CCharacter *)this);
        iVar6 = CSkill::getManaCost(local_48);
        if (iVar6 <= iVar5) {
          iVar5 = CCharacter::mana((CCharacter *)this);
          iVar6 = CSkill::getManaCostOT(local_48);
          if ((iVar6 <= iVar5) &&
             (cVar2 = CSkillManager::getSkillIsCooling(*(CSkillManager **)(this + 0x1c8),local_48),
             cVar2 == '\0')) {
            lVar7 = *(long *)(local_48 + 0x90);
            if ((lVar7 == 0) && (*(int *)(local_48 + 0xa8) != 0)) {
              lVar7 = **(long **)(local_48 + 0xa0);
            }
            if (((*(int *)(lVar7 + 0x50) == 2) || (*(int *)(local_48 + 0x5c) == 1)) &&
               (((byte)local_48[0x6d] & ((byte)local_48[0x6b] ^ 1)) != 0)) {
              if (param_1) {
                CCharacter::setActiveSkill((CCharacter *)this,local_48,false);
                cVar2 = CCharacter::canCastCurrentSkill
                                  ((CBaseUnit *)this,SUB81(*(undefined8 *)(this + 0x340),0),false);
                if (cVar2 == '\0') goto joined_r0x008d500a;
              }
              CRandomizer::addChoice(this_00,uVar10,1);
            }
          }
        }
joined_r0x008d500a:
        lVar12 = lVar12 + 8;
        uVar10 = uVar10 + 1;
        if (iVar3 <= (int)uVar10) {
          if (*(int *)(this + 0x7b0) != 0) {
            uVar10 = CRandomizer::getRandom(this_00);
            lVar12 = *(long *)(this + 0x1c8);
            if (((int)uVar10 < *(int *)(lVar12 + 0x68)) && (uVar10 != 0xffffffff)) {
              if (uVar10 < *(uint *)(lVar12 + 0x6c)) {
                puVar8 = (undefined8 *)((ulong)uVar10 * 8 + *(long *)(lVar12 + 0x60));
              }
              else {
                puVar8 = *(undefined8 **)(lVar12 + 0x60);
              }
              pCVar11 = (CSkill *)*puVar8;
            }
            else {
              pCVar11 = (CSkill *)0x0;
            }
          }
          CCharacter::setActiveSkill((CCharacter *)this,pCVar11,false);
          return;
        }
      } while( true );
    }
  }
  return;
}

/* address=008d51d0
   symbol=CMonster::notifyAISkillComplete */

/* CMonster::notifyAISkillComplete() */

void __thiscall CMonster::notifyAISkillComplete(CMonster *this)

{
  selectOffensiveSkill(this,false);
  return;
}

/* address=008d51e0
   symbol=CMonster::selectDefensiveSkill */

/* CMonster::selectDefensiveSkill() */

void __thiscall CMonster::selectDefensiveSkill(CMonster *this)

{
  CRandomizer *this_00;
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  long lVar6;
  undefined8 *puVar7;
  long *plVar8;
  long lVar9;
  uint uVar10;
  CSkill *pCVar11;
  long lVar12;

  if (*(CSkillManager **)(this + 0x1c8) != (CSkillManager *)0x0) {
    iVar2 = CSkillManager::knownSkills(*(CSkillManager **)(this + 0x1c8),0);
    uVar5 = *(uint *)(*(long *)(this + 0x1c8) + 0x68);
    if (uVar5 != 0) {
      plVar8 = *(long **)(*(long *)(this + 0x1c8) + 0x60);
      uVar10 = 0;
      lVar12 = *plVar8;
      while ((*(long *)(this + 0x398) != lVar12 && (uVar10 = uVar10 + 1, uVar10 < uVar5))) {
        lVar12 = plVar8[1];
        plVar8 = plVar8 + 1;
      }
    }
    if (0 < iVar2) {
      this_00 = (CRandomizer *)(this + 0x780);
      lVar12 = 0;
      CRandomizer::clear(this_00);
      CCharacter::setActiveSkill((CCharacter *)this,(CSkill *)0x0,false);
      uVar5 = 0;
      do {
        while( true ) {
          lVar6 = *(long *)(this + 0x1c8);
          pCVar11 = (CSkill *)0x0;
          if ((int)uVar5 < *(int *)(lVar6 + 0x68)) {
            if (uVar5 < *(uint *)(lVar6 + 0x6c)) {
              puVar7 = (undefined8 *)(lVar12 + *(long *)(lVar6 + 0x60));
            }
            else {
              puVar7 = *(undefined8 **)(lVar6 + 0x60);
            }
            pCVar11 = (CSkill *)*puVar7;
          }
          iVar3 = CCharacter::mana((CCharacter *)this);
          iVar4 = CSkill::getManaCost(pCVar11);
          if (iVar4 <= iVar3) break;
LAB_008d5270:
          uVar5 = uVar5 + 1;
          lVar12 = lVar12 + 8;
          if (iVar2 <= (int)uVar5) goto LAB_008d5378;
        }
        iVar3 = CCharacter::mana((CCharacter *)this);
        iVar4 = CSkill::getManaCostOT(pCVar11);
        if ((iVar3 < iVar4) ||
           (cVar1 = CSkillManager::getSkillIsCooling(*(CSkillManager **)(this + 0x1c8),pCVar11),
           cVar1 != '\0')) goto LAB_008d5270;
        lVar6 = *(long *)(pCVar11 + 0x90);
        lVar9 = lVar6;
        if ((lVar6 == 0) && (*(int *)(pCVar11 + 0xa8) != 0)) {
          lVar9 = **(long **)(pCVar11 + 0xa0);
        }
        if (*(int *)(lVar9 + 0x70) != 3) {
          lVar9 = lVar6;
          if ((lVar6 == 0) && (*(int *)(pCVar11 + 0xa8) != 0)) {
            lVar9 = **(long **)(pCVar11 + 0xa0);
          }
          if (*(int *)(lVar9 + 0x70) != 10) {
            if ((lVar6 == 0) && (*(int *)(pCVar11 + 0xa8) != 0)) {
              lVar6 = **(long **)(pCVar11 + 0xa0);
            }
            if ((*(int *)(lVar6 + 0x70) != 9) && (*(int *)(pCVar11 + 0x5c) != 2)) goto LAB_008d5270;
          }
        }
        if ((*(int *)(pCVar11 + 0x120) == 2) ||
           (((byte)pCVar11[0x6d] & ((byte)pCVar11[0x6b] ^ 1)) == 0)) goto LAB_008d5270;
        uVar10 = uVar5 + 1;
        lVar12 = lVar12 + 8;
        CRandomizer::addChoice(this_00,uVar5,1);
        uVar5 = uVar10;
      } while ((int)uVar10 < iVar2);
LAB_008d5378:
      if (*(int *)(this + 0x7b0) != 0) {
        uVar5 = CRandomizer::getRandom(this_00);
        lVar12 = *(long *)(this + 0x1c8);
        if (((int)uVar5 < *(int *)(lVar12 + 0x68)) && (uVar5 != 0xffffffff)) {
          if (uVar5 < *(uint *)(lVar12 + 0x6c)) {
            puVar7 = (undefined8 *)((ulong)uVar5 * 8 + *(long *)(lVar12 + 0x60));
          }
          else {
            puVar7 = *(undefined8 **)(lVar12 + 0x60);
          }
          pCVar11 = (CSkill *)*puVar7;
        }
        else {
          pCVar11 = (CSkill *)0x0;
        }
        CCharacter::setActiveSkill((CCharacter *)this,pCVar11,false);
        return;
      }
    }
  }
  return;
}

/* address=008d5470
   symbol=CMonster::reactToDamage */

/* CMonster::reactToDamage(CCharacter*, bool) */

void __thiscall CMonster::reactToDamage(CMonster *this,CCharacter *param_1,bool param_2)

{
  uint uVar1;
  char cVar2;
  int iVar3;
  long lVar4;
  CLevel *pCVar5;
  CDynamicPropertyFile *this_00;
  float fVar6;
  float fVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  float fVar10;
  float fVar11;
  float local_68;
  float fStack_64;
  float local_58;
  float fStack_54;
  wstring_conflict local_48 [16];
  string local_38 [14];
  allocator local_2a;
  allocator local_29 [9];

  cVar2 = CCharacter::alive((CCharacter *)this);
  if (cVar2 == '\0') {
    return;
  }
  lVar4 = 0;
  if (*(int *)(*(long *)(this + 0x68) + 0x30) != 0) {
    lVar4 = **(long **)(*(long *)(this + 0x68) + 0x28);
  }
  if (*(int *)(lVar4 + 0x390c) == 1) {
    return;
  }
  iVar3 = *(int *)(this + 0x330);
  if (iVar3 == 0x10) {
    return;
  }
  if (iVar3 == 0x29) {
    return;
  }
  if (iVar3 == 0x28) {
    return;
  }
  if (iVar3 == 0x23) {
    return;
  }
  if (iVar3 == 0x2a) {
    return;
  }
  if (iVar3 == 1) {
                    /* try { // try from 008d58eb to 008d58ef has its CatchHandler @ 008d5985 */
    std::string::string(local_38,"IDLE",local_29);
                    /* try { // try from 008d5913 to 008d5917 has its CatchHandler @ 008d5972 */
    CCharacter::blendAnimation
              ((string *)this,SUB81(local_38,0),DAT_00fa480c,DAT_00fa47fc,DAT_00fa8760);
                    /* try { // try from 008d591b to 008d591f has its CatchHandler @ 008d5985 */
    std::string::~string(local_38);
  }
  if (param_1 != (CCharacter *)0x0) {
    if (this == (CMonster *)param_1) {
      return;
    }
    if (*(int *)(this + 0x330) == 10) {
      return;
    }
    cVar2 = CCharacter::isPetNearDeath((CCharacter *)this);
    uVar1 = KSETTINGS_PLAYER_UNTARGETABLE;
    if (cVar2 != '\0') {
      return;
    }
    this_00 = (CDynamicPropertyFile *)0x0;
    if (*(long *)(this + 0x68) != 0) {
      lVar4 = CMasterResourceManager::getSingleton();
      this_00 = *(CDynamicPropertyFile **)(lVar4 + 0x90);
    }
    iVar3 = CDynamicPropertyFile::GetInt(this_00,uVar1);
    if (iVar3 != 1) {
      *(undefined4 *)(this + 0x524) =
           *(undefined4 *)(KAIThinkTime + (long)*(int *)(this + 0x520) * 4);
      if ((param_2) && (cVar2 = CBaseUnit::ISA((CBaseUnit *)this,0xa7), cVar2 != '\0')) {
                    /* try { // try from 008d5955 to 008d5959 has its CatchHandler @ 008d5997 */
        std::wstring::wstring(local_48,L"MIMICIDLE",&local_2a);
                    /* try { // try from 008d5960 to 008d5964 has its CatchHandler @ 008d598a */
        CBaseUnit::removeUnitTheme((CBaseUnit *)this,local_48);
                    /* try { // try from 008d5968 to 008d596c has its CatchHandler @ 008d5997 */
        std::wstring::~wstring(local_48);
      }
      iVar3 = CCharacter::maxHP((CCharacter *)this);
      fVar10 = (float)iVar3;
      iVar3 = CCharacter::HP((CCharacter *)this);
      fVar11 = fVar10;
      if ((float)iVar3 <= fVar10) {
        fVar11 = (float)iVar3;
      }
      if (((fVar10 <= DAT_00fa47f8) || (!param_2)) ||
         ((*(int *)(this + 0x710) != 0 &&
          ((fVar6 = (float)CCharacter::getBravery((CCharacter *)this),
           DAT_00fa47fc - fVar6 <= fVar11 / fVar10 ||
           ((*(int *)(this + 0x710) != 0 &&
            (iVar3 = UTILITIES::randomIntegerBetweenVolatile(0,100), 0x31 < iVar3)))))))) {
        cVar2 = CCharacter::alive(param_1);
        if ((cVar2 != '\0') &&
           ((cVar2 = CCharacter::isEnemy((CCharacter *)this,param_1), cVar2 != '\0' &&
            (param_1[0x531] != (CCharacter)0x0)))) {
          iVar3 = UTILITIES::randomIntegerBetweenVolatile(0,100);
          if ((iVar3 < 10) &&
             (((*(CCharacter **)(this + 0x340) == (CCharacter *)0x0 ||
               (param_1 != *(CCharacter **)(this + 0x340))) && (*(int *)(this + 0x330) != 10)))) {
            CCharacter::setTarget((CCharacter *)this,(CCharacter *)0x0);
            (**(code **)(*(long *)this + 0x348))(this,2);
          }
          if ((*(int *)(this + 0x710) != 0) &&
             (((iVar3 = *(int *)(this + 0x330), iVar3 == 2 || (iVar3 == 0)) || (iVar3 == 1)))) {
            CCharacter::stopPathing((CCharacter *)this);
            (**(code **)(*(long *)this + 0x348))(this,4);
            CCharacter::setTarget((CCharacter *)this,param_1);
            if (*(CSoundBank **)(this + 0x298) != (CSoundBank *)0x0) {
              CSoundBank::playSample
                        (*(CSoundBank **)(this + 0x298),0xd,*(SceneNode **)(this + 0x58),0.0,0.0,
                         false);
            }
          }
        }
      }
      else {
        CCharacter::interrupt((CCharacter *)this,true);
        (**(code **)(*(long *)this + 0x348))(this,10);
        if ((*(long *)(this + 0x68) != 0) && (*(long *)(*(long *)(this + 0x68) + 0x18) != 0)) {
          uVar8 = CPositionableObject::getPosition((CPositionableObject *)param_1,true);
          fVar11 = fVar10;
          uVar9 = CPositionableObject::getPosition((CPositionableObject *)this,true);
          local_58 = (float)uVar9;
          local_68 = (float)uVar8;
          local_58 = local_58 - local_68;
          fStack_54 = (float)((ulong)uVar9 >> 0x20);
          fStack_64 = (float)((ulong)uVar8 >> 0x20);
          fVar11 = fVar11 - fVar10;
          fVar10 = SQRT(local_58 * local_58 + (fStack_54 - fStack_64) * (fStack_54 - fStack_64) +
                        fVar11 * fVar11);
          if (DAT_00fa87a0 < (double)fVar10) {
            fVar10 = DAT_00fa47fc / fVar10;
            local_58 = local_58 * fVar10;
            fVar11 = fVar11 * fVar10;
          }
          fVar10 = DAT_00fa86d0;
          fVar6 = (float)UTILITIES::randomBetweenVolatile(DAT_00fa86d4,DAT_00fa86d0);
          fVar7 = (float)CPositionableObject::getPosition((CPositionableObject *)this,true);
          pCVar5 = (CLevel *)0x0;
          if (*(long *)(this + 0x68) != 0) {
            pCVar5 = *(CLevel **)(*(long *)(this + 0x68) + 0x18);
          }
          CCharacter::setDestination
                    ((CCharacter *)this,pCVar5,fVar6 * local_58 + fVar7,fVar10 + fVar11 * fVar6);
        }
      }
      return;
    }
    return;
  }
  return;
}

/* address=008d59a0
   symbol=CMonster::fleeAI */

/* CMonster::fleeAI(float, CLevel&) */

void CMonster::fleeAI(float param_1,CLevel *param_2)

{
  char cVar1;
  int iVar2;
  CLevel *in_RSI;
  float fVar3;
  float fVar4;
  float fVar5;
  float in_XMM1_Da;

  CCharacter::setTarget((CCharacter *)param_2,(CCharacter *)0x0);
  param_2[0x321] = (CLevel)0x1;
  if (param_2[0x264] != (CLevel)0x0) {
    return;
  }
  iVar2 = UTILITIES::randomIntegerBetweenVolatile(0,100);
  if (iVar2 < 0x4b) {
    selectDefensiveSkill((CMonster *)param_2);
    if (*(long *)(param_2 + 0x398) != 0) {
      cVar1 = CCharacter::canCastCurrentSkill((CBaseUnit *)param_2,false,false);
      if (cVar1 != '\0') {
        CCharacter::castSkill((longlong)param_2);
        return;
      }
    }
  }
  iVar2 = UTILITIES::randomIntegerBetweenVolatile(0,100);
  if (iVar2 < 0x4b) {
    cVar1 = CCharacter::isPetNearDeath((CCharacter *)param_2);
    if (cVar1 == '\0') {
      cVar1 = CBaseUnit::hasEffect(param_2,0x4f);
      if (cVar1 == '\0') {
        (**(code **)(*(long *)param_2 + 0x348))(param_2,2);
      }
    }
  }
  if (*(long *)(param_2 + 0x640) != 0) {
    cVar1 = CBaseUnit::ISA((CBaseUnit *)param_2);
    if (cVar1 == '\0') {
      CPositionableObject::getPosition(*(CPositionableObject **)(param_2 + 0x640),false);
      fVar3 = DAT_00fd2b78 + in_XMM1_Da;
      CPositionableObject::getPosition(*(CPositionableObject **)(param_2 + 0x640),true);
      fVar3 = (float)UTILITIES::randomBetweenVolatile(in_XMM1_Da - DAT_00fd2b78,fVar3);
      fVar4 = (float)CPositionableObject::getPosition
                               (*(CPositionableObject **)(param_2 + 0x640),false);
      fVar4 = DAT_00fd2b78 + fVar4;
      fVar5 = (float)CPositionableObject::getPosition
                               (*(CPositionableObject **)(param_2 + 0x640),true);
      fVar4 = (float)UTILITIES::randomBetweenVolatile(fVar5 - DAT_00fd2b78,fVar4);
      goto LAB_008d5a69;
    }
  }
  fVar4 = DAT_00fa86d0;
  fVar3 = (float)UTILITIES::randomBetweenVolatile
                           (*(float *)(param_2 + 0x8c) - DAT_00fa86d0,
                            *(float *)(param_2 + 0x8c) + DAT_00fa86d0);
  fVar4 = (float)UTILITIES::randomBetweenVolatile
                           (*(float *)(param_2 + 0x84) - fVar4,*(float *)(param_2 + 0x84) + fVar4);
LAB_008d5a69:
  CCharacter::setDestination((CCharacter *)param_2,in_RSI,fVar4,fVar3);
  return;
}

/* address=008d5c40
   symbol=CMonster::setPathToFollow */

/* CMonster::setPathToFollow(CPathController*) */

void __thiscall CMonster::setPathToFollow(CMonster *this,CPathController *param_1)

{
  CRunicCore *this_00;
  long lVar1;
  undefined4 uVar2;

  if (*(long *)(this + 0x268) != 0) {
    *(undefined4 *)(*(long *)(this + 0x268) + 0x6c) = *(undefined4 *)(this + 0x768);
  }
  this_00 = *(CRunicCore **)(this + 0x750);
  if (param_1 != (CPathController *)this_00) {
    if (this_00 != (CRunicCore *)0x0) {
      CRunicCore::removeSafePointer(this_00,(TSafePointer *)(this + 0x750),*(uint *)(this + 0x758));
    }
    *(undefined8 *)(this + 0x750) = 0;
    if (param_1 != (CPathController *)0x0) {
      uVar2 = CRunicCore::addSafePointer((CRunicCore *)param_1,(TSafePointer *)(this + 0x750));
      *(undefined4 *)(this + 0x758) = uVar2;
    }
    *(CPathController **)(this + 0x750) = param_1;
  }
  if ((param_1 != (CPathController *)0x0) && (lVar1 = *(long *)(this + 0x268), lVar1 != 0)) {
    *(undefined4 *)(this + 0x768) = *(undefined4 *)(lVar1 + 0x6c);
    *(undefined4 *)(lVar1 + 0x6c) = 800;
  }
  *(undefined4 *)(this + 0x278) = 0x41200000;
  *(undefined4 *)(this + 0x1e8) = 0xbf800000;
  return;
}

/* address=008d5c50
   symbol=CMonster::approachAI */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CMonster::approachAI(float, CLevel&) */

void __thiscall CMonster::approachAI(CMonster *this,float param_1,CLevel *param_2)

{
  CBaseUnit *pCVar1;
  char cVar2;
  CQuestManager *this_00;
  long lVar3;
  code *UNRECOVERED_JUMPTABLE;
  undefined8 uVar4;
  CGameClient *this_01;
  float fVar5;
  float fVar6;
  float extraout_XMM0_Da;
  float extraout_XMM0_Da_00;
  float fVar7;
  float in_XMM1_Da;

  if (*(long *)(this + 0x340) == 0) {
    if (*(long *)(this + 0x350) == 0) {
      uVar4 = 0;
      UNRECOVERED_JUMPTABLE = *(code **)(*(long *)this + 0x348);
      goto LAB_00825679;
    }
    fVar5 = (float)CPositionableObject::getPosition((CPositionableObject *)this,true);
    fVar7 = in_XMM1_Da;
    fVar6 = (float)CPositionableObject::getPosition(*(CPositionableObject **)(this + 0x350),true);
    fVar6 = fVar6 - fVar5;
    fVar7 = fVar7 - in_XMM1_Da;
  }
  else {
    fVar5 = (float)CPositionableObject::getPosition((CPositionableObject *)this,true);
    fVar7 = in_XMM1_Da;
    fVar6 = (float)CPositionableObject::getPosition(*(CPositionableObject **)(this + 0x340),true);
    fVar6 = fVar6 - fVar5;
    fVar7 = fVar7 - in_XMM1_Da;
  }
  fVar7 = SQRT(fVar6 * fVar6 + DAT_00fa47f8 + fVar7 * fVar7);
  this[0x321] = (CMonster)(*(float *)(this + 0x364) <= fVar7);
  if (DAT_00fa4824 < fVar7) {
    if (this[0x264] != (CMonster)0x0) {
      return;
    }
    if (fVar7 <= _DAT_00fce4c8) goto LAB_0082558c;
LAB_00825660:
    param_1 = (float)CCharacter::setTarget((CCharacter *)this,(CCharacter *)0x0);
    uVar4 = 2;
    UNRECOVERED_JUMPTABLE = *(code **)(*(long *)this + 0x348);
LAB_00825679:
                    /* WARNING: Could not recover jumptable at 0x00825682. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*UNRECOVERED_JUMPTABLE)(param_1,this,uVar4);
    return;
  }
  if (this[0x264] != (CMonster)0x0) {
    *(undefined4 *)(this + 0x278) = 0x41200000;
  }
LAB_0082558c:
  pCVar1 = *(CBaseUnit **)(this + 0x340);
  this[0x264] = (CMonster)0x0;
  *(undefined4 *)(this + 0x21c) = *(undefined4 *)(this + 0x84);
  *(undefined4 *)(this + 0x220) = *(undefined4 *)(this + 0x88);
  *(undefined4 *)(this + 0x224) = *(undefined4 *)(this + 0x8c);
  this_00 = (CQuestManager *)CQuestManager::getSingleton();
  lVar3 = CQuestManager::getQuestForNPC(this_00,pCVar1);
  if (lVar3 == 0) {
    cVar2 = CBaseUnit::ISA(*(CBaseUnit **)(this + 0x340),0x82);
    if (cVar2 != '\0') {
      lVar3 = *(long *)this;
      uVar4 = 0x15;
      goto LAB_008255df;
    }
    cVar2 = CBaseUnit::ISA(*(CBaseUnit **)(this + 0x340),0xaf);
    if (cVar2 != '\0') {
      lVar3 = *(long *)this;
      uVar4 = 0x1b;
      goto LAB_008255df;
    }
    cVar2 = CBaseUnit::ISA(*(CBaseUnit **)(this + 0x340),0x84);
    if (cVar2 != '\0') {
      lVar3 = *(long *)this;
      uVar4 = 0x19;
      goto LAB_008255df;
    }
    cVar2 = CBaseUnit::ISA(*(CBaseUnit **)(this + 0x340),0x85);
    if (cVar2 != '\0') {
      lVar3 = *(long *)this;
      uVar4 = 0x1a;
      goto LAB_008255df;
    }
    cVar2 = CBaseUnit::ISA(*(CBaseUnit **)(this + 0x340),0x86);
    if (cVar2 != '\0') {
      lVar3 = *(long *)this;
      uVar4 = 0x11;
      goto LAB_008255df;
    }
    cVar2 = CBaseUnit::ISA(*(CBaseUnit **)(this + 0x340),0x29);
    if (cVar2 != '\0') {
      lVar3 = *(long *)this;
      uVar4 = 0x13;
      goto LAB_008255df;
    }
    cVar2 = CBaseUnit::ISA(*(CBaseUnit **)(this + 0x340),0x80);
    if (cVar2 != '\0') {
      uVar4 = 0x24;
      UNRECOVERED_JUMPTABLE = *(code **)(*(long *)this + 0x348);
      param_1 = extraout_XMM0_Da;
      goto LAB_00825679;
    }
    cVar2 = CBaseUnit::ISA(*(CBaseUnit **)(this + 0x340),0xaa);
    if (cVar2 != '\0') {
      this_01 = (CGameClient *)0x0;
      if (*(int *)(*(long *)(this + 0x68) + 0x30) != 0) {
        this_01 = (CGameClient *)**(undefined8 **)(*(long *)(this + 0x68) + 0x28);
      }
      cVar2 = CGameClient::getPlayerIsCheat(this_01);
      if (cVar2 != '\0') {
        return;
      }
      uVar4 = 0x25;
      UNRECOVERED_JUMPTABLE = *(code **)(*(long *)this + 0x348);
      param_1 = extraout_XMM0_Da_00;
      goto LAB_00825679;
    }
    cVar2 = CBaseUnit::ISA(*(CBaseUnit **)(this + 0x340));
    if (cVar2 == '\0') {
      if (this[0x264] != (CMonster)0x0) {
        return;
      }
      goto LAB_00825660;
    }
  }
  lVar3 = *(long *)this;
  uVar4 = 0x1e;
LAB_008255df:
  (**(code **)(lVar3 + 0x348))(this,uVar4);
  CCharacter::setTarget(*(CCharacter **)(this + 0x340),(CCharacter *)this);
  lVar3 = *(long *)(this + 0x340);
  if (*(char *)(lVar3 + 0x264) != '\0') {
    *(undefined4 *)(lVar3 + 0x278) = 0x41200000;
  }
  *(undefined1 *)(lVar3 + 0x264) = 0;
  *(undefined4 *)(lVar3 + 0x21c) = *(undefined4 *)(lVar3 + 0x84);
  *(undefined4 *)(lVar3 + 0x220) = *(undefined4 *)(lVar3 + 0x88);
  *(undefined4 *)(lVar3 + 0x224) = *(undefined4 *)(lVar3 + 0x8c);
  return;
}

/* address=008d5c60
   symbol=CMonster::canAttackWithCurrentWeapon */

/* CMonster::canAttackWithCurrentWeapon() */

undefined8 __thiscall CMonster::canAttackWithCurrentWeapon(CMonster *this)

{
  undefined8 uVar1;

  if (DAT_00fa47f8 < *(float *)(this + 0x7e8)) {
    return 0;
  }
  uVar1 = CCharacter::canAttackWithCurrentWeapon((CCharacter *)this);
  return uVar1;
}

/* address=008d5c80
   symbol=CMonster::CMonster */

/* CMonster::CMonster(CResourceManager*, int) */

void __thiscall CMonster::CMonster(CMonster *this,CResourceManager *param_1,int param_2)

{
  CCharacter::CCharacter((CCharacter *)this,param_1);
  *(undefined ***)this = &PTR__CMonster_00fd2690;
  *(undefined ***)(this + 0x1d8) = &PTR__CMonster_00fd2ac0;
  *(undefined ***)(this + 0x1e0) = &PTR__CMonster_00fd2b10;
  *(undefined4 **)(this + 0x778) = &DAT_01424558;
                    /* try { // try from 008d5cc1 to 008d5cc5 has its CatchHandler @ 008d5cf9 */
  CRandomizer::CRandomizer((CRandomizer *)(this + 0x780),0);
  *(undefined4 *)(this + 0x7e8) = 0;
  *(undefined4 *)(this + 0x7ec) = 0;
  this[0x7f0] = (CMonster)0x0;
  if (param_2 < *(int *)(this + 0x100)) {
    param_2 = *(int *)(this + 0x100);
  }
  *(int *)(this + 0x100) = param_2;
  return;
}

/* address=008df360
   symbol=CMonster::_GLOBAL__I_CMonster */

/* CMonster::CMonster(CResourceManager*, int) */

void CMonster::_GLOBAL__I_CMonster(void)

{
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
  std::wstring::wstring((wstring_conflict *)OGRE_UTILITIES::gPRIMITIVE_NAMES,L"SPHERE",&aStack_38b);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 8),L"BOX",&aStack_38a);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x10),L"PLANE",&aStack_389);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x18),L"CYLINDER",&aStack_388);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x20),L"CONE",&aStack_387);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x28),L"ARROW",&aStack_386);
  __cxa_atexit(::__tcf_0,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gKEYFRAME_TYPES,L"HIT",&aStack_385);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 8),L"BLENDIN",&aStack_384);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x10),L"BLENDOUT",&aStack_383);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x18),L"PLAYSOUND",&aStack_382);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x20),L"SPAWNPARTICLE",&aStack_381)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x28),L"SPAWNPARTICLE_STOP_ON_DEATH",
             &aStack_380);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x30),L"FOOTSTEP",&aStack_37f);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x38),L"SHOWWEAPONTRAIL",&aStack_37e);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x40),L"HIDEWEAPONTRAIL",&aStack_37d);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x48),L"ATTACKSOUND",&aStack_37c);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x50),L"ENABLECOLLISION",&aStack_37b);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x58),L"DISABLECOLLISION",&aStack_37a);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x60),L"REMOVEPARTICLES",&aStack_379);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x68),L"REMOVEANIMATIONPARTICLES",&aStack_378)
  ;
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x70),L"CAMERASHAKE",&aStack_377);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x78),L"ATTACKEND",&aStack_376);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x80),L"UNTARGETABLE",&aStack_375);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x88),L"TARGETABLE",&aStack_374);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x90),L"DAMPVELOCITY",&aStack_373);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x98),L"UNDAMPVELOCITY",&aStack_372);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xa0),L"SHOWWEAPONS",&aStack_371);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xa8),L"HIDEWEAPONS",&aStack_370);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xb0),L"HIDEMESH",&aStack_36f);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xb8),L"SHOWMESH",&aStack_36e);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xc0),L"FADEOUTMESH",&aStack_36d);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 200),L"FADEINMESH",&aStack_36c);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0xd0),L"CAMERASHAKE_NO_FALLOFF",&aStack_36b);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0xd8),L"PLAYSOUND_NO_FALLOFF",&aStack_36a);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xe0),L"HITTWO",&aStack_369);
  __cxa_atexit(::__tcf_1,0,&__dso_handle);
  ParticleUniverse::HALFSCALE._4_4_ = DAT_0142463c * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._0_4_ = Ogre::Vector3::UNIT_SCALE * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._8_4_ = DAT_00fa4810 * DAT_01424640;
  std::string::string((string *)&ParticleUniverse::ALIAS,"1",&aStack_368);
  __cxa_atexit(std::string::~string,&ParticleUniverse::ALIAS,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::SYSTEM,"2",&aStack_367);
  __cxa_atexit(std::string::~string,&ParticleUniverse::SYSTEM,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::TECHNIQUE,"3",&aStack_366);
  __cxa_atexit(std::string::~string,&ParticleUniverse::TECHNIQUE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::RENDERER,"4",&aStack_365);
  __cxa_atexit(std::string::~string,&ParticleUniverse::RENDERER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EMITTER,"5",&aStack_364);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EMITTER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::AFFECTOR,"6",&aStack_363);
  __cxa_atexit(std::string::~string,&ParticleUniverse::AFFECTOR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::OBSERVER,"7",&aStack_362);
  __cxa_atexit(std::string::~string,&ParticleUniverse::OBSERVER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::HANDLER,"8",&aStack_361);
  __cxa_atexit(std::string::~string,&ParticleUniverse::HANDLER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::BEHAVIOUR,"9",&aStack_360);
  __cxa_atexit(std::string::~string,&ParticleUniverse::BEHAVIOUR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EXTERN,"10",&aStack_35f);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EXTERN,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DYNAMIC_ATTRIBUTE,"11",&aStack_35e);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DYNAMIC_ATTRIBUTE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DEPENDENCY,"12",&aStack_35d);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DEPENDENCY,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_TYPE_NAMES,L"",&aStack_35c);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 8),L"FIND",&aStack_35b);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x10),L"KILL NUM",&aStack_35a);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x18),L"KILL BOSS",&aStack_359);
  __cxa_atexit(::__tcf_2,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_DIALOG_TYPE_NAMES,L"ERROR",&aStack_358);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 8),L"INTRO",&aStack_357);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x10),L"RETURN",&aStack_356);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x18),L"COMPLETE",&aStack_355);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x20),L"PASSIVE",&aStack_354);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x28),L"DETAILS",&aStack_353);
  __cxa_atexit(::__tcf_3,0,&__dso_handle);
  std::string::string((string *)::KLayoutFunctionNames,"GUIEXITGAME",&aStack_352);
  std::string::string((string *)(::KLayoutFunctionNames + 8),"GUIEXITAPPLICATION",&aStack_351);
  std::string::string((string *)(::KLayoutFunctionNames + 0x10),"GUINEWGAME",&aStack_350);
  std::string::string((string *)(::KLayoutFunctionNames + 0x18),"GUICONTINUEGAME",&aStack_34f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x20),"GUINEWGAMEMENU",&aStack_34e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x28),"GUICONTINUEGAMEMENU",&aStack_34d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x30),"GUICLOSEMENU",&aStack_34c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x38),"GUIBACK",&aStack_34b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x40),"GUIDECLINE",&aStack_34a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x48),"GUIACCEPT",&aStack_349);
  std::string::string((string *)(::KLayoutFunctionNames + 0x50),"GUIOK",&aStack_348);
  std::string::string((string *)(::KLayoutFunctionNames + 0x58),"GUIPAUSE",&aStack_347);
  std::string::string((string *)(::KLayoutFunctionNames + 0x60),"GUISCROLLUP",&aStack_346);
  std::string::string((string *)(::KLayoutFunctionNames + 0x68),"GUISCROLLDOWN",&aStack_345);
  std::string::string((string *)(::KLayoutFunctionNames + 0x70),"GUISELECT1",&aStack_344);
  std::string::string((string *)(::KLayoutFunctionNames + 0x78),"GUISELECT2",&aStack_343);
  std::string::string((string *)(::KLayoutFunctionNames + 0x80),"GUISELECT3",&aStack_342);
  std::string::string((string *)(::KLayoutFunctionNames + 0x88),"GUISELECT4",&aStack_341);
  std::string::string((string *)(::KLayoutFunctionNames + 0x90),"GUISELECT5",&aStack_340);
  std::string::string((string *)(::KLayoutFunctionNames + 0x98),"GUISELECT6",&aStack_33f);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa0),"GUISELECT7",&aStack_33e);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa8),"GUISELECT8",&aStack_33d);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb0),"GUISELECT9",&aStack_33c);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb8),"GUISELECT10",&aStack_33b);
  std::string::string((string *)(::KLayoutFunctionNames + 0xc0),"GUISELECT11",&aStack_33a);
  std::string::string((string *)(::KLayoutFunctionNames + 200),"GUISELECT12",&aStack_339);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd0),"GUISELECT13",&aStack_338);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd8),"GUISELECT14",&aStack_337);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe0),"GUISELECT15",&aStack_336);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe8),"GUISELECT16",&aStack_335);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf0),"GUISELECT17",&aStack_334);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf8),"GUISELECT18",&aStack_333);
  std::string::string((string *)(::KLayoutFunctionNames + 0x100),"GUISELECT19",&aStack_332);
  std::string::string((string *)(::KLayoutFunctionNames + 0x108),"GUISELECT20",&aStack_331);
  std::string::string((string *)(::KLayoutFunctionNames + 0x110),"GUISELECT21",&aStack_330);
  std::string::string((string *)(::KLayoutFunctionNames + 0x118),"GUISELECT22",&aStack_32f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x120),"GUISELECT23",&aStack_32e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x128),"GUISELECT24",&aStack_32d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x130),"GUISELECT25",&aStack_32c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x138),"GUISELECT26",&aStack_32b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x140),"GUISELECT27",&aStack_32a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x148),"GUISELECT28",&aStack_329);
  std::string::string((string *)(::KLayoutFunctionNames + 0x150),"GUISELECT29",&aStack_328);
  std::string::string((string *)(::KLayoutFunctionNames + 0x158),"GUISELECT30",&aStack_327);
  std::string::string((string *)(::KLayoutFunctionNames + 0x160),"GUISELECT31",&aStack_326);
  std::string::string((string *)(::KLayoutFunctionNames + 0x168),"GUISELECT32",&aStack_325);
  std::string::string((string *)(::KLayoutFunctionNames + 0x170),"GUISELECT33",&aStack_324);
  std::string::string((string *)(::KLayoutFunctionNames + 0x178),"GUISELECT34",&aStack_323);
  std::string::string((string *)(::KLayoutFunctionNames + 0x180),"GUISELECT35",&aStack_322);
  std::string::string((string *)(::KLayoutFunctionNames + 0x188),"GUISELECT36",&aStack_321);
  std::string::string((string *)(::KLayoutFunctionNames + 400),"GUISELECT37",&aStack_320);
  std::string::string((string *)(::KLayoutFunctionNames + 0x198),"GUISELECT38",&aStack_31f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a0),"GUISELECT39",&aStack_31e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a8),"GUISELECT40",&aStack_31d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b0),"GUISELECT41",&aStack_31c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b8),"GUISELECT42",&aStack_31b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c0),"GUISELECT43",&aStack_31a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c8),"GUISELECT44",&aStack_319);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d0),"GUISELECT45",&aStack_318);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d8),"GUISELECT46",&aStack_317);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e0),"GUISELECT47",&aStack_316);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e8),"GUISELECT48",&aStack_315);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f0),"GUISELECT49",&aStack_314);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f8),"GUISELECT50",&aStack_313);
  std::string::string((string *)(::KLayoutFunctionNames + 0x200),"GUISELECTA",&aStack_312);
  std::string::string((string *)(::KLayoutFunctionNames + 0x208),"GUISELECTB",&aStack_311);
  std::string::string((string *)(::KLayoutFunctionNames + 0x210),"GUISELECTC",&aStack_310);
  std::string::string((string *)(::KLayoutFunctionNames + 0x218),"GUISELECTD",&aStack_30f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x220),"GUIFEEDPET",&aStack_30e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x228),"GUIPETPASSIVE",&aStack_30d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x230),"GUIPETAGGRESSIVE",&aStack_30c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x238),"GUIPETDEFENSIVE",&aStack_30b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x240),"GUITOGGLEINVENTORY",&aStack_30a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x248),"GUITOGGLEQUESTS",&aStack_309);
  std::string::string((string *)(::KLayoutFunctionNames + 0x250),"GUITOGGLESTATS",&aStack_308);
  std::string::string((string *)(::KLayoutFunctionNames + 600),"GUITOGGLESKILLS",&aStack_307);
  std::string::string((string *)(::KLayoutFunctionNames + 0x260),"GUITOGGLEPERKS",&aStack_306);
  std::string::string((string *)(::KLayoutFunctionNames + 0x268),"GUITOGGLEJOURNAL",&aStack_305);
  std::string::string((string *)(::KLayoutFunctionNames + 0x270),"GUITOGGLEPET",&aStack_304);
  std::string::string((string *)(::KLayoutFunctionNames + 0x278),"GUITOGGLEAUTOMAP",&aStack_303);
  std::string::string((string *)(::KLayoutFunctionNames + 0x280),"GUITOGGLEOPTIONS",&aStack_302);
  std::string::string((string *)(::KLayoutFunctionNames + 0x288),"GUITOGGLEITEMNAMES",&aStack_301);
  std::string::string((string *)(::KLayoutFunctionNames + 0x290),"GUIAUTOMAPZOOMIN",&aStack_300);
  std::string::string((string *)(::KLayoutFunctionNames + 0x298),"GUIAUTOMAPZOOMOUT",&aStack_2ff);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a0),"GUILEVELUP",&aStack_2fe);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a8),"GUISTATSUP",&aStack_2fd);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b0),"GUISKILLUP",&aStack_2fc);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b8),"GUIPET1",&aStack_2fb);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c0),"GUIPET2",&aStack_2fa);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c8),"GUIPET3",&aStack_2f9);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d0),"GUIDELETE1",&aStack_2f8);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d8),"GUIDELETE2",&aStack_2f7);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e0),"GUIDELETE3",&aStack_2f6);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e8),"GUIDELETE4",&aStack_2f5);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f0),"GUISETTINGSMENU",&aStack_2f4);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f8),"GUIPETSELL",&aStack_2f3);
  std::string::string((string *)(::KLayoutFunctionNames + 0x300),"NONE",&aStack_2f2);
  __cxa_atexit(::__tcf_4,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSOUNDBANK_STRINGS,L"STEP_SOUND",&aStack_2f1);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 8),L"STRIKE_SOUND",&aStack_2f0);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x10),L"PHYSICALHIT_SOUND",&aStack_2ef);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x18),L"ICEHIT_SOUND",&aStack_2ee);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x20),L"FIREHIT_SOUND",&aStack_2ed);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x28),L"ELECTRICHIT_SOUND",&aStack_2ec);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x30),L"POISONHIT_SOUND",&aStack_2eb);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x38),L"SHIELDBLOCK",&aStack_2ea);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x40),L"BLOCK",&aStack_2e9);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x48),L"CRITICAL_SOUND",&aStack_2e8);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x50),L"ATTACK_SOUND",&aStack_2e7);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x58),L"IDLE_SOUND",&aStack_2e6)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x60),L"DEATH_SOUND",&aStack_2e5);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x68),L"ROAR_SOUND",&aStack_2e4)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x70),L"FLEE_SOUND",&aStack_2e3)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x78),L"MISS_SOUND",&aStack_2e2)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x80),L"FALL_SOUND",&aStack_2e1)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x88),L"LAND_SOUND",&aStack_2e0)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x90),L"TAKE_SOUND",&aStack_2df)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x98),L"SPAWN_SOUND",&aStack_2de);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa0),L"USE_SOUND",&aStack_2dd);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa8),L"EQUIP_SOUND",&aStack_2dc);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb0),L"OPENMENU_SOUND",&aStack_2db);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb8),L"BUY_SOUND",&aStack_2da);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xc0),L"ERROR_SOUND",&aStack_2d9);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 200),L"LEVELUP_SOUND",&aStack_2d8);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd0),L"EFFORT_SOUND",&aStack_2d7);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd8),L"SPENDPOINT_SOUND",&aStack_2d6);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe0),L"PORTALENTER_SOUND",&aStack_2d5);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe8),L"POERTALEXIT_SOUND",&aStack_2d4);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf0),L"SKILLASSIGN_SOUND",&aStack_2d3);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf8),L"QUESTRECEIVED_SOUND",&aStack_2d2);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x100),L"QUESTCOMPLETED_SOUND",&aStack_2d1)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x108),L"LOWMANA_SOUND",&aStack_2d0);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x110),L"MISSILEREFLECT_SOUND",&aStack_2cf)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x118),L"BADEFFECT_SOUND",&aStack_2ce);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x120),L"GOODEFFECT_SOUND",&aStack_2cd);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x128),L"NPCDIALOG_SOUND",&aStack_2cc);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x130),L"NPCGREET",&aStack_2cb);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x138),L"NPCBYE",&aStack_2ca);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x140),L"NPCPURCHASE",&aStack_2c9);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x148),L"NPCSELL",&aStack_2c8);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x150),L"VOICEPETINVENTORYFULL_SOUND",
             &aStack_2c7);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x158),L"VOICEPETDEPARTED_SOUND",
             &aStack_2c6);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x160),L"VOICEPETRETURNED_SOUND",
             &aStack_2c5);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x168),L"VOICEPETFLED_SOUND",&aStack_2c4);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x170),L"VOICEPETLEVELUP_SOUND",&aStack_2c3
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x178),L"VOICEINVENTORYFULL_SOUND",
             &aStack_2c2);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x180),L"VOICEINSUFFICIENTGOLD_SOUND",
             &aStack_2c1);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x188),L"VOICEIMPOSSIBLE_SOUND",&aStack_2c0
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 400),L"VOICECANTCAST_SOUND",&aStack_2bf);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x198),L"VOICECANTCASTHERE_SOUND",
             &aStack_2be);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a0),L"VOICEHEALTHLOW_SOUND",&aStack_2bd)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a8),L"VOICEMANALOW_SOUND",&aStack_2bc);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b0),L"VOICETRAPSPRUNG_SOUND",&aStack_2bb
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b8),L"VOICEREFRESHED_SOUND",&aStack_2ba)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c0),L"VOICEPOWERFUL_SOUND",&aStack_2b9);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c8),L"VOICEHEALTHY_SOUND",&aStack_2b8);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d0),L"VOICEILL_SOUND",&aStack_2b7);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d8),L"VOICEPOISONED_SOUND",&aStack_2b6);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e0),L"VOICELEVELUP_SOUND",&aStack_2b5);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e8),L"VOICEFAMEUP_SOUND",&aStack_2b4);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f0),L"VOICESKILLUP_SOUND",&aStack_2b3);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f8),L"VOICEFORTUNEGOOD_SOUND",
             &aStack_2b2);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x200),L"VOICEFORTUNEBAD_SOUND",&aStack_2b1
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x208),L"VOICESPELLLEARNED_SOUND",
             &aStack_2b0);
  ::KSOUNDBANK_STRINGS._528_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_5,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KALIGNMENT_STRINGS,L"NEUTRAL",&aStack_2af);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 8),L"GOOD",&aStack_2ae);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x10),L"EVIL",&aStack_2ad);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x18),L"ALL",&aStack_2ac);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x20),L"BERSERK",&aStack_2ab);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x28),L"EVILBERSERK",&aStack_2aa);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x30),L"GOODBERSERK",&aStack_2a9);
  __cxa_atexit(::__tcf_6,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KAITYPE_STRINGS,L"NORMAL",&aStack_2a8);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 8),L"RANGEDDEFENDER",&aStack_2a7);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x10),L"DEFENDER",&aStack_2a6);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x18),L"RANGEDCASTER",&aStack_2a5);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x20),L"CIRCLER",&aStack_2a4);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x28),L"RESURRECTER",&aStack_2a3);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x30),L"DUMMY",&aStack_2a2);
  __cxa_atexit(::__tcf_7,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gDAMAGE_TYPES,L"Physical",&aStack_2a1);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 8),L"Magical",&aStack_2a0);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x10),L"Fire",&aStack_29f);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x18),L"Ice",&aStack_29e);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x20),L"Electric",&aStack_29d);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x28),L"Poison",&aStack_29c);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x30),L"All",&aStack_29b);
  __cxa_atexit(::__tcf_8,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::gTARGET_TYPES,L"USER",&aStack_29a);
  std::wstring::wstring((wstring_conflict *)&DAT_01488e08,L"ITEM",&aStack_299);
  __cxa_atexit(::__tcf_9,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSFXTypeName,L"STATIONARYTARGET",&aStack_298);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 8),L"STATIONARYOWNER",&aStack_297);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x10),L"STATIONARY",&aStack_296);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x18),L"STATIONARYPORTAL",&aStack_295)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x20),L"BEAM",&aStack_294);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x28),L"FOLLOWOWNER",&aStack_293);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x30),L"FOLLOWTARGET",&aStack_292);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x38),L"PROJECTILELOCATION",&aStack_291);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x40),L"PROJECTILECHARACTER",&aStack_290);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x48),L"PROJECTILELOCATIONERRATIC",&aStack_28f);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x50),L"PROJECTILECHARACTERERRATIC",&aStack_28e);
  __cxa_atexit(::__tcf_10,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KCharacterNames,L"NA",&aStack_28d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 8),L"NA",&aStack_28c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x10),L"NA",&aStack_28b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x18),L"NA",&aStack_28a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x20),L"NA",&aStack_289);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x28),L"NA",&aStack_288);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x30),L"NA",&aStack_287);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x38),L"NA",&aStack_286);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x40),L"Bksp",&aStack_285);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x48),L"Tab",&aStack_284);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x50),L"NA",&aStack_283);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x58),L"NA",&aStack_282);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x60),L"Ctr",&aStack_281);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x68),L"Ret",&aStack_280);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x70),L"NA",&aStack_27f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x78),L"NA",&aStack_27e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x80),L"Shift",&aStack_27d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x88),L"Ctrl",&aStack_27c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x90),L"Alt",&aStack_27b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x98),L"Tab",&aStack_27a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa0),L"NA",&aStack_279);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa8),L"NA",&aStack_278);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb0),L"NA",&aStack_277);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb8),L"NA",&aStack_276);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xc0),L"NA",&aStack_275);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 200),L"NA",&aStack_274);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd0),L"NA",&aStack_273);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd8),L"NA",&aStack_272);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe0),L"NA",&aStack_271);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe8),L"NA",&aStack_270);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf0),L"NA",&aStack_26f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf8),L"NA",&aStack_26e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x100),L"space",&aStack_26d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x108),L"pgup",&aStack_26c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x110),L"pgdn",&aStack_26b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x118),L"end",&aStack_26a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x120),L"home",&aStack_269);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x128),L"left arrow",&aStack_268);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x130),L"up arrow",&aStack_267);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x138),L"right arrow",&aStack_266);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x140),L"down arrow",&aStack_265);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x148),L")",&aStack_264);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x150),L"*",&aStack_263);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x158),L"+",&aStack_262);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x160),L",",&aStack_261);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x168),L"ins",&aStack_260);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x170),L"del",&aStack_25f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x178),L"/",&aStack_25e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x180),L"0",&aStack_25d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x188),L"1",&aStack_25c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 400),L"2",&aStack_25b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x198),L"3",&aStack_25a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a0),L"4",&aStack_259);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a8),L"5",&aStack_258);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b0),L"6",&aStack_257);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b8),L"7",&aStack_256);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c0),L"8",&aStack_255);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c8),L"9",&aStack_254);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d0),L":",&aStack_253);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d8),L";",&aStack_252);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e0),L"<",&aStack_251);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e8),L"=",&aStack_250);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f0),L">",&aStack_24f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f8),L"?",&aStack_24e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x200),L"@",&aStack_24d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x208),L"a",&aStack_24c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x210),L"b",&aStack_24b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x218),L"c",&aStack_24a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x220),L"d",&aStack_249);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x228),L"e",&aStack_248);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x230),L"NA",&aStack_247);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x238),L"g",&aStack_246);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x240),L"h",&aStack_245);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x248),L"i",&aStack_244);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x250),L"j",&aStack_243);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 600),L"k",&aStack_242);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x260),L"l",&aStack_241);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x268),L"m",&aStack_240);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x270),L"n",&aStack_23f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x278),L"o",&aStack_23e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x280),L"p",&aStack_23d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x288),L"NA",&aStack_23c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x290),L"r",&aStack_23b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x298),L"s",&aStack_23a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a0),L"t",&aStack_239);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a8),L"u",&aStack_238);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b0),L"v",&aStack_237);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b8),L"w",&aStack_236);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c0),L"x",&aStack_235);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c8),L"y",&aStack_234);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d0),L"z",&aStack_233);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d8),L"[",&aStack_232);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e0),L"\\",&aStack_231);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e8),L"]",&aStack_230);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f0),L"^",&aStack_22f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f8),L"_",&aStack_22e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x300),L"NUM 0",&aStack_22d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x308),L"NUM 1",&aStack_22c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x310),L"NUM 2",&aStack_22b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x318),L"NUM 3",&aStack_22a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 800),L"NUM 4",&aStack_229);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x328),L"NUM 5",&aStack_228);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x330),L"NUM 6",&aStack_227);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x338),L"NUM 7",&aStack_226);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x340),L"NUM 8",&aStack_225);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x348),L"NUM 9",&aStack_224);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x350),L"*",&aStack_223);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x358),L"+",&aStack_222);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x360),L"NA",&aStack_221);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x368),L"-",&aStack_220);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x370),L"NA",&aStack_21f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x378),L"F1",&aStack_21e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x380),L"F2",&aStack_21d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x388),L"F3",&aStack_21c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x390),L"F4",&aStack_21b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x398),L"F5",&aStack_21a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a0),L"F6",&aStack_219);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a8),L"F7",&aStack_218);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b0),L"F8",&aStack_217);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b8),L"F9",&aStack_216);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c0),L"F10",&aStack_215);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c8),L"F11",&aStack_214);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d0),L"F12",&aStack_213);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d8),L"{",&aStack_212);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3e0),L"|",&aStack_211);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 1000),L"}",&aStack_210);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f0),L"~",&aStack_20f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f8),L";",&aStack_20e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x400),L"=",&aStack_20d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x408),L".",&aStack_20c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x410),L"-",&aStack_20b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x418),L",",&aStack_20a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x420),L"/",&aStack_209);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x428),L"`",&aStack_208);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x430),L"[",&aStack_207);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x438),L"\\",&aStack_206);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x440),L"]",&aStack_205);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x448),L"\'",&aStack_204);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x450),L"NA",&aStack_203);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x458),L"NA",&aStack_202);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x460),L"NA",&aStack_201);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x468),L"NA",&aStack_200);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x470),L"NA",&aStack_1ff);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x478),L"NA",&aStack_1fe);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x480),L"NA",&aStack_1fd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x488),L"NA",&aStack_1fc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x490),L"NA",&aStack_1fb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x498),L"NA",&aStack_1fa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a0),L"NA",&aStack_1f9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a8),L"NA",&aStack_1f8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b0),L"NA",&aStack_1f7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b8),L"NA",&aStack_1f6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c0),L"NA",&aStack_1f5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c8),L"NA",&aStack_1f4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d0),L"NA",&aStack_1f3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d8),L"NA",&aStack_1f2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e0),L"NA",&aStack_1f1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e8),L"NA",&aStack_1f0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f0),L"NA",&aStack_1ef);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f8),L"NA",&aStack_1ee);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x500),L"NA",&aStack_1ed);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x508),L"NA",&aStack_1ec);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x510),L"NA",&aStack_1eb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x518),L"NA",&aStack_1ea);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x520),L"NA",&aStack_1e9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x528),L"NA",&aStack_1e8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x530),L"NA",&aStack_1e7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x538),L"NA",&aStack_1e6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x540),L"NA",&aStack_1e5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x548),L"NA",&aStack_1e4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x550),L"NA",&aStack_1e3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x558),L"NA",&aStack_1e2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x560),L"NA",&aStack_1e1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x568),L"NA",&aStack_1e0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x570),L"NA",&aStack_1df);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x578),L"NA",&aStack_1de);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x580),L"NA",&aStack_1dd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x588),L"NA",&aStack_1dc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x590),L"NA",&aStack_1db);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x598),L"NA",&aStack_1da);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a0),L"NA",&aStack_1d9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a8),L"NA",&aStack_1d8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b0),L"NA",&aStack_1d7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b8),L"NA",&aStack_1d6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c0),L"NA",&aStack_1d5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c8),L"NA",&aStack_1d4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d0),L";",&aStack_1d3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d8),L"=",&aStack_1d2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e0),L",",&aStack_1d1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e8),L"-",&aStack_1d0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f0),L".",&aStack_1cf);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f8),L"/",&aStack_1ce);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x600),L"`",&aStack_1cd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x608),L"NA",&aStack_1cc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x610),L"NA",&aStack_1cb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x618),L"NA",&aStack_1ca);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x620),L"NA",&aStack_1c9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x628),L"NA",&aStack_1c8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x630),L"NA",&aStack_1c7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x638),L"NA",&aStack_1c6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x640),L"NA",&aStack_1c5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x648),L"NA",&aStack_1c4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x650),L"NA",&aStack_1c3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x658),L"NA",&aStack_1c2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x660),L"NA",&aStack_1c1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x668),L"NA",&aStack_1c0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x670),L"NA",&aStack_1bf);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x678),L"NA",&aStack_1be);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x680),L"NA",&aStack_1bd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x688),L"NA",&aStack_1bc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x690),L"NA",&aStack_1bb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x698),L"NA",&aStack_1ba);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a0),L"NA",&aStack_1b9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a8),L"NA",&aStack_1b8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b0),L"NA",&aStack_1b7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b8),L"NA",&aStack_1b6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c0),L"NA",&aStack_1b5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c8),L"NA",&aStack_1b4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d0),L"NA",&aStack_1b3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d8),L"[",&aStack_1b2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e0),L"\\",&aStack_1b1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e8),L"]",&aStack_1b0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f0),L"\'",&aStack_1af);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f8),L"NA",&aStack_1ae);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x700),L"NA",&aStack_1ad);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x708),L"NA",&aStack_1ac);
  __cxa_atexit(::__tcf_11,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEffect_Activation_Names,L"PASSIVE",&aStack_1ab);
  std::wstring::wstring((wstring_conflict *)(::gEffect_Activation_Names + 8),L"DYNAMIC",&aStack_1aa)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gEffect_Activation_Names + 0x10),L"TRANSFER",&aStack_1a9);
  __cxa_atexit(::__tcf_12,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEFFECT_STAT_MODIFIER_NAMES,L"MELEE",&aStack_1a8);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 8),L"RANGED",&aStack_1a7);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x10),L"DEFENSE",&aStack_1a6);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x18),L"MAGIC",&aStack_1a5);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x20),L"LEVEL",&aStack_1a4);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x28),L"OWNERLEVEL",&aStack_1a3);
  __cxa_atexit(::__tcf_13,0,&__dso_handle);
  std::string::string((string *)::gEFFECT_STAT_MODIFIER_ICON_NAMES,"iconmelee",&aStack_1a2);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 8),"iconranged",&aStack_1a1);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x10),"icondefense",
                      &aStack_1a0);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x18),"iconmagic",&aStack_19f)
  ;
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x20),"iconmagic",&aStack_19e)
  ;
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x28),"iconmagic",&aStack_19d)
  ;
  __cxa_atexit(::__tcf_14,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES,"tag_righthand",&aStack_19c);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 8),"tag_lefthand",&aStack_19b);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x10),"",&aStack_19a);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x18),"Bip01 Head",&aStack_199);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x20),"",&aStack_198);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x28),"Bip01 L Clavicle",&aStack_197);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x30),"",&aStack_196);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x38),"",&aStack_195);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x40),"",&aStack_194);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x48),"",&aStack_193);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x50),"",&aStack_192);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x58),"tag_leftarm",&aStack_191);
  __cxa_atexit(::__tcf_15,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES_SECONDARY,"",&aStack_190);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 8),"",&aStack_18f);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x10),"",&aStack_18e);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x18),"",&aStack_18d);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x20),"",&aStack_18c);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x28),"Bip01 R Clavicle",
                      &aStack_18b);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x30),"",&aStack_18a);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x38),"",&aStack_189);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x40),"",&aStack_188);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x48),"",&aStack_187);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x50),"",&aStack_186);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x58),"",&aStack_185);
  __cxa_atexit(::__tcf_16,0,&__dso_handle);
  std::string::string((string *)::KEquipmentIconName,"EquipLeftHand",&aStack_184);
  std::string::string((string *)(::KEquipmentIconName + 8),"EquipRightHand",&aStack_183);
  std::string::string((string *)(::KEquipmentIconName + 0x10),"EquipGloves",&aStack_182);
  std::string::string((string *)(::KEquipmentIconName + 0x18),"EquipHelm",&aStack_181);
  std::string::string((string *)(::KEquipmentIconName + 0x20),"EquipChest",&aStack_180);
  std::string::string((string *)(::KEquipmentIconName + 0x28),"EquipShoulder",&aStack_17f);
  std::string::string((string *)(::KEquipmentIconName + 0x30),"EquipBoots",&aStack_17e);
  std::string::string((string *)(::KEquipmentIconName + 0x38),"EquipBelt",&aStack_17d);
  std::string::string((string *)(::KEquipmentIconName + 0x40),"EquipRing1",&aStack_17c);
  std::string::string((string *)(::KEquipmentIconName + 0x48),"EquipRing2",&aStack_17b);
  std::string::string((string *)(::KEquipmentIconName + 0x50),"EquipAmulet",&aStack_17a);
  std::string::string((string *)(::KEquipmentIconName + 0x58),"",&aStack_179);
  __cxa_atexit(::__tcf_17,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames,L"CHEST",&aStack_178);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 8),L"GLOVES",&aStack_177);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x10),L"BOOTS",&aStack_176);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x18),L"HELMET",&aStack_175);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x20),L"SHOULDERS",&aStack_174);
  __cxa_atexit(::__tcf_18,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames2,L"",&aStack_173);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 8),L"",&aStack_172);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x10),L"",&aStack_171);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x18),L"FACE",&aStack_170);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x20),L"",&aStack_16f);
  __cxa_atexit(::__tcf_19,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_AIFLAG_TYPE_NAMES,L"AWARE",&aStack_16e);
  std::wstring::wstring((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 8),L"BERSERK",&aStack_16d);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x10),L"CANNOT INTERRUPT",&aStack_16c);
  std::wstring::wstring((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x18),L"FRIGHTEN",&aStack_16b);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x20),L"NO LINE OF SIGHT",&aStack_16a);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x28),L"NEVER CHANGE TARGET",&aStack_169);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AIFLAG_TYPE_NAMES + 0x30),L"CANNOT TARGET",&aStack_168);
  __cxa_atexit(::__tcf_20,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_AISTAT_TYPE_NAMES,L"NONE",&aStack_167);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 8),L"HP",&aStack_166);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x10),L"MANA",&aStack_165);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x18),L"HP PCT",&aStack_164);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x20),L"MANA PCT",&aStack_163);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AISTAT_TYPE_NAMES + 0x28),L"ACTIVE UNITS",&aStack_162);
  __cxa_atexit(::__tcf_21,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::g_AISTAT_LOGIC_NAMES,L"BELOW",&aStack_161);
  std::wstring::wstring((wstring_conflict *)&DAT_01489858,L"ABOVE",&aStack_160);
  __cxa_atexit(::__tcf_22,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_AISTAT_TARGET_NAMES,L"SELF",&aStack_15f);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 8),L"FORMATION",&aStack_15e);
  std::wstring::wstring((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 0x10),L"AREA",&aStack_15d);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 0x18),L"AREAUNITTYPES",&aStack_15c);
  std::wstring::wstring
            ((wstring_conflict *)(::g_AISTAT_TARGET_NAMES + 0x20),L"AREAFORMATION",&aStack_15b);
  __cxa_atexit(::__tcf_23,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_EVENT_TYPE_NAMES,L"EVENT_START",&aStack_15a);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 8),L"EVENT_END",&aStack_159);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x10),L"EVENT_TRIGGER",&aStack_158);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x18),L"EVENT_TRIGGER_TWO",&aStack_157
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x20),L"EVENT_UNITHIT",&aStack_156);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x28),L"EVENT_UNITDIE",&aStack_155);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x30),L"EVENT_MISSILEHIT",&aStack_154)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x38),L"EVENT_MISSILEDIE",&aStack_153)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x40),L"EVENT_DIEBYEFFECT",&aStack_152
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x48),L"EVENT_CASTERDIE",&aStack_151);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x50),L"EVENT_UNIT_CREATE",&aStack_150
            );
  __cxa_atexit(::__tcf_24,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_TARGET_TYPE_NAMES,L"NONE",&aStack_14f);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 8),L"POSITION",&aStack_14e);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x10),L"TARGET",&aStack_14d);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x18),L"SELF",&aStack_14c)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x20),L"EVERYBODY",&aStack_14b);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x28),L"POSITIONRANDOM",&aStack_14a);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x30),L"POSITIONFLEE",&aStack_149);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x38),L"ITEM",&aStack_148)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x40),L"UNIDENTIFIEDITEM",&aStack_147
            );
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x48),L"PETS",&aStack_146)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x50),L"SELFANDPETS",&aStack_145);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x58),L"TARGET_POS",&aStack_144);
  __cxa_atexit(::__tcf_25,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_ACTIVATION_TYPE_NAMES,L"ANY",&aStack_143);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 8),L"PROC",&aStack_142);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 0x10),L"WEAPON",&aStack_141);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 0x18),L"NORMAL",&aStack_140);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 0x20),L"PASSIVE",&aStack_13f);
  __cxa_atexit(::__tcf_26,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_TYPE_NAMES,L"SKILL",&aStack_13e);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TYPE_NAMES + 8),L"OFFENSIVE",&aStack_13d);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TYPE_NAMES + 0x10),L"DEFENSIVE",&aStack_13c);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TYPE_NAMES + 0x18),L"CHARM",&aStack_13b);
  ::gSKILL_TYPE_NAMES._32_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_27,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_TYPE_DISPLAY_NAMES,L"Class Skill",&aStack_13a);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TYPE_DISPLAY_NAMES + 8),L"Offensive Spell",&aStack_139);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TYPE_DISPLAY_NAMES + 0x10),L"Defensive Spell",&aStack_138
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TYPE_DISPLAY_NAMES + 0x18),L"Charm Spell",&aStack_137);
  ::gSKILL_TYPE_DISPLAY_NAMES._32_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_28,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_BONE_ATTACHMENT_NAMES,L"",&aStack_136);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 8),L"CENTER",&aStack_135);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x10),L"HEAD",&aStack_134);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x18),L"RIGHTHAND",&aStack_133);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x20),L"LEFTHAND",&aStack_132);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x28),L"RIGHTSHOULDER",
             &aStack_131);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x30),L"LEFTSHOULDER",&aStack_130
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x38),L"POSITION",&aStack_12f);
  __cxa_atexit(::__tcf_29,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEDITOR_EVENT_NAMES,L"STOP",&aStack_12e);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 8),L"PLAY",&aStack_12d);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x10),L"RELOAD TILES",&aStack_12c);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x18),L"TOGGLE LIGHTING",&aStack_12b);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x20),L"SELECT COLLIDABLE",&aStack_12a);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x28),L"PAUSE PARTICLES",&aStack_129);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x30),L"UNPAUSE PARTICLES",&aStack_128);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x38),L"COLLISION ALL",&aStack_127);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x40),L"COLLISION MODELS",&aStack_126);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x48),L"COLLISION PREFABS",&aStack_125);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x50),L"COLLISION ROOMPIECES",&aStack_124)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x58),L"COLLISION ROOMPROPS",&aStack_123);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x60),L"RELOAD GRAPHS",&aStack_122);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x68),L"TOGGLE PLAYER LIGHT",&aStack_121);
  __cxa_atexit(::__tcf_30,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEDITOR_FLAG_NAMES,L"LOGIC ENABLED",&aStack_120);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 8),L"INGAME MODE",&aStack_11f);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x10),L"SHOW STATS",&aStack_11e)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x18),L"EDIT POSITION",&aStack_11d);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x20),L"EDIT SCALE",&aStack_11c)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x28),L"EDIT ORIENTATION",&aStack_11b);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x30),L"EDIT NONE",&aStack_11a);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x38),L"SHOW HELPERS",&aStack_119);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x40),L"SHOW GRID",&aStack_118);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x48),L"SHOW WORKING PLANE",&aStack_117);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x50),L"SNAP TO GRID",&aStack_116);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x58),L"SUSPEND EDITOR",&aStack_115);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x60),L"LIGHTING VISIBLE",&aStack_114);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x68),L"RECALCULATE LIGHTING",&aStack_113);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x70),L"SHOW EDGES",&aStack_112)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x78),L"UPDATE PARTICLES CIRCLE",
             &aStack_111);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x80),L"SHOW LOGIC OUTPUT",&aStack_110);
  __cxa_atexit(::__tcf_31,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::gEDITOR_UPDATE_MASKS,L"OBJECT SELECTION CHANGED",&aStack_10f);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 8),L"OBJECT DATA CHANGED",&aStack_10e);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 0x10),L"OBJECTS CREATED",&aStack_10d);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 0x18),L"REFRESH TREE VIEW",&aStack_10c);
  __cxa_atexit(::__tcf_32,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KContextTipNames,L"TIP_INVENTORY",&aStack_10b);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 8),L"TIP_UNIDENTIFIED",&aStack_10a);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x10),L"TIP_INVENTORYFULL",&aStack_109);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x18),L"TIP_HEALTHLOW",&aStack_108);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x20),L"TIP_MANALOW",&aStack_107);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x28),L"TIP_MERCHANT",&aStack_106)
  ;
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x30),L"TIP_LEVELUP",&aStack_105);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x38),L"TIP_STATS",&aStack_104);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x40),L"TIP_SPELL",&aStack_103);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x48),L"TIP_WELCOME",&aStack_102);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x50),L"TIP_SOCKETABLE",&aStack_101);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x58),L"TIP_PETFLEE",&aStack_100);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x60),L"TIP_GAMBLE",&aStack_ff);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x68),L"TIP_ENCHANT",&aStack_fe);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x70),L"TIP_TRANSMUTE",&aStack_fd)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x78),L"TIP_PETINVENTORY",&aStack_fc);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x80),L"TIP_PETINVENTORYFULL",&aStack_fb);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x88),L"TIP_STASH",&aStack_fa);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x90),L"TIP_FISHING",&aStack_f9);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x98),L"TIP_SPELLFIND",&aStack_f8)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xa0),L"TIP_QUESTCOMPLETE",&aStack_f7);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xa8),L"TIP_SHAREDSTASH",&aStack_f6);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xb0),L"TIP_HOWTOATTACK",&aStack_f5);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xb8),L"TIP_TEMP5",&aStack_f4);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xc0),L"TIP_TEMP6",&aStack_f3);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 200),L"TIP_TEMP7",&aStack_f2);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xd0),L"TIP_TEMP8",&aStack_f1);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xd8),L"TIP_TEMP9",&aStack_f0);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xe0),L"TIP_TEMP10",&aStack_ef);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xe8),L"TIP_TEMP11",&aStack_ee);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xf0),L"TIP_TEMP12",&aStack_ed);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xf8),L"TIP_TEMP13",&aStack_ec);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x100),L"TIP_TEMP14",&aStack_eb);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x108),L"TIP_TEMP15",&aStack_ea);
  __cxa_atexit(::__tcf_33,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::m_gFileVersionExtension,L".svt",&aStack_e9);
  __cxa_atexit(std::wstring::~wstring,&::m_gFileVersionExtension,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::g_LEVELLAYOUT_CREATION_NAMES,L"MONSTERSPAWNCLASS",&aStack_e8);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 8),L"CHAMPIONSPAWNCLASS",
             &aStack_e7);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x10),L"PROPSPAWNCLASS",
             &aStack_e6);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x18),L"NPCSPAWNCLASS",&aStack_e5
            );
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x20),L"CREEPSPAWNCLASS",
             &aStack_e4);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x28),L"GOLD",&aStack_e3);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x30),L"FISHSPAWNCLASS",
             &aStack_e2);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x38),L"FORMATIONS",&aStack_e1);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x40),L"QUESTMONSTERSPAWNCLASS",
             &aStack_e0);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x48),L"QUESTITEMSPAWNCLASS",
             &aStack_df);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x50),L"QUESTCHAMPIONSPAWNCLASS",
             &aStack_de);
  __cxa_atexit(::__tcf_34,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES,
             L"MONSTERSPAWNCLASSRANDOMIZED",&aStack_dd);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 8),
             L"CHAMPIONSPAWNCLASSRANDOMIZED",&aStack_dc);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x10),
             L"PROPSPAWNCLASSRANDOMIZED",&aStack_db);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x18),
             L"NPCSPAWNCLASSRANDOMIZED",&aStack_da);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x20),
             L"CREEPSPAWNCLASSRANDOMIZED",&aStack_d9);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x28),
             L"GOLDRANDOMIZED",&aStack_d8);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x30),
             L"FISHSPAWNCLASSRANDOMIZED",&aStack_d7);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x38),
             L"FORMATIONSRANDOMIZED",&aStack_d6);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x40),
             L"QUESTMONSTERSPAWNCLASSRANDOMIZED",&aStack_d5);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x48),
             L"QUESTITEMSPAWNCLASSRANDOMIZED",&aStack_d4);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x50),
             L"QUESTCHAMPIONSPAWNCLASSRANDOMIZED",&aStack_d3);
  __cxa_atexit(::__tcf_35,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::g_LEVELLAYOUT_CREATION_PATHNODES,L"MONSTERS_PER_METER_MIN",
             &aStack_d2);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 8),L"MONSTERS_PER_METER_MAX",
             &aStack_d1);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x10),
             L"CHAMPIONS_PER_METER_MIN",&aStack_d0);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x18),
             L"CHAMPIONS_PER_METER_MAX",&aStack_cf);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x20),L"PROPS_PER_METER_MIN",
             &aStack_ce);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x28),L"PROPS_PER_METER_MAX",
             &aStack_cd);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x30),L"NPCS_PER_METER_MIN",
             &aStack_cc);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x38),L"NPCS_PER_METER_MAX",
             &aStack_cb);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x40),L"CREEPS_PER_METER_MIN"
             ,&aStack_ca);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x48),L"CREEPS_PER_METER_MAX"
             ,&aStack_c9);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x50),L"GOLD_PER_METER_MIN",
             &aStack_c8);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x58),L"GOLD_PER_METER_MAX",
             &aStack_c7);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x60),L"FISH_PER_METER_MIN",
             &aStack_c6);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x68),L"FISH_PER_METER_MAX",
             &aStack_c5);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x70),
             L"FORMATIONS_PER_METER_MIN",&aStack_c4);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x78),
             L"FORMATIONS_PER_METER_MAX",&aStack_c3);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x80),L"",&aStack_c2);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x88),L"",&aStack_c1);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x90),L"",&aStack_c0);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x98),L"",&aStack_bf);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0xa0),L"",&aStack_be);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0xa8),L"",&aStack_bd);
  __cxa_atexit(::__tcf_36,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::g_LEVELLAYOUT_CREATION_COUNTS,L"MONSTER_MIN",&aStack_bc);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 8),L"MONSTER_MAX",&aStack_bb);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x10),L"CHAMPIONS_MIN",
             &aStack_ba);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x18),L"CHAMPIONS_MAX",
             &aStack_b9);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x20),L"PROPS_MIN",&aStack_b8);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x28),L"PPROPS_MAX",&aStack_b7);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x30),L"NPCS_MIN",&aStack_b6);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x38),L"NPCS_MAX",&aStack_b5);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x40),L"CREEPS_MIN",&aStack_b4);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x48),L"CREEPS_MAX",&aStack_b3);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x50),L"GOLD_MIN",&aStack_b2);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x58),L"GOLD_MAX",&aStack_b1);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x60),L"FISH_MIN",&aStack_b0);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x68),L"FISH_MAX",&aStack_af);
  std::wstring::wstring((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x70),L"",&aStack_ae)
  ;
  std::wstring::wstring((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x78),L"",&aStack_ad)
  ;
  std::wstring::wstring((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x80),L"",&aStack_ac)
  ;
  std::wstring::wstring((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x88),L"",&aStack_ab)
  ;
  std::wstring::wstring((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x90),L"",&aStack_aa)
  ;
  std::wstring::wstring((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x98),L"",&aStack_a9)
  ;
  std::wstring::wstring((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0xa0),L"",&aStack_a8)
  ;
  std::wstring::wstring((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0xa8),L"",&aStack_a7)
  ;
  __cxa_atexit(::__tcf_37,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gOUTPUT_EVENTS_NAMES,L"Triggered",&aStack_a6);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 8),L"Triggered First Time",&aStack_a5);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x10),L"Deactivated",&aStack_a4);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x18),L"Deactivated First Time",
             &aStack_a3);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x20),L"On Visible",&aStack_a2);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x28),L"On Invisible",&aStack_a1);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x30),L"Enabled",&aStack_a0);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x38),L"Disabled",&aStack_9f);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x40),L"Activated",&aStack_9e)
  ;
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x48),L"Reset",&aStack_9d);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x50),L"Initialized",&aStack_9c);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x58),L"Playing",&aStack_9b);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x60),L"Stopped",&aStack_9a);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x68),L"Sound Ended",&aStack_99);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x70),L"Paused",&aStack_98);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x78),L"Resumed",&aStack_97);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x80),L"Incremented",&aStack_96);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x88),L"First Increment",&aStack_95);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x90),L"Second Increment",&aStack_94);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x98),L"Third Increment",&aStack_93);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xa0),L"Fourth Increment",&aStack_92);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xa8),L"Fifth Increment",&aStack_91);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xb0),L"Increment Greater Then Five",
             &aStack_90);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xb8),L"Monsters Spawned",&aStack_8f);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xc0),L"Monster Killed",&aStack_8e);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 200),L"All Monsters Dead",&aStack_8d);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xd0),L"All Units Spawned",&aStack_8c);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xd8),L"Item Picked Up",&aStack_8b);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xe0),L"All Items Picked Up",&aStack_8a);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xe8),L"Item Interacted",&aStack_89);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xf0),L"All Items Interacted With",
             &aStack_88);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0xf8),L"Particle Started",&aStack_87);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x100),L"Particle Stopped",&aStack_86);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x108),L"Particle Paused",&aStack_85);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x110),L"Particle Resumed",&aStack_84);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x118),L"Stopped",&aStack_83);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x120),L"Started",&aStack_82);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x128),L"Paused",&aStack_81);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x130),L"Reset to Beginning",&aStack_80);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x138),L"Reset to End",&aStack_7f);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x140),L"Looped",&aStack_7e);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x148),L"Started Backwards",&aStack_7d);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x150),L"Started Forwards",&aStack_7c);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x158),L"Stopped Backwards",&aStack_7b);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x160),L"Stopped Forwards",&aStack_7a);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x168),L"Finished",&aStack_79)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x170),L"State One",&aStack_78);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x178),L"State Two",&aStack_77);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x180),L"Activation Failed",&aStack_76);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x188),L"One",&aStack_75);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 400),L"Two",&aStack_74);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x198),L"Three",&aStack_73);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1a0),L"Four",&aStack_72);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1a8),L"Five",&aStack_71);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1b0),L"FAILED",&aStack_70);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1b8),L"SUCCESS",&aStack_6f);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1c0),L"Interacted with Unit",&aStack_6e
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1c8),L"HP 90 PCT",&aStack_6d);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1d0),L"HP 80 PCT",&aStack_6c);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1d8),L"HP 70 PCT",&aStack_6b);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1e0),L"HP 60 PCT",&aStack_6a);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1e8),L"HP 50 PCT",&aStack_69);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1f0),L"HP 40 PCT",&aStack_68);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x1f8),L"HP 30 PCT",&aStack_67);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x200),L"HP 20 PCT",&aStack_66);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x208),L"HP 10 PCT",&aStack_65);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x210),L"Monster Alerted",&aStack_64);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x218),L"Player HP Below 90 PCT",
             &aStack_63);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x220),L"Player HP Below 80 PCT",
             &aStack_62);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x228),L"Player HP Below 70 PCT",
             &aStack_61);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x230),L"Player HP Below 60 PCT",
             &aStack_60);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x238),L"Player HP Below 50 PCT",
             &aStack_5f);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x240),L"Player HP Below 40 PCT",
             &aStack_5e);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x248),L"Player HP Below 30 PCT",
             &aStack_5d);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x250),L"Player HP Below 20 PCT",
             &aStack_5c);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 600),L"Player HP Below 10 PCT",&aStack_5b
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x260),L"Player HP Above 90 PCT",
             &aStack_5a);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x268),L"Player HP Above 80 PCT",
             &aStack_59);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x270),L"Player HP Above 70 PCT",
             &aStack_58);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x278),L"Player HP Above 60 PCT",
             &aStack_57);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x280),L"Player HP Above 50 PCT",
             &aStack_56);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x288),L"Player HP Above 40 PCT",
             &aStack_55);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x290),L"Player HP Above 30 PCT",
             &aStack_54);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x298),L"Player HP Above 20 PCT",
             &aStack_53);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2a0),L"Player HP Above 10 PCT",
             &aStack_52);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2a8),L"Accepted",&aStack_51)
  ;
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2b0),L"Declined",&aStack_50)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2b8),L"Camera Moving",&aStack_4f);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2c0),L"Camera Stopped",&aStack_4e);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2c8),L"Camera Pausing",&aStack_4d);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2d0),L"Camera Control Restored",
             &aStack_4c);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2d8),L"Interacting",&aStack_4b);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2e0),L"Interacted",&aStack_4a);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2e8),L"Interacted Accepted",&aStack_49)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2f0),L"Interacted Declined",&aStack_48)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x2f8),L"Interacted Closed",&aStack_47);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x300),L"Invulnerable",&aStack_46);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x308),L"Vulnerable",&aStack_45);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x310),L"Quest Active",&aStack_44);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x318),L"Quest Not Active",&aStack_43);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 800),L"Quest Complete",&aStack_42);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x328),L"Quest Not Complete",&aStack_41);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x330),L"Quest Abandoned",&aStack_40);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x338),L"Skill Started",&aStack_3f);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x340),L"Skill Stopped",&aStack_3e);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x348),L"Skill Learned",&aStack_3d);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x350),L"Skill Unlearned",&aStack_3c);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x358),L"Item Dropped",&aStack_3b);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x360),L"Item Equipped",&aStack_3a);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x368),L"Item Unequipped",&aStack_39);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x370),L"End of Path Reached",&aStack_38)
  ;
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x378),L"Clicked",&aStack_37);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x380),L"Animation Stopped",&aStack_36);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x388),L"Animation Playing",&aStack_35);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x390),L"Skip Cutscene",&aStack_34);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x398),L"Level Activated",&aStack_33);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3a0),L"Insufficient funds",&aStack_32);
  std::wstring::wstring
            ((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3a8),L"Money Taken",&aStack_31);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3b0),L"Stop",&aStack_30);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3b8),L"Start",&aStack_2f);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3c0),L"Pause",&aStack_2e);
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3c8),L"Output 1",&aStack_2d)
  ;
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3d0),L"Output 2",&aStack_2c)
  ;
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3d8),L"Output 3",&aStack_2b)
  ;
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 0x3e0),L"Output 4",&aStack_2a)
  ;
  std::wstring::wstring((wstring_conflict *)(::gOUTPUT_EVENTS_NAMES + 1000),L"Output 5",aaStack_29);
  __cxa_atexit(::__tcf_38,0,&__dso_handle);
  return;
}

/* address=008df370
   symbol=CMonster::huntAI */

/* CMonster::huntAI(float, CLevel&) */

void CMonster::huntAI(float param_1,CLevel *param_2)

{
  ulong uVar1;
  char cVar2;
  char cVar3;
  int iVar4;
  CPositionableObject *this;
  long lVar5;
  long lVar6;
  CLevel *in_RSI;
  float extraout_XMM0_Da;
  float extraout_XMM0_Da_00;
  float extraout_XMM0_Da_01;
  float extraout_XMM0_Da_02;
  float extraout_XMM0_Da_03;
  float extraout_XMM0_Da_04;
  float fVar7;
  float fVar8;
  float in_XMM1_Da;
  float fVar9;
  float fVar10;
  float local_148;
  float local_144;
  float local_140;
  float local_138;
  float local_134;
  float local_130;
  undefined8 local_128;
  float local_120;
  undefined8 local_118;
  float local_110;
  float local_108 [4];
  undefined8 local_f8;
  float local_f0;
  undefined8 local_e8;
  float local_e0;
  undefined8 local_d8;
  float local_d0;
  undefined8 local_c8;
  float local_c0;
  undefined8 local_b8;
  float local_b0;
  undefined8 local_a8;
  float local_a0;
  undefined8 local_98;
  float local_90;
  float local_88 [4];
  undefined8 local_78;
  float local_70;
  undefined8 local_68;
  float local_60;
  undefined8 local_58;
  float local_50;
  undefined8 local_48;
  undefined8 local_38;
  undefined8 local_28;

  if (((((*(CCharacter **)(param_2 + 0x340) == (CCharacter *)0x0) ||
        (cVar2 = CCharacter::alive(*(CCharacter **)(param_2 + 0x340)), param_1 = extraout_XMM0_Da,
        cVar2 == '\0')) ||
       (cVar2 = CCharacter::isPetNearDeath((CCharacter *)param_2), param_1 = extraout_XMM0_Da_00,
       cVar2 != '\0')) ||
      ((cVar2 = CCharacter::isPetNearDeath(*(CCharacter **)(param_2 + 0x340)),
       param_1 = extraout_XMM0_Da_01, cVar2 != '\0' ||
       (cVar2 = (**(code **)(*(long *)param_2 + 0x3f8))(param_2), param_1 = extraout_XMM0_Da_02,
       cVar2 == '\0')))) ||
     ((*(CCharacter **)(param_2 + 0x340) == (CCharacter *)0x0 ||
      (cVar2 = CCharacter::alive(*(CCharacter **)(param_2 + 0x340)), param_1 = extraout_XMM0_Da_03,
      cVar2 == '\0')))) {
LAB_008df396:
    lVar5 = *(long *)param_2;
LAB_008df39e:
    (**(code **)(lVar5 + 0x348))(param_1,param_2);
    CCharacter::setTarget((CCharacter *)param_2,(CCharacter *)0x0);
    return;
  }
  cVar2 = CCharacter::isFriend((CCharacter *)param_2,*(CCharacter **)(param_2 + 0x340));
  if (cVar2 != '\0') {
    lVar5 = *(long *)param_2;
    param_1 = extraout_XMM0_Da_04;
    goto LAB_008df39e;
  }
  if (param_2[0x682] != (CLevel)0x0) {
    if (*(CPositionableObject **)(param_2 + 0x340) == (CPositionableObject *)0x0) {
      return;
    }
    local_28 = CPositionableObject::getPosition(*(CPositionableObject **)(param_2 + 0x340),true);
    uVar1 = (ulong)local_28 >> 0x20;
    local_38 = CPositionableObject::getPosition((CPositionableObject *)param_2,false);
    if ((float)uVar1 < (float)((ulong)local_38 >> 0x20) - DAT_00fa47fc) {
      CCharacter::attemptJumpDown();
    }
  }
  if (*(long *)(param_2 + 0x340) == 0) {
    return;
  }
  if (((*(long *)(param_2 + 0x718) != 0) &&
      (cVar2 = CAIManager::hasAIFlag(*(long *)(param_2 + 0x718),1), cVar2 != '\0')) &&
     ((this = (CPositionableObject *)CCharacter::calculateTargetInSight((CCharacter *)param_2,3,1),
      this != (CPositionableObject *)0x0 && (this != *(CPositionableObject **)(param_2 + 0x340)))))
  {
    local_58 = CPositionableObject::getPosition((CPositionableObject *)param_2,true);
    local_50 = in_XMM1_Da;
    local_48 = CPositionableObject::getPosition(*(CPositionableObject **)(param_2 + 0x340),true);
    fVar9 = (float)((ulong)local_48 >> 0x20) - local_58._4_4_;
    local_138 = (float)local_48 - (float)local_58;
    local_130 = in_XMM1_Da - local_50;
    local_134 = fVar9;
    fVar7 = (float)Ogre::Vector3::length((Vector3 *)&local_138);
    local_78 = CPositionableObject::getPosition((CPositionableObject *)param_2,true);
    local_70 = fVar9;
    local_68 = CPositionableObject::getPosition(this,true);
    in_XMM1_Da = (float)((ulong)local_68 >> 0x20) - local_78._4_4_;
    local_148 = (float)local_68 - (float)local_78;
    local_140 = fVar9 - local_70;
    local_144 = in_XMM1_Da;
    local_60 = fVar9;
    fVar9 = (float)Ogre::Vector3::length((Vector3 *)&local_148);
    if (fVar9 < fVar7 - DAT_00fa480c) {
      CCharacter::setTarget((CCharacter *)param_2,(CCharacter *)this);
    }
  }
  local_a8 = CPositionableObject::getPosition((CPositionableObject *)param_2,true);
  local_a0 = in_XMM1_Da;
  local_98 = CPositionableObject::getPosition(*(CPositionableObject **)(param_2 + 0x340),true);
  local_88[1] = 0.0;
  local_88[0] = (float)local_98 - (float)local_a8;
  local_88[2] = in_XMM1_Da - local_a0;
  fVar7 = *(float *)(param_2 + 0x370);
  fVar9 = SQRT(local_88[0] * local_88[0] + 0.0 + local_88[2] * local_88[2]);
  param_2[0x321] = (CLevel)(*(float *)(param_2 + 0x364) <= fVar9);
  local_90 = in_XMM1_Da;
  fVar8 = (float)CCharacter::getEffectValue((CCharacter *)param_2,0x2c,7);
  lVar5 = 0;
  if (*(long *)(param_2 + 0x68) != 0) {
    lVar5 = *(long *)(*(long *)(param_2 + 0x68) + 0x18);
  }
  if (((fVar8 * fVar7) / DAT_00fa483c + fVar7 + *(float *)(*(long *)(lVar5 + 0x1d8) + 0x98) <= fVar9
      ) && (*(long *)(param_2 + 0x640) == 0)) {
    param_1 = (float)CCharacter::stopPathing((CCharacter *)param_2);
    goto LAB_008df396;
  }
  cVar2 = CCharacter::validLineOfSight(param_2,SUB81(in_RSI,0));
  cVar3 = CCharacter::inAttackRange(param_2,0);
  if (((cVar3 == '\0') || (cVar2 == '\0')) && (DAT_00fa4810 < *(float *)(param_2 + 0x278))) {
    fVar7 = (float)CCharacter::walkingSpeed((CCharacter *)param_2);
    fVar8 = 0.0;
    if ((fVar7 == 0.0) && (!NAN(fVar7))) {
      fVar7 = (float)CCharacter::runningSpeed((CCharacter *)param_2);
      if ((fVar7 == 0.0) && (!NAN(fVar7))) goto LAB_008df973;
    }
    iVar4 = *(int *)(param_2 + 0x334);
    if (iVar4 == 3) {
      iVar4 = UTILITIES::randomIntegerBetweenVolatile(0,100);
      if (iVar4 < 10) goto LAB_008dfbad;
      iVar4 = *(int *)(param_2 + 0x334);
    }
    if (iVar4 == 1) {
      iVar4 = UTILITIES::randomIntegerBetweenVolatile(0,100);
      if (iVar4 < 10) {
LAB_008dfbad:
        (**(code **)(*(long *)param_2 + 0x348))(param_2,10);
        return;
      }
      iVar4 = *(int *)(param_2 + 0x334);
    }
    if ((iVar4 == 4) && (iVar4 = UTILITIES::randomIntegerBetweenVolatile(0,100), iVar4 < 10)) {
      (**(code **)(*(long *)param_2 + 0x348))(param_2);
      local_e8 = CPositionableObject::getPosition(*(CPositionableObject **)(param_2 + 0x340),false);
      fVar9 = DAT_00fa86d4 + fVar8;
      local_e0 = fVar8;
      local_d8 = CPositionableObject::getPosition(*(CPositionableObject **)(param_2 + 0x340),true);
      local_d0 = fVar8;
      fVar8 = (float)UTILITIES::randomBetweenVolatile(fVar8 - DAT_00fa86d4,fVar9);
      local_c8 = CPositionableObject::getPosition(*(CPositionableObject **)(param_2 + 0x340),false);
      fVar10 = DAT_00fa86d4 + (float)local_c8;
      fVar7 = fVar10;
      local_c0 = fVar9;
      local_b8 = CPositionableObject::getPosition(*(CPositionableObject **)(param_2 + 0x340),true);
      local_b0 = fVar7;
      fVar7 = (float)UTILITIES::randomBetweenVolatile((float)local_b8 - DAT_00fa86d4,fVar10);
      CCharacter::setDestination((CCharacter *)param_2,in_RSI,fVar7,fVar8);
      return;
    }
    fVar9 = fVar8;
    if (param_2[0x264] == (CLevel)0x0) {
LAB_008dfac8:
      CCharacter::followCharacter((CCharacter *)param_2,*(CLevel **)(param_2 + 0x340));
    }
    else {
      local_f8 = CPositionableObject::getPosition(*(CPositionableObject **)(param_2 + 0x340),true);
      local_88[1] = 0.0;
      fVar9 = (float)local_f8 - *(float *)(param_2 + 0x228);
      local_88[2] = fVar8 - *(float *)(param_2 + 0x230);
      local_f0 = fVar8;
      local_88[0] = fVar9;
      fVar7 = (float)Ogre::Vector3::length((Vector3 *)local_88);
      if (DAT_00fa47fc <= fVar7) goto LAB_008dfac8;
    }
    if (param_2[0x264] == (CLevel)0x0) goto LAB_008df973;
  }
  cVar3 = CCharacter::inAttackRange(param_2,0);
  if ((cVar3 != '\0') && (cVar2 != '\0')) {
    (**(code **)(*(long *)param_2 + 0x348))(param_2,3);
    (**(code **)(*(long *)param_2 + 0x3d8))(0,param_2);
    CCharacter::stopPathing((CCharacter *)param_2);
    return;
  }
  lVar5 = *(long *)(param_2 + 0x398);
  if (lVar5 != 0) {
    lVar6 = *(long *)(lVar5 + 0x90);
    if ((lVar6 == 0) && (*(int *)(lVar5 + 0xa8) != 0)) {
      lVar6 = **(long **)(lVar5 + 0xa0);
    }
    if ((*(int *)(lVar6 + 0x50) == 2) &&
       (cVar2 = CCharacter::canCastCurrentSkill
                          ((CBaseUnit *)param_2,SUB81(*(undefined8 *)(param_2 + 0x340),0),false),
       cVar2 != '\0')) {
      (**(code **)(*(long *)param_2 + 0x348))(param_2,0xd);
      (**(code **)(*(long *)param_2 + 0x3e0))(0,param_2);
      return;
    }
  }
  iVar4 = UTILITIES::randomIntegerBetweenVolatile(0,100);
  if (iVar4 < 10) {
    selectOffensiveSkill((CMonster *)param_2,false);
  }
  if (*(long *)(param_2 + 0x640) == 0) {
    return;
  }
  if (*(CPositionableObject **)(param_2 + 0x340) == (CPositionableObject *)0x0) {
    return;
  }
  local_128 = CPositionableObject::getPosition(*(CPositionableObject **)(param_2 + 0x340),true);
  local_120 = fVar9;
  local_118 = CPositionableObject::getPosition(*(CPositionableObject **)(param_2 + 0x640),true);
  local_108[1] = 0.0;
  local_108[0] = (float)local_118 - (float)local_128;
  local_108[2] = fVar9 - local_120;
  local_110 = fVar9;
  fVar7 = (float)Ogre::Vector3::length((Vector3 *)local_108);
  if (fVar7 <= DAT_00fa4814) {
    return;
  }
  CCharacter::setTarget((CCharacter *)param_2,(CCharacter *)0x0);
LAB_008df973:
  (**(code **)(*(long *)param_2 + 0x348))(param_2,2);
  return;
}

/* address=008dfd80
   symbol=CMonster::attackAI */

/* CMonster::attackAI(float, CLevel&) */

void __thiscall CMonster::attackAI(CMonster *this,float param_1,CLevel *param_2)

{
  CCharacter *this_00;
  char cVar1;
  int iVar2;
  long lVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  undefined8 local_48;
  float local_40;
  undefined8 local_38;
  float local_30;
  undefined8 local_28;
  float local_20;

  fVar5 = 0.0;
  if (0.0 < *(float *)(this + 0x7e8)) {
LAB_008dfdf8:
    lVar3 = *(long *)this;
  }
  else {
    if (*(long *)(this + 0x350) != 0) {
      CCharacter::setTargetItem((CCharacter *)this,(CItem *)0x0);
    }
    if (((*(CCharacter **)(this + 0x340) != (CCharacter *)0x0) &&
        (cVar1 = CCharacter::alive(*(CCharacter **)(this + 0x340)), cVar1 != '\0')) &&
       (cVar1 = CCharacter::isPetNearDeath((CCharacter *)this), cVar1 == '\0')) {
      this_00 = *(CCharacter **)(this + 0x340);
      cVar1 = CCharacter::isPetNearDeath(this_00);
      if (((cVar1 == '\0') && (cVar1 = CCharacter::alive(this_00), cVar1 != '\0')) &&
         ((*(int *)(this_00 + 0x330) != 0x2a && (*(int *)(this_00 + 0x330) != 0x29)))) {
        cVar1 = CCharacter::isFriend((CCharacter *)this,*(CCharacter **)(this + 0x340));
        if (cVar1 == '\0') {
          if (((*(long *)(this + 0x390) == 0) || (this[0x1f5] != (CMonster)0x0)) &&
             ((CCharacter::selectAttack((CCharacter *)this), *(long *)(this + 0x390) == 0 ||
              (this[0x1f5] != (CMonster)0x0)))) {
            CCharacter::setActiveSkill((CCharacter *)this,(CSkill *)0x0,false);
            selectOffensiveSkill(this,true);
            if (*(long *)(this + 0x398) == 0) {
              return;
            }
            iVar2 = CCharacter::inSkillRange((longlong)this,true);
            if (iVar2 != 0) {
              return;
            }
LAB_008dfec0:
            CCharacter::castSkill((longlong)this);
            return;
          }
          local_38 = CPositionableObject::getPosition((CPositionableObject *)this,true);
          local_30 = fVar5;
          local_28 = CPositionableObject::getPosition(*(CPositionableObject **)(this + 0x340),true);
          fVar6 = (fVar5 - local_30) * (fVar5 - local_30);
          local_20 = fVar5;
          if (SQRT(((float)local_28 - (float)local_38) * ((float)local_28 - (float)local_38) + 0.0 +
                   fVar6) < *(float *)(this + 0x370)) {
            local_48 = CPositionableObject::getPosition
                                 (*(CPositionableObject **)(this + 0x340),true);
            local_40 = fVar6;
            CCharacter::turnTowardPosition((CCharacter *)this,(Vector3 *)&local_48,param_1);
            cVar1 = CCharacter::facingTarget((CCharacter *)this);
            if (cVar1 != '\0') {
              CCharacter::setActiveSkill((CCharacter *)this,(CSkill *)0x0,false);
              selectOffensiveSkill(this,true);
              if ((*(long *)(this + 0x398) != 0) &&
                 (iVar2 = CCharacter::inSkillRange((longlong)this,true), iVar2 == 0))
              goto LAB_008dfec0;
            }
            cVar1 = CCharacter::inAttackRange(this,0);
            if ((cVar1 == '\0') ||
               (cVar1 = CCharacter::validLineOfSight((CLevel *)this,SUB81(param_2,0)), cVar1 == '\0'
               )) {
              cVar1 = CCharacter::performingAttack((CCharacter *)this);
              if (cVar1 != '\0') {
                return;
              }
              (**(code **)(*(long *)this + 0x348))(this,4);
              return;
            }
            cVar1 = CCharacter::performingAttack((CCharacter *)this);
            if (cVar1 == '\0') {
              if ((*(int *)(this + 0x334) == 4) &&
                 (iVar2 = UTILITIES::randomIntegerBetweenVolatile(0,100), iVar2 < 0x19)) {
                (**(code **)(*(long *)this + 0x348))(this);
                CPositionableObject::getPosition(*(CPositionableObject **)(this + 0x340),false);
                fVar5 = DAT_00fa86d4 + fVar6;
                CPositionableObject::getPosition(*(CPositionableObject **)(this + 0x340),true);
                fVar5 = (float)UTILITIES::randomBetweenVolatile(fVar6 - DAT_00fa86d4,fVar5);
                fVar6 = (float)CPositionableObject::getPosition
                                         (*(CPositionableObject **)(this + 0x340),false);
                fVar6 = DAT_00fa86d4 + fVar6;
                fVar4 = (float)CPositionableObject::getPosition
                                         (*(CPositionableObject **)(this + 0x340),true);
                fVar6 = (float)UTILITIES::randomBetweenVolatile(fVar4 - DAT_00fa86d4,fVar6);
                CCharacter::setDestination((CCharacter *)this,param_2,fVar6,fVar5);
                return;
              }
              cVar1 = CCharacter::facingTarget((CCharacter *)this);
              if (cVar1 != '\0') {
                CCharacter::selectAttack((CCharacter *)this,0);
                cVar1 = CCharacter::attack();
                if (cVar1 != '\0') {
                  if (*(long *)(this + 0x498) != 0) {
                    *(float *)(this + 0x7e8) =
                         (float)((uint)*(float *)(this + 0x7e8) &
                                -(uint)(0.0 < *(float *)(this + 0x7e8))) +
                         *(float *)(*(long *)(this + 0x498) + 0x408);
                  }
                  fVar5 = *(float *)(this + 0x7e8);
                  if (fVar5 <= 0.0) {
                    fVar5 = 0.0;
                  }
                  *(float *)(this + 0x7e8) = fVar5 + *(float *)(this + 0x7ec);
                }
              }
            }
            cVar1 = (**(code **)(*(long *)this + 0x3f8))(this);
            if (cVar1 != '\0') {
              return;
            }
            (**(code **)(*(long *)this + 0x348))(this,10);
            return;
          }
          CCharacter::stopPathing((CCharacter *)this);
          lVar3 = *(long *)this;
          goto LAB_008dfdd5;
        }
        goto LAB_008dfdf8;
      }
    }
    lVar3 = *(long *)this;
  }
LAB_008dfdd5:
  (**(code **)(lVar3 + 0x348))(this);
  CCharacter::setTarget((CCharacter *)this,(CCharacter *)0x0);
  return;
}

/* address=008e02b0
   symbol=CMonster::idleAINormal */

/* CMonster::idleAINormal(float, CLevel&, bool) */

undefined8 CMonster::idleAINormal(float param_1,CLevel *param_2,bool param_3)

{
  uint uVar1;
  char cVar2;
  int iVar3;
  CPositionableObject *this;
  long lVar4;
  byte in_DL;
  long lVar5;
  undefined8 uVar6;
  CDynamicPropertyFile *pCVar7;
  float fVar8;
  float fVar9;
  float in_XMM1_Da;
  float fVar10;

  param_2[0x321] = (CLevel)0x0;
  iVar3 = CCharacter::alignment((CCharacter *)param_2);
  if (((iVar3 == 0) ||
      (cVar2 = CCharacter::isPetNearDeath((CCharacter *)param_2),
      uVar1 = KSETTINGS_PLAYER_UNTARGETABLE, cVar2 != '\0')) || (*(int *)(param_2 + 0x710) != 1)) {
LAB_008e02d4:
    iVar3 = CCharacter::alignment((CCharacter *)param_2);
    if (((iVar3 != 0) &&
        (cVar2 = CCharacter::isPetNearDeath((CCharacter *)param_2),
        uVar1 = KSETTINGS_PLAYER_UNTARGETABLE, cVar2 == '\0')) && (*(int *)(param_2 + 0x710) != 1))
    {
      lVar4 = *(long *)(param_2 + 0x68);
      lVar5 = 0;
      if (lVar4 != 0) {
        lVar5 = *(long *)(lVar4 + 0x18);
      }
      if (*(int *)(*(long *)(lVar5 + 0x220) + 0x38d0) == 1) {
        pCVar7 = (CDynamicPropertyFile *)0x0;
        if (lVar4 != 0) {
          lVar4 = CMasterResourceManager::getSingleton();
          pCVar7 = *(CDynamicPropertyFile **)(lVar4 + 0x90);
        }
        iVar3 = CDynamicPropertyFile::GetInt(pCVar7,uVar1);
        if (iVar3 == 0) {
          *(undefined8 *)(param_2 + 0x398) = 0;
          selectDefensiveSkill((CMonster *)param_2);
          cVar2 = CCharacter::canCastCurrentSkill
                            ((CBaseUnit *)param_2,SUB81(*(undefined8 *)(param_2 + 0x340),0),false);
          if (cVar2 != '\0') {
            CCharacter::castSkill((longlong)param_2);
            return 1;
          }
        }
      }
    }
    return 0;
  }
  lVar4 = *(long *)(param_2 + 0x68);
  lVar5 = 0;
  if (lVar4 != 0) {
    lVar5 = *(long *)(lVar4 + 0x18);
  }
  if (*(int *)(*(long *)(lVar5 + 0x220) + 0x38d0) != 1) goto LAB_008e02d4;
  pCVar7 = (CDynamicPropertyFile *)0x0;
  if (lVar4 != 0) {
    lVar4 = CMasterResourceManager::getSingleton();
    pCVar7 = *(CDynamicPropertyFile **)(lVar4 + 0x90);
  }
  iVar3 = CDynamicPropertyFile::GetInt(pCVar7,uVar1);
  if (iVar3 != 0) goto LAB_008e02d4;
  if (*(long *)(param_2 + 0x640) != 0) {
    cVar2 = CCharacter::attachesToMaster((CCharacter *)param_2);
    uVar6 = 1;
    if (cVar2 != '\0') goto LAB_008e036b;
  }
  uVar6 = 0;
LAB_008e036b:
  this = (CPositionableObject *)CCharacter::calculateTargetInSight((CCharacter *)param_2,7,uVar6);
  if (this == (CPositionableObject *)0x0) {
    if (*(long *)(param_2 + 0x398) == 0) {
      cVar2 = hasDefensiveSkill((CMonster *)param_2);
      if ((cVar2 == '\0') || (iVar3 = UTILITIES::randomIntegerBetweenVolatile(0,100), 0x22 < iVar3))
      {
        selectOffensiveSkill((CMonster *)param_2,false);
      }
      else {
        selectDefensiveSkill((CMonster *)param_2);
      }
    }
  }
  else {
    cVar2 = hasDefensiveSkill((CMonster *)param_2);
    if ((cVar2 == '\0') || (iVar3 = UTILITIES::randomIntegerBetweenVolatile(0,100), 0x22 < iVar3)) {
      selectOffensiveSkill((CMonster *)param_2,false);
    }
    else {
      selectDefensiveSkill((CMonster *)param_2);
    }
    cVar2 = CCharacter::canCastCurrentSkill((CBaseUnit *)param_2,SUB81(this,0),false);
    if (cVar2 != '\0') {
      CCharacter::setTarget((CCharacter *)param_2,(CCharacter *)this);
      CCharacter::stopPathing((CCharacter *)param_2);
      (**(code **)(*(long *)param_2 + 0x348))(param_2,0xd);
      (**(code **)(*(long *)param_2 + 0x358))(param_1,param_2,in_DL ^ 1);
      return 1;
    }
  }
  if (*(long *)(param_2 + 0x640) == 0) {
    if (this == (CPositionableObject *)0x0) {
      return 0;
    }
  }
  else {
    if (this == (CPositionableObject *)0x0) {
      return 0;
    }
    cVar2 = CBaseUnit::ISA((CBaseUnit *)param_2,0xa9);
    if (cVar2 == '\0') {
      fVar8 = (float)CPositionableObject::getPosition(this,true);
      fVar10 = in_XMM1_Da;
      fVar9 = (float)CPositionableObject::getPosition
                               (*(CPositionableObject **)(param_2 + 0x640),true);
      if (DAT_00fa4814 <
          SQRT((fVar9 - fVar8) * (fVar9 - fVar8) + DAT_00fa47f8 +
               (fVar10 - in_XMM1_Da) * (fVar10 - in_XMM1_Da))) {
        return 0;
      }
    }
  }
  cVar2 = CCharacter::isEnemy((CCharacter *)param_2,(CCharacter *)this);
  if (cVar2 == '\0') {
    return 0;
  }
  cVar2 = (**(code **)(*(long *)param_2 + 0x3f8))(param_2);
  if (cVar2 == '\0') {
    return 0;
  }
  CCharacter::stopPathing((CCharacter *)param_2);
  (**(code **)(*(long *)param_2 + 0x348))(param_2,4);
  CCharacter::setTarget((CCharacter *)param_2,(CCharacter *)this);
  if (*(CSoundBank **)(param_2 + 0x298) != (CSoundBank *)0x0) {
    CSoundBank::playSample
              (*(CSoundBank **)(param_2 + 0x298),0xd,*(SceneNode **)(param_2 + 0x58),0.0,0.0,false);
    return 1;
  }
  return 1;
}

/* address=008e06c0
   symbol=CMonster::idleAIResurrecter */

/* CMonster::idleAIResurrecter(float, CLevel&, bool) */

void CMonster::idleAIResurrecter(float param_1,CLevel *param_2,bool param_3)

{
  idleAINormal(param_1,param_2,param_3);
  return;
}

/* address=008e06d0
   symbol=CMonster::idleAIDefender */

/* CMonster::idleAIDefender(float, CLevel&, bool) */

void CMonster::idleAIDefender(float param_1,CLevel *param_2,bool param_3)

{
  idleAINormal(param_1,param_2,param_3);
  return;
}

/* address=008e06e0
   symbol=CMonster::idleAICircler */

/* CMonster::idleAICircler(float, CLevel&, bool) */

undefined8 CMonster::idleAICircler(float param_1,CLevel *param_2,bool param_3)

{
  uint uVar1;
  char cVar2;
  int iVar3;
  long lVar4;
  CPositionableObject *this;
  byte in_DL;
  undefined8 uVar5;
  undefined7 in_register_00000031;
  CDynamicPropertyFile *this_00;
  float fVar6;
  float fVar7;
  float fVar8;
  float in_XMM1_Da;

  param_2[0x321] = (CLevel)0x0;
  iVar3 = CCharacter::alignment((CCharacter *)param_2);
  if (iVar3 == 0) {
    return 0;
  }
  cVar2 = CCharacter::isPetNearDeath((CCharacter *)param_2);
  uVar1 = KSETTINGS_PLAYER_UNTARGETABLE;
  if (cVar2 != '\0') {
    return 0;
  }
  this_00 = (CDynamicPropertyFile *)0x0;
  if (*(long *)(param_2 + 0x68) != 0) {
    lVar4 = CMasterResourceManager::getSingleton();
    this_00 = *(CDynamicPropertyFile **)(lVar4 + 0x90);
  }
  iVar3 = CDynamicPropertyFile::GetInt(this_00,uVar1);
  if (iVar3 != 0) {
    return 0;
  }
  if (*(long *)(param_2 + 0x640) == 0) {
LAB_008e08a0:
    uVar5 = 0;
  }
  else {
    cVar2 = CCharacter::attachesToMaster((CCharacter *)param_2);
    uVar5 = 1;
    if (cVar2 == '\0') goto LAB_008e08a0;
  }
  this = (CPositionableObject *)CCharacter::calculateTargetInSight((CCharacter *)param_2,7,uVar5);
  if (*(long *)(param_2 + 0x640) == 0) {
    if (this != (CPositionableObject *)0x0) {
LAB_008e08b5:
      CCharacter::setTarget((CCharacter *)param_2,(CCharacter *)this);
      cVar2 = (**(code **)(*(long *)param_2 + 0x3f8))(param_2);
      if ((cVar2 != '\0') && (cVar2 = CCharacter::inAttackRange(param_2), cVar2 != '\0')) {
        CCharacter::stopPathing((CCharacter *)param_2);
        (**(code **)(*(long *)param_2 + 0x348))(param_2,4);
        CCharacter::setTarget((CCharacter *)param_2,(CCharacter *)this);
        if (*(CSoundBank **)(param_2 + 0x298) != (CSoundBank *)0x0) {
          CSoundBank::playSample
                    (*(CSoundBank **)(param_2 + 0x298),0xd,*(SceneNode **)(param_2 + 0x58),0.0,0.0,
                     false);
          return 1;
        }
        return 1;
      }
      cVar2 = hasDefensiveSkill((CMonster *)param_2);
      if ((cVar2 == '\0') || (iVar3 = UTILITIES::randomIntegerBetweenVolatile(0,100), 9 < iVar3)) {
        selectOffensiveSkill((CMonster *)param_2,false);
      }
      else {
        selectDefensiveSkill((CMonster *)param_2);
      }
      if ((*(long *)(param_2 + 0x398) != 0) &&
         (cVar2 = CCharacter::canCastCurrentSkill((CBaseUnit *)param_2,SUB81(this,0),false),
         cVar2 != '\0')) {
        CCharacter::setTarget((CCharacter *)param_2,(CCharacter *)this);
        (**(code **)(*(long *)param_2 + 0x348))(param_2,0xd);
        CCharacter::stopPathing((CCharacter *)param_2);
        (**(code **)(*(long *)param_2 + 0x358))(param_1,param_2,in_DL ^ 1);
        return 1;
      }
      (**(code **)(*(long *)param_2 + 0x348))(param_2,4);
      iVar3 = UTILITIES::randomIntegerBetweenVolatile(0,100);
      if (0x13 < iVar3) {
        return 0;
      }
      (**(code **)(*(long *)param_2 + 0x348))(param_2);
      CPositionableObject::getPosition(this,false);
      fVar8 = DAT_00fa86d4 + in_XMM1_Da;
      CPositionableObject::getPosition(this,true);
      fVar8 = (float)UTILITIES::randomBetweenVolatile(in_XMM1_Da - DAT_00fa86d4,fVar8);
      fVar6 = (float)CPositionableObject::getPosition(this,false);
      fVar6 = DAT_00fa86d4 + fVar6;
      fVar7 = (float)CPositionableObject::getPosition(this,true);
      fVar6 = (float)UTILITIES::randomBetweenVolatile(fVar7 - DAT_00fa86d4,fVar6);
      CCharacter::setDestination
                ((CCharacter *)param_2,(CLevel *)CONCAT71(in_register_00000031,param_3),fVar6,fVar8)
      ;
      return 1;
    }
  }
  else if (this != (CPositionableObject *)0x0) {
    fVar6 = (float)CPositionableObject::getPosition(this,true);
    fVar8 = in_XMM1_Da;
    fVar7 = (float)CPositionableObject::getPosition(*(CPositionableObject **)(param_2 + 0x640),true)
    ;
    in_XMM1_Da = (fVar8 - in_XMM1_Da) * (fVar8 - in_XMM1_Da);
    if (SQRT((fVar7 - fVar6) * (fVar7 - fVar6) + DAT_00fa47f8 + in_XMM1_Da) <= DAT_00fa4814)
    goto LAB_008e08b5;
  }
  if (*(long *)(param_2 + 0x398) != 0) {
    return 0;
  }
  cVar2 = hasDefensiveSkill((CMonster *)param_2);
  if ((cVar2 != '\0') && (iVar3 = UTILITIES::randomIntegerBetweenVolatile(0,100), iVar3 < 10)) {
    selectDefensiveSkill((CMonster *)param_2);
    return 0;
  }
  selectOffensiveSkill((CMonster *)param_2,false);
  return 0;
}

/* address=008e0b90
   symbol=CMonster::idleAIRangedCaster */

/* CMonster::idleAIRangedCaster(float, CLevel&, bool) */

undefined8 CMonster::idleAIRangedCaster(float param_1,CLevel *param_2,bool param_3)

{
  uint uVar1;
  char cVar2;
  int iVar3;
  long lVar4;
  CPositionableObject *this;
  byte in_DL;
  undefined8 uVar5;
  CDynamicPropertyFile *this_00;
  float fVar6;
  float fVar7;
  float in_XMM1_Da;
  float fVar8;

  param_2[0x321] = (CLevel)0x0;
  iVar3 = CCharacter::alignment((CCharacter *)param_2);
  if (iVar3 == 0) {
    return 0;
  }
  cVar2 = CCharacter::isPetNearDeath((CCharacter *)param_2);
  uVar1 = KSETTINGS_PLAYER_UNTARGETABLE;
  if (cVar2 != '\0') {
    return 0;
  }
  this_00 = (CDynamicPropertyFile *)0x0;
  if (*(long *)(param_2 + 0x68) != 0) {
    lVar4 = CMasterResourceManager::getSingleton();
    this_00 = *(CDynamicPropertyFile **)(lVar4 + 0x90);
  }
  iVar3 = CDynamicPropertyFile::GetInt(this_00,uVar1);
  if (iVar3 != 0) {
    return 0;
  }
  if (*(long *)(param_2 + 0x640) == 0) {
LAB_008e0d10:
    uVar5 = 0;
  }
  else {
    cVar2 = CCharacter::attachesToMaster((CCharacter *)param_2);
    uVar5 = 1;
    if (cVar2 == '\0') goto LAB_008e0d10;
  }
  this = (CPositionableObject *)CCharacter::calculateTargetInSight((CCharacter *)param_2,7,uVar5);
  if (*(long *)(param_2 + 0x640) == 0) {
    if (this != (CPositionableObject *)0x0) {
LAB_008e0d25:
      CCharacter::setTarget((CCharacter *)param_2,(CCharacter *)this);
      cVar2 = (**(code **)(*(long *)param_2 + 0x3f8))(param_2);
      if ((cVar2 != '\0') && (cVar2 = CCharacter::inAttackRange(param_2), cVar2 != '\0')) {
        CCharacter::stopPathing((CCharacter *)param_2);
        (**(code **)(*(long *)param_2 + 0x348))(param_2,4);
        CCharacter::setTarget((CCharacter *)param_2,(CCharacter *)this);
        if (*(CSoundBank **)(param_2 + 0x298) != (CSoundBank *)0x0) {
          CSoundBank::playSample
                    (*(CSoundBank **)(param_2 + 0x298),0xd,*(SceneNode **)(param_2 + 0x58),0.0,0.0,
                     false);
          return 1;
        }
        return 1;
      }
      cVar2 = hasDefensiveSkill((CMonster *)param_2);
      if ((cVar2 == '\0') || (iVar3 = UTILITIES::randomIntegerBetweenVolatile(0,100), 0x22 < iVar3))
      {
        selectOffensiveSkill((CMonster *)param_2,false);
      }
      else {
        selectDefensiveSkill((CMonster *)param_2);
      }
      if ((*(long *)(param_2 + 0x398) != 0) &&
         (cVar2 = CCharacter::canCastCurrentSkill((CBaseUnit *)param_2,SUB81(this,0),false),
         cVar2 != '\0')) {
        CCharacter::setTarget((CCharacter *)param_2,(CCharacter *)this);
        (**(code **)(*(long *)param_2 + 0x348))(param_2,0xd);
        CCharacter::stopPathing((CCharacter *)param_2);
        (**(code **)(*(long *)param_2 + 0x358))(param_1,param_2,in_DL ^ 1);
        return 1;
      }
      iVar3 = UTILITIES::randomIntegerBetweenVolatile(0,100);
      if (9 < iVar3) {
        return 0;
      }
      (**(code **)(*(long *)param_2 + 0x348))(param_2,10);
      return 1;
    }
  }
  else if (this != (CPositionableObject *)0x0) {
    fVar6 = (float)CPositionableObject::getPosition(this,true);
    fVar8 = in_XMM1_Da;
    fVar7 = (float)CPositionableObject::getPosition(*(CPositionableObject **)(param_2 + 0x640),true)
    ;
    if (SQRT((fVar7 - fVar6) * (fVar7 - fVar6) + DAT_00fa47f8 +
             (fVar8 - in_XMM1_Da) * (fVar8 - in_XMM1_Da)) <= DAT_00fa4814) goto LAB_008e0d25;
  }
  if (*(long *)(param_2 + 0x398) != 0) {
    return 0;
  }
  cVar2 = hasDefensiveSkill((CMonster *)param_2);
  if ((cVar2 != '\0') && (iVar3 = UTILITIES::randomIntegerBetweenVolatile(0,100), iVar3 < 0x23)) {
    selectDefensiveSkill((CMonster *)param_2);
    return 0;
  }
  selectOffensiveSkill((CMonster *)param_2,false);
  return 0;
}

/* address=008e0eb0
   symbol=CMonster::idleAIRangedDefender */

/* CMonster::idleAIRangedDefender(float, CLevel&, bool) */

undefined8 CMonster::idleAIRangedDefender(float param_1,CLevel *param_2,bool param_3)

{
  uint uVar1;
  char cVar2;
  int iVar3;
  long lVar4;
  CPositionableObject *this;
  undefined8 uVar5;
  CDynamicPropertyFile *this_00;
  float fVar6;
  float fVar7;
  float in_XMM1_Da;
  float fVar8;

  param_2[0x321] = (CLevel)0x0;
  iVar3 = CCharacter::alignment((CCharacter *)param_2);
  if (iVar3 == 0) {
    return 0;
  }
  cVar2 = CCharacter::isPetNearDeath((CCharacter *)param_2);
  uVar1 = KSETTINGS_PLAYER_UNTARGETABLE;
  if (cVar2 != '\0') {
    return 0;
  }
  this_00 = (CDynamicPropertyFile *)0x0;
  if (*(long *)(param_2 + 0x68) != 0) {
    lVar4 = CMasterResourceManager::getSingleton();
    this_00 = *(CDynamicPropertyFile **)(lVar4 + 0x90);
  }
  iVar3 = CDynamicPropertyFile::GetInt(this_00,uVar1);
  if (iVar3 != 0) {
    return 0;
  }
  if (*(long *)(param_2 + 0x640) == 0) {
LAB_008e1028:
    uVar5 = 0;
  }
  else {
    cVar2 = CCharacter::attachesToMaster((CCharacter *)param_2);
    uVar5 = 1;
    if (cVar2 == '\0') goto LAB_008e1028;
  }
  this = (CPositionableObject *)CCharacter::calculateTargetInSight((CCharacter *)param_2,7,uVar5);
  if (*(long *)(param_2 + 0x640) == 0) {
    if (this != (CPositionableObject *)0x0) goto LAB_008e1035;
  }
  else if (this != (CPositionableObject *)0x0) {
    cVar2 = CBaseUnit::ISA((CBaseUnit *)param_2,0xa9);
    if (cVar2 == '\0') {
      fVar6 = (float)CPositionableObject::getPosition(this,true);
      fVar8 = in_XMM1_Da;
      fVar7 = (float)CPositionableObject::getPosition
                               (*(CPositionableObject **)(param_2 + 0x640),true);
      if (DAT_00fa4814 <
          SQRT((fVar7 - fVar6) * (fVar7 - fVar6) + DAT_00fa47f8 +
               (fVar8 - in_XMM1_Da) * (fVar8 - in_XMM1_Da))) goto LAB_008e1006;
    }
LAB_008e1035:
    CCharacter::setTarget((CCharacter *)param_2,(CCharacter *)this);
    cVar2 = (**(code **)(*(long *)param_2 + 0x3f8))(param_2);
    if ((cVar2 != '\0') && (cVar2 = CCharacter::inAttackRange(param_2), cVar2 != '\0')) {
      CCharacter::stopPathing((CCharacter *)param_2);
      (**(code **)(*(long *)param_2 + 0x348))(param_2,4);
      CCharacter::setTarget((CCharacter *)param_2,(CCharacter *)this);
      if (*(CSoundBank **)(param_2 + 0x298) != (CSoundBank *)0x0) {
        CSoundBank::playSample
                  (*(CSoundBank **)(param_2 + 0x298),0xd,*(SceneNode **)(param_2 + 0x58),0.0,0.0,
                   false);
        return 1;
      }
      return 1;
    }
    selectDefensiveSkill((CMonster *)param_2);
    if ((*(long *)(param_2 + 0x398) != 0) &&
       (cVar2 = CCharacter::canCastCurrentSkill((CBaseUnit *)param_2,false,false), cVar2 != '\0')) {
      CCharacter::castSkill((longlong)param_2);
      return 1;
    }
    iVar3 = UTILITIES::randomIntegerBetweenVolatile(0,100);
    if (9 < iVar3) {
      return 0;
    }
    (**(code **)(*(long *)param_2 + 0x348))(param_2,10);
    return 1;
  }
LAB_008e1006:
  if (*(long *)(param_2 + 0x398) != 0) {
    return 0;
  }
  selectDefensiveSkill((CMonster *)param_2);
  return 0;
}

/* address=008e1390
   symbol=CMonster::fidgetAI */

/* WARNING: Removing unreachable block (ram,0x008e1574) */
/* CMonster::fidgetAI(float, CLevel&) */

void __thiscall CMonster::fidgetAI(CMonster *this,float param_1,CLevel *param_2)

{
  int *piVar1;
  int iVar2;
  char cVar3;
  float fVar4;
  float fVar5;
  float in_XMM1_Da;
  float fVar6;
  string local_38 [16];
  long local_28;
  allocator local_1a;
  allocator local_19 [9];

  cVar3 = CCharacter::alive((CCharacter *)this);
  if (cVar3 != '\0') {
                    /* try { // try from 008e13c2 to 008e13c6 has its CatchHandler @ 008e156b */
    std::string::string((string *)&local_28,"FIDGET",local_19);
                    /* try { // try from 008e13d1 to 008e13d5 has its CatchHandler @ 008e1570 */
    cVar3 = CGenericModel::animationPlayingSubstring
                      (*(CGenericModel **)(this + 0x200),(string *)&local_28);
    if ((allocator *)(local_28 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_28 + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_28 + -0x18));
      }
    }
    if (cVar3 == '\0') {
      (**(code **)(*(long *)this + 0x348))(this,2);
    }
    if ((*(long *)(this + 0x640) != 0) &&
       (cVar3 = CBaseUnit::ISA((CBaseUnit *)this,0xa9), cVar3 == '\0')) {
      fVar4 = (float)CPositionableObject::getPosition((CPositionableObject *)this,true);
      fVar6 = in_XMM1_Da;
      fVar5 = (float)CPositionableObject::getPosition(*(CPositionableObject **)(this + 0x640),true);
      if (DAT_00fa8730 <
          SQRT((fVar5 - fVar4) * (fVar5 - fVar4) + DAT_00fa47f8 +
               (fVar6 - in_XMM1_Da) * (fVar6 - in_XMM1_Da))) {
        (**(code **)(*(long *)this + 0x348))(this,2);
                    /* try { // try from 008e14d3 to 008e14d7 has its CatchHandler @ 008e1572 */
        std::string::string(local_38,"IDLE",&local_1a);
                    /* try { // try from 008e14fb to 008e14ff has its CatchHandler @ 008e1558 */
        CCharacter::blendAnimation
                  ((string *)this,SUB81(local_38,0),DAT_00fa480c,DAT_00fa47fc,DAT_00fa8760);
                    /* try { // try from 008e1503 to 008e1507 has its CatchHandler @ 008e1572 */
        std::string::~string(local_38);
      }
    }
  }
  return;
}

/* address=008e1580
   symbol=CMonster::jumpDownAI */

/* WARNING: Removing unreachable block (ram,0x008e194f) */
/* WARNING: Removing unreachable block (ram,0x008e1972) */
/* WARNING: Removing unreachable block (ram,0x008e195d) */
/* CMonster::jumpDownAI(float, CLevel&) */

void __thiscall CMonster::jumpDownAI(CMonster *this,float param_1,CLevel *param_2)

{
  int *piVar1;
  float fVar2;
  int iVar3;
  char cVar4;
  CPath *this_00;
  float fVar5;
  float fVar6;
  undefined8 uVar7;
  float fVar8;
  undefined8 local_78;
  float local_70;
  undefined8 local_68;
  undefined8 local_58;
  long local_48 [2];
  long local_38 [2];
  long local_28;
  allocator local_1b;
  allocator local_1a;
  allocator local_19 [9];

  fVar2 = *(float *)(this + 0x678);
  local_58 = CPath::GetPoint(*(CPath **)(this + 0x670),1);
  local_68 = CPath::GetPoint(*(CPath **)(this + 0x670),0);
  this_00 = *(CPath **)(this + 0x670);
  fVar5 = *(float *)(this + 0x678);
  if (fVar5 < DAT_00fa4810 * *(float *)(this_00 + 0x18)) {
    local_78 = CPath::GetPoint(this_00,2);
    local_70 = fVar5;
    CCharacter::turnTowardPosition((CCharacter *)this,(Vector3 *)&local_78,param_1);
    fVar5 = *(float *)(this + 0x678);
    this_00 = *(CPath **)(this + 0x670);
  }
  fVar5 = param_1 * *(float *)(this + 0x67c) + fVar5;
  *(float *)(this + 0x678) = fVar5;
  fVar8 = *(float *)(this_00 + 0x18);
  if (fVar5 < fVar8) {
                    /* try { // try from 008e17e2 to 008e17e6 has its CatchHandler @ 008e194a */
    std::string::string((string *)&local_28,"JUMP_DOWN",local_19);
                    /* try { // try from 008e17f1 to 008e17f5 has its CatchHandler @ 008e1948 */
    fVar6 = (float)CGenericModel::getAnimationLengthSeconds
                             (*(CGenericModel **)(this + 0x200),(string *)&local_28);
    if ((allocator *)(local_28 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_28 + -8);
      iVar3 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar3 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_28 + -0x18));
      }
    }
    CGenericModel::setAnimationTime
              (*(CGenericModel **)(this + 0x200),fVar6 * (fVar5 / fVar8) - param_1);
    this_00 = *(CPath **)(this + 0x670);
    fVar5 = *(float *)(this + 0x678);
    fVar8 = *(float *)(this_00 + 0x18);
  }
  if (fVar8 <= fVar5) {
    if (fVar8 <= fVar2) {
      this[0x680] = (CMonster)0x0;
                    /* try { // try from 008e1681 to 008e1685 has its CatchHandler @ 008e196f */
      std::string::string((string *)local_48,"IDLE",&local_1b);
                    /* try { // try from 008e1690 to 008e1694 has its CatchHandler @ 008e1935 */
      cVar4 = CGenericModel::animationPlayingSubstring
                        (*(CGenericModel **)(this + 0x200),(string *)local_48);
      if ((allocator *)(local_48[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_48[0] + -8);
        iVar3 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar3 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
        }
      }
      if (cVar4 == '\0') {
        return;
      }
      (**(code **)(*(long *)this + 0x348))(this,4);
      return;
    }
    *(float *)(this + 0x678) = fVar8;
    if (*(CSoundBank **)(this + 0x298) != (CSoundBank *)0x0) {
      CSoundBank::playSample
                (*(CSoundBank **)(this + 0x298),0x11,*(SceneNode **)(this + 0x58),0.0,0.0,false);
    }
                    /* try { // try from 008e1712 to 008e1716 has its CatchHandler @ 008e196b */
    std::string::string((string *)local_38,"IDLE",&local_1a);
    fVar8 = DAT_00fa47fc;
                    /* try { // try from 008e1732 to 008e1736 has its CatchHandler @ 008e196d */
    CCharacter::queueBlendAnimation
              ((CCharacter *)this,(string *)local_38,true,DAT_00fa86e8,DAT_00fa47fc);
    if ((allocator *)(local_38[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_38[0] + -8);
      iVar3 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar3 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_38[0] + -0x18));
      }
    }
    this_00 = *(CPath **)(this + 0x670);
    fVar5 = *(float *)(this + 0x678);
  }
  uVar7 = CPath::GetSplinePositionAtDistance(this_00,fVar5);
  *(undefined8 *)(this + 0x84) = uVar7;
  *(float *)(this + 0x8c) = fVar8;
  CPositionableObject::setPosition((CPositionableObject *)this,(Vector3 *)(this + 0x84));
  return;
}

/* address=008e2ae0
   symbol=CMonster::unitInit */

/* WARNING: Removing unreachable block (ram,0x008e2baf) */
/* CMonster::unitInit(CDataGroup*, bool) */

void __thiscall CMonster::unitInit(CMonster *this,CDataGroup *param_1,bool param_2)

{
  int *piVar1;
  int iVar2;
  long lVar3;
  undefined4 uVar4;
  long local_28;
  allocator local_19;

  CCharacter::unitInit((CCharacter *)this,param_1,param_2);
                    /* try { // try from 008e2b0e to 008e2b12 has its CatchHandler @ 008e2baa */
  std::wstring::wstring((wstring_conflict *)&local_28,L"AI_ATTACKCOOLDOWN",&local_19);
                    /* try { // try from 008e2b1c to 008e2b20 has its CatchHandler @ 008e2b97 */
  uVar4 = CDataGroup::GetDataValue(param_1,(wstring_conflict *)&local_28,0.0);
  *(undefined4 *)(this + 0x7ec) = uVar4;
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
  lVar3 = (**(code **)(*(long *)this + 0x1e0))(this);
  if (lVar3 != 0) {
    lVar3 = (**(code **)(*(long *)this + 0x1e0))(this);
    *(undefined4 *)(lVar3 + 0x24c) = 0x3c23d70a;
  }
  return;
}

/* address=008e2bc0
   symbol=CMonster::~CMonster */

/* WARNING: Removing unreachable block (ram,0x008e2cba) */
/* CMonster::~CMonster() */

void __thiscall CMonster::~CMonster(CMonster *this)

{
  allocator *paVar1;
  int *piVar2;
  int iVar3;

  *(undefined ***)this = &PTR__CMonster_00fd2690;
  *(undefined ***)(this + 0x1d8) = &PTR__CMonster_00fd2ac0;
  *(undefined ***)(this + 0x1e0) = &PTR__CMonster_00fd2b10;
  *(undefined ***)(this + 0x780) = &PTR__CRandomizer_00fc8a30;
  if (*(void **)(this + 0x7c0) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x7c0));
    *(undefined8 *)(this + 0x7c0) = 0;
  }
  if (*(void **)(this + 0x7a8) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x7a8));
    *(undefined8 *)(this + 0x7a8) = 0;
  }
  if (*(void **)(this + 0x790) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x790));
    *(undefined8 *)(this + 0x790) = 0;
  }
                    /* try { // try from 008e2c4b to 008e2c4f has its CatchHandler @ 008e2c94 */
  CRunicCore::~CRunicCore((CRunicCore *)(this + 0x780));
  paVar1 = (allocator *)(*(long *)(this + 0x778) + -0x18);
  if (paVar1 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar2 = (int *)(*(long *)(this + 0x778) + -8);
    iVar3 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar1);
    }
  }
  CCharacter::~CCharacter((CCharacter *)this);
  return;
}

/* address=008e2cd0
   symbol=CMonster::~CMonster */

/* non-virtual thunk to CMonster::~CMonster() */

void __thiscall CMonster::~CMonster(CMonster *this)

{
  ~CMonster(this + -0x1e0);
  return;
}

/* address=008e2ce0
   symbol=CMonster::~CMonster */

/* non-virtual thunk to CMonster::~CMonster() */

void __thiscall CMonster::~CMonster(CMonster *this)

{
  ~CMonster(this + -0x1d8);
  return;
}

/* address=008e2cf0
   symbol=CMonster::~CMonster */

/* non-virtual thunk to CMonster::~CMonster() */

void __thiscall CMonster::~CMonster(CMonster *this)

{
  ~CMonster(this + -0x1e0);
  return;
}

/* address=008e2d00
   symbol=CMonster::~CMonster */

/* non-virtual thunk to CMonster::~CMonster() */

void __thiscall CMonster::~CMonster(CMonster *this)

{
  ~CMonster(this + -0x1d8);
  return;
}

/* address=008e2d10
   symbol=CMonster::~CMonster */

/* CMonster::~CMonster() */

void __thiscall CMonster::~CMonster(CMonster *this)

{
  ~CMonster(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}

/* address=008e2d30
   symbol=CMonster::idleAI */

/* WARNING: Removing unreachable block (ram,0x008e3a16) */
/* WARNING: Removing unreachable block (ram,0x008e39e2) */
/* CMonster::idleAI(float, CLevel&, bool) */

void CMonster::idleAI(float param_1,CLevel *param_2,bool param_3)

{
  int *piVar1;
  long lVar2;
  char cVar3;
  char cVar4;
  uint uVar5;
  int iVar6;
  float *pfVar7;
  CLevel CVar8;
  undefined7 in_register_00000031;
  CLevel *pCVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  ulong local_118;
  float local_110;
  undefined8 local_108;
  float local_100;
  undefined8 local_f8;
  float local_f0;
  undefined8 local_e8;
  float local_e0;
  undefined8 local_d8;
  float local_d0;
  undefined8 local_c8;
  float local_c0;
  undefined8 local_b8;
  float local_b0;
  undefined8 local_a8;
  float local_a0;
  undefined8 local_98;
  float local_90;
  undefined8 local_88;
  float local_80;
  string local_78 [16];
  string local_68 [16];
  string local_58 [16];
  long local_48 [2];
  long local_38;
  allocator local_2d;
  allocator local_2c;
  allocator local_2b;
  allocator local_2a;
  allocator local_29 [9];

  pCVar9 = (CLevel *)CONCAT71(in_register_00000031,param_3);
  cVar3 = (**(code **)(*(long *)param_2 + 0x48))();
  if ((cVar3 == '\0') || (*(long *)(param_2 + 0x750) != 0)) {
switchD_008e3073_default:
    cVar3 = '\0';
  }
  else {
    switch(*(undefined4 *)(param_2 + 0x334)) {
    case 0:
    case 2:
    case 5:
      cVar3 = idleAINormal(param_1,param_2,param_3);
      break;
    case 1:
      cVar3 = idleAIRangedDefender(param_1,param_2,param_3);
      break;
    case 3:
      cVar3 = idleAIRangedCaster(param_1,param_2,param_3);
      break;
    case 4:
      cVar3 = idleAICircler(param_1,param_2,param_3);
      break;
    default:
      goto switchD_008e3073_default;
    }
  }
  cVar4 = CBaseUnit::ISA((CBaseUnit *)param_2,0xa7);
  if (cVar4 != '\0') {
    if (*(int *)(param_2 + 0x330) == 2) {
                    /* try { // try from 008e2ea8 to 008e2eac has its CatchHandler @ 008e3a14 */
      std::wstring::wstring((wstring_conflict *)local_48,L"MIMICIDLE",&local_2a);
                    /* try { // try from 008e2eb3 to 008e2eb7 has its CatchHandler @ 008e3a07 */
      cVar4 = CBaseUnit::hasUnitTheme((CBaseUnit *)param_2,(wstring_conflict *)local_48);
      if ((allocator *)(local_48[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_48[0] + -8);
        iVar6 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar6 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
        }
      }
      if (cVar4 != '\0') {
        return;
      }
    }
    else {
                    /* try { // try from 008e2d9b to 008e2d9f has its CatchHandler @ 008e3a27 */
      std::wstring::wstring((wstring_conflict *)&local_38,L"MIMICIDLE",local_29);
                    /* try { // try from 008e2da6 to 008e2daa has its CatchHandler @ 008e3a29 */
      CBaseUnit::removeUnitTheme((CBaseUnit *)param_2,(wstring_conflict *)&local_38);
      if ((allocator *)(local_38 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
      {
        LOCK();
        piVar1 = (int *)(local_38 + -8);
        iVar6 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar6 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_38 + -0x18));
        }
      }
    }
  }
  if (cVar3 != '\0') {
    return;
  }
  if (((((*(long *)(param_2 + 0x200) != 0) &&
        (cVar3 = (**(code **)(*(long *)param_2 + 0x48))(), cVar3 != '\0')) &&
       (param_2[0x264] == (CLevel)0x0)) &&
      ((*(long *)(param_2 + 0x750) == 0 && (*(int *)(param_2 + 0x330) == 2)))) &&
     (iVar6 = UTILITIES::randomIntegerBetweenVolatile(0,1000), iVar6 < 10)) {
    if (*(float *)(param_2 + 0x284) <= DAT_00fa86e0) {
      return;
    }
                    /* try { // try from 008e2f3d to 008e2f55 has its CatchHandler @ 008e39ca */
    std::string::string(local_58,"FIDGET",&local_2b);
    cVar3 = CGenericModel::animationExistsSubstring(*(CGenericModel **)(param_2 + 0x200),local_58);
                    /* try { // try from 008e2f5f to 008e2f63 has its CatchHandler @ 008e39f2 */
    std::string::~string(local_58);
    if (cVar3 == '\0') {
      return;
    }
                    /* try { // try from 008e2f85 to 008e2f89 has its CatchHandler @ 008e39ed */
    std::string::string(local_68,"FIDGET",&local_2c);
                    /* try { // try from 008e2f94 to 008e2fc0 has its CatchHandler @ 008e39f6 */
    uVar5 = CGenericModel::findRandomAnimation(*(CGenericModel **)(param_2 + 0x200),local_68);
    CGenericModel::blendAnimation
              (*(CGenericModel **)(param_2 + 0x200),uVar5,false,DAT_00fa86e8,DAT_00fa47fc,
               DAT_00fa8760);
                    /* try { // try from 008e2fc4 to 008e2fc8 has its CatchHandler @ 008e39ed */
    std::string::~string(local_68);
                    /* try { // try from 008e2fe1 to 008e2fe5 has its CatchHandler @ 008e39f4 */
    std::string::string(local_78,"IDLE",&local_2d);
                    /* try { // try from 008e3001 to 008e3005 has its CatchHandler @ 008e3a25 */
    CCharacter::queueBlendAnimation((CCharacter *)param_2,local_78,true,DAT_00fa86e8,DAT_00fa47fc);
                    /* try { // try from 008e3009 to 008e300d has its CatchHandler @ 008e39f4 */
    std::string::~string(local_78);
    (**(code **)(*(long *)param_2 + 0x348))(param_2,1);
    if (*(CSoundBank **)(param_2 + 0x298) != (CSoundBank *)0x0) {
      CSoundBank::playSample
                (*(CSoundBank **)(param_2 + 0x298),0xb,*(SceneNode **)(param_2 + 0x58),0.0,0.0,false
                );
    }
    *(undefined4 *)(param_2 + 0x280) = 0;
    *(undefined4 *)(param_2 + 0x284) = 0;
    return;
  }
  fVar10 = (float)CCharacter::walkingSpeed((CCharacter *)param_2);
  fVar12 = 0.0;
  if (fVar10 == 0.0) {
    return;
  }
  if (param_2[0x7f0] != (CLevel)0x0) {
    return;
  }
  if (((*(CBaseUnit **)(param_2 + 0x340) == (CBaseUnit *)0x0) ||
      (cVar3 = CBaseUnit::ISA(*(CBaseUnit **)(param_2 + 0x340),0x1c), cVar3 == '\0')) ||
     ((param_2 != *(CLevel **)(*(long *)(param_2 + 0x340) + 0x340) ||
      (cVar3 = CBaseUnit::ISA((CBaseUnit *)param_2,0x83), cVar3 == '\0')))) {
    if (*(long *)(param_2 + 0x750) != 0) goto LAB_008e2e4f;
    if (param_2[0x264] != (CLevel)0x0) goto LAB_008e2e59;
    fVar12 = DAT_00fa871c;
    fVar10 = (float)UTILITIES::randomBetweenVolatile(0.0,DAT_00fa871c);
    if ((DAT_00fa483c <= fVar10) || (NAN(fVar10) || NAN(DAT_00fa483c))) goto LAB_008e2e59;
    if ((*(long *)(param_2 + 0x640) != 0) &&
       ((cVar3 = (**(code **)(*(long *)param_2 + 0x48))(param_2), cVar3 != '\0' &&
        (cVar3 = CBaseUnit::ISA((CBaseUnit *)param_2,0xa9), cVar3 == '\0')))) {
      local_118 = CPositionableObject::getPosition(*(CPositionableObject **)(param_2 + 0x640),true);
      fVar14 = (float)local_118;
      local_110 = fVar12;
      pfVar7 = (float *)(**(code **)(**(long **)(param_2 + 0x640) + 0x130))();
      fVar14 = *pfVar7 * DAT_00fa86d4 + fVar14;
      fVar11 = DAT_00fa86d4 * pfVar7[2];
      fVar13 = fVar14;
      local_98 = CPositionableObject::getPosition(*(CPositionableObject **)(param_2 + 0x640),true);
      fVar10 = DAT_00fd2b7c;
      fVar15 = fVar13 + DAT_00fd2b7c;
      local_90 = fVar13;
      fVar12 = (float)UTILITIES::randomBetweenVolatile((fVar11 + fVar12) - DAT_00fd2b7c,fVar15);
      local_88 = CPositionableObject::getPosition(*(CPositionableObject **)(param_2 + 0x640),true);
      local_80 = fVar15;
      fVar10 = (float)UTILITIES::randomBetweenVolatile(fVar14 - fVar10,(float)local_88 + fVar10);
      CCharacter::setDestination((CCharacter *)param_2,pCVar9,fVar10,fVar12);
      goto LAB_008e2e59;
    }
    cVar3 = (**(code **)(*(long *)param_2 + 0x48))(param_2);
    fVar10 = DAT_00fa8730;
    if (cVar3 != '\0') {
      fVar12 = (float)UTILITIES::randomBetweenVolatile
                                (*(float *)(param_2 + 0x8c) - DAT_00fa8730,
                                 *(float *)(param_2 + 0x8c) + DAT_00fa8730);
      fVar10 = (float)UTILITIES::randomBetweenVolatile
                                (*(float *)(param_2 + 0x84) - fVar10,
                                 *(float *)(param_2 + 0x84) + fVar10);
      CCharacter::setDestination((CCharacter *)param_2,pCVar9,fVar10,fVar12);
      goto LAB_008e2e59;
    }
  }
  else if (*(long *)(param_2 + 0x750) != 0) {
LAB_008e2e4f:
    CCharacter::updatePathFollowing(SUB81(param_2,0));
    goto LAB_008e2e59;
  }
  CCharacter::stopPathing((CCharacter *)param_2);
LAB_008e2e59:
  if ((((*(long *)(param_2 + 0x640) != 0) &&
       (cVar3 = CCharacter::attachesToMaster((CCharacter *)param_2), cVar3 == '\0')) &&
      (*(long *)(param_2 + 0x750) == 0)) &&
     ((cVar3 = (**(code **)(*(long *)param_2 + 0x48))(param_2), cVar3 != '\0' &&
      (cVar3 = CBaseUnit::ISA((CBaseUnit *)param_2,0xa9), cVar3 == '\0')))) {
    lVar2 = *(long *)(param_2 + 0x640);
    CVar8 = (CLevel)0x0;
    if (*(char *)(lVar2 + 0x321) != '\0') {
      CVar8 = (CLevel)(*(float *)(lVar2 + 0x28c) <= *(float *)(lVar2 + 0x290) &&
                      *(float *)(lVar2 + 0x290) != *(float *)(lVar2 + 0x28c));
    }
    param_2[0x321] = CVar8;
    fVar10 = fVar12;
    if (((*(int *)(param_2 + 0x710) != 0) && (*(CCharacter **)(lVar2 + 0x340) != (CCharacter *)0x0))
       && ((cVar3 = CCharacter::isEnemy((CCharacter *)param_2,*(CCharacter **)(lVar2 + 0x340)),
           fVar10 = fVar12, cVar3 != '\0' &&
           (cVar3 = CCharacter::isPetNearDeath((CCharacter *)param_2), fVar10 = fVar12,
           cVar3 == '\0')))) {
      local_b8 = CPositionableObject::getPosition
                           (*(CPositionableObject **)(*(long *)(param_2 + 0x640) + 0x340),true);
      local_b0 = fVar12;
      local_a8 = CPositionableObject::getPosition(*(CPositionableObject **)(param_2 + 0x640),true);
      fVar10 = (float)local_a8 - (float)local_b8;
      local_110 = fVar12 - local_b0;
      local_118 = (ulong)(uint)fVar10;
      local_a0 = fVar12;
      fVar12 = (float)Ogre::Vector3::length((Vector3 *)&local_118);
      if ((fVar12 <= DAT_00fa8730) && (!NAN(fVar12) && !NAN(DAT_00fa8730))) {
        CCharacter::setTarget
                  ((CCharacter *)param_2,*(CCharacter **)(*(long *)(param_2 + 0x640) + 0x340));
        (**(code **)(*(long *)param_2 + 0x348))(param_2,4);
        return;
      }
    }
    local_d8 = CPositionableObject::getPosition((CPositionableObject *)param_2,true);
    local_d0 = fVar10;
    local_c8 = CPositionableObject::getPosition(*(CPositionableObject **)(param_2 + 0x640),true);
    fVar12 = (float)local_c8 - (float)local_d8;
    fVar13 = (fVar10 - local_d0) * (fVar10 - local_d0);
    fVar12 = SQRT(fVar12 * fVar12 + 0.0 + fVar13);
    if (fVar12 <= DAT_00fce4b0) {
      if (((fVar12 <= DAT_00fa8730) && (!NAN(fVar12) && !NAN(DAT_00fa8730))) &&
         (*(char *)(*(long *)(param_2 + 0x640) + 0x264) == '\0')) {
        param_2[0x321] = (CLevel)0x0;
      }
    }
    else {
      param_2[0x321] = (CLevel)0x1;
    }
    local_c0 = fVar10;
    if (DAT_00fc6760 < fVar12) {
      fVar12 = (float)CCharacter::walkingSpeed((CCharacter *)param_2);
      fVar13 = 0.0;
      if (0.0 < fVar12) {
        CCharacter::teleportToMaster(DAT_00fb2bd8);
      }
    }
    cVar3 = CCharacter::isPetNearDeath((CCharacter *)param_2);
    if (cVar3 != '\0') {
      param_2[0x321] = (CLevel)0x1;
    }
    if (param_2[0x264] == (CLevel)0x0) {
      local_108 = CPositionableObject::getPosition((CPositionableObject *)param_2,true);
      local_100 = fVar13;
      local_f8 = CPositionableObject::getPosition(*(CPositionableObject **)(param_2 + 0x640),true);
      fVar10 = (float)local_f8 - (float)local_108;
      fVar12 = fVar13 - local_100;
      local_f0 = fVar13;
    }
    else {
      local_e8 = CPositionableObject::getPosition(*(CPositionableObject **)(param_2 + 0x640),true);
      fVar10 = (float)local_e8 - *(float *)(param_2 + 0x228);
      fVar12 = fVar13 - *(float *)(param_2 + 0x230);
      local_e0 = fVar13;
    }
    fVar12 = fVar12 * fVar12;
    fVar10 = SQRT(fVar10 * fVar10 + 0.0 + fVar12);
    iVar6 = rand();
    if (((iVar6 % 1000 < 100) || (DAT_00fa8730 < fVar10)) ||
       (cVar3 = CCharacter::isPetNearDeath((CCharacter *)param_2), cVar3 != '\0')) {
      cVar3 = CCharacter::isPetNearDeath((CCharacter *)param_2);
      if (cVar3 != '\0') {
        (**(code **)(*(long *)param_2 + 0x348))(param_2,10);
      }
      cVar3 = CCharacter::isPetNearDeath((CCharacter *)param_2);
      if (((cVar3 != '\0') && (param_2[0x264] == (CLevel)0x0)) ||
         ((DAT_00fa8730 < fVar10 && (fVar12 = fVar10, DAT_00fce520 < *(float *)(param_2 + 0x278)))))
      {
        param_2[0x321] = (CLevel)0x1;
        local_118 = CPositionableObject::getPosition
                              (*(CPositionableObject **)(param_2 + 0x640),true);
        fVar14 = (float)local_118;
        local_110 = fVar12;
        pfVar7 = (float *)(**(code **)(**(long **)(param_2 + 0x640) + 0x130))();
        fVar14 = *pfVar7 * DAT_00fa86d4 + fVar14;
        fVar11 = DAT_00fa86d4 * pfVar7[2];
        fVar13 = fVar14;
        CPositionableObject::getPosition(*(CPositionableObject **)(param_2 + 0x640),true);
        fVar10 = DAT_00fd2b7c;
        fVar12 = (float)UTILITIES::randomBetweenVolatile
                                  ((fVar11 + fVar12) - DAT_00fd2b7c,fVar13 + DAT_00fd2b7c);
        fVar13 = (float)CPositionableObject::getPosition
                                  (*(CPositionableObject **)(param_2 + 0x640),true);
        fVar10 = (float)UTILITIES::randomBetweenVolatile(fVar14 - fVar10,fVar13 + fVar10);
        CCharacter::setDestination((CCharacter *)param_2,pCVar9,fVar10,fVar12);
      }
    }
  }
  return;
}

/* address=008e3a40
   symbol=CMonster::updateAI */

/* CMonster::updateAI(float, bool) */

void __thiscall CMonster::updateAI(CMonster *this,float param_1,bool param_2)

{
  float fVar1;
  uint uVar2;
  char cVar3;
  int iVar4;
  long lVar5;
  code *UNRECOVERED_JUMPTABLE;
  CDynamicPropertyFile *this_00;
  CLevel *this_01;

  *(float *)(this + 0x7e8) = *(float *)(this + 0x7e8) - param_1;
  if ((*(long *)(this + 0x1c8) == 0) ||
     (cVar3 = CCharacter::performingSkill((CCharacter *)this), cVar3 == '\0')) {
LAB_008e3a7e:
    if ((*(int *)(this + 0x330) != 0x2c) && (*(int *)(this + 0x330) != 0x23)) goto LAB_008e3a8e;
  }
  else {
    if ((*(int *)(this + 0x330) != 0xe) && (*(int *)(this + 0x330) != 0xd)) {
      CSkillManager::stopAllSkills(*(CSkillManager **)(this + 0x1c8),false,false,false);
      goto LAB_008e3a7e;
    }
LAB_008e3a8e:
    if (*(long *)(this + 0x750) == 0) {
      fVar1 = *(float *)(this + 0x524);
      *(float *)(this + 0x524) = param_1 + fVar1;
      if (((!param_2) &&
          (param_1 + fVar1 < *(float *)(KAIThinkTime + (long)*(int *)(this + 0x520) * 4))) &&
         (this[0x680] == (CMonster)0x0)) {
        return;
      }
      goto LAB_008e3ab7;
    }
  }
  *(float *)(this + 0x524) = param_1 + *(float *)(this + 0x524);
LAB_008e3ab7:
  *(undefined4 *)(this + 0x524) = 0;
  if (*(CCharacter **)(this + 0x340) != (CCharacter *)0x0) {
    cVar3 = CCharacter::alive(*(CCharacter **)(this + 0x340));
    if (cVar3 == '\0') {
      CCharacter::setTarget((CCharacter *)this,(CCharacter *)0x0);
    }
    else if (*(char *)(*(long *)(this + 0x340) + 0x199) == '\0') {
      CCharacter::setTarget((CCharacter *)this,(CCharacter *)0x0);
    }
  }
  uVar2 = KSETTINGS_AI_FREEZE;
  this_00 = (CDynamicPropertyFile *)0x0;
  if (*(long *)(this + 0x68) != 0) {
    lVar5 = CMasterResourceManager::getSingleton();
    this_00 = *(CDynamicPropertyFile **)(lVar5 + 0x90);
  }
  iVar4 = CDynamicPropertyFile::GetInt(this_00,uVar2);
  if (0 < iVar4) {
    return;
  }
  this_01 = (CLevel *)0x0;
  if (*(long *)(this + 0x68) != 0) {
    this_01 = *(CLevel **)(*(long *)(this + 0x68) + 0x18);
  }
  cVar3 = CCharacter::alive((CCharacter *)this);
  if ((cVar3 != '\0') &&
     ((cVar3 = CLevel::isDormant(this_01), cVar3 != '\0' ||
      (cVar3 = (**(code **)(*(long *)this + 0x48))(this), cVar3 == '\0')))) {
    cVar3 = CCharacter::performingAttack((CCharacter *)this);
    if ((cVar3 == '\0') &&
       ((((cVar3 = CCharacter::performingSkill((CCharacter *)this), cVar3 == '\0' &&
          (iVar4 = *(int *)(this + 0x330), iVar4 != 2)) &&
         ((iVar4 != 0x23 && (((iVar4 != 0x10 && (iVar4 != 0x29)) && (iVar4 != 0x2a)))))) &&
        (iVar4 != 0x28)))) {
      (**(code **)(*(long *)this + 0x348))(this,2);
    }
    else {
      cVar3 = CCharacter::performingSkill((CCharacter *)this);
      if (cVar3 != '\0') {
        CCharacter::attemptStopOfActiveSkill((CCharacter *)this);
      }
    }
  }
  switch(*(undefined4 *)(this + 0x330)) {
  case 0:
    cVar3 = CCharacter::performingAttack((CCharacter *)this);
    if (cVar3 != '\0') {
      return;
    }
    cVar3 = CCharacter::performingSkill((CCharacter *)this);
    if (cVar3 != '\0') {
      return;
    }
                    /* WARNING: Could not recover jumptable at 0x008e3de0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*(long *)this + 0x348))(this,2);
    return;
  case 1:
    fidgetAI(this,param_1,this_01);
    return;
  case 2:
    idleAI(param_1,(CLevel *)this,SUB81(this_01,0));
    return;
  case 3:
    UNRECOVERED_JUMPTABLE = *(code **)(*(long *)this + 0x3d8);
    break;
  case 4:
    UNRECOVERED_JUMPTABLE = *(code **)(*(long *)this + 0x3b8);
    break;
  case 5:
    UNRECOVERED_JUMPTABLE = *(code **)(*(long *)this + 0x360);
    break;
  default:
    return;
  case 7:
    UNRECOVERED_JUMPTABLE = *(code **)(*(long *)this + 0x3c8);
    break;
  case 9:
    UNRECOVERED_JUMPTABLE = *(code **)(*(long *)this + 0x3d0);
    break;
  case 10:
    fleeAI(param_1,(CLevel *)this);
    return;
  case 0xb:
    getRangeAI(param_1,(CLevel *)this);
    return;
  case 0xc:
    UNRECOVERED_JUMPTABLE = *(code **)(*(long *)this + 0x378);
    break;
  case 0xd:
    UNRECOVERED_JUMPTABLE = *(code **)(*(long *)this + 0x3e0);
    break;
  case 0xe:
                    /* WARNING: Could not recover jumptable at 0x008e3cd3. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*(long *)this + 0x388))(param_1,this);
    return;
  case 0xf:
                    /* WARNING: Could not recover jumptable at 0x008e3cb6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*(long *)this + 0x3c0))(param_1,this,this_01,0xffffffffffffffff);
    return;
  case 0x10:
    jumpDownAI(this,param_1,this_01);
    return;
  case 0x1d:
    UNRECOVERED_JUMPTABLE = *(code **)(*(long *)this + 0x390);
    break;
  case 0x23:
    CCharacter::animationPlayAI((CCharacter *)this,param_1);
    return;
  case 0x29:
    UNRECOVERED_JUMPTABLE = *(code **)(*(long *)this + 0x368);
  }
                    /* WARNING: Could not recover jumptable at 0x008e3c54. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)(param_1,this,this_01);
  return;
}

/* export-summary functions=32 failures=0 */
