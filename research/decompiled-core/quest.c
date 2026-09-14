/* Targeted Ghidra class export.
   namespace=CQuest
   Treat pseudocode as navigation evidence. */


/* address=00d0c700
   symbol=CQuest::getPlayer */

/* CQuest::getPlayer() */

undefined8 __thiscall CQuest::getPlayer(CQuest *this)

{
  undefined8 uVar1;

  uVar1 = 0;
  if (*(long *)(this + 0x1d0) != 0) {
    uVar1 = *(undefined8 *)(*(long *)(this + 0x1d0) + 0x10);
  }
  return uVar1;
}

/* address=00d0c720
   symbol=CQuest::setQuestAcceptDialogInteracted */

/* CQuest::setQuestAcceptDialogInteracted(bool) */

void __thiscall CQuest::setQuestAcceptDialogInteracted(CQuest *this,bool param_1)

{
  uint uVar1;
  ulong uVar2;

  if (*(int *)(this + 0x68) != 0) {
    uVar1 = 0;
    do {
      while (uVar1 < *(uint *)(this + 0x6c)) {
        uVar2 = (ulong)uVar1;
        uVar1 = uVar1 + 1;
        *(bool *)(*(long *)(uVar2 * 8 + *(long *)(this + 0x60)) + 0x76) = param_1;
        if (*(uint *)(this + 0x68) <= uVar1) {
          return;
        }
      }
      uVar1 = uVar1 + 1;
      *(bool *)(**(long **)(this + 0x60) + 0x76) = param_1;
    } while (uVar1 < *(uint *)(this + 0x68));
  }
  return;
}

/* address=00d0c770
   symbol=CQuest::caculateRewards */

/* CQuest::caculateRewards(CDataGroup*) */

void CQuest::caculateRewards(CDataGroup *param_1)

{
  return;
}

/* address=00d0c780
   symbol=CQuest::getDungeonMaxFloor */

/* CQuest::getDungeonMaxFloor() */

int __thiscall CQuest::getDungeonMaxFloor(CQuest *this)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  undefined8 *puVar4;
  long *plVar5;
  int iVar6;
  uint uVar7;
  ulong uVar8;
  ulong uVar9;
  uint uVar10;

  iVar6 = *(int *)(this + 0x20);
  if (*(int *)(this + 0x138) != 0) {
    uVar2 = *(uint *)(this + 0x13c);
    uVar9 = 0;
    do {
      uVar10 = (uint)uVar9;
      uVar8 = 0;
      while( true ) {
        uVar7 = (uint)uVar8;
        if (uVar10 < uVar2) {
          uVar1 = *(uint *)(*(long *)(uVar9 * 8 + *(long *)(this + 0x130)) + 8);
        }
        else {
          uVar1 = *(uint *)(**(long **)(this + 0x130) + 8);
        }
        if (uVar1 <= uVar7) break;
        if (uVar10 < uVar2) {
          plVar5 = (long *)(uVar9 * 8 + *(long *)(this + 0x130));
        }
        else {
          plVar5 = *(long **)(this + 0x130);
        }
        plVar5 = (long *)*plVar5;
        if (uVar7 < *(uint *)((long)plVar5 + 0xc)) {
          puVar4 = (undefined8 *)(uVar8 * 8 + *plVar5);
        }
        else {
          puVar4 = (undefined8 *)*plVar5;
        }
        iVar3 = CQuestUnitData::getDeepestFloor((CQuestUnitData *)*puVar4);
        if (iVar6 < iVar3) {
          iVar6 = iVar3;
        }
        uVar2 = *(uint *)(this + 0x13c);
        uVar8 = (ulong)(uVar7 + 1);
      }
      uVar9 = (ulong)(uVar10 + 1);
    } while (uVar10 + 1 < *(uint *)(this + 0x138));
  }
  if (*(int *)(this + 0x150) != 0) {
    uVar2 = *(uint *)(this + 0x154);
    uVar10 = 0;
    do {
      uVar9 = 0;
      while( true ) {
        uVar7 = (uint)uVar9;
        if (uVar10 < uVar2) {
          uVar1 = *(uint *)(*(long *)((ulong)uVar10 * 8 + *(long *)(this + 0x148)) + 8);
        }
        else {
          uVar1 = *(uint *)(**(long **)(this + 0x148) + 8);
        }
        if (uVar1 <= uVar7) break;
        if (uVar10 < uVar2) {
          plVar5 = (long *)((ulong)uVar10 * 8 + *(long *)(this + 0x148));
        }
        else {
          plVar5 = *(long **)(this + 0x148);
        }
        plVar5 = (long *)*plVar5;
        if (uVar7 < *(uint *)((long)plVar5 + 0xc)) {
          puVar4 = (undefined8 *)(uVar9 * 8 + *plVar5);
        }
        else {
          puVar4 = (undefined8 *)*plVar5;
        }
        iVar3 = CQuestUnitData::getDeepestFloor((CQuestUnitData *)*puVar4);
        if (iVar6 < iVar3) {
          iVar6 = iVar3;
        }
        uVar2 = *(uint *)(this + 0x154);
        uVar9 = (ulong)(uVar7 + 1);
      }
      uVar10 = uVar10 + 1;
    } while (uVar10 < *(uint *)(this + 0x150));
  }
  return iVar6;
}

/* address=00d0c910
   symbol=CQuest::getQuestHasRandomPieces */

/* CQuest::getQuestHasRandomPieces() */

undefined8 __thiscall CQuest::getQuestHasRandomPieces(CQuest *this)

{
  uint uVar1;
  char cVar2;
  uint uVar3;
  undefined8 *puVar4;
  long *plVar5;
  uint uVar6;
  ulong uVar7;
  uint uVar8;
  ulong uVar9;

  if (*(int *)(this + 0x138) != 0) {
    uVar3 = *(uint *)(this + 0x13c);
    uVar9 = 0;
    do {
      uVar8 = (uint)uVar9;
      uVar7 = 0;
      while( true ) {
        uVar6 = (uint)uVar7;
        if (uVar8 < uVar3) {
          uVar1 = *(uint *)(*(long *)(uVar9 * 8 + *(long *)(this + 0x130)) + 8);
        }
        else {
          uVar1 = *(uint *)(**(long **)(this + 0x130) + 8);
        }
        if (uVar1 <= uVar6) break;
        if (uVar8 < uVar3) {
          plVar5 = (long *)(uVar9 * 8 + *(long *)(this + 0x130));
        }
        else {
          plVar5 = *(long **)(this + 0x130);
        }
        plVar5 = (long *)*plVar5;
        if (uVar6 < *(uint *)((long)plVar5 + 0xc)) {
          cVar2 = CQuestUnitData::getIsRandom(*(CQuestUnitData **)(uVar7 * 8 + *plVar5));
        }
        else {
          cVar2 = CQuestUnitData::getIsRandom(*(CQuestUnitData **)*plVar5);
        }
        if (cVar2 != '\0') {
          return 1;
        }
        uVar3 = *(uint *)(this + 0x13c);
        uVar7 = (ulong)(uVar6 + 1);
      }
      uVar9 = (ulong)(uVar8 + 1);
    } while (uVar8 + 1 < *(uint *)(this + 0x138));
  }
  if (*(int *)(this + 0x150) != 0) {
    uVar3 = *(uint *)(this + 0x154);
    uVar8 = 0;
    do {
      uVar6 = 0;
      while( true ) {
        if (uVar8 < uVar3) {
          plVar5 = (long *)((ulong)uVar8 * 8 + *(long *)(this + 0x148));
        }
        else {
          plVar5 = *(long **)(this + 0x148);
        }
        if (*(uint *)(*plVar5 + 8) <= uVar6) break;
        if (uVar8 < uVar3) {
          plVar5 = (long *)((ulong)uVar8 * 8 + *(long *)(this + 0x148));
        }
        else {
          plVar5 = *(long **)(this + 0x148);
        }
        plVar5 = (long *)*plVar5;
        if (uVar6 < *(uint *)((long)plVar5 + 0xc)) {
          puVar4 = (undefined8 *)((ulong)uVar6 * 8 + *plVar5);
        }
        else {
          puVar4 = (undefined8 *)*plVar5;
        }
        cVar2 = CQuestUnitData::getIsRandom((CQuestUnitData *)*puVar4);
        if (cVar2 != '\0') {
          return 1;
        }
        uVar3 = *(uint *)(this + 0x154);
        uVar6 = uVar6 + 1;
      }
      uVar8 = uVar8 + 1;
    } while (uVar8 < *(uint *)(this + 0x150));
  }
  return 0;
}

/* address=00d0cab0
   symbol=CQuest::getQuestRewardFame */

/* CQuest::getQuestRewardFame() */

int __thiscall CQuest::getQuestRewardFame(CQuest *this)

{
  CQuestRewards *this_00;
  int iVar1;

  this_00 = *(CQuestRewards **)(this + 0x128);
  iVar1 = 0;
  if (this_00 != (CQuestRewards *)0x0) {
    CQuestRewards::calculateRewards(this_00);
    iVar1 = (int)*(float *)(this_00 + 0x20);
  }
  return iVar1;
}

/* address=00d0cae0
   symbol=CQuest::getQuestRewardXP */

/* CQuest::getQuestRewardXP() */

int __thiscall CQuest::getQuestRewardXP(CQuest *this)

{
  CQuestRewards *this_00;
  int iVar1;

  this_00 = *(CQuestRewards **)(this + 0x128);
  iVar1 = 0;
  if (this_00 != (CQuestRewards *)0x0) {
    CQuestRewards::calculateRewards(this_00);
    iVar1 = (int)*(float *)(this_00 + 0x18);
  }
  return iVar1;
}

/* address=00d0cb10
   symbol=CQuest::getQuestRewardGold */

/* CQuest::getQuestRewardGold() */

int __thiscall CQuest::getQuestRewardGold(CQuest *this)

{
  CQuestRewards *this_00;
  int iVar1;

  this_00 = *(CQuestRewards **)(this + 0x128);
  iVar1 = 0;
  if (this_00 != (CQuestRewards *)0x0) {
    CQuestRewards::calculateRewards(this_00);
    iVar1 = (int)*(float *)(this_00 + 0x1c);
  }
  return iVar1;
}

/* address=00d0cb40
   symbol=CQuest::getQuestRewardString */

/* CQuest::getQuestRewardString() */

void CQuest::getQuestRewardString(void)

{
  long in_RSI;
  wstring_conflict *in_RDI;

  if (*(long *)(in_RSI + 0x128) != 0) {
    CQuestRewards::getRewardString();
    return;
  }
  std::wstring::wstring(in_RDI,(wstring_conflict *)&::EMPTY_WSTRING);
  return;
}

/* address=00d0cb70
   symbol=CQuest::setQuestAccepted */

/* CQuest::setQuestAccepted(bool) */

void __thiscall CQuest::setQuestAccepted(CQuest *this,bool param_1)

{
  uint uVar1;
  ulong uVar2;

  if (this[0x26] != (CQuest)param_1) {
    this[0x26] = (CQuest)param_1;
    if (param_1) {
      CQuestManager::questEventUpdate(*(undefined8 *)(this + 0x1d0),3,0,0);
      return;
    }
    uVar1 = 0;
    if (*(int *)(this + 0x68) == 0) {
      return;
    }
    do {
      while (uVar1 < *(uint *)(this + 0x6c)) {
        uVar2 = (ulong)uVar1;
        uVar1 = uVar1 + 1;
        *(undefined1 *)(*(long *)(uVar2 * 8 + *(long *)(this + 0x60)) + 0x76) = 0;
        if (*(uint *)(this + 0x68) <= uVar1) {
          return;
        }
      }
      uVar1 = uVar1 + 1;
      *(undefined1 *)(**(long **)(this + 0x60) + 0x76) = 0;
    } while (uVar1 < *(uint *)(this + 0x68));
  }
  return;
}

/* address=00d0cbe0
   symbol=CQuest::setIsComplete */

/* CQuest::setIsComplete(bool) */

void __thiscall CQuest::setIsComplete(CQuest *this,bool param_1)

{
  if ((this[0x24] != (CQuest)param_1) && (this[0x24] = (CQuest)param_1, param_1)) {
    CQuestManager::questEventUpdate(*(undefined8 *)(this + 0x1d0),4,0,0);
    return;
  }
  return;
}

/* address=00d0cc10
   symbol=CQuest::isComplete */

/* CQuest::isComplete(bool) */

undefined8 __thiscall CQuest::isComplete(CQuest *this,bool param_1)

{
  uint uVar1;
  bool bVar2;
  char cVar3;
  uint uVar4;
  undefined8 *puVar5;
  ulong uVar6;
  long *plVar7;
  char *pcVar8;
  uint uVar9;
  ulong uVar10;
  long lVar11;
  uint uVar12;

  if ((!param_1) && (this[0x24] != (CQuest)0x0)) {
    return 1;
  }
  if (this[0x2a] == (CQuest)0x0) {
    if (*(int *)(this + 0x138) == 0) {
      bVar2 = false;
    }
    else {
      uVar4 = *(uint *)(this + 0x13c);
      uVar6 = 0;
      bVar2 = false;
      do {
        uVar12 = (uint)uVar6;
        uVar10 = 0;
        while( true ) {
          uVar9 = (uint)uVar10;
          if (uVar12 < uVar4) {
            uVar1 = *(uint *)(*(long *)(uVar6 * 8 + *(long *)(this + 0x130)) + 8);
          }
          else {
            uVar1 = *(uint *)(**(long **)(this + 0x130) + 8);
          }
          if (uVar1 <= uVar9) break;
          if (uVar12 < uVar4) {
            plVar7 = (long *)(uVar6 * 8 + *(long *)(this + 0x130));
          }
          else {
            plVar7 = *(long **)(this + 0x130);
          }
          plVar7 = (long *)*plVar7;
          if (uVar9 < *(uint *)((long)plVar7 + 0xc)) {
            puVar5 = (undefined8 *)(uVar10 * 8 + *plVar7);
          }
          else {
            puVar5 = (undefined8 *)*plVar7;
          }
          cVar3 = CQuestUnitData::isComplete((CQuestUnitData *)*puVar5,false);
          if (cVar3 == '\0') {
            return 0;
          }
          uVar4 = *(uint *)(this + 0x13c);
          uVar10 = (ulong)(uVar9 + 1);
          bVar2 = true;
        }
        uVar6 = (ulong)(uVar12 + 1);
      } while (uVar12 + 1 < *(uint *)(this + 0x138));
    }
    if (*(int *)(this + 0x150) != 0) {
      uVar4 = *(uint *)(this + 0x154);
      uVar12 = 0;
      do {
        uVar6 = 0;
        while( true ) {
          if (uVar12 < uVar4) {
            plVar7 = (long *)((ulong)uVar12 * 8 + *(long *)(this + 0x148));
          }
          else {
            plVar7 = *(long **)(this + 0x148);
          }
          uVar9 = (uint)uVar6;
          if (*(uint *)(*plVar7 + 8) <= uVar9) break;
          if (uVar12 < uVar4) {
            plVar7 = (long *)((ulong)uVar12 * 8 + *(long *)(this + 0x148));
          }
          else {
            plVar7 = *(long **)(this + 0x148);
          }
          plVar7 = (long *)*plVar7;
          if (uVar9 < *(uint *)((long)plVar7 + 0xc)) {
            puVar5 = (undefined8 *)(uVar6 * 8 + *plVar7);
          }
          else {
            puVar5 = (undefined8 *)*plVar7;
          }
          cVar3 = CQuestUnitData::isComplete((CQuestUnitData *)*puVar5,false);
          if (cVar3 == '\0') {
            return 0;
          }
          uVar4 = *(uint *)(this + 0x154);
          uVar6 = (ulong)(uVar9 + 1);
          bVar2 = true;
        }
        uVar12 = uVar12 + 1;
      } while (uVar12 < *(uint *)(this + 0x150));
    }
    lVar11 = 0;
    do {
      if (*(uint *)(this + lVar11 + 0x100) != 0) {
        uVar6 = 0;
        do {
          if ((uint)uVar6 < *(uint *)(this + lVar11 + 0x104)) {
            pcVar8 = (char *)(uVar6 + *(long *)(this + lVar11 + 0xf8));
          }
          else {
            pcVar8 = *(char **)(this + lVar11 + 0xf8);
          }
          if (*pcVar8 == '\0') {
            return 0;
          }
          uVar4 = (uint)uVar6 + 1;
          uVar6 = (ulong)uVar4;
        } while (uVar4 < *(uint *)(this + lVar11 + 0x100));
        bVar2 = true;
      }
      lVar11 = lVar11 + 0x18;
    } while (lVar11 != 0x30);
    if (bVar2) {
LAB_00d0ce6c:
      setIsComplete(this,true);
      return 1;
    }
    if (!param_1) {
      if (*(uint *)(this + 0x68) == 0) goto LAB_00d0ce6c;
      lVar11 = 0;
      uVar4 = 0;
      do {
        if (uVar4 < *(uint *)(this + 0x6c)) {
          plVar7 = (long *)(lVar11 + *(long *)(this + 0x60));
        }
        else {
          plVar7 = *(long **)(this + 0x60);
        }
        if (*(char *)(*plVar7 + 0x76) != '\0') goto LAB_00d0ce6c;
        uVar4 = uVar4 + 1;
        lVar11 = lVar11 + 8;
      } while (uVar4 < *(uint *)(this + 0x68));
    }
  }
  return 0;
}

/* address=00d0ce90
   symbol=CQuest::questEventUpdate */

/* CQuest::questEventUpdate(EQUEST_EVENTS, CBaseUnit*, CBaseUnit*) */

void __thiscall
CQuest::questEventUpdate(CQuest *this,undefined4 param_2,long param_3,CBaseUnit *param_4)

{
  uint uVar1;
  char cVar2;
  char *pcVar3;
  long *plVar4;
  undefined1 *puVar5;
  wstring_conflict *pwVar6;
  uint uVar7;
  ulong uVar8;
  uint uVar9;

  switch(param_2) {
  case 0:
    uVar9 = 0;
    if (*(int *)(this + 0x138) != 0) {
LAB_00d0d0a0:
      do {
        uVar8 = 0;
        while( true ) {
          uVar7 = (uint)uVar8;
          if (uVar9 < *(uint *)(this + 0x13c)) {
            uVar1 = *(uint *)(*(long *)((ulong)uVar9 * 8 + *(long *)(this + 0x130)) + 8);
          }
          else {
            uVar1 = *(uint *)(**(long **)(this + 0x130) + 8);
          }
          if (uVar1 <= uVar7) {
            uVar9 = uVar9 + 1;
            if (*(uint *)(this + 0x138) <= uVar9) goto LAB_00d0d126;
            goto LAB_00d0d0a0;
          }
          if (uVar9 < *(uint *)(this + 0x13c)) {
            plVar4 = (long *)((ulong)uVar9 * 8 + *(long *)(this + 0x130));
          }
          else {
            plVar4 = *(long **)(this + 0x130);
          }
          plVar4 = (long *)*plVar4;
          if (uVar7 < *(uint *)((long)plVar4 + 0xc)) {
            cVar2 = CQuestUnitData::unitPickedUp(*(CQuestUnitData **)(uVar8 * 8 + *plVar4),param_4);
          }
          else {
            cVar2 = CQuestUnitData::unitPickedUp(*(CQuestUnitData **)*plVar4,param_4);
          }
          if (cVar2 != '\0') break;
          uVar8 = (ulong)(uVar7 + 1);
        }
        uVar9 = uVar9 + 1;
        isComplete(this,false);
      } while (uVar9 < *(uint *)(this + 0x138));
    }
LAB_00d0d126:
    uVar9 = 0;
    if (*(int *)(this + 0x150) != 0) {
LAB_00d0d140:
      do {
        uVar8 = 0;
        while( true ) {
          uVar7 = (uint)uVar8;
          if (uVar9 < *(uint *)(this + 0x154)) {
            uVar1 = *(uint *)(*(long *)((ulong)uVar9 * 8 + *(long *)(this + 0x148)) + 8);
          }
          else {
            uVar1 = *(uint *)(**(long **)(this + 0x148) + 8);
          }
          if (uVar1 <= uVar7) {
            uVar9 = uVar9 + 1;
            if (*(uint *)(this + 0x150) <= uVar9) {
              return;
            }
            goto LAB_00d0d140;
          }
          if (uVar9 < *(uint *)(this + 0x154)) {
            plVar4 = (long *)((ulong)uVar9 * 8 + *(long *)(this + 0x148));
          }
          else {
            plVar4 = *(long **)(this + 0x148);
          }
          plVar4 = (long *)*plVar4;
          if (uVar7 < *(uint *)((long)plVar4 + 0xc)) {
            cVar2 = CQuestUnitData::unitPickedUp(*(CQuestUnitData **)(uVar8 * 8 + *plVar4),param_4);
          }
          else {
            cVar2 = CQuestUnitData::unitPickedUp(*(CQuestUnitData **)*plVar4,param_4);
          }
          if (cVar2 != '\0') break;
          uVar8 = (ulong)(uVar7 + 1);
        }
        uVar9 = uVar9 + 1;
        isComplete(this,false);
        if (*(uint *)(this + 0x150) <= uVar9) {
          return;
        }
      } while( true );
    }
    break;
  case 1:
    uVar9 = 0;
    if (*(int *)(this + 0x138) != 0) {
LAB_00d0d1e0:
      do {
        uVar8 = 0;
        while( true ) {
          uVar7 = (uint)uVar8;
          if (uVar9 < *(uint *)(this + 0x13c)) {
            uVar1 = *(uint *)(*(long *)((ulong)uVar9 * 8 + *(long *)(this + 0x130)) + 8);
          }
          else {
            uVar1 = *(uint *)(**(long **)(this + 0x130) + 8);
          }
          if (uVar1 <= uVar7) {
            uVar9 = uVar9 + 1;
            if (*(uint *)(this + 0x138) <= uVar9) goto LAB_00d0d266;
            goto LAB_00d0d1e0;
          }
          if (uVar9 < *(uint *)(this + 0x13c)) {
            plVar4 = (long *)((ulong)uVar9 * 8 + *(long *)(this + 0x130));
          }
          else {
            plVar4 = *(long **)(this + 0x130);
          }
          plVar4 = (long *)*plVar4;
          if (uVar7 < *(uint *)((long)plVar4 + 0xc)) {
            cVar2 = CQuestUnitData::unitDefeated(*(CQuestUnitData **)(uVar8 * 8 + *plVar4),param_4);
          }
          else {
            cVar2 = CQuestUnitData::unitDefeated(*(CQuestUnitData **)*plVar4,param_4);
          }
          if (cVar2 != '\0') break;
          uVar8 = (ulong)(uVar7 + 1);
        }
        uVar9 = uVar9 + 1;
        isComplete(this,false);
      } while (uVar9 < *(uint *)(this + 0x138));
    }
LAB_00d0d266:
    uVar9 = 0;
    if (*(int *)(this + 0x150) != 0) {
LAB_00d0d280:
      do {
        uVar7 = 0;
        while( true ) {
          if (uVar9 < *(uint *)(this + 0x154)) {
            uVar1 = *(uint *)(*(long *)((ulong)uVar9 * 8 + *(long *)(this + 0x148)) + 8);
          }
          else {
            uVar1 = *(uint *)(**(long **)(this + 0x148) + 8);
          }
          if (uVar1 <= uVar7) {
            uVar9 = uVar9 + 1;
            if (*(uint *)(this + 0x150) <= uVar9) {
              return;
            }
            goto LAB_00d0d280;
          }
          if (uVar9 < *(uint *)(this + 0x154)) {
            plVar4 = (long *)((ulong)uVar9 * 8 + *(long *)(this + 0x148));
          }
          else {
            plVar4 = *(long **)(this + 0x148);
          }
          plVar4 = (long *)*plVar4;
          if (uVar7 < *(uint *)((long)plVar4 + 0xc)) {
            cVar2 = CQuestUnitData::unitDefeated
                              (*(CQuestUnitData **)((ulong)uVar7 * 8 + *plVar4),param_4);
          }
          else {
            cVar2 = CQuestUnitData::unitDefeated(*(CQuestUnitData **)*plVar4,param_4);
          }
          if (cVar2 != '\0') break;
          uVar7 = uVar7 + 1;
        }
        uVar9 = uVar9 + 1;
        isComplete(this,false);
        if (*(uint *)(this + 0x150) <= uVar9) {
          return;
        }
      } while( true );
    }
    break;
  case 2:
    if (*(long *)(*(long *)(this + 0x1d0) + 0x10) == param_3) {
      uVar9 = 0;
      if (*(int *)(this + 0x138) != 0) {
        do {
          uVar8 = 0;
          while( true ) {
            uVar7 = (uint)uVar8;
            if (uVar9 < *(uint *)(this + 0x13c)) {
              uVar1 = *(uint *)(*(long *)((ulong)uVar9 * 8 + *(long *)(this + 0x130)) + 8);
            }
            else {
              uVar1 = *(uint *)(**(long **)(this + 0x130) + 8);
            }
            if (uVar1 <= uVar7) goto LAB_00d0d665;
            if (uVar9 < *(uint *)(this + 0x13c)) {
              plVar4 = (long *)((ulong)uVar9 * 8 + *(long *)(this + 0x130));
            }
            else {
              plVar4 = *(long **)(this + 0x130);
            }
            plVar4 = (long *)*plVar4;
            if (uVar7 < *(uint *)((long)plVar4 + 0xc)) {
              cVar2 = CQuestUnitData::unitInteracted
                                (*(CQuestUnitData **)(uVar8 * 8 + *plVar4),param_4);
            }
            else {
              cVar2 = CQuestUnitData::unitInteracted(*(CQuestUnitData **)*plVar4,param_4);
            }
            if (cVar2 != '\0') break;
            uVar8 = (ulong)(uVar7 + 1);
          }
          isComplete(this,false);
LAB_00d0d665:
          uVar9 = uVar9 + 1;
        } while (uVar9 < *(uint *)(this + 0x138));
      }
      uVar9 = 0;
      if (*(int *)(this + 0x150) != 0) {
LAB_00d0d690:
        do {
          uVar8 = 0;
          while( true ) {
            uVar7 = (uint)uVar8;
            if (uVar9 < *(uint *)(this + 0x154)) {
              uVar1 = *(uint *)(*(long *)((ulong)uVar9 * 8 + *(long *)(this + 0x148)) + 8);
            }
            else {
              uVar1 = *(uint *)(**(long **)(this + 0x148) + 8);
            }
            if (uVar1 <= uVar7) {
              uVar9 = uVar9 + 1;
              if (*(uint *)(this + 0x150) <= uVar9) {
                return;
              }
              goto LAB_00d0d690;
            }
            if (uVar9 < *(uint *)(this + 0x154)) {
              plVar4 = (long *)((ulong)uVar9 * 8 + *(long *)(this + 0x148));
            }
            else {
              plVar4 = *(long **)(this + 0x148);
            }
            plVar4 = (long *)*plVar4;
            if (uVar7 < *(uint *)((long)plVar4 + 0xc)) {
              cVar2 = CQuestUnitData::unitInteracted
                                (*(CQuestUnitData **)(uVar8 * 8 + *plVar4),param_4);
            }
            else {
              cVar2 = CQuestUnitData::unitInteracted(*(CQuestUnitData **)*plVar4,param_4);
            }
            if (cVar2 != '\0') break;
            uVar8 = (ulong)(uVar7 + 1);
          }
          uVar9 = uVar9 + 1;
          isComplete(this,false);
        } while (uVar9 < *(uint *)(this + 0x150));
      }
    }
    break;
  case 3:
    uVar9 = 0;
    if (*(int *)(this + 0xd0) != 0) {
      do {
        if (uVar9 < *(uint *)(this + 0x104)) {
          pcVar3 = (char *)((ulong)uVar9 + *(long *)(this + 0xf8));
        }
        else {
          pcVar3 = *(char **)(this + 0xf8);
        }
        if (*pcVar3 == '\0') {
          if (uVar9 < *(uint *)(this + 0xd4)) {
            pwVar6 = (wstring_conflict *)((ulong)uVar9 * 8 + *(long *)(this + 200));
          }
          else {
            pwVar6 = *(wstring_conflict **)(this + 200);
          }
          cVar2 = CQuestManager::getQuestIsActive(*(CQuestManager **)(this + 0x1d0),pwVar6);
          if (cVar2 != '\0') {
            if (uVar9 < *(uint *)(this + 0x104)) {
              puVar5 = (undefined1 *)((ulong)uVar9 + *(long *)(this + 0xf8));
            }
            else {
              puVar5 = *(undefined1 **)(this + 0xf8);
            }
            *puVar5 = 1;
          }
        }
        uVar9 = uVar9 + 1;
      } while (uVar9 < *(uint *)(this + 0xd0));
    }
    goto LAB_00d0d5c8;
  case 4:
    uVar9 = 0;
    if (*(int *)(this + 0xe8) != 0) {
      do {
        if (uVar9 < *(uint *)(this + 0x11c)) {
          pcVar3 = (char *)((ulong)uVar9 + *(long *)(this + 0x110));
        }
        else {
          pcVar3 = *(char **)(this + 0x110);
        }
        if (*pcVar3 == '\0') {
          if (uVar9 < *(uint *)(this + 0xec)) {
            pwVar6 = (wstring_conflict *)((ulong)uVar9 * 8 + *(long *)(this + 0xe0));
          }
          else {
            pwVar6 = *(wstring_conflict **)(this + 0xe0);
          }
          cVar2 = CQuestManager::getQuestComplete(*(CQuestManager **)(this + 0x1d0),pwVar6);
          if (cVar2 != '\0') {
            if (uVar9 < *(uint *)(this + 0x11c)) {
              puVar5 = (undefined1 *)((ulong)uVar9 + *(long *)(this + 0x110));
            }
            else {
              puVar5 = *(undefined1 **)(this + 0x110);
            }
            *puVar5 = 1;
          }
        }
        uVar9 = uVar9 + 1;
      } while (uVar9 < *(uint *)(this + 0xe8));
    }
LAB_00d0d5c8:
    isComplete(this,false);
    return;
  case 5:
    uVar9 = 0;
    if (*(int *)(this + 0x138) != 0) {
LAB_00d0cf60:
      do {
        uVar8 = 0;
        while( true ) {
          uVar7 = (uint)uVar8;
          if (uVar9 < *(uint *)(this + 0x13c)) {
            uVar1 = *(uint *)(*(long *)((ulong)uVar9 * 8 + *(long *)(this + 0x130)) + 8);
          }
          else {
            uVar1 = *(uint *)(**(long **)(this + 0x130) + 8);
          }
          if (uVar1 <= uVar7) {
            uVar9 = uVar9 + 1;
            if (*(uint *)(this + 0x138) <= uVar9) goto LAB_00d0cfe6;
            goto LAB_00d0cf60;
          }
          if (uVar9 < *(uint *)(this + 0x13c)) {
            plVar4 = (long *)((ulong)uVar9 * 8 + *(long *)(this + 0x130));
          }
          else {
            plVar4 = *(long **)(this + 0x130);
          }
          plVar4 = (long *)*plVar4;
          if (uVar7 < *(uint *)((long)plVar4 + 0xc)) {
            cVar2 = CQuestUnitData::unitDropped(*(CQuestUnitData **)(uVar8 * 8 + *plVar4),param_4);
          }
          else {
            cVar2 = CQuestUnitData::unitDropped(*(CQuestUnitData **)*plVar4,param_4);
          }
          if (cVar2 != '\0') break;
          uVar8 = (ulong)(uVar7 + 1);
        }
        uVar9 = uVar9 + 1;
        this[0x24] = (CQuest)0x0;
      } while (uVar9 < *(uint *)(this + 0x138));
    }
LAB_00d0cfe6:
    uVar9 = 0;
    if (*(int *)(this + 0x150) != 0) {
LAB_00d0d000:
      do {
        uVar8 = 0;
        while( true ) {
          uVar7 = (uint)uVar8;
          if (uVar9 < *(uint *)(this + 0x154)) {
            uVar1 = *(uint *)(*(long *)((ulong)uVar9 * 8 + *(long *)(this + 0x148)) + 8);
          }
          else {
            uVar1 = *(uint *)(**(long **)(this + 0x148) + 8);
          }
          if (uVar1 <= uVar7) {
            uVar9 = uVar9 + 1;
            if (*(uint *)(this + 0x150) <= uVar9) {
              return;
            }
            goto LAB_00d0d000;
          }
          if (uVar9 < *(uint *)(this + 0x154)) {
            plVar4 = (long *)((ulong)uVar9 * 8 + *(long *)(this + 0x148));
          }
          else {
            plVar4 = *(long **)(this + 0x148);
          }
          plVar4 = (long *)*plVar4;
          if (uVar7 < *(uint *)((long)plVar4 + 0xc)) {
            cVar2 = CQuestUnitData::unitDropped(*(CQuestUnitData **)(uVar8 * 8 + *plVar4),param_4);
          }
          else {
            cVar2 = CQuestUnitData::unitDropped(*(CQuestUnitData **)*plVar4,param_4);
          }
          if (cVar2 != '\0') break;
          uVar8 = (ulong)(uVar7 + 1);
        }
        uVar9 = uVar9 + 1;
        this[0x24] = (CQuest)0x0;
        if (*(uint *)(this + 0x150) <= uVar9) {
          return;
        }
      } while( true );
    }
  }
  return;
}

/* address=00d0d7b0
   symbol=CQuest::cleanUpDialog */

/* CQuest::cleanUpDialog(TArrayList<CQuestDialog*>&) */

void __thiscall CQuest::cleanUpDialog(CQuest *this,TArrayList *param_1)

