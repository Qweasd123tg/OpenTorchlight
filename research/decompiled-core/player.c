/* Targeted Ghidra class export.
   namespace=CPlayer
   Treat pseudocode as navigation evidence. */


/* address=008e3e70
   symbol=CPlayer::clearSkillMap */

/* CPlayer::clearSkillMap() */

void __thiscall CPlayer::clearSkillMap(CPlayer *this)

{
  long lVar1;

  lVar1 = 0;
  do {
    *(undefined8 *)(this + lVar1 + 0x8b0) = 0xffffffffffffffff;
    *(undefined8 *)(this + lVar1 + 0x900) = 0xffffffffffffffff;
    lVar1 = lVar1 + 8;
  } while (lVar1 != 0x50);
  return;
}



/* address=008e3ea0
   symbol=CPlayer::clearSkillFunctionMap */

/* CPlayer::clearSkillFunctionMap() */

void __thiscall CPlayer::clearSkillFunctionMap(CPlayer *this)

{
  long lVar1;

  lVar1 = 0;
  do {
    *(undefined8 *)(this + lVar1 + 0x950) = 0xffffffffffffffff;
    *(undefined8 *)(this + lVar1 + 0x9b0) = 0xffffffffffffffff;
    lVar1 = lVar1 + 8;
  } while (lVar1 != 0x60);
  return;
}



/* address=008e3ed0
   symbol=CPlayer::setMappedFunctionSkill */

/* CPlayer::setMappedFunctionSkill(unsigned int, long long) */

void __thiscall CPlayer::setMappedFunctionSkill(CPlayer *this,uint param_1,longlong param_2)

{
  long lVar1;

  lVar1 = 0;
  do {
    while (*(long *)(this + lVar1 + 0x950) == param_2) {
      *(undefined8 *)(this + lVar1 + 0x950) = 0xffffffffffffffff;
      lVar1 = lVar1 + 8;
      if (lVar1 == 0x60) goto LAB_008e3f02;
    }
    lVar1 = lVar1 + 8;
  } while (lVar1 != 0x60);
LAB_008e3f02:
  *(longlong *)(this + (ulong)param_1 * 8 + 0x950) = param_2;
  if (param_2 != -1) {
    *(undefined8 *)(this + (ulong)param_1 * 8 + 0x9b0) = 0xffffffffffffffff;
  }
  return;
}



/* address=008e3f20
   symbol=CPlayer::setLeftMappedFunctionSkill */

/* CPlayer::setLeftMappedFunctionSkill(unsigned int, long long) */

void __thiscall CPlayer::setLeftMappedFunctionSkill(CPlayer *this,uint param_1,longlong param_2)

{
  long lVar1;

  lVar1 = 0;
  do {
    while (*(long *)(this + lVar1 + 0x9b0) == param_2) {
      *(undefined8 *)(this + lVar1 + 0x9b0) = 0xffffffffffffffff;
      lVar1 = lVar1 + 8;
      if (lVar1 == 0x60) goto LAB_008e3f52;
    }
    lVar1 = lVar1 + 8;
  } while (lVar1 != 0x60);
LAB_008e3f52:
  *(longlong *)(this + (ulong)param_1 * 8 + 0x9b0) = param_2;
  if (param_2 != -1) {
    *(undefined8 *)(this + (ulong)param_1 * 8 + 0x950) = 0xffffffffffffffff;
  }
  return;
}



/* address=008e3f70
   symbol=CPlayer::clearItemLinkMap */

/* CPlayer::clearItemLinkMap() */

void __thiscall CPlayer::clearItemLinkMap(CPlayer *this)

{
  *(undefined8 *)(this + 0x780) = 0xffffffffffffffff;
  *(undefined8 *)(this + 0x788) = 0xffffffffffffffff;
  return;
}



/* address=008e3f90
   symbol=CPlayer::resetLevel */

/* CPlayer::resetLevel() */

void __thiscall CPlayer::resetLevel(CPlayer *this)

{
  *(undefined4 *)(this + 0x100) = 1;
  *(undefined4 *)(this + 0x448) = 0;
  *(undefined4 *)(this + 0x44c) = 0;
  (**(code **)(*(long *)this + 0x418))();
  *(float *)(this + 0x414) = (float)*(int *)(this + 0x418);
  (**(code **)(*(long *)this + 0x410))(this);
  *(float *)(this + 0x438) = (float)*(int *)(this + 0x43c);
  return;
}



/* address=008e3ff0
   symbol=CPlayer::setAIState */

/* CPlayer::setAIState(EAIState) */

void __thiscall CPlayer::setAIState(CPlayer *this,int param_2)

{
  long *plVar1;

  if ((((*(int *)(this + 0x330) - 0x20U < 3) && (param_2 != 0x20)) && (param_2 != 0x21)) &&
     ((param_2 != 0x22 && (plVar1 = *(long **)(this + 0x2f0), plVar1 != (long *)0x0)))) {
    (**(code **)(*plVar1 + 0x378))(plVar1,0,1);
  }
  *(int *)(this + 0x330) = param_2;
  return;
}



/* address=008e4060
   symbol=CPlayer::removeLevelSavedState */

/* CPlayer::removeLevelSavedState(unsigned int) */

void __thiscall CPlayer::removeLevelSavedState(CPlayer *this,uint param_1)

{
  long lVar1;
  long *plVar2;
  long lVar3;
  long lVar4;

  lVar3 = *(long *)(this + 0x7a0);
  lVar4 = *(long *)(this + 0x798);
  lVar1 = lVar3 - lVar4 >> 3;
  if ((int)param_1 < (int)lVar1) {
    lVar3 = (long)(int)param_1 * 8;
    plVar2 = (long *)(lVar4 + lVar3);
    if ((long *)*plVar2 != (long *)0x0) {
      (**(code **)(*(long *)*plVar2 + 8))();
      *(undefined8 *)(*(long *)(this + 0x798) + (long)(int)param_1 * 8) = 0;
      lVar4 = *(long *)(this + 0x798);
      plVar2 = (long *)(lVar4 + lVar3);
      lVar1 = *(long *)(this + 0x7a0) - lVar4 >> 3;
    }
    *plVar2 = *(long *)(lVar4 + -8 + lVar1 * 8);
    lVar3 = *(long *)(this + 0x7a0);
  }
  *(long *)(this + 0x7a0) = lVar3 + -8;
  return;
}



/* address=008e4110
   symbol=CPlayer::clearLevelHistory */

/* CPlayer::clearLevelHistory() */

void __thiscall CPlayer::clearLevelHistory(CPlayer *this)

{
  long lVar1;
  long lVar2;
  uint uVar3;
  uint uVar4;

  lVar1 = *(long *)(this + 0x7a0);
  lVar2 = *(long *)(this + 0x798);
  if (0 < (int)(lVar1 - lVar2 >> 3)) {
    uVar3 = 0;
    do {
      uVar4 = uVar3;
      if (*(char *)(*(long *)(lVar2 + (long)(int)uVar3 * 8) + 0xb0) == '\0') {
        uVar4 = uVar3 - 1;
        removeLevelSavedState(this,uVar3);
        lVar2 = *(long *)(this + 0x798);
        lVar1 = *(long *)(this + 0x7a0);
      }
      uVar3 = uVar4 + 1;
    } while ((int)uVar3 < (int)(lVar1 - lVar2 >> 3));
  }
  return;
}



/* address=008e4190
   symbol=CPlayer::setJournalStatistic */

/* CPlayer::setJournalStatistic(EJournalStatistic, int) */

void __thiscall CPlayer::setJournalStatistic(CPlayer *this,int param_2,undefined4 param_3)

{
  *(undefined4 *)(this + (long)param_2 * 4 + 0x7dc) = param_3;
  return;
}



/* address=008e41a0
   symbol=CPlayer::soldItem */

/* CPlayer::soldItem(CEquipment*) */

void CPlayer::soldItem(CEquipment *param_1)

{
  undefined8 uVar1;

  uVar1 = CSteamStats::getSingleton();
  CSteamStats::incrementStat(uVar1,0x11,1);
  return;
}



/* address=008e41c0
   symbol=CPlayer::incrementJournalStatistic */

/* CPlayer::incrementJournalStatistic(EJournalStatistic, int) */

void __thiscall CPlayer::incrementJournalStatistic(CPlayer *this,int param_2,int param_3)

{
  undefined8 uVar1;
  CAchievements *pCVar2;
  CAchievement *this_00;

  switch(param_2) {
  case 1:
    uVar1 = CSteamStats::getSingleton();
    CSteamStats::incrementStat(uVar1,0xd,param_3);
    if (99999 < *(int *)(this + 0x444) + param_3) {
      pCVar2 = (CAchievements *)CAchievements::getSingleton();
      this_00 = (CAchievement *)CAchievements::getAchievement(pCVar2,0x23);
      CAchievement::forceComplete(this_00);
    }
    break;
  case 3:
    uVar1 = CSteamStats::getSingleton();
    CSteamStats::incrementStat(uVar1,0xf,param_3);
    break;
  case 4:
    uVar1 = CSteamStats::getSingleton();
    CSteamStats::incrementStat(uVar1,10,param_3);
    break;
  case 5:
    uVar1 = CSteamStats::getSingleton();
    CSteamStats::incrementStat(uVar1,0,param_3);
    if (this[0xa15] != (CPlayer)0x0) {
      uVar1 = CSteamStats::getSingleton();
      CSteamStats::incrementStat(uVar1,0x12,param_3);
    }
    break;
  case 6:
    uVar1 = CSteamStats::getSingleton();
    CSteamStats::incrementStat(uVar1,4,param_3);
    break;
  case 0xb:
    uVar1 = CSteamStats::getSingleton();
    CSteamStats::incrementStat(uVar1,1,param_3);
    break;
  case 0xc:
    uVar1 = CSteamStats::getSingleton();
    CSteamStats::incrementStat(uVar1,0x10,param_3);
    break;
  case 0xe:
    uVar1 = CSteamStats::getSingleton();
    CSteamStats::incrementStat(uVar1,6,param_3);
    break;
  case 0xf:
    uVar1 = CSteamStats::getSingleton();
    CSteamStats::incrementStat(uVar1,9,param_3);
    break;
  case 0x10:
    uVar1 = CSteamStats::getSingleton();
    CSteamStats::incrementStat(uVar1,8,param_3);
  }
  *(int *)(this + (long)param_2 * 4 + 0x7dc) = *(int *)(this + (long)param_2 * 4 + 0x7dc) + param_3;
  return;
}



/* address=008e4490
   symbol=CPlayer::createPortals */

/* CPlayer::createPortals(CLevel&) */

void __thiscall CPlayer::createPortals(CPlayer *this,CLevel *param_1)

{
  size_t __n;
  int iVar1;
  long *plVar2;
  CItem *pCVar3;
  uint uVar4;
  long lVar5;
  undefined8 local_38;
  undefined4 local_30;
  undefined8 local_28;
  float local_20;

  local_28 = *(undefined8 *)(param_1 + 0x158);
  local_20 = *(float *)(param_1 + 0x160);
  if ((DAT_00fa8760 == (float)local_28) &&
     (local_28._4_4_ = (float)((ulong)local_28 >> 0x20), DAT_00fa8760 == local_28._4_4_)) {
    if ((DAT_00fa8760 != local_20) || (NAN(DAT_00fa8760) || NAN(local_20))) goto LAB_008e44c7;
  }
  else {
LAB_008e44c7:
    if (*(uint *)(this + 0xa48) != 0) {
      lVar5 = 0;
      uVar4 = 0;
      do {
        if (uVar4 < *(uint *)(this + 0xa4c)) {
          plVar2 = (long *)(lVar5 + *(long *)(this + 0xa40));
        }
        else {
          plVar2 = *(long **)(this + 0xa40);
        }
        if (*(long *)(*plVar2 + 0x20) - *(long *)(*plVar2 + 0x18) >> 2 != 0) {
          lVar5 = CResourceManager::createUnit
                            (*(CResourceManager **)(this + 0x68),L"PROPS",L"WAYPOINT PORTAL",0,false
                            );
          if ((lVar5 != 0) &&
             (pCVar3 = (CItem *)__dynamic_cast(lVar5,&CBaseUnit::typeinfo,&CItem::typeinfo),
             pCVar3 != (CItem *)0x0)) {
            CLevel::addItem(param_1,pCVar3,(Vector3 *)&local_28,false);
          }
          break;
        }
        uVar4 = uVar4 + 1;
        lVar5 = lVar5 + 8;
      } while (uVar4 < *(uint *)(this + 0xa48));
    }
  }
  if (this[0x7b0] == (CPlayer)0x0) goto LAB_008e4635;
  if (*(int *)(this + 0x7b4) == *(int *)(param_1 + 0x1a4)) {
    __n = *(size_t *)(*(wchar_t **)(param_1 + 0x280) + -6);
    if ((__n != *(size_t *)(*(wchar_t **)(this + 0x7b8) + -6)) ||
       (iVar1 = wmemcmp(*(wchar_t **)(param_1 + 0x280),*(wchar_t **)(this + 0x7b8),__n), iVar1 != 0)
       ) goto LAB_008e458f;
    lVar5 = *(long *)(param_1 + 0x1d8);
  }
  else {
LAB_008e458f:
    lVar5 = *(long *)(param_1 + 0x1d8);
    if (*(char *)(lVar5 + 0x86) == '\0') {
      return;
    }
  }
  local_38 = *(undefined8 *)(this + 0x7c0);
  local_30 = *(undefined4 *)(this + 0x7c8);
  if (*(char *)(lVar5 + 0x86) == '\0') {
LAB_008e4678:
    lVar5 = CResourceManager::createUnit
                      (*(CResourceManager **)(this + 0x68),L"PROPS",L"RETURN TO TOWN",0,false);
  }
  else {
    local_38 = *(undefined8 *)(param_1 + 0x14c);
    local_30 = *(undefined4 *)(param_1 + 0x154);
    if (*(char *)(lVar5 + 0x86) == '\0') goto LAB_008e4678;
    lVar5 = CResourceManager::createUnit
                      (*(CResourceManager **)(this + 0x68),L"PROPS",L"RETURN TO DUNGEON",0,false);
  }
  if ((lVar5 != 0) &&
     (pCVar3 = (CItem *)__dynamic_cast(lVar5,&CBaseUnit::typeinfo,&CItem::typeinfo),
     pCVar3 != (CItem *)0x0)) {
    CLevel::addItem(param_1,pCVar3,(Vector3 *)&local_38,false);
  }
LAB_008e4635:
  CLevel::updateAutomapIcons();
  return;
}



/* address=008e46e0
   symbol=CPlayer::openPortal */

/* CPlayer::openPortal(CLevel&) */

void CPlayer::openPortal(CLevel *param_1)

{
  CLevel *in_RSI;
  undefined8 uVar1;
  undefined4 in_XMM1_Da;
  undefined8 local_28 [3];

  if (*(char *)(*(long *)(in_RSI + 0x1d8) + 0x84) != '\0') {
    CLevel::deleteOpenPortals(in_RSI);
    param_1[0x7b0] = (CLevel)0x1;
    *(undefined4 *)(param_1 + 0x7b4) = *(undefined4 *)(in_RSI + 0x1a4);
    std::wstring::assign((wstring_conflict *)(param_1 + 0x7b8));
    local_28[0] = CPositionableObject::getPosition((CPositionableObject *)param_1,true);
    uVar1 = CLevel::randomOpenPosition(in_RSI,(Vector3 *)local_28,DAT_00fa86d4,false);
    *(undefined8 *)(param_1 + 0x7c0) = uVar1;
    *(undefined4 *)(param_1 + 0x7c8) = in_XMM1_Da;
    createPortals((CPlayer *)param_1,in_RSI);
  }
  return;
}



/* address=008e47d0
   symbol=CPlayer::die */

/* CPlayer::die(CCharacter*, Ogre::Vector3 const*, float, bool) */

void CPlayer::die(CCharacter *param_1,Vector3 *param_2,float param_3,bool param_4)

{
  char cVar1;
  long lVar2;
  CGameClient *this;

  cVar1 = CCharacter::alive(param_1);
  if (cVar1 != '\0') {
    lVar2 = 0;
    if (*(int *)(*(long *)(param_1 + 0x68) + 0x30) != 0) {
      lVar2 = **(long **)(*(long *)(param_1 + 0x68) + 0x28);
    }
    if (*(int *)(lVar2 + 0x38d0) == 1) {
      CCharacter::die(param_1,param_2,param_3,param_4);
      if (param_1[0xa15] != (CCharacter)0x0) {
        this = (CGameClient *)0x0;
        if (*(int *)(*(long *)(param_1 + 0x68) + 0x30) != 0) {
          this = (CGameClient *)**(undefined8 **)(*(long *)(param_1 + 0x68) + 0x28);
        }
        CGameClient::saveCharacter(this,true,true);
        return;
      }
    }
  }
  return;
}



/* address=008e48a0
   symbol=CPlayer::update */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CPlayer::update(Ogre::Camera*, Ogre::Vector3 const&, float) */

void __thiscall CPlayer::update(CPlayer *this,Camera *param_1,Vector3 *param_2,float param_3)

{
  float fVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  long lVar6;
  CGameUI *pCVar7;
  CCharacter *this_00;
  bool bVar8;
  string local_68 [16];
  string local_58 [16];
  string local_48 [16];
  string local_38 [12];
  allocator local_2c;
  allocator local_2b;
  allocator local_2a;
  allocator local_29;

  CCharacter::update((CCharacter *)this,param_1,param_2,param_3);
  if (*(long *)(this + 0x868) != 0) {
    CQuestManager::update(param_3);
  }
  if (*(long *)(this + 0x750) != 0) {
    CCharacter::updatePathFollowing(SUB81(this,0));
  }
  if (this[0x264] == (CPlayer)0x0) {
    this[0x321] = (CPlayer)0x0;
                    /* try { // try from 008e4a0a to 008e4a3f has its CatchHandler @ 008e4caf */
    if (((((*(int *)(this + 0x330) == 0) || (*(int *)(this + 0x330) == 2)) &&
         (cVar2 = CCharacter::performingSkill((CCharacter *)this), cVar2 == '\0')) &&
        ((cVar2 = CCharacter::performingAttack((CCharacter *)this), cVar2 == '\0' &&
         (DAT_00fa86e0 < *(float *)(this + 0x284))))) &&
       (iVar3 = UTILITIES::randomIntegerBetweenVolatile(0,1000), iVar3 < 3)) {
      std::string::string(local_38,"IDLE",&local_29);
      cVar2 = CCharacter::animationPlaying((CCharacter *)this,local_38);
      if (cVar2 == '\0') {
        bVar8 = false;
      }
      else {
                    /* try { // try from 008e4c82 to 008e4c9b has its CatchHandler @ 008e4caf */
        std::string::string(local_48,"FIDGET",&local_2a);
        cVar2 = CGenericModel::animationExistsSubstring(*(CGenericModel **)(this + 0x200),local_48);
        bVar8 = cVar2 != '\0';
                    /* try { // try from 008e4ca5 to 008e4ca9 has its CatchHandler @ 008e4cdb */
        std::string::~string(local_48);
      }
                    /* try { // try from 008e4a53 to 008e4a57 has its CatchHandler @ 008e4cf4 */
      std::string::~string(local_38);
      if (bVar8) {
        *(undefined4 *)(this + 0x284) = 0;
                    /* try { // try from 008e4a84 to 008e4a88 has its CatchHandler @ 008e4cf2 */
        std::string::string(local_58,"FIDGET",&local_2b);
                    /* try { // try from 008e4a93 to 008e4abf has its CatchHandler @ 008e4cef */
        uVar4 = CGenericModel::findRandomAnimation(*(CGenericModel **)(this + 0x200),local_58);
        CGenericModel::blendAnimation
                  (*(CGenericModel **)(this + 0x200),uVar4,false,DAT_00fa86e8,DAT_00fa47fc,
                   DAT_00fa8760);
                    /* try { // try from 008e4ac3 to 008e4ac7 has its CatchHandler @ 008e4cf2 */
        std::string::~string(local_58);
                    /* try { // try from 008e4ada to 008e4ade has its CatchHandler @ 008e4cea */
        std::string::string(local_68,"IDLE",&local_2c);
                    /* try { // try from 008e4afa to 008e4afe has its CatchHandler @ 008e4cce */
        CCharacter::queueBlendAnimation((CCharacter *)this,local_68,true,DAT_00fa86e8,DAT_00fa47fc);
                    /* try { // try from 008e4b02 to 008e4b06 has its CatchHandler @ 008e4cea */
        std::string::~string(local_68);
      }
    }
  }
  else {
    this[0x321] = (CPlayer)0x1;
  }
  lVar6 = 0;
  if (*(int *)(*(long *)(this + 0x68) + 0x30) != 0) {
    lVar6 = **(long **)(*(long *)(this + 0x68) + 0x28);
  }
  if ((*(int *)(lVar6 + 0x38d0) == 1) && (lVar6 = CResourceManager::getGameUI(), lVar6 != 0)) {
    iVar3 = CCharacter::HP((CCharacter *)this);
    iVar5 = CCharacter::maxHP((CCharacter *)this);
    if ((float)iVar3 <= (float)iVar5 * _DAT_00fd22e8) {
      pCVar7 = (CGameUI *)CResourceManager::getGameUI();
      CGameUI::queueTip(pCVar7,3);
    }
    iVar3 = CCharacter::mana((CCharacter *)this);
    iVar5 = CCharacter::maxMana((CCharacter *)this);
    if ((float)iVar3 <= (float)iVar5 * DAT_00fa86e8) {
      pCVar7 = (CGameUI *)CResourceManager::getGameUI();
      CGameUI::queueTip(pCVar7,4);
    }
    lVar6 = *(long *)(this + 0x650) - (long)*(undefined8 **)(this + 0x648) >> 3;
    if ((int)lVar6 != 0) {
      this_00 = (CCharacter *)0x0;
      if (lVar6 != 0) {
        this_00 = (CCharacter *)**(undefined8 **)(this + 0x648);
      }
      cVar2 = CCharacter::isPetNearDeath(this_00);
      if (cVar2 != '\0') {
        pCVar7 = (CGameUI *)CResourceManager::getGameUI();
        CGameUI::queueTip(pCVar7,0xb);
      }
    }
  }
  iVar3 = CCharacter::HP((CCharacter *)this);
  if ((0.0 < (float)iVar3) || (lVar6 = CResourceManager::getGameUI(), lVar6 == 0)) {
    if (this[0xa14] == (CPlayer)0x0) {
      return;
    }
  }
  else {
    lVar6 = 0;
    if (*(int *)(*(long *)(this + 0x68) + 0x30) != 0) {
      lVar6 = **(long **)(*(long *)(this + 0x68) + 0x28);
    }
    if (*(int *)(lVar6 + 0x38d0) == 1) {
      fVar1 = *(float *)(this + 0x884);
      *(float *)(this + 0x884) = fVar1 - param_3;
      if (0.0 < fVar1 - param_3) {
        return;
      }
      pCVar7 = (CGameUI *)CResourceManager::getGameUI();
      CGameUI::toggleDeath(pCVar7);
      *(undefined4 *)(this + 0x884) = 0x497423f0;
      return;
    }
  }
  *(undefined4 *)(this + 0x528) = 0x3ecccccd;
  CCharacter::updateOpacity((CCharacter *)this,0.0,true);
  return;
}



/* address=008e4d00
   symbol=CPlayer::startFishing */

/* CPlayer::startFishing() */

void __thiscall CPlayer::startFishing(CPlayer *this)

{
  undefined4 uVar1;

  CCharacter::startFishing((CCharacter *)this);
  (**(code **)(**(long **)(this + 0x830) + 0x50))(*(long **)(this + 0x830),0);
  this[0x85c] = (CPlayer)0x0;
  uVar1 = UTILITIES::randomBetweenVolatile(DAT_00fa47fc,DAT_00fa86d4);
  *(undefined4 *)(this + 0x858) = uVar1;
  *(undefined4 *)(this + 0x850) = 0x40000000;
  *(undefined4 *)(this + 0x860) = 0;
  *(undefined4 *)(this + 0x854) = 0;
  return;
}



/* address=008e4d60
   symbol=CPlayer::calculateMaxMana */

/* CPlayer::calculateMaxMana() */

void __thiscall CPlayer::calculateMaxMana(CPlayer *this)

{
  int iVar1;
  CGraphManager *this_00;
  CGraph *this_01;
  float fVar2;
  float fVar3;

  if (*(long *)(*(long *)(this + 0x888) + -0x18) != 0) {
    this_00 = (CGraphManager *)CGraphManager::getSingleton();
    this_01 = (CGraph *)CGraphManager::getGraph(this_00,(wstring_conflict *)(this + 0x888));
    if (this_01 != (CGraph *)0x0) {
      fVar2 = (float)CGraph::getValue(this_01,(float)*(int *)(this + 0x100),0);
      fVar3 = ceilf(fVar2);
      fVar2 = *(float *)(this + 0x438);
      *(int *)(this + 0x43c) = (int)fVar3;
      iVar1 = CCharacter::maxMana((CCharacter *)this);
      if ((float)iVar1 < fVar2) {
        iVar1 = CCharacter::maxMana((CCharacter *)this);
        *(float *)(this + 0x438) = (float)iVar1;
        return;
      }
    }
  }
  return;
}



/* address=008e4e00
   symbol=CPlayer::getSkillPointsAwardedForFameLevel */

/* CPlayer::getSkillPointsAwardedForFameLevel(unsigned int) */

int __thiscall CPlayer::getSkillPointsAwardedForFameLevel(CPlayer *this,uint param_1)

{
  CGraphManager *this_00;
  CGraph *this_01;
  float fVar1;

  if (*(long *)(*(long *)(this + 0x8a8) + -0x18) != 0) {
    this_00 = (CGraphManager *)CGraphManager::getSingleton();
    this_01 = (CGraph *)CGraphManager::getGraph(this_00,(wstring_conflict *)(this + 0x8a8));
    if (this_01 != (CGraph *)0x0) {
      fVar1 = (float)CGraph::getValue(this_01,(float)param_1,0);
      fVar1 = ceilf(fVar1);
      return (int)fVar1;
    }
  }
  return 0;
}



/* address=008e4e80
   symbol=CPlayer::getSkillPointsAwardedForLevel */

/* CPlayer::getSkillPointsAwardedForLevel(unsigned int) */

int __thiscall CPlayer::getSkillPointsAwardedForLevel(CPlayer *this,uint param_1)

{
  CGraphManager *this_00;
  CGraph *this_01;
  float fVar1;

  if (*(long *)(*(long *)(this + 0x8a0) + -0x18) != 0) {
    this_00 = (CGraphManager *)CGraphManager::getSingleton();
    this_01 = (CGraph *)CGraphManager::getGraph(this_00,(wstring_conflict *)(this + 0x8a0));
    if (this_01 != (CGraph *)0x0) {
      fVar1 = (float)CGraph::getValue(this_01,(float)param_1,0);
      fVar1 = ceilf(fVar1);
      return (int)fVar1;
    }
  }
  return 0;
}



/* address=008e4f00
   symbol=CPlayer::getStatsPointsAwardedForLevel */

/* CPlayer::getStatsPointsAwardedForLevel(unsigned int) */

int __thiscall CPlayer::getStatsPointsAwardedForLevel(CPlayer *this,uint param_1)

{
  CGraphManager *this_00;
  CGraph *this_01;
  float fVar1;

  if (*(long *)(*(long *)(this + 0x898) + -0x18) != 0) {
    this_00 = (CGraphManager *)CGraphManager::getSingleton();
    this_01 = (CGraph *)CGraphManager::getGraph(this_00,(wstring_conflict *)(this + 0x898));
    if (this_01 != (CGraph *)0x0) {
      fVar1 = (float)CGraph::getValue(this_01,(float)param_1,0);
      fVar1 = ceilf(fVar1);
      return (int)fVar1;
    }
  }
  return 0;
}



/* address=008e4f80
   symbol=CPlayer::calculateMaxHP */

/* CPlayer::calculateMaxHP() */

void __thiscall CPlayer::calculateMaxHP(CPlayer *this)

{
  int iVar1;
  CGraphManager *this_00;
  CGraph *this_01;
  float fVar2;
  float fVar3;

  if (*(long *)(*(long *)(this + 0x890) + -0x18) != 0) {
    this_00 = (CGraphManager *)CGraphManager::getSingleton();
    this_01 = (CGraph *)CGraphManager::getGraph(this_00,(wstring_conflict *)(this + 0x890));
    if (this_01 != (CGraph *)0x0) {
      fVar2 = (float)CGraph::getValue(this_01,(float)*(int *)(this + 0x100),0);
      fVar3 = ceilf(fVar2);
      fVar2 = *(float *)(this + 0x414);
      *(int *)(this + 0x418) = (int)fVar3;
      iVar1 = CCharacter::maxHP((CCharacter *)this);
      if ((float)iVar1 < fVar2) {
        iVar1 = CCharacter::maxHP((CCharacter *)this);
        *(float *)(this + 0x414) = (float)iVar1;
        return;
      }
    }
  }
  return;
}



/* address=008e5020
   symbol=CPlayer::firstTimeSetup */

/* CPlayer::firstTimeSetup() */

void __thiscall CPlayer::firstTimeSetup(CPlayer *this)

{
  CEquipment *pCVar1;
  CGameUI *pCVar2;

  if (*(long *)(this + 0x490) != 0) {
    pCVar1 = (CEquipment *)
             CResourceManager::createEquipment
                       (*(CResourceManager **)(this + 0x68),L"Health Potion",false,true);
    if (pCVar1 != (CEquipment *)0x0) {
      CInventory::pickupEquipment(*(CInventory **)(this + 0x490),pCVar1,true);
    }
    pCVar1 = (CEquipment *)
             CResourceManager::createEquipment
                       (*(CResourceManager **)(this + 0x68),L"Health Potion",false,true);
    if (pCVar1 != (CEquipment *)0x0) {
      CInventory::pickupEquipment(*(CInventory **)(this + 0x490),pCVar1,true);
    }
    pCVar1 = (CEquipment *)
             CResourceManager::createEquipment
                       (*(CResourceManager **)(this + 0x68),L"Mana Potion",false,true);
    if (pCVar1 != (CEquipment *)0x0) {
      CInventory::pickupEquipment(*(CInventory **)(this + 0x490),pCVar1,true);
    }
    pCVar1 = (CEquipment *)
             CResourceManager::createEquipment
                       (*(CResourceManager **)(this + 0x68),L"Mana Potion",false,true);
    if (pCVar1 != (CEquipment *)0x0) {
      CInventory::pickupEquipment(*(CInventory **)(this + 0x490),pCVar1,true);
    }
    pCVar1 = (CEquipment *)
             CResourceManager::createEquipment
                       (*(CResourceManager **)(this + 0x68),L"Town Portal Scroll",false,true);
    if (pCVar1 != (CEquipment *)0x0) {
      CInventory::pickupEquipment(*(CInventory **)(this + 0x490),pCVar1,true);
    }
    pCVar1 = (CEquipment *)
             CResourceManager::createEquipment
                       (*(CResourceManager **)(this + 0x68),L"Town Portal Scroll",false,true);
    if (pCVar1 != (CEquipment *)0x0) {
      CInventory::pickupEquipment(*(CInventory **)(this + 0x490),pCVar1,true);
    }
    pCVar1 = (CEquipment *)
             CResourceManager::createEquipment
                       (*(CResourceManager **)(this + 0x68),L"Identify Scroll",false,true);
    if (pCVar1 != (CEquipment *)0x0) {
      CInventory::pickupEquipment(*(CInventory **)(this + 0x490),pCVar1,true);
    }
    pCVar1 = (CEquipment *)
             CResourceManager::createEquipment
                       (*(CResourceManager **)(this + 0x68),L"Identify Scroll",false,true);
    if (pCVar1 != (CEquipment *)0x0) {
      CInventory::pickupEquipment(*(CInventory **)(this + 0x490),pCVar1,true);
    }
    pCVar2 = (CGameUI *)CResourceManager::getGameUI();
    CGameUI::queueTip(pCVar2,9);
    return;
  }
  return;
}



/* address=008e51d0
   symbol=CPlayer::levelLoaded */

/* CPlayer::levelLoaded(CLevel*) */

void CPlayer::levelLoaded(CLevel *param_1)

{
  long lVar1;
  CEquipment *this;
  uint uVar2;
  CInventory *this_00;

  this_00 = *(CInventory **)(param_1 + 0x490);
  if (this_00 != (CInventory *)0x0) {
    uVar2 = 0;
    while( true ) {
      lVar1 = CInventory::getEquipmentInSlot(this_00,uVar2);
      if (lVar1 != 0) {
        this = (CEquipment *)CInventory::getEquipmentInSlot(*(CInventory **)(param_1 + 0x490),uVar2)
        ;
        CEquipment::resetVisualLayout(this);
      }
      uVar2 = uVar2 + 1;
      if (uVar2 == 0xc) break;
      this_00 = *(CInventory **)(param_1 + 0x490);
    }
  }
  return;
}



/* address=008ef510
   symbol=CPlayer::_GLOBAL__I_CPlayer */

/* CPlayer::CPlayer(CResourceManager*) */

void CPlayer::_GLOBAL__I_CPlayer(void)

{
  allocator aStack_3bd;
  allocator aStack_3bc;
  allocator aStack_3bb;
  allocator aStack_3ba;
  allocator aStack_3b9;
  allocator aStack_3b8;
  allocator aStack_3b7;
  allocator aStack_3b6;
  allocator aStack_3b5;
  allocator aStack_3b4;
  allocator aStack_3b3;
  allocator aStack_3b2;
  allocator aStack_3b1;
  allocator aStack_3b0;
  allocator aStack_3af;
  allocator aStack_3ae;
  allocator aStack_3ad;
  allocator aStack_3ac;
  allocator aStack_3ab;
  allocator aStack_3aa;
  allocator aStack_3a9;
  allocator aStack_3a8;
  allocator aStack_3a7;
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
  ParticleUniverse::HALFSCALE._4_4_ = DAT_0142463c * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._0_4_ = Ogre::Vector3::UNIT_SCALE * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._8_4_ = DAT_00fa4810 * DAT_01424640;
  std::string::string((string *)&ParticleUniverse::ALIAS,"1",&aStack_3bd);
  __cxa_atexit(std::string::~string,&ParticleUniverse::ALIAS,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::SYSTEM,"2",&aStack_3bc);
  __cxa_atexit(std::string::~string,&ParticleUniverse::SYSTEM,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::TECHNIQUE,"3",&aStack_3bb);
  __cxa_atexit(std::string::~string,&ParticleUniverse::TECHNIQUE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::RENDERER,"4",&aStack_3ba);
  __cxa_atexit(std::string::~string,&ParticleUniverse::RENDERER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EMITTER,"5",&aStack_3b9);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EMITTER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::AFFECTOR,"6",&aStack_3b8);
  __cxa_atexit(std::string::~string,&ParticleUniverse::AFFECTOR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::OBSERVER,"7",&aStack_3b7);
  __cxa_atexit(std::string::~string,&ParticleUniverse::OBSERVER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::HANDLER,"8",&aStack_3b6);
  __cxa_atexit(std::string::~string,&ParticleUniverse::HANDLER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::BEHAVIOUR,"9",&aStack_3b5);
  __cxa_atexit(std::string::~string,&ParticleUniverse::BEHAVIOUR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EXTERN,"10",&aStack_3b4);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EXTERN,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DYNAMIC_ATTRIBUTE,"11",&aStack_3b3);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DYNAMIC_ATTRIBUTE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DEPENDENCY,"12",&aStack_3b2);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DEPENDENCY,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gRESOURCE_GROUP_NAMES,L"ITEMS",&aStack_3b1);
  std::wstring::wstring((wstring_conflict *)(::gRESOURCE_GROUP_NAMES + 8),L"MONSTERS",&aStack_3b0);
  std::wstring::wstring((wstring_conflict *)(::gRESOURCE_GROUP_NAMES + 0x10),L"PLAYERS",&aStack_3af)
  ;
  std::wstring::wstring((wstring_conflict *)(::gRESOURCE_GROUP_NAMES + 0x18),L"PROPS",&aStack_3ae);
  __cxa_atexit(::__tcf_0,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::gRESOURCE_GROUP_FILE_LOCATIONS,L"media/units/items/",&aStack_3ad)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gRESOURCE_GROUP_FILE_LOCATIONS + 8),L"media/units/monsters/",
             &aStack_3ac);
  std::wstring::wstring
            ((wstring_conflict *)(::gRESOURCE_GROUP_FILE_LOCATIONS + 0x10),L"media/units/players/",
             &aStack_3ab);
  std::wstring::wstring
            ((wstring_conflict *)(::gRESOURCE_GROUP_FILE_LOCATIONS + 0x18),L"media/units/props/",
             &aStack_3aa);
  __cxa_atexit(::__tcf_1,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_TYPE_NAMES,L"",&aStack_3a9);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 8),L"FIND",&aStack_3a8);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x10),L"KILL NUM",&aStack_3a7);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x18),L"KILL BOSS",&aStack_3a6);
  __cxa_atexit(::__tcf_2,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_DIALOG_TYPE_NAMES,L"ERROR",&aStack_3a5);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 8),L"INTRO",&aStack_3a4);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x10),L"RETURN",&aStack_3a3);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x18),L"COMPLETE",&aStack_3a2);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x20),L"PASSIVE",&aStack_3a1);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x28),L"DETAILS",&aStack_3a0);
  __cxa_atexit(::__tcf_3,0,&__dso_handle);
  std::string::string((string *)::KLayoutFunctionNames,"GUIEXITGAME",&aStack_39f);
  std::string::string((string *)(::KLayoutFunctionNames + 8),"GUIEXITAPPLICATION",&aStack_39e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x10),"GUINEWGAME",&aStack_39d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x18),"GUICONTINUEGAME",&aStack_39c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x20),"GUINEWGAMEMENU",&aStack_39b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x28),"GUICONTINUEGAMEMENU",&aStack_39a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x30),"GUICLOSEMENU",&aStack_399);
  std::string::string((string *)(::KLayoutFunctionNames + 0x38),"GUIBACK",&aStack_398);
  std::string::string((string *)(::KLayoutFunctionNames + 0x40),"GUIDECLINE",&aStack_397);
  std::string::string((string *)(::KLayoutFunctionNames + 0x48),"GUIACCEPT",&aStack_396);
  std::string::string((string *)(::KLayoutFunctionNames + 0x50),"GUIOK",&aStack_395);
  std::string::string((string *)(::KLayoutFunctionNames + 0x58),"GUIPAUSE",&aStack_394);
  std::string::string((string *)(::KLayoutFunctionNames + 0x60),"GUISCROLLUP",&aStack_393);
  std::string::string((string *)(::KLayoutFunctionNames + 0x68),"GUISCROLLDOWN",&aStack_392);
  std::string::string((string *)(::KLayoutFunctionNames + 0x70),"GUISELECT1",&aStack_391);
  std::string::string((string *)(::KLayoutFunctionNames + 0x78),"GUISELECT2",&aStack_390);
  std::string::string((string *)(::KLayoutFunctionNames + 0x80),"GUISELECT3",&aStack_38f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x88),"GUISELECT4",&aStack_38e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x90),"GUISELECT5",&aStack_38d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x98),"GUISELECT6",&aStack_38c);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa0),"GUISELECT7",&aStack_38b);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa8),"GUISELECT8",&aStack_38a);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb0),"GUISELECT9",&aStack_389);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb8),"GUISELECT10",&aStack_388);
  std::string::string((string *)(::KLayoutFunctionNames + 0xc0),"GUISELECT11",&aStack_387);
  std::string::string((string *)(::KLayoutFunctionNames + 200),"GUISELECT12",&aStack_386);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd0),"GUISELECT13",&aStack_385);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd8),"GUISELECT14",&aStack_384);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe0),"GUISELECT15",&aStack_383);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe8),"GUISELECT16",&aStack_382);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf0),"GUISELECT17",&aStack_381);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf8),"GUISELECT18",&aStack_380);
  std::string::string((string *)(::KLayoutFunctionNames + 0x100),"GUISELECT19",&aStack_37f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x108),"GUISELECT20",&aStack_37e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x110),"GUISELECT21",&aStack_37d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x118),"GUISELECT22",&aStack_37c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x120),"GUISELECT23",&aStack_37b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x128),"GUISELECT24",&aStack_37a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x130),"GUISELECT25",&aStack_379);
  std::string::string((string *)(::KLayoutFunctionNames + 0x138),"GUISELECT26",&aStack_378);
  std::string::string((string *)(::KLayoutFunctionNames + 0x140),"GUISELECT27",&aStack_377);
  std::string::string((string *)(::KLayoutFunctionNames + 0x148),"GUISELECT28",&aStack_376);
  std::string::string((string *)(::KLayoutFunctionNames + 0x150),"GUISELECT29",&aStack_375);
  std::string::string((string *)(::KLayoutFunctionNames + 0x158),"GUISELECT30",&aStack_374);
  std::string::string((string *)(::KLayoutFunctionNames + 0x160),"GUISELECT31",&aStack_373);
  std::string::string((string *)(::KLayoutFunctionNames + 0x168),"GUISELECT32",&aStack_372);
  std::string::string((string *)(::KLayoutFunctionNames + 0x170),"GUISELECT33",&aStack_371);
  std::string::string((string *)(::KLayoutFunctionNames + 0x178),"GUISELECT34",&aStack_370);
  std::string::string((string *)(::KLayoutFunctionNames + 0x180),"GUISELECT35",&aStack_36f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x188),"GUISELECT36",&aStack_36e);
  std::string::string((string *)(::KLayoutFunctionNames + 400),"GUISELECT37",&aStack_36d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x198),"GUISELECT38",&aStack_36c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a0),"GUISELECT39",&aStack_36b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a8),"GUISELECT40",&aStack_36a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b0),"GUISELECT41",&aStack_369);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b8),"GUISELECT42",&aStack_368);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c0),"GUISELECT43",&aStack_367);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c8),"GUISELECT44",&aStack_366);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d0),"GUISELECT45",&aStack_365);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d8),"GUISELECT46",&aStack_364);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e0),"GUISELECT47",&aStack_363);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e8),"GUISELECT48",&aStack_362);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f0),"GUISELECT49",&aStack_361);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f8),"GUISELECT50",&aStack_360);
  std::string::string((string *)(::KLayoutFunctionNames + 0x200),"GUISELECTA",&aStack_35f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x208),"GUISELECTB",&aStack_35e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x210),"GUISELECTC",&aStack_35d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x218),"GUISELECTD",&aStack_35c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x220),"GUIFEEDPET",&aStack_35b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x228),"GUIPETPASSIVE",&aStack_35a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x230),"GUIPETAGGRESSIVE",&aStack_359);
  std::string::string((string *)(::KLayoutFunctionNames + 0x238),"GUIPETDEFENSIVE",&aStack_358);
  std::string::string((string *)(::KLayoutFunctionNames + 0x240),"GUITOGGLEINVENTORY",&aStack_357);
  std::string::string((string *)(::KLayoutFunctionNames + 0x248),"GUITOGGLEQUESTS",&aStack_356);
  std::string::string((string *)(::KLayoutFunctionNames + 0x250),"GUITOGGLESTATS",&aStack_355);
  std::string::string((string *)(::KLayoutFunctionNames + 600),"GUITOGGLESKILLS",&aStack_354);
  std::string::string((string *)(::KLayoutFunctionNames + 0x260),"GUITOGGLEPERKS",&aStack_353);
  std::string::string((string *)(::KLayoutFunctionNames + 0x268),"GUITOGGLEJOURNAL",&aStack_352);
  std::string::string((string *)(::KLayoutFunctionNames + 0x270),"GUITOGGLEPET",&aStack_351);
  std::string::string((string *)(::KLayoutFunctionNames + 0x278),"GUITOGGLEAUTOMAP",&aStack_350);
  std::string::string((string *)(::KLayoutFunctionNames + 0x280),"GUITOGGLEOPTIONS",&aStack_34f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x288),"GUITOGGLEITEMNAMES",&aStack_34e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x290),"GUIAUTOMAPZOOMIN",&aStack_34d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x298),"GUIAUTOMAPZOOMOUT",&aStack_34c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a0),"GUILEVELUP",&aStack_34b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a8),"GUISTATSUP",&aStack_34a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b0),"GUISKILLUP",&aStack_349);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b8),"GUIPET1",&aStack_348);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c0),"GUIPET2",&aStack_347);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c8),"GUIPET3",&aStack_346);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d0),"GUIDELETE1",&aStack_345);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d8),"GUIDELETE2",&aStack_344);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e0),"GUIDELETE3",&aStack_343);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e8),"GUIDELETE4",&aStack_342);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f0),"GUISETTINGSMENU",&aStack_341);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f8),"GUIPETSELL",&aStack_340);
  std::string::string((string *)(::KLayoutFunctionNames + 0x300),"NONE",&aStack_33f);
  __cxa_atexit(::__tcf_4,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSOUNDBANK_STRINGS,L"STEP_SOUND",&aStack_33e);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 8),L"STRIKE_SOUND",&aStack_33d);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x10),L"PHYSICALHIT_SOUND",&aStack_33c);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x18),L"ICEHIT_SOUND",&aStack_33b);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x20),L"FIREHIT_SOUND",&aStack_33a);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x28),L"ELECTRICHIT_SOUND",&aStack_339);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x30),L"POISONHIT_SOUND",&aStack_338);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x38),L"SHIELDBLOCK",&aStack_337);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x40),L"BLOCK",&aStack_336);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x48),L"CRITICAL_SOUND",&aStack_335);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x50),L"ATTACK_SOUND",&aStack_334);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x58),L"IDLE_SOUND",&aStack_333)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x60),L"DEATH_SOUND",&aStack_332);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x68),L"ROAR_SOUND",&aStack_331)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x70),L"FLEE_SOUND",&aStack_330)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x78),L"MISS_SOUND",&aStack_32f)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x80),L"FALL_SOUND",&aStack_32e)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x88),L"LAND_SOUND",&aStack_32d)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x90),L"TAKE_SOUND",&aStack_32c)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x98),L"SPAWN_SOUND",&aStack_32b);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa0),L"USE_SOUND",&aStack_32a);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa8),L"EQUIP_SOUND",&aStack_329);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb0),L"OPENMENU_SOUND",&aStack_328);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb8),L"BUY_SOUND",&aStack_327);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xc0),L"ERROR_SOUND",&aStack_326);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 200),L"LEVELUP_SOUND",&aStack_325);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd0),L"EFFORT_SOUND",&aStack_324);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd8),L"SPENDPOINT_SOUND",&aStack_323);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe0),L"PORTALENTER_SOUND",&aStack_322);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe8),L"POERTALEXIT_SOUND",&aStack_321);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf0),L"SKILLASSIGN_SOUND",&aStack_320);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf8),L"QUESTRECEIVED_SOUND",&aStack_31f);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x100),L"QUESTCOMPLETED_SOUND",&aStack_31e)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x108),L"LOWMANA_SOUND",&aStack_31d);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x110),L"MISSILEREFLECT_SOUND",&aStack_31c)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x118),L"BADEFFECT_SOUND",&aStack_31b);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x120),L"GOODEFFECT_SOUND",&aStack_31a);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x128),L"NPCDIALOG_SOUND",&aStack_319);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x130),L"NPCGREET",&aStack_318);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x138),L"NPCBYE",&aStack_317);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x140),L"NPCPURCHASE",&aStack_316);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x148),L"NPCSELL",&aStack_315);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x150),L"VOICEPETINVENTORYFULL_SOUND",
             &aStack_314);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x158),L"VOICEPETDEPARTED_SOUND",
             &aStack_313);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x160),L"VOICEPETRETURNED_SOUND",
             &aStack_312);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x168),L"VOICEPETFLED_SOUND",&aStack_311);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x170),L"VOICEPETLEVELUP_SOUND",&aStack_310
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x178),L"VOICEINVENTORYFULL_SOUND",
             &aStack_30f);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x180),L"VOICEINSUFFICIENTGOLD_SOUND",
             &aStack_30e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x188),L"VOICEIMPOSSIBLE_SOUND",&aStack_30d
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 400),L"VOICECANTCAST_SOUND",&aStack_30c);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x198),L"VOICECANTCASTHERE_SOUND",
             &aStack_30b);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a0),L"VOICEHEALTHLOW_SOUND",&aStack_30a)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a8),L"VOICEMANALOW_SOUND",&aStack_309);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b0),L"VOICETRAPSPRUNG_SOUND",&aStack_308
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b8),L"VOICEREFRESHED_SOUND",&aStack_307)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c0),L"VOICEPOWERFUL_SOUND",&aStack_306);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c8),L"VOICEHEALTHY_SOUND",&aStack_305);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d0),L"VOICEILL_SOUND",&aStack_304);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d8),L"VOICEPOISONED_SOUND",&aStack_303);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e0),L"VOICELEVELUP_SOUND",&aStack_302);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e8),L"VOICEFAMEUP_SOUND",&aStack_301);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f0),L"VOICESKILLUP_SOUND",&aStack_300);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f8),L"VOICEFORTUNEGOOD_SOUND",
             &aStack_2ff);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x200),L"VOICEFORTUNEBAD_SOUND",&aStack_2fe
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x208),L"VOICESPELLLEARNED_SOUND",
             &aStack_2fd);
  ::KSOUNDBANK_STRINGS._528_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_5,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KALIGNMENT_STRINGS,L"NEUTRAL",&aStack_2fc);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 8),L"GOOD",&aStack_2fb);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x10),L"EVIL",&aStack_2fa);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x18),L"ALL",&aStack_2f9);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x20),L"BERSERK",&aStack_2f8);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x28),L"EVILBERSERK",&aStack_2f7);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x30),L"GOODBERSERK",&aStack_2f6);
  __cxa_atexit(::__tcf_6,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KAITYPE_STRINGS,L"NORMAL",&aStack_2f5);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 8),L"RANGEDDEFENDER",&aStack_2f4);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x10),L"DEFENDER",&aStack_2f3);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x18),L"RANGEDCASTER",&aStack_2f2);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x20),L"CIRCLER",&aStack_2f1);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x28),L"RESURRECTER",&aStack_2f0);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x30),L"DUMMY",&aStack_2ef);
  __cxa_atexit(::__tcf_7,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gDAMAGE_TYPES,L"Physical",&aStack_2ee);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 8),L"Magical",&aStack_2ed);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x10),L"Fire",&aStack_2ec);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x18),L"Ice",&aStack_2eb);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x20),L"Electric",&aStack_2ea);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x28),L"Poison",&aStack_2e9);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x30),L"All",&aStack_2e8);
  __cxa_atexit(::__tcf_8,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::gTARGET_TYPES,L"USER",&aStack_2e7);
  std::wstring::wstring((wstring_conflict *)&DAT_0148aa28,L"ITEM",&aStack_2e6);
  __cxa_atexit(::__tcf_9,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSFXTypeName,L"STATIONARYTARGET",&aStack_2e5);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 8),L"STATIONARYOWNER",&aStack_2e4);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x10),L"STATIONARY",&aStack_2e3);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x18),L"STATIONARYPORTAL",&aStack_2e2)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x20),L"BEAM",&aStack_2e1);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x28),L"FOLLOWOWNER",&aStack_2e0);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x30),L"FOLLOWTARGET",&aStack_2df);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x38),L"PROJECTILELOCATION",&aStack_2de);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x40),L"PROJECTILECHARACTER",&aStack_2dd);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x48),L"PROJECTILELOCATIONERRATIC",&aStack_2dc);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x50),L"PROJECTILECHARACTERERRATIC",&aStack_2db);
  __cxa_atexit(::__tcf_10,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KCharacterNames,L"NA",&aStack_2da);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 8),L"NA",&aStack_2d9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x10),L"NA",&aStack_2d8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x18),L"NA",&aStack_2d7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x20),L"NA",&aStack_2d6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x28),L"NA",&aStack_2d5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x30),L"NA",&aStack_2d4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x38),L"NA",&aStack_2d3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x40),L"Bksp",&aStack_2d2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x48),L"Tab",&aStack_2d1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x50),L"NA",&aStack_2d0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x58),L"NA",&aStack_2cf);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x60),L"Ctr",&aStack_2ce);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x68),L"Ret",&aStack_2cd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x70),L"NA",&aStack_2cc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x78),L"NA",&aStack_2cb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x80),L"Shift",&aStack_2ca);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x88),L"Ctrl",&aStack_2c9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x90),L"Alt",&aStack_2c8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x98),L"Tab",&aStack_2c7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa0),L"NA",&aStack_2c6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa8),L"NA",&aStack_2c5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb0),L"NA",&aStack_2c4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb8),L"NA",&aStack_2c3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xc0),L"NA",&aStack_2c2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 200),L"NA",&aStack_2c1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd0),L"NA",&aStack_2c0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd8),L"NA",&aStack_2bf);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe0),L"NA",&aStack_2be);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe8),L"NA",&aStack_2bd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf0),L"NA",&aStack_2bc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf8),L"NA",&aStack_2bb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x100),L"space",&aStack_2ba);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x108),L"pgup",&aStack_2b9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x110),L"pgdn",&aStack_2b8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x118),L"end",&aStack_2b7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x120),L"home",&aStack_2b6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x128),L"left arrow",&aStack_2b5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x130),L"up arrow",&aStack_2b4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x138),L"right arrow",&aStack_2b3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x140),L"down arrow",&aStack_2b2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x148),L")",&aStack_2b1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x150),L"*",&aStack_2b0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x158),L"+",&aStack_2af);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x160),L",",&aStack_2ae);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x168),L"ins",&aStack_2ad);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x170),L"del",&aStack_2ac);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x178),L"/",&aStack_2ab);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x180),L"0",&aStack_2aa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x188),L"1",&aStack_2a9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 400),L"2",&aStack_2a8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x198),L"3",&aStack_2a7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a0),L"4",&aStack_2a6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a8),L"5",&aStack_2a5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b0),L"6",&aStack_2a4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b8),L"7",&aStack_2a3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c0),L"8",&aStack_2a2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c8),L"9",&aStack_2a1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d0),L":",&aStack_2a0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d8),L";",&aStack_29f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e0),L"<",&aStack_29e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e8),L"=",&aStack_29d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f0),L">",&aStack_29c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f8),L"?",&aStack_29b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x200),L"@",&aStack_29a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x208),L"a",&aStack_299);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x210),L"b",&aStack_298);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x218),L"c",&aStack_297);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x220),L"d",&aStack_296);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x228),L"e",&aStack_295);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x230),L"NA",&aStack_294);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x238),L"g",&aStack_293);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x240),L"h",&aStack_292);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x248),L"i",&aStack_291);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x250),L"j",&aStack_290);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 600),L"k",&aStack_28f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x260),L"l",&aStack_28e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x268),L"m",&aStack_28d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x270),L"n",&aStack_28c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x278),L"o",&aStack_28b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x280),L"p",&aStack_28a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x288),L"NA",&aStack_289);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x290),L"r",&aStack_288);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x298),L"s",&aStack_287);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a0),L"t",&aStack_286);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a8),L"u",&aStack_285);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b0),L"v",&aStack_284);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b8),L"w",&aStack_283);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c0),L"x",&aStack_282);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c8),L"y",&aStack_281);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d0),L"z",&aStack_280);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d8),L"[",&aStack_27f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e0),L"\\",&aStack_27e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e8),L"]",&aStack_27d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f0),L"^",&aStack_27c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f8),L"_",&aStack_27b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x300),L"NUM 0",&aStack_27a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x308),L"NUM 1",&aStack_279);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x310),L"NUM 2",&aStack_278);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x318),L"NUM 3",&aStack_277);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 800),L"NUM 4",&aStack_276);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x328),L"NUM 5",&aStack_275);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x330),L"NUM 6",&aStack_274);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x338),L"NUM 7",&aStack_273);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x340),L"NUM 8",&aStack_272);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x348),L"NUM 9",&aStack_271);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x350),L"*",&aStack_270);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x358),L"+",&aStack_26f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x360),L"NA",&aStack_26e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x368),L"-",&aStack_26d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x370),L"NA",&aStack_26c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x378),L"F1",&aStack_26b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x380),L"F2",&aStack_26a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x388),L"F3",&aStack_269);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x390),L"F4",&aStack_268);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x398),L"F5",&aStack_267);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a0),L"F6",&aStack_266);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a8),L"F7",&aStack_265);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b0),L"F8",&aStack_264);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b8),L"F9",&aStack_263);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c0),L"F10",&aStack_262);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c8),L"F11",&aStack_261);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d0),L"F12",&aStack_260);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d8),L"{",&aStack_25f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3e0),L"|",&aStack_25e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 1000),L"}",&aStack_25d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f0),L"~",&aStack_25c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f8),L";",&aStack_25b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x400),L"=",&aStack_25a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x408),L".",&aStack_259);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x410),L"-",&aStack_258);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x418),L",",&aStack_257);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x420),L"/",&aStack_256);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x428),L"`",&aStack_255);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x430),L"[",&aStack_254);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x438),L"\\",&aStack_253);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x440),L"]",&aStack_252);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x448),L"\'",&aStack_251);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x450),L"NA",&aStack_250);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x458),L"NA",&aStack_24f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x460),L"NA",&aStack_24e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x468),L"NA",&aStack_24d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x470),L"NA",&aStack_24c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x478),L"NA",&aStack_24b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x480),L"NA",&aStack_24a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x488),L"NA",&aStack_249);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x490),L"NA",&aStack_248);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x498),L"NA",&aStack_247);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a0),L"NA",&aStack_246);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a8),L"NA",&aStack_245);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b0),L"NA",&aStack_244);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b8),L"NA",&aStack_243);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c0),L"NA",&aStack_242);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c8),L"NA",&aStack_241);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d0),L"NA",&aStack_240);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d8),L"NA",&aStack_23f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e0),L"NA",&aStack_23e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e8),L"NA",&aStack_23d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f0),L"NA",&aStack_23c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f8),L"NA",&aStack_23b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x500),L"NA",&aStack_23a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x508),L"NA",&aStack_239);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x510),L"NA",&aStack_238);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x518),L"NA",&aStack_237);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x520),L"NA",&aStack_236);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x528),L"NA",&aStack_235);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x530),L"NA",&aStack_234);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x538),L"NA",&aStack_233);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x540),L"NA",&aStack_232);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x548),L"NA",&aStack_231);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x550),L"NA",&aStack_230);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x558),L"NA",&aStack_22f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x560),L"NA",&aStack_22e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x568),L"NA",&aStack_22d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x570),L"NA",&aStack_22c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x578),L"NA",&aStack_22b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x580),L"NA",&aStack_22a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x588),L"NA",&aStack_229);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x590),L"NA",&aStack_228);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x598),L"NA",&aStack_227);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a0),L"NA",&aStack_226);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a8),L"NA",&aStack_225);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b0),L"NA",&aStack_224);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b8),L"NA",&aStack_223);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c0),L"NA",&aStack_222);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c8),L"NA",&aStack_221);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d0),L";",&aStack_220);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d8),L"=",&aStack_21f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e0),L",",&aStack_21e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e8),L"-",&aStack_21d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f0),L".",&aStack_21c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f8),L"/",&aStack_21b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x600),L"`",&aStack_21a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x608),L"NA",&aStack_219);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x610),L"NA",&aStack_218);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x618),L"NA",&aStack_217);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x620),L"NA",&aStack_216);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x628),L"NA",&aStack_215);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x630),L"NA",&aStack_214);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x638),L"NA",&aStack_213);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x640),L"NA",&aStack_212);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x648),L"NA",&aStack_211);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x650),L"NA",&aStack_210);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x658),L"NA",&aStack_20f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x660),L"NA",&aStack_20e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x668),L"NA",&aStack_20d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x670),L"NA",&aStack_20c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x678),L"NA",&aStack_20b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x680),L"NA",&aStack_20a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x688),L"NA",&aStack_209);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x690),L"NA",&aStack_208);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x698),L"NA",&aStack_207);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a0),L"NA",&aStack_206);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a8),L"NA",&aStack_205);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b0),L"NA",&aStack_204);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b8),L"NA",&aStack_203);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c0),L"NA",&aStack_202);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c8),L"NA",&aStack_201);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d0),L"NA",&aStack_200);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d8),L"[",&aStack_1ff);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e0),L"\\",&aStack_1fe);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e8),L"]",&aStack_1fd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f0),L"\'",&aStack_1fc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f8),L"NA",&aStack_1fb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x700),L"NA",&aStack_1fa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x708),L"NA",&aStack_1f9);
  __cxa_atexit(::__tcf_11,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEffect_Activation_Names,L"PASSIVE",&aStack_1f8);
  std::wstring::wstring((wstring_conflict *)(::gEffect_Activation_Names + 8),L"DYNAMIC",&aStack_1f7)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gEffect_Activation_Names + 0x10),L"TRANSFER",&aStack_1f6);
  __cxa_atexit(::__tcf_12,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEFFECT_STAT_MODIFIER_NAMES,L"MELEE",&aStack_1f5);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 8),L"RANGED",&aStack_1f4);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x10),L"DEFENSE",&aStack_1f3);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x18),L"MAGIC",&aStack_1f2);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x20),L"LEVEL",&aStack_1f1);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x28),L"OWNERLEVEL",&aStack_1f0);
  __cxa_atexit(::__tcf_13,0,&__dso_handle);
  std::string::string((string *)::gEFFECT_STAT_MODIFIER_ICON_NAMES,"iconmelee",&aStack_1ef);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 8),"iconranged",&aStack_1ee);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x10),"icondefense",
                      &aStack_1ed);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x18),"iconmagic",&aStack_1ec)
  ;
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x20),"iconmagic",&aStack_1eb)
  ;
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x28),"iconmagic",&aStack_1ea)
  ;
  __cxa_atexit(::__tcf_14,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES,"tag_righthand",&aStack_1e9);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 8),"tag_lefthand",&aStack_1e8);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x10),"",&aStack_1e7);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x18),"Bip01 Head",&aStack_1e6);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x20),"",&aStack_1e5);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x28),"Bip01 L Clavicle",&aStack_1e4);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x30),"",&aStack_1e3);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x38),"",&aStack_1e2);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x40),"",&aStack_1e1);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x48),"",&aStack_1e0);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x50),"",&aStack_1df);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x58),"tag_leftarm",&aStack_1de);
  __cxa_atexit(::__tcf_15,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES_SECONDARY,"",&aStack_1dd);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 8),"",&aStack_1dc);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x10),"",&aStack_1db);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x18),"",&aStack_1da);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x20),"",&aStack_1d9);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x28),"Bip01 R Clavicle",
                      &aStack_1d8);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x30),"",&aStack_1d7);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x38),"",&aStack_1d6);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x40),"",&aStack_1d5);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x48),"",&aStack_1d4);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x50),"",&aStack_1d3);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x58),"",&aStack_1d2);
  __cxa_atexit(::__tcf_16,0,&__dso_handle);
  std::string::string((string *)::KEquipmentIconName,"EquipLeftHand",&aStack_1d1);
  std::string::string((string *)(::KEquipmentIconName + 8),"EquipRightHand",&aStack_1d0);
  std::string::string((string *)(::KEquipmentIconName + 0x10),"EquipGloves",&aStack_1cf);
  std::string::string((string *)(::KEquipmentIconName + 0x18),"EquipHelm",&aStack_1ce);
  std::string::string((string *)(::KEquipmentIconName + 0x20),"EquipChest",&aStack_1cd);
  std::string::string((string *)(::KEquipmentIconName + 0x28),"EquipShoulder",&aStack_1cc);
  std::string::string((string *)(::KEquipmentIconName + 0x30),"EquipBoots",&aStack_1cb);
  std::string::string((string *)(::KEquipmentIconName + 0x38),"EquipBelt",&aStack_1ca);
  std::string::string((string *)(::KEquipmentIconName + 0x40),"EquipRing1",&aStack_1c9);
  std::string::string((string *)(::KEquipmentIconName + 0x48),"EquipRing2",&aStack_1c8);
  std::string::string((string *)(::KEquipmentIconName + 0x50),"EquipAmulet",&aStack_1c7);
  std::string::string((string *)(::KEquipmentIconName + 0x58),"",&aStack_1c6);
  __cxa_atexit(::__tcf_17,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames,L"CHEST",&aStack_1c5);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 8),L"GLOVES",&aStack_1c4);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x10),L"BOOTS",&aStack_1c3);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x18),L"HELMET",&aStack_1c2);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x20),L"SHOULDERS",&aStack_1c1);
  __cxa_atexit(::__tcf_18,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames2,L"",&aStack_1c0);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 8),L"",&aStack_1bf);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x10),L"",&aStack_1be);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x18),L"FACE",&aStack_1bd);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x20),L"",&aStack_1bc);
  __cxa_atexit(::__tcf_19,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)OGRE_UTILITIES::gPRIMITIVE_NAMES,L"SPHERE",&aStack_1bb);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 8),L"BOX",&aStack_1ba);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x10),L"PLANE",&aStack_1b9);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x18),L"CYLINDER",&aStack_1b8);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x20),L"CONE",&aStack_1b7);
  std::wstring::wstring
            ((wstring_conflict *)(OGRE_UTILITIES::gPRIMITIVE_NAMES + 0x28),L"ARROW",&aStack_1b6);
  __cxa_atexit(::__tcf_20,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gKEYFRAME_TYPES,L"HIT",&aStack_1b5);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 8),L"BLENDIN",&aStack_1b4);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x10),L"BLENDOUT",&aStack_1b3);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x18),L"PLAYSOUND",&aStack_1b2);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x20),L"SPAWNPARTICLE",&aStack_1b1)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x28),L"SPAWNPARTICLE_STOP_ON_DEATH",
             &aStack_1b0);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x30),L"FOOTSTEP",&aStack_1af);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x38),L"SHOWWEAPONTRAIL",&aStack_1ae);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x40),L"HIDEWEAPONTRAIL",&aStack_1ad);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x48),L"ATTACKSOUND",&aStack_1ac);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x50),L"ENABLECOLLISION",&aStack_1ab);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x58),L"DISABLECOLLISION",&aStack_1aa);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x60),L"REMOVEPARTICLES",&aStack_1a9);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x68),L"REMOVEANIMATIONPARTICLES",&aStack_1a8)
  ;
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x70),L"CAMERASHAKE",&aStack_1a7);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x78),L"ATTACKEND",&aStack_1a6);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x80),L"UNTARGETABLE",&aStack_1a5);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x88),L"TARGETABLE",&aStack_1a4);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0x90),L"DAMPVELOCITY",&aStack_1a3);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0x98),L"UNDAMPVELOCITY",&aStack_1a2);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xa0),L"SHOWWEAPONS",&aStack_1a1);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xa8),L"HIDEWEAPONS",&aStack_1a0);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xb0),L"HIDEMESH",&aStack_19f);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xb8),L"SHOWMESH",&aStack_19e);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xc0),L"FADEOUTMESH",&aStack_19d);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 200),L"FADEINMESH",&aStack_19c);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0xd0),L"CAMERASHAKE_NO_FALLOFF",&aStack_19b);
  std::wstring::wstring
            ((wstring_conflict *)(::gKEYFRAME_TYPES + 0xd8),L"PLAYSOUND_NO_FALLOFF",&aStack_19a);
  std::wstring::wstring((wstring_conflict *)(::gKEYFRAME_TYPES + 0xe0),L"HITTWO",&aStack_199);
  __cxa_atexit(::__tcf_21,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KContextTipNames,L"TIP_INVENTORY",&aStack_198);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 8),L"TIP_UNIDENTIFIED",&aStack_197);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x10),L"TIP_INVENTORYFULL",&aStack_196);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x18),L"TIP_HEALTHLOW",&aStack_195);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x20),L"TIP_MANALOW",&aStack_194);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x28),L"TIP_MERCHANT",&aStack_193)
  ;
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x30),L"TIP_LEVELUP",&aStack_192);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x38),L"TIP_STATS",&aStack_191);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x40),L"TIP_SPELL",&aStack_190);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x48),L"TIP_WELCOME",&aStack_18f);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x50),L"TIP_SOCKETABLE",&aStack_18e);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x58),L"TIP_PETFLEE",&aStack_18d);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x60),L"TIP_GAMBLE",&aStack_18c);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x68),L"TIP_ENCHANT",&aStack_18b);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x70),L"TIP_TRANSMUTE",&aStack_18a);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x78),L"TIP_PETINVENTORY",&aStack_189);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x80),L"TIP_PETINVENTORYFULL",&aStack_188);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x88),L"TIP_STASH",&aStack_187);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x90),L"TIP_FISHING",&aStack_186);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x98),L"TIP_SPELLFIND",&aStack_185);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xa0),L"TIP_QUESTCOMPLETE",&aStack_184);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xa8),L"TIP_SHAREDSTASH",&aStack_183);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xb0),L"TIP_HOWTOATTACK",&aStack_182);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xb8),L"TIP_TEMP5",&aStack_181);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xc0),L"TIP_TEMP6",&aStack_180);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 200),L"TIP_TEMP7",&aStack_17f);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xd0),L"TIP_TEMP8",&aStack_17e);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xd8),L"TIP_TEMP9",&aStack_17d);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xe0),L"TIP_TEMP10",&aStack_17c);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xe8),L"TIP_TEMP11",&aStack_17b);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xf0),L"TIP_TEMP12",&aStack_17a);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xf8),L"TIP_TEMP13",&aStack_179);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x100),L"TIP_TEMP14",&aStack_178);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x108),L"TIP_TEMP15",&aStack_177);
  __cxa_atexit(::__tcf_22,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&gTRIGGER_STATE_NAMES,L"One",&aStack_176);
  std::wstring::wstring((wstring_conflict *)&DAT_0148b658,L"Two",&aStack_175);
  __cxa_atexit(::__tcf_23,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)gTRIGGER_LOOP_TYPE_NAMES,L"No Loop",&aStack_174);
  std::wstring::wstring((wstring_conflict *)(gTRIGGER_LOOP_TYPE_NAMES + 8),L"Cycle",&aStack_173);
  std::wstring::wstring
            ((wstring_conflict *)(gTRIGGER_LOOP_TYPE_NAMES + 0x10),L"Back and Forth",&aStack_172);
  __cxa_atexit(::__tcf_24,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_EVENT_TYPE_NAMES,L"EVENT_START",&aStack_171);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 8),L"EVENT_END",&aStack_170);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x10),L"EVENT_TRIGGER",&aStack_16f);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x18),L"EVENT_TRIGGER_TWO",&aStack_16e
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x20),L"EVENT_UNITHIT",&aStack_16d);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x28),L"EVENT_UNITDIE",&aStack_16c);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x30),L"EVENT_MISSILEHIT",&aStack_16b)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x38),L"EVENT_MISSILEDIE",&aStack_16a)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x40),L"EVENT_DIEBYEFFECT",&aStack_169
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x48),L"EVENT_CASTERDIE",&aStack_168);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_EVENT_TYPE_NAMES + 0x50),L"EVENT_UNIT_CREATE",&aStack_167
            );
  __cxa_atexit(::__tcf_25,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_TARGET_TYPE_NAMES,L"NONE",&aStack_166);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 8),L"POSITION",&aStack_165);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x10),L"TARGET",&aStack_164);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x18),L"SELF",&aStack_163)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x20),L"EVERYBODY",&aStack_162);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x28),L"POSITIONRANDOM",&aStack_161);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x30),L"POSITIONFLEE",&aStack_160);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x38),L"ITEM",&aStack_15f)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x40),L"UNIDENTIFIEDITEM",&aStack_15e
            );
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x48),L"PETS",&aStack_15d)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x50),L"SELFANDPETS",&aStack_15c);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TARGET_TYPE_NAMES + 0x58),L"TARGET_POS",&aStack_15b);
  __cxa_atexit(::__tcf_26,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_ACTIVATION_TYPE_NAMES,L"ANY",&aStack_15a);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 8),L"PROC",&aStack_159);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 0x10),L"WEAPON",&aStack_158);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 0x18),L"NORMAL",&aStack_157);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_ACTIVATION_TYPE_NAMES + 0x20),L"PASSIVE",&aStack_156);
  __cxa_atexit(::__tcf_27,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_TYPE_NAMES,L"SKILL",&aStack_155);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TYPE_NAMES + 8),L"OFFENSIVE",&aStack_154);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TYPE_NAMES + 0x10),L"DEFENSIVE",&aStack_153);
  std::wstring::wstring((wstring_conflict *)(::gSKILL_TYPE_NAMES + 0x18),L"CHARM",&aStack_152);
  ::gSKILL_TYPE_NAMES._32_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_28,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_TYPE_DISPLAY_NAMES,L"Class Skill",&aStack_151);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TYPE_DISPLAY_NAMES + 8),L"Offensive Spell",&aStack_150);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TYPE_DISPLAY_NAMES + 0x10),L"Defensive Spell",&aStack_14f
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_TYPE_DISPLAY_NAMES + 0x18),L"Charm Spell",&aStack_14e);
  ::gSKILL_TYPE_DISPLAY_NAMES._32_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_29,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSKILL_BONE_ATTACHMENT_NAMES,L"",&aStack_14d);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 8),L"CENTER",&aStack_14c);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x10),L"HEAD",&aStack_14b);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x18),L"RIGHTHAND",&aStack_14a);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x20),L"LEFTHAND",&aStack_149);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x28),L"RIGHTSHOULDER",
             &aStack_148);
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x30),L"LEFTSHOULDER",&aStack_147
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gSKILL_BONE_ATTACHMENT_NAMES + 0x38),L"POSITION",&aStack_146);
  __cxa_atexit(::__tcf_30,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::g_LEVELLAYOUT_CREATION_NAMES,L"MONSTERSPAWNCLASS",&aStack_145);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 8),L"CHAMPIONSPAWNCLASS",
             &aStack_144);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x10),L"PROPSPAWNCLASS",
             &aStack_143);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x18),L"NPCSPAWNCLASS",
             &aStack_142);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x20),L"CREEPSPAWNCLASS",
             &aStack_141);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x28),L"GOLD",&aStack_140);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x30),L"FISHSPAWNCLASS",
             &aStack_13f);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x38),L"FORMATIONS",&aStack_13e);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x40),L"QUESTMONSTERSPAWNCLASS",
             &aStack_13d);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x48),L"QUESTITEMSPAWNCLASS",
             &aStack_13c);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x50),L"QUESTCHAMPIONSPAWNCLASS",
             &aStack_13b);
  __cxa_atexit(::__tcf_31,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES,
             L"MONSTERSPAWNCLASSRANDOMIZED",&aStack_13a);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 8),
             L"CHAMPIONSPAWNCLASSRANDOMIZED",&aStack_139);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x10),
             L"PROPSPAWNCLASSRANDOMIZED",&aStack_138);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x18),
             L"NPCSPAWNCLASSRANDOMIZED",&aStack_137);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x20),
             L"CREEPSPAWNCLASSRANDOMIZED",&aStack_136);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x28),
             L"GOLDRANDOMIZED",&aStack_135);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x30),
             L"FISHSPAWNCLASSRANDOMIZED",&aStack_134);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x38),
             L"FORMATIONSRANDOMIZED",&aStack_133);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x40),
             L"QUESTMONSTERSPAWNCLASSRANDOMIZED",&aStack_132);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x48),
             L"QUESTITEMSPAWNCLASSRANDOMIZED",&aStack_131);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x50),
             L"QUESTCHAMPIONSPAWNCLASSRANDOMIZED",&aStack_130);
  __cxa_atexit(::__tcf_32,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::g_LEVELLAYOUT_CREATION_PATHNODES,L"MONSTERS_PER_METER_MIN",
             &aStack_12f);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 8),L"MONSTERS_PER_METER_MAX",
             &aStack_12e);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x10),
             L"CHAMPIONS_PER_METER_MIN",&aStack_12d);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x18),
             L"CHAMPIONS_PER_METER_MAX",&aStack_12c);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x20),L"PROPS_PER_METER_MIN",
             &aStack_12b);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x28),L"PROPS_PER_METER_MAX",
             &aStack_12a);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x30),L"NPCS_PER_METER_MIN",
             &aStack_129);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x38),L"NPCS_PER_METER_MAX",
             &aStack_128);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x40),L"CREEPS_PER_METER_MIN"
             ,&aStack_127);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x48),L"CREEPS_PER_METER_MAX"
             ,&aStack_126);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x50),L"GOLD_PER_METER_MIN",
             &aStack_125);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x58),L"GOLD_PER_METER_MAX",
             &aStack_124);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x60),L"FISH_PER_METER_MIN",
             &aStack_123);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x68),L"FISH_PER_METER_MAX",
             &aStack_122);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x70),
             L"FORMATIONS_PER_METER_MIN",&aStack_121);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x78),
             L"FORMATIONS_PER_METER_MAX",&aStack_120);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x80),L"",&aStack_11f);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x88),L"",&aStack_11e);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x90),L"",&aStack_11d);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x98),L"",&aStack_11c);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0xa0),L"",&aStack_11b);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0xa8),L"",&aStack_11a);
  __cxa_atexit(::__tcf_33,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::g_LEVELLAYOUT_CREATION_COUNTS,L"MONSTER_MIN",&aStack_119);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 8),L"MONSTER_MAX",&aStack_118);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x10),L"CHAMPIONS_MIN",
             &aStack_117);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x18),L"CHAMPIONS_MAX",
             &aStack_116);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x20),L"PROPS_MIN",&aStack_115);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x28),L"PPROPS_MAX",&aStack_114)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x30),L"NPCS_MIN",&aStack_113);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x38),L"NPCS_MAX",&aStack_112);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x40),L"CREEPS_MIN",&aStack_111)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x48),L"CREEPS_MAX",&aStack_110)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x50),L"GOLD_MIN",&aStack_10f);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x58),L"GOLD_MAX",&aStack_10e);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x60),L"FISH_MIN",&aStack_10d);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x68),L"FISH_MAX",&aStack_10c);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x70),L"",&aStack_10b);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x78),L"",&aStack_10a);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x80),L"",&aStack_109);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x88),L"",&aStack_108);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x90),L"",&aStack_107);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x98),L"",&aStack_106);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0xa0),L"",&aStack_105);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0xa8),L"",&aStack_104);
  __cxa_atexit(::__tcf_34,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEDITOR_EVENT_NAMES,L"STOP",&aStack_103);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 8),L"PLAY",&aStack_102);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x10),L"RELOAD TILES",&aStack_101);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x18),L"TOGGLE LIGHTING",&aStack_100);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x20),L"SELECT COLLIDABLE",&aStack_ff);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x28),L"PAUSE PARTICLES",&aStack_fe);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x30),L"UNPAUSE PARTICLES",&aStack_fd);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x38),L"COLLISION ALL",&aStack_fc);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x40),L"COLLISION MODELS",&aStack_fb);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x48),L"COLLISION PREFABS",&aStack_fa);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x50),L"COLLISION ROOMPIECES",&aStack_f9);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x58),L"COLLISION ROOMPROPS",&aStack_f8);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x60),L"RELOAD GRAPHS",&aStack_f7);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_EVENT_NAMES + 0x68),L"TOGGLE PLAYER LIGHT",&aStack_f6);
  __cxa_atexit(::__tcf_35,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEDITOR_FLAG_NAMES,L"LOGIC ENABLED",&aStack_f5);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 8),L"INGAME MODE",&aStack_f4);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x10),L"SHOW STATS",&aStack_f3);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x18),L"EDIT POSITION",&aStack_f2);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x20),L"EDIT SCALE",&aStack_f1);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x28),L"EDIT ORIENTATION",&aStack_f0);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x30),L"EDIT NONE",&aStack_ef);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x38),L"SHOW HELPERS",&aStack_ee);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x40),L"SHOW GRID",&aStack_ed);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x48),L"SHOW WORKING PLANE",&aStack_ec);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x50),L"SNAP TO GRID",&aStack_eb);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x58),L"SUSPEND EDITOR",&aStack_ea);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x60),L"LIGHTING VISIBLE",&aStack_e9);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x68),L"RECALCULATE LIGHTING",&aStack_e8);
  std::wstring::wstring((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x70),L"SHOW EDGES",&aStack_e7);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x78),L"UPDATE PARTICLES CIRCLE",&aStack_e6
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_FLAG_NAMES + 0x80),L"SHOW LOGIC OUTPUT",&aStack_e5);
  __cxa_atexit(::__tcf_36,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::gEDITOR_UPDATE_MASKS,L"OBJECT SELECTION CHANGED",&aStack_e4);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 8),L"OBJECT DATA CHANGED",&aStack_e3);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 0x10),L"OBJECTS CREATED",&aStack_e2);
  std::wstring::wstring
            ((wstring_conflict *)(::gEDITOR_UPDATE_MASKS + 0x18),L"REFRESH TREE VIEW",&aStack_e1);
  __cxa_atexit(::__tcf_37,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::g_LAYOUT_TYPE_NAMES,L"NORMAL",&aStack_e0);
  std::wstring::wstring((wstring_conflict *)(::g_LAYOUT_TYPE_NAMES + 8),L"PARTICLE",&aStack_df);
  std::wstring::wstring((wstring_conflict *)(::g_LAYOUT_TYPE_NAMES + 0x10),L"TIMELINE",&aStack_de);
  std::wstring::wstring((wstring_conflict *)(::g_LAYOUT_TYPE_NAMES + 0x18),L"TRIGGER",&aStack_dd);
  __cxa_atexit(::__tcf_38,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)gPROPERTY_NODE_TYPE_NAMES,L"Point of Interest",&aStack_dc);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 8),L"Player Start",&aStack_db);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x10),L"Editor Player Start",
             &aStack_da);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x18),L"No Spawn Region",&aStack_d9);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x20),L"Entrance",&aStack_d8);
  std::wstring::wstring((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x28),L"Exit",&aStack_d7);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x30),L"Jump Down Area",&aStack_d6);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x38),L"Town Portal",&aStack_d5);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x40),L"Path Node Occupation Circle",
             &aStack_d4);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x48),L"Path Node Occupation Box",
             &aStack_d3);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x50),L"Camera Position",&aStack_d2);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x58),L"Camera Target",&aStack_d1);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x60),L"Quest Item",&aStack_d0);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x68),L"Quest Boss",&aStack_cf);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x70),L"Waypoint",&aStack_ce);
  std::wstring::wstring
            ((wstring_conflict *)(gPROPERTY_NODE_TYPE_NAMES + 0x78),L"Waypoint Start",&aStack_cd);
  __cxa_atexit(::__tcf_39,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)gCOUNTER_TYPE_NAMES,L"Activate only once",&aStack_cc);
  std::wstring::wstring
            ((wstring_conflict *)(gCOUNTER_TYPE_NAMES + 8),L"Activate and reset",&aStack_cb);
  std::wstring::wstring
            ((wstring_conflict *)(gCOUNTER_TYPE_NAMES + 0x10),L"Activate on each add",&aStack_ca);
  std::wstring::wstring
            ((wstring_conflict *)(gCOUNTER_TYPE_NAMES + 0x18),L"Activate on each add and reset",
             &aStack_c9);
  std::wstring::wstring
            ((wstring_conflict *)(gCOUNTER_TYPE_NAMES + 0x20),L"Activate on each subtract",
             &aStack_c8);
  std::wstring::wstring
            ((wstring_conflict *)(gCOUNTER_TYPE_NAMES + 0x28),L"Activate on each subtract and reset"
             ,&aStack_c7);
  __cxa_atexit(__tcf_40,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)gRANDOMGROUP_NAMES,L"ALL",&aStack_c6);
  std::wstring::wstring((wstring_conflict *)(gRANDOMGROUP_NAMES + 8),L"Weight",&aStack_c5);
  std::wstring::wstring((wstring_conflict *)(gRANDOMGROUP_NAMES + 0x10),L"Random Chance",&aStack_c4)
  ;
  __cxa_atexit(__tcf_41,0,&__dso_handle);
  ::gUnionOf32BitData._0_4_ = 0;
  ::gUnionOf32BitData._4_4_ = 0;
  ::gUnionOf32BitData._8_4_ = 0;
  std::wstring::wstring
            ((wstring_conflict *)::KEditorObjectPropertyTypeNames,L"NOT VALID",&aStack_c3);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 8),L"NOT SET",&aStack_c2);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x10),L"INTEGER",&aStack_c1);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x18),L"FLOAT",&aStack_c0);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x20),L"UNSIGNED INTEGER",
             &aStack_bf);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x28),L"STRING",&aStack_be);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x30),L"BOOL",&aStack_bd);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x38),L"VECTOR2",&aStack_bc);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x40),L"VECTOR3",&aStack_bb);
  std::wstring::wstring
            ((wstring_conflict *)(::KEditorObjectPropertyTypeNames + 0x48),L"VECTOR4",&aStack_ba);
  __cxa_atexit(__tcf_42,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)gTIMELINE_INTERP_TYPES,L"Linear",&aStack_b9);
  std::wstring::wstring((wstring_conflict *)(gTIMELINE_INTERP_TYPES + 8),L"Linear Round",&aStack_b8)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(gTIMELINE_INTERP_TYPES + 0x10),L"Linear Round Down",&aStack_b7);
  std::wstring::wstring
            ((wstring_conflict *)(gTIMELINE_INTERP_TYPES + 0x18),L"Linear Round Up",&aStack_b6);
  std::wstring::wstring((wstring_conflict *)(gTIMELINE_INTERP_TYPES + 0x20),L"Spline",&aStack_b5);
  std::wstring::wstring
            ((wstring_conflict *)(gTIMELINE_INTERP_TYPES + 0x28),L"Quaternion",&aStack_b4);
  std::wstring::wstring
            ((wstring_conflict *)(gTIMELINE_INTERP_TYPES + 0x30),L"No Interpolation",&aStack_b3);
  std::wstring::wstring
            ((wstring_conflict *)(gTIMELINE_INTERP_TYPES + 0x38),L"Use Timeline Default",&aStack_b2)
  ;
  __cxa_atexit(__tcf_43,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)gTIMELINE_MODIFICATION_TYPE_NAMES,L"None",&aStack_b1);
  std::wstring::wstring
            ((wstring_conflict *)(gTIMELINE_MODIFICATION_TYPE_NAMES + 8),L"Set",&aStack_b0);
  std::wstring::wstring
            ((wstring_conflict *)(gTIMELINE_MODIFICATION_TYPE_NAMES + 0x10),L"Multiply",&aStack_af);
  __cxa_atexit(__tcf_44,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::m_gFileVersionExtension,L".svt",&aStack_ae);
  __cxa_atexit(std::wstring::~wstring,&::m_gFileVersionExtension,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)gANIMATIONPLAYER_TYPE_NAMES,L"PLAYER",&aStack_ad);
  std::wstring::wstring
            ((wstring_conflict *)(gANIMATIONPLAYER_TYPE_NAMES + 8),L"MONSTERS",&aStack_ac);
  std::wstring::wstring
            ((wstring_conflict *)(gANIMATIONPLAYER_TYPE_NAMES + 0x10),L"UNITTYPE",&aStack_ab);
  std::wstring::wstring((wstring_conflict *)(gANIMATIONPLAYER_TYPE_NAMES + 0x18),L"PROP",&aStack_aa)
  ;
  __cxa_atexit(__tcf_45,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gPARTICLE_RENDER_TYPE_NAMES,L"Billboard",&aStack_a9);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 8),L"Billboard Up",&aStack_a8);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x10),L"Billboard Forward",
             &aStack_a7);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x18),L"Billboard Up Camera",
             &aStack_a6);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x20),L"Billboard Forward Camera",
             &aStack_a5);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x28),L"Billboard Self",&aStack_a4
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x30),L"Billboard Common",
             &aStack_a3);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x38),L"Billboard Shape",
             &aStack_a2);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x40),L"Box",&aStack_a1);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x48),L"Sphere",&aStack_a0);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x50),L"Entity",&aStack_9f);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x58),L"EntityWorld",&aStack_9e);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_RENDER_TYPE_NAMES + 0x60),L"RibbonTrail",&aStack_9d);
  __cxa_atexit(__tcf_46,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)&::gPARTICLE_AFFECTOR_FORCE_APPLICATION_TYPES,L"Average",&aStack_9c
            );
  std::wstring::wstring((wstring_conflict *)&DAT_0148be18,L"Add",&aStack_9b);
  __cxa_atexit(__tcf_47,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)&::gPARTICLE_BILLBOARD_ROTATION_TYPES,L"Geometry",&aStack_9a);
  std::wstring::wstring((wstring_conflict *)&DAT_0148be28,L"Texture",&aStack_99);
  __cxa_atexit(__tcf_48,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gPARTICLE_COLLISION_TYPE,L"Stop",&aStack_98);
  std::wstring::wstring((wstring_conflict *)(::gPARTICLE_COLLISION_TYPE + 8),L"Bounce",&aStack_97);
  std::wstring::wstring((wstring_conflict *)(::gPARTICLE_COLLISION_TYPE + 0x10),L"Flow",&aStack_96);
  __cxa_atexit(__tcf_49,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gPARTICLE_INTERSECTION_TYPE,L"Fast",&aStack_95);
  std::wstring::wstring((wstring_conflict *)(::gPARTICLE_INTERSECTION_TYPE + 8),L"Box",&aStack_94);
  ::gPARTICLE_INTERSECTION_TYPE._16_8_ = &DAT_01424558;
  __cxa_atexit(__tcf_50,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS,L"Top Left",&aStack_93);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 8),L"Top Center",
             &aStack_92);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x10),L"Top Right",
             &aStack_91);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x18),L"Center Left",
             &aStack_90);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x20),L"Center",
             &aStack_8f);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x28),L"Center Right",
             &aStack_8e);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x30),L"Bottom Left",
             &aStack_8d);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x38),L"Bottom Center",
             &aStack_8c);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_BILLBOARD_ORIGIN_POSITIONS + 0x40),L"Bottom Right",
             &aStack_8b);
  __cxa_atexit(__tcf_51,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gPARTICLE_MATERIAL_TYPES,L"Alpha",&aStack_8a);
  std::wstring::wstring((wstring_conflict *)(::gPARTICLE_MATERIAL_TYPES + 8),L"Normal",&aStack_89);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_MATERIAL_TYPES + 0x10),L"Additive",&aStack_88);
  std::wstring::wstring
            ((wstring_conflict *)(::gPARTICLE_MATERIAL_TYPES + 0x18),L"Modulate",&aStack_87);
  __cxa_atexit(__tcf_52,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEMITTER_TYPES,L"Point",&aStack_86);
  std::wstring::wstring((wstring_conflict *)(::gEMITTER_TYPES + 8),L"Box",&aStack_85);
  std::wstring::wstring((wstring_conflict *)(::gEMITTER_TYPES + 0x10),L"Circle",&aStack_84);
  std::wstring::wstring((wstring_conflict *)(::gEMITTER_TYPES + 0x18),L"Line",&aStack_83);
  std::wstring::wstring((wstring_conflict *)(::gEMITTER_TYPES + 0x20),L"SphereSurface",&aStack_82);
  __cxa_atexit(__tcf_53,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gPOINT_ORDER_NAMES,L"Clockwise",&aStack_81);
  std::wstring::wstring
            ((wstring_conflict *)(::gPOINT_ORDER_NAMES + 8),L"Counter Clockwise",&aStack_80);
  std::wstring::wstring((wstring_conflict *)(::gPOINT_ORDER_NAMES + 0x10),L"Random",&aStack_7f);
  __cxa_atexit(__tcf_54,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSHAPE_NAMES,L"Angle",&aStack_7e);
  std::wstring::wstring((wstring_conflict *)(::gSHAPE_NAMES + 8),L"Line",&aStack_7d);
  std::wstring::wstring((wstring_conflict *)(::gSHAPE_NAMES + 0x10),L"Sphere",&aStack_7c);
  std::wstring::wstring((wstring_conflict *)(::gSHAPE_NAMES + 0x18),L"Point",&aStack_7b);
  std::wstring::wstring((wstring_conflict *)(::gSHAPE_NAMES + 0x20),L"Box",&aStack_7a);
  __cxa_atexit(__tcf_55,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gSHAPE_DIRECTION_NAMES,L"Forward",&aStack_79);
  std::wstring::wstring((wstring_conflict *)(::gSHAPE_DIRECTION_NAMES + 8),L"Down",&aStack_78);
  std::wstring::wstring((wstring_conflict *)(::gSHAPE_DIRECTION_NAMES + 0x10),L"Up",&aStack_77);
  std::wstring::wstring
            ((wstring_conflict *)(::gSHAPE_DIRECTION_NAMES + 0x18),L"Outward From Center",&aStack_76
            );
  std::wstring::wstring
            ((wstring_conflict *)(::gSHAPE_DIRECTION_NAMES + 0x20),L"Inward to Center",&aStack_75);
  __cxa_atexit(__tcf_56,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)gSPAWN_TYPE_NAMES,L"Monsters",&aStack_74);
  std::wstring::wstring((wstring_conflict *)(gSPAWN_TYPE_NAMES + 8),L"Items",&aStack_73);
  std::wstring::wstring((wstring_conflict *)(gSPAWN_TYPE_NAMES + 0x10),L"Particle",&aStack_72);
  std::wstring::wstring((wstring_conflict *)(gSPAWN_TYPE_NAMES + 0x18),L"Spawn Class",&aStack_71);
  std::wstring::wstring((wstring_conflict *)(gSPAWN_TYPE_NAMES + 0x20),L"Missiles",&aStack_70);
  std::wstring::wstring((wstring_conflict *)(gSPAWN_TYPE_NAMES + 0x28),L"Unit Type",&aStack_6f);
  std::wstring::wstring((wstring_conflict *)(gSPAWN_TYPE_NAMES + 0x30),L"Props",&aStack_6e);
  __cxa_atexit(__tcf_57,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)&::g_QUEST_COMPLETE_TYPE_NAMES,L"COMPLETE_ON_QUEST_ACCEPT",
             &aStack_6d);
  std::wstring::wstring((wstring_conflict *)&DAT_0148c028,L"COMPLETE_ON_QUEST_COMPLETE",&aStack_6c);
  __cxa_atexit(__tcf_58,0,&__dso_handle);
  ::g_strStatDefines._0_4_ = 1;
  ::g_strStatDefines._4_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 8),"STAT_DEATHS",&aStack_6b);
  ::g_strStatDefines[0x10] = 0;
  ::g_strStatDefines._24_4_ = 2;
  ::g_strStatDefines._28_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x20),"STAT_BREAKABLES",&aStack_6a);
  ::g_strStatDefines[0x28] = 0;
  ::g_strStatDefines._48_4_ = 3;
  ::g_strStatDefines._52_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x38),"STAT_CRITICAL_STRIKES",&aStack_69);
  ::g_strStatDefines[0x40] = 0;
  ::g_strStatDefines._72_4_ = 4;
  ::g_strStatDefines._76_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x50),"STAT_MAX_DMG_DONE",&aStack_68);
  ::g_strStatDefines[0x58] = 0;
  ::g_strStatDefines._96_4_ = 5;
  ::g_strStatDefines._100_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x68),"STAT_MONSTERS_KILLED",&aStack_67);
  ::g_strStatDefines[0x70] = 0;
  ::g_strStatDefines._120_4_ = 6;
  ::g_strStatDefines._124_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x80),"STAT_DEEPEST_FLOOR",&aStack_66);
  ::g_strStatDefines[0x88] = 0;
  ::g_strStatDefines._144_4_ = 7;
  ::g_strStatDefines._148_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x98),"STAT_FISH_CAUGHT",&aStack_65);
  ::g_strStatDefines[0xa0] = 0;
  ::g_strStatDefines._168_4_ = 8;
  ::g_strStatDefines._172_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0xb0),"STAT_ENCHANTER_FAILS",&aStack_64);
  ::g_strStatDefines[0xb8] = 0;
  ::g_strStatDefines._192_4_ = 9;
  ::g_strStatDefines._196_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 200),"STAT_RECIPES_MADE",&aStack_63);
  ::g_strStatDefines[0xd0] = 0;
  ::g_strStatDefines._216_4_ = 10;
  ::g_strStatDefines._220_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0xe0),"STAT_GAMBLE_COUNT",&aStack_62);
  ::g_strStatDefines[0xe8] = 0;
  ::g_strStatDefines._240_4_ = 0xb;
  ::g_strStatDefines._244_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0xf8),"STAT_QUESTS_COMPLETED",&aStack_61);
  ::g_strStatDefines[0x100] = 0;
  ::g_strStatDefines._264_4_ = 0xc;
  ::g_strStatDefines._268_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x110),"STAT_RETIRED_COUNT",&aStack_60);
  ::g_strStatDefines[0x118] = 0;
  ::g_strStatDefines._288_4_ = 0xd;
  ::g_strStatDefines._292_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x128),"STAT_RETIRED_LVLS_TOTAL",&aStack_5f);
  ::g_strStatDefines[0x130] = 0;
  ::g_strStatDefines._312_4_ = 0xe;
  ::g_strStatDefines._316_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x140),"STAT_GOLD_COLLECTED",&aStack_5e);
  ::g_strStatDefines[0x148] = 0;
  ::g_strStatDefines._336_4_ = 0xf;
  ::g_strStatDefines._340_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x158),"STAT_LEVERS_PULLED",&aStack_5d);
  ::g_strStatDefines[0x160] = 0;
  ::g_strStatDefines._360_4_ = 0x10;
  ::g_strStatDefines._364_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x170),"STAT_TOTAL_STEPS",&aStack_5c);
  ::g_strStatDefines[0x178] = 0;
  ::g_strStatDefines._384_4_ = 0x11;
  ::g_strStatDefines._388_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x188),"STAT_TOTAL_POTIONS_USED",&aStack_5b);
  ::g_strStatDefines[400] = 0;
  ::g_strStatDefines._408_4_ = 0x12;
  ::g_strStatDefines._412_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x1a0),"STAT_TOTAL_ITEMS_SOLD",&aStack_5a);
  ::g_strStatDefines[0x1a8] = 0;
  ::g_strStatDefines._432_4_ = 0x13;
  ::g_strStatDefines._436_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x1b8),"STAT_DEATHS_HARDCORE",&aStack_59);
  ::g_strStatDefines[0x1c0] = 0;
  ::g_strStatDefines._456_4_ = 0x14;
  ::g_strStatDefines._460_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x1d0),"STAT_TROLL_CHMPS",&aStack_58);
  ::g_strStatDefines[0x1d8] = 0;
  ::g_strStatDefines._480_4_ = 0x15;
  ::g_strStatDefines._484_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x1e8),"STAT_POTIONS_PET",&aStack_57);
  ::g_strStatDefines[0x1f0] = 0;
  ::g_strStatDefines._504_4_ = 0x16;
  ::g_strStatDefines._508_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x200),"STAT_WIN_VANQ",&aStack_56);
  ::g_strStatDefines[0x208] = 0;
  ::g_strStatDefines._528_4_ = 0x17;
  ::g_strStatDefines._532_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x218),"STAT_WIN_ALCH",&aStack_55);
  ::g_strStatDefines[0x220] = 0;
  ::g_strStatDefines._552_4_ = 0x18;
  ::g_strStatDefines._556_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x230),"STAT_WIN_DESTROYER",&aStack_54);
  ::g_strStatDefines[0x238] = 0;
  ::g_strStatDefines._576_4_ = 0x19;
  ::g_strStatDefines._580_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x248),"STAT_EXPLODE_ENEMY",&aStack_53);
  ::g_strStatDefines[0x250] = 0;
  ::g_strStatDefines._600_4_ = 0x1a;
  ::g_strStatDefines._604_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x260),"STAT_QUESTS_COMPLETED_HATCH",
                      &aStack_52);
  ::g_strStatDefines[0x268] = 0;
  ::g_strStatDefines._624_4_ = 0x1b;
  ::g_strStatDefines._628_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x278),"STAT_QUESTS_COMPLETED_GARR",&aStack_51
                     );
  ::g_strStatDefines[0x280] = 0;
  ::g_strStatDefines._648_4_ = 0x1c;
  ::g_strStatDefines._652_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x290),"STAT_HORSE_TALK",&aStack_50);
  ::g_strStatDefines[0x298] = 0;
  ::g_strStatDefines._672_4_ = 0xffffffff;
  ::g_strStatDefines._676_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x2a8),"PLAYER_DEATHS",&aStack_4f);
  ::g_strStatDefines[0x2b0] = 0;
  ::g_strStatDefines._696_4_ = 0xffffffff;
  ::g_strStatDefines._700_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x2c0),"PLAYER_GOLD",&aStack_4e);
  ::g_strStatDefines[0x2c8] = 0;
  ::g_strStatDefines._720_4_ = 0xffffffff;
  ::g_strStatDefines._724_4_ = 0;
  std::string::string((string *)(::g_strStatDefines + 0x2d8),"NONE",&aStack_4d);
  ::g_strStatDefines[0x2e0] = 0;
  __cxa_atexit(__tcf_59,0,&__dso_handle);
  std::string::string((string *)g_strAchievementsCodeName,"TORCHLIGHT_ACHIEVEMENT_FIRSTLEVEL",
                      &aStack_4c);
  std::string::string((string *)(g_strAchievementsCodeName + 8),"BEAST_OF_BURDEN",&aStack_4b);
  std::string::string((string *)(g_strAchievementsCodeName + 0x10),"PET_SEND_TO_TOWN",&aStack_4a);
  std::string::string((string *)(g_strAchievementsCodeName + 0x18),"PET_FEED_FISH_ANY",&aStack_49);
  std::string::string((string *)(g_strAchievementsCodeName + 0x20),"PET_FEED_FISH_PERMANENT",
                      &aStack_48);
  std::string::string((string *)(g_strAchievementsCodeName + 0x28),"GAMBLE_UNIQUE",&aStack_47);
  std::string::string((string *)(g_strAchievementsCodeName + 0x30),"MAX_FAME",&aStack_46);
  std::string::string((string *)(g_strAchievementsCodeName + 0x38),"KILL_BRINK",&aStack_45);
  std::string::string((string *)(g_strAchievementsCodeName + 0x40),"KILL_LICH",&aStack_44);
  std::string::string((string *)(g_strAchievementsCodeName + 0x48),"KILL_ROOT_GOLEM",&aStack_43);
  std::string::string((string *)(g_strAchievementsCodeName + 0x50),"KILL_EMBER_COLOSSUS",&aStack_42)
  ;
  std::string::string((string *)(g_strAchievementsCodeName + 0x58),"KILL_TROLL_BOSS",&aStack_41);
  std::string::string((string *)(g_strAchievementsCodeName + 0x60),"KILL_MEDEA",&aStack_40);
  std::string::string((string *)(g_strAchievementsCodeName + 0x68),"KILL_ALRIC",&aStack_3f);
  std::string::string((string *)(g_strAchievementsCodeName + 0x70),"BEASTSLAYERI",&aStack_3e);
  std::string::string((string *)(g_strAchievementsCodeName + 0x78),"BEASTSLAYERII",&aStack_3d);
  std::string::string((string *)(g_strAchievementsCodeName + 0x80),"BEASTSLAYERIII",&aStack_3c);
  std::string::string((string *)(g_strAchievementsCodeName + 0x88),"HARDCORE_VICTOR",&aStack_3b);
  std::string::string((string *)(g_strAchievementsCodeName + 0x90),"HARDCORE_HERO",&aStack_3a);
  std::string::string((string *)(g_strAchievementsCodeName + 0x98),"HARDCORE_CHAMPION",&aStack_39);
  std::string::string((string *)(g_strAchievementsCodeName + 0xa0),"HARDCORE_GOD",&aStack_38);
  std::string::string((string *)(g_strAchievementsCodeName + 0xa8),"SPEEDY",&aStack_37);
  std::string::string((string *)(g_strAchievementsCodeName + 0xb0),"SPEED_KING",&aStack_36);
  std::string::string((string *)(g_strAchievementsCodeName + 0xb8),"HAT_TRICK",&aStack_35);
  std::string::string((string *)(g_strAchievementsCodeName + 0xc0),"PLAYER_LEVEL_65",&aStack_34);
  std::string::string((string *)(g_strAchievementsCodeName + 200),"PLAYER_LEVEL_100",&aStack_33);
  std::string::string((string *)(g_strAchievementsCodeName + 0xd0),"MODS_1",&aStack_32);
  std::string::string((string *)(g_strAchievementsCodeName + 0xd8),"MODS_5",&aStack_31);
  std::string::string((string *)(g_strAchievementsCodeName + 0xe0),"MODS_10",&aStack_30);
  std::string::string((string *)(g_strAchievementsCodeName + 0xe8),"ENCHANTER_FAILURE_FIRST",
                      &aStack_2f);
  std::string::string((string *)(g_strAchievementsCodeName + 0xf0),"PET_MIMIC",&aStack_2e);
  std::string::string((string *)(g_strAchievementsCodeName + 0xf8),"PET_TRAINER",&aStack_2d);
  std::string::string((string *)(g_strAchievementsCodeName + 0x100),"ENCHANTER_SUCCESS_5",&aStack_2c
                     );
  std::string::string((string *)(g_strAchievementsCodeName + 0x108),"ENCHANTER_SUCCESS_10",
                      &aStack_2b);
  std::string::string((string *)(g_strAchievementsCodeName + 0x110),"PERFECT_VICTORY",&aStack_2a);
  std::string::string((string *)(g_strAchievementsCodeName + 0x118),"PLAYER_GOLD_IN_POCKET",
                      aaStack_29);
  __cxa_atexit(__tcf_60,0,&__dso_handle);
  return;
}



/* address=008ef520
   symbol=CPlayer::getDungeonRank */

/* CPlayer::getDungeonRank(std::wstring) */

undefined4 __thiscall CPlayer::getDungeonRank(CPlayer *this,undefined8 *param_2)

{
  uint uVar1;
  uint uVar2;
  wchar_t *__s2;
  size_t __n;
  wchar_t *__s1;
  size_t sVar3;
  int iVar4;
  uint uVar5;
  long *plVar6;
  long lVar7;

  uVar1 = *(uint *)(this + 0xa48);
  if (uVar1 != 0) {
    __s2 = (wchar_t *)*param_2;
    uVar2 = *(uint *)(this + 0xa4c);
    lVar7 = 0;
    uVar5 = 0;
    __n = *(size_t *)(__s2 + -6);
    do {
      if (uVar5 < uVar2) {
        __s1 = (wchar_t *)**(long **)(lVar7 + *(long *)(this + 0xa40));
        sVar3 = *(size_t *)(__s1 + -6);
      }
      else {
        __s1 = *(wchar_t **)**(undefined8 **)(this + 0xa40);
        sVar3 = *(size_t *)(__s1 + -6);
      }
      if ((sVar3 == __n) && (iVar4 = wmemcmp(__s1,__s2,__n), iVar4 == 0)) {
        if (uVar5 < uVar2) {
          plVar6 = (long *)((ulong)uVar5 * 8 + *(long *)(this + 0xa40));
        }
        else {
          plVar6 = *(long **)(this + 0xa40);
        }
        return *(undefined4 *)(*plVar6 + 0xc);
      }
      uVar5 = uVar5 + 1;
      lVar7 = lVar7 + 8;
    } while (uVar5 < uVar1);
  }
  return 0;
}



/* address=008ef600
   symbol=CPlayer::getLevelSavedState */

/* CPlayer::getLevelSavedState(std::wstring, int) */

long __thiscall CPlayer::getLevelSavedState(CPlayer *this,undefined8 *param_2,int param_3)

{
  long lVar1;
  long lVar2;
  size_t __n;
  int iVar3;
  ulong uVar4;
  uint uVar5;
  ulong uVar6;

  lVar1 = *(long *)(this + 0x798);
  uVar6 = *(long *)(this + 0x7a0) - lVar1 >> 3;
  if (uVar6 == 0) {
    return 0;
  }
  uVar4 = 0;
  uVar5 = 0;
  do {
    while (lVar2 = *(long *)(lVar1 + uVar4 * 8), param_3 != *(int *)(lVar2 + 0x10)) {
LAB_008ef650:
      uVar5 = uVar5 + 1;
      uVar4 = (ulong)uVar5;
      if (uVar6 <= uVar4) {
        return 0;
      }
    }
    __n = *(size_t *)(*(wchar_t **)(lVar2 + 0x18) + -6);
    if (__n != *(size_t *)((wchar_t *)*param_2 + -6)) goto LAB_008ef650;
    iVar3 = wmemcmp(*(wchar_t **)(lVar2 + 0x18),(wchar_t *)*param_2,__n);
    if (iVar3 == 0) {
      return lVar2;
    }
    uVar5 = uVar5 + 1;
    uVar4 = (ulong)uVar5;
    if (uVar6 <= uVar4) {
      return 0;
    }
  } while( true );
}



/* address=008ef6c0
   symbol=CPlayer::hasLevelSavedState */

/* CPlayer::hasLevelSavedState(std::wstring, int) */

undefined8 __thiscall CPlayer::hasLevelSavedState(CPlayer *this,undefined8 *param_2,int param_3)

{
  long lVar1;
  long lVar2;
  wchar_t *__s1;
  size_t __n;
  int iVar3;
  ulong uVar4;
  uint uVar5;
  ulong uVar6;

  lVar1 = *(long *)(this + 0x798);
  uVar6 = *(long *)(this + 0x7a0) - lVar1 >> 3;
  if (uVar6 != 0) {
    uVar4 = 0;
    uVar5 = 0;
    do {
      lVar2 = *(long *)(lVar1 + uVar4 * 8);
      if (param_3 == *(int *)(lVar2 + 0x10)) {
        __s1 = *(wchar_t **)(lVar2 + 0x18);
        __n = *(size_t *)(__s1 + -6);
        if (__n == *(size_t *)((wchar_t *)*param_2 + -6)) {
          iVar3 = wmemcmp(__s1,(wchar_t *)*param_2,__n);
          if (iVar3 == 0) {
            return 1;
          }
        }
      }
      uVar5 = uVar5 + 1;
      uVar4 = (ulong)uVar5;
    } while (uVar4 < uVar6);
  }
  return 0;
}



/* address=008efa70
   symbol=CPlayer::addWaypoint */

/* CPlayer::addWaypoint(std::wstring, int) */

undefined8 __thiscall CPlayer::addWaypoint(CPlayer *this,undefined8 *param_2,int param_3)

{
  uint uVar1;
  wchar_t *__s2;
  size_t __n;
  wchar_t *__s1;
  size_t sVar2;
  long *plVar3;
  int *piVar4;
  int iVar5;
  long *plVar6;
  long lVar7;
  uint uVar8;
  long lVar9;
  uint uVar10;
  long *plVar11;
  int local_3c [3];

  uVar10 = *(uint *)(this + 0xa48);
  if (uVar10 != 0) {
    __s2 = (wchar_t *)*param_2;
    uVar1 = *(uint *)(this + 0xa4c);
    lVar9 = 0;
    uVar8 = 0;
    __n = *(size_t *)(__s2 + -6);
    local_3c[0] = param_3;
    do {
      if (uVar8 < uVar1) {
        __s1 = (wchar_t *)**(long **)(lVar9 + *(long *)(this + 0xa40));
        sVar2 = *(size_t *)(__s1 + -6);
      }
      else {
        __s1 = *(wchar_t **)**(undefined8 **)(this + 0xa40);
        sVar2 = *(size_t *)(__s1 + -6);
      }
      if ((__n == sVar2) && (iVar5 = wmemcmp(__s1,__s2,__n), iVar5 == 0)) {
        plVar3 = *(long **)(this + 0xa40);
        uVar10 = 0;
        plVar11 = plVar3 + uVar8;
        while( true ) {
          plVar6 = plVar11;
          if (uVar1 <= uVar8) {
            plVar6 = plVar3;
          }
          if ((ulong)(*(long *)(*plVar6 + 0x20) - *(long *)(*plVar6 + 0x18) >> 2) <= (ulong)uVar10)
          {
            if (uVar1 <= uVar8) {
              plVar11 = plVar3;
            }
            lVar9 = *plVar11;
            piVar4 = *(int **)(lVar9 + 0x20);
            if (piVar4 != *(int **)(lVar9 + 0x28)) {
              lVar7 = 0;
              if (piVar4 != (int *)0x0) {
                *piVar4 = local_3c[0];
                lVar7 = *(long *)(lVar9 + 0x20);
              }
              *(long *)(lVar9 + 0x20) = lVar7 + 4;
              return 1;
            }
            std::vector<int,std::allocator<int>>::_M_insert_aux
                      ((vector<int,std::allocator<int>> *)(lVar9 + 0x18),piVar4,local_3c);
            return 1;
          }
          plVar6 = plVar3;
          if (uVar8 < uVar1) {
            plVar6 = plVar11;
          }
          if (*(int *)(*(long *)(*plVar6 + 0x18) + (ulong)uVar10 * 4) == local_3c[0]) break;
          uVar10 = uVar10 + 1;
        }
        return 0;
      }
      uVar8 = uVar8 + 1;
      lVar9 = lVar9 + 8;
    } while (uVar8 < uVar10);
  }
  return 0;
}



/* address=008efbc0
   symbol=CPlayer::updateFishingLine */

/* WARNING: Removing unreachable block (ram,0x008f0a35) */
/* WARNING: Removing unreachable block (ram,0x008f09dd) */
/* WARNING: Removing unreachable block (ram,0x008f0a25) */
/* WARNING: Removing unreachable block (ram,0x008f094d) */
/* CPlayer::updateFishingLine(float) */

void CPlayer::updateFishingLine(float param_1)

{
  int *piVar1;
  int iVar2;
  code *pcVar3;
  ulong uVar4;
  long *plVar5;
  long *plVar6;
  long *plVar7;
  long *plVar8;
  float *pfVar9;
  undefined8 *puVar10;
  uint uVar11;
  ushort uVar12;
  CPositionableObject *in_RDI;
  CPath *this;
  ushort uVar13;
  float in_XMM1_Da;
  float fVar14;
  float fVar15;
  float fVar16;
  float local_1a8;
  float fStack_1a4;
  float local_1a0;
  undefined8 local_198;
  float local_190;
  undefined8 local_188;
  float local_180;
  float local_178;
  float local_174;
  float local_170;
  undefined8 local_168;
  float local_160;
  undefined8 local_158;
  float local_150;
  undefined8 local_148;
  float local_140;
  undefined8 local_138;
  float local_130;
  undefined8 local_128;
  float local_120;
  float local_118;
  float local_114;
  float local_110;
  undefined8 local_108;
  float local_100;
  undefined8 local_f8;
  float local_f0;
  float local_e8;
  float local_e4;
  float local_e0;
  undefined8 local_d8;
  float local_d0;
  undefined8 local_c8;
  float local_c0;
  float local_b8;
  float local_b4;
  float local_b0;
  undefined8 local_a8;
  float local_a0;
  undefined8 local_98;
  float local_90;
  float local_88;
  float local_84;
  float local_80;
  long local_78 [2];
  long local_68 [2];
  long local_58 [2];
  long local_48;
  allocator local_3c;
  allocator local_3b;
  allocator local_3a;
  allocator local_39 [9];

  CPath::Clear(*(CPath **)(in_RDI + 0x838));
  plVar8 = *(long **)(*(long *)(in_RDI + 0x200) + 0x130);
  pcVar3 = *(code **)(*plVar8 + 0x1b0);
                    /* try { // try from 008efc11 to 008efc15 has its CatchHandler @ 008f09d8 */
  std::string::string((string *)&local_48,"tag_zfishpoleend",local_39);
                    /* try { // try from 008efc1c to 008efc1e has its CatchHandler @ 008f09c8 */
  plVar5 = (long *)(*pcVar3)(plVar8,(string *)&local_48);
  if ((allocator *)(local_48 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_48 + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_48 + -0x18));
    }
  }
  pcVar3 = *(code **)(*plVar8 + 0x1b0);
                    /* try { // try from 008efc62 to 008efc66 has its CatchHandler @ 008f099a */
  std::string::string((string *)local_58,"tag_zfishcenter",&local_3a);
                    /* try { // try from 008efc6d to 008efc6f has its CatchHandler @ 008f0a14 */
  plVar6 = (long *)(*pcVar3)(plVar8,(string *)local_58);
  if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_58[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
    }
  }
  pcVar3 = *(code **)(*plVar8 + 0x1b0);
                    /* try { // try from 008efcab to 008efcaf has its CatchHandler @ 008f0a30 */
  std::string::string((string *)local_68,"tag_zfishlure",&local_3b);
                    /* try { // try from 008efcb6 to 008efcb8 has its CatchHandler @ 008f098d */
  plVar7 = (long *)(*pcVar3)(plVar8,(string *)local_68);
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
  pcVar3 = *(code **)(*plVar8 + 0x1b0);
                    /* try { // try from 008efcf9 to 008efcfd has its CatchHandler @ 008f0958 */
  std::string::string((string *)local_78,"tag_zfishlureend",&local_3c);
                    /* try { // try from 008efd04 to 008efd07 has its CatchHandler @ 008f093a */
  plVar8 = (long *)(*pcVar3)(plVar8);
  if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_78[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
    }
  }
  local_98 = CPositionableObject::getPosition(*(CPositionableObject **)(in_RDI + 0x200),false);
  local_90 = in_XMM1_Da;
  pfVar9 = (float *)(**(code **)(*plVar5 + 0x200))(plVar5);
  local_84 = pfVar9[1] + local_98._4_4_;
  local_88 = *pfVar9 + (float)local_98;
  local_80 = pfVar9[2] + local_90;
  pfVar9 = (float *)(**(code **)(*(long *)in_RDI + 0xe8))();
  fVar16 = DAT_00fa47fc /
           (pfVar9[0xc] * local_88 + pfVar9[0xd] * local_84 + pfVar9[0xe] * local_80 + pfVar9[0xf]);
  fVar15 = local_80 * pfVar9[2];
  fVar14 = (pfVar9[4] * local_88 + pfVar9[5] * local_84 + pfVar9[6] * local_80 + pfVar9[7]) * fVar16
  ;
  local_80 = (pfVar9[8] * local_88 + pfVar9[9] * local_84 + pfVar9[10] * local_80 + pfVar9[0xb]) *
             fVar16;
  local_88 = (local_88 * *pfVar9 + local_84 * pfVar9[1] + fVar15 + pfVar9[3]) * fVar16;
  local_84 = fVar14;
  local_a8 = CPositionableObject::getPosition(in_RDI,true);
  local_88 = local_88 + (float)local_a8;
  local_84 = local_84 + (float)((ulong)local_a8 >> 0x20);
  local_80 = local_80 + fVar14;
  local_a0 = fVar14;
  local_c8 = CPositionableObject::getPosition(*(CPositionableObject **)(in_RDI + 0x200),false);
  local_c0 = fVar14;
  pfVar9 = (float *)(**(code **)(*plVar6 + 0x200))(plVar6);
  local_b4 = pfVar9[1] + local_c8._4_4_;
  local_b8 = *pfVar9 + (float)local_c8;
  local_b0 = pfVar9[2] + local_c0;
  pfVar9 = (float *)(**(code **)(*(long *)in_RDI + 0xe8))();
  fVar16 = DAT_00fa47fc /
           (pfVar9[0xc] * local_b8 + pfVar9[0xd] * local_b4 + pfVar9[0xe] * local_b0 + pfVar9[0xf]);
  fVar15 = local_b0 * pfVar9[2];
  fVar14 = (pfVar9[4] * local_b8 + pfVar9[5] * local_b4 + pfVar9[6] * local_b0 + pfVar9[7]) * fVar16
  ;
  local_b0 = (pfVar9[8] * local_b8 + pfVar9[9] * local_b4 + pfVar9[10] * local_b0 + pfVar9[0xb]) *
             fVar16;
  local_b8 = (local_b8 * *pfVar9 + local_b4 * pfVar9[1] + fVar15 + pfVar9[3]) * fVar16;
  local_b4 = fVar14;
  local_d8 = CPositionableObject::getPosition(in_RDI,true);
  local_b8 = local_b8 + (float)local_d8;
  local_b4 = local_b4 + (float)((ulong)local_d8 >> 0x20);
  local_b0 = local_b0 + fVar14;
  local_d0 = fVar14;
  local_f8 = CPositionableObject::getPosition(*(CPositionableObject **)(in_RDI + 0x200),false);
  local_f0 = fVar14;
  pfVar9 = (float *)(**(code **)(*plVar7 + 0x200))(plVar7);
  local_e4 = pfVar9[1] + local_f8._4_4_;
  local_e8 = *pfVar9 + (float)local_f8;
  local_e0 = pfVar9[2] + local_f0;
  pfVar9 = (float *)(**(code **)(*(long *)in_RDI + 0xe8))();
  fVar16 = DAT_00fa47fc /
           (pfVar9[0xc] * local_e8 + pfVar9[0xd] * local_e4 + pfVar9[0xe] * local_e0 + pfVar9[0xf]);
  fVar15 = local_e0 * pfVar9[2];
  fVar14 = (pfVar9[4] * local_e8 + pfVar9[5] * local_e4 + pfVar9[6] * local_e0 + pfVar9[7]) * fVar16
  ;
  local_e0 = (pfVar9[8] * local_e8 + pfVar9[9] * local_e4 + pfVar9[10] * local_e0 + pfVar9[0xb]) *
             fVar16;
  local_e8 = (local_e8 * *pfVar9 + local_e4 * pfVar9[1] + fVar15 + pfVar9[3]) * fVar16;
  local_e4 = fVar14;
  local_108 = CPositionableObject::getPosition(in_RDI,true);
  local_e8 = local_e8 + (float)local_108;
  local_e4 = local_e4 + (float)((ulong)local_108 >> 0x20);
  local_e0 = local_e0 + fVar14;
  local_100 = fVar14;
  local_128 = CPositionableObject::getPosition(*(CPositionableObject **)(in_RDI + 0x200),false);
  local_120 = fVar14;
  pfVar9 = (float *)(**(code **)(*plVar8 + 0x200))(plVar8);
  local_114 = pfVar9[1] + local_128._4_4_;
  local_118 = *pfVar9 + (float)local_128;
  local_110 = pfVar9[2] + local_120;
  pfVar9 = (float *)(**(code **)(*(long *)in_RDI + 0xe8))();
  fVar16 = DAT_00fa47fc /
           (pfVar9[0xc] * local_118 + pfVar9[0xd] * local_114 + pfVar9[0xe] * local_110 +
           pfVar9[0xf]);
  fVar15 = local_110 * pfVar9[2];
  fVar14 = (pfVar9[4] * local_118 + pfVar9[5] * local_114 + pfVar9[6] * local_110 + pfVar9[7]) *
           fVar16;
  local_110 = (pfVar9[8] * local_118 + pfVar9[9] * local_114 + pfVar9[10] * local_110 + pfVar9[0xb])
              * fVar16;
  local_118 = (local_118 * *pfVar9 + local_114 * pfVar9[1] + fVar15 + pfVar9[3]) * fVar16;
  local_114 = fVar14;
  local_138 = CPositionableObject::getPosition(in_RDI,true);
  local_118 = local_118 + (float)local_138;
  local_114 = local_114 + (float)((ulong)local_138 >> 0x20);
  local_110 = local_110 + fVar14;
  local_130 = fVar14;
  if (*(CPositionableObject **)(in_RDI + 0x350) != (CPositionableObject *)0x0) {
    local_148 = CPositionableObject::getPosition(*(CPositionableObject **)(in_RDI + 0x350),true);
    fVar15 = (float)((ulong)local_148 >> 0x20);
    local_140 = fVar14;
    if (local_e4 <= fVar15) {
      local_e4 = fVar15;
    }
  }
  uVar13 = 0;
  uVar11 = 0;
  CPath::AddPoint(*(CPath **)(in_RDI + 0x838),(Vector3 *)&local_88,DAT_00fce4d4,DAT_00fa8778);
  CPath::AddPoint(*(CPath **)(in_RDI + 0x838),(Vector3 *)&local_b8,DAT_00fce4d4,DAT_00fa8778);
  CPath::AddPoint(*(CPath **)(in_RDI + 0x838),(Vector3 *)&local_e8,DAT_00fce4d4,DAT_00fa8778);
  fVar14 = DAT_00fa8778;
  CPath::AddPoint(*(CPath **)(in_RDI + 0x838),(Vector3 *)&local_118,DAT_00fce4d4,DAT_00fa8778);
  this = *(CPath **)(in_RDI + 0x838);
  fVar15 = DAT_00fd3a54 * *(float *)(this + 0x18);
  while( true ) {
    uVar4 = (ulong)uVar11;
    uVar11 = uVar11 + 1;
    local_158 = CPath::GetSplinePositionAtDistance(this,(float)uVar4 * fVar15);
    local_150 = fVar14;
    CDynamicLine::setPoint(*(CDynamicLine **)(in_RDI + 0x840),uVar13,(Vector3 *)&local_158);
    local_168 = CPath::GetSplinePositionAtDistance
                          (*(CPath **)(in_RDI + 0x838),(float)uVar11 * fVar15);
    uVar12 = uVar13 + 1;
    uVar13 = uVar13 + 2;
    local_160 = fVar14;
    CDynamicLine::setPoint(*(CDynamicLine **)(in_RDI + 0x840),uVar12,(Vector3 *)&local_168);
    if (uVar11 == 8) break;
    this = *(CPath **)(in_RDI + 0x838);
  }
  CDynamicLine::update(*(CDynamicLine **)(in_RDI + 0x840));
  (**(code **)(**(long **)(in_RDI + 0x848) + 600))(*(long **)(in_RDI + 0x848),0);
  if (in_RDI[0x85c] != (CPositionableObject)0x0) {
    (**(code **)(**(long **)(in_RDI + 0x830) + 0x50))(*(long **)(in_RDI + 0x830),1);
    CPositionableObject::setPosition
              (*(CPositionableObject **)(in_RDI + 0x830),(Vector3 *)&local_118);
    local_198 = CPath::GetSplinePositionAtDistance
                          (*(CPath **)(in_RDI + 0x838),
                           *(float *)(*(CPath **)(in_RDI + 0x838) + 0x18));
    local_190 = fVar14;
    local_188 = CPath::GetSplinePositionAtDistance
                          (*(CPath **)(in_RDI + 0x838),
                           *(float *)(*(CPath **)(in_RDI + 0x838) + 0x18) - DAT_00fce4dc);
    local_174 = (float)((ulong)local_188 >> 0x20) - local_198._4_4_;
    local_178 = (float)local_188 - (float)local_198;
    local_170 = fVar14 - local_190;
    fVar15 = SQRT(local_178 * local_178 + local_174 * local_174 + local_170 * local_170);
    if (DAT_00fa87a0 < (double)fVar15) {
      fVar15 = DAT_00fa47fc / fVar15;
      local_178 = local_178 * fVar15;
      local_174 = local_174 * fVar15;
      local_170 = local_170 * fVar15;
    }
    local_180 = fVar14;
    puVar10 = (undefined8 *)(**(code **)(*(long *)in_RDI + 0x130))();
    local_1a8 = (float)*puVar10;
    fStack_1a4 = (float)((ulong)*puVar10 >> 0x20);
    fVar16 = local_1a8 * local_174 - fStack_1a4 * local_178;
    fVar15 = local_178 * *(float *)(puVar10 + 1) - local_1a8 * local_170;
    fVar14 = fStack_1a4 * local_170 - *(float *)(puVar10 + 1) * local_174;
    local_1a0 = fVar15 * local_178 - fVar14 * local_174;
    _local_1a8 = CONCAT44(local_170 * fVar14 - fVar16 * local_178,
                          local_174 * fVar16 - local_170 * fVar15);
    (**(code **)(**(long **)(in_RDI + 0x830) + 0x128))
              (*(long **)(in_RDI + 0x830),&local_1a8,&local_178);
  }
  return;
}



/* address=008f0a50
   symbol=CPlayer::catchFish */

/* WARNING: Removing unreachable block (ram,0x008f0b9a) */
/* WARNING: Removing unreachable block (ram,0x008f0bc2) */
/* CPlayer::catchFish() */

void __thiscall CPlayer::catchFish(CPlayer *this)

{
  int *piVar1;
  int iVar2;
  long local_38 [2];
  long local_28;
  allocator local_1a;
  allocator local_19 [9];

  if (*(int *)(this + 0x330) != 0x22) {
    this[0x85c] = (CPlayer)0x0;
    if (DAT_00fa47f8 < *(float *)(this + 0x860)) {
      this[0x85c] = (CPlayer)0x1;
    }
    (**(code **)(*(long *)this + 0x348))(this,0x22);
                    /* try { // try from 008f0aa5 to 008f0aa9 has its CatchHandler @ 008f0bbf */
    std::string::string((string *)&local_28,"FISHING_CATCH",local_19);
                    /* try { // try from 008f0aca to 008f0ace has its CatchHandler @ 008f0ba5 */
    CCharacter::blendAnimation
              ((string *)this,SUB81((string *)&local_28,0),DAT_00fa86e8,DAT_00fa47fc,DAT_00fa8760);
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
                    /* try { // try from 008f0af2 to 008f0af6 has its CatchHandler @ 008f0b8f */
    std::string::string((string *)local_38,"IDLE",&local_1a);
                    /* try { // try from 008f0b16 to 008f0b1a has its CatchHandler @ 008f0bb2 */
    CGenericModel::queueBlendAnimation
              (*(CGenericModel **)(this + 0x200),(string *)local_38,true,DAT_00fa86e8,DAT_00fa47fc);
    if ((allocator *)(local_38[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
    {
      LOCK();
      piVar1 = (int *)(local_38[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_38[0] + -0x18));
      }
    }
  }
  return;
}



/* address=008f0bd0
   symbol=CPlayer::attemptToStopPlayerSkill */

/* WARNING: Removing unreachable block (ram,0x008f0cfe) */
/* CPlayer::attemptToStopPlayerSkill(bool) */

void __thiscall CPlayer::attemptToStopPlayerSkill(CPlayer *this,bool param_1)

{
  int *piVar1;
  char cVar2;
  int iVar3;
  long local_28;
  allocator local_19;

  if (*(CSkill **)(this + 0x398) != (CSkill *)0x0) {
    iVar3 = CSkill::getAnimationIndexLoopEnd(*(CSkill **)(this + 0x398));
    CCharacter::attemptStopOfActiveSkill((CCharacter *)this);
    cVar2 = CCharacter::performingSkill((CCharacter *)this);
    if (cVar2 == '\0') {
      if (iVar3 != -1) {
        CCharacter::blendAnimation((int)this,SUB41(iVar3,0),DAT_00fa86e8,DAT_00fa47fc,DAT_00fa8760);
                    /* try { // try from 008f0c53 to 008f0c57 has its CatchHandler @ 008f0ce6 */
        std::string::string((string *)&local_28,"IDLE",&local_19);
                    /* try { // try from 008f0c73 to 008f0c77 has its CatchHandler @ 008f0cf1 */
        CCharacter::queueBlendAnimation
                  ((CCharacter *)this,(string *)&local_28,true,DAT_00fa86e8,DAT_00fa47fc);
        if ((allocator *)(local_28 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage
           ) {
          LOCK();
          piVar1 = (int *)(local_28 + -8);
          iVar3 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar3 < 1) {
            std::string::_Rep::_M_destroy((allocator *)(local_28 + -0x18));
          }
        }
      }
      if (((*(long *)(this + 0x398) != 0) && (*(char *)(*(long *)(this + 0x398) + 0x68) != '\0')) &&
         (param_1)) {
        CCharacter::stopPathing((CCharacter *)this);
      }
    }
  }
  return;
}



/* address=008f0d10
   symbol=CPlayer::updateAnimation */

/* WARNING: Removing unreachable block (ram,0x008f0f4e) */
/* CPlayer::updateAnimation(float) */

void __thiscall CPlayer::updateAnimation(CPlayer *this,float param_1)

{
  int *piVar1;
  long *plVar2;
  code *pcVar3;
  long *plVar4;
  CPlayer CVar5;
  undefined1 uVar6;
  CPlayer CVar7;
  char cVar8;
  int iVar9;
  long lVar10;
  CGenericModel *this_00;
  long lVar11;
  uint uVar12;
  long lVar13;
  uint uVar14;
  long local_48;
  allocator local_39 [9];

  if (*(long *)(this + 0x200) != 0) {
    CVar7 = this[0xa16];
    CVar5 = (CPlayer)(**(code **)(*(long *)this + 0x48))();
    if (CVar7 != CVar5) {
      lVar10 = *(long *)(this + 0x650);
      lVar11 = *(long *)(this + 0x648);
      uVar14 = (uint)((ulong)(lVar10 - lVar11) >> 3);
      if (uVar14 != 0) {
        lVar13 = 0;
        uVar12 = 0;
        while( true ) {
          if ((lVar10 - lVar11 >> 3 != 0) &&
             (plVar2 = *(long **)(lVar11 + lVar13), plVar2 != (long *)0x0)) {
            pcVar3 = *(code **)(*plVar2 + 0x40);
            uVar6 = (**(code **)(*(long *)this + 0x48))(this);
            (*pcVar3)(plVar2,uVar6);
          }
          uVar12 = uVar12 + 1;
          lVar13 = lVar13 + 8;
          if (uVar14 <= uVar12) break;
          lVar10 = *(long *)(this + 0x650);
          lVar11 = *(long *)(this + 0x648);
        }
      }
    }
    CVar7 = (CPlayer)(**(code **)(*(long *)this + 0x48))(this);
    this[0xa16] = CVar7;
    CCharacter::updateAnimation(param_1);
    plVar2 = *(long **)(this + 0x830);
    if ((plVar2 != (long *)0x0) && (plVar4 = *(long **)(this + 0x848), plVar4 != (long *)0x0)) {
      if (*(int *)(this + 0x330) - 0x20U < 3) {
        (**(code **)(*plVar4 + 0x378))(plVar4,1,1);
        updateFishingLine(param_1);
        if ((*(CGenericModel **)(this + 0x830))[0x81] != (CGenericModel)0x0) {
          CGenericModel::updateAnimation(*(CGenericModel **)(this + 0x830),param_1,false);
        }
      }
      else {
        (**(code **)(*plVar2 + 0x50))(plVar2,0);
        (**(code **)(**(long **)(this + 0x848) + 0x378))(*(long **)(this + 0x848),0,1);
      }
    }
                    /* try { // try from 008f0e36 to 008f0e3a has its CatchHandler @ 008f0f12 */
    iVar9 = CCharacter::HP((CCharacter *)this);
    if (((float)iVar9 <= DAT_00fa47f8) && (!NAN((float)iVar9) && !NAN(DAT_00fa47f8))) {
                    /* try { // try from 008f0e9c to 008f0ebc has its CatchHandler @ 008f0f12 */
      std::string::string((string *)&local_48,"DIE",local_39);
      this_00 = (CGenericModel *)(**(code **)(*(long *)this + 0x1e0))(this);
      cVar8 = CGenericModel::animationPlayingSubstring(this_00,(string *)&local_48);
      if ((allocator *)(local_48 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage)
      {
        LOCK();
        piVar1 = (int *)(local_48 + -8);
        iVar9 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar9 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_48 + -0x18));
        }
      }
      if (cVar8 != '\0') {
        *(undefined4 *)(this + 0x884) = 0x3f000000;
        return;
      }
    }
  }
  return;
}



/* address=008f0f60
   symbol=CPlayer::fishingAI */

/* WARNING: Removing unreachable block (ram,0x008f1368) */
/* WARNING: Removing unreachable block (ram,0x008f135d) */
/* CPlayer::fishingAI(float, CLevel&) */

void CPlayer::fishingAI(float param_1,CLevel *param_2)

{
  int *piVar1;
  int iVar2;
  float fVar3;
  char cVar4;
  bool bVar5;
  float fVar6;
  undefined4 uVar7;
  float fVar8;
  float local_5c;
  long local_58 [2];
  long local_48;
  allocator local_3a;
  allocator local_39 [9];

  fVar6 = DAT_00fa8768;
  *(float *)(param_2 + 0x854) = param_1 * DAT_00fa8768 + *(float *)(param_2 + 0x854);
  fVar3 = DAT_00fa47fc;
  fVar8 = *(float *)(param_2 + 0x850);
  if ((DAT_00fa4824 <= fVar8) || (fVar8 <= DAT_00fa47fc)) {
    if (DAT_00fa4824 <= fVar8) {
      local_5c = *(float *)(param_2 + 0x858);
      fVar6 = 0.0;
      fVar8 = DAT_00fa872c;
    }
    else {
      if (DAT_00fa47fc < fVar8) goto LAB_008f0fe8;
      local_5c = *(float *)(param_2 + 0x858);
      fVar8 = DAT_00fa4810;
      fVar6 = DAT_00fa86e0;
    }
  }
  else {
    local_5c = *(float *)(param_2 + 0x858);
    fVar8 = DAT_00fd3a58;
  }
  fVar8 = (float)UTILITIES::randomBetweenVolatile(fVar8,fVar6);
  *(float *)(param_2 + 0x858) = fVar8 * param_1 + local_5c;
  fVar8 = *(float *)(param_2 + 0x850);
LAB_008f0fe8:
  if ((fVar8 < DAT_00fce4b8) && (!NAN(fVar8) && !NAN(DAT_00fce4b8))) {
    fVar8 = (float)UTILITIES::randomBetweenVolatile(0.0,DAT_00fc6764);
    if ((fVar8 < DAT_00fa86d0) && (!NAN(fVar8) && !NAN(DAT_00fa86d0))) {
      fVar8 = *(float *)(param_2 + 0x858);
      fVar6 = (float)UTILITIES::randomBetweenVolatile(DAT_00fa4820,DAT_00fa8748);
      *(float *)(param_2 + 0x858) = fVar6 + fVar8;
    }
  }
  if (DAT_00fa47f8 < *(float *)(param_2 + 0x860)) {
    *(float *)(param_2 + 0x860) = *(float *)(param_2 + 0x860) - param_1;
  }
  fVar8 = *(float *)(param_2 + 0x858);
  if ((DAT_00fa86e0 <= fVar8) || (NAN(fVar8) || NAN(DAT_00fa86e0))) {
    *(undefined4 *)(param_2 + 0x858) = 0x41200000;
    fVar8 = 10.0;
  }
  else if (fVar8 <= DAT_00fce4a0) {
    fVar8 = DAT_00fce4a0;
  }
  *(float *)(param_2 + 0x858) = fVar8;
  fVar8 = param_1 * fVar8 + *(float *)(param_2 + 0x850);
  if (DAT_00fa4824 <= fVar8) {
    fVar8 = DAT_00fa4824;
  }
  *(float *)(param_2 + 0x850) = fVar8;
  fVar6 = sinf(*(float *)(param_2 + 0x854));
  if (fVar6 * DAT_00fa86e8 + fVar8 <= fVar3) {
    *(undefined4 *)(param_2 + 0x850) = 0x3f800000;
    *(undefined4 *)(param_2 + 0x858) = 0x3f800000;
                    /* try { // try from 008f113c to 008f1155 has its CatchHandler @ 008f1336 */
    std::string::string((string *)&local_48,"FISHING_CAST",local_39);
    cVar4 = CGenericModel::animationPlayingSubstring
                      (*(CGenericModel **)(param_2 + 0x200),(string *)&local_48);
    bVar5 = false;
    if (cVar4 == '\0') {
                    /* try { // try from 008f12b2 to 008f12cb has its CatchHandler @ 008f1336 */
      std::string::string((string *)local_58,"FISHING_BITE",&local_3a);
      cVar4 = CGenericModel::animationPlayingSubstring
                        (*(CGenericModel **)(param_2 + 0x200),(string *)local_58);
      bVar5 = cVar4 == '\0';
      if ((allocator *)(local_58[0] + -0x18) !=
          (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_58[0] + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar2 < 1) {
          std::string::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
        }
      }
    }
    if ((allocator *)(local_48 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_48 + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::string::_Rep::_M_destroy((allocator *)(local_48 + -0x18));
      }
    }
    if (bVar5) {
      uVar7 = UTILITIES::randomBetweenVolatile(DAT_00fce520,DAT_00fa4830);
      *(undefined4 *)(param_2 + 0x860) = uVar7;
      CCharacter::fishingSplash((CCharacter *)param_2);
    }
  }
  return;
}



/* address=008f1380
   symbol=CPlayer::removeItemFromInventoryOrPetsInventoryByGuid */

/* CPlayer::removeItemFromInventoryOrPetsInventoryByGuid(long long, bool, bool,
   UNITTYPES::EUNITTYPES) */

byte __thiscall
CPlayer::removeItemFromInventoryOrPetsInventoryByGuid
          (CPlayer *this,long param_1,char param_2,char param_3,undefined4 param_5)

{
  CInventory *pCVar1;
  CEquipment *pCVar2;
  long lVar3;
  char cVar4;
  uint uVar5;
  long *plVar6;
  uint uVar7;
  ulong uVar8;
  byte bVar9;
  byte local_69;
  long *local_58;
  uint local_50;
  uint local_4c;
  undefined4 local_48;

  pCVar1 = *(CInventory **)(this + 0x490);
  local_69 = 0;
  if (pCVar1 == (CInventory *)0x0) goto LAB_008f14b8;
  local_58 = (long *)0x0;
  local_50 = 0;
  local_4c = 0;
  local_48 = 10;
  if (param_1 == -1) {
                    /* try { // try from 008f13f3 to 008f1474 has its CatchHandler @ 008f16cf */
    CInventory::getEquipmentsOfQuestID(pCVar1,0xffffffff,(TArrayList *)&local_58);
    uVar7 = local_50;
LAB_008f13fc:
    if (uVar7 == 0) goto LAB_008f1499;
    local_69 = 0;
    uVar8 = 0;
    do {
      plVar6 = local_58;
      if ((uint)uVar8 < local_4c) {
        plVar6 = local_58 + uVar8;
      }
      pCVar2 = *(CEquipment **)(*plVar6 + 0x10);
      if ((pCVar2 != (CEquipment *)0x0) &&
         (cVar4 = CBaseUnit::ISA((CBaseUnit *)pCVar2,param_5), cVar4 != '\0')) {
        cVar4 = param_3;
        if (param_2 == '\0') {
          (**(code **)(*(long *)pCVar2 + 0x338))(pCVar2,0xffffffff);
          if (*(int *)(pCVar2 + 0x238) == 0) {
            cVar4 = '\x01';
            goto LAB_008f145b;
          }
        }
        else {
LAB_008f145b:
          CInventory::removeEquipment(pCVar1,pCVar2);
          if (cVar4 != '\0') {
            (**(code **)(*(long *)pCVar2 + 8))(pCVar2);
          }
        }
        local_69 = 1;
      }
      uVar7 = (uint)uVar8 + 1;
      uVar8 = (ulong)uVar7;
    } while (uVar7 < local_50);
  }
  else {
                    /* try { // try from 008f1621 to 008f1625 has its CatchHandler @ 008f16cf */
    CInventory::getEquipmentsOfQuestID(pCVar1,0xffffffff,(TArrayList *)&local_58);
    if (local_50 != 0) {
      uVar5 = 0;
      uVar7 = local_50;
      do {
        plVar6 = local_58;
        if (uVar5 < local_4c) {
          plVar6 = local_58 + uVar5;
        }
        if (param_1 != *(long *)(*(long *)(*plVar6 + 0x10) + 0x1a0)) {
          if (uVar5 < uVar7) {
            local_50 = uVar7 - 1;
            local_58[uVar5] = local_58[local_50];
            uVar7 = local_50;
          }
          uVar5 = uVar5 - 1;
        }
        uVar5 = uVar5 + 1;
      } while (uVar5 < uVar7);
      goto LAB_008f13fc;
    }
LAB_008f1499:
    local_69 = 0;
  }
  if (local_58 != (long *)0x0) {
    operator_delete__(local_58);
  }
LAB_008f14b8:
  if ((*(long *)(this + 0x650) - (long)*(long **)(this + 0x648) >> 3 != 0) &&
     (lVar3 = **(long **)(this + 0x648), lVar3 != 0)) {
    pCVar1 = *(CInventory **)(lVar3 + 0x490);
    bVar9 = 0;
    if (pCVar1 != (CInventory *)0x0) {
      local_58 = (long *)0x0;
      local_50 = 0;
      local_4c = 0;
      local_48 = 10;
      if (param_1 == -1) {
                    /* try { // try from 008f16ab to 008f16af has its CatchHandler @ 008f16b5 */
        CInventory::getEquipmentsOfQuestID(pCVar1,-1,(TArrayList *)&local_58);
      }
      else {
                    /* try { // try from 008f1538 to 008f15bc has its CatchHandler @ 008f16b5 */
        CInventory::getEquipmentsOfUnitGuid(pCVar1,param_1,(TArrayList *)&local_58);
      }
      if (local_50 == 0) {
        bVar9 = 0;
      }
      else {
        bVar9 = 0;
        uVar7 = 0;
        do {
          plVar6 = local_58;
          if (uVar7 < local_4c) {
            plVar6 = local_58 + uVar7;
          }
          pCVar2 = *(CEquipment **)(*plVar6 + 0x10);
          if ((pCVar2 != (CEquipment *)0x0) &&
             (cVar4 = CBaseUnit::ISA((CBaseUnit *)pCVar2,param_5), cVar4 != '\0')) {
            cVar4 = param_3;
            if (param_2 == '\0') {
              (**(code **)(*(long *)pCVar2 + 0x338))(pCVar2,0xffffffff);
              if (*(int *)(pCVar2 + 0x238) == 0) {
                cVar4 = '\x01';
                goto LAB_008f15a3;
              }
            }
            else {
LAB_008f15a3:
              CInventory::removeEquipment(pCVar1,pCVar2);
              if (cVar4 != '\0') {
                (**(code **)(*(long *)pCVar2 + 8))(pCVar2);
              }
            }
            bVar9 = 1;
          }
          uVar7 = uVar7 + 1;
        } while (uVar7 < local_50);
      }
      if (local_58 != (long *)0x0) {
        operator_delete__(local_58);
      }
    }
    local_69 = local_69 | bVar9;
  }
  return local_69;
}



/* address=008f16e0
   symbol=CPlayer::removeQuestItemFromInventoryOrPetsInventoryByGuid */

/* CPlayer::removeQuestItemFromInventoryOrPetsInventoryByGuid(long long, long long, bool, bool,
   UNITTYPES::EUNITTYPES) */

byte __thiscall
CPlayer::removeQuestItemFromInventoryOrPetsInventoryByGuid
          (CPlayer *this,longlong param_1,long param_2,char param_3,char param_4,undefined4 param_6)

{
  CInventory *pCVar1;
  CEquipment *pCVar2;
  long lVar3;
  char cVar4;
  uint uVar5;
  long *plVar6;
  uint uVar7;
  ulong uVar8;
  byte bVar9;
  byte local_71;
  long *local_58;
  uint local_50;
  uint local_4c;
  undefined4 local_48;

  pCVar1 = *(CInventory **)(this + 0x490);
  local_71 = 0;
  if (pCVar1 != (CInventory *)0x0) {
    local_58 = (long *)0x0;
    local_50 = 0;
    local_4c = 0;
    local_48 = 10;
    if (param_2 == -1) {
                    /* try { // try from 008f175a to 008f17dd has its CatchHandler @ 008f1aef */
      CInventory::getEquipmentsOfQuestID(pCVar1,param_1,(TArrayList *)&local_58);
      uVar7 = local_50;
LAB_008f1763:
      if (uVar7 == 0) goto LAB_008f1802;
      local_71 = 0;
      uVar8 = 0;
      do {
        plVar6 = local_58;
        if ((uint)uVar8 < local_4c) {
          plVar6 = local_58 + uVar8;
        }
        pCVar2 = *(CEquipment **)(*plVar6 + 0x10);
        if ((pCVar2 != (CEquipment *)0x0) &&
           (cVar4 = CBaseUnit::ISA((CBaseUnit *)pCVar2,param_6), cVar4 != '\0')) {
          cVar4 = param_4;
          if (param_3 == '\0') {
            (**(code **)(*(long *)pCVar2 + 0x338))(pCVar2,0xffffffff);
            if (*(int *)(pCVar2 + 0x238) == 0) {
              cVar4 = '\x01';
              goto LAB_008f17c3;
            }
          }
          else {
LAB_008f17c3:
            CInventory::removeEquipment(pCVar1,pCVar2);
            if (cVar4 != '\0') {
              (**(code **)(*(long *)pCVar2 + 8))(pCVar2);
            }
          }
          local_71 = 1;
        }
        uVar7 = (uint)uVar8 + 1;
        uVar8 = (ulong)uVar7;
      } while (uVar7 < local_50);
    }
    else {
      if (param_1 == -1) {
                    /* try { // try from 008f19a1 to 008f19bc has its CatchHandler @ 008f1aef */
        CInventory::getEquipmentsOfUnitGuid(pCVar1,param_2,(TArrayList *)&local_58);
        uVar7 = local_50;
        goto LAB_008f1763;
      }
      CInventory::getEquipmentsOfQuestID(pCVar1,param_1,(TArrayList *)&local_58);
      if (local_50 != 0) {
        uVar5 = 0;
        uVar7 = local_50;
        do {
          plVar6 = local_58;
          if (uVar5 < local_4c) {
            plVar6 = local_58 + uVar5;
          }
          if (param_2 != *(long *)(*(long *)(*plVar6 + 0x10) + 0x1a0)) {
            if (uVar5 < uVar7) {
              local_50 = uVar7 - 1;
              local_58[uVar5] = local_58[local_50];
              uVar7 = local_50;
            }
            uVar5 = uVar5 - 1;
          }
          uVar5 = uVar5 + 1;
        } while (uVar5 < uVar7);
        goto LAB_008f1763;
      }
LAB_008f1802:
      local_71 = 0;
    }
    if (local_58 != (long *)0x0) {
      operator_delete__(local_58);
    }
  }
  if (*(long *)(this + 0x650) - (long)*(long **)(this + 0x648) >> 3 == 0) {
    return local_71;
  }
  lVar3 = **(long **)(this + 0x648);
  if (lVar3 == 0) {
    return local_71;
  }
  pCVar1 = *(CInventory **)(lVar3 + 0x490);
  bVar9 = 0;
  if (pCVar1 == (CInventory *)0x0) goto LAB_008f1973;
  local_58 = (long *)0x0;
  local_50 = 0;
  local_4c = 0;
  local_48 = 10;
  if (param_2 == -1) {
                    /* try { // try from 008f18ab to 008f192d has its CatchHandler @ 008f1ad5 */
    CInventory::getEquipmentsOfQuestID(pCVar1,param_1,(TArrayList *)&local_58);
    uVar7 = local_50;
LAB_008f18b4:
    if (uVar7 == 0) goto LAB_008f1953;
    bVar9 = 0;
    uVar7 = 0;
    do {
      plVar6 = local_58;
      if (uVar7 < local_4c) {
        plVar6 = local_58 + uVar7;
      }
      pCVar2 = *(CEquipment **)(*plVar6 + 0x10);
      if ((pCVar2 != (CEquipment *)0x0) &&
         (cVar4 = CBaseUnit::ISA((CBaseUnit *)pCVar2,param_6), cVar4 != '\0')) {
        cVar4 = param_4;
        if (param_3 == '\0') {
          (**(code **)(*(long *)pCVar2 + 0x338))(pCVar2,0xffffffff);
          if (*(int *)(pCVar2 + 0x238) == 0) {
            cVar4 = '\x01';
            goto LAB_008f1913;
          }
        }
        else {
LAB_008f1913:
          CInventory::removeEquipment(pCVar1,pCVar2);
          if (cVar4 != '\0') {
            (**(code **)(*(long *)pCVar2 + 8))(pCVar2);
          }
        }
        bVar9 = 1;
      }
      uVar7 = uVar7 + 1;
    } while (uVar7 < local_50);
  }
  else {
    if (param_1 == -1) {
                    /* try { // try from 008f1a44 to 008f1a61 has its CatchHandler @ 008f1ad5 */
      CInventory::getEquipmentsOfUnitGuid(pCVar1,param_2,(TArrayList *)&local_58);
      uVar7 = local_50;
      goto LAB_008f18b4;
    }
    CInventory::getEquipmentsOfQuestID(pCVar1,param_1,(TArrayList *)&local_58);
    if (local_50 != 0) {
      uVar5 = 0;
      uVar7 = local_50;
      do {
        plVar6 = local_58;
        if (uVar5 < local_4c) {
          plVar6 = local_58 + uVar5;
        }
        if (param_2 != *(long *)(*(long *)(*plVar6 + 0x10) + 0x1a0)) {
          if (uVar5 < uVar7) {
            local_50 = uVar7 - 1;
            local_58[uVar5] = local_58[local_50];
            uVar7 = local_50;
          }
          uVar5 = uVar5 - 1;
        }
        uVar5 = uVar5 + 1;
      } while (uVar5 < uVar7);
      goto LAB_008f18b4;
    }
LAB_008f1953:
    bVar9 = 0;
  }
  if (local_58 != (long *)0x0) {
    operator_delete__(local_58);
  }
LAB_008f1973:
  return local_71 | bVar9;
}



/* address=008f3450
   symbol=CPlayer::CPlayer */

/* WARNING: Removing unreachable block (ram,0x008f3af4) */
/* WARNING: Removing unreachable block (ram,0x008f3b8a) */
/* WARNING: Removing unreachable block (ram,0x008f3ae6) */
/* CPlayer::CPlayer(CResourceManager*) */

void __thiscall CPlayer::CPlayer(CPlayer *this,CResourceManager *param_1)

{
  int *piVar1;
  code *pcVar2;
  long lVar3;
  CPlayer *pCVar4;
  CPath *pCVar5;
  CDynamicLine *pCVar6;
  long *plVar7;
  undefined8 uVar8;
  CFileSystem *this_00;
  int iVar9;
  undefined4 local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  long local_68 [2];
  long local_58 [2];
  long local_48;
  allocator local_39 [9];

  CCharacter::CCharacter((CCharacter *)this,param_1);
  *(undefined ***)this = &PTR__CPlayer_00fd3510;
  *(undefined ***)(this + 0x1d8) = &PTR__CPlayer_00fd3940;
  *(undefined ***)(this + 0x1e0) = &PTR__CPlayer_00fd3990;
  *(undefined8 *)(this + 0x778) = 0;
  this[0x790] = (CPlayer)0x0;
  this[0x791] = (CPlayer)0x4e;
  *(undefined8 *)(this + 0x798) = 0;
  *(undefined8 *)(this + 0x7a0) = 0;
  *(undefined8 *)(this + 0x7a8) = 0;
  this[0x7b0] = (CPlayer)0x0;
  *(undefined4 *)(this + 0x7b4) = 1;
                    /* try { // try from 008f34e5 to 008f34e9 has its CatchHandler @ 008f39d6 */
  std::wstring::wstring((wstring_conflict *)(this + 0x7b8),(wstring_conflict *)&::EMPTY_WSTRING);
  *(undefined4 *)(this + 0x7cc) = 0;
                    /* try { // try from 008f3507 to 008f350b has its CatchHandler @ 008f3b79 */
  std::wstring::wstring((wstring_conflict *)(this + 2000),(wstring_conflict *)&::EMPTY_WSTRING);
  *(undefined4 *)(this + 0x7d8) = 0;
  *(undefined8 *)(this + 0x828) = 0;
  lVar3 = 0;
  *(undefined8 *)(this + 0x830) = 0;
  *(undefined8 *)(this + 0x838) = 0;
  *(undefined8 *)(this + 0x840) = 0;
  *(undefined8 *)(this + 0x848) = 0;
  *(undefined4 *)(this + 0x850) = 0x40000000;
  *(undefined4 *)(this + 0x854) = 0;
  *(undefined4 *)(this + 0x858) = 0;
  this[0x85c] = (CPlayer)0x0;
  *(undefined4 *)(this + 0x864) = 0;
  *(undefined8 *)(this + 0x868) = 0;
  *(undefined4 *)(this + 0x870) = 0;
  *(undefined4 *)(this + 0x874) = 0;
  *(undefined4 *)(this + 0x878) = 0;
  *(undefined4 *)(this + 0x87c) = 0;
  *(undefined4 *)(this + 0x880) = 0;
  *(undefined4 *)(this + 0x884) = 0x41200000;
  *(undefined4 **)(this + 0x888) = &DAT_01424558;
  *(undefined4 **)(this + 0x890) = &DAT_01424558;
  *(undefined4 **)(this + 0x898) = &DAT_01424558;
  *(undefined4 **)(this + 0x8a0) = &DAT_01424558;
  *(undefined4 **)(this + 0x8a8) = &DAT_01424558;
  *(undefined4 *)(this + 0xa10) = 0;
  this[0xa14] = (CPlayer)0x0;
  this[0xa15] = (CPlayer)0x0;
  this[0xa16] = (CPlayer)0x0;
  *(undefined8 *)(this + 0xa40) = 0;
  *(undefined4 *)(this + 0xa48) = 0;
  *(undefined4 *)(this + 0xa4c) = 0;
  *(undefined4 *)(this + 0xa50) = 5;
  *(undefined8 *)(this + 0xa58) = 0;
  *(undefined4 *)(this + 0xa60) = 0;
  *(undefined4 *)(this + 0xa64) = 0;
  *(undefined4 *)(this + 0xa68) = 10;
  *(undefined4 *)(this + 0x418) = 2000;
  *(undefined4 *)(this + 0x414) = 0x44fa0000;
  *(undefined4 *)(this + 0x288) = 0x41a00000;
  *(undefined4 *)(this + 0x42c) = 10;
  *(undefined4 *)(this + 0x428) = 0;
  *(undefined4 *)(this + 0x434) = 3;
  *(undefined4 *)(this + 0x430) = 10;
  *(undefined4 *)(this + 0x424) = 4;
  *(undefined8 *)(this + 0x780) = 0xffffffffffffffff;
  *(undefined8 *)(this + 0x788) = 0xffffffffffffffff;
  do {
    *(undefined8 *)(this + lVar3 + 0x8b0) = 0xffffffffffffffff;
    *(undefined8 *)(this + lVar3 + 0x900) = 0xffffffffffffffff;
    lVar3 = lVar3 + 8;
  } while (lVar3 != 0x50);
  lVar3 = 0;
  do {
    *(undefined8 *)(this + lVar3 + 0x950) = 0xffffffffffffffff;
    *(undefined8 *)(this + lVar3 + 0x9b0) = 0xffffffffffffffff;
    lVar3 = lVar3 + 8;
  } while (lVar3 != 0x60);
  pCVar4 = this;
  do {
    pCVar4[0xa17] = (CPlayer)0x0;
    pCVar4 = pCVar4 + 1;
  } while (pCVar4 != this + 0x22);
                    /* try { // try from 008f3754 to 008f3758 has its CatchHandler @ 008f3b71 */
  std::string::string((string *)&local_48,(string *)&::EMPTY_STRING);
  local_78 = 0;
  local_74 = 0;
  local_70 = 0;
                    /* try { // try from 008f377c to 008f3780 has its CatchHandler @ 008f3b85 */
  pCVar5 = (CPath *)Ogre::NedAllocImpl::allocBytes(200,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 008f3791 to 008f3795 has its CatchHandler @ 008f3b52 */
  CPath::CPath(pCVar5,(string *)&local_48,0);
  *(CPath **)(this + 0x838) = pCVar5;
  if ((allocator *)(local_48 + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_48 + -8);
    iVar9 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar9 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_48 + -0x18));
    }
  }
                    /* try { // try from 008f37c7 to 008f37cb has its CatchHandler @ 008f3b71 */
  pCVar6 = (CDynamicLine *)Ogre::NedAllocImpl::allocBytes(0x238,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 008f37d7 to 008f37db has its CatchHandler @ 008f3b12 */
  CDynamicLine::CDynamicLine(pCVar6,2);
  *(CDynamicLine **)(this + 0x840) = pCVar6;
  local_88 = 0;
  local_84 = 0;
  local_80 = 0;
                    /* try { // try from 008f381e to 008f38de has its CatchHandler @ 008f3b71 */
  CPath::AddPoint(*(CPath **)(this + 0x838),(Vector3 *)&local_88,DAT_00fce4d4,DAT_00fa8778);
  local_98 = 0;
  local_94 = 0;
  local_90 = 0;
  CPath::AddPoint(*(CPath **)(this + 0x838),(Vector3 *)&local_98,DAT_00fce4d4,DAT_00fa8778);
  local_a8 = 0;
  local_a4 = 0;
  local_a0 = 0;
  CPath::AddPoint(*(CPath **)(this + 0x838),(Vector3 *)&local_a8,DAT_00fce4d4,DAT_00fa8778);
  iVar9 = 0;
  do {
    CDynamicLine::addPoint(*(CDynamicLine **)(this + 0x840),0.0,0.0,0.0);
    iVar9 = iVar9 + 1;
  } while (iVar9 != 0x10);
  plVar7 = (long *)0x0;
  if (*(long *)(this + 0x68) != 0) {
    plVar7 = *(long **)(*(long *)(this + 0x68) + 0x10);
  }
  plVar7 = (long *)(**(code **)(*plVar7 + 0x250))();
  pcVar2 = *(code **)(*plVar7 + 0x328);
                    /* try { // try from 008f38fe to 008f3902 has its CatchHandler @ 008f3b0a */
  std::string::string((string *)local_58,"line_",local_39);
                    /* try { // try from 008f390e to 008f3912 has its CatchHandler @ 008f3b02 */
  STRINGS::uniqueName((STRINGS *)local_68,(string *)local_58);
                    /* try { // try from 008f3923 to 008f3925 has its CatchHandler @ 008f3a54 */
  uVar8 = (*pcVar2)(plVar7,(STRINGS *)local_68,&Ogre::Vector3::ZERO,&Ogre::Quaternion::IDENTITY);
  *(undefined8 *)(this + 0x848) = uVar8;
  if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_68[0] + -8);
    iVar9 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar9 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
    }
  }
  if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_58[0] + -8);
    iVar9 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar9 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
    }
  }
                    /* try { // try from 008f3969 to 008f39c3 has its CatchHandler @ 008f3b71 */
  (**(code **)(**(long **)(this + 0x848) + 0x278))
            (*(long **)(this + 0x848),*(undefined8 *)(this + 0x840));
  (**(code **)(**(long **)(this + 0x848) + 0x378))(*(long **)(this + 0x848),0,1);
  CCharacter::setAlignment((CCharacter *)this,1);
  lVar3 = 0;
  do {
    *(undefined4 *)(this + lVar3 + 0x7dc) = 0;
    lVar3 = lVar3 + 4;
  } while (lVar3 != 0x48);
  this_00 = (CFileSystem *)CFileSystem::getSingleton();
  CFileSystem::getEnabledModNames(this_00,(TArrayList *)(this + 0xa58));
  return;
}



/* address=008f3ba0
   symbol=CPlayer::updateStoredLevels */

/* WARNING: Removing unreachable block (ram,0x008f4460) */
/* WARNING: Removing unreachable block (ram,0x008f4482) */
/* WARNING: Removing unreachable block (ram,0x008f4472) */
/* WARNING: Removing unreachable block (ram,0x008f4492) */
/* CPlayer::updateStoredLevels(CLevel&) */

void __thiscall CPlayer::updateStoredLevels(CPlayer *this,CLevel *param_1)

{
  allocator *paVar1;
  wchar_t *pwVar2;
  wchar_t wVar3;
  float fVar4;
  wchar_t *pwVar5;
  long lVar6;
  size_t sVar7;
  bool bVar8;
  int iVar9;
  int iVar10;
  long lVar11;
  ulong uVar12;
  long *plVar13;
  long lVar14;
  ulong uVar15;
  uint uVar16;
  long lVar17;
  bool bVar18;
  bool bVar19;
  bool bVar20;
  float fVar21;
  long local_b0;
  uint local_a8;
  uint local_84;
  wchar_t *local_78 [2];
  wchar_t *local_68;
  wchar_t *local_58 [2];
  wchar_t *local_48;

  lVar17 = *(long *)(this + 0x7a0);
  lVar14 = *(long *)(this + 0x798);
  lVar11 = CGameGlobals::getSingleton();
  if (*(int *)(lVar11 + 0x2c0) < (int)((ulong)(lVar17 - lVar14) >> 3)) {
    lVar17 = *(long *)(this + 0x7a0);
    lVar14 = *(long *)(this + 0x798);
    if (lVar17 - lVar14 >> 3 != 0) {
      lVar11 = *(long *)(this + 0x868);
      uVar15 = 0;
      local_a8 = 0;
      local_84 = 0xffffffff;
      fVar21 = DAT_00fc54ec;
      if (lVar11 == 0) goto LAB_008f3de8;
LAB_008f3c40:
      if (*(int *)(lVar11 + 0x20) < 1) goto LAB_008f3de8;
      local_b0 = uVar15 * 8;
      lVar17 = 0;
      uVar16 = 0;
      bVar20 = false;
      do {
        CQuest::getQuestDetails();
        pwVar2 = local_48;
        bVar18 = false;
        paVar1 = (allocator *)(local_48 + -6);
        if (*(size_t *)(local_48 + -6) == *(size_t *)(::EMPTY_WSTRING + -6)) {
          iVar10 = wmemcmp(local_48,::EMPTY_WSTRING,*(size_t *)(local_48 + -6));
          bVar18 = iVar10 == 0;
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
        bVar8 = bVar20;
        if (!bVar18) {
          lVar14 = *(long *)(*(long *)(this + 0x798) + local_b0);
          if (uVar16 < *(uint *)(lVar11 + 0x24)) {
            plVar13 = (long *)(lVar17 + *(long *)(lVar11 + 0x18));
          }
          else {
            plVar13 = *(long **)(lVar11 + 0x18);
          }
                    /* try { // try from 008f3cde to 008f3ce2 has its CatchHandler @ 008f4470 */
          STRINGS::StringUpper((STRINGS *)local_58,(wstring_conflict *)(*plVar13 + 0x30));
          pwVar2 = local_58[0];
          pwVar5 = *(wchar_t **)(lVar14 + 0x18);
          paVar1 = (allocator *)(local_58[0] + -6);
          if ((*(size_t *)(local_58[0] + -6) == *(size_t *)(pwVar5 + -6)) &&
             (iVar10 = wmemcmp(local_58[0],pwVar5,*(size_t *)(local_58[0] + -6)), iVar10 == 0)) {
            if (uVar16 < *(uint *)(lVar11 + 0x24)) {
              plVar13 = (long *)(lVar17 + *(long *)(lVar11 + 0x18));
            }
            else {
              plVar13 = *(long **)(lVar11 + 0x18);
            }
            bVar18 = *(int *)(*plVar13 + 0x20) ==
                     *(int *)(*(long *)(*(long *)(this + 0x798) + local_b0) + 0x10);
          }
          else {
            bVar18 = false;
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
          bVar8 = true;
          if (!bVar18) {
            bVar8 = bVar20;
          }
        }
        uVar16 = uVar16 + 1;
        lVar17 = lVar17 + 8;
        bVar20 = bVar8;
      } while ((int)uVar16 < *(int *)(lVar11 + 0x20));
      lVar14 = *(long *)(this + 0x798);
      lVar17 = *(long *)(this + 0x7a0);
      do {
        lVar11 = *(long *)(lVar14 + local_b0);
        if (((*(char *)(lVar11 + 0xb1) == '\0') && (!bVar8)) && (*(char *)(lVar11 + 0xb0) == '\0'))
        {
          iVar10 = *(int *)(lVar11 + 0x10);
          if (iVar10 == *(int *)(param_1 + 0x1a4)) {
            sVar7 = *(size_t *)(*(wchar_t **)(lVar11 + 0x18) + -6);
            if ((sVar7 == *(size_t *)(*(wchar_t **)(param_1 + 0x280) + -6)) &&
               (iVar9 = wmemcmp(*(wchar_t **)(lVar11 + 0x18),*(wchar_t **)(param_1 + 0x280),sVar7),
               iVar9 == 0)) goto LAB_008f3db6;
          }
          if (*(int *)(this + 0x7cc) == iVar10) {
            sVar7 = *(size_t *)(*(wchar_t **)(lVar11 + 0x18) + -6);
            if ((sVar7 == *(size_t *)(*(wchar_t **)(this + 2000) + -6)) &&
               (iVar9 = wmemcmp(*(wchar_t **)(lVar11 + 0x18),*(wchar_t **)(this + 2000),sVar7),
               iVar9 == 0)) goto LAB_008f3db6;
          }
          if (*(int *)(this + 0x7b4) == iVar10) {
            sVar7 = *(size_t *)(*(wchar_t **)(lVar11 + 0x18) + -6);
            if (((sVar7 == *(size_t *)(*(wchar_t **)(this + 0x7b8) + -6)) &&
                (iVar10 = wmemcmp(*(wchar_t **)(lVar11 + 0x18),*(wchar_t **)(this + 0x7b8),sVar7),
                iVar10 == 0)) && (this[0x7b0] != (CPlayer)0x0)) goto LAB_008f3db6;
          }
          if (*(float *)(lVar11 + 0x98) < fVar21) {
            local_84 = local_a8;
            fVar21 = *(float *)(lVar11 + 0x98);
          }
        }
LAB_008f3db6:
        local_a8 = local_a8 + 1;
        uVar15 = (ulong)local_a8;
        uVar12 = lVar17 - lVar14 >> 3;
        if (uVar12 <= uVar15) {
          if (local_84 == 0xffffffff) goto LAB_008f3f57;
          removeLevelSavedState(this,local_84);
          goto LAB_008f3f42;
        }
        lVar11 = *(long *)(this + 0x868);
        if (lVar11 != 0) goto LAB_008f3c40;
LAB_008f3de8:
        local_b0 = uVar15 << 3;
        bVar8 = false;
      } while( true );
    }
  }
  else {
LAB_008f3f42:
    lVar14 = *(long *)(this + 0x798);
    uVar12 = *(long *)(this + 0x7a0) - lVar14 >> 3;
LAB_008f3f57:
    if (0 < (int)uVar12) {
      local_84 = 0;
      do {
        lVar11 = (long)(int)local_84;
        lVar17 = *(long *)(lVar14 + lVar11 * 8);
        if (*(int *)(this + 0x7cc) == *(int *)(lVar17 + 0x10)) {
          sVar7 = *(size_t *)(*(wchar_t **)(lVar17 + 0x18) + -6);
          if (sVar7 != *(size_t *)(*(wchar_t **)(this + 2000) + -6)) goto LAB_008f3f9c;
          iVar10 = wmemcmp(*(wchar_t **)(lVar17 + 0x18),*(wchar_t **)(this + 2000),sVar7);
          bVar20 = iVar10 == 0;
        }
        else {
LAB_008f3f9c:
          bVar20 = false;
        }
        lVar6 = *(long *)(this + 0x868);
        bVar18 = false;
        if (DAT_00fa8760 != *(float *)(lVar17 + 0x98)) {
          bVar18 = bVar20;
        }
        if (NAN(DAT_00fa8760) || NAN(*(float *)(lVar17 + 0x98))) {
          bVar18 = bVar20;
        }
        if ((lVar6 == 0) || (*(int *)(lVar6 + 0x20) < 1)) {
          bVar20 = false;
        }
        else {
          lVar17 = 0;
          uVar16 = 0;
          bVar8 = false;
          do {
            CQuest::getQuestDetails();
            pwVar2 = local_68;
            bVar19 = false;
            paVar1 = (allocator *)(local_68 + -6);
            if (*(size_t *)(local_68 + -6) == *(size_t *)(::EMPTY_WSTRING + -6)) {
              iVar10 = wmemcmp(local_68,::EMPTY_WSTRING,*(size_t *)(local_68 + -6));
              bVar19 = iVar10 == 0;
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
            bVar20 = bVar8;
            if (!bVar19) {
              lVar14 = *(long *)(*(long *)(this + 0x798) + lVar11 * 8);
              if (uVar16 < *(uint *)(lVar6 + 0x24)) {
                plVar13 = (long *)(lVar17 + *(long *)(lVar6 + 0x18));
              }
              else {
                plVar13 = *(long **)(lVar6 + 0x18);
              }
                    /* try { // try from 008f4073 to 008f4077 has its CatchHandler @ 008f4458 */
              STRINGS::StringUpper((STRINGS *)local_78,(wstring_conflict *)(*plVar13 + 0x30));
              pwVar2 = local_78[0];
              pwVar5 = *(wchar_t **)(lVar14 + 0x18);
              paVar1 = (allocator *)(local_78[0] + -6);
              if ((*(size_t *)(local_78[0] + -6) == *(size_t *)(pwVar5 + -6)) &&
                 (iVar10 = wmemcmp(local_78[0],pwVar5,*(size_t *)(local_78[0] + -6)), iVar10 == 0))
              {
                if (uVar16 < *(uint *)(lVar6 + 0x24)) {
                  plVar13 = (long *)(lVar17 + *(long *)(lVar6 + 0x18));
                }
                else {
                  plVar13 = *(long **)(lVar6 + 0x18);
                }
                bVar19 = *(int *)(*plVar13 + 0x20) ==
                         *(int *)(*(long *)(*(long *)(this + 0x798) + lVar11 * 8) + 0x10);
              }
              else {
                bVar19 = false;
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
              bVar20 = true;
              if (!bVar19) {
                bVar20 = bVar8;
              }
            }
            uVar16 = uVar16 + 1;
            lVar17 = lVar17 + 8;
            bVar8 = bVar20;
          } while ((int)uVar16 < *(int *)(lVar6 + 0x20));
          lVar14 = *(long *)(this + 0x798);
        }
        lVar17 = *(long *)(lVar14 + lVar11 * 8);
        if (*(char *)(lVar17 + 0xb1) == '\0') {
          fVar21 = *(float *)(lVar17 + 0x98);
          fVar4 = *(float *)(this + 0x388);
          lVar17 = CGameGlobals::getSingleton();
          if (fVar4 <= (float)*(int *)(lVar17 + 0x2c4) + fVar21) {
            lVar14 = *(long *)(this + 0x798);
            lVar17 = *(long *)(lVar14 + lVar11 * 8);
            if ((DAT_00fa8760 != *(float *)(lVar17 + 0x98)) ||
               (NAN(DAT_00fa8760) || NAN(*(float *)(lVar17 + 0x98)))) goto LAB_008f40e0;
          }
          else {
            lVar14 = *(long *)(this + 0x798);
            lVar17 = *(long *)(lVar14 + lVar11 * 8);
          }
          iVar10 = *(int *)(lVar17 + 0x10);
          if (iVar10 == *(int *)(param_1 + 0x1a4)) {
            sVar7 = *(size_t *)(*(wchar_t **)(lVar17 + 0x18) + -6);
            if ((sVar7 == *(size_t *)(*(wchar_t **)(param_1 + 0x280) + -6)) &&
               (iVar9 = wmemcmp(*(wchar_t **)(lVar17 + 0x18),*(wchar_t **)(param_1 + 0x280),sVar7),
               iVar9 == 0)) goto LAB_008f40e0;
          }
          if (!bVar18) {
            if (*(int *)(this + 0x7b4) == iVar10) {
              sVar7 = *(size_t *)(*(wchar_t **)(lVar17 + 0x18) + -6);
              if (((sVar7 == *(size_t *)(*(wchar_t **)(this + 0x7b8) + -6)) &&
                  (iVar10 = wmemcmp(*(wchar_t **)(lVar17 + 0x18),*(wchar_t **)(this + 0x7b8),sVar7),
                  iVar10 == 0)) && (this[0x7b0] != (CPlayer)0x0)) goto LAB_008f40e0;
            }
            if ((!bVar20) && (*(char *)(lVar17 + 0xb0) == '\0')) {
              removeLevelSavedState(this,local_84);
              local_84 = local_84 - 1;
              lVar14 = *(long *)(this + 0x798);
            }
          }
        }
LAB_008f40e0:
        local_84 = local_84 + 1;
      } while ((int)local_84 < (int)(*(long *)(this + 0x7a0) - lVar14 >> 3));
    }
  }
  return;
}



/* address=008f4780
   symbol=CPlayer::loadModel */

/* WARNING: Removing unreachable block (ram,0x008f4abc) */
/* WARNING: Removing unreachable block (ram,0x008f4a83) */
/* WARNING: Removing unreachable block (ram,0x008f4aae) */
/* CPlayer::loadModel(std::wstring, std::wstring) */

void __thiscall
CPlayer::loadModel(CPlayer *this,wstring_conflict *param_2,wstring_conflict *param_3)

{
  int *piVar1;
  int iVar2;
  CResourceManager *this_00;
  long *plVar3;
  long lVar4;
  undefined8 uVar5;
  long *plVar6;
  long local_58 [2];
  long local_48 [2];
  long local_38;
  allocator local_29;

  if (*(long *)(this + 0x828) != 0) {
    plVar3 = (long *)Ogre::SceneNode::getParentSceneNode();
    if (plVar3 != (long *)0x0) {
      (**(code **)(*plVar3 + 0x1e0))(plVar3,*(undefined8 *)(*(long *)(this + 0x828) + 0x58));
    }
    if (*(long **)(this + 0x828) != (long *)0x0) {
      (**(code **)(**(long **)(this + 0x828) + 8))();
      *(undefined8 *)(this + 0x828) = 0;
    }
  }
  if (*(long *)(this + 0x830) != 0) {
    plVar3 = (long *)Ogre::SceneNode::getParentSceneNode();
    if (plVar3 != (long *)0x0) {
      (**(code **)(*plVar3 + 0x1e0))(plVar3,*(undefined8 *)(*(long *)(this + 0x830) + 0x58));
    }
    if (*(long **)(this + 0x830) != (long *)0x0) {
      (**(code **)(**(long **)(this + 0x830) + 8))();
      *(undefined8 *)(this + 0x830) = 0;
    }
  }
  std::wstring::wstring((wstring_conflict *)local_48,param_3);
                    /* try { // try from 008f484c to 008f4850 has its CatchHandler @ 008f4aa9 */
  std::wstring::wstring((wstring_conflict *)&local_38,param_2);
                    /* try { // try from 008f485a to 008f485e has its CatchHandler @ 008f4a8e */
  CCharacter::loadModel
            ((CCharacter *)this,(wstring_conflict *)&local_38,(wstring_conflict *)local_48);
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
  this_00 = *(CResourceManager **)(this + 0x68);
  lVar4 = CResourceManager::createGenericModel
                    (this_00,(SceneManager *)0x0,L"media/models/fishingpole/fishingpole.mesh",
                     *(wchar_t **)param_3,false,false,true);
  *(long *)(this + 0x828) = lVar4;
  (**(code **)(**(long **)(lVar4 + 0x60) + 0x140))();
  uVar5 = CResourceManager::createGenericModel
                    (this_00,(SceneManager *)0x0,L"media/models/fish/fish.mesh",*(wchar_t **)param_3
                     ,false,false,true);
  *(undefined8 *)(this + 0x830) = uVar5;
                    /* try { // try from 008f4902 to 008f4906 has its CatchHandler @ 008f4a7e */
  std::string::string((string *)local_58,"IDLE",&local_29);
                    /* try { // try from 008f4926 to 008f492a has its CatchHandler @ 008f4a6b */
  CGenericModel::playAnimation
            (*(CGenericModel **)(this + 0x830),(string *)local_58,true,DAT_00fa47fc,DAT_00fa8760);
  if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_58[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
    }
  }
  (**(code **)(**(long **)(this + 0x830) + 0x50))();
  CGenericModel::setRenderBehind(*(CGenericModel **)(this + 0x830),false);
  (**(code **)(**(long **)(*(long *)(this + 0x830) + 0x60) + 0x140))
            (*(long **)(*(long *)(this + 0x830) + 0x60),0x58);
  plVar3 = *(long **)(this + 0x2f0);
  if (plVar3 != (long *)0x0) {
    plVar6 = (long *)Ogre::SceneNode::getParentSceneNode();
    if (plVar6 != (long *)0x0) {
      (**(code **)(*plVar6 + 0x1e0))(plVar6,*(undefined8 *)(*(long *)(this + 0x828) + 0x58));
    }
    (**(code **)(*plVar3 + 0x1a8))(plVar3,*(undefined8 *)(*(long *)(this + 0x828) + 0x58));
    (**(code **)(*plVar3 + 0x378))(plVar3,0,1);
  }
  return;
}



/* address=008f4c60
   symbol=CPlayer::clearDungeonHistory */

/* WARNING: Removing unreachable block (ram,0x008f4d7b) */
/* CPlayer::clearDungeonHistory(std::wstring) */

void __thiscall CPlayer::clearDungeonHistory(CPlayer *this,wstring_conflict *param_2)

{
  int *piVar1;
  long lVar2;
  wchar_t *__s1;
  size_t __n;
  int iVar3;
  long lVar4;
  int iVar5;
  long lVar6;
  long lVar7;
  long local_48 [3];

  STRINGS::StringUpper((STRINGS *)local_48,param_2);
                    /* try { // try from 008f4c87 to 008f4c8b has its CatchHandler @ 008f4d3f */
  std::wstring::assign(param_2);
  if ((allocator *)(local_48[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_48[0] + -8);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
    }
  }
  lVar4 = *(long *)(this + 0x7a0);
  lVar7 = *(long *)(this + 0x798);
  lVar6 = 0;
  iVar5 = 0;
  if (0 < (int)(lVar4 - lVar7 >> 3)) {
    do {
      lVar2 = *(long *)(lVar7 + lVar6);
      __s1 = *(wchar_t **)(lVar2 + 0x18);
      __n = *(size_t *)(__s1 + -6);
      if ((__n == *(size_t *)(*(wchar_t **)param_2 + -6)) &&
         (iVar3 = wmemcmp(__s1,*(wchar_t **)param_2,__n), iVar3 == 0)) {
        *(undefined4 *)(lVar2 + 0x98) = 0xbf800000;
        lVar7 = *(long *)(this + 0x798);
        lVar4 = *(long *)(this + 0x7a0);
      }
      iVar5 = iVar5 + 1;
      lVar6 = lVar6 + 8;
    } while (iVar5 < (int)(lVar4 - lVar7 >> 3));
  }
  return;
}



/* address=008f4d90
   symbol=CPlayer::getMaxDepth */

/* WARNING: Removing unreachable block (ram,0x008f4ed3) */
/* CPlayer::getMaxDepth(std::wstring) */

undefined4 __thiscall CPlayer::getMaxDepth(CPlayer *this,wstring_conflict *param_2)

{
  int *piVar1;
  uint uVar2;
  uint uVar3;
  wchar_t *__s2;
  size_t __n;
  wchar_t *__s1;
  size_t sVar4;
  int iVar5;
  uint uVar6;
  long *plVar7;
  long lVar8;
  long local_48 [3];

  STRINGS::StringUpper((STRINGS *)local_48,param_2);
                    /* try { // try from 008f4db7 to 008f4dbb has its CatchHandler @ 008f4ec0 */
  std::wstring::assign(param_2);
  if ((allocator *)(local_48[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_48[0] + -8);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
    }
  }
  uVar2 = *(uint *)(this + 0xa48);
  if (uVar2 != 0) {
    __s2 = *(wchar_t **)param_2;
    uVar3 = *(uint *)(this + 0xa4c);
    lVar8 = 0;
    __n = *(size_t *)(__s2 + -6);
    uVar6 = 0;
    do {
      if (uVar6 < uVar3) {
        __s1 = (wchar_t *)**(long **)(lVar8 + *(long *)(this + 0xa40));
        sVar4 = *(size_t *)(__s1 + -6);
      }
      else {
        __s1 = *(wchar_t **)**(undefined8 **)(this + 0xa40);
        sVar4 = *(size_t *)(__s1 + -6);
      }
      if ((sVar4 == __n) && (iVar5 = wmemcmp(__s1,__s2,__n), iVar5 == 0)) {
        if (uVar6 < uVar3) {
          plVar7 = (long *)((ulong)uVar6 * 8 + *(long *)(this + 0xa40));
        }
        else {
          plVar7 = *(long **)(this + 0xa40);
        }
        return *(undefined4 *)(*plVar7 + 8);
      }
      uVar6 = uVar6 + 1;
      lVar8 = lVar8 + 8;
    } while (uVar6 < uVar2);
  }
  return 0xffffffff;
}



/* address=008f4ee0
   symbol=CPlayer::hasDungeonHistory */

/* WARNING: Removing unreachable block (ram,0x008f4fbe) */
/* CPlayer::hasDungeonHistory(std::wstring) */

undefined8 __thiscall CPlayer::hasDungeonHistory(CPlayer *this,wstring_conflict *param_2)

{
  int *piVar1;
  long lVar2;
  wchar_t *__s2;
  size_t __n;
  wchar_t *__s1;
  int iVar3;
  long lVar4;
  int iVar5;
  int iVar6;
  long local_48 [3];

  STRINGS::StringUpper((STRINGS *)local_48,param_2);
                    /* try { // try from 008f4f02 to 008f4f06 has its CatchHandler @ 008f4f7e */
  std::wstring::assign(param_2);
  if ((allocator *)(local_48[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_48[0] + -8);
    iVar6 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar6 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
    }
  }
  lVar2 = *(long *)(this + 0x798);
  iVar6 = (int)((ulong)(*(long *)(this + 0x7a0) - lVar2) >> 3);
  if (0 < iVar6) {
    __s2 = *(wchar_t **)param_2;
    iVar5 = 0;
    lVar4 = 0;
    __n = *(size_t *)(__s2 + -6);
    do {
      __s1 = *(wchar_t **)(*(long *)(lVar2 + lVar4) + 0x18);
      if ((*(size_t *)(__s1 + -6) == __n) && (iVar3 = wmemcmp(__s1,__s2,__n), iVar3 == 0)) {
        return 1;
      }
      iVar5 = iVar5 + 1;
      lVar4 = lVar4 + 8;
    } while (iVar5 < iVar6);
  }
  return 0;
}



/* address=008f4fd0
   symbol=CPlayer::resetStatPoints */

/* WARNING: Removing unreachable block (ram,0x008f528e) */
/* WARNING: Removing unreachable block (ram,0x008f522d) */
/* WARNING: Removing unreachable block (ram,0x008f5264) */
/* WARNING: Removing unreachable block (ram,0x008f5272) */
/* WARNING: Removing unreachable block (ram,0x008f5280) */
/* CPlayer::resetStatPoints() */

void __thiscall CPlayer::resetStatPoints(CPlayer *this)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  long local_78 [2];
  long local_68 [2];
  long local_58 [2];
  long local_48 [2];
  long local_38 [3];
  allocator local_1d;
  allocator local_1c;
  allocator local_1b;
  allocator local_1a;
  allocator local_19;

  *(undefined4 *)(this + 0x45c) = 0;
  *(undefined4 *)(this + 0x460) = 0;
                    /* try { // try from 008f5001 to 008f5005 has its CatchHandler @ 008f5262 */
  std::wstring::wstring((wstring_conflict *)local_38,L"STRENGTH",&local_19);
                    /* try { // try from 008f5015 to 008f5019 has its CatchHandler @ 008f5254 */
  uVar3 = CDataGroup::GetDataValue(*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_38,10);
  *(undefined4 *)(this + 0x42c) = uVar3;
  if ((allocator *)(local_38[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_38[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_38[0] + -0x18));
    }
  }
                    /* try { // try from 008f5049 to 008f504d has its CatchHandler @ 008f5242 */
  std::wstring::wstring((wstring_conflict *)local_48,L"DEXTERITY",&local_1a);
                    /* try { // try from 008f505d to 008f5061 has its CatchHandler @ 008f523c */
  uVar3 = CDataGroup::GetDataValue(*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_48,10);
  *(undefined4 *)(this + 0x428) = uVar3;
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
                    /* try { // try from 008f508c to 008f5090 has its CatchHandler @ 008f523a */
  std::wstring::wstring((wstring_conflict *)local_58,L"MAGIC",&local_1b);
                    /* try { // try from 008f50a0 to 008f50a4 has its CatchHandler @ 008f5238 */
  uVar3 = CDataGroup::GetDataValue(*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_58,10);
  *(undefined4 *)(this + 0x434) = uVar3;
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
                    /* try { // try from 008f50cf to 008f50d3 has its CatchHandler @ 008f5228 */
  std::wstring::wstring((wstring_conflict *)local_68,L"DEFENSE",&local_1c);
                    /* try { // try from 008f50e3 to 008f50e7 has its CatchHandler @ 008f5215 */
  uVar3 = CDataGroup::GetDataValue(*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_68,10);
  *(undefined4 *)(this + 0x430) = uVar3;
  if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_68[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
    }
  }
                    /* try { // try from 008f510d to 008f5111 has its CatchHandler @ 008f5252 */
  std::wstring::wstring((wstring_conflict *)local_78,L"ARMOR",&local_1d);
                    /* try { // try from 008f511e to 008f5122 has its CatchHandler @ 008f5244 */
  uVar3 = CDataGroup::GetDataValue(*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_78,0);
  *(undefined4 *)(this + 0x424) = uVar3;
  if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_78[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
    }
  }
  return;
}



/* address=008f52a0
   symbol=CPlayer::getPlayerClassName */

/* WARNING: Removing unreachable block (ram,0x008f5366) */
/* CPlayer::getPlayerClassName() */

void CPlayer::getPlayerClassName(void)

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
                    /* try { // try from 008f52d0 to 008f52d4 has its CatchHandler @ 008f5361 */
    std::wstring::wstring((wstring_conflict *)&local_28,L"NAME",&local_19);
                    /* try { // try from 008f52e4 to 008f52f3 has its CatchHandler @ 008f534e */
    pwVar3 = (wstring_conflict *)
             CDataGroup::GetDataValue
                       (*(CDataGroup **)(in_RSI + 0x1b0),(wstring_conflict *)&local_28,
                        L"NOT SPECIFIED");
    STRINGS::StringUpper((STRINGS *)in_RDI,pwVar3);
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



/* address=008f5380
   symbol=CPlayer::resetSkills */

/* WARNING: Removing unreachable block (ram,0x008f55e4) */
/* WARNING: Removing unreachable block (ram,0x008f563e) */
/* WARNING: Removing unreachable block (ram,0x008f5649) */
/* WARNING: Removing unreachable block (ram,0x008f5657) */
/* CPlayer::resetSkills() */

void __thiscall CPlayer::resetSkills(CPlayer *this)

{
  int *piVar1;
  int iVar2;
  CDataGroup *this_00;
  int iVar3;
  uint uVar4;
  int iVar5;
  wstring_conflict *pwVar6;
  long lVar7;
  uint uVar8;
  void *local_98;
  undefined8 local_90;
  undefined8 local_88;
  long local_78 [2];
  long local_68 [2];
  long local_58 [2];
  long local_48;
  allocator local_3b;
  allocator local_3a;
  allocator local_39 [9];

  if (*(CSkillManager **)(this + 0x1c8) != (CSkillManager *)0x0) {
    iVar3 = CSkillManager::getSkillPoints(*(CSkillManager **)(this + 0x1c8));
    CSkillManager::stopAllSkills(*(CSkillManager **)(this + 0x1c8),true,false,true);
    CSkillManager::resetSkillLevels(*(CSkillManager **)(this + 0x1c8));
    local_98 = (void *)0x0;
    local_90 = 0;
    local_88 = 0;
                    /* try { // try from 008f53fa to 008f53fe has its CatchHandler @ 008f5603 */
    std::wstring::wstring((wstring_conflict *)&local_48,L"SKILL",local_39);
                    /* try { // try from 008f540e to 008f5412 has its CatchHandler @ 008f5631 */
    uVar4 = CDataGroup::GetDataGroupsMatchingName
                      (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)&local_48,
                       (vector *)&local_98);
    if ((allocator *)(local_48 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_48 + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_48 + -0x18));
      }
    }
    if (uVar4 != 0) {
      lVar7 = 0;
      uVar8 = 0;
      do {
        this_00 = *(CDataGroup **)((long)local_98 + lVar7);
                    /* try { // try from 008f5458 to 008f545c has its CatchHandler @ 008f55fe */
        std::wstring::wstring((wstring_conflict *)local_68,L"NAME",&local_3a);
                    /* try { // try from 008f546a to 008f547b has its CatchHandler @ 008f55ef */
        pwVar6 = (wstring_conflict *)
                 CDataGroup::GetDataValue(this_00,(wstring_conflict *)local_68,L"");
        STRINGS::StringUpper((STRINGS *)local_58,pwVar6);
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
                    /* try { // try from 008f549d to 008f54a1 has its CatchHandler @ 008f55df */
        std::wstring::wstring((wstring_conflict *)local_78,L"LEVEL",&local_3b);
                    /* try { // try from 008f54ac to 008f54b0 has its CatchHandler @ 008f55b1 */
        iVar5 = CDataGroup::GetDataValue(this_00,(wstring_conflict *)local_78,0);
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
        iVar3 = iVar3 - iVar5;
                    /* try { // try from 008f54d4 to 008f54d8 has its CatchHandler @ 008f5605 */
        CSkillManager::setSkillLevel(*(wstring_conflict **)(this + 0x1c8),(uint)local_58);
        if ((allocator *)(local_58[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_58[0] + -8);
          iVar5 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar5 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
          }
        }
        uVar8 = uVar8 + 1;
        lVar7 = lVar7 + 8;
      } while (uVar8 < uVar4);
    }
    iVar5 = 0;
    if (-1 < iVar3) {
      iVar5 = iVar3;
    }
    *(int *)(this + 0x460) = *(int *)(this + 0x460) + iVar5;
    if (local_98 != (void *)0x0) {
      operator_delete(local_98);
    }
  }
  return;
}



/* address=008f5670
   symbol=CPlayer::openMapPortal */
/* DECOMPILATION FAILED:
Low-level Error: Overriding symbol with different type size */

/* address=008f5810
   symbol=CPlayer::levelResetting */

/* WARNING: Removing unreachable block (ram,0x008f5b76) */
/* WARNING: Removing unreachable block (ram,0x008f5c3f) */
/* WARNING: Removing unreachable block (ram,0x008f5c2f) */
/* WARNING: Removing unreachable block (ram,0x008f5bad) */
/* WARNING: Removing unreachable block (ram,0x008f5b2b) */
/* CPlayer::levelResetting() */

void __thiscall CPlayer::levelResetting(CPlayer *this)

{
  int *piVar1;
  int iVar2;
  long lVar3;
  ulong uVar4;
  ulong uVar5;
  undefined1 uVar6;
  uint uVar7;
  long local_78 [2];
  long local_68 [2];
  long local_58 [2];
  long local_48 [2];
  long local_38 [3];
  allocator local_1d;
  allocator local_1c;
  allocator local_1b;
  allocator local_1a;
  allocator local_19;

  CCharacter::levelResetting((CCharacter *)this);
  iVar2 = CCharacter::maxHP((CCharacter *)this);
  CCharacter::modifyHP((CCharacter *)this,(float)iVar2);
  iVar2 = CCharacter::maxMana((CCharacter *)this);
  CCharacter::modifyMana((CCharacter *)this,(float)iVar2);
  if (((*(long *)(this + 0x68) != 0) && (*(long *)(*(long *)(this + 0x68) + 0x18) != 0)) &&
     (lVar3 = CResourceManager::getGameUI(), *(int *)(lVar3 + 0x1928) == 1)) {
    lVar3 = 0;
    if (*(long *)(this + 0x68) != 0) {
      lVar3 = *(long *)(*(long *)(this + 0x68) + 0x18);
    }
    CPositionableObject::setPosition((CPositionableObject *)this,(Vector3 *)(lVar3 + 0x140));
    uVar6 = false;
    if (*(long *)(this + 0x68) != 0) {
      uVar6 = (undefined1)*(undefined8 *)(*(long *)(this + 0x68) + 0x18);
    }
    CCharacter::dropToGround((CLevel *)this,DAT_00fa8768,(bool)uVar6);
    lVar3 = 0;
    if (*(long *)(this + 0x68) != 0) {
      lVar3 = *(long *)(*(long *)(this + 0x68) + 0x18);
    }
    CCharacter::setToward((CCharacter *)this,(Vector3 *)(lVar3 + 0x164));
  }
  uVar4 = *(long *)(this + 0x650) - *(long *)(this + 0x648) >> 3;
  if (uVar4 != 0) {
    uVar5 = 0;
    uVar7 = 0;
    do {
      lVar3 = uVar5 * 8;
      uVar7 = uVar7 + 1;
      CCharacter::teleportToMaster((float)uVar4 * DAT_00fce520);
      iVar2 = CCharacter::maxHP(*(CCharacter **)(*(long *)(this + 0x648) + lVar3));
      uVar5 = (ulong)uVar7;
      CCharacter::modifyHP(*(CCharacter **)(*(long *)(this + 0x648) + lVar3),(float)iVar2);
      uVar4 = *(long *)(this + 0x650) - *(long *)(this + 0x648) >> 3;
    } while (uVar5 < uVar4);
  }
  (**(code **)(*(long *)this + 0x348))(this,0);
                    /* try { // try from 008f5930 to 008f5934 has its CatchHandler @ 008f5aea */
  std::string::string((string *)local_38,"IDLE",&local_19);
                    /* try { // try from 008f5954 to 008f5958 has its CatchHandler @ 008f5c1f */
  CGenericModel::playAnimation
            (*(CGenericModel **)(this + 0x200),(string *)local_38,true,DAT_00fa47fc,DAT_00fa8760);
  if ((allocator *)(local_38[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_38[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_38[0] + -0x18));
    }
  }
  (**(code **)(*(long *)this + 0x40))(this,1);
  if (*(long *)(this + 0x1b8) != 0) {
                    /* try { // try from 008f599d to 008f59a1 has its CatchHandler @ 008f5c3a */
    std::wstring::wstring((wstring_conflict *)local_48,L"DAMAGEEFFECTFROZENPLAYER",&local_1a);
                    /* try { // try from 008f59ac to 008f59b0 has its CatchHandler @ 008f5be6 */
    CEffectManager::deleteAffix(*(CEffectManager **)(this + 0x1b8),(wstring_conflict *)local_48);
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
                    /* try { // try from 008f59da to 008f59de has its CatchHandler @ 008f5bb8 */
    std::wstring::wstring((wstring_conflict *)local_58,L"DAMAGEEFFECTONFIRE",&local_1b);
                    /* try { // try from 008f59e9 to 008f59ed has its CatchHandler @ 008f5bab */
    CEffectManager::deleteAffix(*(CEffectManager **)(this + 0x1b8),(wstring_conflict *)local_58);
    if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_58[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
      }
    }
                    /* try { // try from 008f5a12 to 008f5a16 has its CatchHandler @ 008f5b71 */
    std::wstring::wstring((wstring_conflict *)local_68,L"DAMAGEEFFECTELECTRICITY",&local_1c);
                    /* try { // try from 008f5a21 to 008f5a25 has its CatchHandler @ 008f5b61 */
    CEffectManager::deleteAffix(*(CEffectManager **)(this + 0x1b8),(wstring_conflict *)local_68);
    if ((allocator *)(local_68[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_68[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -0x18));
      }
    }
                    /* try { // try from 008f5a45 to 008f5a49 has its CatchHandler @ 008f5b36 */
    std::wstring::wstring((wstring_conflict *)local_78,L"DAMAGEEFFECTPOISONED",&local_1d);
                    /* try { // try from 008f5a54 to 008f5a58 has its CatchHandler @ 008f5b1e */
    CEffectManager::deleteAffix(*(CEffectManager **)(this + 0x1b8),(wstring_conflict *)local_78);
    if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_78[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
      }
    }
    if (*(CEffectManager **)(this + 0x1b8) != (CEffectManager *)0x0) {
      CEffectManager::removeNonSavedEffects(*(CEffectManager **)(this + 0x1b8));
    }
  }
  return;
}



/* address=008f5c50
   symbol=CPlayer::updateDungeonTracking */

/* WARNING: Removing unreachable block (ram,0x008f602f) */
/* WARNING: Removing unreachable block (ram,0x008f6065) */
/* WARNING: Removing unreachable block (ram,0x008f5fe8) */
/* CPlayer::updateDungeonTracking(std::wstring, int) */

void __thiscall CPlayer::updateDungeonTracking(CPlayer *this,wstring_conflict *param_2,int param_3)

{
  int *piVar1;
  undefined4 uVar2;
  wchar_t *__s2;
  size_t __n;
  wchar_t *__s1;
  size_t sVar3;
  int iVar4;
  uint uVar5;
  CDungeonManager *pCVar6;
  long lVar7;
  long *plVar8;
  wstring_conflict *this_00;
  void *pvVar9;
  long *plVar10;
  ulong uVar11;
  uint uVar12;
  undefined4 uVar13;
  uint uVar14;
  long lVar15;
  long local_68 [2];
  long local_58 [2];
  long local_48 [3];

  STRINGS::StringUpper((STRINGS *)local_48,param_2);
                    /* try { // try from 008f5c7d to 008f5c81 has its CatchHandler @ 008f6063 */
  std::wstring::assign(param_2);
  if ((allocator *)(local_48[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_48[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
    }
  }
  std::wstring::wstring((wstring_conflict *)local_58,param_2);
                    /* try { // try from 008f5ca9 to 008f5cb8 has its CatchHandler @ 008f601c */
  pCVar6 = (CDungeonManager *)CDungeonManager::getSingleton();
  lVar7 = CDungeonManager::getDungeonByName(pCVar6,(wstring_conflict *)local_58);
  if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_58[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
    }
  }
  uVar14 = *(uint *)(this + 0xa48);
  if (uVar14 != 0) {
    uVar5 = *(uint *)(this + 0xa4c);
    lVar15 = 0;
    uVar12 = 0;
    __s2 = *(wchar_t **)param_2;
    __n = *(size_t *)(__s2 + -6);
    do {
      if (uVar12 < uVar5) {
        __s1 = (wchar_t *)**(long **)(lVar15 + *(long *)(this + 0xa40));
        sVar3 = *(size_t *)(__s1 + -6);
      }
      else {
        __s1 = *(wchar_t **)**(undefined8 **)(this + 0xa40);
        sVar3 = *(size_t *)(__s1 + -6);
      }
      if ((sVar3 == __n) && (iVar4 = wmemcmp(__s1,__s2,__n), iVar4 == 0)) {
        if (uVar12 < uVar5) {
          lVar15 = *(long *)((ulong)uVar12 * 8 + *(long *)(this + 0xa40));
        }
        else {
          lVar15 = **(long **)(this + 0xa40);
        }
        iVar4 = *(int *)(lVar15 + 8);
        if (*(int *)(lVar15 + 8) <= param_3) {
          iVar4 = param_3;
        }
        *(int *)(lVar15 + 8) = iVar4;
        if (lVar7 == 0) {
          return;
        }
        uVar14 = *(uint *)(this + 0xa4c);
        if (uVar12 < uVar14) {
          plVar8 = *(long **)(this + 0xa40);
          plVar10 = plVar8 + uVar12;
        }
        else {
          plVar8 = *(long **)(this + 0xa40);
          plVar10 = plVar8;
        }
        iVar4 = *(int *)(*plVar10 + 0x10);
        if (iVar4 != *(int *)(lVar7 + 0x58)) {
          if (uVar12 < uVar14) {
            plVar8 = plVar8 + uVar12;
          }
          *(undefined4 *)(*plVar8 + 0xc) = *(undefined4 *)(this + 0x100);
          uVar14 = *(uint *)(this + 0xa4c);
          iVar4 = *(int *)(lVar7 + 0x58);
          plVar8 = *(long **)(this + 0xa40);
        }
        if (uVar12 < uVar14) {
          plVar8 = plVar8 + uVar12;
        }
        *(int *)(*plVar8 + 0x10) = iVar4;
        return;
      }
      uVar12 = uVar12 + 1;
      lVar15 = lVar15 + 8;
    } while (uVar12 < uVar14);
  }
  uVar13 = 0;
  std::wstring::wstring((wstring_conflict *)local_68,param_2);
  uVar2 = *(undefined4 *)(this + 0x100);
  if (lVar7 != 0) {
    uVar13 = *(undefined4 *)(lVar7 + 0x58);
  }
                    /* try { // try from 008f5e2f to 008f5e33 has its CatchHandler @ 008f5f9f */
  this_00 = (wstring_conflict *)Ogre::NedAllocImpl::allocBytes(0x30,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 008f5e3d to 008f5e41 has its CatchHandler @ 008f5fdb */
  std::wstring::wstring(this_00,(wstring_conflict *)local_68);
  *(undefined4 *)(this_00 + 0xc) = uVar2;
  *(undefined4 *)(this_00 + 0x10) = uVar13;
  *(undefined8 *)(this_00 + 0x18) = 0;
  *(undefined8 *)(this_00 + 0x20) = 0;
  *(undefined8 *)(this_00 + 0x28) = 0;
  *(int *)(this_00 + 8) = param_3;
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
  uVar14 = *(uint *)(this + 0xa48);
  if (uVar14 < *(uint *)(this + 0xa4c)) {
    pvVar9 = *(void **)(this + 0xa40);
  }
  else if (*(long *)(this + 0xa40) == 0) {
    *(uint *)(this + 0xa4c) = *(uint *)(this + 0xa50);
    pvVar9 = operator_new__((ulong)*(uint *)(this + 0xa50) << 3);
    *(void **)(this + 0xa40) = pvVar9;
    uVar14 = *(uint *)(this + 0xa48);
  }
  else {
    uVar14 = *(uint *)(this + 0xa4c) + *(int *)(this + 0xa50);
    pvVar9 = operator_new__((ulong)uVar14 << 3);
    if (*(int *)(this + 0xa4c) != 0) {
      uVar5 = 0;
      do {
        uVar11 = (ulong)uVar5;
        uVar5 = uVar5 + 1;
        *(undefined8 *)((long)pvVar9 + uVar11 * 8) =
             *(undefined8 *)(*(long *)(this + 0xa40) + uVar11 * 8);
      } while (uVar5 < *(uint *)(this + 0xa4c));
    }
    if (*(void **)(this + 0xa40) != (void *)0x0) {
      operator_delete__(*(void **)(this + 0xa40));
    }
    *(void **)(this + 0xa40) = pvVar9;
    *(uint *)(this + 0xa4c) = uVar14;
    uVar14 = *(uint *)(this + 0xa48);
  }
  *(wstring_conflict **)((long)pvVar9 + (ulong)uVar14 * 8) = this_00;
  *(int *)(this + 0xa48) = *(int *)(this + 0xa48) + 1;
  return;
}



/* address=008f6080
   symbol=CPlayer::storeLevelSavedState */

/* WARNING: Removing unreachable block (ram,0x008f7fef) */
/* WARNING: Removing unreachable block (ram,0x008f7f1c) */
/* WARNING: Removing unreachable block (ram,0x008f8039) */
/* WARNING: Removing unreachable block (ram,0x008f80c9) */
/* WARNING: Removing unreachable block (ram,0x008f8159) */
/* WARNING: Removing unreachable block (ram,0x008f8215) */
/* WARNING: Removing unreachable block (ram,0x008f7dc4) */
/* WARNING: Removing unreachable block (ram,0x008f7dcf) */
/* WARNING: Removing unreachable block (ram,0x008f81be) */
/* WARNING: Removing unreachable block (ram,0x008f810f) */
/* WARNING: Removing unreachable block (ram,0x008f807f) */
/* WARNING: Removing unreachable block (ram,0x008f7fa9) */
/* WARNING: Removing unreachable block (ram,0x008f7e88) */
/* WARNING: Removing unreachable block (ram,0x008f7e44) */
/* WARNING: Removing unreachable block (ram,0x008f7f62) */
/* WARNING: Removing unreachable block (ram,0x008f7ece) */
/* CPlayer::storeLevelSavedState(CLevel&) */

void CPlayer::storeLevelSavedState(CLevel *param_1)

{
  wchar_t *pwVar1;
  int *piVar2;
  wchar_t wVar3;
  CEditorBaseObject CVar4;
  size_t __n;
  CCharacter *pCVar5;
  CLevel *pCVar6;
  wstring_conflict *this;
  CEditorScene *this_00;
  char cVar7;
  CRunicCore CVar8;
  int iVar9;
  int iVar10;
  undefined4 uVar11;
  CLevelState *pCVar12;
  CPositionableObject *pCVar13;
  CRunicCore *pCVar14;
  undefined8 uVar15;
  CEditorBaseObject *pCVar16;
  long *plVar17;
  undefined8 *puVar18;
  long lVar19;
  uint uVar20;
  CLevel *in_RSI;
  CBaseUnit *this_01;
  CRunicCore *pCVar21;
  uint uVar22;
  ulong uVar23;
  ulong uVar24;
  long lVar25;
  byte bVar26;
  float fVar27;
  float in_XMM1_Da;
  float local_1f4;
  long local_1e0;
  void *local_1d8;
  long *local_1b8;
  int local_1b0;
  uint local_1ac;
  undefined4 local_1a8;
  undefined8 local_198;
  float local_190;
  undefined8 local_188;
  float local_180;
  undefined8 local_178;
  float local_170;
  undefined8 local_168;
  float local_160;
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
  long local_98;
  CLevelState *local_90;
  long local_88 [2];
  long local_78 [2];
  wchar_t *local_68 [4];
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

  bVar26 = 0;
  uVar11 = *(undefined4 *)(in_RSI + 0x1a4);
  std::wstring::wstring((wstring_conflict *)local_68,(wstring_conflict *)(in_RSI + 0x280));
                    /* try { // try from 008f60ce to 008f60d2 has its CatchHandler @ 008f7d5a */
  std::wstring::wstring((wstring_conflict *)local_78,(wstring_conflict *)local_68);
                    /* try { // try from 008f60dd to 008f60e1 has its CatchHandler @ 008f7d5f */
  updateDungeonTracking((CPlayer *)param_1,(wstring_conflict *)local_78,uVar11);
  if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_78[0] + -8);
    iVar9 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar9 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
    }
  }
  iVar9 = *(int *)(param_1 + 0x7d8);
  if (*(int *)(param_1 + 0x7d8) <= *(int *)(in_RSI + 0x1a4)) {
    iVar9 = *(int *)(in_RSI + 0x1a4);
  }
  *(int *)(param_1 + 0x7d8) = iVar9;
  if (iVar9 < *(int *)(param_1 + 0x7e4)) {
    iVar9 = *(int *)(param_1 + 0x7e4);
  }
  *(int *)(param_1 + 0x7e4) = iVar9;
  uVar11 = *(undefined4 *)(in_RSI + 0x1a4);
                    /* try { // try from 008f614b to 008f621e has its CatchHandler @ 008f7d5a */
  std::wstring::wstring((wstring_conflict *)local_88,(wstring_conflict *)local_68);
  cVar7 = hasLevelSavedState((CPlayer *)param_1,(wstring_conflict *)local_88,uVar11);
  if ((allocator *)(local_88[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar2 = (int *)(local_88[0] + -8);
    iVar9 = *piVar2;
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (iVar9 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
    }
  }
  if (cVar7 != '\0') {
    lVar25 = *(long *)(param_1 + 0x798);
    uVar23 = *(long *)(param_1 + 0x7a0) - lVar25 >> 3;
    if (uVar23 != 0) {
      iVar9 = *(int *)(in_RSI + 0x1a4);
      uVar24 = 0;
      uVar20 = 0;
      do {
        lVar19 = *(long *)(lVar25 + uVar24 * 8);
        if (*(int *)(lVar19 + 0x10) == iVar9) {
          __n = *(size_t *)(*(wchar_t **)(lVar19 + 0x18) + -6);
          if ((__n == *(size_t *)(local_68[0] + -6)) &&
             (iVar10 = wmemcmp(*(wchar_t **)(lVar19 + 0x18),local_68[0],__n), iVar10 == 0)) {
            local_1f4 = *(float *)(lVar19 + 0x98);
            removeLevelSavedState((CPlayer *)param_1,uVar20);
            iVar9 = *(int *)(in_RSI + 0x1a4);
            goto LAB_008f620f;
          }
        }
        uVar20 = uVar20 + 1;
        uVar24 = (ulong)uVar20;
      } while (uVar24 < uVar23);
      local_1f4 = DAT_00fa8760;
      goto LAB_008f620f;
    }
  }
  iVar9 = *(int *)(in_RSI + 0x1a4);
  local_1f4 = DAT_00fa8760;
LAB_008f620f:
  pCVar12 = (CLevelState *)Ogre::NedAllocImpl::allocBytes(0xb8,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 008f6227 to 008f622b has its CatchHandler @ 008f7d3a */
  CLevelState::CLevelState(pCVar12,iVar9);
  local_90 = pCVar12;
                    /* try { // try from 008f623d to 008f6359 has its CatchHandler @ 008f7d5a */
  std::wstring::assign((wstring_conflict *)(pCVar12 + 0x18));
  local_90[0xb0] = *(CLevelState *)(*(long *)(in_RSI + 0x1d8) + 0x86);
  puVar18 = *(undefined8 **)(param_1 + 0x7a0);
  if (puVar18 == *(undefined8 **)(param_1 + 0x7a8)) {
                    /* try { // try from 008f8249 to 008f824d has its CatchHandler @ 008f7d5a */
    std::vector<CLevelState*,std::allocator<CLevelState*>>::_M_insert_aux
              ((vector<CLevelState*,std::allocator<CLevelState*>> *)(param_1 + 0x798),puVar18,
               &local_90);
  }
  else {
    lVar25 = 0;
    if (puVar18 != (undefined8 *)0x0) {
      *puVar18 = local_90;
      lVar25 = *(long *)(param_1 + 0x7a0);
    }
    *(long *)(param_1 + 0x7a0) = lVar25 + 8;
  }
  if ((*(long *)(in_RSI + 0x1d8) == 0) || (*(char *)(*(long *)(in_RSI + 0x1d8) + 0x5a) == '\0')) {
    if ((local_1f4 != DAT_00fa8760) || (NAN(local_1f4) || NAN(DAT_00fa8760))) {
      *(float *)(local_90 + 0x98) = local_1f4;
    }
    else {
      *(undefined4 *)(local_90 + 0x98) = *(undefined4 *)(param_1 + 0x388);
    }
  }
  else {
    *(undefined4 *)(local_90 + 0x98) = 0xbf800000;
  }
  lVar25 = 0;
  if (*(long *)(param_1 + 0x68) != 0) {
    lVar25 = *(long *)(*(long *)(param_1 + 0x68) + 0x18);
  }
  CLevelState::addFormations((TArrayList *)local_90,(CLevel *)(lVar25 + 0x200));
  plVar17 = (long *)**(undefined8 **)(in_RSI + 0xa0);
  do {
    while( true ) {
      if (plVar17 == (long *)0x0) {
        puVar18 = (undefined8 *)**(long **)(in_RSI + 0x98);
        if (puVar18 != (undefined8 *)0x0) {
          do {
            pCVar5 = (CCharacter *)*puVar18;
                    /* try { // try from 008f63a8 to 008f6436 has its CatchHandler @ 008f822a */
            if ((((param_1 != (CLevel *)pCVar5) && (param_1 != *(CLevel **)(pCVar5 + 0x640))) &&
                (cVar7 = CCharacter::alive(pCVar5), cVar7 != '\0')) &&
               ((pCVar6 = (CLevel *)*puVar18, pCVar6[400] == (CLevel)0x0 &&
                (*(long *)(pCVar6 + 0x640) == 0)))) {
                    /* try { // try from 008f7cb9 to 008f7cbd has its CatchHandler @ 008f822a */
              CLevelState::addCharacter((CCharacter *)local_90,pCVar6);
            }
            puVar18 = (undefined8 *)puVar18[1];
          } while (puVar18 != (undefined8 *)0x0);
          for (puVar18 = (undefined8 *)**(undefined8 **)(in_RSI + 0x98);
              puVar18 != (undefined8 *)0x0; puVar18 = (undefined8 *)puVar18[1]) {
            pCVar5 = (CCharacter *)*puVar18;
            if (((param_1 != (CLevel *)pCVar5) && (param_1 != *(CLevel **)(pCVar5 + 0x640))) &&
               ((cVar7 = CCharacter::alive(pCVar5), cVar7 != '\0' &&
                ((pCVar6 = (CLevel *)*puVar18, pCVar6[400] == (CLevel)0x0 &&
                 (*(long *)(pCVar6 + 0x640) != 0)))))) {
              CLevelState::addCharacter((CCharacter *)local_90,pCVar6);
            }
          }
        }
        uVar23 = *(long *)(in_RSI + 0x1f0) - *(long *)(in_RSI + 0x1e8) >> 3;
        if (uVar23 == 0) {
          local_1d8 = (void *)0x0;
        }
        else {
          if (0x1fffffffffffffff < uVar23) {
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 008f8225 to 008f8229 has its CatchHandler @ 008f8220 */
            std::__throw_bad_alloc();
          }
                    /* try { // try from 008f647f to 008f6483 has its CatchHandler @ 008f8220 */
          local_1d8 = operator_new(uVar23 * 8);
          uVar23 = *(long *)(in_RSI + 0x1f0) - (long)*(void **)(in_RSI + 0x1e8);
          uVar24 = (long)uVar23 >> 3;
          memmove(local_1d8,*(void **)(in_RSI + 0x1e8),uVar23 & 0xfffffffffffffff8);
          if (uVar24 != 0) {
            uVar23 = 0;
            uVar20 = 0;
            do {
                    /* try { // try from 008f6518 to 008f651c has its CatchHandler @ 008f8207 */
              std::wstring::wstring
                        ((wstring_conflict *)&local_98,
                         (wstring_conflict *)(*(long *)((long)local_1d8 + uVar23 * 8) + 0x20));
              pCVar12 = local_90;
              this = *(wstring_conflict **)(local_90 + 0x70);
              if (this == *(wstring_conflict **)(local_90 + 0x78)) {
                    /* try { // try from 008f6545 to 008f6549 has its CatchHandler @ 008f81c9 */
                std::vector<std::wstring,std::allocator<std::wstring>>::_M_insert_aux
                          ((vector<std::wstring,std::allocator<std::wstring>> *)(local_90 + 0x68),
                           this,(wstring_conflict *)&local_98);
              }
              else {
                if (this == (wstring_conflict *)0x0) {
                  lVar25 = 0;
                }
                else {
                    /* try { // try from 008f64d3 to 008f64d7 has its CatchHandler @ 008f8205 */
                  std::wstring::wstring(this,(wstring_conflict *)&local_98);
                  lVar25 = *(long *)(pCVar12 + 0x70);
                }
                *(long *)(pCVar12 + 0x70) = lVar25 + 8;
              }
              if ((allocator *)(local_98 + -0x18) !=
                  (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar2 = (int *)(local_98 + -8);
                iVar9 = *piVar2;
                *piVar2 = *piVar2 + -1;
                UNLOCK();
                if (iVar9 < 1) {
                  std::wstring::_Rep::_M_destroy((allocator *)(local_98 + -0x18));
                }
              }
              uVar20 = uVar20 + 1;
              uVar23 = (ulong)uVar20;
            } while (uVar23 < uVar24);
          }
        }
        if (*(CAutomap **)(in_RSI + 0x1e0) != (CAutomap *)0x0) {
                    /* try { // try from 008f6569 to 008f656d has its CatchHandler @ 008f8207 */
          CLevelState::addAutomap(local_90,*(CAutomap **)(in_RSI + 0x1e0));
        }
        iVar9 = *(int *)(in_RSI + 0x18);
        if (0 < iVar9) {
          local_1e0 = 0;
          uVar20 = 0;
          do {
            if (uVar20 < *(uint *)(in_RSI + 0x1c)) {
              puVar18 = (undefined8 *)(local_1e0 + *(long *)(in_RSI + 0x10));
            }
            else {
              puVar18 = *(undefined8 **)(in_RSI + 0x10);
            }
            this_00 = (CEditorScene *)*puVar18;
            local_1b8 = (long *)0x0;
            local_1b0 = 0;
            local_1ac = 0;
            local_1a8 = 10;
                    /* try { // try from 008f65dc to 008f65e0 has its CatchHandler @ 008f81b9 */
            std::wstring::wstring((wstring_conflict *)local_a8,L"Player Sphere Trigger",local_39);
                    /* try { // try from 008f65f3 to 008f65f7 has its CatchHandler @ 008f81a4 */
            CEditorScene::GetObjectsCreatedByADescriptor
                      (this_00,(wstring_conflict *)local_a8,(TArrayList *)&local_1b8);
            if ((allocator *)(local_a8[0] + -0x18) !=
                (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar2 = (int *)(local_a8[0] + -8);
              iVar10 = *piVar2;
              *piVar2 = *piVar2 + -1;
              UNLOCK();
              if (iVar10 < 1) {
                std::wstring::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
              }
            }
            iVar10 = local_1b0;
            if ((local_1b0 != 0) && (0 < local_1b0)) {
              lVar25 = 0;
              uVar22 = 0;
              do {
                plVar17 = local_1b8;
                if (uVar22 < local_1ac) {
                  plVar17 = (long *)(lVar25 + (long)local_1b8);
                }
                if ((*plVar17 != 0) &&
                   (pCVar13 = (CPositionableObject *)
                              __dynamic_cast(*plVar17,&CEditorBaseObject::typeinfo,
                                             &CTriggerSphere::typeinfo),
                   pCVar13 != (CPositionableObject *)0x0)) {
                    /* try { // try from 008f6671 to 008f6675 has its CatchHandler @ 008f816e */
                  pCVar14 = (CRunicCore *)
                            Ogre::NedAllocImpl::allocBytes(0x60,(char *)0x0,0,(char *)0x0);
                  pCVar21 = pCVar14;
                  for (lVar19 = 0xb; lVar19 != 0; lVar19 = lVar19 + -1) {
                    *(undefined8 *)pCVar21 = 0;
                    pCVar21 = pCVar21 + (ulong)bVar26 * -0x10 + 8;
                  }
                  *(undefined4 *)pCVar21 = 0;
                    /* try { // try from 008f668f to 008f6693 has its CatchHandler @ 008f8169 */
                  CRunicCore::CRunicCore(pCVar14);
                  *(undefined ***)pCVar14 = &PTR__CLogicNodeState_00fd3a10;
                  *(undefined4 **)(pCVar14 + 0x28) = &DAT_01424558;
                    /* try { // try from 008f66aa to 008f67b7 has its CatchHandler @ 008f816e */
                  CVar8 = (CRunicCore)(**(code **)(*(long *)pCVar13 + 0x48))(pCVar13);
                  pCVar14[0x10] = CVar8;
                  *(CPositionableObject *)(pCVar14 + 0x11) = pCVar13[0x100];
                  *(CPositionableObject *)(pCVar14 + 0x12) = pCVar13[0x101];
                  *(CPositionableObject *)(pCVar14 + 0x13) = pCVar13[0x102];
                  lVar19 = *(long *)(pCVar13 + 0x28);
                  if (lVar19 == 0) {
                    CEditorBaseObject::calculateParentHierarchyHashCode
                              ((CEditorBaseObject *)pCVar13);
                    lVar19 = *(long *)(pCVar13 + 0x28);
                  }
                  *(long *)(pCVar14 + 0x40) = lVar19;
                  wcslen(L"Player Sphere Trigger");
                  std::wstring::assign((wchar_t *)(pCVar14 + 0x28),0xfa7558);
                  local_168 = CPositionableObject::getPosition(pCVar13,false);
                  *(undefined8 *)(pCVar14 + 0x50) = local_168;
                  *(uint *)(pCVar14 + 0x30) = uVar20;
                  *(float *)(pCVar14 + 0x58) = in_XMM1_Da;
                  *(undefined8 *)(pCVar14 + 0x48) = *(undefined8 *)(pCVar13 + 0x20);
                  uVar15 = 0xffffffffffffffff;
                  if (*(long *)(pCVar13 + 0x50) != 0) {
                    uVar15 = *(undefined8 *)(*(long *)(pCVar13 + 0x50) + 0x20);
                  }
                  *(undefined8 *)(pCVar14 + 0x38) = uVar15;
                  local_160 = in_XMM1_Da;
                  CLevelState::addLogicState((CLogicNodeState *)local_90,(CLevel *)pCVar14);
                }
                uVar22 = uVar22 + 1;
                lVar25 = lVar25 + 8;
              } while ((int)uVar22 < iVar10);
            }
            local_1b0 = 0;
            local_1ac = 0;
            if (local_1b8 != (long *)0x0) {
              operator_delete__(local_1b8);
            }
            local_1b8 = (long *)0x0;
                    /* try { // try from 008f6808 to 008f680c has its CatchHandler @ 008f8164 */
            std::wstring::wstring((wstring_conflict *)local_b8,L"Player Box Trigger",&local_3a);
                    /* try { // try from 008f681a to 008f681e has its CatchHandler @ 008f8154 */
            CEditorScene::GetObjectsCreatedByADescriptor
                      (this_00,(wstring_conflict *)local_b8,(TArrayList *)&local_1b8);
            if ((allocator *)(local_b8[0] + -0x18) !=
                (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar2 = (int *)(local_b8[0] + -8);
              iVar10 = *piVar2;
              *piVar2 = *piVar2 + -1;
              UNLOCK();
              if (iVar10 < 1) {
                std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
              }
            }
            iVar10 = local_1b0;
            if ((local_1b0 != 0) && (0 < local_1b0)) {
              lVar25 = 0;
              uVar22 = 0;
              do {
                plVar17 = local_1b8;
                if (uVar22 < local_1ac) {
                  plVar17 = (long *)(lVar25 + (long)local_1b8);
                }
                if ((*plVar17 != 0) &&
                   (pCVar13 = (CPositionableObject *)
                              __dynamic_cast(*plVar17,&CEditorBaseObject::typeinfo,
                                             &CTriggerBox::typeinfo),
                   pCVar13 != (CPositionableObject *)0x0)) {
                    /* try { // try from 008f6899 to 008f689d has its CatchHandler @ 008f816e */
                  pCVar14 = (CRunicCore *)
                            Ogre::NedAllocImpl::allocBytes(0x60,(char *)0x0,0,(char *)0x0);
                  pCVar21 = pCVar14;
                  for (lVar19 = 0xb; lVar19 != 0; lVar19 = lVar19 + -1) {
                    *(undefined8 *)pCVar21 = 0;
                    pCVar21 = pCVar21 + (ulong)bVar26 * -0x10 + 8;
                  }
                  *(undefined4 *)pCVar21 = 0;
                    /* try { // try from 008f68b7 to 008f68bb has its CatchHandler @ 008f811f */
                  CRunicCore::CRunicCore(pCVar14);
                  *(undefined ***)pCVar14 = &PTR__CLogicNodeState_00fd3a10;
                  *(undefined4 **)(pCVar14 + 0x28) = &DAT_01424558;
                    /* try { // try from 008f68d2 to 008f69df has its CatchHandler @ 008f816e */
                  CVar8 = (CRunicCore)(**(code **)(*(long *)pCVar13 + 0x48))(pCVar13);
                  pCVar14[0x10] = CVar8;
                  *(CPositionableObject *)(pCVar14 + 0x11) = pCVar13[0x100];
                  *(CPositionableObject *)(pCVar14 + 0x12) = pCVar13[0x101];
                  *(CPositionableObject *)(pCVar14 + 0x13) = pCVar13[0x102];
                  lVar19 = *(long *)(pCVar13 + 0x28);
                  if (lVar19 == 0) {
                    CEditorBaseObject::calculateParentHierarchyHashCode
                              ((CEditorBaseObject *)pCVar13);
                    lVar19 = *(long *)(pCVar13 + 0x28);
                  }
                  *(long *)(pCVar14 + 0x40) = lVar19;
                  wcslen(L"Player Box Trigger");
                  std::wstring::assign((wchar_t *)(pCVar14 + 0x28),0xfa75b0);
                  local_178 = CPositionableObject::getPosition(pCVar13,false);
                  *(undefined8 *)(pCVar14 + 0x50) = local_178;
                  *(uint *)(pCVar14 + 0x30) = uVar20;
                  *(float *)(pCVar14 + 0x58) = in_XMM1_Da;
                  *(undefined8 *)(pCVar14 + 0x48) = *(undefined8 *)(pCVar13 + 0x20);
                  uVar15 = 0xffffffffffffffff;
                  if (*(long *)(pCVar13 + 0x50) != 0) {
                    uVar15 = *(undefined8 *)(*(long *)(pCVar13 + 0x50) + 0x20);
                  }
                  *(undefined8 *)(pCVar14 + 0x38) = uVar15;
                  local_170 = in_XMM1_Da;
                  CLevelState::addLogicState((CLogicNodeState *)local_90,(CLevel *)pCVar14);
                }
                uVar22 = uVar22 + 1;
                lVar25 = lVar25 + 8;
              } while ((int)uVar22 < iVar10);
            }
            local_1b0 = 0;
            local_1ac = 0;
            if (local_1b8 != (long *)0x0) {
              operator_delete__(local_1b8);
            }
            local_1b8 = (long *)0x0;
                    /* try { // try from 008f6a30 to 008f6a34 has its CatchHandler @ 008f811a */
            std::wstring::wstring((wstring_conflict *)local_c8,L"Property Node",&local_3b);
                    /* try { // try from 008f6a42 to 008f6a46 has its CatchHandler @ 008f810a */
            CEditorScene::GetObjectsCreatedByADescriptor
                      (this_00,(wstring_conflict *)local_c8,(TArrayList *)&local_1b8);
            if ((allocator *)(local_c8[0] + -0x18) !=
                (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar2 = (int *)(local_c8[0] + -8);
              iVar10 = *piVar2;
              *piVar2 = *piVar2 + -1;
              UNLOCK();
              if (iVar10 < 1) {
                std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
              }
            }
            iVar10 = local_1b0;
            if ((local_1b0 != 0) && (0 < local_1b0)) {
              lVar25 = 0;
              uVar22 = 0;
              do {
                plVar17 = local_1b8;
                if (uVar22 < local_1ac) {
                  plVar17 = (long *)(lVar25 + (long)local_1b8);
                }
                if ((*plVar17 != 0) &&
                   (pCVar13 = (CPositionableObject *)
                              __dynamic_cast(*plVar17,&CEditorBaseObject::typeinfo,
                                             &CPropertyNode::typeinfo),
                   pCVar13 != (CPositionableObject *)0x0)) {
                    /* try { // try from 008f6ac1 to 008f6ac5 has its CatchHandler @ 008f816e */
                  pCVar14 = (CRunicCore *)
                            Ogre::NedAllocImpl::allocBytes(0x60,(char *)0x0,0,(char *)0x0);
                  pCVar21 = pCVar14;
                  for (lVar19 = 0xb; lVar19 != 0; lVar19 = lVar19 + -1) {
                    *(undefined8 *)pCVar21 = 0;
                    pCVar21 = pCVar21 + (ulong)bVar26 * -0x10 + 8;
                  }
                  *(undefined4 *)pCVar21 = 0;
                    /* try { // try from 008f6adf to 008f6ae3 has its CatchHandler @ 008f80d9 */
                  CRunicCore::CRunicCore(pCVar14);
                  *(undefined ***)pCVar14 = &PTR__CLogicNodeState_00fd3a10;
                  *(undefined4 **)(pCVar14 + 0x28) = &DAT_01424558;
                    /* try { // try from 008f6afa to 008f6be7 has its CatchHandler @ 008f816e */
                  CVar8 = (CRunicCore)(**(code **)(*(long *)pCVar13 + 0x48))(pCVar13);
                  pCVar14[0x10] = CVar8;
                  lVar19 = *(long *)(pCVar13 + 0x28);
                  if (lVar19 == 0) {
                    CEditorBaseObject::calculateParentHierarchyHashCode
                              ((CEditorBaseObject *)pCVar13);
                    lVar19 = *(long *)(pCVar13 + 0x28);
                  }
                  *(long *)(pCVar14 + 0x40) = lVar19;
                  wcslen(L"Property Node");
                  std::wstring::assign((wchar_t *)(pCVar14 + 0x28),0xfa7600);
                  local_188 = CPositionableObject::getPosition(pCVar13,false);
                  *(undefined8 *)(pCVar14 + 0x50) = local_188;
                  *(uint *)(pCVar14 + 0x30) = uVar20;
                  *(float *)(pCVar14 + 0x58) = in_XMM1_Da;
                  *(undefined8 *)(pCVar14 + 0x48) = *(undefined8 *)(pCVar13 + 0x20);
                  uVar15 = 0xffffffffffffffff;
                  if (*(long *)(pCVar13 + 0x50) != 0) {
                    uVar15 = *(undefined8 *)(*(long *)(pCVar13 + 0x50) + 0x20);
                  }
                  *(undefined8 *)(pCVar14 + 0x38) = uVar15;
                  local_180 = in_XMM1_Da;
                  CLevelState::addLogicState((CLogicNodeState *)local_90,(CLevel *)pCVar14);
                }
                uVar22 = uVar22 + 1;
                lVar25 = lVar25 + 8;
              } while ((int)uVar22 < iVar10);
            }
            local_1b0 = 0;
            local_1ac = 0;
            if (local_1b8 != (long *)0x0) {
              operator_delete__(local_1b8);
            }
            local_1b8 = (long *)0x0;
                    /* try { // try from 008f6c38 to 008f6c3c has its CatchHandler @ 008f80d4 */
            std::wstring::wstring((wstring_conflict *)local_d8,L"Group",&local_3c);
                    /* try { // try from 008f6c4a to 008f6c4e has its CatchHandler @ 008f80c4 */
            CEditorScene::GetObjectsCreatedByADescriptor
                      (this_00,(wstring_conflict *)local_d8,(TArrayList *)&local_1b8);
            if ((allocator *)(local_d8[0] + -0x18) !=
                (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar2 = (int *)(local_d8[0] + -8);
              iVar10 = *piVar2;
              *piVar2 = *piVar2 + -1;
              UNLOCK();
              if (iVar10 < 1) {
                std::wstring::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
              }
            }
            iVar10 = local_1b0;
            if ((local_1b0 != 0) && (0 < local_1b0)) {
              lVar25 = 0;
              uVar22 = 0;
              do {
                plVar17 = local_1b8;
                if (uVar22 < local_1ac) {
                  plVar17 = (long *)(lVar25 + (long)local_1b8);
                }
                if ((*plVar17 != 0) &&
                   (pCVar13 = (CPositionableObject *)
                              __dynamic_cast(*plVar17,&CEditorBaseObject::typeinfo,
                                             &CRandomGroup::typeinfo),
                   pCVar13 != (CPositionableObject *)0x0)) {
                    /* try { // try from 008f6cc9 to 008f6ccd has its CatchHandler @ 008f816e */
                  pCVar14 = (CRunicCore *)
                            Ogre::NedAllocImpl::allocBytes(0x60,(char *)0x0,0,(char *)0x0);
                  pCVar21 = pCVar14;
                  for (lVar19 = 0xb; lVar19 != 0; lVar19 = lVar19 + -1) {
                    *(undefined8 *)pCVar21 = 0;
                    pCVar21 = pCVar21 + (ulong)bVar26 * -0x10 + 8;
                  }
                  *(undefined4 *)pCVar21 = 0;
                    /* try { // try from 008f6ce7 to 008f6ceb has its CatchHandler @ 008f808f */
                  CRunicCore::CRunicCore(pCVar14);
                  *(undefined ***)pCVar14 = &PTR__CLogicNodeState_00fd3a10;
                  *(undefined4 **)(pCVar14 + 0x28) = &DAT_01424558;
                    /* try { // try from 008f6d02 to 008f6de7 has its CatchHandler @ 008f816e */
                  CVar8 = (CRunicCore)(**(code **)(*(long *)pCVar13 + 0x48))(pCVar13);
                  pCVar14[0x10] = CVar8;
                  *(CPositionableObject *)(pCVar14 + 0x11) = pCVar13[0x81];
                  local_198 = CPositionableObject::getPosition(pCVar13,false);
                  *(undefined8 *)(pCVar14 + 0x50) = local_198;
                  *(float *)(pCVar14 + 0x58) = in_XMM1_Da;
                  lVar19 = *(long *)(pCVar13 + 0x28);
                  local_190 = in_XMM1_Da;
                  if (lVar19 == 0) {
                    CEditorBaseObject::calculateParentHierarchyHashCode
                              ((CEditorBaseObject *)pCVar13);
                    lVar19 = *(long *)(pCVar13 + 0x28);
                  }
                  *(long *)(pCVar14 + 0x40) = lVar19;
                  wcslen(L"Group");
                  std::wstring::assign((wchar_t *)(pCVar14 + 0x28),0xfa8310);
                  *(uint *)(pCVar14 + 0x30) = uVar20;
                  *(undefined8 *)(pCVar14 + 0x48) = *(undefined8 *)(pCVar13 + 0x20);
                  uVar15 = 0xffffffffffffffff;
                  if (*(long *)(pCVar13 + 0x50) != 0) {
                    uVar15 = *(undefined8 *)(*(long *)(pCVar13 + 0x50) + 0x20);
                  }
                  *(undefined8 *)(pCVar14 + 0x38) = uVar15;
                  CLevelState::addLogicState((CLogicNodeState *)local_90,(CLevel *)pCVar14);
                }
                uVar22 = uVar22 + 1;
                lVar25 = lVar25 + 8;
              } while ((int)uVar22 < iVar10);
            }
            local_1b0 = 0;
            local_1ac = 0;
            if (local_1b8 != (long *)0x0) {
              operator_delete__(local_1b8);
            }
            local_1b8 = (long *)0x0;
                    /* try { // try from 008f6e38 to 008f6e3c has its CatchHandler @ 008f808a */
            std::wstring::wstring((wstring_conflict *)local_e8,L"Timeline",&local_3d);
                    /* try { // try from 008f6e4a to 008f6e4e has its CatchHandler @ 008f807a */
            CEditorScene::GetObjectsCreatedByADescriptor
                      (this_00,(wstring_conflict *)local_e8,(TArrayList *)&local_1b8);
            if ((allocator *)(local_e8[0] + -0x18) !=
                (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar2 = (int *)(local_e8[0] + -8);
              iVar10 = *piVar2;
              *piVar2 = *piVar2 + -1;
              UNLOCK();
              if (iVar10 < 1) {
                std::wstring::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
              }
            }
            iVar10 = local_1b0;
            if ((local_1b0 != 0) && (0 < local_1b0)) {
              lVar25 = 0;
              uVar22 = 0;
              do {
                plVar17 = local_1b8;
                if (uVar22 < local_1ac) {
                  plVar17 = (long *)(lVar25 + (long)local_1b8);
                }
                if ((*plVar17 != 0) &&
                   (pCVar16 = (CEditorBaseObject *)
                              __dynamic_cast(*plVar17,&CEditorBaseObject::typeinfo,
                                             &CTimeline::typeinfo),
                   pCVar16 != (CEditorBaseObject *)0x0)) {
                    /* try { // try from 008f6ec9 to 008f6ecd has its CatchHandler @ 008f816e */
                  pCVar14 = (CRunicCore *)
                            Ogre::NedAllocImpl::allocBytes(0x60,(char *)0x0,0,(char *)0x0);
                  pCVar21 = pCVar14;
                  for (lVar19 = 0xb; lVar19 != 0; lVar19 = lVar19 + -1) {
                    *(undefined8 *)pCVar21 = 0;
                    pCVar21 = pCVar21 + (ulong)bVar26 * -0x10 + 8;
                  }
                  *(undefined4 *)pCVar21 = 0;
                    /* try { // try from 008f6ee7 to 008f6eeb has its CatchHandler @ 008f8049 */
                  CRunicCore::CRunicCore(pCVar14);
                  *(undefined ***)pCVar14 = &PTR__CLogicNodeState_00fd3a10;
                  *(undefined4 **)(pCVar14 + 0x28) = &DAT_01424558;
                  in_XMM1_Da = *(float *)(pCVar16 + 0x94);
                  fVar27 = DAT_00fa47fc;
                  if (0.0 < in_XMM1_Da) {
                    fVar27 = *(float *)(pCVar16 + 0x98) / in_XMM1_Da;
                  }
                  *(float *)(pCVar14 + 0x20) = fVar27;
                  wcslen(L"Timeline");
                    /* try { // try from 008f6f3a to 008f6fe7 has its CatchHandler @ 008f816e */
                  std::wstring::assign((wchar_t *)(pCVar14 + 0x28),0xfada70);
                  lVar19 = *(long *)(pCVar16 + 0x28);
                  if (lVar19 == 0) {
                    CEditorBaseObject::calculateParentHierarchyHashCode(pCVar16);
                    lVar19 = *(long *)(pCVar16 + 0x28);
                  }
                  *(long *)(pCVar14 + 0x40) = lVar19;
                  CVar4 = pCVar16[0xa1];
                  *(uint *)(pCVar14 + 0x30) = uVar20;
                  *(CEditorBaseObject *)(pCVar14 + 0x10) = CVar4;
                  uVar11 = 0;
                  if (pCVar16[0xa0] != (CEditorBaseObject)0x0) {
                    uVar11 = 0x3f800000;
                  }
                  *(undefined4 *)(pCVar14 + 0x24) = uVar11;
                  *(undefined8 *)(pCVar14 + 0x48) = *(undefined8 *)(pCVar16 + 0x20);
                  uVar15 = 0xffffffffffffffff;
                  if (*(long *)(pCVar16 + 0x50) != 0) {
                    uVar15 = *(undefined8 *)(*(long *)(pCVar16 + 0x50) + 0x20);
                  }
                  *(undefined8 *)(pCVar14 + 0x38) = uVar15;
                  pCVar14[0x14] = (CRunicCore)((byte)pCVar16[0xa2] ^ 1);
                  CLevelState::addLogicState((CLogicNodeState *)local_90,(CLevel *)pCVar14);
                }
                uVar22 = uVar22 + 1;
                lVar25 = lVar25 + 8;
              } while ((int)uVar22 < iVar10);
            }
            local_1b0 = 0;
            local_1ac = 0;
            if (local_1b8 != (long *)0x0) {
              operator_delete__(local_1b8);
            }
            local_1b8 = (long *)0x0;
                    /* try { // try from 008f7038 to 008f703c has its CatchHandler @ 008f8044 */
            std::wstring::wstring((wstring_conflict *)local_f8,L"Counter",&local_3e);
                    /* try { // try from 008f704a to 008f704e has its CatchHandler @ 008f8034 */
            CEditorScene::GetObjectsCreatedByADescriptor
                      (this_00,(wstring_conflict *)local_f8,(TArrayList *)&local_1b8);
            if ((allocator *)(local_f8[0] + -0x18) !=
                (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar2 = (int *)(local_f8[0] + -8);
              iVar10 = *piVar2;
              *piVar2 = *piVar2 + -1;
              UNLOCK();
              if (iVar10 < 1) {
                std::wstring::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
              }
            }
            iVar10 = local_1b0;
            if ((local_1b0 != 0) && (0 < local_1b0)) {
              lVar25 = 0;
              uVar22 = 0;
              do {
                plVar17 = local_1b8;
                if (uVar22 < local_1ac) {
                  plVar17 = (long *)(lVar25 + (long)local_1b8);
                }
                if ((*plVar17 != 0) &&
                   (pCVar16 = (CEditorBaseObject *)
                              __dynamic_cast(*plVar17,&CEditorBaseObject::typeinfo,
                                             &CCounter::typeinfo),
                   pCVar16 != (CEditorBaseObject *)0x0)) {
                    /* try { // try from 008f70c9 to 008f70cd has its CatchHandler @ 008f816e */
                  pCVar14 = (CRunicCore *)
                            Ogre::NedAllocImpl::allocBytes(0x60,(char *)0x0,0,(char *)0x0);
                  pCVar21 = pCVar14;
                  for (lVar19 = 0xb; lVar19 != 0; lVar19 = lVar19 + -1) {
                    *(undefined8 *)pCVar21 = 0;
                    pCVar21 = pCVar21 + (ulong)bVar26 * -0x10 + 8;
                  }
                  *(undefined4 *)pCVar21 = 0;
                    /* try { // try from 008f70e7 to 008f70eb has its CatchHandler @ 008f7fff */
                  CRunicCore::CRunicCore(pCVar14);
                  *(undefined ***)pCVar14 = &PTR__CLogicNodeState_00fd3a10;
                  *(undefined4 **)(pCVar14 + 0x28) = &DAT_01424558;
                  *(float *)(pCVar14 + 0x20) = (float)*(int *)(pCVar16 + 0x60);
                  *(CEditorBaseObject *)(pCVar14 + 0x10) = pCVar16[0x68];
                  lVar19 = *(long *)(pCVar16 + 0x28);
                  if (lVar19 == 0) {
                    CEditorBaseObject::calculateParentHierarchyHashCode(pCVar16);
                    lVar19 = *(long *)(pCVar16 + 0x28);
                  }
                  *(long *)(pCVar14 + 0x40) = lVar19;
                  wcslen(L"Counter");
                    /* try { // try from 008f7133 to 008f71a7 has its CatchHandler @ 008f816e */
                  std::wstring::assign((wchar_t *)(pCVar14 + 0x28),0xfa7690);
                  *(uint *)(pCVar14 + 0x30) = uVar20;
                  *(undefined8 *)(pCVar14 + 0x48) = *(undefined8 *)(pCVar16 + 0x20);
                  uVar15 = 0xffffffffffffffff;
                  if (*(long *)(pCVar16 + 0x50) != 0) {
                    uVar15 = *(undefined8 *)(*(long *)(pCVar16 + 0x50) + 0x20);
                  }
                  *(undefined8 *)(pCVar14 + 0x38) = uVar15;
                  CLevelState::addLogicState((CLogicNodeState *)local_90,(CLevel *)pCVar14);
                }
                uVar22 = uVar22 + 1;
                lVar25 = lVar25 + 8;
              } while ((int)uVar22 < iVar10);
            }
            local_1b0 = 0;
            local_1ac = 0;
            if (local_1b8 != (long *)0x0) {
              operator_delete__(local_1b8);
            }
            local_1b8 = (long *)0x0;
                    /* try { // try from 008f71f8 to 008f71fc has its CatchHandler @ 008f7ffa */
            std::wstring::wstring((wstring_conflict *)local_108,L"Timer",&local_3f);
                    /* try { // try from 008f720a to 008f720e has its CatchHandler @ 008f7fea */
            CEditorScene::GetObjectsCreatedByADescriptor
                      (this_00,(wstring_conflict *)local_108,(TArrayList *)&local_1b8);
            if ((allocator *)(local_108[0] + -0x18) !=
                (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar2 = (int *)(local_108[0] + -8);
              iVar10 = *piVar2;
              *piVar2 = *piVar2 + -1;
              UNLOCK();
              if (iVar10 < 1) {
                std::wstring::_Rep::_M_destroy((allocator *)(local_108[0] + -0x18));
              }
            }
            iVar10 = local_1b0;
            if ((local_1b0 != 0) && (0 < local_1b0)) {
              lVar25 = 0;
              uVar22 = 0;
              do {
                plVar17 = local_1b8;
                if (uVar22 < local_1ac) {
                  plVar17 = (long *)(lVar25 + (long)local_1b8);
                }
                if ((*plVar17 != 0) &&
                   (pCVar16 = (CEditorBaseObject *)
                              __dynamic_cast(*plVar17,&CEditorBaseObject::typeinfo,
                                             &CLogicTimer::typeinfo),
                   pCVar16 != (CEditorBaseObject *)0x0)) {
                    /* try { // try from 008f7289 to 008f728d has its CatchHandler @ 008f816e */
                  pCVar14 = (CRunicCore *)
                            Ogre::NedAllocImpl::allocBytes(0x60,(char *)0x0,0,(char *)0x0);
                  pCVar21 = pCVar14;
                  for (lVar19 = 0xb; lVar19 != 0; lVar19 = lVar19 + -1) {
                    *(undefined8 *)pCVar21 = 0;
                    pCVar21 = pCVar21 + (ulong)bVar26 * -0x10 + 8;
                  }
                  *(undefined4 *)pCVar21 = 0;
                    /* try { // try from 008f72a7 to 008f72ab has its CatchHandler @ 008f7fb9 */
                  CRunicCore::CRunicCore(pCVar14);
                  *(undefined ***)pCVar14 = &PTR__CLogicNodeState_00fd3a10;
                  *(undefined4 **)(pCVar14 + 0x28) = &DAT_01424558;
                  *(undefined4 *)(pCVar14 + 0x1c) = *(undefined4 *)(pCVar16 + 0x68);
                  *(undefined4 *)(pCVar14 + 0x20) = *(undefined4 *)(pCVar16 + 0x58);
                  *(CEditorBaseObject *)(pCVar14 + 0x10) = pCVar16[0x6c];
                  lVar19 = *(long *)(pCVar16 + 0x28);
                  if (lVar19 == 0) {
                    CEditorBaseObject::calculateParentHierarchyHashCode(pCVar16);
                    lVar19 = *(long *)(pCVar16 + 0x28);
                  }
                  *(long *)(pCVar14 + 0x40) = lVar19;
                  wcslen(L"Timer");
                    /* try { // try from 008f72f6 to 008f7367 has its CatchHandler @ 008f816e */
                  std::wstring::assign((wchar_t *)(pCVar14 + 0x28),0xfa8328);
                  *(uint *)(pCVar14 + 0x30) = uVar20;
                  *(undefined8 *)(pCVar14 + 0x48) = *(undefined8 *)(pCVar16 + 0x20);
                  uVar15 = 0xffffffffffffffff;
                  if (*(long *)(pCVar16 + 0x50) != 0) {
                    uVar15 = *(undefined8 *)(*(long *)(pCVar16 + 0x50) + 0x20);
                  }
                  *(undefined8 *)(pCVar14 + 0x38) = uVar15;
                  CLevelState::addLogicState((CLogicNodeState *)local_90,(CLevel *)pCVar14);
                }
                uVar22 = uVar22 + 1;
                lVar25 = lVar25 + 8;
              } while ((int)uVar22 < iVar10);
            }
            local_1b0 = 0;
            local_1ac = 0;
            if (local_1b8 != (long *)0x0) {
              operator_delete__(local_1b8);
            }
            local_1b8 = (long *)0x0;
                    /* try { // try from 008f73b8 to 008f73bc has its CatchHandler @ 008f7fb4 */
            std::wstring::wstring((wstring_conflict *)local_118,L"Output Incrementor",&local_40);
                    /* try { // try from 008f73ca to 008f73ce has its CatchHandler @ 008f7fa4 */
            CEditorScene::GetObjectsCreatedByADescriptor
                      (this_00,(wstring_conflict *)local_118,(TArrayList *)&local_1b8);
            if ((allocator *)(local_118[0] + -0x18) !=
                (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar2 = (int *)(local_118[0] + -8);
              iVar10 = *piVar2;
              *piVar2 = *piVar2 + -1;
              UNLOCK();
              if (iVar10 < 1) {
                std::wstring::_Rep::_M_destroy((allocator *)(local_118[0] + -0x18));
              }
            }
            iVar10 = local_1b0;
            if ((local_1b0 != 0) && (0 < local_1b0)) {
              lVar25 = 0;
              uVar22 = 0;
              do {
                plVar17 = local_1b8;
                if (uVar22 < local_1ac) {
                  plVar17 = (long *)(lVar25 + (long)local_1b8);
                }
                if ((*plVar17 != 0) &&
                   (pCVar16 = (CEditorBaseObject *)
                              __dynamic_cast(*plVar17,&CEditorBaseObject::typeinfo,
                                             &COutputIncrementor::typeinfo),
                   pCVar16 != (CEditorBaseObject *)0x0)) {
                    /* try { // try from 008f7449 to 008f744d has its CatchHandler @ 008f816e */
                  pCVar14 = (CRunicCore *)
                            Ogre::NedAllocImpl::allocBytes(0x60,(char *)0x0,0,(char *)0x0);
                  pCVar21 = pCVar14;
                  for (lVar19 = 0xb; lVar19 != 0; lVar19 = lVar19 + -1) {
                    *(undefined8 *)pCVar21 = 0;
                    pCVar21 = pCVar21 + (ulong)bVar26 * -0x10 + 8;
                  }
                  *(undefined4 *)pCVar21 = 0;
                    /* try { // try from 008f7467 to 008f746b has its CatchHandler @ 008f7f72 */
                  CRunicCore::CRunicCore(pCVar14);
                  *(undefined ***)pCVar14 = &PTR__CLogicNodeState_00fd3a10;
                  *(undefined4 **)(pCVar14 + 0x28) = &DAT_01424558;
                  *(undefined4 *)(pCVar14 + 0x1c) = *(undefined4 *)(pCVar16 + 0x5c);
                  *(float *)(pCVar14 + 0x20) = (float)*(int *)(pCVar16 + 100);
                  *(CEditorBaseObject *)(pCVar14 + 0x10) = pCVar16[0x68];
                  lVar19 = *(long *)(pCVar16 + 0x28);
                  if (lVar19 == 0) {
                    CEditorBaseObject::calculateParentHierarchyHashCode(pCVar16);
                    lVar19 = *(long *)(pCVar16 + 0x28);
                  }
                  *(long *)(pCVar14 + 0x40) = lVar19;
                  wcslen(L"Output Incrementor");
                    /* try { // try from 008f74b9 to 008f7527 has its CatchHandler @ 008f816e */
                  std::wstring::assign((wchar_t *)(pCVar14 + 0x28),0xfa76b0);
                  *(uint *)(pCVar14 + 0x30) = uVar20;
                  *(undefined8 *)(pCVar14 + 0x48) = *(undefined8 *)(pCVar16 + 0x20);
                  uVar15 = 0xffffffffffffffff;
                  if (*(long *)(pCVar16 + 0x50) != 0) {
                    uVar15 = *(undefined8 *)(*(long *)(pCVar16 + 0x50) + 0x20);
                  }
                  *(undefined8 *)(pCVar14 + 0x38) = uVar15;
                  CLevelState::addLogicState((CLogicNodeState *)local_90,(CLevel *)pCVar14);
                }
                uVar22 = uVar22 + 1;
                lVar25 = lVar25 + 8;
              } while ((int)uVar22 < iVar10);
            }
            local_1b0 = 0;
            local_1ac = 0;
            if (local_1b8 != (long *)0x0) {
              operator_delete__(local_1b8);
            }
            local_1b8 = (long *)0x0;
                    /* try { // try from 008f7578 to 008f757c has its CatchHandler @ 008f7f6d */
            std::wstring::wstring((wstring_conflict *)local_128,L"Teleport",&local_41);
                    /* try { // try from 008f758a to 008f758e has its CatchHandler @ 008f7f5d */
            CEditorScene::GetObjectsCreatedByADescriptor
                      (this_00,(wstring_conflict *)local_128,(TArrayList *)&local_1b8);
            if ((allocator *)(local_128[0] + -0x18) !=
                (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar2 = (int *)(local_128[0] + -8);
              iVar10 = *piVar2;
              *piVar2 = *piVar2 + -1;
              UNLOCK();
              if (iVar10 < 1) {
                std::wstring::_Rep::_M_destroy((allocator *)(local_128[0] + -0x18));
              }
            }
            iVar10 = local_1b0;
            if ((local_1b0 != 0) && (0 < local_1b0)) {
              lVar25 = 0;
              uVar22 = 0;
              do {
                plVar17 = local_1b8;
                if (uVar22 < local_1ac) {
                  plVar17 = (long *)(lVar25 + (long)local_1b8);
                }
                if ((*plVar17 != 0) &&
                   (pCVar16 = (CEditorBaseObject *)
                              __dynamic_cast(*plVar17,&CEditorBaseObject::typeinfo,
                                             &CTeleport::typeinfo),
                   pCVar16 != (CEditorBaseObject *)0x0)) {
                    /* try { // try from 008f7609 to 008f760d has its CatchHandler @ 008f816e */
                  pCVar14 = (CRunicCore *)
                            Ogre::NedAllocImpl::allocBytes(0x60,(char *)0x0,0,(char *)0x0);
                  pCVar21 = pCVar14;
                  for (lVar19 = 0xb; lVar19 != 0; lVar19 = lVar19 + -1) {
                    *(undefined8 *)pCVar21 = 0;
                    pCVar21 = pCVar21 + (ulong)bVar26 * -0x10 + 8;
                  }
                  *(undefined4 *)pCVar21 = 0;
                    /* try { // try from 008f7627 to 008f762b has its CatchHandler @ 008f7f2c */
                  CRunicCore::CRunicCore(pCVar14);
                  *(undefined ***)pCVar14 = &PTR__CLogicNodeState_00fd3a10;
                  *(undefined4 **)(pCVar14 + 0x28) = &DAT_01424558;
                    /* try { // try from 008f7642 to 008f76d7 has its CatchHandler @ 008f816e */
                  CVar8 = (CRunicCore)(**(code **)(*(long *)pCVar16 + 0x48))(pCVar16);
                  pCVar14[0x10] = CVar8;
                  lVar19 = *(long *)(pCVar16 + 0x28);
                  if (lVar19 == 0) {
                    CEditorBaseObject::calculateParentHierarchyHashCode(pCVar16);
                    lVar19 = *(long *)(pCVar16 + 0x28);
                  }
                  *(long *)(pCVar14 + 0x40) = lVar19;
                  wcslen(L"Teleport");
                  std::wstring::assign((wchar_t *)(pCVar14 + 0x28),0xfa7700);
                  *(uint *)(pCVar14 + 0x30) = uVar20;
                  *(undefined8 *)(pCVar14 + 0x48) = *(undefined8 *)(pCVar16 + 0x20);
                  uVar15 = 0xffffffffffffffff;
                  if (*(long *)(pCVar16 + 0x50) != 0) {
                    uVar15 = *(undefined8 *)(*(long *)(pCVar16 + 0x50) + 0x20);
                  }
                  *(undefined8 *)(pCVar14 + 0x38) = uVar15;
                  CLevelState::addLogicState((CLogicNodeState *)local_90,(CLevel *)pCVar14);
                }
                uVar22 = uVar22 + 1;
                lVar25 = lVar25 + 8;
              } while ((int)uVar22 < iVar10);
            }
            local_1b0 = 0;
            local_1ac = 0;
            if (local_1b8 != (long *)0x0) {
              operator_delete__(local_1b8);
            }
            local_1b8 = (long *)0x0;
                    /* try { // try from 008f7728 to 008f772c has its CatchHandler @ 008f7f27 */
            std::wstring::wstring((wstring_conflict *)local_138,L"Animation Controller",&local_42);
                    /* try { // try from 008f773a to 008f773e has its CatchHandler @ 008f7f17 */
            CEditorScene::GetObjectsCreatedByADescriptor
                      (this_00,(wstring_conflict *)local_138,(TArrayList *)&local_1b8);
            if ((allocator *)(local_138[0] + -0x18) !=
                (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar2 = (int *)(local_138[0] + -8);
              iVar10 = *piVar2;
              *piVar2 = *piVar2 + -1;
              UNLOCK();
              if (iVar10 < 1) {
                std::wstring::_Rep::_M_destroy((allocator *)(local_138[0] + -0x18));
              }
            }
            iVar10 = local_1b0;
            if ((local_1b0 != 0) && (0 < local_1b0)) {
              lVar25 = 0;
              uVar22 = 0;
              do {
                plVar17 = local_1b8;
                if (uVar22 < local_1ac) {
                  plVar17 = (long *)(lVar25 + (long)local_1b8);
                }
                if ((*plVar17 != 0) &&
                   (pCVar16 = (CEditorBaseObject *)
                              __dynamic_cast(*plVar17,&CEditorBaseObject::typeinfo,
                                             &CAnimationPlayer::typeinfo),
                   pCVar16 != (CEditorBaseObject *)0x0)) {
                    /* try { // try from 008f77b9 to 008f77bd has its CatchHandler @ 008f816e */
                  pCVar14 = (CRunicCore *)
                            Ogre::NedAllocImpl::allocBytes(0x60,(char *)0x0,0,(char *)0x0);
                  pCVar21 = pCVar14;
                  for (lVar19 = 0xb; lVar19 != 0; lVar19 = lVar19 + -1) {
                    *(undefined8 *)pCVar21 = 0;
                    pCVar21 = pCVar21 + (ulong)bVar26 * -0x10 + 8;
                  }
                  *(undefined4 *)pCVar21 = 0;
                    /* try { // try from 008f77d7 to 008f77db has its CatchHandler @ 008f7edb */
                  CRunicCore::CRunicCore(pCVar14);
                  *(undefined ***)pCVar14 = &PTR__CLogicNodeState_00fd3a10;
                  *(undefined4 **)(pCVar14 + 0x28) = &DAT_01424558;
                  *(uint *)(pCVar14 + 0x30) = uVar20;
                  *(CEditorBaseObject *)(pCVar14 + 0x10) = pCVar16[0x91];
                  lVar19 = *(long *)(pCVar16 + 0x28);
                  if (lVar19 == 0) {
                    CEditorBaseObject::calculateParentHierarchyHashCode(pCVar16);
                    lVar19 = *(long *)(pCVar16 + 0x28);
                  }
                  *(long *)(pCVar14 + 0x40) = lVar19;
                  wcslen(L"Animation Controller");
                    /* try { // try from 008f7821 to 008f789f has its CatchHandler @ 008f816e */
                  std::wstring::assign((wchar_t *)(pCVar14 + 0x28),0xfa7638);
                  *(undefined8 *)(pCVar14 + 0x48) = *(undefined8 *)(pCVar16 + 0x20);
                  uVar15 = 0xffffffffffffffff;
                  if (*(long *)(pCVar16 + 0x50) != 0) {
                    uVar15 = *(undefined8 *)(*(long *)(pCVar16 + 0x50) + 0x20);
                  }
                  *(undefined8 *)(pCVar14 + 0x38) = uVar15;
                  *(CEditorBaseObject *)(pCVar14 + 0x14) = pCVar16[0x92];
                  *(undefined4 *)(pCVar14 + 0x18) = *(undefined4 *)(pCVar16 + 0xa4);
                  CLevelState::addLogicState((CLogicNodeState *)local_90,(CLevel *)pCVar14);
                }
                uVar22 = uVar22 + 1;
                lVar25 = lVar25 + 8;
              } while ((int)uVar22 < iVar10);
            }
            local_1b0 = 0;
            local_1ac = 0;
            if (local_1b8 != (long *)0x0) {
              operator_delete__(local_1b8);
            }
            local_1b8 = (long *)0x0;
                    /* try { // try from 008f78f0 to 008f78f4 has its CatchHandler @ 008f7ed9 */
            std::wstring::wstring((wstring_conflict *)local_148,L"Puzzle Input",&local_43);
                    /* try { // try from 008f7902 to 008f7906 has its CatchHandler @ 008f7ecc */
            CEditorScene::GetObjectsCreatedByADescriptor
                      (this_00,(wstring_conflict *)local_148,(TArrayList *)&local_1b8);
            if ((allocator *)(local_148[0] + -0x18) !=
                (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar2 = (int *)(local_148[0] + -8);
              iVar10 = *piVar2;
              *piVar2 = *piVar2 + -1;
              UNLOCK();
              if (iVar10 < 1) {
                std::wstring::_Rep::_M_destroy((allocator *)(local_148[0] + -0x18));
              }
            }
            iVar10 = local_1b0;
            if ((local_1b0 != 0) && (0 < local_1b0)) {
              lVar25 = 0;
              uVar22 = 0;
              do {
                plVar17 = local_1b8;
                if (uVar22 < local_1ac) {
                  plVar17 = (long *)(lVar25 + (long)local_1b8);
                }
                if ((*plVar17 != 0) &&
                   (pCVar16 = (CEditorBaseObject *)
                              __dynamic_cast(*plVar17,&CEditorBaseObject::typeinfo,
                                             &CPuzzleRandomizer::typeinfo),
                   pCVar16 != (CEditorBaseObject *)0x0)) {
                    /* try { // try from 008f7981 to 008f7985 has its CatchHandler @ 008f816e */
                  pCVar14 = (CRunicCore *)
                            Ogre::NedAllocImpl::allocBytes(0x60,(char *)0x0,0,(char *)0x0);
                  pCVar21 = pCVar14;
                  for (lVar19 = 0xb; lVar19 != 0; lVar19 = lVar19 + -1) {
                    *(undefined8 *)pCVar21 = 0;
                    pCVar21 = pCVar21 + (ulong)bVar26 * -0x10 + 8;
                  }
                  *(undefined4 *)pCVar21 = 0;
                    /* try { // try from 008f799f to 008f79a3 has its CatchHandler @ 008f7e9b */
                  CRunicCore::CRunicCore(pCVar14);
                  *(undefined ***)pCVar14 = &PTR__CLogicNodeState_00fd3a10;
                  *(undefined4 **)(pCVar14 + 0x28) = &DAT_01424558;
                  *(CEditorBaseObject *)(pCVar14 + 0x10) = pCVar16[0x68];
                  lVar19 = *(long *)(pCVar16 + 0x28);
                  if (lVar19 == 0) {
                    CEditorBaseObject::calculateParentHierarchyHashCode(pCVar16);
                    lVar19 = *(long *)(pCVar16 + 0x28);
                  }
                  *(long *)(pCVar14 + 0x40) = lVar19;
                  wcslen(L"Puzzle Input");
                    /* try { // try from 008f79dd to 008f7a47 has its CatchHandler @ 008f816e */
                  std::wstring::assign((wchar_t *)(pCVar14 + 0x28),0xfa7728);
                  *(uint *)(pCVar14 + 0x30) = uVar20;
                  *(undefined8 *)(pCVar14 + 0x48) = *(undefined8 *)(pCVar16 + 0x20);
                  uVar15 = 0xffffffffffffffff;
                  if (*(long *)(pCVar16 + 0x50) != 0) {
                    uVar15 = *(undefined8 *)(*(long *)(pCVar16 + 0x50) + 0x20);
                  }
                  *(undefined8 *)(pCVar14 + 0x38) = uVar15;
                  CLevelState::addLogicState((CLogicNodeState *)local_90,(CLevel *)pCVar14);
                }
                uVar22 = uVar22 + 1;
                lVar25 = lVar25 + 8;
              } while ((int)uVar22 < iVar10);
            }
            local_1b0 = 0;
            local_1ac = 0;
            if (local_1b8 != (long *)0x0) {
              operator_delete__(local_1b8);
            }
            local_1b8 = (long *)0x0;
                    /* try { // try from 008f7a98 to 008f7a9c has its CatchHandler @ 008f7e93 */
            std::wstring::wstring((wstring_conflict *)local_158,L"Unit Spawner",&local_44);
                    /* try { // try from 008f7aaa to 008f7aae has its CatchHandler @ 008f7e7b */
            CEditorScene::GetObjectsCreatedByADescriptor
                      (this_00,(wstring_conflict *)local_158,(TArrayList *)&local_1b8);
            if ((allocator *)(local_158[0] + -0x18) !=
                (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar2 = (int *)(local_158[0] + -8);
              iVar10 = *piVar2;
              *piVar2 = *piVar2 + -1;
              UNLOCK();
              if (iVar10 < 1) {
                std::wstring::_Rep::_M_destroy((allocator *)(local_158[0] + -0x18));
              }
            }
            iVar10 = local_1b0;
            if ((local_1b0 != 0) && (0 < local_1b0)) {
              lVar25 = 0;
              uVar22 = 0;
              do {
                plVar17 = local_1b8;
                if (uVar22 < local_1ac) {
                  plVar17 = (long *)(lVar25 + (long)local_1b8);
                }
                if ((*plVar17 != 0) &&
                   (pCVar16 = (CEditorBaseObject *)
                              __dynamic_cast(*plVar17,&CEditorBaseObject::typeinfo,
                                             &CUnitSpawner::typeinfo),
                   pCVar16 != (CEditorBaseObject *)0x0)) {
                    /* try { // try from 008f7b29 to 008f7b2d has its CatchHandler @ 008f816e */
                  pCVar14 = (CRunicCore *)
                            Ogre::NedAllocImpl::allocBytes(0x60,(char *)0x0,0,(char *)0x0);
                  pCVar21 = pCVar14;
                  for (lVar19 = 0xb; lVar19 != 0; lVar19 = lVar19 + -1) {
                    *(undefined8 *)pCVar21 = 0;
                    pCVar21 = pCVar21 + (ulong)bVar26 * -0x10 + 8;
                  }
                  *(undefined4 *)pCVar21 = 0;
                    /* try { // try from 008f7b47 to 008f7b4b has its CatchHandler @ 008f7e06 */
                  CRunicCore::CRunicCore(pCVar14);
                  *(undefined ***)pCVar14 = &PTR__CLogicNodeState_00fd3a10;
                  *(undefined4 **)(pCVar14 + 0x28) = &DAT_01424558;
                  *(CEditorBaseObject *)(pCVar14 + 0x10) = pCVar16[0x1c1];
                  *(float *)(pCVar14 + 0x20) = (float)*(uint *)(pCVar16 + 0x18c);
                  *(undefined4 *)(pCVar14 + 0x24) = *(undefined4 *)(pCVar16 + 0x188);
                  lVar19 = *(long *)(pCVar16 + 0x28);
                  if (lVar19 == 0) {
                    CEditorBaseObject::calculateParentHierarchyHashCode(pCVar16);
                    lVar19 = *(long *)(pCVar16 + 0x28);
                  }
                  *(long *)(pCVar14 + 0x40) = lVar19;
                  wcslen(L"Unit Spawner");
                    /* try { // try from 008f7ba5 to 008f7c17 has its CatchHandler @ 008f816e */
                  std::wstring::assign((wchar_t *)(pCVar14 + 0x28),0xfa7760);
                  *(uint *)(pCVar14 + 0x30) = uVar20;
                  *(undefined8 *)(pCVar14 + 0x48) = *(undefined8 *)(pCVar16 + 0x20);
                  uVar15 = 0xffffffffffffffff;
                  if (*(long *)(pCVar16 + 0x50) != 0) {
                    uVar15 = *(undefined8 *)(*(long *)(pCVar16 + 0x50) + 0x20);
                  }
                  *(undefined8 *)(pCVar14 + 0x38) = uVar15;
                  CLevelState::addLogicState((CLogicNodeState *)local_90,(CLevel *)pCVar14);
                }
                uVar22 = uVar22 + 1;
                lVar25 = lVar25 + 8;
              } while ((int)uVar22 < iVar10);
            }
            if (local_1b8 != (long *)0x0) {
              operator_delete__(local_1b8);
              local_1b8 = (long *)0x0;
            }
            uVar20 = uVar20 + 1;
            local_1e0 = local_1e0 + 8;
          } while ((int)uVar20 < iVar9);
        }
                    /* try { // try from 008f7c5d to 008f7c61 has its CatchHandler @ 008f8207 */
        updateStoredLevels((CPlayer *)param_1,in_RSI);
        if (local_1d8 != (void *)0x0) {
          operator_delete(local_1d8);
        }
        if ((allocator *)(local_68[0] + -6) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          pwVar1 = local_68[0] + -2;
          wVar3 = *pwVar1;
          *pwVar1 = *pwVar1 + L'\xffffffff';
          UNLOCK();
          if (wVar3 < L'\x01') {
            std::wstring::_Rep::_M_destroy((allocator *)(local_68[0] + -6));
          }
        }
        return;
      }
      cVar7 = CBaseUnit::ISA((CBaseUnit *)*plVar17,0x1d);
      if (cVar7 != '\0') break;
      this_01 = (CBaseUnit *)*plVar17;
LAB_008f6313:
      if (this_01[400] == (CBaseUnit)0x0) {
        cVar7 = CBaseUnit::getIsQuestUnit(this_01);
        if (cVar7 != '\0') {
          local_90[0xb1] = (CLevelState)0x1;
        }
        CLevelState::addItem(local_90,(CItem *)*plVar17);
      }
      plVar17 = (long *)plVar17[1];
    }
    this_01 = (CBaseUnit *)*plVar17;
    if (this_01[0x218] == (CBaseUnit)0x0) goto LAB_008f6313;
    plVar17 = (long *)plVar17[1];
  } while( true );
}



/* address=008f8260
   symbol=CPlayer::setQuestManager */

/* WARNING: Removing unreachable block (ram,0x008f8501) */
/* WARNING: Removing unreachable block (ram,0x008f84f1) */
/* CPlayer::setQuestManager(CQuestManager*) */

void __thiscall CPlayer::setQuestManager(CPlayer *this,CQuestManager *param_1)

{
  int *piVar1;
  char cVar2;
  int iVar3;
  long lVar4;
  wstring_conflict *pwVar5;
  CQuest *pCVar6;
  long *plVar7;
  undefined8 *puVar8;
  uint uVar9;
  long local_58 [2];
  long local_48;
  allocator local_39 [9];

  *(CQuestManager **)(this + 0x868) = param_1;
  if ((*(long *)(this + 0x1b0) != 0) && (param_1 != (CQuestManager *)0x0)) {
    CQuestManager::setPlayer(param_1,this);
    CQuestManager::resetQuestManager(*(CQuestManager **)(this + 0x868),true);
                    /* try { // try from 008f82c0 to 008f82c4 has its CatchHandler @ 008f84fc */
    std::wstring::wstring((wstring_conflict *)&local_48,L"QUESTS",local_39);
                    /* try { // try from 008f82d2 to 008f82d6 has its CatchHandler @ 008f84d1 */
    lVar4 = CDataGroup::GetDataGroupByName
                      (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)&local_48,false);
    if ((allocator *)(local_48 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_48 + -8);
      iVar3 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar3 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_48 + -0x18));
      }
    }
    if ((lVar4 != 0) && (*(int *)(lVar4 + 0x28) != 0)) {
      uVar9 = 0;
      do {
        if (uVar9 < *(uint *)(lVar4 + 0x2c)) {
          plVar7 = (long *)((ulong)uVar9 * 8 + *(long *)(lVar4 + 0x20));
        }
        else {
          plVar7 = *(long **)(lVar4 + 0x20);
        }
        if ((*(int *)(*plVar7 + 0x30) == 8) || (*(int *)(*plVar7 + 0x30) == 5)) {
          if (uVar9 < *(uint *)(lVar4 + 0x2c)) {
            puVar8 = (undefined8 *)((ulong)uVar9 * 8 + *(long *)(lVar4 + 0x20));
          }
          else {
            puVar8 = *(undefined8 **)(lVar4 + 0x20);
          }
          pwVar5 = (wstring_conflict *)CDataValue::GetValueString((CDataValue *)*puVar8,true);
          STRINGS::StringUpper((STRINGS *)local_58,pwVar5);
                    /* try { // try from 008f8353 to 008f8357 has its CatchHandler @ 008f84e4 */
          pCVar6 = (CQuest *)
                   CQuestManager::getQuestByName
                             (*(CQuestManager **)(this + 0x868),(wstring_conflict *)local_58);
          if ((allocator *)(local_58[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_58[0] + -8);
            iVar3 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar3 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
            }
          }
          if (pCVar6 != (CQuest *)0x0) {
            CQuestManager::giveQuest
                      (*(CQuestManager **)(this + 0x868),pCVar6,(CBaseUnit *)0x0,false);
            CQuest::setQuestAccepted(pCVar6,true);
          }
        }
        uVar9 = uVar9 + 1;
      } while (uVar9 < *(uint *)(lVar4 + 0x28));
    }
    uVar9 = KSETTINGS_GAME_COMPLETED_ONCE;
    lVar4 = CMasterResourceManager::getSingleton();
    iVar3 = CDynamicPropertyFile::GetInt(*(CDynamicPropertyFile **)(lVar4 + 0x90),uVar9);
    uVar9 = KSETTINGS_RETIREE_QUEST;
    if (iVar3 == 1) {
      lVar4 = CMasterResourceManager::getSingleton();
      pwVar5 = (wstring_conflict *)
               CDynamicPropertyFile::GetString(*(CDynamicPropertyFile **)(lVar4 + 0x90),uVar9);
      pCVar6 = (CQuest *)CQuestManager::getQuestByName(*(CQuestManager **)(this + 0x868),pwVar5);
      uVar9 = KSETTINGS_RETIREE_QUEST;
      if (pCVar6 != (CQuest *)0x0) {
        lVar4 = CMasterResourceManager::getSingleton();
        pwVar5 = (wstring_conflict *)
                 CDynamicPropertyFile::GetString(*(CDynamicPropertyFile **)(lVar4 + 0x90),uVar9);
        cVar2 = CQuestManager::getQuestComplete(*(CQuestManager **)(this + 0x868),pwVar5);
        if (cVar2 == '\0') {
          CQuestManager::giveQuest(*(CQuestManager **)(this + 0x868),pCVar6,(CBaseUnit *)0x0,true);
          CQuestManager::completeQuest(*(CQuestManager **)(this + 0x868),pCVar6);
        }
      }
    }
  }
  return;
}



/* address=008f8510
   symbol=CPlayer::calculateNaturalArmor */

/* WARNING: Removing unreachable block (ram,0x008f8666) */
/* WARNING: Removing unreachable block (ram,0x008f8671) */
/* CPlayer::calculateNaturalArmor() */

void __thiscall CPlayer::calculateNaturalArmor(CPlayer *this)

{
  int *piVar1;
  int iVar2;
  CGraphManager *this_00;
  CGraph *this_01;
  float fVar3;
  long local_38 [2];
  long local_28;
  allocator local_1a;
  allocator local_19 [9];

                    /* try { // try from 008f852b to 008f852f has its CatchHandler @ 008f865f */
  std::wstring::wstring((wstring_conflict *)&local_28,L"ARMOR",local_19);
                    /* try { // try from 008f853c to 008f8540 has its CatchHandler @ 008f864a */
  iVar2 = CDataGroup::GetDataValue(*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)&local_28,0);
  *(int *)(this + 0x424) = iVar2;
  if ((allocator *)(local_28 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_28 + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_28 + -0x18));
    }
    iVar2 = *(int *)(this + 0x424);
  }
  if (iVar2 != 0) {
                    /* try { // try from 008f8582 to 008f8586 has its CatchHandler @ 008f8664 */
    std::wstring::wstring((wstring_conflict *)local_38,L"ARMOR_MONSTER_BYLEVEL",&local_1a);
                    /* try { // try from 008f8587 to 008f8596 has its CatchHandler @ 008f865d */
    this_00 = (CGraphManager *)CGraphManager::getSingleton();
    this_01 = (CGraph *)CGraphManager::getGraph(this_00,(wstring_conflict *)local_38);
    if ((allocator *)(local_38[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_38[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_38[0] + -0x18));
      }
    }
    if (this_01 != (CGraph *)0x0) {
      fVar3 = (float)CGraph::getValue(this_01,(float)*(uint *)(this + 0x100),0);
      fVar3 = ceilf(fVar3 * ((float)*(int *)(this + 0x424) / DAT_00fa483c));
      *(int *)(this + 0x424) = (int)fVar3;
      return;
    }
  }
  return;
}



/* address=008f8680
   symbol=CPlayer::applySaveState */

/* WARNING: Removing unreachable block (ram,0x008f8a17) */
/* WARNING: Removing unreachable block (ram,0x008f8a3e) */
/* WARNING: Removing unreachable block (ram,0x008f89f2) */
/* CPlayer::applySaveState(CCharacterSaveState&) */

void __thiscall CPlayer::applySaveState(CPlayer *this,CCharacterSaveState *param_1)

{
  int *piVar1;
  CPlayer *pCVar2;
  int iVar3;
  undefined4 uVar4;
  char cVar5;
  ulong *puVar6;
  long *plVar7;
  uint uVar8;
  long *plVar9;
  uint uVar10;
  ulong uVar11;
  long lVar12;
  wstring_conflict *pwVar13;
  allocator *paVar14;
  ulong *puVar15;
  uint uVar16;
  long local_48 [3];

  pCVar2 = this + 0xa58;
  CCharacter::applySaveState((CCharacter *)this,param_1);
  plVar9 = *(long **)(this + 0xa58);
  *(CCharacterSaveState *)(this + 0x791) = param_1[0x34];
  *(undefined4 *)(this + 0x7d8) = *(undefined4 *)(param_1 + 0x68);
  uVar4 = *(undefined4 *)(param_1 + 0xf8);
  *(undefined4 *)(this + 0xa60) = 0;
  *(undefined4 *)(this + 0xa64) = 0;
  *(undefined4 *)(this + 0x388) = uVar4;
  if (plVar9 != (long *)0x0) {
    plVar7 = plVar9 + plVar9[-1];
    while (plVar7 != plVar9) {
      plVar7 = plVar7 + -1;
      paVar14 = (allocator *)(*plVar7 + -0x18);
      if (paVar14 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(*plVar7 + -8);
        iVar3 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar3 < 1) {
          std::wstring::_Rep::_M_destroy(paVar14);
          plVar9 = *(long **)pCVar2;
        }
        else {
          plVar9 = *(long **)pCVar2;
        }
      }
    }
    operator_delete__((void *)(*(long *)(this + 0xa58) + -8));
  }
  *(undefined8 *)(this + 0xa58) = 0;
  if (*(int *)(param_1 + 0x218) != 0) {
    uVar16 = 0;
    do {
      if (uVar16 < *(uint *)(param_1 + 0x21c)) {
        pwVar13 = (wstring_conflict *)((ulong)uVar16 * 8 + *(long *)(param_1 + 0x210));
      }
      else {
        pwVar13 = *(wstring_conflict **)(param_1 + 0x210);
      }
      std::wstring::wstring((wstring_conflict *)local_48,pwVar13);
      uVar8 = *(uint *)(this + 0xa60);
      if (uVar8 < *(uint *)(this + 0xa64)) {
        puVar15 = *(ulong **)(this + 0xa58);
      }
      else if (*(long *)(this + 0xa58) == 0) {
        uVar11 = (ulong)*(uint *)(this + 0xa68);
        *(uint *)(this + 0xa64) = *(uint *)(this + 0xa68);
                    /* try { // try from 008f8940 to 008f8944 has its CatchHandler @ 008f89dd */
        puVar6 = operator_new__(uVar11 * 8 + 8);
        *puVar6 = uVar11;
        puVar15 = puVar6 + 1;
        if (uVar11 != 0) {
          lVar12 = uVar11 - 2;
          do {
            lVar12 = lVar12 + -1;
            puVar6[1] = (ulong)&DAT_01424558;
            puVar6 = puVar6 + 1;
          } while (lVar12 != -2);
        }
        *(ulong **)(this + 0xa58) = puVar15;
        uVar8 = *(uint *)(this + 0xa60);
      }
      else {
        uVar8 = *(uint *)(this + 0xa64) + *(int *)(this + 0xa68);
        uVar11 = (ulong)uVar8;
                    /* try { // try from 008f87bb to 008f8892 has its CatchHandler @ 008f89dd */
        puVar6 = operator_new__(uVar11 * 8 + 8);
        *puVar6 = uVar11;
        puVar15 = puVar6 + 1;
        if (uVar11 != 0) {
          lVar12 = uVar11 - 2;
          do {
            lVar12 = lVar12 + -1;
            puVar6[1] = (ulong)&DAT_01424558;
            puVar6 = puVar6 + 1;
          } while (lVar12 != -2);
        }
        if (*(int *)(this + 0xa64) != 0) {
          uVar10 = 0;
          do {
            std::wstring::assign((wstring_conflict *)(puVar15 + uVar10));
            uVar10 = uVar10 + 1;
          } while (uVar10 < *(uint *)(this + 0xa64));
        }
        lVar12 = *(long *)(this + 0xa58);
        if (lVar12 != 0) {
          plVar9 = (long *)(lVar12 + *(long *)(lVar12 + -8) * 8);
          do {
            plVar7 = *(long **)pCVar2;
            while( true ) {
              do {
                if (plVar9 == plVar7) {
                  operator_delete__((void *)(*(long *)(this + 0xa58) + -8));
                  goto LAB_008f8866;
                }
                plVar9 = plVar9 + -1;
                paVar14 = (allocator *)(*plVar9 + -0x18);
              } while (paVar14 == (allocator *)&std::wstring::_Rep::_S_empty_rep_storage);
              LOCK();
              piVar1 = (int *)(*plVar9 + -8);
              iVar3 = *piVar1;
              *piVar1 = *piVar1 + -1;
              UNLOCK();
              if (0 < iVar3) break;
              std::wstring::_Rep::_M_destroy(paVar14);
              plVar7 = *(long **)pCVar2;
            }
          } while( true );
        }
LAB_008f8866:
        *(ulong **)(this + 0xa58) = puVar15;
        *(uint *)(this + 0xa64) = uVar8;
        uVar8 = *(uint *)(this + 0xa60);
      }
      std::wstring::assign((wstring_conflict *)(puVar15 + uVar8));
      *(int *)(this + 0xa60) = *(int *)(this + 0xa60) + 1;
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
      uVar16 = uVar16 + 1;
    } while (uVar16 < *(uint *)(param_1 + 0x218));
  }
  calculateNaturalArmor(this);
  cVar5 = (**(code **)(*(long *)this + 0x48))(this);
  if (cVar5 == '\0') {
    (**(code **)(*(long *)this + 0x40))(this,1);
  }
  return;
}



/* address=008f8a50
   symbol=CPlayer::unitInit */

/* WARNING: Removing unreachable block (ram,0x008f9a2b) */
/* WARNING: Removing unreachable block (ram,0x008f9975) */
/* WARNING: Removing unreachable block (ram,0x008f954a) */
/* WARNING: Removing unreachable block (ram,0x008f95f3) */
/* WARNING: Removing unreachable block (ram,0x008f97be) */
/* WARNING: Removing unreachable block (ram,0x008f96fa) */
/* WARNING: Removing unreachable block (ram,0x008f97b3) */
/* WARNING: Removing unreachable block (ram,0x008f9ab3) */
/* WARNING: Removing unreachable block (ram,0x008f99da) */
/* WARNING: Removing unreachable block (ram,0x008f9812) */
/* WARNING: Removing unreachable block (ram,0x008f9894) */
/* WARNING: Removing unreachable block (ram,0x008f948e) */
/* WARNING: Removing unreachable block (ram,0x008f9924) */
/* WARNING: Removing unreachable block (ram,0x008f9858) */
/* WARNING: Removing unreachable block (ram,0x008f97a5) */
/* WARNING: Removing unreachable block (ram,0x008f99e5) */
/* WARNING: Removing unreachable block (ram,0x008f9abe) */
/* WARNING: Removing unreachable block (ram,0x008f97cc) */
/* WARNING: Removing unreachable block (ram,0x008f969b) */
/* WARNING: Removing unreachable block (ram,0x008f96e5) */
/* WARNING: Removing unreachable block (ram,0x008f95b5) */
/* WARNING: Removing unreachable block (ram,0x008f953f) */
/* WARNING: Removing unreachable block (ram,0x008f992f) */
/* WARNING: Removing unreachable block (ram,0x008f94dc) */
/* CPlayer::unitInit(CDataGroup*, bool) */

void __thiscall CPlayer::unitInit(CPlayer *this,CDataGroup *param_1,bool param_2)

{
  int *piVar1;
  long lVar2;
  CSoundBankDataInformation *this_00;
  undefined4 uVar3;
  int iVar4;
  CSceneNodeObject *this_01;
  long *plVar5;
  CUnitResourceList *pCVar6;
  CDataGroup *pCVar7;
  undefined8 uVar8;
  CQuestManager *pCVar9;
  CSharedStash *this_02;
  CSkillManager *pCVar10;
  uint uVar11;
  long lVar12;
  undefined4 local_1e8;
  undefined4 local_1e4;
  undefined4 local_1e0;
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
  allocator local_39;
  allocator local_38;
  allocator local_37;
  allocator local_36;
  allocator local_35;
  allocator local_34;
  allocator local_33;
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

  CCharacter::unitInit((CCharacter *)this,param_1,param_2);
  CInventory::addSection(*(CInventory **)(this + 0x490),1,0x15);
  CInventory::addSection(*(CInventory **)(this + 0x490),2,0x15);
                    /* try { // try from 008f8aac to 008f8ab0 has its CatchHandler @ 008f9499 */
  std::wstring::wstring((wstring_conflict *)local_68,L"STRENGTH",local_29);
                    /* try { // try from 008f8ac0 to 008f8ac4 has its CatchHandler @ 008f9481 */
  uVar3 = CDataGroup::GetDataValue(*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_68,10);
  *(undefined4 *)(this + 0x42c) = uVar3;
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
                    /* try { // try from 008f8afd to 008f8b01 has its CatchHandler @ 008f9450 */
  std::wstring::wstring((wstring_conflict *)local_78,L"DEXTERITY",&local_2a);
                    /* try { // try from 008f8b11 to 008f8b15 has its CatchHandler @ 008f98d1 */
  uVar3 = CDataGroup::GetDataValue(*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_78,10);
  *(undefined4 *)(this + 0x428) = uVar3;
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
                    /* try { // try from 008f8b49 to 008f8b4d has its CatchHandler @ 008f989f */
  std::wstring::wstring((wstring_conflict *)local_88,L"MAGIC",&local_2b);
                    /* try { // try from 008f8b5d to 008f8b61 has its CatchHandler @ 008f988f */
  uVar3 = CDataGroup::GetDataValue(*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_88,10);
  *(undefined4 *)(this + 0x434) = uVar3;
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
  }
                    /* try { // try from 008f8b95 to 008f8b99 has its CatchHandler @ 008f9853 */
  std::wstring::wstring((wstring_conflict *)local_98,L"DEFENSE",&local_2c);
                    /* try { // try from 008f8ba9 to 008f8bad has its CatchHandler @ 008f984e */
  uVar3 = CDataGroup::GetDataValue(*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_98,10);
  *(undefined4 *)(this + 0x430) = uVar3;
  if ((allocator *)(local_98[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_98[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
    }
  }
                    /* try { // try from 008f8be1 to 008f8be5 has its CatchHandler @ 008f981d */
  std::wstring::wstring((wstring_conflict *)local_a8,L"MANA_GRAPH",&local_2d);
                    /* try { // try from 008f8bf5 to 008f8c08 has its CatchHandler @ 008f980d */
  CDataGroup::GetDataValue
            (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_a8,L"MANA_PLAYER_DESTROYER");
  std::wstring::assign((wstring_conflict *)(this + 0x888));
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
                    /* try { // try from 008f8c36 to 008f8c3a has its CatchHandler @ 008f97dc */
  std::wstring::wstring((wstring_conflict *)local_b8,L"HEALTH_GRAPH",&local_2e);
                    /* try { // try from 008f8c4a to 008f8c5d has its CatchHandler @ 008f97d7 */
  CDataGroup::GetDataValue
            (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_b8,L"HEALTH_PLAYER_DESTROYER")
  ;
  std::wstring::assign((wstring_conflict *)(this + 0x890));
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
                    /* try { // try from 008f8c8b to 008f8c8f has its CatchHandler @ 008f970f */
  std::wstring::wstring((wstring_conflict *)local_c8,L"STAT_POINTS_PER_LEVEL",&local_2f);
                    /* try { // try from 008f8c9f to 008f8cb2 has its CatchHandler @ 008f970a */
  CDataGroup::GetDataValue
            (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_c8,L"STAT_POINTS_PER_LEVEL");
  std::wstring::assign((wstring_conflict *)(this + 0x898));
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
  }
                    /* try { // try from 008f8ce0 to 008f8ce4 has its CatchHandler @ 008f9970 */
  std::wstring::wstring((wstring_conflict *)local_d8,L"SKILL_POINTS_PER_LEVEL",&local_30);
                    /* try { // try from 008f8cf4 to 008f8d07 has its CatchHandler @ 008f996b */
  CDataGroup::GetDataValue
            (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_d8,L"SKILL_POINTS_PER_LEVEL");
  std::wstring::assign((wstring_conflict *)(this + 0x8a0));
  if ((allocator *)(local_d8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_d8[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
    }
  }
                    /* try { // try from 008f8d35 to 008f8d39 has its CatchHandler @ 008f9a36 */
  std::wstring::wstring((wstring_conflict *)local_e8,L"SKILL_POINTS_PER_FAME_LEVEL",&local_31);
                    /* try { // try from 008f8d49 to 008f8d5c has its CatchHandler @ 008f9a26 */
  CDataGroup::GetDataValue
            (*(CDataGroup **)(this + 0x1b0),(wstring_conflict *)local_e8,
             L"SKILL_POINTS_PER_FAME_LEVEL");
  std::wstring::assign((wstring_conflict *)(this + 0x8a8));
  if ((allocator *)(local_e8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_e8[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
    }
  }
  (**(code **)(*(long *)this + 0x418))(this);
  *(float *)(this + 0x414) = (float)*(int *)(this + 0x418);
  (**(code **)(*(long *)this + 0x410))(this);
  *(float *)(this + 0x438) = (float)*(int *)(this + 0x43c);
  calculateNaturalArmor(this);
  this_01 = (CSceneNodeObject *)
            CResourceManager::createParticle(*(CResourceManager **)(this + 0x68),L"PLAYER_LEVELUP");
  *(CSceneNodeObject **)(this + 0x778) = this_01;
  if (this_01 != (CSceneNodeObject *)0x0) {
    CSceneNodeObject::sceneNodeSetParent(this_01,*(SceneNode **)(this + 0x58),false);
    local_1e8 = 0;
    local_1e4 = 0;
    local_1e0 = 0;
    CPositionableObject::setPosition(*(CPositionableObject **)(this + 0x778),(Vector3 *)&local_1e8);
  }
  pCVar10 = *(CSkillManager **)(this + 0x1c8);
  if (pCVar10 == (CSkillManager *)0x0) goto LAB_008f8f30;
  if (*(int *)(pCVar10 + 0x68) < 1) {
    *(undefined8 *)(this + 0x398) = 0;
LAB_008f93eb:
    lVar12 = *(long *)(this + 0x398);
    *(undefined8 *)(this + 0x3b0) = 0xffffffffffffffff;
LAB_008f93fd:
    if (lVar12 != 0) goto LAB_008f8e78;
    *(undefined8 *)(this + 0x8c0) = 0xffffffffffffffff;
  }
  else {
    lVar12 = **(long **)(pCVar10 + 0x60);
    *(long *)(this + 0x398) = lVar12;
    if (lVar12 == 0) goto LAB_008f93eb;
    *(undefined8 *)(this + 0x3b0) = *(undefined8 *)(lVar12 + 0x150);
    if (((*(int *)(lVar12 + 0xdc) == 0) || (*(int *)(lVar12 + 0x60) == 4)) ||
       ((*(byte *)(lVar12 + 0x6d) & (*(byte *)(lVar12 + 0x6b) ^ 1)) == 0)) {
      CCharacter::cycleSkill((CCharacter *)this,1);
      lVar12 = *(long *)(this + 0x398);
      pCVar10 = *(CSkillManager **)(this + 0x1c8);
      goto LAB_008f93fd;
    }
LAB_008f8e78:
    lVar12 = *(long *)(lVar12 + 0x150);
    *(long *)(this + 0x8c0) = lVar12;
    if (lVar12 != -1) {
      *(undefined8 *)(this + 0x910) = 0xffffffffffffffff;
    }
  }
  lVar12 = 0;
  *(undefined8 *)(this + 0x3b8) = *(undefined8 *)(this + 0x3b0);
  for (uVar11 = 0; iVar4 = CSkillManager::knownSkills(pCVar10,0), (int)uVar11 < iVar4;
      uVar11 = uVar11 + 1) {
    pCVar10 = *(CSkillManager **)(this + 0x1c8);
    if ((int)uVar11 < *(int *)(pCVar10 + 0x68)) {
      if (uVar11 < *(uint *)(pCVar10 + 0x6c)) {
        plVar5 = (long *)(*(long *)(pCVar10 + 0x60) + lVar12);
      }
      else {
        plVar5 = *(long **)(pCVar10 + 0x60);
      }
      lVar2 = *plVar5;
      if (((lVar2 != 0) && (*(long *)(this + 0x398) != lVar2)) &&
         ((*(int *)(lVar2 + 0x60) != 4 &&
          (((*(byte *)(lVar2 + 0x6d) & (*(byte *)(lVar2 + 0x6b) ^ 1)) != 0 &&
           (*(int *)(lVar2 + 0xdc) != 0)))))) {
        *(undefined8 *)(this + 0x3b8) = *(undefined8 *)(lVar2 + 0x150);
      }
    }
    lVar12 = lVar12 + 8;
  }
LAB_008f8f30:
  if (*(long *)(this + 0x298) != 0) {
    lVar12 = CMasterResourceManager::getSingleton();
    this_00 = *(CSoundBankDataInformation **)(lVar12 + 0x100);
                    /* try { // try from 008f8f62 to 008f8f66 has its CatchHandler @ 008f9a67 */
    std::wstring::wstring((wstring_conflict *)local_f8,L"LEVELUP",&local_32);
                    /* try { // try from 008f8f6d to 008f8f71 has its CatchHandler @ 008f943d */
    lVar12 = CSoundBankDataInformation::getSoundDataObject(this_00,(wstring_conflict *)local_f8);
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
    if (lVar12 != 0) {
      CSoundBank::addSample(*(CSoundBank **)(this + 0x298),0x19,*(longlong *)(lVar12 + 0x20));
    }
                    /* try { // try from 008f8fb9 to 008f8fbd has its CatchHandler @ 008f9a6c */
    std::wstring::wstring((wstring_conflict *)local_118,L"Health Potion",&local_34);
                    /* try { // try from 008f8fd6 to 008f8fda has its CatchHandler @ 008f9aae */
    std::wstring::wstring((wstring_conflict *)local_108,L"ITEMS",&local_33);
                    /* try { // try from 008f8fdf to 008f8ff1 has its CatchHandler @ 008f9705 */
    pCVar6 = (CUnitResourceList *)CResourceManager::getMasterResourceList();
    pCVar7 = (CDataGroup *)
             CUnitResourceList::getDataGroupByObjectName
                       (pCVar6,(wstring_conflict *)local_108,(wstring_conflict *)local_118);
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
    if (pCVar7 != (CDataGroup *)0x0) {
                    /* try { // try from 008f9040 to 008f9044 has its CatchHandler @ 008f9774 */
      std::wstring::wstring((wstring_conflict *)local_128,L"UNIT_GUID",&local_35);
                    /* try { // try from 008f904f to 008f9053 has its CatchHandler @ 008f9665 */
      uVar8 = CResourceManager::getUnitGuidByDataGroup
                        (*(CResourceManager **)(this + 0x68),pCVar7,(wstring_conflict *)local_128);
      *(undefined8 *)(this + 0x780) = uVar8;
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
                    /* try { // try from 008f9088 to 008f908c has its CatchHandler @ 008f96a6 */
      std::wstring::wstring((wstring_conflict *)local_138,L"UNIT_GUID",&local_36);
                    /* try { // try from 008f9097 to 008f909b has its CatchHandler @ 008f9696 */
      lVar12 = CResourceManager::getUnitGuidByDataGroup
                         (*(CResourceManager **)(this + 0x68),pCVar7,(wstring_conflict *)local_138);
      *(long *)(this + 0x900) = lVar12;
      if (lVar12 != -1) {
        *(undefined8 *)(this + 0x8b0) = 0xffffffffffffffff;
      }
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
                    /* try { // try from 008f90e1 to 008f90e5 has its CatchHandler @ 008f96f5 */
    std::wstring::wstring((wstring_conflict *)local_158,L"Mana Potion",&local_38);
                    /* try { // try from 008f90fe to 008f9102 has its CatchHandler @ 008f96d7 */
    std::wstring::wstring((wstring_conflict *)local_148,L"ITEMS",&local_37);
                    /* try { // try from 008f9107 to 008f9119 has its CatchHandler @ 008f96dc */
    pCVar6 = (CUnitResourceList *)CResourceManager::getMasterResourceList();
    pCVar7 = (CDataGroup *)
             CUnitResourceList::getDataGroupByObjectName
                       (pCVar6,(wstring_conflict *)local_148,(wstring_conflict *)local_158);
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
    if (pCVar7 != (CDataGroup *)0x0) {
                    /* try { // try from 008f9168 to 008f916c has its CatchHandler @ 008f95fe */
      std::wstring::wstring((wstring_conflict *)local_168,L"UNIT_GUID",&local_39);
                    /* try { // try from 008f9177 to 008f917b has its CatchHandler @ 008f95ee */
      uVar8 = CResourceManager::getUnitGuidByDataGroup
                        (*(CResourceManager **)(this + 0x68),pCVar7,(wstring_conflict *)local_168);
      *(undefined8 *)(this + 0x788) = uVar8;
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
                    /* try { // try from 008f91b0 to 008f91b4 has its CatchHandler @ 008f95a9 */
      std::wstring::wstring((wstring_conflict *)local_178,L"UNIT_GUID",&local_3a);
                    /* try { // try from 008f91bf to 008f91c3 has its CatchHandler @ 008f95a4 */
      lVar12 = CResourceManager::getUnitGuidByDataGroup
                         (*(CResourceManager **)(this + 0x68),pCVar7,(wstring_conflict *)local_178);
      *(long *)(this + 0x908) = lVar12;
      if (lVar12 != -1) {
        *(undefined8 *)(this + 0x8b8) = 0xffffffffffffffff;
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
    }
                    /* try { // try from 008f9206 to 008f920a has its CatchHandler @ 008f956a */
    std::wstring::wstring((wstring_conflict *)local_198,L"Town Portal Scroll",&local_3c);
                    /* try { // try from 008f9220 to 008f9224 has its CatchHandler @ 008f9565 */
    std::wstring::wstring((wstring_conflict *)local_188,L"ITEMS",&local_3b);
                    /* try { // try from 008f9229 to 008f923b has its CatchHandler @ 008f9555 */
    pCVar6 = (CUnitResourceList *)CResourceManager::getMasterResourceList();
    pCVar7 = (CDataGroup *)
             CUnitResourceList::getDataGroupByObjectName
                       (pCVar6,(wstring_conflict *)local_188,(wstring_conflict *)local_198);
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
    if (pCVar7 != (CDataGroup *)0x0) {
                    /* try { // try from 008f927d to 008f9281 has its CatchHandler @ 008f94d7 */
      std::wstring::wstring((wstring_conflict *)local_1a8,L"UNIT_GUID",&local_3d);
                    /* try { // try from 008f928c to 008f9290 has its CatchHandler @ 008f94c7 */
      lVar12 = CResourceManager::getUnitGuidByDataGroup
                         (*(CResourceManager **)(this + 0x68),pCVar7,(wstring_conflict *)local_1a8);
      *(long *)(this + 0x948) = lVar12;
      if (lVar12 != -1) {
        *(undefined8 *)(this + 0x8f8) = 0xffffffffffffffff;
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
    }
                    /* try { // try from 008f92d0 to 008f92d4 has its CatchHandler @ 008f993a */
    std::wstring::wstring((wstring_conflict *)local_1c8,L"Identify Scroll",&local_3f);
                    /* try { // try from 008f92ea to 008f92ee has its CatchHandler @ 008f98e5 */
    std::wstring::wstring((wstring_conflict *)local_1b8,L"ITEMS",&local_3e);
                    /* try { // try from 008f92f3 to 008f9305 has its CatchHandler @ 008f98d6 */
    pCVar6 = (CUnitResourceList *)CResourceManager::getMasterResourceList();
    pCVar7 = (CDataGroup *)
             CUnitResourceList::getDataGroupByObjectName
                       (pCVar6,(wstring_conflict *)local_1b8,(wstring_conflict *)local_1c8);
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
    if (pCVar7 != (CDataGroup *)0x0) {
                    /* try { // try from 008f9347 to 008f934b has its CatchHandler @ 008f99f5 */
      std::wstring::wstring((wstring_conflict *)local_1d8,L"UNIT_GUID",&local_40);
                    /* try { // try from 008f9356 to 008f935a has its CatchHandler @ 008f99f0 */
      lVar12 = CResourceManager::getUnitGuidByDataGroup
                         (*(CResourceManager **)(this + 0x68),pCVar7,(wstring_conflict *)local_1d8);
      *(long *)(this + 0x940) = lVar12;
      if (lVar12 != -1) {
        *(undefined8 *)(this + 0x8f0) = 0xffffffffffffffff;
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
    }
  }
  lVar12 = (**(code **)(*(long *)this + 0x1e0))(this);
  if (lVar12 != 0) {
    lVar12 = (**(code **)(*(long *)this + 0x1e0))(this);
    *(undefined4 *)(lVar12 + 0x24c) = 0x3c23d70a;
  }
  pCVar9 = (CQuestManager *)CQuestManager::getSingleton();
  setQuestManager(this,pCVar9);
  this_02 = (CSharedStash *)CSharedStash::getSingleton();
  CSharedStash::setPlayer(this_02,this);
  return;
}



/* address=008f9ad0
   symbol=CPlayer::levelUp */
/* DECOMPILATION FAILED:
Low-level Error: Overriding symbol with different type size */

/* address=008fa300
   symbol=CPlayer::fishingAICatch */

/* WARNING: Removing unreachable block (ram,0x008facf0) */
/* WARNING: Removing unreachable block (ram,0x008faedc) */
/* WARNING: Removing unreachable block (ram,0x008fae8f) */
/* WARNING: Removing unreachable block (ram,0x008fadc5) */
/* WARNING: Removing unreachable block (ram,0x008fafe2) */
/* WARNING: Removing unreachable block (ram,0x008fad54) */
/* WARNING: Removing unreachable block (ram,0x008fac8d) */
/* WARNING: Removing unreachable block (ram,0x008faf3c) */
/* WARNING: Removing unreachable block (ram,0x008faca8) */
/* WARNING: Removing unreachable block (ram,0x008fac7d) */
/* WARNING: Removing unreachable block (ram,0x008fb028) */
/* WARNING: Removing unreachable block (ram,0x008fad62) */
/* WARNING: Removing unreachable block (ram,0x008fae9a) */
/* WARNING: Removing unreachable block (ram,0x008faed1) */
/* WARNING: Removing unreachable block (ram,0x008fadd0) */
/* WARNING: Removing unreachable block (ram,0x008face2) */
/* WARNING: Removing unreachable block (ram,0x008fafd5) */
/* CPlayer::fishingAICatch(float, CLevel&) */

void CPlayer::fishingAICatch(float param_1,CLevel *param_2)

{
  int *piVar1;
  bool bVar2;
  char cVar3;
  int iVar4;
  CSpawnClass *pCVar5;
  long *plVar6;
  CPositionableObject *this;
  long lVar7;
  CGameUI *pCVar8;
  uint uVar9;
  CLevel *in_RSI;
  long *local_178;
  uint local_170;
  uint local_16c;
  undefined4 local_168;
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
  undefined4 *local_b8 [2];
  long local_a8 [2];
  long local_98 [2];
  long local_88 [2];
  long local_78 [2];
  long local_68 [2];
  long local_58 [3];
  allocator local_3a;
  allocator local_39 [9];

                    /* try { // try from 008fa331 to 008fa335 has its CatchHandler @ 008faeea */
  std::string::string((string *)local_58,"FISHING_CATCH",local_39);
                    /* try { // try from 008fa340 to 008fa344 has its CatchHandler @ 008faf27 */
  cVar3 = CGenericModel::animationPlayingSubstring
                    (*(CGenericModel **)(param_2 + 0x200),(string *)local_58);
  if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::string::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_58[0] + -8);
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::string::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
    }
  }
  if (cVar3 != '\0') {
    return;
  }
  if ((fishingAICatch(float,CLevel&)::g_Fishing == '\0') &&
     (iVar4 = __cxa_guard_acquire(&fishingAICatch(float,CLevel&)::g_Fishing), iVar4 != 0)) {
    fishingAICatch(float,CLevel&)::g_Fishing = &DAT_01424558;
    __cxa_guard_release(&fishingAICatch(float,CLevel&)::g_Fishing);
    __cxa_atexit(std::wstring::~wstring,&fishingAICatch(float,CLevel&)::g_Fishing,&__dso_handle);
  }
  if (*(long *)(fishingAICatch(float,CLevel&)::g_Fishing + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_68);
                    /* try { // try from 008faa45 to 008faa49 has its CatchHandler @ 008fac9b */
    std::wstring::assign((wstring_conflict *)&fishingAICatch(float,CLevel&)::g_Fishing);
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
  if ((fishingAICatch(float,CLevel&)::g_CaughtNothing == '\0') &&
     (iVar4 = __cxa_guard_acquire(&fishingAICatch(float,CLevel&)::g_CaughtNothing), iVar4 != 0)) {
    fishingAICatch(float,CLevel&)::g_CaughtNothing = &DAT_01424558;
    __cxa_guard_release(&fishingAICatch(float,CLevel&)::g_CaughtNothing);
    __cxa_atexit(std::wstring::~wstring,&fishingAICatch(float,CLevel&)::g_CaughtNothing,
                 &__dso_handle);
  }
  if (*(long *)(fishingAICatch(float,CLevel&)::g_CaughtNothing + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_78);
                    /* try { // try from 008faafd to 008fab01 has its CatchHandler @ 008fac8b */
    std::wstring::assign((wstring_conflict *)&fishingAICatch(float,CLevel&)::g_CaughtNothing);
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
  if ((fishingAICatch(float,CLevel&)::g_Caught == '\0') &&
     (iVar4 = __cxa_guard_acquire(&fishingAICatch(float,CLevel&)::g_Caught), iVar4 != 0)) {
    fishingAICatch(float,CLevel&)::g_Caught = &DAT_01424558;
    __cxa_guard_release(&fishingAICatch(float,CLevel&)::g_Caught);
    __cxa_atexit(std::wstring::~wstring,&fishingAICatch(float,CLevel&)::g_Caught,&__dso_handle);
  }
  if (*(long *)(fishingAICatch(float,CLevel&)::g_Caught + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_88);
                    /* try { // try from 008fabb5 to 008fabb9 has its CatchHandler @ 008fac6a */
    std::wstring::assign((wstring_conflict *)&fishingAICatch(float,CLevel&)::g_Caught);
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
  if ((fishingAICatch(float,CLevel&)::g_CaughtContaining == '\0') &&
     (iVar4 = __cxa_guard_acquire(&fishingAICatch(float,CLevel&)::g_CaughtContaining), iVar4 != 0))
  {
    fishingAICatch(float,CLevel&)::g_CaughtContaining = &DAT_01424558;
    __cxa_guard_release(&fishingAICatch(float,CLevel&)::g_CaughtContaining);
    __cxa_atexit(std::wstring::~wstring,&fishingAICatch(float,CLevel&)::g_CaughtContaining,
                 &__dso_handle);
  }
  if (*(long *)(fishingAICatch(float,CLevel&)::g_CaughtContaining + -6) == 0) {
    CStringTranslate::getSinglton();
    CStringTranslate::getTranslateString((wchar_t *)local_98);
                    /* try { // try from 008fa8d5 to 008fa8d9 has its CatchHandler @ 008fad15 */
    std::wstring::assign((wstring_conflict *)&fishingAICatch(float,CLevel&)::g_CaughtContaining);
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
  if (param_2[0x85c] == (CLevel)0x0) {
    std::wstring::wstring
              ((wstring_conflict *)local_148,
               (wstring_conflict *)&fishingAICatch(float,CLevel&)::g_CaughtNothing);
    wcslen(L"!");
                    /* try { // try from 008fa94f to 008fa953 has its CatchHandler @ 008fad10 */
    std::wstring::append((wchar_t *)local_148,0xfcd158);
                    /* try { // try from 008fa961 to 008fa965 has its CatchHandler @ 008fad0b */
    std::wstring::wstring
              ((wstring_conflict *)local_158,
               (wstring_conflict *)&fishingAICatch(float,CLevel&)::g_Fishing);
                    /* try { // try from 008fa96a to 008fa97e has its CatchHandler @ 008facfb */
    pCVar8 = (CGameUI *)CResourceManager::getGameUI();
    CGameUI::openModalDialog(pCVar8,(wstring_conflict *)local_158,(wstring_conflict *)local_148,0);
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
    goto LAB_008fa6bd;
  }
  if (*(long *)(in_RSI + 0x1d8) == 0) {
                    /* try { // try from 008fac60 to 008fac64 has its CatchHandler @ 008fb023 */
    std::wstring::wstring((wstring_conflict *)local_a8,L"FISH_SPAWN",&local_3a);
  }
  else {
                    /* try { // try from 008fa417 to 008fa41b has its CatchHandler @ 008fb023 */
    std::wstring::wstring
              ((wstring_conflict *)local_a8,(wstring_conflict *)(*(long *)(in_RSI + 0x1d8) + 0x5a8))
    ;
  }
                    /* try { // try from 008fa423 to 008fa427 has its CatchHandler @ 008fafd0 */
  pCVar5 = (CSpawnClass *)
           CResourceManager::getSpawnClassByName
                     (*(CResourceManager **)(param_2 + 0x68),(wstring_conflict *)local_a8);
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
  local_178 = (long *)0x0;
  local_170 = 0;
  local_16c = 0;
  local_168 = 10;
                    /* try { // try from 008fa488 to 008fa48c has its CatchHandler @ 008fb03b */
  CResourceManager::createUnitsBySpawnClass
            (*(CResourceManager **)(param_2 + 0x68),pCVar5,(TArrayList *)&local_178,1,
             (CCharacter *)param_2,(CCharacter *)param_2,-1,0);
  local_b8[0] = &DAT_01424558;
  if (local_170 == 0) {
LAB_008fa778:
    std::wstring::wstring
              ((wstring_conflict *)local_108,
               (wstring_conflict *)&fishingAICatch(float,CLevel&)::g_CaughtContaining);
    wcslen(L":\n");
                    /* try { // try from 008fa7a2 to 008fa7a6 has its CatchHandler @ 008faddb */
    std::wstring::append((wchar_t *)local_108,0xfd343c);
                    /* try { // try from 008fa7b8 to 008fa7bc has its CatchHandler @ 008fae06 */
    std::operator+((wstring_conflict *)local_118,(wstring_conflict *)local_108);
                    /* try { // try from 008fa7cb to 008fa7cf has its CatchHandler @ 008fae08 */
    std::wstring::wstring((wstring_conflict *)local_128,(wstring_conflict *)local_118);
    wcslen(L"!");
                    /* try { // try from 008fa7e5 to 008fa7e9 has its CatchHandler @ 008fae17 */
    std::wstring::append((wchar_t *)local_128,0xfcd158);
                    /* try { // try from 008fa7f7 to 008fa7fb has its CatchHandler @ 008fae24 */
    std::wstring::wstring
              ((wstring_conflict *)local_138,
               (wstring_conflict *)&fishingAICatch(float,CLevel&)::g_Fishing);
                    /* try { // try from 008fa800 to 008fa814 has its CatchHandler @ 008fae26 */
    pCVar8 = (CGameUI *)CResourceManager::getGameUI();
    CGameUI::openModalDialog(pCVar8,(wstring_conflict *)local_138,(wstring_conflict *)local_128,0);
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
  else {
    uVar9 = 0;
    bVar2 = false;
    do {
      plVar6 = local_178;
      if (uVar9 < local_16c) {
        plVar6 = local_178 + uVar9;
      }
      if ((*plVar6 != 0) &&
         (this = (CPositionableObject *)
                 __dynamic_cast(*plVar6,&CBaseUnit::typeinfo,&CEquipment::typeinfo,0),
         this != (CPositionableObject *)0x0)) {
                    /* try { // try from 008fa4fc to 008fa585 has its CatchHandler @ 008fb033 */
        (**(code **)(*(long *)this + 0x2a0))(this);
        std::wstring::assign((wstring_conflict *)local_b8);
        cVar3 = CBaseUnit::ISA((CBaseUnit *)this,0x7c);
        if (cVar3 != '\0') {
          bVar2 = true;
        }
        if ((*(CInventory **)(param_2 + 0x490) != (CInventory *)0x0) &&
           (lVar7 = CInventory::pickupEquipment
                              (*(CInventory **)(param_2 + 0x490),(CEquipment *)this,true),
           lVar7 == 0)) {
                    /* try { // try from 008fa74a to 008fa78c has its CatchHandler @ 008fb033 */
          CLevel::addItem(in_RSI,(CItem *)this,(Vector3 *)(param_2 + 0x84),true);
          CPositionableObject::setPosition(this,(Vector3 *)(param_2 + 0x84));
          (**(code **)(*(long *)this + 0x360))(this);
        }
      }
      uVar9 = uVar9 + 1;
    } while (uVar9 < local_170);
    if (!bVar2) goto LAB_008fa778;
    std::wstring::wstring
              ((wstring_conflict *)local_c8,
               (wstring_conflict *)&fishingAICatch(float,CLevel&)::g_Caught);
    wcslen(L" ");
                    /* try { // try from 008fa59b to 008fa59f has its CatchHandler @ 008faf37 */
    std::wstring::append((wchar_t *)local_c8,0xfd0b98);
                    /* try { // try from 008fa5b1 to 008fa5b5 has its CatchHandler @ 008faf47 */
    std::operator+((wstring_conflict *)local_d8,(wstring_conflict *)local_c8);
                    /* try { // try from 008fa5c4 to 008fa5c8 has its CatchHandler @ 008faf4c */
    std::wstring::wstring((wstring_conflict *)local_e8,(wstring_conflict *)local_d8);
    wcslen(L"!");
                    /* try { // try from 008fa5de to 008fa5e2 has its CatchHandler @ 008faf51 */
    std::wstring::append((wchar_t *)local_e8,0xfcd158);
                    /* try { // try from 008fa5f3 to 008fa5f7 has its CatchHandler @ 008faf61 */
    std::wstring::wstring
              ((wstring_conflict *)local_f8,
               (wstring_conflict *)&fishingAICatch(float,CLevel&)::g_Fishing);
                    /* try { // try from 008fa5fc to 008fa610 has its CatchHandler @ 008faf66 */
    pCVar8 = (CGameUI *)CResourceManager::getGameUI();
    CGameUI::openModalDialog(pCVar8,(wstring_conflict *)local_f8,(wstring_conflict *)local_e8,0);
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
                    /* try { // try from 008fa686 to 008fa68a has its CatchHandler @ 008fb033 */
  incrementJournalStatistic((CPlayer *)param_2,0xe,1);
  if ((allocator *)(local_b8[0] + -6) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = local_b8[0] + -2;
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -6));
    }
  }
  if (local_178 != (long *)0x0) {
    operator_delete__(local_178);
    local_178 = (long *)0x0;
  }
LAB_008fa6bd:
  (**(code **)(*(long *)param_2 + 0x348))(param_2,2);
  if (param_2[0x705] != (CLevel)0x0) {
    plVar6 = *(long **)(param_2 + 0x2e8);
    param_2[0x705] = (CLevel)0x0;
    if (plVar6 != (long *)0x0) {
      (**(code **)(*plVar6 + 0x378))(plVar6,1,1);
    }
    plVar6 = *(long **)(param_2 + 0x2f8);
    if (plVar6 != (long *)0x0) {
      (**(code **)(*plVar6 + 0x378))(plVar6,1,1);
    }
  }
  return;
}



/* address=008fb050
   symbol=CPlayer::applyAchievementsForKilledCharacter */

/* WARNING: Removing unreachable block (ram,0x008fb6a4) */
/* WARNING: Removing unreachable block (ram,0x008fb642) */
/* WARNING: Removing unreachable block (ram,0x008fb660) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* CPlayer::applyAchievementsForKilledCharacter(CCharacter*) */

void __thiscall CPlayer::applyAchievementsForKilledCharacter(CPlayer *this,CCharacter *param_1)

{
  int *piVar1;
  int iVar2;
  CPlayer CVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  CAchievements *pCVar7;
  long lVar8;
  CAchievement *pCVar9;
  wstring_conflict *pwVar10;
  undefined8 uVar11;
  float fVar12;
  long local_c8 [2];
  STRINGS local_b8 [16];
  STRINGS local_a8 [16];
  STRINGS local_98 [16];
  STRINGS local_88 [16];
  STRINGS local_78 [16];
  STRINGS local_68 [16];
  long local_58 [2];
  long local_48 [3];

  iVar5 = CCharacter::HP(param_1);
  if (0 < iVar5) {
    return;
  }
  lVar8 = *(long *)(this + 0x68);
  if (((lVar8 == 0) || (*(int *)(lVar8 + 0x30) == 0)) || (**(long **)(lVar8 + 0x28) == 0)) {
    iVar5 = 1;
  }
  else {
    iVar5 = *(int *)(**(long **)(lVar8 + 0x28) + 0x38ec);
  }
  CVar3 = this[0xa15];
  iVar4 = *(int *)(this + 0x7f0);
  pwVar10 = (wstring_conflict *)(param_1 + 0x40);
  fVar12 = *(float *)(this + 0x388);
  STRINGS::StringUpper((STRINGS *)local_48,pwVar10);
                    /* try { // try from 008fb118 to 008fb11c has its CatchHandler @ 008fb64d */
  iVar6 = std::wstring::compare((wchar_t *)local_48);
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
  uVar11 = 10;
  if (iVar6 != 0) {
    STRINGS::StringUpper((STRINGS *)local_58,pwVar10);
                    /* try { // try from 008fb1bb to 008fb1bf has its CatchHandler @ 008fb6a2 */
    iVar6 = std::wstring::compare((wchar_t *)local_58);
    if ((allocator *)(local_58[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_58[0] + -8);
      iVar2 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar2 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
      }
    }
    uVar11 = 0xd;
    if (iVar6 != 0) {
      STRINGS::StringUpper(local_68,pwVar10);
                    /* try { // try from 008fb1fe to 008fb202 has its CatchHandler @ 008fb6e5 */
      iVar6 = std::wstring::compare((wchar_t *)local_68);
      std::wstring::~wstring((wstring_conflict *)local_68);
      if (iVar6 == 0) goto LAB_008fb348;
      STRINGS::StringUpper(local_78,pwVar10);
                    /* try { // try from 008fb233 to 008fb237 has its CatchHandler @ 008fb6d5 */
      iVar6 = std::wstring::compare((wchar_t *)local_78);
      uVar11 = 8;
      std::wstring::~wstring((wstring_conflict *)local_78);
      if (iVar6 != 0) {
        STRINGS::StringUpper(local_88,pwVar10);
                    /* try { // try from 008fb26e to 008fb272 has its CatchHandler @ 008fb6c5 */
        iVar6 = std::wstring::compare((wchar_t *)local_88);
        uVar11 = 0xc;
        std::wstring::~wstring((wstring_conflict *)local_88);
        if (iVar6 != 0) {
          STRINGS::StringUpper(local_98,pwVar10);
                    /* try { // try from 008fb2a9 to 008fb2ad has its CatchHandler @ 008fb6ba */
          iVar6 = std::wstring::compare((wchar_t *)local_98);
          uVar11 = 7;
          std::wstring::~wstring((wstring_conflict *)local_98);
          if (iVar6 != 0) {
            STRINGS::StringUpper(local_a8,pwVar10);
                    /* try { // try from 008fb2e4 to 008fb2e8 has its CatchHandler @ 008fb6b5 */
            iVar6 = std::wstring::compare((wchar_t *)local_a8);
            uVar11 = 9;
            std::wstring::~wstring((wstring_conflict *)local_a8);
            if (iVar6 != 0) {
              STRINGS::StringUpper(local_b8,pwVar10);
                    /* try { // try from 008fb31f to 008fb323 has its CatchHandler @ 008fb6af */
              iVar6 = std::wstring::compare((wchar_t *)local_b8);
              uVar11 = 0xb;
              std::wstring::~wstring((wstring_conflict *)local_b8);
              if (iVar6 != 0) goto LAB_008fb348;
            }
          }
        }
      }
    }
  }
  pCVar7 = (CAchievements *)CAchievements::getSingleton();
  lVar8 = CAchievements::getAchievement(pCVar7,uVar11);
  if (lVar8 != 0) {
    pCVar7 = (CAchievements *)CAchievements::getSingleton();
    pCVar9 = (CAchievement *)CAchievements::getAchievement(pCVar7,uVar11);
    CAchievement::forceComplete(pCVar9);
    return;
  }
LAB_008fb348:
  STRINGS::StringUpper((STRINGS *)local_c8,pwVar10);
                    /* try { // try from 008fb360 to 008fb364 has its CatchHandler @ 008fb62f */
  iVar6 = std::wstring::compare((wchar_t *)local_c8);
  if ((allocator *)(local_c8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_c8[0] + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
    }
  }
  if (iVar6 == 0) {
    if (iVar4 == 0) {
      pCVar7 = (CAchievements *)CAchievements::getSingleton();
      pCVar9 = (CAchievement *)CAchievements::getAchievement(pCVar7,0x22);
      CAchievement::forceComplete(pCVar9);
    }
    if (iVar5 == 1) {
      pCVar7 = (CAchievements *)CAchievements::getSingleton();
      pCVar9 = (CAchievement *)CAchievements::getAchievement(pCVar7,0xe);
      CAchievement::forceComplete(pCVar9);
      if (CVar3 != (CPlayer)0x0) {
        pCVar7 = (CAchievements *)CAchievements::getSingleton();
        pCVar9 = (CAchievement *)CAchievements::getAchievement(pCVar7,0x12);
        CAchievement::forceComplete(pCVar9);
      }
    }
    else if (iVar5 < 2) {
      if (iVar5 == 0) {
        pCVar7 = (CAchievements *)CAchievements::getSingleton();
        pCVar9 = (CAchievement *)CAchievements::getAchievement(pCVar7,0xe);
        CAchievement::forceComplete(pCVar9);
        if (CVar3 != (CPlayer)0x0) {
          pCVar7 = (CAchievements *)CAchievements::getSingleton();
          pCVar9 = (CAchievement *)CAchievements::getAchievement(pCVar7,0x11);
          CAchievement::forceComplete(pCVar9);
        }
      }
    }
    else if (iVar5 == 2) {
      pCVar7 = (CAchievements *)CAchievements::getSingleton();
      pCVar9 = (CAchievement *)CAchievements::getAchievement(pCVar7,0xe);
      CAchievement::forceComplete(pCVar9);
      pCVar7 = (CAchievements *)CAchievements::getSingleton();
      pCVar9 = (CAchievement *)CAchievements::getAchievement(pCVar7,0xf);
      CAchievement::forceComplete(pCVar9);
      if (CVar3 != (CPlayer)0x0) {
        pCVar7 = (CAchievements *)CAchievements::getSingleton();
        pCVar9 = (CAchievement *)CAchievements::getAchievement(pCVar7,0x13);
        CAchievement::forceComplete(pCVar9);
      }
    }
    else if (iVar5 == 3) {
      pCVar7 = (CAchievements *)CAchievements::getSingleton();
      pCVar9 = (CAchievement *)CAchievements::getAchievement(pCVar7,0xe);
      CAchievement::forceComplete(pCVar9);
      pCVar7 = (CAchievements *)CAchievements::getSingleton();
      pCVar9 = (CAchievement *)CAchievements::getAchievement(pCVar7,0xf);
      CAchievement::forceComplete(pCVar9);
      pCVar7 = (CAchievements *)CAchievements::getSingleton();
      pCVar9 = (CAchievement *)CAchievements::getAchievement(pCVar7,0x10);
      CAchievement::forceComplete(pCVar9);
      if (CVar3 != (CPlayer)0x0) {
        pCVar7 = (CAchievements *)CAchievements::getSingleton();
        pCVar9 = (CAchievement *)CAchievements::getAchievement(pCVar7,0x14);
        CAchievement::forceComplete(pCVar9);
      }
    }
    fVar12 = fVar12 / _DAT_00fd3a60;
    if ((fVar12 <= DAT_00fa8730) && (!NAN(fVar12) && !NAN(DAT_00fa8730))) {
      pCVar7 = (CAchievements *)CAchievements::getSingleton();
      pCVar9 = (CAchievement *)CAchievements::getAchievement(pCVar7,0x15);
      CAchievement::forceComplete(pCVar9);
    }
    if ((fVar12 <= DAT_00fa86d0) && (!NAN(fVar12) && !NAN(DAT_00fa86d0))) {
      pCVar7 = (CAchievements *)CAchievements::getSingleton();
      pCVar9 = (CAchievement *)CAchievements::getAchievement(pCVar7,0x16);
      CAchievement::forceComplete(pCVar9);
    }
  }
  return;
}



/* address=008fb700
   symbol=CPlayer::~CPlayer */

/* WARNING: Removing unreachable block (ram,0x008fbd20) */
/* WARNING: Removing unreachable block (ram,0x008fbd88) */
/* WARNING: Removing unreachable block (ram,0x008fbec7) */
/* WARNING: Removing unreachable block (ram,0x008fbcb8) */
/* WARNING: Removing unreachable block (ram,0x008fbca3) */
/* WARNING: Removing unreachable block (ram,0x008fbe5c) */
/* WARNING: Removing unreachable block (ram,0x008fbebc) */
/* WARNING: Removing unreachable block (ram,0x008fbd7d) */
/* WARNING: Removing unreachable block (ram,0x008fbd15) */
/* WARNING: Removing unreachable block (ram,0x008fbeed) */
/* CPlayer::~CPlayer() */

void __thiscall CPlayer::~CPlayer(CPlayer *this)

{
  int *piVar1;
  CPlayer *pCVar2;
  int iVar3;
  long *plVar4;
  ulong uVar5;
  undefined8 *puVar6;
  long lVar7;
  uint uVar8;
  uint uVar9;
  long *plVar10;
  long lVar11;
  allocator *paVar12;

  *(undefined ***)this = &PTR__CPlayer_00fd3510;
  *(undefined ***)(this + 0x1d8) = &PTR__CPlayer_00fd3940;
  *(undefined ***)(this + 0x1e0) = &PTR__CPlayer_00fd3990;
  if (*(long **)(this + 0x848) != (long *)0x0) {
                    /* try { // try from 008fb74b to 008fbad9 has its CatchHandler @ 008fbdc0 */
    (**(code **)(**(long **)(this + 0x848) + 0x2a0))();
    OGRE_UTILITIES::removeChildFromParentNode(*(SceneNode **)(this + 0x848));
  }
  if (*(long **)(this + 0x840) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x840) + 8))();
    *(undefined8 *)(this + 0x840) = 0;
  }
  if (*(long **)(this + 0x848) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x848) + 0x1f0))();
    plVar4 = (long *)0x0;
    if (*(long *)(this + 0x68) != 0) {
      plVar4 = *(long **)(*(long *)(this + 0x68) + 0x10);
    }
    (**(code **)(*plVar4 + 0x248))();
    *(undefined8 *)(this + 0x848) = 0;
  }
  if (*(CQuestManager **)(this + 0x868) != (CQuestManager *)0x0) {
    CQuestManager::setPlayer(*(CQuestManager **)(this + 0x868),(CPlayer *)0x0);
  }
  *(undefined8 *)(this + 0x868) = 0;
  if ((*(long *)(this + 0x828) != 0) &&
     (plVar4 = (long *)Ogre::SceneNode::getParentSceneNode(), plVar4 != (long *)0x0)) {
    (**(code **)(*plVar4 + 0x1e0))(plVar4,*(undefined8 *)(*(long *)(this + 0x828) + 0x58));
  }
  plVar4 = *(long **)(this + 0x830);
  if (plVar4 != (long *)0x0) {
    (**(code **)(*plVar4 + 0x50))(plVar4,0);
  }
  lVar11 = *(long *)(this + 0x7a0);
  lVar7 = *(long *)(this + 0x798);
  uVar5 = 0;
  uVar9 = 0;
  if (lVar11 - lVar7 >> 3 != 0) {
    do {
      plVar4 = *(long **)(lVar7 + uVar5 * 8);
      if (plVar4 != (long *)0x0) {
        (**(code **)(*plVar4 + 8))();
        *(undefined8 *)(*(long *)(this + 0x798) + uVar5 * 8) = 0;
        lVar7 = *(long *)(this + 0x798);
        lVar11 = *(long *)(this + 0x7a0);
      }
      uVar9 = uVar9 + 1;
      uVar5 = (ulong)uVar9;
    } while (uVar5 < (ulong)(lVar11 - lVar7 >> 3));
  }
  *(long *)(this + 0x7a0) = lVar7;
  if (*(int *)(this + 0xa48) != 0) {
    uVar9 = 0;
    do {
      uVar8 = *(uint *)(this + 0xa4c);
      if (uVar9 < uVar8) {
        plVar4 = (long *)((ulong)uVar9 * 8 + *(long *)(this + 0xa40));
      }
      else {
        plVar4 = *(long **)(this + 0xa40);
      }
      if (*plVar4 != 0) {
        if (uVar9 < uVar8) {
          puVar6 = (undefined8 *)((ulong)uVar9 * 8 + *(long *)(this + 0xa40));
        }
        else {
          puVar6 = *(undefined8 **)(this + 0xa40);
        }
        plVar4 = (long *)*puVar6;
        if (plVar4 != (long *)0x0) {
          if ((void *)plVar4[3] != (void *)0x0) {
            operator_delete((void *)plVar4[3]);
          }
          paVar12 = (allocator *)(*plVar4 + -0x18);
          if (paVar12 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(*plVar4 + -8);
            iVar3 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar3 < 1) {
              std::wstring::_Rep::_M_destroy(paVar12);
            }
          }
          Ogre::NedAllocImpl::deallocBytes(plVar4);
          uVar8 = *(uint *)(this + 0xa4c);
        }
        if (uVar9 < uVar8) {
          puVar6 = (undefined8 *)((ulong)uVar9 * 8 + *(long *)(this + 0xa40));
        }
        else {
          puVar6 = *(undefined8 **)(this + 0xa40);
        }
        *puVar6 = 0;
      }
      uVar9 = uVar9 + 1;
    } while (uVar9 < *(uint *)(this + 0xa48));
  }
  *(undefined4 *)(this + 0xa48) = 0;
  *(undefined4 *)(this + 0xa4c) = 0;
  if (*(void **)(this + 0xa40) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0xa40));
  }
  plVar4 = *(long **)(this + 0xa58);
  *(undefined8 *)(this + 0xa40) = 0;
  pCVar2 = this + 0xa58;
  *(undefined4 *)(this + 0xa60) = 0;
  *(undefined4 *)(this + 0xa64) = 0;
  if (plVar4 != (long *)0x0) {
    plVar10 = plVar4 + plVar4[-1];
    while (plVar10 != plVar4) {
      plVar10 = plVar10 + -1;
      paVar12 = (allocator *)(*plVar10 + -0x18);
      if (paVar12 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(*plVar10 + -8);
        iVar3 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar3 < 1) {
          std::wstring::_Rep::_M_destroy(paVar12);
        }
        plVar4 = *(long **)pCVar2;
      }
    }
    operator_delete__((void *)(*(long *)(this + 0xa58) + -8));
  }
  *(undefined8 *)(this + 0xa58) = 0;
  if (*(long **)(this + 0x778) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x778) + 8))();
    *(undefined8 *)(this + 0x778) = 0;
  }
  if (*(long **)(this + 0x828) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x828) + 8))();
    *(undefined8 *)(this + 0x828) = 0;
  }
  if (*(long **)(this + 0x830) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x830) + 8))();
    *(undefined8 *)(this + 0x830) = 0;
  }
  if (*(long **)(this + 0x838) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x838) + 8))();
    *(undefined8 *)(this + 0x838) = 0;
  }
  plVar4 = *(long **)(this + 0xa58);
  if (plVar4 != (long *)0x0) {
    plVar10 = plVar4 + plVar4[-1];
    while (plVar10 != plVar4) {
      plVar10 = plVar10 + -1;
      paVar12 = (allocator *)(*plVar10 + -0x18);
      if (paVar12 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(*plVar10 + -8);
        iVar3 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar3 < 1) {
          std::wstring::_Rep::_M_destroy(paVar12);
          plVar4 = *(long **)pCVar2;
        }
        else {
          plVar4 = *(long **)pCVar2;
        }
      }
    }
    operator_delete__((void *)(*(long *)(this + 0xa58) + -8));
    *(undefined8 *)(this + 0xa58) = 0;
  }
  if (*(void **)(this + 0xa40) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0xa40));
    *(undefined8 *)(this + 0xa40) = 0;
  }
  paVar12 = (allocator *)(*(long *)(this + 0x8a8) + -0x18);
  if (paVar12 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(*(long *)(this + 0x8a8) + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar12);
    }
  }
  paVar12 = (allocator *)(*(long *)(this + 0x8a0) + -0x18);
  if (paVar12 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(*(long *)(this + 0x8a0) + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar12);
    }
  }
  paVar12 = (allocator *)(*(long *)(this + 0x898) + -0x18);
  if (paVar12 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(*(long *)(this + 0x898) + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar12);
    }
  }
  paVar12 = (allocator *)(*(long *)(this + 0x890) + -0x18);
  if (paVar12 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(*(long *)(this + 0x890) + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar12);
    }
  }
  paVar12 = (allocator *)(*(long *)(this + 0x888) + -0x18);
  if (paVar12 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(*(long *)(this + 0x888) + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar12);
    }
  }
  paVar12 = (allocator *)(*(long *)(this + 2000) + -0x18);
  if (paVar12 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(*(long *)(this + 2000) + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar12);
    }
  }
  paVar12 = (allocator *)(*(long *)(this + 0x7b8) + -0x18);
  if (paVar12 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(*(long *)(this + 0x7b8) + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar12);
    }
  }
  if (*(void **)(this + 0x798) != (void *)0x0) {
    operator_delete(*(void **)(this + 0x798));
  }
  CCharacter::~CCharacter((CCharacter *)this);
  return;
}



/* address=008fbf00
   symbol=CPlayer::~CPlayer */

/* non-virtual thunk to CPlayer::~CPlayer() */

void __thiscall CPlayer::~CPlayer(CPlayer *this)

{
  ~CPlayer(this + -0x1e0);
  return;
}



/* address=008fbf10
   symbol=CPlayer::~CPlayer */

/* non-virtual thunk to CPlayer::~CPlayer() */

void __thiscall CPlayer::~CPlayer(CPlayer *this)

{
  ~CPlayer(this + -0x1d8);
  return;
}



/* address=008fbf20
   symbol=CPlayer::~CPlayer */

/* non-virtual thunk to CPlayer::~CPlayer() */

void __thiscall CPlayer::~CPlayer(CPlayer *this)

{
  ~CPlayer(this + -0x1e0);
  return;
}



/* address=008fbf30
   symbol=CPlayer::~CPlayer */

/* non-virtual thunk to CPlayer::~CPlayer() */

void __thiscall CPlayer::~CPlayer(CPlayer *this)

{
  ~CPlayer(this + -0x1d8);
  return;
}



/* address=008fbf40
   symbol=CPlayer::~CPlayer */

/* CPlayer::~CPlayer() */

void __thiscall CPlayer::~CPlayer(CPlayer *this)

{
  ~CPlayer(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}



/* address=008fbf60
   symbol=CPlayer::fillSaveState */

/* WARNING: Removing unreachable block (ram,0x008fc299) */
/* WARNING: Removing unreachable block (ram,0x008fc2e8) */
/* WARNING: Removing unreachable block (ram,0x008fc2f3) */
/* CPlayer::fillSaveState(CCharacterSaveState&) */

void __thiscall CPlayer::fillSaveState(CPlayer *this,CCharacterSaveState *param_1)

{
  int *piVar1;
  int iVar2;
  CFileSystem *this_00;
  ulong *puVar3;
  long *plVar4;
  wstring_conflict *pwVar5;
  uint uVar6;
  uint uVar7;
  ulong uVar8;
  long lVar9;
  long *plVar10;
  wstring_conflict *pwVar11;
  allocator *paVar12;
  ulong *puVar13;
  uint uVar14;
  wstring_conflict *local_68;
  uint local_60;
  uint local_5c;
  undefined4 local_58;
  long local_48 [3];

  CCharacter::fillSaveState((CCharacterSaveState *)this);
  param_1[0x34] = *(CCharacterSaveState *)(this + 0x791);
  *(undefined4 *)(param_1 + 0x68) = *(undefined4 *)(this + 0x7d8);
  *(undefined4 *)(param_1 + 0xf8) = *(undefined4 *)(this + 0x388);
  local_68 = (wstring_conflict *)0x0;
  local_60 = 0;
  local_5c = 0;
  local_58 = 10;
                    /* try { // try from 008fbfc9 to 008fc017 has its CatchHandler @ 008fc2c1 */
  this_00 = (CFileSystem *)CFileSystem::getSingleton();
  CFileSystem::getEnabledModNames(this_00,(TArrayList *)&local_68);
  if (local_60 != 0) {
    uVar14 = 0;
    do {
      pwVar11 = local_68;
      if (uVar14 < local_5c) {
        pwVar11 = local_68 + (ulong)uVar14 * 8;
      }
      std::wstring::wstring((wstring_conflict *)local_48,pwVar11);
      uVar7 = *(uint *)(param_1 + 0x218);
      if (uVar7 < *(uint *)(param_1 + 0x21c)) {
        puVar13 = *(ulong **)(param_1 + 0x210);
      }
      else if (*(long *)(param_1 + 0x210) == 0) {
        uVar8 = (ulong)*(uint *)(param_1 + 0x220);
        *(uint *)(param_1 + 0x21c) = *(uint *)(param_1 + 0x220);
        puVar3 = operator_new__(uVar8 * 8 + 8);
        *puVar3 = uVar8;
        puVar13 = puVar3 + 1;
        if (uVar8 != 0) {
          lVar9 = uVar8 - 2;
          do {
            lVar9 = lVar9 + -1;
            puVar3[1] = (ulong)&DAT_01424558;
            puVar3 = puVar3 + 1;
          } while (lVar9 != -2);
        }
        *(ulong **)(param_1 + 0x210) = puVar13;
        uVar7 = *(uint *)(param_1 + 0x218);
      }
      else {
        uVar6 = *(uint *)(param_1 + 0x21c) + *(int *)(param_1 + 0x220);
        uVar8 = (ulong)uVar6;
                    /* try { // try from 008fc055 to 008fc204 has its CatchHandler @ 008fc2a4 */
        puVar3 = operator_new__(uVar8 * 8 + 8);
        *puVar3 = uVar8;
        puVar13 = puVar3 + 1;
        if (uVar8 != 0) {
          lVar9 = uVar8 - 2;
          do {
            lVar9 = lVar9 + -1;
            puVar3[1] = (ulong)&DAT_01424558;
            puVar3 = puVar3 + 1;
          } while (lVar9 != -2);
        }
        if (*(int *)(param_1 + 0x21c) != 0) {
          uVar7 = 0;
          do {
            std::wstring::assign((wstring_conflict *)(puVar13 + uVar7));
            uVar7 = uVar7 + 1;
          } while (uVar7 < *(uint *)(param_1 + 0x21c));
        }
        lVar9 = *(long *)(param_1 + 0x210);
        if (lVar9 != 0) {
          plVar10 = (long *)(lVar9 + *(long *)(lVar9 + -8) * 8);
          do {
            plVar4 = *(long **)(param_1 + 0x210);
            while( true ) {
              do {
                if (plVar10 == plVar4) {
                  operator_delete__((void *)(*(long *)(param_1 + 0x210) + -8));
                  goto LAB_008fc106;
                }
                plVar10 = plVar10 + -1;
                paVar12 = (allocator *)(*plVar10 + -0x18);
              } while (paVar12 == (allocator *)&std::wstring::_Rep::_S_empty_rep_storage);
              LOCK();
              piVar1 = (int *)(*plVar10 + -8);
              iVar2 = *piVar1;
              *piVar1 = *piVar1 + -1;
              UNLOCK();
              if (0 < iVar2) break;
              std::wstring::_Rep::_M_destroy(paVar12);
              plVar4 = *(long **)(param_1 + 0x210);
            }
          } while( true );
        }
LAB_008fc106:
        *(ulong **)(param_1 + 0x210) = puVar13;
        uVar7 = *(uint *)(param_1 + 0x218);
        *(uint *)(param_1 + 0x21c) = uVar6;
      }
      std::wstring::assign((wstring_conflict *)(puVar13 + uVar7));
      *(int *)(param_1 + 0x218) = *(int *)(param_1 + 0x218) + 1;
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
      uVar14 = uVar14 + 1;
    } while (uVar14 < local_60);
  }
  if (local_68 != (wstring_conflict *)0x0) {
    pwVar11 = local_68 + *(long *)(local_68 + -8) * 8;
    pwVar5 = local_68;
    while (pwVar11 != pwVar5) {
      pwVar11 = pwVar11 + -8;
      paVar12 = (allocator *)(*(long *)pwVar11 + -0x18);
      if (paVar12 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(*(long *)pwVar11 + -8);
        iVar2 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        pwVar5 = local_68;
        if (iVar2 < 1) {
          std::wstring::_Rep::_M_destroy(paVar12);
          pwVar5 = local_68;
        }
      }
    }
    operator_delete__(pwVar11 + -8);
  }
  return;
}



/* address=008fc300
   symbol=CPlayer::getIsInGodMode */

/* CPlayer::getIsInGodMode() */

CPlayer __thiscall CPlayer::getIsInGodMode(CPlayer *this)

{
  return this[0x790];
}



/* address=008fc310
   symbol=CPlayer::getIsPlayer */

/* CPlayer::getIsPlayer() */

undefined8 CPlayer::getIsPlayer(void)

{
  return 1;
}



/* address=00afcc10
   symbol=CPlayer::setCheater */

/* WARNING: Removing unreachable block (ram,0x00afccc9) */
/* CPlayer::setCheater() */

void __thiscall CPlayer::setCheater(CPlayer *this)

{
  int *piVar1;
  int iVar2;
  long local_28 [2];

  if (this[0x791] != (CPlayer)0xd6) {
    std::wstring::wstring((wstring_conflict *)local_28,(wstring_conflict *)(this + 0x4c0));
    wcslen(L" the Cheat");
                    /* try { // try from 00afcc56 to 00afcc5a has its CatchHandler @ 00afccc7 */
    std::wstring::append((wchar_t *)local_28,0xfea1e8);
                    /* try { // try from 00afcc61 to 00afcc65 has its CatchHandler @ 00afccb4 */
    std::wstring::assign((wstring_conflict *)(this + 0x4c0));
    if ((allocator *)(local_28[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
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
  this[0x791] = (CPlayer)0xd6;
  return;
}



/* export-summary functions=66 failures=2 */