{
  ulong uVar1;
  uint uVar2;

  if (*(int *)(param_1 + 8) != 0) {
    uVar2 = 0;
    do {
      while (uVar2 < *(uint *)(param_1 + 0xc)) {
        uVar1 = (ulong)uVar2;
        uVar2 = uVar2 + 1;
        CQuestDialog::cleanUp(*(CQuestDialog **)(uVar1 * 8 + *(long *)param_1));
        if (*(uint *)(param_1 + 8) <= uVar2) {
          return;
        }
      }
      uVar2 = uVar2 + 1;
      CQuestDialog::cleanUp((CQuestDialog *)**(undefined8 **)param_1);
    } while (uVar2 < *(uint *)(param_1 + 8));
  }
  return;
}

/* address=00d0d810
   symbol=CQuest::destroyIcons */

/* CQuest::destroyIcons() */

void __thiscall CQuest::destroyIcons(CQuest *this)

{
  if (*(CQuestRewards **)(this + 0x128) != (CQuestRewards *)0x0) {
    CQuestRewards::destroyIcons(*(CQuestRewards **)(this + 0x128));
    return;
  }
  return;
}

/* address=00d14500
   symbol=CQuest::_GLOBAL__I_CQuest */

/* CQuest::CQuest(CResourceManager*, CQuestManager*) */

void CQuest::_GLOBAL__I_CQuest(void)

{
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
  std::wstring::wstring((wstring_conflict *)::gQUEST_TYPE_NAMES,L"",&aStack_292);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 8),L"FIND",&aStack_291);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x10),L"KILL NUM",&aStack_290);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_TYPE_NAMES + 0x18),L"KILL BOSS",&aStack_28f);
  __cxa_atexit(::__tcf_0,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gQUEST_DIALOG_TYPE_NAMES,L"ERROR",&aStack_28e);
  std::wstring::wstring((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 8),L"INTRO",&aStack_28d);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x10),L"RETURN",&aStack_28c);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x18),L"COMPLETE",&aStack_28b);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x20),L"PASSIVE",&aStack_28a);
  std::wstring::wstring
            ((wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x28),L"DETAILS",&aStack_289);
  __cxa_atexit(::__tcf_1,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)&::g_QUEST_COMPLETE_TYPE_NAMES,L"COMPLETE_ON_QUEST_ACCEPT",
             &aStack_288);
  std::wstring::wstring((wstring_conflict *)&DAT_014fa058,L"COMPLETE_ON_QUEST_COMPLETE",&aStack_287)
  ;
  __cxa_atexit(::__tcf_2,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&g_QUEST_TAG_DIALOG_ITEM_NAMES,L"GIVEITEM",&aStack_286);
  std::wstring::wstring((wstring_conflict *)&DAT_014fa068,L"TAKEITEM",&aStack_285);
  __cxa_atexit(::__tcf_3,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)gQUEST_REQUIREMENTS,L"QUESTSCOMPLETE",&aStack_284);
  std::wstring::wstring
            ((wstring_conflict *)(gQUEST_REQUIREMENTS + 8),L"QUESTSNOTCOMPLETE",&aStack_283);
  std::wstring::wstring
            ((wstring_conflict *)(gQUEST_REQUIREMENTS + 0x10),L"QUESTSACTIVE",&aStack_282);
  __cxa_atexit(::__tcf_4,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)g_QUESTUNIT_SPAWNCLASS_PREDEFINE_NAMES,L"",&aStack_281);
  std::wstring::wstring
            ((wstring_conflict *)(g_QUESTUNIT_SPAWNCLASS_PREDEFINE_NAMES + 8),
             L"LEVEL_QUEST_MONSTERS",&aStack_280);
  std::wstring::wstring
            ((wstring_conflict *)(g_QUESTUNIT_SPAWNCLASS_PREDEFINE_NAMES + 0x10),
             L"LEVEL_QUEST_CHAMPIONS",&aStack_27f);
  std::wstring::wstring
            ((wstring_conflict *)(g_QUESTUNIT_SPAWNCLASS_PREDEFINE_NAMES + 0x18),
             L"LEVEL_QUEST_ITEMS",&aStack_27e);
  __cxa_atexit(::__tcf_5,0,&__dso_handle);
  ParticleUniverse::HALFSCALE._4_4_ = DAT_0142463c * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._0_4_ = Ogre::Vector3::UNIT_SCALE * DAT_00fa4810;
  ParticleUniverse::HALFSCALE._8_4_ = DAT_00fa4810 * DAT_01424640;
  std::string::string((string *)&ParticleUniverse::ALIAS,"1",&aStack_27d);
  __cxa_atexit(std::string::~string,&ParticleUniverse::ALIAS,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::SYSTEM,"2",&aStack_27c);
  __cxa_atexit(std::string::~string,&ParticleUniverse::SYSTEM,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::TECHNIQUE,"3",&aStack_27b);
  __cxa_atexit(std::string::~string,&ParticleUniverse::TECHNIQUE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::RENDERER,"4",&aStack_27a);
  __cxa_atexit(std::string::~string,&ParticleUniverse::RENDERER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EMITTER,"5",&aStack_279);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EMITTER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::AFFECTOR,"6",&aStack_278);
  __cxa_atexit(std::string::~string,&ParticleUniverse::AFFECTOR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::OBSERVER,"7",&aStack_277);
  __cxa_atexit(std::string::~string,&ParticleUniverse::OBSERVER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::HANDLER,"8",&aStack_276);
  __cxa_atexit(std::string::~string,&ParticleUniverse::HANDLER,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::BEHAVIOUR,"9",&aStack_275);
  __cxa_atexit(std::string::~string,&ParticleUniverse::BEHAVIOUR,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::EXTERN,"10",&aStack_274);
  __cxa_atexit(std::string::~string,&ParticleUniverse::EXTERN,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DYNAMIC_ATTRIBUTE,"11",&aStack_273);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DYNAMIC_ATTRIBUTE,&__dso_handle);
  std::string::string((string *)&ParticleUniverse::DEPENDENCY,"12",&aStack_272);
  __cxa_atexit(std::string::~string,&ParticleUniverse::DEPENDENCY,&__dso_handle);
  std::string::string((string *)::KLayoutFunctionNames,"GUIEXITGAME",&aStack_271);
  std::string::string((string *)(::KLayoutFunctionNames + 8),"GUIEXITAPPLICATION",&aStack_270);
  std::string::string((string *)(::KLayoutFunctionNames + 0x10),"GUINEWGAME",&aStack_26f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x18),"GUICONTINUEGAME",&aStack_26e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x20),"GUINEWGAMEMENU",&aStack_26d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x28),"GUICONTINUEGAMEMENU",&aStack_26c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x30),"GUICLOSEMENU",&aStack_26b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x38),"GUIBACK",&aStack_26a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x40),"GUIDECLINE",&aStack_269);
  std::string::string((string *)(::KLayoutFunctionNames + 0x48),"GUIACCEPT",&aStack_268);
  std::string::string((string *)(::KLayoutFunctionNames + 0x50),"GUIOK",&aStack_267);
  std::string::string((string *)(::KLayoutFunctionNames + 0x58),"GUIPAUSE",&aStack_266);
  std::string::string((string *)(::KLayoutFunctionNames + 0x60),"GUISCROLLUP",&aStack_265);
  std::string::string((string *)(::KLayoutFunctionNames + 0x68),"GUISCROLLDOWN",&aStack_264);
  std::string::string((string *)(::KLayoutFunctionNames + 0x70),"GUISELECT1",&aStack_263);
  std::string::string((string *)(::KLayoutFunctionNames + 0x78),"GUISELECT2",&aStack_262);
  std::string::string((string *)(::KLayoutFunctionNames + 0x80),"GUISELECT3",&aStack_261);
  std::string::string((string *)(::KLayoutFunctionNames + 0x88),"GUISELECT4",&aStack_260);
  std::string::string((string *)(::KLayoutFunctionNames + 0x90),"GUISELECT5",&aStack_25f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x98),"GUISELECT6",&aStack_25e);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa0),"GUISELECT7",&aStack_25d);
  std::string::string((string *)(::KLayoutFunctionNames + 0xa8),"GUISELECT8",&aStack_25c);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb0),"GUISELECT9",&aStack_25b);
  std::string::string((string *)(::KLayoutFunctionNames + 0xb8),"GUISELECT10",&aStack_25a);
  std::string::string((string *)(::KLayoutFunctionNames + 0xc0),"GUISELECT11",&aStack_259);
  std::string::string((string *)(::KLayoutFunctionNames + 200),"GUISELECT12",&aStack_258);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd0),"GUISELECT13",&aStack_257);
  std::string::string((string *)(::KLayoutFunctionNames + 0xd8),"GUISELECT14",&aStack_256);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe0),"GUISELECT15",&aStack_255);
  std::string::string((string *)(::KLayoutFunctionNames + 0xe8),"GUISELECT16",&aStack_254);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf0),"GUISELECT17",&aStack_253);
  std::string::string((string *)(::KLayoutFunctionNames + 0xf8),"GUISELECT18",&aStack_252);
  std::string::string((string *)(::KLayoutFunctionNames + 0x100),"GUISELECT19",&aStack_251);
  std::string::string((string *)(::KLayoutFunctionNames + 0x108),"GUISELECT20",&aStack_250);
  std::string::string((string *)(::KLayoutFunctionNames + 0x110),"GUISELECT21",&aStack_24f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x118),"GUISELECT22",&aStack_24e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x120),"GUISELECT23",&aStack_24d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x128),"GUISELECT24",&aStack_24c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x130),"GUISELECT25",&aStack_24b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x138),"GUISELECT26",&aStack_24a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x140),"GUISELECT27",&aStack_249);
  std::string::string((string *)(::KLayoutFunctionNames + 0x148),"GUISELECT28",&aStack_248);
  std::string::string((string *)(::KLayoutFunctionNames + 0x150),"GUISELECT29",&aStack_247);
  std::string::string((string *)(::KLayoutFunctionNames + 0x158),"GUISELECT30",&aStack_246);
  std::string::string((string *)(::KLayoutFunctionNames + 0x160),"GUISELECT31",&aStack_245);
  std::string::string((string *)(::KLayoutFunctionNames + 0x168),"GUISELECT32",&aStack_244);
  std::string::string((string *)(::KLayoutFunctionNames + 0x170),"GUISELECT33",&aStack_243);
  std::string::string((string *)(::KLayoutFunctionNames + 0x178),"GUISELECT34",&aStack_242);
  std::string::string((string *)(::KLayoutFunctionNames + 0x180),"GUISELECT35",&aStack_241);
  std::string::string((string *)(::KLayoutFunctionNames + 0x188),"GUISELECT36",&aStack_240);
  std::string::string((string *)(::KLayoutFunctionNames + 400),"GUISELECT37",&aStack_23f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x198),"GUISELECT38",&aStack_23e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a0),"GUISELECT39",&aStack_23d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1a8),"GUISELECT40",&aStack_23c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b0),"GUISELECT41",&aStack_23b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1b8),"GUISELECT42",&aStack_23a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c0),"GUISELECT43",&aStack_239);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1c8),"GUISELECT44",&aStack_238);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d0),"GUISELECT45",&aStack_237);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1d8),"GUISELECT46",&aStack_236);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e0),"GUISELECT47",&aStack_235);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1e8),"GUISELECT48",&aStack_234);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f0),"GUISELECT49",&aStack_233);
  std::string::string((string *)(::KLayoutFunctionNames + 0x1f8),"GUISELECT50",&aStack_232);
  std::string::string((string *)(::KLayoutFunctionNames + 0x200),"GUISELECTA",&aStack_231);
  std::string::string((string *)(::KLayoutFunctionNames + 0x208),"GUISELECTB",&aStack_230);
  std::string::string((string *)(::KLayoutFunctionNames + 0x210),"GUISELECTC",&aStack_22f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x218),"GUISELECTD",&aStack_22e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x220),"GUIFEEDPET",&aStack_22d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x228),"GUIPETPASSIVE",&aStack_22c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x230),"GUIPETAGGRESSIVE",&aStack_22b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x238),"GUIPETDEFENSIVE",&aStack_22a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x240),"GUITOGGLEINVENTORY",&aStack_229);
  std::string::string((string *)(::KLayoutFunctionNames + 0x248),"GUITOGGLEQUESTS",&aStack_228);
  std::string::string((string *)(::KLayoutFunctionNames + 0x250),"GUITOGGLESTATS",&aStack_227);
  std::string::string((string *)(::KLayoutFunctionNames + 600),"GUITOGGLESKILLS",&aStack_226);
  std::string::string((string *)(::KLayoutFunctionNames + 0x260),"GUITOGGLEPERKS",&aStack_225);
  std::string::string((string *)(::KLayoutFunctionNames + 0x268),"GUITOGGLEJOURNAL",&aStack_224);
  std::string::string((string *)(::KLayoutFunctionNames + 0x270),"GUITOGGLEPET",&aStack_223);
  std::string::string((string *)(::KLayoutFunctionNames + 0x278),"GUITOGGLEAUTOMAP",&aStack_222);
  std::string::string((string *)(::KLayoutFunctionNames + 0x280),"GUITOGGLEOPTIONS",&aStack_221);
  std::string::string((string *)(::KLayoutFunctionNames + 0x288),"GUITOGGLEITEMNAMES",&aStack_220);
  std::string::string((string *)(::KLayoutFunctionNames + 0x290),"GUIAUTOMAPZOOMIN",&aStack_21f);
  std::string::string((string *)(::KLayoutFunctionNames + 0x298),"GUIAUTOMAPZOOMOUT",&aStack_21e);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a0),"GUILEVELUP",&aStack_21d);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2a8),"GUISTATSUP",&aStack_21c);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b0),"GUISKILLUP",&aStack_21b);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2b8),"GUIPET1",&aStack_21a);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c0),"GUIPET2",&aStack_219);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2c8),"GUIPET3",&aStack_218);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d0),"GUIDELETE1",&aStack_217);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2d8),"GUIDELETE2",&aStack_216);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e0),"GUIDELETE3",&aStack_215);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2e8),"GUIDELETE4",&aStack_214);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f0),"GUISETTINGSMENU",&aStack_213);
  std::string::string((string *)(::KLayoutFunctionNames + 0x2f8),"GUIPETSELL",&aStack_212);
  std::string::string((string *)(::KLayoutFunctionNames + 0x300),"NONE",&aStack_211);
  __cxa_atexit(::__tcf_6,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSOUNDBANK_STRINGS,L"STEP_SOUND",&aStack_210);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 8),L"STRIKE_SOUND",&aStack_20f);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x10),L"PHYSICALHIT_SOUND",&aStack_20e);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x18),L"ICEHIT_SOUND",&aStack_20d);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x20),L"FIREHIT_SOUND",&aStack_20c);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x28),L"ELECTRICHIT_SOUND",&aStack_20b);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x30),L"POISONHIT_SOUND",&aStack_20a);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x38),L"SHIELDBLOCK",&aStack_209);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x40),L"BLOCK",&aStack_208);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x48),L"CRITICAL_SOUND",&aStack_207);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x50),L"ATTACK_SOUND",&aStack_206);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x58),L"IDLE_SOUND",&aStack_205)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x60),L"DEATH_SOUND",&aStack_204);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x68),L"ROAR_SOUND",&aStack_203)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x70),L"FLEE_SOUND",&aStack_202)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x78),L"MISS_SOUND",&aStack_201)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x80),L"FALL_SOUND",&aStack_200)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x88),L"LAND_SOUND",&aStack_1ff)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x90),L"TAKE_SOUND",&aStack_1fe)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x98),L"SPAWN_SOUND",&aStack_1fd);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa0),L"USE_SOUND",&aStack_1fc);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xa8),L"EQUIP_SOUND",&aStack_1fb);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb0),L"OPENMENU_SOUND",&aStack_1fa);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xb8),L"BUY_SOUND",&aStack_1f9);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xc0),L"ERROR_SOUND",&aStack_1f8);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 200),L"LEVELUP_SOUND",&aStack_1f7);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd0),L"EFFORT_SOUND",&aStack_1f6);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xd8),L"SPENDPOINT_SOUND",&aStack_1f5);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe0),L"PORTALENTER_SOUND",&aStack_1f4);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xe8),L"POERTALEXIT_SOUND",&aStack_1f3);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf0),L"SKILLASSIGN_SOUND",&aStack_1f2);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0xf8),L"QUESTRECEIVED_SOUND",&aStack_1f1);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x100),L"QUESTCOMPLETED_SOUND",&aStack_1f0)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x108),L"LOWMANA_SOUND",&aStack_1ef);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x110),L"MISSILEREFLECT_SOUND",&aStack_1ee)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x118),L"BADEFFECT_SOUND",&aStack_1ed);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x120),L"GOODEFFECT_SOUND",&aStack_1ec);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x128),L"NPCDIALOG_SOUND",&aStack_1eb);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x130),L"NPCGREET",&aStack_1ea);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x138),L"NPCBYE",&aStack_1e9);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x140),L"NPCPURCHASE",&aStack_1e8);
  std::wstring::wstring((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x148),L"NPCSELL",&aStack_1e7);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x150),L"VOICEPETINVENTORYFULL_SOUND",
             &aStack_1e6);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x158),L"VOICEPETDEPARTED_SOUND",
             &aStack_1e5);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x160),L"VOICEPETRETURNED_SOUND",
             &aStack_1e4);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x168),L"VOICEPETFLED_SOUND",&aStack_1e3);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x170),L"VOICEPETLEVELUP_SOUND",&aStack_1e2
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x178),L"VOICEINVENTORYFULL_SOUND",
             &aStack_1e1);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x180),L"VOICEINSUFFICIENTGOLD_SOUND",
             &aStack_1e0);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x188),L"VOICEIMPOSSIBLE_SOUND",&aStack_1df
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 400),L"VOICECANTCAST_SOUND",&aStack_1de);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x198),L"VOICECANTCASTHERE_SOUND",
             &aStack_1dd);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a0),L"VOICEHEALTHLOW_SOUND",&aStack_1dc)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1a8),L"VOICEMANALOW_SOUND",&aStack_1db);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b0),L"VOICETRAPSPRUNG_SOUND",&aStack_1da
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1b8),L"VOICEREFRESHED_SOUND",&aStack_1d9)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c0),L"VOICEPOWERFUL_SOUND",&aStack_1d8);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1c8),L"VOICEHEALTHY_SOUND",&aStack_1d7);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d0),L"VOICEILL_SOUND",&aStack_1d6);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1d8),L"VOICEPOISONED_SOUND",&aStack_1d5);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e0),L"VOICELEVELUP_SOUND",&aStack_1d4);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1e8),L"VOICEFAMEUP_SOUND",&aStack_1d3);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f0),L"VOICESKILLUP_SOUND",&aStack_1d2);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x1f8),L"VOICEFORTUNEGOOD_SOUND",
             &aStack_1d1);
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x200),L"VOICEFORTUNEBAD_SOUND",&aStack_1d0
            );
  std::wstring::wstring
            ((wstring_conflict *)(::KSOUNDBANK_STRINGS + 0x208),L"VOICESPELLLEARNED_SOUND",
             &aStack_1cf);
  ::KSOUNDBANK_STRINGS._528_8_ = &DAT_01424558;
  __cxa_atexit(::__tcf_7,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KALIGNMENT_STRINGS,L"NEUTRAL",&aStack_1ce);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 8),L"GOOD",&aStack_1cd);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x10),L"EVIL",&aStack_1cc);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x18),L"ALL",&aStack_1cb);
  std::wstring::wstring((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x20),L"BERSERK",&aStack_1ca);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x28),L"EVILBERSERK",&aStack_1c9);
  std::wstring::wstring
            ((wstring_conflict *)(::KALIGNMENT_STRINGS + 0x30),L"GOODBERSERK",&aStack_1c8);
  __cxa_atexit(::__tcf_8,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KAITYPE_STRINGS,L"NORMAL",&aStack_1c7);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 8),L"RANGEDDEFENDER",&aStack_1c6);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x10),L"DEFENDER",&aStack_1c5);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x18),L"RANGEDCASTER",&aStack_1c4);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x20),L"CIRCLER",&aStack_1c3);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x28),L"RESURRECTER",&aStack_1c2);
  std::wstring::wstring((wstring_conflict *)(::KAITYPE_STRINGS + 0x30),L"DUMMY",&aStack_1c1);
  __cxa_atexit(::__tcf_9,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gDAMAGE_TYPES,L"Physical",&aStack_1c0);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 8),L"Magical",&aStack_1bf);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x10),L"Fire",&aStack_1be);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x18),L"Ice",&aStack_1bd);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x20),L"Electric",&aStack_1bc);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x28),L"Poison",&aStack_1bb);
  std::wstring::wstring((wstring_conflict *)(::gDAMAGE_TYPES + 0x30),L"All",&aStack_1ba);
  __cxa_atexit(::__tcf_10,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::gTARGET_TYPES,L"USER",&aStack_1b9);
  std::wstring::wstring((wstring_conflict *)&DAT_014fa748,L"ITEM",&aStack_1b8);
  __cxa_atexit(::__tcf_11,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KSFXTypeName,L"STATIONARYTARGET",&aStack_1b7);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 8),L"STATIONARYOWNER",&aStack_1b6);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x10),L"STATIONARY",&aStack_1b5);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x18),L"STATIONARYPORTAL",&aStack_1b4)
  ;
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x20),L"BEAM",&aStack_1b3);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x28),L"FOLLOWOWNER",&aStack_1b2);
  std::wstring::wstring((wstring_conflict *)(::KSFXTypeName + 0x30),L"FOLLOWTARGET",&aStack_1b1);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x38),L"PROJECTILELOCATION",&aStack_1b0);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x40),L"PROJECTILECHARACTER",&aStack_1af);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x48),L"PROJECTILELOCATIONERRATIC",&aStack_1ae);
  std::wstring::wstring
            ((wstring_conflict *)(::KSFXTypeName + 0x50),L"PROJECTILECHARACTERERRATIC",&aStack_1ad);
  __cxa_atexit(::__tcf_12,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KCharacterNames,L"NA",&aStack_1ac);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 8),L"NA",&aStack_1ab);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x10),L"NA",&aStack_1aa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x18),L"NA",&aStack_1a9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x20),L"NA",&aStack_1a8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x28),L"NA",&aStack_1a7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x30),L"NA",&aStack_1a6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x38),L"NA",&aStack_1a5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x40),L"Bksp",&aStack_1a4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x48),L"Tab",&aStack_1a3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x50),L"NA",&aStack_1a2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x58),L"NA",&aStack_1a1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x60),L"Ctr",&aStack_1a0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x68),L"Ret",&aStack_19f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x70),L"NA",&aStack_19e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x78),L"NA",&aStack_19d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x80),L"Shift",&aStack_19c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x88),L"Ctrl",&aStack_19b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x90),L"Alt",&aStack_19a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x98),L"Tab",&aStack_199);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa0),L"NA",&aStack_198);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xa8),L"NA",&aStack_197);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb0),L"NA",&aStack_196);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xb8),L"NA",&aStack_195);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xc0),L"NA",&aStack_194);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 200),L"NA",&aStack_193);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd0),L"NA",&aStack_192);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xd8),L"NA",&aStack_191);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe0),L"NA",&aStack_190);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xe8),L"NA",&aStack_18f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf0),L"NA",&aStack_18e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0xf8),L"NA",&aStack_18d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x100),L"space",&aStack_18c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x108),L"pgup",&aStack_18b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x110),L"pgdn",&aStack_18a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x118),L"end",&aStack_189);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x120),L"home",&aStack_188);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x128),L"left arrow",&aStack_187);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x130),L"up arrow",&aStack_186);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x138),L"right arrow",&aStack_185);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x140),L"down arrow",&aStack_184);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x148),L")",&aStack_183);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x150),L"*",&aStack_182);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x158),L"+",&aStack_181);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x160),L",",&aStack_180);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x168),L"ins",&aStack_17f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x170),L"del",&aStack_17e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x178),L"/",&aStack_17d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x180),L"0",&aStack_17c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x188),L"1",&aStack_17b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 400),L"2",&aStack_17a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x198),L"3",&aStack_179);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a0),L"4",&aStack_178);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1a8),L"5",&aStack_177);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b0),L"6",&aStack_176);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1b8),L"7",&aStack_175);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c0),L"8",&aStack_174);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1c8),L"9",&aStack_173);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d0),L":",&aStack_172);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1d8),L";",&aStack_171);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e0),L"<",&aStack_170);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1e8),L"=",&aStack_16f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f0),L">",&aStack_16e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x1f8),L"?",&aStack_16d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x200),L"@",&aStack_16c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x208),L"a",&aStack_16b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x210),L"b",&aStack_16a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x218),L"c",&aStack_169);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x220),L"d",&aStack_168);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x228),L"e",&aStack_167);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x230),L"NA",&aStack_166);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x238),L"g",&aStack_165);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x240),L"h",&aStack_164);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x248),L"i",&aStack_163);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x250),L"j",&aStack_162);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 600),L"k",&aStack_161);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x260),L"l",&aStack_160);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x268),L"m",&aStack_15f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x270),L"n",&aStack_15e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x278),L"o",&aStack_15d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x280),L"p",&aStack_15c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x288),L"NA",&aStack_15b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x290),L"r",&aStack_15a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x298),L"s",&aStack_159);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a0),L"t",&aStack_158);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2a8),L"u",&aStack_157);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b0),L"v",&aStack_156);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2b8),L"w",&aStack_155);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c0),L"x",&aStack_154);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2c8),L"y",&aStack_153);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d0),L"z",&aStack_152);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2d8),L"[",&aStack_151);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e0),L"\\",&aStack_150);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2e8),L"]",&aStack_14f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f0),L"^",&aStack_14e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x2f8),L"_",&aStack_14d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x300),L"NUM 0",&aStack_14c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x308),L"NUM 1",&aStack_14b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x310),L"NUM 2",&aStack_14a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x318),L"NUM 3",&aStack_149);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 800),L"NUM 4",&aStack_148);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x328),L"NUM 5",&aStack_147);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x330),L"NUM 6",&aStack_146);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x338),L"NUM 7",&aStack_145);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x340),L"NUM 8",&aStack_144);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x348),L"NUM 9",&aStack_143);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x350),L"*",&aStack_142);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x358),L"+",&aStack_141);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x360),L"NA",&aStack_140);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x368),L"-",&aStack_13f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x370),L"NA",&aStack_13e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x378),L"F1",&aStack_13d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x380),L"F2",&aStack_13c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x388),L"F3",&aStack_13b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x390),L"F4",&aStack_13a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x398),L"F5",&aStack_139);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a0),L"F6",&aStack_138);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3a8),L"F7",&aStack_137);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b0),L"F8",&aStack_136);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3b8),L"F9",&aStack_135);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c0),L"F10",&aStack_134);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3c8),L"F11",&aStack_133);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d0),L"F12",&aStack_132);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3d8),L"{",&aStack_131);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3e0),L"|",&aStack_130);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 1000),L"}",&aStack_12f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f0),L"~",&aStack_12e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x3f8),L";",&aStack_12d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x400),L"=",&aStack_12c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x408),L".",&aStack_12b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x410),L"-",&aStack_12a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x418),L",",&aStack_129);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x420),L"/",&aStack_128);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x428),L"`",&aStack_127);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x430),L"[",&aStack_126);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x438),L"\\",&aStack_125);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x440),L"]",&aStack_124);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x448),L"\'",&aStack_123);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x450),L"NA",&aStack_122);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x458),L"NA",&aStack_121);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x460),L"NA",&aStack_120);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x468),L"NA",&aStack_11f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x470),L"NA",&aStack_11e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x478),L"NA",&aStack_11d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x480),L"NA",&aStack_11c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x488),L"NA",&aStack_11b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x490),L"NA",&aStack_11a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x498),L"NA",&aStack_119);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a0),L"NA",&aStack_118);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4a8),L"NA",&aStack_117);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b0),L"NA",&aStack_116);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4b8),L"NA",&aStack_115);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c0),L"NA",&aStack_114);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4c8),L"NA",&aStack_113);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d0),L"NA",&aStack_112);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4d8),L"NA",&aStack_111);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e0),L"NA",&aStack_110);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4e8),L"NA",&aStack_10f);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f0),L"NA",&aStack_10e);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x4f8),L"NA",&aStack_10d);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x500),L"NA",&aStack_10c);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x508),L"NA",&aStack_10b);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x510),L"NA",&aStack_10a);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x518),L"NA",&aStack_109);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x520),L"NA",&aStack_108);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x528),L"NA",&aStack_107);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x530),L"NA",&aStack_106);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x538),L"NA",&aStack_105);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x540),L"NA",&aStack_104);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x548),L"NA",&aStack_103);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x550),L"NA",&aStack_102);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x558),L"NA",&aStack_101);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x560),L"NA",&aStack_100);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x568),L"NA",&aStack_ff);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x570),L"NA",&aStack_fe);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x578),L"NA",&aStack_fd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x580),L"NA",&aStack_fc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x588),L"NA",&aStack_fb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x590),L"NA",&aStack_fa);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x598),L"NA",&aStack_f9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a0),L"NA",&aStack_f8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5a8),L"NA",&aStack_f7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b0),L"NA",&aStack_f6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5b8),L"NA",&aStack_f5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c0),L"NA",&aStack_f4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5c8),L"NA",&aStack_f3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d0),L";",&aStack_f2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5d8),L"=",&aStack_f1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e0),L",",&aStack_f0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5e8),L"-",&aStack_ef);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f0),L".",&aStack_ee);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x5f8),L"/",&aStack_ed);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x600),L"`",&aStack_ec);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x608),L"NA",&aStack_eb);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x610),L"NA",&aStack_ea);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x618),L"NA",&aStack_e9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x620),L"NA",&aStack_e8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x628),L"NA",&aStack_e7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x630),L"NA",&aStack_e6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x638),L"NA",&aStack_e5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x640),L"NA",&aStack_e4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x648),L"NA",&aStack_e3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x650),L"NA",&aStack_e2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x658),L"NA",&aStack_e1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x660),L"NA",&aStack_e0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x668),L"NA",&aStack_df);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x670),L"NA",&aStack_de);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x678),L"NA",&aStack_dd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x680),L"NA",&aStack_dc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x688),L"NA",&aStack_db);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x690),L"NA",&aStack_da);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x698),L"NA",&aStack_d9);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a0),L"NA",&aStack_d8);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6a8),L"NA",&aStack_d7);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b0),L"NA",&aStack_d6);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6b8),L"NA",&aStack_d5);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c0),L"NA",&aStack_d4);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6c8),L"NA",&aStack_d3);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d0),L"NA",&aStack_d2);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6d8),L"[",&aStack_d1);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e0),L"\\",&aStack_d0);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6e8),L"]",&aStack_cf);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f0),L"\'",&aStack_ce);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x6f8),L"NA",&aStack_cd);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x700),L"NA",&aStack_cc);
  std::wstring::wstring((wstring_conflict *)(::KCharacterNames + 0x708),L"NA",&aStack_cb);
  __cxa_atexit(::__tcf_13,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEffect_Activation_Names,L"PASSIVE",&aStack_ca);
  std::wstring::wstring((wstring_conflict *)(::gEffect_Activation_Names + 8),L"DYNAMIC",&aStack_c9);
  std::wstring::wstring
            ((wstring_conflict *)(::gEffect_Activation_Names + 0x10),L"TRANSFER",&aStack_c8);
  __cxa_atexit(::__tcf_14,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::gEFFECT_STAT_MODIFIER_NAMES,L"MELEE",&aStack_c7);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 8),L"RANGED",&aStack_c6);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x10),L"DEFENSE",&aStack_c5);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x18),L"MAGIC",&aStack_c4);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x20),L"LEVEL",&aStack_c3);
  std::wstring::wstring
            ((wstring_conflict *)(::gEFFECT_STAT_MODIFIER_NAMES + 0x28),L"OWNERLEVEL",&aStack_c2);
  __cxa_atexit(::__tcf_15,0,&__dso_handle);
  std::string::string((string *)::gEFFECT_STAT_MODIFIER_ICON_NAMES,"iconmelee",&aStack_c1);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 8),"iconranged",&aStack_c0);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x10),"icondefense",&aStack_bf
                     );
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x18),"iconmagic",&aStack_be);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x20),"iconmagic",&aStack_bd);
  std::string::string((string *)(::gEFFECT_STAT_MODIFIER_ICON_NAMES + 0x28),"iconmagic",&aStack_bc);
  __cxa_atexit(::__tcf_16,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES,"tag_righthand",&aStack_bb);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 8),"tag_lefthand",&aStack_ba);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x10),"",&aStack_b9);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x18),"Bip01 Head",&aStack_b8);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x20),"",&aStack_b7);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x28),"Bip01 L Clavicle",&aStack_b6);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x30),"",&aStack_b5);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x38),"",&aStack_b4);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x40),"",&aStack_b3);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x48),"",&aStack_b2);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x50),"",&aStack_b1);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES + 0x58),"tag_leftarm",&aStack_b0);
  __cxa_atexit(::__tcf_17,0,&__dso_handle);
  std::string::string((string *)::KEQUIP_LOCATION_BONES_SECONDARY,"",&aStack_af);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 8),"",&aStack_ae);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x10),"",&aStack_ad);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x18),"",&aStack_ac);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x20),"",&aStack_ab);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x28),"Bip01 R Clavicle",
                      &aStack_aa);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x30),"",&aStack_a9);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x38),"",&aStack_a8);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x40),"",&aStack_a7);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x48),"",&aStack_a6);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x50),"",&aStack_a5);
  std::string::string((string *)(::KEQUIP_LOCATION_BONES_SECONDARY + 0x58),"",&aStack_a4);
  __cxa_atexit(::__tcf_18,0,&__dso_handle);
  std::string::string((string *)::KEquipmentIconName,"EquipLeftHand",&aStack_a3);
  std::string::string((string *)(::KEquipmentIconName + 8),"EquipRightHand",&aStack_a2);
  std::string::string((string *)(::KEquipmentIconName + 0x10),"EquipGloves",&aStack_a1);
  std::string::string((string *)(::KEquipmentIconName + 0x18),"EquipHelm",&aStack_a0);
  std::string::string((string *)(::KEquipmentIconName + 0x20),"EquipChest",&aStack_9f);
  std::string::string((string *)(::KEquipmentIconName + 0x28),"EquipShoulder",&aStack_9e);
  std::string::string((string *)(::KEquipmentIconName + 0x30),"EquipBoots",&aStack_9d);
  std::string::string((string *)(::KEquipmentIconName + 0x38),"EquipBelt",&aStack_9c);
  std::string::string((string *)(::KEquipmentIconName + 0x40),"EquipRing1",&aStack_9b);
  std::string::string((string *)(::KEquipmentIconName + 0x48),"EquipRing2",&aStack_9a);
  std::string::string((string *)(::KEquipmentIconName + 0x50),"EquipAmulet",&aStack_99);
  std::string::string((string *)(::KEquipmentIconName + 0x58),"",&aStack_98);
  __cxa_atexit(::__tcf_19,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames,L"CHEST",&aStack_97);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 8),L"GLOVES",&aStack_96);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x10),L"BOOTS",&aStack_95);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x18),L"HELMET",&aStack_94);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames + 0x20),L"SHOULDERS",&aStack_93);
  __cxa_atexit(::__tcf_20,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KWardrobeSlotNames2,L"",&aStack_92);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 8),L"",&aStack_91);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x10),L"",&aStack_90);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x18),L"FACE",&aStack_8f);
  std::wstring::wstring((wstring_conflict *)(::KWardrobeSlotNames2 + 0x20),L"",&aStack_8e);
  __cxa_atexit(::__tcf_21,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)::KContextTipNames,L"TIP_INVENTORY",&aStack_8d);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 8),L"TIP_UNIDENTIFIED",&aStack_8c)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x10),L"TIP_INVENTORYFULL",&aStack_8b);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x18),L"TIP_HEALTHLOW",&aStack_8a)
  ;
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x20),L"TIP_MANALOW",&aStack_89);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x28),L"TIP_MERCHANT",&aStack_88);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x30),L"TIP_LEVELUP",&aStack_87);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x38),L"TIP_STATS",&aStack_86);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x40),L"TIP_SPELL",&aStack_85);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x48),L"TIP_WELCOME",&aStack_84);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x50),L"TIP_SOCKETABLE",&aStack_83);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x58),L"TIP_PETFLEE",&aStack_82);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x60),L"TIP_GAMBLE",&aStack_81);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x68),L"TIP_ENCHANT",&aStack_80);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x70),L"TIP_TRANSMUTE",&aStack_7f)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x78),L"TIP_PETINVENTORY",&aStack_7e);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0x80),L"TIP_PETINVENTORYFULL",&aStack_7d);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x88),L"TIP_STASH",&aStack_7c);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x90),L"TIP_FISHING",&aStack_7b);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x98),L"TIP_SPELLFIND",&aStack_7a)
  ;
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xa0),L"TIP_QUESTCOMPLETE",&aStack_79);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xa8),L"TIP_SHAREDSTASH",&aStack_78);
  std::wstring::wstring
            ((wstring_conflict *)(::KContextTipNames + 0xb0),L"TIP_HOWTOATTACK",&aStack_77);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xb8),L"TIP_TEMP5",&aStack_76);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xc0),L"TIP_TEMP6",&aStack_75);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 200),L"TIP_TEMP7",&aStack_74);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xd0),L"TIP_TEMP8",&aStack_73);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xd8),L"TIP_TEMP9",&aStack_72);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xe0),L"TIP_TEMP10",&aStack_71);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xe8),L"TIP_TEMP11",&aStack_70);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xf0),L"TIP_TEMP12",&aStack_6f);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0xf8),L"TIP_TEMP13",&aStack_6e);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x100),L"TIP_TEMP14",&aStack_6d);
  std::wstring::wstring((wstring_conflict *)(::KContextTipNames + 0x108),L"TIP_TEMP15",&aStack_6c);
  __cxa_atexit(::__tcf_22,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::g_LEVELLAYOUT_CREATION_NAMES,L"MONSTERSPAWNCLASS",&aStack_6b);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 8),L"CHAMPIONSPAWNCLASS",
             &aStack_6a);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x10),L"PROPSPAWNCLASS",
             &aStack_69);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x18),L"NPCSPAWNCLASS",&aStack_68
            );
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x20),L"CREEPSPAWNCLASS",
             &aStack_67);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x28),L"GOLD",&aStack_66);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x30),L"FISHSPAWNCLASS",
             &aStack_65);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x38),L"FORMATIONS",&aStack_64);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x40),L"QUESTMONSTERSPAWNCLASS",
             &aStack_63);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x48),L"QUESTITEMSPAWNCLASS",
             &aStack_62);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_NAMES + 0x50),L"QUESTCHAMPIONSPAWNCLASS",
             &aStack_61);
  __cxa_atexit(::__tcf_23,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES,
             L"MONSTERSPAWNCLASSRANDOMIZED",&aStack_60);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 8),
             L"CHAMPIONSPAWNCLASSRANDOMIZED",&aStack_5f);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x10),
             L"PROPSPAWNCLASSRANDOMIZED",&aStack_5e);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x18),
             L"NPCSPAWNCLASSRANDOMIZED",&aStack_5d);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x20),
             L"CREEPSPAWNCLASSRANDOMIZED",&aStack_5c);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x28),
             L"GOLDRANDOMIZED",&aStack_5b);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x30),
             L"FISHSPAWNCLASSRANDOMIZED",&aStack_5a);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x38),
             L"FORMATIONSRANDOMIZED",&aStack_59);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x40),
             L"QUESTMONSTERSPAWNCLASSRANDOMIZED",&aStack_58);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x48),
             L"QUESTITEMSPAWNCLASSRANDOMIZED",&aStack_57);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_RANDOMIZED_NAMES + 0x50),
             L"QUESTCHAMPIONSPAWNCLASSRANDOMIZED",&aStack_56);
  __cxa_atexit(::__tcf_24,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::g_LEVELLAYOUT_CREATION_PATHNODES,L"MONSTERS_PER_METER_MIN",
             &aStack_55);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 8),L"MONSTERS_PER_METER_MAX",
             &aStack_54);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x10),
             L"CHAMPIONS_PER_METER_MIN",&aStack_53);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x18),
             L"CHAMPIONS_PER_METER_MAX",&aStack_52);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x20),L"PROPS_PER_METER_MIN",
             &aStack_51);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x28),L"PROPS_PER_METER_MAX",
             &aStack_50);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x30),L"NPCS_PER_METER_MIN",
             &aStack_4f);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x38),L"NPCS_PER_METER_MAX",
             &aStack_4e);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x40),L"CREEPS_PER_METER_MIN"
             ,&aStack_4d);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x48),L"CREEPS_PER_METER_MAX"
             ,&aStack_4c);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x50),L"GOLD_PER_METER_MIN",
             &aStack_4b);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x58),L"GOLD_PER_METER_MAX",
             &aStack_4a);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x60),L"FISH_PER_METER_MIN",
             &aStack_49);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x68),L"FISH_PER_METER_MAX",
             &aStack_48);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x70),
             L"FORMATIONS_PER_METER_MIN",&aStack_47);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x78),
             L"FORMATIONS_PER_METER_MAX",&aStack_46);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x80),L"",&aStack_45);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x88),L"",&aStack_44);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x90),L"",&aStack_43);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0x98),L"",&aStack_42);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0xa0),L"",&aStack_41);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_PATHNODES + 0xa8),L"",&aStack_40);
  __cxa_atexit(::__tcf_25,0,&__dso_handle);
  std::wstring::wstring
            ((wstring_conflict *)::g_LEVELLAYOUT_CREATION_COUNTS,L"MONSTER_MIN",&aStack_3f);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 8),L"MONSTER_MAX",&aStack_3e);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x10),L"CHAMPIONS_MIN",
             &aStack_3d);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x18),L"CHAMPIONS_MAX",
             &aStack_3c);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x20),L"PROPS_MIN",&aStack_3b);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x28),L"PPROPS_MAX",&aStack_3a);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x30),L"NPCS_MIN",&aStack_39);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x38),L"NPCS_MAX",&aStack_38);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x40),L"CREEPS_MIN",&aStack_37);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x48),L"CREEPS_MAX",&aStack_36);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x50),L"GOLD_MIN",&aStack_35);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x58),L"GOLD_MAX",&aStack_34);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x60),L"FISH_MIN",&aStack_33);
  std::wstring::wstring
            ((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x68),L"FISH_MAX",&aStack_32);
  std::wstring::wstring((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x70),L"",&aStack_31)
  ;
  std::wstring::wstring((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x78),L"",&aStack_30)
  ;
  std::wstring::wstring((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x80),L"",&aStack_2f)
  ;
  std::wstring::wstring((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x88),L"",&aStack_2e)
  ;
  std::wstring::wstring((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x90),L"",&aStack_2d)
  ;
  std::wstring::wstring((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0x98),L"",&aStack_2c)
  ;
  std::wstring::wstring((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0xa0),L"",&aStack_2b)
  ;
  std::wstring::wstring((wstring_conflict *)(::g_LEVELLAYOUT_CREATION_COUNTS + 0xa8),L"",&aStack_2a)
  ;
  __cxa_atexit(::__tcf_26,0,&__dso_handle);
  std::wstring::wstring((wstring_conflict *)&::m_gFileVersionExtension,L".svt",aaStack_29);
  __cxa_atexit(std::wstring::~wstring,&::m_gFileVersionExtension,&__dso_handle);
  return;
}

/* address=00d14510
   symbol=CQuest::populate */

/* CQuest::populate(CLevel*) */

void __thiscall CQuest::populate(CQuest *this,CLevel *param_1)

{
  uint uVar1;
  undefined8 *puVar2;
  long *plVar3;
  uint uVar4;
  uint uVar5;
  ulong uVar6;
  ulong uVar7;
  uint uVar8;

  if (param_1 != (CLevel *)0x0) {
    if (*(int *)(this + 0x138) != 0) {
      uVar5 = *(uint *)(this + 0x13c);
      uVar7 = 0;
      do {
        uVar8 = (uint)uVar7;
        uVar6 = 0;
        while( true ) {
          uVar4 = (uint)uVar6;
          if (uVar8 < uVar5) {
            uVar1 = *(uint *)(*(long *)(uVar7 * 8 + *(long *)(this + 0x130)) + 8);
          }
          else {
            uVar1 = *(uint *)(**(long **)(this + 0x130) + 8);
          }
          if (uVar1 <= uVar4) break;
          if (uVar8 < uVar5) {
            plVar3 = (long *)(uVar7 * 8 + *(long *)(this + 0x130));
          }
          else {
            plVar3 = *(long **)(this + 0x130);
          }
          plVar3 = (long *)*plVar3;
          if (uVar4 < *(uint *)((long)plVar3 + 0xc)) {
            puVar2 = (undefined8 *)(uVar6 * 8 + *plVar3);
          }
          else {
            puVar2 = (undefined8 *)*plVar3;
          }
          uVar6 = (ulong)(uVar4 + 1);
          CQuestUnitData::populate((CQuestUnitData *)*puVar2,param_1);
          uVar5 = *(uint *)(this + 0x13c);
        }
        uVar7 = (ulong)(uVar8 + 1);
      } while (uVar8 + 1 < *(uint *)(this + 0x138));
    }
    if (*(int *)(this + 0x150) != 0) {
      uVar5 = *(uint *)(this + 0x154);
      uVar7 = 0;
      do {
        uVar8 = (uint)uVar7;
        uVar6 = 0;
        while( true ) {
          uVar4 = (uint)uVar6;
          if (uVar8 < uVar5) {
            uVar1 = *(uint *)(*(long *)(uVar7 * 8 + *(long *)(this + 0x148)) + 8);
          }
          else {
            uVar1 = *(uint *)(**(long **)(this + 0x148) + 8);
          }
          if (uVar1 <= uVar4) break;
          if (uVar8 < uVar5) {
            plVar3 = (long *)(uVar7 * 8 + *(long *)(this + 0x148));
          }
          else {
            plVar3 = *(long **)(this + 0x148);
          }
          plVar3 = (long *)*plVar3;
          if (uVar4 < *(uint *)((long)plVar3 + 0xc)) {
            puVar2 = (undefined8 *)(uVar6 * 8 + *plVar3);
          }
          else {
            puVar2 = (undefined8 *)*plVar3;
          }
          uVar6 = (ulong)(uVar4 + 1);
          CQuestUnitData::populate((CQuestUnitData *)*puVar2,param_1);
          uVar5 = *(uint *)(this + 0x154);
        }
        uVar7 = (ulong)(uVar8 + 1);
      } while (uVar8 + 1 < *(uint *)(this + 0x150));
    }
    if (*(int *)(this + 0x168) != 0) {
      uVar5 = *(uint *)(this + 0x16c);
      uVar8 = 0;
      do {
        uVar7 = 0;
        while( true ) {
          uVar4 = (uint)uVar7;
          if (uVar8 < uVar5) {
            uVar1 = *(uint *)(*(long *)((ulong)uVar8 * 8 + *(long *)(this + 0x160)) + 8);
          }
          else {
            uVar1 = *(uint *)(**(long **)(this + 0x160) + 8);
          }
          if (uVar1 <= uVar4) break;
          if (uVar8 < uVar5) {
            plVar3 = (long *)((ulong)uVar8 * 8 + *(long *)(this + 0x160));
          }
          else {
            plVar3 = *(long **)(this + 0x160);
          }
          plVar3 = (long *)*plVar3;
          if (uVar4 < *(uint *)((long)plVar3 + 0xc)) {
            puVar2 = (undefined8 *)(uVar7 * 8 + *plVar3);
          }
          else {
            puVar2 = (undefined8 *)*plVar3;
          }
          uVar7 = (ulong)(uVar4 + 1);
          CQuestUnitData::populate((CQuestUnitData *)*puVar2,param_1);
          uVar5 = *(uint *)(this + 0x16c);
        }
        uVar8 = uVar8 + 1;
      } while (uVar8 < *(uint *)(this + 0x168));
    }
    if (*(int *)(this + 0x68) != 0) {
      uVar7 = 0;
      do {
        if ((uint)uVar7 < *(uint *)(this + 0x6c)) {
          puVar2 = (undefined8 *)(uVar7 * 8 + *(long *)(this + 0x60));
        }
        else {
          puVar2 = *(undefined8 **)(this + 0x60);
        }
        uVar5 = (uint)uVar7 + 1;
        uVar7 = (ulong)uVar5;
        CQuestDialog::populate((CQuestDialog *)*puVar2);
      } while (uVar5 < *(uint *)(this + 0x68));
    }
    if (*(int *)(this + 0x80) != 0) {
      uVar7 = 0;
      do {
        if ((uint)uVar7 < *(uint *)(this + 0x84)) {
          puVar2 = (undefined8 *)(uVar7 * 8 + *(long *)(this + 0x78));
        }
        else {
          puVar2 = *(undefined8 **)(this + 0x78);
        }
        uVar5 = (uint)uVar7 + 1;
        uVar7 = (ulong)uVar5;
        CQuestDialog::populate((CQuestDialog *)*puVar2);
      } while (uVar5 < *(uint *)(this + 0x80));
    }
    if (*(int *)(this + 0x98) != 0) {
      uVar7 = 0;
      do {
        if ((uint)uVar7 < *(uint *)(this + 0x9c)) {
          puVar2 = (undefined8 *)(uVar7 * 8 + *(long *)(this + 0x90));
        }
        else {
          puVar2 = *(undefined8 **)(this + 0x90);
        }
        uVar5 = (uint)uVar7 + 1;
        uVar7 = (ulong)uVar5;
        CQuestDialog::populate((CQuestDialog *)*puVar2);
      } while (uVar5 < *(uint *)(this + 0x98));
    }
    if (*(int *)(this + 0xb0) != 0) {
      uVar5 = 0;
      do {
        if (uVar5 < *(uint *)(this + 0xb4)) {
          puVar2 = (undefined8 *)((ulong)uVar5 * 8 + *(long *)(this + 0xa8));
        }
        else {
          puVar2 = *(undefined8 **)(this + 0xa8);
        }
        uVar5 = uVar5 + 1;
        CQuestDialog::populate((CQuestDialog *)*puVar2);
      } while (uVar5 < *(uint *)(this + 0xb0));
    }
    this[0x2d] = (CQuest)0x1;
  }
  return;
}

/* address=00d14860
   symbol=CQuest::addQuestControllerListerner */

/* CQuest::addQuestControllerListerner(CQuestController*) */

void __thiscall CQuest::addQuestControllerListerner(CQuest *this,CQuestController *param_1)

{
  CQuestController *pCVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined8 *puVar4;
  TSafePointer *pTVar5;
  void *pvVar6;
  long *plVar7;
  ulong uVar8;
  uint uVar9;

  if (*(int *)(this + 0x1b8) != 0) {
    uVar9 = 0;
    do {
      uVar3 = *(uint *)(this + 0x1bc);
      if (uVar9 < uVar3) {
        pCVar1 = (CQuestController *)**(long **)((ulong)uVar9 * 8 + *(long *)(this + 0x1b0));
      }
      else {
        pCVar1 = *(CQuestController **)**(undefined8 **)(this + 0x1b0);
      }
      if (param_1 == pCVar1) {
        return;
      }
      if (uVar9 < uVar3) {
        if (**(long **)((ulong)uVar9 * 8 + *(long *)(this + 0x1b0)) == 0) goto LAB_00d14906;
LAB_00d148ab:
        uVar3 = *(uint *)(this + 0x1b8);
      }
      else {
        if (*(long *)**(undefined8 **)(this + 0x1b0) != 0) goto LAB_00d148ab;
LAB_00d14906:
        if (uVar9 < uVar3) {
          plVar7 = (long *)((ulong)uVar9 * 8 + *(long *)(this + 0x1b0));
        }
        else {
          plVar7 = *(long **)(this + 0x1b0);
        }
        if (*plVar7 != 0) {
          if (uVar9 < uVar3) {
            puVar4 = (undefined8 *)((ulong)uVar9 * 8 + *(long *)(this + 0x1b0));
          }
          else {
            puVar4 = *(undefined8 **)(this + 0x1b0);
          }
          pTVar5 = (TSafePointer *)*puVar4;
          if (pTVar5 != (TSafePointer *)0x0) {
            if (*(CRunicCore **)pTVar5 != (CRunicCore *)0x0) {
                    /* try { // try from 00d14942 to 00d14946 has its CatchHandler @ 00d14b1c */
              CRunicCore::removeSafePointer(*(CRunicCore **)pTVar5,pTVar5,*(uint *)(pTVar5 + 8));
            }
            *(undefined8 *)pTVar5 = 0;
            *(undefined4 *)(pTVar5 + 8) = 0xffffffff;
            Ogre::NedAllocImpl::deallocBytes(pTVar5);
            uVar3 = *(uint *)(this + 0x1bc);
          }
          if (uVar9 < uVar3) {
            puVar4 = (undefined8 *)((ulong)uVar9 * 8 + *(long *)(this + 0x1b0));
          }
          else {
            puVar4 = *(undefined8 **)(this + 0x1b0);
          }
          *puVar4 = 0;
        }
        uVar3 = *(uint *)(this + 0x1b8);
        if (uVar9 < uVar3) {
          *(uint *)(this + 0x1b8) = uVar3 - 1;
          *(undefined8 *)(*(long *)(this + 0x1b0) + (ulong)uVar9 * 8) =
               *(undefined8 *)(*(long *)(this + 0x1b0) + (ulong)(uVar3 - 1) * 8);
          goto LAB_00d148ab;
        }
      }
      uVar9 = uVar9 + 1;
    } while (uVar9 < uVar3);
  }
  pTVar5 = (TSafePointer *)Ogre::NedAllocImpl::allocBytes(0x10,(char *)0x0,0,(char *)0x0);
  *(undefined8 *)pTVar5 = 0;
  *(undefined4 *)(pTVar5 + 8) = 0xffffffff;
  if (param_1 != (CQuestController *)0x0) {
                    /* try { // try from 00d14a24 to 00d14a28 has its CatchHandler @ 00d14b09 */
    uVar2 = CRunicCore::addSafePointer((CRunicCore *)param_1,pTVar5);
    *(undefined4 *)(pTVar5 + 8) = uVar2;
    *(CQuestController **)pTVar5 = param_1;
  }
  uVar9 = *(uint *)(this + 0x1b8);
  if (uVar9 < *(uint *)(this + 0x1bc)) {
    pvVar6 = *(void **)(this + 0x1b0);
  }
  else if (*(long *)(this + 0x1b0) == 0) {
    *(uint *)(this + 0x1bc) = *(uint *)(this + 0x1c0);
    pvVar6 = operator_new__((ulong)*(uint *)(this + 0x1c0) << 3);
    *(void **)(this + 0x1b0) = pvVar6;
    uVar9 = *(uint *)(this + 0x1b8);
  }
  else {
    uVar9 = *(uint *)(this + 0x1bc) + *(int *)(this + 0x1c0);
    pvVar6 = operator_new__((ulong)uVar9 << 3);
    if (*(int *)(this + 0x1bc) != 0) {
      uVar3 = 0;
      do {
        uVar8 = (ulong)uVar3;
        uVar3 = uVar3 + 1;
        *(undefined8 *)((long)pvVar6 + uVar8 * 8) =
             *(undefined8 *)(*(long *)(this + 0x1b0) + uVar8 * 8);
      } while (uVar3 < *(uint *)(this + 0x1bc));
    }
    if (*(void **)(this + 0x1b0) != (void *)0x0) {
      operator_delete__(*(void **)(this + 0x1b0));
    }
    *(void **)(this + 0x1b0) = pvVar6;
    *(uint *)(this + 0x1bc) = uVar9;
    uVar9 = *(uint *)(this + 0x1b8);
  }
  *(TSafePointer **)((long)pvVar6 + (ulong)uVar9 * 8) = pTVar5;
  *(int *)(this + 0x1b8) = *(int *)(this + 0x1b8) + 1;
  return;
}

/* address=00d14b30
   symbol=CQuest::removeQuestControllerListerner */

/* CQuest::removeQuestControllerListerner(CQuestController*) */

void __thiscall CQuest::removeQuestControllerListerner(CQuest *this,CQuestController *param_1)

{
  TSafePointer *pTVar1;
  uint uVar2;
  long *plVar3;
  long *plVar4;
  uint uVar5;
  ulong uVar6;

  if (*(int *)(this + 0x1b8) != 0) {
    uVar6 = 0;
    do {
      while( true ) {
        uVar2 = *(uint *)(this + 0x1bc);
        uVar5 = (uint)uVar6;
        if (uVar2 <= uVar5) break;
        plVar3 = *(long **)(this + 0x1b0);
        if (param_1 != *(CQuestController **)plVar3[uVar6]) goto LAB_00d14b6a;
LAB_00d14bb4:
        plVar4 = plVar3;
        if (uVar5 < uVar2) {
          plVar4 = plVar3 + uVar6;
        }
        if (*plVar4 != 0) {
          plVar4 = plVar3;
          if (uVar5 < uVar2) {
            plVar4 = plVar3 + uVar6;
          }
          pTVar1 = (TSafePointer *)*plVar4;
          if (pTVar1 != (TSafePointer *)0x0) {
            if (*(CRunicCore **)pTVar1 != (CRunicCore *)0x0) {
                    /* try { // try from 00d14bec to 00d14bf0 has its CatchHandler @ 00d14cfb */
              CRunicCore::removeSafePointer(*(CRunicCore **)pTVar1,pTVar1,*(uint *)(pTVar1 + 8));
            }
            *(undefined8 *)pTVar1 = 0;
            *(undefined4 *)(pTVar1 + 8) = 0xffffffff;
            Ogre::NedAllocImpl::deallocBytes(pTVar1);
            uVar2 = *(uint *)(this + 0x1bc);
            plVar3 = *(long **)(this + 0x1b0);
          }
          if (uVar5 < uVar2) {
            plVar3 = plVar3 + uVar6;
          }
          *plVar3 = 0;
        }
        uVar2 = *(uint *)(this + 0x1b8);
        if (uVar5 < uVar2) {
LAB_00d14c35:
          *(uint *)(this + 0x1b8) = uVar2 - 1;
          *(undefined8 *)(*(long *)(this + 0x1b0) + uVar6 * 8) =
               *(undefined8 *)(*(long *)(this + 0x1b0) + (ulong)(uVar2 - 1) * 8);
LAB_00d14b84:
          uVar2 = *(uint *)(this + 0x1b8);
        }
        uVar6 = (ulong)(uVar5 + 1);
        if (uVar2 <= uVar5 + 1) {
          return;
        }
      }
      plVar3 = *(long **)(this + 0x1b0);
      if (param_1 == *(CQuestController **)*plVar3) goto LAB_00d14bb4;
LAB_00d14b6a:
      plVar4 = plVar3;
      if (uVar5 < uVar2) {
        plVar4 = plVar3 + uVar6;
      }
      if (*(long *)*plVar4 != 0) goto LAB_00d14b84;
      plVar4 = plVar3;
      if (uVar5 < uVar2) {
        plVar4 = plVar3 + uVar6;
      }
      if (*plVar4 != 0) {
        plVar4 = plVar3;
        if (uVar5 < uVar2) {
          plVar4 = plVar3 + uVar6;
        }
        pTVar1 = (TSafePointer *)*plVar4;
        if (pTVar1 != (TSafePointer *)0x0) {
          if (*(CRunicCore **)pTVar1 != (CRunicCore *)0x0) {
                    /* try { // try from 00d14c98 to 00d14c9c has its CatchHandler @ 00d14d03 */
            CRunicCore::removeSafePointer(*(CRunicCore **)pTVar1,pTVar1,*(uint *)(pTVar1 + 8));
          }
          *(undefined8 *)pTVar1 = 0;
          *(undefined4 *)(pTVar1 + 8) = 0xffffffff;
          Ogre::NedAllocImpl::deallocBytes(pTVar1);
          uVar2 = *(uint *)(this + 0x1bc);
          plVar3 = *(long **)(this + 0x1b0);
        }
        if (uVar5 < uVar2) {
          plVar3 = plVar3 + uVar6;
        }
        *plVar3 = 0;
      }
      uVar2 = *(uint *)(this + 0x1b8);
      if (uVar5 < uVar2) goto LAB_00d14c35;
      uVar6 = (ulong)(uVar5 + 1);
    } while (uVar5 + 1 < uVar2);
  }
  return;
}

/* address=00d14f60
   symbol=CQuest::getQuestDialog */

/* CQuest::getQuestDialog(CBaseUnit*) */

undefined8 __thiscall CQuest::getQuestDialog(CQuest *this,CBaseUnit *param_1)

{
  char cVar1;
  undefined8 *puVar2;
  long *plVar3;
  uint uVar4;
  TArrayList *pTVar5;
  TArrayList *pTVar6;

  if (param_1 == (CBaseUnit *)0x0) {
    return 0;
  }
  pTVar6 = (TArrayList *)(this + 0x78);
  if (*(int *)(this + 0x80) != 0) {
    uVar4 = 0;
    do {
      if (uVar4 < *(uint *)(this + 0x84)) {
        puVar2 = (undefined8 *)((ulong)uVar4 * 8 + *(long *)pTVar6);
      }
      else {
        puVar2 = *(undefined8 **)pTVar6;
      }
      cVar1 = CQuestDialog::dialogIsForNPC((CQuestDialog *)*puVar2,param_1);
      if (cVar1 != '\0') goto LAB_00d14ffa;
      uVar4 = uVar4 + 1;
    } while (uVar4 < *(uint *)(this + 0x80));
  }
  pTVar6 = (TArrayList *)0x0;
LAB_00d14ffa:
  pTVar5 = (TArrayList *)(this + 0x90);
  cVar1 = isComplete(this,false);
  if ((cVar1 == '\0') && (pTVar5 = (TArrayList *)(this + 0x60), this[0x26] != (CQuest)0x0)) {
    cVar1 = dialogIsForNPC(param_1,pTVar5);
    if (cVar1 != '\0') {
      if (*(int *)(this + 0x68) != 0) {
        uVar4 = 0;
        if (*(int *)(this + 0x6c) != 0) goto LAB_00d1514d;
        do {
          puVar2 = *(undefined8 **)(this + 0x60);
          while( true ) {
            cVar1 = CQuestDialog::dialogIsForNPC((CQuestDialog *)*puVar2,param_1);
            if (cVar1 != '\0') {
              if (uVar4 < *(uint *)(this + 0x6c)) {
                plVar3 = (long *)((ulong)uVar4 * 8 + *(long *)(this + 0x60));
              }
              else {
                plVar3 = *(long **)(this + 0x60);
              }
              if (*(char *)(*plVar3 + 0x76) != '\0') goto LAB_00d1509f;
            }
            uVar4 = uVar4 + 1;
            if (*(uint *)(this + 0x68) <= uVar4) goto LAB_00d1501d;
            if (*(uint *)(this + 0x6c) <= uVar4) break;
LAB_00d1514d:
            puVar2 = (undefined8 *)((ulong)uVar4 * 8 + *(long *)(this + 0x60));
          }
        } while( true );
      }
      goto LAB_00d1501d;
    }
LAB_00d1509f:
    if (this[0x26] == (CQuest)0x0) goto LAB_00d1501d;
  }
  else {
LAB_00d1501d:
    cVar1 = dialogIsForNPC(param_1,pTVar5);
    if (cVar1 != '\0') goto LAB_00d1502f;
  }
  pTVar5 = pTVar6;
LAB_00d1502f:
  if ((pTVar5 == (TArrayList *)0x0) && (this[0x26] != (CQuest)0x0)) {
    cVar1 = dialogIsForNPC(param_1,(TArrayList *)(this + 0xa8));
    if (cVar1 != '\0') {
      pTVar5 = (TArrayList *)(this + 0xa8);
    }
  }
  if ((pTVar5 != (TArrayList *)0x0) && (*(int *)(pTVar5 + 8) != 0)) {
    uVar4 = 0;
    do {
      if (uVar4 < *(uint *)(pTVar5 + 0xc)) {
        puVar2 = (undefined8 *)((ulong)uVar4 * 8 + *(long *)pTVar5);
      }
      else {
        puVar2 = *(undefined8 **)pTVar5;
      }
      cVar1 = CQuestDialog::dialogIsForNPC((CQuestDialog *)*puVar2,param_1);
      if (cVar1 != '\0') {
        if (uVar4 < *(uint *)(pTVar5 + 0xc)) {
          puVar2 = (undefined8 *)((ulong)uVar4 * 8 + *(long *)pTVar5);
        }
        else {
          puVar2 = *(undefined8 **)pTVar5;
        }
        return *puVar2;
      }
      uVar4 = uVar4 + 1;
    } while (uVar4 < *(uint *)(pTVar5 + 8));
  }
  return 0;
}

/* address=00d15180
   symbol=CQuest::getQuestIsValidForNPC */

/* CQuest::getQuestIsValidForNPC(CBaseUnit*) */

undefined4 __thiscall CQuest::getQuestIsValidForNPC(CQuest *this,CBaseUnit *param_1)

{
  undefined4 uVar1;
  long lVar2;

  if ((param_1 != (CBaseUnit *)0x0) && (this[0x210] == (CQuest)0x0)) {
    uVar1 = 1;
    if ((*(CQuestRequirements **)(this + 0x1e0) != (CQuestRequirements *)0x0) &&
       (uVar1 = CQuestRequirements::questRequirmentsHaveBeenMet
                          (*(CQuestRequirements **)(this + 0x1e0)), (char)uVar1 == '\0')) {
      return uVar1;
    }
    lVar2 = getQuestDialog(this,param_1);
    if (lVar2 != 0) {
      return uVar1;
    }
    if (this[0x20b] != (CQuest)0x0) {
      return uVar1;
    }
  }
  return 0;
}

/* address=00d15210
   symbol=CQuest::getAllNPCUnitDataInvolvedInQuest */

/* CQuest::getAllNPCUnitDataInvolvedInQuest(TArrayList<CDataGroup*>&) */

void __thiscall CQuest::getAllNPCUnitDataInvolvedInQuest(CQuest *this,TArrayList *param_1)

{
  long *plVar1;
  long lVar2;
  uint uVar3;
  long *plVar4;
  long *plVar5;
  uint uVar6;
  ulong uVar7;
  long *plVar8;
  uint uVar9;
  uint uVar10;

  if (*(int *)(this + 0x68) != 0) {
    uVar9 = 0;
    do {
      while( true ) {
        uVar10 = *(uint *)(this + 0x6c);
        if (uVar9 < uVar10) {
          plVar8 = (long *)((ulong)uVar9 * 8 + *(long *)(this + 0x60));
        }
        else {
          plVar8 = *(long **)(this + 0x60);
        }
        if (*(long *)(*plVar8 + 0x68) != 0) break;
LAB_00d15329:
        uVar9 = uVar9 + 1;
        if (*(uint *)(this + 0x68) <= uVar9) goto LAB_00d15337;
      }
      if (uVar9 < uVar10) {
        plVar8 = (long *)((ulong)uVar9 * 8 + *(long *)(this + 0x60));
      }
      else {
        plVar8 = *(long **)(this + 0x60);
      }
      uVar3 = *(uint *)(param_1 + 8);
      if (uVar3 == 0) {
        plVar4 = *(long **)param_1;
LAB_00d152a6:
        if (uVar9 < uVar10) {
          plVar8 = (long *)((ulong)uVar9 * 8 + *(long *)(this + 0x60));
        }
        else {
          plVar8 = *(long **)(this + 0x60);
        }
        lVar2 = *(long *)(*plVar8 + 0x68);
        if (*(uint *)(param_1 + 0xc) <= uVar3) {
          if (plVar4 == (long *)0x0) {
            *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0x10);
            plVar4 = operator_new__((ulong)*(uint *)(param_1 + 0x10) << 3);
            uVar3 = *(uint *)(param_1 + 8);
            *(long **)param_1 = plVar4;
          }
          else {
            uVar10 = *(uint *)(param_1 + 0xc) + *(int *)(param_1 + 0x10);
            plVar4 = operator_new__((ulong)uVar10 << 3);
            if (*(int *)(param_1 + 0xc) != 0) {
              uVar3 = 0;
              do {
                uVar7 = (ulong)uVar3;
                uVar3 = uVar3 + 1;
                plVar4[uVar7] = *(long *)(*(long *)param_1 + uVar7 * 8);
              } while (uVar3 < *(uint *)(param_1 + 0xc));
            }
            if (*(void **)param_1 != (void *)0x0) {
              operator_delete__(*(void **)param_1);
            }
            uVar3 = *(uint *)(param_1 + 8);
            *(long **)param_1 = plVar4;
            *(uint *)(param_1 + 0xc) = uVar10;
          }
        }
        plVar4[uVar3] = lVar2;
        *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 1;
        goto LAB_00d15329;
      }
      plVar4 = *(long **)param_1;
      uVar6 = 0;
      plVar5 = plVar4;
      if (*(long *)(*plVar8 + 0x68) == *plVar4) goto LAB_00d15329;
      do {
        uVar6 = uVar6 + 1;
        if (uVar3 <= uVar6) goto LAB_00d152a6;
        plVar1 = plVar5 + 1;
        plVar5 = plVar5 + 1;
      } while (*(long *)(*plVar8 + 0x68) != *plVar1);
      if (uVar6 == 0xffffffff) goto LAB_00d152a6;
      uVar9 = uVar9 + 1;
    } while (uVar9 < *(uint *)(this + 0x68));
  }
LAB_00d15337:
  if (*(int *)(this + 0x80) != 0) {
    uVar9 = 0;
    do {
      while( true ) {
        uVar10 = *(uint *)(this + 0x84);
        if (uVar9 < uVar10) {
          plVar8 = (long *)((ulong)uVar9 * 8 + *(long *)(this + 0x78));
        }
        else {
          plVar8 = *(long **)(this + 0x78);
        }
        if (*(long *)(*plVar8 + 0x68) != 0) break;
LAB_00d15441:
        uVar9 = uVar9 + 1;
        if (*(uint *)(this + 0x80) <= uVar9) goto LAB_00d15452;
      }
      if (uVar9 < uVar10) {
        plVar8 = (long *)((ulong)uVar9 * 8 + *(long *)(this + 0x78));
      }
      else {
        plVar8 = *(long **)(this + 0x78);
      }
      uVar3 = *(uint *)(param_1 + 8);
      if (uVar3 == 0) {
        plVar4 = *(long **)param_1;
LAB_00d153be:
        if (uVar9 < uVar10) {
          plVar8 = (long *)((ulong)uVar9 * 8 + *(long *)(this + 0x78));
        }
        else {
          plVar8 = *(long **)(this + 0x78);
        }
        lVar2 = *(long *)(*plVar8 + 0x68);
        if (*(uint *)(param_1 + 0xc) <= uVar3) {
          if (plVar4 == (long *)0x0) {
            *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0x10);
            plVar4 = operator_new__((ulong)*(uint *)(param_1 + 0x10) << 3);
            uVar3 = *(uint *)(param_1 + 8);
            *(long **)param_1 = plVar4;
          }
          else {
            uVar10 = *(uint *)(param_1 + 0xc) + *(int *)(param_1 + 0x10);
            plVar4 = operator_new__((ulong)uVar10 << 3);
            if (*(int *)(param_1 + 0xc) != 0) {
              uVar3 = 0;
              do {
                uVar7 = (ulong)uVar3;
                uVar3 = uVar3 + 1;
                plVar4[uVar7] = *(long *)(*(long *)param_1 + uVar7 * 8);
              } while (uVar3 < *(uint *)(param_1 + 0xc));
            }
            if (*(void **)param_1 != (void *)0x0) {
              operator_delete__(*(void **)param_1);
            }
            uVar3 = *(uint *)(param_1 + 8);
            *(long **)param_1 = plVar4;
            *(uint *)(param_1 + 0xc) = uVar10;
          }
        }
        plVar4[uVar3] = lVar2;
        *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 1;
        goto LAB_00d15441;
      }
      plVar4 = *(long **)param_1;
      uVar6 = 0;
      plVar5 = plVar4;
      if (*(long *)(*plVar8 + 0x68) == *plVar4) goto LAB_00d15441;
      do {
        uVar6 = uVar6 + 1;
        if (uVar3 <= uVar6) goto LAB_00d153be;
        plVar1 = plVar5 + 1;
        plVar5 = plVar5 + 1;
      } while (*(long *)(*plVar8 + 0x68) != *plVar1);
      if (uVar6 == 0xffffffff) goto LAB_00d153be;
      uVar9 = uVar9 + 1;
    } while (uVar9 < *(uint *)(this + 0x80));
  }
LAB_00d15452:
  if (*(int *)(this + 0x98) != 0) {
    uVar9 = 0;
    do {
      while( true ) {
        uVar10 = *(uint *)(this + 0x9c);
        if (uVar9 < uVar10) {
          plVar8 = (long *)((ulong)uVar9 * 8 + *(long *)(this + 0x90));
        }
        else {
          plVar8 = *(long **)(this + 0x90);
        }
        if (*(long *)(*plVar8 + 0x68) != 0) break;
LAB_00d15569:
        uVar9 = uVar9 + 1;
        if (*(uint *)(this + 0x98) <= uVar9) goto LAB_00d1557a;
      }
      if (uVar9 < uVar10) {
        plVar8 = (long *)((ulong)uVar9 * 8 + *(long *)(this + 0x90));
      }
      else {
        plVar8 = *(long **)(this + 0x90);
      }
      uVar3 = *(uint *)(param_1 + 8);
      if (uVar3 == 0) {
        plVar4 = *(long **)param_1;
LAB_00d154de:
        if (uVar9 < uVar10) {
          plVar8 = (long *)((ulong)uVar9 * 8 + *(long *)(this + 0x90));
        }
        else {
          plVar8 = *(long **)(this + 0x90);
        }
        lVar2 = *(long *)(*plVar8 + 0x68);
        if (*(uint *)(param_1 + 0xc) <= uVar3) {
          if (plVar4 == (long *)0x0) {
            *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0x10);
            plVar4 = operator_new__((ulong)*(uint *)(param_1 + 0x10) << 3);
            uVar3 = *(uint *)(param_1 + 8);
            *(long **)param_1 = plVar4;
          }
          else {
            uVar10 = *(uint *)(param_1 + 0xc) + *(int *)(param_1 + 0x10);
            plVar4 = operator_new__((ulong)uVar10 << 3);
            if (*(int *)(param_1 + 0xc) != 0) {
              uVar3 = 0;
              do {
                uVar7 = (ulong)uVar3;
                uVar3 = uVar3 + 1;
                plVar4[uVar7] = *(long *)(*(long *)param_1 + uVar7 * 8);
              } while (uVar3 < *(uint *)(param_1 + 0xc));
            }
            if (*(void **)param_1 != (void *)0x0) {
              operator_delete__(*(void **)param_1);
            }
            uVar3 = *(uint *)(param_1 + 8);
            *(long **)param_1 = plVar4;
            *(uint *)(param_1 + 0xc) = uVar10;
          }
        }
        plVar4[uVar3] = lVar2;
        *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 1;
        goto LAB_00d15569;
      }
      plVar4 = *(long **)param_1;
      uVar6 = 0;
      plVar5 = plVar4;
      if (*(long *)(*plVar8 + 0x68) == *plVar4) goto LAB_00d15569;
      do {
        uVar6 = uVar6 + 1;
        if (uVar3 <= uVar6) goto LAB_00d154de;
        plVar1 = plVar5 + 1;
        plVar5 = plVar5 + 1;
      } while (*(long *)(*plVar8 + 0x68) != *plVar1);
      if (uVar6 == 0xffffffff) goto LAB_00d154de;
      uVar9 = uVar9 + 1;
    } while (uVar9 < *(uint *)(this + 0x98));
  }
LAB_00d1557a:
  if (*(int *)(this + 0xb0) != 0) {
    uVar9 = 0;
    do {
      while( true ) {
        uVar10 = *(uint *)(this + 0xb4);
        if (uVar9 < uVar10) {
          plVar8 = (long *)((ulong)uVar9 * 8 + *(long *)(this + 0xa8));
        }
        else {
          plVar8 = *(long **)(this + 0xa8);
        }
        if (*(long *)(*plVar8 + 0x68) != 0) break;
LAB_00d15699:
        uVar9 = uVar9 + 1;
        if (*(uint *)(this + 0xb0) <= uVar9) {
          return;
        }
      }
      if (uVar9 < uVar10) {
        plVar8 = (long *)((ulong)uVar9 * 8 + *(long *)(this + 0xa8));
      }
      else {
        plVar8 = *(long **)(this + 0xa8);
      }
      uVar3 = *(uint *)(param_1 + 8);
      if (uVar3 == 0) {
        plVar4 = *(long **)param_1;
LAB_00d1560e:
        if (uVar9 < uVar10) {
          plVar8 = (long *)((ulong)uVar9 * 8 + *(long *)(this + 0xa8));
        }
        else {
          plVar8 = *(long **)(this + 0xa8);
        }
        lVar2 = *(long *)(*plVar8 + 0x68);
        if (*(uint *)(param_1 + 0xc) <= uVar3) {
          if (plVar4 == (long *)0x0) {
            *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0x10);
            plVar4 = operator_new__((ulong)*(uint *)(param_1 + 0x10) << 3);
            uVar3 = *(uint *)(param_1 + 8);
            *(long **)param_1 = plVar4;
          }
          else {
            uVar10 = *(uint *)(param_1 + 0xc) + *(int *)(param_1 + 0x10);
            plVar4 = operator_new__((ulong)uVar10 << 3);
            if (*(int *)(param_1 + 0xc) != 0) {
              uVar3 = 0;
              do {
                uVar7 = (ulong)uVar3;
                uVar3 = uVar3 + 1;
                plVar4[uVar7] = *(long *)(*(long *)param_1 + uVar7 * 8);
              } while (uVar3 < *(uint *)(param_1 + 0xc));
            }
            if (*(void **)param_1 != (void *)0x0) {
              operator_delete__(*(void **)param_1);
            }
            uVar3 = *(uint *)(param_1 + 8);
            *(long **)param_1 = plVar4;
            *(uint *)(param_1 + 0xc) = uVar10;
          }
        }
        plVar4[uVar3] = lVar2;
        *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 1;
        goto LAB_00d15699;
      }
      plVar4 = *(long **)param_1;
      uVar6 = 0;
      plVar5 = plVar4;
      if (*(long *)(*plVar8 + 0x68) == *plVar4) goto LAB_00d15699;
      do {
        uVar6 = uVar6 + 1;
        if (uVar3 <= uVar6) goto LAB_00d1560e;
        plVar1 = plVar5 + 1;
        plVar5 = plVar5 + 1;
      } while (*(long *)(*plVar8 + 0x68) != *plVar1);
      if (uVar6 == 0xffffffff) goto LAB_00d1560e;
      uVar9 = uVar9 + 1;
    } while (uVar9 < *(uint *)(this + 0xb0));
  }
  return;
}

/* address=00d16280
   symbol=CQuest::CQuest */

/* CQuest::CQuest(CResourceManager*, CQuestManager*) */

void __thiscall CQuest::CQuest(CQuest *this,CResourceManager *param_1,CQuestManager *param_2)

{
  CQuestRequirements *this_00;

  CRunicCore::CRunicCore((CRunicCore *)this);
  *(undefined ***)this = &PTR__CQuest_00ff7170;
  *(undefined8 *)(this + 0x10) = 0;
  *(undefined4 *)(this + 0x18) = 0;
  *(undefined4 *)(this + 0x1c) = 0xffffffff;
  *(undefined4 *)(this + 0x20) = 0;
  this[0x24] = (CQuest)0x0;
  this[0x25] = (CQuest)0x0;
  this[0x26] = (CQuest)0x0;
  this[0x27] = (CQuest)0x0;
  this[0x28] = (CQuest)0x0;
  this[0x29] = (CQuest)0x1;
  this[0x2a] = (CQuest)0x0;
  this[0x2b] = (CQuest)0x0;
                    /* try { // try from 00d162f1 to 00d162f5 has its CatchHandler @ 00d16658 */
  std::wstring::wstring((wstring_conflict *)(this + 0x30),(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 00d16302 to 00d16306 has its CatchHandler @ 00d16728 */
  std::wstring::wstring((wstring_conflict *)(this + 0x38),(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 00d16313 to 00d16317 has its CatchHandler @ 00d1670e */
  std::wstring::wstring((wstring_conflict *)(this + 0x40),(wstring_conflict *)&::EMPTY_WSTRING);
                    /* try { // try from 00d16324 to 00d16328 has its CatchHandler @ 00d1672d */
  std::wstring::wstring((wstring_conflict *)(this + 0x48),(wstring_conflict *)&::EMPTY_WSTRING);
  *(undefined4 **)(this + 0x50) = &DAT_01424558;
  *(undefined4 **)(this + 0x58) = &DAT_01424558;
  *(undefined8 *)(this + 0x60) = 0;
  *(undefined4 *)(this + 0x68) = 0;
  *(undefined4 *)(this + 0x6c) = 0;
  *(undefined4 *)(this + 0x70) = 10;
  *(undefined8 *)(this + 0x78) = 0;
  *(undefined4 *)(this + 0x80) = 0;
  *(undefined4 *)(this + 0x84) = 0;
  *(undefined4 *)(this + 0x88) = 10;
  *(undefined8 *)(this + 0x90) = 0;
  *(undefined4 *)(this + 0x98) = 0;
  *(undefined4 *)(this + 0x9c) = 0;
  *(undefined4 *)(this + 0xa0) = 10;
  *(undefined8 *)(this + 0xa8) = 0;
  *(undefined4 *)(this + 0xb0) = 0;
  *(undefined4 *)(this + 0xb4) = 0;
  *(undefined4 *)(this + 0xb8) = 10;
  *(undefined8 *)(this + 0xc0) = 0;
  *(undefined8 *)(this + 200) = 0;
  *(undefined4 *)(this + 0xd0) = 0;
  *(undefined4 *)(this + 0xd4) = 0;
  *(undefined4 *)(this + 0xd8) = 10;
  *(undefined8 *)(this + 0xe0) = 0;
  *(undefined4 *)(this + 0xe8) = 0;
  *(undefined4 *)(this + 0xec) = 0;
  *(undefined4 *)(this + 0xf0) = 10;
  *(undefined8 *)(this + 0xf8) = 0;
  *(undefined4 *)(this + 0x100) = 0;
  *(undefined4 *)(this + 0x104) = 0;
  *(undefined4 *)(this + 0x108) = 10;
  *(undefined8 *)(this + 0x110) = 0;
  *(undefined4 *)(this + 0x118) = 0;
  *(undefined4 *)(this + 0x11c) = 0;
  *(undefined4 *)(this + 0x120) = 10;
  *(undefined8 *)(this + 0x128) = 0;
  *(undefined8 *)(this + 0x130) = 0;
  *(undefined4 *)(this + 0x138) = 0;
  *(undefined4 *)(this + 0x13c) = 0;
  *(undefined4 *)(this + 0x140) = 1;
  *(undefined8 *)(this + 0x148) = 0;
  *(undefined4 *)(this + 0x150) = 0;
  *(undefined4 *)(this + 0x154) = 0;
  *(undefined4 *)(this + 0x158) = 1;
  *(undefined8 *)(this + 0x160) = 0;
  *(undefined4 *)(this + 0x168) = 0;
  *(undefined4 *)(this + 0x16c) = 0;
  *(undefined4 *)(this + 0x170) = 1;
  *(undefined8 *)(this + 0x178) = 0;
  *(undefined4 *)(this + 0x180) = 0;
  *(undefined4 *)(this + 0x184) = 0;
  *(undefined4 *)(this + 0x188) = 1;
  *(undefined8 *)(this + 400) = 0;
  *(undefined4 *)(this + 0x198) = 0;
  *(undefined4 *)(this + 0x19c) = 0;
  *(undefined4 *)(this + 0x1a0) = 1;
  *(undefined4 *)(this + 0x1a8) = 1;
  *(undefined4 *)(this + 0x1ac) = 1;
  *(undefined8 *)(this + 0x1b0) = 0;
  *(undefined4 *)(this + 0x1b8) = 0;
  *(undefined4 *)(this + 0x1bc) = 0;
  *(undefined4 *)(this + 0x1c0) = 1;
  *(undefined8 *)(this + 0x1c8) = 0xffffffffffffffff;
  *(CQuestManager **)(this + 0x1d0) = param_2;
  *(CResourceManager **)(this + 0x1d8) = param_1;
  *(undefined8 *)(this + 0x1e0) = 0;
  *(undefined8 *)(this + 0x1e8) = 0;
  *(undefined8 *)(this + 0x1f0) = 0;
  *(undefined4 *)(this + 0x1f8) = 0;
  *(undefined4 *)(this + 0x1fc) = 0;
  *(undefined4 *)(this + 0x200) = 10;
  this[0x209] = (CQuest)0x0;
  this[0x20a] = (CQuest)0x0;
  this[0x20b] = (CQuest)0x0;
  *(undefined4 *)(this + 0x20c) = 1;
  this[0x210] = (CQuest)0x0;
                    /* try { // try from 00d1662f to 00d16633 has its CatchHandler @ 00d16706 */
  this_00 = (CQuestRequirements *)Ogre::NedAllocImpl::allocBytes(0x50,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00d1663d to 00d16641 has its CatchHandler @ 00d1666b */
  CQuestRequirements::CQuestRequirements(this_00,this);
  *(CQuestRequirements **)(this + 0x1e0) = this_00;
  return;
}

/* address=00d167a0
   symbol=CQuest::getQuestStrings */

/* WARNING: Removing unreachable block (ram,0x00d169f2) */
/* CQuest::getQuestStrings(CDataGroup*, std::wstring const&, TArrayList<CQuestDialog*>&) */

void __thiscall
CQuest::getQuestStrings
          (CQuest *this,CDataGroup *param_1,wstring_conflict *param_2,TArrayList *param_3)

{
  int *piVar1;
  int iVar2;
  CDataGroup *pCVar3;
  char cVar4;
  CQuestDialog *this_00;
  wstring_conflict *pwVar5;
  void *pvVar6;
  ulong uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  void *local_68;
  long local_60;
  undefined8 local_58;
  long local_48;
  allocator local_39 [9];

  if (param_1 != (CDataGroup *)0x0) {
    local_68 = (void *)0x0;
    local_60 = 0;
    local_58 = 0;
                    /* try { // try from 00d167e8 to 00d16865 has its CatchHandler @ 00d169e4 */
    CDataGroup::GetDataGroupsMatchingName(param_1,param_2,(vector *)&local_68);
    if (local_60 - (long)local_68 >> 3 != 0) {
      uVar7 = 0;
      uVar10 = 0;
      do {
        this_00 = (CQuestDialog *)Ogre::NedAllocImpl::allocBytes(0xa8,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00d16871 to 00d16875 has its CatchHandler @ 00d169d7 */
        CQuestDialog::CQuestDialog(this_00,this);
        pCVar3 = *(CDataGroup **)((long)local_68 + uVar7 * 8);
                    /* try { // try from 00d1688c to 00d16890 has its CatchHandler @ 00d169e9 */
        std::wstring::wstring((wstring_conflict *)&local_48,L"UNITNAME",local_39);
                    /* try { // try from 00d1689c to 00d168ae has its CatchHandler @ 00d169b5 */
        pwVar5 = (wstring_conflict *)
                 CDataGroup::GetDataValue
                           (param_1,(wstring_conflict *)&local_48,
                            (wstring_conflict *)&::EMPTY_WSTRING);
        cVar4 = CQuestDialog::parseDialogTag(this_00,pwVar5,pCVar3);
        if ((allocator *)(local_48 + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_48 + -8);
          iVar2 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar2 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_48 + -0x18));
          }
        }
        if (cVar4 == '\0') {
          if (this_00 != (CQuestDialog *)0x0) {
                    /* try { // try from 00d168dd to 00d16960 has its CatchHandler @ 00d169e4 */
            (**(code **)(*(long *)this_00 + 8))(this_00);
          }
        }
        else {
          uVar9 = *(uint *)(param_3 + 8);
          if (uVar9 < *(uint *)(param_3 + 0xc)) {
            pvVar6 = *(void **)param_3;
          }
          else if (*(long *)param_3 == 0) {
            *(uint *)(param_3 + 0xc) = *(uint *)(param_3 + 0x10);
            pvVar6 = operator_new__((ulong)*(uint *)(param_3 + 0x10) << 3);
            *(void **)param_3 = pvVar6;
            uVar9 = *(uint *)(param_3 + 8);
          }
          else {
            uVar9 = *(uint *)(param_3 + 0xc) + *(int *)(param_3 + 0x10);
            pvVar6 = operator_new__((ulong)uVar9 << 3);
            if (*(int *)(param_3 + 0xc) != 0) {
              uVar8 = 0;
              do {
                uVar7 = (ulong)uVar8;
                uVar8 = uVar8 + 1;
                *(undefined8 *)((long)pvVar6 + uVar7 * 8) =
                     *(undefined8 *)(*(long *)param_3 + uVar7 * 8);
              } while (uVar8 < *(uint *)(param_3 + 0xc));
            }
            if (*(void **)param_3 != (void *)0x0) {
              operator_delete__(*(void **)param_3);
            }
            *(void **)param_3 = pvVar6;
            *(uint *)(param_3 + 0xc) = uVar9;
            uVar9 = *(uint *)(param_3 + 8);
          }
          *(CQuestDialog **)((long)pvVar6 + (ulong)uVar9 * 8) = this_00;
          *(int *)(param_3 + 8) = *(int *)(param_3 + 8) + 1;
        }
        uVar10 = uVar10 + 1;
        uVar7 = (ulong)uVar10;
      } while (uVar7 < (ulong)(local_60 - (long)local_68 >> 3));
    }
    if (local_68 != (void *)0x0) {
      operator_delete(local_68);
    }
  }
  return;
}

/* address=00d16bb0
   symbol=CQuest::save */

/* WARNING: Removing unreachable block (ram,0x00d171f4) */
/* CQuest::save(_IO_FILE*) */

void __thiscall CQuest::save(CQuest *this,_IO_FILE *param_1)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  undefined8 *puVar4;
  long *plVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  ulong uVar9;
  long local_58;
  undefined8 local_50;
  uint local_44;
  undefined4 local_40;
  allocator local_39 [9];

  local_50 = 0xffffffffffffffff;
  if (*(long *)(this + 0x1e8) != 0) {
                    /* try { // try from 00d16be9 to 00d16bed has its CatchHandler @ 00d171b3 */
    std::wstring::wstring((wstring_conflict *)&local_58,L"UNIT_GUID",local_39);
                    /* try { // try from 00d16bff to 00d16c03 has its CatchHandler @ 00d171e7 */
    local_50 = CResourceManager::getUnitGuidByDataGroup
                         (*(CResourceManager **)(this + 0x1d8),*(CDataGroup **)(this + 0x1e8),
                          (wstring_conflict *)&local_58);
    if ((allocator *)(local_58 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_58 + -8);
      iVar3 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar3 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_58 + -0x18));
      }
    }
  }
  fwrite(&local_50,8,1,param_1);
  fwrite(this + 0x1c,4,1,param_1);
  fwrite(this + 0x20,4,1,param_1);
  fwrite(this + 0x20c,4,1,param_1);
  local_40 = *(undefined4 *)(this + 0x68);
  fwrite(&local_40,4,1,param_1);
  if (*(int *)(this + 0x68) != 0) {
    uVar6 = 0;
    do {
      if (uVar6 < *(uint *)(this + 0x6c)) {
        puVar4 = (undefined8 *)((ulong)uVar6 * 8 + *(long *)(this + 0x60));
      }
      else {
        puVar4 = *(undefined8 **)(this + 0x60);
      }
      uVar6 = uVar6 + 1;
      CQuestDialog::save((CQuestDialog *)*puVar4,param_1);
    } while (uVar6 < *(uint *)(this + 0x68));
  }
  local_40 = *(undefined4 *)(this + 0x80);
  fwrite(&local_40,4,1,param_1);
  if (*(int *)(this + 0x80) != 0) {
    uVar6 = 0;
    do {
      if (uVar6 < *(uint *)(this + 0x84)) {
        puVar4 = (undefined8 *)((ulong)uVar6 * 8 + *(long *)(this + 0x78));
      }
      else {
        puVar4 = *(undefined8 **)(this + 0x78);
      }
      uVar6 = uVar6 + 1;
      CQuestDialog::save((CQuestDialog *)*puVar4,param_1);
    } while (uVar6 < *(uint *)(this + 0x80));
  }
  local_40 = *(undefined4 *)(this + 0x98);
  fwrite(&local_40,4,1,param_1);
  if (*(int *)(this + 0x98) != 0) {
    uVar6 = 0;
    do {
      if (uVar6 < *(uint *)(this + 0x9c)) {
        puVar4 = (undefined8 *)((ulong)uVar6 * 8 + *(long *)(this + 0x90));
      }
      else {
        puVar4 = *(undefined8 **)(this + 0x90);
      }
      uVar6 = uVar6 + 1;
      CQuestDialog::save((CQuestDialog *)*puVar4,param_1);
    } while (uVar6 < *(uint *)(this + 0x98));
  }
  local_40 = *(undefined4 *)(this + 0xb0);
  fwrite(&local_40,4,1,param_1);
  if (*(int *)(this + 0xb0) != 0) {
    uVar6 = 0;
    do {
      if (uVar6 < *(uint *)(this + 0xb4)) {
        puVar4 = (undefined8 *)((ulong)uVar6 * 8 + *(long *)(this + 0xa8));
      }
      else {
        puVar4 = *(undefined8 **)(this + 0xa8);
      }
      uVar6 = uVar6 + 1;
      CQuestDialog::save((CQuestDialog *)*puVar4,param_1);
    } while (uVar6 < *(uint *)(this + 0xb0));
  }
  local_40 = *(undefined4 *)(this + 0x138);
  fwrite(&local_40,4,1,param_1);
  if (*(int *)(this + 0x138) != 0) {
    uVar6 = *(uint *)(this + 0x13c);
    uVar7 = 0;
    do {
      if (uVar7 < uVar6) {
        plVar5 = (long *)((ulong)uVar7 * 8 + *(long *)(this + 0x130));
      }
      else {
        plVar5 = *(long **)(this + 0x130);
      }
      uVar9 = 0;
      local_40 = *(undefined4 *)(*plVar5 + 8);
      fwrite(&local_40,4,1,param_1);
      while( true ) {
        uVar6 = *(uint *)(this + 0x13c);
        uVar8 = (uint)uVar9;
        if (uVar7 < uVar6) {
          uVar2 = *(uint *)(*(long *)((ulong)uVar7 * 8 + *(long *)(this + 0x130)) + 8);
        }
        else {
          uVar2 = *(uint *)(**(long **)(this + 0x130) + 8);
        }
        if (uVar2 <= uVar8) break;
        if (uVar7 < uVar6) {
          plVar5 = (long *)((ulong)uVar7 * 8 + *(long *)(this + 0x130));
        }
        else {
          plVar5 = *(long **)(this + 0x130);
        }
        plVar5 = (long *)*plVar5;
        if (uVar8 < *(uint *)((long)plVar5 + 0xc)) {
          puVar4 = (undefined8 *)(uVar9 * 8 + *plVar5);
        }
        else {
          puVar4 = (undefined8 *)*plVar5;
        }
        uVar9 = (ulong)(uVar8 + 1);
        CQuestUnitData::save((CQuestUnitData *)*puVar4,param_1);
      }
      uVar7 = uVar7 + 1;
    } while (uVar7 < *(uint *)(this + 0x138));
  }
  local_40 = *(undefined4 *)(this + 0x150);
  fwrite(&local_40,4,1,param_1);
  if (*(int *)(this + 0x150) != 0) {
    uVar6 = 0;
    do {
      local_44 = 0;
      if (uVar6 < *(uint *)(this + 0x154)) {
        plVar5 = (long *)((ulong)uVar6 * 8 + *(long *)(this + 0x148));
      }
      else {
        plVar5 = *(long **)(this + 0x148);
      }
      if (*plVar5 != 0) {
        if (uVar6 < *(uint *)(this + 0x154)) {
          plVar5 = (long *)((ulong)uVar6 * 8 + *(long *)(this + 0x148));
        }
        else {
          plVar5 = *(long **)(this + 0x148);
        }
        local_44 = *(uint *)(*plVar5 + 8);
      }
      fwrite(&local_44,4,1,param_1);
      if (local_44 != 0) {
        uVar9 = 0;
        do {
          uVar7 = (uint)uVar9;
          if (uVar6 < *(uint *)(this + 0x154)) {
            plVar5 = *(long **)((ulong)uVar6 * 8 + *(long *)(this + 0x148));
            if (uVar7 < *(uint *)((long)plVar5 + 0xc)) goto LAB_00d16ff7;
LAB_00d16fc0:
            puVar4 = (undefined8 *)*plVar5;
          }
          else {
            plVar5 = (long *)**(long **)(this + 0x148);
            if (*(uint *)((long)plVar5 + 0xc) <= uVar7) goto LAB_00d16fc0;
LAB_00d16ff7:
            puVar4 = (undefined8 *)(uVar9 * 8 + *plVar5);
          }
          uVar9 = (ulong)(uVar7 + 1);
          CQuestUnitData::save((CQuestUnitData *)*puVar4,param_1);
        } while (uVar7 + 1 < local_44);
      }
      uVar6 = uVar6 + 1;
    } while (uVar6 < *(uint *)(this + 0x150));
  }
  local_40 = *(undefined4 *)(this + 0x168);
  fwrite(&local_40,4,1,param_1);
  if (*(int *)(this + 0x168) != 0) {
    uVar6 = *(uint *)(this + 0x16c);
    uVar7 = 0;
    do {
      if (uVar7 < uVar6) {
        plVar5 = (long *)((ulong)uVar7 * 8 + *(long *)(this + 0x160));
      }
      else {
        plVar5 = *(long **)(this + 0x160);
      }
      uVar9 = 0;
      local_40 = *(undefined4 *)(*plVar5 + 8);
      fwrite(&local_40,4,1,param_1);
      while( true ) {
        uVar6 = *(uint *)(this + 0x16c);
        uVar8 = (uint)uVar9;
        if (uVar7 < uVar6) {
          uVar2 = *(uint *)(*(long *)((ulong)uVar7 * 8 + *(long *)(this + 0x160)) + 8);
        }
        else {
          uVar2 = *(uint *)(**(long **)(this + 0x160) + 8);
        }
        if (uVar2 <= uVar8) break;
        if (uVar7 < uVar6) {
          plVar5 = (long *)((ulong)uVar7 * 8 + *(long *)(this + 0x160));
        }
        else {
          plVar5 = *(long **)(this + 0x160);
        }
        plVar5 = (long *)*plVar5;
        if (uVar8 < *(uint *)((long)plVar5 + 0xc)) {
          puVar4 = (undefined8 *)(uVar9 * 8 + *plVar5);
        }
        else {
          puVar4 = (undefined8 *)*plVar5;
        }
        uVar9 = (ulong)(uVar8 + 1);
        CQuestUnitData::save((CQuestUnitData *)*puVar4,param_1);
      }
      uVar7 = uVar7 + 1;
    } while (uVar7 < *(uint *)(this + 0x168));
  }
  return;
}

/* address=00d17200
   symbol=CQuest::reinitializeQuest */

/* WARNING: Removing unreachable block (ram,0x00d17b06) */
/* WARNING: Removing unreachable block (ram,0x00d17aa7) */
/* CQuest::reinitializeQuest(bool, bool) */

void __thiscall CQuest::reinitializeQuest(CQuest *this,bool param_1,bool param_2)

{
  int *piVar1;
  uint uVar2;
  undefined8 uVar3;
  int iVar4;
  uint uVar5;
  CDungeonManager *pCVar6;
  CDungeon *this_00;
  void *pvVar7;
  ulong uVar8;
  undefined8 *puVar9;
  uint uVar10;
  undefined1 *puVar11;
  long *plVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  int iVar16;
  ulong uVar17;
  CGameClient *pCVar18;
  long lVar19;
  CGameClient *local_70;
  long local_58 [2];
  long local_48 [3];

  this[0x24] = (CQuest)0x0;
  this[0x26] = (CQuest)0x0;
  this[0x209] = (CQuest)0x0;
  *(undefined8 *)(this + 0x1e8) = 0;
  this[0x210] = (CQuest)0x0;
  if (!param_2) {
    if (*(int *)(this + 0x1c) != -1) {
      UTILITIES::setSeed(*(int *)(this + 0x1c));
    }
    *(undefined8 *)(this + 0x10) = 0;
    local_70 = (CGameClient *)0x0;
    if (*(int *)(*(long *)(this + 0x1d8) + 0x30) != 0) {
      local_70 = (CGameClient *)**(undefined8 **)(*(long *)(this + 0x1d8) + 0x28);
    }
    std::wstring::wstring((wstring_conflict *)local_48,(wstring_conflict *)(this + 0x30));
                    /* try { // try from 00d1728a to 00d17299 has its CatchHandler @ 00d17af3 */
    pCVar6 = (CDungeonManager *)CDungeonManager::getSingleton();
    this_00 = (CDungeon *)CDungeonManager::getDungeonByName(pCVar6,(wstring_conflict *)local_48);
    if ((allocator *)(local_48[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_48[0] + -8);
      iVar16 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar16 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_48[0] + -0x18));
      }
    }
    if (this_00 != (CDungeon *)0x0) {
      lVar19 = *(long *)(this + 0x10);
      uVar15 = 0;
      iVar16 = 1;
      while( true ) {
        if ((9 < uVar15) || (lVar19 != 0)) goto LAB_00d17367;
        if (*(long *)(*(long *)(this + 0x1d0) + 0x10) == 0) {
          *(int *)(this + 0x20) = iVar16;
          iVar4 = iVar16;
        }
        else {
                    /* try { // try from 00d17300 to 00d1731d has its CatchHandler @ 00d17ab2 */
          std::wstring::wstring((wstring_conflict *)local_58,(wstring_conflict *)(this + 0x30));
          iVar4 = CPlayer::getMaxDepth
                            (*(CPlayer **)(*(long *)(this + 0x1d0) + 0x10),
                             (wstring_conflict *)local_58);
          *(int *)(this + 0x20) = iVar4 + iVar16;
          iVar4 = iVar4 + iVar16;
          if ((allocator *)(local_58[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_58[0] + -8);
            iVar4 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar4 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_58[0] + -0x18));
            }
            iVar4 = *(int *)(this + 0x20);
          }
        }
        if (((this_00[0x89] == (CDungeon)0x0) && (this[0x20b] != (CQuest)0x0)) &&
           (*(int *)(this_00 + 0x18) <= iVar4)) break;
        if (iVar4 < 0) {
          *(undefined4 *)(this + 0x20) = 0;
          iVar4 = 0;
        }
        CGameClient::resetGameSeed(local_70,iVar4);
        pCVar18 = (CGameClient *)0x0;
        if (*(int *)(*(long *)(this + 0x1d8) + 0x30) != 0) {
          pCVar18 = (CGameClient *)**(undefined8 **)(*(long *)(this + 0x1d8) + 0x28);
        }
        lVar19 = CDungeon::getLevelTemplateDataForDepth(this_00,pCVar18,*(uint *)(this + 0x20));
        *(long *)(this + 0x10) = lVar19;
        if (*(char *)(lVar19 + 0x87) != '\0') {
          *(undefined8 *)(this + 0x10) = 0;
          lVar19 = 0;
        }
        iVar16 = iVar16 + 1;
        uVar15 = uVar15 + 1;
      }
      this[0x210] = (CQuest)0x1;
    }
  }
LAB_00d17367:
  uVar15 = *(uint *)(this + 0x180);
  uVar5 = UTILITIES::randomIntegerBetween(*(int *)(this + 0x1a8),*(int *)(this + 0x198));
  if (this[0x27] != (CQuest)0x0) {
    uVar15 = *(uint *)(this + 0x180);
  }
  *(undefined4 *)(this + 0x138) = 0;
  *(undefined4 *)(this + 0x13c) = 0;
  if (*(void **)(this + 0x130) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x130));
  }
  *(undefined8 *)(this + 0x130) = 0;
  *(undefined4 *)(this + 0x150) = 0;
  *(undefined4 *)(this + 0x154) = 0;
  if (*(void **)(this + 0x148) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x148));
  }
  *(undefined8 *)(this + 0x148) = 0;
  if (*(int *)(this + 0x168) != 0) {
    uVar14 = *(uint *)(this + 0x16c);
    uVar8 = 0;
    do {
      uVar13 = (uint)uVar8;
      uVar17 = 0;
      while( true ) {
        uVar10 = (uint)uVar17;
        if (uVar13 < uVar14) {
          uVar2 = *(uint *)(*(long *)(uVar8 * 8 + *(long *)(this + 0x160)) + 8);
        }
        else {
          uVar2 = *(uint *)(**(long **)(this + 0x160) + 8);
        }
        if (uVar2 <= uVar10) break;
        if (uVar13 < uVar14) {
          plVar12 = (long *)(uVar8 * 8 + *(long *)(this + 0x160));
        }
        else {
          plVar12 = *(long **)(this + 0x160);
        }
        plVar12 = (long *)*plVar12;
        if (uVar10 < *(uint *)((long)plVar12 + 0xc)) {
          puVar9 = (undefined8 *)(uVar17 * 8 + *plVar12);
        }
        else {
          puVar9 = (undefined8 *)*plVar12;
        }
        uVar17 = (ulong)(uVar10 + 1);
        CQuestUnitData::reinitialize((CQuestUnitData *)*puVar9,param_1);
        uVar14 = *(uint *)(this + 0x16c);
      }
      uVar8 = (ulong)(uVar13 + 1);
    } while (uVar13 + 1 < *(uint *)(this + 0x168));
  }
  if (uVar15 != 0) {
    uVar14 = *(uint *)(this + 0x13c);
    lVar19 = 0;
    uVar13 = 0;
    do {
      if (uVar13 < *(uint *)(this + 0x184)) {
        uVar10 = *(uint *)(this + 0x138);
        uVar3 = *(undefined8 *)(lVar19 + *(long *)(this + 0x178));
      }
      else {
        uVar10 = *(uint *)(this + 0x138);
        uVar3 = **(undefined8 **)(this + 0x178);
      }
      if (uVar10 < uVar14) {
        pvVar7 = *(void **)(this + 0x130);
      }
      else if (*(long *)(this + 0x130) == 0) {
        *(uint *)(this + 0x13c) = *(uint *)(this + 0x140);
        pvVar7 = operator_new__((ulong)*(uint *)(this + 0x140) << 3);
        uVar10 = *(uint *)(this + 0x138);
        *(void **)(this + 0x130) = pvVar7;
      }
      else {
        iVar16 = *(int *)(this + 0x140);
        pvVar7 = operator_new__((ulong)(uVar14 + iVar16) << 3);
        if (*(int *)(this + 0x13c) != 0) {
          uVar10 = 0;
          do {
            uVar8 = (ulong)uVar10;
            uVar10 = uVar10 + 1;
            *(undefined8 *)((long)pvVar7 + uVar8 * 8) =
                 *(undefined8 *)(*(long *)(this + 0x130) + uVar8 * 8);
          } while (uVar10 < *(uint *)(this + 0x13c));
        }
        if (*(void **)(this + 0x130) != (void *)0x0) {
          operator_delete__(*(void **)(this + 0x130));
        }
        *(void **)(this + 0x130) = pvVar7;
        uVar10 = *(uint *)(this + 0x138);
        *(uint *)(this + 0x13c) = uVar14 + iVar16;
      }
      *(undefined8 *)((long)pvVar7 + (ulong)uVar10 * 8) = uVar3;
      uVar8 = 0;
      *(int *)(this + 0x138) = *(int *)(this + 0x138) + 1;
      while( true ) {
        uVar14 = *(uint *)(this + 0x13c);
        uVar10 = (uint)uVar8;
        if (uVar13 < uVar14) {
          uVar2 = *(uint *)(*(long *)(lVar19 + *(long *)(this + 0x130)) + 8);
        }
        else {
          uVar2 = *(uint *)(**(long **)(this + 0x130) + 8);
        }
        if (uVar2 <= uVar10) break;
        if (uVar13 < uVar14) {
          plVar12 = (long *)(lVar19 + *(long *)(this + 0x130));
        }
        else {
          plVar12 = *(long **)(this + 0x130);
        }
        plVar12 = (long *)*plVar12;
        if (uVar10 < *(uint *)((long)plVar12 + 0xc)) {
          puVar9 = (undefined8 *)(uVar8 * 8 + *plVar12);
        }
        else {
          puVar9 = (undefined8 *)*plVar12;
        }
        CQuestUnitData::reinitialize((CQuestUnitData *)*puVar9,param_1);
        uVar8 = (ulong)(uVar10 + 1);
      }
      uVar13 = uVar13 + 1;
      lVar19 = lVar19 + 8;
    } while (uVar13 < uVar15);
  }
  if (uVar5 != 0) {
    uVar15 = *(uint *)(this + 0x154);
    lVar19 = 0;
    uVar14 = 0;
    do {
      if (uVar14 < *(uint *)(this + 0x19c)) {
        uVar13 = *(uint *)(this + 0x150);
        uVar3 = *(undefined8 *)(lVar19 + *(long *)(this + 400));
      }
      else {
        uVar13 = *(uint *)(this + 0x150);
        uVar3 = **(undefined8 **)(this + 400);
      }
      if (uVar13 < uVar15) {
        pvVar7 = *(void **)(this + 0x148);
      }
      else if (*(long *)(this + 0x148) == 0) {
        *(uint *)(this + 0x154) = *(uint *)(this + 0x158);
        pvVar7 = operator_new__((ulong)*(uint *)(this + 0x158) << 3);
        uVar13 = *(uint *)(this + 0x150);
        *(void **)(this + 0x148) = pvVar7;
      }
      else {
        iVar16 = *(int *)(this + 0x158);
        pvVar7 = operator_new__((ulong)(uVar15 + iVar16) << 3);
        if (*(int *)(this + 0x154) != 0) {
          uVar13 = 0;
          do {
            uVar8 = (ulong)uVar13;
            uVar13 = uVar13 + 1;
            *(undefined8 *)((long)pvVar7 + uVar8 * 8) =
                 *(undefined8 *)(*(long *)(this + 0x148) + uVar8 * 8);
          } while (uVar13 < *(uint *)(this + 0x154));
        }
        if (*(void **)(this + 0x148) != (void *)0x0) {
          operator_delete__(*(void **)(this + 0x148));
        }
        *(void **)(this + 0x148) = pvVar7;
        uVar13 = *(uint *)(this + 0x150);
        *(uint *)(this + 0x154) = uVar15 + iVar16;
      }
      *(undefined8 *)((long)pvVar7 + (ulong)uVar13 * 8) = uVar3;
      uVar8 = 0;
      *(int *)(this + 0x150) = *(int *)(this + 0x150) + 1;
      while( true ) {
        uVar15 = *(uint *)(this + 0x154);
        uVar13 = (uint)uVar8;
        if (uVar14 < uVar15) {
          uVar10 = *(uint *)(*(long *)(lVar19 + *(long *)(this + 0x148)) + 8);
        }
        else {
          uVar10 = *(uint *)(**(long **)(this + 0x148) + 8);
        }
        if (uVar10 <= uVar13) break;
        if (uVar14 < uVar15) {
          plVar12 = (long *)(lVar19 + *(long *)(this + 0x148));
        }
        else {
          plVar12 = *(long **)(this + 0x148);
        }
        plVar12 = (long *)*plVar12;
        if (uVar13 < *(uint *)((long)plVar12 + 0xc)) {
          puVar9 = (undefined8 *)(uVar8 * 8 + *plVar12);
        }
        else {
          puVar9 = (undefined8 *)*plVar12;
        }
        CQuestUnitData::reinitialize((CQuestUnitData *)*puVar9,param_1);
        uVar8 = (ulong)(uVar13 + 1);
      }
      uVar14 = uVar14 + 1;
      lVar19 = lVar19 + 8;
    } while (uVar14 < uVar5);
  }
  lVar19 = 0;
  do {
    uVar8 = 0;
    if (*(int *)(this + lVar19 + 0x100) != 0) {
      do {
        while (uVar15 = (uint)uVar8, *(uint *)(this + lVar19 + 0x104) <= uVar15) {
          uVar8 = (ulong)(uVar15 + 1);
          **(undefined1 **)(this + lVar19 + 0xf8) = 0;
          if (*(uint *)(this + lVar19 + 0x100) <= uVar15 + 1) goto LAB_00d17799;
        }
        puVar11 = (undefined1 *)(uVar8 + *(long *)(this + lVar19 + 0xf8));
        uVar8 = (ulong)(uVar15 + 1);
        *puVar11 = 0;
      } while (uVar15 + 1 < *(uint *)(this + lVar19 + 0x100));
    }
LAB_00d17799:
    lVar19 = lVar19 + 0x18;
  } while (lVar19 != 0x30);
  if (*(int *)(this + 0x68) != 0) {
    uVar15 = 0;
    do {
      while (*(uint *)(this + 0x6c) <= uVar15) {
        uVar15 = uVar15 + 1;
        CQuestDialog::reinitialize((CQuestDialog *)**(undefined8 **)(this + 0x60));
        if (*(uint *)(this + 0x68) <= uVar15) goto LAB_00d177e3;
      }
      uVar8 = (ulong)uVar15;
      uVar15 = uVar15 + 1;
      CQuestDialog::reinitialize(*(CQuestDialog **)(uVar8 * 8 + *(long *)(this + 0x60)));
    } while (uVar15 < *(uint *)(this + 0x68));
  }
LAB_00d177e3:
  if (*(int *)(this + 0x80) != 0) {
    uVar15 = 0;
    do {
      if (uVar15 < *(uint *)(this + 0x84)) {
        puVar9 = (undefined8 *)((ulong)uVar15 * 8 + *(long *)(this + 0x78));
      }
      else {
        puVar9 = *(undefined8 **)(this + 0x78);
      }
      uVar15 = uVar15 + 1;
      CQuestDialog::reinitialize((CQuestDialog *)*puVar9);
    } while (uVar15 < *(uint *)(this + 0x80));
  }
  if (*(int *)(this + 0x98) != 0) {
    uVar15 = 0;
    do {
      if (uVar15 < *(uint *)(this + 0x9c)) {
        puVar9 = (undefined8 *)((ulong)uVar15 * 8 + *(long *)(this + 0x90));
      }
      else {
        puVar9 = *(undefined8 **)(this + 0x90);
      }
      uVar15 = uVar15 + 1;
      CQuestDialog::reinitialize((CQuestDialog *)*puVar9);
    } while (uVar15 < *(uint *)(this + 0x98));
  }
  if (*(int *)(this + 0xb0) != 0) {
    uVar15 = 0;
    do {
      if (uVar15 < *(uint *)(this + 0xb4)) {
        puVar9 = (undefined8 *)((ulong)uVar15 * 8 + *(long *)(this + 0xa8));
      }
      else {
        puVar9 = *(undefined8 **)(this + 0xa8);
      }
      uVar15 = uVar15 + 1;
      CQuestDialog::reinitialize((CQuestDialog *)*puVar9);
    } while (uVar15 < *(uint *)(this + 0xb0));
  }
  return;
}

/* address=00d17b20
   symbol=CQuest::load */

/* WARNING: Removing unreachable block (ram,0x00d18186) */
/* CQuest::load(_IO_FILE*, CResourceManager*, unsigned int) */

void __thiscall CQuest::load(CQuest *this,_IO_FILE *param_1,CResourceManager *param_2,uint param_3)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  undefined8 uVar4;
  CDungeonManager *pCVar5;
  CDungeon *this_00;
  undefined8 *puVar6;
  uint uVar7;
  CGameClient *pCVar8;
  long *plVar9;
  uint uVar10;
  uint uVar11;
  ulong uVar12;
  long local_58;
  long local_50;
  uint local_44;
  uint local_40 [4];

  local_50 = -1;
  fread(&local_50,8,1,param_1);
  if (local_50 != -1) {
    uVar4 = CResourceManager::getUnitDataByGuid(*(CResourceManager **)(this + 0x1d8),local_50);
    *(undefined8 *)(this + 0x1e8) = uVar4;
  }
  fread(this + 0x1c,4,1,param_1);
  fread(this + 0x20,4,1,param_1);
  if (0x13 < param_3) {
    fread(this + 0x20c,4,1,param_1);
  }
  pCVar8 = (CGameClient *)0x0;
  if (*(int *)(*(long *)(this + 0x1d8) + 0x30) != 0) {
    pCVar8 = (CGameClient *)**(undefined8 **)(*(long *)(this + 0x1d8) + 0x28);
  }
  CGameClient::resetGameSeed(pCVar8,*(int *)(this + 0x20));
  std::wstring::wstring((wstring_conflict *)&local_58,(wstring_conflict *)(this + 0x30));
                    /* try { // try from 00d17bdd to 00d17bec has its CatchHandler @ 00d18173 */
  pCVar5 = (CDungeonManager *)CDungeonManager::getSingleton();
  this_00 = (CDungeon *)CDungeonManager::getDungeonByName(pCVar5);
  if ((allocator *)(local_58 + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(local_58 + -8);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_58 + -0x18));
    }
  }
  if (this_00 != (CDungeon *)0x0) {
    pCVar8 = (CGameClient *)0x0;
    if (*(int *)(*(long *)(this + 0x1d8) + 0x30) != 0) {
      pCVar8 = (CGameClient *)**(undefined8 **)(*(long *)(this + 0x1d8) + 0x28);
    }
    uVar4 = CDungeon::getLevelTemplateDataForDepth(this_00,pCVar8,*(uint *)(this + 0x20));
    *(undefined8 *)(this + 0x10) = uVar4;
  }
  uVar4 = *(undefined8 *)(this + 0x1e8);
  reinitializeQuest(this,true,true);
  *(undefined8 *)(this + 0x1e8) = uVar4;
  fread(local_40,4,1,param_1);
  if (local_40[0] != 0) {
    uVar12 = 0;
    do {
      uVar11 = (uint)uVar12;
      if (uVar11 < *(uint *)(this + 0x68)) {
        if (uVar11 < *(uint *)(this + 0x6c)) {
          puVar6 = (undefined8 *)(uVar12 * 8 + *(long *)(this + 0x60));
        }
        else {
          puVar6 = *(undefined8 **)(this + 0x60);
        }
        CQuestDialog::load((CQuestDialog *)*puVar6,param_1);
      }
      uVar12 = (ulong)(uVar11 + 1);
    } while (uVar11 + 1 < local_40[0]);
  }
  fread(local_40,4,1,param_1);
  if (local_40[0] != 0) {
    uVar12 = 0;
    do {
      uVar11 = (uint)uVar12;
      if (uVar11 < *(uint *)(this + 0x80)) {
        if (uVar11 < *(uint *)(this + 0x84)) {
          puVar6 = (undefined8 *)(uVar12 * 8 + *(long *)(this + 0x78));
        }
        else {
          puVar6 = *(undefined8 **)(this + 0x78);
        }
        CQuestDialog::load((CQuestDialog *)*puVar6,param_1);
      }
      uVar12 = (ulong)(uVar11 + 1);
    } while (uVar11 + 1 < local_40[0]);
  }
  fread(local_40,4,1,param_1);
  if (local_40[0] != 0) {
    uVar12 = 0;
    do {
      uVar11 = (uint)uVar12;
      if (uVar11 < *(uint *)(this + 0x98)) {
        if (uVar11 < *(uint *)(this + 0x9c)) {
          puVar6 = (undefined8 *)(uVar12 * 8 + *(long *)(this + 0x90));
        }
        else {
          puVar6 = *(undefined8 **)(this + 0x90);
        }
        CQuestDialog::load((CQuestDialog *)*puVar6,param_1);
      }
      uVar12 = (ulong)(uVar11 + 1);
    } while (uVar11 + 1 < local_40[0]);
  }
  fread(local_40,4,1,param_1);
  if (local_40[0] != 0) {
    uVar12 = 0;
    do {
      uVar11 = (uint)uVar12;
      if (uVar11 < *(uint *)(this + 0xb0)) {
        if (uVar11 < *(uint *)(this + 0xb4)) {
          puVar6 = (undefined8 *)(uVar12 * 8 + *(long *)(this + 0xa8));
        }
        else {
          puVar6 = *(undefined8 **)(this + 0xa8);
        }
        CQuestDialog::load((CQuestDialog *)*puVar6,param_1);
      }
      uVar12 = (ulong)(uVar11 + 1);
    } while (uVar11 + 1 < local_40[0]);
  }
  fread(local_40,4,1,param_1);
  if (local_40[0] != 0) {
    uVar12 = 0;
    do {
      fread(&local_44,4,1,param_1);
      uVar10 = (uint)uVar12;
      uVar11 = local_40[0];
      if (local_44 != 0) {
        uVar3 = 0;
        uVar7 = local_44;
        do {
          if (uVar11 <= *(uint *)(this + 0x138)) {
            if (uVar10 < *(uint *)(this + 0x13c)) {
              plVar9 = (long *)(uVar12 * 8 + *(long *)(this + 0x130));
            }
            else {
              plVar9 = *(long **)(this + 0x130);
            }
            if (uVar7 <= *(uint *)(*plVar9 + 8)) {
              if (uVar10 < *(uint *)(this + 0x13c)) {
                plVar9 = (long *)(uVar12 * 8 + *(long *)(this + 0x130));
              }
              else {
                plVar9 = *(long **)(this + 0x130);
              }
              plVar9 = (long *)*plVar9;
              if (uVar3 < *(uint *)((long)plVar9 + 0xc)) {
                puVar6 = (undefined8 *)((ulong)uVar3 * 8 + *plVar9);
              }
              else {
                puVar6 = (undefined8 *)*plVar9;
              }
              CQuestUnitData::load((CQuestUnitData *)*puVar6,param_1,param_3);
              uVar7 = local_44;
              uVar11 = local_40[0];
            }
          }
          uVar3 = uVar3 + 1;
        } while (uVar3 < uVar7);
      }
      uVar12 = (ulong)(uVar10 + 1);
    } while (uVar10 + 1 < uVar11);
  }
  fread(local_40,4,1,param_1);
  if (local_40[0] != 0) {
    uVar11 = 0;
    do {
      fread(&local_44,4,1,param_1);
      uVar10 = local_40[0];
      if (local_44 != 0) {
        uVar3 = 0;
        uVar7 = local_44;
        do {
          if (uVar10 <= *(uint *)(this + 0x150)) {
            if (uVar11 < *(uint *)(this + 0x154)) {
              plVar9 = (long *)((ulong)uVar11 * 8 + *(long *)(this + 0x148));
            }
            else {
              plVar9 = *(long **)(this + 0x148);
            }
            if (uVar7 <= *(uint *)(*plVar9 + 8)) {
              if (uVar11 < *(uint *)(this + 0x154)) {
                plVar9 = (long *)((ulong)uVar11 * 8 + *(long *)(this + 0x148));
              }
              else {
                plVar9 = *(long **)(this + 0x148);
              }
              plVar9 = (long *)*plVar9;
              if (uVar3 < *(uint *)((long)plVar9 + 0xc)) {
                puVar6 = (undefined8 *)((ulong)uVar3 * 8 + *plVar9);
              }
              else {
                puVar6 = (undefined8 *)*plVar9;
              }
              CQuestUnitData::load((CQuestUnitData *)*puVar6,param_1,param_3);
              uVar7 = local_44;
              uVar10 = local_40[0];
            }
          }
          uVar3 = uVar3 + 1;
        } while (uVar3 < uVar7);
      }
      uVar11 = uVar11 + 1;
    } while (uVar11 < uVar10);
  }
  fread(local_40,4,1,param_1);
  if (local_40[0] != 0) {
    uVar11 = 0;
    do {
      fread(&local_44,4,1,param_1);
      uVar10 = local_40[0];
      if (local_44 != 0) {
        uVar12 = 0;
        uVar7 = local_44;
        do {
          uVar3 = (uint)uVar12;
          if (uVar10 <= *(uint *)(this + 0x168)) {
            if (uVar11 < *(uint *)(this + 0x16c)) {
              plVar9 = (long *)((ulong)uVar11 * 8 + *(long *)(this + 0x160));
            }
            else {
              plVar9 = *(long **)(this + 0x160);
            }
            if (uVar7 <= *(uint *)(*plVar9 + 8)) {
              if (uVar11 < *(uint *)(this + 0x16c)) {
                plVar9 = *(long **)((ulong)uVar11 * 8 + *(long *)(this + 0x160));
                if (uVar3 < *(uint *)((long)plVar9 + 0xc)) goto LAB_00d180e5;
LAB_00d18084:
                puVar6 = (undefined8 *)*plVar9;
              }
              else {
                plVar9 = (long *)**(long **)(this + 0x160);
                if (*(uint *)((long)plVar9 + 0xc) <= uVar3) goto LAB_00d18084;
LAB_00d180e5:
                puVar6 = (undefined8 *)(uVar12 * 8 + *plVar9);
              }
              CQuestUnitData::load((CQuestUnitData *)*puVar6,param_1,param_3);
              uVar7 = local_44;
              uVar10 = local_40[0];
            }
          }
          uVar12 = (ulong)(uVar3 + 1);
        } while (uVar3 + 1 < uVar7);
      }
      uVar11 = uVar11 + 1;
    } while (uVar11 < uVar10);
  }
  this[0x26] = (CQuest)0x1;
  return;
}

/* address=00d181a0
   symbol=CQuest::replaceStringTags */

/* WARNING: Removing unreachable block (ram,0x00d1956c) */
/* WARNING: Removing unreachable block (ram,0x00d196f3) */
/* WARNING: Removing unreachable block (ram,0x00d18c8a) */
/* WARNING: Removing unreachable block (ram,0x00d1933c) */
/* WARNING: Removing unreachable block (ram,0x00d19675) */
/* WARNING: Removing unreachable block (ram,0x00d19509) */
/* WARNING: Removing unreachable block (ram,0x00d193df) */
/* WARNING: Removing unreachable block (ram,0x00d1932e) */
/* WARNING: Removing unreachable block (ram,0x00d191a1) */
/* WARNING: Removing unreachable block (ram,0x00d1913d) */
/* WARNING: Removing unreachable block (ram,0x00d19002) */
/* WARNING: Removing unreachable block (ram,0x00d1900d) */
/* WARNING: Removing unreachable block (ram,0x00d18ee3) */
/* WARNING: Removing unreachable block (ram,0x00d18eee) */
/* WARNING: Removing unreachable block (ram,0x00d18dbd) */
/* WARNING: Removing unreachable block (ram,0x00d18dc8) */
/* WARNING: Removing unreachable block (ram,0x00d18daf) */
/* WARNING: Removing unreachable block (ram,0x00d18dd6) */
/* WARNING: Removing unreachable block (ram,0x00d18ed5) */
/* WARNING: Removing unreachable block (ram,0x00d18efc) */
/* WARNING: Removing unreachable block (ram,0x00d18ff4) */
/* WARNING: Removing unreachable block (ram,0x00d1901b) */
/* WARNING: Removing unreachable block (ram,0x00d190a5) */
/* WARNING: Removing unreachable block (ram,0x00d19148) */
/* WARNING: Removing unreachable block (ram,0x00d191ed) */
/* WARNING: Removing unreachable block (ram,0x00d19323) */
/* WARNING: Removing unreachable block (ram,0x00d1944d) */
/* WARNING: Removing unreachable block (ram,0x00d196ac) */
/* WARNING: Removing unreachable block (ram,0x00d196d3) */
/* WARNING: Removing unreachable block (ram,0x00d194fe) */
/* WARNING: Removing unreachable block (ram,0x00d193d4) */
/* WARNING: Removing unreachable block (ram,0x00d19315) */
/* WARNING: Removing unreachable block (ram,0x00d19442) */
/* WARNING: Removing unreachable block (ram,0x00d190b0) */
/* WARNING: Removing unreachable block (ram,0x00d19577) */
/* WARNING: Removing unreachable block (ram,0x00d196ba) */
/* WARNING: Removing unreachable block (ram,0x00d196c5) */
/* CQuest::replaceStringTags(std::wstring const&) */

wstring_conflict * CQuest::replaceStringTags(wstring_conflict *param_1)

{
  int *piVar1;
  undefined8 uVar2;
  CQuestUnitData *this;
  char cVar3;
  uint uVar4;
  int iVar5;
  undefined8 *puVar6;
  long *plVar7;
  wstring_conflict *in_RDX;
  ulong uVar8;
  uint uVar9;
  long in_RSI;
  wchar_t *pwVar10;
  long lVar11;
  bool bVar12;
  uint local_2d0;
  uint local_2c4;
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
  undefined4 *local_188 [2];
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
  long local_78 [7];
  allocator local_3e;
  allocator local_3d;
  allocator local_3c;
  allocator local_3b;
  allocator local_3a;
  allocator local_39 [9];

  std::wstring::wstring(param_1,in_RDX);
  if (*(uint *)(in_RSI + 0x138) != 0) {
    lVar11 = 0;
    uVar9 = 0;
    do {
      uVar4 = 0;
      while( true ) {
        plVar7 = (long *)((long)*(long **)(in_RSI + 0x130) + lVar11);
        if (*(uint *)(in_RSI + 0x13c) <= uVar9) {
          plVar7 = *(long **)(in_RSI + 0x130);
        }
        if (*(uint *)(*plVar7 + 8) <= uVar4) break;
        uVar4 = uVar4 + 1;
      }
      uVar9 = uVar9 + 1;
      lVar11 = lVar11 + 8;
    } while (uVar9 < *(uint *)(in_RSI + 0x138));
  }
  if (*(uint *)(in_RSI + 0x150) != 0) {
    lVar11 = 0;
    uVar9 = 0;
    do {
      uVar4 = 0;
      while( true ) {
        plVar7 = (long *)((long)*(long **)(in_RSI + 0x148) + lVar11);
        if (*(uint *)(in_RSI + 0x154) <= uVar9) {
          plVar7 = *(long **)(in_RSI + 0x148);
        }
        if (*(uint *)(*plVar7 + 8) <= uVar4) break;
        uVar4 = uVar4 + 1;
      }
      uVar9 = uVar9 + 1;
      lVar11 = lVar11 + 8;
    } while (uVar9 < *(uint *)(in_RSI + 0x150));
  }
                    /* try { // try from 00d182e2 to 00d182e6 has its CatchHandler @ 00d18c95 */
  STRINGS::GetValueAsWString((STRINGS *)local_78,*(int *)(in_RSI + 0x20) + 1);
                    /* try { // try from 00d182ff to 00d18303 has its CatchHandler @ 00d18ca8 */
  std::wstring::wstring((wstring_conflict *)local_98,L"[DEPTH]",local_39);
                    /* try { // try from 00d18312 to 00d18316 has its CatchHandler @ 00d18cba */
  std::wstring::wstring((wstring_conflict *)local_88,param_1);
                    /* try { // try from 00d18330 to 00d18334 has its CatchHandler @ 00d18cc7 */
  STRINGS::replaceWString
            ((STRINGS *)local_a8,(wstring_conflict *)local_88,(wstring_conflict *)local_98,local_78)
  ;
                    /* try { // try from 00d1833b to 00d1833f has its CatchHandler @ 00d18cd4 */
  std::wstring::assign(param_1);
  if ((allocator *)(local_a8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_a8[0] + -8);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
    }
  }
  if ((allocator *)(local_88[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_88[0] + -8);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
    }
  }
  if ((allocator *)(local_98[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_98[0] + -8);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
    }
  }
  if ((allocator *)(local_78[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_78[0] + -8);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_78[0] + -0x18));
    }
  }
                    /* try { // try from 00d183a4 to 00d183a8 has its CatchHandler @ 00d18c95 */
  STRINGS::GetValueAsWString((uint)local_b8);
                    /* try { // try from 00d183c1 to 00d183c5 has its CatchHandler @ 00d18d9a */
  std::wstring::wstring((wstring_conflict *)local_d8,L"[DEFEATCOMPLETECOUNT]",&local_3a);
                    /* try { // try from 00d183d4 to 00d183d8 has its CatchHandler @ 00d18de1 */
  std::wstring::wstring((wstring_conflict *)local_c8,param_1);
                    /* try { // try from 00d183f2 to 00d183f6 has its CatchHandler @ 00d18dee */
  STRINGS::replaceWString
            ((STRINGS *)local_e8,(wstring_conflict *)local_c8,(wstring_conflict *)local_d8,local_b8)
  ;
                    /* try { // try from 00d183fd to 00d18401 has its CatchHandler @ 00d18dfb */
  std::wstring::assign(param_1);
  if ((allocator *)(local_e8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_e8[0] + -8);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_e8[0] + -0x18));
    }
  }
  if ((allocator *)(local_c8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_c8[0] + -8);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
    }
  }
  if ((allocator *)(local_d8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_d8[0] + -8);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_d8[0] + -0x18));
    }
  }
  if ((allocator *)(local_b8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_b8[0] + -8);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
    }
  }
                    /* try { // try from 00d18460 to 00d18464 has its CatchHandler @ 00d18c95 */
  STRINGS::GetValueAsWString((uint)local_f8);
                    /* try { // try from 00d1847d to 00d18481 has its CatchHandler @ 00d18ec0 */
  std::wstring::wstring((wstring_conflict *)local_118,L"[ACQUIRECOMPLETECOUNT]",&local_3b);
                    /* try { // try from 00d18490 to 00d18494 has its CatchHandler @ 00d18f07 */
  std::wstring::wstring((wstring_conflict *)local_108,param_1);
                    /* try { // try from 00d184ae to 00d184b2 has its CatchHandler @ 00d18f14 */
  STRINGS::replaceWString
            ((STRINGS *)local_128,(wstring_conflict *)local_108,(wstring_conflict *)local_118,
             local_f8);
                    /* try { // try from 00d184b9 to 00d184bd has its CatchHandler @ 00d18f22 */
  std::wstring::assign(param_1);
  if ((allocator *)(local_128[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_128[0] + -8);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_128[0] + -0x18));
    }
  }
  if ((allocator *)(local_108[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_108[0] + -8);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_108[0] + -0x18));
    }
  }
  if ((allocator *)(local_118[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_118[0] + -8);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_118[0] + -0x18));
    }
  }
  if ((allocator *)(local_f8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_f8[0] + -8);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
    }
  }
  if (*(int *)(in_RSI + 0x138) != 0) {
    uVar8 = 0;
    do {
      if ((uint)uVar8 < *(uint *)(in_RSI + 0x13c)) {
        puVar6 = (undefined8 *)(uVar8 * 8 + *(long *)(in_RSI + 0x130));
      }
      else {
        puVar6 = *(undefined8 **)(in_RSI + 0x130);
      }
      uVar2 = **(undefined8 **)*puVar6;
                    /* try { // try from 00d18560 to 00d18564 has its CatchHandler @ 00d18fe7 */
      std::wstring::wstring((wstring_conflict *)local_138,L"[ACQUIRE",&local_3c);
                    /* try { // try from 00d18575 to 00d18579 has its CatchHandler @ 00d19026 */
      getAcquireTags(local_148,uVar2,(wstring_conflict *)local_138,uVar8,param_1);
                    /* try { // try from 00d18582 to 00d18586 has its CatchHandler @ 00d1903b */
      std::wstring::assign(param_1);
      if ((allocator *)(local_148[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_148[0] + -8);
        iVar5 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar5 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_148[0] + -0x18));
        }
      }
      if ((allocator *)(local_138[0] + -0x18) !=
          (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(local_138[0] + -8);
        iVar5 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar5 < 1) {
          std::wstring::_Rep::_M_destroy((allocator *)(local_138[0] + -0x18));
        }
      }
      uVar9 = (uint)uVar8 + 1;
      uVar8 = (ulong)uVar9;
    } while (uVar9 < *(uint *)(in_RSI + 0x138));
  }
                    /* try { // try from 00d185f4 to 00d185f8 has its CatchHandler @ 00d18c95 */
  lVar11 = CResourceManager::getDungeonByName
                     (*(CResourceManager **)(in_RSI + 0x1d8),(wstring_conflict *)(in_RSI + 0x30));
  if (lVar11 != 0) {
                    /* try { // try from 00d1861e to 00d18622 has its CatchHandler @ 00d190bb */
    std::wstring::wstring((wstring_conflict *)local_168,L"[DUNEGONNAME]",&local_3d);
                    /* try { // try from 00d18631 to 00d18635 has its CatchHandler @ 00d190c0 */
    std::wstring::wstring((wstring_conflict *)local_158,param_1);
                    /* try { // try from 00d1864a to 00d1864e has its CatchHandler @ 00d190c8 */
    STRINGS::replaceWString
              ((STRINGS *)local_178,(wstring_conflict *)local_158,(wstring_conflict *)local_168,
               lVar11 + 0x68);
                    /* try { // try from 00d18655 to 00d18659 has its CatchHandler @ 00d190d8 */
    std::wstring::assign(param_1);
    if ((allocator *)(local_178[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_178[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_178[0] + -0x18));
      }
    }
    if ((allocator *)(local_158[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_158[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_158[0] + -0x18));
      }
    }
    if ((allocator *)(local_168[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_168[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_168[0] + -0x18));
      }
    }
  }
  if (*(int *)(in_RSI + 0x150) != 0) {
    local_2d0 = 1;
    local_2c4 = 0;
    do {
      if (local_2c4 < *(uint *)(in_RSI + 0x154)) {
        puVar6 = (undefined8 *)((ulong)local_2c4 * 8 + *(long *)(in_RSI + 0x148));
      }
      else {
        puVar6 = *(undefined8 **)(in_RSI + 0x148);
      }
      this = (CQuestUnitData *)**(undefined8 **)*puVar6;
      if (this != (CQuestUnitData *)0x0) {
                    /* try { // try from 00d186fa to 00d186fe has its CatchHandler @ 00d18c95 */
        STRINGS::GetValueAsWString((uint)local_198);
        wcslen(L"[DEFEAT");
        local_188[0] = &DAT_01424558;
                    /* try { // try from 00d1872f to 00d1875d has its CatchHandler @ 00d1917f */
        std::wstring::reserve((ulong)local_188);
        std::wstring::append((wchar_t *)local_188,0xff6cf8);
        std::wstring::append((wstring_conflict *)local_188);
        if ((allocator *)(local_198[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_198[0] + -8);
          iVar5 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar5 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_198[0] + -0x18));
          }
        }
                    /* try { // try from 00d1877e to 00d18782 has its CatchHandler @ 00d191d8 */
        STRINGS::GetValueAsWString((uint)local_1b8);
                    /* try { // try from 00d18793 to 00d18797 has its CatchHandler @ 00d191f8 */
        std::wstring::wstring((wstring_conflict *)local_1a8,(wstring_conflict *)local_188);
        wcslen(L"COUNT]");
                    /* try { // try from 00d187b2 to 00d187b6 has its CatchHandler @ 00d1920a */
        std::wstring::append((wchar_t *)local_1a8,0xff6948);
                    /* try { // try from 00d187c5 to 00d187c9 has its CatchHandler @ 00d1921c */
        std::wstring::wstring((wstring_conflict *)local_1c8,param_1);
                    /* try { // try from 00d187e8 to 00d187ec has its CatchHandler @ 00d1922e */
        STRINGS::replaceWString
                  ((STRINGS *)local_1d8,(wstring_conflict *)local_1c8,local_1a8,local_1b8);
                    /* try { // try from 00d187f3 to 00d187f7 has its CatchHandler @ 00d1923b */
        std::wstring::assign(param_1);
        if ((allocator *)(local_1d8[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_1d8[0] + -8);
          iVar5 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar5 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_1d8[0] + -0x18));
          }
        }
        if ((allocator *)(local_1c8[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_1c8[0] + -8);
          iVar5 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar5 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_1c8[0] + -0x18));
          }
        }
        if ((allocator *)(local_1a8[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_1a8[0] + -8);
          iVar5 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar5 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_1a8[0] + -0x18));
          }
        }
        if ((allocator *)(local_1b8[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_1b8[0] + -8);
          iVar5 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar5 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_1b8[0] + -0x18));
          }
        }
                    /* try { // try from 00d1884f to 00d18863 has its CatchHandler @ 00d191d8 */
        iVar5 = CQuestUnitData::getDungeonFloorActiveOn(this);
        STRINGS::GetValueAsWString((STRINGS *)local_1f8,iVar5 + 1);
                    /* try { // try from 00d18877 to 00d1887b has its CatchHandler @ 00d19300 */
        std::wstring::wstring((wstring_conflict *)local_1e8,(wstring_conflict *)local_188);
        wcslen(L"DEPTH]");
                    /* try { // try from 00d18891 to 00d18895 has its CatchHandler @ 00d19347 */
        std::wstring::append((wchar_t *)local_1e8,0xff6964);
                    /* try { // try from 00d188a4 to 00d188a8 has its CatchHandler @ 00d19354 */
        std::wstring::wstring((wstring_conflict *)local_208,param_1);
                    /* try { // try from 00d188c2 to 00d188c6 has its CatchHandler @ 00d19362 */
        STRINGS::replaceWString
                  ((STRINGS *)local_218,(wstring_conflict *)local_208,(wstring_conflict *)local_1e8,
                   local_1f8);
                    /* try { // try from 00d188cd to 00d188d1 has its CatchHandler @ 00d1936f */
        std::wstring::assign(param_1);
        if ((allocator *)(local_218[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_218[0] + -8);
          iVar5 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar5 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_218[0] + -0x18));
          }
        }
        if ((allocator *)(local_208[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_208[0] + -8);
          iVar5 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar5 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_208[0] + -0x18));
          }
        }
        if ((allocator *)(local_1e8[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_1e8[0] + -8);
          iVar5 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar5 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_1e8[0] + -0x18));
          }
        }
        if ((allocator *)(local_1f8[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_1f8[0] + -8);
          iVar5 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar5 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_1f8[0] + -0x18));
          }
        }
                    /* try { // try from 00d1892e to 00d18957 has its CatchHandler @ 00d19458 */
        cVar3 = CQuestUnitData::isComplete(this,true);
        pwVar10 = L"Incomplete";
        if (cVar3 != '\0') {
          pwVar10 = L"Complete";
        }
        std::wstring::wstring((wstring_conflict *)local_248,pwVar10,&local_3e);
                    /* try { // try from 00d1896b to 00d1896f has its CatchHandler @ 00d1945d */
        std::wstring::wstring((wstring_conflict *)local_228,(wstring_conflict *)local_188);
        wcslen(L"COMPLETE]");
                    /* try { // try from 00d18985 to 00d18989 has its CatchHandler @ 00d19472 */
        std::wstring::append((wchar_t *)local_228,0xff6b98);
                    /* try { // try from 00d18998 to 00d1899c has its CatchHandler @ 00d1947f */
        std::wstring::wstring((wstring_conflict *)local_238,param_1);
                    /* try { // try from 00d189b6 to 00d189ba has its CatchHandler @ 00d1948c */
        STRINGS::replaceWString
                  ((STRINGS *)local_258,(wstring_conflict *)local_238,(wstring_conflict *)local_228,
                   local_248);
                    /* try { // try from 00d189c1 to 00d189c5 has its CatchHandler @ 00d19499 */
        std::wstring::assign(param_1);
        if ((allocator *)(local_258[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_258[0] + -8);
          iVar5 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar5 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_258[0] + -0x18));
          }
        }
        if ((allocator *)(local_238[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_238[0] + -8);
          iVar5 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar5 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_238[0] + -0x18));
          }
        }
        if ((allocator *)(local_228[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_228[0] + -8);
          iVar5 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar5 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_228[0] + -0x18));
          }
        }
        if ((allocator *)(local_248[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_248[0] + -8);
          iVar5 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar5 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_248[0] + -0x18));
          }
        }
                    /* try { // try from 00d18a22 to 00d18a26 has its CatchHandler @ 00d191d8 */
        CQuestUnitData::getUnitName();
                    /* try { // try from 00d18a37 to 00d18a3b has its CatchHandler @ 00d19582 */
        std::wstring::wstring((wstring_conflict *)local_268,(wstring_conflict *)local_188);
        wcslen(L"]");
                    /* try { // try from 00d18a51 to 00d18a55 has its CatchHandler @ 00d19594 */
        std::wstring::append((wchar_t *)local_268,0xfee368);
                    /* try { // try from 00d18a61 to 00d18a65 has its CatchHandler @ 00d195a2 */
        std::wstring::wstring((wstring_conflict *)local_288,param_1);
                    /* try { // try from 00d18a79 to 00d18a7d has its CatchHandler @ 00d195af */
        STRINGS::replaceWString
                  ((STRINGS *)local_298,(wstring_conflict *)local_288,(wstring_conflict *)local_268,
                   local_278);
                    /* try { // try from 00d18a84 to 00d18a88 has its CatchHandler @ 00d195bc */
        std::wstring::assign(param_1);
        if ((allocator *)(local_298[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_298[0] + -8);
          iVar5 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar5 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_298[0] + -0x18));
          }
        }
        if ((allocator *)(local_288[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_288[0] + -8);
          iVar5 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar5 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_288[0] + -0x18));
          }
        }
        if ((allocator *)(local_268[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_268[0] + -8);
          iVar5 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar5 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_268[0] + -0x18));
          }
        }
        if ((allocator *)(local_278[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_278[0] + -8);
          iVar5 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar5 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_278[0] + -0x18));
          }
        }
        if (*(int *)(this + 0x50) != 0) {
          uVar8 = 0;
          do {
            if ((uint)uVar8 < *(uint *)(this + 0x54)) {
              puVar6 = (undefined8 *)(uVar8 * 8 + *(long *)(this + 0x48));
            }
            else {
              puVar6 = *(undefined8 **)(this + 0x48);
            }
            uVar2 = *puVar6;
                    /* try { // try from 00d18b02 to 00d18b06 has its CatchHandler @ 00d191d8 */
            std::wstring::wstring((wstring_conflict *)local_2a8,(wstring_conflict *)local_188);
            wcslen(L"ACQUIRE");
                    /* try { // try from 00d18b1c to 00d18b20 has its CatchHandler @ 00d19665 */
            std::wstring::append((wchar_t *)local_2a8,0xff6d18);
                    /* try { // try from 00d18b31 to 00d18b35 has its CatchHandler @ 00d19629 */
            getAcquireTags(local_2b8,uVar2,(wstring_conflict *)local_2a8,uVar8,param_1);
                    /* try { // try from 00d18b3e to 00d18b42 has its CatchHandler @ 00d196e1 */
            std::wstring::assign(param_1);
            if ((allocator *)(local_2b8[0] + -0x18) !=
                (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar1 = (int *)(local_2b8[0] + -8);
              iVar5 = *piVar1;
              *piVar1 = *piVar1 + -1;
              UNLOCK();
              if (iVar5 < 1) {
                std::wstring::_Rep::_M_destroy((allocator *)(local_2b8[0] + -0x18));
              }
            }
            if ((allocator *)(local_2a8[0] + -0x18) !=
                (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
              LOCK();
              piVar1 = (int *)(local_2a8[0] + -8);
              iVar5 = *piVar1;
              *piVar1 = *piVar1 + -1;
              UNLOCK();
              if (iVar5 < 1) {
                std::wstring::_Rep::_M_destroy((allocator *)(local_2a8[0] + -0x18));
              }
            }
            uVar9 = (uint)uVar8 + 1;
            uVar8 = (ulong)uVar9;
          } while (uVar9 < *(uint *)(this + 0x50));
        }
        if ((allocator *)(local_188[0] + -6) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = local_188[0] + -2;
          iVar5 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar5 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_188[0] + -6));
          }
        }
      }
      local_2c4 = local_2c4 + 1;
      bVar12 = local_2d0 < *(uint *)(in_RSI + 0x150);
      local_2d0 = local_2d0 + 1;
    } while (bVar12);
  }
  return param_1;
}

/* address=00d19710
   symbol=CQuest::getQuestDetails */

/* WARNING: Removing unreachable block (ram,0x00d197b9) */
/* CQuest::getQuestDetails() */

void CQuest::getQuestDetails(void)

{
  int *piVar1;
  int iVar2;
  long in_RSI;
  wstring_conflict *in_RDI;
  long local_28;

  if (*(long *)(in_RSI + 0xc0) == 0) {
    std::wstring::wstring(in_RDI,(wstring_conflict *)&::EMPTY_WSTRING);
  }
  else {
    CQuestDialog::getDialog(true);
                    /* try { // try from 00d19748 to 00d1974c has its CatchHandler @ 00d197a6 */
    replaceStringTags(in_RDI);
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

/* address=00d197d0
   symbol=CQuest::initializeQuestWithNPC */

/* WARNING: Removing unreachable block (ram,0x00d199fd) */
/* CQuest::initializeQuestWithNPC(CBaseUnit*) */

void __thiscall CQuest::initializeQuestWithNPC(CQuest *this,CBaseUnit *param_1)

{
  int *piVar1;
  long lVar2;
  char cVar3;
  int iVar4;
  undefined4 uVar5;
  CDungeon *pCVar6;
  long lVar7;
  int iVar8;
  CLevel *pCVar9;
  CPlayer *pCVar10;
  CGameClient *this_00;
  long local_38 [2];

  if (((param_1 == (CBaseUnit *)0x0) || (*(long *)(this + 0x1e8) != *(long *)(param_1 + 0x1b0))) &&
     ((cVar3 = CQuestManager::getPlayerHasQuest(*(CQuestManager **)(this + 0x1d0),this),
      cVar3 == '\0' || (param_1 == (CBaseUnit *)0x0)))) {
    pCVar6 = (CDungeon *)
             CResourceManager::getDungeonByName
                       (*(CResourceManager **)(this + 0x1d8),(wstring_conflict *)(this + 0x30));
    if ((((pCVar6 != (CDungeon *)0x0) && (lVar2 = *(long *)(this + 0x1d8), lVar2 != 0)) &&
        (*(int *)(lVar2 + 0x30) != 0)) && (**(long **)(lVar2 + 0x28) != 0)) {
      if (((this[0x20a] != (CQuest)0x0) && (*(long *)(this + 0x1d0) != 0)) &&
         (*(long *)(*(long *)(this + 0x1d0) + 0x10) != 0)) {
        std::wstring::wstring((wstring_conflict *)local_38,(wstring_conflict *)(this + 0x30));
        pCVar10 = (CPlayer *)0x0;
        if (*(long *)(this + 0x1d0) != 0) {
          pCVar10 = *(CPlayer **)(*(long *)(this + 0x1d0) + 0x10);
        }
                    /* try { // try from 00d198c6 to 00d198ca has its CatchHandler @ 00d199ea */
        CPlayer::clearDungeonHistory(pCVar10);
        if ((allocator *)(local_38[0] + -0x18) !=
            (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(local_38[0] + -8);
          iVar4 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar4 < 1) {
            std::wstring::_Rep::_M_destroy((allocator *)(local_38[0] + -0x18));
          }
        }
        lVar2 = *(long *)(this + 0x1d0);
        lVar7 = 0;
        if (lVar2 != 0) {
          lVar7 = *(long *)(lVar2 + 0x10);
        }
        pCVar9 = (CLevel *)0x0;
        if (*(long *)(lVar7 + 0x68) != 0) {
          pCVar9 = *(CLevel **)(*(long *)(lVar7 + 0x68) + 0x18);
        }
        pCVar10 = (CPlayer *)0x0;
        if (lVar2 != 0) {
          pCVar10 = *(CPlayer **)(lVar2 + 0x10);
        }
        CPlayer::updateStoredLevels(pCVar10,pCVar9);
      }
      iVar4 = getDungeonMaxFloor(this);
      this_00 = (CGameClient *)0x0;
      if (*(int *)(*(long *)(this + 0x1d8) + 0x30) != 0) {
        this_00 = (CGameClient *)**(undefined8 **)(*(long *)(this + 0x1d8) + 0x28);
      }
      iVar8 = 1;
      if (0 < iVar4) {
        iVar8 = iVar4;
      }
      uVar5 = CGameClient::getRankOfMonstersOnFloor(this_00,iVar8,pCVar6,true);
      *(undefined4 *)(this + 0x20c) = uVar5;
    }
    if (param_1 == (CBaseUnit *)0x0) {
      reinitializeQuest(this,false,false);
    }
    else {
      uVar5 = UTILITIES::randomIntegerBetweenVolatile(0,0x7fffffff);
      *(undefined4 *)(this + 0x1c) = uVar5;
      reinitializeQuest(this,true,false);
      *(undefined8 *)(this + 0x1e8) = *(undefined8 *)(param_1 + 0x1b0);
      if ((*(long *)(this + 0x128) != 0) && (this[0x2d] != (CQuest)0x0)) {
        this[0x2d] = (CQuest)0x0;
        CQuestRewards::reInitializeRewards(*(CQuestRewards **)(this + 0x128));
      }
    }
  }
  return;
}

/* address=00d19a10
   symbol=CQuest::calculateUnitsFromTag */

/* WARNING: Removing unreachable block (ram,0x00d1a375) */
/* WARNING: Removing unreachable block (ram,0x00d1a322) */
/* WARNING: Removing unreachable block (ram,0x00d1a385) */
/* WARNING: Removing unreachable block (ram,0x00d1a259) */
/* WARNING: Removing unreachable block (ram,0x00d1a2db) */
/* WARNING: Removing unreachable block (ram,0x00d1a24e) */
/* CQuest::calculateUnitsFromTag(CDataGroup*, TArrayList<TArrayList<CQuestUnitData*>*>*,
   TArrayList<CQuestUnitData*>*, unsigned int) */

uint __thiscall
CQuest::calculateUnitsFromTag
          (CQuest *this,CDataGroup *param_1,TArrayList *param_2,TArrayList *param_3,uint param_4)

{
  int *piVar1;
  int iVar2;
  char cVar3;
  uint uVar4;
  uint uVar5;
  long lVar6;
  CQuestUnitData *this_00;
  undefined8 uVar7;
  undefined8 *puVar8;
  void *pvVar9;
  CDataGroup *pCVar10;
  CQuestUnitData *this_01;
  ulong uVar11;
  uint uVar12;
  long *plVar13;
  uint uVar14;
  uint local_dc;
  uint local_d0;
  void *local_c8;
  long local_c0;
  undefined8 local_b8;
  long local_a8 [2];
  long local_98 [2];
  long local_88 [2];
  long local_78 [2];
  long local_68 [2];
  long local_58 [3];
  allocator local_3e;
  allocator local_3d;
  allocator local_3c;
  allocator local_3b;
  allocator local_3a;
  allocator local_39 [9];

  if ((param_1 == (CDataGroup *)0x0) ||
     ((param_3 == (TArrayList *)0x0 && (param_2 == (TArrayList *)0x0)))) {
    local_d0 = 0;
  }
  else {
                    /* try { // try from 00d19a7b to 00d19a7f has its CatchHandler @ 00d1a383 */
    std::wstring::wstring((wstring_conflict *)local_58,L"MINCREATE",local_39);
                    /* try { // try from 00d19a88 to 00d19a8c has its CatchHandler @ 00d1a361 */
    local_d0 = CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_58,0);
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
                    /* try { // try from 00d19ac1 to 00d19ac5 has its CatchHandler @ 00d1a32d */
    std::wstring::wstring((wstring_conflict *)local_68,L"MAXCREATE",&local_3a);
                    /* try { // try from 00d19ace to 00d19ad2 has its CatchHandler @ 00d1a312 */
    uVar4 = CDataGroup::GetDataValue(param_1,(wstring_conflict *)local_68,0);
    if ((int)local_d0 < 1) {
      local_d0 = 1;
    }
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
    if (uVar4 < local_d0) {
      uVar4 = local_d0;
    }
    this[0x27] = (CQuest)(local_d0 == uVar4 && local_d0 == 0);
    local_c8 = (void *)0x0;
    local_c0 = 0;
    local_b8 = 0;
                    /* try { // try from 00d19b55 to 00d19b59 has its CatchHandler @ 00d1a21f */
    std::wstring::wstring((wstring_conflict *)local_78,L"UNIT",&local_3b);
                    /* try { // try from 00d19b65 to 00d19b69 has its CatchHandler @ 00d1a212 */
    CDataGroup::GetDataGroupsMatchingName(param_1,(wstring_conflict *)local_78,(vector *)&local_c8);
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
    lVar6 = local_c0 - (long)local_c8 >> 3;
    if (lVar6 == 0) {
      local_d0 = 0;
    }
    else {
      local_dc = 0;
      if (this[0x27] != (CQuest)0x0) {
        local_d0 = (uint)lVar6;
      }
      uVar11 = 0;
      do {
        this_00 = (CQuestUnitData *)Ogre::NedAllocImpl::allocBytes(200,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00d19c0d to 00d19c11 has its CatchHandler @ 00d1a277 */
        CQuestUnitData::CQuestUnitData(this_00,this);
        lVar6 = uVar11 * 8;
                    /* try { // try from 00d19c28 to 00d19d45 has its CatchHandler @ 00d1a1f8 */
        cVar3 = CQuestUnitData::parseDataGroup
                          (this_00,*(CDataGroup **)((long)local_c8 + uVar11 * 8),(CDataGroup *)0x0);
        if (cVar3 == '\0') {
          if (this_00 != (CQuestUnitData *)0x0) {
                    /* try { // try from 00d19bcc to 00d19c01 has its CatchHandler @ 00d1a1f8 */
            (**(code **)(*(long *)this_00 + 8))(this_00);
          }
        }
        else {
          *(uint *)(this_00 + 0xb4) = param_4;
          uVar7 = CQuestUnitData::getBaseUnitDataGroup(this_00);
          *(undefined8 *)(this_00 + 0x20) = uVar7;
          if (param_2 == (TArrayList *)0x0) {
            if (param_3 != (TArrayList *)0x0) {
              uVar4 = *(uint *)(param_3 + 8);
              if (uVar4 < *(uint *)(param_3 + 0xc)) {
                pvVar9 = *(void **)param_3;
              }
              else if (*(long *)param_3 == 0) {
                *(uint *)(param_3 + 0xc) = *(uint *)(param_3 + 0x10);
                pvVar9 = operator_new__((ulong)*(uint *)(param_3 + 0x10) * 8);
                *(void **)param_3 = pvVar9;
                uVar4 = *(uint *)(param_3 + 8);
              }
              else {
                uVar5 = *(uint *)(param_3 + 0xc) + *(int *)(param_3 + 0x10);
                pvVar9 = operator_new__((ulong)uVar5 << 3);
                if (*(int *)(param_3 + 0xc) != 0) {
                  uVar4 = 0;
                  do {
                    uVar11 = (ulong)uVar4;
                    uVar4 = uVar4 + 1;
                    *(undefined8 *)((long)pvVar9 + uVar11 * 8) =
                         *(undefined8 *)(*(long *)param_3 + uVar11 * 8);
                  } while (uVar4 < *(uint *)(param_3 + 0xc));
                }
                if (*(void **)param_3 != (void *)0x0) {
                  operator_delete__(*(void **)param_3);
                }
                uVar4 = *(uint *)(param_3 + 8);
                *(void **)param_3 = pvVar9;
                *(uint *)(param_3 + 0xc) = uVar5;
              }
              *(CQuestUnitData **)((long)pvVar9 + (ulong)uVar4 * 8) = this_00;
              *(int *)(param_3 + 8) = *(int *)(param_3 + 8) + 1;
                    /* try { // try from 00d1a099 to 00d1a09d has its CatchHandler @ 00d1a264 */
              std::wstring::wstring((wstring_conflict *)local_a8,L"ACQUIRE",&local_3e);
                    /* try { // try from 00d1a0ae to 00d1a0ca has its CatchHandler @ 00d1a363 */
              pCVar10 = (CDataGroup *)
                        CDataGroup::GetDataGroupByName
                                  (*(CDataGroup **)((long)local_c8 + lVar6),
                                   (wstring_conflict *)local_a8,false);
              calculateUnitsFromTag(this,pCVar10,(TArrayList *)0x0,(TArrayList *)(this_00 + 0x48),1)
              ;
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
            }
          }
          else {
            uVar4 = *(uint *)(param_2 + 8);
            puVar8 = (undefined8 *)Ogre::NedAllocImpl::allocBytes(0x18,(char *)0x0,0,(char *)0x0);
            *puVar8 = 0;
            *(undefined4 *)(puVar8 + 1) = 0;
            *(undefined4 *)((long)puVar8 + 0xc) = 0;
            *(undefined4 *)(puVar8 + 2) = 1;
            uVar5 = *(uint *)(param_2 + 8);
            if (uVar5 < *(uint *)(param_2 + 0xc)) {
              pvVar9 = *(void **)param_2;
            }
            else if (*(long *)param_2 == 0) {
              *(uint *)(param_2 + 0xc) = *(uint *)(param_2 + 0x10);
              pvVar9 = operator_new__((ulong)*(uint *)(param_2 + 0x10) * 8);
              *(void **)param_2 = pvVar9;
              uVar5 = *(uint *)(param_2 + 8);
            }
            else {
              uVar14 = *(int *)(param_2 + 0x10) + *(uint *)(param_2 + 0xc);
              pvVar9 = operator_new__((ulong)uVar14 << 3);
              if (*(int *)(param_2 + 0xc) != 0) {
                uVar5 = 0;
                do {
                  uVar11 = (ulong)uVar5;
                  uVar5 = uVar5 + 1;
                  *(undefined8 *)((long)pvVar9 + uVar11 * 8) =
                       *(undefined8 *)(*(long *)param_2 + uVar11 * 8);
                } while (uVar5 < *(uint *)(param_2 + 0xc));
              }
              if (*(void **)param_2 != (void *)0x0) {
                operator_delete__(*(void **)param_2);
              }
              uVar5 = *(uint *)(param_2 + 8);
              *(void **)param_2 = pvVar9;
              *(uint *)(param_2 + 0xc) = uVar14;
            }
            *(undefined8 **)((long)pvVar9 + (ulong)uVar5 * 8) = puVar8;
            *(int *)(param_2 + 8) = *(int *)(param_2 + 8) + 1;
            if (uVar4 < *(uint *)(param_2 + 0xc)) {
              plVar13 = *(long **)((ulong)uVar4 * 8 + *(long *)param_2);
              uVar14 = *(uint *)(plVar13 + 1);
              uVar5 = *(uint *)((long)plVar13 + 0xc);
              if (uVar14 < uVar5) goto LAB_00d19fe3;
LAB_00d19d29:
              if (*plVar13 == 0) {
                *(uint *)((long)plVar13 + 0xc) = *(uint *)(plVar13 + 2);
                    /* try { // try from 00d1a164 to 00d1a1b3 has its CatchHandler @ 00d1a1f8 */
                pvVar9 = operator_new__((ulong)*(uint *)(plVar13 + 2) * 8);
                *plVar13 = (long)pvVar9;
                uVar14 = *(uint *)(plVar13 + 1);
              }
              else {
                uVar5 = (int)plVar13[2] + uVar5;
                pvVar9 = operator_new__((ulong)uVar5 << 3);
                if (*(int *)((long)plVar13 + 0xc) != 0) {
                  uVar14 = 0;
                  do {
                    uVar11 = (ulong)uVar14;
                    uVar14 = uVar14 + 1;
                    *(undefined8 *)((long)pvVar9 + uVar11 * 8) =
                         *(undefined8 *)(*plVar13 + uVar11 * 8);
                  } while (uVar14 < *(uint *)((long)plVar13 + 0xc));
                }
                if ((void *)*plVar13 != (void *)0x0) {
                  operator_delete__((void *)*plVar13);
                }
                uVar14 = *(uint *)(plVar13 + 1);
                *plVar13 = (long)pvVar9;
                *(uint *)((long)plVar13 + 0xc) = uVar5;
              }
            }
            else {
              plVar13 = (long *)**(long **)param_2;
              uVar14 = *(uint *)(plVar13 + 1);
              uVar5 = *(uint *)((long)plVar13 + 0xc);
              if (uVar5 <= uVar14) goto LAB_00d19d29;
LAB_00d19fe3:
              pvVar9 = (void *)*plVar13;
            }
            *(CQuestUnitData **)((long)pvVar9 + (ulong)uVar14 * 8) = this_00;
            *(int *)(plVar13 + 1) = (int)plVar13[1] + 1;
                    /* try { // try from 00d19dad to 00d19db1 has its CatchHandler @ 00d1a275 */
            std::wstring::wstring((wstring_conflict *)local_88,L"ACQUIRE",&local_3c);
                    /* try { // try from 00d19dc0 to 00d19ddc has its CatchHandler @ 00d1a2cb */
            pCVar10 = (CDataGroup *)
                      CDataGroup::GetDataGroupByName
                                (*(CDataGroup **)((long)local_c8 + lVar6),
                                 (wstring_conflict *)local_88,false);
            calculateUnitsFromTag(this,pCVar10,(TArrayList *)0x0,(TArrayList *)(this_00 + 0x48),1);
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
            if (1 < *(uint *)(this_00 + 0x38)) {
              uVar5 = 1;
              do {
                    /* try { // try from 00d19e2b to 00d19e2f has its CatchHandler @ 00d1a1f8 */
                this_01 = (CQuestUnitData *)
                          Ogre::NedAllocImpl::allocBytes(200,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00d19e3b to 00d19e3f has its CatchHandler @ 00d1a28f */
                CQuestUnitData::CQuestUnitData(this_01,this);
                    /* try { // try from 00d19e51 to 00d19eb2 has its CatchHandler @ 00d1a1f8 */
                CQuestUnitData::parseDataGroup
                          (this_01,*(CDataGroup **)((long)local_c8 + lVar6),
                           *(CDataGroup **)(this_00 + 0x20));
                *(undefined4 *)(this_01 + 0xb4) = 1;
                uVar7 = CQuestUnitData::getBaseUnitDataGroup(this_01);
                *(undefined8 *)(this_01 + 0x20) = uVar7;
                *(undefined4 *)(this_01 + 0x38) = *(undefined4 *)(this_00 + 0x38);
                if (uVar4 < *(uint *)(param_2 + 0xc)) {
                  plVar13 = *(long **)((ulong)uVar4 * 8 + *(long *)param_2);
                  uVar12 = *(uint *)(plVar13 + 1);
                  uVar14 = *(uint *)((long)plVar13 + 0xc);
                  if (uVar12 < uVar14) goto LAB_00d19f9a;
LAB_00d19e97:
                  if (*plVar13 == 0) {
                    *(uint *)((long)plVar13 + 0xc) = *(uint *)(plVar13 + 2);
                    /* try { // try from 00d19fb6 to 00d1a02b has its CatchHandler @ 00d1a1f8 */
                    pvVar9 = operator_new__((ulong)*(uint *)(plVar13 + 2) * 8);
                    *plVar13 = (long)pvVar9;
                    uVar12 = *(uint *)(plVar13 + 1);
                  }
                  else {
                    uVar14 = uVar14 + (int)plVar13[2];
                    pvVar9 = operator_new__((ulong)uVar14 << 3);
                    if (*(int *)((long)plVar13 + 0xc) != 0) {
                      uVar12 = 0;
                      do {
                        uVar11 = (ulong)uVar12;
                        uVar12 = uVar12 + 1;
                        *(undefined8 *)((long)pvVar9 + uVar11 * 8) =
                             *(undefined8 *)(*plVar13 + uVar11 * 8);
                      } while (uVar12 < *(uint *)((long)plVar13 + 0xc));
                    }
                    if ((void *)*plVar13 != (void *)0x0) {
                      operator_delete__((void *)*plVar13);
                    }
                    *plVar13 = (long)pvVar9;
                    *(uint *)((long)plVar13 + 0xc) = uVar14;
                    uVar12 = *(uint *)(plVar13 + 1);
                  }
                }
                else {
                  plVar13 = (long *)**(long **)param_2;
                  uVar12 = *(uint *)(plVar13 + 1);
                  uVar14 = *(uint *)((long)plVar13 + 0xc);
                  if (uVar14 <= uVar12) goto LAB_00d19e97;
LAB_00d19f9a:
                  pvVar9 = (void *)*plVar13;
                }
                *(CQuestUnitData **)((long)pvVar9 + (ulong)uVar12 * 8) = this_01;
                *(int *)(plVar13 + 1) = (int)plVar13[1] + 1;
                    /* try { // try from 00d19f19 to 00d19f1d has its CatchHandler @ 00d1a28a */
                std::wstring::wstring((wstring_conflict *)local_98,L"ACQUIRE",&local_3d);
                    /* try { // try from 00d19f2e to 00d19f4a has its CatchHandler @ 00d1a266 */
                pCVar10 = (CDataGroup *)
                          CDataGroup::GetDataGroupByName
                                    (*(CDataGroup **)((long)local_c8 + lVar6),
                                     (wstring_conflict *)local_98,false);
                calculateUnitsFromTag
                          (this,pCVar10,(TArrayList *)0x0,(TArrayList *)(this_01 + 0x48),1);
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
                uVar5 = uVar5 + 1;
              } while (uVar5 < *(uint *)(this_00 + 0x38));
            }
          }
        }
        local_dc = local_dc + 1;
        uVar11 = (ulong)local_dc;
      } while (uVar11 < (ulong)(local_c0 - (long)local_c8 >> 3));
    }
    if (local_c8 != (void *)0x0) {
      operator_delete(local_c8);
    }
  }
  return local_d0;
}

/* address=00d1a390
   symbol=CQuest::~CQuest */

/* WARNING: Removing unreachable block (ram,0x00d1b587) */
/* WARNING: Removing unreachable block (ram,0x00d1b4b7) */
/* WARNING: Removing unreachable block (ram,0x00d1b51f) */
/* WARNING: Removing unreachable block (ram,0x00d1b2c7) */
/* WARNING: Removing unreachable block (ram,0x00d1b514) */
/* WARNING: Removing unreachable block (ram,0x00d1b4ac) */
/* WARNING: Removing unreachable block (ram,0x00d1b57c) */
/* WARNING: Removing unreachable block (ram,0x00d1b5ab) */
/* CQuest::~CQuest() */

void __thiscall CQuest::~CQuest(CQuest *this)

{
  int *piVar1;
  long lVar2;
  int iVar3;
  TSafePointer *pTVar4;
  undefined8 *puVar5;
  long *plVar6;
  long *plVar7;
  undefined8 *puVar8;
  ulong uVar9;
  uint uVar10;
  uint uVar11;
  allocator *paVar12;
  CQuest *pCVar13;

  *(undefined ***)this = &PTR__CQuest_00ff7170;
  *(undefined8 *)(this + 0x10) = 0;
  if (*(int *)(this + 0x1b8) != 0) {
    uVar9 = 0;
    do {
      puVar5 = (undefined8 *)(uVar9 * 8 + *(long *)(this + 0x1b0));
      pTVar4 = (TSafePointer *)*puVar5;
      if (pTVar4 != (TSafePointer *)0x0) {
        if (*(CRunicCore **)pTVar4 != (CRunicCore *)0x0) {
                    /* try { // try from 00d1a447 to 00d1a44b has its CatchHandler @ 00d1b380 */
          CRunicCore::removeSafePointer(*(CRunicCore **)pTVar4,pTVar4,*(uint *)(pTVar4 + 8));
        }
        *(undefined8 *)pTVar4 = 0;
        *(undefined4 *)(pTVar4 + 8) = 0xffffffff;
                    /* try { // try from 00d1a49e to 00d1aef5 has its CatchHandler @ 00d1b2f4 */
        Ogre::NedAllocImpl::deallocBytes(pTVar4);
        *(undefined8 *)(*(long *)(this + 0x1b0) + uVar9 * 8) = 0;
        puVar5 = (undefined8 *)(uVar9 * 8 + *(long *)(this + 0x1b0));
      }
      *puVar5 = 0;
      uVar10 = (int)uVar9 + 1;
      uVar9 = (ulong)uVar10;
    } while (uVar10 < *(uint *)(this + 0x1b8));
  }
  *(undefined4 *)(this + 0x1b8) = 0;
  *(undefined4 *)(this + 0x1bc) = 0;
  if (*(void **)(this + 0x1b0) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x1b0));
  }
  *(undefined8 *)(this + 0x1b0) = 0;
  if (*(long **)(this + 0x128) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x128) + 8))();
    *(undefined8 *)(this + 0x128) = 0;
  }
  if (*(long **)(this + 0xc0) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0xc0) + 8))();
    *(undefined8 *)(this + 0xc0) = 0;
  }
  if (*(long **)(this + 0x1e0) != (long *)0x0) {
    (**(code **)(**(long **)(this + 0x1e0) + 8))();
    *(undefined8 *)(this + 0x1e0) = 0;
  }
  pCVar13 = this + 0xa8;
  if (*(int *)(this + 0xb0) != 0) {
    uVar9 = 0;
    do {
      plVar6 = (long *)(*(long *)pCVar13 + uVar9 * 8);
      if ((long *)*plVar6 != (long *)0x0) {
        (**(code **)(*(long *)*plVar6 + 8))();
        *(undefined8 *)(*(long *)pCVar13 + uVar9 * 8) = 0;
        plVar6 = (long *)(*(long *)pCVar13 + uVar9 * 8);
      }
      *plVar6 = 0;
      uVar10 = (int)uVar9 + 1;
      uVar9 = (ulong)uVar10;
    } while (uVar10 < *(uint *)(this + 0xb0));
  }
  *(undefined4 *)(this + 0xb0) = 0;
  *(undefined4 *)(this + 0xb4) = 0;
  if (*(void **)(this + 0xa8) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0xa8));
  }
  pCVar13 = this + 0x60;
  *(undefined8 *)(this + 0xa8) = 0;
  if (*(int *)(this + 0x68) != 0) {
    uVar9 = 0;
    do {
      plVar6 = (long *)(*(long *)pCVar13 + uVar9 * 8);
      if ((long *)*plVar6 != (long *)0x0) {
        (**(code **)(*(long *)*plVar6 + 8))();
        *(undefined8 *)(*(long *)pCVar13 + uVar9 * 8) = 0;
        plVar6 = (long *)(*(long *)pCVar13 + uVar9 * 8);
      }
      *plVar6 = 0;
      uVar10 = (int)uVar9 + 1;
      uVar9 = (ulong)uVar10;
    } while (uVar10 < *(uint *)(this + 0x68));
  }
  *(undefined4 *)(this + 0x68) = 0;
  *(undefined4 *)(this + 0x6c) = 0;
  if (*(void **)(this + 0x60) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x60));
  }
  pCVar13 = this + 0x78;
  *(undefined8 *)(this + 0x60) = 0;
  if (*(int *)(this + 0x80) != 0) {
    uVar9 = 0;
    do {
      plVar6 = (long *)(*(long *)pCVar13 + uVar9 * 8);
      if ((long *)*plVar6 != (long *)0x0) {
        (**(code **)(*(long *)*plVar6 + 8))();
        *(undefined8 *)(*(long *)pCVar13 + uVar9 * 8) = 0;
        plVar6 = (long *)(*(long *)pCVar13 + uVar9 * 8);
      }
      *plVar6 = 0;
      uVar10 = (int)uVar9 + 1;
      uVar9 = (ulong)uVar10;
    } while (uVar10 < *(uint *)(this + 0x80));
  }
  *(undefined4 *)(this + 0x80) = 0;
  *(undefined4 *)(this + 0x84) = 0;
  if (*(void **)(this + 0x78) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x78));
  }
  pCVar13 = this + 0x90;
  *(undefined8 *)(this + 0x78) = 0;
  if (*(int *)(this + 0x98) != 0) {
    uVar9 = 0;
    do {
      plVar6 = (long *)(*(long *)pCVar13 + uVar9 * 8);
      if ((long *)*plVar6 != (long *)0x0) {
        (**(code **)(*(long *)*plVar6 + 8))();
        *(undefined8 *)(*(long *)pCVar13 + uVar9 * 8) = 0;
        plVar6 = (long *)(*(long *)pCVar13 + uVar9 * 8);
      }
      *plVar6 = 0;
      uVar10 = (int)uVar9 + 1;
      uVar9 = (ulong)uVar10;
    } while (uVar10 < *(uint *)(this + 0x98));
  }
  *(undefined4 *)(this + 0x98) = 0;
  *(undefined4 *)(this + 0x9c) = 0;
  if (*(void **)(this + 0x90) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x90));
  }
  *(undefined8 *)(this + 0x90) = 0;
  if (*(int *)(this + 0x180) != 0) {
    uVar10 = 0;
    do {
      if (uVar10 < *(uint *)(this + 0x184)) {
        puVar5 = (undefined8 *)((ulong)uVar10 * 8 + *(long *)(this + 0x178));
      }
      else {
        puVar5 = *(undefined8 **)(this + 0x178);
      }
      plVar6 = (long *)*puVar5;
      if ((int)plVar6[1] != 0) {
        uVar9 = 0;
        do {
          plVar7 = (long *)(uVar9 * 8 + *plVar6);
          if ((long *)*plVar7 != (long *)0x0) {
            (**(code **)(*(long *)*plVar7 + 8))();
            *(undefined8 *)(*plVar6 + uVar9 * 8) = 0;
            plVar7 = (long *)(uVar9 * 8 + *plVar6);
          }
          *plVar7 = 0;
          uVar11 = (int)uVar9 + 1;
          uVar9 = (ulong)uVar11;
        } while (uVar11 < *(uint *)(plVar6 + 1));
      }
      *(undefined4 *)(plVar6 + 1) = 0;
      *(undefined4 *)((long)plVar6 + 0xc) = 0;
      if ((void *)*plVar6 != (void *)0x0) {
        operator_delete__((void *)*plVar6);
      }
      *plVar6 = 0;
      uVar10 = uVar10 + 1;
    } while (uVar10 < *(uint *)(this + 0x180));
  }
  if (*(int *)(this + 0x168) != 0) {
    uVar10 = 0;
    do {
      if (uVar10 < *(uint *)(this + 0x16c)) {
        puVar5 = (undefined8 *)((ulong)uVar10 * 8 + *(long *)(this + 0x160));
      }
      else {
        puVar5 = *(undefined8 **)(this + 0x160);
      }
      plVar6 = (long *)*puVar5;
      if ((int)plVar6[1] != 0) {
        uVar9 = 0;
        do {
          plVar7 = (long *)(uVar9 * 8 + *plVar6);
          if ((long *)*plVar7 != (long *)0x0) {
            (**(code **)(*(long *)*plVar7 + 8))();
            *(undefined8 *)(*plVar6 + uVar9 * 8) = 0;
            plVar7 = (long *)(uVar9 * 8 + *plVar6);
          }
          *plVar7 = 0;
          uVar11 = (int)uVar9 + 1;
          uVar9 = (ulong)uVar11;
        } while (uVar11 < *(uint *)(plVar6 + 1));
      }
      *(undefined4 *)(plVar6 + 1) = 0;
      *(undefined4 *)((long)plVar6 + 0xc) = 0;
      if ((void *)*plVar6 != (void *)0x0) {
        operator_delete__((void *)*plVar6);
      }
      *plVar6 = 0;
      uVar10 = uVar10 + 1;
    } while (uVar10 < *(uint *)(this + 0x168));
  }
  if (*(int *)(this + 0x198) != 0) {
    uVar10 = 0;
    do {
      if (uVar10 < *(uint *)(this + 0x19c)) {
        puVar5 = (undefined8 *)((ulong)uVar10 * 8 + *(long *)(this + 400));
      }
      else {
        puVar5 = *(undefined8 **)(this + 400);
      }
      plVar6 = (long *)*puVar5;
      if ((int)plVar6[1] != 0) {
        uVar9 = 0;
        do {
          plVar7 = (long *)(uVar9 * 8 + *plVar6);
          if ((long *)*plVar7 != (long *)0x0) {
            (**(code **)(*(long *)*plVar7 + 8))();
            *(undefined8 *)(*plVar6 + uVar9 * 8) = 0;
            plVar7 = (long *)(uVar9 * 8 + *plVar6);
          }
          *plVar7 = 0;
          uVar11 = (int)uVar9 + 1;
          uVar9 = (ulong)uVar11;
        } while (uVar11 < *(uint *)(plVar6 + 1));
      }
      *(undefined4 *)(plVar6 + 1) = 0;
      *(undefined4 *)((long)plVar6 + 0xc) = 0;
      if ((void *)*plVar6 != (void *)0x0) {
        operator_delete__((void *)*plVar6);
      }
      *plVar6 = 0;
      uVar10 = uVar10 + 1;
    } while (uVar10 < *(uint *)(this + 0x198));
  }
  pCVar13 = this + 0x160;
  if (*(int *)(this + 0x168) != 0) {
    uVar9 = 0;
    do {
      puVar8 = (undefined8 *)(*(long *)pCVar13 + uVar9 * 8);
      puVar5 = (undefined8 *)*puVar8;
      if (puVar5 != (undefined8 *)0x0) {
        if ((void *)*puVar5 != (void *)0x0) {
          operator_delete__((void *)*puVar5);
          *puVar5 = 0;
        }
        Ogre::NedAllocImpl::deallocBytes(puVar5);
        *(undefined8 *)(*(long *)pCVar13 + uVar9 * 8) = 0;
        puVar8 = (undefined8 *)(*(long *)pCVar13 + uVar9 * 8);
      }
      *puVar8 = 0;
      uVar10 = (int)uVar9 + 1;
      uVar9 = (ulong)uVar10;
    } while (uVar10 < *(uint *)(this + 0x168));
  }
  *(undefined4 *)(this + 0x168) = 0;
  *(undefined4 *)(this + 0x16c) = 0;
  if (*(void **)(this + 0x160) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x160));
  }
  pCVar13 = this + 400;
  *(undefined8 *)(this + 0x160) = 0;
  if (*(int *)(this + 0x198) != 0) {
    uVar9 = 0;
    do {
      puVar8 = (undefined8 *)(*(long *)pCVar13 + uVar9 * 8);
      puVar5 = (undefined8 *)*puVar8;
      if (puVar5 != (undefined8 *)0x0) {
        if ((void *)*puVar5 != (void *)0x0) {
          operator_delete__((void *)*puVar5);
          *puVar5 = 0;
        }
        Ogre::NedAllocImpl::deallocBytes(puVar5);
        *(undefined8 *)(*(long *)pCVar13 + uVar9 * 8) = 0;
        puVar8 = (undefined8 *)(*(long *)pCVar13 + uVar9 * 8);
      }
      *puVar8 = 0;
      uVar10 = (int)uVar9 + 1;
      uVar9 = (ulong)uVar10;
    } while (uVar10 < *(uint *)(this + 0x198));
  }
  *(undefined4 *)(this + 0x198) = 0;
  *(undefined4 *)(this + 0x19c) = 0;
  if (*(void **)(this + 400) != (void *)0x0) {
    operator_delete__(*(void **)(this + 400));
  }
  *(undefined8 *)(this + 400) = 0;
  pCVar13 = this + 0x178;
  if (*(int *)(this + 0x180) != 0) {
    uVar10 = 0;
    do {
      lVar2 = (ulong)uVar10 * 8;
      puVar8 = (undefined8 *)(*(long *)pCVar13 + lVar2);
      puVar5 = (undefined8 *)*puVar8;
      if (puVar5 != (undefined8 *)0x0) {
        if ((void *)*puVar5 != (void *)0x0) {
          operator_delete__((void *)*puVar5);
          *puVar5 = 0;
        }
        Ogre::NedAllocImpl::deallocBytes(puVar5);
        *(undefined8 *)(*(long *)pCVar13 + (ulong)uVar10 * 8) = 0;
        puVar8 = (undefined8 *)(*(long *)pCVar13 + lVar2);
      }
      *puVar8 = 0;
      uVar10 = uVar10 + 1;
    } while (uVar10 < *(uint *)(this + 0x180));
  }
  *(undefined4 *)(this + 0x180) = 0;
  *(undefined4 *)(this + 0x184) = 0;
  if (*(void **)(this + 0x178) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x178));
  }
  *(undefined8 *)(this + 0x178) = 0;
  *(undefined4 *)(this + 0x138) = 0;
  *(undefined4 *)(this + 0x13c) = 0;
  if (*(void **)(this + 0x130) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x130));
  }
  *(undefined8 *)(this + 0x130) = 0;
  *(undefined4 *)(this + 0x150) = 0;
  *(undefined4 *)(this + 0x154) = 0;
  if (*(void **)(this + 0x148) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x148));
  }
  plVar6 = *(long **)(this + 0x1f0);
  *(undefined8 *)(this + 0x148) = 0;
  *(undefined8 *)(this + 0x1d0) = 0;
  if (plVar6 != (long *)0x0) {
    plVar7 = plVar6 + plVar6[-1];
    while (plVar6 != plVar7) {
      plVar7 = plVar7 + -1;
      paVar12 = (allocator *)(*plVar7 + -0x18);
      if (paVar12 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
        LOCK();
        piVar1 = (int *)(*plVar7 + -8);
        iVar3 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (iVar3 < 1) {
          std::wstring::_Rep::_M_destroy(paVar12);
          plVar6 = *(long **)(this + 0x1f0);
        }
        else {
          plVar6 = *(long **)(this + 0x1f0);
        }
      }
    }
    operator_delete__((void *)(*(long *)(this + 0x1f0) + -8));
    *(undefined8 *)(this + 0x1f0) = 0;
  }
  if (*(void **)(this + 0x1b0) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x1b0));
    *(undefined8 *)(this + 0x1b0) = 0;
  }
  if (*(void **)(this + 400) != (void *)0x0) {
    operator_delete__(*(void **)(this + 400));
    *(undefined8 *)(this + 400) = 0;
  }
  if (*(void **)(this + 0x178) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x178));
    *(undefined8 *)(this + 0x178) = 0;
  }
  if (*(void **)(this + 0x160) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x160));
    *(undefined8 *)(this + 0x160) = 0;
  }
  if (*(void **)(this + 0x148) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x148));
    *(undefined8 *)(this + 0x148) = 0;
  }
  if (*(void **)(this + 0x130) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x130));
    *(undefined8 *)(this + 0x130) = 0;
  }
  if (*(void **)(this + 0x110) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x110));
    *(undefined8 *)(this + 0x110) = 0;
  }
  if (*(void **)(this + 0xf8) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0xf8));
    *(undefined8 *)(this + 0xf8) = 0;
  }
  pCVar13 = this + 0xf8;
  do {
    pCVar13 = pCVar13 + -0x18;
    plVar6 = *(long **)pCVar13;
    if (plVar6 != (long *)0x0) {
      plVar7 = plVar6 + plVar6[-1];
      while (plVar6 != plVar7) {
        plVar7 = plVar7 + -1;
        paVar12 = (allocator *)(*plVar7 + -0x18);
        if (paVar12 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
          LOCK();
          piVar1 = (int *)(*plVar7 + -8);
          iVar3 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar3 < 1) {
            std::wstring::_Rep::_M_destroy(paVar12);
          }
          plVar6 = *(long **)pCVar13;
        }
      }
      operator_delete__(plVar6 + -1);
      *(long *)pCVar13 = 0;
    }
  } while (pCVar13 != this + 200);
  if (*(void **)(this + 0xa8) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0xa8));
    *(undefined8 *)(this + 0xa8) = 0;
  }
  if (*(void **)(this + 0x90) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x90));
    *(undefined8 *)(this + 0x90) = 0;
  }
  if (*(void **)(this + 0x78) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x78));
    *(undefined8 *)(this + 0x78) = 0;
  }
  if (*(void **)(this + 0x60) != (void *)0x0) {
    operator_delete__(*(void **)(this + 0x60));
    *(undefined8 *)(this + 0x60) = 0;
  }
  paVar12 = (allocator *)(*(long *)(this + 0x58) + -0x18);
  if (paVar12 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(*(long *)(this + 0x58) + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar12);
    }
  }
  paVar12 = (allocator *)(*(long *)(this + 0x50) + -0x18);
  if (paVar12 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(*(long *)(this + 0x50) + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar12);
    }
  }
  paVar12 = (allocator *)(*(long *)(this + 0x48) + -0x18);
  if (paVar12 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(*(long *)(this + 0x48) + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar12);
    }
  }
  paVar12 = (allocator *)(*(long *)(this + 0x40) + -0x18);
  if (paVar12 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(*(long *)(this + 0x40) + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar12);
    }
  }
  paVar12 = (allocator *)(*(long *)(this + 0x38) + -0x18);
  if (paVar12 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(*(long *)(this + 0x38) + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar12);
    }
  }
  paVar12 = (allocator *)(*(long *)(this + 0x30) + -0x18);
  if (paVar12 != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
    LOCK();
    piVar1 = (int *)(*(long *)(this + 0x30) + -8);
    iVar3 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar3 < 1) {
      std::wstring::_Rep::_M_destroy(paVar12);
    }
  }
  CRunicCore::~CRunicCore((CRunicCore *)this);
  return;
}

/* address=00d1b5c0
   symbol=CQuest::~CQuest */

/* CQuest::~CQuest() */

void __thiscall CQuest::~CQuest(CQuest *this)

{
  ~CQuest(this);
  Ogre::NedAllocImpl::deallocBytes(this);
  return;
}

/* address=00d1b5e0
   symbol=CQuest::loadQuestData */

/* WARNING: Removing unreachable block (ram,0x00d1c8aa) */
/* WARNING: Removing unreachable block (ram,0x00d1cee1) */
/* WARNING: Removing unreachable block (ram,0x00d1c924) */
/* WARNING: Removing unreachable block (ram,0x00d1c869) */
/* WARNING: Removing unreachable block (ram,0x00d1ce03) */
/* WARNING: Removing unreachable block (ram,0x00d1cf26) */
/* WARNING: Removing unreachable block (ram,0x00d1cf34) */
/* WARNING: Removing unreachable block (ram,0x00d1cc45) */
/* WARNING: Removing unreachable block (ram,0x00d1cd58) */
/* WARNING: Removing unreachable block (ram,0x00d1cd48) */
/* WARNING: Removing unreachable block (ram,0x00d1c9c5) */
/* WARNING: Removing unreachable block (ram,0x00d1ca89) */
/* WARNING: Removing unreachable block (ram,0x00d1cad5) */
/* WARNING: Removing unreachable block (ram,0x00d1cbca) */
/* WARNING: Removing unreachable block (ram,0x00d1cb8b) */
/* WARNING: Removing unreachable block (ram,0x00d1cb13) */
/* WARNING: Removing unreachable block (ram,0x00d1ca79) */
/* WARNING: Removing unreachable block (ram,0x00d1ca03) */
/* WARNING: Removing unreachable block (ram,0x00d1c977) */
/* WARNING: Removing unreachable block (ram,0x00d1cd7e) */
/* WARNING: Removing unreachable block (ram,0x00d1cd6b) */
/* WARNING: Removing unreachable block (ram,0x00d1cc3a) */
/* WARNING: Removing unreachable block (ram,0x00d1c8dd) */
/* WARNING: Removing unreachable block (ram,0x00d1cea5) */
/* WARNING: Removing unreachable block (ram,0x00d1cdc7) */
/* WARNING: Removing unreachable block (ram,0x00d1c8b8) */
/* WARNING: Removing unreachable block (ram,0x00d1c932) */
/* WARNING: Removing unreachable block (ram,0x00d1c762) */
/* WARNING: Removing unreachable block (ram,0x00d1c79b) */
/* WARNING: Removing unreachable block (ram,0x00d1ceef) */
/* WARNING: Removing unreachable block (ram,0x00d1c70d) */
/* CQuest::loadQuestData(std::wstring const&) */

undefined8 __thiscall CQuest::loadQuestData(CQuest *this,wstring_conflict *param_1)

{
  int *piVar1;
  CQuest *pCVar2;
  CQuest CVar3;
  char cVar4;
  int iVar5;
  undefined4 uVar6;
  wchar_t *pwVar7;
  long lVar8;
  wstring_conflict *pwVar9;
  ulong *puVar10;
  CDataGroup *pCVar11;
  long *plVar12;
  CDataGroup *pCVar13;
  CQuestDialog *this_00;
  long *plVar14;
  undefined8 *puVar15;
  void *pvVar16;
  CQuestRewards *this_01;
  uint uVar17;
  ulong *puVar18;
  ulong uVar19;
  uint uVar20;
  long lVar21;
  CQuest *pCVar22;
  undefined8 uVar23;
  allocator *paVar24;
  uint uVar25;
  uint local_2cc;
  CDataGroup local_2c8 [96];
  wstring_conflict local_268 [16];
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
  wstring_conflict local_118 [16];
  long local_108 [2];
  long local_f8 [2];
  long local_e8 [2];
  long local_d8 [2];
  long local_c8 [2];
  long local_b8 [2];
  long local_a8 [2];
  long local_98 [2];
  long local_88 [6];
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

  this[0x24] = (CQuest)0x0;
  if ((*(long *)(this + 0x1d0) == 0) || (*(long *)(*(long *)(this + 0x48) + -0x18) != 0)) {
    return 0;
  }
  std::wstring::assign((wstring_conflict *)(this + 0x48));
                    /* try { // try from 00d1b63c to 00d1b640 has its CatchHandler @ 00d1cbab */
  std::wstring::wstring((wstring_conflict *)local_88,L"ERROR",local_39);
                    /* try { // try from 00d1b659 to 00d1b65d has its CatchHandler @ 00d1cbb5 */
  CDataGroup::CDataGroup
            (local_2c8,(wstring_conflict *)local_88,(CDataGroup *)0x0,0x14,10,(TRepository *)0x0);
  if ((allocator *)(local_88[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage)
  {
    LOCK();
    piVar1 = (int *)(local_88[0] + -8);
    iVar5 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar5 < 1) {
      std::wstring::_Rep::_M_destroy((allocator *)(local_88[0] + -0x18));
    }
  }
                    /* try { // try from 00d1b681 to 00d1b69c has its CatchHandler @ 00d1cb86 */
  CDataGroup::LoadFile(local_2c8,(wstring_conflict *)(this + 0x48),(CTimerStatics *)0x0);
  pwVar7 = (wchar_t *)CDataGroup::GetGroupName(local_2c8);
  iVar5 = std::wstring::compare(pwVar7);
  uVar23 = 0;
  if (iVar5 == 0) {
LAB_00d1c3ce:
    CDataGroup::~CDataGroup(local_2c8);
  }
  else {
                    /* try { // try from 00d1b6bf to 00d1b6c3 has its CatchHandler @ 00d1cbc5 */
    std::wstring::wstring((wstring_conflict *)local_98,L"COMPLETESONACCEPT",&local_3a);
                    /* try { // try from 00d1b6ce to 00d1b6d2 has its CatchHandler @ 00d1cb55 */
    CVar3 = (CQuest)CDataGroup::GetDataValue(local_2c8,(wstring_conflict *)local_98,false);
    this[0x2b] = CVar3;
    if ((allocator *)(local_98[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_98[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_98[0] + -0x18));
      }
    }
                    /* try { // try from 00d1b709 to 00d1b70d has its CatchHandler @ 00d1cb1e */
    std::wstring::wstring((wstring_conflict *)local_a8,L"FORCEACCEPT",&local_3b);
                    /* try { // try from 00d1b718 to 00d1b71c has its CatchHandler @ 00d1cb0e */
    CVar3 = (CQuest)CDataGroup::GetDataValue(local_2c8,(wstring_conflict *)local_a8,false);
    this[0x28] = CVar3;
    if ((allocator *)(local_a8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_a8[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_a8[0] + -0x18));
      }
    }
                    /* try { // try from 00d1b753 to 00d1b757 has its CatchHandler @ 00d1caca */
    std::wstring::wstring((wstring_conflict *)local_b8,L"SHOWQUESTCOMPLETE",&local_3c);
                    /* try { // try from 00d1b765 to 00d1b769 has its CatchHandler @ 00d1cac5 */
    CVar3 = (CQuest)CDataGroup::GetDataValue(local_2c8,(wstring_conflict *)local_b8,true);
    this[0x29] = CVar3;
    if ((allocator *)(local_b8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_b8[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_b8[0] + -0x18));
      }
    }
                    /* try { // try from 00d1b7a0 to 00d1b7a4 has its CatchHandler @ 00d1ca94 */
    std::wstring::wstring((wstring_conflict *)local_c8,L"QUESTCONTROLLERCOMPLETES",&local_3d);
                    /* try { // try from 00d1b7af to 00d1b7b3 has its CatchHandler @ 00d1ca74 */
    CVar3 = (CQuest)CDataGroup::GetDataValue(local_2c8,(wstring_conflict *)local_c8,false);
    this[0x2a] = CVar3;
    if ((allocator *)(local_c8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_c8[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_c8[0] + -0x18));
      }
    }
                    /* try { // try from 00d1b7ea to 00d1b7ee has its CatchHandler @ 00d1ca84 */
    std::wstring::wstring((wstring_conflict *)local_d8,L"NO_NOTIFICATION",&local_3e);
                    /* try { // try from 00d1b7f9 to 00d1b7fd has its CatchHandler @ 00d1ca41 */
    CVar3 = (CQuest)CDataGroup::GetDataValue(local_2c8,(wstring_conflict *)local_d8,false);
    this[0x25] = CVar3;
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
                    /* try { // try from 00d1b834 to 00d1b838 has its CatchHandler @ 00d1ca0e */
    std::wstring::wstring((wstring_conflict *)local_e8,L"CLEAR_DUNGEON_HISTORY",&local_3f);
                    /* try { // try from 00d1b843 to 00d1b847 has its CatchHandler @ 00d1c9fe */
    CVar3 = (CQuest)CDataGroup::GetDataValue(local_2c8,(wstring_conflict *)local_e8,false);
    this[0x20a] = CVar3;
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
                    /* try { // try from 00d1b881 to 00d1b885 has its CatchHandler @ 00d1c9bd */
    std::wstring::wstring((wstring_conflict *)local_f8,L"REPEATABLE",&local_40);
                    /* try { // try from 00d1b890 to 00d1b894 has its CatchHandler @ 00d1c9b8 */
    CVar3 = (CQuest)CDataGroup::GetDataValue(local_2c8,(wstring_conflict *)local_f8,false);
    this[0x20b] = CVar3;
    if ((allocator *)(local_f8[0] + -0x18) != (allocator *)&std::wstring::_Rep::_S_empty_rep_storage
       ) {
      LOCK();
      piVar1 = (int *)(local_f8[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_f8[0] + -0x18));
      }
    }
                    /* try { // try from 00d1b8ce to 00d1b8d2 has its CatchHandler @ 00d1c987 */
    std::wstring::wstring((wstring_conflict *)local_108,L"QUEST_GUID",&local_41);
                    /* try { // try from 00d1b8e2 to 00d1b8e6 has its CatchHandler @ 00d1c982 */
    lVar8 = CDataGroup::GetDataValue(local_2c8,(wstring_conflict *)local_108,-1);
    *(long *)(this + 0x1c8) = lVar8;
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
      lVar8 = *(long *)(this + 0x1c8);
    }
    if (lVar8 == -1) {
      do {
                    /* try { // try from 00d1c400 to 00d1c404 has its CatchHandler @ 00d1cb86 */
        lVar8 = UTILITIES::createUniqueGuid();
        *(long *)(this + 0x1c8) = lVar8;
      } while (lVar8 == -1);
                    /* try { // try from 00d1c42d to 00d1c431 has its CatchHandler @ 00d1cba6 */
      std::wstring::wstring(local_118,L"QUEST_GUID",&local_42);
                    /* try { // try from 00d1c43d to 00d1c441 has its CatchHandler @ 00d1cb96 */
      CDataGroup::SetDataValue(local_2c8,local_118,lVar8);
                    /* try { // try from 00d1c445 to 00d1c449 has its CatchHandler @ 00d1cba6 */
      std::wstring::~wstring(local_118);
                    /* try { // try from 00d1c452 to 00d1c4aa has its CatchHandler @ 00d1cb86 */
      CDataGroup::SaveToFile(local_2c8,param_1);
    }
                    /* try { // try from 00d1b92a to 00d1b92e has its CatchHandler @ 00d1c942 */
    std::wstring::wstring((wstring_conflict *)local_128,L"CANABANDON",&local_43);
                    /* try { // try from 00d1b939 to 00d1b93d has its CatchHandler @ 00d1c93d */
    CVar3 = (CQuest)CDataGroup::GetDataValue(local_2c8,(wstring_conflict *)local_128,false);
    this[0x208] = CVar3;
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
      CVar3 = this[0x208];
    }
                    /* try { // try from 00d1b97a to 00d1b97e has its CatchHandler @ 00d1cd0d */
    std::wstring::wstring((wstring_conflict *)local_138,L"SHOWTIPS",&local_44);
                    /* try { // try from 00d1b989 to 00d1b98d has its CatchHandler @ 00d1cd53 */
    CVar3 = (CQuest)CDataGroup::GetDataValue(local_2c8,(wstring_conflict *)local_138,(bool)CVar3);
    this[0x2c] = CVar3;
    if ((allocator *)(local_138[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_138[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_138[0] + -0x18));
      }
    }
                    /* try { // try from 00d1b9c8 to 00d1b9cc has its CatchHandler @ 00d1cd79 */
    std::wstring::wstring((wstring_conflict *)local_148,L"DUNGEON",&local_45);
                    /* try { // try from 00d1b9d8 to 00d1b9ef has its CatchHandler @ 00d1cd08 */
    pwVar9 = (wstring_conflict *)
             CDataGroup::GetDataValue
                       (local_2c8,(wstring_conflict *)local_148,(wstring_conflict *)(this + 0x30));
    STRINGS::StringUpper((STRINGS *)local_158,pwVar9);
                    /* try { // try from 00d1b9f6 to 00d1b9fa has its CatchHandler @ 00d1cd66 */
    std::wstring::assign((wstring_conflict *)(this + 0x30));
    if ((allocator *)(local_158[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_158[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_158[0] + -0x18));
      }
    }
    if ((allocator *)(local_148[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_148[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_148[0] + -0x18));
      }
    }
                    /* try { // try from 00d1ba47 to 00d1ba4b has its CatchHandler @ 00d1cc65 */
    std::wstring::wstring((wstring_conflict *)local_168,L"QUESTTYPE",&local_46);
                    /* try { // try from 00d1ba59 to 00d1ba70 has its CatchHandler @ 00d1cc60 */
    pwVar9 = (wstring_conflict *)
             CDataGroup::GetDataValue
                       (local_2c8,(wstring_conflict *)local_168,(wstring_conflict *)&::EMPTY_WSTRING
                       );
    STRINGS::StringUpper((STRINGS *)local_178,pwVar9);
                    /* try { // try from 00d1ba83 to 00d1ba87 has its CatchHandler @ 00d1cc50 */
    uVar6 = STRINGS::getStringIndex
                      ((wstring_conflict *)local_178,(wstring_conflict *)::gQUEST_TYPE_NAMES,4,0,
                       false);
    *(undefined4 *)(this + 0x18) = uVar6;
    if ((allocator *)(local_178[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_178[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_178[0] + -0x18));
      }
    }
    if ((allocator *)(local_168[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_168[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_168[0] + -0x18));
      }
    }
                    /* try { // try from 00d1bad8 to 00d1badc has its CatchHandler @ 00d1cbdd */
    std::wstring::wstring((wstring_conflict *)local_188,L"GIVE_QUESTS_ON_COMPLETE",&local_47);
                    /* try { // try from 00d1bae7 to 00d1baeb has its CatchHandler @ 00d1cbd8 */
    lVar8 = CDataGroup::GetDataGroupByName(local_2c8,(wstring_conflict *)local_188,false);
    if ((allocator *)(local_188[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_188[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_188[0] + -0x18));
      }
    }
    if ((lVar8 != 0) && (*(int *)(lVar8 + 0x28) != 0)) {
      uVar25 = 0;
      do {
        if (uVar25 < *(uint *)(lVar8 + 0x2c)) {
          plVar14 = (long *)((ulong)uVar25 * 8 + *(long *)(lVar8 + 0x20));
        }
        else {
          plVar14 = *(long **)(lVar8 + 0x20);
        }
        if ((*(int *)(*plVar14 + 0x30) == 8) || (*(int *)(*plVar14 + 0x30) == 5)) {
          if (uVar25 < *(uint *)(lVar8 + 0x2c)) {
            puVar15 = (undefined8 *)((ulong)uVar25 * 8 + *(long *)(lVar8 + 0x20));
          }
          else {
            puVar15 = *(undefined8 **)(lVar8 + 0x20);
          }
                    /* try { // try from 00d1bb6a to 00d1bb7e has its CatchHandler @ 00d1cb86 */
          pwVar9 = (wstring_conflict *)CDataValue::GetValueString((CDataValue *)*puVar15,true);
          std::wstring::wstring((wstring_conflict *)local_198,pwVar9);
          uVar20 = *(uint *)(this + 0x1f8);
          if (uVar20 < *(uint *)(this + 0x1fc)) {
            puVar18 = *(ulong **)(this + 0x1f0);
          }
          else if (*(long *)(this + 0x1f0) == 0) {
            uVar19 = (ulong)*(uint *)(this + 0x200);
            *(uint *)(this + 0x1fc) = *(uint *)(this + 0x200);
                    /* try { // try from 00d1c5db to 00d1c5df has its CatchHandler @ 00d1ce75 */
            puVar10 = operator_new__(uVar19 * 8 + 8);
            *puVar10 = uVar19;
            puVar18 = puVar10 + 1;
            if (uVar19 != 0) {
              lVar21 = uVar19 - 2;
              do {
                lVar21 = lVar21 + -1;
                puVar10[1] = (ulong)&DAT_01424558;
                puVar10 = puVar10 + 1;
              } while (lVar21 != -2);
            }
            *(ulong **)(this + 0x1f0) = puVar18;
            uVar20 = *(uint *)(this + 0x1f8);
          }
          else {
            uVar17 = *(uint *)(this + 0x1fc) + *(int *)(this + 0x200);
            uVar19 = (ulong)uVar17;
                    /* try { // try from 00d1bbb8 to 00d1bc89 has its CatchHandler @ 00d1ce75 */
            puVar10 = operator_new__(uVar19 * 8 + 8);
            *puVar10 = uVar19;
            puVar18 = puVar10 + 1;
            if (uVar19 != 0) {
              lVar21 = uVar19 - 2;
              do {
                lVar21 = lVar21 + -1;
                puVar10[1] = (ulong)&DAT_01424558;
                puVar10 = puVar10 + 1;
              } while (lVar21 != -2);
            }
            if (*(int *)(this + 0x1fc) != 0) {
              uVar20 = 0;
              do {
                std::wstring::assign((wstring_conflict *)(puVar18 + uVar20));
                uVar20 = uVar20 + 1;
              } while (uVar20 < *(uint *)(this + 0x1fc));
            }
            lVar21 = *(long *)(this + 0x1f0);
            if (lVar21 != 0) {
              plVar14 = (long *)(lVar21 + *(long *)(lVar21 + -8) * 8);
              do {
                plVar12 = *(long **)(this + 0x1f0);
                while( true ) {
                  do {
                    if (plVar14 == plVar12) {
                      operator_delete__((void *)(*(long *)(this + 0x1f0) + -8));
                      goto LAB_00d1bc5e;
                    }
                    plVar14 = plVar14 + -1;
                    paVar24 = (allocator *)(*plVar14 + -0x18);
                  } while (paVar24 == (allocator *)&std::wstring::_Rep::_S_empty_rep_storage);
                  LOCK();
                  piVar1 = (int *)(*plVar14 + -8);
                  iVar5 = *piVar1;
                  *piVar1 = *piVar1 + -1;
                  UNLOCK();
                  if (0 < iVar5) break;
                  std::wstring::_Rep::_M_destroy(paVar24);
                  plVar12 = *(long **)(this + 0x1f0);
                }
              } while( true );
            }
LAB_00d1bc5e:
            uVar20 = *(uint *)(this + 0x1f8);
            *(ulong **)(this + 0x1f0) = puVar18;
            *(uint *)(this + 0x1fc) = uVar17;
          }
          std::wstring::assign((wstring_conflict *)(puVar18 + uVar20));
          *(int *)(this + 0x1f8) = *(int *)(this + 0x1f8) + 1;
          if ((allocator *)(local_198[0] + -0x18) !=
              (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
            LOCK();
            piVar1 = (int *)(local_198[0] + -8);
            iVar5 = *piVar1;
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (iVar5 < 1) {
              std::wstring::_Rep::_M_destroy((allocator *)(local_198[0] + -0x18));
            }
          }
        }
        uVar25 = uVar25 + 1;
      } while (uVar25 < *(uint *)(lVar8 + 0x28));
    }
                    /* try { // try from 00d1bcd2 to 00d1bcd6 has its CatchHandler @ 00d1ce8f */
    std::wstring::wstring((wstring_conflict *)local_1a8,L"NAME",&local_48);
                    /* try { // try from 00d1bce4 to 00d1bcfb has its CatchHandler @ 00d1ce8a */
    pwVar9 = (wstring_conflict *)
             CDataGroup::GetDataValue
                       (local_2c8,(wstring_conflict *)local_1a8,(wstring_conflict *)&::EMPTY_WSTRING
                       );
    STRINGS::StringUpper((STRINGS *)local_1b8,pwVar9);
                    /* try { // try from 00d1bd03 to 00d1bd07 has its CatchHandler @ 00d1ce95 */
    std::wstring::assign((wstring_conflict *)(this + 0x50));
    if ((allocator *)(local_1b8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_1b8[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_1b8[0] + -0x18));
      }
    }
    if ((allocator *)(local_1a8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_1a8[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_1a8[0] + -0x18));
      }
    }
                    /* try { // try from 00d1bd54 to 00d1bd58 has its CatchHandler @ 00d1ce0e */
    std::wstring::wstring((wstring_conflict *)local_1c8,L"DISPLAYNAME",&local_49);
                    /* try { // try from 00d1bd66 to 00d1bd76 has its CatchHandler @ 00d1cdfe */
    CDataGroup::GetDataValue
              (local_2c8,(wstring_conflict *)local_1c8,(wstring_conflict *)&::EMPTY_WSTRING);
    std::wstring::assign((wstring_conflict *)(this + 0x58));
    if ((allocator *)(local_1c8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_1c8[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_1c8[0] + -0x18));
      }
    }
                    /* try { // try from 00d1bda9 to 00d1bdad has its CatchHandler @ 00d1cdc2 */
    std::wstring::wstring((wstring_conflict *)local_1d8,L"ALTERNATIVECOMPLETETEXT",&local_4a);
                    /* try { // try from 00d1bdbb to 00d1bdcb has its CatchHandler @ 00d1cdbd */
    CDataGroup::GetDataValue
              (local_2c8,(wstring_conflict *)local_1d8,(wstring_conflict *)&::EMPTY_WSTRING);
    std::wstring::assign((wstring_conflict *)(this + 0x38));
    if ((allocator *)(local_1d8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_1d8[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_1d8[0] + -0x18));
      }
    }
                    /* try { // try from 00d1bdfe to 00d1be02 has its CatchHandler @ 00d1cd8c */
    std::wstring::wstring((wstring_conflict *)local_1e8,L"ALTERNATIVECOMPLETETEXTSMALL",&local_4b);
                    /* try { // try from 00d1be10 to 00d1be20 has its CatchHandler @ 00d1c864 */
    CDataGroup::GetDataValue
              (local_2c8,(wstring_conflict *)local_1e8,(wstring_conflict *)&::EMPTY_WSTRING);
    std::wstring::assign((wstring_conflict *)(this + 0x40));
    if ((allocator *)(local_1e8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_1e8[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_1e8[0] + -0x18));
      }
    }
    *(undefined4 *)(this + 0x1c) = 0xffffffff;
                    /* try { // try from 00d1be62 to 00d1be66 has its CatchHandler @ 00d1c82f */
    std::wstring::wstring((wstring_conflict *)local_1f8,L"DEFEAT",&local_4c);
                    /* try { // try from 00d1be71 to 00d1be88 has its CatchHandler @ 00d1c82a */
    pCVar11 = (CDataGroup *)
              CDataGroup::GetDataGroupByName(local_2c8,(wstring_conflict *)local_1f8,false);
    uVar6 = calculateUnitsFromTag(this,pCVar11,(TArrayList *)(this + 400),(TArrayList *)0x0,0);
    *(undefined4 *)(this + 0x1a8) = uVar6;
    if ((allocator *)(local_1f8[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_1f8[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_1f8[0] + -0x18));
      }
    }
                    /* try { // try from 00d1bec9 to 00d1becd has its CatchHandler @ 00d1c874 */
    std::wstring::wstring((wstring_conflict *)local_208,L"ACQUIRE",&local_4d);
                    /* try { // try from 00d1bed8 to 00d1bef2 has its CatchHandler @ 00d1c8a5 */
    pCVar11 = (CDataGroup *)
              CDataGroup::GetDataGroupByName(local_2c8,(wstring_conflict *)local_208,false);
    uVar6 = calculateUnitsFromTag(this,pCVar11,(TArrayList *)(this + 0x178),(TArrayList *)0x0,1);
    *(undefined4 *)(this + 0x1ac) = uVar6;
    if ((allocator *)(local_208[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_208[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_208[0] + -0x18));
      }
    }
                    /* try { // try from 00d1bf33 to 00d1bf37 has its CatchHandler @ 00d1c8f0 */
    std::wstring::wstring((wstring_conflict *)local_218,L"POPULATE",&local_4e);
                    /* try { // try from 00d1bf42 to 00d1bf59 has its CatchHandler @ 00d1c8eb */
    pCVar11 = (CDataGroup *)
              CDataGroup::GetDataGroupByName(local_2c8,(wstring_conflict *)local_218,false);
    calculateUnitsFromTag(this,pCVar11,(TArrayList *)(this + 0x160),(TArrayList *)0x0,0);
    if ((allocator *)(local_218[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_218[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_218[0] + -0x18));
      }
    }
    local_2cc = 0;
    pCVar22 = this;
    do {
                    /* try { // try from 00d1bf92 to 00d1c026 has its CatchHandler @ 00d1cb86 */
      lVar8 = CDataGroup::GetDataGroupByName
                        (local_2c8,(wstring_conflict *)(&::g_QUEST_COMPLETE_TYPE_NAMES + local_2cc),
                         false);
      if (lVar8 != 0) {
        *(undefined4 *)(pCVar22 + 0xd8) = 2;
        *(undefined4 *)(pCVar22 + 0x108) = 2;
        if (*(int *)(lVar8 + 0x28) != 0) {
          uVar19 = 0;
          pCVar2 = this + (ulong)local_2cc * 0x18 + 200;
          do {
            uVar25 = (uint)uVar19;
            if (uVar25 < *(uint *)(lVar8 + 0x2c)) {
              plVar14 = (long *)(uVar19 * 8 + *(long *)(lVar8 + 0x20));
            }
            else {
              plVar14 = *(long **)(lVar8 + 0x20);
            }
            if ((*(int *)(*plVar14 + 0x30) == 8) || (*(int *)(*plVar14 + 0x30) == 5)) {
              if (uVar25 < *(uint *)(lVar8 + 0x2c)) {
                puVar15 = (undefined8 *)(uVar19 * 8 + *(long *)(lVar8 + 0x20));
              }
              else {
                puVar15 = *(undefined8 **)(lVar8 + 0x20);
              }
              pwVar9 = (wstring_conflict *)CDataValue::GetValueString((CDataValue *)*puVar15,true);
              STRINGS::StringUpper((STRINGS *)local_228,pwVar9);
              uVar20 = *(uint *)(pCVar22 + 0xd0);
              if (uVar20 < *(uint *)(pCVar22 + 0xd4)) {
                puVar18 = *(ulong **)(pCVar22 + 200);
              }
              else if (*(long *)(pCVar22 + 200) == 0) {
                uVar19 = (ulong)*(uint *)(pCVar22 + 0xd8);
                *(uint *)(pCVar22 + 0xd4) = *(uint *)(pCVar22 + 0xd8);
                    /* try { // try from 00d1c556 to 00d1c55a has its CatchHandler @ 00d1c815 */
                puVar10 = operator_new__(uVar19 * 8 + 8);
                *puVar10 = uVar19;
                puVar18 = puVar10 + 1;
                while (uVar19 = uVar19 - 1, uVar19 != 0xffffffffffffffff) {
                  puVar10[1] = (ulong)&DAT_01424558;
                  puVar10 = puVar10 + 1;
                }
                *(ulong **)(pCVar22 + 200) = puVar18;
                uVar20 = *(uint *)(pCVar22 + 0xd0);
              }
              else {
                uVar20 = *(uint *)(pCVar22 + 0xd4) + *(int *)(pCVar22 + 0xd8);
                uVar19 = (ulong)uVar20;
                    /* try { // try from 00d1c05d to 00d1c14a has its CatchHandler @ 00d1c815 */
                puVar10 = operator_new__(uVar19 * 8 + 8);
                *puVar10 = uVar19;
                puVar18 = puVar10 + 1;
                while (uVar19 = uVar19 - 1, uVar19 != 0xffffffffffffffff) {
                  puVar10[1] = (ulong)&DAT_01424558;
                  puVar10 = puVar10 + 1;
                }
                if (*(int *)(pCVar22 + 0xd4) != 0) {
                  uVar17 = 0;
                  do {
                    std::wstring::assign((wstring_conflict *)(puVar18 + uVar17));
                    uVar17 = uVar17 + 1;
                  } while (uVar17 < *(uint *)(pCVar2 + 0xc));
                }
                lVar21 = *(long *)(pCVar22 + 200);
                if (lVar21 != 0) {
                  plVar14 = (long *)(lVar21 + *(long *)(lVar21 + -8) * 8);
                  do {
                    plVar12 = *(long **)pCVar2;
                    while( true ) {
                      do {
                        if (plVar12 == plVar14) {
                          operator_delete__((void *)(*(long *)(pCVar22 + 200) + -8));
                          goto LAB_00d1c117;
                        }
                        plVar14 = plVar14 + -1;
                        paVar24 = (allocator *)(*plVar14 + -0x18);
                      } while (paVar24 == (allocator *)&std::wstring::_Rep::_S_empty_rep_storage);
                      LOCK();
                      piVar1 = (int *)(*plVar14 + -8);
                      iVar5 = *piVar1;
                      *piVar1 = *piVar1 + -1;
                      UNLOCK();
                      if (0 < iVar5) break;
                      std::wstring::_Rep::_M_destroy(paVar24);
                      plVar12 = *(long **)pCVar2;
                    }
                  } while( true );
                }
LAB_00d1c117:
                *(ulong **)(pCVar22 + 200) = puVar18;
                *(uint *)(pCVar22 + 0xd4) = uVar20;
                uVar20 = *(uint *)(pCVar22 + 0xd0);
              }
              std::wstring::assign((wstring_conflict *)(puVar18 + uVar20));
              *(int *)(pCVar22 + 0xd0) = *(int *)(pCVar22 + 0xd0) + 1;
              if ((allocator *)(local_228[0] + -0x18) !=
                  (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
                LOCK();
                piVar1 = (int *)(local_228[0] + -8);
                iVar5 = *piVar1;
                *piVar1 = *piVar1 + -1;
                UNLOCK();
                if (iVar5 < 1) {
                  std::wstring::_Rep::_M_destroy((allocator *)(local_228[0] + -0x18));
                }
              }
              uVar20 = *(uint *)(pCVar22 + 0x100);
              if (uVar20 < *(uint *)(pCVar22 + 0x104)) {
                pvVar16 = *(void **)(pCVar22 + 0xf8);
              }
              else if (*(long *)(pCVar22 + 0xf8) == 0) {
                *(uint *)(pCVar22 + 0x104) = *(uint *)(pCVar22 + 0x108);
                    /* try { // try from 00d1c5ae to 00d1c5b2 has its CatchHandler @ 00d1cb86 */
                pvVar16 = operator_new__((ulong)*(uint *)(pCVar22 + 0x108));
                *(void **)(pCVar22 + 0xf8) = pvVar16;
                uVar20 = *(uint *)(pCVar22 + 0x100);
              }
              else {
                uVar20 = *(uint *)(pCVar22 + 0x104) + *(int *)(pCVar22 + 0x108);
                pvVar16 = operator_new__((ulong)uVar20);
                if (*(int *)(pCVar22 + 0x104) != 0) {
                  uVar19 = 0;
                  do {
                    uVar17 = (int)uVar19 + 1;
                    *(undefined1 *)((long)pvVar16 + uVar19) =
                         *(undefined1 *)(*(long *)(pCVar22 + 0xf8) + uVar19);
                    uVar19 = (ulong)uVar17;
                  } while (uVar17 < *(uint *)(pCVar22 + 0x104));
                }
                if (*(void **)(pCVar22 + 0xf8) != (void *)0x0) {
                  operator_delete__(*(void **)(pCVar22 + 0xf8));
                }
                *(void **)(pCVar22 + 0xf8) = pvVar16;
                *(uint *)(pCVar22 + 0x104) = uVar20;
                uVar20 = *(uint *)(pCVar22 + 0x100);
              }
              *(undefined1 *)((long)pvVar16 + (ulong)uVar20) = 0;
              *(int *)(pCVar22 + 0x100) = *(int *)(pCVar22 + 0x100) + 1;
            }
            uVar19 = (ulong)(uVar25 + 1);
          } while (uVar25 + 1 < *(uint *)(lVar8 + 0x28));
        }
      }
      local_2cc = local_2cc + 1;
      pCVar22 = pCVar22 + 0x18;
    } while (local_2cc != 2);
                    /* try { // try from 00d1c1ce to 00d1c1d2 has its CatchHandler @ 00d1c8c8 */
    std::wstring::wstring((wstring_conflict *)local_238,L"REQUIREMENTS",&local_4f);
                    /* try { // try from 00d1c1dd to 00d1c1f0 has its CatchHandler @ 00d1c8c3 */
    pCVar11 = (CDataGroup *)
              CDataGroup::GetDataGroupByName(local_2c8,(wstring_conflict *)local_238,false);
    CQuestRequirements::parseRequirementTag(*(CQuestRequirements **)(this + 0x1e0),pCVar11);
    if ((allocator *)(local_238[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_238[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_238[0] + -0x18));
      }
    }
    if (*(long *)(this + 0x128) == 0) {
                    /* try { // try from 00d1c638 to 00d1c63c has its CatchHandler @ 00d1cb86 */
      this_01 = (CQuestRewards *)Ogre::NedAllocImpl::allocBytes(0x78,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00d1c646 to 00d1c64a has its CatchHandler @ 00d1c8cd */
      CQuestRewards::CQuestRewards(this_01,this);
      *(CQuestRewards **)(this + 0x128) = this_01;
    }
                    /* try { // try from 00d1c231 to 00d1c235 has its CatchHandler @ 00d1c75e */
    std::wstring::wstring((wstring_conflict *)local_248,L"REWARD",&local_50);
                    /* try { // try from 00d1c240 to 00d1c244 has its CatchHandler @ 00d1c751 */
    pCVar11 = (CDataGroup *)
              CDataGroup::GetDataGroupByName(local_2c8,(wstring_conflict *)local_248,false);
    if ((allocator *)(local_248[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_248[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_248[0] + -0x18));
      }
    }
    if (pCVar11 != (CDataGroup *)0x0) {
                    /* try { // try from 00d1c26e to 00d1c272 has its CatchHandler @ 00d1cb86 */
      CQuestRewards::parseRewardTag(*(CQuestRewards **)(this + 0x128),pCVar11);
    }
                    /* try { // try from 00d1c28b to 00d1c28f has its CatchHandler @ 00d1c7a6 */
    std::wstring::wstring((wstring_conflict *)local_258,L"DIALOG",&local_51);
                    /* try { // try from 00d1c29a to 00d1c29e has its CatchHandler @ 00d1c799 */
    pCVar11 = (CDataGroup *)
              CDataGroup::GetDataGroupByName(local_2c8,(wstring_conflict *)local_258,false);
    if ((allocator *)(local_258[0] + -0x18) !=
        (allocator *)&std::wstring::_Rep::_S_empty_rep_storage) {
      LOCK();
      piVar1 = (int *)(local_258[0] + -8);
      iVar5 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (iVar5 < 1) {
        std::wstring::_Rep::_M_destroy((allocator *)(local_258[0] + -0x18));
      }
    }
    if (pCVar11 != (CDataGroup *)0x0) {
                    /* try { // try from 00d1c2d4 to 00d1c345 has its CatchHandler @ 00d1cb86 */
      getQuestStrings(this,pCVar11,(wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 8),
                      (TArrayList *)(this + 0x60));
      getQuestStrings(this,pCVar11,(wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x10),
                      (TArrayList *)(this + 0x78));
      getQuestStrings(this,pCVar11,(wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x18),
                      (TArrayList *)(this + 0x90));
      getQuestStrings(this,pCVar11,(wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x20),
                      (TArrayList *)(this + 0xa8));
      pCVar13 = (CDataGroup *)
                CDataGroup::GetDataGroupByName
                          (pCVar11,(wstring_conflict *)(::gQUEST_DIALOG_TYPE_NAMES + 0x28),false);
      if (pCVar13 != (CDataGroup *)0x0) {
        this_00 = (CQuestDialog *)Ogre::NedAllocImpl::allocBytes(0xa8,(char *)0x0,0,(char *)0x0);
                    /* try { // try from 00d1c34f to 00d1c353 has its CatchHandler @ 00d1c700 */
        CQuestDialog::CQuestDialog(this_00,this);
        *(CQuestDialog **)(this + 0xc0) = this_00;
                    /* try { // try from 00d1c373 to 00d1c377 has its CatchHandler @ 00d1c6eb */
        std::wstring::wstring(local_268,L"UNITNAME",&local_52);
                    /* try { // try from 00d1c383 to 00d1c399 has its CatchHandler @ 00d1c718 */
        pwVar9 = (wstring_conflict *)
                 CDataGroup::GetDataValue(pCVar11,local_268,(wstring_conflict *)&::EMPTY_WSTRING);
        cVar4 = CQuestDialog::parseDialogTag(*(CQuestDialog **)(this + 0xc0),pwVar9,pCVar13);
                    /* try { // try from 00d1c39f to 00d1c3a3 has its CatchHandler @ 00d1c6eb */
        std::wstring::~wstring(local_268);
        if (cVar4 == '\0') {
          if (*(long **)(this + 0xc0) != (long *)0x0) {
                    /* try { // try from 00d1c3bb to 00d1c3bd has its CatchHandler @ 00d1cb86 */
            (**(code **)(**(long **)(this + 0xc0) + 8))();
          }
          *(undefined8 *)(this + 0xc0) = 0;
          uVar23 = 1;
          goto LAB_00d1c3ce;
        }
      }
    }
    uVar23 = 1;
    CDataGroup::~CDataGroup(local_2c8);
  }
  return uVar23;
}

/* address=00d1cf40
   symbol=CQuest::cleanUp */

/* WARNING: Removing unreachable block (ram,0x00d1d25b) */
/* CQuest::cleanUp(bool) */

void __thiscall CQuest::cleanUp(CQuest *this,bool param_1)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  long lVar5;
  undefined8 *puVar6;
  long *plVar7;
  long lVar8;
  CLevel *pCVar9;
  CPlayer *pCVar10;
  uint uVar11;
  uint uVar12;
  ulong uVar13;
  long local_48 [3];

  if ((*(long *)(this + 0x1d0) != 0) && (*(long *)(*(long *)(this + 0x1d0) + 0x10) != 0)) {
    if (this[0x20a] != (CQuest)0x0) {
      std::wstring::wstring((wstring_conflict *)local_48,(wstring_conflict *)(this + 0x30));
      pCVar10 = (CPlayer *)0x0;
      if (*(long *)(this + 0x1d0) != 0) {
        pCVar10 = *(CPlayer **)(*(long *)(this + 0x1d0) + 0x10);
      }
                    /* try { // try from 00d1cf98 to 00d1cf9c has its CatchHandler @ 00d1d21f */
      CPlayer::clearDungeonHistory(pCVar10);
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
      lVar5 = *(long *)(this + 0x1d0);
      lVar8 = 0;
      if (lVar5 != 0) {
        lVar8 = *(long *)(lVar5 + 0x10);
      }
      pCVar9 = (CLevel *)0x0;
      if (*(long *)(lVar8 + 0x68) != 0) {
        pCVar9 = *(CLevel **)(*(long *)(lVar8 + 0x68) + 0x18);
      }
      pCVar10 = (CPlayer *)0x0;
      if (lVar5 != 0) {
        pCVar10 = *(CPlayer **)(lVar5 + 0x10);
      }
      CPlayer::updateStoredLevels(pCVar10,pCVar9);
    }
    if (*(int *)(this + 0x138) != 0) {
      uVar4 = *(uint *)(this + 0x13c);
      uVar13 = 0;
      do {
        uVar12 = (uint)uVar13;
        uVar11 = 0;
        while( true ) {
          if (uVar12 < uVar4) {
            uVar2 = *(uint *)(*(long *)(uVar13 * 8 + *(long *)(this + 0x130)) + 8);
          }
          else {
            uVar2 = *(uint *)(**(long **)(this + 0x130) + 8);
          }
          if (uVar2 <= uVar11) break;
          if (uVar12 < uVar4) {
            plVar7 = (long *)(uVar13 * 8 + *(long *)(this + 0x130));
          }
          else {
            plVar7 = *(long **)(this + 0x130);
          }
          plVar7 = (long *)*plVar7;
          if (uVar11 < *(uint *)((long)plVar7 + 0xc)) {
            puVar6 = (undefined8 *)((ulong)uVar11 * 8 + *plVar7);
          }
          else {
            puVar6 = (undefined8 *)*plVar7;
          }
          uVar11 = uVar11 + 1;
          CQuestUnitData::cleanUpForQuestRemoveall((CQuestUnitData *)*puVar6,param_1);
          uVar4 = *(uint *)(this + 0x13c);
        }
        uVar13 = (ulong)(uVar12 + 1);
      } while (uVar12 + 1 < *(uint *)(this + 0x138));
    }
    if (*(int *)(this + 0x150) != 0) {
      uVar4 = *(uint *)(this + 0x154);
      uVar13 = 0;
      do {
        uVar12 = (uint)uVar13;
        uVar11 = 0;
        while( true ) {
          if (uVar12 < uVar4) {
            uVar2 = *(uint *)(*(long *)(uVar13 * 8 + *(long *)(this + 0x148)) + 8);
          }
          else {
            uVar2 = *(uint *)(**(long **)(this + 0x148) + 8);
          }
          if (uVar2 <= uVar11) break;
          if (uVar12 < uVar4) {
            plVar7 = (long *)(uVar13 * 8 + *(long *)(this + 0x148));
          }
          else {
            plVar7 = *(long **)(this + 0x148);
          }
          plVar7 = (long *)*plVar7;
          if (uVar11 < *(uint *)((long)plVar7 + 0xc)) {
            puVar6 = (undefined8 *)((ulong)uVar11 * 8 + *plVar7);
          }
          else {
            puVar6 = (undefined8 *)*plVar7;
          }
          uVar11 = uVar11 + 1;
          CQuestUnitData::cleanUpForQuestRemoveall((CQuestUnitData *)*puVar6,param_1);
          uVar4 = *(uint *)(this + 0x154);
        }
        uVar13 = (ulong)(uVar12 + 1);
      } while (uVar12 + 1 < *(uint *)(this + 0x150));
    }
    cleanUpDialog(this,(TArrayList *)(this + 0x60));
    cleanUpDialog(this,(TArrayList *)(this + 0x78));
    cleanUpDialog(this,(TArrayList *)(this + 0x90));
    cleanUpDialog(this,(TArrayList *)(this + 0xa8));
    pCVar10 = (CPlayer *)0x0;
    if (*(long *)(this + 0x1d0) != 0) {
      pCVar10 = *(CPlayer **)(*(long *)(this + 0x1d0) + 0x10);
    }
    CPlayer::removeQuestItemFromInventoryOrPetsInventoryByGuid
              (pCVar10,*(undefined8 *)(this + 0x1c8),0xffffffffffffffff,0,1,0x67);
    lVar5 = 0;
    if (*(long *)(this + 0x1d0) != 0) {
      lVar5 = *(long *)(*(long *)(this + 0x1d0) + 0x10);
    }
    if ((*(long *)(lVar5 + 0x68) != 0) &&
       (lVar5 = *(long *)(*(long *)(lVar5 + 0x68) + 0x18), lVar5 != 0)) {
      CLevel::makeQuestUnitsUncool(lVar5,SUB81(*(undefined8 *)(this + 0x1c8),0));
    }
    reinitializeQuest(this,false,false);
  }
  return;
}

/* address=00d1d270
   symbol=CQuest::giveRewardForQuest */

/* WARNING: Removing unreachable block (ram,0x00d1d3b7) */
/* CQuest::giveRewardForQuest() */

void __thiscall CQuest::giveRewardForQuest(CQuest *this)

{
  int *piVar1;
  int iVar2;
  CPlayer *pCVar3;
  CQuest *this_00;
  uint uVar4;
  wstring_conflict *pwVar5;
  long local_48 [3];

  if ((*(long *)(this + 0x1d0) != 0) &&
     (pCVar3 = *(CPlayer **)(*(long *)(this + 0x1d0) + 0x10), pCVar3 != (CPlayer *)0x0)) {
    CPlayer::incrementJournalStatistic(pCVar3,4,1);
    if (*(long *)(this + 0x128) != 0) {
      CQuestRewards::rewardPlayer();
      this[0x2d] = (CQuest)0x1;
    }
    if (*(int *)(this + 0x1f8) != 0) {
      uVar4 = 0;
      do {
        if (uVar4 < *(uint *)(this + 0x1fc)) {
          pwVar5 = (wstring_conflict *)((ulong)uVar4 * 8 + *(long *)(this + 0x1f0));
        }
        else {
          pwVar5 = *(wstring_conflict **)(this + 0x1f0);
        }
        STRINGS::StringUpper((STRINGS *)local_48,pwVar5);
                    /* try { // try from 00d1d301 to 00d1d305 has its CatchHandler @ 00d1d3a4 */
        this_00 = (CQuest *)
                  CQuestManager::getQuestByName
                            (*(CQuestManager **)(this + 0x1d0),(wstring_conflict *)local_48);
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
        if (this_00 != (CQuest *)0x0) {
          CQuestManager::giveQuest(*(CQuestManager **)(this + 0x1d0),this_00,(CBaseUnit *)0x0,false)
          ;
          setQuestAccepted(this_00,true);
        }
        uVar4 = uVar4 + 1;
      } while (uVar4 < *(uint *)(this + 0x1f8));
    }
    cleanUp(this,true);
  }
  return;
}

/* export-summary functions=36 failures=0 */
